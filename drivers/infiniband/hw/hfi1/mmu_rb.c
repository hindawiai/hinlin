<शैली गुरु>
/*
 * Copyright(c) 2020 Cornelis Networks, Inc.
 * Copyright(c) 2016 - 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/पूर्णांकerval_tree_generic.h>
#समावेश <linux/sched/mm.h>

#समावेश "mmu_rb.h"
#समावेश "trace.h"

अटल अचिन्हित दीर्घ mmu_node_start(काष्ठा mmu_rb_node *);
अटल अचिन्हित दीर्घ mmu_node_last(काष्ठा mmu_rb_node *);
अटल पूर्णांक mmu_notअगरier_range_start(काष्ठा mmu_notअगरier *,
		स्थिर काष्ठा mmu_notअगरier_range *);
अटल काष्ठा mmu_rb_node *__mmu_rb_search(काष्ठा mmu_rb_handler *,
					   अचिन्हित दीर्घ, अचिन्हित दीर्घ);
अटल व्योम करो_हटाओ(काष्ठा mmu_rb_handler *handler,
		      काष्ठा list_head *del_list);
अटल व्योम handle_हटाओ(काष्ठा work_काष्ठा *work);

अटल स्थिर काष्ठा mmu_notअगरier_ops mn_opts = अणु
	.invalidate_range_start = mmu_notअगरier_range_start,
पूर्ण;

INTERVAL_TREE_DEFINE(काष्ठा mmu_rb_node, node, अचिन्हित दीर्घ, __last,
		     mmu_node_start, mmu_node_last, अटल, __mmu_पूर्णांक_rb);

अटल अचिन्हित दीर्घ mmu_node_start(काष्ठा mmu_rb_node *node)
अणु
	वापस node->addr & PAGE_MASK;
पूर्ण

अटल अचिन्हित दीर्घ mmu_node_last(काष्ठा mmu_rb_node *node)
अणु
	वापस PAGE_ALIGN(node->addr + node->len) - 1;
पूर्ण

पूर्णांक hfi1_mmu_rb_रेजिस्टर(व्योम *ops_arg,
			 काष्ठा mmu_rb_ops *ops,
			 काष्ठा workqueue_काष्ठा *wq,
			 काष्ठा mmu_rb_handler **handler)
अणु
	काष्ठा mmu_rb_handler *h;
	पूर्णांक ret;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस -ENOMEM;

	h->root = RB_ROOT_CACHED;
	h->ops = ops;
	h->ops_arg = ops_arg;
	INIT_HLIST_NODE(&h->mn.hlist);
	spin_lock_init(&h->lock);
	h->mn.ops = &mn_opts;
	INIT_WORK(&h->del_work, handle_हटाओ);
	INIT_LIST_HEAD(&h->del_list);
	INIT_LIST_HEAD(&h->lru_list);
	h->wq = wq;

	ret = mmu_notअगरier_रेजिस्टर(&h->mn, current->mm);
	अगर (ret) अणु
		kमुक्त(h);
		वापस ret;
	पूर्ण

	*handler = h;
	वापस 0;
पूर्ण

व्योम hfi1_mmu_rb_unरेजिस्टर(काष्ठा mmu_rb_handler *handler)
अणु
	काष्ठा mmu_rb_node *rbnode;
	काष्ठा rb_node *node;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head del_list;

	/* Unरेजिस्टर first so we करोn't get any more notअगरications. */
	mmu_notअगरier_unरेजिस्टर(&handler->mn, handler->mn.mm);

	/*
	 * Make sure the wq delete handler is finished running.  It will not
	 * be triggered once the mmu notअगरiers are unरेजिस्टरed above.
	 */
	flush_work(&handler->del_work);

	INIT_LIST_HEAD(&del_list);

	spin_lock_irqsave(&handler->lock, flags);
	जबतक ((node = rb_first_cached(&handler->root))) अणु
		rbnode = rb_entry(node, काष्ठा mmu_rb_node, node);
		rb_erase_cached(node, &handler->root);
		/* move from LRU list to delete list */
		list_move(&rbnode->list, &del_list);
	पूर्ण
	spin_unlock_irqrestore(&handler->lock, flags);

	करो_हटाओ(handler, &del_list);

	kमुक्त(handler);
पूर्ण

पूर्णांक hfi1_mmu_rb_insert(काष्ठा mmu_rb_handler *handler,
		       काष्ठा mmu_rb_node *mnode)
अणु
	काष्ठा mmu_rb_node *node;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	trace_hfi1_mmu_rb_insert(mnode->addr, mnode->len);

	अगर (current->mm != handler->mn.mm)
		वापस -EPERM;

	spin_lock_irqsave(&handler->lock, flags);
	node = __mmu_rb_search(handler, mnode->addr, mnode->len);
	अगर (node) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण
	__mmu_पूर्णांक_rb_insert(mnode, &handler->root);
	list_add(&mnode->list, &handler->lru_list);

	ret = handler->ops->insert(handler->ops_arg, mnode);
	अगर (ret) अणु
		__mmu_पूर्णांक_rb_हटाओ(mnode, &handler->root);
		list_del(&mnode->list); /* हटाओ from LRU list */
	पूर्ण
	mnode->handler = handler;
unlock:
	spin_unlock_irqrestore(&handler->lock, flags);
	वापस ret;
पूर्ण

/* Caller must hold handler lock */
अटल काष्ठा mmu_rb_node *__mmu_rb_search(काष्ठा mmu_rb_handler *handler,
					   अचिन्हित दीर्घ addr,
					   अचिन्हित दीर्घ len)
अणु
	काष्ठा mmu_rb_node *node = शून्य;

	trace_hfi1_mmu_rb_search(addr, len);
	अगर (!handler->ops->filter) अणु
		node = __mmu_पूर्णांक_rb_iter_first(&handler->root, addr,
					       (addr + len) - 1);
	पूर्ण अन्यथा अणु
		क्रम (node = __mmu_पूर्णांक_rb_iter_first(&handler->root, addr,
						    (addr + len) - 1);
		     node;
		     node = __mmu_पूर्णांक_rb_iter_next(node, addr,
						   (addr + len) - 1)) अणु
			अगर (handler->ops->filter(node, addr, len))
				वापस node;
		पूर्ण
	पूर्ण
	वापस node;
पूर्ण

bool hfi1_mmu_rb_हटाओ_unless_exact(काष्ठा mmu_rb_handler *handler,
				     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				     काष्ठा mmu_rb_node **rb_node)
अणु
	काष्ठा mmu_rb_node *node;
	अचिन्हित दीर्घ flags;
	bool ret = false;

	अगर (current->mm != handler->mn.mm)
		वापस ret;

	spin_lock_irqsave(&handler->lock, flags);
	node = __mmu_rb_search(handler, addr, len);
	अगर (node) अणु
		अगर (node->addr == addr && node->len == len)
			जाओ unlock;
		__mmu_पूर्णांक_rb_हटाओ(node, &handler->root);
		list_del(&node->list); /* हटाओ from LRU list */
		ret = true;
	पूर्ण
unlock:
	spin_unlock_irqrestore(&handler->lock, flags);
	*rb_node = node;
	वापस ret;
पूर्ण

व्योम hfi1_mmu_rb_evict(काष्ठा mmu_rb_handler *handler, व्योम *evict_arg)
अणु
	काष्ठा mmu_rb_node *rbnode, *ptr;
	काष्ठा list_head del_list;
	अचिन्हित दीर्घ flags;
	bool stop = false;

	अगर (current->mm != handler->mn.mm)
		वापस;

	INIT_LIST_HEAD(&del_list);

	spin_lock_irqsave(&handler->lock, flags);
	list_क्रम_each_entry_safe_reverse(rbnode, ptr, &handler->lru_list,
					 list) अणु
		अगर (handler->ops->evict(handler->ops_arg, rbnode, evict_arg,
					&stop)) अणु
			__mmu_पूर्णांक_rb_हटाओ(rbnode, &handler->root);
			/* move from LRU list to delete list */
			list_move(&rbnode->list, &del_list);
		पूर्ण
		अगर (stop)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&handler->lock, flags);

	जबतक (!list_empty(&del_list)) अणु
		rbnode = list_first_entry(&del_list, काष्ठा mmu_rb_node, list);
		list_del(&rbnode->list);
		handler->ops->हटाओ(handler->ops_arg, rbnode);
	पूर्ण
पूर्ण

/*
 * It is up to the caller to ensure that this function करोes not race with the
 * mmu invalidate notअगरier which may be calling the users हटाओ callback on
 * 'node'.
 */
व्योम hfi1_mmu_rb_हटाओ(काष्ठा mmu_rb_handler *handler,
			काष्ठा mmu_rb_node *node)
अणु
	अचिन्हित दीर्घ flags;

	अगर (current->mm != handler->mn.mm)
		वापस;

	/* Validity of handler and node poपूर्णांकers has been checked by caller. */
	trace_hfi1_mmu_rb_हटाओ(node->addr, node->len);
	spin_lock_irqsave(&handler->lock, flags);
	__mmu_पूर्णांक_rb_हटाओ(node, &handler->root);
	list_del(&node->list); /* हटाओ from LRU list */
	spin_unlock_irqrestore(&handler->lock, flags);

	handler->ops->हटाओ(handler->ops_arg, node);
पूर्ण

अटल पूर्णांक mmu_notअगरier_range_start(काष्ठा mmu_notअगरier *mn,
		स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा mmu_rb_handler *handler =
		container_of(mn, काष्ठा mmu_rb_handler, mn);
	काष्ठा rb_root_cached *root = &handler->root;
	काष्ठा mmu_rb_node *node, *ptr = शून्य;
	अचिन्हित दीर्घ flags;
	bool added = false;

	spin_lock_irqsave(&handler->lock, flags);
	क्रम (node = __mmu_पूर्णांक_rb_iter_first(root, range->start, range->end-1);
	     node; node = ptr) अणु
		/* Guard against node removal. */
		ptr = __mmu_पूर्णांक_rb_iter_next(node, range->start,
					     range->end - 1);
		trace_hfi1_mmu_mem_invalidate(node->addr, node->len);
		अगर (handler->ops->invalidate(handler->ops_arg, node)) अणु
			__mmu_पूर्णांक_rb_हटाओ(node, root);
			/* move from LRU list to delete list */
			list_move(&node->list, &handler->del_list);
			added = true;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&handler->lock, flags);

	अगर (added)
		queue_work(handler->wq, &handler->del_work);

	वापस 0;
पूर्ण

/*
 * Call the हटाओ function क्रम the given handler and the list.  This
 * is expected to be called with a delete list extracted from handler.
 * The caller should not be holding the handler lock.
 */
अटल व्योम करो_हटाओ(काष्ठा mmu_rb_handler *handler,
		      काष्ठा list_head *del_list)
अणु
	काष्ठा mmu_rb_node *node;

	जबतक (!list_empty(del_list)) अणु
		node = list_first_entry(del_list, काष्ठा mmu_rb_node, list);
		list_del(&node->list);
		handler->ops->हटाओ(handler->ops_arg, node);
	पूर्ण
पूर्ण

/*
 * Work queue function to हटाओ all nodes that have been queued up to
 * be हटाओd.  The key feature is that mm->mmap_lock is not being held
 * and the हटाओ callback can sleep जबतक taking it, अगर needed.
 */
अटल व्योम handle_हटाओ(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmu_rb_handler *handler = container_of(work,
						काष्ठा mmu_rb_handler,
						del_work);
	काष्ठा list_head del_list;
	अचिन्हित दीर्घ flags;

	/* हटाओ anything that is queued to get हटाओd */
	spin_lock_irqsave(&handler->lock, flags);
	list_replace_init(&handler->del_list, &del_list);
	spin_unlock_irqrestore(&handler->lock, flags);

	करो_हटाओ(handler, &del_list);
पूर्ण
