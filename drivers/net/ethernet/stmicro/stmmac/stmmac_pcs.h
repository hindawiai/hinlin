<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * sपंचांगmac_pcs.h: Physical Coding Sublayer Header File
 *
 * Copyright (C) 2016 STMicroelectronics (R&D) Limited
 * Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
 */

#अगर_अघोषित __STMMAC_PCS_H__
#घोषणा __STMMAC_PCS_H__

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश "common.h"

/* PCS रेजिस्टरs (AN/TBI/SGMII/RGMII) offsets */
#घोषणा GMAC_AN_CTRL(x)		(x)		/* AN control */
#घोषणा GMAC_AN_STATUS(x)	(x + 0x4)	/* AN status */
#घोषणा GMAC_ANE_ADV(x)		(x + 0x8)	/* ANE Advertisement */
#घोषणा GMAC_ANE_LPA(x)		(x + 0xc)	/* ANE link partener ability */
#घोषणा GMAC_ANE_EXP(x)		(x + 0x10)	/* ANE expansion */
#घोषणा GMAC_TBI(x)		(x + 0x14)	/* TBI extend status */

/* AN Configuration defines */
#घोषणा GMAC_AN_CTRL_RAN	BIT(9)	/* Restart Auto-Negotiation */
#घोषणा GMAC_AN_CTRL_ANE	BIT(12)	/* Auto-Negotiation Enable */
#घोषणा GMAC_AN_CTRL_ELE	BIT(14)	/* External Loopback Enable */
#घोषणा GMAC_AN_CTRL_ECD	BIT(16)	/* Enable Comma Detect */
#घोषणा GMAC_AN_CTRL_LR		BIT(17)	/* Lock to Reference */
#घोषणा GMAC_AN_CTRL_SGMRAL	BIT(18)	/* SGMII RAL Control */

/* AN Status defines */
#घोषणा GMAC_AN_STATUS_LS	BIT(2)	/* Link Status 0:करोwn 1:up */
#घोषणा GMAC_AN_STATUS_ANA	BIT(3)	/* Auto-Negotiation Ability */
#घोषणा GMAC_AN_STATUS_ANC	BIT(5)	/* Auto-Negotiation Complete */
#घोषणा GMAC_AN_STATUS_ES	BIT(8)	/* Extended Status */

/* ADV and LPA defines */
#घोषणा GMAC_ANE_FD		BIT(5)
#घोषणा GMAC_ANE_HD		BIT(6)
#घोषणा GMAC_ANE_PSE		GENMASK(8, 7)
#घोषणा GMAC_ANE_PSE_SHIFT	7
#घोषणा GMAC_ANE_RFE		GENMASK(13, 12)
#घोषणा GMAC_ANE_RFE_SHIFT	12
#घोषणा GMAC_ANE_ACK		BIT(14)

/**
 * dwmac_pcs_isr - TBI, RTBI, or SGMII PHY ISR
 * @ioaddr: IO रेजिस्टरs poपूर्णांकer
 * @reg: Base address of the AN Control Register.
 * @पूर्णांकr_status: GMAC core पूर्णांकerrupt status
 * @x: poपूर्णांकer to log these events as stats
 * Description: it is the ISR क्रम PCS events: Auto-Negotiation Completed and
 * Link status.
 */
अटल अंतरभूत व्योम dwmac_pcs_isr(व्योम __iomem *ioaddr, u32 reg,
				 अचिन्हित पूर्णांक पूर्णांकr_status,
				 काष्ठा sपंचांगmac_extra_stats *x)
अणु
	u32 val = पढ़ोl(ioaddr + GMAC_AN_STATUS(reg));

	अगर (पूर्णांकr_status & PCS_ANE_IRQ) अणु
		x->irq_pcs_ane_n++;
		अगर (val & GMAC_AN_STATUS_ANC)
			pr_info("stmmac_pcs: ANE process completed\n");
	पूर्ण

	अगर (पूर्णांकr_status & PCS_LINK_IRQ) अणु
		x->irq_pcs_link_n++;
		अगर (val & GMAC_AN_STATUS_LS)
			pr_info("stmmac_pcs: Link Up\n");
		अन्यथा
			pr_info("stmmac_pcs: Link Down\n");
	पूर्ण
पूर्ण

/**
 * dwmac_rane - To restart ANE
 * @ioaddr: IO रेजिस्टरs poपूर्णांकer
 * @reg: Base address of the AN Control Register.
 * @restart: to restart ANE
 * Description: this is to just restart the Auto-Negotiation.
 */
अटल अंतरभूत व्योम dwmac_rane(व्योम __iomem *ioaddr, u32 reg, bool restart)
अणु
	u32 value = पढ़ोl(ioaddr + GMAC_AN_CTRL(reg));

	अगर (restart)
		value |= GMAC_AN_CTRL_RAN;

	ग_लिखोl(value, ioaddr + GMAC_AN_CTRL(reg));
पूर्ण

/**
 * dwmac_ctrl_ane - To program the AN Control Register.
 * @ioaddr: IO रेजिस्टरs poपूर्णांकer
 * @reg: Base address of the AN Control Register.
 * @ane: to enable the स्वतः-negotiation
 * @srgmi_ral: to manage MAC-2-MAC SGMII connections.
 * @loopback: to cause the PHY to loopback tx data पूर्णांकo rx path.
 * Description: this is the मुख्य function to configure the AN control रेजिस्टर
 * and init the ANE, select loopback (usually क्रम debugging purpose) and
 * configure SGMII RAL.
 */
अटल अंतरभूत व्योम dwmac_ctrl_ane(व्योम __iomem *ioaddr, u32 reg, bool ane,
				  bool srgmi_ral, bool loopback)
अणु
	u32 value = पढ़ोl(ioaddr + GMAC_AN_CTRL(reg));

	/* Enable and restart the Auto-Negotiation */
	अगर (ane)
		value |= GMAC_AN_CTRL_ANE | GMAC_AN_CTRL_RAN;

	/* In हाल of MAC-2-MAC connection, block is configured to operate
	 * according to MAC conf रेजिस्टर.
	 */
	अगर (srgmi_ral)
		value |= GMAC_AN_CTRL_SGMRAL;

	अगर (loopback)
		value |= GMAC_AN_CTRL_ELE;

	ग_लिखोl(value, ioaddr + GMAC_AN_CTRL(reg));
पूर्ण

/**
 * dwmac_get_adv_lp - Get ADV and LP cap
 * @ioaddr: IO रेजिस्टरs poपूर्णांकer
 * @reg: Base address of the AN Control Register.
 * @adv_lp: काष्ठाure to store the adv,lp status
 * Description: this is to expose the ANE advertisement and Link partner ability
 * status to ethtool support.
 */
अटल अंतरभूत व्योम dwmac_get_adv_lp(व्योम __iomem *ioaddr, u32 reg,
				    काष्ठा rgmii_adv *adv_lp)
अणु
	u32 value = पढ़ोl(ioaddr + GMAC_ANE_ADV(reg));

	अगर (value & GMAC_ANE_FD)
		adv_lp->duplex = DUPLEX_FULL;
	अगर (value & GMAC_ANE_HD)
		adv_lp->duplex |= DUPLEX_HALF;

	adv_lp->छोड़ो = (value & GMAC_ANE_PSE) >> GMAC_ANE_PSE_SHIFT;

	value = पढ़ोl(ioaddr + GMAC_ANE_LPA(reg));

	अगर (value & GMAC_ANE_FD)
		adv_lp->lp_duplex = DUPLEX_FULL;
	अगर (value & GMAC_ANE_HD)
		adv_lp->lp_duplex = DUPLEX_HALF;

	adv_lp->lp_छोड़ो = (value & GMAC_ANE_PSE) >> GMAC_ANE_PSE_SHIFT;
पूर्ण
#पूर्ण_अगर /* __STMMAC_PCS_H__ */
