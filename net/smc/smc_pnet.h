<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  PNET table queries
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Thomas Richter <पंचांगricht@linux.vnet.ibm.com>
 */

#अगर_अघोषित _SMC_PNET_H
#घोषणा _SMC_PNET_H

#समावेश <net/smc.h>

#अगर IS_ENABLED(CONFIG_HAVE_PNETID)
#समावेश <यंत्र/pnet.h>
#पूर्ण_अगर

काष्ठा smc_ib_device;
काष्ठा smcd_dev;
काष्ठा smc_init_info;
काष्ठा smc_link_group;

/**
 * काष्ठा smc_pnettable - SMC PNET table anchor
 * @lock: Lock क्रम list action
 * @pnetlist: List of PNETIDs
 */
काष्ठा smc_pnettable अणु
	rwlock_t lock;
	काष्ठा list_head pnetlist;
पूर्ण;

काष्ठा smc_pnetids_ndev अणु	/* list of pnetids क्रम net devices in UP state*/
	काष्ठा list_head	list;
	rwlock_t		lock;
पूर्ण;

काष्ठा smc_pnetids_ndev_entry अणु
	काष्ठा list_head	list;
	u8			pnetid[SMC_MAX_PNETID_LEN];
	refcount_t		refcnt;
पूर्ण;

अटल अंतरभूत पूर्णांक smc_pnetid_by_dev_port(काष्ठा device *dev,
					 अचिन्हित लघु port, u8 *pnetid)
अणु
#अगर IS_ENABLED(CONFIG_HAVE_PNETID)
	वापस pnet_id_by_dev_port(dev, port, pnetid);
#अन्यथा
	वापस -ENOENT;
#पूर्ण_अगर
पूर्ण

पूर्णांक smc_pnet_init(व्योम) __init;
पूर्णांक smc_pnet_net_init(काष्ठा net *net);
व्योम smc_pnet_निकास(व्योम);
व्योम smc_pnet_net_निकास(काष्ठा net *net);
व्योम smc_pnet_find_roce_resource(काष्ठा sock *sk, काष्ठा smc_init_info *ini);
व्योम smc_pnet_find_ism_resource(काष्ठा sock *sk, काष्ठा smc_init_info *ini);
पूर्णांक smc_pnetid_by_table_ib(काष्ठा smc_ib_device *smcibdev, u8 ib_port);
पूर्णांक smc_pnetid_by_table_smcd(काष्ठा smcd_dev *smcd);
व्योम smc_pnet_find_alt_roce(काष्ठा smc_link_group *lgr,
			    काष्ठा smc_init_info *ini,
			    काष्ठा smc_ib_device *known_dev);
bool smc_pnet_is_ndev_pnetid(काष्ठा net *net, u8 *pnetid);
bool smc_pnet_is_pnetid_set(u8 *pnetid);
#पूर्ण_अगर
