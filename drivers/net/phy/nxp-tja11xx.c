<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* NXP TJA1100 BroadRReach PHY driver
 *
 * Copyright (C) 2018 Marek Vasut <marex@denx.de>
 */
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_irq.h>

#घोषणा PHY_ID_MASK			0xfffffff0
#घोषणा PHY_ID_TJA1100			0x0180dc40
#घोषणा PHY_ID_TJA1101			0x0180dd00
#घोषणा PHY_ID_TJA1102			0x0180dc80

#घोषणा MII_ECTRL			17
#घोषणा MII_ECTRL_LINK_CONTROL		BIT(15)
#घोषणा MII_ECTRL_POWER_MODE_MASK	GENMASK(14, 11)
#घोषणा MII_ECTRL_POWER_MODE_NO_CHANGE	(0x0 << 11)
#घोषणा MII_ECTRL_POWER_MODE_NORMAL	(0x3 << 11)
#घोषणा MII_ECTRL_POWER_MODE_STANDBY	(0xc << 11)
#घोषणा MII_ECTRL_CABLE_TEST		BIT(5)
#घोषणा MII_ECTRL_CONFIG_EN		BIT(2)
#घोषणा MII_ECTRL_WAKE_REQUEST		BIT(0)

#घोषणा MII_CFG1			18
#घोषणा MII_CFG1_MASTER_SLAVE		BIT(15)
#घोषणा MII_CFG1_AUTO_OP		BIT(14)
#घोषणा MII_CFG1_SLEEP_CONFIRM		BIT(6)
#घोषणा MII_CFG1_LED_MODE_MASK		GENMASK(5, 4)
#घोषणा MII_CFG1_LED_MODE_LINKUP	0
#घोषणा MII_CFG1_LED_ENABLE		BIT(3)

#घोषणा MII_CFG2			19
#घोषणा MII_CFG2_SLEEP_REQUEST_TO	GENMASK(1, 0)
#घोषणा MII_CFG2_SLEEP_REQUEST_TO_16MS	0x3

#घोषणा MII_INTSRC			21
#घोषणा MII_INTSRC_LINK_FAIL		BIT(10)
#घोषणा MII_INTSRC_LINK_UP		BIT(9)
#घोषणा MII_INTSRC_MASK			(MII_INTSRC_LINK_FAIL | MII_INTSRC_LINK_UP)
#घोषणा MII_INTSRC_TEMP_ERR		BIT(1)
#घोषणा MII_INTSRC_UV_ERR		BIT(3)

#घोषणा MII_INTEN			22
#घोषणा MII_INTEN_LINK_FAIL		BIT(10)
#घोषणा MII_INTEN_LINK_UP		BIT(9)

#घोषणा MII_COMMSTAT			23
#घोषणा MII_COMMSTAT_LINK_UP		BIT(15)
#घोषणा MII_COMMSTAT_SQI_STATE		GENMASK(7, 5)
#घोषणा MII_COMMSTAT_SQI_MAX		7

#घोषणा MII_GENSTAT			24
#घोषणा MII_GENSTAT_PLL_LOCKED		BIT(14)

#घोषणा MII_EXTSTAT			25
#घोषणा MII_EXTSTAT_SHORT_DETECT	BIT(8)
#घोषणा MII_EXTSTAT_OPEN_DETECT		BIT(7)
#घोषणा MII_EXTSTAT_POLARITY_DETECT	BIT(6)

#घोषणा MII_COMMCFG			27
#घोषणा MII_COMMCFG_AUTO_OP		BIT(15)

काष्ठा tja11xx_priv अणु
	अक्षर		*hwmon_name;
	काष्ठा device	*hwmon_dev;
	काष्ठा phy_device *phydev;
	काष्ठा work_काष्ठा phy_रेजिस्टर_work;
पूर्ण;

काष्ठा tja11xx_phy_stats अणु
	स्थिर अक्षर	*string;
	u8		reg;
	u8		off;
	u16		mask;
पूर्ण;

अटल काष्ठा tja11xx_phy_stats tja11xx_hw_stats[] = अणु
	अणु "phy_symbol_error_count", 20, 0, GENMASK(15, 0) पूर्ण,
	अणु "phy_polarity_detect", 25, 6, BIT(6) पूर्ण,
	अणु "phy_open_detect", 25, 7, BIT(7) पूर्ण,
	अणु "phy_short_detect", 25, 8, BIT(8) पूर्ण,
	अणु "phy_rem_rcvr_count", 26, 0, GENMASK(7, 0) पूर्ण,
	अणु "phy_loc_rcvr_count", 26, 8, GENMASK(15, 8) पूर्ण,
पूर्ण;

अटल पूर्णांक tja11xx_check(काष्ठा phy_device *phydev, u8 reg, u16 mask, u16 set)
अणु
	पूर्णांक val;

	वापस phy_पढ़ो_poll_समयout(phydev, reg, val, (val & mask) == set,
				     150, 30000, false);
पूर्ण

अटल पूर्णांक phy_modअगरy_check(काष्ठा phy_device *phydev, u8 reg,
			    u16 mask, u16 set)
अणु
	पूर्णांक ret;

	ret = phy_modअगरy(phydev, reg, mask, set);
	अगर (ret)
		वापस ret;

	वापस tja11xx_check(phydev, reg, mask, set);
पूर्ण

अटल पूर्णांक tja11xx_enable_reg_ग_लिखो(काष्ठा phy_device *phydev)
अणु
	वापस phy_set_bits(phydev, MII_ECTRL, MII_ECTRL_CONFIG_EN);
पूर्ण

अटल पूर्णांक tja11xx_enable_link_control(काष्ठा phy_device *phydev)
अणु
	वापस phy_set_bits(phydev, MII_ECTRL, MII_ECTRL_LINK_CONTROL);
पूर्ण

अटल पूर्णांक tja11xx_disable_link_control(काष्ठा phy_device *phydev)
अणु
	वापस phy_clear_bits(phydev, MII_ECTRL, MII_ECTRL_LINK_CONTROL);
पूर्ण

अटल पूर्णांक tja11xx_wakeup(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो(phydev, MII_ECTRL);
	अगर (ret < 0)
		वापस ret;

	चयन (ret & MII_ECTRL_POWER_MODE_MASK) अणु
	हाल MII_ECTRL_POWER_MODE_NO_CHANGE:
		अवरोध;
	हाल MII_ECTRL_POWER_MODE_NORMAL:
		ret = phy_set_bits(phydev, MII_ECTRL, MII_ECTRL_WAKE_REQUEST);
		अगर (ret)
			वापस ret;

		ret = phy_clear_bits(phydev, MII_ECTRL, MII_ECTRL_WAKE_REQUEST);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल MII_ECTRL_POWER_MODE_STANDBY:
		ret = phy_modअगरy_check(phydev, MII_ECTRL,
				       MII_ECTRL_POWER_MODE_MASK,
				       MII_ECTRL_POWER_MODE_STANDBY);
		अगर (ret)
			वापस ret;

		ret = phy_modअगरy(phydev, MII_ECTRL, MII_ECTRL_POWER_MODE_MASK,
				 MII_ECTRL_POWER_MODE_NORMAL);
		अगर (ret)
			वापस ret;

		ret = phy_modअगरy_check(phydev, MII_GENSTAT,
				       MII_GENSTAT_PLL_LOCKED,
				       MII_GENSTAT_PLL_LOCKED);
		अगर (ret)
			वापस ret;

		वापस tja11xx_enable_link_control(phydev);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tja11xx_soft_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = tja11xx_enable_reg_ग_लिखो(phydev);
	अगर (ret)
		वापस ret;

	वापस genphy_soft_reset(phydev);
पूर्ण

अटल पूर्णांक tja11xx_config_aneg_cable_test(काष्ठा phy_device *phydev)
अणु
	bool finished = false;
	पूर्णांक ret;

	अगर (phydev->link)
		वापस 0;

	अगर (!phydev->drv->cable_test_start ||
	    !phydev->drv->cable_test_get_status)
		वापस 0;

	ret = ethnl_cable_test_alloc(phydev, ETHTOOL_MSG_CABLE_TEST_NTF);
	अगर (ret)
		वापस ret;

	ret = phydev->drv->cable_test_start(phydev);
	अगर (ret)
		वापस ret;

	/* According to the करोcumentation this test takes 100 usec */
	usleep_range(100, 200);

	ret = phydev->drv->cable_test_get_status(phydev, &finished);
	अगर (ret)
		वापस ret;

	अगर (finished)
		ethnl_cable_test_finished(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक tja11xx_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret, changed = 0;
	u16 ctl = 0;

	चयन (phydev->master_slave_set) अणु
	हाल MASTER_SLAVE_CFG_MASTER_FORCE:
		ctl |= MII_CFG1_MASTER_SLAVE;
		अवरोध;
	हाल MASTER_SLAVE_CFG_SLAVE_FORCE:
		अवरोध;
	हाल MASTER_SLAVE_CFG_UNKNOWN:
	हाल MASTER_SLAVE_CFG_UNSUPPORTED:
		जाओ करो_test;
	शेष:
		phydev_warn(phydev, "Unsupported Master/Slave mode\n");
		वापस -ENOTSUPP;
	पूर्ण

	changed = phy_modअगरy_changed(phydev, MII_CFG1, MII_CFG1_MASTER_SLAVE, ctl);
	अगर (changed < 0)
		वापस changed;

करो_test:
	ret = tja11xx_config_aneg_cable_test(phydev);
	अगर (ret)
		वापस ret;

	वापस __genphy_config_aneg(phydev, changed);
पूर्ण

अटल पूर्णांक tja11xx_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = tja11xx_enable_reg_ग_लिखो(phydev);
	अगर (ret)
		वापस ret;

	phydev->स्वतःneg = AUTONEG_DISABLE;
	phydev->speed = SPEED_100;
	phydev->duplex = DUPLEX_FULL;

	चयन (phydev->phy_id & PHY_ID_MASK) अणु
	हाल PHY_ID_TJA1100:
		ret = phy_modअगरy(phydev, MII_CFG1,
				 MII_CFG1_AUTO_OP | MII_CFG1_LED_MODE_MASK |
				 MII_CFG1_LED_ENABLE,
				 MII_CFG1_AUTO_OP | MII_CFG1_LED_MODE_LINKUP |
				 MII_CFG1_LED_ENABLE);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल PHY_ID_TJA1101:
	हाल PHY_ID_TJA1102:
		ret = phy_set_bits(phydev, MII_COMMCFG, MII_COMMCFG_AUTO_OP);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = phy_clear_bits(phydev, MII_CFG1, MII_CFG1_SLEEP_CONFIRM);
	अगर (ret)
		वापस ret;

	ret = phy_modअगरy(phydev, MII_CFG2, MII_CFG2_SLEEP_REQUEST_TO,
			 MII_CFG2_SLEEP_REQUEST_TO_16MS);
	अगर (ret)
		वापस ret;

	ret = tja11xx_wakeup(phydev);
	अगर (ret < 0)
		वापस ret;

	/* ACK पूर्णांकerrupts by पढ़ोing the status रेजिस्टर */
	ret = phy_पढ़ो(phydev, MII_INTSRC);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tja11xx_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	phydev->master_slave_get = MASTER_SLAVE_CFG_UNKNOWN;
	phydev->master_slave_state = MASTER_SLAVE_STATE_UNSUPPORTED;

	ret = genphy_update_link(phydev);
	अगर (ret)
		वापस ret;

	ret = phy_पढ़ो(phydev, MII_CFG1);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & MII_CFG1_MASTER_SLAVE)
		phydev->master_slave_get = MASTER_SLAVE_CFG_MASTER_FORCE;
	अन्यथा
		phydev->master_slave_get = MASTER_SLAVE_CFG_SLAVE_FORCE;

	अगर (phydev->link) अणु
		ret = phy_पढ़ो(phydev, MII_COMMSTAT);
		अगर (ret < 0)
			वापस ret;

		अगर (!(ret & MII_COMMSTAT_LINK_UP))
			phydev->link = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tja11xx_get_sqi(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो(phydev, MII_COMMSTAT);
	अगर (ret < 0)
		वापस ret;

	वापस FIELD_GET(MII_COMMSTAT_SQI_STATE, ret);
पूर्ण

अटल पूर्णांक tja11xx_get_sqi_max(काष्ठा phy_device *phydev)
अणु
	वापस MII_COMMSTAT_SQI_MAX;
पूर्ण

अटल पूर्णांक tja11xx_get_sset_count(काष्ठा phy_device *phydev)
अणु
	वापस ARRAY_SIZE(tja11xx_hw_stats);
पूर्ण

अटल व्योम tja11xx_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tja11xx_hw_stats); i++) अणु
		म_नकलन(data + i * ETH_GSTRING_LEN,
			tja11xx_hw_stats[i].string, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल व्योम tja11xx_get_stats(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(tja11xx_hw_stats); i++) अणु
		ret = phy_पढ़ो(phydev, tja11xx_hw_stats[i].reg);
		अगर (ret < 0)
			data[i] = U64_MAX;
		अन्यथा अणु
			data[i] = ret & tja11xx_hw_stats[i].mask;
			data[i] >>= tja11xx_hw_stats[i].off;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tja11xx_hwmon_पढ़ो(काष्ठा device *dev,
			      क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel, दीर्घ *value)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (type == hwmon_in && attr == hwmon_in_lcrit_alarm) अणु
		ret = phy_पढ़ो(phydev, MII_INTSRC);
		अगर (ret < 0)
			वापस ret;

		*value = !!(ret & MII_INTSRC_TEMP_ERR);
		वापस 0;
	पूर्ण

	अगर (type == hwmon_temp && attr == hwmon_temp_crit_alarm) अणु
		ret = phy_पढ़ो(phydev, MII_INTSRC);
		अगर (ret < 0)
			वापस ret;

		*value = !!(ret & MII_INTSRC_UV_ERR);
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल umode_t tja11xx_hwmon_is_visible(स्थिर व्योम *data,
					क्रमागत hwmon_sensor_types type,
					u32 attr, पूर्णांक channel)
अणु
	अगर (type == hwmon_in && attr == hwmon_in_lcrit_alarm)
		वापस 0444;

	अगर (type == hwmon_temp && attr == hwmon_temp_crit_alarm)
		वापस 0444;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *tja11xx_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(in, HWMON_I_LCRIT_ALARM),
	HWMON_CHANNEL_INFO(temp, HWMON_T_CRIT_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops tja11xx_hwmon_hwmon_ops = अणु
	.is_visible	= tja11xx_hwmon_is_visible,
	.पढ़ो		= tja11xx_hwmon_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info tja11xx_hwmon_chip_info = अणु
	.ops		= &tja11xx_hwmon_hwmon_ops,
	.info		= tja11xx_hwmon_info,
पूर्ण;

अटल पूर्णांक tja11xx_hwmon_रेजिस्टर(काष्ठा phy_device *phydev,
				  काष्ठा tja11xx_priv *priv)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	पूर्णांक i;

	priv->hwmon_name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	अगर (!priv->hwmon_name)
		वापस -ENOMEM;

	क्रम (i = 0; priv->hwmon_name[i]; i++)
		अगर (hwmon_is_bad_अक्षर(priv->hwmon_name[i]))
			priv->hwmon_name[i] = '_';

	priv->hwmon_dev =
		devm_hwmon_device_रेजिस्टर_with_info(dev, priv->hwmon_name,
						     phydev,
						     &tja11xx_hwmon_chip_info,
						     शून्य);

	वापस PTR_ERR_OR_ZERO(priv->hwmon_dev);
पूर्ण

अटल पूर्णांक tja11xx_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा tja11xx_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->phydev = phydev;

	वापस tja11xx_hwmon_रेजिस्टर(phydev, priv);
पूर्ण

अटल व्योम tja1102_p1_रेजिस्टर(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tja11xx_priv *priv = container_of(work, काष्ठा tja11xx_priv,
						 phy_रेजिस्टर_work);
	काष्ठा phy_device *phydev_phy0 = priv->phydev;
	काष्ठा mii_bus *bus = phydev_phy0->mdio.bus;
	काष्ठा device *dev = &phydev_phy0->mdio.dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	पूर्णांक ret;

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा phy_device *phy;
		पूर्णांक addr;

		addr = of_mdio_parse_addr(dev, child);
		अगर (addr < 0) अणु
			dev_err(dev, "Can't parse addr\n");
			जारी;
		पूर्ण अन्यथा अगर (addr != phydev_phy0->mdio.addr + 1) अणु
			/* Currently we care only about द्विगुन PHY chip TJA1102.
			 * If some day NXP will decide to bring chips with more
			 * PHYs, this logic should be reworked.
			 */
			dev_err(dev, "Unexpected address. Should be: %i\n",
				phydev_phy0->mdio.addr + 1);
			जारी;
		पूर्ण

		अगर (mdiobus_is_रेजिस्टरed_device(bus, addr)) अणु
			dev_err(dev, "device is already registered\n");
			जारी;
		पूर्ण

		/* Real PHY ID of Port 1 is 0 */
		phy = phy_device_create(bus, addr, PHY_ID_TJA1102, false, शून्य);
		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "Can't create PHY device for Port 1: %i\n",
				addr);
			जारी;
		पूर्ण

		/* Overग_लिखो parent device. phy_device_create() set parent to
		 * the mii_bus->dev, which is not correct in हाल.
		 */
		phy->mdio.dev.parent = dev;

		ret = of_mdiobus_phy_device_रेजिस्टर(bus, phy, child, addr);
		अगर (ret) अणु
			/* All resources needed क्रम Port 1 should be alपढ़ोy
			 * available क्रम Port 0. Both ports use the same
			 * पूर्णांकerrupt line, so -EPROBE_DEFER would make no sense
			 * here.
			 */
			dev_err(dev, "Can't register Port 1. Unexpected error: %i\n",
				ret);
			phy_device_मुक्त(phy);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tja1102_p0_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा tja11xx_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->phydev = phydev;
	INIT_WORK(&priv->phy_रेजिस्टर_work, tja1102_p1_रेजिस्टर);

	ret = tja11xx_hwmon_रेजिस्टर(phydev, priv);
	अगर (ret)
		वापस ret;

	schedule_work(&priv->phy_रेजिस्टर_work);

	वापस 0;
पूर्ण

अटल पूर्णांक tja1102_match_phy_device(काष्ठा phy_device *phydev, bool port0)
अणु
	पूर्णांक ret;

	अगर ((phydev->phy_id & PHY_ID_MASK) != PHY_ID_TJA1102)
		वापस 0;

	ret = phy_पढ़ो(phydev, MII_PHYSID2);
	अगर (ret < 0)
		वापस ret;

	/* TJA1102 Port 1 has phyid 0 and करोesn't support temperature
	 * and undervoltage alarms.
	 */
	अगर (port0)
		वापस ret ? 1 : 0;

	वापस !ret;
पूर्ण

अटल पूर्णांक tja1102_p0_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस tja1102_match_phy_device(phydev, true);
पूर्ण

अटल पूर्णांक tja1102_p1_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस tja1102_match_phy_device(phydev, false);
पूर्ण

अटल पूर्णांक tja11xx_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो(phydev, MII_INTSRC);

	वापस (ret < 0) ? ret : 0;
पूर्ण

अटल पूर्णांक tja11xx_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value = 0;
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = tja11xx_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		value = MII_INTEN_LINK_FAIL | MII_INTEN_LINK_UP;
		err = phy_ग_लिखो(phydev, MII_INTEN, value);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_INTEN, value);
		अगर (err)
			वापस err;

		err = tja11xx_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t tja11xx_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_INTSRC);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_INTSRC_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tja11xx_cable_test_start(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_clear_bits(phydev, MII_COMMCFG, MII_COMMCFG_AUTO_OP);
	अगर (ret)
		वापस ret;

	ret = tja11xx_wakeup(phydev);
	अगर (ret < 0)
		वापस ret;

	ret = tja11xx_disable_link_control(phydev);
	अगर (ret < 0)
		वापस ret;

	वापस phy_set_bits(phydev, MII_ECTRL, MII_ECTRL_CABLE_TEST);
पूर्ण

/*
 * | BI_DA+           | BI_DA-                 | Result
 * | खोलो             | खोलो                   | खोलो
 * | + लघु to -     | - लघु to +           | लघु
 * | लघु to Vdd     | खोलो                   | खोलो
 * | खोलो             | shot to Vdd            | खोलो
 * | लघु to Vdd     | लघु to Vdd           | लघु
 * | shot to GND      | खोलो                   | खोलो
 * | खोलो             | shot to GND            | खोलो
 * | लघु to GND     | shot to GND            | लघु
 * | connected to active link partner (master) | shot and खोलो
 */
अटल पूर्णांक tja11xx_cable_test_report_trans(u32 result)
अणु
	u32 mask = MII_EXTSTAT_SHORT_DETECT | MII_EXTSTAT_OPEN_DETECT;

	अगर ((result & mask) == mask) अणु
		/* connected to active link partner (master) */
		वापस ETHTOOL_A_CABLE_RESULT_CODE_UNSPEC;
	पूर्ण अन्यथा अगर ((result & mask) == 0) अणु
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OK;
	पूर्ण अन्यथा अगर (result & MII_EXTSTAT_SHORT_DETECT) अणु
		वापस ETHTOOL_A_CABLE_RESULT_CODE_SAME_SHORT;
	पूर्ण अन्यथा अगर (result & MII_EXTSTAT_OPEN_DETECT) अणु
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OPEN;
	पूर्ण अन्यथा अणु
		वापस ETHTOOL_A_CABLE_RESULT_CODE_UNSPEC;
	पूर्ण
पूर्ण

अटल पूर्णांक tja11xx_cable_test_report(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो(phydev, MII_EXTSTAT);
	अगर (ret < 0)
		वापस ret;

	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_A,
				tja11xx_cable_test_report_trans(ret));

	वापस 0;
पूर्ण

अटल पूर्णांक tja11xx_cable_test_get_status(काष्ठा phy_device *phydev,
					 bool *finished)
अणु
	पूर्णांक ret;

	*finished = false;

	ret = phy_पढ़ो(phydev, MII_ECTRL);
	अगर (ret < 0)
		वापस ret;

	अगर (!(ret & MII_ECTRL_CABLE_TEST)) अणु
		*finished = true;

		ret = phy_set_bits(phydev, MII_COMMCFG, MII_COMMCFG_AUTO_OP);
		अगर (ret)
			वापस ret;

		वापस tja11xx_cable_test_report(phydev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा phy_driver tja11xx_driver[] = अणु
	अणु
		PHY_ID_MATCH_MODEL(PHY_ID_TJA1100),
		.name		= "NXP TJA1100",
		.features       = PHY_BASIC_T1_FEATURES,
		.probe		= tja11xx_probe,
		.soft_reset	= tja11xx_soft_reset,
		.config_aneg	= tja11xx_config_aneg,
		.config_init	= tja11xx_config_init,
		.पढ़ो_status	= tja11xx_पढ़ो_status,
		.get_sqi	= tja11xx_get_sqi,
		.get_sqi_max	= tja11xx_get_sqi_max,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.set_loopback   = genphy_loopback,
		/* Statistics */
		.get_sset_count = tja11xx_get_sset_count,
		.get_strings	= tja11xx_get_strings,
		.get_stats	= tja11xx_get_stats,
	पूर्ण, अणु
		PHY_ID_MATCH_MODEL(PHY_ID_TJA1101),
		.name		= "NXP TJA1101",
		.features       = PHY_BASIC_T1_FEATURES,
		.probe		= tja11xx_probe,
		.soft_reset	= tja11xx_soft_reset,
		.config_aneg	= tja11xx_config_aneg,
		.config_init	= tja11xx_config_init,
		.पढ़ो_status	= tja11xx_पढ़ो_status,
		.get_sqi	= tja11xx_get_sqi,
		.get_sqi_max	= tja11xx_get_sqi_max,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.set_loopback   = genphy_loopback,
		/* Statistics */
		.get_sset_count = tja11xx_get_sset_count,
		.get_strings	= tja11xx_get_strings,
		.get_stats	= tja11xx_get_stats,
	पूर्ण, अणु
		.name		= "NXP TJA1102 Port 0",
		.features       = PHY_BASIC_T1_FEATURES,
		.flags          = PHY_POLL_CABLE_TEST,
		.probe		= tja1102_p0_probe,
		.soft_reset	= tja11xx_soft_reset,
		.config_aneg	= tja11xx_config_aneg,
		.config_init	= tja11xx_config_init,
		.पढ़ो_status	= tja11xx_पढ़ो_status,
		.get_sqi	= tja11xx_get_sqi,
		.get_sqi_max	= tja11xx_get_sqi_max,
		.match_phy_device = tja1102_p0_match_phy_device,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.set_loopback   = genphy_loopback,
		/* Statistics */
		.get_sset_count = tja11xx_get_sset_count,
		.get_strings	= tja11xx_get_strings,
		.get_stats	= tja11xx_get_stats,
		.config_पूर्णांकr	= tja11xx_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = tja11xx_handle_पूर्णांकerrupt,
		.cable_test_start = tja11xx_cable_test_start,
		.cable_test_get_status = tja11xx_cable_test_get_status,
	पूर्ण, अणु
		.name		= "NXP TJA1102 Port 1",
		.features       = PHY_BASIC_T1_FEATURES,
		.flags          = PHY_POLL_CABLE_TEST,
		/* currently no probe क्रम Port 1 is need */
		.soft_reset	= tja11xx_soft_reset,
		.config_aneg	= tja11xx_config_aneg,
		.config_init	= tja11xx_config_init,
		.पढ़ो_status	= tja11xx_पढ़ो_status,
		.get_sqi	= tja11xx_get_sqi,
		.get_sqi_max	= tja11xx_get_sqi_max,
		.match_phy_device = tja1102_p1_match_phy_device,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.set_loopback   = genphy_loopback,
		/* Statistics */
		.get_sset_count = tja11xx_get_sset_count,
		.get_strings	= tja11xx_get_strings,
		.get_stats	= tja11xx_get_stats,
		.config_पूर्णांकr	= tja11xx_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = tja11xx_handle_पूर्णांकerrupt,
		.cable_test_start = tja11xx_cable_test_start,
		.cable_test_get_status = tja11xx_cable_test_get_status,
	पूर्ण
पूर्ण;

module_phy_driver(tja11xx_driver);

अटल काष्ठा mdio_device_id __maybe_unused tja11xx_tbl[] = अणु
	अणु PHY_ID_MATCH_MODEL(PHY_ID_TJA1100) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_TJA1101) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_TJA1102) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, tja11xx_tbl);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("NXP TJA11xx BoardR-Reach PHY driver");
MODULE_LICENSE("GPL");
