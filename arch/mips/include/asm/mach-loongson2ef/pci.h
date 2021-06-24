<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2008 Zhang Le <r0bertz@gentoo.org>
 * Copyright (c) 2009 Wu Zhangjin <wuzhangjin@gmail.com>
 */

#अगर_अघोषित __ASM_MACH_LOONGSON2EF_PCI_H_
#घोषणा __ASM_MACH_LOONGSON2EF_PCI_H_

बाह्य काष्ठा pci_ops loongson_pci_ops;

/* this is an offset from mips_io_port_base */
#घोषणा LOONGSON_PCI_IO_START	0x00004000UL

#अगर_घोषित CONFIG_CPU_SUPPORTS_ADDRWINCFG

/*
 * we use address winकरोw2 to map cpu address space to pci space
 * winकरोw2: cpu [1G, 2G] -> pci [1G, 2G]
 * why not use winकरोw 0 & 1? because they are used by cpu when booting.
 * winकरोw0: cpu [0, 256M] -> ddr [0, 256M]
 * winकरोw1: cpu [256M, 512M] -> pci [256M, 512M]
 */

/* the smallest LOONGSON_CPU_MEM_SRC can be 512M */
#घोषणा LOONGSON_CPU_MEM_SRC	0x40000000ul		/* 1G */
#घोषणा LOONGSON_PCI_MEM_DST	LOONGSON_CPU_MEM_SRC

#घोषणा LOONGSON_PCI_MEM_START	LOONGSON_PCI_MEM_DST
#घोषणा LOONGSON_PCI_MEM_END	(0x80000000ul-1)	/* 2G */

#घोषणा MMAP_CPUTOPCI_SIZE	(LOONGSON_PCI_MEM_END - \
					LOONGSON_PCI_MEM_START + 1)

#अन्यथा	/* loongson2f/32bit & loongson2e */

/* this pci memory space is mapped by pcimap in pci.c */
#घोषणा LOONGSON_PCI_MEM_START	LOONGSON_PCILO1_BASE
#घोषणा LOONGSON_PCI_MEM_END	(LOONGSON_PCILO1_BASE + 0x04000000 * 2)

/* this is an offset from mips_io_port_base */
#घोषणा LOONGSON_PCI_IO_START	0x00004000UL

#पूर्ण_अगर	/* !CONFIG_CPU_SUPPORTS_ADDRWINCFG */

#पूर्ण_अगर /* !__ASM_MACH_LOONGSON2EF_PCI_H_ */
