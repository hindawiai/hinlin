<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_COMPAT_H
#घोषणा _ASM_COMPAT_H
/*
 * Architecture specअगरic compatibility types
 */
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>

#समावेश <यंत्र-generic/compat.h>

#घोषणा COMPAT_USER_HZ		100
#घोषणा COMPAT_UTS_MACHINE	"mips\0\0\0"

प्रकार s32		__compat_uid_t;
प्रकार s32		__compat_gid_t;
प्रकार __compat_uid_t	__compat_uid32_t;
प्रकार __compat_gid_t	__compat_gid32_t;
प्रकार u32		compat_mode_t;
प्रकार u32		compat_dev_t;
प्रकार u32		compat_nlink_t;
प्रकार s32		compat_ipc_pid_t;
प्रकार s32		compat_caddr_t;
प्रकार काष्ठा अणु
	s32	val[2];
पूर्ण compat_fsid_t;

काष्ठा compat_stat अणु
	compat_dev_t	st_dev;
	s32		st_pad1[3];
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nlink_t	st_nlink;
	__compat_uid_t	st_uid;
	__compat_gid_t	st_gid;
	compat_dev_t	st_rdev;
	s32		st_pad2[2];
	compat_off_t	st_size;
	s32		st_pad3;
	old_समय32_t	st_aसमय;
	s32		st_aसमय_nsec;
	old_समय32_t	st_mसमय;
	s32		st_mसमय_nsec;
	old_समय32_t	st_स_समय;
	s32		st_स_समय_nsec;
	s32		st_blksize;
	s32		st_blocks;
	s32		st_pad4[14];
पूर्ण;

काष्ठा compat_flock अणु
	लघु		l_type;
	लघु		l_whence;
	compat_off_t	l_start;
	compat_off_t	l_len;
	s32		l_sysid;
	compat_pid_t	l_pid;
	s32		pad[4];
पूर्ण;

#घोषणा F_GETLK64	33
#घोषणा F_SETLK64	34
#घोषणा F_SETLKW64	35

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
	पूर्णांक		f_frsize;
	पूर्णांक		f_blocks;
	पूर्णांक		f_bमुक्त;
	पूर्णांक		f_files;
	पूर्णांक		f_fमुक्त;
	पूर्णांक		f_bavail;
	compat_fsid_t	f_fsid;
	पूर्णांक		f_namelen;
	पूर्णांक		f_flags;
	पूर्णांक		f_spare[5];
पूर्ण;

#घोषणा COMPAT_RLIM_अनन्त	0x7fffffffUL

प्रकार u32		compat_old_sigset_t;	/* at least 32 bits */

#घोषणा _COMPAT_NSIG		128		/* Don't ask !$@#% ...	*/
#घोषणा _COMPAT_NSIG_BPW	32

प्रकार u32		compat_sigset_word;

#घोषणा COMPAT_OFF_T_MAX	0x7fffffff

अटल अंतरभूत व्योम __user *arch_compat_alloc_user_space(दीर्घ len)
अणु
	काष्ठा pt_regs *regs = (काष्ठा pt_regs *)
		((अचिन्हित दीर्घ) current_thपढ़ो_info() + THREAD_SIZE - 32) - 1;

	वापस (व्योम __user *) (regs->regs[29] - len);
पूर्ण

काष्ठा compat_ipc64_perm अणु
	compat_key_t key;
	__compat_uid32_t uid;
	__compat_gid32_t gid;
	__compat_uid32_t cuid;
	__compat_gid32_t cgid;
	compat_mode_t mode;
	अचिन्हित लघु seq;
	अचिन्हित लघु __pad2;
	compat_uदीर्घ_t __unused1;
	compat_uदीर्घ_t __unused2;
पूर्ण;

काष्ठा compat_semid64_ds अणु
	काष्ठा compat_ipc64_perm sem_perm;
	compat_uदीर्घ_t	sem_oसमय;
	compat_uदीर्घ_t	sem_स_समय;
	compat_uदीर्घ_t	sem_nsems;
	compat_uदीर्घ_t	sem_oसमय_high;
	compat_uदीर्घ_t	sem_स_समय_high;
पूर्ण;

काष्ठा compat_msqid64_ds अणु
	काष्ठा compat_ipc64_perm msg_perm;
#अगर_अघोषित CONFIG_CPU_LITTLE_ENDIAN
	compat_uदीर्घ_t	msg_sसमय_high;
#पूर्ण_अगर
	compat_uदीर्घ_t	msg_sसमय;
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
	compat_uदीर्घ_t	msg_sसमय_high;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_CPU_LITTLE_ENDIAN
	compat_uदीर्घ_t	msg_rसमय_high;
#पूर्ण_अगर
	compat_uदीर्घ_t	msg_rसमय;
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
	compat_uदीर्घ_t	msg_rसमय_high;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_CPU_LITTLE_ENDIAN
	compat_uदीर्घ_t	msg_स_समय_high;
#पूर्ण_अगर
	compat_uदीर्घ_t	msg_स_समय;
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
	compat_uदीर्घ_t	msg_स_समय_high;
#पूर्ण_अगर
	compat_uदीर्घ_t	msg_cbytes;
	compat_uदीर्घ_t	msg_qnum;
	compat_uदीर्घ_t	msg_qbytes;
	compat_pid_t	msg_lspid;
	compat_pid_t	msg_lrpid;
	compat_uदीर्घ_t	__unused4;
	compat_uदीर्घ_t	__unused5;
पूर्ण;

काष्ठा compat_shmid64_ds अणु
	काष्ठा compat_ipc64_perm shm_perm;
	compat_माप_प्रकार	shm_segsz;
	compat_uदीर्घ_t	shm_aसमय;
	compat_uदीर्घ_t	shm_dसमय;
	compat_uदीर्घ_t	shm_स_समय;
	compat_pid_t	shm_cpid;
	compat_pid_t	shm_lpid;
	compat_uदीर्घ_t	shm_nattch;
	compat_uलघु_t	shm_aसमय_high;
	compat_uलघु_t	shm_dसमय_high;
	compat_uलघु_t	shm_स_समय_high;
	compat_uलघु_t	__unused2;
पूर्ण;

/* MIPS has unusual order of fields in stack_t */
प्रकार काष्ठा compat_sigaltstack अणु
	compat_uptr_t			ss_sp;
	compat_माप_प्रकार			ss_size;
	पूर्णांक				ss_flags;
पूर्ण compat_stack_t;
#घोषणा compat_sigaltstack compat_sigaltstack

अटल अंतरभूत पूर्णांक is_compat_task(व्योम)
अणु
	वापस test_thपढ़ो_flag(TIF_32BIT_ADDR);
पूर्ण

#पूर्ण_अगर /* _ASM_COMPAT_H */
