/*
이름:조현성
학번:202211506 
프로그램 명:FInd_naerest_pair
프로그램 날짜:2023.5.07(일)
프로그램 설명: 최근접점쌍을 찾는 프로그램 
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

    /*입력 파일 열기 */
    if (fopen_s(&inputFile, "data.txt", "r") != 0) {
        printf("입력 파일을 열 수 없습니다.\n");
        return 1;
    }

    /* 데이터 개수 읽기 */
    if (fscanf_s(inputFile, "%d", &numPoints) != 1) {
        printf("데이터 개수를 읽을 수 없습니다.\n");
        fclose(inputFile);
        return 1;
    }

    /* 포인트 데이터 배열 동적 할당 */
    points = (Point*)malloc(numPoints * sizeof(Point));

    /* 포인트 데이터 읽기 */
    for (i = 0; i < numPoints; i++) {
        if (fscanf_s(inputFile, "%d %d", &points[i].x, &points[i].y) != 2) {
            printf("포인트 데이터를 읽을 수 없습니다.\n");
            fclose(inputFile);
            free(points);
            return 1;
        }
    }

    /* 입력 파일 닫기 */
    fclose(inputFile);

    /* 최근접 쌍 찾기 */
    minDistance = distance(points[0], points[1]);
    for (i = 0; i < numPoints; i++) {
        for (j = i + 1; j < numPoints; j++) {
            double d = distance(points[i], points[j]);
            if (d < minDistance) {
                minDistance = d;
            }
        }
    }

    /* 결과 파일 열기 */
    if (fopen_s(&outputFile, "result.txt", "w") != 0) {
        printf("결과 파일을 열 수 없습니다.\n");
        free(points);
        return 1;
    }

    /* 최근접 쌍 거리 쓰기 */
    if (fprintf(outputFile, "%.2f\n", minDistance) < 0) {
        printf("결과 파일에 쓸 수 없습니다.\n");
        fclose(outputFile);
        free(points);
        return 1;
    }

    /* 결과 파일 닫기 */ 
    fclose(outputFile);

    /* 동적 할당 해제 */
    free(points);

    printf("최근접 쌍 거리: %.2f\n", minDistance);

    return 0;
}