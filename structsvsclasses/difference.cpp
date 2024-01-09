struct Coordinates {
    int x;
    int y;
    Coordinates() : x(x), y(y) {}
};

class Coords {
    int x;
    int y;
public:
    Coords() : x(x), y(y) {}
    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

/*
 * DIFFERENCES
 * 1. Structs' fields public by default, classes are private
 * 2. Structs represent PASSIVE data, which should be accessed directly (no getters/setters)
 * 3. Methods = don't provide behavior but set data
 * 4.
 */