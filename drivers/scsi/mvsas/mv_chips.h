<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Marvell 88SE64xx/88SE94xx रेजिस्टर IO पूर्णांकerface
 *
 * Copyright 2007 Red Hat, Inc.
 * Copyright 2008 Marvell. <kewei@marvell.com>
 * Copyright 2009-2011 Marvell. <yuxiangl@marvell.com>
*/


#अगर_अघोषित _MV_CHIPS_H_
#घोषणा _MV_CHIPS_H_

#घोषणा mr32(reg)	पढ़ोl(regs + reg)
#घोषणा mw32(reg, val)	ग_लिखोl((val), regs + reg)
#घोषणा mw32_f(reg, val)	करो अणु			\
				mw32(reg, val);	\
				mr32(reg);	\
			पूर्ण जबतक (0)

#घोषणा iow32(reg, val) 	outl(val, (अचिन्हित दीर्घ)(regs + reg))
#घोषणा ior32(reg) 		inl((अचिन्हित दीर्घ)(regs + reg))
#घोषणा iow16(reg, val) 	outw((अचिन्हित दीर्घ)(val, regs + reg))
#घोषणा ior16(reg) 		inw((अचिन्हित दीर्घ)(regs + reg))
#घोषणा iow8(reg, val) 		outb((अचिन्हित दीर्घ)(val, regs + reg))
#घोषणा ior8(reg) 		inb((अचिन्हित दीर्घ)(regs + reg))

अटल अंतरभूत u32 mvs_cr32(काष्ठा mvs_info *mvi, u32 addr)
अणु
	व्योम __iomem *regs = mvi->regs;
	mw32(MVS_CMD_ADDR, addr);
	वापस mr32(MVS_CMD_DATA);
पूर्ण

अटल अंतरभूत व्योम mvs_cw32(काष्ठा mvs_info *mvi, u32 addr, u32 val)
अणु
	व्योम __iomem *regs = mvi->regs;
	mw32(MVS_CMD_ADDR, addr);
	mw32(MVS_CMD_DATA, val);
पूर्ण

अटल अंतरभूत u32 mvs_पढ़ो_phy_ctl(काष्ठा mvs_info *mvi, u32 port)
अणु
	व्योम __iomem *regs = mvi->regs;
	वापस (port < 4) ? mr32(MVS_P0_SER_CTLSTAT + port * 4) :
		mr32(MVS_P4_SER_CTLSTAT + (port - 4) * 4);
पूर्ण

अटल अंतरभूत व्योम mvs_ग_लिखो_phy_ctl(काष्ठा mvs_info *mvi, u32 port, u32 val)
अणु
	व्योम __iomem *regs = mvi->regs;
	अगर (port < 4)
		mw32(MVS_P0_SER_CTLSTAT + port * 4, val);
	अन्यथा
		mw32(MVS_P4_SER_CTLSTAT + (port - 4) * 4, val);
पूर्ण

अटल अंतरभूत u32 mvs_पढ़ो_port(काष्ठा mvs_info *mvi, u32 off,
				u32 off2, u32 port)
अणु
	व्योम __iomem *regs = mvi->regs + off;
	व्योम __iomem *regs2 = mvi->regs + off2;
	वापस (port < 4) ? पढ़ोl(regs + port * 8) :
		पढ़ोl(regs2 + (port - 4) * 8);
पूर्ण

अटल अंतरभूत व्योम mvs_ग_लिखो_port(काष्ठा mvs_info *mvi, u32 off, u32 off2,
				u32 port, u32 val)
अणु
	व्योम __iomem *regs = mvi->regs + off;
	व्योम __iomem *regs2 = mvi->regs + off2;
	अगर (port < 4)
		ग_लिखोl(val, regs + port * 8);
	अन्यथा
		ग_लिखोl(val, regs2 + (port - 4) * 8);
पूर्ण

अटल अंतरभूत u32 mvs_पढ़ो_port_cfg_data(काष्ठा mvs_info *mvi, u32 port)
अणु
	वापस mvs_पढ़ो_port(mvi, MVS_P0_CFG_DATA,
			MVS_P4_CFG_DATA, port);
पूर्ण

अटल अंतरभूत व्योम mvs_ग_लिखो_port_cfg_data(काष्ठा mvs_info *mvi,
						u32 port, u32 val)
अणु
	mvs_ग_लिखो_port(mvi, MVS_P0_CFG_DATA,
			MVS_P4_CFG_DATA, port, val);
पूर्ण

अटल अंतरभूत व्योम mvs_ग_लिखो_port_cfg_addr(काष्ठा mvs_info *mvi,
						u32 port, u32 addr)
अणु
	mvs_ग_लिखो_port(mvi, MVS_P0_CFG_ADDR,
			MVS_P4_CFG_ADDR, port, addr);
	mdelay(10);
पूर्ण

अटल अंतरभूत u32 mvs_पढ़ो_port_vsr_data(काष्ठा mvs_info *mvi, u32 port)
अणु
	वापस mvs_पढ़ो_port(mvi, MVS_P0_VSR_DATA,
			MVS_P4_VSR_DATA, port);
पूर्ण

अटल अंतरभूत व्योम mvs_ग_लिखो_port_vsr_data(काष्ठा mvs_info *mvi,
						u32 port, u32 val)
अणु
	mvs_ग_लिखो_port(mvi, MVS_P0_VSR_DATA,
			MVS_P4_VSR_DATA, port, val);
पूर्ण

अटल अंतरभूत व्योम mvs_ग_लिखो_port_vsr_addr(काष्ठा mvs_info *mvi,
						u32 port, u32 addr)
अणु
	mvs_ग_लिखो_port(mvi, MVS_P0_VSR_ADDR,
			MVS_P4_VSR_ADDR, port, addr);
	mdelay(10);
पूर्ण

अटल अंतरभूत u32 mvs_पढ़ो_port_irq_stat(काष्ठा mvs_info *mvi, u32 port)
अणु
	वापस mvs_पढ़ो_port(mvi, MVS_P0_INT_STAT,
			MVS_P4_INT_STAT, port);
पूर्ण

अटल अंतरभूत व्योम mvs_ग_लिखो_port_irq_stat(काष्ठा mvs_info *mvi,
						u32 port, u32 val)
अणु
	mvs_ग_लिखो_port(mvi, MVS_P0_INT_STAT,
			MVS_P4_INT_STAT, port, val);
पूर्ण

अटल अंतरभूत u32 mvs_पढ़ो_port_irq_mask(काष्ठा mvs_info *mvi, u32 port)
अणु
	वापस mvs_पढ़ो_port(mvi, MVS_P0_INT_MASK,
			MVS_P4_INT_MASK, port);

पूर्ण

अटल अंतरभूत व्योम mvs_ग_लिखो_port_irq_mask(काष्ठा mvs_info *mvi,
						u32 port, u32 val)
अणु
	mvs_ग_लिखो_port(mvi, MVS_P0_INT_MASK,
			MVS_P4_INT_MASK, port, val);
पूर्ण

अटल अंतरभूत व्योम mvs_phy_hacks(काष्ठा mvs_info *mvi)
अणु
	u32 पंचांगp;

	पंचांगp = mvs_cr32(mvi, CMD_PHY_TIMER);
	पंचांगp &= ~(1 << 9);
	पंचांगp |= (1 << 10);
	mvs_cw32(mvi, CMD_PHY_TIMER, पंचांगp);

	/* enable retry 127 बार */
	mvs_cw32(mvi, CMD_SAS_CTL1, 0x7f7f);

	/* extend खोलो frame समयout to max */
	पंचांगp = mvs_cr32(mvi, CMD_SAS_CTL0);
	पंचांगp &= ~0xffff;
	पंचांगp |= 0x3fff;
	mvs_cw32(mvi, CMD_SAS_CTL0, पंचांगp);

	mvs_cw32(mvi, CMD_WD_TIMER, 0x7a0000);

	/* not to halt क्रम dअगरferent port op during wideport link change */
	mvs_cw32(mvi, CMD_APP_ERR_CONFIG, 0xffefbf7d);
पूर्ण

अटल अंतरभूत व्योम mvs_पूर्णांक_sata(काष्ठा mvs_info *mvi)
अणु
	u32 पंचांगp;
	व्योम __iomem *regs = mvi->regs;
	पंचांगp = mr32(MVS_INT_STAT_SRS_0);
	अगर (पंचांगp)
		mw32(MVS_INT_STAT_SRS_0, पंचांगp);
	MVS_CHIP_DISP->clear_active_cmds(mvi);
पूर्ण

अटल अंतरभूत व्योम mvs_पूर्णांक_full(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	u32 पंचांगp, stat;
	पूर्णांक i;

	stat = mr32(MVS_INT_STAT);
	mvs_पूर्णांक_rx(mvi, false);

	क्रम (i = 0; i < mvi->chip->n_phy; i++) अणु
		पंचांगp = (stat >> i) & (CINT_PORT | CINT_PORT_STOPPED);
		अगर (पंचांगp)
			mvs_पूर्णांक_port(mvi, i, पंचांगp);
	पूर्ण

	अगर (stat & CINT_NON_SPEC_NCQ_ERROR)
		MVS_CHIP_DISP->non_spec_ncq_error(mvi);

	अगर (stat & CINT_SRS)
		mvs_पूर्णांक_sata(mvi);

	mw32(MVS_INT_STAT, stat);
पूर्ण

अटल अंतरभूत व्योम mvs_start_delivery(काष्ठा mvs_info *mvi, u32 tx)
अणु
	व्योम __iomem *regs = mvi->regs;
	mw32(MVS_TX_PROD_IDX, tx);
पूर्ण

अटल अंतरभूत u32 mvs_rx_update(काष्ठा mvs_info *mvi)
अणु
	व्योम __iomem *regs = mvi->regs;
	वापस mr32(MVS_RX_CONS_IDX);
पूर्ण

अटल अंतरभूत u32 mvs_get_prd_size(व्योम)
अणु
	वापस माप(काष्ठा mvs_prd);
पूर्ण

अटल अंतरभूत u32 mvs_get_prd_count(व्योम)
अणु
	वापस MAX_SG_ENTRY;
पूर्ण

अटल अंतरभूत व्योम mvs_show_pcie_usage(काष्ठा mvs_info *mvi)
अणु
	u16 link_stat, link_spd;
	स्थिर अक्षर *spd[] = अणु
		"UnKnown",
		"2.5",
		"5.0",
	पूर्ण;
	अगर (mvi->flags & MVF_FLAG_SOC || mvi->id > 0)
		वापस;

	pci_पढ़ो_config_word(mvi->pdev, PCR_LINK_STAT, &link_stat);
	link_spd = (link_stat & PLS_LINK_SPD) >> PLS_LINK_SPD_OFFS;
	अगर (link_spd >= 3)
		link_spd = 0;
	dev_prपूर्णांकk(KERN_INFO, mvi->dev,
		"mvsas: PCI-E x%u, Bandwidth Usage: %s Gbps\n",
	       (link_stat & PLS_NEG_LINK_WD) >> PLS_NEG_LINK_WD_OFFS,
	       spd[link_spd]);
पूर्ण

अटल अंतरभूत u32 mvs_hw_max_link_rate(व्योम)
अणु
	वापस MAX_LINK_RATE;
पूर्ण

#पूर्ण_अगर  /* _MV_CHIPS_H_ */

