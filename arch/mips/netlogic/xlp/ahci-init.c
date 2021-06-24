<शैली गुरु>
/*
 * Copyright (c) 2003-2014 Broadcom Corporation
 * All Rights Reserved
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the Broadcom
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
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mipsregs.h>

#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/mips-extns.h>

#घोषणा SATA_CTL		0x0
#घोषणा SATA_STATUS		0x1	/* Status Reg */
#घोषणा SATA_INT		0x2	/* Interrupt Reg */
#घोषणा SATA_INT_MASK		0x3	/* Interrupt Mask Reg */
#घोषणा SATA_CR_REG_TIMER	0x4	/* PHY Conrol Timer Reg */
#घोषणा SATA_CORE_ID		0x5	/* Core ID Reg */
#घोषणा SATA_AXI_SLAVE_OPT1	0x6	/* AXI Slave Options Reg */
#घोषणा SATA_PHY_LOS_LEV	0x7	/* PHY LOS Level Reg */
#घोषणा SATA_PHY_MULTI		0x8	/* PHY Multiplier Reg */
#घोषणा SATA_PHY_CLK_SEL	0x9	/* Clock Select Reg */
#घोषणा SATA_PHY_AMP1_GEN1	0xa	/* PHY Transmit Amplitude Reg 1 */
#घोषणा SATA_PHY_AMP1_GEN2	0xb	/* PHY Transmit Amplitude Reg 2 */
#घोषणा SATA_PHY_AMP1_GEN3	0xc	/* PHY Transmit Amplitude Reg 3 */
#घोषणा SATA_PHY_PRE1		0xd	/* PHY Transmit Preemphasis Reg 1 */
#घोषणा SATA_PHY_PRE2		0xe	/* PHY Transmit Preemphasis Reg 2 */
#घोषणा SATA_PHY_PRE3		0xf	/* PHY Transmit Preemphasis Reg 3 */
#घोषणा SATA_SPDMODE		0x10	/* Speed Mode Reg */
#घोषणा SATA_REFCLK		0x11	/* Reference Clock Control Reg */
#घोषणा SATA_BYTE_SWAP_DIS	0x12	/* byte swap disable */

/*SATA_CTL Bits */
#घोषणा SATA_RST_N		BIT(0)
#घोषणा PHY0_RESET_N		BIT(16)
#घोषणा PHY1_RESET_N		BIT(17)
#घोषणा PHY2_RESET_N		BIT(18)
#घोषणा PHY3_RESET_N		BIT(19)
#घोषणा M_CSYSREQ		BIT(2)
#घोषणा S_CSYSREQ		BIT(3)

/*SATA_STATUS Bits */
#घोषणा P0_PHY_READY		BIT(4)
#घोषणा P1_PHY_READY		BIT(5)
#घोषणा P2_PHY_READY		BIT(6)
#घोषणा P3_PHY_READY		BIT(7)

#घोषणा nlm_पढ़ो_sata_reg(b, r)		nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_sata_reg(b, r, v)	nlm_ग_लिखो_reg(b, r, v)
#घोषणा nlm_get_sata_pcibase(node)	\
		nlm_pcicfg_base(XLP_IO_SATA_OFFSET(node))
/* SATA device specअगरic configuration रेजिस्टरs are starts at 0x900 offset */
#घोषणा nlm_get_sata_regbase(node)	\
		(nlm_get_sata_pcibase(node) + 0x900)

अटल व्योम sata_clear_glue_reg(uपूर्णांक64_t regbase, uपूर्णांक32_t off, uपूर्णांक32_t bit)
अणु
	uपूर्णांक32_t reg_val;

	reg_val = nlm_पढ़ो_sata_reg(regbase, off);
	nlm_ग_लिखो_sata_reg(regbase, off, (reg_val & ~bit));
पूर्ण

अटल व्योम sata_set_glue_reg(uपूर्णांक64_t regbase, uपूर्णांक32_t off, uपूर्णांक32_t bit)
अणु
	uपूर्णांक32_t reg_val;

	reg_val = nlm_पढ़ो_sata_reg(regbase, off);
	nlm_ग_लिखो_sata_reg(regbase, off, (reg_val | bit));
पूर्ण

अटल व्योम nlm_sata_firmware_init(पूर्णांक node)
अणु
	uपूर्णांक32_t reg_val;
	uपूर्णांक64_t regbase;
	पूर्णांक i;

	pr_info("XLP AHCI Initialization started.\n");
	regbase = nlm_get_sata_regbase(node);

	/* Reset SATA */
	sata_clear_glue_reg(regbase, SATA_CTL, SATA_RST_N);
	/* Reset PHY */
	sata_clear_glue_reg(regbase, SATA_CTL,
			(PHY3_RESET_N | PHY2_RESET_N
			 | PHY1_RESET_N | PHY0_RESET_N));

	/* Set SATA */
	sata_set_glue_reg(regbase, SATA_CTL, SATA_RST_N);
	/* Set PHY */
	sata_set_glue_reg(regbase, SATA_CTL,
			(PHY3_RESET_N | PHY2_RESET_N
			 | PHY1_RESET_N | PHY0_RESET_N));

	pr_debug("Waiting for PHYs to come up.\n");
	i = 0;
	करो अणु
		reg_val = nlm_पढ़ो_sata_reg(regbase, SATA_STATUS);
		i++;
	पूर्ण जबतक (((reg_val & 0xF0) != 0xF0) && (i < 10000));

	क्रम (i = 0; i < 4; i++) अणु
		अगर (reg_val  & (P0_PHY_READY << i))
			pr_info("PHY%d is up.\n", i);
		अन्यथा
			pr_info("PHY%d is down.\n", i);
	पूर्ण

	pr_info("XLP AHCI init done.\n");
पूर्ण

अटल पूर्णांक __init nlm_ahci_init(व्योम)
अणु
	पूर्णांक node = 0;
	पूर्णांक chip = पढ़ो_c0_prid() & PRID_IMP_MASK;

	अगर (chip == PRID_IMP_NETLOGIC_XLP3XX)
		nlm_sata_firmware_init(node);
	वापस 0;
पूर्ण

अटल व्योम nlm_sata_पूर्णांकr_ack(काष्ठा irq_data *data)
अणु
	uपूर्णांक32_t val = 0;
	uपूर्णांक64_t regbase;

	regbase = nlm_get_sata_regbase(nlm_nodeid());
	val = nlm_पढ़ो_sata_reg(regbase, SATA_INT);
	sata_set_glue_reg(regbase, SATA_INT, val);
पूर्ण

अटल व्योम nlm_sata_fixup_bar(काष्ठा pci_dev *dev)
अणु
	/*
	 * The AHCI resource is in BAR 0, move it to
	 * BAR 5, where it is expected
	 */
	dev->resource[5] = dev->resource[0];
	स_रखो(&dev->resource[0], 0, माप(dev->resource[0]));
पूर्ण

अटल व्योम nlm_sata_fixup_final(काष्ठा pci_dev *dev)
अणु
	uपूर्णांक32_t val;
	uपूर्णांक64_t regbase;
	पूर्णांक node = 0; /* XLP3XX करोes not support multi-node */

	regbase = nlm_get_sata_regbase(node);

	/* clear pending पूर्णांकerrupts and then enable them */
	val = nlm_पढ़ो_sata_reg(regbase, SATA_INT);
	sata_set_glue_reg(regbase, SATA_INT, val);

	/* Mask the core पूर्णांकerrupt. If all the पूर्णांकerrupts
	 * are enabled there are spurious पूर्णांकerrupt flow
	 * happening, to aव्योम only enable core पूर्णांकerrupt
	 * mask.
	 */
	sata_set_glue_reg(regbase, SATA_INT_MASK, 0x1);

	dev->irq = PIC_SATA_IRQ;
	nlm_set_pic_extra_ack(node, PIC_SATA_IRQ, nlm_sata_पूर्णांकr_ack);
पूर्ण

arch_initcall(nlm_ahci_init);

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_NETLOGIC, PCI_DEVICE_ID_NLM_SATA,
		nlm_sata_fixup_bar);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_NETLOGIC, PCI_DEVICE_ID_NLM_SATA,
		nlm_sata_fixup_final);
