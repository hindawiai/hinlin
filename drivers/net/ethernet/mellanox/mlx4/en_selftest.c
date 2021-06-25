<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/kernel.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/mlx4/driver.h>

#समावेश "mlx4_en.h"


अटल पूर्णांक mlx4_en_test_रेजिस्टरs(काष्ठा mlx4_en_priv *priv)
अणु
	वापस mlx4_cmd(priv->mdev->dev, 0, 0, 0, MLX4_CMD_HW_HEALTH_CHECK,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_en_test_loopback_xmit(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr *ethh;
	अचिन्हित अक्षर *packet;
	अचिन्हित पूर्णांक packet_size = MLX4_LOOPBACK_TEST_PAYLOAD;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;


	/* build the pkt beक्रमe xmit */
	skb = netdev_alloc_skb(priv->dev, MLX4_LOOPBACK_TEST_PAYLOAD + ETH_HLEN + NET_IP_ALIGN);
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, NET_IP_ALIGN);

	ethh = skb_put(skb, माप(काष्ठा ethhdr));
	packet = skb_put(skb, packet_size);
	स_नकल(ethh->h_dest, priv->dev->dev_addr, ETH_ALEN);
	eth_zero_addr(ethh->h_source);
	ethh->h_proto = htons(ETH_P_ARP);
	skb_reset_mac_header(skb);
	क्रम (i = 0; i < packet_size; ++i)	/* fill our packet */
		packet[i] = (अचिन्हित अक्षर)(i & 0xff);

	/* xmit the pkt */
	err = mlx4_en_xmit(skb, priv->dev);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_test_loopback(काष्ठा mlx4_en_priv *priv)
अणु
	u32 loopback_ok = 0;
	पूर्णांक i;

        priv->loopback_ok = 0;
	priv->validate_loopback = 1;

	mlx4_en_update_loopback_state(priv->dev, priv->dev->features);

	/* xmit */
	अगर (mlx4_en_test_loopback_xmit(priv)) अणु
		en_err(priv, "Transmitting loopback packet failed\n");
		जाओ mlx4_en_test_loopback_निकास;
	पूर्ण

	/* polling क्रम result */
	क्रम (i = 0; i < MLX4_EN_LOOPBACK_RETRIES; ++i) अणु
		msleep(MLX4_EN_LOOPBACK_TIMEOUT);
		अगर (priv->loopback_ok) अणु
			loopback_ok = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!loopback_ok)
		en_err(priv, "Loopback packet didn't arrive\n");

mlx4_en_test_loopback_निकास:

	priv->validate_loopback = 0;

	mlx4_en_update_loopback_state(priv->dev, priv->dev->features);
	वापस !loopback_ok;
पूर्ण

अटल पूर्णांक mlx4_en_test_पूर्णांकerrupts(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err = 0;
	पूर्णांक i = 0;

	err = mlx4_test_async(mdev->dev);
	/* When not in MSI_X or slave, test only async */
	अगर (!(mdev->dev->flags & MLX4_FLAG_MSI_X) || mlx4_is_slave(mdev->dev))
		वापस err;

	/* A loop over all completion vectors of current port,
	 * क्रम each vector check whether it works by mapping command
	 * completions to that vector and perक्रमming a NOP command
	 */
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		err = mlx4_test_पूर्णांकerrupt(mdev->dev, priv->rx_cq[i]->vector);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_test_link(काष्ठा mlx4_en_priv *priv)
अणु
	अगर (mlx4_en_QUERY_PORT(priv->mdev, priv->port))
		वापस -ENOMEM;
	अगर (priv->port_state.link_state == 1)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक mlx4_en_test_speed(काष्ठा mlx4_en_priv *priv)
अणु

	अगर (mlx4_en_QUERY_PORT(priv->mdev, priv->port))
		वापस -ENOMEM;

	/* The device supports 100M, 1G, 10G, 20G, 40G and 56G speed */
	अगर (priv->port_state.link_speed != SPEED_100 &&
	    priv->port_state.link_speed != SPEED_1000 &&
	    priv->port_state.link_speed != SPEED_10000 &&
	    priv->port_state.link_speed != SPEED_20000 &&
	    priv->port_state.link_speed != SPEED_40000 &&
	    priv->port_state.link_speed != SPEED_56000)
		वापस priv->port_state.link_speed;

	वापस 0;
पूर्ण


व्योम mlx4_en_ex_selftest(काष्ठा net_device *dev, u32 *flags, u64 *buf)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक i, carrier_ok;

	स_रखो(buf, 0, माप(u64) * MLX4_EN_NUM_SELF_TEST);

	अगर (*flags & ETH_TEST_FL_OFFLINE) अणु
		/* disable the पूर्णांकerface */
		carrier_ok = netअगर_carrier_ok(dev);

		netअगर_carrier_off(dev);
		/* Wait until all tx queues are empty.
		 * there should not be any additional incoming traffic
		 * since we turned the carrier off */
		msleep(200);

		अगर (priv->mdev->dev->caps.flags &
					MLX4_DEV_CAP_FLAG_UC_LOOPBACK) अणु
			buf[3] = mlx4_en_test_रेजिस्टरs(priv);
			अगर (priv->port_up && dev->mtu >= MLX4_SELFTEST_LB_MIN_MTU)
				buf[4] = mlx4_en_test_loopback(priv);
		पूर्ण

		अगर (carrier_ok)
			netअगर_carrier_on(dev);

	पूर्ण
	buf[0] = mlx4_en_test_पूर्णांकerrupts(priv);
	buf[1] = mlx4_en_test_link(priv);
	buf[2] = mlx4_en_test_speed(priv);

	क्रम (i = 0; i < MLX4_EN_NUM_SELF_TEST; i++) अणु
		अगर (buf[i])
			*flags |= ETH_TEST_FL_FAILED;
	पूर्ण
पूर्ण
