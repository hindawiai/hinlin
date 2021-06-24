<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2019 Intel Corporation. All rights reserved.
 *
 * Author: Keyon Jie <yang.jie@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __SOF_INTEL_HDA_IPC_H
#घोषणा __SOF_INTEL_HDA_IPC_H

/*
 * Primary रेजिस्टर, mapped to
 * - DIPCTDR (HIPCIDR) in sideband IPC (cAVS 1.8+)
 * - DIPCT in cAVS 1.5 IPC
 *
 * Secondary रेजिस्टर, mapped to:
 * - DIPCTDD (HIPCIDD) in sideband IPC (cAVS 1.8+)
 * - DIPCTE in cAVS 1.5 IPC
 */

/* Common bits in primary रेजिस्टर */

/* Reserved क्रम करोorbell */
#घोषणा HDA_IPC_RSVD_31		BIT(31)
/* Target, 0 - normal message, 1 - compact message(cAVS compatible) */
#घोषणा HDA_IPC_MSG_COMPACT	BIT(30)
/* Direction, 0 - request, 1 - response */
#घोषणा HDA_IPC_RSP		BIT(29)

#घोषणा HDA_IPC_TYPE_SHIFT	24
#घोषणा HDA_IPC_TYPE_MASK	GENMASK(28, 24)
#घोषणा HDA_IPC_TYPE(x)		((x) << HDA_IPC_TYPE_SHIFT)

#घोषणा HDA_IPC_PM_GATE		HDA_IPC_TYPE(0x8U)

/* Command specअगरic payload bits in secondary रेजिस्टर */

/* Disable DMA tracing (0 - keep tracing, 1 - to disable DMA trace) */
#घोषणा HDA_PM_NO_DMA_TRACE	BIT(4)
/* Prevent घड़ी gating (0 - cg allowed, 1 - DSP घड़ी always on) */
#घोषणा HDA_PM_PCG		BIT(3)
/* Prevent घातer gating (0 - deep घातer state transitions allowed) */
#घोषणा HDA_PM_PPG		BIT(2)
/* Indicates whether streaming is active */
#घोषणा HDA_PM_PG_STREAMING	BIT(1)
#घोषणा HDA_PM_PG_RSVD		BIT(0)

irqवापस_t cnl_ipc_irq_thपढ़ो(पूर्णांक irq, व्योम *context);
पूर्णांक cnl_ipc_send_msg(काष्ठा snd_sof_dev *sdev, काष्ठा snd_sof_ipc_msg *msg);
व्योम cnl_ipc_dump(काष्ठा snd_sof_dev *sdev);

#पूर्ण_अगर
