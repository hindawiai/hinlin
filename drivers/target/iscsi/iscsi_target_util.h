<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_UTIL_H
#घोषणा ISCSI_TARGET_UTIL_H

#समावेश <linux/types.h>
#समावेश <scsi/iscsi_proto.h>        /* itt_t */

#घोषणा MARKER_SIZE	8

काष्ठा iscsi_cmd;
काष्ठा iscsi_conn;
काष्ठा iscsi_conn_recovery;
काष्ठा iscsi_session;

बाह्य पूर्णांक iscsit_add_r2t_to_list(काष्ठा iscsi_cmd *, u32, u32, पूर्णांक, u32);
बाह्य काष्ठा iscsi_r2t *iscsit_get_r2t_क्रम_eos(काष्ठा iscsi_cmd *, u32, u32);
बाह्य काष्ठा iscsi_r2t *iscsit_get_r2t_from_list(काष्ठा iscsi_cmd *);
बाह्य व्योम iscsit_मुक्त_r2t(काष्ठा iscsi_r2t *, काष्ठा iscsi_cmd *);
बाह्य व्योम iscsit_मुक्त_r2ts_from_list(काष्ठा iscsi_cmd *);
बाह्य काष्ठा iscsi_cmd *iscsit_alloc_cmd(काष्ठा iscsi_conn *, gfp_t);
बाह्य काष्ठा iscsi_cmd *iscsit_allocate_cmd(काष्ठा iscsi_conn *, पूर्णांक);
बाह्य काष्ठा iscsi_seq *iscsit_get_seq_holder_क्रम_datain(काष्ठा iscsi_cmd *, u32);
बाह्य काष्ठा iscsi_seq *iscsit_get_seq_holder_क्रम_r2t(काष्ठा iscsi_cmd *);
बाह्य काष्ठा iscsi_r2t *iscsit_get_holder_क्रम_r2tsn(काष्ठा iscsi_cmd *, u32);
बाह्य पूर्णांक iscsit_sequence_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			       अचिन्हित अक्षर * ,__be32 cmdsn);
बाह्य पूर्णांक iscsit_check_unsolicited_dataout(काष्ठा iscsi_cmd *, अचिन्हित अक्षर *);
बाह्य काष्ठा iscsi_cmd *iscsit_find_cmd_from_itt_or_dump(काष्ठा iscsi_conn *,
			itt_t, u32);
बाह्य काष्ठा iscsi_cmd *iscsit_find_cmd_from_ttt(काष्ठा iscsi_conn *, u32);
बाह्य पूर्णांक iscsit_find_cmd_क्रम_recovery(काष्ठा iscsi_session *, काष्ठा iscsi_cmd **,
			काष्ठा iscsi_conn_recovery **, itt_t);
बाह्य व्योम iscsit_add_cmd_to_immediate_queue(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *, u8);
बाह्य काष्ठा iscsi_queue_req *iscsit_get_cmd_from_immediate_queue(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_add_cmd_to_response_queue(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *, u8);
बाह्य काष्ठा iscsi_queue_req *iscsit_get_cmd_from_response_queue(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_हटाओ_cmd_from_tx_queues(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);
बाह्य bool iscsit_conn_all_queues_empty(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_मुक्त_queue_reqs_क्रम_conn(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_release_cmd(काष्ठा iscsi_cmd *);
बाह्य व्योम __iscsit_मुक्त_cmd(काष्ठा iscsi_cmd *, bool);
बाह्य व्योम iscsit_मुक्त_cmd(काष्ठा iscsi_cmd *, bool);
बाह्य bool iscsit_check_session_usage_count(काष्ठा iscsi_session *sess, bool can_sleep);
बाह्य व्योम iscsit_dec_session_usage_count(काष्ठा iscsi_session *);
बाह्य व्योम iscsit_inc_session_usage_count(काष्ठा iscsi_session *);
बाह्य काष्ठा iscsi_conn *iscsit_get_conn_from_cid(काष्ठा iscsi_session *, u16);
बाह्य काष्ठा iscsi_conn *iscsit_get_conn_from_cid_rcfr(काष्ठा iscsi_session *, u16);
बाह्य व्योम iscsit_check_conn_usage_count(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_dec_conn_usage_count(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_inc_conn_usage_count(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_handle_nopin_response_समयout(काष्ठा समयr_list *t);
बाह्य व्योम iscsit_mod_nopin_response_समयr(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_start_nopin_response_समयr(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_stop_nopin_response_समयr(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_handle_nopin_समयout(काष्ठा समयr_list *t);
बाह्य व्योम __iscsit_start_nopin_समयr(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_start_nopin_समयr(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_stop_nopin_समयr(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_send_tx_data(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *, पूर्णांक);
बाह्य पूर्णांक iscsit_fe_sendpage_sg(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_tx_login_rsp(काष्ठा iscsi_conn *, u8, u8);
बाह्य व्योम iscsit_prपूर्णांक_session_params(काष्ठा iscsi_session *);
बाह्य पूर्णांक iscsit_prपूर्णांक_dev_to_proc(अक्षर *, अक्षर **, off_t, पूर्णांक);
बाह्य पूर्णांक iscsit_prपूर्णांक_sessions_to_proc(अक्षर *, अक्षर **, off_t, पूर्णांक);
बाह्य पूर्णांक iscsit_prपूर्णांक_tpg_to_proc(अक्षर *, अक्षर **, off_t, पूर्णांक);
बाह्य पूर्णांक rx_data(काष्ठा iscsi_conn *, काष्ठा kvec *, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक tx_data(काष्ठा iscsi_conn *, काष्ठा kvec *, पूर्णांक, पूर्णांक);
बाह्य व्योम iscsit_collect_login_stats(काष्ठा iscsi_conn *, u8, u8);
बाह्य काष्ठा iscsi_tiqn *iscsit_snmp_get_tiqn(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_fill_cxn_समयout_err_stats(काष्ठा iscsi_session *);

#पूर्ण_अगर /*** ISCSI_TARGET_UTIL_H ***/
