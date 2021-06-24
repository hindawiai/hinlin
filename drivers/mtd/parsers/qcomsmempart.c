<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm SMEM न_अंकD flash partition parser
 *
 * Copyright (C) 2020, Linaro Ltd.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/sस्मृति.स>

#घोषणा SMEM_AARM_PARTITION_TABLE	9
#घोषणा SMEM_APPS			0

#घोषणा SMEM_FLASH_PART_MAGIC1		0x55ee73aa
#घोषणा SMEM_FLASH_PART_MAGIC2		0xe35ebddb
#घोषणा SMEM_FLASH_PTABLE_V3		3
#घोषणा SMEM_FLASH_PTABLE_V4		4
#घोषणा SMEM_FLASH_PTABLE_MAX_PARTS_V3	16
#घोषणा SMEM_FLASH_PTABLE_MAX_PARTS_V4	48
#घोषणा SMEM_FLASH_PTABLE_HDR_LEN	(4 * माप(u32))
#घोषणा SMEM_FLASH_PTABLE_NAME_SIZE	16

/**
 * काष्ठा smem_flash_pentry - SMEM Flash partition entry
 * @name: Name of the partition
 * @offset: Offset in blocks
 * @length: Length of the partition in blocks
 * @attr: Flags क्रम this partition
 */
काष्ठा smem_flash_pentry अणु
	अक्षर name[SMEM_FLASH_PTABLE_NAME_SIZE];
	__le32 offset;
	__le32 length;
	u8 attr;
पूर्ण __packed __aligned(4);

/**
 * काष्ठा smem_flash_ptable - SMEM Flash partition table
 * @magic1: Partition table Magic 1
 * @magic2: Partition table Magic 2
 * @version: Partition table version
 * @numparts: Number of partitions in this ptable
 * @pentry: Flash partition entries beदीर्घing to this ptable
 */
काष्ठा smem_flash_ptable अणु
	__le32 magic1;
	__le32 magic2;
	__le32 version;
	__le32 numparts;
	काष्ठा smem_flash_pentry pentry[SMEM_FLASH_PTABLE_MAX_PARTS_V4];
पूर्ण __packed __aligned(4);

अटल पूर्णांक parse_qcomsmem_part(काष्ठा mtd_info *mtd,
			       स्थिर काष्ठा mtd_partition **pparts,
			       काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा smem_flash_pentry *pentry;
	काष्ठा smem_flash_ptable *ptable;
	माप_प्रकार len = SMEM_FLASH_PTABLE_HDR_LEN;
	काष्ठा mtd_partition *parts;
	पूर्णांक ret, i, numparts;
	अक्षर *name, *c;

	अगर (IS_ENABLED(CONFIG_MTD_SPI_NOR_USE_4K_SECTORS)
			&& mtd->type == MTD_NORFLASH) अणु
		pr_err("%s: SMEM partition parser is incompatible with 4K sectors\n",
				mtd->name);
		वापस -EINVAL;
	पूर्ण

	pr_debug("Parsing partition table info from SMEM\n");
	ptable = qcom_smem_get(SMEM_APPS, SMEM_AARM_PARTITION_TABLE, &len);
	अगर (IS_ERR(ptable)) अणु
		pr_err("Error reading partition table header\n");
		वापस PTR_ERR(ptable);
	पूर्ण

	/* Verअगरy ptable magic */
	अगर (le32_to_cpu(ptable->magic1) != SMEM_FLASH_PART_MAGIC1 ||
	    le32_to_cpu(ptable->magic2) != SMEM_FLASH_PART_MAGIC2) अणु
		pr_err("Partition table magic verification failed\n");
		वापस -EINVAL;
	पूर्ण

	/* Ensure that # of partitions is less than the max we have allocated */
	numparts = le32_to_cpu(ptable->numparts);
	अगर (numparts > SMEM_FLASH_PTABLE_MAX_PARTS_V4) अणु
		pr_err("Partition numbers exceed the max limit\n");
		वापस -EINVAL;
	पूर्ण

	/* Find out length of partition data based on table version */
	अगर (le32_to_cpu(ptable->version) <= SMEM_FLASH_PTABLE_V3) अणु
		len = SMEM_FLASH_PTABLE_HDR_LEN + SMEM_FLASH_PTABLE_MAX_PARTS_V3 *
			माप(काष्ठा smem_flash_pentry);
	पूर्ण अन्यथा अगर (le32_to_cpu(ptable->version) == SMEM_FLASH_PTABLE_V4) अणु
		len = SMEM_FLASH_PTABLE_HDR_LEN + SMEM_FLASH_PTABLE_MAX_PARTS_V4 *
			माप(काष्ठा smem_flash_pentry);
	पूर्ण अन्यथा अणु
		pr_err("Unknown ptable version (%d)", le32_to_cpu(ptable->version));
		वापस -EINVAL;
	पूर्ण

	/*
	 * Now that the partition table header has been parsed, verअगरied
	 * and the length of the partition table calculated, पढ़ो the
	 * complete partition table
	 */
	ptable = qcom_smem_get(SMEM_APPS, SMEM_AARM_PARTITION_TABLE, &len);
	अगर (IS_ERR(ptable)) अणु
		pr_err("Error reading partition table\n");
		वापस PTR_ERR(ptable);
	पूर्ण

	parts = kसुस्मृति(numparts, माप(*parts), GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	क्रम (i = 0; i < numparts; i++) अणु
		pentry = &ptable->pentry[i];
		अगर (pentry->name[0] == '\0')
			जारी;

		name = kstrdup(pentry->name, GFP_KERNEL);
		अगर (!name) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_parts;
		पूर्ण

		/* Convert name to lower हाल */
		क्रम (c = name; *c != '\0'; c++)
			*c = छोटे(*c);

		parts[i].name = name;
		parts[i].offset = le32_to_cpu(pentry->offset) * mtd->erasesize;
		parts[i].mask_flags = pentry->attr;
		parts[i].size = le32_to_cpu(pentry->length) * mtd->erasesize;
		pr_debug("%d: %s offs=0x%08x size=0x%08x attr:0x%08x\n",
			 i, pentry->name, le32_to_cpu(pentry->offset),
			 le32_to_cpu(pentry->length), pentry->attr);
	पूर्ण

	pr_debug("SMEM partition table found: ver: %d len: %d\n",
		 le32_to_cpu(ptable->version), numparts);
	*pparts = parts;

	वापस numparts;

out_मुक्त_parts:
	जबतक (--i >= 0)
		kमुक्त(parts[i].name);
	kमुक्त(parts);
	*pparts = शून्य;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcomsmem_of_match_table[] = अणु
	अणु .compatible = "qcom,smem-part" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qcomsmem_of_match_table);

अटल काष्ठा mtd_part_parser mtd_parser_qcomsmem = अणु
	.parse_fn = parse_qcomsmem_part,
	.name = "qcomsmem",
	.of_match_table = qcomsmem_of_match_table,
पूर्ण;
module_mtd_part_parser(mtd_parser_qcomsmem);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("Qualcomm SMEM NAND flash partition parser");
