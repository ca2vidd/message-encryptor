#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encrypt(const char *message, int shift) {
  int length = strlen(message);
  char *encrypted = malloc(length + 1);

  if (!encrypted) {
    perror("Failed to allocate memory for encryption");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < length; i++) {
    if (isalpha(message[i])) {
      char base = isupper(message[i]) ? 'A' : 'a';
      encrypted[i] = (message[i] - base + shift) % 26 + base;
    } else {
      encrypted[i] = message[i];
    }
  }

  encrypted[length] = '\0';
  return encrypted;
}

char *decrypt(const char *encrypted, int shift) {
  int length = strlen(encrypted);
  char *decrypted = malloc(length + 1);

  if (!decrypted) {
    perror("Failed to allocate memory for decryption");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < length; i++) {
    if (isalpha(encrypted[i])) {
      char base = isupper(encrypted[i]) ? 'A' : 'a';
      decrypted[i] = (encrypted[i] - base - shift + 26) % 26 + base;
    } else {
      decrypted[i] = encrypted[i];
    }
  }

  decrypted[length] = '\0';
  return decrypted;
}

void secure_free(char *ptr, int length) {
  if (ptr) {
    memset(ptr, 0, length);
    free(ptr);
  }
}

int main() {
  char message[1024];
  int shift;

  printf("Enter a message to encrypt: ");
  fgets(message, sizeof(message), stdin);
  message[strcspn(message, "\n")] = 0;

  printf("Enter the shift value: ");
  scanf("%d", &shift);

  char *encryptedMessage = encrypt(message, shift);
  printf("Encrypted Message: %s\n", encryptedMessage);

  char *decryptedMessage = decrypt(encryptedMessage, shift);
  printf("Decrypted Message: %s\n", decryptedMessage);

  secure_free(encryptedMessage, strlen(encryptedMessage));
  secure_free(decryptedMessage, strlen(decryptedMessage));

  return 0;
}
