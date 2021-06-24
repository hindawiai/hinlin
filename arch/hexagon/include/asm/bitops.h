<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Bit operations क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_BITOPS_H
#घोषणा _ASM_BITOPS_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/atomic.h>
#समावेश <यंत्र/barrier.h>

#अगर_घोषित __KERNEL__

/*
 * The offset calculations क्रम these are based on BITS_PER_LONG == 32
 * (i.e. I get to shअगरt by #5-2 (32 bits per दीर्घ, 4 bytes per access),
 * mask by 0x0000001F)
 *
 * Typically, R10 is clobbered क्रम address, R11 bit nr, and R12 is temp
 */

/**
 * test_and_clear_bit - clear a bit and वापस its old value
 * @nr:  bit number to clear
 * @addr:  poपूर्णांकer to memory
 */
अटल अंतरभूत पूर्णांक test_and_clear_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक oldval;

	__यंत्र__ __अस्थिर__ (
	"	{R10 = %1; R11 = asr(%2,#5); }\n"
	"	{R10 += asl(R11,#2); R11 = and(%2,#0x1f)}\n"
	"1:	R12 = memw_locked(R10);\n"
	"	{ P0 = tstbit(R12,R11); R12 = clrbit(R12,R11); }\n"
	"	memw_locked(R10,P1) = R12;\n"
	"	{if (!P1) jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&r" (oldval)
	: "r" (addr), "r" (nr)
	: "r10", "r11", "r12", "p0", "p1", "memory"
	);

	वापस oldval;
पूर्ण

/**
 * test_and_set_bit - set a bit and वापस its old value
 * @nr:  bit number to set
 * @addr:  poपूर्णांकer to memory
 */
अटल अंतरभूत पूर्णांक test_and_set_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक oldval;

	__यंत्र__ __अस्थिर__ (
	"	{R10 = %1; R11 = asr(%2,#5); }\n"
	"	{R10 += asl(R11,#2); R11 = and(%2,#0x1f)}\n"
	"1:	R12 = memw_locked(R10);\n"
	"	{ P0 = tstbit(R12,R11); R12 = setbit(R12,R11); }\n"
	"	memw_locked(R10,P1) = R12;\n"
	"	{if (!P1) jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&r" (oldval)
	: "r" (addr), "r" (nr)
	: "r10", "r11", "r12", "p0", "p1", "memory"
	);


	वापस oldval;

पूर्ण

/**
 * test_and_change_bit - toggle a bit and वापस its old value
 * @nr:  bit number to set
 * @addr:  poपूर्णांकer to memory
 */
अटल अंतरभूत पूर्णांक test_and_change_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक oldval;

	__यंत्र__ __अस्थिर__ (
	"	{R10 = %1; R11 = asr(%2,#5); }\n"
	"	{R10 += asl(R11,#2); R11 = and(%2,#0x1f)}\n"
	"1:	R12 = memw_locked(R10);\n"
	"	{ P0 = tstbit(R12,R11); R12 = togglebit(R12,R11); }\n"
	"	memw_locked(R10,P1) = R12;\n"
	"	{if (!P1) jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&r" (oldval)
	: "r" (addr), "r" (nr)
	: "r10", "r11", "r12", "p0", "p1", "memory"
	);

	वापस oldval;

पूर्ण

/*
 * Atomic, but करोesn't care about the वापस value.
 * Reग_लिखो later to save a cycle or two.
 */

अटल अंतरभूत व्योम clear_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	test_and_clear_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम set_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	test_and_set_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम change_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	test_and_change_bit(nr, addr);
पूर्ण


/*
 * These are allowed to be non-atomic.  In fact the generic flavors are
 * in non-atomic.h.  Would it be better to use पूर्णांकrinsics क्रम this?
 *
 * OK, ग_लिखोs in our architecture करो not invalidate LL/SC, so this has to
 * be atomic, particularly क्रम things like slab_lock and slab_unlock.
 *
 */
अटल अंतरभूत व्योम __clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	test_and_clear_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम __set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	test_and_set_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम __change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	test_and_change_bit(nr, addr);
पूर्ण

/*  Apparently, at least some of these are allowed to be non-atomic  */
अटल अंतरभूत पूर्णांक __test_and_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस test_and_clear_bit(nr, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __test_and_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस test_and_set_bit(nr, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __test_and_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस test_and_change_bit(nr, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __test_bit(पूर्णांक nr, स्थिर अस्थिर अचिन्हित दीर्घ *addr)
अणु
	पूर्णांक retval;

	यंत्र अस्थिर(
	"{P0 = tstbit(%1,%2); if (P0.new) %0 = #1; if (!P0.new) %0 = #0;}\n"
	: "=&r" (retval)
	: "r" (addr[BIT_WORD(nr)]), "r" (nr % BITS_PER_LONG)
	: "p0"
	);

	वापस retval;
पूर्ण

#घोषणा test_bit(nr, addr) __test_bit(nr, addr)

/*
 * ffz - find first zero in word.
 * @word: The word to search
 *
 * Undefined अगर no zero exists, so code should check against ~0UL first.
 */
अटल अंतरभूत दीर्घ ffz(पूर्णांक x)
अणु
	पूर्णांक r;

	यंत्र("%0 = ct1(%1);\n"
		: "=&r" (r)
		: "r" (x));
	वापस r;
पूर्ण

/*
 * fls - find last (most-signअगरicant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
अटल अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक r;

	यंत्र("{ %0 = cl0(%1);}\n"
		"%0 = sub(#32,%0);\n"
		: "=&r" (r)
		: "r" (x)
		: "p0");

	वापस r;
पूर्ण

/*
 * ffs - find first bit set
 * @x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, thereक्रमe
 * dअगरfers in spirit from the above ffz (man ffs).
 */
अटल अंतरभूत पूर्णांक ffs(पूर्णांक x)
अणु
	पूर्णांक r;

	यंत्र("{ P0 = cmp.eq(%1,#0); %0 = ct0(%1);}\n"
		"{ if (P0) %0 = #0; if (!P0) %0 = add(%0,#1);}\n"
		: "=&r" (r)
		: "r" (x)
		: "p0");

	वापस r;
पूर्ण

/*
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined अगर no bit exists, so code should check against 0 first.
 *
 * bits_per_दीर्घ assumed to be 32
 * numbering starts at 0 I think (instead of 1 like ffs)
 */
अटल अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
	पूर्णांक num;

	यंत्र("%0 = ct0(%1);\n"
		: "=&r" (num)
		: "r" (word));

	वापस num;
पूर्ण

/*
 * __fls - find last (most-signअगरicant) set bit in a दीर्घ word
 * @word: the word to search
 *
 * Undefined अगर no set bit exists, so code should check against 0 first.
 * bits_per_दीर्घ assumed to be 32
 */
अटल अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ word)
अणु
	पूर्णांक num;

	यंत्र("%0 = cl0(%1);\n"
		"%0 = sub(#31,%0);\n"
		: "=&r" (num)
		: "r" (word));

	वापस num;
पूर्ण

#समावेश <यंत्र-generic/bitops/lock.h>
#समावेश <यंत्र-generic/bitops/find.h>

#समावेश <यंत्र-generic/bitops/fls64.h>
#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/hweight.h>

#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic.h>

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
