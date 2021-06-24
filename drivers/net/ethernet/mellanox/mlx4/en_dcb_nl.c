<शैली गुरु>
/*
 * Copyright (c) 2011 Mellanox Technologies. All rights reserved.
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
 *
 */

#समावेश <linux/dcbnl.h>
#समावेश <linux/math64.h>

#समावेश "mlx4_en.h"
#समावेश "fw_qos.h"

क्रमागत अणु
	MLX4_CEE_STATE_DOWN   = 0,
	MLX4_CEE_STATE_UP     = 1,
पूर्ण;

/* Definitions क्रम QCN
 */

काष्ठा mlx4_congestion_control_mb_prio_802_1_qau_params अणु
	__be32 modअगरy_enable_high;
	__be32 modअगरy_enable_low;
	__be32 reserved1;
	__be32 extended_enable;
	__be32 rppp_max_rps;
	__be32 rpg_समय_reset;
	__be32 rpg_byte_reset;
	__be32 rpg_threshold;
	__be32 rpg_max_rate;
	__be32 rpg_ai_rate;
	__be32 rpg_hai_rate;
	__be32 rpg_gd;
	__be32 rpg_min_dec_fac;
	__be32 rpg_min_rate;
	__be32 max_समय_rise;
	__be32 max_byte_rise;
	__be32 max_qdelta;
	__be32 min_qoffset;
	__be32 gd_coefficient;
	__be32 reserved2[5];
	__be32 cp_sample_base;
	__be32 reserved3[39];
पूर्ण;

काष्ठा mlx4_congestion_control_mb_prio_802_1_qau_statistics अणु
	__be64 rppp_rp_centiseconds;
	__be32 reserved1;
	__be32 ignored_cnm;
	__be32 rppp_created_rps;
	__be32 estimated_total_rate;
	__be32 max_active_rate_limiter_index;
	__be32 dropped_cnms_busy_fw;
	__be32 reserved2;
	__be32 cnms_handled_successfully;
	__be32 min_total_limiters_rate;
	__be32 max_total_limiters_rate;
	__be32 reserved3[4];
पूर्ण;

अटल u8 mlx4_en_dcbnl_अ_लोap(काष्ठा net_device *dev, पूर्णांक capid, u8 *cap)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	चयन (capid) अणु
	हाल DCB_CAP_ATTR_PFC:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_DCBX:
		*cap = priv->dcbx_cap;
		अवरोध;
	हाल DCB_CAP_ATTR_PFC_TCS:
		*cap = 1 <<  mlx4_max_tc(priv->mdev->dev);
		अवरोध;
	शेष:
		*cap = false;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 mlx4_en_dcbnl_getpfcstate(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);

	वापस priv->cee_config.pfc_state;
पूर्ण

अटल व्योम mlx4_en_dcbnl_setpfcstate(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);

	priv->cee_config.pfc_state = state;
पूर्ण

अटल व्योम mlx4_en_dcbnl_get_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक priority,
				      u8 *setting)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);

	*setting = priv->cee_config.dcb_pfc[priority];
पूर्ण

अटल व्योम mlx4_en_dcbnl_set_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक priority,
				      u8 setting)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);

	priv->cee_config.dcb_pfc[priority] = setting;
	priv->cee_config.pfc_state = true;
पूर्ण

अटल पूर्णांक mlx4_en_dcbnl_getnumtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 *num)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);

	अगर (!(priv->flags & MLX4_EN_FLAG_DCB_ENABLED))
		वापस -EINVAL;

	अगर (tcid == DCB_NUMTCS_ATTR_PFC)
		*num = mlx4_max_tc(priv->mdev->dev);
	अन्यथा
		*num = 0;

	वापस 0;
पूर्ण

अटल u8 mlx4_en_dcbnl_set_all(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);
	काष्ठा mlx4_en_port_profile *prof = priv->prof;
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	u8 tx_छोड़ो, tx_ppp, rx_छोड़ो, rx_ppp;

	अगर (!(priv->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस 1;

	अगर (priv->cee_config.pfc_state) अणु
		पूर्णांक tc;
		rx_ppp = prof->rx_ppp;
		tx_ppp = prof->tx_ppp;

		क्रम (tc = 0; tc < CEE_DCBX_MAX_PRIO; tc++) अणु
			u8 tc_mask = 1 << tc;

			चयन (priv->cee_config.dcb_pfc[tc]) अणु
			हाल pfc_disabled:
				tx_ppp &= ~tc_mask;
				rx_ppp &= ~tc_mask;
				अवरोध;
			हाल pfc_enabled_full:
				tx_ppp |= tc_mask;
				rx_ppp |= tc_mask;
				अवरोध;
			हाल pfc_enabled_tx:
				tx_ppp |= tc_mask;
				rx_ppp &= ~tc_mask;
				अवरोध;
			हाल pfc_enabled_rx:
				tx_ppp &= ~tc_mask;
				rx_ppp |= tc_mask;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		rx_छोड़ो = !!(rx_ppp || tx_ppp) ? 0 : prof->rx_छोड़ो;
		tx_छोड़ो = !!(rx_ppp || tx_ppp) ? 0 : prof->tx_छोड़ो;
	पूर्ण अन्यथा अणु
		rx_ppp = 0;
		tx_ppp = 0;
		rx_छोड़ो = prof->rx_छोड़ो;
		tx_छोड़ो = prof->tx_छोड़ो;
	पूर्ण

	अगर (mlx4_SET_PORT_general(mdev->dev, priv->port,
				  priv->rx_skb_size + ETH_FCS_LEN,
				  tx_छोड़ो, tx_ppp, rx_छोड़ो, rx_ppp)) अणु
		en_err(priv, "Failed setting pause params\n");
		वापस 1;
	पूर्ण

	prof->tx_ppp = tx_ppp;
	prof->rx_ppp = rx_ppp;
	prof->tx_छोड़ो = tx_छोड़ो;
	prof->rx_छोड़ो = rx_छोड़ो;

	वापस 0;
पूर्ण

अटल u8 mlx4_en_dcbnl_get_state(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	अगर (priv->flags & MLX4_EN_FLAG_DCB_ENABLED)
		वापस MLX4_CEE_STATE_UP;

	वापस MLX4_CEE_STATE_DOWN;
पूर्ण

अटल u8 mlx4_en_dcbnl_set_state(काष्ठा net_device *dev, u8 state)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक num_tcs = 0;

	अगर (!(priv->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस 1;

	अगर (!!(state) == !!(priv->flags & MLX4_EN_FLAG_DCB_ENABLED))
		वापस 0;

	अगर (state) अणु
		priv->flags |= MLX4_EN_FLAG_DCB_ENABLED;
		num_tcs = IEEE_8021QAZ_MAX_TCS;
	पूर्ण अन्यथा अणु
		priv->flags &= ~MLX4_EN_FLAG_DCB_ENABLED;
	पूर्ण

	अगर (mlx4_en_alloc_tx_queue_per_tc(dev, num_tcs))
		वापस 1;

	वापस 0;
पूर्ण

/* On success वापसs a non-zero 802.1p user priority biपंचांगap
 * otherwise वापसs 0 as the invalid user priority biपंचांगap to
 * indicate an error.
 */
अटल पूर्णांक mlx4_en_dcbnl_getapp(काष्ठा net_device *netdev, u8 idtype, u16 id)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);
	काष्ठा dcb_app app = अणु
				.selector = idtype,
				.protocol = id,
			     पूर्ण;
	अगर (!(priv->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस 0;

	वापस dcb_getapp(netdev, &app);
पूर्ण

अटल पूर्णांक mlx4_en_dcbnl_setapp(काष्ठा net_device *netdev, u8 idtype,
				u16 id, u8 up)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);
	काष्ठा dcb_app app;

	अगर (!(priv->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस -EINVAL;

	स_रखो(&app, 0, माप(काष्ठा dcb_app));
	app.selector = idtype;
	app.protocol = id;
	app.priority = up;

	वापस dcb_setapp(netdev, &app);
पूर्ण

अटल पूर्णांक mlx4_en_dcbnl_ieee_getets(काष्ठा net_device *dev,
				   काष्ठा ieee_ets *ets)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा ieee_ets *my_ets = &priv->ets;

	अगर (!my_ets)
		वापस -EINVAL;

	ets->ets_cap = IEEE_8021QAZ_MAX_TCS;
	ets->cbs = my_ets->cbs;
	स_नकल(ets->tc_tx_bw, my_ets->tc_tx_bw, माप(ets->tc_tx_bw));
	स_नकल(ets->tc_tsa, my_ets->tc_tsa, माप(ets->tc_tsa));
	स_नकल(ets->prio_tc, my_ets->prio_tc, माप(ets->prio_tc));

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_ets_validate(काष्ठा mlx4_en_priv *priv, काष्ठा ieee_ets *ets)
अणु
	पूर्णांक i;
	पूर्णांक total_ets_bw = 0;
	पूर्णांक has_ets_tc = 0;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		अगर (ets->prio_tc[i] >= MLX4_EN_NUM_UP_HIGH) अणु
			en_err(priv, "Bad priority in UP <=> TC mapping. TC: %d, UP: %d\n",
					i, ets->prio_tc[i]);
			वापस -EINVAL;
		पूर्ण

		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_VENDOR:
		हाल IEEE_8021QAZ_TSA_STRICT:
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			has_ets_tc = 1;
			total_ets_bw += ets->tc_tx_bw[i];
			अवरोध;
		शेष:
			en_err(priv, "TC[%d]: Not supported TSA: %d\n",
					i, ets->tc_tsa[i]);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (has_ets_tc && total_ets_bw != MLX4_EN_BW_MAX) अणु
		en_err(priv, "Bad ETS BW sum: %d. Should be exactly 100%%\n",
				total_ets_bw);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_config_port_scheduler(काष्ठा mlx4_en_priv *priv,
		काष्ठा ieee_ets *ets, u16 *ratelimit)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक num_strict = 0;
	पूर्णांक i;
	__u8 tc_tx_bw[IEEE_8021QAZ_MAX_TCS] = अणु 0 पूर्ण;
	__u8 pg[IEEE_8021QAZ_MAX_TCS] = अणु 0 पूर्ण;

	ets = ets ?: &priv->ets;
	ratelimit = ratelimit ?: priv->maxrate;

	/* higher TC means higher priority => lower pg */
	क्रम (i = IEEE_8021QAZ_MAX_TCS - 1; i >= 0; i--) अणु
		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_VENDOR:
			pg[i] = MLX4_EN_TC_VENDOR;
			tc_tx_bw[i] = MLX4_EN_BW_MAX;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_STRICT:
			pg[i] = num_strict++;
			tc_tx_bw[i] = MLX4_EN_BW_MAX;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			pg[i] = MLX4_EN_TC_ETS;
			tc_tx_bw[i] = ets->tc_tx_bw[i] ?: MLX4_EN_BW_MIN;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस mlx4_SET_PORT_SCHEDULER(mdev->dev, priv->port, tc_tx_bw, pg,
			ratelimit);
पूर्ण

अटल पूर्णांक
mlx4_en_dcbnl_ieee_setets(काष्ठा net_device *dev, काष्ठा ieee_ets *ets)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err;

	err = mlx4_en_ets_validate(priv, ets);
	अगर (err)
		वापस err;

	err = mlx4_SET_PORT_PRIO2TC(mdev->dev, priv->port, ets->prio_tc);
	अगर (err)
		वापस err;

	err = mlx4_en_config_port_scheduler(priv, ets, शून्य);
	अगर (err)
		वापस err;

	स_नकल(&priv->ets, ets, माप(priv->ets));

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_dcbnl_ieee_getpfc(काष्ठा net_device *dev,
		काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;
	pfc->pfc_en = priv->prof->tx_ppp;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_dcbnl_ieee_setpfc(काष्ठा net_device *dev,
		काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_port_profile *prof = priv->prof;
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	u32 tx_छोड़ो, tx_ppp, rx_छोड़ो, rx_ppp;
	पूर्णांक err;

	en_dbg(DRV, priv, "cap: 0x%x en: 0x%x mbc: 0x%x delay: %d\n",
			pfc->pfc_cap,
			pfc->pfc_en,
			pfc->mbc,
			pfc->delay);

	rx_छोड़ो = prof->rx_छोड़ो && !pfc->pfc_en;
	tx_छोड़ो = prof->tx_छोड़ो && !pfc->pfc_en;
	rx_ppp = pfc->pfc_en;
	tx_ppp = pfc->pfc_en;

	err = mlx4_SET_PORT_general(mdev->dev, priv->port,
				    priv->rx_skb_size + ETH_FCS_LEN,
				    tx_छोड़ो, tx_ppp, rx_छोड़ो, rx_ppp);
	अगर (err) अणु
		en_err(priv, "Failed setting pause params\n");
		वापस err;
	पूर्ण

	mlx4_en_update_pfc_stats_biपंचांगap(mdev->dev, &priv->stats_biपंचांगap,
					rx_ppp, rx_छोड़ो, tx_ppp, tx_छोड़ो);

	prof->tx_ppp = tx_ppp;
	prof->rx_ppp = rx_ppp;
	prof->rx_छोड़ो = rx_छोड़ो;
	prof->tx_छोड़ो = tx_छोड़ो;

	वापस err;
पूर्ण

अटल u8 mlx4_en_dcbnl_getdcbx(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	वापस priv->dcbx_cap;
पूर्ण

अटल u8 mlx4_en_dcbnl_setdcbx(काष्ठा net_device *dev, u8 mode)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा ieee_ets ets = अणु0पूर्ण;
	काष्ठा ieee_pfc pfc = अणु0पूर्ण;

	अगर (mode == priv->dcbx_cap)
		वापस 0;

	अगर ((mode & DCB_CAP_DCBX_LLD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VER_IEEE) &&
	     (mode & DCB_CAP_DCBX_VER_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		जाओ err;

	priv->dcbx_cap = mode;

	ets.ets_cap = IEEE_8021QAZ_MAX_TCS;
	pfc.pfc_cap = IEEE_8021QAZ_MAX_TCS;

	अगर (mode & DCB_CAP_DCBX_VER_IEEE) अणु
		अगर (mlx4_en_dcbnl_ieee_setets(dev, &ets))
			जाओ err;
		अगर (mlx4_en_dcbnl_ieee_setpfc(dev, &pfc))
			जाओ err;
	पूर्ण अन्यथा अगर (mode & DCB_CAP_DCBX_VER_CEE) अणु
		अगर (mlx4_en_dcbnl_set_all(dev))
			जाओ err;
	पूर्ण अन्यथा अणु
		अगर (mlx4_en_dcbnl_ieee_setets(dev, &ets))
			जाओ err;
		अगर (mlx4_en_dcbnl_ieee_setpfc(dev, &pfc))
			जाओ err;
		अगर (mlx4_en_alloc_tx_queue_per_tc(dev, 0))
			जाओ err;
	पूर्ण

	वापस 0;
err:
	वापस 1;
पूर्ण

#घोषणा MLX4_RATELIMIT_UNITS_IN_KB 100000 /* rate-limit HW unit in Kbps */
अटल पूर्णांक mlx4_en_dcbnl_ieee_geपंचांगaxrate(काष्ठा net_device *dev,
				   काष्ठा ieee_maxrate *maxrate)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		maxrate->tc_maxrate[i] =
			priv->maxrate[i] * MLX4_RATELIMIT_UNITS_IN_KB;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_dcbnl_ieee_seपंचांगaxrate(काष्ठा net_device *dev,
		काष्ठा ieee_maxrate *maxrate)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	u16 पंचांगp[IEEE_8021QAZ_MAX_TCS];
	पूर्णांक i, err;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		/* Convert from Kbps पूर्णांकo HW units, rounding result up.
		 * Setting to 0, means unlimited BW.
		 */
		पंचांगp[i] = भाग_u64(maxrate->tc_maxrate[i] +
				 MLX4_RATELIMIT_UNITS_IN_KB - 1,
				 MLX4_RATELIMIT_UNITS_IN_KB);
	पूर्ण

	err = mlx4_en_config_port_scheduler(priv, शून्य, पंचांगp);
	अगर (err)
		वापस err;

	स_नकल(priv->maxrate, पंचांगp, माप(priv->maxrate));

	वापस 0;
पूर्ण

#घोषणा RPG_ENABLE_BIT	31
#घोषणा CN_TAG_BIT	30

अटल पूर्णांक mlx4_en_dcbnl_ieee_getqcn(काष्ठा net_device *dev,
				     काष्ठा ieee_qcn *qcn)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_congestion_control_mb_prio_802_1_qau_params *hw_qcn;
	काष्ठा mlx4_cmd_mailbox *mailbox_out = शून्य;
	u64 mailbox_in_dma = 0;
	u32 inmod = 0;
	पूर्णांक i, err;

	अगर (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QCN))
		वापस -EOPNOTSUPP;

	mailbox_out = mlx4_alloc_cmd_mailbox(priv->mdev->dev);
	अगर (IS_ERR(mailbox_out))
		वापस -ENOMEM;
	hw_qcn =
	(काष्ठा mlx4_congestion_control_mb_prio_802_1_qau_params *)
	mailbox_out->buf;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		inmod = priv->port | ((1 << i) << 8) |
			 (MLX4_CTRL_ALGO_802_1_QAU_REACTION_POINT << 16);
		err = mlx4_cmd_box(priv->mdev->dev, mailbox_in_dma,
				   mailbox_out->dma,
				   inmod, MLX4_CONGESTION_CONTROL_GET_PARAMS,
				   MLX4_CMD_CONGESTION_CTRL_OPCODE,
				   MLX4_CMD_TIME_CLASS_C,
				   MLX4_CMD_NATIVE);
		अगर (err) अणु
			mlx4_मुक्त_cmd_mailbox(priv->mdev->dev, mailbox_out);
			वापस err;
		पूर्ण

		qcn->rpg_enable[i] =
			be32_to_cpu(hw_qcn->extended_enable) >> RPG_ENABLE_BIT;
		qcn->rppp_max_rps[i] =
			be32_to_cpu(hw_qcn->rppp_max_rps);
		qcn->rpg_समय_reset[i] =
			be32_to_cpu(hw_qcn->rpg_समय_reset);
		qcn->rpg_byte_reset[i] =
			be32_to_cpu(hw_qcn->rpg_byte_reset);
		qcn->rpg_threshold[i] =
			be32_to_cpu(hw_qcn->rpg_threshold);
		qcn->rpg_max_rate[i] =
			be32_to_cpu(hw_qcn->rpg_max_rate);
		qcn->rpg_ai_rate[i] =
			be32_to_cpu(hw_qcn->rpg_ai_rate);
		qcn->rpg_hai_rate[i] =
			be32_to_cpu(hw_qcn->rpg_hai_rate);
		qcn->rpg_gd[i] =
			be32_to_cpu(hw_qcn->rpg_gd);
		qcn->rpg_min_dec_fac[i] =
			be32_to_cpu(hw_qcn->rpg_min_dec_fac);
		qcn->rpg_min_rate[i] =
			be32_to_cpu(hw_qcn->rpg_min_rate);
		qcn->cndd_state_machine[i] =
			priv->cndd_state[i];
	पूर्ण
	mlx4_मुक्त_cmd_mailbox(priv->mdev->dev, mailbox_out);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_dcbnl_ieee_setqcn(काष्ठा net_device *dev,
				     काष्ठा ieee_qcn *qcn)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_congestion_control_mb_prio_802_1_qau_params *hw_qcn;
	काष्ठा mlx4_cmd_mailbox *mailbox_in = शून्य;
	u64 mailbox_in_dma = 0;
	u32 inmod = 0;
	पूर्णांक i, err;
#घोषणा MODIFY_ENABLE_HIGH_MASK 0xc0000000
#घोषणा MODIFY_ENABLE_LOW_MASK 0xffc00000

	अगर (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QCN))
		वापस -EOPNOTSUPP;

	mailbox_in = mlx4_alloc_cmd_mailbox(priv->mdev->dev);
	अगर (IS_ERR(mailbox_in))
		वापस -ENOMEM;

	mailbox_in_dma = mailbox_in->dma;
	hw_qcn =
	(काष्ठा mlx4_congestion_control_mb_prio_802_1_qau_params *)mailbox_in->buf;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		inmod = priv->port | ((1 << i) << 8) |
			 (MLX4_CTRL_ALGO_802_1_QAU_REACTION_POINT << 16);

		/* Beक्रमe updating QCN parameter,
		 * need to set it's modअगरy enable bit to 1
		 */

		hw_qcn->modअगरy_enable_high = cpu_to_be32(
						MODIFY_ENABLE_HIGH_MASK);
		hw_qcn->modअगरy_enable_low = cpu_to_be32(MODIFY_ENABLE_LOW_MASK);

		hw_qcn->extended_enable = cpu_to_be32(qcn->rpg_enable[i] << RPG_ENABLE_BIT);
		hw_qcn->rppp_max_rps = cpu_to_be32(qcn->rppp_max_rps[i]);
		hw_qcn->rpg_समय_reset = cpu_to_be32(qcn->rpg_समय_reset[i]);
		hw_qcn->rpg_byte_reset = cpu_to_be32(qcn->rpg_byte_reset[i]);
		hw_qcn->rpg_threshold = cpu_to_be32(qcn->rpg_threshold[i]);
		hw_qcn->rpg_max_rate = cpu_to_be32(qcn->rpg_max_rate[i]);
		hw_qcn->rpg_ai_rate = cpu_to_be32(qcn->rpg_ai_rate[i]);
		hw_qcn->rpg_hai_rate = cpu_to_be32(qcn->rpg_hai_rate[i]);
		hw_qcn->rpg_gd = cpu_to_be32(qcn->rpg_gd[i]);
		hw_qcn->rpg_min_dec_fac = cpu_to_be32(qcn->rpg_min_dec_fac[i]);
		hw_qcn->rpg_min_rate = cpu_to_be32(qcn->rpg_min_rate[i]);
		priv->cndd_state[i] = qcn->cndd_state_machine[i];
		अगर (qcn->cndd_state_machine[i] == DCB_CNDD_INTERIOR_READY)
			hw_qcn->extended_enable |= cpu_to_be32(1 << CN_TAG_BIT);

		err = mlx4_cmd(priv->mdev->dev, mailbox_in_dma, inmod,
			       MLX4_CONGESTION_CONTROL_SET_PARAMS,
			       MLX4_CMD_CONGESTION_CTRL_OPCODE,
			       MLX4_CMD_TIME_CLASS_C,
			       MLX4_CMD_NATIVE);
		अगर (err) अणु
			mlx4_मुक्त_cmd_mailbox(priv->mdev->dev, mailbox_in);
			वापस err;
		पूर्ण
	पूर्ण
	mlx4_मुक्त_cmd_mailbox(priv->mdev->dev, mailbox_in);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_dcbnl_ieee_getqcnstats(काष्ठा net_device *dev,
					  काष्ठा ieee_qcn_stats *qcn_stats)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_congestion_control_mb_prio_802_1_qau_statistics *hw_qcn_stats;
	काष्ठा mlx4_cmd_mailbox *mailbox_out = शून्य;
	u64 mailbox_in_dma = 0;
	u32 inmod = 0;
	पूर्णांक i, err;

	अगर (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QCN))
		वापस -EOPNOTSUPP;

	mailbox_out = mlx4_alloc_cmd_mailbox(priv->mdev->dev);
	अगर (IS_ERR(mailbox_out))
		वापस -ENOMEM;

	hw_qcn_stats =
	(काष्ठा mlx4_congestion_control_mb_prio_802_1_qau_statistics *)
	mailbox_out->buf;

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		inmod = priv->port | ((1 << i) << 8) |
			 (MLX4_CTRL_ALGO_802_1_QAU_REACTION_POINT << 16);
		err = mlx4_cmd_box(priv->mdev->dev, mailbox_in_dma,
				   mailbox_out->dma, inmod,
				   MLX4_CONGESTION_CONTROL_GET_STATISTICS,
				   MLX4_CMD_CONGESTION_CTRL_OPCODE,
				   MLX4_CMD_TIME_CLASS_C,
				   MLX4_CMD_NATIVE);
		अगर (err) अणु
			mlx4_मुक्त_cmd_mailbox(priv->mdev->dev, mailbox_out);
			वापस err;
		पूर्ण
		qcn_stats->rppp_rp_centiseconds[i] =
			be64_to_cpu(hw_qcn_stats->rppp_rp_centiseconds);
		qcn_stats->rppp_created_rps[i] =
			be32_to_cpu(hw_qcn_stats->rppp_created_rps);
	पूर्ण
	mlx4_मुक्त_cmd_mailbox(priv->mdev->dev, mailbox_out);
	वापस 0;
पूर्ण

स्थिर काष्ठा dcbnl_rtnl_ops mlx4_en_dcbnl_ops = अणु
	.ieee_getets		= mlx4_en_dcbnl_ieee_getets,
	.ieee_setets		= mlx4_en_dcbnl_ieee_setets,
	.ieee_geपंचांगaxrate	= mlx4_en_dcbnl_ieee_geपंचांगaxrate,
	.ieee_seपंचांगaxrate	= mlx4_en_dcbnl_ieee_seपंचांगaxrate,
	.ieee_getqcn		= mlx4_en_dcbnl_ieee_getqcn,
	.ieee_setqcn		= mlx4_en_dcbnl_ieee_setqcn,
	.ieee_getqcnstats	= mlx4_en_dcbnl_ieee_getqcnstats,
	.ieee_getpfc		= mlx4_en_dcbnl_ieee_getpfc,
	.ieee_setpfc		= mlx4_en_dcbnl_ieee_setpfc,

	.माला_लोtate	= mlx4_en_dcbnl_get_state,
	.setstate	= mlx4_en_dcbnl_set_state,
	.getpfccfg	= mlx4_en_dcbnl_get_pfc_cfg,
	.setpfccfg	= mlx4_en_dcbnl_set_pfc_cfg,
	.setall		= mlx4_en_dcbnl_set_all,
	.अ_लोap		= mlx4_en_dcbnl_अ_लोap,
	.getnumtcs	= mlx4_en_dcbnl_getnumtcs,
	.getpfcstate	= mlx4_en_dcbnl_getpfcstate,
	.setpfcstate	= mlx4_en_dcbnl_setpfcstate,
	.getapp		= mlx4_en_dcbnl_getapp,
	.setapp		= mlx4_en_dcbnl_setapp,

	.getdcbx	= mlx4_en_dcbnl_getdcbx,
	.setdcbx	= mlx4_en_dcbnl_setdcbx,
पूर्ण;

स्थिर काष्ठा dcbnl_rtnl_ops mlx4_en_dcbnl_pfc_ops = अणु
	.ieee_getpfc	= mlx4_en_dcbnl_ieee_getpfc,
	.ieee_setpfc	= mlx4_en_dcbnl_ieee_setpfc,

	.setstate	= mlx4_en_dcbnl_set_state,
	.getpfccfg	= mlx4_en_dcbnl_get_pfc_cfg,
	.setpfccfg	= mlx4_en_dcbnl_set_pfc_cfg,
	.setall		= mlx4_en_dcbnl_set_all,
	.getnumtcs	= mlx4_en_dcbnl_getnumtcs,
	.getpfcstate	= mlx4_en_dcbnl_getpfcstate,
	.setpfcstate	= mlx4_en_dcbnl_setpfcstate,
	.getapp		= mlx4_en_dcbnl_getapp,
	.setapp		= mlx4_en_dcbnl_setapp,

	.getdcbx	= mlx4_en_dcbnl_getdcbx,
	.setdcbx	= mlx4_en_dcbnl_setdcbx,
पूर्ण;
