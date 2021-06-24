<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device operations क्रम the pnfs nfs4 file layout driver.
 *
 * Copyright (c) 2014, Primary Data, Inc. All rights reserved.
 *
 * Tao Peng <bergwolf@primarydata.com>
 */

#समावेश <linux/nfs_fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/sunrpc/addr.h>

#समावेश "../internal.h"
#समावेश "../nfs4session.h"
#समावेश "flexfilelayout.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PNFS_LD

अटल अचिन्हित पूर्णांक dataserver_समयo = NFS_DEF_TCP_TIMEO;
अटल अचिन्हित पूर्णांक dataserver_retrans;

अटल bool ff_layout_has_available_ds(काष्ठा pnfs_layout_segment *lseg);

व्योम nfs4_ff_layout_put_deviceid(काष्ठा nfs4_ff_layout_ds *mirror_ds)
अणु
	अगर (!IS_ERR_OR_शून्य(mirror_ds))
		nfs4_put_deviceid_node(&mirror_ds->id_node);
पूर्ण

व्योम nfs4_ff_layout_मुक्त_deviceid(काष्ठा nfs4_ff_layout_ds *mirror_ds)
अणु
	nfs4_prपूर्णांक_deviceid(&mirror_ds->id_node.deviceid);
	nfs4_pnfs_ds_put(mirror_ds->ds);
	kमुक्त(mirror_ds->ds_versions);
	kमुक्त_rcu(mirror_ds, id_node.rcu);
पूर्ण

/* Decode opaque device data and स्थिरruct new_ds using it */
काष्ठा nfs4_ff_layout_ds *
nfs4_ff_alloc_deviceid_node(काष्ठा nfs_server *server, काष्ठा pnfs_device *pdev,
			    gfp_t gfp_flags)
अणु
	काष्ठा xdr_stream stream;
	काष्ठा xdr_buf buf;
	काष्ठा page *scratch;
	काष्ठा list_head dsaddrs;
	काष्ठा nfs4_pnfs_ds_addr *da;
	काष्ठा nfs4_ff_layout_ds *new_ds = शून्य;
	काष्ठा nfs4_ff_ds_version *ds_versions = शून्य;
	u32 mp_count;
	u32 version_count;
	__be32 *p;
	पूर्णांक i, ret = -ENOMEM;

	/* set up xdr stream */
	scratch = alloc_page(gfp_flags);
	अगर (!scratch)
		जाओ out_err;

	new_ds = kzalloc(माप(काष्ठा nfs4_ff_layout_ds), gfp_flags);
	अगर (!new_ds)
		जाओ out_scratch;

	nfs4_init_deviceid_node(&new_ds->id_node,
				server,
				&pdev->dev_id);
	INIT_LIST_HEAD(&dsaddrs);

	xdr_init_decode_pages(&stream, &buf, pdev->pages, pdev->pglen);
	xdr_set_scratch_page(&stream, scratch);

	/* multipath count */
	p = xdr_अंतरभूत_decode(&stream, 4);
	अगर (unlikely(!p))
		जाओ out_err_drain_dsaddrs;
	mp_count = be32_to_cpup(p);
	dprपूर्णांकk("%s: multipath ds count %d\n", __func__, mp_count);

	क्रम (i = 0; i < mp_count; i++) अणु
		/* multipath ds */
		da = nfs4_decode_mp_ds_addr(server->nfs_client->cl_net,
					    &stream, gfp_flags);
		अगर (da)
			list_add_tail(&da->da_node, &dsaddrs);
	पूर्ण
	अगर (list_empty(&dsaddrs)) अणु
		dprपूर्णांकk("%s: no suitable DS addresses found\n",
			__func__);
		ret = -ENOMEDIUM;
		जाओ out_err_drain_dsaddrs;
	पूर्ण

	/* version count */
	p = xdr_अंतरभूत_decode(&stream, 4);
	अगर (unlikely(!p))
		जाओ out_err_drain_dsaddrs;
	version_count = be32_to_cpup(p);
	dprपूर्णांकk("%s: version count %d\n", __func__, version_count);

	ds_versions = kसुस्मृति(version_count,
			      माप(काष्ठा nfs4_ff_ds_version),
			      gfp_flags);
	अगर (!ds_versions)
		जाओ out_scratch;

	क्रम (i = 0; i < version_count; i++) अणु
		/* 20 = version(4) + minor_version(4) + rsize(4) + wsize(4) +
		 * tightly_coupled(4) */
		p = xdr_अंतरभूत_decode(&stream, 20);
		अगर (unlikely(!p))
			जाओ out_err_drain_dsaddrs;
		ds_versions[i].version = be32_to_cpup(p++);
		ds_versions[i].minor_version = be32_to_cpup(p++);
		ds_versions[i].rsize = nfs_block_size(be32_to_cpup(p++), शून्य);
		ds_versions[i].wsize = nfs_block_size(be32_to_cpup(p++), शून्य);
		ds_versions[i].tightly_coupled = be32_to_cpup(p);

		अगर (ds_versions[i].rsize > NFS_MAX_खाता_IO_SIZE)
			ds_versions[i].rsize = NFS_MAX_खाता_IO_SIZE;
		अगर (ds_versions[i].wsize > NFS_MAX_खाता_IO_SIZE)
			ds_versions[i].wsize = NFS_MAX_खाता_IO_SIZE;

		/*
		 * check क्रम valid major/minor combination.
		 * currently we support dataserver which talk:
		 *   v3, v4.0, v4.1, v4.2
		 */
		अगर (!((ds_versions[i].version == 3 && ds_versions[i].minor_version == 0) ||
			(ds_versions[i].version == 4 && ds_versions[i].minor_version < 3))) अणु
			dprपूर्णांकk("%s: [%d] unsupported ds version %d-%d\n", __func__,
				i, ds_versions[i].version,
				ds_versions[i].minor_version);
			ret = -EPROTONOSUPPORT;
			जाओ out_err_drain_dsaddrs;
		पूर्ण

		dprपूर्णांकk("%s: [%d] vers %u minor_ver %u rsize %u wsize %u coupled %d\n",
			__func__, i, ds_versions[i].version,
			ds_versions[i].minor_version,
			ds_versions[i].rsize,
			ds_versions[i].wsize,
			ds_versions[i].tightly_coupled);
	पूर्ण

	new_ds->ds_versions = ds_versions;
	new_ds->ds_versions_cnt = version_count;

	new_ds->ds = nfs4_pnfs_ds_add(&dsaddrs, gfp_flags);
	अगर (!new_ds->ds)
		जाओ out_err_drain_dsaddrs;

	/* If DS was alपढ़ोy in cache, मुक्त ds addrs */
	जबतक (!list_empty(&dsaddrs)) अणु
		da = list_first_entry(&dsaddrs,
				      काष्ठा nfs4_pnfs_ds_addr,
				      da_node);
		list_del_init(&da->da_node);
		kमुक्त(da->da_remotestr);
		kमुक्त(da);
	पूर्ण

	__मुक्त_page(scratch);
	वापस new_ds;

out_err_drain_dsaddrs:
	जबतक (!list_empty(&dsaddrs)) अणु
		da = list_first_entry(&dsaddrs, काष्ठा nfs4_pnfs_ds_addr,
				      da_node);
		list_del_init(&da->da_node);
		kमुक्त(da->da_remotestr);
		kमुक्त(da);
	पूर्ण

	kमुक्त(ds_versions);
out_scratch:
	__मुक्त_page(scratch);
out_err:
	kमुक्त(new_ds);

	dprपूर्णांकk("%s ERROR: returning %d\n", __func__, ret);
	वापस शून्य;
पूर्ण

अटल व्योम extend_ds_error(काष्ठा nfs4_ff_layout_ds_err *err,
			    u64 offset, u64 length)
अणु
	u64 end;

	end = max_t(u64, pnfs_end_offset(err->offset, err->length),
		    pnfs_end_offset(offset, length));
	err->offset = min_t(u64, err->offset, offset);
	err->length = end - err->offset;
पूर्ण

अटल पूर्णांक
ff_ds_error_match(स्थिर काष्ठा nfs4_ff_layout_ds_err *e1,
		स्थिर काष्ठा nfs4_ff_layout_ds_err *e2)
अणु
	पूर्णांक ret;

	अगर (e1->opnum != e2->opnum)
		वापस e1->opnum < e2->opnum ? -1 : 1;
	अगर (e1->status != e2->status)
		वापस e1->status < e2->status ? -1 : 1;
	ret = स_भेद(e1->stateid.data, e2->stateid.data,
			माप(e1->stateid.data));
	अगर (ret != 0)
		वापस ret;
	ret = स_भेद(&e1->deviceid, &e2->deviceid, माप(e1->deviceid));
	अगर (ret != 0)
		वापस ret;
	अगर (pnfs_end_offset(e1->offset, e1->length) < e2->offset)
		वापस -1;
	अगर (e1->offset > pnfs_end_offset(e2->offset, e2->length))
		वापस 1;
	/* If ranges overlap or are contiguous, they are the same */
	वापस 0;
पूर्ण

अटल व्योम
ff_layout_add_ds_error_locked(काष्ठा nfs4_flexfile_layout *flo,
			      काष्ठा nfs4_ff_layout_ds_err *dserr)
अणु
	काष्ठा nfs4_ff_layout_ds_err *err, *पंचांगp;
	काष्ठा list_head *head = &flo->error_list;
	पूर्णांक match;

	/* Do insertion sort w/ merges */
	list_क्रम_each_entry_safe(err, पंचांगp, &flo->error_list, list) अणु
		match = ff_ds_error_match(err, dserr);
		अगर (match < 0)
			जारी;
		अगर (match > 0) अणु
			/* Add entry "dserr" _beक्रमe_ entry "err" */
			head = &err->list;
			अवरोध;
		पूर्ण
		/* Entries match, so merge "err" पूर्णांकo "dserr" */
		extend_ds_error(dserr, err->offset, err->length);
		list_replace(&err->list, &dserr->list);
		kमुक्त(err);
		वापस;
	पूर्ण

	list_add_tail(&dserr->list, head);
पूर्ण

पूर्णांक ff_layout_track_ds_error(काष्ठा nfs4_flexfile_layout *flo,
			     काष्ठा nfs4_ff_layout_mirror *mirror, u64 offset,
			     u64 length, पूर्णांक status, क्रमागत nfs_opnum4 opnum,
			     gfp_t gfp_flags)
अणु
	काष्ठा nfs4_ff_layout_ds_err *dserr;

	अगर (status == 0)
		वापस 0;

	अगर (IS_ERR_OR_शून्य(mirror->mirror_ds))
		वापस -EINVAL;

	dserr = kदो_स्मृति(माप(*dserr), gfp_flags);
	अगर (!dserr)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dserr->list);
	dserr->offset = offset;
	dserr->length = length;
	dserr->status = status;
	dserr->opnum = opnum;
	nfs4_stateid_copy(&dserr->stateid, &mirror->stateid);
	स_नकल(&dserr->deviceid, &mirror->mirror_ds->id_node.deviceid,
	       NFS4_DEVICEID4_SIZE);

	spin_lock(&flo->generic_hdr.plh_inode->i_lock);
	ff_layout_add_ds_error_locked(flo, dserr);
	spin_unlock(&flo->generic_hdr.plh_inode->i_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cred *
ff_layout_get_mirror_cred(काष्ठा nfs4_ff_layout_mirror *mirror, u32 iomode)
अणु
	स्थिर काष्ठा cred *cred, __rcu **pcred;

	अगर (iomode == IOMODE_READ)
		pcred = &mirror->ro_cred;
	अन्यथा
		pcred = &mirror->rw_cred;

	rcu_पढ़ो_lock();
	करो अणु
		cred = rcu_dereference(*pcred);
		अगर (!cred)
			अवरोध;

		cred = get_cred_rcu(cred);
	पूर्ण जबतक(!cred);
	rcu_पढ़ो_unlock();
	वापस cred;
पूर्ण

काष्ठा nfs_fh *
nfs4_ff_layout_select_ds_fh(काष्ठा nfs4_ff_layout_mirror *mirror)
अणु
	/* FIXME: For now assume there is only 1 version available क्रम the DS */
	वापस &mirror->fh_versions[0];
पूर्ण

व्योम
nfs4_ff_layout_select_ds_stateid(स्थिर काष्ठा nfs4_ff_layout_mirror *mirror,
		nfs4_stateid *stateid)
अणु
	अगर (nfs4_ff_layout_ds_version(mirror) == 4)
		nfs4_stateid_copy(stateid, &mirror->stateid);
पूर्ण

अटल bool
ff_layout_init_mirror_ds(काष्ठा pnfs_layout_hdr *lo,
			 काष्ठा nfs4_ff_layout_mirror *mirror)
अणु
	अगर (mirror == शून्य)
		जाओ outerr;
	अगर (mirror->mirror_ds == शून्य) अणु
		काष्ठा nfs4_deviceid_node *node;
		काष्ठा nfs4_ff_layout_ds *mirror_ds = ERR_PTR(-ENODEV);

		node = nfs4_find_get_deviceid(NFS_SERVER(lo->plh_inode),
				&mirror->devid, lo->plh_lc_cred,
				GFP_KERNEL);
		अगर (node)
			mirror_ds = FF_LAYOUT_MIRROR_DS(node);

		/* check क्रम race with another call to this function */
		अगर (cmpxchg(&mirror->mirror_ds, शून्य, mirror_ds) &&
		    mirror_ds != ERR_PTR(-ENODEV))
			nfs4_put_deviceid_node(node);
	पूर्ण

	अगर (IS_ERR(mirror->mirror_ds))
		जाओ outerr;

	वापस true;
outerr:
	वापस false;
पूर्ण

/**
 * nfs4_ff_layout_prepare_ds - prepare a DS connection क्रम an RPC call
 * @lseg: the layout segment we're operating on
 * @mirror: layout mirror describing the DS to use
 * @fail_वापस: वापस layout on connect failure?
 *
 * Try to prepare a DS connection to accept an RPC call. This involves
 * selecting a mirror to use and connecting the client to it अगर it's not
 * alपढ़ोy connected.
 *
 * Since we only need a single functioning mirror to satisfy a पढ़ो, we करोn't
 * want to वापस the layout अगर there is one. For ग_लिखोs though, any करोwn
 * mirror should result in a LAYOUTRETURN. @fail_वापस is how we distinguish
 * between the two हालs.
 *
 * Returns a poपूर्णांकer to a connected DS object on success or शून्य on failure.
 */
काष्ठा nfs4_pnfs_ds *
nfs4_ff_layout_prepare_ds(काष्ठा pnfs_layout_segment *lseg,
			  काष्ठा nfs4_ff_layout_mirror *mirror,
			  bool fail_वापस)
अणु
	काष्ठा nfs4_pnfs_ds *ds = शून्य;
	काष्ठा inode *ino = lseg->pls_layout->plh_inode;
	काष्ठा nfs_server *s = NFS_SERVER(ino);
	अचिन्हित पूर्णांक max_payload;
	पूर्णांक status;

	अगर (!ff_layout_init_mirror_ds(lseg->pls_layout, mirror))
		जाओ noconnect;

	ds = mirror->mirror_ds->ds;
	/* matching smp_wmb() in _nfs4_pnfs_v3/4_ds_connect */
	smp_rmb();
	अगर (ds->ds_clp)
		जाओ out;

	/* FIXME: For now we assume the server sent only one version of NFS
	 * to use क्रम the DS.
	 */
	status = nfs4_pnfs_ds_connect(s, ds, &mirror->mirror_ds->id_node,
			     dataserver_समयo, dataserver_retrans,
			     mirror->mirror_ds->ds_versions[0].version,
			     mirror->mirror_ds->ds_versions[0].minor_version);

	/* connect success, check rsize/wsize limit */
	अगर (!status) अणु
		max_payload =
			nfs_block_size(rpc_max_payload(ds->ds_clp->cl_rpcclient),
				       शून्य);
		अगर (mirror->mirror_ds->ds_versions[0].rsize > max_payload)
			mirror->mirror_ds->ds_versions[0].rsize = max_payload;
		अगर (mirror->mirror_ds->ds_versions[0].wsize > max_payload)
			mirror->mirror_ds->ds_versions[0].wsize = max_payload;
		जाओ out;
	पूर्ण
noconnect:
	ff_layout_track_ds_error(FF_LAYOUT_FROM_HDR(lseg->pls_layout),
				 mirror, lseg->pls_range.offset,
				 lseg->pls_range.length, NFS4ERR_NXIO,
				 OP_ILLEGAL, GFP_NOIO);
	ff_layout_send_layouterror(lseg);
	अगर (fail_वापस || !ff_layout_has_available_ds(lseg))
		pnfs_error_mark_layout_क्रम_वापस(ino, lseg);
	ds = शून्य;
out:
	वापस ds;
पूर्ण

स्थिर काष्ठा cred *
ff_layout_get_ds_cred(काष्ठा nfs4_ff_layout_mirror *mirror,
		      स्थिर काष्ठा pnfs_layout_range *range,
		      स्थिर काष्ठा cred *mdscred)
अणु
	स्थिर काष्ठा cred *cred;

	अगर (mirror && !mirror->mirror_ds->ds_versions[0].tightly_coupled) अणु
		cred = ff_layout_get_mirror_cred(mirror, range->iomode);
		अगर (!cred)
			cred = get_cred(mdscred);
	पूर्ण अन्यथा अणु
		cred = get_cred(mdscred);
	पूर्ण
	वापस cred;
पूर्ण

/**
 * nfs4_ff_find_or_create_ds_client - Find or create a DS rpc client
 * @mirror: poपूर्णांकer to the mirror
 * @ds_clp: nfs_client क्रम the DS
 * @inode: poपूर्णांकer to inode
 *
 * Find or create a DS rpc client with th MDS server rpc client auth flavor
 * in the nfs_client cl_ds_clients list.
 */
काष्ठा rpc_clnt *
nfs4_ff_find_or_create_ds_client(काष्ठा nfs4_ff_layout_mirror *mirror,
				 काष्ठा nfs_client *ds_clp, काष्ठा inode *inode)
अणु
	चयन (mirror->mirror_ds->ds_versions[0].version) अणु
	हाल 3:
		/* For NFSv3 DS, flavor is set when creating DS connections */
		वापस ds_clp->cl_rpcclient;
	हाल 4:
		वापस nfs4_find_or_create_ds_client(ds_clp, inode);
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम ff_layout_मुक्त_ds_ioerr(काष्ठा list_head *head)
अणु
	काष्ठा nfs4_ff_layout_ds_err *err;

	जबतक (!list_empty(head)) अणु
		err = list_first_entry(head,
				काष्ठा nfs4_ff_layout_ds_err,
				list);
		list_del(&err->list);
		kमुक्त(err);
	पूर्ण
पूर्ण

/* called with inode i_lock held */
पूर्णांक ff_layout_encode_ds_ioerr(काष्ठा xdr_stream *xdr, स्थिर काष्ठा list_head *head)
अणु
	काष्ठा nfs4_ff_layout_ds_err *err;
	__be32 *p;

	list_क्रम_each_entry(err, head, list) अणु
		/* offset(8) + length(8) + stateid(NFS4_STATEID_SIZE)
		 * + array length + deviceid(NFS4_DEVICEID4_SIZE)
		 * + status(4) + opnum(4)
		 */
		p = xdr_reserve_space(xdr,
				28 + NFS4_STATEID_SIZE + NFS4_DEVICEID4_SIZE);
		अगर (unlikely(!p))
			वापस -ENOBUFS;
		p = xdr_encode_hyper(p, err->offset);
		p = xdr_encode_hyper(p, err->length);
		p = xdr_encode_opaque_fixed(p, &err->stateid,
					    NFS4_STATEID_SIZE);
		/* Encode 1 error */
		*p++ = cpu_to_be32(1);
		p = xdr_encode_opaque_fixed(p, &err->deviceid,
					    NFS4_DEVICEID4_SIZE);
		*p++ = cpu_to_be32(err->status);
		*p++ = cpu_to_be32(err->opnum);
		dprपूर्णांकk("%s: offset %llu length %llu status %d op %d\n",
			__func__, err->offset, err->length, err->status,
			err->opnum);
	पूर्ण

	वापस 0;
पूर्ण

अटल
अचिन्हित पूर्णांक करो_layout_fetch_ds_ioerr(काष्ठा pnfs_layout_hdr *lo,
				      स्थिर काष्ठा pnfs_layout_range *range,
				      काष्ठा list_head *head,
				      अचिन्हित पूर्णांक maxnum)
अणु
	काष्ठा nfs4_flexfile_layout *flo = FF_LAYOUT_FROM_HDR(lo);
	काष्ठा inode *inode = lo->plh_inode;
	काष्ठा nfs4_ff_layout_ds_err *err, *n;
	अचिन्हित पूर्णांक ret = 0;

	spin_lock(&inode->i_lock);
	list_क्रम_each_entry_safe(err, n, &flo->error_list, list) अणु
		अगर (!pnfs_is_range_पूर्णांकersecting(err->offset,
				pnfs_end_offset(err->offset, err->length),
				range->offset,
				pnfs_end_offset(range->offset, range->length)))
			जारी;
		अगर (!maxnum)
			अवरोध;
		list_move(&err->list, head);
		maxnum--;
		ret++;
	पूर्ण
	spin_unlock(&inode->i_lock);
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक ff_layout_fetch_ds_ioerr(काष्ठा pnfs_layout_hdr *lo,
				      स्थिर काष्ठा pnfs_layout_range *range,
				      काष्ठा list_head *head,
				      अचिन्हित पूर्णांक maxnum)
अणु
	अचिन्हित पूर्णांक ret;

	ret = करो_layout_fetch_ds_ioerr(lo, range, head, maxnum);
	/* If we're over the max, discard all reमुख्यing entries */
	अगर (ret == maxnum) अणु
		LIST_HEAD(discard);
		करो_layout_fetch_ds_ioerr(lo, range, &discard, -1);
		ff_layout_मुक्त_ds_ioerr(&discard);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool ff_पढ़ो_layout_has_available_ds(काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा nfs4_ff_layout_mirror *mirror;
	काष्ठा nfs4_deviceid_node *devid;
	u32 idx;

	क्रम (idx = 0; idx < FF_LAYOUT_MIRROR_COUNT(lseg); idx++) अणु
		mirror = FF_LAYOUT_COMP(lseg, idx);
		अगर (mirror) अणु
			अगर (!mirror->mirror_ds)
				वापस true;
			अगर (IS_ERR(mirror->mirror_ds))
				जारी;
			devid = &mirror->mirror_ds->id_node;
			अगर (!nfs4_test_deviceid_unavailable(devid))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool ff_rw_layout_has_available_ds(काष्ठा pnfs_layout_segment *lseg)
अणु
	काष्ठा nfs4_ff_layout_mirror *mirror;
	काष्ठा nfs4_deviceid_node *devid;
	u32 idx;

	क्रम (idx = 0; idx < FF_LAYOUT_MIRROR_COUNT(lseg); idx++) अणु
		mirror = FF_LAYOUT_COMP(lseg, idx);
		अगर (!mirror || IS_ERR(mirror->mirror_ds))
			वापस false;
		अगर (!mirror->mirror_ds)
			जारी;
		devid = &mirror->mirror_ds->id_node;
		अगर (nfs4_test_deviceid_unavailable(devid))
			वापस false;
	पूर्ण

	वापस FF_LAYOUT_MIRROR_COUNT(lseg) != 0;
पूर्ण

अटल bool ff_layout_has_available_ds(काष्ठा pnfs_layout_segment *lseg)
अणु
	अगर (lseg->pls_range.iomode == IOMODE_READ)
		वापस  ff_पढ़ो_layout_has_available_ds(lseg);
	/* Note: RW layout needs all mirrors available */
	वापस ff_rw_layout_has_available_ds(lseg);
पूर्ण

bool ff_layout_aव्योम_mds_available_ds(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस ff_layout_no_fallback_to_mds(lseg) ||
	       ff_layout_has_available_ds(lseg);
पूर्ण

bool ff_layout_aव्योम_पढ़ो_on_rw(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस lseg->pls_range.iomode == IOMODE_RW &&
	       ff_layout_no_पढ़ो_on_rw(lseg);
पूर्ण

module_param(dataserver_retrans, uपूर्णांक, 0644);
MODULE_PARM_DESC(dataserver_retrans, "The  number of times the NFSv4.1 client "
			"retries a request before it attempts further "
			" recovery  action.");
module_param(dataserver_समयo, uपूर्णांक, 0644);
MODULE_PARM_DESC(dataserver_समयo, "The time (in tenths of a second) the "
			"NFSv4.1  client  waits for a response from a "
			" data server before it retries an NFS request.");
