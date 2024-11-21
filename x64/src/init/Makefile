OUT_DIR := $(addsuffix /init, $(BUILD_DIR))

TARGETS := main start
TARGETS := $(addprefix $(OUT_DIR)/, $(addsuffix .o, $(TARGETS)))


all:  
	make $(TARGETS) 
$(OUT_DIR):
	mkdir -p $(OUT_DIR)
$(OUT_DIR)/main.o: main.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^
$(OUT_DIR)/start.o: start.s | $(OUT_DIR)
	$(ASM) $(ASMFLAGS) -o $@ $^
