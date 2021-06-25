<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RDMA_TRANSPORT_H
#घोषणा _RDMA_TRANSPORT_H

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>
#समावेश "rds.h"

/* RDMA_CM also uses 16385 as the listener port. */
#घोषणा RDS_CM_PORT	16385

#घोषणा RDS_RDMA_RESOLVE_TIMEOUT_MS     5000

/* Below reject reason is क्रम legacy पूर्णांकeroperability issue with non-linux
 * RDS endpoपूर्णांकs where older version incompatibility is conveyed via value 1.
 * For future version(s), proper encoded reject reason should be used.
 */
#घोषणा RDS_RDMA_REJ_INCOMPAT		1

पूर्णांक rds_rdma_conn_connect(काष्ठा rds_connection *conn);
पूर्णांक rds_rdma_cm_event_handler(काष्ठा rdma_cm_id *cm_id,
			      काष्ठा rdma_cm_event *event);
पूर्णांक rds6_rdma_cm_event_handler(काष्ठा rdma_cm_id *cm_id,
			       काष्ठा rdma_cm_event *event);

/* from ib.c */
बाह्य काष्ठा rds_transport rds_ib_transport;
पूर्णांक rds_ib_init(व्योम);
व्योम rds_ib_निकास(व्योम);

#पूर्ण_अगर
