<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_USER_H
#घोषणा _H8300_USER_H

#समावेश <यंत्र/page.h>

/* Core file क्रमmat: The core file is written in such a way that gdb
   can understand it and provide useful inक्रमmation to the user (under
   linux we use the 'trad-core' bfd).  There are quite a number of
   obstacles to being able to view the contents of the भग्नing poपूर्णांक
   रेजिस्टरs, and until these are solved you will not be able to view the
   contents of them.  Actually, you can पढ़ो in the core file and look at
   the contents of the user काष्ठा to find out what the भग्नing poपूर्णांक
   रेजिस्टरs contain.
   The actual file contents are as follows:
   UPAGE: 1 page consisting of a user काष्ठा that tells gdb what is present
   in the file.  Directly after this is a copy of the task_काष्ठा, which
   is currently not used by gdb, but it may come in useful at some poपूर्णांक.
   All of the रेजिस्टरs are stored as part of the upage.  The upage should
   always be only one page.
   DATA: The data area is stored.  We use current->end_text to
   current->brk to pick up all of the user variables, plus any memory
   that may have been दो_स्मृतिed.  No attempt is made to determine अगर a page
   is demand-zero or अगर a page is totally unused, we just cover the entire
   range.  All of the addresses are rounded in such a way that an पूर्णांकegral
   number of pages is written.
   STACK: We need the stack inक्रमmation in order to get a meaningful
   backtrace.  We need to ग_लिखो the data from (esp) to
   current->start_stack, so we round each of these off in order to be able
   to ग_लिखो an पूर्णांकeger number of pages.
   The minimum core file size is 3 pages, or 12288 bytes.
*/

/* This is the old layout of "struct pt_regs" as of Linux 1.x, and
   is still the layout used by user (the new pt_regs करोesn't have
   all रेजिस्टरs). */
काष्ठा user_regs_काष्ठा अणु
	दीर्घ er1, er2, er3, er4, er5, er6;
	दीर्घ er0;
	दीर्घ usp;
	दीर्घ orig_er0;
	दीर्घ ccr;
	दीर्घ pc;
पूर्ण;

/* When the kernel dumps core, it starts by dumping the user काष्ठा -
   this will be used by gdb to figure out where the data and stack segments
   are within the file, and what भव addresses to use. */
काष्ठा user अणु
/* We start with the रेजिस्टरs, to mimic the way that "memory" is वापसed
   from the ptrace(3,...) function.  */
	काष्ठा user_regs_काष्ठा regs;	/* Where the रेजिस्टरs are actually stored */
/* ptrace करोes not yet supply these.  Someday.... */
/* The rest of this junk is to help gdb figure out what goes where */
	अचिन्हित दीर्घ पूर्णांक u_tsize;	/* Text segment size (pages). */
	अचिन्हित दीर्घ पूर्णांक u_dsize;	/* Data segment size (pages). */
	अचिन्हित दीर्घ पूर्णांक u_ssize;	/* Stack segment size (pages). */
	अचिन्हित दीर्घ start_code;     /* Starting भव address of text. */
	अचिन्हित दीर्घ start_stack;	/* Starting भव address of stack area.
					   This is actually the bottom of the stack,
					   the top of the stack is always found in the
					   esp रेजिस्टर.  */
	दीर्घ पूर्णांक संकेत;		/* Signal that caused the core dump. */
	पूर्णांक reserved;			/* No दीर्घer used */
	अचिन्हित दीर्घ u_ar0;		/* Used by gdb to help find the values क्रम */
	/* the रेजिस्टरs. */
	अचिन्हित दीर्घ magic;		/* To uniquely identअगरy a core file */
	अक्षर u_comm[32];		/* User command that was responsible */
पूर्ण;
#घोषणा NBPG PAGE_SIZE
#घोषणा UPAGES 1
#घोषणा HOST_TEXT_START_ADDR (u.start_code)
#घोषणा HOST_STACK_END_ADDR (u.start_stack + u.u_ssize * NBPG)

#पूर्ण_अगर
