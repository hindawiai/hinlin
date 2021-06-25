<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* linux/net/inet/arp.h */
#अगर_अघोषित _ARP_H
#घोषणा _ARP_H

#समावेश <linux/अगर_arp.h>
#समावेश <linux/hash.h>
#समावेश <net/neighbour.h>


बाह्य काष्ठा neigh_table arp_tbl;

अटल अंतरभूत u32 arp_hashfn(स्थिर व्योम *pkey, स्थिर काष्ठा net_device *dev, u32 *hash_rnd)
अणु
	u32 key = *(स्थिर u32 *)pkey;
	u32 val = key ^ hash32_ptr(dev);

	वापस val * hash_rnd[0];
पूर्ण

#अगर_घोषित CONFIG_INET
अटल अंतरभूत काष्ठा neighbour *__ipv4_neigh_lookup_noref(काष्ठा net_device *dev, u32 key)
अणु
	अगर (dev->flags & (IFF_LOOPBACK | IFF_POINTOPOINT))
		key = INADDR_ANY;

	वापस ___neigh_lookup_noref(&arp_tbl, neigh_key_eq32, arp_hashfn, &key, dev);
पूर्ण
#अन्यथा
अटल अंतरभूत
काष्ठा neighbour *__ipv4_neigh_lookup_noref(काष्ठा net_device *dev, u32 key)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा neighbour *__ipv4_neigh_lookup(काष्ठा net_device *dev, u32 key)
अणु
	काष्ठा neighbour *n;

	rcu_पढ़ो_lock_bh();
	n = __ipv4_neigh_lookup_noref(dev, key);
	अगर (n && !refcount_inc_not_zero(&n->refcnt))
		n = शून्य;
	rcu_पढ़ो_unlock_bh();

	वापस n;
पूर्ण

अटल अंतरभूत व्योम __ipv4_confirm_neigh(काष्ठा net_device *dev, u32 key)
अणु
	काष्ठा neighbour *n;

	rcu_पढ़ो_lock_bh();
	n = __ipv4_neigh_lookup_noref(dev, key);
	अगर (n) अणु
		अचिन्हित दीर्घ now = jअगरfies;

		/* aव्योम dirtying neighbour */
		अगर (READ_ONCE(n->confirmed) != now)
			WRITE_ONCE(n->confirmed, now);
	पूर्ण
	rcu_पढ़ो_unlock_bh();
पूर्ण

व्योम arp_init(व्योम);
पूर्णांक arp_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
व्योम arp_send(पूर्णांक type, पूर्णांक ptype, __be32 dest_ip,
	      काष्ठा net_device *dev, __be32 src_ip,
	      स्थिर अचिन्हित अक्षर *dest_hw,
	      स्थिर अचिन्हित अक्षर *src_hw, स्थिर अचिन्हित अक्षर *th);
पूर्णांक arp_mc_map(__be32 addr, u8 *haddr, काष्ठा net_device *dev, पूर्णांक dir);
व्योम arp_अगरकरोwn(काष्ठा net_device *dev);

काष्ठा sk_buff *arp_create(पूर्णांक type, पूर्णांक ptype, __be32 dest_ip,
			   काष्ठा net_device *dev, __be32 src_ip,
			   स्थिर अचिन्हित अक्षर *dest_hw,
			   स्थिर अचिन्हित अक्षर *src_hw,
			   स्थिर अचिन्हित अक्षर *target_hw);
व्योम arp_xmit(काष्ठा sk_buff *skb);

#पूर्ण_अगर	/* _ARP_H */
