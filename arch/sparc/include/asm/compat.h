<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SPARC64_COMPAT_H
#घोषणा _ASM_SPARC64_COMPAT_H
/*
 * Architecture specअगरic compatibility types
 */
#समावेश <linux/types.h>

#समावेश <यंत्र-generic/compat.h>

#घोषणा COMPAT_USER_HZ		100
#घोषणा COMPAT_UTS_MACHINE	"sparc\0\0"

प्रकार u16		__compat_uid_t;
प्रकार u16		__compat_gid_t;
प्रकार u32		__compat_uid32_t;
प्रकार u32		__compat_gid32_t;
प्रकार u16		compat_mode_t;
प्रकार u16		compat_dev_t;
प्रकार s16		compat_nlink_t;
प्रकार u16		compat_ipc_pid_t;
प्रकार u32		compat_caddr_t;
प्रकार __kernel_fsid_t	compat_fsid_t;

काष्ठा compat_stat अणु
	compat_dev_t	st_dev;
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nlink_t	st_nlink;
	__compat_uid_t	st_uid;
	__compat_gid_t	st_gid;
	compat_dev_t	st_rdev;
	compat_off_t	st_size;
	old_समय32_t	st_aसमय;
	compat_uदीर्घ_t	st_aसमय_nsec;
	old_समय32_t	st_mसमय;
	compat_uदीर्घ_t	st_mसमय_nsec;
	old_समय32_t	st_स_समय;
	compat_uदीर्घ_t	st_स_समय_nsec;
	compat_off_t	st_blksize;
	compat_off_t	st_blocks;
	u32		__unused4[2];
पूर्ण;

काष्ठा compat_stat64 अणु
	अचिन्हित दीर्घ दीर्घ	st_dev;

	अचिन्हित दीर्घ दीर्घ	st_ino;

	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_nlink;

	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;

	अचिन्हित दीर्घ दीर्घ	st_rdev;

	अचिन्हित अक्षर	__pad3[8];

	दीर्घ दीर्घ	st_size;
	अचिन्हित पूर्णांक	st_blksize;

	अचिन्हित अक्षर	__pad4[8];
	अचिन्हित पूर्णांक	st_blocks;

	अचिन्हित पूर्णांक	st_aसमय;
	अचिन्हित पूर्णांक	st_aसमय_nsec;

	अचिन्हित पूर्णांक	st_mसमय;
	अचिन्हित पूर्णांक	st_mसमय_nsec;

	अचिन्हित पूर्णांक	st_स_समय;
	अचिन्हित पूर्णांक	st_स_समय_nsec;

	अचिन्हित पूर्णांक	__unused4;
	अचिन्हित पूर्णांक	__unused5;
पूर्ण;

काष्ठा compat_flock अणु
	लघु		l_type;
	लघु		l_whence;
	compat_off_t	l_start;
	compat_off_t	l_len;
	compat_pid_t	l_pid;
	लघु		__unused;
पूर्ण;

#घोषणा F_GETLK64	12
#घोषणा F_SETLK64	13
#घोषणा F_SETLKW64	14

काष्ठा compat_flock64 अणु
	लघु		l_type;
	लघु		l_whence;
	compat_loff_t	l_start;
	compat_loff_t	l_len;
	compat_pid_t	l_pid;
	लघु		__unused;
पूर्ण;

काष्ठा compat_statfs अणु
	पूर्णांक		f_type;
	पूर्णांक		f_bsize;
	पूर्णांक		f_blocks;
	पूर्णांक		f_bमुक्त;
	पूर्णांक		f_bavail;
	पूर्णांक		f_files;
	पूर्णांक		f_fमुक्त;
	compat_fsid_t	f_fsid;
	पूर्णांक		f_namelen;	/* SunOS ignores this field. */
	पूर्णांक		f_frsize;
	पूर्णांक		f_flags;
	पूर्णांक		f_spare[4];
पूर्ण;

#घोषणा COMPAT_RLIM_अनन्त 0x7fffffff

प्रकार u32		compat_old_sigset_t;

#घोषणा _COMPAT_NSIG		64
#घोषणा _COMPAT_NSIG_BPW	32

प्रकार u32		compat_sigset_word;

#घोषणा COMPAT_OFF_T_MAX	0x7fffffff

#अगर_घोषित CONFIG_COMPAT
अटल अंतरभूत व्योम __user *arch_compat_alloc_user_space(दीर्घ len)
अणु
	काष्ठा pt_regs *regs = current_thपढ़ो_info()->kregs;
	अचिन्हित दीर्घ usp = regs->u_regs[UREG_I6];

	अगर (test_thपढ़ो_64bit_stack(usp))
		usp += STACK_BIAS;

	अगर (test_thपढ़ो_flag(TIF_32BIT))
		usp &= 0xffffffffUL;

	usp -= len;
	usp &= ~0x7UL;

	वापस (व्योम __user *) usp;
पूर्ण
#पूर्ण_अगर

काष्ठा compat_ipc64_perm अणु
	compat_key_t key;
	__compat_uid32_t uid;
	__compat_gid32_t gid;
	__compat_uid32_t cuid;
	__compat_gid32_t cgid;
	अचिन्हित लघु __pad1;
	compat_mode_t mode;
	अचिन्हित लघु __pad2;
	अचिन्हित लघु seq;
	अचिन्हित दीर्घ __unused1;	/* yes they really are 64bit pads */
	अचिन्हित दीर्घ __unused2;
पूर्ण;

काष्ठा compat_semid64_ds अणु
	काष्ठा compat_ipc64_perm sem_perm;
	अचिन्हित पूर्णांक	sem_oसमय_high;
	अचिन्हित पूर्णांक	sem_oसमय;
	अचिन्हित पूर्णांक	sem_स_समय_high;
	अचिन्हित पूर्णांक	sem_स_समय;
	u32		sem_nsems;
	u32		__unused1;
	u32		__unused2;
पूर्ण;

काष्ठा compat_msqid64_ds अणु
	काष्ठा compat_ipc64_perm msg_perm;
	अचिन्हित पूर्णांक	msg_sसमय_high;
	अचिन्हित पूर्णांक	msg_sसमय;
	अचिन्हित पूर्णांक	msg_rसमय_high;
	अचिन्हित पूर्णांक	msg_rसमय;
	अचिन्हित पूर्णांक	msg_स_समय_high;
	अचिन्हित पूर्णांक	msg_स_समय;
	अचिन्हित पूर्णांक	msg_cbytes;
	अचिन्हित पूर्णांक	msg_qnum;
	अचिन्हित पूर्णांक	msg_qbytes;
	compat_pid_t	msg_lspid;
	compat_pid_t	msg_lrpid;
	अचिन्हित पूर्णांक	__unused1;
	अचिन्हित पूर्णांक	__unused2;
पूर्ण;

काष्ठा compat_shmid64_ds अणु
	काष्ठा compat_ipc64_perm shm_perm;
	अचिन्हित पूर्णांक	shm_aसमय_high;
	अचिन्हित पूर्णांक	shm_aसमय;
	अचिन्हित पूर्णांक	shm_dसमय_high;
	अचिन्हित पूर्णांक	shm_dसमय;
	अचिन्हित पूर्णांक	shm_स_समय_high;
	अचिन्हित पूर्णांक	shm_स_समय;
	compat_माप_प्रकार	shm_segsz;
	compat_pid_t	shm_cpid;
	compat_pid_t	shm_lpid;
	अचिन्हित पूर्णांक	shm_nattch;
	अचिन्हित पूर्णांक	__unused1;
	अचिन्हित पूर्णांक	__unused2;
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल अंतरभूत पूर्णांक is_compat_task(व्योम)
अणु
	वापस test_thपढ़ो_flag(TIF_32BIT);
पूर्ण

अटल अंतरभूत bool in_compat_syscall(व्योम)
अणु
	/* Vector 0x110 is LINUX_32BIT_SYSCALL_TRAP */
	वापस pt_regs_trap_type(current_pt_regs()) == 0x110;
पूर्ण
#घोषणा in_compat_syscall in_compat_syscall
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SPARC64_COMPAT_H */
