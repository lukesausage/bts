#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "cJSON.h"

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

class btsFS {

    public:

        void init() {

            system("mkdir .bts");
            system("mkdir .bts/bugs");
            return;

        }

        void callToJebus() {

            cout << "ALL HAIL JEBUS" << endl;
            return;

        }

};

class Config {

    private:

         string configFileContents;
         const string configFileLocation = ".bts/bts.config";

    public:

         void writeStandardCredentials(string editor, string name, string email) {

             assert(editor != "" and (name != "" and email != ""));
             cJSONFile cjsonfile;
             cjsonfile.open(configFileLocation);
             string standardCredentialKeys[3] = {"name", "email", "editor"};
             string standardCredentialValues[3] = {name, email, editor};
             vector<string> standardCredentialKeysVector(standardCredentialKeys, standardCredentialKeys+3);
             vector<string> standardCredentialValuesVector(standardCredentialValues, standardCredentialValues+3);
             cjsonfile.makeCJSONFields(standardCredentialKeysVector, standardCredentialValuesVector);
             return;


         }

         void getAndWriteStandardCredentialsFromGit() {

             /* COMING SOON */
             return;

         }

         string getEditorFromConfigFile() {

             cJSONFile cjsonfile;
             cjsonfile.open(configFileLocation);
             return cjsonfile.getValueFromKey("editor");

         }

         string getNameFromConfigFile() {

             cJSONFile cjsonfile;
             cjsonfile.open(configFileLocation);
             return cjsonfile.getValueFromKey("name");

         }

         string getEmailFromConfigFile() {

             cJSONFile cjsonfile;
             cjsonfile.open(configFileLocation);
             return cjsonfile.getValueFromKey("email");

         }

};

class Bugs {

    private:

         string bugFileName;

         vector<string> constructBugFileParametersNames() {

             const int parameterNamesSize = 6;
             const string parameterNames[parameterNamesSize] = {"submitter", "bugname", "commit-version", "file", "description", "status"};
             vector<string> bugFileParametersNames(parameterNames, parameterNames+parameterNamesSize);
             return bugFileParametersNames;

         }

         void addBugFileToMap(string bugFile) {

             ofstream file(".bts/bugs/bugs.map", fstream::app);
             assert(bugFile != "" and file);
             file << bugFile << endl;
             return;

         }

         string generateRandomString() {

             string randomString;
             string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

             for(int i = 0; i < 8; ++i) {

                 randomString += chars[(rand()*time(NULL)) % (sizeof(chars) - 1)];

             }

             return randomString;

         }

    public:

        void init() {

            system("mkdir .bts/bugs");
            return;

        }

        void makeBugFile(vector<string> bugFileParameters) {

            assert(bugFileParameters.size() > 0);
            cJSONFile cjsonFile;
            string bugFileName = generateRandomString();
            vector<string> bugFileParametersNames = constructBugFileParametersNames();
            addBugFileToMap(bugFileName);
            cjsonFile.open(".bts/bugs/"+bugFileName);
            cjsonFile.makeCJSONFields(bugFileParametersNames, bugFileParameters);
            return;

        }

        vector<string> getCJSONFieldValuesFromAll(string key) {

            ifstream file(".bts/bugs/bugs.map");
            assert(key != "" and file);
            string currentLine;
            vector<string> cJSONFieldValues;
            cJSONFile cjsonFile;

            while(getline(file, currentLine)) {

                cjsonFile.open(".bts/bugs/"+currentLine);
                cJSONFieldValues.push_back(cjsonFile.getValueFromKey(key));
                cjsonFile.remove();

            }

            return cJSONFieldValues;

        }

        vector<string> getCJSONFieldsValueFromAll(vector<string> keys) {

            ifstream file(".bts/bugs/bugs.map");
            assert(file and keys.size() > 0);
            string currentLine;
            vector<string> cJSONFieldValues;
            cJSONFile cjsonFile;

            while(getline(file, currentLine)) {

                cjsonFile.open(".bts/bugs/"+currentLine);
                vector<string> temporaryValues = cjsonFile.getValueFromKeys(keys);
                cJSONFieldValues.reserve(temporaryValues.size());
                cJSONFieldValues.insert(cJSONFieldValues.end(), temporaryValues.begin(), temporaryValues.end());
                cjsonFile.remove();

            }
            return cJSONFieldValues;

        }

        string getCJSONFieldValuesFromBugID(string bugID, string key) {

            assert(bugID != "" and key != "");
            cJSONFile cjsonFile;
            cjsonFile.open(".bts/bugs/"+bugID);
            string value = cjsonFile.getValueFromKey(key);
            cjsonFile.remove();
            return value;

        }

        vector<string> getCJSONFieldsValueFromBugID(string bugID, vector<string> keys) {

            cJSONFile cjsonFile;
            cjsonFile.open(".bts/bugs/"+bugID);
            vector<string> cJSONFieldsValues = cjsonFile.getValueFromKeys(keys);
            cJSONFieldsValues.reserve(cJSONFieldsValues.size());
            cJSONFieldsValues.insert(cJSONFieldsValues.end(), cJSONFieldsValues.begin(), cJSONFieldsValues.end());
            cjsonFile.remove();
            return cJSONFieldsValues;

        }

        void changeCJSONFieldValuesFromBugID(string bugID, string key, string value) {

            assert(bugID != "" and (key != "" and value != ""));
            cJSONFile cjsonFile;
            cjsonFile.open(".bts/bugs/"+bugID);
            cjsonFile.changeCJSONField(key, value);
            cjsonFile.remove();
            return;

        }


        string getBugIdFromBugName(string name) {

            ifstream file(".bts/bugs/bugs.map");
            assert(file and name != "");
            string currentLine;
            cJSONFile cjsonFile;

            while(getline(file, currentLine)) {

                cjsonFile.open(".bts/bugs/"+currentLine);
                if(cjsonFile.getValueFromKey("bugname") == name) { cjsonFile.remove(); return currentLine; }
                cjsonFile.remove();

            }

            return "bugname is incorrect or doesn't exist";

        }

        int getNumberOfBugs() {

            int total = 0;
            vector<string> bugStatuses = getCJSONFieldValuesFromAll("status");

            for(int i = 0; i <= bugStatuses.size(); i++) {

                if(bugStatuses[i] == "PRESENT") { total += 1; }

            }
            return total;

        }

        void displayBugFromBugName(string bugName) {

            const string bugInformationKeysArray[6] = {"bugname", "description", "commit-version", "file", "submitter", "status"};
            vector<string> bugInformationKeys(bugInformationKeysArray, bugInformationKeysArray+6);
            vector<string> bugInformation = getCJSONFieldsValueFromBugID(getBugIdFromBugName(bugName), bugInformationKeys);
            cout << "#######################################################" << endl;
            cout << "Name: " << bugInformation[0] << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "Description: " << bugInformation[1] << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "Commit-Version: " << bugInformation[2] << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "File: " << bugInformation[3] << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "Submitter: " << bugInformation[4] << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "Status: " << bugInformation[5] << endl;
            cout << "#######################################################" << endl;
            return;

        }

        void displayAllBugs() {

            const string bugInformationKeysArray[6] = {"bugname", "description", "commit-version", "file", "submitter", "status"};
            vector<string> bugInformationKeys(bugInformationKeysArray, bugInformationKeysArray+6);
            vector<string> bugInformation = getCJSONFieldsValueFromAll(bugInformationKeys);

            for(int i = 0; i < (bugInformation.size() / 6); i++) {

                cout << "#######################################################" << endl;
                cout << "Name: " << bugInformation[i] << endl;
                cout << "-------------------------------------------------------" << endl;
                cout << "Description: " << bugInformation[i+1] << endl;
                cout << "-------------------------------------------------------" << endl;
                cout << "Commit-Version: " << bugInformation[i+2] << endl;
                cout << "-------------------------------------------------------" << endl;
                cout << "File: " << bugInformation[i+3] << endl;
                cout << "-------------------------------------------------------" << endl;
                cout << "Submitter: " << bugInformation[i+4] << endl;
                cout << "-------------------------------------------------------" << endl;
                cout << "Status: " << bugInformation[i+5] << endl;
                cout << "#######################################################" << endl;

            }

            return;

        }

        void changeBugStatusToFixed(string bugName) {

            changeCJSONFieldValuesFromBugID(getBugIdFromBugName(bugName), "status", "FIXED");
            return;

        }

};
