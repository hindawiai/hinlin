<शैली गुरु>
/*
 * linux/include/यंत्र-xtensa/pci.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_PCI_H
#घोषणा _XTENSA_PCI_H

/* Can be used to override the logic in pci_scan_bus क्रम skipping
 * alपढ़ोy-configured bus numbers - to be used क्रम buggy BIOSes
 * or architectures with incomplete PCI setup by the loader
 */

#घोषणा pcibios_assign_all_busses()	0

/* Assume some values. (We should revise them, अगर necessary) */

#घोषणा PCIBIOS_MIN_IO		0x2000
#घोषणा PCIBIOS_MIN_MEM		0x10000000

/* Dynamic DMA mapping stuff.
 * Xtensa has everything mapped अटलally like x86.
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/पन.स>

/* The PCI address space करोes equal the physical memory address space.
 * The networking and block device layers use this boolean क्रम bounce buffer
 * decisions.
 */

/* Tell PCI code what kind of PCI resource mappings we support */
#घोषणा HAVE_PCI_MMAP			1
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE	1
#घोषणा arch_can_pci_mmap_io()		1

/* Generic PCI */
#समावेश <यंत्र-generic/pci.h>

#पूर्ण_अगर	/* _XTENSA_PCI_H */
