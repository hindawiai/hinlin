<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zfcp device driver
 *
 * Global definitions क्रम the zfcp device driver.
 *
 * Copyright IBM Corp. 2002, 2020
 */

#अगर_अघोषित ZFCP_DEF_H
#घोषणा ZFCP_DEF_H

/*************************** INCLUDES *****************************************/

#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/major.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/mempool.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/ioctl.h>
#समावेश <scsi/fc/fc_fs.h>
#समावेश <scsi/fc/fc_gs.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/scsi_bsg_fc.h>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश "zfcp_fsf.h"
#समावेश "zfcp_fc.h"
#समावेश "zfcp_qdio.h"

/********************* FSF SPECIFIC DEFINES *********************************/

/* ATTENTION: value must not be used by hardware */
#घोषणा FSF_QTCB_UNSOLICITED_STATUS		0x6305

/*************** ADAPTER/PORT/UNIT AND FSF_REQ STATUS FLAGS ******************/

/*
 * Note, the lefपंचांगost 12 status bits (3 nibbles) are common among adapter, port
 * and unit. This is a mask क्रम bitwise 'and' with status values.
 */
#घोषणा ZFCP_COMMON_FLAGS			0xfff00000

/* common status bits */
#घोषणा ZFCP_STATUS_COMMON_RUNNING		0x40000000
#घोषणा ZFCP_STATUS_COMMON_ERP_FAILED		0x20000000
#घोषणा ZFCP_STATUS_COMMON_UNBLOCKED		0x10000000
#घोषणा ZFCP_STATUS_COMMON_OPEN                 0x04000000
#घोषणा ZFCP_STATUS_COMMON_ERP_INUSE		0x01000000
#घोषणा ZFCP_STATUS_COMMON_ACCESS_DENIED	0x00800000
#घोषणा ZFCP_STATUS_COMMON_ACCESS_BOXED		0x00400000
#घोषणा ZFCP_STATUS_COMMON_NOESC		0x00200000

/* adapter status */
#घोषणा ZFCP_STATUS_ADAPTER_MB_ACT		0x00000001
#घोषणा ZFCP_STATUS_ADAPTER_QDIOUP		0x00000002
#घोषणा ZFCP_STATUS_ADAPTER_SIOSL_ISSUED	0x00000004
#घोषणा ZFCP_STATUS_ADAPTER_XCONFIG_OK		0x00000008
#घोषणा ZFCP_STATUS_ADAPTER_HOST_CON_INIT	0x00000010
#घोषणा ZFCP_STATUS_ADAPTER_ERP_PENDING		0x00000100
#घोषणा ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED	0x00000200
#घोषणा ZFCP_STATUS_ADAPTER_DATA_DIV_ENABLED	0x00000400

/* remote port status */
#घोषणा ZFCP_STATUS_PORT_PHYS_OPEN		0x00000001
#घोषणा ZFCP_STATUS_PORT_LINK_TEST		0x00000002

/* FSF request status (this करोes not have a common part) */
#घोषणा ZFCP_STATUS_FSFREQ_ERROR		0x00000008
#घोषणा ZFCP_STATUS_FSFREQ_CLEANUP		0x00000010
#घोषणा ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED	0x00000040
#घोषणा ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED       0x00000080
#घोषणा ZFCP_STATUS_FSFREQ_TMFUNCFAILED         0x00000200
#घोषणा ZFCP_STATUS_FSFREQ_DISMISSED            0x00001000
#घोषणा ZFCP_STATUS_FSFREQ_XDATAINCOMPLETE	0x00020000

/************************* STRUCTURE DEFINITIONS *****************************/

/**
 * क्रमागत zfcp_erp_act_type - Type of ERP action object.
 * @ZFCP_ERP_ACTION_REOPEN_LUN: LUN recovery.
 * @ZFCP_ERP_ACTION_REOPEN_PORT: Port recovery.
 * @ZFCP_ERP_ACTION_REOPEN_PORT_FORCED: Forced port recovery.
 * @ZFCP_ERP_ACTION_REOPEN_ADAPTER: Adapter recovery.
 *
 * Values must fit पूर्णांकo u8 because of code dependencies:
 * zfcp_dbf_rec_trig(), &zfcp_dbf_rec_trigger.want, &zfcp_dbf_rec_trigger.need;
 * zfcp_dbf_rec_run_lvl(), zfcp_dbf_rec_run(), &zfcp_dbf_rec_running.rec_action.
 */
क्रमागत zfcp_erp_act_type अणु
	ZFCP_ERP_ACTION_REOPEN_LUN	   = 1,
	ZFCP_ERP_ACTION_REOPEN_PORT	   = 2,
	ZFCP_ERP_ACTION_REOPEN_PORT_FORCED = 3,
	ZFCP_ERP_ACTION_REOPEN_ADAPTER	   = 4,
पूर्ण;

/*
 * Values must fit पूर्णांकo u16 because of code dependencies:
 * zfcp_dbf_rec_run_lvl(), zfcp_dbf_rec_run(), zfcp_dbf_rec_run_wka(),
 * &zfcp_dbf_rec_running.rec_step.
 */
क्रमागत zfcp_erp_steps अणु
	ZFCP_ERP_STEP_UNINITIALIZED	= 0x0000,
	ZFCP_ERP_STEP_PHYS_PORT_CLOSING	= 0x0010,
	ZFCP_ERP_STEP_PORT_CLOSING	= 0x0100,
	ZFCP_ERP_STEP_PORT_OPENING	= 0x0800,
	ZFCP_ERP_STEP_LUN_CLOSING	= 0x1000,
	ZFCP_ERP_STEP_LUN_OPENING	= 0x2000,
पूर्ण;

काष्ठा zfcp_erp_action अणु
	काष्ठा list_head list;
	क्रमागत zfcp_erp_act_type type;  /* requested action code */
	काष्ठा zfcp_adapter *adapter; /* device which should be recovered */
	काष्ठा zfcp_port *port;
	काष्ठा scsi_device *sdev;
	u32		status;	      /* recovery status */
	क्रमागत zfcp_erp_steps	step;	/* active step of this erp action */
	अचिन्हित दीर्घ		fsf_req_id;
	काष्ठा समयr_list समयr;
पूर्ण;

/* holds various memory pools of an adapter */
काष्ठा zfcp_adapter_mempool अणु
	mempool_t *erp_req;
	mempool_t *gid_pn_req;
	mempool_t *scsi_req;
	mempool_t *scsi_पात;
	mempool_t *status_पढ़ो_req;
	mempool_t *sr_data;
	mempool_t *gid_pn;
	mempool_t *qtcb_pool;
पूर्ण;

काष्ठा zfcp_adapter अणु
	काष्ठा kref		ref;
	u64			peer_wwnn;	   /* P2P peer WWNN */
	u64			peer_wwpn;	   /* P2P peer WWPN */
	u32			peer_d_id;	   /* P2P peer D_ID */
	काष्ठा ccw_device       *ccw_device;	   /* S/390 ccw device */
	काष्ठा zfcp_qdio	*qdio;
	u32			hydra_version;	   /* Hydra version */
	u32			fsf_lic_version;
	u32			adapter_features;  /* FCP channel features */
	u32			connection_features; /* host connection features */
	u32			hardware_version;  /* of FCP channel */
	u32			fc_security_algorithms; /* of FCP channel */
	u32			fc_security_algorithms_old; /* of FCP channel */
	u16			समयr_ticks;       /* समय पूर्णांक क्रम a tick */
	काष्ठा Scsi_Host	*scsi_host;	   /* Poपूर्णांकer to mid-layer */
	काष्ठा list_head	port_list;	   /* remote port list */
	rwlock_t		port_list_lock;    /* port list lock */
	अचिन्हित दीर्घ		req_no;		   /* unique FSF req number */
	काष्ठा zfcp_reqlist	*req_list;
	u32			fsf_req_seq_no;	   /* FSF cmnd seq number */
	rwlock_t		पात_lock;        /* Protects against SCSI
						      stack पात/command
						      completion races */
	atomic_t		stat_miss;	   /* # missing status पढ़ोs*/
	अचिन्हित पूर्णांक		stat_पढ़ो_buf_num;
	काष्ठा work_काष्ठा	stat_work;
	atomic_t		status;	           /* status of this adapter */
	काष्ठा list_head	erp_पढ़ोy_head;	   /* error recovery क्रम this
						      adapter/devices */
	रुको_queue_head_t	erp_पढ़ोy_wq;
	काष्ठा list_head	erp_running_head;
	rwlock_t		erp_lock;
	रुको_queue_head_t	erp_करोne_wqh;
	काष्ठा zfcp_erp_action	erp_action;	   /* pending error recovery */
	atomic_t		erp_counter;
	u32			erp_total_count;   /* total nr of enqueued erp
						      actions */
	u32			erp_low_mem_count; /* nr of erp actions रुकोing
						      क्रम memory */
	काष्ठा task_काष्ठा	*erp_thपढ़ो;
	काष्ठा zfcp_fc_wka_ports *gs;		   /* generic services */
	काष्ठा zfcp_dbf		*dbf;		   /* debug traces */
	काष्ठा zfcp_adapter_mempool	pool;      /* Adapter memory pools */
	काष्ठा fc_host_statistics *fc_stats;
	काष्ठा fsf_qtcb_bottom_port *stats_reset_data;
	अचिन्हित दीर्घ		stats_reset;
	काष्ठा delayed_work	scan_work;
	काष्ठा work_काष्ठा	ns_up_work;
	काष्ठा service_level	service_level;
	काष्ठा workqueue_काष्ठा	*work_queue;
	काष्ठा device_dma_parameters dma_parms;
	काष्ठा zfcp_fc_events events;
	अचिन्हित दीर्घ		next_port_scan;
	काष्ठा zfcp_diag_adapter	*diagnostics;
	काष्ठा work_काष्ठा	version_change_lost_work;
पूर्ण;

काष्ठा zfcp_port अणु
	काष्ठा device          dev;
	काष्ठा fc_rport        *rport;         /* rport of fc transport class */
	काष्ठा list_head       list;	       /* list of remote ports */
	काष्ठा zfcp_adapter    *adapter;       /* adapter used to access port */
	काष्ठा list_head	unit_list;	/* head of logical unit list */
	rwlock_t		unit_list_lock; /* unit list lock */
	atomic_t		units;	       /* zfcp_unit count */
	atomic_t	       status;	       /* status of this remote port */
	u64		       wwnn;	       /* WWNN अगर known */
	u64		       wwpn;	       /* WWPN */
	u32		       d_id;	       /* D_ID */
	u32		       handle;	       /* handle asचिन्हित by FSF */
	काष्ठा zfcp_erp_action erp_action;     /* pending error recovery */
	atomic_t	       erp_counter;
	u32                    maxframe_size;
	u32                    supported_classes;
	u32                    connection_info;
	u32                    connection_info_old;
	काष्ठा work_काष्ठा     gid_pn_work;
	काष्ठा work_काष्ठा     test_link_work;
	काष्ठा work_काष्ठा     rport_work;
	क्रमागत अणु RPORT_NONE, RPORT_ADD, RPORT_DEL पूर्ण  rport_task;
	अचिन्हित पूर्णांक		starget_id;
पूर्ण;

काष्ठा zfcp_latency_record अणु
	u32 min;
	u32 max;
	u64 sum;
पूर्ण;

काष्ठा zfcp_latency_cont अणु
	काष्ठा zfcp_latency_record channel;
	काष्ठा zfcp_latency_record fabric;
	u64 counter;
पूर्ण;

काष्ठा zfcp_latencies अणु
	काष्ठा zfcp_latency_cont पढ़ो;
	काष्ठा zfcp_latency_cont ग_लिखो;
	काष्ठा zfcp_latency_cont cmd;
	spinlock_t lock;
पूर्ण;

/**
 * काष्ठा zfcp_unit - LUN configured via zfcp sysfs
 * @dev: काष्ठा device क्रम sysfs representation and reference counting
 * @list: entry in LUN/unit list per zfcp_port
 * @port: reference to zfcp_port where this LUN is configured
 * @fcp_lun: 64 bit LUN value
 * @scsi_work: क्रम running scsi_scan_target
 *
 * This is the representation of a LUN that has been configured क्रम
 * usage. The मुख्य data here is the 64 bit LUN value, data क्रम
 * running I/O and recovery is in काष्ठा zfcp_scsi_dev.
 */
काष्ठा zfcp_unit अणु
	काष्ठा device		dev;
	काष्ठा list_head	list;
	काष्ठा zfcp_port	*port;
	u64			fcp_lun;
	काष्ठा work_काष्ठा	scsi_work;
पूर्ण;

/**
 * काष्ठा zfcp_scsi_dev - zfcp data per SCSI device
 * @status: zfcp पूर्णांकernal status flags
 * @lun_handle: handle from "open lun" क्रम issuing FSF requests
 * @erp_action: zfcp erp data क्रम खोलोing and recovering this LUN
 * @erp_counter: zfcp erp counter क्रम this LUN
 * @latencies: FSF channel and fabric latencies
 * @port: zfcp_port where this LUN beदीर्घs to
 */
काष्ठा zfcp_scsi_dev अणु
	atomic_t		status;
	u32			lun_handle;
	काष्ठा zfcp_erp_action	erp_action;
	atomic_t		erp_counter;
	काष्ठा zfcp_latencies	latencies;
	काष्ठा zfcp_port	*port;
पूर्ण;

/**
 * sdev_to_zfcp - Access zfcp LUN data क्रम SCSI device
 * @sdev: scsi_device where to get the zfcp_scsi_dev poपूर्णांकer
 */
अटल अंतरभूत काष्ठा zfcp_scsi_dev *sdev_to_zfcp(काष्ठा scsi_device *sdev)
अणु
	वापस scsi_transport_device_data(sdev);
पूर्ण

/**
 * zfcp_scsi_dev_lun - Return SCSI device LUN as 64 bit FCP LUN
 * @sdev: SCSI device where to get the LUN from
 */
अटल अंतरभूत u64 zfcp_scsi_dev_lun(काष्ठा scsi_device *sdev)
अणु
	u64 fcp_lun;

	पूर्णांक_to_scsilun(sdev->lun, (काष्ठा scsi_lun *)&fcp_lun);
	वापस fcp_lun;
पूर्ण

/**
 * काष्ठा zfcp_fsf_req - basic FSF request काष्ठाure
 * @list: list of FSF requests
 * @req_id: unique request ID
 * @adapter: adapter this request beदीर्घs to
 * @qdio_req: qdio queue related values
 * @completion: used to संकेत the completion of the request
 * @status: status of the request
 * @qtcb: associated QTCB
 * @data: निजी data
 * @समयr: समयr data of this request
 * @erp_action: reference to erp action अगर request issued on behalf of ERP
 * @pool: reference to memory pool अगर used क्रम this request
 * @issued: समय when request was send (STCK)
 * @handler: handler which should be called to process response
 */
काष्ठा zfcp_fsf_req अणु
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		req_id;
	काष्ठा zfcp_adapter	*adapter;
	काष्ठा zfcp_qdio_req	qdio_req;
	काष्ठा completion	completion;
	u32			status;
	काष्ठा fsf_qtcb		*qtcb;
	व्योम			*data;
	काष्ठा समयr_list	समयr;
	काष्ठा zfcp_erp_action	*erp_action;
	mempool_t		*pool;
	अचिन्हित दीर्घ दीर्घ	issued;
	व्योम			(*handler)(काष्ठा zfcp_fsf_req *);
पूर्ण;

अटल अंतरभूत
पूर्णांक zfcp_adapter_multi_buffer_active(काष्ठा zfcp_adapter *adapter)
अणु
	वापस atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_ADAPTER_MB_ACT;
पूर्ण

अटल अंतरभूत bool zfcp_fsf_req_is_status_पढ़ो_buffer(काष्ठा zfcp_fsf_req *req)
अणु
	वापस req->qtcb == शून्य;
पूर्ण

#पूर्ण_अगर /* ZFCP_DEF_H */
