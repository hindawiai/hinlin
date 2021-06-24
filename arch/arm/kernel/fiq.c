<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/kernel/fiq.c
 *
 *  Copyright (C) 1998 Russell King
 *  Copyright (C) 1998, 1999 Phil Blundell
 *
 *  FIQ support written by Philip Blundell <philb@gnu.org>, 1998.
 *
 *  FIQ support re-written by Russell King to be more generic
 *
 * We now properly support a method by which the FIQ handlers can
 * be stacked onto the vector.  We still करो not support sharing
 * the FIQ vector itself.
 *
 * Operation is as follows:
 *  1. Owner A claims FIQ:
 *     - शेष_fiq relinquishes control.
 *  2. Owner A:
 *     - inserts code.
 *     - sets any रेजिस्टरs,
 *     - enables FIQ.
 *  3. Owner B claims FIQ:
 *     - अगर owner A has a relinquish function.
 *       - disable FIQs.
 *       - saves any रेजिस्टरs.
 *       - वापसs zero.
 *  4. Owner B:
 *     - inserts code.
 *     - sets any रेजिस्टरs,
 *     - enables FIQ.
 *  5. Owner B releases FIQ:
 *     - Owner A is asked to reacquire FIQ:
 *	 - inserts code.
 *	 - restores saved रेजिस्टरs.
 *	 - enables FIQ.
 *  6. Goto 3
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/fiq.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>

#घोषणा FIQ_OFFSET (अणु					\
		बाह्य व्योम *vector_fiq_offset;		\
		(अचिन्हित)&vector_fiq_offset;		\
	पूर्ण)

अटल अचिन्हित दीर्घ dfl_fiq_insn;
अटल काष्ठा pt_regs dfl_fiq_regs;

/* Default reacquire function
 * - we always relinquish FIQ control
 * - we always reacquire FIQ control
 */
अटल पूर्णांक fiq_def_op(व्योम *ref, पूर्णांक relinquish)
अणु
	अगर (!relinquish) अणु
		/* Restore शेष handler and रेजिस्टरs */
		local_fiq_disable();
		set_fiq_regs(&dfl_fiq_regs);
		set_fiq_handler(&dfl_fiq_insn, माप(dfl_fiq_insn));
		local_fiq_enable();

		/* FIXME: notअगरy irq controller to standard enable FIQs */
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा fiq_handler शेष_owner = अणु
	.name	= "default",
	.fiq_op = fiq_def_op,
पूर्ण;

अटल काष्ठा fiq_handler *current_fiq = &शेष_owner;

पूर्णांक show_fiq_list(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	अगर (current_fiq != &शेष_owner)
		seq_म_लिखो(p, "%*s:              %s\n", prec, "FIQ",
			current_fiq->name);

	वापस 0;
पूर्ण

व्योम set_fiq_handler(व्योम *start, अचिन्हित पूर्णांक length)
अणु
	व्योम *base = vectors_page;
	अचिन्हित offset = FIQ_OFFSET;

	स_नकल(base + offset, start, length);
	अगर (!cache_is_vipt_nonaliasing())
		flush_icache_range((अचिन्हित दीर्घ)base + offset,
				   (अचिन्हित दीर्घ)base + offset + length);
	flush_icache_range(0xffff0000 + offset, 0xffff0000 + offset + length);
पूर्ण

पूर्णांक claim_fiq(काष्ठा fiq_handler *f)
अणु
	पूर्णांक ret = 0;

	अगर (current_fiq) अणु
		ret = -EBUSY;

		अगर (current_fiq->fiq_op != शून्य)
			ret = current_fiq->fiq_op(current_fiq->dev_id, 1);
	पूर्ण

	अगर (!ret) अणु
		f->next = current_fiq;
		current_fiq = f;
	पूर्ण

	वापस ret;
पूर्ण

व्योम release_fiq(काष्ठा fiq_handler *f)
अणु
	अगर (current_fiq != f) अणु
		pr_err("%s FIQ trying to release %s FIQ\n",
		       f->name, current_fiq->name);
		dump_stack();
		वापस;
	पूर्ण

	करो
		current_fiq = current_fiq->next;
	जबतक (current_fiq->fiq_op(current_fiq->dev_id, 0));
पूर्ण

अटल पूर्णांक fiq_start;

व्योम enable_fiq(पूर्णांक fiq)
अणु
	enable_irq(fiq + fiq_start);
पूर्ण

व्योम disable_fiq(पूर्णांक fiq)
अणु
	disable_irq(fiq + fiq_start);
पूर्ण

EXPORT_SYMBOL(set_fiq_handler);
EXPORT_SYMBOL(__set_fiq_regs);	/* defined in fiqयंत्र.S */
EXPORT_SYMBOL(__get_fiq_regs);	/* defined in fiqयंत्र.S */
EXPORT_SYMBOL(claim_fiq);
EXPORT_SYMBOL(release_fiq);
EXPORT_SYMBOL(enable_fiq);
EXPORT_SYMBOL(disable_fiq);

व्योम __init init_FIQ(पूर्णांक start)
अणु
	अचिन्हित offset = FIQ_OFFSET;
	dfl_fiq_insn = *(अचिन्हित दीर्घ *)(0xffff0000 + offset);
	get_fiq_regs(&dfl_fiq_regs);
	fiq_start = start;
पूर्ण
