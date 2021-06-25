<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_COMPAT_H
#घोषणा __ASM_COMPAT_H

#समावेश <यंत्र-generic/compat.h>

#अगर_घोषित CONFIG_COMPAT

/*
 * Architecture specअगरic compatibility types
 */
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>

#घोषणा COMPAT_USER_HZ		100
#अगर_घोषित __AARCH64EB__
#घोषणा COMPAT_UTS_MACHINE	"armv8b\0\0"
#अन्यथा
#घोषणा COMPAT_UTS_MACHINE	"armv8l\0\0"
#पूर्ण_अगर

प्रकार u16		__compat_uid_t;
प्रकार u16		__compat_gid_t;
प्रकार u16		__compat_uid16_t;
प्रकार u16		__compat_gid16_t;
प्रकार u32		__compat_uid32_t;
प्रकार u32		__compat_gid32_t;
प्रकार u16		compat_mode_t;
प्रकार u32		compat_dev_t;
प्रकार s32		compat_nlink_t;
प्रकार u16		compat_ipc_pid_t;
प्रकार u32		compat_caddr_t;
प्रकार __kernel_fsid_t	compat_fsid_t;

काष्ठा compat_stat अणु
#अगर_घोषित __AARCH64EB__
	लघु		st_dev;
	लघु		__pad1;
#अन्यथा
	compat_dev_t	st_dev;
#पूर्ण_अगर
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_uलघु_t	st_nlink;
	__compat_uid16_t	st_uid;
	__compat_gid16_t	st_gid;
#अगर_घोषित __AARCH64EB__
	लघु		st_rdev;
	लघु		__pad2;
#अन्यथा
	compat_dev_t	st_rdev;
#पूर्ण_अगर
	compat_off_t	st_size;
	compat_off_t	st_blksize;
	compat_off_t	st_blocks;
	old_समय32_t	st_aसमय;
	compat_uदीर्घ_t	st_aसमय_nsec;
	old_समय32_t	st_mसमय;
	compat_uदीर्घ_t	st_mसमय_nsec;
	old_समय32_t	st_स_समय;
	compat_uदीर्घ_t	st_स_समय_nsec;
	compat_uदीर्घ_t	__unused4[2];
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

#घोषणा compat_user_stack_poपूर्णांकer() (user_stack_poपूर्णांकer(task_pt_regs(current)))
#घोषणा COMPAT_MINSIGSTKSZ	2048

अटल अंतरभूत व्योम __user *arch_compat_alloc_user_space(दीर्घ len)
अणु
	वापस (व्योम __user *)compat_user_stack_poपूर्णांकer() - len;
पूर्ण

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

अटल अंतरभूत पूर्णांक is_compat_task(व्योम)
अणु
	वापस test_thपढ़ो_flag(TIF_32BIT);
पूर्ण

अटल अंतरभूत पूर्णांक is_compat_thपढ़ो(काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	वापस test_ti_thपढ़ो_flag(thपढ़ो, TIF_32BIT);
पूर्ण

#अन्यथा /* !CONFIG_COMPAT */

अटल अंतरभूत पूर्णांक is_compat_thपढ़ो(काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */
#पूर्ण_अगर /* __ASM_COMPAT_H */
