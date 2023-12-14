#include "shell.h"

/**
 * _outputString - prints an input string to standard error
 * @inputString: the string to be printed
 *
 * Return: Nothing
 */
void _outputString(char *inputString)
{
    int i = 0;

    if (!inputString)
        return;
    while (inputString[i] != '\0')
    {
        _outputCharacter(inputString[i]);
        i++;
    }
}

/**
 * _outputCharacter - writes the character c to standard error
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _outputCharacter(char character)
{
    static int index;
    static char buffer[WRITE_BUFFER_SIZE];

    if (character == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
    {
        write(2, buffer, index);
        index = 0;
    }
    if (character != BUFFER_FLUSH)
        buffer[index++] = character;
    return (1);
}

/**
 * _writeCharacterToFD - writes the character c to a given file descriptor
 * @character: The character to print
 * @fileDescriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _writeCharacterToFD(char character, int fileDescriptor)
{
    static int index;
    static char buffer[WRITE_BUFFER_SIZE];

    if (character == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
    {
        write(fileDescriptor, buffer, index);
        index = 0;
    }
    if (character != BUFFER_FLUSH)
        buffer[index++] = character;
    return (1);
}

/**
 * _outputStringToFD - prints an input string to a given file descriptor
 * @inputString: the string to be printed
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _outputStringToFD(char *inputString, int fileDescriptor)
{
    int i = 0;

    if (!inputString)
        return (0);
    while (*inputString)
    {
        i += _writeCharacterToFD(*inputString++, fileDescriptor);
    }
    return (i);
}

