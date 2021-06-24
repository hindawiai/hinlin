<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007-2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Tony Li <tony.li@मुक्तscale.com>
 *	   Jason Jin <Jason.jin@मुक्तscale.com>
 */
#अगर_अघोषित _POWERPC_SYSDEV_FSL_MSI_H
#घोषणा _POWERPC_SYSDEV_FSL_MSI_H

#समावेश <linux/of.h>
#समावेश <यंत्र/msi_biपंचांगap.h>

#घोषणा NR_MSI_REG_MSIIR	8  /* MSIIR can index 8 MSI रेजिस्टरs */
#घोषणा NR_MSI_REG_MSIIR1	16 /* MSIIR1 can index 16 MSI रेजिस्टरs */
#घोषणा NR_MSI_REG_MAX		NR_MSI_REG_MSIIR1
#घोषणा IRQS_PER_MSI_REG	32
#घोषणा NR_MSI_IRQS_MAX	(NR_MSI_REG_MAX * IRQS_PER_MSI_REG)

#घोषणा FSL_PIC_IP_MASK   0x0000000F
#घोषणा FSL_PIC_IP_MPIC   0x00000001
#घोषणा FSL_PIC_IP_IPIC   0x00000002
#घोषणा FSL_PIC_IP_VMPIC  0x00000003

#घोषणा MSI_HW_ERRATA_ENDIAN 0x00000010

काष्ठा fsl_msi_cascade_data;

काष्ठा fsl_msi अणु
	काष्ठा irq_करोमुख्य *irqhost;

	अचिन्हित दीर्घ cascade_irq;

	u32 msiir_offset; /* Offset of MSIIR, relative to start of CCSR */
	u32 ibs_shअगरt; /* Shअगरt of पूर्णांकerrupt bit select */
	u32 srs_shअगरt; /* Shअगरt of the shared पूर्णांकerrupt रेजिस्टर select */
	व्योम __iomem *msi_regs;
	u32 feature;
	काष्ठा fsl_msi_cascade_data *cascade_array[NR_MSI_REG_MAX];

	काष्ठा msi_biपंचांगap biपंचांगap;

	काष्ठा list_head list;          /* support multiple MSI banks */

	phandle phandle;
पूर्ण;

#पूर्ण_अगर /* _POWERPC_SYSDEV_FSL_MSI_H */

