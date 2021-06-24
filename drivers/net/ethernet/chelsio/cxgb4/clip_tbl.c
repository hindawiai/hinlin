<शैली गुरु>
/*
 *  This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *  Copyright (C) 2003-2014 Chelsio Communications.  All rights reserved.
 *
 *  Written by Deepak (deepak.s@chelsio.com)
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the LICENSE file included in this
 *  release क्रम licensing terms and conditions.
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/addrconf.h>
#समावेश "cxgb4.h"
#समावेश "clip_tbl.h"

अटल अंतरभूत अचिन्हित पूर्णांक ipv4_clip_hash(काष्ठा clip_tbl *c, स्थिर u32 *key)
अणु
	अचिन्हित पूर्णांक clipt_size_half = c->clipt_size / 2;

	वापस jhash_1word(*key, 0) % clipt_size_half;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ipv6_clip_hash(काष्ठा clip_tbl *d, स्थिर u32 *key)
अणु
	अचिन्हित पूर्णांक clipt_size_half = d->clipt_size / 2;
	u32 xor = key[0] ^ key[1] ^ key[2] ^ key[3];

	वापस clipt_size_half +
		(jhash_1word(xor, 0) % clipt_size_half);
पूर्ण

अटल अचिन्हित पूर्णांक clip_addr_hash(काष्ठा clip_tbl *ctbl, स्थिर u32 *addr,
				   u8 v6)
अणु
	वापस v6 ? ipv6_clip_hash(ctbl, addr) :
			ipv4_clip_hash(ctbl, addr);
पूर्ण

अटल पूर्णांक clip6_get_mbox(स्थिर काष्ठा net_device *dev,
			  स्थिर काष्ठा in6_addr *lip)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा fw_clip_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_CLIP_CMD) |
			      FW_CMD_REQUEST_F | FW_CMD_WRITE_F);
	c.alloc_to_len16 = htonl(FW_CLIP_CMD_ALLOC_F | FW_LEN16(c));
	*(__be64 *)&c.ip_hi = *(__be64 *)(lip->s6_addr);
	*(__be64 *)&c.ip_lo = *(__be64 *)(lip->s6_addr + 8);
	वापस t4_wr_mbox_meat(adap, adap->mbox, &c, माप(c), &c, false);
पूर्ण

अटल पूर्णांक clip6_release_mbox(स्थिर काष्ठा net_device *dev,
			      स्थिर काष्ठा in6_addr *lip)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा fw_clip_cmd c;

	स_रखो(&c, 0, माप(c));
	c.op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_CLIP_CMD) |
			      FW_CMD_REQUEST_F | FW_CMD_READ_F);
	c.alloc_to_len16 = htonl(FW_CLIP_CMD_FREE_F | FW_LEN16(c));
	*(__be64 *)&c.ip_hi = *(__be64 *)(lip->s6_addr);
	*(__be64 *)&c.ip_lo = *(__be64 *)(lip->s6_addr + 8);
	वापस t4_wr_mbox_meat(adap, adap->mbox, &c, माप(c), &c, false);
पूर्ण

पूर्णांक cxgb4_clip_get(स्थिर काष्ठा net_device *dev, स्थिर u32 *lip, u8 v6)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा clip_tbl *ctbl = adap->clipt;
	काष्ठा clip_entry *ce, *cte;
	u32 *addr = (u32 *)lip;
	पूर्णांक hash;
	पूर्णांक ret = -1;

	अगर (!ctbl)
		वापस 0;

	hash = clip_addr_hash(ctbl, addr, v6);

	पढ़ो_lock_bh(&ctbl->lock);
	list_क्रम_each_entry(cte, &ctbl->hash_list[hash], list) अणु
		अगर (cte->addr6.sin6_family == AF_INET6 && v6)
			ret = स_भेद(lip, cte->addr6.sin6_addr.s6_addr,
				     माप(काष्ठा in6_addr));
		अन्यथा अगर (cte->addr.sin_family == AF_INET && !v6)
			ret = स_भेद(lip, (अक्षर *)(&cte->addr.sin_addr),
				     माप(काष्ठा in_addr));
		अगर (!ret) अणु
			ce = cte;
			पढ़ो_unlock_bh(&ctbl->lock);
			refcount_inc(&ce->refcnt);
			वापस 0;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&ctbl->lock);

	ग_लिखो_lock_bh(&ctbl->lock);
	अगर (!list_empty(&ctbl->ce_मुक्त_head)) अणु
		ce = list_first_entry(&ctbl->ce_मुक्त_head,
				      काष्ठा clip_entry, list);
		list_del(&ce->list);
		INIT_LIST_HEAD(&ce->list);
		spin_lock_init(&ce->lock);
		refcount_set(&ce->refcnt, 0);
		atomic_dec(&ctbl->nमुक्त);
		list_add_tail(&ce->list, &ctbl->hash_list[hash]);
		अगर (v6) अणु
			ce->addr6.sin6_family = AF_INET6;
			स_नकल(ce->addr6.sin6_addr.s6_addr,
			       lip, माप(काष्ठा in6_addr));
			ret = clip6_get_mbox(dev, (स्थिर काष्ठा in6_addr *)lip);
			अगर (ret) अणु
				ग_लिखो_unlock_bh(&ctbl->lock);
				dev_err(adap->pdev_dev,
					"CLIP FW cmd failed with error %d, "
					"Connections using %pI6c wont be "
					"offloaded",
					ret, ce->addr6.sin6_addr.s6_addr);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			ce->addr.sin_family = AF_INET;
			स_नकल((अक्षर *)(&ce->addr.sin_addr), lip,
			       माप(काष्ठा in_addr));
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखो_unlock_bh(&ctbl->lock);
		dev_info(adap->pdev_dev, "CLIP table overflow, "
			 "Connections using %pI6c wont be offloaded",
			 (व्योम *)lip);
		वापस -ENOMEM;
	पूर्ण
	ग_लिखो_unlock_bh(&ctbl->lock);
	refcount_set(&ce->refcnt, 1);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cxgb4_clip_get);

व्योम cxgb4_clip_release(स्थिर काष्ठा net_device *dev, स्थिर u32 *lip, u8 v6)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा clip_tbl *ctbl = adap->clipt;
	काष्ठा clip_entry *ce, *cte;
	u32 *addr = (u32 *)lip;
	पूर्णांक hash;
	पूर्णांक ret = -1;

	अगर (!ctbl)
		वापस;

	hash = clip_addr_hash(ctbl, addr, v6);

	पढ़ो_lock_bh(&ctbl->lock);
	list_क्रम_each_entry(cte, &ctbl->hash_list[hash], list) अणु
		अगर (cte->addr6.sin6_family == AF_INET6 && v6)
			ret = स_भेद(lip, cte->addr6.sin6_addr.s6_addr,
				     माप(काष्ठा in6_addr));
		अन्यथा अगर (cte->addr.sin_family == AF_INET && !v6)
			ret = स_भेद(lip, (अक्षर *)(&cte->addr.sin_addr),
				     माप(काष्ठा in_addr));
		अगर (!ret) अणु
			ce = cte;
			पढ़ो_unlock_bh(&ctbl->lock);
			जाओ found;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&ctbl->lock);

	वापस;
found:
	ग_लिखो_lock_bh(&ctbl->lock);
	spin_lock_bh(&ce->lock);
	अगर (refcount_dec_and_test(&ce->refcnt)) अणु
		list_del(&ce->list);
		INIT_LIST_HEAD(&ce->list);
		list_add_tail(&ce->list, &ctbl->ce_मुक्त_head);
		atomic_inc(&ctbl->nमुक्त);
		अगर (v6)
			clip6_release_mbox(dev, (स्थिर काष्ठा in6_addr *)lip);
	पूर्ण
	spin_unlock_bh(&ce->lock);
	ग_लिखो_unlock_bh(&ctbl->lock);
पूर्ण
EXPORT_SYMBOL(cxgb4_clip_release);

/* Retrieves IPv6 addresses from a root device (bond, vlan) associated with
 * a physical device.
 * The physical device reference is needed to send the actul CLIP command.
 */
अटल पूर्णांक cxgb4_update_dev_clip(काष्ठा net_device *root_dev,
				 काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev = शून्य;
	काष्ठा inet6_अगरaddr *अगरa;
	पूर्णांक ret = 0;

	idev = __in6_dev_get(root_dev);
	अगर (!idev)
		वापस ret;

	पढ़ो_lock_bh(&idev->lock);
	list_क्रम_each_entry(अगरa, &idev->addr_list, अगर_list) अणु
		ret = cxgb4_clip_get(dev, (स्थिर u32 *)अगरa->addr.s6_addr, 1);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	पढ़ो_unlock_bh(&idev->lock);

	वापस ret;
पूर्ण

पूर्णांक cxgb4_update_root_dev_clip(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *root_dev = शून्य;
	पूर्णांक i, ret = 0;

	/* First populate the real net device's IPv6 addresses */
	ret = cxgb4_update_dev_clip(dev, dev);
	अगर (ret)
		वापस ret;

	/* Parse all bond and vlan devices layered on top of the physical dev */
	root_dev = netdev_master_upper_dev_get_rcu(dev);
	अगर (root_dev) अणु
		ret = cxgb4_update_dev_clip(root_dev, dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < VLAN_N_VID; i++) अणु
		root_dev = __vlan_find_dev_deep_rcu(dev, htons(ETH_P_8021Q), i);
		अगर (!root_dev)
			जारी;

		ret = cxgb4_update_dev_clip(root_dev, dev);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(cxgb4_update_root_dev_clip);

पूर्णांक clip_tbl_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	काष्ठा clip_tbl *ctbl = adapter->clipt;
	काष्ठा clip_entry *ce;
	अक्षर ip[60];
	पूर्णांक i;

	पढ़ो_lock_bh(&ctbl->lock);

	seq_माला_दो(seq, "IP Address                  Users\n");
	क्रम (i = 0 ; i < ctbl->clipt_size;  ++i) अणु
		list_क्रम_each_entry(ce, &ctbl->hash_list[i], list) अणु
			ip[0] = '\0';
			प्र_लिखो(ip, "%pISc", &ce->addr);
			seq_म_लिखो(seq, "%-25s   %u\n", ip,
				   refcount_पढ़ो(&ce->refcnt));
		पूर्ण
	पूर्ण
	seq_म_लिखो(seq, "Free clip entries : %d\n", atomic_पढ़ो(&ctbl->nमुक्त));

	पढ़ो_unlock_bh(&ctbl->lock);

	वापस 0;
पूर्ण

काष्ठा clip_tbl *t4_init_clip_tbl(अचिन्हित पूर्णांक clipt_start,
				  अचिन्हित पूर्णांक clipt_end)
अणु
	काष्ठा clip_entry *cl_list;
	काष्ठा clip_tbl *ctbl;
	अचिन्हित पूर्णांक clipt_size;
	पूर्णांक i;

	अगर (clipt_start >= clipt_end)
		वापस शून्य;
	clipt_size = clipt_end - clipt_start + 1;
	अगर (clipt_size < CLIPT_MIN_HASH_BUCKETS)
		वापस शून्य;

	ctbl = kvzalloc(काष्ठा_size(ctbl, hash_list, clipt_size), GFP_KERNEL);
	अगर (!ctbl)
		वापस शून्य;

	ctbl->clipt_start = clipt_start;
	ctbl->clipt_size = clipt_size;
	INIT_LIST_HEAD(&ctbl->ce_मुक्त_head);

	atomic_set(&ctbl->nमुक्त, clipt_size);
	rwlock_init(&ctbl->lock);

	क्रम (i = 0; i < ctbl->clipt_size; ++i)
		INIT_LIST_HEAD(&ctbl->hash_list[i]);

	cl_list = kvसुस्मृति(clipt_size, माप(काष्ठा clip_entry), GFP_KERNEL);
	अगर (!cl_list) अणु
		kvमुक्त(ctbl);
		वापस शून्य;
	पूर्ण
	ctbl->cl_list = (व्योम *)cl_list;

	क्रम (i = 0; i < clipt_size; i++) अणु
		INIT_LIST_HEAD(&cl_list[i].list);
		list_add_tail(&cl_list[i].list, &ctbl->ce_मुक्त_head);
	पूर्ण

	वापस ctbl;
पूर्ण

व्योम t4_cleanup_clip_tbl(काष्ठा adapter *adap)
अणु
	काष्ठा clip_tbl *ctbl = adap->clipt;

	अगर (ctbl) अणु
		kvमुक्त(ctbl->cl_list);
		kvमुक्त(ctbl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(t4_cleanup_clip_tbl);
