<शैली गुरु>
/*
 *  Device operations क्रम the pnfs nfs4 file layout driver.
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

#समावेश <linux/nfs_fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>

#समावेश "../internal.h"
#समावेश "../nfs4session.h"
#समावेश "filelayout.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PNFS_LD

अटल अचिन्हित पूर्णांक dataserver_समयo = NFS4_DEF_DS_TIMEO;
अटल अचिन्हित पूर्णांक dataserver_retrans = NFS4_DEF_DS_RETRANS;

व्योम
nfs4_fl_मुक्त_deviceid(काष्ठा nfs4_file_layout_dsaddr *dsaddr)
अणु
	काष्ठा nfs4_pnfs_ds *ds;
	पूर्णांक i;

	nfs4_prपूर्णांक_deviceid(&dsaddr->id_node.deviceid);

	क्रम (i = 0; i < dsaddr->ds_num; i++) अणु
		ds = dsaddr->ds_list[i];
		अगर (ds != शून्य)
			nfs4_pnfs_ds_put(ds);
	पूर्ण
	kमुक्त(dsaddr->stripe_indices);
	kमुक्त_rcu(dsaddr, id_node.rcu);
पूर्ण

/* Decode opaque device data and वापस the result */
काष्ठा nfs4_file_layout_dsaddr *
nfs4_fl_alloc_deviceid_node(काष्ठा nfs_server *server, काष्ठा pnfs_device *pdev,
		gfp_t gfp_flags)
अणु
	पूर्णांक i;
	u32 cnt, num;
	u8 *indexp;
	__be32 *p;
	u8 *stripe_indices;
	u8 max_stripe_index;
	काष्ठा nfs4_file_layout_dsaddr *dsaddr = शून्य;
	काष्ठा xdr_stream stream;
	काष्ठा xdr_buf buf;
	काष्ठा page *scratch;
	काष्ठा list_head dsaddrs;
	काष्ठा nfs4_pnfs_ds_addr *da;

	/* set up xdr stream */
	scratch = alloc_page(gfp_flags);
	अगर (!scratch)
		जाओ out_err;

	xdr_init_decode_pages(&stream, &buf, pdev->pages, pdev->pglen);
	xdr_set_scratch_page(&stream, scratch);

	/* Get the stripe count (number of stripe index) */
	p = xdr_अंतरभूत_decode(&stream, 4);
	अगर (unlikely(!p))
		जाओ out_err_मुक्त_scratch;

	cnt = be32_to_cpup(p);
	dprपूर्णांकk("%s stripe count  %d\n", __func__, cnt);
	अगर (cnt > NFS4_PNFS_MAX_STRIPE_CNT) अणु
		prपूर्णांकk(KERN_WARNING "NFS: %s: stripe count %d greater than "
		       "supported maximum %d\n", __func__,
			cnt, NFS4_PNFS_MAX_STRIPE_CNT);
		जाओ out_err_मुक्त_scratch;
	पूर्ण

	/* पढ़ो stripe indices */
	stripe_indices = kसुस्मृति(cnt, माप(u8), gfp_flags);
	अगर (!stripe_indices)
		जाओ out_err_मुक्त_scratch;

	p = xdr_अंतरभूत_decode(&stream, cnt << 2);
	अगर (unlikely(!p))
		जाओ out_err_मुक्त_stripe_indices;

	indexp = &stripe_indices[0];
	max_stripe_index = 0;
	क्रम (i = 0; i < cnt; i++) अणु
		*indexp = be32_to_cpup(p++);
		max_stripe_index = max(max_stripe_index, *indexp);
		indexp++;
	पूर्ण

	/* Check the multipath list count */
	p = xdr_अंतरभूत_decode(&stream, 4);
	अगर (unlikely(!p))
		जाओ out_err_मुक्त_stripe_indices;

	num = be32_to_cpup(p);
	dprपूर्णांकk("%s ds_num %u\n", __func__, num);
	अगर (num > NFS4_PNFS_MAX_MULTI_CNT) अणु
		prपूर्णांकk(KERN_WARNING "NFS: %s: multipath count %d greater than "
			"supported maximum %d\n", __func__,
			num, NFS4_PNFS_MAX_MULTI_CNT);
		जाओ out_err_मुक्त_stripe_indices;
	पूर्ण

	/* validate stripe indices are all < num */
	अगर (max_stripe_index >= num) अणु
		prपूर्णांकk(KERN_WARNING "NFS: %s: stripe index %u >= num ds %u\n",
			__func__, max_stripe_index, num);
		जाओ out_err_मुक्त_stripe_indices;
	पूर्ण

	dsaddr = kzalloc(माप(*dsaddr) +
			(माप(काष्ठा nfs4_pnfs_ds *) * (num - 1)),
			gfp_flags);
	अगर (!dsaddr)
		जाओ out_err_मुक्त_stripe_indices;

	dsaddr->stripe_count = cnt;
	dsaddr->stripe_indices = stripe_indices;
	stripe_indices = शून्य;
	dsaddr->ds_num = num;
	nfs4_init_deviceid_node(&dsaddr->id_node, server, &pdev->dev_id);

	INIT_LIST_HEAD(&dsaddrs);

	क्रम (i = 0; i < dsaddr->ds_num; i++) अणु
		पूर्णांक j;
		u32 mp_count;

		p = xdr_अंतरभूत_decode(&stream, 4);
		अगर (unlikely(!p))
			जाओ out_err_मुक्त_deviceid;

		mp_count = be32_to_cpup(p); /* multipath count */
		क्रम (j = 0; j < mp_count; j++) अणु
			da = nfs4_decode_mp_ds_addr(server->nfs_client->cl_net,
						    &stream, gfp_flags);
			अगर (da)
				list_add_tail(&da->da_node, &dsaddrs);
		पूर्ण
		अगर (list_empty(&dsaddrs)) अणु
			dprपूर्णांकk("%s: no suitable DS addresses found\n",
				__func__);
			जाओ out_err_मुक्त_deviceid;
		पूर्ण

		dsaddr->ds_list[i] = nfs4_pnfs_ds_add(&dsaddrs, gfp_flags);
		अगर (!dsaddr->ds_list[i])
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
	पूर्ण

	__मुक्त_page(scratch);
	वापस dsaddr;

out_err_drain_dsaddrs:
	जबतक (!list_empty(&dsaddrs)) अणु
		da = list_first_entry(&dsaddrs, काष्ठा nfs4_pnfs_ds_addr,
				      da_node);
		list_del_init(&da->da_node);
		kमुक्त(da->da_remotestr);
		kमुक्त(da);
	पूर्ण
out_err_मुक्त_deviceid:
	nfs4_fl_मुक्त_deviceid(dsaddr);
	/* stripe_indicies was part of dsaddr */
	जाओ out_err_मुक्त_scratch;
out_err_मुक्त_stripe_indices:
	kमुक्त(stripe_indices);
out_err_मुक्त_scratch:
	__मुक्त_page(scratch);
out_err:
	dprपूर्णांकk("%s ERROR: returning NULL\n", __func__);
	वापस शून्य;
पूर्ण

व्योम
nfs4_fl_put_deviceid(काष्ठा nfs4_file_layout_dsaddr *dsaddr)
अणु
	nfs4_put_deviceid_node(&dsaddr->id_node);
पूर्ण

/*
 * Want res = (offset - layout->pattern_offset)/ layout->stripe_unit
 * Then: ((res + fsi) % dsaddr->stripe_count)
 */
u32
nfs4_fl_calc_j_index(काष्ठा pnfs_layout_segment *lseg, loff_t offset)
अणु
	काष्ठा nfs4_filelayout_segment *flseg = खाताLAYOUT_LSEG(lseg);
	u64 पंचांगp;

	पंचांगp = offset - flseg->pattern_offset;
	करो_भाग(पंचांगp, flseg->stripe_unit);
	पंचांगp += flseg->first_stripe_index;
	वापस करो_भाग(पंचांगp, flseg->dsaddr->stripe_count);
पूर्ण

u32
nfs4_fl_calc_ds_index(काष्ठा pnfs_layout_segment *lseg, u32 j)
अणु
	वापस खाताLAYOUT_LSEG(lseg)->dsaddr->stripe_indices[j];
पूर्ण

काष्ठा nfs_fh *
nfs4_fl_select_ds_fh(काष्ठा pnfs_layout_segment *lseg, u32 j)
अणु
	काष्ठा nfs4_filelayout_segment *flseg = खाताLAYOUT_LSEG(lseg);
	u32 i;

	अगर (flseg->stripe_type == STRIPE_SPARSE) अणु
		अगर (flseg->num_fh == 1)
			i = 0;
		अन्यथा अगर (flseg->num_fh == 0)
			/* Use the MDS OPEN fh set in nfs_पढ़ो_rpcsetup */
			वापस शून्य;
		अन्यथा
			i = nfs4_fl_calc_ds_index(lseg, j);
	पूर्ण अन्यथा
		i = j;
	वापस flseg->fh_array[i];
पूर्ण

/* Upon वापस, either ds is connected, or ds is शून्य */
काष्ठा nfs4_pnfs_ds *
nfs4_fl_prepare_ds(काष्ठा pnfs_layout_segment *lseg, u32 ds_idx)
अणु
	काष्ठा nfs4_file_layout_dsaddr *dsaddr = खाताLAYOUT_LSEG(lseg)->dsaddr;
	काष्ठा nfs4_pnfs_ds *ds = dsaddr->ds_list[ds_idx];
	काष्ठा nfs4_deviceid_node *devid = खाताLAYOUT_DEVID_NODE(lseg);
	काष्ठा nfs4_pnfs_ds *ret = ds;
	काष्ठा nfs_server *s = NFS_SERVER(lseg->pls_layout->plh_inode);
	पूर्णांक status;

	अगर (ds == शून्य) अणु
		prपूर्णांकk(KERN_ERR "NFS: %s: No data server for offset index %d\n",
			__func__, ds_idx);
		pnfs_generic_mark_devid_invalid(devid);
		जाओ out;
	पूर्ण
	smp_rmb();
	अगर (ds->ds_clp)
		जाओ out_test_devid;

	status = nfs4_pnfs_ds_connect(s, ds, devid, dataserver_समयo,
			     dataserver_retrans, 4,
			     s->nfs_client->cl_minorversion);
	अगर (status) अणु
		nfs4_mark_deviceid_unavailable(devid);
		ret = शून्य;
		जाओ out;
	पूर्ण

out_test_devid:
	अगर (ret->ds_clp == शून्य ||
	    filelayout_test_devid_unavailable(devid))
		ret = शून्य;
out:
	वापस ret;
पूर्ण

module_param(dataserver_retrans, uपूर्णांक, 0644);
MODULE_PARM_DESC(dataserver_retrans, "The  number of times the NFSv4.1 client "
			"retries a request before it attempts further "
			" recovery  action.");
module_param(dataserver_समयo, uपूर्णांक, 0644);
MODULE_PARM_DESC(dataserver_समयo, "The time (in tenths of a second) the "
			"NFSv4.1  client  waits for a response from a "
			" data server before it retries an NFS request.");
