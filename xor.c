#include <stdio.h>
#include <string.h>

void xorEncrypt(char *message, char *key) {
    int keyLen = strlen(key);
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= key[i % keyLen];
    }
}

void encryptFile(const char *filename, const char *message, const char *key) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    xorEncrypt((char *)message, key);
    fprintf(file, "%s", message);

    fclose(file);
}

void decryptFile(const char *filename, const char *key) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc((fileSize + 1) * sizeof(char));
    if (!buffer) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    xorEncrypt(buffer, key);

    for (int i = 0; buffer[i] != '\0'; i++) {
        printf("%c", buffer[i]);
    }

    free(buffer);
    fclose(file);
}

int main() {
    char mode;
    printf("Enter 'e' to encrypt or 'd' to decrypt: ");
    scanf(" %c", &mode);

    if (mode == 'e') {
        char message[100];
        char filename[50];
        char key[20];

        printf("Enter the message to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        printf("Enter the filename to save encrypted data: ");
        scanf("%s", filename);

        printf("Enter the encryption key: ");
        scanf("%s", key);

        encryptFile(filename, message, key);
    } else if (mode == 'd') {
        char filename[50];
        char key[20];

        printf("Enter the filename to decrypt: ");
        scanf("%s", filename);

        printf("Enter the decryption key: ");
        scanf("%s", key);

        decryptFile(filename, key);
    } else {
        printf("Invalid mode.\n");
    }

    return 0;
}