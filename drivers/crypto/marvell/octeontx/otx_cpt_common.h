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

#अगर_अघोषित __OTX_CPT_COMMON_H
#घोषणा __OTX_CPT_COMMON_H

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>

#घोषणा OTX_CPT_MAX_MBOX_DATA_STR_SIZE 64

क्रमागत otx_cptpf_type अणु
	OTX_CPT_AE = 2,
	OTX_CPT_SE = 3,
	BAD_OTX_CPTPF_TYPE,
पूर्ण;

क्रमागत otx_cptvf_type अणु
	OTX_CPT_AE_TYPES = 1,
	OTX_CPT_SE_TYPES = 2,
	BAD_OTX_CPTVF_TYPE,
पूर्ण;

/* VF-PF message opcodes */
क्रमागत otx_cpt_mbox_opcode अणु
	OTX_CPT_MSG_VF_UP = 1,
	OTX_CPT_MSG_VF_DOWN,
	OTX_CPT_MSG_READY,
	OTX_CPT_MSG_QLEN,
	OTX_CPT_MSG_QBIND_GRP,
	OTX_CPT_MSG_VQ_PRIORITY,
	OTX_CPT_MSG_PF_TYPE,
	OTX_CPT_MSG_ACK,
	OTX_CPT_MSG_NACK
पूर्ण;

/* OcteonTX CPT mailbox काष्ठाure */
काष्ठा otx_cpt_mbox अणु
	u64 msg; /* Message type MBOX[0] */
	u64 data;/* Data         MBOX[1] */
पूर्ण;

#पूर्ण_अगर /* __OTX_CPT_COMMON_H */
