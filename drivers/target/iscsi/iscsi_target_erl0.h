<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_ERL0_H
#घोषणा ISCSI_TARGET_ERL0_H

#समावेश <linux/types.h>

काष्ठा iscsi_cmd;
काष्ठा iscsi_conn;
काष्ठा iscsi_session;

बाह्य व्योम iscsit_set_dataout_sequence_values(काष्ठा iscsi_cmd *);
बाह्य पूर्णांक iscsit_check_pre_dataout(काष्ठा iscsi_cmd *, अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsit_check_post_dataout(काष्ठा iscsi_cmd *, अचिन्हित अक्षर *, u8);
बाह्य व्योम iscsit_start_समय2retain_handler(काष्ठा iscsi_session *);
बाह्य व्योम iscsit_handle_समय2retain_समयout(काष्ठा समयr_list *t);
बाह्य पूर्णांक iscsit_stop_समय2retain_समयr(काष्ठा iscsi_session *);
बाह्य व्योम iscsit_connection_reinstatement_rcfr(काष्ठा iscsi_conn *);
बाह्य व्योम iscsit_cause_connection_reinstatement(काष्ठा iscsi_conn *, पूर्णांक);
बाह्य व्योम iscsit_fall_back_to_erl0(काष्ठा iscsi_session *);
बाह्य व्योम iscsit_take_action_क्रम_connection_निकास(काष्ठा iscsi_conn *, bool *);

#पूर्ण_अगर   /*** ISCSI_TARGET_ERL0_H ***/
