.PHONY: p1 p2 p3 p4 p5 p6

p1:
	find / -mindepth 0 -size +1024c -type f -executable -name "*.exe"

p2:
	find ~/OS -mindepth 0 -size +100c -type f -name "*.c"

p3:
	find ~ -mindepth 0 -type f -user matteo -readable -regextype posix-egrep -regex ".*(A[^/]*a|a[^/]*A)[^/]*" -exec tail -n 3 \{} \;

p4:
	echo "Caratteri:\n" && find ~ -mindepth 3 -maxdepth 5 -type f -user matteo -readable -size +250c -regextype posix-egrep -regex "\w{4}" -exec wc -m \{} \;
	echo "Righe:\n" && find ~ -mindepth 3 -maxdepth 5 -type f -user matteo -readable -size +250c -regex ".*/[a-z]{4}" -exec wc -l \{} \;

p5:
	find ~ -mindepth 0 -type f -regextype posix-egrep -regex ".*/A[^/]*z{3}[^/]*\.[A-Za-z]{3}" -exec gzip -c \{} \;

p6:
	find / -mindepth 0 -type d -name "bin" -exec ls -la \{} \;