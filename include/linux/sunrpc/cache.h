<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/sunrpc/cache.h
 *
 * Generic code क्रम various authentication-related caches
 * used by sunrpc clients and servers.
 *
 * Copyright (C) 2002 Neil Brown <neilb@cse.unsw.edu.au>
 */

#अगर_अघोषित _LINUX_SUNRPC_CACHE_H_
#घोषणा _LINUX_SUNRPC_CACHE_H_

#समावेश <linux/kref.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/proc_fs.h>

/*
 * Each cache requires:
 *  - A 'struct cache_detail' which contains inक्रमmation specअगरic to the cache
 *    क्रम common code to use.
 *  - An item काष्ठाure that must contain a "struct cache_head"
 *  - A lookup function defined using DefineCacheLookup
 *  - A 'put' function that can release a cache item. It will only
 *    be called after cache_put has succeed, so there are guarantee
 *    to be no references.
 *  - A function to calculate a hash of an item's key.
 *
 * as well as assorted code fragments (e.g. compare keys) and numbers
 * (e.g. hash size, goal_age, etc).
 *
 * Each cache must be रेजिस्टरed so that it can be cleaned regularly.
 * When the cache is unरेजिस्टरed, it is flushed completely.
 *
 * Entries have a ref count and a 'hashed' flag which counts the existence
 * in the hash table.
 * We only expire entries when refcount is zero.
 * Existence in the cache is counted  the refcount.
 */

/* Every cache item has a common header that is used
 * क्रम expiring and refreshing entries.
 * 
 */
काष्ठा cache_head अणु
	काष्ठा hlist_node	cache_list;
	समय64_t	expiry_समय;	/* After समय expiry_समय, करोn't use
					 * the data */
	समय64_t	last_refresh;   /* If CACHE_PENDING, this is when upcall was
					 * sent, अन्यथा this is when update was
					 * received, though it is alway set to
					 * be *after* ->flush_समय.
					 */
	काष्ठा kref	ref;
	अचिन्हित दीर्घ	flags;
पूर्ण;
#घोषणा	CACHE_VALID	0	/* Entry contains valid data */
#घोषणा	CACHE_NEGATIVE	1	/* Negative entry - there is no match क्रम the key */
#घोषणा	CACHE_PENDING	2	/* An upcall has been sent but no reply received yet*/
#घोषणा	CACHE_CLEANED	3	/* Entry has been cleaned from cache */

#घोषणा	CACHE_NEW_EXPIRY 120	/* keep new things pending confirmation क्रम 120 seconds */

काष्ठा cache_detail अणु
	काष्ठा module *		owner;
	पूर्णांक			hash_size;
	काष्ठा hlist_head *	hash_table;
	spinlock_t		hash_lock;

	अक्षर			*name;
	व्योम			(*cache_put)(काष्ठा kref *);

	पूर्णांक			(*cache_upcall)(काष्ठा cache_detail *,
						काष्ठा cache_head *);

	व्योम			(*cache_request)(काष्ठा cache_detail *cd,
						 काष्ठा cache_head *ch,
						 अक्षर **bpp, पूर्णांक *blen);

	पूर्णांक			(*cache_parse)(काष्ठा cache_detail *,
					       अक्षर *buf, पूर्णांक len);

	पूर्णांक			(*cache_show)(काष्ठा seq_file *m,
					      काष्ठा cache_detail *cd,
					      काष्ठा cache_head *h);
	व्योम			(*warn_no_listener)(काष्ठा cache_detail *cd,
					      पूर्णांक has_died);

	काष्ठा cache_head *	(*alloc)(व्योम);
	व्योम			(*flush)(व्योम);
	पूर्णांक			(*match)(काष्ठा cache_head *orig, काष्ठा cache_head *new);
	व्योम			(*init)(काष्ठा cache_head *orig, काष्ठा cache_head *new);
	व्योम			(*update)(काष्ठा cache_head *orig, काष्ठा cache_head *new);

	/* fields below this comment are क्रम पूर्णांकernal use
	 * and should not be touched by cache owners
	 */
	समय64_t		flush_समय;		/* flush all cache items with
							 * last_refresh at or earlier
							 * than this.  last_refresh
							 * is never set at or earlier
							 * than this.
							 */
	काष्ठा list_head	others;
	समय64_t		nextcheck;
	पूर्णांक			entries;

	/* fields क्रम communication over channel */
	काष्ठा list_head	queue;

	atomic_t		ग_लिखोrs;		/* how many समय is /channel खोलो */
	समय64_t		last_बंद;		/* अगर no ग_लिखोrs, when did last बंद */
	समय64_t		last_warn;		/* when we last warned about no ग_लिखोrs */

	जोड़ अणु
		काष्ठा proc_dir_entry	*procfs;
		काष्ठा dentry		*pipefs;
	पूर्ण;
	काष्ठा net		*net;
पूर्ण;


/* this must be embedded in any request काष्ठाure that
 * identअगरies an object that will want a callback on
 * a cache fill
 */
काष्ठा cache_req अणु
	काष्ठा cache_deferred_req *(*defer)(काष्ठा cache_req *req);
	पूर्णांक thपढ़ो_रुको;  /* How दीर्घ (jअगरfies) we can block the
			   * current thपढ़ो to रुको क्रम updates.
			   */
पूर्ण;
/* this must be embedded in a deferred_request that is being
 * delayed aरुकोing cache-fill
 */
काष्ठा cache_deferred_req अणु
	काष्ठा hlist_node	hash;	/* on hash chain */
	काष्ठा list_head	recent; /* on fअगरo */
	काष्ठा cache_head	*item;  /* cache item we रुको on */
	व्योम			*owner; /* we might need to discard all defered requests
					 * owned by someone */
	व्योम			(*revisit)(काष्ठा cache_deferred_req *req,
					   पूर्णांक too_many);
पूर्ण;

/*
 * बारtamps kept in the cache are expressed in seconds
 * since boot.  This is the best क्रम measuring dअगरferences in
 * real समय.
 * This reimplemnts kसमय_get_bootसमय_seconds() in a slightly
 * faster but less accurate way. When we end up converting
 * back to wallघड़ी (CLOCK_REALTIME), that error often
 * cancels out during the reverse operation.
 */
अटल अंतरभूत समय64_t seconds_since_boot(व्योम)
अणु
	काष्ठा बारpec64 boot;
	getbootसमय64(&boot);
	वापस kसमय_get_real_seconds() - boot.tv_sec;
पूर्ण

अटल अंतरभूत समय64_t convert_to_wallघड़ी(समय64_t sinceboot)
अणु
	काष्ठा बारpec64 boot;
	getbootसमय64(&boot);
	वापस boot.tv_sec + sinceboot;
पूर्ण

बाह्य स्थिर काष्ठा file_operations cache_file_operations_pipefs;
बाह्य स्थिर काष्ठा file_operations content_file_operations_pipefs;
बाह्य स्थिर काष्ठा file_operations cache_flush_operations_pipefs;

बाह्य काष्ठा cache_head *
sunrpc_cache_lookup_rcu(काष्ठा cache_detail *detail,
			काष्ठा cache_head *key, पूर्णांक hash);
बाह्य काष्ठा cache_head *
sunrpc_cache_update(काष्ठा cache_detail *detail,
		    काष्ठा cache_head *new, काष्ठा cache_head *old, पूर्णांक hash);

बाह्य पूर्णांक
sunrpc_cache_pipe_upcall(काष्ठा cache_detail *detail, काष्ठा cache_head *h);
बाह्य पूर्णांक
sunrpc_cache_pipe_upcall_समयout(काष्ठा cache_detail *detail,
				 काष्ठा cache_head *h);


बाह्य व्योम cache_clean_deferred(व्योम *owner);

अटल अंतरभूत काष्ठा cache_head  *cache_get(काष्ठा cache_head *h)
अणु
	kref_get(&h->ref);
	वापस h;
पूर्ण

अटल अंतरभूत काष्ठा cache_head  *cache_get_rcu(काष्ठा cache_head *h)
अणु
	अगर (kref_get_unless_zero(&h->ref))
		वापस h;
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम cache_put(काष्ठा cache_head *h, काष्ठा cache_detail *cd)
अणु
	अगर (kref_पढ़ो(&h->ref) <= 2 &&
	    h->expiry_समय < cd->nextcheck)
		cd->nextcheck = h->expiry_समय;
	kref_put(&h->ref, cd->cache_put);
पूर्ण

अटल अंतरभूत bool cache_is_expired(काष्ठा cache_detail *detail, काष्ठा cache_head *h)
अणु
	अगर (h->expiry_समय < seconds_since_boot())
		वापस true;
	अगर (!test_bit(CACHE_VALID, &h->flags))
		वापस false;
	वापस detail->flush_समय >= h->last_refresh;
पूर्ण

बाह्य पूर्णांक cache_check(काष्ठा cache_detail *detail,
		       काष्ठा cache_head *h, काष्ठा cache_req *rqstp);
बाह्य व्योम cache_flush(व्योम);
बाह्य व्योम cache_purge(काष्ठा cache_detail *detail);
#घोषणा NEVER (0x7FFFFFFF)
बाह्य व्योम __init cache_initialize(व्योम);
बाह्य पूर्णांक cache_रेजिस्टर_net(काष्ठा cache_detail *cd, काष्ठा net *net);
बाह्य व्योम cache_unरेजिस्टर_net(काष्ठा cache_detail *cd, काष्ठा net *net);

बाह्य काष्ठा cache_detail *cache_create_net(स्थिर काष्ठा cache_detail *पंचांगpl, काष्ठा net *net);
बाह्य व्योम cache_destroy_net(काष्ठा cache_detail *cd, काष्ठा net *net);

बाह्य व्योम sunrpc_init_cache_detail(काष्ठा cache_detail *cd);
बाह्य व्योम sunrpc_destroy_cache_detail(काष्ठा cache_detail *cd);
बाह्य पूर्णांक sunrpc_cache_रेजिस्टर_pipefs(काष्ठा dentry *parent, स्थिर अक्षर *,
					umode_t, काष्ठा cache_detail *);
बाह्य व्योम sunrpc_cache_unरेजिस्टर_pipefs(काष्ठा cache_detail *);
बाह्य व्योम sunrpc_cache_unhash(काष्ठा cache_detail *, काष्ठा cache_head *);

/* Must store cache_detail in seq_file->निजी अगर using next three functions */
बाह्य व्योम *cache_seq_start_rcu(काष्ठा seq_file *file, loff_t *pos);
बाह्य व्योम *cache_seq_next_rcu(काष्ठा seq_file *file, व्योम *p, loff_t *pos);
बाह्य व्योम cache_seq_stop_rcu(काष्ठा seq_file *file, व्योम *p);

बाह्य व्योम qword_add(अक्षर **bpp, पूर्णांक *lp, अक्षर *str);
बाह्य व्योम qword_addhex(अक्षर **bpp, पूर्णांक *lp, अक्षर *buf, पूर्णांक blen);
बाह्य पूर्णांक qword_get(अक्षर **bpp, अक्षर *dest, पूर्णांक bufsize);

अटल अंतरभूत पूर्णांक get_पूर्णांक(अक्षर **bpp, पूर्णांक *anपूर्णांक)
अणु
	अक्षर buf[50];
	अक्षर *ep;
	पूर्णांक rv;
	पूर्णांक len = qword_get(bpp, buf, माप(buf));

	अगर (len < 0)
		वापस -EINVAL;
	अगर (len == 0)
		वापस -ENOENT;

	rv = simple_म_से_दीर्घ(buf, &ep, 0);
	अगर (*ep)
		वापस -EINVAL;

	*anपूर्णांक = rv;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_uपूर्णांक(अक्षर **bpp, अचिन्हित पूर्णांक *anपूर्णांक)
अणु
	अक्षर buf[50];
	पूर्णांक len = qword_get(bpp, buf, माप(buf));

	अगर (len < 0)
		वापस -EINVAL;
	अगर (len == 0)
		वापस -ENOENT;

	अगर (kstrtouपूर्णांक(buf, 0, anपूर्णांक))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_समय(अक्षर **bpp, समय64_t *समय)
अणु
	अक्षर buf[50];
	दीर्घ दीर्घ ll;
	पूर्णांक len = qword_get(bpp, buf, माप(buf));

	अगर (len < 0)
		वापस -EINVAL;
	अगर (len == 0)
		वापस -ENOENT;

	अगर (kम_से_दीर्घl(buf, 0, &ll))
		वापस -EINVAL;

	*समय = ll;
	वापस 0;
पूर्ण

अटल अंतरभूत समय64_t get_expiry(अक्षर **bpp)
अणु
	समय64_t rv;
	काष्ठा बारpec64 boot;

	अगर (get_समय(bpp, &rv))
		वापस 0;
	अगर (rv < 0)
		वापस 0;
	getbootसमय64(&boot);
	वापस rv - boot.tv_sec;
पूर्ण

#पूर्ण_अगर /*  _LINUX_SUNRPC_CACHE_H_ */
