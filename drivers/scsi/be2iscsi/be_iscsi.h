<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2017 Broadcom. All Rights Reserved.
 * The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * Contact Inक्रमmation:
 * linux-drivers@broadcom.com
 */

#अगर_अघोषित _BE_ISCSI_
#घोषणा _BE_ISCSI_

#समावेश "be_main.h"
#समावेश "be_mgmt.h"

व्योम beiscsi_अगरace_create_शेष(काष्ठा beiscsi_hba *phba);

व्योम beiscsi_अगरace_destroy_शेष(काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_अगरace_get_param(काष्ठा iscsi_अगरace *अगरace,
			     क्रमागत iscsi_param_type param_type,
			     पूर्णांक param, अक्षर *buf);

पूर्णांक beiscsi_अगरace_set_param(काष्ठा Scsi_Host *shost,
			     व्योम *data, uपूर्णांक32_t count);

umode_t beiscsi_attr_is_visible(पूर्णांक param_type, पूर्णांक param);

व्योम beiscsi_offload_connection(काष्ठा beiscsi_conn *beiscsi_conn,
				काष्ठा beiscsi_offload_params *params);

व्योम beiscsi_offload_iscsi(काष्ठा beiscsi_hba *phba, काष्ठा iscsi_conn *conn,
			   काष्ठा beiscsi_conn *beiscsi_conn,
			   अचिन्हित पूर्णांक fw_handle);

काष्ठा iscsi_cls_session *beiscsi_session_create(काष्ठा iscsi_endpoपूर्णांक *ep,
						 uपूर्णांक16_t cmds_max,
						 uपूर्णांक16_t qdepth,
						 uपूर्णांक32_t initial_cmdsn);

व्योम beiscsi_session_destroy(काष्ठा iscsi_cls_session *cls_session);

व्योम beiscsi_session_fail(काष्ठा iscsi_cls_session *cls_session);

काष्ठा iscsi_cls_conn *beiscsi_conn_create(काष्ठा iscsi_cls_session
					   *cls_session, uपूर्णांक32_t cid);

पूर्णांक beiscsi_conn_bind(काष्ठा iscsi_cls_session *cls_session,
		      काष्ठा iscsi_cls_conn *cls_conn,
		      uपूर्णांक64_t transport_fd, पूर्णांक is_leading);

पूर्णांक beiscsi_ep_get_param(काष्ठा iscsi_endpoपूर्णांक *ep, क्रमागत iscsi_param param,
			 अक्षर *buf);

पूर्णांक beiscsi_get_host_param(काष्ठा Scsi_Host *shost,
			   क्रमागत iscsi_host_param param, अक्षर *buf);

पूर्णांक beiscsi_get_macaddr(अक्षर *buf, काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_set_param(काष्ठा iscsi_cls_conn *cls_conn,
		      क्रमागत iscsi_param param, अक्षर *buf, पूर्णांक buflen);

पूर्णांक beiscsi_conn_start(काष्ठा iscsi_cls_conn *cls_conn);

काष्ठा iscsi_endpoपूर्णांक *beiscsi_ep_connect(काष्ठा Scsi_Host *shost,
					  काष्ठा sockaddr *dst_addr,
					  पूर्णांक non_blocking);

पूर्णांक beiscsi_ep_poll(काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms);

व्योम beiscsi_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *ep);

व्योम beiscsi_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
			    काष्ठा iscsi_stats *stats);

#पूर्ण_अगर
