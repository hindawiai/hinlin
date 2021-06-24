<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __OTX_CPTVF_H
#घोषणा __OTX_CPTVF_H

#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश "otx_cpt_common.h"
#समावेश "otx_cptvf_reqmgr.h"

/* Flags to indicate the features supported */
#घोषणा OTX_CPT_FLAG_DEVICE_READY  BIT(1)
#घोषणा otx_cpt_device_पढ़ोy(cpt)  ((cpt)->flags & OTX_CPT_FLAG_DEVICE_READY)
/* Default command queue length */
#घोषणा OTX_CPT_CMD_QLEN	(4*2046)
#घोषणा OTX_CPT_CMD_QCHUNK_SIZE	1023
#घोषणा OTX_CPT_NUM_QS_PER_VF	1

काष्ठा otx_cpt_cmd_chunk अणु
	u8 *head;
	dma_addr_t dma_addr;
	u32 size; /* Chunk size, max OTX_CPT_INST_CHUNK_MAX_SIZE */
	काष्ठा list_head nextchunk;
पूर्ण;

काष्ठा otx_cpt_cmd_queue अणु
	u32 idx;	/* Command queue host ग_लिखो idx */
	u32 num_chunks;	/* Number of command chunks */
	काष्ठा otx_cpt_cmd_chunk *qhead;/*
					 * Command queue head, inकाष्ठाions
					 * are inserted here
					 */
	काष्ठा otx_cpt_cmd_chunk *base;
	काष्ठा list_head chead;
पूर्ण;

काष्ठा otx_cpt_cmd_qinfo अणु
	u32 qchunksize; /* Command queue chunk size */
	काष्ठा otx_cpt_cmd_queue queue[OTX_CPT_NUM_QS_PER_VF];
पूर्ण;

काष्ठा otx_cpt_pending_qinfo अणु
	u32 num_queues;	/* Number of queues supported */
	काष्ठा otx_cpt_pending_queue queue[OTX_CPT_NUM_QS_PER_VF];
पूर्ण;

#घोषणा क्रम_each_pending_queue(qinfo, q, i)	\
		क्रम (i = 0, q = &qinfo->queue[i]; i < qinfo->num_queues; i++, \
		     q = &qinfo->queue[i])

काष्ठा otx_cptvf_wqe अणु
	काष्ठा tasklet_काष्ठा twork;
	काष्ठा otx_cptvf *cptvf;
पूर्ण;

काष्ठा otx_cptvf_wqe_info अणु
	काष्ठा otx_cptvf_wqe vq_wqe[OTX_CPT_NUM_QS_PER_VF];
पूर्ण;

काष्ठा otx_cptvf अणु
	u16 flags;	/* Flags to hold device status bits */
	u8 vfid;	/* Device Index 0...OTX_CPT_MAX_VF_NUM */
	u8 num_vfs;	/* Number of enabled VFs */
	u8 vftype;	/* VF type of SE_TYPE(2) or AE_TYPE(1) */
	u8 vfgrp;	/* VF group (0 - 8) */
	u8 node;	/* Operating node: Bits (46:44) in BAR0 address */
	u8 priority;	/*
			 * VF priority ring: 1-High proirity round
			 * robin ring;0-Low priority round robin ring;
			 */
	काष्ठा pci_dev *pdev;	/* Pci device handle */
	व्योम __iomem *reg_base;	/* Register start address */
	व्योम *wqe_info;		/* BH worker info */
	/* MSI-X */
	cpumask_var_t affinity_mask[OTX_CPT_VF_MSIX_VECTORS];
	/* Command and Pending queues */
	u32 qsize;
	u32 num_queues;
	काष्ठा otx_cpt_cmd_qinfo cqinfo; /* Command queue inक्रमmation */
	काष्ठा otx_cpt_pending_qinfo pqinfo; /* Pending queue inक्रमmation */
	/* VF-PF mailbox communication */
	bool pf_acked;
	bool pf_nacked;
पूर्ण;

पूर्णांक otx_cptvf_send_vf_up(काष्ठा otx_cptvf *cptvf);
पूर्णांक otx_cptvf_send_vf_करोwn(काष्ठा otx_cptvf *cptvf);
पूर्णांक otx_cptvf_send_vf_to_grp_msg(काष्ठा otx_cptvf *cptvf, पूर्णांक group);
पूर्णांक otx_cptvf_send_vf_priority_msg(काष्ठा otx_cptvf *cptvf);
पूर्णांक otx_cptvf_send_vq_size_msg(काष्ठा otx_cptvf *cptvf);
पूर्णांक otx_cptvf_check_pf_पढ़ोy(काष्ठा otx_cptvf *cptvf);
व्योम otx_cptvf_handle_mbox_पूर्णांकr(काष्ठा otx_cptvf *cptvf);
व्योम otx_cptvf_ग_लिखो_vq_करोorbell(काष्ठा otx_cptvf *cptvf, u32 val);

#पूर्ण_अगर /* __OTX_CPTVF_H */
