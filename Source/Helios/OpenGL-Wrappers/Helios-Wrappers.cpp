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

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

using namespace std;
using namespace glm;
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                    Helping Methods                                   *
 *                                                                                      */
//========================================================================================

/**
 * @brief Set the data for a VBO
 *
 * @tparam T The type of the data with which to fill the buffer
 * @param buffer The OpenGL ID of the buffer
 * @param data Vector containing the data to fill the buffer with
*/
template <class T>
void inline static set_data_buffer(GLuint buffer, vector<T> &data, string name)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glObjectLabel(GL_BUFFER, buffer, -1, name.c_str());
    glBufferData(GL_ARRAY_BUFFER, sizeof(T)*data.size(), data.data(), GL_STATIC_DRAW);
}

/**
 * @brief Set the indices for indexed rendering in a VBO
 *
 * @tparam T The type if the index data  (should be uint, left as general just in case)
 * @param buffer The OpenGL ID of the buffer
 * @param data Vector containing the data to fill the buffer with
*/
template <class T>
void inline static set_indices_buffer(GLuint buffer, vector<T> &data, string name)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glObjectLabel(GL_BUFFER, buffer, -1, name.c_str());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T)*data.size(), data.data(),
        GL_STATIC_DRAW);
}

/**
 * @brief Set the attribute locations for a shader
 *
 * Each of the arrays should have the same number of elements. Each parameter is a list
 * of values to be passed top the corresponding parameter for
 * https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribFormat.xhtml.
 * Each index in one array represents one paremeter.
 *
 * @param locations Array of attribute locations
 * @param element_size Number of elements (counted as 4 bytes per element) per vertex instance
 * @param normalize Should the values be normalized
 * @param element_distance Distance between consecutive elements in the array
*/
void inline static set_attribute_locations(vector<GLuint> &locations,
    vector<GLint> &element_size, vector<GLboolean> &normalize,
    vector<GLuint> &element_distance)
{
    //check that array sizes match one another
    if(locations.size()!=element_size.size() || locations.size()!=normalize.size() ||
        locations.size()!=element_distance.size())
    {
        cerr << "Un-matching array sizes for set_attribute_locations()" << endl;
        Log::record_log(std::string(80, '!') +
            "\nUn-matching array sizes for set_attribute_locations()\n" +
            std::string(80, '!'));
    }
    //Specify layout format for each target location (the way the data is to be read)
    //This needs to match the layout declarations in the shaders
    int buffer_index = 0;
    for(uint i=0; i<locations.size(); i++)
    {
        glEnableVertexAttribArray(locations[i]);
        glVertexAttribFormat(locations[i], element_size[i],
            GL_FLOAT, normalize[i], element_distance[i]);
        glVertexAttribBinding(locations[i], buffer_index++);
    }
}
/**
 * @brief Extract a base name from a file path
 *
 * @param file_path
 * @return string
*/
string inline static extract_name(string file_path)
{
    string name = string(basename((char*) file_path.c_str()));
    size_t lastindex = name.find_last_of(".");
    return name.substr(0, lastindex);
}
//########################################################################################

namespace Helios{

//========================================================================================
/*                                                                                      *
 *                                     Texture CLass                                    *
 *                                                                                      */
//========================================================================================

//Main constructor
Texture::Texture(string file_path, GLuint t_target)
{
    //Change the coordinate system of the image
    stbi_set_flip_vertically_on_load(true);
    int numComponents;
    //Load the pixel data of the image
    void *data = stbi_load(file_path.c_str(), &width, &height, &numComponents, 0);
    if (data == nullptr)//Error check
    {
        cerr << "Error when loading texture from file: " + file_path << endl;

        Log::record_log(
            string(80, '!') +
            "\nError when loading texture from file: " + file_path + "\n" +
            string(80, '!')
        );
        exit(EXIT_FAILURE);
    }
    //Create the texture OpenGL object
    target = t_target;
    glGenTextures(1, &textureID);
    glBindTexture(target, textureID);
    //Name the texture
    glObjectLabel(GL_TEXTURE, textureID, -1,
        ("\"" + extract_name(file_path) +"\"").c_str());
    //Set the color format
    color_format = numComponents == 3 ? GL_RGB : GL_RGBA;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(target, 0, color_format, width, height, 0,
        color_format, GL_UNSIGNED_BYTE, data);
    //Set the texture parameters of the image
   	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //free the memory
    stbi_image_free(data);
    //Create a debug notification event
    char name[100];
    glGetObjectLabel(GL_TEXTURE, textureID, 100, NULL, name);
    string message = "Succesfully created texture: " + string(name) +
        ". Bound to target: " + textureTargetEnumToString(target);
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_OTHER, 0,
        GL_DEBUG_SEVERITY_NOTIFICATION, message.size(), message.c_str());
}

//Destructor
Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

//Load the texture info to a program into a uniform sampler
void Texture::load_to_program(Shading_Program *program, string uniform)
{
    //Request the program for a free texture unit
    GLenum texture_unit = program->getFreeTextureUnit();
    //Use program
    program->use();
    //Bind texture to the texture unit to its appropriate target
    glActiveTexture(texture_unit);
	glBindTexture(target, textureID);
    //Get the uniform location in the program and attach the texture unit
    GLuint location = program->get_uniform_location(uniform);
    glUniform1i(location,texture_unit - GL_TEXTURE0);
}
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                      Mesh Class                                      *
 *                                                                                      */
//========================================================================================

//Enumerators used to index through the buffers[] array
enum {MESH_VERTEX_BUFFER=0, MESH_NORMAL_BUFFER, MESH_UV_BUFFER, MESH_INDICES_BUFFER};

//Default mesh constructor, for testing only
Mesh::Mesh()
{
    //Create a triangle for illustration purposes
    vertices = {glm::vec3(-1,-1,0), glm::vec3(1,-1,0), glm::vec3(0,1,0)};
    normals = {glm::vec3(-1,-1,0), glm::vec3(1,-1,0), glm::vec3(0,1,0)};
    uvs = {vec2(0,0), vec2(1,0), vec2 (0,1)};
    indices = {0,1,2};

    //Initialize VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glObjectLabel(GL_VERTEX_ARRAY, VAO, -1, "\"Generic mesh VAO\"");

    //Initialize buffers and fill them with data
    glGenBuffers(4, buffers);
    set_data_buffer(buffers[MESH_VERTEX_BUFFER], vertices,
        "\"Default Mesh Vertex Buffer\"");
    set_data_buffer(buffers[MESH_NORMAL_BUFFER], normals,
        "\"Default Mesh Normal Buffer\"");
    set_data_buffer(buffers[MESH_UV_BUFFER], uvs,
        "\"Default Mesh UV Buffer\"");
    set_indices_buffer(buffers[MESH_INDICES_BUFFER], indices,
        "\"Default Mesh Index Buffer\"");

    //Set attribute location information
    vector<GLuint> locs = {0,1,2};  // attribute locations 0,1,2
    vector<GLint> sizes = {3,3,2};  // element sizes of 3,3,2 bytes (vec3, vec3, vec2)
    vector<GLboolean> normalize = {false, true, false}; //Should the element be normalized
    vector<GLuint> distance = {0,0,0}; //Distance between elements of the buffer
    set_attribute_locations(locs, sizes, normalize, distance);
}
//Construct a mesh from a file
Mesh::Mesh(string file_path)
{
    //Load an object from a wavefront file
    load_from_obj(file_path);

    //Extract base file name
    string name = extract_name(file_path);

    //Initialize VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glObjectLabel(GL_VERTEX_ARRAY, VAO, -1, string("\"" + name + " mesh VAO\"").c_str());

    //Initialize buffers and fill them with data
    glGenBuffers(4, buffers);
    set_data_buffer(buffers[MESH_VERTEX_BUFFER], vertices,
        "\"" + name + " mesh vertex buffer\"");
    set_data_buffer(buffers[MESH_NORMAL_BUFFER], normals,
        "\"" + name + " mesh normal buffer\"");
    set_data_buffer(buffers[MESH_UV_BUFFER], uvs,
        "\"" + name + " mesh uv buffer\"");
    set_indices_buffer(buffers[MESH_INDICES_BUFFER], indices,
        "\"" + name + " mesh index buffer\"");

    //Set attribute location information
    vector<GLuint> locs = {0,1,2};  // attribute locations 0,1,2
    vector<GLint> sizes = {3,3,2};  // element sizes of 3,3,2 bytes (vec3, vec3, vec2)
    vector<GLboolean> normalize = {false, true, false}; //Should the element be normalized
    vector<GLuint> distance = {0,0,0}; //Distance between elements of the buffer
    set_attribute_locations(locs, sizes, normalize, distance);
}
// Mesh destructor
Mesh::~Mesh()
{
    glDeleteBuffers(4, buffers);
}
//Draw the mesh
void Mesh::draw()
{
    //Bind the buffers and draw their contents
    GLintptr offsets[] = {0,0,0};
    int strides[] = {sizeof(vec3),sizeof(vec3), sizeof(vec2)};
    glBindVertexBuffers(0, 3, buffers, offsets, strides);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
//Load mesh from .obj file
void Mesh::load_from_obj(string file_path)
{
    vector<vec3> vs, ns;
    vector<vec2> ts;

    ifstream wfile;
    wfile.open(file_path);
    //error check
    if (!wfile) {
        cerr << "Unable to open file " << file_path << " when creating mesh" <<endl;
        Log::record_log(
            string(80, '!') +
            "Error with file " + file_path + " when crating mesh" +
            string(80, '!')
            );
        exit(EXIT_FAILURE);   // call system to stop
    }
    string line;
    while(getline(wfile, line))
    {
        //Create string stream and read the first word
        stringstream ss(line);
        string word;
        ss >> word;
        //If the first word in the line is 'v'
        //then this is a vertex information line
        if(word == "v")
        {
            vector<double> coords;
            //convert and store info to temporary vertex array
            while(ss>>word)
                coords.push_back(stof(word));
            vs.push_back(vec3(coords[0], coords[1], coords[2]));
        }
        //If the first word in the line is 'vt' this is
        //a texture coordinate information line
        else if(word == "vt")
        {
           vector<double> coords;
            //convert and store info to temporary uvs array
            while(ss>>word)
                coords.push_back(stof(word));
            ts.push_back(vec2(coords[0], coords[1]));
        }
        //If the first word in the line is 'vn' this is
        //a normals information line
        else if(word == "vn")
        {
            vector<double> coords;
            //convert and store info to temporary vertex array
            while(ss>>word)
                coords.push_back(stof(word));
            ns.push_back(vec3(coords[0], coords[1], coords[2]));
        }
    }
    //reset stream to the beggining of the file
    wfile.clear();
    wfile.seekg(0, ios::beg);
    //once again read every line
    while(getline(wfile, line))
    {
        //once again read word by word
        stringstream ss(line);
        string word;
        ss >> word;
        //if the first word is 'f' this is a face information line
        if(word == "f")
        {
            //process the word, there should be 3 consecutive such words only
            while(ss>>word)
            {
                //split the string
                replace(word.begin(), word.end(), '/', ' ');

                //Store index information of the vertex/texture/normal relationship
                stringstream ws(word);
                vector<int> indices;
                string number;
                for(int i=0; i<3; i++)
                {
                    ws >> number;
                    indices.push_back(stoi(number)-1);
                }

                //Push associated vertex and normal information into the return arrays
                //Now each vertex is associated with the correct normal.
                vertices.push_back(vs[indices[0]]);
                normals.push_back(ns[indices[2]]);

                //Same as above for texture coordinates
                    uvs.push_back(ts[indices[1]]);

            }
        }
    }
    //Close the file
    wfile.close();
}
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
    //Name the object
    glObjectLabel(GL_SHADER, shaderID, file_path.length(), file_path.c_str());
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

//Destructor
Shader::~Shader()
{
    glDeleteShader(shaderID);
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

        exit(EXIT_FAILURE);
    }

    //return true upon a good file
    return true;
}
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                 Shading_Program Class                                *
 *                                                                                      */
//========================================================================================
//Enumerators used to index through the shaders[] array
enum {HELIOS_VERTEX_S=0, HELIOS_TESSC_S, HELIOS_TESSE_S,
      HELIOS_GEOMETRY_S, HELIOS_FRAGMENT_S, HELIOS_COMPUTE_S};

#define E_MESS "Not Specified"
/**
 * @brief Verify that an OpenGL program was correctly linked
 *
 * @param programID The program to be verified
 * @param vs Path to a shader source file or ""
 * @param tcs Path to a shader source file or ""
 * @param tes Path to a shader source file or ""
 * @param gs Path to a shader source file or ""
 * @param fs Path to a shader source file or ""
 * @param cs Path to a shader source file or ""
*/
void static verify_linking(GLuint programID, string vs, string tcs, string tes,
    string gs, string fs, string cs)
{
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

//Each string is either null or a pointer to the path to the source shader file
Shading_Program::Shading_Program(string vs, string tcs, string tes,
    string gs, string fs, string cs)
{
    //TODO: this needs better error checking
    if(vs == "" || fs == "")
    {
        cerr << "Both the vertex shader and the fragment shader need to be specified\n";
        exit(EXIT_FAILURE);
    }
    vector<Shader*> shaders = vector<Shader*>(6);
    //Initialize mandatory shaders
    shaders[HELIOS_VERTEX_S] = new Shader(vs);
	shaders[HELIOS_FRAGMENT_S] = new Shader(fs);

    //Conditionally initialize optional shaders
    shaders[HELIOS_TESSC_S]= tcs == ""? NULL: new Shader(tcs);
    shaders[HELIOS_TESSE_S] = tes == ""? NULL: new Shader(tes);
    shaders[HELIOS_GEOMETRY_S] = gs == ""? NULL: new Shader(gs);
    shaders[HELIOS_COMPUTE_S] = cs == ""? NULL: new Shader(cs);

	//Initialize and create the rendering program
	programID = glCreateProgram();
    string name = string(basename((char*) vs.c_str()));
    size_t lastindex = name.find_last_of("-");
    name = name.substr(0, lastindex);
    glObjectLabel(GL_PROGRAM, programID, -1, ("\""+name+"\"").c_str());

    //Attach shaders if available
    for(int c_shader=0; c_shader < shaders.size(); c_shader++)
        if(shaders[c_shader]!=NULL)
            shaders[c_shader]->attachTo(programID);

    //Attempt to link the GLSL program
	glLinkProgram(programID);
    verify_linking(programID, vs, tcs, tes, gs, fs, cs);

    //Delete the saders, they are no longer needed once we have the program
    for(int c_shader=0; c_shader < shaders.size(); c_shader++)
    {
        if(shaders[c_shader]!=NULL)
        {
            shaders[c_shader]->detachFrom(programID);
            delete(shaders[c_shader]);
        }
    }
}

Shading_Program::~Shading_Program()
{
    glDeleteProgram(programID);
}

//──── Other Functions ───────────────────────────────────────────────────────────────────

        //Retrieve uniform location
        GLint Shading_Program::get_uniform_location(std::string name)
        {
            //Get the current active program
            use();
            //Get the location of the uniform in the shader
            GLint loc = glGetUniformLocation(programID, name.c_str());
            //Error handling
            if(loc == GL_INVALID_VALUE || loc==GL_INVALID_OPERATION || loc==-1)
            {
                std::cerr << "Error returned when trying to find uniform " <<
                    "\"" + name + "\"" << std::endl;

                if(loc == -1)
                {
                    char label_buffer[100];
                    GLsizei buff_size;
                    glGetObjectLabel(GL_PROGRAM, programID, 100, &buff_size, label_buffer);

                    Log::record_log(
                        std::string(80, '!') + "\nFailed to find uniform: " + name + "\n"
                        + "No such uniform exists in program: " + std::string(label_buffer)
                        + "\n" + std::string(80, '!')
                    );
                }
                else
                {
                    Log::record_log(
                        std::string(80, '!') +
                        "Problem when requesting uniform: \"" + name + "\"\n" +
                        "Check that there is an active program and that it has been"
                        "correctly Initialized" +
                        std::string(80, '!')
                    );
                }
                exit(EXIT_FAILURE);
            }

            return loc;
        }

}//Closing bracket of Helios namespace
//########################################################################################