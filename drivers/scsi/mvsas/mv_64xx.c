<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell 88SE64xx hardware specअगरic
 *
 * Copyright 2007 Red Hat, Inc.
 * Copyright 2008 Marvell. <kewei@marvell.com>
 * Copyright 2009-2011 Marvell. <yuxiangl@marvell.com>
*/

#समावेश "mv_sas.h"
#समावेश "mv_64xx.h"
#समावेश "mv_chips.h"

अटल व्योम mvs_64xx_detect_porttype(काष्ठा mvs_info *mvi, पूर्णांक i)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 reg;
	काष्ठा mvs_phy *phy = &mvi->phy[i];

	reg = mr32(MVS_GBL_PORT_TYPE);
	phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	अगर (reg & MODE_SAS_SATA & (1 << i))
		phy->phy_type |= PORT_TYPE_SAS;
	अन्यथा
		phy->phy_type |= PORT_TYPE_SATA;
पूर्ण

अटल व्योम mvs_64xx_enable_xmt(काष्ठा mvs_info *mvi, पूर्णांक phy_id)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;

	पंचांगp = mr32(MVS_PCS);
	अगर (mvi->chip->n_phy <= MVS_SOC_PORTS)
		पंचांगp |= 1 << (phy_id + PCS_EN_PORT_XMT_SHIFT);
	अन्यथा
		पंचांगp |= 1 << (phy_id + PCS_EN_PORT_XMT_SHIFT2);
	mw32(MVS_PCS, पंचांगp);
पूर्ण

अटल व्योम mvs_64xx_phy_hacks(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	पूर्णांक i;

	mvs_phy_hacks(mvi);

	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		क्रम (i = 0; i < MVS_SOC_PORTS; i++) अणु
			mvs_ग_लिखो_port_vsr_addr(mvi, i, VSR_PHY_MODE8);
			mvs_ग_लिखो_port_vsr_data(mvi, i, 0x2F0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable स्वतः port detection */
		mw32(MVS_GBL_PORT_TYPE, 0);
		क्रम (i = 0; i < mvi->chip->n_phy; i++) अणु
			mvs_ग_लिखो_port_vsr_addr(mvi, i, VSR_PHY_MODE7);
			mvs_ग_लिखो_port_vsr_data(mvi, i, 0x90000000);
			mvs_ग_लिखो_port_vsr_addr(mvi, i, VSR_PHY_MODE9);
			mvs_ग_लिखो_port_vsr_data(mvi, i, 0x50f2);
			mvs_ग_लिखो_port_vsr_addr(mvi, i, VSR_PHY_MODE11);
			mvs_ग_लिखो_port_vsr_data(mvi, i, 0x0e);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mvs_64xx_stp_reset(काष्ठा mvs_info *mvi, u32 phy_id)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 reg, पंचांगp;

	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		अगर (phy_id < MVS_SOC_PORTS)
			pci_पढ़ो_config_dword(mvi->pdev, PCR_PHY_CTL, &reg);
		अन्यथा
			pci_पढ़ो_config_dword(mvi->pdev, PCR_PHY_CTL2, &reg);

	पूर्ण अन्यथा
		reg = mr32(MVS_PHY_CTL);

	पंचांगp = reg;
	अगर (phy_id < MVS_SOC_PORTS)
		पंचांगp |= (1U << phy_id) << PCTL_LINK_OFFS;
	अन्यथा
		पंचांगp |= (1U << (phy_id - MVS_SOC_PORTS)) << PCTL_LINK_OFFS;

	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		अगर (phy_id < MVS_SOC_PORTS) अणु
			pci_ग_लिखो_config_dword(mvi->pdev, PCR_PHY_CTL, पंचांगp);
			mdelay(10);
			pci_ग_लिखो_config_dword(mvi->pdev, PCR_PHY_CTL, reg);
		पूर्ण अन्यथा अणु
			pci_ग_लिखो_config_dword(mvi->pdev, PCR_PHY_CTL2, पंचांगp);
			mdelay(10);
			pci_ग_लिखो_config_dword(mvi->pdev, PCR_PHY_CTL2, reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		mw32(MVS_PHY_CTL, पंचांगp);
		mdelay(10);
		mw32(MVS_PHY_CTL, reg);
	पूर्ण
पूर्ण

अटल व्योम mvs_64xx_phy_reset(काष्ठा mvs_info *mvi, u32 phy_id, पूर्णांक hard)
अणु
	u32 पंचांगp;
	पंचांगp = mvs_पढ़ो_port_irq_stat(mvi, phy_id);
	पंचांगp &= ~PHYEV_RDY_CH;
	mvs_ग_लिखो_port_irq_stat(mvi, phy_id, पंचांगp);
	पंचांगp = mvs_पढ़ो_phy_ctl(mvi, phy_id);
	अगर (hard == MVS_HARD_RESET)
		पंचांगp |= PHY_RST_HARD;
	अन्यथा अगर (hard == MVS_SOFT_RESET)
		पंचांगp |= PHY_RST;
	mvs_ग_लिखो_phy_ctl(mvi, phy_id, पंचांगp);
	अगर (hard) अणु
		करो अणु
			पंचांगp = mvs_पढ़ो_phy_ctl(mvi, phy_id);
		पूर्ण जबतक (पंचांगp & PHY_RST_HARD);
	पूर्ण
पूर्ण

अटल व्योम
mvs_64xx_clear_srs_irq(काष्ठा mvs_info *mvi, u8 reg_set, u8 clear_all)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;
	अगर (clear_all) अणु
		पंचांगp = mr32(MVS_INT_STAT_SRS_0);
		अगर (पंचांगp) अणु
			prपूर्णांकk(KERN_DEBUG "check SRS 0 %08X.\n", पंचांगp);
			mw32(MVS_INT_STAT_SRS_0, पंचांगp);
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = mr32(MVS_INT_STAT_SRS_0);
		अगर (पंचांगp &  (1 << (reg_set % 32))) अणु
			prपूर्णांकk(KERN_DEBUG "register set 0x%x was stopped.\n",
			       reg_set);
			mw32(MVS_INT_STAT_SRS_0, 1 << (reg_set % 32));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mvs_64xx_chip_reset(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;
	पूर्णांक i;

	/* make sure पूर्णांकerrupts are masked immediately (paranoia) */
	mw32(MVS_GBL_CTL, 0);
	पंचांगp = mr32(MVS_GBL_CTL);

	/* Reset Controller */
	अगर (!(पंचांगp & HBA_RST)) अणु
		अगर (mvi->flags & MVF_PHY_PWR_FIX) अणु
			pci_पढ़ो_config_dword(mvi->pdev, PCR_PHY_CTL, &पंचांगp);
			पंचांगp &= ~PCTL_PWR_OFF;
			पंचांगp |= PCTL_PHY_DSBL;
			pci_ग_लिखो_config_dword(mvi->pdev, PCR_PHY_CTL, पंचांगp);

			pci_पढ़ो_config_dword(mvi->pdev, PCR_PHY_CTL2, &पंचांगp);
			पंचांगp &= ~PCTL_PWR_OFF;
			पंचांगp |= PCTL_PHY_DSBL;
			pci_ग_लिखो_config_dword(mvi->pdev, PCR_PHY_CTL2, पंचांगp);
		पूर्ण
	पूर्ण

	/* make sure पूर्णांकerrupts are masked immediately (paranoia) */
	mw32(MVS_GBL_CTL, 0);
	पंचांगp = mr32(MVS_GBL_CTL);

	/* Reset Controller */
	अगर (!(पंचांगp & HBA_RST)) अणु
		/* global reset, incl. COMRESET/H_RESET_N (self-clearing) */
		mw32_f(MVS_GBL_CTL, HBA_RST);
	पूर्ण

	/* रुको क्रम reset to finish; समयout is just a guess */
	i = 1000;
	जबतक (i-- > 0) अणु
		msleep(10);

		अगर (!(mr32(MVS_GBL_CTL) & HBA_RST))
			अवरोध;
	पूर्ण
	अगर (mr32(MVS_GBL_CTL) & HBA_RST) अणु
		dev_prपूर्णांकk(KERN_ERR, mvi->dev, "HBA reset failed\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mvs_64xx_phy_disable(काष्ठा mvs_info *mvi, u32 phy_id)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;
	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		u32 offs;
		अगर (phy_id < 4)
			offs = PCR_PHY_CTL;
		अन्यथा अणु
			offs = PCR_PHY_CTL2;
			phy_id -= 4;
		पूर्ण
		pci_पढ़ो_config_dword(mvi->pdev, offs, &पंचांगp);
		पंचांगp |= 1U << (PCTL_PHY_DSBL_OFFS + phy_id);
		pci_ग_लिखो_config_dword(mvi->pdev, offs, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = mr32(MVS_PHY_CTL);
		पंचांगp |= 1U << (PCTL_PHY_DSBL_OFFS + phy_id);
		mw32(MVS_PHY_CTL, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम mvs_64xx_phy_enable(काष्ठा mvs_info *mvi, u32 phy_id)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;
	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		u32 offs;
		अगर (phy_id < 4)
			offs = PCR_PHY_CTL;
		अन्यथा अणु
			offs = PCR_PHY_CTL2;
			phy_id -= 4;
		पूर्ण
		pci_पढ़ो_config_dword(mvi->pdev, offs, &पंचांगp);
		पंचांगp &= ~(1U << (PCTL_PHY_DSBL_OFFS + phy_id));
		pci_ग_लिखो_config_dword(mvi->pdev, offs, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = mr32(MVS_PHY_CTL);
		पंचांगp &= ~(1U << (PCTL_PHY_DSBL_OFFS + phy_id));
		mw32(MVS_PHY_CTL, पंचांगp);
	पूर्ण
पूर्ण

अटल पूर्णांक mvs_64xx_init(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	पूर्णांक i;
	u32 पंचांगp, cctl;

	अगर (mvi->pdev && mvi->pdev->revision == 0)
		mvi->flags |= MVF_PHY_PWR_FIX;
	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		mvs_show_pcie_usage(mvi);
		पंचांगp = mvs_64xx_chip_reset(mvi);
		अगर (पंचांगp)
			वापस पंचांगp;
	पूर्ण अन्यथा अणु
		पंचांगp = mr32(MVS_PHY_CTL);
		पंचांगp &= ~PCTL_PWR_OFF;
		पंचांगp |= PCTL_PHY_DSBL;
		mw32(MVS_PHY_CTL, पंचांगp);
	पूर्ण

	/* Init Chip */
	/* make sure RST is set; HBA_RST /should/ have करोne that क्रम us */
	cctl = mr32(MVS_CTL) & 0xFFFF;
	अगर (cctl & CCTL_RST)
		cctl &= ~CCTL_RST;
	अन्यथा
		mw32_f(MVS_CTL, cctl | CCTL_RST);

	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		/* ग_लिखो to device control _AND_ device status रेजिस्टर */
		pci_पढ़ो_config_dword(mvi->pdev, PCR_DEV_CTRL, &पंचांगp);
		पंचांगp &= ~PRD_REQ_MASK;
		पंचांगp |= PRD_REQ_SIZE;
		pci_ग_लिखो_config_dword(mvi->pdev, PCR_DEV_CTRL, पंचांगp);

		pci_पढ़ो_config_dword(mvi->pdev, PCR_PHY_CTL, &पंचांगp);
		पंचांगp &= ~PCTL_PWR_OFF;
		पंचांगp &= ~PCTL_PHY_DSBL;
		pci_ग_लिखो_config_dword(mvi->pdev, PCR_PHY_CTL, पंचांगp);

		pci_पढ़ो_config_dword(mvi->pdev, PCR_PHY_CTL2, &पंचांगp);
		पंचांगp &= PCTL_PWR_OFF;
		पंचांगp &= ~PCTL_PHY_DSBL;
		pci_ग_लिखो_config_dword(mvi->pdev, PCR_PHY_CTL2, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = mr32(MVS_PHY_CTL);
		पंचांगp &= ~PCTL_PWR_OFF;
		पंचांगp |= PCTL_COM_ON;
		पंचांगp &= ~PCTL_PHY_DSBL;
		पंचांगp |= PCTL_LINK_RST;
		mw32(MVS_PHY_CTL, पंचांगp);
		msleep(100);
		पंचांगp &= ~PCTL_LINK_RST;
		mw32(MVS_PHY_CTL, पंचांगp);
		msleep(100);
	पूर्ण

	/* reset control */
	mw32(MVS_PCS, 0);		/* MVS_PCS */
	/* init phys */
	mvs_64xx_phy_hacks(mvi);

	पंचांगp = mvs_cr32(mvi, CMD_PHY_MODE_21);
	पंचांगp &= 0x0000ffff;
	पंचांगp |= 0x00fa0000;
	mvs_cw32(mvi, CMD_PHY_MODE_21, पंचांगp);

	/* enable स्वतः port detection */
	mw32(MVS_GBL_PORT_TYPE, MODE_AUTO_DET_EN);

	mw32(MVS_CMD_LIST_LO, mvi->slot_dma);
	mw32(MVS_CMD_LIST_HI, (mvi->slot_dma >> 16) >> 16);

	mw32(MVS_RX_FIS_LO, mvi->rx_fis_dma);
	mw32(MVS_RX_FIS_HI, (mvi->rx_fis_dma >> 16) >> 16);

	mw32(MVS_TX_CFG, MVS_CHIP_SLOT_SZ);
	mw32(MVS_TX_LO, mvi->tx_dma);
	mw32(MVS_TX_HI, (mvi->tx_dma >> 16) >> 16);

	mw32(MVS_RX_CFG, MVS_RX_RING_SZ);
	mw32(MVS_RX_LO, mvi->rx_dma);
	mw32(MVS_RX_HI, (mvi->rx_dma >> 16) >> 16);

	क्रम (i = 0; i < mvi->chip->n_phy; i++) अणु
		/* set phy local SAS address */
		/* should set little endian SAS address to 64xx chip */
		mvs_set_sas_addr(mvi, i, PHYR_ADDR_LO, PHYR_ADDR_HI,
				cpu_to_be64(mvi->phy[i].dev_sas_addr));

		mvs_64xx_enable_xmt(mvi, i);

		mvs_64xx_phy_reset(mvi, i, MVS_HARD_RESET);
		msleep(500);
		mvs_64xx_detect_porttype(mvi, i);
	पूर्ण
	अगर (mvi->flags & MVF_FLAG_SOC) अणु
		/* set select रेजिस्टरs */
		ग_लिखोl(0x0E008000, regs + 0x000);
		ग_लिखोl(0x59000008, regs + 0x004);
		ग_लिखोl(0x20, regs + 0x008);
		ग_लिखोl(0x20, regs + 0x00c);
		ग_लिखोl(0x20, regs + 0x010);
		ग_लिखोl(0x20, regs + 0x014);
		ग_लिखोl(0x20, regs + 0x018);
		ग_लिखोl(0x20, regs + 0x01c);
	पूर्ण
	क्रम (i = 0; i < mvi->chip->n_phy; i++) अणु
		/* clear phy पूर्णांक status */
		पंचांगp = mvs_पढ़ो_port_irq_stat(mvi, i);
		पंचांगp &= ~PHYEV_SIG_FIS;
		mvs_ग_लिखो_port_irq_stat(mvi, i, पंचांगp);

		/* set phy पूर्णांक mask */
		पंचांगp = PHYEV_RDY_CH | PHYEV_BROAD_CH | PHYEV_UNASSOC_FIS |
			PHYEV_ID_DONE | PHYEV_DCDR_ERR | PHYEV_CRC_ERR |
			PHYEV_DEC_ERR;
		mvs_ग_लिखो_port_irq_mask(mvi, i, पंचांगp);

		msleep(100);
		mvs_update_phyinfo(mvi, i, 1);
	पूर्ण

	/* little endian क्रम खोलो address and command table, etc. */
	cctl = mr32(MVS_CTL);
	cctl |= CCTL_ENDIAN_CMD;
	cctl |= CCTL_ENDIAN_DATA;
	cctl &= ~CCTL_ENDIAN_OPEN;
	cctl |= CCTL_ENDIAN_RSP;
	mw32_f(MVS_CTL, cctl);

	/* reset CMD queue */
	पंचांगp = mr32(MVS_PCS);
	पंचांगp |= PCS_CMD_RST;
	पंचांगp &= ~PCS_SELF_CLEAR;
	mw32(MVS_PCS, पंचांगp);
	/*
	 * the max count is 0x1ff, जबतक our max slot is 0x200,
	 * it will make count 0.
	 */
	पंचांगp = 0;
	अगर (MVS_CHIP_SLOT_SZ > 0x1ff)
		mw32(MVS_INT_COAL, 0x1ff | COAL_EN);
	अन्यथा
		mw32(MVS_INT_COAL, MVS_CHIP_SLOT_SZ | COAL_EN);

	पंचांगp = 0x10000 | पूर्णांकerrupt_coalescing;
	mw32(MVS_INT_COAL_TMOUT, पंचांगp);

	/* ladies and gentlemen, start your engines */
	mw32(MVS_TX_CFG, 0);
	mw32(MVS_TX_CFG, MVS_CHIP_SLOT_SZ | TX_EN);
	mw32(MVS_RX_CFG, MVS_RX_RING_SZ | RX_EN);
	/* enable CMD/CMPL_Q/RESP mode */
	mw32(MVS_PCS, PCS_SATA_RETRY | PCS_FIS_RX_EN |
		PCS_CMD_EN | PCS_CMD_STOP_ERR);

	/* enable completion queue पूर्णांकerrupt */
	पंचांगp = (CINT_PORT_MASK | CINT_DONE | CINT_MEM | CINT_SRS | CINT_CI_STOP |
		CINT_DMA_PCIE);

	mw32(MVS_INT_MASK, पंचांगp);

	/* Enable SRS पूर्णांकerrupt */
	mw32(MVS_INT_MASK_SRS_0, 0xFFFF);

	वापस 0;
पूर्ण

अटल पूर्णांक mvs_64xx_ioremap(काष्ठा mvs_info *mvi)
अणु
	अगर (!mvs_ioremap(mvi, 4, 2))
		वापस 0;
	वापस -1;
पूर्ण

अटल व्योम mvs_64xx_iounmap(काष्ठा mvs_info *mvi)
अणु
	mvs_iounmap(mvi->regs);
	mvs_iounmap(mvi->regs_ex);
पूर्ण

अटल व्योम mvs_64xx_पूर्णांकerrupt_enable(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;

	पंचांगp = mr32(MVS_GBL_CTL);
	mw32(MVS_GBL_CTL, पंचांगp | INT_EN);
पूर्ण

अटल व्योम mvs_64xx_पूर्णांकerrupt_disable(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;

	पंचांगp = mr32(MVS_GBL_CTL);
	mw32(MVS_GBL_CTL, पंचांगp & ~INT_EN);
पूर्ण

अटल u32 mvs_64xx_isr_status(काष्ठा mvs_info *mvi, पूर्णांक irq)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 stat;

	अगर (!(mvi->flags & MVF_FLAG_SOC)) अणु
		stat = mr32(MVS_GBL_INT_STAT);

		अगर (stat == 0 || stat == 0xffffffff)
			वापस 0;
	पूर्ण अन्यथा
		stat = 1;
	वापस stat;
पूर्ण

अटल irqवापस_t mvs_64xx_isr(काष्ठा mvs_info *mvi, पूर्णांक irq, u32 stat)
अणु
	व्योम __iomem *regs = mvi->regs;

	/* clear CMD_CMPLT ASAP */
	mw32_f(MVS_INT_STAT, CINT_DONE);

	spin_lock(&mvi->lock);
	mvs_पूर्णांक_full(mvi);
	spin_unlock(&mvi->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mvs_64xx_command_active(काष्ठा mvs_info *mvi, u32 slot_idx)
अणु
	u32 पंचांगp;
	mvs_cw32(mvi, 0x40 + (slot_idx >> 3), 1 << (slot_idx % 32));
	mvs_cw32(mvi, 0x00 + (slot_idx >> 3), 1 << (slot_idx % 32));
	करो अणु
		पंचांगp = mvs_cr32(mvi, 0x00 + (slot_idx >> 3));
	पूर्ण जबतक (पंचांगp & 1 << (slot_idx % 32));
	करो अणु
		पंचांगp = mvs_cr32(mvi, 0x40 + (slot_idx >> 3));
	पूर्ण जबतक (पंचांगp & 1 << (slot_idx % 32));
पूर्ण

अटल व्योम mvs_64xx_issue_stop(काष्ठा mvs_info *mvi, क्रमागत mvs_port_type type,
				u32 tfs)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp;

	अगर (type == PORT_TYPE_SATA) अणु
		पंचांगp = mr32(MVS_INT_STAT_SRS_0) | (1U << tfs);
		mw32(MVS_INT_STAT_SRS_0, पंचांगp);
	पूर्ण
	mw32(MVS_INT_STAT, CINT_CI_STOP);
	पंचांगp = mr32(MVS_PCS) | 0xFF00;
	mw32(MVS_PCS, पंचांगp);
पूर्ण

अटल व्योम mvs_64xx_मुक्त_reg_set(काष्ठा mvs_info *mvi, u8 *tfs)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp, offs;

	अगर (*tfs == MVS_ID_NOT_MAPPED)
		वापस;

	offs = 1U << ((*tfs & 0x0f) + PCS_EN_SATA_REG_SHIFT);
	अगर (*tfs < 16) अणु
		पंचांगp = mr32(MVS_PCS);
		mw32(MVS_PCS, पंचांगp & ~offs);
	पूर्ण अन्यथा अणु
		पंचांगp = mr32(MVS_CTL);
		mw32(MVS_CTL, पंचांगp & ~offs);
	पूर्ण

	पंचांगp = mr32(MVS_INT_STAT_SRS_0) & (1U << *tfs);
	अगर (पंचांगp)
		mw32(MVS_INT_STAT_SRS_0, पंचांगp);

	*tfs = MVS_ID_NOT_MAPPED;
	वापस;
पूर्ण

अटल u8 mvs_64xx_assign_reg_set(काष्ठा mvs_info *mvi, u8 *tfs)
अणु
	पूर्णांक i;
	u32 पंचांगp, offs;
	व्योम __iomem *regs = mvi->regs;

	अगर (*tfs != MVS_ID_NOT_MAPPED)
		वापस 0;

	पंचांगp = mr32(MVS_PCS);

	क्रम (i = 0; i < mvi->chip->srs_sz; i++) अणु
		अगर (i == 16)
			पंचांगp = mr32(MVS_CTL);
		offs = 1U << ((i & 0x0f) + PCS_EN_SATA_REG_SHIFT);
		अगर (!(पंचांगp & offs)) अणु
			*tfs = i;

			अगर (i < 16)
				mw32(MVS_PCS, पंचांगp | offs);
			अन्यथा
				mw32(MVS_CTL, पंचांगp | offs);
			पंचांगp = mr32(MVS_INT_STAT_SRS_0) & (1U << i);
			अगर (पंचांगp)
				mw32(MVS_INT_STAT_SRS_0, पंचांगp);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस MVS_ID_NOT_MAPPED;
पूर्ण

अटल व्योम mvs_64xx_make_prd(काष्ठा scatterlist *scatter, पूर्णांक nr, व्योम *prd)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;
	काष्ठा mvs_prd *buf_prd = prd;
	क्रम_each_sg(scatter, sg, nr, i) अणु
		buf_prd->addr = cpu_to_le64(sg_dma_address(sg));
		buf_prd->len = cpu_to_le32(sg_dma_len(sg));
		buf_prd++;
	पूर्ण
पूर्ण

अटल पूर्णांक mvs_64xx_oob_करोne(काष्ठा mvs_info *mvi, पूर्णांक i)
अणु
	u32 phy_st;
	mvs_ग_लिखो_port_cfg_addr(mvi, i,
			PHYR_PHY_STAT);
	phy_st = mvs_पढ़ो_port_cfg_data(mvi, i);
	अगर (phy_st & PHY_OOB_DTCTD)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम mvs_64xx_fix_phy_info(काष्ठा mvs_info *mvi, पूर्णांक i,
				काष्ठा sas_identअगरy_frame *id)

अणु
	काष्ठा mvs_phy *phy = &mvi->phy[i];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;

	sas_phy->linkrate =
		(phy->phy_status & PHY_NEG_SPP_PHYS_LINK_RATE_MASK) >>
			PHY_NEG_SPP_PHYS_LINK_RATE_MASK_OFFSET;

	phy->minimum_linkrate =
		(phy->phy_status &
			PHY_MIN_SPP_PHYS_LINK_RATE_MASK) >> 8;
	phy->maximum_linkrate =
		(phy->phy_status &
			PHY_MAX_SPP_PHYS_LINK_RATE_MASK) >> 12;

	mvs_ग_लिखो_port_cfg_addr(mvi, i, PHYR_IDENTIFY);
	phy->dev_info = mvs_पढ़ो_port_cfg_data(mvi, i);

	mvs_ग_लिखो_port_cfg_addr(mvi, i, PHYR_ATT_DEV_INFO);
	phy->att_dev_info = mvs_पढ़ो_port_cfg_data(mvi, i);

	mvs_ग_लिखो_port_cfg_addr(mvi, i, PHYR_ATT_ADDR_HI);
	phy->att_dev_sas_addr =
	     (u64) mvs_पढ़ो_port_cfg_data(mvi, i) << 32;
	mvs_ग_लिखो_port_cfg_addr(mvi, i, PHYR_ATT_ADDR_LO);
	phy->att_dev_sas_addr |= mvs_पढ़ो_port_cfg_data(mvi, i);
	phy->att_dev_sas_addr = SAS_ADDR(&phy->att_dev_sas_addr);
पूर्ण

अटल व्योम mvs_64xx_phy_work_around(काष्ठा mvs_info *mvi, पूर्णांक i)
अणु
	u32 पंचांगp;
	काष्ठा mvs_phy *phy = &mvi->phy[i];
	mvs_ग_लिखो_port_vsr_addr(mvi, i, VSR_PHY_MODE6);
	पंचांगp = mvs_पढ़ो_port_vsr_data(mvi, i);
	अगर (((phy->phy_status & PHY_NEG_SPP_PHYS_LINK_RATE_MASK) >>
	     PHY_NEG_SPP_PHYS_LINK_RATE_MASK_OFFSET) ==
		SAS_LINK_RATE_1_5_GBPS)
		पंचांगp &= ~PHY_MODE6_LATECLK;
	अन्यथा
		पंचांगp |= PHY_MODE6_LATECLK;
	mvs_ग_लिखो_port_vsr_data(mvi, i, पंचांगp);
पूर्ण

अटल व्योम mvs_64xx_phy_set_link_rate(काष्ठा mvs_info *mvi, u32 phy_id,
			काष्ठा sas_phy_linkrates *rates)
अणु
	u32 lrmin = 0, lrmax = 0;
	u32 पंचांगp;

	पंचांगp = mvs_पढ़ो_phy_ctl(mvi, phy_id);
	lrmin = (rates->minimum_linkrate << 8);
	lrmax = (rates->maximum_linkrate << 12);

	अगर (lrmin) अणु
		पंचांगp &= ~(0xf << 8);
		पंचांगp |= lrmin;
	पूर्ण
	अगर (lrmax) अणु
		पंचांगp &= ~(0xf << 12);
		पंचांगp |= lrmax;
	पूर्ण
	mvs_ग_लिखो_phy_ctl(mvi, phy_id, पंचांगp);
	mvs_64xx_phy_reset(mvi, phy_id, MVS_HARD_RESET);
पूर्ण

अटल व्योम mvs_64xx_clear_active_cmds(काष्ठा mvs_info *mvi)
अणु
	u32 पंचांगp;
	व्योम __iomem *regs = mvi->regs;
	पंचांगp = mr32(MVS_PCS);
	mw32(MVS_PCS, पंचांगp & 0xFFFF);
	mw32(MVS_PCS, पंचांगp);
	पंचांगp = mr32(MVS_CTL);
	mw32(MVS_CTL, पंचांगp & 0xFFFF);
	mw32(MVS_CTL, पंचांगp);
पूर्ण


अटल u32 mvs_64xx_spi_पढ़ो_data(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs_ex;
	वापस ior32(SPI_DATA_REG_64XX);
पूर्ण

अटल व्योम mvs_64xx_spi_ग_लिखो_data(काष्ठा mvs_info *mvi, u32 data)
अणु
	व्योम __iomem *regs = mvi->regs_ex;

	iow32(SPI_DATA_REG_64XX, data);
पूर्ण


अटल पूर्णांक mvs_64xx_spi_buildcmd(काष्ठा mvs_info *mvi,
			u32      *dwCmd,
			u8       cmd,
			u8       पढ़ो,
			u8       length,
			u32      addr
			)
अणु
	u32  dwTmp;

	dwTmp = ((u32)cmd << 24) | ((u32)length << 19);
	अगर (पढ़ो)
		dwTmp |= 1U<<23;

	अगर (addr != MV_MAX_U32) अणु
		dwTmp |= 1U<<22;
		dwTmp |= (addr & 0x0003FFFF);
	पूर्ण

	*dwCmd = dwTmp;
	वापस 0;
पूर्ण


अटल पूर्णांक mvs_64xx_spi_issuecmd(काष्ठा mvs_info *mvi, u32 cmd)
अणु
	व्योम __iomem *regs = mvi->regs_ex;
	पूर्णांक     retry;

	क्रम (retry = 0; retry < 1; retry++) अणु
		iow32(SPI_CTRL_REG_64XX, SPI_CTRL_VENDOR_ENABLE);
		iow32(SPI_CMD_REG_64XX, cmd);
		iow32(SPI_CTRL_REG_64XX,
			SPI_CTRL_VENDOR_ENABLE | SPI_CTRL_SPISTART);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvs_64xx_spi_रुकोdataपढ़ोy(काष्ठा mvs_info *mvi, u32 समयout)
अणु
	व्योम __iomem *regs = mvi->regs_ex;
	u32 i, dwTmp;

	क्रम (i = 0; i < समयout; i++) अणु
		dwTmp = ior32(SPI_CTRL_REG_64XX);
		अगर (!(dwTmp & SPI_CTRL_SPISTART))
			वापस 0;
		msleep(10);
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम mvs_64xx_fix_dma(काष्ठा mvs_info *mvi, u32 phy_mask,
				पूर्णांक buf_len, पूर्णांक from, व्योम *prd)
अणु
	पूर्णांक i;
	काष्ठा mvs_prd *buf_prd = prd;
	dma_addr_t buf_dma = mvi->bulk_buffer_dma;

	buf_prd	+= from;
	क्रम (i = 0; i < MAX_SG_ENTRY - from; i++) अणु
		buf_prd->addr = cpu_to_le64(buf_dma);
		buf_prd->len = cpu_to_le32(buf_len);
		++buf_prd;
	पूर्ण
पूर्ण

अटल व्योम mvs_64xx_tune_पूर्णांकerrupt(काष्ठा mvs_info *mvi, u32 समय)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp = 0;
	/*
	 * the max count is 0x1ff, जबतक our max slot is 0x200,
	 * it will make count 0.
	 */
	अगर (समय == 0) अणु
		mw32(MVS_INT_COAL, 0);
		mw32(MVS_INT_COAL_TMOUT, 0x10000);
	पूर्ण अन्यथा अणु
		अगर (MVS_CHIP_SLOT_SZ > 0x1ff)
			mw32(MVS_INT_COAL, 0x1ff|COAL_EN);
		अन्यथा
			mw32(MVS_INT_COAL, MVS_CHIP_SLOT_SZ|COAL_EN);

		पंचांगp = 0x10000 | समय;
		mw32(MVS_INT_COAL_TMOUT, पंचांगp);
	पूर्ण
पूर्ण

स्थिर काष्ठा mvs_dispatch mvs_64xx_dispatch = अणु
	"mv64xx",
	mvs_64xx_init,
	शून्य,
	mvs_64xx_ioremap,
	mvs_64xx_iounmap,
	mvs_64xx_isr,
	mvs_64xx_isr_status,
	mvs_64xx_पूर्णांकerrupt_enable,
	mvs_64xx_पूर्णांकerrupt_disable,
	mvs_पढ़ो_phy_ctl,
	mvs_ग_लिखो_phy_ctl,
	mvs_पढ़ो_port_cfg_data,
	mvs_ग_लिखो_port_cfg_data,
	mvs_ग_लिखो_port_cfg_addr,
	mvs_पढ़ो_port_vsr_data,
	mvs_ग_लिखो_port_vsr_data,
	mvs_ग_लिखो_port_vsr_addr,
	mvs_पढ़ो_port_irq_stat,
	mvs_ग_लिखो_port_irq_stat,
	mvs_पढ़ो_port_irq_mask,
	mvs_ग_लिखो_port_irq_mask,
	mvs_64xx_command_active,
	mvs_64xx_clear_srs_irq,
	mvs_64xx_issue_stop,
	mvs_start_delivery,
	mvs_rx_update,
	mvs_पूर्णांक_full,
	mvs_64xx_assign_reg_set,
	mvs_64xx_मुक्त_reg_set,
	mvs_get_prd_size,
	mvs_get_prd_count,
	mvs_64xx_make_prd,
	mvs_64xx_detect_porttype,
	mvs_64xx_oob_करोne,
	mvs_64xx_fix_phy_info,
	mvs_64xx_phy_work_around,
	mvs_64xx_phy_set_link_rate,
	mvs_hw_max_link_rate,
	mvs_64xx_phy_disable,
	mvs_64xx_phy_enable,
	mvs_64xx_phy_reset,
	mvs_64xx_stp_reset,
	mvs_64xx_clear_active_cmds,
	mvs_64xx_spi_पढ़ो_data,
	mvs_64xx_spi_ग_लिखो_data,
	mvs_64xx_spi_buildcmd,
	mvs_64xx_spi_issuecmd,
	mvs_64xx_spi_रुकोdataपढ़ोy,
	mvs_64xx_fix_dma,
	mvs_64xx_tune_पूर्णांकerrupt,
	शून्य,
पूर्ण;

