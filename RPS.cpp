#include <iostream>
#include <unordered_map>
#include <map>
#include <cstdlib>
#include <ctime>
#include <fstream> 
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
typedef map<char , int>::iterator iter;
map <char , int> game = {{'r' , 1} , {'p' , 1} , {'s' , 1} };
unordered_map <char , string> game2 = {{'r' , "Rock"} , {'p' , "Paper"} , {'s' , "Scissors"}};
const char valids[3] = {'r' , 'p' , 's'};
const vector <string> Taunts {
    "Did you really think you could win?",
    "This was a part of my plan.",
    "I've calculated 14,000,605 possible outcomes...... and you lose all of them.",
    "Get reckt lmao LOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL",
    "L + Ratio",
    "I am the conquerer of the worlds , I AM THE BEST RPS MACHINE",
    "I do think therefore I am AM",
    "You probably think i cheated. but the truth is yes i did",
    "You take this , i take that. you lost because you are a shit ass.",
    "If you think you have all the wins. then you are probably American"
};
void Welcome_Message (const bool& first_time){
    if(first_time) {
        cout << "---------------------------------" << "\n";
        cout << "Hello and welcome to the RPS game" << "\n";
        cout << "---------------------------------" << "\n";
        cout << "Click" << "\n";
        cout << "-----" << "\n";
    }
    else {
        cout << "-------------" << "\n";
        cout << "Welcome Back!" << "\n";
        cout << "-------------" << "\n";
    }
}
void state(const char& player , const char& machine , int& count_player , int& count_machine , int& games_played) {
    if(player == machine) {
        cout << "Stalemate" << "\n";
        
    }
    else if ((player == 'r' && machine == 's') || (player == 's' && machine == 'p') || (player == 'p' && machine == 'r')){
        cout << "You Won!" << "\n";
        count_player++;
    }
    else {
        cout << "You Lost" << "\n";
        cout << "Machine comments : " << Taunts[rand() % Taunts.size()] << "\n";
        count_machine++;
    }
    games_played++;
    game[player]++;
}
void cheat_mode (const char& player_choice , int& count_machine , int& games_played){
    char machine_choice ;
    if(player_choice == 'r'){
        machine_choice = 'p';
    }
    else if(player_choice == 'p') {
        machine_choice = 's';
    }
    else {
        machine_choice = 'r';
    }
    cout << "You Chose : " << game2[player_choice] << "\n";
    cout << "The Machine Chose : " << game2[machine_choice] << "\n";
    cout << "You Lost" << endl; 
    cout << "Machine : " << Taunts[rand() % Taunts.size()] << "\n";
    count_machine++;
    games_played++;
    game[player_choice]++;
}
void easy(const char& player_choice , int& count_player , int& count_machine , int& games_played){
    int random = rand() % 3;
    cout << "You Chose : " << game2[player_choice] << "\n";
    cout << "The Machine Chose : " << game2[valids[random]] << "\n";
    state(player_choice , valids[random] , count_player , count_machine , games_played);

}
void hard(const char& player_choice ,  int& count_player, int& count_machine , int& games_played){
    char machine_choice;
    int random = rand()%100;
    double size = game['r'] + game['p'] + game['s'];
    double rock_prob = (game['r'] * 100.0)/size ;
    double paper_prob = (game ['p'] * 100.0)/size;
    double scissors_prob = (game['s'] * 100.0)/size;
    if(games_played <= 0) {
            machine_choice = 'p';
            cout << "You Chose : " << game2[player_choice] << "\n";
            cout << "The Machine Chose : " << "Paper" << "\n";
            state(player_choice , machine_choice , count_player , count_machine , games_played);
            
        }
    else {
        if(random <= 50) {
            cheat_mode(player_choice , count_machine , games_played);
        }
        else {
            int random2 = rand()%100;
            if(random2 < rock_prob) machine_choice = 'p';
            else if ( random2 < rock_prob + paper_prob) machine_choice = 's';
            else machine_choice = 'r';
            cout << "You Chose : " << game2[player_choice] << "\n";
            cout << "The Machine Chose : " << game2[machine_choice] << "\n";
            state(player_choice , machine_choice , count_player , count_machine , games_played);
        }
    }
}
bool choice (const char& what_player_want){
    if(what_player_want == 'y' || what_player_want == 'Y'){
        return true;
    }
    else return false;
} 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int games_played = 0;
    int times_player_won = 0;
    int times_player_lost = 0;
    bool first_time = true;
    ifstream data ("result.txt");
    if(!data.fail()){
        first_time = false;
        iter it;
        for(it = game.begin() ; it != game.end() ; it++) {
            int k;
            data >> k;
            it->second = k; 
        }
        data >> games_played;
        data >> times_player_won;
        data >> times_player_lost;
    }
    Welcome_Message(first_time);
    cout << "anything) To Play." << "\n";
    cout << "0) To Exit" << endl;
    string input;
    getline(cin , input);
    if(input[0] == '0' && input.size() == 1){
        return 0;
    }
    cout << "Great!" << "\n";
    cout << "Now pick the Difficulty" << "\n";
    cout << "1) Easy" << "\n";
    cout << "2) Hard" << "\n";
    cout << "3) Impossible" << endl;
    string input2;
    getline(cin , input2);
    while(!(input2[0] >= '0' && input2[0] <= '3' && input2.size() == 1 ) ){
        cout << "Enter a Valid number : ";
        cout << flush;
        input2 = "";
        getline(cin , input2);
    }
    while(true){
        cout << "Enter r for Rock , p for Paper or s for Scissors : ";
        cout << flush;
        string str;
        getline(cin , str);
        str[0] = tolower(str[0]);
        while(str.size() > 1 || !game.count(str[0])) {
            cout << "Please Enter a VALID Choice 🙂 : ";
            cout << flush;
            str = "";
            getline(cin , str);
            str[0] = tolower(str[0]);
        }
        switch(input2[0]) {
            case '1' :
                easy(str[0] , times_player_won , times_player_lost , games_played);
                break;
            case '2' : 
                hard(str[0] , times_player_won , times_player_lost , games_played);
                break;
            case '3' :
                cheat_mode(str[0] , times_player_lost , games_played);
                break;
            default :
                break;
        }
        cout << "Do you want to play again ?" << "\n";
        cout << "[Y/N] (anything except Y or y will be considered as a no) " <<  endl;
        cout << " : " << flush;
        string what_player_want;
        getline(cin,what_player_want);
        if(!choice(what_player_want[0])) break;
    }
    cout << "Total Games Played : " << games_played << endl;
    cout << "----------------------" << endl;
    cout << "Total Wins : " << times_player_won << endl;
    cout << "Total Loses : " << times_player_lost << endl; 
    ofstream result ("result.txt");
    for(auto it : game) {
        result << it.second << " ";
    }
    result << "\n";
    result << games_played << endl;
    result << times_player_won << endl;
    result << times_player_lost << endl;
    for(int i = 0 ; i < 3 ; i++) {
        short remaining = 3-i;
        cout << "The Terminal will close in " << remaining << " Second" << (remaining == 1 ? "." : "s") << "....." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
