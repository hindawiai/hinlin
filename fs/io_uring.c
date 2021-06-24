<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Shared application/kernel submission and completion ring pairs, क्रम
 * supporting fast/efficient IO.
 *
 * A note on the पढ़ो/ग_लिखो ordering memory barriers that are matched between
 * the application and kernel side.
 *
 * After the application पढ़ोs the CQ ring tail, it must use an
 * appropriate smp_rmb() to pair with the smp_wmb() the kernel uses
 * beक्रमe writing the tail (using smp_load_acquire to पढ़ो the tail will
 * करो). It also needs a smp_mb() beक्रमe updating CQ head (ordering the
 * entry load(s) with the head store), pairing with an implicit barrier
 * through a control-dependency in io_get_cqring (smp_store_release to
 * store head will करो). Failure to करो so could lead to पढ़ोing invalid
 * CQ entries.
 *
 * Likewise, the application must use an appropriate smp_wmb() beक्रमe
 * writing the SQ tail (ordering SQ entry stores with the tail store),
 * which pairs with smp_load_acquire in io_get_sqring (smp_store_release
 * to store the tail will करो). And it needs a barrier ordering the SQ
 * head load beक्रमe writing new SQ entries (smp_load_acquire to पढ़ो
 * head will करो).
 *
 * When using the SQ poll thपढ़ो (IORING_SETUP_SQPOLL), the application
 * needs to check the SQ flags क्रम IORING_SQ_NEED_WAKEUP *after*
 * updating the SQ tail; a full memory barrier smp_mb() is needed
 * between.
 *
 * Also see the examples in the liburing library:
 *
 *	git://git.kernel.dk/liburing
 *
 * io_uring also uses READ/WRITE_ONCE() क्रम _any_ store or load that happens
 * from data shared between the kernel and application. This is करोne both
 * क्रम ordering purposes, but also to ensure that once a value is loaded from
 * data that the application could potentially modअगरy, it reमुख्यs stable.
 *
 * Copyright (C) 2018-2019 Jens Axboe
 * Copyright (c) 2018-2019 Christoph Hellwig
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/compat.h>
#समावेश <net/compat.h>
#समावेश <linux/refcount.h>
#समावेश <linux/uपन.स>
#समावेश <linux/bits.h>

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bvec.h>
#समावेश <linux/net.h>
#समावेश <net/sock.h>
#समावेश <net/af_unix.h>
#समावेश <net/scm.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/nospec.h>
#समावेश <linux/sizes.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/namei.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/fadvise.h>
#समावेश <linux/eventpoll.h>
#समावेश <linux/splice.h>
#समावेश <linux/task_work.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/io_uring.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/io_uring.h>

#समावेश <uapi/linux/io_uring.h>

#समावेश "internal.h"
#समावेश "io-wq.h"

#घोषणा IORING_MAX_ENTRIES	32768
#घोषणा IORING_MAX_CQ_ENTRIES	(2 * IORING_MAX_ENTRIES)

/*
 * Shअगरt of 9 is 512 entries, or exactly one page on 64-bit archs
 */
#घोषणा IORING_खाता_TABLE_SHIFT	9
#घोषणा IORING_MAX_खाताS_TABLE	(1U << IORING_खाता_TABLE_SHIFT)
#घोषणा IORING_खाता_TABLE_MASK	(IORING_MAX_खाताS_TABLE - 1)
#घोषणा IORING_MAX_FIXED_खाताS	(64 * IORING_MAX_खाताS_TABLE)
#घोषणा IORING_MAX_RESTRICTIONS	(IORING_RESTRICTION_LAST + \
				 IORING_REGISTER_LAST + IORING_OP_LAST)

#घोषणा IORING_MAX_REG_BUFFERS	(1U << 14)

#घोषणा SQE_VALID_FLAGS	(IOSQE_FIXED_खाता|IOSQE_IO_DRAIN|IOSQE_IO_LINK|	\
				IOSQE_IO_HARDLINK | IOSQE_ASYNC | \
				IOSQE_BUFFER_SELECT)

काष्ठा io_uring अणु
	u32 head ____cacheline_aligned_in_smp;
	u32 tail ____cacheline_aligned_in_smp;
पूर्ण;

/*
 * This data is shared with the application through the mmap at offsets
 * IORING_OFF_SQ_RING and IORING_OFF_CQ_RING.
 *
 * The offsets to the member fields are published through काष्ठा
 * io_sqring_offsets when calling io_uring_setup.
 */
काष्ठा io_rings अणु
	/*
	 * Head and tail offsets पूर्णांकo the ring; the offsets need to be
	 * masked to get valid indices.
	 *
	 * The kernel controls head of the sq ring and the tail of the cq ring,
	 * and the application controls tail of the sq ring and the head of the
	 * cq ring.
	 */
	काष्ठा io_uring		sq, cq;
	/*
	 * Biपंचांगasks to apply to head and tail offsets (स्थिरant, equals
	 * ring_entries - 1)
	 */
	u32			sq_ring_mask, cq_ring_mask;
	/* Ring sizes (स्थिरant, घातer of 2) */
	u32			sq_ring_entries, cq_ring_entries;
	/*
	 * Number of invalid entries dropped by the kernel due to
	 * invalid index stored in array
	 *
	 * Written by the kernel, shouldn't be modअगरied by the
	 * application (i.e. get number of "new events" by comparing to
	 * cached value).
	 *
	 * After a new SQ head value was पढ़ो by the application this
	 * counter includes all submissions that were dropped reaching
	 * the new SQ head (and possibly more).
	 */
	u32			sq_dropped;
	/*
	 * Runसमय SQ flags
	 *
	 * Written by the kernel, shouldn't be modअगरied by the
	 * application.
	 *
	 * The application needs a full memory barrier beक्रमe checking
	 * क्रम IORING_SQ_NEED_WAKEUP after updating the sq tail.
	 */
	u32			sq_flags;
	/*
	 * Runसमय CQ flags
	 *
	 * Written by the application, shouldn't be modअगरied by the
	 * kernel.
	 */
	u32                     cq_flags;
	/*
	 * Number of completion events lost because the queue was full;
	 * this should be aव्योमed by the application by making sure
	 * there are not more requests pending than there is space in
	 * the completion queue.
	 *
	 * Written by the kernel, shouldn't be modअगरied by the
	 * application (i.e. get number of "new events" by comparing to
	 * cached value).
	 *
	 * As completion events come in out of order this counter is not
	 * ordered with any other data.
	 */
	u32			cq_overflow;
	/*
	 * Ring buffer of completion events.
	 *
	 * The kernel ग_लिखोs completion events fresh every समय they are
	 * produced, so the application is allowed to modअगरy pending
	 * entries.
	 */
	काष्ठा io_uring_cqe	cqes[] ____cacheline_aligned_in_smp;
पूर्ण;

क्रमागत io_uring_cmd_flags अणु
	IO_URING_F_NONBLOCK		= 1,
	IO_URING_F_COMPLETE_DEFER	= 2,
पूर्ण;

काष्ठा io_mapped_ubuf अणु
	u64		ubuf;
	u64		ubuf_end;
	अचिन्हित पूर्णांक	nr_bvecs;
	अचिन्हित दीर्घ	acct_pages;
	काष्ठा bio_vec	bvec[];
पूर्ण;

काष्ठा io_ring_ctx;

काष्ठा io_overflow_cqe अणु
	काष्ठा io_uring_cqe cqe;
	काष्ठा list_head list;
पूर्ण;

काष्ठा io_fixed_file अणु
	/* file * with additional FFS_* flags */
	अचिन्हित दीर्घ file_ptr;
पूर्ण;

काष्ठा io_rsrc_put अणु
	काष्ठा list_head list;
	u64 tag;
	जोड़ अणु
		व्योम *rsrc;
		काष्ठा file *file;
		काष्ठा io_mapped_ubuf *buf;
	पूर्ण;
पूर्ण;

काष्ठा io_file_table अणु
	/* two level table */
	काष्ठा io_fixed_file **files;
पूर्ण;

काष्ठा io_rsrc_node अणु
	काष्ठा percpu_ref		refs;
	काष्ठा list_head		node;
	काष्ठा list_head		rsrc_list;
	काष्ठा io_rsrc_data		*rsrc_data;
	काष्ठा llist_node		llist;
	bool				करोne;
पूर्ण;

प्रकार व्योम (rsrc_put_fn)(काष्ठा io_ring_ctx *ctx, काष्ठा io_rsrc_put *prsrc);

काष्ठा io_rsrc_data अणु
	काष्ठा io_ring_ctx		*ctx;

	u64				*tags;
	rsrc_put_fn			*करो_put;
	atomic_t			refs;
	काष्ठा completion		करोne;
	bool				quiesce;
पूर्ण;

काष्ठा io_buffer अणु
	काष्ठा list_head list;
	__u64 addr;
	__u32 len;
	__u16 bid;
पूर्ण;

काष्ठा io_restriction अणु
	DECLARE_BITMAP(रेजिस्टर_op, IORING_REGISTER_LAST);
	DECLARE_BITMAP(sqe_op, IORING_OP_LAST);
	u8 sqe_flags_allowed;
	u8 sqe_flags_required;
	bool रेजिस्टरed;
पूर्ण;

क्रमागत अणु
	IO_SQ_THREAD_SHOULD_STOP = 0,
	IO_SQ_THREAD_SHOULD_PARK,
पूर्ण;

काष्ठा io_sq_data अणु
	refcount_t		refs;
	atomic_t		park_pending;
	काष्ठा mutex		lock;

	/* ctx's that are using this sqd */
	काष्ठा list_head	ctx_list;

	काष्ठा task_काष्ठा	*thपढ़ो;
	काष्ठा रुको_queue_head	रुको;

	अचिन्हित		sq_thपढ़ो_idle;
	पूर्णांक			sq_cpu;
	pid_t			task_pid;
	pid_t			task_tgid;

	अचिन्हित दीर्घ		state;
	काष्ठा completion	निकासed;
	काष्ठा callback_head	*park_task_work;
पूर्ण;

#घोषणा IO_IOPOLL_BATCH			8
#घोषणा IO_COMPL_BATCH			32
#घोषणा IO_REQ_CACHE_SIZE		32
#घोषणा IO_REQ_ALLOC_BATCH		8

काष्ठा io_comp_state अणु
	काष्ठा io_kiocb		*reqs[IO_COMPL_BATCH];
	अचिन्हित पूर्णांक		nr;
	अचिन्हित पूर्णांक		locked_मुक्त_nr;
	/* अंतरभूत/task_work completion list, under ->uring_lock */
	काष्ठा list_head	मुक्त_list;
	/* IRQ completion list, under ->completion_lock */
	काष्ठा list_head	locked_मुक्त_list;
पूर्ण;

काष्ठा io_submit_link अणु
	काष्ठा io_kiocb		*head;
	काष्ठा io_kiocb		*last;
पूर्ण;

काष्ठा io_submit_state अणु
	काष्ठा blk_plug		plug;
	काष्ठा io_submit_link	link;

	/*
	 * io_kiocb alloc cache
	 */
	व्योम			*reqs[IO_REQ_CACHE_SIZE];
	अचिन्हित पूर्णांक		मुक्त_reqs;

	bool			plug_started;

	/*
	 * Batch completion logic
	 */
	काष्ठा io_comp_state	comp;

	/*
	 * File reference cache
	 */
	काष्ठा file		*file;
	अचिन्हित पूर्णांक		fd;
	अचिन्हित पूर्णांक		file_refs;
	अचिन्हित पूर्णांक		ios_left;
पूर्ण;

काष्ठा io_ring_ctx अणु
	काष्ठा अणु
		काष्ठा percpu_ref	refs;
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा अणु
		अचिन्हित पूर्णांक		flags;
		अचिन्हित पूर्णांक		compat: 1;
		अचिन्हित पूर्णांक		drain_next: 1;
		अचिन्हित पूर्णांक		eventfd_async: 1;
		अचिन्हित पूर्णांक		restricted: 1;

		/*
		 * Ring buffer of indices पूर्णांकo array of io_uring_sqe, which is
		 * mmapped by the application using the IORING_OFF_SQES offset.
		 *
		 * This indirection could e.g. be used to assign fixed
		 * io_uring_sqe entries to operations and only submit them to
		 * the queue when needed.
		 *
		 * The kernel modअगरies neither the indices array nor the entries
		 * array.
		 */
		u32			*sq_array;
		अचिन्हित		cached_sq_head;
		अचिन्हित		sq_entries;
		अचिन्हित		sq_mask;
		अचिन्हित		sq_thपढ़ो_idle;
		अचिन्हित		cached_sq_dropped;
		अचिन्हित		cached_cq_overflow;
		अचिन्हित दीर्घ		sq_check_overflow;

		/* hashed buffered ग_लिखो serialization */
		काष्ठा io_wq_hash	*hash_map;

		काष्ठा list_head	defer_list;
		काष्ठा list_head	समयout_list;
		काष्ठा list_head	cq_overflow_list;

		काष्ठा io_uring_sqe	*sq_sqes;
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा अणु
		काष्ठा mutex		uring_lock;
		रुको_queue_head_t	रुको;
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा io_submit_state		submit_state;

	काष्ठा io_rings	*rings;

	/* Only used क्रम accounting purposes */
	काष्ठा mm_काष्ठा	*mm_account;

	स्थिर काष्ठा cred	*sq_creds;	/* cred used क्रम __io_sq_thपढ़ो() */
	काष्ठा io_sq_data	*sq_data;	/* अगर using sq thपढ़ो polling */

	काष्ठा रुको_queue_head	sqo_sq_रुको;
	काष्ठा list_head	sqd_list;

	/*
	 * If used, fixed file set. Writers must ensure that ->refs is dead,
	 * पढ़ोers must ensure that ->refs is alive as दीर्घ as the file* is
	 * used. Only updated through io_uring_रेजिस्टर(2).
	 */
	काष्ठा io_rsrc_data	*file_data;
	काष्ठा io_file_table	file_table;
	अचिन्हित		nr_user_files;

	/* अगर used, fixed mapped user buffers */
	काष्ठा io_rsrc_data	*buf_data;
	अचिन्हित		nr_user_bufs;
	काष्ठा io_mapped_ubuf	**user_bufs;

	काष्ठा user_काष्ठा	*user;

	काष्ठा completion	ref_comp;

#अगर defined(CONFIG_UNIX)
	काष्ठा socket		*ring_sock;
#पूर्ण_अगर

	काष्ठा xarray		io_buffers;

	काष्ठा xarray		personalities;
	u32			pers_next;

	काष्ठा अणु
		अचिन्हित		cached_cq_tail;
		अचिन्हित		cq_entries;
		अचिन्हित		cq_mask;
		atomic_t		cq_समयouts;
		अचिन्हित		cq_last_पंचांग_flush;
		अचिन्हित		cq_extra;
		अचिन्हित दीर्घ		cq_check_overflow;
		काष्ठा रुको_queue_head	cq_रुको;
		काष्ठा fasync_काष्ठा	*cq_fasync;
		काष्ठा eventfd_ctx	*cq_ev_fd;
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा अणु
		spinlock_t		completion_lock;

		/*
		 * ->iopoll_list is रक्षित by the ctx->uring_lock क्रम
		 * io_uring instances that करोn't use IORING_SETUP_SQPOLL.
		 * For SQPOLL, only the single thपढ़ोed io_sq_thपढ़ो() will
		 * manipulate the list, hence no extra locking is needed there.
		 */
		काष्ठा list_head	iopoll_list;
		काष्ठा hlist_head	*cancel_hash;
		अचिन्हित		cancel_hash_bits;
		bool			poll_multi_file;
	पूर्ण ____cacheline_aligned_in_smp;

	काष्ठा delayed_work		rsrc_put_work;
	काष्ठा llist_head		rsrc_put_llist;
	काष्ठा list_head		rsrc_ref_list;
	spinlock_t			rsrc_ref_lock;
	काष्ठा io_rsrc_node		*rsrc_node;
	काष्ठा io_rsrc_node		*rsrc_backup_node;
	काष्ठा io_mapped_ubuf		*dummy_ubuf;

	काष्ठा io_restriction		restrictions;

	/* निकास task_work */
	काष्ठा callback_head		*निकास_task_work;

	/* Keep this last, we करोn't need it क्रम the fast path */
	काष्ठा work_काष्ठा		निकास_work;
	काष्ठा list_head		tctx_list;
पूर्ण;

काष्ठा io_uring_task अणु
	/* submission side */
	काष्ठा xarray		xa;
	काष्ठा रुको_queue_head	रुको;
	स्थिर काष्ठा io_ring_ctx *last;
	काष्ठा io_wq		*io_wq;
	काष्ठा percpu_counter	inflight;
	atomic_t		inflight_tracked;
	atomic_t		in_idle;

	spinlock_t		task_lock;
	काष्ठा io_wq_work_list	task_list;
	अचिन्हित दीर्घ		task_state;
	काष्ठा callback_head	task_work;
पूर्ण;

/*
 * First field must be the file poपूर्णांकer in all the
 * iocb जोड़s! See also 'struct kiocb' in <linux/fs.h>
 */
काष्ठा io_poll_iocb अणु
	काष्ठा file			*file;
	काष्ठा रुको_queue_head		*head;
	__poll_t			events;
	bool				करोne;
	bool				canceled;
	काष्ठा रुको_queue_entry		रुको;
पूर्ण;

काष्ठा io_poll_update अणु
	काष्ठा file			*file;
	u64				old_user_data;
	u64				new_user_data;
	__poll_t			events;
	bool				update_events;
	bool				update_user_data;
पूर्ण;

काष्ठा io_बंद अणु
	काष्ठा file			*file;
	पूर्णांक				fd;
पूर्ण;

काष्ठा io_समयout_data अणु
	काष्ठा io_kiocb			*req;
	काष्ठा hrसमयr			समयr;
	काष्ठा बारpec64		ts;
	क्रमागत hrसमयr_mode		mode;
पूर्ण;

काष्ठा io_accept अणु
	काष्ठा file			*file;
	काष्ठा sockaddr __user		*addr;
	पूर्णांक __user			*addr_len;
	पूर्णांक				flags;
	अचिन्हित दीर्घ			nofile;
पूर्ण;

काष्ठा io_sync अणु
	काष्ठा file			*file;
	loff_t				len;
	loff_t				off;
	पूर्णांक				flags;
	पूर्णांक				mode;
पूर्ण;

काष्ठा io_cancel अणु
	काष्ठा file			*file;
	u64				addr;
पूर्ण;

काष्ठा io_समयout अणु
	काष्ठा file			*file;
	u32				off;
	u32				target_seq;
	काष्ठा list_head		list;
	/* head of the link, used by linked समयouts only */
	काष्ठा io_kiocb			*head;
पूर्ण;

काष्ठा io_समयout_rem अणु
	काष्ठा file			*file;
	u64				addr;

	/* समयout update */
	काष्ठा बारpec64		ts;
	u32				flags;
पूर्ण;

काष्ठा io_rw अणु
	/* NOTE: kiocb has the file as the first member, so करोn't करो it here */
	काष्ठा kiocb			kiocb;
	u64				addr;
	u64				len;
पूर्ण;

काष्ठा io_connect अणु
	काष्ठा file			*file;
	काष्ठा sockaddr __user		*addr;
	पूर्णांक				addr_len;
पूर्ण;

काष्ठा io_sr_msg अणु
	काष्ठा file			*file;
	जोड़ अणु
		काष्ठा compat_msghdr __user	*umsg_compat;
		काष्ठा user_msghdr __user	*umsg;
		व्योम __user			*buf;
	पूर्ण;
	पूर्णांक				msg_flags;
	पूर्णांक				bgid;
	माप_प्रकार				len;
	काष्ठा io_buffer		*kbuf;
पूर्ण;

काष्ठा io_खोलो अणु
	काष्ठा file			*file;
	पूर्णांक				dfd;
	काष्ठा filename			*filename;
	काष्ठा खोलो_how			how;
	अचिन्हित दीर्घ			nofile;
पूर्ण;

काष्ठा io_rsrc_update अणु
	काष्ठा file			*file;
	u64				arg;
	u32				nr_args;
	u32				offset;
पूर्ण;

काष्ठा io_fadvise अणु
	काष्ठा file			*file;
	u64				offset;
	u32				len;
	u32				advice;
पूर्ण;

काष्ठा io_madvise अणु
	काष्ठा file			*file;
	u64				addr;
	u32				len;
	u32				advice;
पूर्ण;

काष्ठा io_epoll अणु
	काष्ठा file			*file;
	पूर्णांक				epfd;
	पूर्णांक				op;
	पूर्णांक				fd;
	काष्ठा epoll_event		event;
पूर्ण;

काष्ठा io_splice अणु
	काष्ठा file			*file_out;
	काष्ठा file			*file_in;
	loff_t				off_out;
	loff_t				off_in;
	u64				len;
	अचिन्हित पूर्णांक			flags;
पूर्ण;

काष्ठा io_provide_buf अणु
	काष्ठा file			*file;
	__u64				addr;
	__u32				len;
	__u32				bgid;
	__u16				nbufs;
	__u16				bid;
पूर्ण;

काष्ठा io_statx अणु
	काष्ठा file			*file;
	पूर्णांक				dfd;
	अचिन्हित पूर्णांक			mask;
	अचिन्हित पूर्णांक			flags;
	स्थिर अक्षर __user		*filename;
	काष्ठा statx __user		*buffer;
पूर्ण;

काष्ठा io_shutकरोwn अणु
	काष्ठा file			*file;
	पूर्णांक				how;
पूर्ण;

काष्ठा io_नाम अणु
	काष्ठा file			*file;
	पूर्णांक				old_dfd;
	पूर्णांक				new_dfd;
	काष्ठा filename			*oldpath;
	काष्ठा filename			*newpath;
	पूर्णांक				flags;
पूर्ण;

काष्ठा io_unlink अणु
	काष्ठा file			*file;
	पूर्णांक				dfd;
	पूर्णांक				flags;
	काष्ठा filename			*filename;
पूर्ण;

काष्ठा io_completion अणु
	काष्ठा file			*file;
	काष्ठा list_head		list;
	u32				cflags;
पूर्ण;

काष्ठा io_async_connect अणु
	काष्ठा sockaddr_storage		address;
पूर्ण;

काष्ठा io_async_msghdr अणु
	काष्ठा iovec			fast_iov[UIO_FASTIOV];
	/* poपूर्णांकs to an allocated iov, अगर शून्य we use fast_iov instead */
	काष्ठा iovec			*मुक्त_iov;
	काष्ठा sockaddr __user		*uaddr;
	काष्ठा msghdr			msg;
	काष्ठा sockaddr_storage		addr;
पूर्ण;

काष्ठा io_async_rw अणु
	काष्ठा iovec			fast_iov[UIO_FASTIOV];
	स्थिर काष्ठा iovec		*मुक्त_iovec;
	काष्ठा iov_iter			iter;
	माप_प्रकार				bytes_करोne;
	काष्ठा रुको_page_queue		wpq;
पूर्ण;

क्रमागत अणु
	REQ_F_FIXED_खाता_BIT	= IOSQE_FIXED_खाता_BIT,
	REQ_F_IO_DRAIN_BIT	= IOSQE_IO_DRAIN_BIT,
	REQ_F_LINK_BIT		= IOSQE_IO_LINK_BIT,
	REQ_F_HARDLINK_BIT	= IOSQE_IO_HARDLINK_BIT,
	REQ_F_FORCE_ASYNC_BIT	= IOSQE_ASYNC_BIT,
	REQ_F_BUFFER_SELECT_BIT	= IOSQE_BUFFER_SELECT_BIT,

	/* first byte is taken by user flags, shअगरt it to not overlap */
	REQ_F_FAIL_LINK_BIT	= 8,
	REQ_F_INFLIGHT_BIT,
	REQ_F_CUR_POS_BIT,
	REQ_F_NOWAIT_BIT,
	REQ_F_LINK_TIMEOUT_BIT,
	REQ_F_NEED_CLEANUP_BIT,
	REQ_F_POLLED_BIT,
	REQ_F_BUFFER_SELECTED_BIT,
	REQ_F_LTIMEOUT_ACTIVE_BIT,
	REQ_F_COMPLETE_INLINE_BIT,
	REQ_F_REISSUE_BIT,
	REQ_F_DONT_REISSUE_BIT,
	/* keep async पढ़ो/ग_लिखो and isreg together and in order */
	REQ_F_ASYNC_READ_BIT,
	REQ_F_ASYNC_WRITE_BIT,
	REQ_F_ISREG_BIT,

	/* not a real bit, just to check we're not overflowing the space */
	__REQ_F_LAST_BIT,
पूर्ण;

क्रमागत अणु
	/* ctx owns file */
	REQ_F_FIXED_खाता	= BIT(REQ_F_FIXED_खाता_BIT),
	/* drain existing IO first */
	REQ_F_IO_DRAIN		= BIT(REQ_F_IO_DRAIN_BIT),
	/* linked sqes */
	REQ_F_LINK		= BIT(REQ_F_LINK_BIT),
	/* करोesn't sever on completion < 0 */
	REQ_F_HARDLINK		= BIT(REQ_F_HARDLINK_BIT),
	/* IOSQE_ASYNC */
	REQ_F_FORCE_ASYNC	= BIT(REQ_F_FORCE_ASYNC_BIT),
	/* IOSQE_BUFFER_SELECT */
	REQ_F_BUFFER_SELECT	= BIT(REQ_F_BUFFER_SELECT_BIT),

	/* fail rest of links */
	REQ_F_FAIL_LINK		= BIT(REQ_F_FAIL_LINK_BIT),
	/* on inflight list, should be cancelled and रुकोed on निकास reliably */
	REQ_F_INFLIGHT		= BIT(REQ_F_INFLIGHT_BIT),
	/* पढ़ो/ग_लिखो uses file position */
	REQ_F_CUR_POS		= BIT(REQ_F_CUR_POS_BIT),
	/* must not punt to workers */
	REQ_F_NOWAIT		= BIT(REQ_F_NOWAIT_BIT),
	/* has or had linked समयout */
	REQ_F_LINK_TIMEOUT	= BIT(REQ_F_LINK_TIMEOUT_BIT),
	/* needs cleanup */
	REQ_F_NEED_CLEANUP	= BIT(REQ_F_NEED_CLEANUP_BIT),
	/* alपढ़ोy went through poll handler */
	REQ_F_POLLED		= BIT(REQ_F_POLLED_BIT),
	/* buffer alपढ़ोy selected */
	REQ_F_BUFFER_SELECTED	= BIT(REQ_F_BUFFER_SELECTED_BIT),
	/* linked समयout is active, i.e. prepared by link's head */
	REQ_F_LTIMEOUT_ACTIVE	= BIT(REQ_F_LTIMEOUT_ACTIVE_BIT),
	/* completion is deferred through io_comp_state */
	REQ_F_COMPLETE_INLINE	= BIT(REQ_F_COMPLETE_INLINE_BIT),
	/* caller should reissue async */
	REQ_F_REISSUE		= BIT(REQ_F_REISSUE_BIT),
	/* करोn't attempt request reissue, see io_rw_reissue() */
	REQ_F_DONT_REISSUE	= BIT(REQ_F_DONT_REISSUE_BIT),
	/* supports async पढ़ोs */
	REQ_F_ASYNC_READ	= BIT(REQ_F_ASYNC_READ_BIT),
	/* supports async ग_लिखोs */
	REQ_F_ASYNC_WRITE	= BIT(REQ_F_ASYNC_WRITE_BIT),
	/* regular file */
	REQ_F_ISREG		= BIT(REQ_F_ISREG_BIT),
पूर्ण;

काष्ठा async_poll अणु
	काष्ठा io_poll_iocb	poll;
	काष्ठा io_poll_iocb	*द्विगुन_poll;
पूर्ण;

काष्ठा io_task_work अणु
	काष्ठा io_wq_work_node	node;
	task_work_func_t	func;
पूर्ण;

क्रमागत अणु
	IORING_RSRC_खाता		= 0,
	IORING_RSRC_BUFFER		= 1,
पूर्ण;

/*
 * NOTE! Each of the iocb जोड़ members has the file poपूर्णांकer
 * as the first entry in their काष्ठा definition. So you can
 * access the file poपूर्णांकer through any of the sub-काष्ठाs,
 * or directly as just 'ki_filp' in this काष्ठा.
 */
काष्ठा io_kiocb अणु
	जोड़ अणु
		काष्ठा file		*file;
		काष्ठा io_rw		rw;
		काष्ठा io_poll_iocb	poll;
		काष्ठा io_poll_update	poll_update;
		काष्ठा io_accept	accept;
		काष्ठा io_sync		sync;
		काष्ठा io_cancel	cancel;
		काष्ठा io_समयout	समयout;
		काष्ठा io_समयout_rem	समयout_rem;
		काष्ठा io_connect	connect;
		काष्ठा io_sr_msg	sr_msg;
		काष्ठा io_खोलो		खोलो;
		काष्ठा io_बंद		बंद;
		काष्ठा io_rsrc_update	rsrc_update;
		काष्ठा io_fadvise	fadvise;
		काष्ठा io_madvise	madvise;
		काष्ठा io_epoll		epoll;
		काष्ठा io_splice	splice;
		काष्ठा io_provide_buf	pbuf;
		काष्ठा io_statx		statx;
		काष्ठा io_shutकरोwn	shutकरोwn;
		काष्ठा io_नाम	नाम;
		काष्ठा io_unlink	unlink;
		/* use only after cleaning per-op data, see io_clean_op() */
		काष्ठा io_completion	compl;
	पूर्ण;

	/* opcode allocated अगर it needs to store data क्रम async defer */
	व्योम				*async_data;
	u8				opcode;
	/* polled IO has completed */
	u8				iopoll_completed;

	u16				buf_index;
	u32				result;

	काष्ठा io_ring_ctx		*ctx;
	अचिन्हित पूर्णांक			flags;
	atomic_t			refs;
	काष्ठा task_काष्ठा		*task;
	u64				user_data;

	काष्ठा io_kiocb			*link;
	काष्ठा percpu_ref		*fixed_rsrc_refs;

	/* used with ctx->iopoll_list with पढ़ोs/ग_लिखोs */
	काष्ठा list_head		inflight_entry;
	जोड़ अणु
		काष्ठा io_task_work	io_task_work;
		काष्ठा callback_head	task_work;
	पूर्ण;
	/* क्रम polled requests, i.e. IORING_OP_POLL_ADD and async armed poll */
	काष्ठा hlist_node		hash_node;
	काष्ठा async_poll		*apoll;
	काष्ठा io_wq_work		work;
	/* store used ubuf, so we can prevent reloading */
	काष्ठा io_mapped_ubuf		*imu;
पूर्ण;

काष्ठा io_tctx_node अणु
	काष्ठा list_head	ctx_node;
	काष्ठा task_काष्ठा	*task;
	काष्ठा io_ring_ctx	*ctx;
पूर्ण;

काष्ठा io_defer_entry अणु
	काष्ठा list_head	list;
	काष्ठा io_kiocb		*req;
	u32			seq;
पूर्ण;

काष्ठा io_op_def अणु
	/* needs req->file asचिन्हित */
	अचिन्हित		needs_file : 1;
	/* hash wq insertion अगर file is a regular file */
	अचिन्हित		hash_reg_file : 1;
	/* unbound wq insertion अगर file is a non-regular file */
	अचिन्हित		unbound_nonreg_file : 1;
	/* opcode is not supported by this kernel */
	अचिन्हित		not_supported : 1;
	/* set अगर opcode supports polled "wait" */
	अचिन्हित		pollin : 1;
	अचिन्हित		pollout : 1;
	/* op supports buffer selection */
	अचिन्हित		buffer_select : 1;
	/* करो prep async अगर is going to be punted */
	अचिन्हित		needs_async_setup : 1;
	/* should block plug */
	अचिन्हित		plug : 1;
	/* size of async data needed, अगर any */
	अचिन्हित लघु		async_size;
पूर्ण;

अटल स्थिर काष्ठा io_op_def io_op_defs[] = अणु
	[IORING_OP_NOP] = अणुपूर्ण,
	[IORING_OP_READV] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollin			= 1,
		.buffer_select		= 1,
		.needs_async_setup	= 1,
		.plug			= 1,
		.async_size		= माप(काष्ठा io_async_rw),
	पूर्ण,
	[IORING_OP_WRITEV] = अणु
		.needs_file		= 1,
		.hash_reg_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollout		= 1,
		.needs_async_setup	= 1,
		.plug			= 1,
		.async_size		= माप(काष्ठा io_async_rw),
	पूर्ण,
	[IORING_OP_FSYNC] = अणु
		.needs_file		= 1,
	पूर्ण,
	[IORING_OP_READ_FIXED] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollin			= 1,
		.plug			= 1,
		.async_size		= माप(काष्ठा io_async_rw),
	पूर्ण,
	[IORING_OP_WRITE_FIXED] = अणु
		.needs_file		= 1,
		.hash_reg_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollout		= 1,
		.plug			= 1,
		.async_size		= माप(काष्ठा io_async_rw),
	पूर्ण,
	[IORING_OP_POLL_ADD] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
	पूर्ण,
	[IORING_OP_POLL_REMOVE] = अणुपूर्ण,
	[IORING_OP_SYNC_खाता_RANGE] = अणु
		.needs_file		= 1,
	पूर्ण,
	[IORING_OP_SENDMSG] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollout		= 1,
		.needs_async_setup	= 1,
		.async_size		= माप(काष्ठा io_async_msghdr),
	पूर्ण,
	[IORING_OP_RECVMSG] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollin			= 1,
		.buffer_select		= 1,
		.needs_async_setup	= 1,
		.async_size		= माप(काष्ठा io_async_msghdr),
	पूर्ण,
	[IORING_OP_TIMEOUT] = अणु
		.async_size		= माप(काष्ठा io_समयout_data),
	पूर्ण,
	[IORING_OP_TIMEOUT_REMOVE] = अणु
		/* used by समयout updates' prep() */
	पूर्ण,
	[IORING_OP_ACCEPT] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollin			= 1,
	पूर्ण,
	[IORING_OP_ASYNC_CANCEL] = अणुपूर्ण,
	[IORING_OP_LINK_TIMEOUT] = अणु
		.async_size		= माप(काष्ठा io_समयout_data),
	पूर्ण,
	[IORING_OP_CONNECT] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollout		= 1,
		.needs_async_setup	= 1,
		.async_size		= माप(काष्ठा io_async_connect),
	पूर्ण,
	[IORING_OP_FALLOCATE] = अणु
		.needs_file		= 1,
	पूर्ण,
	[IORING_OP_OPENAT] = अणुपूर्ण,
	[IORING_OP_CLOSE] = अणुपूर्ण,
	[IORING_OP_खाताS_UPDATE] = अणुपूर्ण,
	[IORING_OP_STATX] = अणुपूर्ण,
	[IORING_OP_READ] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollin			= 1,
		.buffer_select		= 1,
		.plug			= 1,
		.async_size		= माप(काष्ठा io_async_rw),
	पूर्ण,
	[IORING_OP_WRITE] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollout		= 1,
		.plug			= 1,
		.async_size		= माप(काष्ठा io_async_rw),
	पूर्ण,
	[IORING_OP_FADVISE] = अणु
		.needs_file		= 1,
	पूर्ण,
	[IORING_OP_MADVISE] = अणुपूर्ण,
	[IORING_OP_SEND] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollout		= 1,
	पूर्ण,
	[IORING_OP_RECV] = अणु
		.needs_file		= 1,
		.unbound_nonreg_file	= 1,
		.pollin			= 1,
		.buffer_select		= 1,
	पूर्ण,
	[IORING_OP_OPENAT2] = अणु
	पूर्ण,
	[IORING_OP_EPOLL_CTL] = अणु
		.unbound_nonreg_file	= 1,
	पूर्ण,
	[IORING_OP_SPLICE] = अणु
		.needs_file		= 1,
		.hash_reg_file		= 1,
		.unbound_nonreg_file	= 1,
	पूर्ण,
	[IORING_OP_PROVIDE_BUFFERS] = अणुपूर्ण,
	[IORING_OP_REMOVE_BUFFERS] = अणुपूर्ण,
	[IORING_OP_TEE] = अणु
		.needs_file		= 1,
		.hash_reg_file		= 1,
		.unbound_nonreg_file	= 1,
	पूर्ण,
	[IORING_OP_SHUTDOWN] = अणु
		.needs_file		= 1,
	पूर्ण,
	[IORING_OP_RENAMEAT] = अणुपूर्ण,
	[IORING_OP_UNLINKAT] = अणुपूर्ण,
पूर्ण;

अटल bool io_disarm_next(काष्ठा io_kiocb *req);
अटल व्योम io_uring_del_task_file(अचिन्हित दीर्घ index);
अटल व्योम io_uring_try_cancel_requests(काष्ठा io_ring_ctx *ctx,
					 काष्ठा task_काष्ठा *task,
					 काष्ठा files_काष्ठा *files);
अटल व्योम io_uring_cancel_sqpoll(काष्ठा io_sq_data *sqd);
अटल काष्ठा io_rsrc_node *io_rsrc_node_alloc(काष्ठा io_ring_ctx *ctx);

अटल bool io_cqring_fill_event(काष्ठा io_ring_ctx *ctx, u64 user_data,
				 दीर्घ res, अचिन्हित पूर्णांक cflags);
अटल व्योम io_put_req(काष्ठा io_kiocb *req);
अटल व्योम io_put_req_deferred(काष्ठा io_kiocb *req, पूर्णांक nr);
अटल व्योम io_dismantle_req(काष्ठा io_kiocb *req);
अटल व्योम io_put_task(काष्ठा task_काष्ठा *task, पूर्णांक nr);
अटल काष्ठा io_kiocb *io_prep_linked_समयout(काष्ठा io_kiocb *req);
अटल व्योम io_queue_linked_समयout(काष्ठा io_kiocb *req);
अटल पूर्णांक __io_रेजिस्टर_rsrc_update(काष्ठा io_ring_ctx *ctx, अचिन्हित type,
				     काष्ठा io_uring_rsrc_update2 *up,
				     अचिन्हित nr_args);
अटल व्योम io_clean_op(काष्ठा io_kiocb *req);
अटल काष्ठा file *io_file_get(काष्ठा io_submit_state *state,
				काष्ठा io_kiocb *req, पूर्णांक fd, bool fixed);
अटल व्योम __io_queue_sqe(काष्ठा io_kiocb *req);
अटल व्योम io_rsrc_put_work(काष्ठा work_काष्ठा *work);

अटल व्योम io_req_task_queue(काष्ठा io_kiocb *req);
अटल व्योम io_submit_flush_completions(काष्ठा io_comp_state *cs,
					काष्ठा io_ring_ctx *ctx);
अटल bool io_poll_हटाओ_रुकोqs(काष्ठा io_kiocb *req);
अटल पूर्णांक io_req_prep_async(काष्ठा io_kiocb *req);

अटल काष्ठा kmem_cache *req_cachep;

अटल स्थिर काष्ठा file_operations io_uring_fops;

काष्ठा sock *io_uring_get_socket(काष्ठा file *file)
अणु
#अगर defined(CONFIG_UNIX)
	अगर (file->f_op == &io_uring_fops) अणु
		काष्ठा io_ring_ctx *ctx = file->निजी_data;

		वापस ctx->ring_sock->sk;
	पूर्ण
#पूर्ण_अगर
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(io_uring_get_socket);

#घोषणा io_क्रम_each_link(pos, head) \
	क्रम (pos = (head); pos; pos = pos->link)

अटल अंतरभूत व्योम io_req_set_rsrc_node(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	अगर (!req->fixed_rsrc_refs) अणु
		req->fixed_rsrc_refs = &ctx->rsrc_node->refs;
		percpu_ref_get(req->fixed_rsrc_refs);
	पूर्ण
पूर्ण

अटल व्योम io_refs_resurrect(काष्ठा percpu_ref *ref, काष्ठा completion *compl)
अणु
	bool got = percpu_ref_tryget(ref);

	/* alपढ़ोy at zero, रुको क्रम ->release() */
	अगर (!got)
		रुको_क्रम_completion(compl);
	percpu_ref_resurrect(ref);
	अगर (got)
		percpu_ref_put(ref);
पूर्ण

अटल bool io_match_task(काष्ठा io_kiocb *head,
			  काष्ठा task_काष्ठा *task,
			  काष्ठा files_काष्ठा *files)
अणु
	काष्ठा io_kiocb *req;

	अगर (task && head->task != task)
		वापस false;
	अगर (!files)
		वापस true;

	io_क्रम_each_link(req, head) अणु
		अगर (req->flags & REQ_F_INFLIGHT)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम req_set_fail_links(काष्ठा io_kiocb *req)
अणु
	अगर (req->flags & REQ_F_LINK)
		req->flags |= REQ_F_FAIL_LINK;
पूर्ण

अटल व्योम io_ring_ctx_ref_मुक्त(काष्ठा percpu_ref *ref)
अणु
	काष्ठा io_ring_ctx *ctx = container_of(ref, काष्ठा io_ring_ctx, refs);

	complete(&ctx->ref_comp);
पूर्ण

अटल अंतरभूत bool io_is_समयout_noseq(काष्ठा io_kiocb *req)
अणु
	वापस !req->समयout.off;
पूर्ण

अटल काष्ठा io_ring_ctx *io_ring_ctx_alloc(काष्ठा io_uring_params *p)
अणु
	काष्ठा io_ring_ctx *ctx;
	पूर्णांक hash_bits;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	/*
	 * Use 5 bits less than the max cq entries, that should give us around
	 * 32 entries per hash list अगर totally full and unअगरormly spपढ़ो.
	 */
	hash_bits = ilog2(p->cq_entries);
	hash_bits -= 5;
	अगर (hash_bits <= 0)
		hash_bits = 1;
	ctx->cancel_hash_bits = hash_bits;
	ctx->cancel_hash = kदो_स्मृति((1U << hash_bits) * माप(काष्ठा hlist_head),
					GFP_KERNEL);
	अगर (!ctx->cancel_hash)
		जाओ err;
	__hash_init(ctx->cancel_hash, 1U << hash_bits);

	ctx->dummy_ubuf = kzalloc(माप(*ctx->dummy_ubuf), GFP_KERNEL);
	अगर (!ctx->dummy_ubuf)
		जाओ err;
	/* set invalid range, so io_import_fixed() fails meeting it */
	ctx->dummy_ubuf->ubuf = -1UL;

	अगर (percpu_ref_init(&ctx->refs, io_ring_ctx_ref_मुक्त,
			    PERCPU_REF_ALLOW_REINIT, GFP_KERNEL))
		जाओ err;

	ctx->flags = p->flags;
	init_रुकोqueue_head(&ctx->sqo_sq_रुको);
	INIT_LIST_HEAD(&ctx->sqd_list);
	init_रुकोqueue_head(&ctx->cq_रुको);
	INIT_LIST_HEAD(&ctx->cq_overflow_list);
	init_completion(&ctx->ref_comp);
	xa_init_flags(&ctx->io_buffers, XA_FLAGS_ALLOC1);
	xa_init_flags(&ctx->personalities, XA_FLAGS_ALLOC1);
	mutex_init(&ctx->uring_lock);
	init_रुकोqueue_head(&ctx->रुको);
	spin_lock_init(&ctx->completion_lock);
	INIT_LIST_HEAD(&ctx->iopoll_list);
	INIT_LIST_HEAD(&ctx->defer_list);
	INIT_LIST_HEAD(&ctx->समयout_list);
	spin_lock_init(&ctx->rsrc_ref_lock);
	INIT_LIST_HEAD(&ctx->rsrc_ref_list);
	INIT_DELAYED_WORK(&ctx->rsrc_put_work, io_rsrc_put_work);
	init_llist_head(&ctx->rsrc_put_llist);
	INIT_LIST_HEAD(&ctx->tctx_list);
	INIT_LIST_HEAD(&ctx->submit_state.comp.मुक्त_list);
	INIT_LIST_HEAD(&ctx->submit_state.comp.locked_मुक्त_list);
	वापस ctx;
err:
	kमुक्त(ctx->dummy_ubuf);
	kमुक्त(ctx->cancel_hash);
	kमुक्त(ctx);
	वापस शून्य;
पूर्ण

अटल bool req_need_defer(काष्ठा io_kiocb *req, u32 seq)
अणु
	अगर (unlikely(req->flags & REQ_F_IO_DRAIN)) अणु
		काष्ठा io_ring_ctx *ctx = req->ctx;

		वापस seq + ctx->cq_extra != ctx->cached_cq_tail
				+ READ_ONCE(ctx->cached_cq_overflow);
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम io_req_track_inflight(काष्ठा io_kiocb *req)
अणु
	अगर (!(req->flags & REQ_F_INFLIGHT)) अणु
		req->flags |= REQ_F_INFLIGHT;
		atomic_inc(&current->io_uring->inflight_tracked);
	पूर्ण
पूर्ण

अटल व्योम io_prep_async_work(काष्ठा io_kiocb *req)
अणु
	स्थिर काष्ठा io_op_def *def = &io_op_defs[req->opcode];
	काष्ठा io_ring_ctx *ctx = req->ctx;

	अगर (!req->work.creds)
		req->work.creds = get_current_cred();

	req->work.list.next = शून्य;
	req->work.flags = 0;
	अगर (req->flags & REQ_F_FORCE_ASYNC)
		req->work.flags |= IO_WQ_WORK_CONCURRENT;

	अगर (req->flags & REQ_F_ISREG) अणु
		अगर (def->hash_reg_file || (ctx->flags & IORING_SETUP_IOPOLL))
			io_wq_hash_work(&req->work, file_inode(req->file));
	पूर्ण अन्यथा अगर (!req->file || !S_ISBLK(file_inode(req->file)->i_mode)) अणु
		अगर (def->unbound_nonreg_file)
			req->work.flags |= IO_WQ_WORK_UNBOUND;
	पूर्ण

	चयन (req->opcode) अणु
	हाल IORING_OP_SPLICE:
	हाल IORING_OP_TEE:
		अगर (!S_ISREG(file_inode(req->splice.file_in)->i_mode))
			req->work.flags |= IO_WQ_WORK_UNBOUND;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम io_prep_async_link(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_kiocb *cur;

	io_क्रम_each_link(cur, req)
		io_prep_async_work(cur);
पूर्ण

अटल व्योम io_queue_async_work(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_kiocb *link = io_prep_linked_समयout(req);
	काष्ठा io_uring_task *tctx = req->task->io_uring;

	BUG_ON(!tctx);
	BUG_ON(!tctx->io_wq);

	/* init ->work of the whole link beक्रमe punting */
	io_prep_async_link(req);
	trace_io_uring_queue_async_work(ctx, io_wq_is_hashed(&req->work), req,
					&req->work, req->flags);
	io_wq_enqueue(tctx->io_wq, &req->work);
	अगर (link)
		io_queue_linked_समयout(link);
पूर्ण

अटल व्योम io_समाप्त_समयout(काष्ठा io_kiocb *req, पूर्णांक status)
	__must_hold(&req->ctx->completion_lock)
अणु
	काष्ठा io_समयout_data *io = req->async_data;

	अगर (hrसमयr_try_to_cancel(&io->समयr) != -1) अणु
		atomic_set(&req->ctx->cq_समयouts,
			atomic_पढ़ो(&req->ctx->cq_समयouts) + 1);
		list_del_init(&req->समयout.list);
		io_cqring_fill_event(req->ctx, req->user_data, status, 0);
		io_put_req_deferred(req, 1);
	पूर्ण
पूर्ण

अटल व्योम __io_queue_deferred(काष्ठा io_ring_ctx *ctx)
अणु
	करो अणु
		काष्ठा io_defer_entry *de = list_first_entry(&ctx->defer_list,
						काष्ठा io_defer_entry, list);

		अगर (req_need_defer(de->req, de->seq))
			अवरोध;
		list_del_init(&de->list);
		io_req_task_queue(de->req);
		kमुक्त(de);
	पूर्ण जबतक (!list_empty(&ctx->defer_list));
पूर्ण

अटल व्योम io_flush_समयouts(काष्ठा io_ring_ctx *ctx)
अणु
	u32 seq;

	अगर (list_empty(&ctx->समयout_list))
		वापस;

	seq = ctx->cached_cq_tail - atomic_पढ़ो(&ctx->cq_समयouts);

	करो अणु
		u32 events_needed, events_got;
		काष्ठा io_kiocb *req = list_first_entry(&ctx->समयout_list,
						काष्ठा io_kiocb, समयout.list);

		अगर (io_is_समयout_noseq(req))
			अवरोध;

		/*
		 * Since seq can easily wrap around over समय, subtract
		 * the last seq at which समयouts were flushed beक्रमe comparing.
		 * Assuming not more than 2^31-1 events have happened since,
		 * these subtractions won't have wrapped, so we can check अगर
		 * target is in [last_seq, current_seq] by comparing the two.
		 */
		events_needed = req->समयout.target_seq - ctx->cq_last_पंचांग_flush;
		events_got = seq - ctx->cq_last_पंचांग_flush;
		अगर (events_got < events_needed)
			अवरोध;

		list_del_init(&req->समयout.list);
		io_समाप्त_समयout(req, 0);
	पूर्ण जबतक (!list_empty(&ctx->समयout_list));

	ctx->cq_last_पंचांग_flush = seq;
पूर्ण

अटल व्योम io_commit_cqring(काष्ठा io_ring_ctx *ctx)
अणु
	io_flush_समयouts(ctx);

	/* order cqe stores with ring update */
	smp_store_release(&ctx->rings->cq.tail, ctx->cached_cq_tail);

	अगर (unlikely(!list_empty(&ctx->defer_list)))
		__io_queue_deferred(ctx);
पूर्ण

अटल अंतरभूत bool io_sqring_full(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_rings *r = ctx->rings;

	वापस READ_ONCE(r->sq.tail) - ctx->cached_sq_head == r->sq_ring_entries;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __io_cqring_events(काष्ठा io_ring_ctx *ctx)
अणु
	वापस ctx->cached_cq_tail - READ_ONCE(ctx->rings->cq.head);
पूर्ण

अटल अंतरभूत काष्ठा io_uring_cqe *io_get_cqring(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_rings *rings = ctx->rings;
	अचिन्हित tail;

	/*
	 * ग_लिखोs to the cq entry need to come after पढ़ोing head; the
	 * control dependency is enough as we're using WRITE_ONCE to
	 * fill the cq entry
	 */
	अगर (__io_cqring_events(ctx) == rings->cq_ring_entries)
		वापस शून्य;

	tail = ctx->cached_cq_tail++;
	वापस &rings->cqes[tail & ctx->cq_mask];
पूर्ण

अटल अंतरभूत bool io_should_trigger_evfd(काष्ठा io_ring_ctx *ctx)
अणु
	अगर (likely(!ctx->cq_ev_fd))
		वापस false;
	अगर (READ_ONCE(ctx->rings->cq_flags) & IORING_CQ_EVENTFD_DISABLED)
		वापस false;
	वापस !ctx->eventfd_async || io_wq_current_is_worker();
पूर्ण

अटल व्योम io_cqring_ev_posted(काष्ठा io_ring_ctx *ctx)
अणु
	/* see रुकोqueue_active() comment */
	smp_mb();

	अगर (रुकोqueue_active(&ctx->रुको))
		wake_up(&ctx->रुको);
	अगर (ctx->sq_data && रुकोqueue_active(&ctx->sq_data->रुको))
		wake_up(&ctx->sq_data->रुको);
	अगर (io_should_trigger_evfd(ctx))
		eventfd_संकेत(ctx->cq_ev_fd, 1);
	अगर (रुकोqueue_active(&ctx->cq_रुको)) अणु
		wake_up_पूर्णांकerruptible(&ctx->cq_रुको);
		समाप्त_fasync(&ctx->cq_fasync, SIGIO, POLL_IN);
	पूर्ण
पूर्ण

अटल व्योम io_cqring_ev_posted_iopoll(काष्ठा io_ring_ctx *ctx)
अणु
	/* see रुकोqueue_active() comment */
	smp_mb();

	अगर (ctx->flags & IORING_SETUP_SQPOLL) अणु
		अगर (रुकोqueue_active(&ctx->रुको))
			wake_up(&ctx->रुको);
	पूर्ण
	अगर (io_should_trigger_evfd(ctx))
		eventfd_संकेत(ctx->cq_ev_fd, 1);
	अगर (रुकोqueue_active(&ctx->cq_रुको)) अणु
		wake_up_पूर्णांकerruptible(&ctx->cq_रुको);
		समाप्त_fasync(&ctx->cq_fasync, SIGIO, POLL_IN);
	पूर्ण
पूर्ण

/* Returns true अगर there are no backlogged entries after the flush */
अटल bool __io_cqring_overflow_flush(काष्ठा io_ring_ctx *ctx, bool क्रमce)
अणु
	काष्ठा io_rings *rings = ctx->rings;
	अचिन्हित दीर्घ flags;
	bool all_flushed, posted;

	अगर (!क्रमce && __io_cqring_events(ctx) == rings->cq_ring_entries)
		वापस false;

	posted = false;
	spin_lock_irqsave(&ctx->completion_lock, flags);
	जबतक (!list_empty(&ctx->cq_overflow_list)) अणु
		काष्ठा io_uring_cqe *cqe = io_get_cqring(ctx);
		काष्ठा io_overflow_cqe *ocqe;

		अगर (!cqe && !क्रमce)
			अवरोध;
		ocqe = list_first_entry(&ctx->cq_overflow_list,
					काष्ठा io_overflow_cqe, list);
		अगर (cqe)
			स_नकल(cqe, &ocqe->cqe, माप(*cqe));
		अन्यथा
			WRITE_ONCE(ctx->rings->cq_overflow,
				   ++ctx->cached_cq_overflow);
		posted = true;
		list_del(&ocqe->list);
		kमुक्त(ocqe);
	पूर्ण

	all_flushed = list_empty(&ctx->cq_overflow_list);
	अगर (all_flushed) अणु
		clear_bit(0, &ctx->sq_check_overflow);
		clear_bit(0, &ctx->cq_check_overflow);
		ctx->rings->sq_flags &= ~IORING_SQ_CQ_OVERFLOW;
	पूर्ण

	अगर (posted)
		io_commit_cqring(ctx);
	spin_unlock_irqrestore(&ctx->completion_lock, flags);
	अगर (posted)
		io_cqring_ev_posted(ctx);
	वापस all_flushed;
पूर्ण

अटल bool io_cqring_overflow_flush(काष्ठा io_ring_ctx *ctx, bool क्रमce)
अणु
	bool ret = true;

	अगर (test_bit(0, &ctx->cq_check_overflow)) अणु
		/* iopoll syncs against uring_lock, not completion_lock */
		अगर (ctx->flags & IORING_SETUP_IOPOLL)
			mutex_lock(&ctx->uring_lock);
		ret = __io_cqring_overflow_flush(ctx, क्रमce);
		अगर (ctx->flags & IORING_SETUP_IOPOLL)
			mutex_unlock(&ctx->uring_lock);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Shamelessly stolen from the mm implementation of page reference checking,
 * see commit f958d7b528b1 क्रम details.
 */
#घोषणा req_ref_zero_or_बंद_to_overflow(req)	\
	((अचिन्हित पूर्णांक) atomic_पढ़ो(&(req->refs)) + 127u <= 127u)

अटल अंतरभूत bool req_ref_inc_not_zero(काष्ठा io_kiocb *req)
अणु
	वापस atomic_inc_not_zero(&req->refs);
पूर्ण

अटल अंतरभूत bool req_ref_sub_and_test(काष्ठा io_kiocb *req, पूर्णांक refs)
अणु
	WARN_ON_ONCE(req_ref_zero_or_बंद_to_overflow(req));
	वापस atomic_sub_and_test(refs, &req->refs);
पूर्ण

अटल अंतरभूत bool req_ref_put_and_test(काष्ठा io_kiocb *req)
अणु
	WARN_ON_ONCE(req_ref_zero_or_बंद_to_overflow(req));
	वापस atomic_dec_and_test(&req->refs);
पूर्ण

अटल अंतरभूत व्योम req_ref_put(काष्ठा io_kiocb *req)
अणु
	WARN_ON_ONCE(req_ref_put_and_test(req));
पूर्ण

अटल अंतरभूत व्योम req_ref_get(काष्ठा io_kiocb *req)
अणु
	WARN_ON_ONCE(req_ref_zero_or_बंद_to_overflow(req));
	atomic_inc(&req->refs);
पूर्ण

अटल bool io_cqring_event_overflow(काष्ठा io_ring_ctx *ctx, u64 user_data,
				     दीर्घ res, अचिन्हित पूर्णांक cflags)
अणु
	काष्ठा io_overflow_cqe *ocqe;

	ocqe = kदो_स्मृति(माप(*ocqe), GFP_ATOMIC | __GFP_ACCOUNT);
	अगर (!ocqe) अणु
		/*
		 * If we're in ring overflow flush mode, or in task cancel mode,
		 * or cannot allocate an overflow entry, then we need to drop it
		 * on the न्यूनमान.
		 */
		WRITE_ONCE(ctx->rings->cq_overflow, ++ctx->cached_cq_overflow);
		वापस false;
	पूर्ण
	अगर (list_empty(&ctx->cq_overflow_list)) अणु
		set_bit(0, &ctx->sq_check_overflow);
		set_bit(0, &ctx->cq_check_overflow);
		ctx->rings->sq_flags |= IORING_SQ_CQ_OVERFLOW;
	पूर्ण
	ocqe->cqe.user_data = user_data;
	ocqe->cqe.res = res;
	ocqe->cqe.flags = cflags;
	list_add_tail(&ocqe->list, &ctx->cq_overflow_list);
	वापस true;
पूर्ण

अटल अंतरभूत bool __io_cqring_fill_event(काष्ठा io_ring_ctx *ctx, u64 user_data,
					  दीर्घ res, अचिन्हित पूर्णांक cflags)
अणु
	काष्ठा io_uring_cqe *cqe;

	trace_io_uring_complete(ctx, user_data, res, cflags);

	/*
	 * If we can't get a cq entry, userspace overflowed the
	 * submission (by quite a lot). Increment the overflow count in
	 * the ring.
	 */
	cqe = io_get_cqring(ctx);
	अगर (likely(cqe)) अणु
		WRITE_ONCE(cqe->user_data, user_data);
		WRITE_ONCE(cqe->res, res);
		WRITE_ONCE(cqe->flags, cflags);
		वापस true;
	पूर्ण
	वापस io_cqring_event_overflow(ctx, user_data, res, cflags);
पूर्ण

/* not as hot to bloat with inlining */
अटल noअंतरभूत bool io_cqring_fill_event(काष्ठा io_ring_ctx *ctx, u64 user_data,
					  दीर्घ res, अचिन्हित पूर्णांक cflags)
अणु
	वापस __io_cqring_fill_event(ctx, user_data, res, cflags);
पूर्ण

अटल व्योम io_req_complete_post(काष्ठा io_kiocb *req, दीर्घ res,
				 अचिन्हित पूर्णांक cflags)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->completion_lock, flags);
	__io_cqring_fill_event(ctx, req->user_data, res, cflags);
	/*
	 * If we're the last reference to this request, add to our locked
	 * मुक्त_list cache.
	 */
	अगर (req_ref_put_and_test(req)) अणु
		काष्ठा io_comp_state *cs = &ctx->submit_state.comp;

		अगर (req->flags & (REQ_F_LINK | REQ_F_HARDLINK)) अणु
			अगर (req->flags & (REQ_F_LINK_TIMEOUT | REQ_F_FAIL_LINK))
				io_disarm_next(req);
			अगर (req->link) अणु
				io_req_task_queue(req->link);
				req->link = शून्य;
			पूर्ण
		पूर्ण
		io_dismantle_req(req);
		io_put_task(req->task, 1);
		list_add(&req->compl.list, &cs->locked_मुक्त_list);
		cs->locked_मुक्त_nr++;
	पूर्ण अन्यथा अणु
		अगर (!percpu_ref_tryget(&ctx->refs))
			req = शून्य;
	पूर्ण
	io_commit_cqring(ctx);
	spin_unlock_irqrestore(&ctx->completion_lock, flags);

	अगर (req) अणु
		io_cqring_ev_posted(ctx);
		percpu_ref_put(&ctx->refs);
	पूर्ण
पूर्ण

अटल अंतरभूत bool io_req_needs_clean(काष्ठा io_kiocb *req)
अणु
	वापस req->flags & (REQ_F_BUFFER_SELECTED | REQ_F_NEED_CLEANUP |
				REQ_F_POLLED | REQ_F_INFLIGHT);
पूर्ण

अटल व्योम io_req_complete_state(काष्ठा io_kiocb *req, दीर्घ res,
				  अचिन्हित पूर्णांक cflags)
अणु
	अगर (io_req_needs_clean(req))
		io_clean_op(req);
	req->result = res;
	req->compl.cflags = cflags;
	req->flags |= REQ_F_COMPLETE_INLINE;
पूर्ण

अटल अंतरभूत व्योम __io_req_complete(काष्ठा io_kiocb *req, अचिन्हित issue_flags,
				     दीर्घ res, अचिन्हित cflags)
अणु
	अगर (issue_flags & IO_URING_F_COMPLETE_DEFER)
		io_req_complete_state(req, res, cflags);
	अन्यथा
		io_req_complete_post(req, res, cflags);
पूर्ण

अटल अंतरभूत व्योम io_req_complete(काष्ठा io_kiocb *req, दीर्घ res)
अणु
	__io_req_complete(req, 0, res, 0);
पूर्ण

अटल व्योम io_req_complete_failed(काष्ठा io_kiocb *req, दीर्घ res)
अणु
	req_set_fail_links(req);
	io_put_req(req);
	io_req_complete_post(req, res, 0);
पूर्ण

अटल व्योम io_flush_cached_locked_reqs(काष्ठा io_ring_ctx *ctx,
					काष्ठा io_comp_state *cs)
अणु
	spin_lock_irq(&ctx->completion_lock);
	list_splice_init(&cs->locked_मुक्त_list, &cs->मुक्त_list);
	cs->locked_मुक्त_nr = 0;
	spin_unlock_irq(&ctx->completion_lock);
पूर्ण

/* Returns true IFF there are requests in the cache */
अटल bool io_flush_cached_reqs(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_submit_state *state = &ctx->submit_state;
	काष्ठा io_comp_state *cs = &state->comp;
	पूर्णांक nr;

	/*
	 * If we have more than a batch's worth of requests in our IRQ side
	 * locked cache, grab the lock and move them over to our submission
	 * side cache.
	 */
	अगर (READ_ONCE(cs->locked_मुक्त_nr) > IO_COMPL_BATCH)
		io_flush_cached_locked_reqs(ctx, cs);

	nr = state->मुक्त_reqs;
	जबतक (!list_empty(&cs->मुक्त_list)) अणु
		काष्ठा io_kiocb *req = list_first_entry(&cs->मुक्त_list,
						काष्ठा io_kiocb, compl.list);

		list_del(&req->compl.list);
		state->reqs[nr++] = req;
		अगर (nr == ARRAY_SIZE(state->reqs))
			अवरोध;
	पूर्ण

	state->मुक्त_reqs = nr;
	वापस nr != 0;
पूर्ण

अटल काष्ठा io_kiocb *io_alloc_req(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_submit_state *state = &ctx->submit_state;

	BUILD_BUG_ON(IO_REQ_ALLOC_BATCH > ARRAY_SIZE(state->reqs));

	अगर (!state->मुक्त_reqs) अणु
		gfp_t gfp = GFP_KERNEL | __GFP_NOWARN;
		पूर्णांक ret;

		अगर (io_flush_cached_reqs(ctx))
			जाओ got_req;

		ret = kmem_cache_alloc_bulk(req_cachep, gfp, IO_REQ_ALLOC_BATCH,
					    state->reqs);

		/*
		 * Bulk alloc is all-or-nothing. If we fail to get a batch,
		 * retry single alloc to be on the safe side.
		 */
		अगर (unlikely(ret <= 0)) अणु
			state->reqs[0] = kmem_cache_alloc(req_cachep, gfp);
			अगर (!state->reqs[0])
				वापस शून्य;
			ret = 1;
		पूर्ण
		state->मुक्त_reqs = ret;
	पूर्ण
got_req:
	state->मुक्त_reqs--;
	वापस state->reqs[state->मुक्त_reqs];
पूर्ण

अटल अंतरभूत व्योम io_put_file(काष्ठा file *file)
अणु
	अगर (file)
		fput(file);
पूर्ण

अटल व्योम io_dismantle_req(काष्ठा io_kiocb *req)
अणु
	अचिन्हित पूर्णांक flags = req->flags;

	अगर (io_req_needs_clean(req))
		io_clean_op(req);
	अगर (!(flags & REQ_F_FIXED_खाता))
		io_put_file(req->file);
	अगर (req->fixed_rsrc_refs)
		percpu_ref_put(req->fixed_rsrc_refs);
	अगर (req->async_data)
		kमुक्त(req->async_data);
	अगर (req->work.creds) अणु
		put_cred(req->work.creds);
		req->work.creds = शून्य;
	पूर्ण
पूर्ण

/* must to be called somewhat लघुly after putting a request */
अटल अंतरभूत व्योम io_put_task(काष्ठा task_काष्ठा *task, पूर्णांक nr)
अणु
	काष्ठा io_uring_task *tctx = task->io_uring;

	percpu_counter_sub(&tctx->inflight, nr);
	अगर (unlikely(atomic_पढ़ो(&tctx->in_idle)))
		wake_up(&tctx->रुको);
	put_task_काष्ठा_many(task, nr);
पूर्ण

अटल व्योम __io_मुक्त_req(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	io_dismantle_req(req);
	io_put_task(req->task, 1);

	kmem_cache_मुक्त(req_cachep, req);
	percpu_ref_put(&ctx->refs);
पूर्ण

अटल अंतरभूत व्योम io_हटाओ_next_linked(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_kiocb *nxt = req->link;

	req->link = nxt->link;
	nxt->link = शून्य;
पूर्ण

अटल bool io_समाप्त_linked_समयout(काष्ठा io_kiocb *req)
	__must_hold(&req->ctx->completion_lock)
अणु
	काष्ठा io_kiocb *link = req->link;

	/*
	 * Can happen अगर a linked समयout fired and link had been like
	 * req -> link t-out -> link t-out [-> ...]
	 */
	अगर (link && (link->flags & REQ_F_LTIMEOUT_ACTIVE)) अणु
		काष्ठा io_समयout_data *io = link->async_data;

		io_हटाओ_next_linked(req);
		link->समयout.head = शून्य;
		अगर (hrसमयr_try_to_cancel(&io->समयr) != -1) अणु
			io_cqring_fill_event(link->ctx, link->user_data,
					     -ECANCELED, 0);
			io_put_req_deferred(link, 1);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम io_fail_links(काष्ठा io_kiocb *req)
	__must_hold(&req->ctx->completion_lock)
अणु
	काष्ठा io_kiocb *nxt, *link = req->link;

	req->link = शून्य;
	जबतक (link) अणु
		nxt = link->link;
		link->link = शून्य;

		trace_io_uring_fail_link(req, link);
		io_cqring_fill_event(link->ctx, link->user_data, -ECANCELED, 0);
		io_put_req_deferred(link, 2);
		link = nxt;
	पूर्ण
पूर्ण

अटल bool io_disarm_next(काष्ठा io_kiocb *req)
	__must_hold(&req->ctx->completion_lock)
अणु
	bool posted = false;

	अगर (likely(req->flags & REQ_F_LINK_TIMEOUT))
		posted = io_समाप्त_linked_समयout(req);
	अगर (unlikely((req->flags & REQ_F_FAIL_LINK) &&
		     !(req->flags & REQ_F_HARDLINK))) अणु
		posted |= (req->link != शून्य);
		io_fail_links(req);
	पूर्ण
	वापस posted;
पूर्ण

अटल काष्ठा io_kiocb *__io_req_find_next(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_kiocb *nxt;

	/*
	 * If LINK is set, we have dependent requests in this chain. If we
	 * didn't fail this request, queue the first one up, moving any other
	 * dependencies to the next request. In हाल of failure, fail the rest
	 * of the chain.
	 */
	अगर (req->flags & (REQ_F_LINK_TIMEOUT | REQ_F_FAIL_LINK)) अणु
		काष्ठा io_ring_ctx *ctx = req->ctx;
		अचिन्हित दीर्घ flags;
		bool posted;

		spin_lock_irqsave(&ctx->completion_lock, flags);
		posted = io_disarm_next(req);
		अगर (posted)
			io_commit_cqring(req->ctx);
		spin_unlock_irqrestore(&ctx->completion_lock, flags);
		अगर (posted)
			io_cqring_ev_posted(ctx);
	पूर्ण
	nxt = req->link;
	req->link = शून्य;
	वापस nxt;
पूर्ण

अटल अंतरभूत काष्ठा io_kiocb *io_req_find_next(काष्ठा io_kiocb *req)
अणु
	अगर (likely(!(req->flags & (REQ_F_LINK|REQ_F_HARDLINK))))
		वापस शून्य;
	वापस __io_req_find_next(req);
पूर्ण

अटल व्योम ctx_flush_and_put(काष्ठा io_ring_ctx *ctx)
अणु
	अगर (!ctx)
		वापस;
	अगर (ctx->submit_state.comp.nr) अणु
		mutex_lock(&ctx->uring_lock);
		io_submit_flush_completions(&ctx->submit_state.comp, ctx);
		mutex_unlock(&ctx->uring_lock);
	पूर्ण
	percpu_ref_put(&ctx->refs);
पूर्ण

अटल bool __tctx_task_work(काष्ठा io_uring_task *tctx)
अणु
	काष्ठा io_ring_ctx *ctx = शून्य;
	काष्ठा io_wq_work_list list;
	काष्ठा io_wq_work_node *node;

	अगर (wq_list_empty(&tctx->task_list))
		वापस false;

	spin_lock_irq(&tctx->task_lock);
	list = tctx->task_list;
	INIT_WQ_LIST(&tctx->task_list);
	spin_unlock_irq(&tctx->task_lock);

	node = list.first;
	जबतक (node) अणु
		काष्ठा io_wq_work_node *next = node->next;
		काष्ठा io_kiocb *req;

		req = container_of(node, काष्ठा io_kiocb, io_task_work.node);
		अगर (req->ctx != ctx) अणु
			ctx_flush_and_put(ctx);
			ctx = req->ctx;
			percpu_ref_get(&ctx->refs);
		पूर्ण

		req->task_work.func(&req->task_work);
		node = next;
	पूर्ण

	ctx_flush_and_put(ctx);
	वापस list.first != शून्य;
पूर्ण

अटल व्योम tctx_task_work(काष्ठा callback_head *cb)
अणु
	काष्ठा io_uring_task *tctx = container_of(cb, काष्ठा io_uring_task, task_work);

	clear_bit(0, &tctx->task_state);

	जबतक (__tctx_task_work(tctx))
		cond_resched();
पूर्ण

अटल पूर्णांक io_req_task_work_add(काष्ठा io_kiocb *req)
अणु
	काष्ठा task_काष्ठा *tsk = req->task;
	काष्ठा io_uring_task *tctx = tsk->io_uring;
	क्रमागत task_work_notअगरy_mode notअगरy;
	काष्ठा io_wq_work_node *node, *prev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (unlikely(tsk->flags & PF_EXITING))
		वापस -ESRCH;

	WARN_ON_ONCE(!tctx);

	spin_lock_irqsave(&tctx->task_lock, flags);
	wq_list_add_tail(&req->io_task_work.node, &tctx->task_list);
	spin_unlock_irqrestore(&tctx->task_lock, flags);

	/* task_work alपढ़ोy pending, we're करोne */
	अगर (test_bit(0, &tctx->task_state) ||
	    test_and_set_bit(0, &tctx->task_state))
		वापस 0;

	/*
	 * SQPOLL kernel thपढ़ो करोesn't need notअगरication, just a wakeup. For
	 * all other हालs, use TWA_SIGNAL unconditionally to ensure we're
	 * processing task_work. There's no reliable way to tell अगर TWA_RESUME
	 * will करो the job.
	 */
	notअगरy = (req->ctx->flags & IORING_SETUP_SQPOLL) ? TWA_NONE : TWA_SIGNAL;

	अगर (!task_work_add(tsk, &tctx->task_work, notअगरy)) अणु
		wake_up_process(tsk);
		वापस 0;
	पूर्ण

	/*
	 * Slow path - we failed, find and delete work. अगर the work is not
	 * in the list, it got run and we're fine.
	 */
	spin_lock_irqsave(&tctx->task_lock, flags);
	wq_list_क्रम_each(node, prev, &tctx->task_list) अणु
		अगर (&req->io_task_work.node == node) अणु
			wq_list_del(&tctx->task_list, node, prev);
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&tctx->task_lock, flags);
	clear_bit(0, &tctx->task_state);
	वापस ret;
पूर्ण

अटल bool io_run_task_work_head(काष्ठा callback_head **work_head)
अणु
	काष्ठा callback_head *work, *next;
	bool executed = false;

	करो अणु
		work = xchg(work_head, शून्य);
		अगर (!work)
			अवरोध;

		करो अणु
			next = work->next;
			work->func(work);
			work = next;
			cond_resched();
		पूर्ण जबतक (work);
		executed = true;
	पूर्ण जबतक (1);

	वापस executed;
पूर्ण

अटल व्योम io_task_work_add_head(काष्ठा callback_head **work_head,
				  काष्ठा callback_head *task_work)
अणु
	काष्ठा callback_head *head;

	करो अणु
		head = READ_ONCE(*work_head);
		task_work->next = head;
	पूर्ण जबतक (cmpxchg(work_head, head, task_work) != head);
पूर्ण

अटल व्योम io_req_task_work_add_fallback(काष्ठा io_kiocb *req,
					  task_work_func_t cb)
अणु
	init_task_work(&req->task_work, cb);
	io_task_work_add_head(&req->ctx->निकास_task_work, &req->task_work);
पूर्ण

अटल व्योम io_req_task_cancel(काष्ठा callback_head *cb)
अणु
	काष्ठा io_kiocb *req = container_of(cb, काष्ठा io_kiocb, task_work);
	काष्ठा io_ring_ctx *ctx = req->ctx;

	/* ctx is guaranteed to stay alive जबतक we hold uring_lock */
	mutex_lock(&ctx->uring_lock);
	io_req_complete_failed(req, req->result);
	mutex_unlock(&ctx->uring_lock);
पूर्ण

अटल व्योम __io_req_task_submit(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	/* ctx stays valid until unlock, even अगर we drop all ours ctx->refs */
	mutex_lock(&ctx->uring_lock);
	अगर (!(current->flags & PF_EXITING) && !current->in_execve)
		__io_queue_sqe(req);
	अन्यथा
		io_req_complete_failed(req, -EFAULT);
	mutex_unlock(&ctx->uring_lock);
पूर्ण

अटल व्योम io_req_task_submit(काष्ठा callback_head *cb)
अणु
	काष्ठा io_kiocb *req = container_of(cb, काष्ठा io_kiocb, task_work);

	__io_req_task_submit(req);
पूर्ण

अटल व्योम io_req_task_queue_fail(काष्ठा io_kiocb *req, पूर्णांक ret)
अणु
	req->result = ret;
	req->task_work.func = io_req_task_cancel;

	अगर (unlikely(io_req_task_work_add(req)))
		io_req_task_work_add_fallback(req, io_req_task_cancel);
पूर्ण

अटल व्योम io_req_task_queue(काष्ठा io_kiocb *req)
अणु
	req->task_work.func = io_req_task_submit;

	अगर (unlikely(io_req_task_work_add(req)))
		io_req_task_queue_fail(req, -ECANCELED);
पूर्ण

अटल अंतरभूत व्योम io_queue_next(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_kiocb *nxt = io_req_find_next(req);

	अगर (nxt)
		io_req_task_queue(nxt);
पूर्ण

अटल व्योम io_मुक्त_req(काष्ठा io_kiocb *req)
अणु
	io_queue_next(req);
	__io_मुक्त_req(req);
पूर्ण

काष्ठा req_batch अणु
	काष्ठा task_काष्ठा	*task;
	पूर्णांक			task_refs;
	पूर्णांक			ctx_refs;
पूर्ण;

अटल अंतरभूत व्योम io_init_req_batch(काष्ठा req_batch *rb)
अणु
	rb->task_refs = 0;
	rb->ctx_refs = 0;
	rb->task = शून्य;
पूर्ण

अटल व्योम io_req_मुक्त_batch_finish(काष्ठा io_ring_ctx *ctx,
				     काष्ठा req_batch *rb)
अणु
	अगर (rb->task)
		io_put_task(rb->task, rb->task_refs);
	अगर (rb->ctx_refs)
		percpu_ref_put_many(&ctx->refs, rb->ctx_refs);
पूर्ण

अटल व्योम io_req_मुक्त_batch(काष्ठा req_batch *rb, काष्ठा io_kiocb *req,
			      काष्ठा io_submit_state *state)
अणु
	io_queue_next(req);
	io_dismantle_req(req);

	अगर (req->task != rb->task) अणु
		अगर (rb->task)
			io_put_task(rb->task, rb->task_refs);
		rb->task = req->task;
		rb->task_refs = 0;
	पूर्ण
	rb->task_refs++;
	rb->ctx_refs++;

	अगर (state->मुक्त_reqs != ARRAY_SIZE(state->reqs))
		state->reqs[state->मुक्त_reqs++] = req;
	अन्यथा
		list_add(&req->compl.list, &state->comp.मुक्त_list);
पूर्ण

अटल व्योम io_submit_flush_completions(काष्ठा io_comp_state *cs,
					काष्ठा io_ring_ctx *ctx)
अणु
	पूर्णांक i, nr = cs->nr;
	काष्ठा io_kiocb *req;
	काष्ठा req_batch rb;

	io_init_req_batch(&rb);
	spin_lock_irq(&ctx->completion_lock);
	क्रम (i = 0; i < nr; i++) अणु
		req = cs->reqs[i];
		__io_cqring_fill_event(ctx, req->user_data, req->result,
					req->compl.cflags);
	पूर्ण
	io_commit_cqring(ctx);
	spin_unlock_irq(&ctx->completion_lock);

	io_cqring_ev_posted(ctx);
	क्रम (i = 0; i < nr; i++) अणु
		req = cs->reqs[i];

		/* submission and completion refs */
		अगर (req_ref_sub_and_test(req, 2))
			io_req_मुक्त_batch(&rb, req, &ctx->submit_state);
	पूर्ण

	io_req_मुक्त_batch_finish(ctx, &rb);
	cs->nr = 0;
पूर्ण

/*
 * Drop reference to request, वापस next in chain (अगर there is one) अगर this
 * was the last reference to this request.
 */
अटल अंतरभूत काष्ठा io_kiocb *io_put_req_find_next(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_kiocb *nxt = शून्य;

	अगर (req_ref_put_and_test(req)) अणु
		nxt = io_req_find_next(req);
		__io_मुक्त_req(req);
	पूर्ण
	वापस nxt;
पूर्ण

अटल अंतरभूत व्योम io_put_req(काष्ठा io_kiocb *req)
अणु
	अगर (req_ref_put_and_test(req))
		io_मुक्त_req(req);
पूर्ण

अटल व्योम io_put_req_deferred_cb(काष्ठा callback_head *cb)
अणु
	काष्ठा io_kiocb *req = container_of(cb, काष्ठा io_kiocb, task_work);

	io_मुक्त_req(req);
पूर्ण

अटल व्योम io_मुक्त_req_deferred(काष्ठा io_kiocb *req)
अणु
	req->task_work.func = io_put_req_deferred_cb;
	अगर (unlikely(io_req_task_work_add(req)))
		io_req_task_work_add_fallback(req, io_put_req_deferred_cb);
पूर्ण

अटल अंतरभूत व्योम io_put_req_deferred(काष्ठा io_kiocb *req, पूर्णांक refs)
अणु
	अगर (req_ref_sub_and_test(req, refs))
		io_मुक्त_req_deferred(req);
पूर्ण

अटल अचिन्हित io_cqring_events(काष्ठा io_ring_ctx *ctx)
अणु
	/* See comment at the top of this file */
	smp_rmb();
	वापस __io_cqring_events(ctx);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक io_sqring_entries(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_rings *rings = ctx->rings;

	/* make sure SQ entry isn't पढ़ो beक्रमe tail */
	वापस smp_load_acquire(&rings->sq.tail) - ctx->cached_sq_head;
पूर्ण

अटल अचिन्हित पूर्णांक io_put_kbuf(काष्ठा io_kiocb *req, काष्ठा io_buffer *kbuf)
अणु
	अचिन्हित पूर्णांक cflags;

	cflags = kbuf->bid << IORING_CQE_BUFFER_SHIFT;
	cflags |= IORING_CQE_F_BUFFER;
	req->flags &= ~REQ_F_BUFFER_SELECTED;
	kमुक्त(kbuf);
	वापस cflags;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक io_put_rw_kbuf(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_buffer *kbuf;

	kbuf = (काष्ठा io_buffer *) (अचिन्हित दीर्घ) req->rw.addr;
	वापस io_put_kbuf(req, kbuf);
पूर्ण

अटल अंतरभूत bool io_run_task_work(व्योम)
अणु
	/*
	 * Not safe to run on निकासing task, and the task_work handling will
	 * not add work to such a task.
	 */
	अगर (unlikely(current->flags & PF_EXITING))
		वापस false;
	अगर (current->task_works) अणु
		__set_current_state(TASK_RUNNING);
		task_work_run();
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Find and मुक्त completed poll iocbs
 */
अटल व्योम io_iopoll_complete(काष्ठा io_ring_ctx *ctx, अचिन्हित पूर्णांक *nr_events,
			       काष्ठा list_head *करोne)
अणु
	काष्ठा req_batch rb;
	काष्ठा io_kiocb *req;

	/* order with ->result store in io_complete_rw_iopoll() */
	smp_rmb();

	io_init_req_batch(&rb);
	जबतक (!list_empty(करोne)) अणु
		पूर्णांक cflags = 0;

		req = list_first_entry(करोne, काष्ठा io_kiocb, inflight_entry);
		list_del(&req->inflight_entry);

		अगर (READ_ONCE(req->result) == -EAGAIN &&
		    !(req->flags & REQ_F_DONT_REISSUE)) अणु
			req->iopoll_completed = 0;
			req_ref_get(req);
			io_queue_async_work(req);
			जारी;
		पूर्ण

		अगर (req->flags & REQ_F_BUFFER_SELECTED)
			cflags = io_put_rw_kbuf(req);

		__io_cqring_fill_event(ctx, req->user_data, req->result, cflags);
		(*nr_events)++;

		अगर (req_ref_put_and_test(req))
			io_req_मुक्त_batch(&rb, req, &ctx->submit_state);
	पूर्ण

	io_commit_cqring(ctx);
	io_cqring_ev_posted_iopoll(ctx);
	io_req_मुक्त_batch_finish(ctx, &rb);
पूर्ण

अटल पूर्णांक io_करो_iopoll(काष्ठा io_ring_ctx *ctx, अचिन्हित पूर्णांक *nr_events,
			दीर्घ min)
अणु
	काष्ठा io_kiocb *req, *पंचांगp;
	LIST_HEAD(करोne);
	bool spin;
	पूर्णांक ret;

	/*
	 * Only spin क्रम completions अगर we करोn't have multiple devices hanging
	 * off our complete list, and we're under the requested amount.
	 */
	spin = !ctx->poll_multi_file && *nr_events < min;

	ret = 0;
	list_क्रम_each_entry_safe(req, पंचांगp, &ctx->iopoll_list, inflight_entry) अणु
		काष्ठा kiocb *kiocb = &req->rw.kiocb;

		/*
		 * Move completed and retryable entries to our local lists.
		 * If we find a request that requires polling, अवरोध out
		 * and complete those lists first, अगर we have entries there.
		 */
		अगर (READ_ONCE(req->iopoll_completed)) अणु
			list_move_tail(&req->inflight_entry, &करोne);
			जारी;
		पूर्ण
		अगर (!list_empty(&करोne))
			अवरोध;

		ret = kiocb->ki_filp->f_op->iopoll(kiocb, spin);
		अगर (ret < 0)
			अवरोध;

		/* iopoll may have completed current req */
		अगर (READ_ONCE(req->iopoll_completed))
			list_move_tail(&req->inflight_entry, &करोne);

		अगर (ret && spin)
			spin = false;
		ret = 0;
	पूर्ण

	अगर (!list_empty(&करोne))
		io_iopoll_complete(ctx, nr_events, &करोne);

	वापस ret;
पूर्ण

/*
 * We can't just रुको क्रम polled events to come to us, we have to actively
 * find and complete them.
 */
अटल व्योम io_iopoll_try_reap_events(काष्ठा io_ring_ctx *ctx)
अणु
	अगर (!(ctx->flags & IORING_SETUP_IOPOLL))
		वापस;

	mutex_lock(&ctx->uring_lock);
	जबतक (!list_empty(&ctx->iopoll_list)) अणु
		अचिन्हित पूर्णांक nr_events = 0;

		io_करो_iopoll(ctx, &nr_events, 0);

		/* let it sleep and repeat later अगर can't complete a request */
		अगर (nr_events == 0)
			अवरोध;
		/*
		 * Ensure we allow local-to-the-cpu processing to take place,
		 * in this हाल we need to ensure that we reap all events.
		 * Also let task_work, etc. to progress by releasing the mutex
		 */
		अगर (need_resched()) अणु
			mutex_unlock(&ctx->uring_lock);
			cond_resched();
			mutex_lock(&ctx->uring_lock);
		पूर्ण
	पूर्ण
	mutex_unlock(&ctx->uring_lock);
पूर्ण

अटल पूर्णांक io_iopoll_check(काष्ठा io_ring_ctx *ctx, दीर्घ min)
अणु
	अचिन्हित पूर्णांक nr_events = 0;
	पूर्णांक ret = 0;

	/*
	 * We disallow the app entering submit/complete with polling, but we
	 * still need to lock the ring to prevent racing with polled issue
	 * that got punted to a workqueue.
	 */
	mutex_lock(&ctx->uring_lock);
	/*
	 * Don't enter poll loop अगर we alपढ़ोy have events pending.
	 * If we करो, we can potentially be spinning क्रम commands that
	 * alपढ़ोy triggered a CQE (eg in error).
	 */
	अगर (test_bit(0, &ctx->cq_check_overflow))
		__io_cqring_overflow_flush(ctx, false);
	अगर (io_cqring_events(ctx))
		जाओ out;
	करो अणु
		/*
		 * If a submit got punted to a workqueue, we can have the
		 * application entering polling क्रम a command beक्रमe it माला_लो
		 * issued. That app will hold the uring_lock क्रम the duration
		 * of the poll right here, so we need to take a breather every
		 * now and then to ensure that the issue has a chance to add
		 * the poll to the issued list. Otherwise we can spin here
		 * क्रमever, जबतक the workqueue is stuck trying to acquire the
		 * very same mutex.
		 */
		अगर (list_empty(&ctx->iopoll_list)) अणु
			mutex_unlock(&ctx->uring_lock);
			io_run_task_work();
			mutex_lock(&ctx->uring_lock);

			अगर (list_empty(&ctx->iopoll_list))
				अवरोध;
		पूर्ण
		ret = io_करो_iopoll(ctx, &nr_events, min);
	पूर्ण जबतक (!ret && nr_events < min && !need_resched());
out:
	mutex_unlock(&ctx->uring_lock);
	वापस ret;
पूर्ण

अटल व्योम kiocb_end_ग_लिखो(काष्ठा io_kiocb *req)
अणु
	/*
	 * Tell lockdep we inherited मुक्तze protection from submission
	 * thपढ़ो.
	 */
	अगर (req->flags & REQ_F_ISREG) अणु
		काष्ठा super_block *sb = file_inode(req->file)->i_sb;

		__sb_ग_लिखोrs_acquired(sb, SB_FREEZE_WRITE);
		sb_end_ग_लिखो(sb);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_BLOCK
अटल bool io_resubmit_prep(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_async_rw *rw = req->async_data;

	अगर (!rw)
		वापस !io_req_prep_async(req);
	/* may have left rw->iter inconsistent on -EIOCBQUEUED */
	iov_iter_revert(&rw->iter, req->result - iov_iter_count(&rw->iter));
	वापस true;
पूर्ण

अटल bool io_rw_should_reissue(काष्ठा io_kiocb *req)
अणु
	umode_t mode = file_inode(req->file)->i_mode;
	काष्ठा io_ring_ctx *ctx = req->ctx;

	अगर (!S_ISBLK(mode) && !S_ISREG(mode))
		वापस false;
	अगर ((req->flags & REQ_F_NOWAIT) || (io_wq_current_is_worker() &&
	    !(ctx->flags & IORING_SETUP_IOPOLL)))
		वापस false;
	/*
	 * If ref is dying, we might be running poll reap from the निकास work.
	 * Don't attempt to reissue from that path, just let it fail with
	 * -EAGAIN.
	 */
	अगर (percpu_ref_is_dying(&ctx->refs))
		वापस false;
	वापस true;
पूर्ण
#अन्यथा
अटल bool io_resubmit_prep(काष्ठा io_kiocb *req)
अणु
	वापस false;
पूर्ण
अटल bool io_rw_should_reissue(काष्ठा io_kiocb *req)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल व्योम __io_complete_rw(काष्ठा io_kiocb *req, दीर्घ res, दीर्घ res2,
			     अचिन्हित पूर्णांक issue_flags)
अणु
	पूर्णांक cflags = 0;

	अगर (req->rw.kiocb.ki_flags & IOCB_WRITE)
		kiocb_end_ग_लिखो(req);
	अगर (res != req->result) अणु
		अगर ((res == -EAGAIN || res == -EOPNOTSUPP) &&
		    io_rw_should_reissue(req)) अणु
			req->flags |= REQ_F_REISSUE;
			वापस;
		पूर्ण
		req_set_fail_links(req);
	पूर्ण
	अगर (req->flags & REQ_F_BUFFER_SELECTED)
		cflags = io_put_rw_kbuf(req);
	__io_req_complete(req, issue_flags, res, cflags);
पूर्ण

अटल व्योम io_complete_rw(काष्ठा kiocb *kiocb, दीर्घ res, दीर्घ res2)
अणु
	काष्ठा io_kiocb *req = container_of(kiocb, काष्ठा io_kiocb, rw.kiocb);

	__io_complete_rw(req, res, res2, 0);
पूर्ण

अटल व्योम io_complete_rw_iopoll(काष्ठा kiocb *kiocb, दीर्घ res, दीर्घ res2)
अणु
	काष्ठा io_kiocb *req = container_of(kiocb, काष्ठा io_kiocb, rw.kiocb);

	अगर (kiocb->ki_flags & IOCB_WRITE)
		kiocb_end_ग_लिखो(req);
	अगर (unlikely(res != req->result)) अणु
		अगर (!(res == -EAGAIN && io_rw_should_reissue(req) &&
		    io_resubmit_prep(req))) अणु
			req_set_fail_links(req);
			req->flags |= REQ_F_DONT_REISSUE;
		पूर्ण
	पूर्ण

	WRITE_ONCE(req->result, res);
	/* order with io_iopoll_complete() checking ->result */
	smp_wmb();
	WRITE_ONCE(req->iopoll_completed, 1);
पूर्ण

/*
 * After the iocb has been issued, it's safe to be found on the poll list.
 * Adding the kiocb to the list AFTER submission ensures that we करोn't
 * find it from a io_करो_iopoll() thपढ़ो beक्रमe the issuer is करोne
 * accessing the kiocb cookie.
 */
अटल व्योम io_iopoll_req_issued(काष्ठा io_kiocb *req, bool in_async)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	/*
	 * Track whether we have multiple files in our lists. This will impact
	 * how we करो polling eventually, not spinning अगर we're on potentially
	 * dअगरferent devices.
	 */
	अगर (list_empty(&ctx->iopoll_list)) अणु
		ctx->poll_multi_file = false;
	पूर्ण अन्यथा अगर (!ctx->poll_multi_file) अणु
		काष्ठा io_kiocb *list_req;

		list_req = list_first_entry(&ctx->iopoll_list, काष्ठा io_kiocb,
						inflight_entry);
		अगर (list_req->file != req->file)
			ctx->poll_multi_file = true;
	पूर्ण

	/*
	 * For fast devices, IO may have alपढ़ोy completed. If it has, add
	 * it to the front so we find it first.
	 */
	अगर (READ_ONCE(req->iopoll_completed))
		list_add(&req->inflight_entry, &ctx->iopoll_list);
	अन्यथा
		list_add_tail(&req->inflight_entry, &ctx->iopoll_list);

	/*
	 * If IORING_SETUP_SQPOLL is enabled, sqes are either handled in sq thपढ़ो
	 * task context or in io worker task context. If current task context is
	 * sq thपढ़ो, we करोn't need to check whether should wake up sq thपढ़ो.
	 */
	अगर (in_async && (ctx->flags & IORING_SETUP_SQPOLL) &&
	    wq_has_sleeper(&ctx->sq_data->रुको))
		wake_up(&ctx->sq_data->रुको);
पूर्ण

अटल अंतरभूत व्योम io_state_file_put(काष्ठा io_submit_state *state)
अणु
	अगर (state->file_refs) अणु
		fput_many(state->file, state->file_refs);
		state->file_refs = 0;
	पूर्ण
पूर्ण

/*
 * Get as many references to a file as we have IOs left in this submission,
 * assuming most submissions are क्रम one file, or at least that each file
 * has more than one submission.
 */
अटल काष्ठा file *__io_file_get(काष्ठा io_submit_state *state, पूर्णांक fd)
अणु
	अगर (!state)
		वापस fget(fd);

	अगर (state->file_refs) अणु
		अगर (state->fd == fd) अणु
			state->file_refs--;
			वापस state->file;
		पूर्ण
		io_state_file_put(state);
	पूर्ण
	state->file = fget_many(fd, state->ios_left);
	अगर (unlikely(!state->file))
		वापस शून्य;

	state->fd = fd;
	state->file_refs = state->ios_left - 1;
	वापस state->file;
पूर्ण

अटल bool io_bdev_noरुको(काष्ठा block_device *bdev)
अणु
	वापस !bdev || blk_queue_noरुको(bdev_get_queue(bdev));
पूर्ण

/*
 * If we tracked the file through the SCM inflight mechanism, we could support
 * any file. For now, just ensure that anything potentially problematic is करोne
 * अंतरभूत.
 */
अटल bool __io_file_supports_async(काष्ठा file *file, पूर्णांक rw)
अणु
	umode_t mode = file_inode(file)->i_mode;

	अगर (S_ISBLK(mode)) अणु
		अगर (IS_ENABLED(CONFIG_BLOCK) &&
		    io_bdev_noरुको(I_BDEV(file->f_mapping->host)))
			वापस true;
		वापस false;
	पूर्ण
	अगर (S_ISCHR(mode) || S_ISSOCK(mode))
		वापस true;
	अगर (S_ISREG(mode)) अणु
		अगर (IS_ENABLED(CONFIG_BLOCK) &&
		    io_bdev_noरुको(file->f_inode->i_sb->s_bdev) &&
		    file->f_op != &io_uring_fops)
			वापस true;
		वापस false;
	पूर्ण

	/* any ->पढ़ो/ग_लिखो should understand O_NONBLOCK */
	अगर (file->f_flags & O_NONBLOCK)
		वापस true;

	अगर (!(file->f_mode & FMODE_NOWAIT))
		वापस false;

	अगर (rw == READ)
		वापस file->f_op->पढ़ो_iter != शून्य;

	वापस file->f_op->ग_लिखो_iter != शून्य;
पूर्ण

अटल bool io_file_supports_async(काष्ठा io_kiocb *req, पूर्णांक rw)
अणु
	अगर (rw == READ && (req->flags & REQ_F_ASYNC_READ))
		वापस true;
	अन्यथा अगर (rw == WRITE && (req->flags & REQ_F_ASYNC_WRITE))
		वापस true;

	वापस __io_file_supports_async(req->file, rw);
पूर्ण

अटल पूर्णांक io_prep_rw(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा kiocb *kiocb = &req->rw.kiocb;
	काष्ठा file *file = req->file;
	अचिन्हित ioprio;
	पूर्णांक ret;

	अगर (!(req->flags & REQ_F_ISREG) && S_ISREG(file_inode(file)->i_mode))
		req->flags |= REQ_F_ISREG;

	kiocb->ki_pos = READ_ONCE(sqe->off);
	अगर (kiocb->ki_pos == -1 && !(file->f_mode & FMODE_STREAM)) अणु
		req->flags |= REQ_F_CUR_POS;
		kiocb->ki_pos = file->f_pos;
	पूर्ण
	kiocb->ki_hपूर्णांक = ki_hपूर्णांक_validate(file_ग_लिखो_hपूर्णांक(kiocb->ki_filp));
	kiocb->ki_flags = iocb_flags(kiocb->ki_filp);
	ret = kiocb_set_rw_flags(kiocb, READ_ONCE(sqe->rw_flags));
	अगर (unlikely(ret))
		वापस ret;

	/* करोn't allow async punt क्रम O_NONBLOCK or RWF_NOWAIT */
	अगर ((kiocb->ki_flags & IOCB_NOWAIT) || (file->f_flags & O_NONBLOCK))
		req->flags |= REQ_F_NOWAIT;

	ioprio = READ_ONCE(sqe->ioprio);
	अगर (ioprio) अणु
		ret = ioprio_check_cap(ioprio);
		अगर (ret)
			वापस ret;

		kiocb->ki_ioprio = ioprio;
	पूर्ण अन्यथा
		kiocb->ki_ioprio = get_current_ioprio();

	अगर (ctx->flags & IORING_SETUP_IOPOLL) अणु
		अगर (!(kiocb->ki_flags & IOCB_सूचीECT) ||
		    !kiocb->ki_filp->f_op->iopoll)
			वापस -EOPNOTSUPP;

		kiocb->ki_flags |= IOCB_HIPRI;
		kiocb->ki_complete = io_complete_rw_iopoll;
		req->iopoll_completed = 0;
	पूर्ण अन्यथा अणु
		अगर (kiocb->ki_flags & IOCB_HIPRI)
			वापस -EINVAL;
		kiocb->ki_complete = io_complete_rw;
	पूर्ण

	अगर (req->opcode == IORING_OP_READ_FIXED ||
	    req->opcode == IORING_OP_WRITE_FIXED) अणु
		req->imu = शून्य;
		io_req_set_rsrc_node(req);
	पूर्ण

	req->rw.addr = READ_ONCE(sqe->addr);
	req->rw.len = READ_ONCE(sqe->len);
	req->buf_index = READ_ONCE(sqe->buf_index);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम io_rw_करोne(काष्ठा kiocb *kiocb, sमाप_प्रकार ret)
अणु
	चयन (ret) अणु
	हाल -EIOCBQUEUED:
		अवरोध;
	हाल -ERESTARTSYS:
	हाल -ERESTARTNOINTR:
	हाल -ERESTARTNOHAND:
	हाल -ERESTART_RESTARTBLOCK:
		/*
		 * We can't just restart the syscall, since previously
		 * submitted sqes may alपढ़ोy be in progress. Just fail this
		 * IO with EINTR.
		 */
		ret = -EINTR;
		fallthrough;
	शेष:
		kiocb->ki_complete(kiocb, ret, 0);
	पूर्ण
पूर्ण

अटल व्योम kiocb_करोne(काष्ठा kiocb *kiocb, sमाप_प्रकार ret,
		       अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_kiocb *req = container_of(kiocb, काष्ठा io_kiocb, rw.kiocb);
	काष्ठा io_async_rw *io = req->async_data;
	bool check_reissue = kiocb->ki_complete == io_complete_rw;

	/* add previously करोne IO, अगर any */
	अगर (io && io->bytes_करोne > 0) अणु
		अगर (ret < 0)
			ret = io->bytes_करोne;
		अन्यथा
			ret += io->bytes_करोne;
	पूर्ण

	अगर (req->flags & REQ_F_CUR_POS)
		req->file->f_pos = kiocb->ki_pos;
	अगर (ret >= 0 && kiocb->ki_complete == io_complete_rw)
		__io_complete_rw(req, ret, 0, issue_flags);
	अन्यथा
		io_rw_करोne(kiocb, ret);

	अगर (check_reissue && req->flags & REQ_F_REISSUE) अणु
		req->flags &= ~REQ_F_REISSUE;
		अगर (io_resubmit_prep(req)) अणु
			req_ref_get(req);
			io_queue_async_work(req);
		पूर्ण अन्यथा अणु
			पूर्णांक cflags = 0;

			req_set_fail_links(req);
			अगर (req->flags & REQ_F_BUFFER_SELECTED)
				cflags = io_put_rw_kbuf(req);
			__io_req_complete(req, issue_flags, ret, cflags);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __io_import_fixed(काष्ठा io_kiocb *req, पूर्णांक rw, काष्ठा iov_iter *iter,
			     काष्ठा io_mapped_ubuf *imu)
अणु
	माप_प्रकार len = req->rw.len;
	u64 buf_end, buf_addr = req->rw.addr;
	माप_प्रकार offset;

	अगर (unlikely(check_add_overflow(buf_addr, (u64)len, &buf_end)))
		वापस -EFAULT;
	/* not inside the mapped region */
	अगर (unlikely(buf_addr < imu->ubuf || buf_end > imu->ubuf_end))
		वापस -EFAULT;

	/*
	 * May not be a start of buffer, set size appropriately
	 * and advance us to the beginning.
	 */
	offset = buf_addr - imu->ubuf;
	iov_iter_bvec(iter, rw, imu->bvec, imu->nr_bvecs, offset + len);

	अगर (offset) अणु
		/*
		 * Don't use iov_iter_advance() here, as it's really slow क्रम
		 * using the latter parts of a big fixed buffer - it iterates
		 * over each segment manually. We can cheat a bit here, because
		 * we know that:
		 *
		 * 1) it's a BVEC iter, we set it up
		 * 2) all bvecs are PAGE_SIZE in size, except potentially the
		 *    first and last bvec
		 *
		 * So just find our index, and adjust the iterator afterwards.
		 * If the offset is within the first bvec (or the whole first
		 * bvec, just use iov_iter_advance(). This makes it easier
		 * since we can just skip the first segment, which may not
		 * be PAGE_SIZE aligned.
		 */
		स्थिर काष्ठा bio_vec *bvec = imu->bvec;

		अगर (offset <= bvec->bv_len) अणु
			iov_iter_advance(iter, offset);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ seg_skip;

			/* skip first vec */
			offset -= bvec->bv_len;
			seg_skip = 1 + (offset >> PAGE_SHIFT);

			iter->bvec = bvec + seg_skip;
			iter->nr_segs -= seg_skip;
			iter->count -= bvec->bv_len + offset;
			iter->iov_offset = offset & ~PAGE_MASK;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक io_import_fixed(काष्ठा io_kiocb *req, पूर्णांक rw, काष्ठा iov_iter *iter)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_mapped_ubuf *imu = req->imu;
	u16 index, buf_index = req->buf_index;

	अगर (likely(!imu)) अणु
		अगर (unlikely(buf_index >= ctx->nr_user_bufs))
			वापस -EFAULT;
		index = array_index_nospec(buf_index, ctx->nr_user_bufs);
		imu = READ_ONCE(ctx->user_bufs[index]);
		req->imu = imu;
	पूर्ण
	वापस __io_import_fixed(req, rw, iter, imu);
पूर्ण

अटल व्योम io_ring_submit_unlock(काष्ठा io_ring_ctx *ctx, bool needs_lock)
अणु
	अगर (needs_lock)
		mutex_unlock(&ctx->uring_lock);
पूर्ण

अटल व्योम io_ring_submit_lock(काष्ठा io_ring_ctx *ctx, bool needs_lock)
अणु
	/*
	 * "Normal" अंतरभूत submissions always hold the uring_lock, since we
	 * grab it from the प्रणाली call. Same is true क्रम the SQPOLL offload.
	 * The only exception is when we've detached the request and issue it
	 * from an async worker thपढ़ो, grab the lock क्रम that हाल.
	 */
	अगर (needs_lock)
		mutex_lock(&ctx->uring_lock);
पूर्ण

अटल काष्ठा io_buffer *io_buffer_select(काष्ठा io_kiocb *req, माप_प्रकार *len,
					  पूर्णांक bgid, काष्ठा io_buffer *kbuf,
					  bool needs_lock)
अणु
	काष्ठा io_buffer *head;

	अगर (req->flags & REQ_F_BUFFER_SELECTED)
		वापस kbuf;

	io_ring_submit_lock(req->ctx, needs_lock);

	lockdep_निश्चित_held(&req->ctx->uring_lock);

	head = xa_load(&req->ctx->io_buffers, bgid);
	अगर (head) अणु
		अगर (!list_empty(&head->list)) अणु
			kbuf = list_last_entry(&head->list, काष्ठा io_buffer,
							list);
			list_del(&kbuf->list);
		पूर्ण अन्यथा अणु
			kbuf = head;
			xa_erase(&req->ctx->io_buffers, bgid);
		पूर्ण
		अगर (*len > kbuf->len)
			*len = kbuf->len;
	पूर्ण अन्यथा अणु
		kbuf = ERR_PTR(-ENOBUFS);
	पूर्ण

	io_ring_submit_unlock(req->ctx, needs_lock);

	वापस kbuf;
पूर्ण

अटल व्योम __user *io_rw_buffer_select(काष्ठा io_kiocb *req, माप_प्रकार *len,
					bool needs_lock)
अणु
	काष्ठा io_buffer *kbuf;
	u16 bgid;

	kbuf = (काष्ठा io_buffer *) (अचिन्हित दीर्घ) req->rw.addr;
	bgid = req->buf_index;
	kbuf = io_buffer_select(req, len, bgid, kbuf, needs_lock);
	अगर (IS_ERR(kbuf))
		वापस kbuf;
	req->rw.addr = (u64) (अचिन्हित दीर्घ) kbuf;
	req->flags |= REQ_F_BUFFER_SELECTED;
	वापस u64_to_user_ptr(kbuf->addr);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल sमाप_प्रकार io_compat_import(काष्ठा io_kiocb *req, काष्ठा iovec *iov,
				bool needs_lock)
अणु
	काष्ठा compat_iovec __user *uiov;
	compat_sमाप_प्रकार clen;
	व्योम __user *buf;
	sमाप_प्रकार len;

	uiov = u64_to_user_ptr(req->rw.addr);
	अगर (!access_ok(uiov, माप(*uiov)))
		वापस -EFAULT;
	अगर (__get_user(clen, &uiov->iov_len))
		वापस -EFAULT;
	अगर (clen < 0)
		वापस -EINVAL;

	len = clen;
	buf = io_rw_buffer_select(req, &len, needs_lock);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);
	iov[0].iov_base = buf;
	iov[0].iov_len = (compat_माप_प्रकार) len;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार __io_iov_buffer_select(काष्ठा io_kiocb *req, काष्ठा iovec *iov,
				      bool needs_lock)
अणु
	काष्ठा iovec __user *uiov = u64_to_user_ptr(req->rw.addr);
	व्योम __user *buf;
	sमाप_प्रकार len;

	अगर (copy_from_user(iov, uiov, माप(*uiov)))
		वापस -EFAULT;

	len = iov[0].iov_len;
	अगर (len < 0)
		वापस -EINVAL;
	buf = io_rw_buffer_select(req, &len, needs_lock);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);
	iov[0].iov_base = buf;
	iov[0].iov_len = len;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार io_iov_buffer_select(काष्ठा io_kiocb *req, काष्ठा iovec *iov,
				    bool needs_lock)
अणु
	अगर (req->flags & REQ_F_BUFFER_SELECTED) अणु
		काष्ठा io_buffer *kbuf;

		kbuf = (काष्ठा io_buffer *) (अचिन्हित दीर्घ) req->rw.addr;
		iov[0].iov_base = u64_to_user_ptr(kbuf->addr);
		iov[0].iov_len = kbuf->len;
		वापस 0;
	पूर्ण
	अगर (req->rw.len != 1)
		वापस -EINVAL;

#अगर_घोषित CONFIG_COMPAT
	अगर (req->ctx->compat)
		वापस io_compat_import(req, iov, needs_lock);
#पूर्ण_अगर

	वापस __io_iov_buffer_select(req, iov, needs_lock);
पूर्ण

अटल पूर्णांक io_import_iovec(पूर्णांक rw, काष्ठा io_kiocb *req, काष्ठा iovec **iovec,
			   काष्ठा iov_iter *iter, bool needs_lock)
अणु
	व्योम __user *buf = u64_to_user_ptr(req->rw.addr);
	माप_प्रकार sqe_len = req->rw.len;
	u8 opcode = req->opcode;
	sमाप_प्रकार ret;

	अगर (opcode == IORING_OP_READ_FIXED || opcode == IORING_OP_WRITE_FIXED) अणु
		*iovec = शून्य;
		वापस io_import_fixed(req, rw, iter);
	पूर्ण

	/* buffer index only valid with fixed पढ़ो/ग_लिखो, or buffer select  */
	अगर (req->buf_index && !(req->flags & REQ_F_BUFFER_SELECT))
		वापस -EINVAL;

	अगर (opcode == IORING_OP_READ || opcode == IORING_OP_WRITE) अणु
		अगर (req->flags & REQ_F_BUFFER_SELECT) अणु
			buf = io_rw_buffer_select(req, &sqe_len, needs_lock);
			अगर (IS_ERR(buf))
				वापस PTR_ERR(buf);
			req->rw.len = sqe_len;
		पूर्ण

		ret = import_single_range(rw, buf, sqe_len, *iovec, iter);
		*iovec = शून्य;
		वापस ret;
	पूर्ण

	अगर (req->flags & REQ_F_BUFFER_SELECT) अणु
		ret = io_iov_buffer_select(req, *iovec, needs_lock);
		अगर (!ret)
			iov_iter_init(iter, rw, *iovec, 1, (*iovec)->iov_len);
		*iovec = शून्य;
		वापस ret;
	पूर्ण

	वापस __import_iovec(rw, buf, sqe_len, UIO_FASTIOV, iovec, iter,
			      req->ctx->compat);
पूर्ण

अटल अंतरभूत loff_t *io_kiocb_ppos(काष्ठा kiocb *kiocb)
अणु
	वापस (kiocb->ki_filp->f_mode & FMODE_STREAM) ? शून्य : &kiocb->ki_pos;
पूर्ण

/*
 * For files that करोn't have ->पढ़ो_iter() and ->ग_लिखो_iter(), handle them
 * by looping over ->पढ़ो() or ->ग_लिखो() manually.
 */
अटल sमाप_प्रकार loop_rw_iter(पूर्णांक rw, काष्ठा io_kiocb *req, काष्ठा iov_iter *iter)
अणु
	काष्ठा kiocb *kiocb = &req->rw.kiocb;
	काष्ठा file *file = req->file;
	sमाप_प्रकार ret = 0;

	/*
	 * Don't support polled IO through this interface, and we can't
	 * support non-blocking either. For the latter, this just causes
	 * the kiocb to be handled from an async context.
	 */
	अगर (kiocb->ki_flags & IOCB_HIPRI)
		वापस -EOPNOTSUPP;
	अगर (kiocb->ki_flags & IOCB_NOWAIT)
		वापस -EAGAIN;

	जबतक (iov_iter_count(iter)) अणु
		काष्ठा iovec iovec;
		sमाप_प्रकार nr;

		अगर (!iov_iter_is_bvec(iter)) अणु
			iovec = iov_iter_iovec(iter);
		पूर्ण अन्यथा अणु
			iovec.iov_base = u64_to_user_ptr(req->rw.addr);
			iovec.iov_len = req->rw.len;
		पूर्ण

		अगर (rw == READ) अणु
			nr = file->f_op->पढ़ो(file, iovec.iov_base,
					      iovec.iov_len, io_kiocb_ppos(kiocb));
		पूर्ण अन्यथा अणु
			nr = file->f_op->ग_लिखो(file, iovec.iov_base,
					       iovec.iov_len, io_kiocb_ppos(kiocb));
		पूर्ण

		अगर (nr < 0) अणु
			अगर (!ret)
				ret = nr;
			अवरोध;
		पूर्ण
		ret += nr;
		अगर (nr != iovec.iov_len)
			अवरोध;
		req->rw.len -= nr;
		req->rw.addr += nr;
		iov_iter_advance(iter, nr);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम io_req_map_rw(काष्ठा io_kiocb *req, स्थिर काष्ठा iovec *iovec,
			  स्थिर काष्ठा iovec *fast_iov, काष्ठा iov_iter *iter)
अणु
	काष्ठा io_async_rw *rw = req->async_data;

	स_नकल(&rw->iter, iter, माप(*iter));
	rw->मुक्त_iovec = iovec;
	rw->bytes_करोne = 0;
	/* can only be fixed buffers, no need to करो anything */
	अगर (iov_iter_is_bvec(iter))
		वापस;
	अगर (!iovec) अणु
		अचिन्हित iov_off = 0;

		rw->iter.iov = rw->fast_iov;
		अगर (iter->iov != fast_iov) अणु
			iov_off = iter->iov - fast_iov;
			rw->iter.iov += iov_off;
		पूर्ण
		अगर (rw->fast_iov != fast_iov)
			स_नकल(rw->fast_iov + iov_off, fast_iov + iov_off,
			       माप(काष्ठा iovec) * iter->nr_segs);
	पूर्ण अन्यथा अणु
		req->flags |= REQ_F_NEED_CLEANUP;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक io_alloc_async_data(काष्ठा io_kiocb *req)
अणु
	WARN_ON_ONCE(!io_op_defs[req->opcode].async_size);
	req->async_data = kदो_स्मृति(io_op_defs[req->opcode].async_size, GFP_KERNEL);
	वापस req->async_data == शून्य;
पूर्ण

अटल पूर्णांक io_setup_async_rw(काष्ठा io_kiocb *req, स्थिर काष्ठा iovec *iovec,
			     स्थिर काष्ठा iovec *fast_iov,
			     काष्ठा iov_iter *iter, bool क्रमce)
अणु
	अगर (!क्रमce && !io_op_defs[req->opcode].needs_async_setup)
		वापस 0;
	अगर (!req->async_data) अणु
		अगर (io_alloc_async_data(req)) अणु
			kमुक्त(iovec);
			वापस -ENOMEM;
		पूर्ण

		io_req_map_rw(req, iovec, fast_iov, iter);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक io_rw_prep_async(काष्ठा io_kiocb *req, पूर्णांक rw)
अणु
	काष्ठा io_async_rw *iorw = req->async_data;
	काष्ठा iovec *iov = iorw->fast_iov;
	पूर्णांक ret;

	ret = io_import_iovec(rw, req, &iov, &iorw->iter, false);
	अगर (unlikely(ret < 0))
		वापस ret;

	iorw->bytes_करोne = 0;
	iorw->मुक्त_iovec = iov;
	अगर (iov)
		req->flags |= REQ_F_NEED_CLEANUP;
	वापस 0;
पूर्ण

अटल पूर्णांक io_पढ़ो_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (unlikely(!(req->file->f_mode & FMODE_READ)))
		वापस -EBADF;
	वापस io_prep_rw(req, sqe);
पूर्ण

/*
 * This is our रुकोqueue callback handler, रेजिस्टरed through lock_page_async()
 * when we initially tried to करो the IO with the iocb armed our रुकोqueue.
 * This माला_लो called when the page is unlocked, and we generally expect that to
 * happen when the page IO is completed and the page is now uptodate. This will
 * queue a task_work based retry of the operation, attempting to copy the data
 * again. If the latter fails because the page was NOT uptodate, then we will
 * करो a thपढ़ो based blocking retry of the operation. That's the unexpected
 * slow path.
 */
अटल पूर्णांक io_async_buf_func(काष्ठा रुको_queue_entry *रुको, अचिन्हित mode,
			     पूर्णांक sync, व्योम *arg)
अणु
	काष्ठा रुको_page_queue *wpq;
	काष्ठा io_kiocb *req = रुको->निजी;
	काष्ठा रुको_page_key *key = arg;

	wpq = container_of(रुको, काष्ठा रुको_page_queue, रुको);

	अगर (!wake_page_match(wpq, key))
		वापस 0;

	req->rw.kiocb.ki_flags &= ~IOCB_WAITQ;
	list_del_init(&रुको->entry);

	/* submit ref माला_लो dropped, acquire a new one */
	req_ref_get(req);
	io_req_task_queue(req);
	वापस 1;
पूर्ण

/*
 * This controls whether a given IO request should be armed क्रम async page
 * based retry. If we वापस false here, the request is handed to the async
 * worker thपढ़ोs क्रम retry. If we're करोing buffered पढ़ोs on a regular file,
 * we prepare a निजी रुको_page_queue entry and retry the operation. This
 * will either succeed because the page is now uptodate and unlocked, or it
 * will रेजिस्टर a callback when the page is unlocked at IO completion. Through
 * that callback, io_uring uses task_work to setup a retry of the operation.
 * That retry will attempt the buffered पढ़ो again. The retry will generally
 * succeed, or in rare हालs where it fails, we then fall back to using the
 * async worker thपढ़ोs क्रम a blocking retry.
 */
अटल bool io_rw_should_retry(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_async_rw *rw = req->async_data;
	काष्ठा रुको_page_queue *रुको = &rw->wpq;
	काष्ठा kiocb *kiocb = &req->rw.kiocb;

	/* never retry क्रम NOWAIT, we just complete with -EAGAIN */
	अगर (req->flags & REQ_F_NOWAIT)
		वापस false;

	/* Only क्रम buffered IO */
	अगर (kiocb->ki_flags & (IOCB_सूचीECT | IOCB_HIPRI))
		वापस false;

	/*
	 * just use poll अगर we can, and करोn't attempt if the fs doesn't
	 * support callback based unlocks
	 */
	अगर (file_can_poll(req->file) || !(req->file->f_mode & FMODE_BUF_RASYNC))
		वापस false;

	रुको->रुको.func = io_async_buf_func;
	रुको->रुको.निजी = req;
	रुको->रुको.flags = 0;
	INIT_LIST_HEAD(&रुको->रुको.entry);
	kiocb->ki_flags |= IOCB_WAITQ;
	kiocb->ki_flags &= ~IOCB_NOWAIT;
	kiocb->ki_रुकोq = रुको;
	वापस true;
पूर्ण

अटल पूर्णांक io_iter_करो_पढ़ो(काष्ठा io_kiocb *req, काष्ठा iov_iter *iter)
अणु
	अगर (req->file->f_op->पढ़ो_iter)
		वापस call_पढ़ो_iter(req->file, &req->rw.kiocb, iter);
	अन्यथा अगर (req->file->f_op->पढ़ो)
		वापस loop_rw_iter(READ, req, iter);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक io_पढ़ो(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा iovec अंतरभूत_vecs[UIO_FASTIOV], *iovec = अंतरभूत_vecs;
	काष्ठा kiocb *kiocb = &req->rw.kiocb;
	काष्ठा iov_iter __iter, *iter = &__iter;
	काष्ठा io_async_rw *rw = req->async_data;
	sमाप_प्रकार io_size, ret, ret2;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;

	अगर (rw) अणु
		iter = &rw->iter;
		iovec = शून्य;
	पूर्ण अन्यथा अणु
		ret = io_import_iovec(READ, req, &iovec, iter, !क्रमce_nonblock);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	io_size = iov_iter_count(iter);
	req->result = io_size;

	/* Ensure we clear previously set non-block flag */
	अगर (!क्रमce_nonblock)
		kiocb->ki_flags &= ~IOCB_NOWAIT;
	अन्यथा
		kiocb->ki_flags |= IOCB_NOWAIT;

	/* If the file करोesn't support async, just async punt */
	अगर (क्रमce_nonblock && !io_file_supports_async(req, READ)) अणु
		ret = io_setup_async_rw(req, iovec, अंतरभूत_vecs, iter, true);
		वापस ret ?: -EAGAIN;
	पूर्ण

	ret = rw_verअगरy_area(READ, req->file, io_kiocb_ppos(kiocb), io_size);
	अगर (unlikely(ret)) अणु
		kमुक्त(iovec);
		वापस ret;
	पूर्ण

	ret = io_iter_करो_पढ़ो(req, iter);

	अगर (ret == -EAGAIN || (req->flags & REQ_F_REISSUE)) अणु
		req->flags &= ~REQ_F_REISSUE;
		/* IOPOLL retry should happen क्रम io-wq thपढ़ोs */
		अगर (!क्रमce_nonblock && !(req->ctx->flags & IORING_SETUP_IOPOLL))
			जाओ करोne;
		/* no retry on NONBLOCK nor RWF_NOWAIT */
		अगर (req->flags & REQ_F_NOWAIT)
			जाओ करोne;
		/* some हालs will consume bytes even on error वापसs */
		iov_iter_revert(iter, io_size - iov_iter_count(iter));
		ret = 0;
	पूर्ण अन्यथा अगर (ret == -EIOCBQUEUED) अणु
		जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (ret <= 0 || ret == io_size || !क्रमce_nonblock ||
		   (req->flags & REQ_F_NOWAIT) || !(req->flags & REQ_F_ISREG)) अणु
		/* पढ़ो all, failed, alपढ़ोy did sync or करोn't want to retry */
		जाओ करोne;
	पूर्ण

	ret2 = io_setup_async_rw(req, iovec, अंतरभूत_vecs, iter, true);
	अगर (ret2)
		वापस ret2;

	iovec = शून्य;
	rw = req->async_data;
	/* now use our persistent iterator, अगर we aren't alपढ़ोy */
	iter = &rw->iter;

	करो अणु
		io_size -= ret;
		rw->bytes_करोne += ret;
		/* अगर we can retry, करो so with the callbacks armed */
		अगर (!io_rw_should_retry(req)) अणु
			kiocb->ki_flags &= ~IOCB_WAITQ;
			वापस -EAGAIN;
		पूर्ण

		/*
		 * Now retry पढ़ो with the IOCB_WAITQ parts set in the iocb. If
		 * we get -EIOCBQUEUED, then we'll get a notअगरication when the
		 * desired page माला_लो unlocked. We can also get a partial पढ़ो
		 * here, and अगर we करो, then just retry at the new offset.
		 */
		ret = io_iter_करो_पढ़ो(req, iter);
		अगर (ret == -EIOCBQUEUED)
			वापस 0;
		/* we got some bytes, but not all. retry. */
		kiocb->ki_flags &= ~IOCB_WAITQ;
	पूर्ण जबतक (ret > 0 && ret < io_size);
करोne:
	kiocb_करोne(kiocb, ret, issue_flags);
out_मुक्त:
	/* it's faster to check here then delegate to kमुक्त */
	अगर (iovec)
		kमुक्त(iovec);
	वापस 0;
पूर्ण

अटल पूर्णांक io_ग_लिखो_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (unlikely(!(req->file->f_mode & FMODE_WRITE)))
		वापस -EBADF;
	वापस io_prep_rw(req, sqe);
पूर्ण

अटल पूर्णांक io_ग_लिखो(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा iovec अंतरभूत_vecs[UIO_FASTIOV], *iovec = अंतरभूत_vecs;
	काष्ठा kiocb *kiocb = &req->rw.kiocb;
	काष्ठा iov_iter __iter, *iter = &__iter;
	काष्ठा io_async_rw *rw = req->async_data;
	sमाप_प्रकार ret, ret2, io_size;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;

	अगर (rw) अणु
		iter = &rw->iter;
		iovec = शून्य;
	पूर्ण अन्यथा अणु
		ret = io_import_iovec(WRITE, req, &iovec, iter, !क्रमce_nonblock);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	io_size = iov_iter_count(iter);
	req->result = io_size;

	/* Ensure we clear previously set non-block flag */
	अगर (!क्रमce_nonblock)
		kiocb->ki_flags &= ~IOCB_NOWAIT;
	अन्यथा
		kiocb->ki_flags |= IOCB_NOWAIT;

	/* If the file करोesn't support async, just async punt */
	अगर (क्रमce_nonblock && !io_file_supports_async(req, WRITE))
		जाओ copy_iov;

	/* file path करोesn't support NOWAIT क्रम non-direct_IO */
	अगर (क्रमce_nonblock && !(kiocb->ki_flags & IOCB_सूचीECT) &&
	    (req->flags & REQ_F_ISREG))
		जाओ copy_iov;

	ret = rw_verअगरy_area(WRITE, req->file, io_kiocb_ppos(kiocb), io_size);
	अगर (unlikely(ret))
		जाओ out_मुक्त;

	/*
	 * Open-code file_start_ग_लिखो here to grab मुक्तze protection,
	 * which will be released by another thपढ़ो in
	 * io_complete_rw().  Fool lockdep by telling it the lock got
	 * released so that it करोesn't complain about the held lock when
	 * we वापस to userspace.
	 */
	अगर (req->flags & REQ_F_ISREG) अणु
		sb_start_ग_लिखो(file_inode(req->file)->i_sb);
		__sb_ग_लिखोrs_release(file_inode(req->file)->i_sb,
					SB_FREEZE_WRITE);
	पूर्ण
	kiocb->ki_flags |= IOCB_WRITE;

	अगर (req->file->f_op->ग_लिखो_iter)
		ret2 = call_ग_लिखो_iter(req->file, kiocb, iter);
	अन्यथा अगर (req->file->f_op->ग_लिखो)
		ret2 = loop_rw_iter(WRITE, req, iter);
	अन्यथा
		ret2 = -EINVAL;

	अगर (req->flags & REQ_F_REISSUE) अणु
		req->flags &= ~REQ_F_REISSUE;
		ret2 = -EAGAIN;
	पूर्ण

	/*
	 * Raw bdev ग_लिखोs will वापस -EOPNOTSUPP क्रम IOCB_NOWAIT. Just
	 * retry them without IOCB_NOWAIT.
	 */
	अगर (ret2 == -EOPNOTSUPP && (kiocb->ki_flags & IOCB_NOWAIT))
		ret2 = -EAGAIN;
	/* no retry on NONBLOCK nor RWF_NOWAIT */
	अगर (ret2 == -EAGAIN && (req->flags & REQ_F_NOWAIT))
		जाओ करोne;
	अगर (!क्रमce_nonblock || ret2 != -EAGAIN) अणु
		/* IOPOLL retry should happen क्रम io-wq thपढ़ोs */
		अगर ((req->ctx->flags & IORING_SETUP_IOPOLL) && ret2 == -EAGAIN)
			जाओ copy_iov;
करोne:
		kiocb_करोne(kiocb, ret2, issue_flags);
	पूर्ण अन्यथा अणु
copy_iov:
		/* some हालs will consume bytes even on error वापसs */
		iov_iter_revert(iter, io_size - iov_iter_count(iter));
		ret = io_setup_async_rw(req, iovec, अंतरभूत_vecs, iter, false);
		वापस ret ?: -EAGAIN;
	पूर्ण
out_मुक्त:
	/* it's reportedly faster than delegating the null check to kमुक्त() */
	अगर (iovec)
		kमुक्त(iovec);
	वापस ret;
पूर्ण

अटल पूर्णांक io_नामat_prep(काष्ठा io_kiocb *req,
			    स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_नाम *ren = &req->नाम;
	स्थिर अक्षर __user *oldf, *newf;

	अगर (unlikely(req->flags & REQ_F_FIXED_खाता))
		वापस -EBADF;

	ren->old_dfd = READ_ONCE(sqe->fd);
	oldf = u64_to_user_ptr(READ_ONCE(sqe->addr));
	newf = u64_to_user_ptr(READ_ONCE(sqe->addr2));
	ren->new_dfd = READ_ONCE(sqe->len);
	ren->flags = READ_ONCE(sqe->नाम_flags);

	ren->oldpath = getname(oldf);
	अगर (IS_ERR(ren->oldpath))
		वापस PTR_ERR(ren->oldpath);

	ren->newpath = getname(newf);
	अगर (IS_ERR(ren->newpath)) अणु
		putname(ren->oldpath);
		वापस PTR_ERR(ren->newpath);
	पूर्ण

	req->flags |= REQ_F_NEED_CLEANUP;
	वापस 0;
पूर्ण

अटल पूर्णांक io_नामat(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_नाम *ren = &req->नाम;
	पूर्णांक ret;

	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	ret = करो_नामat2(ren->old_dfd, ren->oldpath, ren->new_dfd,
				ren->newpath, ren->flags);

	req->flags &= ~REQ_F_NEED_CLEANUP;
	अगर (ret < 0)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक io_unlinkat_prep(काष्ठा io_kiocb *req,
			    स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_unlink *un = &req->unlink;
	स्थिर अक्षर __user *fname;

	अगर (unlikely(req->flags & REQ_F_FIXED_खाता))
		वापस -EBADF;

	un->dfd = READ_ONCE(sqe->fd);

	un->flags = READ_ONCE(sqe->unlink_flags);
	अगर (un->flags & ~AT_REMOVEसूची)
		वापस -EINVAL;

	fname = u64_to_user_ptr(READ_ONCE(sqe->addr));
	un->filename = getname(fname);
	अगर (IS_ERR(un->filename))
		वापस PTR_ERR(un->filename);

	req->flags |= REQ_F_NEED_CLEANUP;
	वापस 0;
पूर्ण

अटल पूर्णांक io_unlinkat(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_unlink *un = &req->unlink;
	पूर्णांक ret;

	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	अगर (un->flags & AT_REMOVEसूची)
		ret = करो_सूची_हटाओ(un->dfd, un->filename);
	अन्यथा
		ret = करो_unlinkat(un->dfd, un->filename);

	req->flags &= ~REQ_F_NEED_CLEANUP;
	अगर (ret < 0)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक io_shutकरोwn_prep(काष्ठा io_kiocb *req,
			    स्थिर काष्ठा io_uring_sqe *sqe)
अणु
#अगर defined(CONFIG_NET)
	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->off || sqe->addr || sqe->rw_flags ||
	    sqe->buf_index)
		वापस -EINVAL;

	req->shutकरोwn.how = READ_ONCE(sqe->len);
	वापस 0;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक io_shutकरोwn(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
#अगर defined(CONFIG_NET)
	काष्ठा socket *sock;
	पूर्णांक ret;

	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	sock = sock_from_file(req->file);
	अगर (unlikely(!sock))
		वापस -ENOTSOCK;

	ret = __sys_shutकरोwn_sock(sock, req->shutकरोwn.how);
	अगर (ret < 0)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __io_splice_prep(काष्ठा io_kiocb *req,
			    स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_splice* sp = &req->splice;
	अचिन्हित पूर्णांक valid_flags = SPLICE_F_FD_IN_FIXED | SPLICE_F_ALL;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;

	sp->file_in = शून्य;
	sp->len = READ_ONCE(sqe->len);
	sp->flags = READ_ONCE(sqe->splice_flags);

	अगर (unlikely(sp->flags & ~valid_flags))
		वापस -EINVAL;

	sp->file_in = io_file_get(शून्य, req, READ_ONCE(sqe->splice_fd_in),
				  (sp->flags & SPLICE_F_FD_IN_FIXED));
	अगर (!sp->file_in)
		वापस -EBADF;
	req->flags |= REQ_F_NEED_CLEANUP;
	वापस 0;
पूर्ण

अटल पूर्णांक io_tee_prep(काष्ठा io_kiocb *req,
		       स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (READ_ONCE(sqe->splice_off_in) || READ_ONCE(sqe->off))
		वापस -EINVAL;
	वापस __io_splice_prep(req, sqe);
पूर्ण

अटल पूर्णांक io_tee(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_splice *sp = &req->splice;
	काष्ठा file *in = sp->file_in;
	काष्ठा file *out = sp->file_out;
	अचिन्हित पूर्णांक flags = sp->flags & ~SPLICE_F_FD_IN_FIXED;
	दीर्घ ret = 0;

	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;
	अगर (sp->len)
		ret = करो_tee(in, out, sp->len, flags);

	अगर (!(sp->flags & SPLICE_F_FD_IN_FIXED))
		io_put_file(in);
	req->flags &= ~REQ_F_NEED_CLEANUP;

	अगर (ret != sp->len)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक io_splice_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_splice* sp = &req->splice;

	sp->off_in = READ_ONCE(sqe->splice_off_in);
	sp->off_out = READ_ONCE(sqe->off);
	वापस __io_splice_prep(req, sqe);
पूर्ण

अटल पूर्णांक io_splice(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_splice *sp = &req->splice;
	काष्ठा file *in = sp->file_in;
	काष्ठा file *out = sp->file_out;
	अचिन्हित पूर्णांक flags = sp->flags & ~SPLICE_F_FD_IN_FIXED;
	loff_t *poff_in, *poff_out;
	दीर्घ ret = 0;

	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	poff_in = (sp->off_in == -1) ? शून्य : &sp->off_in;
	poff_out = (sp->off_out == -1) ? शून्य : &sp->off_out;

	अगर (sp->len)
		ret = करो_splice(in, poff_in, out, poff_out, sp->len, flags);

	अगर (!(sp->flags & SPLICE_F_FD_IN_FIXED))
		io_put_file(in);
	req->flags &= ~REQ_F_NEED_CLEANUP;

	अगर (ret != sp->len)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
पूर्ण

/*
 * IORING_OP_NOP just posts a completion event, nothing अन्यथा.
 */
अटल पूर्णांक io_nop(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	अगर (unlikely(ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;

	__io_req_complete(req, issue_flags, 0, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक io_fsync_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	अगर (!req->file)
		वापस -EBADF;

	अगर (unlikely(ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (unlikely(sqe->addr || sqe->ioprio || sqe->buf_index))
		वापस -EINVAL;

	req->sync.flags = READ_ONCE(sqe->fsync_flags);
	अगर (unlikely(req->sync.flags & ~IORING_FSYNC_DATASYNC))
		वापस -EINVAL;

	req->sync.off = READ_ONCE(sqe->off);
	req->sync.len = READ_ONCE(sqe->len);
	वापस 0;
पूर्ण

अटल पूर्णांक io_fsync(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	loff_t end = req->sync.off + req->sync.len;
	पूर्णांक ret;

	/* fsync always requires a blocking context */
	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	ret = vfs_fsync_range(req->file, req->sync.off,
				end > 0 ? end : Lदीर्घ_उच्च,
				req->sync.flags & IORING_FSYNC_DATASYNC);
	अगर (ret < 0)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक io_fallocate_prep(काष्ठा io_kiocb *req,
			     स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (sqe->ioprio || sqe->buf_index || sqe->rw_flags)
		वापस -EINVAL;
	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;

	req->sync.off = READ_ONCE(sqe->off);
	req->sync.len = READ_ONCE(sqe->addr);
	req->sync.mode = READ_ONCE(sqe->len);
	वापस 0;
पूर्ण

अटल पूर्णांक io_fallocate(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	पूर्णांक ret;

	/* fallocate always requiring blocking context */
	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;
	ret = vfs_fallocate(req->file, req->sync.mode, req->sync.off,
				req->sync.len);
	अगर (ret < 0)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक __io_खोलोat_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	स्थिर अक्षर __user *fname;
	पूर्णांक ret;

	अगर (unlikely(sqe->ioprio || sqe->buf_index))
		वापस -EINVAL;
	अगर (unlikely(req->flags & REQ_F_FIXED_खाता))
		वापस -EBADF;

	/* खोलो.how should be alपढ़ोy initialised */
	अगर (!(req->खोलो.how.flags & O_PATH) && क्रमce_o_largefile())
		req->खोलो.how.flags |= O_LARGEखाता;

	req->खोलो.dfd = READ_ONCE(sqe->fd);
	fname = u64_to_user_ptr(READ_ONCE(sqe->addr));
	req->खोलो.filename = getname(fname);
	अगर (IS_ERR(req->खोलो.filename)) अणु
		ret = PTR_ERR(req->खोलो.filename);
		req->खोलो.filename = शून्य;
		वापस ret;
	पूर्ण
	req->खोलो.nofile = rlimit(RLIMIT_NOखाता);
	req->flags |= REQ_F_NEED_CLEANUP;
	वापस 0;
पूर्ण

अटल पूर्णांक io_खोलोat_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	u64 flags, mode;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	mode = READ_ONCE(sqe->len);
	flags = READ_ONCE(sqe->खोलो_flags);
	req->खोलो.how = build_खोलो_how(flags, mode);
	वापस __io_खोलोat_prep(req, sqe);
पूर्ण

अटल पूर्णांक io_खोलोat2_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा खोलो_how __user *how;
	माप_प्रकार len;
	पूर्णांक ret;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	how = u64_to_user_ptr(READ_ONCE(sqe->addr2));
	len = READ_ONCE(sqe->len);
	अगर (len < OPEN_HOW_SIZE_VER0)
		वापस -EINVAL;

	ret = copy_काष्ठा_from_user(&req->खोलो.how, माप(req->खोलो.how), how,
					len);
	अगर (ret)
		वापस ret;

	वापस __io_खोलोat_prep(req, sqe);
पूर्ण

अटल पूर्णांक io_खोलोat2(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा खोलो_flags op;
	काष्ठा file *file;
	bool nonblock_set;
	bool resolve_nonblock;
	पूर्णांक ret;

	ret = build_खोलो_flags(&req->खोलो.how, &op);
	अगर (ret)
		जाओ err;
	nonblock_set = op.खोलो_flag & O_NONBLOCK;
	resolve_nonblock = req->खोलो.how.resolve & RESOLVE_CACHED;
	अगर (issue_flags & IO_URING_F_NONBLOCK) अणु
		/*
		 * Don't bother trying क्रम O_TRUNC, O_CREAT, or O_TMPखाता खोलो,
		 * it'll always -EAGAIN
		 */
		अगर (req->खोलो.how.flags & (O_TRUNC | O_CREAT | O_TMPखाता))
			वापस -EAGAIN;
		op.lookup_flags |= LOOKUP_CACHED;
		op.खोलो_flag |= O_NONBLOCK;
	पूर्ण

	ret = __get_unused_fd_flags(req->खोलो.how.flags, req->खोलो.nofile);
	अगर (ret < 0)
		जाओ err;

	file = करो_filp_खोलो(req->खोलो.dfd, req->खोलो.filename, &op);
	/* only retry अगर RESOLVE_CACHED wasn't alपढ़ोy set by application */
	अगर ((!resolve_nonblock && (issue_flags & IO_URING_F_NONBLOCK)) &&
	    file == ERR_PTR(-EAGAIN)) अणु
		/*
		 * We could hang on to this 'fd', but seems like marginal
		 * gain क्रम something that is now known to be a slower path.
		 * So just put it, and we'll get a new one when we retry.
		 */
		put_unused_fd(ret);
		वापस -EAGAIN;
	पूर्ण

	अगर (IS_ERR(file)) अणु
		put_unused_fd(ret);
		ret = PTR_ERR(file);
	पूर्ण अन्यथा अणु
		अगर ((issue_flags & IO_URING_F_NONBLOCK) && !nonblock_set)
			file->f_flags &= ~O_NONBLOCK;
		fsnotअगरy_खोलो(file);
		fd_install(ret, file);
	पूर्ण
err:
	putname(req->खोलो.filename);
	req->flags &= ~REQ_F_NEED_CLEANUP;
	अगर (ret < 0)
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक io_खोलोat(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	वापस io_खोलोat2(req, issue_flags);
पूर्ण

अटल पूर्णांक io_हटाओ_buffers_prep(काष्ठा io_kiocb *req,
				  स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_provide_buf *p = &req->pbuf;
	u64 पंचांगp;

	अगर (sqe->ioprio || sqe->rw_flags || sqe->addr || sqe->len || sqe->off)
		वापस -EINVAL;

	पंचांगp = READ_ONCE(sqe->fd);
	अगर (!पंचांगp || पंचांगp > अच_लघु_उच्च)
		वापस -EINVAL;

	स_रखो(p, 0, माप(*p));
	p->nbufs = पंचांगp;
	p->bgid = READ_ONCE(sqe->buf_group);
	वापस 0;
पूर्ण

अटल पूर्णांक __io_हटाओ_buffers(काष्ठा io_ring_ctx *ctx, काष्ठा io_buffer *buf,
			       पूर्णांक bgid, अचिन्हित nbufs)
अणु
	अचिन्हित i = 0;

	/* shouldn't happen */
	अगर (!nbufs)
		वापस 0;

	/* the head kbuf is the list itself */
	जबतक (!list_empty(&buf->list)) अणु
		काष्ठा io_buffer *nxt;

		nxt = list_first_entry(&buf->list, काष्ठा io_buffer, list);
		list_del(&nxt->list);
		kमुक्त(nxt);
		अगर (++i == nbufs)
			वापस i;
	पूर्ण
	i++;
	kमुक्त(buf);
	xa_erase(&ctx->io_buffers, bgid);

	वापस i;
पूर्ण

अटल पूर्णांक io_हटाओ_buffers(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_provide_buf *p = &req->pbuf;
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_buffer *head;
	पूर्णांक ret = 0;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;

	io_ring_submit_lock(ctx, !क्रमce_nonblock);

	lockdep_निश्चित_held(&ctx->uring_lock);

	ret = -ENOENT;
	head = xa_load(&ctx->io_buffers, p->bgid);
	अगर (head)
		ret = __io_हटाओ_buffers(ctx, head, p->bgid, p->nbufs);
	अगर (ret < 0)
		req_set_fail_links(req);

	/* complete beक्रमe unlock, IOPOLL may need the lock */
	__io_req_complete(req, issue_flags, ret, 0);
	io_ring_submit_unlock(ctx, !क्रमce_nonblock);
	वापस 0;
पूर्ण

अटल पूर्णांक io_provide_buffers_prep(काष्ठा io_kiocb *req,
				   स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अचिन्हित दीर्घ size, पंचांगp_check;
	काष्ठा io_provide_buf *p = &req->pbuf;
	u64 पंचांगp;

	अगर (sqe->ioprio || sqe->rw_flags)
		वापस -EINVAL;

	पंचांगp = READ_ONCE(sqe->fd);
	अगर (!पंचांगp || पंचांगp > अच_लघु_उच्च)
		वापस -E2BIG;
	p->nbufs = पंचांगp;
	p->addr = READ_ONCE(sqe->addr);
	p->len = READ_ONCE(sqe->len);

	अगर (check_mul_overflow((अचिन्हित दीर्घ)p->len, (अचिन्हित दीर्घ)p->nbufs,
				&size))
		वापस -EOVERFLOW;
	अगर (check_add_overflow((अचिन्हित दीर्घ)p->addr, size, &पंचांगp_check))
		वापस -EOVERFLOW;

	size = (अचिन्हित दीर्घ)p->len * p->nbufs;
	अगर (!access_ok(u64_to_user_ptr(p->addr), size))
		वापस -EFAULT;

	p->bgid = READ_ONCE(sqe->buf_group);
	पंचांगp = READ_ONCE(sqe->off);
	अगर (पंचांगp > अच_लघु_उच्च)
		वापस -E2BIG;
	p->bid = पंचांगp;
	वापस 0;
पूर्ण

अटल पूर्णांक io_add_buffers(काष्ठा io_provide_buf *pbuf, काष्ठा io_buffer **head)
अणु
	काष्ठा io_buffer *buf;
	u64 addr = pbuf->addr;
	पूर्णांक i, bid = pbuf->bid;

	क्रम (i = 0; i < pbuf->nbufs; i++) अणु
		buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
		अगर (!buf)
			अवरोध;

		buf->addr = addr;
		buf->len = min_t(__u32, pbuf->len, MAX_RW_COUNT);
		buf->bid = bid;
		addr += pbuf->len;
		bid++;
		अगर (!*head) अणु
			INIT_LIST_HEAD(&buf->list);
			*head = buf;
		पूर्ण अन्यथा अणु
			list_add_tail(&buf->list, &(*head)->list);
		पूर्ण
	पूर्ण

	वापस i ? i : -ENOMEM;
पूर्ण

अटल पूर्णांक io_provide_buffers(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_provide_buf *p = &req->pbuf;
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_buffer *head, *list;
	पूर्णांक ret = 0;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;

	io_ring_submit_lock(ctx, !क्रमce_nonblock);

	lockdep_निश्चित_held(&ctx->uring_lock);

	list = head = xa_load(&ctx->io_buffers, p->bgid);

	ret = io_add_buffers(p, &head);
	अगर (ret >= 0 && !list) अणु
		ret = xa_insert(&ctx->io_buffers, p->bgid, head, GFP_KERNEL);
		अगर (ret < 0)
			__io_हटाओ_buffers(ctx, head, p->bgid, -1U);
	पूर्ण
	अगर (ret < 0)
		req_set_fail_links(req);
	/* complete beक्रमe unlock, IOPOLL may need the lock */
	__io_req_complete(req, issue_flags, ret, 0);
	io_ring_submit_unlock(ctx, !क्रमce_nonblock);
	वापस 0;
पूर्ण

अटल पूर्णांक io_epoll_ctl_prep(काष्ठा io_kiocb *req,
			     स्थिर काष्ठा io_uring_sqe *sqe)
अणु
#अगर defined(CONFIG_EPOLL)
	अगर (sqe->ioprio || sqe->buf_index)
		वापस -EINVAL;
	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;

	req->epoll.epfd = READ_ONCE(sqe->fd);
	req->epoll.op = READ_ONCE(sqe->len);
	req->epoll.fd = READ_ONCE(sqe->off);

	अगर (ep_op_has_event(req->epoll.op)) अणु
		काष्ठा epoll_event __user *ev;

		ev = u64_to_user_ptr(READ_ONCE(sqe->addr));
		अगर (copy_from_user(&req->epoll.event, ev, माप(*ev)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक io_epoll_ctl(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
#अगर defined(CONFIG_EPOLL)
	काष्ठा io_epoll *ie = &req->epoll;
	पूर्णांक ret;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;

	ret = करो_epoll_ctl(ie->epfd, ie->op, ie->fd, &ie->event, क्रमce_nonblock);
	अगर (क्रमce_nonblock && ret == -EAGAIN)
		वापस -EAGAIN;

	अगर (ret < 0)
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक io_madvise_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
#अगर defined(CONFIG_ADVISE_SYSCALLS) && defined(CONFIG_MMU)
	अगर (sqe->ioprio || sqe->buf_index || sqe->off)
		वापस -EINVAL;
	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;

	req->madvise.addr = READ_ONCE(sqe->addr);
	req->madvise.len = READ_ONCE(sqe->len);
	req->madvise.advice = READ_ONCE(sqe->fadvise_advice);
	वापस 0;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक io_madvise(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
#अगर defined(CONFIG_ADVISE_SYSCALLS) && defined(CONFIG_MMU)
	काष्ठा io_madvise *ma = &req->madvise;
	पूर्णांक ret;

	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	ret = करो_madvise(current->mm, ma->addr, ma->len, ma->advice);
	अगर (ret < 0)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक io_fadvise_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (sqe->ioprio || sqe->buf_index || sqe->addr)
		वापस -EINVAL;
	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;

	req->fadvise.offset = READ_ONCE(sqe->off);
	req->fadvise.len = READ_ONCE(sqe->len);
	req->fadvise.advice = READ_ONCE(sqe->fadvise_advice);
	वापस 0;
पूर्ण

अटल पूर्णांक io_fadvise(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_fadvise *fa = &req->fadvise;
	पूर्णांक ret;

	अगर (issue_flags & IO_URING_F_NONBLOCK) अणु
		चयन (fa->advice) अणु
		हाल POSIX_FADV_NORMAL:
		हाल POSIX_FADV_RANDOM:
		हाल POSIX_FADV_SEQUENTIAL:
			अवरोध;
		शेष:
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	ret = vfs_fadvise(req->file, fa->offset, fa->len, fa->advice);
	अगर (ret < 0)
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक io_statx_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->buf_index)
		वापस -EINVAL;
	अगर (req->flags & REQ_F_FIXED_खाता)
		वापस -EBADF;

	req->statx.dfd = READ_ONCE(sqe->fd);
	req->statx.mask = READ_ONCE(sqe->len);
	req->statx.filename = u64_to_user_ptr(READ_ONCE(sqe->addr));
	req->statx.buffer = u64_to_user_ptr(READ_ONCE(sqe->addr2));
	req->statx.flags = READ_ONCE(sqe->statx_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक io_statx(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_statx *ctx = &req->statx;
	पूर्णांक ret;

	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	ret = करो_statx(ctx->dfd, ctx->filename, ctx->flags, ctx->mask,
		       ctx->buffer);

	अगर (ret < 0)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक io_बंद_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->off || sqe->addr || sqe->len ||
	    sqe->rw_flags || sqe->buf_index)
		वापस -EINVAL;
	अगर (req->flags & REQ_F_FIXED_खाता)
		वापस -EBADF;

	req->बंद.fd = READ_ONCE(sqe->fd);
	वापस 0;
पूर्ण

अटल पूर्णांक io_बंद(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा files_काष्ठा *files = current->files;
	काष्ठा io_बंद *बंद = &req->बंद;
	काष्ठा fdtable *fdt;
	काष्ठा file *file = शून्य;
	पूर्णांक ret = -EBADF;

	spin_lock(&files->file_lock);
	fdt = files_fdtable(files);
	अगर (बंद->fd >= fdt->max_fds) अणु
		spin_unlock(&files->file_lock);
		जाओ err;
	पूर्ण
	file = fdt->fd[बंद->fd];
	अगर (!file || file->f_op == &io_uring_fops) अणु
		spin_unlock(&files->file_lock);
		file = शून्य;
		जाओ err;
	पूर्ण

	/* अगर the file has a flush method, be safe and punt to async */
	अगर (file->f_op->flush && (issue_flags & IO_URING_F_NONBLOCK)) अणु
		spin_unlock(&files->file_lock);
		वापस -EAGAIN;
	पूर्ण

	ret = __बंद_fd_get_file(बंद->fd, &file);
	spin_unlock(&files->file_lock);
	अगर (ret < 0) अणु
		अगर (ret == -ENOENT)
			ret = -EBADF;
		जाओ err;
	पूर्ण

	/* No ->flush() or alपढ़ोy async, safely बंद from here */
	ret = filp_बंद(file, current->files);
err:
	अगर (ret < 0)
		req_set_fail_links(req);
	अगर (file)
		fput(file);
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक io_sfr_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	अगर (unlikely(ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (unlikely(sqe->addr || sqe->ioprio || sqe->buf_index))
		वापस -EINVAL;

	req->sync.off = READ_ONCE(sqe->off);
	req->sync.len = READ_ONCE(sqe->len);
	req->sync.flags = READ_ONCE(sqe->sync_range_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक io_sync_file_range(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	पूर्णांक ret;

	/* sync_file_range always requires a blocking context */
	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	ret = sync_file_range(req->file, req->sync.off, req->sync.len,
				req->sync.flags);
	अगर (ret < 0)
		req_set_fail_links(req);
	io_req_complete(req, ret);
	वापस 0;
पूर्ण

#अगर defined(CONFIG_NET)
अटल पूर्णांक io_setup_async_msg(काष्ठा io_kiocb *req,
			      काष्ठा io_async_msghdr *kmsg)
अणु
	काष्ठा io_async_msghdr *async_msg = req->async_data;

	अगर (async_msg)
		वापस -EAGAIN;
	अगर (io_alloc_async_data(req)) अणु
		kमुक्त(kmsg->मुक्त_iov);
		वापस -ENOMEM;
	पूर्ण
	async_msg = req->async_data;
	req->flags |= REQ_F_NEED_CLEANUP;
	स_नकल(async_msg, kmsg, माप(*kmsg));
	async_msg->msg.msg_name = &async_msg->addr;
	/* अगर were using fast_iov, set it to the new one */
	अगर (!async_msg->मुक्त_iov)
		async_msg->msg.msg_iter.iov = async_msg->fast_iov;

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक io_sendmsg_copy_hdr(काष्ठा io_kiocb *req,
			       काष्ठा io_async_msghdr *iomsg)
अणु
	iomsg->msg.msg_name = &iomsg->addr;
	iomsg->मुक्त_iov = iomsg->fast_iov;
	वापस sendmsg_copy_msghdr(&iomsg->msg, req->sr_msg.umsg,
				   req->sr_msg.msg_flags, &iomsg->मुक्त_iov);
पूर्ण

अटल पूर्णांक io_sendmsg_prep_async(काष्ठा io_kiocb *req)
अणु
	पूर्णांक ret;

	ret = io_sendmsg_copy_hdr(req, req->async_data);
	अगर (!ret)
		req->flags |= REQ_F_NEED_CLEANUP;
	वापस ret;
पूर्ण

अटल पूर्णांक io_sendmsg_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_sr_msg *sr = &req->sr_msg;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;

	sr->umsg = u64_to_user_ptr(READ_ONCE(sqe->addr));
	sr->len = READ_ONCE(sqe->len);
	sr->msg_flags = READ_ONCE(sqe->msg_flags) | MSG_NOSIGNAL;
	अगर (sr->msg_flags & MSG_DONTWAIT)
		req->flags |= REQ_F_NOWAIT;

#अगर_घोषित CONFIG_COMPAT
	अगर (req->ctx->compat)
		sr->msg_flags |= MSG_CMSG_COMPAT;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक io_sendmsg(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_async_msghdr iomsg, *kmsg;
	काष्ठा socket *sock;
	अचिन्हित flags;
	पूर्णांक min_ret = 0;
	पूर्णांक ret;

	sock = sock_from_file(req->file);
	अगर (unlikely(!sock))
		वापस -ENOTSOCK;

	kmsg = req->async_data;
	अगर (!kmsg) अणु
		ret = io_sendmsg_copy_hdr(req, &iomsg);
		अगर (ret)
			वापस ret;
		kmsg = &iomsg;
	पूर्ण

	flags = req->sr_msg.msg_flags;
	अगर (issue_flags & IO_URING_F_NONBLOCK)
		flags |= MSG_DONTWAIT;
	अगर (flags & MSG_WAITALL)
		min_ret = iov_iter_count(&kmsg->msg.msg_iter);

	ret = __sys_sendmsg_sock(sock, &kmsg->msg, flags);
	अगर ((issue_flags & IO_URING_F_NONBLOCK) && ret == -EAGAIN)
		वापस io_setup_async_msg(req, kmsg);
	अगर (ret == -ERESTARTSYS)
		ret = -EINTR;

	/* fast path, check क्रम non-शून्य to aव्योम function call */
	अगर (kmsg->मुक्त_iov)
		kमुक्त(kmsg->मुक्त_iov);
	req->flags &= ~REQ_F_NEED_CLEANUP;
	अगर (ret < min_ret)
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक io_send(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_sr_msg *sr = &req->sr_msg;
	काष्ठा msghdr msg;
	काष्ठा iovec iov;
	काष्ठा socket *sock;
	अचिन्हित flags;
	पूर्णांक min_ret = 0;
	पूर्णांक ret;

	sock = sock_from_file(req->file);
	अगर (unlikely(!sock))
		वापस -ENOTSOCK;

	ret = import_single_range(WRITE, sr->buf, sr->len, &iov, &msg.msg_iter);
	अगर (unlikely(ret))
		वापस ret;

	msg.msg_name = शून्य;
	msg.msg_control = शून्य;
	msg.msg_controllen = 0;
	msg.msg_namelen = 0;

	flags = req->sr_msg.msg_flags;
	अगर (issue_flags & IO_URING_F_NONBLOCK)
		flags |= MSG_DONTWAIT;
	अगर (flags & MSG_WAITALL)
		min_ret = iov_iter_count(&msg.msg_iter);

	msg.msg_flags = flags;
	ret = sock_sendmsg(sock, &msg);
	अगर ((issue_flags & IO_URING_F_NONBLOCK) && ret == -EAGAIN)
		वापस -EAGAIN;
	अगर (ret == -ERESTARTSYS)
		ret = -EINTR;

	अगर (ret < min_ret)
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक __io_recvmsg_copy_hdr(काष्ठा io_kiocb *req,
				 काष्ठा io_async_msghdr *iomsg)
अणु
	काष्ठा io_sr_msg *sr = &req->sr_msg;
	काष्ठा iovec __user *uiov;
	माप_प्रकार iov_len;
	पूर्णांक ret;

	ret = __copy_msghdr_from_user(&iomsg->msg, sr->umsg,
					&iomsg->uaddr, &uiov, &iov_len);
	अगर (ret)
		वापस ret;

	अगर (req->flags & REQ_F_BUFFER_SELECT) अणु
		अगर (iov_len > 1)
			वापस -EINVAL;
		अगर (copy_from_user(iomsg->fast_iov, uiov, माप(*uiov)))
			वापस -EFAULT;
		sr->len = iomsg->fast_iov[0].iov_len;
		iomsg->मुक्त_iov = शून्य;
	पूर्ण अन्यथा अणु
		iomsg->मुक्त_iov = iomsg->fast_iov;
		ret = __import_iovec(READ, uiov, iov_len, UIO_FASTIOV,
				     &iomsg->मुक्त_iov, &iomsg->msg.msg_iter,
				     false);
		अगर (ret > 0)
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक __io_compat_recvmsg_copy_hdr(काष्ठा io_kiocb *req,
					काष्ठा io_async_msghdr *iomsg)
अणु
	काष्ठा io_sr_msg *sr = &req->sr_msg;
	काष्ठा compat_iovec __user *uiov;
	compat_uptr_t ptr;
	compat_माप_प्रकार len;
	पूर्णांक ret;

	ret = __get_compat_msghdr(&iomsg->msg, sr->umsg_compat, &iomsg->uaddr,
				  &ptr, &len);
	अगर (ret)
		वापस ret;

	uiov = compat_ptr(ptr);
	अगर (req->flags & REQ_F_BUFFER_SELECT) अणु
		compat_sमाप_प्रकार clen;

		अगर (len > 1)
			वापस -EINVAL;
		अगर (!access_ok(uiov, माप(*uiov)))
			वापस -EFAULT;
		अगर (__get_user(clen, &uiov->iov_len))
			वापस -EFAULT;
		अगर (clen < 0)
			वापस -EINVAL;
		sr->len = clen;
		iomsg->मुक्त_iov = शून्य;
	पूर्ण अन्यथा अणु
		iomsg->मुक्त_iov = iomsg->fast_iov;
		ret = __import_iovec(READ, (काष्ठा iovec __user *)uiov, len,
				   UIO_FASTIOV, &iomsg->मुक्त_iov,
				   &iomsg->msg.msg_iter, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक io_recvmsg_copy_hdr(काष्ठा io_kiocb *req,
			       काष्ठा io_async_msghdr *iomsg)
अणु
	iomsg->msg.msg_name = &iomsg->addr;

#अगर_घोषित CONFIG_COMPAT
	अगर (req->ctx->compat)
		वापस __io_compat_recvmsg_copy_hdr(req, iomsg);
#पूर्ण_अगर

	वापस __io_recvmsg_copy_hdr(req, iomsg);
पूर्ण

अटल काष्ठा io_buffer *io_recv_buffer_select(काष्ठा io_kiocb *req,
					       bool needs_lock)
अणु
	काष्ठा io_sr_msg *sr = &req->sr_msg;
	काष्ठा io_buffer *kbuf;

	kbuf = io_buffer_select(req, &sr->len, sr->bgid, sr->kbuf, needs_lock);
	अगर (IS_ERR(kbuf))
		वापस kbuf;

	sr->kbuf = kbuf;
	req->flags |= REQ_F_BUFFER_SELECTED;
	वापस kbuf;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक io_put_recv_kbuf(काष्ठा io_kiocb *req)
अणु
	वापस io_put_kbuf(req, req->sr_msg.kbuf);
पूर्ण

अटल पूर्णांक io_recvmsg_prep_async(काष्ठा io_kiocb *req)
अणु
	पूर्णांक ret;

	ret = io_recvmsg_copy_hdr(req, req->async_data);
	अगर (!ret)
		req->flags |= REQ_F_NEED_CLEANUP;
	वापस ret;
पूर्ण

अटल पूर्णांक io_recvmsg_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_sr_msg *sr = &req->sr_msg;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;

	sr->umsg = u64_to_user_ptr(READ_ONCE(sqe->addr));
	sr->len = READ_ONCE(sqe->len);
	sr->bgid = READ_ONCE(sqe->buf_group);
	sr->msg_flags = READ_ONCE(sqe->msg_flags) | MSG_NOSIGNAL;
	अगर (sr->msg_flags & MSG_DONTWAIT)
		req->flags |= REQ_F_NOWAIT;

#अगर_घोषित CONFIG_COMPAT
	अगर (req->ctx->compat)
		sr->msg_flags |= MSG_CMSG_COMPAT;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक io_recvmsg(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_async_msghdr iomsg, *kmsg;
	काष्ठा socket *sock;
	काष्ठा io_buffer *kbuf;
	अचिन्हित flags;
	पूर्णांक min_ret = 0;
	पूर्णांक ret, cflags = 0;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;

	sock = sock_from_file(req->file);
	अगर (unlikely(!sock))
		वापस -ENOTSOCK;

	kmsg = req->async_data;
	अगर (!kmsg) अणु
		ret = io_recvmsg_copy_hdr(req, &iomsg);
		अगर (ret)
			वापस ret;
		kmsg = &iomsg;
	पूर्ण

	अगर (req->flags & REQ_F_BUFFER_SELECT) अणु
		kbuf = io_recv_buffer_select(req, !क्रमce_nonblock);
		अगर (IS_ERR(kbuf))
			वापस PTR_ERR(kbuf);
		kmsg->fast_iov[0].iov_base = u64_to_user_ptr(kbuf->addr);
		kmsg->fast_iov[0].iov_len = req->sr_msg.len;
		iov_iter_init(&kmsg->msg.msg_iter, READ, kmsg->fast_iov,
				1, req->sr_msg.len);
	पूर्ण

	flags = req->sr_msg.msg_flags;
	अगर (क्रमce_nonblock)
		flags |= MSG_DONTWAIT;
	अगर (flags & MSG_WAITALL)
		min_ret = iov_iter_count(&kmsg->msg.msg_iter);

	ret = __sys_recvmsg_sock(sock, &kmsg->msg, req->sr_msg.umsg,
					kmsg->uaddr, flags);
	अगर (क्रमce_nonblock && ret == -EAGAIN)
		वापस io_setup_async_msg(req, kmsg);
	अगर (ret == -ERESTARTSYS)
		ret = -EINTR;

	अगर (req->flags & REQ_F_BUFFER_SELECTED)
		cflags = io_put_recv_kbuf(req);
	/* fast path, check क्रम non-शून्य to aव्योम function call */
	अगर (kmsg->मुक्त_iov)
		kमुक्त(kmsg->मुक्त_iov);
	req->flags &= ~REQ_F_NEED_CLEANUP;
	अगर (ret < min_ret || ((flags & MSG_WAITALL) && (kmsg->msg.msg_flags & (MSG_TRUNC | MSG_CTRUNC))))
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, cflags);
	वापस 0;
पूर्ण

अटल पूर्णांक io_recv(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_buffer *kbuf;
	काष्ठा io_sr_msg *sr = &req->sr_msg;
	काष्ठा msghdr msg;
	व्योम __user *buf = sr->buf;
	काष्ठा socket *sock;
	काष्ठा iovec iov;
	अचिन्हित flags;
	पूर्णांक min_ret = 0;
	पूर्णांक ret, cflags = 0;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;

	sock = sock_from_file(req->file);
	अगर (unlikely(!sock))
		वापस -ENOTSOCK;

	अगर (req->flags & REQ_F_BUFFER_SELECT) अणु
		kbuf = io_recv_buffer_select(req, !क्रमce_nonblock);
		अगर (IS_ERR(kbuf))
			वापस PTR_ERR(kbuf);
		buf = u64_to_user_ptr(kbuf->addr);
	पूर्ण

	ret = import_single_range(READ, buf, sr->len, &iov, &msg.msg_iter);
	अगर (unlikely(ret))
		जाओ out_मुक्त;

	msg.msg_name = शून्य;
	msg.msg_control = शून्य;
	msg.msg_controllen = 0;
	msg.msg_namelen = 0;
	msg.msg_iocb = शून्य;
	msg.msg_flags = 0;

	flags = req->sr_msg.msg_flags;
	अगर (क्रमce_nonblock)
		flags |= MSG_DONTWAIT;
	अगर (flags & MSG_WAITALL)
		min_ret = iov_iter_count(&msg.msg_iter);

	ret = sock_recvmsg(sock, &msg, flags);
	अगर (क्रमce_nonblock && ret == -EAGAIN)
		वापस -EAGAIN;
	अगर (ret == -ERESTARTSYS)
		ret = -EINTR;
out_मुक्त:
	अगर (req->flags & REQ_F_BUFFER_SELECTED)
		cflags = io_put_recv_kbuf(req);
	अगर (ret < min_ret || ((flags & MSG_WAITALL) && (msg.msg_flags & (MSG_TRUNC | MSG_CTRUNC))))
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, cflags);
	वापस 0;
पूर्ण

अटल पूर्णांक io_accept_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_accept *accept = &req->accept;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->len || sqe->buf_index)
		वापस -EINVAL;

	accept->addr = u64_to_user_ptr(READ_ONCE(sqe->addr));
	accept->addr_len = u64_to_user_ptr(READ_ONCE(sqe->addr2));
	accept->flags = READ_ONCE(sqe->accept_flags);
	accept->nofile = rlimit(RLIMIT_NOखाता);
	वापस 0;
पूर्ण

अटल पूर्णांक io_accept(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_accept *accept = &req->accept;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;
	अचिन्हित पूर्णांक file_flags = क्रमce_nonblock ? O_NONBLOCK : 0;
	पूर्णांक ret;

	अगर (req->file->f_flags & O_NONBLOCK)
		req->flags |= REQ_F_NOWAIT;

	ret = __sys_accept4_file(req->file, file_flags, accept->addr,
					accept->addr_len, accept->flags,
					accept->nofile);
	अगर (ret == -EAGAIN && क्रमce_nonblock)
		वापस -EAGAIN;
	अगर (ret < 0) अणु
		अगर (ret == -ERESTARTSYS)
			ret = -EINTR;
		req_set_fail_links(req);
	पूर्ण
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक io_connect_prep_async(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_async_connect *io = req->async_data;
	काष्ठा io_connect *conn = &req->connect;

	वापस move_addr_to_kernel(conn->addr, conn->addr_len, &io->address);
पूर्ण

अटल पूर्णांक io_connect_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_connect *conn = &req->connect;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->len || sqe->buf_index || sqe->rw_flags)
		वापस -EINVAL;

	conn->addr = u64_to_user_ptr(READ_ONCE(sqe->addr));
	conn->addr_len =  READ_ONCE(sqe->addr2);
	वापस 0;
पूर्ण

अटल पूर्णांक io_connect(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_async_connect __io, *io;
	अचिन्हित file_flags;
	पूर्णांक ret;
	bool क्रमce_nonblock = issue_flags & IO_URING_F_NONBLOCK;

	अगर (req->async_data) अणु
		io = req->async_data;
	पूर्ण अन्यथा अणु
		ret = move_addr_to_kernel(req->connect.addr,
						req->connect.addr_len,
						&__io.address);
		अगर (ret)
			जाओ out;
		io = &__io;
	पूर्ण

	file_flags = क्रमce_nonblock ? O_NONBLOCK : 0;

	ret = __sys_connect_file(req->file, &io->address,
					req->connect.addr_len, file_flags);
	अगर ((ret == -EAGAIN || ret == -EINPROGRESS) && क्रमce_nonblock) अणु
		अगर (req->async_data)
			वापस -EAGAIN;
		अगर (io_alloc_async_data(req)) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		स_नकल(req->async_data, &__io, माप(__io));
		वापस -EAGAIN;
	पूर्ण
	अगर (ret == -ERESTARTSYS)
		ret = -EINTR;
out:
	अगर (ret < 0)
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_NET */
#घोषणा IO_NETOP_FN(op)							\
अटल पूर्णांक io_##op(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)	\
अणु									\
	वापस -EOPNOTSUPP;						\
पूर्ण

#घोषणा IO_NETOP_PREP(op)						\
IO_NETOP_FN(op)								\
अटल पूर्णांक io_##op##_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe) \
अणु									\
	वापस -EOPNOTSUPP;						\
पूर्ण									\

#घोषणा IO_NETOP_PREP_ASYNC(op)						\
IO_NETOP_PREP(op)							\
अटल पूर्णांक io_##op##_prep_async(काष्ठा io_kiocb *req)			\
अणु									\
	वापस -EOPNOTSUPP;						\
पूर्ण

IO_NETOP_PREP_ASYNC(sendmsg);
IO_NETOP_PREP_ASYNC(recvmsg);
IO_NETOP_PREP_ASYNC(connect);
IO_NETOP_PREP(accept);
IO_NETOP_FN(send);
IO_NETOP_FN(recv);
#पूर्ण_अगर /* CONFIG_NET */

काष्ठा io_poll_table अणु
	काष्ठा poll_table_काष्ठा pt;
	काष्ठा io_kiocb *req;
	पूर्णांक error;
पूर्ण;

अटल पूर्णांक __io_async_wake(काष्ठा io_kiocb *req, काष्ठा io_poll_iocb *poll,
			   __poll_t mask, task_work_func_t func)
अणु
	पूर्णांक ret;

	/* क्रम instances that support it check क्रम an event match first: */
	अगर (mask && !(mask & poll->events))
		वापस 0;

	trace_io_uring_task_add(req->ctx, req->opcode, req->user_data, mask);

	list_del_init(&poll->रुको.entry);

	req->result = mask;
	req->task_work.func = func;

	/*
	 * If this fails, then the task is निकासing. When a task निकासs, the
	 * work माला_लो canceled, so just cancel this request as well instead
	 * of executing it. We can't safely execute it anyway, as we may not
	 * have the needed state needed क्रम it anyway.
	 */
	ret = io_req_task_work_add(req);
	अगर (unlikely(ret)) अणु
		WRITE_ONCE(poll->canceled, true);
		io_req_task_work_add_fallback(req, func);
	पूर्ण
	वापस 1;
पूर्ण

अटल bool io_poll_reरुको(काष्ठा io_kiocb *req, काष्ठा io_poll_iocb *poll)
	__acquires(&req->ctx->completion_lock)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	अगर (!req->result && !READ_ONCE(poll->canceled)) अणु
		काष्ठा poll_table_काष्ठा pt = अणु ._key = poll->events पूर्ण;

		req->result = vfs_poll(req->file, &pt) & poll->events;
	पूर्ण

	spin_lock_irq(&ctx->completion_lock);
	अगर (!req->result && !READ_ONCE(poll->canceled)) अणु
		add_रुको_queue(poll->head, &poll->रुको);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा io_poll_iocb *io_poll_get_द्विगुन(काष्ठा io_kiocb *req)
अणु
	/* pure poll stashes this in ->async_data, poll driven retry अन्यथाwhere */
	अगर (req->opcode == IORING_OP_POLL_ADD)
		वापस req->async_data;
	वापस req->apoll->द्विगुन_poll;
पूर्ण

अटल काष्ठा io_poll_iocb *io_poll_get_single(काष्ठा io_kiocb *req)
अणु
	अगर (req->opcode == IORING_OP_POLL_ADD)
		वापस &req->poll;
	वापस &req->apoll->poll;
पूर्ण

अटल व्योम io_poll_हटाओ_द्विगुन(काष्ठा io_kiocb *req)
	__must_hold(&req->ctx->completion_lock)
अणु
	काष्ठा io_poll_iocb *poll = io_poll_get_द्विगुन(req);

	lockdep_निश्चित_held(&req->ctx->completion_lock);

	अगर (poll && poll->head) अणु
		काष्ठा रुको_queue_head *head = poll->head;

		spin_lock(&head->lock);
		list_del_init(&poll->रुको.entry);
		अगर (poll->रुको.निजी)
			req_ref_put(req);
		poll->head = शून्य;
		spin_unlock(&head->lock);
	पूर्ण
पूर्ण

अटल bool io_poll_complete(काष्ठा io_kiocb *req, __poll_t mask)
	__must_hold(&req->ctx->completion_lock)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	अचिन्हित flags = IORING_CQE_F_MORE;
	पूर्णांक error;

	अगर (READ_ONCE(req->poll.canceled)) अणु
		error = -ECANCELED;
		req->poll.events |= EPOLLONESHOT;
	पूर्ण अन्यथा अणु
		error = mangle_poll(mask);
	पूर्ण
	अगर (req->poll.events & EPOLLONESHOT)
		flags = 0;
	अगर (!io_cqring_fill_event(ctx, req->user_data, error, flags)) अणु
		io_poll_हटाओ_रुकोqs(req);
		req->poll.करोne = true;
		flags = 0;
	पूर्ण
	अगर (flags & IORING_CQE_F_MORE)
		ctx->cq_extra++;

	io_commit_cqring(ctx);
	वापस !(flags & IORING_CQE_F_MORE);
पूर्ण

अटल व्योम io_poll_task_func(काष्ठा callback_head *cb)
अणु
	काष्ठा io_kiocb *req = container_of(cb, काष्ठा io_kiocb, task_work);
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_kiocb *nxt;

	अगर (io_poll_reरुको(req, &req->poll)) अणु
		spin_unlock_irq(&ctx->completion_lock);
	पूर्ण अन्यथा अणु
		bool करोne;

		करोne = io_poll_complete(req, req->result);
		अगर (करोne) अणु
			hash_del(&req->hash_node);
		पूर्ण अन्यथा अणु
			req->result = 0;
			add_रुको_queue(req->poll.head, &req->poll.रुको);
		पूर्ण
		spin_unlock_irq(&ctx->completion_lock);
		io_cqring_ev_posted(ctx);

		अगर (करोne) अणु
			nxt = io_put_req_find_next(req);
			अगर (nxt)
				__io_req_task_submit(nxt);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक io_poll_द्विगुन_wake(काष्ठा रुको_queue_entry *रुको, अचिन्हित mode,
			       पूर्णांक sync, व्योम *key)
अणु
	काष्ठा io_kiocb *req = रुको->निजी;
	काष्ठा io_poll_iocb *poll = io_poll_get_single(req);
	__poll_t mask = key_to_poll(key);

	/* क्रम instances that support it check क्रम an event match first: */
	अगर (mask && !(mask & poll->events))
		वापस 0;
	अगर (!(poll->events & EPOLLONESHOT))
		वापस poll->रुको.func(&poll->रुको, mode, sync, key);

	list_del_init(&रुको->entry);

	अगर (poll && poll->head) अणु
		bool करोne;

		spin_lock(&poll->head->lock);
		करोne = list_empty(&poll->रुको.entry);
		अगर (!करोne)
			list_del_init(&poll->रुको.entry);
		/* make sure द्विगुन हटाओ sees this as being gone */
		रुको->निजी = शून्य;
		spin_unlock(&poll->head->lock);
		अगर (!करोne) अणु
			/* use रुको func handler, so it matches the rq type */
			poll->रुको.func(&poll->रुको, mode, sync, key);
		पूर्ण
	पूर्ण
	req_ref_put(req);
	वापस 1;
पूर्ण

अटल व्योम io_init_poll_iocb(काष्ठा io_poll_iocb *poll, __poll_t events,
			      रुको_queue_func_t wake_func)
अणु
	poll->head = शून्य;
	poll->करोne = false;
	poll->canceled = false;
#घोषणा IO_POLL_UNMASK	(EPOLLERR|EPOLLHUP|EPOLLNVAL|EPOLLRDHUP)
	/* mask in events that we always want/need */
	poll->events = events | IO_POLL_UNMASK;
	INIT_LIST_HEAD(&poll->रुको.entry);
	init_रुकोqueue_func_entry(&poll->रुको, wake_func);
पूर्ण

अटल व्योम __io_queue_proc(काष्ठा io_poll_iocb *poll, काष्ठा io_poll_table *pt,
			    काष्ठा रुको_queue_head *head,
			    काष्ठा io_poll_iocb **poll_ptr)
अणु
	काष्ठा io_kiocb *req = pt->req;

	/*
	 * If poll->head is alपढ़ोy set, it's because the file being polled
	 * uses multiple रुकोqueues क्रम poll handling (eg one क्रम पढ़ो, one
	 * क्रम ग_लिखो). Setup a separate io_poll_iocb अगर this happens.
	 */
	अगर (unlikely(poll->head)) अणु
		काष्ठा io_poll_iocb *poll_one = poll;

		/* alपढ़ोy have a 2nd entry, fail a third attempt */
		अगर (*poll_ptr) अणु
			pt->error = -EINVAL;
			वापस;
		पूर्ण
		/*
		 * Can't handle multishot क्रम द्विगुन रुको क्रम now, turn it
		 * पूर्णांकo one-shot mode.
		 */
		अगर (!(poll_one->events & EPOLLONESHOT))
			poll_one->events |= EPOLLONESHOT;
		/* द्विगुन add on the same रुकोqueue head, ignore */
		अगर (poll_one->head == head)
			वापस;
		poll = kदो_स्मृति(माप(*poll), GFP_ATOMIC);
		अगर (!poll) अणु
			pt->error = -ENOMEM;
			वापस;
		पूर्ण
		io_init_poll_iocb(poll, poll_one->events, io_poll_द्विगुन_wake);
		req_ref_get(req);
		poll->रुको.निजी = req;
		*poll_ptr = poll;
	पूर्ण

	pt->error = 0;
	poll->head = head;

	अगर (poll->events & EPOLLEXCLUSIVE)
		add_रुको_queue_exclusive(head, &poll->रुको);
	अन्यथा
		add_रुको_queue(head, &poll->रुको);
पूर्ण

अटल व्योम io_async_queue_proc(काष्ठा file *file, काष्ठा रुको_queue_head *head,
			       काष्ठा poll_table_काष्ठा *p)
अणु
	काष्ठा io_poll_table *pt = container_of(p, काष्ठा io_poll_table, pt);
	काष्ठा async_poll *apoll = pt->req->apoll;

	__io_queue_proc(&apoll->poll, pt, head, &apoll->द्विगुन_poll);
पूर्ण

अटल व्योम io_async_task_func(काष्ठा callback_head *cb)
अणु
	काष्ठा io_kiocb *req = container_of(cb, काष्ठा io_kiocb, task_work);
	काष्ठा async_poll *apoll = req->apoll;
	काष्ठा io_ring_ctx *ctx = req->ctx;

	trace_io_uring_task_run(req->ctx, req->opcode, req->user_data);

	अगर (io_poll_reरुको(req, &apoll->poll)) अणु
		spin_unlock_irq(&ctx->completion_lock);
		वापस;
	पूर्ण

	hash_del(&req->hash_node);
	io_poll_हटाओ_द्विगुन(req);
	spin_unlock_irq(&ctx->completion_lock);

	अगर (!READ_ONCE(apoll->poll.canceled))
		__io_req_task_submit(req);
	अन्यथा
		io_req_complete_failed(req, -ECANCELED);
पूर्ण

अटल पूर्णांक io_async_wake(काष्ठा रुको_queue_entry *रुको, अचिन्हित mode, पूर्णांक sync,
			व्योम *key)
अणु
	काष्ठा io_kiocb *req = रुको->निजी;
	काष्ठा io_poll_iocb *poll = &req->apoll->poll;

	trace_io_uring_poll_wake(req->ctx, req->opcode, req->user_data,
					key_to_poll(key));

	वापस __io_async_wake(req, poll, key_to_poll(key), io_async_task_func);
पूर्ण

अटल व्योम io_poll_req_insert(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा hlist_head *list;

	list = &ctx->cancel_hash[hash_दीर्घ(req->user_data, ctx->cancel_hash_bits)];
	hlist_add_head(&req->hash_node, list);
पूर्ण

अटल __poll_t __io_arm_poll_handler(काष्ठा io_kiocb *req,
				      काष्ठा io_poll_iocb *poll,
				      काष्ठा io_poll_table *ipt, __poll_t mask,
				      रुको_queue_func_t wake_func)
	__acquires(&ctx->completion_lock)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	bool cancel = false;

	INIT_HLIST_NODE(&req->hash_node);
	io_init_poll_iocb(poll, mask, wake_func);
	poll->file = req->file;
	poll->रुको.निजी = req;

	ipt->pt._key = mask;
	ipt->req = req;
	ipt->error = -EINVAL;

	mask = vfs_poll(req->file, &ipt->pt) & poll->events;

	spin_lock_irq(&ctx->completion_lock);
	अगर (likely(poll->head)) अणु
		spin_lock(&poll->head->lock);
		अगर (unlikely(list_empty(&poll->रुको.entry))) अणु
			अगर (ipt->error)
				cancel = true;
			ipt->error = 0;
			mask = 0;
		पूर्ण
		अगर ((mask && (poll->events & EPOLLONESHOT)) || ipt->error)
			list_del_init(&poll->रुको.entry);
		अन्यथा अगर (cancel)
			WRITE_ONCE(poll->canceled, true);
		अन्यथा अगर (!poll->करोne) /* actually रुकोing क्रम an event */
			io_poll_req_insert(req);
		spin_unlock(&poll->head->lock);
	पूर्ण

	वापस mask;
पूर्ण

अटल bool io_arm_poll_handler(काष्ठा io_kiocb *req)
अणु
	स्थिर काष्ठा io_op_def *def = &io_op_defs[req->opcode];
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा async_poll *apoll;
	काष्ठा io_poll_table ipt;
	__poll_t mask, ret;
	पूर्णांक rw;

	अगर (!req->file || !file_can_poll(req->file))
		वापस false;
	अगर (req->flags & REQ_F_POLLED)
		वापस false;
	अगर (def->pollin)
		rw = READ;
	अन्यथा अगर (def->pollout)
		rw = WRITE;
	अन्यथा
		वापस false;
	/* अगर we can't nonblock try, then no poपूर्णांक in arming a poll handler */
	अगर (!io_file_supports_async(req, rw))
		वापस false;

	apoll = kदो_स्मृति(माप(*apoll), GFP_ATOMIC);
	अगर (unlikely(!apoll))
		वापस false;
	apoll->द्विगुन_poll = शून्य;

	req->flags |= REQ_F_POLLED;
	req->apoll = apoll;

	mask = EPOLLONESHOT;
	अगर (def->pollin)
		mask |= POLLIN | POLLRDNORM;
	अगर (def->pollout)
		mask |= POLLOUT | POLLWRNORM;

	/* If पढ़ोing from MSG_ERRQUEUE using recvmsg, ignore POLLIN */
	अगर ((req->opcode == IORING_OP_RECVMSG) &&
	    (req->sr_msg.msg_flags & MSG_ERRQUEUE))
		mask &= ~POLLIN;

	mask |= POLLERR | POLLPRI;

	ipt.pt._qproc = io_async_queue_proc;

	ret = __io_arm_poll_handler(req, &apoll->poll, &ipt, mask,
					io_async_wake);
	अगर (ret || ipt.error) अणु
		io_poll_हटाओ_द्विगुन(req);
		spin_unlock_irq(&ctx->completion_lock);
		वापस false;
	पूर्ण
	spin_unlock_irq(&ctx->completion_lock);
	trace_io_uring_poll_arm(ctx, req->opcode, req->user_data, mask,
					apoll->poll.events);
	वापस true;
पूर्ण

अटल bool __io_poll_हटाओ_one(काष्ठा io_kiocb *req,
				 काष्ठा io_poll_iocb *poll, bool करो_cancel)
	__must_hold(&req->ctx->completion_lock)
अणु
	bool करो_complete = false;

	अगर (!poll->head)
		वापस false;
	spin_lock(&poll->head->lock);
	अगर (करो_cancel)
		WRITE_ONCE(poll->canceled, true);
	अगर (!list_empty(&poll->रुको.entry)) अणु
		list_del_init(&poll->रुको.entry);
		करो_complete = true;
	पूर्ण
	spin_unlock(&poll->head->lock);
	hash_del(&req->hash_node);
	वापस करो_complete;
पूर्ण

अटल bool io_poll_हटाओ_रुकोqs(काष्ठा io_kiocb *req)
	__must_hold(&req->ctx->completion_lock)
अणु
	bool करो_complete;

	io_poll_हटाओ_द्विगुन(req);
	करो_complete = __io_poll_हटाओ_one(req, io_poll_get_single(req), true);

	अगर (req->opcode != IORING_OP_POLL_ADD && करो_complete) अणु
		/* non-poll requests have submit ref still */
		req_ref_put(req);
	पूर्ण
	वापस करो_complete;
पूर्ण

अटल bool io_poll_हटाओ_one(काष्ठा io_kiocb *req)
	__must_hold(&req->ctx->completion_lock)
अणु
	bool करो_complete;

	करो_complete = io_poll_हटाओ_रुकोqs(req);
	अगर (करो_complete) अणु
		io_cqring_fill_event(req->ctx, req->user_data, -ECANCELED, 0);
		io_commit_cqring(req->ctx);
		req_set_fail_links(req);
		io_put_req_deferred(req, 1);
	पूर्ण

	वापस करो_complete;
पूर्ण

/*
 * Returns true अगर we found and समाप्तed one or more poll requests
 */
अटल bool io_poll_हटाओ_all(काष्ठा io_ring_ctx *ctx, काष्ठा task_काष्ठा *tsk,
			       काष्ठा files_काष्ठा *files)
अणु
	काष्ठा hlist_node *पंचांगp;
	काष्ठा io_kiocb *req;
	पूर्णांक posted = 0, i;

	spin_lock_irq(&ctx->completion_lock);
	क्रम (i = 0; i < (1U << ctx->cancel_hash_bits); i++) अणु
		काष्ठा hlist_head *list;

		list = &ctx->cancel_hash[i];
		hlist_क्रम_each_entry_safe(req, पंचांगp, list, hash_node) अणु
			अगर (io_match_task(req, tsk, files))
				posted += io_poll_हटाओ_one(req);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ctx->completion_lock);

	अगर (posted)
		io_cqring_ev_posted(ctx);

	वापस posted != 0;
पूर्ण

अटल काष्ठा io_kiocb *io_poll_find(काष्ठा io_ring_ctx *ctx, __u64 sqe_addr,
				     bool poll_only)
	__must_hold(&ctx->completion_lock)
अणु
	काष्ठा hlist_head *list;
	काष्ठा io_kiocb *req;

	list = &ctx->cancel_hash[hash_दीर्घ(sqe_addr, ctx->cancel_hash_bits)];
	hlist_क्रम_each_entry(req, list, hash_node) अणु
		अगर (sqe_addr != req->user_data)
			जारी;
		अगर (poll_only && req->opcode != IORING_OP_POLL_ADD)
			जारी;
		वापस req;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक io_poll_cancel(काष्ठा io_ring_ctx *ctx, __u64 sqe_addr,
			  bool poll_only)
	__must_hold(&ctx->completion_lock)
अणु
	काष्ठा io_kiocb *req;

	req = io_poll_find(ctx, sqe_addr, poll_only);
	अगर (!req)
		वापस -ENOENT;
	अगर (io_poll_हटाओ_one(req))
		वापस 0;

	वापस -EALREADY;
पूर्ण

अटल __poll_t io_poll_parse_events(स्थिर काष्ठा io_uring_sqe *sqe,
				     अचिन्हित पूर्णांक flags)
अणु
	u32 events;

	events = READ_ONCE(sqe->poll32_events);
#अगर_घोषित __BIG_ENDIAN
	events = swahw32(events);
#पूर्ण_अगर
	अगर (!(flags & IORING_POLL_ADD_MULTI))
		events |= EPOLLONESHOT;
	वापस demangle_poll(events) | (events & (EPOLLEXCLUSIVE|EPOLLONESHOT));
पूर्ण

अटल पूर्णांक io_poll_update_prep(काष्ठा io_kiocb *req,
			       स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_poll_update *upd = &req->poll_update;
	u32 flags;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->buf_index)
		वापस -EINVAL;
	flags = READ_ONCE(sqe->len);
	अगर (flags & ~(IORING_POLL_UPDATE_EVENTS | IORING_POLL_UPDATE_USER_DATA |
		      IORING_POLL_ADD_MULTI))
		वापस -EINVAL;
	/* meaningless without update */
	अगर (flags == IORING_POLL_ADD_MULTI)
		वापस -EINVAL;

	upd->old_user_data = READ_ONCE(sqe->addr);
	upd->update_events = flags & IORING_POLL_UPDATE_EVENTS;
	upd->update_user_data = flags & IORING_POLL_UPDATE_USER_DATA;

	upd->new_user_data = READ_ONCE(sqe->off);
	अगर (!upd->update_user_data && upd->new_user_data)
		वापस -EINVAL;
	अगर (upd->update_events)
		upd->events = io_poll_parse_events(sqe, flags);
	अन्यथा अगर (sqe->poll32_events)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक io_poll_wake(काष्ठा रुको_queue_entry *रुको, अचिन्हित mode, पूर्णांक sync,
			व्योम *key)
अणु
	काष्ठा io_kiocb *req = रुको->निजी;
	काष्ठा io_poll_iocb *poll = &req->poll;

	वापस __io_async_wake(req, poll, key_to_poll(key), io_poll_task_func);
पूर्ण

अटल व्योम io_poll_queue_proc(काष्ठा file *file, काष्ठा रुको_queue_head *head,
			       काष्ठा poll_table_काष्ठा *p)
अणु
	काष्ठा io_poll_table *pt = container_of(p, काष्ठा io_poll_table, pt);

	__io_queue_proc(&pt->req->poll, pt, head, (काष्ठा io_poll_iocb **) &pt->req->async_data);
पूर्ण

अटल पूर्णांक io_poll_add_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_poll_iocb *poll = &req->poll;
	u32 flags;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->buf_index || sqe->off || sqe->addr)
		वापस -EINVAL;
	flags = READ_ONCE(sqe->len);
	अगर (flags & ~IORING_POLL_ADD_MULTI)
		वापस -EINVAL;

	poll->events = io_poll_parse_events(sqe, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक io_poll_add(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_poll_iocb *poll = &req->poll;
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_poll_table ipt;
	__poll_t mask;

	ipt.pt._qproc = io_poll_queue_proc;

	mask = __io_arm_poll_handler(req, &req->poll, &ipt, poll->events,
					io_poll_wake);

	अगर (mask) अणु /* no async, we'd stolen it */
		ipt.error = 0;
		io_poll_complete(req, mask);
	पूर्ण
	spin_unlock_irq(&ctx->completion_lock);

	अगर (mask) अणु
		io_cqring_ev_posted(ctx);
		अगर (poll->events & EPOLLONESHOT)
			io_put_req(req);
	पूर्ण
	वापस ipt.error;
पूर्ण

अटल पूर्णांक io_poll_update(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_kiocb *preq;
	bool completing;
	पूर्णांक ret;

	spin_lock_irq(&ctx->completion_lock);
	preq = io_poll_find(ctx, req->poll_update.old_user_data, true);
	अगर (!preq) अणु
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	अगर (!req->poll_update.update_events && !req->poll_update.update_user_data) अणु
		completing = true;
		ret = io_poll_हटाओ_one(preq) ? 0 : -EALREADY;
		जाओ err;
	पूर्ण

	/*
	 * Don't allow racy completion with singleshot, as we cannot safely
	 * update those. For multishot, अगर we're racing with completion, just
	 * let completion re-add it.
	 */
	completing = !__io_poll_हटाओ_one(preq, &preq->poll, false);
	अगर (completing && (preq->poll.events & EPOLLONESHOT)) अणु
		ret = -EALREADY;
		जाओ err;
	पूर्ण
	/* we now have a detached poll request. reissue. */
	ret = 0;
err:
	अगर (ret < 0) अणु
		spin_unlock_irq(&ctx->completion_lock);
		req_set_fail_links(req);
		io_req_complete(req, ret);
		वापस 0;
	पूर्ण
	/* only mask one event flags, keep behavior flags */
	अगर (req->poll_update.update_events) अणु
		preq->poll.events &= ~0xffff;
		preq->poll.events |= req->poll_update.events & 0xffff;
		preq->poll.events |= IO_POLL_UNMASK;
	पूर्ण
	अगर (req->poll_update.update_user_data)
		preq->user_data = req->poll_update.new_user_data;
	spin_unlock_irq(&ctx->completion_lock);

	/* complete update request, we're करोne with it */
	io_req_complete(req, ret);

	अगर (!completing) अणु
		ret = io_poll_add(preq, issue_flags);
		अगर (ret < 0) अणु
			req_set_fail_links(preq);
			io_req_complete(preq, ret);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत hrसमयr_restart io_समयout_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा io_समयout_data *data = container_of(समयr,
						काष्ठा io_समयout_data, समयr);
	काष्ठा io_kiocb *req = data->req;
	काष्ठा io_ring_ctx *ctx = req->ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->completion_lock, flags);
	list_del_init(&req->समयout.list);
	atomic_set(&req->ctx->cq_समयouts,
		atomic_पढ़ो(&req->ctx->cq_समयouts) + 1);

	io_cqring_fill_event(ctx, req->user_data, -ETIME, 0);
	io_commit_cqring(ctx);
	spin_unlock_irqrestore(&ctx->completion_lock, flags);

	io_cqring_ev_posted(ctx);
	req_set_fail_links(req);
	io_put_req(req);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल काष्ठा io_kiocb *io_समयout_extract(काष्ठा io_ring_ctx *ctx,
					   __u64 user_data)
	__must_hold(&ctx->completion_lock)
अणु
	काष्ठा io_समयout_data *io;
	काष्ठा io_kiocb *req;
	bool found = false;

	list_क्रम_each_entry(req, &ctx->समयout_list, समयout.list) अणु
		found = user_data == req->user_data;
		अगर (found)
			अवरोध;
	पूर्ण
	अगर (!found)
		वापस ERR_PTR(-ENOENT);

	io = req->async_data;
	अगर (hrसमयr_try_to_cancel(&io->समयr) == -1)
		वापस ERR_PTR(-EALREADY);
	list_del_init(&req->समयout.list);
	वापस req;
पूर्ण

अटल पूर्णांक io_समयout_cancel(काष्ठा io_ring_ctx *ctx, __u64 user_data)
	__must_hold(&ctx->completion_lock)
अणु
	काष्ठा io_kiocb *req = io_समयout_extract(ctx, user_data);

	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	req_set_fail_links(req);
	io_cqring_fill_event(ctx, req->user_data, -ECANCELED, 0);
	io_put_req_deferred(req, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक io_समयout_update(काष्ठा io_ring_ctx *ctx, __u64 user_data,
			     काष्ठा बारpec64 *ts, क्रमागत hrसमयr_mode mode)
	__must_hold(&ctx->completion_lock)
अणु
	काष्ठा io_kiocb *req = io_समयout_extract(ctx, user_data);
	काष्ठा io_समयout_data *data;

	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	req->समयout.off = 0; /* noseq */
	data = req->async_data;
	list_add_tail(&req->समयout.list, &ctx->समयout_list);
	hrसमयr_init(&data->समयr, CLOCK_MONOTONIC, mode);
	data->समयr.function = io_समयout_fn;
	hrसमयr_start(&data->समयr, बारpec64_to_kसमय(*ts), mode);
	वापस 0;
पूर्ण

अटल पूर्णांक io_समयout_हटाओ_prep(काष्ठा io_kiocb *req,
				  स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_समयout_rem *tr = &req->समयout_rem;

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (unlikely(req->flags & (REQ_F_FIXED_खाता | REQ_F_BUFFER_SELECT)))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->buf_index || sqe->len)
		वापस -EINVAL;

	tr->addr = READ_ONCE(sqe->addr);
	tr->flags = READ_ONCE(sqe->समयout_flags);
	अगर (tr->flags & IORING_TIMEOUT_UPDATE) अणु
		अगर (tr->flags & ~(IORING_TIMEOUT_UPDATE|IORING_TIMEOUT_ABS))
			वापस -EINVAL;
		अगर (get_बारpec64(&tr->ts, u64_to_user_ptr(sqe->addr2)))
			वापस -EFAULT;
	पूर्ण अन्यथा अगर (tr->flags) अणु
		/* समयout removal करोesn't support flags */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत hrसमयr_mode io_translate_समयout_mode(अचिन्हित पूर्णांक flags)
अणु
	वापस (flags & IORING_TIMEOUT_ABS) ? HRTIMER_MODE_ABS
					    : HRTIMER_MODE_REL;
पूर्ण

/*
 * Remove or update an existing समयout command
 */
अटल पूर्णांक io_समयout_हटाओ(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_समयout_rem *tr = &req->समयout_rem;
	काष्ठा io_ring_ctx *ctx = req->ctx;
	पूर्णांक ret;

	spin_lock_irq(&ctx->completion_lock);
	अगर (!(req->समयout_rem.flags & IORING_TIMEOUT_UPDATE))
		ret = io_समयout_cancel(ctx, tr->addr);
	अन्यथा
		ret = io_समयout_update(ctx, tr->addr, &tr->ts,
					io_translate_समयout_mode(tr->flags));

	io_cqring_fill_event(ctx, req->user_data, ret, 0);
	io_commit_cqring(ctx);
	spin_unlock_irq(&ctx->completion_lock);
	io_cqring_ev_posted(ctx);
	अगर (ret < 0)
		req_set_fail_links(req);
	io_put_req(req);
	वापस 0;
पूर्ण

अटल पूर्णांक io_समयout_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe,
			   bool is_समयout_link)
अणु
	काष्ठा io_समयout_data *data;
	अचिन्हित flags;
	u32 off = READ_ONCE(sqe->off);

	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->buf_index || sqe->len != 1)
		वापस -EINVAL;
	अगर (off && is_समयout_link)
		वापस -EINVAL;
	flags = READ_ONCE(sqe->समयout_flags);
	अगर (flags & ~IORING_TIMEOUT_ABS)
		वापस -EINVAL;

	req->समयout.off = off;

	अगर (!req->async_data && io_alloc_async_data(req))
		वापस -ENOMEM;

	data = req->async_data;
	data->req = req;

	अगर (get_बारpec64(&data->ts, u64_to_user_ptr(sqe->addr)))
		वापस -EFAULT;

	data->mode = io_translate_समयout_mode(flags);
	hrसमयr_init(&data->समयr, CLOCK_MONOTONIC, data->mode);
	अगर (is_समयout_link)
		io_req_track_inflight(req);
	वापस 0;
पूर्ण

अटल पूर्णांक io_समयout(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_समयout_data *data = req->async_data;
	काष्ठा list_head *entry;
	u32 tail, off = req->समयout.off;

	spin_lock_irq(&ctx->completion_lock);

	/*
	 * sqe->off holds how many events that need to occur क्रम this
	 * समयout event to be satisfied. If it isn't set, then this is
	 * a pure समयout request, sequence isn't used.
	 */
	अगर (io_is_समयout_noseq(req)) अणु
		entry = ctx->समयout_list.prev;
		जाओ add;
	पूर्ण

	tail = ctx->cached_cq_tail - atomic_पढ़ो(&ctx->cq_समयouts);
	req->समयout.target_seq = tail + off;

	/* Update the last seq here in हाल io_flush_समयouts() hasn't.
	 * This is safe because ->completion_lock is held, and submissions
	 * and completions are never mixed in the same ->completion_lock section.
	 */
	ctx->cq_last_पंचांग_flush = tail;

	/*
	 * Insertion sort, ensuring the first entry in the list is always
	 * the one we need first.
	 */
	list_क्रम_each_prev(entry, &ctx->समयout_list) अणु
		काष्ठा io_kiocb *nxt = list_entry(entry, काष्ठा io_kiocb,
						  समयout.list);

		अगर (io_is_समयout_noseq(nxt))
			जारी;
		/* nxt.seq is behind @tail, otherwise would've been completed */
		अगर (off >= nxt->समयout.target_seq - tail)
			अवरोध;
	पूर्ण
add:
	list_add(&req->समयout.list, entry);
	data->समयr.function = io_समयout_fn;
	hrसमयr_start(&data->समयr, बारpec64_to_kसमय(data->ts), data->mode);
	spin_unlock_irq(&ctx->completion_lock);
	वापस 0;
पूर्ण

काष्ठा io_cancel_data अणु
	काष्ठा io_ring_ctx *ctx;
	u64 user_data;
पूर्ण;

अटल bool io_cancel_cb(काष्ठा io_wq_work *work, व्योम *data)
अणु
	काष्ठा io_kiocb *req = container_of(work, काष्ठा io_kiocb, work);
	काष्ठा io_cancel_data *cd = data;

	वापस req->ctx == cd->ctx && req->user_data == cd->user_data;
पूर्ण

अटल पूर्णांक io_async_cancel_one(काष्ठा io_uring_task *tctx, u64 user_data,
			       काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_cancel_data data = अणु .ctx = ctx, .user_data = user_data, पूर्ण;
	क्रमागत io_wq_cancel cancel_ret;
	पूर्णांक ret = 0;

	अगर (!tctx || !tctx->io_wq)
		वापस -ENOENT;

	cancel_ret = io_wq_cancel_cb(tctx->io_wq, io_cancel_cb, &data, false);
	चयन (cancel_ret) अणु
	हाल IO_WQ_CANCEL_OK:
		ret = 0;
		अवरोध;
	हाल IO_WQ_CANCEL_RUNNING:
		ret = -EALREADY;
		अवरोध;
	हाल IO_WQ_CANCEL_NOTFOUND:
		ret = -ENOENT;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम io_async_find_and_cancel(काष्ठा io_ring_ctx *ctx,
				     काष्ठा io_kiocb *req, __u64 sqe_addr,
				     पूर्णांक success_ret)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = io_async_cancel_one(req->task->io_uring, sqe_addr, ctx);
	spin_lock_irqsave(&ctx->completion_lock, flags);
	अगर (ret != -ENOENT)
		जाओ करोne;
	ret = io_समयout_cancel(ctx, sqe_addr);
	अगर (ret != -ENOENT)
		जाओ करोne;
	ret = io_poll_cancel(ctx, sqe_addr, false);
करोne:
	अगर (!ret)
		ret = success_ret;
	io_cqring_fill_event(ctx, req->user_data, ret, 0);
	io_commit_cqring(ctx);
	spin_unlock_irqrestore(&ctx->completion_lock, flags);
	io_cqring_ev_posted(ctx);

	अगर (ret < 0)
		req_set_fail_links(req);
पूर्ण

अटल पूर्णांक io_async_cancel_prep(काष्ठा io_kiocb *req,
				स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		वापस -EINVAL;
	अगर (unlikely(req->flags & (REQ_F_FIXED_खाता | REQ_F_BUFFER_SELECT)))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->off || sqe->len || sqe->cancel_flags)
		वापस -EINVAL;

	req->cancel.addr = READ_ONCE(sqe->addr);
	वापस 0;
पूर्ण

अटल पूर्णांक io_async_cancel(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	u64 sqe_addr = req->cancel.addr;
	काष्ठा io_tctx_node *node;
	पूर्णांक ret;

	/* tasks should रुको क्रम their io-wq thपढ़ोs, so safe w/o sync */
	ret = io_async_cancel_one(req->task->io_uring, sqe_addr, ctx);
	spin_lock_irq(&ctx->completion_lock);
	अगर (ret != -ENOENT)
		जाओ करोne;
	ret = io_समयout_cancel(ctx, sqe_addr);
	अगर (ret != -ENOENT)
		जाओ करोne;
	ret = io_poll_cancel(ctx, sqe_addr, false);
	अगर (ret != -ENOENT)
		जाओ करोne;
	spin_unlock_irq(&ctx->completion_lock);

	/* slow path, try all io-wq's */
	io_ring_submit_lock(ctx, !(issue_flags & IO_URING_F_NONBLOCK));
	ret = -ENOENT;
	list_क्रम_each_entry(node, &ctx->tctx_list, ctx_node) अणु
		काष्ठा io_uring_task *tctx = node->task->io_uring;

		ret = io_async_cancel_one(tctx, req->cancel.addr, ctx);
		अगर (ret != -ENOENT)
			अवरोध;
	पूर्ण
	io_ring_submit_unlock(ctx, !(issue_flags & IO_URING_F_NONBLOCK));

	spin_lock_irq(&ctx->completion_lock);
करोne:
	io_cqring_fill_event(ctx, req->user_data, ret, 0);
	io_commit_cqring(ctx);
	spin_unlock_irq(&ctx->completion_lock);
	io_cqring_ev_posted(ctx);

	अगर (ret < 0)
		req_set_fail_links(req);
	io_put_req(req);
	वापस 0;
पूर्ण

अटल पूर्णांक io_rsrc_update_prep(काष्ठा io_kiocb *req,
				स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	अगर (unlikely(req->flags & (REQ_F_FIXED_खाता | REQ_F_BUFFER_SELECT)))
		वापस -EINVAL;
	अगर (sqe->ioprio || sqe->rw_flags)
		वापस -EINVAL;

	req->rsrc_update.offset = READ_ONCE(sqe->off);
	req->rsrc_update.nr_args = READ_ONCE(sqe->len);
	अगर (!req->rsrc_update.nr_args)
		वापस -EINVAL;
	req->rsrc_update.arg = READ_ONCE(sqe->addr);
	वापस 0;
पूर्ण

अटल पूर्णांक io_files_update(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_uring_rsrc_update2 up;
	पूर्णांक ret;

	अगर (issue_flags & IO_URING_F_NONBLOCK)
		वापस -EAGAIN;

	up.offset = req->rsrc_update.offset;
	up.data = req->rsrc_update.arg;
	up.nr = 0;
	up.tags = 0;
	up.resv = 0;

	mutex_lock(&ctx->uring_lock);
	ret = __io_रेजिस्टर_rsrc_update(ctx, IORING_RSRC_खाता,
					&up, req->rsrc_update.nr_args);
	mutex_unlock(&ctx->uring_lock);

	अगर (ret < 0)
		req_set_fail_links(req);
	__io_req_complete(req, issue_flags, ret, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक io_req_prep(काष्ठा io_kiocb *req, स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	चयन (req->opcode) अणु
	हाल IORING_OP_NOP:
		वापस 0;
	हाल IORING_OP_READV:
	हाल IORING_OP_READ_FIXED:
	हाल IORING_OP_READ:
		वापस io_पढ़ो_prep(req, sqe);
	हाल IORING_OP_WRITEV:
	हाल IORING_OP_WRITE_FIXED:
	हाल IORING_OP_WRITE:
		वापस io_ग_लिखो_prep(req, sqe);
	हाल IORING_OP_POLL_ADD:
		वापस io_poll_add_prep(req, sqe);
	हाल IORING_OP_POLL_REMOVE:
		वापस io_poll_update_prep(req, sqe);
	हाल IORING_OP_FSYNC:
		वापस io_fsync_prep(req, sqe);
	हाल IORING_OP_SYNC_खाता_RANGE:
		वापस io_sfr_prep(req, sqe);
	हाल IORING_OP_SENDMSG:
	हाल IORING_OP_SEND:
		वापस io_sendmsg_prep(req, sqe);
	हाल IORING_OP_RECVMSG:
	हाल IORING_OP_RECV:
		वापस io_recvmsg_prep(req, sqe);
	हाल IORING_OP_CONNECT:
		वापस io_connect_prep(req, sqe);
	हाल IORING_OP_TIMEOUT:
		वापस io_समयout_prep(req, sqe, false);
	हाल IORING_OP_TIMEOUT_REMOVE:
		वापस io_समयout_हटाओ_prep(req, sqe);
	हाल IORING_OP_ASYNC_CANCEL:
		वापस io_async_cancel_prep(req, sqe);
	हाल IORING_OP_LINK_TIMEOUT:
		वापस io_समयout_prep(req, sqe, true);
	हाल IORING_OP_ACCEPT:
		वापस io_accept_prep(req, sqe);
	हाल IORING_OP_FALLOCATE:
		वापस io_fallocate_prep(req, sqe);
	हाल IORING_OP_OPENAT:
		वापस io_खोलोat_prep(req, sqe);
	हाल IORING_OP_CLOSE:
		वापस io_बंद_prep(req, sqe);
	हाल IORING_OP_खाताS_UPDATE:
		वापस io_rsrc_update_prep(req, sqe);
	हाल IORING_OP_STATX:
		वापस io_statx_prep(req, sqe);
	हाल IORING_OP_FADVISE:
		वापस io_fadvise_prep(req, sqe);
	हाल IORING_OP_MADVISE:
		वापस io_madvise_prep(req, sqe);
	हाल IORING_OP_OPENAT2:
		वापस io_खोलोat2_prep(req, sqe);
	हाल IORING_OP_EPOLL_CTL:
		वापस io_epoll_ctl_prep(req, sqe);
	हाल IORING_OP_SPLICE:
		वापस io_splice_prep(req, sqe);
	हाल IORING_OP_PROVIDE_BUFFERS:
		वापस io_provide_buffers_prep(req, sqe);
	हाल IORING_OP_REMOVE_BUFFERS:
		वापस io_हटाओ_buffers_prep(req, sqe);
	हाल IORING_OP_TEE:
		वापस io_tee_prep(req, sqe);
	हाल IORING_OP_SHUTDOWN:
		वापस io_shutकरोwn_prep(req, sqe);
	हाल IORING_OP_RENAMEAT:
		वापस io_नामat_prep(req, sqe);
	हाल IORING_OP_UNLINKAT:
		वापस io_unlinkat_prep(req, sqe);
	पूर्ण

	prपूर्णांकk_once(KERN_WARNING "io_uring: unhandled opcode %d\n",
			req->opcode);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक io_req_prep_async(काष्ठा io_kiocb *req)
अणु
	अगर (!io_op_defs[req->opcode].needs_async_setup)
		वापस 0;
	अगर (WARN_ON_ONCE(req->async_data))
		वापस -EFAULT;
	अगर (io_alloc_async_data(req))
		वापस -EAGAIN;

	चयन (req->opcode) अणु
	हाल IORING_OP_READV:
		वापस io_rw_prep_async(req, READ);
	हाल IORING_OP_WRITEV:
		वापस io_rw_prep_async(req, WRITE);
	हाल IORING_OP_SENDMSG:
		वापस io_sendmsg_prep_async(req);
	हाल IORING_OP_RECVMSG:
		वापस io_recvmsg_prep_async(req);
	हाल IORING_OP_CONNECT:
		वापस io_connect_prep_async(req);
	पूर्ण
	prपूर्णांकk_once(KERN_WARNING "io_uring: prep_async() bad opcode %d\n",
		    req->opcode);
	वापस -EFAULT;
पूर्ण

अटल u32 io_get_sequence(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_kiocb *pos;
	काष्ठा io_ring_ctx *ctx = req->ctx;
	u32 total_submitted, nr_reqs = 0;

	io_क्रम_each_link(pos, req)
		nr_reqs++;

	total_submitted = ctx->cached_sq_head - ctx->cached_sq_dropped;
	वापस total_submitted - nr_reqs;
पूर्ण

अटल पूर्णांक io_req_defer(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा io_defer_entry *de;
	पूर्णांक ret;
	u32 seq;

	/* Still need defer अगर there is pending req in defer list. */
	अगर (likely(list_empty_careful(&ctx->defer_list) &&
		!(req->flags & REQ_F_IO_DRAIN)))
		वापस 0;

	seq = io_get_sequence(req);
	/* Still a chance to pass the sequence check */
	अगर (!req_need_defer(req, seq) && list_empty_careful(&ctx->defer_list))
		वापस 0;

	ret = io_req_prep_async(req);
	अगर (ret)
		वापस ret;
	io_prep_async_link(req);
	de = kदो_स्मृति(माप(*de), GFP_KERNEL);
	अगर (!de)
		वापस -ENOMEM;

	spin_lock_irq(&ctx->completion_lock);
	अगर (!req_need_defer(req, seq) && list_empty(&ctx->defer_list)) अणु
		spin_unlock_irq(&ctx->completion_lock);
		kमुक्त(de);
		io_queue_async_work(req);
		वापस -EIOCBQUEUED;
	पूर्ण

	trace_io_uring_defer(ctx, req, req->user_data);
	de->req = req;
	de->seq = seq;
	list_add_tail(&de->list, &ctx->defer_list);
	spin_unlock_irq(&ctx->completion_lock);
	वापस -EIOCBQUEUED;
पूर्ण

अटल व्योम io_clean_op(काष्ठा io_kiocb *req)
अणु
	अगर (req->flags & REQ_F_BUFFER_SELECTED) अणु
		चयन (req->opcode) अणु
		हाल IORING_OP_READV:
		हाल IORING_OP_READ_FIXED:
		हाल IORING_OP_READ:
			kमुक्त((व्योम *)(अचिन्हित दीर्घ)req->rw.addr);
			अवरोध;
		हाल IORING_OP_RECVMSG:
		हाल IORING_OP_RECV:
			kमुक्त(req->sr_msg.kbuf);
			अवरोध;
		पूर्ण
		req->flags &= ~REQ_F_BUFFER_SELECTED;
	पूर्ण

	अगर (req->flags & REQ_F_NEED_CLEANUP) अणु
		चयन (req->opcode) अणु
		हाल IORING_OP_READV:
		हाल IORING_OP_READ_FIXED:
		हाल IORING_OP_READ:
		हाल IORING_OP_WRITEV:
		हाल IORING_OP_WRITE_FIXED:
		हाल IORING_OP_WRITE: अणु
			काष्ठा io_async_rw *io = req->async_data;
			अगर (io->मुक्त_iovec)
				kमुक्त(io->मुक्त_iovec);
			अवरोध;
			पूर्ण
		हाल IORING_OP_RECVMSG:
		हाल IORING_OP_SENDMSG: अणु
			काष्ठा io_async_msghdr *io = req->async_data;

			kमुक्त(io->मुक्त_iov);
			अवरोध;
			पूर्ण
		हाल IORING_OP_SPLICE:
		हाल IORING_OP_TEE:
			अगर (!(req->splice.flags & SPLICE_F_FD_IN_FIXED))
				io_put_file(req->splice.file_in);
			अवरोध;
		हाल IORING_OP_OPENAT:
		हाल IORING_OP_OPENAT2:
			अगर (req->खोलो.filename)
				putname(req->खोलो.filename);
			अवरोध;
		हाल IORING_OP_RENAMEAT:
			putname(req->नाम.oldpath);
			putname(req->नाम.newpath);
			अवरोध;
		हाल IORING_OP_UNLINKAT:
			putname(req->unlink.filename);
			अवरोध;
		पूर्ण
		req->flags &= ~REQ_F_NEED_CLEANUP;
	पूर्ण
	अगर ((req->flags & REQ_F_POLLED) && req->apoll) अणु
		kमुक्त(req->apoll->द्विगुन_poll);
		kमुक्त(req->apoll);
		req->apoll = शून्य;
	पूर्ण
	अगर (req->flags & REQ_F_INFLIGHT) अणु
		काष्ठा io_uring_task *tctx = req->task->io_uring;

		atomic_dec(&tctx->inflight_tracked);
		req->flags &= ~REQ_F_INFLIGHT;
	पूर्ण
पूर्ण

अटल पूर्णांक io_issue_sqe(काष्ठा io_kiocb *req, अचिन्हित पूर्णांक issue_flags)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	स्थिर काष्ठा cred *creds = शून्य;
	पूर्णांक ret;

	अगर (req->work.creds && req->work.creds != current_cred())
		creds = override_creds(req->work.creds);

	चयन (req->opcode) अणु
	हाल IORING_OP_NOP:
		ret = io_nop(req, issue_flags);
		अवरोध;
	हाल IORING_OP_READV:
	हाल IORING_OP_READ_FIXED:
	हाल IORING_OP_READ:
		ret = io_पढ़ो(req, issue_flags);
		अवरोध;
	हाल IORING_OP_WRITEV:
	हाल IORING_OP_WRITE_FIXED:
	हाल IORING_OP_WRITE:
		ret = io_ग_लिखो(req, issue_flags);
		अवरोध;
	हाल IORING_OP_FSYNC:
		ret = io_fsync(req, issue_flags);
		अवरोध;
	हाल IORING_OP_POLL_ADD:
		ret = io_poll_add(req, issue_flags);
		अवरोध;
	हाल IORING_OP_POLL_REMOVE:
		ret = io_poll_update(req, issue_flags);
		अवरोध;
	हाल IORING_OP_SYNC_खाता_RANGE:
		ret = io_sync_file_range(req, issue_flags);
		अवरोध;
	हाल IORING_OP_SENDMSG:
		ret = io_sendmsg(req, issue_flags);
		अवरोध;
	हाल IORING_OP_SEND:
		ret = io_send(req, issue_flags);
		अवरोध;
	हाल IORING_OP_RECVMSG:
		ret = io_recvmsg(req, issue_flags);
		अवरोध;
	हाल IORING_OP_RECV:
		ret = io_recv(req, issue_flags);
		अवरोध;
	हाल IORING_OP_TIMEOUT:
		ret = io_समयout(req, issue_flags);
		अवरोध;
	हाल IORING_OP_TIMEOUT_REMOVE:
		ret = io_समयout_हटाओ(req, issue_flags);
		अवरोध;
	हाल IORING_OP_ACCEPT:
		ret = io_accept(req, issue_flags);
		अवरोध;
	हाल IORING_OP_CONNECT:
		ret = io_connect(req, issue_flags);
		अवरोध;
	हाल IORING_OP_ASYNC_CANCEL:
		ret = io_async_cancel(req, issue_flags);
		अवरोध;
	हाल IORING_OP_FALLOCATE:
		ret = io_fallocate(req, issue_flags);
		अवरोध;
	हाल IORING_OP_OPENAT:
		ret = io_खोलोat(req, issue_flags);
		अवरोध;
	हाल IORING_OP_CLOSE:
		ret = io_बंद(req, issue_flags);
		अवरोध;
	हाल IORING_OP_खाताS_UPDATE:
		ret = io_files_update(req, issue_flags);
		अवरोध;
	हाल IORING_OP_STATX:
		ret = io_statx(req, issue_flags);
		अवरोध;
	हाल IORING_OP_FADVISE:
		ret = io_fadvise(req, issue_flags);
		अवरोध;
	हाल IORING_OP_MADVISE:
		ret = io_madvise(req, issue_flags);
		अवरोध;
	हाल IORING_OP_OPENAT2:
		ret = io_खोलोat2(req, issue_flags);
		अवरोध;
	हाल IORING_OP_EPOLL_CTL:
		ret = io_epoll_ctl(req, issue_flags);
		अवरोध;
	हाल IORING_OP_SPLICE:
		ret = io_splice(req, issue_flags);
		अवरोध;
	हाल IORING_OP_PROVIDE_BUFFERS:
		ret = io_provide_buffers(req, issue_flags);
		अवरोध;
	हाल IORING_OP_REMOVE_BUFFERS:
		ret = io_हटाओ_buffers(req, issue_flags);
		अवरोध;
	हाल IORING_OP_TEE:
		ret = io_tee(req, issue_flags);
		अवरोध;
	हाल IORING_OP_SHUTDOWN:
		ret = io_shutकरोwn(req, issue_flags);
		अवरोध;
	हाल IORING_OP_RENAMEAT:
		ret = io_नामat(req, issue_flags);
		अवरोध;
	हाल IORING_OP_UNLINKAT:
		ret = io_unlinkat(req, issue_flags);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (creds)
		revert_creds(creds);

	अगर (ret)
		वापस ret;

	/* If the op करोesn't have a file, we're not polling क्रम it */
	अगर ((ctx->flags & IORING_SETUP_IOPOLL) && req->file) अणु
		स्थिर bool in_async = io_wq_current_is_worker();

		/* workqueue context करोesn't hold uring_lock, grab it now */
		अगर (in_async)
			mutex_lock(&ctx->uring_lock);

		io_iopoll_req_issued(req, in_async);

		अगर (in_async)
			mutex_unlock(&ctx->uring_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम io_wq_submit_work(काष्ठा io_wq_work *work)
अणु
	काष्ठा io_kiocb *req = container_of(work, काष्ठा io_kiocb, work);
	काष्ठा io_kiocb *समयout;
	पूर्णांक ret = 0;

	समयout = io_prep_linked_समयout(req);
	अगर (समयout)
		io_queue_linked_समयout(समयout);

	अगर (work->flags & IO_WQ_WORK_CANCEL)
		ret = -ECANCELED;

	अगर (!ret) अणु
		करो अणु
			ret = io_issue_sqe(req, 0);
			/*
			 * We can get EAGAIN क्रम polled IO even though we're
			 * क्रमcing a sync submission from here, since we can't
			 * रुको क्रम request slots on the block side.
			 */
			अगर (ret != -EAGAIN)
				अवरोध;
			cond_resched();
		पूर्ण जबतक (1);
	पूर्ण

	/* aव्योम locking problems by failing it from a clean context */
	अगर (ret) अणु
		/* io-wq is going to take one करोwn */
		req_ref_get(req);
		io_req_task_queue_fail(req, ret);
	पूर्ण
पूर्ण

#घोषणा FFS_ASYNC_READ		0x1UL
#घोषणा FFS_ASYNC_WRITE		0x2UL
#अगर_घोषित CONFIG_64BIT
#घोषणा FFS_ISREG		0x4UL
#अन्यथा
#घोषणा FFS_ISREG		0x0UL
#पूर्ण_अगर
#घोषणा FFS_MASK		~(FFS_ASYNC_READ|FFS_ASYNC_WRITE|FFS_ISREG)

अटल अंतरभूत काष्ठा io_fixed_file *io_fixed_file_slot(काष्ठा io_file_table *table,
						      अचिन्हित i)
अणु
	काष्ठा io_fixed_file *table_l2;

	table_l2 = table->files[i >> IORING_खाता_TABLE_SHIFT];
	वापस &table_l2[i & IORING_खाता_TABLE_MASK];
पूर्ण

अटल अंतरभूत काष्ठा file *io_file_from_index(काष्ठा io_ring_ctx *ctx,
					      पूर्णांक index)
अणु
	काष्ठा io_fixed_file *slot = io_fixed_file_slot(&ctx->file_table, index);

	वापस (काष्ठा file *) (slot->file_ptr & FFS_MASK);
पूर्ण

अटल व्योम io_fixed_file_set(काष्ठा io_fixed_file *file_slot, काष्ठा file *file)
अणु
	अचिन्हित दीर्घ file_ptr = (अचिन्हित दीर्घ) file;

	अगर (__io_file_supports_async(file, READ))
		file_ptr |= FFS_ASYNC_READ;
	अगर (__io_file_supports_async(file, WRITE))
		file_ptr |= FFS_ASYNC_WRITE;
	अगर (S_ISREG(file_inode(file)->i_mode))
		file_ptr |= FFS_ISREG;
	file_slot->file_ptr = file_ptr;
पूर्ण

अटल काष्ठा file *io_file_get(काष्ठा io_submit_state *state,
				काष्ठा io_kiocb *req, पूर्णांक fd, bool fixed)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;
	काष्ठा file *file;

	अगर (fixed) अणु
		अचिन्हित दीर्घ file_ptr;

		अगर (unlikely((अचिन्हित पूर्णांक)fd >= ctx->nr_user_files))
			वापस शून्य;
		fd = array_index_nospec(fd, ctx->nr_user_files);
		file_ptr = io_fixed_file_slot(&ctx->file_table, fd)->file_ptr;
		file = (काष्ठा file *) (file_ptr & FFS_MASK);
		file_ptr &= ~FFS_MASK;
		/* mask in overlapping REQ_F and FFS bits */
		req->flags |= (file_ptr << REQ_F_ASYNC_READ_BIT);
		io_req_set_rsrc_node(req);
	पूर्ण अन्यथा अणु
		trace_io_uring_file_get(ctx, fd);
		file = __io_file_get(state, fd);

		/* we करोn't allow fixed io_uring files */
		अगर (file && unlikely(file->f_op == &io_uring_fops))
			io_req_track_inflight(req);
	पूर्ण

	वापस file;
पूर्ण

अटल क्रमागत hrसमयr_restart io_link_समयout_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा io_समयout_data *data = container_of(समयr,
						काष्ठा io_समयout_data, समयr);
	काष्ठा io_kiocb *prev, *req = data->req;
	काष्ठा io_ring_ctx *ctx = req->ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->completion_lock, flags);
	prev = req->समयout.head;
	req->समयout.head = शून्य;

	/*
	 * We करोn't expect the list to be empty, that will only happen अगर we
	 * race with the completion of the linked work.
	 */
	अगर (prev) अणु
		io_हटाओ_next_linked(prev);
		अगर (!req_ref_inc_not_zero(prev))
			prev = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&ctx->completion_lock, flags);

	अगर (prev) अणु
		io_async_find_and_cancel(ctx, req, prev->user_data, -ETIME);
		io_put_req_deferred(prev, 1);
		io_put_req_deferred(req, 1);
	पूर्ण अन्यथा अणु
		io_req_complete_post(req, -ETIME, 0);
	पूर्ण
	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम io_queue_linked_समयout(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_ring_ctx *ctx = req->ctx;

	spin_lock_irq(&ctx->completion_lock);
	/*
	 * If the back reference is शून्य, then our linked request finished
	 * beक्रमe we got a chance to setup the समयr
	 */
	अगर (req->समयout.head) अणु
		काष्ठा io_समयout_data *data = req->async_data;

		data->समयr.function = io_link_समयout_fn;
		hrसमयr_start(&data->समयr, बारpec64_to_kसमय(data->ts),
				data->mode);
	पूर्ण
	spin_unlock_irq(&ctx->completion_lock);
	/* drop submission reference */
	io_put_req(req);
पूर्ण

अटल काष्ठा io_kiocb *io_prep_linked_समयout(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_kiocb *nxt = req->link;

	अगर (!nxt || (req->flags & REQ_F_LINK_TIMEOUT) ||
	    nxt->opcode != IORING_OP_LINK_TIMEOUT)
		वापस शून्य;

	nxt->समयout.head = req;
	nxt->flags |= REQ_F_LTIMEOUT_ACTIVE;
	req->flags |= REQ_F_LINK_TIMEOUT;
	वापस nxt;
पूर्ण

अटल व्योम __io_queue_sqe(काष्ठा io_kiocb *req)
अणु
	काष्ठा io_kiocb *linked_समयout = io_prep_linked_समयout(req);
	पूर्णांक ret;

	ret = io_issue_sqe(req, IO_URING_F_NONBLOCK|IO_URING_F_COMPLETE_DEFER);

	/*
	 * We async punt it अगर the file wasn't marked NOWAIT, or अगर the file
	 * करोesn't support non-blocking पढ़ो/ग_लिखो attempts
	 */
	अगर (likely(!ret)) अणु
		/* drop submission reference */
		अगर (req->flags & REQ_F_COMPLETE_INLINE) अणु
			काष्ठा io_ring_ctx *ctx = req->ctx;
			काष्ठा io_comp_state *cs = &ctx->submit_state.comp;

			cs->reqs[cs->nr++] = req;
			अगर (cs->nr == ARRAY_SIZE(cs->reqs))
				io_submit_flush_completions(cs, ctx);
		पूर्ण अन्यथा अणु
			io_put_req(req);
		पूर्ण
	पूर्ण अन्यथा अगर (ret == -EAGAIN && !(req->flags & REQ_F_NOWAIT)) अणु
		अगर (!io_arm_poll_handler(req)) अणु
			/*
			 * Queued up क्रम async execution, worker will release
			 * submit reference when the iocb is actually submitted.
			 */
			io_queue_async_work(req);
		पूर्ण
	पूर्ण अन्यथा अणु
		io_req_complete_failed(req, ret);
	पूर्ण
	अगर (linked_समयout)
		io_queue_linked_समयout(linked_समयout);
पूर्ण

अटल व्योम io_queue_sqe(काष्ठा io_kiocb *req)
अणु
	पूर्णांक ret;

	ret = io_req_defer(req);
	अगर (ret) अणु
		अगर (ret != -EIOCBQUEUED) अणु
fail_req:
			io_req_complete_failed(req, ret);
		पूर्ण
	पूर्ण अन्यथा अगर (req->flags & REQ_F_FORCE_ASYNC) अणु
		ret = io_req_prep_async(req);
		अगर (unlikely(ret))
			जाओ fail_req;
		io_queue_async_work(req);
	पूर्ण अन्यथा अणु
		__io_queue_sqe(req);
	पूर्ण
पूर्ण

/*
 * Check SQE restrictions (opcode and flags).
 *
 * Returns 'true' if SQE is allowed, 'false' otherwise.
 */
अटल अंतरभूत bool io_check_restriction(काष्ठा io_ring_ctx *ctx,
					काष्ठा io_kiocb *req,
					अचिन्हित पूर्णांक sqe_flags)
अणु
	अगर (!ctx->restricted)
		वापस true;

	अगर (!test_bit(req->opcode, ctx->restrictions.sqe_op))
		वापस false;

	अगर ((sqe_flags & ctx->restrictions.sqe_flags_required) !=
	    ctx->restrictions.sqe_flags_required)
		वापस false;

	अगर (sqe_flags & ~(ctx->restrictions.sqe_flags_allowed |
			  ctx->restrictions.sqe_flags_required))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक io_init_req(काष्ठा io_ring_ctx *ctx, काष्ठा io_kiocb *req,
		       स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_submit_state *state;
	अचिन्हित पूर्णांक sqe_flags;
	पूर्णांक personality, ret = 0;

	req->opcode = READ_ONCE(sqe->opcode);
	/* same numerical values with corresponding REQ_F_*, safe to copy */
	req->flags = sqe_flags = READ_ONCE(sqe->flags);
	req->user_data = READ_ONCE(sqe->user_data);
	req->async_data = शून्य;
	req->file = शून्य;
	req->ctx = ctx;
	req->link = शून्य;
	req->fixed_rsrc_refs = शून्य;
	/* one is dropped after submission, the other at completion */
	atomic_set(&req->refs, 2);
	req->task = current;
	req->result = 0;
	req->work.creds = शून्य;

	/* enक्रमce क्रमwards compatibility on users */
	अगर (unlikely(sqe_flags & ~SQE_VALID_FLAGS))
		वापस -EINVAL;
	अगर (unlikely(req->opcode >= IORING_OP_LAST))
		वापस -EINVAL;
	अगर (unlikely(!io_check_restriction(ctx, req, sqe_flags)))
		वापस -EACCES;

	अगर ((sqe_flags & IOSQE_BUFFER_SELECT) &&
	    !io_op_defs[req->opcode].buffer_select)
		वापस -EOPNOTSUPP;

	personality = READ_ONCE(sqe->personality);
	अगर (personality) अणु
		req->work.creds = xa_load(&ctx->personalities, personality);
		अगर (!req->work.creds)
			वापस -EINVAL;
		get_cred(req->work.creds);
	पूर्ण
	state = &ctx->submit_state;

	/*
	 * Plug now अगर we have more than 1 IO left after this, and the target
	 * is potentially a पढ़ो/ग_लिखो to block based storage.
	 */
	अगर (!state->plug_started && state->ios_left > 1 &&
	    io_op_defs[req->opcode].plug) अणु
		blk_start_plug(&state->plug);
		state->plug_started = true;
	पूर्ण

	अगर (io_op_defs[req->opcode].needs_file) अणु
		bool fixed = req->flags & REQ_F_FIXED_खाता;

		req->file = io_file_get(state, req, READ_ONCE(sqe->fd), fixed);
		अगर (unlikely(!req->file))
			ret = -EBADF;
	पूर्ण

	state->ios_left--;
	वापस ret;
पूर्ण

अटल पूर्णांक io_submit_sqe(काष्ठा io_ring_ctx *ctx, काष्ठा io_kiocb *req,
			 स्थिर काष्ठा io_uring_sqe *sqe)
अणु
	काष्ठा io_submit_link *link = &ctx->submit_state.link;
	पूर्णांक ret;

	ret = io_init_req(ctx, req, sqe);
	अगर (unlikely(ret)) अणु
fail_req:
		अगर (link->head) अणु
			/* fail even hard links since we करोn't submit */
			link->head->flags |= REQ_F_FAIL_LINK;
			io_req_complete_failed(link->head, -ECANCELED);
			link->head = शून्य;
		पूर्ण
		io_req_complete_failed(req, ret);
		वापस ret;
	पूर्ण
	ret = io_req_prep(req, sqe);
	अगर (unlikely(ret))
		जाओ fail_req;

	/* करोn't need @sqe from now on */
	trace_io_uring_submit_sqe(ctx, req->opcode, req->user_data,
				true, ctx->flags & IORING_SETUP_SQPOLL);

	/*
	 * If we alपढ़ोy have a head request, queue this one क्रम async
	 * submittal once the head completes. If we करोn't have a head but
	 * IOSQE_IO_LINK is set in the sqe, start a new head. This one will be
	 * submitted sync once the chain is complete. If none of those
	 * conditions are true (normal request), then just queue it.
	 */
	अगर (link->head) अणु
		काष्ठा io_kiocb *head = link->head;

		/*
		 * Taking sequential execution of a link, draining both sides
		 * of the link also fullfils IOSQE_IO_DRAIN semantics क्रम all
		 * requests in the link. So, it drains the head and the
		 * next after the link request. The last one is करोne via
		 * drain_next flag to persist the effect across calls.
		 */
		अगर (req->flags & REQ_F_IO_DRAIN) अणु
			head->flags |= REQ_F_IO_DRAIN;
			ctx->drain_next = 1;
		पूर्ण
		ret = io_req_prep_async(req);
		अगर (unlikely(ret))
			जाओ fail_req;
		trace_io_uring_link(ctx, req, head);
		link->last->link = req;
		link->last = req;

		/* last request of a link, enqueue the link */
		अगर (!(req->flags & (REQ_F_LINK | REQ_F_HARDLINK))) अणु
			io_queue_sqe(head);
			link->head = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(ctx->drain_next)) अणु
			req->flags |= REQ_F_IO_DRAIN;
			ctx->drain_next = 0;
		पूर्ण
		अगर (req->flags & (REQ_F_LINK | REQ_F_HARDLINK)) अणु
			link->head = req;
			link->last = req;
		पूर्ण अन्यथा अणु
			io_queue_sqe(req);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Batched submission is करोne, ensure local IO is flushed out.
 */
अटल व्योम io_submit_state_end(काष्ठा io_submit_state *state,
				काष्ठा io_ring_ctx *ctx)
अणु
	अगर (state->link.head)
		io_queue_sqe(state->link.head);
	अगर (state->comp.nr)
		io_submit_flush_completions(&state->comp, ctx);
	अगर (state->plug_started)
		blk_finish_plug(&state->plug);
	io_state_file_put(state);
पूर्ण

/*
 * Start submission side cache.
 */
अटल व्योम io_submit_state_start(काष्ठा io_submit_state *state,
				  अचिन्हित पूर्णांक max_ios)
अणु
	state->plug_started = false;
	state->ios_left = max_ios;
	/* set only head, no need to init link_last in advance */
	state->link.head = शून्य;
पूर्ण

अटल व्योम io_commit_sqring(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_rings *rings = ctx->rings;

	/*
	 * Ensure any loads from the SQEs are करोne at this poपूर्णांक,
	 * since once we ग_लिखो the new head, the application could
	 * ग_लिखो new data to them.
	 */
	smp_store_release(&rings->sq.head, ctx->cached_sq_head);
पूर्ण

/*
 * Fetch an sqe, अगर one is available. Note that sqe_ptr will poपूर्णांक to memory
 * that is mapped by userspace. This means that care needs to be taken to
 * ensure that पढ़ोs are stable, as we cannot rely on userspace always
 * being a good citizen. If members of the sqe are validated and then later
 * used, it's important that those पढ़ोs are करोne through READ_ONCE() to
 * prevent a re-load करोwn the line.
 */
अटल स्थिर काष्ठा io_uring_sqe *io_get_sqe(काष्ठा io_ring_ctx *ctx)
अणु
	u32 *sq_array = ctx->sq_array;
	अचिन्हित head;

	/*
	 * The cached sq head (or cq tail) serves two purposes:
	 *
	 * 1) allows us to batch the cost of updating the user visible
	 *    head updates.
	 * 2) allows the kernel side to track the head on its own, even
	 *    though the application is the one updating it.
	 */
	head = READ_ONCE(sq_array[ctx->cached_sq_head++ & ctx->sq_mask]);
	अगर (likely(head < ctx->sq_entries))
		वापस &ctx->sq_sqes[head];

	/* drop invalid entries */
	ctx->cached_sq_dropped++;
	WRITE_ONCE(ctx->rings->sq_dropped, ctx->cached_sq_dropped);
	वापस शून्य;
पूर्ण

अटल पूर्णांक io_submit_sqes(काष्ठा io_ring_ctx *ctx, अचिन्हित पूर्णांक nr)
अणु
	पूर्णांक submitted = 0;

	/* make sure SQ entry isn't पढ़ो beक्रमe tail */
	nr = min3(nr, ctx->sq_entries, io_sqring_entries(ctx));

	अगर (!percpu_ref_tryget_many(&ctx->refs, nr))
		वापस -EAGAIN;

	percpu_counter_add(&current->io_uring->inflight, nr);
	refcount_add(nr, &current->usage);
	io_submit_state_start(&ctx->submit_state, nr);

	जबतक (submitted < nr) अणु
		स्थिर काष्ठा io_uring_sqe *sqe;
		काष्ठा io_kiocb *req;

		req = io_alloc_req(ctx);
		अगर (unlikely(!req)) अणु
			अगर (!submitted)
				submitted = -EAGAIN;
			अवरोध;
		पूर्ण
		sqe = io_get_sqe(ctx);
		अगर (unlikely(!sqe)) अणु
			kmem_cache_मुक्त(req_cachep, req);
			अवरोध;
		पूर्ण
		/* will complete beyond this poपूर्णांक, count as submitted */
		submitted++;
		अगर (io_submit_sqe(ctx, req, sqe))
			अवरोध;
	पूर्ण

	अगर (unlikely(submitted != nr)) अणु
		पूर्णांक ref_used = (submitted == -EAGAIN) ? 0 : submitted;
		काष्ठा io_uring_task *tctx = current->io_uring;
		पूर्णांक unused = nr - ref_used;

		percpu_ref_put_many(&ctx->refs, unused);
		percpu_counter_sub(&tctx->inflight, unused);
		put_task_काष्ठा_many(current, unused);
	पूर्ण

	io_submit_state_end(&ctx->submit_state, ctx);
	 /* Commit SQ ring head once we've consumed and submitted all SQEs */
	io_commit_sqring(ctx);

	वापस submitted;
पूर्ण

अटल अंतरभूत व्योम io_ring_set_wakeup_flag(काष्ठा io_ring_ctx *ctx)
अणु
	/* Tell userspace we may need a wakeup call */
	spin_lock_irq(&ctx->completion_lock);
	ctx->rings->sq_flags |= IORING_SQ_NEED_WAKEUP;
	spin_unlock_irq(&ctx->completion_lock);
पूर्ण

अटल अंतरभूत व्योम io_ring_clear_wakeup_flag(काष्ठा io_ring_ctx *ctx)
अणु
	spin_lock_irq(&ctx->completion_lock);
	ctx->rings->sq_flags &= ~IORING_SQ_NEED_WAKEUP;
	spin_unlock_irq(&ctx->completion_lock);
पूर्ण

अटल पूर्णांक __io_sq_thपढ़ो(काष्ठा io_ring_ctx *ctx, bool cap_entries)
अणु
	अचिन्हित पूर्णांक to_submit;
	पूर्णांक ret = 0;

	to_submit = io_sqring_entries(ctx);
	/* अगर we're handling multiple rings, cap submit size क्रम fairness */
	अगर (cap_entries && to_submit > 8)
		to_submit = 8;

	अगर (!list_empty(&ctx->iopoll_list) || to_submit) अणु
		अचिन्हित nr_events = 0;

		mutex_lock(&ctx->uring_lock);
		अगर (!list_empty(&ctx->iopoll_list))
			io_करो_iopoll(ctx, &nr_events, 0);

		/*
		 * Don't submit अगर refs are dying, good क्रम io_uring_रेजिस्टर(),
		 * but also it is relied upon by io_ring_निकास_work()
		 */
		अगर (to_submit && likely(!percpu_ref_is_dying(&ctx->refs)) &&
		    !(ctx->flags & IORING_SETUP_R_DISABLED))
			ret = io_submit_sqes(ctx, to_submit);
		mutex_unlock(&ctx->uring_lock);
	पूर्ण

	अगर (!io_sqring_full(ctx) && wq_has_sleeper(&ctx->sqo_sq_रुको))
		wake_up(&ctx->sqo_sq_रुको);

	वापस ret;
पूर्ण

अटल व्योम io_sqd_update_thपढ़ो_idle(काष्ठा io_sq_data *sqd)
अणु
	काष्ठा io_ring_ctx *ctx;
	अचिन्हित sq_thपढ़ो_idle = 0;

	list_क्रम_each_entry(ctx, &sqd->ctx_list, sqd_list)
		sq_thपढ़ो_idle = max(sq_thपढ़ो_idle, ctx->sq_thपढ़ो_idle);
	sqd->sq_thपढ़ो_idle = sq_thपढ़ो_idle;
पूर्ण

अटल पूर्णांक io_sq_thपढ़ो(व्योम *data)
अणु
	काष्ठा io_sq_data *sqd = data;
	काष्ठा io_ring_ctx *ctx;
	अचिन्हित दीर्घ समयout = 0;
	अक्षर buf[TASK_COMM_LEN];
	DEFINE_WAIT(रुको);

	snम_लिखो(buf, माप(buf), "iou-sqp-%d", sqd->task_pid);
	set_task_comm(current, buf);

	अगर (sqd->sq_cpu != -1)
		set_cpus_allowed_ptr(current, cpumask_of(sqd->sq_cpu));
	अन्यथा
		set_cpus_allowed_ptr(current, cpu_online_mask);
	current->flags |= PF_NO_SETAFFINITY;

	mutex_lock(&sqd->lock);
	/* a user may had निकासed beक्रमe the thपढ़ो started */
	io_run_task_work_head(&sqd->park_task_work);

	जबतक (!test_bit(IO_SQ_THREAD_SHOULD_STOP, &sqd->state)) अणु
		पूर्णांक ret;
		bool cap_entries, sqt_spin, needs_sched;

		अगर (test_bit(IO_SQ_THREAD_SHOULD_PARK, &sqd->state) ||
		    संकेत_pending(current)) अणु
			bool did_sig = false;

			mutex_unlock(&sqd->lock);
			अगर (संकेत_pending(current)) अणु
				काष्ठा kसंकेत ksig;

				did_sig = get_संकेत(&ksig);
			पूर्ण
			cond_resched();
			mutex_lock(&sqd->lock);
			io_run_task_work();
			io_run_task_work_head(&sqd->park_task_work);
			अगर (did_sig)
				अवरोध;
			समयout = jअगरfies + sqd->sq_thपढ़ो_idle;
			जारी;
		पूर्ण
		sqt_spin = false;
		cap_entries = !list_is_singular(&sqd->ctx_list);
		list_क्रम_each_entry(ctx, &sqd->ctx_list, sqd_list) अणु
			स्थिर काष्ठा cred *creds = शून्य;

			अगर (ctx->sq_creds != current_cred())
				creds = override_creds(ctx->sq_creds);
			ret = __io_sq_thपढ़ो(ctx, cap_entries);
			अगर (creds)
				revert_creds(creds);
			अगर (!sqt_spin && (ret > 0 || !list_empty(&ctx->iopoll_list)))
				sqt_spin = true;
		पूर्ण

		अगर (sqt_spin || !समय_after(jअगरfies, समयout)) अणु
			io_run_task_work();
			cond_resched();
			अगर (sqt_spin)
				समयout = jअगरfies + sqd->sq_thपढ़ो_idle;
			जारी;
		पूर्ण

		prepare_to_रुको(&sqd->रुको, &रुको, TASK_INTERRUPTIBLE);
		अगर (!test_bit(IO_SQ_THREAD_SHOULD_PARK, &sqd->state)) अणु
			list_क्रम_each_entry(ctx, &sqd->ctx_list, sqd_list)
				io_ring_set_wakeup_flag(ctx);

			needs_sched = true;
			list_क्रम_each_entry(ctx, &sqd->ctx_list, sqd_list) अणु
				अगर ((ctx->flags & IORING_SETUP_IOPOLL) &&
				    !list_empty_careful(&ctx->iopoll_list)) अणु
					needs_sched = false;
					अवरोध;
				पूर्ण
				अगर (io_sqring_entries(ctx)) अणु
					needs_sched = false;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (needs_sched) अणु
				mutex_unlock(&sqd->lock);
				schedule();
				mutex_lock(&sqd->lock);
			पूर्ण
			list_क्रम_each_entry(ctx, &sqd->ctx_list, sqd_list)
				io_ring_clear_wakeup_flag(ctx);
		पूर्ण

		finish_रुको(&sqd->रुको, &रुको);
		io_run_task_work_head(&sqd->park_task_work);
		समयout = jअगरfies + sqd->sq_thपढ़ो_idle;
	पूर्ण

	io_uring_cancel_sqpoll(sqd);
	sqd->thपढ़ो = शून्य;
	list_क्रम_each_entry(ctx, &sqd->ctx_list, sqd_list)
		io_ring_set_wakeup_flag(ctx);
	io_run_task_work();
	io_run_task_work_head(&sqd->park_task_work);
	mutex_unlock(&sqd->lock);

	complete(&sqd->निकासed);
	करो_निकास(0);
पूर्ण

काष्ठा io_रुको_queue अणु
	काष्ठा रुको_queue_entry wq;
	काष्ठा io_ring_ctx *ctx;
	अचिन्हित to_रुको;
	अचिन्हित nr_समयouts;
पूर्ण;

अटल अंतरभूत bool io_should_wake(काष्ठा io_रुको_queue *iowq)
अणु
	काष्ठा io_ring_ctx *ctx = iowq->ctx;

	/*
	 * Wake up अगर we have enough events, or अगर a समयout occurred since we
	 * started रुकोing. For समयouts, we always want to वापस to userspace,
	 * regardless of event count.
	 */
	वापस io_cqring_events(ctx) >= iowq->to_रुको ||
			atomic_पढ़ो(&ctx->cq_समयouts) != iowq->nr_समयouts;
पूर्ण

अटल पूर्णांक io_wake_function(काष्ठा रुको_queue_entry *curr, अचिन्हित पूर्णांक mode,
			    पूर्णांक wake_flags, व्योम *key)
अणु
	काष्ठा io_रुको_queue *iowq = container_of(curr, काष्ठा io_रुको_queue,
							wq);

	/*
	 * Cannot safely flush overflowed CQEs from here, ensure we wake up
	 * the task, and the next invocation will करो it.
	 */
	अगर (io_should_wake(iowq) || test_bit(0, &iowq->ctx->cq_check_overflow))
		वापस स्वतःहटाओ_wake_function(curr, mode, wake_flags, key);
	वापस -1;
पूर्ण

अटल पूर्णांक io_run_task_work_sig(व्योम)
अणु
	अगर (io_run_task_work())
		वापस 1;
	अगर (!संकेत_pending(current))
		वापस 0;
	अगर (test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL))
		वापस -ERESTARTSYS;
	वापस -EINTR;
पूर्ण

/* when वापसs >0, the caller should retry */
अटल अंतरभूत पूर्णांक io_cqring_रुको_schedule(काष्ठा io_ring_ctx *ctx,
					  काष्ठा io_रुको_queue *iowq,
					  चिन्हित दीर्घ *समयout)
अणु
	पूर्णांक ret;

	/* make sure we run task_work beक्रमe checking क्रम संकेतs */
	ret = io_run_task_work_sig();
	अगर (ret || io_should_wake(iowq))
		वापस ret;
	/* let the caller flush overflows, retry */
	अगर (test_bit(0, &ctx->cq_check_overflow))
		वापस 1;

	*समयout = schedule_समयout(*समयout);
	वापस !*समयout ? -ETIME : 1;
पूर्ण

/*
 * Wait until events become available, अगर we करोn't alपढ़ोy have some. The
 * application must reap them itself, as they reside on the shared cq ring.
 */
अटल पूर्णांक io_cqring_रुको(काष्ठा io_ring_ctx *ctx, पूर्णांक min_events,
			  स्थिर sigset_t __user *sig, माप_प्रकार sigsz,
			  काष्ठा __kernel_बारpec __user *uts)
अणु
	काष्ठा io_रुको_queue iowq = अणु
		.wq = अणु
			.निजी	= current,
			.func		= io_wake_function,
			.entry		= LIST_HEAD_INIT(iowq.wq.entry),
		पूर्ण,
		.ctx		= ctx,
		.to_रुको	= min_events,
	पूर्ण;
	काष्ठा io_rings *rings = ctx->rings;
	चिन्हित दीर्घ समयout = MAX_SCHEDULE_TIMEOUT;
	पूर्णांक ret;

	करो अणु
		io_cqring_overflow_flush(ctx, false);
		अगर (io_cqring_events(ctx) >= min_events)
			वापस 0;
		अगर (!io_run_task_work())
			अवरोध;
	पूर्ण जबतक (1);

	अगर (sig) अणु
#अगर_घोषित CONFIG_COMPAT
		अगर (in_compat_syscall())
			ret = set_compat_user_sigmask((स्थिर compat_sigset_t __user *)sig,
						      sigsz);
		अन्यथा
#पूर्ण_अगर
			ret = set_user_sigmask(sig, sigsz);

		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (uts) अणु
		काष्ठा बारpec64 ts;

		अगर (get_बारpec64(&ts, uts))
			वापस -EFAULT;
		समयout = बारpec64_to_jअगरfies(&ts);
	पूर्ण

	iowq.nr_समयouts = atomic_पढ़ो(&ctx->cq_समयouts);
	trace_io_uring_cqring_रुको(ctx, min_events);
	करो अणु
		/* अगर we can't even flush overflow, don't रुको क्रम more */
		अगर (!io_cqring_overflow_flush(ctx, false)) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण
		prepare_to_रुको_exclusive(&ctx->रुको, &iowq.wq,
						TASK_INTERRUPTIBLE);
		ret = io_cqring_रुको_schedule(ctx, &iowq, &समयout);
		finish_रुको(&ctx->रुको, &iowq.wq);
		cond_resched();
	पूर्ण जबतक (ret > 0);

	restore_saved_sigmask_unless(ret == -EINTR);

	वापस READ_ONCE(rings->cq.head) == READ_ONCE(rings->cq.tail) ? ret : 0;
पूर्ण

अटल व्योम io_मुक्त_file_tables(काष्ठा io_file_table *table, अचिन्हित nr_files)
अणु
	अचिन्हित i, nr_tables = DIV_ROUND_UP(nr_files, IORING_MAX_खाताS_TABLE);

	क्रम (i = 0; i < nr_tables; i++)
		kमुक्त(table->files[i]);
	kमुक्त(table->files);
	table->files = शून्य;
पूर्ण

अटल अंतरभूत व्योम io_rsrc_ref_lock(काष्ठा io_ring_ctx *ctx)
अणु
	spin_lock_bh(&ctx->rsrc_ref_lock);
पूर्ण

अटल अंतरभूत व्योम io_rsrc_ref_unlock(काष्ठा io_ring_ctx *ctx)
अणु
	spin_unlock_bh(&ctx->rsrc_ref_lock);
पूर्ण

अटल व्योम io_rsrc_node_destroy(काष्ठा io_rsrc_node *ref_node)
अणु
	percpu_ref_निकास(&ref_node->refs);
	kमुक्त(ref_node);
पूर्ण

अटल व्योम io_rsrc_node_चयन(काष्ठा io_ring_ctx *ctx,
				काष्ठा io_rsrc_data *data_to_समाप्त)
अणु
	WARN_ON_ONCE(!ctx->rsrc_backup_node);
	WARN_ON_ONCE(data_to_समाप्त && !ctx->rsrc_node);

	अगर (data_to_समाप्त) अणु
		काष्ठा io_rsrc_node *rsrc_node = ctx->rsrc_node;

		rsrc_node->rsrc_data = data_to_समाप्त;
		io_rsrc_ref_lock(ctx);
		list_add_tail(&rsrc_node->node, &ctx->rsrc_ref_list);
		io_rsrc_ref_unlock(ctx);

		atomic_inc(&data_to_समाप्त->refs);
		percpu_ref_समाप्त(&rsrc_node->refs);
		ctx->rsrc_node = शून्य;
	पूर्ण

	अगर (!ctx->rsrc_node) अणु
		ctx->rsrc_node = ctx->rsrc_backup_node;
		ctx->rsrc_backup_node = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक io_rsrc_node_चयन_start(काष्ठा io_ring_ctx *ctx)
अणु
	अगर (ctx->rsrc_backup_node)
		वापस 0;
	ctx->rsrc_backup_node = io_rsrc_node_alloc(ctx);
	वापस ctx->rsrc_backup_node ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक io_rsrc_ref_quiesce(काष्ठा io_rsrc_data *data, काष्ठा io_ring_ctx *ctx)
अणु
	पूर्णांक ret;

	/* As we may drop ->uring_lock, other task may have started quiesce */
	अगर (data->quiesce)
		वापस -ENXIO;

	data->quiesce = true;
	करो अणु
		ret = io_rsrc_node_चयन_start(ctx);
		अगर (ret)
			अवरोध;
		io_rsrc_node_चयन(ctx, data);

		/* समाप्त initial ref, alपढ़ोy quiesced अगर zero */
		अगर (atomic_dec_and_test(&data->refs))
			अवरोध;
		flush_delayed_work(&ctx->rsrc_put_work);
		ret = रुको_क्रम_completion_पूर्णांकerruptible(&data->करोne);
		अगर (!ret)
			अवरोध;

		atomic_inc(&data->refs);
		/* रुको क्रम all works potentially completing data->करोne */
		flush_delayed_work(&ctx->rsrc_put_work);
		reinit_completion(&data->करोne);

		mutex_unlock(&ctx->uring_lock);
		ret = io_run_task_work_sig();
		mutex_lock(&ctx->uring_lock);
	पूर्ण जबतक (ret >= 0);
	data->quiesce = false;

	वापस ret;
पूर्ण

अटल व्योम io_rsrc_data_मुक्त(काष्ठा io_rsrc_data *data)
अणु
	kvमुक्त(data->tags);
	kमुक्त(data);
पूर्ण

अटल काष्ठा io_rsrc_data *io_rsrc_data_alloc(काष्ठा io_ring_ctx *ctx,
					       rsrc_put_fn *करो_put,
					       अचिन्हित nr)
अणु
	काष्ठा io_rsrc_data *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	data->tags = kvसुस्मृति(nr, माप(*data->tags), GFP_KERNEL);
	अगर (!data->tags) अणु
		kमुक्त(data);
		वापस शून्य;
	पूर्ण

	atomic_set(&data->refs, 1);
	data->ctx = ctx;
	data->करो_put = करो_put;
	init_completion(&data->करोne);
	वापस data;
पूर्ण

अटल व्योम __io_sqe_files_unरेजिस्टर(काष्ठा io_ring_ctx *ctx)
अणु
#अगर defined(CONFIG_UNIX)
	अगर (ctx->ring_sock) अणु
		काष्ठा sock *sock = ctx->ring_sock->sk;
		काष्ठा sk_buff *skb;

		जबतक ((skb = skb_dequeue(&sock->sk_receive_queue)) != शून्य)
			kमुक्त_skb(skb);
	पूर्ण
#अन्यथा
	पूर्णांक i;

	क्रम (i = 0; i < ctx->nr_user_files; i++) अणु
		काष्ठा file *file;

		file = io_file_from_index(ctx, i);
		अगर (file)
			fput(file);
	पूर्ण
#पूर्ण_अगर
	io_मुक्त_file_tables(&ctx->file_table, ctx->nr_user_files);
	io_rsrc_data_मुक्त(ctx->file_data);
	ctx->file_data = शून्य;
	ctx->nr_user_files = 0;
पूर्ण

अटल पूर्णांक io_sqe_files_unरेजिस्टर(काष्ठा io_ring_ctx *ctx)
अणु
	पूर्णांक ret;

	अगर (!ctx->file_data)
		वापस -ENXIO;
	ret = io_rsrc_ref_quiesce(ctx->file_data, ctx);
	अगर (!ret)
		__io_sqe_files_unरेजिस्टर(ctx);
	वापस ret;
पूर्ण

अटल व्योम io_sq_thपढ़ो_unpark(काष्ठा io_sq_data *sqd)
	__releases(&sqd->lock)
अणु
	WARN_ON_ONCE(sqd->thपढ़ो == current);

	/*
	 * Do the dance but not conditional clear_bit() because it'd race with
	 * other thपढ़ोs incrementing park_pending and setting the bit.
	 */
	clear_bit(IO_SQ_THREAD_SHOULD_PARK, &sqd->state);
	अगर (atomic_dec_वापस(&sqd->park_pending))
		set_bit(IO_SQ_THREAD_SHOULD_PARK, &sqd->state);
	mutex_unlock(&sqd->lock);
पूर्ण

अटल व्योम io_sq_thपढ़ो_park(काष्ठा io_sq_data *sqd)
	__acquires(&sqd->lock)
अणु
	WARN_ON_ONCE(sqd->thपढ़ो == current);

	atomic_inc(&sqd->park_pending);
	set_bit(IO_SQ_THREAD_SHOULD_PARK, &sqd->state);
	mutex_lock(&sqd->lock);
	अगर (sqd->thपढ़ो)
		wake_up_process(sqd->thपढ़ो);
पूर्ण

अटल व्योम io_sq_thपढ़ो_stop(काष्ठा io_sq_data *sqd)
अणु
	WARN_ON_ONCE(sqd->thपढ़ो == current);
	WARN_ON_ONCE(test_bit(IO_SQ_THREAD_SHOULD_STOP, &sqd->state));

	set_bit(IO_SQ_THREAD_SHOULD_STOP, &sqd->state);
	mutex_lock(&sqd->lock);
	अगर (sqd->thपढ़ो)
		wake_up_process(sqd->thपढ़ो);
	mutex_unlock(&sqd->lock);
	रुको_क्रम_completion(&sqd->निकासed);
पूर्ण

अटल व्योम io_put_sq_data(काष्ठा io_sq_data *sqd)
अणु
	अगर (refcount_dec_and_test(&sqd->refs)) अणु
		WARN_ON_ONCE(atomic_पढ़ो(&sqd->park_pending));

		io_sq_thपढ़ो_stop(sqd);
		kमुक्त(sqd);
	पूर्ण
पूर्ण

अटल व्योम io_sq_thपढ़ो_finish(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_sq_data *sqd = ctx->sq_data;

	अगर (sqd) अणु
		io_sq_thपढ़ो_park(sqd);
		list_del_init(&ctx->sqd_list);
		io_sqd_update_thपढ़ो_idle(sqd);
		io_sq_thपढ़ो_unpark(sqd);

		io_put_sq_data(sqd);
		ctx->sq_data = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा io_sq_data *io_attach_sq_data(काष्ठा io_uring_params *p)
अणु
	काष्ठा io_ring_ctx *ctx_attach;
	काष्ठा io_sq_data *sqd;
	काष्ठा fd f;

	f = fdget(p->wq_fd);
	अगर (!f.file)
		वापस ERR_PTR(-ENXIO);
	अगर (f.file->f_op != &io_uring_fops) अणु
		fdput(f);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ctx_attach = f.file->निजी_data;
	sqd = ctx_attach->sq_data;
	अगर (!sqd) अणु
		fdput(f);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (sqd->task_tgid != current->tgid) अणु
		fdput(f);
		वापस ERR_PTR(-EPERM);
	पूर्ण

	refcount_inc(&sqd->refs);
	fdput(f);
	वापस sqd;
पूर्ण

अटल काष्ठा io_sq_data *io_get_sq_data(काष्ठा io_uring_params *p,
					 bool *attached)
अणु
	काष्ठा io_sq_data *sqd;

	*attached = false;
	अगर (p->flags & IORING_SETUP_ATTACH_WQ) अणु
		sqd = io_attach_sq_data(p);
		अगर (!IS_ERR(sqd)) अणु
			*attached = true;
			वापस sqd;
		पूर्ण
		/* fall through क्रम EPERM हाल, setup new sqd/task */
		अगर (PTR_ERR(sqd) != -EPERM)
			वापस sqd;
	पूर्ण

	sqd = kzalloc(माप(*sqd), GFP_KERNEL);
	अगर (!sqd)
		वापस ERR_PTR(-ENOMEM);

	atomic_set(&sqd->park_pending, 0);
	refcount_set(&sqd->refs, 1);
	INIT_LIST_HEAD(&sqd->ctx_list);
	mutex_init(&sqd->lock);
	init_रुकोqueue_head(&sqd->रुको);
	init_completion(&sqd->निकासed);
	वापस sqd;
पूर्ण

#अगर defined(CONFIG_UNIX)
/*
 * Ensure the UNIX gc is aware of our file set, so we are certain that
 * the io_uring can be safely unरेजिस्टरed on process निकास, even अगर we have
 * loops in the file referencing.
 */
अटल पूर्णांक __io_sqe_files_scm(काष्ठा io_ring_ctx *ctx, पूर्णांक nr, पूर्णांक offset)
अणु
	काष्ठा sock *sk = ctx->ring_sock->sk;
	काष्ठा scm_fp_list *fpl;
	काष्ठा sk_buff *skb;
	पूर्णांक i, nr_files;

	fpl = kzalloc(माप(*fpl), GFP_KERNEL);
	अगर (!fpl)
		वापस -ENOMEM;

	skb = alloc_skb(0, GFP_KERNEL);
	अगर (!skb) अणु
		kमुक्त(fpl);
		वापस -ENOMEM;
	पूर्ण

	skb->sk = sk;

	nr_files = 0;
	fpl->user = get_uid(current_user());
	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा file *file = io_file_from_index(ctx, i + offset);

		अगर (!file)
			जारी;
		fpl->fp[nr_files] = get_file(file);
		unix_inflight(fpl->user, fpl->fp[nr_files]);
		nr_files++;
	पूर्ण

	अगर (nr_files) अणु
		fpl->max = SCM_MAX_FD;
		fpl->count = nr_files;
		UNIXCB(skb).fp = fpl;
		skb->deकाष्ठाor = unix_deकाष्ठा_scm;
		refcount_add(skb->truesize, &sk->sk_wmem_alloc);
		skb_queue_head(&sk->sk_receive_queue, skb);

		क्रम (i = 0; i < nr_files; i++)
			fput(fpl->fp[i]);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
		kमुक्त(fpl);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If UNIX sockets are enabled, fd passing can cause a reference cycle which
 * causes regular reference counting to अवरोध करोwn. We rely on the UNIX
 * garbage collection to take care of this problem क्रम us.
 */
अटल पूर्णांक io_sqe_files_scm(काष्ठा io_ring_ctx *ctx)
अणु
	अचिन्हित left, total;
	पूर्णांक ret = 0;

	total = 0;
	left = ctx->nr_user_files;
	जबतक (left) अणु
		अचिन्हित this_files = min_t(अचिन्हित, left, SCM_MAX_FD);

		ret = __io_sqe_files_scm(ctx, this_files, total);
		अगर (ret)
			अवरोध;
		left -= this_files;
		total += this_files;
	पूर्ण

	अगर (!ret)
		वापस 0;

	जबतक (total < ctx->nr_user_files) अणु
		काष्ठा file *file = io_file_from_index(ctx, total);

		अगर (file)
			fput(file);
		total++;
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक io_sqe_files_scm(काष्ठा io_ring_ctx *ctx)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल bool io_alloc_file_tables(काष्ठा io_file_table *table, अचिन्हित nr_files)
अणु
	अचिन्हित i, nr_tables = DIV_ROUND_UP(nr_files, IORING_MAX_खाताS_TABLE);

	table->files = kसुस्मृति(nr_tables, माप(*table->files), GFP_KERNEL);
	अगर (!table->files)
		वापस false;

	क्रम (i = 0; i < nr_tables; i++) अणु
		अचिन्हित पूर्णांक this_files = min(nr_files, IORING_MAX_खाताS_TABLE);

		table->files[i] = kसुस्मृति(this_files, माप(*table->files[i]),
					GFP_KERNEL);
		अगर (!table->files[i])
			अवरोध;
		nr_files -= this_files;
	पूर्ण

	अगर (i == nr_tables)
		वापस true;

	io_मुक्त_file_tables(table, nr_tables * IORING_MAX_खाताS_TABLE);
	वापस false;
पूर्ण

अटल व्योम io_rsrc_file_put(काष्ठा io_ring_ctx *ctx, काष्ठा io_rsrc_put *prsrc)
अणु
	काष्ठा file *file = prsrc->file;
#अगर defined(CONFIG_UNIX)
	काष्ठा sock *sock = ctx->ring_sock->sk;
	काष्ठा sk_buff_head list, *head = &sock->sk_receive_queue;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	__skb_queue_head_init(&list);

	/*
	 * Find the skb that holds this file in its SCM_RIGHTS. When found,
	 * हटाओ this entry and rearrange the file array.
	 */
	skb = skb_dequeue(head);
	जबतक (skb) अणु
		काष्ठा scm_fp_list *fp;

		fp = UNIXCB(skb).fp;
		क्रम (i = 0; i < fp->count; i++) अणु
			पूर्णांक left;

			अगर (fp->fp[i] != file)
				जारी;

			unix_notinflight(fp->user, fp->fp[i]);
			left = fp->count - 1 - i;
			अगर (left) अणु
				स_हटाओ(&fp->fp[i], &fp->fp[i + 1],
						left * माप(काष्ठा file *));
			पूर्ण
			fp->count--;
			अगर (!fp->count) अणु
				kमुक्त_skb(skb);
				skb = शून्य;
			पूर्ण अन्यथा अणु
				__skb_queue_tail(&list, skb);
			पूर्ण
			fput(file);
			file = शून्य;
			अवरोध;
		पूर्ण

		अगर (!file)
			अवरोध;

		__skb_queue_tail(&list, skb);

		skb = skb_dequeue(head);
	पूर्ण

	अगर (skb_peek(&list)) अणु
		spin_lock_irq(&head->lock);
		जबतक ((skb = __skb_dequeue(&list)) != शून्य)
			__skb_queue_tail(head, skb);
		spin_unlock_irq(&head->lock);
	पूर्ण
#अन्यथा
	fput(file);
#पूर्ण_अगर
पूर्ण

अटल व्योम __io_rsrc_put_work(काष्ठा io_rsrc_node *ref_node)
अणु
	काष्ठा io_rsrc_data *rsrc_data = ref_node->rsrc_data;
	काष्ठा io_ring_ctx *ctx = rsrc_data->ctx;
	काष्ठा io_rsrc_put *prsrc, *पंचांगp;

	list_क्रम_each_entry_safe(prsrc, पंचांगp, &ref_node->rsrc_list, list) अणु
		list_del(&prsrc->list);

		अगर (prsrc->tag) अणु
			bool lock_ring = ctx->flags & IORING_SETUP_IOPOLL;
			अचिन्हित दीर्घ flags;

			io_ring_submit_lock(ctx, lock_ring);
			spin_lock_irqsave(&ctx->completion_lock, flags);
			io_cqring_fill_event(ctx, prsrc->tag, 0, 0);
			ctx->cq_extra++;
			io_commit_cqring(ctx);
			spin_unlock_irqrestore(&ctx->completion_lock, flags);
			io_cqring_ev_posted(ctx);
			io_ring_submit_unlock(ctx, lock_ring);
		पूर्ण

		rsrc_data->करो_put(ctx, prsrc);
		kमुक्त(prsrc);
	पूर्ण

	io_rsrc_node_destroy(ref_node);
	अगर (atomic_dec_and_test(&rsrc_data->refs))
		complete(&rsrc_data->करोne);
पूर्ण

अटल व्योम io_rsrc_put_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा io_ring_ctx *ctx;
	काष्ठा llist_node *node;

	ctx = container_of(work, काष्ठा io_ring_ctx, rsrc_put_work.work);
	node = llist_del_all(&ctx->rsrc_put_llist);

	जबतक (node) अणु
		काष्ठा io_rsrc_node *ref_node;
		काष्ठा llist_node *next = node->next;

		ref_node = llist_entry(node, काष्ठा io_rsrc_node, llist);
		__io_rsrc_put_work(ref_node);
		node = next;
	पूर्ण
पूर्ण

अटल व्योम io_rsrc_node_ref_zero(काष्ठा percpu_ref *ref)
अणु
	काष्ठा io_rsrc_node *node = container_of(ref, काष्ठा io_rsrc_node, refs);
	काष्ठा io_ring_ctx *ctx = node->rsrc_data->ctx;
	bool first_add = false;

	io_rsrc_ref_lock(ctx);
	node->करोne = true;

	जबतक (!list_empty(&ctx->rsrc_ref_list)) अणु
		node = list_first_entry(&ctx->rsrc_ref_list,
					    काष्ठा io_rsrc_node, node);
		/* recycle ref nodes in order */
		अगर (!node->करोne)
			अवरोध;
		list_del(&node->node);
		first_add |= llist_add(&node->llist, &ctx->rsrc_put_llist);
	पूर्ण
	io_rsrc_ref_unlock(ctx);

	अगर (first_add)
		mod_delayed_work(प्रणाली_wq, &ctx->rsrc_put_work, HZ);
पूर्ण

अटल काष्ठा io_rsrc_node *io_rsrc_node_alloc(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_rsrc_node *ref_node;

	ref_node = kzalloc(माप(*ref_node), GFP_KERNEL);
	अगर (!ref_node)
		वापस शून्य;

	अगर (percpu_ref_init(&ref_node->refs, io_rsrc_node_ref_zero,
			    0, GFP_KERNEL)) अणु
		kमुक्त(ref_node);
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&ref_node->node);
	INIT_LIST_HEAD(&ref_node->rsrc_list);
	ref_node->करोne = false;
	वापस ref_node;
पूर्ण

अटल पूर्णांक io_sqe_files_रेजिस्टर(काष्ठा io_ring_ctx *ctx, व्योम __user *arg,
				 अचिन्हित nr_args, u64 __user *tags)
अणु
	__s32 __user *fds = (__s32 __user *) arg;
	काष्ठा file *file;
	पूर्णांक fd, ret;
	अचिन्हित i;
	काष्ठा io_rsrc_data *file_data;

	अगर (ctx->file_data)
		वापस -EBUSY;
	अगर (!nr_args)
		वापस -EINVAL;
	अगर (nr_args > IORING_MAX_FIXED_खाताS)
		वापस -EMखाता;
	ret = io_rsrc_node_चयन_start(ctx);
	अगर (ret)
		वापस ret;

	file_data = io_rsrc_data_alloc(ctx, io_rsrc_file_put, nr_args);
	अगर (!file_data)
		वापस -ENOMEM;
	ctx->file_data = file_data;
	ret = -ENOMEM;
	अगर (!io_alloc_file_tables(&ctx->file_table, nr_args))
		जाओ out_मुक्त;

	क्रम (i = 0; i < nr_args; i++, ctx->nr_user_files++) अणु
		u64 tag = 0;

		अगर ((tags && copy_from_user(&tag, &tags[i], माप(tag))) ||
		    copy_from_user(&fd, &fds[i], माप(fd))) अणु
			ret = -EFAULT;
			जाओ out_fput;
		पूर्ण
		/* allow sparse sets */
		अगर (fd == -1) अणु
			ret = -EINVAL;
			अगर (unlikely(tag))
				जाओ out_fput;
			जारी;
		पूर्ण

		file = fget(fd);
		ret = -EBADF;
		अगर (unlikely(!file))
			जाओ out_fput;

		/*
		 * Don't allow io_uring instances to be रेजिस्टरed. If UNIX
		 * isn't enabled, then this causes a reference cycle and this
		 * instance can never get मुक्तd. If UNIX is enabled we'll
		 * handle it just fine, but there's still no poपूर्णांक in allowing
		 * a ring fd as it करोesn't support regular पढ़ो/ग_लिखो anyway.
		 */
		अगर (file->f_op == &io_uring_fops) अणु
			fput(file);
			जाओ out_fput;
		पूर्ण
		ctx->file_data->tags[i] = tag;
		io_fixed_file_set(io_fixed_file_slot(&ctx->file_table, i), file);
	पूर्ण

	ret = io_sqe_files_scm(ctx);
	अगर (ret) अणु
		__io_sqe_files_unरेजिस्टर(ctx);
		वापस ret;
	पूर्ण

	io_rsrc_node_चयन(ctx, शून्य);
	वापस ret;
out_fput:
	क्रम (i = 0; i < ctx->nr_user_files; i++) अणु
		file = io_file_from_index(ctx, i);
		अगर (file)
			fput(file);
	पूर्ण
	io_मुक्त_file_tables(&ctx->file_table, nr_args);
	ctx->nr_user_files = 0;
out_मुक्त:
	io_rsrc_data_मुक्त(ctx->file_data);
	ctx->file_data = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक io_sqe_file_रेजिस्टर(काष्ठा io_ring_ctx *ctx, काष्ठा file *file,
				पूर्णांक index)
अणु
#अगर defined(CONFIG_UNIX)
	काष्ठा sock *sock = ctx->ring_sock->sk;
	काष्ठा sk_buff_head *head = &sock->sk_receive_queue;
	काष्ठा sk_buff *skb;

	/*
	 * See अगर we can merge this file पूर्णांकo an existing skb SCM_RIGHTS
	 * file set. If there's no room, fall back to allocating a new skb
	 * and filling it in.
	 */
	spin_lock_irq(&head->lock);
	skb = skb_peek(head);
	अगर (skb) अणु
		काष्ठा scm_fp_list *fpl = UNIXCB(skb).fp;

		अगर (fpl->count < SCM_MAX_FD) अणु
			__skb_unlink(skb, head);
			spin_unlock_irq(&head->lock);
			fpl->fp[fpl->count] = get_file(file);
			unix_inflight(fpl->user, fpl->fp[fpl->count]);
			fpl->count++;
			spin_lock_irq(&head->lock);
			__skb_queue_head(head, skb);
		पूर्ण अन्यथा अणु
			skb = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&head->lock);

	अगर (skb) अणु
		fput(file);
		वापस 0;
	पूर्ण

	वापस __io_sqe_files_scm(ctx, 1, index);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक io_queue_rsrc_removal(काष्ठा io_rsrc_data *data, अचिन्हित idx,
				 काष्ठा io_rsrc_node *node, व्योम *rsrc)
अणु
	काष्ठा io_rsrc_put *prsrc;

	prsrc = kzalloc(माप(*prsrc), GFP_KERNEL);
	अगर (!prsrc)
		वापस -ENOMEM;

	prsrc->tag = data->tags[idx];
	prsrc->rsrc = rsrc;
	list_add(&prsrc->list, &node->rsrc_list);
	वापस 0;
पूर्ण

अटल पूर्णांक __io_sqe_files_update(काष्ठा io_ring_ctx *ctx,
				 काष्ठा io_uring_rsrc_update2 *up,
				 अचिन्हित nr_args)
अणु
	u64 __user *tags = u64_to_user_ptr(up->tags);
	__s32 __user *fds = u64_to_user_ptr(up->data);
	काष्ठा io_rsrc_data *data = ctx->file_data;
	काष्ठा io_fixed_file *file_slot;
	काष्ठा file *file;
	पूर्णांक fd, i, err = 0;
	अचिन्हित पूर्णांक करोne;
	bool needs_चयन = false;

	अगर (!ctx->file_data)
		वापस -ENXIO;
	अगर (up->offset + nr_args > ctx->nr_user_files)
		वापस -EINVAL;

	क्रम (करोne = 0; करोne < nr_args; करोne++) अणु
		u64 tag = 0;

		अगर ((tags && copy_from_user(&tag, &tags[करोne], माप(tag))) ||
		    copy_from_user(&fd, &fds[करोne], माप(fd))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर ((fd == IORING_REGISTER_खाताS_SKIP || fd == -1) && tag) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (fd == IORING_REGISTER_खाताS_SKIP)
			जारी;

		i = array_index_nospec(up->offset + करोne, ctx->nr_user_files);
		file_slot = io_fixed_file_slot(&ctx->file_table, i);

		अगर (file_slot->file_ptr) अणु
			file = (काष्ठा file *)(file_slot->file_ptr & FFS_MASK);
			err = io_queue_rsrc_removal(data, up->offset + करोne,
						    ctx->rsrc_node, file);
			अगर (err)
				अवरोध;
			file_slot->file_ptr = 0;
			needs_चयन = true;
		पूर्ण
		अगर (fd != -1) अणु
			file = fget(fd);
			अगर (!file) अणु
				err = -EBADF;
				अवरोध;
			पूर्ण
			/*
			 * Don't allow io_uring instances to be रेजिस्टरed. If
			 * UNIX isn't enabled, then this causes a reference
			 * cycle and this instance can never get मुक्तd. If UNIX
			 * is enabled we'll handle it just fine, but there's
			 * still no poपूर्णांक in allowing a ring fd as it करोesn't
			 * support regular पढ़ो/ग_लिखो anyway.
			 */
			अगर (file->f_op == &io_uring_fops) अणु
				fput(file);
				err = -EBADF;
				अवरोध;
			पूर्ण
			data->tags[up->offset + करोne] = tag;
			io_fixed_file_set(file_slot, file);
			err = io_sqe_file_रेजिस्टर(ctx, file, i);
			अगर (err) अणु
				file_slot->file_ptr = 0;
				fput(file);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (needs_चयन)
		io_rsrc_node_चयन(ctx, data);
	वापस करोne ? करोne : err;
पूर्ण

अटल काष्ठा io_wq_work *io_मुक्त_work(काष्ठा io_wq_work *work)
अणु
	काष्ठा io_kiocb *req = container_of(work, काष्ठा io_kiocb, work);

	req = io_put_req_find_next(req);
	वापस req ? &req->work : शून्य;
पूर्ण

अटल काष्ठा io_wq *io_init_wq_offload(काष्ठा io_ring_ctx *ctx,
					काष्ठा task_काष्ठा *task)
अणु
	काष्ठा io_wq_hash *hash;
	काष्ठा io_wq_data data;
	अचिन्हित पूर्णांक concurrency;

	hash = ctx->hash_map;
	अगर (!hash) अणु
		hash = kzalloc(माप(*hash), GFP_KERNEL);
		अगर (!hash)
			वापस ERR_PTR(-ENOMEM);
		refcount_set(&hash->refs, 1);
		init_रुकोqueue_head(&hash->रुको);
		ctx->hash_map = hash;
	पूर्ण

	data.hash = hash;
	data.task = task;
	data.मुक्त_work = io_मुक्त_work;
	data.करो_work = io_wq_submit_work;

	/* Do QD, or 4 * CPUS, whatever is smallest */
	concurrency = min(ctx->sq_entries, 4 * num_online_cpus());

	वापस io_wq_create(concurrency, &data);
पूर्ण

अटल पूर्णांक io_uring_alloc_task_context(काष्ठा task_काष्ठा *task,
				       काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_uring_task *tctx;
	पूर्णांक ret;

	tctx = kदो_स्मृति(माप(*tctx), GFP_KERNEL);
	अगर (unlikely(!tctx))
		वापस -ENOMEM;

	ret = percpu_counter_init(&tctx->inflight, 0, GFP_KERNEL);
	अगर (unlikely(ret)) अणु
		kमुक्त(tctx);
		वापस ret;
	पूर्ण

	tctx->io_wq = io_init_wq_offload(ctx, task);
	अगर (IS_ERR(tctx->io_wq)) अणु
		ret = PTR_ERR(tctx->io_wq);
		percpu_counter_destroy(&tctx->inflight);
		kमुक्त(tctx);
		वापस ret;
	पूर्ण

	xa_init(&tctx->xa);
	init_रुकोqueue_head(&tctx->रुको);
	tctx->last = शून्य;
	atomic_set(&tctx->in_idle, 0);
	atomic_set(&tctx->inflight_tracked, 0);
	task->io_uring = tctx;
	spin_lock_init(&tctx->task_lock);
	INIT_WQ_LIST(&tctx->task_list);
	tctx->task_state = 0;
	init_task_work(&tctx->task_work, tctx_task_work);
	वापस 0;
पूर्ण

व्योम __io_uring_मुक्त(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा io_uring_task *tctx = tsk->io_uring;

	WARN_ON_ONCE(!xa_empty(&tctx->xa));
	WARN_ON_ONCE(tctx->io_wq);

	percpu_counter_destroy(&tctx->inflight);
	kमुक्त(tctx);
	tsk->io_uring = शून्य;
पूर्ण

अटल पूर्णांक io_sq_offload_create(काष्ठा io_ring_ctx *ctx,
				काष्ठा io_uring_params *p)
अणु
	पूर्णांक ret;

	/* Retain compatibility with failing क्रम an invalid attach attempt */
	अगर ((ctx->flags & (IORING_SETUP_ATTACH_WQ | IORING_SETUP_SQPOLL)) ==
				IORING_SETUP_ATTACH_WQ) अणु
		काष्ठा fd f;

		f = fdget(p->wq_fd);
		अगर (!f.file)
			वापस -ENXIO;
		fdput(f);
		अगर (f.file->f_op != &io_uring_fops)
			वापस -EINVAL;
	पूर्ण
	अगर (ctx->flags & IORING_SETUP_SQPOLL) अणु
		काष्ठा task_काष्ठा *tsk;
		काष्ठा io_sq_data *sqd;
		bool attached;

		sqd = io_get_sq_data(p, &attached);
		अगर (IS_ERR(sqd)) अणु
			ret = PTR_ERR(sqd);
			जाओ err;
		पूर्ण

		ctx->sq_creds = get_current_cred();
		ctx->sq_data = sqd;
		ctx->sq_thपढ़ो_idle = msecs_to_jअगरfies(p->sq_thपढ़ो_idle);
		अगर (!ctx->sq_thपढ़ो_idle)
			ctx->sq_thपढ़ो_idle = HZ;

		io_sq_thपढ़ो_park(sqd);
		list_add(&ctx->sqd_list, &sqd->ctx_list);
		io_sqd_update_thपढ़ो_idle(sqd);
		/* करोn't attach to a dying SQPOLL thपढ़ो, would be racy */
		ret = (attached && !sqd->thपढ़ो) ? -ENXIO : 0;
		io_sq_thपढ़ो_unpark(sqd);

		अगर (ret < 0)
			जाओ err;
		अगर (attached)
			वापस 0;

		अगर (p->flags & IORING_SETUP_SQ_AFF) अणु
			पूर्णांक cpu = p->sq_thपढ़ो_cpu;

			ret = -EINVAL;
			अगर (cpu >= nr_cpu_ids || !cpu_online(cpu))
				जाओ err_sqpoll;
			sqd->sq_cpu = cpu;
		पूर्ण अन्यथा अणु
			sqd->sq_cpu = -1;
		पूर्ण

		sqd->task_pid = current->pid;
		sqd->task_tgid = current->tgid;
		tsk = create_io_thपढ़ो(io_sq_thपढ़ो, sqd, NUMA_NO_NODE);
		अगर (IS_ERR(tsk)) अणु
			ret = PTR_ERR(tsk);
			जाओ err_sqpoll;
		पूर्ण

		sqd->thपढ़ो = tsk;
		ret = io_uring_alloc_task_context(tsk, ctx);
		wake_up_new_task(tsk);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (p->flags & IORING_SETUP_SQ_AFF) अणु
		/* Can't have SQ_AFF without SQPOLL */
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	वापस 0;
err_sqpoll:
	complete(&ctx->sq_data->निकासed);
err:
	io_sq_thपढ़ो_finish(ctx);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम __io_unaccount_mem(काष्ठा user_काष्ठा *user,
				      अचिन्हित दीर्घ nr_pages)
अणु
	atomic_दीर्घ_sub(nr_pages, &user->locked_vm);
पूर्ण

अटल अंतरभूत पूर्णांक __io_account_mem(काष्ठा user_काष्ठा *user,
				   अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ page_limit, cur_pages, new_pages;

	/* Don't allow more pages than we can safely lock */
	page_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

	करो अणु
		cur_pages = atomic_दीर्घ_पढ़ो(&user->locked_vm);
		new_pages = cur_pages + nr_pages;
		अगर (new_pages > page_limit)
			वापस -ENOMEM;
	पूर्ण जबतक (atomic_दीर्घ_cmpxchg(&user->locked_vm, cur_pages,
					new_pages) != cur_pages);

	वापस 0;
पूर्ण

अटल व्योम io_unaccount_mem(काष्ठा io_ring_ctx *ctx, अचिन्हित दीर्घ nr_pages)
अणु
	अगर (ctx->user)
		__io_unaccount_mem(ctx->user, nr_pages);

	अगर (ctx->mm_account)
		atomic64_sub(nr_pages, &ctx->mm_account->pinned_vm);
पूर्ण

अटल पूर्णांक io_account_mem(काष्ठा io_ring_ctx *ctx, अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक ret;

	अगर (ctx->user) अणु
		ret = __io_account_mem(ctx->user, nr_pages);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ctx->mm_account)
		atomic64_add(nr_pages, &ctx->mm_account->pinned_vm);

	वापस 0;
पूर्ण

अटल व्योम io_mem_मुक्त(व्योम *ptr)
अणु
	काष्ठा page *page;

	अगर (!ptr)
		वापस;

	page = virt_to_head_page(ptr);
	अगर (put_page_testzero(page))
		मुक्त_compound_page(page);
पूर्ण

अटल व्योम *io_mem_alloc(माप_प्रकार size)
अणु
	gfp_t gfp_flags = GFP_KERNEL | __GFP_ZERO | __GFP_NOWARN | __GFP_COMP |
				__GFP_NORETRY | __GFP_ACCOUNT;

	वापस (व्योम *) __get_मुक्त_pages(gfp_flags, get_order(size));
पूर्ण

अटल अचिन्हित दीर्घ rings_size(अचिन्हित sq_entries, अचिन्हित cq_entries,
				माप_प्रकार *sq_offset)
अणु
	काष्ठा io_rings *rings;
	माप_प्रकार off, sq_array_size;

	off = काष्ठा_size(rings, cqes, cq_entries);
	अगर (off == SIZE_MAX)
		वापस SIZE_MAX;

#अगर_घोषित CONFIG_SMP
	off = ALIGN(off, SMP_CACHE_BYTES);
	अगर (off == 0)
		वापस SIZE_MAX;
#पूर्ण_अगर

	अगर (sq_offset)
		*sq_offset = off;

	sq_array_size = array_size(माप(u32), sq_entries);
	अगर (sq_array_size == SIZE_MAX)
		वापस SIZE_MAX;

	अगर (check_add_overflow(off, sq_array_size, &off))
		वापस SIZE_MAX;

	वापस off;
पूर्ण

अटल व्योम io_buffer_unmap(काष्ठा io_ring_ctx *ctx, काष्ठा io_mapped_ubuf **slot)
अणु
	काष्ठा io_mapped_ubuf *imu = *slot;
	अचिन्हित पूर्णांक i;

	अगर (imu != ctx->dummy_ubuf) अणु
		क्रम (i = 0; i < imu->nr_bvecs; i++)
			unpin_user_page(imu->bvec[i].bv_page);
		अगर (imu->acct_pages)
			io_unaccount_mem(ctx, imu->acct_pages);
		kvमुक्त(imu);
	पूर्ण
	*slot = शून्य;
पूर्ण

अटल व्योम io_rsrc_buf_put(काष्ठा io_ring_ctx *ctx, काष्ठा io_rsrc_put *prsrc)
अणु
	io_buffer_unmap(ctx, &prsrc->buf);
	prsrc->buf = शून्य;
पूर्ण

अटल व्योम __io_sqe_buffers_unरेजिस्टर(काष्ठा io_ring_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ctx->nr_user_bufs; i++)
		io_buffer_unmap(ctx, &ctx->user_bufs[i]);
	kमुक्त(ctx->user_bufs);
	io_rsrc_data_मुक्त(ctx->buf_data);
	ctx->user_bufs = शून्य;
	ctx->buf_data = शून्य;
	ctx->nr_user_bufs = 0;
पूर्ण

अटल पूर्णांक io_sqe_buffers_unरेजिस्टर(काष्ठा io_ring_ctx *ctx)
अणु
	पूर्णांक ret;

	अगर (!ctx->buf_data)
		वापस -ENXIO;

	ret = io_rsrc_ref_quiesce(ctx->buf_data, ctx);
	अगर (!ret)
		__io_sqe_buffers_unरेजिस्टर(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक io_copy_iov(काष्ठा io_ring_ctx *ctx, काष्ठा iovec *dst,
		       व्योम __user *arg, अचिन्हित index)
अणु
	काष्ठा iovec __user *src;

#अगर_घोषित CONFIG_COMPAT
	अगर (ctx->compat) अणु
		काष्ठा compat_iovec __user *ciovs;
		काष्ठा compat_iovec ciov;

		ciovs = (काष्ठा compat_iovec __user *) arg;
		अगर (copy_from_user(&ciov, &ciovs[index], माप(ciov)))
			वापस -EFAULT;

		dst->iov_base = u64_to_user_ptr((u64)ciov.iov_base);
		dst->iov_len = ciov.iov_len;
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	src = (काष्ठा iovec __user *) arg;
	अगर (copy_from_user(dst, &src[index], माप(*dst)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * Not super efficient, but this is just a registration समय. And we करो cache
 * the last compound head, so generally we'll only do a full search if we don't
 * match that one.
 *
 * We check अगर the given compound head page has alपढ़ोy been accounted, to
 * aव्योम द्विगुन accounting it. This allows us to account the full size of the
 * page, not just the स्थिरituent pages of a huge page.
 */
अटल bool headpage_alपढ़ोy_acct(काष्ठा io_ring_ctx *ctx, काष्ठा page **pages,
				  पूर्णांक nr_pages, काष्ठा page *hpage)
अणु
	पूर्णांक i, j;

	/* check current page array */
	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (!PageCompound(pages[i]))
			जारी;
		अगर (compound_head(pages[i]) == hpage)
			वापस true;
	पूर्ण

	/* check previously रेजिस्टरed pages */
	क्रम (i = 0; i < ctx->nr_user_bufs; i++) अणु
		काष्ठा io_mapped_ubuf *imu = ctx->user_bufs[i];

		क्रम (j = 0; j < imu->nr_bvecs; j++) अणु
			अगर (!PageCompound(imu->bvec[j].bv_page))
				जारी;
			अगर (compound_head(imu->bvec[j].bv_page) == hpage)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक io_buffer_account_pin(काष्ठा io_ring_ctx *ctx, काष्ठा page **pages,
				 पूर्णांक nr_pages, काष्ठा io_mapped_ubuf *imu,
				 काष्ठा page **last_hpage)
अणु
	पूर्णांक i, ret;

	imu->acct_pages = 0;
	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (!PageCompound(pages[i])) अणु
			imu->acct_pages++;
		पूर्ण अन्यथा अणु
			काष्ठा page *hpage;

			hpage = compound_head(pages[i]);
			अगर (hpage == *last_hpage)
				जारी;
			*last_hpage = hpage;
			अगर (headpage_alपढ़ोy_acct(ctx, pages, i, hpage))
				जारी;
			imu->acct_pages += page_size(hpage) >> PAGE_SHIFT;
		पूर्ण
	पूर्ण

	अगर (!imu->acct_pages)
		वापस 0;

	ret = io_account_mem(ctx, imu->acct_pages);
	अगर (ret)
		imu->acct_pages = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक io_sqe_buffer_रेजिस्टर(काष्ठा io_ring_ctx *ctx, काष्ठा iovec *iov,
				  काष्ठा io_mapped_ubuf **pimu,
				  काष्ठा page **last_hpage)
अणु
	काष्ठा io_mapped_ubuf *imu = शून्य;
	काष्ठा vm_area_काष्ठा **vmas = शून्य;
	काष्ठा page **pages = शून्य;
	अचिन्हित दीर्घ off, start, end, ubuf;
	माप_प्रकार size;
	पूर्णांक ret, pret, nr_pages, i;

	अगर (!iov->iov_base) अणु
		*pimu = ctx->dummy_ubuf;
		वापस 0;
	पूर्ण

	ubuf = (अचिन्हित दीर्घ) iov->iov_base;
	end = (ubuf + iov->iov_len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	start = ubuf >> PAGE_SHIFT;
	nr_pages = end - start;

	*pimu = शून्य;
	ret = -ENOMEM;

	pages = kvदो_स्मृति_array(nr_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages)
		जाओ करोne;

	vmas = kvदो_स्मृति_array(nr_pages, माप(काष्ठा vm_area_काष्ठा *),
			      GFP_KERNEL);
	अगर (!vmas)
		जाओ करोne;

	imu = kvदो_स्मृति(काष्ठा_size(imu, bvec, nr_pages), GFP_KERNEL);
	अगर (!imu)
		जाओ करोne;

	ret = 0;
	mmap_पढ़ो_lock(current->mm);
	pret = pin_user_pages(ubuf, nr_pages, FOLL_WRITE | FOLL_LONGTERM,
			      pages, vmas);
	अगर (pret == nr_pages) अणु
		/* करोn't support file backed memory */
		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा vm_area_काष्ठा *vma = vmas[i];

			अगर (vma->vm_file &&
			    !is_file_hugepages(vma->vm_file)) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = pret < 0 ? pret : -EFAULT;
	पूर्ण
	mmap_पढ़ो_unlock(current->mm);
	अगर (ret) अणु
		/*
		 * अगर we did partial map, or found file backed vmas,
		 * release any pages we did get
		 */
		अगर (pret > 0)
			unpin_user_pages(pages, pret);
		जाओ करोne;
	पूर्ण

	ret = io_buffer_account_pin(ctx, pages, pret, imu, last_hpage);
	अगर (ret) अणु
		unpin_user_pages(pages, pret);
		जाओ करोne;
	पूर्ण

	off = ubuf & ~PAGE_MASK;
	size = iov->iov_len;
	क्रम (i = 0; i < nr_pages; i++) अणु
		माप_प्रकार vec_len;

		vec_len = min_t(माप_प्रकार, size, PAGE_SIZE - off);
		imu->bvec[i].bv_page = pages[i];
		imu->bvec[i].bv_len = vec_len;
		imu->bvec[i].bv_offset = off;
		off = 0;
		size -= vec_len;
	पूर्ण
	/* store original address क्रम later verअगरication */
	imu->ubuf = ubuf;
	imu->ubuf_end = ubuf + iov->iov_len;
	imu->nr_bvecs = nr_pages;
	*pimu = imu;
	ret = 0;
करोne:
	अगर (ret)
		kvमुक्त(imu);
	kvमुक्त(pages);
	kvमुक्त(vmas);
	वापस ret;
पूर्ण

अटल पूर्णांक io_buffers_map_alloc(काष्ठा io_ring_ctx *ctx, अचिन्हित पूर्णांक nr_args)
अणु
	ctx->user_bufs = kसुस्मृति(nr_args, माप(*ctx->user_bufs), GFP_KERNEL);
	वापस ctx->user_bufs ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक io_buffer_validate(काष्ठा iovec *iov)
अणु
	अचिन्हित दीर्घ पंचांगp, acct_len = iov->iov_len + (PAGE_SIZE - 1);

	/*
	 * Don't impose further limits on the size and buffer
	 * स्थिरraपूर्णांकs here, we'll -EINVAL later when IO is
	 * submitted अगर they are wrong.
	 */
	अगर (!iov->iov_base)
		वापस iov->iov_len ? -EFAULT : 0;
	अगर (!iov->iov_len)
		वापस -EFAULT;

	/* arbitrary limit, but we need something */
	अगर (iov->iov_len > SZ_1G)
		वापस -EFAULT;

	अगर (check_add_overflow((अचिन्हित दीर्घ)iov->iov_base, acct_len, &पंचांगp))
		वापस -EOVERFLOW;

	वापस 0;
पूर्ण

अटल पूर्णांक io_sqe_buffers_रेजिस्टर(काष्ठा io_ring_ctx *ctx, व्योम __user *arg,
				   अचिन्हित पूर्णांक nr_args, u64 __user *tags)
अणु
	काष्ठा page *last_hpage = शून्य;
	काष्ठा io_rsrc_data *data;
	पूर्णांक i, ret;
	काष्ठा iovec iov;

	अगर (ctx->user_bufs)
		वापस -EBUSY;
	अगर (!nr_args || nr_args > IORING_MAX_REG_BUFFERS)
		वापस -EINVAL;
	ret = io_rsrc_node_चयन_start(ctx);
	अगर (ret)
		वापस ret;
	data = io_rsrc_data_alloc(ctx, io_rsrc_buf_put, nr_args);
	अगर (!data)
		वापस -ENOMEM;
	ret = io_buffers_map_alloc(ctx, nr_args);
	अगर (ret) अणु
		io_rsrc_data_मुक्त(data);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < nr_args; i++, ctx->nr_user_bufs++) अणु
		u64 tag = 0;

		अगर (tags && copy_from_user(&tag, &tags[i], माप(tag))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ret = io_copy_iov(ctx, &iov, arg, i);
		अगर (ret)
			अवरोध;
		ret = io_buffer_validate(&iov);
		अगर (ret)
			अवरोध;
		अगर (!iov.iov_base && tag) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = io_sqe_buffer_रेजिस्टर(ctx, &iov, &ctx->user_bufs[i],
					     &last_hpage);
		अगर (ret)
			अवरोध;
		data->tags[i] = tag;
	पूर्ण

	WARN_ON_ONCE(ctx->buf_data);

	ctx->buf_data = data;
	अगर (ret)
		__io_sqe_buffers_unरेजिस्टर(ctx);
	अन्यथा
		io_rsrc_node_चयन(ctx, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक __io_sqe_buffers_update(काष्ठा io_ring_ctx *ctx,
				   काष्ठा io_uring_rsrc_update2 *up,
				   अचिन्हित पूर्णांक nr_args)
अणु
	u64 __user *tags = u64_to_user_ptr(up->tags);
	काष्ठा iovec iov, __user *iovs = u64_to_user_ptr(up->data);
	काष्ठा page *last_hpage = शून्य;
	bool needs_चयन = false;
	__u32 करोne;
	पूर्णांक i, err;

	अगर (!ctx->buf_data)
		वापस -ENXIO;
	अगर (up->offset + nr_args > ctx->nr_user_bufs)
		वापस -EINVAL;

	क्रम (करोne = 0; करोne < nr_args; करोne++) अणु
		काष्ठा io_mapped_ubuf *imu;
		पूर्णांक offset = up->offset + करोne;
		u64 tag = 0;

		err = io_copy_iov(ctx, &iov, iovs, करोne);
		अगर (err)
			अवरोध;
		अगर (tags && copy_from_user(&tag, &tags[करोne], माप(tag))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		err = io_buffer_validate(&iov);
		अगर (err)
			अवरोध;
		अगर (!iov.iov_base && tag) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		err = io_sqe_buffer_रेजिस्टर(ctx, &iov, &imu, &last_hpage);
		अगर (err)
			अवरोध;

		i = array_index_nospec(offset, ctx->nr_user_bufs);
		अगर (ctx->user_bufs[i] != ctx->dummy_ubuf) अणु
			err = io_queue_rsrc_removal(ctx->buf_data, offset,
						    ctx->rsrc_node, ctx->user_bufs[i]);
			अगर (unlikely(err)) अणु
				io_buffer_unmap(ctx, &imu);
				अवरोध;
			पूर्ण
			ctx->user_bufs[i] = शून्य;
			needs_चयन = true;
		पूर्ण

		ctx->user_bufs[i] = imu;
		ctx->buf_data->tags[offset] = tag;
	पूर्ण

	अगर (needs_चयन)
		io_rsrc_node_चयन(ctx, ctx->buf_data);
	वापस करोne ? करोne : err;
पूर्ण

अटल पूर्णांक io_eventfd_रेजिस्टर(काष्ठा io_ring_ctx *ctx, व्योम __user *arg)
अणु
	__s32 __user *fds = arg;
	पूर्णांक fd;

	अगर (ctx->cq_ev_fd)
		वापस -EBUSY;

	अगर (copy_from_user(&fd, fds, माप(*fds)))
		वापस -EFAULT;

	ctx->cq_ev_fd = eventfd_ctx_fdget(fd);
	अगर (IS_ERR(ctx->cq_ev_fd)) अणु
		पूर्णांक ret = PTR_ERR(ctx->cq_ev_fd);
		ctx->cq_ev_fd = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक io_eventfd_unरेजिस्टर(काष्ठा io_ring_ctx *ctx)
अणु
	अगर (ctx->cq_ev_fd) अणु
		eventfd_ctx_put(ctx->cq_ev_fd);
		ctx->cq_ev_fd = शून्य;
		वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल व्योम io_destroy_buffers(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_buffer *buf;
	अचिन्हित दीर्घ index;

	xa_क्रम_each(&ctx->io_buffers, index, buf)
		__io_हटाओ_buffers(ctx, buf, index, -1U);
पूर्ण

अटल व्योम io_req_cache_मुक्त(काष्ठा list_head *list, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा io_kiocb *req, *nxt;

	list_क्रम_each_entry_safe(req, nxt, list, compl.list) अणु
		अगर (tsk && req->task != tsk)
			जारी;
		list_del(&req->compl.list);
		kmem_cache_मुक्त(req_cachep, req);
	पूर्ण
पूर्ण

अटल व्योम io_req_caches_मुक्त(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_submit_state *submit_state = &ctx->submit_state;
	काष्ठा io_comp_state *cs = &ctx->submit_state.comp;

	mutex_lock(&ctx->uring_lock);

	अगर (submit_state->मुक्त_reqs) अणु
		kmem_cache_मुक्त_bulk(req_cachep, submit_state->मुक्त_reqs,
				     submit_state->reqs);
		submit_state->मुक्त_reqs = 0;
	पूर्ण

	io_flush_cached_locked_reqs(ctx, cs);
	io_req_cache_मुक्त(&cs->मुक्त_list, शून्य);
	mutex_unlock(&ctx->uring_lock);
पूर्ण

अटल bool io_रुको_rsrc_data(काष्ठा io_rsrc_data *data)
अणु
	अगर (!data)
		वापस false;
	अगर (!atomic_dec_and_test(&data->refs))
		रुको_क्रम_completion(&data->करोne);
	वापस true;
पूर्ण

अटल व्योम io_ring_ctx_मुक्त(काष्ठा io_ring_ctx *ctx)
अणु
	io_sq_thपढ़ो_finish(ctx);

	अगर (ctx->mm_account) अणु
		mmdrop(ctx->mm_account);
		ctx->mm_account = शून्य;
	पूर्ण

	mutex_lock(&ctx->uring_lock);
	अगर (io_रुको_rsrc_data(ctx->buf_data))
		__io_sqe_buffers_unरेजिस्टर(ctx);
	अगर (io_रुको_rsrc_data(ctx->file_data))
		__io_sqe_files_unरेजिस्टर(ctx);
	अगर (ctx->rings)
		__io_cqring_overflow_flush(ctx, true);
	mutex_unlock(&ctx->uring_lock);
	io_eventfd_unरेजिस्टर(ctx);
	io_destroy_buffers(ctx);
	अगर (ctx->sq_creds)
		put_cred(ctx->sq_creds);

	/* there are no रेजिस्टरed resources left, nobody uses it */
	अगर (ctx->rsrc_node)
		io_rsrc_node_destroy(ctx->rsrc_node);
	अगर (ctx->rsrc_backup_node)
		io_rsrc_node_destroy(ctx->rsrc_backup_node);
	flush_delayed_work(&ctx->rsrc_put_work);

	WARN_ON_ONCE(!list_empty(&ctx->rsrc_ref_list));
	WARN_ON_ONCE(!llist_empty(&ctx->rsrc_put_llist));

#अगर defined(CONFIG_UNIX)
	अगर (ctx->ring_sock) अणु
		ctx->ring_sock->file = शून्य; /* so that iput() is called */
		sock_release(ctx->ring_sock);
	पूर्ण
#पूर्ण_अगर

	io_mem_मुक्त(ctx->rings);
	io_mem_मुक्त(ctx->sq_sqes);

	percpu_ref_निकास(&ctx->refs);
	मुक्त_uid(ctx->user);
	io_req_caches_मुक्त(ctx);
	अगर (ctx->hash_map)
		io_wq_put_hash(ctx->hash_map);
	kमुक्त(ctx->cancel_hash);
	kमुक्त(ctx->dummy_ubuf);
	kमुक्त(ctx);
पूर्ण

अटल __poll_t io_uring_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा io_ring_ctx *ctx = file->निजी_data;
	__poll_t mask = 0;

	poll_रुको(file, &ctx->cq_रुको, रुको);
	/*
	 * synchronizes with barrier from wq_has_sleeper call in
	 * io_commit_cqring
	 */
	smp_rmb();
	अगर (!io_sqring_full(ctx))
		mask |= EPOLLOUT | EPOLLWRNORM;

	/*
	 * Don't flush cqring overflow list here, just करो a simple check.
	 * Otherwise there could possible be ABBA deadlock:
	 *      CPU0                    CPU1
	 *      ----                    ----
	 * lock(&ctx->uring_lock);
	 *                              lock(&ep->mtx);
	 *                              lock(&ctx->uring_lock);
	 * lock(&ep->mtx);
	 *
	 * Users may get EPOLLIN meanजबतक seeing nothing in cqring, this
	 * pushs them to करो the flush.
	 */
	अगर (io_cqring_events(ctx) || test_bit(0, &ctx->cq_check_overflow))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल पूर्णांक io_uring_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा io_ring_ctx *ctx = file->निजी_data;

	वापस fasync_helper(fd, file, on, &ctx->cq_fasync);
पूर्ण

अटल पूर्णांक io_unरेजिस्टर_personality(काष्ठा io_ring_ctx *ctx, अचिन्हित id)
अणु
	स्थिर काष्ठा cred *creds;

	creds = xa_erase(&ctx->personalities, id);
	अगर (creds) अणु
		put_cred(creds);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत bool io_run_ctx_fallback(काष्ठा io_ring_ctx *ctx)
अणु
	वापस io_run_task_work_head(&ctx->निकास_task_work);
पूर्ण

काष्ठा io_tctx_निकास अणु
	काष्ठा callback_head		task_work;
	काष्ठा completion		completion;
	काष्ठा io_ring_ctx		*ctx;
पूर्ण;

अटल व्योम io_tctx_निकास_cb(काष्ठा callback_head *cb)
अणु
	काष्ठा io_uring_task *tctx = current->io_uring;
	काष्ठा io_tctx_निकास *work;

	work = container_of(cb, काष्ठा io_tctx_निकास, task_work);
	/*
	 * When @in_idle, we're in cancellation and it's racy to हटाओ the
	 * node. It'll be हटाओd by the end of cancellation, just ignore it.
	 */
	अगर (!atomic_पढ़ो(&tctx->in_idle))
		io_uring_del_task_file((अचिन्हित दीर्घ)work->ctx);
	complete(&work->completion);
पूर्ण

अटल bool io_cancel_ctx_cb(काष्ठा io_wq_work *work, व्योम *data)
अणु
	काष्ठा io_kiocb *req = container_of(work, काष्ठा io_kiocb, work);

	वापस req->ctx == data;
पूर्ण

अटल व्योम io_ring_निकास_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा io_ring_ctx *ctx = container_of(work, काष्ठा io_ring_ctx, निकास_work);
	अचिन्हित दीर्घ समयout = jअगरfies + HZ * 60 * 5;
	काष्ठा io_tctx_निकास निकास;
	काष्ठा io_tctx_node *node;
	पूर्णांक ret;

	/*
	 * If we're करोing polled IO and end up having requests being
	 * submitted async (out-of-line), then completions can come in जबतक
	 * we're रुकोing क्रम refs to drop. We need to reap these manually,
	 * as nobody अन्यथा will be looking क्रम them.
	 */
	करो अणु
		io_uring_try_cancel_requests(ctx, शून्य, शून्य);
		अगर (ctx->sq_data) अणु
			काष्ठा io_sq_data *sqd = ctx->sq_data;
			काष्ठा task_काष्ठा *tsk;

			io_sq_thपढ़ो_park(sqd);
			tsk = sqd->thपढ़ो;
			अगर (tsk && tsk->io_uring && tsk->io_uring->io_wq)
				io_wq_cancel_cb(tsk->io_uring->io_wq,
						io_cancel_ctx_cb, ctx, true);
			io_sq_thपढ़ो_unpark(sqd);
		पूर्ण

		WARN_ON_ONCE(समय_after(jअगरfies, समयout));
	पूर्ण जबतक (!रुको_क्रम_completion_समयout(&ctx->ref_comp, HZ/20));

	init_completion(&निकास.completion);
	init_task_work(&निकास.task_work, io_tctx_निकास_cb);
	निकास.ctx = ctx;
	/*
	 * Some may use context even when all refs and requests have been put,
	 * and they are मुक्त to करो so जबतक still holding uring_lock or
	 * completion_lock, see __io_req_task_submit(). Apart from other work,
	 * this lock/unlock section also रुकोs them to finish.
	 */
	mutex_lock(&ctx->uring_lock);
	जबतक (!list_empty(&ctx->tctx_list)) अणु
		WARN_ON_ONCE(समय_after(jअगरfies, समयout));

		node = list_first_entry(&ctx->tctx_list, काष्ठा io_tctx_node,
					ctx_node);
		/* करोn't spin on a single task अगर cancellation failed */
		list_rotate_left(&ctx->tctx_list);
		ret = task_work_add(node->task, &निकास.task_work, TWA_SIGNAL);
		अगर (WARN_ON_ONCE(ret))
			जारी;
		wake_up_process(node->task);

		mutex_unlock(&ctx->uring_lock);
		रुको_क्रम_completion(&निकास.completion);
		mutex_lock(&ctx->uring_lock);
	पूर्ण
	mutex_unlock(&ctx->uring_lock);
	spin_lock_irq(&ctx->completion_lock);
	spin_unlock_irq(&ctx->completion_lock);

	io_ring_ctx_मुक्त(ctx);
पूर्ण

/* Returns true अगर we found and समाप्तed one or more समयouts */
अटल bool io_समाप्त_समयouts(काष्ठा io_ring_ctx *ctx, काष्ठा task_काष्ठा *tsk,
			     काष्ठा files_काष्ठा *files)
अणु
	काष्ठा io_kiocb *req, *पंचांगp;
	पूर्णांक canceled = 0;

	spin_lock_irq(&ctx->completion_lock);
	list_क्रम_each_entry_safe(req, पंचांगp, &ctx->समयout_list, समयout.list) अणु
		अगर (io_match_task(req, tsk, files)) अणु
			io_समाप्त_समयout(req, -ECANCELED);
			canceled++;
		पूर्ण
	पूर्ण
	अगर (canceled != 0)
		io_commit_cqring(ctx);
	spin_unlock_irq(&ctx->completion_lock);
	अगर (canceled != 0)
		io_cqring_ev_posted(ctx);
	वापस canceled != 0;
पूर्ण

अटल व्योम io_ring_ctx_रुको_and_समाप्त(काष्ठा io_ring_ctx *ctx)
अणु
	अचिन्हित दीर्घ index;
	काष्ठा creds *creds;

	mutex_lock(&ctx->uring_lock);
	percpu_ref_समाप्त(&ctx->refs);
	अगर (ctx->rings)
		__io_cqring_overflow_flush(ctx, true);
	xa_क्रम_each(&ctx->personalities, index, creds)
		io_unरेजिस्टर_personality(ctx, index);
	mutex_unlock(&ctx->uring_lock);

	io_समाप्त_समयouts(ctx, शून्य, शून्य);
	io_poll_हटाओ_all(ctx, शून्य, शून्य);

	/* अगर we failed setting up the ctx, we might not have any rings */
	io_iopoll_try_reap_events(ctx);

	INIT_WORK(&ctx->निकास_work, io_ring_निकास_work);
	/*
	 * Use प्रणाली_unbound_wq to aव्योम spawning tons of event kworkers
	 * अगर we're निकासing a ton of rings at the same समय. It just adds
	 * noise and overhead, there's no discernable change in runसमय
	 * over using प्रणाली_wq.
	 */
	queue_work(प्रणाली_unbound_wq, &ctx->निकास_work);
पूर्ण

अटल पूर्णांक io_uring_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा io_ring_ctx *ctx = file->निजी_data;

	file->निजी_data = शून्य;
	io_ring_ctx_रुको_and_समाप्त(ctx);
	वापस 0;
पूर्ण

काष्ठा io_task_cancel अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा files_काष्ठा *files;
पूर्ण;

अटल bool io_cancel_task_cb(काष्ठा io_wq_work *work, व्योम *data)
अणु
	काष्ठा io_kiocb *req = container_of(work, काष्ठा io_kiocb, work);
	काष्ठा io_task_cancel *cancel = data;
	bool ret;

	अगर (cancel->files && (req->flags & REQ_F_LINK_TIMEOUT)) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा io_ring_ctx *ctx = req->ctx;

		/* protect against races with linked समयouts */
		spin_lock_irqsave(&ctx->completion_lock, flags);
		ret = io_match_task(req, cancel->task, cancel->files);
		spin_unlock_irqrestore(&ctx->completion_lock, flags);
	पूर्ण अन्यथा अणु
		ret = io_match_task(req, cancel->task, cancel->files);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool io_cancel_defer_files(काष्ठा io_ring_ctx *ctx,
				  काष्ठा task_काष्ठा *task,
				  काष्ठा files_काष्ठा *files)
अणु
	काष्ठा io_defer_entry *de;
	LIST_HEAD(list);

	spin_lock_irq(&ctx->completion_lock);
	list_क्रम_each_entry_reverse(de, &ctx->defer_list, list) अणु
		अगर (io_match_task(de->req, task, files)) अणु
			list_cut_position(&list, &ctx->defer_list, &de->list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ctx->completion_lock);
	अगर (list_empty(&list))
		वापस false;

	जबतक (!list_empty(&list)) अणु
		de = list_first_entry(&list, काष्ठा io_defer_entry, list);
		list_del_init(&de->list);
		io_req_complete_failed(de->req, -ECANCELED);
		kमुक्त(de);
	पूर्ण
	वापस true;
पूर्ण

अटल bool io_uring_try_cancel_iowq(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_tctx_node *node;
	क्रमागत io_wq_cancel cret;
	bool ret = false;

	mutex_lock(&ctx->uring_lock);
	list_क्रम_each_entry(node, &ctx->tctx_list, ctx_node) अणु
		काष्ठा io_uring_task *tctx = node->task->io_uring;

		/*
		 * io_wq will stay alive जबतक we hold uring_lock, because it's
		 * समाप्तed after ctx nodes, which requires to take the lock.
		 */
		अगर (!tctx || !tctx->io_wq)
			जारी;
		cret = io_wq_cancel_cb(tctx->io_wq, io_cancel_ctx_cb, ctx, true);
		ret |= (cret != IO_WQ_CANCEL_NOTFOUND);
	पूर्ण
	mutex_unlock(&ctx->uring_lock);

	वापस ret;
पूर्ण

अटल व्योम io_uring_try_cancel_requests(काष्ठा io_ring_ctx *ctx,
					 काष्ठा task_काष्ठा *task,
					 काष्ठा files_काष्ठा *files)
अणु
	काष्ठा io_task_cancel cancel = अणु .task = task, .files = files, पूर्ण;
	काष्ठा io_uring_task *tctx = task ? task->io_uring : शून्य;

	जबतक (1) अणु
		क्रमागत io_wq_cancel cret;
		bool ret = false;

		अगर (!task) अणु
			ret |= io_uring_try_cancel_iowq(ctx);
		पूर्ण अन्यथा अगर (tctx && tctx->io_wq) अणु
			/*
			 * Cancels requests of all rings, not only @ctx, but
			 * it's fine as the task is in निकास/exec.
			 */
			cret = io_wq_cancel_cb(tctx->io_wq, io_cancel_task_cb,
					       &cancel, true);
			ret |= (cret != IO_WQ_CANCEL_NOTFOUND);
		पूर्ण

		/* SQPOLL thपढ़ो करोes its own polling */
		अगर ((!(ctx->flags & IORING_SETUP_SQPOLL) && !files) ||
		    (ctx->sq_data && ctx->sq_data->thपढ़ो == current)) अणु
			जबतक (!list_empty_careful(&ctx->iopoll_list)) अणु
				io_iopoll_try_reap_events(ctx);
				ret = true;
			पूर्ण
		पूर्ण

		ret |= io_cancel_defer_files(ctx, task, files);
		ret |= io_poll_हटाओ_all(ctx, task, files);
		ret |= io_समाप्त_समयouts(ctx, task, files);
		ret |= io_run_task_work();
		ret |= io_run_ctx_fallback(ctx);
		अगर (!ret)
			अवरोध;
		cond_resched();
	पूर्ण
पूर्ण

अटल पूर्णांक __io_uring_add_task_file(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_uring_task *tctx = current->io_uring;
	काष्ठा io_tctx_node *node;
	पूर्णांक ret;

	अगर (unlikely(!tctx)) अणु
		ret = io_uring_alloc_task_context(current, ctx);
		अगर (unlikely(ret))
			वापस ret;
		tctx = current->io_uring;
	पूर्ण
	अगर (!xa_load(&tctx->xa, (अचिन्हित दीर्घ)ctx)) अणु
		node = kदो_स्मृति(माप(*node), GFP_KERNEL);
		अगर (!node)
			वापस -ENOMEM;
		node->ctx = ctx;
		node->task = current;

		ret = xa_err(xa_store(&tctx->xa, (अचिन्हित दीर्घ)ctx,
					node, GFP_KERNEL));
		अगर (ret) अणु
			kमुक्त(node);
			वापस ret;
		पूर्ण

		mutex_lock(&ctx->uring_lock);
		list_add(&node->ctx_node, &ctx->tctx_list);
		mutex_unlock(&ctx->uring_lock);
	पूर्ण
	tctx->last = ctx;
	वापस 0;
पूर्ण

/*
 * Note that this task has used io_uring. We use it क्रम cancelation purposes.
 */
अटल अंतरभूत पूर्णांक io_uring_add_task_file(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा io_uring_task *tctx = current->io_uring;

	अगर (likely(tctx && tctx->last == ctx))
		वापस 0;
	वापस __io_uring_add_task_file(ctx);
पूर्ण

/*
 * Remove this io_uring_file -> task mapping.
 */
अटल व्योम io_uring_del_task_file(अचिन्हित दीर्घ index)
अणु
	काष्ठा io_uring_task *tctx = current->io_uring;
	काष्ठा io_tctx_node *node;

	अगर (!tctx)
		वापस;
	node = xa_erase(&tctx->xa, index);
	अगर (!node)
		वापस;

	WARN_ON_ONCE(current != node->task);
	WARN_ON_ONCE(list_empty(&node->ctx_node));

	mutex_lock(&node->ctx->uring_lock);
	list_del(&node->ctx_node);
	mutex_unlock(&node->ctx->uring_lock);

	अगर (tctx->last == node->ctx)
		tctx->last = शून्य;
	kमुक्त(node);
पूर्ण

अटल व्योम io_uring_clean_tctx(काष्ठा io_uring_task *tctx)
अणु
	काष्ठा io_wq *wq = tctx->io_wq;
	काष्ठा io_tctx_node *node;
	अचिन्हित दीर्घ index;

	xa_क्रम_each(&tctx->xa, index, node)
		io_uring_del_task_file(index);
	अगर (wq) अणु
		/*
		 * Must be after io_uring_del_task_file() (हटाओs nodes under
		 * uring_lock) to aव्योम race with io_uring_try_cancel_iowq().
		 */
		tctx->io_wq = शून्य;
		io_wq_put_and_निकास(wq);
	पूर्ण
पूर्ण

अटल s64 tctx_inflight(काष्ठा io_uring_task *tctx, bool tracked)
अणु
	अगर (tracked)
		वापस atomic_पढ़ो(&tctx->inflight_tracked);
	वापस percpu_counter_sum(&tctx->inflight);
पूर्ण

अटल व्योम io_uring_try_cancel(काष्ठा files_काष्ठा *files)
अणु
	काष्ठा io_uring_task *tctx = current->io_uring;
	काष्ठा io_tctx_node *node;
	अचिन्हित दीर्घ index;

	xa_क्रम_each(&tctx->xa, index, node) अणु
		काष्ठा io_ring_ctx *ctx = node->ctx;

		/* sqpoll task will cancel all its requests */
		अगर (!ctx->sq_data)
			io_uring_try_cancel_requests(ctx, current, files);
	पूर्ण
पूर्ण

/* should only be called by SQPOLL task */
अटल व्योम io_uring_cancel_sqpoll(काष्ठा io_sq_data *sqd)
अणु
	काष्ठा io_uring_task *tctx = current->io_uring;
	काष्ठा io_ring_ctx *ctx;
	s64 inflight;
	DEFINE_WAIT(रुको);

	अगर (!current->io_uring)
		वापस;
	अगर (tctx->io_wq)
		io_wq_निकास_start(tctx->io_wq);

	WARN_ON_ONCE(!sqd || sqd->thपढ़ो != current);

	atomic_inc(&tctx->in_idle);
	करो अणु
		/* पढ़ो completions beक्रमe cancelations */
		inflight = tctx_inflight(tctx, false);
		अगर (!inflight)
			अवरोध;
		list_क्रम_each_entry(ctx, &sqd->ctx_list, sqd_list)
			io_uring_try_cancel_requests(ctx, current, शून्य);

		prepare_to_रुको(&tctx->रुको, &रुको, TASK_UNINTERRUPTIBLE);
		/*
		 * If we've seen completions, retry without रुकोing. This
		 * aव्योमs a race where a completion comes in beक्रमe we did
		 * prepare_to_रुको().
		 */
		अगर (inflight == tctx_inflight(tctx, false))
			schedule();
		finish_रुको(&tctx->रुको, &रुको);
	पूर्ण जबतक (1);
	atomic_dec(&tctx->in_idle);
पूर्ण

/*
 * Find any io_uring fd that this task has रेजिस्टरed or करोne IO on, and cancel
 * requests.
 */
व्योम __io_uring_cancel(काष्ठा files_काष्ठा *files)
अणु
	काष्ठा io_uring_task *tctx = current->io_uring;
	DEFINE_WAIT(रुको);
	s64 inflight;

	अगर (tctx->io_wq)
		io_wq_निकास_start(tctx->io_wq);

	/* make sure overflow events are dropped */
	atomic_inc(&tctx->in_idle);
	करो अणु
		/* पढ़ो completions beक्रमe cancelations */
		inflight = tctx_inflight(tctx, !!files);
		अगर (!inflight)
			अवरोध;
		io_uring_try_cancel(files);
		prepare_to_रुको(&tctx->रुको, &रुको, TASK_UNINTERRUPTIBLE);

		/*
		 * If we've seen completions, retry without रुकोing. This
		 * aव्योमs a race where a completion comes in beक्रमe we did
		 * prepare_to_रुको().
		 */
		अगर (inflight == tctx_inflight(tctx, !!files))
			schedule();
		finish_रुको(&tctx->रुको, &रुको);
	पूर्ण जबतक (1);
	atomic_dec(&tctx->in_idle);

	io_uring_clean_tctx(tctx);
	अगर (!files) अणु
		/* क्रम exec all current's requests should be gone, समाप्त tctx */
		__io_uring_मुक्त(current);
	पूर्ण
पूर्ण

अटल व्योम *io_uring_validate_mmap_request(काष्ठा file *file,
					    loff_t pgoff, माप_प्रकार sz)
अणु
	काष्ठा io_ring_ctx *ctx = file->निजी_data;
	loff_t offset = pgoff << PAGE_SHIFT;
	काष्ठा page *page;
	व्योम *ptr;

	चयन (offset) अणु
	हाल IORING_OFF_SQ_RING:
	हाल IORING_OFF_CQ_RING:
		ptr = ctx->rings;
		अवरोध;
	हाल IORING_OFF_SQES:
		ptr = ctx->sq_sqes;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	page = virt_to_head_page(ptr);
	अगर (sz > page_size(page))
		वापस ERR_PTR(-EINVAL);

	वापस ptr;
पूर्ण

#अगर_घोषित CONFIG_MMU

अटल पूर्णांक io_uring_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	माप_प्रकार sz = vma->vm_end - vma->vm_start;
	अचिन्हित दीर्घ pfn;
	व्योम *ptr;

	ptr = io_uring_validate_mmap_request(file, vma->vm_pgoff, sz);
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);

	pfn = virt_to_phys(ptr) >> PAGE_SHIFT;
	वापस remap_pfn_range(vma, vma->vm_start, pfn, sz, vma->vm_page_prot);
पूर्ण

#अन्यथा /* !CONFIG_MMU */

अटल पूर्णांक io_uring_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & (VM_SHARED | VM_MAYSHARE) ? 0 : -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक io_uring_nommu_mmap_capabilities(काष्ठा file *file)
अणु
	वापस NOMMU_MAP_सूचीECT | NOMMU_MAP_READ | NOMMU_MAP_WRITE;
पूर्ण

अटल अचिन्हित दीर्घ io_uring_nommu_get_unmapped_area(काष्ठा file *file,
	अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	व्योम *ptr;

	ptr = io_uring_validate_mmap_request(file, pgoff, len);
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);

	वापस (अचिन्हित दीर्घ) ptr;
पूर्ण

#पूर्ण_अगर /* !CONFIG_MMU */

अटल पूर्णांक io_sqpoll_रुको_sq(काष्ठा io_ring_ctx *ctx)
अणु
	DEFINE_WAIT(रुको);

	करो अणु
		अगर (!io_sqring_full(ctx))
			अवरोध;
		prepare_to_रुको(&ctx->sqo_sq_रुको, &रुको, TASK_INTERRUPTIBLE);

		अगर (!io_sqring_full(ctx))
			अवरोध;
		schedule();
	पूर्ण जबतक (!संकेत_pending(current));

	finish_रुको(&ctx->sqo_sq_रुको, &रुको);
	वापस 0;
पूर्ण

अटल पूर्णांक io_get_ext_arg(अचिन्हित flags, स्थिर व्योम __user *argp, माप_प्रकार *argsz,
			  काष्ठा __kernel_बारpec __user **ts,
			  स्थिर sigset_t __user **sig)
अणु
	काष्ठा io_uring_getevents_arg arg;

	/*
	 * If EXT_ARG isn't set, then we have no बारpec and the argp poपूर्णांकer
	 * is just a poपूर्णांकer to the sigset_t.
	 */
	अगर (!(flags & IORING_ENTER_EXT_ARG)) अणु
		*sig = (स्थिर sigset_t __user *) argp;
		*ts = शून्य;
		वापस 0;
	पूर्ण

	/*
	 * EXT_ARG is set - ensure we agree on the size of it and copy in our
	 * बारpec and sigset_t poपूर्णांकers अगर good.
	 */
	अगर (*argsz != माप(arg))
		वापस -EINVAL;
	अगर (copy_from_user(&arg, argp, माप(arg)))
		वापस -EFAULT;
	*sig = u64_to_user_ptr(arg.sigmask);
	*argsz = arg.sigmask_sz;
	*ts = u64_to_user_ptr(arg.ts);
	वापस 0;
पूर्ण

SYSCALL_DEFINE6(io_uring_enter, अचिन्हित पूर्णांक, fd, u32, to_submit,
		u32, min_complete, u32, flags, स्थिर व्योम __user *, argp,
		माप_प्रकार, argsz)
अणु
	काष्ठा io_ring_ctx *ctx;
	पूर्णांक submitted = 0;
	काष्ठा fd f;
	दीर्घ ret;

	io_run_task_work();

	अगर (unlikely(flags & ~(IORING_ENTER_GETEVENTS | IORING_ENTER_SQ_WAKEUP |
			       IORING_ENTER_SQ_WAIT | IORING_ENTER_EXT_ARG)))
		वापस -EINVAL;

	f = fdget(fd);
	अगर (unlikely(!f.file))
		वापस -EBADF;

	ret = -EOPNOTSUPP;
	अगर (unlikely(f.file->f_op != &io_uring_fops))
		जाओ out_fput;

	ret = -ENXIO;
	ctx = f.file->निजी_data;
	अगर (unlikely(!percpu_ref_tryget(&ctx->refs)))
		जाओ out_fput;

	ret = -EBADFD;
	अगर (unlikely(ctx->flags & IORING_SETUP_R_DISABLED))
		जाओ out;

	/*
	 * For SQ polling, the thपढ़ो will करो all submissions and completions.
	 * Just वापस the requested submit count, and wake the thपढ़ो अगर
	 * we were asked to.
	 */
	ret = 0;
	अगर (ctx->flags & IORING_SETUP_SQPOLL) अणु
		io_cqring_overflow_flush(ctx, false);

		ret = -EOWNERDEAD;
		अगर (unlikely(ctx->sq_data->thपढ़ो == शून्य)) अणु
			जाओ out;
		पूर्ण
		अगर (flags & IORING_ENTER_SQ_WAKEUP)
			wake_up(&ctx->sq_data->रुको);
		अगर (flags & IORING_ENTER_SQ_WAIT) अणु
			ret = io_sqpoll_रुको_sq(ctx);
			अगर (ret)
				जाओ out;
		पूर्ण
		submitted = to_submit;
	पूर्ण अन्यथा अगर (to_submit) अणु
		ret = io_uring_add_task_file(ctx);
		अगर (unlikely(ret))
			जाओ out;
		mutex_lock(&ctx->uring_lock);
		submitted = io_submit_sqes(ctx, to_submit);
		mutex_unlock(&ctx->uring_lock);

		अगर (submitted != to_submit)
			जाओ out;
	पूर्ण
	अगर (flags & IORING_ENTER_GETEVENTS) अणु
		स्थिर sigset_t __user *sig;
		काष्ठा __kernel_बारpec __user *ts;

		ret = io_get_ext_arg(flags, argp, &argsz, &ts, &sig);
		अगर (unlikely(ret))
			जाओ out;

		min_complete = min(min_complete, ctx->cq_entries);

		/*
		 * When SETUP_IOPOLL and SETUP_SQPOLL are both enabled, user
		 * space applications करोn't need to करो io completion events
		 * polling again, they can rely on io_sq_thपढ़ो to करो polling
		 * work, which can reduce cpu usage and uring_lock contention.
		 */
		अगर (ctx->flags & IORING_SETUP_IOPOLL &&
		    !(ctx->flags & IORING_SETUP_SQPOLL)) अणु
			ret = io_iopoll_check(ctx, min_complete);
		पूर्ण अन्यथा अणु
			ret = io_cqring_रुको(ctx, min_complete, sig, argsz, ts);
		पूर्ण
	पूर्ण

out:
	percpu_ref_put(&ctx->refs);
out_fput:
	fdput(f);
	वापस submitted ? submitted : ret;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक io_uring_show_cred(काष्ठा seq_file *m, अचिन्हित पूर्णांक id,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा user_namespace *uns = seq_user_ns(m);
	काष्ठा group_info *gi;
	kernel_cap_t cap;
	अचिन्हित __capi;
	पूर्णांक g;

	seq_म_लिखो(m, "%5d\n", id);
	seq_put_decimal_ull(m, "\tUid:\t", from_kuid_munged(uns, cred->uid));
	seq_put_decimal_ull(m, "\t\t", from_kuid_munged(uns, cred->euid));
	seq_put_decimal_ull(m, "\t\t", from_kuid_munged(uns, cred->suid));
	seq_put_decimal_ull(m, "\t\t", from_kuid_munged(uns, cred->fsuid));
	seq_put_decimal_ull(m, "\n\tGid:\t", from_kgid_munged(uns, cred->gid));
	seq_put_decimal_ull(m, "\t\t", from_kgid_munged(uns, cred->egid));
	seq_put_decimal_ull(m, "\t\t", from_kgid_munged(uns, cred->sgid));
	seq_put_decimal_ull(m, "\t\t", from_kgid_munged(uns, cred->fsgid));
	seq_माला_दो(m, "\n\tGroups:\t");
	gi = cred->group_info;
	क्रम (g = 0; g < gi->ngroups; g++) अणु
		seq_put_decimal_ull(m, g ? " " : "",
					from_kgid_munged(uns, gi->gid[g]));
	पूर्ण
	seq_माला_दो(m, "\n\tCapEff:\t");
	cap = cred->cap_effective;
	CAP_FOR_EACH_U32(__capi)
		seq_put_hex_ll(m, शून्य, cap.cap[CAP_LAST_U32 - __capi], 8);
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल व्योम __io_uring_show_fdinfo(काष्ठा io_ring_ctx *ctx, काष्ठा seq_file *m)
अणु
	काष्ठा io_sq_data *sq = शून्य;
	bool has_lock;
	पूर्णांक i;

	/*
	 * Aव्योम ABBA deadlock between the seq lock and the io_uring mutex,
	 * since fdinfo हाल grअसल it in the opposite direction of normal use
	 * हालs. If we fail to get the lock, we just करोn't iterate any
	 * काष्ठाures that could be going away outside the io_uring mutex.
	 */
	has_lock = mutex_trylock(&ctx->uring_lock);

	अगर (has_lock && (ctx->flags & IORING_SETUP_SQPOLL)) अणु
		sq = ctx->sq_data;
		अगर (!sq->thपढ़ो)
			sq = शून्य;
	पूर्ण

	seq_म_लिखो(m, "SqThread:\t%d\n", sq ? task_pid_nr(sq->thपढ़ो) : -1);
	seq_म_लिखो(m, "SqThreadCpu:\t%d\n", sq ? task_cpu(sq->thपढ़ो) : -1);
	seq_म_लिखो(m, "UserFiles:\t%u\n", ctx->nr_user_files);
	क्रम (i = 0; has_lock && i < ctx->nr_user_files; i++) अणु
		काष्ठा file *f = io_file_from_index(ctx, i);

		अगर (f)
			seq_म_लिखो(m, "%5u: %s\n", i, file_dentry(f)->d_iname);
		अन्यथा
			seq_म_लिखो(m, "%5u: <none>\n", i);
	पूर्ण
	seq_म_लिखो(m, "UserBufs:\t%u\n", ctx->nr_user_bufs);
	क्रम (i = 0; has_lock && i < ctx->nr_user_bufs; i++) अणु
		काष्ठा io_mapped_ubuf *buf = ctx->user_bufs[i];
		अचिन्हित पूर्णांक len = buf->ubuf_end - buf->ubuf;

		seq_म_लिखो(m, "%5u: 0x%llx/%u\n", i, buf->ubuf, len);
	पूर्ण
	अगर (has_lock && !xa_empty(&ctx->personalities)) अणु
		अचिन्हित दीर्घ index;
		स्थिर काष्ठा cred *cred;

		seq_म_लिखो(m, "Personalities:\n");
		xa_क्रम_each(&ctx->personalities, index, cred)
			io_uring_show_cred(m, index, cred);
	पूर्ण
	seq_म_लिखो(m, "PollList:\n");
	spin_lock_irq(&ctx->completion_lock);
	क्रम (i = 0; i < (1U << ctx->cancel_hash_bits); i++) अणु
		काष्ठा hlist_head *list = &ctx->cancel_hash[i];
		काष्ठा io_kiocb *req;

		hlist_क्रम_each_entry(req, list, hash_node)
			seq_म_लिखो(m, "  op=%d, task_works=%d\n", req->opcode,
					req->task->task_works != शून्य);
	पूर्ण
	spin_unlock_irq(&ctx->completion_lock);
	अगर (has_lock)
		mutex_unlock(&ctx->uring_lock);
पूर्ण

अटल व्योम io_uring_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f)
अणु
	काष्ठा io_ring_ctx *ctx = f->निजी_data;

	अगर (percpu_ref_tryget(&ctx->refs)) अणु
		__io_uring_show_fdinfo(ctx, m);
		percpu_ref_put(&ctx->refs);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations io_uring_fops = अणु
	.release	= io_uring_release,
	.mmap		= io_uring_mmap,
#अगर_अघोषित CONFIG_MMU
	.get_unmapped_area = io_uring_nommu_get_unmapped_area,
	.mmap_capabilities = io_uring_nommu_mmap_capabilities,
#पूर्ण_अगर
	.poll		= io_uring_poll,
	.fasync		= io_uring_fasync,
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo	= io_uring_show_fdinfo,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक io_allocate_scq_urings(काष्ठा io_ring_ctx *ctx,
				  काष्ठा io_uring_params *p)
अणु
	काष्ठा io_rings *rings;
	माप_प्रकार size, sq_array_offset;

	/* make sure these are sane, as we alपढ़ोy accounted them */
	ctx->sq_entries = p->sq_entries;
	ctx->cq_entries = p->cq_entries;

	size = rings_size(p->sq_entries, p->cq_entries, &sq_array_offset);
	अगर (size == SIZE_MAX)
		वापस -EOVERFLOW;

	rings = io_mem_alloc(size);
	अगर (!rings)
		वापस -ENOMEM;

	ctx->rings = rings;
	ctx->sq_array = (u32 *)((अक्षर *)rings + sq_array_offset);
	rings->sq_ring_mask = p->sq_entries - 1;
	rings->cq_ring_mask = p->cq_entries - 1;
	rings->sq_ring_entries = p->sq_entries;
	rings->cq_ring_entries = p->cq_entries;
	ctx->sq_mask = rings->sq_ring_mask;
	ctx->cq_mask = rings->cq_ring_mask;

	size = array_size(माप(काष्ठा io_uring_sqe), p->sq_entries);
	अगर (size == SIZE_MAX) अणु
		io_mem_मुक्त(ctx->rings);
		ctx->rings = शून्य;
		वापस -EOVERFLOW;
	पूर्ण

	ctx->sq_sqes = io_mem_alloc(size);
	अगर (!ctx->sq_sqes) अणु
		io_mem_मुक्त(ctx->rings);
		ctx->rings = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक io_uring_install_fd(काष्ठा io_ring_ctx *ctx, काष्ठा file *file)
अणु
	पूर्णांक ret, fd;

	fd = get_unused_fd_flags(O_RDWR | O_CLOEXEC);
	अगर (fd < 0)
		वापस fd;

	ret = io_uring_add_task_file(ctx);
	अगर (ret) अणु
		put_unused_fd(fd);
		वापस ret;
	पूर्ण
	fd_install(fd, file);
	वापस fd;
पूर्ण

/*
 * Allocate an anonymous fd, this is what स्थिरitutes the application
 * visible backing of an io_uring instance. The application mmaps this
 * fd to gain access to the SQ/CQ ring details. If UNIX sockets are enabled,
 * we have to tie this fd to a socket क्रम file garbage collection purposes.
 */
अटल काष्ठा file *io_uring_get_file(काष्ठा io_ring_ctx *ctx)
अणु
	काष्ठा file *file;
#अगर defined(CONFIG_UNIX)
	पूर्णांक ret;

	ret = sock_create_kern(&init_net, PF_UNIX, SOCK_RAW, IPPROTO_IP,
				&ctx->ring_sock);
	अगर (ret)
		वापस ERR_PTR(ret);
#पूर्ण_अगर

	file = anon_inode_getfile("[io_uring]", &io_uring_fops, ctx,
					O_RDWR | O_CLOEXEC);
#अगर defined(CONFIG_UNIX)
	अगर (IS_ERR(file)) अणु
		sock_release(ctx->ring_sock);
		ctx->ring_sock = शून्य;
	पूर्ण अन्यथा अणु
		ctx->ring_sock->file = file;
	पूर्ण
#पूर्ण_अगर
	वापस file;
पूर्ण

अटल पूर्णांक io_uring_create(अचिन्हित entries, काष्ठा io_uring_params *p,
			   काष्ठा io_uring_params __user *params)
अणु
	काष्ठा io_ring_ctx *ctx;
	काष्ठा file *file;
	पूर्णांक ret;

	अगर (!entries)
		वापस -EINVAL;
	अगर (entries > IORING_MAX_ENTRIES) अणु
		अगर (!(p->flags & IORING_SETUP_CLAMP))
			वापस -EINVAL;
		entries = IORING_MAX_ENTRIES;
	पूर्ण

	/*
	 * Use twice as many entries क्रम the CQ ring. It's possible क्रम the
	 * application to drive a higher depth than the size of the SQ ring,
	 * since the sqes are only used at submission समय. This allows क्रम
	 * some flexibility in overcommitting a bit. If the application has
	 * set IORING_SETUP_CQSIZE, it will have passed in the desired number
	 * of CQ ring entries manually.
	 */
	p->sq_entries = roundup_घात_of_two(entries);
	अगर (p->flags & IORING_SETUP_CQSIZE) अणु
		/*
		 * If IORING_SETUP_CQSIZE is set, we करो the same roundup
		 * to a घातer-of-two, अगर it isn't alपढ़ोy. We करो NOT impose
		 * any cq vs sq ring sizing.
		 */
		अगर (!p->cq_entries)
			वापस -EINVAL;
		अगर (p->cq_entries > IORING_MAX_CQ_ENTRIES) अणु
			अगर (!(p->flags & IORING_SETUP_CLAMP))
				वापस -EINVAL;
			p->cq_entries = IORING_MAX_CQ_ENTRIES;
		पूर्ण
		p->cq_entries = roundup_घात_of_two(p->cq_entries);
		अगर (p->cq_entries < p->sq_entries)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		p->cq_entries = 2 * p->sq_entries;
	पूर्ण

	ctx = io_ring_ctx_alloc(p);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->compat = in_compat_syscall();
	अगर (!capable(CAP_IPC_LOCK))
		ctx->user = get_uid(current_user());

	/*
	 * This is just grabbed क्रम accounting purposes. When a process निकासs,
	 * the mm is निकासed and dropped beक्रमe the files, hence we need to hang
	 * on to this mm purely क्रम the purposes of being able to unaccount
	 * memory (locked/pinned vm). It's not used क्रम anything अन्यथा.
	 */
	mmgrab(current->mm);
	ctx->mm_account = current->mm;

	ret = io_allocate_scq_urings(ctx, p);
	अगर (ret)
		जाओ err;

	ret = io_sq_offload_create(ctx, p);
	अगर (ret)
		जाओ err;
	/* always set a rsrc node */
	ret = io_rsrc_node_चयन_start(ctx);
	अगर (ret)
		जाओ err;
	io_rsrc_node_चयन(ctx, शून्य);

	स_रखो(&p->sq_off, 0, माप(p->sq_off));
	p->sq_off.head = दुरत्व(काष्ठा io_rings, sq.head);
	p->sq_off.tail = दुरत्व(काष्ठा io_rings, sq.tail);
	p->sq_off.ring_mask = दुरत्व(काष्ठा io_rings, sq_ring_mask);
	p->sq_off.ring_entries = दुरत्व(काष्ठा io_rings, sq_ring_entries);
	p->sq_off.flags = दुरत्व(काष्ठा io_rings, sq_flags);
	p->sq_off.dropped = दुरत्व(काष्ठा io_rings, sq_dropped);
	p->sq_off.array = (अक्षर *)ctx->sq_array - (अक्षर *)ctx->rings;

	स_रखो(&p->cq_off, 0, माप(p->cq_off));
	p->cq_off.head = दुरत्व(काष्ठा io_rings, cq.head);
	p->cq_off.tail = दुरत्व(काष्ठा io_rings, cq.tail);
	p->cq_off.ring_mask = दुरत्व(काष्ठा io_rings, cq_ring_mask);
	p->cq_off.ring_entries = दुरत्व(काष्ठा io_rings, cq_ring_entries);
	p->cq_off.overflow = दुरत्व(काष्ठा io_rings, cq_overflow);
	p->cq_off.cqes = दुरत्व(काष्ठा io_rings, cqes);
	p->cq_off.flags = दुरत्व(काष्ठा io_rings, cq_flags);

	p->features = IORING_FEAT_SINGLE_MMAP | IORING_FEAT_NODROP |
			IORING_FEAT_SUBMIT_STABLE | IORING_FEAT_RW_CUR_POS |
			IORING_FEAT_CUR_PERSONALITY | IORING_FEAT_FAST_POLL |
			IORING_FEAT_POLL_32BITS | IORING_FEAT_SQPOLL_NONFIXED |
			IORING_FEAT_EXT_ARG | IORING_FEAT_NATIVE_WORKERS |
			IORING_FEAT_RSRC_TAGS;

	अगर (copy_to_user(params, p, माप(*p))) अणु
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	file = io_uring_get_file(ctx);
	अगर (IS_ERR(file)) अणु
		ret = PTR_ERR(file);
		जाओ err;
	पूर्ण

	/*
	 * Install ring fd as the very last thing, so we करोn't risk someone
	 * having बंदd it beक्रमe we finish setup
	 */
	ret = io_uring_install_fd(ctx, file);
	अगर (ret < 0) अणु
		/* fput will clean it up */
		fput(file);
		वापस ret;
	पूर्ण

	trace_io_uring_create(ret, ctx, p->sq_entries, p->cq_entries, p->flags);
	वापस ret;
err:
	io_ring_ctx_रुको_and_समाप्त(ctx);
	वापस ret;
पूर्ण

/*
 * Sets up an aio uring context, and वापसs the fd. Applications asks क्रम a
 * ring size, we वापस the actual sq/cq ring sizes (among other things) in the
 * params काष्ठाure passed in.
 */
अटल दीर्घ io_uring_setup(u32 entries, काष्ठा io_uring_params __user *params)
अणु
	काष्ठा io_uring_params p;
	पूर्णांक i;

	अगर (copy_from_user(&p, params, माप(p)))
		वापस -EFAULT;
	क्रम (i = 0; i < ARRAY_SIZE(p.resv); i++) अणु
		अगर (p.resv[i])
			वापस -EINVAL;
	पूर्ण

	अगर (p.flags & ~(IORING_SETUP_IOPOLL | IORING_SETUP_SQPOLL |
			IORING_SETUP_SQ_AFF | IORING_SETUP_CQSIZE |
			IORING_SETUP_CLAMP | IORING_SETUP_ATTACH_WQ |
			IORING_SETUP_R_DISABLED))
		वापस -EINVAL;

	वापस  io_uring_create(entries, &p, params);
पूर्ण

SYSCALL_DEFINE2(io_uring_setup, u32, entries,
		काष्ठा io_uring_params __user *, params)
अणु
	वापस io_uring_setup(entries, params);
पूर्ण

अटल पूर्णांक io_probe(काष्ठा io_ring_ctx *ctx, व्योम __user *arg, अचिन्हित nr_args)
अणु
	काष्ठा io_uring_probe *p;
	माप_प्रकार size;
	पूर्णांक i, ret;

	size = काष्ठा_size(p, ops, nr_args);
	अगर (size == SIZE_MAX)
		वापस -EOVERFLOW;
	p = kzalloc(size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	ret = -EFAULT;
	अगर (copy_from_user(p, arg, size))
		जाओ out;
	ret = -EINVAL;
	अगर (स_प्रथम_inv(p, 0, size))
		जाओ out;

	p->last_op = IORING_OP_LAST - 1;
	अगर (nr_args > IORING_OP_LAST)
		nr_args = IORING_OP_LAST;

	क्रम (i = 0; i < nr_args; i++) अणु
		p->ops[i].op = i;
		अगर (!io_op_defs[i].not_supported)
			p->ops[i].flags = IO_URING_OP_SUPPORTED;
	पूर्ण
	p->ops_len = i;

	ret = 0;
	अगर (copy_to_user(arg, p, size))
		ret = -EFAULT;
out:
	kमुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक io_रेजिस्टर_personality(काष्ठा io_ring_ctx *ctx)
अणु
	स्थिर काष्ठा cred *creds;
	u32 id;
	पूर्णांक ret;

	creds = get_current_cred();

	ret = xa_alloc_cyclic(&ctx->personalities, &id, (व्योम *)creds,
			XA_LIMIT(0, अच_लघु_उच्च), &ctx->pers_next, GFP_KERNEL);
	अगर (!ret)
		वापस id;
	put_cred(creds);
	वापस ret;
पूर्ण

अटल पूर्णांक io_रेजिस्टर_restrictions(काष्ठा io_ring_ctx *ctx, व्योम __user *arg,
				    अचिन्हित पूर्णांक nr_args)
अणु
	काष्ठा io_uring_restriction *res;
	माप_प्रकार size;
	पूर्णांक i, ret;

	/* Restrictions allowed only अगर rings started disabled */
	अगर (!(ctx->flags & IORING_SETUP_R_DISABLED))
		वापस -EBADFD;

	/* We allow only a single restrictions registration */
	अगर (ctx->restrictions.रेजिस्टरed)
		वापस -EBUSY;

	अगर (!arg || nr_args > IORING_MAX_RESTRICTIONS)
		वापस -EINVAL;

	size = array_size(nr_args, माप(*res));
	अगर (size == SIZE_MAX)
		वापस -EOVERFLOW;

	res = memdup_user(arg, size);
	अगर (IS_ERR(res))
		वापस PTR_ERR(res);

	ret = 0;

	क्रम (i = 0; i < nr_args; i++) अणु
		चयन (res[i].opcode) अणु
		हाल IORING_RESTRICTION_REGISTER_OP:
			अगर (res[i].रेजिस्टर_op >= IORING_REGISTER_LAST) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			__set_bit(res[i].रेजिस्टर_op,
				  ctx->restrictions.रेजिस्टर_op);
			अवरोध;
		हाल IORING_RESTRICTION_SQE_OP:
			अगर (res[i].sqe_op >= IORING_OP_LAST) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			__set_bit(res[i].sqe_op, ctx->restrictions.sqe_op);
			अवरोध;
		हाल IORING_RESTRICTION_SQE_FLAGS_ALLOWED:
			ctx->restrictions.sqe_flags_allowed = res[i].sqe_flags;
			अवरोध;
		हाल IORING_RESTRICTION_SQE_FLAGS_REQUIRED:
			ctx->restrictions.sqe_flags_required = res[i].sqe_flags;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	/* Reset all restrictions अगर an error happened */
	अगर (ret != 0)
		स_रखो(&ctx->restrictions, 0, माप(ctx->restrictions));
	अन्यथा
		ctx->restrictions.रेजिस्टरed = true;

	kमुक्त(res);
	वापस ret;
पूर्ण

अटल पूर्णांक io_रेजिस्टर_enable_rings(काष्ठा io_ring_ctx *ctx)
अणु
	अगर (!(ctx->flags & IORING_SETUP_R_DISABLED))
		वापस -EBADFD;

	अगर (ctx->restrictions.रेजिस्टरed)
		ctx->restricted = 1;

	ctx->flags &= ~IORING_SETUP_R_DISABLED;
	अगर (ctx->sq_data && wq_has_sleeper(&ctx->sq_data->रुको))
		wake_up(&ctx->sq_data->रुको);
	वापस 0;
पूर्ण

अटल पूर्णांक __io_रेजिस्टर_rsrc_update(काष्ठा io_ring_ctx *ctx, अचिन्हित type,
				     काष्ठा io_uring_rsrc_update2 *up,
				     अचिन्हित nr_args)
अणु
	__u32 पंचांगp;
	पूर्णांक err;

	अगर (up->resv)
		वापस -EINVAL;
	अगर (check_add_overflow(up->offset, nr_args, &पंचांगp))
		वापस -EOVERFLOW;
	err = io_rsrc_node_चयन_start(ctx);
	अगर (err)
		वापस err;

	चयन (type) अणु
	हाल IORING_RSRC_खाता:
		वापस __io_sqe_files_update(ctx, up, nr_args);
	हाल IORING_RSRC_BUFFER:
		वापस __io_sqe_buffers_update(ctx, up, nr_args);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक io_रेजिस्टर_files_update(काष्ठा io_ring_ctx *ctx, व्योम __user *arg,
				    अचिन्हित nr_args)
अणु
	काष्ठा io_uring_rsrc_update2 up;

	अगर (!nr_args)
		वापस -EINVAL;
	स_रखो(&up, 0, माप(up));
	अगर (copy_from_user(&up, arg, माप(काष्ठा io_uring_rsrc_update)))
		वापस -EFAULT;
	वापस __io_रेजिस्टर_rsrc_update(ctx, IORING_RSRC_खाता, &up, nr_args);
पूर्ण

अटल पूर्णांक io_रेजिस्टर_rsrc_update(काष्ठा io_ring_ctx *ctx, व्योम __user *arg,
				   अचिन्हित size, अचिन्हित type)
अणु
	काष्ठा io_uring_rsrc_update2 up;

	अगर (size != माप(up))
		वापस -EINVAL;
	अगर (copy_from_user(&up, arg, माप(up)))
		वापस -EFAULT;
	अगर (!up.nr || up.resv)
		वापस -EINVAL;
	वापस __io_रेजिस्टर_rsrc_update(ctx, type, &up, up.nr);
पूर्ण

अटल पूर्णांक io_रेजिस्टर_rsrc(काष्ठा io_ring_ctx *ctx, व्योम __user *arg,
			    अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक type)
अणु
	काष्ठा io_uring_rsrc_रेजिस्टर rr;

	/* keep it extendible */
	अगर (size != माप(rr))
		वापस -EINVAL;

	स_रखो(&rr, 0, माप(rr));
	अगर (copy_from_user(&rr, arg, size))
		वापस -EFAULT;
	अगर (!rr.nr || rr.resv || rr.resv2)
		वापस -EINVAL;

	चयन (type) अणु
	हाल IORING_RSRC_खाता:
		वापस io_sqe_files_रेजिस्टर(ctx, u64_to_user_ptr(rr.data),
					     rr.nr, u64_to_user_ptr(rr.tags));
	हाल IORING_RSRC_BUFFER:
		वापस io_sqe_buffers_रेजिस्टर(ctx, u64_to_user_ptr(rr.data),
					       rr.nr, u64_to_user_ptr(rr.tags));
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल bool io_रेजिस्टर_op_must_quiesce(पूर्णांक op)
अणु
	चयन (op) अणु
	हाल IORING_REGISTER_BUFFERS:
	हाल IORING_UNREGISTER_BUFFERS:
	हाल IORING_REGISTER_खाताS:
	हाल IORING_UNREGISTER_खाताS:
	हाल IORING_REGISTER_खाताS_UPDATE:
	हाल IORING_REGISTER_PROBE:
	हाल IORING_REGISTER_PERSONALITY:
	हाल IORING_UNREGISTER_PERSONALITY:
	हाल IORING_REGISTER_खाताS2:
	हाल IORING_REGISTER_खाताS_UPDATE2:
	हाल IORING_REGISTER_BUFFERS2:
	हाल IORING_REGISTER_BUFFERS_UPDATE:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक __io_uring_रेजिस्टर(काष्ठा io_ring_ctx *ctx, अचिन्हित opcode,
			       व्योम __user *arg, अचिन्हित nr_args)
	__releases(ctx->uring_lock)
	__acquires(ctx->uring_lock)
अणु
	पूर्णांक ret;

	/*
	 * We're inside the ring mutex, अगर the ref is alपढ़ोy dying, then
	 * someone अन्यथा समाप्तed the ctx or is alपढ़ोy going through
	 * io_uring_रेजिस्टर().
	 */
	अगर (percpu_ref_is_dying(&ctx->refs))
		वापस -ENXIO;

	अगर (ctx->restricted) अणु
		अगर (opcode >= IORING_REGISTER_LAST)
			वापस -EINVAL;
		opcode = array_index_nospec(opcode, IORING_REGISTER_LAST);
		अगर (!test_bit(opcode, ctx->restrictions.रेजिस्टर_op))
			वापस -EACCES;
	पूर्ण

	अगर (io_रेजिस्टर_op_must_quiesce(opcode)) अणु
		percpu_ref_समाप्त(&ctx->refs);

		/*
		 * Drop uring mutex beक्रमe रुकोing क्रम references to निकास. If
		 * another thपढ़ो is currently inside io_uring_enter() it might
		 * need to grab the uring_lock to make progress. If we hold it
		 * here across the drain रुको, then we can deadlock. It's safe
		 * to drop the mutex here, since no new references will come in
		 * after we've समाप्तed the percpu ref.
		 */
		mutex_unlock(&ctx->uring_lock);
		करो अणु
			ret = रुको_क्रम_completion_पूर्णांकerruptible(&ctx->ref_comp);
			अगर (!ret)
				अवरोध;
			ret = io_run_task_work_sig();
			अगर (ret < 0)
				अवरोध;
		पूर्ण जबतक (1);
		mutex_lock(&ctx->uring_lock);

		अगर (ret) अणु
			io_refs_resurrect(&ctx->refs, &ctx->ref_comp);
			वापस ret;
		पूर्ण
	पूर्ण

	चयन (opcode) अणु
	हाल IORING_REGISTER_BUFFERS:
		ret = io_sqe_buffers_रेजिस्टर(ctx, arg, nr_args, शून्य);
		अवरोध;
	हाल IORING_UNREGISTER_BUFFERS:
		ret = -EINVAL;
		अगर (arg || nr_args)
			अवरोध;
		ret = io_sqe_buffers_unरेजिस्टर(ctx);
		अवरोध;
	हाल IORING_REGISTER_खाताS:
		ret = io_sqe_files_रेजिस्टर(ctx, arg, nr_args, शून्य);
		अवरोध;
	हाल IORING_UNREGISTER_खाताS:
		ret = -EINVAL;
		अगर (arg || nr_args)
			अवरोध;
		ret = io_sqe_files_unरेजिस्टर(ctx);
		अवरोध;
	हाल IORING_REGISTER_खाताS_UPDATE:
		ret = io_रेजिस्टर_files_update(ctx, arg, nr_args);
		अवरोध;
	हाल IORING_REGISTER_EVENTFD:
	हाल IORING_REGISTER_EVENTFD_ASYNC:
		ret = -EINVAL;
		अगर (nr_args != 1)
			अवरोध;
		ret = io_eventfd_रेजिस्टर(ctx, arg);
		अगर (ret)
			अवरोध;
		अगर (opcode == IORING_REGISTER_EVENTFD_ASYNC)
			ctx->eventfd_async = 1;
		अन्यथा
			ctx->eventfd_async = 0;
		अवरोध;
	हाल IORING_UNREGISTER_EVENTFD:
		ret = -EINVAL;
		अगर (arg || nr_args)
			अवरोध;
		ret = io_eventfd_unरेजिस्टर(ctx);
		अवरोध;
	हाल IORING_REGISTER_PROBE:
		ret = -EINVAL;
		अगर (!arg || nr_args > 256)
			अवरोध;
		ret = io_probe(ctx, arg, nr_args);
		अवरोध;
	हाल IORING_REGISTER_PERSONALITY:
		ret = -EINVAL;
		अगर (arg || nr_args)
			अवरोध;
		ret = io_रेजिस्टर_personality(ctx);
		अवरोध;
	हाल IORING_UNREGISTER_PERSONALITY:
		ret = -EINVAL;
		अगर (arg)
			अवरोध;
		ret = io_unरेजिस्टर_personality(ctx, nr_args);
		अवरोध;
	हाल IORING_REGISTER_ENABLE_RINGS:
		ret = -EINVAL;
		अगर (arg || nr_args)
			अवरोध;
		ret = io_रेजिस्टर_enable_rings(ctx);
		अवरोध;
	हाल IORING_REGISTER_RESTRICTIONS:
		ret = io_रेजिस्टर_restrictions(ctx, arg, nr_args);
		अवरोध;
	हाल IORING_REGISTER_खाताS2:
		ret = io_रेजिस्टर_rsrc(ctx, arg, nr_args, IORING_RSRC_खाता);
		अवरोध;
	हाल IORING_REGISTER_खाताS_UPDATE2:
		ret = io_रेजिस्टर_rsrc_update(ctx, arg, nr_args,
					      IORING_RSRC_खाता);
		अवरोध;
	हाल IORING_REGISTER_BUFFERS2:
		ret = io_रेजिस्टर_rsrc(ctx, arg, nr_args, IORING_RSRC_BUFFER);
		अवरोध;
	हाल IORING_REGISTER_BUFFERS_UPDATE:
		ret = io_रेजिस्टर_rsrc_update(ctx, arg, nr_args,
					      IORING_RSRC_BUFFER);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (io_रेजिस्टर_op_must_quiesce(opcode)) अणु
		/* bring the ctx back to lअगरe */
		percpu_ref_reinit(&ctx->refs);
		reinit_completion(&ctx->ref_comp);
	पूर्ण
	वापस ret;
पूर्ण

SYSCALL_DEFINE4(io_uring_रेजिस्टर, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, opcode,
		व्योम __user *, arg, अचिन्हित पूर्णांक, nr_args)
अणु
	काष्ठा io_ring_ctx *ctx;
	दीर्घ ret = -EBADF;
	काष्ठा fd f;

	f = fdget(fd);
	अगर (!f.file)
		वापस -EBADF;

	ret = -EOPNOTSUPP;
	अगर (f.file->f_op != &io_uring_fops)
		जाओ out_fput;

	ctx = f.file->निजी_data;

	io_run_task_work();

	mutex_lock(&ctx->uring_lock);
	ret = __io_uring_रेजिस्टर(ctx, opcode, arg, nr_args);
	mutex_unlock(&ctx->uring_lock);
	trace_io_uring_रेजिस्टर(ctx, opcode, ctx->nr_user_files, ctx->nr_user_bufs,
							ctx->cq_ev_fd != शून्य, ret);
out_fput:
	fdput(f);
	वापस ret;
पूर्ण

अटल पूर्णांक __init io_uring_init(व्योम)
अणु
#घोषणा __BUILD_BUG_VERIFY_ELEMENT(stype, eoffset, etype, ename) करो अणु \
	BUILD_BUG_ON(दुरत्व(stype, ename) != eoffset); \
	BUILD_BUG_ON(माप(etype) != माप_field(stype, ename)); \
पूर्ण जबतक (0)

#घोषणा BUILD_BUG_SQE_ELEM(eoffset, etype, ename) \
	__BUILD_BUG_VERIFY_ELEMENT(काष्ठा io_uring_sqe, eoffset, etype, ename)
	BUILD_BUG_ON(माप(काष्ठा io_uring_sqe) != 64);
	BUILD_BUG_SQE_ELEM(0,  __u8,   opcode);
	BUILD_BUG_SQE_ELEM(1,  __u8,   flags);
	BUILD_BUG_SQE_ELEM(2,  __u16,  ioprio);
	BUILD_BUG_SQE_ELEM(4,  __s32,  fd);
	BUILD_BUG_SQE_ELEM(8,  __u64,  off);
	BUILD_BUG_SQE_ELEM(8,  __u64,  addr2);
	BUILD_BUG_SQE_ELEM(16, __u64,  addr);
	BUILD_BUG_SQE_ELEM(16, __u64,  splice_off_in);
	BUILD_BUG_SQE_ELEM(24, __u32,  len);
	BUILD_BUG_SQE_ELEM(28,     __kernel_rwf_t, rw_flags);
	BUILD_BUG_SQE_ELEM(28, /* compat */   पूर्णांक, rw_flags);
	BUILD_BUG_SQE_ELEM(28, /* compat */ __u32, rw_flags);
	BUILD_BUG_SQE_ELEM(28, __u32,  fsync_flags);
	BUILD_BUG_SQE_ELEM(28, /* compat */ __u16,  poll_events);
	BUILD_BUG_SQE_ELEM(28, __u32,  poll32_events);
	BUILD_BUG_SQE_ELEM(28, __u32,  sync_range_flags);
	BUILD_BUG_SQE_ELEM(28, __u32,  msg_flags);
	BUILD_BUG_SQE_ELEM(28, __u32,  समयout_flags);
	BUILD_BUG_SQE_ELEM(28, __u32,  accept_flags);
	BUILD_BUG_SQE_ELEM(28, __u32,  cancel_flags);
	BUILD_BUG_SQE_ELEM(28, __u32,  खोलो_flags);
	BUILD_BUG_SQE_ELEM(28, __u32,  statx_flags);
	BUILD_BUG_SQE_ELEM(28, __u32,  fadvise_advice);
	BUILD_BUG_SQE_ELEM(28, __u32,  splice_flags);
	BUILD_BUG_SQE_ELEM(32, __u64,  user_data);
	BUILD_BUG_SQE_ELEM(40, __u16,  buf_index);
	BUILD_BUG_SQE_ELEM(42, __u16,  personality);
	BUILD_BUG_SQE_ELEM(44, __s32,  splice_fd_in);

	BUILD_BUG_ON(माप(काष्ठा io_uring_files_update) !=
		     माप(काष्ठा io_uring_rsrc_update));
	BUILD_BUG_ON(माप(काष्ठा io_uring_rsrc_update) >
		     माप(काष्ठा io_uring_rsrc_update2));
	/* should fit पूर्णांकo one byte */
	BUILD_BUG_ON(SQE_VALID_FLAGS >= (1 << 8));

	BUILD_BUG_ON(ARRAY_SIZE(io_op_defs) != IORING_OP_LAST);
	BUILD_BUG_ON(__REQ_F_LAST_BIT >= 8 * माप(पूर्णांक));
	req_cachep = KMEM_CACHE(io_kiocb, SLAB_HWCACHE_ALIGN | SLAB_PANIC |
				SLAB_ACCOUNT);
	वापस 0;
पूर्ण;
__initcall(io_uring_init);
