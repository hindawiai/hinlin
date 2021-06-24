<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_NEGO_H
#घोषणा ISCSI_TARGET_NEGO_H

#घोषणा DECIMAL         0
#घोषणा HEX             1

काष्ठा iscsi_conn;
काष्ठा iscsi_login;
काष्ठा iscsi_np;

बाह्य व्योम convert_null_to_semi(अक्षर *, पूर्णांक);
बाह्य पूर्णांक extract_param(स्थिर अक्षर *, स्थिर अक्षर *, अचिन्हित पूर्णांक, अक्षर *,
		अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsi_target_check_login_request(काष्ठा iscsi_conn *,
		काष्ठा iscsi_login *);
बाह्य पूर्णांक iscsi_target_get_initial_payload(काष्ठा iscsi_conn *,
		काष्ठा iscsi_login *);
बाह्य पूर्णांक iscsi_target_locate_portal(काष्ठा iscsi_np *, काष्ठा iscsi_conn *,
		काष्ठा iscsi_login *);
बाह्य पूर्णांक iscsi_target_start_negotiation(
		काष्ठा iscsi_login *, काष्ठा iscsi_conn *);
बाह्य व्योम iscsi_target_nego_release(काष्ठा iscsi_conn *);

#पूर्ण_अगर /* ISCSI_TARGET_NEGO_H */
