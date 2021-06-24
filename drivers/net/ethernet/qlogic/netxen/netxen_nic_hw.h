<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2003 - 2009 NetXen, Inc.
 * Copyright (C) 2009 - QLogic Corporation.
 * All rights reserved.
 */

#अगर_अघोषित __NETXEN_NIC_HW_H_
#घोषणा __NETXEN_NIC_HW_H_

/* Hardware memory size of 128 meg */
#घोषणा NETXEN_MEMADDR_MAX (128 * 1024 * 1024)

काष्ठा netxen_adapter;

#घोषणा NETXEN_PCI_MAPSIZE_BYTES  (NETXEN_PCI_MAPSIZE << 20)

व्योम netxen_nic_set_link_parameters(काष्ठा netxen_adapter *adapter);

/* Nibble or Byte mode क्रम phy पूर्णांकerface (GbE mode only) */

#घोषणा _netxen_crb_get_bit(var, bit)  ((var >> bit) & 0x1)

/*
 * NIU GB MAC Config Register 0 (applies to GB0, GB1, GB2, GB3)
 *
 *	Bit 0 : enable_tx => 1:enable frame xmit, 0:disable
 *	Bit 1 : tx_synced => R/O: xmit enable synched to xmit stream
 *	Bit 2 : enable_rx => 1:enable frame recv, 0:disable
 *	Bit 3 : rx_synced => R/O: recv enable synched to recv stream
 *	Bit 4 : tx_flowctl => 1:enable छोड़ो frame generation, 0:disable
 *	Bit 5 : rx_flowctl => 1:act on recv'd छोड़ो frames, 0:ignore
 *	Bit 8 : loopback => 1:loop MAC xmits to MAC recvs, 0:normal
 *	Bit 16: tx_reset_pb => 1:reset frame xmit protocol blk, 0:no-op
 *	Bit 17: rx_reset_pb => 1:reset frame recv protocol blk, 0:no-op
 *	Bit 18: tx_reset_mac => 1:reset data/ctl multiplexer blk, 0:no-op
 *	Bit 19: rx_reset_mac => 1:reset ctl frames & समयrs blk, 0:no-op
 *	Bit 31: soft_reset => 1:reset the MAC and the SERDES, 0:no-op
 */

#घोषणा netxen_gb_tx_flowctl(config_word)	\
	((config_word) |= 1 << 4)
#घोषणा netxen_gb_rx_flowctl(config_word)	\
	((config_word) |= 1 << 5)
#घोषणा netxen_gb_tx_reset_pb(config_word)	\
	((config_word) |= 1 << 16)
#घोषणा netxen_gb_rx_reset_pb(config_word)	\
	((config_word) |= 1 << 17)
#घोषणा netxen_gb_tx_reset_mac(config_word)	\
	((config_word) |= 1 << 18)
#घोषणा netxen_gb_rx_reset_mac(config_word)	\
	((config_word) |= 1 << 19)

#घोषणा netxen_gb_unset_tx_flowctl(config_word)	\
	((config_word) &= ~(1 << 4))
#घोषणा netxen_gb_unset_rx_flowctl(config_word)	\
	((config_word) &= ~(1 << 5))

#घोषणा netxen_gb_get_tx_synced(config_word)	\
		_netxen_crb_get_bit((config_word), 1)
#घोषणा netxen_gb_get_rx_synced(config_word)	\
		_netxen_crb_get_bit((config_word), 3)
#घोषणा netxen_gb_get_tx_flowctl(config_word)	\
		_netxen_crb_get_bit((config_word), 4)
#घोषणा netxen_gb_get_rx_flowctl(config_word)	\
		_netxen_crb_get_bit((config_word), 5)
#घोषणा netxen_gb_get_soft_reset(config_word)	\
		_netxen_crb_get_bit((config_word), 31)

#घोषणा netxen_gb_get_stationaddress_low(config_word) ((config_word) >> 16)

#घोषणा netxen_gb_set_mii_mgmt_घड़ीselect(config_word, val)	\
		((config_word) |= ((val) & 0x07))
#घोषणा netxen_gb_mii_mgmt_reset(config_word)	\
		((config_word) |= 1 << 31)
#घोषणा netxen_gb_mii_mgmt_unset(config_word)	\
		((config_word) &= ~(1 << 31))

/*
 * NIU GB MII Mgmt Command Register (applies to GB0, GB1, GB2, GB3)
 * Bit 0 : पढ़ो_cycle => 1:perक्रमm single पढ़ो cycle, 0:no-op
 * Bit 1 : scan_cycle => 1:perक्रमm continuous पढ़ो cycles, 0:no-op
 */

#घोषणा netxen_gb_mii_mgmt_set_पढ़ो_cycle(config_word)	\
		((config_word) |= 1 << 0)
#घोषणा netxen_gb_mii_mgmt_reg_addr(config_word, val)	\
		((config_word) |= ((val) & 0x1F))
#घोषणा netxen_gb_mii_mgmt_phy_addr(config_word, val)	\
		((config_word) |= (((val) & 0x1F) << 8))

/*
 * NIU GB MII Mgmt Indicators Register (applies to GB0, GB1, GB2, GB3)
 * Read-only रेजिस्टर.
 * Bit 0 : busy => 1:perक्रमming an MII mgmt cycle, 0:idle
 * Bit 1 : scanning => 1:scan operation in progress, 0:idle
 * Bit 2 : notvalid => :mgmt result data not yet valid, 0:idle
 */
#घोषणा netxen_get_gb_mii_mgmt_busy(config_word)	\
		_netxen_crb_get_bit(config_word, 0)
#घोषणा netxen_get_gb_mii_mgmt_scanning(config_word)	\
		_netxen_crb_get_bit(config_word, 1)
#घोषणा netxen_get_gb_mii_mgmt_notvalid(config_word)	\
		_netxen_crb_get_bit(config_word, 2)
/*
 * NIU XG Pause Ctl Register
 *
 *      Bit 0       : xg0_mask => 1:disable tx छोड़ो frames
 *      Bit 1       : xg0_request => 1:request single छोड़ो frame
 *      Bit 2       : xg0_on_off => 1:request is छोड़ो on, 0:off
 *      Bit 3       : xg1_mask => 1:disable tx छोड़ो frames
 *      Bit 4       : xg1_request => 1:request single छोड़ो frame
 *      Bit 5       : xg1_on_off => 1:request is छोड़ो on, 0:off
 */

#घोषणा netxen_xg_set_xg0_mask(config_word)    \
	((config_word) |= 1 << 0)
#घोषणा netxen_xg_set_xg1_mask(config_word)    \
	((config_word) |= 1 << 3)

#घोषणा netxen_xg_get_xg0_mask(config_word)    \
	_netxen_crb_get_bit((config_word), 0)
#घोषणा netxen_xg_get_xg1_mask(config_word)    \
	_netxen_crb_get_bit((config_word), 3)

#घोषणा netxen_xg_unset_xg0_mask(config_word)  \
	((config_word) &= ~(1 << 0))
#घोषणा netxen_xg_unset_xg1_mask(config_word)  \
	((config_word) &= ~(1 << 3))

/*
 * NIU XG Pause Ctl Register
 *
 *      Bit 0       : xg0_mask => 1:disable tx छोड़ो frames
 *      Bit 1       : xg0_request => 1:request single छोड़ो frame
 *      Bit 2       : xg0_on_off => 1:request is छोड़ो on, 0:off
 *      Bit 3       : xg1_mask => 1:disable tx छोड़ो frames
 *      Bit 4       : xg1_request => 1:request single छोड़ो frame
 *      Bit 5       : xg1_on_off => 1:request is छोड़ो on, 0:off
 */
#घोषणा netxen_gb_set_gb0_mask(config_word)    \
	((config_word) |= 1 << 0)
#घोषणा netxen_gb_set_gb1_mask(config_word)    \
	((config_word) |= 1 << 2)
#घोषणा netxen_gb_set_gb2_mask(config_word)    \
	((config_word) |= 1 << 4)
#घोषणा netxen_gb_set_gb3_mask(config_word)    \
	((config_word) |= 1 << 6)

#घोषणा netxen_gb_get_gb0_mask(config_word)    \
	_netxen_crb_get_bit((config_word), 0)
#घोषणा netxen_gb_get_gb1_mask(config_word)    \
	_netxen_crb_get_bit((config_word), 2)
#घोषणा netxen_gb_get_gb2_mask(config_word)    \
	_netxen_crb_get_bit((config_word), 4)
#घोषणा netxen_gb_get_gb3_mask(config_word)    \
	_netxen_crb_get_bit((config_word), 6)

#घोषणा netxen_gb_unset_gb0_mask(config_word)  \
	((config_word) &= ~(1 << 0))
#घोषणा netxen_gb_unset_gb1_mask(config_word)  \
	((config_word) &= ~(1 << 2))
#घोषणा netxen_gb_unset_gb2_mask(config_word)  \
	((config_word) &= ~(1 << 4))
#घोषणा netxen_gb_unset_gb3_mask(config_word)  \
	((config_word) &= ~(1 << 6))


/*
 * PHY-Specअगरic MII control/status रेजिस्टरs.
 */
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_CONTROL		0
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_STATUS		1
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_PHY_ID_0		2
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_PHY_ID_1		3
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_AUTONEG		4
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_LNKPART		5
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_AUTONEG_MORE	6
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_NEXTPAGE_XMIT	7
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_LNKPART_NEXTPAGE	8
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_1000BT_CONTROL	9
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_1000BT_STATUS	10
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_EXTENDED_STATUS	15
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_PHY_CONTROL		16
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_PHY_STATUS		17
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_INT_ENABLE		18
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_INT_STATUS		19
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_PHY_CONTROL_MORE	20
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_RECV_ERROR_COUNT	21
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_LED_CONTROL		24
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_LED_OVERRIDE	25
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_PHY_CONTROL_MORE_YET	26
#घोषणा NETXEN_NIU_GB_MII_MGMT_ADDR_PHY_STATUS_MORE	27

/*
 * PHY-Specअगरic Status Register (reg 17).
 *
 * Bit 0      : jabber => 1:jabber detected, 0:not
 * Bit 1      : polarity => 1:polarity reversed, 0:normal
 * Bit 2      : recvछोड़ो => 1:receive छोड़ो enabled, 0:disabled
 * Bit 3      : xmitछोड़ो => 1:transmit छोड़ो enabled, 0:disabled
 * Bit 4      : energydetect => 1:sleep, 0:active
 * Bit 5      : करोwnshअगरt => 1:करोwnshअगरt, 0:no करोwnshअगरt
 * Bit 6      : crossover => 1:MDIX (crossover), 0:MDI (no crossover)
 * Bits 7-9   : cablelen => not valid in 10Mb/s mode
 *			0:<50m, 1:50-80m, 2:80-110m, 3:110-140m, 4:>140m
 * Bit 10     : link => 1:link up, 0:link करोwn
 * Bit 11     : resolved => 1:speed and duplex resolved, 0:not yet
 * Bit 12     : pagercvd => 1:page received, 0:page not received
 * Bit 13     : duplex => 1:full duplex, 0:half duplex
 * Bits 14-15 : speed => 0:10Mb/s, 1:100Mb/s, 2:1000Mb/s, 3:rsvd
 */

#घोषणा netxen_get_phy_speed(config_word) (((config_word) >> 14) & 0x03)

#घोषणा netxen_set_phy_speed(config_word, val)	\
		((config_word) |= ((val & 0x03) << 14))
#घोषणा netxen_set_phy_duplex(config_word)	\
		((config_word) |= 1 << 13)
#घोषणा netxen_clear_phy_duplex(config_word)	\
		((config_word) &= ~(1 << 13))

#घोषणा netxen_get_phy_link(config_word)	\
		_netxen_crb_get_bit(config_word, 10)
#घोषणा netxen_get_phy_duplex(config_word)	\
		_netxen_crb_get_bit(config_word, 13)

/*
 * NIU Mode Register.
 * Bit 0 : enable FibreChannel
 * Bit 1 : enable 10/100/1000 Ethernet
 * Bit 2 : enable 10Gb Ethernet
 */

#घोषणा netxen_get_niu_enable_ge(config_word)	\
		_netxen_crb_get_bit(config_word, 1)

#घोषणा NETXEN_NIU_NON_PROMISC_MODE	0
#घोषणा NETXEN_NIU_PROMISC_MODE		1
#घोषणा NETXEN_NIU_ALLMULTI_MODE	2

/*
 * NIU XG MAC Config Register
 *
 * Bit 0 : tx_enable => 1:enable frame xmit, 0:disable
 * Bit 2 : rx_enable => 1:enable frame recv, 0:disable
 * Bit 4 : soft_reset => 1:reset the MAC , 0:no-op
 * Bit 27: xaui_framer_reset
 * Bit 28: xaui_rx_reset
 * Bit 29: xaui_tx_reset
 * Bit 30: xg_ingress_afअगरo_reset
 * Bit 31: xg_egress_afअगरo_reset
 */

#घोषणा netxen_xg_soft_reset(config_word)	\
		((config_word) |= 1 << 4)

प्रकार काष्ठा अणु
	अचिन्हित valid;
	अचिन्हित start_128M;
	अचिन्हित end_128M;
	अचिन्हित start_2M;
पूर्ण crb_128M_2M_sub_block_map_t;

प्रकार काष्ठा अणु
	crb_128M_2M_sub_block_map_t sub_block[16];
पूर्ण crb_128M_2M_block_map_t;

#पूर्ण_अगर				/* __NETXEN_NIC_HW_H_ */
