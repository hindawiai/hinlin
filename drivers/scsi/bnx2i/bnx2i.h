<शैली गुरु>
/* bnx2i.h: QLogic NetXtreme II iSCSI driver.
 *
 * Copyright (c) 2006 - 2013 Broadcom Corporation
 * Copyright (c) 2007, 2008 Red Hat, Inc.  All rights reserved.
 * Copyright (c) 2007, 2008 Mike Christie
 * Copyright (c) 2014, QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Anil Veerabhadrappa (anilgv@broadcom.com)
 * Previously Maपूर्णांकained by: Eddie Wai (eddie.wai@broadcom.com)
 * Maपूर्णांकained by: QLogic-Storage-Upstream@qlogic.com
 */

#अगर_अघोषित _BNX2I_H_
#घोषणा _BNX2I_H_

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/in.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/completion.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/cpu.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <scsi/libiscsi.h>
#समावेश <scsi/scsi_transport_iscsi.h>

#समावेश "../../net/ethernet/broadcom/cnic_if.h"
#समावेश "57xx_iscsi_hsi.h"
#समावेश "57xx_iscsi_constants.h"

#समावेश "../../net/ethernet/broadcom/bnx2x/bnx2x_mfw_req.h"

#घोषणा BNX2_ISCSI_DRIVER_NAME		"bnx2i"

#घोषणा BNX2I_MAX_ADAPTERS		8

#घोषणा ISCSI_MAX_CONNS_PER_HBA		128
#घोषणा ISCSI_MAX_SESS_PER_HBA		ISCSI_MAX_CONNS_PER_HBA
#घोषणा ISCSI_MAX_CMDS_PER_SESS		128

/* Total active commands across all connections supported by devices */
#घोषणा ISCSI_MAX_CMDS_PER_HBA_5708	(28 * (ISCSI_MAX_CMDS_PER_SESS - 1))
#घोषणा ISCSI_MAX_CMDS_PER_HBA_5709	(128 * (ISCSI_MAX_CMDS_PER_SESS - 1))
#घोषणा ISCSI_MAX_CMDS_PER_HBA_57710	(256 * (ISCSI_MAX_CMDS_PER_SESS - 1))

#घोषणा ISCSI_MAX_BDS_PER_CMD		32

#घोषणा MAX_PAGES_PER_CTRL_STRUCT_POOL	8
#घोषणा BNX2I_RESERVED_SLOW_PATH_CMD_SLOTS	4

#घोषणा BNX2X_DB_SHIFT			3

/* 5706/08 hardware has limit on maximum buffer size per BD it can handle */
#घोषणा MAX_BD_LENGTH			65535
#घोषणा BD_SPLIT_SIZE			32768

/* min, max & शेष values क्रम SQ/RQ/CQ size, configurable via' modparam */
#घोषणा BNX2I_SQ_WQES_MIN		16
#घोषणा BNX2I_570X_SQ_WQES_MAX		128
#घोषणा BNX2I_5770X_SQ_WQES_MAX		512
#घोषणा BNX2I_570X_SQ_WQES_DEFAULT	128
#घोषणा BNX2I_5770X_SQ_WQES_DEFAULT	128

#घोषणा BNX2I_570X_CQ_WQES_MAX 		128
#घोषणा BNX2I_5770X_CQ_WQES_MAX 	512

#घोषणा BNX2I_RQ_WQES_MIN 		16
#घोषणा BNX2I_RQ_WQES_MAX 		32
#घोषणा BNX2I_RQ_WQES_DEFAULT 		16

/* CCELLs per conn */
#घोषणा BNX2I_CCELLS_MIN		16
#घोषणा BNX2I_CCELLS_MAX		96
#घोषणा BNX2I_CCELLS_DEFAULT		64

#घोषणा ITT_INVALID_SIGNATURE		0xFFFF

#घोषणा ISCSI_CMD_CLEANUP_TIMEOUT	100

#घोषणा BNX2I_CONN_CTX_BUF_SIZE		16384

#घोषणा BNX2I_SQ_WQE_SIZE		64
#घोषणा BNX2I_RQ_WQE_SIZE		256
#घोषणा BNX2I_CQE_SIZE			64

#घोषणा MB_KERNEL_CTX_SHIFT		8
#घोषणा MB_KERNEL_CTX_SIZE		(1 << MB_KERNEL_CTX_SHIFT)

#घोषणा CTX_SHIFT			7
#घोषणा GET_CID_NUM(cid_addr)		((cid_addr) >> CTX_SHIFT)

#घोषणा CTX_OFFSET 			0x10000
#घोषणा MAX_CID_CNT			0x4000

#घोषणा BNX2I_570X_PAGE_SIZE_DEFAULT	4096

/* 5709 context रेजिस्टरs */
#घोषणा BNX2_MQ_CONFIG2			0x00003d00
#घोषणा BNX2_MQ_CONFIG2_CONT_SZ		(0x7L<<4)
#घोषणा BNX2_MQ_CONFIG2_FIRST_L4L5	(0x1fL<<8)

/* 57710's BAR2 is mapped to करोorbell रेजिस्टरs */
#घोषणा BNX2X_DOORBELL_PCI_BAR		2
#घोषणा BNX2X_MAX_CQS			8

#घोषणा CNIC_ARM_CQE			1
#घोषणा CNIC_ARM_CQE_FP			2
#घोषणा CNIC_DISARM_CQE			0

#घोषणा REG_RD(__hba, offset)				\
		पढ़ोl(__hba->regview + offset)
#घोषणा REG_WR(__hba, offset, val)			\
		ग_लिखोl(val, __hba->regview + offset)

#अगर_घोषित CONFIG_32BIT
#घोषणा GET_STATS_64(__hba, dst, field)				\
	करो अणु							\
		spin_lock_bh(&__hba->stat_lock);		\
		dst->field##_lo = __hba->stats.field##_lo;	\
		dst->field##_hi = __hba->stats.field##_hi;	\
		spin_unlock_bh(&__hba->stat_lock);		\
	पूर्ण जबतक (0)

#घोषणा ADD_STATS_64(__hba, field, len)				\
	करो अणु							\
		अगर (spin_trylock(&__hba->stat_lock)) अणु		\
			अगर (__hba->stats.field##_lo + len <	\
			    __hba->stats.field##_lo)		\
				__hba->stats.field##_hi++;	\
			__hba->stats.field##_lo += len;		\
			spin_unlock(&__hba->stat_lock);		\
		पूर्ण						\
	पूर्ण जबतक (0)

#अन्यथा
#घोषणा GET_STATS_64(__hba, dst, field)				\
	करो अणु							\
		u64 val, *out;					\
								\
		val = __hba->bnx2i_stats.field;			\
		out = (u64 *)&__hba->stats.field##_lo;		\
		*out = cpu_to_le64(val);			\
		out = (u64 *)&dst->field##_lo;			\
		*out = cpu_to_le64(val);			\
	पूर्ण जबतक (0)

#घोषणा ADD_STATS_64(__hba, field, len)				\
	करो अणु							\
		__hba->bnx2i_stats.field += len;		\
	पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * काष्ठा generic_pdu_resc - login pdu resource काष्ठाure
 *
 * @req_buf:            driver buffer used to stage payload associated with
 *                      the login request
 * @req_dma_addr:       dma address क्रम iscsi login request payload buffer
 * @req_buf_size:       actual login request payload length
 * @req_wr_ptr:         poपूर्णांकer पूर्णांकo login request buffer when next data is
 *                      to be written
 * @resp_hdr:           iscsi header where iscsi login response header is to
 *                      be recreated
 * @resp_buf:           buffer to stage login response payload
 * @resp_dma_addr:      login response payload buffer dma address
 * @resp_buf_size:      login response paylod length
 * @resp_wr_ptr:        poपूर्णांकer पूर्णांकo login response buffer when next data is
 *                      to be written
 * @req_bd_tbl:         iscsi login request payload BD table
 * @req_bd_dma:         login request BD table dma address
 * @resp_bd_tbl:        iscsi login response payload BD table
 * @resp_bd_dma:        login request BD table dma address
 *
 * following काष्ठाure defines buffer info क्रम generic pdus such as iSCSI Login,
 *	Logout and NOP
 */
काष्ठा generic_pdu_resc अणु
	अक्षर *req_buf;
	dma_addr_t req_dma_addr;
	u32 req_buf_size;
	अक्षर *req_wr_ptr;
	काष्ठा iscsi_hdr resp_hdr;
	अक्षर *resp_buf;
	dma_addr_t resp_dma_addr;
	u32 resp_buf_size;
	अक्षर *resp_wr_ptr;
	अक्षर *req_bd_tbl;
	dma_addr_t req_bd_dma;
	अक्षर *resp_bd_tbl;
	dma_addr_t resp_bd_dma;
पूर्ण;


/**
 * काष्ठा bd_resc_page - tracks DMA'able memory allocated क्रम BD tables
 *
 * @link:               list head to link elements
 * @max_ptrs:           maximun poपूर्णांकers that can be stored in this page
 * @num_valid:          number of poपूर्णांकer valid in this page
 * @page:               base addess क्रम page poपूर्णांकer array
 *
 * काष्ठाure to track DMA'able memory allocated क्रम command BD tables
 */
काष्ठा bd_resc_page अणु
	काष्ठा list_head link;
	u32 max_ptrs;
	u32 num_valid;
	व्योम *page[1];
पूर्ण;


/**
 * काष्ठा io_bdt - I/O buffer destricptor table
 *
 * @bd_tbl:             BD table's भव address
 * @bd_tbl_dma:         BD table's dma address
 * @bd_valid:           num valid BD entries
 *
 * IO BD table
 */
काष्ठा io_bdt अणु
	काष्ठा iscsi_bd *bd_tbl;
	dma_addr_t bd_tbl_dma;
	u16 bd_valid;
पूर्ण;


/**
 * bnx2i_cmd - iscsi command काष्ठाure
 *
 * @hdr:                iSCSI header
 * @conn:               iscsi_conn poपूर्णांकer
 * @scsi_cmd:           SCSI-ML task poपूर्णांकer corresponding to this iscsi cmd
 * @sg:                 SG list
 * @io_tbl:             buffer descriptor (BD) table
 * @bd_tbl_dma:         buffer descriptor (BD) table's dma address
 * @req:                bnx2i specअगरic command request काष्ठा
 */
काष्ठा bnx2i_cmd अणु
	काष्ठा iscsi_hdr hdr;
	काष्ठा bnx2i_conn *conn;
	काष्ठा scsi_cmnd *scsi_cmd;
	काष्ठा scatterlist *sg;
	काष्ठा io_bdt io_tbl;
	dma_addr_t bd_tbl_dma;
	काष्ठा bnx2i_cmd_request req;
पूर्ण;


/**
 * काष्ठा bnx2i_conn - iscsi connection काष्ठाure
 *
 * @cls_conn:              poपूर्णांकer to iscsi cls conn
 * @hba:                   adapter काष्ठाure poपूर्णांकer
 * @iscsi_conn_cid:        iscsi conn id
 * @fw_cid:                firmware iscsi context id
 * @ep:                    endpoपूर्णांक काष्ठाure poपूर्णांकer
 * @gen_pdu:               login/nopout/logout pdu resources
 * @violation_notअगरied:    bit mask used to track iscsi error/warning messages
 *                         alपढ़ोy prपूर्णांकed out
 * @work_cnt:              keeps track of the number of outstanding work
 *
 * iSCSI connection काष्ठाure
 */
काष्ठा bnx2i_conn अणु
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा bnx2i_hba *hba;
	काष्ठा completion cmd_cleanup_cmpl;

	u32 iscsi_conn_cid;
#घोषणा BNX2I_CID_RESERVED	0x5AFF
	u32 fw_cid;

	काष्ठा समयr_list poll_समयr;
	/*
	 * Queue Pair (QP) related काष्ठाure elements.
	 */
	काष्ठा bnx2i_endpoपूर्णांक *ep;

	/*
	 * Buffer क्रम login negotiation process
	 */
	काष्ठा generic_pdu_resc gen_pdu;
	u64 violation_notअगरied;

	atomic_t work_cnt;
पूर्ण;



/**
 * काष्ठा iscsi_cid_queue - Per adapter iscsi cid queue
 *
 * @cid_que_base:           queue base memory
 * @cid_que:                queue memory poपूर्णांकer
 * @cid_q_prod_idx:         produce index
 * @cid_q_cons_idx:         consumer index
 * @cid_q_max_idx:          max index. used to detect wrap around condition
 * @cid_मुक्त_cnt:           queue size
 * @conn_cid_tbl:           iscsi cid to conn काष्ठाure mapping table
 *
 * Per adapter iSCSI CID Queue
 */
काष्ठा iscsi_cid_queue अणु
	व्योम *cid_que_base;
	u32 *cid_que;
	u32 cid_q_prod_idx;
	u32 cid_q_cons_idx;
	u32 cid_q_max_idx;
	u32 cid_मुक्त_cnt;
	काष्ठा bnx2i_conn **conn_cid_tbl;
पूर्ण;


काष्ठा bnx2i_stats_info अणु
	u64 rx_pdus;
	u64 rx_bytes;
	u64 tx_pdus;
	u64 tx_bytes;
पूर्ण;


/**
 * काष्ठा bnx2i_hba - bnx2i adapter काष्ठाure
 *
 * @link:                  list head to link elements
 * @cnic:                  poपूर्णांकer to cnic device
 * @pcidev:                poपूर्णांकer to pci dev
 * @netdev:                poपूर्णांकer to netdev काष्ठाure
 * @regview:               mapped PCI रेजिस्टर space
 * @age:                   age, incremented by every recovery
 * @cnic_dev_type:         cnic device type, 5706/5708/5709/57710
 * @mail_queue_access:     mailbox queue access mode, applicable to 5709 only
 * @reg_with_cnic:         indicates whether the device is रेजिस्टर with CNIC
 * @adapter_state:         adapter state, UP, GOING_DOWN, LINK_DOWN
 * @mtu_supported:         Ethernet MTU supported
 * @shost:                 scsi host poपूर्णांकer
 * @max_sqes:              SQ size
 * @max_rqes:              RQ size
 * @max_cqes:              CQ size
 * @num_ccell:             number of command cells per connection
 * @ofld_conns_active:     active connection list
 * @eh_रुको:               रुको queue क्रम the endpoपूर्णांक to shutकरोwn
 * @max_active_conns:      max offload connections supported by this device
 * @cid_que:               iscsi cid queue
 * @ep_rdwr_lock:          पढ़ो / ग_लिखो lock to synchronize various ep lists
 * @ep_ofld_list:          connection list क्रम pending offload completion
 * @ep_active_list:        connection list क्रम active offload endpoपूर्णांकs
 * @ep_destroy_list:       connection list क्रम pending offload completion
 * @mp_bd_tbl:             BD table to be used with middle path requests
 * @mp_bd_dma:             DMA address of 'mp_bd_tbl' memory buffer
 * @dummy_buffer:          Dummy buffer to be used with zero length scsicmd reqs
 * @dummy_buf_dma:         DMA address of 'dummy_buffer' memory buffer
 * @lock:              	   lock to synchonize access to hba काष्ठाure
 * @hba_shutकरोwn_पंचांगo:      Timeout value to shutकरोwn each connection
 * @conn_tearकरोwn_पंचांगo:     Timeout value to tear करोwn each connection
 * @conn_ctx_destroy_पंचांगo:  Timeout value to destroy context of each connection
 * @pci_did:               PCI device ID
 * @pci_vid:               PCI venकरोr ID
 * @pci_sdid:              PCI subप्रणाली device ID
 * @pci_svid:              PCI subप्रणाली venकरोr ID
 * @pci_func:              PCI function number in प्रणाली pci tree
 * @pci_devno:             PCI device number in प्रणाली pci tree
 * @num_wqe_sent:          statistic counter, total wqe's sent
 * @num_cqe_rcvd:          statistic counter, total cqe's received
 * @num_पूर्णांकr_claimed:      statistic counter, total पूर्णांकerrupts claimed
 * @link_changed_count:    statistic counter, num of link change notअगरications
 *                         received
 * @ipaddr_changed_count:  statistic counter, num बार IP address changed जबतक
 *                         at least one connection is offloaded
 * @num_sess_खोलोed:       statistic counter, total num sessions खोलोed
 * @num_conn_खोलोed:       statistic counter, total num conns खोलोed on this hba
 * @ctx_ccell_tasks:       captures number of ccells and tasks supported by
 *                         currently offloaded connection, used to decode
 *                         context memory
 * @stat_lock:		   spin lock used by the statistic collector (32 bit)
 * @stats:		   local iSCSI statistic collection place holder
 *
 * Adapter Data Structure
 */
काष्ठा bnx2i_hba अणु
	काष्ठा list_head link;
	काष्ठा cnic_dev *cnic;
	काष्ठा pci_dev *pcidev;
	काष्ठा net_device *netdev;
	व्योम __iomem *regview;
	resource_माप_प्रकार reg_base;

	u32 age;
	अचिन्हित दीर्घ cnic_dev_type;
		#घोषणा BNX2I_NX2_DEV_5706		0x0
		#घोषणा BNX2I_NX2_DEV_5708		0x1
		#घोषणा BNX2I_NX2_DEV_5709		0x2
		#घोषणा BNX2I_NX2_DEV_57710		0x3
	u32 mail_queue_access;
		#घोषणा BNX2I_MQ_KERNEL_MODE		0x0
		#घोषणा BNX2I_MQ_KERNEL_BYPASS_MODE	0x1
		#घोषणा BNX2I_MQ_BIN_MODE		0x2
	अचिन्हित दीर्घ  reg_with_cnic;
		#घोषणा BNX2I_CNIC_REGISTERED		1

	अचिन्हित दीर्घ  adapter_state;
		#घोषणा ADAPTER_STATE_UP		0
		#घोषणा ADAPTER_STATE_GOING_DOWN	1
		#घोषणा ADAPTER_STATE_LINK_DOWN		2
		#घोषणा ADAPTER_STATE_INIT_FAILED	31
	अचिन्हित पूर्णांक mtu_supported;
		#घोषणा BNX2I_MAX_MTU_SUPPORTED		9000

	काष्ठा Scsi_Host *shost;

	u32 max_sqes;
	u32 max_rqes;
	u32 max_cqes;
	u32 num_ccell;

	पूर्णांक ofld_conns_active;
	रुको_queue_head_t eh_रुको;

	पूर्णांक max_active_conns;
	काष्ठा iscsi_cid_queue cid_que;

	rwlock_t ep_rdwr_lock;
	काष्ठा list_head ep_ofld_list;
	काष्ठा list_head ep_active_list;
	काष्ठा list_head ep_destroy_list;

	/*
	 * BD table to be used with MP (Middle Path requests.
	 */
	अक्षर *mp_bd_tbl;
	dma_addr_t mp_bd_dma;
	अक्षर *dummy_buffer;
	dma_addr_t dummy_buf_dma;

	spinlock_t lock;	/* protects hba काष्ठाure access */
	काष्ठा mutex net_dev_lock;/* sync net device access */

	पूर्णांक hba_shutकरोwn_पंचांगo;
	पूर्णांक conn_tearकरोwn_पंचांगo;
	पूर्णांक conn_ctx_destroy_पंचांगo;
	/*
	 * PCI related info.
	 */
	u16 pci_did;
	u16 pci_vid;
	u16 pci_sdid;
	u16 pci_svid;
	u16 pci_func;
	u16 pci_devno;

	/*
	 * Following are a bunch of statistics useful during development
	 * and later stage क्रम score boarding.
	 */
	u32 num_wqe_sent;
	u32 num_cqe_rcvd;
	u32 num_पूर्णांकr_claimed;
	u32 link_changed_count;
	u32 ipaddr_changed_count;
	u32 num_sess_खोलोed;
	u32 num_conn_खोलोed;
	अचिन्हित पूर्णांक ctx_ccell_tasks;

#अगर_घोषित CONFIG_32BIT
	spinlock_t stat_lock;
#पूर्ण_अगर
	काष्ठा bnx2i_stats_info bnx2i_stats;
	काष्ठा iscsi_stats_info stats;
पूर्ण;


/*******************************************************************************
 * 	QP [ SQ / RQ / CQ ] info.
 ******************************************************************************/

/*
 * SQ/RQ/CQ generic काष्ठाure definition
 */
काष्ठा 	sqe अणु
	u8 sqe_byte[BNX2I_SQ_WQE_SIZE];
पूर्ण;

काष्ठा 	rqe अणु
	u8 rqe_byte[BNX2I_RQ_WQE_SIZE];
पूर्ण;

काष्ठा 	cqe अणु
	u8 cqe_byte[BNX2I_CQE_SIZE];
पूर्ण;


क्रमागत अणु
#अगर defined(__LITTLE_ENDIAN)
	CNIC_EVENT_COAL_INDEX	= 0x0,
	CNIC_SEND_DOORBELL	= 0x4,
	CNIC_EVENT_CQ_ARM	= 0x7,
	CNIC_RECV_DOORBELL	= 0x8
#या_अगर defined(__BIG_ENDIAN)
	CNIC_EVENT_COAL_INDEX	= 0x2,
	CNIC_SEND_DOORBELL	= 0x6,
	CNIC_EVENT_CQ_ARM	= 0x4,
	CNIC_RECV_DOORBELL	= 0xa
#पूर्ण_अगर
पूर्ण;


/*
 * CQ DB
 */
काष्ठा bnx2x_iscsi_cq_pend_cmpl अणु
	/* CQ producer, updated by Ustorm */
	u16 ustrom_prod;
	/* CQ pending completion counter */
	u16 pend_cntr;
पूर्ण;


काष्ठा bnx2i_5771x_cq_db अणु
	काष्ठा bnx2x_iscsi_cq_pend_cmpl qp_pend_cmpl[BNX2X_MAX_CQS];
	/* CQ pending completion ITT array */
	u16 itt[BNX2X_MAX_CQS];
	/* Cstorm CQ sequence to notअगरy array, updated by driver */;
	u16 sqn[BNX2X_MAX_CQS];
	u32 reserved[4] /* 16 byte allignment */;
पूर्ण;


काष्ठा bnx2i_5771x_sq_rq_db अणु
	u16 prod_idx;
	u8 reserved0[62]; /* Pad काष्ठाure size to 64 bytes */
पूर्ण;


काष्ठा bnx2i_5771x_dbell_hdr अणु
	u8 header;
	/* 1 क्रम rx करोorbell, 0 क्रम tx करोorbell */
#घोषणा B577XX_DOORBELL_HDR_RX				(0x1<<0)
#घोषणा B577XX_DOORBELL_HDR_RX_SHIFT			0
	/* 0 क्रम normal करोorbell, 1 क्रम advertise wnd करोorbell */
#घोषणा B577XX_DOORBELL_HDR_DB_TYPE			(0x1<<1)
#घोषणा B577XX_DOORBELL_HDR_DB_TYPE_SHIFT		1
	/* rdma tx only: DPM transaction size specअगरier (64/128/256/512B) */
#घोषणा B577XX_DOORBELL_HDR_DPM_SIZE			(0x3<<2)
#घोषणा B577XX_DOORBELL_HDR_DPM_SIZE_SHIFT		2
	/* connection type */
#घोषणा B577XX_DOORBELL_HDR_CONN_TYPE			(0xF<<4)
#घोषणा B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT		4
पूर्ण;

काष्ठा bnx2i_5771x_dbell अणु
	काष्ठा bnx2i_5771x_dbell_hdr dbell;
	u8 pad[3];

पूर्ण;

/**
 * काष्ठा qp_info - QP (share queue region) atrributes काष्ठाure
 *
 * @ctx_base:           ioremapped pci रेजिस्टर base to access करोorbell रेजिस्टर
 *                      pertaining to this offloaded connection
 * @sq_virt:            भव address of send queue (SQ) region
 * @sq_phys:            DMA address of SQ memory region
 * @sq_mem_size:        SQ size
 * @sq_prod_qe:         SQ producer entry poपूर्णांकer
 * @sq_cons_qe:         SQ consumer entry poपूर्णांकer
 * @sq_first_qe:        भव address of first entry in SQ
 * @sq_last_qe:         भव address of last entry in SQ
 * @sq_prod_idx:        SQ producer index
 * @sq_cons_idx:        SQ consumer index
 * @sqe_left:           number sq entry left
 * @sq_pgtbl_virt:      page table describing buffer consituting SQ region
 * @sq_pgtbl_phys:      dma address of 'sq_pgtbl_virt'
 * @sq_pgtbl_size:      SQ page table size
 * @cq_virt:            भव address of completion queue (CQ) region
 * @cq_phys:            DMA address of RQ memory region
 * @cq_mem_size:        CQ size
 * @cq_prod_qe:         CQ producer entry poपूर्णांकer
 * @cq_cons_qe:         CQ consumer entry poपूर्णांकer
 * @cq_first_qe:        भव address of first entry in CQ
 * @cq_last_qe:         भव address of last entry in CQ
 * @cq_prod_idx:        CQ producer index
 * @cq_cons_idx:        CQ consumer index
 * @cqe_left:           number cq entry left
 * @cqe_size:           size of each CQ entry
 * @cqe_exp_seq_sn:     next expected CQE sequence number
 * @cq_pgtbl_virt:      page table describing buffer consituting CQ region
 * @cq_pgtbl_phys:      dma address of 'cq_pgtbl_virt'
 * @cq_pgtbl_size:    	CQ page table size
 * @rq_virt:            भव address of receive queue (RQ) region
 * @rq_phys:            DMA address of RQ memory region
 * @rq_mem_size:        RQ size
 * @rq_prod_qe:         RQ producer entry poपूर्णांकer
 * @rq_cons_qe:         RQ consumer entry poपूर्णांकer
 * @rq_first_qe:        भव address of first entry in RQ
 * @rq_last_qe:         भव address of last entry in RQ
 * @rq_prod_idx:        RQ producer index
 * @rq_cons_idx:        RQ consumer index
 * @rqe_left:           number rq entry left
 * @rq_pgtbl_virt:      page table describing buffer consituting RQ region
 * @rq_pgtbl_phys:      dma address of 'rq_pgtbl_virt'
 * @rq_pgtbl_size:      RQ page table size
 *
 * queue pair (QP) is a per connection shared data काष्ठाure which is used
 *	to send work requests (SQ), receive completion notअगरications (CQ)
 *	and receive asynchoronous / scsi sense info (RQ). 'qp_info' काष्ठाure
 *	below holds queue memory, consumer/producer indexes and page table
 *	inक्रमmation
 */
काष्ठा qp_info अणु
	व्योम __iomem *ctx_base;
#घोषणा DPM_TRIGER_TYPE			0x40

#घोषणा BNX2I_570x_QUE_DB_SIZE		0
#घोषणा BNX2I_5771x_QUE_DB_SIZE		16
	काष्ठा sqe *sq_virt;
	dma_addr_t sq_phys;
	u32 sq_mem_size;

	काष्ठा sqe *sq_prod_qe;
	काष्ठा sqe *sq_cons_qe;
	काष्ठा sqe *sq_first_qe;
	काष्ठा sqe *sq_last_qe;
	u16 sq_prod_idx;
	u16 sq_cons_idx;
	u32 sqe_left;

	व्योम *sq_pgtbl_virt;
	dma_addr_t sq_pgtbl_phys;
	u32 sq_pgtbl_size;	/* set to PAGE_SIZE क्रम 5708 & 5709 */

	काष्ठा cqe *cq_virt;
	dma_addr_t cq_phys;
	u32 cq_mem_size;

	काष्ठा cqe *cq_prod_qe;
	काष्ठा cqe *cq_cons_qe;
	काष्ठा cqe *cq_first_qe;
	काष्ठा cqe *cq_last_qe;
	u16 cq_prod_idx;
	u16 cq_cons_idx;
	u32 cqe_left;
	u32 cqe_size;
	u32 cqe_exp_seq_sn;

	व्योम *cq_pgtbl_virt;
	dma_addr_t cq_pgtbl_phys;
	u32 cq_pgtbl_size;	/* set to PAGE_SIZE क्रम 5708 & 5709 */

	काष्ठा rqe *rq_virt;
	dma_addr_t rq_phys;
	u32 rq_mem_size;

	काष्ठा rqe *rq_prod_qe;
	काष्ठा rqe *rq_cons_qe;
	काष्ठा rqe *rq_first_qe;
	काष्ठा rqe *rq_last_qe;
	u16 rq_prod_idx;
	u16 rq_cons_idx;
	u32 rqe_left;

	व्योम *rq_pgtbl_virt;
	dma_addr_t rq_pgtbl_phys;
	u32 rq_pgtbl_size;	/* set to PAGE_SIZE क्रम 5708 & 5709 */
पूर्ण;



/*
 * CID handles
 */
काष्ठा ep_handles अणु
	u32 fw_cid;
	u32 drv_iscsi_cid;
	u16 pg_cid;
	u16 rsvd;
पूर्ण;


क्रमागत अणु
	EP_STATE_IDLE                   = 0x0,
	EP_STATE_PG_OFLD_START          = 0x1,
	EP_STATE_PG_OFLD_COMPL          = 0x2,
	EP_STATE_OFLD_START             = 0x4,
	EP_STATE_OFLD_COMPL             = 0x8,
	EP_STATE_CONNECT_START          = 0x10,
	EP_STATE_CONNECT_COMPL          = 0x20,
	EP_STATE_ULP_UPDATE_START       = 0x40,
	EP_STATE_ULP_UPDATE_COMPL       = 0x80,
	EP_STATE_DISCONN_START          = 0x100,
	EP_STATE_DISCONN_COMPL          = 0x200,
	EP_STATE_CLEANUP_START          = 0x400,
	EP_STATE_CLEANUP_CMPL           = 0x800,
	EP_STATE_TCP_FIN_RCVD           = 0x1000,
	EP_STATE_TCP_RST_RCVD           = 0x2000,
	EP_STATE_LOGOUT_SENT            = 0x4000,
	EP_STATE_LOGOUT_RESP_RCVD       = 0x8000,
	EP_STATE_PG_OFLD_FAILED         = 0x1000000,
	EP_STATE_ULP_UPDATE_FAILED      = 0x2000000,
	EP_STATE_CLEANUP_FAILED         = 0x4000000,
	EP_STATE_OFLD_FAILED            = 0x8000000,
	EP_STATE_CONNECT_FAILED         = 0x10000000,
	EP_STATE_DISCONN_TIMEDOUT       = 0x20000000,
	EP_STATE_OFLD_FAILED_CID_BUSY   = 0x80000000,
पूर्ण;

/**
 * काष्ठा bnx2i_endpoपूर्णांक - representation of tcp connection in NX2 world
 *
 * @link:               list head to link elements
 * @hba:                adapter to which this connection beदीर्घs
 * @conn:               iscsi connection this EP is linked to
 * @cls_ep:             associated iSCSI endpoपूर्णांक poपूर्णांकer
 * @cm_sk:              cnic sock काष्ठा
 * @hba_age:            age to detect अगर 'iscsid' issues ep_disconnect()
 *                      after HBA reset is completed by bnx2i/cnic/bnx2
 *                      modules
 * @state:              tracks offload connection state machine
 * @बारtamp:          tracks the start समय when the ep begins to connect
 * @num_active_cmds:    tracks the number of outstanding commands क्रम this ep
 * @ec_shअगरt:           the amount of shअगरt as part of the event coal calc
 * @qp:                 QP inक्रमmation
 * @ids:                contains chip allocated *context id* & driver asचिन्हित
 *                      *iscsi cid*
 * @ofld_समयr:         offload समयr to detect समयout
 * @ofld_रुको:          रुको queue
 *
 * Endpoपूर्णांक Structure - equivalent of tcp socket काष्ठाure
 */
काष्ठा bnx2i_endpoपूर्णांक अणु
	काष्ठा list_head link;
	काष्ठा bnx2i_hba *hba;
	काष्ठा bnx2i_conn *conn;
	काष्ठा iscsi_endpoपूर्णांक *cls_ep;
	काष्ठा cnic_sock *cm_sk;
	u32 hba_age;
	u32 state;
	अचिन्हित दीर्घ बारtamp;
	atomic_t num_active_cmds;
	u32 ec_shअगरt;

	काष्ठा qp_info qp;
	काष्ठा ep_handles ids;
		#घोषणा ep_iscsi_cid	ids.drv_iscsi_cid
		#घोषणा ep_cid		ids.fw_cid
		#घोषणा ep_pg_cid	ids.pg_cid
	काष्ठा समयr_list ofld_समयr;
	रुको_queue_head_t ofld_रुको;
पूर्ण;


काष्ठा bnx2i_work अणु
	काष्ठा list_head list;
	काष्ठा iscsi_session *session;
	काष्ठा bnx2i_conn *bnx2i_conn;
	काष्ठा cqe cqe;
पूर्ण;

काष्ठा bnx2i_percpu_s अणु
	काष्ठा task_काष्ठा *iothपढ़ो;
	काष्ठा list_head work_list;
	spinlock_t p_work_lock;
पूर्ण;


/* Global variables */
बाह्य अचिन्हित पूर्णांक error_mask1, error_mask2;
बाह्य u64 iscsi_error_mask;
बाह्य अचिन्हित पूर्णांक en_tcp_dack;
बाह्य अचिन्हित पूर्णांक event_coal_भाग;
बाह्य अचिन्हित पूर्णांक event_coal_min;

बाह्य काष्ठा scsi_transport_ढाँचा *bnx2i_scsi_xport_ढाँचा;
बाह्य काष्ठा iscsi_transport bnx2i_iscsi_transport;
बाह्य काष्ठा cnic_ulp_ops bnx2i_cnic_cb;

बाह्य अचिन्हित पूर्णांक sq_size;
बाह्य अचिन्हित पूर्णांक rq_size;

बाह्य काष्ठा device_attribute *bnx2i_dev_attributes[];



/*
 * Function Prototypes
 */
बाह्य व्योम bnx2i_identअगरy_device(काष्ठा bnx2i_hba *hba, काष्ठा cnic_dev *dev);

बाह्य व्योम bnx2i_ulp_init(काष्ठा cnic_dev *dev);
बाह्य व्योम bnx2i_ulp_निकास(काष्ठा cnic_dev *dev);
बाह्य व्योम bnx2i_start(व्योम *handle);
बाह्य व्योम bnx2i_stop(व्योम *handle);
बाह्य पूर्णांक bnx2i_get_stats(व्योम *handle);

बाह्य काष्ठा bnx2i_hba *get_adapter_list_head(व्योम);

काष्ठा bnx2i_conn *bnx2i_get_conn_from_id(काष्ठा bnx2i_hba *hba,
					  u16 iscsi_cid);

पूर्णांक bnx2i_alloc_ep_pool(व्योम);
व्योम bnx2i_release_ep_pool(व्योम);
काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep_ofld_list_next(काष्ठा bnx2i_hba *hba);
काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep_destroy_list_next(काष्ठा bnx2i_hba *hba);

काष्ठा bnx2i_hba *bnx2i_find_hba_क्रम_cnic(काष्ठा cnic_dev *cnic);

काष्ठा bnx2i_hba *bnx2i_alloc_hba(काष्ठा cnic_dev *cnic);
व्योम bnx2i_मुक्त_hba(काष्ठा bnx2i_hba *hba);

व्योम bnx2i_get_rq_buf(काष्ठा bnx2i_conn *conn, अक्षर *ptr, पूर्णांक len);
व्योम bnx2i_put_rq_buf(काष्ठा bnx2i_conn *conn, पूर्णांक count);

व्योम bnx2i_iscsi_unmap_sg_list(काष्ठा bnx2i_cmd *cmd);

व्योम bnx2i_drop_session(काष्ठा iscsi_cls_session *session);

बाह्य पूर्णांक bnx2i_send_fw_iscsi_init_msg(काष्ठा bnx2i_hba *hba);
बाह्य पूर्णांक bnx2i_send_iscsi_login(काष्ठा bnx2i_conn *conn,
				  काष्ठा iscsi_task *mtask);
बाह्य पूर्णांक bnx2i_send_iscsi_पंचांगf(काष्ठा bnx2i_conn *conn,
				  काष्ठा iscsi_task *mtask);
बाह्य पूर्णांक bnx2i_send_iscsi_text(काष्ठा bnx2i_conn *conn,
				 काष्ठा iscsi_task *mtask);
बाह्य पूर्णांक bnx2i_send_iscsi_scsicmd(काष्ठा bnx2i_conn *conn,
				    काष्ठा bnx2i_cmd *cmnd);
बाह्य पूर्णांक bnx2i_send_iscsi_nopout(काष्ठा bnx2i_conn *conn,
				   काष्ठा iscsi_task *mtask,
				   अक्षर *datap, पूर्णांक data_len, पूर्णांक unsol);
बाह्य पूर्णांक bnx2i_send_iscsi_logout(काष्ठा bnx2i_conn *conn,
				   काष्ठा iscsi_task *mtask);
बाह्य व्योम bnx2i_send_cmd_cleanup_req(काष्ठा bnx2i_hba *hba,
				       काष्ठा bnx2i_cmd *cmd);
बाह्य पूर्णांक bnx2i_send_conn_ofld_req(काष्ठा bnx2i_hba *hba,
				    काष्ठा bnx2i_endpoपूर्णांक *ep);
बाह्य व्योम bnx2i_update_iscsi_conn(काष्ठा iscsi_conn *conn);
बाह्य पूर्णांक bnx2i_send_conn_destroy(काष्ठा bnx2i_hba *hba,
				   काष्ठा bnx2i_endpoपूर्णांक *ep);

बाह्य पूर्णांक bnx2i_alloc_qp_resc(काष्ठा bnx2i_hba *hba,
			       काष्ठा bnx2i_endpoपूर्णांक *ep);
बाह्य व्योम bnx2i_मुक्त_qp_resc(काष्ठा bnx2i_hba *hba,
			       काष्ठा bnx2i_endpoपूर्णांक *ep);
बाह्य व्योम bnx2i_ep_ofld_समयr(काष्ठा समयr_list *t);
बाह्य काष्ठा bnx2i_endpoपूर्णांक *bnx2i_find_ep_in_ofld_list(
		काष्ठा bnx2i_hba *hba, u32 iscsi_cid);
बाह्य काष्ठा bnx2i_endpoपूर्णांक *bnx2i_find_ep_in_destroy_list(
		काष्ठा bnx2i_hba *hba, u32 iscsi_cid);

बाह्य पूर्णांक bnx2i_map_ep_dbell_regs(काष्ठा bnx2i_endpoपूर्णांक *ep);
बाह्य पूर्णांक bnx2i_arm_cq_event_coalescing(काष्ठा bnx2i_endpoपूर्णांक *ep, u8 action);

बाह्य पूर्णांक bnx2i_hw_ep_disconnect(काष्ठा bnx2i_endpoपूर्णांक *bnx2i_ep);

/* Debug related function prototypes */
बाह्य व्योम bnx2i_prपूर्णांक_pend_cmd_queue(काष्ठा bnx2i_conn *conn);
बाह्य व्योम bnx2i_prपूर्णांक_active_cmd_queue(काष्ठा bnx2i_conn *conn);
बाह्य व्योम bnx2i_prपूर्णांक_xmit_pdu_queue(काष्ठा bnx2i_conn *conn);
बाह्य व्योम bnx2i_prपूर्णांक_recv_state(काष्ठा bnx2i_conn *conn);

बाह्य पूर्णांक bnx2i_percpu_io_thपढ़ो(व्योम *arg);
बाह्य पूर्णांक bnx2i_process_scsi_cmd_resp(काष्ठा iscsi_session *session,
				       काष्ठा bnx2i_conn *bnx2i_conn,
				       काष्ठा cqe *cqe);
#पूर्ण_अगर
