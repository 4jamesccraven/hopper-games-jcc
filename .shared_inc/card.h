    #pragma once
    #ifndef CARD_H
    #define CARD_H

    #include<iostream>
    #include<vector>
    #include<random>
    #include<algorithm>

    namespace cards{
        enum spanish_suit_type {Coins = 1, Swords = 2, Cups = 3, Rods = 4};
        enum french_suit_type {Hearts = 1, Diamonds = 2, Spades = 3, Clubs = 4};

        template<typename T>
        struct card {
            T suit;
            unsigned int rank;
        };

        template<typename T>
        std::ostream& operator<<(std::ostream& os, card<T> c);

        template<typename T>
        class deck {
        public:
            deck();
            void shuffle();
            void print(std::ostream& os);
            card<T> deal();
        protected:
            std::vector<card<T>> internal_deck_;
            std::vector<card<T>> used_;
            unsigned int size_;
        };


        template<>
        inline cards::deck<cards::spanish_suit_type>::deck() {
            size_ = 40;
            internal_deck_.resize(size_);
            used_.resize(size_);
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

        template <typename T>
        inline void deck<T>::shuffle() {
            std::random_device r;
            std::mt19937 gen(r());
            std::shuffle(internal_deck_.begin(), internal_deck_.end(), gen);
        }

        template <typename T>
        inline void deck<T>::print(std::ostream &os) {
            for (auto card : internal_deck_) {
                os << card << std::endl;
            }
        }

        template <typename T>
        inline card<T> deck<T>::deal() {
            card<T> dealt = internal_deck_.back();
            internal_deck_.pop_back();
            used_.push_back(dealt);
            return dealt;
        }

        template<>
        inline cards::deck<cards::french_suit_type>::deck() {
            size_ = 52;
            internal_deck_.resize(size_);
            used_.resize(size_);
            unsigned int index = 0;
            std::for_each(internal_deck_.begin(), internal_deck_.end(), [&index](card<french_suit_type>& c){
                unsigned int rank = (index % 13) + 1;
                unsigned int suit = (index / 13) + 1;

                c.rank = rank;
                c.suit = static_cast<french_suit_type>(suit);
                index++;
            });
        }

        template <typename T>
        std::ostream &operator<<(std::ostream &os, card<T> c) {
            os << c.rank << " of " << c.suit;
        }
    }

#endif