    #pragma once
    #ifndef CARD_H
    #define CARD_H

    #include<iostream>
    #include<string>
    #include<vector>
    #include<ctime>
    #include<random>
    #include<algorithm>

    namespace cards{
        //card suits
        enum spanish_suit_type {Coins = 1, Swords = 2, Cups = 3, Rods = 4};
        enum french_suit_type {Hearts = 1, Diamonds = 2, Spades = 3, Clubs = 4};

        //card
        template<typename T>
        struct card {
            T suit;
            unsigned int rank;
        };

        template<typename T>
        std::ostream& operator<<(std::ostream& os, card<T> c);

        //deck
        template<typename T>
        class deck {
        public:
            constexpr deck();                   //constructor

            void shuffle();                     //deck manipulation
            card<T> deal();
            void returnUsed();

            void print(std::ostream& os);       //print methods
            void printUsed(std::ostream& os);
        protected:
            std::vector<card<T>> internal_deck_;
            std::vector<card<T>> used_;
        };

        //***---DECK---***//
        //constructors
        template<>
        inline cards::deck<cards::spanish_suit_type>::deck() {
            internal_deck_.resize(40);
            unsigned int index = 0;
            std::for_each(internal_deck_.begin(), internal_deck_.end(), [&index](card<spanish_suit_type>& c){
                unsigned int rank = (index % 10) + 1;
                unsigned int suit = (index / 10) + 1;
                if (rank > 7) rank += 2;

                c.rank = rank;
                c.suit = static_cast<spanish_suit_type>(suit);
                index++;
            });
        }

        template<>
        inline cards::deck<cards::french_suit_type>::deck() {
            internal_deck_.resize(52);
            unsigned int index = 0;
            std::for_each(internal_deck_.begin(), internal_deck_.end(), [&index](card<french_suit_type>& c){
                unsigned int rank = (index % 13) + 1;
                unsigned int suit = (index / 13) + 1;

                c.rank = rank;
                c.suit = static_cast<french_suit_type>(suit);
                index++;
            });
        }

        //deck manipulations
        template <typename T>
        inline void deck<T>::shuffle() {
            std::mt19937 gen(std::time(NULL));
            if (!used_.empty()) this->returnUsed();
            std::shuffle(internal_deck_.begin(), internal_deck_.end(), gen);
        }

        template <typename T>
        inline card<T> deck<T>::deal() {
            card<T> dealt = internal_deck_.back();
            internal_deck_.pop_back();
            used_.push_back(dealt);
            return dealt;
        }

        template <typename T>
        inline void deck<T>::returnUsed() {
            while (!used_.empty()) {
                card<T> toMove = used_.back();
                used_.pop_back();
                internal_deck_.push_back(toMove);
            }
            return;
        }

        //print methods
        template <typename T>
        inline void deck<T>::print(std::ostream &os) {
            for (auto card : internal_deck_) {
                os << card << std::endl;
            }
        }


        template <typename T>
        inline void deck<T>::printUsed(std::ostream &os) {
            for (auto card : used_) {
                os << card << std::endl;
            }
        }

        //***---CARD---***//
        //card printing overload
        template <>
        std::ostream &operator<<(std::ostream &os, card<cards::spanish_suit_type> c) {
            std::string rankString;
            std::string suitString;
            switch(static_cast<int>(c.suit)) {
            case 1:
                suitString = "Coins";
                break;
            case 2:
                suitString = "Swords";
                break;
            case 3:
                suitString = "Cups";
                break;
            case 4:
                suitString = "Rods";
                break;
            }
            switch(c.rank){
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                rankString = std::to_string(c.rank);
                break;
            case 10:
                rankString = "Knight";
                break;
            case 11:
                rankString = "Queen";
                break;
            case 12:
                rankString = "King";
                break;
            default:
                rankString = "error";
                break;
            }

            os << rankString << " of " << suitString;
            return os;
        }

        template <>
        std::ostream &operator<<(std::ostream &os, card<cards::french_suit_type> c) {
            std::string rankString;
            std::string suitString;
            switch(static_cast<int>(c.suit)) {
            case 1:
                suitString = "Hearts";
                break;
            case 2:
                suitString = "Diamonds";
                break;
            case 3:
                suitString = "Spades";
                break;
            case 4:
                suitString = "Clubs";
                break;
            }
            switch(c.rank){
            case 1:
                rankString = "Ace";
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                rankString = std::to_string(c.rank);
                break;
            case 11:
                rankString = "Jack";
                break;
            case 12:
                rankString = "Queen";
                break;
            case 13:
                rankString = "King";
                break;
            default:
                rankString = "error";
                break;
            }

            os << rankString << " of " << suitString;
            return os;
        }
    }

#endif