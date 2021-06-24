<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Work Requests exploiting Infiniband API
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Steffen Maier <maier@linux.vnet.ibm.com>
 */

#अगर_अघोषित SMC_WR_H
#घोषणा SMC_WR_H

#समावेश <linux/atomic.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "smc.h"
#समावेश "smc_core.h"

#घोषणा SMC_WR_BUF_CNT 16	/* # of ctrl buffers per link */

#घोषणा SMC_WR_TX_WAIT_FREE_SLOT_TIME	(10 * HZ)
#घोषणा SMC_WR_TX_WAIT_PENDING_TIME	(5 * HZ)

#घोषणा SMC_WR_TX_SIZE 44 /* actual size of wr_send data (<=SMC_WR_BUF_SIZE) */

#घोषणा SMC_WR_TX_PEND_PRIV_SIZE 32

काष्ठा smc_wr_tx_pend_priv अणु
	u8			priv[SMC_WR_TX_PEND_PRIV_SIZE];
पूर्ण;

प्रकार व्योम (*smc_wr_tx_handler)(काष्ठा smc_wr_tx_pend_priv *,
				  काष्ठा smc_link *,
				  क्रमागत ib_wc_status);

प्रकार bool (*smc_wr_tx_filter)(काष्ठा smc_wr_tx_pend_priv *,
				 अचिन्हित दीर्घ);

प्रकार व्योम (*smc_wr_tx_dismisser)(काष्ठा smc_wr_tx_pend_priv *);

काष्ठा smc_wr_rx_handler अणु
	काष्ठा hlist_node	list;	/* hash table collision resolution */
	व्योम			(*handler)(काष्ठा ib_wc *, व्योम *);
	u8			type;
पूर्ण;

/* Only used by RDMA ग_लिखो WRs.
 * All other WRs (CDC/LLC) use smc_wr_tx_send handling WR_ID implicitly
 */
अटल अंतरभूत दीर्घ smc_wr_tx_get_next_wr_id(काष्ठा smc_link *link)
अणु
	वापस atomic_दीर्घ_inc_वापस(&link->wr_tx_id);
पूर्ण

अटल अंतरभूत व्योम smc_wr_tx_set_wr_id(atomic_दीर्घ_t *wr_tx_id, दीर्घ val)
अणु
	atomic_दीर्घ_set(wr_tx_id, val);
पूर्ण

अटल अंतरभूत व्योम smc_wr_wakeup_tx_रुको(काष्ठा smc_link *lnk)
अणु
	wake_up_all(&lnk->wr_tx_रुको);
पूर्ण

अटल अंतरभूत व्योम smc_wr_wakeup_reg_रुको(काष्ठा smc_link *lnk)
अणु
	wake_up(&lnk->wr_reg_रुको);
पूर्ण

/* post a new receive work request to fill a completed old work request entry */
अटल अंतरभूत पूर्णांक smc_wr_rx_post(काष्ठा smc_link *link)
अणु
	पूर्णांक rc;
	u64 wr_id, temp_wr_id;
	u32 index;

	wr_id = ++link->wr_rx_id; /* tasklet context, thus not atomic */
	temp_wr_id = wr_id;
	index = करो_भाग(temp_wr_id, link->wr_rx_cnt);
	link->wr_rx_ibs[index].wr_id = wr_id;
	rc = ib_post_recv(link->roce_qp, &link->wr_rx_ibs[index], शून्य);
	वापस rc;
पूर्ण

पूर्णांक smc_wr_create_link(काष्ठा smc_link *lnk);
पूर्णांक smc_wr_alloc_link_mem(काष्ठा smc_link *lnk);
व्योम smc_wr_मुक्त_link(काष्ठा smc_link *lnk);
व्योम smc_wr_मुक्त_link_mem(काष्ठा smc_link *lnk);
व्योम smc_wr_remember_qp_attr(काष्ठा smc_link *lnk);
व्योम smc_wr_हटाओ_dev(काष्ठा smc_ib_device *smcibdev);
व्योम smc_wr_add_dev(काष्ठा smc_ib_device *smcibdev);

पूर्णांक smc_wr_tx_get_मुक्त_slot(काष्ठा smc_link *link, smc_wr_tx_handler handler,
			    काष्ठा smc_wr_buf **wr_buf,
			    काष्ठा smc_rdma_wr **wrs,
			    काष्ठा smc_wr_tx_pend_priv **wr_pend_priv);
पूर्णांक smc_wr_tx_put_slot(काष्ठा smc_link *link,
		       काष्ठा smc_wr_tx_pend_priv *wr_pend_priv);
पूर्णांक smc_wr_tx_send(काष्ठा smc_link *link,
		   काष्ठा smc_wr_tx_pend_priv *wr_pend_priv);
पूर्णांक smc_wr_tx_send_रुको(काष्ठा smc_link *link, काष्ठा smc_wr_tx_pend_priv *priv,
			अचिन्हित दीर्घ समयout);
व्योम smc_wr_tx_cq_handler(काष्ठा ib_cq *ib_cq, व्योम *cq_context);
व्योम smc_wr_tx_dismiss_slots(काष्ठा smc_link *lnk, u8 wr_rx_hdr_type,
			     smc_wr_tx_filter filter,
			     smc_wr_tx_dismisser dismisser,
			     अचिन्हित दीर्घ data);
पूर्णांक smc_wr_tx_रुको_no_pending_sends(काष्ठा smc_link *link);

पूर्णांक smc_wr_rx_रेजिस्टर_handler(काष्ठा smc_wr_rx_handler *handler);
पूर्णांक smc_wr_rx_post_init(काष्ठा smc_link *link);
व्योम smc_wr_rx_cq_handler(काष्ठा ib_cq *ib_cq, व्योम *cq_context);
पूर्णांक smc_wr_reg_send(काष्ठा smc_link *link, काष्ठा ib_mr *mr);

#पूर्ण_अगर /* SMC_WR_H */
