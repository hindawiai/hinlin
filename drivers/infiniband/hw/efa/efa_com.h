<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause */
/*
 * Copyright 2018-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित _EFA_COM_H_
#घोषणा _EFA_COM_H_

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/sched.h>

#समावेश <rdma/ib_verbs.h>

#समावेश "efa_common_defs.h"
#समावेश "efa_admin_defs.h"
#समावेश "efa_admin_cmds_defs.h"
#समावेश "efa_regs_defs.h"

#घोषणा EFA_MAX_HANDLERS 256

काष्ठा efa_com_admin_cq अणु
	काष्ठा efa_admin_acq_entry *entries;
	dma_addr_t dma_addr;
	spinlock_t lock; /* Protects ACQ */

	u16 cc; /* consumer counter */
	u8 phase;
पूर्ण;

काष्ठा efa_com_admin_sq अणु
	काष्ठा efa_admin_aq_entry *entries;
	dma_addr_t dma_addr;
	spinlock_t lock; /* Protects ASQ */

	u32 __iomem *db_addr;

	u16 cc; /* consumer counter */
	u16 pc; /* producer counter */
	u8 phase;

पूर्ण;

/* Don't use anything other than atomic64 */
काष्ठा efa_com_stats_admin अणु
	atomic64_t submitted_cmd;
	atomic64_t completed_cmd;
	atomic64_t cmd_err;
	atomic64_t no_completion;
पूर्ण;

क्रमागत अणु
	EFA_AQ_STATE_RUNNING_BIT = 0,
	EFA_AQ_STATE_POLLING_BIT = 1,
पूर्ण;

काष्ठा efa_com_admin_queue अणु
	व्योम *dmadev;
	व्योम *efa_dev;
	काष्ठा efa_comp_ctx *comp_ctx;
	u32 completion_समयout; /* usecs */
	u16 poll_पूर्णांकerval; /* msecs */
	u16 depth;
	काष्ठा efa_com_admin_cq cq;
	काष्ठा efa_com_admin_sq sq;
	u16 msix_vector_idx;

	अचिन्हित दीर्घ state;

	/* Count the number of available admin commands */
	काष्ठा semaphore avail_cmds;

	काष्ठा efa_com_stats_admin stats;

	spinlock_t comp_ctx_lock; /* Protects completion context pool */
	u32 *comp_ctx_pool;
	u16 comp_ctx_pool_next;
पूर्ण;

काष्ठा efa_aenq_handlers;

काष्ठा efa_com_aenq अणु
	काष्ठा efa_admin_aenq_entry *entries;
	काष्ठा efa_aenq_handlers *aenq_handlers;
	dma_addr_t dma_addr;
	u32 cc; /* consumer counter */
	u16 msix_vector_idx;
	u16 depth;
	u8 phase;
पूर्ण;

काष्ठा efa_com_mmio_पढ़ो अणु
	काष्ठा efa_admin_mmio_req_पढ़ो_less_resp *पढ़ो_resp;
	dma_addr_t पढ़ो_resp_dma_addr;
	u16 seq_num;
	u16 mmio_पढ़ो_समयout; /* usecs */
	/* serializes mmio पढ़ोs */
	spinlock_t lock;
पूर्ण;

काष्ठा efa_com_dev अणु
	काष्ठा efa_com_admin_queue aq;
	काष्ठा efa_com_aenq aenq;
	u8 __iomem *reg_bar;
	व्योम *dmadev;
	व्योम *efa_dev;
	u32 supported_features;
	u32 dma_addr_bits;

	काष्ठा efa_com_mmio_पढ़ो mmio_पढ़ो;
पूर्ण;

प्रकार व्योम (*efa_aenq_handler)(व्योम *data,
	      काष्ठा efa_admin_aenq_entry *aenq_e);

/* Holds aenq handlers. Indexed by AENQ event group */
काष्ठा efa_aenq_handlers अणु
	efa_aenq_handler handlers[EFA_MAX_HANDLERS];
	efa_aenq_handler unimplemented_handler;
पूर्ण;

पूर्णांक efa_com_admin_init(काष्ठा efa_com_dev *edev,
		       काष्ठा efa_aenq_handlers *aenq_handlers);
व्योम efa_com_admin_destroy(काष्ठा efa_com_dev *edev);
पूर्णांक efa_com_dev_reset(काष्ठा efa_com_dev *edev,
		      क्रमागत efa_regs_reset_reason_types reset_reason);
व्योम efa_com_set_admin_polling_mode(काष्ठा efa_com_dev *edev, bool polling);
व्योम efa_com_admin_q_comp_पूर्णांकr_handler(काष्ठा efa_com_dev *edev);
पूर्णांक efa_com_mmio_reg_पढ़ो_init(काष्ठा efa_com_dev *edev);
व्योम efa_com_mmio_reg_पढ़ो_destroy(काष्ठा efa_com_dev *edev);

पूर्णांक efa_com_validate_version(काष्ठा efa_com_dev *edev);
पूर्णांक efa_com_get_dma_width(काष्ठा efa_com_dev *edev);

पूर्णांक efa_com_cmd_exec(काष्ठा efa_com_admin_queue *aq,
		     काष्ठा efa_admin_aq_entry *cmd,
		     माप_प्रकार cmd_size,
		     काष्ठा efa_admin_acq_entry *comp,
		     माप_प्रकार comp_size);
व्योम efa_com_aenq_पूर्णांकr_handler(काष्ठा efa_com_dev *edev, व्योम *data);

#पूर्ण_अगर /* _EFA_COM_H_ */
