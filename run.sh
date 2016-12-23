screen -d -m -S master ~/afl-2.35b/afl-fuzz -i testcases/ -o sync_dir -M fuzzer1 -m100 ${PROG}

for i in $(seq 3 $(nproc --all))
do
	echo ${i}
	screen -d -m -S afl${i}  ~/afl-2.35b/afl-fuzz -i testcases/ -o sync_dir -m100 -S fuzzer${i} ${PROF}
done

screen -d -m -S status watch "~/afl-2.35b/afl-whatsup -s sync_dir"
rm -f totals
screen -d -m -S reporter watch -n 5  "~/afl-2.35b/afl-whatsup -s sync_dir | grep Cumulative | tee -a totals"
