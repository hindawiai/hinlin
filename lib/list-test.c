<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KUnit test क्रम the Kernel Linked-list काष्ठाures.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: David Gow <davidgow@google.com>
 */
#समावेश <kunit/test.h>

#समावेश <linux/list.h>

काष्ठा list_test_काष्ठा अणु
	पूर्णांक data;
	काष्ठा list_head list;
पूर्ण;

अटल व्योम list_test_list_init(काष्ठा kunit *test)
अणु
	/* Test the dअगरferent ways of initialising a list. */
	काष्ठा list_head list1 = LIST_HEAD_INIT(list1);
	काष्ठा list_head list2;
	LIST_HEAD(list3);
	काष्ठा list_head *list4;
	काष्ठा list_head *list5;

	INIT_LIST_HEAD(&list2);

	list4 = kzalloc(माप(*list4), GFP_KERNEL | __GFP_NOFAIL);
	INIT_LIST_HEAD(list4);

	list5 = kदो_स्मृति(माप(*list5), GFP_KERNEL | __GFP_NOFAIL);
	स_रखो(list5, 0xFF, माप(*list5));
	INIT_LIST_HEAD(list5);

	/* list_empty_careful() checks both next and prev. */
	KUNIT_EXPECT_TRUE(test, list_empty_careful(&list1));
	KUNIT_EXPECT_TRUE(test, list_empty_careful(&list2));
	KUNIT_EXPECT_TRUE(test, list_empty_careful(&list3));
	KUNIT_EXPECT_TRUE(test, list_empty_careful(list4));
	KUNIT_EXPECT_TRUE(test, list_empty_careful(list5));

	kमुक्त(list4);
	kमुक्त(list5);
पूर्ण

अटल व्योम list_test_list_add(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	list_add(&a, &list);
	list_add(&b, &list);

	/* should be [list] -> b -> a */
	KUNIT_EXPECT_PTR_EQ(test, list.next, &b);
	KUNIT_EXPECT_PTR_EQ(test, b.prev, &list);
	KUNIT_EXPECT_PTR_EQ(test, b.next, &a);
पूर्ण

अटल व्योम list_test_list_add_tail(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	list_add_tail(&a, &list);
	list_add_tail(&b, &list);

	/* should be [list] -> a -> b */
	KUNIT_EXPECT_PTR_EQ(test, list.next, &a);
	KUNIT_EXPECT_PTR_EQ(test, a.prev, &list);
	KUNIT_EXPECT_PTR_EQ(test, a.next, &b);
पूर्ण

अटल व्योम list_test_list_del(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	list_add_tail(&a, &list);
	list_add_tail(&b, &list);

	/* beक्रमe: [list] -> a -> b */
	list_del(&a);

	/* now: [list] -> b */
	KUNIT_EXPECT_PTR_EQ(test, list.next, &b);
	KUNIT_EXPECT_PTR_EQ(test, b.prev, &list);
पूर्ण

अटल व्योम list_test_list_replace(काष्ठा kunit *test)
अणु
	काष्ठा list_head a_old, a_new, b;
	LIST_HEAD(list);

	list_add_tail(&a_old, &list);
	list_add_tail(&b, &list);

	/* beक्रमe: [list] -> a_old -> b */
	list_replace(&a_old, &a_new);

	/* now: [list] -> a_new -> b */
	KUNIT_EXPECT_PTR_EQ(test, list.next, &a_new);
	KUNIT_EXPECT_PTR_EQ(test, b.prev, &a_new);
पूर्ण

अटल व्योम list_test_list_replace_init(काष्ठा kunit *test)
अणु
	काष्ठा list_head a_old, a_new, b;
	LIST_HEAD(list);

	list_add_tail(&a_old, &list);
	list_add_tail(&b, &list);

	/* beक्रमe: [list] -> a_old -> b */
	list_replace_init(&a_old, &a_new);

	/* now: [list] -> a_new -> b */
	KUNIT_EXPECT_PTR_EQ(test, list.next, &a_new);
	KUNIT_EXPECT_PTR_EQ(test, b.prev, &a_new);

	/* check a_old is empty (initialized) */
	KUNIT_EXPECT_TRUE(test, list_empty_careful(&a_old));
पूर्ण

अटल व्योम list_test_list_swap(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	list_add_tail(&a, &list);
	list_add_tail(&b, &list);

	/* beक्रमe: [list] -> a -> b */
	list_swap(&a, &b);

	/* after: [list] -> b -> a */
	KUNIT_EXPECT_PTR_EQ(test, &b, list.next);
	KUNIT_EXPECT_PTR_EQ(test, &a, list.prev);

	KUNIT_EXPECT_PTR_EQ(test, &a, b.next);
	KUNIT_EXPECT_PTR_EQ(test, &list, b.prev);

	KUNIT_EXPECT_PTR_EQ(test, &list, a.next);
	KUNIT_EXPECT_PTR_EQ(test, &b, a.prev);
पूर्ण

अटल व्योम list_test_list_del_init(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	list_add_tail(&a, &list);
	list_add_tail(&b, &list);

	/* beक्रमe: [list] -> a -> b */
	list_del_init(&a);
	/* after: [list] -> b, a initialised */

	KUNIT_EXPECT_PTR_EQ(test, list.next, &b);
	KUNIT_EXPECT_PTR_EQ(test, b.prev, &list);
	KUNIT_EXPECT_TRUE(test, list_empty_careful(&a));
पूर्ण

अटल व्योम list_test_list_move(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list1);
	LIST_HEAD(list2);

	list_add_tail(&a, &list1);
	list_add_tail(&b, &list2);

	/* beक्रमe: [list1] -> a, [list2] -> b */
	list_move(&a, &list2);
	/* after: [list1] empty, [list2] -> a -> b */

	KUNIT_EXPECT_TRUE(test, list_empty(&list1));

	KUNIT_EXPECT_PTR_EQ(test, &a, list2.next);
	KUNIT_EXPECT_PTR_EQ(test, &b, a.next);
पूर्ण

अटल व्योम list_test_list_move_tail(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list1);
	LIST_HEAD(list2);

	list_add_tail(&a, &list1);
	list_add_tail(&b, &list2);

	/* beक्रमe: [list1] -> a, [list2] -> b */
	list_move_tail(&a, &list2);
	/* after: [list1] empty, [list2] -> b -> a */

	KUNIT_EXPECT_TRUE(test, list_empty(&list1));

	KUNIT_EXPECT_PTR_EQ(test, &b, list2.next);
	KUNIT_EXPECT_PTR_EQ(test, &a, b.next);
पूर्ण

अटल व्योम list_test_list_bulk_move_tail(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b, c, d, x, y;
	काष्ठा list_head *list1_values[] = अणु &x, &b, &c, &y पूर्ण;
	काष्ठा list_head *list2_values[] = अणु &a, &d पूर्ण;
	काष्ठा list_head *ptr;
	LIST_HEAD(list1);
	LIST_HEAD(list2);
	पूर्णांक i = 0;

	list_add_tail(&x, &list1);
	list_add_tail(&y, &list1);

	list_add_tail(&a, &list2);
	list_add_tail(&b, &list2);
	list_add_tail(&c, &list2);
	list_add_tail(&d, &list2);

	/* beक्रमe: [list1] -> x -> y, [list2] -> a -> b -> c -> d */
	list_bulk_move_tail(&y, &b, &c);
	/* after: [list1] -> x -> b -> c -> y, [list2] -> a -> d */

	list_क्रम_each(ptr, &list1) अणु
		KUNIT_EXPECT_PTR_EQ(test, ptr, list1_values[i]);
		i++;
	पूर्ण
	KUNIT_EXPECT_EQ(test, i, 4);
	i = 0;
	list_क्रम_each(ptr, &list2) अणु
		KUNIT_EXPECT_PTR_EQ(test, ptr, list2_values[i]);
		i++;
	पूर्ण
	KUNIT_EXPECT_EQ(test, i, 2);
पूर्ण

अटल व्योम list_test_list_is_first(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	list_add_tail(&a, &list);
	list_add_tail(&b, &list);

	KUNIT_EXPECT_TRUE(test, list_is_first(&a, &list));
	KUNIT_EXPECT_FALSE(test, list_is_first(&b, &list));
पूर्ण

अटल व्योम list_test_list_is_last(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	list_add_tail(&a, &list);
	list_add_tail(&b, &list);

	KUNIT_EXPECT_FALSE(test, list_is_last(&a, &list));
	KUNIT_EXPECT_TRUE(test, list_is_last(&b, &list));
पूर्ण

अटल व्योम list_test_list_empty(काष्ठा kunit *test)
अणु
	काष्ठा list_head a;
	LIST_HEAD(list1);
	LIST_HEAD(list2);

	list_add_tail(&a, &list1);

	KUNIT_EXPECT_FALSE(test, list_empty(&list1));
	KUNIT_EXPECT_TRUE(test, list_empty(&list2));
पूर्ण

अटल व्योम list_test_list_empty_careful(काष्ठा kunit *test)
अणु
	/* This test करोesn't check correctness under concurrent access */
	काष्ठा list_head a;
	LIST_HEAD(list1);
	LIST_HEAD(list2);

	list_add_tail(&a, &list1);

	KUNIT_EXPECT_FALSE(test, list_empty_careful(&list1));
	KUNIT_EXPECT_TRUE(test, list_empty_careful(&list2));
पूर्ण

अटल व्योम list_test_list_rotate_left(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	list_add_tail(&a, &list);
	list_add_tail(&b, &list);

	/* beक्रमe: [list] -> a -> b */
	list_rotate_left(&list);
	/* after: [list] -> b -> a */

	KUNIT_EXPECT_PTR_EQ(test, list.next, &b);
	KUNIT_EXPECT_PTR_EQ(test, b.prev, &list);
	KUNIT_EXPECT_PTR_EQ(test, b.next, &a);
पूर्ण

अटल व्योम list_test_list_rotate_to_front(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b, c, d;
	काष्ठा list_head *list_values[] = अणु &c, &d, &a, &b पूर्ण;
	काष्ठा list_head *ptr;
	LIST_HEAD(list);
	पूर्णांक i = 0;

	list_add_tail(&a, &list);
	list_add_tail(&b, &list);
	list_add_tail(&c, &list);
	list_add_tail(&d, &list);

	/* beक्रमe: [list] -> a -> b -> c -> d */
	list_rotate_to_front(&c, &list);
	/* after: [list] -> c -> d -> a -> b */

	list_क्रम_each(ptr, &list) अणु
		KUNIT_EXPECT_PTR_EQ(test, ptr, list_values[i]);
		i++;
	पूर्ण
	KUNIT_EXPECT_EQ(test, i, 4);
पूर्ण

अटल व्योम list_test_list_is_singular(काष्ठा kunit *test)
अणु
	काष्ठा list_head a, b;
	LIST_HEAD(list);

	/* [list] empty */
	KUNIT_EXPECT_FALSE(test, list_is_singular(&list));

	list_add_tail(&a, &list);

	/* [list] -> a */
	KUNIT_EXPECT_TRUE(test, list_is_singular(&list));

	list_add_tail(&b, &list);

	/* [list] -> a -> b */
	KUNIT_EXPECT_FALSE(test, list_is_singular(&list));
पूर्ण

अटल व्योम list_test_list_cut_position(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[3], *cur;
	LIST_HEAD(list1);
	LIST_HEAD(list2);
	पूर्णांक i = 0;

	list_add_tail(&entries[0], &list1);
	list_add_tail(&entries[1], &list1);
	list_add_tail(&entries[2], &list1);

	/* beक्रमe: [list1] -> entries[0] -> entries[1] -> entries[2] */
	list_cut_position(&list2, &list1, &entries[1]);
	/* after: [list2] -> entries[0] -> entries[1], [list1] -> entries[2] */

	list_क्रम_each(cur, &list2) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 2);

	list_क्रम_each(cur, &list1) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण
पूर्ण

अटल व्योम list_test_list_cut_beक्रमe(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[3], *cur;
	LIST_HEAD(list1);
	LIST_HEAD(list2);
	पूर्णांक i = 0;

	list_add_tail(&entries[0], &list1);
	list_add_tail(&entries[1], &list1);
	list_add_tail(&entries[2], &list1);

	/* beक्रमe: [list1] -> entries[0] -> entries[1] -> entries[2] */
	list_cut_beक्रमe(&list2, &list1, &entries[1]);
	/* after: [list2] -> entries[0], [list1] -> entries[1] -> entries[2] */

	list_क्रम_each(cur, &list2) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 1);

	list_क्रम_each(cur, &list1) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण
पूर्ण

अटल व्योम list_test_list_splice(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[5], *cur;
	LIST_HEAD(list1);
	LIST_HEAD(list2);
	पूर्णांक i = 0;

	list_add_tail(&entries[0], &list1);
	list_add_tail(&entries[1], &list1);
	list_add_tail(&entries[2], &list2);
	list_add_tail(&entries[3], &list2);
	list_add_tail(&entries[4], &list1);

	/* beक्रमe: [list1]->e[0]->e[1]->e[4], [list2]->e[2]->e[3] */
	list_splice(&list2, &entries[1]);
	/* after: [list1]->e[0]->e[1]->e[2]->e[3]->e[4], [list2] uninit */

	list_क्रम_each(cur, &list1) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 5);
पूर्ण

अटल व्योम list_test_list_splice_tail(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[5], *cur;
	LIST_HEAD(list1);
	LIST_HEAD(list2);
	पूर्णांक i = 0;

	list_add_tail(&entries[0], &list1);
	list_add_tail(&entries[1], &list1);
	list_add_tail(&entries[2], &list2);
	list_add_tail(&entries[3], &list2);
	list_add_tail(&entries[4], &list1);

	/* beक्रमe: [list1]->e[0]->e[1]->e[4], [list2]->e[2]->e[3] */
	list_splice_tail(&list2, &entries[4]);
	/* after: [list1]->e[0]->e[1]->e[2]->e[3]->e[4], [list2] uninit */

	list_क्रम_each(cur, &list1) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 5);
पूर्ण

अटल व्योम list_test_list_splice_init(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[5], *cur;
	LIST_HEAD(list1);
	LIST_HEAD(list2);
	पूर्णांक i = 0;

	list_add_tail(&entries[0], &list1);
	list_add_tail(&entries[1], &list1);
	list_add_tail(&entries[2], &list2);
	list_add_tail(&entries[3], &list2);
	list_add_tail(&entries[4], &list1);

	/* beक्रमe: [list1]->e[0]->e[1]->e[4], [list2]->e[2]->e[3] */
	list_splice_init(&list2, &entries[1]);
	/* after: [list1]->e[0]->e[1]->e[2]->e[3]->e[4], [list2] empty */

	list_क्रम_each(cur, &list1) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 5);

	KUNIT_EXPECT_TRUE(test, list_empty_careful(&list2));
पूर्ण

अटल व्योम list_test_list_splice_tail_init(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[5], *cur;
	LIST_HEAD(list1);
	LIST_HEAD(list2);
	पूर्णांक i = 0;

	list_add_tail(&entries[0], &list1);
	list_add_tail(&entries[1], &list1);
	list_add_tail(&entries[2], &list2);
	list_add_tail(&entries[3], &list2);
	list_add_tail(&entries[4], &list1);

	/* beक्रमe: [list1]->e[0]->e[1]->e[4], [list2]->e[2]->e[3] */
	list_splice_tail_init(&list2, &entries[4]);
	/* after: [list1]->e[0]->e[1]->e[2]->e[3]->e[4], [list2] empty */

	list_क्रम_each(cur, &list1) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 5);

	KUNIT_EXPECT_TRUE(test, list_empty_careful(&list2));
पूर्ण

अटल व्योम list_test_list_entry(काष्ठा kunit *test)
अणु
	काष्ठा list_test_काष्ठा test_काष्ठा;

	KUNIT_EXPECT_PTR_EQ(test, &test_काष्ठा, list_entry(&(test_काष्ठा.list),
				काष्ठा list_test_काष्ठा, list));
पूर्ण

अटल व्योम list_test_list_first_entry(काष्ठा kunit *test)
अणु
	काष्ठा list_test_काष्ठा test_काष्ठा1, test_काष्ठा2;
	LIST_HEAD(list);

	list_add_tail(&test_काष्ठा1.list, &list);
	list_add_tail(&test_काष्ठा2.list, &list);


	KUNIT_EXPECT_PTR_EQ(test, &test_काष्ठा1, list_first_entry(&list,
				काष्ठा list_test_काष्ठा, list));
पूर्ण

अटल व्योम list_test_list_last_entry(काष्ठा kunit *test)
अणु
	काष्ठा list_test_काष्ठा test_काष्ठा1, test_काष्ठा2;
	LIST_HEAD(list);

	list_add_tail(&test_काष्ठा1.list, &list);
	list_add_tail(&test_काष्ठा2.list, &list);


	KUNIT_EXPECT_PTR_EQ(test, &test_काष्ठा2, list_last_entry(&list,
				काष्ठा list_test_काष्ठा, list));
पूर्ण

अटल व्योम list_test_list_first_entry_or_null(काष्ठा kunit *test)
अणु
	काष्ठा list_test_काष्ठा test_काष्ठा1, test_काष्ठा2;
	LIST_HEAD(list);

	KUNIT_EXPECT_FALSE(test, list_first_entry_or_null(&list,
				काष्ठा list_test_काष्ठा, list));

	list_add_tail(&test_काष्ठा1.list, &list);
	list_add_tail(&test_काष्ठा2.list, &list);

	KUNIT_EXPECT_PTR_EQ(test, &test_काष्ठा1,
			list_first_entry_or_null(&list,
				काष्ठा list_test_काष्ठा, list));
पूर्ण

अटल व्योम list_test_list_next_entry(काष्ठा kunit *test)
अणु
	काष्ठा list_test_काष्ठा test_काष्ठा1, test_काष्ठा2;
	LIST_HEAD(list);

	list_add_tail(&test_काष्ठा1.list, &list);
	list_add_tail(&test_काष्ठा2.list, &list);


	KUNIT_EXPECT_PTR_EQ(test, &test_काष्ठा2, list_next_entry(&test_काष्ठा1,
				list));
पूर्ण

अटल व्योम list_test_list_prev_entry(काष्ठा kunit *test)
अणु
	काष्ठा list_test_काष्ठा test_काष्ठा1, test_काष्ठा2;
	LIST_HEAD(list);

	list_add_tail(&test_काष्ठा1.list, &list);
	list_add_tail(&test_काष्ठा2.list, &list);


	KUNIT_EXPECT_PTR_EQ(test, &test_काष्ठा1, list_prev_entry(&test_काष्ठा2,
				list));
पूर्ण

अटल व्योम list_test_list_क्रम_each(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[3], *cur;
	LIST_HEAD(list);
	पूर्णांक i = 0;

	list_add_tail(&entries[0], &list);
	list_add_tail(&entries[1], &list);
	list_add_tail(&entries[2], &list);

	list_क्रम_each(cur, &list) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 3);
पूर्ण

अटल व्योम list_test_list_क्रम_each_prev(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[3], *cur;
	LIST_HEAD(list);
	पूर्णांक i = 2;

	list_add_tail(&entries[0], &list);
	list_add_tail(&entries[1], &list);
	list_add_tail(&entries[2], &list);

	list_क्रम_each_prev(cur, &list) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		i--;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, -1);
पूर्ण

अटल व्योम list_test_list_क्रम_each_safe(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[3], *cur, *n;
	LIST_HEAD(list);
	पूर्णांक i = 0;


	list_add_tail(&entries[0], &list);
	list_add_tail(&entries[1], &list);
	list_add_tail(&entries[2], &list);

	list_क्रम_each_safe(cur, n, &list) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		list_del(&entries[i]);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 3);
	KUNIT_EXPECT_TRUE(test, list_empty(&list));
पूर्ण

अटल व्योम list_test_list_क्रम_each_prev_safe(काष्ठा kunit *test)
अणु
	काष्ठा list_head entries[3], *cur, *n;
	LIST_HEAD(list);
	पूर्णांक i = 2;

	list_add_tail(&entries[0], &list);
	list_add_tail(&entries[1], &list);
	list_add_tail(&entries[2], &list);

	list_क्रम_each_prev_safe(cur, n, &list) अणु
		KUNIT_EXPECT_PTR_EQ(test, cur, &entries[i]);
		list_del(&entries[i]);
		i--;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, -1);
	KUNIT_EXPECT_TRUE(test, list_empty(&list));
पूर्ण

अटल व्योम list_test_list_क्रम_each_entry(काष्ठा kunit *test)
अणु
	काष्ठा list_test_काष्ठा entries[5], *cur;
	LIST_HEAD(list);
	पूर्णांक i = 0;

	क्रम (i = 0; i < 5; ++i) अणु
		entries[i].data = i;
		list_add_tail(&entries[i].list, &list);
	पूर्ण

	i = 0;

	list_क्रम_each_entry(cur, &list, list) अणु
		KUNIT_EXPECT_EQ(test, cur->data, i);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, 5);
पूर्ण

अटल व्योम list_test_list_क्रम_each_entry_reverse(काष्ठा kunit *test)
अणु
	काष्ठा list_test_काष्ठा entries[5], *cur;
	LIST_HEAD(list);
	पूर्णांक i = 0;

	क्रम (i = 0; i < 5; ++i) अणु
		entries[i].data = i;
		list_add_tail(&entries[i].list, &list);
	पूर्ण

	i = 4;

	list_क्रम_each_entry_reverse(cur, &list, list) अणु
		KUNIT_EXPECT_EQ(test, cur->data, i);
		i--;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, -1);
पूर्ण

अटल काष्ठा kunit_हाल list_test_हालs[] = अणु
	KUNIT_CASE(list_test_list_init),
	KUNIT_CASE(list_test_list_add),
	KUNIT_CASE(list_test_list_add_tail),
	KUNIT_CASE(list_test_list_del),
	KUNIT_CASE(list_test_list_replace),
	KUNIT_CASE(list_test_list_replace_init),
	KUNIT_CASE(list_test_list_swap),
	KUNIT_CASE(list_test_list_del_init),
	KUNIT_CASE(list_test_list_move),
	KUNIT_CASE(list_test_list_move_tail),
	KUNIT_CASE(list_test_list_bulk_move_tail),
	KUNIT_CASE(list_test_list_is_first),
	KUNIT_CASE(list_test_list_is_last),
	KUNIT_CASE(list_test_list_empty),
	KUNIT_CASE(list_test_list_empty_careful),
	KUNIT_CASE(list_test_list_rotate_left),
	KUNIT_CASE(list_test_list_rotate_to_front),
	KUNIT_CASE(list_test_list_is_singular),
	KUNIT_CASE(list_test_list_cut_position),
	KUNIT_CASE(list_test_list_cut_beक्रमe),
	KUNIT_CASE(list_test_list_splice),
	KUNIT_CASE(list_test_list_splice_tail),
	KUNIT_CASE(list_test_list_splice_init),
	KUNIT_CASE(list_test_list_splice_tail_init),
	KUNIT_CASE(list_test_list_entry),
	KUNIT_CASE(list_test_list_first_entry),
	KUNIT_CASE(list_test_list_last_entry),
	KUNIT_CASE(list_test_list_first_entry_or_null),
	KUNIT_CASE(list_test_list_next_entry),
	KUNIT_CASE(list_test_list_prev_entry),
	KUNIT_CASE(list_test_list_क्रम_each),
	KUNIT_CASE(list_test_list_क्रम_each_prev),
	KUNIT_CASE(list_test_list_क्रम_each_safe),
	KUNIT_CASE(list_test_list_क्रम_each_prev_safe),
	KUNIT_CASE(list_test_list_क्रम_each_entry),
	KUNIT_CASE(list_test_list_क्रम_each_entry_reverse),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा kunit_suite list_test_module = अणु
	.name = "list-kunit-test",
	.test_हालs = list_test_हालs,
पूर्ण;

kunit_test_suites(&list_test_module);

MODULE_LICENSE("GPL v2");
