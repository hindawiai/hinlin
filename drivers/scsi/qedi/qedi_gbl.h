<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#अगर_अघोषित _QEDI_GBL_H_
#घोषणा _QEDI_GBL_H_

#समावेश "qedi_iscsi.h"

#अगर_घोषित CONFIG_DEBUG_FS
बाह्य पूर्णांक qedi_करो_not_recover;
#अन्यथा
#घोषणा qedi_करो_not_recover (0)
#पूर्ण_अगर

बाह्य uपूर्णांक qedi_io_tracing;

बाह्य काष्ठा scsi_host_ढाँचा qedi_host_ढाँचा;
बाह्य काष्ठा iscsi_transport qedi_iscsi_transport;
बाह्य स्थिर काष्ठा qed_iscsi_ops *qedi_ops;
बाह्य स्थिर काष्ठा qedi_debugfs_ops qedi_debugfs_ops[];
बाह्य स्थिर काष्ठा file_operations qedi_dbg_fops[];
बाह्य काष्ठा device_attribute *qedi_shost_attrs[];

पूर्णांक qedi_alloc_sq(काष्ठा qedi_ctx *qedi, काष्ठा qedi_endpoपूर्णांक *ep);
व्योम qedi_मुक्त_sq(काष्ठा qedi_ctx *qedi, काष्ठा qedi_endpoपूर्णांक *ep);

पूर्णांक qedi_send_iscsi_login(काष्ठा qedi_conn *qedi_conn,
			  काष्ठा iscsi_task *task);
पूर्णांक qedi_send_iscsi_logout(काष्ठा qedi_conn *qedi_conn,
			   काष्ठा iscsi_task *task);
पूर्णांक qedi_iscsi_पात_work(काष्ठा qedi_conn *qedi_conn,
			  काष्ठा iscsi_task *mtask);
पूर्णांक qedi_send_iscsi_text(काष्ठा qedi_conn *qedi_conn,
			 काष्ठा iscsi_task *task);
पूर्णांक qedi_send_iscsi_nopout(काष्ठा qedi_conn *qedi_conn,
			   काष्ठा iscsi_task *task,
			   अक्षर *datap, पूर्णांक data_len, पूर्णांक unsol);
पूर्णांक qedi_iscsi_send_ioreq(काष्ठा iscsi_task *task);
पूर्णांक qedi_get_task_idx(काष्ठा qedi_ctx *qedi);
व्योम qedi_clear_task_idx(काष्ठा qedi_ctx *qedi, पूर्णांक idx);
पूर्णांक qedi_iscsi_cleanup_task(काष्ठा iscsi_task *task,
			    bool mark_cmd_node_deleted);
व्योम qedi_iscsi_unmap_sg_list(काष्ठा qedi_cmd *cmd);
व्योम qedi_update_itt_map(काष्ठा qedi_ctx *qedi, u32 tid, u32 proto_itt,
			 काष्ठा qedi_cmd *qedi_cmd);
व्योम qedi_get_proto_itt(काष्ठा qedi_ctx *qedi, u32 tid, u32 *proto_itt);
व्योम qedi_get_task_tid(काष्ठा qedi_ctx *qedi, u32 itt, पूर्णांक16_t *tid);
व्योम qedi_process_iscsi_error(काष्ठा qedi_endpoपूर्णांक *ep,
			      काष्ठा iscsi_eqe_data *data);
व्योम qedi_start_conn_recovery(काष्ठा qedi_ctx *qedi,
			      काष्ठा qedi_conn *qedi_conn);
काष्ठा qedi_conn *qedi_get_conn_from_id(काष्ठा qedi_ctx *qedi, u32 iscsi_cid);
व्योम qedi_process_tcp_error(काष्ठा qedi_endpoपूर्णांक *ep,
			    काष्ठा iscsi_eqe_data *data);
व्योम qedi_mark_device_missing(काष्ठा iscsi_cls_session *cls_session);
व्योम qedi_mark_device_available(काष्ठा iscsi_cls_session *cls_session);
व्योम qedi_reset_host_mtu(काष्ठा qedi_ctx *qedi, u16 mtu);
पूर्णांक qedi_recover_all_conns(काष्ठा qedi_ctx *qedi);
व्योम qedi_fp_process_cqes(काष्ठा qedi_work *work);
पूर्णांक qedi_cleanup_all_io(काष्ठा qedi_ctx *qedi,
			काष्ठा qedi_conn *qedi_conn,
			काष्ठा iscsi_task *task, bool in_recovery);
व्योम qedi_trace_io(काष्ठा qedi_ctx *qedi, काष्ठा iscsi_task *task,
		   u16 tid, पूर्णांक8_t direction);
पूर्णांक qedi_alloc_id(काष्ठा qedi_portid_tbl *id_tbl, u16 id);
u16 qedi_alloc_new_id(काष्ठा qedi_portid_tbl *id_tbl);
व्योम qedi_मुक्त_id(काष्ठा qedi_portid_tbl *id_tbl, u16 id);
पूर्णांक qedi_create_sysfs_ctx_attr(काष्ठा qedi_ctx *qedi);
व्योम qedi_हटाओ_sysfs_ctx_attr(काष्ठा qedi_ctx *qedi);
व्योम qedi_clearsq(काष्ठा qedi_ctx *qedi,
		  काष्ठा qedi_conn *qedi_conn,
		  काष्ठा iscsi_task *task);
व्योम qedi_clear_session_ctx(काष्ठा iscsi_cls_session *cls_sess);

#पूर्ण_अगर
