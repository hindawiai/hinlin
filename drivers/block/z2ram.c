<शैली गुरु>
/*
** z2ram - Amiga pseuकरो-driver to access 16bit-RAM in ZorroII space
**         as a block device, to be used as a RAM disk or swap space
** 
** Copyright (C) 1994 by Ingo Wilken (Ingo.Wilken@inक्रमmatik.uni-oldenburg.de)
**
** ++Geert: support क्रम zorro_unused_z2ram, better range checking
** ++roman: translate accesses via an array
** ++Milan: support क्रम ChipRAM usage
** ++yambo: converted to 2.0 kernel
** ++yambo: modularized and support added क्रम 3 minor devices including:
**          MAJOR  MINOR  DESCRIPTION
**          -----  -----  ----------------------------------------------
**          37     0       Use Zorro II and Chip ram
**          37     1       Use only Zorro II ram
**          37     2       Use only Chip ram
**          37     4-7     Use memory list entry 1-4 (first is 0)
** ++jskov: support क्रम 1-4th memory list entry.
**
** Permission to use, copy, modअगरy, and distribute this software and its
** करोcumentation क्रम any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** करोcumentation.  This software is provided "as is" without express or
** implied warranty.
*/

#घोषणा DEVICE_NAME "Z2RAM"

#समावेश <linux/major.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/amigahw.h>

#समावेश <linux/zorro.h>

#घोषणा Z2MINOR_COMBINED      (0)
#घोषणा Z2MINOR_Z2ONLY        (1)
#घोषणा Z2MINOR_CHIPONLY      (2)
#घोषणा Z2MINOR_MEMLIST1      (4)
#घोषणा Z2MINOR_MEMLIST2      (5)
#घोषणा Z2MINOR_MEMLIST3      (6)
#घोषणा Z2MINOR_MEMLIST4      (7)
#घोषणा Z2MINOR_COUNT         (8)	/* Move this करोwn when adding a new minor */

#घोषणा Z2RAM_CHUNK1024       ( Z2RAM_CHUNKSIZE >> 10 )

अटल DEFINE_MUTEX(z2ram_mutex);
अटल u_दीर्घ *z2ram_map = शून्य;
अटल u_दीर्घ z2ram_size = 0;
अटल पूर्णांक z2_count = 0;
अटल पूर्णांक chip_count = 0;
अटल पूर्णांक list_count = 0;
अटल पूर्णांक current_device = -1;

अटल DEFINE_SPINLOCK(z2ram_lock);

अटल काष्ठा gendisk *z2ram_gendisk[Z2MINOR_COUNT];

अटल blk_status_t z2_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request *req = bd->rq;
	अचिन्हित दीर्घ start = blk_rq_pos(req) << 9;
	अचिन्हित दीर्घ len = blk_rq_cur_bytes(req);

	blk_mq_start_request(req);

	अगर (start + len > z2ram_size) अणु
		pr_err(DEVICE_NAME ": bad access: block=%llu, "
		       "count=%u\n",
		       (अचिन्हित दीर्घ दीर्घ)blk_rq_pos(req),
		       blk_rq_cur_sectors(req));
		वापस BLK_STS_IOERR;
	पूर्ण

	spin_lock_irq(&z2ram_lock);

	जबतक (len) अणु
		अचिन्हित दीर्घ addr = start & Z2RAM_CHUNKMASK;
		अचिन्हित दीर्घ size = Z2RAM_CHUNKSIZE - addr;
		व्योम *buffer = bio_data(req->bio);

		अगर (len < size)
			size = len;
		addr += z2ram_map[start >> Z2RAM_CHUNKSHIFT];
		अगर (rq_data_dir(req) == READ)
			स_नकल(buffer, (अक्षर *)addr, size);
		अन्यथा
			स_नकल((अक्षर *)addr, buffer, size);
		start += size;
		len -= size;
	पूर्ण

	spin_unlock_irq(&z2ram_lock);
	blk_mq_end_request(req, BLK_STS_OK);
	वापस BLK_STS_OK;
पूर्ण

अटल व्योम get_z2ram(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < Z2RAM_SIZE / Z2RAM_CHUNKSIZE; i++) अणु
		अगर (test_bit(i, zorro_unused_z2ram)) अणु
			z2_count++;
			z2ram_map[z2ram_size++] =
			    (अचिन्हित दीर्घ)ZTWO_VADDR(Z2RAM_START) +
			    (i << Z2RAM_CHUNKSHIFT);
			clear_bit(i, zorro_unused_z2ram);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल व्योम get_chipram(व्योम)
अणु

	जबतक (amiga_chip_avail() > (Z2RAM_CHUNKSIZE * 4)) अणु
		chip_count++;
		z2ram_map[z2ram_size] =
		    (u_दीर्घ) amiga_chip_alloc(Z2RAM_CHUNKSIZE, "z2ram");

		अगर (z2ram_map[z2ram_size] == 0) अणु
			अवरोध;
		पूर्ण

		z2ram_size++;
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक z2_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक device;
	पूर्णांक max_z2_map = (Z2RAM_SIZE / Z2RAM_CHUNKSIZE) * माप(z2ram_map[0]);
	पूर्णांक max_chip_map = (amiga_chip_size / Z2RAM_CHUNKSIZE) *
	    माप(z2ram_map[0]);
	पूर्णांक rc = -ENOMEM;

	device = MINOR(bdev->bd_dev);

	mutex_lock(&z2ram_mutex);
	अगर (current_device != -1 && current_device != device) अणु
		rc = -EBUSY;
		जाओ err_out;
	पूर्ण

	अगर (current_device == -1) अणु
		z2_count = 0;
		chip_count = 0;
		list_count = 0;
		z2ram_size = 0;

		/* Use a specअगरic list entry. */
		अगर (device >= Z2MINOR_MEMLIST1 && device <= Z2MINOR_MEMLIST4) अणु
			पूर्णांक index = device - Z2MINOR_MEMLIST1 + 1;
			अचिन्हित दीर्घ size, paddr, vaddr;

			अगर (index >= m68k_realnum_memory) अणु
				prपूर्णांकk(KERN_ERR DEVICE_NAME
				       ": no such entry in z2ram_map\n");
				जाओ err_out;
			पूर्ण

			paddr = m68k_memory[index].addr;
			size = m68k_memory[index].size & ~(Z2RAM_CHUNKSIZE - 1);

#अगर_घोषित __घातerpc__
			/* FIXME: ioremap करोesn't build correct memory tables. */
			अणु
				vमुक्त(vदो_स्मृति(size));
			पूर्ण

			vaddr = (अचिन्हित दीर्घ)ioremap_wt(paddr, size);

#अन्यथा
			vaddr =
			    (अचिन्हित दीर्घ)z_remap_nocache_nonser(paddr, size);
#पूर्ण_अगर
			z2ram_map =
			    kदो_स्मृति_array(size / Z2RAM_CHUNKSIZE,
					  माप(z2ram_map[0]), GFP_KERNEL);
			अगर (z2ram_map == शून्य) अणु
				prपूर्णांकk(KERN_ERR DEVICE_NAME
				       ": cannot get mem for z2ram_map\n");
				जाओ err_out;
			पूर्ण

			जबतक (size) अणु
				z2ram_map[z2ram_size++] = vaddr;
				size -= Z2RAM_CHUNKSIZE;
				vaddr += Z2RAM_CHUNKSIZE;
				list_count++;
			पूर्ण

			अगर (z2ram_size != 0)
				prपूर्णांकk(KERN_INFO DEVICE_NAME
				       ": using %iK List Entry %d Memory\n",
				       list_count * Z2RAM_CHUNK1024, index);
		पूर्ण अन्यथा
			चयन (device) अणु
			हाल Z2MINOR_COMBINED:

				z2ram_map =
				    kदो_स्मृति(max_z2_map + max_chip_map,
					    GFP_KERNEL);
				अगर (z2ram_map == शून्य) अणु
					prपूर्णांकk(KERN_ERR DEVICE_NAME
					       ": cannot get mem for z2ram_map\n");
					जाओ err_out;
				पूर्ण

				get_z2ram();
				get_chipram();

				अगर (z2ram_size != 0)
					prपूर्णांकk(KERN_INFO DEVICE_NAME
					       ": using %iK Zorro II RAM and %iK Chip RAM (Total %dK)\n",
					       z2_count * Z2RAM_CHUNK1024,
					       chip_count * Z2RAM_CHUNK1024,
					       (z2_count +
						chip_count) * Z2RAM_CHUNK1024);

				अवरोध;

			हाल Z2MINOR_Z2ONLY:
				z2ram_map = kदो_स्मृति(max_z2_map, GFP_KERNEL);
				अगर (z2ram_map == शून्य) अणु
					prपूर्णांकk(KERN_ERR DEVICE_NAME
					       ": cannot get mem for z2ram_map\n");
					जाओ err_out;
				पूर्ण

				get_z2ram();

				अगर (z2ram_size != 0)
					prपूर्णांकk(KERN_INFO DEVICE_NAME
					       ": using %iK of Zorro II RAM\n",
					       z2_count * Z2RAM_CHUNK1024);

				अवरोध;

			हाल Z2MINOR_CHIPONLY:
				z2ram_map = kदो_स्मृति(max_chip_map, GFP_KERNEL);
				अगर (z2ram_map == शून्य) अणु
					prपूर्णांकk(KERN_ERR DEVICE_NAME
					       ": cannot get mem for z2ram_map\n");
					जाओ err_out;
				पूर्ण

				get_chipram();

				अगर (z2ram_size != 0)
					prपूर्णांकk(KERN_INFO DEVICE_NAME
					       ": using %iK Chip RAM\n",
					       chip_count * Z2RAM_CHUNK1024);

				अवरोध;

			शेष:
				rc = -ENODEV;
				जाओ err_out;

				अवरोध;
			पूर्ण

		अगर (z2ram_size == 0) अणु
			prपूर्णांकk(KERN_NOTICE DEVICE_NAME
			       ": no unused ZII/Chip RAM found\n");
			जाओ err_out_kमुक्त;
		पूर्ण

		current_device = device;
		z2ram_size <<= Z2RAM_CHUNKSHIFT;
		set_capacity(z2ram_gendisk[device], z2ram_size >> 9);
	पूर्ण

	mutex_unlock(&z2ram_mutex);
	वापस 0;

err_out_kमुक्त:
	kमुक्त(z2ram_map);
err_out:
	mutex_unlock(&z2ram_mutex);
	वापस rc;
पूर्ण

अटल व्योम z2_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	mutex_lock(&z2ram_mutex);
	अगर (current_device == -1) अणु
		mutex_unlock(&z2ram_mutex);
		वापस;
	पूर्ण
	mutex_unlock(&z2ram_mutex);
	/*
	 * FIXME: unmap memory
	 */
पूर्ण

अटल स्थिर काष्ठा block_device_operations z2_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = z2_खोलो,
	.release = z2_release,
पूर्ण;

अटल काष्ठा blk_mq_tag_set tag_set;

अटल स्थिर काष्ठा blk_mq_ops z2_mq_ops = अणु
	.queue_rq = z2_queue_rq,
पूर्ण;

अटल पूर्णांक z2ram_रेजिस्टर_disk(पूर्णांक minor)
अणु
	काष्ठा request_queue *q;
	काष्ठा gendisk *disk;

	disk = alloc_disk(1);
	अगर (!disk)
		वापस -ENOMEM;

	q = blk_mq_init_queue(&tag_set);
	अगर (IS_ERR(q)) अणु
		put_disk(disk);
		वापस PTR_ERR(q);
	पूर्ण

	disk->major = Z2RAM_MAJOR;
	disk->first_minor = minor;
	disk->fops = &z2_fops;
	अगर (minor)
		प्र_लिखो(disk->disk_name, "z2ram%d", minor);
	अन्यथा
		प्र_लिखो(disk->disk_name, "z2ram");
	disk->queue = q;

	z2ram_gendisk[minor] = disk;
	add_disk(disk);
	वापस 0;
पूर्ण

अटल पूर्णांक __init z2_init(व्योम)
अणु
	पूर्णांक ret, i;

	अगर (!MACH_IS_AMIGA)
		वापस -ENODEV;

	अगर (रेजिस्टर_blkdev(Z2RAM_MAJOR, DEVICE_NAME))
		वापस -EBUSY;

	tag_set.ops = &z2_mq_ops;
	tag_set.nr_hw_queues = 1;
	tag_set.nr_maps = 1;
	tag_set.queue_depth = 16;
	tag_set.numa_node = NUMA_NO_NODE;
	tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	ret = blk_mq_alloc_tag_set(&tag_set);
	अगर (ret)
		जाओ out_unरेजिस्टर_blkdev;

	क्रम (i = 0; i < Z2MINOR_COUNT; i++) अणु
		ret = z2ram_रेजिस्टर_disk(i);
		अगर (ret && i == 0)
			जाओ out_मुक्त_tagset;
	पूर्ण

	वापस 0;

out_मुक्त_tagset:
	blk_mq_मुक्त_tag_set(&tag_set);
out_unरेजिस्टर_blkdev:
	unरेजिस्टर_blkdev(Z2RAM_MAJOR, DEVICE_NAME);
	वापस ret;
पूर्ण

अटल व्योम __निकास z2_निकास(व्योम)
अणु
	पूर्णांक i, j;

	unरेजिस्टर_blkdev(Z2RAM_MAJOR, DEVICE_NAME);

	क्रम (i = 0; i < Z2MINOR_COUNT; i++) अणु
		del_gendisk(z2ram_gendisk[i]);
		blk_cleanup_queue(z2ram_gendisk[i]->queue);
		put_disk(z2ram_gendisk[i]);
	पूर्ण
	blk_mq_मुक्त_tag_set(&tag_set);

	अगर (current_device != -1) अणु
		i = 0;

		क्रम (j = 0; j < z2_count; j++) अणु
			set_bit(i++, zorro_unused_z2ram);
		पूर्ण

		क्रम (j = 0; j < chip_count; j++) अणु
			अगर (z2ram_map[i]) अणु
				amiga_chip_मुक्त((व्योम *)z2ram_map[i++]);
			पूर्ण
		पूर्ण

		अगर (z2ram_map != शून्य) अणु
			kमुक्त(z2ram_map);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

module_init(z2_init);
module_निकास(z2_निकास);
MODULE_LICENSE("GPL");
