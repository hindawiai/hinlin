<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
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
#समावेश "ipoib.h"

अटल व्योम mlx5i_get_drvinfo(काष्ठा net_device *dev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);

	mlx5e_ethtool_get_drvinfo(priv, drvinfo);
	strlcpy(drvinfo->driver, KBUILD_MODNAME "[ib_ipoib]",
		माप(drvinfo->driver));
पूर्ण

अटल व्योम mlx5i_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	काष्ठा mlx5e_priv *priv  = mlx5i_epriv(dev);

	mlx5e_ethtool_get_strings(priv, stringset, data);
पूर्ण

अटल पूर्णांक mlx5i_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);

	वापस mlx5e_ethtool_get_sset_count(priv, sset);
पूर्ण

अटल व्योम mlx5i_get_ethtool_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *stats,
				    u64 *data)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);

	mlx5e_ethtool_get_ethtool_stats(priv, stats, data);
पूर्ण

अटल पूर्णांक mlx5i_set_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);

	वापस mlx5e_ethtool_set_ringparam(priv, param);
पूर्ण

अटल व्योम mlx5i_get_ringparam(काष्ठा net_device *dev,
				काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);

	mlx5e_ethtool_get_ringparam(priv, param);
पूर्ण

अटल पूर्णांक mlx5i_set_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);

	वापस mlx5e_ethtool_set_channels(priv, ch);
पूर्ण

अटल व्योम mlx5i_get_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *ch)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);

	mlx5e_ethtool_get_channels(priv, ch);
पूर्ण

अटल पूर्णांक mlx5i_set_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);

	वापस mlx5e_ethtool_set_coalesce(priv, coal);
पूर्ण

अटल पूर्णांक mlx5i_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);

	वापस mlx5e_ethtool_get_coalesce(priv, coal);
पूर्ण

अटल पूर्णांक mlx5i_get_ts_info(काष्ठा net_device *netdev,
			     काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);

	वापस mlx5e_ethtool_get_ts_info(priv, info);
पूर्ण

अटल पूर्णांक mlx5i_flash_device(काष्ठा net_device *netdev,
			      काष्ठा ethtool_flash *flash)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);

	वापस mlx5e_ethtool_flash_device(priv, flash);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_ptys_width_क्रमागत_to_पूर्णांक(क्रमागत mlx5_ptys_width width)
अणु
	चयन (width) अणु
	हाल MLX5_PTYS_WIDTH_1X:  वापस  1;
	हाल MLX5_PTYS_WIDTH_2X:  वापस  2;
	हाल MLX5_PTYS_WIDTH_4X:  वापस  4;
	हाल MLX5_PTYS_WIDTH_8X:  वापस  8;
	हाल MLX5_PTYS_WIDTH_12X: वापस 12;
	शेष:		  वापस -1;
	पूर्ण
पूर्ण

क्रमागत mlx5_ptys_rate अणु
	MLX5_PTYS_RATE_SDR	= 1 << 0,
	MLX5_PTYS_RATE_DDR	= 1 << 1,
	MLX5_PTYS_RATE_QDR	= 1 << 2,
	MLX5_PTYS_RATE_FDR10	= 1 << 3,
	MLX5_PTYS_RATE_FDR	= 1 << 4,
	MLX5_PTYS_RATE_EDR	= 1 << 5,
	MLX5_PTYS_RATE_HDR	= 1 << 6,
पूर्ण;

अटल अंतरभूत पूर्णांक mlx5_ptys_rate_क्रमागत_to_पूर्णांक(क्रमागत mlx5_ptys_rate rate)
अणु
	चयन (rate) अणु
	हाल MLX5_PTYS_RATE_SDR:   वापस 2500;
	हाल MLX5_PTYS_RATE_DDR:   वापस 5000;
	हाल MLX5_PTYS_RATE_QDR:
	हाल MLX5_PTYS_RATE_FDR10: वापस 10000;
	हाल MLX5_PTYS_RATE_FDR:   वापस 14000;
	हाल MLX5_PTYS_RATE_EDR:   वापस 25000;
	हाल MLX5_PTYS_RATE_HDR:   वापस 50000;
	शेष:		   वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5i_get_speed_settings(u16 ib_link_width_oper, u16 ib_proto_oper)
अणु
	पूर्णांक rate, width;

	rate = mlx5_ptys_rate_क्रमागत_to_पूर्णांक(ib_proto_oper);
	अगर (rate < 0)
		वापस -EINVAL;
	width = mlx5_ptys_width_क्रमागत_to_पूर्णांक(ib_link_width_oper);
	अगर (width < 0)
		वापस -EINVAL;

	वापस rate * width;
पूर्ण

अटल पूर्णांक mlx5i_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 ib_link_width_oper;
	u16 ib_proto_oper;
	पूर्णांक speed, ret;

	ret = mlx5_query_ib_port_oper(mdev, &ib_link_width_oper, &ib_proto_oper,
				      1);
	अगर (ret)
		वापस ret;

	ethtool_link_ksettings_zero_link_mode(link_ksettings, supported);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, advertising);

	speed = mlx5i_get_speed_settings(ib_link_width_oper, ib_proto_oper);
	अगर (speed < 0)
		वापस -EINVAL;

	link_ksettings->base.duplex = DUPLEX_FULL;
	link_ksettings->base.port = PORT_OTHER;

	link_ksettings->base.स्वतःneg = AUTONEG_DISABLE;

	link_ksettings->base.speed = speed;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops mlx5i_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE,
	.get_drvinfo        = mlx5i_get_drvinfo,
	.get_strings        = mlx5i_get_strings,
	.get_sset_count     = mlx5i_get_sset_count,
	.get_ethtool_stats  = mlx5i_get_ethtool_stats,
	.get_ringparam      = mlx5i_get_ringparam,
	.set_ringparam      = mlx5i_set_ringparam,
	.flash_device       = mlx5i_flash_device,
	.get_channels       = mlx5i_get_channels,
	.set_channels       = mlx5i_set_channels,
	.get_coalesce       = mlx5i_get_coalesce,
	.set_coalesce       = mlx5i_set_coalesce,
	.get_ts_info        = mlx5i_get_ts_info,
	.get_link_ksettings = mlx5i_get_link_ksettings,
	.get_link           = ethtool_op_get_link,
पूर्ण;

स्थिर काष्ठा ethtool_ops mlx5i_pkey_ethtool_ops = अणु
	.get_drvinfo        = mlx5i_get_drvinfo,
	.get_link           = ethtool_op_get_link,
	.get_ts_info        = mlx5i_get_ts_info,
पूर्ण;
