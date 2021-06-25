<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xpram.c -- the S/390 expanded memory RAM-disk
 *           
 * signअगरicant parts of this code are based on
 * the sbull device driver presented in
 * A. Rubini: Linux Device Drivers
 *
 * Author of XPRAM specअगरic coding: Reinhard Buendgen
 *                                  buendgen@de.ibm.com
 * Reग_लिखो क्रम 2.5: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *
 * External पूर्णांकerfaces:
 *   Interfaces to linux kernel
 *        xpram_setup: पढ़ो kernel parameters
 *   Device specअगरic file operations
 *        xpram_iotcl
 *        xpram_खोलो
 *
 * "ad-hoc" partitioning:
 *    the expanded memory can be partitioned among several devices 
 *    (with dअगरferent minors). The partitioning set up can be
 *    set by kernel or module parameters (पूर्णांक devs & पूर्णांक sizes[])
 *
 * Potential future improvements:
 *   generic hard disk support to replace ad-hoc partitioning
 */

#घोषणा KMSG_COMPONENT "xpram"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/प्रकार.स>  /* है_अंक, है_षष्ठादशक */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/hdreg.h>  /* HDIO_GETGEO */
#समावेश <linux/device.h>
#समावेश <linux/bपन.स>
#समावेश <linux/suspend.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/uaccess.h>

#घोषणा XPRAM_NAME	"xpram"
#घोषणा XPRAM_DEVS	1	/* one partition */
#घोषणा XPRAM_MAX_DEVS	32	/* maximal number of devices (partitions) */

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक	size;		/* size of xpram segment in pages */
	अचिन्हित पूर्णांक	offset;		/* start page of xpram segment */
पूर्ण xpram_device_t;

अटल xpram_device_t xpram_devices[XPRAM_MAX_DEVS];
अटल अचिन्हित पूर्णांक xpram_sizes[XPRAM_MAX_DEVS];
अटल काष्ठा gendisk *xpram_disks[XPRAM_MAX_DEVS];
अटल काष्ठा request_queue *xpram_queues[XPRAM_MAX_DEVS];
अटल अचिन्हित पूर्णांक xpram_pages;
अटल पूर्णांक xpram_devs;

/*
 * Parameter parsing functions.
 */
अटल पूर्णांक devs = XPRAM_DEVS;
अटल अक्षर *sizes[XPRAM_MAX_DEVS];

module_param(devs, पूर्णांक, 0);
module_param_array(sizes, अक्षरp, शून्य, 0);

MODULE_PARM_DESC(devs, "number of devices (\"partitions\"), " \
		 "the default is " __MODULE_STRING(XPRAM_DEVS) "\n");
MODULE_PARM_DESC(sizes, "list of device (partition) sizes " \
		 "the defaults are 0s \n" \
		 "All devices with size 0 equally partition the "
		 "remaining space on the expanded strorage not "
		 "claimed by explicit sizes\n");
MODULE_LICENSE("GPL");

/*
 * Copy expanded memory page (4kB) पूर्णांकo मुख्य memory                  
 * Arguments                                                         
 *           page_addr:    address of target page                    
 *           xpage_index:  index of expandeded memory page           
 * Return value                                                      
 *           0:            अगर operation succeeds
 *           -EIO:         अगर pgin failed
 *           -ENXIO:       अगर xpram has vanished
 */
अटल पूर्णांक xpram_page_in (अचिन्हित दीर्घ page_addr, अचिन्हित पूर्णांक xpage_index)
अणु
	पूर्णांक cc = 2;	/* वापस unused cc 2 अगर pgin traps */

	यंत्र अस्थिर(
		"	.insn	rre,0xb22e0000,%1,%2\n"  /* pgin %1,%2 */
		"0:	ipm	%0\n"
		"	srl	%0,28\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "+d" (cc) : "a" (__pa(page_addr)), "d" (xpage_index) : "cc");
	अगर (cc == 3)
		वापस -ENXIO;
	अगर (cc == 2)
		वापस -ENXIO;
	अगर (cc == 1)
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * Copy a 4kB page of मुख्य memory to an expanded memory page          
 * Arguments                                                          
 *           page_addr:    address of source page                     
 *           xpage_index:  index of expandeded memory page            
 * Return value                                                       
 *           0:            अगर operation succeeds
 *           -EIO:         अगर pgout failed
 *           -ENXIO:       अगर xpram has vanished
 */
अटल दीर्घ xpram_page_out (अचिन्हित दीर्घ page_addr, अचिन्हित पूर्णांक xpage_index)
अणु
	पूर्णांक cc = 2;	/* वापस unused cc 2 अगर pgin traps */

	यंत्र अस्थिर(
		"	.insn	rre,0xb22f0000,%1,%2\n"  /* pgout %1,%2 */
		"0:	ipm	%0\n"
		"	srl	%0,28\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "+d" (cc) : "a" (__pa(page_addr)), "d" (xpage_index) : "cc");
	अगर (cc == 3)
		वापस -ENXIO;
	अगर (cc == 2)
		वापस -ENXIO;
	अगर (cc == 1)
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * Check अगर xpram is available.
 */
अटल पूर्णांक xpram_present(व्योम)
अणु
	अचिन्हित दीर्घ mem_page;
	पूर्णांक rc;

	mem_page = (अचिन्हित दीर्घ) __get_मुक्त_page(GFP_KERNEL);
	अगर (!mem_page)
		वापस -ENOMEM;
	rc = xpram_page_in(mem_page, 0);
	मुक्त_page(mem_page);
	वापस rc ? -ENXIO : 0;
पूर्ण

/*
 * Return index of the last available xpram page.
 */
अटल अचिन्हित दीर्घ xpram_highest_page_index(व्योम)
अणु
	अचिन्हित पूर्णांक page_index, add_bit;
	अचिन्हित दीर्घ mem_page;

	mem_page = (अचिन्हित दीर्घ) __get_मुक्त_page(GFP_KERNEL);
	अगर (!mem_page)
		वापस 0;

	page_index = 0;
	add_bit = 1ULL << (माप(अचिन्हित पूर्णांक)*8 - 1);
	जबतक (add_bit > 0) अणु
		अगर (xpram_page_in(mem_page, page_index | add_bit) == 0)
			page_index |= add_bit;
		add_bit >>= 1;
	पूर्ण

	मुक्त_page (mem_page);

	वापस page_index;
पूर्ण

/*
 * Block device make request function.
 */
अटल blk_qc_t xpram_submit_bio(काष्ठा bio *bio)
अणु
	xpram_device_t *xdev = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	अचिन्हित पूर्णांक index;
	अचिन्हित दीर्घ page_addr;
	अचिन्हित दीर्घ bytes;

	blk_queue_split(&bio);

	अगर ((bio->bi_iter.bi_sector & 7) != 0 ||
	    (bio->bi_iter.bi_size & 4095) != 0)
		/* Request is not page-aligned. */
		जाओ fail;
	अगर ((bio->bi_iter.bi_size >> 12) > xdev->size)
		/* Request size is no page-aligned. */
		जाओ fail;
	अगर ((bio->bi_iter.bi_sector >> 3) > 0xffffffffU - xdev->offset)
		जाओ fail;
	index = (bio->bi_iter.bi_sector >> 3) + xdev->offset;
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		page_addr = (अचिन्हित दीर्घ)
			kmap(bvec.bv_page) + bvec.bv_offset;
		bytes = bvec.bv_len;
		अगर ((page_addr & 4095) != 0 || (bytes & 4095) != 0)
			/* More paranoia. */
			जाओ fail;
		जबतक (bytes > 0) अणु
			अगर (bio_data_dir(bio) == READ) अणु
				अगर (xpram_page_in(page_addr, index) != 0)
					जाओ fail;
			पूर्ण अन्यथा अणु
				अगर (xpram_page_out(page_addr, index) != 0)
					जाओ fail;
			पूर्ण
			page_addr += 4096;
			bytes -= 4096;
			index++;
		पूर्ण
	पूर्ण
	bio_endio(bio);
	वापस BLK_QC_T_NONE;
fail:
	bio_io_error(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक xpram_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	अचिन्हित दीर्घ size;

	/*
	 * get geometry: we have to fake one...  trim the size to a
	 * multiple of 64 (32k): tell we have 16 sectors, 4 heads,
	 * whatever cylinders. Tell also that data starts at sector. 4.
	 */
	size = (xpram_pages * 8) & ~0x3f;
	geo->cylinders = size >> 6;
	geo->heads = 4;
	geo->sectors = 16;
	geo->start = 4;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations xpram_devops =
अणु
	.owner	= THIS_MODULE,
	.submit_bio = xpram_submit_bio,
	.getgeo	= xpram_getgeo,
पूर्ण;

/*
 * Setup xpram_sizes array.
 */
अटल पूर्णांक __init xpram_setup_sizes(अचिन्हित दीर्घ pages)
अणु
	अचिन्हित दीर्घ mem_needed;
	अचिन्हित दीर्घ mem_स्वतः;
	अचिन्हित दीर्घ दीर्घ size;
	अक्षर *sizes_end;
	पूर्णांक mem_स्वतः_no;
	पूर्णांक i;

	/* Check number of devices. */
	अगर (devs <= 0 || devs > XPRAM_MAX_DEVS) अणु
		pr_err("%d is not a valid number of XPRAM devices\n",devs);
		वापस -EINVAL;
	पूर्ण
	xpram_devs = devs;

	/*
	 * Copy sizes array to xpram_sizes and align partition
	 * sizes to page boundary.
	 */
	mem_needed = 0;
	mem_स्वतः_no = 0;
	क्रम (i = 0; i < xpram_devs; i++) अणु
		अगर (sizes[i]) अणु
			size = simple_म_से_अदीर्घl(sizes[i], &sizes_end, 0);
			चयन (*sizes_end) अणु
			हाल 'g':
			हाल 'G':
				size <<= 20;
				अवरोध;
			हाल 'm':
			हाल 'M':
				size <<= 10;
			पूर्ण
			xpram_sizes[i] = (size + 3) & -4UL;
		पूर्ण
		अगर (xpram_sizes[i])
			mem_needed += xpram_sizes[i];
		अन्यथा
			mem_स्वतः_no++;
	पूर्ण
	
	pr_info("  number of devices (partitions): %d \n", xpram_devs);
	क्रम (i = 0; i < xpram_devs; i++) अणु
		अगर (xpram_sizes[i])
			pr_info("  size of partition %d: %u kB\n",
				i, xpram_sizes[i]);
		अन्यथा
			pr_info("  size of partition %d to be set "
				"automatically\n",i);
	पूर्ण
	pr_info("  memory needed (for sized partitions): %lu kB\n",
		mem_needed);
	pr_info("  partitions to be sized automatically: %d\n",
		mem_स्वतः_no);

	अगर (mem_needed > pages * 4) अणु
		pr_err("Not enough expanded memory available\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * partitioning:
	 * xpram_sizes[i] != 0; partition i has size xpram_sizes[i] kB
	 * अन्यथा:             ; all partitions with zero xpram_sizes[i]
	 *                     partition equally the reमुख्यing space
	 */
	अगर (mem_स्वतः_no) अणु
		mem_स्वतः = ((pages - mem_needed / 4) / mem_स्वतः_no) * 4;
		pr_info("  automatically determined "
			"partition size: %lu kB\n", mem_स्वतः);
		क्रम (i = 0; i < xpram_devs; i++)
			अगर (xpram_sizes[i] == 0)
				xpram_sizes[i] = mem_स्वतः;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init xpram_setup_blkdev(व्योम)
अणु
	अचिन्हित दीर्घ offset;
	पूर्णांक i, rc = -ENOMEM;

	क्रम (i = 0; i < xpram_devs; i++) अणु
		xpram_disks[i] = alloc_disk(1);
		अगर (!xpram_disks[i])
			जाओ out;
		xpram_queues[i] = blk_alloc_queue(NUMA_NO_NODE);
		अगर (!xpram_queues[i]) अणु
			put_disk(xpram_disks[i]);
			जाओ out;
		पूर्ण
		blk_queue_flag_set(QUEUE_FLAG_NONROT, xpram_queues[i]);
		blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, xpram_queues[i]);
		blk_queue_logical_block_size(xpram_queues[i], 4096);
	पूर्ण

	/*
	 * Register xpram major.
	 */
	rc = रेजिस्टर_blkdev(XPRAM_MAJOR, XPRAM_NAME);
	अगर (rc < 0)
		जाओ out;

	/*
	 * Setup device काष्ठाures.
	 */
	offset = 0;
	क्रम (i = 0; i < xpram_devs; i++) अणु
		काष्ठा gendisk *disk = xpram_disks[i];

		xpram_devices[i].size = xpram_sizes[i] / 4;
		xpram_devices[i].offset = offset;
		offset += xpram_devices[i].size;
		disk->major = XPRAM_MAJOR;
		disk->first_minor = i;
		disk->fops = &xpram_devops;
		disk->निजी_data = &xpram_devices[i];
		disk->queue = xpram_queues[i];
		प्र_लिखो(disk->disk_name, "slram%d", i);
		set_capacity(disk, xpram_sizes[i] << 1);
		add_disk(disk);
	पूर्ण

	वापस 0;
out:
	जबतक (i--) अणु
		blk_cleanup_queue(xpram_queues[i]);
		put_disk(xpram_disks[i]);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Resume failed: Prपूर्णांक error message and call panic.
 */
अटल व्योम xpram_resume_error(स्थिर अक्षर *message)
अणु
	pr_err("Resuming the system failed: %s\n", message);
	panic("xpram resume error\n");
पूर्ण

/*
 * Check अगर xpram setup changed between suspend and resume.
 */
अटल पूर्णांक xpram_restore(काष्ठा device *dev)
अणु
	अगर (!xpram_pages)
		वापस 0;
	अगर (xpram_present() != 0)
		xpram_resume_error("xpram disappeared");
	अगर (xpram_pages != xpram_highest_page_index() + 1)
		xpram_resume_error("Size of xpram changed");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xpram_pm_ops = अणु
	.restore	= xpram_restore,
पूर्ण;

अटल काष्ठा platक्रमm_driver xpram_pdrv = अणु
	.driver = अणु
		.name	= XPRAM_NAME,
		.pm	= &xpram_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *xpram_pdev;

/*
 * Finally, the init/निकास functions.
 */
अटल व्योम __निकास xpram_निकास(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < xpram_devs; i++) अणु
		del_gendisk(xpram_disks[i]);
		blk_cleanup_queue(xpram_queues[i]);
		put_disk(xpram_disks[i]);
	पूर्ण
	unरेजिस्टर_blkdev(XPRAM_MAJOR, XPRAM_NAME);
	platक्रमm_device_unरेजिस्टर(xpram_pdev);
	platक्रमm_driver_unरेजिस्टर(&xpram_pdrv);
पूर्ण

अटल पूर्णांक __init xpram_init(व्योम)
अणु
	पूर्णांक rc;

	/* Find out size of expanded memory. */
	अगर (xpram_present() != 0) अणु
		pr_err("No expanded memory available\n");
		वापस -ENODEV;
	पूर्ण
	xpram_pages = xpram_highest_page_index() + 1;
	pr_info("  %u pages expanded memory found (%lu KB).\n",
		xpram_pages, (अचिन्हित दीर्घ) xpram_pages*4);
	rc = xpram_setup_sizes(xpram_pages);
	अगर (rc)
		वापस rc;
	rc = platक्रमm_driver_रेजिस्टर(&xpram_pdrv);
	अगर (rc)
		वापस rc;
	xpram_pdev = platक्रमm_device_रेजिस्टर_simple(XPRAM_NAME, -1, शून्य, 0);
	अगर (IS_ERR(xpram_pdev)) अणु
		rc = PTR_ERR(xpram_pdev);
		जाओ fail_platक्रमm_driver_unरेजिस्टर;
	पूर्ण
	rc = xpram_setup_blkdev();
	अगर (rc)
		जाओ fail_platक्रमm_device_unरेजिस्टर;
	वापस 0;

fail_platक्रमm_device_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(xpram_pdev);
fail_platक्रमm_driver_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&xpram_pdrv);
	वापस rc;
पूर्ण

module_init(xpram_init);
module_निकास(xpram_निकास);
