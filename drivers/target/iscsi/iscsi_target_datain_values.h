<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_DATAIN_VALUES_H
#घोषणा ISCSI_TARGET_DATAIN_VALUES_H

काष्ठा iscsi_cmd;
काष्ठा iscsi_datain;

बाह्य काष्ठा iscsi_datain_req *iscsit_allocate_datain_req(व्योम);
बाह्य व्योम iscsit_attach_datain_req(काष्ठा iscsi_cmd *, काष्ठा iscsi_datain_req *);
बाह्य व्योम iscsit_मुक्त_datain_req(काष्ठा iscsi_cmd *, काष्ठा iscsi_datain_req *);
बाह्य व्योम iscsit_मुक्त_all_datain_reqs(काष्ठा iscsi_cmd *);
बाह्य काष्ठा iscsi_datain_req *iscsit_get_datain_req(काष्ठा iscsi_cmd *);
बाह्य काष्ठा iscsi_datain_req *iscsit_get_datain_values(काष्ठा iscsi_cmd *,
			काष्ठा iscsi_datain *);

#पूर्ण_अगर   /*** ISCSI_TARGET_DATAIN_VALUES_H ***/
