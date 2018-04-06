#include <iostream>
#include "pa3.h"
#include <fstream>
#include "vector"

using namespace std;

vector <string> tokens; // stores all tokens that are found in input file for analysis
vector <string> keywords; // stores keyword tokens that are found
vector <string> identifiers; //stores identifiers that are found
vector <string> constants; // stores constants that are found
vector <string> operators; // stores operators that are found
vector <string> delimiters; //stores delimiters that are found
vector <string> syntaxErrors; // stores syntax errors that are found
Stack callStack; // stores BEGIN and END keywords that are found to track depth of nester loops

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

//returns data stored in top of stack then deletes top item from the Stack
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

    return data;
}

// returns number of elements in stack
int Stack::getSize() {
    return size;
}


/*
 * Stack methods end
 */


/*
 * main methods begin
 */

// takes a string containing code input and stores each token into it's own element of a vector
void findTokens(string code) {
    string lastWord = ""; // temp variable that stores contents of currWord when a new token is encountered
    string currWord = ""; //Stores string of current token until a new token is encountered

    // iterates through each character of a string of code
    for (int i = 0; i < (int)code.size(); i++){
        // checks if element is an operator, delimiter, or parenthesis. If it is one of these, adds contents of currWord string to vector of tokens
        if (code.at(i) == '(' || code.at(i) == ')' || code.at(i) == '+' || code.at(i) == '-' || code.at(i) == '*' || code.at(i) == '/' || code.at(i) == '='
            || code.at(i) == ',' || code.at(i) == ';' ) {
            lastWord = currWord;
            currWord = code.at(i);

            // if statement prevents empty string from being placed into token vector
            if (lastWord != "") {
                tokens.push_back(lastWord);
            }

            // special case for preventing "+" from being added to token list when token is actually "++"
            if (code.at(i + 1) != '+') {
                // if statement prevents empty string from being placed into token vector
                if (currWord != "") {
                    tokens.push_back(currWord);
                }
            }

            // special case for preventing "+" from being added to token list when token is actually "++"
            else {
                tokens.push_back("++");
                i++;
            }

            // resets currWord and lastWord to prepare them to store next tokens
            currWord = "";
            lastWord = "";
        }

        // tests if characer is lower case. If it is, concatinates it onto currWord sting to eventually be stored in token vector as identifier.
        else if (isLowerCaseLetter(code.at(i))) {
            currWord += code.at(i);

        }

        // checks if character is new line. If it is, stores contents of currWord on tokens vector
        else if (code.at(i) == '\n') {
            if (currWord != "") {
                tokens.push_back(currWord);
            }

            // resets currWord to prepare it to store next token
            currWord = "";
        }
        // checks if current character is white space. If it is, adds contents of currWord to tokens vector
        else if (isWhiteSpace(code.at(i))) {
            if (currWord != "") {
                tokens.push_back(currWord);
            }

            // resets currWord to prepare it to store next token
            currWord = "";
        }

        // if character reaches this statement, it must be a capitol letter. stores character to currWord to eventually be stored into token vector
        else {
            currWord += code.at(i);
        }
    }
}

// method that returns true if passed in characer is white space, false otherwise
bool isWhiteSpace(char a) {
    const int asciiVal = (int) a;
    if (asciiVal == 32) {
        return true;
    }

    else {
        return false;
    }
}

// method that returns true if ascii value of passed in character is within ascii range for lowercase letters, false otherwise
bool isLowerCaseLetter(char b) {
    const int asciiVal = (int) b;
    if ((asciiVal > 96) && (asciiVal < 123)){
        return true;
    }

    else {
        return false;
    }
}

// returns true if passed string is "+", "-", "*", "/", or "++". False otherwise.
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

//returns true if passed in string is "FOR", "BEGIN", or "END". returns false otherwise
bool isKeyword(string str) {
    if (str == "FOR" || str == "BEGIN" || str == "END"){
        return true;
    }

    else {
        return false;
    }
}

//returns true if passed in character is "," or ";", false otherwise.
bool isDelimiter(char d) {
    if (d == ';'){
        return true;
    }

    if (d == ',') {
        return true;
    }

    return false;
}

//iterates through vector array of tokens adding them to appropriate categories (keywords, operaters, etc...)
int compiler(int i) {
    int beginOrEndCounter = 0;
    bool addElement = true;
    /*
     * FOR keyword branch start
     */
    if (tokens[i] == "FOR") {
        //keywords.push_back(tokens[i]);
        if (tokens[i + 1] != "("){
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

    //Adds misspelled keywords to syntax errors list
    if (isupper(tokens[i].at(0)) && !isKeyword(tokens[i])){
        for (int j = 0; j < (int) keywords.size(); j++){
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
        for (int j = 0; j < (int)keywords.size(); j++){
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
        for (int j = 0; j < (int)identifiers.size(); j++){
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
        for (int j = 0; j < (int)constants.size(); j++) {
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
        for (int j = 0; j < (int)operators.size(); j++) {
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
        for (int j = 0; j < (int)delimiters.size(); j++) {
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
    const int NUM_STACK_ELEMENTS = callStack.getSize();
    string tempCallStack[NUM_STACK_ELEMENTS];

    for (int i = 0; i < NUM_STACK_ELEMENTS; i++){
        tempCallStack[i] = callStack.pop();
    }
    for (int i = 0; i < NUM_STACK_ELEMENTS; i++) {
        if (tempCallStack[i] == "END") {
            countBegins = true;
            if (loopCounter > numLoops) {
                numLoops = loopCounter;
            }
            loopCounter = 0;
        }

        if (tempCallStack[i] == "BEGIN"){
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
    string inputFileName;

    cout << "Please enter the name of the input file:";

    cin >> inputFileName;


    /*
     * write file to tokens vector
     */

    ifstream infile(inputFileName, ios::in); // test.text must be located in "C:\Users\Brock\CLionProjects\projectName\cmake-build-debug"

    if (infile.is_open()){
        while (getline(infile, str)) { // returns null when it reaches an empty line in the file
            codeVector.push_back(str + "\n"); //write file to a vector of strings
        }
        infile.close();
    }

    else {
        cout << "No input file available. Ensure filename matches input.";
        return 0;
    }

    /*
     * end writing file to tokens vector
     */

    for (int i = 0; i < (int)codeVector.size(); i++){
        code += codeVector[i];
    }

    findTokens(code);

    for (int i = 0; i < (int)tokens.size(); i++) {
        beginWithoutEnd += compiler(i);
    }

    if (beginWithoutEnd > 0) {
        syntaxErrors.push_back("END");
    }

    /*while (callStack.getSize() > 0) //FIXME delete before submission
    {
        cout << "\n" << callStack.pop();
    }*/

    cout << endl << "The depth of nested loop(s) is " << findDepthOfNestedLoops();

    cout << "\n" << "\n" << "Keywords: ";
    for (int i = 0; i < (int)keywords.size(); i++){
        cout << keywords[i] << " ";
    }

    cout << "\n " << "Identifier: ";
    for (int i = 0; i < (int)identifiers.size(); i++){
        cout << identifiers[i] << " ";
    }

    cout << "\n " << "Constant: ";
    for (int i = 0; i < (int)constants.size(); i++){
        cout << constants[i] << " ";
    }

    cout << "\n " << "Operators: ";
    for (int i = 0; i < (int)operators.size(); i++){
        cout << operators[i] << " ";
    }

    cout << "\n " << "Delimiter: ";
    for (int i = 0; i < (int)delimiters.size(); i++){
        cout << delimiters[i] << " ";
    }

    cout << endl;
    cout << "\n " << "Syntax Error(s): ";
    if (syntaxErrors.empty()){
        cout << "N/A";
    }

    else {
        for (int i = 0; i < (int)syntaxErrors.size(); i++) {
            cout << syntaxErrors[i] << " ";
        }
    }

    /*cout << "\n"; //FIXME delete before submission
    for (int i = 0; i < (int)tokens.size(); i++) {
        cout << tokens[i] << "\n";
    }*/

    return 0;
}


