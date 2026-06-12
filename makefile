
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g -Iinclude
LDFLAGS = 
TARGET  = biblioteca.exe
 
# ─── Diretórios ───────────────────────────────────────────────
SRCDIR  = src
INCDIR  = include
OBJDIR  = obj
DATADIR = data
 
# ─── Fontes, objetos e dependências ───────────────────────────
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEPS = $(wildcard $(INCDIR)/*.h)
 
# ─── Regra padrão ─────────────────────────────────────────────
all: dirs $(TARGET)
	@echo.
	@echo   [OK] Compilacao concluida: $(TARGET)
 
# ─── Cria diretórios necessários ──────────────────────────────
# Detecta automaticamente se está rodando em MSYS2/MinGW (sh.exe disponível)
# ou no Prompt de Comando nativo do Windows (cmd.exe).
ifeq ($(OS),Windows_NT)
    SHELL_TYPE := $(shell sh -c "echo sh" 2>nul)
    ifeq ($(SHELL_TYPE),sh)
        # MSYS2 / Git Bash
        MKDIR = mkdir -p
        RM    = rm -rf
        RUN   = ./$(TARGET)
    else
        # CMD nativo
        MKDIR = if not exist
        RM    = rmdir /s /q
        RUN   = $(TARGET)
    endif
else
    MKDIR = mkdir -p
    RM    = rm -rf
    RUN   = ./$(TARGET)
endif
 
dirs:
ifeq ($(SHELL_TYPE),sh)
	@mkdir -p $(OBJDIR) $(DATADIR)
else
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(DATADIR) mkdir $(DATADIR)
endif
 
# ─── Linka o executável ───────────────────────────────────────
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
 
# ─── Compila cada .c → .o (recompila se algum .h mudar) ───────
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
 
# ─── Remove artefatos de compilação ───────────────────────────
clean:
ifeq ($(SHELL_TYPE),sh)
	rm -rf $(OBJDIR) $(TARGET)
else
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(TARGET) del /q $(TARGET)
endif
	@echo   [OK] Limpeza concluida.
 
# ─── Compila e executa ────────────────────────────────────────
run: all
ifeq ($(SHELL_TYPE),sh)
	./$(TARGET)
else
	$(TARGET)
endif
 
# ─── Recompila tudo do zero ───────────────────────────────────
rebuild: clean all
 
.PHONY: all dirs clean run rebuild
 