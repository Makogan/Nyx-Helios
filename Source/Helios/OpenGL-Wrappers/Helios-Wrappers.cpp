//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**                                                                                     *
 * @brief Implementation of OpenGL wrapping classes for the Helios Library
 * 
 * @file Helios-Wrappers.cpp
 * @author Camilo Talero
 * @date 2018-04-15
 *                                                                                      */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================

#include "Helios-Wrappers.hpp"
#include "Helios/System-Libraries.hpp"

using namespace std;
//########################################################################################

namespace Helios{

//TODO: add destructors for the following classes
//========================================================================================
/*                                                                                      *
 *                                 Shading_Program Class                                *
 *                                                                                      */
//========================================================================================

//Compile and attach the shaders to the GL program
void Shading_Program::compileShaders(string vs, string tcs, string tes,
    string gs, string fs, string cs)
{
     //TODO: this needs better error checking
    if(vs == "" || fs == "")
    {
        cerr << "Both the vertex shader and the fragment shader need to be specified" << endl;
        return;
    }
    //Initialize mandatory shaders
    vertex = new Shader(vs);
	fragment = new Shader(fs);

    //Conditionally initialize optional shaders
    tessc = tcs == ""? NULL: new Shader(tcs);
    tesse = tes == ""? NULL: new Shader(tes);
    geometry = gs == ""? NULL: new Shader(gs);
    compute = cs == ""? NULL: new Shader(cs);

	//Initialize and create the rendering program
	programID = glCreateProgram();
    //Attach mandatory shaders
	glAttachShader(programID, vertex->getShaderID());
    glAttachShader(programID, fragment->getShaderID());

    //Attach optional shaders if available
    if(tessc!=NULL)
		glAttachShader(programID, tessc->getShaderID());
	if(tesse!=NULL)
		glAttachShader(programID, tesse->getShaderID());
	if(geometry!=NULL)
		glAttachShader(programID, geometry->getShaderID());
    if(compute!=NULL)
		glAttachShader(programID, compute->getShaderID());
}

//Each string is either null or a pointer to the path to the source shader file
#define E_MESS "Not Specified"
Shading_Program::Shading_Program(string vs, string tcs, string tes,
    string gs, string fs, string cs)
{
    compileShaders(vs,tcs,tes,gs,fs,cs);

    //Attempt to link the GLSL program
	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) //Check that linking was successful
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		string infoLog(maxLength, ' ');
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
        //Record problem
		cerr << endl << infoLog <<endl;
        Log::record_log(string(80,'!'));
        Log::record_log("Shader Program failed to link\n");
        Log::record_log("\nSource files:"
              "\nVertex Shader:" + (vs==""? E_MESS: vs)
            + "\nTessellation Control Shader:" + (tcs==""? E_MESS: tcs)
            + "\nTessellation Evaluation Shader:" + (tes==""? E_MESS: tes)
            + "\nGeometry Shader:" + (gs==""? E_MESS: gs)
            + "\nFragment Shader:" + (fs==""? E_MESS: fs)
            + "\nCompute Shader:" + (cs==""? E_MESS: cs)
            );
        Log::record_log("\nLinking error:\n" + infoLog);
        Log::record_log(infoLog+"\n");
        Log::record_log(string(80, '!'));

        // The program is useless now. So delete it.
		glDeleteProgram(programID);

		exit(EXIT_FAILURE);
	}
}
#undef E_MESS
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                     Shader Class                                     *
 *                                                                                      */
//========================================================================================

//──── Constructors and Destructors ──────────────────────────────────────────────────────

Shader::Shader(string file_path)
{
    //Ensure file is correct
    if(!check_file(file_path))
        return;

    //Get the shader string into RAM
    string source;
	ifstream input(file_path.c_str());
	copy(istreambuf_iterator<char>(input),
		istreambuf_iterator<char>(),
		back_inserter(source));
	input.close();

    const GLchar* s_ptr = source.c_str();//get raw c string (char array)

    shaderID = glCreateShader(type);//create shader on GPU
    glObjectLabel(GL_SHADER, shaderID, file_path.length(), file_path.c_str());//Name the object
	glShaderSource(shaderID, 1, &s_ptr, NULL);//set shader program source

	glCompileShader(shaderID);

    //verify compilation
	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if(status!=GL_TRUE)
	{
		cerr << "Shader compilation error. Could not compile: "
		    << file_path << "\nShader type: "
		    << shaderEnumToString(type)
		    <<endl;

        //Get the shader string from the GPU
		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

        //Get the error message associated with the compilation error
		string log(length, ' ');
		glGetShaderInfoLog(shaderID, log.length(), &length, &log[0]);

		cerr<< endl << source <<endl;
		cerr << endl << log <<endl;

        Log::record_log(string(80,'!'));
        Log::record_log("Shader " + file_path + " failed to compile\n");
        Log::record_log("\nShader"+file_path+":\n\n" + source + "\n\n");
        Log::record_log(log+"\n");
        Log::record_log(string(80, '!'));

        //Shader is now useless, delete
        glDeleteShader(shaderID);

		exit(EXIT_FAILURE);
	}
	type = type;
}

//──── Getters and Setters ───────────────────────────────────────────────────────────────

GLuint Shader::getShaderID()
{
    return shaderID;
}

GLenum Shader::getType()
{
    return type;
}

//──── Private Methods ───────────────────────────────────────────────────────────────────

//Verify that the file exists and that its name identifies it as a valid GLSL shader
bool Shader::check_file(std::string file_path)
{
    //Start reading from the input file
    std::ifstream infile(file_path);
    //Error check and output error message if needed
    if(!infile.good())
    {
        cerr << "Problem with file " + file_path << endl;
        cerr << "It could be that the file is corrupt or it does not exist" << endl;

        Log::record_log(string(80,'-'));
        Log::record_log("Error:\n\tShader not created due to error with file: " + file_path);
        Log::record_log(string(80,'-'));

        exit(EXIT_FAILURE);
    }

    //Set the entire string to lower case
    std::string lname = file_path;
    std::transform(lname.begin(), lname.end(), lname.begin(), ::tolower);

    //Look for a substring in the file to identify the shader type
    if(lname.find("vertex")!=string::npos)
        type = GL_VERTEX_SHADER;
    else if(lname.find("tessc")!=string::npos)
        type = GL_TESS_CONTROL_SHADER;
    else if(lname.find("tesse")!=string::npos)
        type = GL_TESS_EVALUATION_SHADER;
    else if(lname.find("geometry")!=string::npos)
        type = GL_GEOMETRY_SHADER;
    else if(lname.find("fragment")!=string::npos)
        type = GL_FRAGMENT_SHADER;
    else if(lname.find("compute")!=string::npos)
        type = GL_COMPUTE_SHADER;
    else
    {
        cerr << "Shader File cannot be identified. Please make sure the file name"
            "contains one of:\nvertex, tesse, tessc, geometry, "
            "fragment, compute\n (Not case sensitive)" << endl;
        cerr << "File Path: " + file_path  << endl;

        Log::record_log(string(80,'-'));
        Log::record_log("\tCould not identify shader file: " + file_path);
        Log::record_log(string(80,'-'));
    }

    //return true upon a good file
    return true;
}

}//Closing bracket of Helios namespace
//########################################################################################