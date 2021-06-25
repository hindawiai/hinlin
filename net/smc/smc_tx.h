<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Manage send buffer
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#अगर_अघोषित SMC_TX_H
#घोषणा SMC_TX_H

#समावेश <linux/socket.h>
#समावेश <linux/types.h>

#समावेश "smc.h"
#समावेश "smc_cdc.h"

अटल अंतरभूत पूर्णांक smc_tx_prepared_sends(काष्ठा smc_connection *conn)
अणु
	जोड़ smc_host_cursor sent, prep;

	smc_curs_copy(&sent, &conn->tx_curs_sent, conn);
	smc_curs_copy(&prep, &conn->tx_curs_prep, conn);
	वापस smc_curs_dअगरf(conn->sndbuf_desc->len, &sent, &prep);
पूर्ण

व्योम smc_tx_work(काष्ठा work_काष्ठा *work);
व्योम smc_tx_init(काष्ठा smc_sock *smc);
पूर्णांक smc_tx_sendmsg(काष्ठा smc_sock *smc, काष्ठा msghdr *msg, माप_प्रकार len);
पूर्णांक smc_tx_sndbuf_nonempty(काष्ठा smc_connection *conn);
व्योम smc_tx_sndbuf_nonfull(काष्ठा smc_sock *smc);
व्योम smc_tx_consumer_update(काष्ठा smc_connection *conn, bool क्रमce);
पूर्णांक smcd_tx_ism_ग_लिखो(काष्ठा smc_connection *conn, व्योम *data, माप_प्रकार len,
		      u32 offset, पूर्णांक संकेत);

#पूर्ण_अगर /* SMC_TX_H */
