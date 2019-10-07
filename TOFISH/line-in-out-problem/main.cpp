//输入格式
//输入共有N+M+1行，第一行是整数N和整数M。
//
//接下来的N+M行中，共有N行有四个整数代表入队，M行有两个整数代表出队。
//
//入队的N行中每行的第一个整数为1，代表入队，第二个整数为入队同学的编号i，第三个整数为已在队列中同学的编号j，第四个整数若为0则代表同学i站在同学j左侧，若为1则代表同学i站在同学j右侧。特别地，当队列为空时，第三个整数与第四个整数没有意义，为保持输入格式一致，将这两个数设为-1。
//
//出队的M行中，第一个整数为0，代表出队，第二个整数为出队同学的编号。
//输出格式
//从左到右的N-M位同学的编号，以-1结尾，共N-M+1个整数。
//

//input:
//5 1
//1 4 -1 -1
//1 2 4 1
//0 4
//1 5 2 0
//1 1 5 1
//1 3 2 1

//output
//5 1 2 3 -1

#include <cstdio>

struct person {
    int left;
    int right;
};

struct person line[500000];

int main(int argc, char **argv) {

    // use scanf via description
    int n, m;
    scanf("%d %d", &n, &m);

    const int total_lines = n + m;
    const int final_students = n - m;

    int head = -1;
    for (int i = 0; i < total_lines; ++i) {
        int type, id;
        scanf("%d %d", &type, &id);
        switch (type) {
            case 1:
                //in
                int target_id, left_right_mark;
                scanf("%d %d", &target_id, &left_right_mark);
                if (target_id != -1) {
                    switch (left_right_mark) {
                        case 0:
                            //left
                            if (line[target_id].left != -1) {
                                line[line[target_id].left].right = id;
                            } else {
                                head = id;
                            }
                            line[id].left = line[target_id].left;
                            line[id].right = target_id;
                            line[target_id].left = id;
                            break;
                        case 1:
                            //right
                            if (line[target_id].right != -1) {
                                line[line[target_id].right].left = id;
                            }
                            line[id].right = line[target_id].right;
                            line[id].left = target_id;
                            line[target_id].right = id;
                            break;
                    }
                } else {
                    line[id].left = -1;
                    line[id].right = -1;
                    head = id;
                }
                break;
            case 0:
                //out
                if (line[id].left != -1) {
                    line[line[id].left].right = line[id].right;
                } else {
                    head = line[id].right;
                }
                if (line[id].right != -1) {
                    line[line[id].right].left = line[id].left;
                }
                break;
        }
    }

    while (head != -1) {
        printf("%d ", head);
        head = line[head].right;
    }
    printf("-1");

    return 0;
}