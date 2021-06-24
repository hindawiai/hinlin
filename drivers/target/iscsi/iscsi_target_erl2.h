<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_ERL2_H
#घोषणा ISCSI_TARGET_ERL2_H

#समावेश <linux/types.h>

काष्ठा iscsi_cmd;
काष्ठा iscsi_conn;
काष्ठा iscsi_conn_recovery;
काष्ठा iscsi_session;

बाह्य व्योम iscsit_create_conn_recovery_datain_values(काष्ठा iscsi_cmd *, __be32);
बाह्य व्योम iscsit_create_conn_recovery_dataout_values(काष्ठा iscsi_cmd *);
बाह्य काष्ठा iscsi_conn_recovery *iscsit_get_inactive_connection_recovery_entry(
			काष्ठा iscsi_session *, u16);
बाह्य व्योम iscsit_मुक्त_connection_recovery_entries(काष्ठा iscsi_session *);
बाह्य पूर्णांक iscsit_हटाओ_active_connection_recovery_entry(
			काष्ठा iscsi_conn_recovery *, काष्ठा iscsi_session *);
बाह्य पूर्णांक iscsit_हटाओ_cmd_from_connection_recovery(काष्ठा iscsi_cmd *,
			काष्ठा iscsi_session *);
बाह्य व्योम iscsit_discard_cr_cmds_by_expstatsn(काष्ठा iscsi_conn_recovery *, u32);
बाह्य पूर्णांक iscsit_discard_unacknowledged_ooo_cmdsns_क्रम_conn(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_prepare_cmds_क्रम_reallegiance(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_connection_recovery_transport_reset(काष्ठा iscsi_conn *);

#पूर्ण_अगर /*** ISCSI_TARGET_ERL2_H ***/
