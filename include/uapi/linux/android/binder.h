<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2008 Google, Inc.
 *
 * Based on, but no दीर्घer compatible with, the original
 * OpenBinder.org binder driver पूर्णांकerface, which is:
 *
 * Copyright (c) 2005 Palmsource, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modअगरied under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित _UAPI_LINUX_BINDER_H
#घोषणा _UAPI_LINUX_BINDER_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा B_PACK_CHARS(c1, c2, c3, c4) \
	((((c1)<<24)) | (((c2)<<16)) | (((c3)<<8)) | (c4))
#घोषणा B_TYPE_LARGE 0x85

क्रमागत अणु
	BINDER_TYPE_BINDER	= B_PACK_CHARS('s', 'b', '*', B_TYPE_LARGE),
	BINDER_TYPE_WEAK_BINDER	= B_PACK_CHARS('w', 'b', '*', B_TYPE_LARGE),
	BINDER_TYPE_HANDLE	= B_PACK_CHARS('s', 'h', '*', B_TYPE_LARGE),
	BINDER_TYPE_WEAK_HANDLE	= B_PACK_CHARS('w', 'h', '*', B_TYPE_LARGE),
	BINDER_TYPE_FD		= B_PACK_CHARS('f', 'd', '*', B_TYPE_LARGE),
	BINDER_TYPE_FDA		= B_PACK_CHARS('f', 'd', 'a', B_TYPE_LARGE),
	BINDER_TYPE_PTR		= B_PACK_CHARS('p', 't', '*', B_TYPE_LARGE),
पूर्ण;

क्रमागत अणु
	FLAT_BINDER_FLAG_PRIORITY_MASK = 0xff,
	FLAT_BINDER_FLAG_ACCEPTS_FDS = 0x100,

	/**
	 * @FLAT_BINDER_FLAG_TXN_SECURITY_CTX: request security contexts
	 *
	 * Only when set, causes senders to include their security
	 * context
	 */
	FLAT_BINDER_FLAG_TXN_SECURITY_CTX = 0x1000,
पूर्ण;

#अगर_घोषित BINDER_IPC_32BIT
प्रकार __u32 binder_माप_प्रकार;
प्रकार __u32 binder_uपूर्णांकptr_t;
#अन्यथा
प्रकार __u64 binder_माप_प्रकार;
प्रकार __u64 binder_uपूर्णांकptr_t;
#पूर्ण_अगर

/**
 * काष्ठा binder_object_header - header shared by all binder metadata objects.
 * @type:	type of the object
 */
काष्ठा binder_object_header अणु
	__u32        type;
पूर्ण;

/*
 * This is the flattened representation of a Binder object क्रम transfer
 * between processes.  The 'offsets' supplied as part of a binder transaction
 * contains offsets पूर्णांकo the data where these काष्ठाures occur.  The Binder
 * driver takes care of re-writing the काष्ठाure type and data as it moves
 * between processes.
 */
काष्ठा flat_binder_object अणु
	काष्ठा binder_object_header	hdr;
	__u32				flags;

	/* 8 bytes of data. */
	जोड़ अणु
		binder_uपूर्णांकptr_t	binder;	/* local object */
		__u32			handle;	/* remote object */
	पूर्ण;

	/* extra data associated with local object */
	binder_uपूर्णांकptr_t	cookie;
पूर्ण;

/**
 * काष्ठा binder_fd_object - describes a filedescriptor to be fixed up.
 * @hdr:	common header काष्ठाure
 * @pad_flags:	padding to reमुख्य compatible with old userspace code
 * @pad_binder:	padding to reमुख्य compatible with old userspace code
 * @fd:		file descriptor
 * @cookie:	opaque data, used by user-space
 */
काष्ठा binder_fd_object अणु
	काष्ठा binder_object_header	hdr;
	__u32				pad_flags;
	जोड़ अणु
		binder_uपूर्णांकptr_t	pad_binder;
		__u32			fd;
	पूर्ण;

	binder_uपूर्णांकptr_t		cookie;
पूर्ण;

/* काष्ठा binder_buffer_object - object describing a userspace buffer
 * @hdr:		common header काष्ठाure
 * @flags:		one or more BINDER_BUFFER_* flags
 * @buffer:		address of the buffer
 * @length:		length of the buffer
 * @parent:		index in offset array poपूर्णांकing to parent buffer
 * @parent_offset:	offset in @parent poपूर्णांकing to this buffer
 *
 * A binder_buffer object represents an object that the
 * binder kernel driver can copy verbatim to the target
 * address space. A buffer itself may be poपूर्णांकed to from
 * within another buffer, meaning that the poपूर्णांकer inside
 * that other buffer needs to be fixed up as well. This
 * can be करोne by setting the BINDER_BUFFER_FLAG_HAS_PARENT
 * flag in @flags, by setting @parent buffer to the index
 * in the offset array poपूर्णांकing to the parent binder_buffer_object,
 * and by setting @parent_offset to the offset in the parent buffer
 * at which the poपूर्णांकer to this buffer is located.
 */
काष्ठा binder_buffer_object अणु
	काष्ठा binder_object_header	hdr;
	__u32				flags;
	binder_uपूर्णांकptr_t		buffer;
	binder_माप_प्रकार			length;
	binder_माप_प्रकार			parent;
	binder_माप_प्रकार			parent_offset;
पूर्ण;

क्रमागत अणु
	BINDER_BUFFER_FLAG_HAS_PARENT = 0x01,
पूर्ण;

/* काष्ठा binder_fd_array_object - object describing an array of fds in a buffer
 * @hdr:		common header काष्ठाure
 * @pad:		padding to ensure correct alignment
 * @num_fds:		number of file descriptors in the buffer
 * @parent:		index in offset array to buffer holding the fd array
 * @parent_offset:	start offset of fd array in the buffer
 *
 * A binder_fd_array object represents an array of file
 * descriptors embedded in a binder_buffer_object. It is
 * dअगरferent from a regular binder_buffer_object because it
 * describes a list of file descriptors to fix up, not an opaque
 * blob of memory, and hence the kernel needs to treat it dअगरferently.
 *
 * An example of how this would be used is with Android's
 * native_handle_t object, which is a काष्ठा with a list of पूर्णांकegers
 * and a list of file descriptors. The native_handle_t काष्ठा itself
 * will be represented by a काष्ठा binder_buffer_objct, whereas the
 * embedded list of file descriptors is represented by a
 * काष्ठा binder_fd_array_object with that binder_buffer_object as
 * a parent.
 */
काष्ठा binder_fd_array_object अणु
	काष्ठा binder_object_header	hdr;
	__u32				pad;
	binder_माप_प्रकार			num_fds;
	binder_माप_प्रकार			parent;
	binder_माप_प्रकार			parent_offset;
पूर्ण;

/*
 * On 64-bit platक्रमms where user code may run in 32-bits the driver must
 * translate the buffer (and local binder) addresses appropriately.
 */

काष्ठा binder_ग_लिखो_पढ़ो अणु
	binder_माप_प्रकार		ग_लिखो_size;	/* bytes to ग_लिखो */
	binder_माप_प्रकार		ग_लिखो_consumed;	/* bytes consumed by driver */
	binder_uपूर्णांकptr_t	ग_लिखो_buffer;
	binder_माप_प्रकार		पढ़ो_size;	/* bytes to पढ़ो */
	binder_माप_प्रकार		पढ़ो_consumed;	/* bytes consumed by driver */
	binder_uपूर्णांकptr_t	पढ़ो_buffer;
पूर्ण;

/* Use with BINDER_VERSION, driver fills in fields. */
काष्ठा binder_version अणु
	/* driver protocol version -- increment with incompatible change */
	__s32       protocol_version;
पूर्ण;

/* This is the current protocol version. */
#अगर_घोषित BINDER_IPC_32BIT
#घोषणा BINDER_CURRENT_PROTOCOL_VERSION 7
#अन्यथा
#घोषणा BINDER_CURRENT_PROTOCOL_VERSION 8
#पूर्ण_अगर

/*
 * Use with BINDER_GET_NODE_DEBUG_INFO, driver पढ़ोs ptr, ग_लिखोs to all fields.
 * Set ptr to शून्य क्रम the first call to get the info क्रम the first node, and
 * then repeat the call passing the previously वापसed value to get the next
 * nodes.  ptr will be 0 when there are no more nodes.
 */
काष्ठा binder_node_debug_info अणु
	binder_uपूर्णांकptr_t ptr;
	binder_uपूर्णांकptr_t cookie;
	__u32            has_strong_ref;
	__u32            has_weak_ref;
पूर्ण;

काष्ठा binder_node_info_क्रम_ref अणु
	__u32            handle;
	__u32            strong_count;
	__u32            weak_count;
	__u32            reserved1;
	__u32            reserved2;
	__u32            reserved3;
पूर्ण;

काष्ठा binder_मुक्तze_info अणु
	__u32            pid;
	__u32            enable;
	__u32            समयout_ms;
पूर्ण;

काष्ठा binder_frozen_status_info अणु
	__u32            pid;
	__u32            sync_recv;
	__u32            async_recv;
पूर्ण;

#घोषणा BINDER_WRITE_READ		_IOWR('b', 1, काष्ठा binder_ग_लिखो_पढ़ो)
#घोषणा BINDER_SET_IDLE_TIMEOUT		_IOW('b', 3, __s64)
#घोषणा BINDER_SET_MAX_THREADS		_IOW('b', 5, __u32)
#घोषणा BINDER_SET_IDLE_PRIORITY	_IOW('b', 6, __s32)
#घोषणा BINDER_SET_CONTEXT_MGR		_IOW('b', 7, __s32)
#घोषणा BINDER_THREAD_EXIT		_IOW('b', 8, __s32)
#घोषणा BINDER_VERSION			_IOWR('b', 9, काष्ठा binder_version)
#घोषणा BINDER_GET_NODE_DEBUG_INFO	_IOWR('b', 11, काष्ठा binder_node_debug_info)
#घोषणा BINDER_GET_NODE_INFO_FOR_REF	_IOWR('b', 12, काष्ठा binder_node_info_क्रम_ref)
#घोषणा BINDER_SET_CONTEXT_MGR_EXT	_IOW('b', 13, काष्ठा flat_binder_object)
#घोषणा BINDER_FREEZE			_IOW('b', 14, काष्ठा binder_मुक्तze_info)
#घोषणा BINDER_GET_FROZEN_INFO		_IOWR('b', 15, काष्ठा binder_frozen_status_info)
#घोषणा BINDER_ENABLE_ONEWAY_SPAM_DETECTION	_IOW('b', 16, __u32)

/*
 * NOTE: Two special error codes you should check क्रम when calling
 * in to the driver are:
 *
 * EINTR -- The operation has been पूर्णांकerupted.  This should be
 * handled by retrying the ioctl() until a dअगरferent error code
 * is वापसed.
 *
 * ECONNREFUSED -- The driver is no दीर्घer accepting operations
 * from your process.  That is, the process is being destroyed.
 * You should handle this by निकासing from your process.  Note
 * that once this error code is वापसed, all further calls to
 * the driver from any thपढ़ो will वापस this same code.
 */

क्रमागत transaction_flags अणु
	TF_ONE_WAY	= 0x01,	/* this is a one-way call: async, no वापस */
	TF_ROOT_OBJECT	= 0x04,	/* contents are the component's root object */
	TF_STATUS_CODE	= 0x08,	/* contents are a 32-bit status code */
	TF_ACCEPT_FDS	= 0x10,	/* allow replies with file descriptors */
	TF_CLEAR_BUF	= 0x20,	/* clear buffer on txn complete */
पूर्ण;

काष्ठा binder_transaction_data अणु
	/* The first two are only used क्रम bcTRANSACTION and brTRANSACTION,
	 * identअगरying the target and contents of the transaction.
	 */
	जोड़ अणु
		/* target descriptor of command transaction */
		__u32	handle;
		/* target descriptor of वापस transaction */
		binder_uपूर्णांकptr_t ptr;
	पूर्ण target;
	binder_uपूर्णांकptr_t	cookie;	/* target object cookie */
	__u32		code;		/* transaction command */

	/* General inक्रमmation about the transaction. */
	__u32	        flags;
	pid_t		sender_pid;
	uid_t		sender_euid;
	binder_माप_प्रकार	data_size;	/* number of bytes of data */
	binder_माप_प्रकार	offsets_size;	/* number of bytes of offsets */

	/* If this transaction is अंतरभूत, the data immediately
	 * follows here; otherwise, it ends with a poपूर्णांकer to
	 * the data buffer.
	 */
	जोड़ अणु
		काष्ठा अणु
			/* transaction data */
			binder_uपूर्णांकptr_t	buffer;
			/* offsets from buffer to flat_binder_object काष्ठाs */
			binder_uपूर्णांकptr_t	offsets;
		पूर्ण ptr;
		__u8	buf[8];
	पूर्ण data;
पूर्ण;

काष्ठा binder_transaction_data_secctx अणु
	काष्ठा binder_transaction_data transaction_data;
	binder_uपूर्णांकptr_t secctx;
पूर्ण;

काष्ठा binder_transaction_data_sg अणु
	काष्ठा binder_transaction_data transaction_data;
	binder_माप_प्रकार buffers_size;
पूर्ण;

काष्ठा binder_ptr_cookie अणु
	binder_uपूर्णांकptr_t ptr;
	binder_uपूर्णांकptr_t cookie;
पूर्ण;

काष्ठा binder_handle_cookie अणु
	__u32 handle;
	binder_uपूर्णांकptr_t cookie;
पूर्ण __packed;

काष्ठा binder_pri_desc अणु
	__s32 priority;
	__u32 desc;
पूर्ण;

काष्ठा binder_pri_ptr_cookie अणु
	__s32 priority;
	binder_uपूर्णांकptr_t ptr;
	binder_uपूर्णांकptr_t cookie;
पूर्ण;

क्रमागत binder_driver_वापस_protocol अणु
	BR_ERROR = _IOR('r', 0, __s32),
	/*
	 * पूर्णांक: error code
	 */

	BR_OK = _IO('r', 1),
	/* No parameters! */

	BR_TRANSACTION_SEC_CTX = _IOR('r', 2,
				      काष्ठा binder_transaction_data_secctx),
	/*
	 * binder_transaction_data_secctx: the received command.
	 */
	BR_TRANSACTION = _IOR('r', 2, काष्ठा binder_transaction_data),
	BR_REPLY = _IOR('r', 3, काष्ठा binder_transaction_data),
	/*
	 * binder_transaction_data: the received command.
	 */

	BR_ACQUIRE_RESULT = _IOR('r', 4, __s32),
	/*
	 * not currently supported
	 * पूर्णांक: 0 अगर the last bcATTEMPT_ACQUIRE was not successful.
	 * Else the remote object has acquired a primary reference.
	 */

	BR_DEAD_REPLY = _IO('r', 5),
	/*
	 * The target of the last transaction (either a bcTRANSACTION or
	 * a bcATTEMPT_ACQUIRE) is no दीर्घer with us.  No parameters.
	 */

	BR_TRANSACTION_COMPLETE = _IO('r', 6),
	/*
	 * No parameters... always refers to the last transaction requested
	 * (including replies).  Note that this will be sent even क्रम
	 * asynchronous transactions.
	 */

	BR_INCREFS = _IOR('r', 7, काष्ठा binder_ptr_cookie),
	BR_ACQUIRE = _IOR('r', 8, काष्ठा binder_ptr_cookie),
	BR_RELEASE = _IOR('r', 9, काष्ठा binder_ptr_cookie),
	BR_DECREFS = _IOR('r', 10, काष्ठा binder_ptr_cookie),
	/*
	 * व्योम *:	ptr to binder
	 * व्योम *: cookie क्रम binder
	 */

	BR_ATTEMPT_ACQUIRE = _IOR('r', 11, काष्ठा binder_pri_ptr_cookie),
	/*
	 * not currently supported
	 * पूर्णांक:	priority
	 * व्योम *: ptr to binder
	 * व्योम *: cookie क्रम binder
	 */

	BR_NOOP = _IO('r', 12),
	/*
	 * No parameters.  Do nothing and examine the next command.  It exists
	 * primarily so that we can replace it with a BR_SPAWN_LOOPER command.
	 */

	BR_SPAWN_LOOPER = _IO('r', 13),
	/*
	 * No parameters.  The driver has determined that a process has no
	 * thपढ़ोs रुकोing to service incoming transactions.  When a process
	 * receives this command, it must spawn a new service thपढ़ो and
	 * रेजिस्टर it via bcENTER_LOOPER.
	 */

	BR_FINISHED = _IO('r', 14),
	/*
	 * not currently supported
	 * stop thपढ़ोpool thपढ़ो
	 */

	BR_DEAD_BINDER = _IOR('r', 15, binder_uपूर्णांकptr_t),
	/*
	 * व्योम *: cookie
	 */
	BR_CLEAR_DEATH_NOTIFICATION_DONE = _IOR('r', 16, binder_uपूर्णांकptr_t),
	/*
	 * व्योम *: cookie
	 */

	BR_FAILED_REPLY = _IO('r', 17),
	/*
	 * The last transaction (either a bcTRANSACTION or
	 * a bcATTEMPT_ACQUIRE) failed (e.g. out of memory).  No parameters.
	 */

	BR_FROZEN_REPLY = _IO('r', 18),
	/*
	 * The target of the last transaction (either a bcTRANSACTION or
	 * a bcATTEMPT_ACQUIRE) is frozen.  No parameters.
	 */

	BR_ONEWAY_SPAM_SUSPECT = _IO('r', 19),
	/*
	 * Current process sent too many oneway calls to target, and the last
	 * asynchronous transaction makes the allocated async buffer size exceed
	 * detection threshold.  No parameters.
	 */
पूर्ण;

क्रमागत binder_driver_command_protocol अणु
	BC_TRANSACTION = _IOW('c', 0, काष्ठा binder_transaction_data),
	BC_REPLY = _IOW('c', 1, काष्ठा binder_transaction_data),
	/*
	 * binder_transaction_data: the sent command.
	 */

	BC_ACQUIRE_RESULT = _IOW('c', 2, __s32),
	/*
	 * not currently supported
	 * पूर्णांक:  0 अगर the last BR_ATTEMPT_ACQUIRE was not successful.
	 * Else you have acquired a primary reference on the object.
	 */

	BC_FREE_BUFFER = _IOW('c', 3, binder_uपूर्णांकptr_t),
	/*
	 * व्योम *: ptr to transaction data received on a पढ़ो
	 */

	BC_INCREFS = _IOW('c', 4, __u32),
	BC_ACQUIRE = _IOW('c', 5, __u32),
	BC_RELEASE = _IOW('c', 6, __u32),
	BC_DECREFS = _IOW('c', 7, __u32),
	/*
	 * पूर्णांक:	descriptor
	 */

	BC_INCREFS_DONE = _IOW('c', 8, काष्ठा binder_ptr_cookie),
	BC_ACQUIRE_DONE = _IOW('c', 9, काष्ठा binder_ptr_cookie),
	/*
	 * व्योम *: ptr to binder
	 * व्योम *: cookie क्रम binder
	 */

	BC_ATTEMPT_ACQUIRE = _IOW('c', 10, काष्ठा binder_pri_desc),
	/*
	 * not currently supported
	 * पूर्णांक: priority
	 * पूर्णांक: descriptor
	 */

	BC_REGISTER_LOOPER = _IO('c', 11),
	/*
	 * No parameters.
	 * Register a spawned looper thपढ़ो with the device.
	 */

	BC_ENTER_LOOPER = _IO('c', 12),
	BC_EXIT_LOOPER = _IO('c', 13),
	/*
	 * No parameters.
	 * These two commands are sent as an application-level thपढ़ो
	 * enters and निकासs the binder loop, respectively.  They are
	 * used so the binder can have an accurate count of the number
	 * of looping thपढ़ोs it has available.
	 */

	BC_REQUEST_DEATH_NOTIFICATION = _IOW('c', 14,
						काष्ठा binder_handle_cookie),
	/*
	 * पूर्णांक: handle
	 * व्योम *: cookie
	 */

	BC_CLEAR_DEATH_NOTIFICATION = _IOW('c', 15,
						काष्ठा binder_handle_cookie),
	/*
	 * पूर्णांक: handle
	 * व्योम *: cookie
	 */

	BC_DEAD_BINDER_DONE = _IOW('c', 16, binder_uपूर्णांकptr_t),
	/*
	 * व्योम *: cookie
	 */

	BC_TRANSACTION_SG = _IOW('c', 17, काष्ठा binder_transaction_data_sg),
	BC_REPLY_SG = _IOW('c', 18, काष्ठा binder_transaction_data_sg),
	/*
	 * binder_transaction_data_sg: the sent command.
	 */
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_BINDER_H */

