<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BINFMTS_H
#घोषणा _LINUX_BINFMTS_H

#समावेश <linux/sched.h>
#समावेश <linux/unistd.h>
#समावेश <यंत्र/exec.h>
#समावेश <uapi/linux/binfmts.h>

काष्ठा filename;

#घोषणा CORENAME_MAX_SIZE 128

/*
 * This काष्ठाure is used to hold the arguments that are used when loading binaries.
 */
काष्ठा linux_binprm अणु
#अगर_घोषित CONFIG_MMU
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ vma_pages;
#अन्यथा
# define MAX_ARG_PAGES	32
	काष्ठा page *page[MAX_ARG_PAGES];
#पूर्ण_अगर
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ p; /* current top of mem */
	अचिन्हित दीर्घ argmin; /* rlimit marker क्रम copy_strings() */
	अचिन्हित पूर्णांक
		/* Should an execfd be passed to userspace? */
		have_execfd:1,

		/* Use the creds of a script (see binfmt_misc) */
		execfd_creds:1,
		/*
		 * Set by bprm_creds_क्रम_exec hook to indicate a
		 * privilege-gaining exec has happened. Used to set
		 * AT_SECURE auxv क्रम glibc.
		 */
		secureexec:1,
		/*
		 * Set when errors can no दीर्घer be वापसed to the
		 * original userspace.
		 */
		poपूर्णांक_of_no_वापस:1;
#अगर_घोषित __alpha__
	अचिन्हित पूर्णांक taso:1;
#पूर्ण_अगर
	काष्ठा file *executable; /* Executable to pass to the पूर्णांकerpreter */
	काष्ठा file *पूर्णांकerpreter;
	काष्ठा file *file;
	काष्ठा cred *cred;	/* new credentials */
	पूर्णांक unsafe;		/* how unsafe this exec is (mask of LSM_UNSAFE_*) */
	अचिन्हित पूर्णांक per_clear;	/* bits to clear in current->personality */
	पूर्णांक argc, envc;
	स्थिर अक्षर *filename;	/* Name of binary as seen by procps */
	स्थिर अक्षर *पूर्णांकerp;	/* Name of the binary really executed. Most
				   of the समय same as filename, but could be
				   dअगरferent क्रम binfmt_अणुmisc,scriptपूर्ण */
	स्थिर अक्षर *fdpath;	/* generated filename क्रम execveat */
	अचिन्हित पूर्णांकerp_flags;
	पूर्णांक execfd;		/* File descriptor of the executable */
	अचिन्हित दीर्घ loader, exec;

	काष्ठा rlimit rlim_stack; /* Saved RLIMIT_STACK used during exec. */

	अक्षर buf[BINPRM_BUF_SIZE];
पूर्ण __अक्रमomize_layout;

#घोषणा BINPRM_FLAGS_ENFORCE_NONDUMP_BIT 0
#घोषणा BINPRM_FLAGS_ENFORCE_NONDUMP (1 << BINPRM_FLAGS_ENFORCE_NONDUMP_BIT)

/* filename of the binary will be inaccessible after exec */
#घोषणा BINPRM_FLAGS_PATH_INACCESSIBLE_BIT 2
#घोषणा BINPRM_FLAGS_PATH_INACCESSIBLE (1 << BINPRM_FLAGS_PATH_INACCESSIBLE_BIT)

/* preserve argv0 क्रम the पूर्णांकerpreter  */
#घोषणा BINPRM_FLAGS_PRESERVE_ARGV0_BIT 3
#घोषणा BINPRM_FLAGS_PRESERVE_ARGV0 (1 << BINPRM_FLAGS_PRESERVE_ARGV0_BIT)

/* Function parameter क्रम binfmt->coredump */
काष्ठा coredump_params अणु
	स्थिर kernel_siginfo_t *siginfo;
	काष्ठा pt_regs *regs;
	काष्ठा file *file;
	अचिन्हित दीर्घ limit;
	अचिन्हित दीर्घ mm_flags;
	loff_t written;
	loff_t pos;
	loff_t to_skip;
पूर्ण;

/*
 * This काष्ठाure defines the functions that are used to load the binary क्रमmats that
 * linux accepts.
 */
काष्ठा linux_binfmt अणु
	काष्ठा list_head lh;
	काष्ठा module *module;
	पूर्णांक (*load_binary)(काष्ठा linux_binprm *);
	पूर्णांक (*load_shlib)(काष्ठा file *);
	पूर्णांक (*core_dump)(काष्ठा coredump_params *cprm);
	अचिन्हित दीर्घ min_coredump;	/* minimal dump size */
पूर्ण __अक्रमomize_layout;

बाह्य व्योम __रेजिस्टर_binfmt(काष्ठा linux_binfmt *fmt, पूर्णांक insert);

/* Registration of शेष binfmt handlers */
अटल अंतरभूत व्योम रेजिस्टर_binfmt(काष्ठा linux_binfmt *fmt)
अणु
	__रेजिस्टर_binfmt(fmt, 0);
पूर्ण
/* Same as above, but adds a new binfmt at the top of the list */
अटल अंतरभूत व्योम insert_binfmt(काष्ठा linux_binfmt *fmt)
अणु
	__रेजिस्टर_binfmt(fmt, 1);
पूर्ण

बाह्य व्योम unरेजिस्टर_binfmt(काष्ठा linux_binfmt *);

बाह्य पूर्णांक __must_check हटाओ_arg_zero(काष्ठा linux_binprm *);
बाह्य पूर्णांक begin_new_exec(काष्ठा linux_binprm * bprm);
बाह्य व्योम setup_new_exec(काष्ठा linux_binprm * bprm);
बाह्य व्योम finalize_exec(काष्ठा linux_binprm *bprm);
बाह्य व्योम would_dump(काष्ठा linux_binprm *, काष्ठा file *);

बाह्य पूर्णांक suid_dumpable;

/* Stack area protections */
#घोषणा EXSTACK_DEFAULT   0	/* Whatever the arch शेषs to */
#घोषणा EXSTACK_DISABLE_X 1	/* Disable executable stacks */
#घोषणा EXSTACK_ENABLE_X  2	/* Enable executable stacks */

बाह्य पूर्णांक setup_arg_pages(काष्ठा linux_binprm * bprm,
			   अचिन्हित दीर्घ stack_top,
			   पूर्णांक executable_stack);
बाह्य पूर्णांक transfer_args_to_stack(काष्ठा linux_binprm *bprm,
				  अचिन्हित दीर्घ *sp_location);
बाह्य पूर्णांक bprm_change_पूर्णांकerp(स्थिर अक्षर *पूर्णांकerp, काष्ठा linux_binprm *bprm);
पूर्णांक copy_string_kernel(स्थिर अक्षर *arg, काष्ठा linux_binprm *bprm);
बाह्य व्योम set_binfmt(काष्ठा linux_binfmt *new);
बाह्य sमाप_प्रकार पढ़ो_code(काष्ठा file *, अचिन्हित दीर्घ, loff_t, माप_प्रकार);

पूर्णांक kernel_execve(स्थिर अक्षर *filename,
		  स्थिर अक्षर *स्थिर *argv, स्थिर अक्षर *स्थिर *envp);

#पूर्ण_अगर /* _LINUX_BINFMTS_H */
