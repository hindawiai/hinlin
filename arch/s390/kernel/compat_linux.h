<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390X_S390_H
#घोषणा _ASM_S390X_S390_H

#समावेश <linux/compat.h>
#समावेश <linux/socket.h>
#समावेश <linux/syscalls.h>

/* Macro that masks the high order bit of an 32 bit poपूर्णांकer and converts it*/
/*       to a 64 bit poपूर्णांकer */
#घोषणा A(__x) ((अचिन्हित दीर्घ)((__x) & 0x7FFFFFFFUL))
#घोषणा AA(__x)				\
	((अचिन्हित दीर्घ)(__x))

/* Now 32bit compatibility types */
काष्ठा ipc_kludge_32 अणु
        __u32   msgp;                           /* poपूर्णांकer              */
        __s32   msgtyp;
पूर्ण;

/* यंत्र/sigcontext.h */
प्रकार जोड़
अणु
	__u64   d;
	__u32   f; 
पूर्ण freg_t32;

प्रकार काष्ठा
अणु
	अचिन्हित पूर्णांक	fpc;
	अचिन्हित पूर्णांक	pad;
	freg_t32	fprs[__NUM_FPRS];              
पूर्ण _s390_fp_regs32;

प्रकार काष्ठा 
अणु
        __u32   mask;
        __u32	addr;
पूर्ण _psw_t32 __attribute__ ((aligned(8)));

प्रकार काष्ठा
अणु
	_psw_t32	psw;
	__u32		gprs[__NUM_GPRS];
	__u32		acrs[__NUM_ACRS];
पूर्ण _s390_regs_common32;

प्रकार काष्ठा
अणु
	_s390_regs_common32 regs;
	_s390_fp_regs32     fpregs;
पूर्ण _sigregs32;

प्रकार काष्ठा
अणु
	__u32 gprs_high[__NUM_GPRS];
	__u64 vxrs_low[__NUM_VXRS_LOW];
	__vector128 vxrs_high[__NUM_VXRS_HIGH];
	__u8 __reserved[128];
पूर्ण _sigregs_ext32;

#घोषणा _SIGCONTEXT_NSIG32	64
#घोषणा _SIGCONTEXT_NSIG_BPW32	32
#घोषणा __SIGNAL_FRAMESIZE32	96
#घोषणा _SIGMASK_COPY_SIZE32	(माप(u32)*2)

काष्ठा sigcontext32
अणु
	__u32	oldmask[_COMPAT_NSIG_WORDS];
	__u32	sregs;				/* poपूर्णांकer */
पूर्ण;

/* यंत्र/संकेत.स */

/* यंत्र/ucontext.h */
काष्ठा ucontext32 अणु
	__u32			uc_flags;
	__u32			uc_link;	/* poपूर्णांकer */	
	compat_stack_t		uc_stack;
	_sigregs32		uc_mcontext;
	compat_sigset_t		uc_sigmask;
	/* Allow क्रम uc_sigmask growth.  Glibc uses a 1024-bit sigset_t.  */
	अचिन्हित अक्षर		__unused[128 - माप(compat_sigset_t)];
	_sigregs_ext32		uc_mcontext_ext;
पूर्ण;

काष्ठा stat64_emu31;
काष्ठा mmap_arg_काष्ठा_emu31;
काष्ठा fadvise64_64_args;

दीर्घ compat_sys_s390_chown16(स्थिर अक्षर __user *filename, u16 user, u16 group);
दीर्घ compat_sys_s390_lchown16(स्थिर अक्षर __user *filename, u16 user, u16 group);
दीर्घ compat_sys_s390_fchown16(अचिन्हित पूर्णांक fd, u16 user, u16 group);
दीर्घ compat_sys_s390_setregid16(u16 rgid, u16 egid);
दीर्घ compat_sys_s390_setgid16(u16 gid);
दीर्घ compat_sys_s390_setreuid16(u16 ruid, u16 euid);
दीर्घ compat_sys_s390_setuid16(u16 uid);
दीर्घ compat_sys_s390_setresuid16(u16 ruid, u16 euid, u16 suid);
दीर्घ compat_sys_s390_getresuid16(u16 __user *ruid, u16 __user *euid, u16 __user *suid);
दीर्घ compat_sys_s390_setresgid16(u16 rgid, u16 egid, u16 sgid);
दीर्घ compat_sys_s390_getresgid16(u16 __user *rgid, u16 __user *egid, u16 __user *sgid);
दीर्घ compat_sys_s390_setfsuid16(u16 uid);
दीर्घ compat_sys_s390_setfsgid16(u16 gid);
दीर्घ compat_sys_s390_getgroups16(पूर्णांक gidsetsize, u16 __user *grouplist);
दीर्घ compat_sys_s390_setgroups16(पूर्णांक gidsetsize, u16 __user *grouplist);
दीर्घ compat_sys_s390_getuid16(व्योम);
दीर्घ compat_sys_s390_geteuid16(व्योम);
दीर्घ compat_sys_s390_getgid16(व्योम);
दीर्घ compat_sys_s390_getegid16(व्योम);
दीर्घ compat_sys_s390_truncate64(स्थिर अक्षर __user *path, u32 high, u32 low);
दीर्घ compat_sys_s390_ftruncate64(अचिन्हित पूर्णांक fd, u32 high, u32 low);
दीर्घ compat_sys_s390_pपढ़ो64(अचिन्हित पूर्णांक fd, अक्षर __user *ubuf, compat_माप_प्रकार count, u32 high, u32 low);
दीर्घ compat_sys_s390_pग_लिखो64(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *ubuf, compat_माप_प्रकार count, u32 high, u32 low);
दीर्घ compat_sys_s390_पढ़ोahead(पूर्णांक fd, u32 high, u32 low, s32 count);
दीर्घ compat_sys_s390_stat64(स्थिर अक्षर __user *filename, काष्ठा stat64_emu31 __user *statbuf);
दीर्घ compat_sys_s390_lstat64(स्थिर अक्षर __user *filename, काष्ठा stat64_emu31 __user *statbuf);
दीर्घ compat_sys_s390_ख_स्थिति64(अचिन्हित पूर्णांक fd, काष्ठा stat64_emu31 __user *statbuf);
दीर्घ compat_sys_s390_ख_स्थितिat64(अचिन्हित पूर्णांक dfd, स्थिर अक्षर __user *filename, काष्ठा stat64_emu31 __user *statbuf, पूर्णांक flag);
दीर्घ compat_sys_s390_old_mmap(काष्ठा mmap_arg_काष्ठा_emu31 __user *arg);
दीर्घ compat_sys_s390_mmap2(काष्ठा mmap_arg_काष्ठा_emu31 __user *arg);
दीर्घ compat_sys_s390_पढ़ो(अचिन्हित पूर्णांक fd, अक्षर __user * buf, compat_माप_प्रकार count);
दीर्घ compat_sys_s390_ग_लिखो(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user * buf, compat_माप_प्रकार count);
दीर्घ compat_sys_s390_fadvise64(पूर्णांक fd, u32 high, u32 low, compat_माप_प्रकार len, पूर्णांक advise);
दीर्घ compat_sys_s390_fadvise64_64(काष्ठा fadvise64_64_args __user *args);
दीर्घ compat_sys_s390_sync_file_range(पूर्णांक fd, u32 offhigh, u32 offlow, u32 nhigh, u32 nlow, अचिन्हित पूर्णांक flags);
दीर्घ compat_sys_s390_fallocate(पूर्णांक fd, पूर्णांक mode, u32 offhigh, u32 offlow, u32 lenhigh, u32 lenlow);
दीर्घ compat_sys_sigवापस(व्योम);
दीर्घ compat_sys_rt_sigवापस(व्योम);

#पूर्ण_अगर /* _ASM_S390X_S390_H */
