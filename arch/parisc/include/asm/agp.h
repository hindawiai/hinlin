<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_AGP_H
#घोषणा _ASM_PARISC_AGP_H

/*
 * PARISC specअगरic AGP definitions.
 * Copyright (c) 2006 Kyle McMartin <kyle@parisc-linux.org>
 *
 */

#घोषणा map_page_पूर्णांकo_agp(page)		/* nothing */
#घोषणा unmap_page_from_agp(page)	/* nothing */
#घोषणा flush_agp_cache()		mb()

/* GATT allocation. Returns/accepts GATT kernel भव address. */
#घोषणा alloc_gatt_pages(order)		\
	((अक्षर *)__get_मुक्त_pages(GFP_KERNEL, (order)))
#घोषणा मुक्त_gatt_pages(table, order)	\
	मुक्त_pages((अचिन्हित दीर्घ)(table), (order))

#पूर्ण_अगर /* _ASM_PARISC_AGP_H */
