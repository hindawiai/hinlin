<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/net/ethernet/ibm/ehea/ehea_ethtool.c
 *
 *  eHEA ethernet device driver क्रम IBM eServer System p
 *
 *  (C) Copyright IBM Corp. 2006
 *
 *  Authors:
 *       Christoph Raisch <raisch@de.ibm.com>
 *       Jan-Bernd Themann <themann@de.ibm.com>
 *       Thomas Klein <tklein@de.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "ehea.h"
#समावेश "ehea_phyp.h"

अटल पूर्णांक ehea_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	u32 supported, advertising;
	u32 speed;
	पूर्णांक ret;

	ret = ehea_sense_port_attr(port);

	अगर (ret)
		वापस ret;

	अगर (netअगर_carrier_ok(dev)) अणु
		चयन (port->port_speed) अणु
		हाल EHEA_SPEED_10M:
			speed = SPEED_10;
			अवरोध;
		हाल EHEA_SPEED_100M:
			speed = SPEED_100;
			अवरोध;
		हाल EHEA_SPEED_1G:
			speed = SPEED_1000;
			अवरोध;
		हाल EHEA_SPEED_10G:
			speed = SPEED_10000;
			अवरोध;
		शेष:
			speed = -1;
			अवरोध; /* BUG */
		पूर्ण
		cmd->base.duplex = port->full_duplex == 1 ?
						     DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	cmd->base.speed = speed;

	अगर (cmd->base.speed == SPEED_10000) अणु
		supported = (SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE);
		advertising = (ADVERTISED_10000baseT_Full | ADVERTISED_FIBRE);
		cmd->base.port = PORT_FIBRE;
	पूर्ण अन्यथा अणु
		supported = (SUPPORTED_1000baseT_Full | SUPPORTED_100baseT_Full
			       | SUPPORTED_100baseT_Half | SUPPORTED_10baseT_Full
			       | SUPPORTED_10baseT_Half | SUPPORTED_Autoneg
			       | SUPPORTED_TP);
		advertising = (ADVERTISED_1000baseT_Full | ADVERTISED_Autoneg
				 | ADVERTISED_TP);
		cmd->base.port = PORT_TP;
	पूर्ण

	cmd->base.स्वतःneg = port->स्वतःneg == 1 ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक ehea_set_link_ksettings(काष्ठा net_device *dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	पूर्णांक ret = 0;
	u32 sp;

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		sp = EHEA_SPEED_AUTONEG;
		जाओ करोit;
	पूर्ण

	चयन (cmd->base.speed) अणु
	हाल SPEED_10:
		अगर (cmd->base.duplex == DUPLEX_FULL)
			sp = H_SPEED_10M_F;
		अन्यथा
			sp = H_SPEED_10M_H;
		अवरोध;

	हाल SPEED_100:
		अगर (cmd->base.duplex == DUPLEX_FULL)
			sp = H_SPEED_100M_F;
		अन्यथा
			sp = H_SPEED_100M_H;
		अवरोध;

	हाल SPEED_1000:
		अगर (cmd->base.duplex == DUPLEX_FULL)
			sp = H_SPEED_1G_F;
		अन्यथा
			ret = -EINVAL;
		अवरोध;

	हाल SPEED_10000:
		अगर (cmd->base.duplex == DUPLEX_FULL)
			sp = H_SPEED_10G_F;
		अन्यथा
			ret = -EINVAL;
		अवरोध;

	शेष:
			ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		जाओ out;
करोit:
	ret = ehea_set_portspeed(port, sp);

	अगर (!ret)
		netdev_info(dev,
			    "Port speed successfully set: %dMbps %s Duplex\n",
			    port->port_speed,
			    port->full_duplex == 1 ? "Full" : "Half");
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ehea_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	पूर्णांक ret;

	ret = ehea_set_portspeed(port, EHEA_SPEED_AUTONEG);

	अगर (!ret)
		netdev_info(port->netdev,
			    "Port speed successfully set: %dMbps %s Duplex\n",
			    port->port_speed,
			    port->full_duplex == 1 ? "Full" : "Half");
	वापस ret;
पूर्ण

अटल व्योम ehea_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
पूर्ण

अटल u32 ehea_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	वापस port->msg_enable;
पूर्ण

अटल व्योम ehea_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा ehea_port *port = netdev_priv(dev);
	port->msg_enable = value;
पूर्ण

अटल स्थिर अक्षर ehea_ethtool_stats_keys[][ETH_GSTRING_LEN] = अणु
	अणु"sig_comp_iv"पूर्ण,
	अणु"swqe_refill_th"पूर्ण,
	अणु"port resets"पूर्ण,
	अणु"Receive errors"पूर्ण,
	अणु"TCP cksum errors"पूर्ण,
	अणु"IP cksum errors"पूर्ण,
	अणु"Frame cksum errors"पूर्ण,
	अणु"num SQ stopped"पूर्ण,
	अणु"PR0 free_swqes"पूर्ण,
	अणु"PR1 free_swqes"पूर्ण,
	अणु"PR2 free_swqes"पूर्ण,
	अणु"PR3 free_swqes"पूर्ण,
	अणु"PR4 free_swqes"पूर्ण,
	अणु"PR5 free_swqes"पूर्ण,
	अणु"PR6 free_swqes"पूर्ण,
	अणु"PR7 free_swqes"पूर्ण,
	अणु"PR8 free_swqes"पूर्ण,
	अणु"PR9 free_swqes"पूर्ण,
	अणु"PR10 free_swqes"पूर्ण,
	अणु"PR11 free_swqes"पूर्ण,
	अणु"PR12 free_swqes"पूर्ण,
	अणु"PR13 free_swqes"पूर्ण,
	अणु"PR14 free_swqes"पूर्ण,
	अणु"PR15 free_swqes"पूर्ण,
पूर्ण;

अटल व्योम ehea_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	अगर (stringset == ETH_SS_STATS) अणु
		स_नकल(data, &ehea_ethtool_stats_keys,
		       माप(ehea_ethtool_stats_keys));
	पूर्ण
पूर्ण

अटल पूर्णांक ehea_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(ehea_ethtool_stats_keys);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम ehea_get_ethtool_stats(काष्ठा net_device *dev,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक i, k, पंचांगp;
	काष्ठा ehea_port *port = netdev_priv(dev);

	क्रम (i = 0; i < ehea_get_sset_count(dev, ETH_SS_STATS); i++)
		data[i] = 0;
	i = 0;

	data[i++] = port->sig_comp_iv;
	data[i++] = port->port_res[0].swqe_refill_th;
	data[i++] = port->resets;

	क्रम (k = 0, पंचांगp = 0; k < EHEA_MAX_PORT_RES; k++)
		पंचांगp += port->port_res[k].p_stats.poll_receive_errors;
	data[i++] = पंचांगp;

	क्रम (k = 0, पंचांगp = 0; k < EHEA_MAX_PORT_RES; k++)
		पंचांगp += port->port_res[k].p_stats.err_tcp_cksum;
	data[i++] = पंचांगp;

	क्रम (k = 0, पंचांगp = 0; k < EHEA_MAX_PORT_RES; k++)
		पंचांगp += port->port_res[k].p_stats.err_ip_cksum;
	data[i++] = पंचांगp;

	क्रम (k = 0, पंचांगp = 0; k < EHEA_MAX_PORT_RES; k++)
		पंचांगp += port->port_res[k].p_stats.err_frame_crc;
	data[i++] = पंचांगp;

	क्रम (k = 0, पंचांगp = 0; k < EHEA_MAX_PORT_RES; k++)
		पंचांगp += port->port_res[k].p_stats.queue_stopped;
	data[i++] = पंचांगp;

	क्रम (k = 0; k < 16; k++)
		data[i++] = atomic_पढ़ो(&port->port_res[k].swqe_avail);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ehea_ethtool_ops = अणु
	.get_drvinfo = ehea_get_drvinfo,
	.get_msglevel = ehea_get_msglevel,
	.set_msglevel = ehea_set_msglevel,
	.get_link = ethtool_op_get_link,
	.get_strings = ehea_get_strings,
	.get_sset_count = ehea_get_sset_count,
	.get_ethtool_stats = ehea_get_ethtool_stats,
	.nway_reset = ehea_nway_reset,		/* Restart स्वतःnegotiation */
	.get_link_ksettings = ehea_get_link_ksettings,
	.set_link_ksettings = ehea_set_link_ksettings,
पूर्ण;

व्योम ehea_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &ehea_ethtool_ops;
पूर्ण
