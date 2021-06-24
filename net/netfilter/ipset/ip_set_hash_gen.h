<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2013 Jozsef Kadlecsik <kadlec@netfilter.org> */

#अगर_अघोषित _IP_SET_HASH_GEN_H
#घोषणा _IP_SET_HASH_GEN_H

#समावेश <linux/rcupdate.h>
#समावेश <linux/jhash.h>
#समावेश <linux/types.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/ipset/ip_set.h>

#घोषणा __ipset_dereference(p)		\
	rcu_dereference_रक्षित(p, 1)
#घोषणा ipset_dereference_nfnl(p)	\
	rcu_dereference_रक्षित(p,	\
		lockdep_nfnl_is_held(NFNL_SUBSYS_IPSET))
#घोषणा ipset_dereference_set(p, set) 	\
	rcu_dereference_रक्षित(p,	\
		lockdep_nfnl_is_held(NFNL_SUBSYS_IPSET) || \
		lockdep_is_held(&(set)->lock))
#घोषणा ipset_dereference_bh_nfnl(p)	\
	rcu_dereference_bh_check(p, 	\
		lockdep_nfnl_is_held(NFNL_SUBSYS_IPSET))

/* Hashing which uses arrays to resolve clashing. The hash table is resized
 * (द्विगुनd) when searching becomes too दीर्घ.
 * Internally jhash is used with the assumption that the size of the
 * stored data is a multiple of माप(u32).
 *
 * Readers and resizing
 *
 * Resizing can be triggered by userspace command only, and those
 * are serialized by the nfnl mutex. During resizing the set is
 * पढ़ो-locked, so the only possible concurrent operations are
 * the kernel side पढ़ोers. Those must be रक्षित by proper RCU locking.
 */

/* Number of elements to store in an initial array block */
#घोषणा AHASH_INIT_SIZE			2
/* Max number of elements to store in an array block */
#घोषणा AHASH_MAX_SIZE			(6 * AHASH_INIT_SIZE)
/* Max muber of elements in the array block when tuned */
#घोषणा AHASH_MAX_TUNED			64

#घोषणा AHASH_MAX(h)			((h)->bucketsize)

/* Max number of elements can be tuned */
#अगर_घोषित IP_SET_HASH_WITH_MULTI
अटल u8
tune_bucketsize(u8 curr, u32 multi)
अणु
	u32 n;

	अगर (multi < curr)
		वापस curr;

	n = curr + AHASH_INIT_SIZE;
	/* Currently, at listing one hash bucket must fit पूर्णांकo a message.
	 * Thereक्रमe we have a hard limit here.
	 */
	वापस n > curr && n <= AHASH_MAX_TUNED ? n : curr;
पूर्ण
#घोषणा TUNE_BUCKETSIZE(h, multi)	\
	((h)->bucketsize = tune_bucketsize((h)->bucketsize, multi))
#अन्यथा
#घोषणा TUNE_BUCKETSIZE(h, multi)
#पूर्ण_अगर

/* A hash bucket */
काष्ठा hbucket अणु
	काष्ठा rcu_head rcu;	/* क्रम call_rcu */
	/* Which positions are used in the array */
	DECLARE_BITMAP(used, AHASH_MAX_TUNED);
	u8 size;		/* size of the array */
	u8 pos;			/* position of the first मुक्त entry */
	अचिन्हित अक्षर value[]	/* the array of the values */
		__aligned(__alignof__(u64));
पूर्ण;

/* Region size क्रम locking == 2^HTABLE_REGION_BITS */
#घोषणा HTABLE_REGION_BITS	10
#घोषणा ahash_numof_locks(htable_bits)		\
	((htable_bits) < HTABLE_REGION_BITS ? 1	\
		: jhash_size((htable_bits) - HTABLE_REGION_BITS))
#घोषणा ahash_माप_regions(htable_bits)		\
	(ahash_numof_locks(htable_bits) * माप(काष्ठा ip_set_region))
#घोषणा ahash_region(n, htable_bits)		\
	((n) % ahash_numof_locks(htable_bits))
#घोषणा ahash_bucket_start(h,  htable_bits)	\
	((htable_bits) < HTABLE_REGION_BITS ? 0	\
		: (h) * jhash_size(HTABLE_REGION_BITS))
#घोषणा ahash_bucket_end(h,  htable_bits)	\
	((htable_bits) < HTABLE_REGION_BITS ? jhash_size(htable_bits)	\
		: ((h) + 1) * jhash_size(HTABLE_REGION_BITS))

काष्ठा htable_gc अणु
	काष्ठा delayed_work dwork;
	काष्ठा ip_set *set;	/* Set the gc beदीर्घs to */
	u32 region;		/* Last gc run position */
पूर्ण;

/* The hash table: the table size stored here in order to make resizing easy */
काष्ठा htable अणु
	atomic_t ref;		/* References क्रम resizing */
	atomic_t uref;		/* References क्रम dumping and gc */
	u8 htable_bits;		/* size of hash table == 2^htable_bits */
	u32 maxelem;		/* Maxelem per region */
	काष्ठा ip_set_region *hregion;	/* Region locks and ext sizes */
	काष्ठा hbucket __rcu *bucket[]; /* hashtable buckets */
पूर्ण;

#घोषणा hbucket(h, i)		((h)->bucket[i])
#घोषणा ext_size(n, dsize)	\
	(माप(काष्ठा hbucket) + (n) * (dsize))

#अगर_अघोषित IPSET_NET_COUNT
#घोषणा IPSET_NET_COUNT		1
#पूर्ण_अगर

/* Book-keeping of the prefixes added to the set */
काष्ठा net_prefixes अणु
	u32 nets[IPSET_NET_COUNT]; /* number of elements क्रम this cidr */
	u8 cidr[IPSET_NET_COUNT];  /* the cidr value */
पूर्ण;

/* Compute the hash table size */
अटल माप_प्रकार
htable_size(u8 hbits)
अणु
	माप_प्रकार hsize;

	/* We must fit both पूर्णांकo u32 in jhash and माप_प्रकार */
	अगर (hbits > 31)
		वापस 0;
	hsize = jhash_size(hbits);
	अगर ((((माप_प्रकार)-1) - माप(काष्ठा htable)) / माप(काष्ठा hbucket *)
	    < hsize)
		वापस 0;

	वापस hsize * माप(काष्ठा hbucket *) + माप(काष्ठा htable);
पूर्ण

#अगर_घोषित IP_SET_HASH_WITH_NETS
#अगर IPSET_NET_COUNT > 1
#घोषणा __CIDR(cidr, i)		(cidr[i])
#अन्यथा
#घोषणा __CIDR(cidr, i)		(cidr)
#पूर्ण_अगर

/* cidr + 1 is stored in net_prefixes to support /0 */
#घोषणा NCIDR_PUT(cidr)		((cidr) + 1)
#घोषणा NCIDR_GET(cidr)		((cidr) - 1)

#अगर_घोषित IP_SET_HASH_WITH_NETS_PACKED
/* When cidr is packed with nomatch, cidr - 1 is stored in the data entry */
#घोषणा DCIDR_PUT(cidr)		((cidr) - 1)
#घोषणा DCIDR_GET(cidr, i)	(__CIDR(cidr, i) + 1)
#अन्यथा
#घोषणा DCIDR_PUT(cidr)		(cidr)
#घोषणा DCIDR_GET(cidr, i)	__CIDR(cidr, i)
#पूर्ण_अगर

#घोषणा INIT_CIDR(cidr, host_mask)	\
	DCIDR_PUT(((cidr) ? NCIDR_GET(cidr) : host_mask))

#अगर_घोषित IP_SET_HASH_WITH_NET0
/* cidr from 0 to HOST_MASK value and c = cidr + 1 */
#घोषणा NLEN			(HOST_MASK + 1)
#घोषणा CIDR_POS(c)		((c) - 1)
#अन्यथा
/* cidr from 1 to HOST_MASK value and c = cidr + 1 */
#घोषणा NLEN			HOST_MASK
#घोषणा CIDR_POS(c)		((c) - 2)
#पूर्ण_अगर

#अन्यथा
#घोषणा NLEN			0
#पूर्ण_अगर /* IP_SET_HASH_WITH_NETS */

#घोषणा SET_ELEM_EXPIRED(set, d)	\
	(SET_WITH_TIMEOUT(set) &&	\
	 ip_set_समयout_expired(ext_समयout(d, set)))

#पूर्ण_अगर /* _IP_SET_HASH_GEN_H */

#अगर_अघोषित MTYPE
#त्रुटि "MTYPE is not defined!"
#पूर्ण_अगर

#अगर_अघोषित HTYPE
#त्रुटि "HTYPE is not defined!"
#पूर्ण_अगर

#अगर_अघोषित HOST_MASK
#त्रुटि "HOST_MASK is not defined!"
#पूर्ण_अगर

/* Family dependent ढाँचाs */

#अघोषित ahash_data
#अघोषित mtype_data_equal
#अघोषित mtype_करो_data_match
#अघोषित mtype_data_set_flags
#अघोषित mtype_data_reset_elem
#अघोषित mtype_data_reset_flags
#अघोषित mtype_data_neपंचांगask
#अघोषित mtype_data_list
#अघोषित mtype_data_next
#अघोषित mtype_elem

#अघोषित mtype_ahash_destroy
#अघोषित mtype_ext_cleanup
#अघोषित mtype_add_cidr
#अघोषित mtype_del_cidr
#अघोषित mtype_ahash_memsize
#अघोषित mtype_flush
#अघोषित mtype_destroy
#अघोषित mtype_same_set
#अघोषित mtype_kadt
#अघोषित mtype_uadt

#अघोषित mtype_add
#अघोषित mtype_del
#अघोषित mtype_test_cidrs
#अघोषित mtype_test
#अघोषित mtype_uref
#अघोषित mtype_resize
#अघोषित mtype_ext_size
#अघोषित mtype_resize_ad
#अघोषित mtype_head
#अघोषित mtype_list
#अघोषित mtype_gc_करो
#अघोषित mtype_gc
#अघोषित mtype_gc_init
#अघोषित mtype_variant
#अघोषित mtype_data_match

#अघोषित htype
#अघोषित HKEY

#घोषणा mtype_data_equal	IPSET_TOKEN(MTYPE, _data_equal)
#अगर_घोषित IP_SET_HASH_WITH_NETS
#घोषणा mtype_करो_data_match	IPSET_TOKEN(MTYPE, _करो_data_match)
#अन्यथा
#घोषणा mtype_करो_data_match(d)	1
#पूर्ण_अगर
#घोषणा mtype_data_set_flags	IPSET_TOKEN(MTYPE, _data_set_flags)
#घोषणा mtype_data_reset_elem	IPSET_TOKEN(MTYPE, _data_reset_elem)
#घोषणा mtype_data_reset_flags	IPSET_TOKEN(MTYPE, _data_reset_flags)
#घोषणा mtype_data_neपंचांगask	IPSET_TOKEN(MTYPE, _data_neपंचांगask)
#घोषणा mtype_data_list		IPSET_TOKEN(MTYPE, _data_list)
#घोषणा mtype_data_next		IPSET_TOKEN(MTYPE, _data_next)
#घोषणा mtype_elem		IPSET_TOKEN(MTYPE, _elem)

#घोषणा mtype_ahash_destroy	IPSET_TOKEN(MTYPE, _ahash_destroy)
#घोषणा mtype_ext_cleanup	IPSET_TOKEN(MTYPE, _ext_cleanup)
#घोषणा mtype_add_cidr		IPSET_TOKEN(MTYPE, _add_cidr)
#घोषणा mtype_del_cidr		IPSET_TOKEN(MTYPE, _del_cidr)
#घोषणा mtype_ahash_memsize	IPSET_TOKEN(MTYPE, _ahash_memsize)
#घोषणा mtype_flush		IPSET_TOKEN(MTYPE, _flush)
#घोषणा mtype_destroy		IPSET_TOKEN(MTYPE, _destroy)
#घोषणा mtype_same_set		IPSET_TOKEN(MTYPE, _same_set)
#घोषणा mtype_kadt		IPSET_TOKEN(MTYPE, _kadt)
#घोषणा mtype_uadt		IPSET_TOKEN(MTYPE, _uadt)

#घोषणा mtype_add		IPSET_TOKEN(MTYPE, _add)
#घोषणा mtype_del		IPSET_TOKEN(MTYPE, _del)
#घोषणा mtype_test_cidrs	IPSET_TOKEN(MTYPE, _test_cidrs)
#घोषणा mtype_test		IPSET_TOKEN(MTYPE, _test)
#घोषणा mtype_uref		IPSET_TOKEN(MTYPE, _uref)
#घोषणा mtype_resize		IPSET_TOKEN(MTYPE, _resize)
#घोषणा mtype_ext_size		IPSET_TOKEN(MTYPE, _ext_size)
#घोषणा mtype_resize_ad		IPSET_TOKEN(MTYPE, _resize_ad)
#घोषणा mtype_head		IPSET_TOKEN(MTYPE, _head)
#घोषणा mtype_list		IPSET_TOKEN(MTYPE, _list)
#घोषणा mtype_gc_करो		IPSET_TOKEN(MTYPE, _gc_करो)
#घोषणा mtype_gc		IPSET_TOKEN(MTYPE, _gc)
#घोषणा mtype_gc_init		IPSET_TOKEN(MTYPE, _gc_init)
#घोषणा mtype_variant		IPSET_TOKEN(MTYPE, _variant)
#घोषणा mtype_data_match	IPSET_TOKEN(MTYPE, _data_match)

#अगर_अघोषित HKEY_DATALEN
#घोषणा HKEY_DATALEN		माप(काष्ठा mtype_elem)
#पूर्ण_अगर

#घोषणा htype			MTYPE

#घोषणा HKEY(data, initval, htable_bits)			\
(अणु								\
	स्थिर u32 *__k = (स्थिर u32 *)data;			\
	u32 __l = HKEY_DATALEN / माप(u32);			\
								\
	BUILD_BUG_ON(HKEY_DATALEN % माप(u32) != 0);		\
								\
	jhash2(__k, __l, initval) & jhash_mask(htable_bits);	\
पूर्ण)

/* The generic hash काष्ठाure */
काष्ठा htype अणु
	काष्ठा htable __rcu *table; /* the hash table */
	काष्ठा htable_gc gc;	/* gc workqueue */
	u32 maxelem;		/* max elements in the hash */
	u32 initval;		/* अक्रमom jhash init value */
#अगर_घोषित IP_SET_HASH_WITH_MARKMASK
	u32 markmask;		/* markmask value क्रम mark mask to store */
#पूर्ण_अगर
	u8 bucketsize;		/* max elements in an array block */
#अगर_घोषित IP_SET_HASH_WITH_NETMASK
	u8 neपंचांगask;		/* neपंचांगask value क्रम subnets to store */
#पूर्ण_अगर
	काष्ठा list_head ad;	/* Resize add|del backlist */
	काष्ठा mtype_elem next; /* temporary storage क्रम uadd */
#अगर_घोषित IP_SET_HASH_WITH_NETS
	काष्ठा net_prefixes nets[NLEN]; /* book-keeping of prefixes */
#पूर्ण_अगर
पूर्ण;

/* ADD|DEL entries saved during resize */
काष्ठा mtype_resize_ad अणु
	काष्ठा list_head list;
	क्रमागत ipset_adt ad;	/* ADD|DEL element */
	काष्ठा mtype_elem d;	/* Element value */
	काष्ठा ip_set_ext ext;	/* Extensions क्रम ADD */
	काष्ठा ip_set_ext mext;	/* Target extensions क्रम ADD */
	u32 flags;		/* Flags क्रम ADD */
पूर्ण;

#अगर_घोषित IP_SET_HASH_WITH_NETS
/* Network cidr size book keeping when the hash stores dअगरferent
 * sized networks. cidr == real cidr + 1 to support /0.
 */
अटल व्योम
mtype_add_cidr(काष्ठा ip_set *set, काष्ठा htype *h, u8 cidr, u8 n)
अणु
	पूर्णांक i, j;

	spin_lock_bh(&set->lock);
	/* Add in increasing prefix order, so larger cidr first */
	क्रम (i = 0, j = -1; i < NLEN && h->nets[i].cidr[n]; i++) अणु
		अगर (j != -1) अणु
			जारी;
		पूर्ण अन्यथा अगर (h->nets[i].cidr[n] < cidr) अणु
			j = i;
		पूर्ण अन्यथा अगर (h->nets[i].cidr[n] == cidr) अणु
			h->nets[CIDR_POS(cidr)].nets[n]++;
			जाओ unlock;
		पूर्ण
	पूर्ण
	अगर (j != -1) अणु
		क्रम (; i > j; i--)
			h->nets[i].cidr[n] = h->nets[i - 1].cidr[n];
	पूर्ण
	h->nets[i].cidr[n] = cidr;
	h->nets[CIDR_POS(cidr)].nets[n] = 1;
unlock:
	spin_unlock_bh(&set->lock);
पूर्ण

अटल व्योम
mtype_del_cidr(काष्ठा ip_set *set, काष्ठा htype *h, u8 cidr, u8 n)
अणु
	u8 i, j, net_end = NLEN - 1;

	spin_lock_bh(&set->lock);
	क्रम (i = 0; i < NLEN; i++) अणु
		अगर (h->nets[i].cidr[n] != cidr)
			जारी;
		h->nets[CIDR_POS(cidr)].nets[n]--;
		अगर (h->nets[CIDR_POS(cidr)].nets[n] > 0)
			जाओ unlock;
		क्रम (j = i; j < net_end && h->nets[j].cidr[n]; j++)
			h->nets[j].cidr[n] = h->nets[j + 1].cidr[n];
		h->nets[j].cidr[n] = 0;
		जाओ unlock;
	पूर्ण
unlock:
	spin_unlock_bh(&set->lock);
पूर्ण
#पूर्ण_अगर

/* Calculate the actual memory size of the set data */
अटल माप_प्रकार
mtype_ahash_memsize(स्थिर काष्ठा htype *h, स्थिर काष्ठा htable *t)
अणु
	वापस माप(*h) + माप(*t) + ahash_माप_regions(t->htable_bits);
पूर्ण

/* Get the ith element from the array block n */
#घोषणा ahash_data(n, i, dsize)	\
	((काष्ठा mtype_elem *)((n)->value + ((i) * (dsize))))

अटल व्योम
mtype_ext_cleanup(काष्ठा ip_set *set, काष्ठा hbucket *n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n->pos; i++)
		अगर (test_bit(i, n->used))
			ip_set_ext_destroy(set, ahash_data(n, i, set->dsize));
पूर्ण

/* Flush a hash type of set: destroy all elements */
अटल व्योम
mtype_flush(काष्ठा ip_set *set)
अणु
	काष्ठा htype *h = set->data;
	काष्ठा htable *t;
	काष्ठा hbucket *n;
	u32 r, i;

	t = ipset_dereference_nfnl(h->table);
	क्रम (r = 0; r < ahash_numof_locks(t->htable_bits); r++) अणु
		spin_lock_bh(&t->hregion[r].lock);
		क्रम (i = ahash_bucket_start(r, t->htable_bits);
		     i < ahash_bucket_end(r, t->htable_bits); i++) अणु
			n = __ipset_dereference(hbucket(t, i));
			अगर (!n)
				जारी;
			अगर (set->extensions & IPSET_EXT_DESTROY)
				mtype_ext_cleanup(set, n);
			/* FIXME: use slab cache */
			rcu_assign_poपूर्णांकer(hbucket(t, i), शून्य);
			kमुक्त_rcu(n, rcu);
		पूर्ण
		t->hregion[r].ext_size = 0;
		t->hregion[r].elements = 0;
		spin_unlock_bh(&t->hregion[r].lock);
	पूर्ण
#अगर_घोषित IP_SET_HASH_WITH_NETS
	स_रखो(h->nets, 0, माप(h->nets));
#पूर्ण_अगर
पूर्ण

/* Destroy the hashtable part of the set */
अटल व्योम
mtype_ahash_destroy(काष्ठा ip_set *set, काष्ठा htable *t, bool ext_destroy)
अणु
	काष्ठा hbucket *n;
	u32 i;

	क्रम (i = 0; i < jhash_size(t->htable_bits); i++) अणु
		n = __ipset_dereference(hbucket(t, i));
		अगर (!n)
			जारी;
		अगर (set->extensions & IPSET_EXT_DESTROY && ext_destroy)
			mtype_ext_cleanup(set, n);
		/* FIXME: use slab cache */
		kमुक्त(n);
	पूर्ण

	ip_set_मुक्त(t->hregion);
	ip_set_मुक्त(t);
पूर्ण

/* Destroy a hash type of set */
अटल व्योम
mtype_destroy(काष्ठा ip_set *set)
अणु
	काष्ठा htype *h = set->data;
	काष्ठा list_head *l, *lt;

	अगर (SET_WITH_TIMEOUT(set))
		cancel_delayed_work_sync(&h->gc.dwork);

	mtype_ahash_destroy(set, ipset_dereference_nfnl(h->table), true);
	list_क्रम_each_safe(l, lt, &h->ad) अणु
		list_del(l);
		kमुक्त(l);
	पूर्ण
	kमुक्त(h);

	set->data = शून्य;
पूर्ण

अटल bool
mtype_same_set(स्थिर काष्ठा ip_set *a, स्थिर काष्ठा ip_set *b)
अणु
	स्थिर काष्ठा htype *x = a->data;
	स्थिर काष्ठा htype *y = b->data;

	/* Resizing changes htable_bits, so we ignore it */
	वापस x->maxelem == y->maxelem &&
	       a->समयout == b->समयout &&
#अगर_घोषित IP_SET_HASH_WITH_NETMASK
	       x->neपंचांगask == y->neपंचांगask &&
#पूर्ण_अगर
#अगर_घोषित IP_SET_HASH_WITH_MARKMASK
	       x->markmask == y->markmask &&
#पूर्ण_अगर
	       a->extensions == b->extensions;
पूर्ण

अटल व्योम
mtype_gc_करो(काष्ठा ip_set *set, काष्ठा htype *h, काष्ठा htable *t, u32 r)
अणु
	काष्ठा hbucket *n, *पंचांगp;
	काष्ठा mtype_elem *data;
	u32 i, j, d;
	माप_प्रकार dsize = set->dsize;
#अगर_घोषित IP_SET_HASH_WITH_NETS
	u8 k;
#पूर्ण_अगर
	u8 htable_bits = t->htable_bits;

	spin_lock_bh(&t->hregion[r].lock);
	क्रम (i = ahash_bucket_start(r, htable_bits);
	     i < ahash_bucket_end(r, htable_bits); i++) अणु
		n = __ipset_dereference(hbucket(t, i));
		अगर (!n)
			जारी;
		क्रम (j = 0, d = 0; j < n->pos; j++) अणु
			अगर (!test_bit(j, n->used)) अणु
				d++;
				जारी;
			पूर्ण
			data = ahash_data(n, j, dsize);
			अगर (!ip_set_समयout_expired(ext_समयout(data, set)))
				जारी;
			pr_debug("expired %u/%u\n", i, j);
			clear_bit(j, n->used);
			smp_mb__after_atomic();
#अगर_घोषित IP_SET_HASH_WITH_NETS
			क्रम (k = 0; k < IPSET_NET_COUNT; k++)
				mtype_del_cidr(set, h,
					NCIDR_PUT(DCIDR_GET(data->cidr, k)),
					k);
#पूर्ण_अगर
			t->hregion[r].elements--;
			ip_set_ext_destroy(set, data);
			d++;
		पूर्ण
		अगर (d >= AHASH_INIT_SIZE) अणु
			अगर (d >= n->size) अणु
				t->hregion[r].ext_size -=
					ext_size(n->size, dsize);
				rcu_assign_poपूर्णांकer(hbucket(t, i), शून्य);
				kमुक्त_rcu(n, rcu);
				जारी;
			पूर्ण
			पंचांगp = kzalloc(माप(*पंचांगp) +
				(n->size - AHASH_INIT_SIZE) * dsize,
				GFP_ATOMIC);
			अगर (!पंचांगp)
				/* Still try to delete expired elements. */
				जारी;
			पंचांगp->size = n->size - AHASH_INIT_SIZE;
			क्रम (j = 0, d = 0; j < n->pos; j++) अणु
				अगर (!test_bit(j, n->used))
					जारी;
				data = ahash_data(n, j, dsize);
				स_नकल(पंचांगp->value + d * dsize,
				       data, dsize);
				set_bit(d, पंचांगp->used);
				d++;
			पूर्ण
			पंचांगp->pos = d;
			t->hregion[r].ext_size -=
				ext_size(AHASH_INIT_SIZE, dsize);
			rcu_assign_poपूर्णांकer(hbucket(t, i), पंचांगp);
			kमुक्त_rcu(n, rcu);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&t->hregion[r].lock);
पूर्ण

अटल व्योम
mtype_gc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा htable_gc *gc;
	काष्ठा ip_set *set;
	काष्ठा htype *h;
	काष्ठा htable *t;
	u32 r, numof_locks;
	अचिन्हित पूर्णांक next_run;

	gc = container_of(work, काष्ठा htable_gc, dwork.work);
	set = gc->set;
	h = set->data;

	spin_lock_bh(&set->lock);
	t = ipset_dereference_set(h->table, set);
	atomic_inc(&t->uref);
	numof_locks = ahash_numof_locks(t->htable_bits);
	r = gc->region++;
	अगर (r >= numof_locks) अणु
		r = gc->region = 0;
	पूर्ण
	next_run = (IPSET_GC_PERIOD(set->समयout) * HZ) / numof_locks;
	अगर (next_run < HZ/10)
		next_run = HZ/10;
	spin_unlock_bh(&set->lock);

	mtype_gc_करो(set, h, t, r);

	अगर (atomic_dec_and_test(&t->uref) && atomic_पढ़ो(&t->ref)) अणु
		pr_debug("Table destroy after resize by expire: %p\n", t);
		mtype_ahash_destroy(set, t, false);
	पूर्ण

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &gc->dwork, next_run);

पूर्ण

अटल व्योम
mtype_gc_init(काष्ठा htable_gc *gc)
अणु
	INIT_DEFERRABLE_WORK(&gc->dwork, mtype_gc);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &gc->dwork, HZ);
पूर्ण

अटल पूर्णांक
mtype_add(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	  काष्ठा ip_set_ext *mext, u32 flags);
अटल पूर्णांक
mtype_del(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	  काष्ठा ip_set_ext *mext, u32 flags);

/* Resize a hash: create a new hash table with करोubling the hashsize
 * and inserting the elements to it. Repeat until we succeed or
 * fail due to memory pressures.
 */
अटल पूर्णांक
mtype_resize(काष्ठा ip_set *set, bool retried)
अणु
	काष्ठा htype *h = set->data;
	काष्ठा htable *t, *orig;
	u8 htable_bits;
	माप_प्रकार hsize, dsize = set->dsize;
#अगर_घोषित IP_SET_HASH_WITH_NETS
	u8 flags;
	काष्ठा mtype_elem *पंचांगp;
#पूर्ण_अगर
	काष्ठा mtype_elem *data;
	काष्ठा mtype_elem *d;
	काष्ठा hbucket *n, *m;
	काष्ठा list_head *l, *lt;
	काष्ठा mtype_resize_ad *x;
	u32 i, j, r, nr, key;
	पूर्णांक ret;

#अगर_घोषित IP_SET_HASH_WITH_NETS
	पंचांगp = kदो_स्मृति(dsize, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;
#पूर्ण_अगर
	orig = ipset_dereference_bh_nfnl(h->table);
	htable_bits = orig->htable_bits;

retry:
	ret = 0;
	htable_bits++;
	अगर (!htable_bits)
		जाओ hbwarn;
	hsize = htable_size(htable_bits);
	अगर (!hsize)
		जाओ hbwarn;
	t = ip_set_alloc(hsize);
	अगर (!t) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	t->hregion = ip_set_alloc(ahash_माप_regions(htable_bits));
	अगर (!t->hregion) अणु
		ip_set_मुक्त(t);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	t->htable_bits = htable_bits;
	t->maxelem = h->maxelem / ahash_numof_locks(htable_bits);
	क्रम (i = 0; i < ahash_numof_locks(htable_bits); i++)
		spin_lock_init(&t->hregion[i].lock);

	/* There can't be another parallel resizing,
	 * but dumping, gc, kernel side add/del are possible
	 */
	orig = ipset_dereference_bh_nfnl(h->table);
	atomic_set(&orig->ref, 1);
	atomic_inc(&orig->uref);
	pr_debug("attempt to resize set %s from %u to %u, t %p\n",
		 set->name, orig->htable_bits, htable_bits, orig);
	क्रम (r = 0; r < ahash_numof_locks(orig->htable_bits); r++) अणु
		/* Expire may replace a hbucket with another one */
		rcu_पढ़ो_lock_bh();
		क्रम (i = ahash_bucket_start(r, orig->htable_bits);
		     i < ahash_bucket_end(r, orig->htable_bits); i++) अणु
			n = __ipset_dereference(hbucket(orig, i));
			अगर (!n)
				जारी;
			क्रम (j = 0; j < n->pos; j++) अणु
				अगर (!test_bit(j, n->used))
					जारी;
				data = ahash_data(n, j, dsize);
				अगर (SET_ELEM_EXPIRED(set, data))
					जारी;
#अगर_घोषित IP_SET_HASH_WITH_NETS
				/* We have पढ़ोers running parallel with us,
				 * so the live data cannot be modअगरied.
				 */
				flags = 0;
				स_नकल(पंचांगp, data, dsize);
				data = पंचांगp;
				mtype_data_reset_flags(data, &flags);
#पूर्ण_अगर
				key = HKEY(data, h->initval, htable_bits);
				m = __ipset_dereference(hbucket(t, key));
				nr = ahash_region(key, htable_bits);
				अगर (!m) अणु
					m = kzalloc(माप(*m) +
					    AHASH_INIT_SIZE * dsize,
					    GFP_ATOMIC);
					अगर (!m) अणु
						ret = -ENOMEM;
						जाओ cleanup;
					पूर्ण
					m->size = AHASH_INIT_SIZE;
					t->hregion[nr].ext_size +=
						ext_size(AHASH_INIT_SIZE,
							 dsize);
					RCU_INIT_POINTER(hbucket(t, key), m);
				पूर्ण अन्यथा अगर (m->pos >= m->size) अणु
					काष्ठा hbucket *ht;

					अगर (m->size >= AHASH_MAX(h)) अणु
						ret = -EAGAIN;
					पूर्ण अन्यथा अणु
						ht = kzalloc(माप(*ht) +
						(m->size + AHASH_INIT_SIZE)
						* dsize,
						GFP_ATOMIC);
						अगर (!ht)
							ret = -ENOMEM;
					पूर्ण
					अगर (ret < 0)
						जाओ cleanup;
					स_नकल(ht, m, माप(काष्ठा hbucket) +
					       m->size * dsize);
					ht->size = m->size + AHASH_INIT_SIZE;
					t->hregion[nr].ext_size +=
						ext_size(AHASH_INIT_SIZE,
							 dsize);
					kमुक्त(m);
					m = ht;
					RCU_INIT_POINTER(hbucket(t, key), ht);
				पूर्ण
				d = ahash_data(m, m->pos, dsize);
				स_नकल(d, data, dsize);
				set_bit(m->pos++, m->used);
				t->hregion[nr].elements++;
#अगर_घोषित IP_SET_HASH_WITH_NETS
				mtype_data_reset_flags(d, &flags);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock_bh();
	पूर्ण

	/* There can't be any other ग_लिखोr. */
	rcu_assign_poपूर्णांकer(h->table, t);

	/* Give समय to other पढ़ोers of the set */
	synchronize_rcu();

	pr_debug("set %s resized from %u (%p) to %u (%p)\n", set->name,
		 orig->htable_bits, orig, t->htable_bits, t);
	/* Add/delete elements processed by the SET target during resize.
	 * Kernel-side add cannot trigger a resize and userspace actions
	 * are serialized by the mutex.
	 */
	list_क्रम_each_safe(l, lt, &h->ad) अणु
		x = list_entry(l, काष्ठा mtype_resize_ad, list);
		अगर (x->ad == IPSET_ADD) अणु
			mtype_add(set, &x->d, &x->ext, &x->mext, x->flags);
		पूर्ण अन्यथा अणु
			mtype_del(set, &x->d, शून्य, शून्य, 0);
		पूर्ण
		list_del(l);
		kमुक्त(l);
	पूर्ण
	/* If there's nobody अन्यथा using the table, destroy it */
	अगर (atomic_dec_and_test(&orig->uref)) अणु
		pr_debug("Table destroy by resize %p\n", orig);
		mtype_ahash_destroy(set, orig, false);
	पूर्ण

out:
#अगर_घोषित IP_SET_HASH_WITH_NETS
	kमुक्त(पंचांगp);
#पूर्ण_अगर
	वापस ret;

cleanup:
	rcu_पढ़ो_unlock_bh();
	atomic_set(&orig->ref, 0);
	atomic_dec(&orig->uref);
	mtype_ahash_destroy(set, t, false);
	अगर (ret == -EAGAIN)
		जाओ retry;
	जाओ out;

hbwarn:
	/* In हाल we have plenty of memory :-) */
	pr_warn("Cannot increase the hashsize of set %s further\n", set->name);
	ret = -IPSET_ERR_HASH_FULL;
	जाओ out;
पूर्ण

/* Get the current number of elements and ext_size in the set  */
अटल व्योम
mtype_ext_size(काष्ठा ip_set *set, u32 *elements, माप_प्रकार *ext_size)
अणु
	काष्ठा htype *h = set->data;
	स्थिर काष्ठा htable *t;
	u32 i, j, r;
	काष्ठा hbucket *n;
	काष्ठा mtype_elem *data;

	t = rcu_dereference_bh(h->table);
	क्रम (r = 0; r < ahash_numof_locks(t->htable_bits); r++) अणु
		क्रम (i = ahash_bucket_start(r, t->htable_bits);
		     i < ahash_bucket_end(r, t->htable_bits); i++) अणु
			n = rcu_dereference_bh(hbucket(t, i));
			अगर (!n)
				जारी;
			क्रम (j = 0; j < n->pos; j++) अणु
				अगर (!test_bit(j, n->used))
					जारी;
				data = ahash_data(n, j, set->dsize);
				अगर (!SET_ELEM_EXPIRED(set, data))
					(*elements)++;
			पूर्ण
		पूर्ण
		*ext_size += t->hregion[r].ext_size;
	पूर्ण
पूर्ण

/* Add an element to a hash and update the पूर्णांकernal counters when succeeded,
 * otherwise report the proper error code.
 */
अटल पूर्णांक
mtype_add(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	  काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा htype *h = set->data;
	काष्ठा htable *t;
	स्थिर काष्ठा mtype_elem *d = value;
	काष्ठा mtype_elem *data;
	काष्ठा hbucket *n, *old = ERR_PTR(-ENOENT);
	पूर्णांक i, j = -1, ret;
	bool flag_exist = flags & IPSET_FLAG_EXIST;
	bool deleted = false, क्रमceadd = false, reuse = false;
	u32 r, key, multi = 0, elements, maxelem;

	rcu_पढ़ो_lock_bh();
	t = rcu_dereference_bh(h->table);
	key = HKEY(value, h->initval, t->htable_bits);
	r = ahash_region(key, t->htable_bits);
	atomic_inc(&t->uref);
	elements = t->hregion[r].elements;
	maxelem = t->maxelem;
	अगर (elements >= maxelem) अणु
		u32 e;
		अगर (SET_WITH_TIMEOUT(set)) अणु
			rcu_पढ़ो_unlock_bh();
			mtype_gc_करो(set, h, t, r);
			rcu_पढ़ो_lock_bh();
		पूर्ण
		maxelem = h->maxelem;
		elements = 0;
		क्रम (e = 0; e < ahash_numof_locks(t->htable_bits); e++)
			elements += t->hregion[e].elements;
		अगर (elements >= maxelem && SET_WITH_FORCEADD(set))
			क्रमceadd = true;
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	spin_lock_bh(&t->hregion[r].lock);
	n = rcu_dereference_bh(hbucket(t, key));
	अगर (!n) अणु
		अगर (क्रमceadd || elements >= maxelem)
			जाओ set_full;
		old = शून्य;
		n = kzalloc(माप(*n) + AHASH_INIT_SIZE * set->dsize,
			    GFP_ATOMIC);
		अगर (!n) अणु
			ret = -ENOMEM;
			जाओ unlock;
		पूर्ण
		n->size = AHASH_INIT_SIZE;
		t->hregion[r].ext_size +=
			ext_size(AHASH_INIT_SIZE, set->dsize);
		जाओ copy_elem;
	पूर्ण
	क्रम (i = 0; i < n->pos; i++) अणु
		अगर (!test_bit(i, n->used)) अणु
			/* Reuse first deleted entry */
			अगर (j == -1) अणु
				deleted = reuse = true;
				j = i;
			पूर्ण
			जारी;
		पूर्ण
		data = ahash_data(n, i, set->dsize);
		अगर (mtype_data_equal(data, d, &multi)) अणु
			अगर (flag_exist || SET_ELEM_EXPIRED(set, data)) अणु
				/* Just the extensions could be overwritten */
				j = i;
				जाओ overग_लिखो_extensions;
			पूर्ण
			ret = -IPSET_ERR_EXIST;
			जाओ unlock;
		पूर्ण
		/* Reuse first समयd out entry */
		अगर (SET_ELEM_EXPIRED(set, data) && j == -1) अणु
			j = i;
			reuse = true;
		पूर्ण
	पूर्ण
	अगर (reuse || क्रमceadd) अणु
		अगर (j == -1)
			j = 0;
		data = ahash_data(n, j, set->dsize);
		अगर (!deleted) अणु
#अगर_घोषित IP_SET_HASH_WITH_NETS
			क्रम (i = 0; i < IPSET_NET_COUNT; i++)
				mtype_del_cidr(set, h,
					NCIDR_PUT(DCIDR_GET(data->cidr, i)),
					i);
#पूर्ण_अगर
			ip_set_ext_destroy(set, data);
			t->hregion[r].elements--;
		पूर्ण
		जाओ copy_data;
	पूर्ण
	अगर (elements >= maxelem)
		जाओ set_full;
	/* Create a new slot */
	अगर (n->pos >= n->size) अणु
		TUNE_BUCKETSIZE(h, multi);
		अगर (n->size >= AHASH_MAX(h)) अणु
			/* Trigger rehashing */
			mtype_data_next(&h->next, d);
			ret = -EAGAIN;
			जाओ resize;
		पूर्ण
		old = n;
		n = kzalloc(माप(*n) +
			    (old->size + AHASH_INIT_SIZE) * set->dsize,
			    GFP_ATOMIC);
		अगर (!n) अणु
			ret = -ENOMEM;
			जाओ unlock;
		पूर्ण
		स_नकल(n, old, माप(काष्ठा hbucket) +
		       old->size * set->dsize);
		n->size = old->size + AHASH_INIT_SIZE;
		t->hregion[r].ext_size +=
			ext_size(AHASH_INIT_SIZE, set->dsize);
	पूर्ण

copy_elem:
	j = n->pos++;
	data = ahash_data(n, j, set->dsize);
copy_data:
	t->hregion[r].elements++;
#अगर_घोषित IP_SET_HASH_WITH_NETS
	क्रम (i = 0; i < IPSET_NET_COUNT; i++)
		mtype_add_cidr(set, h, NCIDR_PUT(DCIDR_GET(d->cidr, i)), i);
#पूर्ण_अगर
	स_नकल(data, d, माप(काष्ठा mtype_elem));
overग_लिखो_extensions:
#अगर_घोषित IP_SET_HASH_WITH_NETS
	mtype_data_set_flags(data, flags);
#पूर्ण_अगर
	अगर (SET_WITH_COUNTER(set))
		ip_set_init_counter(ext_counter(data, set), ext);
	अगर (SET_WITH_COMMENT(set))
		ip_set_init_comment(set, ext_comment(data, set), ext);
	अगर (SET_WITH_SKBINFO(set))
		ip_set_init_skbinfo(ext_skbinfo(data, set), ext);
	/* Must come last क्रम the हाल when समयd out entry is reused */
	अगर (SET_WITH_TIMEOUT(set))
		ip_set_समयout_set(ext_समयout(data, set), ext->समयout);
	smp_mb__beक्रमe_atomic();
	set_bit(j, n->used);
	अगर (old != ERR_PTR(-ENOENT)) अणु
		rcu_assign_poपूर्णांकer(hbucket(t, key), n);
		अगर (old)
			kमुक्त_rcu(old, rcu);
	पूर्ण
	ret = 0;
resize:
	spin_unlock_bh(&t->hregion[r].lock);
	अगर (atomic_पढ़ो(&t->ref) && ext->target) अणु
		/* Resize is in process and kernel side add, save values */
		काष्ठा mtype_resize_ad *x;

		x = kzalloc(माप(काष्ठा mtype_resize_ad), GFP_ATOMIC);
		अगर (!x)
			/* Don't bother */
			जाओ out;
		x->ad = IPSET_ADD;
		स_नकल(&x->d, value, माप(काष्ठा mtype_elem));
		स_नकल(&x->ext, ext, माप(काष्ठा ip_set_ext));
		स_नकल(&x->mext, mext, माप(काष्ठा ip_set_ext));
		x->flags = flags;
		spin_lock_bh(&set->lock);
		list_add_tail(&x->list, &h->ad);
		spin_unlock_bh(&set->lock);
	पूर्ण
	जाओ out;

set_full:
	अगर (net_ratelimit())
		pr_warn("Set %s is full, maxelem %u reached\n",
			set->name, maxelem);
	ret = -IPSET_ERR_HASH_FULL;
unlock:
	spin_unlock_bh(&t->hregion[r].lock);
out:
	अगर (atomic_dec_and_test(&t->uref) && atomic_पढ़ो(&t->ref)) अणु
		pr_debug("Table destroy after resize by add: %p\n", t);
		mtype_ahash_destroy(set, t, false);
	पूर्ण
	वापस ret;
पूर्ण

/* Delete an element from the hash and मुक्त up space अगर possible.
 */
अटल पूर्णांक
mtype_del(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	  काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा htype *h = set->data;
	काष्ठा htable *t;
	स्थिर काष्ठा mtype_elem *d = value;
	काष्ठा mtype_elem *data;
	काष्ठा hbucket *n;
	काष्ठा mtype_resize_ad *x = शून्य;
	पूर्णांक i, j, k, r, ret = -IPSET_ERR_EXIST;
	u32 key, multi = 0;
	माप_प्रकार dsize = set->dsize;

	/* Userspace add and resize is excluded by the mutex.
	 * Kernespace add करोes not trigger resize.
	 */
	rcu_पढ़ो_lock_bh();
	t = rcu_dereference_bh(h->table);
	key = HKEY(value, h->initval, t->htable_bits);
	r = ahash_region(key, t->htable_bits);
	atomic_inc(&t->uref);
	rcu_पढ़ो_unlock_bh();

	spin_lock_bh(&t->hregion[r].lock);
	n = rcu_dereference_bh(hbucket(t, key));
	अगर (!n)
		जाओ out;
	क्रम (i = 0, k = 0; i < n->pos; i++) अणु
		अगर (!test_bit(i, n->used)) अणु
			k++;
			जारी;
		पूर्ण
		data = ahash_data(n, i, dsize);
		अगर (!mtype_data_equal(data, d, &multi))
			जारी;
		अगर (SET_ELEM_EXPIRED(set, data))
			जाओ out;

		ret = 0;
		clear_bit(i, n->used);
		smp_mb__after_atomic();
		अगर (i + 1 == n->pos)
			n->pos--;
		t->hregion[r].elements--;
#अगर_घोषित IP_SET_HASH_WITH_NETS
		क्रम (j = 0; j < IPSET_NET_COUNT; j++)
			mtype_del_cidr(set, h,
				       NCIDR_PUT(DCIDR_GET(d->cidr, j)), j);
#पूर्ण_अगर
		ip_set_ext_destroy(set, data);

		अगर (atomic_पढ़ो(&t->ref) && ext->target) अणु
			/* Resize is in process and kernel side del,
			 * save values
			 */
			x = kzalloc(माप(काष्ठा mtype_resize_ad),
				    GFP_ATOMIC);
			अगर (x) अणु
				x->ad = IPSET_DEL;
				स_नकल(&x->d, value,
				       माप(काष्ठा mtype_elem));
				x->flags = flags;
			पूर्ण
		पूर्ण
		क्रम (; i < n->pos; i++) अणु
			अगर (!test_bit(i, n->used))
				k++;
		पूर्ण
		अगर (n->pos == 0 && k == 0) अणु
			t->hregion[r].ext_size -= ext_size(n->size, dsize);
			rcu_assign_poपूर्णांकer(hbucket(t, key), शून्य);
			kमुक्त_rcu(n, rcu);
		पूर्ण अन्यथा अगर (k >= AHASH_INIT_SIZE) अणु
			काष्ठा hbucket *पंचांगp = kzalloc(माप(*पंचांगp) +
					(n->size - AHASH_INIT_SIZE) * dsize,
					GFP_ATOMIC);
			अगर (!पंचांगp)
				जाओ out;
			पंचांगp->size = n->size - AHASH_INIT_SIZE;
			क्रम (j = 0, k = 0; j < n->pos; j++) अणु
				अगर (!test_bit(j, n->used))
					जारी;
				data = ahash_data(n, j, dsize);
				स_नकल(पंचांगp->value + k * dsize, data, dsize);
				set_bit(k, पंचांगp->used);
				k++;
			पूर्ण
			पंचांगp->pos = k;
			t->hregion[r].ext_size -=
				ext_size(AHASH_INIT_SIZE, dsize);
			rcu_assign_poपूर्णांकer(hbucket(t, key), पंचांगp);
			kमुक्त_rcu(n, rcu);
		पूर्ण
		जाओ out;
	पूर्ण

out:
	spin_unlock_bh(&t->hregion[r].lock);
	अगर (x) अणु
		spin_lock_bh(&set->lock);
		list_add(&x->list, &h->ad);
		spin_unlock_bh(&set->lock);
	पूर्ण
	अगर (atomic_dec_and_test(&t->uref) && atomic_पढ़ो(&t->ref)) अणु
		pr_debug("Table destroy after resize by del: %p\n", t);
		mtype_ahash_destroy(set, t, false);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
mtype_data_match(काष्ठा mtype_elem *data, स्थिर काष्ठा ip_set_ext *ext,
		 काष्ठा ip_set_ext *mext, काष्ठा ip_set *set, u32 flags)
अणु
	अगर (!ip_set_match_extensions(set, ext, mext, flags, data))
		वापस 0;
	/* nomatch entries वापस -ENOTEMPTY */
	वापस mtype_करो_data_match(data);
पूर्ण

#अगर_घोषित IP_SET_HASH_WITH_NETS
/* Special test function which takes पूर्णांकo account the dअगरferent network
 * sizes added to the set
 */
अटल पूर्णांक
mtype_test_cidrs(काष्ठा ip_set *set, काष्ठा mtype_elem *d,
		 स्थिर काष्ठा ip_set_ext *ext,
		 काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा htype *h = set->data;
	काष्ठा htable *t = rcu_dereference_bh(h->table);
	काष्ठा hbucket *n;
	काष्ठा mtype_elem *data;
#अगर IPSET_NET_COUNT == 2
	काष्ठा mtype_elem orig = *d;
	पूर्णांक ret, i, j = 0, k;
#अन्यथा
	पूर्णांक ret, i, j = 0;
#पूर्ण_अगर
	u32 key, multi = 0;

	pr_debug("test by nets\n");
	क्रम (; j < NLEN && h->nets[j].cidr[0] && !multi; j++) अणु
#अगर IPSET_NET_COUNT == 2
		mtype_data_reset_elem(d, &orig);
		mtype_data_neपंचांगask(d, NCIDR_GET(h->nets[j].cidr[0]), false);
		क्रम (k = 0; k < NLEN && h->nets[k].cidr[1] && !multi;
		     k++) अणु
			mtype_data_neपंचांगask(d, NCIDR_GET(h->nets[k].cidr[1]),
					   true);
#अन्यथा
		mtype_data_neपंचांगask(d, NCIDR_GET(h->nets[j].cidr[0]));
#पूर्ण_अगर
		key = HKEY(d, h->initval, t->htable_bits);
		n = rcu_dereference_bh(hbucket(t, key));
		अगर (!n)
			जारी;
		क्रम (i = 0; i < n->pos; i++) अणु
			अगर (!test_bit(i, n->used))
				जारी;
			data = ahash_data(n, i, set->dsize);
			अगर (!mtype_data_equal(data, d, &multi))
				जारी;
			ret = mtype_data_match(data, ext, mext, set, flags);
			अगर (ret != 0)
				वापस ret;
#अगर_घोषित IP_SET_HASH_WITH_MULTI
			/* No match, reset multiple match flag */
			multi = 0;
#पूर्ण_अगर
		पूर्ण
#अगर IPSET_NET_COUNT == 2
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Test whether the element is added to the set */
अटल पूर्णांक
mtype_test(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	   काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा htype *h = set->data;
	काष्ठा htable *t;
	काष्ठा mtype_elem *d = value;
	काष्ठा hbucket *n;
	काष्ठा mtype_elem *data;
	पूर्णांक i, ret = 0;
	u32 key, multi = 0;

	rcu_पढ़ो_lock_bh();
	t = rcu_dereference_bh(h->table);
#अगर_घोषित IP_SET_HASH_WITH_NETS
	/* If we test an IP address and not a network address,
	 * try all possible network sizes
	 */
	क्रम (i = 0; i < IPSET_NET_COUNT; i++)
		अगर (DCIDR_GET(d->cidr, i) != HOST_MASK)
			अवरोध;
	अगर (i == IPSET_NET_COUNT) अणु
		ret = mtype_test_cidrs(set, d, ext, mext, flags);
		जाओ out;
	पूर्ण
#पूर्ण_अगर

	key = HKEY(d, h->initval, t->htable_bits);
	n = rcu_dereference_bh(hbucket(t, key));
	अगर (!n) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < n->pos; i++) अणु
		अगर (!test_bit(i, n->used))
			जारी;
		data = ahash_data(n, i, set->dsize);
		अगर (!mtype_data_equal(data, d, &multi))
			जारी;
		ret = mtype_data_match(data, ext, mext, set, flags);
		अगर (ret != 0)
			जाओ out;
	पूर्ण
out:
	rcu_पढ़ो_unlock_bh();
	वापस ret;
पूर्ण

/* Reply a HEADER request: fill out the header part of the set */
अटल पूर्णांक
mtype_head(काष्ठा ip_set *set, काष्ठा sk_buff *skb)
अणु
	काष्ठा htype *h = set->data;
	स्थिर काष्ठा htable *t;
	काष्ठा nlattr *nested;
	माप_प्रकार memsize;
	u32 elements = 0;
	माप_प्रकार ext_size = 0;
	u8 htable_bits;

	rcu_पढ़ो_lock_bh();
	t = rcu_dereference_bh(h->table);
	mtype_ext_size(set, &elements, &ext_size);
	memsize = mtype_ahash_memsize(h, t) + ext_size + set->ext_size;
	htable_bits = t->htable_bits;
	rcu_पढ़ो_unlock_bh();

	nested = nla_nest_start(skb, IPSET_ATTR_DATA);
	अगर (!nested)
		जाओ nla_put_failure;
	अगर (nla_put_net32(skb, IPSET_ATTR_HASHSIZE,
			  htonl(jhash_size(htable_bits))) ||
	    nla_put_net32(skb, IPSET_ATTR_MAXELEM, htonl(h->maxelem)))
		जाओ nla_put_failure;
#अगर_घोषित IP_SET_HASH_WITH_NETMASK
	अगर (h->neपंचांगask != HOST_MASK &&
	    nla_put_u8(skb, IPSET_ATTR_NETMASK, h->neपंचांगask))
		जाओ nla_put_failure;
#पूर्ण_अगर
#अगर_घोषित IP_SET_HASH_WITH_MARKMASK
	अगर (nla_put_u32(skb, IPSET_ATTR_MARKMASK, h->markmask))
		जाओ nla_put_failure;
#पूर्ण_अगर
	अगर (set->flags & IPSET_CREATE_FLAG_BUCKETSIZE) अणु
		अगर (nla_put_u8(skb, IPSET_ATTR_BUCKETSIZE, h->bucketsize) ||
		    nla_put_net32(skb, IPSET_ATTR_INITVAL, htonl(h->initval)))
			जाओ nla_put_failure;
	पूर्ण
	अगर (nla_put_net32(skb, IPSET_ATTR_REFERENCES, htonl(set->ref)) ||
	    nla_put_net32(skb, IPSET_ATTR_MEMSIZE, htonl(memsize)) ||
	    nla_put_net32(skb, IPSET_ATTR_ELEMENTS, htonl(elements)))
		जाओ nla_put_failure;
	अगर (unlikely(ip_set_put_flags(skb, set)))
		जाओ nla_put_failure;
	nla_nest_end(skb, nested);

	वापस 0;
nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

/* Make possible to run dumping parallel with resizing */
अटल व्योम
mtype_uref(काष्ठा ip_set *set, काष्ठा netlink_callback *cb, bool start)
अणु
	काष्ठा htype *h = set->data;
	काष्ठा htable *t;

	अगर (start) अणु
		rcu_पढ़ो_lock_bh();
		t = ipset_dereference_bh_nfnl(h->table);
		atomic_inc(&t->uref);
		cb->args[IPSET_CB_PRIVATE] = (अचिन्हित दीर्घ)t;
		rcu_पढ़ो_unlock_bh();
	पूर्ण अन्यथा अगर (cb->args[IPSET_CB_PRIVATE]) अणु
		t = (काष्ठा htable *)cb->args[IPSET_CB_PRIVATE];
		अगर (atomic_dec_and_test(&t->uref) && atomic_पढ़ो(&t->ref)) अणु
			pr_debug("Table destroy after resize "
				 " by dump: %p\n", t);
			mtype_ahash_destroy(set, t, false);
		पूर्ण
		cb->args[IPSET_CB_PRIVATE] = 0;
	पूर्ण
पूर्ण

/* Reply a LIST/SAVE request: dump the elements of the specअगरied set */
अटल पूर्णांक
mtype_list(स्थिर काष्ठा ip_set *set,
	   काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा htable *t;
	काष्ठा nlattr *atd, *nested;
	स्थिर काष्ठा hbucket *n;
	स्थिर काष्ठा mtype_elem *e;
	u32 first = cb->args[IPSET_CB_ARG0];
	/* We assume that one hash bucket fills पूर्णांकo one page */
	व्योम *incomplete;
	पूर्णांक i, ret = 0;

	atd = nla_nest_start(skb, IPSET_ATTR_ADT);
	अगर (!atd)
		वापस -EMSGSIZE;

	pr_debug("list hash set %s\n", set->name);
	t = (स्थिर काष्ठा htable *)cb->args[IPSET_CB_PRIVATE];
	/* Expire may replace a hbucket with another one */
	rcu_पढ़ो_lock();
	क्रम (; cb->args[IPSET_CB_ARG0] < jhash_size(t->htable_bits);
	     cb->args[IPSET_CB_ARG0]++) अणु
		cond_resched_rcu();
		incomplete = skb_tail_poपूर्णांकer(skb);
		n = rcu_dereference(hbucket(t, cb->args[IPSET_CB_ARG0]));
		pr_debug("cb->arg bucket: %lu, t %p n %p\n",
			 cb->args[IPSET_CB_ARG0], t, n);
		अगर (!n)
			जारी;
		क्रम (i = 0; i < n->pos; i++) अणु
			अगर (!test_bit(i, n->used))
				जारी;
			e = ahash_data(n, i, set->dsize);
			अगर (SET_ELEM_EXPIRED(set, e))
				जारी;
			pr_debug("list hash %lu hbucket %p i %u, data %p\n",
				 cb->args[IPSET_CB_ARG0], n, i, e);
			nested = nla_nest_start(skb, IPSET_ATTR_DATA);
			अगर (!nested) अणु
				अगर (cb->args[IPSET_CB_ARG0] == first) अणु
					nla_nest_cancel(skb, atd);
					ret = -EMSGSIZE;
					जाओ out;
				पूर्ण
				जाओ nla_put_failure;
			पूर्ण
			अगर (mtype_data_list(skb, e))
				जाओ nla_put_failure;
			अगर (ip_set_put_extensions(skb, set, e, true))
				जाओ nla_put_failure;
			nla_nest_end(skb, nested);
		पूर्ण
	पूर्ण
	nla_nest_end(skb, atd);
	/* Set listing finished */
	cb->args[IPSET_CB_ARG0] = 0;

	जाओ out;

nla_put_failure:
	nlmsg_trim(skb, incomplete);
	अगर (unlikely(first == cb->args[IPSET_CB_ARG0])) अणु
		pr_warn("Can't list set %s: one bucket does not fit into a message. Please report it!\n",
			set->name);
		cb->args[IPSET_CB_ARG0] = 0;
		ret = -EMSGSIZE;
	पूर्ण अन्यथा अणु
		nla_nest_end(skb, atd);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक
IPSET_TOKEN(MTYPE, _kadt)(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
			  स्थिर काष्ठा xt_action_param *par,
			  क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt);

अटल पूर्णांक
IPSET_TOKEN(MTYPE, _uadt)(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
			  क्रमागत ipset_adt adt, u32 *lineno, u32 flags,
			  bool retried);

अटल स्थिर काष्ठा ip_set_type_variant mtype_variant = अणु
	.kadt	= mtype_kadt,
	.uadt	= mtype_uadt,
	.adt	= अणु
		[IPSET_ADD] = mtype_add,
		[IPSET_DEL] = mtype_del,
		[IPSET_TEST] = mtype_test,
	पूर्ण,
	.destroy = mtype_destroy,
	.flush	= mtype_flush,
	.head	= mtype_head,
	.list	= mtype_list,
	.uref	= mtype_uref,
	.resize	= mtype_resize,
	.same_set = mtype_same_set,
	.region_lock = true,
पूर्ण;

#अगर_घोषित IP_SET_EMIT_CREATE
अटल पूर्णांक
IPSET_TOKEN(HTYPE, _create)(काष्ठा net *net, काष्ठा ip_set *set,
			    काष्ठा nlattr *tb[], u32 flags)
अणु
	u32 hashsize = IPSET_DEFAULT_HASHSIZE, maxelem = IPSET_DEFAULT_MAXELEM;
#अगर_घोषित IP_SET_HASH_WITH_MARKMASK
	u32 markmask;
#पूर्ण_अगर
	u8 hbits;
#अगर_घोषित IP_SET_HASH_WITH_NETMASK
	u8 neपंचांगask;
#पूर्ण_अगर
	माप_प्रकार hsize;
	काष्ठा htype *h;
	काष्ठा htable *t;
	u32 i;

	pr_debug("Create set %s with family %s\n",
		 set->name, set->family == NFPROTO_IPV4 ? "inet" : "inet6");

#अगर_घोषित IP_SET_PROTO_UNDEF
	अगर (set->family != NFPROTO_UNSPEC)
		वापस -IPSET_ERR_INVALID_FAMILY;
#अन्यथा
	अगर (!(set->family == NFPROTO_IPV4 || set->family == NFPROTO_IPV6))
		वापस -IPSET_ERR_INVALID_FAMILY;
#पूर्ण_अगर

	अगर (unlikely(!ip_set_optattr_netorder(tb, IPSET_ATTR_HASHSIZE) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_MAXELEM) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_TIMEOUT) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;

#अगर_घोषित IP_SET_HASH_WITH_MARKMASK
	/* Separated condition in order to aव्योम directive in argument list */
	अगर (unlikely(!ip_set_optattr_netorder(tb, IPSET_ATTR_MARKMASK)))
		वापस -IPSET_ERR_PROTOCOL;

	markmask = 0xffffffff;
	अगर (tb[IPSET_ATTR_MARKMASK]) अणु
		markmask = ntohl(nla_get_be32(tb[IPSET_ATTR_MARKMASK]));
		अगर (markmask == 0)
			वापस -IPSET_ERR_INVALID_MARKMASK;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित IP_SET_HASH_WITH_NETMASK
	neपंचांगask = set->family == NFPROTO_IPV4 ? 32 : 128;
	अगर (tb[IPSET_ATTR_NETMASK]) अणु
		neपंचांगask = nla_get_u8(tb[IPSET_ATTR_NETMASK]);

		अगर ((set->family == NFPROTO_IPV4 && neपंचांगask > 32) ||
		    (set->family == NFPROTO_IPV6 && neपंचांगask > 128) ||
		    neपंचांगask == 0)
			वापस -IPSET_ERR_INVALID_NETMASK;
	पूर्ण
#पूर्ण_अगर

	अगर (tb[IPSET_ATTR_HASHSIZE]) अणु
		hashsize = ip_set_get_h32(tb[IPSET_ATTR_HASHSIZE]);
		अगर (hashsize < IPSET_MIMINAL_HASHSIZE)
			hashsize = IPSET_MIMINAL_HASHSIZE;
	पूर्ण

	अगर (tb[IPSET_ATTR_MAXELEM])
		maxelem = ip_set_get_h32(tb[IPSET_ATTR_MAXELEM]);

	hsize = माप(*h);
	h = kzalloc(hsize, GFP_KERNEL);
	अगर (!h)
		वापस -ENOMEM;

	/* Compute htable_bits from the user input parameter hashsize.
	 * Assume that hashsize == 2^htable_bits,
	 * otherwise round up to the first 2^n value.
	 */
	hbits = fls(hashsize - 1);
	hsize = htable_size(hbits);
	अगर (hsize == 0) अणु
		kमुक्त(h);
		वापस -ENOMEM;
	पूर्ण
	t = ip_set_alloc(hsize);
	अगर (!t) अणु
		kमुक्त(h);
		वापस -ENOMEM;
	पूर्ण
	t->hregion = ip_set_alloc(ahash_माप_regions(hbits));
	अगर (!t->hregion) अणु
		ip_set_मुक्त(t);
		kमुक्त(h);
		वापस -ENOMEM;
	पूर्ण
	h->gc.set = set;
	क्रम (i = 0; i < ahash_numof_locks(hbits); i++)
		spin_lock_init(&t->hregion[i].lock);
	h->maxelem = maxelem;
#अगर_घोषित IP_SET_HASH_WITH_NETMASK
	h->neपंचांगask = neपंचांगask;
#पूर्ण_अगर
#अगर_घोषित IP_SET_HASH_WITH_MARKMASK
	h->markmask = markmask;
#पूर्ण_अगर
	अगर (tb[IPSET_ATTR_INITVAL])
		h->initval = ntohl(nla_get_be32(tb[IPSET_ATTR_INITVAL]));
	अन्यथा
		get_अक्रमom_bytes(&h->initval, माप(h->initval));
	h->bucketsize = AHASH_MAX_SIZE;
	अगर (tb[IPSET_ATTR_BUCKETSIZE]) अणु
		h->bucketsize = nla_get_u8(tb[IPSET_ATTR_BUCKETSIZE]);
		अगर (h->bucketsize < AHASH_INIT_SIZE)
			h->bucketsize = AHASH_INIT_SIZE;
		अन्यथा अगर (h->bucketsize > AHASH_MAX_SIZE)
			h->bucketsize = AHASH_MAX_SIZE;
		अन्यथा अगर (h->bucketsize % 2)
			h->bucketsize += 1;
	पूर्ण
	t->htable_bits = hbits;
	t->maxelem = h->maxelem / ahash_numof_locks(hbits);
	RCU_INIT_POINTER(h->table, t);

	INIT_LIST_HEAD(&h->ad);
	set->data = h;
#अगर_अघोषित IP_SET_PROTO_UNDEF
	अगर (set->family == NFPROTO_IPV4) अणु
#पूर्ण_अगर
		set->variant = &IPSET_TOKEN(HTYPE, 4_variant);
		set->dsize = ip_set_elem_len(set, tb,
			माप(काष्ठा IPSET_TOKEN(HTYPE, 4_elem)),
			__alignof__(काष्ठा IPSET_TOKEN(HTYPE, 4_elem)));
#अगर_अघोषित IP_SET_PROTO_UNDEF
	पूर्ण अन्यथा अणु
		set->variant = &IPSET_TOKEN(HTYPE, 6_variant);
		set->dsize = ip_set_elem_len(set, tb,
			माप(काष्ठा IPSET_TOKEN(HTYPE, 6_elem)),
			__alignof__(काष्ठा IPSET_TOKEN(HTYPE, 6_elem)));
	पूर्ण
#पूर्ण_अगर
	set->समयout = IPSET_NO_TIMEOUT;
	अगर (tb[IPSET_ATTR_TIMEOUT]) अणु
		set->समयout = ip_set_समयout_uget(tb[IPSET_ATTR_TIMEOUT]);
#अगर_अघोषित IP_SET_PROTO_UNDEF
		अगर (set->family == NFPROTO_IPV4)
#पूर्ण_अगर
			IPSET_TOKEN(HTYPE, 4_gc_init)(&h->gc);
#अगर_अघोषित IP_SET_PROTO_UNDEF
		अन्यथा
			IPSET_TOKEN(HTYPE, 6_gc_init)(&h->gc);
#पूर्ण_अगर
	पूर्ण
	pr_debug("create %s hashsize %u (%u) maxelem %u: %p(%p)\n",
		 set->name, jhash_size(t->htable_bits),
		 t->htable_bits, h->maxelem, set->data, t);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* IP_SET_EMIT_CREATE */

#अघोषित HKEY_DATALEN
