<शैली गुरु>
/*
 * Copyright (c) 2003-2013 Broadcom Corporation
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
#समावेश <linux/pci_ids.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>

#घोषणा XLPII_USB3_CTL_0		0xc0
#घोषणा XLPII_VAUXRST			BIT(0)
#घोषणा XLPII_VCCRST			BIT(1)
#घोषणा XLPII_NUM2PORT			9
#घोषणा XLPII_NUM3PORT			13
#घोषणा XLPII_RTUNEREQ			BIT(20)
#घोषणा XLPII_MS_CSYSREQ		BIT(21)
#घोषणा XLPII_XS_CSYSREQ		BIT(22)
#घोषणा XLPII_RETENABLEN		BIT(23)
#घोषणा XLPII_TX2RX			BIT(24)
#घोषणा XLPII_XHCIREV			BIT(25)
#घोषणा XLPII_ECCDIS			BIT(26)

#घोषणा XLPII_USB3_INT_REG		0xc2
#घोषणा XLPII_USB3_INT_MASK		0xc3

#घोषणा XLPII_USB_PHY_TEST		0xc6
#घोषणा XLPII_PRESET			BIT(0)
#घोषणा XLPII_ATERESET			BIT(1)
#घोषणा XLPII_LOOPEN			BIT(2)
#घोषणा XLPII_TESTPDHSP			BIT(3)
#घोषणा XLPII_TESTPDSSP			BIT(4)
#घोषणा XLPII_TESTBURNIN		BIT(5)

#घोषणा XLPII_USB_PHY_LOS_LV		0xc9
#घोषणा XLPII_LOSLEV			0
#घोषणा XLPII_LOSBIAS			5
#घोषणा XLPII_SQRXTX			8
#घोषणा XLPII_TXBOOST			11
#घोषणा XLPII_RSLKSEL			16
#घोषणा XLPII_FSEL			20

#घोषणा XLPII_USB_RFCLK_REG		0xcc
#घोषणा XLPII_VVLD			30

#घोषणा nlm_पढ़ो_usb_reg(b, r)		nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_usb_reg(b, r, v)	nlm_ग_लिखो_reg(b, r, v)

#घोषणा nlm_xlpii_get_usb_pcibase(node, inst)			\
			nlm_pcicfg_base(cpu_is_xlp9xx() ?	\
			XLP9XX_IO_USB_OFFSET(node, inst) :	\
			XLP2XX_IO_USB_OFFSET(node, inst))
#घोषणा nlm_xlpii_get_usb_regbase(node, inst)		\
	(nlm_xlpii_get_usb_pcibase(node, inst) + XLP_IO_PCI_HDRSZ)

अटल व्योम xlp2xx_usb_ack(काष्ठा irq_data *data)
अणु
	u64 port_addr;

	चयन (data->irq) अणु
	हाल PIC_2XX_XHCI_0_IRQ:
		port_addr = nlm_xlpii_get_usb_regbase(0, 1);
		अवरोध;
	हाल PIC_2XX_XHCI_1_IRQ:
		port_addr = nlm_xlpii_get_usb_regbase(0, 2);
		अवरोध;
	हाल PIC_2XX_XHCI_2_IRQ:
		port_addr = nlm_xlpii_get_usb_regbase(0, 3);
		अवरोध;
	शेष:
		pr_err("No matching USB irq!\n");
		वापस;
	पूर्ण
	nlm_ग_लिखो_usb_reg(port_addr, XLPII_USB3_INT_REG, 0xffffffff);
पूर्ण

अटल व्योम xlp9xx_usb_ack(काष्ठा irq_data *data)
अणु
	u64 port_addr;
	पूर्णांक node, irq;

	/* Find the node and irq on the node */
	irq = data->irq % NLM_IRQS_PER_NODE;
	node = data->irq / NLM_IRQS_PER_NODE;

	चयन (irq) अणु
	हाल PIC_9XX_XHCI_0_IRQ:
		port_addr = nlm_xlpii_get_usb_regbase(node, 1);
		अवरोध;
	हाल PIC_9XX_XHCI_1_IRQ:
		port_addr = nlm_xlpii_get_usb_regbase(node, 2);
		अवरोध;
	हाल PIC_9XX_XHCI_2_IRQ:
		port_addr = nlm_xlpii_get_usb_regbase(node, 3);
		अवरोध;
	शेष:
		pr_err("No matching USB irq %d node  %d!\n", irq, node);
		वापस;
	पूर्ण
	nlm_ग_लिखो_usb_reg(port_addr, XLPII_USB3_INT_REG, 0xffffffff);
पूर्ण

अटल व्योम nlm_xlpii_usb_hw_reset(पूर्णांक node, पूर्णांक port)
अणु
	u64 port_addr, xhci_base, pci_base;
	व्योम __iomem *corebase;
	u32 val;

	port_addr = nlm_xlpii_get_usb_regbase(node, port);

	/* Set frequency */
	val = nlm_पढ़ो_usb_reg(port_addr, XLPII_USB_PHY_LOS_LV);
	val &= ~(0x3f << XLPII_FSEL);
	val |= (0x27 << XLPII_FSEL);
	nlm_ग_लिखो_usb_reg(port_addr, XLPII_USB_PHY_LOS_LV, val);

	val = nlm_पढ़ो_usb_reg(port_addr, XLPII_USB_RFCLK_REG);
	val |= (1 << XLPII_VVLD);
	nlm_ग_लिखो_usb_reg(port_addr, XLPII_USB_RFCLK_REG, val);

	/* PHY reset */
	val = nlm_पढ़ो_usb_reg(port_addr, XLPII_USB_PHY_TEST);
	val &= (XLPII_ATERESET | XLPII_LOOPEN | XLPII_TESTPDHSP
		| XLPII_TESTPDSSP | XLPII_TESTBURNIN);
	nlm_ग_लिखो_usb_reg(port_addr, XLPII_USB_PHY_TEST, val);

	/* Setup control रेजिस्टर */
	val =  XLPII_VAUXRST | XLPII_VCCRST | (1 << XLPII_NUM2PORT)
		| (1 << XLPII_NUM3PORT) | XLPII_MS_CSYSREQ | XLPII_XS_CSYSREQ
		| XLPII_RETENABLEN | XLPII_XHCIREV;
	nlm_ग_लिखो_usb_reg(port_addr, XLPII_USB3_CTL_0, val);

	/* Enable पूर्णांकerrupts */
	nlm_ग_लिखो_usb_reg(port_addr, XLPII_USB3_INT_MASK, 0x00000001);

	/* Clear all पूर्णांकerrupts */
	nlm_ग_लिखो_usb_reg(port_addr, XLPII_USB3_INT_REG, 0xffffffff);

	udelay(2000);

	/* XHCI configuration at PCI mem */
	pci_base = nlm_xlpii_get_usb_pcibase(node, port);
	xhci_base = nlm_पढ़ो_usb_reg(pci_base, 0x4) & ~0xf;
	corebase = ioremap(xhci_base, 0x10000);
	अगर (!corebase)
		वापस;

	ग_लिखोl(0x240002, corebase + 0xc2c0);
	/* GCTL 0xc110 */
	val = पढ़ोl(corebase + 0xc110);
	val &= ~(0x3 << 12);
	val |= (1 << 12);
	ग_लिखोl(val, corebase + 0xc110);
	udelay(100);

	/* PHYCFG 0xc200 */
	val = पढ़ोl(corebase + 0xc200);
	val &= ~(1 << 6);
	ग_लिखोl(val, corebase + 0xc200);
	udelay(100);

	/* PIPECTL 0xc2c0 */
	val = पढ़ोl(corebase + 0xc2c0);
	val &= ~(1 << 17);
	ग_लिखोl(val, corebase + 0xc2c0);

	iounmap(corebase);
पूर्ण

अटल पूर्णांक __init nlm_platक्रमm_xlpii_usb_init(व्योम)
अणु
	पूर्णांक node;

	अगर (!cpu_is_xlpii())
		वापस 0;

	अगर (!cpu_is_xlp9xx()) अणु
		/* XLP 2XX single node */
		pr_info("Initializing 2XX USB Interface\n");
		nlm_xlpii_usb_hw_reset(0, 1);
		nlm_xlpii_usb_hw_reset(0, 2);
		nlm_xlpii_usb_hw_reset(0, 3);
		nlm_set_pic_extra_ack(0, PIC_2XX_XHCI_0_IRQ, xlp2xx_usb_ack);
		nlm_set_pic_extra_ack(0, PIC_2XX_XHCI_1_IRQ, xlp2xx_usb_ack);
		nlm_set_pic_extra_ack(0, PIC_2XX_XHCI_2_IRQ, xlp2xx_usb_ack);
		वापस 0;
	पूर्ण

	/* XLP 9XX, multi-node */
	pr_info("Initializing 9XX/5XX USB Interface\n");
	क्रम (node = 0; node < NLM_NR_NODES; node++) अणु
		अगर (!nlm_node_present(node))
			जारी;
		nlm_xlpii_usb_hw_reset(node, 1);
		nlm_xlpii_usb_hw_reset(node, 2);
		nlm_xlpii_usb_hw_reset(node, 3);
		nlm_set_pic_extra_ack(node, PIC_9XX_XHCI_0_IRQ, xlp9xx_usb_ack);
		nlm_set_pic_extra_ack(node, PIC_9XX_XHCI_1_IRQ, xlp9xx_usb_ack);
		nlm_set_pic_extra_ack(node, PIC_9XX_XHCI_2_IRQ, xlp9xx_usb_ack);
	पूर्ण
	वापस 0;
पूर्ण

arch_initcall(nlm_platक्रमm_xlpii_usb_init);

अटल u64 xlp_usb_dmamask = ~(u32)0;

/* Fixup the IRQ क्रम USB devices which is exist on XLP9XX SOC PCIE bus */
अटल व्योम nlm_xlp9xx_usb_fixup_final(काष्ठा pci_dev *dev)
अणु
	पूर्णांक node;

	node = xlp_socdev_to_node(dev);
	dev->dev.dma_mask		= &xlp_usb_dmamask;
	dev->dev.coherent_dma_mask	= DMA_BIT_MASK(32);
	चयन (dev->devfn) अणु
	हाल 0x21:
		dev->irq = nlm_irq_to_xirq(node, PIC_9XX_XHCI_0_IRQ);
		अवरोध;
	हाल 0x22:
		dev->irq = nlm_irq_to_xirq(node, PIC_9XX_XHCI_1_IRQ);
		अवरोध;
	हाल 0x23:
		dev->irq = nlm_irq_to_xirq(node, PIC_9XX_XHCI_2_IRQ);
		अवरोध;
	पूर्ण
पूर्ण

/* Fixup the IRQ क्रम USB devices which is exist on XLP2XX SOC PCIE bus */
अटल व्योम nlm_xlp2xx_usb_fixup_final(काष्ठा pci_dev *dev)
अणु
	dev->dev.dma_mask		= &xlp_usb_dmamask;
	dev->dev.coherent_dma_mask	= DMA_BIT_MASK(32);
	चयन (dev->devfn) अणु
	हाल 0x21:
		dev->irq = PIC_2XX_XHCI_0_IRQ;
		अवरोध;
	हाल 0x22:
		dev->irq = PIC_2XX_XHCI_1_IRQ;
		अवरोध;
	हाल 0x23:
		dev->irq = PIC_2XX_XHCI_2_IRQ;
		अवरोध;
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_XLP9XX_XHCI,
		nlm_xlp9xx_usb_fixup_final);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_NETLOGIC, PCI_DEVICE_ID_NLM_XHCI,
		nlm_xlp2xx_usb_fixup_final);
