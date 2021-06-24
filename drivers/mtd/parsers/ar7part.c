<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright तऊ 2007 Eugene Konev <ejka@खोलोwrt.org>
 *
 * TI AR7 flash partition table.
 * Based on ar7 map by Felix Fietkau <nbd@खोलोwrt.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/memblock.h>
#समावेश <linux/module.h>

#समावेश <uapi/linux/magic.h>

#घोषणा AR7_PARTS	4
#घोषणा ROOT_OFFSET	0xe0000

#घोषणा LOADER_MAGIC1	le32_to_cpu(0xfeedfa42)
#घोषणा LOADER_MAGIC2	le32_to_cpu(0xfeed1281)

काष्ठा ar7_bin_rec अणु
	अचिन्हित पूर्णांक checksum;
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक address;
पूर्ण;

अटल पूर्णांक create_mtd_partitions(काष्ठा mtd_info *master,
				 स्थिर काष्ठा mtd_partition **pparts,
				 काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा ar7_bin_rec header;
	अचिन्हित पूर्णांक offset;
	माप_प्रकार len;
	अचिन्हित पूर्णांक pre_size = master->erasesize, post_size = 0;
	अचिन्हित पूर्णांक root_offset = ROOT_OFFSET;

	पूर्णांक retries = 10;
	काष्ठा mtd_partition *ar7_parts;

	ar7_parts = kसुस्मृति(AR7_PARTS, माप(*ar7_parts), GFP_KERNEL);
	अगर (!ar7_parts)
		वापस -ENOMEM;
	ar7_parts[0].name = "loader";
	ar7_parts[0].offset = 0;
	ar7_parts[0].size = master->erasesize;
	ar7_parts[0].mask_flags = MTD_WRITEABLE;

	ar7_parts[1].name = "config";
	ar7_parts[1].offset = 0;
	ar7_parts[1].size = master->erasesize;
	ar7_parts[1].mask_flags = 0;

	करो अणु /* Try 10 blocks starting from master->erasesize */
		offset = pre_size;
		mtd_पढ़ो(master, offset, माप(header), &len,
			 (uपूर्णांक8_t *)&header);
		अगर (!म_भेदन((अक्षर *)&header, "TIENV0.8", 8))
			ar7_parts[1].offset = pre_size;
		अगर (header.checksum == LOADER_MAGIC1)
			अवरोध;
		अगर (header.checksum == LOADER_MAGIC2)
			अवरोध;
		pre_size += master->erasesize;
	पूर्ण जबतक (retries--);

	pre_size = offset;

	अगर (!ar7_parts[1].offset) अणु
		ar7_parts[1].offset = master->size - master->erasesize;
		post_size = master->erasesize;
	पूर्ण

	चयन (header.checksum) अणु
	हाल LOADER_MAGIC1:
		जबतक (header.length) अणु
			offset += माप(header) + header.length;
			mtd_पढ़ो(master, offset, माप(header), &len,
				 (uपूर्णांक8_t *)&header);
		पूर्ण
		root_offset = offset + माप(header) + 4;
		अवरोध;
	हाल LOADER_MAGIC2:
		जबतक (header.length) अणु
			offset += माप(header) + header.length;
			mtd_पढ़ो(master, offset, माप(header), &len,
				 (uपूर्णांक8_t *)&header);
		पूर्ण
		root_offset = offset + माप(header) + 4 + 0xff;
		root_offset &= ~(uपूर्णांक32_t)0xff;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "Unknown magic: %08x\n", header.checksum);
		अवरोध;
	पूर्ण

	mtd_पढ़ो(master, root_offset, माप(header), &len, (u8 *)&header);
	अगर (header.checksum != SQUASHFS_MAGIC) अणु
		root_offset += master->erasesize - 1;
		root_offset &= ~(master->erasesize - 1);
	पूर्ण

	ar7_parts[2].name = "linux";
	ar7_parts[2].offset = pre_size;
	ar7_parts[2].size = master->size - pre_size - post_size;
	ar7_parts[2].mask_flags = 0;

	ar7_parts[3].name = "rootfs";
	ar7_parts[3].offset = root_offset;
	ar7_parts[3].size = master->size - root_offset - post_size;
	ar7_parts[3].mask_flags = 0;

	*pparts = ar7_parts;
	वापस AR7_PARTS;
पूर्ण

अटल काष्ठा mtd_part_parser ar7_parser = अणु
	.parse_fn = create_mtd_partitions,
	.name = "ar7part",
पूर्ण;
module_mtd_part_parser(ar7_parser);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(	"Felix Fietkau <nbd@openwrt.org>, "
		"Eugene Konev <ejka@openwrt.org>");
MODULE_DESCRIPTION("MTD partitioning for TI AR7");
