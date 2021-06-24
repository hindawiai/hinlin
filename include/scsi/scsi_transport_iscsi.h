<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * iSCSI transport class definitions
 *
 * Copyright (C) IBM Corporation, 2004
 * Copyright (C) Mike Christie, 2004 - 2006
 * Copyright (C) Dmitry Yusupov, 2004 - 2005
 * Copyright (C) Alex Aizman, 2004 - 2005
 */
#अगर_अघोषित SCSI_TRANSPORT_ISCSI_H
#घोषणा SCSI_TRANSPORT_ISCSI_H

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <scsi/iscsi_अगर.h>

काष्ठा scsi_transport_ढाँचा;
काष्ठा iscsi_transport;
काष्ठा iscsi_endpoपूर्णांक;
काष्ठा Scsi_Host;
काष्ठा scsi_cmnd;
काष्ठा iscsi_cls_conn;
काष्ठा iscsi_conn;
काष्ठा iscsi_task;
काष्ठा sockaddr;
काष्ठा iscsi_अगरace;
काष्ठा bsg_job;
काष्ठा iscsi_bus_flash_session;
काष्ठा iscsi_bus_flash_conn;

/**
 * काष्ठा iscsi_transport - iSCSI Transport ढाँचा
 *
 * @name:		transport name
 * @caps:		iSCSI Data-Path capabilities
 * @create_session:	create new iSCSI session object
 * @destroy_session:	destroy existing iSCSI session object
 * @create_conn:	create new iSCSI connection
 * @bind_conn:		associate this connection with existing iSCSI session
 *			and specअगरied transport descriptor
 * @destroy_conn:	destroy inactive iSCSI connection
 * @set_param:		set iSCSI parameter. Return 0 on success, -ENODATA
 *			when param is not supported, and a -Exx value on other
 *			error.
 * @get_param		get iSCSI parameter. Must वापस number of bytes
 *			copied to buffer on success, -ENODATA when param
 *			is not supported, and a -Exx value on other error
 * @start_conn:		set connection to be operational
 * @stop_conn:		suspend/recover/terminate connection
 * @send_pdu:		send iSCSI PDU, Login, Logout, NOP-Out, Reject, Text.
 * @session_recovery_समयकरोut: notअगरy LLD a block during recovery समयd out
 * @init_task:		Initialize a iscsi_task and any पूर्णांकernal काष्ठाs.
 *			When offloading the data path, this is called from
 *			queuecommand with the session lock, or from the
 *			iscsi_conn_send_pdu context with the session lock.
 *			When not offloading the data path, this is called
 *			from the scsi work queue without the session lock.
 * @xmit_task		Requests LLD to transfer cmd task. Returns 0 or the
 *			number of bytes transferred on success, and -Exyz
 *			value on error. When offloading the data path, this
 *			is called from queuecommand with the session lock, or
 *			from the iscsi_conn_send_pdu context with the session
 *			lock. When not offloading the data path, this is called
 *			from the scsi work queue without the session lock.
 * @cleanup_task:	requests LLD to fail task. Called with session lock
 *			and after the connection has been suspended and
 *			terminated during recovery. If called
 *			from पात task then connection is not suspended
 *			or terminated but sk_callback_lock is held
 *
 * Template API provided by iSCSI Transport
 */
काष्ठा iscsi_transport अणु
	काष्ठा module *owner;
	अक्षर *name;
	अचिन्हित पूर्णांक caps;

	काष्ठा iscsi_cls_session *(*create_session) (काष्ठा iscsi_endpoपूर्णांक *ep,
					uपूर्णांक16_t cmds_max, uपूर्णांक16_t qdepth,
					uपूर्णांक32_t sn);
	व्योम (*destroy_session) (काष्ठा iscsi_cls_session *session);
	काष्ठा iscsi_cls_conn *(*create_conn) (काष्ठा iscsi_cls_session *sess,
				uपूर्णांक32_t cid);
	पूर्णांक (*bind_conn) (काष्ठा iscsi_cls_session *session,
			  काष्ठा iscsi_cls_conn *cls_conn,
			  uपूर्णांक64_t transport_eph, पूर्णांक is_leading);
	पूर्णांक (*start_conn) (काष्ठा iscsi_cls_conn *conn);
	व्योम (*stop_conn) (काष्ठा iscsi_cls_conn *conn, पूर्णांक flag);
	व्योम (*destroy_conn) (काष्ठा iscsi_cls_conn *conn);
	पूर्णांक (*set_param) (काष्ठा iscsi_cls_conn *conn, क्रमागत iscsi_param param,
			  अक्षर *buf, पूर्णांक buflen);
	पूर्णांक (*get_ep_param) (काष्ठा iscsi_endpoपूर्णांक *ep, क्रमागत iscsi_param param,
			     अक्षर *buf);
	पूर्णांक (*get_conn_param) (काष्ठा iscsi_cls_conn *conn,
			       क्रमागत iscsi_param param, अक्षर *buf);
	पूर्णांक (*get_session_param) (काष्ठा iscsi_cls_session *session,
				  क्रमागत iscsi_param param, अक्षर *buf);
	पूर्णांक (*get_host_param) (काष्ठा Scsi_Host *shost,
				क्रमागत iscsi_host_param param, अक्षर *buf);
	पूर्णांक (*set_host_param) (काष्ठा Scsi_Host *shost,
			       क्रमागत iscsi_host_param param, अक्षर *buf,
			       पूर्णांक buflen);
	पूर्णांक (*send_pdu) (काष्ठा iscsi_cls_conn *conn, काष्ठा iscsi_hdr *hdr,
			 अक्षर *data, uपूर्णांक32_t data_size);
	व्योम (*get_stats) (काष्ठा iscsi_cls_conn *conn,
			   काष्ठा iscsi_stats *stats);

	पूर्णांक (*init_task) (काष्ठा iscsi_task *task);
	पूर्णांक (*xmit_task) (काष्ठा iscsi_task *task);
	व्योम (*cleanup_task) (काष्ठा iscsi_task *task);

	पूर्णांक (*alloc_pdu) (काष्ठा iscsi_task *task, uपूर्णांक8_t opcode);
	पूर्णांक (*xmit_pdu) (काष्ठा iscsi_task *task);
	पूर्णांक (*init_pdu) (काष्ठा iscsi_task *task, अचिन्हित पूर्णांक offset,
			 अचिन्हित पूर्णांक count);
	व्योम (*parse_pdu_itt) (काष्ठा iscsi_conn *conn, itt_t itt,
			       पूर्णांक *index, पूर्णांक *age);

	व्योम (*session_recovery_समयकरोut) (काष्ठा iscsi_cls_session *session);
	काष्ठा iscsi_endpoपूर्णांक *(*ep_connect) (काष्ठा Scsi_Host *shost,
					      काष्ठा sockaddr *dst_addr,
					      पूर्णांक non_blocking);
	पूर्णांक (*ep_poll) (काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms);
	व्योम (*ep_disconnect) (काष्ठा iscsi_endpoपूर्णांक *ep);
	पूर्णांक (*tgt_dscvr) (काष्ठा Scsi_Host *shost, क्रमागत iscsi_tgt_dscvr type,
			  uपूर्णांक32_t enable, काष्ठा sockaddr *dst_addr);
	पूर्णांक (*set_path) (काष्ठा Scsi_Host *shost, काष्ठा iscsi_path *params);
	पूर्णांक (*set_अगरace_param) (काष्ठा Scsi_Host *shost, व्योम *data,
				uपूर्णांक32_t len);
	पूर्णांक (*get_अगरace_param) (काष्ठा iscsi_अगरace *अगरace,
				क्रमागत iscsi_param_type param_type,
				पूर्णांक param, अक्षर *buf);
	umode_t (*attr_is_visible)(पूर्णांक param_type, पूर्णांक param);
	पूर्णांक (*bsg_request)(काष्ठा bsg_job *job);
	पूर्णांक (*send_ping) (काष्ठा Scsi_Host *shost, uपूर्णांक32_t अगरace_num,
			  uपूर्णांक32_t अगरace_type, uपूर्णांक32_t payload_size,
			  uपूर्णांक32_t pid, काष्ठा sockaddr *dst_addr);
	पूर्णांक (*get_chap) (काष्ठा Scsi_Host *shost, uपूर्णांक16_t chap_tbl_idx,
			 uपूर्णांक32_t *num_entries, अक्षर *buf);
	पूर्णांक (*delete_chap) (काष्ठा Scsi_Host *shost, uपूर्णांक16_t chap_tbl_idx);
	पूर्णांक (*set_chap) (काष्ठा Scsi_Host *shost, व्योम *data, पूर्णांक len);
	पूर्णांक (*get_flashnode_param) (काष्ठा iscsi_bus_flash_session *fnode_sess,
				    पूर्णांक param, अक्षर *buf);
	पूर्णांक (*set_flashnode_param) (काष्ठा iscsi_bus_flash_session *fnode_sess,
				    काष्ठा iscsi_bus_flash_conn *fnode_conn,
				    व्योम *data, पूर्णांक len);
	पूर्णांक (*new_flashnode) (काष्ठा Scsi_Host *shost, स्थिर अक्षर *buf,
			      पूर्णांक len);
	पूर्णांक (*del_flashnode) (काष्ठा iscsi_bus_flash_session *fnode_sess);
	पूर्णांक (*login_flashnode) (काष्ठा iscsi_bus_flash_session *fnode_sess,
				काष्ठा iscsi_bus_flash_conn *fnode_conn);
	पूर्णांक (*logout_flashnode) (काष्ठा iscsi_bus_flash_session *fnode_sess,
				 काष्ठा iscsi_bus_flash_conn *fnode_conn);
	पूर्णांक (*logout_flashnode_sid) (काष्ठा iscsi_cls_session *cls_sess);
	पूर्णांक (*get_host_stats) (काष्ठा Scsi_Host *shost, अक्षर *buf, पूर्णांक len);
	u8 (*check_protection)(काष्ठा iscsi_task *task, sector_t *sector);
पूर्ण;

/*
 * transport registration upcalls
 */
बाह्य काष्ठा scsi_transport_ढाँचा *iscsi_रेजिस्टर_transport(काष्ठा iscsi_transport *tt);
बाह्य पूर्णांक iscsi_unरेजिस्टर_transport(काष्ठा iscsi_transport *tt);

/*
 * control plane upcalls
 */
बाह्य व्योम iscsi_conn_error_event(काष्ठा iscsi_cls_conn *conn,
				   क्रमागत iscsi_err error);
बाह्य व्योम iscsi_conn_login_event(काष्ठा iscsi_cls_conn *conn,
				   क्रमागत iscsi_conn_state state);
बाह्य पूर्णांक iscsi_recv_pdu(काष्ठा iscsi_cls_conn *conn, काष्ठा iscsi_hdr *hdr,
			  अक्षर *data, uपूर्णांक32_t data_size);

बाह्य पूर्णांक iscsi_offload_mesg(काष्ठा Scsi_Host *shost,
			      काष्ठा iscsi_transport *transport, uपूर्णांक32_t type,
			      अक्षर *data, uपूर्णांक16_t data_size);

बाह्य व्योम iscsi_post_host_event(uपूर्णांक32_t host_no,
				  काष्ठा iscsi_transport *transport,
				  क्रमागत iscsi_host_event_code code,
				  uपूर्णांक32_t data_size,
				  uपूर्णांक8_t *data);

बाह्य व्योम iscsi_ping_comp_event(uपूर्णांक32_t host_no,
				  काष्ठा iscsi_transport *transport,
				  uपूर्णांक32_t status, uपूर्णांक32_t pid,
				  uपूर्णांक32_t data_size, uपूर्णांक8_t *data);

/* iscsi class connection state */
क्रमागत iscsi_connection_state अणु
	ISCSI_CONN_UP = 0,
	ISCSI_CONN_DOWN,
	ISCSI_CONN_FAILED,
	ISCSI_CONN_BOUND,
पूर्ण;

काष्ठा iscsi_cls_conn अणु
	काष्ठा list_head conn_list;	/* item in connlist */
	काष्ठा list_head conn_list_err;	/* item in connlist_err */
	व्योम *dd_data;			/* LLD निजी data */
	काष्ठा iscsi_transport *transport;
	uपूर्णांक32_t cid;			/* connection id */
	काष्ठा mutex ep_mutex;
	काष्ठा iscsi_endpoपूर्णांक *ep;

	काष्ठा device dev;		/* sysfs transport/container device */
	क्रमागत iscsi_connection_state state;
पूर्ण;

#घोषणा iscsi_dev_to_conn(_dev) \
	container_of(_dev, काष्ठा iscsi_cls_conn, dev)

#घोषणा transport_class_to_conn(_cdev) \
	iscsi_dev_to_conn(_cdev->parent)

#घोषणा iscsi_conn_to_session(_conn) \
	iscsi_dev_to_session(_conn->dev.parent)

/* iscsi class session state */
क्रमागत अणु
	ISCSI_SESSION_LOGGED_IN,
	ISCSI_SESSION_FAILED,
	ISCSI_SESSION_FREE,
पूर्ण;

#घोषणा ISCSI_MAX_TARGET -1

काष्ठा iscsi_cls_session अणु
	काष्ठा list_head sess_list;		/* item in session_list */
	काष्ठा iscsi_transport *transport;
	spinlock_t lock;
	काष्ठा work_काष्ठा block_work;
	काष्ठा work_काष्ठा unblock_work;
	काष्ठा work_काष्ठा scan_work;
	काष्ठा work_काष्ठा unbind_work;
	काष्ठा work_काष्ठा destroy_work;

	/* recovery fields */
	पूर्णांक recovery_पंचांगo;
	bool recovery_पंचांगo_sysfs_override;
	काष्ठा delayed_work recovery_work;

	अचिन्हित पूर्णांक target_id;
	bool ida_used;

	/*
	 * pid of userspace process that created session or -1 अगर
	 * created by the kernel.
	 */
	pid_t creator;
	पूर्णांक state;
	पूर्णांक sid;				/* session id */
	व्योम *dd_data;				/* LLD निजी data */
	काष्ठा device dev;	/* sysfs transport/container device */
पूर्ण;

#घोषणा iscsi_dev_to_session(_dev) \
	container_of(_dev, काष्ठा iscsi_cls_session, dev)

#घोषणा transport_class_to_session(_cdev) \
	iscsi_dev_to_session(_cdev->parent)

#घोषणा iscsi_session_to_shost(_session) \
	dev_to_shost(_session->dev.parent)

#घोषणा starget_to_session(_stgt) \
	iscsi_dev_to_session(_stgt->dev.parent)

काष्ठा iscsi_cls_host अणु
	atomic_t nr_scans;
	काष्ठा mutex mutex;
	काष्ठा request_queue *bsg_q;
	uपूर्णांक32_t port_speed;
	uपूर्णांक32_t port_state;
पूर्ण;

#घोषणा iscsi_job_to_shost(_job) \
        dev_to_shost(_job->dev)

बाह्य व्योम iscsi_host_क्रम_each_session(काष्ठा Scsi_Host *shost,
				व्योम (*fn)(काष्ठा iscsi_cls_session *));

काष्ठा iscsi_endpoपूर्णांक अणु
	व्योम *dd_data;			/* LLD निजी data */
	काष्ठा device dev;
	uपूर्णांक64_t id;
	काष्ठा iscsi_cls_conn *conn;
पूर्ण;

काष्ठा iscsi_अगरace अणु
	काष्ठा device dev;
	काष्ठा iscsi_transport *transport;
	uपूर्णांक32_t अगरace_type;	/* IPv4 or IPv6 */
	uपूर्णांक32_t अगरace_num;	/* अगरace number, 0 - n */
	व्योम *dd_data;		/* LLD निजी data */
पूर्ण;

#घोषणा iscsi_dev_to_अगरace(_dev) \
	container_of(_dev, काष्ठा iscsi_अगरace, dev)

#घोषणा iscsi_अगरace_to_shost(_अगरace) \
	dev_to_shost(_अगरace->dev.parent)


काष्ठा iscsi_bus_flash_conn अणु
	काष्ठा list_head conn_list;	/* item in connlist */
	व्योम *dd_data;			/* LLD निजी data */
	काष्ठा iscsi_transport *transport;
	काष्ठा device dev;		/* sysfs transport/container device */
	/* iscsi connection parameters */
	uपूर्णांक32_t		exp_statsn;
	uपूर्णांक32_t		statsn;
	अचिन्हित		max_recv_dlength; /* initiator_max_recv_dsl*/
	अचिन्हित		max_xmit_dlength; /* target_max_recv_dsl */
	अचिन्हित		max_segment_size;
	अचिन्हित		tcp_xmit_wsf;
	अचिन्हित		tcp_recv_wsf;
	पूर्णांक			hdrdgst_en;
	पूर्णांक			datadgst_en;
	पूर्णांक			port;
	अक्षर			*ipaddress;
	अक्षर			*link_local_ipv6_addr;
	अक्षर			*redirect_ipaddr;
	uपूर्णांक16_t		keepalive_समयout;
	uपूर्णांक16_t		local_port;
	uपूर्णांक8_t			snack_req_en;
	/* tcp बारtamp negotiation status */
	uपूर्णांक8_t			tcp_बारtamp_stat;
	uपूर्णांक8_t			tcp_nagle_disable;
	/* tcp winकरोw scale factor */
	uपूर्णांक8_t			tcp_wsf_disable;
	uपूर्णांक8_t			tcp_समयr_scale;
	uपूर्णांक8_t			tcp_बारtamp_en;
	uपूर्णांक8_t			ipv4_tos;
	uपूर्णांक8_t			ipv6_traffic_class;
	uपूर्णांक8_t			ipv6_flow_label;
	uपूर्णांक8_t			fragment_disable;
	/* Link local IPv6 address is asचिन्हित by firmware or driver */
	uपूर्णांक8_t			is_fw_asचिन्हित_ipv6;
पूर्ण;

#घोषणा iscsi_dev_to_flash_conn(_dev) \
	container_of(_dev, काष्ठा iscsi_bus_flash_conn, dev)

#घोषणा iscsi_flash_conn_to_flash_session(_conn) \
	iscsi_dev_to_flash_session(_conn->dev.parent)

#घोषणा ISID_SIZE 6

काष्ठा iscsi_bus_flash_session अणु
	काष्ठा list_head sess_list;		/* item in session_list */
	काष्ठा iscsi_transport *transport;
	अचिन्हित पूर्णांक target_id;
	पूर्णांक flash_state;	/* persistent or non-persistent */
	व्योम *dd_data;				/* LLD निजी data */
	काष्ठा device dev;	/* sysfs transport/container device */
	/* iscsi session parameters */
	अचिन्हित		first_burst;
	अचिन्हित		max_burst;
	अचिन्हित लघु		max_r2t;
	पूर्णांक			शेष_taskmgmt_समयout;
	पूर्णांक			initial_r2t_en;
	पूर्णांक			imm_data_en;
	पूर्णांक			समय2रुको;
	पूर्णांक			समय2retain;
	पूर्णांक			pdu_inorder_en;
	पूर्णांक			dataseq_inorder_en;
	पूर्णांक			erl;
	पूर्णांक			tpgt;
	अक्षर			*username;
	अक्षर			*username_in;
	अक्षर			*password;
	अक्षर			*password_in;
	अक्षर			*targetname;
	अक्षर			*targetalias;
	अक्षर			*portal_type;
	uपूर्णांक16_t		tsid;
	uपूर्णांक16_t		chap_in_idx;
	uपूर्णांक16_t		chap_out_idx;
	/* index of iSCSI discovery session अगर the entry is
	 * discovered by iSCSI discovery session
	 */
	uपूर्णांक16_t		discovery_parent_idx;
	/* indicates अगर discovery was करोne through iSNS discovery service
	 * or through sendTarget */
	uपूर्णांक16_t		discovery_parent_type;
	/* Firmware स्वतः sendtarget discovery disable */
	uपूर्णांक8_t			स्वतः_snd_tgt_disable;
	uपूर्णांक8_t			discovery_sess;
	/* indicates अगर this flashnode entry is enabled or disabled */
	uपूर्णांक8_t			entry_state;
	uपूर्णांक8_t			chap_auth_en;
	/* enables firmware to स्वतः logout the discovery session on discovery
	 * completion
	 */
	uपूर्णांक8_t			discovery_logout_en;
	uपूर्णांक8_t			bidi_chap_en;
	/* makes authentication क्रम discovery session optional */
	uपूर्णांक8_t			discovery_auth_optional;
	uपूर्णांक8_t			isid[ISID_SIZE];
	uपूर्णांक8_t			is_boot_target;
पूर्ण;

#घोषणा iscsi_dev_to_flash_session(_dev) \
	container_of(_dev, काष्ठा iscsi_bus_flash_session, dev)

#घोषणा iscsi_flash_session_to_shost(_session) \
	dev_to_shost(_session->dev.parent)

/*
 * session and connection functions that can be used by HW iSCSI LLDs
 */
#घोषणा iscsi_cls_session_prपूर्णांकk(prefix, _cls_session, fmt, a...) \
	dev_prपूर्णांकk(prefix, &(_cls_session)->dev, fmt, ##a)

#घोषणा iscsi_cls_conn_prपूर्णांकk(prefix, _cls_conn, fmt, a...) \
	dev_prपूर्णांकk(prefix, &(_cls_conn)->dev, fmt, ##a)

बाह्य पूर्णांक iscsi_session_chkपढ़ोy(काष्ठा iscsi_cls_session *session);
बाह्य पूर्णांक iscsi_is_session_online(काष्ठा iscsi_cls_session *session);
बाह्य काष्ठा iscsi_cls_session *iscsi_alloc_session(काष्ठा Scsi_Host *shost,
				काष्ठा iscsi_transport *transport, पूर्णांक dd_size);
बाह्य पूर्णांक iscsi_add_session(काष्ठा iscsi_cls_session *session,
			     अचिन्हित पूर्णांक target_id);
बाह्य पूर्णांक iscsi_session_event(काष्ठा iscsi_cls_session *session,
			       क्रमागत iscsi_uevent_e event);
बाह्य काष्ठा iscsi_cls_session *iscsi_create_session(काष्ठा Scsi_Host *shost,
						काष्ठा iscsi_transport *t,
						पूर्णांक dd_size,
						अचिन्हित पूर्णांक target_id);
बाह्य व्योम iscsi_हटाओ_session(काष्ठा iscsi_cls_session *session);
बाह्य व्योम iscsi_मुक्त_session(काष्ठा iscsi_cls_session *session);
बाह्य काष्ठा iscsi_cls_conn *iscsi_create_conn(काष्ठा iscsi_cls_session *sess,
						पूर्णांक dd_size, uपूर्णांक32_t cid);
बाह्य पूर्णांक iscsi_destroy_conn(काष्ठा iscsi_cls_conn *conn);
बाह्य व्योम iscsi_unblock_session(काष्ठा iscsi_cls_session *session);
बाह्य व्योम iscsi_block_session(काष्ठा iscsi_cls_session *session);
बाह्य पूर्णांक iscsi_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय);
बाह्य काष्ठा iscsi_endpoपूर्णांक *iscsi_create_endpoपूर्णांक(पूर्णांक dd_size);
बाह्य व्योम iscsi_destroy_endpoपूर्णांक(काष्ठा iscsi_endpoपूर्णांक *ep);
बाह्य काष्ठा iscsi_endpoपूर्णांक *iscsi_lookup_endpoपूर्णांक(u64 handle);
बाह्य पूर्णांक iscsi_block_scsi_eh(काष्ठा scsi_cmnd *cmd);
बाह्य काष्ठा iscsi_अगरace *iscsi_create_अगरace(काष्ठा Scsi_Host *shost,
					      काष्ठा iscsi_transport *t,
					      uपूर्णांक32_t अगरace_type,
					      uपूर्णांक32_t अगरace_num, पूर्णांक dd_size);
बाह्य व्योम iscsi_destroy_अगरace(काष्ठा iscsi_अगरace *अगरace);
बाह्य काष्ठा iscsi_अगरace *iscsi_lookup_अगरace(पूर्णांक handle);
बाह्य अक्षर *iscsi_get_port_speed_name(काष्ठा Scsi_Host *shost);
बाह्य अक्षर *iscsi_get_port_state_name(काष्ठा Scsi_Host *shost);
बाह्य पूर्णांक iscsi_is_session_dev(स्थिर काष्ठा device *dev);

बाह्य अक्षर *iscsi_get_discovery_parent_name(पूर्णांक parent_type);
बाह्य काष्ठा device *
iscsi_find_flashnode(काष्ठा Scsi_Host *shost, व्योम *data,
		     पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data));

बाह्य काष्ठा iscsi_bus_flash_session *
iscsi_create_flashnode_sess(काष्ठा Scsi_Host *shost, पूर्णांक index,
			    काष्ठा iscsi_transport *transport, पूर्णांक dd_size);

बाह्य काष्ठा iscsi_bus_flash_conn *
iscsi_create_flashnode_conn(काष्ठा Scsi_Host *shost,
			    काष्ठा iscsi_bus_flash_session *fnode_sess,
			    काष्ठा iscsi_transport *transport, पूर्णांक dd_size);

बाह्य व्योम
iscsi_destroy_flashnode_sess(काष्ठा iscsi_bus_flash_session *fnode_sess);

बाह्य व्योम iscsi_destroy_all_flashnode(काष्ठा Scsi_Host *shost);
बाह्य पूर्णांक iscsi_flashnode_bus_match(काष्ठा device *dev,
				     काष्ठा device_driver *drv);
बाह्य काष्ठा device *
iscsi_find_flashnode_sess(काष्ठा Scsi_Host *shost, व्योम *data,
			  पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data));
बाह्य काष्ठा device *
iscsi_find_flashnode_conn(काष्ठा iscsi_bus_flash_session *fnode_sess);

बाह्य अक्षर *
iscsi_get_ipaddress_state_name(क्रमागत iscsi_ipaddress_state port_state);
बाह्य अक्षर *iscsi_get_router_state_name(क्रमागत iscsi_router_state router_state);
#पूर्ण_अगर
