<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_HISI_QM_H
#घोषणा _UAPI_HISI_QM_H

#समावेश <linux/types.h>

/**
 * काष्ठा hisi_qp_ctx - User data क्रम hisi qp.
 * @id: qp_index वापस to user space
 * @qc_type: Accelerator algorithm type
 */
काष्ठा hisi_qp_ctx अणु
	__u16 id;
	__u16 qc_type;
पूर्ण;

#घोषणा HISI_QM_API_VER_BASE "hisi_qm_v1"
#घोषणा HISI_QM_API_VER2_BASE "hisi_qm_v2"
#घोषणा HISI_QM_API_VER3_BASE "hisi_qm_v3"

/* UACCE_CMD_QM_SET_QP_CTX: Set qp algorithm type */
#घोषणा UACCE_CMD_QM_SET_QP_CTX	_IOWR('H', 10, काष्ठा hisi_qp_ctx)

#पूर्ण_अगर
