<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_RSEQ_H
#घोषणा _UAPI_LINUX_RSEQ_H

/*
 * linux/rseq.h
 *
 * Restartable sequences प्रणाली call API
 *
 * Copyright (c) 2015-2018 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

क्रमागत rseq_cpu_id_state अणु
	RSEQ_CPU_ID_UNINITIALIZED		= -1,
	RSEQ_CPU_ID_REGISTRATION_FAILED		= -2,
पूर्ण;

क्रमागत rseq_flags अणु
	RSEQ_FLAG_UNREGISTER = (1 << 0),
पूर्ण;

क्रमागत rseq_cs_flags_bit अणु
	RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT_BIT	= 0,
	RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL_BIT	= 1,
	RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE_BIT	= 2,
पूर्ण;

क्रमागत rseq_cs_flags अणु
	RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT	=
		(1U << RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT_BIT),
	RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL	=
		(1U << RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL_BIT),
	RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE	=
		(1U << RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE_BIT),
पूर्ण;

/*
 * काष्ठा rseq_cs is aligned on 4 * 8 bytes to ensure it is always
 * contained within a single cache-line. It is usually declared as
 * link-समय स्थिरant data.
 */
काष्ठा rseq_cs अणु
	/* Version of this काष्ठाure. */
	__u32 version;
	/* क्रमागत rseq_cs_flags */
	__u32 flags;
	__u64 start_ip;
	/* Offset from start_ip. */
	__u64 post_commit_offset;
	__u64 पात_ip;
पूर्ण __attribute__((aligned(4 * माप(__u64))));

/*
 * काष्ठा rseq is aligned on 4 * 8 bytes to ensure it is always
 * contained within a single cache-line.
 *
 * A single काष्ठा rseq per thपढ़ो is allowed.
 */
काष्ठा rseq अणु
	/*
	 * Restartable sequences cpu_id_start field. Updated by the
	 * kernel. Read by user-space with single-copy atomicity
	 * semantics. This field should only be पढ़ो by the thपढ़ो which
	 * रेजिस्टरed this data काष्ठाure. Aligned on 32-bit. Always
	 * contains a value in the range of possible CPUs, although the
	 * value may not be the actual current CPU (e.g. अगर rseq is not
	 * initialized). This CPU number value should always be compared
	 * against the value of the cpu_id field beक्रमe perक्रमming a rseq
	 * commit or वापसing a value पढ़ो from a data काष्ठाure indexed
	 * using the cpu_id_start value.
	 */
	__u32 cpu_id_start;
	/*
	 * Restartable sequences cpu_id field. Updated by the kernel.
	 * Read by user-space with single-copy atomicity semantics. This
	 * field should only be पढ़ो by the thपढ़ो which रेजिस्टरed this
	 * data काष्ठाure. Aligned on 32-bit. Values
	 * RSEQ_CPU_ID_UNINITIALIZED and RSEQ_CPU_ID_REGISTRATION_FAILED
	 * have a special semantic: the क्रमmer means "rseq uninitialized",
	 * and latter means "rseq initialization failed". This value is
	 * meant to be पढ़ो within rseq critical sections and compared
	 * with the cpu_id_start value previously पढ़ो, beक्रमe perक्रमming
	 * the commit inकाष्ठाion, or पढ़ो and compared with the
	 * cpu_id_start value beक्रमe वापसing a value loaded from a data
	 * काष्ठाure indexed using the cpu_id_start value.
	 */
	__u32 cpu_id;
	/*
	 * Restartable sequences rseq_cs field.
	 *
	 * Contains शून्य when no critical section is active क्रम the current
	 * thपढ़ो, or holds a poपूर्णांकer to the currently active काष्ठा rseq_cs.
	 *
	 * Updated by user-space, which sets the address of the currently
	 * active rseq_cs at the beginning of assembly inकाष्ठाion sequence
	 * block, and set to शून्य by the kernel when it restarts an assembly
	 * inकाष्ठाion sequence block, as well as when the kernel detects that
	 * it is preempting or delivering a संकेत outside of the range
	 * targeted by the rseq_cs. Also needs to be set to शून्य by user-space
	 * beक्रमe reclaiming memory that contains the targeted काष्ठा rseq_cs.
	 *
	 * Read and set by the kernel. Set by user-space with single-copy
	 * atomicity semantics. This field should only be updated by the
	 * thपढ़ो which रेजिस्टरed this data काष्ठाure. Aligned on 64-bit.
	 */
	जोड़ अणु
		__u64 ptr64;
#अगर_घोषित __LP64__
		__u64 ptr;
#अन्यथा
		काष्ठा अणु
#अगर (defined(__BYTE_ORDER) && (__BYTE_ORDER == __BIG_ENDIAN)) || defined(__BIG_ENDIAN)
			__u32 padding;		/* Initialized to zero. */
			__u32 ptr32;
#अन्यथा /* LITTLE */
			__u32 ptr32;
			__u32 padding;		/* Initialized to zero. */
#पूर्ण_अगर /* ENDIAN */
		पूर्ण ptr;
#पूर्ण_अगर
	पूर्ण rseq_cs;

	/*
	 * Restartable sequences flags field.
	 *
	 * This field should only be updated by the thपढ़ो which
	 * रेजिस्टरed this data काष्ठाure. Read by the kernel.
	 * Mainly used क्रम single-stepping through rseq critical sections
	 * with debuggers.
	 *
	 * - RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT
	 *     Inhibit inकाष्ठाion sequence block restart on preemption
	 *     क्रम this thपढ़ो.
	 * - RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL
	 *     Inhibit inकाष्ठाion sequence block restart on संकेत
	 *     delivery क्रम this thपढ़ो.
	 * - RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE
	 *     Inhibit inकाष्ठाion sequence block restart on migration क्रम
	 *     this thपढ़ो.
	 */
	__u32 flags;
पूर्ण __attribute__((aligned(4 * माप(__u64))));

#पूर्ण_अगर /* _UAPI_LINUX_RSEQ_H */
