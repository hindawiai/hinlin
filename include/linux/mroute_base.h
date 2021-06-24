<शैली गुरु>
#अगर_अघोषित __LINUX_MROUTE_BASE_H
#घोषणा __LINUX_MROUTE_BASE_H

#समावेश <linux/netdevice.h>
#समावेश <linux/rhashtable-types.h>
#समावेश <linux/spinlock.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <net/ip_fib.h>

/**
 * काष्ठा vअगर_device - पूर्णांकerface representor क्रम multicast routing
 * @dev: network device being used
 * @bytes_in: statistic; bytes ingressing
 * @bytes_out: statistic; bytes egresing
 * @pkt_in: statistic; packets ingressing
 * @pkt_out: statistic; packets egressing
 * @rate_limit: Traffic shaping (NI)
 * @threshold: TTL threshold
 * @flags: Control flags
 * @link: Physical पूर्णांकerface index
 * @dev_parent_id: device parent id
 * @local: Local address
 * @remote: Remote address क्रम tunnels
 */
काष्ठा vअगर_device अणु
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ bytes_in, bytes_out;
	अचिन्हित दीर्घ pkt_in, pkt_out;
	अचिन्हित दीर्घ rate_limit;
	अचिन्हित अक्षर threshold;
	अचिन्हित लघु flags;
	पूर्णांक link;

	/* Currently only used by ipmr */
	काष्ठा netdev_phys_item_id dev_parent_id;
	__be32 local, remote;
पूर्ण;

काष्ठा vअगर_entry_notअगरier_info अणु
	काष्ठा fib_notअगरier_info info;
	काष्ठा net_device *dev;
	अचिन्हित लघु vअगर_index;
	अचिन्हित लघु vअगर_flags;
	u32 tb_id;
पूर्ण;

अटल अंतरभूत पूर्णांक mr_call_vअगर_notअगरier(काष्ठा notअगरier_block *nb,
				       अचिन्हित लघु family,
				       क्रमागत fib_event_type event_type,
				       काष्ठा vअगर_device *vअगर,
				       अचिन्हित लघु vअगर_index, u32 tb_id,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vअगर_entry_notअगरier_info info = अणु
		.info = अणु
			.family = family,
			.extack = extack,
		पूर्ण,
		.dev = vअगर->dev,
		.vअगर_index = vअगर_index,
		.vअगर_flags = vअगर->flags,
		.tb_id = tb_id,
	पूर्ण;

	वापस call_fib_notअगरier(nb, event_type, &info.info);
पूर्ण

अटल अंतरभूत पूर्णांक mr_call_vअगर_notअगरiers(काष्ठा net *net,
					अचिन्हित लघु family,
					क्रमागत fib_event_type event_type,
					काष्ठा vअगर_device *vअगर,
					अचिन्हित लघु vअगर_index, u32 tb_id,
					अचिन्हित पूर्णांक *ipmr_seq)
अणु
	काष्ठा vअगर_entry_notअगरier_info info = अणु
		.info = अणु
			.family = family,
		पूर्ण,
		.dev = vअगर->dev,
		.vअगर_index = vअगर_index,
		.vअगर_flags = vअगर->flags,
		.tb_id = tb_id,
	पूर्ण;

	ASSERT_RTNL();
	(*ipmr_seq)++;
	वापस call_fib_notअगरiers(net, event_type, &info.info);
पूर्ण

#अगर_अघोषित MAXVIFS
/* This one is nasty; value is defined in uapi using dअगरferent symbols क्रम
 * mroute and morute6 but both map पूर्णांकo same 32.
 */
#घोषणा MAXVIFS	32
#पूर्ण_अगर

#घोषणा VIF_EXISTS(_mrt, _idx) (!!((_mrt)->vअगर_table[_idx].dev))

/* mfc_flags:
 * MFC_STATIC - the entry was added अटलally (not by a routing daemon)
 * MFC_OFFLOAD - the entry was offloaded to the hardware
 */
क्रमागत अणु
	MFC_STATIC = BIT(0),
	MFC_OFFLOAD = BIT(1),
पूर्ण;

/**
 * काष्ठा mr_mfc - common multicast routing entries
 * @mnode: rhashtable list
 * @mfc_parent: source पूर्णांकerface (iअगर)
 * @mfc_flags: entry flags
 * @expires: unresolved entry expire समय
 * @unresolved: unresolved cached skbs
 * @last_निश्चित: समय of last निश्चित
 * @minvअगर: minimum VIF id
 * @maxvअगर: maximum VIF id
 * @bytes: bytes that have passed क्रम this entry
 * @pkt: packets that have passed क्रम this entry
 * @wrong_अगर: number of wrong source पूर्णांकerface hits
 * @lastuse: समय of last use of the group (traffic or update)
 * @ttls: OIF TTL threshold array
 * @refcount: reference count क्रम this entry
 * @list: global entry list
 * @rcu: used क्रम entry deकाष्ठाion
 * @मुक्त: Operation used क्रम मुक्तing an entry under RCU
 */
काष्ठा mr_mfc अणु
	काष्ठा rhlist_head mnode;
	अचिन्हित लघु mfc_parent;
	पूर्णांक mfc_flags;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ expires;
			काष्ठा sk_buff_head unresolved;
		पूर्ण unres;
		काष्ठा अणु
			अचिन्हित दीर्घ last_निश्चित;
			पूर्णांक minvअगर;
			पूर्णांक maxvअगर;
			अचिन्हित दीर्घ bytes;
			अचिन्हित दीर्घ pkt;
			अचिन्हित दीर्घ wrong_अगर;
			अचिन्हित दीर्घ lastuse;
			अचिन्हित अक्षर ttls[MAXVIFS];
			refcount_t refcount;
		पूर्ण res;
	पूर्ण mfc_un;
	काष्ठा list_head list;
	काष्ठा rcu_head	rcu;
	व्योम (*मुक्त)(काष्ठा rcu_head *head);
पूर्ण;

अटल अंतरभूत व्योम mr_cache_put(काष्ठा mr_mfc *c)
अणु
	अगर (refcount_dec_and_test(&c->mfc_un.res.refcount))
		call_rcu(&c->rcu, c->मुक्त);
पूर्ण

अटल अंतरभूत व्योम mr_cache_hold(काष्ठा mr_mfc *c)
अणु
	refcount_inc(&c->mfc_un.res.refcount);
पूर्ण

काष्ठा mfc_entry_notअगरier_info अणु
	काष्ठा fib_notअगरier_info info;
	काष्ठा mr_mfc *mfc;
	u32 tb_id;
पूर्ण;

अटल अंतरभूत पूर्णांक mr_call_mfc_notअगरier(काष्ठा notअगरier_block *nb,
				       अचिन्हित लघु family,
				       क्रमागत fib_event_type event_type,
				       काष्ठा mr_mfc *mfc, u32 tb_id,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mfc_entry_notअगरier_info info = अणु
		.info = अणु
			.family = family,
			.extack = extack,
		पूर्ण,
		.mfc = mfc,
		.tb_id = tb_id
	पूर्ण;

	वापस call_fib_notअगरier(nb, event_type, &info.info);
पूर्ण

अटल अंतरभूत पूर्णांक mr_call_mfc_notअगरiers(काष्ठा net *net,
					अचिन्हित लघु family,
					क्रमागत fib_event_type event_type,
					काष्ठा mr_mfc *mfc, u32 tb_id,
					अचिन्हित पूर्णांक *ipmr_seq)
अणु
	काष्ठा mfc_entry_notअगरier_info info = अणु
		.info = अणु
			.family = family,
		पूर्ण,
		.mfc = mfc,
		.tb_id = tb_id
	पूर्ण;

	ASSERT_RTNL();
	(*ipmr_seq)++;
	वापस call_fib_notअगरiers(net, event_type, &info.info);
पूर्ण

काष्ठा mr_table;

/**
 * काष्ठा mr_table_ops - callbacks and info क्रम protocol-specअगरic ops
 * @rht_params: parameters क्रम accessing the MFC hash
 * @cmparg_any: a hash key to be used क्रम matching on (*,*) routes
 */
काष्ठा mr_table_ops अणु
	स्थिर काष्ठा rhashtable_params *rht_params;
	व्योम *cmparg_any;
पूर्ण;

/**
 * काष्ठा mr_table - a multicast routing table
 * @list: entry within a list of multicast routing tables
 * @net: net where this table beदीर्घs
 * @ops: protocol specअगरic operations
 * @id: identअगरier of the table
 * @mroute_sk: socket associated with the table
 * @ipmr_expire_समयr: समयr क्रम handling unresolved routes
 * @mfc_unres_queue: list of unresolved MFC entries
 * @vअगर_table: array containing all possible vअगरs
 * @mfc_hash: Hash table of all resolved routes क्रम easy lookup
 * @mfc_cache_list: list of resovled routes क्रम possible traversal
 * @maxvअगर: Identअगरier of highest value vअगर currently in use
 * @cache_resolve_queue_len: current size of unresolved queue
 * @mroute_करो_निश्चित: Whether to inक्रमm userspace on wrong ingress
 * @mroute_करो_pim: Whether to receive IGMP PIMv1
 * @mroute_reg_vअगर_num: PIM-device vअगर index
 */
काष्ठा mr_table अणु
	काष्ठा list_head	list;
	possible_net_t		net;
	काष्ठा mr_table_ops	ops;
	u32			id;
	काष्ठा sock __rcu	*mroute_sk;
	काष्ठा समयr_list	ipmr_expire_समयr;
	काष्ठा list_head	mfc_unres_queue;
	काष्ठा vअगर_device	vअगर_table[MAXVIFS];
	काष्ठा rhltable		mfc_hash;
	काष्ठा list_head	mfc_cache_list;
	पूर्णांक			maxvअगर;
	atomic_t		cache_resolve_queue_len;
	bool			mroute_करो_निश्चित;
	bool			mroute_करो_pim;
	bool			mroute_करो_wrvअगरwhole;
	पूर्णांक			mroute_reg_vअगर_num;
पूर्ण;

#अगर_घोषित CONFIG_IP_MROUTE_COMMON
व्योम vअगर_device_init(काष्ठा vअगर_device *v,
		     काष्ठा net_device *dev,
		     अचिन्हित दीर्घ rate_limit,
		     अचिन्हित अक्षर threshold,
		     अचिन्हित लघु flags,
		     अचिन्हित लघु get_अगरlink_mask);

काष्ठा mr_table *
mr_table_alloc(काष्ठा net *net, u32 id,
	       काष्ठा mr_table_ops *ops,
	       व्योम (*expire_func)(काष्ठा समयr_list *t),
	       व्योम (*table_set)(काष्ठा mr_table *mrt,
				 काष्ठा net *net));

/* These actually वापस 'struct mr_mfc *', but to aव्योम need क्रम explicit
 * castings they simply वापस व्योम.
 */
व्योम *mr_mfc_find_parent(काष्ठा mr_table *mrt,
			 व्योम *hasharg, पूर्णांक parent);
व्योम *mr_mfc_find_any_parent(काष्ठा mr_table *mrt, पूर्णांक vअगरi);
व्योम *mr_mfc_find_any(काष्ठा mr_table *mrt, पूर्णांक vअगरi, व्योम *hasharg);

पूर्णांक mr_fill_mroute(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
		   काष्ठा mr_mfc *c, काष्ठा rपंचांगsg *rपंचांग);
पूर्णांक mr_table_dump(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
		  काष्ठा netlink_callback *cb,
		  पूर्णांक (*fill)(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
			      u32 portid, u32 seq, काष्ठा mr_mfc *c,
			      पूर्णांक cmd, पूर्णांक flags),
		  spinlock_t *lock, काष्ठा fib_dump_filter *filter);
पूर्णांक mr_rपंचांग_dumproute(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		     काष्ठा mr_table *(*iter)(काष्ठा net *net,
					      काष्ठा mr_table *mrt),
		     पूर्णांक (*fill)(काष्ठा mr_table *mrt,
				 काष्ठा sk_buff *skb,
				 u32 portid, u32 seq, काष्ठा mr_mfc *c,
				 पूर्णांक cmd, पूर्णांक flags),
		     spinlock_t *lock, काष्ठा fib_dump_filter *filter);

पूर्णांक mr_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb, अचिन्हित लघु family,
	    पूर्णांक (*rules_dump)(काष्ठा net *net,
			      काष्ठा notअगरier_block *nb,
			      काष्ठा netlink_ext_ack *extack),
	    काष्ठा mr_table *(*mr_iter)(काष्ठा net *net,
					काष्ठा mr_table *mrt),
	    rwlock_t *mrt_lock, काष्ठा netlink_ext_ack *extack);
#अन्यथा
अटल अंतरभूत व्योम vअगर_device_init(काष्ठा vअगर_device *v,
				   काष्ठा net_device *dev,
				   अचिन्हित दीर्घ rate_limit,
				   अचिन्हित अक्षर threshold,
				   अचिन्हित लघु flags,
				   अचिन्हित लघु get_अगरlink_mask)
अणु
पूर्ण

अटल अंतरभूत व्योम *mr_mfc_find_parent(काष्ठा mr_table *mrt,
				       व्योम *hasharg, पूर्णांक parent)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *mr_mfc_find_any_parent(काष्ठा mr_table *mrt,
					   पूर्णांक vअगरi)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mr_mfc *mr_mfc_find_any(काष्ठा mr_table *mrt,
					     पूर्णांक vअगरi, व्योम *hasharg)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक mr_fill_mroute(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
				 काष्ठा mr_mfc *c, काष्ठा rपंचांगsg *rपंचांग)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
mr_rपंचांग_dumproute(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		 काष्ठा mr_table *(*iter)(काष्ठा net *net,
					  काष्ठा mr_table *mrt),
		 पूर्णांक (*fill)(काष्ठा mr_table *mrt,
			     काष्ठा sk_buff *skb,
			     u32 portid, u32 seq, काष्ठा mr_mfc *c,
			     पूर्णांक cmd, पूर्णांक flags),
		 spinlock_t *lock, काष्ठा fib_dump_filter *filter)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक mr_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			  अचिन्हित लघु family,
			  पूर्णांक (*rules_dump)(काष्ठा net *net,
					    काष्ठा notअगरier_block *nb,
					    काष्ठा netlink_ext_ack *extack),
			  काष्ठा mr_table *(*mr_iter)(काष्ठा net *net,
						      काष्ठा mr_table *mrt),
			  rwlock_t *mrt_lock, काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम *mr_mfc_find(काष्ठा mr_table *mrt, व्योम *hasharg)
अणु
	वापस mr_mfc_find_parent(mrt, hasharg, -1);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
काष्ठा mr_vअगर_iter अणु
	काष्ठा seq_net_निजी p;
	काष्ठा mr_table *mrt;
	पूर्णांक ct;
पूर्ण;

काष्ठा mr_mfc_iter अणु
	काष्ठा seq_net_निजी p;
	काष्ठा mr_table *mrt;
	काष्ठा list_head *cache;

	/* Lock protecting the mr_table's unresolved queue */
	spinlock_t *lock;
पूर्ण;

#अगर_घोषित CONFIG_IP_MROUTE_COMMON
व्योम *mr_vअगर_seq_idx(काष्ठा net *net, काष्ठा mr_vअगर_iter *iter, loff_t pos);
व्योम *mr_vअगर_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos);

अटल अंतरभूत व्योम *mr_vअगर_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos ? mr_vअगर_seq_idx(seq_file_net(seq),
				     seq->निजी, *pos - 1)
		    : SEQ_START_TOKEN;
पूर्ण

/* These actually वापस 'struct mr_mfc *', but to aव्योम need क्रम explicit
 * castings they simply वापस व्योम.
 */
व्योम *mr_mfc_seq_idx(काष्ठा net *net,
		     काष्ठा mr_mfc_iter *it, loff_t pos);
व्योम *mr_mfc_seq_next(काष्ठा seq_file *seq, व्योम *v,
		      loff_t *pos);

अटल अंतरभूत व्योम *mr_mfc_seq_start(काष्ठा seq_file *seq, loff_t *pos,
				     काष्ठा mr_table *mrt, spinlock_t *lock)
अणु
	काष्ठा mr_mfc_iter *it = seq->निजी;

	it->mrt = mrt;
	it->cache = शून्य;
	it->lock = lock;

	वापस *pos ? mr_mfc_seq_idx(seq_file_net(seq),
				     seq->निजी, *pos - 1)
		    : SEQ_START_TOKEN;
पूर्ण

अटल अंतरभूत व्योम mr_mfc_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा mr_mfc_iter *it = seq->निजी;
	काष्ठा mr_table *mrt = it->mrt;

	अगर (it->cache == &mrt->mfc_unres_queue)
		spin_unlock_bh(it->lock);
	अन्यथा अगर (it->cache == &mrt->mfc_cache_list)
		rcu_पढ़ो_unlock();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम *mr_vअगर_seq_idx(काष्ठा net *net, काष्ठा mr_vअगर_iter *iter,
				   loff_t pos)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *mr_vअगर_seq_next(काष्ठा seq_file *seq,
				    व्योम *v, loff_t *pos)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *mr_vअगर_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *mr_mfc_seq_idx(काष्ठा net *net,
				   काष्ठा mr_mfc_iter *it, loff_t pos)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *mr_mfc_seq_next(काष्ठा seq_file *seq, व्योम *v,
				    loff_t *pos)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *mr_mfc_seq_start(काष्ठा seq_file *seq, loff_t *pos,
				     काष्ठा mr_table *mrt, spinlock_t *lock)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mr_mfc_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
