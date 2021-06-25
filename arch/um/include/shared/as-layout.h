<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __START_H__
#घोषणा __START_H__

#समावेश <generated/यंत्र-offsets.h>

/*
 * Stolen from linux/स्थिर.h, which can't be directly included since
 * this is used in userspace code, which has no access to the kernel
 * headers.  Changed to be suitable क्रम adding casts to the start,
 * rather than "UL" to the end.
 */

/* Some स्थिरant macros are used in both assembler and
 * C code.  Thereक्रमe we cannot annotate them always with
 * 'UL' and other type specअगरiers unilaterally.  We
 * use the following macros to deal with this.
 */
#घोषणा STUB_START stub_start
#घोषणा STUB_CODE STUB_START
#घोषणा STUB_DATA (STUB_CODE + UM_KERN_PAGE_SIZE)
#घोषणा STUB_END (STUB_DATA + UM_KERN_PAGE_SIZE)

#अगर_अघोषित __ASSEMBLY__

#समावेश <sysdep/ptrace.h>

काष्ठा cpu_task अणु
	पूर्णांक pid;
	व्योम *task;
पूर्ण;

बाह्य काष्ठा cpu_task cpu_tasks[];

बाह्य अचिन्हित दीर्घ high_physmem;
बाह्य अचिन्हित दीर्घ uml_physmem;
बाह्य अचिन्हित दीर्घ uml_reserved;
बाह्य अचिन्हित दीर्घ end_vm;
बाह्य अचिन्हित दीर्घ start_vm;
बाह्य अचिन्हित दीर्घ दीर्घ highmem;

बाह्य अचिन्हित दीर्घ brk_start;

बाह्य अचिन्हित दीर्घ host_task_size;
बाह्य अचिन्हित दीर्घ stub_start;

बाह्य पूर्णांक linux_मुख्य(पूर्णांक argc, अक्षर **argv);
बाह्य व्योम uml_finishsetup(व्योम);

काष्ठा siginfo;
बाह्य व्योम (*sig_info[])(पूर्णांक, काष्ठा siginfo *si, काष्ठा uml_pt_regs *);

#पूर्ण_अगर

#पूर्ण_अगर
