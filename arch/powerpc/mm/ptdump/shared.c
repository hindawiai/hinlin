<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * From split of dump_linuxpagetables.c
 * Copyright 2016, Rashmica Gupta, IBM Corp.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pgtable.h>

#समावेश "ptdump.h"

अटल स्थिर काष्ठा flag_info flag_array[] = अणु
	अणु
		.mask	= _PAGE_USER,
		.val	= _PAGE_USER,
		.set	= "user",
		.clear	= "    ",
	पूर्ण, अणु
		.mask	= _PAGE_RW,
		.val	= _PAGE_RW,
		.set	= "rw",
		.clear	= "r ",
	पूर्ण, अणु
		.mask	= _PAGE_EXEC,
		.val	= _PAGE_EXEC,
		.set	= " X ",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= _PAGE_PRESENT,
		.val	= _PAGE_PRESENT,
		.set	= "present",
		.clear	= "       ",
	पूर्ण, अणु
		.mask	= _PAGE_COHERENT,
		.val	= _PAGE_COHERENT,
		.set	= "coherent",
		.clear	= "        ",
	पूर्ण, अणु
		.mask	= _PAGE_GUARDED,
		.val	= _PAGE_GUARDED,
		.set	= "guarded",
		.clear	= "       ",
	पूर्ण, अणु
		.mask	= _PAGE_सूचीTY,
		.val	= _PAGE_सूचीTY,
		.set	= "dirty",
		.clear	= "     ",
	पूर्ण, अणु
		.mask	= _PAGE_ACCESSED,
		.val	= _PAGE_ACCESSED,
		.set	= "accessed",
		.clear	= "        ",
	पूर्ण, अणु
		.mask	= _PAGE_WRITETHRU,
		.val	= _PAGE_WRITETHRU,
		.set	= "write through",
		.clear	= "             ",
	पूर्ण, अणु
		.mask	= _PAGE_NO_CACHE,
		.val	= _PAGE_NO_CACHE,
		.set	= "no cache",
		.clear	= "        ",
	पूर्ण, अणु
		.mask	= _PAGE_SPECIAL,
		.val	= _PAGE_SPECIAL,
		.set	= "special",
	पूर्ण
पूर्ण;

काष्ठा pgtable_level pg_level[5] = अणु
	अणु
	पूर्ण, अणु /* pgd */
		.flag	= flag_array,
		.num	= ARRAY_SIZE(flag_array),
	पूर्ण, अणु /* pud */
		.flag	= flag_array,
		.num	= ARRAY_SIZE(flag_array),
	पूर्ण, अणु /* pmd */
		.flag	= flag_array,
		.num	= ARRAY_SIZE(flag_array),
	पूर्ण, अणु /* pte */
		.flag	= flag_array,
		.num	= ARRAY_SIZE(flag_array),
	पूर्ण,
पूर्ण;
