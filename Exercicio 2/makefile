# Nome do arquivo executável
TARGET = programa

# Caminho do compilador C
CC = gcc

# Diretório onde os arquivos .o (objetos) serão gerados
OBJ_DIR = obj

# Diretório onde o executável será gerado
BIN_DIR = bin

# Lista de arquivos fonte
SOURCES = $(wildcard *.c)

# Lista de arquivos objeto (.o)
OBJECTS = $(SOURCES:.c=.o)

# Nome da regra que compila e roda o programa
all: $(TARGET) run

# Cria os diretórios bin e obj se eles não existirem
$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(BIN_DIR):
	@mkdir $(BIN_DIR)

# Compila o código C e cria o executável
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@$(CC) -o $(BIN_DIR)/$(TARGET) $(OBJECTS)

# Compila os arquivos .c para .o (objetos)
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) -c $< -o $@

# Executa o programa C
run: $(TARGET)
	@./$(BIN_DIR)/$(TARGET)

# Limpa os arquivos gerados
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
