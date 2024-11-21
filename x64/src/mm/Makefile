OUT_DIR := $(addsuffix /mm, $(BUILD_DIR))

TARGETS := buddy
TARGETS := $(addprefix $(OUT_DIR)/, $(addsuffix .o, $(TARGETS)))


all:  
	make $(TARGETS) 
$(OUT_DIR):
	mkdir -p $(OUT_DIR)
$(OUT_DIR)/buddy.o: buddy.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^

