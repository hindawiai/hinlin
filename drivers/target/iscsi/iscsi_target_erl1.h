<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_ERL1_H
#घोषणा ISCSI_TARGET_ERL1_H

#समावेश <linux/types.h>
#समावेश <scsi/iscsi_proto.h> /* itt_t */

काष्ठा iscsi_cmd;
काष्ठा iscsi_conn;
काष्ठा iscsi_datain_req;
काष्ठा iscsi_ooo_cmdsn;
काष्ठा iscsi_pdu;
काष्ठा iscsi_session;

बाह्य पूर्णांक iscsit_dump_data_payload(काष्ठा iscsi_conn *, u32, पूर्णांक);
बाह्य पूर्णांक iscsit_create_recovery_datain_values_datasequenceinorder_yes(
			काष्ठा iscsi_cmd *, काष्ठा iscsi_datain_req *);
बाह्य पूर्णांक iscsit_create_recovery_datain_values_datasequenceinorder_no(
			काष्ठा iscsi_cmd *, काष्ठा iscsi_datain_req *);
बाह्य पूर्णांक iscsit_handle_recovery_datain_or_r2t(काष्ठा iscsi_conn *, अचिन्हित अक्षर *,
			itt_t, u32, u32, u32);
बाह्य पूर्णांक iscsit_handle_status_snack(काष्ठा iscsi_conn *, itt_t, u32,
			u32, u32);
बाह्य पूर्णांक iscsit_handle_data_ack(काष्ठा iscsi_conn *, u32, u32, u32);
बाह्य पूर्णांक iscsit_dataout_datapduinorder_no_fbit(काष्ठा iscsi_cmd *, काष्ठा iscsi_pdu *);
बाह्य पूर्णांक iscsit_recover_dataout_sequence(काष्ठा iscsi_cmd *, u32, u32);
बाह्य व्योम iscsit_clear_ooo_cmdsns_क्रम_conn(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_मुक्त_all_ooo_cmdsns(काष्ठा iscsi_session *);
बाह्य पूर्णांक iscsit_execute_ooo_cmdsns(काष्ठा iscsi_session *);
बाह्य पूर्णांक iscsit_execute_cmd(काष्ठा iscsi_cmd *, पूर्णांक);
बाह्य पूर्णांक iscsit_handle_ooo_cmdsn(काष्ठा iscsi_session *, काष्ठा iscsi_cmd *, u32);
बाह्य व्योम iscsit_हटाओ_ooo_cmdsn(काष्ठा iscsi_session *, काष्ठा iscsi_ooo_cmdsn *);
बाह्य व्योम iscsit_handle_dataout_समयout(काष्ठा समयr_list *t);
बाह्य व्योम iscsit_mod_dataout_समयr(काष्ठा iscsi_cmd *);
बाह्य व्योम iscsit_start_dataout_समयr(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_stop_dataout_समयr(काष्ठा iscsi_cmd *);

#पूर्ण_अगर /* ISCSI_TARGET_ERL1_H */
