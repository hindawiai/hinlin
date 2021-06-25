<शैली गुरु>
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
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

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/msi.h>
#समावेश <linux/mm.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/console.h>

#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/netlogic/पूर्णांकerrupt.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/mips-extns.h>

#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/pic.h>
#समावेश <यंत्र/netlogic/xlp-hal/pcibus.h>
#समावेश <यंत्र/netlogic/xlp-hal/bridge.h>

#घोषणा XLP_MSIVEC_PER_LINK	32
#घोषणा XLP_MSIXVEC_TOTAL	(cpu_is_xlp9xx() ? 128 : 32)
#घोषणा XLP_MSIXVEC_PER_LINK	(cpu_is_xlp9xx() ? 32 : 8)

/* 128 MSI irqs per node, mapped starting at NLM_MSI_VEC_BASE */
अटल अंतरभूत पूर्णांक nlm_link_msiirq(पूर्णांक link, पूर्णांक msivec)
अणु
	वापस NLM_MSI_VEC_BASE + link * XLP_MSIVEC_PER_LINK + msivec;
पूर्ण

/* get the link MSI vector from irq number */
अटल अंतरभूत पूर्णांक nlm_irq_msivec(पूर्णांक irq)
अणु
	वापस (irq - NLM_MSI_VEC_BASE) % XLP_MSIVEC_PER_LINK;
पूर्ण

/* get the link from the irq number */
अटल अंतरभूत पूर्णांक nlm_irq_msilink(पूर्णांक irq)
अणु
	पूर्णांक total_msivec = XLP_MSIVEC_PER_LINK * PCIE_NLINKS;

	वापस ((irq - NLM_MSI_VEC_BASE) % total_msivec) /
		XLP_MSIVEC_PER_LINK;
पूर्ण

/*
 * For XLP 8xx/4xx/3xx/2xx, only 32 MSI-X vectors are possible because
 * there are only 32 PIC पूर्णांकerrupts क्रम MSI. We split them अटलally
 * and use 8 MSI-X vectors per link - this keeps the allocation and
 * lookup simple.
 * On XLP 9xx, there are 32 vectors per link, and the पूर्णांकerrupts are
 * not routed thru PIC, so we can use all 128 MSI-X vectors.
 */
अटल अंतरभूत पूर्णांक nlm_link_msixirq(पूर्णांक link, पूर्णांक bit)
अणु
	वापस NLM_MSIX_VEC_BASE + link * XLP_MSIXVEC_PER_LINK + bit;
पूर्ण

/* get the link MSI vector from irq number */
अटल अंतरभूत पूर्णांक nlm_irq_msixvec(पूर्णांक irq)
अणु
	वापस (irq - NLM_MSIX_VEC_BASE) % XLP_MSIXVEC_TOTAL;
पूर्ण

/* get the link from MSIX vec */
अटल अंतरभूत पूर्णांक nlm_irq_msixlink(पूर्णांक msixvec)
अणु
	वापस msixvec / XLP_MSIXVEC_PER_LINK;
पूर्ण

/*
 * Per link MSI and MSI-X inक्रमmation, set as IRQ handler data क्रम
 * MSI and MSI-X पूर्णांकerrupts.
 */
काष्ठा xlp_msi_data अणु
	काष्ठा nlm_soc_info *node;
	uपूर्णांक64_t	lnkbase;
	uपूर्णांक32_t	msi_enabled_mask;
	uपूर्णांक32_t	msi_alloc_mask;
	uपूर्णांक32_t	msix_alloc_mask;
	spinlock_t	msi_lock;
पूर्ण;

/*
 * MSI Chip definitions
 *
 * On XLP, there is a PIC पूर्णांकerrupt associated with each PCIe link on the
 * chip (which appears as a PCI bridge to us). This gives us 32 MSI irqa
 * per link and 128 overall.
 *
 * When a device connected to the link उठाओs a MSI पूर्णांकerrupt, we get a
 * link पूर्णांकerrupt and we then have to look at PCIE_MSI_STATUS रेजिस्टर at
 * the bridge to map it to the IRQ
 */
अटल व्योम xlp_msi_enable(काष्ठा irq_data *d)
अणु
	काष्ठा xlp_msi_data *md = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;
	पूर्णांक vec;

	vec = nlm_irq_msivec(d->irq);
	spin_lock_irqsave(&md->msi_lock, flags);
	md->msi_enabled_mask |= 1u << vec;
	अगर (cpu_is_xlp9xx())
		nlm_ग_लिखो_reg(md->lnkbase, PCIE_9XX_MSI_EN,
				md->msi_enabled_mask);
	अन्यथा
		nlm_ग_लिखो_reg(md->lnkbase, PCIE_MSI_EN, md->msi_enabled_mask);
	spin_unlock_irqrestore(&md->msi_lock, flags);
पूर्ण

अटल व्योम xlp_msi_disable(काष्ठा irq_data *d)
अणु
	काष्ठा xlp_msi_data *md = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;
	पूर्णांक vec;

	vec = nlm_irq_msivec(d->irq);
	spin_lock_irqsave(&md->msi_lock, flags);
	md->msi_enabled_mask &= ~(1u << vec);
	अगर (cpu_is_xlp9xx())
		nlm_ग_लिखो_reg(md->lnkbase, PCIE_9XX_MSI_EN,
				md->msi_enabled_mask);
	अन्यथा
		nlm_ग_लिखो_reg(md->lnkbase, PCIE_MSI_EN, md->msi_enabled_mask);
	spin_unlock_irqrestore(&md->msi_lock, flags);
पूर्ण

अटल व्योम xlp_msi_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा xlp_msi_data *md = irq_data_get_irq_chip_data(d);
	पूर्णांक link, vec;

	link = nlm_irq_msilink(d->irq);
	vec = nlm_irq_msivec(d->irq);
	xlp_msi_disable(d);

	/* Ack MSI on bridge */
	अगर (cpu_is_xlp9xx())
		nlm_ग_लिखो_reg(md->lnkbase, PCIE_9XX_MSI_STATUS, 1u << vec);
	अन्यथा
		nlm_ग_लिखो_reg(md->lnkbase, PCIE_MSI_STATUS, 1u << vec);

पूर्ण

अटल काष्ठा irq_chip xlp_msi_chip = अणु
	.name		= "XLP-MSI",
	.irq_enable	= xlp_msi_enable,
	.irq_disable	= xlp_msi_disable,
	.irq_mask_ack	= xlp_msi_mask_ack,
	.irq_unmask	= xlp_msi_enable,
पूर्ण;

/*
 * XLP8XX/4XX/3XX/2XX:
 * The MSI-X पूर्णांकerrupt handling is dअगरferent from MSI, there are 32 MSI-X
 * पूर्णांकerrupts generated by the PIC and each of these correspond to a MSI-X
 * vector (0-31) that can be asचिन्हित.
 *
 * We भागide the MSI-X vectors to 8 per link and करो a per-link allocation
 *
 * XLP9XX:
 * 32 MSI-X vectors are available per link, and the पूर्णांकerrupts are not routed
 * thru the PIC. PIC ack not needed.
 *
 * Enable and disable करोne using standard MSI functions.
 */
अटल व्योम xlp_msix_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा xlp_msi_data *md;
	पूर्णांक link, msixvec;
	uपूर्णांक32_t status_reg, bit;

	msixvec = nlm_irq_msixvec(d->irq);
	link = nlm_irq_msixlink(msixvec);
	pci_msi_mask_irq(d);
	md = irq_data_get_irq_chip_data(d);

	/* Ack MSI on bridge */
	अगर (cpu_is_xlp9xx()) अणु
		status_reg = PCIE_9XX_MSIX_STATUSX(link);
		bit = msixvec % XLP_MSIXVEC_PER_LINK;
	पूर्ण अन्यथा अणु
		status_reg = PCIE_MSIX_STATUS;
		bit = msixvec;
	पूर्ण
	nlm_ग_लिखो_reg(md->lnkbase, status_reg, 1u << bit);

	अगर (!cpu_is_xlp9xx())
		nlm_pic_ack(md->node->picbase,
				PIC_IRT_PCIE_MSIX_INDEX(msixvec));
पूर्ण

अटल काष्ठा irq_chip xlp_msix_chip = अणु
	.name		= "XLP-MSIX",
	.irq_enable	= pci_msi_unmask_irq,
	.irq_disable	= pci_msi_mask_irq,
	.irq_mask_ack	= xlp_msix_mask_ack,
	.irq_unmask	= pci_msi_unmask_irq,
पूर्ण;

व्योम arch_tearकरोwn_msi_irq(अचिन्हित पूर्णांक irq)
अणु
पूर्ण

/*
 * Setup a PCIe link क्रम MSI.  By शेष, the links are in
 * legacy पूर्णांकerrupt mode.  We will चयन them to MSI mode
 * at the first MSI request.
 */
अटल व्योम xlp_config_link_msi(uपूर्णांक64_t lnkbase, पूर्णांक lirq, uपूर्णांक64_t msiaddr)
अणु
	u32 val;

	अगर (cpu_is_xlp9xx()) अणु
		val = nlm_पढ़ो_reg(lnkbase, PCIE_9XX_INT_EN0);
		अगर ((val & 0x200) == 0) अणु
			val |= 0x200;		/* MSI Interrupt enable */
			nlm_ग_लिखो_reg(lnkbase, PCIE_9XX_INT_EN0, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		val = nlm_पढ़ो_reg(lnkbase, PCIE_INT_EN0);
		अगर ((val & 0x200) == 0) अणु
			val |= 0x200;
			nlm_ग_लिखो_reg(lnkbase, PCIE_INT_EN0, val);
		पूर्ण
	पूर्ण

	val = nlm_पढ़ो_reg(lnkbase, 0x1);	/* CMD */
	अगर ((val & 0x0400) == 0) अणु
		val |= 0x0400;
		nlm_ग_लिखो_reg(lnkbase, 0x1, val);
	पूर्ण

	/* Update IRQ in the PCI irq reg */
	val = nlm_पढ़ो_pci_reg(lnkbase, 0xf);
	val &= ~0x1fu;
	val |= (1 << 8) | lirq;
	nlm_ग_लिखो_pci_reg(lnkbase, 0xf, val);

	/* MSI addr */
	nlm_ग_लिखो_reg(lnkbase, PCIE_BRIDGE_MSI_ADDRH, msiaddr >> 32);
	nlm_ग_लिखो_reg(lnkbase, PCIE_BRIDGE_MSI_ADDRL, msiaddr & 0xffffffff);

	/* MSI cap क्रम bridge */
	val = nlm_पढ़ो_reg(lnkbase, PCIE_BRIDGE_MSI_CAP);
	अगर ((val & (1 << 16)) == 0) अणु
		val |= 0xb << 16;		/* mmc32, msi enable */
		nlm_ग_लिखो_reg(lnkbase, PCIE_BRIDGE_MSI_CAP, val);
	पूर्ण
पूर्ण

/*
 * Allocate a MSI vector on a link
 */
अटल पूर्णांक xlp_setup_msi(uपूर्णांक64_t lnkbase, पूर्णांक node, पूर्णांक link,
	काष्ठा msi_desc *desc)
अणु
	काष्ठा xlp_msi_data *md;
	काष्ठा msi_msg msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक msivec, irt, lirq, xirq, ret;
	uपूर्णांक64_t msiaddr;

	/* Get MSI data क्रम the link */
	lirq = PIC_PCIE_LINK_MSI_IRQ(link);
	xirq = nlm_irq_to_xirq(node, nlm_link_msiirq(link, 0));
	md = irq_get_chip_data(xirq);
	msiaddr = MSI_LINK_ADDR(node, link);

	spin_lock_irqsave(&md->msi_lock, flags);
	अगर (md->msi_alloc_mask == 0) अणु
		xlp_config_link_msi(lnkbase, lirq, msiaddr);
		/* चयन the link IRQ to MSI range */
		अगर (cpu_is_xlp9xx())
			irt = PIC_9XX_IRT_PCIE_LINK_INDEX(link);
		अन्यथा
			irt = PIC_IRT_PCIE_LINK_INDEX(link);
		nlm_setup_pic_irq(node, lirq, lirq, irt);
		nlm_pic_init_irt(nlm_get_node(node)->picbase, irt, lirq,
				 node * nlm_thपढ़ोs_per_node(), 1 /*en */);
	पूर्ण

	/* allocate a MSI vec, and tell the bridge about it */
	msivec = fls(md->msi_alloc_mask);
	अगर (msivec == XLP_MSIVEC_PER_LINK) अणु
		spin_unlock_irqrestore(&md->msi_lock, flags);
		वापस -ENOMEM;
	पूर्ण
	md->msi_alloc_mask |= (1u << msivec);
	spin_unlock_irqrestore(&md->msi_lock, flags);

	msg.address_hi = msiaddr >> 32;
	msg.address_lo = msiaddr & 0xffffffff;
	msg.data = 0xc00 | msivec;

	xirq = xirq + msivec;		/* msi mapped to global irq space */
	ret = irq_set_msi_desc(xirq, desc);
	अगर (ret < 0)
		वापस ret;

	pci_ग_लिखो_msi_msg(xirq, &msg);
	वापस 0;
पूर्ण

/*
 * Switch a link to MSI-X mode
 */
अटल व्योम xlp_config_link_msix(uपूर्णांक64_t lnkbase, पूर्णांक lirq, uपूर्णांक64_t msixaddr)
अणु
	u32 val;

	val = nlm_पढ़ो_reg(lnkbase, 0x2C);
	अगर ((val & 0x80000000U) == 0) अणु
		val |= 0x80000000U;
		nlm_ग_लिखो_reg(lnkbase, 0x2C, val);
	पूर्ण

	अगर (cpu_is_xlp9xx()) अणु
		val = nlm_पढ़ो_reg(lnkbase, PCIE_9XX_INT_EN0);
		अगर ((val & 0x200) == 0) अणु
			val |= 0x200;		/* MSI Interrupt enable */
			nlm_ग_लिखो_reg(lnkbase, PCIE_9XX_INT_EN0, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		val = nlm_पढ़ो_reg(lnkbase, PCIE_INT_EN0);
		अगर ((val & 0x200) == 0) अणु
			val |= 0x200;		/* MSI Interrupt enable */
			nlm_ग_लिखो_reg(lnkbase, PCIE_INT_EN0, val);
		पूर्ण
	पूर्ण

	val = nlm_पढ़ो_reg(lnkbase, 0x1);	/* CMD */
	अगर ((val & 0x0400) == 0) अणु
		val |= 0x0400;
		nlm_ग_लिखो_reg(lnkbase, 0x1, val);
	पूर्ण

	/* Update IRQ in the PCI irq reg */
	val = nlm_पढ़ो_pci_reg(lnkbase, 0xf);
	val &= ~0x1fu;
	val |= (1 << 8) | lirq;
	nlm_ग_लिखो_pci_reg(lnkbase, 0xf, val);

	अगर (cpu_is_xlp9xx()) अणु
		/* MSI-X addresses */
		nlm_ग_लिखो_reg(lnkbase, PCIE_9XX_BRIDGE_MSIX_ADDR_BASE,
				msixaddr >> 8);
		nlm_ग_लिखो_reg(lnkbase, PCIE_9XX_BRIDGE_MSIX_ADDR_LIMIT,
				(msixaddr + MSI_ADDR_SZ) >> 8);
	पूर्ण अन्यथा अणु
		/* MSI-X addresses */
		nlm_ग_लिखो_reg(lnkbase, PCIE_BRIDGE_MSIX_ADDR_BASE,
				msixaddr >> 8);
		nlm_ग_लिखो_reg(lnkbase, PCIE_BRIDGE_MSIX_ADDR_LIMIT,
				(msixaddr + MSI_ADDR_SZ) >> 8);
	पूर्ण
पूर्ण

/*
 *  Allocate a MSI-X vector
 */
अटल पूर्णांक xlp_setup_msix(uपूर्णांक64_t lnkbase, पूर्णांक node, पूर्णांक link,
	काष्ठा msi_desc *desc)
अणु
	काष्ठा xlp_msi_data *md;
	काष्ठा msi_msg msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक t, msixvec, lirq, xirq, ret;
	uपूर्णांक64_t msixaddr;

	/* Get MSI data क्रम the link */
	lirq = PIC_PCIE_MSIX_IRQ(link);
	xirq = nlm_irq_to_xirq(node, nlm_link_msixirq(link, 0));
	md = irq_get_chip_data(xirq);
	msixaddr = MSIX_LINK_ADDR(node, link);

	spin_lock_irqsave(&md->msi_lock, flags);
	/* चयन the PCIe link to MSI-X mode at the first alloc */
	अगर (md->msix_alloc_mask == 0)
		xlp_config_link_msix(lnkbase, lirq, msixaddr);

	/* allocate a MSI-X vec, and tell the bridge about it */
	t = fls(md->msix_alloc_mask);
	अगर (t == XLP_MSIXVEC_PER_LINK) अणु
		spin_unlock_irqrestore(&md->msi_lock, flags);
		वापस -ENOMEM;
	पूर्ण
	md->msix_alloc_mask |= (1u << t);
	spin_unlock_irqrestore(&md->msi_lock, flags);

	xirq += t;
	msixvec = nlm_irq_msixvec(xirq);

	msg.address_hi = msixaddr >> 32;
	msg.address_lo = msixaddr & 0xffffffff;
	msg.data = 0xc00 | msixvec;

	ret = irq_set_msi_desc(xirq, desc);
	अगर (ret < 0)
		वापस ret;

	pci_ग_लिखो_msi_msg(xirq, &msg);
	वापस 0;
पूर्ण

पूर्णांक arch_setup_msi_irq(काष्ठा pci_dev *dev, काष्ठा msi_desc *desc)
अणु
	काष्ठा pci_dev *lnkdev;
	uपूर्णांक64_t lnkbase;
	पूर्णांक node, link, slot;

	lnkdev = xlp_get_pcie_link(dev);
	अगर (lnkdev == शून्य) अणु
		dev_err(&dev->dev, "Could not find bridge\n");
		वापस 1;
	पूर्ण
	slot = PCI_SLOT(lnkdev->devfn);
	link = PCI_FUNC(lnkdev->devfn);
	node = slot / 8;
	lnkbase = nlm_get_pcie_base(node, link);

	अगर (desc->msi_attrib.is_msix)
		वापस xlp_setup_msix(lnkbase, node, link, desc);
	अन्यथा
		वापस xlp_setup_msi(lnkbase, node, link, desc);
पूर्ण

व्योम __init xlp_init_node_msi_irqs(पूर्णांक node, पूर्णांक link)
अणु
	काष्ठा nlm_soc_info *nodep;
	काष्ठा xlp_msi_data *md;
	पूर्णांक irq, i, irt, msixvec, val;

	pr_info("[%d %d] Init node PCI IRT\n", node, link);
	nodep = nlm_get_node(node);

	/* Alloc an MSI block क्रम the link */
	md = kzalloc(माप(*md), GFP_KERNEL);
	spin_lock_init(&md->msi_lock);
	md->msi_enabled_mask = 0;
	md->msi_alloc_mask = 0;
	md->msix_alloc_mask = 0;
	md->node = nodep;
	md->lnkbase = nlm_get_pcie_base(node, link);

	/* extended space क्रम MSI पूर्णांकerrupts */
	irq = nlm_irq_to_xirq(node, nlm_link_msiirq(link, 0));
	क्रम (i = irq; i < irq + XLP_MSIVEC_PER_LINK; i++) अणु
		irq_set_chip_and_handler(i, &xlp_msi_chip, handle_level_irq);
		irq_set_chip_data(i, md);
	पूर्ण

	क्रम (i = 0; i < XLP_MSIXVEC_PER_LINK ; i++) अणु
		अगर (cpu_is_xlp9xx()) अणु
			val = ((node * nlm_thपढ़ोs_per_node()) << 7 |
				PIC_PCIE_MSIX_IRQ(link) << 1 | 0 << 0);
			nlm_ग_लिखो_pcie_reg(md->lnkbase, PCIE_9XX_MSIX_VECX(i +
					(link * XLP_MSIXVEC_PER_LINK)), val);
		पूर्ण अन्यथा अणु
			/* Initialize MSI-X irts to generate one पूर्णांकerrupt
			 * per link
			 */
			msixvec = link * XLP_MSIXVEC_PER_LINK + i;
			irt = PIC_IRT_PCIE_MSIX_INDEX(msixvec);
			nlm_pic_init_irt(nodep->picbase, irt,
					PIC_PCIE_MSIX_IRQ(link),
					node * nlm_thपढ़ोs_per_node(), 1);
		पूर्ण

		/* Initialize MSI-X extended irq space क्रम the link  */
		irq = nlm_irq_to_xirq(node, nlm_link_msixirq(link, i));
		irq_set_chip_and_handler(irq, &xlp_msix_chip, handle_level_irq);
		irq_set_chip_data(irq, md);
	पूर्ण
पूर्ण

व्योम nlm_dispatch_msi(पूर्णांक node, पूर्णांक lirq)
अणु
	काष्ठा xlp_msi_data *md;
	पूर्णांक link, i, irqbase;
	u32 status;

	link = lirq - PIC_PCIE_LINK_MSI_IRQ_BASE;
	irqbase = nlm_irq_to_xirq(node, nlm_link_msiirq(link, 0));
	md = irq_get_chip_data(irqbase);
	अगर (cpu_is_xlp9xx())
		status = nlm_पढ़ो_reg(md->lnkbase, PCIE_9XX_MSI_STATUS) &
						md->msi_enabled_mask;
	अन्यथा
		status = nlm_पढ़ो_reg(md->lnkbase, PCIE_MSI_STATUS) &
						md->msi_enabled_mask;
	जबतक (status) अणु
		i = __ffs(status);
		करो_IRQ(irqbase + i);
		status &= status - 1;
	पूर्ण

	/* Ack at eirr and PIC */
	ack_c0_eirr(PIC_PCIE_LINK_MSI_IRQ(link));
	अगर (cpu_is_xlp9xx())
		nlm_pic_ack(md->node->picbase,
				PIC_9XX_IRT_PCIE_LINK_INDEX(link));
	अन्यथा
		nlm_pic_ack(md->node->picbase, PIC_IRT_PCIE_LINK_INDEX(link));
पूर्ण

व्योम nlm_dispatch_msix(पूर्णांक node, पूर्णांक lirq)
अणु
	काष्ठा xlp_msi_data *md;
	पूर्णांक link, i, irqbase;
	u32 status;

	link = lirq - PIC_PCIE_MSIX_IRQ_BASE;
	irqbase = nlm_irq_to_xirq(node, nlm_link_msixirq(link, 0));
	md = irq_get_chip_data(irqbase);
	अगर (cpu_is_xlp9xx())
		status = nlm_पढ़ो_reg(md->lnkbase, PCIE_9XX_MSIX_STATUSX(link));
	अन्यथा
		status = nlm_पढ़ो_reg(md->lnkbase, PCIE_MSIX_STATUS);

	/* narrow it करोwn to the MSI-x vectors क्रम our link */
	अगर (!cpu_is_xlp9xx())
		status = (status >> (link * XLP_MSIXVEC_PER_LINK)) &
			((1 << XLP_MSIXVEC_PER_LINK) - 1);

	जबतक (status) अणु
		i = __ffs(status);
		करो_IRQ(irqbase + i);
		status &= status - 1;
	पूर्ण
	/* Ack at eirr and PIC */
	ack_c0_eirr(PIC_PCIE_MSIX_IRQ(link));
पूर्ण
