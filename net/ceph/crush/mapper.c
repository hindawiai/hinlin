<शैली गुरु>
/*
 * Ceph - scalable distributed file प्रणाली
 *
 * Copyright (C) 2015 Intel Corporation All Rights Reserved
 *
 * This is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 *
 */

#अगर_घोषित __KERNEL__
# include <linux/माला.स>
# include <linux/slab.h>
# include <linux/bug.h>
# include <linux/kernel.h>
# include <linux/crush/crush.h>
# include <linux/crush/hash.h>
# include <linux/crush/mapper.h>
#अन्यथा
# include "crush_compat.h"
# include "crush.h"
# include "hash.h"
# include "mapper.h"
#पूर्ण_अगर
#समावेश "crush_ln_table.h"

#घोषणा dprपूर्णांकk(args...) /* म_लिखो(args) */

/*
 * Implement the core CRUSH mapping algorithm.
 */

/**
 * crush_find_rule - find a crush_rule id क्रम a given ruleset, type, and size.
 * @map: the crush_map
 * @ruleset: the storage ruleset id (user defined)
 * @type: storage ruleset type (user defined)
 * @size: output set size
 */
पूर्णांक crush_find_rule(स्थिर काष्ठा crush_map *map, पूर्णांक ruleset, पूर्णांक type, पूर्णांक size)
अणु
	__u32 i;

	क्रम (i = 0; i < map->max_rules; i++) अणु
		अगर (map->rules[i] &&
		    map->rules[i]->mask.ruleset == ruleset &&
		    map->rules[i]->mask.type == type &&
		    map->rules[i]->mask.min_size <= size &&
		    map->rules[i]->mask.max_size >= size)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

/*
 * bucket choose methods
 *
 * For each bucket algorithm, we have a "choose" method that, given a
 * crush input @x and replica position (usually, position in output set) @r,
 * will produce an item in the bucket.
 */

/*
 * Choose based on a अक्रमom permutation of the bucket.
 *
 * We used to use some prime number arithmetic to करो this, but it
 * wasn't very अक्रमom, and had some other bad behaviors.  Instead, we
 * calculate an actual अक्रमom permutation of the bucket members.
 * Since this is expensive, we optimize क्रम the r=0 हाल, which
 * captures the vast majority of calls.
 */
अटल पूर्णांक bucket_perm_choose(स्थिर काष्ठा crush_bucket *bucket,
			      काष्ठा crush_work_bucket *work,
			      पूर्णांक x, पूर्णांक r)
अणु
	अचिन्हित पूर्णांक pr = r % bucket->size;
	अचिन्हित पूर्णांक i, s;

	/* start a new permutation अगर @x has changed */
	अगर (work->perm_x != (__u32)x || work->perm_n == 0) अणु
		dprपूर्णांकk("bucket %d new x=%d\n", bucket->id, x);
		work->perm_x = x;

		/* optimize common r=0 हाल */
		अगर (pr == 0) अणु
			s = crush_hash32_3(bucket->hash, x, bucket->id, 0) %
				bucket->size;
			work->perm[0] = s;
			work->perm_n = 0xffff;   /* magic value, see below */
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < bucket->size; i++)
			work->perm[i] = i;
		work->perm_n = 0;
	पूर्ण अन्यथा अगर (work->perm_n == 0xffff) अणु
		/* clean up after the r=0 हाल above */
		क्रम (i = 1; i < bucket->size; i++)
			work->perm[i] = i;
		work->perm[work->perm[0]] = 0;
		work->perm_n = 1;
	पूर्ण

	/* calculate permutation up to pr */
	क्रम (i = 0; i < work->perm_n; i++)
		dprपूर्णांकk(" perm_choose have %d: %d\n", i, work->perm[i]);
	जबतक (work->perm_n <= pr) अणु
		अचिन्हित पूर्णांक p = work->perm_n;
		/* no poपूर्णांक in swapping the final entry */
		अगर (p < bucket->size - 1) अणु
			i = crush_hash32_3(bucket->hash, x, bucket->id, p) %
				(bucket->size - p);
			अगर (i) अणु
				अचिन्हित पूर्णांक t = work->perm[p + i];
				work->perm[p + i] = work->perm[p];
				work->perm[p] = t;
			पूर्ण
			dprपूर्णांकk(" perm_choose swap %d with %d\n", p, p+i);
		पूर्ण
		work->perm_n++;
	पूर्ण
	क्रम (i = 0; i < bucket->size; i++)
		dprपूर्णांकk(" perm_choose  %d: %d\n", i, work->perm[i]);

	s = work->perm[pr];
out:
	dprपूर्णांकk(" perm_choose %d sz=%d x=%d r=%d (%d) s=%d\n", bucket->id,
		bucket->size, x, r, pr, s);
	वापस bucket->items[s];
पूर्ण

/* unअगरorm */
अटल पूर्णांक bucket_unअगरorm_choose(स्थिर काष्ठा crush_bucket_unअगरorm *bucket,
				 काष्ठा crush_work_bucket *work, पूर्णांक x, पूर्णांक r)
अणु
	वापस bucket_perm_choose(&bucket->h, work, x, r);
पूर्ण

/* list */
अटल पूर्णांक bucket_list_choose(स्थिर काष्ठा crush_bucket_list *bucket,
			      पूर्णांक x, पूर्णांक r)
अणु
	पूर्णांक i;

	क्रम (i = bucket->h.size-1; i >= 0; i--) अणु
		__u64 w = crush_hash32_4(bucket->h.hash, x, bucket->h.items[i],
					 r, bucket->h.id);
		w &= 0xffff;
		dprपूर्णांकk("list_choose i=%d x=%d r=%d item %d weight %x "
			"sw %x rand %llx",
			i, x, r, bucket->h.items[i], bucket->item_weights[i],
			bucket->sum_weights[i], w);
		w *= bucket->sum_weights[i];
		w = w >> 16;
		/*dprपूर्णांकk(" scaled %llx\n", w);*/
		अगर (w < bucket->item_weights[i]) अणु
			वापस bucket->h.items[i];
		पूर्ण
	पूर्ण

	dprपूर्णांकk("bad list sums for bucket %d\n", bucket->h.id);
	वापस bucket->h.items[0];
पूर्ण


/* (binary) tree */
अटल पूर्णांक height(पूर्णांक n)
अणु
	पूर्णांक h = 0;
	जबतक ((n & 1) == 0) अणु
		h++;
		n = n >> 1;
	पूर्ण
	वापस h;
पूर्ण

अटल पूर्णांक left(पूर्णांक x)
अणु
	पूर्णांक h = height(x);
	वापस x - (1 << (h-1));
पूर्ण

अटल पूर्णांक right(पूर्णांक x)
अणु
	पूर्णांक h = height(x);
	वापस x + (1 << (h-1));
पूर्ण

अटल पूर्णांक terminal(पूर्णांक x)
अणु
	वापस x & 1;
पूर्ण

अटल पूर्णांक bucket_tree_choose(स्थिर काष्ठा crush_bucket_tree *bucket,
			      पूर्णांक x, पूर्णांक r)
अणु
	पूर्णांक n;
	__u32 w;
	__u64 t;

	/* start at root */
	n = bucket->num_nodes >> 1;

	जबतक (!terminal(n)) अणु
		पूर्णांक l;
		/* pick poपूर्णांक in [0, w) */
		w = bucket->node_weights[n];
		t = (__u64)crush_hash32_4(bucket->h.hash, x, n, r,
					  bucket->h.id) * (__u64)w;
		t = t >> 32;

		/* descend to the left or right? */
		l = left(n);
		अगर (t < bucket->node_weights[l])
			n = l;
		अन्यथा
			n = right(n);
	पूर्ण

	वापस bucket->h.items[n >> 1];
पूर्ण


/* straw */

अटल पूर्णांक bucket_straw_choose(स्थिर काष्ठा crush_bucket_straw *bucket,
			       पूर्णांक x, पूर्णांक r)
अणु
	__u32 i;
	पूर्णांक high = 0;
	__u64 high_draw = 0;
	__u64 draw;

	क्रम (i = 0; i < bucket->h.size; i++) अणु
		draw = crush_hash32_3(bucket->h.hash, x, bucket->h.items[i], r);
		draw &= 0xffff;
		draw *= bucket->straws[i];
		अगर (i == 0 || draw > high_draw) अणु
			high = i;
			high_draw = draw;
		पूर्ण
	पूर्ण
	वापस bucket->h.items[high];
पूर्ण

/* compute 2^44*log2(input+1) */
अटल __u64 crush_ln(अचिन्हित पूर्णांक xin)
अणु
	अचिन्हित पूर्णांक x = xin;
	पूर्णांक iexpon, index1, index2;
	__u64 RH, LH, LL, xl64, result;

	x++;

	/* normalize input */
	iexpon = 15;

	/*
	 * figure out number of bits we need to shअगरt and
	 * करो it in one step instead of iteratively
	 */
	अगर (!(x & 0x18000)) अणु
		पूर्णांक bits = __builtin_clz(x & 0x1FFFF) - 16;
		x <<= bits;
		iexpon = 15 - bits;
	पूर्ण

	index1 = (x >> 8) << 1;
	/* RH ~ 2^56/index1 */
	RH = __RH_LH_tbl[index1 - 256];
	/* LH ~ 2^48 * log2(index1/256) */
	LH = __RH_LH_tbl[index1 + 1 - 256];

	/* RH*x ~ 2^48 * (2^15 + xf), xf<2^8 */
	xl64 = (__s64)x * RH;
	xl64 >>= 48;

	result = iexpon;
	result <<= (12 + 32);

	index2 = xl64 & 0xff;
	/* LL ~ 2^48*log2(1.0+index2/2^15) */
	LL = __LL_tbl[index2];

	LH = LH + LL;

	LH >>= (48 - 12 - 32);
	result += LH;

	वापस result;
पूर्ण


/*
 * straw2
 *
 * क्रम reference, see:
 *
 * https://en.wikipedia.org/wiki/Exponential_distribution#Distribution_of_the_minimum_of_exponential_अक्रमom_variables
 *
 */

अटल __u32 *get_choose_arg_weights(स्थिर काष्ठा crush_bucket_straw2 *bucket,
				     स्थिर काष्ठा crush_choose_arg *arg,
				     पूर्णांक position)
अणु
	अगर (!arg || !arg->weight_set)
		वापस bucket->item_weights;

	अगर (position >= arg->weight_set_size)
		position = arg->weight_set_size - 1;
	वापस arg->weight_set[position].weights;
पूर्ण

अटल __s32 *get_choose_arg_ids(स्थिर काष्ठा crush_bucket_straw2 *bucket,
				 स्थिर काष्ठा crush_choose_arg *arg)
अणु
	अगर (!arg || !arg->ids)
		वापस bucket->h.items;

	वापस arg->ids;
पूर्ण

अटल पूर्णांक bucket_straw2_choose(स्थिर काष्ठा crush_bucket_straw2 *bucket,
				पूर्णांक x, पूर्णांक r,
				स्थिर काष्ठा crush_choose_arg *arg,
				पूर्णांक position)
अणु
	अचिन्हित पूर्णांक i, high = 0;
	अचिन्हित पूर्णांक u;
	__s64 ln, draw, high_draw = 0;
	__u32 *weights = get_choose_arg_weights(bucket, arg, position);
	__s32 *ids = get_choose_arg_ids(bucket, arg);

	क्रम (i = 0; i < bucket->h.size; i++) अणु
		dprपूर्णांकk("weight 0x%x item %d\n", weights[i], ids[i]);
		अगर (weights[i]) अणु
			u = crush_hash32_3(bucket->h.hash, x, ids[i], r);
			u &= 0xffff;

			/*
			 * क्रम some reason slightly less than 0x10000 produces
			 * a slightly more accurate distribution... probably a
			 * rounding effect.
			 *
			 * the natural log lookup table maps [0,0xffff]
			 * (corresponding to real numbers [1/0x10000, 1] to
			 * [0, 0xffffffffffff] (corresponding to real numbers
			 * [-11.090355,0]).
			 */
			ln = crush_ln(u) - 0x1000000000000ll;

			/*
			 * भागide by 16.16 fixed-poपूर्णांक weight.  note
			 * that the ln value is negative, so a larger
			 * weight means a larger (less negative) value
			 * क्रम draw.
			 */
			draw = भाग64_s64(ln, weights[i]);
		पूर्ण अन्यथा अणु
			draw = S64_MIN;
		पूर्ण

		अगर (i == 0 || draw > high_draw) अणु
			high = i;
			high_draw = draw;
		पूर्ण
	पूर्ण

	वापस bucket->h.items[high];
पूर्ण


अटल पूर्णांक crush_bucket_choose(स्थिर काष्ठा crush_bucket *in,
			       काष्ठा crush_work_bucket *work,
			       पूर्णांक x, पूर्णांक r,
			       स्थिर काष्ठा crush_choose_arg *arg,
			       पूर्णांक position)
अणु
	dprपूर्णांकk(" crush_bucket_choose %d x=%d r=%d\n", in->id, x, r);
	BUG_ON(in->size == 0);
	चयन (in->alg) अणु
	हाल CRUSH_BUCKET_UNIFORM:
		वापस bucket_unअगरorm_choose(
			(स्थिर काष्ठा crush_bucket_unअगरorm *)in,
			work, x, r);
	हाल CRUSH_BUCKET_LIST:
		वापस bucket_list_choose((स्थिर काष्ठा crush_bucket_list *)in,
					  x, r);
	हाल CRUSH_BUCKET_TREE:
		वापस bucket_tree_choose((स्थिर काष्ठा crush_bucket_tree *)in,
					  x, r);
	हाल CRUSH_BUCKET_STRAW:
		वापस bucket_straw_choose(
			(स्थिर काष्ठा crush_bucket_straw *)in,
			x, r);
	हाल CRUSH_BUCKET_STRAW2:
		वापस bucket_straw2_choose(
			(स्थिर काष्ठा crush_bucket_straw2 *)in,
			x, r, arg, position);
	शेष:
		dprपूर्णांकk("unknown bucket %d alg %d\n", in->id, in->alg);
		वापस in->items[0];
	पूर्ण
पूर्ण

/*
 * true अगर device is marked "out" (failed, fully offloaded)
 * of the cluster
 */
अटल पूर्णांक is_out(स्थिर काष्ठा crush_map *map,
		  स्थिर __u32 *weight, पूर्णांक weight_max,
		  पूर्णांक item, पूर्णांक x)
अणु
	अगर (item >= weight_max)
		वापस 1;
	अगर (weight[item] >= 0x10000)
		वापस 0;
	अगर (weight[item] == 0)
		वापस 1;
	अगर ((crush_hash32_2(CRUSH_HASH_RJENKINS1, x, item) & 0xffff)
	    < weight[item])
		वापस 0;
	वापस 1;
पूर्ण

/**
 * crush_choose_firstn - choose numrep distinct items of given type
 * @map: the crush_map
 * @bucket: the bucket we are choose an item from
 * @x: crush input value
 * @numrep: the number of items to choose
 * @type: the type of item to choose
 * @out: poपूर्णांकer to output vector
 * @outpos: our position in that vector
 * @out_size: size of the out vector
 * @tries: number of attempts to make
 * @recurse_tries: number of attempts to have recursive chooseleaf make
 * @local_retries: localized retries
 * @local_fallback_retries: localized fallback retries
 * @recurse_to_leaf: true अगर we want one device under each item of given type (chooseleaf instead of choose)
 * @stable: stable mode starts rep=0 in the recursive call क्रम all replicas
 * @vary_r: pass r to recursive calls
 * @out2: second output vector क्रम leaf items (अगर @recurse_to_leaf)
 * @parent_r: r value passed from the parent
 */
अटल पूर्णांक crush_choose_firstn(स्थिर काष्ठा crush_map *map,
			       काष्ठा crush_work *work,
			       स्थिर काष्ठा crush_bucket *bucket,
			       स्थिर __u32 *weight, पूर्णांक weight_max,
			       पूर्णांक x, पूर्णांक numrep, पूर्णांक type,
			       पूर्णांक *out, पूर्णांक outpos,
			       पूर्णांक out_size,
			       अचिन्हित पूर्णांक tries,
			       अचिन्हित पूर्णांक recurse_tries,
			       अचिन्हित पूर्णांक local_retries,
			       अचिन्हित पूर्णांक local_fallback_retries,
			       पूर्णांक recurse_to_leaf,
			       अचिन्हित पूर्णांक vary_r,
			       अचिन्हित पूर्णांक stable,
			       पूर्णांक *out2,
			       पूर्णांक parent_r,
			       स्थिर काष्ठा crush_choose_arg *choose_args)
अणु
	पूर्णांक rep;
	अचिन्हित पूर्णांक ftotal, flocal;
	पूर्णांक retry_descent, retry_bucket, skip_rep;
	स्थिर काष्ठा crush_bucket *in = bucket;
	पूर्णांक r;
	पूर्णांक i;
	पूर्णांक item = 0;
	पूर्णांक itemtype;
	पूर्णांक collide, reject;
	पूर्णांक count = out_size;

	dprपूर्णांकk("CHOOSE%s bucket %d x %d outpos %d numrep %d tries %d recurse_tries %d local_retries %d local_fallback_retries %d parent_r %d stable %d\n",
		recurse_to_leaf ? "_LEAF" : "",
		bucket->id, x, outpos, numrep,
		tries, recurse_tries, local_retries, local_fallback_retries,
		parent_r, stable);

	क्रम (rep = stable ? 0 : outpos; rep < numrep && count > 0 ; rep++) अणु
		/* keep trying until we get a non-out, non-colliding item */
		ftotal = 0;
		skip_rep = 0;
		करो अणु
			retry_descent = 0;
			in = bucket;               /* initial bucket */

			/* choose through पूर्णांकervening buckets */
			flocal = 0;
			करो अणु
				collide = 0;
				retry_bucket = 0;
				r = rep + parent_r;
				/* r' = r + f_total */
				r += ftotal;

				/* bucket choose */
				अगर (in->size == 0) अणु
					reject = 1;
					जाओ reject;
				पूर्ण
				अगर (local_fallback_retries > 0 &&
				    flocal >= (in->size>>1) &&
				    flocal > local_fallback_retries)
					item = bucket_perm_choose(
						in, work->work[-1-in->id],
						x, r);
				अन्यथा
					item = crush_bucket_choose(
						in, work->work[-1-in->id],
						x, r,
						(choose_args ?
						 &choose_args[-1-in->id] : शून्य),
						outpos);
				अगर (item >= map->max_devices) अणु
					dprपूर्णांकk("   bad item %d\n", item);
					skip_rep = 1;
					अवरोध;
				पूर्ण

				/* desired type? */
				अगर (item < 0)
					itemtype = map->buckets[-1-item]->type;
				अन्यथा
					itemtype = 0;
				dprपूर्णांकk("  item %d type %d\n", item, itemtype);

				/* keep going? */
				अगर (itemtype != type) अणु
					अगर (item >= 0 ||
					    (-1-item) >= map->max_buckets) अणु
						dprपूर्णांकk("   bad item type %d\n", type);
						skip_rep = 1;
						अवरोध;
					पूर्ण
					in = map->buckets[-1-item];
					retry_bucket = 1;
					जारी;
				पूर्ण

				/* collision? */
				क्रम (i = 0; i < outpos; i++) अणु
					अगर (out[i] == item) अणु
						collide = 1;
						अवरोध;
					पूर्ण
				पूर्ण

				reject = 0;
				अगर (!collide && recurse_to_leaf) अणु
					अगर (item < 0) अणु
						पूर्णांक sub_r;
						अगर (vary_r)
							sub_r = r >> (vary_r-1);
						अन्यथा
							sub_r = 0;
						अगर (crush_choose_firstn(
							    map,
							    work,
							    map->buckets[-1-item],
							    weight, weight_max,
							    x, stable ? 1 : outpos+1, 0,
							    out2, outpos, count,
							    recurse_tries, 0,
							    local_retries,
							    local_fallback_retries,
							    0,
							    vary_r,
							    stable,
							    शून्य,
							    sub_r,
							    choose_args) <= outpos)
							/* didn't get leaf */
							reject = 1;
					पूर्ण अन्यथा अणु
						/* we alपढ़ोy have a leaf! */
						out2[outpos] = item;
					पूर्ण
				पूर्ण

				अगर (!reject && !collide) अणु
					/* out? */
					अगर (itemtype == 0)
						reject = is_out(map, weight,
								weight_max,
								item, x);
				पूर्ण

reject:
				अगर (reject || collide) अणु
					ftotal++;
					flocal++;

					अगर (collide && flocal <= local_retries)
						/* retry locally a few बार */
						retry_bucket = 1;
					अन्यथा अगर (local_fallback_retries > 0 &&
						 flocal <= in->size + local_fallback_retries)
						/* exhaustive bucket search */
						retry_bucket = 1;
					अन्यथा अगर (ftotal < tries)
						/* then retry descent */
						retry_descent = 1;
					अन्यथा
						/* अन्यथा give up */
						skip_rep = 1;
					dprपूर्णांकk("  reject %d  collide %d  "
						"ftotal %u  flocal %u\n",
						reject, collide, ftotal,
						flocal);
				पूर्ण
			पूर्ण जबतक (retry_bucket);
		पूर्ण जबतक (retry_descent);

		अगर (skip_rep) अणु
			dprपूर्णांकk("skip rep\n");
			जारी;
		पूर्ण

		dprपूर्णांकk("CHOOSE got %d\n", item);
		out[outpos] = item;
		outpos++;
		count--;
#अगर_अघोषित __KERNEL__
		अगर (map->choose_tries && ftotal <= map->choose_total_tries)
			map->choose_tries[ftotal]++;
#पूर्ण_अगर
	पूर्ण

	dprपूर्णांकk("CHOOSE returns %d\n", outpos);
	वापस outpos;
पूर्ण


/**
 * crush_choose_indep: alternative bपढ़ोth-first positionally stable mapping
 *
 */
अटल व्योम crush_choose_indep(स्थिर काष्ठा crush_map *map,
			       काष्ठा crush_work *work,
			       स्थिर काष्ठा crush_bucket *bucket,
			       स्थिर __u32 *weight, पूर्णांक weight_max,
			       पूर्णांक x, पूर्णांक left, पूर्णांक numrep, पूर्णांक type,
			       पूर्णांक *out, पूर्णांक outpos,
			       अचिन्हित पूर्णांक tries,
			       अचिन्हित पूर्णांक recurse_tries,
			       पूर्णांक recurse_to_leaf,
			       पूर्णांक *out2,
			       पूर्णांक parent_r,
			       स्थिर काष्ठा crush_choose_arg *choose_args)
अणु
	स्थिर काष्ठा crush_bucket *in = bucket;
	पूर्णांक endpos = outpos + left;
	पूर्णांक rep;
	अचिन्हित पूर्णांक ftotal;
	पूर्णांक r;
	पूर्णांक i;
	पूर्णांक item = 0;
	पूर्णांक itemtype;
	पूर्णांक collide;

	dprपूर्णांकk("CHOOSE%s INDEP bucket %d x %d outpos %d numrep %d\n", recurse_to_leaf ? "_LEAF" : "",
		bucket->id, x, outpos, numrep);

	/* initially my result is undefined */
	क्रम (rep = outpos; rep < endpos; rep++) अणु
		out[rep] = CRUSH_ITEM_UNDEF;
		अगर (out2)
			out2[rep] = CRUSH_ITEM_UNDEF;
	पूर्ण

	क्रम (ftotal = 0; left > 0 && ftotal < tries; ftotal++) अणु
#अगर_घोषित DEBUG_INDEP
		अगर (out2 && ftotal) अणु
			dprपूर्णांकk("%u %d a: ", ftotal, left);
			क्रम (rep = outpos; rep < endpos; rep++) अणु
				dprपूर्णांकk(" %d", out[rep]);
			पूर्ण
			dprपूर्णांकk("\n");
			dprपूर्णांकk("%u %d b: ", ftotal, left);
			क्रम (rep = outpos; rep < endpos; rep++) अणु
				dprपूर्णांकk(" %d", out2[rep]);
			पूर्ण
			dprपूर्णांकk("\n");
		पूर्ण
#पूर्ण_अगर
		क्रम (rep = outpos; rep < endpos; rep++) अणु
			अगर (out[rep] != CRUSH_ITEM_UNDEF)
				जारी;

			in = bucket;  /* initial bucket */

			/* choose through पूर्णांकervening buckets */
			क्रम (;;) अणु
				/* note: we base the choice on the position
				 * even in the nested call.  that means that
				 * अगर the first layer chooses the same bucket
				 * in a dअगरferent position, we will tend to
				 * choose a dअगरferent item in that bucket.
				 * this will involve more devices in data
				 * movement and tend to distribute the load.
				 */
				r = rep + parent_r;

				/* be careful */
				अगर (in->alg == CRUSH_BUCKET_UNIFORM &&
				    in->size % numrep == 0)
					/* r'=r+(n+1)*f_total */
					r += (numrep+1) * ftotal;
				अन्यथा
					/* r' = r + n*f_total */
					r += numrep * ftotal;

				/* bucket choose */
				अगर (in->size == 0) अणु
					dprपूर्णांकk("   empty bucket\n");
					अवरोध;
				पूर्ण

				item = crush_bucket_choose(
					in, work->work[-1-in->id],
					x, r,
					(choose_args ?
					 &choose_args[-1-in->id] : शून्य),
					outpos);
				अगर (item >= map->max_devices) अणु
					dprपूर्णांकk("   bad item %d\n", item);
					out[rep] = CRUSH_ITEM_NONE;
					अगर (out2)
						out2[rep] = CRUSH_ITEM_NONE;
					left--;
					अवरोध;
				पूर्ण

				/* desired type? */
				अगर (item < 0)
					itemtype = map->buckets[-1-item]->type;
				अन्यथा
					itemtype = 0;
				dprपूर्णांकk("  item %d type %d\n", item, itemtype);

				/* keep going? */
				अगर (itemtype != type) अणु
					अगर (item >= 0 ||
					    (-1-item) >= map->max_buckets) अणु
						dprपूर्णांकk("   bad item type %d\n", type);
						out[rep] = CRUSH_ITEM_NONE;
						अगर (out2)
							out2[rep] =
								CRUSH_ITEM_NONE;
						left--;
						अवरोध;
					पूर्ण
					in = map->buckets[-1-item];
					जारी;
				पूर्ण

				/* collision? */
				collide = 0;
				क्रम (i = outpos; i < endpos; i++) अणु
					अगर (out[i] == item) अणु
						collide = 1;
						अवरोध;
					पूर्ण
				पूर्ण
				अगर (collide)
					अवरोध;

				अगर (recurse_to_leaf) अणु
					अगर (item < 0) अणु
						crush_choose_indep(
							map,
							work,
							map->buckets[-1-item],
							weight, weight_max,
							x, 1, numrep, 0,
							out2, rep,
							recurse_tries, 0,
							0, शून्य, r,
							choose_args);
						अगर (out2[rep] == CRUSH_ITEM_NONE) अणु
							/* placed nothing; no leaf */
							अवरोध;
						पूर्ण
					पूर्ण अन्यथा अणु
						/* we alपढ़ोy have a leaf! */
						out2[rep] = item;
					पूर्ण
				पूर्ण

				/* out? */
				अगर (itemtype == 0 &&
				    is_out(map, weight, weight_max, item, x))
					अवरोध;

				/* yay! */
				out[rep] = item;
				left--;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (rep = outpos; rep < endpos; rep++) अणु
		अगर (out[rep] == CRUSH_ITEM_UNDEF) अणु
			out[rep] = CRUSH_ITEM_NONE;
		पूर्ण
		अगर (out2 && out2[rep] == CRUSH_ITEM_UNDEF) अणु
			out2[rep] = CRUSH_ITEM_NONE;
		पूर्ण
	पूर्ण
#अगर_अघोषित __KERNEL__
	अगर (map->choose_tries && ftotal <= map->choose_total_tries)
		map->choose_tries[ftotal]++;
#पूर्ण_अगर
#अगर_घोषित DEBUG_INDEP
	अगर (out2) अणु
		dprपूर्णांकk("%u %d a: ", ftotal, left);
		क्रम (rep = outpos; rep < endpos; rep++) अणु
			dprपूर्णांकk(" %d", out[rep]);
		पूर्ण
		dprपूर्णांकk("\n");
		dprपूर्णांकk("%u %d b: ", ftotal, left);
		क्रम (rep = outpos; rep < endpos; rep++) अणु
			dprपूर्णांकk(" %d", out2[rep]);
		पूर्ण
		dprपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण


/*
 * This takes a chunk of memory and sets it up to be a shiny new
 * working area क्रम a CRUSH placement computation. It must be called
 * on any newly allocated memory beक्रमe passing it in to
 * crush_करो_rule. It may be used repeatedly after that, so दीर्घ as the
 * map has not changed. If the map /has/ changed, you must make sure
 * the working size is no smaller than what was allocated and re-run
 * crush_init_workspace.
 *
 * If you करो retain the working space between calls to crush, make it
 * thपढ़ो-local.
 */
व्योम crush_init_workspace(स्थिर काष्ठा crush_map *map, व्योम *v)
अणु
	काष्ठा crush_work *w = v;
	__s32 b;

	/*
	 * We work by moving through the available space and setting
	 * values and poपूर्णांकers as we go.
	 *
	 * It's a bit like Forth's use of the 'allot' word since we
	 * set the poपूर्णांकer first and then reserve the space क्रम it to
	 * poपूर्णांक to by incrementing the poपूर्णांक.
	 */
	v += माप(काष्ठा crush_work);
	w->work = v;
	v += map->max_buckets * माप(काष्ठा crush_work_bucket *);
	क्रम (b = 0; b < map->max_buckets; ++b) अणु
		अगर (!map->buckets[b])
			जारी;

		w->work[b] = v;
		चयन (map->buckets[b]->alg) अणु
		शेष:
			v += माप(काष्ठा crush_work_bucket);
			अवरोध;
		पूर्ण
		w->work[b]->perm_x = 0;
		w->work[b]->perm_n = 0;
		w->work[b]->perm = v;
		v += map->buckets[b]->size * माप(__u32);
	पूर्ण
	BUG_ON(v - (व्योम *)w != map->working_size);
पूर्ण

/**
 * crush_करो_rule - calculate a mapping with the given input and rule
 * @map: the crush_map
 * @ruleno: the rule id
 * @x: hash input
 * @result: poपूर्णांकer to result vector
 * @result_max: maximum result size
 * @weight: weight vector (क्रम map leaves)
 * @weight_max: size of weight vector
 * @cwin: poपूर्णांकer to at least crush_work_size() bytes of memory
 * @choose_args: weights and ids क्रम each known bucket
 */
पूर्णांक crush_करो_rule(स्थिर काष्ठा crush_map *map,
		  पूर्णांक ruleno, पूर्णांक x, पूर्णांक *result, पूर्णांक result_max,
		  स्थिर __u32 *weight, पूर्णांक weight_max,
		  व्योम *cwin, स्थिर काष्ठा crush_choose_arg *choose_args)
अणु
	पूर्णांक result_len;
	काष्ठा crush_work *cw = cwin;
	पूर्णांक *a = cwin + map->working_size;
	पूर्णांक *b = a + result_max;
	पूर्णांक *c = b + result_max;
	पूर्णांक *w = a;
	पूर्णांक *o = b;
	पूर्णांक recurse_to_leaf;
	पूर्णांक wsize = 0;
	पूर्णांक osize;
	पूर्णांक *पंचांगp;
	स्थिर काष्ठा crush_rule *rule;
	__u32 step;
	पूर्णांक i, j;
	पूर्णांक numrep;
	पूर्णांक out_size;
	/*
	 * the original choose_total_tries value was off by one (it
	 * counted "retries" and not "tries").  add one.
	 */
	पूर्णांक choose_tries = map->choose_total_tries + 1;
	पूर्णांक choose_leaf_tries = 0;
	/*
	 * the local tries values were counted as "retries", though,
	 * and need no adjusपंचांगent
	 */
	पूर्णांक choose_local_retries = map->choose_local_tries;
	पूर्णांक choose_local_fallback_retries = map->choose_local_fallback_tries;

	पूर्णांक vary_r = map->chooseleaf_vary_r;
	पूर्णांक stable = map->chooseleaf_stable;

	अगर ((__u32)ruleno >= map->max_rules) अणु
		dprपूर्णांकk(" bad ruleno %d\n", ruleno);
		वापस 0;
	पूर्ण

	rule = map->rules[ruleno];
	result_len = 0;

	क्रम (step = 0; step < rule->len; step++) अणु
		पूर्णांक firstn = 0;
		स्थिर काष्ठा crush_rule_step *curstep = &rule->steps[step];

		चयन (curstep->op) अणु
		हाल CRUSH_RULE_TAKE:
			अगर ((curstep->arg1 >= 0 &&
			     curstep->arg1 < map->max_devices) ||
			    (-1-curstep->arg1 >= 0 &&
			     -1-curstep->arg1 < map->max_buckets &&
			     map->buckets[-1-curstep->arg1])) अणु
				w[0] = curstep->arg1;
				wsize = 1;
			पूर्ण अन्यथा अणु
				dprपूर्णांकk(" bad take value %d\n", curstep->arg1);
			पूर्ण
			अवरोध;

		हाल CRUSH_RULE_SET_CHOOSE_TRIES:
			अगर (curstep->arg1 > 0)
				choose_tries = curstep->arg1;
			अवरोध;

		हाल CRUSH_RULE_SET_CHOOSELEAF_TRIES:
			अगर (curstep->arg1 > 0)
				choose_leaf_tries = curstep->arg1;
			अवरोध;

		हाल CRUSH_RULE_SET_CHOOSE_LOCAL_TRIES:
			अगर (curstep->arg1 >= 0)
				choose_local_retries = curstep->arg1;
			अवरोध;

		हाल CRUSH_RULE_SET_CHOOSE_LOCAL_FALLBACK_TRIES:
			अगर (curstep->arg1 >= 0)
				choose_local_fallback_retries = curstep->arg1;
			अवरोध;

		हाल CRUSH_RULE_SET_CHOOSELEAF_VARY_R:
			अगर (curstep->arg1 >= 0)
				vary_r = curstep->arg1;
			अवरोध;

		हाल CRUSH_RULE_SET_CHOOSELEAF_STABLE:
			अगर (curstep->arg1 >= 0)
				stable = curstep->arg1;
			अवरोध;

		हाल CRUSH_RULE_CHOOSELEAF_FIRSTN:
		हाल CRUSH_RULE_CHOOSE_FIRSTN:
			firstn = 1;
			fallthrough;
		हाल CRUSH_RULE_CHOOSELEAF_INDEP:
		हाल CRUSH_RULE_CHOOSE_INDEP:
			अगर (wsize == 0)
				अवरोध;

			recurse_to_leaf =
				curstep->op ==
				 CRUSH_RULE_CHOOSELEAF_FIRSTN ||
				curstep->op ==
				CRUSH_RULE_CHOOSELEAF_INDEP;

			/* reset output */
			osize = 0;

			क्रम (i = 0; i < wsize; i++) अणु
				पूर्णांक bno;
				numrep = curstep->arg1;
				अगर (numrep <= 0) अणु
					numrep += result_max;
					अगर (numrep <= 0)
						जारी;
				पूर्ण
				j = 0;
				/* make sure bucket id is valid */
				bno = -1 - w[i];
				अगर (bno < 0 || bno >= map->max_buckets) अणु
					/* w[i] is probably CRUSH_ITEM_NONE */
					dprपूर्णांकk("  bad w[i] %d\n", w[i]);
					जारी;
				पूर्ण
				अगर (firstn) अणु
					पूर्णांक recurse_tries;
					अगर (choose_leaf_tries)
						recurse_tries =
							choose_leaf_tries;
					अन्यथा अगर (map->chooseleaf_descend_once)
						recurse_tries = 1;
					अन्यथा
						recurse_tries = choose_tries;
					osize += crush_choose_firstn(
						map,
						cw,
						map->buckets[bno],
						weight, weight_max,
						x, numrep,
						curstep->arg2,
						o+osize, j,
						result_max-osize,
						choose_tries,
						recurse_tries,
						choose_local_retries,
						choose_local_fallback_retries,
						recurse_to_leaf,
						vary_r,
						stable,
						c+osize,
						0,
						choose_args);
				पूर्ण अन्यथा अणु
					out_size = ((numrep < (result_max-osize)) ?
						    numrep : (result_max-osize));
					crush_choose_indep(
						map,
						cw,
						map->buckets[bno],
						weight, weight_max,
						x, out_size, numrep,
						curstep->arg2,
						o+osize, j,
						choose_tries,
						choose_leaf_tries ?
						   choose_leaf_tries : 1,
						recurse_to_leaf,
						c+osize,
						0,
						choose_args);
					osize += out_size;
				पूर्ण
			पूर्ण

			अगर (recurse_to_leaf)
				/* copy final _leaf_ values to output set */
				स_नकल(o, c, osize*माप(*o));

			/* swap o and w arrays */
			पंचांगp = o;
			o = w;
			w = पंचांगp;
			wsize = osize;
			अवरोध;


		हाल CRUSH_RULE_EMIT:
			क्रम (i = 0; i < wsize && result_len < result_max; i++) अणु
				result[result_len] = w[i];
				result_len++;
			पूर्ण
			wsize = 0;
			अवरोध;

		शेष:
			dprपूर्णांकk(" unknown op %d at step %d\n",
				curstep->op, step);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result_len;
पूर्ण
