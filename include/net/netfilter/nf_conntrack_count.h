<शैली गुरु>
#अगर_अघोषित _NF_CONNTRACK_COUNT_H
#घोषणा _NF_CONNTRACK_COUNT_H

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>

काष्ठा nf_conncount_data;

काष्ठा nf_conncount_list अणु
	spinlock_t list_lock;
	काष्ठा list_head head;	/* connections with the same filtering key */
	अचिन्हित पूर्णांक count;	/* length of list */
पूर्ण;

काष्ठा nf_conncount_data *nf_conncount_init(काष्ठा net *net, अचिन्हित पूर्णांक family,
					    अचिन्हित पूर्णांक keylen);
व्योम nf_conncount_destroy(काष्ठा net *net, अचिन्हित पूर्णांक family,
			  काष्ठा nf_conncount_data *data);

अचिन्हित पूर्णांक nf_conncount_count(काष्ठा net *net,
				काष्ठा nf_conncount_data *data,
				स्थिर u32 *key,
				स्थिर काष्ठा nf_conntrack_tuple *tuple,
				स्थिर काष्ठा nf_conntrack_zone *zone);

पूर्णांक nf_conncount_add(काष्ठा net *net, काष्ठा nf_conncount_list *list,
		     स्थिर काष्ठा nf_conntrack_tuple *tuple,
		     स्थिर काष्ठा nf_conntrack_zone *zone);

व्योम nf_conncount_list_init(काष्ठा nf_conncount_list *list);

bool nf_conncount_gc_list(काष्ठा net *net,
			  काष्ठा nf_conncount_list *list);

व्योम nf_conncount_cache_मुक्त(काष्ठा nf_conncount_list *list);

#पूर्ण_अगर
