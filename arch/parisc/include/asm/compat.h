<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_COMPAT_H
#घोषणा _ASM_PARISC_COMPAT_H
/*
 * Architecture specअगरic compatibility types
 */
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र-generic/compat.h>

#घोषणा COMPAT_USER_HZ 		100
#घोषणा COMPAT_UTS_MACHINE	"parisc\0\0"

प्रकार u32	__compat_uid_t;
प्रकार u32	__compat_gid_t;
प्रकार u32	__compat_uid32_t;
प्रकार u32	__compat_gid32_t;
प्रकार u16	compat_mode_t;
प्रकार u32	compat_dev_t;
प्रकार u16	compat_nlink_t;
प्रकार u16	compat_ipc_pid_t;
प्रकार u32	compat_caddr_t;

काष्ठा compat_stat अणु
	compat_dev_t		st_dev;	/* dev_t is 32 bits on parisc */
	compat_ino_t		st_ino;	/* 32 bits */
	compat_mode_t		st_mode;	/* 16 bits */
	compat_nlink_t  	st_nlink;	/* 16 bits */
	u16			st_reserved1;	/* old st_uid */
	u16			st_reserved2;	/* old st_gid */
	compat_dev_t		st_rdev;
	compat_off_t		st_size;
	old_समय32_t		st_aसमय;
	u32			st_aसमय_nsec;
	old_समय32_t		st_mसमय;
	u32			st_mसमय_nsec;
	old_समय32_t		st_स_समय;
	u32			st_स_समय_nsec;
	s32			st_blksize;
	s32			st_blocks;
	u32			__unused1;	/* ACL stuff */
	compat_dev_t		__unused2;	/* network */
	compat_ino_t		__unused3;	/* network */
	u32			__unused4;	/* cnodes */
	u16			__unused5;	/* netsite */
	लघु			st_fstype;
	compat_dev_t		st_realdev;
	u16			st_basemode;
	u16			st_spareलघु;
	__compat_uid32_t	st_uid;
	__compat_gid32_t	st_gid;
	u32			st_spare4[3];
पूर्ण;

काष्ठा compat_flock अणु
	लघु			l_type;
	लघु			l_whence;
	compat_off_t		l_start;
	compat_off_t		l_len;
	compat_pid_t		l_pid;
पूर्ण;

काष्ठा compat_flock64 अणु
	लघु			l_type;
	लघु			l_whence;
	compat_loff_t		l_start;
	compat_loff_t		l_len;
	compat_pid_t		l_pid;
पूर्ण;

काष्ठा compat_statfs अणु
	s32		f_type;
	s32		f_bsize;
	s32		f_blocks;
	s32		f_bमुक्त;
	s32		f_bavail;
	s32		f_files;
	s32		f_fमुक्त;
	__kernel_fsid_t	f_fsid;
	s32		f_namelen;
	s32		f_frsize;
	s32		f_flags;
	s32		f_spare[4];
पूर्ण;

काष्ठा compat_sigcontext अणु
	compat_पूर्णांक_t sc_flags;
	compat_पूर्णांक_t sc_gr[32]; /* PSW in sc_gr[0] */
	u64 sc_fr[32];
	compat_पूर्णांक_t sc_iasq[2];
	compat_पूर्णांक_t sc_iaoq[2];
	compat_पूर्णांक_t sc_sar; /* cr11 */
पूर्ण;

#घोषणा COMPAT_RLIM_अनन्त 0xffffffff

प्रकार u32		compat_old_sigset_t;	/* at least 32 bits */

#घोषणा _COMPAT_NSIG		64
#घोषणा _COMPAT_NSIG_BPW	32

प्रकार u32		compat_sigset_word;

#घोषणा COMPAT_OFF_T_MAX	0x7fffffff

काष्ठा compat_ipc64_perm अणु
	compat_key_t key;
	__compat_uid_t uid;
	__compat_gid_t gid;
	__compat_uid_t cuid;
	__compat_gid_t cgid;
	अचिन्हित लघु पूर्णांक __pad1;
	compat_mode_t mode;
	अचिन्हित लघु पूर्णांक __pad2;
	अचिन्हित लघु पूर्णांक seq;
	अचिन्हित पूर्णांक __pad3;
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

/*
 * The type of काष्ठा elf_prstatus.pr_reg in compatible core dumps.
 */
#घोषणा COMPAT_ELF_NGREG 80
प्रकार compat_uदीर्घ_t compat_elf_gregset_t[COMPAT_ELF_NGREG];

अटल __अंतरभूत__ व्योम __user *arch_compat_alloc_user_space(दीर्घ len)
अणु
	काष्ठा pt_regs *regs = &current->thपढ़ो.regs;
	वापस (व्योम __user *)regs->gr[30];
पूर्ण

अटल अंतरभूत पूर्णांक __is_compat_task(काष्ठा task_काष्ठा *t)
अणु
	वापस test_tsk_thपढ़ो_flag(t, TIF_32BIT);
पूर्ण

अटल अंतरभूत पूर्णांक is_compat_task(व्योम)
अणु
	वापस __is_compat_task(current);
पूर्ण

#पूर्ण_अगर /* _ASM_PARISC_COMPAT_H */
