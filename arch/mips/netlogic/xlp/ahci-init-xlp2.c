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
#समावेश <linux/pci_ids.h>
#समावेश <linux/nodemask.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mipsregs.h>

#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/mips-extns.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>

#घोषणा SATA_CTL		0x0
#घोषणा SATA_STATUS		0x1 /* Status Reg */
#घोषणा SATA_INT		0x2 /* Interrupt Reg */
#घोषणा SATA_INT_MASK		0x3 /* Interrupt Mask Reg */
#घोषणा SATA_BIU_TIMEOUT	0x4
#घोषणा AXIWRSPERRLOG		0x5
#घोषणा AXIRDSPERRLOG		0x6
#घोषणा BiuTimeoutLow		0x7
#घोषणा BiuTimeoutHi		0x8
#घोषणा BiuSlvErLow		0x9
#घोषणा BiuSlvErHi		0xa
#घोषणा IO_CONFIG_SWAP_DIS	0xb
#घोषणा CR_REG_TIMER		0xc
#घोषणा CORE_ID			0xd
#घोषणा AXI_SLAVE_OPT1		0xe
#घोषणा PHY_MEM_ACCESS		0xf
#घोषणा PHY0_CNTRL		0x10
#घोषणा PHY0_STAT		0x11
#घोषणा PHY0_RX_ALIGN		0x12
#घोषणा PHY0_RX_EQ_LO		0x13
#घोषणा PHY0_RX_EQ_HI		0x14
#घोषणा PHY0_BIST_LOOP		0x15
#घोषणा PHY1_CNTRL		0x16
#घोषणा PHY1_STAT		0x17
#घोषणा PHY1_RX_ALIGN		0x18
#घोषणा PHY1_RX_EQ_LO		0x19
#घोषणा PHY1_RX_EQ_HI		0x1a
#घोषणा PHY1_BIST_LOOP		0x1b
#घोषणा RdExBase		0x1c
#घोषणा RdExLimit		0x1d
#घोषणा CacheAllocBase		0x1e
#घोषणा CacheAllocLimit		0x1f
#घोषणा BiuSlaveCmdGstNum	0x20

/*SATA_CTL Bits */
#घोषणा SATA_RST_N		BIT(0)  /* Active low reset sata_core phy */
#घोषणा SataCtlReserve0		BIT(1)
#घोषणा M_CSYSREQ		BIT(2)  /* AXI master low घातer, not used */
#घोषणा S_CSYSREQ		BIT(3)  /* AXI slave low घातer, not used */
#घोषणा P0_CP_DET		BIT(8)  /* Reserved, bring in from pad */
#घोषणा P0_MP_SW		BIT(9)  /* Mech Switch */
#घोषणा P0_DISABLE		BIT(10) /* disable p0 */
#घोषणा P0_ACT_LED_EN		BIT(11) /* Active LED enable */
#घोषणा P0_IRST_HARD_SYNTH	BIT(12) /* PHY hard synth reset */
#घोषणा P0_IRST_HARD_TXRX	BIT(13) /* PHY lane hard reset */
#घोषणा P0_IRST_POR		BIT(14) /* PHY घातer on reset*/
#घोषणा P0_IPDTXL		BIT(15) /* PHY Tx lane dis/घातer करोwn */
#घोषणा P0_IPDRXL		BIT(16) /* PHY Rx lane dis/घातer करोwn */
#घोषणा P0_IPDIPDMSYNTH		BIT(17) /* PHY synthesizer dis/porwer करोwn */
#घोषणा P0_CP_POD_EN		BIT(18) /* CP_POD enable */
#घोषणा P0_AT_BYPASS		BIT(19) /* P0 address translation by pass */
#घोषणा P1_CP_DET		BIT(20) /* Reserved,Cold Detect */
#घोषणा P1_MP_SW		BIT(21) /* Mech Switch */
#घोषणा P1_DISABLE		BIT(22) /* disable p1 */
#घोषणा P1_ACT_LED_EN		BIT(23) /* Active LED enable */
#घोषणा P1_IRST_HARD_SYNTH	BIT(24) /* PHY hard synth reset */
#घोषणा P1_IRST_HARD_TXRX	BIT(25) /* PHY lane hard reset */
#घोषणा P1_IRST_POR		BIT(26) /* PHY घातer on reset*/
#घोषणा P1_IPDTXL		BIT(27) /* PHY Tx lane dis/porwer करोwn */
#घोषणा P1_IPDRXL		BIT(28) /* PHY Rx lane dis/porwer करोwn */
#घोषणा P1_IPDIPDMSYNTH		BIT(29) /* PHY synthesizer dis/porwer करोwn */
#घोषणा P1_CP_POD_EN		BIT(30)
#घोषणा P1_AT_BYPASS		BIT(31) /* P1 address translation by pass */

/* Status रेजिस्टर */
#घोषणा M_CACTIVE		BIT(0)  /* m_cactive, not used */
#घोषणा S_CACTIVE		BIT(1)  /* s_cactive, not used */
#घोषणा P0_PHY_READY		BIT(8)  /* phy is पढ़ोy */
#घोषणा P0_CP_POD		BIT(9)  /* Cold PowerOn */
#घोषणा P0_SLUMBER		BIT(10) /* घातer mode slumber */
#घोषणा P0_PATIAL		BIT(11) /* घातer mode patial */
#घोषणा P0_PHY_SIG_DET		BIT(12) /* phy dignal detect */
#घोषणा P0_PHY_CALI		BIT(13) /* phy calibration करोne */
#घोषणा P1_PHY_READY		BIT(16) /* phy is पढ़ोy */
#घोषणा P1_CP_POD		BIT(17) /* Cold PowerOn */
#घोषणा P1_SLUMBER		BIT(18) /* घातer mode slumber */
#घोषणा P1_PATIAL		BIT(19) /* घातer mode patial */
#घोषणा P1_PHY_SIG_DET		BIT(20) /* phy dignal detect */
#घोषणा P1_PHY_CALI		BIT(21) /* phy calibration करोne */

/* SATA CR_REG_TIMER bits */
#घोषणा CR_TIME_SCALE		(0x1000 << 0)

/* SATA PHY specअगरic रेजिस्टरs start and end address */
#घोषणा RXCDRCALFOSC0		0x0065
#घोषणा CALDUTY			0x006e
#घोषणा RXDPIF			0x8065
#घोषणा PPMDRIFTMAX_HI		0x80A4

#घोषणा nlm_पढ़ो_sata_reg(b, r)		nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_sata_reg(b, r, v)	nlm_ग_लिखो_reg(b, r, v)
#घोषणा nlm_get_sata_pcibase(node)	\
		nlm_pcicfg_base(XLP9XX_IO_SATA_OFFSET(node))
#घोषणा nlm_get_sata_regbase(node)	\
		(nlm_get_sata_pcibase(node) + 0x100)

/* SATA PHY config क्रम रेजिस्टर block 1 0x0065 .. 0x006e */
अटल स्थिर u8 sata_phy_config1[]  = अणु
	0xC9, 0xC9, 0x07, 0x07, 0x18, 0x18, 0x01, 0x01, 0x22, 0x00
पूर्ण;

/* SATA PHY config क्रम रेजिस्टर block 2 0x8065 .. 0x80A4 */
अटल स्थिर u8 sata_phy_config2[]  = अणु
	0xAA, 0x00, 0x4C, 0xC9, 0xC9, 0x07, 0x07, 0x18,
	0x18, 0x05, 0x0C, 0x10, 0x00, 0x10, 0x00, 0xFF,
	0xCF, 0xF7, 0xE1, 0xF5, 0xFD, 0xFD, 0xFF, 0xFF,
	0xFF, 0xFF, 0xE3, 0xE7, 0xDB, 0xF5, 0xFD, 0xFD,
	0xF5, 0xF5, 0xFF, 0xFF, 0xE3, 0xE7, 0xDB, 0xF5,
	0xFD, 0xFD, 0xF5, 0xF5, 0xFF, 0xFF, 0xFF, 0xF5,
	0x3F, 0x00, 0x32, 0x00, 0x03, 0x01, 0x05, 0x05,
	0x04, 0x00, 0x00, 0x08, 0x04, 0x00, 0x00, 0x04,
पूर्ण;

स्थिर पूर्णांक sata_phy_debug = 0;	/* set to verअगरy PHY ग_लिखोs */

अटल व्योम sata_clear_glue_reg(u64 regbase, u32 off, u32 bit)
अणु
	u32 reg_val;

	reg_val = nlm_पढ़ो_sata_reg(regbase, off);
	nlm_ग_लिखो_sata_reg(regbase, off, (reg_val & ~bit));
पूर्ण

अटल व्योम sata_set_glue_reg(u64 regbase, u32 off, u32 bit)
अणु
	u32 reg_val;

	reg_val = nlm_पढ़ो_sata_reg(regbase, off);
	nlm_ग_लिखो_sata_reg(regbase, off, (reg_val | bit));
पूर्ण

अटल व्योम ग_लिखो_phy_reg(u64 regbase, u32 addr, u32 physel, u8 data)
अणु
	nlm_ग_लिखो_sata_reg(regbase, PHY_MEM_ACCESS,
		(1u << 31) | (physel << 24) | (data << 16) | addr);
	udelay(850);
पूर्ण

अटल u8 पढ़ो_phy_reg(u64 regbase, u32 addr, u32 physel)
अणु
	u32 val;

	nlm_ग_लिखो_sata_reg(regbase, PHY_MEM_ACCESS,
		(0 << 31) | (physel << 24) | (0 << 16) | addr);
	udelay(850);
	val = nlm_पढ़ो_sata_reg(regbase, PHY_MEM_ACCESS);
	वापस (val >> 16) & 0xff;
पूर्ण

अटल व्योम config_sata_phy(u64 regbase)
अणु
	u32 port, i, reg;
	u8 val;

	क्रम (port = 0; port < 2; port++) अणु
		क्रम (i = 0, reg = RXCDRCALFOSC0; reg <= CALDUTY; reg++, i++)
			ग_लिखो_phy_reg(regbase, reg, port, sata_phy_config1[i]);

		क्रम (i = 0, reg = RXDPIF; reg <= PPMDRIFTMAX_HI; reg++, i++)
			ग_लिखो_phy_reg(regbase, reg, port, sata_phy_config2[i]);

		/* Fix क्रम PHY link up failures at lower temperatures */
		ग_लिखो_phy_reg(regbase, 0x800F, port, 0x1f);

		val = पढ़ो_phy_reg(regbase, 0x0029, port);
		ग_लिखो_phy_reg(regbase, 0x0029, port, val | (0x7 << 1));

		val = पढ़ो_phy_reg(regbase, 0x0056, port);
		ग_लिखो_phy_reg(regbase, 0x0056, port, val & ~(1 << 3));

		val = पढ़ो_phy_reg(regbase, 0x0018, port);
		ग_लिखो_phy_reg(regbase, 0x0018, port, val & ~(0x7 << 0));
	पूर्ण
पूर्ण

अटल व्योम check_phy_रेजिस्टर(u64 regbase, u32 addr, u32 physel, u8 xdata)
अणु
	u8 data;

	data = पढ़ो_phy_reg(regbase, addr, physel);
	pr_info("PHY read addr = 0x%x physel = %d data = 0x%x %s\n",
		addr, physel, data, data == xdata ? "TRUE" : "FALSE");
पूर्ण

अटल व्योम verअगरy_sata_phy_config(u64 regbase)
अणु
	u32 port, i, reg;

	क्रम (port = 0; port < 2; port++) अणु
		क्रम (i = 0, reg = RXCDRCALFOSC0; reg <= CALDUTY; reg++, i++)
			check_phy_रेजिस्टर(regbase, reg, port,
						sata_phy_config1[i]);

		क्रम (i = 0, reg = RXDPIF; reg <= PPMDRIFTMAX_HI; reg++, i++)
			check_phy_रेजिस्टर(regbase, reg, port,
						sata_phy_config2[i]);
	पूर्ण
पूर्ण

अटल व्योम nlm_sata_firmware_init(पूर्णांक node)
अणु
	u32 reg_val;
	u64 regbase;
	पूर्णांक n;

	pr_info("Initializing XLP9XX On-chip AHCI...\n");
	regbase = nlm_get_sata_regbase(node);

	/* Reset port0 */
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IRST_POR);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IRST_HARD_TXRX);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IRST_HARD_SYNTH);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IPDTXL);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IPDRXL);
	sata_clear_glue_reg(regbase, SATA_CTL, P0_IPDIPDMSYNTH);

	/* port1 */
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IRST_POR);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IRST_HARD_TXRX);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IRST_HARD_SYNTH);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IPDTXL);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IPDRXL);
	sata_clear_glue_reg(regbase, SATA_CTL, P1_IPDIPDMSYNTH);
	udelay(300);

	/* Set PHY */
	sata_set_glue_reg(regbase, SATA_CTL, P0_IPDTXL);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IPDRXL);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IPDIPDMSYNTH);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IPDTXL);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IPDRXL);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IPDIPDMSYNTH);

	udelay(1000);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IRST_POR);
	udelay(1000);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IRST_POR);
	udelay(1000);

	/* setup PHY */
	config_sata_phy(regbase);
	अगर (sata_phy_debug)
		verअगरy_sata_phy_config(regbase);

	udelay(1000);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IRST_HARD_TXRX);
	sata_set_glue_reg(regbase, SATA_CTL, P0_IRST_HARD_SYNTH);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IRST_HARD_TXRX);
	sata_set_glue_reg(regbase, SATA_CTL, P1_IRST_HARD_SYNTH);
	udelay(300);

	/* Override reset in serial PHY mode */
	sata_set_glue_reg(regbase, CR_REG_TIMER, CR_TIME_SCALE);
	/* Set reset SATA */
	sata_set_glue_reg(regbase, SATA_CTL, SATA_RST_N);
	sata_set_glue_reg(regbase, SATA_CTL, M_CSYSREQ);
	sata_set_glue_reg(regbase, SATA_CTL, S_CSYSREQ);

	pr_debug("Waiting for PHYs to come up.\n");
	n = 10000;
	करो अणु
		reg_val = nlm_पढ़ो_sata_reg(regbase, SATA_STATUS);
		अगर ((reg_val & P1_PHY_READY) && (reg_val & P0_PHY_READY))
			अवरोध;
		udelay(10);
	पूर्ण जबतक (--n > 0);

	अगर (reg_val  & P0_PHY_READY)
		pr_info("PHY0 is up.\n");
	अन्यथा
		pr_info("PHY0 is down.\n");
	अगर (reg_val  & P1_PHY_READY)
		pr_info("PHY1 is up.\n");
	अन्यथा
		pr_info("PHY1 is down.\n");

	pr_info("XLP AHCI Init Done.\n");
पूर्ण

अटल पूर्णांक __init nlm_ahci_init(व्योम)
अणु
	पूर्णांक node;

	अगर (!cpu_is_xlp9xx())
		वापस 0;
	क्रम (node = 0; node < NLM_NR_NODES; node++)
		अगर (nlm_node_present(node))
			nlm_sata_firmware_init(node);
	वापस 0;
पूर्ण

अटल व्योम nlm_sata_पूर्णांकr_ack(काष्ठा irq_data *data)
अणु
	u64 regbase;
	u32 val;
	पूर्णांक node;

	node = data->irq / NLM_IRQS_PER_NODE;
	regbase = nlm_get_sata_regbase(node);
	val = nlm_पढ़ो_sata_reg(regbase, SATA_INT);
	sata_set_glue_reg(regbase, SATA_INT, val);
पूर्ण

अटल व्योम nlm_sata_fixup_bar(काष्ठा pci_dev *dev)
अणु
	dev->resource[5] = dev->resource[0];
	स_रखो(&dev->resource[0], 0, माप(dev->resource[0]));
पूर्ण

अटल व्योम nlm_sata_fixup_final(काष्ठा pci_dev *dev)
अणु
	u32 val;
	u64 regbase;
	पूर्णांक node;

	/* Find end bridge function to find node */
	node = xlp_socdev_to_node(dev);
	regbase = nlm_get_sata_regbase(node);

	/* clear pending पूर्णांकerrupts and then enable them */
	val = nlm_पढ़ो_sata_reg(regbase, SATA_INT);
	sata_set_glue_reg(regbase, SATA_INT, val);

	/* Enable only the core पूर्णांकerrupt */
	sata_set_glue_reg(regbase, SATA_INT_MASK, 0x1);

	dev->irq = nlm_irq_to_xirq(node, PIC_SATA_IRQ);
	nlm_set_pic_extra_ack(node, PIC_SATA_IRQ, nlm_sata_पूर्णांकr_ack);
पूर्ण

arch_initcall(nlm_ahci_init);

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_XLP9XX_SATA,
		nlm_sata_fixup_bar);

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_XLP9XX_SATA,
		nlm_sata_fixup_final);
