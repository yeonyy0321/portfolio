#include <stdio.h>
#include <string.h>
#include <json-c/json.h>


const char* json_data[] = {
    "{\"name\":\"John\",\"age\":30}",
    "{\"name\":\"Alice\",\"age\":25}",
    "{\"name\":\"Bob\",\"age\":35}",
    "{\"name\":\"Eva\",\"age\":28}",
    "{\"name\":\"Michael\",\"age\":32}",
    "{\"name\":\"Sarah\",\"age\":23}",
    "{\"name\":\"David\",\"age\":40}",
    "{\"name\":\"Linda\",\"age\":45}",
    "{\"name\":\"Kevin\",\"age\":29}",
    "{\"name\":\"Olivia\",\"age\":27}"
};

// JSON 파싱 함수
void parseJson(const char* jsonStr) {
    json_object *parsedJson = json_tokener_parse(jsonStr);
    const char *name = json_object_get_string(json_object_object_get(parsedJson, "name"));
    int age = json_object_get_int(json_object_object_get(parsedJson, "age"));
    printf("Name: %s, Age: %d\n", name, age);
}

// 1. JSON 데이터를 모두 파싱하고 출력하는 함수
void parseAllJsonData() {
    for (int i = 0; i < 3; i++) {
        parseJson(json_data[i]);
    }
}

// 2. 특정 이름을 가진 사람의 나이를 반환하는 함수
int getAgeByName(const char* name) {
    for (int i = 0; i < 3; i++) {
        json_object *parsedJson = json_tokener_parse(json_data[i]);
        const char *jsonName = json_object_get_string(json_object_object_get(parsedJson, "name"));
        if (strcmp(jsonName, name) == 0) {
            return json_object_get_int(json_object_object_get(parsedJson, "age"));
        }
    }
    return -1; // 이름을 찾을 수 없을 경우 -1 반환
}

// 3. 모든 사람의 평균 나이를 계산하는 함수
float calculateAverageAge() {
    int totalAge = 0;
    for (int i = 0; i < 3; i++) {
        json_object *parsedJson = json_tokener_parse(json_data[i]);
        totalAge += json_object_get_int(json_object_object_get(parsedJson, "age"));
    }
    return (float)totalAge / 3;
}

// 4. 특정 나이 이상인 사람의 이름을 출력하는 함수
void printNamesAboveAge(int thresholdAge) {
    for (int i = 0; i < 3; i++) {
        json_object *parsedJson = json_tokener_parse(json_data[i]);
        int age = json_object_get_int(json_object_object_get(parsedJson, "age"));
        if (age >= thresholdAge) {
            const char *name = json_object_get_string(json_object_object_get(parsedJson, "name"));
            printf("Name: %s\n", name);
        }
    }
}

// 5. JSON 데이터의 이름과 나이를 반대로 출력하는 함수
void printNamesAndAgesReversed() {
    for (int i = 0; i < 3; i++) {
        json_object *parsedJson = json_tokener_parse(json_data[i]);
        const char *name = json_object_get_string(json_object_object_get(parsedJson, "name"));
        int age = json_object_get_int(json_object_object_get(parsedJson, "age"));
        printf("Age: %d, Name: %s\n", age, name);
    }
}

int main() {
    parseAllJsonData();
    
    const char* searchName = "Alice";
    int age = getAgeByName(searchName);
    if (age != -1) {
        printf("%s's Age: %d\n", searchName, age);
    } else {
        printf("%s not found.\n", searchName);
    }

    float avgAge = calculateAverageAge();
    printf("Average Age: %.2f\n", avgAge);

    int threshold = 30;
    printf("Names above %d years old:\n", threshold);
    printNamesAboveAge(threshold);

    printf("Names and Ages Reversed:\n");
    printNamesAndAgesReversed();

    return 0;
}
#include <stdio.h>


//  특정 나이 이하인 사람의 이름을 출력하는 함수
void printNamesBelowAge(int thresholdAge) {
    for (int i = 0; i < 3; i++) {
        json_object *parsedJson = json_tokener_parse(json_data[i]);
        int age = json_object_get_int(json_object_object_get(parsedJson, "age"));
        if (age <= thresholdAge) {
            const char *name = json_object_get_string(json_object_object_get(parsedJson, "name"));
            printf("Name: %s\n", name);
        }
    }
}

//  JSON 데이터를 파일로 저장하는 함수
void saveJsonToFile(const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < 3; i++) {
            fprintf(file, "%s\n", json_data[i]);
        }
        fclose(file);
        printf("JSON data saved to %s\n", filename);
    } else {
        printf("Failed to open %s for writing.\n", filename);
    }
}


//  이름을 기준으로 JSON 데이터를 검색하는 함수
void searchJsonByName(const char* name) {
    for (int i = 0; i < 3; i++) {
        json_object *parsedJson = json_tokener_parse(json_data[i]);
        const char *jsonName = json_object_get_string(json_object_object_get(parsedJson, "name"));
        if (strcmp(jsonName, name) == 0) {
            printf("Found %s in JSON data.\n", name);
            return;
        }
    }
    printf("%s not found in JSON data.\n", name);
} 

// 6. 특정 나이 이상인 사람의 수를 세는 함수
int countPeopleAboveAge(int thresholdAge) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        json_object *parsedJson = json_tokener_parse(json_data[i]);
        int age = json_object_get_int(json_object_object_get(parsedJson, "age"));
        if (age > thresholdAge) {
            count++;
        }
    }
    return count;
}

// 7. 가장 나이가 많은 사람의 이름과 나이를 찾는 함수
void findOldestPerson() {
    int maxAge = 0;
    const char *oldestName = NULL;
    
    for (int i = 0; i < 3; i++) {
        json_object *parsedJson = json_tokener_parse(json_data[i]);
        const char *name = json_object_get_string(json_object_object_get(parsedJson, "name"));
        int age = json_object_get_int(json_object_object_get(parsedJson, "age"));
        
        if (age > maxAge) {
            maxAge = age;
            oldestName = name;
        }
    }
    
    if (oldestName != NULL) {
        printf("%s님은 가장 나이가 많으며, 나이는 %d세입니다.\n", oldestName, maxAge);
    } else {
        printf("가장 나이 많은 사람을 결정할 수 있는 데이터가 없습니다.\n");
    }
}

// 8. 나이를 기준으로 JSON 데이터를 정렬하고 출력하는 함수
void sortAndPrintDataByAge() {
    // 데이터를 나이를 기준으로 정렬하기 위해 정렬 알고리즘을 사용할 수 있으며
    // 그 다음에 정렬된 데이터를 출력할 수 있습니다.
}



int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return a / b;
}

int maintwo() {
    int x = 10;
    int y = 5;

    if (x > y) {
        printf("x is greater than y\n");
    } else {
        printf("x is not greater than y\n");
    }

    if (x == 10) {
        printf("x is equal to 10\n");
    }

    int result = add(x, y);

    printf("Result of addition: %d\n", result);

    return 0;
}
