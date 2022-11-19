.PHONY: p1 p2 p3 p4 p5 p6 p7 p8 p9 p10

p1:
	sort -k1,1nr lab05e04in.txt

p2:
	sort -k2,2 lab05e04in.txt

p3:
	grep 2011/2012 lab05e04in.txt | cut -f 2-3

p4:
	grep INF1T3 lab05e04in.txt | sort -k1,1n | cut -f 1-3

p5:
	grep -E -e "^[0-9]*[24]\s.+$$" lab05e04in.txt | sort -k2,2

p6:
	grep TLC1T3 lab05e04in.txt | grep "Da frequentare" | sort -k1,1nr | cut -f 1-3

p7:
	grep -E -e "^[0-9]+\s[A-Z]*A.{2}A[A-Z]*.+$$" lab05e04in.txt

p8:
	grep -E -e "^[0-9]+\s[B-Z][A-Z]*A[A-Z]{2}A[A-Z]*[B-Z].+$$" lab05e04in.txt

p9:
	cut -f 1 lab05e04in.txt | tr -d 0 | tr 8 1 | sort -n | uniq

p10:
	cut -f 1 lab05e04in.txt | tr -d 0 | tr 8 1 | sort -n | uniq -d -c