# Makefile - bruteforce_full (spec 10)
# Uso:
#   make                       monta com os valores padrao
#   make DELAY_NS=0            velocidade maxima (--defsym DELAY_NS=0)
#   make SHOW_SHIFT=20 ...     tela a cada 2^20 tentativas
#   make run / make clean
# Ao mudar DELAY_NS/SHOW_SHIFT, rode "make clean" antes (ou use "make -B").

AS ?= as
LD ?= ld
PROG := bruteforce_full

DEFSYMS := $(if $(DELAY_NS),--defsym DELAY_NS=$(DELAY_NS)) \
           $(if $(SHOW_SHIFT),--defsym SHOW_SHIFT=$(SHOW_SHIFT))

.PHONY: all run clean

all: $(PROG)

$(PROG): $(PROG).o
	$(LD) $< -o $@

$(PROG).o: $(PROG).asm
	$(AS) $(DEFSYMS) $< -o $@

run: $(PROG)
	./$(PROG)

clean:
	rm -f $(PROG) $(PROG).o
