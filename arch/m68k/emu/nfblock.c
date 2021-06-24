<शैली गुरु>
/*
 * ARAnyM block device driver
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/genhd.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/natfeat.h>

अटल दीर्घ nfhd_id;

क्रमागत अणु
	/* emulation entry poपूर्णांकs */
	NFHD_READ_WRITE = 10,
	NFHD_GET_CAPACITY = 14,

	/* skip ACSI devices */
	NFHD_DEV_OFFSET = 8,
पूर्ण;

अटल अंतरभूत s32 nfhd_पढ़ो_ग_लिखो(u32 major, u32 minor, u32 rwflag, u32 recno,
				  u32 count, u32 buf)
अणु
	वापस nf_call(nfhd_id + NFHD_READ_WRITE, major, minor, rwflag, recno,
		       count, buf);
पूर्ण

अटल अंतरभूत s32 nfhd_get_capacity(u32 major, u32 minor, u32 *blocks,
				    u32 *blocksize)
अणु
	वापस nf_call(nfhd_id + NFHD_GET_CAPACITY, major, minor,
		       virt_to_phys(blocks), virt_to_phys(blocksize));
पूर्ण

अटल LIST_HEAD(nfhd_list);

अटल पूर्णांक major_num;
module_param(major_num, पूर्णांक, 0);

काष्ठा nfhd_device अणु
	काष्ठा list_head list;
	पूर्णांक id;
	u32 blocks, bsize;
	पूर्णांक bshअगरt;
	काष्ठा request_queue *queue;
	काष्ठा gendisk *disk;
पूर्ण;

अटल blk_qc_t nfhd_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा nfhd_device *dev = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	पूर्णांक dir, len, shअगरt;
	sector_t sec = bio->bi_iter.bi_sector;

	dir = bio_data_dir(bio);
	shअगरt = dev->bshअगरt;
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		len = bvec.bv_len;
		len >>= 9;
		nfhd_पढ़ो_ग_लिखो(dev->id, 0, dir, sec >> shअगरt, len >> shअगरt,
				page_to_phys(bvec.bv_page) + bvec.bv_offset);
		sec += len;
	पूर्ण
	bio_endio(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक nfhd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा nfhd_device *dev = bdev->bd_disk->निजी_data;

	geo->cylinders = dev->blocks >> (6 - dev->bshअगरt);
	geo->heads = 4;
	geo->sectors = 16;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations nfhd_ops = अणु
	.owner	= THIS_MODULE,
	.submit_bio = nfhd_submit_bio,
	.getgeo	= nfhd_getgeo,
पूर्ण;

अटल पूर्णांक __init nfhd_init_one(पूर्णांक id, u32 blocks, u32 bsize)
अणु
	काष्ठा nfhd_device *dev;
	पूर्णांक dev_id = id - NFHD_DEV_OFFSET;

	pr_info("nfhd%u: found device with %u blocks (%u bytes)\n", dev_id,
		blocks, bsize);

	अगर (bsize < 512 || (bsize & (bsize - 1))) अणु
		pr_warn("nfhd%u: invalid block size\n", dev_id);
		वापस -EINVAL;
	पूर्ण

	dev = kदो_स्मृति(माप(काष्ठा nfhd_device), GFP_KERNEL);
	अगर (!dev)
		जाओ out;

	dev->id = id;
	dev->blocks = blocks;
	dev->bsize = bsize;
	dev->bshअगरt = ffs(bsize) - 10;

	dev->queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (dev->queue == शून्य)
		जाओ मुक्त_dev;

	blk_queue_logical_block_size(dev->queue, bsize);

	dev->disk = alloc_disk(16);
	अगर (!dev->disk)
		जाओ मुक्त_queue;

	dev->disk->major = major_num;
	dev->disk->first_minor = dev_id * 16;
	dev->disk->fops = &nfhd_ops;
	dev->disk->निजी_data = dev;
	प्र_लिखो(dev->disk->disk_name, "nfhd%u", dev_id);
	set_capacity(dev->disk, (sector_t)blocks * (bsize / 512));
	dev->disk->queue = dev->queue;

	add_disk(dev->disk);

	list_add_tail(&dev->list, &nfhd_list);

	वापस 0;

मुक्त_queue:
	blk_cleanup_queue(dev->queue);
मुक्त_dev:
	kमुक्त(dev);
out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __init nfhd_init(व्योम)
अणु
	u32 blocks, bsize;
	पूर्णांक ret;
	पूर्णांक i;

	nfhd_id = nf_get_id("XHDI");
	अगर (!nfhd_id)
		वापस -ENODEV;

	ret = रेजिस्टर_blkdev(major_num, "nfhd");
	अगर (ret < 0) अणु
		pr_warn("nfhd: unable to get major number\n");
		वापस ret;
	पूर्ण

	अगर (!major_num)
		major_num = ret;

	क्रम (i = NFHD_DEV_OFFSET; i < 24; i++) अणु
		अगर (nfhd_get_capacity(i, 0, &blocks, &bsize))
			जारी;
		nfhd_init_one(i, blocks, bsize);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास nfhd_निकास(व्योम)
अणु
	काष्ठा nfhd_device *dev, *next;

	list_क्रम_each_entry_safe(dev, next, &nfhd_list, list) अणु
		list_del(&dev->list);
		del_gendisk(dev->disk);
		put_disk(dev->disk);
		blk_cleanup_queue(dev->queue);
		kमुक्त(dev);
	पूर्ण
	unरेजिस्टर_blkdev(major_num, "nfhd");
पूर्ण

module_init(nfhd_init);
module_निकास(nfhd_निकास);

MODULE_LICENSE("GPL");
