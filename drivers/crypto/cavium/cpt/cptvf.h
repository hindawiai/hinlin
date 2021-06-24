<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#अगर_अघोषित __CPTVF_H
#घोषणा __CPTVF_H

#समावेश <linux/list.h>
#समावेश "cpt_common.h"

/* Default command queue length */
#घोषणा CPT_CMD_QLEN 2046
#घोषणा CPT_CMD_QCHUNK_SIZE 1023

/* Default command समयout in seconds */
#घोषणा CPT_COMMAND_TIMEOUT 4
#घोषणा CPT_TIMER_THOLD	0xFFFF
#घोषणा CPT_NUM_QS_PER_VF 1
#घोषणा CPT_INST_SIZE 64
#घोषणा CPT_NEXT_CHUNK_PTR_SIZE 8

#घोषणा	CPT_VF_MSIX_VECTORS 2
#घोषणा CPT_VF_INTR_MBOX_MASK BIT(0)
#घोषणा CPT_VF_INTR_DOVF_MASK BIT(1)
#घोषणा CPT_VF_INTR_IRDE_MASK BIT(2)
#घोषणा CPT_VF_INTR_NWRP_MASK BIT(3)
#घोषणा CPT_VF_INTR_SERR_MASK BIT(4)
#घोषणा DMA_सूचीECT_सूचीECT 0 /* Input सूचीECT, Output सूचीECT */
#घोषणा DMA_GATHER_SCATTER 1
#घोषणा FROM_DPTR 1

/**
 * Enumeration cpt_vf_पूर्णांक_vec_e
 *
 * CPT VF MSI-X Vector Enumeration
 * Enumerates the MSI-X पूर्णांकerrupt vectors.
 */
क्रमागत cpt_vf_पूर्णांक_vec_e अणु
	CPT_VF_INT_VEC_E_MISC = 0x00,
	CPT_VF_INT_VEC_E_DONE = 0x01
पूर्ण;

काष्ठा command_chunk अणु
	u8 *head;
	dma_addr_t dma_addr;
	u32 size; /* Chunk size, max CPT_INST_CHUNK_MAX_SIZE */
	काष्ठा hlist_node nextchunk;
पूर्ण;

काष्ठा command_queue अणु
	spinlock_t lock; /* command queue lock */
	u32 idx; /* Command queue host ग_लिखो idx */
	u32 nchunks; /* Number of command chunks */
	काष्ठा command_chunk *qhead;	/* Command queue head, inकाष्ठाions
					 * are inserted here
					 */
	काष्ठा hlist_head chead;
पूर्ण;

काष्ठा command_qinfo अणु
	u32 cmd_size;
	u32 qchunksize; /* Command queue chunk size */
	काष्ठा command_queue queue[CPT_NUM_QS_PER_VF];
पूर्ण;

काष्ठा pending_entry अणु
	u8 busy; /* Entry status (मुक्त/busy) */

	अस्थिर u64 *completion_addr; /* Completion address */
	व्योम *post_arg;
	व्योम (*callback)(पूर्णांक, व्योम *); /* Kernel ASYNC request callabck */
	व्योम *callback_arg; /* Kernel ASYNC request callabck arg */
पूर्ण;

काष्ठा pending_queue अणु
	काष्ठा pending_entry *head;	/* head of the queue */
	u32 front; /* Process work from here */
	u32 rear; /* Append new work here */
	atomic64_t pending_count;
	spinlock_t lock; /* Queue lock */
पूर्ण;

काष्ठा pending_qinfo अणु
	u32 nr_queues;	/* Number of queues supported */
	u32 qlen; /* Queue length */
	काष्ठा pending_queue queue[CPT_NUM_QS_PER_VF];
पूर्ण;

#घोषणा क्रम_each_pending_queue(qinfo, q, i)	\
	क्रम (i = 0, q = &qinfo->queue[i]; i < qinfo->nr_queues; i++, \
	     q = &qinfo->queue[i])

काष्ठा cpt_vf अणु
	u16 flags; /* Flags to hold device status bits */
	u8 vfid; /* Device Index 0...CPT_MAX_VF_NUM */
	u8 vftype; /* VF type of SE_TYPE(1) or AE_TYPE(1) */
	u8 vfgrp; /* VF group (0 - 8) */
	u8 node; /* Operating node: Bits (46:44) in BAR0 address */
	u8 priority; /* VF priority ring: 1-High proirity round
		      * robin ring;0-Low priority round robin ring;
		      */
	काष्ठा pci_dev *pdev; /* pci device handle */
	व्योम __iomem *reg_base; /* Register start address */
	व्योम *wqe_info;	/* BH worker info */
	/* MSI-X */
	cpumask_var_t affinity_mask[CPT_VF_MSIX_VECTORS];
	/* Command and Pending queues */
	u32 qsize;
	u32 nr_queues;
	काष्ठा command_qinfo cqinfo; /* Command queue inक्रमmation */
	काष्ठा pending_qinfo pqinfo; /* Pending queue inक्रमmation */
	/* VF-PF mailbox communication */
	bool pf_acked;
	bool pf_nacked;
पूर्ण;

पूर्णांक cptvf_send_vf_up(काष्ठा cpt_vf *cptvf);
पूर्णांक cptvf_send_vf_करोwn(काष्ठा cpt_vf *cptvf);
पूर्णांक cptvf_send_vf_to_grp_msg(काष्ठा cpt_vf *cptvf);
पूर्णांक cptvf_send_vf_priority_msg(काष्ठा cpt_vf *cptvf);
पूर्णांक cptvf_send_vq_size_msg(काष्ठा cpt_vf *cptvf);
पूर्णांक cptvf_check_pf_पढ़ोy(काष्ठा cpt_vf *cptvf);
व्योम cptvf_handle_mbox_पूर्णांकr(काष्ठा cpt_vf *cptvf);
व्योम cvm_crypto_निकास(व्योम);
पूर्णांक cvm_crypto_init(काष्ठा cpt_vf *cptvf);
व्योम vq_post_process(काष्ठा cpt_vf *cptvf, u32 qno);
व्योम cptvf_ग_लिखो_vq_करोorbell(काष्ठा cpt_vf *cptvf, u32 val);
#पूर्ण_अगर /* __CPTVF_H */
