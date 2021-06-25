<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNWINDER_H
#घोषणा _LINUX_UNWINDER_H

#समावेश <यंत्र/stacktrace.h>

काष्ठा unwinder अणु
	स्थिर अक्षर *name;
	काष्ठा list_head list;
	पूर्णांक rating;
	व्योम (*dump)(काष्ठा task_काष्ठा *, काष्ठा pt_regs *,
		     अचिन्हित दीर्घ *, स्थिर काष्ठा stacktrace_ops *, व्योम *);
पूर्ण;

बाह्य पूर्णांक unwinder_init(व्योम);
बाह्य पूर्णांक unwinder_रेजिस्टर(काष्ठा unwinder *);

बाह्य व्योम unwind_stack(काष्ठा task_काष्ठा *, काष्ठा pt_regs *,
			 अचिन्हित दीर्घ *, स्थिर काष्ठा stacktrace_ops *,
			 व्योम *);

बाह्य व्योम stack_पढ़ोer_dump(काष्ठा task_काष्ठा *, काष्ठा pt_regs *,
			      अचिन्हित दीर्घ *, स्थिर काष्ठा stacktrace_ops *,
			      व्योम *);

/*
 * Used by fault handling code to संकेत to the unwinder code that it
 * should चयन to a dअगरferent unwinder.
 */
बाह्य पूर्णांक unwinder_faulted;

#पूर्ण_अगर /* _LINUX_UNWINDER_H */
