<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_TMR_H
#घोषणा ISCSI_TARGET_TMR_H

#समावेश <linux/types.h>

काष्ठा iscsi_cmd;
काष्ठा iscsi_conn;
काष्ठा iscsi_पंचांगr_req;

बाह्य u8 iscsit_पंचांगr_पात_task(काष्ठा iscsi_cmd *, अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsit_पंचांगr_task_warm_reset(काष्ठा iscsi_conn *, काष्ठा iscsi_पंचांगr_req *,
			अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsit_पंचांगr_task_cold_reset(काष्ठा iscsi_conn *, काष्ठा iscsi_पंचांगr_req *,
			अचिन्हित अक्षर *);
बाह्य u8 iscsit_पंचांगr_task_reassign(काष्ठा iscsi_cmd *, अचिन्हित अक्षर *);
बाह्य पूर्णांक iscsit_पंचांगr_post_handler(काष्ठा iscsi_cmd *, काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsit_check_task_reassign_expdatasn(काष्ठा iscsi_पंचांगr_req *,
			काष्ठा iscsi_conn *);

#पूर्ण_अगर /* ISCSI_TARGET_TMR_H */
