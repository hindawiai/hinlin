<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __AU1X00_ETH_DATA_H
#घोषणा __AU1X00_ETH_DATA_H

/* Platक्रमm specअगरic PHY configuration passed to the MAC driver */
काष्ठा au1000_eth_platक्रमm_data अणु
	पूर्णांक phy_अटल_config;
	पूर्णांक phy_search_highest_addr;
	पूर्णांक phy1_search_mac0;
	पूर्णांक phy_addr;
	पूर्णांक phy_busid;
	पूर्णांक phy_irq;
	अक्षर mac[6];
पूर्ण;

व्योम __init au1xxx_override_eth_cfg(अचिन्हित port,
			काष्ठा au1000_eth_platक्रमm_data *eth_data);

#पूर्ण_अगर /* __AU1X00_ETH_DATA_H */
