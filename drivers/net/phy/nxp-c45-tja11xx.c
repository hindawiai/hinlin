<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* NXP C45 PHY driver
 * Copyright (C) 2021 NXP
 * Author: Radu Pirea <radu-nicolae.pirea@oss.nxp.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/processor.h>
#समावेश <linux/property.h>

#घोषणा PHY_ID_TJA_1103			0x001BB010

#घोषणा PMAPMD_B100T1_PMAPMD_CTL	0x0834
#घोषणा B100T1_PMAPMD_CONFIG_EN		BIT(15)
#घोषणा B100T1_PMAPMD_MASTER		BIT(14)
#घोषणा MASTER_MODE			(B100T1_PMAPMD_CONFIG_EN | \
					 B100T1_PMAPMD_MASTER)
#घोषणा SLAVE_MODE			(B100T1_PMAPMD_CONFIG_EN)

#घोषणा VEND1_DEVICE_CONTROL		0x0040
#घोषणा DEVICE_CONTROL_RESET		BIT(15)
#घोषणा DEVICE_CONTROL_CONFIG_GLOBAL_EN	BIT(14)
#घोषणा DEVICE_CONTROL_CONFIG_ALL_EN	BIT(13)

#घोषणा VEND1_PHY_IRQ_ACK		0x80A0
#घोषणा VEND1_PHY_IRQ_EN		0x80A1
#घोषणा VEND1_PHY_IRQ_STATUS		0x80A2
#घोषणा PHY_IRQ_LINK_EVENT		BIT(1)

#घोषणा VEND1_PHY_CONTROL		0x8100
#घोषणा PHY_CONFIG_EN			BIT(14)
#घोषणा PHY_START_OP			BIT(0)

#घोषणा VEND1_PHY_CONFIG		0x8108
#घोषणा PHY_CONFIG_AUTO			BIT(0)

#घोषणा VEND1_SIGNAL_QUALITY		0x8320
#घोषणा SQI_VALID			BIT(14)
#घोषणा SQI_MASK			GENMASK(2, 0)
#घोषणा MAX_SQI				SQI_MASK

#घोषणा VEND1_CABLE_TEST		0x8330
#घोषणा CABLE_TEST_ENABLE		BIT(15)
#घोषणा CABLE_TEST_START		BIT(14)
#घोषणा CABLE_TEST_VALID		BIT(13)
#घोषणा CABLE_TEST_OK			0x00
#घोषणा CABLE_TEST_SHORTED		0x01
#घोषणा CABLE_TEST_OPEN			0x02
#घोषणा CABLE_TEST_UNKNOWN		0x07

#घोषणा VEND1_PORT_CONTROL		0x8040
#घोषणा PORT_CONTROL_EN			BIT(14)

#घोषणा VEND1_PORT_INFRA_CONTROL	0xAC00
#घोषणा PORT_INFRA_CONTROL_EN		BIT(14)

#घोषणा VEND1_RXID			0xAFCC
#घोषणा VEND1_TXID			0xAFCD
#घोषणा ID_ENABLE			BIT(15)

#घोषणा VEND1_ABILITIES			0xAFC4
#घोषणा RGMII_ID_ABILITY		BIT(15)
#घोषणा RGMII_ABILITY			BIT(14)
#घोषणा RMII_ABILITY			BIT(10)
#घोषणा REVMII_ABILITY			BIT(9)
#घोषणा MII_ABILITY			BIT(8)
#घोषणा SGMII_ABILITY			BIT(0)

#घोषणा VEND1_MII_BASIC_CONFIG		0xAFC6
#घोषणा MII_BASIC_CONFIG_REV		BIT(8)
#घोषणा MII_BASIC_CONFIG_SGMII		0x9
#घोषणा MII_BASIC_CONFIG_RGMII		0x7
#घोषणा MII_BASIC_CONFIG_RMII		0x5
#घोषणा MII_BASIC_CONFIG_MII		0x4

#घोषणा VEND1_SYMBOL_ERROR_COUNTER	0x8350
#घोषणा VEND1_LINK_DROP_COUNTER		0x8352
#घोषणा VEND1_LINK_LOSSES_AND_FAILURES	0x8353
#घोषणा VEND1_R_GOOD_FRAME_CNT		0xA950
#घोषणा VEND1_R_BAD_FRAME_CNT		0xA952
#घोषणा VEND1_R_RXER_FRAME_CNT		0xA954
#घोषणा VEND1_RX_PREAMBLE_COUNT		0xAFCE
#घोषणा VEND1_TX_PREAMBLE_COUNT		0xAFCF
#घोषणा VEND1_RX_IPG_LENGTH		0xAFD0
#घोषणा VEND1_TX_IPG_LENGTH		0xAFD1
#घोषणा COUNTER_EN			BIT(15)

#घोषणा RGMII_PERIOD_PS			8000U
#घोषणा PS_PER_DEGREE			भाग_u64(RGMII_PERIOD_PS, 360)
#घोषणा MIN_ID_PS			1644U
#घोषणा MAX_ID_PS			2260U
#घोषणा DEFAULT_ID_PS			2000U

काष्ठा nxp_c45_phy अणु
	u32 tx_delay;
	u32 rx_delay;
पूर्ण;

काष्ठा nxp_c45_phy_stats अणु
	स्थिर अक्षर	*name;
	u8		mmd;
	u16		reg;
	u8		off;
	u16		mask;
पूर्ण;

अटल स्थिर काष्ठा nxp_c45_phy_stats nxp_c45_hw_stats[] = अणु
	अणु "phy_symbol_error_cnt", MDIO_MMD_VEND1,
		VEND1_SYMBOL_ERROR_COUNTER, 0, GENMASK(15, 0) पूर्ण,
	अणु "phy_link_status_drop_cnt", MDIO_MMD_VEND1,
		VEND1_LINK_DROP_COUNTER, 8, GENMASK(13, 8) पूर्ण,
	अणु "phy_link_availability_drop_cnt", MDIO_MMD_VEND1,
		VEND1_LINK_DROP_COUNTER, 0, GENMASK(5, 0) पूर्ण,
	अणु "phy_link_loss_cnt", MDIO_MMD_VEND1,
		VEND1_LINK_LOSSES_AND_FAILURES, 10, GENMASK(15, 10) पूर्ण,
	अणु "phy_link_failure_cnt", MDIO_MMD_VEND1,
		VEND1_LINK_LOSSES_AND_FAILURES, 0, GENMASK(9, 0) पूर्ण,
	अणु "r_good_frame_cnt", MDIO_MMD_VEND1,
		VEND1_R_GOOD_FRAME_CNT, 0, GENMASK(15, 0) पूर्ण,
	अणु "r_bad_frame_cnt", MDIO_MMD_VEND1,
		VEND1_R_BAD_FRAME_CNT, 0, GENMASK(15, 0) पूर्ण,
	अणु "r_rxer_frame_cnt", MDIO_MMD_VEND1,
		VEND1_R_RXER_FRAME_CNT, 0, GENMASK(15, 0) पूर्ण,
	अणु "rx_preamble_count", MDIO_MMD_VEND1,
		VEND1_RX_PREAMBLE_COUNT, 0, GENMASK(5, 0) पूर्ण,
	अणु "tx_preamble_count", MDIO_MMD_VEND1,
		VEND1_TX_PREAMBLE_COUNT, 0, GENMASK(5, 0) पूर्ण,
	अणु "rx_ipg_length", MDIO_MMD_VEND1,
		VEND1_RX_IPG_LENGTH, 0, GENMASK(8, 0) पूर्ण,
	अणु "tx_ipg_length", MDIO_MMD_VEND1,
		VEND1_TX_IPG_LENGTH, 0, GENMASK(8, 0) पूर्ण,
पूर्ण;

अटल पूर्णांक nxp_c45_get_sset_count(काष्ठा phy_device *phydev)
अणु
	वापस ARRAY_SIZE(nxp_c45_hw_stats);
पूर्ण

अटल व्योम nxp_c45_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(nxp_c45_hw_stats); i++) अणु
		म_नकलन(data + i * ETH_GSTRING_LEN,
			nxp_c45_hw_stats[i].name, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल व्योम nxp_c45_get_stats(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	माप_प्रकार i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(nxp_c45_hw_stats); i++) अणु
		ret = phy_पढ़ो_mmd(phydev, nxp_c45_hw_stats[i].mmd,
				   nxp_c45_hw_stats[i].reg);
		अगर (ret < 0) अणु
			data[i] = U64_MAX;
		पूर्ण अन्यथा अणु
			data[i] = ret & nxp_c45_hw_stats[i].mask;
			data[i] >>= nxp_c45_hw_stats[i].off;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक nxp_c45_config_enable(काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_DEVICE_CONTROL,
		      DEVICE_CONTROL_CONFIG_GLOBAL_EN |
		      DEVICE_CONTROL_CONFIG_ALL_EN);
	usleep_range(400, 450);

	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_PORT_CONTROL,
		      PORT_CONTROL_EN);
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_CONTROL,
		      PHY_CONFIG_EN);
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_PORT_INFRA_CONTROL,
		      PORT_INFRA_CONTROL_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_c45_start_op(काष्ठा phy_device *phydev)
अणु
	वापस phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_CONTROL,
				PHY_START_OP);
पूर्ण

अटल पूर्णांक nxp_c45_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED)
		वापस phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
					VEND1_PHY_IRQ_EN, PHY_IRQ_LINK_EVENT);
	अन्यथा
		वापस phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1,
					  VEND1_PHY_IRQ_EN, PHY_IRQ_LINK_EVENT);
पूर्ण

अटल irqवापस_t nxp_c45_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक irq;

	irq = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_IRQ_STATUS);
	अगर (irq & PHY_IRQ_LINK_EVENT) अणु
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_IRQ_ACK,
			      PHY_IRQ_LINK_EVENT);
		phy_trigger_machine(phydev);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nxp_c45_soft_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_DEVICE_CONTROL,
			    DEVICE_CONTROL_RESET);
	अगर (ret)
		वापस ret;

	वापस phy_पढ़ो_mmd_poll_समयout(phydev, MDIO_MMD_VEND1,
					 VEND1_DEVICE_CONTROL, ret,
					 !(ret & DEVICE_CONTROL_RESET), 20000,
					 240000, false);
पूर्ण

अटल पूर्णांक nxp_c45_cable_test_start(काष्ठा phy_device *phydev)
अणु
	वापस phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_CABLE_TEST,
			     CABLE_TEST_ENABLE | CABLE_TEST_START);
पूर्ण

अटल पूर्णांक nxp_c45_cable_test_get_status(काष्ठा phy_device *phydev,
					 bool *finished)
अणु
	पूर्णांक ret;
	u8 cable_test_result;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, VEND1_CABLE_TEST);
	अगर (!(ret & CABLE_TEST_VALID)) अणु
		*finished = false;
		वापस 0;
	पूर्ण

	*finished = true;
	cable_test_result = ret & GENMASK(2, 0);

	चयन (cable_test_result) अणु
	हाल CABLE_TEST_OK:
		ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_A,
					ETHTOOL_A_CABLE_RESULT_CODE_OK);
		अवरोध;
	हाल CABLE_TEST_SHORTED:
		ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_A,
					ETHTOOL_A_CABLE_RESULT_CODE_SAME_SHORT);
		अवरोध;
	हाल CABLE_TEST_OPEN:
		ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_A,
					ETHTOOL_A_CABLE_RESULT_CODE_OPEN);
		अवरोध;
	शेष:
		ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_A,
					ETHTOOL_A_CABLE_RESULT_CODE_UNSPEC);
	पूर्ण

	phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_CABLE_TEST,
			   CABLE_TEST_ENABLE);

	वापस nxp_c45_start_op(phydev);
पूर्ण

अटल पूर्णांक nxp_c45_setup_master_slave(काष्ठा phy_device *phydev)
अणु
	चयन (phydev->master_slave_set) अणु
	हाल MASTER_SLAVE_CFG_MASTER_FORCE:
	हाल MASTER_SLAVE_CFG_MASTER_PREFERRED:
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_PMAPMD, PMAPMD_B100T1_PMAPMD_CTL,
			      MASTER_MODE);
		अवरोध;
	हाल MASTER_SLAVE_CFG_SLAVE_PREFERRED:
	हाल MASTER_SLAVE_CFG_SLAVE_FORCE:
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_PMAPMD, PMAPMD_B100T1_PMAPMD_CTL,
			      SLAVE_MODE);
		अवरोध;
	हाल MASTER_SLAVE_CFG_UNKNOWN:
	हाल MASTER_SLAVE_CFG_UNSUPPORTED:
		वापस 0;
	शेष:
		phydev_warn(phydev, "Unsupported Master/Slave mode\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_c45_पढ़ो_master_slave(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	phydev->master_slave_get = MASTER_SLAVE_CFG_UNKNOWN;
	phydev->master_slave_state = MASTER_SLAVE_STATE_UNKNOWN;

	reg = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, PMAPMD_B100T1_PMAPMD_CTL);
	अगर (reg < 0)
		वापस reg;

	अगर (reg & B100T1_PMAPMD_MASTER) अणु
		phydev->master_slave_get = MASTER_SLAVE_CFG_MASTER_FORCE;
		phydev->master_slave_state = MASTER_SLAVE_STATE_MASTER;
	पूर्ण अन्यथा अणु
		phydev->master_slave_get = MASTER_SLAVE_CFG_SLAVE_FORCE;
		phydev->master_slave_state = MASTER_SLAVE_STATE_SLAVE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_c45_config_aneg(काष्ठा phy_device *phydev)
अणु
	वापस nxp_c45_setup_master_slave(phydev);
पूर्ण

अटल पूर्णांक nxp_c45_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = genphy_c45_पढ़ो_status(phydev);
	अगर (ret)
		वापस ret;

	ret = nxp_c45_पढ़ो_master_slave(phydev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_c45_get_sqi(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	reg = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, VEND1_SIGNAL_QUALITY);
	अगर (!(reg & SQI_VALID))
		वापस -EINVAL;

	reg &= SQI_MASK;

	वापस reg;
पूर्ण

अटल पूर्णांक nxp_c45_get_sqi_max(काष्ठा phy_device *phydev)
अणु
	वापस MAX_SQI;
पूर्ण

अटल पूर्णांक nxp_c45_check_delay(काष्ठा phy_device *phydev, u32 delay)
अणु
	अगर (delay < MIN_ID_PS) अणु
		phydev_err(phydev, "delay value smaller than %u\n", MIN_ID_PS);
		वापस -EINVAL;
	पूर्ण

	अगर (delay > MAX_ID_PS) अणु
		phydev_err(phydev, "delay value higher than %u\n", MAX_ID_PS);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 nxp_c45_get_phase_shअगरt(u64 phase_offset_raw)
अणु
	/* The delay in degree phase is 73.8 + phase_offset_raw * 0.9.
	 * To aव्योम भग्नing poपूर्णांक operations we'll multiply by 10
	 * and get 1 decimal poपूर्णांक precision.
	 */
	phase_offset_raw *= 10;
	phase_offset_raw -= 738;
	वापस भाग_u64(phase_offset_raw, 9);
पूर्ण

अटल व्योम nxp_c45_disable_delays(काष्ठा phy_device *phydev)
अणु
	phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_TXID, ID_ENABLE);
	phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_RXID, ID_ENABLE);
पूर्ण

अटल व्योम nxp_c45_set_delays(काष्ठा phy_device *phydev)
अणु
	काष्ठा nxp_c45_phy *priv = phydev->priv;
	u64 tx_delay = priv->tx_delay;
	u64 rx_delay = priv->rx_delay;
	u64 degree;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) अणु
		degree = भाग_u64(tx_delay, PS_PER_DEGREE);
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_TXID,
			      ID_ENABLE | nxp_c45_get_phase_shअगरt(degree));
	पूर्ण अन्यथा अणु
		phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_TXID,
				   ID_ENABLE);
	पूर्ण

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) अणु
		degree = भाग_u64(rx_delay, PS_PER_DEGREE);
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_RXID,
			      ID_ENABLE | nxp_c45_get_phase_shअगरt(degree));
	पूर्ण अन्यथा अणु
		phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_RXID,
				   ID_ENABLE);
	पूर्ण
पूर्ण

अटल पूर्णांक nxp_c45_get_delays(काष्ठा phy_device *phydev)
अणु
	काष्ठा nxp_c45_phy *priv = phydev->priv;
	पूर्णांक ret;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) अणु
		ret = device_property_पढ़ो_u32(&phydev->mdio.dev,
					       "tx-internal-delay-ps",
					       &priv->tx_delay);
		अगर (ret)
			priv->tx_delay = DEFAULT_ID_PS;

		ret = nxp_c45_check_delay(phydev, priv->tx_delay);
		अगर (ret) अणु
			phydev_err(phydev,
				   "tx-internal-delay-ps invalid value\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) अणु
		ret = device_property_पढ़ो_u32(&phydev->mdio.dev,
					       "rx-internal-delay-ps",
					       &priv->rx_delay);
		अगर (ret)
			priv->rx_delay = DEFAULT_ID_PS;

		ret = nxp_c45_check_delay(phydev, priv->rx_delay);
		अगर (ret) अणु
			phydev_err(phydev,
				   "rx-internal-delay-ps invalid value\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_c45_set_phy_mode(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, VEND1_ABILITIES);
	phydev_dbg(phydev, "Clause 45 managed PHY abilities 0x%x\n", ret);

	चयन (phydev->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		अगर (!(ret & RGMII_ABILITY)) अणु
			phydev_err(phydev, "rgmii mode not supported\n");
			वापस -EINVAL;
		पूर्ण
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_RGMII);
		nxp_c45_disable_delays(phydev);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		अगर (!(ret & RGMII_ID_ABILITY)) अणु
			phydev_err(phydev, "rgmii-id, rgmii-txid, rgmii-rxid modes are not supported\n");
			वापस -EINVAL;
		पूर्ण
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_RGMII);
		ret = nxp_c45_get_delays(phydev);
		अगर (ret)
			वापस ret;

		nxp_c45_set_delays(phydev);
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
		अगर (!(ret & MII_ABILITY)) अणु
			phydev_err(phydev, "mii mode not supported\n");
			वापस -EINVAL;
		पूर्ण
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_MII);
		अवरोध;
	हाल PHY_INTERFACE_MODE_REVMII:
		अगर (!(ret & REVMII_ABILITY)) अणु
			phydev_err(phydev, "rev-mii mode not supported\n");
			वापस -EINVAL;
		पूर्ण
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_MII | MII_BASIC_CONFIG_REV);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		अगर (!(ret & RMII_ABILITY)) अणु
			phydev_err(phydev, "rmii mode not supported\n");
			वापस -EINVAL;
		पूर्ण
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_RMII);
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
		अगर (!(ret & SGMII_ABILITY)) अणु
			phydev_err(phydev, "sgmii mode not supported\n");
			वापस -EINVAL;
		पूर्ण
		phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_SGMII);
		अवरोध;
	हाल PHY_INTERFACE_MODE_INTERNAL:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_c45_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = nxp_c45_config_enable(phydev);
	अगर (ret) अणु
		phydev_err(phydev, "Failed to enable config\n");
		वापस ret;
	पूर्ण

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_CONFIG,
			 PHY_CONFIG_AUTO);

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_LINK_DROP_COUNTER,
			 COUNTER_EN);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_RX_PREAMBLE_COUNT,
			 COUNTER_EN);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_TX_PREAMBLE_COUNT,
			 COUNTER_EN);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_RX_IPG_LENGTH,
			 COUNTER_EN);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_TX_IPG_LENGTH,
			 COUNTER_EN);

	ret = nxp_c45_set_phy_mode(phydev);
	अगर (ret)
		वापस ret;

	phydev->स्वतःneg = AUTONEG_DISABLE;

	वापस nxp_c45_start_op(phydev);
पूर्ण

अटल पूर्णांक nxp_c45_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा nxp_c45_phy *priv;

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	वापस 0;
पूर्ण

अटल काष्ठा phy_driver nxp_c45_driver[] = अणु
	अणु
		PHY_ID_MATCH_MODEL(PHY_ID_TJA_1103),
		.name			= "NXP C45 TJA1103",
		.features		= PHY_BASIC_T1_FEATURES,
		.probe			= nxp_c45_probe,
		.soft_reset		= nxp_c45_soft_reset,
		.config_aneg		= nxp_c45_config_aneg,
		.config_init		= nxp_c45_config_init,
		.config_पूर्णांकr		= nxp_c45_config_पूर्णांकr,
		.handle_पूर्णांकerrupt	= nxp_c45_handle_पूर्णांकerrupt,
		.पढ़ो_status		= nxp_c45_पढ़ो_status,
		.suspend		= genphy_c45_pma_suspend,
		.resume			= genphy_c45_pma_resume,
		.get_sset_count		= nxp_c45_get_sset_count,
		.get_strings		= nxp_c45_get_strings,
		.get_stats		= nxp_c45_get_stats,
		.cable_test_start	= nxp_c45_cable_test_start,
		.cable_test_get_status	= nxp_c45_cable_test_get_status,
		.set_loopback		= genphy_c45_loopback,
		.get_sqi		= nxp_c45_get_sqi,
		.get_sqi_max		= nxp_c45_get_sqi_max,
	पूर्ण,
पूर्ण;

module_phy_driver(nxp_c45_driver);

अटल काष्ठा mdio_device_id __maybe_unused nxp_c45_tbl[] = अणु
	अणु PHY_ID_MATCH_MODEL(PHY_ID_TJA_1103) पूर्ण,
	अणु /*sentinel*/ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(mdio, nxp_c45_tbl);

MODULE_AUTHOR("Radu Pirea <radu-nicolae.pirea@oss.nxp.com>");
MODULE_DESCRIPTION("NXP C45 PHY driver");
MODULE_LICENSE("GPL v2");
