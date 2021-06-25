<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __NLM_HAL_BRIDGE_H__
#घोषणा __NLM_HAL_BRIDGE_H__

/**
* @file_name mपन.स
* @author Netlogic Microप्रणालीs
* @brief Basic definitions of XLP memory and io subप्रणाली
*/

/*
 * BRIDGE specअगरic रेजिस्टरs
 *
 * These रेजिस्टरs start after the PCIe header, which has 0x40
 * standard entries
 */
#घोषणा BRIDGE_MODE			0x00
#घोषणा BRIDGE_PCI_CFG_BASE		0x01
#घोषणा BRIDGE_PCI_CFG_LIMIT		0x02
#घोषणा BRIDGE_PCIE_CFG_BASE		0x03
#घोषणा BRIDGE_PCIE_CFG_LIMIT		0x04
#घोषणा BRIDGE_BUSNUM_BAR0		0x05
#घोषणा BRIDGE_BUSNUM_BAR1		0x06
#घोषणा BRIDGE_BUSNUM_BAR2		0x07
#घोषणा BRIDGE_BUSNUM_BAR3		0x08
#घोषणा BRIDGE_BUSNUM_BAR4		0x09
#घोषणा BRIDGE_BUSNUM_BAR5		0x0a
#घोषणा BRIDGE_BUSNUM_BAR6		0x0b
#घोषणा BRIDGE_FLASH_BAR0		0x0c
#घोषणा BRIDGE_FLASH_BAR1		0x0d
#घोषणा BRIDGE_FLASH_BAR2		0x0e
#घोषणा BRIDGE_FLASH_BAR3		0x0f
#घोषणा BRIDGE_FLASH_LIMIT0		0x10
#घोषणा BRIDGE_FLASH_LIMIT1		0x11
#घोषणा BRIDGE_FLASH_LIMIT2		0x12
#घोषणा BRIDGE_FLASH_LIMIT3		0x13

#घोषणा BRIDGE_DRAM_BAR(i)		(0x14 + (i))
#घोषणा BRIDGE_DRAM_LIMIT(i)		(0x1c + (i))
#घोषणा BRIDGE_DRAM_NODE_TRANSLN(i)	(0x24 + (i))
#घोषणा BRIDGE_DRAM_CHNL_TRANSLN(i)	(0x2c + (i))

#घोषणा BRIDGE_PCIEMEM_BASE0		0x34
#घोषणा BRIDGE_PCIEMEM_BASE1		0x35
#घोषणा BRIDGE_PCIEMEM_BASE2		0x36
#घोषणा BRIDGE_PCIEMEM_BASE3		0x37
#घोषणा BRIDGE_PCIEMEM_LIMIT0		0x38
#घोषणा BRIDGE_PCIEMEM_LIMIT1		0x39
#घोषणा BRIDGE_PCIEMEM_LIMIT2		0x3a
#घोषणा BRIDGE_PCIEMEM_LIMIT3		0x3b
#घोषणा BRIDGE_PCIEIO_BASE0		0x3c
#घोषणा BRIDGE_PCIEIO_BASE1		0x3d
#घोषणा BRIDGE_PCIEIO_BASE2		0x3e
#घोषणा BRIDGE_PCIEIO_BASE3		0x3f
#घोषणा BRIDGE_PCIEIO_LIMIT0		0x40
#घोषणा BRIDGE_PCIEIO_LIMIT1		0x41
#घोषणा BRIDGE_PCIEIO_LIMIT2		0x42
#घोषणा BRIDGE_PCIEIO_LIMIT3		0x43
#घोषणा BRIDGE_PCIEMEM_BASE4		0x44
#घोषणा BRIDGE_PCIEMEM_BASE5		0x45
#घोषणा BRIDGE_PCIEMEM_BASE6		0x46
#घोषणा BRIDGE_PCIEMEM_LIMIT4		0x47
#घोषणा BRIDGE_PCIEMEM_LIMIT5		0x48
#घोषणा BRIDGE_PCIEMEM_LIMIT6		0x49
#घोषणा BRIDGE_PCIEIO_BASE4		0x4a
#घोषणा BRIDGE_PCIEIO_BASE5		0x4b
#घोषणा BRIDGE_PCIEIO_BASE6		0x4c
#घोषणा BRIDGE_PCIEIO_LIMIT4		0x4d
#घोषणा BRIDGE_PCIEIO_LIMIT5		0x4e
#घोषणा BRIDGE_PCIEIO_LIMIT6		0x4f
#घोषणा BRIDGE_NBU_EVENT_CNT_CTL	0x50
#घोषणा BRIDGE_EVNTCTR1_LOW		0x51
#घोषणा BRIDGE_EVNTCTR1_HI		0x52
#घोषणा BRIDGE_EVNT_CNT_CTL2		0x53
#घोषणा BRIDGE_EVNTCTR2_LOW		0x54
#घोषणा BRIDGE_EVNTCTR2_HI		0x55
#घोषणा BRIDGE_TRACEBUF_MATCH0		0x56
#घोषणा BRIDGE_TRACEBUF_MATCH1		0x57
#घोषणा BRIDGE_TRACEBUF_MATCH_LOW	0x58
#घोषणा BRIDGE_TRACEBUF_MATCH_HI	0x59
#घोषणा BRIDGE_TRACEBUF_CTRL		0x5a
#घोषणा BRIDGE_TRACEBUF_INIT		0x5b
#घोषणा BRIDGE_TRACEBUF_ACCESS		0x5c
#घोषणा BRIDGE_TRACEBUF_READ_DATA0	0x5d
#घोषणा BRIDGE_TRACEBUF_READ_DATA1	0x5d
#घोषणा BRIDGE_TRACEBUF_READ_DATA2	0x5f
#घोषणा BRIDGE_TRACEBUF_READ_DATA3	0x60
#घोषणा BRIDGE_TRACEBUF_STATUS		0x61
#घोषणा BRIDGE_ADDRESS_ERROR0		0x62
#घोषणा BRIDGE_ADDRESS_ERROR1		0x63
#घोषणा BRIDGE_ADDRESS_ERROR2		0x64
#घोषणा BRIDGE_TAG_ECC_ADDR_ERROR0	0x65
#घोषणा BRIDGE_TAG_ECC_ADDR_ERROR1	0x66
#घोषणा BRIDGE_TAG_ECC_ADDR_ERROR2	0x67
#घोषणा BRIDGE_LINE_FLUSH0		0x68
#घोषणा BRIDGE_LINE_FLUSH1		0x69
#घोषणा BRIDGE_NODE_ID			0x6a
#घोषणा BRIDGE_ERROR_INTERRUPT_EN	0x6b
#घोषणा BRIDGE_PCIE0_WEIGHT		0x2c0
#घोषणा BRIDGE_PCIE1_WEIGHT		0x2c1
#घोषणा BRIDGE_PCIE2_WEIGHT		0x2c2
#घोषणा BRIDGE_PCIE3_WEIGHT		0x2c3
#घोषणा BRIDGE_USB_WEIGHT		0x2c4
#घोषणा BRIDGE_NET_WEIGHT		0x2c5
#घोषणा BRIDGE_POE_WEIGHT		0x2c6
#घोषणा BRIDGE_CMS_WEIGHT		0x2c7
#घोषणा BRIDGE_DMAENG_WEIGHT		0x2c8
#घोषणा BRIDGE_SEC_WEIGHT		0x2c9
#घोषणा BRIDGE_COMP_WEIGHT		0x2ca
#घोषणा BRIDGE_GIO_WEIGHT		0x2cb
#घोषणा BRIDGE_FLASH_WEIGHT		0x2cc

/* FIXME verअगरy */
#घोषणा BRIDGE_9XX_FLASH_BAR(i)		(0x11 + (i))
#घोषणा BRIDGE_9XX_FLASH_BAR_LIMIT(i)	(0x15 + (i))

#घोषणा BRIDGE_9XX_DRAM_BAR(i)		(0x19 + (i))
#घोषणा BRIDGE_9XX_DRAM_LIMIT(i)	(0x29 + (i))
#घोषणा BRIDGE_9XX_DRAM_NODE_TRANSLN(i)	(0x39 + (i))
#घोषणा BRIDGE_9XX_DRAM_CHNL_TRANSLN(i)	(0x49 + (i))

#घोषणा BRIDGE_9XX_ADDRESS_ERROR0	0x9d
#घोषणा BRIDGE_9XX_ADDRESS_ERROR1	0x9e
#घोषणा BRIDGE_9XX_ADDRESS_ERROR2	0x9f

#घोषणा BRIDGE_9XX_PCIEMEM_BASE0	0x59
#घोषणा BRIDGE_9XX_PCIEMEM_BASE1	0x5a
#घोषणा BRIDGE_9XX_PCIEMEM_BASE2	0x5b
#घोषणा BRIDGE_9XX_PCIEMEM_BASE3	0x5c
#घोषणा BRIDGE_9XX_PCIEMEM_LIMIT0	0x5d
#घोषणा BRIDGE_9XX_PCIEMEM_LIMIT1	0x5e
#घोषणा BRIDGE_9XX_PCIEMEM_LIMIT2	0x5f
#घोषणा BRIDGE_9XX_PCIEMEM_LIMIT3	0x60
#घोषणा BRIDGE_9XX_PCIEIO_BASE0		0x61
#घोषणा BRIDGE_9XX_PCIEIO_BASE1		0x62
#घोषणा BRIDGE_9XX_PCIEIO_BASE2		0x63
#घोषणा BRIDGE_9XX_PCIEIO_BASE3		0x64
#घोषणा BRIDGE_9XX_PCIEIO_LIMIT0	0x65
#घोषणा BRIDGE_9XX_PCIEIO_LIMIT1	0x66
#घोषणा BRIDGE_9XX_PCIEIO_LIMIT2	0x67
#घोषणा BRIDGE_9XX_PCIEIO_LIMIT3	0x68

#अगर_अघोषित __ASSEMBLY__

#घोषणा nlm_पढ़ो_bridge_reg(b, r)	nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_bridge_reg(b, r, v)	nlm_ग_लिखो_reg(b, r, v)
#घोषणा nlm_get_bridge_pcibase(node)	nlm_pcicfg_base(cpu_is_xlp9xx() ? \
		XLP9XX_IO_BRIDGE_OFFSET(node) : XLP_IO_BRIDGE_OFFSET(node))
#घोषणा nlm_get_bridge_regbase(node)	\
			(nlm_get_bridge_pcibase(node) + XLP_IO_PCI_HDRSZ)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __NLM_HAL_BRIDGE_H__ */
