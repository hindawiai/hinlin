<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor Inc.
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

#अगर_अघोषित __DPAA_H
#घोषणा __DPAA_H

#समावेश <linux/netdevice.h>
#समावेश <linux/refcount.h>
#समावेश <soc/fsl/qman.h>
#समावेश <soc/fsl/bman.h>

#समावेश "fman.h"
#समावेश "mac.h"
#समावेश "dpaa_eth_trace.h"

/* Number of prioritised traffic classes */
#घोषणा DPAA_TC_NUM		4
/* Number of Tx queues per traffic class */
#घोषणा DPAA_TC_TXQ_NUM		NR_CPUS
/* Total number of Tx queues */
#घोषणा DPAA_ETH_TXQ_NUM	(DPAA_TC_NUM * DPAA_TC_TXQ_NUM)

/* More detailed FQ types - used क्रम fine-grained WQ assignments */
क्रमागत dpaa_fq_type अणु
	FQ_TYPE_RX_DEFAULT = 1, /* Rx Default FQs */
	FQ_TYPE_RX_ERROR,	/* Rx Error FQs */
	FQ_TYPE_RX_PCD,		/* Rx Parse Classअगरy Distribute FQs */
	FQ_TYPE_TX,		/* "Real" Tx FQs */
	FQ_TYPE_TX_CONFIRM,	/* Tx शेष Conf FQ (actually an Rx FQ) */
	FQ_TYPE_TX_CONF_MQ,	/* Tx conf FQs (one क्रम each Tx FQ) */
	FQ_TYPE_TX_ERROR,	/* Tx Error FQs (these are actually Rx FQs) */
पूर्ण;

काष्ठा dpaa_fq अणु
	काष्ठा qman_fq fq_base;
	काष्ठा list_head list;
	काष्ठा net_device *net_dev;
	bool init;
	u32 fqid;
	u32 flags;
	u16 channel;
	u8 wq;
	क्रमागत dpaa_fq_type fq_type;
	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण;

काष्ठा dpaa_fq_cbs अणु
	काष्ठा qman_fq rx_defq;
	काष्ठा qman_fq tx_defq;
	काष्ठा qman_fq rx_errq;
	काष्ठा qman_fq tx_errq;
	काष्ठा qman_fq egress_ern;
पूर्ण;

काष्ठा dpaa_priv;

काष्ठा dpaa_bp अणु
	/* used in the DMA mapping operations */
	काष्ठा dpaa_priv *priv;
	/* current number of buffers in the buffer pool alloted to each CPU */
	पूर्णांक __percpu *percpu_count;
	/* all buffers allocated क्रम this pool have this raw size */
	माप_प्रकार raw_size;
	/* all buffers in this pool have this same usable size */
	माप_प्रकार size;
	/* the buffer pools are initialized with config_count buffers क्रम each
	 * CPU; at runसमय the number of buffers per CPU is स्थिरantly brought
	 * back to this level
	 */
	u16 config_count;
	u8 bpid;
	काष्ठा bman_pool *pool;
	/* bpool can be seeded beक्रमe use by this cb */
	पूर्णांक (*seed_cb)(काष्ठा dpaa_bp *);
	/* bpool can be emptied beक्रमe मुक्तing by this cb */
	व्योम (*मुक्त_buf_cb)(स्थिर काष्ठा dpaa_bp *, काष्ठा bm_buffer *);
	refcount_t refs;
पूर्ण;

काष्ठा dpaa_rx_errors अणु
	u64 dme;		/* DMA Error */
	u64 fpe;		/* Frame Physical Error */
	u64 fse;		/* Frame Size Error */
	u64 phe;		/* Header Error */
पूर्ण;

/* Counters क्रम QMan ERN frames - one counter per rejection code */
काष्ठा dpaa_ern_cnt अणु
	u64 cg_tdrop;		/* Congestion group taildrop */
	u64 wred;		/* WRED congestion */
	u64 err_cond;		/* Error condition */
	u64 early_winकरोw;	/* Order restoration, frame too early */
	u64 late_winकरोw;	/* Order restoration, frame too late */
	u64 fq_tdrop;		/* FQ taildrop */
	u64 fq_retired;		/* FQ is retired */
	u64 orp_zero;		/* ORP disabled */
पूर्ण;

काष्ठा dpaa_napi_portal अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा qman_portal *p;
	bool करोwn;
	पूर्णांक xdp_act;
पूर्ण;

काष्ठा dpaa_percpu_priv अणु
	काष्ठा net_device *net_dev;
	काष्ठा dpaa_napi_portal np;
	u64 in_पूर्णांकerrupt;
	u64 tx_confirm;
	/* fragmented (non-linear) skbuffs received from the stack */
	u64 tx_frag_skbuffs;
	काष्ठा rtnl_link_stats64 stats;
	काष्ठा dpaa_rx_errors rx_errors;
	काष्ठा dpaa_ern_cnt ern_cnt;
पूर्ण;

काष्ठा dpaa_buffer_layout अणु
	u16 priv_data_size;
पूर्ण;

/* Inक्रमmation to be used on the Tx confirmation path. Stored just
 * beक्रमe the start of the transmit buffer. Maximum size allowed
 * is DPAA_TX_PRIV_DATA_SIZE bytes.
 */
काष्ठा dpaa_eth_swbp अणु
	काष्ठा sk_buff *skb;
	काष्ठा xdp_frame *xdpf;
पूर्ण;

काष्ठा dpaa_priv अणु
	काष्ठा dpaa_percpu_priv __percpu *percpu_priv;
	काष्ठा dpaa_bp *dpaa_bp;
	/* Store here the needed Tx headroom क्रम convenience and speed
	 * (even though it can be computed based on the fields of buf_layout)
	 */
	u16 tx_headroom;
	काष्ठा net_device *net_dev;
	काष्ठा mac_device *mac_dev;
	काष्ठा device *rx_dma_dev;
	काष्ठा device *tx_dma_dev;
	काष्ठा qman_fq *egress_fqs[DPAA_ETH_TXQ_NUM];
	काष्ठा qman_fq *conf_fqs[DPAA_ETH_TXQ_NUM];

	u16 channel;
	काष्ठा list_head dpaa_fq_list;

	u8 num_tc;
	bool keygen_in_use;
	u32 msg_enable;	/* net_device message level */

	काष्ठा अणु
		/* All egress queues to a given net device beदीर्घ to one
		 * (and the same) congestion group.
		 */
		काष्ठा qman_cgr cgr;
		/* If congested, when it began. Used क्रम perक्रमmance stats. */
		u32 congestion_start_jअगरfies;
		/* Number of jअगरfies the Tx port was congested. */
		u32 congested_jअगरfies;
		/* Counter क्रम the number of बार the CGR
		 * entered congestion state
		 */
		u32 cgr_congested_count;
	पूर्ण cgr_data;
	/* Use a per-port CGR क्रम ingress traffic. */
	bool use_ingress_cgr;
	काष्ठा qman_cgr ingress_cgr;

	काष्ठा dpaa_buffer_layout buf_layout[2];
	u16 rx_headroom;

	bool tx_tstamp; /* Tx बारtamping enabled */
	bool rx_tstamp; /* Rx बारtamping enabled */

	काष्ठा bpf_prog *xdp_prog;
पूर्ण;

/* from dpaa_ethtool.c */
बाह्य स्थिर काष्ठा ethtool_ops dpaa_ethtool_ops;

/* from dpaa_eth_sysfs.c */
व्योम dpaa_eth_sysfs_हटाओ(काष्ठा device *dev);
व्योम dpaa_eth_sysfs_init(काष्ठा device *dev);
#पूर्ण_अगर	/* __DPAA_H */
