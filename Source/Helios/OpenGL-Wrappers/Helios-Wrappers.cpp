//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Implementation of OpenGL wrapping classes for the Helios Library
 * 
 * @file Helios-Wrappers.cpp
 * @author Camilo Talero
 * @date 2018-04-15
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//
// ────────────────────────────────────────────────────────────────── I ──────────
//   :::::: I N C L U D E   F I L E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//
#include "Helios-Wrappers.hpp"
#include "Helios/System-Libraries.hpp"

using namespace std;
// ────────────────────────────────────────────────────────────────────────────────

namespace Helios{

//
// ──────────────────────────────────────────────────────────────── I ──────────
//   :::::: S H A D E R   C L A S S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────
//

bool Shader::check_file(std::string file_path)
{
    std::ifstream infile(file_path);
    if(!infile.good())
    {
        cerr << "Problem with file " + file_path << endl;
        cerr << "It could be that the file is corrupt or it does not exist" << endl;

        Log::record_log(string(80,'-'));
        Log::record_log("\tShader not created due to error with file: " + file_path);
        Log::record_log(string(80,'-'));

        exit(EXIT_FAILURE);
    }

    std::string lname = file_path; 
    std::transform(lname.begin(), lname.end(), lname.begin(), ::tolower);

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
            "fragment, compute\n (Not case snesitive)" << endl;
        cerr << "File Path: " + file_path  << endl;

        Log::record_log(string(80,'-'));
        Log::record_log("\tCould not identify shader file: " + file_path);
        Log::record_log(string(80,'-'));
    }

    return true;
}

Shader::Shader(string file_path)
{
    if(!check_file(file_path))
        return;
}
// ────────────────────────────────────────────────────────────────────────────────

}//Closing bracket of Helios namespace