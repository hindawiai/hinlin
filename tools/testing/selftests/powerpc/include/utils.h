<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2013, Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_UTILS_H
#घोषणा _SELFTESTS_POWERPC_UTILS_H

#घोषणा __cacheline_aligned __attribute__((aligned(128)))

#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <linux/auxvec.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/cputable.h>
#समावेश "reg.h"

/* Aव्योम headaches with PRI?64 - just use %ll? always */
प्रकार अचिन्हित दीर्घ दीर्घ u64;
प्रकार   चिन्हित दीर्घ दीर्घ s64;

/* Just क्रम familiarity */
प्रकार uपूर्णांक32_t u32;
प्रकार uपूर्णांक16_t u16;
प्रकार uपूर्णांक8_t u8;

व्योम test_harness_set_समयout(uपूर्णांक64_t समय);
पूर्णांक test_harness(पूर्णांक (test_function)(व्योम), अक्षर *name);

पूर्णांक पढ़ो_auxv(अक्षर *buf, sमाप_प्रकार buf_size);
व्योम *find_auxv_entry(पूर्णांक type, अक्षर *auxv);
व्योम *get_auxv_entry(पूर्णांक type);

पूर्णांक pick_online_cpu(व्योम);

पूर्णांक पढ़ो_debugfs_file(अक्षर *debugfs_file, पूर्णांक *result);
पूर्णांक ग_लिखो_debugfs_file(अक्षर *debugfs_file, पूर्णांक result);
पूर्णांक पढ़ो_sysfs_file(अक्षर *debugfs_file, अक्षर *result, माप_प्रकार result_size);
पूर्णांक perf_event_खोलो_counter(अचिन्हित पूर्णांक type,
			    अचिन्हित दीर्घ config, पूर्णांक group_fd);
पूर्णांक perf_event_enable(पूर्णांक fd);
पूर्णांक perf_event_disable(पूर्णांक fd);
पूर्णांक perf_event_reset(पूर्णांक fd);

काष्ठा perf_event_पढ़ो अणु
	__u64 nr;
	__u64 l1d_misses;
पूर्ण;

#अगर !defined(__GLIBC_PREREQ) || !__GLIBC_PREREQ(2, 30)
#समावेश <unistd.h>
#समावेश <sys/syscall.h>

अटल अंतरभूत pid_t gettid(व्योम)
अणु
	वापस syscall(SYS_gettid);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool have_hwcap(अचिन्हित दीर्घ ftr)
अणु
	वापस ((अचिन्हित दीर्घ)get_auxv_entry(AT_HWCAP) & ftr) == ftr;
पूर्ण

#अगर_घोषित AT_HWCAP2
अटल अंतरभूत bool have_hwcap2(अचिन्हित दीर्घ ftr2)
अणु
	वापस ((अचिन्हित दीर्घ)get_auxv_entry(AT_HWCAP2) & ftr2) == ftr2;
पूर्ण
#अन्यथा
अटल अंतरभूत bool have_hwcap2(अचिन्हित दीर्घ ftr2)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

bool is_ppc64le(व्योम);
पूर्णांक using_hash_mmu(bool *using_hash);

/* Yes, this is evil */
#घोषणा FAIL_IF(x)						\
करो अणु								\
	अगर ((x)) अणु						\
		ख_लिखो(मानक_त्रुटि,					\
		"[FAIL] Test FAILED on line %d\n", __LINE__);	\
		वापस 1;					\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा FAIL_IF_EXIT(x)						\
करो अणु								\
	अगर ((x)) अणु						\
		ख_लिखो(मानक_त्रुटि,					\
		"[FAIL] Test FAILED on line %d\n", __LINE__);	\
		_निकास(1);					\
	पूर्ण							\
पूर्ण जबतक (0)

/* The test harness uses this, yes it's gross */
#घोषणा MAGIC_SKIP_RETURN_VALUE	99

#घोषणा SKIP_IF(x)						\
करो अणु								\
	अगर ((x)) अणु						\
		ख_लिखो(मानक_त्रुटि,					\
		"[SKIP] Test skipped on line %d\n", __LINE__);	\
		वापस MAGIC_SKIP_RETURN_VALUE;			\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा SKIP_IF_MSG(x, msg)					\
करो अणु								\
	अगर ((x)) अणु						\
		ख_लिखो(मानक_त्रुटि,					\
		"[SKIP] Test skipped on line %d: %s\n",		\
		 __LINE__, msg);				\
		वापस MAGIC_SKIP_RETURN_VALUE;			\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा _str(s) #s
#घोषणा str(s) _str(s)

#घोषणा sigsafe_err(msg)	(अणु \
		sमाप_प्रकार nbytes __attribute__((unused)); \
		nbytes = ग_लिखो(STDERR_खाताNO, msg, म_माप(msg)); पूर्ण)

/* POWER9 feature */
#अगर_अघोषित PPC_FEATURE2_ARCH_3_00
#घोषणा PPC_FEATURE2_ARCH_3_00 0x00800000
#पूर्ण_अगर

/* POWER10 feature */
#अगर_अघोषित PPC_FEATURE2_ARCH_3_1
#घोषणा PPC_FEATURE2_ARCH_3_1 0x00040000
#पूर्ण_अगर

#अगर defined(__घातerpc64__)
#घोषणा UCONTEXT_NIA(UC)	(UC)->uc_mcontext.gp_regs[PT_NIP]
#घोषणा UCONTEXT_MSR(UC)	(UC)->uc_mcontext.gp_regs[PT_MSR]
#या_अगर defined(__घातerpc__)
#घोषणा UCONTEXT_NIA(UC)	(UC)->uc_mcontext.uc_regs->gregs[PT_NIP]
#घोषणा UCONTEXT_MSR(UC)	(UC)->uc_mcontext.uc_regs->gregs[PT_MSR]
#अन्यथा
#त्रुटि implement UCONTEXT_NIA
#पूर्ण_अगर

#पूर्ण_अगर /* _SELFTESTS_POWERPC_UTILS_H */
