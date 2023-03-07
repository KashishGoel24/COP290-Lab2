part1 :
	gcc part1/src/main.c -o part1/obj/object
	./part1/obj/object $(arg1) $(arg2) $(arg3) $(arg4) $(arg5)

part2-main:
	gcc part2/test/main.c part2/src/list.c part2/src/hm.c part2/src/mythread.c -o part2/obj/main_test 
	./part2/obj/main_test ($arg1) ($arg2) ($arg3) ($arg4)

part2-list_test:
	gcc -o part2/obj/list_test part2/test/list_test.c part2/src/list.c
	./part2/obj/list_test

part2-hashmap_test :
	gcc part2/test/hashmap_test.c part2/src/list.c part2/src/hm.c part2/src/mythread.c -o part2/obj/hashmap_test
	./part2/obj/hashmap_test

part2-no_yield :
	gcc part2/test/main_no_yield.c part2/src/list.c part2/src/hm.c part2/src/mythread.c -o/part2/obj/no_yield
	./part2/obj/no_yield $(arg1) $(arg2) $(arg3) $arg(4)

part2-race :
	gcc part2/test/main_race.c part2/src/list.c part2/src/hm.c part2/src/mythread.c -o part2/obj/main_race
	./part2/obj/main_race


part3 :
  gcc -g3 -o part3/obj/main.o part3/test/main.c part3/src/list.c part3/src/hm.c part3/src/mythread.c     -I include/ -pthread
  ./part3/obj/main.o ($arg1) ($arg2) ($arg3) ($arg4)
 
	
