#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h> // Make sure cJSON.h is in your include path

int main() {
    cJSON *root = NULL;
    char *json_string_created = NULL;
    char *json_string_parsed = "{\"name\":\"John Doe\",\"age\":30,\"isStudent\":false,\"grades\":[95,88,72],\"address\":{\"street\":\"123 Main St\",\"city\":\"Anytown\",\"zip\":\"12345\"}}";
    cJSON *parsed_json = NULL;

    // --- Part 1: Creating JSON ---
    printf("--- Creating JSON ---\n");

    // Create the root object
    root = cJSON_CreateObject();
    if (root == NULL) {
        printf("Failed to create JSON root object.\n");
        return 1;
    }

    // Add string
    cJSON_AddStringToObject(root, "name", "Alice Smith");
    // Add integer
    cJSON_AddNumberToObject(root, "age", 25);
    // Add boolean
    cJSON_AddBoolToObject(root, "isStudent", cJSON_True);

    // Add an array
    cJSON *grades_array = cJSON_CreateArray();
    if (grades_array == NULL) {
        printf("Failed to create grades array.\n");
        cJSON_Delete(root);
        return 1;
    }
    cJSON_AddItemToObject(root, "grades", grades_array);
    cJSON_AddItemToArray(grades_array, cJSON_CreateNumber(85));
    cJSON_AddItemToArray(grades_array, cJSON_CreateNumber(92));
    cJSON_AddItemToArray(grades_array, cJSON_CreateNumber(78));

    // Add a nested object
    cJSON *address_object = cJSON_CreateObject();
    if (address_object == NULL) {
        printf("Failed to create address object.\n");
        cJSON_Delete(root);
        return 1;
    }
    cJSON_AddItemToObject(root, "address", address_object);
    cJSON_AddStringToObject(address_object, "street", "456 Oak Ave");
    cJSON_AddStringToObject(address_object, "city", "Someville");
    cJSON_AddStringToObject(address_object, "zip", "67890");

    // Print the created JSON
    json_string_created = cJSON_Print(root);
    if (json_string_created == NULL) {
        printf("Failed to print JSON to string.\n");
        cJSON_Delete(root);
        return 1;
    }
    printf("Created JSON: %s\n\n", json_string_created);

    // Clean up created JSON string and root object
    free(json_string_created);
    cJSON_Delete(root);

    // --- Part 2: Parsing JSON ---
    printf("--- Parsing JSON ---\n");

    printf("JSON string to parse: %s\n", json_string_parsed);

    // Parse the JSON string
    parsed_json = cJSON_Parse(json_string_parsed);
    if (parsed_json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        printf("Failed to parse JSON string.\n");
        return 1;
    }

    // Access values
    cJSON *name = cJSON_GetObjectItemCaseSensitive(parsed_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        printf("Name: %s\n", name->valuestring);
    }

    cJSON *age = cJSON_GetObjectItemCaseSensitive(parsed_json, "age");
    if (cJSON_IsNumber(age)) {
        printf("Age: %d\n", age->valueint);
    }

    cJSON *is_student = cJSON_GetObjectItemCaseSensitive(parsed_json, "isStudent");
    if (cJSON_IsBool(is_student)) {
        printf("Is Student: %s\n", cJSON_IsTrue(is_student) ? "true" : "false");
    }

    cJSON *grades = cJSON_GetObjectItemCaseSensitive(parsed_json, "grades");
    if (cJSON_IsArray(grades)) {
        printf("Grades: ");
        int i;
        cJSON *grade_item = NULL;
        cJSON_ArrayForEach(grade_item, grades) {
            if (cJSON_IsNumber(grade_item)) {
                printf("%d ", grade_item->valueint);
            }
        }
        printf("\n");
    }

    cJSON *address = cJSON_GetObjectItemCaseSensitive(parsed_json, "address");
    if (cJSON_IsObject(address)) {
        cJSON *street = cJSON_GetObjectItemCaseSensitive(address, "street");
        if (cJSON_IsString(street) && (street->valuestring != NULL)) {
            printf("Address Street: %s\n", street->valuestring);
        }
        cJSON *city = cJSON_GetObjectItemCaseSensitive(address, "city");
        if (cJSON_IsString(city) && (city->valuestring != NULL)) {
            printf("Address City: %s\n", city->valuestring);
        }
    }

    // Clean up parsed JSON object
    cJSON_Delete(parsed_json);

    return 0;
}
