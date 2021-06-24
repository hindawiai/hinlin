<शैली गुरु>
/*
 * fixmap.h: compile-समय भव memory allocation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998 Ingo Molnar
 *
 * Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999
 * x86_32 and x86_64 पूर्णांकegration by Gustavo F. Paकरोvan, February 2009
 * Break out common bits to यंत्र-generic by Mark Salter, November 2013
 */

#अगर_अघोषित __ASM_GENERIC_FIXMAP_H
#घोषणा __ASM_GENERIC_FIXMAP_H

#समावेश <linux/bug.h>
#समावेश <linux/mm_types.h>

#घोषणा __fix_to_virt(x)	(FIXADDR_TOP - ((x) << PAGE_SHIFT))
#घोषणा __virt_to_fix(x)	((FIXADDR_TOP - ((x)&PAGE_MASK)) >> PAGE_SHIFT)

#अगर_अघोषित __ASSEMBLY__
/*
 * 'index to address' translation. If anyone tries to use the idx
 * directly without translation, we catch the bug with a शून्य-deference
 * kernel oops. Illegal ranges of incoming indices are caught too.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ fix_to_virt(स्थिर अचिन्हित पूर्णांक idx)
अणु
	BUILD_BUG_ON(idx >= __end_of_fixed_addresses);
	वापस __fix_to_virt(idx);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ virt_to_fix(स्थिर अचिन्हित दीर्घ vaddr)
अणु
	BUG_ON(vaddr >= FIXADDR_TOP || vaddr < FIXADDR_START);
	वापस __virt_to_fix(vaddr);
पूर्ण

/*
 * Provide some reasonable शेषs क्रम page flags.
 * Not all architectures use all of these dअगरferent types and some
 * architectures use dअगरferent names.
 */
#अगर_अघोषित FIXMAP_PAGE_NORMAL
#घोषणा FIXMAP_PAGE_NORMAL PAGE_KERNEL
#पूर्ण_अगर
#अगर !defined(FIXMAP_PAGE_RO) && defined(PAGE_KERNEL_RO)
#घोषणा FIXMAP_PAGE_RO PAGE_KERNEL_RO
#पूर्ण_अगर
#अगर_अघोषित FIXMAP_PAGE_NOCACHE
#घोषणा FIXMAP_PAGE_NOCACHE PAGE_KERNEL_NOCACHE
#पूर्ण_अगर
#अगर_अघोषित FIXMAP_PAGE_IO
#घोषणा FIXMAP_PAGE_IO PAGE_KERNEL_IO
#पूर्ण_अगर
#अगर_अघोषित FIXMAP_PAGE_CLEAR
#घोषणा FIXMAP_PAGE_CLEAR __pgprot(0)
#पूर्ण_अगर

#अगर_अघोषित set_fixmap
#घोषणा set_fixmap(idx, phys)				\
	__set_fixmap(idx, phys, FIXMAP_PAGE_NORMAL)
#पूर्ण_अगर

#अगर_अघोषित clear_fixmap
#घोषणा clear_fixmap(idx)			\
	__set_fixmap(idx, 0, FIXMAP_PAGE_CLEAR)
#पूर्ण_अगर

/* Return a poपूर्णांकer with offset calculated */
#घोषणा __set_fixmap_offset(idx, phys, flags)				\
(अणु									\
	अचिन्हित दीर्घ ________addr;					\
	__set_fixmap(idx, phys, flags);					\
	________addr = fix_to_virt(idx) + ((phys) & (PAGE_SIZE - 1));	\
	________addr;							\
पूर्ण)

#घोषणा set_fixmap_offset(idx, phys) \
	__set_fixmap_offset(idx, phys, FIXMAP_PAGE_NORMAL)

/*
 * Some hardware wants to get fixmapped without caching.
 */
#घोषणा set_fixmap_nocache(idx, phys) \
	__set_fixmap(idx, phys, FIXMAP_PAGE_NOCACHE)

#घोषणा set_fixmap_offset_nocache(idx, phys) \
	__set_fixmap_offset(idx, phys, FIXMAP_PAGE_NOCACHE)

/*
 * Some fixmaps are क्रम IO
 */
#घोषणा set_fixmap_io(idx, phys) \
	__set_fixmap(idx, phys, FIXMAP_PAGE_IO)

#घोषणा set_fixmap_offset_io(idx, phys) \
	__set_fixmap_offset(idx, phys, FIXMAP_PAGE_IO)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_GENERIC_FIXMAP_H */
