<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम the N64 cart.
 *
 * Copyright (c) 2021 Lauri Kasanen
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/bitops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

क्रमागत अणु
	PI_DRAM_REG = 0,
	PI_CART_REG,
	PI_READ_REG,
	PI_WRITE_REG,
	PI_STATUS_REG,
पूर्ण;

#घोषणा PI_STATUS_DMA_BUSY	(1 << 0)
#घोषणा PI_STATUS_IO_BUSY	(1 << 1)

#घोषणा CART_DOMAIN		0x10000000
#घोषणा CART_MAX		0x1FFFFFFF

#घोषणा MIN_ALIGNMENT		8

अटल u32 __iomem *reg_base;

अटल अचिन्हित पूर्णांक start;
module_param(start, uपूर्णांक, 0);
MODULE_PARM_DESC(start, "Start address of the cart block data");

अटल अचिन्हित पूर्णांक size;
module_param(size, uपूर्णांक, 0);
MODULE_PARM_DESC(size, "Size of the cart block data, in bytes");

अटल व्योम n64cart_ग_लिखो_reg(स्थिर u8 reg, स्थिर u32 value)
अणु
	ग_लिखोl(value, reg_base + reg);
पूर्ण

अटल u32 n64cart_पढ़ो_reg(स्थिर u8 reg)
अणु
	वापस पढ़ोl(reg_base + reg);
पूर्ण

अटल व्योम n64cart_रुको_dma(व्योम)
अणु
	जबतक (n64cart_पढ़ो_reg(PI_STATUS_REG) &
		(PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY))
		cpu_relax();
पूर्ण

/*
 * Process a single bvec of a bio.
 */
अटल bool n64cart_करो_bvec(काष्ठा device *dev, काष्ठा bio_vec *bv, u32 pos)
अणु
	dma_addr_t dma_addr;
	स्थिर u32 bstart = pos + start;

	/* Alignment check */
	WARN_ON_ONCE((bv->bv_offset & (MIN_ALIGNMENT - 1)) ||
		     (bv->bv_len & (MIN_ALIGNMENT - 1)));

	dma_addr = dma_map_bvec(dev, bv, DMA_FROM_DEVICE, 0);
	अगर (dma_mapping_error(dev, dma_addr))
		वापस false;

	n64cart_रुको_dma();

	n64cart_ग_लिखो_reg(PI_DRAM_REG, dma_addr + bv->bv_offset);
	n64cart_ग_लिखो_reg(PI_CART_REG, (bstart | CART_DOMAIN) & CART_MAX);
	n64cart_ग_लिखो_reg(PI_WRITE_REG, bv->bv_len - 1);

	n64cart_रुको_dma();

	dma_unmap_page(dev, dma_addr, bv->bv_len, DMA_FROM_DEVICE);
	वापस true;
पूर्ण

अटल blk_qc_t n64cart_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	काष्ठा device *dev = bio->bi_disk->निजी_data;
	u32 pos = bio->bi_iter.bi_sector << SECTOR_SHIFT;

	bio_क्रम_each_segment(bvec, bio, iter) अणु
		अगर (!n64cart_करो_bvec(dev, &bvec, pos))
			जाओ io_error;
		pos += bvec.bv_len;
	पूर्ण

	bio_endio(bio);
	वापस BLK_QC_T_NONE;
io_error:
	bio_io_error(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल स्थिर काष्ठा block_device_operations n64cart_fops = अणु
	.owner		= THIS_MODULE,
	.submit_bio	= n64cart_submit_bio,
पूर्ण;

/*
 * The target device is embedded and RAM-स्थिरrained. We save RAM
 * by initializing in __init code that माला_लो dropped late in boot.
 * For the same reason there is no module or unloading support.
 */
अटल पूर्णांक __init n64cart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gendisk *disk;

	अगर (!start || !size) अणु
		pr_err("start or size not specified\n");
		वापस -ENODEV;
	पूर्ण

	अगर (size & 4095) अणु
		pr_err("size must be a multiple of 4K\n");
		वापस -ENODEV;
	पूर्ण

	reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (!reg_base)
		वापस -EINVAL;

	disk = alloc_disk(0);
	अगर (!disk)
		वापस -ENOMEM;

	disk->queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!disk->queue)
		वापस -ENOMEM;

	disk->first_minor = 0;
	disk->flags = GENHD_FL_NO_PART_SCAN | GENHD_FL_EXT_DEVT;
	disk->fops = &n64cart_fops;
	disk->निजी_data = &pdev->dev;
	म_नकल(disk->disk_name, "n64cart");

	set_capacity(disk, size >> SECTOR_SHIFT);
	set_disk_ro(disk, 1);

	blk_queue_flag_set(QUEUE_FLAG_NONROT, disk->queue);
	blk_queue_physical_block_size(disk->queue, 4096);
	blk_queue_logical_block_size(disk->queue, 4096);

	add_disk(disk);

	pr_info("n64cart: %u kb disk\n", size / 1024);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver n64cart_driver = अणु
	.driver = अणु
		.name = "n64cart",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init n64cart_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&n64cart_driver, n64cart_probe);
पूर्ण

module_init(n64cart_init);

MODULE_AUTHOR("Lauri Kasanen <cand@gmx.com>");
MODULE_DESCRIPTION("Driver for the N64 cart");
MODULE_LICENSE("GPL");
