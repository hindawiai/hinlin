<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 *	      Keyur Chudgar <kchudgar@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_V2_MAC_H__
#घोषणा __XGENE_ENET_V2_MAC_H__

/* Register offsets */
#घोषणा MAC_CONFIG_1		0xa000
#घोषणा MAC_CONFIG_2		0xa004
#घोषणा MII_MGMT_CONFIG		0xa020
#घोषणा MII_MGMT_COMMAND	0xa024
#घोषणा MII_MGMT_ADDRESS	0xa028
#घोषणा MII_MGMT_CONTROL	0xa02c
#घोषणा MII_MGMT_STATUS		0xa030
#घोषणा MII_MGMT_INDICATORS	0xa034
#घोषणा INTERFACE_CONTROL	0xa038
#घोषणा STATION_ADDR0		0xa040
#घोषणा STATION_ADDR1		0xa044

#घोषणा RGMII_REG_0		0x27e0
#घोषणा ICM_CONFIG0_REG_0	0x2c00
#घोषणा ICM_CONFIG2_REG_0	0x2c08
#घोषणा ECM_CONFIG0_REG_0	0x2d00

/* Register fields */
#घोषणा SOFT_RESET		BIT(31)
#घोषणा TX_EN			BIT(0)
#घोषणा RX_EN			BIT(2)
#घोषणा PAD_CRC			BIT(2)
#घोषणा CRC_EN			BIT(1)
#घोषणा FULL_DUPLEX		BIT(0)

#घोषणा INTF_MODE_POS		8
#घोषणा INTF_MODE_LEN		2
#घोषणा HD_MODE_POS		25
#घोषणा HD_MODE_LEN		2
#घोषणा CFG_MACMODE_POS		18
#घोषणा CFG_MACMODE_LEN		2
#घोषणा CFG_WAITASYNCRD_POS	0
#घोषणा CFG_WAITASYNCRD_LEN	16
#घोषणा CFG_SPEED_125_POS	24
#घोषणा CFG_WFIFOFULLTHR_POS	0
#घोषणा CFG_WFIFOFULLTHR_LEN	7
#घोषणा MGMT_CLOCK_SEL_POS	0
#घोषणा MGMT_CLOCK_SEL_LEN	3
#घोषणा PHY_ADDR_POS		8
#घोषणा PHY_ADDR_LEN		5
#घोषणा REG_ADDR_POS		0
#घोषणा REG_ADDR_LEN		5
#घोषणा MII_MGMT_BUSY		BIT(0)
#घोषणा MII_READ_CYCLE		BIT(0)
#घोषणा CFG_WAITASYNCRD_EN	BIT(16)

अटल अंतरभूत व्योम xgene_set_reg_bits(u32 *var, पूर्णांक pos, पूर्णांक len, u32 val)
अणु
	u32 mask = GENMASK(pos + len, pos);

	*var &= ~mask;
	*var |= ((val << pos) & mask);
पूर्ण

अटल अंतरभूत u32 xgene_get_reg_bits(u32 var, पूर्णांक pos, पूर्णांक len)
अणु
	u32 mask = GENMASK(pos + len, pos);

	वापस (var & mask) >> pos;
पूर्ण

#घोषणा SET_REG_BITS(var, field, val)					\
	xgene_set_reg_bits(var, field ## _POS, field ## _LEN, val)

#घोषणा SET_REG_BIT(var, field, val)					\
	xgene_set_reg_bits(var, field ## _POS, 1, val)

#घोषणा GET_REG_BITS(var, field)					\
	xgene_get_reg_bits(var, field ## _POS, field ## _LEN)

#घोषणा GET_REG_BIT(var, field)		((var) & (field))

काष्ठा xge_pdata;

व्योम xge_mac_reset(काष्ठा xge_pdata *pdata);
व्योम xge_mac_set_speed(काष्ठा xge_pdata *pdata);
व्योम xge_mac_enable(काष्ठा xge_pdata *pdata);
व्योम xge_mac_disable(काष्ठा xge_pdata *pdata);
व्योम xge_mac_init(काष्ठा xge_pdata *pdata);
व्योम xge_mac_set_station_addr(काष्ठा xge_pdata *pdata);

#पूर्ण_अगर /* __XGENE_ENET_V2_MAC_H__ */
