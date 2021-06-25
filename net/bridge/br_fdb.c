<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Forwarding database
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/rculist.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/बार.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/चयनdev.h>
#समावेश <trace/events/bridge.h>
#समावेश "br_private.h"

अटल स्थिर काष्ठा rhashtable_params br_fdb_rht_params = अणु
	.head_offset = दुरत्व(काष्ठा net_bridge_fdb_entry, rhnode),
	.key_offset = दुरत्व(काष्ठा net_bridge_fdb_entry, key),
	.key_len = माप(काष्ठा net_bridge_fdb_key),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल काष्ठा kmem_cache *br_fdb_cache __पढ़ो_mostly;
अटल पूर्णांक fdb_insert(काष्ठा net_bridge *br, काष्ठा net_bridge_port *source,
		      स्थिर अचिन्हित अक्षर *addr, u16 vid);
अटल व्योम fdb_notअगरy(काष्ठा net_bridge *br,
		       स्थिर काष्ठा net_bridge_fdb_entry *, पूर्णांक, bool);

पूर्णांक __init br_fdb_init(व्योम)
अणु
	br_fdb_cache = kmem_cache_create("bridge_fdb_cache",
					 माप(काष्ठा net_bridge_fdb_entry),
					 0,
					 SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!br_fdb_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम br_fdb_fini(व्योम)
अणु
	kmem_cache_destroy(br_fdb_cache);
पूर्ण

पूर्णांक br_fdb_hash_init(काष्ठा net_bridge *br)
अणु
	वापस rhashtable_init(&br->fdb_hash_tbl, &br_fdb_rht_params);
पूर्ण

व्योम br_fdb_hash_fini(काष्ठा net_bridge *br)
अणु
	rhashtable_destroy(&br->fdb_hash_tbl);
पूर्ण

/* अगर topology_changing then use क्रमward_delay (शेष 15 sec)
 * otherwise keep दीर्घer (शेष 5 minutes)
 */
अटल अंतरभूत अचिन्हित दीर्घ hold_समय(स्थिर काष्ठा net_bridge *br)
अणु
	वापस br->topology_change ? br->क्रमward_delay : br->ageing_समय;
पूर्ण

अटल अंतरभूत पूर्णांक has_expired(स्थिर काष्ठा net_bridge *br,
				  स्थिर काष्ठा net_bridge_fdb_entry *fdb)
अणु
	वापस !test_bit(BR_FDB_STATIC, &fdb->flags) &&
	       !test_bit(BR_FDB_ADDED_BY_EXT_LEARN, &fdb->flags) &&
	       समय_beक्रमe_eq(fdb->updated + hold_समय(br), jअगरfies);
पूर्ण

अटल व्योम fdb_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा net_bridge_fdb_entry *ent
		= container_of(head, काष्ठा net_bridge_fdb_entry, rcu);
	kmem_cache_मुक्त(br_fdb_cache, ent);
पूर्ण

अटल काष्ठा net_bridge_fdb_entry *fdb_find_rcu(काष्ठा rhashtable *tbl,
						 स्थिर अचिन्हित अक्षर *addr,
						 __u16 vid)
अणु
	काष्ठा net_bridge_fdb_key key;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	key.vlan_id = vid;
	स_नकल(key.addr.addr, addr, माप(key.addr.addr));

	वापस rhashtable_lookup(tbl, &key, br_fdb_rht_params);
पूर्ण

/* requires bridge hash_lock */
अटल काष्ठा net_bridge_fdb_entry *br_fdb_find(काष्ठा net_bridge *br,
						स्थिर अचिन्हित अक्षर *addr,
						__u16 vid)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;

	lockdep_निश्चित_held_once(&br->hash_lock);

	rcu_पढ़ो_lock();
	fdb = fdb_find_rcu(&br->fdb_hash_tbl, addr, vid);
	rcu_पढ़ो_unlock();

	वापस fdb;
पूर्ण

काष्ठा net_device *br_fdb_find_port(स्थिर काष्ठा net_device *br_dev,
				    स्थिर अचिन्हित अक्षर *addr,
				    __u16 vid)
अणु
	काष्ठा net_bridge_fdb_entry *f;
	काष्ठा net_device *dev = शून्य;
	काष्ठा net_bridge *br;

	ASSERT_RTNL();

	अगर (!netअगर_is_bridge_master(br_dev))
		वापस शून्य;

	br = netdev_priv(br_dev);
	rcu_पढ़ो_lock();
	f = br_fdb_find_rcu(br, addr, vid);
	अगर (f && f->dst)
		dev = f->dst->dev;
	rcu_पढ़ो_unlock();

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(br_fdb_find_port);

काष्ठा net_bridge_fdb_entry *br_fdb_find_rcu(काष्ठा net_bridge *br,
					     स्थिर अचिन्हित अक्षर *addr,
					     __u16 vid)
अणु
	वापस fdb_find_rcu(&br->fdb_hash_tbl, addr, vid);
पूर्ण

/* When a अटल FDB entry is added, the mac address from the entry is
 * added to the bridge निजी HW address list and all required ports
 * are then updated with the new inक्रमmation.
 * Called under RTNL.
 */
अटल व्योम fdb_add_hw_addr(काष्ठा net_bridge *br, स्थिर अचिन्हित अक्षर *addr)
अणु
	पूर्णांक err;
	काष्ठा net_bridge_port *p;

	ASSERT_RTNL();

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (!br_promisc_port(p)) अणु
			err = dev_uc_add(p->dev, addr);
			अगर (err)
				जाओ unकरो;
		पूर्ण
	पूर्ण

	वापस;
unकरो:
	list_क्रम_each_entry_जारी_reverse(p, &br->port_list, list) अणु
		अगर (!br_promisc_port(p))
			dev_uc_del(p->dev, addr);
	पूर्ण
पूर्ण

/* When a अटल FDB entry is deleted, the HW address from that entry is
 * also हटाओd from the bridge निजी HW address list and updates all
 * the ports with needed inक्रमmation.
 * Called under RTNL.
 */
अटल व्योम fdb_del_hw_addr(काष्ठा net_bridge *br, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा net_bridge_port *p;

	ASSERT_RTNL();

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (!br_promisc_port(p))
			dev_uc_del(p->dev, addr);
	पूर्ण
पूर्ण

अटल व्योम fdb_delete(काष्ठा net_bridge *br, काष्ठा net_bridge_fdb_entry *f,
		       bool swdev_notअगरy)
अणु
	trace_fdb_delete(br, f);

	अगर (test_bit(BR_FDB_STATIC, &f->flags))
		fdb_del_hw_addr(br, f->key.addr.addr);

	hlist_del_init_rcu(&f->fdb_node);
	rhashtable_हटाओ_fast(&br->fdb_hash_tbl, &f->rhnode,
			       br_fdb_rht_params);
	fdb_notअगरy(br, f, RTM_DELNEIGH, swdev_notअगरy);
	call_rcu(&f->rcu, fdb_rcu_मुक्त);
पूर्ण

/* Delete a local entry अगर no other port had the same address. */
अटल व्योम fdb_delete_local(काष्ठा net_bridge *br,
			     स्थिर काष्ठा net_bridge_port *p,
			     काष्ठा net_bridge_fdb_entry *f)
अणु
	स्थिर अचिन्हित अक्षर *addr = f->key.addr.addr;
	काष्ठा net_bridge_vlan_group *vg;
	स्थिर काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge_port *op;
	u16 vid = f->key.vlan_id;

	/* Maybe another port has same hw addr? */
	list_क्रम_each_entry(op, &br->port_list, list) अणु
		vg = nbp_vlan_group(op);
		अगर (op != p && ether_addr_equal(op->dev->dev_addr, addr) &&
		    (!vid || br_vlan_find(vg, vid))) अणु
			f->dst = op;
			clear_bit(BR_FDB_ADDED_BY_USER, &f->flags);
			वापस;
		पूर्ण
	पूर्ण

	vg = br_vlan_group(br);
	v = br_vlan_find(vg, vid);
	/* Maybe bridge device has same hw addr? */
	अगर (p && ether_addr_equal(br->dev->dev_addr, addr) &&
	    (!vid || (v && br_vlan_should_use(v)))) अणु
		f->dst = शून्य;
		clear_bit(BR_FDB_ADDED_BY_USER, &f->flags);
		वापस;
	पूर्ण

	fdb_delete(br, f, true);
पूर्ण

व्योम br_fdb_find_delete_local(काष्ठा net_bridge *br,
			      स्थिर काष्ठा net_bridge_port *p,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा net_bridge_fdb_entry *f;

	spin_lock_bh(&br->hash_lock);
	f = br_fdb_find(br, addr, vid);
	अगर (f && test_bit(BR_FDB_LOCAL, &f->flags) &&
	    !test_bit(BR_FDB_ADDED_BY_USER, &f->flags) && f->dst == p)
		fdb_delete_local(br, p, f);
	spin_unlock_bh(&br->hash_lock);
पूर्ण

व्योम br_fdb_changeaddr(काष्ठा net_bridge_port *p, स्थिर अचिन्हित अक्षर *newaddr)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_fdb_entry *f;
	काष्ठा net_bridge *br = p->br;
	काष्ठा net_bridge_vlan *v;

	spin_lock_bh(&br->hash_lock);
	vg = nbp_vlan_group(p);
	hlist_क्रम_each_entry(f, &br->fdb_list, fdb_node) अणु
		अगर (f->dst == p && test_bit(BR_FDB_LOCAL, &f->flags) &&
		    !test_bit(BR_FDB_ADDED_BY_USER, &f->flags)) अणु
			/* delete old one */
			fdb_delete_local(br, p, f);

			/* अगर this port has no vlan inक्रमmation
			 * configured, we can safely be करोne at
			 * this poपूर्णांक.
			 */
			अगर (!vg || !vg->num_vlans)
				जाओ insert;
		पूर्ण
	पूर्ण

insert:
	/* insert new address,  may fail अगर invalid address or dup. */
	fdb_insert(br, p, newaddr, 0);

	अगर (!vg || !vg->num_vlans)
		जाओ करोne;

	/* Now add entries क्रम every VLAN configured on the port.
	 * This function runs under RTNL so the biपंचांगap will not change
	 * from under us.
	 */
	list_क्रम_each_entry(v, &vg->vlan_list, vlist)
		fdb_insert(br, p, newaddr, v->vid);

करोne:
	spin_unlock_bh(&br->hash_lock);
पूर्ण

व्योम br_fdb_change_mac_address(काष्ठा net_bridge *br, स्थिर u8 *newaddr)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_fdb_entry *f;
	काष्ठा net_bridge_vlan *v;

	spin_lock_bh(&br->hash_lock);

	/* If old entry was unassociated with any port, then delete it. */
	f = br_fdb_find(br, br->dev->dev_addr, 0);
	अगर (f && test_bit(BR_FDB_LOCAL, &f->flags) &&
	    !f->dst && !test_bit(BR_FDB_ADDED_BY_USER, &f->flags))
		fdb_delete_local(br, शून्य, f);

	fdb_insert(br, शून्य, newaddr, 0);
	vg = br_vlan_group(br);
	अगर (!vg || !vg->num_vlans)
		जाओ out;
	/* Now हटाओ and add entries क्रम every VLAN configured on the
	 * bridge.  This function runs under RTNL so the biपंचांगap will not
	 * change from under us.
	 */
	list_क्रम_each_entry(v, &vg->vlan_list, vlist) अणु
		अगर (!br_vlan_should_use(v))
			जारी;
		f = br_fdb_find(br, br->dev->dev_addr, v->vid);
		अगर (f && test_bit(BR_FDB_LOCAL, &f->flags) &&
		    !f->dst && !test_bit(BR_FDB_ADDED_BY_USER, &f->flags))
			fdb_delete_local(br, शून्य, f);
		fdb_insert(br, शून्य, newaddr, v->vid);
	पूर्ण
out:
	spin_unlock_bh(&br->hash_lock);
पूर्ण

व्योम br_fdb_cleanup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net_bridge *br = container_of(work, काष्ठा net_bridge,
					     gc_work.work);
	काष्ठा net_bridge_fdb_entry *f = शून्य;
	अचिन्हित दीर्घ delay = hold_समय(br);
	अचिन्हित दीर्घ work_delay = delay;
	अचिन्हित दीर्घ now = jअगरfies;

	/* this part is tricky, in order to aव्योम blocking learning and
	 * consequently क्रमwarding, we rely on rcu to delete objects with
	 * delayed मुक्तing allowing us to जारी traversing
	 */
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(f, &br->fdb_list, fdb_node) अणु
		अचिन्हित दीर्घ this_समयr = f->updated + delay;

		अगर (test_bit(BR_FDB_STATIC, &f->flags) ||
		    test_bit(BR_FDB_ADDED_BY_EXT_LEARN, &f->flags)) अणु
			अगर (test_bit(BR_FDB_NOTIFY, &f->flags)) अणु
				अगर (समय_after(this_समयr, now))
					work_delay = min(work_delay,
							 this_समयr - now);
				अन्यथा अगर (!test_and_set_bit(BR_FDB_NOTIFY_INACTIVE,
							   &f->flags))
					fdb_notअगरy(br, f, RTM_NEWNEIGH, false);
			पूर्ण
			जारी;
		पूर्ण

		अगर (समय_after(this_समयr, now)) अणु
			work_delay = min(work_delay, this_समयr - now);
		पूर्ण अन्यथा अणु
			spin_lock_bh(&br->hash_lock);
			अगर (!hlist_unhashed(&f->fdb_node))
				fdb_delete(br, f, true);
			spin_unlock_bh(&br->hash_lock);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Cleanup minimum 10 milliseconds apart */
	work_delay = max_t(अचिन्हित दीर्घ, work_delay, msecs_to_jअगरfies(10));
	mod_delayed_work(प्रणाली_दीर्घ_wq, &br->gc_work, work_delay);
पूर्ण

/* Completely flush all dynamic entries in क्रमwarding database.*/
व्योम br_fdb_flush(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_fdb_entry *f;
	काष्ठा hlist_node *पंचांगp;

	spin_lock_bh(&br->hash_lock);
	hlist_क्रम_each_entry_safe(f, पंचांगp, &br->fdb_list, fdb_node) अणु
		अगर (!test_bit(BR_FDB_STATIC, &f->flags))
			fdb_delete(br, f, true);
	पूर्ण
	spin_unlock_bh(&br->hash_lock);
पूर्ण

/* Flush all entries referring to a specअगरic port.
 * अगर करो_all is set also flush अटल entries
 * अगर vid is set delete all entries that match the vlan_id
 */
व्योम br_fdb_delete_by_port(काष्ठा net_bridge *br,
			   स्थिर काष्ठा net_bridge_port *p,
			   u16 vid,
			   पूर्णांक करो_all)
अणु
	काष्ठा net_bridge_fdb_entry *f;
	काष्ठा hlist_node *पंचांगp;

	spin_lock_bh(&br->hash_lock);
	hlist_क्रम_each_entry_safe(f, पंचांगp, &br->fdb_list, fdb_node) अणु
		अगर (f->dst != p)
			जारी;

		अगर (!करो_all)
			अगर (test_bit(BR_FDB_STATIC, &f->flags) ||
			    (test_bit(BR_FDB_ADDED_BY_EXT_LEARN, &f->flags) &&
			     !test_bit(BR_FDB_OFFLOADED, &f->flags)) ||
			    (vid && f->key.vlan_id != vid))
				जारी;

		अगर (test_bit(BR_FDB_LOCAL, &f->flags))
			fdb_delete_local(br, p, f);
		अन्यथा
			fdb_delete(br, f, true);
	पूर्ण
	spin_unlock_bh(&br->hash_lock);
पूर्ण

#अगर IS_ENABLED(CONFIG_ATM_LANE)
/* Interface used by ATM LANE hook to test
 * अगर an addr is on some other bridge port */
पूर्णांक br_fdb_test_addr(काष्ठा net_device *dev, अचिन्हित अक्षर *addr)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;
	काष्ठा net_bridge_port *port;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	port = br_port_get_rcu(dev);
	अगर (!port)
		ret = 0;
	अन्यथा अणु
		fdb = br_fdb_find_rcu(port->br, addr, 0);
		ret = fdb && fdb->dst && fdb->dst->dev != dev &&
			fdb->dst->state == BR_STATE_FORWARDING;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATM_LANE */

/*
 * Fill buffer with क्रमwarding table records in
 * the API क्रमmat.
 */
पूर्णांक br_fdb_fillbuf(काष्ठा net_bridge *br, व्योम *buf,
		   अचिन्हित दीर्घ maxnum, अचिन्हित दीर्घ skip)
अणु
	काष्ठा net_bridge_fdb_entry *f;
	काष्ठा __fdb_entry *fe = buf;
	पूर्णांक num = 0;

	स_रखो(buf, 0, maxnum*माप(काष्ठा __fdb_entry));

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(f, &br->fdb_list, fdb_node) अणु
		अगर (num >= maxnum)
			अवरोध;

		अगर (has_expired(br, f))
			जारी;

		/* ignore pseuकरो entry क्रम local MAC address */
		अगर (!f->dst)
			जारी;

		अगर (skip) अणु
			--skip;
			जारी;
		पूर्ण

		/* convert from पूर्णांकernal क्रमmat to API */
		स_नकल(fe->mac_addr, f->key.addr.addr, ETH_ALEN);

		/* due to ABI compat need to split पूर्णांकo hi/lo */
		fe->port_no = f->dst->port_no;
		fe->port_hi = f->dst->port_no >> 8;

		fe->is_local = test_bit(BR_FDB_LOCAL, &f->flags);
		अगर (!test_bit(BR_FDB_STATIC, &f->flags))
			fe->ageing_समयr_value = jअगरfies_delta_to_घड़ी_प्रकार(jअगरfies - f->updated);
		++fe;
		++num;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस num;
पूर्ण

अटल काष्ठा net_bridge_fdb_entry *fdb_create(काष्ठा net_bridge *br,
					       काष्ठा net_bridge_port *source,
					       स्थिर अचिन्हित अक्षर *addr,
					       __u16 vid,
					       अचिन्हित दीर्घ flags)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;

	fdb = kmem_cache_alloc(br_fdb_cache, GFP_ATOMIC);
	अगर (fdb) अणु
		स_नकल(fdb->key.addr.addr, addr, ETH_ALEN);
		fdb->dst = source;
		fdb->key.vlan_id = vid;
		fdb->flags = flags;
		fdb->updated = fdb->used = jअगरfies;
		अगर (rhashtable_lookup_insert_fast(&br->fdb_hash_tbl,
						  &fdb->rhnode,
						  br_fdb_rht_params)) अणु
			kmem_cache_मुक्त(br_fdb_cache, fdb);
			fdb = शून्य;
		पूर्ण अन्यथा अणु
			hlist_add_head_rcu(&fdb->fdb_node, &br->fdb_list);
		पूर्ण
	पूर्ण
	वापस fdb;
पूर्ण

अटल पूर्णांक fdb_insert(काष्ठा net_bridge *br, काष्ठा net_bridge_port *source,
		  स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;

	अगर (!is_valid_ether_addr(addr))
		वापस -EINVAL;

	fdb = br_fdb_find(br, addr, vid);
	अगर (fdb) अणु
		/* it is okay to have multiple ports with same
		 * address, just use the first one.
		 */
		अगर (test_bit(BR_FDB_LOCAL, &fdb->flags))
			वापस 0;
		br_warn(br, "adding interface %s with same address as a received packet (addr:%pM, vlan:%u)\n",
		       source ? source->dev->name : br->dev->name, addr, vid);
		fdb_delete(br, fdb, true);
	पूर्ण

	fdb = fdb_create(br, source, addr, vid,
			 BIT(BR_FDB_LOCAL) | BIT(BR_FDB_STATIC));
	अगर (!fdb)
		वापस -ENOMEM;

	fdb_add_hw_addr(br, addr);
	fdb_notअगरy(br, fdb, RTM_NEWNEIGH, true);
	वापस 0;
पूर्ण

/* Add entry क्रम local address of पूर्णांकerface */
पूर्णांक br_fdb_insert(काष्ठा net_bridge *br, काष्ठा net_bridge_port *source,
		  स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	पूर्णांक ret;

	spin_lock_bh(&br->hash_lock);
	ret = fdb_insert(br, source, addr, vid);
	spin_unlock_bh(&br->hash_lock);
	वापस ret;
पूर्ण

/* वापसs true अगर the fdb was modअगरied */
अटल bool __fdb_mark_active(काष्ठा net_bridge_fdb_entry *fdb)
अणु
	वापस !!(test_bit(BR_FDB_NOTIFY_INACTIVE, &fdb->flags) &&
		  test_and_clear_bit(BR_FDB_NOTIFY_INACTIVE, &fdb->flags));
पूर्ण

व्योम br_fdb_update(काष्ठा net_bridge *br, काष्ठा net_bridge_port *source,
		   स्थिर अचिन्हित अक्षर *addr, u16 vid, अचिन्हित दीर्घ flags)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;

	/* some users want to always flood. */
	अगर (hold_समय(br) == 0)
		वापस;

	fdb = fdb_find_rcu(&br->fdb_hash_tbl, addr, vid);
	अगर (likely(fdb)) अणु
		/* attempt to update an entry क्रम a local पूर्णांकerface */
		अगर (unlikely(test_bit(BR_FDB_LOCAL, &fdb->flags))) अणु
			अगर (net_ratelimit())
				br_warn(br, "received packet on %s with own address as source address (addr:%pM, vlan:%u)\n",
					source->dev->name, addr, vid);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ now = jअगरfies;
			bool fdb_modअगरied = false;

			अगर (now != fdb->updated) अणु
				fdb->updated = now;
				fdb_modअगरied = __fdb_mark_active(fdb);
			पूर्ण

			/* fastpath: update of existing entry */
			अगर (unlikely(source != fdb->dst &&
				     !test_bit(BR_FDB_STICKY, &fdb->flags))) अणु
				br_चयनdev_fdb_notअगरy(fdb, RTM_DELNEIGH);
				fdb->dst = source;
				fdb_modअगरied = true;
				/* Take over HW learned entry */
				अगर (unlikely(test_bit(BR_FDB_ADDED_BY_EXT_LEARN,
						      &fdb->flags)))
					clear_bit(BR_FDB_ADDED_BY_EXT_LEARN,
						  &fdb->flags);
			पूर्ण

			अगर (unlikely(test_bit(BR_FDB_ADDED_BY_USER, &flags)))
				set_bit(BR_FDB_ADDED_BY_USER, &fdb->flags);
			अगर (unlikely(fdb_modअगरied)) अणु
				trace_br_fdb_update(br, source, addr, vid, flags);
				fdb_notअगरy(br, fdb, RTM_NEWNEIGH, true);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_lock(&br->hash_lock);
		fdb = fdb_create(br, source, addr, vid, flags);
		अगर (fdb) अणु
			trace_br_fdb_update(br, source, addr, vid, flags);
			fdb_notअगरy(br, fdb, RTM_NEWNEIGH, true);
		पूर्ण
		/* अन्यथा  we lose race and someone अन्यथा inserts
		 * it first, करोn't bother updating
		 */
		spin_unlock(&br->hash_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक fdb_to_nud(स्थिर काष्ठा net_bridge *br,
		      स्थिर काष्ठा net_bridge_fdb_entry *fdb)
अणु
	अगर (test_bit(BR_FDB_LOCAL, &fdb->flags))
		वापस NUD_PERMANENT;
	अन्यथा अगर (test_bit(BR_FDB_STATIC, &fdb->flags))
		वापस NUD_NOARP;
	अन्यथा अगर (has_expired(br, fdb))
		वापस NUD_STALE;
	अन्यथा
		वापस NUD_REACHABLE;
पूर्ण

अटल पूर्णांक fdb_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_bridge *br,
			 स्थिर काष्ठा net_bridge_fdb_entry *fdb,
			 u32 portid, u32 seq, पूर्णांक type, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा nda_cacheinfo ci;
	काष्ठा nlmsghdr *nlh;
	काष्ठा ndmsg *ndm;

	nlh = nlmsg_put(skb, portid, seq, type, माप(*ndm), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	ndm->ndm_family	 = AF_BRIDGE;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_flags	 = 0;
	ndm->ndm_type	 = 0;
	ndm->ndm_अगरindex = fdb->dst ? fdb->dst->dev->अगरindex : br->dev->अगरindex;
	ndm->ndm_state   = fdb_to_nud(br, fdb);

	अगर (test_bit(BR_FDB_OFFLOADED, &fdb->flags))
		ndm->ndm_flags |= NTF_OFFLOADED;
	अगर (test_bit(BR_FDB_ADDED_BY_EXT_LEARN, &fdb->flags))
		ndm->ndm_flags |= NTF_EXT_LEARNED;
	अगर (test_bit(BR_FDB_STICKY, &fdb->flags))
		ndm->ndm_flags |= NTF_STICKY;

	अगर (nla_put(skb, NDA_LLADDR, ETH_ALEN, &fdb->key.addr))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, NDA_MASTER, br->dev->अगरindex))
		जाओ nla_put_failure;
	ci.ndm_used	 = jअगरfies_to_घड़ी_प्रकार(now - fdb->used);
	ci.ndm_confirmed = 0;
	ci.ndm_updated	 = jअगरfies_to_घड़ी_प्रकार(now - fdb->updated);
	ci.ndm_refcnt	 = 0;
	अगर (nla_put(skb, NDA_CACHEINFO, माप(ci), &ci))
		जाओ nla_put_failure;

	अगर (fdb->key.vlan_id && nla_put(skb, NDA_VLAN, माप(u16),
					&fdb->key.vlan_id))
		जाओ nla_put_failure;

	अगर (test_bit(BR_FDB_NOTIFY, &fdb->flags)) अणु
		काष्ठा nlattr *nest = nla_nest_start(skb, NDA_FDB_EXT_ATTRS);
		u8 notअगरy_bits = FDB_NOTIFY_BIT;

		अगर (!nest)
			जाओ nla_put_failure;
		अगर (test_bit(BR_FDB_NOTIFY_INACTIVE, &fdb->flags))
			notअगरy_bits |= FDB_NOTIFY_INACTIVE_BIT;

		अगर (nla_put_u8(skb, NFEA_ACTIVITY_NOTIFY, notअगरy_bits)) अणु
			nla_nest_cancel(skb, nest);
			जाओ nla_put_failure;
		पूर्ण

		nla_nest_end(skb, nest);
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल अंतरभूत माप_प्रकार fdb_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा ndmsg))
		+ nla_total_size(ETH_ALEN) /* NDA_LLADDR */
		+ nla_total_size(माप(u32)) /* NDA_MASTER */
		+ nla_total_size(माप(u16)) /* NDA_VLAN */
		+ nla_total_size(माप(काष्ठा nda_cacheinfo))
		+ nla_total_size(0) /* NDA_FDB_EXT_ATTRS */
		+ nla_total_size(माप(u8)); /* NFEA_ACTIVITY_NOTIFY */
पूर्ण

अटल पूर्णांक br_fdb_replay_one(काष्ठा notअगरier_block *nb,
			     काष्ठा net_bridge_fdb_entry *fdb,
			     काष्ठा net_device *dev)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info item;
	पूर्णांक err;

	item.addr = fdb->key.addr.addr;
	item.vid = fdb->key.vlan_id;
	item.added_by_user = test_bit(BR_FDB_ADDED_BY_USER, &fdb->flags);
	item.offloaded = test_bit(BR_FDB_OFFLOADED, &fdb->flags);
	item.info.dev = dev;

	err = nb->notअगरier_call(nb, SWITCHDEV_FDB_ADD_TO_DEVICE, &item);
	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण

पूर्णांक br_fdb_replay(काष्ठा net_device *br_dev, काष्ठा net_device *dev,
		  काष्ठा notअगरier_block *nb)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;
	काष्ठा net_bridge *br;
	पूर्णांक err = 0;

	अगर (!netअगर_is_bridge_master(br_dev) || !netअगर_is_bridge_port(dev))
		वापस -EINVAL;

	br = netdev_priv(br_dev);

	rcu_पढ़ो_lock();

	hlist_क्रम_each_entry_rcu(fdb, &br->fdb_list, fdb_node) अणु
		काष्ठा net_bridge_port *dst = READ_ONCE(fdb->dst);
		काष्ठा net_device *dst_dev;

		dst_dev = dst ? dst->dev : br->dev;
		अगर (dst_dev != br_dev && dst_dev != dev)
			जारी;

		err = br_fdb_replay_one(nb, fdb, dst_dev);
		अगर (err)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(br_fdb_replay);

अटल व्योम fdb_notअगरy(काष्ठा net_bridge *br,
		       स्थिर काष्ठा net_bridge_fdb_entry *fdb, पूर्णांक type,
		       bool swdev_notअगरy)
अणु
	काष्ठा net *net = dev_net(br->dev);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	अगर (swdev_notअगरy)
		br_चयनdev_fdb_notअगरy(fdb, type);

	skb = nlmsg_new(fdb_nlmsg_size(), GFP_ATOMIC);
	अगर (skb == शून्य)
		जाओ errout;

	err = fdb_fill_info(skb, br, fdb, 0, 0, type, 0);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in fdb_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, 0, RTNLGRP_NEIGH, शून्य, GFP_ATOMIC);
	वापस;
errout:
	rtnl_set_sk_err(net, RTNLGRP_NEIGH, err);
पूर्ण

/* Dump inक्रमmation about entries, in response to GETNEIGH */
पूर्णांक br_fdb_dump(काष्ठा sk_buff *skb,
		काष्ठा netlink_callback *cb,
		काष्ठा net_device *dev,
		काष्ठा net_device *filter_dev,
		पूर्णांक *idx)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_fdb_entry *f;
	पूर्णांक err = 0;

	अगर (!(dev->priv_flags & IFF_EBRIDGE))
		वापस err;

	अगर (!filter_dev) अणु
		err = nकरो_dflt_fdb_dump(skb, cb, dev, शून्य, idx);
		अगर (err < 0)
			वापस err;
	पूर्ण

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(f, &br->fdb_list, fdb_node) अणु
		अगर (*idx < cb->args[2])
			जाओ skip;
		अगर (filter_dev && (!f->dst || f->dst->dev != filter_dev)) अणु
			अगर (filter_dev != dev)
				जाओ skip;
			/* !f->dst is a special हाल क्रम bridge
			 * It means the MAC beदीर्घs to the bridge
			 * Thereक्रमe need a little more filtering
			 * we only want to dump the !f->dst हाल
			 */
			अगर (f->dst)
				जाओ skip;
		पूर्ण
		अगर (!filter_dev && f->dst)
			जाओ skip;

		err = fdb_fill_info(skb, br, f,
				    NETLINK_CB(cb->skb).portid,
				    cb->nlh->nlmsg_seq,
				    RTM_NEWNEIGH,
				    NLM_F_MULTI);
		अगर (err < 0)
			अवरोध;
skip:
		*idx += 1;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

पूर्णांक br_fdb_get(काष्ठा sk_buff *skb,
	       काष्ठा nlattr *tb[],
	       काष्ठा net_device *dev,
	       स्थिर अचिन्हित अक्षर *addr,
	       u16 vid, u32 portid, u32 seq,
	       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_fdb_entry *f;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	f = br_fdb_find_rcu(br, addr, vid);
	अगर (!f) अणु
		NL_SET_ERR_MSG(extack, "Fdb entry not found");
		err = -ENOENT;
		जाओ errout;
	पूर्ण

	err = fdb_fill_info(skb, br, f, portid, seq,
			    RTM_NEWNEIGH, 0);
errout:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

/* वापसs true अगर the fdb is modअगरied */
अटल bool fdb_handle_notअगरy(काष्ठा net_bridge_fdb_entry *fdb, u8 notअगरy)
अणु
	bool modअगरied = false;

	/* allow to mark an entry as inactive, usually करोne on creation */
	अगर ((notअगरy & FDB_NOTIFY_INACTIVE_BIT) &&
	    !test_and_set_bit(BR_FDB_NOTIFY_INACTIVE, &fdb->flags))
		modअगरied = true;

	अगर ((notअगरy & FDB_NOTIFY_BIT) &&
	    !test_and_set_bit(BR_FDB_NOTIFY, &fdb->flags)) अणु
		/* enabled activity tracking */
		modअगरied = true;
	पूर्ण अन्यथा अगर (!(notअगरy & FDB_NOTIFY_BIT) &&
		   test_and_clear_bit(BR_FDB_NOTIFY, &fdb->flags)) अणु
		/* disabled activity tracking, clear notअगरy state */
		clear_bit(BR_FDB_NOTIFY_INACTIVE, &fdb->flags);
		modअगरied = true;
	पूर्ण

	वापस modअगरied;
पूर्ण

/* Update (create or replace) क्रमwarding database entry */
अटल पूर्णांक fdb_add_entry(काष्ठा net_bridge *br, काष्ठा net_bridge_port *source,
			 स्थिर u8 *addr, काष्ठा ndmsg *ndm, u16 flags, u16 vid,
			 काष्ठा nlattr *nfea_tb[])
अणु
	bool is_sticky = !!(ndm->ndm_flags & NTF_STICKY);
	bool refresh = !nfea_tb[NFEA_DONT_REFRESH];
	काष्ठा net_bridge_fdb_entry *fdb;
	u16 state = ndm->ndm_state;
	bool modअगरied = false;
	u8 notअगरy = 0;

	/* If the port cannot learn allow only local and अटल entries */
	अगर (source && !(state & NUD_PERMANENT) && !(state & NUD_NOARP) &&
	    !(source->state == BR_STATE_LEARNING ||
	      source->state == BR_STATE_FORWARDING))
		वापस -EPERM;

	अगर (!source && !(state & NUD_PERMANENT)) अणु
		pr_info("bridge: RTM_NEWNEIGH %s without NUD_PERMANENT\n",
			br->dev->name);
		वापस -EINVAL;
	पूर्ण

	अगर (is_sticky && (state & NUD_PERMANENT))
		वापस -EINVAL;

	अगर (nfea_tb[NFEA_ACTIVITY_NOTIFY]) अणु
		notअगरy = nla_get_u8(nfea_tb[NFEA_ACTIVITY_NOTIFY]);
		अगर ((notअगरy & ~BR_FDB_NOTIFY_SETTABLE_BITS) ||
		    (notअगरy & BR_FDB_NOTIFY_SETTABLE_BITS) == FDB_NOTIFY_INACTIVE_BIT)
			वापस -EINVAL;
	पूर्ण

	fdb = br_fdb_find(br, addr, vid);
	अगर (fdb == शून्य) अणु
		अगर (!(flags & NLM_F_CREATE))
			वापस -ENOENT;

		fdb = fdb_create(br, source, addr, vid, 0);
		अगर (!fdb)
			वापस -ENOMEM;

		modअगरied = true;
	पूर्ण अन्यथा अणु
		अगर (flags & NLM_F_EXCL)
			वापस -EEXIST;

		अगर (fdb->dst != source) अणु
			fdb->dst = source;
			modअगरied = true;
		पूर्ण
	पूर्ण

	अगर (fdb_to_nud(br, fdb) != state) अणु
		अगर (state & NUD_PERMANENT) अणु
			set_bit(BR_FDB_LOCAL, &fdb->flags);
			अगर (!test_and_set_bit(BR_FDB_STATIC, &fdb->flags))
				fdb_add_hw_addr(br, addr);
		पूर्ण अन्यथा अगर (state & NUD_NOARP) अणु
			clear_bit(BR_FDB_LOCAL, &fdb->flags);
			अगर (!test_and_set_bit(BR_FDB_STATIC, &fdb->flags))
				fdb_add_hw_addr(br, addr);
		पूर्ण अन्यथा अणु
			clear_bit(BR_FDB_LOCAL, &fdb->flags);
			अगर (test_and_clear_bit(BR_FDB_STATIC, &fdb->flags))
				fdb_del_hw_addr(br, addr);
		पूर्ण

		modअगरied = true;
	पूर्ण

	अगर (is_sticky != test_bit(BR_FDB_STICKY, &fdb->flags)) अणु
		change_bit(BR_FDB_STICKY, &fdb->flags);
		modअगरied = true;
	पूर्ण

	अगर (fdb_handle_notअगरy(fdb, notअगरy))
		modअगरied = true;

	set_bit(BR_FDB_ADDED_BY_USER, &fdb->flags);

	fdb->used = jअगरfies;
	अगर (modअगरied) अणु
		अगर (refresh)
			fdb->updated = jअगरfies;
		fdb_notअगरy(br, fdb, RTM_NEWNEIGH, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __br_fdb_add(काष्ठा ndmsg *ndm, काष्ठा net_bridge *br,
			काष्ठा net_bridge_port *p, स्थिर अचिन्हित अक्षर *addr,
			u16 nlh_flags, u16 vid, काष्ठा nlattr *nfea_tb[])
अणु
	पूर्णांक err = 0;

	अगर (ndm->ndm_flags & NTF_USE) अणु
		अगर (!p) अणु
			pr_info("bridge: RTM_NEWNEIGH %s with NTF_USE is not supported\n",
				br->dev->name);
			वापस -EINVAL;
		पूर्ण
		अगर (!nbp_state_should_learn(p))
			वापस 0;

		local_bh_disable();
		rcu_पढ़ो_lock();
		br_fdb_update(br, p, addr, vid, BIT(BR_FDB_ADDED_BY_USER));
		rcu_पढ़ो_unlock();
		local_bh_enable();
	पूर्ण अन्यथा अगर (ndm->ndm_flags & NTF_EXT_LEARNED) अणु
		err = br_fdb_बाह्यal_learn_add(br, p, addr, vid, true);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&br->hash_lock);
		err = fdb_add_entry(br, p, addr, ndm, nlh_flags, vid, nfea_tb);
		spin_unlock_bh(&br->hash_lock);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy br_nda_fdb_pol[NFEA_MAX + 1] = अणु
	[NFEA_ACTIVITY_NOTIFY]	= अणु .type = NLA_U8 पूर्ण,
	[NFEA_DONT_REFRESH]	= अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

/* Add new permanent fdb entry with RTM_NEWNEIGH */
पूर्णांक br_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
	       काष्ठा net_device *dev,
	       स्थिर अचिन्हित अक्षर *addr, u16 vid, u16 nlh_flags,
	       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *nfea_tb[NFEA_MAX + 1], *attr;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p = शून्य;
	काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge *br = शून्य;
	पूर्णांक err = 0;

	trace_br_fdb_add(ndm, dev, addr, vid, nlh_flags);

	अगर (!(ndm->ndm_state & (NUD_PERMANENT|NUD_NOARP|NUD_REACHABLE))) अणु
		pr_info("bridge: RTM_NEWNEIGH with invalid state %#x\n", ndm->ndm_state);
		वापस -EINVAL;
	पूर्ण

	अगर (is_zero_ether_addr(addr)) अणु
		pr_info("bridge: RTM_NEWNEIGH with invalid ether address\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->priv_flags & IFF_EBRIDGE) अणु
		br = netdev_priv(dev);
		vg = br_vlan_group(br);
	पूर्ण अन्यथा अणु
		p = br_port_get_rtnl(dev);
		अगर (!p) अणु
			pr_info("bridge: RTM_NEWNEIGH %s not a bridge port\n",
				dev->name);
			वापस -EINVAL;
		पूर्ण
		br = p->br;
		vg = nbp_vlan_group(p);
	पूर्ण

	अगर (tb[NDA_FDB_EXT_ATTRS]) अणु
		attr = tb[NDA_FDB_EXT_ATTRS];
		err = nla_parse_nested(nfea_tb, NFEA_MAX, attr,
				       br_nda_fdb_pol, extack);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		स_रखो(nfea_tb, 0, माप(काष्ठा nlattr *) * (NFEA_MAX + 1));
	पूर्ण

	अगर (vid) अणु
		v = br_vlan_find(vg, vid);
		अगर (!v || !br_vlan_should_use(v)) अणु
			pr_info("bridge: RTM_NEWNEIGH with unconfigured vlan %d on %s\n", vid, dev->name);
			वापस -EINVAL;
		पूर्ण

		/* VID was specअगरied, so use it. */
		err = __br_fdb_add(ndm, br, p, addr, nlh_flags, vid, nfea_tb);
	पूर्ण अन्यथा अणु
		err = __br_fdb_add(ndm, br, p, addr, nlh_flags, 0, nfea_tb);
		अगर (err || !vg || !vg->num_vlans)
			जाओ out;

		/* We have vlans configured on this port and user didn't
		 * specअगरy a VLAN.  To be nice, add/update entry क्रम every
		 * vlan on this port.
		 */
		list_क्रम_each_entry(v, &vg->vlan_list, vlist) अणु
			अगर (!br_vlan_should_use(v))
				जारी;
			err = __br_fdb_add(ndm, br, p, addr, nlh_flags, v->vid,
					   nfea_tb);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस err;
पूर्ण

अटल पूर्णांक fdb_delete_by_addr_and_port(काष्ठा net_bridge *br,
				       स्थिर काष्ठा net_bridge_port *p,
				       स्थिर u8 *addr, u16 vlan)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;

	fdb = br_fdb_find(br, addr, vlan);
	अगर (!fdb || fdb->dst != p)
		वापस -ENOENT;

	fdb_delete(br, fdb, true);

	वापस 0;
पूर्ण

अटल पूर्णांक __br_fdb_delete(काष्ठा net_bridge *br,
			   स्थिर काष्ठा net_bridge_port *p,
			   स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	पूर्णांक err;

	spin_lock_bh(&br->hash_lock);
	err = fdb_delete_by_addr_and_port(br, p, addr, vid);
	spin_unlock_bh(&br->hash_lock);

	वापस err;
पूर्ण

/* Remove neighbor entry with RTM_DELNEIGH */
पूर्णांक br_fdb_delete(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
		  काष्ठा net_device *dev,
		  स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p = शून्य;
	काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge *br;
	पूर्णांक err;

	अगर (dev->priv_flags & IFF_EBRIDGE) अणु
		br = netdev_priv(dev);
		vg = br_vlan_group(br);
	पूर्ण अन्यथा अणु
		p = br_port_get_rtnl(dev);
		अगर (!p) अणु
			pr_info("bridge: RTM_DELNEIGH %s not a bridge port\n",
				dev->name);
			वापस -EINVAL;
		पूर्ण
		vg = nbp_vlan_group(p);
		br = p->br;
	पूर्ण

	अगर (vid) अणु
		v = br_vlan_find(vg, vid);
		अगर (!v) अणु
			pr_info("bridge: RTM_DELNEIGH with unconfigured vlan %d on %s\n", vid, dev->name);
			वापस -EINVAL;
		पूर्ण

		err = __br_fdb_delete(br, p, addr, vid);
	पूर्ण अन्यथा अणु
		err = -ENOENT;
		err &= __br_fdb_delete(br, p, addr, 0);
		अगर (!vg || !vg->num_vlans)
			वापस err;

		list_क्रम_each_entry(v, &vg->vlan_list, vlist) अणु
			अगर (!br_vlan_should_use(v))
				जारी;
			err &= __br_fdb_delete(br, p, addr, v->vid);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक br_fdb_sync_अटल(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge_fdb_entry *f, *पंचांगp;
	पूर्णांक err = 0;

	ASSERT_RTNL();

	/* the key here is that अटल entries change only under rtnl */
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(f, &br->fdb_list, fdb_node) अणु
		/* We only care क्रम अटल entries */
		अगर (!test_bit(BR_FDB_STATIC, &f->flags))
			जारी;
		err = dev_uc_add(p->dev, f->key.addr.addr);
		अगर (err)
			जाओ rollback;
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();

	वापस err;

rollback:
	hlist_क्रम_each_entry_rcu(पंचांगp, &br->fdb_list, fdb_node) अणु
		/* We only care क्रम अटल entries */
		अगर (!test_bit(BR_FDB_STATIC, &पंचांगp->flags))
			जारी;
		अगर (पंचांगp == f)
			अवरोध;
		dev_uc_del(p->dev, पंचांगp->key.addr.addr);
	पूर्ण

	जाओ करोne;
पूर्ण

व्योम br_fdb_unsync_अटल(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge_fdb_entry *f;

	ASSERT_RTNL();

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(f, &br->fdb_list, fdb_node) अणु
		/* We only care क्रम अटल entries */
		अगर (!test_bit(BR_FDB_STATIC, &f->flags))
			जारी;

		dev_uc_del(p->dev, f->key.addr.addr);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक br_fdb_बाह्यal_learn_add(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid,
			      bool swdev_notअगरy)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;
	bool modअगरied = false;
	पूर्णांक err = 0;

	trace_br_fdb_बाह्यal_learn_add(br, p, addr, vid);

	spin_lock_bh(&br->hash_lock);

	fdb = br_fdb_find(br, addr, vid);
	अगर (!fdb) अणु
		अचिन्हित दीर्घ flags = BIT(BR_FDB_ADDED_BY_EXT_LEARN);

		अगर (swdev_notअगरy)
			flags |= BIT(BR_FDB_ADDED_BY_USER);
		fdb = fdb_create(br, p, addr, vid, flags);
		अगर (!fdb) अणु
			err = -ENOMEM;
			जाओ err_unlock;
		पूर्ण
		fdb_notअगरy(br, fdb, RTM_NEWNEIGH, swdev_notअगरy);
	पूर्ण अन्यथा अणु
		fdb->updated = jअगरfies;

		अगर (fdb->dst != p) अणु
			fdb->dst = p;
			modअगरied = true;
		पूर्ण

		अगर (test_bit(BR_FDB_ADDED_BY_EXT_LEARN, &fdb->flags)) अणु
			/* Refresh entry */
			fdb->used = jअगरfies;
		पूर्ण अन्यथा अगर (!test_bit(BR_FDB_ADDED_BY_USER, &fdb->flags)) अणु
			/* Take over SW learned entry */
			set_bit(BR_FDB_ADDED_BY_EXT_LEARN, &fdb->flags);
			modअगरied = true;
		पूर्ण

		अगर (swdev_notअगरy)
			set_bit(BR_FDB_ADDED_BY_USER, &fdb->flags);

		अगर (modअगरied)
			fdb_notअगरy(br, fdb, RTM_NEWNEIGH, swdev_notअगरy);
	पूर्ण

err_unlock:
	spin_unlock_bh(&br->hash_lock);

	वापस err;
पूर्ण

पूर्णांक br_fdb_बाह्यal_learn_del(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid,
			      bool swdev_notअगरy)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;
	पूर्णांक err = 0;

	spin_lock_bh(&br->hash_lock);

	fdb = br_fdb_find(br, addr, vid);
	अगर (fdb && test_bit(BR_FDB_ADDED_BY_EXT_LEARN, &fdb->flags))
		fdb_delete(br, fdb, swdev_notअगरy);
	अन्यथा
		err = -ENOENT;

	spin_unlock_bh(&br->hash_lock);

	वापस err;
पूर्ण

व्योम br_fdb_offloaded_set(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			  स्थिर अचिन्हित अक्षर *addr, u16 vid, bool offloaded)
अणु
	काष्ठा net_bridge_fdb_entry *fdb;

	spin_lock_bh(&br->hash_lock);

	fdb = br_fdb_find(br, addr, vid);
	अगर (fdb && offloaded != test_bit(BR_FDB_OFFLOADED, &fdb->flags))
		change_bit(BR_FDB_OFFLOADED, &fdb->flags);

	spin_unlock_bh(&br->hash_lock);
पूर्ण

व्योम br_fdb_clear_offload(स्थिर काष्ठा net_device *dev, u16 vid)
अणु
	काष्ठा net_bridge_fdb_entry *f;
	काष्ठा net_bridge_port *p;

	ASSERT_RTNL();

	p = br_port_get_rtnl(dev);
	अगर (!p)
		वापस;

	spin_lock_bh(&p->br->hash_lock);
	hlist_क्रम_each_entry(f, &p->br->fdb_list, fdb_node) अणु
		अगर (f->dst == p && f->key.vlan_id == vid)
			clear_bit(BR_FDB_OFFLOADED, &f->flags);
	पूर्ण
	spin_unlock_bh(&p->br->hash_lock);
पूर्ण
EXPORT_SYMBOL_GPL(br_fdb_clear_offload);
