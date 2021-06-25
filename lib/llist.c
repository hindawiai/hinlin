<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Lock-less शून्य terminated single linked list
 *
 * The basic atomic operation of this list is cmpxchg on दीर्घ.  On
 * architectures that करोn't have NMI-safe cmpxchg implementation, the
 * list can NOT be used in NMI handlers.  So code that uses the list in
 * an NMI handler should depend on CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG.
 *
 * Copyright 2010,2011 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/llist.h>


/**
 * llist_add_batch - add several linked entries in batch
 * @new_first:	first entry in batch to be added
 * @new_last:	last entry in batch to be added
 * @head:	the head क्रम your lock-less list
 *
 * Return whether list is empty beक्रमe adding.
 */
bool llist_add_batch(काष्ठा llist_node *new_first, काष्ठा llist_node *new_last,
		     काष्ठा llist_head *head)
अणु
	काष्ठा llist_node *first;

	करो अणु
		new_last->next = first = READ_ONCE(head->first);
	पूर्ण जबतक (cmpxchg(&head->first, first, new_first) != first);

	वापस !first;
पूर्ण
EXPORT_SYMBOL_GPL(llist_add_batch);

/**
 * llist_del_first - delete the first entry of lock-less list
 * @head:	the head क्रम your lock-less list
 *
 * If list is empty, वापस शून्य, otherwise, वापस the first entry
 * deleted, this is the newest added one.
 *
 * Only one llist_del_first user can be used simultaneously with
 * multiple llist_add users without lock.  Because otherwise
 * llist_del_first, llist_add, llist_add (or llist_del_all, llist_add,
 * llist_add) sequence in another user may change @head->first->next,
 * but keep @head->first.  If multiple consumers are needed, please
 * use llist_del_all or use lock between consumers.
 */
काष्ठा llist_node *llist_del_first(काष्ठा llist_head *head)
अणु
	काष्ठा llist_node *entry, *old_entry, *next;

	entry = smp_load_acquire(&head->first);
	क्रम (;;) अणु
		अगर (entry == शून्य)
			वापस शून्य;
		old_entry = entry;
		next = READ_ONCE(entry->next);
		entry = cmpxchg(&head->first, old_entry, next);
		अगर (entry == old_entry)
			अवरोध;
	पूर्ण

	वापस entry;
पूर्ण
EXPORT_SYMBOL_GPL(llist_del_first);

/**
 * llist_reverse_order - reverse order of a llist chain
 * @head:	first item of the list to be reversed
 *
 * Reverse the order of a chain of llist entries and वापस the
 * new first entry.
 */
काष्ठा llist_node *llist_reverse_order(काष्ठा llist_node *head)
अणु
	काष्ठा llist_node *new_head = शून्य;

	जबतक (head) अणु
		काष्ठा llist_node *पंचांगp = head;
		head = head->next;
		पंचांगp->next = new_head;
		new_head = पंचांगp;
	पूर्ण

	वापस new_head;
पूर्ण
EXPORT_SYMBOL_GPL(llist_reverse_order);
