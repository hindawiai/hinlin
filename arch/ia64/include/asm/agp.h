<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_AGP_H
#घोषणा _ASM_IA64_AGP_H

/*
 * IA-64 specअगरic AGP definitions.
 *
 * Copyright (C) 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

/*
 * To aव्योम memory-attribute aliasing issues, we require that the AGPGART engine operate
 * in coherent mode, which lets us map the AGP memory as normal (ग_लिखो-back) memory
 * (unlike x86, where it माला_लो mapped "write-coalescing").
 */
#घोषणा map_page_पूर्णांकo_agp(page)		करो अणु पूर्ण जबतक (0)
#घोषणा unmap_page_from_agp(page)	करो अणु पूर्ण जबतक (0)
#घोषणा flush_agp_cache()		mb()

/* GATT allocation. Returns/accepts GATT kernel भव address. */
#घोषणा alloc_gatt_pages(order)		\
	((अक्षर *)__get_मुक्त_pages(GFP_KERNEL, (order)))
#घोषणा मुक्त_gatt_pages(table, order)	\
	मुक्त_pages((अचिन्हित दीर्घ)(table), (order))

#पूर्ण_अगर /* _ASM_IA64_AGP_H */
