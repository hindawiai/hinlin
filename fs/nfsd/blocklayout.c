<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014-2016 Christoph Hellwig.
 */
#समावेश <linux/exportfs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/genhd.h>
#समावेश <linux/slab.h>
#समावेश <linux/pr.h>

#समावेश <linux/nfsd/debug.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/scsi_common.h>
#समावेश <scsi/scsi_request.h>

#समावेश "blocklayoutxdr.h"
#समावेश "pnfs.h"
#समावेश "filecache.h"

#घोषणा NFSDDBG_FACILITY	NFSDDBG_PNFS


अटल __be32
nfsd4_block_proc_layoutget(काष्ठा inode *inode, स्थिर काष्ठा svc_fh *fhp,
		काष्ठा nfsd4_layoutget *args)
अणु
	काष्ठा nfsd4_layout_seg *seg = &args->lg_seg;
	काष्ठा super_block *sb = inode->i_sb;
	u32 block_size = i_blocksize(inode);
	काष्ठा pnfs_block_extent *bex;
	काष्ठा iomap iomap;
	u32 device_generation = 0;
	पूर्णांक error;

	अगर (seg->offset & (block_size - 1)) अणु
		dprपूर्णांकk("pnfsd: I/O misaligned\n");
		जाओ out_layoutunavailable;
	पूर्ण

	/*
	 * Some clients barf on non-zero block numbers क्रम NONE or INVALID
	 * layouts, so make sure to zero the whole काष्ठाure.
	 */
	error = -ENOMEM;
	bex = kzalloc(माप(*bex), GFP_KERNEL);
	अगर (!bex)
		जाओ out_error;
	args->lg_content = bex;

	error = sb->s_export_op->map_blocks(inode, seg->offset, seg->length,
					    &iomap, seg->iomode != IOMODE_READ,
					    &device_generation);
	अगर (error) अणु
		अगर (error == -ENXIO)
			जाओ out_layoutunavailable;
		जाओ out_error;
	पूर्ण

	अगर (iomap.length < args->lg_minlength) अणु
		dprपूर्णांकk("pnfsd: extent smaller than minlength\n");
		जाओ out_layoutunavailable;
	पूर्ण

	चयन (iomap.type) अणु
	हाल IOMAP_MAPPED:
		अगर (seg->iomode == IOMODE_READ)
			bex->es = PNFS_BLOCK_READ_DATA;
		अन्यथा
			bex->es = PNFS_BLOCK_READWRITE_DATA;
		bex->soff = iomap.addr;
		अवरोध;
	हाल IOMAP_UNWRITTEN:
		अगर (seg->iomode & IOMODE_RW) अणु
			/*
			 * Crack monkey special हाल from section 2.3.1.
			 */
			अगर (args->lg_minlength == 0) अणु
				dprपूर्णांकk("pnfsd: no soup for you!\n");
				जाओ out_layoutunavailable;
			पूर्ण

			bex->es = PNFS_BLOCK_INVALID_DATA;
			bex->soff = iomap.addr;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल IOMAP_HOLE:
		अगर (seg->iomode == IOMODE_READ) अणु
			bex->es = PNFS_BLOCK_NONE_DATA;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल IOMAP_DELALLOC:
	शेष:
		WARN(1, "pnfsd: filesystem returned %d extent\n", iomap.type);
		जाओ out_layoutunavailable;
	पूर्ण

	error = nfsd4_set_deviceid(&bex->vol_id, fhp, device_generation);
	अगर (error)
		जाओ out_error;
	bex->foff = iomap.offset;
	bex->len = iomap.length;

	seg->offset = iomap.offset;
	seg->length = iomap.length;

	dprपूर्णांकk("GET: 0x%llx:0x%llx %d\n", bex->foff, bex->len, bex->es);
	वापस 0;

out_error:
	seg->length = 0;
	वापस nfsत्रुटि_सं(error);
out_layoutunavailable:
	seg->length = 0;
	वापस nfserr_layoutunavailable;
पूर्ण

अटल __be32
nfsd4_block_commit_blocks(काष्ठा inode *inode, काष्ठा nfsd4_layoutcommit *lcp,
		काष्ठा iomap *iomaps, पूर्णांक nr_iomaps)
अणु
	loff_t new_size = lcp->lc_last_wr + 1;
	काष्ठा iattr iattr = अणु .ia_valid = 0 पूर्ण;
	पूर्णांक error;

	अगर (lcp->lc_mसमय.tv_nsec == UTIME_NOW ||
	    बारpec64_compare(&lcp->lc_mसमय, &inode->i_mसमय) < 0)
		lcp->lc_mसमय = current_समय(inode);
	iattr.ia_valid |= ATTR_ATIME | ATTR_CTIME | ATTR_MTIME;
	iattr.ia_aसमय = iattr.ia_स_समय = iattr.ia_mसमय = lcp->lc_mसमय;

	अगर (new_size > i_size_पढ़ो(inode)) अणु
		iattr.ia_valid |= ATTR_SIZE;
		iattr.ia_size = new_size;
	पूर्ण

	error = inode->i_sb->s_export_op->commit_blocks(inode, iomaps,
			nr_iomaps, &iattr);
	kमुक्त(iomaps);
	वापस nfsत्रुटि_सं(error);
पूर्ण

#अगर_घोषित CONFIG_NFSD_BLOCKLAYOUT
अटल पूर्णांक
nfsd4_block_get_device_info_simple(काष्ठा super_block *sb,
		काष्ठा nfsd4_getdeviceinfo *gdp)
अणु
	काष्ठा pnfs_block_deviceaddr *dev;
	काष्ठा pnfs_block_volume *b;

	dev = kzalloc(माप(काष्ठा pnfs_block_deviceaddr) +
		      माप(काष्ठा pnfs_block_volume), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	gdp->gd_device = dev;

	dev->nr_volumes = 1;
	b = &dev->volumes[0];

	b->type = PNFS_BLOCK_VOLUME_SIMPLE;
	b->simple.sig_len = PNFS_BLOCK_UUID_LEN;
	वापस sb->s_export_op->get_uuid(sb, b->simple.sig, &b->simple.sig_len,
			&b->simple.offset);
पूर्ण

अटल __be32
nfsd4_block_proc_getdeviceinfo(काष्ठा super_block *sb,
		काष्ठा svc_rqst *rqstp,
		काष्ठा nfs4_client *clp,
		काष्ठा nfsd4_getdeviceinfo *gdp)
अणु
	अगर (bdev_is_partition(sb->s_bdev))
		वापस nfserr_inval;
	वापस nfsत्रुटि_सं(nfsd4_block_get_device_info_simple(sb, gdp));
पूर्ण

अटल __be32
nfsd4_block_proc_layoutcommit(काष्ठा inode *inode,
		काष्ठा nfsd4_layoutcommit *lcp)
अणु
	काष्ठा iomap *iomaps;
	पूर्णांक nr_iomaps;

	nr_iomaps = nfsd4_block_decode_layoutupdate(lcp->lc_up_layout,
			lcp->lc_up_len, &iomaps, i_blocksize(inode));
	अगर (nr_iomaps < 0)
		वापस nfsत्रुटि_सं(nr_iomaps);

	वापस nfsd4_block_commit_blocks(inode, lcp, iomaps, nr_iomaps);
पूर्ण

स्थिर काष्ठा nfsd4_layout_ops bl_layout_ops = अणु
	/*
	 * Pretend that we send notअगरication to the client.  This is a blatant
	 * lie to क्रमce recent Linux clients to cache our device IDs.
	 * We rarely ever change the device ID, so the harm of leaking deviceids
	 * क्रम a जबतक isn't too bad.  Unक्रमtunately RFC5661 is a complete mess
	 * in this regard, but I filed errata 4119 क्रम this a जबतक ago, and
	 * hopefully the Linux client will eventually start caching deviceids
	 * without this again.
	 */
	.notअगरy_types		=
			NOTIFY_DEVICEID4_DELETE | NOTIFY_DEVICEID4_CHANGE,
	.proc_getdeviceinfo	= nfsd4_block_proc_getdeviceinfo,
	.encode_getdeviceinfo	= nfsd4_block_encode_getdeviceinfo,
	.proc_layoutget		= nfsd4_block_proc_layoutget,
	.encode_layoutget	= nfsd4_block_encode_layoutget,
	.proc_layoutcommit	= nfsd4_block_proc_layoutcommit,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NFSD_BLOCKLAYOUT */

#अगर_घोषित CONFIG_NFSD_SCSILAYOUT
अटल पूर्णांक nfsd4_scsi_identअगरy_device(काष्ठा block_device *bdev,
		काष्ठा pnfs_block_volume *b)
अणु
	काष्ठा request_queue *q = bdev->bd_disk->queue;
	काष्ठा request *rq;
	काष्ठा scsi_request *req;
	/*
	 * The allocation length (passed in bytes 3 and 4 of the INQUIRY
	 * command descriptor block) specअगरies the number of bytes that have
	 * been allocated क्रम the data-in buffer.
	 * 252 is the highest one-byte value that is a multiple of 4.
	 * 65532 is the highest two-byte value that is a multiple of 4.
	 */
	माप_प्रकार bufflen = 252, maxlen = 65532, len, id_len;
	u8 *buf, *d, type, assoc;
	पूर्णांक retries = 1, error;

	अगर (WARN_ON_ONCE(!blk_queue_scsi_passthrough(q)))
		वापस -EINVAL;

again:
	buf = kzalloc(bufflen, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	rq = blk_get_request(q, REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(rq)) अणु
		error = -ENOMEM;
		जाओ out_मुक्त_buf;
	पूर्ण
	req = scsi_req(rq);

	error = blk_rq_map_kern(q, rq, buf, bufflen, GFP_KERNEL);
	अगर (error)
		जाओ out_put_request;

	req->cmd[0] = INQUIRY;
	req->cmd[1] = 1;
	req->cmd[2] = 0x83;
	req->cmd[3] = bufflen >> 8;
	req->cmd[4] = bufflen & 0xff;
	req->cmd_len = COMMAND_SIZE(INQUIRY);

	blk_execute_rq(शून्य, rq, 1);
	अगर (req->result) अणु
		pr_err("pNFS: INQUIRY 0x83 failed with: %x\n",
			req->result);
		error = -EIO;
		जाओ out_put_request;
	पूर्ण

	len = (buf[2] << 8) + buf[3] + 4;
	अगर (len > bufflen) अणु
		अगर (len <= maxlen && retries--) अणु
			blk_put_request(rq);
			kमुक्त(buf);
			bufflen = len;
			जाओ again;
		पूर्ण
		pr_err("pNFS: INQUIRY 0x83 response invalid (len = %zd)\n",
			len);
		जाओ out_put_request;
	पूर्ण

	d = buf + 4;
	क्रम (d = buf + 4; d < buf + len; d += id_len + 4) अणु
		id_len = d[3];
		type = d[1] & 0xf;
		assoc = (d[1] >> 4) & 0x3;

		/*
		 * We only care about a EUI-64 and NAA designator types
		 * with LU association.
		 */
		अगर (assoc != 0x00)
			जारी;
		अगर (type != 0x02 && type != 0x03)
			जारी;
		अगर (id_len != 8 && id_len != 12 && id_len != 16)
			जारी;

		b->scsi.code_set = PS_CODE_SET_BINARY;
		b->scsi.designator_type = type == 0x02 ?
			PS_DESIGNATOR_EUI64 : PS_DESIGNATOR_NAA;
		b->scsi.designator_len = id_len;
		स_नकल(b->scsi.designator, d + 4, id_len);

		/*
		 * If we found a 8 or 12 byte descriptor जारी on to
		 * see अगर a 16 byte one is available.  If we find a
		 * 16 byte descriptor we're करोne.
		 */
		अगर (id_len == 16)
			अवरोध;
	पूर्ण

out_put_request:
	blk_put_request(rq);
out_मुक्त_buf:
	kमुक्त(buf);
	वापस error;
पूर्ण

#घोषणा NFSD_MDS_PR_KEY		0x0100000000000000ULL

/*
 * We use the client ID as a unique key क्रम the reservations.
 * This allows us to easily fence a client when recalls fail.
 */
अटल u64 nfsd4_scsi_pr_key(काष्ठा nfs4_client *clp)
अणु
	वापस ((u64)clp->cl_clientid.cl_boot << 32) | clp->cl_clientid.cl_id;
पूर्ण

अटल पूर्णांक
nfsd4_block_get_device_info_scsi(काष्ठा super_block *sb,
		काष्ठा nfs4_client *clp,
		काष्ठा nfsd4_getdeviceinfo *gdp)
अणु
	काष्ठा pnfs_block_deviceaddr *dev;
	काष्ठा pnfs_block_volume *b;
	स्थिर काष्ठा pr_ops *ops;
	पूर्णांक error;

	dev = kzalloc(माप(काष्ठा pnfs_block_deviceaddr) +
		      माप(काष्ठा pnfs_block_volume), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	gdp->gd_device = dev;

	dev->nr_volumes = 1;
	b = &dev->volumes[0];

	b->type = PNFS_BLOCK_VOLUME_SCSI;
	b->scsi.pr_key = nfsd4_scsi_pr_key(clp);

	error = nfsd4_scsi_identअगरy_device(sb->s_bdev, b);
	अगर (error)
		वापस error;

	ops = sb->s_bdev->bd_disk->fops->pr_ops;
	अगर (!ops) अणु
		pr_err("pNFS: device %s does not support PRs.\n",
			sb->s_id);
		वापस -EINVAL;
	पूर्ण

	error = ops->pr_रेजिस्टर(sb->s_bdev, 0, NFSD_MDS_PR_KEY, true);
	अगर (error) अणु
		pr_err("pNFS: failed to register key for device %s.\n",
			sb->s_id);
		वापस -EINVAL;
	पूर्ण

	error = ops->pr_reserve(sb->s_bdev, NFSD_MDS_PR_KEY,
			PR_EXCLUSIVE_ACCESS_REG_ONLY, 0);
	अगर (error) अणु
		pr_err("pNFS: failed to reserve device %s.\n",
			sb->s_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल __be32
nfsd4_scsi_proc_getdeviceinfo(काष्ठा super_block *sb,
		काष्ठा svc_rqst *rqstp,
		काष्ठा nfs4_client *clp,
		काष्ठा nfsd4_getdeviceinfo *gdp)
अणु
	अगर (bdev_is_partition(sb->s_bdev))
		वापस nfserr_inval;
	वापस nfsत्रुटि_सं(nfsd4_block_get_device_info_scsi(sb, clp, gdp));
पूर्ण
अटल __be32
nfsd4_scsi_proc_layoutcommit(काष्ठा inode *inode,
		काष्ठा nfsd4_layoutcommit *lcp)
अणु
	काष्ठा iomap *iomaps;
	पूर्णांक nr_iomaps;

	nr_iomaps = nfsd4_scsi_decode_layoutupdate(lcp->lc_up_layout,
			lcp->lc_up_len, &iomaps, i_blocksize(inode));
	अगर (nr_iomaps < 0)
		वापस nfsत्रुटि_सं(nr_iomaps);

	वापस nfsd4_block_commit_blocks(inode, lcp, iomaps, nr_iomaps);
पूर्ण

अटल व्योम
nfsd4_scsi_fence_client(काष्ठा nfs4_layout_stateid *ls)
अणु
	काष्ठा nfs4_client *clp = ls->ls_stid.sc_client;
	काष्ठा block_device *bdev = ls->ls_file->nf_file->f_path.mnt->mnt_sb->s_bdev;

	bdev->bd_disk->fops->pr_ops->pr_preempt(bdev, NFSD_MDS_PR_KEY,
			nfsd4_scsi_pr_key(clp), 0, true);
पूर्ण

स्थिर काष्ठा nfsd4_layout_ops scsi_layout_ops = अणु
	/*
	 * Pretend that we send notअगरication to the client.  This is a blatant
	 * lie to क्रमce recent Linux clients to cache our device IDs.
	 * We rarely ever change the device ID, so the harm of leaking deviceids
	 * क्रम a जबतक isn't too bad.  Unक्रमtunately RFC5661 is a complete mess
	 * in this regard, but I filed errata 4119 क्रम this a जबतक ago, and
	 * hopefully the Linux client will eventually start caching deviceids
	 * without this again.
	 */
	.notअगरy_types		=
			NOTIFY_DEVICEID4_DELETE | NOTIFY_DEVICEID4_CHANGE,
	.proc_getdeviceinfo	= nfsd4_scsi_proc_getdeviceinfo,
	.encode_getdeviceinfo	= nfsd4_block_encode_getdeviceinfo,
	.proc_layoutget		= nfsd4_block_proc_layoutget,
	.encode_layoutget	= nfsd4_block_encode_layoutget,
	.proc_layoutcommit	= nfsd4_scsi_proc_layoutcommit,
	.fence_client		= nfsd4_scsi_fence_client,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NFSD_SCSILAYOUT */
