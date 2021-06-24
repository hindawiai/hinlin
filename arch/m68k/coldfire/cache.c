<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	cache.c -- general ColdFire Cache मुख्यtenance code
 *
 *	Copyright (C) 2010, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>

/***************************************************************************/
#अगर_घोषित CACHE_PUSH
/***************************************************************************/

/*
 *	Use cpushl to push all dirty cache lines back to memory.
 *	Older versions of GAS करोn't seem to know how to generate the
 *	ColdFire cpushl inकाष्ठाion... Oh well, bit stuff it क्रम now.
 */

व्योम mcf_cache_push(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"clrl	%%d0\n\t"
		"1:\n\t"
		"movel	%%d0,%%a0\n\t"
		"2:\n\t"
		".word	0xf468\n\t"
		"addl	%0,%%a0\n\t"
		"cmpl	%1,%%a0\n\t"
		"blt	2b\n\t"
		"addql	#1,%%d0\n\t"
		"cmpil	%2,%%d0\n\t"
		"bne	1b\n\t"
		: /* No output */
		: "i" (CACHE_LINE_SIZE),
		  "i" (DCACHE_SIZE / CACHE_WAYS),
		  "i" (CACHE_WAYS)
		: "d0", "a0" );
पूर्ण

/***************************************************************************/
#पूर्ण_अगर /* CACHE_PUSH */
/***************************************************************************/
