#include <bits/stdc++.h>
using namespace std;

#define UNDEFINED -1
#define TRUE 1
#define FALSE 0

uint numVariables;
uint numClauses;
vector<vector<int>> clauses;
vector<vector<uint>> positiveClauses; // positiveClauses[i] = indices of clauses where i occurs
vector<vector<uint>> negetiveClauses; // negetiveClauses[i] = indices of clauses where -i occurs 
vector<int> finalModel;

void getInput (vector<pair<int,int>> &clauseMetaData) {

    char c = cin.get(); // CNF comments
    while (c == 'c') {
        while (c != '\n') {
            c = cin.get();
        }
        c = cin.get();
    }
    string t;
    cin>>t;

    cin>>numVariables;
    cin>>numClauses;
    for (uint i=0; i<numVariables+1; i++) {
        finalModel.push_back(UNDEFINED);
    }
    positiveClauses.resize(numVariables+1);
    negetiveClauses.resize(numVariables+1);
    for (uint i=0; i<numClauses; i++) {
        vector<int> a;
        int c;
        cin>>c;
        while (c != 0) {
            a.push_back(c);
            if (c > 0) {
                positiveClauses[c].push_back(i);
            }
            else {
                negetiveClauses[-c].push_back(i);
            }
            cin>>c;
        }
        // a.value = UNDEFINED;
        // a.size = a.elements.size();
        clauses.push_back(a);
        clauseMetaData.push_back(make_pair(UNDEFINED,a.size()));
    }
}

bool unitProp (vector<pair<int,int>> &clauseMetaData, vector<int> &m) {
    for (uint clause=0; clause<numClauses; clause++) {
        // cout<<"Clause number: "<<clause<<" meta data is : ("<<clauseMetaData[clause].first<<","<<clauseMetaData[clause].second<<")\n";
        if (clauseMetaData[clause].first == FALSE) {
            return false;
        }
        else if (clauseMetaData[clause].first == UNDEFINED && clauseMetaData[clause].second == 1) {
            // first locate unit variable
            int unitVar = 0;
            vector<int> clauseBeingProp = clauses[clause];
            for (int i=0; i<clauseBeingProp.size(); i++) {
                if (m[abs(clauseBeingProp[i])] == UNDEFINED) {
                    unitVar = clauseBeingProp[i];
                }
            }

            if (unitVar > 0) {
                // first set m[unitVar] = TRUE
                m[unitVar] = TRUE;
                // for every clause where unitVar occurs positively, make them true
                for (int i=0; i<positiveClauses[unitVar].size(); i++) {
                    clauseMetaData[positiveClauses[unitVar][i]].first = TRUE;
                }
                // for every clause where unitVar occurs negetively, decrease size by one
                for (int i=0; i<negetiveClauses[unitVar].size(); i++) {
                    clauseMetaData[negetiveClauses[unitVar][i]].second--;
                    if (clauseMetaData[negetiveClauses[unitVar][i]].second == 0) {
                        return false; // l & -l type situation
                    }
                }
            }
            else {
                // set m[abs(unitVar)] = false
                unitVar = abs(unitVar);
                m[unitVar] = FALSE;
                for (int i=0; i<negetiveClauses[unitVar].size(); i++) {
                    clauseMetaData[negetiveClauses[unitVar][i]].first = TRUE;
                }
                for (int i=0; i<positiveClauses[unitVar].size(); i++) {
                    clauseMetaData[positiveClauses[unitVar][i]].second--;
                    if (clauseMetaData[positiveClauses[unitVar][i]].second == 0) {
                        return false;
                    } 
                }
            }
        }
        else {
            continue;
        }
    }
    return true;
}

bool doPll (vector<pair<int,int>> clauseMetaData, vector<int> model) {
    if (!unitProp(clauseMetaData,model)) {
        return false;
    }
    bool shouldBreak = true;
    for (int i=0; i<clauseMetaData.size(); i++) {
        if (clauseMetaData[i].first != TRUE) {
            shouldBreak = false;
            if (clauseMetaData[i].first == FALSE) {
                return false;
            }
        }
    }

    if (shouldBreak) {
        // model found!
        finalModel = model;
        return true;
    }

    for (int var=1; var<=numVariables; var++) {
        if (model[var] == UNDEFINED) {
            // create two children, pos and neg
            vector<int> modelPos = model;
            vector<int> modelNeg = model;
            vector<pair<int,int>> posClauseMeta = clauseMetaData;
            vector<pair<int,int>> negClauseMeta = clauseMetaData;
            modelPos[var] = TRUE;
            modelNeg[var] = FALSE;
            bool doPos = true;
            bool doNeg = true;
            for (int i=0; i<positiveClauses[var].size(); i++) {
                posClauseMeta[positiveClauses[var][i]].first = TRUE;
                negClauseMeta[positiveClauses[var][i]].second--;
                if (negClauseMeta[positiveClauses[var][i]].second == 0) {
                    doNeg = false; // no point because its false
                }
            }
            for (int i=0; i<negetiveClauses[var].size(); i++) {
                negClauseMeta[negetiveClauses[var][i]].first = TRUE;
                posClauseMeta[negetiveClauses[var][i]].second--;
                if (posClauseMeta[negetiveClauses[var][i]].second == 0) {
                    doPos = false;
                }
            }
            if (doPos && doNeg) {
                return (doPll(posClauseMeta,modelPos)||doPll(negClauseMeta,modelNeg));
            }
            else if (doPos) {
                return doPll(posClauseMeta,modelPos);
            }
            else if (doNeg) {
                return doPll(negClauseMeta,modelNeg);
            }
            else {
                return false;
            }
        }
        else {
            continue;
        }
    }

}

int main () {
    vector<pair<int,int>> clauseMetaData;
    getInput(clauseMetaData);
    unitProp(clauseMetaData, finalModel);
    if (doPll(clauseMetaData,finalModel)) {
        cout<<"TRUE\n";
        for (int i=1; i<finalModel.size(); i++) {
            cout<<i<<" : "<<finalModel[i]<<endl;
        }
    }
    else {
        cout<<"UNSAT\n";
    }
}