<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_VADDRS_H
#घोषणा _SPARC_VADDRS_H

#समावेश <यंत्र/head.h>

/*
 * यंत्र/vaddrs.h:  Here we define the भव addresses at
 *                      which important things will be mapped.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 2000 Anton Blanअक्षरd (anton@samba.org)
 */

#घोषणा SRMMU_MAXMEM		0x0c000000

#घोषणा SRMMU_NOCACHE_VADDR	(KERNBASE + SRMMU_MAXMEM)
				/* = 0x0fc000000 */
/* XXX Empiricals - this needs to go away - KMW */
#घोषणा SRMMU_MIN_NOCACHE_PAGES (550)
#घोषणा SRMMU_MAX_NOCACHE_PAGES	(1280)

/* The following स्थिरant is used in mm/srmmu.c::srmmu_nocache_calcsize()
 * to determine the amount of memory that will be reserved as nocache:
 *
 * 256 pages will be taken as nocache per each
 * SRMMU_NOCACHE_ALCRATIO MB of प्रणाली memory.
 *
 * limits enक्रमced:	nocache minimum = 256 pages
 *			nocache maximum = 1280 pages
 */
#घोषणा SRMMU_NOCACHE_ALCRATIO	64	/* 256 pages per 64MB of प्रणाली RAM */

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/kmap_size.h>

क्रमागत fixed_addresses अणु
	FIX_HOLE,
#अगर_घोषित CONFIG_HIGHMEM
	FIX_KMAP_BEGIN,
	FIX_KMAP_END = (KM_MAX_IDX * NR_CPUS),
#पूर्ण_अगर
	__end_of_fixed_addresses
पूर्ण;
#पूर्ण_अगर

/* Leave one empty page between IO pages at 0xfd000000 and
 * the top of the fixmap.
 */
#घोषणा FIXADDR_TOP		(0xfcfff000UL)
#घोषणा FIXADDR_SIZE		((FIX_KMAP_END + 1) << PAGE_SHIFT)
#घोषणा FIXADDR_START		(FIXADDR_TOP - FIXADDR_SIZE)

#घोषणा __fix_to_virt(x)        (FIXADDR_TOP - ((x) << PAGE_SHIFT))

#घोषणा SUN4M_IOBASE_VADDR	0xfd000000 /* Base क्रम mapping pages */
#घोषणा IOBASE_VADDR		0xfe000000
#घोषणा IOBASE_END		0xfe600000

#घोषणा KADB_DEBUGGER_BEGVM	0xffc00000 /* Where kern debugger is in virt-mem */
#घोषणा KADB_DEBUGGER_ENDVM	0xffd00000
#घोषणा DEBUG_FIRSTVADDR	KADB_DEBUGGER_BEGVM
#घोषणा DEBUG_LASTVADDR		KADB_DEBUGGER_ENDVM

#घोषणा LINUX_OPPROM_BEGVM	0xffd00000
#घोषणा LINUX_OPPROM_ENDVM	0xfff00000

#घोषणा DVMA_VADDR		0xfff00000 /* Base area of the DVMA on suns */
#घोषणा DVMA_END		0xfffc0000

#पूर्ण_अगर /* !(_SPARC_VADDRS_H) */
