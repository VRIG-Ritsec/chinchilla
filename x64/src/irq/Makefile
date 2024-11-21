OUT_DIR := $(addsuffix /irq, $(BUILD_DIR))

TARGETS = idt isr 
TARGETS := $(addprefix $(OUT_DIR)/, $(addsuffix .o, $(TARGETS)))


all:  
	make $(TARGETS) 
$(OUT_DIR):
	mkdir -p $(OUT_DIR)
$(OUT_DIR)/idt.o: idt.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^
$(OUT_DIR)/isr.o: isr.s | $(OUT_DIR)
	$(ASM) $(ASMFLAGS) -o $@ $^


