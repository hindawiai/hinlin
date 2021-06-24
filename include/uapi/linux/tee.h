<शैली गुरु>
/*
 * Copyright (c) 2015-2016, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary क्रमm must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the करोcumentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __TEE_H
#घोषणा __TEE_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/*
 * This file describes the API provided by a TEE driver to user space.
 *
 * Each TEE driver defines a TEE specअगरic protocol which is used क्रम the
 * data passed back and क्रमth using TEE_IOC_CMD.
 */

/* Helpers to make the ioctl defines */
#घोषणा TEE_IOC_MAGIC	0xa4
#घोषणा TEE_IOC_BASE	0

/* Flags relating to shared memory */
#घोषणा TEE_IOCTL_SHM_MAPPED	0x1	/* memory mapped in normal world */
#घोषणा TEE_IOCTL_SHM_DMA_BUF	0x2	/* dma-buf handle on shared memory */

#घोषणा TEE_MAX_ARG_SIZE	1024

#घोषणा TEE_GEN_CAP_GP		(1 << 0)/* GlobalPlatक्रमm compliant TEE */
#घोषणा TEE_GEN_CAP_PRIVILEGED	(1 << 1)/* Privileged device (क्रम supplicant) */
#घोषणा TEE_GEN_CAP_REG_MEM	(1 << 2)/* Supports रेजिस्टरing shared memory */
#घोषणा TEE_GEN_CAP_MEMREF_शून्य	(1 << 3)/* शून्य MemRef support */

#घोषणा TEE_MEMREF_शून्य		(__u64)(-1) /* शून्य MemRef Buffer */

/*
 * TEE Implementation ID
 */
#घोषणा TEE_IMPL_ID_OPTEE	1
#घोषणा TEE_IMPL_ID_AMDTEE	2

/*
 * OP-TEE specअगरic capabilities
 */
#घोषणा TEE_OPTEE_CAP_TZ	(1 << 0)

/**
 * काष्ठा tee_ioctl_version_data - TEE version
 * @impl_id:	[out] TEE implementation id
 * @impl_caps:	[out] Implementation specअगरic capabilities
 * @gen_caps:	[out] Generic capabilities, defined by TEE_GEN_CAPS_* above
 *
 * Identअगरies the TEE implementation, @impl_id is one of TEE_IMPL_ID_* above.
 * @impl_caps is implementation specअगरic, क्रम example TEE_OPTEE_CAP_*
 * is valid when @impl_id == TEE_IMPL_ID_OPTEE.
 */
काष्ठा tee_ioctl_version_data अणु
	__u32 impl_id;
	__u32 impl_caps;
	__u32 gen_caps;
पूर्ण;

/**
 * TEE_IOC_VERSION - query version of TEE
 *
 * Takes a tee_ioctl_version_data काष्ठा and वापसs with the TEE version
 * data filled in.
 */
#घोषणा TEE_IOC_VERSION		_IOR(TEE_IOC_MAGIC, TEE_IOC_BASE + 0, \
				     काष्ठा tee_ioctl_version_data)

/**
 * काष्ठा tee_ioctl_shm_alloc_data - Shared memory allocate argument
 * @size:	[in/out] Size of shared memory to allocate
 * @flags:	[in/out] Flags to/from allocation.
 * @id:		[out] Identअगरier of the shared memory
 *
 * The flags field should currently be zero as input. Updated by the call
 * with actual flags as defined by TEE_IOCTL_SHM_* above.
 * This काष्ठाure is used as argument क्रम TEE_IOC_SHM_ALLOC below.
 */
काष्ठा tee_ioctl_shm_alloc_data अणु
	__u64 size;
	__u32 flags;
	__s32 id;
पूर्ण;

/**
 * TEE_IOC_SHM_ALLOC - allocate shared memory
 *
 * Allocates shared memory between the user space process and secure OS.
 *
 * Returns a file descriptor on success or < 0 on failure
 *
 * The वापसed file descriptor is used to map the shared memory पूर्णांकo user
 * space. The shared memory is मुक्तd when the descriptor is बंदd and the
 * memory is unmapped.
 */
#घोषणा TEE_IOC_SHM_ALLOC	_IOWR(TEE_IOC_MAGIC, TEE_IOC_BASE + 1, \
				     काष्ठा tee_ioctl_shm_alloc_data)

/**
 * काष्ठा tee_ioctl_buf_data - Variable sized buffer
 * @buf_ptr:	[in] A __user poपूर्णांकer to a buffer
 * @buf_len:	[in] Length of the buffer above
 *
 * Used as argument क्रम TEE_IOC_OPEN_SESSION, TEE_IOC_INVOKE,
 * TEE_IOC_SUPPL_RECV, and TEE_IOC_SUPPL_SEND below.
 */
काष्ठा tee_ioctl_buf_data अणु
	__u64 buf_ptr;
	__u64 buf_len;
पूर्ण;

/*
 * Attributes क्रम काष्ठा tee_ioctl_param, selects field in the जोड़
 */
#घोषणा TEE_IOCTL_PARAM_ATTR_TYPE_NONE		0	/* parameter not used */

/*
 * These defines value parameters (काष्ठा tee_ioctl_param_value)
 */
#घोषणा TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT	1
#घोषणा TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT	2
#घोषणा TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT	3	/* input and output */

/*
 * These defines shared memory reference parameters (काष्ठा
 * tee_ioctl_param_memref)
 */
#घोषणा TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT	5
#घोषणा TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT	6
#घोषणा TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT	7	/* input and output */

/*
 * Mask क्रम the type part of the attribute, leaves room क्रम more types
 */
#घोषणा TEE_IOCTL_PARAM_ATTR_TYPE_MASK		0xff

/* Meta parameter carrying extra inक्रमmation about the message. */
#घोषणा TEE_IOCTL_PARAM_ATTR_META		0x100

/* Mask of all known attr bits */
#घोषणा TEE_IOCTL_PARAM_ATTR_MASK \
	(TEE_IOCTL_PARAM_ATTR_TYPE_MASK | TEE_IOCTL_PARAM_ATTR_META)

/*
 * Matches TEEC_LOGIN_* in GP TEE Client API
 * Are only defined क्रम GP compliant TEEs
 */
#घोषणा TEE_IOCTL_LOGIN_PUBLIC			0
#घोषणा TEE_IOCTL_LOGIN_USER			1
#घोषणा TEE_IOCTL_LOGIN_GROUP			2
#घोषणा TEE_IOCTL_LOGIN_APPLICATION		4
#घोषणा TEE_IOCTL_LOGIN_USER_APPLICATION	5
#घोषणा TEE_IOCTL_LOGIN_GROUP_APPLICATION	6
/*
 * Disallow user-space to use GP implementation specअगरic login
 * method range (0x80000000 - 0xBFFFFFFF). This range is rather
 * being reserved क्रम REE kernel clients or TEE implementation.
 */
#घोषणा TEE_IOCTL_LOGIN_REE_KERNEL_MIN		0x80000000
#घोषणा TEE_IOCTL_LOGIN_REE_KERNEL_MAX		0xBFFFFFFF
/* Private login method क्रम REE kernel clients */
#घोषणा TEE_IOCTL_LOGIN_REE_KERNEL		0x80000000

/**
 * काष्ठा tee_ioctl_param - parameter
 * @attr: attributes
 * @a: अगर a memref, offset पूर्णांकo the shared memory object, अन्यथा a value parameter
 * @b: अगर a memref, size of the buffer, अन्यथा a value parameter
 * @c: अगर a memref, shared memory identअगरier, अन्यथा a value parameter
 *
 * @attr & TEE_PARAM_ATTR_TYPE_MASK indicates अगर memref or value is used in
 * the जोड़. TEE_PARAM_ATTR_TYPE_VALUE_* indicates value and
 * TEE_PARAM_ATTR_TYPE_MEMREF_* indicates memref. TEE_PARAM_ATTR_TYPE_NONE
 * indicates that none of the members are used.
 *
 * Shared memory is allocated with TEE_IOC_SHM_ALLOC which वापसs an
 * identअगरier representing the shared memory object. A memref can reference
 * a part of a shared memory by specअगरying an offset (@a) and size (@b) of
 * the object. To supply the entire shared memory object set the offset
 * (@a) to 0 and size (@b) to the previously वापसed size of the object.
 *
 * A client may need to present a शून्य poपूर्णांकer in the argument
 * passed to a trusted application in the TEE.
 * This is also a requirement in GlobalPlatक्रमm Client API v1.0c
 * (section 3.2.5 memory references), which can be found at
 * http://www.globalplatक्रमm.org/specअगरicationsdevice.asp
 *
 * If a शून्य poपूर्णांकer is passed to a TA in the TEE, the (@c)
 * IOCTL parameters value must be set to TEE_MEMREF_शून्य indicating a शून्य
 * memory reference.
 */
काष्ठा tee_ioctl_param अणु
	__u64 attr;
	__u64 a;
	__u64 b;
	__u64 c;
पूर्ण;

#घोषणा TEE_IOCTL_UUID_LEN		16

/**
 * काष्ठा tee_ioctl_खोलो_session_arg - Open session argument
 * @uuid:	[in] UUID of the Trusted Application
 * @clnt_uuid:	[in] UUID of client
 * @clnt_login:	[in] Login class of client, TEE_IOCTL_LOGIN_* above
 * @cancel_id:	[in] Cancellation id, a unique value to identअगरy this request
 * @session:	[out] Session id
 * @ret:	[out] वापस value
 * @ret_origin	[out] origin of the वापस value
 * @num_params	[in] number of parameters following this काष्ठा
 */
काष्ठा tee_ioctl_खोलो_session_arg अणु
	__u8 uuid[TEE_IOCTL_UUID_LEN];
	__u8 clnt_uuid[TEE_IOCTL_UUID_LEN];
	__u32 clnt_login;
	__u32 cancel_id;
	__u32 session;
	__u32 ret;
	__u32 ret_origin;
	__u32 num_params;
	/* num_params tells the actual number of element in params */
	काष्ठा tee_ioctl_param params[];
पूर्ण;

/**
 * TEE_IOC_OPEN_SESSION - खोलोs a session to a Trusted Application
 *
 * Takes a काष्ठा tee_ioctl_buf_data which contains a काष्ठा
 * tee_ioctl_खोलो_session_arg followed by any array of काष्ठा
 * tee_ioctl_param
 */
#घोषणा TEE_IOC_OPEN_SESSION	_IOR(TEE_IOC_MAGIC, TEE_IOC_BASE + 2, \
				     काष्ठा tee_ioctl_buf_data)

/**
 * काष्ठा tee_ioctl_invoke_func_arg - Invokes a function in a Trusted
 * Application
 * @func:	[in] Trusted Application function, specअगरic to the TA
 * @session:	[in] Session id
 * @cancel_id:	[in] Cancellation id, a unique value to identअगरy this request
 * @ret:	[out] वापस value
 * @ret_origin	[out] origin of the वापस value
 * @num_params	[in] number of parameters following this काष्ठा
 */
काष्ठा tee_ioctl_invoke_arg अणु
	__u32 func;
	__u32 session;
	__u32 cancel_id;
	__u32 ret;
	__u32 ret_origin;
	__u32 num_params;
	/* num_params tells the actual number of element in params */
	काष्ठा tee_ioctl_param params[];
पूर्ण;

/**
 * TEE_IOC_INVOKE - Invokes a function in a Trusted Application
 *
 * Takes a काष्ठा tee_ioctl_buf_data which contains a काष्ठा
 * tee_invoke_func_arg followed by any array of काष्ठा tee_param
 */
#घोषणा TEE_IOC_INVOKE		_IOR(TEE_IOC_MAGIC, TEE_IOC_BASE + 3, \
				     काष्ठा tee_ioctl_buf_data)

/**
 * काष्ठा tee_ioctl_cancel_arg - Cancels an खोलो session or invoke ioctl
 * @cancel_id:	[in] Cancellation id, a unique value to identअगरy this request
 * @session:	[in] Session id, अगर the session is खोलोed, अन्यथा set to 0
 */
काष्ठा tee_ioctl_cancel_arg अणु
	__u32 cancel_id;
	__u32 session;
पूर्ण;

/**
 * TEE_IOC_CANCEL - Cancels an खोलो session or invoke
 */
#घोषणा TEE_IOC_CANCEL		_IOR(TEE_IOC_MAGIC, TEE_IOC_BASE + 4, \
				     काष्ठा tee_ioctl_cancel_arg)

/**
 * काष्ठा tee_ioctl_बंद_session_arg - Closes an खोलो session
 * @session:	[in] Session id
 */
काष्ठा tee_ioctl_बंद_session_arg अणु
	__u32 session;
पूर्ण;

/**
 * TEE_IOC_CLOSE_SESSION - Closes a session
 */
#घोषणा TEE_IOC_CLOSE_SESSION	_IOR(TEE_IOC_MAGIC, TEE_IOC_BASE + 5, \
				     काष्ठा tee_ioctl_बंद_session_arg)

/**
 * काष्ठा tee_iocl_supp_recv_arg - Receive a request क्रम a supplicant function
 * @func:	[in] supplicant function
 * @num_params	[in/out] number of parameters following this काष्ठा
 *
 * @num_params is the number of params that tee-supplicant has room to
 * receive when input, @num_params is the number of actual params
 * tee-supplicant receives when output.
 */
काष्ठा tee_iocl_supp_recv_arg अणु
	__u32 func;
	__u32 num_params;
	/* num_params tells the actual number of element in params */
	काष्ठा tee_ioctl_param params[];
पूर्ण;

/**
 * TEE_IOC_SUPPL_RECV - Receive a request क्रम a supplicant function
 *
 * Takes a काष्ठा tee_ioctl_buf_data which contains a काष्ठा
 * tee_iocl_supp_recv_arg followed by any array of काष्ठा tee_param
 */
#घोषणा TEE_IOC_SUPPL_RECV	_IOR(TEE_IOC_MAGIC, TEE_IOC_BASE + 6, \
				     काष्ठा tee_ioctl_buf_data)

/**
 * काष्ठा tee_iocl_supp_send_arg - Send a response to a received request
 * @ret:	[out] वापस value
 * @num_params	[in] number of parameters following this काष्ठा
 */
काष्ठा tee_iocl_supp_send_arg अणु
	__u32 ret;
	__u32 num_params;
	/* num_params tells the actual number of element in params */
	काष्ठा tee_ioctl_param params[];
पूर्ण;

/**
 * TEE_IOC_SUPPL_SEND - Send a response to a received request
 *
 * Takes a काष्ठा tee_ioctl_buf_data which contains a काष्ठा
 * tee_iocl_supp_send_arg followed by any array of काष्ठा tee_param
 */
#घोषणा TEE_IOC_SUPPL_SEND	_IOR(TEE_IOC_MAGIC, TEE_IOC_BASE + 7, \
				     काष्ठा tee_ioctl_buf_data)

/**
 * काष्ठा tee_ioctl_shm_रेजिस्टर_data - Shared memory रेजिस्टर argument
 * @addr:      [in] Start address of shared memory to रेजिस्टर
 * @length:    [in/out] Length of shared memory to रेजिस्टर
 * @flags:     [in/out] Flags to/from registration.
 * @id:                [out] Identअगरier of the shared memory
 *
 * The flags field should currently be zero as input. Updated by the call
 * with actual flags as defined by TEE_IOCTL_SHM_* above.
 * This काष्ठाure is used as argument क्रम TEE_IOC_SHM_REGISTER below.
 */
काष्ठा tee_ioctl_shm_रेजिस्टर_data अणु
	__u64 addr;
	__u64 length;
	__u32 flags;
	__s32 id;
पूर्ण;

/**
 * TEE_IOC_SHM_REGISTER - Register shared memory argument
 *
 * Registers shared memory between the user space process and secure OS.
 *
 * Returns a file descriptor on success or < 0 on failure
 *
 * The shared memory is unरेजिस्टरred when the descriptor is बंदd.
 */
#घोषणा TEE_IOC_SHM_REGISTER   _IOWR(TEE_IOC_MAGIC, TEE_IOC_BASE + 9, \
				     काष्ठा tee_ioctl_shm_रेजिस्टर_data)
/*
 * Five syscalls are used when communicating with the TEE driver.
 * खोलो(): खोलोs the device associated with the driver
 * ioctl(): as described above operating on the file descriptor from खोलो()
 * बंद(): two हालs
 *   - बंदs the device file descriptor
 *   - बंदs a file descriptor connected to allocated shared memory
 * mmap(): maps shared memory पूर्णांकo user space using inक्रमmation from काष्ठा
 *	   tee_ioctl_shm_alloc_data
 * munmap(): unmaps previously shared memory
 */

#पूर्ण_अगर /*__TEE_H*/
