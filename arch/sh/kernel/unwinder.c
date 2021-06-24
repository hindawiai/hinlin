<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009  Matt Fleming
 *
 * Based, in part, on kernel/समय/घड़ीsource.c.
 *
 * This file provides arbitration code क्रम stack unwinders.
 *
 * Multiple stack unwinders can be available on a प्रणाली, usually with
 * the most accurate unwinder being the currently active one.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unwinder.h>
#समावेश <linux/atomic.h>

/*
 * This is the most basic stack unwinder an architecture can
 * provide. For architectures without reliable frame poपूर्णांकers, e.g.
 * RISC CPUs, it can be implemented by looking through the stack क्रम
 * addresses that lie within the kernel text section.
 *
 * Other CPUs, e.g. x86, can use their frame poपूर्णांकer रेजिस्टर to
 * स्थिरruct more accurate stack traces.
 */
अटल काष्ठा list_head unwinder_list;
अटल काष्ठा unwinder stack_पढ़ोer = अणु
	.name = "stack-reader",
	.dump = stack_पढ़ोer_dump,
	.rating = 50,
	.list = अणु
		.next = &unwinder_list,
		.prev = &unwinder_list,
	पूर्ण,
पूर्ण;

/*
 * "curr_unwinder" poपूर्णांकs to the stack unwinder currently in use. This
 * is the unwinder with the highest rating.
 *
 * "unwinder_list" is a linked-list of all available unwinders, sorted
 * by rating.
 *
 * All modअगरications of "curr_unwinder" and "unwinder_list" must be
 * perक्रमmed whilst holding "unwinder_lock".
 */
अटल काष्ठा unwinder *curr_unwinder = &stack_पढ़ोer;

अटल काष्ठा list_head unwinder_list = अणु
	.next = &stack_पढ़ोer.list,
	.prev = &stack_पढ़ोer.list,
पूर्ण;

अटल DEFINE_SPINLOCK(unwinder_lock);

/**
 * select_unwinder - Select the best रेजिस्टरed stack unwinder.
 *
 * Private function. Must hold unwinder_lock when called.
 *
 * Select the stack unwinder with the best rating. This is useful क्रम
 * setting up curr_unwinder.
 */
अटल काष्ठा unwinder *select_unwinder(व्योम)
अणु
	काष्ठा unwinder *best;

	अगर (list_empty(&unwinder_list))
		वापस शून्य;

	best = list_entry(unwinder_list.next, काष्ठा unwinder, list);
	अगर (best == curr_unwinder)
		वापस शून्य;

	वापस best;
पूर्ण

/*
 * Enqueue the stack unwinder sorted by rating.
 */
अटल पूर्णांक unwinder_enqueue(काष्ठा unwinder *ops)
अणु
	काष्ठा list_head *पंचांगp, *entry = &unwinder_list;

	list_क्रम_each(पंचांगp, &unwinder_list) अणु
		काष्ठा unwinder *o;

		o = list_entry(पंचांगp, काष्ठा unwinder, list);
		अगर (o == ops)
			वापस -EBUSY;
		/* Keep track of the place, where to insert */
		अगर (o->rating >= ops->rating)
			entry = पंचांगp;
	पूर्ण
	list_add(&ops->list, entry);

	वापस 0;
पूर्ण

/**
 * unwinder_रेजिस्टर - Used to install new stack unwinder
 * @u: unwinder to be रेजिस्टरed
 *
 * Install the new stack unwinder on the unwinder list, which is sorted
 * by rating.
 *
 * Returns -EBUSY अगर registration fails, zero otherwise.
 */
पूर्णांक unwinder_रेजिस्टर(काष्ठा unwinder *u)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&unwinder_lock, flags);
	ret = unwinder_enqueue(u);
	अगर (!ret)
		curr_unwinder = select_unwinder();
	spin_unlock_irqrestore(&unwinder_lock, flags);

	वापस ret;
पूर्ण

पूर्णांक unwinder_faulted = 0;

/*
 * Unwind the call stack and pass inक्रमmation to the stacktrace_ops
 * functions. Also handle the हाल where we need to चयन to a new
 * stack dumper because the current one faulted unexpectedly.
 */
व्योम unwind_stack(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		  अचिन्हित दीर्घ *sp, स्थिर काष्ठा stacktrace_ops *ops,
		  व्योम *data)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * The problem with unwinders with high ratings is that they are
	 * inherently more complicated than the simple ones with lower
	 * ratings. We are thereक्रमe more likely to fault in the
	 * complicated ones, e.g. hitting BUG()s. If we fault in the
	 * code क्रम the current stack unwinder we try to करोwngrade to
	 * one with a lower rating.
	 *
	 * Hopefully this will give us a semi-reliable stacktrace so we
	 * can diagnose why curr_unwinder->dump() faulted.
	 */
	अगर (unwinder_faulted) अणु
		spin_lock_irqsave(&unwinder_lock, flags);

		/* Make sure no one beat us to changing the unwinder */
		अगर (unwinder_faulted && !list_is_singular(&unwinder_list)) अणु
			list_del(&curr_unwinder->list);
			curr_unwinder = select_unwinder();

			unwinder_faulted = 0;
		पूर्ण

		spin_unlock_irqrestore(&unwinder_lock, flags);
	पूर्ण

	curr_unwinder->dump(task, regs, sp, ops, data);
पूर्ण
EXPORT_SYMBOL_GPL(unwind_stack);
