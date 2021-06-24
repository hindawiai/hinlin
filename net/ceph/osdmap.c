<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/osdmap.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/crush/hash.h>
#समावेश <linux/crush/mapper.h>

अक्षर *ceph_osdmap_state_str(अक्षर *str, पूर्णांक len, u32 state)
अणु
	अगर (!len)
		वापस str;

	अगर ((state & CEPH_OSD_EXISTS) && (state & CEPH_OSD_UP))
		snम_लिखो(str, len, "exists, up");
	अन्यथा अगर (state & CEPH_OSD_EXISTS)
		snम_लिखो(str, len, "exists");
	अन्यथा अगर (state & CEPH_OSD_UP)
		snम_लिखो(str, len, "up");
	अन्यथा
		snम_लिखो(str, len, "doesn't exist");

	वापस str;
पूर्ण

/* maps */

अटल पूर्णांक calc_bits_of(अचिन्हित पूर्णांक t)
अणु
	पूर्णांक b = 0;
	जबतक (t) अणु
		t = t >> 1;
		b++;
	पूर्ण
	वापस b;
पूर्ण

/*
 * the foo_mask is the smallest value 2^n-1 that is >= foo.
 */
अटल व्योम calc_pg_masks(काष्ठा ceph_pg_pool_info *pi)
अणु
	pi->pg_num_mask = (1 << calc_bits_of(pi->pg_num-1)) - 1;
	pi->pgp_num_mask = (1 << calc_bits_of(pi->pgp_num-1)) - 1;
पूर्ण

/*
 * decode crush map
 */
अटल पूर्णांक crush_decode_unअगरorm_bucket(व्योम **p, व्योम *end,
				       काष्ठा crush_bucket_unअगरorm *b)
अणु
	करोut("crush_decode_uniform_bucket %p to %p\n", *p, end);
	ceph_decode_need(p, end, (1+b->h.size) * माप(u32), bad);
	b->item_weight = ceph_decode_32(p);
	वापस 0;
bad:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक crush_decode_list_bucket(व्योम **p, व्योम *end,
				    काष्ठा crush_bucket_list *b)
अणु
	पूर्णांक j;
	करोut("crush_decode_list_bucket %p to %p\n", *p, end);
	b->item_weights = kसुस्मृति(b->h.size, माप(u32), GFP_NOFS);
	अगर (b->item_weights == शून्य)
		वापस -ENOMEM;
	b->sum_weights = kसुस्मृति(b->h.size, माप(u32), GFP_NOFS);
	अगर (b->sum_weights == शून्य)
		वापस -ENOMEM;
	ceph_decode_need(p, end, 2 * b->h.size * माप(u32), bad);
	क्रम (j = 0; j < b->h.size; j++) अणु
		b->item_weights[j] = ceph_decode_32(p);
		b->sum_weights[j] = ceph_decode_32(p);
	पूर्ण
	वापस 0;
bad:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक crush_decode_tree_bucket(व्योम **p, व्योम *end,
				    काष्ठा crush_bucket_tree *b)
अणु
	पूर्णांक j;
	करोut("crush_decode_tree_bucket %p to %p\n", *p, end);
	ceph_decode_8_safe(p, end, b->num_nodes, bad);
	b->node_weights = kसुस्मृति(b->num_nodes, माप(u32), GFP_NOFS);
	अगर (b->node_weights == शून्य)
		वापस -ENOMEM;
	ceph_decode_need(p, end, b->num_nodes * माप(u32), bad);
	क्रम (j = 0; j < b->num_nodes; j++)
		b->node_weights[j] = ceph_decode_32(p);
	वापस 0;
bad:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक crush_decode_straw_bucket(व्योम **p, व्योम *end,
				     काष्ठा crush_bucket_straw *b)
अणु
	पूर्णांक j;
	करोut("crush_decode_straw_bucket %p to %p\n", *p, end);
	b->item_weights = kसुस्मृति(b->h.size, माप(u32), GFP_NOFS);
	अगर (b->item_weights == शून्य)
		वापस -ENOMEM;
	b->straws = kसुस्मृति(b->h.size, माप(u32), GFP_NOFS);
	अगर (b->straws == शून्य)
		वापस -ENOMEM;
	ceph_decode_need(p, end, 2 * b->h.size * माप(u32), bad);
	क्रम (j = 0; j < b->h.size; j++) अणु
		b->item_weights[j] = ceph_decode_32(p);
		b->straws[j] = ceph_decode_32(p);
	पूर्ण
	वापस 0;
bad:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक crush_decode_straw2_bucket(व्योम **p, व्योम *end,
				      काष्ठा crush_bucket_straw2 *b)
अणु
	पूर्णांक j;
	करोut("crush_decode_straw2_bucket %p to %p\n", *p, end);
	b->item_weights = kसुस्मृति(b->h.size, माप(u32), GFP_NOFS);
	अगर (b->item_weights == शून्य)
		वापस -ENOMEM;
	ceph_decode_need(p, end, b->h.size * माप(u32), bad);
	क्रम (j = 0; j < b->h.size; j++)
		b->item_weights[j] = ceph_decode_32(p);
	वापस 0;
bad:
	वापस -EINVAL;
पूर्ण

काष्ठा crush_name_node अणु
	काष्ठा rb_node cn_node;
	पूर्णांक cn_id;
	अक्षर cn_name[];
पूर्ण;

अटल काष्ठा crush_name_node *alloc_crush_name(माप_प्रकार name_len)
अणु
	काष्ठा crush_name_node *cn;

	cn = kदो_स्मृति(माप(*cn) + name_len + 1, GFP_NOIO);
	अगर (!cn)
		वापस शून्य;

	RB_CLEAR_NODE(&cn->cn_node);
	वापस cn;
पूर्ण

अटल व्योम मुक्त_crush_name(काष्ठा crush_name_node *cn)
अणु
	WARN_ON(!RB_EMPTY_NODE(&cn->cn_node));

	kमुक्त(cn);
पूर्ण

DEFINE_RB_FUNCS(crush_name, काष्ठा crush_name_node, cn_id, cn_node)

अटल पूर्णांक decode_crush_names(व्योम **p, व्योम *end, काष्ठा rb_root *root)
अणु
	u32 n;

	ceph_decode_32_safe(p, end, n, e_inval);
	जबतक (n--) अणु
		काष्ठा crush_name_node *cn;
		पूर्णांक id;
		u32 name_len;

		ceph_decode_32_safe(p, end, id, e_inval);
		ceph_decode_32_safe(p, end, name_len, e_inval);
		ceph_decode_need(p, end, name_len, e_inval);

		cn = alloc_crush_name(name_len);
		अगर (!cn)
			वापस -ENOMEM;

		cn->cn_id = id;
		स_नकल(cn->cn_name, *p, name_len);
		cn->cn_name[name_len] = '\0';
		*p += name_len;

		अगर (!__insert_crush_name(root, cn)) अणु
			मुक्त_crush_name(cn);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

व्योम clear_crush_names(काष्ठा rb_root *root)
अणु
	जबतक (!RB_EMPTY_ROOT(root)) अणु
		काष्ठा crush_name_node *cn =
		    rb_entry(rb_first(root), काष्ठा crush_name_node, cn_node);

		erase_crush_name(root, cn);
		मुक्त_crush_name(cn);
	पूर्ण
पूर्ण

अटल काष्ठा crush_choose_arg_map *alloc_choose_arg_map(व्योम)
अणु
	काष्ठा crush_choose_arg_map *arg_map;

	arg_map = kzalloc(माप(*arg_map), GFP_NOIO);
	अगर (!arg_map)
		वापस शून्य;

	RB_CLEAR_NODE(&arg_map->node);
	वापस arg_map;
पूर्ण

अटल व्योम मुक्त_choose_arg_map(काष्ठा crush_choose_arg_map *arg_map)
अणु
	अगर (arg_map) अणु
		पूर्णांक i, j;

		WARN_ON(!RB_EMPTY_NODE(&arg_map->node));

		क्रम (i = 0; i < arg_map->size; i++) अणु
			काष्ठा crush_choose_arg *arg = &arg_map->args[i];

			क्रम (j = 0; j < arg->weight_set_size; j++)
				kमुक्त(arg->weight_set[j].weights);
			kमुक्त(arg->weight_set);
			kमुक्त(arg->ids);
		पूर्ण
		kमुक्त(arg_map->args);
		kमुक्त(arg_map);
	पूर्ण
पूर्ण

DEFINE_RB_FUNCS(choose_arg_map, काष्ठा crush_choose_arg_map, choose_args_index,
		node);

व्योम clear_choose_args(काष्ठा crush_map *c)
अणु
	जबतक (!RB_EMPTY_ROOT(&c->choose_args)) अणु
		काष्ठा crush_choose_arg_map *arg_map =
		    rb_entry(rb_first(&c->choose_args),
			     काष्ठा crush_choose_arg_map, node);

		erase_choose_arg_map(&c->choose_args, arg_map);
		मुक्त_choose_arg_map(arg_map);
	पूर्ण
पूर्ण

अटल u32 *decode_array_32_alloc(व्योम **p, व्योम *end, u32 *plen)
अणु
	u32 *a = शून्य;
	u32 len;
	पूर्णांक ret;

	ceph_decode_32_safe(p, end, len, e_inval);
	अगर (len) अणु
		u32 i;

		a = kदो_स्मृति_array(len, माप(u32), GFP_NOIO);
		अगर (!a) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		ceph_decode_need(p, end, len * माप(u32), e_inval);
		क्रम (i = 0; i < len; i++)
			a[i] = ceph_decode_32(p);
	पूर्ण

	*plen = len;
	वापस a;

e_inval:
	ret = -EINVAL;
fail:
	kमुक्त(a);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Assumes @arg is zero-initialized.
 */
अटल पूर्णांक decode_choose_arg(व्योम **p, व्योम *end, काष्ठा crush_choose_arg *arg)
अणु
	पूर्णांक ret;

	ceph_decode_32_safe(p, end, arg->weight_set_size, e_inval);
	अगर (arg->weight_set_size) अणु
		u32 i;

		arg->weight_set = kदो_स्मृति_array(arg->weight_set_size,
						माप(*arg->weight_set),
						GFP_NOIO);
		अगर (!arg->weight_set)
			वापस -ENOMEM;

		क्रम (i = 0; i < arg->weight_set_size; i++) अणु
			काष्ठा crush_weight_set *w = &arg->weight_set[i];

			w->weights = decode_array_32_alloc(p, end, &w->size);
			अगर (IS_ERR(w->weights)) अणु
				ret = PTR_ERR(w->weights);
				w->weights = शून्य;
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	arg->ids = decode_array_32_alloc(p, end, &arg->ids_size);
	अगर (IS_ERR(arg->ids)) अणु
		ret = PTR_ERR(arg->ids);
		arg->ids = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक decode_choose_args(व्योम **p, व्योम *end, काष्ठा crush_map *c)
अणु
	काष्ठा crush_choose_arg_map *arg_map = शून्य;
	u32 num_choose_arg_maps, num_buckets;
	पूर्णांक ret;

	ceph_decode_32_safe(p, end, num_choose_arg_maps, e_inval);
	जबतक (num_choose_arg_maps--) अणु
		arg_map = alloc_choose_arg_map();
		अगर (!arg_map) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		ceph_decode_64_safe(p, end, arg_map->choose_args_index,
				    e_inval);
		arg_map->size = c->max_buckets;
		arg_map->args = kसुस्मृति(arg_map->size, माप(*arg_map->args),
					GFP_NOIO);
		अगर (!arg_map->args) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		ceph_decode_32_safe(p, end, num_buckets, e_inval);
		जबतक (num_buckets--) अणु
			काष्ठा crush_choose_arg *arg;
			u32 bucket_index;

			ceph_decode_32_safe(p, end, bucket_index, e_inval);
			अगर (bucket_index >= arg_map->size)
				जाओ e_inval;

			arg = &arg_map->args[bucket_index];
			ret = decode_choose_arg(p, end, arg);
			अगर (ret)
				जाओ fail;

			अगर (arg->ids_size &&
			    arg->ids_size != c->buckets[bucket_index]->size)
				जाओ e_inval;
		पूर्ण

		insert_choose_arg_map(&c->choose_args, arg_map);
	पूर्ण

	वापस 0;

e_inval:
	ret = -EINVAL;
fail:
	मुक्त_choose_arg_map(arg_map);
	वापस ret;
पूर्ण

अटल व्योम crush_finalize(काष्ठा crush_map *c)
अणु
	__s32 b;

	/* Space क्रम the array of poपूर्णांकers to per-bucket workspace */
	c->working_size = माप(काष्ठा crush_work) +
	    c->max_buckets * माप(काष्ठा crush_work_bucket *);

	क्रम (b = 0; b < c->max_buckets; b++) अणु
		अगर (!c->buckets[b])
			जारी;

		चयन (c->buckets[b]->alg) अणु
		शेष:
			/*
			 * The base हाल, permutation variables and
			 * the poपूर्णांकer to the permutation array.
			 */
			c->working_size += माप(काष्ठा crush_work_bucket);
			अवरोध;
		पूर्ण
		/* Every bucket has a permutation array. */
		c->working_size += c->buckets[b]->size * माप(__u32);
	पूर्ण
पूर्ण

अटल काष्ठा crush_map *crush_decode(व्योम *pbyval, व्योम *end)
अणु
	काष्ठा crush_map *c;
	पूर्णांक err;
	पूर्णांक i, j;
	व्योम **p = &pbyval;
	व्योम *start = pbyval;
	u32 magic;

	करोut("crush_decode %p to %p len %d\n", *p, end, (पूर्णांक)(end - *p));

	c = kzalloc(माप(*c), GFP_NOFS);
	अगर (c == शून्य)
		वापस ERR_PTR(-ENOMEM);

	c->type_names = RB_ROOT;
	c->names = RB_ROOT;
	c->choose_args = RB_ROOT;

        /* set tunables to शेष values */
        c->choose_local_tries = 2;
        c->choose_local_fallback_tries = 5;
        c->choose_total_tries = 19;
	c->chooseleaf_descend_once = 0;

	ceph_decode_need(p, end, 4*माप(u32), bad);
	magic = ceph_decode_32(p);
	अगर (magic != CRUSH_MAGIC) अणु
		pr_err("crush_decode magic %x != current %x\n",
		       (अचिन्हित पूर्णांक)magic, (अचिन्हित पूर्णांक)CRUSH_MAGIC);
		जाओ bad;
	पूर्ण
	c->max_buckets = ceph_decode_32(p);
	c->max_rules = ceph_decode_32(p);
	c->max_devices = ceph_decode_32(p);

	c->buckets = kसुस्मृति(c->max_buckets, माप(*c->buckets), GFP_NOFS);
	अगर (c->buckets == शून्य)
		जाओ badmem;
	c->rules = kसुस्मृति(c->max_rules, माप(*c->rules), GFP_NOFS);
	अगर (c->rules == शून्य)
		जाओ badmem;

	/* buckets */
	क्रम (i = 0; i < c->max_buckets; i++) अणु
		पूर्णांक size = 0;
		u32 alg;
		काष्ठा crush_bucket *b;

		ceph_decode_32_safe(p, end, alg, bad);
		अगर (alg == 0) अणु
			c->buckets[i] = शून्य;
			जारी;
		पूर्ण
		करोut("crush_decode bucket %d off %x %p to %p\n",
		     i, (पूर्णांक)(*p-start), *p, end);

		चयन (alg) अणु
		हाल CRUSH_BUCKET_UNIFORM:
			size = माप(काष्ठा crush_bucket_unअगरorm);
			अवरोध;
		हाल CRUSH_BUCKET_LIST:
			size = माप(काष्ठा crush_bucket_list);
			अवरोध;
		हाल CRUSH_BUCKET_TREE:
			size = माप(काष्ठा crush_bucket_tree);
			अवरोध;
		हाल CRUSH_BUCKET_STRAW:
			size = माप(काष्ठा crush_bucket_straw);
			अवरोध;
		हाल CRUSH_BUCKET_STRAW2:
			size = माप(काष्ठा crush_bucket_straw2);
			अवरोध;
		शेष:
			जाओ bad;
		पूर्ण
		BUG_ON(size == 0);
		b = c->buckets[i] = kzalloc(size, GFP_NOFS);
		अगर (b == शून्य)
			जाओ badmem;

		ceph_decode_need(p, end, 4*माप(u32), bad);
		b->id = ceph_decode_32(p);
		b->type = ceph_decode_16(p);
		b->alg = ceph_decode_8(p);
		b->hash = ceph_decode_8(p);
		b->weight = ceph_decode_32(p);
		b->size = ceph_decode_32(p);

		करोut("crush_decode bucket size %d off %x %p to %p\n",
		     b->size, (पूर्णांक)(*p-start), *p, end);

		b->items = kसुस्मृति(b->size, माप(__s32), GFP_NOFS);
		अगर (b->items == शून्य)
			जाओ badmem;

		ceph_decode_need(p, end, b->size*माप(u32), bad);
		क्रम (j = 0; j < b->size; j++)
			b->items[j] = ceph_decode_32(p);

		चयन (b->alg) अणु
		हाल CRUSH_BUCKET_UNIFORM:
			err = crush_decode_unअगरorm_bucket(p, end,
				  (काष्ठा crush_bucket_unअगरorm *)b);
			अगर (err < 0)
				जाओ fail;
			अवरोध;
		हाल CRUSH_BUCKET_LIST:
			err = crush_decode_list_bucket(p, end,
			       (काष्ठा crush_bucket_list *)b);
			अगर (err < 0)
				जाओ fail;
			अवरोध;
		हाल CRUSH_BUCKET_TREE:
			err = crush_decode_tree_bucket(p, end,
				(काष्ठा crush_bucket_tree *)b);
			अगर (err < 0)
				जाओ fail;
			अवरोध;
		हाल CRUSH_BUCKET_STRAW:
			err = crush_decode_straw_bucket(p, end,
				(काष्ठा crush_bucket_straw *)b);
			अगर (err < 0)
				जाओ fail;
			अवरोध;
		हाल CRUSH_BUCKET_STRAW2:
			err = crush_decode_straw2_bucket(p, end,
				(काष्ठा crush_bucket_straw2 *)b);
			अगर (err < 0)
				जाओ fail;
			अवरोध;
		पूर्ण
	पूर्ण

	/* rules */
	करोut("rule vec is %p\n", c->rules);
	क्रम (i = 0; i < c->max_rules; i++) अणु
		u32 yes;
		काष्ठा crush_rule *r;

		ceph_decode_32_safe(p, end, yes, bad);
		अगर (!yes) अणु
			करोut("crush_decode NO rule %d off %x %p to %p\n",
			     i, (पूर्णांक)(*p-start), *p, end);
			c->rules[i] = शून्य;
			जारी;
		पूर्ण

		करोut("crush_decode rule %d off %x %p to %p\n",
		     i, (पूर्णांक)(*p-start), *p, end);

		/* len */
		ceph_decode_32_safe(p, end, yes, bad);
#अगर BITS_PER_LONG == 32
		अगर (yes > (अच_दीर्घ_उच्च - माप(*r))
			  / माप(काष्ठा crush_rule_step))
			जाओ bad;
#पूर्ण_अगर
		r = kदो_स्मृति(काष्ठा_size(r, steps, yes), GFP_NOFS);
		c->rules[i] = r;
		अगर (r == शून्य)
			जाओ badmem;
		करोut(" rule %d is at %p\n", i, r);
		r->len = yes;
		ceph_decode_copy_safe(p, end, &r->mask, 4, bad); /* 4 u8's */
		ceph_decode_need(p, end, r->len*3*माप(u32), bad);
		क्रम (j = 0; j < r->len; j++) अणु
			r->steps[j].op = ceph_decode_32(p);
			r->steps[j].arg1 = ceph_decode_32(p);
			r->steps[j].arg2 = ceph_decode_32(p);
		पूर्ण
	पूर्ण

	err = decode_crush_names(p, end, &c->type_names);
	अगर (err)
		जाओ fail;

	err = decode_crush_names(p, end, &c->names);
	अगर (err)
		जाओ fail;

	ceph_decode_skip_map(p, end, 32, string, bad); /* rule_name_map */

        /* tunables */
        ceph_decode_need(p, end, 3*माप(u32), करोne);
        c->choose_local_tries = ceph_decode_32(p);
        c->choose_local_fallback_tries =  ceph_decode_32(p);
        c->choose_total_tries = ceph_decode_32(p);
        करोut("crush decode tunable choose_local_tries = %d\n",
             c->choose_local_tries);
        करोut("crush decode tunable choose_local_fallback_tries = %d\n",
             c->choose_local_fallback_tries);
        करोut("crush decode tunable choose_total_tries = %d\n",
             c->choose_total_tries);

	ceph_decode_need(p, end, माप(u32), करोne);
	c->chooseleaf_descend_once = ceph_decode_32(p);
	करोut("crush decode tunable chooseleaf_descend_once = %d\n",
	     c->chooseleaf_descend_once);

	ceph_decode_need(p, end, माप(u8), करोne);
	c->chooseleaf_vary_r = ceph_decode_8(p);
	करोut("crush decode tunable chooseleaf_vary_r = %d\n",
	     c->chooseleaf_vary_r);

	/* skip straw_calc_version, allowed_bucket_algs */
	ceph_decode_need(p, end, माप(u8) + माप(u32), करोne);
	*p += माप(u8) + माप(u32);

	ceph_decode_need(p, end, माप(u8), करोne);
	c->chooseleaf_stable = ceph_decode_8(p);
	करोut("crush decode tunable chooseleaf_stable = %d\n",
	     c->chooseleaf_stable);

	अगर (*p != end) अणु
		/* class_map */
		ceph_decode_skip_map(p, end, 32, 32, bad);
		/* class_name */
		ceph_decode_skip_map(p, end, 32, string, bad);
		/* class_bucket */
		ceph_decode_skip_map_of_map(p, end, 32, 32, 32, bad);
	पूर्ण

	अगर (*p != end) अणु
		err = decode_choose_args(p, end, c);
		अगर (err)
			जाओ fail;
	पूर्ण

करोne:
	crush_finalize(c);
	करोut("crush_decode success\n");
	वापस c;

badmem:
	err = -ENOMEM;
fail:
	करोut("crush_decode fail %d\n", err);
	crush_destroy(c);
	वापस ERR_PTR(err);

bad:
	err = -EINVAL;
	जाओ fail;
पूर्ण

पूर्णांक ceph_pg_compare(स्थिर काष्ठा ceph_pg *lhs, स्थिर काष्ठा ceph_pg *rhs)
अणु
	अगर (lhs->pool < rhs->pool)
		वापस -1;
	अगर (lhs->pool > rhs->pool)
		वापस 1;
	अगर (lhs->seed < rhs->seed)
		वापस -1;
	अगर (lhs->seed > rhs->seed)
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक ceph_spg_compare(स्थिर काष्ठा ceph_spg *lhs, स्थिर काष्ठा ceph_spg *rhs)
अणु
	पूर्णांक ret;

	ret = ceph_pg_compare(&lhs->pgid, &rhs->pgid);
	अगर (ret)
		वापस ret;

	अगर (lhs->shard < rhs->shard)
		वापस -1;
	अगर (lhs->shard > rhs->shard)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा ceph_pg_mapping *alloc_pg_mapping(माप_प्रकार payload_len)
अणु
	काष्ठा ceph_pg_mapping *pg;

	pg = kदो_स्मृति(माप(*pg) + payload_len, GFP_NOIO);
	अगर (!pg)
		वापस शून्य;

	RB_CLEAR_NODE(&pg->node);
	वापस pg;
पूर्ण

अटल व्योम मुक्त_pg_mapping(काष्ठा ceph_pg_mapping *pg)
अणु
	WARN_ON(!RB_EMPTY_NODE(&pg->node));

	kमुक्त(pg);
पूर्ण

/*
 * rbtree of pg_mapping क्रम handling pg_temp (explicit mapping of pgid
 * to a set of osds) and primary_temp (explicit primary setting)
 */
DEFINE_RB_FUNCS2(pg_mapping, काष्ठा ceph_pg_mapping, pgid, ceph_pg_compare,
		 RB_BYPTR, स्थिर काष्ठा ceph_pg *, node)

/*
 * rbtree of pg pool info
 */
DEFINE_RB_FUNCS(pg_pool, काष्ठा ceph_pg_pool_info, id, node)

काष्ठा ceph_pg_pool_info *ceph_pg_pool_by_id(काष्ठा ceph_osdmap *map, u64 id)
अणु
	वापस lookup_pg_pool(&map->pg_pools, id);
पूर्ण

स्थिर अक्षर *ceph_pg_pool_name_by_id(काष्ठा ceph_osdmap *map, u64 id)
अणु
	काष्ठा ceph_pg_pool_info *pi;

	अगर (id == CEPH_NOPOOL)
		वापस शून्य;

	अगर (WARN_ON_ONCE(id > (u64) पूर्णांक_उच्च))
		वापस शून्य;

	pi = lookup_pg_pool(&map->pg_pools, id);
	वापस pi ? pi->name : शून्य;
पूर्ण
EXPORT_SYMBOL(ceph_pg_pool_name_by_id);

पूर्णांक ceph_pg_poolid_by_name(काष्ठा ceph_osdmap *map, स्थिर अक्षर *name)
अणु
	काष्ठा rb_node *rbp;

	क्रम (rbp = rb_first(&map->pg_pools); rbp; rbp = rb_next(rbp)) अणु
		काष्ठा ceph_pg_pool_info *pi =
			rb_entry(rbp, काष्ठा ceph_pg_pool_info, node);
		अगर (pi->name && म_भेद(pi->name, name) == 0)
			वापस pi->id;
	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(ceph_pg_poolid_by_name);

u64 ceph_pg_pool_flags(काष्ठा ceph_osdmap *map, u64 id)
अणु
	काष्ठा ceph_pg_pool_info *pi;

	pi = lookup_pg_pool(&map->pg_pools, id);
	वापस pi ? pi->flags : 0;
पूर्ण
EXPORT_SYMBOL(ceph_pg_pool_flags);

अटल व्योम __हटाओ_pg_pool(काष्ठा rb_root *root, काष्ठा ceph_pg_pool_info *pi)
अणु
	erase_pg_pool(root, pi);
	kमुक्त(pi->name);
	kमुक्त(pi);
पूर्ण

अटल पूर्णांक decode_pool(व्योम **p, व्योम *end, काष्ठा ceph_pg_pool_info *pi)
अणु
	u8 ev, cv;
	अचिन्हित len, num;
	व्योम *pool_end;

	ceph_decode_need(p, end, 2 + 4, bad);
	ev = ceph_decode_8(p);  /* encoding version */
	cv = ceph_decode_8(p); /* compat version */
	अगर (ev < 5) अणु
		pr_warn("got v %d < 5 cv %d of ceph_pg_pool\n", ev, cv);
		वापस -EINVAL;
	पूर्ण
	अगर (cv > 9) अणु
		pr_warn("got v %d cv %d > 9 of ceph_pg_pool\n", ev, cv);
		वापस -EINVAL;
	पूर्ण
	len = ceph_decode_32(p);
	ceph_decode_need(p, end, len, bad);
	pool_end = *p + len;

	pi->type = ceph_decode_8(p);
	pi->size = ceph_decode_8(p);
	pi->crush_ruleset = ceph_decode_8(p);
	pi->object_hash = ceph_decode_8(p);

	pi->pg_num = ceph_decode_32(p);
	pi->pgp_num = ceph_decode_32(p);

	*p += 4 + 4;  /* skip lpg* */
	*p += 4;      /* skip last_change */
	*p += 8 + 4;  /* skip snap_seq, snap_epoch */

	/* skip snaps */
	num = ceph_decode_32(p);
	जबतक (num--) अणु
		*p += 8;  /* snapid key */
		*p += 1 + 1; /* versions */
		len = ceph_decode_32(p);
		*p += len;
	पूर्ण

	/* skip हटाओd_snaps */
	num = ceph_decode_32(p);
	*p += num * (8 + 8);

	*p += 8;  /* skip auid */
	pi->flags = ceph_decode_64(p);
	*p += 4;  /* skip crash_replay_पूर्णांकerval */

	अगर (ev >= 7)
		pi->min_size = ceph_decode_8(p);
	अन्यथा
		pi->min_size = pi->size - pi->size / 2;

	अगर (ev >= 8)
		*p += 8 + 8;  /* skip quota_max_* */

	अगर (ev >= 9) अणु
		/* skip tiers */
		num = ceph_decode_32(p);
		*p += num * 8;

		*p += 8;  /* skip tier_of */
		*p += 1;  /* skip cache_mode */

		pi->पढ़ो_tier = ceph_decode_64(p);
		pi->ग_लिखो_tier = ceph_decode_64(p);
	पूर्ण अन्यथा अणु
		pi->पढ़ो_tier = -1;
		pi->ग_लिखो_tier = -1;
	पूर्ण

	अगर (ev >= 10) अणु
		/* skip properties */
		num = ceph_decode_32(p);
		जबतक (num--) अणु
			len = ceph_decode_32(p);
			*p += len; /* key */
			len = ceph_decode_32(p);
			*p += len; /* val */
		पूर्ण
	पूर्ण

	अगर (ev >= 11) अणु
		/* skip hit_set_params */
		*p += 1 + 1; /* versions */
		len = ceph_decode_32(p);
		*p += len;

		*p += 4; /* skip hit_set_period */
		*p += 4; /* skip hit_set_count */
	पूर्ण

	अगर (ev >= 12)
		*p += 4; /* skip stripe_width */

	अगर (ev >= 13) अणु
		*p += 8; /* skip target_max_bytes */
		*p += 8; /* skip target_max_objects */
		*p += 4; /* skip cache_target_dirty_ratio_micro */
		*p += 4; /* skip cache_target_full_ratio_micro */
		*p += 4; /* skip cache_min_flush_age */
		*p += 4; /* skip cache_min_evict_age */
	पूर्ण

	अगर (ev >=  14) अणु
		/* skip erasure_code_profile */
		len = ceph_decode_32(p);
		*p += len;
	पूर्ण

	/*
	 * last_क्रमce_op_resend_preluminous, will be overridden अगर the
	 * map was encoded with RESEND_ON_SPLIT
	 */
	अगर (ev >= 15)
		pi->last_क्रमce_request_resend = ceph_decode_32(p);
	अन्यथा
		pi->last_क्रमce_request_resend = 0;

	अगर (ev >= 16)
		*p += 4; /* skip min_पढ़ो_recency_क्रम_promote */

	अगर (ev >= 17)
		*p += 8; /* skip expected_num_objects */

	अगर (ev >= 19)
		*p += 4; /* skip cache_target_dirty_high_ratio_micro */

	अगर (ev >= 20)
		*p += 4; /* skip min_ग_लिखो_recency_क्रम_promote */

	अगर (ev >= 21)
		*p += 1; /* skip use_gmt_hitset */

	अगर (ev >= 22)
		*p += 1; /* skip fast_पढ़ो */

	अगर (ev >= 23) अणु
		*p += 4; /* skip hit_set_grade_decay_rate */
		*p += 4; /* skip hit_set_search_last_n */
	पूर्ण

	अगर (ev >= 24) अणु
		/* skip opts */
		*p += 1 + 1; /* versions */
		len = ceph_decode_32(p);
		*p += len;
	पूर्ण

	अगर (ev >= 25)
		pi->last_क्रमce_request_resend = ceph_decode_32(p);

	/* ignore the rest */

	*p = pool_end;
	calc_pg_masks(pi);
	वापस 0;

bad:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक decode_pool_names(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	काष्ठा ceph_pg_pool_info *pi;
	u32 num, len;
	u64 pool;

	ceph_decode_32_safe(p, end, num, bad);
	करोut(" %d pool names\n", num);
	जबतक (num--) अणु
		ceph_decode_64_safe(p, end, pool, bad);
		ceph_decode_32_safe(p, end, len, bad);
		करोut("  pool %llu len %d\n", pool, len);
		ceph_decode_need(p, end, len, bad);
		pi = lookup_pg_pool(&map->pg_pools, pool);
		अगर (pi) अणु
			अक्षर *name = kstrndup(*p, len, GFP_NOFS);

			अगर (!name)
				वापस -ENOMEM;
			kमुक्त(pi->name);
			pi->name = name;
			करोut("  name is %s\n", pi->name);
		पूर्ण
		*p += len;
	पूर्ण
	वापस 0;

bad:
	वापस -EINVAL;
पूर्ण

/*
 * CRUSH workspaces
 *
 * workspace_manager framework borrowed from fs/btrfs/compression.c.
 * Two simplअगरications: there is only one type of workspace and there
 * is always at least one workspace.
 */
अटल काष्ठा crush_work *alloc_workspace(स्थिर काष्ठा crush_map *c)
अणु
	काष्ठा crush_work *work;
	माप_प्रकार work_size;

	WARN_ON(!c->working_size);
	work_size = crush_work_size(c, CEPH_PG_MAX_SIZE);
	करोut("%s work_size %zu bytes\n", __func__, work_size);

	work = ceph_kvदो_स्मृति(work_size, GFP_NOIO);
	अगर (!work)
		वापस शून्य;

	INIT_LIST_HEAD(&work->item);
	crush_init_workspace(c, work);
	वापस work;
पूर्ण

अटल व्योम मुक्त_workspace(काष्ठा crush_work *work)
अणु
	WARN_ON(!list_empty(&work->item));
	kvमुक्त(work);
पूर्ण

अटल व्योम init_workspace_manager(काष्ठा workspace_manager *wsm)
अणु
	INIT_LIST_HEAD(&wsm->idle_ws);
	spin_lock_init(&wsm->ws_lock);
	atomic_set(&wsm->total_ws, 0);
	wsm->मुक्त_ws = 0;
	init_रुकोqueue_head(&wsm->ws_रुको);
पूर्ण

अटल व्योम add_initial_workspace(काष्ठा workspace_manager *wsm,
				  काष्ठा crush_work *work)
अणु
	WARN_ON(!list_empty(&wsm->idle_ws));

	list_add(&work->item, &wsm->idle_ws);
	atomic_set(&wsm->total_ws, 1);
	wsm->मुक्त_ws = 1;
पूर्ण

अटल व्योम cleanup_workspace_manager(काष्ठा workspace_manager *wsm)
अणु
	काष्ठा crush_work *work;

	जबतक (!list_empty(&wsm->idle_ws)) अणु
		work = list_first_entry(&wsm->idle_ws, काष्ठा crush_work,
					item);
		list_del_init(&work->item);
		मुक्त_workspace(work);
	पूर्ण
	atomic_set(&wsm->total_ws, 0);
	wsm->मुक्त_ws = 0;
पूर्ण

/*
 * Finds an available workspace or allocates a new one.  If it's not
 * possible to allocate a new one, रुकोs until there is one.
 */
अटल काष्ठा crush_work *get_workspace(काष्ठा workspace_manager *wsm,
					स्थिर काष्ठा crush_map *c)
अणु
	काष्ठा crush_work *work;
	पूर्णांक cpus = num_online_cpus();

again:
	spin_lock(&wsm->ws_lock);
	अगर (!list_empty(&wsm->idle_ws)) अणु
		work = list_first_entry(&wsm->idle_ws, काष्ठा crush_work,
					item);
		list_del_init(&work->item);
		wsm->मुक्त_ws--;
		spin_unlock(&wsm->ws_lock);
		वापस work;

	पूर्ण
	अगर (atomic_पढ़ो(&wsm->total_ws) > cpus) अणु
		DEFINE_WAIT(रुको);

		spin_unlock(&wsm->ws_lock);
		prepare_to_रुको(&wsm->ws_रुको, &रुको, TASK_UNINTERRUPTIBLE);
		अगर (atomic_पढ़ो(&wsm->total_ws) > cpus && !wsm->मुक्त_ws)
			schedule();
		finish_रुको(&wsm->ws_रुको, &रुको);
		जाओ again;
	पूर्ण
	atomic_inc(&wsm->total_ws);
	spin_unlock(&wsm->ws_lock);

	work = alloc_workspace(c);
	अगर (!work) अणु
		atomic_dec(&wsm->total_ws);
		wake_up(&wsm->ws_रुको);

		/*
		 * Do not वापस the error but go back to रुकोing.  We
		 * have the initial workspace and the CRUSH computation
		 * समय is bounded so we will get it eventually.
		 */
		WARN_ON(atomic_पढ़ो(&wsm->total_ws) < 1);
		जाओ again;
	पूर्ण
	वापस work;
पूर्ण

/*
 * Puts a workspace back on the list or मुक्तs it अगर we have enough
 * idle ones sitting around.
 */
अटल व्योम put_workspace(काष्ठा workspace_manager *wsm,
			  काष्ठा crush_work *work)
अणु
	spin_lock(&wsm->ws_lock);
	अगर (wsm->मुक्त_ws <= num_online_cpus()) अणु
		list_add(&work->item, &wsm->idle_ws);
		wsm->मुक्त_ws++;
		spin_unlock(&wsm->ws_lock);
		जाओ wake;
	पूर्ण
	spin_unlock(&wsm->ws_lock);

	मुक्त_workspace(work);
	atomic_dec(&wsm->total_ws);
wake:
	अगर (wq_has_sleeper(&wsm->ws_रुको))
		wake_up(&wsm->ws_रुको);
पूर्ण

/*
 * osd map
 */
काष्ठा ceph_osdmap *ceph_osdmap_alloc(व्योम)
अणु
	काष्ठा ceph_osdmap *map;

	map = kzalloc(माप(*map), GFP_NOIO);
	अगर (!map)
		वापस शून्य;

	map->pg_pools = RB_ROOT;
	map->pool_max = -1;
	map->pg_temp = RB_ROOT;
	map->primary_temp = RB_ROOT;
	map->pg_upmap = RB_ROOT;
	map->pg_upmap_items = RB_ROOT;

	init_workspace_manager(&map->crush_wsm);

	वापस map;
पूर्ण

व्योम ceph_osdmap_destroy(काष्ठा ceph_osdmap *map)
अणु
	करोut("osdmap_destroy %p\n", map);

	अगर (map->crush)
		crush_destroy(map->crush);
	cleanup_workspace_manager(&map->crush_wsm);

	जबतक (!RB_EMPTY_ROOT(&map->pg_temp)) अणु
		काष्ठा ceph_pg_mapping *pg =
			rb_entry(rb_first(&map->pg_temp),
				 काष्ठा ceph_pg_mapping, node);
		erase_pg_mapping(&map->pg_temp, pg);
		मुक्त_pg_mapping(pg);
	पूर्ण
	जबतक (!RB_EMPTY_ROOT(&map->primary_temp)) अणु
		काष्ठा ceph_pg_mapping *pg =
			rb_entry(rb_first(&map->primary_temp),
				 काष्ठा ceph_pg_mapping, node);
		erase_pg_mapping(&map->primary_temp, pg);
		मुक्त_pg_mapping(pg);
	पूर्ण
	जबतक (!RB_EMPTY_ROOT(&map->pg_upmap)) अणु
		काष्ठा ceph_pg_mapping *pg =
			rb_entry(rb_first(&map->pg_upmap),
				 काष्ठा ceph_pg_mapping, node);
		rb_erase(&pg->node, &map->pg_upmap);
		kमुक्त(pg);
	पूर्ण
	जबतक (!RB_EMPTY_ROOT(&map->pg_upmap_items)) अणु
		काष्ठा ceph_pg_mapping *pg =
			rb_entry(rb_first(&map->pg_upmap_items),
				 काष्ठा ceph_pg_mapping, node);
		rb_erase(&pg->node, &map->pg_upmap_items);
		kमुक्त(pg);
	पूर्ण
	जबतक (!RB_EMPTY_ROOT(&map->pg_pools)) अणु
		काष्ठा ceph_pg_pool_info *pi =
			rb_entry(rb_first(&map->pg_pools),
				 काष्ठा ceph_pg_pool_info, node);
		__हटाओ_pg_pool(&map->pg_pools, pi);
	पूर्ण
	kvमुक्त(map->osd_state);
	kvमुक्त(map->osd_weight);
	kvमुक्त(map->osd_addr);
	kvमुक्त(map->osd_primary_affinity);
	kमुक्त(map);
पूर्ण

/*
 * Adjust max_osd value, (re)allocate arrays.
 *
 * The new elements are properly initialized.
 */
अटल पूर्णांक osdmap_set_max_osd(काष्ठा ceph_osdmap *map, u32 max)
अणु
	u32 *state;
	u32 *weight;
	काष्ठा ceph_entity_addr *addr;
	u32 to_copy;
	पूर्णांक i;

	करोut("%s old %u new %u\n", __func__, map->max_osd, max);
	अगर (max == map->max_osd)
		वापस 0;

	state = ceph_kvदो_स्मृति(array_size(max, माप(*state)), GFP_NOFS);
	weight = ceph_kvदो_स्मृति(array_size(max, माप(*weight)), GFP_NOFS);
	addr = ceph_kvदो_स्मृति(array_size(max, माप(*addr)), GFP_NOFS);
	अगर (!state || !weight || !addr) अणु
		kvमुक्त(state);
		kvमुक्त(weight);
		kvमुक्त(addr);
		वापस -ENOMEM;
	पूर्ण

	to_copy = min(map->max_osd, max);
	अगर (map->osd_state) अणु
		स_नकल(state, map->osd_state, to_copy * माप(*state));
		स_नकल(weight, map->osd_weight, to_copy * माप(*weight));
		स_नकल(addr, map->osd_addr, to_copy * माप(*addr));
		kvमुक्त(map->osd_state);
		kvमुक्त(map->osd_weight);
		kvमुक्त(map->osd_addr);
	पूर्ण

	map->osd_state = state;
	map->osd_weight = weight;
	map->osd_addr = addr;
	क्रम (i = map->max_osd; i < max; i++) अणु
		map->osd_state[i] = 0;
		map->osd_weight[i] = CEPH_OSD_OUT;
		स_रखो(map->osd_addr + i, 0, माप(*map->osd_addr));
	पूर्ण

	अगर (map->osd_primary_affinity) अणु
		u32 *affinity;

		affinity = ceph_kvदो_स्मृति(array_size(max, माप(*affinity)),
					 GFP_NOFS);
		अगर (!affinity)
			वापस -ENOMEM;

		स_नकल(affinity, map->osd_primary_affinity,
		       to_copy * माप(*affinity));
		kvमुक्त(map->osd_primary_affinity);

		map->osd_primary_affinity = affinity;
		क्रम (i = map->max_osd; i < max; i++)
			map->osd_primary_affinity[i] =
			    CEPH_OSD_DEFAULT_PRIMARY_AFFINITY;
	पूर्ण

	map->max_osd = max;

	वापस 0;
पूर्ण

अटल पूर्णांक osdmap_set_crush(काष्ठा ceph_osdmap *map, काष्ठा crush_map *crush)
अणु
	काष्ठा crush_work *work;

	अगर (IS_ERR(crush))
		वापस PTR_ERR(crush);

	work = alloc_workspace(crush);
	अगर (!work) अणु
		crush_destroy(crush);
		वापस -ENOMEM;
	पूर्ण

	अगर (map->crush)
		crush_destroy(map->crush);
	cleanup_workspace_manager(&map->crush_wsm);
	map->crush = crush;
	add_initial_workspace(&map->crush_wsm, work);
	वापस 0;
पूर्ण

#घोषणा OSDMAP_WRAPPER_COMPAT_VER	7
#घोषणा OSDMAP_CLIENT_DATA_COMPAT_VER	1

/*
 * Return 0 or error.  On success, *v is set to 0 क्रम old (v6) osdmaps,
 * to काष्ठा_v of the client_data section क्रम new (v7 and above)
 * osdmaps.
 */
अटल पूर्णांक get_osdmap_client_data_v(व्योम **p, व्योम *end,
				    स्थिर अक्षर *prefix, u8 *v)
अणु
	u8 काष्ठा_v;

	ceph_decode_8_safe(p, end, काष्ठा_v, e_inval);
	अगर (काष्ठा_v >= 7) अणु
		u8 काष्ठा_compat;

		ceph_decode_8_safe(p, end, काष्ठा_compat, e_inval);
		अगर (काष्ठा_compat > OSDMAP_WRAPPER_COMPAT_VER) अणु
			pr_warn("got v %d cv %d > %d of %s ceph_osdmap\n",
				काष्ठा_v, काष्ठा_compat,
				OSDMAP_WRAPPER_COMPAT_VER, prefix);
			वापस -EINVAL;
		पूर्ण
		*p += 4; /* ignore wrapper काष्ठा_len */

		ceph_decode_8_safe(p, end, काष्ठा_v, e_inval);
		ceph_decode_8_safe(p, end, काष्ठा_compat, e_inval);
		अगर (काष्ठा_compat > OSDMAP_CLIENT_DATA_COMPAT_VER) अणु
			pr_warn("got v %d cv %d > %d of %s ceph_osdmap client data\n",
				काष्ठा_v, काष्ठा_compat,
				OSDMAP_CLIENT_DATA_COMPAT_VER, prefix);
			वापस -EINVAL;
		पूर्ण
		*p += 4; /* ignore client data काष्ठा_len */
	पूर्ण अन्यथा अणु
		u16 version;

		*p -= 1;
		ceph_decode_16_safe(p, end, version, e_inval);
		अगर (version < 6) अणु
			pr_warn("got v %d < 6 of %s ceph_osdmap\n",
				version, prefix);
			वापस -EINVAL;
		पूर्ण

		/* old osdmap enconding */
		काष्ठा_v = 0;
	पूर्ण

	*v = काष्ठा_v;
	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __decode_pools(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map,
			  bool incremental)
अणु
	u32 n;

	ceph_decode_32_safe(p, end, n, e_inval);
	जबतक (n--) अणु
		काष्ठा ceph_pg_pool_info *pi;
		u64 pool;
		पूर्णांक ret;

		ceph_decode_64_safe(p, end, pool, e_inval);

		pi = lookup_pg_pool(&map->pg_pools, pool);
		अगर (!incremental || !pi) अणु
			pi = kzalloc(माप(*pi), GFP_NOFS);
			अगर (!pi)
				वापस -ENOMEM;

			RB_CLEAR_NODE(&pi->node);
			pi->id = pool;

			अगर (!__insert_pg_pool(&map->pg_pools, pi)) अणु
				kमुक्त(pi);
				वापस -EEXIST;
			पूर्ण
		पूर्ण

		ret = decode_pool(p, end, pi);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक decode_pools(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस __decode_pools(p, end, map, false);
पूर्ण

अटल पूर्णांक decode_new_pools(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस __decode_pools(p, end, map, true);
पूर्ण

प्रकार काष्ठा ceph_pg_mapping *(*decode_mapping_fn_t)(व्योम **, व्योम *, bool);

अटल पूर्णांक decode_pg_mapping(व्योम **p, व्योम *end, काष्ठा rb_root *mapping_root,
			     decode_mapping_fn_t fn, bool incremental)
अणु
	u32 n;

	WARN_ON(!incremental && !fn);

	ceph_decode_32_safe(p, end, n, e_inval);
	जबतक (n--) अणु
		काष्ठा ceph_pg_mapping *pg;
		काष्ठा ceph_pg pgid;
		पूर्णांक ret;

		ret = ceph_decode_pgid(p, end, &pgid);
		अगर (ret)
			वापस ret;

		pg = lookup_pg_mapping(mapping_root, &pgid);
		अगर (pg) अणु
			WARN_ON(!incremental);
			erase_pg_mapping(mapping_root, pg);
			मुक्त_pg_mapping(pg);
		पूर्ण

		अगर (fn) अणु
			pg = fn(p, end, incremental);
			अगर (IS_ERR(pg))
				वापस PTR_ERR(pg);

			अगर (pg) अणु
				pg->pgid = pgid; /* काष्ठा */
				insert_pg_mapping(mapping_root, pg);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल काष्ठा ceph_pg_mapping *__decode_pg_temp(व्योम **p, व्योम *end,
						bool incremental)
अणु
	काष्ठा ceph_pg_mapping *pg;
	u32 len, i;

	ceph_decode_32_safe(p, end, len, e_inval);
	अगर (len == 0 && incremental)
		वापस शून्य;	/* new_pg_temp: [] to हटाओ */
	अगर (len > (SIZE_MAX - माप(*pg)) / माप(u32))
		वापस ERR_PTR(-EINVAL);

	ceph_decode_need(p, end, len * माप(u32), e_inval);
	pg = alloc_pg_mapping(len * माप(u32));
	अगर (!pg)
		वापस ERR_PTR(-ENOMEM);

	pg->pg_temp.len = len;
	क्रम (i = 0; i < len; i++)
		pg->pg_temp.osds[i] = ceph_decode_32(p);

	वापस pg;

e_inval:
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक decode_pg_temp(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->pg_temp, __decode_pg_temp,
				 false);
पूर्ण

अटल पूर्णांक decode_new_pg_temp(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->pg_temp, __decode_pg_temp,
				 true);
पूर्ण

अटल काष्ठा ceph_pg_mapping *__decode_primary_temp(व्योम **p, व्योम *end,
						     bool incremental)
अणु
	काष्ठा ceph_pg_mapping *pg;
	u32 osd;

	ceph_decode_32_safe(p, end, osd, e_inval);
	अगर (osd == (u32)-1 && incremental)
		वापस शून्य;	/* new_primary_temp: -1 to हटाओ */

	pg = alloc_pg_mapping(0);
	अगर (!pg)
		वापस ERR_PTR(-ENOMEM);

	pg->primary_temp.osd = osd;
	वापस pg;

e_inval:
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक decode_primary_temp(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->primary_temp,
				 __decode_primary_temp, false);
पूर्ण

अटल पूर्णांक decode_new_primary_temp(व्योम **p, व्योम *end,
				   काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->primary_temp,
				 __decode_primary_temp, true);
पूर्ण

u32 ceph_get_primary_affinity(काष्ठा ceph_osdmap *map, पूर्णांक osd)
अणु
	BUG_ON(osd >= map->max_osd);

	अगर (!map->osd_primary_affinity)
		वापस CEPH_OSD_DEFAULT_PRIMARY_AFFINITY;

	वापस map->osd_primary_affinity[osd];
पूर्ण

अटल पूर्णांक set_primary_affinity(काष्ठा ceph_osdmap *map, पूर्णांक osd, u32 aff)
अणु
	BUG_ON(osd >= map->max_osd);

	अगर (!map->osd_primary_affinity) अणु
		पूर्णांक i;

		map->osd_primary_affinity = ceph_kvदो_स्मृति(
		    array_size(map->max_osd, माप(*map->osd_primary_affinity)),
		    GFP_NOFS);
		अगर (!map->osd_primary_affinity)
			वापस -ENOMEM;

		क्रम (i = 0; i < map->max_osd; i++)
			map->osd_primary_affinity[i] =
			    CEPH_OSD_DEFAULT_PRIMARY_AFFINITY;
	पूर्ण

	map->osd_primary_affinity[osd] = aff;

	वापस 0;
पूर्ण

अटल पूर्णांक decode_primary_affinity(व्योम **p, व्योम *end,
				   काष्ठा ceph_osdmap *map)
अणु
	u32 len, i;

	ceph_decode_32_safe(p, end, len, e_inval);
	अगर (len == 0) अणु
		kvमुक्त(map->osd_primary_affinity);
		map->osd_primary_affinity = शून्य;
		वापस 0;
	पूर्ण
	अगर (len != map->max_osd)
		जाओ e_inval;

	ceph_decode_need(p, end, map->max_osd*माप(u32), e_inval);

	क्रम (i = 0; i < map->max_osd; i++) अणु
		पूर्णांक ret;

		ret = set_primary_affinity(map, i, ceph_decode_32(p));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक decode_new_primary_affinity(व्योम **p, व्योम *end,
				       काष्ठा ceph_osdmap *map)
अणु
	u32 n;

	ceph_decode_32_safe(p, end, n, e_inval);
	जबतक (n--) अणु
		u32 osd, aff;
		पूर्णांक ret;

		ceph_decode_32_safe(p, end, osd, e_inval);
		ceph_decode_32_safe(p, end, aff, e_inval);

		ret = set_primary_affinity(map, osd, aff);
		अगर (ret)
			वापस ret;

		pr_info("osd%d primary-affinity 0x%x\n", osd, aff);
	पूर्ण

	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

अटल काष्ठा ceph_pg_mapping *__decode_pg_upmap(व्योम **p, व्योम *end,
						 bool __unused)
अणु
	वापस __decode_pg_temp(p, end, false);
पूर्ण

अटल पूर्णांक decode_pg_upmap(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->pg_upmap, __decode_pg_upmap,
				 false);
पूर्ण

अटल पूर्णांक decode_new_pg_upmap(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->pg_upmap, __decode_pg_upmap,
				 true);
पूर्ण

अटल पूर्णांक decode_old_pg_upmap(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->pg_upmap, शून्य, true);
पूर्ण

अटल काष्ठा ceph_pg_mapping *__decode_pg_upmap_items(व्योम **p, व्योम *end,
						       bool __unused)
अणु
	काष्ठा ceph_pg_mapping *pg;
	u32 len, i;

	ceph_decode_32_safe(p, end, len, e_inval);
	अगर (len > (SIZE_MAX - माप(*pg)) / (2 * माप(u32)))
		वापस ERR_PTR(-EINVAL);

	ceph_decode_need(p, end, 2 * len * माप(u32), e_inval);
	pg = alloc_pg_mapping(2 * len * माप(u32));
	अगर (!pg)
		वापस ERR_PTR(-ENOMEM);

	pg->pg_upmap_items.len = len;
	क्रम (i = 0; i < len; i++) अणु
		pg->pg_upmap_items.from_to[i][0] = ceph_decode_32(p);
		pg->pg_upmap_items.from_to[i][1] = ceph_decode_32(p);
	पूर्ण

	वापस pg;

e_inval:
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक decode_pg_upmap_items(व्योम **p, व्योम *end, काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->pg_upmap_items,
				 __decode_pg_upmap_items, false);
पूर्ण

अटल पूर्णांक decode_new_pg_upmap_items(व्योम **p, व्योम *end,
				     काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->pg_upmap_items,
				 __decode_pg_upmap_items, true);
पूर्ण

अटल पूर्णांक decode_old_pg_upmap_items(व्योम **p, व्योम *end,
				     काष्ठा ceph_osdmap *map)
अणु
	वापस decode_pg_mapping(p, end, &map->pg_upmap_items, शून्य, true);
पूर्ण

/*
 * decode a full map.
 */
अटल पूर्णांक osdmap_decode(व्योम **p, व्योम *end, bool msgr2,
			 काष्ठा ceph_osdmap *map)
अणु
	u8 काष्ठा_v;
	u32 epoch = 0;
	व्योम *start = *p;
	u32 max;
	u32 len, i;
	पूर्णांक err;

	करोut("%s %p to %p len %d\n", __func__, *p, end, (पूर्णांक)(end - *p));

	err = get_osdmap_client_data_v(p, end, "full", &काष्ठा_v);
	अगर (err)
		जाओ bad;

	/* fsid, epoch, created, modअगरied */
	ceph_decode_need(p, end, माप(map->fsid) + माप(u32) +
			 माप(map->created) + माप(map->modअगरied), e_inval);
	ceph_decode_copy(p, &map->fsid, माप(map->fsid));
	epoch = map->epoch = ceph_decode_32(p);
	ceph_decode_copy(p, &map->created, माप(map->created));
	ceph_decode_copy(p, &map->modअगरied, माप(map->modअगरied));

	/* pools */
	err = decode_pools(p, end, map);
	अगर (err)
		जाओ bad;

	/* pool_name */
	err = decode_pool_names(p, end, map);
	अगर (err)
		जाओ bad;

	ceph_decode_32_safe(p, end, map->pool_max, e_inval);

	ceph_decode_32_safe(p, end, map->flags, e_inval);

	/* max_osd */
	ceph_decode_32_safe(p, end, max, e_inval);

	/* (re)alloc osd arrays */
	err = osdmap_set_max_osd(map, max);
	अगर (err)
		जाओ bad;

	/* osd_state, osd_weight, osd_addrs->client_addr */
	ceph_decode_need(p, end, 3*माप(u32) +
			 map->max_osd*(काष्ठा_v >= 5 ? माप(u32) :
						       माप(u8)) +
				       माप(*map->osd_weight), e_inval);
	अगर (ceph_decode_32(p) != map->max_osd)
		जाओ e_inval;

	अगर (काष्ठा_v >= 5) अणु
		क्रम (i = 0; i < map->max_osd; i++)
			map->osd_state[i] = ceph_decode_32(p);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < map->max_osd; i++)
			map->osd_state[i] = ceph_decode_8(p);
	पूर्ण

	अगर (ceph_decode_32(p) != map->max_osd)
		जाओ e_inval;

	क्रम (i = 0; i < map->max_osd; i++)
		map->osd_weight[i] = ceph_decode_32(p);

	अगर (ceph_decode_32(p) != map->max_osd)
		जाओ e_inval;

	क्रम (i = 0; i < map->max_osd; i++) अणु
		काष्ठा ceph_entity_addr *addr = &map->osd_addr[i];

		अगर (काष्ठा_v >= 8)
			err = ceph_decode_entity_addrvec(p, end, msgr2, addr);
		अन्यथा
			err = ceph_decode_entity_addr(p, end, addr);
		अगर (err)
			जाओ bad;

		करोut("%s osd%d addr %s\n", __func__, i, ceph_pr_addr(addr));
	पूर्ण

	/* pg_temp */
	err = decode_pg_temp(p, end, map);
	अगर (err)
		जाओ bad;

	/* primary_temp */
	अगर (काष्ठा_v >= 1) अणु
		err = decode_primary_temp(p, end, map);
		अगर (err)
			जाओ bad;
	पूर्ण

	/* primary_affinity */
	अगर (काष्ठा_v >= 2) अणु
		err = decode_primary_affinity(p, end, map);
		अगर (err)
			जाओ bad;
	पूर्ण अन्यथा अणु
		WARN_ON(map->osd_primary_affinity);
	पूर्ण

	/* crush */
	ceph_decode_32_safe(p, end, len, e_inval);
	err = osdmap_set_crush(map, crush_decode(*p, min(*p + len, end)));
	अगर (err)
		जाओ bad;

	*p += len;
	अगर (काष्ठा_v >= 3) अणु
		/* erasure_code_profiles */
		ceph_decode_skip_map_of_map(p, end, string, string, string,
					    e_inval);
	पूर्ण

	अगर (काष्ठा_v >= 4) अणु
		err = decode_pg_upmap(p, end, map);
		अगर (err)
			जाओ bad;

		err = decode_pg_upmap_items(p, end, map);
		अगर (err)
			जाओ bad;
	पूर्ण अन्यथा अणु
		WARN_ON(!RB_EMPTY_ROOT(&map->pg_upmap));
		WARN_ON(!RB_EMPTY_ROOT(&map->pg_upmap_items));
	पूर्ण

	/* ignore the rest */
	*p = end;

	करोut("full osdmap epoch %d max_osd %d\n", map->epoch, map->max_osd);
	वापस 0;

e_inval:
	err = -EINVAL;
bad:
	pr_err("corrupt full osdmap (%d) epoch %d off %d (%p of %p-%p)\n",
	       err, epoch, (पूर्णांक)(*p - start), *p, start, end);
	prपूर्णांक_hex_dump(KERN_DEBUG, "osdmap: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       start, end - start, true);
	वापस err;
पूर्ण

/*
 * Allocate and decode a full map.
 */
काष्ठा ceph_osdmap *ceph_osdmap_decode(व्योम **p, व्योम *end, bool msgr2)
अणु
	काष्ठा ceph_osdmap *map;
	पूर्णांक ret;

	map = ceph_osdmap_alloc();
	अगर (!map)
		वापस ERR_PTR(-ENOMEM);

	ret = osdmap_decode(p, end, msgr2, map);
	अगर (ret) अणु
		ceph_osdmap_destroy(map);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस map;
पूर्ण

/*
 * Encoding order is (new_up_client, new_state, new_weight).  Need to
 * apply in the (new_weight, new_state, new_up_client) order, because
 * an incremental map may look like e.g.
 *
 *     new_up_client: अणु osd=6, addr=... पूर्ण # set osd_state and addr
 *     new_state: अणु osd=6, xorstate=EXISTS पूर्ण # clear osd_state
 */
अटल पूर्णांक decode_new_up_state_weight(व्योम **p, व्योम *end, u8 काष्ठा_v,
				      bool msgr2, काष्ठा ceph_osdmap *map)
अणु
	व्योम *new_up_client;
	व्योम *new_state;
	व्योम *new_weight_end;
	u32 len;
	पूर्णांक ret;
	पूर्णांक i;

	new_up_client = *p;
	ceph_decode_32_safe(p, end, len, e_inval);
	क्रम (i = 0; i < len; ++i) अणु
		काष्ठा ceph_entity_addr addr;

		ceph_decode_skip_32(p, end, e_inval);
		अगर (काष्ठा_v >= 7)
			ret = ceph_decode_entity_addrvec(p, end, msgr2, &addr);
		अन्यथा
			ret = ceph_decode_entity_addr(p, end, &addr);
		अगर (ret)
			वापस ret;
	पूर्ण

	new_state = *p;
	ceph_decode_32_safe(p, end, len, e_inval);
	len *= माप(u32) + (काष्ठा_v >= 5 ? माप(u32) : माप(u8));
	ceph_decode_need(p, end, len, e_inval);
	*p += len;

	/* new_weight */
	ceph_decode_32_safe(p, end, len, e_inval);
	जबतक (len--) अणु
		s32 osd;
		u32 w;

		ceph_decode_need(p, end, 2*माप(u32), e_inval);
		osd = ceph_decode_32(p);
		w = ceph_decode_32(p);
		BUG_ON(osd >= map->max_osd);
		pr_info("osd%d weight 0x%x %s\n", osd, w,
		     w == CEPH_OSD_IN ? "(in)" :
		     (w == CEPH_OSD_OUT ? "(out)" : ""));
		map->osd_weight[osd] = w;

		/*
		 * If we are marking in, set the EXISTS, and clear the
		 * AUTOOUT and NEW bits.
		 */
		अगर (w) अणु
			map->osd_state[osd] |= CEPH_OSD_EXISTS;
			map->osd_state[osd] &= ~(CEPH_OSD_AUTOOUT |
						 CEPH_OSD_NEW);
		पूर्ण
	पूर्ण
	new_weight_end = *p;

	/* new_state (up/करोwn) */
	*p = new_state;
	len = ceph_decode_32(p);
	जबतक (len--) अणु
		s32 osd;
		u32 xorstate;

		osd = ceph_decode_32(p);
		अगर (काष्ठा_v >= 5)
			xorstate = ceph_decode_32(p);
		अन्यथा
			xorstate = ceph_decode_8(p);
		अगर (xorstate == 0)
			xorstate = CEPH_OSD_UP;
		BUG_ON(osd >= map->max_osd);
		अगर ((map->osd_state[osd] & CEPH_OSD_UP) &&
		    (xorstate & CEPH_OSD_UP))
			pr_info("osd%d down\n", osd);
		अगर ((map->osd_state[osd] & CEPH_OSD_EXISTS) &&
		    (xorstate & CEPH_OSD_EXISTS)) अणु
			pr_info("osd%d does not exist\n", osd);
			ret = set_primary_affinity(map, osd,
						   CEPH_OSD_DEFAULT_PRIMARY_AFFINITY);
			अगर (ret)
				वापस ret;
			स_रखो(map->osd_addr + osd, 0, माप(*map->osd_addr));
			map->osd_state[osd] = 0;
		पूर्ण अन्यथा अणु
			map->osd_state[osd] ^= xorstate;
		पूर्ण
	पूर्ण

	/* new_up_client */
	*p = new_up_client;
	len = ceph_decode_32(p);
	जबतक (len--) अणु
		s32 osd;
		काष्ठा ceph_entity_addr addr;

		osd = ceph_decode_32(p);
		BUG_ON(osd >= map->max_osd);
		अगर (काष्ठा_v >= 7)
			ret = ceph_decode_entity_addrvec(p, end, msgr2, &addr);
		अन्यथा
			ret = ceph_decode_entity_addr(p, end, &addr);
		अगर (ret)
			वापस ret;

		करोut("%s osd%d addr %s\n", __func__, osd, ceph_pr_addr(&addr));

		pr_info("osd%d up\n", osd);
		map->osd_state[osd] |= CEPH_OSD_EXISTS | CEPH_OSD_UP;
		map->osd_addr[osd] = addr;
	पूर्ण

	*p = new_weight_end;
	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

/*
 * decode and apply an incremental map update.
 */
काष्ठा ceph_osdmap *osdmap_apply_incremental(व्योम **p, व्योम *end, bool msgr2,
					     काष्ठा ceph_osdmap *map)
अणु
	काष्ठा ceph_fsid fsid;
	u32 epoch = 0;
	काष्ठा ceph_बारpec modअगरied;
	s32 len;
	u64 pool;
	__s64 new_pool_max;
	__s32 new_flags, max;
	व्योम *start = *p;
	पूर्णांक err;
	u8 काष्ठा_v;

	करोut("%s %p to %p len %d\n", __func__, *p, end, (पूर्णांक)(end - *p));

	err = get_osdmap_client_data_v(p, end, "inc", &काष्ठा_v);
	अगर (err)
		जाओ bad;

	/* fsid, epoch, modअगरied, new_pool_max, new_flags */
	ceph_decode_need(p, end, माप(fsid) + माप(u32) + माप(modअगरied) +
			 माप(u64) + माप(u32), e_inval);
	ceph_decode_copy(p, &fsid, माप(fsid));
	epoch = ceph_decode_32(p);
	BUG_ON(epoch != map->epoch+1);
	ceph_decode_copy(p, &modअगरied, माप(modअगरied));
	new_pool_max = ceph_decode_64(p);
	new_flags = ceph_decode_32(p);

	/* full map? */
	ceph_decode_32_safe(p, end, len, e_inval);
	अगर (len > 0) अणु
		करोut("apply_incremental full map len %d, %p to %p\n",
		     len, *p, end);
		वापस ceph_osdmap_decode(p, min(*p+len, end), msgr2);
	पूर्ण

	/* new crush? */
	ceph_decode_32_safe(p, end, len, e_inval);
	अगर (len > 0) अणु
		err = osdmap_set_crush(map,
				       crush_decode(*p, min(*p + len, end)));
		अगर (err)
			जाओ bad;
		*p += len;
	पूर्ण

	/* new flags? */
	अगर (new_flags >= 0)
		map->flags = new_flags;
	अगर (new_pool_max >= 0)
		map->pool_max = new_pool_max;

	/* new max? */
	ceph_decode_32_safe(p, end, max, e_inval);
	अगर (max >= 0) अणु
		err = osdmap_set_max_osd(map, max);
		अगर (err)
			जाओ bad;
	पूर्ण

	map->epoch++;
	map->modअगरied = modअगरied;

	/* new_pools */
	err = decode_new_pools(p, end, map);
	अगर (err)
		जाओ bad;

	/* new_pool_names */
	err = decode_pool_names(p, end, map);
	अगर (err)
		जाओ bad;

	/* old_pool */
	ceph_decode_32_safe(p, end, len, e_inval);
	जबतक (len--) अणु
		काष्ठा ceph_pg_pool_info *pi;

		ceph_decode_64_safe(p, end, pool, e_inval);
		pi = lookup_pg_pool(&map->pg_pools, pool);
		अगर (pi)
			__हटाओ_pg_pool(&map->pg_pools, pi);
	पूर्ण

	/* new_up_client, new_state, new_weight */
	err = decode_new_up_state_weight(p, end, काष्ठा_v, msgr2, map);
	अगर (err)
		जाओ bad;

	/* new_pg_temp */
	err = decode_new_pg_temp(p, end, map);
	अगर (err)
		जाओ bad;

	/* new_primary_temp */
	अगर (काष्ठा_v >= 1) अणु
		err = decode_new_primary_temp(p, end, map);
		अगर (err)
			जाओ bad;
	पूर्ण

	/* new_primary_affinity */
	अगर (काष्ठा_v >= 2) अणु
		err = decode_new_primary_affinity(p, end, map);
		अगर (err)
			जाओ bad;
	पूर्ण

	अगर (काष्ठा_v >= 3) अणु
		/* new_erasure_code_profiles */
		ceph_decode_skip_map_of_map(p, end, string, string, string,
					    e_inval);
		/* old_erasure_code_profiles */
		ceph_decode_skip_set(p, end, string, e_inval);
	पूर्ण

	अगर (काष्ठा_v >= 4) अणु
		err = decode_new_pg_upmap(p, end, map);
		अगर (err)
			जाओ bad;

		err = decode_old_pg_upmap(p, end, map);
		अगर (err)
			जाओ bad;

		err = decode_new_pg_upmap_items(p, end, map);
		अगर (err)
			जाओ bad;

		err = decode_old_pg_upmap_items(p, end, map);
		अगर (err)
			जाओ bad;
	पूर्ण

	/* ignore the rest */
	*p = end;

	करोut("inc osdmap epoch %d max_osd %d\n", map->epoch, map->max_osd);
	वापस map;

e_inval:
	err = -EINVAL;
bad:
	pr_err("corrupt inc osdmap (%d) epoch %d off %d (%p of %p-%p)\n",
	       err, epoch, (पूर्णांक)(*p - start), *p, start, end);
	prपूर्णांक_hex_dump(KERN_DEBUG, "osdmap: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       start, end - start, true);
	वापस ERR_PTR(err);
पूर्ण

व्योम ceph_oloc_copy(काष्ठा ceph_object_locator *dest,
		    स्थिर काष्ठा ceph_object_locator *src)
अणु
	ceph_oloc_destroy(dest);

	dest->pool = src->pool;
	अगर (src->pool_ns)
		dest->pool_ns = ceph_get_string(src->pool_ns);
	अन्यथा
		dest->pool_ns = शून्य;
पूर्ण
EXPORT_SYMBOL(ceph_oloc_copy);

व्योम ceph_oloc_destroy(काष्ठा ceph_object_locator *oloc)
अणु
	ceph_put_string(oloc->pool_ns);
पूर्ण
EXPORT_SYMBOL(ceph_oloc_destroy);

व्योम ceph_oid_copy(काष्ठा ceph_object_id *dest,
		   स्थिर काष्ठा ceph_object_id *src)
अणु
	ceph_oid_destroy(dest);

	अगर (src->name != src->अंतरभूत_name) अणु
		/* very rare, see ceph_object_id definition */
		dest->name = kदो_स्मृति(src->name_len + 1,
				     GFP_NOIO | __GFP_NOFAIL);
	पूर्ण अन्यथा अणु
		dest->name = dest->अंतरभूत_name;
	पूर्ण
	स_नकल(dest->name, src->name, src->name_len + 1);
	dest->name_len = src->name_len;
पूर्ण
EXPORT_SYMBOL(ceph_oid_copy);

अटल __म_लिखो(2, 0)
पूर्णांक oid_म_लिखो_vargs(काष्ठा ceph_object_id *oid, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	पूर्णांक len;

	WARN_ON(!ceph_oid_empty(oid));

	len = vsnम_लिखो(oid->अंतरभूत_name, माप(oid->अंतरभूत_name), fmt, ap);
	अगर (len >= माप(oid->अंतरभूत_name))
		वापस len;

	oid->name_len = len;
	वापस 0;
पूर्ण

/*
 * If oid करोesn't fit पूर्णांकo अंतरभूत buffer, BUG.
 */
व्योम ceph_oid_म_लिखो(काष्ठा ceph_object_id *oid, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	BUG_ON(oid_म_लिखो_vargs(oid, fmt, ap));
	बहु_पूर्ण(ap);
पूर्ण
EXPORT_SYMBOL(ceph_oid_म_लिखो);

अटल __म_लिखो(3, 0)
पूर्णांक oid_aम_लिखो_vargs(काष्ठा ceph_object_id *oid, gfp_t gfp,
		      स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	बहु_सूची aq;
	पूर्णांक len;

	va_copy(aq, ap);
	len = oid_म_लिखो_vargs(oid, fmt, aq);
	बहु_पूर्ण(aq);

	अगर (len) अणु
		अक्षर *बाह्यal_name;

		बाह्यal_name = kदो_स्मृति(len + 1, gfp);
		अगर (!बाह्यal_name)
			वापस -ENOMEM;

		oid->name = बाह्यal_name;
		WARN_ON(vsnम_लिखो(oid->name, len + 1, fmt, ap) != len);
		oid->name_len = len;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If oid करोesn't fit पूर्णांकo अंतरभूत buffer, allocate.
 */
पूर्णांक ceph_oid_aम_लिखो(काष्ठा ceph_object_id *oid, gfp_t gfp,
		     स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	बहु_शुरू(ap, fmt);
	ret = oid_aम_लिखो_vargs(oid, gfp, fmt, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_oid_aम_लिखो);

व्योम ceph_oid_destroy(काष्ठा ceph_object_id *oid)
अणु
	अगर (oid->name != oid->अंतरभूत_name)
		kमुक्त(oid->name);
पूर्ण
EXPORT_SYMBOL(ceph_oid_destroy);

/*
 * osds only
 */
अटल bool __osds_equal(स्थिर काष्ठा ceph_osds *lhs,
			 स्थिर काष्ठा ceph_osds *rhs)
अणु
	अगर (lhs->size == rhs->size &&
	    !स_भेद(lhs->osds, rhs->osds, rhs->size * माप(rhs->osds[0])))
		वापस true;

	वापस false;
पूर्ण

/*
 * osds + primary
 */
अटल bool osds_equal(स्थिर काष्ठा ceph_osds *lhs,
		       स्थिर काष्ठा ceph_osds *rhs)
अणु
	अगर (__osds_equal(lhs, rhs) &&
	    lhs->primary == rhs->primary)
		वापस true;

	वापस false;
पूर्ण

अटल bool osds_valid(स्थिर काष्ठा ceph_osds *set)
अणु
	/* non-empty set */
	अगर (set->size > 0 && set->primary >= 0)
		वापस true;

	/* empty can_shअगरt_osds set */
	अगर (!set->size && set->primary == -1)
		वापस true;

	/* empty !can_shअगरt_osds set - all NONE */
	अगर (set->size > 0 && set->primary == -1) अणु
		पूर्णांक i;

		क्रम (i = 0; i < set->size; i++) अणु
			अगर (set->osds[i] != CRUSH_ITEM_NONE)
				अवरोध;
		पूर्ण
		अगर (i == set->size)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम ceph_osds_copy(काष्ठा ceph_osds *dest, स्थिर काष्ठा ceph_osds *src)
अणु
	स_नकल(dest->osds, src->osds, src->size * माप(src->osds[0]));
	dest->size = src->size;
	dest->primary = src->primary;
पूर्ण

bool ceph_pg_is_split(स्थिर काष्ठा ceph_pg *pgid, u32 old_pg_num,
		      u32 new_pg_num)
अणु
	पूर्णांक old_bits = calc_bits_of(old_pg_num);
	पूर्णांक old_mask = (1 << old_bits) - 1;
	पूर्णांक n;

	WARN_ON(pgid->seed >= old_pg_num);
	अगर (new_pg_num <= old_pg_num)
		वापस false;

	क्रम (n = 1; ; n++) अणु
		पूर्णांक next_bit = n << (old_bits - 1);
		u32 s = next_bit | pgid->seed;

		अगर (s < old_pg_num || s == pgid->seed)
			जारी;
		अगर (s >= new_pg_num)
			अवरोध;

		s = ceph_stable_mod(s, old_pg_num, old_mask);
		अगर (s == pgid->seed)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool ceph_is_new_पूर्णांकerval(स्थिर काष्ठा ceph_osds *old_acting,
			  स्थिर काष्ठा ceph_osds *new_acting,
			  स्थिर काष्ठा ceph_osds *old_up,
			  स्थिर काष्ठा ceph_osds *new_up,
			  पूर्णांक old_size,
			  पूर्णांक new_size,
			  पूर्णांक old_min_size,
			  पूर्णांक new_min_size,
			  u32 old_pg_num,
			  u32 new_pg_num,
			  bool old_sort_bitwise,
			  bool new_sort_bitwise,
			  bool old_recovery_deletes,
			  bool new_recovery_deletes,
			  स्थिर काष्ठा ceph_pg *pgid)
अणु
	वापस !osds_equal(old_acting, new_acting) ||
	       !osds_equal(old_up, new_up) ||
	       old_size != new_size ||
	       old_min_size != new_min_size ||
	       ceph_pg_is_split(pgid, old_pg_num, new_pg_num) ||
	       old_sort_bitwise != new_sort_bitwise ||
	       old_recovery_deletes != new_recovery_deletes;
पूर्ण

अटल पूर्णांक calc_pg_rank(पूर्णांक osd, स्थिर काष्ठा ceph_osds *acting)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < acting->size; i++) अणु
		अगर (acting->osds[i] == osd)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल bool primary_changed(स्थिर काष्ठा ceph_osds *old_acting,
			    स्थिर काष्ठा ceph_osds *new_acting)
अणु
	अगर (!old_acting->size && !new_acting->size)
		वापस false; /* both still empty */

	अगर (!old_acting->size ^ !new_acting->size)
		वापस true; /* was empty, now not, or vice versa */

	अगर (old_acting->primary != new_acting->primary)
		वापस true; /* primary changed */

	अगर (calc_pg_rank(old_acting->primary, old_acting) !=
	    calc_pg_rank(new_acting->primary, new_acting))
		वापस true;

	वापस false; /* same primary (tho replicas may have changed) */
पूर्ण

bool ceph_osds_changed(स्थिर काष्ठा ceph_osds *old_acting,
		       स्थिर काष्ठा ceph_osds *new_acting,
		       bool any_change)
अणु
	अगर (primary_changed(old_acting, new_acting))
		वापस true;

	अगर (any_change && !__osds_equal(old_acting, new_acting))
		वापस true;

	वापस false;
पूर्ण

/*
 * Map an object पूर्णांकo a PG.
 *
 * Should only be called with target_oid and target_oloc (as opposed to
 * base_oid and base_oloc), since tiering isn't taken पूर्णांकo account.
 */
व्योम __ceph_object_locator_to_pg(काष्ठा ceph_pg_pool_info *pi,
				 स्थिर काष्ठा ceph_object_id *oid,
				 स्थिर काष्ठा ceph_object_locator *oloc,
				 काष्ठा ceph_pg *raw_pgid)
अणु
	WARN_ON(pi->id != oloc->pool);

	अगर (!oloc->pool_ns) अणु
		raw_pgid->pool = oloc->pool;
		raw_pgid->seed = ceph_str_hash(pi->object_hash, oid->name,
					     oid->name_len);
		करोut("%s %s -> raw_pgid %llu.%x\n", __func__, oid->name,
		     raw_pgid->pool, raw_pgid->seed);
	पूर्ण अन्यथा अणु
		अक्षर stack_buf[256];
		अक्षर *buf = stack_buf;
		पूर्णांक nsl = oloc->pool_ns->len;
		माप_प्रकार total = nsl + 1 + oid->name_len;

		अगर (total > माप(stack_buf))
			buf = kदो_स्मृति(total, GFP_NOIO | __GFP_NOFAIL);
		स_नकल(buf, oloc->pool_ns->str, nsl);
		buf[nsl] = '\037';
		स_नकल(buf + nsl + 1, oid->name, oid->name_len);
		raw_pgid->pool = oloc->pool;
		raw_pgid->seed = ceph_str_hash(pi->object_hash, buf, total);
		अगर (buf != stack_buf)
			kमुक्त(buf);
		करोut("%s %s ns %.*s -> raw_pgid %llu.%x\n", __func__,
		     oid->name, nsl, oloc->pool_ns->str,
		     raw_pgid->pool, raw_pgid->seed);
	पूर्ण
पूर्ण

पूर्णांक ceph_object_locator_to_pg(काष्ठा ceph_osdmap *osdmap,
			      स्थिर काष्ठा ceph_object_id *oid,
			      स्थिर काष्ठा ceph_object_locator *oloc,
			      काष्ठा ceph_pg *raw_pgid)
अणु
	काष्ठा ceph_pg_pool_info *pi;

	pi = ceph_pg_pool_by_id(osdmap, oloc->pool);
	अगर (!pi)
		वापस -ENOENT;

	__ceph_object_locator_to_pg(pi, oid, oloc, raw_pgid);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_object_locator_to_pg);

/*
 * Map a raw PG (full precision ps) पूर्णांकo an actual PG.
 */
अटल व्योम raw_pg_to_pg(काष्ठा ceph_pg_pool_info *pi,
			 स्थिर काष्ठा ceph_pg *raw_pgid,
			 काष्ठा ceph_pg *pgid)
अणु
	pgid->pool = raw_pgid->pool;
	pgid->seed = ceph_stable_mod(raw_pgid->seed, pi->pg_num,
				     pi->pg_num_mask);
पूर्ण

/*
 * Map a raw PG (full precision ps) पूर्णांकo a placement ps (placement
 * seed).  Include pool id in that value so that dअगरferent pools करोn't
 * use the same seeds.
 */
अटल u32 raw_pg_to_pps(काष्ठा ceph_pg_pool_info *pi,
			 स्थिर काष्ठा ceph_pg *raw_pgid)
अणु
	अगर (pi->flags & CEPH_POOL_FLAG_HASHPSPOOL) अणु
		/* hash pool id and seed so that pool PGs करो not overlap */
		वापस crush_hash32_2(CRUSH_HASH_RJENKINS1,
				      ceph_stable_mod(raw_pgid->seed,
						      pi->pgp_num,
						      pi->pgp_num_mask),
				      raw_pgid->pool);
	पूर्ण अन्यथा अणु
		/*
		 * legacy behavior: add ps and pool together.  this is
		 * not a great approach because the PGs from each pool
		 * will overlap on top of each other: 0.5 == 1.4 ==
		 * 2.3 == ...
		 */
		वापस ceph_stable_mod(raw_pgid->seed, pi->pgp_num,
				       pi->pgp_num_mask) +
		       (अचिन्हित)raw_pgid->pool;
	पूर्ण
पूर्ण

/*
 * Magic value used क्रम a "default" fallback choose_args, used अगर the
 * crush_choose_arg_map passed to करो_crush() करोes not exist.  If this
 * also करोesn't exist, fall back to canonical weights.
 */
#घोषणा CEPH_DEFAULT_CHOOSE_ARGS	-1

अटल पूर्णांक करो_crush(काष्ठा ceph_osdmap *map, पूर्णांक ruleno, पूर्णांक x,
		    पूर्णांक *result, पूर्णांक result_max,
		    स्थिर __u32 *weight, पूर्णांक weight_max,
		    s64 choose_args_index)
अणु
	काष्ठा crush_choose_arg_map *arg_map;
	काष्ठा crush_work *work;
	पूर्णांक r;

	BUG_ON(result_max > CEPH_PG_MAX_SIZE);

	arg_map = lookup_choose_arg_map(&map->crush->choose_args,
					choose_args_index);
	अगर (!arg_map)
		arg_map = lookup_choose_arg_map(&map->crush->choose_args,
						CEPH_DEFAULT_CHOOSE_ARGS);

	work = get_workspace(&map->crush_wsm, map->crush);
	r = crush_करो_rule(map->crush, ruleno, x, result, result_max,
			  weight, weight_max, work,
			  arg_map ? arg_map->args : शून्य);
	put_workspace(&map->crush_wsm, work);
	वापस r;
पूर्ण

अटल व्योम हटाओ_nonexistent_osds(काष्ठा ceph_osdmap *osdmap,
				    काष्ठा ceph_pg_pool_info *pi,
				    काष्ठा ceph_osds *set)
अणु
	पूर्णांक i;

	अगर (ceph_can_shअगरt_osds(pi)) अणु
		पूर्णांक हटाओd = 0;

		/* shअगरt left */
		क्रम (i = 0; i < set->size; i++) अणु
			अगर (!ceph_osd_exists(osdmap, set->osds[i])) अणु
				हटाओd++;
				जारी;
			पूर्ण
			अगर (हटाओd)
				set->osds[i - हटाओd] = set->osds[i];
		पूर्ण
		set->size -= हटाओd;
	पूर्ण अन्यथा अणु
		/* set dne devices to NONE */
		क्रम (i = 0; i < set->size; i++) अणु
			अगर (!ceph_osd_exists(osdmap, set->osds[i]))
				set->osds[i] = CRUSH_ITEM_NONE;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Calculate raw set (CRUSH output) क्रम given PG and filter out
 * nonexistent OSDs.  ->primary is undefined क्रम a raw set.
 *
 * Placement seed (CRUSH input) is वापसed through @ppps.
 */
अटल व्योम pg_to_raw_osds(काष्ठा ceph_osdmap *osdmap,
			   काष्ठा ceph_pg_pool_info *pi,
			   स्थिर काष्ठा ceph_pg *raw_pgid,
			   काष्ठा ceph_osds *raw,
			   u32 *ppps)
अणु
	u32 pps = raw_pg_to_pps(pi, raw_pgid);
	पूर्णांक ruleno;
	पूर्णांक len;

	ceph_osds_init(raw);
	अगर (ppps)
		*ppps = pps;

	ruleno = crush_find_rule(osdmap->crush, pi->crush_ruleset, pi->type,
				 pi->size);
	अगर (ruleno < 0) अणु
		pr_err("no crush rule: pool %lld ruleset %d type %d size %d\n",
		       pi->id, pi->crush_ruleset, pi->type, pi->size);
		वापस;
	पूर्ण

	अगर (pi->size > ARRAY_SIZE(raw->osds)) अणु
		pr_err_ratelimited("pool %lld ruleset %d type %d too wide: size %d > %zu\n",
		       pi->id, pi->crush_ruleset, pi->type, pi->size,
		       ARRAY_SIZE(raw->osds));
		वापस;
	पूर्ण

	len = करो_crush(osdmap, ruleno, pps, raw->osds, pi->size,
		       osdmap->osd_weight, osdmap->max_osd, pi->id);
	अगर (len < 0) अणु
		pr_err("error %d from crush rule %d: pool %lld ruleset %d type %d size %d\n",
		       len, ruleno, pi->id, pi->crush_ruleset, pi->type,
		       pi->size);
		वापस;
	पूर्ण

	raw->size = len;
	हटाओ_nonexistent_osds(osdmap, pi, raw);
पूर्ण

/* apply pg_upmap[_items] mappings */
अटल व्योम apply_upmap(काष्ठा ceph_osdmap *osdmap,
			स्थिर काष्ठा ceph_pg *pgid,
			काष्ठा ceph_osds *raw)
अणु
	काष्ठा ceph_pg_mapping *pg;
	पूर्णांक i, j;

	pg = lookup_pg_mapping(&osdmap->pg_upmap, pgid);
	अगर (pg) अणु
		/* make sure tarमाला_लो aren't marked out */
		क्रम (i = 0; i < pg->pg_upmap.len; i++) अणु
			पूर्णांक osd = pg->pg_upmap.osds[i];

			अगर (osd != CRUSH_ITEM_NONE &&
			    osd < osdmap->max_osd &&
			    osdmap->osd_weight[osd] == 0) अणु
				/* reject/ignore explicit mapping */
				वापस;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < pg->pg_upmap.len; i++)
			raw->osds[i] = pg->pg_upmap.osds[i];
		raw->size = pg->pg_upmap.len;
		/* check and apply pg_upmap_items, अगर any */
	पूर्ण

	pg = lookup_pg_mapping(&osdmap->pg_upmap_items, pgid);
	अगर (pg) अणु
		/*
		 * Note: this approach करोes not allow a bidirectional swap,
		 * e.g., [[1,2],[2,1]] applied to [0,1,2] -> [0,2,1].
		 */
		क्रम (i = 0; i < pg->pg_upmap_items.len; i++) अणु
			पूर्णांक from = pg->pg_upmap_items.from_to[i][0];
			पूर्णांक to = pg->pg_upmap_items.from_to[i][1];
			पूर्णांक pos = -1;
			bool exists = false;

			/* make sure replacement करोesn't alपढ़ोy appear */
			क्रम (j = 0; j < raw->size; j++) अणु
				पूर्णांक osd = raw->osds[j];

				अगर (osd == to) अणु
					exists = true;
					अवरोध;
				पूर्ण
				/* ignore mapping अगर target is marked out */
				अगर (osd == from && pos < 0 &&
				    !(to != CRUSH_ITEM_NONE &&
				      to < osdmap->max_osd &&
				      osdmap->osd_weight[to] == 0)) अणु
					pos = j;
				पूर्ण
			पूर्ण
			अगर (!exists && pos >= 0)
				raw->osds[pos] = to;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Given raw set, calculate up set and up primary.  By definition of an
 * up set, the result won't contain nonexistent or करोwn OSDs.
 *
 * This is करोne in-place - on वापस @set is the up set.  If it's
 * empty, ->primary will reमुख्य undefined.
 */
अटल व्योम raw_to_up_osds(काष्ठा ceph_osdmap *osdmap,
			   काष्ठा ceph_pg_pool_info *pi,
			   काष्ठा ceph_osds *set)
अणु
	पूर्णांक i;

	/* ->primary is undefined क्रम a raw set */
	BUG_ON(set->primary != -1);

	अगर (ceph_can_shअगरt_osds(pi)) अणु
		पूर्णांक हटाओd = 0;

		/* shअगरt left */
		क्रम (i = 0; i < set->size; i++) अणु
			अगर (ceph_osd_is_करोwn(osdmap, set->osds[i])) अणु
				हटाओd++;
				जारी;
			पूर्ण
			अगर (हटाओd)
				set->osds[i - हटाओd] = set->osds[i];
		पूर्ण
		set->size -= हटाओd;
		अगर (set->size > 0)
			set->primary = set->osds[0];
	पूर्ण अन्यथा अणु
		/* set करोwn/dne devices to NONE */
		क्रम (i = set->size - 1; i >= 0; i--) अणु
			अगर (ceph_osd_is_करोwn(osdmap, set->osds[i]))
				set->osds[i] = CRUSH_ITEM_NONE;
			अन्यथा
				set->primary = set->osds[i];
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम apply_primary_affinity(काष्ठा ceph_osdmap *osdmap,
				   काष्ठा ceph_pg_pool_info *pi,
				   u32 pps,
				   काष्ठा ceph_osds *up)
अणु
	पूर्णांक i;
	पूर्णांक pos = -1;

	/*
	 * Do we have any non-शेष primary_affinity values क्रम these
	 * osds?
	 */
	अगर (!osdmap->osd_primary_affinity)
		वापस;

	क्रम (i = 0; i < up->size; i++) अणु
		पूर्णांक osd = up->osds[i];

		अगर (osd != CRUSH_ITEM_NONE &&
		    osdmap->osd_primary_affinity[osd] !=
					CEPH_OSD_DEFAULT_PRIMARY_AFFINITY) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == up->size)
		वापस;

	/*
	 * Pick the primary.  Feed both the seed (क्रम the pg) and the
	 * osd पूर्णांकo the hash/rng so that a proportional fraction of an
	 * osd's pgs get rejected as primary.
	 */
	क्रम (i = 0; i < up->size; i++) अणु
		पूर्णांक osd = up->osds[i];
		u32 aff;

		अगर (osd == CRUSH_ITEM_NONE)
			जारी;

		aff = osdmap->osd_primary_affinity[osd];
		अगर (aff < CEPH_OSD_MAX_PRIMARY_AFFINITY &&
		    (crush_hash32_2(CRUSH_HASH_RJENKINS1,
				    pps, osd) >> 16) >= aff) अणु
			/*
			 * We chose not to use this primary.  Note it
			 * anyway as a fallback in हाल we करोn't pick
			 * anyone अन्यथा, but keep looking.
			 */
			अगर (pos < 0)
				pos = i;
		पूर्ण अन्यथा अणु
			pos = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pos < 0)
		वापस;

	up->primary = up->osds[pos];

	अगर (ceph_can_shअगरt_osds(pi) && pos > 0) अणु
		/* move the new primary to the front */
		क्रम (i = pos; i > 0; i--)
			up->osds[i] = up->osds[i - 1];
		up->osds[0] = up->primary;
	पूर्ण
पूर्ण

/*
 * Get pg_temp and primary_temp mappings क्रम given PG.
 *
 * Note that a PG may have none, only pg_temp, only primary_temp or
 * both pg_temp and primary_temp mappings.  This means @temp isn't
 * always a valid OSD set on वापस: in the "only primary_temp" हाल,
 * @temp will have its ->primary >= 0 but ->size == 0.
 */
अटल व्योम get_temp_osds(काष्ठा ceph_osdmap *osdmap,
			  काष्ठा ceph_pg_pool_info *pi,
			  स्थिर काष्ठा ceph_pg *pgid,
			  काष्ठा ceph_osds *temp)
अणु
	काष्ठा ceph_pg_mapping *pg;
	पूर्णांक i;

	ceph_osds_init(temp);

	/* pg_temp? */
	pg = lookup_pg_mapping(&osdmap->pg_temp, pgid);
	अगर (pg) अणु
		क्रम (i = 0; i < pg->pg_temp.len; i++) अणु
			अगर (ceph_osd_is_करोwn(osdmap, pg->pg_temp.osds[i])) अणु
				अगर (ceph_can_shअगरt_osds(pi))
					जारी;

				temp->osds[temp->size++] = CRUSH_ITEM_NONE;
			पूर्ण अन्यथा अणु
				temp->osds[temp->size++] = pg->pg_temp.osds[i];
			पूर्ण
		पूर्ण

		/* apply pg_temp's primary */
		क्रम (i = 0; i < temp->size; i++) अणु
			अगर (temp->osds[i] != CRUSH_ITEM_NONE) अणु
				temp->primary = temp->osds[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* primary_temp? */
	pg = lookup_pg_mapping(&osdmap->primary_temp, pgid);
	अगर (pg)
		temp->primary = pg->primary_temp.osd;
पूर्ण

/*
 * Map a PG to its acting set as well as its up set.
 *
 * Acting set is used क्रम data mapping purposes, जबतक up set can be
 * recorded क्रम detecting पूर्णांकerval changes and deciding whether to
 * resend a request.
 */
व्योम ceph_pg_to_up_acting_osds(काष्ठा ceph_osdmap *osdmap,
			       काष्ठा ceph_pg_pool_info *pi,
			       स्थिर काष्ठा ceph_pg *raw_pgid,
			       काष्ठा ceph_osds *up,
			       काष्ठा ceph_osds *acting)
अणु
	काष्ठा ceph_pg pgid;
	u32 pps;

	WARN_ON(pi->id != raw_pgid->pool);
	raw_pg_to_pg(pi, raw_pgid, &pgid);

	pg_to_raw_osds(osdmap, pi, raw_pgid, up, &pps);
	apply_upmap(osdmap, &pgid, up);
	raw_to_up_osds(osdmap, pi, up);
	apply_primary_affinity(osdmap, pi, pps, up);
	get_temp_osds(osdmap, pi, &pgid, acting);
	अगर (!acting->size) अणु
		स_नकल(acting->osds, up->osds, up->size * माप(up->osds[0]));
		acting->size = up->size;
		अगर (acting->primary == -1)
			acting->primary = up->primary;
	पूर्ण
	WARN_ON(!osds_valid(up) || !osds_valid(acting));
पूर्ण

bool ceph_pg_to_primary_shard(काष्ठा ceph_osdmap *osdmap,
			      काष्ठा ceph_pg_pool_info *pi,
			      स्थिर काष्ठा ceph_pg *raw_pgid,
			      काष्ठा ceph_spg *spgid)
अणु
	काष्ठा ceph_pg pgid;
	काष्ठा ceph_osds up, acting;
	पूर्णांक i;

	WARN_ON(pi->id != raw_pgid->pool);
	raw_pg_to_pg(pi, raw_pgid, &pgid);

	अगर (ceph_can_shअगरt_osds(pi)) अणु
		spgid->pgid = pgid; /* काष्ठा */
		spgid->shard = CEPH_SPG_NOSHARD;
		वापस true;
	पूर्ण

	ceph_pg_to_up_acting_osds(osdmap, pi, &pgid, &up, &acting);
	क्रम (i = 0; i < acting.size; i++) अणु
		अगर (acting.osds[i] == acting.primary) अणु
			spgid->pgid = pgid; /* काष्ठा */
			spgid->shard = i;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/*
 * Return acting primary क्रम given PG, or -1 अगर none.
 */
पूर्णांक ceph_pg_to_acting_primary(काष्ठा ceph_osdmap *osdmap,
			      स्थिर काष्ठा ceph_pg *raw_pgid)
अणु
	काष्ठा ceph_pg_pool_info *pi;
	काष्ठा ceph_osds up, acting;

	pi = ceph_pg_pool_by_id(osdmap, raw_pgid->pool);
	अगर (!pi)
		वापस -1;

	ceph_pg_to_up_acting_osds(osdmap, pi, raw_pgid, &up, &acting);
	वापस acting.primary;
पूर्ण
EXPORT_SYMBOL(ceph_pg_to_acting_primary);

अटल काष्ठा crush_loc_node *alloc_crush_loc(माप_प्रकार type_name_len,
					      माप_प्रकार name_len)
अणु
	काष्ठा crush_loc_node *loc;

	loc = kदो_स्मृति(माप(*loc) + type_name_len + name_len + 2, GFP_NOIO);
	अगर (!loc)
		वापस शून्य;

	RB_CLEAR_NODE(&loc->cl_node);
	वापस loc;
पूर्ण

अटल व्योम मुक्त_crush_loc(काष्ठा crush_loc_node *loc)
अणु
	WARN_ON(!RB_EMPTY_NODE(&loc->cl_node));

	kमुक्त(loc);
पूर्ण

अटल पूर्णांक crush_loc_compare(स्थिर काष्ठा crush_loc *loc1,
			     स्थिर काष्ठा crush_loc *loc2)
अणु
	वापस म_भेद(loc1->cl_type_name, loc2->cl_type_name) ?:
	       म_भेद(loc1->cl_name, loc2->cl_name);
पूर्ण

DEFINE_RB_FUNCS2(crush_loc, काष्ठा crush_loc_node, cl_loc, crush_loc_compare,
		 RB_BYPTR, स्थिर काष्ठा crush_loc *, cl_node)

/*
 * Parses a set of <bucket type name>':'<bucket name> pairs separated
 * by '|', e.g. "rack:foo1|rack:foo2|datacenter:bar".
 *
 * Note that @crush_location is modअगरied by strsep().
 */
पूर्णांक ceph_parse_crush_location(अक्षर *crush_location, काष्ठा rb_root *locs)
अणु
	काष्ठा crush_loc_node *loc;
	स्थिर अक्षर *type_name, *name, *colon;
	माप_प्रकार type_name_len, name_len;

	करोut("%s '%s'\n", __func__, crush_location);
	जबतक ((type_name = strsep(&crush_location, "|"))) अणु
		colon = म_अक्षर(type_name, ':');
		अगर (!colon)
			वापस -EINVAL;

		type_name_len = colon - type_name;
		अगर (type_name_len == 0)
			वापस -EINVAL;

		name = colon + 1;
		name_len = म_माप(name);
		अगर (name_len == 0)
			वापस -EINVAL;

		loc = alloc_crush_loc(type_name_len, name_len);
		अगर (!loc)
			वापस -ENOMEM;

		loc->cl_loc.cl_type_name = loc->cl_data;
		स_नकल(loc->cl_loc.cl_type_name, type_name, type_name_len);
		loc->cl_loc.cl_type_name[type_name_len] = '\0';

		loc->cl_loc.cl_name = loc->cl_data + type_name_len + 1;
		स_नकल(loc->cl_loc.cl_name, name, name_len);
		loc->cl_loc.cl_name[name_len] = '\0';

		अगर (!__insert_crush_loc(locs, loc)) अणु
			मुक्त_crush_loc(loc);
			वापस -EEXIST;
		पूर्ण

		करोut("%s type_name '%s' name '%s'\n", __func__,
		     loc->cl_loc.cl_type_name, loc->cl_loc.cl_name);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ceph_compare_crush_locs(काष्ठा rb_root *locs1, काष्ठा rb_root *locs2)
अणु
	काष्ठा rb_node *n1 = rb_first(locs1);
	काष्ठा rb_node *n2 = rb_first(locs2);
	पूर्णांक ret;

	क्रम ( ; n1 && n2; n1 = rb_next(n1), n2 = rb_next(n2)) अणु
		काष्ठा crush_loc_node *loc1 =
		    rb_entry(n1, काष्ठा crush_loc_node, cl_node);
		काष्ठा crush_loc_node *loc2 =
		    rb_entry(n2, काष्ठा crush_loc_node, cl_node);

		ret = crush_loc_compare(&loc1->cl_loc, &loc2->cl_loc);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!n1 && n2)
		वापस -1;
	अगर (n1 && !n2)
		वापस 1;
	वापस 0;
पूर्ण

व्योम ceph_clear_crush_locs(काष्ठा rb_root *locs)
अणु
	जबतक (!RB_EMPTY_ROOT(locs)) अणु
		काष्ठा crush_loc_node *loc =
		    rb_entry(rb_first(locs), काष्ठा crush_loc_node, cl_node);

		erase_crush_loc(locs, loc);
		मुक्त_crush_loc(loc);
	पूर्ण
पूर्ण

/*
 * [a-zA-Z0-9-_.]+
 */
अटल bool is_valid_crush_name(स्थिर अक्षर *name)
अणु
	करो अणु
		अगर (!('a' <= *name && *name <= 'z') &&
		    !('A' <= *name && *name <= 'Z') &&
		    !('0' <= *name && *name <= '9') &&
		    *name != '-' && *name != '_' && *name != '.')
			वापस false;
	पूर्ण जबतक (*++name != '\0');

	वापस true;
पूर्ण

/*
 * Gets the parent of an item.  Returns its id (<0 because the
 * parent is always a bucket), type id (>0 क्रम the same reason,
 * via @parent_type_id) and location (via @parent_loc).  If no
 * parent, वापसs 0.
 *
 * Does a linear search, as there are no parent poपूर्णांकers of any
 * kind.  Note that the result is ambigous क्रम items that occur
 * multiple बार in the map.
 */
अटल पूर्णांक get_immediate_parent(काष्ठा crush_map *c, पूर्णांक id,
				u16 *parent_type_id,
				काष्ठा crush_loc *parent_loc)
अणु
	काष्ठा crush_bucket *b;
	काष्ठा crush_name_node *type_cn, *cn;
	पूर्णांक i, j;

	क्रम (i = 0; i < c->max_buckets; i++) अणु
		b = c->buckets[i];
		अगर (!b)
			जारी;

		/* ignore per-class shaकरोw hierarchy */
		cn = lookup_crush_name(&c->names, b->id);
		अगर (!cn || !is_valid_crush_name(cn->cn_name))
			जारी;

		क्रम (j = 0; j < b->size; j++) अणु
			अगर (b->items[j] != id)
				जारी;

			*parent_type_id = b->type;
			type_cn = lookup_crush_name(&c->type_names, b->type);
			parent_loc->cl_type_name = type_cn->cn_name;
			parent_loc->cl_name = cn->cn_name;
			वापस b->id;
		पूर्ण
	पूर्ण

	वापस 0;  /* no parent */
पूर्ण

/*
 * Calculates the locality/distance from an item to a client
 * location expressed in terms of CRUSH hierarchy as a set of
 * (bucket type name, bucket name) pairs.  Specअगरically, looks
 * क्रम the lowest-valued bucket type क्रम which the location of
 * @id matches one of the locations in @locs, so क्रम standard
 * bucket types (host = 1, rack = 3, datacenter = 8, zone = 9)
 * a matching host is बंदr than a matching rack and a matching
 * data center is बंदr than a matching zone.
 *
 * Specअगरying multiple locations (a "multipath" location) such
 * as "rack=foo1 rack=foo2 datacenter=bar" is allowed -- @locs
 * is a multimap.  The locality will be:
 *
 * - 3 क्रम OSDs in racks foo1 and foo2
 * - 8 क्रम OSDs in data center bar
 * - -1 क्रम all other OSDs
 *
 * The lowest possible bucket type is 1, so the best locality
 * क्रम an OSD is 1 (i.e. a matching host).  Locality 0 would be
 * the OSD itself.
 */
पूर्णांक ceph_get_crush_locality(काष्ठा ceph_osdmap *osdmap, पूर्णांक id,
			    काष्ठा rb_root *locs)
अणु
	काष्ठा crush_loc loc;
	u16 type_id;

	/*
	 * Instead of repeated get_immediate_parent() calls,
	 * the location of @id could be obtained with a single
	 * depth-first traversal.
	 */
	क्रम (;;) अणु
		id = get_immediate_parent(osdmap->crush, id, &type_id, &loc);
		अगर (id >= 0)
			वापस -1;  /* not local */

		अगर (lookup_crush_loc(locs, &loc))
			वापस type_id;
	पूर्ण
पूर्ण
