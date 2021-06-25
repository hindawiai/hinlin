<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Nuvoton Technology corporation.

#समावेश <linux/bits.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi-स्मृति.स>
#समावेश <linux/mfd/syscon.h>

/* NPCM7xx GCR module */
#घोषणा NPCM7XX_INTCR3_OFFSET		0x9C
#घोषणा NPCM7XX_INTCR3_FIU_FIX		BIT(6)

/* Flash Interface Unit (FIU) Registers */
#घोषणा NPCM_FIU_DRD_CFG		0x00
#घोषणा NPCM_FIU_DWR_CFG		0x04
#घोषणा NPCM_FIU_UMA_CFG		0x08
#घोषणा NPCM_FIU_UMA_CTS		0x0C
#घोषणा NPCM_FIU_UMA_CMD		0x10
#घोषणा NPCM_FIU_UMA_ADDR		0x14
#घोषणा NPCM_FIU_PRT_CFG		0x18
#घोषणा NPCM_FIU_UMA_DW0		0x20
#घोषणा NPCM_FIU_UMA_DW1		0x24
#घोषणा NPCM_FIU_UMA_DW2		0x28
#घोषणा NPCM_FIU_UMA_DW3		0x2C
#घोषणा NPCM_FIU_UMA_DR0		0x30
#घोषणा NPCM_FIU_UMA_DR1		0x34
#घोषणा NPCM_FIU_UMA_DR2		0x38
#घोषणा NPCM_FIU_UMA_DR3		0x3C
#घोषणा NPCM_FIU_MAX_REG_LIMIT		0x80

/* FIU Direct Read Configuration Register */
#घोषणा NPCM_FIU_DRD_CFG_LCK		BIT(31)
#घोषणा NPCM_FIU_DRD_CFG_R_BURST	GENMASK(25, 24)
#घोषणा NPCM_FIU_DRD_CFG_ADDSIZ		GENMASK(17, 16)
#घोषणा NPCM_FIU_DRD_CFG_DBW		GENMASK(13, 12)
#घोषणा NPCM_FIU_DRD_CFG_ACCTYPE	GENMASK(9, 8)
#घोषणा NPCM_FIU_DRD_CFG_RDCMD		GENMASK(7, 0)
#घोषणा NPCM_FIU_DRD_ADDSIZ_SHIFT	16
#घोषणा NPCM_FIU_DRD_DBW_SHIFT		12
#घोषणा NPCM_FIU_DRD_ACCTYPE_SHIFT	8

/* FIU Direct Write Configuration Register */
#घोषणा NPCM_FIU_DWR_CFG_LCK		BIT(31)
#घोषणा NPCM_FIU_DWR_CFG_W_BURST	GENMASK(25, 24)
#घोषणा NPCM_FIU_DWR_CFG_ADDSIZ		GENMASK(17, 16)
#घोषणा NPCM_FIU_DWR_CFG_ABPCK		GENMASK(11, 10)
#घोषणा NPCM_FIU_DWR_CFG_DBPCK		GENMASK(9, 8)
#घोषणा NPCM_FIU_DWR_CFG_WRCMD		GENMASK(7, 0)
#घोषणा NPCM_FIU_DWR_ADDSIZ_SHIFT	16
#घोषणा NPCM_FIU_DWR_ABPCK_SHIFT	10
#घोषणा NPCM_FIU_DWR_DBPCK_SHIFT	8

/* FIU UMA Configuration Register */
#घोषणा NPCM_FIU_UMA_CFG_LCK		BIT(31)
#घोषणा NPCM_FIU_UMA_CFG_CMMLCK		BIT(30)
#घोषणा NPCM_FIU_UMA_CFG_RDATSIZ	GENMASK(28, 24)
#घोषणा NPCM_FIU_UMA_CFG_DBSIZ		GENMASK(23, 21)
#घोषणा NPCM_FIU_UMA_CFG_WDATSIZ	GENMASK(20, 16)
#घोषणा NPCM_FIU_UMA_CFG_ADDSIZ		GENMASK(13, 11)
#घोषणा NPCM_FIU_UMA_CFG_CMDSIZ		BIT(10)
#घोषणा NPCM_FIU_UMA_CFG_RDBPCK		GENMASK(9, 8)
#घोषणा NPCM_FIU_UMA_CFG_DBPCK		GENMASK(7, 6)
#घोषणा NPCM_FIU_UMA_CFG_WDBPCK		GENMASK(5, 4)
#घोषणा NPCM_FIU_UMA_CFG_ADBPCK		GENMASK(3, 2)
#घोषणा NPCM_FIU_UMA_CFG_CMBPCK		GENMASK(1, 0)
#घोषणा NPCM_FIU_UMA_CFG_ADBPCK_SHIFT	2
#घोषणा NPCM_FIU_UMA_CFG_WDBPCK_SHIFT	4
#घोषणा NPCM_FIU_UMA_CFG_DBPCK_SHIFT	6
#घोषणा NPCM_FIU_UMA_CFG_RDBPCK_SHIFT	8
#घोषणा NPCM_FIU_UMA_CFG_ADDSIZ_SHIFT	11
#घोषणा NPCM_FIU_UMA_CFG_WDATSIZ_SHIFT	16
#घोषणा NPCM_FIU_UMA_CFG_DBSIZ_SHIFT	21
#घोषणा NPCM_FIU_UMA_CFG_RDATSIZ_SHIFT	24

/* FIU UMA Control and Status Register */
#घोषणा NPCM_FIU_UMA_CTS_RDYIE		BIT(25)
#घोषणा NPCM_FIU_UMA_CTS_RDYST		BIT(24)
#घोषणा NPCM_FIU_UMA_CTS_SW_CS		BIT(16)
#घोषणा NPCM_FIU_UMA_CTS_DEV_NUM	GENMASK(9, 8)
#घोषणा NPCM_FIU_UMA_CTS_EXEC_DONE	BIT(0)
#घोषणा NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT	8

/* FIU UMA Command Register */
#घोषणा NPCM_FIU_UMA_CMD_DUM3		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_CMD_DUM2		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_CMD_DUM1		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_CMD_CMD		GENMASK(7, 0)

/* FIU UMA Address Register */
#घोषणा NPCM_FIU_UMA_ADDR_UMA_ADDR	GENMASK(31, 0)
#घोषणा NPCM_FIU_UMA_ADDR_AB3		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_ADDR_AB2		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_ADDR_AB1		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_ADDR_AB0		GENMASK(7, 0)

/* FIU UMA Write Data Bytes 0-3 Register */
#घोषणा NPCM_FIU_UMA_DW0_WB3		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_DW0_WB2		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_DW0_WB1		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_DW0_WB0		GENMASK(7, 0)

/* FIU UMA Write Data Bytes 4-7 Register */
#घोषणा NPCM_FIU_UMA_DW1_WB7		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_DW1_WB6		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_DW1_WB5		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_DW1_WB4		GENMASK(7, 0)

/* FIU UMA Write Data Bytes 8-11 Register */
#घोषणा NPCM_FIU_UMA_DW2_WB11		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_DW2_WB10		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_DW2_WB9		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_DW2_WB8		GENMASK(7, 0)

/* FIU UMA Write Data Bytes 12-15 Register */
#घोषणा NPCM_FIU_UMA_DW3_WB15		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_DW3_WB14		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_DW3_WB13		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_DW3_WB12		GENMASK(7, 0)

/* FIU UMA Read Data Bytes 0-3 Register */
#घोषणा NPCM_FIU_UMA_DR0_RB3		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_DR0_RB2		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_DR0_RB1		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_DR0_RB0		GENMASK(7, 0)

/* FIU UMA Read Data Bytes 4-7 Register */
#घोषणा NPCM_FIU_UMA_DR1_RB15		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_DR1_RB14		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_DR1_RB13		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_DR1_RB12		GENMASK(7, 0)

/* FIU UMA Read Data Bytes 8-11 Register */
#घोषणा NPCM_FIU_UMA_DR2_RB15		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_DR2_RB14		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_DR2_RB13		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_DR2_RB12		GENMASK(7, 0)

/* FIU UMA Read Data Bytes 12-15 Register */
#घोषणा NPCM_FIU_UMA_DR3_RB15		GENMASK(31, 24)
#घोषणा NPCM_FIU_UMA_DR3_RB14		GENMASK(23, 16)
#घोषणा NPCM_FIU_UMA_DR3_RB13		GENMASK(15, 8)
#घोषणा NPCM_FIU_UMA_DR3_RB12		GENMASK(7, 0)

/* FIU Read Mode */
क्रमागत अणु
	DRD_SINGLE_WIRE_MODE	= 0,
	DRD_DUAL_IO_MODE	= 1,
	DRD_QUAD_IO_MODE	= 2,
	DRD_SPI_X_MODE		= 3,
पूर्ण;

क्रमागत अणु
	DWR_ABPCK_BIT_PER_CLK	= 0,
	DWR_ABPCK_2_BIT_PER_CLK	= 1,
	DWR_ABPCK_4_BIT_PER_CLK	= 2,
पूर्ण;

क्रमागत अणु
	DWR_DBPCK_BIT_PER_CLK	= 0,
	DWR_DBPCK_2_BIT_PER_CLK	= 1,
	DWR_DBPCK_4_BIT_PER_CLK	= 2,
पूर्ण;

#घोषणा NPCM_FIU_DRD_16_BYTE_BURST	0x3000000
#घोषणा NPCM_FIU_DWR_16_BYTE_BURST	0x3000000

#घोषणा MAP_SIZE_128MB			0x8000000
#घोषणा MAP_SIZE_16MB			0x1000000
#घोषणा MAP_SIZE_8MB			0x800000

#घोषणा FIU_DRD_MAX_DUMMY_NUMBER	3
#घोषणा NPCM_MAX_CHIP_NUM		4
#घोषणा CHUNK_SIZE			16
#घोषणा UMA_MICRO_SEC_TIMEOUT		150

क्रमागत अणु
	FIU0 = 0,
	FIU3,
	FIUX,
पूर्ण;

काष्ठा npcm_fiu_info अणु
	अक्षर *name;
	u32 fiu_id;
	u32 max_map_size;
	u32 max_cs;
पूर्ण;

काष्ठा fiu_data अणु
	स्थिर काष्ठा npcm_fiu_info *npcm_fiu_data_info;
	पूर्णांक fiu_max;
पूर्ण;

अटल स्थिर काष्ठा npcm_fiu_info npxm7xx_fiu_info[] = अणु
	अणु.name = "FIU0", .fiu_id = FIU0,
		.max_map_size = MAP_SIZE_128MB, .max_cs = 2पूर्ण,
	अणु.name = "FIU3", .fiu_id = FIU3,
		.max_map_size = MAP_SIZE_128MB, .max_cs = 4पूर्ण,
	अणु.name = "FIUX", .fiu_id = FIUX,
		.max_map_size = MAP_SIZE_16MB, .max_cs = 2पूर्ण पूर्ण;

अटल स्थिर काष्ठा fiu_data npxm7xx_fiu_data = अणु
	.npcm_fiu_data_info = npxm7xx_fiu_info,
	.fiu_max = 3,
पूर्ण;

काष्ठा npcm_fiu_spi;

काष्ठा npcm_fiu_chip अणु
	व्योम __iomem *flash_region_mapped_ptr;
	काष्ठा npcm_fiu_spi *fiu;
	अचिन्हित दीर्घ clkrate;
	u32 chipselect;
पूर्ण;

काष्ठा npcm_fiu_spi अणु
	काष्ठा npcm_fiu_chip chip[NPCM_MAX_CHIP_NUM];
	स्थिर काष्ठा npcm_fiu_info *info;
	काष्ठा spi_mem_op drd_op;
	काष्ठा resource *res_mem;
	काष्ठा regmap *regmap;
	अचिन्हित दीर्घ clkrate;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	bool spix_mode;
पूर्ण;

अटल स्थिर काष्ठा regmap_config npcm_mtd_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = NPCM_FIU_MAX_REG_LIMIT,
पूर्ण;

अटल व्योम npcm_fiu_set_drd(काष्ठा npcm_fiu_spi *fiu,
			     स्थिर काष्ठा spi_mem_op *op)
अणु
	regmap_update_bits(fiu->regmap, NPCM_FIU_DRD_CFG,
			   NPCM_FIU_DRD_CFG_ACCTYPE,
			   ilog2(op->addr.buswidth) <<
			   NPCM_FIU_DRD_ACCTYPE_SHIFT);
	fiu->drd_op.addr.buswidth = op->addr.buswidth;
	regmap_update_bits(fiu->regmap, NPCM_FIU_DRD_CFG,
			   NPCM_FIU_DRD_CFG_DBW,
			   ((op->dummy.nbytes * ilog2(op->addr.buswidth)) / BITS_PER_BYTE)
			   << NPCM_FIU_DRD_DBW_SHIFT);
	fiu->drd_op.dummy.nbytes = op->dummy.nbytes;
	regmap_update_bits(fiu->regmap, NPCM_FIU_DRD_CFG,
			   NPCM_FIU_DRD_CFG_RDCMD, op->cmd.opcode);
	fiu->drd_op.cmd.opcode = op->cmd.opcode;
	regmap_update_bits(fiu->regmap, NPCM_FIU_DRD_CFG,
			   NPCM_FIU_DRD_CFG_ADDSIZ,
			   (op->addr.nbytes - 3) << NPCM_FIU_DRD_ADDSIZ_SHIFT);
	fiu->drd_op.addr.nbytes = op->addr.nbytes;
पूर्ण

अटल sमाप_प्रकार npcm_fiu_direct_पढ़ो(काष्ठा spi_mem_dirmap_desc *desc,
				    u64 offs, माप_प्रकार len, व्योम *buf)
अणु
	काष्ठा npcm_fiu_spi *fiu =
		spi_controller_get_devdata(desc->mem->spi->master);
	काष्ठा npcm_fiu_chip *chip = &fiu->chip[desc->mem->spi->chip_select];
	व्योम __iomem *src = (व्योम __iomem *)(chip->flash_region_mapped_ptr +
					     offs);
	u8 *buf_rx = buf;
	u32 i;

	अगर (fiu->spix_mode) अणु
		क्रम (i = 0 ; i < len ; i++)
			*(buf_rx + i) = ioपढ़ो8(src + i);
	पूर्ण अन्यथा अणु
		अगर (desc->info.op_पंचांगpl.addr.buswidth != fiu->drd_op.addr.buswidth ||
		    desc->info.op_पंचांगpl.dummy.nbytes != fiu->drd_op.dummy.nbytes ||
		    desc->info.op_पंचांगpl.cmd.opcode != fiu->drd_op.cmd.opcode ||
		    desc->info.op_पंचांगpl.addr.nbytes != fiu->drd_op.addr.nbytes)
			npcm_fiu_set_drd(fiu, &desc->info.op_पंचांगpl);

		स_नकल_fromio(buf_rx, src, len);
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार npcm_fiu_direct_ग_लिखो(काष्ठा spi_mem_dirmap_desc *desc,
				     u64 offs, माप_प्रकार len, स्थिर व्योम *buf)
अणु
	काष्ठा npcm_fiu_spi *fiu =
		spi_controller_get_devdata(desc->mem->spi->master);
	काष्ठा npcm_fiu_chip *chip = &fiu->chip[desc->mem->spi->chip_select];
	व्योम __iomem *dst = (व्योम __iomem *)(chip->flash_region_mapped_ptr +
					     offs);
	स्थिर u8 *buf_tx = buf;
	u32 i;

	अगर (fiu->spix_mode)
		क्रम (i = 0 ; i < len ; i++)
			ioग_लिखो8(*(buf_tx + i), dst + i);
	अन्यथा
		स_नकल_toio(dst, buf_tx, len);

	वापस len;
पूर्ण

अटल पूर्णांक npcm_fiu_uma_पढ़ो(काष्ठा spi_mem *mem,
			     स्थिर काष्ठा spi_mem_op *op, u32 addr,
			      bool is_address_size, u8 *data, u32 data_size)
अणु
	काष्ठा npcm_fiu_spi *fiu =
		spi_controller_get_devdata(mem->spi->master);
	u32 uma_cfg = BIT(10);
	u32 data_reg[4];
	पूर्णांक ret;
	u32 val;
	u32 i;

	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_DEV_NUM,
			   (mem->spi->chip_select <<
			    NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT));
	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CMD,
			   NPCM_FIU_UMA_CMD_CMD, op->cmd.opcode);

	अगर (is_address_size) अणु
		uma_cfg |= ilog2(op->cmd.buswidth);
		uma_cfg |= ilog2(op->addr.buswidth)
			<< NPCM_FIU_UMA_CFG_ADBPCK_SHIFT;
		uma_cfg |= ilog2(op->dummy.buswidth)
			<< NPCM_FIU_UMA_CFG_DBPCK_SHIFT;
		uma_cfg |= ilog2(op->data.buswidth)
			<< NPCM_FIU_UMA_CFG_RDBPCK_SHIFT;
		uma_cfg |= op->dummy.nbytes << NPCM_FIU_UMA_CFG_DBSIZ_SHIFT;
		uma_cfg |= op->addr.nbytes << NPCM_FIU_UMA_CFG_ADDSIZ_SHIFT;
		regmap_ग_लिखो(fiu->regmap, NPCM_FIU_UMA_ADDR, addr);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(fiu->regmap, NPCM_FIU_UMA_ADDR, 0x0);
	पूर्ण

	uma_cfg |= data_size << NPCM_FIU_UMA_CFG_RDATSIZ_SHIFT;
	regmap_ग_लिखो(fiu->regmap, NPCM_FIU_UMA_CFG, uma_cfg);
	regmap_ग_लिखो_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			  NPCM_FIU_UMA_CTS_EXEC_DONE,
			  NPCM_FIU_UMA_CTS_EXEC_DONE);
	ret = regmap_पढ़ो_poll_समयout(fiu->regmap, NPCM_FIU_UMA_CTS, val,
				       (!(val & NPCM_FIU_UMA_CTS_EXEC_DONE)), 0,
				       UMA_MICRO_SEC_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (data_size) अणु
		क्रम (i = 0; i < DIV_ROUND_UP(data_size, 4); i++)
			regmap_पढ़ो(fiu->regmap, NPCM_FIU_UMA_DR0 + (i * 4),
				    &data_reg[i]);
		स_नकल(data, data_reg, data_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_fiu_uma_ग_लिखो(काष्ठा spi_mem *mem,
			      स्थिर काष्ठा spi_mem_op *op, u8 cmd,
			      bool is_address_size, u8 *data, u32 data_size)
अणु
	काष्ठा npcm_fiu_spi *fiu =
		spi_controller_get_devdata(mem->spi->master);
	u32 uma_cfg = BIT(10);
	u32 data_reg[4] = अणु0पूर्ण;
	u32 val;
	u32 i;

	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_DEV_NUM,
			   (mem->spi->chip_select <<
			    NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT));

	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CMD,
			   NPCM_FIU_UMA_CMD_CMD, cmd);

	अगर (data_size) अणु
		स_नकल(data_reg, data, data_size);
		क्रम (i = 0; i < DIV_ROUND_UP(data_size, 4); i++)
			regmap_ग_लिखो(fiu->regmap, NPCM_FIU_UMA_DW0 + (i * 4),
				     data_reg[i]);
	पूर्ण

	अगर (is_address_size) अणु
		uma_cfg |= ilog2(op->cmd.buswidth);
		uma_cfg |= ilog2(op->addr.buswidth) <<
			NPCM_FIU_UMA_CFG_ADBPCK_SHIFT;
		uma_cfg |= ilog2(op->data.buswidth) <<
			NPCM_FIU_UMA_CFG_WDBPCK_SHIFT;
		uma_cfg |= op->addr.nbytes << NPCM_FIU_UMA_CFG_ADDSIZ_SHIFT;
		regmap_ग_लिखो(fiu->regmap, NPCM_FIU_UMA_ADDR, op->addr.val);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(fiu->regmap, NPCM_FIU_UMA_ADDR, 0x0);
	पूर्ण

	uma_cfg |= (data_size << NPCM_FIU_UMA_CFG_WDATSIZ_SHIFT);
	regmap_ग_लिखो(fiu->regmap, NPCM_FIU_UMA_CFG, uma_cfg);

	regmap_ग_लिखो_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			  NPCM_FIU_UMA_CTS_EXEC_DONE,
			  NPCM_FIU_UMA_CTS_EXEC_DONE);

	वापस regmap_पढ़ो_poll_समयout(fiu->regmap, NPCM_FIU_UMA_CTS, val,
				       (!(val & NPCM_FIU_UMA_CTS_EXEC_DONE)), 0,
					UMA_MICRO_SEC_TIMEOUT);
पूर्ण

अटल पूर्णांक npcm_fiu_manualग_लिखो(काष्ठा spi_mem *mem,
				स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा npcm_fiu_spi *fiu =
		spi_controller_get_devdata(mem->spi->master);
	u8 *data = (u8 *)op->data.buf.out;
	u32 num_data_chunks;
	u32 reमुख्य_data;
	u32 idx = 0;
	पूर्णांक ret;

	num_data_chunks  = op->data.nbytes / CHUNK_SIZE;
	reमुख्य_data  = op->data.nbytes % CHUNK_SIZE;

	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_DEV_NUM,
			   (mem->spi->chip_select <<
			    NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT));
	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_SW_CS, 0);

	ret = npcm_fiu_uma_ग_लिखो(mem, op, op->cmd.opcode, true, शून्य, 0);
	अगर (ret)
		वापस ret;

	/* Starting the data writing loop in multiples of 8 */
	क्रम (idx = 0; idx < num_data_chunks; ++idx) अणु
		ret = npcm_fiu_uma_ग_लिखो(mem, op, data[0], false,
					 &data[1], CHUNK_SIZE - 1);
		अगर (ret)
			वापस ret;

		data += CHUNK_SIZE;
	पूर्ण

	/* Handling chunk reमुख्यs */
	अगर (reमुख्य_data > 0) अणु
		ret = npcm_fiu_uma_ग_लिखो(mem, op, data[0], false,
					 &data[1], reमुख्य_data - 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_SW_CS, NPCM_FIU_UMA_CTS_SW_CS);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_fiu_पढ़ो(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	u8 *data = op->data.buf.in;
	पूर्णांक i, पढ़ोlen, currlen;
	u8 *buf_ptr;
	u32 addr;
	पूर्णांक ret;

	i = 0;
	currlen = op->data.nbytes;

	करो अणु
		addr = ((u32)op->addr.val + i);
		अगर (currlen < 16)
			पढ़ोlen = currlen;
		अन्यथा
			पढ़ोlen = 16;

		buf_ptr = data + i;
		ret = npcm_fiu_uma_पढ़ो(mem, op, addr, true, buf_ptr,
					पढ़ोlen);
		अगर (ret)
			वापस ret;

		i += पढ़ोlen;
		currlen -= 16;
	पूर्ण जबतक (currlen > 0);

	वापस 0;
पूर्ण

अटल व्योम npcm_fiux_set_direct_wr(काष्ठा npcm_fiu_spi *fiu)
अणु
	regmap_ग_लिखो(fiu->regmap, NPCM_FIU_DWR_CFG,
		     NPCM_FIU_DWR_16_BYTE_BURST);
	regmap_update_bits(fiu->regmap, NPCM_FIU_DWR_CFG,
			   NPCM_FIU_DWR_CFG_ABPCK,
			   DWR_ABPCK_4_BIT_PER_CLK << NPCM_FIU_DWR_ABPCK_SHIFT);
	regmap_update_bits(fiu->regmap, NPCM_FIU_DWR_CFG,
			   NPCM_FIU_DWR_CFG_DBPCK,
			   DWR_DBPCK_4_BIT_PER_CLK << NPCM_FIU_DWR_DBPCK_SHIFT);
पूर्ण

अटल व्योम npcm_fiux_set_direct_rd(काष्ठा npcm_fiu_spi *fiu)
अणु
	u32 rx_dummy = 0;

	regmap_ग_लिखो(fiu->regmap, NPCM_FIU_DRD_CFG,
		     NPCM_FIU_DRD_16_BYTE_BURST);
	regmap_update_bits(fiu->regmap, NPCM_FIU_DRD_CFG,
			   NPCM_FIU_DRD_CFG_ACCTYPE,
			   DRD_SPI_X_MODE << NPCM_FIU_DRD_ACCTYPE_SHIFT);
	regmap_update_bits(fiu->regmap, NPCM_FIU_DRD_CFG,
			   NPCM_FIU_DRD_CFG_DBW,
			   rx_dummy << NPCM_FIU_DRD_DBW_SHIFT);
पूर्ण

अटल पूर्णांक npcm_fiu_exec_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा npcm_fiu_spi *fiu =
		spi_controller_get_devdata(mem->spi->master);
	काष्ठा npcm_fiu_chip *chip = &fiu->chip[mem->spi->chip_select];
	पूर्णांक ret = 0;
	u8 *buf;

	dev_dbg(fiu->dev, "cmd:%#x mode:%d.%d.%d.%d addr:%#llx len:%#x\n",
		op->cmd.opcode, op->cmd.buswidth, op->addr.buswidth,
		op->dummy.buswidth, op->data.buswidth, op->addr.val,
		op->data.nbytes);

	अगर (fiu->spix_mode || op->addr.nbytes > 4)
		वापस -ENOTSUPP;

	अगर (fiu->clkrate != chip->clkrate) अणु
		ret = clk_set_rate(fiu->clk, chip->clkrate);
		अगर (ret < 0)
			dev_warn(fiu->dev, "Failed setting %lu frequency, stay at %lu frequency\n",
				 chip->clkrate, fiu->clkrate);
		अन्यथा
			fiu->clkrate = chip->clkrate;
	पूर्ण

	अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		अगर (!op->addr.nbytes) अणु
			buf = op->data.buf.in;
			ret = npcm_fiu_uma_पढ़ो(mem, op, op->addr.val, false,
						buf, op->data.nbytes);
		पूर्ण अन्यथा अणु
			ret = npcm_fiu_पढ़ो(mem, op);
		पूर्ण
	पूर्ण अन्यथा  अणु
		अगर (!op->addr.nbytes && !op->data.nbytes)
			ret = npcm_fiu_uma_ग_लिखो(mem, op, op->cmd.opcode, false,
						 शून्य, 0);
		अगर (op->addr.nbytes && !op->data.nbytes) अणु
			पूर्णांक i;
			u8 buf_addr[4];
			u32 addr = op->addr.val;

			क्रम (i = op->addr.nbytes - 1; i >= 0; i--) अणु
				buf_addr[i] = addr & 0xff;
				addr >>= 8;
			पूर्ण
			ret = npcm_fiu_uma_ग_लिखो(mem, op, op->cmd.opcode, false,
						 buf_addr, op->addr.nbytes);
		पूर्ण
		अगर (!op->addr.nbytes && op->data.nbytes)
			ret = npcm_fiu_uma_ग_लिखो(mem, op, op->cmd.opcode, false,
						 (u8 *)op->data.buf.out,
						 op->data.nbytes);
		अगर (op->addr.nbytes && op->data.nbytes)
			ret = npcm_fiu_manualग_लिखो(mem, op);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक npcm_fiu_dirmap_create(काष्ठा spi_mem_dirmap_desc *desc)
अणु
	काष्ठा npcm_fiu_spi *fiu =
		spi_controller_get_devdata(desc->mem->spi->master);
	काष्ठा npcm_fiu_chip *chip = &fiu->chip[desc->mem->spi->chip_select];
	काष्ठा regmap *gcr_regmap;

	अगर (!fiu->res_mem) अणु
		dev_warn(fiu->dev, "Reserved memory not defined, direct read disabled\n");
		desc->nodirmap = true;
		वापस 0;
	पूर्ण

	अगर (!fiu->spix_mode &&
	    desc->info.op_पंचांगpl.data.dir == SPI_MEM_DATA_OUT) अणु
		desc->nodirmap = true;
		वापस 0;
	पूर्ण

	अगर (!chip->flash_region_mapped_ptr) अणु
		chip->flash_region_mapped_ptr =
			devm_ioremap(fiu->dev, (fiu->res_mem->start +
							(fiu->info->max_map_size *
						    desc->mem->spi->chip_select)),
					     (u32)desc->info.length);
		अगर (!chip->flash_region_mapped_ptr) अणु
			dev_warn(fiu->dev, "Error mapping memory region, direct read disabled\n");
			desc->nodirmap = true;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (of_device_is_compatible(fiu->dev->of_node, "nuvoton,npcm750-fiu")) अणु
		gcr_regmap =
			syscon_regmap_lookup_by_compatible("nuvoton,npcm750-gcr");
		अगर (IS_ERR(gcr_regmap)) अणु
			dev_warn(fiu->dev, "Didn't find nuvoton,npcm750-gcr, direct read disabled\n");
			desc->nodirmap = true;
			वापस 0;
		पूर्ण
		regmap_update_bits(gcr_regmap, NPCM7XX_INTCR3_OFFSET,
				   NPCM7XX_INTCR3_FIU_FIX,
				   NPCM7XX_INTCR3_FIU_FIX);
	पूर्ण

	अगर (desc->info.op_पंचांगpl.data.dir == SPI_MEM_DATA_IN) अणु
		अगर (!fiu->spix_mode)
			npcm_fiu_set_drd(fiu, &desc->info.op_पंचांगpl);
		अन्यथा
			npcm_fiux_set_direct_rd(fiu);

	पूर्ण अन्यथा अणु
		npcm_fiux_set_direct_wr(fiu);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_fiu_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctrl = spi->master;
	काष्ठा npcm_fiu_spi *fiu = spi_controller_get_devdata(ctrl);
	काष्ठा npcm_fiu_chip *chip;

	chip = &fiu->chip[spi->chip_select];
	chip->fiu = fiu;
	chip->chipselect = spi->chip_select;
	chip->clkrate = spi->max_speed_hz;

	fiu->clkrate = clk_get_rate(fiu->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops npcm_fiu_mem_ops = अणु
	.exec_op = npcm_fiu_exec_op,
	.dirmap_create = npcm_fiu_dirmap_create,
	.dirmap_पढ़ो = npcm_fiu_direct_पढ़ो,
	.dirmap_ग_लिखो = npcm_fiu_direct_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा of_device_id npcm_fiu_dt_ids[] = अणु
	अणु .compatible = "nuvoton,npcm750-fiu", .data = &npxm7xx_fiu_data  पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक npcm_fiu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा fiu_data *fiu_data_match;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spi_controller *ctrl;
	काष्ठा npcm_fiu_spi *fiu;
	व्योम __iomem *regbase;
	काष्ठा resource *res;
	पूर्णांक id, ret;

	ctrl = devm_spi_alloc_master(dev, माप(*fiu));
	अगर (!ctrl)
		वापस -ENOMEM;

	fiu = spi_controller_get_devdata(ctrl);

	match = of_match_device(npcm_fiu_dt_ids, dev);
	अगर (!match || !match->data) अणु
		dev_err(dev, "No compatible OF match\n");
		वापस -ENODEV;
	पूर्ण

	fiu_data_match = match->data;
	id = of_alias_get_id(dev->of_node, "fiu");
	अगर (id < 0 || id >= fiu_data_match->fiu_max) अणु
		dev_err(dev, "Invalid platform device id: %d\n", id);
		वापस -EINVAL;
	पूर्ण

	fiu->info = &fiu_data_match->npcm_fiu_data_info[id];

	platक्रमm_set_drvdata(pdev, fiu);
	fiu->dev = dev;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "control");
	regbase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regbase))
		वापस PTR_ERR(regbase);

	fiu->regmap = devm_regmap_init_mmio(dev, regbase,
					    &npcm_mtd_regmap_config);
	अगर (IS_ERR(fiu->regmap)) अणु
		dev_err(dev, "Failed to create regmap\n");
		वापस PTR_ERR(fiu->regmap);
	पूर्ण

	fiu->res_mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						    "memory");
	fiu->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(fiu->clk))
		वापस PTR_ERR(fiu->clk);

	fiu->spix_mode = of_property_पढ़ो_bool(dev->of_node,
					       "nuvoton,spix-mode");

	platक्रमm_set_drvdata(pdev, fiu);
	clk_prepare_enable(fiu->clk);

	ctrl->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD
		| SPI_TX_DUAL | SPI_TX_QUAD;
	ctrl->setup = npcm_fiu_setup;
	ctrl->bus_num = -1;
	ctrl->mem_ops = &npcm_fiu_mem_ops;
	ctrl->num_chipselect = fiu->info->max_cs;
	ctrl->dev.of_node = dev->of_node;

	ret = devm_spi_रेजिस्टर_master(dev, ctrl);
	अगर (ret)
		clk_disable_unprepare(fiu->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक npcm_fiu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा npcm_fiu_spi *fiu = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(fiu->clk);
	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(of, npcm_fiu_dt_ids);

अटल काष्ठा platक्रमm_driver npcm_fiu_driver = अणु
	.driver = अणु
		.name	= "NPCM-FIU",
		.bus	= &platक्रमm_bus_type,
		.of_match_table = npcm_fiu_dt_ids,
	पूर्ण,
	.probe      = npcm_fiu_probe,
	.हटाओ	    = npcm_fiu_हटाओ,
पूर्ण;
module_platक्रमm_driver(npcm_fiu_driver);

MODULE_DESCRIPTION("Nuvoton FLASH Interface Unit SPI Controller Driver");
MODULE_AUTHOR("Tomer Maimon <tomer.maimon@nuvoton.com>");
MODULE_LICENSE("GPL v2");
