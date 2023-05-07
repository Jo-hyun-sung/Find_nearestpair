/*
�̸�:������
�й�:202211506 
���α׷� ��:FInd_naerest_pair
���α׷� ��¥:2023.5.07(��)
���α׷� ����: �ֱ��������� ã�� ���α׷� 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

double distance(Point p1, Point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    FILE* inputFile, * outputFile;
    Point* points;
    int numPoints, i, j;
    double minDistance;

    /*�Է� ���� ���� */
    if (fopen_s(&inputFile, "data.txt", "r") != 0) {
        printf("�Է� ������ �� �� �����ϴ�.\n");
        return 1;
    }

    /* ������ ���� �б� */
    if (fscanf_s(inputFile, "%d", &numPoints) != 1) {
        printf("������ ������ ���� �� �����ϴ�.\n");
        fclose(inputFile);
        return 1;
    }

    /* ����Ʈ ������ �迭 ���� �Ҵ� */
    points = (Point*)malloc(numPoints * sizeof(Point));

    /* ����Ʈ ������ �б� */
    for (i = 0; i < numPoints; i++) {
        if (fscanf_s(inputFile, "%d %d", &points[i].x, &points[i].y) != 2) {
            printf("����Ʈ �����͸� ���� �� �����ϴ�.\n");
            fclose(inputFile);
            free(points);
            return 1;
        }
    }

    /* �Է� ���� �ݱ� */
    fclose(inputFile);

    /* �ֱ��� �� ã�� */
    minDistance = distance(points[0], points[1]);
    for (i = 0; i < numPoints; i++) {
        for (j = i + 1; j < numPoints; j++) {
            double d = distance(points[i], points[j]);
            if (d < minDistance) {
                minDistance = d;
            }
        }
    }

    /* ��� ���� ���� */
    if (fopen_s(&outputFile, "result.txt", "w") != 0) {
        printf("��� ������ �� �� �����ϴ�.\n");
        free(points);
        return 1;
    }

    /* �ֱ��� �� �Ÿ� ���� */
    if (fprintf(outputFile, "%.2f\n", minDistance) < 0) {
        printf("��� ���Ͽ� �� �� �����ϴ�.\n");
        fclose(outputFile);
        free(points);
        return 1;
    }

    /* ��� ���� �ݱ� */ 
    fclose(outputFile);

    /* ���� �Ҵ� ���� */
    free(points);

    printf("�ֱ��� �� �Ÿ�: %.2f\n", minDistance);

    return 0;
}