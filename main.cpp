#include "triang.h"

int main(int argc, char* argv[]) {
    try {
        Triang tri(argc, argv);
        tri.getOption();
        tri.createPoly();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
