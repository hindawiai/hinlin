<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DPAA2 Ethernet Switch ethtool support
 *
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2018 NXP
 *
 */

#समावेश <linux/ethtool.h>

#समावेश "dpaa2-switch.h"

अटल काष्ठा अणु
	क्रमागत dpsw_counter id;
	अक्षर name[ETH_GSTRING_LEN];
पूर्ण dpaa2_चयन_ethtool_counters[] =  अणु
	अणुDPSW_CNT_ING_FRAME,		"rx frames"पूर्ण,
	अणुDPSW_CNT_ING_BYTE,		"rx bytes"पूर्ण,
	अणुDPSW_CNT_ING_FLTR_FRAME,	"rx filtered frames"पूर्ण,
	अणुDPSW_CNT_ING_FRAME_DISCARD,	"rx discarded frames"पूर्ण,
	अणुDPSW_CNT_ING_BCAST_FRAME,	"rx b-cast frames"पूर्ण,
	अणुDPSW_CNT_ING_BCAST_BYTES,	"rx b-cast bytes"पूर्ण,
	अणुDPSW_CNT_ING_MCAST_FRAME,	"rx m-cast frames"पूर्ण,
	अणुDPSW_CNT_ING_MCAST_BYTE,	"rx m-cast bytes"पूर्ण,
	अणुDPSW_CNT_EGR_FRAME,		"tx frames"पूर्ण,
	अणुDPSW_CNT_EGR_BYTE,		"tx bytes"पूर्ण,
	अणुDPSW_CNT_EGR_FRAME_DISCARD,	"tx discarded frames"पूर्ण,
	अणुDPSW_CNT_ING_NO_BUFF_DISCARD,	"rx discarded no buffer frames"पूर्ण,
पूर्ण;

#घोषणा DPAA2_SWITCH_NUM_COUNTERS	ARRAY_SIZE(dpaa2_चयन_ethtool_counters)

अटल व्योम dpaa2_चयन_get_drvinfo(काष्ठा net_device *netdev,
				     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	u16 version_major, version_minor;
	पूर्णांक err;

	strscpy(drvinfo->driver, KBUILD_MODNAME, माप(drvinfo->driver));

	err = dpsw_get_api_version(port_priv->ethsw_data->mc_io, 0,
				   &version_major,
				   &version_minor);
	अगर (err)
		strscpy(drvinfo->fw_version, "N/A",
			माप(drvinfo->fw_version));
	अन्यथा
		snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
			 "%u.%u", version_major, version_minor);

	strscpy(drvinfo->bus_info, dev_name(netdev->dev.parent->parent),
		माप(drvinfo->bus_info));
पूर्ण

अटल पूर्णांक
dpaa2_चयन_get_link_ksettings(काष्ठा net_device *netdev,
				काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा dpsw_link_state state = अणु0पूर्ण;
	पूर्णांक err = 0;

	err = dpsw_अगर_get_link_state(port_priv->ethsw_data->mc_io, 0,
				     port_priv->ethsw_data->dpsw_handle,
				     port_priv->idx,
				     &state);
	अगर (err) अणु
		netdev_err(netdev, "ERROR %d getting link state\n", err);
		जाओ out;
	पूर्ण

	/* At the moment, we have no way of पूर्णांकerrogating the DPMAC
	 * from the DPSW side or there may not exist a DPMAC at all.
	 * Report only स्वतःneg state, duplनिकासy and speed.
	 */
	अगर (state.options & DPSW_LINK_OPT_AUTONEG)
		link_ksettings->base.स्वतःneg = AUTONEG_ENABLE;
	अगर (!(state.options & DPSW_LINK_OPT_HALF_DUPLEX))
		link_ksettings->base.duplex = DUPLEX_FULL;
	link_ksettings->base.speed = state.rate;

out:
	वापस err;
पूर्ण

अटल पूर्णांक
dpaa2_चयन_set_link_ksettings(काष्ठा net_device *netdev,
				स्थिर काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	काष्ठा ethsw_core *ethsw = port_priv->ethsw_data;
	काष्ठा dpsw_link_cfg cfg = अणु0पूर्ण;
	bool अगर_running;
	पूर्णांक err = 0, ret;

	/* Interface needs to be करोwn to change link settings */
	अगर_running = netअगर_running(netdev);
	अगर (अगर_running) अणु
		err = dpsw_अगर_disable(ethsw->mc_io, 0,
				      ethsw->dpsw_handle,
				      port_priv->idx);
		अगर (err) अणु
			netdev_err(netdev, "dpsw_if_disable err %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	cfg.rate = link_ksettings->base.speed;
	अगर (link_ksettings->base.स्वतःneg == AUTONEG_ENABLE)
		cfg.options |= DPSW_LINK_OPT_AUTONEG;
	अन्यथा
		cfg.options &= ~DPSW_LINK_OPT_AUTONEG;
	अगर (link_ksettings->base.duplex  == DUPLEX_HALF)
		cfg.options |= DPSW_LINK_OPT_HALF_DUPLEX;
	अन्यथा
		cfg.options &= ~DPSW_LINK_OPT_HALF_DUPLEX;

	err = dpsw_अगर_set_link_cfg(port_priv->ethsw_data->mc_io, 0,
				   port_priv->ethsw_data->dpsw_handle,
				   port_priv->idx,
				   &cfg);

	अगर (अगर_running) अणु
		ret = dpsw_अगर_enable(ethsw->mc_io, 0,
				     ethsw->dpsw_handle,
				     port_priv->idx);
		अगर (ret) अणु
			netdev_err(netdev, "dpsw_if_enable err %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_चयन_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस DPAA2_SWITCH_NUM_COUNTERS;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम dpaa2_चयन_ethtool_get_strings(काष्ठा net_device *netdev,
					     u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < DPAA2_SWITCH_NUM_COUNTERS; i++)
			स_नकल(data + i * ETH_GSTRING_LEN,
			       dpaa2_चयन_ethtool_counters[i].name,
			       ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dpaa2_चयन_ethtool_get_stats(काष्ठा net_device *netdev,
					   काष्ठा ethtool_stats *stats,
					   u64 *data)
अणु
	काष्ठा ethsw_port_priv *port_priv = netdev_priv(netdev);
	पूर्णांक i, err;

	क्रम (i = 0; i < DPAA2_SWITCH_NUM_COUNTERS; i++) अणु
		err = dpsw_अगर_get_counter(port_priv->ethsw_data->mc_io, 0,
					  port_priv->ethsw_data->dpsw_handle,
					  port_priv->idx,
					  dpaa2_चयन_ethtool_counters[i].id,
					  &data[i]);
		अगर (err)
			netdev_err(netdev, "dpsw_if_get_counter[%s] err %d\n",
				   dpaa2_चयन_ethtool_counters[i].name, err);
	पूर्ण
पूर्ण

स्थिर काष्ठा ethtool_ops dpaa2_चयन_port_ethtool_ops = अणु
	.get_drvinfo		= dpaa2_चयन_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= dpaa2_चयन_get_link_ksettings,
	.set_link_ksettings	= dpaa2_चयन_set_link_ksettings,
	.get_strings		= dpaa2_चयन_ethtool_get_strings,
	.get_ethtool_stats	= dpaa2_चयन_ethtool_get_stats,
	.get_sset_count		= dpaa2_चयन_ethtool_get_sset_count,
पूर्ण;
