#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

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

/**********************************************/
/*cJSON stands for crappy JSON and was made  */
/*so I didn't have to worry about linking    */
/*third party libraries and so I could make  */
/*compilation easier                         */
/**********************************************/

string returnContents(string fileName) {

      string currentLine;
      string contents;
      ifstream file(fileName.c_str());
      assert(file and fileName != "");

      while(getline(file, currentLine)) {

          contents += currentLine;
          contents += "\n";

      }

      assert(contents != "");
      return contents;

}

class cJSON {

  private:

      string cJSON;

      string returnType(char character) {

          if(character == ':') { return "START_VALUE"; }
          if(character == ';') { return "END_STATEMENT";
          }else{ return "NORM_CHAR"; }

      }

      string removeUnecessaryCJSONBeforePoint(string point) {

          int pointPos = cJSON.find(point);
          assert(pointPos != string::npos);
          int cJSONLen = cJSON.length();
          int lenOfEditedCJSON = cJSONLen - pointPos;
          assert(lenOfEditedCJSON > 0);
          return cJSON.substr(pointPos, lenOfEditedCJSON);

      }

  public:

      void load(string cJSONCode) {

          assert(cJSONCode != "");
          cJSON = cJSONCode;
          return;

      }

      void remove() {

          cJSON = "";
          return;

      }

      void changeCJSONField(string key, string value) {

          int cJSONFieldLocation = cJSON.find(key+":") - 1;
          assert(cJSONFieldLocation != string::npos and (key != "" and value != ""));
          int cJSONFieldLength = (key+":").length();
          int charactersToWrite = value.length();
          int x = 0;

          for(int i = cJSONFieldLocation+cJSONFieldLength; 0 < charactersToWrite; charactersToWrite--) {

            if(cJSON[++i] == ';') { cJSON.insert(i, " "); }
            if(charactersToWrite == 1 and cJSON[2+i] != ';') {

              while(cJSON[1+i] != ';') {

                cJSON.replace(1+i, 1, "");

              }

            }
            cJSON[i] = value[x];
            x++;

          }
          return;

      }

      void makeCJSONField(string key, string value) {

          assert(key != "" and value != "");
          cJSON += key+":"+value+";\n";
          return;

      }

      string findValueFromKey(string key) {

          assert(key != "");
          bool recordValue = false;
          string cJSONEdited = removeUnecessaryCJSONBeforePoint(key);
          string value;
          int cJSONEditedLen = cJSONEdited.length();

          for(int i = 0; i <= cJSONEditedLen; i++) {

              if(returnType(cJSONEdited[i]) == "START_VALUE") {

                  recordValue = true;

              }else if(returnType(cJSONEdited[i]) == "NORM_CHAR" and recordValue){

                  value += cJSONEdited[i];

              }else if(returnType(cJSONEdited[i]) == "END_STATEMENT") { return value; }

          }

          return "Key isn't found";

      }

      string print() {

          assert(cJSON != "");
          return cJSON;

      }

};



class cJSONFile {

      private:

           string cJSONFileName;
           cJSON cjson;

      public:

           void open(string fileName) {

               assert(fileName != "");
               cJSONFileName = fileName;
               return;

           }

           string getValueFromKey(string key) {

               assert(key != "");
               string cJSONFileContents = returnContents(cJSONFileName);
               cjson.load(cJSONFileContents);
               string value = cjson.findValueFromKey(key);
               cjson.remove();
               return value;

           }

           vector<string> getValueFromKeys(vector<string> keys) {

               assert(keys.size() > 0);
               string cJSONFileContents = returnContents(cJSONFileName);
               vector<string> values;
               cjson.load(cJSONFileContents);

               for(int i = 0; i < keys.size(); i++) {

                 values.push_back(cjson.findValueFromKey(keys[i]));

               }

               cjson.remove();
               return values;

           }

           void changeCJSONField(string key, string value) {

               assert(key != "" and value != "");
               cjson.load(returnContents(cJSONFileName));
               cjson.changeCJSONField(key, value);
               ofstream file(cJSONFileName.c_str());
               assert(file);
               file << cjson.print();
               cjson.remove();
               return;

           }

           void makeCJSONField(string key, string value) {

               ofstream file(cJSONFileName.c_str());
               assert(file and (key != "" and value != ""));
               cjson.makeCJSONField(key, value);
               file << cjson.print();
               cjson.remove();
               return;

           }

           void makeCJSONFields(vector<string> keys, vector<string> values) {

               ofstream file(cJSONFileName.c_str(), fstream::app);
               assert(file and (keys.size() > 0 and values.size() > 0));

               for(int i = 0; i < keys.size(); i++) {

                   cjson.makeCJSONField(keys[i], values[i]);

               }

               file << cjson.print();
               cjson.remove();
               return;

           }

           void remove() {

             cJSONFileName = "";
             cjson.remove();
             return;

           }

};
