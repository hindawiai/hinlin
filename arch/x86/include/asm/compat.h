<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_COMPAT_H
#घोषणा _ASM_X86_COMPAT_H

/*
 * Architecture specअगरic compatibility types
 */
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/user32.h>
#समावेश <यंत्र/unistd.h>

#समावेश <यंत्र-generic/compat.h>

#घोषणा COMPAT_USER_HZ		100
#घोषणा COMPAT_UTS_MACHINE	"i686\0\0"

प्रकार u16		__compat_uid_t;
प्रकार u16		__compat_gid_t;
प्रकार u32		__compat_uid32_t;
प्रकार u32		__compat_gid32_t;
प्रकार u16		compat_mode_t;
प्रकार u16		compat_dev_t;
प्रकार u16		compat_nlink_t;
प्रकार u16		compat_ipc_pid_t;
प्रकार u32		compat_caddr_t;
प्रकार __kernel_fsid_t	compat_fsid_t;

काष्ठा compat_stat अणु
	compat_dev_t	st_dev;
	u16		__pad1;
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nlink_t	st_nlink;
	__compat_uid_t	st_uid;
	__compat_gid_t	st_gid;
	compat_dev_t	st_rdev;
	u16		__pad2;
	u32		st_size;
	u32		st_blksize;
	u32		st_blocks;
	u32		st_aसमय;
	u32		st_aसमय_nsec;
	u32		st_mसमय;
	u32		st_mसमय_nsec;
	u32		st_स_समय;
	u32		st_स_समय_nsec;
	u32		__unused4;
	u32		__unused5;
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

/*
 * IA32 uses 4 byte alignment क्रम 64 bit quantities,
 * so we need to pack this काष्ठाure.
 */
काष्ठा compat_flock64 अणु
	लघु		l_type;
	लघु		l_whence;
	compat_loff_t	l_start;
	compat_loff_t	l_len;
	compat_pid_t	l_pid;
पूर्ण __attribute__((packed));

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

प्रकार u32		compat_old_sigset_t;	/* at least 32 bits */

#घोषणा _COMPAT_NSIG		64
#घोषणा _COMPAT_NSIG_BPW	32

प्रकार u32               compat_sigset_word;

#घोषणा COMPAT_OFF_T_MAX	0x7fffffff

काष्ठा compat_ipc64_perm अणु
	compat_key_t key;
	__compat_uid32_t uid;
	__compat_gid32_t gid;
	__compat_uid32_t cuid;
	__compat_gid32_t cgid;
	अचिन्हित लघु mode;
	अचिन्हित लघु __pad1;
	अचिन्हित लघु seq;
	अचिन्हित लघु __pad2;
	compat_uदीर्घ_t unused1;
	compat_uदीर्घ_t unused2;
पूर्ण;

काष्ठा compat_semid64_ds अणु
	काष्ठा compat_ipc64_perm sem_perm;
	compat_uदीर्घ_t sem_oसमय;
	compat_uदीर्घ_t sem_oसमय_high;
	compat_uदीर्घ_t sem_स_समय;
	compat_uदीर्घ_t sem_स_समय_high;
	compat_uदीर्घ_t sem_nsems;
	compat_uदीर्घ_t __unused3;
	compat_uदीर्घ_t __unused4;
पूर्ण;

काष्ठा compat_msqid64_ds अणु
	काष्ठा compat_ipc64_perm msg_perm;
	compat_uदीर्घ_t msg_sसमय;
	compat_uदीर्घ_t msg_sसमय_high;
	compat_uदीर्घ_t msg_rसमय;
	compat_uदीर्घ_t msg_rसमय_high;
	compat_uदीर्घ_t msg_स_समय;
	compat_uदीर्घ_t msg_स_समय_high;
	compat_uदीर्घ_t msg_cbytes;
	compat_uदीर्घ_t msg_qnum;
	compat_uदीर्घ_t msg_qbytes;
	compat_pid_t   msg_lspid;
	compat_pid_t   msg_lrpid;
	compat_uदीर्घ_t __unused4;
	compat_uदीर्घ_t __unused5;
पूर्ण;

काष्ठा compat_shmid64_ds अणु
	काष्ठा compat_ipc64_perm shm_perm;
	compat_माप_प्रकार  shm_segsz;
	compat_uदीर्घ_t shm_aसमय;
	compat_uदीर्घ_t shm_aसमय_high;
	compat_uदीर्घ_t shm_dसमय;
	compat_uदीर्घ_t shm_dसमय_high;
	compat_uदीर्घ_t shm_स_समय;
	compat_uदीर्घ_t shm_स_समय_high;
	compat_pid_t   shm_cpid;
	compat_pid_t   shm_lpid;
	compat_uदीर्घ_t shm_nattch;
	compat_uदीर्घ_t __unused4;
	compat_uदीर्घ_t __unused5;
पूर्ण;

#अगर_घोषित CONFIG_X86_X32_ABI
#घोषणा COMPAT_USE_64BIT_TIME \
	(!!(task_pt_regs(current)->orig_ax & __X32_SYSCALL_BIT))
#पूर्ण_अगर

अटल अंतरभूत व्योम __user *arch_compat_alloc_user_space(दीर्घ len)
अणु
	compat_uptr_t sp = task_pt_regs(current)->sp;

	/*
	 * -128 क्रम the x32 ABI redzone.  For IA32, it is not strictly
	 * necessary, but not harmful.
	 */
	sp -= 128;

	वापस (व्योम __user *)round_करोwn(sp - len, 16);
पूर्ण

अटल अंतरभूत bool in_x32_syscall(व्योम)
अणु
#अगर_घोषित CONFIG_X86_X32_ABI
	अगर (task_pt_regs(current)->orig_ax & __X32_SYSCALL_BIT)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत bool in_32bit_syscall(व्योम)
अणु
	वापस in_ia32_syscall() || in_x32_syscall();
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल अंतरभूत bool in_compat_syscall(व्योम)
अणु
	वापस in_32bit_syscall();
पूर्ण
#घोषणा in_compat_syscall in_compat_syscall	/* override the generic impl */
#घोषणा compat_need_64bit_alignment_fixup in_ia32_syscall
#पूर्ण_अगर

काष्ठा compat_siginfo;

#अगर_घोषित CONFIG_X86_X32_ABI
पूर्णांक copy_siginfo_to_user32(काष्ठा compat_siginfo __user *to,
		स्थिर kernel_siginfo_t *from);
#घोषणा copy_siginfo_to_user32 copy_siginfo_to_user32
#पूर्ण_अगर /* CONFIG_X86_X32_ABI */

#पूर्ण_अगर /* _ASM_X86_COMPAT_H */
