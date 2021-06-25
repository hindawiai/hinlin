<शैली गुरु>
/*
 * TI DaVinci EMAC platक्रमm support
 *
 * Author: Kevin Hilman, Deep Root Systems, LLC
 *
 * 2007 (c) Deep Root Systems, LLC. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित _LINUX_DAVINCI_EMAC_H
#घोषणा _LINUX_DAVINCI_EMAC_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/nvmem-consumer.h>

काष्ठा mdio_platक्रमm_data अणु
	अचिन्हित दीर्घ		bus_freq;
पूर्ण;

काष्ठा emac_platक्रमm_data अणु
	अक्षर mac_addr[ETH_ALEN];
	u32 ctrl_reg_offset;
	u32 ctrl_mod_reg_offset;
	u32 ctrl_ram_offset;
	u32 hw_ram_addr;
	u32 ctrl_ram_size;

	/*
	 * phy_id can be one of the following:
	 *   - शून्य		: use the first phy on the bus,
	 *   - ""		: क्रमce to 100/full, no mdio control
	 *   - "<bus>:<addr>"	: use the specअगरied bus and phy
	 */
	स्थिर अक्षर *phy_id;

	u8 rmii_en;
	u8 version;
	bool no_bd_ram;
	व्योम (*पूर्णांकerrupt_enable) (व्योम);
	व्योम (*पूर्णांकerrupt_disable) (व्योम);
पूर्ण;

क्रमागत अणु
	EMAC_VERSION_1,	/* DM644x */
	EMAC_VERSION_2,	/* DM646x */
पूर्ण;

#पूर्ण_अगर
