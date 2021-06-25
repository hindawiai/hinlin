<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NVDIMM Block Winकरोw Driver
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/genhd.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/nd.h>
#समावेश <linux/sizes.h>
#समावेश "nd.h"

अटल u32 nsblk_meta_size(काष्ठा nd_namespace_blk *nsblk)
अणु
	वापस nsblk->lbasize - ((nsblk->lbasize >= 4096) ? 4096 : 512);
पूर्ण

अटल u32 nsblk_पूर्णांकernal_lbasize(काष्ठा nd_namespace_blk *nsblk)
अणु
	वापस roundup(nsblk->lbasize, INT_LBASIZE_ALIGNMENT);
पूर्ण

अटल u32 nsblk_sector_size(काष्ठा nd_namespace_blk *nsblk)
अणु
	वापस nsblk->lbasize - nsblk_meta_size(nsblk);
पूर्ण

अटल resource_माप_प्रकार to_dev_offset(काष्ठा nd_namespace_blk *nsblk,
				resource_माप_प्रकार ns_offset, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nsblk->num_resources; i++) अणु
		अगर (ns_offset < resource_size(nsblk->res[i])) अणु
			अगर (ns_offset + len > resource_size(nsblk->res[i])) अणु
				dev_WARN_ONCE(&nsblk->common.dev, 1,
					"illegal request\n");
				वापस SIZE_MAX;
			पूर्ण
			वापस nsblk->res[i]->start + ns_offset;
		पूर्ण
		ns_offset -= resource_size(nsblk->res[i]);
	पूर्ण

	dev_WARN_ONCE(&nsblk->common.dev, 1, "request out of range\n");
	वापस SIZE_MAX;
पूर्ण

अटल काष्ठा nd_blk_region *to_ndbr(काष्ठा nd_namespace_blk *nsblk)
अणु
	काष्ठा nd_region *nd_region;
	काष्ठा device *parent;

	parent = nsblk->common.dev.parent;
	nd_region = container_of(parent, काष्ठा nd_region, dev);
	वापस container_of(nd_region, काष्ठा nd_blk_region, nd_region);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
अटल पूर्णांक nd_blk_rw_पूर्णांकegrity(काष्ठा nd_namespace_blk *nsblk,
		काष्ठा bio_पूर्णांकegrity_payload *bip, u64 lba, पूर्णांक rw)
अणु
	काष्ठा nd_blk_region *ndbr = to_ndbr(nsblk);
	अचिन्हित पूर्णांक len = nsblk_meta_size(nsblk);
	resource_माप_प्रकार	dev_offset, ns_offset;
	u32 पूर्णांकernal_lbasize, sector_size;
	पूर्णांक err = 0;

	पूर्णांकernal_lbasize = nsblk_पूर्णांकernal_lbasize(nsblk);
	sector_size = nsblk_sector_size(nsblk);
	ns_offset = lba * पूर्णांकernal_lbasize + sector_size;
	dev_offset = to_dev_offset(nsblk, ns_offset, len);
	अगर (dev_offset == SIZE_MAX)
		वापस -EIO;

	जबतक (len) अणु
		अचिन्हित पूर्णांक cur_len;
		काष्ठा bio_vec bv;
		व्योम *iobuf;

		bv = bvec_iter_bvec(bip->bip_vec, bip->bip_iter);
		/*
		 * The 'bv' obtained from bvec_iter_bvec has its .bv_len and
		 * .bv_offset alपढ़ोy adjusted क्रम iter->bi_bvec_करोne, and we
		 * can use those directly
		 */

		cur_len = min(len, bv.bv_len);
		iobuf = kmap_atomic(bv.bv_page);
		err = ndbr->करो_io(ndbr, dev_offset, iobuf + bv.bv_offset,
				cur_len, rw);
		kunmap_atomic(iobuf);
		अगर (err)
			वापस err;

		len -= cur_len;
		dev_offset += cur_len;
		अगर (!bvec_iter_advance(bip->bip_vec, &bip->bip_iter, cur_len))
			वापस -EIO;
	पूर्ण

	वापस err;
पूर्ण

#अन्यथा /* CONFIG_BLK_DEV_INTEGRITY */
अटल पूर्णांक nd_blk_rw_पूर्णांकegrity(काष्ठा nd_namespace_blk *nsblk,
		काष्ठा bio_पूर्णांकegrity_payload *bip, u64 lba, पूर्णांक rw)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nsblk_करो_bvec(काष्ठा nd_namespace_blk *nsblk,
		काष्ठा bio_पूर्णांकegrity_payload *bip, काष्ठा page *page,
		अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off, पूर्णांक rw, sector_t sector)
अणु
	काष्ठा nd_blk_region *ndbr = to_ndbr(nsblk);
	resource_माप_प्रकार	dev_offset, ns_offset;
	u32 पूर्णांकernal_lbasize, sector_size;
	पूर्णांक err = 0;
	व्योम *iobuf;
	u64 lba;

	पूर्णांकernal_lbasize = nsblk_पूर्णांकernal_lbasize(nsblk);
	sector_size = nsblk_sector_size(nsblk);
	जबतक (len) अणु
		अचिन्हित पूर्णांक cur_len;

		/*
		 * If we करोn't have an integrity payload, we don't have to
		 * split the bvec पूर्णांकo sectors, as this would cause unnecessary
		 * Block Winकरोw setup/move steps. the करो_io routine is capable
		 * of handling len <= PAGE_SIZE.
		 */
		cur_len = bip ? min(len, sector_size) : len;

		lba = भाग_u64(sector << SECTOR_SHIFT, sector_size);
		ns_offset = lba * पूर्णांकernal_lbasize;
		dev_offset = to_dev_offset(nsblk, ns_offset, cur_len);
		अगर (dev_offset == SIZE_MAX)
			वापस -EIO;

		iobuf = kmap_atomic(page);
		err = ndbr->करो_io(ndbr, dev_offset, iobuf + off, cur_len, rw);
		kunmap_atomic(iobuf);
		अगर (err)
			वापस err;

		अगर (bip) अणु
			err = nd_blk_rw_पूर्णांकegrity(nsblk, bip, lba, rw);
			अगर (err)
				वापस err;
		पूर्ण
		len -= cur_len;
		off += cur_len;
		sector += sector_size >> SECTOR_SHIFT;
	पूर्ण

	वापस err;
पूर्ण

अटल blk_qc_t nd_blk_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip;
	काष्ठा nd_namespace_blk *nsblk = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा bvec_iter iter;
	अचिन्हित दीर्घ start;
	काष्ठा bio_vec bvec;
	पूर्णांक err = 0, rw;
	bool करो_acct;

	अगर (!bio_पूर्णांकegrity_prep(bio))
		वापस BLK_QC_T_NONE;

	bip = bio_पूर्णांकegrity(bio);
	rw = bio_data_dir(bio);
	करो_acct = blk_queue_io_stat(bio->bi_bdev->bd_disk->queue);
	अगर (करो_acct)
		start = bio_start_io_acct(bio);
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		अचिन्हित पूर्णांक len = bvec.bv_len;

		BUG_ON(len > PAGE_SIZE);
		err = nsblk_करो_bvec(nsblk, bip, bvec.bv_page, len,
				bvec.bv_offset, rw, iter.bi_sector);
		अगर (err) अणु
			dev_dbg(&nsblk->common.dev,
					"io error in %s sector %lld, len %d,\n",
					(rw == READ) ? "READ" : "WRITE",
					(अचिन्हित दीर्घ दीर्घ) iter.bi_sector, len);
			bio->bi_status = त्रुटि_सं_to_blk_status(err);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (करो_acct)
		bio_end_io_acct(bio, start);

	bio_endio(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक nsblk_rw_bytes(काष्ठा nd_namespace_common *ndns,
		resource_माप_प्रकार offset, व्योम *iobuf, माप_प्रकार n, पूर्णांक rw,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(&ndns->dev);
	काष्ठा nd_blk_region *ndbr = to_ndbr(nsblk);
	resource_माप_प्रकार	dev_offset;

	dev_offset = to_dev_offset(nsblk, offset, n);

	अगर (unlikely(offset + n > nsblk->size)) अणु
		dev_WARN_ONCE(&ndns->dev, 1, "request out of range\n");
		वापस -EFAULT;
	पूर्ण

	अगर (dev_offset == SIZE_MAX)
		वापस -EIO;

	वापस ndbr->करो_io(ndbr, dev_offset, iobuf, n, rw);
पूर्ण

अटल स्थिर काष्ठा block_device_operations nd_blk_fops = अणु
	.owner = THIS_MODULE,
	.submit_bio =  nd_blk_submit_bio,
पूर्ण;

अटल व्योम nd_blk_release_queue(व्योम *q)
अणु
	blk_cleanup_queue(q);
पूर्ण

अटल व्योम nd_blk_release_disk(व्योम *disk)
अणु
	del_gendisk(disk);
	put_disk(disk);
पूर्ण

अटल पूर्णांक nsblk_attach_disk(काष्ठा nd_namespace_blk *nsblk)
अणु
	काष्ठा device *dev = &nsblk->common.dev;
	resource_माप_प्रकार available_disk_size;
	काष्ठा request_queue *q;
	काष्ठा gendisk *disk;
	u64 पूर्णांकernal_nlba;

	पूर्णांकernal_nlba = भाग_u64(nsblk->size, nsblk_पूर्णांकernal_lbasize(nsblk));
	available_disk_size = पूर्णांकernal_nlba * nsblk_sector_size(nsblk);

	q = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!q)
		वापस -ENOMEM;
	अगर (devm_add_action_or_reset(dev, nd_blk_release_queue, q))
		वापस -ENOMEM;

	blk_queue_max_hw_sectors(q, अच_पूर्णांक_उच्च);
	blk_queue_logical_block_size(q, nsblk_sector_size(nsblk));
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);

	disk = alloc_disk(0);
	अगर (!disk)
		वापस -ENOMEM;

	disk->first_minor	= 0;
	disk->fops		= &nd_blk_fops;
	disk->queue		= q;
	disk->flags		= GENHD_FL_EXT_DEVT;
	disk->निजी_data	= nsblk;
	nvdimm_namespace_disk_name(&nsblk->common, disk->disk_name);

	अगर (devm_add_action_or_reset(dev, nd_blk_release_disk, disk))
		वापस -ENOMEM;

	अगर (nsblk_meta_size(nsblk)) अणु
		पूर्णांक rc = nd_पूर्णांकegrity_init(disk, nsblk_meta_size(nsblk));

		अगर (rc)
			वापस rc;
	पूर्ण

	set_capacity(disk, available_disk_size >> SECTOR_SHIFT);
	device_add_disk(dev, disk, शून्य);
	nvdimm_check_and_set_ro(disk);
	वापस 0;
पूर्ण

अटल पूर्णांक nd_blk_probe(काष्ठा device *dev)
अणु
	काष्ठा nd_namespace_common *ndns;
	काष्ठा nd_namespace_blk *nsblk;

	ndns = nvdimm_namespace_common_probe(dev);
	अगर (IS_ERR(ndns))
		वापस PTR_ERR(ndns);

	nsblk = to_nd_namespace_blk(&ndns->dev);
	nsblk->size = nvdimm_namespace_capacity(ndns);
	dev_set_drvdata(dev, nsblk);

	ndns->rw_bytes = nsblk_rw_bytes;
	अगर (is_nd_btt(dev))
		वापस nvdimm_namespace_attach_btt(ndns);
	अन्यथा अगर (nd_btt_probe(dev, ndns) == 0) अणु
		/* we'll come back as btt-blk */
		वापस -ENXIO;
	पूर्ण अन्यथा
		वापस nsblk_attach_disk(nsblk);
पूर्ण

अटल व्योम nd_blk_हटाओ(काष्ठा device *dev)
अणु
	अगर (is_nd_btt(dev))
		nvdimm_namespace_detach_btt(to_nd_btt(dev));
पूर्ण

अटल काष्ठा nd_device_driver nd_blk_driver = अणु
	.probe = nd_blk_probe,
	.हटाओ = nd_blk_हटाओ,
	.drv = अणु
		.name = "nd_blk",
	पूर्ण,
	.type = ND_DRIVER_NAMESPACE_BLK,
पूर्ण;

अटल पूर्णांक __init nd_blk_init(व्योम)
अणु
	वापस nd_driver_रेजिस्टर(&nd_blk_driver);
पूर्ण

अटल व्योम __निकास nd_blk_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&nd_blk_driver.drv);
पूर्ण

MODULE_AUTHOR("Ross Zwisler <ross.zwisler@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_ND_DEVICE(ND_DEVICE_NAMESPACE_BLK);
module_init(nd_blk_init);
module_निकास(nd_blk_निकास);
