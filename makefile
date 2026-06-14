CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g -Iinclude
LDFLAGS = -lkernel32
BINARY  = biblioteca.exe

# ─── Diretórios ───────────────────────────────────────────────
SRCDIR  = src
INCDIR  = include
OBJDIR  = obj
DATADIR = data
OUTDIR  = output

TARGET  = $(OUTDIR)/$(BINARY)

# ─── Fontes e objetos ─────────────────────────────────────────
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# ─── Detecta ambiente: MSYS2/Git Bash ou CMD nativo ───────────
ifeq ($(OS),Windows_NT)
    SHELL_TYPE := $(shell sh -c "echo sh" 2>nul)
    ifeq ($(SHELL_TYPE),sh)
        MKDIR = mkdir -p
        RM    = rm -rf
        RUN   = ./$(TARGET)
    else
        MKDIR = mkdir
        RM    = rmdir /s /q
        RUN   = $(OUTDIR)\$(BINARY)
    endif
else
    SHELL_TYPE = sh
    MKDIR = mkdir -p
    RM    = rm -rf
    RUN   = ./$(TARGET)
endif

# ─── Regra padrão ─────────────────────────────────────────────
all: dirs $(TARGET)
	@echo.
	@echo   [OK] Compilacao concluida: $(TARGET) em $(OUTDIR)/

# ─── Cria diretórios necessários ──────────────────────────────
dirs:
ifeq ($(SHELL_TYPE),sh)
	@mkdir -p $(OBJDIR) $(DATADIR) $(OUTDIR)
else
	@if not exist $(OBJDIR) $(MKDIR) $(OBJDIR)
	@if not exist $(DATADIR) $(MKDIR) $(DATADIR)
	@if not exist $(OUTDIR) $(MKDIR) $(OUTDIR)
endif

# ─── Linka o executável ───────────────────────────────────────
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# ─── Compila cada .c em .o com dependências individuais ───────
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Inclui as dependências geradas automaticamente pelo -MMD
-include $(OBJS:.o=.d)

# ─── Remove artefatos de compilação ───────────────────────────
clean:
ifeq ($(SHELL_TYPE),sh)
	$(RM) $(OBJDIR) $(OUTDIR)
else
	@if exist $(OBJDIR) $(RM) $(OBJDIR)
	@if exist $(OUTDIR) $(RM) $(OUTDIR)
endif
	@echo   [OK] Limpeza concluida.

# ─── Compila e executa ────────────────────────────────────────
run: all
	$(RUN)

# ─── Recompila tudo do zero ───────────────────────────────────
rebuild: clean all

.PHONY: all dirs clean run rebuild