#include <stdio.h>
#include <string.h>

// 예제 C 코드 파일명
char sourceCodeFilename[] = "sourcecode.c";

// 함수 정보를 저장할 구조체
struct FunctionInfo {
    char name[100];
    char returnType[100];
    int parameterCount;
    char parameterTypes[10][100];
    char parameterNames[10][100];
    int ifCount;
};

// 함수 정보를 저장하는 배열
struct FunctionInfo functions[100];
int functionCount = 0;

// if 조건 개수
int ifCount = 0;

// 함수 정보를 추출하는 함수
void extractFunctionInfo(FILE *sourceFile) {
    char line[1000]; // 가정: 한 줄이 1000자 이하
    while (fgets(line, sizeof(line), sourceFile) != NULL) {
        if (strstr(line, "int ") != NULL && strstr(line, "(") != NULL) {
            char *nameStart = strstr(line, "int ") + 4;
            char *nameEnd = strchr(nameStart, '(');
            char *returnType = nameStart;
            *nameEnd = '\0';

            // 이름 추출
            strcpy(functions[functionCount].name, nameEnd + 1);

            // 리턴 타입 추출
            strcpy(functions[functionCount].returnType, returnType);

            // 파라미터 정보 추출
            char *parameterStart = nameEnd + 1;
            char *parameterEnd = strchr(parameterStart, ')');
            *parameterEnd = '\0';
            char *parameter = parameterStart;
            functions[functionCount].parameterCount = 0;

            while (parameter != NULL && *parameter != '\0') {
                char *comma = strchr(parameter, ',');
                if (comma != NULL) {
                    *comma = '\0';
                }

                char *space = strchr(parameter, ' ');
                if (space != NULL) {
                    char *paramType = parameter;
                    char *paramName = space + 1;

                    // 파라미터 타입 추출
                    strncpy(functions[functionCount].parameterTypes[functions[functionCount].parameterCount], paramType, sizeof(functions[functionCount].parameterTypes[functions[functionCount].parameterCount]));

                    // 파라미터 이름 추출
                    strcpy(functions[functionCount].parameterNames[functions[functionCount].parameterCount], paramName);

                    functions[functionCount].parameterCount++;
                }

                parameter = comma + 1;
            }

            functionCount++;
        }

        if (strstr(line, "if (") != NULL) {
            ifCount++;
        }
    }
}

int main() {
    // 소스 코드 파일 열기
    FILE *sourceFile = fopen(sourceCodeFilename, "r");
    if (sourceFile == NULL) {
        perror("파일을 열 수 없습니다");
        return 1;
    }

    // 함수 정보를 추출
    extractFunctionInfo(sourceFile);

    // 파일 닫기
    fclose(sourceFile);

    // 함수 정보 및 if 조건 개수 출력
    printf("함수 개수: %d\n", functionCount);
    printf("함수 정보:\n");
    for (int i = 0; i < functionCount; i++) {
        printf("  함수 이름: %s\n", functions[i].name);
        printf("  리턴 타입: %s\n", functions[i].returnType);
        printf("  파라미터 개수: %d\n", functions[i].parameterCount);
        printf("  파라미터 정보:\n");
        for (int j = 0; j < functions[i].parameterCount; j++) {
            printf("    타입: %s, 변수명: %s\n", functions[i].parameterTypes[j], functions[i].parameterNames[j]);
        }
    }
    printf("if 조건 개수: %d\n", ifCount);

    return 0;
}
