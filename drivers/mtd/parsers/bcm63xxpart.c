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

#समावेश <linux/bcm963xx_nvram.h>
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

#अगर_घोषित CONFIG_MIPS
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/fw/cfe/cfe_api.h>
#पूर्ण_अगर /* CONFIG_MIPS */

#घोषणा BCM963XX_CFE_BLOCK_SIZE		SZ_64K	/* always at least 64KiB */

#घोषणा BCM963XX_CFE_MAGIC_OFFSET	0x4e0
#घोषणा BCM963XX_CFE_VERSION_OFFSET	0x570
#घोषणा BCM963XX_NVRAM_OFFSET		0x580

/* Ensure strings पढ़ो from flash काष्ठाs are null terminated */
#घोषणा STR_शून्य_TERMINATE(x) \
	करो अणु अक्षर *_str = (x); _str[माप(x) - 1] = 0; पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक bcm63xx_detect_cfe(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर_घोषित CONFIG_MIPS
	ret = (fw_arg3 == CFE_EPTSEAL);
#पूर्ण_अगर /* CONFIG_MIPS */

	वापस ret;
पूर्ण

अटल पूर्णांक bcm63xx_पढ़ो_nvram(काष्ठा mtd_info *master,
	काष्ठा bcm963xx_nvram *nvram)
अणु
	u32 actual_crc, expected_crc;
	माप_प्रकार retlen;
	पूर्णांक ret;

	/* extract nvram data */
	ret = mtd_पढ़ो(master, BCM963XX_NVRAM_OFFSET, BCM963XX_NVRAM_V5_SIZE,
			&retlen, (व्योम *)nvram);
	अगर (ret)
		वापस ret;

	ret = bcm963xx_nvram_checksum(nvram, &expected_crc, &actual_crc);
	अगर (ret)
		pr_warn("nvram checksum failed, contents may be invalid (expected %08x, got %08x)\n",
			expected_crc, actual_crc);

	अगर (!nvram->psi_size)
		nvram->psi_size = BCM963XX_DEFAULT_PSI_SIZE;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर bcm63xx_cfe_part_types[] = अणु
	"bcm963xx-imagetag",
	शून्य,
पूर्ण;

अटल पूर्णांक bcm63xx_parse_cfe_nor_partitions(काष्ठा mtd_info *master,
	स्थिर काष्ठा mtd_partition **pparts, काष्ठा bcm963xx_nvram *nvram)
अणु
	काष्ठा mtd_partition *parts;
	पूर्णांक nrparts = 3, curpart = 0;
	अचिन्हित पूर्णांक cfelen, nvramlen;
	अचिन्हित पूर्णांक cfe_erasesize;
	पूर्णांक i;

	cfe_erasesize = max_t(uपूर्णांक32_t, master->erasesize,
			      BCM963XX_CFE_BLOCK_SIZE);

	cfelen = cfe_erasesize;
	nvramlen = nvram->psi_size * SZ_1K;
	nvramlen = roundup(nvramlen, cfe_erasesize);

	parts = kzalloc(माप(*parts) * nrparts + 10 * nrparts, GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	/* Start building partition list */
	parts[curpart].name = "CFE";
	parts[curpart].offset = 0;
	parts[curpart].size = cfelen;
	curpart++;

	parts[curpart].name = "nvram";
	parts[curpart].offset = master->size - nvramlen;
	parts[curpart].size = nvramlen;
	curpart++;

	/* Global partition "linux" to make easy firmware upgrade */
	parts[curpart].name = "linux";
	parts[curpart].offset = cfelen;
	parts[curpart].size = master->size - cfelen - nvramlen;
	parts[curpart].types = bcm63xx_cfe_part_types;

	क्रम (i = 0; i < nrparts; i++)
		pr_info("Partition %d is %s offset %llx and length %llx\n", i,
			parts[i].name, parts[i].offset,	parts[i].size);

	*pparts = parts;

	वापस nrparts;
पूर्ण

अटल पूर्णांक bcm63xx_parse_cfe_partitions(काष्ठा mtd_info *master,
					स्थिर काष्ठा mtd_partition **pparts,
					काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा bcm963xx_nvram *nvram = शून्य;
	पूर्णांक ret;

	अगर (!bcm63xx_detect_cfe())
		वापस -EINVAL;

	nvram = vzalloc(माप(*nvram));
	अगर (!nvram)
		वापस -ENOMEM;

	ret = bcm63xx_पढ़ो_nvram(master, nvram);
	अगर (ret)
		जाओ out;

	अगर (!mtd_type_is_nand(master))
		ret = bcm63xx_parse_cfe_nor_partitions(master, pparts, nvram);
	अन्यथा
		ret = -EINVAL;

out:
	vमुक्त(nvram);
	वापस ret;
पूर्ण;

अटल स्थिर काष्ठा of_device_id parse_bcm63xx_cfe_match_table[] = अणु
	अणु .compatible = "brcm,bcm963xx-cfe-nor-partitions" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, parse_bcm63xx_cfe_match_table);

अटल काष्ठा mtd_part_parser bcm63xx_cfe_parser = अणु
	.parse_fn = bcm63xx_parse_cfe_partitions,
	.name = "bcm63xxpart",
	.of_match_table = parse_bcm63xx_cfe_match_table,
पूर्ण;
module_mtd_part_parser(bcm63xx_cfe_parser);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Dickinson <openwrt@cshore.neomailbox.net>");
MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_AUTHOR("Mike Albon <malbon@openwrt.org>");
MODULE_AUTHOR("Jonas Gorski <jonas.gorski@gmail.com");
MODULE_DESCRIPTION("MTD partitioning for BCM63XX CFE bootloaders");
