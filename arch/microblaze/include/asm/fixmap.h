<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fixmap.h: compile-समय भव memory allocation
 *
 * Copyright (C) 1998 Ingo Molnar
 *
 * Copyright 2008 Freescale Semiconductor Inc.
 *   Port to घातerpc added by Kumar Gala
 *
 * Copyright 2011 Michal Simek <monstr@monstr.eu>
 * Copyright 2011 PetaLogix Qld Pty Ltd
 *   Port to Microblaze
 */

#अगर_अघोषित _ASM_FIXMAP_H
#घोषणा _ASM_FIXMAP_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/kernel.h>
#समावेश <यंत्र/page.h>
#अगर_घोषित CONFIG_HIGHMEM
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/kmap_size.h>
#पूर्ण_अगर

#घोषणा FIXADDR_TOP	((अचिन्हित दीर्घ)(-PAGE_SIZE))

/*
 * Here we define all the compile-समय 'special' भव
 * addresses. The poपूर्णांक is to have a स्थिरant address at
 * compile समय, but to set the physical address only
 * in the boot process. We allocate these special addresses
 * from the end of भव memory (0xfffff000) backwards.
 * Also this lets us करो fail-safe vदो_स्मृति(), we
 * can guarantee that these special addresses and
 * vदो_स्मृति()-ed addresses never overlap.
 *
 * these 'compile-time allocated' memory buffers are
 * fixed-size 4k pages. (or larger अगर used with an increment
 * highger than 1) use fixmap_set(idx,phys) to associate
 * physical memory with fixmap indices.
 *
 * TLB entries of such buffers will not be flushed across
 * task चयनes.
 */
क्रमागत fixed_addresses अणु
	FIX_HOLE,
#अगर_घोषित CONFIG_HIGHMEM
	FIX_KMAP_BEGIN,	/* reserved pte's क्रम temporary kernel mappings */
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * num_possible_cpus()) - 1,
#पूर्ण_अगर
	__end_of_fixed_addresses
पूर्ण;

बाह्य व्योम __set_fixmap(क्रमागत fixed_addresses idx,
					phys_addr_t phys, pgprot_t flags);

#घोषणा __FIXADDR_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START		(FIXADDR_TOP - __FIXADDR_SIZE)

#घोषणा FIXMAP_PAGE_NOCACHE PAGE_KERNEL_CI

#समावेश <यंत्र-generic/fixmap.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर
