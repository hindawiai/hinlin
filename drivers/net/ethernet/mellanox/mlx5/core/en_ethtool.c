<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies. All rights reserved.
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

#समावेश "en.h"
#समावेश "en/port.h"
#समावेश "en/params.h"
#समावेश "en/xsk/pool.h"
#समावेश "en/ptp.h"
#समावेश "lib/clock.h"

व्योम mlx5e_ethtool_get_drvinfo(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	strlcpy(drvinfo->driver, KBUILD_MODNAME, माप(drvinfo->driver));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%d.%d.%04d (%.16s)",
		 fw_rev_maj(mdev), fw_rev_min(mdev), fw_rev_sub(mdev),
		 mdev->board_id);
	strlcpy(drvinfo->bus_info, dev_name(mdev->device),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम mlx5e_get_drvinfo(काष्ठा net_device *dev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_ethtool_get_drvinfo(priv, drvinfo);
पूर्ण

काष्ठा ptys2ethtool_config अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(advertised);
पूर्ण;

अटल
काष्ठा ptys2ethtool_config ptys2legacy_ethtool_table[MLX5E_LINK_MODES_NUMBER];
अटल
काष्ठा ptys2ethtool_config ptys2ext_ethtool_table[MLX5E_EXT_LINK_MODES_NUMBER];

#घोषणा MLX5_BUILD_PTYS2ETHTOOL_CONFIG(reg_, table, ...)                  \
	(अणु                                                              \
		काष्ठा ptys2ethtool_config *cfg;                        \
		स्थिर अचिन्हित पूर्णांक modes[] = अणु __VA_ARGS__ पूर्ण;           \
		अचिन्हित पूर्णांक i, bit, idx;                               \
		cfg = &ptys2##table##_ethtool_table[reg_];		\
		biपंचांगap_zero(cfg->supported,                             \
			    __ETHTOOL_LINK_MODE_MASK_NBITS);            \
		biपंचांगap_zero(cfg->advertised,                            \
			    __ETHTOOL_LINK_MODE_MASK_NBITS);            \
		क्रम (i = 0 ; i < ARRAY_SIZE(modes) ; ++i) अणु             \
			bit = modes[i] % 64;                            \
			idx = modes[i] / 64;                            \
			__set_bit(bit, &cfg->supported[idx]);           \
			__set_bit(bit, &cfg->advertised[idx]);          \
		पूर्ण                                                       \
	पूर्ण)

व्योम mlx5e_build_ptys2ethtool_map(व्योम)
अणु
	स_रखो(ptys2legacy_ethtool_table, 0, माप(ptys2legacy_ethtool_table));
	स_रखो(ptys2ext_ethtool_table, 0, माप(ptys2ext_ethtool_table));
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_1000BASE_CX_SGMII, legacy,
				       ETHTOOL_LINK_MODE_1000baseKX_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_1000BASE_KX, legacy,
				       ETHTOOL_LINK_MODE_1000baseKX_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_CX4, legacy,
				       ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_KX4, legacy,
				       ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_KR, legacy,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_20GBASE_KR2, legacy,
				       ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_CR4, legacy,
				       ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_KR4, legacy,
				       ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_56GBASE_R4, legacy,
				       ETHTOOL_LINK_MODE_56000baseKR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_CR, legacy,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_SR, legacy,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_ER, legacy,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_SR4, legacy,
				       ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_LR4, legacy,
				       ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_50GBASE_SR2, legacy,
				       ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GBASE_CR4, legacy,
				       ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GBASE_SR4, legacy,
				       ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GBASE_KR4, legacy,
				       ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GBASE_LR4, legacy,
				       ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_T, legacy,
				       ETHTOOL_LINK_MODE_10000baseT_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_25GBASE_CR, legacy,
				       ETHTOOL_LINK_MODE_25000baseCR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_25GBASE_KR, legacy,
				       ETHTOOL_LINK_MODE_25000baseKR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_25GBASE_SR, legacy,
				       ETHTOOL_LINK_MODE_25000baseSR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_50GBASE_CR2, legacy,
				       ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_50GBASE_KR2, legacy,
				       ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_SGMII_100M, ext,
				       ETHTOOL_LINK_MODE_100baseT_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_1000BASE_X_SGMII, ext,
				       ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				       ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
				       ETHTOOL_LINK_MODE_1000baseX_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_5GBASE_R, ext,
				       ETHTOOL_LINK_MODE_5000baseT_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_10GBASE_XFI_XAUI_1, ext,
				       ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
				       ETHTOOL_LINK_MODE_10000baseR_FEC_BIT,
				       ETHTOOL_LINK_MODE_10000baseCR_Full_BIT,
				       ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
				       ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
				       ETHTOOL_LINK_MODE_10000baseER_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_40GBASE_XLAUI_4_XLPPI_4, ext,
				       ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
				       ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
				       ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
				       ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_25GAUI_1_25GBASE_CR_KR, ext,
				       ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
				       ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
				       ETHTOOL_LINK_MODE_25000baseSR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_50GAUI_2_LAUI_2_50GBASE_CR2_KR2,
				       ext,
				       ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
				       ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
				       ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_50GAUI_1_LAUI_1_50GBASE_CR_KR, ext,
				       ETHTOOL_LINK_MODE_50000baseKR_Full_BIT,
				       ETHTOOL_LINK_MODE_50000baseSR_Full_BIT,
				       ETHTOOL_LINK_MODE_50000baseCR_Full_BIT,
				       ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT,
				       ETHTOOL_LINK_MODE_50000baseDR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_CAUI_4_100GBASE_CR4_KR4, ext,
				       ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GAUI_2_100GBASE_CR2_KR2, ext,
				       ETHTOOL_LINK_MODE_100000baseKR2_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseSR2_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseCR2_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseLR2_ER2_FR2_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseDR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_200GAUI_4_200GBASE_CR4_KR4, ext,
				       ETHTOOL_LINK_MODE_200000baseKR4_Full_BIT,
				       ETHTOOL_LINK_MODE_200000baseSR4_Full_BIT,
				       ETHTOOL_LINK_MODE_200000baseLR4_ER4_FR4_Full_BIT,
				       ETHTOOL_LINK_MODE_200000baseDR4_Full_BIT,
				       ETHTOOL_LINK_MODE_200000baseCR4_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_100GAUI_1_100GBASE_CR_KR, ext,
				       ETHTOOL_LINK_MODE_100000baseKR_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseSR_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseLR_ER_FR_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseDR_Full_BIT,
				       ETHTOOL_LINK_MODE_100000baseCR_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_200GAUI_2_200GBASE_CR2_KR2, ext,
				       ETHTOOL_LINK_MODE_200000baseKR2_Full_BIT,
				       ETHTOOL_LINK_MODE_200000baseSR2_Full_BIT,
				       ETHTOOL_LINK_MODE_200000baseLR2_ER2_FR2_Full_BIT,
				       ETHTOOL_LINK_MODE_200000baseDR2_Full_BIT,
				       ETHTOOL_LINK_MODE_200000baseCR2_Full_BIT);
	MLX5_BUILD_PTYS2ETHTOOL_CONFIG(MLX5E_400GAUI_4_400GBASE_CR4_KR4, ext,
				       ETHTOOL_LINK_MODE_400000baseKR4_Full_BIT,
				       ETHTOOL_LINK_MODE_400000baseSR4_Full_BIT,
				       ETHTOOL_LINK_MODE_400000baseLR4_ER4_FR4_Full_BIT,
				       ETHTOOL_LINK_MODE_400000baseDR4_Full_BIT,
				       ETHTOOL_LINK_MODE_400000baseCR4_Full_BIT);
पूर्ण

अटल व्योम mlx5e_ethtool_get_speed_arr(काष्ठा mlx5_core_dev *mdev,
					काष्ठा ptys2ethtool_config **arr,
					u32 *size)
अणु
	bool ext = mlx5e_ptys_ext_supported(mdev);

	*arr = ext ? ptys2ext_ethtool_table : ptys2legacy_ethtool_table;
	*size = ext ? ARRAY_SIZE(ptys2ext_ethtool_table) :
		      ARRAY_SIZE(ptys2legacy_ethtool_table);
पूर्ण

प्रकार पूर्णांक (*mlx5e_pflag_handler)(काष्ठा net_device *netdev, bool enable);

काष्ठा pflag_desc अणु
	अक्षर name[ETH_GSTRING_LEN];
	mlx5e_pflag_handler handler;
पूर्ण;

अटल स्थिर काष्ठा pflag_desc mlx5e_priv_flags[MLX5E_NUM_PFLAGS];

पूर्णांक mlx5e_ethtool_get_sset_count(काष्ठा mlx5e_priv *priv, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस mlx5e_stats_total_num(priv);
	हाल ETH_SS_PRIV_FLAGS:
		वापस MLX5E_NUM_PFLAGS;
	हाल ETH_SS_TEST:
		वापस mlx5e_self_test_num(priv);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	वापस mlx5e_ethtool_get_sset_count(priv, sset);
पूर्ण

व्योम mlx5e_ethtool_get_strings(काष्ठा mlx5e_priv *priv, u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_PRIV_FLAGS:
		क्रम (i = 0; i < MLX5E_NUM_PFLAGS; i++)
			म_नकल(data + i * ETH_GSTRING_LEN,
			       mlx5e_priv_flags[i].name);
		अवरोध;

	हाल ETH_SS_TEST:
		क्रम (i = 0; i < mlx5e_self_test_num(priv); i++)
			म_नकल(data + i * ETH_GSTRING_LEN,
			       mlx5e_self_tests[i]);
		अवरोध;

	हाल ETH_SS_STATS:
		mlx5e_stats_fill_strings(priv, data);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_ethtool_get_strings(priv, stringset, data);
पूर्ण

व्योम mlx5e_ethtool_get_ethtool_stats(काष्ठा mlx5e_priv *priv,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक idx = 0;

	mutex_lock(&priv->state_lock);
	mlx5e_stats_update(priv);
	mutex_unlock(&priv->state_lock);

	mlx5e_stats_fill(priv, data, idx);
पूर्ण

अटल व्योम mlx5e_get_ethtool_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *stats,
				    u64 *data)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_ethtool_get_ethtool_stats(priv, stats, data);
पूर्ण

व्योम mlx5e_ethtool_get_ringparam(काष्ठा mlx5e_priv *priv,
				 काष्ठा ethtool_ringparam *param)
अणु
	param->rx_max_pending = 1 << MLX5E_PARAMS_MAXIMUM_LOG_RQ_SIZE;
	param->tx_max_pending = 1 << MLX5E_PARAMS_MAXIMUM_LOG_SQ_SIZE;
	param->rx_pending     = 1 << priv->channels.params.log_rq_mtu_frames;
	param->tx_pending     = 1 << priv->channels.params.log_sq_size;
पूर्ण

अटल व्योम mlx5e_get_ringparam(काष्ठा net_device *dev,
				काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_ethtool_get_ringparam(priv, param);
पूर्ण

पूर्णांक mlx5e_ethtool_set_ringparam(काष्ठा mlx5e_priv *priv,
				काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx5e_params new_params;
	u8 log_rq_size;
	u8 log_sq_size;
	पूर्णांक err = 0;

	अगर (param->rx_jumbo_pending) अणु
		netdev_info(priv->netdev, "%s: rx_jumbo_pending not supported\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (param->rx_mini_pending) अणु
		netdev_info(priv->netdev, "%s: rx_mini_pending not supported\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (param->rx_pending < (1 << MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE)) अणु
		netdev_info(priv->netdev, "%s: rx_pending (%d) < min (%d)\n",
			    __func__, param->rx_pending,
			    1 << MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE);
		वापस -EINVAL;
	पूर्ण

	अगर (param->tx_pending < (1 << MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE)) अणु
		netdev_info(priv->netdev, "%s: tx_pending (%d) < min (%d)\n",
			    __func__, param->tx_pending,
			    1 << MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE);
		वापस -EINVAL;
	पूर्ण

	log_rq_size = order_base_2(param->rx_pending);
	log_sq_size = order_base_2(param->tx_pending);

	अगर (log_rq_size == priv->channels.params.log_rq_mtu_frames &&
	    log_sq_size == priv->channels.params.log_sq_size)
		वापस 0;

	mutex_lock(&priv->state_lock);

	new_params = priv->channels.params;
	new_params.log_rq_mtu_frames = log_rq_size;
	new_params.log_sq_size = log_sq_size;

	err = mlx5e_validate_params(priv->mdev, &new_params);
	अगर (err)
		जाओ unlock;

	err = mlx5e_safe_चयन_params(priv, &new_params, शून्य, शून्य, true);

unlock:
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_set_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	वापस mlx5e_ethtool_set_ringparam(priv, param);
पूर्ण

व्योम mlx5e_ethtool_get_channels(काष्ठा mlx5e_priv *priv,
				काष्ठा ethtool_channels *ch)
अणु
	mutex_lock(&priv->state_lock);

	ch->max_combined   = priv->max_nch;
	ch->combined_count = priv->channels.params.num_channels;
	अगर (priv->xsk.refcnt) अणु
		/* The upper half are XSK queues. */
		ch->max_combined *= 2;
		ch->combined_count *= 2;
	पूर्ण

	mutex_unlock(&priv->state_lock);
पूर्ण

अटल व्योम mlx5e_get_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *ch)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_ethtool_get_channels(priv, ch);
पूर्ण

पूर्णांक mlx5e_ethtool_set_channels(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_channels *ch)
अणु
	काष्ठा mlx5e_params *cur_params = &priv->channels.params;
	अचिन्हित पूर्णांक count = ch->combined_count;
	काष्ठा mlx5e_params new_params;
	bool arfs_enabled;
	bool खोलोed;
	पूर्णांक err = 0;

	अगर (!count) अणु
		netdev_info(priv->netdev, "%s: combined_count=0 not supported\n",
			    __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (cur_params->num_channels == count)
		वापस 0;

	mutex_lock(&priv->state_lock);

	/* Don't allow changing the number of channels अगर there is an active
	 * XSK, because the numeration of the XSK and regular RQs will change.
	 */
	अगर (priv->xsk.refcnt) अणु
		err = -EINVAL;
		netdev_err(priv->netdev, "%s: AF_XDP is active, cannot change the number of channels\n",
			   __func__);
		जाओ out;
	पूर्ण

	/* Don't allow changing the number of channels अगर HTB offload is active,
	 * because the numeration of the QoS SQs will change, जबतक per-queue
	 * qdiscs are attached.
	 */
	अगर (priv->htb.maj_id) अणु
		err = -EINVAL;
		netdev_err(priv->netdev, "%s: HTB offload is active, cannot change the number of channels\n",
			   __func__);
		जाओ out;
	पूर्ण

	new_params = *cur_params;
	new_params.num_channels = count;

	खोलोed = test_bit(MLX5E_STATE_OPENED, &priv->state);

	arfs_enabled = खोलोed && (priv->netdev->features & NETIF_F_NTUPLE);
	अगर (arfs_enabled)
		mlx5e_arfs_disable(priv);

	/* Switch to new channels, set new parameters and बंद old ones */
	err = mlx5e_safe_चयन_params(priv, &new_params,
				       mlx5e_num_channels_changed_ctx, शून्य, true);

	अगर (arfs_enabled) अणु
		पूर्णांक err2 = mlx5e_arfs_enable(priv);

		अगर (err2)
			netdev_err(priv->netdev, "%s: mlx5e_arfs_enable failed: %d\n",
				   __func__, err2);
	पूर्ण

out:
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_set_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	वापस mlx5e_ethtool_set_channels(priv, ch);
पूर्ण

पूर्णांक mlx5e_ethtool_get_coalesce(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा dim_cq_moder *rx_moder, *tx_moder;

	अगर (!MLX5_CAP_GEN(priv->mdev, cq_moderation))
		वापस -EOPNOTSUPP;

	rx_moder = &priv->channels.params.rx_cq_moderation;
	coal->rx_coalesce_usecs		= rx_moder->usec;
	coal->rx_max_coalesced_frames	= rx_moder->pkts;
	coal->use_adaptive_rx_coalesce	= priv->channels.params.rx_dim_enabled;

	tx_moder = &priv->channels.params.tx_cq_moderation;
	coal->tx_coalesce_usecs		= tx_moder->usec;
	coal->tx_max_coalesced_frames	= tx_moder->pkts;
	coal->use_adaptive_tx_coalesce	= priv->channels.params.tx_dim_enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_get_coalesce(priv, coal);
पूर्ण

#घोषणा MLX5E_MAX_COAL_TIME		MLX5_MAX_CQ_PERIOD
#घोषणा MLX5E_MAX_COAL_FRAMES		MLX5_MAX_CQ_COUNT

अटल व्योम
mlx5e_set_priv_channels_tx_coalesce(काष्ठा mlx5e_priv *priv, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक tc;
	पूर्णांक i;

	क्रम (i = 0; i < priv->channels.num; ++i) अणु
		काष्ठा mlx5e_channel *c = priv->channels.c[i];

		क्रम (tc = 0; tc < c->num_tc; tc++) अणु
			mlx5_core_modअगरy_cq_moderation(mdev,
						&c->sq[tc].cq.mcq,
						coal->tx_coalesce_usecs,
						coal->tx_max_coalesced_frames);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mlx5e_set_priv_channels_rx_coalesce(काष्ठा mlx5e_priv *priv, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक i;

	क्रम (i = 0; i < priv->channels.num; ++i) अणु
		काष्ठा mlx5e_channel *c = priv->channels.c[i];

		mlx5_core_modअगरy_cq_moderation(mdev, &c->rq.cq.mcq,
					       coal->rx_coalesce_usecs,
					       coal->rx_max_coalesced_frames);
	पूर्ण
पूर्ण

पूर्णांक mlx5e_ethtool_set_coalesce(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा dim_cq_moder *rx_moder, *tx_moder;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_params new_params;
	bool reset_rx, reset_tx;
	bool reset = true;
	पूर्णांक err = 0;

	अगर (!MLX5_CAP_GEN(mdev, cq_moderation))
		वापस -EOPNOTSUPP;

	अगर (coal->tx_coalesce_usecs > MLX5E_MAX_COAL_TIME ||
	    coal->rx_coalesce_usecs > MLX5E_MAX_COAL_TIME) अणु
		netdev_info(priv->netdev, "%s: maximum coalesce time supported is %lu usecs\n",
			    __func__, MLX5E_MAX_COAL_TIME);
		वापस -दुस्फल;
	पूर्ण

	अगर (coal->tx_max_coalesced_frames > MLX5E_MAX_COAL_FRAMES ||
	    coal->rx_max_coalesced_frames > MLX5E_MAX_COAL_FRAMES) अणु
		netdev_info(priv->netdev, "%s: maximum coalesced frames supported is %lu\n",
			    __func__, MLX5E_MAX_COAL_FRAMES);
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&priv->state_lock);
	new_params = priv->channels.params;

	rx_moder          = &new_params.rx_cq_moderation;
	rx_moder->usec    = coal->rx_coalesce_usecs;
	rx_moder->pkts    = coal->rx_max_coalesced_frames;
	new_params.rx_dim_enabled = !!coal->use_adaptive_rx_coalesce;

	tx_moder          = &new_params.tx_cq_moderation;
	tx_moder->usec    = coal->tx_coalesce_usecs;
	tx_moder->pkts    = coal->tx_max_coalesced_frames;
	new_params.tx_dim_enabled = !!coal->use_adaptive_tx_coalesce;

	reset_rx = !!coal->use_adaptive_rx_coalesce != priv->channels.params.rx_dim_enabled;
	reset_tx = !!coal->use_adaptive_tx_coalesce != priv->channels.params.tx_dim_enabled;

	अगर (reset_rx) अणु
		u8 mode = MLX5E_GET_PFLAG(&new_params,
					  MLX5E_PFLAG_RX_CQE_BASED_MODER);

		mlx5e_reset_rx_moderation(&new_params, mode);
	पूर्ण
	अगर (reset_tx) अणु
		u8 mode = MLX5E_GET_PFLAG(&new_params,
					  MLX5E_PFLAG_TX_CQE_BASED_MODER);

		mlx5e_reset_tx_moderation(&new_params, mode);
	पूर्ण

	/* If DIM state hasn't changed, it's possible to modअगरy पूर्णांकerrupt
	 * moderation parameters on the fly, even अगर the channels are खोलो.
	 */
	अगर (!reset_rx && !reset_tx && test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		अगर (!coal->use_adaptive_rx_coalesce)
			mlx5e_set_priv_channels_rx_coalesce(priv, coal);
		अगर (!coal->use_adaptive_tx_coalesce)
			mlx5e_set_priv_channels_tx_coalesce(priv, coal);
		reset = false;
	पूर्ण

	err = mlx5e_safe_चयन_params(priv, &new_params, शून्य, शून्य, reset);

	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_set_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx5e_priv *priv    = netdev_priv(netdev);

	वापस mlx5e_ethtool_set_coalesce(priv, coal);
पूर्ण

अटल व्योम ptys2ethtool_supported_link(काष्ठा mlx5_core_dev *mdev,
					अचिन्हित दीर्घ *supported_modes,
					u32 eth_proto_cap)
अणु
	अचिन्हित दीर्घ proto_cap = eth_proto_cap;
	काष्ठा ptys2ethtool_config *table;
	u32 max_size;
	पूर्णांक proto;

	mlx5e_ethtool_get_speed_arr(mdev, &table, &max_size);
	क्रम_each_set_bit(proto, &proto_cap, max_size)
		biपंचांगap_or(supported_modes, supported_modes,
			  table[proto].supported,
			  __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल व्योम ptys2ethtool_adver_link(अचिन्हित दीर्घ *advertising_modes,
				    u32 eth_proto_cap, bool ext)
अणु
	अचिन्हित दीर्घ proto_cap = eth_proto_cap;
	काष्ठा ptys2ethtool_config *table;
	u32 max_size;
	पूर्णांक proto;

	table = ext ? ptys2ext_ethtool_table : ptys2legacy_ethtool_table;
	max_size = ext ? ARRAY_SIZE(ptys2ext_ethtool_table) :
			 ARRAY_SIZE(ptys2legacy_ethtool_table);

	क्रम_each_set_bit(proto, &proto_cap, max_size)
		biपंचांगap_or(advertising_modes, advertising_modes,
			  table[proto].advertised,
			  __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल स्थिर u32 pplm_fec_2_ethtool[] = अणु
	[MLX5E_FEC_NOFEC] = ETHTOOL_FEC_OFF,
	[MLX5E_FEC_FIRECODE] = ETHTOOL_FEC_BASER,
	[MLX5E_FEC_RS_528_514] = ETHTOOL_FEC_RS,
	[MLX5E_FEC_RS_544_514] = ETHTOOL_FEC_RS,
	[MLX5E_FEC_LLRS_272_257_1] = ETHTOOL_FEC_LLRS,
पूर्ण;

अटल u32 pplm2ethtool_fec(u_दीर्घ fec_mode, अचिन्हित दीर्घ size)
अणु
	पूर्णांक mode = 0;

	अगर (!fec_mode)
		वापस ETHTOOL_FEC_AUTO;

	mode = find_first_bit(&fec_mode, size);

	अगर (mode < ARRAY_SIZE(pplm_fec_2_ethtool))
		वापस pplm_fec_2_ethtool[mode];

	वापस 0;
पूर्ण

#घोषणा MLX5E_ADVERTISE_SUPPORTED_FEC(mlx5_fec, ethtool_fec)		\
	करो अणु								\
		अगर (mlx5e_fec_in_caps(dev, 1 << (mlx5_fec)))		\
			__set_bit(ethtool_fec,				\
				  link_ksettings->link_modes.supported);\
	पूर्ण जबतक (0)

अटल स्थिर u32 pplm_fec_2_ethtool_linkmodes[] = अणु
	[MLX5E_FEC_NOFEC] = ETHTOOL_LINK_MODE_FEC_NONE_BIT,
	[MLX5E_FEC_FIRECODE] = ETHTOOL_LINK_MODE_FEC_BASER_BIT,
	[MLX5E_FEC_RS_528_514] = ETHTOOL_LINK_MODE_FEC_RS_BIT,
	[MLX5E_FEC_RS_544_514] = ETHTOOL_LINK_MODE_FEC_RS_BIT,
	[MLX5E_FEC_LLRS_272_257_1] = ETHTOOL_LINK_MODE_FEC_LLRS_BIT,
पूर्ण;

अटल पूर्णांक get_fec_supported_advertised(काष्ठा mlx5_core_dev *dev,
					काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	अचिन्हित दीर्घ active_fec_दीर्घ;
	u32 active_fec;
	u32 bitn;
	पूर्णांक err;

	err = mlx5e_get_fec_mode(dev, &active_fec, शून्य);
	अगर (err)
		वापस (err == -EOPNOTSUPP) ? 0 : err;

	MLX5E_ADVERTISE_SUPPORTED_FEC(MLX5E_FEC_NOFEC,
				      ETHTOOL_LINK_MODE_FEC_NONE_BIT);
	MLX5E_ADVERTISE_SUPPORTED_FEC(MLX5E_FEC_FIRECODE,
				      ETHTOOL_LINK_MODE_FEC_BASER_BIT);
	MLX5E_ADVERTISE_SUPPORTED_FEC(MLX5E_FEC_RS_528_514,
				      ETHTOOL_LINK_MODE_FEC_RS_BIT);
	MLX5E_ADVERTISE_SUPPORTED_FEC(MLX5E_FEC_LLRS_272_257_1,
				      ETHTOOL_LINK_MODE_FEC_LLRS_BIT);

	active_fec_दीर्घ = active_fec;
	/* active fec is a bit set, find out which bit is set and
	 * advertise the corresponding ethtool bit
	 */
	bitn = find_first_bit(&active_fec_दीर्घ, माप(active_fec_दीर्घ) * BITS_PER_BYTE);
	अगर (bitn < ARRAY_SIZE(pplm_fec_2_ethtool_linkmodes))
		__set_bit(pplm_fec_2_ethtool_linkmodes[bitn],
			  link_ksettings->link_modes.advertising);

	वापस 0;
पूर्ण

अटल व्योम ptys2ethtool_supported_advertised_port(काष्ठा mlx5_core_dev *mdev,
						   काष्ठा ethtool_link_ksettings *link_ksettings,
						   u32 eth_proto_cap, u8 connector_type)
अणु
	अगर (!MLX5_CAP_PCAM_FEATURE(mdev, ptys_connector_type)) अणु
		अगर (eth_proto_cap & (MLX5E_PROT_MASK(MLX5E_10GBASE_CR)
				   | MLX5E_PROT_MASK(MLX5E_10GBASE_SR)
				   | MLX5E_PROT_MASK(MLX5E_40GBASE_CR4)
				   | MLX5E_PROT_MASK(MLX5E_40GBASE_SR4)
				   | MLX5E_PROT_MASK(MLX5E_100GBASE_SR4)
				   | MLX5E_PROT_MASK(MLX5E_1000BASE_CX_SGMII))) अणु
			ethtool_link_ksettings_add_link_mode(link_ksettings,
							     supported,
							     FIBRE);
			ethtool_link_ksettings_add_link_mode(link_ksettings,
							     advertising,
							     FIBRE);
		पूर्ण

		अगर (eth_proto_cap & (MLX5E_PROT_MASK(MLX5E_100GBASE_KR4)
				   | MLX5E_PROT_MASK(MLX5E_40GBASE_KR4)
				   | MLX5E_PROT_MASK(MLX5E_10GBASE_KR)
				   | MLX5E_PROT_MASK(MLX5E_10GBASE_KX4)
				   | MLX5E_PROT_MASK(MLX5E_1000BASE_KX))) अणु
			ethtool_link_ksettings_add_link_mode(link_ksettings,
							     supported,
							     Backplane);
			ethtool_link_ksettings_add_link_mode(link_ksettings,
							     advertising,
							     Backplane);
		पूर्ण
		वापस;
	पूर्ण

	चयन (connector_type) अणु
	हाल MLX5E_PORT_TP:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, TP);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, TP);
		अवरोध;
	हाल MLX5E_PORT_AUI:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, AUI);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, AUI);
		अवरोध;
	हाल MLX5E_PORT_BNC:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, BNC);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, BNC);
		अवरोध;
	हाल MLX5E_PORT_MII:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, MII);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, MII);
		अवरोध;
	हाल MLX5E_PORT_FIBRE:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, FIBRE);
		अवरोध;
	हाल MLX5E_PORT_DA:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Backplane);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Backplane);
		अवरोध;
	हाल MLX5E_PORT_NONE:
	हाल MLX5E_PORT_OTHER:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम get_speed_duplex(काष्ठा net_device *netdev,
			     u32 eth_proto_oper, bool क्रमce_legacy,
			     u16 data_rate_oper,
			     काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	u32 speed = SPEED_UNKNOWN;
	u8 duplex = DUPLEX_UNKNOWN;

	अगर (!netअगर_carrier_ok(netdev))
		जाओ out;

	speed = mlx5e_port_ptys2speed(priv->mdev, eth_proto_oper, क्रमce_legacy);
	अगर (!speed) अणु
		अगर (data_rate_oper)
			speed = 100 * data_rate_oper;
		अन्यथा
			speed = SPEED_UNKNOWN;
		जाओ out;
	पूर्ण

	duplex = DUPLEX_FULL;

out:
	link_ksettings->base.speed = speed;
	link_ksettings->base.duplex = duplex;
पूर्ण

अटल व्योम get_supported(काष्ठा mlx5_core_dev *mdev, u32 eth_proto_cap,
			  काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	अचिन्हित दीर्घ *supported = link_ksettings->link_modes.supported;
	ptys2ethtool_supported_link(mdev, supported, eth_proto_cap);

	ethtool_link_ksettings_add_link_mode(link_ksettings, supported, Pause);
पूर्ण

अटल व्योम get_advertising(u32 eth_proto_cap, u8 tx_छोड़ो, u8 rx_छोड़ो,
			    काष्ठा ethtool_link_ksettings *link_ksettings,
			    bool ext)
अणु
	अचिन्हित दीर्घ *advertising = link_ksettings->link_modes.advertising;
	ptys2ethtool_adver_link(advertising, eth_proto_cap, ext);

	अगर (rx_छोड़ो)
		ethtool_link_ksettings_add_link_mode(link_ksettings, advertising, Pause);
	अगर (tx_छोड़ो ^ rx_छोड़ो)
		ethtool_link_ksettings_add_link_mode(link_ksettings, advertising, Asym_Pause);
पूर्ण

अटल पूर्णांक ptys2connector_type[MLX5E_CONNECTOR_TYPE_NUMBER] = अणु
		[MLX5E_PORT_UNKNOWN]            = PORT_OTHER,
		[MLX5E_PORT_NONE]               = PORT_NONE,
		[MLX5E_PORT_TP]                 = PORT_TP,
		[MLX5E_PORT_AUI]                = PORT_AUI,
		[MLX5E_PORT_BNC]                = PORT_BNC,
		[MLX5E_PORT_MII]                = PORT_MII,
		[MLX5E_PORT_FIBRE]              = PORT_FIBRE,
		[MLX5E_PORT_DA]                 = PORT_DA,
		[MLX5E_PORT_OTHER]              = PORT_OTHER,
	पूर्ण;

अटल u8 get_connector_port(काष्ठा mlx5_core_dev *mdev, u32 eth_proto, u8 connector_type)
अणु
	अगर (MLX5_CAP_PCAM_FEATURE(mdev, ptys_connector_type))
		वापस ptys2connector_type[connector_type];

	अगर (eth_proto &
	    (MLX5E_PROT_MASK(MLX5E_10GBASE_SR)   |
	     MLX5E_PROT_MASK(MLX5E_40GBASE_SR4)  |
	     MLX5E_PROT_MASK(MLX5E_100GBASE_SR4) |
	     MLX5E_PROT_MASK(MLX5E_1000BASE_CX_SGMII))) अणु
		वापस PORT_FIBRE;
	पूर्ण

	अगर (eth_proto &
	    (MLX5E_PROT_MASK(MLX5E_40GBASE_CR4) |
	     MLX5E_PROT_MASK(MLX5E_10GBASE_CR)  |
	     MLX5E_PROT_MASK(MLX5E_100GBASE_CR4))) अणु
		वापस PORT_DA;
	पूर्ण

	अगर (eth_proto &
	    (MLX5E_PROT_MASK(MLX5E_10GBASE_KX4) |
	     MLX5E_PROT_MASK(MLX5E_10GBASE_KR)  |
	     MLX5E_PROT_MASK(MLX5E_40GBASE_KR4) |
	     MLX5E_PROT_MASK(MLX5E_100GBASE_KR4))) अणु
		वापस PORT_NONE;
	पूर्ण

	वापस PORT_OTHER;
पूर्ण

अटल व्योम get_lp_advertising(काष्ठा mlx5_core_dev *mdev, u32 eth_proto_lp,
			       काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	अचिन्हित दीर्घ *lp_advertising = link_ksettings->link_modes.lp_advertising;
	bool ext = mlx5e_ptys_ext_supported(mdev);

	ptys2ethtool_adver_link(lp_advertising, eth_proto_lp, ext);
पूर्ण

पूर्णांक mlx5e_ethtool_get_link_ksettings(काष्ठा mlx5e_priv *priv,
				     काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 out[MLX5_ST_SZ_DW(ptys_reg)] = अणुपूर्ण;
	u32 eth_proto_admin;
	u8 an_disable_admin;
	u16 data_rate_oper;
	u32 eth_proto_oper;
	u32 eth_proto_cap;
	u8 connector_type;
	u32 rx_छोड़ो = 0;
	u32 tx_छोड़ो = 0;
	u32 eth_proto_lp;
	bool admin_ext;
	u8 an_status;
	bool ext;
	पूर्णांक err;

	err = mlx5_query_port_ptys(mdev, out, माप(out), MLX5_PTYS_EN, 1);
	अगर (err) अणु
		netdev_err(priv->netdev, "%s: query port ptys failed: %d\n",
			   __func__, err);
		जाओ err_query_regs;
	पूर्ण
	ext = !!MLX5_GET_ETH_PROTO(ptys_reg, out, true, eth_proto_capability);
	eth_proto_cap    = MLX5_GET_ETH_PROTO(ptys_reg, out, ext,
					      eth_proto_capability);
	eth_proto_admin  = MLX5_GET_ETH_PROTO(ptys_reg, out, ext,
					      eth_proto_admin);
	/* Fields: eth_proto_admin and ext_eth_proto_admin  are
	 * mutually exclusive. Hence try पढ़ोing legacy advertising
	 * when extended advertising is zero.
	 * admin_ext indicates which proto_admin (ext vs. legacy)
	 * should be पढ़ो and पूर्णांकerpreted
	 */
	admin_ext = ext;
	अगर (ext && !eth_proto_admin) अणु
		eth_proto_admin  = MLX5_GET_ETH_PROTO(ptys_reg, out, false,
						      eth_proto_admin);
		admin_ext = false;
	पूर्ण

	eth_proto_oper   = MLX5_GET_ETH_PROTO(ptys_reg, out, admin_ext,
					      eth_proto_oper);
	eth_proto_lp	    = MLX5_GET(ptys_reg, out, eth_proto_lp_advertise);
	an_disable_admin    = MLX5_GET(ptys_reg, out, an_disable_admin);
	an_status	    = MLX5_GET(ptys_reg, out, an_status);
	connector_type	    = MLX5_GET(ptys_reg, out, connector_type);
	data_rate_oper	    = MLX5_GET(ptys_reg, out, data_rate_oper);

	mlx5_query_port_छोड़ो(mdev, &rx_छोड़ो, &tx_छोड़ो);

	ethtool_link_ksettings_zero_link_mode(link_ksettings, supported);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, advertising);

	get_supported(mdev, eth_proto_cap, link_ksettings);
	get_advertising(eth_proto_admin, tx_छोड़ो, rx_छोड़ो, link_ksettings,
			admin_ext);
	get_speed_duplex(priv->netdev, eth_proto_oper, !admin_ext,
			 data_rate_oper, link_ksettings);

	eth_proto_oper = eth_proto_oper ? eth_proto_oper : eth_proto_cap;
	connector_type = connector_type < MLX5E_CONNECTOR_TYPE_NUMBER ?
			 connector_type : MLX5E_PORT_UNKNOWN;
	link_ksettings->base.port = get_connector_port(mdev, eth_proto_oper, connector_type);
	ptys2ethtool_supported_advertised_port(mdev, link_ksettings, eth_proto_admin,
					       connector_type);
	get_lp_advertising(mdev, eth_proto_lp, link_ksettings);

	अगर (an_status == MLX5_AN_COMPLETE)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     lp_advertising, Autoneg);

	link_ksettings->base.स्वतःneg = an_disable_admin ? AUTONEG_DISABLE :
							  AUTONEG_ENABLE;
	ethtool_link_ksettings_add_link_mode(link_ksettings, supported,
					     Autoneg);

	err = get_fec_supported_advertised(mdev, link_ksettings);
	अगर (err) अणु
		netdev_dbg(priv->netdev, "%s: FEC caps query failed: %d\n",
			   __func__, err);
		err = 0; /* करोn't fail caps query because of FEC error */
	पूर्ण

	अगर (!an_disable_admin)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Autoneg);

err_query_regs:
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_get_link_ksettings(priv, link_ksettings);
पूर्ण

अटल पूर्णांक mlx5e_speed_validate(काष्ठा net_device *netdev, bool ext,
				स्थिर अचिन्हित दीर्घ link_modes, u8 स्वतःneg)
अणु
	/* Extended link-mode has no speed limitations. */
	अगर (ext)
		वापस 0;

	अगर ((link_modes & MLX5E_PROT_MASK(MLX5E_56GBASE_R4)) &&
	    स्वतःneg != AUTONEG_ENABLE) अणु
		netdev_err(netdev, "%s: 56G link speed requires autoneg enabled\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 mlx5e_ethtool2ptys_adver_link(स्थिर अचिन्हित दीर्घ *link_modes)
अणु
	u32 i, ptys_modes = 0;

	क्रम (i = 0; i < MLX5E_LINK_MODES_NUMBER; ++i) अणु
		अगर (*ptys2legacy_ethtool_table[i].advertised == 0)
			जारी;
		अगर (biपंचांगap_पूर्णांकersects(ptys2legacy_ethtool_table[i].advertised,
				      link_modes,
				      __ETHTOOL_LINK_MODE_MASK_NBITS))
			ptys_modes |= MLX5E_PROT_MASK(i);
	पूर्ण

	वापस ptys_modes;
पूर्ण

अटल u32 mlx5e_ethtool2ptys_ext_adver_link(स्थिर अचिन्हित दीर्घ *link_modes)
अणु
	u32 i, ptys_modes = 0;
	अचिन्हित दीर्घ modes[2];

	क्रम (i = 0; i < MLX5E_EXT_LINK_MODES_NUMBER; ++i) अणु
		अगर (ptys2ext_ethtool_table[i].advertised[0] == 0 &&
		    ptys2ext_ethtool_table[i].advertised[1] == 0)
			जारी;
		स_रखो(modes, 0, माप(modes));
		biपंचांगap_and(modes, ptys2ext_ethtool_table[i].advertised,
			   link_modes, __ETHTOOL_LINK_MODE_MASK_NBITS);

		अगर (modes[0] == ptys2ext_ethtool_table[i].advertised[0] &&
		    modes[1] == ptys2ext_ethtool_table[i].advertised[1])
			ptys_modes |= MLX5E_PROT_MASK(i);
	पूर्ण
	वापस ptys_modes;
पूर्ण

अटल bool ext_link_mode_requested(स्थिर अचिन्हित दीर्घ *adver)
अणु
#घोषणा MLX5E_MIN_PTYS_EXT_LINK_MODE_BIT ETHTOOL_LINK_MODE_50000baseKR_Full_BIT
	पूर्णांक size = __ETHTOOL_LINK_MODE_MASK_NBITS - MLX5E_MIN_PTYS_EXT_LINK_MODE_BIT;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(modes) = अणु0,पूर्ण;

	biपंचांगap_set(modes, MLX5E_MIN_PTYS_EXT_LINK_MODE_BIT, size);
	वापस biपंचांगap_पूर्णांकersects(modes, adver, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल bool ext_requested(u8 स्वतःneg, स्थिर अचिन्हित दीर्घ *adver, bool ext_supported)
अणु
	bool ext_link_mode = ext_link_mode_requested(adver);

	वापस  स्वतःneg == AUTONEG_ENABLE ? ext_link_mode : ext_supported;
पूर्ण

पूर्णांक mlx5e_ethtool_set_link_ksettings(काष्ठा mlx5e_priv *priv,
				     स्थिर काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_port_eth_proto eproto;
	स्थिर अचिन्हित दीर्घ *adver;
	bool an_changes = false;
	u8 an_disable_admin;
	bool ext_supported;
	u8 an_disable_cap;
	bool an_disable;
	u32 link_modes;
	u8 an_status;
	u8 स्वतःneg;
	u32 speed;
	bool ext;
	पूर्णांक err;

	u32 (*ethtool2ptys_adver_func)(स्थिर अचिन्हित दीर्घ *adver);

	adver = link_ksettings->link_modes.advertising;
	स्वतःneg = link_ksettings->base.स्वतःneg;
	speed = link_ksettings->base.speed;

	ext_supported = mlx5e_ptys_ext_supported(mdev);
	ext = ext_requested(स्वतःneg, adver, ext_supported);
	अगर (!ext_supported && ext)
		वापस -EOPNOTSUPP;

	ethtool2ptys_adver_func = ext ? mlx5e_ethtool2ptys_ext_adver_link :
				  mlx5e_ethtool2ptys_adver_link;
	err = mlx5_port_query_eth_proto(mdev, 1, ext, &eproto);
	अगर (err) अणु
		netdev_err(priv->netdev, "%s: query port eth proto failed: %d\n",
			   __func__, err);
		जाओ out;
	पूर्ण
	link_modes = स्वतःneg == AUTONEG_ENABLE ? ethtool2ptys_adver_func(adver) :
		mlx5e_port_speed2linkmodes(mdev, speed, !ext);

	err = mlx5e_speed_validate(priv->netdev, ext, link_modes, स्वतःneg);
	अगर (err)
		जाओ out;

	link_modes = link_modes & eproto.cap;
	अगर (!link_modes) अणु
		netdev_err(priv->netdev, "%s: Not supported link mode(s) requested",
			   __func__);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	mlx5_port_query_eth_स्वतःneg(mdev, &an_status, &an_disable_cap,
				    &an_disable_admin);

	an_disable = स्वतःneg == AUTONEG_DISABLE;
	an_changes = ((!an_disable && an_disable_admin) ||
		      (an_disable && !an_disable_admin));

	अगर (!an_changes && link_modes == eproto.admin)
		जाओ out;

	mlx5_port_set_eth_ptys(mdev, an_disable, link_modes, ext);
	mlx5_toggle_port_link(mdev);

out:
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_set_link_ksettings(काष्ठा net_device *netdev,
				    स्थिर काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_set_link_ksettings(priv, link_ksettings);
पूर्ण

u32 mlx5e_ethtool_get_rxfh_key_size(काष्ठा mlx5e_priv *priv)
अणु
	वापस माप(priv->rss_params.toeplitz_hash_key);
पूर्ण

अटल u32 mlx5e_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_get_rxfh_key_size(priv);
पूर्ण

u32 mlx5e_ethtool_get_rxfh_indir_size(काष्ठा mlx5e_priv *priv)
अणु
	वापस MLX5E_INसूची_RQT_SIZE;
पूर्ण

अटल u32 mlx5e_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_get_rxfh_indir_size(priv);
पूर्ण

पूर्णांक mlx5e_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
		   u8 *hfunc)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_rss_params *rss = &priv->rss_params;

	अगर (indir)
		स_नकल(indir, rss->indirection_rqt,
		       माप(rss->indirection_rqt));

	अगर (key)
		स_नकल(key, rss->toeplitz_hash_key,
		       माप(rss->toeplitz_hash_key));

	अगर (hfunc)
		*hfunc = rss->hfunc;

	वापस 0;
पूर्ण

पूर्णांक mlx5e_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
		   स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_rss_params *rss = &priv->rss_params;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_tir_in);
	bool refresh_tirs = false;
	bool refresh_rqt = false;
	व्योम *in;

	अगर ((hfunc != ETH_RSS_HASH_NO_CHANGE) &&
	    (hfunc != ETH_RSS_HASH_XOR) &&
	    (hfunc != ETH_RSS_HASH_TOP))
		वापस -EINVAL;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	mutex_lock(&priv->state_lock);

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != rss->hfunc) अणु
		rss->hfunc = hfunc;
		refresh_rqt = true;
		refresh_tirs = true;
	पूर्ण

	अगर (indir) अणु
		स_नकल(rss->indirection_rqt, indir,
		       माप(rss->indirection_rqt));
		refresh_rqt = true;
	पूर्ण

	अगर (key) अणु
		स_नकल(rss->toeplitz_hash_key, key,
		       माप(rss->toeplitz_hash_key));
		refresh_tirs = refresh_tirs || rss->hfunc == ETH_RSS_HASH_TOP;
	पूर्ण

	अगर (refresh_rqt && test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		काष्ठा mlx5e_redirect_rqt_param rrp = अणु
			.is_rss = true,
			अणु
				.rss = अणु
					.hfunc = rss->hfunc,
					.channels  = &priv->channels,
				पूर्ण,
			पूर्ण,
		पूर्ण;
		u32 rqtn = priv->indir_rqt.rqtn;

		mlx5e_redirect_rqt(priv, rqtn, MLX5E_INसूची_RQT_SIZE, rrp);
	पूर्ण

	अगर (refresh_tirs)
		mlx5e_modअगरy_tirs_hash(priv, in);

	mutex_unlock(&priv->state_lock);

	kvमुक्त(in);

	वापस 0;
पूर्ण

#घोषणा MLX5E_PFC_PREVEN_AUTO_TOUT_MSEC		100
#घोषणा MLX5E_PFC_PREVEN_TOUT_MAX_MSEC		8000
#घोषणा MLX5E_PFC_PREVEN_MINOR_PRECENT		85
#घोषणा MLX5E_PFC_PREVEN_TOUT_MIN_MSEC		80
#घोषणा MLX5E_DEVICE_STALL_MINOR_WATERMARK(critical_tout) \
	max_t(u16, MLX5E_PFC_PREVEN_TOUT_MIN_MSEC, \
	      (critical_tout * MLX5E_PFC_PREVEN_MINOR_PRECENT) / 100)

अटल पूर्णांक mlx5e_get_pfc_prevention_tout(काष्ठा net_device *netdev,
					 u16 *pfc_prevention_tout)
अणु
	काष्ठा mlx5e_priv *priv    = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (!MLX5_CAP_PCAM_FEATURE((priv)->mdev, pfcc_mask) ||
	    !MLX5_CAP_DEBUG((priv)->mdev, stall_detect))
		वापस -EOPNOTSUPP;

	वापस mlx5_query_port_stall_watermark(mdev, pfc_prevention_tout, शून्य);
पूर्ण

अटल पूर्णांक mlx5e_set_pfc_prevention_tout(काष्ठा net_device *netdev,
					 u16 pfc_preven)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 critical_tout;
	u16 minor;

	अगर (!MLX5_CAP_PCAM_FEATURE((priv)->mdev, pfcc_mask) ||
	    !MLX5_CAP_DEBUG((priv)->mdev, stall_detect))
		वापस -EOPNOTSUPP;

	critical_tout = (pfc_preven == PFC_STORM_PREVENTION_AUTO) ?
			MLX5E_PFC_PREVEN_AUTO_TOUT_MSEC :
			pfc_preven;

	अगर (critical_tout != PFC_STORM_PREVENTION_DISABLE &&
	    (critical_tout > MLX5E_PFC_PREVEN_TOUT_MAX_MSEC ||
	     critical_tout < MLX5E_PFC_PREVEN_TOUT_MIN_MSEC)) अणु
		netdev_info(netdev, "%s: pfc prevention tout not in range (%d-%d)\n",
			    __func__, MLX5E_PFC_PREVEN_TOUT_MIN_MSEC,
			    MLX5E_PFC_PREVEN_TOUT_MAX_MSEC);
		वापस -EINVAL;
	पूर्ण

	minor = MLX5E_DEVICE_STALL_MINOR_WATERMARK(critical_tout);
	वापस mlx5_set_port_stall_watermark(mdev, critical_tout,
					     minor);
पूर्ण

अटल पूर्णांक mlx5e_get_tunable(काष्ठा net_device *dev,
			     स्थिर काष्ठा ethtool_tunable *tuna,
			     व्योम *data)
अणु
	पूर्णांक err;

	चयन (tuna->id) अणु
	हाल ETHTOOL_PFC_PREVENTION_TOUT:
		err = mlx5e_get_pfc_prevention_tout(dev, data);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_set_tunable(काष्ठा net_device *dev,
			     स्थिर काष्ठा ethtool_tunable *tuna,
			     स्थिर व्योम *data)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	mutex_lock(&priv->state_lock);

	चयन (tuna->id) अणु
	हाल ETHTOOL_PFC_PREVENTION_TOUT:
		err = mlx5e_set_pfc_prevention_tout(dev, *(u16 *)data);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल व्योम mlx5e_get_छोड़ो_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_छोड़ो_stats *छोड़ो_stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_stats_छोड़ो_get(priv, छोड़ो_stats);
पूर्ण

व्योम mlx5e_ethtool_get_छोड़ोparam(काष्ठा mlx5e_priv *priv,
				  काष्ठा ethtool_छोड़ोparam *छोड़ोparam)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक err;

	err = mlx5_query_port_छोड़ो(mdev, &छोड़ोparam->rx_छोड़ो,
				    &छोड़ोparam->tx_छोड़ो);
	अगर (err) अणु
		netdev_err(priv->netdev, "%s: mlx5_query_port_pause failed:0x%x\n",
			   __func__, err);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_get_छोड़ोparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ोparam)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_ethtool_get_छोड़ोparam(priv, छोड़ोparam);
पूर्ण

पूर्णांक mlx5e_ethtool_set_छोड़ोparam(काष्ठा mlx5e_priv *priv,
				 काष्ठा ethtool_छोड़ोparam *छोड़ोparam)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(mdev, vport_group_manager))
		वापस -EOPNOTSUPP;

	अगर (छोड़ोparam->स्वतःneg)
		वापस -EINVAL;

	err = mlx5_set_port_छोड़ो(mdev,
				  छोड़ोparam->rx_छोड़ो ? 1 : 0,
				  छोड़ोparam->tx_छोड़ो ? 1 : 0);
	अगर (err) अणु
		netdev_err(priv->netdev, "%s: mlx5_set_port_pause failed:0x%x\n",
			   __func__, err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_set_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ोparam)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_set_छोड़ोparam(priv, छोड़ोparam);
पूर्ण

पूर्णांक mlx5e_ethtool_get_ts_info(काष्ठा mlx5e_priv *priv,
			      काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	info->phc_index = mlx5_घड़ी_get_ptp_index(mdev);

	अगर (!MLX5_CAP_GEN(priv->mdev, device_frequency_khz) ||
	    info->phc_index == -1)
		वापस 0;

	info->so_बारtamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) |
			   BIT(HWTSTAMP_FILTER_ALL);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_get_ts_info(काष्ठा net_device *dev,
			     काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	वापस mlx5e_ethtool_get_ts_info(priv, info);
पूर्ण

अटल __u32 mlx5e_get_wol_supported(काष्ठा mlx5_core_dev *mdev)
अणु
	__u32 ret = 0;

	अगर (MLX5_CAP_GEN(mdev, wol_g))
		ret |= WAKE_MAGIC;

	अगर (MLX5_CAP_GEN(mdev, wol_s))
		ret |= WAKE_MAGICSECURE;

	अगर (MLX5_CAP_GEN(mdev, wol_a))
		ret |= WAKE_ARP;

	अगर (MLX5_CAP_GEN(mdev, wol_b))
		ret |= WAKE_BCAST;

	अगर (MLX5_CAP_GEN(mdev, wol_m))
		ret |= WAKE_MCAST;

	अगर (MLX5_CAP_GEN(mdev, wol_u))
		ret |= WAKE_UCAST;

	अगर (MLX5_CAP_GEN(mdev, wol_p))
		ret |= WAKE_PHY;

	वापस ret;
पूर्ण

अटल __u32 mlx5e_reक्रमmat_wol_mode_mlx5_to_linux(u8 mode)
अणु
	__u32 ret = 0;

	अगर (mode & MLX5_WOL_MAGIC)
		ret |= WAKE_MAGIC;

	अगर (mode & MLX5_WOL_SECURED_MAGIC)
		ret |= WAKE_MAGICSECURE;

	अगर (mode & MLX5_WOL_ARP)
		ret |= WAKE_ARP;

	अगर (mode & MLX5_WOL_BROADCAST)
		ret |= WAKE_BCAST;

	अगर (mode & MLX5_WOL_MULTICAST)
		ret |= WAKE_MCAST;

	अगर (mode & MLX5_WOL_UNICAST)
		ret |= WAKE_UCAST;

	अगर (mode & MLX5_WOL_PHY_ACTIVITY)
		ret |= WAKE_PHY;

	वापस ret;
पूर्ण

अटल u8 mlx5e_reक्रमmat_wol_mode_linux_to_mlx5(__u32 mode)
अणु
	u8 ret = 0;

	अगर (mode & WAKE_MAGIC)
		ret |= MLX5_WOL_MAGIC;

	अगर (mode & WAKE_MAGICSECURE)
		ret |= MLX5_WOL_SECURED_MAGIC;

	अगर (mode & WAKE_ARP)
		ret |= MLX5_WOL_ARP;

	अगर (mode & WAKE_BCAST)
		ret |= MLX5_WOL_BROADCAST;

	अगर (mode & WAKE_MCAST)
		ret |= MLX5_WOL_MULTICAST;

	अगर (mode & WAKE_UCAST)
		ret |= MLX5_WOL_UNICAST;

	अगर (mode & WAKE_PHY)
		ret |= MLX5_WOL_PHY_ACTIVITY;

	वापस ret;
पूर्ण

अटल व्योम mlx5e_get_wol(काष्ठा net_device *netdev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 mlx5_wol_mode;
	पूर्णांक err;

	स_रखो(wol, 0, माप(*wol));

	wol->supported = mlx5e_get_wol_supported(mdev);
	अगर (!wol->supported)
		वापस;

	err = mlx5_query_port_wol(mdev, &mlx5_wol_mode);
	अगर (err)
		वापस;

	wol->wolopts = mlx5e_reक्रमmat_wol_mode_mlx5_to_linux(mlx5_wol_mode);
पूर्ण

अटल पूर्णांक mlx5e_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	__u32 wol_supported = mlx5e_get_wol_supported(mdev);
	u32 mlx5_wol_mode;

	अगर (!wol_supported)
		वापस -EOPNOTSUPP;

	अगर (wol->wolopts & ~wol_supported)
		वापस -EINVAL;

	mlx5_wol_mode = mlx5e_reक्रमmat_wol_mode_linux_to_mlx5(wol->wolopts);

	वापस mlx5_set_port_wol(mdev, mlx5_wol_mode);
पूर्ण

अटल व्योम mlx5e_get_fec_stats(काष्ठा net_device *netdev,
				काष्ठा ethtool_fec_stats *fec_stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_stats_fec_get(priv, fec_stats);
पूर्ण

अटल पूर्णांक mlx5e_get_fecparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 fec_configured;
	u32 fec_active;
	पूर्णांक err;

	err = mlx5e_get_fec_mode(mdev, &fec_active, &fec_configured);

	अगर (err)
		वापस err;

	fecparam->active_fec = pplm2ethtool_fec((अचिन्हित दीर्घ)fec_active,
						माप(अचिन्हित दीर्घ) * BITS_PER_BYTE);

	अगर (!fecparam->active_fec)
		वापस -EOPNOTSUPP;

	fecparam->fec = pplm2ethtool_fec((अचिन्हित दीर्घ)fec_configured,
					 माप(अचिन्हित दीर्घ) * BITS_PER_BYTE);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_set_fecparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	अचिन्हित दीर्घ fec_biपंचांगap;
	u16 fec_policy = 0;
	पूर्णांक mode;
	पूर्णांक err;

	biपंचांगap_from_arr32(&fec_biपंचांगap, &fecparam->fec, माप(fecparam->fec) * BITS_PER_BYTE);
	अगर (biपंचांगap_weight(&fec_biपंचांगap, ETHTOOL_FEC_LLRS_BIT + 1) > 1)
		वापस -EOPNOTSUPP;

	क्रम (mode = 0; mode < ARRAY_SIZE(pplm_fec_2_ethtool); mode++) अणु
		अगर (!(pplm_fec_2_ethtool[mode] & fecparam->fec))
			जारी;
		fec_policy |= (1 << mode);
		अवरोध;
	पूर्ण

	err = mlx5e_set_fec_mode(mdev, fec_policy);

	अगर (err)
		वापस err;

	mlx5_toggle_port_link(mdev);

	वापस 0;
पूर्ण

अटल u32 mlx5e_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस ((काष्ठा mlx5e_priv *)netdev_priv(dev))->msglevel;
पूर्ण

अटल व्योम mlx5e_set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	((काष्ठा mlx5e_priv *)netdev_priv(dev))->msglevel = val;
पूर्ण

अटल पूर्णांक mlx5e_set_phys_id(काष्ठा net_device *dev,
			     क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 beacon_duration;

	अगर (!MLX5_CAP_GEN(mdev, beacon_led))
		वापस -EOPNOTSUPP;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		beacon_duration = MLX5_BEACON_DURATION_INF;
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		beacon_duration = MLX5_BEACON_DURATION_OFF;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस mlx5_set_port_beacon(mdev, beacon_duration);
पूर्ण

अटल पूर्णांक mlx5e_get_module_info(काष्ठा net_device *netdev,
				 काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *dev = priv->mdev;
	पूर्णांक size_पढ़ो = 0;
	u8 data[4] = अणु0पूर्ण;

	size_पढ़ो = mlx5_query_module_eeprom(dev, 0, 2, data);
	अगर (size_पढ़ो < 2)
		वापस -EIO;

	/* data[0] = identअगरier byte */
	चयन (data[0]) अणु
	हाल MLX5_MODULE_ID_QSFP:
		modinfo->type       = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_MAX_LEN;
		अवरोध;
	हाल MLX5_MODULE_ID_QSFP_PLUS:
	हाल MLX5_MODULE_ID_QSFP28:
		/* data[1] = revision id */
		अगर (data[0] == MLX5_MODULE_ID_QSFP28 || data[1] >= 0x3) अणु
			modinfo->type       = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_MAX_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type       = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_MAX_LEN;
		पूर्ण
		अवरोध;
	हाल MLX5_MODULE_ID_SFP:
		modinfo->type       = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		अवरोध;
	शेष:
		netdev_err(priv->netdev, "%s: cable type not recognized:0x%x\n",
			   __func__, data[0]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_get_module_eeprom(काष्ठा net_device *netdev,
				   काष्ठा ethtool_eeprom *ee,
				   u8 *data)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक offset = ee->offset;
	पूर्णांक size_पढ़ो;
	पूर्णांक i = 0;

	अगर (!ee->len)
		वापस -EINVAL;

	स_रखो(data, 0, ee->len);

	जबतक (i < ee->len) अणु
		size_पढ़ो = mlx5_query_module_eeprom(mdev, offset, ee->len - i,
						     data + i);

		अगर (!size_पढ़ो)
			/* Done पढ़ोing */
			वापस 0;

		अगर (size_पढ़ो < 0) अणु
			netdev_err(priv->netdev, "%s: mlx5_query_eeprom failed:0x%x\n",
				   __func__, size_पढ़ो);
			वापस 0;
		पूर्ण

		i += size_पढ़ो;
		offset += size_पढ़ो;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_get_module_eeprom_by_page(काष्ठा net_device *netdev,
					   स्थिर काष्ठा ethtool_module_eeprom *page_data,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_module_eeprom_query_params query;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 *data = page_data->data;
	पूर्णांक size_पढ़ो;
	पूर्णांक i = 0;

	अगर (!page_data->length)
		वापस -EINVAL;

	स_रखो(data, 0, page_data->length);

	query.offset = page_data->offset;
	query.i2c_address = page_data->i2c_address;
	query.bank = page_data->bank;
	query.page = page_data->page;
	जबतक (i < page_data->length) अणु
		query.size = page_data->length - i;
		size_पढ़ो = mlx5_query_module_eeprom_by_page(mdev, &query, data + i);

		/* Done पढ़ोing, वापस how many bytes was पढ़ो */
		अगर (!size_पढ़ो)
			वापस i;

		अगर (size_पढ़ो == -EINVAL)
			वापस -EINVAL;
		अगर (size_पढ़ो < 0) अणु
			netdev_err(priv->netdev, "%s: mlx5_query_module_eeprom_by_page failed:0x%x\n",
				   __func__, size_पढ़ो);
			वापस i;
		पूर्ण

		i += size_पढ़ो;
		query.offset += size_पढ़ो;
	पूर्ण

	वापस i;
पूर्ण

पूर्णांक mlx5e_ethtool_flash_device(काष्ठा mlx5e_priv *priv,
			       काष्ठा ethtool_flash *flash)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा net_device *dev = priv->netdev;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;

	अगर (flash->region != ETHTOOL_FLASH_ALL_REGIONS)
		वापस -EOPNOTSUPP;

	err = request_firmware_direct(&fw, flash->data, &dev->dev);
	अगर (err)
		वापस err;

	dev_hold(dev);
	rtnl_unlock();

	err = mlx5_firmware_flash(mdev, fw, शून्य);
	release_firmware(fw);

	rtnl_lock();
	dev_put(dev);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_flash_device(काष्ठा net_device *dev,
			      काष्ठा ethtool_flash *flash)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	वापस mlx5e_ethtool_flash_device(priv, flash);
पूर्ण

अटल पूर्णांक set_pflag_cqe_based_moder(काष्ठा net_device *netdev, bool enable,
				     bool is_rx_cq)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_params new_params;
	bool mode_changed;
	u8 cq_period_mode, current_cq_period_mode;

	cq_period_mode = enable ?
		MLX5_CQ_PERIOD_MODE_START_FROM_CQE :
		MLX5_CQ_PERIOD_MODE_START_FROM_EQE;
	current_cq_period_mode = is_rx_cq ?
		priv->channels.params.rx_cq_moderation.cq_period_mode :
		priv->channels.params.tx_cq_moderation.cq_period_mode;
	mode_changed = cq_period_mode != current_cq_period_mode;

	अगर (cq_period_mode == MLX5_CQ_PERIOD_MODE_START_FROM_CQE &&
	    !MLX5_CAP_GEN(mdev, cq_period_start_from_cqe))
		वापस -EOPNOTSUPP;

	अगर (!mode_changed)
		वापस 0;

	new_params = priv->channels.params;
	अगर (is_rx_cq)
		mlx5e_set_rx_cq_mode_params(&new_params, cq_period_mode);
	अन्यथा
		mlx5e_set_tx_cq_mode_params(&new_params, cq_period_mode);

	वापस mlx5e_safe_चयन_params(priv, &new_params, शून्य, शून्य, true);
पूर्ण

अटल पूर्णांक set_pflag_tx_cqe_based_moder(काष्ठा net_device *netdev, bool enable)
अणु
	वापस set_pflag_cqe_based_moder(netdev, enable, false);
पूर्ण

अटल पूर्णांक set_pflag_rx_cqe_based_moder(काष्ठा net_device *netdev, bool enable)
अणु
	वापस set_pflag_cqe_based_moder(netdev, enable, true);
पूर्ण

पूर्णांक mlx5e_modअगरy_rx_cqe_compression_locked(काष्ठा mlx5e_priv *priv, bool new_val)
अणु
	bool curr_val = MLX5E_GET_PFLAG(&priv->channels.params, MLX5E_PFLAG_RX_CQE_COMPRESS);
	काष्ठा mlx5e_params new_params;
	पूर्णांक err = 0;

	अगर (!MLX5_CAP_GEN(priv->mdev, cqe_compression))
		वापस new_val ? -EOPNOTSUPP : 0;

	अगर (curr_val == new_val)
		वापस 0;

	अगर (new_val && !priv->profile->rx_ptp_support &&
	    priv->tstamp.rx_filter != HWTSTAMP_FILTER_NONE) अणु
		netdev_err(priv->netdev,
			   "Profile doesn't support enabling of CQE compression while hardware time-stamping is enabled.\n");
		वापस -EINVAL;
	पूर्ण

	new_params = priv->channels.params;
	MLX5E_SET_PFLAG(&new_params, MLX5E_PFLAG_RX_CQE_COMPRESS, new_val);
	अगर (priv->tstamp.rx_filter != HWTSTAMP_FILTER_NONE)
		new_params.ptp_rx = new_val;

	अगर (new_params.ptp_rx == priv->channels.params.ptp_rx)
		err = mlx5e_safe_चयन_params(priv, &new_params, शून्य, शून्य, true);
	अन्यथा
		err = mlx5e_safe_चयन_params(priv, &new_params, mlx5e_ptp_rx_manage_fs_ctx,
					       &new_params.ptp_rx, true);
	अगर (err)
		वापस err;

	mlx5e_dbg(DRV, priv, "MLX5E: RxCqeCmprss was turned %s\n",
		  MLX5E_GET_PFLAG(&priv->channels.params,
				  MLX5E_PFLAG_RX_CQE_COMPRESS) ? "ON" : "OFF");

	वापस 0;
पूर्ण

अटल पूर्णांक set_pflag_rx_cqe_compress(काष्ठा net_device *netdev,
				     bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(mdev, cqe_compression))
		वापस -EOPNOTSUPP;

	err = mlx5e_modअगरy_rx_cqe_compression_locked(priv, enable);
	अगर (err)
		वापस err;

	priv->channels.params.rx_cqe_compress_def = enable;

	वापस 0;
पूर्ण

अटल पूर्णांक set_pflag_rx_striding_rq(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_params new_params;

	अगर (enable) अणु
		अगर (!mlx5e_check_fragmented_striding_rq_cap(mdev))
			वापस -EOPNOTSUPP;
		अगर (!mlx5e_striding_rq_possible(mdev, &priv->channels.params))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (priv->channels.params.lro_en) अणु
		netdev_warn(netdev, "Can't set legacy RQ with LRO, disable LRO first\n");
		वापस -EINVAL;
	पूर्ण

	new_params = priv->channels.params;

	MLX5E_SET_PFLAG(&new_params, MLX5E_PFLAG_RX_STRIDING_RQ, enable);
	mlx5e_set_rq_type(mdev, &new_params);

	वापस mlx5e_safe_चयन_params(priv, &new_params, शून्य, शून्य, true);
पूर्ण

अटल पूर्णांक set_pflag_rx_no_csum_complete(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_channels *channels = &priv->channels;
	काष्ठा mlx5e_channel *c;
	पूर्णांक i;

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state) ||
	    priv->channels.params.xdp_prog)
		वापस 0;

	क्रम (i = 0; i < channels->num; i++) अणु
		c = channels->c[i];
		अगर (enable)
			__set_bit(MLX5E_RQ_STATE_NO_CSUM_COMPLETE, &c->rq.state);
		अन्यथा
			__clear_bit(MLX5E_RQ_STATE_NO_CSUM_COMPLETE, &c->rq.state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_pflag_tx_mpwqe_common(काष्ठा net_device *netdev, u32 flag, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_params new_params;

	अगर (enable && !MLX5_CAP_ETH(mdev, enhanced_multi_pkt_send_wqe))
		वापस -EOPNOTSUPP;

	new_params = priv->channels.params;

	MLX5E_SET_PFLAG(&new_params, flag, enable);

	वापस mlx5e_safe_चयन_params(priv, &new_params, शून्य, शून्य, true);
पूर्ण

अटल पूर्णांक set_pflag_xdp_tx_mpwqe(काष्ठा net_device *netdev, bool enable)
अणु
	वापस set_pflag_tx_mpwqe_common(netdev, MLX5E_PFLAG_XDP_TX_MPWQE, enable);
पूर्ण

अटल पूर्णांक set_pflag_skb_tx_mpwqe(काष्ठा net_device *netdev, bool enable)
अणु
	वापस set_pflag_tx_mpwqe_common(netdev, MLX5E_PFLAG_SKB_TX_MPWQE, enable);
पूर्ण

अटल पूर्णांक set_pflag_tx_port_ts(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_params new_params;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(mdev, ts_cqe_to_dest_cqn))
		वापस -EOPNOTSUPP;

	/* Don't allow changing the PTP state अगर HTB offload is active, because
	 * the numeration of the QoS SQs will change, जबतक per-queue qdiscs are
	 * attached.
	 */
	अगर (priv->htb.maj_id) अणु
		netdev_err(priv->netdev, "%s: HTB offload is active, cannot change the PTP state\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	new_params = priv->channels.params;
	MLX5E_SET_PFLAG(&new_params, MLX5E_PFLAG_TX_PORT_TS, enable);
	/* No need to verअगरy SQ stop room as
	 * ptpsq.txqsq.stop_room <= generic_sq->stop_room, and both
	 * has the same log_sq_size.
	 */

	err = mlx5e_safe_चयन_params(priv, &new_params,
				       mlx5e_num_channels_changed_ctx, शून्य, true);
	अगर (!err)
		priv->tx_ptp_खोलोed = true;

	वापस err;
पूर्ण

अटल स्थिर काष्ठा pflag_desc mlx5e_priv_flags[MLX5E_NUM_PFLAGS] = अणु
	अणु "rx_cqe_moder",        set_pflag_rx_cqe_based_moder पूर्ण,
	अणु "tx_cqe_moder",        set_pflag_tx_cqe_based_moder पूर्ण,
	अणु "rx_cqe_compress",     set_pflag_rx_cqe_compress पूर्ण,
	अणु "rx_striding_rq",      set_pflag_rx_striding_rq पूर्ण,
	अणु "rx_no_csum_complete", set_pflag_rx_no_csum_complete पूर्ण,
	अणु "xdp_tx_mpwqe",        set_pflag_xdp_tx_mpwqe पूर्ण,
	अणु "skb_tx_mpwqe",        set_pflag_skb_tx_mpwqe पूर्ण,
	अणु "tx_port_ts",          set_pflag_tx_port_ts पूर्ण,
पूर्ण;

अटल पूर्णांक mlx5e_handle_pflag(काष्ठा net_device *netdev,
			      u32 wanted_flags,
			      क्रमागत mlx5e_priv_flag flag)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	bool enable = !!(wanted_flags & BIT(flag));
	u32 changes = wanted_flags ^ priv->channels.params.pflags;
	पूर्णांक err;

	अगर (!(changes & BIT(flag)))
		वापस 0;

	err = mlx5e_priv_flags[flag].handler(netdev, enable);
	अगर (err) अणु
		netdev_err(netdev, "%s private flag '%s' failed err %d\n",
			   enable ? "Enable" : "Disable", mlx5e_priv_flags[flag].name, err);
		वापस err;
	पूर्ण

	MLX5E_SET_PFLAG(&priv->channels.params, flag, enable);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_set_priv_flags(काष्ठा net_device *netdev, u32 pflags)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	क्रमागत mlx5e_priv_flag pflag;
	पूर्णांक err;

	mutex_lock(&priv->state_lock);

	क्रम (pflag = 0; pflag < MLX5E_NUM_PFLAGS; pflag++) अणु
		err = mlx5e_handle_pflag(netdev, pflags, pflag);
		अगर (err)
			अवरोध;
	पूर्ण

	mutex_unlock(&priv->state_lock);

	/* Need to fix some features.. */
	netdev_update_features(netdev);

	वापस err;
पूर्ण

अटल u32 mlx5e_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस priv->channels.params.pflags;
पूर्ण

पूर्णांक mlx5e_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info,
		    u32 *rule_locs)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	/* ETHTOOL_GRXRINGS is needed by ethtool -x which is not part
	 * of rxnfc. We keep this logic out of mlx5e_ethtool_get_rxnfc,
	 * to aव्योम अवरोधing "ethtool -x" when mlx5e_ethtool_get_rxnfc
	 * is compiled out via CONFIG_MLX5_EN_RXNFC=n.
	 */
	अगर (info->cmd == ETHTOOL_GRXRINGS) अणु
		info->data = priv->channels.params.num_channels;
		वापस 0;
	पूर्ण

	वापस mlx5e_ethtool_get_rxnfc(dev, info, rule_locs);
पूर्ण

पूर्णांक mlx5e_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	वापस mlx5e_ethtool_set_rxnfc(dev, cmd);
पूर्ण

अटल पूर्णांक query_port_status_opcode(काष्ठा mlx5_core_dev *mdev, u32 *status_opcode)
अणु
	काष्ठा mlx5_अगरc_pddr_troubleshooting_page_bits *pddr_troubleshooting_page;
	u32 in[MLX5_ST_SZ_DW(pddr_reg)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(pddr_reg)];
	पूर्णांक err;

	MLX5_SET(pddr_reg, in, local_port, 1);
	MLX5_SET(pddr_reg, in, page_select,
		 MLX5_PDDR_REG_PAGE_SELECT_TROUBLESHOOTING_INFO_PAGE);

	pddr_troubleshooting_page = MLX5_ADDR_OF(pddr_reg, in, page_data);
	MLX5_SET(pddr_troubleshooting_page, pddr_troubleshooting_page,
		 group_opcode, MLX5_PDDR_REG_TRBLSH_GROUP_OPCODE_MONITOR);
	err = mlx5_core_access_reg(mdev, in, माप(in), out,
				   माप(out), MLX5_REG_PDDR, 0, 0);
	अगर (err)
		वापस err;

	pddr_troubleshooting_page = MLX5_ADDR_OF(pddr_reg, out, page_data);
	*status_opcode = MLX5_GET(pddr_troubleshooting_page, pddr_troubleshooting_page,
				  status_opcode);
	वापस 0;
पूर्ण

काष्ठा mlx5e_ethtool_link_ext_state_opcode_mapping अणु
	u32 status_opcode;
	क्रमागत ethtool_link_ext_state link_ext_state;
	u8 link_ext_substate;
पूर्ण;

अटल स्थिर काष्ठा mlx5e_ethtool_link_ext_state_opcode_mapping
mlx5e_link_ext_state_opcode_map[] = अणु
	/* States relating to the स्वतःnegotiation or issues therein */
	अणु2, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTEDपूर्ण,
	अणु3, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_ACK_NOT_RECEIVEDपूर्ण,
	अणु4, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAILEDपूर्ण,
	अणु36, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTED_FORCE_MODEपूर्ण,
	अणु38, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DURING_OVERRIDEपूर्ण,
	अणु39, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_HCDपूर्ण,

	/* Failure during link training */
	अणु5, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
		ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_FRAME_LOCK_NOT_ACQUIREDपूर्ण,
	अणु6, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
		ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_LINK_INHIBIT_TIMEOUTपूर्ण,
	अणु7, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
		ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_LINK_PARTNER_DID_NOT_SET_RECEIVER_READYपूर्ण,
	अणु8, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE, 0पूर्ण,
	अणु14, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
		ETHTOOL_LINK_EXT_SUBSTATE_LT_REMOTE_FAULTपूर्ण,

	/* Logical mismatch in physical coding sublayer or क्रमward error correction sublayer */
	अणु9, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_BLOCK_LOCKपूर्ण,
	अणु10, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_AM_LOCKपूर्ण,
	अणु11, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_GET_ALIGN_STATUSपूर्ण,
	अणु12, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_FC_FEC_IS_NOT_LOCKEDपूर्ण,
	अणु13, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_RS_FEC_IS_NOT_LOCKEDपूर्ण,

	/* Signal पूर्णांकegrity issues */
	अणु15, ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY, 0पूर्ण,
	अणु17, ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY,
		ETHTOOL_LINK_EXT_SUBSTATE_BSI_LARGE_NUMBER_OF_PHYSICAL_ERRORSपूर्ण,
	अणु42, ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY,
		ETHTOOL_LINK_EXT_SUBSTATE_BSI_UNSUPPORTED_RATEपूर्ण,

	/* No cable connected */
	अणु1024, ETHTOOL_LINK_EXT_STATE_NO_CABLE, 0पूर्ण,

	/* Failure is related to cable, e.g., unsupported cable */
	अणु16, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु20, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु29, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु1025, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु1029, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु1031, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE, 0पूर्ण,

	/* Failure is related to EEPROM, e.g., failure during पढ़ोing or parsing the data */
	अणु1027, ETHTOOL_LINK_EXT_STATE_EEPROM_ISSUE, 0पूर्ण,

	/* Failure during calibration algorithm */
	अणु23, ETHTOOL_LINK_EXT_STATE_CALIBRATION_FAILURE, 0पूर्ण,

	/* The hardware is not able to provide the घातer required from cable or module */
	अणु1032, ETHTOOL_LINK_EXT_STATE_POWER_BUDGET_EXCEEDED, 0पूर्ण,

	/* The module is overheated */
	अणु1030, ETHTOOL_LINK_EXT_STATE_OVERHEAT, 0पूर्ण,
पूर्ण;

अटल व्योम
mlx5e_set_link_ext_state(काष्ठा mlx5e_ethtool_link_ext_state_opcode_mapping
			 link_ext_state_mapping,
			 काष्ठा ethtool_link_ext_state_info *link_ext_state_info)
अणु
	चयन (link_ext_state_mapping.link_ext_state) अणु
	हाल ETHTOOL_LINK_EXT_STATE_AUTONEG:
		link_ext_state_info->स्वतःneg =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	हाल ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE:
		link_ext_state_info->link_training =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	हाल ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH:
		link_ext_state_info->link_logical_mismatch =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	हाल ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY:
		link_ext_state_info->bad_संकेत_पूर्णांकegrity =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	हाल ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE:
		link_ext_state_info->cable_issue =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	link_ext_state_info->link_ext_state = link_ext_state_mapping.link_ext_state;
पूर्ण

अटल पूर्णांक
mlx5e_get_link_ext_state(काष्ठा net_device *dev,
			 काष्ठा ethtool_link_ext_state_info *link_ext_state_info)
अणु
	काष्ठा mlx5e_ethtool_link_ext_state_opcode_mapping link_ext_state_mapping;
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	u32 status_opcode = 0;
	पूर्णांक i;

	/* Exit without data अगर the पूर्णांकerface state is OK, since no extended data is
	 * available in such हाल
	 */
	अगर (netअगर_carrier_ok(dev))
		वापस -ENODATA;

	अगर (query_port_status_opcode(priv->mdev, &status_opcode) ||
	    !status_opcode)
		वापस -ENODATA;

	क्रम (i = 0; i < ARRAY_SIZE(mlx5e_link_ext_state_opcode_map); i++) अणु
		link_ext_state_mapping = mlx5e_link_ext_state_opcode_map[i];
		अगर (link_ext_state_mapping.status_opcode == status_opcode) अणु
			mlx5e_set_link_ext_state(link_ext_state_mapping,
						 link_ext_state_info);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODATA;
पूर्ण

अटल व्योम mlx5e_get_eth_phy_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_eth_phy_stats *phy_stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_stats_eth_phy_get(priv, phy_stats);
पूर्ण

अटल व्योम mlx5e_get_eth_mac_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_eth_mac_stats *mac_stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_stats_eth_mac_get(priv, mac_stats);
पूर्ण

अटल व्योम mlx5e_get_eth_ctrl_stats(काष्ठा net_device *netdev,
				     काष्ठा ethtool_eth_ctrl_stats *ctrl_stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_stats_eth_ctrl_get(priv, ctrl_stats);
पूर्ण

अटल व्योम mlx5e_get_rmon_stats(काष्ठा net_device *netdev,
				 काष्ठा ethtool_rmon_stats *rmon_stats,
				 स्थिर काष्ठा ethtool_rmon_hist_range **ranges)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_stats_rmon_get(priv, rmon_stats, ranges);
पूर्ण

स्थिर काष्ठा ethtool_ops mlx5e_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE,
	.get_drvinfo       = mlx5e_get_drvinfo,
	.get_link          = ethtool_op_get_link,
	.get_link_ext_state  = mlx5e_get_link_ext_state,
	.get_strings       = mlx5e_get_strings,
	.get_sset_count    = mlx5e_get_sset_count,
	.get_ethtool_stats = mlx5e_get_ethtool_stats,
	.get_ringparam     = mlx5e_get_ringparam,
	.set_ringparam     = mlx5e_set_ringparam,
	.get_channels      = mlx5e_get_channels,
	.set_channels      = mlx5e_set_channels,
	.get_coalesce      = mlx5e_get_coalesce,
	.set_coalesce      = mlx5e_set_coalesce,
	.get_link_ksettings  = mlx5e_get_link_ksettings,
	.set_link_ksettings  = mlx5e_set_link_ksettings,
	.get_rxfh_key_size   = mlx5e_get_rxfh_key_size,
	.get_rxfh_indir_size = mlx5e_get_rxfh_indir_size,
	.get_rxfh          = mlx5e_get_rxfh,
	.set_rxfh          = mlx5e_set_rxfh,
	.get_rxnfc         = mlx5e_get_rxnfc,
	.set_rxnfc         = mlx5e_set_rxnfc,
	.get_tunable       = mlx5e_get_tunable,
	.set_tunable       = mlx5e_set_tunable,
	.get_छोड़ो_stats   = mlx5e_get_छोड़ो_stats,
	.get_छोड़ोparam    = mlx5e_get_छोड़ोparam,
	.set_छोड़ोparam    = mlx5e_set_छोड़ोparam,
	.get_ts_info       = mlx5e_get_ts_info,
	.set_phys_id       = mlx5e_set_phys_id,
	.get_wol	   = mlx5e_get_wol,
	.set_wol	   = mlx5e_set_wol,
	.get_module_info   = mlx5e_get_module_info,
	.get_module_eeprom = mlx5e_get_module_eeprom,
	.get_module_eeprom_by_page = mlx5e_get_module_eeprom_by_page,
	.flash_device      = mlx5e_flash_device,
	.get_priv_flags    = mlx5e_get_priv_flags,
	.set_priv_flags    = mlx5e_set_priv_flags,
	.self_test         = mlx5e_self_test,
	.get_msglevel      = mlx5e_get_msglevel,
	.set_msglevel      = mlx5e_set_msglevel,
	.get_fec_stats     = mlx5e_get_fec_stats,
	.get_fecparam      = mlx5e_get_fecparam,
	.set_fecparam      = mlx5e_set_fecparam,
	.get_eth_phy_stats = mlx5e_get_eth_phy_stats,
	.get_eth_mac_stats = mlx5e_get_eth_mac_stats,
	.get_eth_ctrl_stats = mlx5e_get_eth_ctrl_stats,
	.get_rmon_stats    = mlx5e_get_rmon_stats,
पूर्ण;
