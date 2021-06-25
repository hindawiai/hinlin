<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Parser क्रम TRX क्रमmat partitions
 *
 * Copyright (C) 2012 - 2017 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#घोषणा TRX_PARSER_MAX_PARTS		4

/* Magics */
#घोषणा TRX_MAGIC			0x30524448
#घोषणा UBI_EC_MAGIC			0x23494255	/* UBI# */

काष्ठा trx_header अणु
	uपूर्णांक32_t magic;
	uपूर्णांक32_t length;
	uपूर्णांक32_t crc32;
	uपूर्णांक16_t flags;
	uपूर्णांक16_t version;
	uपूर्णांक32_t offset[3];
पूर्ण __packed;

अटल स्थिर अक्षर *parser_trx_data_part_name(काष्ठा mtd_info *master,
					     माप_प्रकार offset)
अणु
	uपूर्णांक32_t buf;
	माप_प्रकार bytes_पढ़ो;
	पूर्णांक err;

	err  = mtd_पढ़ो(master, offset, माप(buf), &bytes_पढ़ो,
			(uपूर्णांक8_t *)&buf);
	अगर (err && !mtd_is_bitflip(err)) अणु
		pr_err("mtd_read error while parsing (offset: 0x%zX): %d\n",
			offset, err);
		जाओ out_शेष;
	पूर्ण

	अगर (buf == UBI_EC_MAGIC)
		वापस "ubi";

out_शेष:
	वापस "rootfs";
पूर्ण

अटल पूर्णांक parser_trx_parse(काष्ठा mtd_info *mtd,
			    स्थिर काष्ठा mtd_partition **pparts,
			    काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा mtd_partition *parts;
	काष्ठा mtd_partition *part;
	काष्ठा trx_header trx;
	माप_प्रकार bytes_पढ़ो;
	uपूर्णांक8_t curr_part = 0, i = 0;
	पूर्णांक err;

	parts = kसुस्मृति(TRX_PARSER_MAX_PARTS, माप(काष्ठा mtd_partition),
			GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	err = mtd_पढ़ो(mtd, 0, माप(trx), &bytes_पढ़ो, (uपूर्णांक8_t *)&trx);
	अगर (err) अणु
		pr_err("MTD reading error: %d\n", err);
		kमुक्त(parts);
		वापस err;
	पूर्ण

	अगर (trx.magic != TRX_MAGIC) अणु
		kमुक्त(parts);
		वापस -ENOENT;
	पूर्ण

	/* We have LZMA loader अगर there is address in offset[2] */
	अगर (trx.offset[2]) अणु
		part = &parts[curr_part++];
		part->name = "loader";
		part->offset = trx.offset[i];
		i++;
	पूर्ण

	अगर (trx.offset[i]) अणु
		part = &parts[curr_part++];
		part->name = "linux";
		part->offset = trx.offset[i];
		i++;
	पूर्ण

	अगर (trx.offset[i]) अणु
		part = &parts[curr_part++];
		part->name = parser_trx_data_part_name(mtd, trx.offset[i]);
		part->offset = trx.offset[i];
		i++;
	पूर्ण

	/*
	 * Assume that every partition ends at the beginning of the one it is
	 * followed by.
	 */
	क्रम (i = 0; i < curr_part; i++) अणु
		u64 next_part_offset = (i < curr_part - 1) ?
				       parts[i + 1].offset : mtd->size;

		parts[i].size = next_part_offset - parts[i].offset;
	पूर्ण

	*pparts = parts;
	वापस i;
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtd_parser_trx_of_match_table[] = अणु
	अणु .compatible = "brcm,trx" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtd_parser_trx_of_match_table);

अटल काष्ठा mtd_part_parser mtd_parser_trx = अणु
	.parse_fn = parser_trx_parse,
	.name = "trx",
	.of_match_table = mtd_parser_trx_of_match_table,
पूर्ण;
module_mtd_part_parser(mtd_parser_trx);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Parser for TRX format partitions");
