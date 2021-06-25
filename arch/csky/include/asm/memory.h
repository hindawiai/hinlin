<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_MEMORY_H
#घोषणा __ASM_CSKY_MEMORY_H

#समावेश <linux/compiler.h>
#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>
#समावेश <linux/sizes.h>

#घोषणा FIXADDR_TOP	_AC(0xffffc000, UL)
#घोषणा PKMAP_BASE	_AC(0xff800000, UL)
#घोषणा VMALLOC_START	(PAGE_OFFSET + LOWMEM_LIMIT + (PAGE_SIZE * 8))
#घोषणा VMALLOC_END	(PKMAP_BASE - (PAGE_SIZE * 2))

#अगर_घोषित CONFIG_HAVE_TCM
#अगर_घोषित CONFIG_HAVE_DTCM
#घोषणा TCM_NR_PAGES	(CONFIG_ITCM_NR_PAGES + CONFIG_DTCM_NR_PAGES)
#अन्यथा
#घोषणा TCM_NR_PAGES	(CONFIG_ITCM_NR_PAGES)
#पूर्ण_अगर
#घोषणा FIXADDR_TCM	_AC(FIXADDR_TOP - (TCM_NR_PAGES * PAGE_SIZE), UL)
#पूर्ण_अगर

#पूर्ण_अगर
