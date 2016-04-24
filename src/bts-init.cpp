#include <iostream>
#include <stdlib.h>
#include <fstream>
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

int main(int argc, char* argv[]) {

    if(argc < 4) {

      cout << "Syntax is like this: " << endl;
      cout << "bts-init <username> <email> <editor of choice>" << endl;
      return 0;

    }

    btsFS btsFileSystem;
    btsFileSystem.init();
    Config configFile;
    configFile.writeStandardCredentials(argv[3], argv[1], argv[2]);
    return 0;

}
