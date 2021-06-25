<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CEPH_CRUSH_CRUSH_H
#घोषणा CEPH_CRUSH_CRUSH_H

#अगर_घोषित __KERNEL__
# include <linux/rbtree.h>
# include <linux/types.h>
#अन्यथा
# include "crush_compat.h"
#पूर्ण_अगर

/*
 * CRUSH is a pseuकरो-अक्रमom data distribution algorithm that
 * efficiently distributes input values (typically, data objects)
 * across a heterogeneous, काष्ठाured storage cluster.
 *
 * The algorithm was originally described in detail in this paper
 * (although the algorithm has evolved somewhat since then):
 *
 *     https://www.ssrc.ucsc.edu/Papers/weil-sc06.pdf
 *
 * LGPL2
 */


#घोषणा CRUSH_MAGIC 0x00010000ul   /* क्रम detecting algorithm revisions */

#घोषणा CRUSH_MAX_DEPTH 10  /* max crush hierarchy depth */
#घोषणा CRUSH_MAX_RULESET (1<<8)  /* max crush ruleset number */
#घोषणा CRUSH_MAX_RULES CRUSH_MAX_RULESET  /* should be the same as max rulesets */

#घोषणा CRUSH_MAX_DEVICE_WEIGHT (100u * 0x10000u)
#घोषणा CRUSH_MAX_BUCKET_WEIGHT (65535u * 0x10000u)

#घोषणा CRUSH_ITEM_UNDEF  0x7ffffffe  /* undefined result (पूर्णांकernal use only) */
#घोषणा CRUSH_ITEM_NONE   0x7fffffff  /* no result */

/*
 * CRUSH uses user-defined "rules" to describe how inमाला_दो should be
 * mapped to devices.  A rule consists of sequence of steps to perक्रमm
 * to generate the set of output devices.
 */
काष्ठा crush_rule_step अणु
	__u32 op;
	__s32 arg1;
	__s32 arg2;
पूर्ण;

/* step op codes */
क्रमागत अणु
	CRUSH_RULE_NOOP = 0,
	CRUSH_RULE_TAKE = 1,          /* arg1 = value to start with */
	CRUSH_RULE_CHOOSE_FIRSTN = 2, /* arg1 = num items to pick */
				      /* arg2 = type */
	CRUSH_RULE_CHOOSE_INDEP = 3,  /* same */
	CRUSH_RULE_EMIT = 4,          /* no args */
	CRUSH_RULE_CHOOSELEAF_FIRSTN = 6,
	CRUSH_RULE_CHOOSELEAF_INDEP = 7,

	CRUSH_RULE_SET_CHOOSE_TRIES = 8, /* override choose_total_tries */
	CRUSH_RULE_SET_CHOOSELEAF_TRIES = 9, /* override chooseleaf_descend_once */
	CRUSH_RULE_SET_CHOOSE_LOCAL_TRIES = 10,
	CRUSH_RULE_SET_CHOOSE_LOCAL_FALLBACK_TRIES = 11,
	CRUSH_RULE_SET_CHOOSELEAF_VARY_R = 12,
	CRUSH_RULE_SET_CHOOSELEAF_STABLE = 13
पूर्ण;

/*
 * क्रम specअगरying choose num (arg1) relative to the max parameter
 * passed to करो_rule
 */
#घोषणा CRUSH_CHOOSE_N            0
#घोषणा CRUSH_CHOOSE_N_MINUS(x)   (-(x))

/*
 * The rule mask is used to describe what the rule is पूर्णांकended क्रम.
 * Given a ruleset and size of output set, we search through the
 * rule list क्रम a matching rule_mask.
 */
काष्ठा crush_rule_mask अणु
	__u8 ruleset;
	__u8 type;
	__u8 min_size;
	__u8 max_size;
पूर्ण;

काष्ठा crush_rule अणु
	__u32 len;
	काष्ठा crush_rule_mask mask;
	काष्ठा crush_rule_step steps[];
पूर्ण;

#घोषणा crush_rule_size(len) (माप(काष्ठा crush_rule) + \
			      (len)*माप(काष्ठा crush_rule_step))



/*
 * A bucket is a named container of other items (either devices or
 * other buckets).  Items within a bucket are chosen using one of a
 * few dअगरferent algorithms.  The table summarizes how the speed of
 * each option measures up against mapping stability when items are
 * added or हटाओd.
 *
 *  Bucket Alg     Speed       Additions    Removals
 *  ------------------------------------------------
 *  unअगरorm         O(1)       poor         poor
 *  list            O(n)       optimal      poor
 *  tree            O(log n)   good         good
 *  straw           O(n)       better       better
 *  straw2          O(n)       optimal      optimal
 */
क्रमागत अणु
	CRUSH_BUCKET_UNIFORM = 1,
	CRUSH_BUCKET_LIST = 2,
	CRUSH_BUCKET_TREE = 3,
	CRUSH_BUCKET_STRAW = 4,
	CRUSH_BUCKET_STRAW2 = 5,
पूर्ण;
बाह्य स्थिर अक्षर *crush_bucket_alg_name(पूर्णांक alg);

/*
 * although tree was a legacy algorithm, it has been buggy, so
 * exclude it.
 */
#घोषणा CRUSH_LEGACY_ALLOWED_BUCKET_ALGS (	\
		(1 << CRUSH_BUCKET_UNIFORM) |	\
		(1 << CRUSH_BUCKET_LIST) |	\
		(1 << CRUSH_BUCKET_STRAW))

काष्ठा crush_bucket अणु
	__s32 id;        /* this'll be negative */
	__u16 type;      /* non-zero; type=0 is reserved क्रम devices */
	__u8 alg;        /* one of CRUSH_BUCKET_* */
	__u8 hash;       /* which hash function to use, CRUSH_HASH_* */
	__u32 weight;    /* 16-bit fixed poपूर्णांक */
	__u32 size;      /* num items */
	__s32 *items;

पूर्ण;

/** @ingroup API
 *
 * Replacement weights क्रम each item in a bucket. The size of the
 * array must be exactly the size of the straw2 bucket, just as the
 * item_weights array.
 *
 */
काष्ठा crush_weight_set अणु
	__u32 *weights; /*!< 16.16 fixed poपूर्णांक weights
                             in the same order as items */
	__u32 size;     /*!< size of the __weights__ array */
पूर्ण;

/** @ingroup API
 *
 * Replacement weights and ids क्रम a given straw2 bucket, क्रम
 * placement purposes.
 *
 * When crush_करो_rule() chooses the Nth item from a straw2 bucket, the
 * replacement weights found at __weight_set[N]__ are used instead of
 * the weights from __item_weights__. If __N__ is greater than
 * __weight_set_size__, the weights found at __weight_set_size-1__ are
 * used instead. For instance अगर __weight_set__ is:
 *
 *    [ [ 0x10000, 0x20000 ],   // position 0
 *      [ 0x20000, 0x40000 ] ]  // position 1
 *
 * choosing the 0th item will use position 0 weights [ 0x10000, 0x20000 ]
 * choosing the 1th item will use position 1 weights [ 0x20000, 0x40000 ]
 * choosing the 2th item will use position 1 weights [ 0x20000, 0x40000 ]
 * etc.
 *
 */
काष्ठा crush_choose_arg अणु
	__s32 *ids;            /*!< values to use instead of items */
	__u32 ids_size;        /*!< size of the __ids__ array */
	काष्ठा crush_weight_set *weight_set; /*!< weight replacements क्रम
                                                  a given position */
	__u32 weight_set_size; /*!< size of the __weight_set__ array */
पूर्ण;

/** @ingroup API
 *
 * Replacement weights and ids क्रम each bucket in the crushmap. The
 * __size__ of the __args__ array must be exactly the same as the
 * __map->max_buckets__.
 *
 * The __crush_choose_arg__ at index N will be used when choosing
 * an item from the bucket __map->buckets[N]__ bucket, provided it
 * is a straw2 bucket.
 *
 */
काष्ठा crush_choose_arg_map अणु
#अगर_घोषित __KERNEL__
	काष्ठा rb_node node;
	s64 choose_args_index;
#पूर्ण_अगर
	काष्ठा crush_choose_arg *args; /*!< replacement क्रम each bucket
                                            in the crushmap */
	__u32 size;                    /*!< size of the __args__ array */
पूर्ण;

काष्ठा crush_bucket_unअगरorm अणु
	काष्ठा crush_bucket h;
	__u32 item_weight;  /* 16-bit fixed poपूर्णांक; all items equally weighted */
पूर्ण;

काष्ठा crush_bucket_list अणु
	काष्ठा crush_bucket h;
	__u32 *item_weights;  /* 16-bit fixed poपूर्णांक */
	__u32 *sum_weights;   /* 16-bit fixed poपूर्णांक.  element i is sum
				 of weights 0..i, inclusive */
पूर्ण;

काष्ठा crush_bucket_tree अणु
	काष्ठा crush_bucket h;  /* note: h.size is _tree_ size, not number of
				   actual items */
	__u8 num_nodes;
	__u32 *node_weights;
पूर्ण;

काष्ठा crush_bucket_straw अणु
	काष्ठा crush_bucket h;
	__u32 *item_weights;   /* 16-bit fixed poपूर्णांक */
	__u32 *straws;         /* 16-bit fixed poपूर्णांक */
पूर्ण;

काष्ठा crush_bucket_straw2 अणु
	काष्ठा crush_bucket h;
	__u32 *item_weights;   /* 16-bit fixed poपूर्णांक */
पूर्ण;



/*
 * CRUSH map includes all buckets, rules, etc.
 */
काष्ठा crush_map अणु
	काष्ठा crush_bucket **buckets;
	काष्ठा crush_rule **rules;

	__s32 max_buckets;
	__u32 max_rules;
	__s32 max_devices;

	/* choose local retries beक्रमe re-descent */
	__u32 choose_local_tries;
	/* choose local attempts using a fallback permutation beक्रमe
	 * re-descent */
	__u32 choose_local_fallback_tries;
	/* choose attempts beक्रमe giving up */
	__u32 choose_total_tries;
	/* attempt chooseleaf inner descent once क्रम firstn mode; on
	 * reject retry outer descent.  Note that this करोes *not*
	 * apply to a collision: in that हाल we will retry as we used
	 * to. */
	__u32 chooseleaf_descend_once;

	/* अगर non-zero, feed r पूर्णांकo chooseleaf, bit-shअगरted right by (r-1)
	 * bits.  a value of 1 is best क्रम new clusters.  क्रम legacy clusters
	 * that want to limit reshuffling, a value of 3 or 4 will make the
	 * mappings line up a bit better with previous mappings. */
	__u8 chooseleaf_vary_r;

	/* अगर true, it makes chooseleaf firstn to वापस stable results (अगर
	 * no local retry) so that data migrations would be optimal when some
	 * device fails. */
	__u8 chooseleaf_stable;

	/*
	 * This value is calculated after decode or स्थिरruction by
	 * the builder. It is exposed here (rather than having a
	 * 'build CRUSH working space' function) so that callers can
	 * reserve a अटल buffer, allocate space on the stack, or
	 * otherwise aव्योम calling पूर्णांकo the heap allocator अगर they
	 * want to. The size of the working space depends on the map,
	 * जबतक the size of the scratch vector passed to the mapper
	 * depends on the size of the desired result set.
	 *
	 * Nothing stops the caller from allocating both in one swell
	 * foop and passing in two poपूर्णांकs, though.
	 */
	माप_प्रकार working_size;

#अगर_अघोषित __KERNEL__
	/*
	 * version 0 (original) of straw_calc has various flaws.  version 1
	 * fixes a few of them.
	 */
	__u8 straw_calc_version;

	/*
	 * allowed bucket algs is a biपंचांगask, here the bit positions
	 * are CRUSH_BUCKET_*.  note that these are *bits* and
	 * CRUSH_BUCKET_* values are not, so we need to or together (1
	 * << CRUSH_BUCKET_WHATEVER).  The 0th bit is not used to
	 * minimize confusion (bucket type values start at 1).
	 */
	__u32 allowed_bucket_algs;

	__u32 *choose_tries;
#अन्यथा
	/* device/bucket type id -> type name (CrushWrapper::type_map) */
	काष्ठा rb_root type_names;

	/* device/bucket id -> name (CrushWrapper::name_map) */
	काष्ठा rb_root names;

	/* CrushWrapper::choose_args */
	काष्ठा rb_root choose_args;
#पूर्ण_अगर
पूर्ण;


/* crush.c */
बाह्य पूर्णांक crush_get_bucket_item_weight(स्थिर काष्ठा crush_bucket *b, पूर्णांक pos);
बाह्य व्योम crush_destroy_bucket_unअगरorm(काष्ठा crush_bucket_unअगरorm *b);
बाह्य व्योम crush_destroy_bucket_list(काष्ठा crush_bucket_list *b);
बाह्य व्योम crush_destroy_bucket_tree(काष्ठा crush_bucket_tree *b);
बाह्य व्योम crush_destroy_bucket_straw(काष्ठा crush_bucket_straw *b);
बाह्य व्योम crush_destroy_bucket_straw2(काष्ठा crush_bucket_straw2 *b);
बाह्य व्योम crush_destroy_bucket(काष्ठा crush_bucket *b);
बाह्य व्योम crush_destroy_rule(काष्ठा crush_rule *r);
बाह्य व्योम crush_destroy(काष्ठा crush_map *map);

अटल अंतरभूत पूर्णांक crush_calc_tree_node(पूर्णांक i)
अणु
	वापस ((i+1) << 1)-1;
पूर्ण

/*
 * These data काष्ठाures are निजी to the CRUSH implementation. They
 * are exposed in this header file because builder needs their
 * definitions to calculate the total working size.
 *
 * Moving this out of the crush map allow us to treat the CRUSH map as
 * immutable within the mapper and हटाओs the requirement क्रम a CRUSH
 * map lock.
 */
काष्ठा crush_work_bucket अणु
	__u32 perm_x; /* @x क्रम which *perm is defined */
	__u32 perm_n; /* num elements of *perm that are permuted/defined */
	__u32 *perm;  /* Permutation of the bucket's items */
पूर्ण;

काष्ठा crush_work अणु
	काष्ठा crush_work_bucket **work; /* Per-bucket working store */
#अगर_घोषित __KERNEL__
	काष्ठा list_head item;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित __KERNEL__
/* osdmap.c */
व्योम clear_crush_names(काष्ठा rb_root *root);
व्योम clear_choose_args(काष्ठा crush_map *c);
#पूर्ण_अगर

#पूर्ण_अगर
