<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Always ON (AON) रेजिस्टर पूर्णांकerface between bootloader and Linux
 *
 * Copyright तऊ 2014-2017 Broadcom
 */

#अगर_अघोषित __BRCMSTB_AON_DEFS_H__
#घोषणा __BRCMSTB_AON_DEFS_H__

#समावेश <linux/compiler.h>

/* Magic number in upper 16-bits */
#घोषणा BRCMSTB_S3_MAGIC_MASK                   0xffff0000
#घोषणा BRCMSTB_S3_MAGIC_SHORT                  0x5AFE0000

क्रमागत अणु
	/* Restore अक्रमom key क्रम AES memory verअगरication (off = fixed key) */
	S3_FLAG_LOAD_RANDKEY		= (1 << 0),

	/* Scratch buffer page table is present */
	S3_FLAG_SCRATCH_BUFFER_TABLE	= (1 << 1),

	/* Skip all memory verअगरication */
	S3_FLAG_NO_MEM_VERIFY		= (1 << 2),

	/*
	 * Modअगरication of this bit reserved क्रम bootloader only.
	 * 1=PSCI started Linux, 0=Direct jump to Linux.
	 */
	S3_FLAG_PSCI_BOOT		= (1 << 3),

	/*
	 * Modअगरication of this bit reserved क्रम bootloader only.
	 * 1=64 bit boot, 0=32 bit boot.
	 */
	S3_FLAG_BOOTED64		= (1 << 4),
पूर्ण;

#घोषणा BRCMSTB_HASH_LEN			(128 / 8) /* 128-bit hash */

#घोषणा AON_REG_MAGIC_FLAGS			0x00
#घोषणा AON_REG_CONTROL_LOW			0x04
#घोषणा AON_REG_CONTROL_HIGH			0x08
#घोषणा AON_REG_S3_HASH				0x0c /* hash of S3 params */
#घोषणा AON_REG_CONTROL_HASH_LEN		0x1c
#घोषणा AON_REG_PANIC				0x20

#घोषणा BRCMSTB_S3_MAGIC		0x5AFEB007
#घोषणा BRCMSTB_PANIC_MAGIC		0x512E115E
#घोषणा BOOTLOADER_SCRATCH_SIZE		64
#घोषणा BRCMSTB_DTU_STATE_MAP_ENTRIES	(8*1024)
#घोषणा BRCMSTB_DTU_CONFIG_ENTRIES	(512)
#घोषणा BRCMSTB_DTU_COUNT		(2)

#घोषणा IMAGE_DESCRIPTORS_बफ_मानE	(2 * 1024)
#घोषणा S3_BOOTLOADER_RESERVED		(S3_FLAG_PSCI_BOOT | S3_FLAG_BOOTED64)

काष्ठा brcmstb_bootloader_dtu_table अणु
	uपूर्णांक32_t	dtu_state_map[BRCMSTB_DTU_STATE_MAP_ENTRIES];
	uपूर्णांक32_t	dtu_config[BRCMSTB_DTU_CONFIG_ENTRIES];
पूर्ण;

/*
 * Bootloader utilizes a custom parameter block left in DRAM क्रम handling S3
 * warm resume
 */
काष्ठा brcmstb_s3_params अणु
	/* scratch memory क्रम bootloader */
	uपूर्णांक8_t scratch[BOOTLOADER_SCRATCH_SIZE];

	uपूर्णांक32_t magic; /* BRCMSTB_S3_MAGIC */
	uपूर्णांक64_t reentry; /* PA */

	/* descriptors */
	uपूर्णांक32_t hash[BRCMSTB_HASH_LEN / 4];

	/*
	 * If 0, then ignore this parameter (there is only one set of
	 *   descriptors)
	 *
	 * If non-0, then a second set of descriptors is stored at:
	 *
	 *   descriptors + desc_offset_2
	 *
	 * The MAC result of both descriptors is XOR'd and stored in @hash
	 */
	uपूर्णांक32_t desc_offset_2;

	/*
	 * (Physical) address of a brcmstb_bootloader_scratch_table, क्रम
	 * providing a large DRAM buffer to the bootloader
	 */
	uपूर्णांक64_t buffer_table;

	uपूर्णांक32_t spare[70];

	uपूर्णांक8_t descriptors[IMAGE_DESCRIPTORS_बफ_मानE];
	/*
	 * Must be last member of काष्ठा. See brcmstb_pm_s3_finish() क्रम reason.
	 */
	काष्ठा brcmstb_bootloader_dtu_table dtu[BRCMSTB_DTU_COUNT];
पूर्ण __packed;

#पूर्ण_अगर /* __BRCMSTB_AON_DEFS_H__ */
