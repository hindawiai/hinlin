<शैली गुरु>
/*
 * lib/parman.c - Manager क्रम linear priority array areas
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/err.h>
#समावेश <linux/parman.h>

काष्ठा parman_algo अणु
	पूर्णांक (*item_add)(काष्ठा parman *parman, काष्ठा parman_prio *prio,
			काष्ठा parman_item *item);
	व्योम (*item_हटाओ)(काष्ठा parman *parman, काष्ठा parman_prio *prio,
			    काष्ठा parman_item *item);
पूर्ण;

काष्ठा parman अणु
	स्थिर काष्ठा parman_ops *ops;
	व्योम *priv;
	स्थिर काष्ठा parman_algo *algo;
	अचिन्हित दीर्घ count;
	अचिन्हित दीर्घ limit_count;
	काष्ठा list_head prio_list;
पूर्ण;

अटल पूर्णांक parman_enlarge(काष्ठा parman *parman)
अणु
	अचिन्हित दीर्घ new_count = parman->limit_count +
				  parman->ops->resize_step;
	पूर्णांक err;

	err = parman->ops->resize(parman->priv, new_count);
	अगर (err)
		वापस err;
	parman->limit_count = new_count;
	वापस 0;
पूर्ण

अटल पूर्णांक parman_shrink(काष्ठा parman *parman)
अणु
	अचिन्हित दीर्घ new_count = parman->limit_count -
				  parman->ops->resize_step;
	पूर्णांक err;

	अगर (new_count < parman->ops->base_count)
		वापस 0;
	err = parman->ops->resize(parman->priv, new_count);
	अगर (err)
		वापस err;
	parman->limit_count = new_count;
	वापस 0;
पूर्ण

अटल bool parman_prio_used(काष्ठा parman_prio *prio)
अणु
	वापस !list_empty(&prio->item_list);
पूर्ण

अटल काष्ठा parman_item *parman_prio_first_item(काष्ठा parman_prio *prio)
अणु
	वापस list_first_entry(&prio->item_list,
				typeof(काष्ठा parman_item), list);
पूर्ण

अटल अचिन्हित दीर्घ parman_prio_first_index(काष्ठा parman_prio *prio)
अणु
	वापस parman_prio_first_item(prio)->index;
पूर्ण

अटल काष्ठा parman_item *parman_prio_last_item(काष्ठा parman_prio *prio)
अणु
	वापस list_last_entry(&prio->item_list,
			       typeof(काष्ठा parman_item), list);
पूर्ण

अटल अचिन्हित दीर्घ parman_prio_last_index(काष्ठा parman_prio *prio)
अणु
	वापस parman_prio_last_item(prio)->index;
पूर्ण

अटल अचिन्हित दीर्घ parman_lsort_new_index_find(काष्ठा parman *parman,
						 काष्ठा parman_prio *prio)
अणु
	list_क्रम_each_entry_from_reverse(prio, &parman->prio_list, list) अणु
		अगर (!parman_prio_used(prio))
			जारी;
		वापस parman_prio_last_index(prio) + 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __parman_prio_move(काष्ठा parman *parman, काष्ठा parman_prio *prio,
			       काष्ठा parman_item *item, अचिन्हित दीर्घ to_index,
			       अचिन्हित दीर्घ count)
अणु
	parman->ops->move(parman->priv, item->index, to_index, count);
पूर्ण

अटल व्योम parman_prio_shअगरt_करोwn(काष्ठा parman *parman,
				   काष्ठा parman_prio *prio)
अणु
	काष्ठा parman_item *item;
	अचिन्हित दीर्घ to_index;

	अगर (!parman_prio_used(prio))
		वापस;
	item = parman_prio_first_item(prio);
	to_index = parman_prio_last_index(prio) + 1;
	__parman_prio_move(parman, prio, item, to_index, 1);
	list_move_tail(&item->list, &prio->item_list);
	item->index = to_index;
पूर्ण

अटल व्योम parman_prio_shअगरt_up(काष्ठा parman *parman,
				 काष्ठा parman_prio *prio)
अणु
	काष्ठा parman_item *item;
	अचिन्हित दीर्घ to_index;

	अगर (!parman_prio_used(prio))
		वापस;
	item = parman_prio_last_item(prio);
	to_index = parman_prio_first_index(prio) - 1;
	__parman_prio_move(parman, prio, item, to_index, 1);
	list_move(&item->list, &prio->item_list);
	item->index = to_index;
पूर्ण

अटल व्योम parman_prio_item_हटाओ(काष्ठा parman *parman,
				    काष्ठा parman_prio *prio,
				    काष्ठा parman_item *item)
अणु
	काष्ठा parman_item *last_item;
	अचिन्हित दीर्घ to_index;

	last_item = parman_prio_last_item(prio);
	अगर (last_item == item) अणु
		list_del(&item->list);
		वापस;
	पूर्ण
	to_index = item->index;
	__parman_prio_move(parman, prio, last_item, to_index, 1);
	list_del(&last_item->list);
	list_replace(&item->list, &last_item->list);
	last_item->index = to_index;
पूर्ण

अटल पूर्णांक parman_lsort_item_add(काष्ठा parman *parman,
				 काष्ठा parman_prio *prio,
				 काष्ठा parman_item *item)
अणु
	काष्ठा parman_prio *prio2;
	अचिन्हित दीर्घ new_index;
	पूर्णांक err;

	अगर (parman->count + 1 > parman->limit_count) अणु
		err = parman_enlarge(parman);
		अगर (err)
			वापस err;
	पूर्ण

	new_index = parman_lsort_new_index_find(parman, prio);
	list_क्रम_each_entry_reverse(prio2, &parman->prio_list, list) अणु
		अगर (prio2 == prio)
			अवरोध;
		parman_prio_shअगरt_करोwn(parman, prio2);
	पूर्ण
	item->index = new_index;
	list_add_tail(&item->list, &prio->item_list);
	parman->count++;
	वापस 0;
पूर्ण

अटल व्योम parman_lsort_item_हटाओ(काष्ठा parman *parman,
				     काष्ठा parman_prio *prio,
				     काष्ठा parman_item *item)
अणु
	parman_prio_item_हटाओ(parman, prio, item);
	list_क्रम_each_entry_जारी(prio, &parman->prio_list, list)
		parman_prio_shअगरt_up(parman, prio);
	parman->count--;
	अगर (parman->limit_count - parman->count >= parman->ops->resize_step)
		parman_shrink(parman);
पूर्ण

अटल स्थिर काष्ठा parman_algo parman_lsort = अणु
	.item_add	= parman_lsort_item_add,
	.item_हटाओ	= parman_lsort_item_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा parman_algo *parman_algos[] = अणु
	&parman_lsort,
पूर्ण;

/**
 * parman_create - creates a new parman instance
 * @ops:	caller-specअगरic callbacks
 * @priv:	poपूर्णांकer to a निजी data passed to the ops
 *
 * Note: all locking must be provided by the caller.
 *
 * Each parman instance manages an array area with chunks of entries
 * with the same priority. Consider following example:
 *
 * item 1 with prio 10
 * item 2 with prio 10
 * item 3 with prio 10
 * item 4 with prio 20
 * item 5 with prio 20
 * item 6 with prio 30
 * item 7 with prio 30
 * item 8 with prio 30
 *
 * In this example, there are 3 priority chunks. The order of the priorities
 * matters, however the order of items within a single priority chunk करोes not
 * matter. So the same array could be ordered as follows:
 *
 * item 2 with prio 10
 * item 3 with prio 10
 * item 1 with prio 10
 * item 5 with prio 20
 * item 4 with prio 20
 * item 7 with prio 30
 * item 8 with prio 30
 * item 6 with prio 30
 *
 * The goal of parman is to मुख्यtain the priority ordering. The caller
 * provides @ops with callbacks parman uses to move the items
 * and resize the array area.
 *
 * Returns a poपूर्णांकer to newly created parman instance in हाल of success,
 * otherwise it वापसs शून्य.
 */
काष्ठा parman *parman_create(स्थिर काष्ठा parman_ops *ops, व्योम *priv)
अणु
	काष्ठा parman *parman;

	parman = kzalloc(माप(*parman), GFP_KERNEL);
	अगर (!parman)
		वापस शून्य;
	INIT_LIST_HEAD(&parman->prio_list);
	parman->ops = ops;
	parman->priv = priv;
	parman->limit_count = ops->base_count;
	parman->algo = parman_algos[ops->algo];
	वापस parman;
पूर्ण
EXPORT_SYMBOL(parman_create);

/**
 * parman_destroy - destroys existing parman instance
 * @parman:	parman instance
 *
 * Note: all locking must be provided by the caller.
 */
व्योम parman_destroy(काष्ठा parman *parman)
अणु
	WARN_ON(!list_empty(&parman->prio_list));
	kमुक्त(parman);
पूर्ण
EXPORT_SYMBOL(parman_destroy);

/**
 * parman_prio_init - initializes a parman priority chunk
 * @parman:	parman instance
 * @prio:	parman prio काष्ठाure to be initialized
 * @priority:	desired priority of the chunk
 *
 * Note: all locking must be provided by the caller.
 *
 * Beक्रमe caller could add an item with certain priority, he has to
 * initialize a priority chunk क्रम it using this function.
 */
व्योम parman_prio_init(काष्ठा parman *parman, काष्ठा parman_prio *prio,
		      अचिन्हित दीर्घ priority)
अणु
	काष्ठा parman_prio *prio2;
	काष्ठा list_head *pos;

	INIT_LIST_HEAD(&prio->item_list);
	prio->priority = priority;

	/* Position inside the list according to priority */
	list_क्रम_each(pos, &parman->prio_list) अणु
		prio2 = list_entry(pos, typeof(*prio2), list);
		अगर (prio2->priority > prio->priority)
			अवरोध;
	पूर्ण
	list_add_tail(&prio->list, pos);
पूर्ण
EXPORT_SYMBOL(parman_prio_init);

/**
 * parman_prio_fini - finalizes use of parman priority chunk
 * @prio:	parman prio काष्ठाure
 *
 * Note: all locking must be provided by the caller.
 */
व्योम parman_prio_fini(काष्ठा parman_prio *prio)
अणु
	WARN_ON(parman_prio_used(prio));
	list_del(&prio->list);
पूर्ण
EXPORT_SYMBOL(parman_prio_fini);

/**
 * parman_item_add - adds a parman item under defined priority
 * @parman:	parman instance
 * @prio:	parman prio instance to add the item to
 * @item:	parman item instance
 *
 * Note: all locking must be provided by the caller.
 *
 * Adds item to a array managed by parman instance under the specअगरied priority.
 *
 * Returns 0 in हाल of success, negative number to indicate an error.
 */
पूर्णांक parman_item_add(काष्ठा parman *parman, काष्ठा parman_prio *prio,
		    काष्ठा parman_item *item)
अणु
	वापस parman->algo->item_add(parman, prio, item);
पूर्ण
EXPORT_SYMBOL(parman_item_add);

/**
 * parman_item_हटाओ - deletes parman item
 * @parman:	parman instance
 * @prio:	parman prio instance to delete the item from
 * @item:	parman item instance
 *
 * Note: all locking must be provided by the caller.
 */
व्योम parman_item_हटाओ(काष्ठा parman *parman, काष्ठा parman_prio *prio,
			काष्ठा parman_item *item)
अणु
	parman->algo->item_हटाओ(parman, prio, item);
पूर्ण
EXPORT_SYMBOL(parman_item_हटाओ);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Priority-based array manager");
