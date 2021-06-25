<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Applied Micro X-Gene SoC MDIO Driver
 *
 * Copyright (c) 2016, Applied Micro Circuits Corporation
 * Author: Iyappan Subramanian <isubramanian@apm.com>
 */

#अगर_अघोषित __MDIO_XGENE_H__
#घोषणा __MDIO_XGENE_H__

#घोषणा BLOCK_XG_MDIO_CSR_OFFSET	0x5000
#घोषणा BLOCK_DIAG_CSR_OFFSET		0xd000
#घोषणा XGENET_CONFIG_REG_ADDR		0x20

#घोषणा MAC_ADDR_REG_OFFSET		0x00
#घोषणा MAC_COMMAND_REG_OFFSET		0x04
#घोषणा MAC_WRITE_REG_OFFSET		0x08
#घोषणा MAC_READ_REG_OFFSET		0x0c
#घोषणा MAC_COMMAND_DONE_REG_OFFSET	0x10

#घोषणा CLKEN_OFFSET			0x08
#घोषणा SRST_OFFSET			0x00

#घोषणा MENET_CFG_MEM_RAM_SHUTDOWN_ADDR	0x70
#घोषणा MENET_BLOCK_MEM_RDY_ADDR	0x74

#घोषणा MAC_CONFIG_1_ADDR		0x00
#घोषणा MII_MGMT_COMMAND_ADDR		0x24
#घोषणा MII_MGMT_ADDRESS_ADDR		0x28
#घोषणा MII_MGMT_CONTROL_ADDR		0x2c
#घोषणा MII_MGMT_STATUS_ADDR		0x30
#घोषणा MII_MGMT_INDICATORS_ADDR	0x34
#घोषणा SOFT_RESET			BIT(31)

#घोषणा MII_MGMT_CONFIG_ADDR            0x20
#घोषणा MII_MGMT_COMMAND_ADDR           0x24
#घोषणा MII_MGMT_ADDRESS_ADDR           0x28
#घोषणा MII_MGMT_CONTROL_ADDR           0x2c
#घोषणा MII_MGMT_STATUS_ADDR            0x30
#घोषणा MII_MGMT_INDICATORS_ADDR        0x34

#घोषणा MIIM_COMMAND_ADDR               0x20
#घोषणा MIIM_FIELD_ADDR                 0x24
#घोषणा MIIM_CONFIGURATION_ADDR         0x28
#घोषणा MIIM_LINKFAILVECTOR_ADDR        0x2c
#घोषणा MIIM_INDICATOR_ADDR             0x30
#घोषणा MIIMRD_FIELD_ADDR               0x34

#घोषणा MDIO_CSR_OFFSET			0x5000

#घोषणा REG_ADDR_POS			0
#घोषणा REG_ADDR_LEN			5
#घोषणा PHY_ADDR_POS			8
#घोषणा PHY_ADDR_LEN			5

#घोषणा HSTMIIMWRDAT_POS		0
#घोषणा HSTMIIMWRDAT_LEN		16
#घोषणा HSTPHYADX_POS			23
#घोषणा HSTPHYADX_LEN			5
#घोषणा HSTREGADX_POS			18
#घोषणा HSTREGADX_LEN			5
#घोषणा HSTLDCMD			BIT(3)
#घोषणा HSTMIIMCMD_POS			0
#घोषणा HSTMIIMCMD_LEN			3

#घोषणा BUSY_MASK			BIT(0)
#घोषणा READ_CYCLE_MASK			BIT(0)

क्रमागत xgene_enet_cmd अणु
	XGENE_ENET_WR_CMD = BIT(31),
	XGENE_ENET_RD_CMD = BIT(30)
पूर्ण;

क्रमागत अणु
	MIIM_CMD_IDLE,
	MIIM_CMD_LEGACY_WRITE,
	MIIM_CMD_LEGACY_READ,
पूर्ण;

क्रमागत xgene_mdio_id अणु
	XGENE_MDIO_RGMII = 1,
	XGENE_MDIO_XFI
पूर्ण;

काष्ठा xgene_mdio_pdata अणु
	काष्ठा clk *clk;
	काष्ठा device *dev;
	व्योम __iomem *mac_csr_addr;
	व्योम __iomem *diag_csr_addr;
	व्योम __iomem *mdio_csr_addr;
	काष्ठा mii_bus *mdio_bus;
	पूर्णांक mdio_id;
	spinlock_t mac_lock; /* mac lock */
पूर्ण;

/* Set the specअगरied value पूर्णांकo a bit-field defined by its starting position
 * and length within a single u64.
 */
अटल अंतरभूत u64 xgene_enet_set_field_value(पूर्णांक pos, पूर्णांक len, u64 val)
अणु
	वापस (val & ((1ULL << len) - 1)) << pos;
पूर्ण

#घोषणा SET_VAL(field, val) \
		xgene_enet_set_field_value(field ## _POS, field ## _LEN, val)

#घोषणा SET_BIT(field) \
		xgene_enet_set_field_value(field ## _POS, 1, 1)

/* Get the value from a bit-field defined by its starting position
 * and length within the specअगरied u64.
 */
अटल अंतरभूत u64 xgene_enet_get_field_value(पूर्णांक pos, पूर्णांक len, u64 src)
अणु
	वापस (src >> pos) & ((1ULL << len) - 1);
पूर्ण

#घोषणा GET_VAL(field, src) \
		xgene_enet_get_field_value(field ## _POS, field ## _LEN, src)

#घोषणा GET_BIT(field, src) \
		xgene_enet_get_field_value(field ## _POS, 1, src)

u32 xgene_mdio_rd_mac(काष्ठा xgene_mdio_pdata *pdata, u32 rd_addr);
व्योम xgene_mdio_wr_mac(काष्ठा xgene_mdio_pdata *pdata, u32 wr_addr, u32 data);
पूर्णांक xgene_mdio_rgmii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg);
पूर्णांक xgene_mdio_rgmii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg, u16 data);
काष्ठा phy_device *xgene_enet_phy_रेजिस्टर(काष्ठा mii_bus *bus, पूर्णांक phy_addr);

#पूर्ण_अगर  /* __MDIO_XGENE_H__ */
