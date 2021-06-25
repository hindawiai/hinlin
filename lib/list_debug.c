<शैली गुरु>
/*
 * Copyright 2006, Red Hat, Inc., Dave Jones
 * Released under the General Public License (GPL).
 *
 * This file contains the linked list validation क्रम DEBUG_LIST.
 */

#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rculist.h>

/*
 * Check that the data काष्ठाures क्रम the list manipulations are reasonably
 * valid. Failures here indicate memory corruption (and possibly an exploit
 * attempt).
 */

bool __list_add_valid(काष्ठा list_head *new, काष्ठा list_head *prev,
		      काष्ठा list_head *next)
अणु
	अगर (CHECK_DATA_CORRUPTION(next->prev != prev,
			"list_add corruption. next->prev should be prev (%px), but was %px. (next=%px).\n",
			prev, next->prev, next) ||
	    CHECK_DATA_CORRUPTION(prev->next != next,
			"list_add corruption. prev->next should be next (%px), but was %px. (prev=%px).\n",
			next, prev->next, prev) ||
	    CHECK_DATA_CORRUPTION(new == prev || new == next,
			"list_add double add: new=%px, prev=%px, next=%px.\n",
			new, prev, next))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(__list_add_valid);

bool __list_del_entry_valid(काष्ठा list_head *entry)
अणु
	काष्ठा list_head *prev, *next;

	prev = entry->prev;
	next = entry->next;

	अगर (CHECK_DATA_CORRUPTION(next == LIST_POISON1,
			"list_del corruption, %px->next is LIST_POISON1 (%px)\n",
			entry, LIST_POISON1) ||
	    CHECK_DATA_CORRUPTION(prev == LIST_POISON2,
			"list_del corruption, %px->prev is LIST_POISON2 (%px)\n",
			entry, LIST_POISON2) ||
	    CHECK_DATA_CORRUPTION(prev->next != entry,
			"list_del corruption. prev->next should be %px, but was %px\n",
			entry, prev->next) ||
	    CHECK_DATA_CORRUPTION(next->prev != entry,
			"list_del corruption. next->prev should be %px, but was %px\n",
			entry, next->prev))
		वापस false;

	वापस true;

पूर्ण
EXPORT_SYMBOL(__list_del_entry_valid);
