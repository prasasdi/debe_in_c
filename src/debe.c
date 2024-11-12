#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/helper.h"
#include "../include/meta_command_enum.h"

typedef struct {
  char* buffer;
  size_t buffer_length;
  size_t input_length;
} InputBuffer;

int new_input_buffer(InputBuffer* input_buffer) {
  input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  if (input_buffer==NULL) {
    perror("new_input_buffer malloc()");
    return -1;
  }
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;
  return 0;
}

void printf_prompt(void)
{
  printf("debe > ");
}

int read_input(InputBuffer* input_buffer) {
  size_t bytes_read = win_getline(&input_buffer->buffer, &input_buffer->input_length, stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;

  return 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

// statement preparation
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }
  if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

void execute_statement(Statement* statement) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      printf("Todo; insert.\n");
      break;
    case (STATEMENT_SELECT):
      printf("Todo; select.\n");
      break;
  }
}

int main(void) {
  InputBuffer input_buffer;
  new_input_buffer(&input_buffer);

  while(1) {
    printf_prompt();
    read_input(&input_buffer);

    if (input_buffer.buffer[0] == '.') {
      switch(do_meta_command(&input_buffer)) {
        case (META_COMMAND_SUCCESS):
          continue;
        case (META_COMMAND_UNRECOGNIZED_COMMAND):
          printf("Unrecognized command '%s'\n", input_buffer.buffer);
          continue;
      }
    }

    Statement statement;

    switch (prepare_statement(&input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized keyword at start of '%s'\n", input_buffer.buffer);
        continue;
    }
    execute_statement(&statement);
    printf("Executed.\n");

  }

  return 0;
}
