<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_NODEATTRIB_H
#घोषणा ISCSI_TARGET_NODEATTRIB_H

#समावेश <linux/types.h>

काष्ठा iscsi_node_acl;
काष्ठा iscsi_portal_group;

बाह्य व्योम iscsit_set_शेष_node_attribues(काष्ठा iscsi_node_acl *,
					      काष्ठा iscsi_portal_group *);
बाह्य पूर्णांक iscsit_na_dataout_समयout(काष्ठा iscsi_node_acl *, u32);
बाह्य पूर्णांक iscsit_na_dataout_समयout_retries(काष्ठा iscsi_node_acl *, u32);
बाह्य पूर्णांक iscsit_na_nopin_समयout(काष्ठा iscsi_node_acl *, u32);
बाह्य पूर्णांक iscsit_na_nopin_response_समयout(काष्ठा iscsi_node_acl *, u32);
बाह्य पूर्णांक iscsit_na_अक्रमom_datain_pdu_offsets(काष्ठा iscsi_node_acl *, u32);
बाह्य पूर्णांक iscsit_na_अक्रमom_datain_seq_offsets(काष्ठा iscsi_node_acl *, u32);
बाह्य पूर्णांक iscsit_na_अक्रमom_r2t_offsets(काष्ठा iscsi_node_acl *, u32);
बाह्य पूर्णांक iscsit_na_शेष_erl(काष्ठा iscsi_node_acl *, u32);

#पूर्ण_अगर /* ISCSI_TARGET_NODEATTRIB_H */
