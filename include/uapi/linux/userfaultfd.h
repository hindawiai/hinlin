<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  include/linux/userfaultfd.h
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *  Copyright (C) 2015  Red Hat, Inc.
 *
 */

#अगर_अघोषित _LINUX_USERFAULTFD_H
#घोषणा _LINUX_USERFAULTFD_H

#समावेश <linux/types.h>

/*
 * If the UFFDIO_API is upgraded someday, the UFFDIO_UNREGISTER and
 * UFFDIO_WAKE ioctls should be defined as _IOW and not as _IOR.  In
 * userfaultfd.h we assumed the kernel was पढ़ोing (instead _IOC_READ
 * means the userland is पढ़ोing).
 */
#घोषणा UFFD_API ((__u64)0xAA)
#घोषणा UFFD_API_REGISTER_MODES (UFFDIO_REGISTER_MODE_MISSING |	\
				 UFFDIO_REGISTER_MODE_WP |	\
				 UFFDIO_REGISTER_MODE_MINOR)
#घोषणा UFFD_API_FEATURES (UFFD_FEATURE_PAGEFAULT_FLAG_WP |	\
			   UFFD_FEATURE_EVENT_FORK |		\
			   UFFD_FEATURE_EVENT_REMAP |		\
			   UFFD_FEATURE_EVENT_REMOVE |		\
			   UFFD_FEATURE_EVENT_UNMAP |		\
			   UFFD_FEATURE_MISSING_HUGETLBFS |	\
			   UFFD_FEATURE_MISSING_SHMEM |		\
			   UFFD_FEATURE_SIGBUS |		\
			   UFFD_FEATURE_THREAD_ID |		\
			   UFFD_FEATURE_MINOR_HUGETLBFS)
#घोषणा UFFD_API_IOCTLS				\
	((__u64)1 << _UFFDIO_REGISTER |		\
	 (__u64)1 << _UFFDIO_UNREGISTER |	\
	 (__u64)1 << _UFFDIO_API)
#घोषणा UFFD_API_RANGE_IOCTLS			\
	((__u64)1 << _UFFDIO_WAKE |		\
	 (__u64)1 << _UFFDIO_COPY |		\
	 (__u64)1 << _UFFDIO_ZEROPAGE |		\
	 (__u64)1 << _UFFDIO_WRITEPROTECT |	\
	 (__u64)1 << _UFFDIO_CONTINUE)
#घोषणा UFFD_API_RANGE_IOCTLS_BASIC		\
	((__u64)1 << _UFFDIO_WAKE |		\
	 (__u64)1 << _UFFDIO_COPY |		\
	 (__u64)1 << _UFFDIO_CONTINUE)

/*
 * Valid ioctl command number range with this API is from 0x00 to
 * 0x3F.  UFFDIO_API is the fixed number, everything अन्यथा can be
 * changed by implementing a dअगरferent UFFD_API. If sticking to the
 * same UFFD_API more ioctl can be added and userland will be aware of
 * which ioctl the running kernel implements through the ioctl command
 * biपंचांगask written by the UFFDIO_API.
 */
#घोषणा _UFFDIO_REGISTER		(0x00)
#घोषणा _UFFDIO_UNREGISTER		(0x01)
#घोषणा _UFFDIO_WAKE			(0x02)
#घोषणा _UFFDIO_COPY			(0x03)
#घोषणा _UFFDIO_ZEROPAGE		(0x04)
#घोषणा _UFFDIO_WRITEPROTECT		(0x06)
#घोषणा _UFFDIO_CONTINUE		(0x07)
#घोषणा _UFFDIO_API			(0x3F)

/* userfaultfd ioctl ids */
#घोषणा UFFDIO 0xAA
#घोषणा UFFDIO_API		_IOWR(UFFDIO, _UFFDIO_API,	\
				      काष्ठा uffdio_api)
#घोषणा UFFDIO_REGISTER		_IOWR(UFFDIO, _UFFDIO_REGISTER, \
				      काष्ठा uffdio_रेजिस्टर)
#घोषणा UFFDIO_UNREGISTER	_IOR(UFFDIO, _UFFDIO_UNREGISTER,	\
				     काष्ठा uffdio_range)
#घोषणा UFFDIO_WAKE		_IOR(UFFDIO, _UFFDIO_WAKE,	\
				     काष्ठा uffdio_range)
#घोषणा UFFDIO_COPY		_IOWR(UFFDIO, _UFFDIO_COPY,	\
				      काष्ठा uffdio_copy)
#घोषणा UFFDIO_ZEROPAGE		_IOWR(UFFDIO, _UFFDIO_ZEROPAGE,	\
				      काष्ठा uffdio_zeropage)
#घोषणा UFFDIO_WRITEPROTECT	_IOWR(UFFDIO, _UFFDIO_WRITEPROTECT, \
				      काष्ठा uffdio_ग_लिखोprotect)
#घोषणा UFFDIO_CONTINUE		_IOR(UFFDIO, _UFFDIO_CONTINUE,	\
				     काष्ठा uffdio_जारी)

/* पढ़ो() काष्ठाure */
काष्ठा uffd_msg अणु
	__u8	event;

	__u8	reserved1;
	__u16	reserved2;
	__u32	reserved3;

	जोड़ अणु
		काष्ठा अणु
			__u64	flags;
			__u64	address;
			जोड़ अणु
				__u32 ptid;
			पूर्ण feat;
		पूर्ण pagefault;

		काष्ठा अणु
			__u32	ufd;
		पूर्ण विभाजन;

		काष्ठा अणु
			__u64	from;
			__u64	to;
			__u64	len;
		पूर्ण remap;

		काष्ठा अणु
			__u64	start;
			__u64	end;
		पूर्ण हटाओ;

		काष्ठा अणु
			/* unused reserved fields */
			__u64	reserved1;
			__u64	reserved2;
			__u64	reserved3;
		पूर्ण reserved;
	पूर्ण arg;
पूर्ण __packed;

/*
 * Start at 0x12 and not at 0 to be more strict against bugs.
 */
#घोषणा UFFD_EVENT_PAGEFAULT	0x12
#घोषणा UFFD_EVENT_FORK		0x13
#घोषणा UFFD_EVENT_REMAP	0x14
#घोषणा UFFD_EVENT_REMOVE	0x15
#घोषणा UFFD_EVENT_UNMAP	0x16

/* flags क्रम UFFD_EVENT_PAGEFAULT */
#घोषणा UFFD_PAGEFAULT_FLAG_WRITE	(1<<0)	/* If this was a ग_लिखो fault */
#घोषणा UFFD_PAGEFAULT_FLAG_WP		(1<<1)	/* If reason is VM_UFFD_WP */
#घोषणा UFFD_PAGEFAULT_FLAG_MINOR	(1<<2)	/* If reason is VM_UFFD_MINOR */

काष्ठा uffdio_api अणु
	/* userland asks क्रम an API number and the features to enable */
	__u64 api;
	/*
	 * Kernel answers below with the all available features क्रम
	 * the API, this notअगरies userland of which events and/or
	 * which flags क्रम each event are enabled in the current
	 * kernel.
	 *
	 * Note: UFFD_EVENT_PAGEFAULT and UFFD_PAGEFAULT_FLAG_WRITE
	 * are to be considered implicitly always enabled in all kernels as
	 * दीर्घ as the uffdio_api.api requested matches UFFD_API.
	 *
	 * UFFD_FEATURE_MISSING_HUGETLBFS means an UFFDIO_REGISTER
	 * with UFFDIO_REGISTER_MODE_MISSING mode will succeed on
	 * hugetlbfs भव memory ranges. Adding or not adding
	 * UFFD_FEATURE_MISSING_HUGETLBFS to uffdio_api.features has
	 * no real functional effect after UFFDIO_API वापसs, but
	 * it's only useful क्रम an initial feature set probe at
	 * UFFDIO_API समय. There are two ways to use it:
	 *
	 * 1) by adding UFFD_FEATURE_MISSING_HUGETLBFS to the
	 *    uffdio_api.features beक्रमe calling UFFDIO_API, an error
	 *    will be वापसed by UFFDIO_API on a kernel without
	 *    hugetlbfs missing support
	 *
	 * 2) the UFFD_FEATURE_MISSING_HUGETLBFS can not be added in
	 *    uffdio_api.features and instead it will be set by the
	 *    kernel in the uffdio_api.features अगर the kernel supports
	 *    it, so userland can later check अगर the feature flag is
	 *    present in uffdio_api.features after UFFDIO_API
	 *    succeeded.
	 *
	 * UFFD_FEATURE_MISSING_SHMEM works the same as
	 * UFFD_FEATURE_MISSING_HUGETLBFS, but it applies to shmem
	 * (i.e. पंचांगpfs and other shmem based APIs).
	 *
	 * UFFD_FEATURE_SIGBUS feature means no page-fault
	 * (UFFD_EVENT_PAGEFAULT) event will be delivered, instead
	 * a SIGBUS संकेत will be sent to the faulting process.
	 *
	 * UFFD_FEATURE_THREAD_ID pid of the page faulted task_काष्ठा will
	 * be वापसed, अगर feature is not requested 0 will be वापसed.
	 *
	 * UFFD_FEATURE_MINOR_HUGETLBFS indicates that minor faults
	 * can be पूर्णांकercepted (via REGISTER_MODE_MINOR) क्रम
	 * hugetlbfs-backed pages.
	 */
#घोषणा UFFD_FEATURE_PAGEFAULT_FLAG_WP		(1<<0)
#घोषणा UFFD_FEATURE_EVENT_FORK			(1<<1)
#घोषणा UFFD_FEATURE_EVENT_REMAP		(1<<2)
#घोषणा UFFD_FEATURE_EVENT_REMOVE		(1<<3)
#घोषणा UFFD_FEATURE_MISSING_HUGETLBFS		(1<<4)
#घोषणा UFFD_FEATURE_MISSING_SHMEM		(1<<5)
#घोषणा UFFD_FEATURE_EVENT_UNMAP		(1<<6)
#घोषणा UFFD_FEATURE_SIGBUS			(1<<7)
#घोषणा UFFD_FEATURE_THREAD_ID			(1<<8)
#घोषणा UFFD_FEATURE_MINOR_HUGETLBFS		(1<<9)
	__u64 features;

	__u64 ioctls;
पूर्ण;

काष्ठा uffdio_range अणु
	__u64 start;
	__u64 len;
पूर्ण;

काष्ठा uffdio_रेजिस्टर अणु
	काष्ठा uffdio_range range;
#घोषणा UFFDIO_REGISTER_MODE_MISSING	((__u64)1<<0)
#घोषणा UFFDIO_REGISTER_MODE_WP		((__u64)1<<1)
#घोषणा UFFDIO_REGISTER_MODE_MINOR	((__u64)1<<2)
	__u64 mode;

	/*
	 * kernel answers which ioctl commands are available क्रम the
	 * range, keep at the end as the last 8 bytes aren't पढ़ो.
	 */
	__u64 ioctls;
पूर्ण;

काष्ठा uffdio_copy अणु
	__u64 dst;
	__u64 src;
	__u64 len;
#घोषणा UFFDIO_COPY_MODE_DONTWAKE		((__u64)1<<0)
	/*
	 * UFFDIO_COPY_MODE_WP will map the page ग_लिखो रक्षित on
	 * the fly.  UFFDIO_COPY_MODE_WP is available only अगर the
	 * ग_लिखो रक्षित ioctl is implemented क्रम the range
	 * according to the uffdio_रेजिस्टर.ioctls.
	 */
#घोषणा UFFDIO_COPY_MODE_WP			((__u64)1<<1)
	__u64 mode;

	/*
	 * "copy" is written by the ioctl and must be at the end: the
	 * copy_from_user will not पढ़ो the last 8 bytes.
	 */
	__s64 copy;
पूर्ण;

काष्ठा uffdio_zeropage अणु
	काष्ठा uffdio_range range;
#घोषणा UFFDIO_ZEROPAGE_MODE_DONTWAKE		((__u64)1<<0)
	__u64 mode;

	/*
	 * "zeropage" is written by the ioctl and must be at the end:
	 * the copy_from_user will not पढ़ो the last 8 bytes.
	 */
	__s64 zeropage;
पूर्ण;

काष्ठा uffdio_ग_लिखोprotect अणु
	काष्ठा uffdio_range range;
/*
 * UFFDIO_WRITEPROTECT_MODE_WP: set the flag to ग_लिखो protect a range,
 * unset the flag to unकरो protection of a range which was previously
 * ग_लिखो रक्षित.
 *
 * UFFDIO_WRITEPROTECT_MODE_DONTWAKE: set the flag to aव्योम waking up
 * any रुको thपढ़ो after the operation succeeds.
 *
 * NOTE: Write protecting a region (WP=1) is unrelated to page faults,
 * thereक्रमe DONTWAKE flag is meaningless with WP=1.  Removing ग_लिखो
 * protection (WP=0) in response to a page fault wakes the faulting
 * task unless DONTWAKE is set.
 */
#घोषणा UFFDIO_WRITEPROTECT_MODE_WP		((__u64)1<<0)
#घोषणा UFFDIO_WRITEPROTECT_MODE_DONTWAKE	((__u64)1<<1)
	__u64 mode;
पूर्ण;

काष्ठा uffdio_जारी अणु
	काष्ठा uffdio_range range;
#घोषणा UFFDIO_CONTINUE_MODE_DONTWAKE		((__u64)1<<0)
	__u64 mode;

	/*
	 * Fields below here are written by the ioctl and must be at the end:
	 * the copy_from_user will not पढ़ो past here.
	 */
	__s64 mapped;
पूर्ण;

/*
 * Flags क्रम the userfaultfd(2) प्रणाली call itself.
 */

/*
 * Create a userfaultfd that can handle page faults only in user mode.
 */
#घोषणा UFFD_USER_MODE_ONLY 1

#पूर्ण_अगर /* _LINUX_USERFAULTFD_H */
