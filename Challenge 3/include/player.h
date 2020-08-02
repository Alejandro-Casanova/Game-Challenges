#ifndef PLAYER_H
#define PLAYER_H

class player
{
    public:
        player();
        player(const int &rowVal, const int &colVal);

        int getRowPosition() const;
        int getColPosition() const;

    private:
        int rowPosition, colPosition;

        void setPosition(const int &rowVal, const int &colVal);

        friend class map;

};

#endif // PLAYER_H
