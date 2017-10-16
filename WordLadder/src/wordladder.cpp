#include <iostream>
#include "console.h"
#include "filelib.h"
#include "lexicon.h"
#include "Stack.h"
#include "queue.h"
#include "strlib.h"

using namespace std;

void print_qStack(Queue<Stack<string> > &qst);
void print_Stack(Stack<string>  &st);
bool contain_stack(Stack<string>  &st, string comp);
bool contain_qstack(Queue<Stack<string> >  &qst, string comp);


int main() {
    // TODO: Finish the program!
    //string parameter
    string open_filename;     //filename of image for the processing
    string word1;
    string word2;
    string temp;

    //int temp;
    bool flag_word_check = 1;
    Queue<Stack<string> > wl;
    Stack<string> tempst;
    Stack<string> word_ladder;


    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time." << endl << endl;

    do{
        cout << "Dictionary file name: ";
        cin >> open_filename;
        // if the blank is entered, break the loop and quit
        if(fileExists(open_filename)) break;
        // open the file with filename
        cout << "Unable to open that file. Try again" << endl;
        // if the file exists in the folder, break the loop
        // if the file doesn't exist in the folder, reprompt
    }while(!fileExists(open_filename));
    Lexicon lex(open_filename);
    Lexicon word_search;
    cin.clear();
    cin.ignore(100,'\n');
    do{
        do{
            cout <<endl;
            wl.clear();
            tempst.clear();
            word_ladder.clear();
            word_search.clear();
            flag_word_check = 1;
            cout << "Word 1 (or Enter to quit): ";
            getline(cin, word1);
            // if the blank is entered, break the loop and quit
            if(word1.empty()){
                flag_word_check = 0;
                break;
            }
            cout << "Word 2 (or Enter to quit): ";
            getline(cin, word2);
            // if the blank is entered, break the loop and quit
            if(word2.empty()){

                flag_word_check = 0;
                break;
            }

            if((!lex.contains(word1))||(!lex.contains(word2))){
                cout << "The two words must be found in the dictionary." <<endl;
                flag_word_check = 0;
            }
            if(word1.length() != word2.length()){
                cout << "The two words must be the same length." <<endl;
                flag_word_check = 0;
            }
            if(word1 == word2){
                cout << "The two words must be different." <<endl;
                flag_word_check = 0;
            }
        }while(!flag_word_check);
        if(!((word1.empty())||(word2.empty()))){
            //cout << "Let's Start"<<endl;
            word1 = toLowerCase(word1);
            //cout << word1;
            word2 = toLowerCase(word2);
            //cout << word2;

            //origin.push(word2);
            //temp = origin.pop();
            //cout << temp << endl;
            //wl.enqueue({}})

            //queue of stack initialization
            tempst.push(word1);
            wl.enqueue(tempst);
            tempst.clear();
            //int k = 0;
            //cout << "wl is empty?"<< wl.isEmpty() << endl;
            //dequeue a stack s
            while(!wl.isEmpty()){
                tempst = wl.dequeue();


                for (int i = 0;i<word1.size();i++){
                    for (char ch = 'a'; ch <= 'z'; ch++) {
                        temp = tempst.peek();
                        temp[i] = ch;

                        if((lex.contains(temp))&&(temp.compare(tempst.peek()))){
                            if(!word_search.contains(temp)){
                                word_search.add(temp);
                                //}
                                //cout << i <<"compare test :" << temp <<"&"<<tempst.peek()<< endl;
                                //if(!contain_qstack(wl,temp)){
                                //if(!word_search.contains(temp)){
                                //std::cout <<"new stack item :"<< temp <<" "<<endl;
                                tempst.push(temp);
                                wl.enqueue(tempst);
                                if(!temp.compare(word2)){
                                    word_ladder = tempst;
                                    //cout << "a word found!" <<endl;

                                    break;
                                }
                                else{
                                    tempst.pop();
                                }
                                //}
                            }
                        }
                        else{

                        }
                    }
                    if(!temp.compare(word2)){
                        //cout << "a word found!" <<endl;
                        break;
                    }
                }
                //print_qStack(wl);
                //k ++;
                //cout << k << endl;
                if(!temp.compare(word2)){
                    //cout << "a word found!" <<endl;
                    break;
                }
            }
            if(wl.isEmpty()){
                cout << "No word ladder found from "<< word2 << " back to "<< word1 << "." << endl;
            }
            else{
                cout << "A ladder from "<< word2 << " back to "<< word1 << "." <<endl;
                //print_qStack(wl);
                print_Stack(word_ladder);
            }

        }
    }while(!((word1.empty())||(word2.empty())));

    cout << "Have a nice day." <<endl;
    return 0;

}
void print_qStack(Queue<Stack<string> > &qst){
    Queue<Stack<string> > qst_copy = qst;
    Stack<string> temps;
    int qst_size = qst_copy.size();
    for(int i=0;i<qst_size;i++){
        temps = qst_copy.dequeue();
        cout << "QStack " <<i;
        do{
            //temp = temps.();
            cout << "->" << temps.top();
            temps.pop();
        }while(!temps.isEmpty());
        cout << endl;
    }
}

void print_Stack(Stack<string>  &st){
    while(!st.isEmpty()){

        cout << st.pop() << " ";
    }
    cout <<endl;
}


bool contain_qstack(Queue<Stack<string> >  &qst, string comp){

    Queue<Stack<string> > qst_copy = qst;
    Stack<string> st_temp;
    while(!qst_copy.isEmpty()){
        st_temp = qst_copy.dequeue();
        if(contain_stack(st_temp,comp)){
            return true;
            break;
        }
    }
    return false;
}
bool contain_stack(Stack<string>  &st, string comp){

    Stack<string> st_copy = st;

    while(!st_copy.isEmpty()){
        //cout << "stack_search" << st_copy.peek()<<endl;
        if(!comp.compare(st_copy.peek())){
            //cout << "do not add this item " << comp<<endl;
            return true;
        }
        else{
            st_copy.pop();
        }
    }
    return 0;
}
