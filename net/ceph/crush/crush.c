<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_घोषित __KERNEL__
# include <linux/slab.h>
# include <linux/crush/crush.h>
#अन्यथा
# include "crush_compat.h"
# include "crush.h"
#पूर्ण_अगर

स्थिर अक्षर *crush_bucket_alg_name(पूर्णांक alg)
अणु
	चयन (alg) अणु
	हाल CRUSH_BUCKET_UNIFORM: वापस "uniform";
	हाल CRUSH_BUCKET_LIST: वापस "list";
	हाल CRUSH_BUCKET_TREE: वापस "tree";
	हाल CRUSH_BUCKET_STRAW: वापस "straw";
	हाल CRUSH_BUCKET_STRAW2: वापस "straw2";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण

/**
 * crush_get_bucket_item_weight - Get weight of an item in given bucket
 * @b: bucket poपूर्णांकer
 * @p: item index in bucket
 */
पूर्णांक crush_get_bucket_item_weight(स्थिर काष्ठा crush_bucket *b, पूर्णांक p)
अणु
	अगर ((__u32)p >= b->size)
		वापस 0;

	चयन (b->alg) अणु
	हाल CRUSH_BUCKET_UNIFORM:
		वापस ((काष्ठा crush_bucket_unअगरorm *)b)->item_weight;
	हाल CRUSH_BUCKET_LIST:
		वापस ((काष्ठा crush_bucket_list *)b)->item_weights[p];
	हाल CRUSH_BUCKET_TREE:
		वापस ((काष्ठा crush_bucket_tree *)b)->node_weights[crush_calc_tree_node(p)];
	हाल CRUSH_BUCKET_STRAW:
		वापस ((काष्ठा crush_bucket_straw *)b)->item_weights[p];
	हाल CRUSH_BUCKET_STRAW2:
		वापस ((काष्ठा crush_bucket_straw2 *)b)->item_weights[p];
	पूर्ण
	वापस 0;
पूर्ण

व्योम crush_destroy_bucket_unअगरorm(काष्ठा crush_bucket_unअगरorm *b)
अणु
	kमुक्त(b->h.items);
	kमुक्त(b);
पूर्ण

व्योम crush_destroy_bucket_list(काष्ठा crush_bucket_list *b)
अणु
	kमुक्त(b->item_weights);
	kमुक्त(b->sum_weights);
	kमुक्त(b->h.items);
	kमुक्त(b);
पूर्ण

व्योम crush_destroy_bucket_tree(काष्ठा crush_bucket_tree *b)
अणु
	kमुक्त(b->h.items);
	kमुक्त(b->node_weights);
	kमुक्त(b);
पूर्ण

व्योम crush_destroy_bucket_straw(काष्ठा crush_bucket_straw *b)
अणु
	kमुक्त(b->straws);
	kमुक्त(b->item_weights);
	kमुक्त(b->h.items);
	kमुक्त(b);
पूर्ण

व्योम crush_destroy_bucket_straw2(काष्ठा crush_bucket_straw2 *b)
अणु
	kमुक्त(b->item_weights);
	kमुक्त(b->h.items);
	kमुक्त(b);
पूर्ण

व्योम crush_destroy_bucket(काष्ठा crush_bucket *b)
अणु
	चयन (b->alg) अणु
	हाल CRUSH_BUCKET_UNIFORM:
		crush_destroy_bucket_unअगरorm((काष्ठा crush_bucket_unअगरorm *)b);
		अवरोध;
	हाल CRUSH_BUCKET_LIST:
		crush_destroy_bucket_list((काष्ठा crush_bucket_list *)b);
		अवरोध;
	हाल CRUSH_BUCKET_TREE:
		crush_destroy_bucket_tree((काष्ठा crush_bucket_tree *)b);
		अवरोध;
	हाल CRUSH_BUCKET_STRAW:
		crush_destroy_bucket_straw((काष्ठा crush_bucket_straw *)b);
		अवरोध;
	हाल CRUSH_BUCKET_STRAW2:
		crush_destroy_bucket_straw2((काष्ठा crush_bucket_straw2 *)b);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * crush_destroy - Destroy a crush_map
 * @map: crush_map poपूर्णांकer
 */
व्योम crush_destroy(काष्ठा crush_map *map)
अणु
	/* buckets */
	अगर (map->buckets) अणु
		__s32 b;
		क्रम (b = 0; b < map->max_buckets; b++) अणु
			अगर (map->buckets[b] == शून्य)
				जारी;
			crush_destroy_bucket(map->buckets[b]);
		पूर्ण
		kमुक्त(map->buckets);
	पूर्ण

	/* rules */
	अगर (map->rules) अणु
		__u32 b;
		क्रम (b = 0; b < map->max_rules; b++)
			crush_destroy_rule(map->rules[b]);
		kमुक्त(map->rules);
	पूर्ण

#अगर_अघोषित __KERNEL__
	kमुक्त(map->choose_tries);
#अन्यथा
	clear_crush_names(&map->type_names);
	clear_crush_names(&map->names);
	clear_choose_args(map);
#पूर्ण_अगर
	kमुक्त(map);
पूर्ण

व्योम crush_destroy_rule(काष्ठा crush_rule *rule)
अणु
	kमुक्त(rule);
पूर्ण
