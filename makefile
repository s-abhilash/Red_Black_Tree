SRCS1 := red_black_tree.c
TRGT1 := red_black_tree

${TRGT1} : ${SRCS1}
	gcc $^ -o $@

clean :
	rm -f ${TRGT1}
