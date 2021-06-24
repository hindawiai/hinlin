<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_BCM963XX_NVRAM_H__
#घोषणा __LINUX_BCM963XX_NVRAM_H__

#समावेश <linux/crc32.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/sizes.h>
#समावेश <linux/types.h>

/*
 * Broadcom BCM963xx SoC board nvram data काष्ठाure.
 *
 * The nvram काष्ठाure varies in size depending on the SoC board version. Use
 * the appropriate minimum BCM963XX_NVRAM_*_SIZE define क्रम the inक्रमmation
 * you need instead of माप(काष्ठा bcm963xx_nvram) as this may change.
 */

#घोषणा BCM963XX_NVRAM_V4_SIZE		300
#घोषणा BCM963XX_NVRAM_V5_SIZE		(1 * SZ_1K)

#घोषणा BCM963XX_DEFAULT_PSI_SIZE	64

क्रमागत bcm963xx_nvram_nand_part अणु
	BCM963XX_NVRAM_न_अंकD_PART_BOOT = 0,
	BCM963XX_NVRAM_न_अंकD_PART_ROOTFS_1,
	BCM963XX_NVRAM_न_अंकD_PART_ROOTFS_2,
	BCM963XX_NVRAM_न_अंकD_PART_DATA,
	BCM963XX_NVRAM_न_अंकD_PART_BBT,

	__BCM963XX_NVRAM_न_अंकD_NR_PARTS
पूर्ण;

काष्ठा bcm963xx_nvram अणु
	u32	version;
	अक्षर	bootline[256];
	अक्षर	name[16];
	u32	मुख्य_tp_number;
	u32	psi_size;
	u32	mac_addr_count;
	u8	mac_addr_base[ETH_ALEN];
	u8	__reserved1[2];
	u32	checksum_v4;

	u8	__reserved2[292];
	u32	nand_part_offset[__BCM963XX_NVRAM_न_अंकD_NR_PARTS];
	u32	nand_part_size[__BCM963XX_NVRAM_न_अंकD_NR_PARTS];
	u8	__reserved3[388];
	u32	checksum_v5;
पूर्ण;

#घोषणा BCM963XX_NVRAM_न_अंकD_PART_OFFSET(nvram, part) \
	bcm963xx_nvram_nand_part_offset(nvram, BCM963XX_NVRAM_न_अंकD_PART_ ##part)

अटल अंतरभूत u64 __pure bcm963xx_nvram_nand_part_offset(
	स्थिर काष्ठा bcm963xx_nvram *nvram,
	क्रमागत bcm963xx_nvram_nand_part part)
अणु
	वापस nvram->nand_part_offset[part] * SZ_1K;
पूर्ण

#घोषणा BCM963XX_NVRAM_न_अंकD_PART_SIZE(nvram, part) \
	bcm963xx_nvram_nand_part_size(nvram, BCM963XX_NVRAM_न_अंकD_PART_ ##part)

अटल अंतरभूत u64 __pure bcm963xx_nvram_nand_part_size(
	स्थिर काष्ठा bcm963xx_nvram *nvram,
	क्रमागत bcm963xx_nvram_nand_part part)
अणु
	वापस nvram->nand_part_size[part] * SZ_1K;
पूर्ण

/*
 * bcm963xx_nvram_checksum - Verअगरy nvram checksum
 *
 * @nvram: poपूर्णांकer to full size nvram data काष्ठाure
 * @expected_out: optional poपूर्णांकer to store expected checksum value
 * @actual_out: optional poपूर्णांकer to store actual checksum value
 *
 * Return: 0 अगर the checksum is valid, otherwise -EINVAL
 */
अटल पूर्णांक __maybe_unused bcm963xx_nvram_checksum(
	स्थिर काष्ठा bcm963xx_nvram *nvram,
	u32 *expected_out, u32 *actual_out)
अणु
	u32 expected, actual;
	माप_प्रकार len;

	अगर (nvram->version <= 4) अणु
		expected = nvram->checksum_v4;
		len = BCM963XX_NVRAM_V4_SIZE - माप(u32);
	पूर्ण अन्यथा अणु
		expected = nvram->checksum_v5;
		len = BCM963XX_NVRAM_V5_SIZE - माप(u32);
	पूर्ण

	/*
	 * Calculate the CRC32 value क्रम the nvram with a checksum value
	 * of 0 without modअगरying or copying the nvram by combining:
	 * - The CRC32 of the nvram without the checksum value
	 * - The CRC32 of a zero checksum value (which is also 0)
	 */
	actual = crc32_le_combine(
		crc32_le(~0, (u8 *)nvram, len), 0, माप(u32));

	अगर (expected_out)
		*expected_out = expected;

	अगर (actual_out)
		*actual_out = actual;

	वापस expected == actual ? 0 : -EINVAL;
पूर्ण;

#पूर्ण_अगर /* __LINUX_BCM963XX_NVRAM_H__ */
