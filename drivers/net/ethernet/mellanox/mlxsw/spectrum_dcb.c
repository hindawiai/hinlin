<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2016-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <net/dcbnl.h>

#समावेश "spectrum.h"
#समावेश "reg.h"

अटल u8 mlxsw_sp_dcbnl_getdcbx(काष्ठा net_device __always_unused *dev)
अणु
	वापस DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VER_IEEE;
पूर्ण

अटल u8 mlxsw_sp_dcbnl_setdcbx(काष्ठा net_device __always_unused *dev,
				 u8 mode)
अणु
	वापस (mode != (DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VER_IEEE)) ? 1 : 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_ieee_getets(काष्ठा net_device *dev,
				      काष्ठा ieee_ets *ets)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	स_नकल(ets, mlxsw_sp_port->dcb.ets, माप(*ets));

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_ets_validate(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      काष्ठा ieee_ets *ets)
अणु
	काष्ठा net_device *dev = mlxsw_sp_port->dev;
	bool has_ets_tc = false;
	पूर्णांक i, tx_bw_sum = 0;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_STRICT:
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			has_ets_tc = true;
			tx_bw_sum += ets->tc_tx_bw[i];
			अवरोध;
		शेष:
			netdev_err(dev, "Only strict priority and ETS are supported\n");
			वापस -EINVAL;
		पूर्ण

		अगर (ets->prio_tc[i] >= IEEE_8021QAZ_MAX_TCS) अणु
			netdev_err(dev, "Invalid TC\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (has_ets_tc && tx_bw_sum != 100) अणु
		netdev_err(dev, "Total ETS bandwidth should equal 100\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_headroom_ets_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					  काष्ठा ieee_ets *ets)
अणु
	काष्ठा net_device *dev = mlxsw_sp_port->dev;
	काष्ठा mlxsw_sp_hdroom hdroom;
	पूर्णांक prio;
	पूर्णांक err;

	hdroom = *mlxsw_sp_port->hdroom;
	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++)
		hdroom.prios.prio[prio].ets_buf_idx = ets->prio_tc[prio];
	mlxsw_sp_hdroom_prios_reset_buf_idx(&hdroom);
	mlxsw_sp_hdroom_bufs_reset_lossiness(&hdroom);
	mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);

	err = mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom);
	अगर (err) अणु
		netdev_err(dev, "Failed to configure port's headroom\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __mlxsw_sp_dcbnl_ieee_setets(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					काष्ठा ieee_ets *ets)
अणु
	काष्ठा ieee_ets *my_ets = mlxsw_sp_port->dcb.ets;
	काष्ठा net_device *dev = mlxsw_sp_port->dev;
	पूर्णांक i, err;

	/* Egress configuration. */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		bool dwrr = ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS;
		u8 weight = ets->tc_tx_bw[i];

		err = mlxsw_sp_port_ets_set(mlxsw_sp_port,
					    MLXSW_REG_QEEC_HR_SUBGROUP, i,
					    0, dwrr, weight);
		अगर (err) अणु
			netdev_err(dev, "Failed to link subgroup ETS element %d to group\n",
				   i);
			जाओ err_port_ets_set;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_prio_tc_set(mlxsw_sp_port, i,
						ets->prio_tc[i]);
		अगर (err) अणु
			netdev_err(dev, "Failed to map prio %d to TC %d\n", i,
				   ets->prio_tc[i]);
			जाओ err_port_prio_tc_set;
		पूर्ण
	पूर्ण

	/* Ingress configuration. */
	err = mlxsw_sp_port_headroom_ets_set(mlxsw_sp_port, ets);
	अगर (err)
		जाओ err_port_headroom_set;

	वापस 0;

err_port_headroom_set:
	i = IEEE_8021QAZ_MAX_TCS;
err_port_prio_tc_set:
	क्रम (i--; i >= 0; i--)
		mlxsw_sp_port_prio_tc_set(mlxsw_sp_port, i, my_ets->prio_tc[i]);
	i = IEEE_8021QAZ_MAX_TCS;
err_port_ets_set:
	क्रम (i--; i >= 0; i--) अणु
		bool dwrr = my_ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS;
		u8 weight = my_ets->tc_tx_bw[i];

		err = mlxsw_sp_port_ets_set(mlxsw_sp_port,
					    MLXSW_REG_QEEC_HR_SUBGROUP, i,
					    0, dwrr, weight);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_ieee_setets(काष्ठा net_device *dev,
				      काष्ठा ieee_ets *ets)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक err;

	err = mlxsw_sp_port_ets_validate(mlxsw_sp_port, ets);
	अगर (err)
		वापस err;

	err = __mlxsw_sp_dcbnl_ieee_setets(mlxsw_sp_port, ets);
	अगर (err)
		वापस err;

	स_नकल(mlxsw_sp_port->dcb.ets, ets, माप(*ets));
	mlxsw_sp_port->dcb.ets->ets_cap = IEEE_8021QAZ_MAX_TCS;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_app_validate(काष्ठा net_device *dev,
				       काष्ठा dcb_app *app)
अणु
	पूर्णांक prio;

	अगर (app->priority >= IEEE_8021QAZ_MAX_TCS) अणु
		netdev_err(dev, "APP entry with priority value %u is invalid\n",
			   app->priority);
		वापस -EINVAL;
	पूर्ण

	चयन (app->selector) अणु
	हाल IEEE_8021QAZ_APP_SEL_DSCP:
		अगर (app->protocol >= 64) अणु
			netdev_err(dev, "DSCP APP entry with protocol value %u is invalid\n",
				   app->protocol);
			वापस -EINVAL;
		पूर्ण

		/* Warn about any DSCP APP entries with the same PID. */
		prio = fls(dcb_ieee_getapp_mask(dev, app));
		अगर (prio--) अणु
			अगर (prio < app->priority)
				netdev_warn(dev, "Choosing priority %d for DSCP %d in favor of previously-active value of %d\n",
					    app->priority, app->protocol, prio);
			अन्यथा अगर (prio > app->priority)
				netdev_warn(dev, "Ignoring new priority %d for DSCP %d in favor of current value of %d\n",
					    app->priority, app->protocol, prio);
		पूर्ण
		अवरोध;

	हाल IEEE_8021QAZ_APP_SEL_ETHERTYPE:
		अगर (app->protocol) अणु
			netdev_err(dev, "EtherType APP entries with protocol value != 0 not supported\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		netdev_err(dev, "APP entries with selector %u not supported\n",
			   app->selector);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8
mlxsw_sp_port_dcb_app_शेष_prio(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	u8 prio_mask;

	prio_mask = dcb_ieee_getapp_शेष_prio_mask(mlxsw_sp_port->dev);
	अगर (prio_mask)
		/* Take the highest configured priority. */
		वापस fls(prio_mask) - 1;

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_port_dcb_app_dscp_prio_map(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    u8 शेष_prio,
				    काष्ठा dcb_ieee_app_dscp_map *map)
अणु
	पूर्णांक i;

	dcb_ieee_getapp_dscp_prio_mask_map(mlxsw_sp_port->dev, map);
	क्रम (i = 0; i < ARRAY_SIZE(map->map); ++i) अणु
		अगर (map->map[i])
			map->map[i] = fls(map->map[i]) - 1;
		अन्यथा
			map->map[i] = शेष_prio;
	पूर्ण
पूर्ण

अटल bool
mlxsw_sp_port_dcb_app_prio_dscp_map(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    काष्ठा dcb_ieee_app_prio_map *map)
अणु
	bool have_dscp = false;
	पूर्णांक i;

	dcb_ieee_getapp_prio_dscp_mask_map(mlxsw_sp_port->dev, map);
	क्रम (i = 0; i < ARRAY_SIZE(map->map); ++i) अणु
		अगर (map->map[i]) अणु
			map->map[i] = fls64(map->map[i]) - 1;
			have_dscp = true;
		पूर्ण
	पूर्ण

	वापस have_dscp;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_dcb_app_update_qpts(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  क्रमागत mlxsw_reg_qpts_trust_state ts)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qpts_pl[MLXSW_REG_QPTS_LEN];

	mlxsw_reg_qpts_pack(qpts_pl, mlxsw_sp_port->local_port, ts);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qpts), qpts_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_dcb_app_update_qrwe(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  bool reग_लिखो_dscp)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qrwe_pl[MLXSW_REG_QRWE_LEN];

	mlxsw_reg_qrwe_pack(qrwe_pl, mlxsw_sp_port->local_port,
			    false, reग_लिखो_dscp);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qrwe), qrwe_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_dcb_toggle_trust(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       क्रमागत mlxsw_reg_qpts_trust_state ts)
अणु
	bool reग_लिखो_dscp = ts == MLXSW_REG_QPTS_TRUST_STATE_DSCP;
	पूर्णांक err;

	अगर (mlxsw_sp_port->dcb.trust_state == ts)
		वापस 0;

	err = mlxsw_sp_port_dcb_app_update_qpts(mlxsw_sp_port, ts);
	अगर (err)
		वापस err;

	err = mlxsw_sp_port_dcb_app_update_qrwe(mlxsw_sp_port, reग_लिखो_dscp);
	अगर (err)
		जाओ err_update_qrwe;

	mlxsw_sp_port->dcb.trust_state = ts;
	वापस 0;

err_update_qrwe:
	mlxsw_sp_port_dcb_app_update_qpts(mlxsw_sp_port,
					  mlxsw_sp_port->dcb.trust_state);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_dcb_app_update_qpdp(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  u8 शेष_prio)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qpdp_pl[MLXSW_REG_QPDP_LEN];

	mlxsw_reg_qpdp_pack(qpdp_pl, mlxsw_sp_port->local_port, शेष_prio);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qpdp), qpdp_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_dcb_app_update_qpdpm(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा dcb_ieee_app_dscp_map *map)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qpdpm_pl[MLXSW_REG_QPDPM_LEN];
	लघु पूर्णांक i;

	mlxsw_reg_qpdpm_pack(qpdpm_pl, mlxsw_sp_port->local_port);
	क्रम (i = 0; i < ARRAY_SIZE(map->map); ++i)
		mlxsw_reg_qpdpm_dscp_pack(qpdpm_pl, i, map->map[i]);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qpdpm), qpdpm_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_dcb_app_update_qpdsm(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा dcb_ieee_app_prio_map *map)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qpdsm_pl[MLXSW_REG_QPDSM_LEN];
	लघु पूर्णांक i;

	mlxsw_reg_qpdsm_pack(qpdsm_pl, mlxsw_sp_port->local_port);
	क्रम (i = 0; i < ARRAY_SIZE(map->map); ++i)
		mlxsw_reg_qpdsm_prio_pack(qpdsm_pl, i, map->map[i]);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qpdsm), qpdsm_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_dcb_app_update(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा dcb_ieee_app_prio_map prio_map;
	काष्ठा dcb_ieee_app_dscp_map dscp_map;
	u8 शेष_prio;
	bool have_dscp;
	पूर्णांक err;

	शेष_prio = mlxsw_sp_port_dcb_app_शेष_prio(mlxsw_sp_port);
	err = mlxsw_sp_port_dcb_app_update_qpdp(mlxsw_sp_port, शेष_prio);
	अगर (err) अणु
		netdev_err(mlxsw_sp_port->dev, "Couldn't configure port default priority\n");
		वापस err;
	पूर्ण

	have_dscp = mlxsw_sp_port_dcb_app_prio_dscp_map(mlxsw_sp_port,
							&prio_map);

	mlxsw_sp_port_dcb_app_dscp_prio_map(mlxsw_sp_port, शेष_prio,
					    &dscp_map);
	err = mlxsw_sp_port_dcb_app_update_qpdpm(mlxsw_sp_port,
						 &dscp_map);
	अगर (err) अणु
		netdev_err(mlxsw_sp_port->dev, "Couldn't configure priority map\n");
		वापस err;
	पूर्ण

	err = mlxsw_sp_port_dcb_app_update_qpdsm(mlxsw_sp_port,
						 &prio_map);
	अगर (err) अणु
		netdev_err(mlxsw_sp_port->dev, "Couldn't configure DSCP rewrite map\n");
		वापस err;
	पूर्ण

	अगर (!have_dscp) अणु
		err = mlxsw_sp_port_dcb_toggle_trust(mlxsw_sp_port,
					MLXSW_REG_QPTS_TRUST_STATE_PCP);
		अगर (err)
			netdev_err(mlxsw_sp_port->dev, "Couldn't switch to trust L2\n");
		वापस err;
	पूर्ण

	err = mlxsw_sp_port_dcb_toggle_trust(mlxsw_sp_port,
					     MLXSW_REG_QPTS_TRUST_STATE_DSCP);
	अगर (err) अणु
		/* A failure to set trust DSCP means that the QPDPM and QPDSM
		 * maps installed above are not in effect. And since we are here
		 * attempting to set trust DSCP, we couldn't have attempted to
		 * चयन trust to PCP. Thus no cleanup is necessary.
		 */
		netdev_err(mlxsw_sp_port->dev, "Couldn't switch to trust L3\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_ieee_setapp(काष्ठा net_device *dev,
				      काष्ठा dcb_app *app)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक err;

	err = mlxsw_sp_dcbnl_app_validate(dev, app);
	अगर (err)
		वापस err;

	err = dcb_ieee_setapp(dev, app);
	अगर (err)
		वापस err;

	err = mlxsw_sp_port_dcb_app_update(mlxsw_sp_port);
	अगर (err)
		जाओ err_update;

	वापस 0;

err_update:
	dcb_ieee_delapp(dev, app);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_ieee_delapp(काष्ठा net_device *dev,
				      काष्ठा dcb_app *app)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक err;

	err = dcb_ieee_delapp(dev, app);
	अगर (err)
		वापस err;

	err = mlxsw_sp_port_dcb_app_update(mlxsw_sp_port);
	अगर (err)
		netdev_err(dev, "Failed to update DCB APP configuration\n");
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_ieee_geपंचांगaxrate(काष्ठा net_device *dev,
					  काष्ठा ieee_maxrate *maxrate)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	स_नकल(maxrate, mlxsw_sp_port->dcb.maxrate, माप(*maxrate));

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_ieee_seपंचांगaxrate(काष्ठा net_device *dev,
					  काष्ठा ieee_maxrate *maxrate)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा ieee_maxrate *my_maxrate = mlxsw_sp_port->dcb.maxrate;
	पूर्णांक err, i;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
						    MLXSW_REG_QEEC_HR_SUBGROUP,
						    i, 0,
						    maxrate->tc_maxrate[i], 0);
		अगर (err) अणु
			netdev_err(dev, "Failed to set maxrate for TC %d\n", i);
			जाओ err_port_ets_maxrate_set;
		पूर्ण
	पूर्ण

	स_नकल(mlxsw_sp_port->dcb.maxrate, maxrate, माप(*maxrate));

	वापस 0;

err_port_ets_maxrate_set:
	क्रम (i--; i >= 0; i--)
		mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
					      MLXSW_REG_QEEC_HR_SUBGROUP,
					      i, 0,
					      my_maxrate->tc_maxrate[i], 0);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_pfc_cnt_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     u8 prio)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा ieee_pfc *my_pfc = mlxsw_sp_port->dcb.pfc;
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];
	पूर्णांक err;

	mlxsw_reg_ppcnt_pack(ppcnt_pl, mlxsw_sp_port->local_port,
			     MLXSW_REG_PPCNT_PRIO_CNT, prio);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ppcnt), ppcnt_pl);
	अगर (err)
		वापस err;

	my_pfc->requests[prio] = mlxsw_reg_ppcnt_tx_छोड़ो_get(ppcnt_pl);
	my_pfc->indications[prio] = mlxsw_reg_ppcnt_rx_छोड़ो_get(ppcnt_pl);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_ieee_getpfc(काष्ठा net_device *dev,
				      काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक err, i;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		err = mlxsw_sp_port_pfc_cnt_get(mlxsw_sp_port, i);
		अगर (err) अणु
			netdev_err(dev, "Failed to get PFC count for priority %d\n",
				   i);
			वापस err;
		पूर्ण
	पूर्ण

	स_नकल(pfc, mlxsw_sp_port->dcb.pfc, माप(*pfc));

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_pfc_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 काष्ठा ieee_pfc *pfc)
अणु
	अक्षर pfcc_pl[MLXSW_REG_PFCC_LEN];

	mlxsw_reg_pfcc_pack(pfcc_pl, mlxsw_sp_port->local_port);
	mlxsw_reg_pfcc_pprx_set(pfcc_pl, mlxsw_sp_port->link.rx_छोड़ो);
	mlxsw_reg_pfcc_pptx_set(pfcc_pl, mlxsw_sp_port->link.tx_छोड़ो);
	mlxsw_reg_pfcc_prio_pack(pfcc_pl, pfc->pfc_en);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(pfcc),
			       pfcc_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_ieee_setpfc(काष्ठा net_device *dev,
				      काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	bool छोड़ो_en = mlxsw_sp_port_is_छोड़ो_en(mlxsw_sp_port);
	काष्ठा mlxsw_sp_hdroom orig_hdroom;
	काष्ठा mlxsw_sp_hdroom hdroom;
	पूर्णांक prio;
	पूर्णांक err;

	अगर (छोड़ो_en && pfc->pfc_en) अणु
		netdev_err(dev, "PAUSE frames already enabled on port\n");
		वापस -EINVAL;
	पूर्ण

	orig_hdroom = *mlxsw_sp_port->hdroom;

	hdroom = orig_hdroom;
	अगर (pfc->pfc_en)
		hdroom.delay_bytes = DIV_ROUND_UP(pfc->delay, BITS_PER_BYTE);
	अन्यथा
		hdroom.delay_bytes = 0;

	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++)
		hdroom.prios.prio[prio].lossy = !(pfc->pfc_en & BIT(prio));

	mlxsw_sp_hdroom_bufs_reset_lossiness(&hdroom);
	mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);

	err = mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom);
	अगर (err) अणु
		netdev_err(dev, "Failed to configure port's headroom for PFC\n");
		वापस err;
	पूर्ण

	err = mlxsw_sp_port_pfc_set(mlxsw_sp_port, pfc);
	अगर (err) अणु
		netdev_err(dev, "Failed to configure PFC\n");
		जाओ err_port_pfc_set;
	पूर्ण

	स_नकल(mlxsw_sp_port->dcb.pfc, pfc, माप(*pfc));
	mlxsw_sp_port->dcb.pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;

	वापस 0;

err_port_pfc_set:
	mlxsw_sp_hdroom_configure(mlxsw_sp_port, &orig_hdroom);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_getbuffer(काष्ठा net_device *dev, काष्ठा dcbnl_buffer *buf)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp_hdroom *hdroom = mlxsw_sp_port->hdroom;
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	पूर्णांक prio;
	पूर्णांक i;

	buf->total_size = 0;

	BUILD_BUG_ON(DCBX_MAX_BUFFERS > MLXSW_SP_PB_COUNT);
	क्रम (i = 0; i < MLXSW_SP_PB_COUNT; i++) अणु
		u32 bytes = mlxsw_sp_cells_bytes(mlxsw_sp, hdroom->bufs.buf[i].size_cells);

		अगर (i < DCBX_MAX_BUFFERS)
			buf->buffer_size[i] = bytes;
		buf->total_size += bytes;
	पूर्ण

	buf->total_size += mlxsw_sp_cells_bytes(mlxsw_sp, hdroom->पूर्णांक_buf.size_cells);

	क्रम (prio = 0; prio < IEEE_8021Q_MAX_PRIORITIES; prio++)
		buf->prio2buffer[prio] = hdroom->prios.prio[prio].buf_idx;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_dcbnl_रखो_बफfer(काष्ठा net_device *dev, काष्ठा dcbnl_buffer *buf)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_hdroom hdroom;
	पूर्णांक prio;
	पूर्णांक i;

	hdroom = *mlxsw_sp_port->hdroom;

	अगर (hdroom.mode != MLXSW_SP_HDROOM_MODE_TC) अणु
		netdev_err(dev, "The use of dcbnl_setbuffer is only allowed if egress is configured using TC\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (prio = 0; prio < IEEE_8021Q_MAX_PRIORITIES; prio++)
		hdroom.prios.prio[prio].set_buf_idx = buf->prio2buffer[prio];

	BUILD_BUG_ON(DCBX_MAX_BUFFERS > MLXSW_SP_PB_COUNT);
	क्रम (i = 0; i < DCBX_MAX_BUFFERS; i++)
		hdroom.bufs.buf[i].set_size_cells = mlxsw_sp_bytes_cells(mlxsw_sp,
									 buf->buffer_size[i]);

	mlxsw_sp_hdroom_prios_reset_buf_idx(&hdroom);
	mlxsw_sp_hdroom_bufs_reset_lossiness(&hdroom);
	mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);
	वापस mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom);
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops mlxsw_sp_dcbnl_ops = अणु
	.ieee_getets		= mlxsw_sp_dcbnl_ieee_getets,
	.ieee_setets		= mlxsw_sp_dcbnl_ieee_setets,
	.ieee_geपंचांगaxrate	= mlxsw_sp_dcbnl_ieee_geपंचांगaxrate,
	.ieee_seपंचांगaxrate	= mlxsw_sp_dcbnl_ieee_seपंचांगaxrate,
	.ieee_getpfc		= mlxsw_sp_dcbnl_ieee_getpfc,
	.ieee_setpfc		= mlxsw_sp_dcbnl_ieee_setpfc,
	.ieee_setapp		= mlxsw_sp_dcbnl_ieee_setapp,
	.ieee_delapp		= mlxsw_sp_dcbnl_ieee_delapp,

	.getdcbx		= mlxsw_sp_dcbnl_getdcbx,
	.setdcbx		= mlxsw_sp_dcbnl_setdcbx,

	.dcbnl_getbuffer	= mlxsw_sp_dcbnl_getbuffer,
	.dcbnl_रखो_बफfer	= mlxsw_sp_dcbnl_रखो_बफfer,
पूर्ण;

अटल पूर्णांक mlxsw_sp_port_ets_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	mlxsw_sp_port->dcb.ets = kzalloc(माप(*mlxsw_sp_port->dcb.ets),
					 GFP_KERNEL);
	अगर (!mlxsw_sp_port->dcb.ets)
		वापस -ENOMEM;

	mlxsw_sp_port->dcb.ets->ets_cap = IEEE_8021QAZ_MAX_TCS;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_port_ets_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	kमुक्त(mlxsw_sp_port->dcb.ets);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_maxrate_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	पूर्णांक i;

	mlxsw_sp_port->dcb.maxrate = kदो_स्मृति(माप(*mlxsw_sp_port->dcb.maxrate),
					     GFP_KERNEL);
	अगर (!mlxsw_sp_port->dcb.maxrate)
		वापस -ENOMEM;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		mlxsw_sp_port->dcb.maxrate->tc_maxrate[i] = MLXSW_REG_QEEC_MAS_DIS;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_port_maxrate_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	kमुक्त(mlxsw_sp_port->dcb.maxrate);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_pfc_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	mlxsw_sp_port->dcb.pfc = kzalloc(माप(*mlxsw_sp_port->dcb.pfc),
					 GFP_KERNEL);
	अगर (!mlxsw_sp_port->dcb.pfc)
		वापस -ENOMEM;

	mlxsw_sp_port->dcb.pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_port_pfc_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	kमुक्त(mlxsw_sp_port->dcb.pfc);
पूर्ण

पूर्णांक mlxsw_sp_port_dcb_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	पूर्णांक err;

	err = mlxsw_sp_port_ets_init(mlxsw_sp_port);
	अगर (err)
		वापस err;
	err = mlxsw_sp_port_maxrate_init(mlxsw_sp_port);
	अगर (err)
		जाओ err_port_maxrate_init;
	err = mlxsw_sp_port_pfc_init(mlxsw_sp_port);
	अगर (err)
		जाओ err_port_pfc_init;

	mlxsw_sp_port->dcb.trust_state = MLXSW_REG_QPTS_TRUST_STATE_PCP;
	mlxsw_sp_port->dev->dcbnl_ops = &mlxsw_sp_dcbnl_ops;

	वापस 0;

err_port_pfc_init:
	mlxsw_sp_port_maxrate_fini(mlxsw_sp_port);
err_port_maxrate_init:
	mlxsw_sp_port_ets_fini(mlxsw_sp_port);
	वापस err;
पूर्ण

व्योम mlxsw_sp_port_dcb_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	mlxsw_sp_port_pfc_fini(mlxsw_sp_port);
	mlxsw_sp_port_maxrate_fini(mlxsw_sp_port);
	mlxsw_sp_port_ets_fini(mlxsw_sp_port);
पूर्ण
