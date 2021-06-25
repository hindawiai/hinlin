<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016-2017 Micron Technology, Inc.
 *
 *  Authors:
 *	Peter Pan <peterpanकरोng@micron.com>
 */
#अगर_अघोषित __LINUX_MTD_SPIन_अंकD_H
#घोषणा __LINUX_MTD_SPIन_अंकD_H

#समावेश <linux/mutex.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

/**
 * Standard SPI न_अंकD flash operations
 */

#घोषणा SPIन_अंकD_RESET_OP						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xff, 1),				\
		   SPI_MEM_OP_NO_ADDR,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#घोषणा SPIन_अंकD_WR_EN_DIS_OP(enable)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD((enable) ? 0x06 : 0x04, 1),		\
		   SPI_MEM_OP_NO_ADDR,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#घोषणा SPIन_अंकD_READID_OP(naddr, ndummy, buf, len)			\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x9f, 1),				\
		   SPI_MEM_OP_ADDR(naddr, 0, 1),			\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 1))

#घोषणा SPIन_अंकD_SET_FEATURE_OP(reg, valptr)				\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x1f, 1),				\
		   SPI_MEM_OP_ADDR(1, reg, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(1, valptr, 1))

#घोषणा SPIन_अंकD_GET_FEATURE_OP(reg, valptr)				\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x0f, 1),				\
		   SPI_MEM_OP_ADDR(1, reg, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_IN(1, valptr, 1))

#घोषणा SPIन_अंकD_BLK_ERASE_OP(addr)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xd8, 1),				\
		   SPI_MEM_OP_ADDR(3, addr, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#घोषणा SPIन_अंकD_PAGE_READ_OP(addr)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x13, 1),				\
		   SPI_MEM_OP_ADDR(3, addr, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(fast, addr, ndummy, buf, len)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(fast ? 0x0b : 0x03, 1),		\
		   SPI_MEM_OP_ADDR(2, addr, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 1))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_OP_3A(fast, addr, ndummy, buf, len) \
	SPI_MEM_OP(SPI_MEM_OP_CMD(fast ? 0x0b : 0x03, 1),		\
		   SPI_MEM_OP_ADDR(3, addr, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 1))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP(addr, ndummy, buf, len)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x3b, 1),				\
		   SPI_MEM_OP_ADDR(2, addr, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 2))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP_3A(addr, ndummy, buf, len)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x3b, 1),				\
		   SPI_MEM_OP_ADDR(3, addr, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 2))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP(addr, ndummy, buf, len)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x6b, 1),				\
		   SPI_MEM_OP_ADDR(2, addr, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 4))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP_3A(addr, ndummy, buf, len)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x6b, 1),				\
		   SPI_MEM_OP_ADDR(3, addr, 1),				\
		   SPI_MEM_OP_DUMMY(ndummy, 1),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 4))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_DUALIO_OP(addr, ndummy, buf, len)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xbb, 1),				\
		   SPI_MEM_OP_ADDR(2, addr, 2),				\
		   SPI_MEM_OP_DUMMY(ndummy, 2),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 2))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_DUALIO_OP_3A(addr, ndummy, buf, len) \
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xbb, 1),				\
		   SPI_MEM_OP_ADDR(3, addr, 2),				\
		   SPI_MEM_OP_DUMMY(ndummy, 2),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 2))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_QUADIO_OP(addr, ndummy, buf, len)	\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xeb, 1),				\
		   SPI_MEM_OP_ADDR(2, addr, 4),				\
		   SPI_MEM_OP_DUMMY(ndummy, 4),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 4))

#घोषणा SPIन_अंकD_PAGE_READ_FROM_CACHE_QUADIO_OP_3A(addr, ndummy, buf, len) \
	SPI_MEM_OP(SPI_MEM_OP_CMD(0xeb, 1),				\
		   SPI_MEM_OP_ADDR(3, addr, 4),				\
		   SPI_MEM_OP_DUMMY(ndummy, 4),				\
		   SPI_MEM_OP_DATA_IN(len, buf, 4))

#घोषणा SPIन_अंकD_PROG_EXEC_OP(addr)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(0x10, 1),				\
		   SPI_MEM_OP_ADDR(3, addr, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#घोषणा SPIन_अंकD_PROG_LOAD(reset, addr, buf, len)			\
	SPI_MEM_OP(SPI_MEM_OP_CMD(reset ? 0x02 : 0x84, 1),		\
		   SPI_MEM_OP_ADDR(2, addr, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(len, buf, 1))

#घोषणा SPIन_अंकD_PROG_LOAD_X4(reset, addr, buf, len)			\
	SPI_MEM_OP(SPI_MEM_OP_CMD(reset ? 0x32 : 0x34, 1),		\
		   SPI_MEM_OP_ADDR(2, addr, 1),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(len, buf, 4))

/**
 * Standard SPI न_अंकD flash commands
 */
#घोषणा SPIन_अंकD_CMD_PROG_LOAD_X4		0x32
#घोषणा SPIन_अंकD_CMD_PROG_LOAD_RDM_DATA_X4	0x34

/* feature रेजिस्टर */
#घोषणा REG_BLOCK_LOCK		0xa0
#घोषणा BL_ALL_UNLOCKED		0x00

/* configuration रेजिस्टर */
#घोषणा REG_CFG			0xb0
#घोषणा CFG_OTP_ENABLE		BIT(6)
#घोषणा CFG_ECC_ENABLE		BIT(4)
#घोषणा CFG_QUAD_ENABLE		BIT(0)

/* status रेजिस्टर */
#घोषणा REG_STATUS		0xc0
#घोषणा STATUS_BUSY		BIT(0)
#घोषणा STATUS_ERASE_FAILED	BIT(2)
#घोषणा STATUS_PROG_FAILED	BIT(3)
#घोषणा STATUS_ECC_MASK		GENMASK(5, 4)
#घोषणा STATUS_ECC_NO_BITFLIPS	(0 << 4)
#घोषणा STATUS_ECC_HAS_BITFLIPS	(1 << 4)
#घोषणा STATUS_ECC_UNCOR_ERROR	(2 << 4)

काष्ठा spinand_op;
काष्ठा spinand_device;

#घोषणा SPIन_अंकD_MAX_ID_LEN	4

/**
 * काष्ठा spinand_id - SPI न_अंकD id काष्ठाure
 * @data: buffer containing the id bytes. Currently 4 bytes large, but can
 *	  be extended अगर required
 * @len: ID length
 */
काष्ठा spinand_id अणु
	u8 data[SPIन_अंकD_MAX_ID_LEN];
	पूर्णांक len;
पूर्ण;

क्रमागत spinand_पढ़ोid_method अणु
	SPIन_अंकD_READID_METHOD_OPCODE,
	SPIन_अंकD_READID_METHOD_OPCODE_ADDR,
	SPIन_अंकD_READID_METHOD_OPCODE_DUMMY,
पूर्ण;

/**
 * काष्ठा spinand_devid - SPI न_अंकD device id काष्ठाure
 * @id: device id of current chip
 * @len: number of bytes in device id
 * @method: method to पढ़ो chip id
 *	    There are 3 possible variants:
 *	    SPIन_अंकD_READID_METHOD_OPCODE: chip id is वापसed immediately
 *	    after पढ़ो_id opcode.
 *	    SPIन_अंकD_READID_METHOD_OPCODE_ADDR: chip id is वापसed after
 *	    पढ़ो_id opcode + 1-byte address.
 *	    SPIन_अंकD_READID_METHOD_OPCODE_DUMMY: chip id is वापसed after
 *	    पढ़ो_id opcode + 1 dummy byte.
 */
काष्ठा spinand_devid अणु
	स्थिर u8 *id;
	स्थिर u8 len;
	स्थिर क्रमागत spinand_पढ़ोid_method method;
पूर्ण;

/**
 * काष्ठा manufacurer_ops - SPI न_अंकD manufacturer specअगरic operations
 * @init: initialize a SPI न_अंकD device
 * @cleanup: cleanup a SPI न_अंकD device
 *
 * Each SPI न_अंकD manufacturer driver should implement this पूर्णांकerface so that
 * न_अंकD chips coming from this venकरोr can be initialized properly.
 */
काष्ठा spinand_manufacturer_ops अणु
	पूर्णांक (*init)(काष्ठा spinand_device *spinand);
	व्योम (*cleanup)(काष्ठा spinand_device *spinand);
पूर्ण;

/**
 * काष्ठा spinand_manufacturer - SPI न_अंकD manufacturer instance
 * @id: manufacturer ID
 * @name: manufacturer name
 * @devid_len: number of bytes in device ID
 * @chips: supported SPI न_अंकDs under current manufacturer
 * @nchips: number of SPI न_अंकDs available in chips array
 * @ops: manufacturer operations
 */
काष्ठा spinand_manufacturer अणु
	u8 id;
	अक्षर *name;
	स्थिर काष्ठा spinand_info *chips;
	स्थिर माप_प्रकार nchips;
	स्थिर काष्ठा spinand_manufacturer_ops *ops;
पूर्ण;

/* SPI न_अंकD manufacturers */
बाह्य स्थिर काष्ठा spinand_manufacturer gigadevice_spinand_manufacturer;
बाह्य स्थिर काष्ठा spinand_manufacturer macronix_spinand_manufacturer;
बाह्य स्थिर काष्ठा spinand_manufacturer micron_spinand_manufacturer;
बाह्य स्थिर काष्ठा spinand_manufacturer paragon_spinand_manufacturer;
बाह्य स्थिर काष्ठा spinand_manufacturer toshiba_spinand_manufacturer;
बाह्य स्थिर काष्ठा spinand_manufacturer winbond_spinand_manufacturer;

/**
 * काष्ठा spinand_op_variants - SPI न_अंकD operation variants
 * @ops: the list of variants क्रम a given operation
 * @nops: the number of variants
 *
 * Some operations like पढ़ो-from-cache/ग_लिखो-to-cache have several variants
 * depending on the number of IO lines you use to transfer data or address
 * cycles. This काष्ठाure is a way to describe the dअगरferent variants supported
 * by a chip and let the core pick the best one based on the SPI mem controller
 * capabilities.
 */
काष्ठा spinand_op_variants अणु
	स्थिर काष्ठा spi_mem_op *ops;
	अचिन्हित पूर्णांक nops;
पूर्ण;

#घोषणा SPIन_अंकD_OP_VARIANTS(name, ...)					\
	स्थिर काष्ठा spinand_op_variants name = अणु			\
		.ops = (काष्ठा spi_mem_op[]) अणु __VA_ARGS__ पूर्ण,		\
		.nops = माप((काष्ठा spi_mem_op[])अणु __VA_ARGS__ पूर्ण) /	\
			माप(काष्ठा spi_mem_op),			\
	पूर्ण

/**
 * spinand_ecc_info - description of the on-die ECC implemented by a SPI न_अंकD
 *		      chip
 * @get_status: get the ECC status. Should वापस a positive number encoding
 *		the number of corrected bitflips अगर correction was possible or
 *		-EBADMSG अगर there are uncorrectable errors. I can also वापस
 *		other negative error codes अगर the error is not caused by
 *		uncorrectable bitflips
 * @ooblayout: the OOB layout used by the on-die ECC implementation
 */
काष्ठा spinand_ecc_info अणु
	पूर्णांक (*get_status)(काष्ठा spinand_device *spinand, u8 status);
	स्थिर काष्ठा mtd_ooblayout_ops *ooblayout;
पूर्ण;

#घोषणा SPIन_अंकD_HAS_QE_BIT		BIT(0)
#घोषणा SPIन_अंकD_HAS_CR_FEAT_BIT		BIT(1)

/**
 * काष्ठा spinand_ondie_ecc_conf - निजी SPI-न_अंकD on-die ECC engine काष्ठाure
 * @status: status of the last रुको operation that will be used in हाल
 *          ->get_status() is not populated by the spinand device.
 */
काष्ठा spinand_ondie_ecc_conf अणु
	u8 status;
पूर्ण;

/**
 * काष्ठा spinand_info - Structure used to describe SPI न_अंकD chips
 * @model: model name
 * @devid: device ID
 * @flags: OR-ing of the SPIन_अंकD_XXX flags
 * @memorg: memory organization
 * @eccreq: ECC requirements
 * @eccinfo: on-die ECC info
 * @op_variants: operations variants
 * @op_variants.पढ़ो_cache: variants of the पढ़ो-cache operation
 * @op_variants.ग_लिखो_cache: variants of the ग_लिखो-cache operation
 * @op_variants.update_cache: variants of the update-cache operation
 * @select_target: function used to select a target/die. Required only क्रम
 *		   multi-die chips
 *
 * Each SPI न_अंकD manufacturer driver should have a spinand_info table
 * describing all the chips supported by the driver.
 */
काष्ठा spinand_info अणु
	स्थिर अक्षर *model;
	काष्ठा spinand_devid devid;
	u32 flags;
	काष्ठा nand_memory_organization memorg;
	काष्ठा nand_ecc_props eccreq;
	काष्ठा spinand_ecc_info eccinfo;
	काष्ठा अणु
		स्थिर काष्ठा spinand_op_variants *पढ़ो_cache;
		स्थिर काष्ठा spinand_op_variants *ग_लिखो_cache;
		स्थिर काष्ठा spinand_op_variants *update_cache;
	पूर्ण op_variants;
	पूर्णांक (*select_target)(काष्ठा spinand_device *spinand,
			     अचिन्हित पूर्णांक target);
पूर्ण;

#घोषणा SPIन_अंकD_ID(__method, ...)					\
	अणु								\
		.id = (स्थिर u8[])अणु __VA_ARGS__ पूर्ण,			\
		.len = माप((u8[])अणु __VA_ARGS__ पूर्ण),			\
		.method = __method,					\
	पूर्ण

#घोषणा SPIन_अंकD_INFO_OP_VARIANTS(__पढ़ो, __ग_लिखो, __update)		\
	अणु								\
		.पढ़ो_cache = __पढ़ो,					\
		.ग_लिखो_cache = __ग_लिखो,					\
		.update_cache = __update,				\
	पूर्ण

#घोषणा SPIन_अंकD_ECCINFO(__ooblayout, __get_status)			\
	.eccinfo = अणु							\
		.ooblayout = __ooblayout,				\
		.get_status = __get_status,				\
	पूर्ण

#घोषणा SPIन_अंकD_SELECT_TARGET(__func)					\
	.select_target = __func,

#घोषणा SPIन_अंकD_INFO(__model, __id, __memorg, __eccreq, __op_variants,	\
		     __flags, ...)					\
	अणु								\
		.model = __model,					\
		.devid = __id,						\
		.memorg = __memorg,					\
		.eccreq = __eccreq,					\
		.op_variants = __op_variants,				\
		.flags = __flags,					\
		__VA_ARGS__						\
	पूर्ण

काष्ठा spinand_dirmap अणु
	काष्ठा spi_mem_dirmap_desc *wdesc;
	काष्ठा spi_mem_dirmap_desc *rdesc;
पूर्ण;

/**
 * काष्ठा spinand_device - SPI न_अंकD device instance
 * @base: न_अंकD device instance
 * @spimem: poपूर्णांकer to the SPI mem object
 * @lock: lock used to serialize accesses to the न_अंकD
 * @id: न_अंकD ID as वापसed by READ_ID
 * @flags: न_अंकD flags
 * @op_ढाँचाs: various SPI mem op ढाँचाs
 * @op_ढाँचाs.पढ़ो_cache: पढ़ो cache op ढाँचा
 * @op_ढाँचाs.ग_लिखो_cache: ग_लिखो cache op ढाँचा
 * @op_ढाँचाs.update_cache: update cache op ढाँचा
 * @select_target: select a specअगरic target/die. Usually called beक्रमe sending
 *		   a command addressing a page or an eraseblock embedded in
 *		   this die. Only required अगर your chip exposes several dies
 * @cur_target: currently selected target/die
 * @eccinfo: on-die ECC inक्रमmation
 * @cfg_cache: config रेजिस्टर cache. One entry per die
 * @databuf: bounce buffer क्रम data
 * @oobbuf: bounce buffer क्रम OOB data
 * @scratchbuf: buffer used क्रम everything but page accesses. This is needed
 *		because the spi-mem पूर्णांकerface explicitly requests that buffers
 *		passed in spi_mem_op be DMA-able, so we can't based the bufs on
 *		the stack
 * @manufacturer: SPI न_अंकD manufacturer inक्रमmation
 * @priv: manufacturer निजी data
 */
काष्ठा spinand_device अणु
	काष्ठा nand_device base;
	काष्ठा spi_mem *spimem;
	काष्ठा mutex lock;
	काष्ठा spinand_id id;
	u32 flags;

	काष्ठा अणु
		स्थिर काष्ठा spi_mem_op *पढ़ो_cache;
		स्थिर काष्ठा spi_mem_op *ग_लिखो_cache;
		स्थिर काष्ठा spi_mem_op *update_cache;
	पूर्ण op_ढाँचाs;

	काष्ठा spinand_dirmap *dirmaps;

	पूर्णांक (*select_target)(काष्ठा spinand_device *spinand,
			     अचिन्हित पूर्णांक target);
	अचिन्हित पूर्णांक cur_target;

	काष्ठा spinand_ecc_info eccinfo;

	u8 *cfg_cache;
	u8 *databuf;
	u8 *oobbuf;
	u8 *scratchbuf;
	स्थिर काष्ठा spinand_manufacturer *manufacturer;
	व्योम *priv;
पूर्ण;

/**
 * mtd_to_spinand() - Get the SPI न_अंकD device attached to an MTD instance
 * @mtd: MTD instance
 *
 * Return: the SPI न_अंकD device attached to @mtd.
 */
अटल अंतरभूत काष्ठा spinand_device *mtd_to_spinand(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd_to_nanddev(mtd), काष्ठा spinand_device, base);
पूर्ण

/**
 * spinand_to_mtd() - Get the MTD device embedded in a SPI न_अंकD device
 * @spinand: SPI न_अंकD device
 *
 * Return: the MTD device embedded in @spinand.
 */
अटल अंतरभूत काष्ठा mtd_info *spinand_to_mtd(काष्ठा spinand_device *spinand)
अणु
	वापस nanddev_to_mtd(&spinand->base);
पूर्ण

/**
 * nand_to_spinand() - Get the SPI न_अंकD device embedding an न_अंकD object
 * @nand: न_अंकD object
 *
 * Return: the SPI न_अंकD device embedding @nand.
 */
अटल अंतरभूत काष्ठा spinand_device *nand_to_spinand(काष्ठा nand_device *nand)
अणु
	वापस container_of(nand, काष्ठा spinand_device, base);
पूर्ण

/**
 * spinand_to_nand() - Get the न_अंकD device embedded in a SPI न_अंकD object
 * @spinand: SPI न_अंकD device
 *
 * Return: the न_अंकD device embedded in @spinand.
 */
अटल अंतरभूत काष्ठा nand_device *
spinand_to_nand(काष्ठा spinand_device *spinand)
अणु
	वापस &spinand->base;
पूर्ण

/**
 * spinand_set_of_node - Attach a DT node to a SPI न_अंकD device
 * @spinand: SPI न_अंकD device
 * @np: DT node
 *
 * Attach a DT node to a SPI न_अंकD device.
 */
अटल अंतरभूत व्योम spinand_set_of_node(काष्ठा spinand_device *spinand,
				       काष्ठा device_node *np)
अणु
	nanddev_set_of_node(&spinand->base, np);
पूर्ण

पूर्णांक spinand_match_and_init(काष्ठा spinand_device *spinand,
			   स्थिर काष्ठा spinand_info *table,
			   अचिन्हित पूर्णांक table_size,
			   क्रमागत spinand_पढ़ोid_method rdid_method);

पूर्णांक spinand_upd_cfg(काष्ठा spinand_device *spinand, u8 mask, u8 val);
पूर्णांक spinand_select_target(काष्ठा spinand_device *spinand, अचिन्हित पूर्णांक target);

#पूर्ण_अगर /* __LINUX_MTD_SPIन_अंकD_H */
