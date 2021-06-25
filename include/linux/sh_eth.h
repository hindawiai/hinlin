<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_ETH_H__
#घोषणा __ASM_SH_ETH_H__

#समावेश <linux/phy.h>
#समावेश <linux/अगर_ether.h>

काष्ठा sh_eth_plat_data अणु
	पूर्णांक phy;
	पूर्णांक phy_irq;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	व्योम (*set_mdio_gate)(व्योम *addr);

	अचिन्हित अक्षर mac_addr[ETH_ALEN];
	अचिन्हित no_ether_link:1;
	अचिन्हित ether_link_active_low:1;
पूर्ण;

#पूर्ण_अगर
