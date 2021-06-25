<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * multiorder.c: Multi-order radix tree entry testing
 * Copyright (c) 2016 Intel Corporation
 * Author: Ross Zwisler <ross.zwisler@linux.पूर्णांकel.com>
 * Author: Matthew Wilcox <matthew.r.wilcox@पूर्णांकel.com>
 */
#समावेश <linux/radix-tree.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <pthपढ़ो.h>

#समावेश "test.h"

अटल पूर्णांक item_insert_order(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
			अचिन्हित order)
अणु
	XA_STATE_ORDER(xas, xa, index, order);
	काष्ठा item *item = item_create(index, order);

	करो अणु
		xas_lock(&xas);
		xas_store(&xas, item);
		xas_unlock(&xas);
	पूर्ण जबतक (xas_nomem(&xas, GFP_KERNEL));

	अगर (!xas_error(&xas))
		वापस 0;

	मुक्त(item);
	वापस xas_error(&xas);
पूर्ण

व्योम multiorder_iteration(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	काष्ठा item *item;
	पूर्णांक i, j, err;

#घोषणा NUM_ENTRIES 11
	पूर्णांक index[NUM_ENTRIES] = अणु0, 2, 4, 8, 16, 32, 34, 36, 64, 72, 128पूर्ण;
	पूर्णांक order[NUM_ENTRIES] = अणु1, 1, 2, 3,  4,  1,  0,  1,  3,  0, 7पूर्ण;

	prपूर्णांकv(1, "Multiorder iteration test\n");

	क्रम (i = 0; i < NUM_ENTRIES; i++) अणु
		err = item_insert_order(xa, index[i], order[i]);
		निश्चित(!err);
	पूर्ण

	क्रम (j = 0; j < 256; j++) अणु
		क्रम (i = 0; i < NUM_ENTRIES; i++)
			अगर (j <= (index[i] | ((1 << order[i]) - 1)))
				अवरोध;

		xas_set(&xas, j);
		xas_क्रम_each(&xas, item, अच_दीर्घ_उच्च) अणु
			पूर्णांक height = order[i] / XA_CHUNK_SHIFT;
			पूर्णांक shअगरt = height * XA_CHUNK_SHIFT;
			अचिन्हित दीर्घ mask = (1UL << order[i]) - 1;

			निश्चित((xas.xa_index | mask) == (index[i] | mask));
			निश्चित(xas.xa_node->shअगरt == shअगरt);
			निश्चित(!radix_tree_is_पूर्णांकernal_node(item));
			निश्चित((item->index | mask) == (index[i] | mask));
			निश्चित(item->order == order[i]);
			i++;
		पूर्ण
	पूर्ण

	item_समाप्त_tree(xa);
पूर्ण

व्योम multiorder_tagged_iteration(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	काष्ठा item *item;
	पूर्णांक i, j;

#घोषणा MT_NUM_ENTRIES 9
	पूर्णांक index[MT_NUM_ENTRIES] = अणु0, 2, 4, 16, 32, 40, 64, 72, 128पूर्ण;
	पूर्णांक order[MT_NUM_ENTRIES] = अणु1, 0, 2, 4,  3,  1,  3,  0,   7पूर्ण;

#घोषणा TAG_ENTRIES 7
	पूर्णांक tag_index[TAG_ENTRIES] = अणु0, 4, 16, 40, 64, 72, 128पूर्ण;

	prपूर्णांकv(1, "Multiorder tagged iteration test\n");

	क्रम (i = 0; i < MT_NUM_ENTRIES; i++)
		निश्चित(!item_insert_order(xa, index[i], order[i]));

	निश्चित(!xa_marked(xa, XA_MARK_1));

	क्रम (i = 0; i < TAG_ENTRIES; i++)
		xa_set_mark(xa, tag_index[i], XA_MARK_1);

	क्रम (j = 0; j < 256; j++) अणु
		पूर्णांक k;

		क्रम (i = 0; i < TAG_ENTRIES; i++) अणु
			क्रम (k = i; index[k] < tag_index[i]; k++)
				;
			अगर (j <= (index[k] | ((1 << order[k]) - 1)))
				अवरोध;
		पूर्ण

		xas_set(&xas, j);
		xas_क्रम_each_marked(&xas, item, अच_दीर्घ_उच्च, XA_MARK_1) अणु
			अचिन्हित दीर्घ mask;
			क्रम (k = i; index[k] < tag_index[i]; k++)
				;
			mask = (1UL << order[k]) - 1;

			निश्चित((xas.xa_index | mask) == (tag_index[i] | mask));
			निश्चित(!xa_is_पूर्णांकernal(item));
			निश्चित((item->index | mask) == (tag_index[i] | mask));
			निश्चित(item->order == order[k]);
			i++;
		पूर्ण
	पूर्ण

	निश्चित(tag_tagged_items(xa, 0, अच_दीर्घ_उच्च, TAG_ENTRIES, XA_MARK_1,
				XA_MARK_2) == TAG_ENTRIES);

	क्रम (j = 0; j < 256; j++) अणु
		पूर्णांक mask, k;

		क्रम (i = 0; i < TAG_ENTRIES; i++) अणु
			क्रम (k = i; index[k] < tag_index[i]; k++)
				;
			अगर (j <= (index[k] | ((1 << order[k]) - 1)))
				अवरोध;
		पूर्ण

		xas_set(&xas, j);
		xas_क्रम_each_marked(&xas, item, अच_दीर्घ_उच्च, XA_MARK_2) अणु
			क्रम (k = i; index[k] < tag_index[i]; k++)
				;
			mask = (1 << order[k]) - 1;

			निश्चित((xas.xa_index | mask) == (tag_index[i] | mask));
			निश्चित(!xa_is_पूर्णांकernal(item));
			निश्चित((item->index | mask) == (tag_index[i] | mask));
			निश्चित(item->order == order[k]);
			i++;
		पूर्ण
	पूर्ण

	निश्चित(tag_tagged_items(xa, 1, अच_दीर्घ_उच्च, MT_NUM_ENTRIES * 2, XA_MARK_1,
				XA_MARK_0) == TAG_ENTRIES);
	i = 0;
	xas_set(&xas, 0);
	xas_क्रम_each_marked(&xas, item, अच_दीर्घ_उच्च, XA_MARK_0) अणु
		निश्चित(xas.xa_index == tag_index[i]);
		i++;
	पूर्ण
	निश्चित(i == TAG_ENTRIES);

	item_समाप्त_tree(xa);
पूर्ण

bool stop_iteration = false;

अटल व्योम *creator_func(व्योम *ptr)
अणु
	/* 'order' is set up to ensure we have sibling entries */
	अचिन्हित पूर्णांक order = RADIX_TREE_MAP_SHIFT - 1;
	काष्ठा radix_tree_root *tree = ptr;
	पूर्णांक i;

	क्रम (i = 0; i < 10000; i++) अणु
		item_insert_order(tree, 0, order);
		item_delete_rcu(tree, 0);
	पूर्ण

	stop_iteration = true;
	वापस शून्य;
पूर्ण

अटल व्योम *iterator_func(व्योम *ptr)
अणु
	XA_STATE(xas, ptr, 0);
	काष्ठा item *item;

	जबतक (!stop_iteration) अणु
		rcu_पढ़ो_lock();
		xas_क्रम_each(&xas, item, अच_दीर्घ_उच्च) अणु
			अगर (xas_retry(&xas, item))
				जारी;

			item_sanity(item, xas.xa_index);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम multiorder_iteration_race(काष्ठा xarray *xa)
अणु
	स्थिर पूर्णांक num_thपढ़ोs = sysconf(_SC_NPROCESSORS_ONLN);
	pthपढ़ो_t worker_thपढ़ो[num_thपढ़ोs];
	पूर्णांक i;

	pthपढ़ो_create(&worker_thपढ़ो[0], शून्य, &creator_func, xa);
	क्रम (i = 1; i < num_thपढ़ोs; i++)
		pthपढ़ो_create(&worker_thपढ़ो[i], शून्य, &iterator_func, xa);

	क्रम (i = 0; i < num_thपढ़ोs; i++)
		pthपढ़ो_join(worker_thपढ़ो[i], शून्य);

	item_समाप्त_tree(xa);
पूर्ण

अटल DEFINE_XARRAY(array);

व्योम multiorder_checks(व्योम)
अणु
	multiorder_iteration(&array);
	multiorder_tagged_iteration(&array);
	multiorder_iteration_race(&array);

	radix_tree_cpu_dead(0);
पूर्ण

पूर्णांक __weak मुख्य(व्योम)
अणु
	rcu_रेजिस्टर_thपढ़ो();
	radix_tree_init();
	multiorder_checks();
	rcu_unरेजिस्टर_thपढ़ो();
	वापस 0;
पूर्ण
