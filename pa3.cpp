#include <iostream>
#include "pa3.h"
#include <fstream>
#include "vector"

using namespace std;

vector <string> tokens;
vector <string> keywords;
vector <string> identifiers;
vector <string> constants;
vector <string> operators;
vector <string> delimiters;
vector <string> syntaxErrors;
Stack callStack;

/*
 * Stack methods start
 */

//Stack constructor
Stack::Stack() {
    head = nullptr;       // variable for first node in Stack
    tail = nullptr;       //variable for last node in Stack
    size = 0;             // keeps track of size of Stack
}

//method for adding new nodes to Stack
void Stack::push(string _data) {
    node *temp = new node;      // creates a space in memeory for new Node
    temp -> data = _data;      // assigns passed in string to data section of new node
    temp -> next = nullptr;     //initializes the next link to null

    // statement triggered when adding first node, sets head and tail to only node in Stack
    if (head == nullptr) {
        head = temp;
        tail = temp;
    }

        //adds data to current tail and sets tail to next node
    else {
        tail -> next = temp;
        tail = tail -> next;
    }

    size++;
}

//returns data stored in tail then deletes tail it from the Stack
string Stack::pop() { //FIXME: crashes program when called with no nodes in the stack
    node *temp = head;
    string data = tail->data;

    for (int i = 0; i < size; i++) {
        if (temp->next == tail || head == tail) {
            delete tail;
            tail = temp;
            size--;
            return data;
        }

        temp = temp->next;
    }
}

int Stack::getSize() {
    return size;
}


/*
 * Stack methods end
 */




/*
 * main methods begin
 */


void findTokens(string code) {
    string lastWord = "";
    string currWord = "";
    //vector <string> tokens; //FIXME extra vector created for debugging because debugger can't track global variables.
    for (int i = 0; i< code.size(); i++){
        if (code.at(i) == '(' || code.at(i) == ')' || code.at(i) == '+' || code.at(i) == '-' || code.at(i) == '*' || code.at(i) == '/' || code.at(i) == '='
               || code.at(i) == ',' || code.at(i) == ';' ) {
            lastWord = currWord;
            currWord = code.at(i);
            if (lastWord != "") {
                tokens.push_back(lastWord);
            }
            if (code.at(i + 1) != '+') {
                if (currWord != "") {
                    tokens.push_back(currWord);
                }
            }

            else {
                tokens.push_back("++");
                i++;
            }
            currWord = "";
            lastWord = "";
        }

        else if (isLowerCaseLetter(code.at(i))) {
            currWord += code.at(i);

        }

        else if (code.at(i) == '\n') {
            if (currWord != "") {
                tokens.push_back(currWord);
            }
            currWord = "";
        }

        else if (isWhiteSpace(code.at(i))) {
            if (currWord != "") {
                tokens.push_back(currWord);
            }
            currWord = "";
        }

        else {
            currWord += code.at(i);
        }
    }
}

bool isWhiteSpace(char a) {
    const int asciiVal = (int) a;
    if (asciiVal == 32) {
        return true;
    }

    else {
        return false;
    }
}

bool isLowerCaseLetter(char b) {
    const int asciiVal = (int) b;
    if ((asciiVal > 96) && (asciiVal < 123)){
        return true;
    }

    else {
        return false;
    }
}

bool isOperator(string c) {
    if (c == "+"){
        return true;
    }

    if (c == "-") {
        return true;
    }

    if (c == "*") {
        return true;
    }

    if (c == "/"){
        return true;
    }

    if (c == "="){
        return true;
    }

    if (c == "++"){
        return true;
    }

    return false;
}

bool isKeyword(string str) {
    if (str == "FOR" || str == "BEGIN" || str == "END"){
        return true;
    }

    else {
        return false;
    }
}

bool isDelimiter(char d) {
    if (d == ';'){
        return true;
    }

    if (d == ',') {
        return true;
    }

    return false;
}

int compiler(int i) {
    int beginOrEndCounter = 0;
    bool addElement = true;
    /*
     * FOR keyword branch start
     */
    if (tokens[i] == "FOR") {
        //keywords.push_back(tokens[i]);
        if (tokens[i + 1] != "("){
            cout << "inside (";
            syntaxErrors.push_back(tokens[i+1]);
        }

        if (tokens[i + 1] == "(") {
            if (isLowerCaseLetter(tokens[i + 2].at(0))) {
                //identifiers.push_back(tokens[i + 2]);
            }

            else {
                syntaxErrors.push_back(tokens[i + 2]);
            }
        }

        if (isLowerCaseLetter(tokens[i + 2].at(0))) {
            if (tokens[i + 3] == ","){
               // delimiters.push_back(tokens[i + 3]);
            }

            else {
                syntaxErrors.push_back(tokens[i + 3]);
            }
        }

        if (tokens[i + 3] == ",") {
            if (isdigit(tokens[i + 4].at(0))) {
                //constants.push_back(tokens[i + 4]);
            }

            else {
                syntaxErrors.push_back(tokens[i + 4]);
            }
        }

        if (isdigit(tokens[i + 4].at(0))){
            if (tokens[i + 5] == ",") {
               // delimiters.push_back(tokens[i + 5]);
            }

            else {
                syntaxErrors.push_back(tokens[i + 5]);
            }
        }

        if (tokens[i + 5] == ",") {
            if (tokens[i + 6] == "++"){
               // operators.push_back(tokens[i + 6]);
            }

            else {
                syntaxErrors.push_back(tokens[i + 6]);
            }
        }

        if (tokens[i + 6] == "++") {
            if (tokens[i + 7] != ")") {
                syntaxErrors.push_back(tokens[i + 7]);
            }
        }

        if (tokens[i + 7] == ")") {
            if (tokens[i + 8] == "BEGIN"){
                //keywords.push_back(tokens[i + 8]);
            }

            else {
                syntaxErrors.push_back(tokens[i + 8]);
            }
        }
    }
    /*
     * FOR keyword branch end
     */

    //Adds mispelled keywords to syntax errors list
    if (isupper(tokens[i].at(0)) && !isKeyword(tokens[i])){
        for (int j = 0; j < keywords.size(); j++){
            if (syntaxErrors[j] == tokens[i]) {
                addElement = false;
            }
        }

        if (addElement) {
            syntaxErrors.push_back(tokens[i]);
        }
    }

    //adds keywords to keywords list
    if (isKeyword(tokens[i])) {
        for (int j = 0; j < keywords.size(); j++){
            if (keywords[j] == tokens[i]) {
                addElement = false;
            }
        }

        if (addElement) {
            keywords.push_back(tokens[i]);
        }
    }

    // adds all identifiers to list
    if (isLowerCaseLetter(tokens[i].at(0))) {
        for (int j = 0; j < identifiers.size(); j++){
            if (identifiers[j] == tokens[i]) {
                addElement = false;
            }
        }

        if (addElement) {
            identifiers.push_back(tokens[i]);
        }
    }

    //adds all constants to list
    if (isdigit(tokens[i].at(0))) {
        for (int j = 0; j < constants.size(); j++) {
            if (constants[j] == tokens[i]) {
                addElement = false;
            }
        }

        if (addElement) {
            constants.push_back(tokens[i]);
        }
    }

    //Adds all operators to operator list
    if (isOperator(tokens[i])) {
        for (int j = 0; j < operators.size(); j++) {
            if (operators[j] == tokens[i]) {
                addElement = false;
            }
        }

        if (addElement) {
            operators.push_back(tokens[i]);
        }
    }

    //adds all delimiters to delimiter list
    if (isDelimiter(tokens[i].at(0))) {
        for (int j = 0; j < delimiters.size(); j++) {
            if (delimiters[j] == tokens[i]) {
                addElement = false;
            }
        }

        if (addElement) {
            delimiters.push_back(tokens[i]);
        }
    }

    addElement = true;

    /*
     * Checks for begin without end
     */
    if (tokens[i] == "BEGIN") {
        beginOrEndCounter = 1;
        callStack.push(tokens[i]);
    }

    if (tokens[i] == "END") {
        beginOrEndCounter = -1;
        callStack.push(tokens[i]);
    }
    /*
     *
     */
    return beginOrEndCounter;
}

int findDepthOfNestedLoops() {
    int loopCounter = 0;
    int numLoops = 0;
    bool countBegins = false;

    while(callStack.getSize() > 0) {

        cout << "loopCounter" << endl;//FIXME delete before submission

        if (callStack.pop() == "END") {
            countBegins = true;
            if (loopCounter > numLoops) {
                numLoops = loopCounter;
            }
            loopCounter = 0;
        }

        if (callStack.pop() == "BEGIN"){
            if (countBegins){
                loopCounter++;
            }
        }
    }

    if (loopCounter > numLoops) {
        numLoops = loopCounter;
    }

    return numLoops;
}


/*
 * main methods end
 */

int main() {
    string str;
    string code = "";
    vector <string> codeVector;
    int beginWithoutEnd = 0;


    /*
     * write file to tokens vector
     */

    ifstream infile("code.txt", ios::in); // test.text must be located in "C:\Users\Brock\CLionProjects\projectName\cmake-build-debug"

    if (infile.is_open()){
        while (getline(infile, str)) { // returns null when it reaches an empty line in the file
            codeVector.push_back(str + "\n"); //write file to a vector of strings
        }
        infile.close();
    }

    else {
        cout << "no input file available";
    }

    /*
     * end writing file to tokens vector
     */

    for (int i = 0; i < codeVector.size(); i++){
        code += codeVector[i];
    }

    findTokens(code);

    for (int i = 0; i < tokens.size(); i++) {
        beginWithoutEnd += compiler(i);
    }

    if (beginWithoutEnd > 0) {
        syntaxErrors.push_back("END");
    }

    /*while (callStack.getSize() > 0) //FIXME delete before submission
    {
        cout << "\n" << callStack.pop();
    }*/

    cout << "The depth of nested loop(s) is " << findDepthOfNestedLoops();

    cout << "\n" << "Keywords: ";
    for (int i = 0; i < keywords.size(); i++){
        cout << keywords[i] << " ";
    }

    cout << "\n " << "Identifier: ";
    for (int i = 0; i < identifiers.size(); i++){
        cout << identifiers[i] << " ";
    }

    cout << "\n " << "Constant: ";
    for (int i = 0; i < constants.size(); i++){
        cout << constants[i] << " ";
    }

    cout << "\n " << "Operators: ";
    for (int i = 0; i < operators.size(); i++){
        cout << operators[i] << " ";
    }

    cout << "\n " << "Delimiter: ";
    for (int i = 0; i < delimiters.size(); i++){
        cout << delimiters[i] << " ";
    }

    cout << endl;
    cout << "\n " << "Syntax Error(s): ";
    if (syntaxErrors.empty()){
        cout << "N/A";
    }

    else {
        for (int i = 0; i < syntaxErrors.size(); i++) {
            cout << syntaxErrors[i] << " ";
        }
    }

    cout << "\n"; //FIXME delete before submission
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << "\n";
    }

    return 0;
}


