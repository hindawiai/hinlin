<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BCM63XX CFE image tag parser
 *
 * Copyright तऊ 2006-2008  Florian Fainelli <florian@खोलोwrt.org>
 *			  Mike Albon <malbon@खोलोwrt.org>
 * Copyright तऊ 2009-2010  Daniel Dickinson <खोलोwrt@cshore.neomailbox.net>
 * Copyright तऊ 2011-2013  Jonas Gorski <jonas.gorski@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bcm963xx_tag.h>
#समावेश <linux/crc32.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of.h>

/* Ensure strings पढ़ो from flash काष्ठाs are null terminated */
#घोषणा STR_शून्य_TERMINATE(x) \
	करो अणु अक्षर *_str = (x); _str[माप(x) - 1] = 0; पूर्ण जबतक (0)

अटल पूर्णांक bcm963xx_पढ़ो_imagetag(काष्ठा mtd_info *master, स्थिर अक्षर *name,
	loff_t tag_offset, काष्ठा bcm_tag *buf)
अणु
	पूर्णांक ret;
	माप_प्रकार retlen;
	u32 computed_crc;

	ret = mtd_पढ़ो(master, tag_offset, माप(*buf), &retlen, (व्योम *)buf);
	अगर (ret)
		वापस ret;

	अगर (retlen != माप(*buf))
		वापस -EIO;

	computed_crc = crc32_le(IMAGETAG_CRC_START, (u8 *)buf,
				दुरत्व(काष्ठा bcm_tag, header_crc));
	अगर (computed_crc == buf->header_crc) अणु
		STR_शून्य_TERMINATE(buf->board_id);
		STR_शून्य_TERMINATE(buf->tag_version);

		pr_info("%s: CFE image tag found at 0x%llx with version %s, board type %s\n",
			name, tag_offset, buf->tag_version, buf->board_id);

		वापस 0;
	पूर्ण

	pr_warn("%s: CFE image tag at 0x%llx CRC invalid (expected %08x, actual %08x)\n",
		name, tag_offset, buf->header_crc, computed_crc);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bcm963xx_parse_imagetag_partitions(काष्ठा mtd_info *master,
					स्थिर काष्ठा mtd_partition **pparts,
					काष्ठा mtd_part_parser_data *data)
अणु
	/* CFE, NVRAM and global Linux are always present */
	पूर्णांक nrparts = 0, curpart = 0;
	काष्ठा bcm_tag *buf = शून्य;
	काष्ठा mtd_partition *parts;
	पूर्णांक ret;
	अचिन्हित पूर्णांक rootfsaddr, kerneladdr, spaपढ़ोdr, offset;
	अचिन्हित पूर्णांक rootfslen, kernellen, sparelen, totallen;
	पूर्णांक i;
	bool rootfs_first = false;

	buf = vदो_स्मृति(माप(काष्ठा bcm_tag));
	अगर (!buf)
		वापस -ENOMEM;

	/* Get the tag */
	ret = bcm963xx_पढ़ो_imagetag(master, "rootfs", 0, buf);
	अगर (!ret) अणु
		STR_शून्य_TERMINATE(buf->flash_image_start);
		अगर (kstrtouपूर्णांक(buf->flash_image_start, 10, &rootfsaddr) ||
				rootfsaddr < BCM963XX_EXTENDED_SIZE) अणु
			pr_err("invalid rootfs address: %*ph\n",
				(पूर्णांक)माप(buf->flash_image_start),
				buf->flash_image_start);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		STR_शून्य_TERMINATE(buf->kernel_address);
		अगर (kstrtouपूर्णांक(buf->kernel_address, 10, &kerneladdr) ||
				kerneladdr < BCM963XX_EXTENDED_SIZE) अणु
			pr_err("invalid kernel address: %*ph\n",
				(पूर्णांक)माप(buf->kernel_address),
				buf->kernel_address);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		STR_शून्य_TERMINATE(buf->kernel_length);
		अगर (kstrtouपूर्णांक(buf->kernel_length, 10, &kernellen)) अणु
			pr_err("invalid kernel length: %*ph\n",
				(पूर्णांक)माप(buf->kernel_length),
				buf->kernel_length);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		STR_शून्य_TERMINATE(buf->total_length);
		अगर (kstrtouपूर्णांक(buf->total_length, 10, &totallen)) अणु
			pr_err("invalid total length: %*ph\n",
				(पूर्णांक)माप(buf->total_length),
				buf->total_length);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * Addresses are flash असलolute, so convert to partition
		 * relative addresses. Assume either kernel or rootfs will
		 * directly follow the image tag.
		 */
		अगर (rootfsaddr < kerneladdr)
			offset = rootfsaddr - माप(काष्ठा bcm_tag);
		अन्यथा
			offset = kerneladdr - माप(काष्ठा bcm_tag);

		kerneladdr = kerneladdr - offset;
		rootfsaddr = rootfsaddr - offset;
		spaपढ़ोdr = roundup(totallen, master->erasesize);

		अगर (rootfsaddr < kerneladdr) अणु
			/* शेष Broadcom layout */
			rootfslen = kerneladdr - rootfsaddr;
			rootfs_first = true;
		पूर्ण अन्यथा अणु
			/* OpenWrt layout */
			rootfsaddr = kerneladdr + kernellen;
			rootfslen = spaपढ़ोdr - rootfsaddr;
		पूर्ण
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण
	sparelen = master->size - spaपढ़ोdr;

	/* Determine number of partitions */
	अगर (rootfslen > 0)
		nrparts++;

	अगर (kernellen > 0)
		nrparts++;

	parts = kzalloc(माप(*parts) * nrparts + 10 * nrparts, GFP_KERNEL);
	अगर (!parts) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Start building partition list */
	अगर (kernellen > 0) अणु
		पूर्णांक kernelpart = curpart;

		अगर (rootfslen > 0 && rootfs_first)
			kernelpart++;
		parts[kernelpart].name = "kernel";
		parts[kernelpart].offset = kerneladdr;
		parts[kernelpart].size = kernellen;
		curpart++;
	पूर्ण

	अगर (rootfslen > 0) अणु
		पूर्णांक rootfspart = curpart;

		अगर (kernellen > 0 && rootfs_first)
			rootfspart--;
		parts[rootfspart].name = "rootfs";
		parts[rootfspart].offset = rootfsaddr;
		parts[rootfspart].size = rootfslen;
		अगर (sparelen > 0  && !rootfs_first)
			parts[rootfspart].size += sparelen;
		curpart++;
	पूर्ण

	क्रम (i = 0; i < nrparts; i++)
		pr_info("Partition %d is %s offset %llx and length %llx\n", i,
			parts[i].name, parts[i].offset,	parts[i].size);

	pr_info("Spare partition is offset %x and length %x\n",	spaपढ़ोdr,
		sparelen);

	*pparts = parts;
	ret = 0;

out:
	vमुक्त(buf);

	अगर (ret)
		वापस ret;

	वापस nrparts;
पूर्ण

अटल स्थिर काष्ठा of_device_id parse_bcm963xx_imagetag_match_table[] = अणु
	अणु .compatible = "brcm,bcm963xx-imagetag" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, parse_bcm963xx_imagetag_match_table);

अटल काष्ठा mtd_part_parser bcm963xx_imagetag_parser = अणु
	.parse_fn = bcm963xx_parse_imagetag_partitions,
	.name = "bcm963xx-imagetag",
	.of_match_table = parse_bcm963xx_imagetag_match_table,
पूर्ण;
module_mtd_part_parser(bcm963xx_imagetag_parser);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Dickinson <openwrt@cshore.neomailbox.net>");
MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_AUTHOR("Mike Albon <malbon@openwrt.org>");
MODULE_AUTHOR("Jonas Gorski <jonas.gorski@gmail.com>");
MODULE_DESCRIPTION("MTD parser for BCM963XX CFE Image Tag partitions");
