<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Socket Closing
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#अगर_अघोषित SMC_CLOSE_H
#घोषणा SMC_CLOSE_H

#समावेश <linux/workqueue.h>

#समावेश "smc.h"

#घोषणा SMC_MAX_STREAM_WAIT_TIMEOUT		(2 * HZ)
#घोषणा SMC_CLOSE_SOCK_PUT_DELAY		HZ

व्योम smc_बंद_wake_tx_prepared(काष्ठा smc_sock *smc);
पूर्णांक smc_बंद_active(काष्ठा smc_sock *smc);
पूर्णांक smc_बंद_shutकरोwn_ग_लिखो(काष्ठा smc_sock *smc);
व्योम smc_बंद_init(काष्ठा smc_sock *smc);
व्योम smc_clcsock_release(काष्ठा smc_sock *smc);
पूर्णांक smc_बंद_पात(काष्ठा smc_connection *conn);
व्योम smc_बंद_active_पात(काष्ठा smc_sock *smc);

#पूर्ण_अगर /* SMC_CLOSE_H */
