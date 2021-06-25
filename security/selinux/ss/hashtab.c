<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of the hash table type.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश "hashtab.h"

अटल काष्ठा kmem_cache *hashtab_node_cachep __ro_after_init;

/*
 * Here we simply round the number of elements up to the nearest घातer of two.
 * I tried also other options like rounding करोwn or rounding to the बंदst
 * घातer of two (up or करोwn based on which is बंदr), but I was unable to
 * find any signअगरicant dअगरference in lookup/insert perक्रमmance that would
 * justअगरy चयनing to a dअगरferent (less पूर्णांकuitive) क्रमmula. It could be that
 * a dअगरferent क्रमmula is actually more optimal, but any future changes here
 * should be supported with perक्रमmance/memory usage data.
 *
 * The total memory used by the htable arrays (only) with Feकरोra policy loaded
 * is approximately 163 KB at the समय of writing.
 */
अटल u32 hashtab_compute_size(u32 nel)
अणु
	वापस nel == 0 ? 0 : roundup_घात_of_two(nel);
पूर्ण

पूर्णांक hashtab_init(काष्ठा hashtab *h, u32 nel_hपूर्णांक)
अणु
	h->size = hashtab_compute_size(nel_hपूर्णांक);
	h->nel = 0;
	अगर (!h->size)
		वापस 0;

	h->htable = kसुस्मृति(h->size, माप(*h->htable), GFP_KERNEL);
	वापस h->htable ? 0 : -ENOMEM;
पूर्ण

पूर्णांक __hashtab_insert(काष्ठा hashtab *h, काष्ठा hashtab_node **dst,
		     व्योम *key, व्योम *datum)
अणु
	काष्ठा hashtab_node *newnode;

	newnode = kmem_cache_zalloc(hashtab_node_cachep, GFP_KERNEL);
	अगर (!newnode)
		वापस -ENOMEM;
	newnode->key = key;
	newnode->datum = datum;
	newnode->next = *dst;
	*dst = newnode;

	h->nel++;
	वापस 0;
पूर्ण

व्योम hashtab_destroy(काष्ठा hashtab *h)
अणु
	u32 i;
	काष्ठा hashtab_node *cur, *temp;

	क्रम (i = 0; i < h->size; i++) अणु
		cur = h->htable[i];
		जबतक (cur) अणु
			temp = cur;
			cur = cur->next;
			kmem_cache_मुक्त(hashtab_node_cachep, temp);
		पूर्ण
		h->htable[i] = शून्य;
	पूर्ण

	kमुक्त(h->htable);
	h->htable = शून्य;
पूर्ण

पूर्णांक hashtab_map(काष्ठा hashtab *h,
		पूर्णांक (*apply)(व्योम *k, व्योम *d, व्योम *args),
		व्योम *args)
अणु
	u32 i;
	पूर्णांक ret;
	काष्ठा hashtab_node *cur;

	क्रम (i = 0; i < h->size; i++) अणु
		cur = h->htable[i];
		जबतक (cur) अणु
			ret = apply(cur->key, cur->datum, args);
			अगर (ret)
				वापस ret;
			cur = cur->next;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


व्योम hashtab_stat(काष्ठा hashtab *h, काष्ठा hashtab_info *info)
अणु
	u32 i, chain_len, slots_used, max_chain_len;
	काष्ठा hashtab_node *cur;

	slots_used = 0;
	max_chain_len = 0;
	क्रम (i = 0; i < h->size; i++) अणु
		cur = h->htable[i];
		अगर (cur) अणु
			slots_used++;
			chain_len = 0;
			जबतक (cur) अणु
				chain_len++;
				cur = cur->next;
			पूर्ण

			अगर (chain_len > max_chain_len)
				max_chain_len = chain_len;
		पूर्ण
	पूर्ण

	info->slots_used = slots_used;
	info->max_chain_len = max_chain_len;
पूर्ण

पूर्णांक hashtab_duplicate(काष्ठा hashtab *new, काष्ठा hashtab *orig,
		पूर्णांक (*copy)(काष्ठा hashtab_node *new,
			काष्ठा hashtab_node *orig, व्योम *args),
		पूर्णांक (*destroy)(व्योम *k, व्योम *d, व्योम *args),
		व्योम *args)
अणु
	काष्ठा hashtab_node *cur, *पंचांगp, *tail;
	पूर्णांक i, rc;

	स_रखो(new, 0, माप(*new));

	new->htable = kसुस्मृति(orig->size, माप(*new->htable), GFP_KERNEL);
	अगर (!new->htable)
		वापस -ENOMEM;

	new->size = orig->size;

	क्रम (i = 0; i < orig->size; i++) अणु
		tail = शून्य;
		क्रम (cur = orig->htable[i]; cur; cur = cur->next) अणु
			पंचांगp = kmem_cache_zalloc(hashtab_node_cachep,
						GFP_KERNEL);
			अगर (!पंचांगp)
				जाओ error;
			rc = copy(पंचांगp, cur, args);
			अगर (rc) अणु
				kmem_cache_मुक्त(hashtab_node_cachep, पंचांगp);
				जाओ error;
			पूर्ण
			पंचांगp->next = शून्य;
			अगर (!tail)
				new->htable[i] = पंचांगp;
			अन्यथा
				tail->next = पंचांगp;
			tail = पंचांगp;
			new->nel++;
		पूर्ण
	पूर्ण

	वापस 0;

 error:
	क्रम (i = 0; i < new->size; i++) अणु
		क्रम (cur = new->htable[i]; cur; cur = पंचांगp) अणु
			पंचांगp = cur->next;
			destroy(cur->key, cur->datum, args);
			kmem_cache_मुक्त(hashtab_node_cachep, cur);
		पूर्ण
	पूर्ण
	kmem_cache_मुक्त(hashtab_node_cachep, new);
	वापस -ENOMEM;
पूर्ण

व्योम __init hashtab_cache_init(व्योम)
अणु
		hashtab_node_cachep = kmem_cache_create("hashtab_node",
			माप(काष्ठा hashtab_node),
			0, SLAB_PANIC, शून्य);
पूर्ण
