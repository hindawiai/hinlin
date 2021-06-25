<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_USER_H
#घोषणा __ASM_SH_USER_H

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/page.h>

/*
 * Core file क्रमmat: The core file is written in such a way that gdb
 * can understand it and provide useful inक्रमmation to the user (under
 * linux we use the `trad-core' bfd).  The file contents are as follows:
 *
 *  upage: 1 page consisting of a user काष्ठा that tells gdb
 *	what is present in the file.  Directly after this is a
 *	copy of the task_काष्ठा, which is currently not used by gdb,
 *	but it may come in handy at some poपूर्णांक.  All of the रेजिस्टरs
 *	are stored as part of the upage.  The upage should always be
 *	only one page दीर्घ.
 *  data: The data segment follows next.  We use current->end_text to
 *	current->brk to pick up all of the user variables, plus any memory
 *	that may have been sbrk'ed.  No attempt is made to determine अगर a
 *	page is demand-zero or अगर a page is totally unused, we just cover
 *	the entire range.  All of the addresses are rounded in such a way
 *	that an पूर्णांकegral number of pages is written.
 *  stack: We need the stack inक्रमmation in order to get a meaningful
 *	backtrace.  We need to ग_लिखो the data from usp to
 *	current->start_stack, so we round each of these in order to be able
 *	to ग_लिखो an पूर्णांकeger number of pages.
 */

काष्ठा user_fpu_काष्ठा अणु
	अचिन्हित दीर्घ fp_regs[16];
	अचिन्हित दीर्घ xfp_regs[16];
	अचिन्हित दीर्घ fpscr;
	अचिन्हित दीर्घ fpul;
पूर्ण;

काष्ठा user अणु
	काष्ठा pt_regs	regs;			/* entire machine state */
	काष्ठा user_fpu_काष्ठा fpu;	/* Math Co-processor रेजिस्टरs  */
	पूर्णांक u_fpvalid;		/* True अगर math co-processor being used */
	माप_प्रकार		u_tsize;		/* text size (pages) */
	माप_प्रकार		u_dsize;		/* data size (pages) */
	माप_प्रकार		u_ssize;		/* stack size (pages) */
	अचिन्हित दीर्घ	start_code;		/* text starting address */
	अचिन्हित दीर्घ	start_data;		/* data starting address */
	अचिन्हित दीर्घ	start_stack;		/* stack starting address */
	दीर्घ पूर्णांक	संकेत;			/* संकेत causing core dump */
	अचिन्हित दीर्घ	u_ar0;			/* help gdb find रेजिस्टरs */
	काष्ठा user_fpu_काष्ठा* u_fpstate;	/* Math Co-processor poपूर्णांकer */
	अचिन्हित दीर्घ	magic;			/* identअगरies a core file */
	अक्षर		u_comm[32];		/* user command name */
पूर्ण;

#घोषणा NBPG			PAGE_SIZE
#घोषणा UPAGES			1
#घोषणा HOST_TEXT_START_ADDR	(u.start_code)
#घोषणा HOST_DATA_START_ADDR	(u.start_data)
#घोषणा HOST_STACK_END_ADDR	(u.start_stack + u.u_ssize * NBPG)

#पूर्ण_अगर /* __ASM_SH_USER_H */
