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
		.mask	= _PAGE_PRIVILEGED,
		.val	= 0,
		.set	= "user",
		.clear	= "    ",
	पूर्ण, अणु
		.mask	= _PAGE_READ,
		.val	= _PAGE_READ,
		.set	= "r",
		.clear	= " ",
	पूर्ण, अणु
		.mask	= _PAGE_WRITE,
		.val	= _PAGE_WRITE,
		.set	= "w",
		.clear	= " ",
	पूर्ण, अणु
		.mask	= _PAGE_EXEC,
		.val	= _PAGE_EXEC,
		.set	= " X ",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= _PAGE_PTE,
		.val	= _PAGE_PTE,
		.set	= "pte",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= _PAGE_PRESENT,
		.val	= _PAGE_PRESENT,
		.set	= "valid",
		.clear	= "     ",
	पूर्ण, अणु
		.mask	= _PAGE_PRESENT | _PAGE_INVALID,
		.val	= 0,
		.set	= "       ",
		.clear	= "present",
	पूर्ण, अणु
		.mask	= H_PAGE_HASHPTE,
		.val	= H_PAGE_HASHPTE,
		.set	= "hpte",
		.clear	= "    ",
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
		.mask	= _PAGE_NON_IDEMPOTENT,
		.val	= _PAGE_NON_IDEMPOTENT,
		.set	= "non-idempotent",
		.clear	= "              ",
	पूर्ण, अणु
		.mask	= _PAGE_TOLERANT,
		.val	= _PAGE_TOLERANT,
		.set	= "tolerant",
		.clear	= "        ",
	पूर्ण, अणु
		.mask	= H_PAGE_BUSY,
		.val	= H_PAGE_BUSY,
		.set	= "busy",
	पूर्ण, अणु
#अगर_घोषित CONFIG_PPC_64K_PAGES
		.mask	= H_PAGE_COMBO,
		.val	= H_PAGE_COMBO,
		.set	= "combo",
	पूर्ण, अणु
		.mask	= H_PAGE_4K_PFN,
		.val	= H_PAGE_4K_PFN,
		.set	= "4K_pfn",
	पूर्ण, अणु
#अन्यथा /* CONFIG_PPC_64K_PAGES */
		.mask	= H_PAGE_F_GIX,
		.val	= H_PAGE_F_GIX,
		.set	= "f_gix",
		.is_val	= true,
		.shअगरt	= H_PAGE_F_GIX_SHIFT,
	पूर्ण, अणु
		.mask	= H_PAGE_F_SECOND,
		.val	= H_PAGE_F_SECOND,
		.set	= "f_second",
	पूर्ण, अणु
#पूर्ण_अगर /* CONFIG_PPC_64K_PAGES */
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
