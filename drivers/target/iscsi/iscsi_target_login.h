<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_LOGIN_H
#घोषणा ISCSI_TARGET_LOGIN_H

#समावेश <linux/types.h>

काष्ठा iscsi_conn;
काष्ठा iscsi_login;
काष्ठा iscsi_np;
काष्ठा sockaddr_storage;

बाह्य पूर्णांक iscsi_login_setup_crypto(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsi_check_क्रम_session_reinstatement(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsi_login_post_auth_non_zero_tsih(काष्ठा iscsi_conn *, u16, u32);
बाह्य पूर्णांक iscsit_setup_np(काष्ठा iscsi_np *,
				काष्ठा sockaddr_storage *);
बाह्य पूर्णांक iscsi_target_setup_login_socket(काष्ठा iscsi_np *,
				काष्ठा sockaddr_storage *);
बाह्य पूर्णांक iscsit_accept_np(काष्ठा iscsi_np *, काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_get_login_rx(काष्ठा iscsi_conn *, काष्ठा iscsi_login *);
बाह्य पूर्णांक iscsit_put_login_tx(काष्ठा iscsi_conn *, काष्ठा iscsi_login *, u32);
बाह्य व्योम iscsit_मुक्त_conn(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_start_kthपढ़ोs(काष्ठा iscsi_conn *);
बाह्य व्योम iscsi_post_login_handler(काष्ठा iscsi_np *, काष्ठा iscsi_conn *, u8);
बाह्य व्योम iscsi_target_login_sess_out(काष्ठा iscsi_conn *, bool, bool);
बाह्य पूर्णांक iscsi_target_login_thपढ़ो(व्योम *);
बाह्य व्योम iscsi_handle_login_thपढ़ो_समयout(काष्ठा समयr_list *t);

#पूर्ण_अगर   /*** ISCSI_TARGET_LOGIN_H ***/
