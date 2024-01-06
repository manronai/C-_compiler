/*
id: 190104128
group: C2
online : 02
date: 20-dec-22
*/

#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include <iomanip>
#include<regex>
using namespace std;
////////////
// symbol tuple object

class symbol {
    public:
    int sid;
    string name=" ";
    string idtype=" ";
    string dtype=" ";
    string value=" ";
    string scope=" ";
    symbol *address;
    void setattribute(string attName, string value)
    {
        
        if( attName=="name")
        {
            name = value;
        }
        if( attName=="idtype")
        {
            idtype = value;
        }
        if( attName=="dtype")
        {
            dtype = value;
        }
        if( attName=="value")
        {
            this->value = value;
        }
        if( attName=="scope")
        {
            scope = value;
        }
    }
};
vector<symbol> objs;
//////////
int c = 0;
vector<vector<string>> stringList;
string removeComments(string prgm)
{
int n = prgm.length();
string res;

bool s_cmt = false;
bool m_cmt = false;

// Traverse the given program
for (int i=0; i<n; i++)
{
// If single line comment flag is on, then check for end of it
if (s_cmt == true && prgm[i] == '\n')
s_cmt = false;
// If multiple line comment is on, then check for end of it
else if (m_cmt == true && prgm[i] == '*' && prgm[i+1] == '/')
m_cmt = false, i++;
// If this character is in a comment, ignore it
else if (s_cmt || m_cmt)
continue;
else if (prgm[i] == '/' && prgm[i+1] == '/')
s_cmt = true, i++;
else if (prgm[i] == '/' && prgm[i+1] == '*')
m_cmt = true, i++;
else res += prgm[i];
}
return res;
}
string spaceless(string str){

//declare an empty string
string nstr;

for(int i=0; i<str.length(); ){

if(str[i] == ' ' || str[i] == '\n'|| str[i] == 9){

if(i==0 || i==str.length()-1){
i++;
continue;
}

while(str[i+1] == ' ' || str[i] == '\n'|| str[i] == 9)
i++;
}
//concatenate the character to the new string
nstr += str[i++];
}
return nstr;
}
bool numberCheck(string s){
    if(regex_match(s, regex("^[1-9]\\d*(\\.\\d+)?$")))
    return true;
    return false;
}
bool validIdentifier(string s){
   if(regex_match(s, regex("^([a-zA-Z_$][a-zA-Z\\d_$]*)$"))){ 
    //if(regex_match(s, regex("((_)|([a-z])|([A-Z]))((_)*|([a-z])*|([A-Z])*|([0-9])*)*"))){
        return true;
    }
    return false;
}
string check(string s){
if(s=="#include" || s=="void"|| s=="include" || s== "int" || s== "float"|| s== "endl" || s=="cout"||
s=="double"|| s=="return")
{
return "keyword";
}
else if(s=="+" || s=="-"|| s=="/" || s== "="|| s=="!")
{
return "operator";
}
else if(s=="}"|| s=="{"|| s=="]"|| s=="["|| s==")"|| s=="(" || s==","|| s==";")
{
return "delimiter";
}
else if(s == "kdj")
{
return "invalidIdentityfier";
}else if(numberCheck(s)){
    c++;
 return "number";
}
else
{if(validIdentifier(s))
return "indentifier";
}
return "Error";
}
// Driver program to test above functions
string splitprint(string S){
string T; // declare string variables
string str;

stringstream X(S);
while (getline(X, T, ' ')) {

string keyword = check(T);
str += "[" + keyword + " "+ T + "] ";
vector<string> ss{keyword, T};
stringList.push_back(ss);
}
return str;
}
bool isPunctuator(char ch) //check if the givencharacter is a punctuator or not
{
if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
ch == '&' || ch == '|')
{
return true;
}
return false;
}
string putspace(string ss){
string s;
for(int i = 0; i< ss.length(); i++){
if(isPunctuator(ss[i])) {
s += " ";
s += ss[i];
s += " ";
continue;
}else{
s += ss[i];
}
}
return s;
}
///////////
void display(){
    cout<< "id"<<setw(10)<<"name"<<setw(10)<<"idtype"<<setw(10)<<"dtype"<<setw(10)<<"value"<<setw(10)<<"scope"<<endl;
    for(symbol i : objs){
        cout<<i.sid<<setw(10)<<i.name<<setw(10)<<i.idtype<<setw(10)<<i.dtype<<setw(10)<<i.value<<setw(10)<<i.scope<<endl;
    }
}
///////////
////////
bool symbolExist(string name){
    for(auto i : objs){
        if(i.name == name){
            return true;
        }
    }
    return false;
}
///////
int main()
{
    string myText;
//ofstream myfile("ldk.txt");
// Read from the text file
//ifstream MyReadFile("filename.txt");
string prgm = " /* Test program */ \n"

"void print(int var){\n"
"double localVar = var\n"
"}\n"
"int fa= 5;"
"int main() \n"
" { \n"
" // variable declaration \n"
" int a = 3; \n"
" float b = 3..3; \n"
" float c = 3.3; \n"
" /* This is a test \n"
" multiline \n"
" comment for \n"
" testing */ \n"
" a = b + c; \n"
" return 0;} \n";
string cmntLess = removeComments(prgm);
cmntLess = putspace(cmntLess);
//cout<< cmntLess<<endl;
string spcLess = spaceless(cmntLess);
//cout<< spcLess;
spcLess = spaceless(spcLess);
cout<< spcLess<<endl<<endl;
spcLess = splitprint(spcLess);
cout<<endl<<spcLess<<endl<<endl<<endl;
cout<< "num of numeric: "<< c<<endl;
vector<string> stack;
cout<<endl;
int serial = 1;
int flagScope = 0;
int flagScope2 = 0;
string currentScope = "global";
for(int i=0;i<stringList.size();i++){
    if(stringList[i][1] == "{" && flagScope2 == 1)
    {
        stack.push_back("{");
        flagScope = 1;
    }
    if(stringList[i][1] == "}" && flagScope == 1)
    {
        stack.pop_back();
        flagScope = 0;
    }
    if(stack.empty() && flagScope == 0){
        currentScope = "global";
        flagScope = 0;
        flagScope2 = 0;
    }
    if(stringList[i][0]=="indentifier" && !symbolExist(stringList[i][1]))
    {   
        symbol obj;
        obj.sid = serial;
        serial++;
        obj.name = stringList[i][1];
        if(i-1>-1 && stringList[i-1][0]=="keyword" && i+1<stringList.size() && stringList[i+1][1] != "(" ){
            obj.dtype= stringList[i-1][1];
            if(stringList[i+1][1]=="=" && i+2<stringList.size()){
                //!symbolExist(stringList[i+2][1]) checks "var = function();"
                if(!symbolExist(stringList[i+2][1]) && (stringList[i+2][0]== "number" || stringList[i+2][0]== "string"))
                        obj.value = stringList[i+2][1];
                obj.idtype = "variable";
                obj.scope = currentScope;
            }else{
                obj.idtype = "variable";
                obj.scope = currentScope;
            }
        }
        if (i-1>-1 && stringList[i-1][0]=="keyword" && i+1<stringList.size() && stringList[i+1][1] == "(" ){
            obj.idtype = "function";
            obj.dtype = stringList[i-1][1];
            currentScope = stringList[i][1];
            obj.scope = stringList[i][1];
            flagScope2 = 1;
        }
        //if(i-1>-1 && stringList[i-1][0] == "keyword" && i+1<stringList.size() && stringList[i+1][1])
        objs.push_back(obj);
    }
}
display();
return 0;
}
