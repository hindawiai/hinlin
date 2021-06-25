<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित _QTN_FMAC_SHM_IPC_DEFS_H_
#घोषणा _QTN_FMAC_SHM_IPC_DEFS_H_

#समावेश <linux/types.h>

#घोषणा QTN_IPC_REG_HDR_SZ	(32)
#घोषणा QTN_IPC_REG_SZ		(4096)
#घोषणा QTN_IPC_MAX_DATA_SZ	(QTN_IPC_REG_SZ - QTN_IPC_REG_HDR_SZ)

क्रमागत qtnf_shm_ipc_region_flags अणु
	QTNF_SHM_IPC_NEW_DATA		= BIT(0),
	QTNF_SHM_IPC_ACK		= BIT(1),
पूर्ण;

काष्ठा qtnf_shm_ipc_region_header अणु
	__le32 flags;
	__le16 data_len;
पूर्ण __packed;

जोड़ qtnf_shm_ipc_region_headroom अणु
	काष्ठा qtnf_shm_ipc_region_header hdr;
	u8 headroom[QTN_IPC_REG_HDR_SZ];
पूर्ण __packed;

काष्ठा qtnf_shm_ipc_region अणु
	जोड़ qtnf_shm_ipc_region_headroom headroom;
	u8 data[QTN_IPC_MAX_DATA_SZ];
पूर्ण __packed;

#पूर्ण_अगर /* _QTN_FMAC_SHM_IPC_DEFS_H_ */
