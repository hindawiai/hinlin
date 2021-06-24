<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*******************************************************************************
 * IBM Virtual SCSI Target Driver
 * Copyright (C) 2003-2005 Dave Boutcher (boutcher@us.ibm.com) IBM Corp.
 *			   Santiago Leon (santil@us.ibm.com) IBM Corp.
 *			   Linda Xie (lxie@us.ibm.com) IBM Corp.
 *
 * Copyright (C) 2005-2011 FUJITA Tomonori <tomof@acm.org>
 * Copyright (C) 2010 Nicholas A. Bellinger <nab@kernel.org>
 * Copyright (C) 2016 Bryant G. Ly <bryantly@linux.vnet.ibm.com> IBM Corp.
 *
 * Authors: Bryant G. Ly <bryantly@linux.vnet.ibm.com>
 * Authors: Michael Cyr <mikecyr@linux.vnet.ibm.com>
 *
 ****************************************************************************/

#अगर_अघोषित __H_IBMVSCSI_TGT
#घोषणा __H_IBMVSCSI_TGT

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "libsrp.h"

#घोषणा SYS_ID_NAME_LEN		64
#घोषणा PARTITION_NAMELEN	96
#घोषणा IBMVSCSIS_NAMELEN       32

#घोषणा MSG_HI  0
#घोषणा MSG_LOW 1

#घोषणा MAX_CMD_Q_PAGES       4
#घोषणा CRQ_PER_PAGE          (PAGE_SIZE / माप(काष्ठा viosrp_crq))
/* in terms of number of elements */
#घोषणा DEFAULT_CMD_Q_SIZE    CRQ_PER_PAGE
#घोषणा MAX_CMD_Q_SIZE        (DEFAULT_CMD_Q_SIZE * MAX_CMD_Q_PAGES)

#घोषणा SRP_VIOLATION           0x102  /* general error code */

/*
 * SRP buffer क्रमmats defined as of 16.a supported by this driver.
 */
#घोषणा SUPPORTED_FORMATS  ((SRP_DATA_DESC_सूचीECT << 1) | \
			    (SRP_DATA_DESC_INसूचीECT << 1))

#घोषणा SCSI_LUN_ADDR_METHOD_FLAT	1

काष्ठा dma_winकरोw अणु
	u32 liobn;	/* Unique per vdevice */
	u64 tce_base;	/* Physical location of the TCE table */
	u64 tce_size;	/* Size of the TCE table in bytes */
पूर्ण;

काष्ठा target_dds अणु
	u64 unit_id;                /* 64 bit will क्रमce alignment */
#घोषणा NUM_DMA_WINDOWS 2
#घोषणा LOCAL  0
#घोषणा REMOTE 1
	काष्ठा dma_winकरोw  winकरोw[NUM_DMA_WINDOWS];

	/* root node property "ibm,partition-no" */
	uपूर्णांक partition_num;
	अक्षर partition_name[PARTITION_NAMELEN];
पूर्ण;

#घोषणा MAX_NUM_PORTS        1
#घोषणा MAX_H_COPY_RDMA      (128 * 1024)

#घोषणा MAX_EYE   64

/* Return codes */
#घोषणा ADAPT_SUCCESS            0L
/* choose error codes that करो not conflict with PHYP */
#घोषणा ERROR                   -40L

काष्ठा क्रमmat_code अणु
	u8 reserved;
	u8 buffers;
पूर्ण;

काष्ठा client_info अणु
#घोषणा SRP_VERSION "16.a"
	अक्षर srp_version[8];
	/* root node property ibm,partition-name */
	अक्षर partition_name[PARTITION_NAMELEN];
	/* root node property ibm,partition-no */
	u32 partition_number;
	/* initially 1 */
	u32 mad_version;
	u32 os_type;
पूर्ण;

/*
 * Changing this स्थिरant changes the number of seconds to रुको beक्रमe
 * considering the client will never service its queue again.
 */
#घोषणा SECONDS_TO_CONSIDER_FAILED 30
/*
 * These स्थिरants set the polling period used to determine अगर the client
 * has मुक्तd at least one element in the response queue.
 */
#घोषणा WAIT_SECONDS 1
#घोषणा WAIT_न_अंकO_SECONDS 5000
#घोषणा MAX_TIMER_POPS ((1000000 / WAIT_न_अंकO_SECONDS) * \
			SECONDS_TO_CONSIDER_FAILED)
/*
 * general purpose समयr control block
 * which can be used क्रम multiple functions
 */
काष्ठा समयr_cb अणु
	काष्ठा hrसमयr समयr;
	/*
	 * how दीर्घ has it been since the client
	 * serviced the queue. The variable is incrmented
	 * in the service_रुको_q routine and cleared
	 * in send messages
	 */
	पूर्णांक समयr_pops;
	/* the समयr is started */
	bool started;
पूर्ण;

काष्ठा cmd_queue अणु
	/* kva */
	काष्ठा viosrp_crq *base_addr;
	dma_addr_t crq_token;
	/* used to मुख्यtain index */
	uपूर्णांक mask;
	/* current element */
	uपूर्णांक index;
	पूर्णांक size;
पूर्ण;

#घोषणा SCSOLNT_RESP_SHIFT	1
#घोषणा UCSOLNT_RESP_SHIFT	2

#घोषणा SCSOLNT         BIT(SCSOLNT_RESP_SHIFT)
#घोषणा UCSOLNT         BIT(UCSOLNT_RESP_SHIFT)

क्रमागत cmd_type अणु
	SCSI_CDB	= 0x01,
	TASK_MANAGEMENT	= 0x02,
	/* MAD or addressed to port 0 */
	ADAPTER_MAD	= 0x04,
	UNSET_TYPE	= 0x08,
पूर्ण;

काष्ठा iu_rsp अणु
	u8 क्रमmat;
	u8 sol_not;
	u16 len;
	/* tag is just to help client identअगरy cmd, so करोn't translate be/le */
	u64 tag;
पूर्ण;

काष्ठा ibmvscsis_cmd अणु
	काष्ठा list_head list;
	/* Used क्रम TCM Core operations */
	काष्ठा se_cmd se_cmd;
	काष्ठा iu_entry *iue;
	काष्ठा iu_rsp rsp;
	काष्ठा work_काष्ठा work;
	काष्ठा scsi_info *adapter;
	काष्ठा ibmvscsis_cmd *पात_cmd;
	/* Sense buffer that will be mapped पूर्णांकo outgoing status */
	अचिन्हित अक्षर sense_buf[TRANSPORT_SENSE_BUFFER];
	u64 init_समय;
#घोषणा CMD_FAST_FAIL	BIT(0)
#घोषणा DELAY_SEND	BIT(1)
	u32 flags;
	अक्षर type;
पूर्ण;

काष्ठा ibmvscsis_nexus अणु
	काष्ठा se_session *se_sess;
पूर्ण;

काष्ठा ibmvscsis_tport अणु
	/* SCSI protocol the tport is providing */
	u8 tport_proto_id;
	/* ASCII क्रमmatted WWPN क्रम SRP Target port */
	अक्षर tport_name[IBMVSCSIS_NAMELEN];
	/* Returned by ibmvscsis_make_tport() */
	काष्ठा se_wwn tport_wwn;
	/* Returned by ibmvscsis_make_tpg() */
	काष्ठा se_portal_group se_tpg;
	/* ibmvscsis port target portal group tag क्रम TCM */
	u16 tport_tpgt;
	/* Poपूर्णांकer to TCM session क्रम I_T Nexus */
	काष्ठा ibmvscsis_nexus *ibmv_nexus;
	bool enabled;
	bool releasing;
पूर्ण;

काष्ठा scsi_info अणु
	काष्ठा list_head list;
	अक्षर eye[MAX_EYE];

	/* commands रुकोing क्रम space on repsonse queue */
	काष्ठा list_head रुकोing_rsp;
#घोषणा NO_QUEUE                    0x00
#घोषणा WAIT_ENABLED                0X01
#घोषणा WAIT_CONNECTION             0x04
	/* have established a connection */
#घोषणा CONNECTED                   0x08
	/* at least one port is processing SRP IU */
#घोषणा SRP_PROCESSING              0x10
	/* हटाओ request received */
#घोषणा UNCONFIGURING               0x20
	/* disconnect by letting adapter go idle, no error */
#घोषणा WAIT_IDLE                   0x40
	/* disconnecting to clear an error */
#घोषणा ERR_DISCONNECT              0x80
	/* disconnect to clear error state, then come back up */
#घोषणा ERR_DISCONNECT_RECONNECT    0x100
	/* disconnected after clearing an error */
#घोषणा ERR_DISCONNECTED            0x200
	/* A series of errors caused unexpected errors */
#घोषणा UNDEFINED                   0x400
	u16  state;
	पूर्णांक fast_fail;
	काष्ठा target_dds dds;
	अक्षर *cmd_pool;
	/* list of मुक्त commands */
	काष्ठा list_head मुक्त_cmd;
	/* command elements पढ़ोy क्रम scheduler */
	काष्ठा list_head schedule_q;
	/* commands sent to TCM */
	काष्ठा list_head active_q;
	caddr_t *map_buf;
	/* ioba of map buffer */
	dma_addr_t map_ioba;
	/* allowable number of outstanding SRP requests */
	पूर्णांक request_limit;
	/* extra credit */
	पूर्णांक credit;
	/* outstanding transactions against credit limit */
	पूर्णांक debit;

	/* allow only one outstanding mad request */
#घोषणा PROCESSING_MAD                0x00002
	/* Waiting to go idle */
#घोषणा WAIT_FOR_IDLE		      0x00004
	/* H_REG_CRQ called */
#घोषणा CRQ_CLOSED                    0x00010
	/* detected that client has failed */
#घोषणा CLIENT_FAILED                 0x00040
	/* detected that transport event occurred */
#घोषणा TRANS_EVENT                   0x00080
	/* करोn't attempt to send anything to the client */
#घोषणा RESPONSE_Q_DOWN               0x00100
	/* request made to schedule disconnect handler */
#घोषणा SCHEDULE_DISCONNECT           0x00400
	/* disconnect handler is scheduled */
#घोषणा DISCONNECT_SCHEDULED          0x00800
	/* हटाओ function is sleeping */
#घोषणा CFG_SLEEPING                  0x01000
	/* Register क्रम Prepare क्रम Suspend Transport Events */
#घोषणा PREP_FOR_SUSPEND_ENABLED      0x02000
	/* Prepare क्रम Suspend event sent */
#घोषणा PREP_FOR_SUSPEND_PENDING      0x04000
	/* Resume from Suspend event sent */
#घोषणा PREP_FOR_SUSPEND_ABORTED      0x08000
	/* Prepare क्रम Suspend event overwrote another CRQ entry */
#घोषणा PREP_FOR_SUSPEND_OVERWRITE    0x10000
	u32 flags;
	/* adapter lock */
	spinlock_t पूर्णांकr_lock;
	/* inक्रमmation needed to manage command queue */
	काष्ठा cmd_queue cmd_q;
	/* used in hcall to copy response back पूर्णांकo srp buffer */
	u64  empty_iu_id;
	/* used in crq, to tag what iu the response is क्रम */
	u64  empty_iu_tag;
	uपूर्णांक new_state;
	uपूर्णांक resume_state;
	/* control block क्रम the response queue समयr */
	काष्ठा समयr_cb rsp_q_समयr;
	/* keep last client to enable proper accounting */
	काष्ठा client_info client_data;
	/* what can this client करो */
	u32 client_cap;
	/*
	 * The following two fields capture state and flag changes that
	 * can occur when the lock is given up.  In the orginal design,
	 * the lock was held during calls पूर्णांकo phyp;
	 * however, phyp did not meet PAPR architecture.  This is
	 * a work around.
	 */
	u16  phyp_acr_state;
	u32 phyp_acr_flags;

	काष्ठा workqueue_काष्ठा *work_q;
	काष्ठा completion रुको_idle;
	काष्ठा completion unconfig;
	काष्ठा device dev;
	काष्ठा vio_dev *dma_dev;
	काष्ठा srp_target target;
	काष्ठा ibmvscsis_tport tport;
	काष्ठा tasklet_काष्ठा work_task;
	काष्ठा work_काष्ठा proc_work;
पूर्ण;

/*
 * Provide a स्थिरant that allows software to detect the adapter is
 * disconnecting from the client from one of several states.
 */
#घोषणा IS_DISCONNECTING (UNCONFIGURING | ERR_DISCONNECT_RECONNECT | \
			  ERR_DISCONNECT)

/*
 * Provide a स्थिरant that can be used with पूर्णांकerrupt handling that
 * essentially lets the पूर्णांकerrupt handler know that all requests should
 * be thrown out,
 */
#घोषणा DONT_PROCESS_STATE (IS_DISCONNECTING | UNDEFINED | \
			    ERR_DISCONNECTED  | WAIT_IDLE)

/*
 * If any of these flag bits are set then करो not allow the पूर्णांकerrupt
 * handler to schedule the off level handler.
 */
#घोषणा BLOCK (DISCONNECT_SCHEDULED)

/* State and transition events that stop the पूर्णांकerrupt handler */
#घोषणा TARGET_STOP(VSCSI) (दीर्घ)(((VSCSI)->state & DONT_PROCESS_STATE) | \
				  ((VSCSI)->flags & BLOCK))

#घोषणा PREP_FOR_SUSPEND_FLAGS  (PREP_FOR_SUSPEND_ENABLED | \
				 PREP_FOR_SUSPEND_PENDING | \
				 PREP_FOR_SUSPEND_ABORTED | \
				 PREP_FOR_SUSPEND_OVERWRITE)

/* flag bit that are not reset during disconnect */
#घोषणा PRESERVE_FLAG_FIELDS (PREP_FOR_SUSPEND_FLAGS)

#घोषणा vio_iu(IUE) ((जोड़ viosrp_iu *)((IUE)->sbuf->buf))

#घोषणा READ_CMD(cdb)	(((cdb)[0] & 0x1F) == 8)
#घोषणा WRITE_CMD(cdb)	(((cdb)[0] & 0x1F) == 0xA)

#अगर_अघोषित H_GET_PARTNER_INFO
#घोषणा H_GET_PARTNER_INFO              0x0000000000000008LL
#पूर्ण_अगर
#अगर_अघोषित H_ENABLE_PREPARE_FOR_SUSPEND
#घोषणा H_ENABLE_PREPARE_FOR_SUSPEND    0x000000000000001DLL
#पूर्ण_अगर
#अगर_अघोषित H_READY_FOR_SUSPEND
#घोषणा H_READY_FOR_SUSPEND             0x000000000000001ELL
#पूर्ण_अगर


#घोषणा h_copy_rdma(l, sa, sb, da, db) \
		plpar_hcall_norets(H_COPY_RDMA, l, sa, sb, da, db)
#घोषणा h_vioctl(u, o, a, u1, u2, u3, u4) \
		plpar_hcall_norets(H_VIOCTL, u, o, a, u1, u2)
#घोषणा h_reg_crq(ua, tok, sz) \
		plpar_hcall_norets(H_REG_CRQ, ua, tok, sz)
#घोषणा h_मुक्त_crq(ua) \
		plpar_hcall_norets(H_FREE_CRQ, ua)
#घोषणा h_send_crq(ua, d1, d2) \
		plpar_hcall_norets(H_SEND_CRQ, ua, d1, d2)

#पूर्ण_अगर
