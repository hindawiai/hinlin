<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * test_xarray.c: Test the XArray API
 * Copyright (c) 2017-2018 Microsoft Corporation
 * Copyright (c) 2019-2020 Oracle
 * Author: Matthew Wilcox <willy@infradead.org>
 */

#समावेश <linux/xarray.h>
#समावेश <linux/module.h>

अटल अचिन्हित पूर्णांक tests_run;
अटल अचिन्हित पूर्णांक tests_passed;

अटल स्थिर अचिन्हित पूर्णांक order_limit =
		IS_ENABLED(CONFIG_XARRAY_MULTI) ? BITS_PER_LONG : 1;

#अगर_अघोषित XA_DEBUG
# अगरdef __KERNEL__
व्योम xa_dump(स्थिर काष्ठा xarray *xa) अणु पूर्ण
# endअगर
#अघोषित XA_BUG_ON
#घोषणा XA_BUG_ON(xa, x) करो अणु					\
	tests_run++;						\
	अगर (x) अणु						\
		prपूर्णांकk("BUG at %s:%d\n", __func__, __LINE__);	\
		xa_dump(xa);					\
		dump_stack();					\
	पूर्ण अन्यथा अणु						\
		tests_passed++;					\
	पूर्ण							\
पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम *xa_mk_index(अचिन्हित दीर्घ index)
अणु
	वापस xa_mk_value(index & दीर्घ_उच्च);
पूर्ण

अटल व्योम *xa_store_index(काष्ठा xarray *xa, अचिन्हित दीर्घ index, gfp_t gfp)
अणु
	वापस xa_store(xa, index, xa_mk_index(index), gfp);
पूर्ण

अटल व्योम xa_insert_index(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	XA_BUG_ON(xa, xa_insert(xa, index, xa_mk_index(index),
				GFP_KERNEL) != 0);
पूर्ण

अटल व्योम xa_alloc_index(काष्ठा xarray *xa, अचिन्हित दीर्घ index, gfp_t gfp)
अणु
	u32 id;

	XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_index(index), xa_limit_32b,
				gfp) != 0);
	XA_BUG_ON(xa, id != index);
पूर्ण

अटल व्योम xa_erase_index(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	XA_BUG_ON(xa, xa_erase(xa, index) != xa_mk_index(index));
	XA_BUG_ON(xa, xa_load(xa, index) != शून्य);
पूर्ण

/*
 * If anyone needs this, please move it to xarray.c.  We have no current
 * users outside the test suite because all current multislot users want
 * to use the advanced API.
 */
अटल व्योम *xa_store_order(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
		अचिन्हित order, व्योम *entry, gfp_t gfp)
अणु
	XA_STATE_ORDER(xas, xa, index, order);
	व्योम *curr;

	करो अणु
		xas_lock(&xas);
		curr = xas_store(&xas, entry);
		xas_unlock(&xas);
	पूर्ण जबतक (xas_nomem(&xas, gfp));

	वापस curr;
पूर्ण

अटल noअंतरभूत व्योम check_xa_err(काष्ठा xarray *xa)
अणु
	XA_BUG_ON(xa, xa_err(xa_store_index(xa, 0, GFP_NOWAIT)) != 0);
	XA_BUG_ON(xa, xa_err(xa_erase(xa, 0)) != 0);
#अगर_अघोषित __KERNEL__
	/* The kernel करोes not fail GFP_NOWAIT allocations */
	XA_BUG_ON(xa, xa_err(xa_store_index(xa, 1, GFP_NOWAIT)) != -ENOMEM);
	XA_BUG_ON(xa, xa_err(xa_store_index(xa, 1, GFP_NOWAIT)) != -ENOMEM);
#पूर्ण_अगर
	XA_BUG_ON(xa, xa_err(xa_store_index(xa, 1, GFP_KERNEL)) != 0);
	XA_BUG_ON(xa, xa_err(xa_store(xa, 1, xa_mk_value(0), GFP_KERNEL)) != 0);
	XA_BUG_ON(xa, xa_err(xa_erase(xa, 1)) != 0);
// समाप्तs the test-suite :-(
//	XA_BUG_ON(xa, xa_err(xa_store(xa, 0, xa_mk_पूर्णांकernal(0), 0)) != -EINVAL);
पूर्ण

अटल noअंतरभूत व्योम check_xas_retry(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	व्योम *entry;

	xa_store_index(xa, 0, GFP_KERNEL);
	xa_store_index(xa, 1, GFP_KERNEL);

	rcu_पढ़ो_lock();
	XA_BUG_ON(xa, xas_find(&xas, अच_दीर्घ_उच्च) != xa_mk_value(0));
	xa_erase_index(xa, 1);
	XA_BUG_ON(xa, !xa_is_retry(xas_reload(&xas)));
	XA_BUG_ON(xa, xas_retry(&xas, शून्य));
	XA_BUG_ON(xa, xas_retry(&xas, xa_mk_value(0)));
	xas_reset(&xas);
	XA_BUG_ON(xa, xas.xa_node != XAS_RESTART);
	XA_BUG_ON(xa, xas_next_entry(&xas, अच_दीर्घ_उच्च) != xa_mk_value(0));
	XA_BUG_ON(xa, xas.xa_node != शून्य);
	rcu_पढ़ो_unlock();

	XA_BUG_ON(xa, xa_store_index(xa, 1, GFP_KERNEL) != शून्य);

	rcu_पढ़ो_lock();
	XA_BUG_ON(xa, !xa_is_पूर्णांकernal(xas_reload(&xas)));
	xas.xa_node = XAS_RESTART;
	XA_BUG_ON(xa, xas_next_entry(&xas, अच_दीर्घ_उच्च) != xa_mk_value(0));
	rcu_पढ़ो_unlock();

	/* Make sure we can iterate through retry entries */
	xas_lock(&xas);
	xas_set(&xas, 0);
	xas_store(&xas, XA_RETRY_ENTRY);
	xas_set(&xas, 1);
	xas_store(&xas, XA_RETRY_ENTRY);

	xas_set(&xas, 0);
	xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
		xas_store(&xas, xa_mk_index(xas.xa_index));
	पूर्ण
	xas_unlock(&xas);

	xa_erase_index(xa, 0);
	xa_erase_index(xa, 1);
पूर्ण

अटल noअंतरभूत व्योम check_xa_load(काष्ठा xarray *xa)
अणु
	अचिन्हित दीर्घ i, j;

	क्रम (i = 0; i < 1024; i++) अणु
		क्रम (j = 0; j < 1024; j++) अणु
			व्योम *entry = xa_load(xa, j);
			अगर (j < i)
				XA_BUG_ON(xa, xa_to_value(entry) != j);
			अन्यथा
				XA_BUG_ON(xa, entry);
		पूर्ण
		XA_BUG_ON(xa, xa_store_index(xa, i, GFP_KERNEL) != शून्य);
	पूर्ण

	क्रम (i = 0; i < 1024; i++) अणु
		क्रम (j = 0; j < 1024; j++) अणु
			व्योम *entry = xa_load(xa, j);
			अगर (j >= i)
				XA_BUG_ON(xa, xa_to_value(entry) != j);
			अन्यथा
				XA_BUG_ON(xa, entry);
		पूर्ण
		xa_erase_index(xa, i);
	पूर्ण
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_xa_mark_1(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	अचिन्हित पूर्णांक order;
	अचिन्हित पूर्णांक max_order = IS_ENABLED(CONFIG_XARRAY_MULTI) ? 8 : 1;

	/* शून्य elements have no marks set */
	XA_BUG_ON(xa, xa_get_mark(xa, index, XA_MARK_0));
	xa_set_mark(xa, index, XA_MARK_0);
	XA_BUG_ON(xa, xa_get_mark(xa, index, XA_MARK_0));

	/* Storing a poपूर्णांकer will not make a mark appear */
	XA_BUG_ON(xa, xa_store_index(xa, index, GFP_KERNEL) != शून्य);
	XA_BUG_ON(xa, xa_get_mark(xa, index, XA_MARK_0));
	xa_set_mark(xa, index, XA_MARK_0);
	XA_BUG_ON(xa, !xa_get_mark(xa, index, XA_MARK_0));

	/* Setting one mark will not set another mark */
	XA_BUG_ON(xa, xa_get_mark(xa, index + 1, XA_MARK_0));
	XA_BUG_ON(xa, xa_get_mark(xa, index, XA_MARK_1));

	/* Storing शून्य clears marks, and they can't be set again */
	xa_erase_index(xa, index);
	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_get_mark(xa, index, XA_MARK_0));
	xa_set_mark(xa, index, XA_MARK_0);
	XA_BUG_ON(xa, xa_get_mark(xa, index, XA_MARK_0));

	/*
	 * Storing a multi-index entry over entries with marks gives the
	 * entire entry the जोड़ of the marks
	 */
	BUG_ON((index % 4) != 0);
	क्रम (order = 2; order < max_order; order++) अणु
		अचिन्हित दीर्घ base = round_करोwn(index, 1UL << order);
		अचिन्हित दीर्घ next = base + (1UL << order);
		अचिन्हित दीर्घ i;

		XA_BUG_ON(xa, xa_store_index(xa, index + 1, GFP_KERNEL));
		xa_set_mark(xa, index + 1, XA_MARK_0);
		XA_BUG_ON(xa, xa_store_index(xa, index + 2, GFP_KERNEL));
		xa_set_mark(xa, index + 2, XA_MARK_2);
		XA_BUG_ON(xa, xa_store_index(xa, next, GFP_KERNEL));
		xa_store_order(xa, index, order, xa_mk_index(index),
				GFP_KERNEL);
		क्रम (i = base; i < next; i++) अणु
			XA_STATE(xas, xa, i);
			अचिन्हित पूर्णांक seen = 0;
			व्योम *entry;

			XA_BUG_ON(xa, !xa_get_mark(xa, i, XA_MARK_0));
			XA_BUG_ON(xa, xa_get_mark(xa, i, XA_MARK_1));
			XA_BUG_ON(xa, !xa_get_mark(xa, i, XA_MARK_2));

			/* We should see two elements in the array */
			rcu_पढ़ो_lock();
			xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च)
				seen++;
			rcu_पढ़ो_unlock();
			XA_BUG_ON(xa, seen != 2);

			/* One of which is marked */
			xas_set(&xas, 0);
			seen = 0;
			rcu_पढ़ो_lock();
			xas_क्रम_each_marked(&xas, entry, अच_दीर्घ_उच्च, XA_MARK_0)
				seen++;
			rcu_पढ़ो_unlock();
			XA_BUG_ON(xa, seen != 1);
		पूर्ण
		XA_BUG_ON(xa, xa_get_mark(xa, next, XA_MARK_0));
		XA_BUG_ON(xa, xa_get_mark(xa, next, XA_MARK_1));
		XA_BUG_ON(xa, xa_get_mark(xa, next, XA_MARK_2));
		xa_erase_index(xa, index);
		xa_erase_index(xa, next);
		XA_BUG_ON(xa, !xa_empty(xa));
	पूर्ण
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_xa_mark_2(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	अचिन्हित दीर्घ index;
	अचिन्हित पूर्णांक count = 0;
	व्योम *entry;

	xa_store_index(xa, 0, GFP_KERNEL);
	xa_set_mark(xa, 0, XA_MARK_0);
	xas_lock(&xas);
	xas_load(&xas);
	xas_init_marks(&xas);
	xas_unlock(&xas);
	XA_BUG_ON(xa, !xa_get_mark(xa, 0, XA_MARK_0) == 0);

	क्रम (index = 3500; index < 4500; index++) अणु
		xa_store_index(xa, index, GFP_KERNEL);
		xa_set_mark(xa, index, XA_MARK_0);
	पूर्ण

	xas_reset(&xas);
	rcu_पढ़ो_lock();
	xas_क्रम_each_marked(&xas, entry, अच_दीर्घ_उच्च, XA_MARK_0)
		count++;
	rcu_पढ़ो_unlock();
	XA_BUG_ON(xa, count != 1000);

	xas_lock(&xas);
	xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
		xas_init_marks(&xas);
		XA_BUG_ON(xa, !xa_get_mark(xa, xas.xa_index, XA_MARK_0));
		XA_BUG_ON(xa, !xas_get_mark(&xas, XA_MARK_0));
	पूर्ण
	xas_unlock(&xas);

	xa_destroy(xa);
पूर्ण

अटल noअंतरभूत व्योम check_xa_mark_3(काष्ठा xarray *xa)
अणु
#अगर_घोषित CONFIG_XARRAY_MULTI
	XA_STATE(xas, xa, 0x41);
	व्योम *entry;
	पूर्णांक count = 0;

	xa_store_order(xa, 0x40, 2, xa_mk_index(0x40), GFP_KERNEL);
	xa_set_mark(xa, 0x41, XA_MARK_0);

	rcu_पढ़ो_lock();
	xas_क्रम_each_marked(&xas, entry, अच_दीर्घ_उच्च, XA_MARK_0) अणु
		count++;
		XA_BUG_ON(xa, entry != xa_mk_index(0x40));
	पूर्ण
	XA_BUG_ON(xa, count != 1);
	rcu_पढ़ो_unlock();
	xa_destroy(xa);
#पूर्ण_अगर
पूर्ण

अटल noअंतरभूत व्योम check_xa_mark(काष्ठा xarray *xa)
अणु
	अचिन्हित दीर्घ index;

	क्रम (index = 0; index < 16384; index += 4)
		check_xa_mark_1(xa, index);

	check_xa_mark_2(xa);
	check_xa_mark_3(xa);
पूर्ण

अटल noअंतरभूत व्योम check_xa_shrink(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 1);
	काष्ठा xa_node *node;
	अचिन्हित पूर्णांक order;
	अचिन्हित पूर्णांक max_order = IS_ENABLED(CONFIG_XARRAY_MULTI) ? 15 : 1;

	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_store_index(xa, 0, GFP_KERNEL) != शून्य);
	XA_BUG_ON(xa, xa_store_index(xa, 1, GFP_KERNEL) != शून्य);

	/*
	 * Check that erasing the entry at 1 shrinks the tree and properly
	 * marks the node as being deleted.
	 */
	xas_lock(&xas);
	XA_BUG_ON(xa, xas_load(&xas) != xa_mk_value(1));
	node = xas.xa_node;
	XA_BUG_ON(xa, xa_entry_locked(xa, node, 0) != xa_mk_value(0));
	XA_BUG_ON(xa, xas_store(&xas, शून्य) != xa_mk_value(1));
	XA_BUG_ON(xa, xa_load(xa, 1) != शून्य);
	XA_BUG_ON(xa, xas.xa_node != XAS_BOUNDS);
	XA_BUG_ON(xa, xa_entry_locked(xa, node, 0) != XA_RETRY_ENTRY);
	XA_BUG_ON(xa, xas_load(&xas) != शून्य);
	xas_unlock(&xas);
	XA_BUG_ON(xa, xa_load(xa, 0) != xa_mk_value(0));
	xa_erase_index(xa, 0);
	XA_BUG_ON(xa, !xa_empty(xa));

	क्रम (order = 0; order < max_order; order++) अणु
		अचिन्हित दीर्घ max = (1UL << order) - 1;
		xa_store_order(xa, 0, order, xa_mk_value(0), GFP_KERNEL);
		XA_BUG_ON(xa, xa_load(xa, max) != xa_mk_value(0));
		XA_BUG_ON(xa, xa_load(xa, max + 1) != शून्य);
		rcu_पढ़ो_lock();
		node = xa_head(xa);
		rcu_पढ़ो_unlock();
		XA_BUG_ON(xa, xa_store_index(xa, अच_दीर्घ_उच्च, GFP_KERNEL) !=
				शून्य);
		rcu_पढ़ो_lock();
		XA_BUG_ON(xa, xa_head(xa) == node);
		rcu_पढ़ो_unlock();
		XA_BUG_ON(xa, xa_load(xa, max + 1) != शून्य);
		xa_erase_index(xa, अच_दीर्घ_उच्च);
		XA_BUG_ON(xa, xa->xa_head != node);
		xa_erase_index(xa, 0);
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम check_insert(काष्ठा xarray *xa)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < 1024; i++) अणु
		xa_insert_index(xa, i);
		XA_BUG_ON(xa, xa_load(xa, i - 1) != शून्य);
		XA_BUG_ON(xa, xa_load(xa, i + 1) != शून्य);
		xa_erase_index(xa, i);
	पूर्ण

	क्रम (i = 10; i < BITS_PER_LONG; i++) अणु
		xa_insert_index(xa, 1UL << i);
		XA_BUG_ON(xa, xa_load(xa, (1UL << i) - 1) != शून्य);
		XA_BUG_ON(xa, xa_load(xa, (1UL << i) + 1) != शून्य);
		xa_erase_index(xa, 1UL << i);

		xa_insert_index(xa, (1UL << i) - 1);
		XA_BUG_ON(xa, xa_load(xa, (1UL << i) - 2) != शून्य);
		XA_BUG_ON(xa, xa_load(xa, 1UL << i) != शून्य);
		xa_erase_index(xa, (1UL << i) - 1);
	पूर्ण

	xa_insert_index(xa, ~0UL);
	XA_BUG_ON(xa, xa_load(xa, 0UL) != शून्य);
	XA_BUG_ON(xa, xa_load(xa, ~1UL) != शून्य);
	xa_erase_index(xa, ~0UL);

	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_cmpxchg(काष्ठा xarray *xa)
अणु
	व्योम *FIVE = xa_mk_value(5);
	व्योम *SIX = xa_mk_value(6);
	व्योम *LOTS = xa_mk_value(12345678);

	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_store_index(xa, 12345678, GFP_KERNEL) != शून्य);
	XA_BUG_ON(xa, xa_insert(xa, 12345678, xa, GFP_KERNEL) != -EBUSY);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 12345678, SIX, FIVE, GFP_KERNEL) != LOTS);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 12345678, LOTS, FIVE, GFP_KERNEL) != LOTS);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 12345678, FIVE, LOTS, GFP_KERNEL) != FIVE);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 5, FIVE, शून्य, GFP_KERNEL) != शून्य);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 5, शून्य, FIVE, GFP_KERNEL) != शून्य);
	XA_BUG_ON(xa, xa_insert(xa, 5, FIVE, GFP_KERNEL) != -EBUSY);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 5, FIVE, शून्य, GFP_KERNEL) != FIVE);
	XA_BUG_ON(xa, xa_insert(xa, 5, FIVE, GFP_KERNEL) == -EBUSY);
	xa_erase_index(xa, 12345678);
	xa_erase_index(xa, 5);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_reserve(काष्ठा xarray *xa)
अणु
	व्योम *entry;
	अचिन्हित दीर्घ index;
	पूर्णांक count;

	/* An array with a reserved entry is not empty */
	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_reserve(xa, 12345678, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, xa_empty(xa));
	XA_BUG_ON(xa, xa_load(xa, 12345678));
	xa_release(xa, 12345678);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Releasing a used entry करोes nothing */
	XA_BUG_ON(xa, xa_reserve(xa, 12345678, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, xa_store_index(xa, 12345678, GFP_NOWAIT) != शून्य);
	xa_release(xa, 12345678);
	xa_erase_index(xa, 12345678);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* cmpxchg sees a reserved entry as ZERO */
	XA_BUG_ON(xa, xa_reserve(xa, 12345678, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, xa_cmpxchg(xa, 12345678, XA_ZERO_ENTRY,
				xa_mk_value(12345678), GFP_NOWAIT) != शून्य);
	xa_release(xa, 12345678);
	xa_erase_index(xa, 12345678);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* xa_insert treats it as busy */
	XA_BUG_ON(xa, xa_reserve(xa, 12345678, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, xa_insert(xa, 12345678, xa_mk_value(12345678), 0) !=
			-EBUSY);
	XA_BUG_ON(xa, xa_empty(xa));
	XA_BUG_ON(xa, xa_erase(xa, 12345678) != शून्य);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Can iterate through a reserved entry */
	xa_store_index(xa, 5, GFP_KERNEL);
	XA_BUG_ON(xa, xa_reserve(xa, 6, GFP_KERNEL) != 0);
	xa_store_index(xa, 7, GFP_KERNEL);

	count = 0;
	xa_क्रम_each(xa, index, entry) अणु
		XA_BUG_ON(xa, index != 5 && index != 7);
		count++;
	पूर्ण
	XA_BUG_ON(xa, count != 2);

	/* If we मुक्त a reserved entry, we should be able to allocate it */
	अगर (xa->xa_flags & XA_FLAGS_ALLOC) अणु
		u32 id;

		XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_value(8),
					XA_LIMIT(5, 10), GFP_KERNEL) != 0);
		XA_BUG_ON(xa, id != 8);

		xa_release(xa, 6);
		XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_value(6),
					XA_LIMIT(5, 10), GFP_KERNEL) != 0);
		XA_BUG_ON(xa, id != 6);
	पूर्ण

	xa_destroy(xa);
पूर्ण

अटल noअंतरभूत व्योम check_xas_erase(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	व्योम *entry;
	अचिन्हित दीर्घ i, j;

	क्रम (i = 0; i < 200; i++) अणु
		क्रम (j = i; j < 2 * i + 17; j++) अणु
			xas_set(&xas, j);
			करो अणु
				xas_lock(&xas);
				xas_store(&xas, xa_mk_index(j));
				xas_unlock(&xas);
			पूर्ण जबतक (xas_nomem(&xas, GFP_KERNEL));
		पूर्ण

		xas_set(&xas, अच_दीर्घ_उच्च);
		करो अणु
			xas_lock(&xas);
			xas_store(&xas, xa_mk_value(0));
			xas_unlock(&xas);
		पूर्ण जबतक (xas_nomem(&xas, GFP_KERNEL));

		xas_lock(&xas);
		xas_store(&xas, शून्य);

		xas_set(&xas, 0);
		j = i;
		xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
			XA_BUG_ON(xa, entry != xa_mk_index(j));
			xas_store(&xas, शून्य);
			j++;
		पूर्ण
		xas_unlock(&xas);
		XA_BUG_ON(xa, !xa_empty(xa));
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_XARRAY_MULTI
अटल noअंतरभूत व्योम check_multi_store_1(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
		अचिन्हित पूर्णांक order)
अणु
	XA_STATE(xas, xa, index);
	अचिन्हित दीर्घ min = index & ~((1UL << order) - 1);
	अचिन्हित दीर्घ max = min + (1UL << order);

	xa_store_order(xa, index, order, xa_mk_index(index), GFP_KERNEL);
	XA_BUG_ON(xa, xa_load(xa, min) != xa_mk_index(index));
	XA_BUG_ON(xa, xa_load(xa, max - 1) != xa_mk_index(index));
	XA_BUG_ON(xa, xa_load(xa, max) != शून्य);
	XA_BUG_ON(xa, xa_load(xa, min - 1) != शून्य);

	xas_lock(&xas);
	XA_BUG_ON(xa, xas_store(&xas, xa_mk_index(min)) != xa_mk_index(index));
	xas_unlock(&xas);
	XA_BUG_ON(xa, xa_load(xa, min) != xa_mk_index(min));
	XA_BUG_ON(xa, xa_load(xa, max - 1) != xa_mk_index(min));
	XA_BUG_ON(xa, xa_load(xa, max) != शून्य);
	XA_BUG_ON(xa, xa_load(xa, min - 1) != शून्य);

	xa_erase_index(xa, min);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_multi_store_2(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
		अचिन्हित पूर्णांक order)
अणु
	XA_STATE(xas, xa, index);
	xa_store_order(xa, index, order, xa_mk_value(0), GFP_KERNEL);

	xas_lock(&xas);
	XA_BUG_ON(xa, xas_store(&xas, xa_mk_value(1)) != xa_mk_value(0));
	XA_BUG_ON(xa, xas.xa_index != index);
	XA_BUG_ON(xa, xas_store(&xas, शून्य) != xa_mk_value(1));
	xas_unlock(&xas);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_multi_store_3(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
		अचिन्हित पूर्णांक order)
अणु
	XA_STATE(xas, xa, 0);
	व्योम *entry;
	पूर्णांक n = 0;

	xa_store_order(xa, index, order, xa_mk_index(index), GFP_KERNEL);

	xas_lock(&xas);
	xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
		XA_BUG_ON(xa, entry != xa_mk_index(index));
		n++;
	पूर्ण
	XA_BUG_ON(xa, n != 1);
	xas_set(&xas, index + 1);
	xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
		XA_BUG_ON(xa, entry != xa_mk_index(index));
		n++;
	पूर्ण
	XA_BUG_ON(xa, n != 2);
	xas_unlock(&xas);

	xa_destroy(xa);
पूर्ण
#पूर्ण_अगर

अटल noअंतरभूत व्योम check_multi_store(काष्ठा xarray *xa)
अणु
#अगर_घोषित CONFIG_XARRAY_MULTI
	अचिन्हित दीर्घ i, j, k;
	अचिन्हित पूर्णांक max_order = (माप(दीर्घ) == 4) ? 30 : 60;

	/* Loading from any position वापसs the same value */
	xa_store_order(xa, 0, 1, xa_mk_value(0), GFP_KERNEL);
	XA_BUG_ON(xa, xa_load(xa, 0) != xa_mk_value(0));
	XA_BUG_ON(xa, xa_load(xa, 1) != xa_mk_value(0));
	XA_BUG_ON(xa, xa_load(xa, 2) != शून्य);
	rcu_पढ़ो_lock();
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->count != 2);
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->nr_values != 2);
	rcu_पढ़ो_unlock();

	/* Storing adjacent to the value करोes not alter the value */
	xa_store(xa, 3, xa, GFP_KERNEL);
	XA_BUG_ON(xa, xa_load(xa, 0) != xa_mk_value(0));
	XA_BUG_ON(xa, xa_load(xa, 1) != xa_mk_value(0));
	XA_BUG_ON(xa, xa_load(xa, 2) != शून्य);
	rcu_पढ़ो_lock();
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->count != 3);
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->nr_values != 2);
	rcu_पढ़ो_unlock();

	/* Overwriting multiple indexes works */
	xa_store_order(xa, 0, 2, xa_mk_value(1), GFP_KERNEL);
	XA_BUG_ON(xa, xa_load(xa, 0) != xa_mk_value(1));
	XA_BUG_ON(xa, xa_load(xa, 1) != xa_mk_value(1));
	XA_BUG_ON(xa, xa_load(xa, 2) != xa_mk_value(1));
	XA_BUG_ON(xa, xa_load(xa, 3) != xa_mk_value(1));
	XA_BUG_ON(xa, xa_load(xa, 4) != शून्य);
	rcu_पढ़ो_lock();
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->count != 4);
	XA_BUG_ON(xa, xa_to_node(xa_head(xa))->nr_values != 4);
	rcu_पढ़ो_unlock();

	/* We can erase multiple values with a single store */
	xa_store_order(xa, 0, BITS_PER_LONG - 1, शून्य, GFP_KERNEL);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Even when the first slot is empty but the others aren't */
	xa_store_index(xa, 1, GFP_KERNEL);
	xa_store_index(xa, 2, GFP_KERNEL);
	xa_store_order(xa, 0, 2, शून्य, GFP_KERNEL);
	XA_BUG_ON(xa, !xa_empty(xa));

	क्रम (i = 0; i < max_order; i++) अणु
		क्रम (j = 0; j < max_order; j++) अणु
			xa_store_order(xa, 0, i, xa_mk_index(i), GFP_KERNEL);
			xa_store_order(xa, 0, j, xa_mk_index(j), GFP_KERNEL);

			क्रम (k = 0; k < max_order; k++) अणु
				व्योम *entry = xa_load(xa, (1UL << k) - 1);
				अगर ((i < k) && (j < k))
					XA_BUG_ON(xa, entry != शून्य);
				अन्यथा
					XA_BUG_ON(xa, entry != xa_mk_index(j));
			पूर्ण

			xa_erase(xa, 0);
			XA_BUG_ON(xa, !xa_empty(xa));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 20; i++) अणु
		check_multi_store_1(xa, 200, i);
		check_multi_store_1(xa, 0, i);
		check_multi_store_1(xa, (1UL << i) + 1, i);
	पूर्ण
	check_multi_store_2(xa, 4095, 9);

	क्रम (i = 1; i < 20; i++) अणु
		check_multi_store_3(xa, 0, i);
		check_multi_store_3(xa, 1UL << i, i);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल noअंतरभूत व्योम check_xa_alloc_1(काष्ठा xarray *xa, अचिन्हित पूर्णांक base)
अणु
	पूर्णांक i;
	u32 id;

	XA_BUG_ON(xa, !xa_empty(xa));
	/* An empty array should assign %base to the first alloc */
	xa_alloc_index(xa, base, GFP_KERNEL);

	/* Erasing it should make the array empty again */
	xa_erase_index(xa, base);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* And it should assign %base again */
	xa_alloc_index(xa, base, GFP_KERNEL);

	/* Allocating and then erasing a lot should not lose base */
	क्रम (i = base + 1; i < 2 * XA_CHUNK_SIZE; i++)
		xa_alloc_index(xa, i, GFP_KERNEL);
	क्रम (i = base; i < 2 * XA_CHUNK_SIZE; i++)
		xa_erase_index(xa, i);
	xa_alloc_index(xa, base, GFP_KERNEL);

	/* Destroying the array should करो the same as erasing */
	xa_destroy(xa);

	/* And it should assign %base again */
	xa_alloc_index(xa, base, GFP_KERNEL);

	/* The next asचिन्हित ID should be base+1 */
	xa_alloc_index(xa, base + 1, GFP_KERNEL);
	xa_erase_index(xa, base + 1);

	/* Storing a value should mark it used */
	xa_store_index(xa, base + 1, GFP_KERNEL);
	xa_alloc_index(xa, base + 2, GFP_KERNEL);

	/* If we then erase base, it should be मुक्त */
	xa_erase_index(xa, base);
	xa_alloc_index(xa, base, GFP_KERNEL);

	xa_erase_index(xa, base + 1);
	xa_erase_index(xa, base + 2);

	क्रम (i = 1; i < 5000; i++) अणु
		xa_alloc_index(xa, base + i, GFP_KERNEL);
	पूर्ण

	xa_destroy(xa);

	/* Check that we fail properly at the limit of allocation */
	XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_index(अच_पूर्णांक_उच्च - 1),
				XA_LIMIT(अच_पूर्णांक_उच्च - 1, अच_पूर्णांक_उच्च),
				GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != 0xfffffffeU);
	XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_index(अच_पूर्णांक_उच्च),
				XA_LIMIT(अच_पूर्णांक_उच्च - 1, अच_पूर्णांक_उच्च),
				GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != 0xffffffffU);
	id = 3;
	XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_index(0),
				XA_LIMIT(अच_पूर्णांक_उच्च - 1, अच_पूर्णांक_उच्च),
				GFP_KERNEL) != -EBUSY);
	XA_BUG_ON(xa, id != 3);
	xa_destroy(xa);

	XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_index(10), XA_LIMIT(10, 5),
				GFP_KERNEL) != -EBUSY);
	XA_BUG_ON(xa, xa_store_index(xa, 3, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_index(10), XA_LIMIT(10, 5),
				GFP_KERNEL) != -EBUSY);
	xa_erase_index(xa, 3);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_xa_alloc_2(काष्ठा xarray *xa, अचिन्हित पूर्णांक base)
अणु
	अचिन्हित पूर्णांक i, id;
	अचिन्हित दीर्घ index;
	व्योम *entry;

	/* Allocate and मुक्त a शून्य and check xa_empty() behaves */
	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_alloc(xa, &id, शून्य, xa_limit_32b, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != base);
	XA_BUG_ON(xa, xa_empty(xa));
	XA_BUG_ON(xa, xa_erase(xa, id) != शून्य);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Ditto, but check destroy instead of erase */
	XA_BUG_ON(xa, !xa_empty(xa));
	XA_BUG_ON(xa, xa_alloc(xa, &id, शून्य, xa_limit_32b, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != base);
	XA_BUG_ON(xa, xa_empty(xa));
	xa_destroy(xa);
	XA_BUG_ON(xa, !xa_empty(xa));

	क्रम (i = base; i < base + 10; i++) अणु
		XA_BUG_ON(xa, xa_alloc(xa, &id, शून्य, xa_limit_32b,
					GFP_KERNEL) != 0);
		XA_BUG_ON(xa, id != i);
	पूर्ण

	XA_BUG_ON(xa, xa_store(xa, 3, xa_mk_index(3), GFP_KERNEL) != शून्य);
	XA_BUG_ON(xa, xa_store(xa, 4, xa_mk_index(4), GFP_KERNEL) != शून्य);
	XA_BUG_ON(xa, xa_store(xa, 4, शून्य, GFP_KERNEL) != xa_mk_index(4));
	XA_BUG_ON(xa, xa_erase(xa, 5) != शून्य);
	XA_BUG_ON(xa, xa_alloc(xa, &id, शून्य, xa_limit_32b, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != 5);

	xa_क्रम_each(xa, index, entry) अणु
		xa_erase_index(xa, index);
	पूर्ण

	क्रम (i = base; i < base + 9; i++) अणु
		XA_BUG_ON(xa, xa_erase(xa, i) != शून्य);
		XA_BUG_ON(xa, xa_empty(xa));
	पूर्ण
	XA_BUG_ON(xa, xa_erase(xa, 8) != शून्य);
	XA_BUG_ON(xa, xa_empty(xa));
	XA_BUG_ON(xa, xa_erase(xa, base + 9) != शून्य);
	XA_BUG_ON(xa, !xa_empty(xa));

	xa_destroy(xa);
पूर्ण

अटल noअंतरभूत व्योम check_xa_alloc_3(काष्ठा xarray *xa, अचिन्हित पूर्णांक base)
अणु
	काष्ठा xa_limit limit = XA_LIMIT(1, 0x3fff);
	u32 next = 0;
	अचिन्हित पूर्णांक i, id;
	अचिन्हित दीर्घ index;
	व्योम *entry;

	XA_BUG_ON(xa, xa_alloc_cyclic(xa, &id, xa_mk_index(1), limit,
				&next, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != 1);

	next = 0x3ffd;
	XA_BUG_ON(xa, xa_alloc_cyclic(xa, &id, xa_mk_index(0x3ffd), limit,
				&next, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != 0x3ffd);
	xa_erase_index(xa, 0x3ffd);
	xa_erase_index(xa, 1);
	XA_BUG_ON(xa, !xa_empty(xa));

	क्रम (i = 0x3ffe; i < 0x4003; i++) अणु
		अगर (i < 0x4000)
			entry = xa_mk_index(i);
		अन्यथा
			entry = xa_mk_index(i - 0x3fff);
		XA_BUG_ON(xa, xa_alloc_cyclic(xa, &id, entry, limit,
					&next, GFP_KERNEL) != (id == 1));
		XA_BUG_ON(xa, xa_mk_index(id) != entry);
	पूर्ण

	/* Check wrap-around is handled correctly */
	अगर (base != 0)
		xa_erase_index(xa, base);
	xa_erase_index(xa, base + 1);
	next = अच_पूर्णांक_उच्च;
	XA_BUG_ON(xa, xa_alloc_cyclic(xa, &id, xa_mk_index(अच_पूर्णांक_उच्च),
				xa_limit_32b, &next, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != अच_पूर्णांक_उच्च);
	XA_BUG_ON(xa, xa_alloc_cyclic(xa, &id, xa_mk_index(base),
				xa_limit_32b, &next, GFP_KERNEL) != 1);
	XA_BUG_ON(xa, id != base);
	XA_BUG_ON(xa, xa_alloc_cyclic(xa, &id, xa_mk_index(base + 1),
				xa_limit_32b, &next, GFP_KERNEL) != 0);
	XA_BUG_ON(xa, id != base + 1);

	xa_क्रम_each(xa, index, entry)
		xa_erase_index(xa, index);

	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल DEFINE_XARRAY_ALLOC(xa0);
अटल DEFINE_XARRAY_ALLOC1(xa1);

अटल noअंतरभूत व्योम check_xa_alloc(व्योम)
अणु
	check_xa_alloc_1(&xa0, 0);
	check_xa_alloc_1(&xa1, 1);
	check_xa_alloc_2(&xa0, 0);
	check_xa_alloc_2(&xa1, 1);
	check_xa_alloc_3(&xa0, 0);
	check_xa_alloc_3(&xa1, 1);
पूर्ण

अटल noअंतरभूत व्योम __check_store_iter(काष्ठा xarray *xa, अचिन्हित दीर्घ start,
			अचिन्हित पूर्णांक order, अचिन्हित पूर्णांक present)
अणु
	XA_STATE_ORDER(xas, xa, start, order);
	व्योम *entry;
	अचिन्हित पूर्णांक count = 0;

retry:
	xas_lock(&xas);
	xas_क्रम_each_conflict(&xas, entry) अणु
		XA_BUG_ON(xa, !xa_is_value(entry));
		XA_BUG_ON(xa, entry < xa_mk_index(start));
		XA_BUG_ON(xa, entry > xa_mk_index(start + (1UL << order) - 1));
		count++;
	पूर्ण
	xas_store(&xas, xa_mk_index(start));
	xas_unlock(&xas);
	अगर (xas_nomem(&xas, GFP_KERNEL)) अणु
		count = 0;
		जाओ retry;
	पूर्ण
	XA_BUG_ON(xa, xas_error(&xas));
	XA_BUG_ON(xa, count != present);
	XA_BUG_ON(xa, xa_load(xa, start) != xa_mk_index(start));
	XA_BUG_ON(xa, xa_load(xa, start + (1UL << order) - 1) !=
			xa_mk_index(start));
	xa_erase_index(xa, start);
पूर्ण

अटल noअंतरभूत व्योम check_store_iter(काष्ठा xarray *xa)
अणु
	अचिन्हित पूर्णांक i, j;
	अचिन्हित पूर्णांक max_order = IS_ENABLED(CONFIG_XARRAY_MULTI) ? 20 : 1;

	क्रम (i = 0; i < max_order; i++) अणु
		अचिन्हित पूर्णांक min = 1 << i;
		अचिन्हित पूर्णांक max = (2 << i) - 1;
		__check_store_iter(xa, 0, i, 0);
		XA_BUG_ON(xa, !xa_empty(xa));
		__check_store_iter(xa, min, i, 0);
		XA_BUG_ON(xa, !xa_empty(xa));

		xa_store_index(xa, min, GFP_KERNEL);
		__check_store_iter(xa, min, i, 1);
		XA_BUG_ON(xa, !xa_empty(xa));
		xa_store_index(xa, max, GFP_KERNEL);
		__check_store_iter(xa, min, i, 1);
		XA_BUG_ON(xa, !xa_empty(xa));

		क्रम (j = 0; j < min; j++)
			xa_store_index(xa, j, GFP_KERNEL);
		__check_store_iter(xa, 0, i, min);
		XA_BUG_ON(xa, !xa_empty(xa));
		क्रम (j = 0; j < min; j++)
			xa_store_index(xa, min + j, GFP_KERNEL);
		__check_store_iter(xa, min, i, min);
		XA_BUG_ON(xa, !xa_empty(xa));
	पूर्ण
#अगर_घोषित CONFIG_XARRAY_MULTI
	xa_store_index(xa, 63, GFP_KERNEL);
	xa_store_index(xa, 65, GFP_KERNEL);
	__check_store_iter(xa, 64, 2, 1);
	xa_erase_index(xa, 63);
#पूर्ण_अगर
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_multi_find_1(काष्ठा xarray *xa, अचिन्हित order)
अणु
#अगर_घोषित CONFIG_XARRAY_MULTI
	अचिन्हित दीर्घ multi = 3 << order;
	अचिन्हित दीर्घ next = 4 << order;
	अचिन्हित दीर्घ index;

	xa_store_order(xa, multi, order, xa_mk_value(multi), GFP_KERNEL);
	XA_BUG_ON(xa, xa_store_index(xa, next, GFP_KERNEL) != शून्य);
	XA_BUG_ON(xa, xa_store_index(xa, next + 1, GFP_KERNEL) != शून्य);

	index = 0;
	XA_BUG_ON(xa, xa_find(xa, &index, अच_दीर्घ_उच्च, XA_PRESENT) !=
			xa_mk_value(multi));
	XA_BUG_ON(xa, index != multi);
	index = multi + 1;
	XA_BUG_ON(xa, xa_find(xa, &index, अच_दीर्घ_उच्च, XA_PRESENT) !=
			xa_mk_value(multi));
	XA_BUG_ON(xa, (index < multi) || (index >= next));
	XA_BUG_ON(xa, xa_find_after(xa, &index, अच_दीर्घ_उच्च, XA_PRESENT) !=
			xa_mk_value(next));
	XA_BUG_ON(xa, index != next);
	XA_BUG_ON(xa, xa_find_after(xa, &index, next, XA_PRESENT) != शून्य);
	XA_BUG_ON(xa, index != next);

	xa_erase_index(xa, multi);
	xa_erase_index(xa, next);
	xa_erase_index(xa, next + 1);
	XA_BUG_ON(xa, !xa_empty(xa));
#पूर्ण_अगर
पूर्ण

अटल noअंतरभूत व्योम check_multi_find_2(काष्ठा xarray *xa)
अणु
	अचिन्हित पूर्णांक max_order = IS_ENABLED(CONFIG_XARRAY_MULTI) ? 10 : 1;
	अचिन्हित पूर्णांक i, j;
	व्योम *entry;

	क्रम (i = 0; i < max_order; i++) अणु
		अचिन्हित दीर्घ index = 1UL << i;
		क्रम (j = 0; j < index; j++) अणु
			XA_STATE(xas, xa, j + index);
			xa_store_index(xa, index - 1, GFP_KERNEL);
			xa_store_order(xa, index, i, xa_mk_index(index),
					GFP_KERNEL);
			rcu_पढ़ो_lock();
			xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
				xa_erase_index(xa, index);
			पूर्ण
			rcu_पढ़ो_unlock();
			xa_erase_index(xa, index - 1);
			XA_BUG_ON(xa, !xa_empty(xa));
		पूर्ण
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम check_multi_find_3(काष्ठा xarray *xa)
अणु
	अचिन्हित पूर्णांक order;

	क्रम (order = 5; order < order_limit; order++) अणु
		अचिन्हित दीर्घ index = 1UL << (order - 5);

		XA_BUG_ON(xa, !xa_empty(xa));
		xa_store_order(xa, 0, order - 4, xa_mk_index(0), GFP_KERNEL);
		XA_BUG_ON(xa, xa_find_after(xa, &index, अच_दीर्घ_उच्च, XA_PRESENT));
		xa_erase_index(xa, 0);
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम check_find_1(काष्ठा xarray *xa)
अणु
	अचिन्हित दीर्घ i, j, k;

	XA_BUG_ON(xa, !xa_empty(xa));

	/*
	 * Check xa_find with all pairs between 0 and 99 inclusive,
	 * starting at every index between 0 and 99
	 */
	क्रम (i = 0; i < 100; i++) अणु
		XA_BUG_ON(xa, xa_store_index(xa, i, GFP_KERNEL) != शून्य);
		xa_set_mark(xa, i, XA_MARK_0);
		क्रम (j = 0; j < i; j++) अणु
			XA_BUG_ON(xa, xa_store_index(xa, j, GFP_KERNEL) !=
					शून्य);
			xa_set_mark(xa, j, XA_MARK_0);
			क्रम (k = 0; k < 100; k++) अणु
				अचिन्हित दीर्घ index = k;
				व्योम *entry = xa_find(xa, &index, अच_दीर्घ_उच्च,
								XA_PRESENT);
				अगर (k <= j)
					XA_BUG_ON(xa, index != j);
				अन्यथा अगर (k <= i)
					XA_BUG_ON(xa, index != i);
				अन्यथा
					XA_BUG_ON(xa, entry != शून्य);

				index = k;
				entry = xa_find(xa, &index, अच_दीर्घ_उच्च,
								XA_MARK_0);
				अगर (k <= j)
					XA_BUG_ON(xa, index != j);
				अन्यथा अगर (k <= i)
					XA_BUG_ON(xa, index != i);
				अन्यथा
					XA_BUG_ON(xa, entry != शून्य);
			पूर्ण
			xa_erase_index(xa, j);
			XA_BUG_ON(xa, xa_get_mark(xa, j, XA_MARK_0));
			XA_BUG_ON(xa, !xa_get_mark(xa, i, XA_MARK_0));
		पूर्ण
		xa_erase_index(xa, i);
		XA_BUG_ON(xa, xa_get_mark(xa, i, XA_MARK_0));
	पूर्ण
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_find_2(काष्ठा xarray *xa)
अणु
	व्योम *entry;
	अचिन्हित दीर्घ i, j, index;

	xa_क्रम_each(xa, index, entry) अणु
		XA_BUG_ON(xa, true);
	पूर्ण

	क्रम (i = 0; i < 1024; i++) अणु
		xa_store_index(xa, index, GFP_KERNEL);
		j = 0;
		xa_क्रम_each(xa, index, entry) अणु
			XA_BUG_ON(xa, xa_mk_index(index) != entry);
			XA_BUG_ON(xa, index != j++);
		पूर्ण
	पूर्ण

	xa_destroy(xa);
पूर्ण

अटल noअंतरभूत व्योम check_find_3(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	अचिन्हित दीर्घ i, j, k;
	व्योम *entry;

	क्रम (i = 0; i < 100; i++) अणु
		क्रम (j = 0; j < 100; j++) अणु
			rcu_पढ़ो_lock();
			क्रम (k = 0; k < 100; k++) अणु
				xas_set(&xas, j);
				xas_क्रम_each_marked(&xas, entry, k, XA_MARK_0)
					;
				अगर (j > k)
					XA_BUG_ON(xa,
						xas.xa_node != XAS_RESTART);
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण
		xa_store_index(xa, i, GFP_KERNEL);
		xa_set_mark(xa, i, XA_MARK_0);
	पूर्ण
	xa_destroy(xa);
पूर्ण

अटल noअंतरभूत व्योम check_find_4(काष्ठा xarray *xa)
अणु
	अचिन्हित दीर्घ index = 0;
	व्योम *entry;

	xa_store_index(xa, अच_दीर्घ_उच्च, GFP_KERNEL);

	entry = xa_find_after(xa, &index, अच_दीर्घ_उच्च, XA_PRESENT);
	XA_BUG_ON(xa, entry != xa_mk_index(अच_दीर्घ_उच्च));

	entry = xa_find_after(xa, &index, अच_दीर्घ_उच्च, XA_PRESENT);
	XA_BUG_ON(xa, entry);

	xa_erase_index(xa, अच_दीर्घ_उच्च);
पूर्ण

अटल noअंतरभूत व्योम check_find(काष्ठा xarray *xa)
अणु
	अचिन्हित i;

	check_find_1(xa);
	check_find_2(xa);
	check_find_3(xa);
	check_find_4(xa);

	क्रम (i = 2; i < 10; i++)
		check_multi_find_1(xa, i);
	check_multi_find_2(xa);
	check_multi_find_3(xa);
पूर्ण

/* See find_swap_entry() in mm/shmem.c */
अटल noअंतरभूत अचिन्हित दीर्घ xa_find_entry(काष्ठा xarray *xa, व्योम *item)
अणु
	XA_STATE(xas, xa, 0);
	अचिन्हित पूर्णांक checked = 0;
	व्योम *entry;

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
		अगर (xas_retry(&xas, entry))
			जारी;
		अगर (entry == item)
			अवरोध;
		checked++;
		अगर ((checked % 4) != 0)
			जारी;
		xas_छोड़ो(&xas);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस entry ? xas.xa_index : -1;
पूर्ण

अटल noअंतरभूत व्योम check_find_entry(काष्ठा xarray *xa)
अणु
#अगर_घोषित CONFIG_XARRAY_MULTI
	अचिन्हित पूर्णांक order;
	अचिन्हित दीर्घ offset, index;

	क्रम (order = 0; order < 20; order++) अणु
		क्रम (offset = 0; offset < (1UL << (order + 3));
		     offset += (1UL << order)) अणु
			क्रम (index = 0; index < (1UL << (order + 5));
			     index += (1UL << order)) अणु
				xa_store_order(xa, index, order,
						xa_mk_index(index), GFP_KERNEL);
				XA_BUG_ON(xa, xa_load(xa, index) !=
						xa_mk_index(index));
				XA_BUG_ON(xa, xa_find_entry(xa,
						xa_mk_index(index)) != index);
			पूर्ण
			XA_BUG_ON(xa, xa_find_entry(xa, xa) != -1);
			xa_destroy(xa);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	XA_BUG_ON(xa, xa_find_entry(xa, xa) != -1);
	xa_store_index(xa, अच_दीर्घ_उच्च, GFP_KERNEL);
	XA_BUG_ON(xa, xa_find_entry(xa, xa) != -1);
	XA_BUG_ON(xa, xa_find_entry(xa, xa_mk_index(अच_दीर्घ_उच्च)) != -1);
	xa_erase_index(xa, अच_दीर्घ_उच्च);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_छोड़ो(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	व्योम *entry;
	अचिन्हित पूर्णांक order;
	अचिन्हित दीर्घ index = 1;
	अचिन्हित पूर्णांक count = 0;

	क्रम (order = 0; order < order_limit; order++) अणु
		XA_BUG_ON(xa, xa_store_order(xa, index, order,
					xa_mk_index(index), GFP_KERNEL));
		index += 1UL << order;
	पूर्ण

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
		XA_BUG_ON(xa, entry != xa_mk_index(1UL << count));
		count++;
	पूर्ण
	rcu_पढ़ो_unlock();
	XA_BUG_ON(xa, count != order_limit);

	count = 0;
	xas_set(&xas, 0);
	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
		XA_BUG_ON(xa, entry != xa_mk_index(1UL << count));
		count++;
		xas_छोड़ो(&xas);
	पूर्ण
	rcu_पढ़ो_unlock();
	XA_BUG_ON(xa, count != order_limit);

	xa_destroy(xa);
पूर्ण

अटल noअंतरभूत व्योम check_move_tiny(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);

	XA_BUG_ON(xa, !xa_empty(xa));
	rcu_पढ़ो_lock();
	XA_BUG_ON(xa, xas_next(&xas) != शून्य);
	XA_BUG_ON(xa, xas_next(&xas) != शून्य);
	rcu_पढ़ो_unlock();
	xa_store_index(xa, 0, GFP_KERNEL);
	rcu_पढ़ो_lock();
	xas_set(&xas, 0);
	XA_BUG_ON(xa, xas_next(&xas) != xa_mk_index(0));
	XA_BUG_ON(xa, xas_next(&xas) != शून्य);
	xas_set(&xas, 0);
	XA_BUG_ON(xa, xas_prev(&xas) != xa_mk_index(0));
	XA_BUG_ON(xa, xas_prev(&xas) != शून्य);
	rcu_पढ़ो_unlock();
	xa_erase_index(xa, 0);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_move_max(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);

	xa_store_index(xa, अच_दीर्घ_उच्च, GFP_KERNEL);
	rcu_पढ़ो_lock();
	XA_BUG_ON(xa, xas_find(&xas, अच_दीर्घ_उच्च) != xa_mk_index(अच_दीर्घ_उच्च));
	XA_BUG_ON(xa, xas_find(&xas, अच_दीर्घ_उच्च) != शून्य);
	rcu_पढ़ो_unlock();

	xas_set(&xas, 0);
	rcu_पढ़ो_lock();
	XA_BUG_ON(xa, xas_find(&xas, अच_दीर्घ_उच्च) != xa_mk_index(अच_दीर्घ_उच्च));
	xas_छोड़ो(&xas);
	XA_BUG_ON(xa, xas_find(&xas, अच_दीर्घ_उच्च) != शून्य);
	rcu_पढ़ो_unlock();

	xa_erase_index(xa, अच_दीर्घ_उच्च);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_move_small(काष्ठा xarray *xa, अचिन्हित दीर्घ idx)
अणु
	XA_STATE(xas, xa, 0);
	अचिन्हित दीर्घ i;

	xa_store_index(xa, 0, GFP_KERNEL);
	xa_store_index(xa, idx, GFP_KERNEL);

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < idx * 4; i++) अणु
		व्योम *entry = xas_next(&xas);
		अगर (i <= idx)
			XA_BUG_ON(xa, xas.xa_node == XAS_RESTART);
		XA_BUG_ON(xa, xas.xa_index != i);
		अगर (i == 0 || i == idx)
			XA_BUG_ON(xa, entry != xa_mk_index(i));
		अन्यथा
			XA_BUG_ON(xa, entry != शून्य);
	पूर्ण
	xas_next(&xas);
	XA_BUG_ON(xa, xas.xa_index != i);

	करो अणु
		व्योम *entry = xas_prev(&xas);
		i--;
		अगर (i <= idx)
			XA_BUG_ON(xa, xas.xa_node == XAS_RESTART);
		XA_BUG_ON(xa, xas.xa_index != i);
		अगर (i == 0 || i == idx)
			XA_BUG_ON(xa, entry != xa_mk_index(i));
		अन्यथा
			XA_BUG_ON(xa, entry != शून्य);
	पूर्ण जबतक (i > 0);

	xas_set(&xas, अच_दीर्घ_उच्च);
	XA_BUG_ON(xa, xas_next(&xas) != शून्य);
	XA_BUG_ON(xa, xas.xa_index != अच_दीर्घ_उच्च);
	XA_BUG_ON(xa, xas_next(&xas) != xa_mk_value(0));
	XA_BUG_ON(xa, xas.xa_index != 0);
	XA_BUG_ON(xa, xas_prev(&xas) != शून्य);
	XA_BUG_ON(xa, xas.xa_index != अच_दीर्घ_उच्च);
	rcu_पढ़ो_unlock();

	xa_erase_index(xa, 0);
	xa_erase_index(xa, idx);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_move(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, (1 << 16) - 1);
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < (1 << 16); i++)
		XA_BUG_ON(xa, xa_store_index(xa, i, GFP_KERNEL) != शून्य);

	rcu_पढ़ो_lock();
	करो अणु
		व्योम *entry = xas_prev(&xas);
		i--;
		XA_BUG_ON(xa, entry != xa_mk_index(i));
		XA_BUG_ON(xa, i != xas.xa_index);
	पूर्ण जबतक (i != 0);

	XA_BUG_ON(xa, xas_prev(&xas) != शून्य);
	XA_BUG_ON(xa, xas.xa_index != अच_दीर्घ_उच्च);

	करो अणु
		व्योम *entry = xas_next(&xas);
		XA_BUG_ON(xa, entry != xa_mk_index(i));
		XA_BUG_ON(xa, i != xas.xa_index);
		i++;
	पूर्ण जबतक (i < (1 << 16));
	rcu_पढ़ो_unlock();

	क्रम (i = (1 << 8); i < (1 << 15); i++)
		xa_erase_index(xa, i);

	i = xas.xa_index;

	rcu_पढ़ो_lock();
	करो अणु
		व्योम *entry = xas_prev(&xas);
		i--;
		अगर ((i < (1 << 8)) || (i >= (1 << 15)))
			XA_BUG_ON(xa, entry != xa_mk_index(i));
		अन्यथा
			XA_BUG_ON(xa, entry != शून्य);
		XA_BUG_ON(xa, i != xas.xa_index);
	पूर्ण जबतक (i != 0);

	XA_BUG_ON(xa, xas_prev(&xas) != शून्य);
	XA_BUG_ON(xa, xas.xa_index != अच_दीर्घ_उच्च);

	करो अणु
		व्योम *entry = xas_next(&xas);
		अगर ((i < (1 << 8)) || (i >= (1 << 15)))
			XA_BUG_ON(xa, entry != xa_mk_index(i));
		अन्यथा
			XA_BUG_ON(xa, entry != शून्य);
		XA_BUG_ON(xa, i != xas.xa_index);
		i++;
	पूर्ण जबतक (i < (1 << 16));
	rcu_पढ़ो_unlock();

	xa_destroy(xa);

	check_move_tiny(xa);
	check_move_max(xa);

	क्रम (i = 0; i < 16; i++)
		check_move_small(xa, 1UL << i);

	क्रम (i = 2; i < 16; i++)
		check_move_small(xa, (1UL << i) - 1);
पूर्ण

अटल noअंतरभूत व्योम xa_store_many_order(काष्ठा xarray *xa,
		अचिन्हित दीर्घ index, अचिन्हित order)
अणु
	XA_STATE_ORDER(xas, xa, index, order);
	अचिन्हित पूर्णांक i = 0;

	करो अणु
		xas_lock(&xas);
		XA_BUG_ON(xa, xas_find_conflict(&xas));
		xas_create_range(&xas);
		अगर (xas_error(&xas))
			जाओ unlock;
		क्रम (i = 0; i < (1U << order); i++) अणु
			XA_BUG_ON(xa, xas_store(&xas, xa_mk_index(index + i)));
			xas_next(&xas);
		पूर्ण
unlock:
		xas_unlock(&xas);
	पूर्ण जबतक (xas_nomem(&xas, GFP_KERNEL));

	XA_BUG_ON(xa, xas_error(&xas));
पूर्ण

अटल noअंतरभूत व्योम check_create_range_1(काष्ठा xarray *xa,
		अचिन्हित दीर्घ index, अचिन्हित order)
अणु
	अचिन्हित दीर्घ i;

	xa_store_many_order(xa, index, order);
	क्रम (i = index; i < index + (1UL << order); i++)
		xa_erase_index(xa, i);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_create_range_2(काष्ठा xarray *xa, अचिन्हित order)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ nr = 1UL << order;

	क्रम (i = 0; i < nr * nr; i += nr)
		xa_store_many_order(xa, i, order);
	क्रम (i = 0; i < nr * nr; i++)
		xa_erase_index(xa, i);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_create_range_3(व्योम)
अणु
	XA_STATE(xas, शून्य, 0);
	xas_set_err(&xas, -EEXIST);
	xas_create_range(&xas);
	XA_BUG_ON(शून्य, xas_error(&xas) != -EEXIST);
पूर्ण

अटल noअंतरभूत व्योम check_create_range_4(काष्ठा xarray *xa,
		अचिन्हित दीर्घ index, अचिन्हित order)
अणु
	XA_STATE_ORDER(xas, xa, index, order);
	अचिन्हित दीर्घ base = xas.xa_index;
	अचिन्हित दीर्घ i = 0;

	xa_store_index(xa, index, GFP_KERNEL);
	करो अणु
		xas_lock(&xas);
		xas_create_range(&xas);
		अगर (xas_error(&xas))
			जाओ unlock;
		क्रम (i = 0; i < (1UL << order); i++) अणु
			व्योम *old = xas_store(&xas, xa_mk_index(base + i));
			अगर (xas.xa_index == index)
				XA_BUG_ON(xa, old != xa_mk_index(base + i));
			अन्यथा
				XA_BUG_ON(xa, old != शून्य);
			xas_next(&xas);
		पूर्ण
unlock:
		xas_unlock(&xas);
	पूर्ण जबतक (xas_nomem(&xas, GFP_KERNEL));

	XA_BUG_ON(xa, xas_error(&xas));

	क्रम (i = base; i < base + (1UL << order); i++)
		xa_erase_index(xa, i);
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_create_range(काष्ठा xarray *xa)
अणु
	अचिन्हित पूर्णांक order;
	अचिन्हित पूर्णांक max_order = IS_ENABLED(CONFIG_XARRAY_MULTI) ? 12 : 1;

	क्रम (order = 0; order < max_order; order++) अणु
		check_create_range_1(xa, 0, order);
		check_create_range_1(xa, 1U << order, order);
		check_create_range_1(xa, 2U << order, order);
		check_create_range_1(xa, 3U << order, order);
		check_create_range_1(xa, 1U << 24, order);
		अगर (order < 10)
			check_create_range_2(xa, order);

		check_create_range_4(xa, 0, order);
		check_create_range_4(xa, 1U << order, order);
		check_create_range_4(xa, 2U << order, order);
		check_create_range_4(xa, 3U << order, order);
		check_create_range_4(xa, 1U << 24, order);

		check_create_range_4(xa, 1, order);
		check_create_range_4(xa, (1U << order) + 1, order);
		check_create_range_4(xa, (2U << order) + 1, order);
		check_create_range_4(xa, (2U << order) - 1, order);
		check_create_range_4(xa, (3U << order) + 1, order);
		check_create_range_4(xa, (3U << order) - 1, order);
		check_create_range_4(xa, (1U << 24) + 1, order);
	पूर्ण

	check_create_range_3();
पूर्ण

अटल noअंतरभूत व्योम __check_store_range(काष्ठा xarray *xa, अचिन्हित दीर्घ first,
		अचिन्हित दीर्घ last)
अणु
#अगर_घोषित CONFIG_XARRAY_MULTI
	xa_store_range(xa, first, last, xa_mk_index(first), GFP_KERNEL);

	XA_BUG_ON(xa, xa_load(xa, first) != xa_mk_index(first));
	XA_BUG_ON(xa, xa_load(xa, last) != xa_mk_index(first));
	XA_BUG_ON(xa, xa_load(xa, first - 1) != शून्य);
	XA_BUG_ON(xa, xa_load(xa, last + 1) != शून्य);

	xa_store_range(xa, first, last, शून्य, GFP_KERNEL);
#पूर्ण_अगर

	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_store_range(काष्ठा xarray *xa)
अणु
	अचिन्हित दीर्घ i, j;

	क्रम (i = 0; i < 128; i++) अणु
		क्रम (j = i; j < 128; j++) अणु
			__check_store_range(xa, i, j);
			__check_store_range(xa, 128 + i, 128 + j);
			__check_store_range(xa, 4095 + i, 4095 + j);
			__check_store_range(xa, 4096 + i, 4096 + j);
			__check_store_range(xa, 123456 + i, 123456 + j);
			__check_store_range(xa, (1 << 24) + i, (1 << 24) + j);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_XARRAY_MULTI
अटल व्योम check_split_1(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
				अचिन्हित पूर्णांक order, अचिन्हित पूर्णांक new_order)
अणु
	XA_STATE_ORDER(xas, xa, index, new_order);
	अचिन्हित पूर्णांक i;

	xa_store_order(xa, index, order, xa, GFP_KERNEL);

	xas_split_alloc(&xas, xa, order, GFP_KERNEL);
	xas_lock(&xas);
	xas_split(&xas, xa, order);
	क्रम (i = 0; i < (1 << order); i += (1 << new_order))
		__xa_store(xa, index + i, xa_mk_index(index + i), 0);
	xas_unlock(&xas);

	क्रम (i = 0; i < (1 << order); i++) अणु
		अचिन्हित पूर्णांक val = index + (i & ~((1 << new_order) - 1));
		XA_BUG_ON(xa, xa_load(xa, index + i) != xa_mk_index(val));
	पूर्ण

	xa_set_mark(xa, index, XA_MARK_0);
	XA_BUG_ON(xa, !xa_get_mark(xa, index, XA_MARK_0));

	xa_destroy(xa);
पूर्ण

अटल noअंतरभूत व्योम check_split(काष्ठा xarray *xa)
अणु
	अचिन्हित पूर्णांक order, new_order;

	XA_BUG_ON(xa, !xa_empty(xa));

	क्रम (order = 1; order < 2 * XA_CHUNK_SHIFT; order++) अणु
		क्रम (new_order = 0; new_order < order; new_order++) अणु
			check_split_1(xa, 0, order, new_order);
			check_split_1(xa, 1UL << order, order, new_order);
			check_split_1(xa, 3UL << order, order, new_order);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम check_split(काष्ठा xarray *xa) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम check_align_1(काष्ठा xarray *xa, अक्षर *name)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक id;
	अचिन्हित दीर्घ index;
	व्योम *entry;

	क्रम (i = 0; i < 8; i++) अणु
		XA_BUG_ON(xa, xa_alloc(xa, &id, name + i, xa_limit_32b,
					GFP_KERNEL) != 0);
		XA_BUG_ON(xa, id != i);
	पूर्ण
	xa_क्रम_each(xa, index, entry)
		XA_BUG_ON(xa, xa_is_err(entry));
	xa_destroy(xa);
पूर्ण

/*
 * We should always be able to store without allocating memory after
 * reserving a slot.
 */
अटल व्योम check_align_2(काष्ठा xarray *xa, अक्षर *name)
अणु
	पूर्णांक i;

	XA_BUG_ON(xa, !xa_empty(xa));

	क्रम (i = 0; i < 8; i++) अणु
		XA_BUG_ON(xa, xa_store(xa, 0, name + i, GFP_KERNEL) != शून्य);
		xa_erase(xa, 0);
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		XA_BUG_ON(xa, xa_reserve(xa, 0, GFP_KERNEL) != 0);
		XA_BUG_ON(xa, xa_store(xa, 0, name + i, 0) != शून्य);
		xa_erase(xa, 0);
	पूर्ण

	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

अटल noअंतरभूत व्योम check_align(काष्ठा xarray *xa)
अणु
	अक्षर name[] = "Motorola 68000";

	check_align_1(xa, name);
	check_align_1(xa, name + 1);
	check_align_1(xa, name + 2);
	check_align_1(xa, name + 3);
	check_align_2(xa, name);
पूर्ण

अटल LIST_HEAD(shaकरोw_nodes);

अटल व्योम test_update_node(काष्ठा xa_node *node)
अणु
	अगर (node->count && node->count == node->nr_values) अणु
		अगर (list_empty(&node->निजी_list))
			list_add(&shaकरोw_nodes, &node->निजी_list);
	पूर्ण अन्यथा अणु
		अगर (!list_empty(&node->निजी_list))
			list_del_init(&node->निजी_list);
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम shaकरोw_हटाओ(काष्ठा xarray *xa)
अणु
	काष्ठा xa_node *node;

	xa_lock(xa);
	जबतक ((node = list_first_entry_or_null(&shaकरोw_nodes,
					काष्ठा xa_node, निजी_list))) अणु
		XA_BUG_ON(xa, node->array != xa);
		list_del_init(&node->निजी_list);
		xa_delete_node(node, test_update_node);
	पूर्ण
	xa_unlock(xa);
पूर्ण

अटल noअंतरभूत व्योम check_workingset(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	XA_STATE(xas, xa, index);
	xas_set_update(&xas, test_update_node);

	करो अणु
		xas_lock(&xas);
		xas_store(&xas, xa_mk_value(0));
		xas_next(&xas);
		xas_store(&xas, xa_mk_value(1));
		xas_unlock(&xas);
	पूर्ण जबतक (xas_nomem(&xas, GFP_KERNEL));

	XA_BUG_ON(xa, list_empty(&shaकरोw_nodes));

	xas_lock(&xas);
	xas_next(&xas);
	xas_store(&xas, &xas);
	XA_BUG_ON(xa, !list_empty(&shaकरोw_nodes));

	xas_store(&xas, xa_mk_value(2));
	xas_unlock(&xas);
	XA_BUG_ON(xa, list_empty(&shaकरोw_nodes));

	shaकरोw_हटाओ(xa);
	XA_BUG_ON(xa, !list_empty(&shaकरोw_nodes));
	XA_BUG_ON(xa, !xa_empty(xa));
पूर्ण

/*
 * Check that the poपूर्णांकer / value / sibling entries are accounted the
 * way we expect them to be.
 */
अटल noअंतरभूत व्योम check_account(काष्ठा xarray *xa)
अणु
#अगर_घोषित CONFIG_XARRAY_MULTI
	अचिन्हित पूर्णांक order;

	क्रम (order = 1; order < 12; order++) अणु
		XA_STATE(xas, xa, 1 << order);

		xa_store_order(xa, 0, order, xa, GFP_KERNEL);
		rcu_पढ़ो_lock();
		xas_load(&xas);
		XA_BUG_ON(xa, xas.xa_node->count == 0);
		XA_BUG_ON(xa, xas.xa_node->count > (1 << order));
		XA_BUG_ON(xa, xas.xa_node->nr_values != 0);
		rcu_पढ़ो_unlock();

		xa_store_order(xa, 1 << order, order, xa_mk_index(1UL << order),
				GFP_KERNEL);
		XA_BUG_ON(xa, xas.xa_node->count != xas.xa_node->nr_values * 2);

		xa_erase(xa, 1 << order);
		XA_BUG_ON(xa, xas.xa_node->nr_values != 0);

		xa_erase(xa, 0);
		XA_BUG_ON(xa, !xa_empty(xa));
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल noअंतरभूत व्योम check_get_order(काष्ठा xarray *xa)
अणु
	अचिन्हित पूर्णांक max_order = IS_ENABLED(CONFIG_XARRAY_MULTI) ? 20 : 1;
	अचिन्हित पूर्णांक order;
	अचिन्हित दीर्घ i, j;

	क्रम (i = 0; i < 3; i++)
		XA_BUG_ON(xa, xa_get_order(xa, i) != 0);

	क्रम (order = 0; order < max_order; order++) अणु
		क्रम (i = 0; i < 10; i++) अणु
			xa_store_order(xa, i << order, order,
					xa_mk_index(i << order), GFP_KERNEL);
			क्रम (j = i << order; j < (i + 1) << order; j++)
				XA_BUG_ON(xa, xa_get_order(xa, j) != order);
			xa_erase(xa, i << order);
		पूर्ण
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम check_destroy(काष्ठा xarray *xa)
अणु
	अचिन्हित दीर्घ index;

	XA_BUG_ON(xa, !xa_empty(xa));

	/* Destroying an empty array is a no-op */
	xa_destroy(xa);
	XA_BUG_ON(xa, !xa_empty(xa));

	/* Destroying an array with a single entry */
	क्रम (index = 0; index < 1000; index++) अणु
		xa_store_index(xa, index, GFP_KERNEL);
		XA_BUG_ON(xa, xa_empty(xa));
		xa_destroy(xa);
		XA_BUG_ON(xa, !xa_empty(xa));
	पूर्ण

	/* Destroying an array with a single entry at अच_दीर्घ_उच्च */
	xa_store(xa, अच_दीर्घ_उच्च, xa, GFP_KERNEL);
	XA_BUG_ON(xa, xa_empty(xa));
	xa_destroy(xa);
	XA_BUG_ON(xa, !xa_empty(xa));

#अगर_घोषित CONFIG_XARRAY_MULTI
	/* Destroying an array with a multi-index entry */
	xa_store_order(xa, 1 << 11, 11, xa, GFP_KERNEL);
	XA_BUG_ON(xa, xa_empty(xa));
	xa_destroy(xa);
	XA_BUG_ON(xa, !xa_empty(xa));
#पूर्ण_अगर
पूर्ण

अटल DEFINE_XARRAY(array);

अटल पूर्णांक xarray_checks(व्योम)
अणु
	check_xa_err(&array);
	check_xas_retry(&array);
	check_xa_load(&array);
	check_xa_mark(&array);
	check_xa_shrink(&array);
	check_xas_erase(&array);
	check_insert(&array);
	check_cmpxchg(&array);
	check_reserve(&array);
	check_reserve(&xa0);
	check_multi_store(&array);
	check_get_order(&array);
	check_xa_alloc();
	check_find(&array);
	check_find_entry(&array);
	check_छोड़ो(&array);
	check_account(&array);
	check_destroy(&array);
	check_move(&array);
	check_create_range(&array);
	check_store_range(&array);
	check_store_iter(&array);
	check_align(&xa0);
	check_split(&array);

	check_workingset(&array, 0);
	check_workingset(&array, 64);
	check_workingset(&array, 4096);

	prपूर्णांकk("XArray: %u of %u tests passed\n", tests_passed, tests_run);
	वापस (tests_run == tests_passed) ? 0 : -EINVAL;
पूर्ण

अटल व्योम xarray_निकास(व्योम)
अणु
पूर्ण

module_init(xarray_checks);
module_निकास(xarray_निकास);
MODULE_AUTHOR("Matthew Wilcox <willy@infradead.org>");
MODULE_LICENSE("GPL");
