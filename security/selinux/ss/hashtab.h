<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * A hash table (hashtab) मुख्यtains associations between
 * key values and datum values.  The type of the key values
 * and the type of the datum values is arbitrary.  The
 * functions क्रम hash computation and key comparison are
 * provided by the creator of the table.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#अगर_अघोषित _SS_HASHTAB_H_
#घोषणा _SS_HASHTAB_H_

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>

#घोषणा HASHTAB_MAX_NODES	U32_MAX

काष्ठा hashtab_key_params अणु
	u32 (*hash)(स्थिर व्योम *key);	/* hash function */
	पूर्णांक (*cmp)(स्थिर व्योम *key1, स्थिर व्योम *key2);
					/* key comparison function */
पूर्ण;

काष्ठा hashtab_node अणु
	व्योम *key;
	व्योम *datum;
	काष्ठा hashtab_node *next;
पूर्ण;

काष्ठा hashtab अणु
	काष्ठा hashtab_node **htable;	/* hash table */
	u32 size;			/* number of slots in hash table */
	u32 nel;			/* number of elements in hash table */
पूर्ण;

काष्ठा hashtab_info अणु
	u32 slots_used;
	u32 max_chain_len;
पूर्ण;

/*
 * Initializes a new hash table with the specअगरied अक्षरacteristics.
 *
 * Returns -ENOMEM अगर insufficient space is available or 0 otherwise.
 */
पूर्णांक hashtab_init(काष्ठा hashtab *h, u32 nel_hपूर्णांक);

पूर्णांक __hashtab_insert(काष्ठा hashtab *h, काष्ठा hashtab_node **dst,
		     व्योम *key, व्योम *datum);

/*
 * Inserts the specअगरied (key, datum) pair पूर्णांकo the specअगरied hash table.
 *
 * Returns -ENOMEM on memory allocation error,
 * -EEXIST अगर there is alपढ़ोy an entry with the same key,
 * -EINVAL क्रम general errors or
  0 otherwise.
 */
अटल अंतरभूत पूर्णांक hashtab_insert(काष्ठा hashtab *h, व्योम *key, व्योम *datum,
				 काष्ठा hashtab_key_params key_params)
अणु
	u32 hvalue;
	काष्ठा hashtab_node *prev, *cur;

	cond_resched();

	अगर (!h->size || h->nel == HASHTAB_MAX_NODES)
		वापस -EINVAL;

	hvalue = key_params.hash(key) & (h->size - 1);
	prev = शून्य;
	cur = h->htable[hvalue];
	जबतक (cur) अणु
		पूर्णांक cmp = key_params.cmp(key, cur->key);

		अगर (cmp == 0)
			वापस -EEXIST;
		अगर (cmp < 0)
			अवरोध;
		prev = cur;
		cur = cur->next;
	पूर्ण

	वापस __hashtab_insert(h, prev ? &prev->next : &h->htable[hvalue],
				key, datum);
पूर्ण

/*
 * Searches क्रम the entry with the specअगरied key in the hash table.
 *
 * Returns शून्य अगर no entry has the specअगरied key or
 * the datum of the entry otherwise.
 */
अटल अंतरभूत व्योम *hashtab_search(काष्ठा hashtab *h, स्थिर व्योम *key,
				   काष्ठा hashtab_key_params key_params)
अणु
	u32 hvalue;
	काष्ठा hashtab_node *cur;

	अगर (!h->size)
		वापस शून्य;

	hvalue = key_params.hash(key) & (h->size - 1);
	cur = h->htable[hvalue];
	जबतक (cur) अणु
		पूर्णांक cmp = key_params.cmp(key, cur->key);

		अगर (cmp == 0)
			वापस cur->datum;
		अगर (cmp < 0)
			अवरोध;
		cur = cur->next;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Destroys the specअगरied hash table.
 */
व्योम hashtab_destroy(काष्ठा hashtab *h);

/*
 * Applies the specअगरied apply function to (key,datum,args)
 * क्रम each entry in the specअगरied hash table.
 *
 * The order in which the function is applied to the entries
 * is dependent upon the पूर्णांकernal काष्ठाure of the hash table.
 *
 * If apply वापसs a non-zero status, then hashtab_map will cease
 * iterating through the hash table and will propagate the error
 * वापस to its caller.
 */
पूर्णांक hashtab_map(काष्ठा hashtab *h,
		पूर्णांक (*apply)(व्योम *k, व्योम *d, व्योम *args),
		व्योम *args);

पूर्णांक hashtab_duplicate(काष्ठा hashtab *new, काष्ठा hashtab *orig,
		पूर्णांक (*copy)(काष्ठा hashtab_node *new,
			काष्ठा hashtab_node *orig, व्योम *args),
		पूर्णांक (*destroy)(व्योम *k, व्योम *d, व्योम *args),
		व्योम *args);

/* Fill info with some hash table statistics */
व्योम hashtab_stat(काष्ठा hashtab *h, काष्ठा hashtab_info *info);

#पूर्ण_अगर	/* _SS_HASHTAB_H */
