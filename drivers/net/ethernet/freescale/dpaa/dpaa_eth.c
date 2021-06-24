<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor Inc.
 * Copyright 2020 NXP
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/पन.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/icmp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/percpu.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sort.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <soc/fsl/bman.h>
#समावेश <soc/fsl/qman.h>
#समावेश "fman.h"
#समावेश "fman_port.h"
#समावेश "mac.h"
#समावेश "dpaa_eth.h"

/* CREATE_TRACE_POINTS only needs to be defined once. Other dpaa files
 * using trace events only need to #समावेश <trace/events/sched.h>
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "dpaa_eth_trace.h"

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "Module/Driver verbosity level (0=none,...,16=all)");

अटल u16 tx_समयout = 1000;
module_param(tx_समयout, uलघु, 0444);
MODULE_PARM_DESC(tx_समयout, "The Tx timeout in ms");

#घोषणा FM_FD_STAT_RX_ERRORS						\
	(FM_FD_ERR_DMA | FM_FD_ERR_PHYSICAL	| \
	 FM_FD_ERR_SIZE | FM_FD_ERR_CLS_DISCARD | \
	 FM_FD_ERR_EXTRACTION | FM_FD_ERR_NO_SCHEME	| \
	 FM_FD_ERR_PRS_TIMEOUT | FM_FD_ERR_PRS_ILL_INSTRUCT | \
	 FM_FD_ERR_PRS_HDR_ERR)

#घोषणा FM_FD_STAT_TX_ERRORS \
	(FM_FD_ERR_UNSUPPORTED_FORMAT | \
	 FM_FD_ERR_LENGTH | FM_FD_ERR_DMA)

#घोषणा DPAA_MSG_DEFAULT (NETIF_MSG_DRV | NETIF_MSG_PROBE | \
			  NETIF_MSG_LINK | NETIF_MSG_IFUP | \
			  NETIF_MSG_IFDOWN | NETIF_MSG_HW)

#घोषणा DPAA_INGRESS_CS_THRESHOLD 0x10000000
/* Ingress congestion threshold on FMan ports
 * The size in bytes of the ingress tail-drop threshold on FMan ports.
 * Traffic piling up above this value will be rejected by QMan and discarded
 * by FMan.
 */

/* Size in bytes of the FQ taildrop threshold */
#घोषणा DPAA_FQ_TD 0x200000

#घोषणा DPAA_CS_THRESHOLD_1G 0x06000000
/* Egress congestion threshold on 1G ports, range 0x1000 .. 0x10000000
 * The size in bytes of the egress Congestion State notअगरication threshold on
 * 1G ports. The 1G dTSECs can quite easily be flooded by cores करोing Tx in a
 * tight loop (e.g. by sending UDP datagrams at "while(1) speed"),
 * and the larger the frame size, the more acute the problem.
 * So we have to find a balance between these factors:
 * - aव्योमing the device staying congested क्रम a proदीर्घed समय (risking
 *   the netdev watchकरोg to fire - see also the tx_समयout module param);
 * - affecting perक्रमmance of protocols such as TCP, which otherwise
 *   behave well under the congestion notअगरication mechanism;
 * - preventing the Tx cores from tightly-looping (as अगर the congestion
 *   threshold was too low to be effective);
 * - running out of memory अगर the CS threshold is set too high.
 */

#घोषणा DPAA_CS_THRESHOLD_10G 0x10000000
/* The size in bytes of the egress Congestion State notअगरication threshold on
 * 10G ports, range 0x1000 .. 0x10000000
 */

/* Largest value that the FQD's OAL field can hold */
#घोषणा FSL_QMAN_MAX_OAL	127

/* Default alignment क्रम start of data in an Rx FD */
#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
/* aligning data start to 64 aव्योमs DMA transaction splits, unless the buffer
 * is crossing a 4k page boundary
 */
#घोषणा DPAA_FD_DATA_ALIGNMENT  (fman_has_errata_a050385() ? 64 : 16)
/* aligning to 256 aव्योमs DMA transaction splits caused by 4k page boundary
 * crossings; also, all SG fragments except the last must have a size multiple
 * of 256 to aव्योम DMA transaction splits
 */
#घोषणा DPAA_A050385_ALIGN 256
#घोषणा DPAA_FD_RX_DATA_ALIGNMENT (fman_has_errata_a050385() ? \
				   DPAA_A050385_ALIGN : 16)
#अन्यथा
#घोषणा DPAA_FD_DATA_ALIGNMENT  16
#घोषणा DPAA_FD_RX_DATA_ALIGNMENT DPAA_FD_DATA_ALIGNMENT
#पूर्ण_अगर

/* The DPAA requires 256 bytes reserved and mapped क्रम the SGT */
#घोषणा DPAA_SGT_SIZE 256

/* Values क्रम the L3R field of the FM Parse Results
 */
/* L3 Type field: First IP Present IPv4 */
#घोषणा FM_L3_PARSE_RESULT_IPV4	0x8000
/* L3 Type field: First IP Present IPv6 */
#घोषणा FM_L3_PARSE_RESULT_IPV6	0x4000
/* Values क्रम the L4R field of the FM Parse Results */
/* L4 Type field: UDP */
#घोषणा FM_L4_PARSE_RESULT_UDP	0x40
/* L4 Type field: TCP */
#घोषणा FM_L4_PARSE_RESULT_TCP	0x20

/* FD status field indicating whether the FM Parser has attempted to validate
 * the L4 csum of the frame.
 * Note that having this bit set करोesn't necessarily imply that the checksum
 * is valid. One would have to check the parse results to find that out.
 */
#घोषणा FM_FD_STAT_L4CV         0x00000004

#घोषणा DPAA_SGT_MAX_ENTRIES 16 /* maximum number of entries in SG Table */
#घोषणा DPAA_BUFF_RELEASE_MAX 8 /* maximum number of buffers released at once */

#घोषणा FSL_DPAA_BPID_INV		0xff
#घोषणा FSL_DPAA_ETH_MAX_BUF_COUNT	128
#घोषणा FSL_DPAA_ETH_REFILL_THRESHOLD	80

#घोषणा DPAA_TX_PRIV_DATA_SIZE	16
#घोषणा DPAA_PARSE_RESULTS_SIZE माप(काष्ठा fman_prs_result)
#घोषणा DPAA_TIME_STAMP_SIZE 8
#घोषणा DPAA_HASH_RESULTS_SIZE 8
#घोषणा DPAA_HWA_SIZE (DPAA_PARSE_RESULTS_SIZE + DPAA_TIME_STAMP_SIZE \
		       + DPAA_HASH_RESULTS_SIZE)
#घोषणा DPAA_RX_PRIV_DATA_DEFAULT_SIZE (DPAA_TX_PRIV_DATA_SIZE + \
					XDP_PACKET_HEADROOM - DPAA_HWA_SIZE)
#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
#घोषणा DPAA_RX_PRIV_DATA_A050385_SIZE (DPAA_A050385_ALIGN - DPAA_HWA_SIZE)
#घोषणा DPAA_RX_PRIV_DATA_SIZE (fman_has_errata_a050385() ? \
				DPAA_RX_PRIV_DATA_A050385_SIZE : \
				DPAA_RX_PRIV_DATA_DEFAULT_SIZE)
#अन्यथा
#घोषणा DPAA_RX_PRIV_DATA_SIZE DPAA_RX_PRIV_DATA_DEFAULT_SIZE
#पूर्ण_अगर

#घोषणा DPAA_ETH_PCD_RXQ_NUM	128

#घोषणा DPAA_ENQUEUE_RETRIES	100000

क्रमागत port_type अणुRX, TXपूर्ण;

काष्ठा fm_port_fqs अणु
	काष्ठा dpaa_fq *tx_defq;
	काष्ठा dpaa_fq *tx_errq;
	काष्ठा dpaa_fq *rx_defq;
	काष्ठा dpaa_fq *rx_errq;
	काष्ठा dpaa_fq *rx_pcdq;
पूर्ण;

/* All the dpa bps in use at any moment */
अटल काष्ठा dpaa_bp *dpaa_bp_array[BM_MAX_NUM_OF_POOLS];

#घोषणा DPAA_BP_RAW_SIZE 4096

#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
#घोषणा dpaa_bp_size(raw_size) (SKB_WITH_OVERHEAD(raw_size) & \
				~(DPAA_A050385_ALIGN - 1))
#अन्यथा
#घोषणा dpaa_bp_size(raw_size) SKB_WITH_OVERHEAD(raw_size)
#पूर्ण_अगर

अटल पूर्णांक dpaa_max_frm;

अटल पूर्णांक dpaa_rx_extra_headroom;

#घोषणा dpaa_get_max_mtu()	\
	(dpaa_max_frm - (VLAN_ETH_HLEN + ETH_FCS_LEN))

अटल पूर्णांक dpaa_netdev_init(काष्ठा net_device *net_dev,
			    स्थिर काष्ठा net_device_ops *dpaa_ops,
			    u16 tx_समयout)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा dpaa_percpu_priv *percpu_priv;
	स्थिर u8 *mac_addr;
	पूर्णांक i, err;

	/* Although we access another CPU's निजी data here
	 * we करो it at initialization so it is safe
	 */
	क्रम_each_possible_cpu(i) अणु
		percpu_priv = per_cpu_ptr(priv->percpu_priv, i);
		percpu_priv->net_dev = net_dev;
	पूर्ण

	net_dev->netdev_ops = dpaa_ops;
	mac_addr = priv->mac_dev->addr;

	net_dev->mem_start = priv->mac_dev->res->start;
	net_dev->mem_end = priv->mac_dev->res->end;

	net_dev->min_mtu = ETH_MIN_MTU;
	net_dev->max_mtu = dpaa_get_max_mtu();

	net_dev->hw_features |= (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				 NETIF_F_LLTX | NETIF_F_RXHASH);

	net_dev->hw_features |= NETIF_F_SG | NETIF_F_HIGHDMA;
	/* The kernels enables GSO स्वतःmatically, अगर we declare NETIF_F_SG.
	 * For conक्रमmity, we'll still declare GSO explicitly.
	 */
	net_dev->features |= NETIF_F_GSO;
	net_dev->features |= NETIF_F_RXCSUM;

	net_dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	/* we करो not want shared skbs on TX */
	net_dev->priv_flags &= ~IFF_TX_SKB_SHARING;

	net_dev->features |= net_dev->hw_features;
	net_dev->vlan_features = net_dev->features;

	अगर (is_valid_ether_addr(mac_addr)) अणु
		स_नकल(net_dev->perm_addr, mac_addr, net_dev->addr_len);
		स_नकल(net_dev->dev_addr, mac_addr, net_dev->addr_len);
	पूर्ण अन्यथा अणु
		eth_hw_addr_अक्रमom(net_dev);
		err = priv->mac_dev->change_addr(priv->mac_dev->fman_mac,
			(enet_addr_t *)net_dev->dev_addr);
		अगर (err) अणु
			dev_err(dev, "Failed to set random MAC address\n");
			वापस -EINVAL;
		पूर्ण
		dev_info(dev, "Using random MAC address: %pM\n",
			 net_dev->dev_addr);
	पूर्ण

	net_dev->ethtool_ops = &dpaa_ethtool_ops;

	net_dev->needed_headroom = priv->tx_headroom;
	net_dev->watchकरोg_समयo = msecs_to_jअगरfies(tx_समयout);

	/* start without the RUNNING flag, phylib controls it later */
	netअगर_carrier_off(net_dev);

	err = रेजिस्टर_netdev(net_dev);
	अगर (err < 0) अणु
		dev_err(dev, "register_netdev() = %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_stop(काष्ठा net_device *net_dev)
अणु
	काष्ठा mac_device *mac_dev;
	काष्ठा dpaa_priv *priv;
	पूर्णांक i, err, error;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;

	netअगर_tx_stop_all_queues(net_dev);
	/* Allow the Fman (Tx) port to process in-flight frames beक्रमe we
	 * try चयनing it off.
	 */
	msleep(200);

	err = mac_dev->stop(mac_dev);
	अगर (err < 0)
		netअगर_err(priv, अगरकरोwn, net_dev, "mac_dev->stop() = %d\n",
			  err);

	क्रम (i = 0; i < ARRAY_SIZE(mac_dev->port); i++) अणु
		error = fman_port_disable(mac_dev->port[i]);
		अगर (error)
			err = error;
	पूर्ण

	अगर (net_dev->phydev)
		phy_disconnect(net_dev->phydev);
	net_dev->phydev = शून्य;

	msleep(200);

	वापस err;
पूर्ण

अटल व्योम dpaa_tx_समयout(काष्ठा net_device *net_dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा dpaa_percpu_priv *percpu_priv;
	स्थिर काष्ठा dpaa_priv	*priv;

	priv = netdev_priv(net_dev);
	percpu_priv = this_cpu_ptr(priv->percpu_priv);

	netअगर_crit(priv, समयr, net_dev, "Transmit timeout latency: %u ms\n",
		   jअगरfies_to_msecs(jअगरfies - dev_trans_start(net_dev)));

	percpu_priv->stats.tx_errors++;
पूर्ण

/* Calculates the statistics क्रम the given device by adding the statistics
 * collected by each CPU.
 */
अटल व्योम dpaa_get_stats64(काष्ठा net_device *net_dev,
			     काष्ठा rtnl_link_stats64 *s)
अणु
	पूर्णांक numstats = माप(काष्ठा rtnl_link_stats64) / माप(u64);
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);
	काष्ठा dpaa_percpu_priv *percpu_priv;
	u64 *netstats = (u64 *)s;
	u64 *cpustats;
	पूर्णांक i, j;

	क्रम_each_possible_cpu(i) अणु
		percpu_priv = per_cpu_ptr(priv->percpu_priv, i);

		cpustats = (u64 *)&percpu_priv->stats;

		/* add stats from all CPUs */
		क्रम (j = 0; j < numstats; j++)
			netstats[j] += cpustats[j];
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa_setup_tc(काष्ठा net_device *net_dev, क्रमागत tc_setup_type type,
			 व्योम *type_data)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);
	काष्ठा tc_mqprio_qopt *mqprio = type_data;
	u8 num_tc;
	पूर्णांक i;

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	num_tc = mqprio->num_tc;

	अगर (num_tc == priv->num_tc)
		वापस 0;

	अगर (!num_tc) अणु
		netdev_reset_tc(net_dev);
		जाओ out;
	पूर्ण

	अगर (num_tc > DPAA_TC_NUM) अणु
		netdev_err(net_dev, "Too many traffic classes: max %d supported.\n",
			   DPAA_TC_NUM);
		वापस -EINVAL;
	पूर्ण

	netdev_set_num_tc(net_dev, num_tc);

	क्रम (i = 0; i < num_tc; i++)
		netdev_set_tc_queue(net_dev, i, DPAA_TC_TXQ_NUM,
				    i * DPAA_TC_TXQ_NUM);

out:
	priv->num_tc = num_tc ? : 1;
	netअगर_set_real_num_tx_queues(net_dev, priv->num_tc * DPAA_TC_TXQ_NUM);
	वापस 0;
पूर्ण

अटल काष्ठा mac_device *dpaa_mac_dev_get(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dpaa_eth_data *eth_data;
	काष्ठा device *dpaa_dev;
	काष्ठा mac_device *mac_dev;

	dpaa_dev = &pdev->dev;
	eth_data = dpaa_dev->platक्रमm_data;
	अगर (!eth_data) अणु
		dev_err(dpaa_dev, "eth_data missing\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	mac_dev = eth_data->mac_dev;
	अगर (!mac_dev) अणु
		dev_err(dpaa_dev, "mac_dev missing\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस mac_dev;
पूर्ण

अटल पूर्णांक dpaa_set_mac_address(काष्ठा net_device *net_dev, व्योम *addr)
अणु
	स्थिर काष्ठा dpaa_priv *priv;
	काष्ठा mac_device *mac_dev;
	काष्ठा sockaddr old_addr;
	पूर्णांक err;

	priv = netdev_priv(net_dev);

	स_नकल(old_addr.sa_data, net_dev->dev_addr,  ETH_ALEN);

	err = eth_mac_addr(net_dev, addr);
	अगर (err < 0) अणु
		netअगर_err(priv, drv, net_dev, "eth_mac_addr() = %d\n", err);
		वापस err;
	पूर्ण

	mac_dev = priv->mac_dev;

	err = mac_dev->change_addr(mac_dev->fman_mac,
				   (enet_addr_t *)net_dev->dev_addr);
	अगर (err < 0) अणु
		netअगर_err(priv, drv, net_dev, "mac_dev->change_addr() = %d\n",
			  err);
		/* reverting to previous address */
		eth_mac_addr(net_dev, &old_addr);

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpaa_set_rx_mode(काष्ठा net_device *net_dev)
अणु
	स्थिर काष्ठा dpaa_priv	*priv;
	पूर्णांक err;

	priv = netdev_priv(net_dev);

	अगर (!!(net_dev->flags & IFF_PROMISC) != priv->mac_dev->promisc) अणु
		priv->mac_dev->promisc = !priv->mac_dev->promisc;
		err = priv->mac_dev->set_promisc(priv->mac_dev->fman_mac,
						 priv->mac_dev->promisc);
		अगर (err < 0)
			netअगर_err(priv, drv, net_dev,
				  "mac_dev->set_promisc() = %d\n",
				  err);
	पूर्ण

	अगर (!!(net_dev->flags & IFF_ALLMULTI) != priv->mac_dev->allmulti) अणु
		priv->mac_dev->allmulti = !priv->mac_dev->allmulti;
		err = priv->mac_dev->set_allmulti(priv->mac_dev->fman_mac,
						  priv->mac_dev->allmulti);
		अगर (err < 0)
			netअगर_err(priv, drv, net_dev,
				  "mac_dev->set_allmulti() = %d\n",
				  err);
	पूर्ण

	err = priv->mac_dev->set_multi(net_dev, priv->mac_dev);
	अगर (err < 0)
		netअगर_err(priv, drv, net_dev, "mac_dev->set_multi() = %d\n",
			  err);
पूर्ण

अटल काष्ठा dpaa_bp *dpaa_bpid2pool(पूर्णांक bpid)
अणु
	अगर (WARN_ON(bpid < 0 || bpid >= BM_MAX_NUM_OF_POOLS))
		वापस शून्य;

	वापस dpaa_bp_array[bpid];
पूर्ण

/* checks अगर this bpool is alपढ़ोy allocated */
अटल bool dpaa_bpid2pool_use(पूर्णांक bpid)
अणु
	अगर (dpaa_bpid2pool(bpid)) अणु
		refcount_inc(&dpaa_bp_array[bpid]->refs);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* called only once per bpid by dpaa_bp_alloc_pool() */
अटल व्योम dpaa_bpid2pool_map(पूर्णांक bpid, काष्ठा dpaa_bp *dpaa_bp)
अणु
	dpaa_bp_array[bpid] = dpaa_bp;
	refcount_set(&dpaa_bp->refs, 1);
पूर्ण

अटल पूर्णांक dpaa_bp_alloc_pool(काष्ठा dpaa_bp *dpaa_bp)
अणु
	पूर्णांक err;

	अगर (dpaa_bp->size == 0 || dpaa_bp->config_count == 0) अणु
		pr_err("%s: Buffer pool is not properly initialized! Missing size or initial number of buffers\n",
		       __func__);
		वापस -EINVAL;
	पूर्ण

	/* If the pool is alपढ़ोy specअगरied, we only create one per bpid */
	अगर (dpaa_bp->bpid != FSL_DPAA_BPID_INV &&
	    dpaa_bpid2pool_use(dpaa_bp->bpid))
		वापस 0;

	अगर (dpaa_bp->bpid == FSL_DPAA_BPID_INV) अणु
		dpaa_bp->pool = bman_new_pool();
		अगर (!dpaa_bp->pool) अणु
			pr_err("%s: bman_new_pool() failed\n",
			       __func__);
			वापस -ENODEV;
		पूर्ण

		dpaa_bp->bpid = (u8)bman_get_bpid(dpaa_bp->pool);
	पूर्ण

	अगर (dpaa_bp->seed_cb) अणु
		err = dpaa_bp->seed_cb(dpaa_bp);
		अगर (err)
			जाओ pool_seed_failed;
	पूर्ण

	dpaa_bpid2pool_map(dpaa_bp->bpid, dpaa_bp);

	वापस 0;

pool_seed_failed:
	pr_err("%s: pool seeding failed\n", __func__);
	bman_मुक्त_pool(dpaa_bp->pool);

	वापस err;
पूर्ण

/* हटाओ and मुक्त all the buffers from the given buffer pool */
अटल व्योम dpaa_bp_drain(काष्ठा dpaa_bp *bp)
अणु
	u8 num = 8;
	पूर्णांक ret;

	करो अणु
		काष्ठा bm_buffer bmb[8];
		पूर्णांक i;

		ret = bman_acquire(bp->pool, bmb, num);
		अगर (ret < 0) अणु
			अगर (num == 8) अणु
				/* we have less than 8 buffers left;
				 * drain them one by one
				 */
				num = 1;
				ret = 1;
				जारी;
			पूर्ण अन्यथा अणु
				/* Pool is fully drained */
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (bp->मुक्त_buf_cb)
			क्रम (i = 0; i < num; i++)
				bp->मुक्त_buf_cb(bp, &bmb[i]);
	पूर्ण जबतक (ret > 0);
पूर्ण

अटल व्योम dpaa_bp_मुक्त(काष्ठा dpaa_bp *dpaa_bp)
अणु
	काष्ठा dpaa_bp *bp = dpaa_bpid2pool(dpaa_bp->bpid);

	/* the mapping between bpid and dpaa_bp is करोne very late in the
	 * allocation procedure; अगर something failed beक्रमe the mapping, the bp
	 * was not configured, thereक्रमe we करोn't need the below inकाष्ठाions
	 */
	अगर (!bp)
		वापस;

	अगर (!refcount_dec_and_test(&bp->refs))
		वापस;

	अगर (bp->मुक्त_buf_cb)
		dpaa_bp_drain(bp);

	dpaa_bp_array[bp->bpid] = शून्य;
	bman_मुक्त_pool(bp->pool);
पूर्ण

अटल व्योम dpaa_bps_मुक्त(काष्ठा dpaa_priv *priv)
अणु
	dpaa_bp_मुक्त(priv->dpaa_bp);
पूर्ण

/* Use multiple WQs क्रम FQ assignment:
 *	- Tx Confirmation queues go to WQ1.
 *	- Rx Error and Tx Error queues go to WQ5 (giving them a better chance
 *	  to be scheduled, in हाल there are many more FQs in WQ6).
 *	- Rx Default goes to WQ6.
 *	- Tx queues go to dअगरferent WQs depending on their priority. Equal
 *	  chunks of NR_CPUS queues go to WQ6 (lowest priority), WQ2, WQ1 and
 *	  WQ0 (highest priority).
 * This ensures that Tx-confirmed buffers are समयly released. In particular,
 * it aव्योमs congestion on the Tx Confirm FQs, which can pile up PFDRs अगर they
 * are greatly outnumbered by other FQs in the प्रणाली, जबतक
 * dequeue scheduling is round-robin.
 */
अटल अंतरभूत व्योम dpaa_assign_wq(काष्ठा dpaa_fq *fq, पूर्णांक idx)
अणु
	चयन (fq->fq_type) अणु
	हाल FQ_TYPE_TX_CONFIRM:
	हाल FQ_TYPE_TX_CONF_MQ:
		fq->wq = 1;
		अवरोध;
	हाल FQ_TYPE_RX_ERROR:
	हाल FQ_TYPE_TX_ERROR:
		fq->wq = 5;
		अवरोध;
	हाल FQ_TYPE_RX_DEFAULT:
	हाल FQ_TYPE_RX_PCD:
		fq->wq = 6;
		अवरोध;
	हाल FQ_TYPE_TX:
		चयन (idx / DPAA_TC_TXQ_NUM) अणु
		हाल 0:
			/* Low priority (best efक्रमt) */
			fq->wq = 6;
			अवरोध;
		हाल 1:
			/* Medium priority */
			fq->wq = 2;
			अवरोध;
		हाल 2:
			/* High priority */
			fq->wq = 1;
			अवरोध;
		हाल 3:
			/* Very high priority */
			fq->wq = 0;
			अवरोध;
		शेष:
			WARN(1, "Too many TX FQs: more than %d!\n",
			     DPAA_ETH_TXQ_NUM);
		पूर्ण
		अवरोध;
	शेष:
		WARN(1, "Invalid FQ type %d for FQID %d!\n",
		     fq->fq_type, fq->fqid);
	पूर्ण
पूर्ण

अटल काष्ठा dpaa_fq *dpaa_fq_alloc(काष्ठा device *dev,
				     u32 start, u32 count,
				     काष्ठा list_head *list,
				     क्रमागत dpaa_fq_type fq_type)
अणु
	काष्ठा dpaa_fq *dpaa_fq;
	पूर्णांक i;

	dpaa_fq = devm_kसुस्मृति(dev, count, माप(*dpaa_fq),
			       GFP_KERNEL);
	अगर (!dpaa_fq)
		वापस शून्य;

	क्रम (i = 0; i < count; i++) अणु
		dpaa_fq[i].fq_type = fq_type;
		dpaa_fq[i].fqid = start ? start + i : 0;
		list_add_tail(&dpaa_fq[i].list, list);
	पूर्ण

	क्रम (i = 0; i < count; i++)
		dpaa_assign_wq(dpaa_fq + i, i);

	वापस dpaa_fq;
पूर्ण

अटल पूर्णांक dpaa_alloc_all_fqs(काष्ठा device *dev, काष्ठा list_head *list,
			      काष्ठा fm_port_fqs *port_fqs)
अणु
	काष्ठा dpaa_fq *dpaa_fq;
	u32 fq_base, fq_base_aligned, i;

	dpaa_fq = dpaa_fq_alloc(dev, 0, 1, list, FQ_TYPE_RX_ERROR);
	अगर (!dpaa_fq)
		जाओ fq_alloc_failed;

	port_fqs->rx_errq = &dpaa_fq[0];

	dpaa_fq = dpaa_fq_alloc(dev, 0, 1, list, FQ_TYPE_RX_DEFAULT);
	अगर (!dpaa_fq)
		जाओ fq_alloc_failed;

	port_fqs->rx_defq = &dpaa_fq[0];

	/* the PCD FQIDs range needs to be aligned क्रम correct operation */
	अगर (qman_alloc_fqid_range(&fq_base, 2 * DPAA_ETH_PCD_RXQ_NUM))
		जाओ fq_alloc_failed;

	fq_base_aligned = ALIGN(fq_base, DPAA_ETH_PCD_RXQ_NUM);

	क्रम (i = fq_base; i < fq_base_aligned; i++)
		qman_release_fqid(i);

	क्रम (i = fq_base_aligned + DPAA_ETH_PCD_RXQ_NUM;
	     i < (fq_base + 2 * DPAA_ETH_PCD_RXQ_NUM); i++)
		qman_release_fqid(i);

	dpaa_fq = dpaa_fq_alloc(dev, fq_base_aligned, DPAA_ETH_PCD_RXQ_NUM,
				list, FQ_TYPE_RX_PCD);
	अगर (!dpaa_fq)
		जाओ fq_alloc_failed;

	port_fqs->rx_pcdq = &dpaa_fq[0];

	अगर (!dpaa_fq_alloc(dev, 0, DPAA_ETH_TXQ_NUM, list, FQ_TYPE_TX_CONF_MQ))
		जाओ fq_alloc_failed;

	dpaa_fq = dpaa_fq_alloc(dev, 0, 1, list, FQ_TYPE_TX_ERROR);
	अगर (!dpaa_fq)
		जाओ fq_alloc_failed;

	port_fqs->tx_errq = &dpaa_fq[0];

	dpaa_fq = dpaa_fq_alloc(dev, 0, 1, list, FQ_TYPE_TX_CONFIRM);
	अगर (!dpaa_fq)
		जाओ fq_alloc_failed;

	port_fqs->tx_defq = &dpaa_fq[0];

	अगर (!dpaa_fq_alloc(dev, 0, DPAA_ETH_TXQ_NUM, list, FQ_TYPE_TX))
		जाओ fq_alloc_failed;

	वापस 0;

fq_alloc_failed:
	dev_err(dev, "dpaa_fq_alloc() failed\n");
	वापस -ENOMEM;
पूर्ण

अटल u32 rx_pool_channel;
अटल DEFINE_SPINLOCK(rx_pool_channel_init);

अटल पूर्णांक dpaa_get_channel(व्योम)
अणु
	spin_lock(&rx_pool_channel_init);
	अगर (!rx_pool_channel) अणु
		u32 pool;
		पूर्णांक ret;

		ret = qman_alloc_pool(&pool);

		अगर (!ret)
			rx_pool_channel = pool;
	पूर्ण
	spin_unlock(&rx_pool_channel_init);
	अगर (!rx_pool_channel)
		वापस -ENOMEM;
	वापस rx_pool_channel;
पूर्ण

अटल व्योम dpaa_release_channel(व्योम)
अणु
	qman_release_pool(rx_pool_channel);
पूर्ण

अटल व्योम dpaa_eth_add_channel(u16 channel, काष्ठा device *dev)
अणु
	u32 pool = QM_SDQCR_CHANNELS_POOL_CONV(channel);
	स्थिर cpumask_t *cpus = qman_affine_cpus();
	काष्ठा qman_portal *portal;
	पूर्णांक cpu;

	क्रम_each_cpu_and(cpu, cpus, cpu_online_mask) अणु
		portal = qman_get_affine_portal(cpu);
		qman_p_अटल_dequeue_add(portal, pool);
		qman_start_using_portal(portal, dev);
	पूर्ण
पूर्ण

/* Congestion group state change notअगरication callback.
 * Stops the device's egress queues जबतक they are congested and
 * wakes them upon निकासing congested state.
 * Also updates some CGR-related stats.
 */
अटल व्योम dpaa_eth_cgscn(काष्ठा qman_portal *qm, काष्ठा qman_cgr *cgr,
			   पूर्णांक congested)
अणु
	काष्ठा dpaa_priv *priv = (काष्ठा dpaa_priv *)container_of(cgr,
		काष्ठा dpaa_priv, cgr_data.cgr);

	अगर (congested) अणु
		priv->cgr_data.congestion_start_jअगरfies = jअगरfies;
		netअगर_tx_stop_all_queues(priv->net_dev);
		priv->cgr_data.cgr_congested_count++;
	पूर्ण अन्यथा अणु
		priv->cgr_data.congested_jअगरfies +=
			(jअगरfies - priv->cgr_data.congestion_start_jअगरfies);
		netअगर_tx_wake_all_queues(priv->net_dev);
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa_eth_cgr_init(काष्ठा dpaa_priv *priv)
अणु
	काष्ठा qm_mcc_initcgr initcgr;
	u32 cs_th;
	पूर्णांक err;

	err = qman_alloc_cgrid(&priv->cgr_data.cgr.cgrid);
	अगर (err < 0) अणु
		अगर (netअगर_msg_drv(priv))
			pr_err("%s: Error %d allocating CGR ID\n",
			       __func__, err);
		जाओ out_error;
	पूर्ण
	priv->cgr_data.cgr.cb = dpaa_eth_cgscn;

	/* Enable Congestion State Change Notअगरications and CS taildrop */
	स_रखो(&initcgr, 0, माप(initcgr));
	initcgr.we_mask = cpu_to_be16(QM_CGR_WE_CSCN_EN | QM_CGR_WE_CS_THRES);
	initcgr.cgr.cscn_en = QM_CGR_EN;

	/* Set dअगरferent thresholds based on the MAC speed.
	 * This may turn suboptimal अगर the MAC is reconfigured at a speed
	 * lower than its max, e.g. अगर a dTSEC later negotiates a 100Mbps link.
	 * In such हालs, we ought to reconfigure the threshold, too.
	 */
	अगर (priv->mac_dev->अगर_support & SUPPORTED_10000baseT_Full)
		cs_th = DPAA_CS_THRESHOLD_10G;
	अन्यथा
		cs_th = DPAA_CS_THRESHOLD_1G;
	qm_cgr_cs_thres_set64(&initcgr.cgr.cs_thres, cs_th, 1);

	initcgr.we_mask |= cpu_to_be16(QM_CGR_WE_CSTD_EN);
	initcgr.cgr.cstd_en = QM_CGR_EN;

	err = qman_create_cgr(&priv->cgr_data.cgr, QMAN_CGR_FLAG_USE_INIT,
			      &initcgr);
	अगर (err < 0) अणु
		अगर (netअगर_msg_drv(priv))
			pr_err("%s: Error %d creating CGR with ID %d\n",
			       __func__, err, priv->cgr_data.cgr.cgrid);
		qman_release_cgrid(priv->cgr_data.cgr.cgrid);
		जाओ out_error;
	पूर्ण
	अगर (netअगर_msg_drv(priv))
		pr_debug("Created CGR %d for netdev with hwaddr %pM on QMan channel %d\n",
			 priv->cgr_data.cgr.cgrid, priv->mac_dev->addr,
			 priv->cgr_data.cgr.chan);

out_error:
	वापस err;
पूर्ण

अटल अंतरभूत व्योम dpaa_setup_ingress(स्थिर काष्ठा dpaa_priv *priv,
				      काष्ठा dpaa_fq *fq,
				      स्थिर काष्ठा qman_fq *ढाँचा)
अणु
	fq->fq_base = *ढाँचा;
	fq->net_dev = priv->net_dev;

	fq->flags = QMAN_FQ_FLAG_NO_ENQUEUE;
	fq->channel = priv->channel;
पूर्ण

अटल अंतरभूत व्योम dpaa_setup_egress(स्थिर काष्ठा dpaa_priv *priv,
				     काष्ठा dpaa_fq *fq,
				     काष्ठा fman_port *port,
				     स्थिर काष्ठा qman_fq *ढाँचा)
अणु
	fq->fq_base = *ढाँचा;
	fq->net_dev = priv->net_dev;

	अगर (port) अणु
		fq->flags = QMAN_FQ_FLAG_TO_DCPORTAL;
		fq->channel = (u16)fman_port_get_qman_channel_id(port);
	पूर्ण अन्यथा अणु
		fq->flags = QMAN_FQ_FLAG_NO_MODIFY;
	पूर्ण
पूर्ण

अटल व्योम dpaa_fq_setup(काष्ठा dpaa_priv *priv,
			  स्थिर काष्ठा dpaa_fq_cbs *fq_cbs,
			  काष्ठा fman_port *tx_port)
अणु
	पूर्णांक egress_cnt = 0, conf_cnt = 0, num_portals = 0, portal_cnt = 0, cpu;
	स्थिर cpumask_t *affine_cpus = qman_affine_cpus();
	u16 channels[NR_CPUS];
	काष्ठा dpaa_fq *fq;

	क्रम_each_cpu_and(cpu, affine_cpus, cpu_online_mask)
		channels[num_portals++] = qman_affine_channel(cpu);

	अगर (num_portals == 0)
		dev_err(priv->net_dev->dev.parent,
			"No Qman software (affine) channels found\n");

	/* Initialize each FQ in the list */
	list_क्रम_each_entry(fq, &priv->dpaa_fq_list, list) अणु
		चयन (fq->fq_type) अणु
		हाल FQ_TYPE_RX_DEFAULT:
			dpaa_setup_ingress(priv, fq, &fq_cbs->rx_defq);
			अवरोध;
		हाल FQ_TYPE_RX_ERROR:
			dpaa_setup_ingress(priv, fq, &fq_cbs->rx_errq);
			अवरोध;
		हाल FQ_TYPE_RX_PCD:
			अगर (!num_portals)
				जारी;
			dpaa_setup_ingress(priv, fq, &fq_cbs->rx_defq);
			fq->channel = channels[portal_cnt++ % num_portals];
			अवरोध;
		हाल FQ_TYPE_TX:
			dpaa_setup_egress(priv, fq, tx_port,
					  &fq_cbs->egress_ern);
			/* If we have more Tx queues than the number of cores,
			 * just ignore the extra ones.
			 */
			अगर (egress_cnt < DPAA_ETH_TXQ_NUM)
				priv->egress_fqs[egress_cnt++] = &fq->fq_base;
			अवरोध;
		हाल FQ_TYPE_TX_CONF_MQ:
			priv->conf_fqs[conf_cnt++] = &fq->fq_base;
			fallthrough;
		हाल FQ_TYPE_TX_CONFIRM:
			dpaa_setup_ingress(priv, fq, &fq_cbs->tx_defq);
			अवरोध;
		हाल FQ_TYPE_TX_ERROR:
			dpaa_setup_ingress(priv, fq, &fq_cbs->tx_errq);
			अवरोध;
		शेष:
			dev_warn(priv->net_dev->dev.parent,
				 "Unknown FQ type detected!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	 /* Make sure all CPUs receive a corresponding Tx queue. */
	जबतक (egress_cnt < DPAA_ETH_TXQ_NUM) अणु
		list_क्रम_each_entry(fq, &priv->dpaa_fq_list, list) अणु
			अगर (fq->fq_type != FQ_TYPE_TX)
				जारी;
			priv->egress_fqs[egress_cnt++] = &fq->fq_base;
			अगर (egress_cnt == DPAA_ETH_TXQ_NUM)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक dpaa_tx_fq_to_id(स्थिर काष्ठा dpaa_priv *priv,
				   काष्ठा qman_fq *tx_fq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DPAA_ETH_TXQ_NUM; i++)
		अगर (priv->egress_fqs[i] == tx_fq)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dpaa_fq_init(काष्ठा dpaa_fq *dpaa_fq, bool td_enable)
अणु
	स्थिर काष्ठा dpaa_priv	*priv;
	काष्ठा qman_fq *confq = शून्य;
	काष्ठा qm_mcc_initfq initfq;
	काष्ठा device *dev;
	काष्ठा qman_fq *fq;
	पूर्णांक queue_id;
	पूर्णांक err;

	priv = netdev_priv(dpaa_fq->net_dev);
	dev = dpaa_fq->net_dev->dev.parent;

	अगर (dpaa_fq->fqid == 0)
		dpaa_fq->flags |= QMAN_FQ_FLAG_DYNAMIC_FQID;

	dpaa_fq->init = !(dpaa_fq->flags & QMAN_FQ_FLAG_NO_MODIFY);

	err = qman_create_fq(dpaa_fq->fqid, dpaa_fq->flags, &dpaa_fq->fq_base);
	अगर (err) अणु
		dev_err(dev, "qman_create_fq() failed\n");
		वापस err;
	पूर्ण
	fq = &dpaa_fq->fq_base;

	अगर (dpaa_fq->init) अणु
		स_रखो(&initfq, 0, माप(initfq));

		initfq.we_mask = cpu_to_be16(QM_INITFQ_WE_FQCTRL);
		/* Note: we may get to keep an empty FQ in cache */
		initfq.fqd.fq_ctrl = cpu_to_be16(QM_FQCTRL_PREFERINCACHE);

		/* Try to reduce the number of portal पूर्णांकerrupts क्रम
		 * Tx Confirmation FQs.
		 */
		अगर (dpaa_fq->fq_type == FQ_TYPE_TX_CONFIRM)
			initfq.fqd.fq_ctrl |= cpu_to_be16(QM_FQCTRL_AVOIDBLOCK);

		/* FQ placement */
		initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_DESTWQ);

		qm_fqd_set_destwq(&initfq.fqd, dpaa_fq->channel, dpaa_fq->wq);

		/* Put all egress queues in a congestion group of their own.
		 * Sensu stricto, the Tx confirmation queues are Rx FQs,
		 * rather than Tx - but they nonetheless account क्रम the
		 * memory footprपूर्णांक on behalf of egress traffic. We thereक्रमe
		 * place them in the netdev's CGR, aदीर्घ with the Tx FQs.
		 */
		अगर (dpaa_fq->fq_type == FQ_TYPE_TX ||
		    dpaa_fq->fq_type == FQ_TYPE_TX_CONFIRM ||
		    dpaa_fq->fq_type == FQ_TYPE_TX_CONF_MQ) अणु
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_CGID);
			initfq.fqd.fq_ctrl |= cpu_to_be16(QM_FQCTRL_CGE);
			initfq.fqd.cgid = (u8)priv->cgr_data.cgr.cgrid;
			/* Set a fixed overhead accounting, in an attempt to
			 * reduce the impact of fixed-size skb shells and the
			 * driver's needed headroom on प्रणाली memory. This is
			 * especially the हाल when the egress traffic is
			 * composed of small datagrams.
			 * Unक्रमtunately, QMan's OAL value is capped to an
			 * insufficient value, but even that is better than
			 * no overhead accounting at all.
			 */
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_OAC);
			qm_fqd_set_oac(&initfq.fqd, QM_OAC_CG);
			qm_fqd_set_oal(&initfq.fqd,
				       min(माप(काष्ठा sk_buff) +
				       priv->tx_headroom,
				       (माप_प्रकार)FSL_QMAN_MAX_OAL));
		पूर्ण

		अगर (td_enable) अणु
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_TDTHRESH);
			qm_fqd_set_taildrop(&initfq.fqd, DPAA_FQ_TD, 1);
			initfq.fqd.fq_ctrl = cpu_to_be16(QM_FQCTRL_TDE);
		पूर्ण

		अगर (dpaa_fq->fq_type == FQ_TYPE_TX) अणु
			queue_id = dpaa_tx_fq_to_id(priv, &dpaa_fq->fq_base);
			अगर (queue_id >= 0)
				confq = priv->conf_fqs[queue_id];
			अगर (confq) अणु
				initfq.we_mask |=
					cpu_to_be16(QM_INITFQ_WE_CONTEXTA);
			/* ContextA: OVOM=1(use contextA2 bits instead of ICAD)
			 *	     A2V=1 (contextA A2 field is valid)
			 *	     A0V=1 (contextA A0 field is valid)
			 *	     B0V=1 (contextB field is valid)
			 * ContextA A2: EBD=1 (deallocate buffers inside FMan)
			 * ContextB B0(ASPID): 0 (असलolute Virtual Storage ID)
			 */
				qm_fqd_context_a_set64(&initfq.fqd,
						       0x1e00000080000000ULL);
			पूर्ण
		पूर्ण

		/* Put all the ingress queues in our "ingress CGR". */
		अगर (priv->use_ingress_cgr &&
		    (dpaa_fq->fq_type == FQ_TYPE_RX_DEFAULT ||
		     dpaa_fq->fq_type == FQ_TYPE_RX_ERROR ||
		     dpaa_fq->fq_type == FQ_TYPE_RX_PCD)) अणु
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_CGID);
			initfq.fqd.fq_ctrl |= cpu_to_be16(QM_FQCTRL_CGE);
			initfq.fqd.cgid = (u8)priv->ingress_cgr.cgrid;
			/* Set a fixed overhead accounting, just like क्रम the
			 * egress CGR.
			 */
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_OAC);
			qm_fqd_set_oac(&initfq.fqd, QM_OAC_CG);
			qm_fqd_set_oal(&initfq.fqd,
				       min(माप(काष्ठा sk_buff) +
				       priv->tx_headroom,
				       (माप_प्रकार)FSL_QMAN_MAX_OAL));
		पूर्ण

		/* Initialization common to all ingress queues */
		अगर (dpaa_fq->flags & QMAN_FQ_FLAG_NO_ENQUEUE) अणु
			initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_CONTEXTA);
			initfq.fqd.fq_ctrl |= cpu_to_be16(QM_FQCTRL_HOLDACTIVE |
						QM_FQCTRL_CTXASTASHING);
			initfq.fqd.context_a.stashing.exclusive =
				QM_STASHING_EXCL_DATA | QM_STASHING_EXCL_CTX |
				QM_STASHING_EXCL_ANNOTATION;
			qm_fqd_set_stashing(&initfq.fqd, 1, 2,
					    DIV_ROUND_UP(माप(काष्ठा qman_fq),
							 64));
		पूर्ण

		err = qman_init_fq(fq, QMAN_INITFQ_FLAG_SCHED, &initfq);
		अगर (err < 0) अणु
			dev_err(dev, "qman_init_fq(%u) = %d\n",
				qman_fq_fqid(fq), err);
			qman_destroy_fq(fq);
			वापस err;
		पूर्ण
	पूर्ण

	dpaa_fq->fqid = qman_fq_fqid(fq);

	अगर (dpaa_fq->fq_type == FQ_TYPE_RX_DEFAULT ||
	    dpaa_fq->fq_type == FQ_TYPE_RX_PCD) अणु
		err = xdp_rxq_info_reg(&dpaa_fq->xdp_rxq, dpaa_fq->net_dev,
				       dpaa_fq->fqid, 0);
		अगर (err) अणु
			dev_err(dev, "xdp_rxq_info_reg() = %d\n", err);
			वापस err;
		पूर्ण

		err = xdp_rxq_info_reg_mem_model(&dpaa_fq->xdp_rxq,
						 MEM_TYPE_PAGE_ORDER0, शून्य);
		अगर (err) अणु
			dev_err(dev, "xdp_rxq_info_reg_mem_model() = %d\n",
				err);
			xdp_rxq_info_unreg(&dpaa_fq->xdp_rxq);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_fq_मुक्त_entry(काष्ठा device *dev, काष्ठा qman_fq *fq)
अणु
	स्थिर काष्ठा dpaa_priv  *priv;
	काष्ठा dpaa_fq *dpaa_fq;
	पूर्णांक err, error;

	err = 0;

	dpaa_fq = container_of(fq, काष्ठा dpaa_fq, fq_base);
	priv = netdev_priv(dpaa_fq->net_dev);

	अगर (dpaa_fq->init) अणु
		err = qman_retire_fq(fq, शून्य);
		अगर (err < 0 && netअगर_msg_drv(priv))
			dev_err(dev, "qman_retire_fq(%u) = %d\n",
				qman_fq_fqid(fq), err);

		error = qman_oos_fq(fq);
		अगर (error < 0 && netअगर_msg_drv(priv)) अणु
			dev_err(dev, "qman_oos_fq(%u) = %d\n",
				qman_fq_fqid(fq), error);
			अगर (err >= 0)
				err = error;
		पूर्ण
	पूर्ण

	अगर ((dpaa_fq->fq_type == FQ_TYPE_RX_DEFAULT ||
	     dpaa_fq->fq_type == FQ_TYPE_RX_PCD) &&
	    xdp_rxq_info_is_reg(&dpaa_fq->xdp_rxq))
		xdp_rxq_info_unreg(&dpaa_fq->xdp_rxq);

	qman_destroy_fq(fq);
	list_del(&dpaa_fq->list);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa_fq_मुक्त(काष्ठा device *dev, काष्ठा list_head *list)
अणु
	काष्ठा dpaa_fq *dpaa_fq, *पंचांगp;
	पूर्णांक err, error;

	err = 0;
	list_क्रम_each_entry_safe(dpaa_fq, पंचांगp, list, list) अणु
		error = dpaa_fq_मुक्त_entry(dev, (काष्ठा qman_fq *)dpaa_fq);
		अगर (error < 0 && err >= 0)
			err = error;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa_eth_init_tx_port(काष्ठा fman_port *port, काष्ठा dpaa_fq *errq,
				 काष्ठा dpaa_fq *defq,
				 काष्ठा dpaa_buffer_layout *buf_layout)
अणु
	काष्ठा fman_buffer_prefix_content buf_prefix_content;
	काष्ठा fman_port_params params;
	पूर्णांक err;

	स_रखो(&params, 0, माप(params));
	स_रखो(&buf_prefix_content, 0, माप(buf_prefix_content));

	buf_prefix_content.priv_data_size = buf_layout->priv_data_size;
	buf_prefix_content.pass_prs_result = true;
	buf_prefix_content.pass_hash_result = true;
	buf_prefix_content.pass_समय_stamp = true;
	buf_prefix_content.data_align = DPAA_FD_DATA_ALIGNMENT;

	params.specअगरic_params.non_rx_params.err_fqid = errq->fqid;
	params.specअगरic_params.non_rx_params.dflt_fqid = defq->fqid;

	err = fman_port_config(port, &params);
	अगर (err) अणु
		pr_err("%s: fman_port_config failed\n", __func__);
		वापस err;
	पूर्ण

	err = fman_port_cfg_buf_prefix_content(port, &buf_prefix_content);
	अगर (err) अणु
		pr_err("%s: fman_port_cfg_buf_prefix_content failed\n",
		       __func__);
		वापस err;
	पूर्ण

	err = fman_port_init(port);
	अगर (err)
		pr_err("%s: fm_port_init failed\n", __func__);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa_eth_init_rx_port(काष्ठा fman_port *port, काष्ठा dpaa_bp *bp,
				 काष्ठा dpaa_fq *errq,
				 काष्ठा dpaa_fq *defq, काष्ठा dpaa_fq *pcdq,
				 काष्ठा dpaa_buffer_layout *buf_layout)
अणु
	काष्ठा fman_buffer_prefix_content buf_prefix_content;
	काष्ठा fman_port_rx_params *rx_p;
	काष्ठा fman_port_params params;
	पूर्णांक err;

	स_रखो(&params, 0, माप(params));
	स_रखो(&buf_prefix_content, 0, माप(buf_prefix_content));

	buf_prefix_content.priv_data_size = buf_layout->priv_data_size;
	buf_prefix_content.pass_prs_result = true;
	buf_prefix_content.pass_hash_result = true;
	buf_prefix_content.pass_समय_stamp = true;
	buf_prefix_content.data_align = DPAA_FD_RX_DATA_ALIGNMENT;

	rx_p = &params.specअगरic_params.rx_params;
	rx_p->err_fqid = errq->fqid;
	rx_p->dflt_fqid = defq->fqid;
	अगर (pcdq) अणु
		rx_p->pcd_base_fqid = pcdq->fqid;
		rx_p->pcd_fqs_count = DPAA_ETH_PCD_RXQ_NUM;
	पूर्ण

	rx_p->ext_buf_pools.num_of_pools_used = 1;
	rx_p->ext_buf_pools.ext_buf_pool[0].id =  bp->bpid;
	rx_p->ext_buf_pools.ext_buf_pool[0].size = (u16)bp->size;

	err = fman_port_config(port, &params);
	अगर (err) अणु
		pr_err("%s: fman_port_config failed\n", __func__);
		वापस err;
	पूर्ण

	err = fman_port_cfg_buf_prefix_content(port, &buf_prefix_content);
	अगर (err) अणु
		pr_err("%s: fman_port_cfg_buf_prefix_content failed\n",
		       __func__);
		वापस err;
	पूर्ण

	err = fman_port_init(port);
	अगर (err)
		pr_err("%s: fm_port_init failed\n", __func__);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa_eth_init_ports(काष्ठा mac_device *mac_dev,
			       काष्ठा dpaa_bp *bp,
			       काष्ठा fm_port_fqs *port_fqs,
			       काष्ठा dpaa_buffer_layout *buf_layout,
			       काष्ठा device *dev)
अणु
	काष्ठा fman_port *rxport = mac_dev->port[RX];
	काष्ठा fman_port *txport = mac_dev->port[TX];
	पूर्णांक err;

	err = dpaa_eth_init_tx_port(txport, port_fqs->tx_errq,
				    port_fqs->tx_defq, &buf_layout[TX]);
	अगर (err)
		वापस err;

	err = dpaa_eth_init_rx_port(rxport, bp, port_fqs->rx_errq,
				    port_fqs->rx_defq, port_fqs->rx_pcdq,
				    &buf_layout[RX]);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa_bman_release(स्थिर काष्ठा dpaa_bp *dpaa_bp,
			     काष्ठा bm_buffer *bmb, पूर्णांक cnt)
अणु
	पूर्णांक err;

	err = bman_release(dpaa_bp->pool, bmb, cnt);
	/* Should never occur, address anyway to aव्योम leaking the buffers */
	अगर (WARN_ON(err) && dpaa_bp->मुक्त_buf_cb)
		जबतक (cnt-- > 0)
			dpaa_bp->मुक्त_buf_cb(dpaa_bp, &bmb[cnt]);

	वापस cnt;
पूर्ण

अटल व्योम dpaa_release_sgt_members(काष्ठा qm_sg_entry *sgt)
अणु
	काष्ठा bm_buffer bmb[DPAA_BUFF_RELEASE_MAX];
	काष्ठा dpaa_bp *dpaa_bp;
	पूर्णांक i = 0, j;

	स_रखो(bmb, 0, माप(bmb));

	करो अणु
		dpaa_bp = dpaa_bpid2pool(sgt[i].bpid);
		अगर (!dpaa_bp)
			वापस;

		j = 0;
		करो अणु
			WARN_ON(qm_sg_entry_is_ext(&sgt[i]));

			bm_buffer_set64(&bmb[j], qm_sg_entry_get64(&sgt[i]));

			j++; i++;
		पूर्ण जबतक (j < ARRAY_SIZE(bmb) &&
				!qm_sg_entry_is_final(&sgt[i - 1]) &&
				sgt[i - 1].bpid == sgt[i].bpid);

		dpaa_bman_release(dpaa_bp, bmb, j);
	पूर्ण जबतक (!qm_sg_entry_is_final(&sgt[i - 1]));
पूर्ण

अटल व्योम dpaa_fd_release(स्थिर काष्ठा net_device *net_dev,
			    स्थिर काष्ठा qm_fd *fd)
अणु
	काष्ठा qm_sg_entry *sgt;
	काष्ठा dpaa_bp *dpaa_bp;
	काष्ठा bm_buffer bmb;
	dma_addr_t addr;
	व्योम *vaddr;

	bmb.data = 0;
	bm_buffer_set64(&bmb, qm_fd_addr(fd));

	dpaa_bp = dpaa_bpid2pool(fd->bpid);
	अगर (!dpaa_bp)
		वापस;

	अगर (qm_fd_get_क्रमmat(fd) == qm_fd_sg) अणु
		vaddr = phys_to_virt(qm_fd_addr(fd));
		sgt = vaddr + qm_fd_get_offset(fd);

		dma_unmap_page(dpaa_bp->priv->rx_dma_dev, qm_fd_addr(fd),
			       DPAA_BP_RAW_SIZE, DMA_FROM_DEVICE);

		dpaa_release_sgt_members(sgt);

		addr = dma_map_page(dpaa_bp->priv->rx_dma_dev,
				    virt_to_page(vaddr), 0, DPAA_BP_RAW_SIZE,
				    DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dpaa_bp->priv->rx_dma_dev, addr)) अणु
			netdev_err(net_dev, "DMA mapping failed\n");
			वापस;
		पूर्ण
		bm_buffer_set64(&bmb, addr);
	पूर्ण

	dpaa_bman_release(dpaa_bp, &bmb, 1);
पूर्ण

अटल व्योम count_ern(काष्ठा dpaa_percpu_priv *percpu_priv,
		      स्थिर जोड़ qm_mr_entry *msg)
अणु
	चयन (msg->ern.rc & QM_MR_RC_MASK) अणु
	हाल QM_MR_RC_CGR_TAILDROP:
		percpu_priv->ern_cnt.cg_tdrop++;
		अवरोध;
	हाल QM_MR_RC_WRED:
		percpu_priv->ern_cnt.wred++;
		अवरोध;
	हाल QM_MR_RC_ERROR:
		percpu_priv->ern_cnt.err_cond++;
		अवरोध;
	हाल QM_MR_RC_ORPWINDOW_EARLY:
		percpu_priv->ern_cnt.early_winकरोw++;
		अवरोध;
	हाल QM_MR_RC_ORPWINDOW_LATE:
		percpu_priv->ern_cnt.late_winकरोw++;
		अवरोध;
	हाल QM_MR_RC_FQ_TAILDROP:
		percpu_priv->ern_cnt.fq_tdrop++;
		अवरोध;
	हाल QM_MR_RC_ORPWINDOW_RETIRED:
		percpu_priv->ern_cnt.fq_retired++;
		अवरोध;
	हाल QM_MR_RC_ORP_ZERO:
		percpu_priv->ern_cnt.orp_zero++;
		अवरोध;
	पूर्ण
पूर्ण

/* Turn on HW checksum computation क्रम this outgoing frame.
 * If the current protocol is not something we support in this regard
 * (or अगर the stack has alपढ़ोy computed the SW checksum), we करो nothing.
 *
 * Returns 0 अगर all goes well (or HW csum करोesn't apply), and a negative value
 * otherwise.
 *
 * Note that this function may modअगरy the fd->cmd field and the skb data buffer
 * (the Parse Results area).
 */
अटल पूर्णांक dpaa_enable_tx_csum(काष्ठा dpaa_priv *priv,
			       काष्ठा sk_buff *skb,
			       काष्ठा qm_fd *fd,
			       व्योम *parse_results)
अणु
	काष्ठा fman_prs_result *parse_result;
	u16 ethertype = ntohs(skb->protocol);
	काष्ठा ipv6hdr *ipv6h = शून्य;
	काष्ठा iphdr *iph;
	पूर्णांक retval = 0;
	u8 l4_proto;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	/* Note: L3 csum seems to be alपढ़ोy computed in sw, but we can't choose
	 * L4 alone from the FM configuration anyway.
	 */

	/* Fill in some fields of the Parse Results array, so the FMan
	 * can find them as अगर they came from the FMan Parser.
	 */
	parse_result = (काष्ठा fman_prs_result *)parse_results;

	/* If we're dealing with VLAN, get the real Ethernet type */
	अगर (ethertype == ETH_P_8021Q) अणु
		/* We can't always assume the MAC header is set correctly
		 * by the stack, so reset to beginning of skb->data
		 */
		skb_reset_mac_header(skb);
		ethertype = ntohs(vlan_eth_hdr(skb)->h_vlan_encapsulated_proto);
	पूर्ण

	/* Fill in the relevant L3 parse result fields
	 * and पढ़ो the L4 protocol type
	 */
	चयन (ethertype) अणु
	हाल ETH_P_IP:
		parse_result->l3r = cpu_to_be16(FM_L3_PARSE_RESULT_IPV4);
		iph = ip_hdr(skb);
		WARN_ON(!iph);
		l4_proto = iph->protocol;
		अवरोध;
	हाल ETH_P_IPV6:
		parse_result->l3r = cpu_to_be16(FM_L3_PARSE_RESULT_IPV6);
		ipv6h = ipv6_hdr(skb);
		WARN_ON(!ipv6h);
		l4_proto = ipv6h->nexthdr;
		अवरोध;
	शेष:
		/* We shouldn't even be here */
		अगर (net_ratelimit())
			netअगर_alert(priv, tx_err, priv->net_dev,
				    "Can't compute HW csum for L3 proto 0x%x\n",
				    ntohs(skb->protocol));
		retval = -EIO;
		जाओ वापस_error;
	पूर्ण

	/* Fill in the relevant L4 parse result fields */
	चयन (l4_proto) अणु
	हाल IPPROTO_UDP:
		parse_result->l4r = FM_L4_PARSE_RESULT_UDP;
		अवरोध;
	हाल IPPROTO_TCP:
		parse_result->l4r = FM_L4_PARSE_RESULT_TCP;
		अवरोध;
	शेष:
		अगर (net_ratelimit())
			netअगर_alert(priv, tx_err, priv->net_dev,
				    "Can't compute HW csum for L4 proto 0x%x\n",
				    l4_proto);
		retval = -EIO;
		जाओ वापस_error;
	पूर्ण

	/* At index 0 is IPOffset_1 as defined in the Parse Results */
	parse_result->ip_off[0] = (u8)skb_network_offset(skb);
	parse_result->l4_off = (u8)skb_transport_offset(skb);

	/* Enable L3 (and L4, अगर TCP or UDP) HW checksum. */
	fd->cmd |= cpu_to_be32(FM_FD_CMD_RPD | FM_FD_CMD_DTC);

	/* On P1023 and similar platक्रमms fd->cmd पूर्णांकerpretation could
	 * be disabled by setting CONTEXT_A bit ICMD; currently this bit
	 * is not set so we करो not need to check; in the future, अगर/when
	 * using context_a we need to check this bit
	 */

वापस_error:
	वापस retval;
पूर्ण

अटल पूर्णांक dpaa_bp_add_8_bufs(स्थिर काष्ठा dpaa_bp *dpaa_bp)
अणु
	काष्ठा net_device *net_dev = dpaa_bp->priv->net_dev;
	काष्ठा bm_buffer bmb[8];
	dma_addr_t addr;
	काष्ठा page *p;
	u8 i;

	क्रम (i = 0; i < 8; i++) अणु
		p = dev_alloc_pages(0);
		अगर (unlikely(!p)) अणु
			netdev_err(net_dev, "dev_alloc_pages() failed\n");
			जाओ release_previous_buffs;
		पूर्ण

		addr = dma_map_page(dpaa_bp->priv->rx_dma_dev, p, 0,
				    DPAA_BP_RAW_SIZE, DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(dpaa_bp->priv->rx_dma_dev,
					       addr))) अणु
			netdev_err(net_dev, "DMA map failed\n");
			जाओ release_previous_buffs;
		पूर्ण

		bmb[i].data = 0;
		bm_buffer_set64(&bmb[i], addr);
	पूर्ण

release_bufs:
	वापस dpaa_bman_release(dpaa_bp, bmb, i);

release_previous_buffs:
	WARN_ONCE(1, "dpaa_eth: failed to add buffers on Rx\n");

	bm_buffer_set64(&bmb[i], 0);
	/* Aव्योम releasing a completely null buffer; bman_release() requires
	 * at least one buffer.
	 */
	अगर (likely(i))
		जाओ release_bufs;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_bp_seed(काष्ठा dpaa_bp *dpaa_bp)
अणु
	पूर्णांक i;

	/* Give each CPU an alloपंचांगent of "config_count" buffers */
	क्रम_each_possible_cpu(i) अणु
		पूर्णांक *count_ptr = per_cpu_ptr(dpaa_bp->percpu_count, i);
		पूर्णांक j;

		/* Although we access another CPU's counters here
		 * we करो it at boot समय so it is safe
		 */
		क्रम (j = 0; j < dpaa_bp->config_count; j += 8)
			*count_ptr += dpaa_bp_add_8_bufs(dpaa_bp);
	पूर्ण
	वापस 0;
पूर्ण

/* Add buffers/(pages) क्रम Rx processing whenever bpool count falls below
 * REFILL_THRESHOLD.
 */
अटल पूर्णांक dpaa_eth_refill_bpool(काष्ठा dpaa_bp *dpaa_bp, पूर्णांक *countptr)
अणु
	पूर्णांक count = *countptr;
	पूर्णांक new_bufs;

	अगर (unlikely(count < FSL_DPAA_ETH_REFILL_THRESHOLD)) अणु
		करो अणु
			new_bufs = dpaa_bp_add_8_bufs(dpaa_bp);
			अगर (unlikely(!new_bufs)) अणु
				/* Aव्योम looping क्रमever अगर we've temporarily
				 * run out of memory. We'll try again at the
				 * next NAPI cycle.
				 */
				अवरोध;
			पूर्ण
			count += new_bufs;
		पूर्ण जबतक (count < FSL_DPAA_ETH_MAX_BUF_COUNT);

		*countptr = count;
		अगर (unlikely(count < FSL_DPAA_ETH_MAX_BUF_COUNT))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_eth_refill_bpools(काष्ठा dpaa_priv *priv)
अणु
	काष्ठा dpaa_bp *dpaa_bp;
	पूर्णांक *countptr;

	dpaa_bp = priv->dpaa_bp;
	अगर (!dpaa_bp)
		वापस -EINVAL;
	countptr = this_cpu_ptr(dpaa_bp->percpu_count);

	वापस dpaa_eth_refill_bpool(dpaa_bp, countptr);
पूर्ण

/* Cleanup function क्रम outgoing frame descriptors that were built on Tx path,
 * either contiguous frames or scatter/gather ones.
 * Skb मुक्तing is not handled here.
 *
 * This function may be called on error paths in the Tx function, so guard
 * against हालs when not all fd relevant fields were filled in. To aव्योम
 * पढ़ोing the invalid transmission बारtamp क्रम the error paths set ts to
 * false.
 *
 * Return the skb backpoपूर्णांकer, since क्रम S/G frames the buffer containing it
 * माला_लो मुक्तd here.
 *
 * No skb backpoपूर्णांकer is set when transmitting XDP frames. Cleanup the buffer
 * and वापस शून्य in this हाल.
 */
अटल काष्ठा sk_buff *dpaa_cleanup_tx_fd(स्थिर काष्ठा dpaa_priv *priv,
					  स्थिर काष्ठा qm_fd *fd, bool ts)
अणु
	स्थिर क्रमागत dma_data_direction dma_dir = DMA_TO_DEVICE;
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	dma_addr_t addr = qm_fd_addr(fd);
	व्योम *vaddr = phys_to_virt(addr);
	स्थिर काष्ठा qm_sg_entry *sgt;
	काष्ठा dpaa_eth_swbp *swbp;
	काष्ठा sk_buff *skb;
	u64 ns;
	पूर्णांक i;

	अगर (unlikely(qm_fd_get_क्रमmat(fd) == qm_fd_sg)) अणु
		dma_unmap_page(priv->tx_dma_dev, addr,
			       qm_fd_get_offset(fd) + DPAA_SGT_SIZE,
			       dma_dir);

		/* The sgt buffer has been allocated with netdev_alloc_frag(),
		 * it's from lowmem.
		 */
		sgt = vaddr + qm_fd_get_offset(fd);

		/* sgt[0] is from lowmem, was dma_map_single()-ed */
		dma_unmap_single(priv->tx_dma_dev, qm_sg_addr(&sgt[0]),
				 qm_sg_entry_get_len(&sgt[0]), dma_dir);

		/* reमुख्यing pages were mapped with skb_frag_dma_map() */
		क्रम (i = 1; (i < DPAA_SGT_MAX_ENTRIES) &&
		     !qm_sg_entry_is_final(&sgt[i - 1]); i++) अणु
			WARN_ON(qm_sg_entry_is_ext(&sgt[i]));

			dma_unmap_page(priv->tx_dma_dev, qm_sg_addr(&sgt[i]),
				       qm_sg_entry_get_len(&sgt[i]), dma_dir);
		पूर्ण
	पूर्ण अन्यथा अणु
		dma_unmap_single(priv->tx_dma_dev, addr,
				 qm_fd_get_offset(fd) + qm_fd_get_length(fd),
				 dma_dir);
	पूर्ण

	swbp = (काष्ठा dpaa_eth_swbp *)vaddr;
	skb = swbp->skb;

	/* No skb backpoपूर्णांकer is set when running XDP. An xdp_frame
	 * backpoपूर्णांकer is saved instead.
	 */
	अगर (!skb) अणु
		xdp_वापस_frame(swbp->xdpf);
		वापस शून्य;
	पूर्ण

	/* DMA unmapping is required beक्रमe accessing the HW provided info */
	अगर (ts && priv->tx_tstamp &&
	    skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) अणु
		स_रखो(&shhwtstamps, 0, माप(shhwtstamps));

		अगर (!fman_port_get_tstamp(priv->mac_dev->port[TX], vaddr,
					  &ns)) अणु
			shhwtstamps.hwtstamp = ns_to_kसमय(ns);
			skb_tstamp_tx(skb, &shhwtstamps);
		पूर्ण अन्यथा अणु
			dev_warn(dev, "fman_port_get_tstamp failed!\n");
		पूर्ण
	पूर्ण

	अगर (qm_fd_get_क्रमmat(fd) == qm_fd_sg)
		/* Free the page that we allocated on Tx क्रम the SGT */
		मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);

	वापस skb;
पूर्ण

अटल u8 rx_csum_offload(स्थिर काष्ठा dpaa_priv *priv, स्थिर काष्ठा qm_fd *fd)
अणु
	/* The parser has run and perक्रमmed L4 checksum validation.
	 * We know there were no parser errors (and implicitly no
	 * L4 csum error), otherwise we wouldn't be here.
	 */
	अगर ((priv->net_dev->features & NETIF_F_RXCSUM) &&
	    (be32_to_cpu(fd->status) & FM_FD_STAT_L4CV))
		वापस CHECKSUM_UNNECESSARY;

	/* We're here because either the parser didn't run or the L4 checksum
	 * was not verअगरied. This may include the हाल of a UDP frame with
	 * checksum zero or an L4 proto other than TCP/UDP
	 */
	वापस CHECKSUM_NONE;
पूर्ण

#घोषणा PTR_IS_ALIGNED(x, a) (IS_ALIGNED((अचिन्हित दीर्घ)(x), (a)))

/* Build a linear skb around the received buffer.
 * We are guaranteed there is enough room at the end of the data buffer to
 * accommodate the shared info area of the skb.
 */
अटल काष्ठा sk_buff *contig_fd_to_skb(स्थिर काष्ठा dpaa_priv *priv,
					स्थिर काष्ठा qm_fd *fd)
अणु
	sमाप_प्रकार fd_off = qm_fd_get_offset(fd);
	dma_addr_t addr = qm_fd_addr(fd);
	काष्ठा dpaa_bp *dpaa_bp;
	काष्ठा sk_buff *skb;
	व्योम *vaddr;

	vaddr = phys_to_virt(addr);
	WARN_ON(!IS_ALIGNED((अचिन्हित दीर्घ)vaddr, SMP_CACHE_BYTES));

	dpaa_bp = dpaa_bpid2pool(fd->bpid);
	अगर (!dpaa_bp)
		जाओ मुक्त_buffer;

	skb = build_skb(vaddr, dpaa_bp->size +
			SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)));
	अगर (WARN_ONCE(!skb, "Build skb failure on Rx\n"))
		जाओ मुक्त_buffer;
	skb_reserve(skb, fd_off);
	skb_put(skb, qm_fd_get_length(fd));

	skb->ip_summed = rx_csum_offload(priv, fd);

	वापस skb;

मुक्त_buffer:
	मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
	वापस शून्य;
पूर्ण

/* Build an skb with the data of the first S/G entry in the linear portion and
 * the rest of the frame as skb fragments.
 *
 * The page fragment holding the S/G Table is recycled here.
 */
अटल काष्ठा sk_buff *sg_fd_to_skb(स्थिर काष्ठा dpaa_priv *priv,
				    स्थिर काष्ठा qm_fd *fd)
अणु
	sमाप_प्रकार fd_off = qm_fd_get_offset(fd);
	dma_addr_t addr = qm_fd_addr(fd);
	स्थिर काष्ठा qm_sg_entry *sgt;
	काष्ठा page *page, *head_page;
	काष्ठा dpaa_bp *dpaa_bp;
	व्योम *vaddr, *sg_vaddr;
	पूर्णांक frag_off, frag_len;
	काष्ठा sk_buff *skb;
	dma_addr_t sg_addr;
	पूर्णांक page_offset;
	अचिन्हित पूर्णांक sz;
	पूर्णांक *count_ptr;
	पूर्णांक i, j;

	vaddr = phys_to_virt(addr);
	WARN_ON(!IS_ALIGNED((अचिन्हित दीर्घ)vaddr, SMP_CACHE_BYTES));

	/* Iterate through the SGT entries and add data buffers to the skb */
	sgt = vaddr + fd_off;
	skb = शून्य;
	क्रम (i = 0; i < DPAA_SGT_MAX_ENTRIES; i++) अणु
		/* Extension bit is not supported */
		WARN_ON(qm_sg_entry_is_ext(&sgt[i]));

		sg_addr = qm_sg_addr(&sgt[i]);
		sg_vaddr = phys_to_virt(sg_addr);
		WARN_ON(!PTR_IS_ALIGNED(sg_vaddr, SMP_CACHE_BYTES));

		dma_unmap_page(priv->rx_dma_dev, sg_addr,
			       DPAA_BP_RAW_SIZE, DMA_FROM_DEVICE);

		/* We may use multiple Rx pools */
		dpaa_bp = dpaa_bpid2pool(sgt[i].bpid);
		अगर (!dpaa_bp)
			जाओ मुक्त_buffers;

		अगर (!skb) अणु
			sz = dpaa_bp->size +
				SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
			skb = build_skb(sg_vaddr, sz);
			अगर (WARN_ON(!skb))
				जाओ मुक्त_buffers;

			skb->ip_summed = rx_csum_offload(priv, fd);

			/* Make sure क्रमwarded skbs will have enough space
			 * on Tx, अगर extra headers are added.
			 */
			WARN_ON(fd_off != priv->rx_headroom);
			skb_reserve(skb, fd_off);
			skb_put(skb, qm_sg_entry_get_len(&sgt[i]));
		पूर्ण अन्यथा अणु
			/* Not the first S/G entry; all data from buffer will
			 * be added in an skb fragment; fragment index is offset
			 * by one since first S/G entry was incorporated in the
			 * linear part of the skb.
			 *
			 * Caution: 'page' may be a tail page.
			 */
			page = virt_to_page(sg_vaddr);
			head_page = virt_to_head_page(sg_vaddr);

			/* Compute offset in (possibly tail) page */
			page_offset = ((अचिन्हित दीर्घ)sg_vaddr &
					(PAGE_SIZE - 1)) +
				(page_address(page) - page_address(head_page));
			/* page_offset only refers to the beginning of sgt[i];
			 * but the buffer itself may have an पूर्णांकernal offset.
			 */
			frag_off = qm_sg_entry_get_off(&sgt[i]) + page_offset;
			frag_len = qm_sg_entry_get_len(&sgt[i]);
			/* skb_add_rx_frag() करोes no checking on the page; अगर
			 * we pass it a tail page, we'll end up with
			 * bad page accounting and eventually with segafults.
			 */
			skb_add_rx_frag(skb, i - 1, head_page, frag_off,
					frag_len, dpaa_bp->size);
		पूर्ण

		/* Update the pool count क्रम the current अणुcpu x bpoolपूर्ण */
		count_ptr = this_cpu_ptr(dpaa_bp->percpu_count);
		(*count_ptr)--;

		अगर (qm_sg_entry_is_final(&sgt[i]))
			अवरोध;
	पूर्ण
	WARN_ONCE(i == DPAA_SGT_MAX_ENTRIES, "No final bit on SGT\n");

	/* मुक्त the SG table buffer */
	मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);

	वापस skb;

मुक्त_buffers:
	/* मुक्त all the SG entries */
	क्रम (j = 0; j < DPAA_SGT_MAX_ENTRIES ; j++) अणु
		sg_addr = qm_sg_addr(&sgt[j]);
		sg_vaddr = phys_to_virt(sg_addr);
		/* all pages 0..i were unmaped */
		अगर (j > i)
			dma_unmap_page(priv->rx_dma_dev, qm_sg_addr(&sgt[j]),
				       DPAA_BP_RAW_SIZE, DMA_FROM_DEVICE);
		मुक्त_pages((अचिन्हित दीर्घ)sg_vaddr, 0);
		/* counters 0..i-1 were decremented */
		अगर (j >= i) अणु
			dpaa_bp = dpaa_bpid2pool(sgt[j].bpid);
			अगर (dpaa_bp) अणु
				count_ptr = this_cpu_ptr(dpaa_bp->percpu_count);
				(*count_ptr)--;
			पूर्ण
		पूर्ण

		अगर (qm_sg_entry_is_final(&sgt[j]))
			अवरोध;
	पूर्ण
	/* मुक्त the SGT fragment */
	मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);

	वापस शून्य;
पूर्ण

अटल पूर्णांक skb_to_contig_fd(काष्ठा dpaa_priv *priv,
			    काष्ठा sk_buff *skb, काष्ठा qm_fd *fd,
			    पूर्णांक *offset)
अणु
	काष्ठा net_device *net_dev = priv->net_dev;
	क्रमागत dma_data_direction dma_dir;
	काष्ठा dpaa_eth_swbp *swbp;
	अचिन्हित अक्षर *buff_start;
	dma_addr_t addr;
	पूर्णांक err;

	/* We are guaranteed to have at least tx_headroom bytes
	 * available, so just use that क्रम offset.
	 */
	fd->bpid = FSL_DPAA_BPID_INV;
	buff_start = skb->data - priv->tx_headroom;
	dma_dir = DMA_TO_DEVICE;

	swbp = (काष्ठा dpaa_eth_swbp *)buff_start;
	swbp->skb = skb;

	/* Enable L3/L4 hardware checksum computation.
	 *
	 * We must करो this beक्रमe dma_map_single(DMA_TO_DEVICE), because we may
	 * need to ग_लिखो पूर्णांकo the skb.
	 */
	err = dpaa_enable_tx_csum(priv, skb, fd,
				  buff_start + DPAA_TX_PRIV_DATA_SIZE);
	अगर (unlikely(err < 0)) अणु
		अगर (net_ratelimit())
			netअगर_err(priv, tx_err, net_dev, "HW csum error: %d\n",
				  err);
		वापस err;
	पूर्ण

	/* Fill in the rest of the FD fields */
	qm_fd_set_contig(fd, priv->tx_headroom, skb->len);
	fd->cmd |= cpu_to_be32(FM_FD_CMD_FCO);

	/* Map the entire buffer size that may be seen by FMan, but no more */
	addr = dma_map_single(priv->tx_dma_dev, buff_start,
			      priv->tx_headroom + skb->len, dma_dir);
	अगर (unlikely(dma_mapping_error(priv->tx_dma_dev, addr))) अणु
		अगर (net_ratelimit())
			netअगर_err(priv, tx_err, net_dev, "dma_map_single() failed\n");
		वापस -EINVAL;
	पूर्ण
	qm_fd_addr_set64(fd, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक skb_to_sg_fd(काष्ठा dpaa_priv *priv,
			काष्ठा sk_buff *skb, काष्ठा qm_fd *fd)
अणु
	स्थिर क्रमागत dma_data_direction dma_dir = DMA_TO_DEVICE;
	स्थिर पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	काष्ठा net_device *net_dev = priv->net_dev;
	काष्ठा dpaa_eth_swbp *swbp;
	काष्ठा qm_sg_entry *sgt;
	व्योम *buff_start;
	skb_frag_t *frag;
	dma_addr_t addr;
	माप_प्रकार frag_len;
	काष्ठा page *p;
	पूर्णांक i, j, err;

	/* get a page to store the SGTable */
	p = dev_alloc_pages(0);
	अगर (unlikely(!p)) अणु
		netdev_err(net_dev, "dev_alloc_pages() failed\n");
		वापस -ENOMEM;
	पूर्ण
	buff_start = page_address(p);

	/* Enable L3/L4 hardware checksum computation.
	 *
	 * We must करो this beक्रमe dma_map_single(DMA_TO_DEVICE), because we may
	 * need to ग_लिखो पूर्णांकo the skb.
	 */
	err = dpaa_enable_tx_csum(priv, skb, fd,
				  buff_start + DPAA_TX_PRIV_DATA_SIZE);
	अगर (unlikely(err < 0)) अणु
		अगर (net_ratelimit())
			netअगर_err(priv, tx_err, net_dev, "HW csum error: %d\n",
				  err);
		जाओ csum_failed;
	पूर्ण

	/* SGT[0] is used by the linear part */
	sgt = (काष्ठा qm_sg_entry *)(buff_start + priv->tx_headroom);
	frag_len = skb_headlen(skb);
	qm_sg_entry_set_len(&sgt[0], frag_len);
	sgt[0].bpid = FSL_DPAA_BPID_INV;
	sgt[0].offset = 0;
	addr = dma_map_single(priv->tx_dma_dev, skb->data,
			      skb_headlen(skb), dma_dir);
	अगर (unlikely(dma_mapping_error(priv->tx_dma_dev, addr))) अणु
		netdev_err(priv->net_dev, "DMA mapping failed\n");
		err = -EINVAL;
		जाओ sg0_map_failed;
	पूर्ण
	qm_sg_entry_set64(&sgt[0], addr);

	/* populate the rest of SGT entries */
	क्रम (i = 0; i < nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		frag_len = skb_frag_size(frag);
		WARN_ON(!skb_frag_page(frag));
		addr = skb_frag_dma_map(priv->tx_dma_dev, frag, 0,
					frag_len, dma_dir);
		अगर (unlikely(dma_mapping_error(priv->tx_dma_dev, addr))) अणु
			netdev_err(priv->net_dev, "DMA mapping failed\n");
			err = -EINVAL;
			जाओ sg_map_failed;
		पूर्ण

		qm_sg_entry_set_len(&sgt[i + 1], frag_len);
		sgt[i + 1].bpid = FSL_DPAA_BPID_INV;
		sgt[i + 1].offset = 0;

		/* keep the offset in the address */
		qm_sg_entry_set64(&sgt[i + 1], addr);
	पूर्ण

	/* Set the final bit in the last used entry of the SGT */
	qm_sg_entry_set_f(&sgt[nr_frags], frag_len);

	/* set fd offset to priv->tx_headroom */
	qm_fd_set_sg(fd, priv->tx_headroom, skb->len);

	/* DMA map the SGT page */
	swbp = (काष्ठा dpaa_eth_swbp *)buff_start;
	swbp->skb = skb;

	addr = dma_map_page(priv->tx_dma_dev, p, 0,
			    priv->tx_headroom + DPAA_SGT_SIZE, dma_dir);
	अगर (unlikely(dma_mapping_error(priv->tx_dma_dev, addr))) अणु
		netdev_err(priv->net_dev, "DMA mapping failed\n");
		err = -EINVAL;
		जाओ sgt_map_failed;
	पूर्ण

	fd->bpid = FSL_DPAA_BPID_INV;
	fd->cmd |= cpu_to_be32(FM_FD_CMD_FCO);
	qm_fd_addr_set64(fd, addr);

	वापस 0;

sgt_map_failed:
sg_map_failed:
	क्रम (j = 0; j < i; j++)
		dma_unmap_page(priv->tx_dma_dev, qm_sg_addr(&sgt[j]),
			       qm_sg_entry_get_len(&sgt[j]), dma_dir);
sg0_map_failed:
csum_failed:
	मुक्त_pages((अचिन्हित दीर्घ)buff_start, 0);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक dpaa_xmit(काष्ठा dpaa_priv *priv,
			    काष्ठा rtnl_link_stats64 *percpu_stats,
			    पूर्णांक queue,
			    काष्ठा qm_fd *fd)
अणु
	काष्ठा qman_fq *egress_fq;
	पूर्णांक err, i;

	egress_fq = priv->egress_fqs[queue];
	अगर (fd->bpid == FSL_DPAA_BPID_INV)
		fd->cmd |= cpu_to_be32(qman_fq_fqid(priv->conf_fqs[queue]));

	/* Trace this Tx fd */
	trace_dpaa_tx_fd(priv->net_dev, egress_fq, fd);

	क्रम (i = 0; i < DPAA_ENQUEUE_RETRIES; i++) अणु
		err = qman_enqueue(egress_fq, fd);
		अगर (err != -EBUSY)
			अवरोध;
	पूर्ण

	अगर (unlikely(err < 0)) अणु
		percpu_stats->tx_fअगरo_errors++;
		वापस err;
	पूर्ण

	percpu_stats->tx_packets++;
	percpu_stats->tx_bytes += qm_fd_get_length(fd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
अटल पूर्णांक dpaa_a050385_wa_skb(काष्ठा net_device *net_dev, काष्ठा sk_buff **s)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);
	काष्ठा sk_buff *new_skb, *skb = *s;
	अचिन्हित अक्षर *start, i;

	/* check linear buffer alignment */
	अगर (!PTR_IS_ALIGNED(skb->data, DPAA_A050385_ALIGN))
		जाओ workaround;

	/* linear buffers just need to have an aligned start */
	अगर (!skb_is_nonlinear(skb))
		वापस 0;

	/* linear data size क्रम nonlinear skbs needs to be aligned */
	अगर (!IS_ALIGNED(skb_headlen(skb), DPAA_A050385_ALIGN))
		जाओ workaround;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		/* all fragments need to have aligned start addresses */
		अगर (!IS_ALIGNED(skb_frag_off(frag), DPAA_A050385_ALIGN))
			जाओ workaround;

		/* all but last fragment need to have aligned sizes */
		अगर (!IS_ALIGNED(skb_frag_size(frag), DPAA_A050385_ALIGN) &&
		    (i < skb_shinfo(skb)->nr_frags - 1))
			जाओ workaround;
	पूर्ण

	वापस 0;

workaround:
	/* copy all the skb content पूर्णांकo a new linear buffer */
	new_skb = netdev_alloc_skb(net_dev, skb->len + DPAA_A050385_ALIGN - 1 +
						priv->tx_headroom);
	अगर (!new_skb)
		वापस -ENOMEM;

	/* NET_SKB_PAD bytes alपढ़ोy reserved, adding up to tx_headroom */
	skb_reserve(new_skb, priv->tx_headroom - NET_SKB_PAD);

	/* Workaround क्रम DPAA_A050385 requires data start to be aligned */
	start = PTR_ALIGN(new_skb->data, DPAA_A050385_ALIGN);
	अगर (start - new_skb->data)
		skb_reserve(new_skb, start - new_skb->data);

	skb_put(new_skb, skb->len);
	skb_copy_bits(skb, 0, new_skb->data, skb->len);
	skb_copy_header(new_skb, skb);
	new_skb->dev = skb->dev;

	/* Copy relevant बारtamp info from the old skb to the new */
	अगर (priv->tx_tstamp) अणु
		skb_shinfo(new_skb)->tx_flags = skb_shinfo(skb)->tx_flags;
		skb_shinfo(new_skb)->hwtstamps = skb_shinfo(skb)->hwtstamps;
		skb_shinfo(new_skb)->tskey = skb_shinfo(skb)->tskey;
		अगर (skb->sk)
			skb_set_owner_w(new_skb, skb->sk);
	पूर्ण

	/* We move the headroom when we align it so we have to reset the
	 * network and transport header offsets relative to the new data
	 * poपूर्णांकer. The checksum offload relies on these offsets.
	 */
	skb_set_network_header(new_skb, skb_network_offset(skb));
	skb_set_transport_header(new_skb, skb_transport_offset(skb));

	dev_kमुक्त_skb(skb);
	*s = new_skb;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_a050385_wa_xdpf(काष्ठा dpaa_priv *priv,
				काष्ठा xdp_frame **init_xdpf)
अणु
	काष्ठा xdp_frame *new_xdpf, *xdpf = *init_xdpf;
	व्योम *new_buff, *aligned_data;
	काष्ठा page *p;
	u32 data_shअगरt;
	पूर्णांक headroom;

	/* Check the data alignment and make sure the headroom is large
	 * enough to store the xdpf backpoपूर्णांकer. Use an aligned headroom
	 * value.
	 *
	 * Due to alignment स्थिरraपूर्णांकs, we give XDP access to the full 256
	 * byte frame headroom. If the XDP program uses all of it, copy the
	 * data to a new buffer and make room क्रम storing the backpoपूर्णांकer.
	 */
	अगर (PTR_IS_ALIGNED(xdpf->data, DPAA_FD_DATA_ALIGNMENT) &&
	    xdpf->headroom >= priv->tx_headroom) अणु
		xdpf->headroom = priv->tx_headroom;
		वापस 0;
	पूर्ण

	/* Try to move the data inside the buffer just enough to align it and
	 * store the xdpf backpoपूर्णांकer. If the available headroom isn't large
	 * enough, resort to allocating a new buffer and copying the data.
	 */
	aligned_data = PTR_ALIGN_DOWN(xdpf->data, DPAA_FD_DATA_ALIGNMENT);
	data_shअगरt = xdpf->data - aligned_data;

	/* The XDP frame's headroom needs to be large enough to accommodate
	 * shअगरting the data as well as storing the xdpf backpoपूर्णांकer.
	 */
	अगर (xdpf->headroom  >= data_shअगरt + priv->tx_headroom) अणु
		स_हटाओ(aligned_data, xdpf->data, xdpf->len);
		xdpf->data = aligned_data;
		xdpf->headroom = priv->tx_headroom;
		वापस 0;
	पूर्ण

	/* The new xdp_frame is stored in the new buffer. Reserve enough space
	 * in the headroom क्रम storing it aदीर्घ with the driver's निजी
	 * info. The headroom needs to be aligned to DPAA_FD_DATA_ALIGNMENT to
	 * guarantee the data's alignment in the buffer.
	 */
	headroom = ALIGN(माप(*new_xdpf) + priv->tx_headroom,
			 DPAA_FD_DATA_ALIGNMENT);

	/* Assure the extended headroom and data करोn't overflow the buffer,
	 * जबतक मुख्यtaining the mandatory tailroom.
	 */
	अगर (headroom + xdpf->len > DPAA_BP_RAW_SIZE -
			SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))
		वापस -ENOMEM;

	p = dev_alloc_pages(0);
	अगर (unlikely(!p))
		वापस -ENOMEM;

	/* Copy the data to the new buffer at a properly aligned offset */
	new_buff = page_address(p);
	स_नकल(new_buff + headroom, xdpf->data, xdpf->len);

	/* Create an XDP frame around the new buffer in a similar fashion
	 * to xdp_convert_buff_to_frame.
	 */
	new_xdpf = new_buff;
	new_xdpf->data = new_buff + headroom;
	new_xdpf->len = xdpf->len;
	new_xdpf->headroom = priv->tx_headroom;
	new_xdpf->frame_sz = DPAA_BP_RAW_SIZE;
	new_xdpf->mem.type = MEM_TYPE_PAGE_ORDER0;

	/* Release the initial buffer */
	xdp_वापस_frame_rx_napi(xdpf);

	*init_xdpf = new_xdpf;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल netdev_tx_t
dpaa_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *net_dev)
अणु
	स्थिर पूर्णांक queue_mapping = skb_get_queue_mapping(skb);
	bool nonlinear = skb_is_nonlinear(skb);
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa_percpu_priv *percpu_priv;
	काष्ठा netdev_queue *txq;
	काष्ठा dpaa_priv *priv;
	काष्ठा qm_fd fd;
	पूर्णांक offset = 0;
	पूर्णांक err = 0;

	priv = netdev_priv(net_dev);
	percpu_priv = this_cpu_ptr(priv->percpu_priv);
	percpu_stats = &percpu_priv->stats;

	qm_fd_clear_fd(&fd);

	अगर (!nonlinear) अणु
		/* We're going to store the skb backpoपूर्णांकer at the beginning
		 * of the data buffer, so we need a निजीly owned skb
		 *
		 * We've made sure skb is not shared in dev->priv_flags,
		 * we need to verअगरy the skb head is not cloned
		 */
		अगर (skb_cow_head(skb, priv->tx_headroom))
			जाओ enomem;

		WARN_ON(skb_is_nonlinear(skb));
	पूर्ण

	/* MAX_SKB_FRAGS is equal or larger than our dpaa_SGT_MAX_ENTRIES;
	 * make sure we करोn't feed FMan with more fragments than it supports.
	 */
	अगर (unlikely(nonlinear &&
		     (skb_shinfo(skb)->nr_frags >= DPAA_SGT_MAX_ENTRIES))) अणु
		/* If the egress skb contains more fragments than we support
		 * we have no choice but to linearize it ourselves.
		 */
		अगर (__skb_linearize(skb))
			जाओ enomem;

		nonlinear = skb_is_nonlinear(skb);
	पूर्ण

#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
	अगर (unlikely(fman_has_errata_a050385())) अणु
		अगर (dpaa_a050385_wa_skb(net_dev, &skb))
			जाओ enomem;
		nonlinear = skb_is_nonlinear(skb);
	पूर्ण
#पूर्ण_अगर

	अगर (nonlinear) अणु
		/* Just create a S/G fd based on the skb */
		err = skb_to_sg_fd(priv, skb, &fd);
		percpu_priv->tx_frag_skbuffs++;
	पूर्ण अन्यथा अणु
		/* Create a contig FD from this skb */
		err = skb_to_contig_fd(priv, skb, &fd, &offset);
	पूर्ण
	अगर (unlikely(err < 0))
		जाओ skb_to_fd_failed;

	txq = netdev_get_tx_queue(net_dev, queue_mapping);

	/* LLTX requires to करो our own update of trans_start */
	txq->trans_start = jअगरfies;

	अगर (priv->tx_tstamp && skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) अणु
		fd.cmd |= cpu_to_be32(FM_FD_CMD_UPD);
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
	पूर्ण

	अगर (likely(dpaa_xmit(priv, percpu_stats, queue_mapping, &fd) == 0))
		वापस NETDEV_TX_OK;

	dpaa_cleanup_tx_fd(priv, &fd, false);
skb_to_fd_failed:
enomem:
	percpu_stats->tx_errors++;
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम dpaa_rx_error(काष्ठा net_device *net_dev,
			  स्थिर काष्ठा dpaa_priv *priv,
			  काष्ठा dpaa_percpu_priv *percpu_priv,
			  स्थिर काष्ठा qm_fd *fd,
			  u32 fqid)
अणु
	अगर (net_ratelimit())
		netअगर_err(priv, hw, net_dev, "Err FD status = 0x%08x\n",
			  be32_to_cpu(fd->status) & FM_FD_STAT_RX_ERRORS);

	percpu_priv->stats.rx_errors++;

	अगर (be32_to_cpu(fd->status) & FM_FD_ERR_DMA)
		percpu_priv->rx_errors.dme++;
	अगर (be32_to_cpu(fd->status) & FM_FD_ERR_PHYSICAL)
		percpu_priv->rx_errors.fpe++;
	अगर (be32_to_cpu(fd->status) & FM_FD_ERR_SIZE)
		percpu_priv->rx_errors.fse++;
	अगर (be32_to_cpu(fd->status) & FM_FD_ERR_PRS_HDR_ERR)
		percpu_priv->rx_errors.phe++;

	dpaa_fd_release(net_dev, fd);
पूर्ण

अटल व्योम dpaa_tx_error(काष्ठा net_device *net_dev,
			  स्थिर काष्ठा dpaa_priv *priv,
			  काष्ठा dpaa_percpu_priv *percpu_priv,
			  स्थिर काष्ठा qm_fd *fd,
			  u32 fqid)
अणु
	काष्ठा sk_buff *skb;

	अगर (net_ratelimit())
		netअगर_warn(priv, hw, net_dev, "FD status = 0x%08x\n",
			   be32_to_cpu(fd->status) & FM_FD_STAT_TX_ERRORS);

	percpu_priv->stats.tx_errors++;

	skb = dpaa_cleanup_tx_fd(priv, fd, false);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक dpaa_eth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा dpaa_napi_portal *np =
			container_of(napi, काष्ठा dpaa_napi_portal, napi);
	पूर्णांक cleaned;

	np->xdp_act = 0;

	cleaned = qman_p_poll_dqrr(np->p, budget);

	अगर (cleaned < budget) अणु
		napi_complete_करोne(napi, cleaned);
		qman_p_irqsource_add(np->p, QM_PIRQ_DQRI);
	पूर्ण अन्यथा अगर (np->करोwn) अणु
		qman_p_irqsource_add(np->p, QM_PIRQ_DQRI);
	पूर्ण

	अगर (np->xdp_act & XDP_REसूचीECT)
		xdp_करो_flush();

	वापस cleaned;
पूर्ण

अटल व्योम dpaa_tx_conf(काष्ठा net_device *net_dev,
			 स्थिर काष्ठा dpaa_priv *priv,
			 काष्ठा dpaa_percpu_priv *percpu_priv,
			 स्थिर काष्ठा qm_fd *fd,
			 u32 fqid)
अणु
	काष्ठा sk_buff	*skb;

	अगर (unlikely(be32_to_cpu(fd->status) & FM_FD_STAT_TX_ERRORS)) अणु
		अगर (net_ratelimit())
			netअगर_warn(priv, hw, net_dev, "FD status = 0x%08x\n",
				   be32_to_cpu(fd->status) &
				   FM_FD_STAT_TX_ERRORS);

		percpu_priv->stats.tx_errors++;
	पूर्ण

	percpu_priv->tx_confirm++;

	skb = dpaa_cleanup_tx_fd(priv, fd, true);

	consume_skb(skb);
पूर्ण

अटल अंतरभूत पूर्णांक dpaa_eth_napi_schedule(काष्ठा dpaa_percpu_priv *percpu_priv,
					 काष्ठा qman_portal *portal, bool sched_napi)
अणु
	अगर (sched_napi) अणु
		/* Disable QMan IRQ and invoke NAPI */
		qman_p_irqsource_हटाओ(portal, QM_PIRQ_DQRI);

		percpu_priv->np.p = portal;
		napi_schedule(&percpu_priv->np.napi);
		percpu_priv->in_पूर्णांकerrupt++;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत qman_cb_dqrr_result rx_error_dqrr(काष्ठा qman_portal *portal,
					      काष्ठा qman_fq *fq,
					      स्थिर काष्ठा qm_dqrr_entry *dq,
					      bool sched_napi)
अणु
	काष्ठा dpaa_fq *dpaa_fq = container_of(fq, काष्ठा dpaa_fq, fq_base);
	काष्ठा dpaa_percpu_priv *percpu_priv;
	काष्ठा net_device *net_dev;
	काष्ठा dpaa_bp *dpaa_bp;
	काष्ठा dpaa_priv *priv;

	net_dev = dpaa_fq->net_dev;
	priv = netdev_priv(net_dev);
	dpaa_bp = dpaa_bpid2pool(dq->fd.bpid);
	अगर (!dpaa_bp)
		वापस qman_cb_dqrr_consume;

	percpu_priv = this_cpu_ptr(priv->percpu_priv);

	अगर (dpaa_eth_napi_schedule(percpu_priv, portal, sched_napi))
		वापस qman_cb_dqrr_stop;

	dpaa_eth_refill_bpools(priv);
	dpaa_rx_error(net_dev, priv, percpu_priv, &dq->fd, fq->fqid);

	वापस qman_cb_dqrr_consume;
पूर्ण

अटल पूर्णांक dpaa_xdp_xmit_frame(काष्ठा net_device *net_dev,
			       काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa_percpu_priv *percpu_priv;
	काष्ठा dpaa_eth_swbp *swbp;
	काष्ठा netdev_queue *txq;
	व्योम *buff_start;
	काष्ठा qm_fd fd;
	dma_addr_t addr;
	पूर्णांक err;

	percpu_priv = this_cpu_ptr(priv->percpu_priv);
	percpu_stats = &percpu_priv->stats;

#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
	अगर (unlikely(fman_has_errata_a050385())) अणु
		अगर (dpaa_a050385_wa_xdpf(priv, &xdpf)) अणु
			err = -ENOMEM;
			जाओ out_error;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (xdpf->headroom < DPAA_TX_PRIV_DATA_SIZE) अणु
		err = -EINVAL;
		जाओ out_error;
	पूर्ण

	buff_start = xdpf->data - xdpf->headroom;

	/* Leave empty the skb backpoपूर्णांकer at the start of the buffer.
	 * Save the XDP frame क्रम easy cleanup on confirmation.
	 */
	swbp = (काष्ठा dpaa_eth_swbp *)buff_start;
	swbp->skb = शून्य;
	swbp->xdpf = xdpf;

	qm_fd_clear_fd(&fd);
	fd.bpid = FSL_DPAA_BPID_INV;
	fd.cmd |= cpu_to_be32(FM_FD_CMD_FCO);
	qm_fd_set_contig(&fd, xdpf->headroom, xdpf->len);

	addr = dma_map_single(priv->tx_dma_dev, buff_start,
			      xdpf->headroom + xdpf->len,
			      DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(priv->tx_dma_dev, addr))) अणु
		err = -EINVAL;
		जाओ out_error;
	पूर्ण

	qm_fd_addr_set64(&fd, addr);

	/* Bump the trans_start */
	txq = netdev_get_tx_queue(net_dev, smp_processor_id());
	txq->trans_start = jअगरfies;

	err = dpaa_xmit(priv, percpu_stats, smp_processor_id(), &fd);
	अगर (err) अणु
		dma_unmap_single(priv->tx_dma_dev, addr,
				 qm_fd_get_offset(&fd) + qm_fd_get_length(&fd),
				 DMA_TO_DEVICE);
		जाओ out_error;
	पूर्ण

	वापस 0;

out_error:
	percpu_stats->tx_errors++;
	वापस err;
पूर्ण

अटल u32 dpaa_run_xdp(काष्ठा dpaa_priv *priv, काष्ठा qm_fd *fd, व्योम *vaddr,
			काष्ठा dpaa_fq *dpaa_fq, अचिन्हित पूर्णांक *xdp_meta_len)
अणु
	sमाप_प्रकार fd_off = qm_fd_get_offset(fd);
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xdp_frame *xdpf;
	काष्ठा xdp_buff xdp;
	u32 xdp_act;
	पूर्णांक err;

	rcu_पढ़ो_lock();

	xdp_prog = READ_ONCE(priv->xdp_prog);
	अगर (!xdp_prog) अणु
		rcu_पढ़ो_unlock();
		वापस XDP_PASS;
	पूर्ण

	xdp_init_buff(&xdp, DPAA_BP_RAW_SIZE - DPAA_TX_PRIV_DATA_SIZE,
		      &dpaa_fq->xdp_rxq);
	xdp_prepare_buff(&xdp, vaddr + fd_off - XDP_PACKET_HEADROOM,
			 XDP_PACKET_HEADROOM, qm_fd_get_length(fd), true);

	/* We reserve a fixed headroom of 256 bytes under the erratum and we
	 * offer it all to XDP programs to use. If no room is left क्रम the
	 * xdpf backpoपूर्णांकer on TX, we will need to copy the data.
	 * Disable metadata support since data realignments might be required
	 * and the inक्रमmation can be lost.
	 */
#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
	अगर (unlikely(fman_has_errata_a050385())) अणु
		xdp_set_data_meta_invalid(&xdp);
		xdp.data_hard_start = vaddr;
		xdp.frame_sz = DPAA_BP_RAW_SIZE;
	पूर्ण
#पूर्ण_अगर

	xdp_act = bpf_prog_run_xdp(xdp_prog, &xdp);

	/* Update the length and the offset of the FD */
	qm_fd_set_contig(fd, xdp.data - vaddr, xdp.data_end - xdp.data);

	चयन (xdp_act) अणु
	हाल XDP_PASS:
#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
		*xdp_meta_len = xdp_data_meta_unsupported(&xdp) ? 0 :
				xdp.data - xdp.data_meta;
#अन्यथा
		*xdp_meta_len = xdp.data - xdp.data_meta;
#पूर्ण_अगर
		अवरोध;
	हाल XDP_TX:
		/* We can access the full headroom when sending the frame
		 * back out
		 */
		xdp.data_hard_start = vaddr;
		xdp.frame_sz = DPAA_BP_RAW_SIZE;
		xdpf = xdp_convert_buff_to_frame(&xdp);
		अगर (unlikely(!xdpf)) अणु
			मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
			अवरोध;
		पूर्ण

		अगर (dpaa_xdp_xmit_frame(priv->net_dev, xdpf))
			xdp_वापस_frame_rx_napi(xdpf);

		अवरोध;
	हाल XDP_REसूचीECT:
		/* Allow redirect to use the full headroom */
		xdp.data_hard_start = vaddr;
		xdp.frame_sz = DPAA_BP_RAW_SIZE;

		err = xdp_करो_redirect(priv->net_dev, &xdp, xdp_prog);
		अगर (err) अणु
			trace_xdp_exception(priv->net_dev, xdp_prog, xdp_act);
			मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
		पूर्ण
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(xdp_act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(priv->net_dev, xdp_prog, xdp_act);
		fallthrough;
	हाल XDP_DROP:
		/* Free the buffer */
		मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
		अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस xdp_act;
पूर्ण

अटल क्रमागत qman_cb_dqrr_result rx_शेष_dqrr(काष्ठा qman_portal *portal,
						काष्ठा qman_fq *fq,
						स्थिर काष्ठा qm_dqrr_entry *dq,
						bool sched_napi)
अणु
	bool ts_valid = false, hash_valid = false;
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	अचिन्हित पूर्णांक skb_len, xdp_meta_len = 0;
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa_percpu_priv *percpu_priv;
	स्थिर काष्ठा qm_fd *fd = &dq->fd;
	dma_addr_t addr = qm_fd_addr(fd);
	काष्ठा dpaa_napi_portal *np;
	क्रमागत qm_fd_क्रमmat fd_क्रमmat;
	काष्ठा net_device *net_dev;
	u32 fd_status, hash_offset;
	काष्ठा qm_sg_entry *sgt;
	काष्ठा dpaa_bp *dpaa_bp;
	काष्ठा dpaa_fq *dpaa_fq;
	काष्ठा dpaa_priv *priv;
	काष्ठा sk_buff *skb;
	पूर्णांक *count_ptr;
	u32 xdp_act;
	व्योम *vaddr;
	u32 hash;
	u64 ns;

	dpaa_fq = container_of(fq, काष्ठा dpaa_fq, fq_base);
	fd_status = be32_to_cpu(fd->status);
	fd_क्रमmat = qm_fd_get_क्रमmat(fd);
	net_dev = dpaa_fq->net_dev;
	priv = netdev_priv(net_dev);
	dpaa_bp = dpaa_bpid2pool(dq->fd.bpid);
	अगर (!dpaa_bp)
		वापस qman_cb_dqrr_consume;

	/* Trace the Rx fd */
	trace_dpaa_rx_fd(net_dev, fq, &dq->fd);

	percpu_priv = this_cpu_ptr(priv->percpu_priv);
	percpu_stats = &percpu_priv->stats;
	np = &percpu_priv->np;

	अगर (unlikely(dpaa_eth_napi_schedule(percpu_priv, portal, sched_napi)))
		वापस qman_cb_dqrr_stop;

	/* Make sure we didn't run out of buffers */
	अगर (unlikely(dpaa_eth_refill_bpools(priv))) अणु
		/* Unable to refill the buffer pool due to insufficient
		 * प्रणाली memory. Just release the frame back पूर्णांकo the pool,
		 * otherwise we'll soon end up with an empty buffer pool.
		 */
		dpaa_fd_release(net_dev, &dq->fd);
		वापस qman_cb_dqrr_consume;
	पूर्ण

	अगर (unlikely(fd_status & FM_FD_STAT_RX_ERRORS) != 0) अणु
		अगर (net_ratelimit())
			netअगर_warn(priv, hw, net_dev, "FD status = 0x%08x\n",
				   fd_status & FM_FD_STAT_RX_ERRORS);

		percpu_stats->rx_errors++;
		dpaa_fd_release(net_dev, fd);
		वापस qman_cb_dqrr_consume;
	पूर्ण

	dma_unmap_page(dpaa_bp->priv->rx_dma_dev, addr, DPAA_BP_RAW_SIZE,
		       DMA_FROM_DEVICE);

	/* prefetch the first 64 bytes of the frame or the SGT start */
	vaddr = phys_to_virt(addr);
	prefetch(vaddr + qm_fd_get_offset(fd));

	/* The only FD types that we may receive are contig and S/G */
	WARN_ON((fd_क्रमmat != qm_fd_contig) && (fd_क्रमmat != qm_fd_sg));

	/* Account क्रम either the contig buffer or the SGT buffer (depending on
	 * which हाल we were in) having been हटाओd from the pool.
	 */
	count_ptr = this_cpu_ptr(dpaa_bp->percpu_count);
	(*count_ptr)--;

	/* Extract the बारtamp stored in the headroom beक्रमe running XDP */
	अगर (priv->rx_tstamp) अणु
		अगर (!fman_port_get_tstamp(priv->mac_dev->port[RX], vaddr, &ns))
			ts_valid = true;
		अन्यथा
			WARN_ONCE(1, "fman_port_get_tstamp failed!\n");
	पूर्ण

	/* Extract the hash stored in the headroom beक्रमe running XDP */
	अगर (net_dev->features & NETIF_F_RXHASH && priv->keygen_in_use &&
	    !fman_port_get_hash_result_offset(priv->mac_dev->port[RX],
					      &hash_offset)) अणु
		hash = be32_to_cpu(*(u32 *)(vaddr + hash_offset));
		hash_valid = true;
	पूर्ण

	अगर (likely(fd_क्रमmat == qm_fd_contig)) अणु
		xdp_act = dpaa_run_xdp(priv, (काष्ठा qm_fd *)fd, vaddr,
				       dpaa_fq, &xdp_meta_len);
		np->xdp_act |= xdp_act;
		अगर (xdp_act != XDP_PASS) अणु
			percpu_stats->rx_packets++;
			percpu_stats->rx_bytes += qm_fd_get_length(fd);
			वापस qman_cb_dqrr_consume;
		पूर्ण
		skb = contig_fd_to_skb(priv, fd);
	पूर्ण अन्यथा अणु
		/* XDP करोesn't support S/G frames. Return the fragments to the
		 * buffer pool and release the SGT.
		 */
		अगर (READ_ONCE(priv->xdp_prog)) अणु
			WARN_ONCE(1, "S/G frames not supported under XDP\n");
			sgt = vaddr + qm_fd_get_offset(fd);
			dpaa_release_sgt_members(sgt);
			मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
			वापस qman_cb_dqrr_consume;
		पूर्ण
		skb = sg_fd_to_skb(priv, fd);
	पूर्ण
	अगर (!skb)
		वापस qman_cb_dqrr_consume;

	अगर (xdp_meta_len)
		skb_metadata_set(skb, xdp_meta_len);

	/* Set the previously extracted बारtamp */
	अगर (ts_valid) अणु
		shhwtstamps = skb_hwtstamps(skb);
		स_रखो(shhwtstamps, 0, माप(*shhwtstamps));
		shhwtstamps->hwtstamp = ns_to_kसमय(ns);
	पूर्ण

	skb->protocol = eth_type_trans(skb, net_dev);

	/* Set the previously extracted hash */
	अगर (hash_valid) अणु
		क्रमागत pkt_hash_types type;

		/* अगर L4 exists, it was used in the hash generation */
		type = be32_to_cpu(fd->status) & FM_FD_STAT_L4CV ?
			PKT_HASH_TYPE_L4 : PKT_HASH_TYPE_L3;
		skb_set_hash(skb, hash, type);
	पूर्ण

	skb_len = skb->len;

	अगर (unlikely(netअगर_receive_skb(skb) == NET_RX_DROP)) अणु
		percpu_stats->rx_dropped++;
		वापस qman_cb_dqrr_consume;
	पूर्ण

	percpu_stats->rx_packets++;
	percpu_stats->rx_bytes += skb_len;

	वापस qman_cb_dqrr_consume;
पूर्ण

अटल क्रमागत qman_cb_dqrr_result conf_error_dqrr(काष्ठा qman_portal *portal,
						काष्ठा qman_fq *fq,
						स्थिर काष्ठा qm_dqrr_entry *dq,
						bool sched_napi)
अणु
	काष्ठा dpaa_percpu_priv *percpu_priv;
	काष्ठा net_device *net_dev;
	काष्ठा dpaa_priv *priv;

	net_dev = ((काष्ठा dpaa_fq *)fq)->net_dev;
	priv = netdev_priv(net_dev);

	percpu_priv = this_cpu_ptr(priv->percpu_priv);

	अगर (dpaa_eth_napi_schedule(percpu_priv, portal, sched_napi))
		वापस qman_cb_dqrr_stop;

	dpaa_tx_error(net_dev, priv, percpu_priv, &dq->fd, fq->fqid);

	वापस qman_cb_dqrr_consume;
पूर्ण

अटल क्रमागत qman_cb_dqrr_result conf_dflt_dqrr(काष्ठा qman_portal *portal,
					       काष्ठा qman_fq *fq,
					       स्थिर काष्ठा qm_dqrr_entry *dq,
					       bool sched_napi)
अणु
	काष्ठा dpaa_percpu_priv *percpu_priv;
	काष्ठा net_device *net_dev;
	काष्ठा dpaa_priv *priv;

	net_dev = ((काष्ठा dpaa_fq *)fq)->net_dev;
	priv = netdev_priv(net_dev);

	/* Trace the fd */
	trace_dpaa_tx_conf_fd(net_dev, fq, &dq->fd);

	percpu_priv = this_cpu_ptr(priv->percpu_priv);

	अगर (dpaa_eth_napi_schedule(percpu_priv, portal, sched_napi))
		वापस qman_cb_dqrr_stop;

	dpaa_tx_conf(net_dev, priv, percpu_priv, &dq->fd, fq->fqid);

	वापस qman_cb_dqrr_consume;
पूर्ण

अटल व्योम egress_ern(काष्ठा qman_portal *portal,
		       काष्ठा qman_fq *fq,
		       स्थिर जोड़ qm_mr_entry *msg)
अणु
	स्थिर काष्ठा qm_fd *fd = &msg->ern.fd;
	काष्ठा dpaa_percpu_priv *percpu_priv;
	स्थिर काष्ठा dpaa_priv *priv;
	काष्ठा net_device *net_dev;
	काष्ठा sk_buff *skb;

	net_dev = ((काष्ठा dpaa_fq *)fq)->net_dev;
	priv = netdev_priv(net_dev);
	percpu_priv = this_cpu_ptr(priv->percpu_priv);

	percpu_priv->stats.tx_dropped++;
	percpu_priv->stats.tx_fअगरo_errors++;
	count_ern(percpu_priv, msg);

	skb = dpaa_cleanup_tx_fd(priv, fd, false);
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल स्थिर काष्ठा dpaa_fq_cbs dpaa_fq_cbs = अणु
	.rx_defq = अणु .cb = अणु .dqrr = rx_शेष_dqrr पूर्ण पूर्ण,
	.tx_defq = अणु .cb = अणु .dqrr = conf_dflt_dqrr पूर्ण पूर्ण,
	.rx_errq = अणु .cb = अणु .dqrr = rx_error_dqrr पूर्ण पूर्ण,
	.tx_errq = अणु .cb = अणु .dqrr = conf_error_dqrr पूर्ण पूर्ण,
	.egress_ern = अणु .cb = अणु .ern = egress_ern पूर्ण पूर्ण
पूर्ण;

अटल व्योम dpaa_eth_napi_enable(काष्ठा dpaa_priv *priv)
अणु
	काष्ठा dpaa_percpu_priv *percpu_priv;
	पूर्णांक i;

	क्रम_each_online_cpu(i) अणु
		percpu_priv = per_cpu_ptr(priv->percpu_priv, i);

		percpu_priv->np.करोwn = false;
		napi_enable(&percpu_priv->np.napi);
	पूर्ण
पूर्ण

अटल व्योम dpaa_eth_napi_disable(काष्ठा dpaa_priv *priv)
अणु
	काष्ठा dpaa_percpu_priv *percpu_priv;
	पूर्णांक i;

	क्रम_each_online_cpu(i) अणु
		percpu_priv = per_cpu_ptr(priv->percpu_priv, i);

		percpu_priv->np.करोwn = true;
		napi_disable(&percpu_priv->np.napi);
	पूर्ण
पूर्ण

अटल व्योम dpaa_adjust_link(काष्ठा net_device *net_dev)
अणु
	काष्ठा mac_device *mac_dev;
	काष्ठा dpaa_priv *priv;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;
	mac_dev->adjust_link(mac_dev);
पूर्ण

/* The Aquantia PHYs are capable of perक्रमming rate adaptation */
#घोषणा PHY_VEND_AQUANTIA	0x03a1b400

अटल पूर्णांक dpaa_phy_init(काष्ठा net_device *net_dev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा mac_device *mac_dev;
	काष्ठा phy_device *phy_dev;
	काष्ठा dpaa_priv *priv;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;

	phy_dev = of_phy_connect(net_dev, mac_dev->phy_node,
				 &dpaa_adjust_link, 0,
				 mac_dev->phy_अगर);
	अगर (!phy_dev) अणु
		netअगर_err(priv, अगरup, net_dev, "init_phy() failed\n");
		वापस -ENODEV;
	पूर्ण

	/* Unless the PHY is capable of rate adaptation */
	अगर (mac_dev->phy_अगर != PHY_INTERFACE_MODE_XGMII ||
	    ((phy_dev->drv->phy_id & GENMASK(31, 10)) != PHY_VEND_AQUANTIA)) अणु
		/* हटाओ any features not supported by the controller */
		ethtool_convert_legacy_u32_to_link_mode(mask,
							mac_dev->अगर_support);
		linkmode_and(phy_dev->supported, phy_dev->supported, mask);
	पूर्ण

	phy_support_asym_छोड़ो(phy_dev);

	mac_dev->phy_dev = phy_dev;
	net_dev->phydev = phy_dev;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा mac_device *mac_dev;
	काष्ठा dpaa_priv *priv;
	पूर्णांक err, i;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;
	dpaa_eth_napi_enable(priv);

	err = dpaa_phy_init(net_dev);
	अगर (err)
		जाओ phy_init_failed;

	क्रम (i = 0; i < ARRAY_SIZE(mac_dev->port); i++) अणु
		err = fman_port_enable(mac_dev->port[i]);
		अगर (err)
			जाओ mac_start_failed;
	पूर्ण

	err = priv->mac_dev->start(mac_dev);
	अगर (err < 0) अणु
		netअगर_err(priv, अगरup, net_dev, "mac_dev->start() = %d\n", err);
		जाओ mac_start_failed;
	पूर्ण

	netअगर_tx_start_all_queues(net_dev);

	वापस 0;

mac_start_failed:
	क्रम (i = 0; i < ARRAY_SIZE(mac_dev->port); i++)
		fman_port_disable(mac_dev->port[i]);

phy_init_failed:
	dpaa_eth_napi_disable(priv);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa_eth_stop(काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa_priv *priv;
	पूर्णांक err;

	err = dpaa_stop(net_dev);

	priv = netdev_priv(net_dev);
	dpaa_eth_napi_disable(priv);

	वापस err;
पूर्ण

अटल bool xdp_validate_mtu(काष्ठा dpaa_priv *priv, पूर्णांक mtu)
अणु
	पूर्णांक max_contig_data = priv->dpaa_bp->size - priv->rx_headroom;

	/* We करो not support S/G fragments when XDP is enabled.
	 * Limit the MTU in relation to the buffer size.
	 */
	अगर (mtu + VLAN_ETH_HLEN + ETH_FCS_LEN > max_contig_data) अणु
		dev_warn(priv->net_dev->dev.parent,
			 "The maximum MTU for XDP is %d\n",
			 max_contig_data - VLAN_ETH_HLEN - ETH_FCS_LEN);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक dpaa_change_mtu(काष्ठा net_device *net_dev, पूर्णांक new_mtu)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);

	अगर (priv->xdp_prog && !xdp_validate_mtu(priv, new_mtu))
		वापस -EINVAL;

	net_dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_setup_xdp(काष्ठा net_device *net_dev, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);
	काष्ठा bpf_prog *old_prog;
	पूर्णांक err;
	bool up;

	/* S/G fragments are not supported in XDP-mode */
	अगर (bpf->prog && !xdp_validate_mtu(priv, net_dev->mtu)) अणु
		NL_SET_ERR_MSG_MOD(bpf->extack, "MTU too large for XDP");
		वापस -EINVAL;
	पूर्ण

	up = netअगर_running(net_dev);

	अगर (up)
		dpaa_eth_stop(net_dev);

	old_prog = xchg(&priv->xdp_prog, bpf->prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	अगर (up) अणु
		err = dpaa_खोलो(net_dev);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(bpf->extack, "dpaa_open() failed");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa_xdp(काष्ठा net_device *net_dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस dpaa_setup_xdp(net_dev, xdp);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa_xdp_xmit(काष्ठा net_device *net_dev, पूर्णांक n,
			 काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा xdp_frame *xdpf;
	पूर्णांक i, nxmit = 0;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	अगर (!netअगर_running(net_dev))
		वापस -ENETDOWN;

	क्रम (i = 0; i < n; i++) अणु
		xdpf = frames[i];
		अगर (dpaa_xdp_xmit_frame(net_dev, xdpf))
			अवरोध;
		nxmit++;
	पूर्ण

	वापस nxmit;
पूर्ण

अटल पूर्णांक dpaa_ts_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(dev);
	काष्ठा hwtstamp_config config;

	अगर (copy_from_user(&config, rq->अगरr_data, माप(config)))
		वापस -EFAULT;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		/* Couldn't disable rx/tx बारtamping separately.
		 * Do nothing here.
		 */
		priv->tx_tstamp = false;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		priv->mac_dev->set_tstamp(priv->mac_dev->fman_mac, true);
		priv->tx_tstamp = true;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	अगर (config.rx_filter == HWTSTAMP_FILTER_NONE) अणु
		/* Couldn't disable rx/tx बारtamping separately.
		 * Do nothing here.
		 */
		priv->rx_tstamp = false;
	पूर्ण अन्यथा अणु
		priv->mac_dev->set_tstamp(priv->mac_dev->fman_mac, true);
		priv->rx_tstamp = true;
		/* TS is set क्रम all frame types, not only those requested */
		config.rx_filter = HWTSTAMP_FILTER_ALL;
	पूर्ण

	वापस copy_to_user(rq->अगरr_data, &config, माप(config)) ?
			-EFAULT : 0;
पूर्ण

अटल पूर्णांक dpaa_ioctl(काष्ठा net_device *net_dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (cmd == SIOCGMIIREG) अणु
		अगर (net_dev->phydev)
			वापस phy_mii_ioctl(net_dev->phydev, rq, cmd);
	पूर्ण

	अगर (cmd == SIOCSHWTSTAMP)
		वापस dpaa_ts_ioctl(net_dev, rq, cmd);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops dpaa_ops = अणु
	.nकरो_खोलो = dpaa_खोलो,
	.nकरो_start_xmit = dpaa_start_xmit,
	.nकरो_stop = dpaa_eth_stop,
	.nकरो_tx_समयout = dpaa_tx_समयout,
	.nकरो_get_stats64 = dpaa_get_stats64,
	.nकरो_change_carrier = fixed_phy_change_carrier,
	.nकरो_set_mac_address = dpaa_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_set_rx_mode = dpaa_set_rx_mode,
	.nकरो_करो_ioctl = dpaa_ioctl,
	.nकरो_setup_tc = dpaa_setup_tc,
	.nकरो_change_mtu = dpaa_change_mtu,
	.nकरो_bpf = dpaa_xdp,
	.nकरो_xdp_xmit = dpaa_xdp_xmit,
पूर्ण;

अटल पूर्णांक dpaa_napi_add(काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);
	काष्ठा dpaa_percpu_priv *percpu_priv;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		percpu_priv = per_cpu_ptr(priv->percpu_priv, cpu);

		netअगर_napi_add(net_dev, &percpu_priv->np.napi,
			       dpaa_eth_poll, NAPI_POLL_WEIGHT);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpaa_napi_del(काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(net_dev);
	काष्ठा dpaa_percpu_priv *percpu_priv;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		percpu_priv = per_cpu_ptr(priv->percpu_priv, cpu);

		netअगर_napi_del(&percpu_priv->np.napi);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dpaa_bp_मुक्त_pf(स्थिर काष्ठा dpaa_bp *bp,
				   काष्ठा bm_buffer *bmb)
अणु
	dma_addr_t addr = bm_buf_addr(bmb);

	dma_unmap_page(bp->priv->rx_dma_dev, addr, DPAA_BP_RAW_SIZE,
		       DMA_FROM_DEVICE);

	skb_मुक्त_frag(phys_to_virt(addr));
पूर्ण

/* Alloc the dpaa_bp काष्ठा and configure शेष values */
अटल काष्ठा dpaa_bp *dpaa_bp_alloc(काष्ठा device *dev)
अणु
	काष्ठा dpaa_bp *dpaa_bp;

	dpaa_bp = devm_kzalloc(dev, माप(*dpaa_bp), GFP_KERNEL);
	अगर (!dpaa_bp)
		वापस ERR_PTR(-ENOMEM);

	dpaa_bp->bpid = FSL_DPAA_BPID_INV;
	dpaa_bp->percpu_count = devm_alloc_percpu(dev, *dpaa_bp->percpu_count);
	अगर (!dpaa_bp->percpu_count)
		वापस ERR_PTR(-ENOMEM);

	dpaa_bp->config_count = FSL_DPAA_ETH_MAX_BUF_COUNT;

	dpaa_bp->seed_cb = dpaa_bp_seed;
	dpaa_bp->मुक्त_buf_cb = dpaa_bp_मुक्त_pf;

	वापस dpaa_bp;
पूर्ण

/* Place all ingress FQs (Rx Default, Rx Error) in a dedicated CGR.
 * We won't be sending congestion notअगरications to FMan; क्रम now, we just use
 * this CGR to generate enqueue rejections to FMan in order to drop the frames
 * beक्रमe they reach our ingress queues and eat up memory.
 */
अटल पूर्णांक dpaa_ingress_cgr_init(काष्ठा dpaa_priv *priv)
अणु
	काष्ठा qm_mcc_initcgr initcgr;
	u32 cs_th;
	पूर्णांक err;

	err = qman_alloc_cgrid(&priv->ingress_cgr.cgrid);
	अगर (err < 0) अणु
		अगर (netअगर_msg_drv(priv))
			pr_err("Error %d allocating CGR ID\n", err);
		जाओ out_error;
	पूर्ण

	/* Enable CS TD, but disable Congestion State Change Notअगरications. */
	स_रखो(&initcgr, 0, माप(initcgr));
	initcgr.we_mask = cpu_to_be16(QM_CGR_WE_CS_THRES);
	initcgr.cgr.cscn_en = QM_CGR_EN;
	cs_th = DPAA_INGRESS_CS_THRESHOLD;
	qm_cgr_cs_thres_set64(&initcgr.cgr.cs_thres, cs_th, 1);

	initcgr.we_mask |= cpu_to_be16(QM_CGR_WE_CSTD_EN);
	initcgr.cgr.cstd_en = QM_CGR_EN;

	/* This CGR will be associated with the SWP affined to the current CPU.
	 * However, we'll place all our ingress FQs in it.
	 */
	err = qman_create_cgr(&priv->ingress_cgr, QMAN_CGR_FLAG_USE_INIT,
			      &initcgr);
	अगर (err < 0) अणु
		अगर (netअगर_msg_drv(priv))
			pr_err("Error %d creating ingress CGR with ID %d\n",
			       err, priv->ingress_cgr.cgrid);
		qman_release_cgrid(priv->ingress_cgr.cgrid);
		जाओ out_error;
	पूर्ण
	अगर (netअगर_msg_drv(priv))
		pr_debug("Created ingress CGR %d for netdev with hwaddr %pM\n",
			 priv->ingress_cgr.cgrid, priv->mac_dev->addr);

	priv->use_ingress_cgr = true;

out_error:
	वापस err;
पूर्ण

अटल u16 dpaa_get_headroom(काष्ठा dpaa_buffer_layout *bl,
			     क्रमागत port_type port)
अणु
	u16 headroom;

	/* The frame headroom must accommodate:
	 * - the driver निजी data area
	 * - parse results, hash results, बारtamp अगर selected
	 * If either hash results or समय stamp are selected, both will
	 * be copied to/from the frame headroom, as TS is located between PR and
	 * HR in the IC and IC copy size has a granularity of 16bytes
	 * (see description of FMBM_RICP and FMBM_TICP रेजिस्टरs in DPAARM)
	 *
	 * Also make sure the headroom is a multiple of data_align bytes
	 */
	headroom = (u16)(bl[port].priv_data_size + DPAA_HWA_SIZE);

	अगर (port == RX) अणु
#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
		अगर (unlikely(fman_has_errata_a050385()))
			headroom = XDP_PACKET_HEADROOM;
#पूर्ण_अगर

		वापस ALIGN(headroom, DPAA_FD_RX_DATA_ALIGNMENT);
	पूर्ण अन्यथा अणु
		वापस ALIGN(headroom, DPAA_FD_DATA_ALIGNMENT);
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa_eth_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *net_dev = शून्य;
	काष्ठा dpaa_bp *dpaa_bp = शून्य;
	काष्ठा dpaa_fq *dpaa_fq, *पंचांगp;
	काष्ठा dpaa_priv *priv = शून्य;
	काष्ठा fm_port_fqs port_fqs;
	काष्ठा mac_device *mac_dev;
	पूर्णांक err = 0, channel;
	काष्ठा device *dev;

	dev = &pdev->dev;

	err = bman_is_probed();
	अगर (!err)
		वापस -EPROBE_DEFER;
	अगर (err < 0) अणु
		dev_err(dev, "failing probe due to bman probe error\n");
		वापस -ENODEV;
	पूर्ण
	err = qman_is_probed();
	अगर (!err)
		वापस -EPROBE_DEFER;
	अगर (err < 0) अणु
		dev_err(dev, "failing probe due to qman probe error\n");
		वापस -ENODEV;
	पूर्ण
	err = bman_portals_probed();
	अगर (!err)
		वापस -EPROBE_DEFER;
	अगर (err < 0) अणु
		dev_err(dev,
			"failing probe due to bman portals probe error\n");
		वापस -ENODEV;
	पूर्ण
	err = qman_portals_probed();
	अगर (!err)
		वापस -EPROBE_DEFER;
	अगर (err < 0) अणु
		dev_err(dev,
			"failing probe due to qman portals probe error\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate this early, so we can store relevant inक्रमmation in
	 * the निजी area
	 */
	net_dev = alloc_etherdev_mq(माप(*priv), DPAA_ETH_TXQ_NUM);
	अगर (!net_dev) अणु
		dev_err(dev, "alloc_etherdev_mq() failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* Do this here, so we can be verbose early */
	SET_NETDEV_DEV(net_dev, dev->parent);
	dev_set_drvdata(dev, net_dev);

	priv = netdev_priv(net_dev);
	priv->net_dev = net_dev;

	priv->msg_enable = netअगर_msg_init(debug, DPAA_MSG_DEFAULT);

	mac_dev = dpaa_mac_dev_get(pdev);
	अगर (IS_ERR(mac_dev)) अणु
		netdev_err(net_dev, "dpaa_mac_dev_get() failed\n");
		err = PTR_ERR(mac_dev);
		जाओ मुक्त_netdev;
	पूर्ण

	/* Devices used क्रम DMA mapping */
	priv->rx_dma_dev = fman_port_get_device(mac_dev->port[RX]);
	priv->tx_dma_dev = fman_port_get_device(mac_dev->port[TX]);
	err = dma_coerce_mask_and_coherent(priv->rx_dma_dev, DMA_BIT_MASK(40));
	अगर (!err)
		err = dma_coerce_mask_and_coherent(priv->tx_dma_dev,
						   DMA_BIT_MASK(40));
	अगर (err) अणु
		netdev_err(net_dev, "dma_coerce_mask_and_coherent() failed\n");
		जाओ मुक्त_netdev;
	पूर्ण

	/* If fsl_fm_max_frm is set to a higher value than the all-common 1500,
	 * we choose conservatively and let the user explicitly set a higher
	 * MTU via अगरconfig. Otherwise, the user may end up with dअगरferent MTUs
	 * in the same LAN.
	 * If on the other hand fsl_fm_max_frm has been chosen below 1500,
	 * start with the maximum allowed.
	 */
	net_dev->mtu = min(dpaa_get_max_mtu(), ETH_DATA_LEN);

	netdev_dbg(net_dev, "Setting initial MTU on net device: %d\n",
		   net_dev->mtu);

	priv->buf_layout[RX].priv_data_size = DPAA_RX_PRIV_DATA_SIZE; /* Rx */
	priv->buf_layout[TX].priv_data_size = DPAA_TX_PRIV_DATA_SIZE; /* Tx */

	/* bp init */
	dpaa_bp = dpaa_bp_alloc(dev);
	अगर (IS_ERR(dpaa_bp)) अणु
		err = PTR_ERR(dpaa_bp);
		जाओ मुक्त_dpaa_bps;
	पूर्ण
	/* the raw size of the buffers used क्रम reception */
	dpaa_bp->raw_size = DPAA_BP_RAW_SIZE;
	/* aव्योम runसमय computations by keeping the usable size here */
	dpaa_bp->size = dpaa_bp_size(dpaa_bp->raw_size);
	dpaa_bp->priv = priv;

	err = dpaa_bp_alloc_pool(dpaa_bp);
	अगर (err < 0)
		जाओ मुक्त_dpaa_bps;
	priv->dpaa_bp = dpaa_bp;

	INIT_LIST_HEAD(&priv->dpaa_fq_list);

	स_रखो(&port_fqs, 0, माप(port_fqs));

	err = dpaa_alloc_all_fqs(dev, &priv->dpaa_fq_list, &port_fqs);
	अगर (err < 0) अणु
		dev_err(dev, "dpaa_alloc_all_fqs() failed\n");
		जाओ मुक्त_dpaa_bps;
	पूर्ण

	priv->mac_dev = mac_dev;

	channel = dpaa_get_channel();
	अगर (channel < 0) अणु
		dev_err(dev, "dpaa_get_channel() failed\n");
		err = channel;
		जाओ मुक्त_dpaa_bps;
	पूर्ण

	priv->channel = (u16)channel;

	/* Walk the CPUs with affine portals
	 * and add this pool channel to each's dequeue mask.
	 */
	dpaa_eth_add_channel(priv->channel, &pdev->dev);

	dpaa_fq_setup(priv, &dpaa_fq_cbs, priv->mac_dev->port[TX]);

	/* Create a congestion group क्रम this netdev, with
	 * dynamically-allocated CGR ID.
	 * Must be executed after probing the MAC, but beक्रमe
	 * assigning the egress FQs to the CGRs.
	 */
	err = dpaa_eth_cgr_init(priv);
	अगर (err < 0) अणु
		dev_err(dev, "Error initializing CGR\n");
		जाओ मुक्त_dpaa_bps;
	पूर्ण

	err = dpaa_ingress_cgr_init(priv);
	अगर (err < 0) अणु
		dev_err(dev, "Error initializing ingress CGR\n");
		जाओ delete_egress_cgr;
	पूर्ण

	/* Add the FQs to the पूर्णांकerface, and make them active */
	list_क्रम_each_entry_safe(dpaa_fq, पंचांगp, &priv->dpaa_fq_list, list) अणु
		err = dpaa_fq_init(dpaa_fq, false);
		अगर (err < 0)
			जाओ मुक्त_dpaa_fqs;
	पूर्ण

	priv->tx_headroom = dpaa_get_headroom(priv->buf_layout, TX);
	priv->rx_headroom = dpaa_get_headroom(priv->buf_layout, RX);

	/* All real पूर्णांकerfaces need their ports initialized */
	err = dpaa_eth_init_ports(mac_dev, dpaa_bp, &port_fqs,
				  &priv->buf_layout[0], dev);
	अगर (err)
		जाओ मुक्त_dpaa_fqs;

	/* Rx traffic distribution based on keygen hashing शेषs to on */
	priv->keygen_in_use = true;

	priv->percpu_priv = devm_alloc_percpu(dev, *priv->percpu_priv);
	अगर (!priv->percpu_priv) अणु
		dev_err(dev, "devm_alloc_percpu() failed\n");
		err = -ENOMEM;
		जाओ मुक्त_dpaa_fqs;
	पूर्ण

	priv->num_tc = 1;
	netअगर_set_real_num_tx_queues(net_dev, priv->num_tc * DPAA_TC_TXQ_NUM);

	/* Initialize NAPI */
	err = dpaa_napi_add(net_dev);
	अगर (err < 0)
		जाओ delete_dpaa_napi;

	err = dpaa_netdev_init(net_dev, &dpaa_ops, tx_समयout);
	अगर (err < 0)
		जाओ delete_dpaa_napi;

	dpaa_eth_sysfs_init(&net_dev->dev);

	netअगर_info(priv, probe, net_dev, "Probed interface %s\n",
		   net_dev->name);

	वापस 0;

delete_dpaa_napi:
	dpaa_napi_del(net_dev);
मुक्त_dpaa_fqs:
	dpaa_fq_मुक्त(dev, &priv->dpaa_fq_list);
	qman_delete_cgr_safe(&priv->ingress_cgr);
	qman_release_cgrid(priv->ingress_cgr.cgrid);
delete_egress_cgr:
	qman_delete_cgr_safe(&priv->cgr_data.cgr);
	qman_release_cgrid(priv->cgr_data.cgr.cgrid);
मुक्त_dpaa_bps:
	dpaa_bps_मुक्त(priv);
मुक्त_netdev:
	dev_set_drvdata(dev, शून्य);
	मुक्त_netdev(net_dev);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *net_dev;
	काष्ठा dpaa_priv *priv;
	काष्ठा device *dev;
	पूर्णांक err;

	dev = &pdev->dev;
	net_dev = dev_get_drvdata(dev);

	priv = netdev_priv(net_dev);

	dpaa_eth_sysfs_हटाओ(dev);

	dev_set_drvdata(dev, शून्य);
	unरेजिस्टर_netdev(net_dev);

	err = dpaa_fq_मुक्त(dev, &priv->dpaa_fq_list);

	qman_delete_cgr_safe(&priv->ingress_cgr);
	qman_release_cgrid(priv->ingress_cgr.cgrid);
	qman_delete_cgr_safe(&priv->cgr_data.cgr);
	qman_release_cgrid(priv->cgr_data.cgr.cgrid);

	dpaa_napi_del(net_dev);

	dpaa_bps_मुक्त(priv);

	मुक्त_netdev(net_dev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id dpaa_devtype[] = अणु
	अणु
		.name = "dpaa-ethernet",
		.driver_data = 0,
	पूर्ण, अणु
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, dpaa_devtype);

अटल काष्ठा platक्रमm_driver dpaa_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
	पूर्ण,
	.id_table = dpaa_devtype,
	.probe = dpaa_eth_probe,
	.हटाओ = dpaa_हटाओ
पूर्ण;

अटल पूर्णांक __init dpaa_load(व्योम)
अणु
	पूर्णांक err;

	pr_debug("FSL DPAA Ethernet driver\n");

	/* initialize dpaa_eth mirror values */
	dpaa_rx_extra_headroom = fman_get_rx_extra_headroom();
	dpaa_max_frm = fman_get_max_frm();

	err = platक्रमm_driver_रेजिस्टर(&dpaa_driver);
	अगर (err < 0)
		pr_err("Error, platform_driver_register() = %d\n", err);

	वापस err;
पूर्ण
module_init(dpaa_load);

अटल व्योम __निकास dpaa_unload(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&dpaa_driver);

	/* Only one channel is used and needs to be released after all
	 * पूर्णांकerfaces are हटाओd
	 */
	dpaa_release_channel();
पूर्ण
module_निकास(dpaa_unload);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("FSL DPAA Ethernet driver");
