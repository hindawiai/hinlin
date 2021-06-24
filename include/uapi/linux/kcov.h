<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_KCOV_IOCTLS_H
#घोषणा _LINUX_KCOV_IOCTLS_H

#समावेश <linux/types.h>

/*
 * Argument क्रम KCOV_REMOTE_ENABLE ioctl, see Documentation/dev-tools/kcov.rst
 * and the comment beक्रमe kcov_remote_start() क्रम usage details.
 */
काष्ठा kcov_remote_arg अणु
	__u32		trace_mode;	/* KCOV_TRACE_PC or KCOV_TRACE_CMP */
	__u32		area_size;	/* Length of coverage buffer in words */
	__u32		num_handles;	/* Size of handles array */
	__aligned_u64	common_handle;
	__aligned_u64	handles[0];
पूर्ण;

#घोषणा KCOV_REMOTE_MAX_HANDLES		0x100

#घोषणा KCOV_INIT_TRACE			_IOR('c', 1, अचिन्हित दीर्घ)
#घोषणा KCOV_ENABLE			_IO('c', 100)
#घोषणा KCOV_DISABLE			_IO('c', 101)
#घोषणा KCOV_REMOTE_ENABLE		_IOW('c', 102, काष्ठा kcov_remote_arg)

क्रमागत अणु
	/*
	 * Tracing coverage collection mode.
	 * Covered PCs are collected in a per-task buffer.
	 * In new KCOV version the mode is chosen by calling
	 * ioctl(fd, KCOV_ENABLE, mode). In older versions the mode argument
	 * was supposed to be 0 in such a call. So, क्रम reasons of backward
	 * compatibility, we have chosen the value KCOV_TRACE_PC to be 0.
	 */
	KCOV_TRACE_PC = 0,
	/* Collecting comparison opeअक्रमs mode. */
	KCOV_TRACE_CMP = 1,
पूर्ण;

/*
 * The क्रमmat क्रम the types of collected comparisons.
 *
 * Bit 0 shows whether one of the arguments is a compile-समय स्थिरant.
 * Bits 1 & 2 contain log2 of the argument size, up to 8 bytes.
 */
#घोषणा KCOV_CMP_CONST          (1 << 0)
#घोषणा KCOV_CMP_SIZE(n)        ((n) << 1)
#घोषणा KCOV_CMP_MASK           KCOV_CMP_SIZE(3)

#घोषणा KCOV_SUBSYSTEM_COMMON	(0x00ull << 56)
#घोषणा KCOV_SUBSYSTEM_USB	(0x01ull << 56)

#घोषणा KCOV_SUBSYSTEM_MASK	(0xffull << 56)
#घोषणा KCOV_INSTANCE_MASK	(0xffffffffull)

अटल अंतरभूत __u64 kcov_remote_handle(__u64 subsys, __u64 inst)
अणु
	अगर (subsys & ~KCOV_SUBSYSTEM_MASK || inst & ~KCOV_INSTANCE_MASK)
		वापस 0;
	वापस subsys | inst;
पूर्ण

#पूर्ण_अगर /* _LINUX_KCOV_IOCTLS_H */
