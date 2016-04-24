#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "lib/btsFS.h"

using namespace std;

/***********************************************************************/
/*Copyright 2016 Luke Sanger                                           */
/*This file is part of bts.                                            */
/*                                                                     */
/*bts is free software: you can redistribute it and/or modify          */
/*it under the terms of the GNU General Public License as published by */
/*the Free Software Foundation, either version 3 of the License, or    */
/*(at your option) any later version.                                  */
/*                                                                     */
/*bts is distributed in the hope that it will be useful,               */
/*but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*GNU General Public License for more details.                         */
/*                                                                     */
/*You should have received a copy of the GNU General Public License    */
/*along with bts.  If not, see <http://www.gnu.org/licenses/>.         */
/***********************************************************************/

string editDescription(string editor);


int main(int argc, char* argv[]) {

    if(argc != 4) {

        cout << "Syntax is like this: " << endl;
        cout << "bts-new <bugname> <git commit version> <file>" << endl;
        return 0;

    }

    Config configFile;
    string userName = configFile.getNameFromConfigFile()+"<"+configFile.getEmailFromConfigFile()+">";
    string editor = configFile.getEditorFromConfigFile();
    string description = editDescription(editor);
    Bugs bugs;
    string bugFileArguments[6] = {userName, argv[1], argv[2], argv[3], description, "PRESENT"};
    vector<string> bugFileArgumentsVector(bugFileArguments, bugFileArguments+6);
    bugs.makeBugFile(bugFileArgumentsVector);
    return 0;

}

string editDescription(string editor) {

     string deleteFileCommand = "rm";
     string deleteTemporaryDescriptionFile = deleteFileCommand+" description.temp";
     string openEditor = editor+" description.temp";
     system(openEditor.c_str());
     string contents = returnContents("description.temp");
     system(deleteTemporaryDescriptionFile.c_str());
     return contents;

}
