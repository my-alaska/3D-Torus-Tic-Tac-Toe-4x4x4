#ifndef TICTACTOE_TORUS_GAME_MAP_H
#define TICTACTOE_TORUS_GAME_MAP_H


class game_map {

public:
    game_map(int size,int length, int start_value);
    ~game_map();
    void clear();
    int ** single_check(int i, int j, int k);
    int ** check();
    int place(int i, int j, int k, int value);
    int ** operator[](int i){
        return map[i];
    }

private:
    int a,b,c;
    int _value;
    int map_size;
    int winning_length;
    int ***map;
    constexpr static int base_size = 13;
    constexpr static int base[13][3] = {
            {1,0,0},{0,1,0},{0,0,1},
            {1,1,0},{1,0,1},{0,1,1},
            {1,-1,0},{1,0,-1},{0,1,-1},
            {1,1,1},{1,1,-1},{1,-1,1},{-1,1,1}
    };
};


#endif //TICTACTOE_TORUS_GAME_MAP_H
