<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  SMC Generic netlink operations
 *
 *  Copyright IBM Corp. 2020
 *
 *  Author(s):	Guvenc Gulce <guvenc@linux.ibm.com>
 */

#अगर_अघोषित _SMC_NETLINK_H
#घोषणा _SMC_NETLINK_H

#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>

बाह्य काष्ठा genl_family smc_gen_nl_family;

काष्ठा smc_nl_dmp_ctx अणु
	पूर्णांक pos[2];
पूर्ण;

अटल अंतरभूत काष्ठा smc_nl_dmp_ctx *smc_nl_dmp_ctx(काष्ठा netlink_callback *c)
अणु
	वापस (काष्ठा smc_nl_dmp_ctx *)c->ctx;
पूर्ण

पूर्णांक smc_nl_init(व्योम) __init;
व्योम smc_nl_निकास(व्योम);

#पूर्ण_अगर
