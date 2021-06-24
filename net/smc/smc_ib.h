<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Definitions क्रम IB environment
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Ursula Braun <Ursula Braun@linux.vnet.ibm.com>
 */

#अगर_अघोषित _SMC_IB_H
#घोषणा _SMC_IB_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <net/smc.h>

#घोषणा SMC_MAX_PORTS			2	/* Max # of ports */
#घोषणा SMC_GID_SIZE			माप(जोड़ ib_gid)

#घोषणा SMC_IB_MAX_SEND_SGE		2

काष्ठा smc_ib_devices अणु			/* list of smc ib devices definition */
	काष्ठा list_head	list;
	काष्ठा mutex		mutex;	/* protects list of smc ib devices */
पूर्ण;

बाह्य काष्ठा smc_ib_devices	smc_ib_devices; /* list of smc ib devices */
बाह्य काष्ठा smc_lgr_list smc_lgr_list; /* list of linkgroups */

काष्ठा smc_ib_device अणु				/* ib-device infos क्रम smc */
	काष्ठा list_head	list;
	काष्ठा ib_device	*ibdev;
	काष्ठा ib_port_attr	pattr[SMC_MAX_PORTS];	/* ib dev. port attrs */
	काष्ठा ib_event_handler	event_handler;	/* global ib_event handler */
	काष्ठा ib_cq		*roce_cq_send;	/* send completion queue */
	काष्ठा ib_cq		*roce_cq_recv;	/* recv completion queue */
	काष्ठा tasklet_काष्ठा	send_tasklet;	/* called by send cq handler */
	काष्ठा tasklet_काष्ठा	recv_tasklet;	/* called by recv cq handler */
	अक्षर			mac[SMC_MAX_PORTS][ETH_ALEN];
						/* mac address per port*/
	u8			pnetid[SMC_MAX_PORTS][SMC_MAX_PNETID_LEN];
						/* pnetid per port */
	bool			pnetid_by_user[SMC_MAX_PORTS];
						/* pnetid defined by user? */
	u8			initialized : 1; /* ib dev CQ, evthdl करोne */
	काष्ठा work_काष्ठा	port_event_work;
	अचिन्हित दीर्घ		port_event_mask;
	DECLARE_BITMAP(ports_going_away, SMC_MAX_PORTS);
	atomic_t		lnk_cnt;	/* number of links on ibdev */
	रुको_queue_head_t	lnks_deleted;	/* रुको 4 removal of all links*/
	काष्ठा mutex		mutex;		/* protect dev setup+cleanup */
	atomic_t		lnk_cnt_by_port[SMC_MAX_PORTS];
						/* number of links per port */
	पूर्णांक			ndev_अगरidx[SMC_MAX_PORTS]; /* ndev अगर indexes */
पूर्ण;

काष्ठा smc_buf_desc;
काष्ठा smc_link;

व्योम smc_ib_ndev_change(काष्ठा net_device *ndev, अचिन्हित दीर्घ event);
पूर्णांक smc_ib_रेजिस्टर_client(व्योम) __init;
व्योम smc_ib_unरेजिस्टर_client(व्योम);
bool smc_ib_port_active(काष्ठा smc_ib_device *smcibdev, u8 ibport);
पूर्णांक smc_ib_buf_map_sg(काष्ठा smc_link *lnk,
		      काष्ठा smc_buf_desc *buf_slot,
		      क्रमागत dma_data_direction data_direction);
व्योम smc_ib_buf_unmap_sg(काष्ठा smc_link *lnk,
			 काष्ठा smc_buf_desc *buf_slot,
			 क्रमागत dma_data_direction data_direction);
व्योम smc_ib_dealloc_protection_करोमुख्य(काष्ठा smc_link *lnk);
पूर्णांक smc_ib_create_protection_करोमुख्य(काष्ठा smc_link *lnk);
व्योम smc_ib_destroy_queue_pair(काष्ठा smc_link *lnk);
पूर्णांक smc_ib_create_queue_pair(काष्ठा smc_link *lnk);
पूर्णांक smc_ib_पढ़ोy_link(काष्ठा smc_link *lnk);
पूर्णांक smc_ib_modअगरy_qp_rts(काष्ठा smc_link *lnk);
पूर्णांक smc_ib_modअगरy_qp_reset(काष्ठा smc_link *lnk);
दीर्घ smc_ib_setup_per_ibdev(काष्ठा smc_ib_device *smcibdev);
पूर्णांक smc_ib_get_memory_region(काष्ठा ib_pd *pd, पूर्णांक access_flags,
			     काष्ठा smc_buf_desc *buf_slot, u8 link_idx);
व्योम smc_ib_put_memory_region(काष्ठा ib_mr *mr);
व्योम smc_ib_sync_sg_क्रम_cpu(काष्ठा smc_link *lnk,
			    काष्ठा smc_buf_desc *buf_slot,
			    क्रमागत dma_data_direction data_direction);
व्योम smc_ib_sync_sg_क्रम_device(काष्ठा smc_link *lnk,
			       काष्ठा smc_buf_desc *buf_slot,
			       क्रमागत dma_data_direction data_direction);
पूर्णांक smc_ib_determine_gid(काष्ठा smc_ib_device *smcibdev, u8 ibport,
			 अचिन्हित लघु vlan_id, u8 gid[], u8 *sgid_index);
bool smc_ib_is_valid_local_प्रणालीid(व्योम);
पूर्णांक smcr_nl_get_device(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
#पूर्ण_अगर
