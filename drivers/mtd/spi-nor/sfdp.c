<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

#घोषणा SFDP_PARAM_HEADER_ID(p)	(((p)->id_msb << 8) | (p)->id_lsb)
#घोषणा SFDP_PARAM_HEADER_PTP(p) \
	(((p)->parameter_table_poपूर्णांकer[2] << 16) | \
	 ((p)->parameter_table_poपूर्णांकer[1] <<  8) | \
	 ((p)->parameter_table_poपूर्णांकer[0] <<  0))

#घोषणा SFDP_BFPT_ID		0xff00	/* Basic Flash Parameter Table */
#घोषणा SFDP_SECTOR_MAP_ID	0xff81	/* Sector Map Table */
#घोषणा SFDP_4BAIT_ID		0xff84  /* 4-byte Address Inकाष्ठाion Table */
#घोषणा SFDP_PROखाता1_ID	0xff05	/* xSPI Profile 1.0 table. */
#घोषणा SFDP_SCCR_MAP_ID	0xff87	/*
					 * Status, Control and Configuration
					 * Register Map.
					 */

#घोषणा SFDP_SIGNATURE		0x50444653U

काष्ठा sfdp_header अणु
	u32		signature; /* Ox50444653U <=> "SFDP" */
	u8		minor;
	u8		major;
	u8		nph; /* 0-base number of parameter headers */
	u8		unused;

	/* Basic Flash Parameter Table. */
	काष्ठा sfdp_parameter_header	bfpt_header;
पूर्ण;

/* Fast Read settings. */
काष्ठा sfdp_bfpt_पढ़ो अणु
	/* The Fast Read x-y-z hardware capability in params->hwcaps.mask. */
	u32			hwcaps;

	/*
	 * The <supported_bit> bit in <supported_dword> BFPT DWORD tells us
	 * whether the Fast Read x-y-z command is supported.
	 */
	u32			supported_dword;
	u32			supported_bit;

	/*
	 * The half-word at offset <setting_shअगरt> in <setting_dword> BFPT DWORD
	 * encodes the op code, the number of mode घड़ीs and the number of रुको
	 * states to be used by Fast Read x-y-z command.
	 */
	u32			settings_dword;
	u32			settings_shअगरt;

	/* The SPI protocol क्रम this Fast Read x-y-z command. */
	क्रमागत spi_nor_protocol	proto;
पूर्ण;

काष्ठा sfdp_bfpt_erase अणु
	/*
	 * The half-word at offset <shअगरt> in DWORD <dword> encodes the
	 * op code and erase sector size to be used by Sector Erase commands.
	 */
	u32			dword;
	u32			shअगरt;
पूर्ण;

#घोषणा SMPT_CMD_ADDRESS_LEN_MASK		GENMASK(23, 22)
#घोषणा SMPT_CMD_ADDRESS_LEN_0			(0x0UL << 22)
#घोषणा SMPT_CMD_ADDRESS_LEN_3			(0x1UL << 22)
#घोषणा SMPT_CMD_ADDRESS_LEN_4			(0x2UL << 22)
#घोषणा SMPT_CMD_ADDRESS_LEN_USE_CURRENT	(0x3UL << 22)

#घोषणा SMPT_CMD_READ_DUMMY_MASK		GENMASK(19, 16)
#घोषणा SMPT_CMD_READ_DUMMY_SHIFT		16
#घोषणा SMPT_CMD_READ_DUMMY(_cmd) \
	(((_cmd) & SMPT_CMD_READ_DUMMY_MASK) >> SMPT_CMD_READ_DUMMY_SHIFT)
#घोषणा SMPT_CMD_READ_DUMMY_IS_VARIABLE		0xfUL

#घोषणा SMPT_CMD_READ_DATA_MASK			GENMASK(31, 24)
#घोषणा SMPT_CMD_READ_DATA_SHIFT		24
#घोषणा SMPT_CMD_READ_DATA(_cmd) \
	(((_cmd) & SMPT_CMD_READ_DATA_MASK) >> SMPT_CMD_READ_DATA_SHIFT)

#घोषणा SMPT_CMD_OPCODE_MASK			GENMASK(15, 8)
#घोषणा SMPT_CMD_OPCODE_SHIFT			8
#घोषणा SMPT_CMD_OPCODE(_cmd) \
	(((_cmd) & SMPT_CMD_OPCODE_MASK) >> SMPT_CMD_OPCODE_SHIFT)

#घोषणा SMPT_MAP_REGION_COUNT_MASK		GENMASK(23, 16)
#घोषणा SMPT_MAP_REGION_COUNT_SHIFT		16
#घोषणा SMPT_MAP_REGION_COUNT(_header) \
	((((_header) & SMPT_MAP_REGION_COUNT_MASK) >> \
	  SMPT_MAP_REGION_COUNT_SHIFT) + 1)

#घोषणा SMPT_MAP_ID_MASK			GENMASK(15, 8)
#घोषणा SMPT_MAP_ID_SHIFT			8
#घोषणा SMPT_MAP_ID(_header) \
	(((_header) & SMPT_MAP_ID_MASK) >> SMPT_MAP_ID_SHIFT)

#घोषणा SMPT_MAP_REGION_SIZE_MASK		GENMASK(31, 8)
#घोषणा SMPT_MAP_REGION_SIZE_SHIFT		8
#घोषणा SMPT_MAP_REGION_SIZE(_region) \
	(((((_region) & SMPT_MAP_REGION_SIZE_MASK) >> \
	   SMPT_MAP_REGION_SIZE_SHIFT) + 1) * 256)

#घोषणा SMPT_MAP_REGION_ERASE_TYPE_MASK		GENMASK(3, 0)
#घोषणा SMPT_MAP_REGION_ERASE_TYPE(_region) \
	((_region) & SMPT_MAP_REGION_ERASE_TYPE_MASK)

#घोषणा SMPT_DESC_TYPE_MAP			BIT(1)
#घोषणा SMPT_DESC_END				BIT(0)

#घोषणा SFDP_4BAIT_DWORD_MAX	2

काष्ठा sfdp_4bait अणु
	/* The hardware capability. */
	u32		hwcaps;

	/*
	 * The <supported_bit> bit in DWORD1 of the 4BAIT tells us whether
	 * the associated 4-byte address op code is supported.
	 */
	u32		supported_bit;
पूर्ण;

/**
 * spi_nor_पढ़ो_raw() - raw पढ़ो of serial flash memory. पढ़ो_opcode,
 *			addr_width and पढ़ो_dummy members of the काष्ठा spi_nor
 *			should be previously
 * set.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @addr:	offset in the serial flash memory
 * @len:	number of bytes to पढ़ो
 * @buf:	buffer where the data is copied पूर्णांकo (dma-safe memory)
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_पढ़ो_raw(काष्ठा spi_nor *nor, u32 addr, माप_प्रकार len, u8 *buf)
अणु
	sमाप_प्रकार ret;

	जबतक (len) अणु
		ret = spi_nor_पढ़ो_data(nor, addr, len, buf);
		अगर (ret < 0)
			वापस ret;
		अगर (!ret || ret > len)
			वापस -EIO;

		buf += ret;
		addr += ret;
		len -= ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * spi_nor_पढ़ो_sfdp() - पढ़ो Serial Flash Discoverable Parameters.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @addr:	offset in the SFDP area to start पढ़ोing data from
 * @len:	number of bytes to पढ़ो
 * @buf:	buffer where the SFDP data are copied पूर्णांकo (dma-safe memory)
 *
 * Whatever the actual numbers of bytes क्रम address and dummy cycles are
 * क्रम (Fast) Read commands, the Read SFDP (5Ah) inकाष्ठाion is always
 * followed by a 3-byte address and 8 dummy घड़ी cycles.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_पढ़ो_sfdp(काष्ठा spi_nor *nor, u32 addr,
			     माप_प्रकार len, व्योम *buf)
अणु
	u8 addr_width, पढ़ो_opcode, पढ़ो_dummy;
	पूर्णांक ret;

	पढ़ो_opcode = nor->पढ़ो_opcode;
	addr_width = nor->addr_width;
	पढ़ो_dummy = nor->पढ़ो_dummy;

	nor->पढ़ो_opcode = SPINOR_OP_RDSFDP;
	nor->addr_width = 3;
	nor->पढ़ो_dummy = 8;

	ret = spi_nor_पढ़ो_raw(nor, addr, len, buf);

	nor->पढ़ो_opcode = पढ़ो_opcode;
	nor->addr_width = addr_width;
	nor->पढ़ो_dummy = पढ़ो_dummy;

	वापस ret;
पूर्ण

/**
 * spi_nor_पढ़ो_sfdp_dma_unsafe() - पढ़ो Serial Flash Discoverable Parameters.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @addr:	offset in the SFDP area to start पढ़ोing data from
 * @len:	number of bytes to पढ़ो
 * @buf:	buffer where the SFDP data are copied पूर्णांकo
 *
 * Wrap spi_nor_पढ़ो_sfdp() using a kदो_स्मृति'ed bounce buffer as @buf is now not
 * guaranteed to be dma-safe.
 *
 * Return: -ENOMEM अगर kदो_स्मृति() fails, the वापस code of spi_nor_पढ़ो_sfdp()
 *          otherwise.
 */
अटल पूर्णांक spi_nor_पढ़ो_sfdp_dma_unsafe(काष्ठा spi_nor *nor, u32 addr,
					माप_प्रकार len, व्योम *buf)
अणु
	व्योम *dma_safe_buf;
	पूर्णांक ret;

	dma_safe_buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!dma_safe_buf)
		वापस -ENOMEM;

	ret = spi_nor_पढ़ो_sfdp(nor, addr, len, dma_safe_buf);
	स_नकल(buf, dma_safe_buf, len);
	kमुक्त(dma_safe_buf);

	वापस ret;
पूर्ण

अटल व्योम
spi_nor_set_पढ़ो_settings_from_bfpt(काष्ठा spi_nor_पढ़ो_command *पढ़ो,
				    u16 half,
				    क्रमागत spi_nor_protocol proto)
अणु
	पढ़ो->num_mode_घड़ीs = (half >> 5) & 0x07;
	पढ़ो->num_रुको_states = (half >> 0) & 0x1f;
	पढ़ो->opcode = (half >> 8) & 0xff;
	पढ़ो->proto = proto;
पूर्ण

अटल स्थिर काष्ठा sfdp_bfpt_पढ़ो sfdp_bfpt_पढ़ोs[] = अणु
	/* Fast Read 1-1-2 */
	अणु
		SNOR_HWCAPS_READ_1_1_2,
		BFPT_DWORD(1), BIT(16),	/* Supported bit */
		BFPT_DWORD(4), 0,	/* Settings */
		SNOR_PROTO_1_1_2,
	पूर्ण,

	/* Fast Read 1-2-2 */
	अणु
		SNOR_HWCAPS_READ_1_2_2,
		BFPT_DWORD(1), BIT(20),	/* Supported bit */
		BFPT_DWORD(4), 16,	/* Settings */
		SNOR_PROTO_1_2_2,
	पूर्ण,

	/* Fast Read 2-2-2 */
	अणु
		SNOR_HWCAPS_READ_2_2_2,
		BFPT_DWORD(5),  BIT(0),	/* Supported bit */
		BFPT_DWORD(6), 16,	/* Settings */
		SNOR_PROTO_2_2_2,
	पूर्ण,

	/* Fast Read 1-1-4 */
	अणु
		SNOR_HWCAPS_READ_1_1_4,
		BFPT_DWORD(1), BIT(22),	/* Supported bit */
		BFPT_DWORD(3), 16,	/* Settings */
		SNOR_PROTO_1_1_4,
	पूर्ण,

	/* Fast Read 1-4-4 */
	अणु
		SNOR_HWCAPS_READ_1_4_4,
		BFPT_DWORD(1), BIT(21),	/* Supported bit */
		BFPT_DWORD(3), 0,	/* Settings */
		SNOR_PROTO_1_4_4,
	पूर्ण,

	/* Fast Read 4-4-4 */
	अणु
		SNOR_HWCAPS_READ_4_4_4,
		BFPT_DWORD(5), BIT(4),	/* Supported bit */
		BFPT_DWORD(7), 16,	/* Settings */
		SNOR_PROTO_4_4_4,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sfdp_bfpt_erase sfdp_bfpt_erases[] = अणु
	/* Erase Type 1 in DWORD8 bits[15:0] */
	अणुBFPT_DWORD(8), 0पूर्ण,

	/* Erase Type 2 in DWORD8 bits[31:16] */
	अणुBFPT_DWORD(8), 16पूर्ण,

	/* Erase Type 3 in DWORD9 bits[15:0] */
	अणुBFPT_DWORD(9), 0पूर्ण,

	/* Erase Type 4 in DWORD9 bits[31:16] */
	अणुBFPT_DWORD(9), 16पूर्ण,
पूर्ण;

/**
 * spi_nor_set_erase_settings_from_bfpt() - set erase type settings from BFPT
 * @erase:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase type
 * @size:	the size of the sector/block erased by the erase type
 * @opcode:	the SPI command op code to erase the sector/block
 * @i:		erase type index as sorted in the Basic Flash Parameter Table
 *
 * The supported Erase Types will be sorted at init in ascending order, with
 * the smallest Erase Type size being the first member in the erase_type array
 * of the spi_nor_erase_map काष्ठाure. Save the Erase Type index as sorted in
 * the Basic Flash Parameter Table since it will be used later on to
 * synchronize with the supported Erase Types defined in SFDP optional tables.
 */
अटल व्योम
spi_nor_set_erase_settings_from_bfpt(काष्ठा spi_nor_erase_type *erase,
				     u32 size, u8 opcode, u8 i)
अणु
	erase->idx = i;
	spi_nor_set_erase_type(erase, size, opcode);
पूर्ण

/**
 * spi_nor_map_cmp_erase_type() - compare the map's erase types by size
 * @l:	member in the left half of the map's erase_type array
 * @r:	member in the right half of the map's erase_type array
 *
 * Comparison function used in the sort() call to sort in ascending order the
 * map's erase types, the smallest erase type size being the first member in the
 * sorted erase_type array.
 *
 * Return: the result of @l->size - @r->size
 */
अटल पूर्णांक spi_nor_map_cmp_erase_type(स्थिर व्योम *l, स्थिर व्योम *r)
अणु
	स्थिर काष्ठा spi_nor_erase_type *left = l, *right = r;

	वापस left->size - right->size;
पूर्ण

/**
 * spi_nor_sort_erase_mask() - sort erase mask
 * @map:	the erase map of the SPI NOR
 * @erase_mask:	the erase type mask to be sorted
 *
 * Replicate the sort करोne क्रम the map's erase types in BFPT: sort the erase
 * mask in ascending order with the smallest erase type size starting from
 * BIT(0) in the sorted erase mask.
 *
 * Return: sorted erase mask.
 */
अटल u8 spi_nor_sort_erase_mask(काष्ठा spi_nor_erase_map *map, u8 erase_mask)
अणु
	काष्ठा spi_nor_erase_type *erase_type = map->erase_type;
	पूर्णांक i;
	u8 sorted_erase_mask = 0;

	अगर (!erase_mask)
		वापस 0;

	/* Replicate the sort करोne क्रम the map's erase types. */
	क्रम (i = 0; i < SNOR_ERASE_TYPE_MAX; i++)
		अगर (erase_type[i].size && erase_mask & BIT(erase_type[i].idx))
			sorted_erase_mask |= BIT(i);

	वापस sorted_erase_mask;
पूर्ण

/**
 * spi_nor_regions_sort_erase_types() - sort erase types in each region
 * @map:	the erase map of the SPI NOR
 *
 * Function assumes that the erase types defined in the erase map are alपढ़ोy
 * sorted in ascending order, with the smallest erase type size being the first
 * member in the erase_type array. It replicates the sort करोne क्रम the map's
 * erase types. Each region's erase biपंचांगask will indicate which erase types are
 * supported from the sorted erase types defined in the erase map.
 * Sort the all region's erase type at init in order to speed up the process of
 * finding the best erase command at runसमय.
 */
अटल व्योम spi_nor_regions_sort_erase_types(काष्ठा spi_nor_erase_map *map)
अणु
	काष्ठा spi_nor_erase_region *region = map->regions;
	u8 region_erase_mask, sorted_erase_mask;

	जबतक (region) अणु
		region_erase_mask = region->offset & SNOR_ERASE_TYPE_MASK;

		sorted_erase_mask = spi_nor_sort_erase_mask(map,
							    region_erase_mask);

		/* Overग_लिखो erase mask. */
		region->offset = (region->offset & ~SNOR_ERASE_TYPE_MASK) |
				 sorted_erase_mask;

		region = spi_nor_region_next(region);
	पूर्ण
पूर्ण

/**
 * spi_nor_parse_bfpt() - पढ़ो and parse the Basic Flash Parameter Table.
 * @nor:		poपूर्णांकer to a 'struct spi_nor'
 * @bfpt_header:	poपूर्णांकer to the 'struct sfdp_parameter_header' describing
 *			the Basic Flash Parameter Table length and version
 *
 * The Basic Flash Parameter Table is the मुख्य and only mandatory table as
 * defined by the SFDP (JESD216) specअगरication.
 * It provides us with the total size (memory density) of the data array and
 * the number of address bytes क्रम Fast Read, Page Program and Sector Erase
 * commands.
 * For Fast READ commands, it also gives the number of mode घड़ी cycles and
 * रुको states (regrouped in the number of dummy घड़ी cycles) क्रम each
 * supported inकाष्ठाion op code.
 * For Page Program, the page size is now available since JESD216 rev A, however
 * the supported inकाष्ठाion op codes are still not provided.
 * For Sector Erase commands, this table stores the supported inकाष्ठाion op
 * codes and the associated sector sizes.
 * Finally, the Quad Enable Requirements (QER) are also available since JESD216
 * rev A. The QER bits encode the manufacturer dependent procedure to be
 * executed to set the Quad Enable (QE) bit in some पूर्णांकernal रेजिस्टर of the
 * Quad SPI memory. Indeed the QE bit, when it exists, must be set beक्रमe
 * sending any Quad SPI command to the memory. Actually, setting the QE bit
 * tells the memory to reassign its WP# and HOLD#/RESET# pins to functions IO2
 * and IO3 hence enabling 4 (Quad) I/O lines.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_parse_bfpt(काष्ठा spi_nor *nor,
			      स्थिर काष्ठा sfdp_parameter_header *bfpt_header)
अणु
	काष्ठा spi_nor_flash_parameter *params = nor->params;
	काष्ठा spi_nor_erase_map *map = &params->erase_map;
	काष्ठा spi_nor_erase_type *erase_type = map->erase_type;
	काष्ठा sfdp_bfpt bfpt;
	माप_प्रकार len;
	पूर्णांक i, cmd, err;
	u32 addr, val;
	u16 half;
	u8 erase_mask;

	/* JESD216 Basic Flash Parameter Table length is at least 9 DWORDs. */
	अगर (bfpt_header->length < BFPT_DWORD_MAX_JESD216)
		वापस -EINVAL;

	/* Read the Basic Flash Parameter Table. */
	len = min_t(माप_प्रकार, माप(bfpt),
		    bfpt_header->length * माप(u32));
	addr = SFDP_PARAM_HEADER_PTP(bfpt_header);
	स_रखो(&bfpt, 0, माप(bfpt));
	err = spi_nor_पढ़ो_sfdp_dma_unsafe(nor,  addr, len, &bfpt);
	अगर (err < 0)
		वापस err;

	/* Fix endianness of the BFPT DWORDs. */
	le32_to_cpu_array(bfpt.dwords, BFPT_DWORD_MAX);

	/* Number of address bytes. */
	चयन (bfpt.dwords[BFPT_DWORD(1)] & BFPT_DWORD1_ADDRESS_BYTES_MASK) अणु
	हाल BFPT_DWORD1_ADDRESS_BYTES_3_ONLY:
	हाल BFPT_DWORD1_ADDRESS_BYTES_3_OR_4:
		nor->addr_width = 3;
		अवरोध;

	हाल BFPT_DWORD1_ADDRESS_BYTES_4_ONLY:
		nor->addr_width = 4;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Flash Memory Density (in bits). */
	val = bfpt.dwords[BFPT_DWORD(2)];
	अगर (val & BIT(31)) अणु
		val &= ~BIT(31);

		/*
		 * Prevent overflows on params->size. Anyway, a NOR of 2^64
		 * bits is unlikely to exist so this error probably means
		 * the BFPT we are पढ़ोing is corrupted/wrong.
		 */
		अगर (val > 63)
			वापस -EINVAL;

		params->size = 1ULL << val;
	पूर्ण अन्यथा अणु
		params->size = val + 1;
	पूर्ण
	params->size >>= 3; /* Convert to bytes. */

	/* Fast Read settings. */
	क्रम (i = 0; i < ARRAY_SIZE(sfdp_bfpt_पढ़ोs); i++) अणु
		स्थिर काष्ठा sfdp_bfpt_पढ़ो *rd = &sfdp_bfpt_पढ़ोs[i];
		काष्ठा spi_nor_पढ़ो_command *पढ़ो;

		अगर (!(bfpt.dwords[rd->supported_dword] & rd->supported_bit)) अणु
			params->hwcaps.mask &= ~rd->hwcaps;
			जारी;
		पूर्ण

		params->hwcaps.mask |= rd->hwcaps;
		cmd = spi_nor_hwcaps_पढ़ो2cmd(rd->hwcaps);
		पढ़ो = &params->पढ़ोs[cmd];
		half = bfpt.dwords[rd->settings_dword] >> rd->settings_shअगरt;
		spi_nor_set_पढ़ो_settings_from_bfpt(पढ़ो, half, rd->proto);
	पूर्ण

	/*
	 * Sector Erase settings. Reinitialize the unअगरorm erase map using the
	 * Erase Types defined in the bfpt table.
	 */
	erase_mask = 0;
	स_रखो(&params->erase_map, 0, माप(params->erase_map));
	क्रम (i = 0; i < ARRAY_SIZE(sfdp_bfpt_erases); i++) अणु
		स्थिर काष्ठा sfdp_bfpt_erase *er = &sfdp_bfpt_erases[i];
		u32 erasesize;
		u8 opcode;

		half = bfpt.dwords[er->dword] >> er->shअगरt;
		erasesize = half & 0xff;

		/* erasesize == 0 means this Erase Type is not supported. */
		अगर (!erasesize)
			जारी;

		erasesize = 1U << erasesize;
		opcode = (half >> 8) & 0xff;
		erase_mask |= BIT(i);
		spi_nor_set_erase_settings_from_bfpt(&erase_type[i], erasesize,
						     opcode, i);
	पूर्ण
	spi_nor_init_unअगरorm_erase_map(map, erase_mask, params->size);
	/*
	 * Sort all the map's Erase Types in ascending order with the smallest
	 * erase size being the first member in the erase_type array.
	 */
	sort(erase_type, SNOR_ERASE_TYPE_MAX, माप(erase_type[0]),
	     spi_nor_map_cmp_erase_type, शून्य);
	/*
	 * Sort the erase types in the unअगरorm region in order to update the
	 * unअगरorm_erase_type biपंचांगask. The biपंचांगask will be used later on when
	 * selecting the unअगरorm erase.
	 */
	spi_nor_regions_sort_erase_types(map);
	map->unअगरorm_erase_type = map->unअगरorm_region.offset &
				  SNOR_ERASE_TYPE_MASK;

	/* Stop here अगर not JESD216 rev A or later. */
	अगर (bfpt_header->length == BFPT_DWORD_MAX_JESD216)
		वापस spi_nor_post_bfpt_fixups(nor, bfpt_header, &bfpt);

	/* Page size: this field specअगरies 'N' so the page size = 2^N bytes. */
	val = bfpt.dwords[BFPT_DWORD(11)];
	val &= BFPT_DWORD11_PAGE_SIZE_MASK;
	val >>= BFPT_DWORD11_PAGE_SIZE_SHIFT;
	params->page_size = 1U << val;

	/* Quad Enable Requirements. */
	चयन (bfpt.dwords[BFPT_DWORD(15)] & BFPT_DWORD15_QER_MASK) अणु
	हाल BFPT_DWORD15_QER_NONE:
		params->quad_enable = शून्य;
		अवरोध;

	हाल BFPT_DWORD15_QER_SR2_BIT1_BUGGY:
		/*
		 * Writing only one byte to the Status Register has the
		 * side-effect of clearing Status Register 2.
		 */
	हाल BFPT_DWORD15_QER_SR2_BIT1_NO_RD:
		/*
		 * Read Configuration Register (35h) inकाष्ठाion is not
		 * supported.
		 */
		nor->flags |= SNOR_F_HAS_16BIT_SR | SNOR_F_NO_READ_CR;
		params->quad_enable = spi_nor_sr2_bit1_quad_enable;
		अवरोध;

	हाल BFPT_DWORD15_QER_SR1_BIT6:
		nor->flags &= ~SNOR_F_HAS_16BIT_SR;
		params->quad_enable = spi_nor_sr1_bit6_quad_enable;
		अवरोध;

	हाल BFPT_DWORD15_QER_SR2_BIT7:
		nor->flags &= ~SNOR_F_HAS_16BIT_SR;
		params->quad_enable = spi_nor_sr2_bit7_quad_enable;
		अवरोध;

	हाल BFPT_DWORD15_QER_SR2_BIT1:
		/*
		 * JESD216 rev B or later करोes not specअगरy अगर writing only one
		 * byte to the Status Register clears or not the Status
		 * Register 2, so let's be cautious and keep the शेष
		 * assumption of a 16-bit Write Status (01h) command.
		 */
		nor->flags |= SNOR_F_HAS_16BIT_SR;

		params->quad_enable = spi_nor_sr2_bit1_quad_enable;
		अवरोध;

	शेष:
		dev_dbg(nor->dev, "BFPT QER reserved value used\n");
		अवरोध;
	पूर्ण

	/* Soft Reset support. */
	अगर (bfpt.dwords[BFPT_DWORD(16)] & BFPT_DWORD16_SWRST_EN_RST)
		nor->flags |= SNOR_F_SOFT_RESET;

	/* Stop here अगर not JESD216 rev C or later. */
	अगर (bfpt_header->length == BFPT_DWORD_MAX_JESD216B)
		वापस spi_nor_post_bfpt_fixups(nor, bfpt_header, &bfpt);

	/* 8D-8D-8D command extension. */
	चयन (bfpt.dwords[BFPT_DWORD(18)] & BFPT_DWORD18_CMD_EXT_MASK) अणु
	हाल BFPT_DWORD18_CMD_EXT_REP:
		nor->cmd_ext_type = SPI_NOR_EXT_REPEAT;
		अवरोध;

	हाल BFPT_DWORD18_CMD_EXT_INV:
		nor->cmd_ext_type = SPI_NOR_EXT_INVERT;
		अवरोध;

	हाल BFPT_DWORD18_CMD_EXT_RES:
		dev_dbg(nor->dev, "Reserved command extension used\n");
		अवरोध;

	हाल BFPT_DWORD18_CMD_EXT_16B:
		dev_dbg(nor->dev, "16-bit opcodes not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस spi_nor_post_bfpt_fixups(nor, bfpt_header, &bfpt);
पूर्ण

/**
 * spi_nor_smpt_addr_width() - वापस the address width used in the
 *			       configuration detection command.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @settings:	configuration detection command descriptor, dword1
 */
अटल u8 spi_nor_smpt_addr_width(स्थिर काष्ठा spi_nor *nor, स्थिर u32 settings)
अणु
	चयन (settings & SMPT_CMD_ADDRESS_LEN_MASK) अणु
	हाल SMPT_CMD_ADDRESS_LEN_0:
		वापस 0;
	हाल SMPT_CMD_ADDRESS_LEN_3:
		वापस 3;
	हाल SMPT_CMD_ADDRESS_LEN_4:
		वापस 4;
	हाल SMPT_CMD_ADDRESS_LEN_USE_CURRENT:
	शेष:
		वापस nor->addr_width;
	पूर्ण
पूर्ण

/**
 * spi_nor_smpt_पढ़ो_dummy() - वापस the configuration detection command पढ़ो
 *			       latency, in घड़ी cycles.
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @settings:	configuration detection command descriptor, dword1
 *
 * Return: the number of dummy cycles क्रम an SMPT पढ़ो
 */
अटल u8 spi_nor_smpt_पढ़ो_dummy(स्थिर काष्ठा spi_nor *nor, स्थिर u32 settings)
अणु
	u8 पढ़ो_dummy = SMPT_CMD_READ_DUMMY(settings);

	अगर (पढ़ो_dummy == SMPT_CMD_READ_DUMMY_IS_VARIABLE)
		वापस nor->पढ़ो_dummy;
	वापस पढ़ो_dummy;
पूर्ण

/**
 * spi_nor_get_map_in_use() - get the configuration map in use
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @smpt:	poपूर्णांकer to the sector map parameter table
 * @smpt_len:	sector map parameter table length
 *
 * Return: poपूर्णांकer to the map in use, ERR_PTR(-त्रुटि_सं) otherwise.
 */
अटल स्थिर u32 *spi_nor_get_map_in_use(काष्ठा spi_nor *nor, स्थिर u32 *smpt,
					 u8 smpt_len)
अणु
	स्थिर u32 *ret;
	u8 *buf;
	u32 addr;
	पूर्णांक err;
	u8 i;
	u8 addr_width, पढ़ो_opcode, पढ़ो_dummy;
	u8 पढ़ो_data_mask, map_id;

	/* Use a kदो_स्मृति'ed bounce buffer to guarantee it is DMA-able. */
	buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	addr_width = nor->addr_width;
	पढ़ो_dummy = nor->पढ़ो_dummy;
	पढ़ो_opcode = nor->पढ़ो_opcode;

	map_id = 0;
	/* Determine अगर there are any optional Detection Command Descriptors */
	क्रम (i = 0; i < smpt_len; i += 2) अणु
		अगर (smpt[i] & SMPT_DESC_TYPE_MAP)
			अवरोध;

		पढ़ो_data_mask = SMPT_CMD_READ_DATA(smpt[i]);
		nor->addr_width = spi_nor_smpt_addr_width(nor, smpt[i]);
		nor->पढ़ो_dummy = spi_nor_smpt_पढ़ो_dummy(nor, smpt[i]);
		nor->पढ़ो_opcode = SMPT_CMD_OPCODE(smpt[i]);
		addr = smpt[i + 1];

		err = spi_nor_पढ़ो_raw(nor, addr, 1, buf);
		अगर (err) अणु
			ret = ERR_PTR(err);
			जाओ out;
		पूर्ण

		/*
		 * Build an index value that is used to select the Sector Map
		 * Configuration that is currently in use.
		 */
		map_id = map_id << 1 | !!(*buf & पढ़ो_data_mask);
	पूर्ण

	/*
	 * If command descriptors are provided, they always precede map
	 * descriptors in the table. There is no need to start the iteration
	 * over smpt array all over again.
	 *
	 * Find the matching configuration map.
	 */
	ret = ERR_PTR(-EINVAL);
	जबतक (i < smpt_len) अणु
		अगर (SMPT_MAP_ID(smpt[i]) == map_id) अणु
			ret = smpt + i;
			अवरोध;
		पूर्ण

		/*
		 * If there are no more configuration map descriptors and no
		 * configuration ID matched the configuration identअगरier, the
		 * sector address map is unknown.
		 */
		अगर (smpt[i] & SMPT_DESC_END)
			अवरोध;

		/* increment the table index to the next map */
		i += SMPT_MAP_REGION_COUNT(smpt[i]) + 1;
	पूर्ण

	/* fall through */
out:
	kमुक्त(buf);
	nor->addr_width = addr_width;
	nor->पढ़ो_dummy = पढ़ो_dummy;
	nor->पढ़ो_opcode = पढ़ो_opcode;
	वापस ret;
पूर्ण

अटल व्योम spi_nor_region_mark_end(काष्ठा spi_nor_erase_region *region)
अणु
	region->offset |= SNOR_LAST_REGION;
पूर्ण

अटल व्योम spi_nor_region_mark_overlay(काष्ठा spi_nor_erase_region *region)
अणु
	region->offset |= SNOR_OVERLAID_REGION;
पूर्ण

/**
 * spi_nor_region_check_overlay() - set overlay bit when the region is overlaid
 * @region:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase region
 * @erase:	poपूर्णांकer to a काष्ठाure that describes a SPI NOR erase type
 * @erase_type:	erase type biपंचांगask
 */
अटल व्योम
spi_nor_region_check_overlay(काष्ठा spi_nor_erase_region *region,
			     स्थिर काष्ठा spi_nor_erase_type *erase,
			     स्थिर u8 erase_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SNOR_ERASE_TYPE_MAX; i++) अणु
		अगर (!(erase[i].size && erase_type & BIT(erase[i].idx)))
			जारी;
		अगर (region->size & erase[i].size_mask) अणु
			spi_nor_region_mark_overlay(region);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * spi_nor_init_non_unअगरorm_erase_map() - initialize the non-unअगरorm erase map
 * @nor:	poपूर्णांकer to a 'struct spi_nor'
 * @smpt:	poपूर्णांकer to the sector map parameter table
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_init_non_unअगरorm_erase_map(काष्ठा spi_nor *nor,
					      स्थिर u32 *smpt)
अणु
	काष्ठा spi_nor_erase_map *map = &nor->params->erase_map;
	काष्ठा spi_nor_erase_type *erase = map->erase_type;
	काष्ठा spi_nor_erase_region *region;
	u64 offset;
	u32 region_count;
	पूर्णांक i, j;
	u8 unअगरorm_erase_type, save_unअगरorm_erase_type;
	u8 erase_type, regions_erase_type;

	region_count = SMPT_MAP_REGION_COUNT(*smpt);
	/*
	 * The regions will be मुक्तd when the driver detaches from the
	 * device.
	 */
	region = devm_kसुस्मृति(nor->dev, region_count, माप(*region),
			      GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;
	map->regions = region;

	unअगरorm_erase_type = 0xff;
	regions_erase_type = 0;
	offset = 0;
	/* Populate regions. */
	क्रम (i = 0; i < region_count; i++) अणु
		j = i + 1; /* index क्रम the region dword */
		region[i].size = SMPT_MAP_REGION_SIZE(smpt[j]);
		erase_type = SMPT_MAP_REGION_ERASE_TYPE(smpt[j]);
		region[i].offset = offset | erase_type;

		spi_nor_region_check_overlay(&region[i], erase, erase_type);

		/*
		 * Save the erase types that are supported in all regions and
		 * can erase the entire flash memory.
		 */
		unअगरorm_erase_type &= erase_type;

		/*
		 * regions_erase_type mask will indicate all the erase types
		 * supported in this configuration map.
		 */
		regions_erase_type |= erase_type;

		offset = (region[i].offset & ~SNOR_ERASE_FLAGS_MASK) +
			 region[i].size;
	पूर्ण
	spi_nor_region_mark_end(&region[i - 1]);

	save_unअगरorm_erase_type = map->unअगरorm_erase_type;
	map->unअगरorm_erase_type = spi_nor_sort_erase_mask(map,
							  unअगरorm_erase_type);

	अगर (!regions_erase_type) अणु
		/*
		 * Roll back to the previous unअगरorm_erase_type mask, SMPT is
		 * broken.
		 */
		map->unअगरorm_erase_type = save_unअगरorm_erase_type;
		वापस -EINVAL;
	पूर्ण

	/*
	 * BFPT advertises all the erase types supported by all the possible
	 * map configurations. Mask out the erase types that are not supported
	 * by the current map configuration.
	 */
	क्रम (i = 0; i < SNOR_ERASE_TYPE_MAX; i++)
		अगर (!(regions_erase_type & BIT(erase[i].idx)))
			spi_nor_set_erase_type(&erase[i], 0, 0xFF);

	वापस 0;
पूर्ण

/**
 * spi_nor_parse_smpt() - parse Sector Map Parameter Table
 * @nor:		poपूर्णांकer to a 'struct spi_nor'
 * @smpt_header:	sector map parameter table header
 *
 * This table is optional, but when available, we parse it to identअगरy the
 * location and size of sectors within the मुख्य data array of the flash memory
 * device and to identअगरy which Erase Types are supported by each sector.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_parse_smpt(काष्ठा spi_nor *nor,
			      स्थिर काष्ठा sfdp_parameter_header *smpt_header)
अणु
	स्थिर u32 *sector_map;
	u32 *smpt;
	माप_प्रकार len;
	u32 addr;
	पूर्णांक ret;

	/* Read the Sector Map Parameter Table. */
	len = smpt_header->length * माप(*smpt);
	smpt = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!smpt)
		वापस -ENOMEM;

	addr = SFDP_PARAM_HEADER_PTP(smpt_header);
	ret = spi_nor_पढ़ो_sfdp(nor, addr, len, smpt);
	अगर (ret)
		जाओ out;

	/* Fix endianness of the SMPT DWORDs. */
	le32_to_cpu_array(smpt, smpt_header->length);

	sector_map = spi_nor_get_map_in_use(nor, smpt, smpt_header->length);
	अगर (IS_ERR(sector_map)) अणु
		ret = PTR_ERR(sector_map);
		जाओ out;
	पूर्ण

	ret = spi_nor_init_non_unअगरorm_erase_map(nor, sector_map);
	अगर (ret)
		जाओ out;

	spi_nor_regions_sort_erase_types(&nor->params->erase_map);
	/* fall through */
out:
	kमुक्त(smpt);
	वापस ret;
पूर्ण

/**
 * spi_nor_parse_4bait() - parse the 4-Byte Address Inकाष्ठाion Table
 * @nor:		poपूर्णांकer to a 'struct spi_nor'.
 * @param_header:	poपूर्णांकer to the 'struct sfdp_parameter_header' describing
 *			the 4-Byte Address Inकाष्ठाion Table length and version.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_parse_4bait(काष्ठा spi_nor *nor,
			       स्थिर काष्ठा sfdp_parameter_header *param_header)
अणु
	अटल स्थिर काष्ठा sfdp_4bait पढ़ोs[] = अणु
		अणु SNOR_HWCAPS_READ,		BIT(0) पूर्ण,
		अणु SNOR_HWCAPS_READ_FAST,	BIT(1) पूर्ण,
		अणु SNOR_HWCAPS_READ_1_1_2,	BIT(2) पूर्ण,
		अणु SNOR_HWCAPS_READ_1_2_2,	BIT(3) पूर्ण,
		अणु SNOR_HWCAPS_READ_1_1_4,	BIT(4) पूर्ण,
		अणु SNOR_HWCAPS_READ_1_4_4,	BIT(5) पूर्ण,
		अणु SNOR_HWCAPS_READ_1_1_1_DTR,	BIT(13) पूर्ण,
		अणु SNOR_HWCAPS_READ_1_2_2_DTR,	BIT(14) पूर्ण,
		अणु SNOR_HWCAPS_READ_1_4_4_DTR,	BIT(15) पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा sfdp_4bait programs[] = अणु
		अणु SNOR_HWCAPS_PP,		BIT(6) पूर्ण,
		अणु SNOR_HWCAPS_PP_1_1_4,		BIT(7) पूर्ण,
		अणु SNOR_HWCAPS_PP_1_4_4,		BIT(8) पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा sfdp_4bait erases[SNOR_ERASE_TYPE_MAX] = अणु
		अणु 0u /* not used */,		BIT(9) पूर्ण,
		अणु 0u /* not used */,		BIT(10) पूर्ण,
		अणु 0u /* not used */,		BIT(11) पूर्ण,
		अणु 0u /* not used */,		BIT(12) पूर्ण,
	पूर्ण;
	काष्ठा spi_nor_flash_parameter *params = nor->params;
	काष्ठा spi_nor_pp_command *params_pp = params->page_programs;
	काष्ठा spi_nor_erase_map *map = &params->erase_map;
	काष्ठा spi_nor_erase_type *erase_type = map->erase_type;
	u32 *dwords;
	माप_प्रकार len;
	u32 addr, discard_hwcaps, पढ़ो_hwcaps, pp_hwcaps, erase_mask;
	पूर्णांक i, ret;

	अगर (param_header->major != SFDP_JESD216_MAJOR ||
	    param_header->length < SFDP_4BAIT_DWORD_MAX)
		वापस -EINVAL;

	/* Read the 4-byte Address Inकाष्ठाion Table. */
	len = माप(*dwords) * SFDP_4BAIT_DWORD_MAX;

	/* Use a kदो_स्मृति'ed bounce buffer to guarantee it is DMA-able. */
	dwords = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!dwords)
		वापस -ENOMEM;

	addr = SFDP_PARAM_HEADER_PTP(param_header);
	ret = spi_nor_पढ़ो_sfdp(nor, addr, len, dwords);
	अगर (ret)
		जाओ out;

	/* Fix endianness of the 4BAIT DWORDs. */
	le32_to_cpu_array(dwords, SFDP_4BAIT_DWORD_MAX);

	/*
	 * Compute the subset of (Fast) Read commands क्रम which the 4-byte
	 * version is supported.
	 */
	discard_hwcaps = 0;
	पढ़ो_hwcaps = 0;
	क्रम (i = 0; i < ARRAY_SIZE(पढ़ोs); i++) अणु
		स्थिर काष्ठा sfdp_4bait *पढ़ो = &पढ़ोs[i];

		discard_hwcaps |= पढ़ो->hwcaps;
		अगर ((params->hwcaps.mask & पढ़ो->hwcaps) &&
		    (dwords[0] & पढ़ो->supported_bit))
			पढ़ो_hwcaps |= पढ़ो->hwcaps;
	पूर्ण

	/*
	 * Compute the subset of Page Program commands क्रम which the 4-byte
	 * version is supported.
	 */
	pp_hwcaps = 0;
	क्रम (i = 0; i < ARRAY_SIZE(programs); i++) अणु
		स्थिर काष्ठा sfdp_4bait *program = &programs[i];

		/*
		 * The 4 Byte Address Inकाष्ठाion (Optional) Table is the only
		 * SFDP table that indicates support क्रम Page Program Commands.
		 * Bypass the params->hwcaps.mask and consider 4BAIT the biggest
		 * authority क्रम specअगरying Page Program support.
		 */
		discard_hwcaps |= program->hwcaps;
		अगर (dwords[0] & program->supported_bit)
			pp_hwcaps |= program->hwcaps;
	पूर्ण

	/*
	 * Compute the subset of Sector Erase commands क्रम which the 4-byte
	 * version is supported.
	 */
	erase_mask = 0;
	क्रम (i = 0; i < SNOR_ERASE_TYPE_MAX; i++) अणु
		स्थिर काष्ठा sfdp_4bait *erase = &erases[i];

		अगर (dwords[0] & erase->supported_bit)
			erase_mask |= BIT(i);
	पूर्ण

	/* Replicate the sort करोne क्रम the map's erase types in BFPT. */
	erase_mask = spi_nor_sort_erase_mask(map, erase_mask);

	/*
	 * We need at least one 4-byte op code per पढ़ो, program and erase
	 * operation; the .पढ़ो(), .ग_लिखो() and .erase() hooks share the
	 * nor->addr_width value.
	 */
	अगर (!पढ़ो_hwcaps || !pp_hwcaps || !erase_mask)
		जाओ out;

	/*
	 * Discard all operations from the 4-byte inकाष्ठाion set which are
	 * not supported by this memory.
	 */
	params->hwcaps.mask &= ~discard_hwcaps;
	params->hwcaps.mask |= (पढ़ो_hwcaps | pp_hwcaps);

	/* Use the 4-byte address inकाष्ठाion set. */
	क्रम (i = 0; i < SNOR_CMD_READ_MAX; i++) अणु
		काष्ठा spi_nor_पढ़ो_command *पढ़ो_cmd = &params->पढ़ोs[i];

		पढ़ो_cmd->opcode = spi_nor_convert_3to4_पढ़ो(पढ़ो_cmd->opcode);
	पूर्ण

	/* 4BAIT is the only SFDP table that indicates page program support. */
	अगर (pp_hwcaps & SNOR_HWCAPS_PP) अणु
		spi_nor_set_pp_settings(&params_pp[SNOR_CMD_PP],
					SPINOR_OP_PP_4B, SNOR_PROTO_1_1_1);
		/*
		 * Since xSPI Page Program opcode is backward compatible with
		 * Legacy SPI, use Legacy SPI opcode there as well.
		 */
		spi_nor_set_pp_settings(&params_pp[SNOR_CMD_PP_8_8_8_DTR],
					SPINOR_OP_PP_4B, SNOR_PROTO_8_8_8_DTR);
	पूर्ण
	अगर (pp_hwcaps & SNOR_HWCAPS_PP_1_1_4)
		spi_nor_set_pp_settings(&params_pp[SNOR_CMD_PP_1_1_4],
					SPINOR_OP_PP_1_1_4_4B,
					SNOR_PROTO_1_1_4);
	अगर (pp_hwcaps & SNOR_HWCAPS_PP_1_4_4)
		spi_nor_set_pp_settings(&params_pp[SNOR_CMD_PP_1_4_4],
					SPINOR_OP_PP_1_4_4_4B,
					SNOR_PROTO_1_4_4);

	क्रम (i = 0; i < SNOR_ERASE_TYPE_MAX; i++) अणु
		अगर (erase_mask & BIT(i))
			erase_type[i].opcode = (dwords[1] >>
						erase_type[i].idx * 8) & 0xFF;
		अन्यथा
			spi_nor_set_erase_type(&erase_type[i], 0u, 0xFF);
	पूर्ण

	/*
	 * We set SNOR_F_HAS_4BAIT in order to skip spi_nor_set_4byte_opcodes()
	 * later because we alपढ़ोy did the conversion to 4byte opcodes. Also,
	 * this latest function implements a legacy quirk क्रम the erase size of
	 * Spansion memory. However this quirk is no दीर्घer needed with new
	 * SFDP compliant memories.
	 */
	nor->addr_width = 4;
	nor->flags |= SNOR_F_4B_OPCODES | SNOR_F_HAS_4BAIT;

	/* fall through */
out:
	kमुक्त(dwords);
	वापस ret;
पूर्ण

#घोषणा PROखाता1_DWORD1_RDSR_ADDR_BYTES		BIT(29)
#घोषणा PROखाता1_DWORD1_RDSR_DUMMY		BIT(28)
#घोषणा PROखाता1_DWORD1_RD_FAST_CMD		GENMASK(15, 8)
#घोषणा PROखाता1_DWORD4_DUMMY_200MHZ		GENMASK(11, 7)
#घोषणा PROखाता1_DWORD5_DUMMY_166MHZ		GENMASK(31, 27)
#घोषणा PROखाता1_DWORD5_DUMMY_133MHZ		GENMASK(21, 17)
#घोषणा PROखाता1_DWORD5_DUMMY_100MHZ		GENMASK(11, 7)

/**
 * spi_nor_parse_profile1() - parse the xSPI Profile 1.0 table
 * @nor:		poपूर्णांकer to a 'struct spi_nor'
 * @profile1_header:	poपूर्णांकer to the 'struct sfdp_parameter_header' describing
 *			the Profile 1.0 Table length and version.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_parse_profile1(काष्ठा spi_nor *nor,
				  स्थिर काष्ठा sfdp_parameter_header *profile1_header)
अणु
	u32 *dwords, addr;
	माप_प्रकार len;
	पूर्णांक ret;
	u8 dummy, opcode;

	len = profile1_header->length * माप(*dwords);
	dwords = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!dwords)
		वापस -ENOMEM;

	addr = SFDP_PARAM_HEADER_PTP(profile1_header);
	ret = spi_nor_पढ़ो_sfdp(nor, addr, len, dwords);
	अगर (ret)
		जाओ out;

	le32_to_cpu_array(dwords, profile1_header->length);

	/* Get 8D-8D-8D fast पढ़ो opcode and dummy cycles. */
	opcode = FIELD_GET(PROखाता1_DWORD1_RD_FAST_CMD, dwords[0]);

	 /* Set the Read Status Register dummy cycles and dummy address bytes. */
	अगर (dwords[0] & PROखाता1_DWORD1_RDSR_DUMMY)
		nor->params->rdsr_dummy = 8;
	अन्यथा
		nor->params->rdsr_dummy = 4;

	अगर (dwords[0] & PROखाता1_DWORD1_RDSR_ADDR_BYTES)
		nor->params->rdsr_addr_nbytes = 4;
	अन्यथा
		nor->params->rdsr_addr_nbytes = 0;

	/*
	 * We करोn't know what speed the controller is running at. Find the
	 * dummy cycles क्रम the fastest frequency the flash can run at to be
	 * sure we are never लघु of dummy cycles. A value of 0 means the
	 * frequency is not supported.
	 *
	 * Default to PROखाता1_DUMMY_DEFAULT अगर we करोn't find anything, and let
	 * flashes set the correct value अगर needed in their fixup hooks.
	 */
	dummy = FIELD_GET(PROखाता1_DWORD4_DUMMY_200MHZ, dwords[3]);
	अगर (!dummy)
		dummy = FIELD_GET(PROखाता1_DWORD5_DUMMY_166MHZ, dwords[4]);
	अगर (!dummy)
		dummy = FIELD_GET(PROखाता1_DWORD5_DUMMY_133MHZ, dwords[4]);
	अगर (!dummy)
		dummy = FIELD_GET(PROखाता1_DWORD5_DUMMY_100MHZ, dwords[4]);
	अगर (!dummy)
		dev_dbg(nor->dev,
			"Can't find dummy cycles from Profile 1.0 table\n");

	/* Round up to an even value to aव्योम tripping controllers up. */
	dummy = round_up(dummy, 2);

	/* Update the fast पढ़ो settings. */
	spi_nor_set_पढ़ो_settings(&nor->params->पढ़ोs[SNOR_CMD_READ_8_8_8_DTR],
				  0, dummy, opcode,
				  SNOR_PROTO_8_8_8_DTR);

out:
	kमुक्त(dwords);
	वापस ret;
पूर्ण

#घोषणा SCCR_DWORD22_OCTAL_DTR_EN_VOLATILE		BIT(31)

/**
 * spi_nor_parse_sccr() - Parse the Status, Control and Configuration Register
 *                        Map.
 * @nor:		poपूर्णांकer to a 'struct spi_nor'
 * @sccr_header:	poपूर्णांकer to the 'struct sfdp_parameter_header' describing
 *			the SCCR Map table length and version.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_parse_sccr(काष्ठा spi_nor *nor,
			      स्थिर काष्ठा sfdp_parameter_header *sccr_header)
अणु
	u32 *dwords, addr;
	माप_प्रकार len;
	पूर्णांक ret;

	len = sccr_header->length * माप(*dwords);
	dwords = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!dwords)
		वापस -ENOMEM;

	addr = SFDP_PARAM_HEADER_PTP(sccr_header);
	ret = spi_nor_पढ़ो_sfdp(nor, addr, len, dwords);
	अगर (ret)
		जाओ out;

	le32_to_cpu_array(dwords, sccr_header->length);

	अगर (FIELD_GET(SCCR_DWORD22_OCTAL_DTR_EN_VOLATILE, dwords[22]))
		nor->flags |= SNOR_F_IO_MODE_EN_VOLATILE;

out:
	kमुक्त(dwords);
	वापस ret;
पूर्ण

/**
 * spi_nor_parse_sfdp() - parse the Serial Flash Discoverable Parameters.
 * @nor:		poपूर्णांकer to a 'struct spi_nor'
 *
 * The Serial Flash Discoverable Parameters are described by the JEDEC JESD216
 * specअगरication. This is a standard which tends to supported by almost all
 * (Q)SPI memory manufacturers. Those hard-coded tables allow us to learn at
 * runसमय the मुख्य parameters needed to perक्रमm basic SPI flash operations such
 * as Fast Read, Page Program or Sector Erase commands.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक spi_nor_parse_sfdp(काष्ठा spi_nor *nor)
अणु
	स्थिर काष्ठा sfdp_parameter_header *param_header, *bfpt_header;
	काष्ठा sfdp_parameter_header *param_headers = शून्य;
	काष्ठा sfdp_header header;
	काष्ठा device *dev = nor->dev;
	माप_प्रकार psize;
	पूर्णांक i, err;

	/* Get the SFDP header. */
	err = spi_nor_पढ़ो_sfdp_dma_unsafe(nor, 0, माप(header), &header);
	अगर (err < 0)
		वापस err;

	/* Check the SFDP header version. */
	अगर (le32_to_cpu(header.signature) != SFDP_SIGNATURE ||
	    header.major != SFDP_JESD216_MAJOR)
		वापस -EINVAL;

	/*
	 * Verअगरy that the first and only mandatory parameter header is a
	 * Basic Flash Parameter Table header as specअगरied in JESD216.
	 */
	bfpt_header = &header.bfpt_header;
	अगर (SFDP_PARAM_HEADER_ID(bfpt_header) != SFDP_BFPT_ID ||
	    bfpt_header->major != SFDP_JESD216_MAJOR)
		वापस -EINVAL;

	/*
	 * Allocate memory then पढ़ो all parameter headers with a single
	 * Read SFDP command. These parameter headers will actually be parsed
	 * twice: a first समय to get the latest revision of the basic flash
	 * parameter table, then a second समय to handle the supported optional
	 * tables.
	 * Hence we पढ़ो the parameter headers once क्रम all to reduce the
	 * processing समय. Also we use kदो_स्मृति() instead of devm_kदो_स्मृति()
	 * because we करोn't need to keep these parameter headers: the allocated
	 * memory is always released with kमुक्त() beक्रमe निकासing this function.
	 */
	अगर (header.nph) अणु
		psize = header.nph * माप(*param_headers);

		param_headers = kदो_स्मृति(psize, GFP_KERNEL);
		अगर (!param_headers)
			वापस -ENOMEM;

		err = spi_nor_पढ़ो_sfdp(nor, माप(header),
					psize, param_headers);
		अगर (err < 0) अणु
			dev_dbg(dev, "failed to read SFDP parameter headers\n");
			जाओ निकास;
		पूर्ण
	पूर्ण

	/*
	 * Check other parameter headers to get the latest revision of
	 * the basic flash parameter table.
	 */
	क्रम (i = 0; i < header.nph; i++) अणु
		param_header = &param_headers[i];

		अगर (SFDP_PARAM_HEADER_ID(param_header) == SFDP_BFPT_ID &&
		    param_header->major == SFDP_JESD216_MAJOR &&
		    (param_header->minor > bfpt_header->minor ||
		     (param_header->minor == bfpt_header->minor &&
		      param_header->length > bfpt_header->length)))
			bfpt_header = param_header;
	पूर्ण

	err = spi_nor_parse_bfpt(nor, bfpt_header);
	अगर (err)
		जाओ निकास;

	/* Parse optional parameter tables. */
	क्रम (i = 0; i < header.nph; i++) अणु
		param_header = &param_headers[i];

		चयन (SFDP_PARAM_HEADER_ID(param_header)) अणु
		हाल SFDP_SECTOR_MAP_ID:
			err = spi_nor_parse_smpt(nor, param_header);
			अवरोध;

		हाल SFDP_4BAIT_ID:
			err = spi_nor_parse_4bait(nor, param_header);
			अवरोध;

		हाल SFDP_PROखाता1_ID:
			err = spi_nor_parse_profile1(nor, param_header);
			अवरोध;

		हाल SFDP_SCCR_MAP_ID:
			err = spi_nor_parse_sccr(nor, param_header);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (err) अणु
			dev_warn(dev, "Failed to parse optional parameter table: %04x\n",
				 SFDP_PARAM_HEADER_ID(param_header));
			/*
			 * Let's not drop all inक्रमmation we extracted so far
			 * अगर optional table parsers fail. In हाल of failing,
			 * each optional parser is responsible to roll back to
			 * the previously known spi_nor data.
			 */
			err = 0;
		पूर्ण
	पूर्ण

निकास:
	kमुक्त(param_headers);
	वापस err;
पूर्ण
