<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __LINUX_MTD_SPI_NOR_INTERNAL_H
#घोषणा __LINUX_MTD_SPI_NOR_INTERNAL_H

#समावेश "sfdp.h"

#घोषणा SPI_NOR_MAX_ID_LEN	6

क्रमागत spi_nor_option_flags अणु
	SNOR_F_USE_FSR		= BIT(0),
	SNOR_F_HAS_SR_TB	= BIT(1),
	SNOR_F_NO_OP_CHIP_ERASE	= BIT(2),
	SNOR_F_READY_XSR_RDY	= BIT(3),
	SNOR_F_USE_CLSR		= BIT(4),
	SNOR_F_BROKEN_RESET	= BIT(5),
	SNOR_F_4B_OPCODES	= BIT(6),
	SNOR_F_HAS_4BAIT	= BIT(7),
	SNOR_F_HAS_LOCK		= BIT(8),
	SNOR_F_HAS_16BIT_SR	= BIT(9),
	SNOR_F_NO_READ_CR	= BIT(10),
	SNOR_F_HAS_SR_TB_BIT6	= BIT(11),
	SNOR_F_HAS_4BIT_BP      = BIT(12),
	SNOR_F_HAS_SR_BP3_BIT6  = BIT(13),
	SNOR_F_IO_MODE_EN_VOLATILE = BIT(14),
	SNOR_F_SOFT_RESET	= BIT(15),
	SNOR_F_SWP_IS_VOLATILE	= BIT(16),
पूर्ण;

काष्ठा spi_nor_पढ़ो_command अणु
	u8			num_mode_घड़ीs;
	u8			num_रुको_states;
	u8			opcode;
	क्रमागत spi_nor_protocol	proto;
पूर्ण;

काष्ठा spi_nor_pp_command अणु
	u8			opcode;
	क्रमागत spi_nor_protocol	proto;
पूर्ण;

क्रमागत spi_nor_पढ़ो_command_index अणु
	SNOR_CMD_READ,
	SNOR_CMD_READ_FAST,
	SNOR_CMD_READ_1_1_1_DTR,

	/* Dual SPI */
	SNOR_CMD_READ_1_1_2,
	SNOR_CMD_READ_1_2_2,
	SNOR_CMD_READ_2_2_2,
	SNOR_CMD_READ_1_2_2_DTR,

	/* Quad SPI */
	SNOR_CMD_READ_1_1_4,
	SNOR_CMD_READ_1_4_4,
	SNOR_CMD_READ_4_4_4,
	SNOR_CMD_READ_1_4_4_DTR,

	/* Octal SPI */
	SNOR_CMD_READ_1_1_8,
	SNOR_CMD_READ_1_8_8,
	SNOR_CMD_READ_8_8_8,
	SNOR_CMD_READ_1_8_8_DTR,
	SNOR_CMD_READ_8_8_8_DTR,

	SNOR_CMD_READ_MAX
पूर्ण;

क्रमागत spi_nor_pp_command_index अणु
	SNOR_CMD_PP,

	/* Quad SPI */
	SNOR_CMD_PP_1_1_4,
	SNOR_CMD_PP_1_4_4,
	SNOR_CMD_PP_4_4_4,

	/* Octal SPI */
	SNOR_CMD_PP_1_1_8,
	SNOR_CMD_PP_1_8_8,
	SNOR_CMD_PP_8_8_8,
	SNOR_CMD_PP_8_8_8_DTR,

	SNOR_CMD_PP_MAX
पूर्ण;

/**
 * काष्ठा spi_nor_erase_type - Structure to describe a SPI NOR erase type
 * @size:		the size of the sector/block erased by the erase type.
 *			JEDEC JESD216B imposes erase sizes to be a घातer of 2.
 * @size_shअगरt:		@size is a घातer of 2, the shअगरt is stored in
 *			@size_shअगरt.
 * @size_mask:		the size mask based on @size_shअगरt.
 * @opcode:		the SPI command op code to erase the sector/block.
 * @idx:		Erase Type index as sorted in the Basic Flash Parameter
 *			Table. It will be used to synchronize the supported
 *			Erase Types with the ones identअगरied in the SFDP
 *			optional tables.
 */
काष्ठा spi_nor_erase_type अणु
	u32	size;
	u32	size_shअगरt;
	u32	size_mask;
	u8	opcode;
	u8	idx;
पूर्ण;

/**
 * काष्ठा spi_nor_erase_command - Used क्रम non-unअगरorm erases
 * The काष्ठाure is used to describe a list of erase commands to be executed
 * once we validate that the erase can be perक्रमmed. The elements in the list
 * are run-length encoded.
 * @list:		क्रम inclusion पूर्णांकo the list of erase commands.
 * @count:		how many बार the same erase command should be
 *			consecutively used.
 * @size:		the size of the sector/block erased by the command.
 * @opcode:		the SPI command op code to erase the sector/block.
 */
काष्ठा spi_nor_erase_command अणु
	काष्ठा list_head	list;
	u32			count;
	u32			size;
	u8			opcode;
पूर्ण;

/**
 * काष्ठा spi_nor_erase_region - Structure to describe a SPI NOR erase region
 * @offset:		the offset in the data array of erase region start.
 *			LSB bits are used as a biपंचांगask encoding flags to
 *			determine अगर this region is overlaid, अगर this region is
 *			the last in the SPI NOR flash memory and to indicate
 *			all the supported erase commands inside this region.
 *			The erase types are sorted in ascending order with the
 *			smallest Erase Type size being at BIT(0).
 * @size:		the size of the region in bytes.
 */
काष्ठा spi_nor_erase_region अणु
	u64		offset;
	u64		size;
पूर्ण;

#घोषणा SNOR_ERASE_TYPE_MAX	4
#घोषणा SNOR_ERASE_TYPE_MASK	GENMASK_ULL(SNOR_ERASE_TYPE_MAX - 1, 0)

#घोषणा SNOR_LAST_REGION	BIT(4)
#घोषणा SNOR_OVERLAID_REGION	BIT(5)

#घोषणा SNOR_ERASE_FLAGS_MAX	6
#घोषणा SNOR_ERASE_FLAGS_MASK	GENMASK_ULL(SNOR_ERASE_FLAGS_MAX - 1, 0)

/**
 * काष्ठा spi_nor_erase_map - Structure to describe the SPI NOR erase map
 * @regions:		array of erase regions. The regions are consecutive in
 *			address space. Walking through the regions is करोne
 *			incrementally.
 * @unअगरorm_region:	a pre-allocated erase region क्रम SPI NOR with a unअगरorm
 *			sector size (legacy implementation).
 * @erase_type:		an array of erase types shared by all the regions.
 *			The erase types are sorted in ascending order, with the
 *			smallest Erase Type size being the first member in the
 *			erase_type array.
 * @unअगरorm_erase_type:	biपंचांगask encoding erase types that can erase the
 *			entire memory. This member is completed at init by
 *			unअगरorm and non-unअगरorm SPI NOR flash memories अगर they
 *			support at least one erase type that can erase the
 *			entire memory.
 */
काष्ठा spi_nor_erase_map अणु
	काष्ठा spi_nor_erase_region	*regions;
	काष्ठा spi_nor_erase_region	unअगरorm_region;
	काष्ठा spi_nor_erase_type	erase_type[SNOR_ERASE_TYPE_MAX];
	u8				unअगरorm_erase_type;
पूर्ण;

/**
 * काष्ठा spi_nor_locking_ops - SPI NOR locking methods
 * @lock:	lock a region of the SPI NOR.
 * @unlock:	unlock a region of the SPI NOR.
 * @is_locked:	check अगर a region of the SPI NOR is completely locked
 */
काष्ठा spi_nor_locking_ops अणु
	पूर्णांक (*lock)(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len);
	पूर्णांक (*unlock)(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len);
	पूर्णांक (*is_locked)(काष्ठा spi_nor *nor, loff_t ofs, uपूर्णांक64_t len);
पूर्ण;

/**
 * काष्ठा spi_nor_otp_organization - Structure to describe the SPI NOR OTP regions
 * @len:	size of one OTP region in bytes.
 * @base:	start address of the OTP area.
 * @offset:	offset between consecutive OTP regions अगर there are more
 *              than one.
 * @n_regions:	number of inभागidual OTP regions.
 */
काष्ठा spi_nor_otp_organization अणु
	माप_प्रकार len;
	loff_t base;
	loff_t offset;
	अचिन्हित पूर्णांक n_regions;
पूर्ण;

/**
 * काष्ठा spi_nor_otp_ops - SPI NOR OTP methods
 * @पढ़ो:	पढ़ो from the SPI NOR OTP area.
 * @ग_लिखो:	ग_लिखो to the SPI NOR OTP area.
 * @lock:	lock an OTP region.
 * @is_locked:	check अगर an OTP region of the SPI NOR is locked.
 */
काष्ठा spi_nor_otp_ops अणु
	पूर्णांक (*पढ़ो)(काष्ठा spi_nor *nor, loff_t addr, माप_प्रकार len, u8 *buf);
	पूर्णांक (*ग_लिखो)(काष्ठा spi_nor *nor, loff_t addr, माप_प्रकार len,
		     स्थिर u8 *buf);
	पूर्णांक (*lock)(काष्ठा spi_nor *nor, अचिन्हित पूर्णांक region);
	पूर्णांक (*is_locked)(काष्ठा spi_nor *nor, अचिन्हित पूर्णांक region);
पूर्ण;

/**
 * काष्ठा spi_nor_otp - SPI NOR OTP grouping काष्ठाure
 * @org:	OTP region organization
 * @ops:	OTP access ops
 */
काष्ठा spi_nor_otp अणु
	स्थिर काष्ठा spi_nor_otp_organization *org;
	स्थिर काष्ठा spi_nor_otp_ops *ops;
पूर्ण;

/**
 * काष्ठा spi_nor_flash_parameter - SPI NOR flash parameters and settings.
 * Includes legacy flash parameters and settings that can be overwritten
 * by the spi_nor_fixups hooks, or dynamically when parsing the JESD216
 * Serial Flash Discoverable Parameters (SFDP) tables.
 *
 * @size:		the flash memory density in bytes.
 * @ग_लिखोsize		Minimal writable flash unit size. Defaults to 1. Set to
 *			ECC unit size क्रम ECC-ed flashes.
 * @page_size:		the page size of the SPI NOR flash memory.
 * @rdsr_dummy:		dummy cycles needed क्रम Read Status Register command.
 * @rdsr_addr_nbytes:	dummy address bytes needed क्रम Read Status Register
 *			command.
 * @hwcaps:		describes the पढ़ो and page program hardware
 *			capabilities.
 * @पढ़ोs:		पढ़ो capabilities ordered by priority: the higher index
 *                      in the array, the higher priority.
 * @page_programs:	page program capabilities ordered by priority: the
 *                      higher index in the array, the higher priority.
 * @erase_map:		the erase map parsed from the SFDP Sector Map Parameter
 *                      Table.
 * @otp_info:		describes the OTP regions.
 * @octal_dtr_enable:	enables SPI NOR octal DTR mode.
 * @quad_enable:	enables SPI NOR quad mode.
 * @set_4byte_addr_mode: माला_दो the SPI NOR in 4 byte addressing mode.
 * @convert_addr:	converts an असलolute address पूर्णांकo something the flash
 *                      will understand. Particularly useful when pagesize is
 *                      not a घातer-of-2.
 * @setup:              configures the SPI NOR memory. Useful क्रम SPI NOR
 *                      flashes that have peculiarities to the SPI NOR standard
 *                      e.g. dअगरferent opcodes, specअगरic address calculation,
 *                      page size, etc.
 * @locking_ops:	SPI NOR locking methods.
 * @otp:		SPI NOR OTP methods.
 */
काष्ठा spi_nor_flash_parameter अणु
	u64				size;
	u32				ग_लिखोsize;
	u32				page_size;
	u8				rdsr_dummy;
	u8				rdsr_addr_nbytes;

	काष्ठा spi_nor_hwcaps		hwcaps;
	काष्ठा spi_nor_पढ़ो_command	पढ़ोs[SNOR_CMD_READ_MAX];
	काष्ठा spi_nor_pp_command	page_programs[SNOR_CMD_PP_MAX];

	काष्ठा spi_nor_erase_map        erase_map;
	काष्ठा spi_nor_otp		otp;

	पूर्णांक (*octal_dtr_enable)(काष्ठा spi_nor *nor, bool enable);
	पूर्णांक (*quad_enable)(काष्ठा spi_nor *nor);
	पूर्णांक (*set_4byte_addr_mode)(काष्ठा spi_nor *nor, bool enable);
	u32 (*convert_addr)(काष्ठा spi_nor *nor, u32 addr);
	पूर्णांक (*setup)(काष्ठा spi_nor *nor, स्थिर काष्ठा spi_nor_hwcaps *hwcaps);

	स्थिर काष्ठा spi_nor_locking_ops *locking_ops;
पूर्ण;

/**
 * काष्ठा spi_nor_fixups - SPI NOR fixup hooks
 * @शेष_init: called after शेष flash parameters init. Used to tweak
 *                flash parameters when inक्रमmation provided by the flash_info
 *                table is incomplete or wrong.
 * @post_bfpt: called after the BFPT table has been parsed
 * @post_sfdp: called after SFDP has been parsed (is also called क्रम SPI NORs
 *             that करो not support RDSFDP). Typically used to tweak various
 *             parameters that could not be extracted by other means (i.e.
 *             when inक्रमmation provided by the SFDP/flash_info tables are
 *             incomplete or wrong).
 *
 * Those hooks can be used to tweak the SPI NOR configuration when the SFDP
 * table is broken or not available.
 */
काष्ठा spi_nor_fixups अणु
	व्योम (*शेष_init)(काष्ठा spi_nor *nor);
	पूर्णांक (*post_bfpt)(काष्ठा spi_nor *nor,
			 स्थिर काष्ठा sfdp_parameter_header *bfpt_header,
			 स्थिर काष्ठा sfdp_bfpt *bfpt);
	व्योम (*post_sfdp)(काष्ठा spi_nor *nor);
पूर्ण;

काष्ठा flash_info अणु
	अक्षर		*name;

	/*
	 * This array stores the ID bytes.
	 * The first three bytes are the JEDIC ID.
	 * JEDEC ID zero means "no ID" (mostly older chips).
	 */
	u8		id[SPI_NOR_MAX_ID_LEN];
	u8		id_len;

	/* The size listed here is what works with SPINOR_OP_SE, which isn't
	 * necessarily called a "sector" by the venकरोr.
	 */
	अचिन्हित	sector_size;
	u16		n_sectors;

	u16		page_size;
	u16		addr_width;

	u32		flags;
#घोषणा SECT_4K			BIT(0)	/* SPINOR_OP_BE_4K works unअगरormly */
#घोषणा SPI_NOR_NO_ERASE	BIT(1)	/* No erase command needed */
#घोषणा SST_WRITE		BIT(2)	/* use SST byte programming */
#घोषणा SPI_NOR_NO_FR		BIT(3)	/* Can't करो fastपढ़ो */
#घोषणा SECT_4K_PMC		BIT(4)	/* SPINOR_OP_BE_4K_PMC works unअगरormly */
#घोषणा SPI_NOR_DUAL_READ	BIT(5)	/* Flash supports Dual Read */
#घोषणा SPI_NOR_QUAD_READ	BIT(6)	/* Flash supports Quad Read */
#घोषणा USE_FSR			BIT(7)	/* use flag status रेजिस्टर */
#घोषणा SPI_NOR_HAS_LOCK	BIT(8)	/* Flash supports lock/unlock via SR */
#घोषणा SPI_NOR_HAS_TB		BIT(9)	/*
					 * Flash SR has Top/Bottom (TB) protect
					 * bit. Must be used with
					 * SPI_NOR_HAS_LOCK.
					 */
#घोषणा SPI_NOR_XSR_RDY		BIT(10)	/*
					 * S3AN flashes have specअगरic opcode to
					 * पढ़ो the status रेजिस्टर.
					 */
#घोषणा SPI_NOR_4B_OPCODES	BIT(11)	/*
					 * Use dedicated 4byte address op codes
					 * to support memory size above 128Mib.
					 */
#घोषणा NO_CHIP_ERASE		BIT(12) /* Chip करोes not support chip erase */
#घोषणा SPI_NOR_SKIP_SFDP	BIT(13)	/* Skip parsing of SFDP tables */
#घोषणा USE_CLSR		BIT(14)	/* use CLSR command */
#घोषणा SPI_NOR_OCTAL_READ	BIT(15)	/* Flash supports Octal Read */
#घोषणा SPI_NOR_TB_SR_BIT6	BIT(16)	/*
					 * Top/Bottom (TB) is bit 6 of
					 * status रेजिस्टर. Must be used with
					 * SPI_NOR_HAS_TB.
					 */
#घोषणा SPI_NOR_4BIT_BP		BIT(17) /*
					 * Flash SR has 4 bit fields (BP0-3)
					 * क्रम block protection.
					 */
#घोषणा SPI_NOR_BP3_SR_BIT6	BIT(18) /*
					 * BP3 is bit 6 of status रेजिस्टर.
					 * Must be used with SPI_NOR_4BIT_BP.
					 */
#घोषणा SPI_NOR_OCTAL_DTR_READ	BIT(19) /* Flash supports octal DTR Read. */
#घोषणा SPI_NOR_OCTAL_DTR_PP	BIT(20) /* Flash supports Octal DTR Page Program */
#घोषणा SPI_NOR_IO_MODE_EN_VOLATILE	BIT(21) /*
						 * Flash enables the best
						 * available I/O mode via a
						 * अस्थिर bit.
						 */
#घोषणा SPI_NOR_SWP_IS_VOLATILE	BIT(22)	/*
					 * Flash has अस्थिर software ग_लिखो
					 * protection bits. Usually these will
					 * घातer-up in a ग_लिखो-रक्षित state.
					 */

	स्थिर काष्ठा spi_nor_otp_organization otp_org;

	/* Part specअगरic fixup hooks. */
	स्थिर काष्ठा spi_nor_fixups *fixups;
पूर्ण;

/* Used when the "_ext_id" is two bytes at most */
#घोषणा INFO(_jedec_id, _ext_id, _sector_size, _n_sectors, _flags)	\
		.id = अणु							\
			((_jedec_id) >> 16) & 0xff,			\
			((_jedec_id) >> 8) & 0xff,			\
			(_jedec_id) & 0xff,				\
			((_ext_id) >> 8) & 0xff,			\
			(_ext_id) & 0xff,				\
			पूर्ण,						\
		.id_len = (!(_jedec_id) ? 0 : (3 + ((_ext_id) ? 2 : 0))),	\
		.sector_size = (_sector_size),				\
		.n_sectors = (_n_sectors),				\
		.page_size = 256,					\
		.flags = (_flags),

#घोषणा INFO6(_jedec_id, _ext_id, _sector_size, _n_sectors, _flags)	\
		.id = अणु							\
			((_jedec_id) >> 16) & 0xff,			\
			((_jedec_id) >> 8) & 0xff,			\
			(_jedec_id) & 0xff,				\
			((_ext_id) >> 16) & 0xff,			\
			((_ext_id) >> 8) & 0xff,			\
			(_ext_id) & 0xff,				\
			पूर्ण,						\
		.id_len = 6,						\
		.sector_size = (_sector_size),				\
		.n_sectors = (_n_sectors),				\
		.page_size = 256,					\
		.flags = (_flags),

#घोषणा CAT25_INFO(_sector_size, _n_sectors, _page_size, _addr_width, _flags)	\
		.sector_size = (_sector_size),				\
		.n_sectors = (_n_sectors),				\
		.page_size = (_page_size),				\
		.addr_width = (_addr_width),				\
		.flags = (_flags),

#घोषणा S3AN_INFO(_jedec_id, _n_sectors, _page_size)			\
		.id = अणु							\
			((_jedec_id) >> 16) & 0xff,			\
			((_jedec_id) >> 8) & 0xff,			\
			(_jedec_id) & 0xff				\
			पूर्ण,						\
		.id_len = 3,						\
		.sector_size = (8*_page_size),				\
		.n_sectors = (_n_sectors),				\
		.page_size = _page_size,				\
		.addr_width = 3,					\
		.flags = SPI_NOR_NO_FR | SPI_NOR_XSR_RDY,

#घोषणा OTP_INFO(_len, _n_regions, _base, _offset)			\
		.otp_org = अणु						\
			.len = (_len),					\
			.base = (_base),				\
			.offset = (_offset),				\
			.n_regions = (_n_regions),			\
		पूर्ण,

/**
 * काष्ठा spi_nor_manufacturer - SPI NOR manufacturer object
 * @name: manufacturer name
 * @parts: array of parts supported by this manufacturer
 * @nparts: number of entries in the parts array
 * @fixups: hooks called at various poपूर्णांकs in समय during spi_nor_scan()
 */
काष्ठा spi_nor_manufacturer अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा flash_info *parts;
	अचिन्हित पूर्णांक nparts;
	स्थिर काष्ठा spi_nor_fixups *fixups;
पूर्ण;

/* Manufacturer drivers. */
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_aपंचांगel;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_catalyst;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_eon;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_esmt;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_everspin;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_fujitsu;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_gigadevice;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_पूर्णांकel;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_issi;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_macronix;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_micron;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_st;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_spansion;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_sst;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_winbond;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_xilinx;
बाह्य स्थिर काष्ठा spi_nor_manufacturer spi_nor_xmc;

व्योम spi_nor_spimem_setup_op(स्थिर काष्ठा spi_nor *nor,
			     काष्ठा spi_mem_op *op,
			     स्थिर क्रमागत spi_nor_protocol proto);
पूर्णांक spi_nor_ग_लिखो_enable(काष्ठा spi_nor *nor);
पूर्णांक spi_nor_ग_लिखो_disable(काष्ठा spi_nor *nor);
पूर्णांक spi_nor_set_4byte_addr_mode(काष्ठा spi_nor *nor, bool enable);
पूर्णांक spi_nor_ग_लिखो_ear(काष्ठा spi_nor *nor, u8 ear);
पूर्णांक spi_nor_रुको_till_पढ़ोy(काष्ठा spi_nor *nor);
पूर्णांक spi_nor_global_block_unlock(काष्ठा spi_nor *nor);
पूर्णांक spi_nor_lock_and_prep(काष्ठा spi_nor *nor);
व्योम spi_nor_unlock_and_unprep(काष्ठा spi_nor *nor);
पूर्णांक spi_nor_sr1_bit6_quad_enable(काष्ठा spi_nor *nor);
पूर्णांक spi_nor_sr2_bit1_quad_enable(काष्ठा spi_nor *nor);
पूर्णांक spi_nor_sr2_bit7_quad_enable(काष्ठा spi_nor *nor);
पूर्णांक spi_nor_पढ़ो_sr(काष्ठा spi_nor *nor, u8 *sr);
पूर्णांक spi_nor_पढ़ो_cr(काष्ठा spi_nor *nor, u8 *cr);
पूर्णांक spi_nor_ग_लिखो_sr(काष्ठा spi_nor *nor, स्थिर u8 *sr, माप_प्रकार len);
पूर्णांक spi_nor_ग_लिखो_sr_and_check(काष्ठा spi_nor *nor, u8 sr1);
पूर्णांक spi_nor_ग_लिखो_16bit_cr_and_check(काष्ठा spi_nor *nor, u8 cr);

पूर्णांक spi_nor_xपढ़ो_sr(काष्ठा spi_nor *nor, u8 *sr);
sमाप_प्रकार spi_nor_पढ़ो_data(काष्ठा spi_nor *nor, loff_t from, माप_प्रकार len,
			  u8 *buf);
sमाप_प्रकार spi_nor_ग_लिखो_data(काष्ठा spi_nor *nor, loff_t to, माप_प्रकार len,
			   स्थिर u8 *buf);

पूर्णांक spi_nor_otp_पढ़ो_secr(काष्ठा spi_nor *nor, loff_t addr, माप_प्रकार len, u8 *buf);
पूर्णांक spi_nor_otp_ग_लिखो_secr(काष्ठा spi_nor *nor, loff_t addr, माप_प्रकार len,
			   स्थिर u8 *buf);
पूर्णांक spi_nor_otp_lock_sr2(काष्ठा spi_nor *nor, अचिन्हित पूर्णांक region);
पूर्णांक spi_nor_otp_is_locked_sr2(काष्ठा spi_nor *nor, अचिन्हित पूर्णांक region);

पूर्णांक spi_nor_hwcaps_पढ़ो2cmd(u32 hwcaps);
u8 spi_nor_convert_3to4_पढ़ो(u8 opcode);
व्योम spi_nor_set_पढ़ो_settings(काष्ठा spi_nor_पढ़ो_command *पढ़ो,
			       u8 num_mode_घड़ीs,
			       u8 num_रुको_states,
			       u8 opcode,
			       क्रमागत spi_nor_protocol proto);
व्योम spi_nor_set_pp_settings(काष्ठा spi_nor_pp_command *pp, u8 opcode,
			     क्रमागत spi_nor_protocol proto);

व्योम spi_nor_set_erase_type(काष्ठा spi_nor_erase_type *erase, u32 size,
			    u8 opcode);
काष्ठा spi_nor_erase_region *
spi_nor_region_next(काष्ठा spi_nor_erase_region *region);
व्योम spi_nor_init_unअगरorm_erase_map(काष्ठा spi_nor_erase_map *map,
				    u8 erase_mask, u64 flash_size);

पूर्णांक spi_nor_post_bfpt_fixups(काष्ठा spi_nor *nor,
			     स्थिर काष्ठा sfdp_parameter_header *bfpt_header,
			     स्थिर काष्ठा sfdp_bfpt *bfpt);

व्योम spi_nor_init_शेष_locking_ops(काष्ठा spi_nor *nor);
व्योम spi_nor_try_unlock_all(काष्ठा spi_nor *nor);
व्योम spi_nor_रेजिस्टर_locking_ops(काष्ठा spi_nor *nor);
व्योम spi_nor_otp_init(काष्ठा spi_nor *nor);

अटल काष्ठा spi_nor __maybe_unused *mtd_to_spi_nor(काष्ठा mtd_info *mtd)
अणु
	वापस mtd->priv;
पूर्ण

#पूर्ण_अगर /* __LINUX_MTD_SPI_NOR_INTERNAL_H */
