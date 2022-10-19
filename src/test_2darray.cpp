#include "test_2darray.h"

class  Color
{
private:
    int i;
protected:
public:
    Color() {}
    Color(int a, int b, int c) {
        this->i = a;
        this->j = b;
        this->k = c;
    }
    int geti() { return this->i;};
    void print_content() {
        printf("i:%d ", this->i);
        printf("j:%d ", this->j);
        printf("k:%d\n", this->k);
    };

    int getR(){ return i;};

    int j;
    int k;
};

static Color *pmatrix[10][10] {};

void setupColor(int r, int c, int R, int G, int B)
{
    Color *c1 = new Color(R,G,B);
    printf("&c1:%p c1:%p\n", &c1, c1);

    // printf("c1->i %p:%d\n" , &(c1->i), c1->i);
    // printf("c1->j %p:%d\n" , &(c1->j), c1->j);
    // printf("c1->k %p:%d\n" , &(c1->k), c1->k);

    pmatrix[r][c] = c1;
    printf("&pmatrix[%d][%d]:%p pmatrix[%d][%d]:%p\n", r, c, &pmatrix[r][c], r, c, pmatrix[r][c]);

}

int test_2darray()
{
    //static to set it to all 0
    // static Color matrix[10][10];
    // printf("size of matrix: %lu\n", sizeof(matrix));


    printf("size of pmatrix: %lu\n", sizeof(pmatrix));

    // Color *c1 = new Color(1,2,3);

    setupColor(0, 0, 1, 2, 3);
    // printf("&c1:%p c1:%p\n", &c1, c1);

    // printf("c1->i %p:%d\n" , &(c1->i), c1->i);
    // printf("c1->j %p:%d\n" , &(c1->j), c1->j);
    // printf("c1->k %p:%d\n" , &(c1->k), c1->k);

    setupColor(0, 1, 4, 5, 6);

    // Color *c2 = new Color(4,5,6);
    // printf("&c1:%p c2:%p\n", &c2 ,c2);

    // printf("c2->i %p:%d\n" , &(c2->i), c2->i);
    // printf("c2->j %p:%d\n" , &(c2->j), c2->j);
    // printf("c2->k %p:%d\n" , &(c2->k), c2->k);

    // pmatrix[0][0] = c1;
    // printf("&pmatrix[0][0]:%p pmatrix[0][0]:%p\n", &pmatrix[0][0], pmatrix[0][0]);

    printf("pmatrix[0][1] = %d  ", pmatrix[0][1]->getR() );
    // pmatrix[0][1] = c2;
    // printf("&pmatrix[0][1]:%p pmatrix[0][1]:%p\n", &pmatrix[0][1], pmatrix[0][1]);


    printf("size of pmatrix after adding c1: %lu\n", sizeof(pmatrix));
    return 0;
}
