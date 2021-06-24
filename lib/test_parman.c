<शैली गुरु>
/*
 * lib/test_parman.c - Test module क्रम parman
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2017 Jiri Pirko <jiri@mellanox.com>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/parman.h>

#घोषणा TEST_PARMAN_PRIO_SHIFT 7 /* defines number of prios क्रम testing */
#घोषणा TEST_PARMAN_PRIO_COUNT BIT(TEST_PARMAN_PRIO_SHIFT)
#घोषणा TEST_PARMAN_PRIO_MASK (TEST_PARMAN_PRIO_COUNT - 1)

#घोषणा TEST_PARMAN_ITEM_SHIFT 13 /* defines a total number
				   * of items क्रम testing
				   */
#घोषणा TEST_PARMAN_ITEM_COUNT BIT(TEST_PARMAN_ITEM_SHIFT)
#घोषणा TEST_PARMAN_ITEM_MASK (TEST_PARMAN_ITEM_COUNT - 1)

#घोषणा TEST_PARMAN_BASE_SHIFT 8
#घोषणा TEST_PARMAN_BASE_COUNT BIT(TEST_PARMAN_BASE_SHIFT)
#घोषणा TEST_PARMAN_RESIZE_STEP_SHIFT 7
#घोषणा TEST_PARMAN_RESIZE_STEP_COUNT BIT(TEST_PARMAN_RESIZE_STEP_SHIFT)

#घोषणा TEST_PARMAN_BULK_MAX_SHIFT (2 + TEST_PARMAN_RESIZE_STEP_SHIFT)
#घोषणा TEST_PARMAN_BULK_MAX_COUNT BIT(TEST_PARMAN_BULK_MAX_SHIFT)
#घोषणा TEST_PARMAN_BULK_MAX_MASK (TEST_PARMAN_BULK_MAX_COUNT - 1)

#घोषणा TEST_PARMAN_RUN_BUDGET (TEST_PARMAN_ITEM_COUNT * 256)

काष्ठा test_parman_prio अणु
	काष्ठा parman_prio parman_prio;
	अचिन्हित दीर्घ priority;
पूर्ण;

काष्ठा test_parman_item अणु
	काष्ठा parman_item parman_item;
	काष्ठा test_parman_prio *prio;
	bool used;
पूर्ण;

काष्ठा test_parman अणु
	काष्ठा parman *parman;
	काष्ठा test_parman_item **prio_array;
	अचिन्हित दीर्घ prio_array_limit;
	काष्ठा test_parman_prio prios[TEST_PARMAN_PRIO_COUNT];
	काष्ठा test_parman_item items[TEST_PARMAN_ITEM_COUNT];
	काष्ठा rnd_state rnd;
	अचिन्हित दीर्घ run_budget;
	अचिन्हित दीर्घ bulk_budget;
	bool bulk_noop;
	अचिन्हित पूर्णांक used_items;
पूर्ण;

#घोषणा ITEM_PTRS_SIZE(count) (माप(काष्ठा test_parman_item *) * (count))

अटल पूर्णांक test_parman_resize(व्योम *priv, अचिन्हित दीर्घ new_count)
अणु
	काष्ठा test_parman *test_parman = priv;
	काष्ठा test_parman_item **prio_array;
	अचिन्हित दीर्घ old_count;

	prio_array = kपुनः_स्मृति(test_parman->prio_array,
			      ITEM_PTRS_SIZE(new_count), GFP_KERNEL);
	अगर (new_count == 0)
		वापस 0;
	अगर (!prio_array)
		वापस -ENOMEM;
	old_count = test_parman->prio_array_limit;
	अगर (new_count > old_count)
		स_रखो(&prio_array[old_count], 0,
		       ITEM_PTRS_SIZE(new_count - old_count));
	test_parman->prio_array = prio_array;
	test_parman->prio_array_limit = new_count;
	वापस 0;
पूर्ण

अटल व्योम test_parman_move(व्योम *priv, अचिन्हित दीर्घ from_index,
			     अचिन्हित दीर्घ to_index, अचिन्हित दीर्घ count)
अणु
	काष्ठा test_parman *test_parman = priv;
	काष्ठा test_parman_item **prio_array = test_parman->prio_array;

	स_हटाओ(&prio_array[to_index], &prio_array[from_index],
		ITEM_PTRS_SIZE(count));
	स_रखो(&prio_array[from_index], 0, ITEM_PTRS_SIZE(count));
पूर्ण

अटल स्थिर काष्ठा parman_ops test_parman_lsort_ops = अणु
	.base_count	= TEST_PARMAN_BASE_COUNT,
	.resize_step	= TEST_PARMAN_RESIZE_STEP_COUNT,
	.resize		= test_parman_resize,
	.move		= test_parman_move,
	.algo		= PARMAN_ALGO_TYPE_LSORT,
पूर्ण;

अटल व्योम test_parman_rnd_init(काष्ठा test_parman *test_parman)
अणु
	pअक्रमom_seed_state(&test_parman->rnd, 3141592653589793238ULL);
पूर्ण

अटल u32 test_parman_rnd_get(काष्ठा test_parman *test_parman)
अणु
	वापस pअक्रमom_u32_state(&test_parman->rnd);
पूर्ण

अटल अचिन्हित दीर्घ test_parman_priority_gen(काष्ठा test_parman *test_parman)
अणु
	अचिन्हित दीर्घ priority;
	पूर्णांक i;

again:
	priority = test_parman_rnd_get(test_parman);
	अगर (priority == 0)
		जाओ again;

	क्रम (i = 0; i < TEST_PARMAN_PRIO_COUNT; i++) अणु
		काष्ठा test_parman_prio *prio = &test_parman->prios[i];

		अगर (prio->priority == 0)
			अवरोध;
		अगर (prio->priority == priority)
			जाओ again;
	पूर्ण
	वापस priority;
पूर्ण

अटल व्योम test_parman_prios_init(काष्ठा test_parman *test_parman)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TEST_PARMAN_PRIO_COUNT; i++) अणु
		काष्ठा test_parman_prio *prio = &test_parman->prios[i];

		/* Assign अक्रमom uniqueue priority to each prio काष्ठाure */
		prio->priority = test_parman_priority_gen(test_parman);
		parman_prio_init(test_parman->parman, &prio->parman_prio,
				 prio->priority);
	पूर्ण
पूर्ण

अटल व्योम test_parman_prios_fini(काष्ठा test_parman *test_parman)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TEST_PARMAN_PRIO_COUNT; i++) अणु
		काष्ठा test_parman_prio *prio = &test_parman->prios[i];

		parman_prio_fini(&prio->parman_prio);
	पूर्ण
पूर्ण

अटल व्योम test_parman_items_init(काष्ठा test_parman *test_parman)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TEST_PARMAN_ITEM_COUNT; i++) अणु
		काष्ठा test_parman_item *item = &test_parman->items[i];
		अचिन्हित पूर्णांक prio_index = test_parman_rnd_get(test_parman) &
					  TEST_PARMAN_PRIO_MASK;

		/* Assign अक्रमom prio to each item काष्ठाure */
		item->prio = &test_parman->prios[prio_index];
	पूर्ण
पूर्ण

अटल व्योम test_parman_items_fini(काष्ठा test_parman *test_parman)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TEST_PARMAN_ITEM_COUNT; i++) अणु
		काष्ठा test_parman_item *item = &test_parman->items[i];

		अगर (!item->used)
			जारी;
		parman_item_हटाओ(test_parman->parman,
				   &item->prio->parman_prio,
				   &item->parman_item);
	पूर्ण
पूर्ण

अटल काष्ठा test_parman *test_parman_create(स्थिर काष्ठा parman_ops *ops)
अणु
	काष्ठा test_parman *test_parman;
	पूर्णांक err;

	test_parman = kzalloc(माप(*test_parman), GFP_KERNEL);
	अगर (!test_parman)
		वापस ERR_PTR(-ENOMEM);
	err = test_parman_resize(test_parman, TEST_PARMAN_BASE_COUNT);
	अगर (err)
		जाओ err_resize;
	test_parman->parman = parman_create(ops, test_parman);
	अगर (!test_parman->parman) अणु
		err = -ENOMEM;
		जाओ err_parman_create;
	पूर्ण
	test_parman_rnd_init(test_parman);
	test_parman_prios_init(test_parman);
	test_parman_items_init(test_parman);
	test_parman->run_budget = TEST_PARMAN_RUN_BUDGET;
	वापस test_parman;

err_parman_create:
	test_parman_resize(test_parman, 0);
err_resize:
	kमुक्त(test_parman);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम test_parman_destroy(काष्ठा test_parman *test_parman)
अणु
	test_parman_items_fini(test_parman);
	test_parman_prios_fini(test_parman);
	parman_destroy(test_parman->parman);
	test_parman_resize(test_parman, 0);
	kमुक्त(test_parman);
पूर्ण

अटल bool test_parman_run_check_budमाला_लो(काष्ठा test_parman *test_parman)
अणु
	अगर (test_parman->run_budget-- == 0)
		वापस false;
	अगर (test_parman->bulk_budget-- != 0)
		वापस true;

	test_parman->bulk_budget = test_parman_rnd_get(test_parman) &
				   TEST_PARMAN_BULK_MAX_MASK;
	test_parman->bulk_noop = test_parman_rnd_get(test_parman) & 1;
	वापस true;
पूर्ण

अटल पूर्णांक test_parman_run(काष्ठा test_parman *test_parman)
अणु
	अचिन्हित पूर्णांक i = test_parman_rnd_get(test_parman);
	पूर्णांक err;

	जबतक (test_parman_run_check_budमाला_लो(test_parman)) अणु
		अचिन्हित पूर्णांक item_index = i++ & TEST_PARMAN_ITEM_MASK;
		काष्ठा test_parman_item *item = &test_parman->items[item_index];

		अगर (test_parman->bulk_noop)
			जारी;

		अगर (!item->used) अणु
			err = parman_item_add(test_parman->parman,
					      &item->prio->parman_prio,
					      &item->parman_item);
			अगर (err)
				वापस err;
			test_parman->prio_array[item->parman_item.index] = item;
			test_parman->used_items++;
		पूर्ण अन्यथा अणु
			test_parman->prio_array[item->parman_item.index] = शून्य;
			parman_item_हटाओ(test_parman->parman,
					   &item->prio->parman_prio,
					   &item->parman_item);
			test_parman->used_items--;
		पूर्ण
		item->used = !item->used;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test_parman_check_array(काष्ठा test_parman *test_parman,
				   bool gaps_allowed)
अणु
	अचिन्हित पूर्णांक last_unused_items = 0;
	अचिन्हित दीर्घ last_priority = 0;
	अचिन्हित पूर्णांक used_items = 0;
	पूर्णांक i;

	अगर (test_parman->prio_array_limit < TEST_PARMAN_BASE_COUNT) अणु
		pr_err("Array limit is lower than the base count (%lu < %lu)\n",
		       test_parman->prio_array_limit, TEST_PARMAN_BASE_COUNT);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < test_parman->prio_array_limit; i++) अणु
		काष्ठा test_parman_item *item = test_parman->prio_array[i];

		अगर (!item) अणु
			last_unused_items++;
			जारी;
		पूर्ण
		अगर (last_unused_items && !gaps_allowed) अणु
			pr_err("Gap found in array even though they are forbidden\n");
			वापस -EINVAL;
		पूर्ण

		last_unused_items = 0;
		used_items++;

		अगर (item->prio->priority < last_priority) अणु
			pr_err("Item belongs under higher priority then the last one (current: %lu, previous: %lu)\n",
			       item->prio->priority, last_priority);
			वापस -EINVAL;
		पूर्ण
		last_priority = item->prio->priority;

		अगर (item->parman_item.index != i) अणु
			pr_err("Item has different index in compare to where it actually is (%lu != %d)\n",
			       item->parman_item.index, i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (used_items != test_parman->used_items) अणु
		pr_err("Number of used items in array does not match (%u != %u)\n",
		       used_items, test_parman->used_items);
		वापस -EINVAL;
	पूर्ण

	अगर (last_unused_items >= TEST_PARMAN_RESIZE_STEP_COUNT) अणु
		pr_err("Number of unused item at the end of array is bigger than resize step (%u >= %lu)\n",
		       last_unused_items, TEST_PARMAN_RESIZE_STEP_COUNT);
		वापस -EINVAL;
	पूर्ण

	pr_info("Priority array check successful\n");

	वापस 0;
पूर्ण

अटल पूर्णांक test_parman_lsort(व्योम)
अणु
	काष्ठा test_parman *test_parman;
	पूर्णांक err;

	test_parman = test_parman_create(&test_parman_lsort_ops);
	अगर (IS_ERR(test_parman))
		वापस PTR_ERR(test_parman);

	err = test_parman_run(test_parman);
	अगर (err)
		जाओ out;

	err = test_parman_check_array(test_parman, false);
	अगर (err)
		जाओ out;
out:
	test_parman_destroy(test_parman);
	वापस err;
पूर्ण

अटल पूर्णांक __init test_parman_init(व्योम)
अणु
	वापस test_parman_lsort();
पूर्ण

अटल व्योम __निकास test_parman_निकास(व्योम)
अणु
पूर्ण

module_init(test_parman_init);
module_निकास(test_parman_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Test module for parman");
