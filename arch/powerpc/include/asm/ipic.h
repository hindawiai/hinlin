<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * IPIC बाह्यal definitions and काष्ठाure.
 *
 * Maपूर्णांकainer: Kumar Gala <galak@kernel.crashing.org>
 *
 * Copyright 2005 Freescale Semiconductor, Inc
 */
#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASM_IPIC_H__
#घोषणा __ASM_IPIC_H__

#समावेश <linux/irq.h>

/* Flags when we init the IPIC */
#घोषणा IPIC_SPREADMODE_GRP_A	0x00000001
#घोषणा IPIC_SPREADMODE_GRP_B	0x00000002
#घोषणा IPIC_SPREADMODE_GRP_C	0x00000004
#घोषणा IPIC_SPREADMODE_GRP_D	0x00000008
#घोषणा IPIC_SPREADMODE_MIX_A	0x00000010
#घोषणा IPIC_SPREADMODE_MIX_B	0x00000020
#घोषणा IPIC_DISABLE_MCP_OUT	0x00000040
#घोषणा IPIC_IRQ0_MCP		0x00000080

/* IPIC रेजिस्टरs offsets */
#घोषणा IPIC_SICFR	0x00	/* System Global Interrupt Configuration Register */
#घोषणा IPIC_SIVCR	0x04	/* System Global Interrupt Vector Register */
#घोषणा IPIC_SIPNR_H	0x08	/* System Internal Interrupt Pending Register (HIGH) */
#घोषणा IPIC_SIPNR_L	0x0C	/* System Internal Interrupt Pending Register (LOW) */
#घोषणा IPIC_SIPRR_A	0x10	/* System Internal Interrupt group A Priority Register */
#घोषणा IPIC_SIPRR_B	0x14	/* System Internal Interrupt group B Priority Register */
#घोषणा IPIC_SIPRR_C	0x18	/* System Internal Interrupt group C Priority Register */
#घोषणा IPIC_SIPRR_D	0x1C	/* System Internal Interrupt group D Priority Register */
#घोषणा IPIC_SIMSR_H	0x20	/* System Internal Interrupt Mask Register (HIGH) */
#घोषणा IPIC_SIMSR_L	0x24	/* System Internal Interrupt Mask Register (LOW) */
#घोषणा IPIC_SICNR	0x28	/* System Internal Interrupt Control Register */
#घोषणा IPIC_SEPNR	0x2C	/* System External Interrupt Pending Register */
#घोषणा IPIC_SMPRR_A	0x30	/* System Mixed Interrupt group A Priority Register */
#घोषणा IPIC_SMPRR_B	0x34	/* System Mixed Interrupt group B Priority Register */
#घोषणा IPIC_SEMSR	0x38	/* System External Interrupt Mask Register */
#घोषणा IPIC_SECNR	0x3C	/* System External Interrupt Control Register */
#घोषणा IPIC_SERSR	0x40	/* System Error Status Register */
#घोषणा IPIC_SERMR	0x44	/* System Error Mask Register */
#घोषणा IPIC_SERCR	0x48	/* System Error Control Register */
#घोषणा IPIC_SIFCR_H	0x50	/* System Internal Interrupt Force Register (HIGH) */
#घोषणा IPIC_SIFCR_L	0x54	/* System Internal Interrupt Force Register (LOW) */
#घोषणा IPIC_SEFCR	0x58	/* System External Interrupt Force Register */
#घोषणा IPIC_SERFR	0x5C	/* System Error Force Register */
#घोषणा IPIC_SCVCR	0x60	/* System Critical Interrupt Vector Register */
#घोषणा IPIC_SMVCR	0x64	/* System Management Interrupt Vector Register */

क्रमागत ipic_prio_grp अणु
	IPIC_INT_GRP_A = IPIC_SIPRR_A,
	IPIC_INT_GRP_D = IPIC_SIPRR_D,
	IPIC_MIX_GRP_A = IPIC_SMPRR_A,
	IPIC_MIX_GRP_B = IPIC_SMPRR_B,
पूर्ण;

क्रमागत ipic_mcp_irq अणु
	IPIC_MCP_IRQ0 = 0,
	IPIC_MCP_WDT  = 1,
	IPIC_MCP_SBA  = 2,
	IPIC_MCP_PCI1 = 5,
	IPIC_MCP_PCI2 = 6,
	IPIC_MCP_MU   = 7,
पूर्ण;

बाह्य व्योम ipic_set_शेष_priority(व्योम);
बाह्य u32 ipic_get_mcp_status(व्योम);
बाह्य व्योम ipic_clear_mcp_status(u32 mask);

बाह्य काष्ठा ipic * ipic_init(काष्ठा device_node *node, अचिन्हित पूर्णांक flags);
बाह्य अचिन्हित पूर्णांक ipic_get_irq(व्योम);

#पूर्ण_अगर /* __ASM_IPIC_H__ */
#पूर्ण_अगर /* __KERNEL__ */
