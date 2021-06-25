<शैली गुरु>
/*
 * This file is part of the Chelsio T4 PCI-E SR-IOV Virtual Function Ethernet
 * driver क्रम Linux.
 *
 * Copyright (c) 2009-2010 Chelsio Communications, Inc. All rights reserved.
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

/*
 * This file should not be included directly.  Include t4vf_common.h instead.
 */

#अगर_अघोषित __CXGB4VF_ADAPTER_H__
#घोषणा __CXGB4VF_ADAPTER_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>

#समावेश "../cxgb4/t4_hw.h"

/*
 * Constants of the implementation.
 */
क्रमागत अणु
	MAX_NPORTS	= 1,		/* max # of "ports" */
	MAX_PORT_QSETS	= 8,		/* max # of Queue Sets / "port" */
	MAX_ETH_QSETS	= MAX_NPORTS*MAX_PORT_QSETS,

	/*
	 * MSI-X पूर्णांकerrupt index usage.
	 */
	MSIX_FW		= 0,		/* MSI-X index क्रम firmware Q */
	MSIX_IQFLINT	= 1,		/* MSI-X index base क्रम Ingress Qs */
	MSIX_EXTRAS	= 1,
	MSIX_ENTRIES	= MAX_ETH_QSETS + MSIX_EXTRAS,

	/*
	 * The maximum number of Ingress and Egress Queues is determined by
	 * the maximum number of "Queue Sets" which we support plus any
	 * ancillary queues.  Each "Queue Set" requires one Ingress Queue
	 * क्रम RX Packet Ingress Event notअगरications and two Egress Queues क्रम
	 * a Free List and an Ethernet TX list.
	 */
	INGQ_EXTRAS	= 2,		/* firmware event queue and */
					/*   क्रमwarded पूर्णांकerrupts */
	MAX_INGQ	= MAX_ETH_QSETS+INGQ_EXTRAS,
	MAX_EGRQ	= MAX_ETH_QSETS*2,
पूर्ण;

/*
 * Forward काष्ठाure definition references.
 */
काष्ठा adapter;
काष्ठा sge_eth_rxq;
काष्ठा sge_rspq;

/*
 * Per-"port" inक्रमmation.  This is really per-Virtual Interface inक्रमmation
 * but the use of the "port" nomanclature makes it easier to go back and क्रमth
 * between the PF and VF drivers ...
 */
काष्ठा port_info अणु
	काष्ठा adapter *adapter;	/* our adapter */
	u32 vlan_id;			/* vlan id क्रम VST */
	u16 viid;			/* भव पूर्णांकerface ID */
	पूर्णांक xact_addr_filt;		/* index of our MAC address filter */
	u16 rss_size;			/* size of VI's RSS table slice */
	u8 pidx;			/* index पूर्णांकo adapter port[] */
	s8 mdio_addr;
	u8 port_type;			/* firmware port type */
	u8 mod_type;			/* firmware module type */
	u8 port_id;			/* physical port ID */
	u8 nqsets;			/* # of "Queue Sets" */
	u8 first_qset;			/* index of first "Queue Set" */
	काष्ठा link_config link_cfg;	/* physical port configuration */
पूर्ण;

/*
 * Scatter Gather Engine resources क्रम the "adapter".  Our ingress and egress
 * queues are organized पूर्णांकo "Queue Sets" with one ingress and one egress
 * queue per Queue Set.  These Queue Sets are aportionable between the "ports"
 * (Virtual Interfaces).  One extra ingress queue is used to receive
 * asynchronous messages from the firmware.  Note that the "Queue IDs" that we
 * use here are really "Relative Queue IDs" which are वापसed as part of the
 * firmware command to allocate queues.  These queue IDs are relative to the
 * असलolute Queue ID base of the section of the Queue ID space allocated to
 * the PF/VF.
 */

/*
 * SGE मुक्त-list queue state.
 */
काष्ठा rx_sw_desc;
काष्ठा sge_fl अणु
	अचिन्हित पूर्णांक avail;		/* # of available RX buffers */
	अचिन्हित पूर्णांक pend_cred;		/* new buffers since last FL DB ring */
	अचिन्हित पूर्णांक cidx;		/* consumer index */
	अचिन्हित पूर्णांक pidx;		/* producer index */
	अचिन्हित दीर्घ alloc_failed;	/* # of buffer allocation failures */
	अचिन्हित दीर्घ large_alloc_failed;
	अचिन्हित दीर्घ starving;		/* # of बार FL was found starving */

	/*
	 * Write-once/infrequently fields.
	 * -------------------------------
	 */

	अचिन्हित पूर्णांक cntxt_id;		/* SGE relative QID क्रम the मुक्त list */
	अचिन्हित पूर्णांक असल_id;		/* SGE असलolute QID क्रम the मुक्त list */
	अचिन्हित पूर्णांक size;		/* capacity of मुक्त list */
	काष्ठा rx_sw_desc *sdesc;	/* address of SW RX descriptor ring */
	__be64 *desc;			/* address of HW RX descriptor ring */
	dma_addr_t addr;		/* PCI bus address of hardware ring */
	व्योम __iomem *bar2_addr;	/* address of BAR2 Queue रेजिस्टरs */
	अचिन्हित पूर्णांक bar2_qid;		/* Queue ID क्रम BAR2 Queue रेजिस्टरs */
पूर्ण;

/*
 * An ingress packet gather list.
 */
काष्ठा pkt_gl अणु
	काष्ठा page_frag frags[MAX_SKB_FRAGS];
	व्योम *va;			/* भव address of first byte */
	अचिन्हित पूर्णांक nfrags;		/* # of fragments */
	अचिन्हित पूर्णांक tot_len;		/* total length of fragments */
पूर्ण;

प्रकार पूर्णांक (*rspq_handler_t)(काष्ठा sge_rspq *, स्थिर __be64 *,
			      स्थिर काष्ठा pkt_gl *);

/*
 * State क्रम an SGE Response Queue.
 */
काष्ठा sge_rspq अणु
	काष्ठा napi_काष्ठा napi;	/* NAPI scheduling control */
	स्थिर __be64 *cur_desc;		/* current descriptor in queue */
	अचिन्हित पूर्णांक cidx;		/* consumer index */
	u8 gen;				/* current generation bit */
	u8 next_पूर्णांकr_params;		/* holकरोff params क्रम next पूर्णांकerrupt */
	पूर्णांक offset;			/* offset पूर्णांकo current FL buffer */

	अचिन्हित पूर्णांक unhandled_irqs;	/* bogus पूर्णांकerrupts */

	/*
	 * Write-once/infrequently fields.
	 * -------------------------------
	 */

	u8 पूर्णांकr_params;			/* पूर्णांकerrupt holकरोff parameters */
	u8 pktcnt_idx;			/* पूर्णांकerrupt packet threshold */
	u8 idx;				/* queue index within its group */
	u16 cntxt_id;			/* SGE rel QID क्रम the response Q */
	u16 असल_id;			/* SGE असल QID क्रम the response Q */
	__be64 *desc;			/* address of hardware response ring */
	dma_addr_t phys_addr;		/* PCI bus address of ring */
	व्योम __iomem *bar2_addr;	/* address of BAR2 Queue रेजिस्टरs */
	अचिन्हित पूर्णांक bar2_qid;		/* Queue ID क्रम BAR2 Queue रेजिस्टरs */
	अचिन्हित पूर्णांक iqe_len;		/* entry size */
	अचिन्हित पूर्णांक size;		/* capcity of response Q */
	काष्ठा adapter *adapter;	/* our adapter */
	काष्ठा net_device *netdev;	/* associated net device */
	rspq_handler_t handler;		/* the handler क्रम this response Q */
पूर्ण;

/*
 * Ethernet queue statistics
 */
काष्ठा sge_eth_stats अणु
	अचिन्हित दीर्घ pkts;		/* # of ethernet packets */
	अचिन्हित दीर्घ lro_pkts;		/* # of LRO super packets */
	अचिन्हित दीर्घ lro_merged;	/* # of wire packets merged by LRO */
	अचिन्हित दीर्घ rx_cso;		/* # of Rx checksum offloads */
	अचिन्हित दीर्घ vlan_ex;		/* # of Rx VLAN extractions */
	अचिन्हित दीर्घ rx_drops;		/* # of packets dropped due to no mem */
पूर्ण;

/*
 * State क्रम an Ethernet Receive Queue.
 */
काष्ठा sge_eth_rxq अणु
	काष्ठा sge_rspq rspq;		/* Response Queue */
	काष्ठा sge_fl fl;		/* Free List */
	काष्ठा sge_eth_stats stats;	/* receive statistics */
पूर्ण;

/*
 * SGE Transmit Queue state.  This contains all of the resources associated
 * with the hardware status of a TX Queue which is a circular ring of hardware
 * TX Descriptors.  For convenience, it also contains a poपूर्णांकer to a parallel
 * "Software Descriptor" array but we करोn't know anything about it here other
 * than its type name.
 */
काष्ठा tx_desc अणु
	/*
	 * Egress Queues are measured in units of SGE_EQ_IDXSIZE by the
	 * hardware: Sizes, Producer and Consumer indices, etc.
	 */
	__be64 flit[SGE_EQ_IDXSIZE/माप(__be64)];
पूर्ण;
काष्ठा tx_sw_desc;
काष्ठा sge_txq अणु
	अचिन्हित पूर्णांक in_use;		/* # of in-use TX descriptors */
	अचिन्हित पूर्णांक size;		/* # of descriptors */
	अचिन्हित पूर्णांक cidx;		/* SW consumer index */
	अचिन्हित पूर्णांक pidx;		/* producer index */
	अचिन्हित दीर्घ stops;		/* # of बार queue has been stopped */
	अचिन्हित दीर्घ restarts;		/* # of queue restarts */

	/*
	 * Write-once/infrequently fields.
	 * -------------------------------
	 */

	अचिन्हित पूर्णांक cntxt_id;		/* SGE relative QID क्रम the TX Q */
	अचिन्हित पूर्णांक असल_id;		/* SGE असलolute QID क्रम the TX Q */
	काष्ठा tx_desc *desc;		/* address of HW TX descriptor ring */
	काष्ठा tx_sw_desc *sdesc;	/* address of SW TX descriptor ring */
	काष्ठा sge_qstat *stat;		/* queue status entry */
	dma_addr_t phys_addr;		/* PCI bus address of hardware ring */
	व्योम __iomem *bar2_addr;	/* address of BAR2 Queue रेजिस्टरs */
	अचिन्हित पूर्णांक bar2_qid;		/* Queue ID क्रम BAR2 Queue रेजिस्टरs */
पूर्ण;

/*
 * State क्रम an Ethernet Transmit Queue.
 */
काष्ठा sge_eth_txq अणु
	काष्ठा sge_txq q;		/* SGE TX Queue */
	काष्ठा netdev_queue *txq;	/* associated netdev TX queue */
	अचिन्हित दीर्घ tso;		/* # of TSO requests */
	अचिन्हित दीर्घ tx_cso;		/* # of TX checksum offloads */
	अचिन्हित दीर्घ vlan_ins;		/* # of TX VLAN insertions */
	अचिन्हित दीर्घ mapping_err;	/* # of I/O MMU packet mapping errors */
पूर्ण;

/*
 * The complete set of Scatter/Gather Engine resources.
 */
काष्ठा sge अणु
	/*
	 * Our "Queue Sets" ...
	 */
	काष्ठा sge_eth_txq ethtxq[MAX_ETH_QSETS];
	काष्ठा sge_eth_rxq ethrxq[MAX_ETH_QSETS];

	/*
	 * Extra ingress queues क्रम asynchronous firmware events and
	 * क्रमwarded पूर्णांकerrupts (when in MSI mode).
	 */
	काष्ठा sge_rspq fw_evtq ____cacheline_aligned_in_smp;

	काष्ठा sge_rspq पूर्णांकrq ____cacheline_aligned_in_smp;
	spinlock_t पूर्णांकrq_lock;

	/*
	 * State क्रम managing "starving Free Lists" -- Free Lists which have
	 * fallen below a certain threshold of buffers available to the
	 * hardware and attempts to refill them up to that threshold have
	 * failed.  We have a regular "slow tick" समयr process which will
	 * make periodic attempts to refill these starving Free Lists ...
	 */
	DECLARE_BITMAP(starving_fl, MAX_EGRQ);
	काष्ठा समयr_list rx_समयr;

	/*
	 * State क्रम cleaning up completed TX descriptors.
	 */
	काष्ठा समयr_list tx_समयr;

	/*
	 * Write-once/infrequently fields.
	 * -------------------------------
	 */

	u16 max_ethqsets;		/* # of available Ethernet queue sets */
	u16 ethqsets;			/* # of active Ethernet queue sets */
	u16 ethtxq_rover;		/* Tx queue to clean up next */
	u16 समयr_val[SGE_NTIMERS];	/* पूर्णांकerrupt holकरोff समयr array */
	u8 counter_val[SGE_NCOUNTERS];	/* पूर्णांकerrupt RX threshold array */

	/* Decoded Adapter Parameters.
	 */
	u32 fl_pg_order;		/* large page allocation size */
	u32 stat_len;			/* length of status page at ring end */
	u32 pktshअगरt;			/* padding between CPL & packet data */
	u32 fl_align;			/* response queue message alignment */
	u32 fl_starve_thres;		/* Free List starvation threshold */

	/*
	 * Reverse maps from Absolute Queue IDs to associated queue poपूर्णांकers.
	 * The असलolute Queue IDs are in a compact range which start at a
	 * [potentially large] Base Queue ID.  We perक्रमm the reverse map by
	 * first converting the Absolute Queue ID पूर्णांकo a Relative Queue ID by
	 * subtracting off the Base Queue ID and then use a Relative Queue ID
	 * indexed table to get the poपूर्णांकer to the corresponding software
	 * queue काष्ठाure.
	 */
	अचिन्हित पूर्णांक egr_base;
	अचिन्हित पूर्णांक ingr_base;
	व्योम *egr_map[MAX_EGRQ];
	काष्ठा sge_rspq *ingr_map[MAX_INGQ];
पूर्ण;

/*
 * Utility macros to convert Absolute- to Relative-Queue indices and Egress-
 * and Ingress-Queues.  The EQ_MAP() and IQ_MAP() macros which provide
 * poपूर्णांकers to Ingress- and Egress-Queues can be used as both L- and R-values
 */
#घोषणा EQ_IDX(s, असल_id) ((अचिन्हित पूर्णांक)((असल_id) - (s)->egr_base))
#घोषणा IQ_IDX(s, असल_id) ((अचिन्हित पूर्णांक)((असल_id) - (s)->ingr_base))

#घोषणा EQ_MAP(s, असल_id) ((s)->egr_map[EQ_IDX(s, असल_id)])
#घोषणा IQ_MAP(s, असल_id) ((s)->ingr_map[IQ_IDX(s, असल_id)])

/*
 * Macro to iterate across Queue Sets ("rxq" is a historic misnomer).
 */
#घोषणा क्रम_each_ethrxq(sge, iter) \
	क्रम (iter = 0; iter < (sge)->ethqsets; iter++)

काष्ठा hash_mac_addr अणु
	काष्ठा list_head list;
	u8 addr[ETH_ALEN];
	अचिन्हित पूर्णांक अगरace_mac;
पूर्ण;

काष्ठा mbox_list अणु
	काष्ठा list_head list;
पूर्ण;

/*
 * Per-"adapter" (Virtual Function) inक्रमmation.
 */
काष्ठा adapter अणु
	/* PCI resources */
	व्योम __iomem *regs;
	व्योम __iomem *bar2;
	काष्ठा pci_dev *pdev;
	काष्ठा device *pdev_dev;

	/* "adapter" resources */
	अचिन्हित दीर्घ रेजिस्टरed_device_map;
	अचिन्हित दीर्घ खोलो_device_map;
	अचिन्हित दीर्घ flags;
	काष्ठा adapter_params params;

	/* queue and पूर्णांकerrupt resources */
	काष्ठा अणु
		अचिन्हित लघु vec;
		अक्षर desc[22];
	पूर्ण msix_info[MSIX_ENTRIES];
	काष्ठा sge sge;

	/* Linux network device resources */
	काष्ठा net_device *port[MAX_NPORTS];
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक msg_enable;

	/* debugfs resources */
	काष्ठा dentry *debugfs_root;

	/* various locks */
	spinlock_t stats_lock;

	/* lock क्रम mailbox cmd list */
	spinlock_t mbox_lock;
	काष्ठा mbox_list mlist;

	/* support क्रम mailbox command/reply logging */
#घोषणा T4VF_OS_LOG_MBOX_CMDS 256
	काष्ठा mbox_cmd_log *mbox_log;

	/* list of MAC addresses in MPS Hash */
	काष्ठा list_head mac_hlist;
पूर्ण;

क्रमागत अणु /* adapter flags */
	CXGB4VF_FULL_INIT_DONE			= (1UL << 0),
	CXGB4VF_USING_MSI			= (1UL << 1),
	CXGB4VF_USING_MSIX			= (1UL << 2),
	CXGB4VF_QUEUES_BOUND			= (1UL << 3),
	CXGB4VF_ROOT_NO_RELAXED_ORDERING	= (1UL << 4),
	CXGB4VF_FW_OK				= (1UL << 5),
पूर्ण;

/*
 * The following रेजिस्टर पढ़ो/ग_लिखो routine definitions are required by
 * the common code.
 */

/**
 * t4_पढ़ो_reg - पढ़ो a HW रेजिस्टर
 * @adapter: the adapter
 * @reg_addr: the रेजिस्टर address
 *
 * Returns the 32-bit value of the given HW रेजिस्टर.
 */
अटल अंतरभूत u32 t4_पढ़ो_reg(काष्ठा adapter *adapter, u32 reg_addr)
अणु
	वापस पढ़ोl(adapter->regs + reg_addr);
पूर्ण

/**
 * t4_ग_लिखो_reg - ग_लिखो a HW रेजिस्टर
 * @adapter: the adapter
 * @reg_addr: the रेजिस्टर address
 * @val: the value to ग_लिखो
 *
 * Write a 32-bit value पूर्णांकo the given HW रेजिस्टर.
 */
अटल अंतरभूत व्योम t4_ग_लिखो_reg(काष्ठा adapter *adapter, u32 reg_addr, u32 val)
अणु
	ग_लिखोl(val, adapter->regs + reg_addr);
पूर्ण

#अगर_अघोषित पढ़ोq
अटल अंतरभूत u64 पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr) + ((u64)पढ़ोl(addr + 4) << 32);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोq(u64 val, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोl(val, addr);
	ग_लिखोl(val >> 32, addr + 4);
पूर्ण
#पूर्ण_अगर

/**
 * t4_पढ़ो_reg64 - पढ़ो a 64-bit HW रेजिस्टर
 * @adapter: the adapter
 * @reg_addr: the रेजिस्टर address
 *
 * Returns the 64-bit value of the given HW रेजिस्टर.
 */
अटल अंतरभूत u64 t4_पढ़ो_reg64(काष्ठा adapter *adapter, u32 reg_addr)
अणु
	वापस पढ़ोq(adapter->regs + reg_addr);
पूर्ण

/**
 * t4_ग_लिखो_reg64 - ग_लिखो a 64-bit HW रेजिस्टर
 * @adapter: the adapter
 * @reg_addr: the रेजिस्टर address
 * @val: the value to ग_लिखो
 *
 * Write a 64-bit value पूर्णांकo the given HW रेजिस्टर.
 */
अटल अंतरभूत व्योम t4_ग_लिखो_reg64(काष्ठा adapter *adapter, u32 reg_addr,
				  u64 val)
अणु
	ग_लिखोq(val, adapter->regs + reg_addr);
पूर्ण

/**
 * port_name - वापस the string name of a port
 * @adapter: the adapter
 * @pidx: the port index
 *
 * Return the string name of the selected port.
 */
अटल अंतरभूत स्थिर अक्षर *port_name(काष्ठा adapter *adapter, पूर्णांक pidx)
अणु
	वापस adapter->port[pidx]->name;
पूर्ण

/**
 * t4_os_set_hw_addr - store a port's MAC address in SW
 * @adapter: the adapter
 * @pidx: the port index
 * @hw_addr: the Ethernet address
 *
 * Store the Ethernet address of the given port in SW.  Called by the common
 * code when it retrieves a port's Ethernet address from EEPROM.
 */
अटल अंतरभूत व्योम t4_os_set_hw_addr(काष्ठा adapter *adapter, पूर्णांक pidx,
				     u8 hw_addr[])
अणु
	स_नकल(adapter->port[pidx]->dev_addr, hw_addr, ETH_ALEN);
पूर्ण

/**
 * netdev2pinfo - वापस the port_info काष्ठाure associated with a net_device
 * @dev: the netdev
 *
 * Return the काष्ठा port_info associated with a net_device
 */
अटल अंतरभूत काष्ठा port_info *netdev2pinfo(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

/**
 * adap2pinfo - वापस the port_info of a port
 * @adap: the adapter
 * @pidx: the port index
 *
 * Return the port_info काष्ठाure क्रम the adapter.
 */
अटल अंतरभूत काष्ठा port_info *adap2pinfo(काष्ठा adapter *adapter, पूर्णांक pidx)
अणु
	वापस netdev_priv(adapter->port[pidx]);
पूर्ण

/**
 * netdev2adap - वापस the adapter काष्ठाure associated with a net_device
 * @dev: the netdev
 *
 * Return the काष्ठा adapter associated with a net_device
 */
अटल अंतरभूत काष्ठा adapter *netdev2adap(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev2pinfo(dev)->adapter;
पूर्ण

/*
 * OS "Callback" function declarations.  These are functions that the OS code
 * is "contracted" to provide क्रम the common code.
 */
व्योम t4vf_os_link_changed(काष्ठा adapter *, पूर्णांक, पूर्णांक);
व्योम t4vf_os_porपंचांगod_changed(काष्ठा adapter *, पूर्णांक);

/*
 * SGE function prototype declarations.
 */
पूर्णांक t4vf_sge_alloc_rxq(काष्ठा adapter *, काष्ठा sge_rspq *, bool,
		       काष्ठा net_device *, पूर्णांक,
		       काष्ठा sge_fl *, rspq_handler_t);
पूर्णांक t4vf_sge_alloc_eth_txq(काष्ठा adapter *, काष्ठा sge_eth_txq *,
			   काष्ठा net_device *, काष्ठा netdev_queue *,
			   अचिन्हित पूर्णांक);
व्योम t4vf_मुक्त_sge_resources(काष्ठा adapter *);

netdev_tx_t t4vf_eth_xmit(काष्ठा sk_buff *, काष्ठा net_device *);
पूर्णांक t4vf_ethrx_handler(काष्ठा sge_rspq *, स्थिर __be64 *,
		       स्थिर काष्ठा pkt_gl *);

irq_handler_t t4vf_पूर्णांकr_handler(काष्ठा adapter *);
irqवापस_t t4vf_sge_पूर्णांकr_msix(पूर्णांक, व्योम *);

पूर्णांक t4vf_sge_init(काष्ठा adapter *);
व्योम t4vf_sge_start(काष्ठा adapter *);
व्योम t4vf_sge_stop(काष्ठा adapter *);

#पूर्ण_अगर /* __CXGB4VF_ADAPTER_H__ */
