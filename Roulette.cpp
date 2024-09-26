

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

// första funktionen skriver ut välkomstmeddelandet, void används för att det inte returneras ngt "värde"
void display_welcome_message() {
    std::cout << "\nWelcome to the game of roulette! \n"
            "\nRules of the game: \n"
            "\nYou will soon be able to choose a bet, you will be able to bet 100, 300 or 500 kr. \n"
            "\nIf this is the first time playing the game, you will receive 1000 kr to start of with! \n"
            "\nYou will then be able to choose either a number (1-36) or a color (red/black) \n"
            "\nThe wheel will then start turning and a number with a color will be shown \n"
            "\nIf the number you chose is the same as the number the wheel got you will get 10 times the amount of the bet, the same applies if you choose to bet on a color, but you will only get 2 the amount of the bet \n"
            "\nIf the number or color doesnt match the wheels result, you will loose your entire bet! \n"
             "\n\nGet ready.... Set..... GOOOO!!! \n" << std::endl;
}

// funktion som hanterar insatsval
int put_bet() {
    // integer, siffror, antingen 100, 300 eller 500
    int bet;
    // while loop som körs tills giltig insats angivits
    while (true) {
        std::cout << "\nPut in your bet please! (100, 300, 500 kr): ";
        std::cin >> bet;
        // https://www.geeksforgeeks.org/how-to-use-cin-fail-method-in-cpp/
        //cin.fail() kollar ifall insats = ogiltigt och blir isf true
        // om inputen skiljer sig från de godkända värdena 100, 300, 500
        if (std::cin.fail() || (bet != 100 && bet != 300 && bet != 500 )) {
            std::cout << "Invalid bet. Try again!" << std::endl;
            // cin.clear() rensar felstatus på cin
            std::cin.clear();
            // cin.ignore() för att bli av med ogiltig input som användaren angav
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // om insatsen = giltig bryts loopen
        } else {
            break;
        }
    }
    // returnerar den giltiga insatsen
    return bet;
}

//funktion som hanterar ifall användaren vill satsa på färg eller siffra
//uppbyggd på samma sätt som put_bet()
int put_number_or_color () {
    int number_or_color;
    while (true) {
        std::cout << "Do you want to bet on a number (enter 1) or a color (enter 2)? ";
        std::cin >> number_or_color;
        if (std::cin.fail() || (number_or_color != 1 && number_or_color != 2)) {
            std::cout << "Invalid choice. Try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return number_or_color;
}

//funktion som kallas på ifall användaren valt att sattsa på en siffra
//uppbyggd på samma sätt som put_bet()
int put_choosen_number() {
    int chosen_number;
    while (true) {
        std::cout << "You've chosen to bet on a number!\nPlease enter a number between 1-36: ";
        std::cin >> chosen_number;
        if (std::cin.fail() || chosen_number < 1 || chosen_number > 36) {
            std::cout << "Invalid number. Try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return chosen_number;
}

//funktion som kallas på ifall användaren valt att sattsa på en färg
//uppbyggd på samma sätt som put_bet()
int put_choosen_color() {
    int chosen_color;
    while (true) {

        std::cout << "You've chosen to bet on a color!\nPlease either red (enter 1) or black (enter 2): ";
        std::cin >> chosen_color;
        if (std::cin.fail() || (chosen_color != 1 && chosen_color != 2)) {
            std::cout << "Invalid color. Try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return chosen_color;
}

//funktion som kallas på i slutet av spelet och frågar användaren ifall dom vill fortsätta spela eller avbryta
//uppbyggd på samma sätt som put_bet()
char put_continue_game() {
    char continue_game;
    while (true) {
        std::cout << "Do you wanna play again? (y/n): ";
        std::cin >> continue_game;
        //både små och stora bokstäver kollas
        if (std::cin.fail() || (continue_game != 'y' && continue_game != 'n' && continue_game != 'Y' && continue_game != 'N')) {
            std::cout << "Invalid input. Try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return continue_game;
}

//här kommer huvud-funktionen som kallar på de ovanstående funktionerna
int main() {
    // anger vad för datatyp varje variabel innehåller
    int saldo = 1000;
    int bet;
    int number_or_color;
    int chosen_number = 0;
    int chosen_color = 0;
    char continue_game;
    bool play = true;

    // börjar spelet att vid första spelomgången visa välkomstmeddelandet från funktionen display_welcome_message()
    display_welcome_message();

    // initierar slumpgeneratorn till hjulet, utan skulle samma sekvens av "slumpmässiga" tal returneras varje gång programmet körs, dvs ej vara särskilt slumpmässigt
    std::srand(std::time(0));

    // loopas igenom så länge play är true dvs att användaren vill fortsätta spela, och saldot är >= än den lägsta möjliga insatsen dvs 100 kr
    while (play == true && saldo >= 100) {
        // varje omgång visar vi saldot först
        std::cout << "\nYour saldo is now: " << saldo << " kr!" << std::endl;
        // variabeln bet blir return värdet av funktionen put_bet()
        bet = put_bet();
        // om insatsen är större än användarens totala saldo
        if (bet > saldo) {
            std::cout << "You don't have enough cash to bet this amount. Try again!" << std::endl;
            continue;
        }

        std::cout << "\nYou choose to bet: " << bet << " kr!" << std::endl;
        // variabeln number_or_color får return värdet av funktionen put_number_or_color()
        number_or_color = put_number_or_color();
        // om användaren valt 1, dvs satsa på nummer, kallas put_choosen_number() funktionen och return värdet läggs i en variabel
        if (number_or_color == 1) {
            chosen_number = put_choosen_number();
        // annars har användaren angivit 2 dvs satsa på färg, och då kallas ist put_chosen_color() funktionen som läggs i en variabel
        } else {
            chosen_color = put_choosen_color();
        }

        // "Snurra hjulet"
        //genererar ett slumpmässigt heltal, +1 för att få ett resultat mellan 1-36
        int result_number = std::rand() % 36 + 1;
        //jämnt nummer = svart, ojämnt = rött
        std::string result_color = (result_number % 2 == 0) ? "black" : "red";


        std::cout << "The wheel is turning... Result: " << result_number << " (" << result_color << ")" << std::endl;

        // kolla vinst/förlust
        // om användaren satsat på ett nummer och det valda numret = slumpade numret
        if (number_or_color == 1 && chosen_number == result_number) {
            // 10 gåmger insatsen
            int win = bet * 10;
            // vinsten läggs på det tot saldot
            saldo += win;
            std::cout << "Congrats! You've won: " << win << " kr!" << std::endl;
        // om användaren ist valt att satsa på färg och den valda färgen matchar den slumpade färgen (lr snare om det slumpade nummret är jämnt lr ojämnt)
        } else if (number_or_color == 2 && ((chosen_color == 1 && result_color == "red") || (chosen_color == 2 && result_color == "black"))) {
            // 2 gånger insatsen
            int win = bet * 2;
            saldo += win;
            std::cout << "Congrats! You've won: " << win << " kr!" << std::endl;
        // när användarens värde inte matchar det slumpade värdet dvs förlust
        } else {
            saldo -= bet;
            std::cout << "Sorry, no win this time, you've lost: " << bet << " kr." << std::endl;
        }
        // så länge saldot är större eller lika med 100 kr, dvs lägsta insattsen
        if (saldo >= 100) {
            //kallar på funktionen put_continue_game() som läggs i en variabel
            continue_game = put_continue_game();
            // om det returnerade värdet är N/n, har användaren valt att avlsuta spelet, play sätts till falskt och man hoppar då ur while loopen
            if (continue_game == 'n' || continue_game == 'N') {
                play = false;
            }
        // om saldot inte är >= 100. har man ej tillräckligt med pengar, och spelet avbryts automatiskt
        } else {
            std::cout << "You have no money to play with!" << std::endl;
            play = false;
        }

    }
    // while loopen är inte längre sann, vilket innebär att spelet avbrutits och det totala saldot printas ut
    std::cout << "Thank you for playing! You've ended up with: " << saldo << " kr." << std::endl;

    // avslutar main funktionen
    return 0;
}

