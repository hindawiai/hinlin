<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _IAVF_ADMINQ_H_
#घोषणा _IAVF_ADMINQ_H_

#समावेश "iavf_osdep.h"
#समावेश "iavf_status.h"
#समावेश "iavf_adminq_cmd.h"

#घोषणा IAVF_ADMINQ_DESC(R, i)   \
	(&(((काष्ठा iavf_aq_desc *)((R).desc_buf.va))[i]))

#घोषणा IAVF_ADMINQ_DESC_ALIGNMENT 4096

काष्ठा iavf_adminq_ring अणु
	काष्ठा iavf_virt_mem dma_head;	/* space क्रम dma काष्ठाures */
	काष्ठा iavf_dma_mem desc_buf;	/* descriptor ring memory */
	काष्ठा iavf_virt_mem cmd_buf;	/* command buffer memory */

	जोड़ अणु
		काष्ठा iavf_dma_mem *asq_bi;
		काष्ठा iavf_dma_mem *arq_bi;
	पूर्ण r;

	u16 count;		/* Number of descriptors */
	u16 rx_buf_len;		/* Admin Receive Queue buffer length */

	/* used क्रम पूर्णांकerrupt processing */
	u16 next_to_use;
	u16 next_to_clean;

	/* used क्रम queue tracking */
	u32 head;
	u32 tail;
	u32 len;
	u32 bah;
	u32 bal;
पूर्ण;

/* ASQ transaction details */
काष्ठा iavf_asq_cmd_details अणु
	व्योम *callback; /* cast from type IAVF_ADMINQ_CALLBACK */
	u64 cookie;
	u16 flags_ena;
	u16 flags_dis;
	bool async;
	bool postpone;
	काष्ठा iavf_aq_desc *wb_desc;
पूर्ण;

#घोषणा IAVF_ADMINQ_DETAILS(R, i)   \
	(&(((काष्ठा iavf_asq_cmd_details *)((R).cmd_buf.va))[i]))

/* ARQ event inक्रमmation */
काष्ठा iavf_arq_event_info अणु
	काष्ठा iavf_aq_desc desc;
	u16 msg_len;
	u16 buf_len;
	u8 *msg_buf;
पूर्ण;

/* Admin Queue inक्रमmation */
काष्ठा iavf_adminq_info अणु
	काष्ठा iavf_adminq_ring arq;    /* receive queue */
	काष्ठा iavf_adminq_ring asq;    /* send queue */
	u32 asq_cmd_समयout;            /* send queue cmd ग_लिखो back समयout*/
	u16 num_arq_entries;            /* receive queue depth */
	u16 num_asq_entries;            /* send queue depth */
	u16 arq_buf_size;               /* receive queue buffer size */
	u16 asq_buf_size;               /* send queue buffer size */
	u16 fw_maj_ver;                 /* firmware major version */
	u16 fw_min_ver;                 /* firmware minor version */
	u32 fw_build;                   /* firmware build number */
	u16 api_maj_ver;                /* api major version */
	u16 api_min_ver;                /* api minor version */

	काष्ठा mutex asq_mutex; /* Send queue lock */
	काष्ठा mutex arq_mutex; /* Receive queue lock */

	/* last status values on send and receive queues */
	क्रमागत iavf_admin_queue_err asq_last_status;
	क्रमागत iavf_admin_queue_err arq_last_status;
पूर्ण;

/**
 * iavf_aq_rc_to_posix - convert errors to user-land codes
 * @aq_ret: AdminQ handler error code can override aq_rc
 * @aq_rc: AdminQ firmware error code to convert
 **/
अटल अंतरभूत पूर्णांक iavf_aq_rc_to_posix(पूर्णांक aq_ret, पूर्णांक aq_rc)
अणु
	पूर्णांक aq_to_posix[] = अणु
		0,           /* IAVF_AQ_RC_OK */
		-EPERM,      /* IAVF_AQ_RC_EPERM */
		-ENOENT,     /* IAVF_AQ_RC_ENOENT */
		-ESRCH,      /* IAVF_AQ_RC_ESRCH */
		-EINTR,      /* IAVF_AQ_RC_EINTR */
		-EIO,        /* IAVF_AQ_RC_EIO */
		-ENXIO,      /* IAVF_AQ_RC_ENXIO */
		-E2BIG,      /* IAVF_AQ_RC_E2BIG */
		-EAGAIN,     /* IAVF_AQ_RC_EAGAIN */
		-ENOMEM,     /* IAVF_AQ_RC_ENOMEM */
		-EACCES,     /* IAVF_AQ_RC_EACCES */
		-EFAULT,     /* IAVF_AQ_RC_EFAULT */
		-EBUSY,      /* IAVF_AQ_RC_EBUSY */
		-EEXIST,     /* IAVF_AQ_RC_EEXIST */
		-EINVAL,     /* IAVF_AQ_RC_EINVAL */
		-ENOTTY,     /* IAVF_AQ_RC_ENOTTY */
		-ENOSPC,     /* IAVF_AQ_RC_ENOSPC */
		-ENOSYS,     /* IAVF_AQ_RC_ENOSYS */
		-दुस्फल,     /* IAVF_AQ_RC_दुस्फल */
		-EPIPE,      /* IAVF_AQ_RC_EFLUSHED */
		-ESPIPE,     /* IAVF_AQ_RC_BAD_ADDR */
		-EROFS,      /* IAVF_AQ_RC_EMODE */
		-EFBIG,      /* IAVF_AQ_RC_EFBIG */
	पूर्ण;

	/* aq_rc is invalid अगर AQ समयd out */
	अगर (aq_ret == IAVF_ERR_ADMIN_QUEUE_TIMEOUT)
		वापस -EAGAIN;

	अगर (!((u32)aq_rc < (माप(aq_to_posix) / माप((aq_to_posix)[0]))))
		वापस -दुस्फल;

	वापस aq_to_posix[aq_rc];
पूर्ण

/* general inक्रमmation */
#घोषणा IAVF_AQ_LARGE_BUF	512
#घोषणा IAVF_ASQ_CMD_TIMEOUT	250000  /* usecs */

व्योम iavf_fill_शेष_direct_cmd_desc(काष्ठा iavf_aq_desc *desc, u16 opcode);

#पूर्ण_अगर /* _IAVF_ADMINQ_H_ */
