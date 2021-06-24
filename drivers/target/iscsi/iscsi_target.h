<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_H
#घोषणा ISCSI_TARGET_H

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>

काष्ठा iscsi_cmd;
काष्ठा iscsi_conn;
काष्ठा iscsi_np;
काष्ठा iscsi_portal_group;
काष्ठा iscsi_session;
काष्ठा iscsi_tpg_np;
काष्ठा kref;
काष्ठा sockaddr_storage;

बाह्य काष्ठा iscsi_tiqn *iscsit_get_tiqn_क्रम_login(अचिन्हित अक्षर *);
बाह्य काष्ठा iscsi_tiqn *iscsit_get_tiqn(अचिन्हित अक्षर *, पूर्णांक);
बाह्य व्योम iscsit_put_tiqn_क्रम_login(काष्ठा iscsi_tiqn *);
बाह्य काष्ठा iscsi_tiqn *iscsit_add_tiqn(अचिन्हित अक्षर *);
बाह्य व्योम iscsit_del_tiqn(काष्ठा iscsi_tiqn *);
बाह्य पूर्णांक iscsit_access_np(काष्ठा iscsi_np *, काष्ठा iscsi_portal_group *);
बाह्य व्योम iscsit_login_kref_put(काष्ठा kref *);
बाह्य पूर्णांक iscsit_deaccess_np(काष्ठा iscsi_np *, काष्ठा iscsi_portal_group *,
				काष्ठा iscsi_tpg_np *);
बाह्य bool iscsit_check_np_match(काष्ठा sockaddr_storage *,
				काष्ठा iscsi_np *, पूर्णांक);
बाह्य काष्ठा iscsi_np *iscsit_add_np(काष्ठा sockaddr_storage *,
				पूर्णांक);
बाह्य पूर्णांक iscsit_reset_np_thपढ़ो(काष्ठा iscsi_np *, काष्ठा iscsi_tpg_np *,
				काष्ठा iscsi_portal_group *, bool);
बाह्य पूर्णांक iscsit_del_np(काष्ठा iscsi_np *);
बाह्य पूर्णांक iscsit_reject_cmd(काष्ठा iscsi_cmd *cmd, u8, अचिन्हित अक्षर *);
बाह्य व्योम iscsit_set_unsolicited_dataout(काष्ठा iscsi_cmd *);
बाह्य पूर्णांक iscsit_logout_बंदsession(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_logout_बंदconnection(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_logout_हटाओconnक्रमrecovery(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_send_async_msg(काष्ठा iscsi_conn *, u16, u8, u8);
बाह्य पूर्णांक iscsit_build_r2ts_क्रम_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *, bool recovery);
बाह्य व्योम iscsit_thपढ़ो_get_cpumask(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsi_target_tx_thपढ़ो(व्योम *);
बाह्य पूर्णांक iscsi_target_rx_thपढ़ो(व्योम *);
बाह्य पूर्णांक iscsit_बंद_connection(काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_बंद_session(काष्ठा iscsi_session *, bool can_sleep);
बाह्य व्योम iscsit_fail_session(काष्ठा iscsi_session *);
बाह्य व्योम iscsit_stop_session(काष्ठा iscsi_session *, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक iscsit_release_sessions_क्रम_tpg(काष्ठा iscsi_portal_group *, पूर्णांक);

बाह्य काष्ठा iscsit_global *iscsit_global;
बाह्य स्थिर काष्ठा target_core_fabric_ops iscsi_ops;

बाह्य काष्ठा kmem_cache *lio_dr_cache;
बाह्य काष्ठा kmem_cache *lio_ooo_cache;
बाह्य काष्ठा kmem_cache *lio_qr_cache;
बाह्य काष्ठा kmem_cache *lio_r2t_cache;

बाह्य काष्ठा ida sess_ida;
बाह्य काष्ठा mutex auth_id_lock;

#पूर्ण_अगर   /*** ISCSI_TARGET_H ***/
