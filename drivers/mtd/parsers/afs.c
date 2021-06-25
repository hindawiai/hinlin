<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*======================================================================

    drivers/mtd/afs.c: ARM Flash Layout/Partitioning

    Copyright तऊ 2000 ARM Limited
    Copyright (C) 2019 Linus Walleij


   This is access code क्रम flashes using ARM's flash partitioning
   standards.

======================================================================*/

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

#घोषणा AFSV1_FOOTER_MAGIC 0xA0FFFF9F
#घोषणा AFSV2_FOOTER_MAGIC1 0x464C5348 /* "FLSH" */
#घोषणा AFSV2_FOOTER_MAGIC2 0x464F4F54 /* "FOOT" */

काष्ठा footer_v1 अणु
	u32 image_info_base;	/* Address of first word of ImageFooter  */
	u32 image_start;	/* Start of area reserved by this footer */
	u32 signature;		/* 'Magic' number proves it's a footer   */
	u32 type;		/* Area type: ARM Image, SIB, customer   */
	u32 checksum;		/* Just this काष्ठाure                   */
पूर्ण;

काष्ठा image_info_v1 अणु
	u32 bootFlags;		/* Boot flags, compression etc.          */
	u32 imageNumber;	/* Unique number, selects क्रम boot etc.  */
	u32 loadAddress;	/* Address program should be loaded to   */
	u32 length;		/* Actual size of image                  */
	u32 address;		/* Image is executed from here           */
	अक्षर name[16];		/* Null terminated                       */
	u32 headerBase;		/* Flash Address of any stripped header  */
	u32 header_length;	/* Length of header in memory            */
	u32 headerType;		/* AIF, RLF, s-record etc.               */
	u32 checksum;		/* Image checksum (inc. this काष्ठा)     */
पूर्ण;

अटल u32 word_sum(व्योम *words, पूर्णांक num)
अणु
	u32 *p = words;
	u32 sum = 0;

	जबतक (num--)
		sum += *p++;

	वापस sum;
पूर्ण

अटल u32 word_sum_v2(u32 *p, u32 num)
अणु
	u32 sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		u32 val;

		val = p[i];
		अगर (val > ~sum)
			sum++;
		sum += val;
	पूर्ण
	वापस ~sum;
पूर्ण

अटल bool afs_is_v1(काष्ठा mtd_info *mtd, u_पूर्णांक off)
अणु
	/* The magic is 12 bytes from the end of the erase block */
	u_पूर्णांक ptr = off + mtd->erasesize - 12;
	u32 magic;
	माप_प्रकार sz;
	पूर्णांक ret;

	ret = mtd_पढ़ो(mtd, ptr, 4, &sz, (u_अक्षर *)&magic);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "AFS: mtd read failed at 0x%x: %d\n",
		       ptr, ret);
		वापस false;
	पूर्ण
	अगर (ret >= 0 && sz != 4)
		वापस false;

	वापस (magic == AFSV1_FOOTER_MAGIC);
पूर्ण

अटल bool afs_is_v2(काष्ठा mtd_info *mtd, u_पूर्णांक off)
अणु
	/* The magic is the 8 last bytes of the erase block */
	u_पूर्णांक ptr = off + mtd->erasesize - 8;
	u32 foot[2];
	माप_प्रकार sz;
	पूर्णांक ret;

	ret = mtd_पढ़ो(mtd, ptr, 8, &sz, (u_अक्षर *)foot);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "AFS: mtd read failed at 0x%x: %d\n",
		       ptr, ret);
		वापस false;
	पूर्ण
	अगर (ret >= 0 && sz != 8)
		वापस false;

	वापस (foot[0] == AFSV2_FOOTER_MAGIC1 &&
		foot[1] == AFSV2_FOOTER_MAGIC2);
पूर्ण

अटल पूर्णांक afs_parse_v1_partition(काष्ठा mtd_info *mtd,
				  u_पूर्णांक off, काष्ठा mtd_partition *part)
अणु
	काष्ठा footer_v1 fs;
	काष्ठा image_info_v1 iis;
	u_पूर्णांक mask;
	/*
	 * Static checks cannot see that we bail out अगर we have an error
	 * पढ़ोing the footer.
	 */
	u_पूर्णांक iis_ptr;
	u_पूर्णांक img_ptr;
	u_पूर्णांक ptr;
	माप_प्रकार sz;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * This is the address mask; we use this to mask off out of
	 * range address bits.
	 */
	mask = mtd->size - 1;

	ptr = off + mtd->erasesize - माप(fs);
	ret = mtd_पढ़ो(mtd, ptr, माप(fs), &sz, (u_अक्षर *)&fs);
	अगर (ret >= 0 && sz != माप(fs))
		ret = -EINVAL;
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "AFS: mtd read failed at 0x%x: %d\n",
		       ptr, ret);
		वापस ret;
	पूर्ण
	/*
	 * Check the checksum.
	 */
	अगर (word_sum(&fs, माप(fs) / माप(u32)) != 0xffffffff)
		वापस -EINVAL;

	/*
	 * Hide the SIB (System Inक्रमmation Block)
	 */
	अगर (fs.type == 2)
		वापस 0;

	iis_ptr = fs.image_info_base & mask;
	img_ptr = fs.image_start & mask;

	/*
	 * Check the image info base.  This can not
	 * be located after the footer काष्ठाure.
	 */
	अगर (iis_ptr >= ptr)
		वापस 0;

	/*
	 * Check the start of this image.  The image
	 * data can not be located after this block.
	 */
	अगर (img_ptr > off)
		वापस 0;

	/* Read the image info block */
	स_रखो(&iis, 0, माप(iis));
	ret = mtd_पढ़ो(mtd, iis_ptr, माप(iis), &sz, (u_अक्षर *)&iis);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "AFS: mtd read failed at 0x%x: %d\n",
		       iis_ptr, ret);
		वापस -EINVAL;
	पूर्ण

	अगर (sz != माप(iis))
		वापस -EINVAL;

	/*
	 * Validate the name - it must be NUL terminated.
	 */
	क्रम (i = 0; i < माप(iis.name); i++)
		अगर (iis.name[i] == '\0')
			अवरोध;
	अगर (i > माप(iis.name))
		वापस -EINVAL;

	part->name = kstrdup(iis.name, GFP_KERNEL);
	अगर (!part->name)
		वापस -ENOMEM;

	part->size = (iis.length + mtd->erasesize - 1) & ~(mtd->erasesize - 1);
	part->offset = img_ptr;
	part->mask_flags = 0;

	prपूर्णांकk("  mtd: at 0x%08x, %5lluKiB, %8u, %s\n",
	       img_ptr, part->size / 1024,
	       iis.imageNumber, part->name);

	वापस 0;
पूर्ण

अटल पूर्णांक afs_parse_v2_partition(काष्ठा mtd_info *mtd,
				  u_पूर्णांक off, काष्ठा mtd_partition *part)
अणु
	u_पूर्णांक ptr;
	u32 footer[12];
	u32 imginfo[36];
	अक्षर *name;
	u32 version;
	u32 entrypoपूर्णांक;
	u32 attributes;
	u32 region_count;
	u32 block_start;
	u32 block_end;
	u32 crc;
	माप_प्रकार sz;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक pad = 0;

	pr_debug("Parsing v2 partition @%08x-%08x\n",
		 off, off + mtd->erasesize);

	/* First पढ़ो the footer */
	ptr = off + mtd->erasesize - माप(footer);
	ret = mtd_पढ़ो(mtd, ptr, माप(footer), &sz, (u_अक्षर *)footer);
	अगर ((ret < 0) || (ret >= 0 && sz != माप(footer))) अणु
		pr_err("AFS: mtd read failed at 0x%x: %d\n",
		       ptr, ret);
		वापस -EIO;
	पूर्ण
	name = (अक्षर *) &footer[0];
	version = footer[9];
	ptr = off + mtd->erasesize - माप(footer) - footer[8];

	pr_debug("found image \"%s\", version %08x, info @%08x\n",
		 name, version, ptr);

	/* Then पढ़ो the image inक्रमmation */
	ret = mtd_पढ़ो(mtd, ptr, माप(imginfo), &sz, (u_अक्षर *)imginfo);
	अगर ((ret < 0) || (ret >= 0 && sz != माप(imginfo))) अणु
		pr_err("AFS: mtd read failed at 0x%x: %d\n",
		       ptr, ret);
		वापस -EIO;
	पूर्ण

	/* 32bit platक्रमms have 4 bytes padding */
	crc = word_sum_v2(&imginfo[1], 34);
	अगर (!crc) अणु
		pr_debug("Padding 1 word (4 bytes)\n");
		pad = 1;
	पूर्ण अन्यथा अणु
		/* 64bit platक्रमms have 8 bytes padding */
		crc = word_sum_v2(&imginfo[2], 34);
		अगर (!crc) अणु
			pr_debug("Padding 2 words (8 bytes)\n");
			pad = 2;
		पूर्ण
	पूर्ण
	अगर (crc) अणु
		pr_err("AFS: bad checksum on v2 image info: %08x\n", crc);
		वापस -EINVAL;
	पूर्ण
	entrypoपूर्णांक = imginfo[pad];
	attributes = imginfo[pad+1];
	region_count = imginfo[pad+2];
	block_start = imginfo[20];
	block_end = imginfo[21];

	pr_debug("image entry=%08x, attr=%08x, regions=%08x, "
		 "bs=%08x, be=%08x\n",
		 entrypoपूर्णांक, attributes, region_count,
		 block_start, block_end);

	क्रम (i = 0; i < region_count; i++) अणु
		u32 region_load_addr = imginfo[pad + 3 + i*4];
		u32 region_size = imginfo[pad + 4 + i*4];
		u32 region_offset = imginfo[pad + 5 + i*4];
		u32 region_start;
		u32 region_end;

		pr_debug("  region %d: address: %08x, size: %08x, "
			 "offset: %08x\n",
			 i,
			 region_load_addr,
			 region_size,
			 region_offset);

		region_start = off + region_offset;
		region_end = region_start + region_size;
		/* Align partition to end of erase block */
		region_end += (mtd->erasesize - 1);
		region_end &= ~(mtd->erasesize -1);
		pr_debug("   partition start = %08x, partition end = %08x\n",
			 region_start, region_end);

		/* Create one partition per region */
		part->name = kstrdup(name, GFP_KERNEL);
		अगर (!part->name)
			वापस -ENOMEM;
		part->offset = region_start;
		part->size = region_end - region_start;
		part->mask_flags = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_afs_partitions(काष्ठा mtd_info *mtd,
				स्थिर काष्ठा mtd_partition **pparts,
				काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा mtd_partition *parts;
	u_पूर्णांक off, sz;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Count the partitions by looping over all erase blocks */
	क्रम (i = off = sz = 0; off < mtd->size; off += mtd->erasesize) अणु
		अगर (afs_is_v1(mtd, off)) अणु
			sz += माप(काष्ठा mtd_partition);
			i += 1;
		पूर्ण
		अगर (afs_is_v2(mtd, off)) अणु
			sz += माप(काष्ठा mtd_partition);
			i += 1;
		पूर्ण
	पूर्ण

	अगर (!i)
		वापस 0;

	parts = kzalloc(sz, GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	/*
	 * Identअगरy the partitions
	 */
	क्रम (i = off = 0; off < mtd->size; off += mtd->erasesize) अणु
		अगर (afs_is_v1(mtd, off)) अणु
			ret = afs_parse_v1_partition(mtd, off, &parts[i]);
			अगर (ret)
				जाओ out_मुक्त_parts;
			i++;
		पूर्ण
		अगर (afs_is_v2(mtd, off)) अणु
			ret = afs_parse_v2_partition(mtd, off, &parts[i]);
			अगर (ret)
				जाओ out_मुक्त_parts;
			i++;
		पूर्ण
	पूर्ण

	*pparts = parts;
	वापस i;

out_मुक्त_parts:
	जबतक (--i >= 0)
		kमुक्त(parts[i].name);
	kमुक्त(parts);
	*pparts = शून्य;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtd_parser_afs_of_match_table[] = अणु
	अणु .compatible = "arm,arm-firmware-suite" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtd_parser_afs_of_match_table);

अटल काष्ठा mtd_part_parser afs_parser = अणु
	.parse_fn = parse_afs_partitions,
	.name = "afs",
	.of_match_table = mtd_parser_afs_of_match_table,
पूर्ण;
module_mtd_part_parser(afs_parser);

MODULE_AUTHOR("ARM Ltd");
MODULE_DESCRIPTION("ARM Firmware Suite partition parser");
MODULE_LICENSE("GPL");
