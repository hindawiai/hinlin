<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/net/ethernet/ibm/ehea/ehea.h
 *
 *  eHEA ethernet device driver क्रम IBM eServer System p
 *
 *  (C) Copyright IBM Corp. 2006
 *
 *  Authors:
 *       Christoph Raisch <raisch@de.ibm.com>
 *       Jan-Bernd Themann <themann@de.ibm.com>
 *       Thomas Klein <tklein@de.ibm.com>
 */

#अगर_अघोषित __EHEA_H__
#घोषणा __EHEA_H__

#समावेश <linux/module.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <यंत्र/ibmebus.h>
#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME	"ehea"
#घोषणा DRV_VERSION	"EHEA_0107"

/* eHEA capability flags */
#घोषणा DLPAR_PORT_ADD_REM 1
#घोषणा DLPAR_MEM_ADD      2
#घोषणा DLPAR_MEM_REM      4
#घोषणा EHEA_CAPABILITIES  (DLPAR_PORT_ADD_REM | DLPAR_MEM_ADD | DLPAR_MEM_REM)

#घोषणा EHEA_MSG_DEFAULT (NETIF_MSG_LINK | NETIF_MSG_TIMER \
	| NETIF_MSG_RX_ERR | NETIF_MSG_TX_ERR)

#घोषणा EHEA_MAX_ENTRIES_RQ1 32767
#घोषणा EHEA_MAX_ENTRIES_RQ2 16383
#घोषणा EHEA_MAX_ENTRIES_RQ3 16383
#घोषणा EHEA_MAX_ENTRIES_SQ  32767
#घोषणा EHEA_MIN_ENTRIES_QP  127

#घोषणा EHEA_SMALL_QUEUES

#अगर_घोषित EHEA_SMALL_QUEUES
#घोषणा EHEA_MAX_CQE_COUNT      1023
#घोषणा EHEA_DEF_ENTRIES_SQ     1023
#घोषणा EHEA_DEF_ENTRIES_RQ1    1023
#घोषणा EHEA_DEF_ENTRIES_RQ2    1023
#घोषणा EHEA_DEF_ENTRIES_RQ3    511
#अन्यथा
#घोषणा EHEA_MAX_CQE_COUNT      4080
#घोषणा EHEA_DEF_ENTRIES_SQ     4080
#घोषणा EHEA_DEF_ENTRIES_RQ1    8160
#घोषणा EHEA_DEF_ENTRIES_RQ2    2040
#घोषणा EHEA_DEF_ENTRIES_RQ3    2040
#पूर्ण_अगर

#घोषणा EHEA_MAX_ENTRIES_EQ 20

#घोषणा EHEA_SG_SQ  2
#घोषणा EHEA_SG_RQ1 1
#घोषणा EHEA_SG_RQ2 0
#घोषणा EHEA_SG_RQ3 0

#घोषणा EHEA_MAX_PACKET_SIZE    9022	/* क्रम jumbo frames */
#घोषणा EHEA_RQ2_PKT_SIZE       2048
#घोषणा EHEA_L_PKT_SIZE         256	/* low latency */

/* Send completion संकेतing */

/* Protection Doमुख्य Identअगरier */
#घोषणा EHEA_PD_ID        0xaabcdeff

#घोषणा EHEA_RQ2_THRESHOLD 	   1
#घोषणा EHEA_RQ3_THRESHOLD	   4	/* use RQ3 threshold of 2048 bytes */

#घोषणा EHEA_SPEED_10G         10000
#घोषणा EHEA_SPEED_1G           1000
#घोषणा EHEA_SPEED_100M          100
#घोषणा EHEA_SPEED_10M            10
#घोषणा EHEA_SPEED_AUTONEG         0

/* Broadcast/Multicast registration types */
#घोषणा EHEA_BCMC_SCOPE_ALL	0x08
#घोषणा EHEA_BCMC_SCOPE_SINGLE	0x00
#घोषणा EHEA_BCMC_MULTICAST	0x04
#घोषणा EHEA_BCMC_BROADCAST	0x00
#घोषणा EHEA_BCMC_UNTAGGED	0x02
#घोषणा EHEA_BCMC_TAGGED	0x00
#घोषणा EHEA_BCMC_VLANID_ALL	0x01
#घोषणा EHEA_BCMC_VLANID_SINGLE	0x00

#घोषणा EHEA_CACHE_LINE          128

/* Memory Regions */
#घोषणा EHEA_MR_ACC_CTRL       0x00800000

#घोषणा EHEA_BUSMAP_START      0x8000000000000000ULL
#घोषणा EHEA_INVAL_ADDR        0xFFFFFFFFFFFFFFFFULL
#घोषणा EHEA_सूची_INDEX_SHIFT 13                   /* 8k Entries in 64k block */
#घोषणा EHEA_TOP_INDEX_SHIFT (EHEA_सूची_INDEX_SHIFT * 2)
#घोषणा EHEA_MAP_ENTRIES (1 << EHEA_सूची_INDEX_SHIFT)
#घोषणा EHEA_MAP_SIZE (0x10000)                   /* currently fixed map size */
#घोषणा EHEA_INDEX_MASK (EHEA_MAP_ENTRIES - 1)


#घोषणा EHEA_WATCH_DOG_TIMEOUT 10*HZ

/* utility functions */

व्योम ehea_dump(व्योम *adr, पूर्णांक len, अक्षर *msg);

#घोषणा EHEA_BMASK(pos, length) (((pos) << 16) + (length))

#घोषणा EHEA_BMASK_IBM(from, to) (((63 - to) << 16) + ((to) - (from) + 1))

#घोषणा EHEA_BMASK_SHIFTPOS(mask) (((mask) >> 16) & 0xffff)

#घोषणा EHEA_BMASK_MASK(mask) \
	(0xffffffffffffffffULL >> ((64 - (mask)) & 0xffff))

#घोषणा EHEA_BMASK_SET(mask, value) \
	((EHEA_BMASK_MASK(mask) & ((u64)(value))) << EHEA_BMASK_SHIFTPOS(mask))

#घोषणा EHEA_BMASK_GET(mask, value) \
	(EHEA_BMASK_MASK(mask) & (((u64)(value)) >> EHEA_BMASK_SHIFTPOS(mask)))

/*
 * Generic ehea page
 */
काष्ठा ehea_page अणु
	u8 entries[PAGE_SIZE];
पूर्ण;

/*
 * Generic queue in linux kernel भव memory
 */
काष्ठा hw_queue अणु
	u64 current_q_offset;		/* current queue entry */
	काष्ठा ehea_page **queue_pages;	/* array of pages beदीर्घing to queue */
	u32 qe_size;			/* queue entry size */
	u32 queue_length;      		/* queue length allocated in bytes */
	u32 pagesize;
	u32 toggle_state;		/* toggle flag - per page */
	u32 reserved;			/* 64 bit alignment */
पूर्ण;

/*
 * For pSeries this is a 64bit memory address where
 * I/O memory is mapped पूर्णांकo CPU address space
 */
काष्ठा h_epa अणु
	व्योम __iomem *addr;
पूर्ण;

काष्ठा h_epa_user अणु
	u64 addr;
पूर्ण;

काष्ठा h_epas अणु
	काष्ठा h_epa kernel;	/* kernel space accessible resource,
				   set to 0 अगर unused */
	काष्ठा h_epa_user user;	/* user space accessible resource
				   set to 0 अगर unused */
पूर्ण;

/*
 * Memory map data काष्ठाures
 */
काष्ठा ehea_dir_bmap
अणु
	u64 ent[EHEA_MAP_ENTRIES];
पूर्ण;
काष्ठा ehea_top_bmap
अणु
	काष्ठा ehea_dir_bmap *dir[EHEA_MAP_ENTRIES];
पूर्ण;
काष्ठा ehea_bmap
अणु
	काष्ठा ehea_top_bmap *top[EHEA_MAP_ENTRIES];
पूर्ण;

काष्ठा ehea_qp;
काष्ठा ehea_cq;
काष्ठा ehea_eq;
काष्ठा ehea_port;
काष्ठा ehea_av;

/*
 * Queue attributes passed to ehea_create_qp()
 */
काष्ठा ehea_qp_init_attr अणु
	/* input parameter */
	u32 qp_token;           /* queue token */
	u8 low_lat_rq1;
	u8 संकेतingtype;       /* cqe generation flag */
	u8 rq_count;            /* num of receive queues */
	u8 eqe_gen;             /* eqe generation flag */
	u16 max_nr_send_wqes;   /* max number of send wqes */
	u16 max_nr_rwqes_rq1;   /* max number of receive wqes */
	u16 max_nr_rwqes_rq2;
	u16 max_nr_rwqes_rq3;
	u8 wqe_size_enc_sq;
	u8 wqe_size_enc_rq1;
	u8 wqe_size_enc_rq2;
	u8 wqe_size_enc_rq3;
	u8 swqe_imm_data_len;   /* immediate data length क्रम swqes */
	u16 port_nr;
	u16 rq2_threshold;
	u16 rq3_threshold;
	u64 send_cq_handle;
	u64 recv_cq_handle;
	u64 aff_eq_handle;

	/* output parameter */
	u32 qp_nr;
	u16 act_nr_send_wqes;
	u16 act_nr_rwqes_rq1;
	u16 act_nr_rwqes_rq2;
	u16 act_nr_rwqes_rq3;
	u8 act_wqe_size_enc_sq;
	u8 act_wqe_size_enc_rq1;
	u8 act_wqe_size_enc_rq2;
	u8 act_wqe_size_enc_rq3;
	u32 nr_sq_pages;
	u32 nr_rq1_pages;
	u32 nr_rq2_pages;
	u32 nr_rq3_pages;
	u32 liobn_sq;
	u32 liobn_rq1;
	u32 liobn_rq2;
	u32 liobn_rq3;
पूर्ण;

/*
 * Event Queue attributes, passed as parameter
 */
काष्ठा ehea_eq_attr अणु
	u32 type;
	u32 max_nr_of_eqes;
	u8 eqe_gen;        /* generate eqe flag */
	u64 eq_handle;
	u32 act_nr_of_eqes;
	u32 nr_pages;
	u32 ist1;          /* Interrupt service token */
	u32 ist2;
	u32 ist3;
	u32 ist4;
पूर्ण;


/*
 * Event Queue
 */
काष्ठा ehea_eq अणु
	काष्ठा ehea_adapter *adapter;
	काष्ठा hw_queue hw_queue;
	u64 fw_handle;
	काष्ठा h_epas epas;
	spinlock_t spinlock;
	काष्ठा ehea_eq_attr attr;
पूर्ण;

/*
 * HEA Queues
 */
काष्ठा ehea_qp अणु
	काष्ठा ehea_adapter *adapter;
	u64 fw_handle;			/* QP handle क्रम firmware calls */
	काष्ठा hw_queue hw_squeue;
	काष्ठा hw_queue hw_rqueue1;
	काष्ठा hw_queue hw_rqueue2;
	काष्ठा hw_queue hw_rqueue3;
	काष्ठा h_epas epas;
	काष्ठा ehea_qp_init_attr init_attr;
पूर्ण;

/*
 * Completion Queue attributes
 */
काष्ठा ehea_cq_attr अणु
	/* input parameter */
	u32 max_nr_of_cqes;
	u32 cq_token;
	u64 eq_handle;

	/* output parameter */
	u32 act_nr_of_cqes;
	u32 nr_pages;
पूर्ण;

/*
 * Completion Queue
 */
काष्ठा ehea_cq अणु
	काष्ठा ehea_adapter *adapter;
	u64 fw_handle;
	काष्ठा hw_queue hw_queue;
	काष्ठा h_epas epas;
	काष्ठा ehea_cq_attr attr;
पूर्ण;

/*
 * Memory Region
 */
काष्ठा ehea_mr अणु
	काष्ठा ehea_adapter *adapter;
	u64 handle;
	u64 vaddr;
	u32 lkey;
पूर्ण;

/*
 * Port state inक्रमmation
 */
काष्ठा port_stats अणु
	पूर्णांक poll_receive_errors;
	पूर्णांक queue_stopped;
	पूर्णांक err_tcp_cksum;
	पूर्णांक err_ip_cksum;
	पूर्णांक err_frame_crc;
पूर्ण;

#घोषणा EHEA_IRQ_NAME_SIZE 20

/*
 * Queue SKB Array
 */
काष्ठा ehea_q_skb_arr अणु
	काष्ठा sk_buff **arr;		/* skb array क्रम queue */
	पूर्णांक len;                	/* array length */
	पूर्णांक index;			/* array index */
	पूर्णांक os_skbs;			/* rq2/rq3 only: outstanding skbs */
पूर्ण;

/*
 * Port resources
 */
काष्ठा ehea_port_res अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा port_stats p_stats;
	काष्ठा ehea_mr send_mr;       	/* send memory region */
	काष्ठा ehea_mr recv_mr;       	/* receive memory region */
	काष्ठा ehea_port *port;
	अक्षर पूर्णांक_recv_name[EHEA_IRQ_NAME_SIZE];
	अक्षर पूर्णांक_send_name[EHEA_IRQ_NAME_SIZE];
	काष्ठा ehea_qp *qp;
	काष्ठा ehea_cq *send_cq;
	काष्ठा ehea_cq *recv_cq;
	काष्ठा ehea_eq *eq;
	काष्ठा ehea_q_skb_arr rq1_skba;
	काष्ठा ehea_q_skb_arr rq2_skba;
	काष्ठा ehea_q_skb_arr rq3_skba;
	काष्ठा ehea_q_skb_arr sq_skba;
	पूर्णांक sq_skba_size;
	पूर्णांक swqe_refill_th;
	atomic_t swqe_avail;
	पूर्णांक swqe_ll_count;
	u32 swqe_id_counter;
	u64 tx_packets;
	u64 tx_bytes;
	u64 rx_packets;
	u64 rx_bytes;
	पूर्णांक sq_restart_flag;
पूर्ण;


#घोषणा EHEA_MAX_PORTS 16

#घोषणा EHEA_NUM_PORTRES_FW_HANDLES    6  /* QP handle, SendCQ handle,
					     RecvCQ handle, EQ handle,
					     SendMR handle, RecvMR handle */
#घोषणा EHEA_NUM_PORT_FW_HANDLES       1  /* EQ handle */
#घोषणा EHEA_NUM_ADAPTER_FW_HANDLES    2  /* MR handle, NEQ handle */

काष्ठा ehea_adapter अणु
	u64 handle;
	काष्ठा platक्रमm_device *ofdev;
	काष्ठा ehea_port *port[EHEA_MAX_PORTS];
	काष्ठा ehea_eq *neq;       /* notअगरication event queue */
	काष्ठा tasklet_काष्ठा neq_tasklet;
	काष्ठा ehea_mr mr;
	u32 pd;                    /* protection करोमुख्य */
	u64 max_mc_mac;            /* max number of multicast mac addresses */
	पूर्णांक active_ports;
	काष्ठा list_head list;
पूर्ण;


काष्ठा ehea_mc_list अणु
	काष्ठा list_head list;
	u64 macaddr;
पूर्ण;

/* kdump support */
काष्ठा ehea_fw_handle_entry अणु
	u64 adh;               /* Adapter Handle */
	u64 fwh;               /* Firmware Handle */
पूर्ण;

काष्ठा ehea_fw_handle_array अणु
	काष्ठा ehea_fw_handle_entry *arr;
	पूर्णांक num_entries;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा ehea_bcmc_reg_entry अणु
	u64 adh;               /* Adapter Handle */
	u32 port_id;           /* Logical Port Id */
	u8 reg_type;           /* Registration Type */
	u64 macaddr;
पूर्ण;

काष्ठा ehea_bcmc_reg_array अणु
	काष्ठा ehea_bcmc_reg_entry *arr;
	पूर्णांक num_entries;
	spinlock_t lock;
पूर्ण;

#घोषणा EHEA_PORT_UP 1
#घोषणा EHEA_PORT_DOWN 0
#घोषणा EHEA_PHY_LINK_UP 1
#घोषणा EHEA_PHY_LINK_DOWN 0
#घोषणा EHEA_MAX_PORT_RES 16
काष्ठा ehea_port अणु
	काष्ठा ehea_adapter *adapter;	 /* adapter that owns this port */
	काष्ठा net_device *netdev;
	काष्ठा rtnl_link_stats64 stats;
	काष्ठा ehea_port_res port_res[EHEA_MAX_PORT_RES];
	काष्ठा platक्रमm_device  ofdev; /* Open Firmware Device */
	काष्ठा ehea_mc_list *mc_list;	 /* Multicast MAC addresses */
	काष्ठा ehea_eq *qp_eq;
	काष्ठा work_काष्ठा reset_task;
	काष्ठा delayed_work stats_work;
	काष्ठा mutex port_lock;
	अक्षर पूर्णांक_aff_name[EHEA_IRQ_NAME_SIZE];
	पूर्णांक allmulti;			 /* Indicates IFF_ALLMULTI state */
	पूर्णांक promisc;		 	 /* Indicates IFF_PROMISC state */
	पूर्णांक num_mcs;
	पूर्णांक resets;
	अचिन्हित दीर्घ flags;
	u64 mac_addr;
	u32 logical_port_id;
	u32 port_speed;
	u32 msg_enable;
	u32 sig_comp_iv;
	u32 state;
	u8 phy_link;
	u8 full_duplex;
	u8 स्वतःneg;
	u8 num_def_qps;
	रुको_queue_head_t swqe_avail_wq;
	रुको_queue_head_t restart_wq;
पूर्ण;

काष्ठा port_res_cfg अणु
	पूर्णांक max_entries_rcq;
	पूर्णांक max_entries_scq;
	पूर्णांक max_entries_sq;
	पूर्णांक max_entries_rq1;
	पूर्णांक max_entries_rq2;
	पूर्णांक max_entries_rq3;
पूर्ण;

क्रमागत ehea_flag_bits अणु
	__EHEA_STOP_XFER,
	__EHEA_DISABLE_PORT_RESET
पूर्ण;

व्योम ehea_set_ethtool_ops(काष्ठा net_device *netdev);
पूर्णांक ehea_sense_port_attr(काष्ठा ehea_port *port);
पूर्णांक ehea_set_portspeed(काष्ठा ehea_port *port, u32 port_speed);

#पूर्ण_अगर	/* __EHEA_H__ */
