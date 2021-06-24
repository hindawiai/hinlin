<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390X_COMPAT_H
#घोषणा _ASM_S390X_COMPAT_H
/*
 * Architecture specअगरic compatibility types
 */
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र-generic/compat.h>

#घोषणा __TYPE_IS_PTR(t) (!__builtin_types_compatible_p( \
				typeof(0?(__क्रमce t)0:0ULL), u64))

#घोषणा __SC_DELOUSE(t,v) (अणु \
	BUILD_BUG_ON(माप(t) > 4 && !__TYPE_IS_PTR(t)); \
	(__क्रमce t)(__TYPE_IS_PTR(t) ? ((v) & 0x7fffffff) : (v)); \
पूर्ण)

#घोषणा PSW32_MASK_PER		0x40000000UL
#घोषणा PSW32_MASK_DAT		0x04000000UL
#घोषणा PSW32_MASK_IO		0x02000000UL
#घोषणा PSW32_MASK_EXT		0x01000000UL
#घोषणा PSW32_MASK_KEY		0x00F00000UL
#घोषणा PSW32_MASK_BASE		0x00080000UL	/* Always one */
#घोषणा PSW32_MASK_MCHECK	0x00040000UL
#घोषणा PSW32_MASK_WAIT		0x00020000UL
#घोषणा PSW32_MASK_PSTATE	0x00010000UL
#घोषणा PSW32_MASK_ASC		0x0000C000UL
#घोषणा PSW32_MASK_CC		0x00003000UL
#घोषणा PSW32_MASK_PM		0x00000f00UL
#घोषणा PSW32_MASK_RI		0x00000080UL

#घोषणा PSW32_MASK_USER		0x0000FF00UL

#घोषणा PSW32_ADDR_AMODE	0x80000000UL
#घोषणा PSW32_ADDR_INSN		0x7FFFFFFFUL

#घोषणा PSW32_DEFAULT_KEY	(((u32) PAGE_DEFAULT_ACC) << 20)

#घोषणा PSW32_ASC_PRIMARY	0x00000000UL
#घोषणा PSW32_ASC_ACCREG	0x00004000UL
#घोषणा PSW32_ASC_SECONDARY	0x00008000UL
#घोषणा PSW32_ASC_HOME		0x0000C000UL

#घोषणा PSW32_USER_BITS (PSW32_MASK_DAT | PSW32_MASK_IO | PSW32_MASK_EXT | \
			 PSW32_DEFAULT_KEY | PSW32_MASK_BASE | \
			 PSW32_MASK_MCHECK | PSW32_MASK_PSTATE | \
			 PSW32_ASC_PRIMARY)

#घोषणा COMPAT_USER_HZ		100
#घोषणा COMPAT_UTS_MACHINE	"s390\0\0\0\0"

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

प्रकार काष्ठा अणु
	u32 mask;
	u32 addr;
पूर्ण __aligned(8) psw_compat_t;

प्रकार काष्ठा अणु
	psw_compat_t psw;
	u32 gprs[NUM_GPRS];
	u32 acrs[NUM_ACRS];
	u32 orig_gpr2;
पूर्ण s390_compat_regs;

प्रकार काष्ठा अणु
	u32 gprs_high[NUM_GPRS];
पूर्ण s390_compat_regs_high;

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

#घोषणा F_GETLK64       12
#घोषणा F_SETLK64       13
#घोषणा F_SETLKW64      14    

काष्ठा compat_flock64 अणु
	लघु		l_type;
	लघु		l_whence;
	compat_loff_t	l_start;
	compat_loff_t	l_len;
	compat_pid_t	l_pid;
पूर्ण;

काष्ठा compat_statfs अणु
	u32		f_type;
	u32		f_bsize;
	u32		f_blocks;
	u32		f_bमुक्त;
	u32		f_bavail;
	u32		f_files;
	u32		f_fमुक्त;
	compat_fsid_t	f_fsid;
	u32		f_namelen;
	u32		f_frsize;
	u32		f_flags;
	u32		f_spare[4];
पूर्ण;

काष्ठा compat_statfs64 अणु
	u32		f_type;
	u32		f_bsize;
	u64		f_blocks;
	u64		f_bमुक्त;
	u64		f_bavail;
	u64		f_files;
	u64		f_fमुक्त;
	compat_fsid_t	f_fsid;
	u32		f_namelen;
	u32		f_frsize;
	u32		f_flags;
	u32		f_spare[4];
पूर्ण;

#घोषणा COMPAT_RLIM_अनन्त		0xffffffff

प्रकार u32		compat_old_sigset_t;	/* at least 32 bits */

#घोषणा _COMPAT_NSIG		64
#घोषणा _COMPAT_NSIG_BPW	32

प्रकार u32		compat_sigset_word;

#घोषणा COMPAT_OFF_T_MAX	0x7fffffff

/*
 * A poपूर्णांकer passed in from user mode. This should not
 * be used क्रम syscall parameters, just declare them
 * as poपूर्णांकers because the syscall entry code will have
 * appropriately converted them alपढ़ोy.
 */

अटल अंतरभूत व्योम __user *compat_ptr(compat_uptr_t uptr)
अणु
	वापस (व्योम __user *)(अचिन्हित दीर्घ)(uptr & 0x7fffffffUL);
पूर्ण
#घोषणा compat_ptr(uptr) compat_ptr(uptr)

#अगर_घोषित CONFIG_COMPAT

अटल अंतरभूत पूर्णांक is_compat_task(व्योम)
अणु
	वापस test_thपढ़ो_flag(TIF_31BIT);
पूर्ण

अटल अंतरभूत व्योम __user *arch_compat_alloc_user_space(दीर्घ len)
अणु
	अचिन्हित दीर्घ stack;

	stack = KSTK_ESP(current);
	अगर (is_compat_task())
		stack &= 0x7fffffffUL;
	वापस (व्योम __user *) (stack - len);
पूर्ण

#पूर्ण_अगर

काष्ठा compat_ipc64_perm अणु
	compat_key_t key;
	__compat_uid32_t uid;
	__compat_gid32_t gid;
	__compat_uid32_t cuid;
	__compat_gid32_t cgid;
	compat_mode_t mode;
	अचिन्हित लघु __pad1;
	अचिन्हित लघु seq;
	अचिन्हित लघु __pad2;
	अचिन्हित पूर्णांक __unused1;
	अचिन्हित पूर्णांक __unused2;
पूर्ण;

काष्ठा compat_semid64_ds अणु
	काष्ठा compat_ipc64_perm sem_perm;
	compat_uदीर्घ_t sem_oसमय;
	compat_uदीर्घ_t sem_oसमय_high;
	compat_uदीर्घ_t sem_स_समय;
	compat_uदीर्घ_t sem_स_समय_high;
	compat_uदीर्घ_t sem_nsems;
	compat_uदीर्घ_t __unused1;
	compat_uदीर्घ_t __unused2;
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
	compat_uदीर्घ_t __unused1;
	compat_uदीर्घ_t __unused2;
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
	compat_uदीर्घ_t __unused1;
	compat_uदीर्घ_t __unused2;
पूर्ण;
#पूर्ण_अगर /* _ASM_S390X_COMPAT_H */
