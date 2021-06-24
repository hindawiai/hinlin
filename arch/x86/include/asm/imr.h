<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * imr.h: Isolated Memory Region API
 *
 * Copyright(c) 2013 Intel Corporation.
 * Copyright(c) 2015 Bryan O'Donoghue <pure.logic@nexus-software.ie>
 */
#अगर_अघोषित _IMR_H
#घोषणा _IMR_H

#समावेश <linux/types.h>

/*
 * IMR agent access mask bits
 * See section 12.7.4.7 from quark-x1000-datasheet.pdf क्रम रेजिस्टर
 * definitions.
 */
#घोषणा IMR_ESRAM_FLUSH		BIT(31)
#घोषणा IMR_CPU_SNOOP		BIT(30)		/* Applicable only to ग_लिखो */
#घोषणा IMR_RMU			BIT(29)
#घोषणा IMR_VC1_SAI_ID3		BIT(15)
#घोषणा IMR_VC1_SAI_ID2		BIT(14)
#घोषणा IMR_VC1_SAI_ID1		BIT(13)
#घोषणा IMR_VC1_SAI_ID0		BIT(12)
#घोषणा IMR_VC0_SAI_ID3		BIT(11)
#घोषणा IMR_VC0_SAI_ID2		BIT(10)
#घोषणा IMR_VC0_SAI_ID1		BIT(9)
#घोषणा IMR_VC0_SAI_ID0		BIT(8)
#घोषणा IMR_CPU_0		BIT(1)		/* SMM mode */
#घोषणा IMR_CPU			BIT(0)		/* Non SMM mode */
#घोषणा IMR_ACCESS_NONE		0

/*
 * Read/Write access-all bits here include some reserved bits
 * These are the values firmware uses and are accepted by hardware.
 * The kernel defines पढ़ो/ग_लिखो access-all in the same way as firmware
 * in order to have a consistent and crisp definition across firmware,
 * bootloader and kernel.
 */
#घोषणा IMR_READ_ACCESS_ALL	0xBFFFFFFF
#घोषणा IMR_WRITE_ACCESS_ALL	0xFFFFFFFF

/* Number of IMRs provided by Quark X1000 SoC */
#घोषणा QUARK_X1000_IMR_MAX	0x08
#घोषणा QUARK_X1000_IMR_REGBASE 0x40

/* IMR alignment bits - only bits 31:10 are checked क्रम IMR validity */
#घोषणा IMR_ALIGN		0x400
#घोषणा IMR_MASK		(IMR_ALIGN - 1)

पूर्णांक imr_add_range(phys_addr_t base, माप_प्रकार size,
		  अचिन्हित पूर्णांक rmask, अचिन्हित पूर्णांक wmask);

पूर्णांक imr_हटाओ_range(phys_addr_t base, माप_प्रकार size);

#पूर्ण_अगर /* _IMR_H */
