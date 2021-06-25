<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Framework क्रम configuring and पढ़ोing PHY devices
 * Based on code in sungem_phy.c and gianfar_phy.c
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 * Copyright (c) 2006, 2007  Maciej W. Rozycki
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_led_triggers.h>
#समावेश <linux/sfp.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/sock.h>

#घोषणा PHY_STATE_TIME	HZ

#घोषणा PHY_STATE_STR(_state)			\
	हाल PHY_##_state:			\
		वापस __stringअगरy(_state);	\

अटल स्थिर अक्षर *phy_state_to_str(क्रमागत phy_state st)
अणु
	चयन (st) अणु
	PHY_STATE_STR(DOWN)
	PHY_STATE_STR(READY)
	PHY_STATE_STR(UP)
	PHY_STATE_STR(RUNNING)
	PHY_STATE_STR(NOLINK)
	PHY_STATE_STR(CABLETEST)
	PHY_STATE_STR(HALTED)
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम phy_link_up(काष्ठा phy_device *phydev)
अणु
	phydev->phy_link_change(phydev, true);
	phy_led_trigger_change_speed(phydev);
पूर्ण

अटल व्योम phy_link_करोwn(काष्ठा phy_device *phydev)
अणु
	phydev->phy_link_change(phydev, false);
	phy_led_trigger_change_speed(phydev);
पूर्ण

अटल स्थिर अक्षर *phy_छोड़ो_str(काष्ठा phy_device *phydev)
अणु
	bool local_छोड़ो, local_asym_छोड़ो;

	अगर (phydev->स्वतःneg == AUTONEG_DISABLE)
		जाओ no_छोड़ो;

	local_छोड़ो = linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
					phydev->advertising);
	local_asym_छोड़ो = linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
					     phydev->advertising);

	अगर (local_छोड़ो && phydev->छोड़ो)
		वापस "rx/tx";

	अगर (local_asym_छोड़ो && phydev->asym_छोड़ो) अणु
		अगर (local_छोड़ो)
			वापस "rx";
		अगर (phydev->छोड़ो)
			वापस "tx";
	पूर्ण

no_छोड़ो:
	वापस "off";
पूर्ण

/**
 * phy_prपूर्णांक_status - Convenience function to prपूर्णांक out the current phy status
 * @phydev: the phy_device काष्ठा
 */
व्योम phy_prपूर्णांक_status(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->link) अणु
		netdev_info(phydev->attached_dev,
			"Link is Up - %s/%s %s- flow control %s\n",
			phy_speed_to_str(phydev->speed),
			phy_duplex_to_str(phydev->duplex),
			phydev->करोwnshअगरted_rate ? "(downshifted) " : "",
			phy_छोड़ो_str(phydev));
	पूर्ण अन्यथा	अणु
		netdev_info(phydev->attached_dev, "Link is Down\n");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(phy_prपूर्णांक_status);

/**
 * phy_config_पूर्णांकerrupt - configure the PHY device क्रम the requested पूर्णांकerrupts
 * @phydev: the phy_device काष्ठा
 * @पूर्णांकerrupts: पूर्णांकerrupt flags to configure क्रम this @phydev
 *
 * Returns 0 on success or < 0 on error.
 */
अटल पूर्णांक phy_config_पूर्णांकerrupt(काष्ठा phy_device *phydev, bool पूर्णांकerrupts)
अणु
	phydev->पूर्णांकerrupts = पूर्णांकerrupts ? 1 : 0;
	अगर (phydev->drv->config_पूर्णांकr)
		वापस phydev->drv->config_पूर्णांकr(phydev);

	वापस 0;
पूर्ण

/**
 * phy_restart_aneg - restart स्वतः-negotiation
 * @phydev: target phy_device काष्ठा
 *
 * Restart the स्वतःnegotiation on @phydev.  Returns >= 0 on success or
 * negative त्रुटि_सं on error.
 */
पूर्णांक phy_restart_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	अगर (phydev->is_c45 && !(phydev->c45_ids.devices_in_package & BIT(0)))
		ret = genphy_c45_restart_aneg(phydev);
	अन्यथा
		ret = genphy_restart_aneg(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_restart_aneg);

/**
 * phy_aneg_करोne - वापस स्वतः-negotiation status
 * @phydev: target phy_device काष्ठा
 *
 * Description: Return the स्वतः-negotiation status from this @phydev
 * Returns > 0 on success or < 0 on error. 0 means that स्वतः-negotiation
 * is still pending.
 */
पूर्णांक phy_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->drv && phydev->drv->aneg_करोne)
		वापस phydev->drv->aneg_करोne(phydev);
	अन्यथा अगर (phydev->is_c45)
		वापस genphy_c45_aneg_करोne(phydev);
	अन्यथा
		वापस genphy_aneg_करोne(phydev);
पूर्ण
EXPORT_SYMBOL(phy_aneg_करोne);

/**
 * phy_find_valid - find a PHY setting that matches the requested parameters
 * @speed: desired speed
 * @duplex: desired duplex
 * @supported: mask of supported link modes
 *
 * Locate a supported phy setting that is, in priority order:
 * - an exact match क्रम the specअगरied speed and duplex mode
 * - a match क्रम the specअगरied speed, or slower speed
 * - the slowest supported speed
 * Returns the matched phy_setting entry, or %शून्य अगर no supported phy
 * settings were found.
 */
अटल स्थिर काष्ठा phy_setting *
phy_find_valid(पूर्णांक speed, पूर्णांक duplex, अचिन्हित दीर्घ *supported)
अणु
	वापस phy_lookup_setting(speed, duplex, supported, false);
पूर्ण

/**
 * phy_supported_speeds - वापस all speeds currently supported by a phy device
 * @phy: The phy device to वापस supported speeds of.
 * @speeds: buffer to store supported speeds in.
 * @size:   size of speeds buffer.
 *
 * Description: Returns the number of supported speeds, and fills the speeds
 * buffer with the supported speeds. If speeds buffer is too small to contain
 * all currently supported speeds, will वापस as many speeds as can fit.
 */
अचिन्हित पूर्णांक phy_supported_speeds(काष्ठा phy_device *phy,
				  अचिन्हित पूर्णांक *speeds,
				  अचिन्हित पूर्णांक size)
अणु
	वापस phy_speeds(speeds, size, phy->supported);
पूर्ण

/**
 * phy_check_valid - check अगर there is a valid PHY setting which matches
 *		     speed, duplex, and feature mask
 * @speed: speed to match
 * @duplex: duplex to match
 * @features: A mask of the valid settings
 *
 * Description: Returns true अगर there is a valid setting, false otherwise.
 */
अटल अंतरभूत bool phy_check_valid(पूर्णांक speed, पूर्णांक duplex,
				   अचिन्हित दीर्घ *features)
अणु
	वापस !!phy_lookup_setting(speed, duplex, features, true);
पूर्ण

/**
 * phy_sanitize_settings - make sure the PHY is set to supported speed and duplex
 * @phydev: the target phy_device काष्ठा
 *
 * Description: Make sure the PHY is set to supported speeds and
 *   duplexes.  Drop करोwn by one in this order:  1000/FULL,
 *   1000/HALF, 100/FULL, 100/HALF, 10/FULL, 10/HALF.
 */
अटल व्योम phy_sanitize_settings(काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा phy_setting *setting;

	setting = phy_find_valid(phydev->speed, phydev->duplex,
				 phydev->supported);
	अगर (setting) अणु
		phydev->speed = setting->speed;
		phydev->duplex = setting->duplex;
	पूर्ण अन्यथा अणु
		/* We failed to find anything (no supported speeds?) */
		phydev->speed = SPEED_UNKNOWN;
		phydev->duplex = DUPLEX_UNKNOWN;
	पूर्ण
पूर्ण

पूर्णांक phy_ethtool_ksettings_set(काष्ठा phy_device *phydev,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(advertising);
	u8 स्वतःneg = cmd->base.स्वतःneg;
	u8 duplex = cmd->base.duplex;
	u32 speed = cmd->base.speed;

	अगर (cmd->base.phy_address != phydev->mdio.addr)
		वापस -EINVAL;

	linkmode_copy(advertising, cmd->link_modes.advertising);

	/* We make sure that we करोn't pass unsupported values in to the PHY */
	linkmode_and(advertising, advertising, phydev->supported);

	/* Verअगरy the settings we care about. */
	अगर (स्वतःneg != AUTONEG_ENABLE && स्वतःneg != AUTONEG_DISABLE)
		वापस -EINVAL;

	अगर (स्वतःneg == AUTONEG_ENABLE && linkmode_empty(advertising))
		वापस -EINVAL;

	अगर (स्वतःneg == AUTONEG_DISABLE &&
	    ((speed != SPEED_1000 &&
	      speed != SPEED_100 &&
	      speed != SPEED_10) ||
	     (duplex != DUPLEX_HALF &&
	      duplex != DUPLEX_FULL)))
		वापस -EINVAL;

	phydev->स्वतःneg = स्वतःneg;

	अगर (स्वतःneg == AUTONEG_DISABLE) अणु
		phydev->speed = speed;
		phydev->duplex = duplex;
	पूर्ण

	linkmode_copy(phydev->advertising, advertising);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
			 phydev->advertising, स्वतःneg == AUTONEG_ENABLE);

	phydev->master_slave_set = cmd->base.master_slave_cfg;
	phydev->mdix_ctrl = cmd->base.eth_tp_mdix_ctrl;

	/* Restart the PHY */
	phy_start_aneg(phydev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_ksettings_set);

व्योम phy_ethtool_ksettings_get(काष्ठा phy_device *phydev,
			       काष्ठा ethtool_link_ksettings *cmd)
अणु
	linkmode_copy(cmd->link_modes.supported, phydev->supported);
	linkmode_copy(cmd->link_modes.advertising, phydev->advertising);
	linkmode_copy(cmd->link_modes.lp_advertising, phydev->lp_advertising);

	cmd->base.speed = phydev->speed;
	cmd->base.duplex = phydev->duplex;
	cmd->base.master_slave_cfg = phydev->master_slave_get;
	cmd->base.master_slave_state = phydev->master_slave_state;
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_MOCA)
		cmd->base.port = PORT_BNC;
	अन्यथा
		cmd->base.port = phydev->port;
	cmd->base.transceiver = phy_is_पूर्णांकernal(phydev) ?
				XCVR_INTERNAL : XCVR_EXTERNAL;
	cmd->base.phy_address = phydev->mdio.addr;
	cmd->base.स्वतःneg = phydev->स्वतःneg;
	cmd->base.eth_tp_mdix_ctrl = phydev->mdix_ctrl;
	cmd->base.eth_tp_mdix = phydev->mdix;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_ksettings_get);

/**
 * phy_mii_ioctl - generic PHY MII ioctl पूर्णांकerface
 * @phydev: the phy_device काष्ठा
 * @अगरr: &काष्ठा अगरreq क्रम socket ioctl's
 * @cmd: ioctl cmd to execute
 *
 * Note that this function is currently incompatible with the
 * PHYCONTROL layer.  It changes रेजिस्टरs without regard to
 * current state.  Use at own risk.
 */
पूर्णांक phy_mii_ioctl(काष्ठा phy_device *phydev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *mii_data = अगर_mii(अगरr);
	u16 val = mii_data->val_in;
	bool change_स्वतःneg = false;
	पूर्णांक prtad, devad;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		mii_data->phy_id = phydev->mdio.addr;
		fallthrough;

	हाल SIOCGMIIREG:
		अगर (mdio_phy_id_is_c45(mii_data->phy_id)) अणु
			prtad = mdio_phy_id_prtad(mii_data->phy_id);
			devad = mdio_phy_id_devad(mii_data->phy_id);
			devad = mdiobus_c45_addr(devad, mii_data->reg_num);
		पूर्ण अन्यथा अणु
			prtad = mii_data->phy_id;
			devad = mii_data->reg_num;
		पूर्ण
		mii_data->val_out = mdiobus_पढ़ो(phydev->mdio.bus, prtad,
						 devad);
		वापस 0;

	हाल SIOCSMIIREG:
		अगर (mdio_phy_id_is_c45(mii_data->phy_id)) अणु
			prtad = mdio_phy_id_prtad(mii_data->phy_id);
			devad = mdio_phy_id_devad(mii_data->phy_id);
			devad = mdiobus_c45_addr(devad, mii_data->reg_num);
		पूर्ण अन्यथा अणु
			prtad = mii_data->phy_id;
			devad = mii_data->reg_num;
		पूर्ण
		अगर (prtad == phydev->mdio.addr) अणु
			चयन (devad) अणु
			हाल MII_BMCR:
				अगर ((val & (BMCR_RESET | BMCR_ANENABLE)) == 0) अणु
					अगर (phydev->स्वतःneg == AUTONEG_ENABLE)
						change_स्वतःneg = true;
					phydev->स्वतःneg = AUTONEG_DISABLE;
					अगर (val & BMCR_FULLDPLX)
						phydev->duplex = DUPLEX_FULL;
					अन्यथा
						phydev->duplex = DUPLEX_HALF;
					अगर (val & BMCR_SPEED1000)
						phydev->speed = SPEED_1000;
					अन्यथा अगर (val & BMCR_SPEED100)
						phydev->speed = SPEED_100;
					अन्यथा phydev->speed = SPEED_10;
				पूर्ण
				अन्यथा अणु
					अगर (phydev->स्वतःneg == AUTONEG_DISABLE)
						change_स्वतःneg = true;
					phydev->स्वतःneg = AUTONEG_ENABLE;
				पूर्ण
				अवरोध;
			हाल MII_ADVERTISE:
				mii_adv_mod_linkmode_adv_t(phydev->advertising,
							   val);
				change_स्वतःneg = true;
				अवरोध;
			हाल MII_CTRL1000:
				mii_ctrl1000_mod_linkmode_adv_t(phydev->advertising,
							        val);
				change_स्वतःneg = true;
				अवरोध;
			शेष:
				/* करो nothing */
				अवरोध;
			पूर्ण
		पूर्ण

		mdiobus_ग_लिखो(phydev->mdio.bus, prtad, devad, val);

		अगर (prtad == phydev->mdio.addr &&
		    devad == MII_BMCR &&
		    val & BMCR_RESET)
			वापस phy_init_hw(phydev);

		अगर (change_स्वतःneg)
			वापस phy_start_aneg(phydev);

		वापस 0;

	हाल SIOCSHWTSTAMP:
		अगर (phydev->mii_ts && phydev->mii_ts->hwtstamp)
			वापस phydev->mii_ts->hwtstamp(phydev->mii_ts, अगरr);
		fallthrough;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(phy_mii_ioctl);

/**
 * phy_करो_ioctl - generic nकरो_करो_ioctl implementation
 * @dev: the net_device काष्ठा
 * @अगरr: &काष्ठा अगरreq क्रम socket ioctl's
 * @cmd: ioctl cmd to execute
 */
पूर्णांक phy_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	अगर (!dev->phydev)
		वापस -ENODEV;

	वापस phy_mii_ioctl(dev->phydev, अगरr, cmd);
पूर्ण
EXPORT_SYMBOL(phy_करो_ioctl);

/**
 * phy_करो_ioctl_running - generic nकरो_करो_ioctl implementation but test first
 *
 * @dev: the net_device काष्ठा
 * @अगरr: &काष्ठा अगरreq क्रम socket ioctl's
 * @cmd: ioctl cmd to execute
 *
 * Same as phy_करो_ioctl, but ensures that net_device is running beक्रमe
 * handling the ioctl.
 */
पूर्णांक phy_करो_ioctl_running(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	अगर (!netअगर_running(dev))
		वापस -ENODEV;

	वापस phy_करो_ioctl(dev, अगरr, cmd);
पूर्ण
EXPORT_SYMBOL(phy_करो_ioctl_running);

/**
 * phy_queue_state_machine - Trigger the state machine to run soon
 *
 * @phydev: the phy_device काष्ठा
 * @jअगरfies: Run the state machine after these jअगरfies
 */
व्योम phy_queue_state_machine(काष्ठा phy_device *phydev, अचिन्हित दीर्घ jअगरfies)
अणु
	mod_delayed_work(प्रणाली_घातer_efficient_wq, &phydev->state_queue,
			 jअगरfies);
पूर्ण
EXPORT_SYMBOL(phy_queue_state_machine);

/**
 * phy_trigger_machine - Trigger the state machine to run now
 *
 * @phydev: the phy_device काष्ठा
 */
व्योम phy_trigger_machine(काष्ठा phy_device *phydev)
अणु
	phy_queue_state_machine(phydev, 0);
पूर्ण
EXPORT_SYMBOL(phy_trigger_machine);

अटल व्योम phy_पात_cable_test(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	ethnl_cable_test_finished(phydev);

	err = phy_init_hw(phydev);
	अगर (err)
		phydev_err(phydev, "Error while aborting cable test");
पूर्ण

/**
 * phy_ethtool_get_strings - Get the statistic counter names
 *
 * @phydev: the phy_device काष्ठा
 * @data: Where to put the strings
 */
पूर्णांक phy_ethtool_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	अगर (!phydev->drv)
		वापस -EIO;

	mutex_lock(&phydev->lock);
	phydev->drv->get_strings(phydev, data);
	mutex_unlock(&phydev->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_get_strings);

/**
 * phy_ethtool_get_sset_count - Get the number of statistic counters
 *
 * @phydev: the phy_device काष्ठा
 */
पूर्णांक phy_ethtool_get_sset_count(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	अगर (!phydev->drv)
		वापस -EIO;

	अगर (phydev->drv->get_sset_count &&
	    phydev->drv->get_strings &&
	    phydev->drv->get_stats) अणु
		mutex_lock(&phydev->lock);
		ret = phydev->drv->get_sset_count(phydev);
		mutex_unlock(&phydev->lock);

		वापस ret;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_get_sset_count);

/**
 * phy_ethtool_get_stats - Get the statistic counters
 *
 * @phydev: the phy_device काष्ठा
 * @stats: What counters to get
 * @data: Where to store the counters
 */
पूर्णांक phy_ethtool_get_stats(काष्ठा phy_device *phydev,
			  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	अगर (!phydev->drv)
		वापस -EIO;

	mutex_lock(&phydev->lock);
	phydev->drv->get_stats(phydev, stats, data);
	mutex_unlock(&phydev->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_get_stats);

/**
 * phy_start_cable_test - Start a cable test
 *
 * @phydev: the phy_device काष्ठा
 * @extack: extack क्रम reporting useful error messages
 */
पूर्णांक phy_start_cable_test(काष्ठा phy_device *phydev,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = phydev->attached_dev;
	पूर्णांक err = -ENOMEM;

	अगर (!(phydev->drv &&
	      phydev->drv->cable_test_start &&
	      phydev->drv->cable_test_get_status)) अणु
		NL_SET_ERR_MSG(extack,
			       "PHY driver does not support cable testing");
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&phydev->lock);
	अगर (phydev->state == PHY_CABLETEST) अणु
		NL_SET_ERR_MSG(extack,
			       "PHY already performing a test");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (phydev->state < PHY_UP ||
	    phydev->state > PHY_CABLETEST) अणु
		NL_SET_ERR_MSG(extack,
			       "PHY not configured. Try setting interface up");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	err = ethnl_cable_test_alloc(phydev, ETHTOOL_MSG_CABLE_TEST_NTF);
	अगर (err)
		जाओ out;

	/* Mark the carrier करोwn until the test is complete */
	phy_link_करोwn(phydev);

	netअगर_testing_on(dev);
	err = phydev->drv->cable_test_start(phydev);
	अगर (err) अणु
		netअगर_testing_off(dev);
		phy_link_up(phydev);
		जाओ out_मुक्त;
	पूर्ण

	phydev->state = PHY_CABLETEST;

	अगर (phy_polling_mode(phydev))
		phy_trigger_machine(phydev);

	mutex_unlock(&phydev->lock);

	वापस 0;

out_मुक्त:
	ethnl_cable_test_मुक्त(phydev);
out:
	mutex_unlock(&phydev->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(phy_start_cable_test);

/**
 * phy_start_cable_test_tdr - Start a raw TDR cable test
 *
 * @phydev: the phy_device काष्ठा
 * @extack: extack क्रम reporting useful error messages
 * @config: Configuration of the test to run
 */
पूर्णांक phy_start_cable_test_tdr(काष्ठा phy_device *phydev,
			     काष्ठा netlink_ext_ack *extack,
			     स्थिर काष्ठा phy_tdr_config *config)
अणु
	काष्ठा net_device *dev = phydev->attached_dev;
	पूर्णांक err = -ENOMEM;

	अगर (!(phydev->drv &&
	      phydev->drv->cable_test_tdr_start &&
	      phydev->drv->cable_test_get_status)) अणु
		NL_SET_ERR_MSG(extack,
			       "PHY driver does not support cable test TDR");
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&phydev->lock);
	अगर (phydev->state == PHY_CABLETEST) अणु
		NL_SET_ERR_MSG(extack,
			       "PHY already performing a test");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (phydev->state < PHY_UP ||
	    phydev->state > PHY_CABLETEST) अणु
		NL_SET_ERR_MSG(extack,
			       "PHY not configured. Try setting interface up");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	err = ethnl_cable_test_alloc(phydev, ETHTOOL_MSG_CABLE_TEST_TDR_NTF);
	अगर (err)
		जाओ out;

	/* Mark the carrier करोwn until the test is complete */
	phy_link_करोwn(phydev);

	netअगर_testing_on(dev);
	err = phydev->drv->cable_test_tdr_start(phydev, config);
	अगर (err) अणु
		netअगर_testing_off(dev);
		phy_link_up(phydev);
		जाओ out_मुक्त;
	पूर्ण

	phydev->state = PHY_CABLETEST;

	अगर (phy_polling_mode(phydev))
		phy_trigger_machine(phydev);

	mutex_unlock(&phydev->lock);

	वापस 0;

out_मुक्त:
	ethnl_cable_test_मुक्त(phydev);
out:
	mutex_unlock(&phydev->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(phy_start_cable_test_tdr);

पूर्णांक phy_config_aneg(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->drv->config_aneg)
		वापस phydev->drv->config_aneg(phydev);

	/* Clause 45 PHYs that करोn't implement Clause 22 रेजिस्टरs are not
	 * allowed to call genphy_config_aneg()
	 */
	अगर (phydev->is_c45 && !(phydev->c45_ids.devices_in_package & BIT(0)))
		वापस genphy_c45_config_aneg(phydev);

	वापस genphy_config_aneg(phydev);
पूर्ण
EXPORT_SYMBOL(phy_config_aneg);

/**
 * phy_check_link_status - check link status and set state accordingly
 * @phydev: the phy_device काष्ठा
 *
 * Description: Check क्रम link and whether स्वतःneg was triggered / is running
 * and set state accordingly
 */
अटल पूर्णांक phy_check_link_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	lockdep_निश्चित_held(&phydev->lock);

	/* Keep previous state अगर loopback is enabled because some PHYs
	 * report that Link is Down when loopback is enabled.
	 */
	अगर (phydev->loopback_enabled)
		वापस 0;

	err = phy_पढ़ो_status(phydev);
	अगर (err)
		वापस err;

	अगर (phydev->link && phydev->state != PHY_RUNNING) अणु
		phy_check_करोwnshअगरt(phydev);
		phydev->state = PHY_RUNNING;
		phy_link_up(phydev);
	पूर्ण अन्यथा अगर (!phydev->link && phydev->state != PHY_NOLINK) अणु
		phydev->state = PHY_NOLINK;
		phy_link_करोwn(phydev);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * phy_start_aneg - start स्वतः-negotiation क्रम this PHY device
 * @phydev: the phy_device काष्ठा
 *
 * Description: Sanitizes the settings (अगर we're not स्वतःnegotiating
 *   them), and then calls the driver's config_aneg function.
 *   If the PHYCONTROL Layer is operating, we change the state to
 *   reflect the beginning of Auto-negotiation or क्रमcing.
 */
पूर्णांक phy_start_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (!phydev->drv)
		वापस -EIO;

	mutex_lock(&phydev->lock);

	अगर (AUTONEG_DISABLE == phydev->स्वतःneg)
		phy_sanitize_settings(phydev);

	err = phy_config_aneg(phydev);
	अगर (err < 0)
		जाओ out_unlock;

	अगर (phy_is_started(phydev))
		err = phy_check_link_status(phydev);
out_unlock:
	mutex_unlock(&phydev->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(phy_start_aneg);

अटल पूर्णांक phy_poll_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	अचिन्हित पूर्णांक retries = 100;
	पूर्णांक ret;

	करो अणु
		msleep(100);
		ret = phy_aneg_करोne(phydev);
	पूर्ण जबतक (!ret && --retries);

	अगर (!ret)
		वापस -ETIMEDOUT;

	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * phy_speed_करोwn - set speed to lowest speed supported by both link partners
 * @phydev: the phy_device काष्ठा
 * @sync: perक्रमm action synchronously
 *
 * Description: Typically used to save energy when रुकोing क्रम a WoL packet
 *
 * WARNING: Setting sync to false may cause the प्रणाली being unable to suspend
 * in हाल the PHY generates an पूर्णांकerrupt when finishing the स्वतःnegotiation.
 * This पूर्णांकerrupt may wake up the प्रणाली immediately after suspend.
 * Thereक्रमe use sync = false only अगर you're sure it's safe with the respective
 * network chip.
 */
पूर्णांक phy_speed_करोwn(काष्ठा phy_device *phydev, bool sync)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(adv_पंचांगp);
	पूर्णांक ret;

	अगर (phydev->स्वतःneg != AUTONEG_ENABLE)
		वापस 0;

	linkmode_copy(adv_पंचांगp, phydev->advertising);

	ret = phy_speed_करोwn_core(phydev);
	अगर (ret)
		वापस ret;

	linkmode_copy(phydev->adv_old, adv_पंचांगp);

	अगर (linkmode_equal(phydev->advertising, adv_पंचांगp))
		वापस 0;

	ret = phy_config_aneg(phydev);
	अगर (ret)
		वापस ret;

	वापस sync ? phy_poll_aneg_करोne(phydev) : 0;
पूर्ण
EXPORT_SYMBOL_GPL(phy_speed_करोwn);

/**
 * phy_speed_up - (re)set advertised speeds to all supported speeds
 * @phydev: the phy_device काष्ठा
 *
 * Description: Used to revert the effect of phy_speed_करोwn
 */
पूर्णांक phy_speed_up(काष्ठा phy_device *phydev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(adv_पंचांगp);

	अगर (phydev->स्वतःneg != AUTONEG_ENABLE)
		वापस 0;

	अगर (linkmode_empty(phydev->adv_old))
		वापस 0;

	linkmode_copy(adv_पंचांगp, phydev->advertising);
	linkmode_copy(phydev->advertising, phydev->adv_old);
	linkmode_zero(phydev->adv_old);

	अगर (linkmode_equal(phydev->advertising, adv_पंचांगp))
		वापस 0;

	वापस phy_config_aneg(phydev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_speed_up);

/**
 * phy_start_machine - start PHY state machine tracking
 * @phydev: the phy_device काष्ठा
 *
 * Description: The PHY infraकाष्ठाure can run a state machine
 *   which tracks whether the PHY is starting up, negotiating,
 *   etc.  This function starts the delayed workqueue which tracks
 *   the state of the PHY. If you want to मुख्यtain your own state machine,
 *   करो not call this function.
 */
व्योम phy_start_machine(काष्ठा phy_device *phydev)
अणु
	phy_trigger_machine(phydev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_start_machine);

/**
 * phy_stop_machine - stop the PHY state machine tracking
 * @phydev: target phy_device काष्ठा
 *
 * Description: Stops the state machine delayed workqueue, sets the
 *   state to UP (unless it wasn't up yet). This function must be
 *   called BEFORE phy_detach.
 */
व्योम phy_stop_machine(काष्ठा phy_device *phydev)
अणु
	cancel_delayed_work_sync(&phydev->state_queue);

	mutex_lock(&phydev->lock);
	अगर (phy_is_started(phydev))
		phydev->state = PHY_UP;
	mutex_unlock(&phydev->lock);
पूर्ण

/**
 * phy_error - enter HALTED state क्रम this PHY device
 * @phydev: target phy_device काष्ठा
 *
 * Moves the PHY to the HALTED state in response to a पढ़ो
 * or ग_लिखो error, and tells the controller the link is करोwn.
 * Must not be called from पूर्णांकerrupt context, or जबतक the
 * phydev->lock is held.
 */
व्योम phy_error(काष्ठा phy_device *phydev)
अणु
	WARN_ON(1);

	mutex_lock(&phydev->lock);
	phydev->state = PHY_HALTED;
	mutex_unlock(&phydev->lock);

	phy_trigger_machine(phydev);
पूर्ण
EXPORT_SYMBOL(phy_error);

/**
 * phy_disable_पूर्णांकerrupts - Disable the PHY पूर्णांकerrupts from the PHY side
 * @phydev: target phy_device काष्ठा
 */
पूर्णांक phy_disable_पूर्णांकerrupts(काष्ठा phy_device *phydev)
अणु
	/* Disable PHY पूर्णांकerrupts */
	वापस phy_config_पूर्णांकerrupt(phydev, PHY_INTERRUPT_DISABLED);
पूर्ण

/**
 * phy_पूर्णांकerrupt - PHY पूर्णांकerrupt handler
 * @irq: पूर्णांकerrupt line
 * @phy_dat: phy_device poपूर्णांकer
 *
 * Description: Handle PHY पूर्णांकerrupt
 */
अटल irqवापस_t phy_पूर्णांकerrupt(पूर्णांक irq, व्योम *phy_dat)
अणु
	काष्ठा phy_device *phydev = phy_dat;
	काष्ठा phy_driver *drv = phydev->drv;

	वापस drv->handle_पूर्णांकerrupt(phydev);
पूर्ण

/**
 * phy_enable_पूर्णांकerrupts - Enable the पूर्णांकerrupts from the PHY side
 * @phydev: target phy_device काष्ठा
 */
अटल पूर्णांक phy_enable_पूर्णांकerrupts(काष्ठा phy_device *phydev)
अणु
	वापस phy_config_पूर्णांकerrupt(phydev, PHY_INTERRUPT_ENABLED);
पूर्ण

/**
 * phy_request_पूर्णांकerrupt - request and enable पूर्णांकerrupt क्रम a PHY device
 * @phydev: target phy_device काष्ठा
 *
 * Description: Request and enable the पूर्णांकerrupt क्रम the given PHY.
 *   If this fails, then we set irq to PHY_POLL.
 *   This should only be called with a valid IRQ number.
 */
व्योम phy_request_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = request_thपढ़ोed_irq(phydev->irq, शून्य, phy_पूर्णांकerrupt,
				   IRQF_ONESHOT | IRQF_SHARED,
				   phydev_name(phydev), phydev);
	अगर (err) अणु
		phydev_warn(phydev, "Error %d requesting IRQ %d, falling back to polling\n",
			    err, phydev->irq);
		phydev->irq = PHY_POLL;
	पूर्ण अन्यथा अणु
		अगर (phy_enable_पूर्णांकerrupts(phydev)) अणु
			phydev_warn(phydev, "Can't enable interrupt, falling back to polling\n");
			phy_मुक्त_पूर्णांकerrupt(phydev);
			phydev->irq = PHY_POLL;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(phy_request_पूर्णांकerrupt);

/**
 * phy_मुक्त_पूर्णांकerrupt - disable and मुक्त पूर्णांकerrupt क्रम a PHY device
 * @phydev: target phy_device काष्ठा
 *
 * Description: Disable and मुक्त the पूर्णांकerrupt क्रम the given PHY.
 *   This should only be called with a valid IRQ number.
 */
व्योम phy_मुक्त_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	phy_disable_पूर्णांकerrupts(phydev);
	मुक्त_irq(phydev->irq, phydev);
पूर्ण
EXPORT_SYMBOL(phy_मुक्त_पूर्णांकerrupt);

/**
 * phy_stop - Bring करोwn the PHY link, and stop checking the status
 * @phydev: target phy_device काष्ठा
 */
व्योम phy_stop(काष्ठा phy_device *phydev)
अणु
	काष्ठा net_device *dev = phydev->attached_dev;

	अगर (!phy_is_started(phydev) && phydev->state != PHY_DOWN) अणु
		WARN(1, "called from state %s\n",
		     phy_state_to_str(phydev->state));
		वापस;
	पूर्ण

	mutex_lock(&phydev->lock);

	अगर (phydev->state == PHY_CABLETEST) अणु
		phy_पात_cable_test(phydev);
		netअगर_testing_off(dev);
	पूर्ण

	अगर (phydev->sfp_bus)
		sfp_upstream_stop(phydev->sfp_bus);

	phydev->state = PHY_HALTED;

	mutex_unlock(&phydev->lock);

	phy_state_machine(&phydev->state_queue.work);
	phy_stop_machine(phydev);

	/* Cannot call flush_scheduled_work() here as desired because
	 * of rtnl_lock(), but PHY_HALTED shall guarantee irq handler
	 * will not reenable पूर्णांकerrupts.
	 */
पूर्ण
EXPORT_SYMBOL(phy_stop);

/**
 * phy_start - start or restart a PHY device
 * @phydev: target phy_device काष्ठा
 *
 * Description: Indicates the attached device's पढ़ोiness to
 *   handle PHY-related work.  Used during startup to start the
 *   PHY, and after a call to phy_stop() to resume operation.
 *   Also used to indicate the MDIO bus has cleared an error
 *   condition.
 */
व्योम phy_start(काष्ठा phy_device *phydev)
अणु
	mutex_lock(&phydev->lock);

	अगर (phydev->state != PHY_READY && phydev->state != PHY_HALTED) अणु
		WARN(1, "called from state %s\n",
		     phy_state_to_str(phydev->state));
		जाओ out;
	पूर्ण

	अगर (phydev->sfp_bus)
		sfp_upstream_start(phydev->sfp_bus);

	/* अगर phy was suspended, bring the physical link up again */
	__phy_resume(phydev);

	phydev->state = PHY_UP;

	phy_start_machine(phydev);
out:
	mutex_unlock(&phydev->lock);
पूर्ण
EXPORT_SYMBOL(phy_start);

/**
 * phy_state_machine - Handle the state machine
 * @work: work_काष्ठा that describes the work to be करोne
 */
व्योम phy_state_machine(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा phy_device *phydev =
			container_of(dwork, काष्ठा phy_device, state_queue);
	काष्ठा net_device *dev = phydev->attached_dev;
	bool needs_aneg = false, करो_suspend = false;
	क्रमागत phy_state old_state;
	bool finished = false;
	पूर्णांक err = 0;

	mutex_lock(&phydev->lock);

	old_state = phydev->state;

	चयन (phydev->state) अणु
	हाल PHY_DOWN:
	हाल PHY_READY:
		अवरोध;
	हाल PHY_UP:
		needs_aneg = true;

		अवरोध;
	हाल PHY_NOLINK:
	हाल PHY_RUNNING:
		err = phy_check_link_status(phydev);
		अवरोध;
	हाल PHY_CABLETEST:
		err = phydev->drv->cable_test_get_status(phydev, &finished);
		अगर (err) अणु
			phy_पात_cable_test(phydev);
			netअगर_testing_off(dev);
			needs_aneg = true;
			phydev->state = PHY_UP;
			अवरोध;
		पूर्ण

		अगर (finished) अणु
			ethnl_cable_test_finished(phydev);
			netअगर_testing_off(dev);
			needs_aneg = true;
			phydev->state = PHY_UP;
		पूर्ण
		अवरोध;
	हाल PHY_HALTED:
		अगर (phydev->link) अणु
			phydev->link = 0;
			phy_link_करोwn(phydev);
		पूर्ण
		करो_suspend = true;
		अवरोध;
	पूर्ण

	mutex_unlock(&phydev->lock);

	अगर (needs_aneg)
		err = phy_start_aneg(phydev);
	अन्यथा अगर (करो_suspend)
		phy_suspend(phydev);

	अगर (err < 0)
		phy_error(phydev);

	अगर (old_state != phydev->state) अणु
		phydev_dbg(phydev, "PHY state change %s -> %s\n",
			   phy_state_to_str(old_state),
			   phy_state_to_str(phydev->state));
		अगर (phydev->drv && phydev->drv->link_change_notअगरy)
			phydev->drv->link_change_notअगरy(phydev);
	पूर्ण

	/* Only re-schedule a PHY state machine change अगर we are polling the
	 * PHY, अगर PHY_MAC_INTERRUPT is set, then we will be moving
	 * between states from phy_mac_पूर्णांकerrupt().
	 *
	 * In state PHY_HALTED the PHY माला_लो suspended, so rescheduling the
	 * state machine would be poपूर्णांकless and possibly error prone when
	 * called from phy_disconnect() synchronously.
	 */
	mutex_lock(&phydev->lock);
	अगर (phy_polling_mode(phydev) && phy_is_started(phydev))
		phy_queue_state_machine(phydev, PHY_STATE_TIME);
	mutex_unlock(&phydev->lock);
पूर्ण

/**
 * phy_mac_पूर्णांकerrupt - MAC says the link has changed
 * @phydev: phy_device काष्ठा with changed link
 *
 * The MAC layer is able to indicate there has been a change in the PHY link
 * status. Trigger the state machine and work a work queue.
 */
व्योम phy_mac_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	/* Trigger a state machine change */
	phy_trigger_machine(phydev);
पूर्ण
EXPORT_SYMBOL(phy_mac_पूर्णांकerrupt);

अटल व्योम mmd_eee_adv_to_linkmode(अचिन्हित दीर्घ *advertising, u16 eee_adv)
अणु
	linkmode_zero(advertising);

	अगर (eee_adv & MDIO_EEE_100TX)
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				 advertising);
	अगर (eee_adv & MDIO_EEE_1000T)
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 advertising);
	अगर (eee_adv & MDIO_EEE_10GT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
				 advertising);
	अगर (eee_adv & MDIO_EEE_1000KX)
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
				 advertising);
	अगर (eee_adv & MDIO_EEE_10GKX4)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
				 advertising);
	अगर (eee_adv & MDIO_EEE_10GKR)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
				 advertising);
पूर्ण

/**
 * phy_init_eee - init and check the EEE feature
 * @phydev: target phy_device काष्ठा
 * @clk_stop_enable: PHY may stop the घड़ी during LPI
 *
 * Description: it checks अगर the Energy-Efficient Ethernet (EEE)
 * is supported by looking at the MMD रेजिस्टरs 3.20 and 7.60/61
 * and it programs the MMD रेजिस्टर 3.0 setting the "Clock stop enable"
 * bit अगर required.
 */
पूर्णांक phy_init_eee(काष्ठा phy_device *phydev, bool clk_stop_enable)
अणु
	अगर (!phydev->drv)
		वापस -EIO;

	/* According to 802.3az,the EEE is supported only in full duplex-mode.
	 */
	अगर (phydev->duplex == DUPLEX_FULL) अणु
		__ETHTOOL_DECLARE_LINK_MODE_MASK(common);
		__ETHTOOL_DECLARE_LINK_MODE_MASK(lp);
		__ETHTOOL_DECLARE_LINK_MODE_MASK(adv);
		पूर्णांक eee_lp, eee_cap, eee_adv;
		पूर्णांक status;
		u32 cap;

		/* Read phy status to properly get the right settings */
		status = phy_पढ़ो_status(phydev);
		अगर (status)
			वापस status;

		/* First check अगर the EEE ability is supported */
		eee_cap = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_EEE_ABLE);
		अगर (eee_cap <= 0)
			जाओ eee_निकास_err;

		cap = mmd_eee_cap_to_ethtool_sup_t(eee_cap);
		अगर (!cap)
			जाओ eee_निकास_err;

		/* Check which link settings negotiated and verअगरy it in
		 * the EEE advertising रेजिस्टरs.
		 */
		eee_lp = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_LPABLE);
		अगर (eee_lp <= 0)
			जाओ eee_निकास_err;

		eee_adv = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV);
		अगर (eee_adv <= 0)
			जाओ eee_निकास_err;

		mmd_eee_adv_to_linkmode(adv, eee_adv);
		mmd_eee_adv_to_linkmode(lp, eee_lp);
		linkmode_and(common, adv, lp);

		अगर (!phy_check_valid(phydev->speed, phydev->duplex, common))
			जाओ eee_निकास_err;

		अगर (clk_stop_enable)
			/* Configure the PHY to stop receiving xMII
			 * घड़ी जबतक it is संकेतing LPI.
			 */
			phy_set_bits_mmd(phydev, MDIO_MMD_PCS, MDIO_CTRL1,
					 MDIO_PCS_CTRL1_CLKSTOP_EN);

		वापस 0; /* EEE supported */
	पूर्ण
eee_निकास_err:
	वापस -EPROTONOSUPPORT;
पूर्ण
EXPORT_SYMBOL(phy_init_eee);

/**
 * phy_get_eee_err - report the EEE wake error count
 * @phydev: target phy_device काष्ठा
 *
 * Description: it is to report the number of समय where the PHY
 * failed to complete its normal wake sequence.
 */
पूर्णांक phy_get_eee_err(काष्ठा phy_device *phydev)
अणु
	अगर (!phydev->drv)
		वापस -EIO;

	वापस phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_EEE_WK_ERR);
पूर्ण
EXPORT_SYMBOL(phy_get_eee_err);

/**
 * phy_ethtool_get_eee - get EEE supported and status
 * @phydev: target phy_device काष्ठा
 * @data: ethtool_eee data
 *
 * Description: it reportes the Supported/Advertisement/LP Advertisement
 * capabilities.
 */
पूर्णांक phy_ethtool_get_eee(काष्ठा phy_device *phydev, काष्ठा ethtool_eee *data)
अणु
	पूर्णांक val;

	अगर (!phydev->drv)
		वापस -EIO;

	/* Get Supported EEE */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_EEE_ABLE);
	अगर (val < 0)
		वापस val;
	data->supported = mmd_eee_cap_to_ethtool_sup_t(val);

	/* Get advertisement EEE */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV);
	अगर (val < 0)
		वापस val;
	data->advertised = mmd_eee_adv_to_ethtool_adv_t(val);
	data->eee_enabled = !!data->advertised;

	/* Get LP advertisement EEE */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_LPABLE);
	अगर (val < 0)
		वापस val;
	data->lp_advertised = mmd_eee_adv_to_ethtool_adv_t(val);

	data->eee_active = !!(data->advertised & data->lp_advertised);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_get_eee);

/**
 * phy_ethtool_set_eee - set EEE supported and status
 * @phydev: target phy_device काष्ठा
 * @data: ethtool_eee data
 *
 * Description: it is to program the Advertisement EEE रेजिस्टर.
 */
पूर्णांक phy_ethtool_set_eee(काष्ठा phy_device *phydev, काष्ठा ethtool_eee *data)
अणु
	पूर्णांक cap, old_adv, adv = 0, ret;

	अगर (!phydev->drv)
		वापस -EIO;

	/* Get Supported EEE */
	cap = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_EEE_ABLE);
	अगर (cap < 0)
		वापस cap;

	old_adv = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV);
	अगर (old_adv < 0)
		वापस old_adv;

	अगर (data->eee_enabled) अणु
		adv = !data->advertised ? cap :
		      ethtool_adv_to_mmd_eee_adv_t(data->advertised) & cap;
		/* Mask prohibited EEE modes */
		adv &= ~phydev->eee_broken_modes;
	पूर्ण

	अगर (old_adv != adv) अणु
		ret = phy_ग_लिखो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV, adv);
		अगर (ret < 0)
			वापस ret;

		/* Restart स्वतःnegotiation so the new modes get sent to the
		 * link partner.
		 */
		अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
			ret = phy_restart_aneg(phydev);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_set_eee);

/**
 * phy_ethtool_set_wol - Configure Wake On LAN
 *
 * @phydev: target phy_device काष्ठा
 * @wol: Configuration requested
 */
पूर्णांक phy_ethtool_set_wol(काष्ठा phy_device *phydev, काष्ठा ethtool_wolinfo *wol)
अणु
	अगर (phydev->drv && phydev->drv->set_wol)
		वापस phydev->drv->set_wol(phydev, wol);

	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_set_wol);

/**
 * phy_ethtool_get_wol - Get the current Wake On LAN configuration
 *
 * @phydev: target phy_device काष्ठा
 * @wol: Store the current configuration here
 */
व्योम phy_ethtool_get_wol(काष्ठा phy_device *phydev, काष्ठा ethtool_wolinfo *wol)
अणु
	अगर (phydev->drv && phydev->drv->get_wol)
		phydev->drv->get_wol(phydev, wol);
पूर्ण
EXPORT_SYMBOL(phy_ethtool_get_wol);

पूर्णांक phy_ethtool_get_link_ksettings(काष्ठा net_device *ndev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (!phydev)
		वापस -ENODEV;

	phy_ethtool_ksettings_get(phydev, cmd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_ethtool_get_link_ksettings);

पूर्णांक phy_ethtool_set_link_ksettings(काष्ठा net_device *ndev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (!phydev)
		वापस -ENODEV;

	वापस phy_ethtool_ksettings_set(phydev, cmd);
पूर्ण
EXPORT_SYMBOL(phy_ethtool_set_link_ksettings);

/**
 * phy_ethtool_nway_reset - Restart स्वतः negotiation
 * @ndev: Network device to restart स्वतःneg क्रम
 */
पूर्णांक phy_ethtool_nway_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (!phydev)
		वापस -ENODEV;

	अगर (!phydev->drv)
		वापस -EIO;

	वापस phy_restart_aneg(phydev);
पूर्ण
EXPORT_SYMBOL(phy_ethtool_nway_reset);
