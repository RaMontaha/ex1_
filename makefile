CC = gcc
OBJS = tool/AsciiArtTool.o tool/main.o RLEList.o
EXEC = AsciiArtTool
DEBUG_FLAG =
COMP_FLAG = -std=c99 -Itool -Wall -pedantic-errors -Werror -DNDEBUG -I.
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
tool/AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h /home/mtm/public/2122b/ex1/RLEList.h
	$(CC) -o $@ -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
tool/main.o:  tool/main.c /home/mtm/public/2122b/ex1/RLEList.h tool/AsciiArtTool.h
	$(CC) -o $@ -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
RLEList.o: RLEList.c /home/mtm/public/2122b/ex1/RLEList.h
	$(CC) -o $@ -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
clean:
	 rm -f $(OBJS) $(EXEC)