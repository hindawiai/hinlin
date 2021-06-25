<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_TPG_H
#घोषणा ISCSI_TARGET_TPG_H

#समावेश <linux/types.h>

काष्ठा iscsi_np;
काष्ठा iscsi_session;
काष्ठा iscsi_tiqn;
काष्ठा iscsi_tpg_np;
काष्ठा se_node_acl;
काष्ठा sockaddr_storage;

बाह्य काष्ठा iscsi_portal_group *iscsit_alloc_portal_group(काष्ठा iscsi_tiqn *, u16);
बाह्य पूर्णांक iscsit_load_discovery_tpg(व्योम);
बाह्य व्योम iscsit_release_discovery_tpg(व्योम);
बाह्य काष्ठा iscsi_portal_group *iscsit_get_tpg_from_np(काष्ठा iscsi_tiqn *,
			काष्ठा iscsi_np *, काष्ठा iscsi_tpg_np **);
बाह्य पूर्णांक iscsit_get_tpg(काष्ठा iscsi_portal_group *);
बाह्य व्योम iscsit_put_tpg(काष्ठा iscsi_portal_group *);
बाह्य व्योम iscsit_tpg_dump_params(काष्ठा iscsi_portal_group *);
बाह्य पूर्णांक iscsit_tpg_add_portal_group(काष्ठा iscsi_tiqn *, काष्ठा iscsi_portal_group *);
बाह्य पूर्णांक iscsit_tpg_del_portal_group(काष्ठा iscsi_tiqn *, काष्ठा iscsi_portal_group *,
			पूर्णांक);
बाह्य पूर्णांक iscsit_tpg_enable_portal_group(काष्ठा iscsi_portal_group *);
बाह्य पूर्णांक iscsit_tpg_disable_portal_group(काष्ठा iscsi_portal_group *, पूर्णांक);
बाह्य काष्ठा iscsi_node_acl *iscsit_tpg_add_initiator_node_acl(
			काष्ठा iscsi_portal_group *, स्थिर अक्षर *, u32);
बाह्य व्योम iscsit_tpg_del_initiator_node_acl(काष्ठा iscsi_portal_group *,
			काष्ठा se_node_acl *);
बाह्य काष्ठा iscsi_node_attrib *iscsit_tpg_get_node_attrib(काष्ठा iscsi_session *);
बाह्य व्योम iscsit_tpg_del_बाह्यal_nps(काष्ठा iscsi_tpg_np *);
बाह्य काष्ठा iscsi_tpg_np *iscsit_tpg_locate_child_np(काष्ठा iscsi_tpg_np *, पूर्णांक);
बाह्य काष्ठा iscsi_tpg_np *iscsit_tpg_add_network_portal(काष्ठा iscsi_portal_group *,
			काष्ठा sockaddr_storage *, काष्ठा iscsi_tpg_np *,
			पूर्णांक);
बाह्य पूर्णांक iscsit_tpg_del_network_portal(काष्ठा iscsi_portal_group *,
			काष्ठा iscsi_tpg_np *);
बाह्य पूर्णांक iscsit_ta_authentication(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_login_समयout(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_netअगर_समयout(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_generate_node_acls(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_शेष_cmdsn_depth(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_cache_dynamic_acls(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_demo_mode_ग_लिखो_protect(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_prod_mode_ग_लिखो_protect(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_demo_mode_discovery(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_शेष_erl(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_t10_pi(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_fabric_prot_type(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_tpg_enabled_sendtarमाला_लो(काष्ठा iscsi_portal_group *, u32);
बाह्य पूर्णांक iscsit_ta_login_keys_workaround(काष्ठा iscsi_portal_group *, u32);

#पूर्ण_अगर /* ISCSI_TARGET_TPG_H */
