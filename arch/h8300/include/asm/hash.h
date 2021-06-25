<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_HASH_H
#घोषणा _ASM_HASH_H

/*
 * The later H8SX models have a 32x32-bit multiply, but the H8/300H
 * and H8S have only 16x16->32.  Since it's tolerably compact, this is
 * basically an अंतरभूतd version of the __mulsi3 code.  Since the inमाला_दो
 * are not expected to be small, it's also simplfied by skipping the
 * early-out checks.
 *
 * (Since neither CPU has any multi-bit shअगरt inकाष्ठाions, a
 * shअगरt-and-add version is a non-starter.)
 *
 * TODO: come up with an arch-specअगरic version of the hashing in fs/namei.c,
 * since that is heavily dependent on rotates.  Which, as mentioned, suck
 * horribly on H8.
 */

#अगर defined(CONFIG_CPU_H300H) || defined(CONFIG_CPU_H8S)

#घोषणा HAVE_ARCH__HASH_32 1

/*
 * Multiply by k = 0x61C88647.  Fitting this पूर्णांकo three रेजिस्टरs requires
 * one extra inकाष्ठाion, but reducing रेजिस्टर pressure will probably
 * make that back and then some.
 *
 * GCC यंत्र note: %e1 is the high half of opeअक्रम %1, जबतक %f1 is the
 * low half.  So अगर %1 is er4, then %e1 is e4 and %f1 is r4.
 *
 * This has been deचिन्हित to modअगरy x in place, since that's the most
 * common usage, but preserve k, since hash_64() makes two calls in
 * quick succession.
 */
अटल अंतरभूत u32 __attribute_स्थिर__ __hash_32(u32 x)
अणु
	u32 temp;

	यंत्र(   "mov.w	%e1,%f0"
	"\n	mulxu.w	%f2,%0"		/* klow * xhigh */
	"\n	mov.w	%f0,%e1"	/* The extra inकाष्ठाion */
	"\n	mov.w	%f1,%f0"
	"\n	mulxu.w	%e2,%0"		/* khigh * xlow */
	"\n	add.w	%e1,%f0"
	"\n	mulxu.w	%f2,%1"		/* klow * xlow */
	"\n	add.w	%f0,%e1"
	: "=&r" (temp), "=r" (x)
	: "%r" (GOLDEN_RATIO_32), "1" (x));
	वापस x;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_HASH_H */
