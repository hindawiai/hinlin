<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 */

#अगर_अघोषित AMDTEE_PRIVATE_H
#घोषणा AMDTEE_PRIVATE_H

#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/kref.h>
#समावेश <linux/types.h>
#समावेश "amdtee_if.h"

#घोषणा DRIVER_NAME	"amdtee"
#घोषणा DRIVER_AUTHOR   "AMD-TEE Linux driver team"

/* Some GlobalPlatक्रमm error codes used in this driver */
#घोषणा TEEC_SUCCESS			0x00000000
#घोषणा TEEC_ERROR_GENERIC		0xFFFF0000
#घोषणा TEEC_ERROR_BAD_PARAMETERS	0xFFFF0006
#घोषणा TEEC_ERROR_OUT_OF_MEMORY	0xFFFF000C
#घोषणा TEEC_ERROR_COMMUNICATION	0xFFFF000E

#घोषणा TEEC_ORIGIN_COMMS		0x00000002

/* Maximum number of sessions which can be खोलोed with a Trusted Application */
#घोषणा TEE_NUM_SESSIONS			32

#घोषणा TA_LOAD_PATH				"/amdtee"
#घोषणा TA_PATH_MAX				60

/**
 * काष्ठा amdtee - मुख्य service काष्ठा
 * @teedev:		client device
 * @pool:		shared memory pool
 */
काष्ठा amdtee अणु
	काष्ठा tee_device *teedev;
	काष्ठा tee_shm_pool *pool;
पूर्ण;

/**
 * काष्ठा amdtee_session - Trusted Application (TA) session related inक्रमmation.
 * @ta_handle:     handle to Trusted Application (TA) loaded in TEE environment
 * @refcount:      counter to keep track of sessions खोलोed क्रम the TA instance
 * @session_info:  an array poपूर्णांकing to TA allocated session data.
 * @sess_mask:     session usage bit-mask. If a particular bit is set, then the
 *                 corresponding @session_info entry is in use or valid.
 *
 * Session काष्ठाure is updated on खोलो_session and this inक्रमmation is used क्रम
 * subsequent operations with the Trusted Application.
 */
काष्ठा amdtee_session अणु
	काष्ठा list_head list_node;
	u32 ta_handle;
	काष्ठा kref refcount;
	u32 session_info[TEE_NUM_SESSIONS];
	DECLARE_BITMAP(sess_mask, TEE_NUM_SESSIONS);
	spinlock_t lock;	/* synchronizes access to @sess_mask */
पूर्ण;

/**
 * काष्ठा amdtee_context_data - AMD-TEE driver context data
 * @sess_list:    Keeps track of sessions खोलोed in current TEE context
 * @shm_list:     Keeps track of buffers allocated and mapped in current TEE
 *                context
 */
काष्ठा amdtee_context_data अणु
	काष्ठा list_head sess_list;
	काष्ठा list_head shm_list;
	काष्ठा mutex shm_mutex;   /* synchronizes access to @shm_list */
पूर्ण;

काष्ठा amdtee_driver_data अणु
	काष्ठा amdtee *amdtee;
पूर्ण;

काष्ठा shmem_desc अणु
	व्योम *kaddr;
	u64 size;
पूर्ण;

/**
 * काष्ठा amdtee_shm_data - Shared memory data
 * @kaddr:	Kernel भव address of shared memory
 * @buf_id:	Buffer id of memory mapped by TEE_CMD_ID_MAP_SHARED_MEM
 */
काष्ठा amdtee_shm_data अणु
	काष्ठा  list_head shm_node;
	व्योम    *kaddr;
	u32     buf_id;
पूर्ण;

/**
 * काष्ठा amdtee_ta_data - Keeps track of all TAs loaded in AMD Secure
 *			   Processor
 * @ta_handle:	Handle to TA loaded in TEE
 * @refcount:	Reference count क्रम the loaded TA
 */
काष्ठा amdtee_ta_data अणु
	काष्ठा list_head list_node;
	u32 ta_handle;
	u32 refcount;
पूर्ण;

#घोषणा LOWER_TWO_BYTE_MASK	0x0000FFFF

/**
 * set_session_id() - Sets the session identअगरier.
 * @ta_handle:      [in] handle of the loaded Trusted Application (TA)
 * @session_index:  [in] Session index. Range: 0 to (TEE_NUM_SESSIONS - 1).
 * @session:        [out] Poपूर्णांकer to session id
 *
 * Lower two bytes of the session identअगरier represents the TA handle and the
 * upper two bytes is session index.
 */
अटल अंतरभूत व्योम set_session_id(u32 ta_handle, u32 session_index,
				  u32 *session)
अणु
	*session = (session_index << 16) | (LOWER_TWO_BYTE_MASK & ta_handle);
पूर्ण

अटल अंतरभूत u32 get_ta_handle(u32 session)
अणु
	वापस session & LOWER_TWO_BYTE_MASK;
पूर्ण

अटल अंतरभूत u32 get_session_index(u32 session)
अणु
	वापस (session >> 16) & LOWER_TWO_BYTE_MASK;
पूर्ण

पूर्णांक amdtee_खोलो_session(काष्ठा tee_context *ctx,
			काष्ठा tee_ioctl_खोलो_session_arg *arg,
			काष्ठा tee_param *param);

पूर्णांक amdtee_बंद_session(काष्ठा tee_context *ctx, u32 session);

पूर्णांक amdtee_invoke_func(काष्ठा tee_context *ctx,
		       काष्ठा tee_ioctl_invoke_arg *arg,
		       काष्ठा tee_param *param);

पूर्णांक amdtee_cancel_req(काष्ठा tee_context *ctx, u32 cancel_id, u32 session);

पूर्णांक amdtee_map_shmem(काष्ठा tee_shm *shm);

व्योम amdtee_unmap_shmem(काष्ठा tee_shm *shm);

पूर्णांक handle_load_ta(व्योम *data, u32 size,
		   काष्ठा tee_ioctl_खोलो_session_arg *arg);

पूर्णांक handle_unload_ta(u32 ta_handle);

पूर्णांक handle_खोलो_session(काष्ठा tee_ioctl_खोलो_session_arg *arg, u32 *info,
			काष्ठा tee_param *p);

पूर्णांक handle_बंद_session(u32 ta_handle, u32 info);

पूर्णांक handle_map_shmem(u32 count, काष्ठा shmem_desc *start, u32 *buf_id);

व्योम handle_unmap_shmem(u32 buf_id);

पूर्णांक handle_invoke_cmd(काष्ठा tee_ioctl_invoke_arg *arg, u32 sinfo,
		      काष्ठा tee_param *p);

काष्ठा tee_shm_pool *amdtee_config_shm(व्योम);

u32 get_buffer_id(काष्ठा tee_shm *shm);
#पूर्ण_अगर /*AMDTEE_PRIVATE_H*/
