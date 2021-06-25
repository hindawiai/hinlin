<शैली गुरु>
/*
 *  Device operations क्रम the pnfs client.
 *
 *  Copyright (c) 2002
 *  The Regents of the University of Michigan
 *  All Rights Reserved
 *
 *  Dean Hildebअक्रम <dhildebz@umich.edu>
 *  Garth Goodson   <Garth.Goodson@netapp.com>
 *
 *  Permission is granted to use, copy, create derivative works, and
 *  redistribute this software and such derivative works क्रम any purpose,
 *  so दीर्घ as the name of the University of Michigan is not used in
 *  any advertising or खुलाity pertaining to the use or distribution
 *  of this software without specअगरic, written prior authorization. If
 *  the above copyright notice or any other identअगरication of the
 *  University of Michigan is included in any copy of any portion of
 *  this software, then the disclaimer below must also be included.
 *
 *  This software is provided as is, without representation or warranty
 *  of any kind either express or implied, including without limitation
 *  the implied warranties of merchantability, fitness क्रम a particular
 *  purpose, or noninfringement.  The Regents of the University of
 *  Michigan shall not be liable क्रम any damages, including special,
 *  indirect, incidental, or consequential damages, with respect to any
 *  claim arising out of or in connection with the use of the software,
 *  even अगर it has been or is hereafter advised of the possibility of
 *  such damages.
 */

#समावेश <linux/export.h>
#समावेश <linux/nfs_fs.h>
#समावेश "nfs4session.h"
#समावेश "internal.h"
#समावेश "pnfs.h"

#समावेश "nfs4trace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PNFS

/*
 * Device ID RCU cache. A device ID is unique per server and layout type.
 */
#घोषणा NFS4_DEVICE_ID_HASH_BITS	5
#घोषणा NFS4_DEVICE_ID_HASH_SIZE	(1 << NFS4_DEVICE_ID_HASH_BITS)
#घोषणा NFS4_DEVICE_ID_HASH_MASK	(NFS4_DEVICE_ID_HASH_SIZE - 1)


अटल काष्ठा hlist_head nfs4_deviceid_cache[NFS4_DEVICE_ID_HASH_SIZE];
अटल DEFINE_SPINLOCK(nfs4_deviceid_lock);

#अगर_घोषित NFS_DEBUG
व्योम
nfs4_prपूर्णांक_deviceid(स्थिर काष्ठा nfs4_deviceid *id)
अणु
	u32 *p = (u32 *)id;

	dprपूर्णांकk("%s: device id= [%x%x%x%x]\n", __func__,
		p[0], p[1], p[2], p[3]);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_prपूर्णांक_deviceid);
#पूर्ण_अगर

अटल अंतरभूत u32
nfs4_deviceid_hash(स्थिर काष्ठा nfs4_deviceid *id)
अणु
	अचिन्हित अक्षर *cptr = (अचिन्हित अक्षर *)id->data;
	अचिन्हित पूर्णांक nbytes = NFS4_DEVICEID4_SIZE;
	u32 x = 0;

	जबतक (nbytes--) अणु
		x *= 37;
		x += *cptr++;
	पूर्ण
	वापस x & NFS4_DEVICE_ID_HASH_MASK;
पूर्ण

अटल काष्ठा nfs4_deviceid_node *
_lookup_deviceid(स्थिर काष्ठा pnfs_layoutdriver_type *ld,
		 स्थिर काष्ठा nfs_client *clp, स्थिर काष्ठा nfs4_deviceid *id,
		 दीर्घ hash)
अणु
	काष्ठा nfs4_deviceid_node *d;

	hlist_क्रम_each_entry_rcu(d, &nfs4_deviceid_cache[hash], node)
		अगर (d->ld == ld && d->nfs_client == clp &&
		    !स_भेद(&d->deviceid, id, माप(*id))) अणु
			अगर (atomic_पढ़ो(&d->ref))
				वापस d;
			अन्यथा
				जारी;
		पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_deviceid_node *
nfs4_get_device_info(काष्ठा nfs_server *server,
		स्थिर काष्ठा nfs4_deviceid *dev_id,
		स्थिर काष्ठा cred *cred, gfp_t gfp_flags)
अणु
	काष्ठा nfs4_deviceid_node *d = शून्य;
	काष्ठा pnfs_device *pdev = शून्य;
	काष्ठा page **pages = शून्य;
	u32 max_resp_sz;
	पूर्णांक max_pages;
	पूर्णांक rc, i;

	/*
	 * Use the session max response size as the basis क्रम setting
	 * GETDEVICEINFO's maxcount
	 */
	max_resp_sz = server->nfs_client->cl_session->fc_attrs.max_resp_sz;
	अगर (server->pnfs_curr_ld->max_deviceinfo_size &&
	    server->pnfs_curr_ld->max_deviceinfo_size < max_resp_sz)
		max_resp_sz = server->pnfs_curr_ld->max_deviceinfo_size;
	max_pages = nfs_page_array_len(0, max_resp_sz);
	dprपूर्णांकk("%s: server %p max_resp_sz %u max_pages %d\n",
		__func__, server, max_resp_sz, max_pages);

	pdev = kzalloc(माप(*pdev), gfp_flags);
	अगर (!pdev)
		वापस शून्य;

	pages = kसुस्मृति(max_pages, माप(काष्ठा page *), gfp_flags);
	अगर (!pages)
		जाओ out_मुक्त_pdev;

	क्रम (i = 0; i < max_pages; i++) अणु
		pages[i] = alloc_page(gfp_flags);
		अगर (!pages[i])
			जाओ out_मुक्त_pages;
	पूर्ण

	स_नकल(&pdev->dev_id, dev_id, माप(*dev_id));
	pdev->layout_type = server->pnfs_curr_ld->id;
	pdev->pages = pages;
	pdev->pgbase = 0;
	pdev->pglen = max_resp_sz;
	pdev->mincount = 0;
	pdev->maxcount = max_resp_sz - nfs41_maxgetdevinfo_overhead;

	rc = nfs4_proc_getdeviceinfo(server, pdev, cred);
	dprपूर्णांकk("%s getdevice info returns %d\n", __func__, rc);
	अगर (rc)
		जाओ out_मुक्त_pages;

	/*
	 * Found new device, need to decode it and then add it to the
	 * list of known devices क्रम this mountpoपूर्णांक.
	 */
	d = server->pnfs_curr_ld->alloc_deviceid_node(server, pdev,
			gfp_flags);
	अगर (d && pdev->nocache)
		set_bit(NFS_DEVICEID_NOCACHE, &d->flags);

out_मुक्त_pages:
	क्रम (i = 0; i < max_pages; i++)
		__मुक्त_page(pages[i]);
	kमुक्त(pages);
out_मुक्त_pdev:
	kमुक्त(pdev);
	dprपूर्णांकk("<-- %s d %p\n", __func__, d);
	वापस d;
पूर्ण

/*
 * Lookup a deviceid in cache and get a reference count on it अगर found
 *
 * @clp nfs_client associated with deviceid
 * @id deviceid to look up
 */
अटल काष्ठा nfs4_deviceid_node *
__nfs4_find_get_deviceid(काष्ठा nfs_server *server,
		स्थिर काष्ठा nfs4_deviceid *id, दीर्घ hash)
अणु
	काष्ठा nfs4_deviceid_node *d;

	rcu_पढ़ो_lock();
	d = _lookup_deviceid(server->pnfs_curr_ld, server->nfs_client, id,
			hash);
	अगर (d != शून्य && !atomic_inc_not_zero(&d->ref))
		d = शून्य;
	rcu_पढ़ो_unlock();
	वापस d;
पूर्ण

काष्ठा nfs4_deviceid_node *
nfs4_find_get_deviceid(काष्ठा nfs_server *server,
		स्थिर काष्ठा nfs4_deviceid *id, स्थिर काष्ठा cred *cred,
		gfp_t gfp_mask)
अणु
	दीर्घ hash = nfs4_deviceid_hash(id);
	काष्ठा nfs4_deviceid_node *d, *new;

	d = __nfs4_find_get_deviceid(server, id, hash);
	अगर (d)
		जाओ found;

	new = nfs4_get_device_info(server, id, cred, gfp_mask);
	अगर (!new) अणु
		trace_nfs4_find_deviceid(server, id, -ENOENT);
		वापस new;
	पूर्ण

	spin_lock(&nfs4_deviceid_lock);
	d = __nfs4_find_get_deviceid(server, id, hash);
	अगर (d) अणु
		spin_unlock(&nfs4_deviceid_lock);
		server->pnfs_curr_ld->मुक्त_deviceid_node(new);
	पूर्ण अन्यथा अणु
		atomic_inc(&new->ref);
		hlist_add_head_rcu(&new->node, &nfs4_deviceid_cache[hash]);
		spin_unlock(&nfs4_deviceid_lock);
		d = new;
	पूर्ण
found:
	trace_nfs4_find_deviceid(server, id, 0);
	वापस d;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_find_get_deviceid);

/*
 * Remove a deviceid from cache
 *
 * @clp nfs_client associated with deviceid
 * @id the deviceid to unhash
 *
 * @ret the unhashed node, अगर found and dereferenced to zero, शून्य otherwise.
 */
व्योम
nfs4_delete_deviceid(स्थिर काष्ठा pnfs_layoutdriver_type *ld,
			 स्थिर काष्ठा nfs_client *clp, स्थिर काष्ठा nfs4_deviceid *id)
अणु
	काष्ठा nfs4_deviceid_node *d;

	spin_lock(&nfs4_deviceid_lock);
	rcu_पढ़ो_lock();
	d = _lookup_deviceid(ld, clp, id, nfs4_deviceid_hash(id));
	rcu_पढ़ो_unlock();
	अगर (!d) अणु
		spin_unlock(&nfs4_deviceid_lock);
		वापस;
	पूर्ण
	hlist_del_init_rcu(&d->node);
	clear_bit(NFS_DEVICEID_NOCACHE, &d->flags);
	spin_unlock(&nfs4_deviceid_lock);

	/* balance the initial ref set in pnfs_insert_deviceid */
	nfs4_put_deviceid_node(d);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_delete_deviceid);

व्योम
nfs4_init_deviceid_node(काष्ठा nfs4_deviceid_node *d, काष्ठा nfs_server *server,
			स्थिर काष्ठा nfs4_deviceid *id)
अणु
	INIT_HLIST_NODE(&d->node);
	INIT_HLIST_NODE(&d->पंचांगpnode);
	d->ld = server->pnfs_curr_ld;
	d->nfs_client = server->nfs_client;
	d->flags = 0;
	d->deviceid = *id;
	atomic_set(&d->ref, 1);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_init_deviceid_node);

/*
 * Dereference a deviceid node and delete it when its reference count drops
 * to zero.
 *
 * @d deviceid node to put
 *
 * वापस true अगरf the node was deleted
 * Note that since the test क्रम d->ref == 0 is sufficient to establish
 * that the node is no दीर्घer hashed in the global device id cache.
 */
bool
nfs4_put_deviceid_node(काष्ठा nfs4_deviceid_node *d)
अणु
	अगर (test_bit(NFS_DEVICEID_NOCACHE, &d->flags)) अणु
		अगर (atomic_add_unless(&d->ref, -1, 2))
			वापस false;
		nfs4_delete_deviceid(d->ld, d->nfs_client, &d->deviceid);
	पूर्ण
	अगर (!atomic_dec_and_test(&d->ref))
		वापस false;
	trace_nfs4_deviceid_मुक्त(d->nfs_client, &d->deviceid);
	d->ld->मुक्त_deviceid_node(d);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_put_deviceid_node);

व्योम
nfs4_mark_deviceid_available(काष्ठा nfs4_deviceid_node *node)
अणु
	अगर (test_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags)) अणु
		clear_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags);
		smp_mb__after_atomic();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_mark_deviceid_available);

व्योम
nfs4_mark_deviceid_unavailable(काष्ठा nfs4_deviceid_node *node)
अणु
	node->बारtamp_unavailable = jअगरfies;
	smp_mb__beक्रमe_atomic();
	set_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags);
	smp_mb__after_atomic();
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_mark_deviceid_unavailable);

bool
nfs4_test_deviceid_unavailable(काष्ठा nfs4_deviceid_node *node)
अणु
	अगर (test_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags)) अणु
		अचिन्हित दीर्घ start, end;

		end = jअगरfies;
		start = end - PNFS_DEVICE_RETRY_TIMEOUT;
		अगर (समय_in_range(node->बारtamp_unavailable, start, end))
			वापस true;
		clear_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags);
		smp_mb__after_atomic();
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_test_deviceid_unavailable);

अटल व्योम
_deviceid_purge_client(स्थिर काष्ठा nfs_client *clp, दीर्घ hash)
अणु
	काष्ठा nfs4_deviceid_node *d;
	HLIST_HEAD(पंचांगp);

	spin_lock(&nfs4_deviceid_lock);
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(d, &nfs4_deviceid_cache[hash], node)
		अगर (d->nfs_client == clp && atomic_पढ़ो(&d->ref)) अणु
			hlist_del_init_rcu(&d->node);
			hlist_add_head(&d->पंचांगpnode, &पंचांगp);
			clear_bit(NFS_DEVICEID_NOCACHE, &d->flags);
		पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock(&nfs4_deviceid_lock);

	अगर (hlist_empty(&पंचांगp))
		वापस;

	जबतक (!hlist_empty(&पंचांगp)) अणु
		d = hlist_entry(पंचांगp.first, काष्ठा nfs4_deviceid_node, पंचांगpnode);
		hlist_del(&d->पंचांगpnode);
		nfs4_put_deviceid_node(d);
	पूर्ण
पूर्ण

व्योम
nfs4_deviceid_purge_client(स्थिर काष्ठा nfs_client *clp)
अणु
	दीर्घ h;

	अगर (!(clp->cl_exchange_flags & EXCHGID4_FLAG_USE_PNFS_MDS))
		वापस;
	क्रम (h = 0; h < NFS4_DEVICE_ID_HASH_SIZE; h++)
		_deviceid_purge_client(clp, h);
पूर्ण

/*
 * Stop use of all deviceids associated with an nfs_client
 */
व्योम
nfs4_deviceid_mark_client_invalid(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs4_deviceid_node *d;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < NFS4_DEVICE_ID_HASH_SIZE; i ++)अणु
		hlist_क्रम_each_entry_rcu(d, &nfs4_deviceid_cache[i], node)
			अगर (d->nfs_client == clp)
				set_bit(NFS_DEVICEID_INVALID, &d->flags);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
