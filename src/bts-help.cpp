#include <iostream>

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

int main() {

  cout << "This is a quick summary of the syntax for more information" << endl;
  cout << "please look up the man pages for your selected function or" << endl;
  cout << "look at the tutorial in the docs directory in /usr/local/bts." << endl;
  cout << endl;
  cout << "bts-init <username> <email> <command line text editor of choice>" << endl;
  cout << "summary: initalize bts repository";
  cout << endl;
  cout << "bts-new <bugname> <git commit-version> <file>" << endl;
  cout << "summary: create new bug file" << endl;
  cout << endl;
  cout << "bts-find <bugname>, bts-find -b, bts find" << endl;
  cout << "summary: show bug information, find number of bugs, show all bug information" << endl;
  return 0;

}
