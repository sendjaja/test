#include "test_2darray.h"

class  Color
{
private:
    int R;
    int G;
    int B;
protected:
public:
    Color() {}
    Color(int a, int b, int c) {
        this->R = a;
        this->G = b;
        this->B = c;
    }

    void print_content() {
        printf("R:%d;G:%d;B:%d\n", this->R, this->G, this->B);
    };

    int getR(){ return R;};
    int getG(){ return G;};
    int getB(){ return B;};
};

static Color *pmatrix[10][10] {};

void setupColor(int row, int col, int R, int G, int B)
{
    Color *c = new Color(R,G,B);
    printf("&c:%p c:%p\n", &c, c);

    pmatrix[row][col] = c;
    printf("&pmatrix[%d][%d]:%p pmatrix[%d][%d]:%p\n", row, col, &pmatrix[row][col], row, col, pmatrix[row][col]);
}

int test_2darray()
{
    //static to set it to all 0
    // static Color matrix[10][10];
    // printf("size of matrix: %lu\n", sizeof(matrix));

    printf("Initial size of pmatrix: %lu\n", sizeof(pmatrix));

    setupColor(0, 0, 1, 2, 3);

    setupColor(0, 1, 4, 5, 6);

    printf("pmatrix[0][0] = %d:%d:%d\n",
        pmatrix[0][0]->getR(), pmatrix[0][0]->getG(), pmatrix[0][0]->getB() );

    printf("pmatrix[0][1] = %d:%d:%d\n",
        pmatrix[0][1]->getR(), pmatrix[0][1]->getG(), pmatrix[0][1]->getB() );

    printf("size of pmatrix after adding two Color: %lu\n", sizeof(pmatrix));
    return 0;
}
