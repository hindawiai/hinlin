<शैली गुरु>
/*
 * Copyright (c) 2003-2008 Chelsio, Inc. All rights reserved.
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

/* This file should not be included directly.  Include common.h instead. */

#अगर_अघोषित __T3_ADAPTER_H__
#घोषणा __T3_ADAPTER_H__

#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/cache.h>
#समावेश <linux/mutex.h>
#समावेश <linux/bitops.h>
#समावेश "t3cdev.h"
#समावेश <यंत्र/पन.स>

काष्ठा adapter;
काष्ठा sge_qset;
काष्ठा port_info;

क्रमागत mac_idx_types अणु
	LAN_MAC_IDX	= 0,
	SAN_MAC_IDX,

	MAX_MAC_IDX
पूर्ण;

काष्ठा iscsi_config अणु
	__u8	mac_addr[ETH_ALEN];
	__u32	flags;
	पूर्णांक (*send)(काष्ठा port_info *pi, काष्ठा sk_buff **skb);
	पूर्णांक (*recv)(काष्ठा port_info *pi, काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा port_info अणु
	काष्ठा adapter *adapter;
	काष्ठा sge_qset *qs;
	u8 port_id;
	u8 nqsets;
	u8 first_qset;
	काष्ठा cphy phy;
	काष्ठा cmac mac;
	काष्ठा link_config link_config;
	पूर्णांक activity;
	__be32 iscsi_ipv4addr;
	काष्ठा iscsi_config iscsic;

	पूर्णांक link_fault; /* link fault was detected */
पूर्ण;

क्रमागत अणु				/* adapter flags */
	FULL_INIT_DONE = (1 << 0),
	USING_MSI = (1 << 1),
	USING_MSIX = (1 << 2),
	QUEUES_BOUND = (1 << 3),
	TP_PARITY_INIT = (1 << 4),
	NAPI_INIT = (1 << 5),
पूर्ण;

काष्ठा fl_pg_chunk अणु
	काष्ठा page *page;
	व्योम *va;
	अचिन्हित पूर्णांक offset;
	अचिन्हित दीर्घ *p_cnt;
	dma_addr_t mapping;
पूर्ण;

काष्ठा rx_desc;
काष्ठा rx_sw_desc;

काष्ठा sge_fl अणु                     /* SGE per मुक्त-buffer list state */
	अचिन्हित पूर्णांक buf_size;      /* size of each Rx buffer */
	अचिन्हित पूर्णांक credits;       /* # of available Rx buffers */
	अचिन्हित पूर्णांक pend_cred;     /* new buffers since last FL DB ring */
	अचिन्हित पूर्णांक size;          /* capacity of मुक्त list */
	अचिन्हित पूर्णांक cidx;          /* consumer index */
	अचिन्हित पूर्णांक pidx;          /* producer index */
	अचिन्हित पूर्णांक gen;           /* मुक्त list generation */
	काष्ठा fl_pg_chunk pg_chunk;/* page chunk cache */
	अचिन्हित पूर्णांक use_pages;     /* whether FL uses pages or sk_buffs */
	अचिन्हित पूर्णांक order;	    /* order of page allocations */
	अचिन्हित पूर्णांक alloc_size;    /* size of allocated buffer */
	काष्ठा rx_desc *desc;       /* address of HW Rx descriptor ring */
	काष्ठा rx_sw_desc *sdesc;   /* address of SW Rx descriptor ring */
	dma_addr_t   phys_addr;     /* physical address of HW ring start */
	अचिन्हित पूर्णांक cntxt_id;      /* SGE context id क्रम the मुक्त list */
	अचिन्हित दीर्घ empty;        /* # of बार queue ran out of buffers */
	अचिन्हित दीर्घ alloc_failed; /* # of बार buffer allocation failed */
पूर्ण;

/*
 * Bundle size क्रम grouping offload RX packets क्रम delivery to the stack.
 * Don't make this too big as we करो prefetch on each packet in a bundle.
 */
# define RX_BUNDLE_SIZE 8

काष्ठा rsp_desc;

काष्ठा sge_rspq अणु		/* state क्रम an SGE response queue */
	अचिन्हित पूर्णांक credits;	/* # of pending response credits */
	अचिन्हित पूर्णांक size;	/* capacity of response queue */
	अचिन्हित पूर्णांक cidx;	/* consumer index */
	अचिन्हित पूर्णांक gen;	/* current generation bit */
	अचिन्हित पूर्णांक polling;	/* is the queue serviced through NAPI? */
	अचिन्हित पूर्णांक holकरोff_पंचांगr;	/* पूर्णांकerrupt holकरोff समयr in 100ns */
	अचिन्हित पूर्णांक next_holकरोff;	/* holकरोff समय क्रम next पूर्णांकerrupt */
	अचिन्हित पूर्णांक rx_recycle_buf; /* whether recycling occurred
					within current sop-eop */
	काष्ठा rsp_desc *desc;	/* address of HW response ring */
	dma_addr_t phys_addr;	/* physical address of the ring */
	अचिन्हित पूर्णांक cntxt_id;	/* SGE context id क्रम the response q */
	spinlock_t lock;	/* guards response processing */
	काष्ठा sk_buff_head rx_queue; /* offload packet receive queue */
	काष्ठा sk_buff *pg_skb; /* used to build frag list in napi handler */

	अचिन्हित दीर्घ offload_pkts;
	अचिन्हित दीर्घ offload_bundles;
	अचिन्हित दीर्घ eth_pkts;	/* # of ethernet packets */
	अचिन्हित दीर्घ pure_rsps;	/* # of pure (non-data) responses */
	अचिन्हित दीर्घ imm_data;	/* responses with immediate data */
	अचिन्हित दीर्घ rx_drops;	/* # of packets dropped due to no mem */
	अचिन्हित दीर्घ async_notअगर; /* # of asynchronous notअगरication events */
	अचिन्हित दीर्घ empty;	/* # of बार queue ran out of credits */
	अचिन्हित दीर्घ nomem;	/* # of responses deferred due to no mem */
	अचिन्हित दीर्घ unhandled_irqs;	/* # of spurious पूर्णांकrs */
	अचिन्हित दीर्घ starved;
	अचिन्हित दीर्घ restarted;
पूर्ण;

काष्ठा tx_desc;
काष्ठा tx_sw_desc;

काष्ठा sge_txq अणु		/* state क्रम an SGE Tx queue */
	अचिन्हित दीर्घ flags;	/* HW DMA fetch status */
	अचिन्हित पूर्णांक in_use;	/* # of in-use Tx descriptors */
	अचिन्हित पूर्णांक size;	/* # of descriptors */
	अचिन्हित पूर्णांक processed;	/* total # of descs HW has processed */
	अचिन्हित पूर्णांक cleaned;	/* total # of descs SW has reclaimed */
	अचिन्हित पूर्णांक stop_thres;	/* SW TX queue suspend threshold */
	अचिन्हित पूर्णांक cidx;	/* consumer index */
	अचिन्हित पूर्णांक pidx;	/* producer index */
	अचिन्हित पूर्णांक gen;	/* current value of generation bit */
	अचिन्हित पूर्णांक unacked;	/* Tx descriptors used since last COMPL */
	काष्ठा tx_desc *desc;	/* address of HW Tx descriptor ring */
	काष्ठा tx_sw_desc *sdesc;	/* address of SW Tx descriptor ring */
	spinlock_t lock;	/* guards enqueueing of new packets */
	अचिन्हित पूर्णांक token;	/* WR token */
	dma_addr_t phys_addr;	/* physical address of the ring */
	काष्ठा sk_buff_head sendq;	/* List of backpressured offload packets */
	काष्ठा tasklet_काष्ठा qresume_tsk;	/* restarts the queue */
	अचिन्हित पूर्णांक cntxt_id;	/* SGE context id क्रम the Tx q */
	अचिन्हित दीर्घ stops;	/* # of बार q has been stopped */
	अचिन्हित दीर्घ restarts;	/* # of queue restarts */
पूर्ण;

क्रमागत अणु				/* per port SGE statistics */
	SGE_PSTAT_TSO,		/* # of TSO requests */
	SGE_PSTAT_RX_CSUM_GOOD,	/* # of successful RX csum offloads */
	SGE_PSTAT_TX_CSUM,	/* # of TX checksum offloads */
	SGE_PSTAT_VLANEX,	/* # of VLAN tag extractions */
	SGE_PSTAT_VLANINS,	/* # of VLAN tag insertions */

	SGE_PSTAT_MAX		/* must be last */
पूर्ण;

काष्ठा napi_gro_fraginfo;

काष्ठा sge_qset अणु		/* an SGE queue set */
	काष्ठा adapter *adap;
	काष्ठा napi_काष्ठा napi;
	काष्ठा sge_rspq rspq;
	काष्ठा sge_fl fl[SGE_RXQ_PER_SET];
	काष्ठा sge_txq txq[SGE_TXQ_PER_SET];
	पूर्णांक nomem;
	व्योम *lro_va;
	काष्ठा net_device *netdev;
	काष्ठा netdev_queue *tx_q;	/* associated netdev TX queue */
	अचिन्हित दीर्घ txq_stopped;	/* which Tx queues are stopped */
	काष्ठा समयr_list tx_reclaim_समयr;	/* reclaims TX buffers */
	काष्ठा समयr_list rx_reclaim_समयr;	/* reclaims RX buffers */
	अचिन्हित दीर्घ port_stats[SGE_PSTAT_MAX];
पूर्ण ____cacheline_aligned;

काष्ठा sge अणु
	काष्ठा sge_qset qs[SGE_QSETS];
	spinlock_t reg_lock;	/* guards non-atomic SGE रेजिस्टरs (eg context) */
पूर्ण;

काष्ठा adapter अणु
	काष्ठा t3cdev tdev;
	काष्ठा list_head adapter_list;
	व्योम __iomem *regs;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ रेजिस्टरed_device_map;
	अचिन्हित दीर्घ खोलो_device_map;
	अचिन्हित दीर्घ flags;

	स्थिर अक्षर *name;
	पूर्णांक msg_enable;
	अचिन्हित पूर्णांक mmio_len;

	काष्ठा adapter_params params;
	अचिन्हित पूर्णांक slow_पूर्णांकr_mask;
	अचिन्हित दीर्घ irq_stats[IRQ_NUM_STATS];

	पूर्णांक msix_nvectors;
	काष्ठा अणु
		अचिन्हित लघु vec;
		अक्षर desc[22];
	पूर्ण msix_info[SGE_QSETS + 1];

	/* T3 modules */
	काष्ठा sge sge;
	काष्ठा mc7 pmrx;
	काष्ठा mc7 pmtx;
	काष्ठा mc7 cm;
	काष्ठा mc5 mc5;

	काष्ठा net_device *port[MAX_NPORTS];
	अचिन्हित पूर्णांक check_task_cnt;
	काष्ठा delayed_work adap_check_task;
	काष्ठा work_काष्ठा ext_पूर्णांकr_handler_task;
	काष्ठा work_काष्ठा fatal_error_handler_task;
	काष्ठा work_काष्ठा link_fault_handler_task;

	काष्ठा work_काष्ठा db_full_task;
	काष्ठा work_काष्ठा db_empty_task;
	काष्ठा work_काष्ठा db_drop_task;

	काष्ठा dentry *debugfs_root;

	काष्ठा mutex mdio_lock;
	spinlock_t stats_lock;
	spinlock_t work_lock;

	काष्ठा sk_buff *nofail_skb;
पूर्ण;

अटल अंतरभूत u32 t3_पढ़ो_reg(काष्ठा adapter *adapter, u32 reg_addr)
अणु
	u32 val = पढ़ोl(adapter->regs + reg_addr);

	CH_DBG(adapter, MMIO, "read register 0x%x value 0x%x\n", reg_addr, val);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम t3_ग_लिखो_reg(काष्ठा adapter *adapter, u32 reg_addr, u32 val)
अणु
	CH_DBG(adapter, MMIO, "setting register 0x%x to 0x%x\n", reg_addr, val);
	ग_लिखोl(val, adapter->regs + reg_addr);
पूर्ण

अटल अंतरभूत काष्ठा port_info *adap2pinfo(काष्ठा adapter *adap, पूर्णांक idx)
अणु
	वापस netdev_priv(adap->port[idx]);
पूर्ण

अटल अंतरभूत पूर्णांक phy2portid(काष्ठा cphy *phy)
अणु
	काष्ठा adapter *adap = phy->adapter;
	काष्ठा port_info *port0 = adap2pinfo(adap, 0);

	वापस &port0->phy == phy ? 0 : 1;
पूर्ण

#घोषणा OFFLOAD_DEVMAP_BIT 15

#घोषणा tdev2adap(d) container_of(d, काष्ठा adapter, tdev)

अटल अंतरभूत पूर्णांक offload_running(काष्ठा adapter *adapter)
अणु
	वापस test_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map);
पूर्ण

पूर्णांक t3_offload_tx(काष्ठा t3cdev *tdev, काष्ठा sk_buff *skb);

व्योम t3_os_ext_पूर्णांकr_handler(काष्ठा adapter *adapter);
व्योम t3_os_link_changed(काष्ठा adapter *adapter, पूर्णांक port_id, पूर्णांक link_status,
			पूर्णांक speed, पूर्णांक duplex, पूर्णांक fc);
व्योम t3_os_phymod_changed(काष्ठा adapter *adap, पूर्णांक port_id);
व्योम t3_os_link_fault(काष्ठा adapter *adapter, पूर्णांक port_id, पूर्णांक state);
व्योम t3_os_link_fault_handler(काष्ठा adapter *adapter, पूर्णांक port_id);

व्योम t3_sge_start(काष्ठा adapter *adap);
व्योम t3_sge_stop_dma(काष्ठा adapter *adap);
व्योम t3_sge_stop(काष्ठा adapter *adap);
व्योम t3_start_sge_समयrs(काष्ठा adapter *adap);
व्योम t3_stop_sge_समयrs(काष्ठा adapter *adap);
व्योम t3_मुक्त_sge_resources(काष्ठा adapter *adap);
व्योम t3_sge_err_पूर्णांकr_handler(काष्ठा adapter *adapter);
irq_handler_t t3_पूर्णांकr_handler(काष्ठा adapter *adap, पूर्णांक polling);
netdev_tx_t t3_eth_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक t3_mgmt_tx(काष्ठा adapter *adap, काष्ठा sk_buff *skb);
व्योम t3_update_qset_coalesce(काष्ठा sge_qset *qs, स्थिर काष्ठा qset_params *p);
पूर्णांक t3_sge_alloc_qset(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, पूर्णांक nports,
		      पूर्णांक irq_vec_idx, स्थिर काष्ठा qset_params *p,
		      पूर्णांक ntxq, काष्ठा net_device *dev,
		      काष्ठा netdev_queue *netdevq);
बाह्य काष्ठा workqueue_काष्ठा *cxgb3_wq;

पूर्णांक t3_get_edc_fw(काष्ठा cphy *phy, पूर्णांक edc_idx, पूर्णांक size);

#पूर्ण_अगर				/* __T3_ADAPTER_H__ */
