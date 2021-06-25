<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MCE event pool management in MCE context
 *
 * Copyright (C) 2015 Intel Corp.
 * Author: Chen, Gong <gong.chen@linux.पूर्णांकel.com>
 */
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/llist.h>
#समावेश "internal.h"

/*
 * prपूर्णांकk() is not safe in MCE context. This is a lock-less memory allocator
 * used to save error inक्रमmation organized in a lock-less list.
 *
 * This memory pool is only to be used to save MCE records in MCE context.
 * MCE events are rare, so a fixed size memory pool should be enough. Use
 * 2 pages to save MCE events क्रम now (~80 MCE records at most).
 */
#घोषणा MCE_POOLSZ	(2 * PAGE_SIZE)

अटल काष्ठा gen_pool *mce_evt_pool;
अटल LLIST_HEAD(mce_event_llist);
अटल अक्षर gen_pool_buf[MCE_POOLSZ];

/*
 * Compare the record "t" with each of the records on list "l" to see अगर
 * an equivalent one is present in the list.
 */
अटल bool is_duplicate_mce_record(काष्ठा mce_evt_llist *t, काष्ठा mce_evt_llist *l)
अणु
	काष्ठा mce_evt_llist *node;
	काष्ठा mce *m1, *m2;

	m1 = &t->mce;

	llist_क्रम_each_entry(node, &l->llnode, llnode) अणु
		m2 = &node->mce;

		अगर (!mce_cmp(m1, m2))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * The प्रणाली has panicked - we'd like to peruse the list of MCE records
 * that have been queued, but not seen by anyone yet.  The list is in
 * reverse समय order, so we need to reverse it. While करोing that we can
 * also drop duplicate records (these were logged because some banks are
 * shared between cores or by all thपढ़ोs on a socket).
 */
काष्ठा llist_node *mce_gen_pool_prepare_records(व्योम)
अणु
	काष्ठा llist_node *head;
	LLIST_HEAD(new_head);
	काष्ठा mce_evt_llist *node, *t;

	head = llist_del_all(&mce_event_llist);
	अगर (!head)
		वापस शून्य;

	/* squeeze out duplicates जबतक reversing order */
	llist_क्रम_each_entry_safe(node, t, head, llnode) अणु
		अगर (!is_duplicate_mce_record(node, t))
			llist_add(&node->llnode, &new_head);
	पूर्ण

	वापस new_head.first;
पूर्ण

व्योम mce_gen_pool_process(काष्ठा work_काष्ठा *__unused)
अणु
	काष्ठा llist_node *head;
	काष्ठा mce_evt_llist *node, *पंचांगp;
	काष्ठा mce *mce;

	head = llist_del_all(&mce_event_llist);
	अगर (!head)
		वापस;

	head = llist_reverse_order(head);
	llist_क्रम_each_entry_safe(node, पंचांगp, head, llnode) अणु
		mce = &node->mce;
		blocking_notअगरier_call_chain(&x86_mce_decoder_chain, 0, mce);
		gen_pool_मुक्त(mce_evt_pool, (अचिन्हित दीर्घ)node, माप(*node));
	पूर्ण
पूर्ण

bool mce_gen_pool_empty(व्योम)
अणु
	वापस llist_empty(&mce_event_llist);
पूर्ण

पूर्णांक mce_gen_pool_add(काष्ठा mce *mce)
अणु
	काष्ठा mce_evt_llist *node;

	अगर (filter_mce(mce))
		वापस -EINVAL;

	अगर (!mce_evt_pool)
		वापस -EINVAL;

	node = (व्योम *)gen_pool_alloc(mce_evt_pool, माप(*node));
	अगर (!node) अणु
		pr_warn_ratelimited("MCE records pool full!\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&node->mce, mce, माप(*mce));
	llist_add(&node->llnode, &mce_event_llist);

	वापस 0;
पूर्ण

अटल पूर्णांक mce_gen_pool_create(व्योम)
अणु
	काष्ठा gen_pool *पंचांगpp;
	पूर्णांक ret = -ENOMEM;

	पंचांगpp = gen_pool_create(ilog2(माप(काष्ठा mce_evt_llist)), -1);
	अगर (!पंचांगpp)
		जाओ out;

	ret = gen_pool_add(पंचांगpp, (अचिन्हित दीर्घ)gen_pool_buf, MCE_POOLSZ, -1);
	अगर (ret) अणु
		gen_pool_destroy(पंचांगpp);
		जाओ out;
	पूर्ण

	mce_evt_pool = पंचांगpp;

out:
	वापस ret;
पूर्ण

पूर्णांक mce_gen_pool_init(व्योम)
अणु
	/* Just init mce_gen_pool once. */
	अगर (mce_evt_pool)
		वापस 0;

	वापस mce_gen_pool_create();
पूर्ण
