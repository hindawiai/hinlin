<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies, Ltd.  All rights reserved.
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

#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <net/udp.h>
#समावेश "en.h"
#समावेश "en/port.h"

क्रमागत अणु
	MLX5E_ST_LINK_STATE,
	MLX5E_ST_LINK_SPEED,
	MLX5E_ST_HEALTH_INFO,
#अगर_घोषित CONFIG_INET
	MLX5E_ST_LOOPBACK,
#पूर्ण_अगर
	MLX5E_ST_NUM,
पूर्ण;

स्थिर अक्षर mlx5e_self_tests[MLX5E_ST_NUM][ETH_GSTRING_LEN] = अणु
	"Link Test",
	"Speed Test",
	"Health Test",
#अगर_घोषित CONFIG_INET
	"Loopback Test",
#पूर्ण_अगर
पूर्ण;

पूर्णांक mlx5e_self_test_num(काष्ठा mlx5e_priv *priv)
अणु
	वापस ARRAY_SIZE(mlx5e_self_tests);
पूर्ण

अटल पूर्णांक mlx5e_test_health_info(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_health *health = &priv->mdev->priv.health;

	वापस health->fatal_error ? 1 : 0;
पूर्ण

अटल पूर्णांक mlx5e_test_link_state(काष्ठा mlx5e_priv *priv)
अणु
	u8 port_state;

	अगर (!netअगर_carrier_ok(priv->netdev))
		वापस 1;

	port_state = mlx5_query_vport_state(priv->mdev, MLX5_VPORT_STATE_OP_MOD_VNIC_VPORT, 0);
	वापस port_state == VPORT_STATE_UP ? 0 : 1;
पूर्ण

अटल पूर्णांक mlx5e_test_link_speed(काष्ठा mlx5e_priv *priv)
अणु
	u32 speed;

	अगर (!netअगर_carrier_ok(priv->netdev))
		वापस 1;

	वापस mlx5e_port_linkspeed(priv->mdev, &speed);
पूर्ण

काष्ठा mlx5ehdr अणु
	__be32 version;
	__be64 magic;
पूर्ण;

#अगर_घोषित CONFIG_INET
/* loopback test */
#घोषणा MLX5E_TEST_PKT_SIZE (माप(काष्ठा ethhdr) + माप(काष्ठा iphdr) +\
			     माप(काष्ठा udphdr) + माप(काष्ठा mlx5ehdr))
#घोषणा MLX5E_TEST_MAGIC 0x5AEED15C001ULL

अटल काष्ठा sk_buff *mlx5e_test_get_udp_skb(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा mlx5ehdr *mlxh;
	काष्ठा ethhdr *ethh;
	काष्ठा udphdr *udph;
	काष्ठा iphdr *iph;
	पूर्णांक    iplen;

	skb = netdev_alloc_skb(priv->netdev, MLX5E_TEST_PKT_SIZE);
	अगर (!skb) अणु
		netdev_err(priv->netdev, "\tFailed to alloc loopback skb\n");
		वापस शून्य;
	पूर्ण

	net_prefetchw(skb->data);
	skb_reserve(skb, NET_IP_ALIGN);

	/*  Reserve क्रम ethernet and IP header  */
	ethh = skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);

	skb_set_network_header(skb, skb->len);
	iph = skb_put(skb, माप(काष्ठा iphdr));

	skb_set_transport_header(skb, skb->len);
	udph = skb_put(skb, माप(काष्ठा udphdr));

	/* Fill ETH header */
	ether_addr_copy(ethh->h_dest, priv->netdev->dev_addr);
	eth_zero_addr(ethh->h_source);
	ethh->h_proto = htons(ETH_P_IP);

	/* Fill UDP header */
	udph->source = htons(9);
	udph->dest = htons(9); /* Discard Protocol */
	udph->len = htons(माप(काष्ठा mlx5ehdr) + माप(काष्ठा udphdr));
	udph->check = 0;

	/* Fill IP header */
	iph->ihl = 5;
	iph->ttl = 32;
	iph->version = 4;
	iph->protocol = IPPROTO_UDP;
	iplen = माप(काष्ठा iphdr) + माप(काष्ठा udphdr) +
		माप(काष्ठा mlx5ehdr);
	iph->tot_len = htons(iplen);
	iph->frag_off = 0;
	iph->saddr = 0;
	iph->daddr = 0;
	iph->tos = 0;
	iph->id = 0;
	ip_send_check(iph);

	/* Fill test header and data */
	mlxh = skb_put(skb, माप(*mlxh));
	mlxh->version = 0;
	mlxh->magic = cpu_to_be64(MLX5E_TEST_MAGIC);

	skb->csum = 0;
	skb->ip_summed = CHECKSUM_PARTIAL;
	udp4_hwcsum(skb, iph->saddr, iph->daddr);

	skb->protocol = htons(ETH_P_IP);
	skb->pkt_type = PACKET_HOST;
	skb->dev = priv->netdev;

	वापस skb;
पूर्ण

काष्ठा mlx5e_lbt_priv अणु
	काष्ठा packet_type pt;
	काष्ठा completion comp;
	bool loopback_ok;
	bool local_lb;
पूर्ण;

अटल पूर्णांक
mlx5e_test_loopback_validate(काष्ठा sk_buff *skb,
			     काष्ठा net_device *ndev,
			     काष्ठा packet_type *pt,
			     काष्ठा net_device *orig_ndev)
अणु
	काष्ठा mlx5e_lbt_priv *lbtp = pt->af_packet_priv;
	काष्ठा mlx5ehdr *mlxh;
	काष्ठा ethhdr *ethh;
	काष्ठा udphdr *udph;
	काष्ठा iphdr *iph;

	/* We are only going to peek, no need to clone the SKB */
	अगर (MLX5E_TEST_PKT_SIZE - ETH_HLEN > skb_headlen(skb))
		जाओ out;

	ethh = (काष्ठा ethhdr *)skb_mac_header(skb);
	अगर (!ether_addr_equal(ethh->h_dest, orig_ndev->dev_addr))
		जाओ out;

	iph = ip_hdr(skb);
	अगर (iph->protocol != IPPROTO_UDP)
		जाओ out;

	/* Don't assume skb_transport_header() was set */
	udph = (काष्ठा udphdr *)((u8 *)iph + 4 * iph->ihl);
	अगर (udph->dest != htons(9))
		जाओ out;

	mlxh = (काष्ठा mlx5ehdr *)((अक्षर *)udph + माप(*udph));
	अगर (mlxh->magic != cpu_to_be64(MLX5E_TEST_MAGIC))
		जाओ out; /* so बंद ! */

	/* bingo */
	lbtp->loopback_ok = true;
	complete(&lbtp->comp);
out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_test_loopback_setup(काष्ठा mlx5e_priv *priv,
				     काष्ठा mlx5e_lbt_priv *lbtp)
अणु
	पूर्णांक err = 0;

	/* Temporarily enable local_lb */
	err = mlx5_nic_vport_query_local_lb(priv->mdev, &lbtp->local_lb);
	अगर (err)
		वापस err;

	अगर (!lbtp->local_lb) अणु
		err = mlx5_nic_vport_update_local_lb(priv->mdev, true);
		अगर (err)
			वापस err;
	पूर्ण

	err = mlx5e_refresh_tirs(priv, true, false);
	अगर (err)
		जाओ out;

	lbtp->loopback_ok = false;
	init_completion(&lbtp->comp);

	lbtp->pt.type = htons(ETH_P_IP);
	lbtp->pt.func = mlx5e_test_loopback_validate;
	lbtp->pt.dev = priv->netdev;
	lbtp->pt.af_packet_priv = lbtp;
	dev_add_pack(&lbtp->pt);

	वापस 0;

out:
	अगर (!lbtp->local_lb)
		mlx5_nic_vport_update_local_lb(priv->mdev, false);

	वापस err;
पूर्ण

अटल व्योम mlx5e_test_loopback_cleanup(काष्ठा mlx5e_priv *priv,
					काष्ठा mlx5e_lbt_priv *lbtp)
अणु
	अगर (!lbtp->local_lb)
		mlx5_nic_vport_update_local_lb(priv->mdev, false);

	dev_हटाओ_pack(&lbtp->pt);
	mlx5e_refresh_tirs(priv, false, false);
पूर्ण

#घोषणा MLX5E_LB_VERIFY_TIMEOUT (msecs_to_jअगरfies(200))
अटल पूर्णांक mlx5e_test_loopback(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_lbt_priv *lbtp;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक err;

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		netdev_err(priv->netdev,
			   "\tCan't perform loopback test while device is down\n");
		वापस -ENODEV;
	पूर्ण

	lbtp = kzalloc(माप(*lbtp), GFP_KERNEL);
	अगर (!lbtp)
		वापस -ENOMEM;
	lbtp->loopback_ok = false;

	err = mlx5e_test_loopback_setup(priv, lbtp);
	अगर (err)
		जाओ out;

	skb = mlx5e_test_get_udp_skb(priv);
	अगर (!skb) अणु
		err = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	skb_set_queue_mapping(skb, 0);
	err = dev_queue_xmit(skb);
	अगर (err) अणु
		netdev_err(priv->netdev,
			   "\tFailed to xmit loopback packet err(%d)\n",
			   err);
		जाओ cleanup;
	पूर्ण

	रुको_क्रम_completion_समयout(&lbtp->comp, MLX5E_LB_VERIFY_TIMEOUT);
	err = !lbtp->loopback_ok;

cleanup:
	mlx5e_test_loopback_cleanup(priv, lbtp);
out:
	kमुक्त(lbtp);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक (*mlx5e_st_func[MLX5E_ST_NUM])(काष्ठा mlx5e_priv *) = अणु
	mlx5e_test_link_state,
	mlx5e_test_link_speed,
	mlx5e_test_health_info,
#अगर_घोषित CONFIG_INET
	mlx5e_test_loopback,
#पूर्ण_अगर
पूर्ण;

व्योम mlx5e_self_test(काष्ठा net_device *ndev, काष्ठा ethtool_test *etest,
		     u64 *buf)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	स_रखो(buf, 0, माप(u64) * MLX5E_ST_NUM);

	mutex_lock(&priv->state_lock);
	netdev_info(ndev, "Self test begin..\n");

	क्रम (i = 0; i < MLX5E_ST_NUM; i++) अणु
		netdev_info(ndev, "\t[%d] %s start..\n",
			    i, mlx5e_self_tests[i]);
		buf[i] = mlx5e_st_func[i](priv);
		netdev_info(ndev, "\t[%d] %s end: result(%lld)\n",
			    i, mlx5e_self_tests[i], buf[i]);
	पूर्ण

	mutex_unlock(&priv->state_lock);

	क्रम (i = 0; i < MLX5E_ST_NUM; i++) अणु
		अगर (buf[i]) अणु
			etest->flags |= ETH_TEST_FL_FAILED;
			अवरोध;
		पूर्ण
	पूर्ण
	netdev_info(ndev, "Self test out: status flags(0x%x)\n",
		    etest->flags);
पूर्ण
