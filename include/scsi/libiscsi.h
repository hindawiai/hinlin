<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * iSCSI lib definitions
 *
 * Copyright (C) 2006 Red Hat, Inc.  All rights reserved.
 * Copyright (C) 2004 - 2006 Mike Christie
 * Copyright (C) 2004 - 2005 Dmitry Yusupov
 * Copyright (C) 2004 - 2005 Alex Aizman
 */
#अगर_अघोषित LIBISCSI_H
#घोषणा LIBISCSI_H

#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/refcount.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <scsi/iscsi_अगर.h>
#समावेश <scsi/scsi_transport_iscsi.h>

काष्ठा scsi_transport_ढाँचा;
काष्ठा scsi_host_ढाँचा;
काष्ठा scsi_device;
काष्ठा Scsi_Host;
काष्ठा scsi_target;
काष्ठा scsi_cmnd;
काष्ठा socket;
काष्ठा iscsi_transport;
काष्ठा iscsi_cls_session;
काष्ठा iscsi_cls_conn;
काष्ठा iscsi_session;
काष्ठा iscsi_nopin;
काष्ठा device;

#घोषणा ISCSI_DEF_XMIT_CMDS_MAX	128	/* must be घातer of 2 */
#घोषणा ISCSI_MGMT_CMDS_MAX	15

#घोषणा ISCSI_DEF_CMD_PER_LUN	32

/* Task Mgmt states */
क्रमागत अणु
	TMF_INITIAL,
	TMF_QUEUED,
	TMF_SUCCESS,
	TMF_FAILED,
	TMF_TIMEDOUT,
	TMF_NOT_FOUND,
पूर्ण;

#घोषणा ISID_SIZE			6

/* Connection suspend "bit" */
#घोषणा ISCSI_SUSPEND_BIT		1

#घोषणा ISCSI_ITT_MASK			0x1fff
#घोषणा ISCSI_TOTAL_CMDS_MAX		4096
/* this must be a घातer of two greater than ISCSI_MGMT_CMDS_MAX */
#घोषणा ISCSI_TOTAL_CMDS_MIN		16
#घोषणा ISCSI_AGE_SHIFT			28
#घोषणा ISCSI_AGE_MASK			0xf

#घोषणा ISCSI_ADDRESS_BUF_LEN		64

क्रमागत अणु
	/* this is the maximum possible storage क्रम AHSs */
	ISCSI_MAX_AHS_SIZE = माप(काष्ठा iscsi_ecdb_ahdr) +
				माप(काष्ठा iscsi_rlength_ahdr),
	ISCSI_DIGEST_SIZE = माप(__u32),
पूर्ण;


क्रमागत अणु
	ISCSI_TASK_FREE,
	ISCSI_TASK_COMPLETED,
	ISCSI_TASK_PENDING,
	ISCSI_TASK_RUNNING,
	ISCSI_TASK_ABRT_TMF,		/* पातed due to TMF */
	ISCSI_TASK_ABRT_SESS_RECOV,	/* पातed due to session recovery */
	ISCSI_TASK_REQUEUE_SCSIQ,	/* qcmd requeueing to scsi-ml */
पूर्ण;

काष्ठा iscsi_r2t_info अणु
	__be32			ttt;		/* copied from R2T */
	__be32			exp_statsn;	/* copied from R2T */
	uपूर्णांक32_t		data_length;	/* copied from R2T */
	uपूर्णांक32_t		data_offset;	/* copied from R2T */
	पूर्णांक			data_count;	/* DATA-Out payload progress */
	पूर्णांक			datasn;
	/* LLDs should set/update these values */
	पूर्णांक			sent;		/* R2T sequence progress */
पूर्ण;

काष्ठा iscsi_task अणु
	/*
	 * Because LLDs allocate their hdr dअगरferently, this is a poपूर्णांकer
	 * and length to that storage. It must be setup at session
	 * creation समय.
	 */
	काष्ठा iscsi_hdr	*hdr;
	अचिन्हित लघु		hdr_max;
	अचिन्हित लघु		hdr_len;	/* accumulated size of hdr used */
	/* copied values in हाल we need to send पंचांगfs */
	itt_t			hdr_itt;
	__be32			cmdsn;
	काष्ठा scsi_lun		lun;

	पूर्णांक			itt;		/* this ITT */

	अचिन्हित		imm_count;	/* imm-data (bytes)   */
	/* offset in unsolicited stream (bytes); */
	काष्ठा iscsi_r2t_info	unsol_r2t;
	अक्षर			*data;		/* mgmt payload */
	अचिन्हित		data_count;
	काष्ठा scsi_cmnd	*sc;		/* associated SCSI cmd*/
	काष्ठा iscsi_conn	*conn;		/* used connection    */

	/* data processing tracking */
	अचिन्हित दीर्घ		last_xfer;
	अचिन्हित दीर्घ		last_समयout;
	bool			have_checked_conn;

	/* T10 protection inक्रमmation */
	bool			रक्षित;

	/* state set/tested under session->lock */
	पूर्णांक			state;
	refcount_t		refcount;
	काष्ठा list_head	running;	/* running cmd list */
	व्योम			*dd_data;	/* driver/transport data */
पूर्ण;

/* invalid scsi_task poपूर्णांकer */
#घोषणा	INVALID_SCSI_TASK	(काष्ठा iscsi_task *)-1l

अटल अंतरभूत पूर्णांक iscsi_task_has_unsol_data(काष्ठा iscsi_task *task)
अणु
	वापस task->unsol_r2t.data_length > task->unsol_r2t.sent;
पूर्ण

अटल अंतरभूत व्योम* iscsi_next_hdr(काष्ठा iscsi_task *task)
अणु
	वापस (व्योम*)task->hdr + task->hdr_len;
पूर्ण

/* Connection's states */
क्रमागत अणु
	ISCSI_CONN_INITIAL_STAGE,
	ISCSI_CONN_STARTED,
	ISCSI_CONN_STOPPED,
	ISCSI_CONN_CLEANUP_WAIT,
पूर्ण;

काष्ठा iscsi_conn अणु
	काष्ठा iscsi_cls_conn	*cls_conn;	/* ptr to class connection */
	व्योम			*dd_data;	/* iscsi_transport data */
	काष्ठा iscsi_session	*session;	/* parent session */
	/*
	 * conn_stop() flag: stop to recover, stop to terminate
	 */
        पूर्णांक			stop_stage;
	काष्ठा समयr_list	transport_समयr;
	अचिन्हित दीर्घ		last_recv;
	अचिन्हित दीर्घ		last_ping;
	पूर्णांक			ping_समयout;
	पूर्णांक			recv_समयout;
	काष्ठा iscsi_task 	*ping_task;

	/* iSCSI connection-wide sequencing */
	uपूर्णांक32_t		exp_statsn;
	uपूर्णांक32_t		statsn;

	/* control data */
	पूर्णांक			id;		/* CID */
	पूर्णांक			c_stage;	/* connection state */
	/*
	 * Pपुनः_स्मृतिated buffer क्रम pdus that have data but करो not
	 * originate from scsi-ml. We never have two pdus using the
	 * buffer at the same समय. It is only allocated to
	 * the शेष max recv size because the pdus we support
	 * should always fit in this buffer
	 */
	अक्षर			*data;
	काष्ठा iscsi_task 	*login_task;	/* mtask used क्रम login/text */
	काष्ठा iscsi_task	*task;		/* xmit task in progress */

	/* xmit */
	/* items must be added/deleted under frwd lock */
	काष्ठा list_head	mgmtqueue;	/* mgmt (control) xmit queue */
	काष्ठा list_head	cmdqueue;	/* data-path cmd queue */
	काष्ठा list_head	requeue;	/* tasks needing another run */
	काष्ठा work_काष्ठा	xmitwork;	/* per-conn. xmit workqueue */
	अचिन्हित दीर्घ		suspend_tx;	/* suspend Tx */
	अचिन्हित दीर्घ		suspend_rx;	/* suspend Rx */

	/* पात */
	रुको_queue_head_t	ehरुको;		/* used in eh_पात() */
	काष्ठा iscsi_पंचांग		पंचांगhdr;
	काष्ठा समयr_list	पंचांगf_समयr;
	पूर्णांक			पंचांगf_state;	/* see TMF_INITIAL, etc.*/

	/* negotiated params */
	अचिन्हित		max_recv_dlength; /* initiator_max_recv_dsl*/
	अचिन्हित		max_xmit_dlength; /* target_max_recv_dsl */
	पूर्णांक			hdrdgst_en;
	पूर्णांक			datadgst_en;
	पूर्णांक			अगरmarker_en;
	पूर्णांक			ofmarker_en;
	/* values userspace uses to id a conn */
	पूर्णांक			persistent_port;
	अक्षर			*persistent_address;

	अचिन्हित		max_segment_size;
	अचिन्हित		tcp_xmit_wsf;
	अचिन्हित		tcp_recv_wsf;
	uपूर्णांक16_t		keepalive_पंचांगo;
	uपूर्णांक16_t		local_port;
	uपूर्णांक8_t			tcp_बारtamp_stat;
	uपूर्णांक8_t			tcp_nagle_disable;
	uपूर्णांक8_t			tcp_wsf_disable;
	uपूर्णांक8_t			tcp_समयr_scale;
	uपूर्णांक8_t			tcp_बारtamp_en;
	uपूर्णांक8_t			fragment_disable;
	uपूर्णांक8_t			ipv4_tos;
	uपूर्णांक8_t			ipv6_traffic_class;
	uपूर्णांक8_t			ipv6_flow_label;
	uपूर्णांक8_t			is_fw_asचिन्हित_ipv6;
	अक्षर			*local_ipaddr;

	/* MIB-statistics */
	uपूर्णांक64_t		txdata_octets;
	uपूर्णांक64_t		rxdata_octets;
	uपूर्णांक32_t		scsicmd_pdus_cnt;
	uपूर्णांक32_t		dataout_pdus_cnt;
	uपूर्णांक32_t		scsirsp_pdus_cnt;
	uपूर्णांक32_t		datain_pdus_cnt;
	uपूर्णांक32_t		r2t_pdus_cnt;
	uपूर्णांक32_t		पंचांगfcmd_pdus_cnt;
	पूर्णांक32_t			पंचांगfrsp_pdus_cnt;

	/* custom statistics */
	uपूर्णांक32_t		eh_पात_cnt;
	uपूर्णांक32_t		fmr_unalign_cnt;
पूर्ण;

काष्ठा iscsi_pool अणु
	काष्ठा kfअगरo		queue;		/* FIFO Queue */
	व्योम			**pool;		/* Pool of elements */
	पूर्णांक			max;		/* Max number of elements */
पूर्ण;

/* Session's states */
क्रमागत अणु
	ISCSI_STATE_FREE = 1,
	ISCSI_STATE_LOGGED_IN,
	ISCSI_STATE_FAILED,
	ISCSI_STATE_TERMINATE,
	ISCSI_STATE_IN_RECOVERY,
	ISCSI_STATE_RECOVERY_FAILED,
	ISCSI_STATE_LOGGING_OUT,
पूर्ण;

काष्ठा iscsi_session अणु
	काष्ठा iscsi_cls_session *cls_session;
	/*
	 * Syncs up the scsi eh thपढ़ो with the iscsi eh thपढ़ो when sending
	 * task management functions. This must be taken beक्रमe the session
	 * and recv lock.
	 */
	काष्ठा mutex		eh_mutex;

	/* iSCSI session-wide sequencing */
	uपूर्णांक32_t		cmdsn;
	uपूर्णांक32_t		exp_cmdsn;
	uपूर्णांक32_t		max_cmdsn;

	/* This tracks the reqs queued पूर्णांकo the initiator */
	uपूर्णांक32_t		queued_cmdsn;

	/* configuration */
	पूर्णांक			पात_समयout;
	पूर्णांक			lu_reset_समयout;
	पूर्णांक			tgt_reset_समयout;
	पूर्णांक			initial_r2t_en;
	अचिन्हित लघु		max_r2t;
	पूर्णांक			imm_data_en;
	अचिन्हित		first_burst;
	अचिन्हित		max_burst;
	पूर्णांक			समय2रुको;
	पूर्णांक			समय2retain;
	पूर्णांक			pdu_inorder_en;
	पूर्णांक			dataseq_inorder_en;
	पूर्णांक			erl;
	पूर्णांक			fast_पात;
	पूर्णांक			tpgt;
	अक्षर			*username;
	अक्षर			*username_in;
	अक्षर			*password;
	अक्षर			*password_in;
	अक्षर			*targetname;
	अक्षर			*targetalias;
	अक्षर			*अगरacename;
	अक्षर			*initiatorname;
	अक्षर			*boot_root;
	अक्षर			*boot_nic;
	अक्षर			*boot_target;
	अक्षर			*portal_type;
	अक्षर			*discovery_parent_type;
	uपूर्णांक16_t		discovery_parent_idx;
	uपूर्णांक16_t		def_taskmgmt_पंचांगo;
	uपूर्णांक16_t		tsid;
	uपूर्णांक8_t			स्वतः_snd_tgt_disable;
	uपूर्णांक8_t			discovery_sess;
	uपूर्णांक8_t			chap_auth_en;
	uपूर्णांक8_t			discovery_logout_en;
	uपूर्णांक8_t			bidi_chap_en;
	uपूर्णांक8_t			discovery_auth_optional;
	uपूर्णांक8_t			isid[ISID_SIZE];

	/* control data */
	काष्ठा iscsi_transport	*tt;
	काष्ठा Scsi_Host	*host;
	काष्ठा iscsi_conn	*leadconn;	/* leading connection */
	/* Between the क्रमward and the backward locks exists a strict locking
	 * hierarchy. The mutual exclusion zone रक्षित by the क्रमward lock
	 * can enबंद the mutual exclusion zone रक्षित by the backward lock
	 * but not vice versa.
	 */
	spinlock_t		frwd_lock;	/* protects session state, *
						 * cmdsn, queued_cmdsn     *
						 * session resources:      *
						 * - cmdpool kfअगरo_out ,   *
						 * - mgmtpool, queues	   */
	spinlock_t		back_lock;	/* protects cmdsn_exp      *
						 * cmdsn_max,              *
						 * cmdpool kfअगरo_in        */
	पूर्णांक			state;		/* session state           */
	पूर्णांक			age;		/* counts session re-खोलोs */

	पूर्णांक			scsi_cmds_max; 	/* max scsi commands */
	पूर्णांक			cmds_max;	/* size of cmds array */
	काष्ठा iscsi_task	**cmds;		/* Original Cmds arr */
	काष्ठा iscsi_pool	cmdpool;	/* PDU's pool */
	व्योम			*dd_data;	/* LLD निजी data */
पूर्ण;

क्रमागत अणु
	ISCSI_HOST_SETUP,
	ISCSI_HOST_REMOVED,
पूर्ण;

काष्ठा iscsi_host अणु
	अक्षर			*initiatorname;
	/* hw address or netdev iscsi connection is bound to */
	अक्षर			*hwaddress;
	अक्षर			*netdev;

	रुको_queue_head_t	session_removal_wq;
	/* protects sessions and state */
	spinlock_t		lock;
	पूर्णांक			num_sessions;
	पूर्णांक			state;

	काष्ठा workqueue_काष्ठा	*workq;
	अक्षर			workq_name[20];
पूर्ण;

/*
 * scsi host ढाँचा
 */
बाह्य पूर्णांक iscsi_eh_पात(काष्ठा scsi_cmnd *sc);
बाह्य पूर्णांक iscsi_eh_recover_target(काष्ठा scsi_cmnd *sc);
बाह्य पूर्णांक iscsi_eh_session_reset(काष्ठा scsi_cmnd *sc);
बाह्य पूर्णांक iscsi_eh_device_reset(काष्ठा scsi_cmnd *sc);
बाह्य पूर्णांक iscsi_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *sc);
बाह्य क्रमागत blk_eh_समयr_वापस iscsi_eh_cmd_समयd_out(काष्ठा scsi_cmnd *sc);

/*
 * iSCSI host helpers.
 */
#घोषणा iscsi_host_priv(_shost) \
	(shost_priv(_shost) + माप(काष्ठा iscsi_host))

बाह्य पूर्णांक iscsi_host_set_param(काष्ठा Scsi_Host *shost,
				क्रमागत iscsi_host_param param, अक्षर *buf,
				पूर्णांक buflen);
बाह्य पूर्णांक iscsi_host_get_param(काष्ठा Scsi_Host *shost,
				क्रमागत iscsi_host_param param, अक्षर *buf);
बाह्य पूर्णांक iscsi_host_add(काष्ठा Scsi_Host *shost, काष्ठा device *pdev);
बाह्य काष्ठा Scsi_Host *iscsi_host_alloc(काष्ठा scsi_host_ढाँचा *sht,
					  पूर्णांक dd_data_size,
					  bool xmit_can_sleep);
बाह्य व्योम iscsi_host_हटाओ(काष्ठा Scsi_Host *shost);
बाह्य व्योम iscsi_host_मुक्त(काष्ठा Scsi_Host *shost);
बाह्य पूर्णांक iscsi_target_alloc(काष्ठा scsi_target *starget);
बाह्य पूर्णांक iscsi_host_get_max_scsi_cmds(काष्ठा Scsi_Host *shost,
					uपूर्णांक16_t requested_cmds_max);

/*
 * session management
 */
बाह्य काष्ठा iscsi_cls_session *
iscsi_session_setup(काष्ठा iscsi_transport *, काष्ठा Scsi_Host *shost,
		    uपूर्णांक16_t, पूर्णांक, पूर्णांक, uपूर्णांक32_t, अचिन्हित पूर्णांक);
बाह्य व्योम iscsi_session_tearकरोwn(काष्ठा iscsi_cls_session *);
बाह्य व्योम iscsi_session_recovery_समयकरोut(काष्ठा iscsi_cls_session *);
बाह्य पूर्णांक iscsi_set_param(काष्ठा iscsi_cls_conn *cls_conn,
			   क्रमागत iscsi_param param, अक्षर *buf, पूर्णांक buflen);
बाह्य पूर्णांक iscsi_session_get_param(काष्ठा iscsi_cls_session *cls_session,
				   क्रमागत iscsi_param param, अक्षर *buf);

#घोषणा iscsi_session_prपूर्णांकk(prefix, _sess, fmt, a...)	\
	iscsi_cls_session_prपूर्णांकk(prefix, _sess->cls_session, fmt, ##a)

/*
 * connection management
 */
बाह्य काष्ठा iscsi_cls_conn *iscsi_conn_setup(काष्ठा iscsi_cls_session *,
					       पूर्णांक, uपूर्णांक32_t);
बाह्य व्योम iscsi_conn_tearकरोwn(काष्ठा iscsi_cls_conn *);
बाह्य पूर्णांक iscsi_conn_start(काष्ठा iscsi_cls_conn *);
बाह्य व्योम iscsi_conn_stop(काष्ठा iscsi_cls_conn *, पूर्णांक);
बाह्य पूर्णांक iscsi_conn_bind(काष्ठा iscsi_cls_session *, काष्ठा iscsi_cls_conn *,
			   पूर्णांक);
बाह्य व्योम iscsi_conn_failure(काष्ठा iscsi_conn *conn, क्रमागत iscsi_err err);
बाह्य व्योम iscsi_session_failure(काष्ठा iscsi_session *session,
				  क्रमागत iscsi_err err);
बाह्य पूर्णांक iscsi_conn_get_param(काष्ठा iscsi_cls_conn *cls_conn,
				क्रमागत iscsi_param param, अक्षर *buf);
बाह्य पूर्णांक iscsi_conn_get_addr_param(काष्ठा sockaddr_storage *addr,
				     क्रमागत iscsi_param param, अक्षर *buf);
बाह्य व्योम iscsi_suspend_tx(काष्ठा iscsi_conn *conn);
बाह्य व्योम iscsi_suspend_queue(काष्ठा iscsi_conn *conn);
बाह्य व्योम iscsi_conn_queue_work(काष्ठा iscsi_conn *conn);

#घोषणा iscsi_conn_prपूर्णांकk(prefix, _c, fmt, a...) \
	iscsi_cls_conn_prपूर्णांकk(prefix, ((काष्ठा iscsi_conn *)_c)->cls_conn, \
			      fmt, ##a)

/*
 * pdu and task processing
 */
बाह्य व्योम iscsi_update_cmdsn(काष्ठा iscsi_session *, काष्ठा iscsi_nopin *);
बाह्य व्योम iscsi_prep_data_out_pdu(काष्ठा iscsi_task *task,
				    काष्ठा iscsi_r2t_info *r2t,
				    काष्ठा iscsi_data *hdr);
बाह्य पूर्णांक iscsi_conn_send_pdu(काष्ठा iscsi_cls_conn *, काष्ठा iscsi_hdr *,
				अक्षर *, uपूर्णांक32_t);
बाह्य पूर्णांक iscsi_complete_pdu(काष्ठा iscsi_conn *, काष्ठा iscsi_hdr *,
			      अक्षर *, पूर्णांक);
बाह्य पूर्णांक __iscsi_complete_pdu(काष्ठा iscsi_conn *, काष्ठा iscsi_hdr *,
				अक्षर *, पूर्णांक);
बाह्य पूर्णांक iscsi_verअगरy_itt(काष्ठा iscsi_conn *, itt_t);
बाह्य काष्ठा iscsi_task *iscsi_itt_to_ctask(काष्ठा iscsi_conn *, itt_t);
बाह्य काष्ठा iscsi_task *iscsi_itt_to_task(काष्ठा iscsi_conn *, itt_t);
बाह्य व्योम iscsi_requeue_task(काष्ठा iscsi_task *task);
बाह्य व्योम iscsi_put_task(काष्ठा iscsi_task *task);
बाह्य व्योम __iscsi_put_task(काष्ठा iscsi_task *task);
बाह्य व्योम __iscsi_get_task(काष्ठा iscsi_task *task);
बाह्य व्योम iscsi_complete_scsi_task(काष्ठा iscsi_task *task,
				     uपूर्णांक32_t exp_cmdsn, uपूर्णांक32_t max_cmdsn);

/*
 * generic helpers
 */
बाह्य व्योम iscsi_pool_मुक्त(काष्ठा iscsi_pool *);
बाह्य पूर्णांक iscsi_pool_init(काष्ठा iscsi_pool *, पूर्णांक, व्योम ***, पूर्णांक);
बाह्य पूर्णांक iscsi_चयन_str_param(अक्षर **, अक्षर *);

/*
 * अंतरभूत functions to deal with padding.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
iscsi_padded(अचिन्हित पूर्णांक len)
अणु
	वापस (len + ISCSI_PAD_LEN - 1) & ~(ISCSI_PAD_LEN - 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
iscsi_padding(अचिन्हित पूर्णांक len)
अणु
	len &= (ISCSI_PAD_LEN - 1);
	अगर (len)
		len = ISCSI_PAD_LEN - len;
	वापस len;
पूर्ण

#पूर्ण_अगर
