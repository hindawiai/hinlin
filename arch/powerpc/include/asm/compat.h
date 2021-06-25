<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_COMPAT_H
#घोषणा _ASM_POWERPC_COMPAT_H
#अगर_घोषित __KERNEL__
/*
 * Architecture specअगरic compatibility types
 */
#समावेश <linux/types.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र-generic/compat.h>

#घोषणा COMPAT_USER_HZ		100
#अगर_घोषित __BIG_ENDIAN__
#घोषणा COMPAT_UTS_MACHINE	"ppc\0\0"
#अन्यथा
#घोषणा COMPAT_UTS_MACHINE	"ppcle\0\0"
#पूर्ण_अगर

प्रकार u32		__compat_uid_t;
प्रकार u32		__compat_gid_t;
प्रकार u32		__compat_uid32_t;
प्रकार u32		__compat_gid32_t;
प्रकार u32		compat_mode_t;
प्रकार u32		compat_dev_t;
प्रकार s16		compat_nlink_t;
प्रकार u16		compat_ipc_pid_t;
प्रकार u32		compat_caddr_t;
प्रकार __kernel_fsid_t	compat_fsid_t;

काष्ठा compat_stat अणु
	compat_dev_t	st_dev;
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nlink_t	st_nlink;
	__compat_uid32_t	st_uid;
	__compat_gid32_t	st_gid;
	compat_dev_t	st_rdev;
	compat_off_t	st_size;
	compat_off_t	st_blksize;
	compat_off_t	st_blocks;
	old_समय32_t	st_aसमय;
	u32		st_aसमय_nsec;
	old_समय32_t	st_mसमय;
	u32		st_mसमय_nsec;
	old_समय32_t	st_स_समय;
	u32		st_स_समय_nsec;
	u32		__unused4[2];
पूर्ण;

काष्ठा compat_flock अणु
	लघु		l_type;
	लघु		l_whence;
	compat_off_t	l_start;
	compat_off_t	l_len;
	compat_pid_t	l_pid;
पूर्ण;

#घोषणा F_GETLK64	12	/*  using 'struct flock64' */
#घोषणा F_SETLK64	13
#घोषणा F_SETLKW64	14

काष्ठा compat_flock64 अणु
	लघु		l_type;
	लघु		l_whence;
	compat_loff_t	l_start;
	compat_loff_t	l_len;
	compat_pid_t	l_pid;
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

#घोषणा COMPAT_RLIM_अनन्त		0xffffffff

प्रकार u32		compat_old_sigset_t;

#घोषणा _COMPAT_NSIG		64
#घोषणा _COMPAT_NSIG_BPW	32

प्रकार u32		compat_sigset_word;

#घोषणा COMPAT_OFF_T_MAX	0x7fffffff

अटल अंतरभूत व्योम __user *arch_compat_alloc_user_space(दीर्घ len)
अणु
	काष्ठा pt_regs *regs = current->thपढ़ो.regs;
	अचिन्हित दीर्घ usp = regs->gpr[1];

	/*
	 * We can't access below the stack poपूर्णांकer in the 32bit ABI and
	 * can access 288 bytes in the 64bit big-endian ABI,
	 * or 512 bytes with the new ELFv2 little-endian ABI.
	 */
	अगर (!is_32bit_task())
		usp -= USER_REDZONE_SIZE;

	वापस (व्योम __user *) (usp - len);
पूर्ण

/*
 * ipc64_perm is actually 32/64bit clean but since the compat layer refers to
 * it we may as well define it.
 */
काष्ठा compat_ipc64_perm अणु
	compat_key_t key;
	__compat_uid_t uid;
	__compat_gid_t gid;
	__compat_uid_t cuid;
	__compat_gid_t cgid;
	compat_mode_t mode;
	अचिन्हित पूर्णांक seq;
	अचिन्हित पूर्णांक __pad2;
	अचिन्हित दीर्घ __unused1;	/* yes they really are 64bit pads */
	अचिन्हित दीर्घ __unused2;
पूर्ण;

काष्ठा compat_semid64_ds अणु
	काष्ठा compat_ipc64_perm sem_perm;
	अचिन्हित पूर्णांक sem_oसमय_high;
	अचिन्हित पूर्णांक sem_oसमय;
	अचिन्हित पूर्णांक sem_स_समय_high;
	अचिन्हित पूर्णांक sem_स_समय;
	compat_uदीर्घ_t sem_nsems;
	compat_uदीर्घ_t __unused3;
	compat_uदीर्घ_t __unused4;
पूर्ण;

काष्ठा compat_msqid64_ds अणु
	काष्ठा compat_ipc64_perm msg_perm;
	अचिन्हित पूर्णांक msg_sसमय_high;
	अचिन्हित पूर्णांक msg_sसमय;
	अचिन्हित पूर्णांक msg_rसमय_high;
	अचिन्हित पूर्णांक msg_rसमय;
	अचिन्हित पूर्णांक msg_स_समय_high;
	अचिन्हित पूर्णांक msg_स_समय;
	compat_uदीर्घ_t msg_cbytes;
	compat_uदीर्घ_t msg_qnum;
	compat_uदीर्घ_t msg_qbytes;
	compat_pid_t msg_lspid;
	compat_pid_t msg_lrpid;
	compat_uदीर्घ_t __unused4;
	compat_uदीर्घ_t __unused5;
पूर्ण;

काष्ठा compat_shmid64_ds अणु
	काष्ठा compat_ipc64_perm shm_perm;
	अचिन्हित पूर्णांक shm_aसमय_high;
	अचिन्हित पूर्णांक shm_aसमय;
	अचिन्हित पूर्णांक shm_dसमय_high;
	अचिन्हित पूर्णांक shm_dसमय;
	अचिन्हित पूर्णांक shm_स_समय_high;
	अचिन्हित पूर्णांक shm_स_समय;
	अचिन्हित पूर्णांक __unused4;
	compat_माप_प्रकार shm_segsz;
	compat_pid_t shm_cpid;
	compat_pid_t shm_lpid;
	compat_uदीर्घ_t shm_nattch;
	compat_uदीर्घ_t __unused5;
	compat_uदीर्घ_t __unused6;
पूर्ण;

अटल अंतरभूत पूर्णांक is_compat_task(व्योम)
अणु
	वापस is_32bit_task();
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_COMPAT_H */
