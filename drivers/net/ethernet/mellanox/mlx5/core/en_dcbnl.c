<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश "en.h"
#समावेश "en/port.h"
#समावेश "en/port_buffer.h"

#घोषणा MLX5E_MAX_BW_ALLOC 100 /* Max percentage of BW allocation */

#घोषणा MLX5E_100MB (100000)
#घोषणा MLX5E_1GB   (1000000)

#घोषणा MLX5E_CEE_STATE_UP    1
#घोषणा MLX5E_CEE_STATE_DOWN  0

/* Max supported cable length is 1000 meters */
#घोषणा MLX5E_MAX_CABLE_LENGTH 1000

क्रमागत अणु
	MLX5E_VENDOR_TC_GROUP_NUM = 7,
	MLX5E_LOWEST_PRIO_GROUP   = 0,
पूर्ण;

क्रमागत अणु
	MLX5_DCB_CHG_RESET,
	MLX5_DCB_NO_CHG,
	MLX5_DCB_CHG_NO_RESET,
पूर्ण;

#घोषणा MLX5_DSCP_SUPPORTED(mdev) (MLX5_CAP_GEN(mdev, qcam_reg)  && \
				   MLX5_CAP_QCAM_REG(mdev, qpts) && \
				   MLX5_CAP_QCAM_REG(mdev, qpdpm))

अटल पूर्णांक mlx5e_set_trust_state(काष्ठा mlx5e_priv *priv, u8 trust_state);
अटल पूर्णांक mlx5e_set_dscp2prio(काष्ठा mlx5e_priv *priv, u8 dscp, u8 prio);

/* If dcbx mode is non-host set the dcbx mode to host.
 */
अटल पूर्णांक mlx5e_dcbnl_set_dcbx_mode(काष्ठा mlx5e_priv *priv,
				     क्रमागत mlx5_dcbx_oper_mode mode)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 param[MLX5_ST_SZ_DW(dcbx_param)];
	पूर्णांक err;

	err = mlx5_query_port_dcbx_param(mdev, param);
	अगर (err)
		वापस err;

	MLX5_SET(dcbx_param, param, version_admin, mode);
	अगर (mode != MLX5E_DCBX_PARAM_VER_OPER_HOST)
		MLX5_SET(dcbx_param, param, willing_admin, 1);

	वापस mlx5_set_port_dcbx_param(mdev, param);
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_चयन_to_host_mode(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_dcbx *dcbx = &priv->dcbx;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(priv->mdev, dcbx))
		वापस 0;

	अगर (dcbx->mode == MLX5E_DCBX_PARAM_VER_OPER_HOST)
		वापस 0;

	err = mlx5e_dcbnl_set_dcbx_mode(priv, MLX5E_DCBX_PARAM_VER_OPER_HOST);
	अगर (err)
		वापस err;

	dcbx->mode = MLX5E_DCBX_PARAM_VER_OPER_HOST;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_ieee_getets(काष्ठा net_device *netdev,
				   काष्ठा ieee_ets *ets)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 tc_group[IEEE_8021QAZ_MAX_TCS];
	bool is_tc_group_6_exist = false;
	bool is_zero_bw_ets_tc = false;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (!MLX5_CAP_GEN(priv->mdev, ets))
		वापस -EOPNOTSUPP;

	ets->ets_cap = mlx5_max_tc(priv->mdev) + 1;
	क्रम (i = 0; i < ets->ets_cap; i++) अणु
		err = mlx5_query_port_prio_tc(mdev, i, &ets->prio_tc[i]);
		अगर (err)
			वापस err;

		err = mlx5_query_port_tc_group(mdev, i, &tc_group[i]);
		अगर (err)
			वापस err;

		err = mlx5_query_port_tc_bw_alloc(mdev, i, &ets->tc_tx_bw[i]);
		अगर (err)
			वापस err;

		अगर (ets->tc_tx_bw[i] < MLX5E_MAX_BW_ALLOC &&
		    tc_group[i] == (MLX5E_LOWEST_PRIO_GROUP + 1))
			is_zero_bw_ets_tc = true;

		अगर (tc_group[i] == (MLX5E_VENDOR_TC_GROUP_NUM - 1))
			is_tc_group_6_exist = true;
	पूर्ण

	/* Report 0% ets tc अगर निकासs*/
	अगर (is_zero_bw_ets_tc) अणु
		क्रम (i = 0; i < ets->ets_cap; i++)
			अगर (tc_group[i] == MLX5E_LOWEST_PRIO_GROUP)
				ets->tc_tx_bw[i] = 0;
	पूर्ण

	/* Update tc_tsa based on fw setting*/
	क्रम (i = 0; i < ets->ets_cap; i++) अणु
		अगर (ets->tc_tx_bw[i] < MLX5E_MAX_BW_ALLOC)
			priv->dcbx.tc_tsa[i] = IEEE_8021QAZ_TSA_ETS;
		अन्यथा अगर (tc_group[i] == MLX5E_VENDOR_TC_GROUP_NUM &&
			 !is_tc_group_6_exist)
			priv->dcbx.tc_tsa[i] = IEEE_8021QAZ_TSA_VENDOR;
	पूर्ण
	स_नकल(ets->tc_tsa, priv->dcbx.tc_tsa, माप(ets->tc_tsa));

	वापस err;
पूर्ण

अटल व्योम mlx5e_build_tc_group(काष्ठा ieee_ets *ets, u8 *tc_group, पूर्णांक max_tc)
अणु
	bool any_tc_mapped_to_ets = false;
	bool ets_zero_bw = false;
	पूर्णांक strict_group;
	पूर्णांक i;

	क्रम (i = 0; i <= max_tc; i++) अणु
		अगर (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS) अणु
			any_tc_mapped_to_ets = true;
			अगर (!ets->tc_tx_bw[i])
				ets_zero_bw = true;
		पूर्ण
	पूर्ण

	/* strict group has higher priority than ets group */
	strict_group = MLX5E_LOWEST_PRIO_GROUP;
	अगर (any_tc_mapped_to_ets)
		strict_group++;
	अगर (ets_zero_bw)
		strict_group++;

	क्रम (i = 0; i <= max_tc; i++) अणु
		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_VENDOR:
			tc_group[i] = MLX5E_VENDOR_TC_GROUP_NUM;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_STRICT:
			tc_group[i] = strict_group++;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			tc_group[i] = MLX5E_LOWEST_PRIO_GROUP;
			अगर (ets->tc_tx_bw[i] && ets_zero_bw)
				tc_group[i] = MLX5E_LOWEST_PRIO_GROUP + 1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mlx5e_build_tc_tx_bw(काष्ठा ieee_ets *ets, u8 *tc_tx_bw,
				 u8 *tc_group, पूर्णांक max_tc)
अणु
	पूर्णांक bw_क्रम_ets_zero_bw_tc = 0;
	पूर्णांक last_ets_zero_bw_tc = -1;
	पूर्णांक num_ets_zero_bw = 0;
	पूर्णांक i;

	क्रम (i = 0; i <= max_tc; i++) अणु
		अगर (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS &&
		    !ets->tc_tx_bw[i]) अणु
			num_ets_zero_bw++;
			last_ets_zero_bw_tc = i;
		पूर्ण
	पूर्ण

	अगर (num_ets_zero_bw)
		bw_क्रम_ets_zero_bw_tc = MLX5E_MAX_BW_ALLOC / num_ets_zero_bw;

	क्रम (i = 0; i <= max_tc; i++) अणु
		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_VENDOR:
			tc_tx_bw[i] = MLX5E_MAX_BW_ALLOC;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_STRICT:
			tc_tx_bw[i] = MLX5E_MAX_BW_ALLOC;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			tc_tx_bw[i] = ets->tc_tx_bw[i] ?
				      ets->tc_tx_bw[i] :
				      bw_क्रम_ets_zero_bw_tc;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Make sure the total bw क्रम ets zero bw group is 100% */
	अगर (last_ets_zero_bw_tc != -1)
		tc_tx_bw[last_ets_zero_bw_tc] +=
			MLX5E_MAX_BW_ALLOC % num_ets_zero_bw;
पूर्ण

/* If there are ETS BW 0,
 *   Set ETS group # to 1 क्रम all ETS non zero BW tcs. Their sum must be 100%.
 *   Set group #0 to all the ETS BW 0 tcs and
 *     equally splits the 100% BW between them
 *   Report both group #0 and #1 as ETS type.
 *     All the tcs in group #0 will be reported with 0% BW.
 */
अटल पूर्णांक mlx5e_dcbnl_ieee_setets_core(काष्ठा mlx5e_priv *priv, काष्ठा ieee_ets *ets)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 tc_tx_bw[IEEE_8021QAZ_MAX_TCS];
	u8 tc_group[IEEE_8021QAZ_MAX_TCS];
	पूर्णांक max_tc = mlx5_max_tc(mdev);
	पूर्णांक err, i;

	mlx5e_build_tc_group(ets, tc_group, max_tc);
	mlx5e_build_tc_tx_bw(ets, tc_tx_bw, tc_group, max_tc);

	err = mlx5_set_port_prio_tc(mdev, ets->prio_tc);
	अगर (err)
		वापस err;

	err = mlx5_set_port_tc_group(mdev, tc_group);
	अगर (err)
		वापस err;

	err = mlx5_set_port_tc_bw_alloc(mdev, tc_tx_bw);

	अगर (err)
		वापस err;

	स_नकल(priv->dcbx.tc_tsa, ets->tc_tsa, माप(ets->tc_tsa));

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		mlx5e_dbg(HW, priv, "%s: prio_%d <=> tc_%d\n",
			  __func__, i, ets->prio_tc[i]);
		mlx5e_dbg(HW, priv, "%s: tc_%d <=> tx_bw_%d%%, group_%d\n",
			  __func__, i, tc_tx_bw[i], tc_group[i]);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_dbcnl_validate_ets(काष्ठा net_device *netdev,
				    काष्ठा ieee_ets *ets,
				    bool zero_sum_allowed)
अणु
	bool have_ets_tc = false;
	पूर्णांक bw_sum = 0;
	पूर्णांक i;

	/* Validate Priority */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		अगर (ets->prio_tc[i] >= MLX5E_MAX_PRIORITY) अणु
			netdev_err(netdev,
				   "Failed to validate ETS: priority value greater than max(%d)\n",
				    MLX5E_MAX_PRIORITY);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Validate Bandwidth Sum */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		अगर (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS) अणु
			have_ets_tc = true;
			bw_sum += ets->tc_tx_bw[i];
		पूर्ण
	पूर्ण

	अगर (have_ets_tc && bw_sum != 100) अणु
		अगर (bw_sum || (!bw_sum && !zero_sum_allowed))
			netdev_err(netdev,
				   "Failed to validate ETS: BW sum is illegal\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_ieee_setets(काष्ठा net_device *netdev,
				   काष्ठा ieee_ets *ets)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(priv->mdev, ets))
		वापस -EOPNOTSUPP;

	err = mlx5e_dbcnl_validate_ets(netdev, ets, false);
	अगर (err)
		वापस err;

	err = mlx5e_dcbnl_ieee_setets_core(priv, ets);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_ieee_getpfc(काष्ठा net_device *dev,
				   काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	पूर्णांक i;

	pfc->pfc_cap = mlx5_max_tc(mdev) + 1;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		pfc->requests[i]    = PPORT_PER_PRIO_GET(pstats, i, tx_छोड़ो);
		pfc->indications[i] = PPORT_PER_PRIO_GET(pstats, i, rx_छोड़ो);
	पूर्ण

	अगर (MLX5_BUFFER_SUPPORTED(mdev))
		pfc->delay = priv->dcbx.cable_len;

	वापस mlx5_query_port_pfc(mdev, &pfc->pfc_en, शून्य);
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_ieee_setpfc(काष्ठा net_device *dev,
				   काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 old_cable_len = priv->dcbx.cable_len;
	काष्ठा ieee_pfc pfc_new;
	u32 changed = 0;
	u8 curr_pfc_en;
	पूर्णांक ret = 0;

	/* pfc_en */
	mlx5_query_port_pfc(mdev, &curr_pfc_en, शून्य);
	अगर (pfc->pfc_en != curr_pfc_en) अणु
		ret = mlx5_set_port_pfc(mdev, pfc->pfc_en, pfc->pfc_en);
		अगर (ret)
			वापस ret;
		mlx5_toggle_port_link(mdev);
		changed |= MLX5E_PORT_BUFFER_PFC;
	पूर्ण

	अगर (pfc->delay &&
	    pfc->delay < MLX5E_MAX_CABLE_LENGTH &&
	    pfc->delay != priv->dcbx.cable_len) अणु
		priv->dcbx.cable_len = pfc->delay;
		changed |= MLX5E_PORT_BUFFER_CABLE_LEN;
	पूर्ण

	अगर (MLX5_BUFFER_SUPPORTED(mdev)) अणु
		pfc_new.pfc_en = (changed & MLX5E_PORT_BUFFER_PFC) ? pfc->pfc_en : curr_pfc_en;
		अगर (priv->dcbx.manual_buffer)
			ret = mlx5e_port_manual_buffer_config(priv, changed,
							      dev->mtu, &pfc_new,
							      शून्य, शून्य);

		अगर (ret && (changed & MLX5E_PORT_BUFFER_CABLE_LEN))
			priv->dcbx.cable_len = old_cable_len;
	पूर्ण

	अगर (!ret) अणु
		mlx5e_dbg(HW, priv,
			  "%s: PFC per priority bit mask: 0x%x\n",
			  __func__, pfc->pfc_en);
	पूर्ण
	वापस ret;
पूर्ण

अटल u8 mlx5e_dcbnl_getdcbx(काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	वापस priv->dcbx.cap;
पूर्ण

अटल u8 mlx5e_dcbnl_setdcbx(काष्ठा net_device *dev, u8 mode)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_dcbx *dcbx = &priv->dcbx;

	अगर (mode & DCB_CAP_DCBX_LLD_MANAGED)
		वापस 1;

	अगर ((!mode) && MLX5_CAP_GEN(priv->mdev, dcbx)) अणु
		अगर (dcbx->mode == MLX5E_DCBX_PARAM_VER_OPER_AUTO)
			वापस 0;

		/* set dcbx to fw controlled */
		अगर (!mlx5e_dcbnl_set_dcbx_mode(priv, MLX5E_DCBX_PARAM_VER_OPER_AUTO)) अणु
			dcbx->mode = MLX5E_DCBX_PARAM_VER_OPER_AUTO;
			dcbx->cap &= ~DCB_CAP_DCBX_HOST;
			वापस 0;
		पूर्ण

		वापस 1;
	पूर्ण

	अगर (!(mode & DCB_CAP_DCBX_HOST))
		वापस 1;

	अगर (mlx5e_dcbnl_चयन_to_host_mode(netdev_priv(dev)))
		वापस 1;

	dcbx->cap = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_ieee_setapp(काष्ठा net_device *dev, काष्ठा dcb_app *app)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा dcb_app temp;
	bool is_new;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(priv->mdev, vport_group_manager) ||
	    !MLX5_DSCP_SUPPORTED(priv->mdev))
		वापस -EOPNOTSUPP;

	अगर ((app->selector != IEEE_8021QAZ_APP_SEL_DSCP) ||
	    (app->protocol >= MLX5E_MAX_DSCP))
		वापस -EINVAL;

	/* Save the old entry info */
	temp.selector = IEEE_8021QAZ_APP_SEL_DSCP;
	temp.protocol = app->protocol;
	temp.priority = priv->dcbx_dp.dscp2prio[app->protocol];

	/* Check अगर need to चयन to dscp trust state */
	अगर (!priv->dcbx.dscp_app_cnt) अणु
		err =  mlx5e_set_trust_state(priv, MLX5_QPTS_TRUST_DSCP);
		अगर (err)
			वापस err;
	पूर्ण

	/* Skip the fw command अगर new and old mapping are the same */
	अगर (app->priority != priv->dcbx_dp.dscp2prio[app->protocol]) अणु
		err = mlx5e_set_dscp2prio(priv, app->protocol, app->priority);
		अगर (err)
			जाओ fw_err;
	पूर्ण

	/* Delete the old entry अगर exists */
	is_new = false;
	err = dcb_ieee_delapp(dev, &temp);
	अगर (err)
		is_new = true;

	/* Add new entry and update counter */
	err = dcb_ieee_setapp(dev, app);
	अगर (err)
		वापस err;

	अगर (is_new)
		priv->dcbx.dscp_app_cnt++;

	वापस err;

fw_err:
	mlx5e_set_trust_state(priv, MLX5_QPTS_TRUST_PCP);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_ieee_delapp(काष्ठा net_device *dev, काष्ठा dcb_app *app)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	अगर  (!MLX5_CAP_GEN(priv->mdev, vport_group_manager) ||
	     !MLX5_DSCP_SUPPORTED(priv->mdev))
		वापस -EOPNOTSUPP;

	अगर ((app->selector != IEEE_8021QAZ_APP_SEL_DSCP) ||
	    (app->protocol >= MLX5E_MAX_DSCP))
		वापस -EINVAL;

	/* Skip अगर no dscp app entry */
	अगर (!priv->dcbx.dscp_app_cnt)
		वापस -ENOENT;

	/* Check अगर the entry matches fw setting */
	अगर (app->priority != priv->dcbx_dp.dscp2prio[app->protocol])
		वापस -ENOENT;

	/* Delete the app entry */
	err = dcb_ieee_delapp(dev, app);
	अगर (err)
		वापस err;

	/* Reset the priority mapping back to zero */
	err = mlx5e_set_dscp2prio(priv, app->protocol, 0);
	अगर (err)
		जाओ fw_err;

	priv->dcbx.dscp_app_cnt--;

	/* Check अगर need to चयन to pcp trust state */
	अगर (!priv->dcbx.dscp_app_cnt)
		err = mlx5e_set_trust_state(priv, MLX5_QPTS_TRUST_PCP);

	वापस err;

fw_err:
	mlx5e_set_trust_state(priv, MLX5_QPTS_TRUST_PCP);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_ieee_geपंचांगaxrate(काष्ठा net_device *netdev,
				       काष्ठा ieee_maxrate *maxrate)
अणु
	काष्ठा mlx5e_priv *priv    = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 max_bw_value[IEEE_8021QAZ_MAX_TCS];
	u8 max_bw_unit[IEEE_8021QAZ_MAX_TCS];
	पूर्णांक err;
	पूर्णांक i;

	err = mlx5_query_port_ets_rate_limit(mdev, max_bw_value, max_bw_unit);
	अगर (err)
		वापस err;

	स_रखो(maxrate->tc_maxrate, 0, माप(maxrate->tc_maxrate));

	क्रम (i = 0; i <= mlx5_max_tc(mdev); i++) अणु
		चयन (max_bw_unit[i]) अणु
		हाल MLX5_100_MBPS_UNIT:
			maxrate->tc_maxrate[i] = max_bw_value[i] * MLX5E_100MB;
			अवरोध;
		हाल MLX5_GBPS_UNIT:
			maxrate->tc_maxrate[i] = max_bw_value[i] * MLX5E_1GB;
			अवरोध;
		हाल MLX5_BW_NO_LIMIT:
			अवरोध;
		शेष:
			WARN(true, "non-supported BW unit");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_ieee_seपंचांगaxrate(काष्ठा net_device *netdev,
				       काष्ठा ieee_maxrate *maxrate)
अणु
	काष्ठा mlx5e_priv *priv    = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 max_bw_value[IEEE_8021QAZ_MAX_TCS];
	u8 max_bw_unit[IEEE_8021QAZ_MAX_TCS];
	__u64 upper_limit_mbps = roundup(255 * MLX5E_100MB, MLX5E_1GB);
	पूर्णांक i;

	स_रखो(max_bw_value, 0, माप(max_bw_value));
	स_रखो(max_bw_unit, 0, माप(max_bw_unit));

	क्रम (i = 0; i <= mlx5_max_tc(mdev); i++) अणु
		अगर (!maxrate->tc_maxrate[i]) अणु
			max_bw_unit[i]  = MLX5_BW_NO_LIMIT;
			जारी;
		पूर्ण
		अगर (maxrate->tc_maxrate[i] < upper_limit_mbps) अणु
			max_bw_value[i] = भाग_u64(maxrate->tc_maxrate[i],
						  MLX5E_100MB);
			max_bw_value[i] = max_bw_value[i] ? max_bw_value[i] : 1;
			max_bw_unit[i]  = MLX5_100_MBPS_UNIT;
		पूर्ण अन्यथा अणु
			max_bw_value[i] = भाग_u64(maxrate->tc_maxrate[i],
						  MLX5E_1GB);
			max_bw_unit[i]  = MLX5_GBPS_UNIT;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		mlx5e_dbg(HW, priv, "%s: tc_%d <=> max_bw %d Gbps\n",
			  __func__, i, max_bw_value[i]);
	पूर्ण

	वापस mlx5_modअगरy_port_ets_rate_limit(mdev, max_bw_value, max_bw_unit);
पूर्ण

अटल u8 mlx5e_dcbnl_setall(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_cee_config *cee_cfg = &priv->dcbx.cee_cfg;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा ieee_ets ets;
	काष्ठा ieee_pfc pfc;
	पूर्णांक err = -EOPNOTSUPP;
	पूर्णांक i;

	अगर (!MLX5_CAP_GEN(mdev, ets))
		जाओ out;

	स_रखो(&ets, 0, माप(ets));
	स_रखो(&pfc, 0, माप(pfc));

	ets.ets_cap = IEEE_8021QAZ_MAX_TCS;
	क्रम (i = 0; i < CEE_DCBX_MAX_PGS; i++) अणु
		ets.tc_tx_bw[i] = cee_cfg->pg_bw_pct[i];
		ets.tc_rx_bw[i] = cee_cfg->pg_bw_pct[i];
		ets.tc_tsa[i]   = IEEE_8021QAZ_TSA_ETS;
		ets.prio_tc[i]  = cee_cfg->prio_to_pg_map[i];
		mlx5e_dbg(HW, priv,
			  "%s: Priority group %d: tx_bw %d, rx_bw %d, prio_tc %d\n",
			  __func__, i, ets.tc_tx_bw[i], ets.tc_rx_bw[i],
			  ets.prio_tc[i]);
	पूर्ण

	err = mlx5e_dbcnl_validate_ets(netdev, &ets, true);
	अगर (err)
		जाओ out;

	err = mlx5e_dcbnl_ieee_setets_core(priv, &ets);
	अगर (err) अणु
		netdev_err(netdev,
			   "%s, Failed to set ETS: %d\n", __func__, err);
		जाओ out;
	पूर्ण

	/* Set PFC */
	pfc.pfc_cap = mlx5_max_tc(mdev) + 1;
	अगर (!cee_cfg->pfc_enable)
		pfc.pfc_en = 0;
	अन्यथा
		क्रम (i = 0; i < CEE_DCBX_MAX_PRIO; i++)
			pfc.pfc_en |= cee_cfg->pfc_setting[i] << i;

	err = mlx5e_dcbnl_ieee_setpfc(netdev, &pfc);
	अगर (err) अणु
		netdev_err(netdev,
			   "%s, Failed to set PFC: %d\n", __func__, err);
		जाओ out;
	पूर्ण
out:
	वापस err ? MLX5_DCB_NO_CHG : MLX5_DCB_CHG_RESET;
पूर्ण

अटल u8 mlx5e_dcbnl_माला_लोtate(काष्ठा net_device *netdev)
अणु
	वापस MLX5E_CEE_STATE_UP;
पूर्ण

अटल व्योम mlx5e_dcbnl_getpermhwaddr(काष्ठा net_device *netdev,
				      u8 *perm_addr)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	अगर (!perm_addr)
		वापस;

	स_रखो(perm_addr, 0xff, MAX_ADDR_LEN);

	mlx5_query_mac_address(priv->mdev, perm_addr);
पूर्ण

अटल व्योम mlx5e_dcbnl_setpgtccfgtx(काष्ठा net_device *netdev,
				     पूर्णांक priority, u8 prio_type,
				     u8 pgid, u8 bw_pct, u8 up_map)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_cee_config *cee_cfg = &priv->dcbx.cee_cfg;

	अगर (priority >= CEE_DCBX_MAX_PRIO) अणु
		netdev_err(netdev,
			   "%s, priority is out of range\n", __func__);
		वापस;
	पूर्ण

	अगर (pgid >= CEE_DCBX_MAX_PGS) अणु
		netdev_err(netdev,
			   "%s, priority group is out of range\n", __func__);
		वापस;
	पूर्ण

	cee_cfg->prio_to_pg_map[priority] = pgid;
पूर्ण

अटल व्योम mlx5e_dcbnl_setpgbwgcfgtx(काष्ठा net_device *netdev,
				      पूर्णांक pgid, u8 bw_pct)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_cee_config *cee_cfg = &priv->dcbx.cee_cfg;

	अगर (pgid >= CEE_DCBX_MAX_PGS) अणु
		netdev_err(netdev,
			   "%s, priority group is out of range\n", __func__);
		वापस;
	पूर्ण

	cee_cfg->pg_bw_pct[pgid] = bw_pct;
पूर्ण

अटल व्योम mlx5e_dcbnl_getpgtccfgtx(काष्ठा net_device *netdev,
				     पूर्णांक priority, u8 *prio_type,
				     u8 *pgid, u8 *bw_pct, u8 *up_map)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (!MLX5_CAP_GEN(priv->mdev, ets)) अणु
		netdev_err(netdev, "%s, ets is not supported\n", __func__);
		वापस;
	पूर्ण

	अगर (priority >= CEE_DCBX_MAX_PRIO) अणु
		netdev_err(netdev,
			   "%s, priority is out of range\n", __func__);
		वापस;
	पूर्ण

	*prio_type = 0;
	*bw_pct = 0;
	*up_map = 0;

	अगर (mlx5_query_port_prio_tc(mdev, priority, pgid))
		*pgid = 0;
पूर्ण

अटल व्योम mlx5e_dcbnl_getpgbwgcfgtx(काष्ठा net_device *netdev,
				      पूर्णांक pgid, u8 *bw_pct)
अणु
	काष्ठा ieee_ets ets;

	अगर (pgid >= CEE_DCBX_MAX_PGS) अणु
		netdev_err(netdev,
			   "%s, priority group is out of range\n", __func__);
		वापस;
	पूर्ण

	mlx5e_dcbnl_ieee_getets(netdev, &ets);
	*bw_pct = ets.tc_tx_bw[pgid];
पूर्ण

अटल व्योम mlx5e_dcbnl_setpfccfg(काष्ठा net_device *netdev,
				  पूर्णांक priority, u8 setting)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_cee_config *cee_cfg = &priv->dcbx.cee_cfg;

	अगर (priority >= CEE_DCBX_MAX_PRIO) अणु
		netdev_err(netdev,
			   "%s, priority is out of range\n", __func__);
		वापस;
	पूर्ण

	अगर (setting > 1)
		वापस;

	cee_cfg->pfc_setting[priority] = setting;
पूर्ण

अटल पूर्णांक
mlx5e_dcbnl_get_priority_pfc(काष्ठा net_device *netdev,
			     पूर्णांक priority, u8 *setting)
अणु
	काष्ठा ieee_pfc pfc;
	पूर्णांक err;

	err = mlx5e_dcbnl_ieee_getpfc(netdev, &pfc);

	अगर (err)
		*setting = 0;
	अन्यथा
		*setting = (pfc.pfc_en >> priority) & 0x01;

	वापस err;
पूर्ण

अटल व्योम mlx5e_dcbnl_getpfccfg(काष्ठा net_device *netdev,
				  पूर्णांक priority, u8 *setting)
अणु
	अगर (priority >= CEE_DCBX_MAX_PRIO) अणु
		netdev_err(netdev,
			   "%s, priority is out of range\n", __func__);
		वापस;
	पूर्ण

	अगर (!setting)
		वापस;

	mlx5e_dcbnl_get_priority_pfc(netdev, priority, setting);
पूर्ण

अटल u8 mlx5e_dcbnl_अ_लोap(काष्ठा net_device *netdev,
			     पूर्णांक capid, u8 *cap)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 rval = 0;

	चयन (capid) अणु
	हाल DCB_CAP_ATTR_PG:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_PFC:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_UP2TC:
		*cap = false;
		अवरोध;
	हाल DCB_CAP_ATTR_PG_TCS:
		*cap = 1 << mlx5_max_tc(mdev);
		अवरोध;
	हाल DCB_CAP_ATTR_PFC_TCS:
		*cap = 1 << mlx5_max_tc(mdev);
		अवरोध;
	हाल DCB_CAP_ATTR_GSP:
		*cap = false;
		अवरोध;
	हाल DCB_CAP_ATTR_BCN:
		*cap = false;
		अवरोध;
	हाल DCB_CAP_ATTR_DCBX:
		*cap = priv->dcbx.cap |
		       DCB_CAP_DCBX_VER_CEE |
		       DCB_CAP_DCBX_VER_IEEE;
		अवरोध;
	शेष:
		*cap = 0;
		rval = 1;
		अवरोध;
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_getnumtcs(काष्ठा net_device *netdev,
				 पूर्णांक tcs_id, u8 *num)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	चयन (tcs_id) अणु
	हाल DCB_NUMTCS_ATTR_PG:
	हाल DCB_NUMTCS_ATTR_PFC:
		*num = mlx5_max_tc(mdev) + 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 mlx5e_dcbnl_getpfcstate(काष्ठा net_device *netdev)
अणु
	काष्ठा ieee_pfc pfc;

	अगर (mlx5e_dcbnl_ieee_getpfc(netdev, &pfc))
		वापस MLX5E_CEE_STATE_DOWN;

	वापस pfc.pfc_en ? MLX5E_CEE_STATE_UP : MLX5E_CEE_STATE_DOWN;
पूर्ण

अटल व्योम mlx5e_dcbnl_setpfcstate(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_cee_config *cee_cfg = &priv->dcbx.cee_cfg;

	अगर ((state != MLX5E_CEE_STATE_UP) && (state != MLX5E_CEE_STATE_DOWN))
		वापस;

	cee_cfg->pfc_enable = state;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_getbuffer(काष्ठा net_device *dev,
				 काष्ठा dcbnl_buffer *dcb_buffer)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_port_buffer port_buffer;
	u8 buffer[MLX5E_MAX_PRIORITY];
	पूर्णांक i, err;

	अगर (!MLX5_BUFFER_SUPPORTED(mdev))
		वापस -EOPNOTSUPP;

	err = mlx5e_port_query_priority2buffer(mdev, buffer);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < MLX5E_MAX_PRIORITY; i++)
		dcb_buffer->prio2buffer[i] = buffer[i];

	err = mlx5e_port_query_buffer(priv, &port_buffer);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < MLX5E_MAX_BUFFER; i++)
		dcb_buffer->buffer_size[i] = port_buffer.buffer[i].size;
	dcb_buffer->total_size = port_buffer.port_buffer_size;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_dcbnl_रखो_बफfer(काष्ठा net_device *dev,
				 काष्ठा dcbnl_buffer *dcb_buffer)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_port_buffer port_buffer;
	u8 old_prio2buffer[MLX5E_MAX_PRIORITY];
	u32 *buffer_size = शून्य;
	u8 *prio2buffer = शून्य;
	u32 changed = 0;
	पूर्णांक i, err;

	अगर (!MLX5_BUFFER_SUPPORTED(mdev))
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i < DCBX_MAX_BUFFERS; i++)
		mlx5_core_dbg(mdev, "buffer[%d]=%d\n", i, dcb_buffer->buffer_size[i]);

	क्रम (i = 0; i < MLX5E_MAX_PRIORITY; i++)
		mlx5_core_dbg(mdev, "priority %d buffer%d\n", i, dcb_buffer->prio2buffer[i]);

	err = mlx5e_port_query_priority2buffer(mdev, old_prio2buffer);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < MLX5E_MAX_PRIORITY; i++) अणु
		अगर (dcb_buffer->prio2buffer[i] != old_prio2buffer[i]) अणु
			changed |= MLX5E_PORT_BUFFER_PRIO2BUFFER;
			prio2buffer = dcb_buffer->prio2buffer;
			अवरोध;
		पूर्ण
	पूर्ण

	err = mlx5e_port_query_buffer(priv, &port_buffer);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < MLX5E_MAX_BUFFER; i++) अणु
		अगर (port_buffer.buffer[i].size != dcb_buffer->buffer_size[i]) अणु
			changed |= MLX5E_PORT_BUFFER_SIZE;
			buffer_size = dcb_buffer->buffer_size;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!changed)
		वापस 0;

	priv->dcbx.manual_buffer = true;
	err = mlx5e_port_manual_buffer_config(priv, changed, dev->mtu, शून्य,
					      buffer_size, prio2buffer);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops mlx5e_dcbnl_ops = अणु
	.ieee_getets	= mlx5e_dcbnl_ieee_getets,
	.ieee_setets	= mlx5e_dcbnl_ieee_setets,
	.ieee_geपंचांगaxrate = mlx5e_dcbnl_ieee_geपंचांगaxrate,
	.ieee_seपंचांगaxrate = mlx5e_dcbnl_ieee_seपंचांगaxrate,
	.ieee_getpfc	= mlx5e_dcbnl_ieee_getpfc,
	.ieee_setpfc	= mlx5e_dcbnl_ieee_setpfc,
	.ieee_setapp    = mlx5e_dcbnl_ieee_setapp,
	.ieee_delapp    = mlx5e_dcbnl_ieee_delapp,
	.getdcbx	= mlx5e_dcbnl_getdcbx,
	.setdcbx	= mlx5e_dcbnl_setdcbx,
	.dcbnl_getbuffer = mlx5e_dcbnl_getbuffer,
	.dcbnl_रखो_बफfer = mlx5e_dcbnl_रखो_बफfer,

/* CEE पूर्णांकerfaces */
	.setall         = mlx5e_dcbnl_setall,
	.माला_लोtate       = mlx5e_dcbnl_माला_लोtate,
	.getpermhwaddr  = mlx5e_dcbnl_getpermhwaddr,

	.setpgtccfgtx   = mlx5e_dcbnl_setpgtccfgtx,
	.setpgbwgcfgtx  = mlx5e_dcbnl_setpgbwgcfgtx,
	.getpgtccfgtx   = mlx5e_dcbnl_getpgtccfgtx,
	.getpgbwgcfgtx  = mlx5e_dcbnl_getpgbwgcfgtx,

	.setpfccfg      = mlx5e_dcbnl_setpfccfg,
	.getpfccfg      = mlx5e_dcbnl_getpfccfg,
	.अ_लोap         = mlx5e_dcbnl_अ_लोap,
	.getnumtcs      = mlx5e_dcbnl_getnumtcs,
	.getpfcstate    = mlx5e_dcbnl_getpfcstate,
	.setpfcstate    = mlx5e_dcbnl_setpfcstate,
पूर्ण;

व्योम mlx5e_dcbnl_build_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (MLX5_CAP_GEN(mdev, vport_group_manager) && MLX5_CAP_GEN(mdev, qos))
		netdev->dcbnl_ops = &mlx5e_dcbnl_ops;
पूर्ण

व्योम mlx5e_dcbnl_build_rep_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (MLX5_CAP_GEN(mdev, qos))
		netdev->dcbnl_ops = &mlx5e_dcbnl_ops;
पूर्ण

अटल व्योम mlx5e_dcbnl_query_dcbx_mode(काष्ठा mlx5e_priv *priv,
					क्रमागत mlx5_dcbx_oper_mode *mode)
अणु
	u32 out[MLX5_ST_SZ_DW(dcbx_param)];

	*mode = MLX5E_DCBX_PARAM_VER_OPER_HOST;

	अगर (!mlx5_query_port_dcbx_param(priv->mdev, out))
		*mode = MLX5_GET(dcbx_param, out, version_oper);

	/* From driver's poपूर्णांक of view, we only care अगर the mode
	 * is host (HOST) or non-host (AUTO)
	 */
	अगर (*mode != MLX5E_DCBX_PARAM_VER_OPER_HOST)
		*mode = MLX5E_DCBX_PARAM_VER_OPER_AUTO;
पूर्ण

अटल व्योम mlx5e_ets_init(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा ieee_ets ets;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!MLX5_CAP_GEN(priv->mdev, ets))
		वापस;

	स_रखो(&ets, 0, माप(ets));
	ets.ets_cap = mlx5_max_tc(priv->mdev) + 1;
	क्रम (i = 0; i < ets.ets_cap; i++) अणु
		ets.tc_tx_bw[i] = MLX5E_MAX_BW_ALLOC;
		ets.tc_tsa[i] = IEEE_8021QAZ_TSA_VENDOR;
		ets.prio_tc[i] = i;
	पूर्ण

	अगर (ets.ets_cap > 1) अणु
		/* tclass[prio=0]=1, tclass[prio=1]=0, tclass[prio=i]=i (क्रम i>1) */
		ets.prio_tc[0] = 1;
		ets.prio_tc[1] = 0;
	पूर्ण

	err = mlx5e_dcbnl_ieee_setets_core(priv, &ets);
	अगर (err)
		netdev_err(priv->netdev,
			   "%s, Failed to init ETS: %d\n", __func__, err);
पूर्ण

क्रमागत अणु
	INIT,
	DELETE,
पूर्ण;

अटल व्योम mlx5e_dcbnl_dscp_app(काष्ठा mlx5e_priv *priv, पूर्णांक action)
अणु
	काष्ठा dcb_app temp;
	पूर्णांक i;

	अगर (!MLX5_CAP_GEN(priv->mdev, vport_group_manager))
		वापस;

	अगर (!MLX5_DSCP_SUPPORTED(priv->mdev))
		वापस;

	/* No SEL_DSCP entry in non DSCP state */
	अगर (priv->dcbx_dp.trust_state != MLX5_QPTS_TRUST_DSCP)
		वापस;

	temp.selector = IEEE_8021QAZ_APP_SEL_DSCP;
	क्रम (i = 0; i < MLX5E_MAX_DSCP; i++) अणु
		temp.protocol = i;
		temp.priority = priv->dcbx_dp.dscp2prio[i];
		अगर (action == INIT)
			dcb_ieee_setapp(priv->netdev, &temp);
		अन्यथा
			dcb_ieee_delapp(priv->netdev, &temp);
	पूर्ण

	priv->dcbx.dscp_app_cnt = (action == INIT) ? MLX5E_MAX_DSCP : 0;
पूर्ण

व्योम mlx5e_dcbnl_init_app(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_dcbnl_dscp_app(priv, INIT);
पूर्ण

व्योम mlx5e_dcbnl_delete_app(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_dcbnl_dscp_app(priv, DELETE);
पूर्ण

अटल व्योम mlx5e_params_calc_trust_tx_min_अंतरभूत_mode(काष्ठा mlx5_core_dev *mdev,
						       काष्ठा mlx5e_params *params,
						       u8 trust_state)
अणु
	mlx5_query_min_अंतरभूत(mdev, &params->tx_min_अंतरभूत_mode);
	अगर (trust_state == MLX5_QPTS_TRUST_DSCP &&
	    params->tx_min_अंतरभूत_mode == MLX5_INLINE_MODE_L2)
		params->tx_min_अंतरभूत_mode = MLX5_INLINE_MODE_IP;
पूर्ण

अटल पूर्णांक mlx5e_update_trust_state_hw(काष्ठा mlx5e_priv *priv, व्योम *context)
अणु
	u8 *trust_state = context;
	पूर्णांक err;

	err = mlx5_set_trust_state(priv->mdev, *trust_state);
	अगर (err)
		वापस err;
	priv->dcbx_dp.trust_state = *trust_state;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_set_trust_state(काष्ठा mlx5e_priv *priv, u8 trust_state)
अणु
	काष्ठा mlx5e_params new_params;
	bool reset = true;
	पूर्णांक err;

	mutex_lock(&priv->state_lock);

	new_params = priv->channels.params;
	mlx5e_params_calc_trust_tx_min_अंतरभूत_mode(priv->mdev, &new_params,
						   trust_state);

	/* Skip अगर tx_min_अंतरभूत is the same */
	अगर (new_params.tx_min_अंतरभूत_mode == priv->channels.params.tx_min_अंतरभूत_mode)
		reset = false;

	err = mlx5e_safe_चयन_params(priv, &new_params,
				       mlx5e_update_trust_state_hw,
				       &trust_state, reset);

	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_set_dscp2prio(काष्ठा mlx5e_priv *priv, u8 dscp, u8 prio)
अणु
	पूर्णांक err;

	err = mlx5_set_dscp2prio(priv->mdev, dscp, prio);
	अगर (err)
		वापस err;

	priv->dcbx_dp.dscp2prio[dscp] = prio;
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_trust_initialize(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक err;

	priv->dcbx_dp.trust_state = MLX5_QPTS_TRUST_PCP;

	अगर (!MLX5_DSCP_SUPPORTED(mdev))
		वापस 0;

	err = mlx5_query_trust_state(priv->mdev, &priv->dcbx_dp.trust_state);
	अगर (err)
		वापस err;

	mlx5e_params_calc_trust_tx_min_अंतरभूत_mode(priv->mdev, &priv->channels.params,
						   priv->dcbx_dp.trust_state);

	err = mlx5_query_dscp2prio(priv->mdev, priv->dcbx_dp.dscp2prio);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

#घोषणा MLX5E_BUFFER_CELL_SHIFT 7

अटल u16 mlx5e_query_port_buffers_cell_size(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 out[MLX5_ST_SZ_DW(sbcam_reg)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(sbcam_reg)] = अणुपूर्ण;

	अगर (!MLX5_CAP_GEN(mdev, sbcam_reg))
		वापस (1 << MLX5E_BUFFER_CELL_SHIFT);

	अगर (mlx5_core_access_reg(mdev, in, माप(in), out, माप(out),
				 MLX5_REG_SBCAM, 0, 0))
		वापस (1 << MLX5E_BUFFER_CELL_SHIFT);

	वापस MLX5_GET(sbcam_reg, out, cap_cell_size);
पूर्ण

व्योम mlx5e_dcbnl_initialize(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_dcbx *dcbx = &priv->dcbx;

	mlx5e_trust_initialize(priv);

	अगर (!MLX5_CAP_GEN(priv->mdev, qos))
		वापस;

	अगर (MLX5_CAP_GEN(priv->mdev, dcbx))
		mlx5e_dcbnl_query_dcbx_mode(priv, &dcbx->mode);

	priv->dcbx.cap = DCB_CAP_DCBX_VER_CEE |
			 DCB_CAP_DCBX_VER_IEEE;
	अगर (priv->dcbx.mode == MLX5E_DCBX_PARAM_VER_OPER_HOST)
		priv->dcbx.cap |= DCB_CAP_DCBX_HOST;

	priv->dcbx.port_buff_cell_sz = mlx5e_query_port_buffers_cell_size(priv);
	priv->dcbx.manual_buffer = false;
	priv->dcbx.cable_len = MLX5E_DEFAULT_CABLE_LEN;

	mlx5e_ets_init(priv);
पूर्ण
