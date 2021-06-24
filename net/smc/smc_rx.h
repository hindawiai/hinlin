<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Manage RMBE
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#अगर_अघोषित SMC_RX_H
#घोषणा SMC_RX_H

#समावेश <linux/socket.h>
#समावेश <linux/types.h>

#समावेश "smc.h"

व्योम smc_rx_init(काष्ठा smc_sock *smc);

पूर्णांक smc_rx_recvmsg(काष्ठा smc_sock *smc, काष्ठा msghdr *msg,
		   काष्ठा pipe_inode_info *pipe, माप_प्रकार len, पूर्णांक flags);
पूर्णांक smc_rx_रुको(काष्ठा smc_sock *smc, दीर्घ *समयo,
		पूर्णांक (*fcrit)(काष्ठा smc_connection *conn));
अटल अंतरभूत पूर्णांक smc_rx_data_available(काष्ठा smc_connection *conn)
अणु
	वापस atomic_पढ़ो(&conn->bytes_to_rcv);
पूर्ण

#पूर्ण_अगर /* SMC_RX_H */
