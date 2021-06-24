<शैली गुरु>
/*
 * arch/xtensa/platक्रमms/iss/simdisk.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001-2013 Tensilica Inc.
 *   Authors	Victor Prupis
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/uaccess.h>
#समावेश <platक्रमm/simcall.h>

#घोषणा SIMDISK_MAJOR 240
#घोषणा SIMDISK_MINORS 1
#घोषणा MAX_SIMDISK_COUNT 10

काष्ठा simdisk अणु
	स्थिर अक्षर *filename;
	spinlock_t lock;
	काष्ठा request_queue *queue;
	काष्ठा gendisk *gd;
	काष्ठा proc_dir_entry *procfile;
	पूर्णांक users;
	अचिन्हित दीर्घ size;
	पूर्णांक fd;
पूर्ण;


अटल पूर्णांक simdisk_count = CONFIG_BLK_DEV_SIMDISK_COUNT;
module_param(simdisk_count, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(simdisk_count, "Number of simdisk units.");

अटल पूर्णांक n_files;
अटल स्थिर अक्षर *filename[MAX_SIMDISK_COUNT] = अणु
#अगर_घोषित CONFIG_SIMDISK0_खाताNAME
	CONFIG_SIMDISK0_खाताNAME,
#अगर_घोषित CONFIG_SIMDISK1_खाताNAME
	CONFIG_SIMDISK1_खाताNAME,
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक simdisk_param_set_filename(स्थिर अक्षर *val,
		स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (n_files < ARRAY_SIZE(filename))
		filename[n_files++] = val;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops simdisk_param_ops_filename = अणु
	.set = simdisk_param_set_filename,
पूर्ण;
module_param_cb(filename, &simdisk_param_ops_filename, &n_files, 0);
MODULE_PARM_DESC(filename, "Backing storage filename.");

अटल पूर्णांक simdisk_major = SIMDISK_MAJOR;

अटल व्योम simdisk_transfer(काष्ठा simdisk *dev, अचिन्हित दीर्घ sector,
		अचिन्हित दीर्घ nsect, अक्षर *buffer, पूर्णांक ग_लिखो)
अणु
	अचिन्हित दीर्घ offset = sector << SECTOR_SHIFT;
	अचिन्हित दीर्घ nbytes = nsect << SECTOR_SHIFT;

	अगर (offset > dev->size || dev->size - offset < nbytes) अणु
		pr_notice("Beyond-end %s (%ld %ld)\n",
				ग_लिखो ? "write" : "read", offset, nbytes);
		वापस;
	पूर्ण

	spin_lock(&dev->lock);
	जबतक (nbytes > 0) अणु
		अचिन्हित दीर्घ io;

		simc_lseek(dev->fd, offset, शुरू_से);
		READ_ONCE(*buffer);
		अगर (ग_लिखो)
			io = simc_ग_लिखो(dev->fd, buffer, nbytes);
		अन्यथा
			io = simc_पढ़ो(dev->fd, buffer, nbytes);
		अगर (io == -1) अणु
			pr_err("SIMDISK: IO error %d\n", त्रुटि_सं);
			अवरोध;
		पूर्ण
		buffer += io;
		offset += io;
		nbytes -= io;
	पूर्ण
	spin_unlock(&dev->lock);
पूर्ण

अटल blk_qc_t simdisk_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा simdisk *dev = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	sector_t sector = bio->bi_iter.bi_sector;

	bio_क्रम_each_segment(bvec, bio, iter) अणु
		अक्षर *buffer = kmap_atomic(bvec.bv_page) + bvec.bv_offset;
		अचिन्हित len = bvec.bv_len >> SECTOR_SHIFT;

		simdisk_transfer(dev, sector, len, buffer,
				bio_data_dir(bio) == WRITE);
		sector += len;
		kunmap_atomic(buffer);
	पूर्ण

	bio_endio(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक simdisk_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा simdisk *dev = bdev->bd_disk->निजी_data;

	spin_lock(&dev->lock);
	++dev->users;
	spin_unlock(&dev->lock);
	वापस 0;
पूर्ण

अटल व्योम simdisk_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा simdisk *dev = disk->निजी_data;
	spin_lock(&dev->lock);
	--dev->users;
	spin_unlock(&dev->lock);
पूर्ण

अटल स्थिर काष्ठा block_device_operations simdisk_ops = अणु
	.owner		= THIS_MODULE,
	.submit_bio	= simdisk_submit_bio,
	.खोलो		= simdisk_खोलो,
	.release	= simdisk_release,
पूर्ण;

अटल काष्ठा simdisk *sddev;
अटल काष्ठा proc_dir_entry *simdisk_procdir;

अटल पूर्णांक simdisk_attach(काष्ठा simdisk *dev, स्थिर अक्षर *filename)
अणु
	पूर्णांक err = 0;

	filename = kstrdup(filename, GFP_KERNEL);
	अगर (filename == शून्य)
		वापस -ENOMEM;

	spin_lock(&dev->lock);

	अगर (dev->fd != -1) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण
	dev->fd = simc_खोलो(filename, O_RDWR, 0);
	अगर (dev->fd == -1) अणु
		pr_err("SIMDISK: Can't open %s: %d\n", filename, त्रुटि_सं);
		err = -ENODEV;
		जाओ out;
	पूर्ण
	dev->size = simc_lseek(dev->fd, 0, अंत_से);
	set_capacity(dev->gd, dev->size >> SECTOR_SHIFT);
	dev->filename = filename;
	pr_info("SIMDISK: %s=%s\n", dev->gd->disk_name, dev->filename);
out:
	अगर (err)
		kमुक्त(filename);
	spin_unlock(&dev->lock);

	वापस err;
पूर्ण

अटल पूर्णांक simdisk_detach(काष्ठा simdisk *dev)
अणु
	पूर्णांक err = 0;

	spin_lock(&dev->lock);

	अगर (dev->users != 0) अणु
		err = -EBUSY;
	पूर्ण अन्यथा अगर (dev->fd != -1) अणु
		अगर (simc_बंद(dev->fd)) अणु
			pr_err("SIMDISK: error closing %s: %d\n",
					dev->filename, त्रुटि_सं);
			err = -EIO;
		पूर्ण अन्यथा अणु
			pr_info("SIMDISK: %s detached from %s\n",
					dev->gd->disk_name, dev->filename);
			dev->fd = -1;
			kमुक्त(dev->filename);
			dev->filename = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock(&dev->lock);
	वापस err;
पूर्ण

अटल sमाप_प्रकार proc_पढ़ो_simdisk(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा simdisk *dev = PDE_DATA(file_inode(file));
	स्थिर अक्षर *s = dev->filename;
	अगर (s) अणु
		sमाप_प्रकार n = simple_पढ़ो_from_buffer(buf, size, ppos,
							s, म_माप(s));
		अगर (n < 0)
			वापस n;
		buf += n;
		size -= n;
	पूर्ण
	वापस simple_पढ़ो_from_buffer(buf, size, ppos, "\n", 1);
पूर्ण

अटल sमाप_प्रकार proc_ग_लिखो_simdisk(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *पंचांगp = memdup_user_nul(buf, count);
	काष्ठा simdisk *dev = PDE_DATA(file_inode(file));
	पूर्णांक err;

	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);

	err = simdisk_detach(dev);
	अगर (err != 0)
		जाओ out_मुक्त;

	अगर (count > 0 && पंचांगp[count - 1] == '\n')
		पंचांगp[count - 1] = 0;

	अगर (पंचांगp[0])
		err = simdisk_attach(dev, पंचांगp);

	अगर (err == 0)
		err = count;
out_मुक्त:
	kमुक्त(पंचांगp);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा proc_ops simdisk_proc_ops = अणु
	.proc_पढ़ो	= proc_पढ़ो_simdisk,
	.proc_ग_लिखो	= proc_ग_लिखो_simdisk,
	.proc_lseek	= शेष_llseek,
पूर्ण;

अटल पूर्णांक __init simdisk_setup(काष्ठा simdisk *dev, पूर्णांक which,
		काष्ठा proc_dir_entry *procdir)
अणु
	अक्षर पंचांगp[2] = अणु '0' + which, 0 पूर्ण;

	dev->fd = -1;
	dev->filename = शून्य;
	spin_lock_init(&dev->lock);
	dev->users = 0;

	dev->queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (dev->queue == शून्य) अणु
		pr_err("blk_alloc_queue failed\n");
		जाओ out_alloc_queue;
	पूर्ण

	dev->gd = alloc_disk(SIMDISK_MINORS);
	अगर (dev->gd == शून्य) अणु
		pr_err("alloc_disk failed\n");
		जाओ out_alloc_disk;
	पूर्ण
	dev->gd->major = simdisk_major;
	dev->gd->first_minor = which;
	dev->gd->fops = &simdisk_ops;
	dev->gd->queue = dev->queue;
	dev->gd->निजी_data = dev;
	snम_लिखो(dev->gd->disk_name, 32, "simdisk%d", which);
	set_capacity(dev->gd, 0);
	add_disk(dev->gd);

	dev->procfile = proc_create_data(पंचांगp, 0644, procdir, &simdisk_proc_ops, dev);
	वापस 0;

out_alloc_disk:
	blk_cleanup_queue(dev->queue);
	dev->queue = शून्य;
out_alloc_queue:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __init simdisk_init(व्योम)
अणु
	पूर्णांक i;

	अगर (रेजिस्टर_blkdev(simdisk_major, "simdisk") < 0) अणु
		pr_err("SIMDISK: register_blkdev: %d\n", simdisk_major);
		वापस -EIO;
	पूर्ण
	pr_info("SIMDISK: major: %d\n", simdisk_major);

	अगर (n_files > simdisk_count)
		simdisk_count = n_files;
	अगर (simdisk_count > MAX_SIMDISK_COUNT)
		simdisk_count = MAX_SIMDISK_COUNT;

	sddev = kदो_स्मृति_array(simdisk_count, माप(*sddev), GFP_KERNEL);
	अगर (sddev == शून्य)
		जाओ out_unरेजिस्टर;

	simdisk_procdir = proc_सूची_गढ़ो("simdisk", 0);
	अगर (simdisk_procdir == शून्य)
		जाओ out_मुक्त_unरेजिस्टर;

	क्रम (i = 0; i < simdisk_count; ++i) अणु
		अगर (simdisk_setup(sddev + i, i, simdisk_procdir) == 0) अणु
			अगर (filename[i] != शून्य && filename[i][0] != 0 &&
					(n_files == 0 || i < n_files))
				simdisk_attach(sddev + i, filename[i]);
		पूर्ण
	पूर्ण

	वापस 0;

out_मुक्त_unरेजिस्टर:
	kमुक्त(sddev);
out_unरेजिस्टर:
	unरेजिस्टर_blkdev(simdisk_major, "simdisk");
	वापस -ENOMEM;
पूर्ण
module_init(simdisk_init);

अटल व्योम simdisk_tearकरोwn(काष्ठा simdisk *dev, पूर्णांक which,
		काष्ठा proc_dir_entry *procdir)
अणु
	अक्षर पंचांगp[2] = अणु '0' + which, 0 पूर्ण;

	simdisk_detach(dev);
	अगर (dev->gd)
		del_gendisk(dev->gd);
	अगर (dev->queue)
		blk_cleanup_queue(dev->queue);
	हटाओ_proc_entry(पंचांगp, procdir);
पूर्ण

अटल व्योम __निकास simdisk_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < simdisk_count; ++i)
		simdisk_tearकरोwn(sddev + i, i, simdisk_procdir);
	हटाओ_proc_entry("simdisk", 0);
	kमुक्त(sddev);
	unरेजिस्टर_blkdev(simdisk_major, "simdisk");
पूर्ण
module_निकास(simdisk_निकास);

MODULE_ALIAS_BLOCKDEV_MAJOR(SIMDISK_MAJOR);

MODULE_LICENSE("GPL");
