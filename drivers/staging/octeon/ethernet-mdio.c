<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

#समावेश <linux/kernel.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/of_mdपन.स>
#समावेश <generated/utsrelease.h>
#समावेश <net/dst.h>

#समावेश "octeon-ethernet.h"
#समावेश "ethernet-defines.h"
#समावेश "ethernet-mdio.h"
#समावेश "ethernet-util.h"

अटल व्योम cvm_oct_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *info)
अणु
	strscpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strscpy(info->version, UTS_RELEASE, माप(info->version));
	strscpy(info->bus_info, "Builtin", माप(info->bus_info));
पूर्ण

अटल पूर्णांक cvm_oct_nway_reset(काष्ठा net_device *dev)
अणु
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (dev->phydev)
		वापस phy_start_aneg(dev->phydev);

	वापस -EINVAL;
पूर्ण

स्थिर काष्ठा ethtool_ops cvm_oct_ethtool_ops = अणु
	.get_drvinfo = cvm_oct_get_drvinfo,
	.nway_reset = cvm_oct_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

/**
 * cvm_oct_ioctl - IOCTL support क्रम PHY control
 * @dev:    Device to change
 * @rq:     the request
 * @cmd:    the command
 *
 * Returns Zero on success
 */
पूर्णांक cvm_oct_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (!dev->phydev)
		वापस -EINVAL;

	वापस phy_mii_ioctl(dev->phydev, rq, cmd);
पूर्ण

व्योम cvm_oct_note_carrier(काष्ठा octeon_ethernet *priv,
			  जोड़ cvmx_helper_link_info li)
अणु
	अगर (li.s.link_up) अणु
		pr_notice_ratelimited("%s: %u Mbps %s duplex, port %d, queue %d\n",
				      netdev_name(priv->netdev), li.s.speed,
				      (li.s.full_duplex) ? "Full" : "Half",
				      priv->port, priv->queue);
	पूर्ण अन्यथा अणु
		pr_notice_ratelimited("%s: Link down\n",
				      netdev_name(priv->netdev));
	पूर्ण
पूर्ण

व्योम cvm_oct_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	जोड़ cvmx_helper_link_info link_info;

	link_info.u64		= 0;
	link_info.s.link_up	= dev->phydev->link ? 1 : 0;
	link_info.s.full_duplex = dev->phydev->duplex ? 1 : 0;
	link_info.s.speed	= dev->phydev->speed;
	priv->link_info		= link_info.u64;

	/*
	 * The polling task need to know about link status changes.
	 */
	अगर (priv->poll)
		priv->poll(dev);

	अगर (priv->last_link != dev->phydev->link) अणु
		priv->last_link = dev->phydev->link;
		cvmx_helper_link_set(priv->port, link_info);
		cvm_oct_note_carrier(priv, link_info);
	पूर्ण
पूर्ण

पूर्णांक cvm_oct_common_stop(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	पूर्णांक पूर्णांकerface = INTERFACE(priv->port);
	जोड़ cvmx_helper_link_info link_info;
	जोड़ cvmx_gmxx_prtx_cfg gmx_cfg;
	पूर्णांक index = INDEX(priv->port);

	gmx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
	gmx_cfg.s.en = 0;
	cvmx_ग_लिखो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface), gmx_cfg.u64);

	priv->poll = शून्य;

	अगर (dev->phydev)
		phy_disconnect(dev->phydev);

	अगर (priv->last_link) अणु
		link_info.u64 = 0;
		priv->last_link = 0;

		cvmx_helper_link_set(priv->port, link_info);
		cvm_oct_note_carrier(priv, link_info);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * cvm_oct_phy_setup_device - setup the PHY
 *
 * @dev:    Device to setup
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक cvm_oct_phy_setup_device(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	काष्ठा device_node *phy_node;
	काष्ठा phy_device *phydev = शून्य;

	अगर (!priv->of_node)
		जाओ no_phy;

	phy_node = of_parse_phandle(priv->of_node, "phy-handle", 0);
	अगर (!phy_node && of_phy_is_fixed_link(priv->of_node))
		phy_node = of_node_get(priv->of_node);
	अगर (!phy_node)
		जाओ no_phy;

	phydev = of_phy_connect(dev, phy_node, cvm_oct_adjust_link, 0,
				priv->phy_mode);
	of_node_put(phy_node);

	अगर (!phydev)
		वापस -EPROBE_DEFER;

	priv->last_link = 0;
	phy_start(phydev);

	वापस 0;
no_phy:
	/* If there is no phy, assume a direct MAC connection and that
	 * the link is up.
	 */
	netअगर_carrier_on(dev);
	वापस 0;
पूर्ण
