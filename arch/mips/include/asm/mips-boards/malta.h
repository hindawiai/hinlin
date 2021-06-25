<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 *
 * Defines of the Malta board specअगरic address-MAP, रेजिस्टरs, etc.
 */
#अगर_अघोषित __ASM_MIPS_BOARDS_MALTA_H
#घोषणा __ASM_MIPS_BOARDS_MALTA_H

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mips-boards/msc01_pci.h>
#समावेश <यंत्र/gt64120.h>

/* Mips पूर्णांकerrupt controller found in SOCit variations */
#घोषणा MIPS_MSC01_IC_REG_BASE		0x1bc40000
#घोषणा MIPS_SOCITSC_IC_REG_BASE	0x1ffa0000

/*
 * Malta I/O ports base address क्रम the Galileo GT64120 and Algorithmics
 * Bonito प्रणाली controllers.
 */
#घोषणा MALTA_GT_PORT_BASE	get_gt_port_base(GT_PCI0IOLD_OFS)
#घोषणा MALTA_BONITO_PORT_BASE	((अचिन्हित दीर्घ)ioremap (0x1fd00000, 0x10000))
#घोषणा MALTA_MSC_PORT_BASE	get_msc_port_base(MSC01_PCI_SC2PIOBASL)

अटल अंतरभूत अचिन्हित दीर्घ get_gt_port_base(अचिन्हित दीर्घ reg)
अणु
	अचिन्हित दीर्घ addr;
	addr = GT_READ(reg);
	वापस (अचिन्हित दीर्घ) ioremap (((addr & 0xffff) << 21), 0x10000);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_msc_port_base(अचिन्हित दीर्घ reg)
अणु
	अचिन्हित दीर्घ addr;
	MSC_READ(reg, addr);
	वापस (अचिन्हित दीर्घ) ioremap(addr, 0x10000);
पूर्ण

/*
 * GCMP Specअगरic definitions
 */
#घोषणा GCMP_BASE_ADDR			0x1fbf8000
#घोषणा GCMP_ADDRSPACE_SZ		(256 * 1024)

/*
 * GIC Specअगरic definitions
 */
#घोषणा GIC_BASE_ADDR			0x1bdc0000
#घोषणा GIC_ADDRSPACE_SZ		(128 * 1024)

/*
 * CPC Specअगरic definitions
 */
#घोषणा CPC_BASE_ADDR			0x1bde0000

/*
 * MSC01 BIU Specअगरic definitions
 * FIXME : These should be अन्यथाwhere ?
 */
#घोषणा MSC01_BIU_REG_BASE		0x1bc80000
#घोषणा MSC01_BIU_ADDRSPACE_SZ		(256 * 1024)
#घोषणा MSC01_SC_CFG_OFS		0x0110
#घोषणा MSC01_SC_CFG_GICPRES_MSK	0x00000004
#घोषणा MSC01_SC_CFG_GICPRES_SHF	2
#घोषणा MSC01_SC_CFG_GICENA_SHF		3

/*
 * Malta RTC-device indirect रेजिस्टर access.
 */
#घोषणा MALTA_RTC_ADR_REG	0x70
#घोषणा MALTA_RTC_DAT_REG	0x71

/*
 * Malta SMSC FDC37M817 Super I/O Controller रेजिस्टर.
 */
#घोषणा SMSC_CONFIG_REG		0x3f0
#घोषणा SMSC_DATA_REG		0x3f1

#घोषणा SMSC_CONFIG_DEVNUM	0x7
#घोषणा SMSC_CONFIG_ACTIVATE	0x30
#घोषणा SMSC_CONFIG_ENTER	0x55
#घोषणा SMSC_CONFIG_EXIT	0xaa

#घोषणा SMSC_CONFIG_DEVNUM_FLOPPY     0

#घोषणा SMSC_CONFIG_ACTIVATE_ENABLE   1

#घोषणा SMSC_WRITE(x, a)     outb(x, a)

#घोषणा MALTA_JMPRS_REG		0x1f000210

बाह्य व्योम __init *malta_dt_shim(व्योम *fdt);

#पूर्ण_अगर /* __ASM_MIPS_BOARDS_MALTA_H */
