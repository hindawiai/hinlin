<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_FSGSBASE_H
#घोषणा _ASM_FSGSBASE_H

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_X86_64

#समावेश <यंत्र/msr-index.h>

/*
 * Read/ग_लिखो a task's FSBASE or GSBASE. This वापसs the value that
 * the FS/GS base would have (अगर the task were to be resumed). These
 * work on the current task or on a non-running (typically stopped
 * ptrace child) task.
 */
बाह्य अचिन्हित दीर्घ x86_fsbase_पढ़ो_task(काष्ठा task_काष्ठा *task);
बाह्य अचिन्हित दीर्घ x86_gsbase_पढ़ो_task(काष्ठा task_काष्ठा *task);
बाह्य व्योम x86_fsbase_ग_लिखो_task(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ fsbase);
बाह्य व्योम x86_gsbase_ग_लिखो_task(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ gsbase);

/* Must be रक्षित by X86_FEATURE_FSGSBASE check. */

अटल __always_अंतरभूत अचिन्हित दीर्घ rdfsbase(व्योम)
अणु
	अचिन्हित दीर्घ fsbase;

	यंत्र अस्थिर("rdfsbase %0" : "=r" (fsbase) :: "memory");

	वापस fsbase;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ rdgsbase(व्योम)
अणु
	अचिन्हित दीर्घ gsbase;

	यंत्र अस्थिर("rdgsbase %0" : "=r" (gsbase) :: "memory");

	वापस gsbase;
पूर्ण

अटल __always_अंतरभूत व्योम wrfsbase(अचिन्हित दीर्घ fsbase)
अणु
	यंत्र अस्थिर("wrfsbase %0" :: "r" (fsbase) : "memory");
पूर्ण

अटल __always_अंतरभूत व्योम wrgsbase(अचिन्हित दीर्घ gsbase)
अणु
	यंत्र अस्थिर("wrgsbase %0" :: "r" (gsbase) : "memory");
पूर्ण

#समावेश <यंत्र/cpufeature.h>

/* Helper functions क्रम पढ़ोing/writing FS/GS base */

अटल अंतरभूत अचिन्हित दीर्घ x86_fsbase_पढ़ो_cpu(व्योम)
अणु
	अचिन्हित दीर्घ fsbase;

	अगर (boot_cpu_has(X86_FEATURE_FSGSBASE))
		fsbase = rdfsbase();
	अन्यथा
		rdmsrl(MSR_FS_BASE, fsbase);

	वापस fsbase;
पूर्ण

अटल अंतरभूत व्योम x86_fsbase_ग_लिखो_cpu(अचिन्हित दीर्घ fsbase)
अणु
	अगर (boot_cpu_has(X86_FEATURE_FSGSBASE))
		wrfsbase(fsbase);
	अन्यथा
		wrmsrl(MSR_FS_BASE, fsbase);
पूर्ण

बाह्य अचिन्हित दीर्घ x86_gsbase_पढ़ो_cpu_inactive(व्योम);
बाह्य व्योम x86_gsbase_ग_लिखो_cpu_inactive(अचिन्हित दीर्घ gsbase);
बाह्य अचिन्हित दीर्घ x86_fsgsbase_पढ़ो_task(काष्ठा task_काष्ठा *task,
					    अचिन्हित लघु selector);

#पूर्ण_अगर /* CONFIG_X86_64 */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_FSGSBASE_H */
