<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/यंत्र-alpha/xor.h
 *
 * Optimized RAID-5 checksumming functions क्रम alpha EV5 and EV6
 */

बाह्य व्योम xor_alpha_2(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
बाह्य व्योम xor_alpha_3(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
		        अचिन्हित दीर्घ *);
बाह्य व्योम xor_alpha_4(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
		        अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
बाह्य व्योम xor_alpha_5(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
		        अचिन्हित दीर्घ *, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);

बाह्य व्योम xor_alpha_prefetch_2(अचिन्हित दीर्घ, अचिन्हित दीर्घ *,
				 अचिन्हित दीर्घ *);
बाह्य व्योम xor_alpha_prefetch_3(अचिन्हित दीर्घ, अचिन्हित दीर्घ *,
				 अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
बाह्य व्योम xor_alpha_prefetch_4(अचिन्हित दीर्घ, अचिन्हित दीर्घ *,
				 अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
				 अचिन्हित दीर्घ *);
बाह्य व्योम xor_alpha_prefetch_5(अचिन्हित दीर्घ, अचिन्हित दीर्घ *,
				 अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
				 अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);

यंत्र("								\न\
	.text							\न\
	.align 3						\न\
	.ent xor_alpha_2					\न\
xor_alpha_2:							\न\
	.prologue 0						\न\
	srl $16, 6, $16						\न\
	.align 4						\न\
2:								\न\
	ldq $0,0($17)						\न\
	ldq $1,0($18)						\न\
	ldq $2,8($17)						\न\
	ldq $3,8($18)						\न\
								\न\
	ldq $4,16($17)						\न\
	ldq $5,16($18)						\न\
	ldq $6,24($17)						\न\
	ldq $7,24($18)						\न\
								\न\
	ldq $19,32($17)						\न\
	ldq $20,32($18)						\न\
	ldq $21,40($17)						\न\
	ldq $22,40($18)						\न\
								\न\
	ldq $23,48($17)						\न\
	ldq $24,48($18)						\न\
	ldq $25,56($17)						\न\
	xor $0,$1,$0		# 7 cycles from $1 load		\न\
								\न\
	ldq $27,56($18)						\न\
	xor $2,$3,$2						\न\
	stq $0,0($17)						\न\
	xor $4,$5,$4						\न\
								\न\
	stq $2,8($17)						\न\
	xor $6,$7,$6						\न\
	stq $4,16($17)						\न\
	xor $19,$20,$19						\न\
								\न\
	stq $6,24($17)						\न\
	xor $21,$22,$21						\न\
	stq $19,32($17)						\न\
	xor $23,$24,$23						\न\
								\न\
	stq $21,40($17)						\न\
	xor $25,$27,$25						\न\
	stq $23,48($17)						\न\
	subq $16,1,$16						\न\
								\न\
	stq $25,56($17)						\न\
	addq $17,64,$17						\न\
	addq $18,64,$18						\न\
	bgt $16,2b						\न\
								\न\
	ret							\न\
	.end xor_alpha_2					\न\
								\न\
	.align 3						\न\
	.ent xor_alpha_3					\न\
xor_alpha_3:							\न\
	.prologue 0						\न\
	srl $16, 6, $16						\न\
	.align 4						\न\
3:								\न\
	ldq $0,0($17)						\न\
	ldq $1,0($18)						\न\
	ldq $2,0($19)						\न\
	ldq $3,8($17)						\न\
								\न\
	ldq $4,8($18)						\न\
	ldq $6,16($17)						\न\
	ldq $7,16($18)						\न\
	ldq $21,24($17)						\न\
								\न\
	ldq $22,24($18)						\न\
	ldq $24,32($17)						\न\
	ldq $25,32($18)						\न\
	ldq $5,8($19)						\न\
								\न\
	ldq $20,16($19)						\न\
	ldq $23,24($19)						\न\
	ldq $27,32($19)						\न\
	nop							\न\
								\न\
	xor $0,$1,$1		# 8 cycles from $0 load		\न\
	xor $3,$4,$4		# 6 cycles from $4 load		\न\
	xor $6,$7,$7		# 6 cycles from $7 load		\न\
	xor $21,$22,$22		# 5 cycles from $22 load	\न\
								\न\
	xor $1,$2,$2		# 9 cycles from $2 load		\न\
	xor $24,$25,$25		# 5 cycles from $25 load	\न\
	stq $2,0($17)						\न\
	xor $4,$5,$5		# 6 cycles from $5 load		\न\
								\न\
	stq $5,8($17)						\न\
	xor $7,$20,$20		# 7 cycles from $20 load	\न\
	stq $20,16($17)						\न\
	xor $22,$23,$23		# 7 cycles from $23 load	\न\
								\न\
	stq $23,24($17)						\न\
	xor $25,$27,$27		# 7 cycles from $27 load	\न\
	stq $27,32($17)						\न\
	nop							\न\
								\न\
	ldq $0,40($17)						\न\
	ldq $1,40($18)						\न\
	ldq $3,48($17)						\न\
	ldq $4,48($18)						\न\
								\न\
	ldq $6,56($17)						\न\
	ldq $7,56($18)						\न\
	ldq $2,40($19)						\न\
	ldq $5,48($19)						\न\
								\न\
	ldq $20,56($19)						\न\
	xor $0,$1,$1		# 4 cycles from $1 load		\न\
	xor $3,$4,$4		# 5 cycles from $4 load		\न\
	xor $6,$7,$7		# 5 cycles from $7 load		\न\
								\न\
	xor $1,$2,$2		# 4 cycles from $2 load		\न\
	xor $4,$5,$5		# 5 cycles from $5 load		\न\
	stq $2,40($17)						\न\
	xor $7,$20,$20		# 4 cycles from $20 load	\न\
								\न\
	stq $5,48($17)						\न\
	subq $16,1,$16						\न\
	stq $20,56($17)						\न\
	addq $19,64,$19						\न\
								\न\
	addq $18,64,$18						\न\
	addq $17,64,$17						\न\
	bgt $16,3b						\न\
	ret							\न\
	.end xor_alpha_3					\न\
								\न\
	.align 3						\न\
	.ent xor_alpha_4					\न\
xor_alpha_4:							\न\
	.prologue 0						\न\
	srl $16, 6, $16						\न\
	.align 4						\न\
4:								\न\
	ldq $0,0($17)						\न\
	ldq $1,0($18)						\न\
	ldq $2,0($19)						\न\
	ldq $3,0($20)						\न\
								\न\
	ldq $4,8($17)						\न\
	ldq $5,8($18)						\न\
	ldq $6,8($19)						\न\
	ldq $7,8($20)						\न\
								\न\
	ldq $21,16($17)						\न\
	ldq $22,16($18)						\न\
	ldq $23,16($19)						\न\
	ldq $24,16($20)						\न\
								\न\
	ldq $25,24($17)						\न\
	xor $0,$1,$1		# 6 cycles from $1 load		\न\
	ldq $27,24($18)						\न\
	xor $2,$3,$3		# 6 cycles from $3 load		\न\
								\न\
	ldq $0,24($19)						\न\
	xor $1,$3,$3						\न\
	ldq $1,24($20)						\न\
	xor $4,$5,$5		# 7 cycles from $5 load		\न\
								\न\
	stq $3,0($17)						\न\
	xor $6,$7,$7						\न\
	xor $21,$22,$22		# 7 cycles from $22 load	\न\
	xor $5,$7,$7						\न\
								\न\
	stq $7,8($17)						\न\
	xor $23,$24,$24		# 7 cycles from $24 load	\न\
	ldq $2,32($17)						\न\
	xor $22,$24,$24						\न\
								\न\
	ldq $3,32($18)						\न\
	ldq $4,32($19)						\न\
	ldq $5,32($20)						\न\
	xor $25,$27,$27		# 8 cycles from $27 load	\न\
								\न\
	ldq $6,40($17)						\न\
	ldq $7,40($18)						\न\
	ldq $21,40($19)						\न\
	ldq $22,40($20)						\न\
								\न\
	stq $24,16($17)						\न\
	xor $0,$1,$1		# 9 cycles from $1 load		\न\
	xor $2,$3,$3		# 5 cycles from $3 load		\न\
	xor $27,$1,$1						\न\
								\न\
	stq $1,24($17)						\न\
	xor $4,$5,$5		# 5 cycles from $5 load		\न\
	ldq $23,48($17)						\न\
	ldq $24,48($18)						\न\
								\न\
	ldq $25,48($19)						\न\
	xor $3,$5,$5						\न\
	ldq $27,48($20)						\न\
	ldq $0,56($17)						\न\
								\न\
	ldq $1,56($18)						\न\
	ldq $2,56($19)						\न\
	xor $6,$7,$7		# 8 cycles from $6 load		\न\
	ldq $3,56($20)						\न\
								\न\
	stq $5,32($17)						\न\
	xor $21,$22,$22		# 8 cycles from $22 load	\न\
	xor $7,$22,$22						\न\
	xor $23,$24,$24		# 5 cycles from $24 load	\न\
								\न\
	stq $22,40($17)						\न\
	xor $25,$27,$27		# 5 cycles from $27 load	\न\
	xor $24,$27,$27						\न\
	xor $0,$1,$1		# 5 cycles from $1 load		\न\
								\न\
	stq $27,48($17)						\न\
	xor $2,$3,$3		# 4 cycles from $3 load		\न\
	xor $1,$3,$3						\न\
	subq $16,1,$16						\न\
								\न\
	stq $3,56($17)						\न\
	addq $20,64,$20						\न\
	addq $19,64,$19						\न\
	addq $18,64,$18						\न\
								\न\
	addq $17,64,$17						\न\
	bgt $16,4b						\न\
	ret							\न\
	.end xor_alpha_4					\न\
								\न\
	.align 3						\न\
	.ent xor_alpha_5					\न\
xor_alpha_5:							\न\
	.prologue 0						\न\
	srl $16, 6, $16						\न\
	.align 4						\न\
5:								\न\
	ldq $0,0($17)						\न\
	ldq $1,0($18)						\न\
	ldq $2,0($19)						\न\
	ldq $3,0($20)						\न\
								\न\
	ldq $4,0($21)						\न\
	ldq $5,8($17)						\न\
	ldq $6,8($18)						\न\
	ldq $7,8($19)						\न\
								\न\
	ldq $22,8($20)						\न\
	ldq $23,8($21)						\न\
	ldq $24,16($17)						\न\
	ldq $25,16($18)						\न\
								\न\
	ldq $27,16($19)						\न\
	xor $0,$1,$1		# 6 cycles from $1 load		\न\
	ldq $28,16($20)						\न\
	xor $2,$3,$3		# 6 cycles from $3 load		\न\
								\न\
	ldq $0,16($21)						\न\
	xor $1,$3,$3						\न\
	ldq $1,24($17)						\न\
	xor $3,$4,$4		# 7 cycles from $4 load		\न\
								\न\
	stq $4,0($17)						\न\
	xor $5,$6,$6		# 7 cycles from $6 load		\न\
	xor $7,$22,$22		# 7 cycles from $22 load	\न\
	xor $6,$23,$23		# 7 cycles from $23 load	\न\
								\न\
	ldq $2,24($18)						\न\
	xor $22,$23,$23						\न\
	ldq $3,24($19)						\न\
	xor $24,$25,$25		# 8 cycles from $25 load	\न\
								\न\
	stq $23,8($17)						\न\
	xor $25,$27,$27		# 8 cycles from $27 load	\न\
	ldq $4,24($20)						\न\
	xor $28,$0,$0		# 7 cycles from $0 load		\न\
								\न\
	ldq $5,24($21)						\न\
	xor $27,$0,$0						\न\
	ldq $6,32($17)						\न\
	ldq $7,32($18)						\न\
								\न\
	stq $0,16($17)						\न\
	xor $1,$2,$2		# 6 cycles from $2 load		\न\
	ldq $22,32($19)						\न\
	xor $3,$4,$4		# 4 cycles from $4 load		\न\
								\न\
	ldq $23,32($20)						\न\
	xor $2,$4,$4						\न\
	ldq $24,32($21)						\न\
	ldq $25,40($17)						\न\
								\न\
	ldq $27,40($18)						\न\
	ldq $28,40($19)						\न\
	ldq $0,40($20)						\न\
	xor $4,$5,$5		# 7 cycles from $5 load		\न\
								\न\
	stq $5,24($17)						\न\
	xor $6,$7,$7		# 7 cycles from $7 load		\न\
	ldq $1,40($21)						\न\
	ldq $2,48($17)						\न\
								\न\
	ldq $3,48($18)						\न\
	xor $7,$22,$22		# 7 cycles from $22 load	\न\
	ldq $4,48($19)						\न\
	xor $23,$24,$24		# 6 cycles from $24 load	\न\
								\न\
	ldq $5,48($20)						\न\
	xor $22,$24,$24						\न\
	ldq $6,48($21)						\न\
	xor $25,$27,$27		# 7 cycles from $27 load	\न\
								\न\
	stq $24,32($17)						\न\
	xor $27,$28,$28		# 8 cycles from $28 load	\न\
	ldq $7,56($17)						\न\
	xor $0,$1,$1		# 6 cycles from $1 load		\न\
								\न\
	ldq $22,56($18)						\न\
	ldq $23,56($19)						\न\
	ldq $24,56($20)						\न\
	ldq $25,56($21)						\न\
								\न\
	xor $28,$1,$1						\न\
	xor $2,$3,$3		# 9 cycles from $3 load		\न\
	xor $3,$4,$4		# 9 cycles from $4 load		\न\
	xor $5,$6,$6		# 8 cycles from $6 load		\न\
								\न\
	stq $1,40($17)						\न\
	xor $4,$6,$6						\न\
	xor $7,$22,$22		# 7 cycles from $22 load	\न\
	xor $23,$24,$24		# 6 cycles from $24 load	\न\
								\न\
	stq $6,48($17)						\न\
	xor $22,$24,$24						\न\
	subq $16,1,$16						\न\
	xor $24,$25,$25		# 8 cycles from $25 load	\न\
								\न\
	stq $25,56($17)						\न\
	addq $21,64,$21						\न\
	addq $20,64,$20						\न\
	addq $19,64,$19						\न\
								\न\
	addq $18,64,$18						\न\
	addq $17,64,$17						\न\
	bgt $16,5b						\न\
	ret							\न\
	.end xor_alpha_5					\न\
								\न\
	.align 3						\न\
	.ent xor_alpha_prefetch_2				\न\
xor_alpha_prefetch_2:						\न\
	.prologue 0						\न\
	srl $16, 6, $16						\न\
								\न\
	ldq $31, 0($17)						\न\
	ldq $31, 0($18)						\न\
								\न\
	ldq $31, 64($17)					\न\
	ldq $31, 64($18)					\न\
								\न\
	ldq $31, 128($17)					\न\
	ldq $31, 128($18)					\न\
								\न\
	ldq $31, 192($17)					\न\
	ldq $31, 192($18)					\न\
	.align 4						\न\
2:								\न\
	ldq $0,0($17)						\न\
	ldq $1,0($18)						\न\
	ldq $2,8($17)						\न\
	ldq $3,8($18)						\न\
								\न\
	ldq $4,16($17)						\न\
	ldq $5,16($18)						\न\
	ldq $6,24($17)						\न\
	ldq $7,24($18)						\न\
								\न\
	ldq $19,32($17)						\न\
	ldq $20,32($18)						\न\
	ldq $21,40($17)						\न\
	ldq $22,40($18)						\न\
								\न\
	ldq $23,48($17)						\न\
	ldq $24,48($18)						\न\
	ldq $25,56($17)						\न\
	ldq $27,56($18)						\न\
								\न\
	ldq $31,256($17)					\न\
	xor $0,$1,$0		# 8 cycles from $1 load		\न\
	ldq $31,256($18)					\न\
	xor $2,$3,$2						\न\
								\न\
	stq $0,0($17)						\न\
	xor $4,$5,$4						\न\
	stq $2,8($17)						\न\
	xor $6,$7,$6						\न\
								\न\
	stq $4,16($17)						\न\
	xor $19,$20,$19						\न\
	stq $6,24($17)						\न\
	xor $21,$22,$21						\न\
								\न\
	stq $19,32($17)						\न\
	xor $23,$24,$23						\न\
	stq $21,40($17)						\न\
	xor $25,$27,$25						\न\
								\न\
	stq $23,48($17)						\न\
	subq $16,1,$16						\न\
	stq $25,56($17)						\न\
	addq $17,64,$17						\न\
								\न\
	addq $18,64,$18						\न\
	bgt $16,2b						\न\
	ret							\न\
	.end xor_alpha_prefetch_2				\न\
								\न\
	.align 3						\न\
	.ent xor_alpha_prefetch_3				\न\
xor_alpha_prefetch_3:						\न\
	.prologue 0						\न\
	srl $16, 6, $16						\न\
								\न\
	ldq $31, 0($17)						\न\
	ldq $31, 0($18)						\न\
	ldq $31, 0($19)						\न\
								\न\
	ldq $31, 64($17)					\न\
	ldq $31, 64($18)					\न\
	ldq $31, 64($19)					\न\
								\न\
	ldq $31, 128($17)					\न\
	ldq $31, 128($18)					\न\
	ldq $31, 128($19)					\न\
								\न\
	ldq $31, 192($17)					\न\
	ldq $31, 192($18)					\न\
	ldq $31, 192($19)					\न\
	.align 4						\न\
3:								\न\
	ldq $0,0($17)						\न\
	ldq $1,0($18)						\न\
	ldq $2,0($19)						\न\
	ldq $3,8($17)						\न\
								\न\
	ldq $4,8($18)						\न\
	ldq $6,16($17)						\न\
	ldq $7,16($18)						\न\
	ldq $21,24($17)						\न\
								\न\
	ldq $22,24($18)						\न\
	ldq $24,32($17)						\न\
	ldq $25,32($18)						\न\
	ldq $5,8($19)						\न\
								\न\
	ldq $20,16($19)						\न\
	ldq $23,24($19)						\न\
	ldq $27,32($19)						\न\
	nop							\न\
								\न\
	xor $0,$1,$1		# 8 cycles from $0 load		\न\
	xor $3,$4,$4		# 7 cycles from $4 load		\न\
	xor $6,$7,$7		# 6 cycles from $7 load		\न\
	xor $21,$22,$22		# 5 cycles from $22 load	\न\
								\न\
	xor $1,$2,$2		# 9 cycles from $2 load		\न\
	xor $24,$25,$25		# 5 cycles from $25 load	\न\
	stq $2,0($17)						\न\
	xor $4,$5,$5		# 6 cycles from $5 load		\न\
								\न\
	stq $5,8($17)						\न\
	xor $7,$20,$20		# 7 cycles from $20 load	\न\
	stq $20,16($17)						\न\
	xor $22,$23,$23		# 7 cycles from $23 load	\न\
								\न\
	stq $23,24($17)						\न\
	xor $25,$27,$27		# 7 cycles from $27 load	\न\
	stq $27,32($17)						\न\
	nop							\न\
								\न\
	ldq $0,40($17)						\न\
	ldq $1,40($18)						\न\
	ldq $3,48($17)						\न\
	ldq $4,48($18)						\न\
								\न\
	ldq $6,56($17)						\न\
	ldq $7,56($18)						\न\
	ldq $2,40($19)						\न\
	ldq $5,48($19)						\न\
								\न\
	ldq $20,56($19)						\न\
	ldq $31,256($17)					\न\
	ldq $31,256($18)					\न\
	ldq $31,256($19)					\न\
								\न\
	xor $0,$1,$1		# 6 cycles from $1 load		\न\
	xor $3,$4,$4		# 5 cycles from $4 load		\न\
	xor $6,$7,$7		# 5 cycles from $7 load		\न\
	xor $1,$2,$2		# 4 cycles from $2 load		\न\
								\न\
	xor $4,$5,$5		# 5 cycles from $5 load		\न\
	xor $7,$20,$20		# 4 cycles from $20 load	\न\
	stq $2,40($17)						\न\
	subq $16,1,$16						\न\
								\न\
	stq $5,48($17)						\न\
	addq $19,64,$19						\न\
	stq $20,56($17)						\न\
	addq $18,64,$18						\न\
								\न\
	addq $17,64,$17						\न\
	bgt $16,3b						\न\
	ret							\न\
	.end xor_alpha_prefetch_3				\न\
								\न\
	.align 3						\न\
	.ent xor_alpha_prefetch_4				\न\
xor_alpha_prefetch_4:						\न\
	.prologue 0						\न\
	srl $16, 6, $16						\न\
								\न\
	ldq $31, 0($17)						\न\
	ldq $31, 0($18)						\न\
	ldq $31, 0($19)						\न\
	ldq $31, 0($20)						\न\
								\न\
	ldq $31, 64($17)					\न\
	ldq $31, 64($18)					\न\
	ldq $31, 64($19)					\न\
	ldq $31, 64($20)					\न\
								\न\
	ldq $31, 128($17)					\न\
	ldq $31, 128($18)					\न\
	ldq $31, 128($19)					\न\
	ldq $31, 128($20)					\न\
								\न\
	ldq $31, 192($17)					\न\
	ldq $31, 192($18)					\न\
	ldq $31, 192($19)					\न\
	ldq $31, 192($20)					\न\
	.align 4						\न\
4:								\न\
	ldq $0,0($17)						\न\
	ldq $1,0($18)						\न\
	ldq $2,0($19)						\न\
	ldq $3,0($20)						\न\
								\न\
	ldq $4,8($17)						\न\
	ldq $5,8($18)						\न\
	ldq $6,8($19)						\न\
	ldq $7,8($20)						\न\
								\न\
	ldq $21,16($17)						\न\
	ldq $22,16($18)						\न\
	ldq $23,16($19)						\न\
	ldq $24,16($20)						\न\
								\न\
	ldq $25,24($17)						\न\
	xor $0,$1,$1		# 6 cycles from $1 load		\न\
	ldq $27,24($18)						\न\
	xor $2,$3,$3		# 6 cycles from $3 load		\न\
								\न\
	ldq $0,24($19)						\न\
	xor $1,$3,$3						\न\
	ldq $1,24($20)						\न\
	xor $4,$5,$5		# 7 cycles from $5 load		\न\
								\न\
	stq $3,0($17)						\न\
	xor $6,$7,$7						\न\
	xor $21,$22,$22		# 7 cycles from $22 load	\न\
	xor $5,$7,$7						\न\
								\न\
	stq $7,8($17)						\न\
	xor $23,$24,$24		# 7 cycles from $24 load	\न\
	ldq $2,32($17)						\न\
	xor $22,$24,$24						\न\
								\न\
	ldq $3,32($18)						\न\
	ldq $4,32($19)						\न\
	ldq $5,32($20)						\न\
	xor $25,$27,$27		# 8 cycles from $27 load	\न\
								\न\
	ldq $6,40($17)						\न\
	ldq $7,40($18)						\न\
	ldq $21,40($19)						\न\
	ldq $22,40($20)						\न\
								\न\
	stq $24,16($17)						\न\
	xor $0,$1,$1		# 9 cycles from $1 load		\न\
	xor $2,$3,$3		# 5 cycles from $3 load		\न\
	xor $27,$1,$1						\न\
								\न\
	stq $1,24($17)						\न\
	xor $4,$5,$5		# 5 cycles from $5 load		\न\
	ldq $23,48($17)						\न\
	xor $3,$5,$5						\न\
								\न\
	ldq $24,48($18)						\न\
	ldq $25,48($19)						\न\
	ldq $27,48($20)						\न\
	ldq $0,56($17)						\न\
								\न\
	ldq $1,56($18)						\न\
	ldq $2,56($19)						\न\
	ldq $3,56($20)						\न\
	xor $6,$7,$7		# 8 cycles from $6 load		\न\
								\न\
	ldq $31,256($17)					\न\
	xor $21,$22,$22		# 8 cycles from $22 load	\न\
	ldq $31,256($18)					\न\
	xor $7,$22,$22						\न\
								\न\
	ldq $31,256($19)					\न\
	xor $23,$24,$24		# 6 cycles from $24 load	\न\
	ldq $31,256($20)					\न\
	xor $25,$27,$27		# 6 cycles from $27 load	\न\
								\न\
	stq $5,32($17)						\न\
	xor $24,$27,$27						\न\
	xor $0,$1,$1		# 7 cycles from $1 load		\न\
	xor $2,$3,$3		# 6 cycles from $3 load		\न\
								\न\
	stq $22,40($17)						\न\
	xor $1,$3,$3						\न\
	stq $27,48($17)						\न\
	subq $16,1,$16						\न\
								\न\
	stq $3,56($17)						\न\
	addq $20,64,$20						\न\
	addq $19,64,$19						\न\
	addq $18,64,$18						\न\
								\न\
	addq $17,64,$17						\न\
	bgt $16,4b						\न\
	ret							\न\
	.end xor_alpha_prefetch_4				\न\
								\न\
	.align 3						\न\
	.ent xor_alpha_prefetch_5				\न\
xor_alpha_prefetch_5:						\न\
	.prologue 0						\न\
	srl $16, 6, $16						\न\
								\न\
	ldq $31, 0($17)						\न\
	ldq $31, 0($18)						\न\
	ldq $31, 0($19)						\न\
	ldq $31, 0($20)						\न\
	ldq $31, 0($21)						\न\
								\न\
	ldq $31, 64($17)					\न\
	ldq $31, 64($18)					\न\
	ldq $31, 64($19)					\न\
	ldq $31, 64($20)					\न\
	ldq $31, 64($21)					\न\
								\न\
	ldq $31, 128($17)					\न\
	ldq $31, 128($18)					\न\
	ldq $31, 128($19)					\न\
	ldq $31, 128($20)					\न\
	ldq $31, 128($21)					\न\
								\न\
	ldq $31, 192($17)					\न\
	ldq $31, 192($18)					\न\
	ldq $31, 192($19)					\न\
	ldq $31, 192($20)					\न\
	ldq $31, 192($21)					\न\
	.align 4						\न\
5:								\न\
	ldq $0,0($17)						\न\
	ldq $1,0($18)						\न\
	ldq $2,0($19)						\न\
	ldq $3,0($20)						\न\
								\न\
	ldq $4,0($21)						\न\
	ldq $5,8($17)						\न\
	ldq $6,8($18)						\न\
	ldq $7,8($19)						\न\
								\न\
	ldq $22,8($20)						\न\
	ldq $23,8($21)						\न\
	ldq $24,16($17)						\न\
	ldq $25,16($18)						\न\
								\न\
	ldq $27,16($19)						\न\
	xor $0,$1,$1		# 6 cycles from $1 load		\न\
	ldq $28,16($20)						\न\
	xor $2,$3,$3		# 6 cycles from $3 load		\न\
								\न\
	ldq $0,16($21)						\न\
	xor $1,$3,$3						\न\
	ldq $1,24($17)						\न\
	xor $3,$4,$4		# 7 cycles from $4 load		\न\
								\न\
	stq $4,0($17)						\न\
	xor $5,$6,$6		# 7 cycles from $6 load		\न\
	xor $7,$22,$22		# 7 cycles from $22 load	\न\
	xor $6,$23,$23		# 7 cycles from $23 load	\न\
								\न\
	ldq $2,24($18)						\न\
	xor $22,$23,$23						\न\
	ldq $3,24($19)						\न\
	xor $24,$25,$25		# 8 cycles from $25 load	\न\
								\न\
	stq $23,8($17)						\न\
	xor $25,$27,$27		# 8 cycles from $27 load	\न\
	ldq $4,24($20)						\न\
	xor $28,$0,$0		# 7 cycles from $0 load		\न\
								\न\
	ldq $5,24($21)						\न\
	xor $27,$0,$0						\न\
	ldq $6,32($17)						\न\
	ldq $7,32($18)						\न\
								\न\
	stq $0,16($17)						\न\
	xor $1,$2,$2		# 6 cycles from $2 load		\न\
	ldq $22,32($19)						\न\
	xor $3,$4,$4		# 4 cycles from $4 load		\न\
								\न\
	ldq $23,32($20)						\न\
	xor $2,$4,$4						\न\
	ldq $24,32($21)						\न\
	ldq $25,40($17)						\न\
								\न\
	ldq $27,40($18)						\न\
	ldq $28,40($19)						\न\
	ldq $0,40($20)						\न\
	xor $4,$5,$5		# 7 cycles from $5 load		\न\
								\न\
	stq $5,24($17)						\न\
	xor $6,$7,$7		# 7 cycles from $7 load		\न\
	ldq $1,40($21)						\न\
	ldq $2,48($17)						\न\
								\न\
	ldq $3,48($18)						\न\
	xor $7,$22,$22		# 7 cycles from $22 load	\न\
	ldq $4,48($19)						\न\
	xor $23,$24,$24		# 6 cycles from $24 load	\न\
								\न\
	ldq $5,48($20)						\न\
	xor $22,$24,$24						\न\
	ldq $6,48($21)						\न\
	xor $25,$27,$27		# 7 cycles from $27 load	\न\
								\न\
	stq $24,32($17)						\न\
	xor $27,$28,$28		# 8 cycles from $28 load	\न\
	ldq $7,56($17)						\न\
	xor $0,$1,$1		# 6 cycles from $1 load		\न\
								\न\
	ldq $22,56($18)						\न\
	ldq $23,56($19)						\न\
	ldq $24,56($20)						\न\
	ldq $25,56($21)						\न\
								\न\
	ldq $31,256($17)					\न\
	xor $28,$1,$1						\न\
	ldq $31,256($18)					\न\
	xor $2,$3,$3		# 9 cycles from $3 load		\न\
								\न\
	ldq $31,256($19)					\न\
	xor $3,$4,$4		# 9 cycles from $4 load		\न\
	ldq $31,256($20)					\न\
	xor $5,$6,$6		# 8 cycles from $6 load		\न\
								\न\
	stq $1,40($17)						\न\
	xor $4,$6,$6						\न\
	xor $7,$22,$22		# 7 cycles from $22 load	\न\
	xor $23,$24,$24		# 6 cycles from $24 load	\न\
								\न\
	stq $6,48($17)						\न\
	xor $22,$24,$24						\न\
	ldq $31,256($21)					\न\
	xor $24,$25,$25		# 8 cycles from $25 load	\न\
								\न\
	stq $25,56($17)						\न\
	subq $16,1,$16						\न\
	addq $21,64,$21						\न\
	addq $20,64,$20						\न\
								\न\
	addq $19,64,$19						\न\
	addq $18,64,$18						\न\
	addq $17,64,$17						\न\
	bgt $16,5b						\न\
								\न\
	ret							\न\
	.end xor_alpha_prefetch_5				\न\
");

अटल काष्ठा xor_block_ढाँचा xor_block_alpha = अणु
	.name	= "alpha",
	.करो_2	= xor_alpha_2,
	.करो_3	= xor_alpha_3,
	.करो_4	= xor_alpha_4,
	.करो_5	= xor_alpha_5,
पूर्ण;

अटल काष्ठा xor_block_ढाँचा xor_block_alpha_prefetch = अणु
	.name	= "alpha prefetch",
	.करो_2	= xor_alpha_prefetch_2,
	.करो_3	= xor_alpha_prefetch_3,
	.करो_4	= xor_alpha_prefetch_4,
	.करो_5	= xor_alpha_prefetch_5,
पूर्ण;

/* For grins, also test the generic routines.  */
#समावेश <यंत्र-generic/xor.h>

#अघोषित XOR_TRY_TEMPLATES
#घोषणा XOR_TRY_TEMPLATES				\
	करो अणु						\
		xor_speed(&xor_block_8regs);		\
		xor_speed(&xor_block_32regs);		\
		xor_speed(&xor_block_alpha);		\
		xor_speed(&xor_block_alpha_prefetch);	\
	पूर्ण जबतक (0)

/* Force the use of alpha_prefetch अगर EV6, as it is signअगरicantly
   faster in the cold cache हाल.  */
#घोषणा XOR_SELECT_TEMPLATE(FASTEST) \
	(implver() == IMPLVER_EV6 ? &xor_block_alpha_prefetch : FASTEST)
