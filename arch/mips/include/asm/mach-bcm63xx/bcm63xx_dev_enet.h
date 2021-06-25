<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_DEV_ENET_H_
#घोषणा BCM63XX_DEV_ENET_H_

#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>

#समावेश <bcm63xx_regs.h>

/*
 * on board ethernet platक्रमm data
 */
काष्ठा bcm63xx_enet_platक्रमm_data अणु
	अक्षर mac_addr[ETH_ALEN];

	पूर्णांक has_phy;

	/* अगर has_phy, then set use_पूर्णांकernal_phy */
	पूर्णांक use_पूर्णांकernal_phy;

	/* or fill phy info to use an बाह्यal one */
	पूर्णांक phy_id;
	पूर्णांक has_phy_पूर्णांकerrupt;
	पूर्णांक phy_पूर्णांकerrupt;

	/* अगर has_phy, use स्वतःnegotiated छोड़ो parameters or क्रमce
	 * them */
	पूर्णांक छोड़ो_स्वतः;
	पूर्णांक छोड़ो_rx;
	पूर्णांक छोड़ो_tx;

	/* अगर !has_phy, set desired क्रमced speed/duplex */
	पूर्णांक क्रमce_speed_100;
	पूर्णांक क्रमce_duplex_full;

	/* अगर !has_phy, set callback to perक्रमm mii device
	 * init/हटाओ */
	पूर्णांक (*mii_config)(काष्ठा net_device *dev, पूर्णांक probe,
			  पूर्णांक (*mii_पढ़ो)(काष्ठा net_device *dev,
					  पूर्णांक phy_id, पूर्णांक reg),
			  व्योम (*mii_ग_लिखो)(काष्ठा net_device *dev,
					    पूर्णांक phy_id, पूर्णांक reg, पूर्णांक val));

	/* DMA channel enable mask */
	u32 dma_chan_en_mask;

	/* DMA channel पूर्णांकerrupt mask */
	u32 dma_chan_पूर्णांक_mask;

	/* DMA engine has पूर्णांकernal SRAM */
	bool dma_has_sram;

	/* DMA channel रेजिस्टर width */
	अचिन्हित पूर्णांक dma_chan_width;

	/* DMA descriptor shअगरt */
	अचिन्हित पूर्णांक dma_desc_shअगरt;

	/* dma channel ids */
	पूर्णांक rx_chan;
	पूर्णांक tx_chan;
पूर्ण;

/*
 * on board ethernet चयन platक्रमm data
 */
#घोषणा ENETSW_MAX_PORT	8
#घोषणा ENETSW_PORTS_6328 5 /* 4 FE PHY + 1 RGMII */
#घोषणा ENETSW_PORTS_6368 6 /* 4 FE PHY + 2 RGMII */

#घोषणा ENETSW_RGMII_PORT0	4

काष्ठा bcm63xx_enetsw_port अणु
	पूर्णांक		used;
	पूर्णांक		phy_id;

	पूर्णांक		bypass_link;
	पूर्णांक		क्रमce_speed;
	पूर्णांक		क्रमce_duplex_full;

	स्थिर अक्षर	*name;
पूर्ण;

काष्ठा bcm63xx_enetsw_platक्रमm_data अणु
	अक्षर mac_addr[ETH_ALEN];
	पूर्णांक num_ports;
	काष्ठा bcm63xx_enetsw_port used_ports[ENETSW_MAX_PORT];

	/* DMA channel enable mask */
	u32 dma_chan_en_mask;

	/* DMA channel पूर्णांकerrupt mask */
	u32 dma_chan_पूर्णांक_mask;

	/* DMA channel रेजिस्टर width */
	अचिन्हित पूर्णांक dma_chan_width;

	/* DMA engine has पूर्णांकernal SRAM */
	bool dma_has_sram;
पूर्ण;

पूर्णांक __init bcm63xx_enet_रेजिस्टर(पूर्णांक unit,
				 स्थिर काष्ठा bcm63xx_enet_platक्रमm_data *pd);

पूर्णांक bcm63xx_enetsw_रेजिस्टर(स्थिर काष्ठा bcm63xx_enetsw_platक्रमm_data *pd);

क्रमागत bcm63xx_regs_enetdmac अणु
	ENETDMAC_CHANCFG,
	ENETDMAC_IR,
	ENETDMAC_IRMASK,
	ENETDMAC_MAXBURST,
	ENETDMAC_BUFALLOC,
	ENETDMAC_RSTART,
	ENETDMAC_FC,
	ENETDMAC_LEN,
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ bcm63xx_enetdmacreg(क्रमागत bcm63xx_regs_enetdmac reg)
अणु
	बाह्य स्थिर अचिन्हित दीर्घ *bcm63xx_regs_enetdmac;

	वापस bcm63xx_regs_enetdmac[reg];
पूर्ण


#पूर्ण_अगर /* ! BCM63XX_DEV_ENET_H_ */
