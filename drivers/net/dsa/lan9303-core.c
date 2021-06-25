<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Pengutronix, Juergen Borleis <kernel@pengutronix.de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/etherdevice.h>

#समावेश "lan9303.h"

#घोषणा LAN9303_NUM_PORTS 3

/* 13.2 System Control and Status Registers
 * Multiply रेजिस्टर number by 4 to get address offset.
 */
#घोषणा LAN9303_CHIP_REV 0x14
# define LAN9303_CHIP_ID 0x9303
#घोषणा LAN9303_IRQ_CFG 0x15
# define LAN9303_IRQ_CFG_IRQ_ENABLE BIT(8)
# define LAN9303_IRQ_CFG_IRQ_POL BIT(4)
# define LAN9303_IRQ_CFG_IRQ_TYPE BIT(0)
#घोषणा LAN9303_INT_STS 0x16
# define LAN9303_INT_STS_PHY_INT2 BIT(27)
# define LAN9303_INT_STS_PHY_INT1 BIT(26)
#घोषणा LAN9303_INT_EN 0x17
# define LAN9303_INT_EN_PHY_INT2_EN BIT(27)
# define LAN9303_INT_EN_PHY_INT1_EN BIT(26)
#घोषणा LAN9303_HW_CFG 0x1D
# define LAN9303_HW_CFG_READY BIT(27)
# define LAN9303_HW_CFG_AMDX_EN_PORT2 BIT(26)
# define LAN9303_HW_CFG_AMDX_EN_PORT1 BIT(25)
#घोषणा LAN9303_PMI_DATA 0x29
#घोषणा LAN9303_PMI_ACCESS 0x2A
# define LAN9303_PMI_ACCESS_PHY_ADDR(x) (((x) & 0x1f) << 11)
# define LAN9303_PMI_ACCESS_MIIRINDA(x) (((x) & 0x1f) << 6)
# define LAN9303_PMI_ACCESS_MII_BUSY BIT(0)
# define LAN9303_PMI_ACCESS_MII_WRITE BIT(1)
#घोषणा LAN9303_MANUAL_FC_1 0x68
#घोषणा LAN9303_MANUAL_FC_2 0x69
#घोषणा LAN9303_MANUAL_FC_0 0x6a
#घोषणा LAN9303_SWITCH_CSR_DATA 0x6b
#घोषणा LAN9303_SWITCH_CSR_CMD 0x6c
#घोषणा LAN9303_SWITCH_CSR_CMD_BUSY BIT(31)
#घोषणा LAN9303_SWITCH_CSR_CMD_RW BIT(30)
#घोषणा LAN9303_SWITCH_CSR_CMD_LANES (BIT(19) | BIT(18) | BIT(17) | BIT(16))
#घोषणा LAN9303_VIRT_PHY_BASE 0x70
#घोषणा LAN9303_VIRT_SPECIAL_CTRL 0x77
#घोषणा  LAN9303_VIRT_SPECIAL_TURBO BIT(10) /*Turbo MII Enable*/

/*13.4 Switch Fabric Control and Status Registers
 * Accessed indirectly via SWITCH_CSR_CMD, SWITCH_CSR_DATA.
 */
#घोषणा LAN9303_SW_DEV_ID 0x0000
#घोषणा LAN9303_SW_RESET 0x0001
#घोषणा LAN9303_SW_RESET_RESET BIT(0)
#घोषणा LAN9303_SW_IMR 0x0004
#घोषणा LAN9303_SW_IPR 0x0005
#घोषणा LAN9303_MAC_VER_ID_0 0x0400
#घोषणा LAN9303_MAC_RX_CFG_0 0x0401
# define LAN9303_MAC_RX_CFG_X_REJECT_MAC_TYPES BIT(1)
# define LAN9303_MAC_RX_CFG_X_RX_ENABLE BIT(0)
#घोषणा LAN9303_MAC_RX_UNDSZE_CNT_0 0x0410
#घोषणा LAN9303_MAC_RX_64_CNT_0 0x0411
#घोषणा LAN9303_MAC_RX_127_CNT_0 0x0412
#घोषणा LAN9303_MAC_RX_255_CNT_0 0x413
#घोषणा LAN9303_MAC_RX_511_CNT_0 0x0414
#घोषणा LAN9303_MAC_RX_1023_CNT_0 0x0415
#घोषणा LAN9303_MAC_RX_MAX_CNT_0 0x0416
#घोषणा LAN9303_MAC_RX_OVRSZE_CNT_0 0x0417
#घोषणा LAN9303_MAC_RX_PKTOK_CNT_0 0x0418
#घोषणा LAN9303_MAC_RX_CRCERR_CNT_0 0x0419
#घोषणा LAN9303_MAC_RX_MULCST_CNT_0 0x041a
#घोषणा LAN9303_MAC_RX_BRDCST_CNT_0 0x041b
#घोषणा LAN9303_MAC_RX_PAUSE_CNT_0 0x041c
#घोषणा LAN9303_MAC_RX_FRAG_CNT_0 0x041d
#घोषणा LAN9303_MAC_RX_JABB_CNT_0 0x041e
#घोषणा LAN9303_MAC_RX_ALIGN_CNT_0 0x041f
#घोषणा LAN9303_MAC_RX_PKTLEN_CNT_0 0x0420
#घोषणा LAN9303_MAC_RX_GOODPKTLEN_CNT_0 0x0421
#घोषणा LAN9303_MAC_RX_SYMBL_CNT_0 0x0422
#घोषणा LAN9303_MAC_RX_CTLFRM_CNT_0 0x0423

#घोषणा LAN9303_MAC_TX_CFG_0 0x0440
# define LAN9303_MAC_TX_CFG_X_TX_IFG_CONFIG_DEFAULT (21 << 2)
# define LAN9303_MAC_TX_CFG_X_TX_PAD_ENABLE BIT(1)
# define LAN9303_MAC_TX_CFG_X_TX_ENABLE BIT(0)
#घोषणा LAN9303_MAC_TX_DEFER_CNT_0 0x0451
#घोषणा LAN9303_MAC_TX_PAUSE_CNT_0 0x0452
#घोषणा LAN9303_MAC_TX_PKTOK_CNT_0 0x0453
#घोषणा LAN9303_MAC_TX_64_CNT_0 0x0454
#घोषणा LAN9303_MAC_TX_127_CNT_0 0x0455
#घोषणा LAN9303_MAC_TX_255_CNT_0 0x0456
#घोषणा LAN9303_MAC_TX_511_CNT_0 0x0457
#घोषणा LAN9303_MAC_TX_1023_CNT_0 0x0458
#घोषणा LAN9303_MAC_TX_MAX_CNT_0 0x0459
#घोषणा LAN9303_MAC_TX_UNDSZE_CNT_0 0x045a
#घोषणा LAN9303_MAC_TX_PKTLEN_CNT_0 0x045c
#घोषणा LAN9303_MAC_TX_BRDCST_CNT_0 0x045d
#घोषणा LAN9303_MAC_TX_MULCST_CNT_0 0x045e
#घोषणा LAN9303_MAC_TX_LATECOL_0 0x045f
#घोषणा LAN9303_MAC_TX_EXCOL_CNT_0 0x0460
#घोषणा LAN9303_MAC_TX_SNGLECOL_CNT_0 0x0461
#घोषणा LAN9303_MAC_TX_MULTICOL_CNT_0 0x0462
#घोषणा LAN9303_MAC_TX_TOTALCOL_CNT_0 0x0463

#घोषणा LAN9303_MAC_VER_ID_1 0x0800
#घोषणा LAN9303_MAC_RX_CFG_1 0x0801
#घोषणा LAN9303_MAC_TX_CFG_1 0x0840
#घोषणा LAN9303_MAC_VER_ID_2 0x0c00
#घोषणा LAN9303_MAC_RX_CFG_2 0x0c01
#घोषणा LAN9303_MAC_TX_CFG_2 0x0c40
#घोषणा LAN9303_SWE_ALR_CMD 0x1800
# define LAN9303_ALR_CMD_MAKE_ENTRY    BIT(2)
# define LAN9303_ALR_CMD_GET_FIRST     BIT(1)
# define LAN9303_ALR_CMD_GET_NEXT      BIT(0)
#घोषणा LAN9303_SWE_ALR_WR_DAT_0 0x1801
#घोषणा LAN9303_SWE_ALR_WR_DAT_1 0x1802
# define LAN9303_ALR_DAT1_VALID        BIT(26)
# define LAN9303_ALR_DAT1_END_OF_TABL  BIT(25)
# define LAN9303_ALR_DAT1_AGE_OVERRID  BIT(25)
# define LAN9303_ALR_DAT1_STATIC       BIT(24)
# define LAN9303_ALR_DAT1_PORT_BITOFFS  16
# define LAN9303_ALR_DAT1_PORT_MASK    (7 << LAN9303_ALR_DAT1_PORT_BITOFFS)
#घोषणा LAN9303_SWE_ALR_RD_DAT_0 0x1805
#घोषणा LAN9303_SWE_ALR_RD_DAT_1 0x1806
#घोषणा LAN9303_SWE_ALR_CMD_STS 0x1808
# define ALR_STS_MAKE_PEND     BIT(0)
#घोषणा LAN9303_SWE_VLAN_CMD 0x180b
# define LAN9303_SWE_VLAN_CMD_RNW BIT(5)
# define LAN9303_SWE_VLAN_CMD_PVIDNVLAN BIT(4)
#घोषणा LAN9303_SWE_VLAN_WR_DATA 0x180c
#घोषणा LAN9303_SWE_VLAN_RD_DATA 0x180e
# define LAN9303_SWE_VLAN_MEMBER_PORT2 BIT(17)
# define LAN9303_SWE_VLAN_UNTAG_PORT2 BIT(16)
# define LAN9303_SWE_VLAN_MEMBER_PORT1 BIT(15)
# define LAN9303_SWE_VLAN_UNTAG_PORT1 BIT(14)
# define LAN9303_SWE_VLAN_MEMBER_PORT0 BIT(13)
# define LAN9303_SWE_VLAN_UNTAG_PORT0 BIT(12)
#घोषणा LAN9303_SWE_VLAN_CMD_STS 0x1810
#घोषणा LAN9303_SWE_GLB_INGRESS_CFG 0x1840
# define LAN9303_SWE_GLB_INGR_IGMP_TRAP BIT(7)
# define LAN9303_SWE_GLB_INGR_IGMP_PORT(p) BIT(10 + p)
#घोषणा LAN9303_SWE_PORT_STATE 0x1843
# define LAN9303_SWE_PORT_STATE_FORWARDING_PORT2 (0)
# define LAN9303_SWE_PORT_STATE_LEARNING_PORT2 BIT(5)
# define LAN9303_SWE_PORT_STATE_BLOCKING_PORT2 BIT(4)
# define LAN9303_SWE_PORT_STATE_FORWARDING_PORT1 (0)
# define LAN9303_SWE_PORT_STATE_LEARNING_PORT1 BIT(3)
# define LAN9303_SWE_PORT_STATE_BLOCKING_PORT1 BIT(2)
# define LAN9303_SWE_PORT_STATE_FORWARDING_PORT0 (0)
# define LAN9303_SWE_PORT_STATE_LEARNING_PORT0 BIT(1)
# define LAN9303_SWE_PORT_STATE_BLOCKING_PORT0 BIT(0)
# define LAN9303_SWE_PORT_STATE_DISABLED_PORT0 (3)
#घोषणा LAN9303_SWE_PORT_MIRROR 0x1846
# define LAN9303_SWE_PORT_MIRROR_SNIFF_ALL BIT(8)
# define LAN9303_SWE_PORT_MIRROR_SNIFFER_PORT2 BIT(7)
# define LAN9303_SWE_PORT_MIRROR_SNIFFER_PORT1 BIT(6)
# define LAN9303_SWE_PORT_MIRROR_SNIFFER_PORT0 BIT(5)
# define LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT2 BIT(4)
# define LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT1 BIT(3)
# define LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT0 BIT(2)
# define LAN9303_SWE_PORT_MIRROR_ENABLE_RX_MIRRORING BIT(1)
# define LAN9303_SWE_PORT_MIRROR_ENABLE_TX_MIRRORING BIT(0)
# define LAN9303_SWE_PORT_MIRROR_DISABLED 0
#घोषणा LAN9303_SWE_INGRESS_PORT_TYPE 0x1847
#घोषणा  LAN9303_SWE_INGRESS_PORT_TYPE_VLAN 3
#घोषणा LAN9303_BM_CFG 0x1c00
#घोषणा LAN9303_BM_EGRSS_PORT_TYPE 0x1c0c
# define LAN9303_BM_EGRSS_PORT_TYPE_SPECIAL_TAG_PORT2 (BIT(17) | BIT(16))
# define LAN9303_BM_EGRSS_PORT_TYPE_SPECIAL_TAG_PORT1 (BIT(9) | BIT(8))
# define LAN9303_BM_EGRSS_PORT_TYPE_SPECIAL_TAG_PORT0 (BIT(1) | BIT(0))

#घोषणा LAN9303_SWITCH_PORT_REG(port, reg0) (0x400 * (port) + (reg0))

/* the built-in PHYs are of type LAN911X */
#घोषणा MII_LAN911X_SPECIAL_MODES 0x12
#घोषणा MII_LAN911X_SPECIAL_CONTROL_STATUS 0x1f

अटल स्थिर काष्ठा regmap_range lan9303_valid_regs[] = अणु
	regmap_reg_range(0x14, 0x17), /* misc, पूर्णांकerrupt */
	regmap_reg_range(0x19, 0x19), /* endian test */
	regmap_reg_range(0x1d, 0x1d), /* hardware config */
	regmap_reg_range(0x23, 0x24), /* general purpose समयr */
	regmap_reg_range(0x27, 0x27), /* counter */
	regmap_reg_range(0x29, 0x2a), /* PMI index regs */
	regmap_reg_range(0x68, 0x6a), /* flow control */
	regmap_reg_range(0x6b, 0x6c), /* चयन fabric indirect regs */
	regmap_reg_range(0x6d, 0x6f), /* misc */
	regmap_reg_range(0x70, 0x77), /* भव phy */
	regmap_reg_range(0x78, 0x7a), /* GPIO */
	regmap_reg_range(0x7c, 0x7e), /* MAC & reset */
	regmap_reg_range(0x80, 0xb7), /* चयन fabric direct regs (wr only) */
पूर्ण;

अटल स्थिर काष्ठा regmap_range lan9303_reserved_ranges[] = अणु
	regmap_reg_range(0x00, 0x13),
	regmap_reg_range(0x18, 0x18),
	regmap_reg_range(0x1a, 0x1c),
	regmap_reg_range(0x1e, 0x22),
	regmap_reg_range(0x25, 0x26),
	regmap_reg_range(0x28, 0x28),
	regmap_reg_range(0x2b, 0x67),
	regmap_reg_range(0x7b, 0x7b),
	regmap_reg_range(0x7f, 0x7f),
	regmap_reg_range(0xb8, 0xff),
पूर्ण;

स्थिर काष्ठा regmap_access_table lan9303_रेजिस्टर_set = अणु
	.yes_ranges = lan9303_valid_regs,
	.n_yes_ranges = ARRAY_SIZE(lan9303_valid_regs),
	.no_ranges = lan9303_reserved_ranges,
	.n_no_ranges = ARRAY_SIZE(lan9303_reserved_ranges),
पूर्ण;
EXPORT_SYMBOL(lan9303_रेजिस्टर_set);

अटल पूर्णांक lan9303_पढ़ो(काष्ठा regmap *regmap, अचिन्हित पूर्णांक offset, u32 *reg)
अणु
	पूर्णांक ret, i;

	/* we can lose arbitration क्रम the I2C हाल, because the device
	 * tries to detect and पढ़ो an बाह्यal EEPROM after reset and acts as
	 * a master on the shared I2C bus itself. This conflicts with our
	 * attempts to access the device as a slave at the same moment.
	 */
	क्रम (i = 0; i < 5; i++) अणु
		ret = regmap_पढ़ो(regmap, offset, reg);
		अगर (!ret)
			वापस 0;
		अगर (ret != -EAGAIN)
			अवरोध;
		msleep(500);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक lan9303_पढ़ो_रुको(काष्ठा lan9303 *chip, पूर्णांक offset, u32 mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 25; i++) अणु
		u32 reg;
		पूर्णांक ret;

		ret = lan9303_पढ़ो(chip->regmap, offset, &reg);
		अगर (ret) अणु
			dev_err(chip->dev, "%s failed to read offset %d: %d\n",
				__func__, offset, ret);
			वापस ret;
		पूर्ण
		अगर (!(reg & mask))
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक lan9303_virt_phy_reg_पढ़ो(काष्ठा lan9303 *chip, पूर्णांक regnum)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (regnum > MII_EXPANSION)
		वापस -EINVAL;

	ret = lan9303_पढ़ो(chip->regmap, LAN9303_VIRT_PHY_BASE + regnum, &val);
	अगर (ret)
		वापस ret;

	वापस val & 0xffff;
पूर्ण

अटल पूर्णांक lan9303_virt_phy_reg_ग_लिखो(काष्ठा lan9303 *chip, पूर्णांक regnum, u16 val)
अणु
	अगर (regnum > MII_EXPANSION)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(chip->regmap, LAN9303_VIRT_PHY_BASE + regnum, val);
पूर्ण

अटल पूर्णांक lan9303_indirect_phy_रुको_क्रम_completion(काष्ठा lan9303 *chip)
अणु
	वापस lan9303_पढ़ो_रुको(chip, LAN9303_PMI_ACCESS,
				 LAN9303_PMI_ACCESS_MII_BUSY);
पूर्ण

अटल पूर्णांक lan9303_indirect_phy_पढ़ो(काष्ठा lan9303 *chip, पूर्णांक addr, पूर्णांक regnum)
अणु
	पूर्णांक ret;
	u32 val;

	val = LAN9303_PMI_ACCESS_PHY_ADDR(addr);
	val |= LAN9303_PMI_ACCESS_MIIRINDA(regnum);

	mutex_lock(&chip->indirect_mutex);

	ret = lan9303_indirect_phy_रुको_क्रम_completion(chip);
	अगर (ret)
		जाओ on_error;

	/* start the MII पढ़ो cycle */
	ret = regmap_ग_लिखो(chip->regmap, LAN9303_PMI_ACCESS, val);
	अगर (ret)
		जाओ on_error;

	ret = lan9303_indirect_phy_रुको_क्रम_completion(chip);
	अगर (ret)
		जाओ on_error;

	/* पढ़ो the result of this operation */
	ret = lan9303_पढ़ो(chip->regmap, LAN9303_PMI_DATA, &val);
	अगर (ret)
		जाओ on_error;

	mutex_unlock(&chip->indirect_mutex);

	वापस val & 0xffff;

on_error:
	mutex_unlock(&chip->indirect_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक lan9303_indirect_phy_ग_लिखो(काष्ठा lan9303 *chip, पूर्णांक addr,
				      पूर्णांक regnum, u16 val)
अणु
	पूर्णांक ret;
	u32 reg;

	reg = LAN9303_PMI_ACCESS_PHY_ADDR(addr);
	reg |= LAN9303_PMI_ACCESS_MIIRINDA(regnum);
	reg |= LAN9303_PMI_ACCESS_MII_WRITE;

	mutex_lock(&chip->indirect_mutex);

	ret = lan9303_indirect_phy_रुको_क्रम_completion(chip);
	अगर (ret)
		जाओ on_error;

	/* ग_लिखो the data first... */
	ret = regmap_ग_लिखो(chip->regmap, LAN9303_PMI_DATA, val);
	अगर (ret)
		जाओ on_error;

	/* ...then start the MII ग_लिखो cycle */
	ret = regmap_ग_लिखो(chip->regmap, LAN9303_PMI_ACCESS, reg);

on_error:
	mutex_unlock(&chip->indirect_mutex);
	वापस ret;
पूर्ण

स्थिर काष्ठा lan9303_phy_ops lan9303_indirect_phy_ops = अणु
	.phy_पढ़ो = lan9303_indirect_phy_पढ़ो,
	.phy_ग_लिखो = lan9303_indirect_phy_ग_लिखो,
पूर्ण;
EXPORT_SYMBOL_GPL(lan9303_indirect_phy_ops);

अटल पूर्णांक lan9303_चयन_रुको_क्रम_completion(काष्ठा lan9303 *chip)
अणु
	वापस lan9303_पढ़ो_रुको(chip, LAN9303_SWITCH_CSR_CMD,
				 LAN9303_SWITCH_CSR_CMD_BUSY);
पूर्ण

अटल पूर्णांक lan9303_ग_लिखो_चयन_reg(काष्ठा lan9303 *chip, u16 regnum, u32 val)
अणु
	u32 reg;
	पूर्णांक ret;

	reg = regnum;
	reg |= LAN9303_SWITCH_CSR_CMD_LANES;
	reg |= LAN9303_SWITCH_CSR_CMD_BUSY;

	mutex_lock(&chip->indirect_mutex);

	ret = lan9303_चयन_रुको_क्रम_completion(chip);
	अगर (ret)
		जाओ on_error;

	ret = regmap_ग_लिखो(chip->regmap, LAN9303_SWITCH_CSR_DATA, val);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to write csr data reg: %d\n", ret);
		जाओ on_error;
	पूर्ण

	/* trigger ग_लिखो */
	ret = regmap_ग_लिखो(chip->regmap, LAN9303_SWITCH_CSR_CMD, reg);
	अगर (ret)
		dev_err(chip->dev, "Failed to write csr command reg: %d\n",
			ret);

on_error:
	mutex_unlock(&chip->indirect_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक lan9303_पढ़ो_चयन_reg(काष्ठा lan9303 *chip, u16 regnum, u32 *val)
अणु
	u32 reg;
	पूर्णांक ret;

	reg = regnum;
	reg |= LAN9303_SWITCH_CSR_CMD_LANES;
	reg |= LAN9303_SWITCH_CSR_CMD_RW;
	reg |= LAN9303_SWITCH_CSR_CMD_BUSY;

	mutex_lock(&chip->indirect_mutex);

	ret = lan9303_चयन_रुको_क्रम_completion(chip);
	अगर (ret)
		जाओ on_error;

	/* trigger पढ़ो */
	ret = regmap_ग_लिखो(chip->regmap, LAN9303_SWITCH_CSR_CMD, reg);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to write csr command reg: %d\n",
			ret);
		जाओ on_error;
	पूर्ण

	ret = lan9303_चयन_रुको_क्रम_completion(chip);
	अगर (ret)
		जाओ on_error;

	ret = lan9303_पढ़ो(chip->regmap, LAN9303_SWITCH_CSR_DATA, val);
	अगर (ret)
		dev_err(chip->dev, "Failed to read csr data reg: %d\n", ret);
on_error:
	mutex_unlock(&chip->indirect_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक lan9303_ग_लिखो_चयन_reg_mask(काष्ठा lan9303 *chip, u16 regnum,
					 u32 val, u32 mask)
अणु
	पूर्णांक ret;
	u32 reg;

	ret = lan9303_पढ़ो_चयन_reg(chip, regnum, &reg);
	अगर (ret)
		वापस ret;

	reg = (reg & ~mask) | val;

	वापस lan9303_ग_लिखो_चयन_reg(chip, regnum, reg);
पूर्ण

अटल पूर्णांक lan9303_ग_लिखो_चयन_port(काष्ठा lan9303 *chip, पूर्णांक port,
				     u16 regnum, u32 val)
अणु
	वापस lan9303_ग_लिखो_चयन_reg(
		chip, LAN9303_SWITCH_PORT_REG(port, regnum), val);
पूर्ण

अटल पूर्णांक lan9303_पढ़ो_चयन_port(काष्ठा lan9303 *chip, पूर्णांक port,
				    u16 regnum, u32 *val)
अणु
	वापस lan9303_पढ़ो_चयन_reg(
		chip, LAN9303_SWITCH_PORT_REG(port, regnum), val);
पूर्ण

अटल पूर्णांक lan9303_detect_phy_setup(काष्ठा lan9303 *chip)
अणु
	पूर्णांक reg;

	/* Calculate chip->phy_addr_base:
	 * Depending on the 'phy_addr_sel_strap' setting, the three phys are
	 * using IDs 0-1-2 or IDs 1-2-3. We cannot पढ़ो back the
	 * 'phy_addr_sel_strap' setting directly, so we need a test, which
	 * configuration is active:
	 * Special reg 18 of phy 3 पढ़ोs as 0x0000, अगर 'phy_addr_sel_strap' is 0
	 * and the IDs are 0-1-2, अन्यथा it contains something dअगरferent from
	 * 0x0000, which means 'phy_addr_sel_strap' is 1 and the IDs are 1-2-3.
	 * 0xffff is वापसed on MDIO पढ़ो with no response.
	 */
	reg = chip->ops->phy_पढ़ो(chip, 3, MII_LAN911X_SPECIAL_MODES);
	अगर (reg < 0) अणु
		dev_err(chip->dev, "Failed to detect phy config: %d\n", reg);
		वापस reg;
	पूर्ण

	chip->phy_addr_base = reg != 0 && reg != 0xffff;

	dev_dbg(chip->dev, "Phy setup '%s' detected\n",
		chip->phy_addr_base ? "1-2-3" : "0-1-2");

	वापस 0;
पूर्ण

/* Map ALR-port bits to port biपंचांगap, and back */
अटल स्थिर पूर्णांक alrport_2_porपंचांगap[] = अणु1, 2, 4, 0, 3, 5, 6, 7 पूर्ण;
अटल स्थिर पूर्णांक porपंचांगap_2_alrport[] = अणु3, 0, 1, 4, 2, 5, 6, 7 पूर्ण;

/* Return poपूर्णांकer to first मुक्त ALR cache entry, वापस शून्य अगर none */
अटल काष्ठा lan9303_alr_cache_entry *
lan9303_alr_cache_find_मुक्त(काष्ठा lan9303 *chip)
अणु
	पूर्णांक i;
	काष्ठा lan9303_alr_cache_entry *entr = chip->alr_cache;

	क्रम (i = 0; i < LAN9303_NUM_ALR_RECORDS; i++, entr++)
		अगर (entr->port_map == 0)
			वापस entr;

	वापस शून्य;
पूर्ण

/* Return poपूर्णांकer to ALR cache entry matching MAC address */
अटल काष्ठा lan9303_alr_cache_entry *
lan9303_alr_cache_find_mac(काष्ठा lan9303 *chip, स्थिर u8 *mac_addr)
अणु
	पूर्णांक i;
	काष्ठा lan9303_alr_cache_entry *entr = chip->alr_cache;

	BUILD_BUG_ON_MSG(माप(काष्ठा lan9303_alr_cache_entry) & 1,
			 "ether_addr_equal require u16 alignment");

	क्रम (i = 0; i < LAN9303_NUM_ALR_RECORDS; i++, entr++)
		अगर (ether_addr_equal(entr->mac_addr, mac_addr))
			वापस entr;

	वापस शून्य;
पूर्ण

अटल पूर्णांक lan9303_csr_reg_रुको(काष्ठा lan9303 *chip, पूर्णांक regno, u32 mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 25; i++) अणु
		u32 reg;

		lan9303_पढ़ो_चयन_reg(chip, regno, &reg);
		अगर (!(reg & mask))
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक lan9303_alr_make_entry_raw(काष्ठा lan9303 *chip, u32 dat0, u32 dat1)
अणु
	lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_ALR_WR_DAT_0, dat0);
	lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_ALR_WR_DAT_1, dat1);
	lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_ALR_CMD,
				 LAN9303_ALR_CMD_MAKE_ENTRY);
	lan9303_csr_reg_रुको(chip, LAN9303_SWE_ALR_CMD_STS, ALR_STS_MAKE_PEND);
	lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_ALR_CMD, 0);

	वापस 0;
पूर्ण

प्रकार व्योम alr_loop_cb_t(काष्ठा lan9303 *chip, u32 dat0, u32 dat1,
			   पूर्णांक porपंचांगap, व्योम *ctx);

अटल व्योम lan9303_alr_loop(काष्ठा lan9303 *chip, alr_loop_cb_t *cb, व्योम *ctx)
अणु
	पूर्णांक i;

	mutex_lock(&chip->alr_mutex);
	lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_ALR_CMD,
				 LAN9303_ALR_CMD_GET_FIRST);
	lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_ALR_CMD, 0);

	क्रम (i = 1; i < LAN9303_NUM_ALR_RECORDS; i++) अणु
		u32 dat0, dat1;
		पूर्णांक alrport, porपंचांगap;

		lan9303_पढ़ो_चयन_reg(chip, LAN9303_SWE_ALR_RD_DAT_0, &dat0);
		lan9303_पढ़ो_चयन_reg(chip, LAN9303_SWE_ALR_RD_DAT_1, &dat1);
		अगर (dat1 & LAN9303_ALR_DAT1_END_OF_TABL)
			अवरोध;

		alrport = (dat1 & LAN9303_ALR_DAT1_PORT_MASK) >>
						LAN9303_ALR_DAT1_PORT_BITOFFS;
		porपंचांगap = alrport_2_porपंचांगap[alrport];

		cb(chip, dat0, dat1, porपंचांगap, ctx);

		lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_ALR_CMD,
					 LAN9303_ALR_CMD_GET_NEXT);
		lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_ALR_CMD, 0);
	पूर्ण
	mutex_unlock(&chip->alr_mutex);
पूर्ण

अटल व्योम alr_reg_to_mac(u32 dat0, u32 dat1, u8 mac[6])
अणु
	mac[0] = (dat0 >>  0) & 0xff;
	mac[1] = (dat0 >>  8) & 0xff;
	mac[2] = (dat0 >> 16) & 0xff;
	mac[3] = (dat0 >> 24) & 0xff;
	mac[4] = (dat1 >>  0) & 0xff;
	mac[5] = (dat1 >>  8) & 0xff;
पूर्ण

काष्ठा del_port_learned_ctx अणु
	पूर्णांक port;
पूर्ण;

/* Clear learned (non-अटल) entry on given port */
अटल व्योम alr_loop_cb_del_port_learned(काष्ठा lan9303 *chip, u32 dat0,
					 u32 dat1, पूर्णांक porपंचांगap, व्योम *ctx)
अणु
	काष्ठा del_port_learned_ctx *del_ctx = ctx;
	पूर्णांक port = del_ctx->port;

	अगर (((BIT(port) & porपंचांगap) == 0) || (dat1 & LAN9303_ALR_DAT1_STATIC))
		वापस;

	/* learned entries has only one port, we can just delete */
	dat1 &= ~LAN9303_ALR_DAT1_VALID; /* delete entry */
	lan9303_alr_make_entry_raw(chip, dat0, dat1);
पूर्ण

काष्ठा port_fdb_dump_ctx अणु
	पूर्णांक port;
	व्योम *data;
	dsa_fdb_dump_cb_t *cb;
पूर्ण;

अटल व्योम alr_loop_cb_fdb_port_dump(काष्ठा lan9303 *chip, u32 dat0,
				      u32 dat1, पूर्णांक porपंचांगap, व्योम *ctx)
अणु
	काष्ठा port_fdb_dump_ctx *dump_ctx = ctx;
	u8 mac[ETH_ALEN];
	bool is_अटल;

	अगर ((BIT(dump_ctx->port) & porपंचांगap) == 0)
		वापस;

	alr_reg_to_mac(dat0, dat1, mac);
	is_अटल = !!(dat1 & LAN9303_ALR_DAT1_STATIC);
	dump_ctx->cb(mac, 0, is_अटल, dump_ctx->data);
पूर्ण

/* Set a अटल ALR entry. Delete entry अगर port_map is zero */
अटल व्योम lan9303_alr_set_entry(काष्ठा lan9303 *chip, स्थिर u8 *mac,
				  u8 port_map, bool stp_override)
अणु
	u32 dat0, dat1, alr_port;

	dev_dbg(chip->dev, "%s(%pM, %d)\n", __func__, mac, port_map);
	dat1 = LAN9303_ALR_DAT1_STATIC;
	अगर (port_map)
		dat1 |= LAN9303_ALR_DAT1_VALID;
	/* otherwise no ports: delete entry */
	अगर (stp_override)
		dat1 |= LAN9303_ALR_DAT1_AGE_OVERRID;

	alr_port = porपंचांगap_2_alrport[port_map & 7];
	dat1 &= ~LAN9303_ALR_DAT1_PORT_MASK;
	dat1 |= alr_port << LAN9303_ALR_DAT1_PORT_BITOFFS;

	dat0 = 0;
	dat0 |= (mac[0] << 0);
	dat0 |= (mac[1] << 8);
	dat0 |= (mac[2] << 16);
	dat0 |= (mac[3] << 24);

	dat1 |= (mac[4] << 0);
	dat1 |= (mac[5] << 8);

	lan9303_alr_make_entry_raw(chip, dat0, dat1);
पूर्ण

/* Add port to अटल ALR entry, create new अटल entry अगर needed */
अटल पूर्णांक lan9303_alr_add_port(काष्ठा lan9303 *chip, स्थिर u8 *mac, पूर्णांक port,
				bool stp_override)
अणु
	काष्ठा lan9303_alr_cache_entry *entr;

	mutex_lock(&chip->alr_mutex);
	entr = lan9303_alr_cache_find_mac(chip, mac);
	अगर (!entr) अणु /*New entry */
		entr = lan9303_alr_cache_find_मुक्त(chip);
		अगर (!entr) अणु
			mutex_unlock(&chip->alr_mutex);
			वापस -ENOSPC;
		पूर्ण
		ether_addr_copy(entr->mac_addr, mac);
	पूर्ण
	entr->port_map |= BIT(port);
	entr->stp_override = stp_override;
	lan9303_alr_set_entry(chip, mac, entr->port_map, stp_override);
	mutex_unlock(&chip->alr_mutex);

	वापस 0;
पूर्ण

/* Delete अटल port from ALR entry, delete entry अगर last port */
अटल पूर्णांक lan9303_alr_del_port(काष्ठा lan9303 *chip, स्थिर u8 *mac, पूर्णांक port)
अणु
	काष्ठा lan9303_alr_cache_entry *entr;

	mutex_lock(&chip->alr_mutex);
	entr = lan9303_alr_cache_find_mac(chip, mac);
	अगर (!entr)
		जाओ out;  /* no अटल entry found */

	entr->port_map &= ~BIT(port);
	अगर (entr->port_map == 0) /* zero means its मुक्त again */
		eth_zero_addr(entr->mac_addr);
	lan9303_alr_set_entry(chip, mac, entr->port_map, entr->stp_override);

out:
	mutex_unlock(&chip->alr_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक lan9303_disable_processing_port(काष्ठा lan9303 *chip,
					   अचिन्हित पूर्णांक port)
अणु
	पूर्णांक ret;

	/* disable RX, but keep रेजिस्टर reset शेष values अन्यथा */
	ret = lan9303_ग_लिखो_चयन_port(chip, port, LAN9303_MAC_RX_CFG_0,
					LAN9303_MAC_RX_CFG_X_REJECT_MAC_TYPES);
	अगर (ret)
		वापस ret;

	/* disable TX, but keep रेजिस्टर reset शेष values अन्यथा */
	वापस lan9303_ग_लिखो_चयन_port(chip, port, LAN9303_MAC_TX_CFG_0,
				LAN9303_MAC_TX_CFG_X_TX_IFG_CONFIG_DEFAULT |
				LAN9303_MAC_TX_CFG_X_TX_PAD_ENABLE);
पूर्ण

अटल पूर्णांक lan9303_enable_processing_port(काष्ठा lan9303 *chip,
					  अचिन्हित पूर्णांक port)
अणु
	पूर्णांक ret;

	/* enable RX and keep रेजिस्टर reset शेष values अन्यथा */
	ret = lan9303_ग_लिखो_चयन_port(chip, port, LAN9303_MAC_RX_CFG_0,
					LAN9303_MAC_RX_CFG_X_REJECT_MAC_TYPES |
					LAN9303_MAC_RX_CFG_X_RX_ENABLE);
	अगर (ret)
		वापस ret;

	/* enable TX and keep रेजिस्टर reset शेष values अन्यथा */
	वापस lan9303_ग_लिखो_चयन_port(chip, port, LAN9303_MAC_TX_CFG_0,
				LAN9303_MAC_TX_CFG_X_TX_IFG_CONFIG_DEFAULT |
				LAN9303_MAC_TX_CFG_X_TX_PAD_ENABLE |
				LAN9303_MAC_TX_CFG_X_TX_ENABLE);
पूर्ण

/* क्रमward special tagged packets from port 0 to port 1 *or* port 2 */
अटल पूर्णांक lan9303_setup_tagging(काष्ठा lan9303 *chip)
अणु
	पूर्णांक ret;
	u32 val;
	/* enable defining the destination port via special VLAN tagging
	 * क्रम port 0
	 */
	ret = lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_INGRESS_PORT_TYPE,
				       LAN9303_SWE_INGRESS_PORT_TYPE_VLAN);
	अगर (ret)
		वापस ret;

	/* tag incoming packets at port 1 and 2 on their way to port 0 to be
	 * able to discover their source port
	 */
	val = LAN9303_BM_EGRSS_PORT_TYPE_SPECIAL_TAG_PORT0;
	वापस lan9303_ग_लिखो_चयन_reg(chip, LAN9303_BM_EGRSS_PORT_TYPE, val);
पूर्ण

/* We want a special working चयन:
 * - करो not क्रमward packets between port 1 and 2
 * - क्रमward everything from port 1 to port 0
 * - क्रमward everything from port 2 to port 0
 */
अटल पूर्णांक lan9303_separate_ports(काष्ठा lan9303 *chip)
अणु
	पूर्णांक ret;

	lan9303_alr_del_port(chip, eth_stp_addr, 0);
	ret = lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_PORT_MIRROR,
				LAN9303_SWE_PORT_MIRROR_SNIFFER_PORT0 |
				LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT1 |
				LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT2 |
				LAN9303_SWE_PORT_MIRROR_ENABLE_RX_MIRRORING |
				LAN9303_SWE_PORT_MIRROR_SNIFF_ALL);
	अगर (ret)
		वापस ret;

	/* prevent port 1 and 2 from क्रमwarding packets by their own */
	वापस lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_PORT_STATE,
				LAN9303_SWE_PORT_STATE_FORWARDING_PORT0 |
				LAN9303_SWE_PORT_STATE_BLOCKING_PORT1 |
				LAN9303_SWE_PORT_STATE_BLOCKING_PORT2);
पूर्ण

अटल व्योम lan9303_bridge_ports(काष्ठा lan9303 *chip)
अणु
	/* ports bridged: हटाओ mirroring */
	lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_PORT_MIRROR,
				 LAN9303_SWE_PORT_MIRROR_DISABLED);

	lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_PORT_STATE,
				 chip->swe_port_state);
	lan9303_alr_add_port(chip, eth_stp_addr, 0, true);
पूर्ण

अटल व्योम lan9303_handle_reset(काष्ठा lan9303 *chip)
अणु
	अगर (!chip->reset_gpio)
		वापस;

	अगर (chip->reset_duration != 0)
		msleep(chip->reset_duration);

	/* release (deनिश्चित) reset and activate the device */
	gpiod_set_value_cansleep(chip->reset_gpio, 0);
पूर्ण

/* stop processing packets क्रम all ports */
अटल पूर्णांक lan9303_disable_processing(काष्ठा lan9303 *chip)
अणु
	पूर्णांक p;

	क्रम (p = 1; p < LAN9303_NUM_PORTS; p++) अणु
		पूर्णांक ret = lan9303_disable_processing_port(chip, p);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan9303_check_device(काष्ठा lan9303 *chip)
अणु
	पूर्णांक ret;
	u32 reg;

	ret = lan9303_पढ़ो(chip->regmap, LAN9303_CHIP_REV, &reg);
	अगर (ret) अणु
		dev_err(chip->dev, "failed to read chip revision register: %d\n",
			ret);
		अगर (!chip->reset_gpio) अणु
			dev_dbg(chip->dev,
				"hint: maybe failed due to missing reset GPIO\n");
		पूर्ण
		वापस ret;
	पूर्ण

	अगर ((reg >> 16) != LAN9303_CHIP_ID) अणु
		dev_err(chip->dev, "expecting LAN9303 chip, but found: %X\n",
			reg >> 16);
		वापस -ENODEV;
	पूर्ण

	/* The शेष state of the LAN9303 device is to क्रमward packets between
	 * all ports (अगर not configured dअगरferently by an बाह्यal EEPROM).
	 * The initial state of a DSA device must be क्रमwarding packets only
	 * between the बाह्यal and the पूर्णांकernal ports and no क्रमwarding
	 * between the बाह्यal ports. In preparation we stop packet handling
	 * at all क्रम now until the LAN9303 device is re-programmed accordingly.
	 */
	ret = lan9303_disable_processing(chip);
	अगर (ret)
		dev_warn(chip->dev, "failed to disable switching %d\n", ret);

	dev_info(chip->dev, "Found LAN9303 rev. %u\n", reg & 0xffff);

	ret = lan9303_detect_phy_setup(chip);
	अगर (ret) अणु
		dev_err(chip->dev,
			"failed to discover phy bootstrap setup: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* ---------------------------- DSA -----------------------------------*/

अटल क्रमागत dsa_tag_protocol lan9303_get_tag_protocol(काष्ठा dsa_चयन *ds,
						      पूर्णांक port,
						      क्रमागत dsa_tag_protocol mp)
अणु
	वापस DSA_TAG_PROTO_LAN9303;
पूर्ण

अटल पूर्णांक lan9303_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा lan9303 *chip = ds->priv;
	पूर्णांक ret;

	/* Make sure that port 0 is the cpu port */
	अगर (!dsa_is_cpu_port(ds, 0)) अणु
		dev_err(chip->dev, "port 0 is not the CPU port\n");
		वापस -EINVAL;
	पूर्ण

	ret = lan9303_setup_tagging(chip);
	अगर (ret)
		dev_err(chip->dev, "failed to setup port tagging %d\n", ret);

	ret = lan9303_separate_ports(chip);
	अगर (ret)
		dev_err(chip->dev, "failed to separate ports %d\n", ret);

	ret = lan9303_enable_processing_port(chip, 0);
	अगर (ret)
		dev_err(chip->dev, "failed to re-enable switching %d\n", ret);

	/* Trap IGMP to port 0 */
	ret = lan9303_ग_लिखो_चयन_reg_mask(chip, LAN9303_SWE_GLB_INGRESS_CFG,
					    LAN9303_SWE_GLB_INGR_IGMP_TRAP |
					    LAN9303_SWE_GLB_INGR_IGMP_PORT(0),
					    LAN9303_SWE_GLB_INGR_IGMP_PORT(1) |
					    LAN9303_SWE_GLB_INGR_IGMP_PORT(2));
	अगर (ret)
		dev_err(chip->dev, "failed to setup IGMP trap %d\n", ret);

	वापस 0;
पूर्ण

काष्ठा lan9303_mib_desc अणु
	अचिन्हित पूर्णांक offset; /* offset of first MAC */
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा lan9303_mib_desc lan9303_mib[] = अणु
	अणु .offset = LAN9303_MAC_RX_BRDCST_CNT_0, .name = "RxBroad", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_PAUSE_CNT_0, .name = "RxPause", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_MULCST_CNT_0, .name = "RxMulti", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_PKTOK_CNT_0, .name = "RxOk", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_CRCERR_CNT_0, .name = "RxCrcErr", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_ALIGN_CNT_0, .name = "RxAlignErr", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_JABB_CNT_0, .name = "RxJabber", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_FRAG_CNT_0, .name = "RxFragment", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_64_CNT_0, .name = "Rx64Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_127_CNT_0, .name = "Rx128Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_255_CNT_0, .name = "Rx256Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_511_CNT_0, .name = "Rx512Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_1023_CNT_0, .name = "Rx1024Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_MAX_CNT_0, .name = "RxMaxByte", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_PKTLEN_CNT_0, .name = "RxByteCnt", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_SYMBL_CNT_0, .name = "RxSymbolCnt", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_CTLFRM_CNT_0, .name = "RxCfs", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_OVRSZE_CNT_0, .name = "RxOverFlow", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_UNDSZE_CNT_0, .name = "TxShort", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_BRDCST_CNT_0, .name = "TxBroad", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_PAUSE_CNT_0, .name = "TxPause", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_MULCST_CNT_0, .name = "TxMulti", पूर्ण,
	अणु .offset = LAN9303_MAC_RX_UNDSZE_CNT_0, .name = "TxUnderRun", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_64_CNT_0, .name = "Tx64Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_127_CNT_0, .name = "Tx128Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_255_CNT_0, .name = "Tx256Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_511_CNT_0, .name = "Tx512Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_1023_CNT_0, .name = "Tx1024Byte", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_MAX_CNT_0, .name = "TxMaxByte", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_PKTLEN_CNT_0, .name = "TxByteCnt", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_PKTOK_CNT_0, .name = "TxOk", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_TOTALCOL_CNT_0, .name = "TxCollision", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_MULTICOL_CNT_0, .name = "TxMultiCol", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_SNGLECOL_CNT_0, .name = "TxSingleCol", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_EXCOL_CNT_0, .name = "TxExcCol", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_DEFER_CNT_0, .name = "TxDefer", पूर्ण,
	अणु .offset = LAN9303_MAC_TX_LATECOL_0, .name = "TxLateCol", पूर्ण,
पूर्ण;

अटल व्योम lan9303_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
				u32 stringset, uपूर्णांक8_t *data)
अणु
	अचिन्हित पूर्णांक u;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (u = 0; u < ARRAY_SIZE(lan9303_mib); u++) अणु
		म_नकलन(data + u * ETH_GSTRING_LEN, lan9303_mib[u].name,
			ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल व्योम lan9303_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      uपूर्णांक64_t *data)
अणु
	काष्ठा lan9303 *chip = ds->priv;
	अचिन्हित पूर्णांक u;

	क्रम (u = 0; u < ARRAY_SIZE(lan9303_mib); u++) अणु
		u32 reg;
		पूर्णांक ret;

		ret = lan9303_पढ़ो_चयन_port(
			chip, port, lan9303_mib[u].offset, &reg);

		अगर (ret)
			dev_warn(chip->dev, "Reading status port %d reg %u failed\n",
				 port, lan9303_mib[u].offset);
		data[u] = reg;
	पूर्ण
पूर्ण

अटल पूर्णांक lan9303_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS)
		वापस 0;

	वापस ARRAY_SIZE(lan9303_mib);
पूर्ण

अटल पूर्णांक lan9303_phy_पढ़ो(काष्ठा dsa_चयन *ds, पूर्णांक phy, पूर्णांक regnum)
अणु
	काष्ठा lan9303 *chip = ds->priv;
	पूर्णांक phy_base = chip->phy_addr_base;

	अगर (phy == phy_base)
		वापस lan9303_virt_phy_reg_पढ़ो(chip, regnum);
	अगर (phy > phy_base + 2)
		वापस -ENODEV;

	वापस chip->ops->phy_पढ़ो(chip, phy, regnum);
पूर्ण

अटल पूर्णांक lan9303_phy_ग_लिखो(काष्ठा dsa_चयन *ds, पूर्णांक phy, पूर्णांक regnum,
			     u16 val)
अणु
	काष्ठा lan9303 *chip = ds->priv;
	पूर्णांक phy_base = chip->phy_addr_base;

	अगर (phy == phy_base)
		वापस lan9303_virt_phy_reg_ग_लिखो(chip, regnum, val);
	अगर (phy > phy_base + 2)
		वापस -ENODEV;

	वापस chip->ops->phy_ग_लिखो(chip, phy, regnum, val);
पूर्ण

अटल व्योम lan9303_adjust_link(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा phy_device *phydev)
अणु
	काष्ठा lan9303 *chip = ds->priv;
	पूर्णांक ctl;

	अगर (!phy_is_pseuकरो_fixed_link(phydev))
		वापस;

	ctl = lan9303_phy_पढ़ो(ds, port, MII_BMCR);

	ctl &= ~BMCR_ANENABLE;

	अगर (phydev->speed == SPEED_100)
		ctl |= BMCR_SPEED100;
	अन्यथा अगर (phydev->speed == SPEED_10)
		ctl &= ~BMCR_SPEED100;
	अन्यथा
		dev_err(ds->dev, "unsupported speed: %d\n", phydev->speed);

	अगर (phydev->duplex == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;
	अन्यथा
		ctl &= ~BMCR_FULLDPLX;

	lan9303_phy_ग_लिखो(ds, port, MII_BMCR, ctl);

	अगर (port == chip->phy_addr_base) अणु
		/* Virtual Phy: Remove Turbo 200Mbit mode */
		lan9303_पढ़ो(chip->regmap, LAN9303_VIRT_SPECIAL_CTRL, &ctl);

		ctl &= ~LAN9303_VIRT_SPECIAL_TURBO;
		regmap_ग_लिखो(chip->regmap, LAN9303_VIRT_SPECIAL_CTRL, ctl);
	पूर्ण
पूर्ण

अटल पूर्णांक lan9303_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा phy_device *phy)
अणु
	काष्ठा lan9303 *chip = ds->priv;

	अगर (!dsa_is_user_port(ds, port))
		वापस 0;

	वापस lan9303_enable_processing_port(chip, port);
पूर्ण

अटल व्योम lan9303_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा lan9303 *chip = ds->priv;

	अगर (!dsa_is_user_port(ds, port))
		वापस;

	lan9303_disable_processing_port(chip, port);
	lan9303_phy_ग_लिखो(ds, chip->phy_addr_base + port, MII_BMCR, BMCR_PDOWN);
पूर्ण

अटल पूर्णांक lan9303_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा net_device *br)
अणु
	काष्ठा lan9303 *chip = ds->priv;

	dev_dbg(chip->dev, "%s(port %d)\n", __func__, port);
	अगर (dsa_to_port(ds, 1)->bridge_dev == dsa_to_port(ds, 2)->bridge_dev) अणु
		lan9303_bridge_ports(chip);
		chip->is_bridged = true;  /* unleash stp_state_set() */
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lan9303_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      काष्ठा net_device *br)
अणु
	काष्ठा lan9303 *chip = ds->priv;

	dev_dbg(chip->dev, "%s(port %d)\n", __func__, port);
	अगर (chip->is_bridged) अणु
		lan9303_separate_ports(chip);
		chip->is_bridged = false;
	पूर्ण
पूर्ण

अटल व्योम lan9303_port_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       u8 state)
अणु
	पूर्णांक porपंचांगask, portstate;
	काष्ठा lan9303 *chip = ds->priv;

	dev_dbg(chip->dev, "%s(port %d, state %d)\n",
		__func__, port, state);

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		portstate = LAN9303_SWE_PORT_STATE_DISABLED_PORT0;
		अवरोध;
	हाल BR_STATE_BLOCKING:
	हाल BR_STATE_LISTENING:
		portstate = LAN9303_SWE_PORT_STATE_BLOCKING_PORT0;
		अवरोध;
	हाल BR_STATE_LEARNING:
		portstate = LAN9303_SWE_PORT_STATE_LEARNING_PORT0;
		अवरोध;
	हाल BR_STATE_FORWARDING:
		portstate = LAN9303_SWE_PORT_STATE_FORWARDING_PORT0;
		अवरोध;
	शेष:
		portstate = LAN9303_SWE_PORT_STATE_DISABLED_PORT0;
		dev_err(chip->dev, "unknown stp state: port %d, state %d\n",
			port, state);
	पूर्ण

	porपंचांगask = 0x3 << (port * 2);
	portstate <<= (port * 2);

	chip->swe_port_state = (chip->swe_port_state & ~porपंचांगask) | portstate;

	अगर (chip->is_bridged)
		lan9303_ग_लिखो_चयन_reg(chip, LAN9303_SWE_PORT_STATE,
					 chip->swe_port_state);
	/* अन्यथा: touching SWE_PORT_STATE would अवरोध port separation */
पूर्ण

अटल व्योम lan9303_port_fast_age(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा lan9303 *chip = ds->priv;
	काष्ठा del_port_learned_ctx del_ctx = अणु
		.port = port,
	पूर्ण;

	dev_dbg(chip->dev, "%s(%d)\n", __func__, port);
	lan9303_alr_loop(chip, alr_loop_cb_del_port_learned, &del_ctx);
पूर्ण

अटल पूर्णांक lan9303_port_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा lan9303 *chip = ds->priv;

	dev_dbg(chip->dev, "%s(%d, %pM, %d)\n", __func__, port, addr, vid);
	अगर (vid)
		वापस -EOPNOTSUPP;

	वापस lan9303_alr_add_port(chip, addr, port, false);
पूर्ण

अटल पूर्णांक lan9303_port_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर अचिन्हित अक्षर *addr, u16 vid)

अणु
	काष्ठा lan9303 *chip = ds->priv;

	dev_dbg(chip->dev, "%s(%d, %pM, %d)\n", __func__, port, addr, vid);
	अगर (vid)
		वापस -EOPNOTSUPP;
	lan9303_alr_del_port(chip, addr, port);

	वापस 0;
पूर्ण

अटल पूर्णांक lan9303_port_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा lan9303 *chip = ds->priv;
	काष्ठा port_fdb_dump_ctx dump_ctx = अणु
		.port = port,
		.data = data,
		.cb   = cb,
	पूर्ण;

	dev_dbg(chip->dev, "%s(%d)\n", __func__, port);
	lan9303_alr_loop(chip, alr_loop_cb_fdb_port_dump, &dump_ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक lan9303_port_mdb_prepare(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा lan9303 *chip = ds->priv;

	dev_dbg(chip->dev, "%s(%d, %pM, %d)\n", __func__, port, mdb->addr,
		mdb->vid);
	अगर (mdb->vid)
		वापस -EOPNOTSUPP;
	अगर (lan9303_alr_cache_find_mac(chip, mdb->addr))
		वापस 0;
	अगर (!lan9303_alr_cache_find_मुक्त(chip))
		वापस -ENOSPC;

	वापस 0;
पूर्ण

अटल पूर्णांक lan9303_port_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा lan9303 *chip = ds->priv;
	पूर्णांक err;

	err = lan9303_port_mdb_prepare(ds, port, mdb);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "%s(%d, %pM, %d)\n", __func__, port, mdb->addr,
		mdb->vid);
	वापस lan9303_alr_add_port(chip, mdb->addr, port, false);
पूर्ण

अटल पूर्णांक lan9303_port_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा lan9303 *chip = ds->priv;

	dev_dbg(chip->dev, "%s(%d, %pM, %d)\n", __func__, port, mdb->addr,
		mdb->vid);
	अगर (mdb->vid)
		वापस -EOPNOTSUPP;
	lan9303_alr_del_port(chip, mdb->addr, port);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops lan9303_चयन_ops = अणु
	.get_tag_protocol = lan9303_get_tag_protocol,
	.setup = lan9303_setup,
	.get_strings = lan9303_get_strings,
	.phy_पढ़ो = lan9303_phy_पढ़ो,
	.phy_ग_लिखो = lan9303_phy_ग_लिखो,
	.adjust_link = lan9303_adjust_link,
	.get_ethtool_stats = lan9303_get_ethtool_stats,
	.get_sset_count = lan9303_get_sset_count,
	.port_enable = lan9303_port_enable,
	.port_disable = lan9303_port_disable,
	.port_bridge_join       = lan9303_port_bridge_join,
	.port_bridge_leave      = lan9303_port_bridge_leave,
	.port_stp_state_set     = lan9303_port_stp_state_set,
	.port_fast_age          = lan9303_port_fast_age,
	.port_fdb_add           = lan9303_port_fdb_add,
	.port_fdb_del           = lan9303_port_fdb_del,
	.port_fdb_dump          = lan9303_port_fdb_dump,
	.port_mdb_add           = lan9303_port_mdb_add,
	.port_mdb_del           = lan9303_port_mdb_del,
पूर्ण;

अटल पूर्णांक lan9303_रेजिस्टर_चयन(काष्ठा lan9303 *chip)
अणु
	पूर्णांक base;

	chip->ds = devm_kzalloc(chip->dev, माप(*chip->ds), GFP_KERNEL);
	अगर (!chip->ds)
		वापस -ENOMEM;

	chip->ds->dev = chip->dev;
	chip->ds->num_ports = LAN9303_NUM_PORTS;
	chip->ds->priv = chip;
	chip->ds->ops = &lan9303_चयन_ops;
	base = chip->phy_addr_base;
	chip->ds->phys_mii_mask = GENMASK(LAN9303_NUM_PORTS - 1 + base, base);

	वापस dsa_रेजिस्टर_चयन(chip->ds);
पूर्ण

अटल पूर्णांक lan9303_probe_reset_gpio(काष्ठा lan9303 *chip,
				     काष्ठा device_node *np)
अणु
	chip->reset_gpio = devm_gpiod_get_optional(chip->dev, "reset",
						   GPIOD_OUT_LOW);
	अगर (IS_ERR(chip->reset_gpio))
		वापस PTR_ERR(chip->reset_gpio);

	अगर (!chip->reset_gpio) अणु
		dev_dbg(chip->dev, "No reset GPIO defined\n");
		वापस 0;
	पूर्ण

	chip->reset_duration = 200;

	अगर (np) अणु
		of_property_पढ़ो_u32(np, "reset-duration",
				     &chip->reset_duration);
	पूर्ण अन्यथा अणु
		dev_dbg(chip->dev, "reset duration defaults to 200 ms\n");
	पूर्ण

	/* A sane reset duration should not be दीर्घer than 1s */
	अगर (chip->reset_duration > 1000)
		chip->reset_duration = 1000;

	वापस 0;
पूर्ण

पूर्णांक lan9303_probe(काष्ठा lan9303 *chip, काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	mutex_init(&chip->indirect_mutex);
	mutex_init(&chip->alr_mutex);

	ret = lan9303_probe_reset_gpio(chip, np);
	अगर (ret)
		वापस ret;

	lan9303_handle_reset(chip);

	ret = lan9303_check_device(chip);
	अगर (ret)
		वापस ret;

	ret = lan9303_रेजिस्टर_चयन(chip);
	अगर (ret) अणु
		dev_dbg(chip->dev, "Failed to register switch: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(lan9303_probe);

पूर्णांक lan9303_हटाओ(काष्ठा lan9303 *chip)
अणु
	पूर्णांक rc;

	rc = lan9303_disable_processing(chip);
	अगर (rc != 0)
		dev_warn(chip->dev, "shutting down failed\n");

	dsa_unरेजिस्टर_चयन(chip->ds);

	/* निश्चित reset to the whole device to prevent it from करोing anything */
	gpiod_set_value_cansleep(chip->reset_gpio, 1);
	gpiod_unexport(chip->reset_gpio);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(lan9303_हटाओ);

MODULE_AUTHOR("Juergen Borleis <kernel@pengutronix.de>");
MODULE_DESCRIPTION("Core driver for SMSC/Microchip LAN9303 three port ethernet switch");
MODULE_LICENSE("GPL v2");
