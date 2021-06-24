<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __VIRT_CONVERT__
#घोषणा __VIRT_CONVERT__

/*
 * Macros used क्रम converting between भव and physical mappings.
 */

#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>
#समावेश <linux/mmzone.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>

/*
 * Change भव addresses to physical addresses and vv.
 */
#घोषणा virt_to_phys virt_to_phys
अटल अंतरभूत अचिन्हित दीर्घ virt_to_phys(व्योम *address)
अणु
	वापस __pa(address);
पूर्ण

#घोषणा phys_to_virt phys_to_virt
अटल अंतरभूत व्योम *phys_to_virt(अचिन्हित दीर्घ address)
अणु
	वापस __va(address);
पूर्ण

/* Permanent address of a page. */
#घोषणा page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

/*
 * IO bus memory addresses are 1:1 with the physical address,
 */
#घोषणा virt_to_bus virt_to_phys
#घोषणा bus_to_virt phys_to_virt

#पूर्ण_अगर
#पूर्ण_अगर
