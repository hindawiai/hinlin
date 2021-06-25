<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BCM47XX MTD partitioning
 *
 * Copyright तऊ 2012 Rafaध Miधecki <zajec5@gmail.com>
 */

#समावेश <linux/bcm47xx_nvram.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <uapi/linux/magic.h>

/*
 * न_अंकD flash on Netgear R6250 was verअगरied to contain 15 partitions.
 * This will result in allocating too big array क्रम some old devices, but the
 * memory will be मुक्तd soon anyway (see mtd_device_parse_रेजिस्टर).
 */
#घोषणा BCM47XXPART_MAX_PARTS		20

/*
 * Amount of bytes we पढ़ो when analyzing each block of flash memory.
 * Set it big enough to allow detecting partition and पढ़ोing important data.
 */
#घोषणा BCM47XXPART_BYTES_TO_READ	0x4e8

/* Magics */
#घोषणा BOARD_DATA_MAGIC		0x5246504D	/* MPFR */
#घोषणा BOARD_DATA_MAGIC2		0xBD0D0BBD
#घोषणा CFE_MAGIC			0x43464531	/* 1EFC */
#घोषणा FACTORY_MAGIC			0x59544346	/* FCTY */
#घोषणा NVRAM_HEADER			0x48534C46	/* FLSH */
#घोषणा POT_MAGIC1			0x54544f50	/* POTT */
#घोषणा POT_MAGIC2			0x504f		/* OP */
#घोषणा ML_MAGIC1			0x39685a42
#घोषणा ML_MAGIC2			0x26594131
#घोषणा TRX_MAGIC			0x30524448
#घोषणा SHSQ_MAGIC			0x71736873	/* shsq (weird ZTE H218N endianness) */

अटल स्थिर अक्षर * स्थिर trx_types[] = अणु "trx", शून्य पूर्ण;

काष्ठा trx_header अणु
	uपूर्णांक32_t magic;
	uपूर्णांक32_t length;
	uपूर्णांक32_t crc32;
	uपूर्णांक16_t flags;
	uपूर्णांक16_t version;
	uपूर्णांक32_t offset[3];
पूर्ण __packed;

अटल व्योम bcm47xxpart_add_part(काष्ठा mtd_partition *part, स्थिर अक्षर *name,
				 u64 offset, uपूर्णांक32_t mask_flags)
अणु
	part->name = name;
	part->offset = offset;
	part->mask_flags = mask_flags;
पूर्ण

/**
 * bcm47xxpart_bootpartition - माला_लो index of TRX partition used by bootloader
 *
 * Some devices may have more than one TRX partition. In such हाल one of them
 * is the मुख्य one and another a failsafe one. Bootloader may fallback to the
 * failsafe firmware अगर it detects corruption of the मुख्य image.
 *
 * This function provides info about currently used TRX partition. It's the one
 * containing kernel started by the bootloader.
 */
अटल पूर्णांक bcm47xxpart_bootpartition(व्योम)
अणु
	अक्षर buf[4];
	पूर्णांक bootpartition;

	/* Check CFE environment variable */
	अगर (bcm47xx_nvram_दो_पर्या("bootpartition", buf, माप(buf)) > 0) अणु
		अगर (!kstrtoपूर्णांक(buf, 0, &bootpartition))
			वापस bootpartition;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xxpart_parse(काष्ठा mtd_info *master,
			     स्थिर काष्ठा mtd_partition **pparts,
			     काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा mtd_partition *parts;
	uपूर्णांक8_t i, curr_part = 0;
	uपूर्णांक32_t *buf;
	माप_प्रकार bytes_पढ़ो;
	uपूर्णांक32_t offset;
	uपूर्णांक32_t blocksize = master->erasesize;
	पूर्णांक trx_parts[2]; /* Array with indexes of TRX partitions */
	पूर्णांक trx_num = 0; /* Number of found TRX partitions */
	पूर्णांक possible_nvram_sizes[] = अणु 0x8000, 0xF000, 0x10000, पूर्ण;
	पूर्णांक err;

	/*
	 * Some really old flashes (like AT45DB*) had smaller erasesize-s, but
	 * partitions were aligned to at least 0x1000 anyway.
	 */
	अगर (blocksize < 0x1000)
		blocksize = 0x1000;

	/* Alloc */
	parts = kसुस्मृति(BCM47XXPART_MAX_PARTS, माप(काष्ठा mtd_partition),
			GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	buf = kzalloc(BCM47XXPART_BYTES_TO_READ, GFP_KERNEL);
	अगर (!buf) अणु
		kमुक्त(parts);
		वापस -ENOMEM;
	पूर्ण

	/* Parse block by block looking क्रम magics */
	क्रम (offset = 0; offset <= master->size - blocksize;
	     offset += blocksize) अणु
		/* Nothing more in higher memory on BCM47XX (MIPS) */
		अगर (IS_ENABLED(CONFIG_BCM47XX) && offset >= 0x2000000)
			अवरोध;

		अगर (curr_part >= BCM47XXPART_MAX_PARTS) अणु
			pr_warn("Reached maximum number of partitions, scanning stopped!\n");
			अवरोध;
		पूर्ण

		/* Read beginning of the block */
		err = mtd_पढ़ो(master, offset, BCM47XXPART_BYTES_TO_READ,
			       &bytes_पढ़ो, (uपूर्णांक8_t *)buf);
		अगर (err && !mtd_is_bitflip(err)) अणु
			pr_err("mtd_read error while parsing (offset: 0x%X): %d\n",
			       offset, err);
			जारी;
		पूर्ण

		/* Magic or small NVRAM at 0x400 */
		अगर ((buf[0x4e0 / 4] == CFE_MAGIC && buf[0x4e4 / 4] == CFE_MAGIC) ||
		    (buf[0x400 / 4] == NVRAM_HEADER)) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "boot",
					     offset, MTD_WRITEABLE);
			जारी;
		पूर्ण

		/*
		 * board_data starts with board_id which dअगरfers across boards,
		 * but we can use 'MPFR' (hopefully) magic at 0x100
		 */
		अगर (buf[0x100 / 4] == BOARD_DATA_MAGIC) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "board_data",
					     offset, MTD_WRITEABLE);
			जारी;
		पूर्ण

		/* Found on Huawei E970 */
		अगर (buf[0x000 / 4] == FACTORY_MAGIC) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "factory",
					     offset, MTD_WRITEABLE);
			जारी;
		पूर्ण

		/* POT(TOP) */
		अगर (buf[0x000 / 4] == POT_MAGIC1 &&
		    (buf[0x004 / 4] & 0xFFFF) == POT_MAGIC2) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "POT", offset,
					     MTD_WRITEABLE);
			जारी;
		पूर्ण

		/* ML */
		अगर (buf[0x010 / 4] == ML_MAGIC1 &&
		    buf[0x014 / 4] == ML_MAGIC2) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "ML", offset,
					     MTD_WRITEABLE);
			जारी;
		पूर्ण

		/* TRX */
		अगर (buf[0x000 / 4] == TRX_MAGIC) अणु
			काष्ठा trx_header *trx;
			uपूर्णांक32_t last_subpart;
			uपूर्णांक32_t trx_size;

			अगर (trx_num >= ARRAY_SIZE(trx_parts))
				pr_warn("No enough space to store another TRX found at 0x%X\n",
					offset);
			अन्यथा
				trx_parts[trx_num++] = curr_part;
			bcm47xxpart_add_part(&parts[curr_part++], "firmware",
					     offset, 0);

			/*
			 * Try to find TRX size. The "length" field isn't fully
			 * reliable as it could be decreased to make CRC32 cover
			 * only part of TRX data. It's commonly used as checksum
			 * can't cover e.g. ever-changing rootfs partition.
			 * Use offsets as helpers क्रम assuming min TRX size.
			 */
			trx = (काष्ठा trx_header *)buf;
			last_subpart = max3(trx->offset[0], trx->offset[1],
					    trx->offset[2]);
			trx_size = max(trx->length, last_subpart + blocksize);

			/*
			 * Skip the TRX data. Decrease offset by block size as
			 * the next loop iteration will increase it.
			 */
			offset += roundup(trx_size, blocksize) - blocksize;
			जारी;
		पूर्ण

		/* Squashfs on devices not using TRX */
		अगर (le32_to_cpu(buf[0x000 / 4]) == SQUASHFS_MAGIC ||
		    buf[0x000 / 4] == SHSQ_MAGIC) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "rootfs",
					     offset, 0);
			जारी;
		पूर्ण

		/*
		 * New (ARM?) devices may have NVRAM in some middle block. Last
		 * block will be checked later, so skip it.
		 */
		अगर (offset != master->size - blocksize &&
		    buf[0x000 / 4] == NVRAM_HEADER) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "nvram",
					     offset, 0);
			जारी;
		पूर्ण

		/* Read middle of the block */
		err = mtd_पढ़ो(master, offset + 0x8000, 0x4, &bytes_पढ़ो,
			       (uपूर्णांक8_t *)buf);
		अगर (err && !mtd_is_bitflip(err)) अणु
			pr_err("mtd_read error while parsing (offset: 0x%X): %d\n",
			       offset, err);
			जारी;
		पूर्ण

		/* Some devices (ex. WNDR3700v3) करोn't have a standard 'MPFR' */
		अगर (buf[0x000 / 4] == BOARD_DATA_MAGIC2) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "board_data",
					     offset, MTD_WRITEABLE);
			जारी;
		पूर्ण
	पूर्ण

	/* Look क्रम NVRAM at the end of the last block. */
	क्रम (i = 0; i < ARRAY_SIZE(possible_nvram_sizes); i++) अणु
		अगर (curr_part >= BCM47XXPART_MAX_PARTS) अणु
			pr_warn("Reached maximum number of partitions, scanning stopped!\n");
			अवरोध;
		पूर्ण

		offset = master->size - possible_nvram_sizes[i];
		err = mtd_पढ़ो(master, offset, 0x4, &bytes_पढ़ो,
			       (uपूर्णांक8_t *)buf);
		अगर (err && !mtd_is_bitflip(err)) अणु
			pr_err("mtd_read error while reading (offset 0x%X): %d\n",
			       offset, err);
			जारी;
		पूर्ण

		/* Standard NVRAM */
		अगर (buf[0] == NVRAM_HEADER) अणु
			bcm47xxpart_add_part(&parts[curr_part++], "nvram",
					     master->size - blocksize, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(buf);

	/*
	 * Assume that partitions end at the beginning of the one they are
	 * followed by.
	 */
	क्रम (i = 0; i < curr_part; i++) अणु
		u64 next_part_offset = (i < curr_part - 1) ?
				       parts[i + 1].offset : master->size;

		parts[i].size = next_part_offset - parts[i].offset;
	पूर्ण

	/* If there was TRX parse it now */
	क्रम (i = 0; i < trx_num; i++) अणु
		काष्ठा mtd_partition *trx = &parts[trx_parts[i]];

		अगर (i == bcm47xxpart_bootpartition())
			trx->types = trx_types;
		अन्यथा
			trx->name = "failsafe";
	पूर्ण

	*pparts = parts;
	वापस curr_part;
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm47xxpart_of_match_table[] = अणु
	अणु .compatible = "brcm,bcm947xx-cfe-partitions" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm47xxpart_of_match_table);

अटल काष्ठा mtd_part_parser bcm47xxpart_mtd_parser = अणु
	.parse_fn = bcm47xxpart_parse,
	.name = "bcm47xxpart",
	.of_match_table = bcm47xxpart_of_match_table,
पूर्ण;
module_mtd_part_parser(bcm47xxpart_mtd_parser);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MTD partitioning for BCM47XX flash memories");
