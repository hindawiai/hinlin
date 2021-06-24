<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 WITH Linux-syscall-note) OR MIT */
/*
 * Header file क्रम the io_uring पूर्णांकerface.
 *
 * Copyright (C) 2019 Jens Axboe
 * Copyright (C) 2019 Christoph Hellwig
 */
#अगर_अघोषित LINUX_IO_URING_H
#घोषणा LINUX_IO_URING_H

#समावेश <linux/fs.h>
#समावेश <linux/types.h>

/*
 * IO submission data काष्ठाure (Submission Queue Entry)
 */
काष्ठा io_uring_sqe अणु
	__u8	opcode;		/* type of operation क्रम this sqe */
	__u8	flags;		/* IOSQE_ flags */
	__u16	ioprio;		/* ioprio क्रम the request */
	__s32	fd;		/* file descriptor to करो IO on */
	जोड़ अणु
		__u64	off;	/* offset पूर्णांकo file */
		__u64	addr2;
	पूर्ण;
	जोड़ अणु
		__u64	addr;	/* poपूर्णांकer to buffer or iovecs */
		__u64	splice_off_in;
	पूर्ण;
	__u32	len;		/* buffer size or number of iovecs */
	जोड़ अणु
		__kernel_rwf_t	rw_flags;
		__u32		fsync_flags;
		__u16		poll_events;	/* compatibility */
		__u32		poll32_events;	/* word-reversed क्रम BE */
		__u32		sync_range_flags;
		__u32		msg_flags;
		__u32		समयout_flags;
		__u32		accept_flags;
		__u32		cancel_flags;
		__u32		खोलो_flags;
		__u32		statx_flags;
		__u32		fadvise_advice;
		__u32		splice_flags;
		__u32		नाम_flags;
		__u32		unlink_flags;
	पूर्ण;
	__u64	user_data;	/* data to be passed back at completion समय */
	जोड़ अणु
		काष्ठा अणु
			/* pack this to aव्योम bogus arm OABI complaपूर्णांकs */
			जोड़ अणु
				/* index पूर्णांकo fixed buffers, अगर used */
				__u16	buf_index;
				/* क्रम grouped buffer selection */
				__u16	buf_group;
			पूर्ण __attribute__((packed));
			/* personality to use, अगर used */
			__u16	personality;
			__s32	splice_fd_in;
		पूर्ण;
		__u64	__pad2[3];
	पूर्ण;
पूर्ण;

क्रमागत अणु
	IOSQE_FIXED_खाता_BIT,
	IOSQE_IO_DRAIN_BIT,
	IOSQE_IO_LINK_BIT,
	IOSQE_IO_HARDLINK_BIT,
	IOSQE_ASYNC_BIT,
	IOSQE_BUFFER_SELECT_BIT,
पूर्ण;

/*
 * sqe->flags
 */
/* use fixed fileset */
#घोषणा IOSQE_FIXED_खाता	(1U << IOSQE_FIXED_खाता_BIT)
/* issue after inflight IO */
#घोषणा IOSQE_IO_DRAIN		(1U << IOSQE_IO_DRAIN_BIT)
/* links next sqe */
#घोषणा IOSQE_IO_LINK		(1U << IOSQE_IO_LINK_BIT)
/* like LINK, but stronger */
#घोषणा IOSQE_IO_HARDLINK	(1U << IOSQE_IO_HARDLINK_BIT)
/* always go async */
#घोषणा IOSQE_ASYNC		(1U << IOSQE_ASYNC_BIT)
/* select buffer from sqe->buf_group */
#घोषणा IOSQE_BUFFER_SELECT	(1U << IOSQE_BUFFER_SELECT_BIT)

/*
 * io_uring_setup() flags
 */
#घोषणा IORING_SETUP_IOPOLL	(1U << 0)	/* io_context is polled */
#घोषणा IORING_SETUP_SQPOLL	(1U << 1)	/* SQ poll thपढ़ो */
#घोषणा IORING_SETUP_SQ_AFF	(1U << 2)	/* sq_thपढ़ो_cpu is valid */
#घोषणा IORING_SETUP_CQSIZE	(1U << 3)	/* app defines CQ size */
#घोषणा IORING_SETUP_CLAMP	(1U << 4)	/* clamp SQ/CQ ring sizes */
#घोषणा IORING_SETUP_ATTACH_WQ	(1U << 5)	/* attach to existing wq */
#घोषणा IORING_SETUP_R_DISABLED	(1U << 6)	/* start with ring disabled */

क्रमागत अणु
	IORING_OP_NOP,
	IORING_OP_READV,
	IORING_OP_WRITEV,
	IORING_OP_FSYNC,
	IORING_OP_READ_FIXED,
	IORING_OP_WRITE_FIXED,
	IORING_OP_POLL_ADD,
	IORING_OP_POLL_REMOVE,
	IORING_OP_SYNC_खाता_RANGE,
	IORING_OP_SENDMSG,
	IORING_OP_RECVMSG,
	IORING_OP_TIMEOUT,
	IORING_OP_TIMEOUT_REMOVE,
	IORING_OP_ACCEPT,
	IORING_OP_ASYNC_CANCEL,
	IORING_OP_LINK_TIMEOUT,
	IORING_OP_CONNECT,
	IORING_OP_FALLOCATE,
	IORING_OP_OPENAT,
	IORING_OP_CLOSE,
	IORING_OP_खाताS_UPDATE,
	IORING_OP_STATX,
	IORING_OP_READ,
	IORING_OP_WRITE,
	IORING_OP_FADVISE,
	IORING_OP_MADVISE,
	IORING_OP_SEND,
	IORING_OP_RECV,
	IORING_OP_OPENAT2,
	IORING_OP_EPOLL_CTL,
	IORING_OP_SPLICE,
	IORING_OP_PROVIDE_BUFFERS,
	IORING_OP_REMOVE_BUFFERS,
	IORING_OP_TEE,
	IORING_OP_SHUTDOWN,
	IORING_OP_RENAMEAT,
	IORING_OP_UNLINKAT,

	/* this goes last, obviously */
	IORING_OP_LAST,
पूर्ण;

/*
 * sqe->fsync_flags
 */
#घोषणा IORING_FSYNC_DATASYNC	(1U << 0)

/*
 * sqe->समयout_flags
 */
#घोषणा IORING_TIMEOUT_ABS	(1U << 0)
#घोषणा IORING_TIMEOUT_UPDATE	(1U << 1)

/*
 * sqe->splice_flags
 * extends splice(2) flags
 */
#घोषणा SPLICE_F_FD_IN_FIXED	(1U << 31) /* the last bit of __u32 */

/*
 * POLL_ADD flags. Note that since sqe->poll_events is the flag space, the
 * command flags क्रम POLL_ADD are stored in sqe->len.
 *
 * IORING_POLL_ADD_MULTI	Multishot poll. Sets IORING_CQE_F_MORE अगर
 *				the poll handler will जारी to report
 *				CQEs on behalf of the same SQE.
 *
 * IORING_POLL_UPDATE		Update existing poll request, matching
 *				sqe->addr as the old user_data field.
 */
#घोषणा IORING_POLL_ADD_MULTI	(1U << 0)
#घोषणा IORING_POLL_UPDATE_EVENTS	(1U << 1)
#घोषणा IORING_POLL_UPDATE_USER_DATA	(1U << 2)

/*
 * IO completion data काष्ठाure (Completion Queue Entry)
 */
काष्ठा io_uring_cqe अणु
	__u64	user_data;	/* sqe->data submission passed back */
	__s32	res;		/* result code क्रम this event */
	__u32	flags;
पूर्ण;

/*
 * cqe->flags
 *
 * IORING_CQE_F_BUFFER	If set, the upper 16 bits are the buffer ID
 * IORING_CQE_F_MORE	If set, parent SQE will generate more CQE entries
 */
#घोषणा IORING_CQE_F_BUFFER		(1U << 0)
#घोषणा IORING_CQE_F_MORE		(1U << 1)

क्रमागत अणु
	IORING_CQE_BUFFER_SHIFT		= 16,
पूर्ण;

/*
 * Magic offsets क्रम the application to mmap the data it needs
 */
#घोषणा IORING_OFF_SQ_RING		0ULL
#घोषणा IORING_OFF_CQ_RING		0x8000000ULL
#घोषणा IORING_OFF_SQES			0x10000000ULL

/*
 * Filled with the offset क्रम mmap(2)
 */
काष्ठा io_sqring_offsets अणु
	__u32 head;
	__u32 tail;
	__u32 ring_mask;
	__u32 ring_entries;
	__u32 flags;
	__u32 dropped;
	__u32 array;
	__u32 resv1;
	__u64 resv2;
पूर्ण;

/*
 * sq_ring->flags
 */
#घोषणा IORING_SQ_NEED_WAKEUP	(1U << 0) /* needs io_uring_enter wakeup */
#घोषणा IORING_SQ_CQ_OVERFLOW	(1U << 1) /* CQ ring is overflown */

काष्ठा io_cqring_offsets अणु
	__u32 head;
	__u32 tail;
	__u32 ring_mask;
	__u32 ring_entries;
	__u32 overflow;
	__u32 cqes;
	__u32 flags;
	__u32 resv1;
	__u64 resv2;
पूर्ण;

/*
 * cq_ring->flags
 */

/* disable eventfd notअगरications */
#घोषणा IORING_CQ_EVENTFD_DISABLED	(1U << 0)

/*
 * io_uring_enter(2) flags
 */
#घोषणा IORING_ENTER_GETEVENTS	(1U << 0)
#घोषणा IORING_ENTER_SQ_WAKEUP	(1U << 1)
#घोषणा IORING_ENTER_SQ_WAIT	(1U << 2)
#घोषणा IORING_ENTER_EXT_ARG	(1U << 3)

/*
 * Passed in क्रम io_uring_setup(2). Copied back with updated info on success
 */
काष्ठा io_uring_params अणु
	__u32 sq_entries;
	__u32 cq_entries;
	__u32 flags;
	__u32 sq_thपढ़ो_cpu;
	__u32 sq_thपढ़ो_idle;
	__u32 features;
	__u32 wq_fd;
	__u32 resv[3];
	काष्ठा io_sqring_offsets sq_off;
	काष्ठा io_cqring_offsets cq_off;
पूर्ण;

/*
 * io_uring_params->features flags
 */
#घोषणा IORING_FEAT_SINGLE_MMAP		(1U << 0)
#घोषणा IORING_FEAT_NODROP		(1U << 1)
#घोषणा IORING_FEAT_SUBMIT_STABLE	(1U << 2)
#घोषणा IORING_FEAT_RW_CUR_POS		(1U << 3)
#घोषणा IORING_FEAT_CUR_PERSONALITY	(1U << 4)
#घोषणा IORING_FEAT_FAST_POLL		(1U << 5)
#घोषणा IORING_FEAT_POLL_32BITS 	(1U << 6)
#घोषणा IORING_FEAT_SQPOLL_NONFIXED	(1U << 7)
#घोषणा IORING_FEAT_EXT_ARG		(1U << 8)
#घोषणा IORING_FEAT_NATIVE_WORKERS	(1U << 9)
#घोषणा IORING_FEAT_RSRC_TAGS		(1U << 10)

/*
 * io_uring_रेजिस्टर(2) opcodes and arguments
 */
क्रमागत अणु
	IORING_REGISTER_BUFFERS			= 0,
	IORING_UNREGISTER_BUFFERS		= 1,
	IORING_REGISTER_खाताS			= 2,
	IORING_UNREGISTER_खाताS			= 3,
	IORING_REGISTER_EVENTFD			= 4,
	IORING_UNREGISTER_EVENTFD		= 5,
	IORING_REGISTER_खाताS_UPDATE		= 6,
	IORING_REGISTER_EVENTFD_ASYNC		= 7,
	IORING_REGISTER_PROBE			= 8,
	IORING_REGISTER_PERSONALITY		= 9,
	IORING_UNREGISTER_PERSONALITY		= 10,
	IORING_REGISTER_RESTRICTIONS		= 11,
	IORING_REGISTER_ENABLE_RINGS		= 12,

	/* extended with tagging */
	IORING_REGISTER_खाताS2			= 13,
	IORING_REGISTER_खाताS_UPDATE2		= 14,
	IORING_REGISTER_BUFFERS2		= 15,
	IORING_REGISTER_BUFFERS_UPDATE		= 16,

	/* this goes last */
	IORING_REGISTER_LAST
पूर्ण;

/* deprecated, see काष्ठा io_uring_rsrc_update */
काष्ठा io_uring_files_update अणु
	__u32 offset;
	__u32 resv;
	__aligned_u64 /* __s32 * */ fds;
पूर्ण;

काष्ठा io_uring_rsrc_रेजिस्टर अणु
	__u32 nr;
	__u32 resv;
	__u64 resv2;
	__aligned_u64 data;
	__aligned_u64 tags;
पूर्ण;

काष्ठा io_uring_rsrc_update अणु
	__u32 offset;
	__u32 resv;
	__aligned_u64 data;
पूर्ण;

काष्ठा io_uring_rsrc_update2 अणु
	__u32 offset;
	__u32 resv;
	__aligned_u64 data;
	__aligned_u64 tags;
	__u32 nr;
	__u32 resv2;
पूर्ण;

/* Skip updating fd indexes set to this value in the fd table */
#घोषणा IORING_REGISTER_खाताS_SKIP	(-2)

#घोषणा IO_URING_OP_SUPPORTED	(1U << 0)

काष्ठा io_uring_probe_op अणु
	__u8 op;
	__u8 resv;
	__u16 flags;	/* IO_URING_OP_* flags */
	__u32 resv2;
पूर्ण;

काष्ठा io_uring_probe अणु
	__u8 last_op;	/* last opcode supported */
	__u8 ops_len;	/* length of ops[] array below */
	__u16 resv;
	__u32 resv2[3];
	काष्ठा io_uring_probe_op ops[0];
पूर्ण;

काष्ठा io_uring_restriction अणु
	__u16 opcode;
	जोड़ अणु
		__u8 रेजिस्टर_op; /* IORING_RESTRICTION_REGISTER_OP */
		__u8 sqe_op;      /* IORING_RESTRICTION_SQE_OP */
		__u8 sqe_flags;   /* IORING_RESTRICTION_SQE_FLAGS_* */
	पूर्ण;
	__u8 resv;
	__u32 resv2[3];
पूर्ण;

/*
 * io_uring_restriction->opcode values
 */
क्रमागत अणु
	/* Allow an io_uring_रेजिस्टर(2) opcode */
	IORING_RESTRICTION_REGISTER_OP		= 0,

	/* Allow an sqe opcode */
	IORING_RESTRICTION_SQE_OP		= 1,

	/* Allow sqe flags */
	IORING_RESTRICTION_SQE_FLAGS_ALLOWED	= 2,

	/* Require sqe flags (these flags must be set on each submission) */
	IORING_RESTRICTION_SQE_FLAGS_REQUIRED	= 3,

	IORING_RESTRICTION_LAST
पूर्ण;

काष्ठा io_uring_getevents_arg अणु
	__u64	sigmask;
	__u32	sigmask_sz;
	__u32	pad;
	__u64	ts;
पूर्ण;

#पूर्ण_अगर
