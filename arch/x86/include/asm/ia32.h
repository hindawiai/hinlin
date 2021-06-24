<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IA32_H
#घोषणा _ASM_X86_IA32_H


#अगर_घोषित CONFIG_IA32_EMULATION

#समावेश <linux/compat.h>

/*
 * 32 bit काष्ठाures क्रम IA32 support.
 */

#समावेश <uapi/यंत्र/sigcontext.h>

/* संकेत.स */

काष्ठा ucontext_ia32 अणु
	अचिन्हित पूर्णांक	  uc_flags;
	अचिन्हित पूर्णांक 	  uc_link;
	compat_stack_t	  uc_stack;
	काष्ठा sigcontext_32 uc_mcontext;
	compat_sigset_t	  uc_sigmask;	/* mask last क्रम extensibility */
पूर्ण;

/* This matches काष्ठा stat64 in glibc2.2, hence the असलolutely
 * insane amounts of padding around dev_t's.
 */
काष्ठा stat64 अणु
	अचिन्हित दीर्घ दीर्घ	st_dev;
	अचिन्हित अक्षर		__pad0[4];

#घोषणा STAT64_HAS_BROKEN_ST_INO	1
	अचिन्हित पूर्णांक		__st_ino;

	अचिन्हित पूर्णांक		st_mode;
	अचिन्हित पूर्णांक		st_nlink;

	अचिन्हित पूर्णांक		st_uid;
	अचिन्हित पूर्णांक		st_gid;

	अचिन्हित दीर्घ दीर्घ	st_rdev;
	अचिन्हित अक्षर		__pad3[4];

	दीर्घ दीर्घ		st_size;
	अचिन्हित पूर्णांक		st_blksize;

	दीर्घ दीर्घ		st_blocks;/* Number 512-byte blocks allocated */

	अचिन्हित 		st_aसमय;
	अचिन्हित 		st_aसमय_nsec;
	अचिन्हित 		st_mसमय;
	अचिन्हित 		st_mसमय_nsec;
	अचिन्हित 		st_स_समय;
	अचिन्हित 		st_स_समय_nsec;

	अचिन्हित दीर्घ दीर्घ	st_ino;
पूर्ण __attribute__((packed));

#घोषणा IA32_STACK_TOP IA32_PAGE_OFFSET

#अगर_घोषित __KERNEL__
काष्ठा linux_binprm;
बाह्य पूर्णांक ia32_setup_arg_pages(काष्ठा linux_binprm *bprm,
				अचिन्हित दीर्घ stack_top, पूर्णांक exec_stack);
काष्ठा mm_काष्ठा;
बाह्य व्योम ia32_pick_mmap_layout(काष्ठा mm_काष्ठा *mm);

#पूर्ण_अगर

#पूर्ण_अगर /* !CONFIG_IA32_SUPPORT */

#पूर्ण_अगर /* _ASM_X86_IA32_H */
