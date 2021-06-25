<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * File created by Kanoj Sarcar 06/06/00.
 * Copyright 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित __ASM_SN_MAPPED_KERNEL_H
#घोषणा __ASM_SN_MAPPED_KERNEL_H

#समावेश <linux/mmzone.h>

/*
 * Note on how mapped kernels work: the text and data section is
 * compiled at cksseg segment (LOADADDR = 0xc001c000), and the
 * init/setup/data section माला_लो a 16M भव address bump in the
 * ld.script file (so that tlblo0 and tlblo1 maps the sections).
 * The vmlinux.64 section addresses are put in the xkseg range
 * using the change-addresses makefile option. Use elfdump -of
 * on IRIX to see where the sections go. The Origin loader loads
 * the two sections contiguously in physical memory. The loader
 * sets the entry poपूर्णांक पूर्णांकo kernel_entry using a xkphys address,
 * but instead of using 0xa800000001160000, it uses the address
 * 0xa800000000160000, which is where it physically loaded that
 * code. So no jumps can be करोne beक्रमe we have चयनed to using
 * cksseg addresses.
 */
#समावेश <यंत्र/addrspace.h>

#घोषणा REP_BASE	CAC_BASE

#अगर_घोषित CONFIG_MAPPED_KERNEL

#घोषणा MAPPED_ADDR_RO_TO_PHYS(x)	(x - REP_BASE)
#घोषणा MAPPED_ADDR_RW_TO_PHYS(x)	(x - REP_BASE - 16777216)

#घोषणा MAPPED_KERN_RO_PHYSBASE(n) (hub_data(n)->kern_vars.kv_ro_baseaddr)
#घोषणा MAPPED_KERN_RW_PHYSBASE(n) (hub_data(n)->kern_vars.kv_rw_baseaddr)

#घोषणा MAPPED_KERN_RO_TO_PHYS(x) \
				((अचिन्हित दीर्घ)MAPPED_ADDR_RO_TO_PHYS(x) | \
				MAPPED_KERN_RO_PHYSBASE(get_nasid()))
#घोषणा MAPPED_KERN_RW_TO_PHYS(x) \
				((अचिन्हित दीर्घ)MAPPED_ADDR_RW_TO_PHYS(x) | \
				MAPPED_KERN_RW_PHYSBASE(get_nasid()))

#अन्यथा /* CONFIG_MAPPED_KERNEL */

#घोषणा MAPPED_KERN_RO_TO_PHYS(x)	(x - REP_BASE)
#घोषणा MAPPED_KERN_RW_TO_PHYS(x)	(x - REP_BASE)

#पूर्ण_अगर /* CONFIG_MAPPED_KERNEL */

#घोषणा MAPPED_KERN_RO_TO_K0(x) PHYS_TO_K0(MAPPED_KERN_RO_TO_PHYS(x))
#घोषणा MAPPED_KERN_RW_TO_K0(x) PHYS_TO_K0(MAPPED_KERN_RW_TO_PHYS(x))

#पूर्ण_अगर /* __ASM_SN_MAPPED_KERNEL_H  */
