<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 HiSilicon Limited. */
#अगर_अघोषित __HISI_HPRE_H
#घोषणा __HISI_HPRE_H

#समावेश <linux/list.h>
#समावेश "../qm.h"

#घोषणा HPRE_SQE_SIZE			माप(काष्ठा hpre_sqe)
#घोषणा HPRE_PF_DEF_Q_NUM		64
#घोषणा HPRE_PF_DEF_Q_BASE		0

/*
 * type used in qm sqc DW6.
 * 0 - Algorithm which has been supported in V2, like RSA, DH and so on;
 * 1 - ECC algorithm in V3.
 */
#घोषणा HPRE_V2_ALG_TYPE	0
#घोषणा HPRE_V3_ECC_ALG_TYPE	1

क्रमागत अणु
	HPRE_CLUSTER0,
	HPRE_CLUSTER1,
	HPRE_CLUSTER2,
	HPRE_CLUSTER3
पूर्ण;

क्रमागत hpre_ctrl_dbgfs_file अणु
	HPRE_CLEAR_ENABLE,
	HPRE_CLUSTER_CTRL,
	HPRE_DEBUG_खाता_NUM,
पूर्ण;

क्रमागत hpre_dfx_dbgfs_file अणु
	HPRE_SEND_CNT,
	HPRE_RECV_CNT,
	HPRE_SEND_FAIL_CNT,
	HPRE_SEND_BUSY_CNT,
	HPRE_OVER_THRHLD_CNT,
	HPRE_OVERTIME_THRHLD,
	HPRE_INVALID_REQ_CNT,
	HPRE_DFX_खाता_NUM
पूर्ण;

#घोषणा HPRE_CLUSTERS_NUM_V2		(HPRE_CLUSTER3 + 1)
#घोषणा HPRE_CLUSTERS_NUM_V3		1
#घोषणा HPRE_CLUSTERS_NUM_MAX		HPRE_CLUSTERS_NUM_V2
#घोषणा HPRE_DEBUGFS_खाता_NUM (HPRE_DEBUG_खाता_NUM + HPRE_CLUSTERS_NUM_MAX - 1)

काष्ठा hpre_debugfs_file अणु
	पूर्णांक index;
	क्रमागत hpre_ctrl_dbgfs_file type;
	spinlock_t lock;
	काष्ठा hpre_debug *debug;
पूर्ण;

काष्ठा hpre_dfx अणु
	atomic64_t value;
	क्रमागत hpre_dfx_dbgfs_file type;
पूर्ण;

/*
 * One HPRE controller has one PF and multiple VFs, some global configurations
 * which PF has need this काष्ठाure.
 * Just relevant क्रम PF.
 */
काष्ठा hpre_debug अणु
	काष्ठा hpre_dfx dfx[HPRE_DFX_खाता_NUM];
	काष्ठा hpre_debugfs_file files[HPRE_DEBUGFS_खाता_NUM];
पूर्ण;

काष्ठा hpre अणु
	काष्ठा hisi_qm qm;
	काष्ठा hpre_debug debug;
	अचिन्हित दीर्घ status;
पूर्ण;

क्रमागत hpre_alg_type अणु
	HPRE_ALG_NC_NCRT = 0x0,
	HPRE_ALG_NC_CRT = 0x1,
	HPRE_ALG_KG_STD = 0x2,
	HPRE_ALG_KG_CRT = 0x3,
	HPRE_ALG_DH_G2 = 0x4,
	HPRE_ALG_DH = 0x5,
	HPRE_ALG_ECC_MUL = 0xD,
	/* shared by x25519 and x448, but x448 is not supported now */
	HPRE_ALG_CURVE25519_MUL = 0x10,
पूर्ण;

काष्ठा hpre_sqe अणु
	__le32 dw0;
	__u8 task_len1;
	__u8 task_len2;
	__u8 mrttest_num;
	__u8 resv1;
	__le64 key;
	__le64 in;
	__le64 out;
	__le16 tag;
	__le16 resv2;
#घोषणा _HPRE_SQE_ALIGN_EXT	7
	__le32 rsvd1[_HPRE_SQE_ALIGN_EXT];
पूर्ण;

काष्ठा hisi_qp *hpre_create_qp(u8 type);
पूर्णांक hpre_algs_रेजिस्टर(काष्ठा hisi_qm *qm);
व्योम hpre_algs_unरेजिस्टर(काष्ठा hisi_qm *qm);

#पूर्ण_अगर
