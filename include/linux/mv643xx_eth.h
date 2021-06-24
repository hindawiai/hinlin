<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MV-643XX ethernet platक्रमm device data definition file.
 */

#अगर_अघोषित __LINUX_MV643XX_ETH_H
#घोषणा __LINUX_MV643XX_ETH_H

#समावेश <linux/mbus.h>
#समावेश <linux/अगर_ether.h>

#घोषणा MV643XX_ETH_SHARED_NAME		"mv643xx_eth"
#घोषणा MV643XX_ETH_NAME		"mv643xx_eth_port"
#घोषणा MV643XX_ETH_SHARED_REGS		0x2000
#घोषणा MV643XX_ETH_SHARED_REGS_SIZE	0x2000
#घोषणा MV643XX_ETH_BAR_4		0x2220
#घोषणा MV643XX_ETH_SIZE_REG_4		0x2224
#घोषणा MV643XX_ETH_BASE_ADDR_ENABLE_REG	0x2290

#घोषणा MV643XX_TX_CSUM_DEFAULT_LIMIT	0

काष्ठा mv643xx_eth_shared_platक्रमm_data अणु
	काष्ठा mbus_dram_target_info	*dram;
	/*
	 * Max packet size क्रम Tx IP/Layer 4 checksum, when set to 0, शेष
	 * limit of 9KiB will be used.
	 */
	पूर्णांक			tx_csum_limit;
पूर्ण;

#घोषणा MV643XX_ETH_PHY_ADDR_DEFAULT	0
#घोषणा MV643XX_ETH_PHY_ADDR(x)		(0x80 | (x))
#घोषणा MV643XX_ETH_PHY_NONE		0xff

काष्ठा device_node;
काष्ठा mv643xx_eth_platक्रमm_data अणु
	/*
	 * Poपूर्णांकer back to our parent instance, and our port number.
	 */
	काष्ठा platक्रमm_device	*shared;
	पूर्णांक			port_number;

	/*
	 * Whether a PHY is present, and अगर yes, at which address.
	 */
	पूर्णांक			phy_addr;
	काष्ठा device_node	*phy_node;

	/*
	 * Use this MAC address अगर it is valid, overriding the
	 * address that is alपढ़ोy in the hardware.
	 */
	u8			mac_addr[ETH_ALEN];

	/*
	 * If speed is 0, स्वतःnegotiation is enabled.
	 *   Valid values क्रम speed: 0, SPEED_10, SPEED_100, SPEED_1000.
	 *   Valid values क्रम duplex: DUPLEX_HALF, DUPLEX_FULL.
	 */
	पूर्णांक			speed;
	पूर्णांक			duplex;

	/*
	 * How many RX/TX queues to use.
	 */
	पूर्णांक			rx_queue_count;
	पूर्णांक			tx_queue_count;

	/*
	 * Override शेष RX/TX queue sizes अगर nonzero.
	 */
	पूर्णांक			rx_queue_size;
	पूर्णांक			tx_queue_size;

	/*
	 * Use on-chip SRAM क्रम RX/TX descriptors अगर size is nonzero
	 * and sufficient to contain all descriptors क्रम the requested
	 * ring sizes.
	 */
	अचिन्हित दीर्घ		rx_sram_addr;
	पूर्णांक			rx_sram_size;
	अचिन्हित दीर्घ		tx_sram_addr;
	पूर्णांक			tx_sram_size;
पूर्ण;


#पूर्ण_अगर
