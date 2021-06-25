<शैली गुरु>
/*
 * OpenRISC unwinder.c
 *
 * Reusable arch specअगरic api क्रम unwinding stacks.
 *
 * Copyright (C) 2017 Stafक्रमd Horne <shorne@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/unwinder.h>

#अगर_घोषित CONFIG_FRAME_POINTER
काष्ठा or1k_frameinfo अणु
	अचिन्हित दीर्घ *fp;
	अचिन्हित दीर्घ ra;
	अचिन्हित दीर्घ top;
पूर्ण;

/*
 * Verअगरy a frameinfo काष्ठाure.  The वापस address should be a valid text
 * address.  The frame poपूर्णांकer may be null अगर its the last frame, otherwise
 * the frame poपूर्णांकer should poपूर्णांक to a location in the stack after the the
 * top of the next frame up.
 */
अटल अंतरभूत पूर्णांक or1k_frameinfo_valid(काष्ठा or1k_frameinfo *frameinfo)
अणु
	वापस (frameinfo->fp == शून्य ||
		(!kstack_end(frameinfo->fp) &&
		 frameinfo->fp > &frameinfo->top)) &&
	       __kernel_text_address(frameinfo->ra);
पूर्ण

/*
 * Create a stack trace करोing scanning which is frame poपूर्णांकer aware. We can
 * get reliable stack traces by matching the previously found frame
 * poपूर्णांकer with the top of the stack address every समय we find a valid
 * or1k_frameinfo.
 *
 * Ideally the stack parameter will be passed as FP, but it can not be
 * guaranteed.  Thereक्रमe we scan each address looking क्रम the first sign
 * of a वापस address.
 *
 * The OpenRISC stack frame looks something like the following.  The
 * location SP is held in r1 and location FP is held in r2 when frame poपूर्णांकers
 * enabled.
 *
 * SP   -> (top of stack)
 *      -  (callee saved रेजिस्टरs)
 *      -  (local variables)
 * FP-8 -> previous FP             \
 * FP-4 -> वापस address          |- or1k_frameinfo
 * FP   -> (previous top of stack) /
 */
व्योम unwind_stack(व्योम *data, अचिन्हित दीर्घ *stack,
		  व्योम (*trace)(व्योम *data, अचिन्हित दीर्घ addr, पूर्णांक reliable))
अणु
	अचिन्हित दीर्घ *next_fp = शून्य;
	काष्ठा or1k_frameinfo *frameinfo = शून्य;
	पूर्णांक reliable = 0;

	जबतक (!kstack_end(stack)) अणु
		frameinfo = container_of(stack,
					 काष्ठा or1k_frameinfo,
					 top);

		अगर (__kernel_text_address(frameinfo->ra)) अणु
			अगर (or1k_frameinfo_valid(frameinfo) &&
			    (next_fp == शून्य ||
			     next_fp == &frameinfo->top)) अणु
				reliable = 1;
				next_fp = frameinfo->fp;
			पूर्ण अन्यथा
				reliable = 0;

			trace(data, frameinfo->ra, reliable);
		पूर्ण
		stack++;
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_FRAME_POINTER */

/*
 * Create a stack trace by करोing a simple scan treating all text addresses
 * as वापस addresses.
 */
व्योम unwind_stack(व्योम *data, अचिन्हित दीर्घ *stack,
		   व्योम (*trace)(व्योम *data, अचिन्हित दीर्घ addr, पूर्णांक reliable))
अणु
	अचिन्हित दीर्घ addr;

	जबतक (!kstack_end(stack)) अणु
		addr = *stack++;
		अगर (__kernel_text_address(addr))
			trace(data, addr, 0);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_FRAME_POINTER */

