<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2009-2015 Freescale Semiconductor, Inc. and others
 *
 * Description: MPC5125, VF610, MCF54418 and Kinetis K70 Nand driver.
 * Jason ported to M54418TWR and MVFA5 (VF610).
 * Authors: Stefan Agner <stefan.agner@toradex.com>
 *          Bill Pringlemeir <bpringlemeir@nbsps.com>
 *          Shaohui Xie <b21989@मुक्तscale.com>
 *          Jason Jin <Jason.jin@मुक्तscale.com>
 *
 * Based on original driver mpc5121_nfc.c.
 *
 * Limitations:
 * - Untested on MPC5125 and M54418.
 * - DMA and pipelining not used.
 * - 2K pages or less.
 * - HW ECC: Only 2K page with 64+ OOB.
 * - HW ECC: Only 24 and 32-bit error correction implemented.
 */

#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/swab.h>

#घोषणा	DRV_NAME		"vf610_nfc"

/* Register Offsets */
#घोषणा NFC_FLASH_CMD1			0x3F00
#घोषणा NFC_FLASH_CMD2			0x3F04
#घोषणा NFC_COL_ADDR			0x3F08
#घोषणा NFC_ROW_ADDR			0x3F0c
#घोषणा NFC_ROW_ADDR_INC		0x3F14
#घोषणा NFC_FLASH_STATUS1		0x3F18
#घोषणा NFC_FLASH_STATUS2		0x3F1c
#घोषणा NFC_CACHE_SWAP			0x3F28
#घोषणा NFC_SECTOR_SIZE			0x3F2c
#घोषणा NFC_FLASH_CONFIG		0x3F30
#घोषणा NFC_IRQ_STATUS			0x3F38

/* Addresses क्रम NFC MAIN RAM BUFFER areas */
#घोषणा NFC_MAIN_AREA(n)		((n) *  0x1000)

#घोषणा PAGE_2K				0x0800
#घोषणा OOB_64				0x0040
#घोषणा OOB_MAX				0x0100

/* NFC_CMD2[CODE] controller cycle bit masks */
#घोषणा COMMAND_CMD_BYTE1		BIT(14)
#घोषणा COMMAND_CAR_BYTE1		BIT(13)
#घोषणा COMMAND_CAR_BYTE2		BIT(12)
#घोषणा COMMAND_RAR_BYTE1		BIT(11)
#घोषणा COMMAND_RAR_BYTE2		BIT(10)
#घोषणा COMMAND_RAR_BYTE3		BIT(9)
#घोषणा COMMAND_NADDR_BYTES(x)		GENMASK(13, 13 - (x) + 1)
#घोषणा COMMAND_WRITE_DATA		BIT(8)
#घोषणा COMMAND_CMD_BYTE2		BIT(7)
#घोषणा COMMAND_RB_HANDSHAKE		BIT(6)
#घोषणा COMMAND_READ_DATA		BIT(5)
#घोषणा COMMAND_CMD_BYTE3		BIT(4)
#घोषणा COMMAND_READ_STATUS		BIT(3)
#घोषणा COMMAND_READ_ID			BIT(2)

/* NFC ECC mode define */
#घोषणा ECC_BYPASS			0
#घोषणा ECC_45_BYTE			6
#घोषणा ECC_60_BYTE			7

/*** Register Mask and bit definitions */

/* NFC_FLASH_CMD1 Field */
#घोषणा CMD_BYTE2_MASK				0xFF000000
#घोषणा CMD_BYTE2_SHIFT				24

/* NFC_FLASH_CM2 Field */
#घोषणा CMD_BYTE1_MASK				0xFF000000
#घोषणा CMD_BYTE1_SHIFT				24
#घोषणा CMD_CODE_MASK				0x00FFFF00
#घोषणा CMD_CODE_SHIFT				8
#घोषणा BUFNO_MASK				0x00000006
#घोषणा BUFNO_SHIFT				1
#घोषणा START_BIT				BIT(0)

/* NFC_COL_ADDR Field */
#घोषणा COL_ADDR_MASK				0x0000FFFF
#घोषणा COL_ADDR_SHIFT				0
#घोषणा COL_ADDR(pos, val)			(((val) & 0xFF) << (8 * (pos)))

/* NFC_ROW_ADDR Field */
#घोषणा ROW_ADDR_MASK				0x00FFFFFF
#घोषणा ROW_ADDR_SHIFT				0
#घोषणा ROW_ADDR(pos, val)			(((val) & 0xFF) << (8 * (pos)))

#घोषणा ROW_ADDR_CHIP_SEL_RB_MASK		0xF0000000
#घोषणा ROW_ADDR_CHIP_SEL_RB_SHIFT		28
#घोषणा ROW_ADDR_CHIP_SEL_MASK			0x0F000000
#घोषणा ROW_ADDR_CHIP_SEL_SHIFT			24

/* NFC_FLASH_STATUS2 Field */
#घोषणा STATUS_BYTE1_MASK			0x000000FF

/* NFC_FLASH_CONFIG Field */
#घोषणा CONFIG_ECC_SRAM_ADDR_MASK		0x7FC00000
#घोषणा CONFIG_ECC_SRAM_ADDR_SHIFT		22
#घोषणा CONFIG_ECC_SRAM_REQ_BIT			BIT(21)
#घोषणा CONFIG_DMA_REQ_BIT			BIT(20)
#घोषणा CONFIG_ECC_MODE_MASK			0x000E0000
#घोषणा CONFIG_ECC_MODE_SHIFT			17
#घोषणा CONFIG_FAST_FLASH_BIT			BIT(16)
#घोषणा CONFIG_16BIT				BIT(7)
#घोषणा CONFIG_BOOT_MODE_BIT			BIT(6)
#घोषणा CONFIG_ADDR_AUTO_INCR_BIT		BIT(5)
#घोषणा CONFIG_BUFNO_AUTO_INCR_BIT		BIT(4)
#घोषणा CONFIG_PAGE_CNT_MASK			0xF
#घोषणा CONFIG_PAGE_CNT_SHIFT			0

/* NFC_IRQ_STATUS Field */
#घोषणा IDLE_IRQ_BIT				BIT(29)
#घोषणा IDLE_EN_BIT				BIT(20)
#घोषणा CMD_DONE_CLEAR_BIT			BIT(18)
#घोषणा IDLE_CLEAR_BIT				BIT(17)

/*
 * ECC status - seems to consume 8 bytes (द्विगुन word). The करोcumented
 * status byte is located in the lowest byte of the second word (which is
 * the 4th or 7th byte depending on endianness).
 * Calculate an offset to store the ECC status at the end of the buffer.
 */
#घोषणा ECC_SRAM_ADDR		(PAGE_2K + OOB_MAX - 8)

#घोषणा ECC_STATUS		0x4
#घोषणा ECC_STATUS_MASK		0x80
#घोषणा ECC_STATUS_ERR_COUNT	0x3F

क्रमागत vf610_nfc_variant अणु
	NFC_VFC610 = 1,
पूर्ण;

काष्ठा vf610_nfc अणु
	काष्ठा nand_controller base;
	काष्ठा nand_chip chip;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा completion cmd_करोne;
	/* Status and ID are in alternate locations. */
	क्रमागत vf610_nfc_variant variant;
	काष्ठा clk *clk;
	/*
	 * Indicate that user data is accessed (full page/oob). This is
	 * useful to indicate the driver whether to swap byte endianness.
	 * See comments in vf610_nfc_rd_from_sram/vf610_nfc_wr_to_sram.
	 */
	bool data_access;
	u32 ecc_mode;
पूर्ण;

अटल अंतरभूत काष्ठा vf610_nfc *chip_to_nfc(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा vf610_nfc, chip);
पूर्ण

अटल अंतरभूत u32 vf610_nfc_पढ़ो(काष्ठा vf610_nfc *nfc, uपूर्णांक reg)
अणु
	वापस पढ़ोl(nfc->regs + reg);
पूर्ण

अटल अंतरभूत व्योम vf610_nfc_ग_लिखो(काष्ठा vf610_nfc *nfc, uपूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, nfc->regs + reg);
पूर्ण

अटल अंतरभूत व्योम vf610_nfc_set(काष्ठा vf610_nfc *nfc, uपूर्णांक reg, u32 bits)
अणु
	vf610_nfc_ग_लिखो(nfc, reg, vf610_nfc_पढ़ो(nfc, reg) | bits);
पूर्ण

अटल अंतरभूत व्योम vf610_nfc_clear(काष्ठा vf610_nfc *nfc, uपूर्णांक reg, u32 bits)
अणु
	vf610_nfc_ग_लिखो(nfc, reg, vf610_nfc_पढ़ो(nfc, reg) & ~bits);
पूर्ण

अटल अंतरभूत व्योम vf610_nfc_set_field(काष्ठा vf610_nfc *nfc, u32 reg,
				       u32 mask, u32 shअगरt, u32 val)
अणु
	vf610_nfc_ग_लिखो(nfc, reg,
			(vf610_nfc_पढ़ो(nfc, reg) & (~mask)) | val << shअगरt);
पूर्ण

अटल अंतरभूत bool vf610_nfc_kernel_is_little_endian(व्योम)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/**
 * Read accessor क्रम पूर्णांकernal SRAM buffer
 * @dst: destination address in regular memory
 * @src: source address in SRAM buffer
 * @len: bytes to copy
 * @fix_endian: Fix endianness अगर required
 *
 * Use this accessor क्रम the पूर्णांकernal SRAM buffers. On the ARM
 * Freescale Vybrid SoC it's known that the driver can treat
 * the SRAM buffer as अगर it's memory. Other platक्रमm might need
 * to treat the buffers dअगरferently.
 *
 * The controller stores bytes from the न_अंकD chip पूर्णांकernally in big
 * endianness. On little endian platक्रमms such as Vybrid this leads
 * to reversed byte order.
 * For perक्रमmance reason (and earlier probably due to unawareness)
 * the driver aव्योमs correcting endianness where it has control over
 * ग_लिखो and पढ़ो side (e.g. page wise data access).
 */
अटल अंतरभूत व्योम vf610_nfc_rd_from_sram(व्योम *dst, स्थिर व्योम __iomem *src,
					  माप_प्रकार len, bool fix_endian)
अणु
	अगर (vf610_nfc_kernel_is_little_endian() && fix_endian) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < len; i += 4) अणु
			u32 val = swab32(__raw_पढ़ोl(src + i));

			स_नकल(dst + i, &val, min(माप(val), len - i));
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल_fromio(dst, src, len);
	पूर्ण
पूर्ण

/**
 * Write accessor क्रम पूर्णांकernal SRAM buffer
 * @dst: destination address in SRAM buffer
 * @src: source address in regular memory
 * @len: bytes to copy
 * @fix_endian: Fix endianness अगर required
 *
 * Use this accessor क्रम the पूर्णांकernal SRAM buffers. On the ARM
 * Freescale Vybrid SoC it's known that the driver can treat
 * the SRAM buffer as अगर it's memory. Other platक्रमm might need
 * to treat the buffers dअगरferently.
 *
 * The controller stores bytes from the न_अंकD chip पूर्णांकernally in big
 * endianness. On little endian platक्रमms such as Vybrid this leads
 * to reversed byte order.
 * For perक्रमmance reason (and earlier probably due to unawareness)
 * the driver aव्योमs correcting endianness where it has control over
 * ग_लिखो and पढ़ो side (e.g. page wise data access).
 */
अटल अंतरभूत व्योम vf610_nfc_wr_to_sram(व्योम __iomem *dst, स्थिर व्योम *src,
					माप_प्रकार len, bool fix_endian)
अणु
	अगर (vf610_nfc_kernel_is_little_endian() && fix_endian) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < len; i += 4) अणु
			u32 val;

			स_नकल(&val, src + i, min(माप(val), len - i));
			__raw_ग_लिखोl(swab32(val), dst + i);
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल_toio(dst, src, len);
	पूर्ण
पूर्ण

/* Clear flags क्रम upcoming command */
अटल अंतरभूत व्योम vf610_nfc_clear_status(काष्ठा vf610_nfc *nfc)
अणु
	u32 पंचांगp = vf610_nfc_पढ़ो(nfc, NFC_IRQ_STATUS);

	पंचांगp |= CMD_DONE_CLEAR_BIT | IDLE_CLEAR_BIT;
	vf610_nfc_ग_लिखो(nfc, NFC_IRQ_STATUS, पंचांगp);
पूर्ण

अटल व्योम vf610_nfc_करोne(काष्ठा vf610_nfc *nfc)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(100);

	/*
	 * Barrier is needed after this ग_लिखो. This ग_लिखो need
	 * to be करोne beक्रमe पढ़ोing the next रेजिस्टर the first
	 * समय.
	 * vf610_nfc_set implicates such a barrier by using ग_लिखोl
	 * to ग_लिखो to the रेजिस्टर.
	 */
	vf610_nfc_set(nfc, NFC_IRQ_STATUS, IDLE_EN_BIT);
	vf610_nfc_set(nfc, NFC_FLASH_CMD2, START_BIT);

	अगर (!रुको_क्रम_completion_समयout(&nfc->cmd_करोne, समयout))
		dev_warn(nfc->dev, "Timeout while waiting for BUSY.\n");

	vf610_nfc_clear_status(nfc);
पूर्ण

अटल irqवापस_t vf610_nfc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vf610_nfc *nfc = data;

	vf610_nfc_clear(nfc, NFC_IRQ_STATUS, IDLE_EN_BIT);
	complete(&nfc->cmd_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम vf610_nfc_ecc_mode(काष्ठा vf610_nfc *nfc, पूर्णांक ecc_mode)
अणु
	vf610_nfc_set_field(nfc, NFC_FLASH_CONFIG,
			    CONFIG_ECC_MODE_MASK,
			    CONFIG_ECC_MODE_SHIFT, ecc_mode);
पूर्ण

अटल अंतरभूत व्योम vf610_nfc_run(काष्ठा vf610_nfc *nfc, u32 col, u32 row,
				 u32 cmd1, u32 cmd2, u32 trfr_sz)
अणु
	vf610_nfc_set_field(nfc, NFC_COL_ADDR, COL_ADDR_MASK,
			    COL_ADDR_SHIFT, col);

	vf610_nfc_set_field(nfc, NFC_ROW_ADDR, ROW_ADDR_MASK,
			    ROW_ADDR_SHIFT, row);

	vf610_nfc_ग_लिखो(nfc, NFC_SECTOR_SIZE, trfr_sz);
	vf610_nfc_ग_लिखो(nfc, NFC_FLASH_CMD1, cmd1);
	vf610_nfc_ग_लिखो(nfc, NFC_FLASH_CMD2, cmd2);

	dev_dbg(nfc->dev,
		"col 0x%04x, row 0x%08x, cmd1 0x%08x, cmd2 0x%08x, len %d\n",
		col, row, cmd1, cmd2, trfr_sz);

	vf610_nfc_करोne(nfc);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा nand_op_instr *
vf610_get_next_instr(स्थिर काष्ठा nand_subop *subop, पूर्णांक *op_id)
अणु
	अगर (*op_id + 1 >= subop->ninstrs)
		वापस शून्य;

	(*op_id)++;

	वापस &subop->instrs[*op_id];
पूर्ण

अटल पूर्णांक vf610_nfc_cmd(काष्ठा nand_chip *chip,
			 स्थिर काष्ठा nand_subop *subop)
अणु
	स्थिर काष्ठा nand_op_instr *instr;
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	पूर्णांक op_id = -1, trfr_sz = 0, offset = 0;
	u32 col = 0, row = 0, cmd1 = 0, cmd2 = 0, code = 0;
	bool क्रमce8bit = false;

	/*
	 * Some ops are optional, but the hardware requires the operations
	 * to be in this exact order.
	 * The op parser enक्रमces the order and makes sure that there isn't
	 * a पढ़ो and ग_लिखो element in a single operation.
	 */
	instr = vf610_get_next_instr(subop, &op_id);
	अगर (!instr)
		वापस -EINVAL;

	अगर (instr && instr->type == न_अंकD_OP_CMD_INSTR) अणु
		cmd2 |= instr->ctx.cmd.opcode << CMD_BYTE1_SHIFT;
		code |= COMMAND_CMD_BYTE1;

		instr = vf610_get_next_instr(subop, &op_id);
	पूर्ण

	अगर (instr && instr->type == न_अंकD_OP_ADDR_INSTR) अणु
		पूर्णांक naddrs = nand_subop_get_num_addr_cyc(subop, op_id);
		पूर्णांक i = nand_subop_get_addr_start_off(subop, op_id);

		क्रम (; i < naddrs; i++) अणु
			u8 val = instr->ctx.addr.addrs[i];

			अगर (i < 2)
				col |= COL_ADDR(i, val);
			अन्यथा
				row |= ROW_ADDR(i - 2, val);
		पूर्ण
		code |= COMMAND_NADDR_BYTES(naddrs);

		instr = vf610_get_next_instr(subop, &op_id);
	पूर्ण

	अगर (instr && instr->type == न_अंकD_OP_DATA_OUT_INSTR) अणु
		trfr_sz = nand_subop_get_data_len(subop, op_id);
		offset = nand_subop_get_data_start_off(subop, op_id);
		क्रमce8bit = instr->ctx.data.क्रमce_8bit;

		/*
		 * Don't fix endianness on page access क्रम historical reasons.
		 * See comment in vf610_nfc_wr_to_sram
		 */
		vf610_nfc_wr_to_sram(nfc->regs + NFC_MAIN_AREA(0) + offset,
				     instr->ctx.data.buf.out + offset,
				     trfr_sz, !nfc->data_access);
		code |= COMMAND_WRITE_DATA;

		instr = vf610_get_next_instr(subop, &op_id);
	पूर्ण

	अगर (instr && instr->type == न_अंकD_OP_CMD_INSTR) अणु
		cmd1 |= instr->ctx.cmd.opcode << CMD_BYTE2_SHIFT;
		code |= COMMAND_CMD_BYTE2;

		instr = vf610_get_next_instr(subop, &op_id);
	पूर्ण

	अगर (instr && instr->type == न_अंकD_OP_WAITRDY_INSTR) अणु
		code |= COMMAND_RB_HANDSHAKE;

		instr = vf610_get_next_instr(subop, &op_id);
	पूर्ण

	अगर (instr && instr->type == न_अंकD_OP_DATA_IN_INSTR) अणु
		trfr_sz = nand_subop_get_data_len(subop, op_id);
		offset = nand_subop_get_data_start_off(subop, op_id);
		क्रमce8bit = instr->ctx.data.क्रमce_8bit;

		code |= COMMAND_READ_DATA;
	पूर्ण

	अगर (क्रमce8bit && (chip->options & न_अंकD_BUSWIDTH_16))
		vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_16BIT);

	cmd2 |= code << CMD_CODE_SHIFT;

	vf610_nfc_run(nfc, col, row, cmd1, cmd2, trfr_sz);

	अगर (instr && instr->type == न_अंकD_OP_DATA_IN_INSTR) अणु
		/*
		 * Don't fix endianness on page access क्रम historical reasons.
		 * See comment in vf610_nfc_rd_from_sram
		 */
		vf610_nfc_rd_from_sram(instr->ctx.data.buf.in + offset,
				       nfc->regs + NFC_MAIN_AREA(0) + offset,
				       trfr_sz, !nfc->data_access);
	पूर्ण

	अगर (क्रमce8bit && (chip->options & न_अंकD_BUSWIDTH_16))
		vf610_nfc_set(nfc, NFC_FLASH_CONFIG, CONFIG_16BIT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_op_parser vf610_nfc_op_parser = न_अंकD_OP_PARSER(
	न_अंकD_OP_PARSER_PATTERN(vf610_nfc_cmd,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 5),
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(true, PAGE_2K + OOB_MAX),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true)),
	न_अंकD_OP_PARSER_PATTERN(vf610_nfc_cmd,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 5),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(true, PAGE_2K + OOB_MAX)),
	);

/*
 * This function supports Vybrid only (MPC5125 would have full RB and four CS)
 */
अटल व्योम vf610_nfc_select_target(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक cs)
अणु
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	u32 पंचांगp;

	/* Vybrid only (MPC5125 would have full RB and four CS) */
	अगर (nfc->variant != NFC_VFC610)
		वापस;

	पंचांगp = vf610_nfc_पढ़ो(nfc, NFC_ROW_ADDR);
	पंचांगp &= ~(ROW_ADDR_CHIP_SEL_RB_MASK | ROW_ADDR_CHIP_SEL_MASK);
	पंचांगp |= 1 << ROW_ADDR_CHIP_SEL_RB_SHIFT;
	पंचांगp |= BIT(cs) << ROW_ADDR_CHIP_SEL_SHIFT;

	vf610_nfc_ग_लिखो(nfc, NFC_ROW_ADDR, पंचांगp);
पूर्ण

अटल पूर्णांक vf610_nfc_exec_op(काष्ठा nand_chip *chip,
			     स्थिर काष्ठा nand_operation *op,
			     bool check_only)
अणु
	अगर (!check_only)
		vf610_nfc_select_target(chip, op->cs);

	वापस nand_op_parser_exec_op(chip, &vf610_nfc_op_parser, op,
				      check_only);
पूर्ण

अटल अंतरभूत पूर्णांक vf610_nfc_correct_data(काष्ठा nand_chip *chip, uपूर्णांक8_t *dat,
					 uपूर्णांक8_t *oob, पूर्णांक page)
अणु
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u32 ecc_status_off = NFC_MAIN_AREA(0) + ECC_SRAM_ADDR + ECC_STATUS;
	u8 ecc_status;
	u8 ecc_count;
	पूर्णांक flips_threshold = nfc->chip.ecc.strength / 2;

	ecc_status = vf610_nfc_पढ़ो(nfc, ecc_status_off) & 0xff;
	ecc_count = ecc_status & ECC_STATUS_ERR_COUNT;

	अगर (!(ecc_status & ECC_STATUS_MASK))
		वापस ecc_count;

	nfc->data_access = true;
	nand_पढ़ो_oob_op(&nfc->chip, page, 0, oob, mtd->oobsize);
	nfc->data_access = false;

	/*
	 * On an erased page, bit count (including OOB) should be zero or
	 * at least less then half of the ECC strength.
	 */
	वापस nand_check_erased_ecc_chunk(dat, nfc->chip.ecc.size, oob,
					   mtd->oobsize, शून्य, 0,
					   flips_threshold);
पूर्ण

अटल व्योम vf610_nfc_fill_row(काष्ठा nand_chip *chip, पूर्णांक page, u32 *code,
			       u32 *row)
अणु
	*row = ROW_ADDR(0, page & 0xff) | ROW_ADDR(1, page >> 8);
	*code |= COMMAND_RAR_BYTE1 | COMMAND_RAR_BYTE2;

	अगर (chip->options & न_अंकD_ROW_ADDR_3) अणु
		*row |= ROW_ADDR(2, page >> 16);
		*code |= COMMAND_RAR_BYTE3;
	पूर्ण
पूर्ण

अटल पूर्णांक vf610_nfc_पढ़ो_page(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			       पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक trfr_sz = mtd->ग_लिखोsize + mtd->oobsize;
	u32 row = 0, cmd1 = 0, cmd2 = 0, code = 0;
	पूर्णांक stat;

	vf610_nfc_select_target(chip, chip->cur_cs);

	cmd2 |= न_अंकD_CMD_READ0 << CMD_BYTE1_SHIFT;
	code |= COMMAND_CMD_BYTE1 | COMMAND_CAR_BYTE1 | COMMAND_CAR_BYTE2;

	vf610_nfc_fill_row(chip, page, &code, &row);

	cmd1 |= न_अंकD_CMD_READSTART << CMD_BYTE2_SHIFT;
	code |= COMMAND_CMD_BYTE2 | COMMAND_RB_HANDSHAKE | COMMAND_READ_DATA;

	cmd2 |= code << CMD_CODE_SHIFT;

	vf610_nfc_ecc_mode(nfc, nfc->ecc_mode);
	vf610_nfc_run(nfc, 0, row, cmd1, cmd2, trfr_sz);
	vf610_nfc_ecc_mode(nfc, ECC_BYPASS);

	/*
	 * Don't fix endianness on page access क्रम historical reasons.
	 * See comment in vf610_nfc_rd_from_sram
	 */
	vf610_nfc_rd_from_sram(buf, nfc->regs + NFC_MAIN_AREA(0),
			       mtd->ग_लिखोsize, false);
	अगर (oob_required)
		vf610_nfc_rd_from_sram(chip->oob_poi,
				       nfc->regs + NFC_MAIN_AREA(0) +
						   mtd->ग_लिखोsize,
				       mtd->oobsize, false);

	stat = vf610_nfc_correct_data(chip, buf, chip->oob_poi, page);

	अगर (stat < 0) अणु
		mtd->ecc_stats.failed++;
		वापस 0;
	पूर्ण अन्यथा अणु
		mtd->ecc_stats.corrected += stat;
		वापस stat;
	पूर्ण
पूर्ण

अटल पूर्णांक vf610_nfc_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक trfr_sz = mtd->ग_लिखोsize + mtd->oobsize;
	u32 row = 0, cmd1 = 0, cmd2 = 0, code = 0;
	u8 status;
	पूर्णांक ret;

	vf610_nfc_select_target(chip, chip->cur_cs);

	cmd2 |= न_अंकD_CMD_SEQIN << CMD_BYTE1_SHIFT;
	code |= COMMAND_CMD_BYTE1 | COMMAND_CAR_BYTE1 | COMMAND_CAR_BYTE2;

	vf610_nfc_fill_row(chip, page, &code, &row);

	cmd1 |= न_अंकD_CMD_PAGEPROG << CMD_BYTE2_SHIFT;
	code |= COMMAND_CMD_BYTE2 | COMMAND_WRITE_DATA;

	/*
	 * Don't fix endianness on page access क्रम historical reasons.
	 * See comment in vf610_nfc_wr_to_sram
	 */
	vf610_nfc_wr_to_sram(nfc->regs + NFC_MAIN_AREA(0), buf,
			     mtd->ग_लिखोsize, false);

	code |= COMMAND_RB_HANDSHAKE;
	cmd2 |= code << CMD_CODE_SHIFT;

	vf610_nfc_ecc_mode(nfc, nfc->ecc_mode);
	vf610_nfc_run(nfc, 0, row, cmd1, cmd2, trfr_sz);
	vf610_nfc_ecc_mode(nfc, ECC_BYPASS);

	ret = nand_status_op(chip, &status);
	अगर (ret)
		वापस ret;

	अगर (status & न_अंकD_STATUS_FAIL)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक vf610_nfc_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf,
				   पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	पूर्णांक ret;

	nfc->data_access = true;
	ret = nand_पढ़ो_page_raw(chip, buf, oob_required, page);
	nfc->data_access = false;

	वापस ret;
पूर्ण

अटल पूर्णांक vf610_nfc_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	nfc->data_access = true;
	ret = nand_prog_page_begin_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	अगर (!ret && oob_required)
		ret = nand_ग_लिखो_data_op(chip, chip->oob_poi, mtd->oobsize,
					 false);
	nfc->data_access = false;

	अगर (ret)
		वापस ret;

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक vf610_nfc_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	पूर्णांक ret;

	nfc->data_access = true;
	ret = nand_पढ़ो_oob_std(chip, page);
	nfc->data_access = false;

	वापस ret;
पूर्ण

अटल पूर्णांक vf610_nfc_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);
	पूर्णांक ret;

	nfc->data_access = true;
	ret = nand_prog_page_begin_op(chip, page, mtd->ग_लिखोsize,
				      chip->oob_poi, mtd->oobsize);
	nfc->data_access = false;

	अगर (ret)
		वापस ret;

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id vf610_nfc_dt_ids[] = अणु
	अणु .compatible = "fsl,vf610-nfc", .data = (व्योम *)NFC_VFC610 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vf610_nfc_dt_ids);

अटल व्योम vf610_nfc_preinit_controller(काष्ठा vf610_nfc *nfc)
अणु
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_16BIT);
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_ADDR_AUTO_INCR_BIT);
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_BUFNO_AUTO_INCR_BIT);
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_BOOT_MODE_BIT);
	vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_DMA_REQ_BIT);
	vf610_nfc_set(nfc, NFC_FLASH_CONFIG, CONFIG_FAST_FLASH_BIT);
	vf610_nfc_ecc_mode(nfc, ECC_BYPASS);

	/* Disable भव pages, only one elementary transfer unit */
	vf610_nfc_set_field(nfc, NFC_FLASH_CONFIG, CONFIG_PAGE_CNT_MASK,
			    CONFIG_PAGE_CNT_SHIFT, 1);
पूर्ण

अटल व्योम vf610_nfc_init_controller(काष्ठा vf610_nfc *nfc)
अणु
	अगर (nfc->chip.options & न_अंकD_BUSWIDTH_16)
		vf610_nfc_set(nfc, NFC_FLASH_CONFIG, CONFIG_16BIT);
	अन्यथा
		vf610_nfc_clear(nfc, NFC_FLASH_CONFIG, CONFIG_16BIT);

	अगर (nfc->chip.ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST) अणु
		/* Set ECC status offset in SRAM */
		vf610_nfc_set_field(nfc, NFC_FLASH_CONFIG,
				    CONFIG_ECC_SRAM_ADDR_MASK,
				    CONFIG_ECC_SRAM_ADDR_SHIFT,
				    ECC_SRAM_ADDR >> 3);

		/* Enable ECC status in SRAM */
		vf610_nfc_set(nfc, NFC_FLASH_CONFIG, CONFIG_ECC_SRAM_REQ_BIT);
	पूर्ण
पूर्ण

अटल पूर्णांक vf610_nfc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा vf610_nfc *nfc = chip_to_nfc(chip);

	vf610_nfc_init_controller(nfc);

	/* Bad block options. */
	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH)
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;

	/* Single buffer only, max 256 OOB minus ECC status */
	अगर (mtd->ग_लिखोsize + mtd->oobsize > PAGE_2K + OOB_MAX - 8) अणु
		dev_err(nfc->dev, "Unsupported flash page size\n");
		वापस -ENXIO;
	पूर्ण

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	अगर (mtd->ग_लिखोsize != PAGE_2K && mtd->oobsize < 64) अणु
		dev_err(nfc->dev, "Unsupported flash with hwecc\n");
		वापस -ENXIO;
	पूर्ण

	अगर (chip->ecc.size != mtd->ग_लिखोsize) अणु
		dev_err(nfc->dev, "Step size needs to be page size\n");
		वापस -ENXIO;
	पूर्ण

	/* Only 64 byte ECC layouts known */
	अगर (mtd->oobsize > 64)
		mtd->oobsize = 64;

	/* Use शेष large page ECC layout defined in न_अंकD core */
	mtd_set_ooblayout(mtd, nand_get_large_page_ooblayout());
	अगर (chip->ecc.strength == 32) अणु
		nfc->ecc_mode = ECC_60_BYTE;
		chip->ecc.bytes = 60;
	पूर्ण अन्यथा अगर (chip->ecc.strength == 24) अणु
		nfc->ecc_mode = ECC_45_BYTE;
		chip->ecc.bytes = 45;
	पूर्ण अन्यथा अणु
		dev_err(nfc->dev, "Unsupported ECC strength\n");
		वापस -ENXIO;
	पूर्ण

	chip->ecc.पढ़ो_page = vf610_nfc_पढ़ो_page;
	chip->ecc.ग_लिखो_page = vf610_nfc_ग_लिखो_page;
	chip->ecc.पढ़ो_page_raw = vf610_nfc_पढ़ो_page_raw;
	chip->ecc.ग_लिखो_page_raw = vf610_nfc_ग_लिखो_page_raw;
	chip->ecc.पढ़ो_oob = vf610_nfc_पढ़ो_oob;
	chip->ecc.ग_लिखो_oob = vf610_nfc_ग_लिखो_oob;

	chip->ecc.size = PAGE_2K;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops vf610_nfc_controller_ops = अणु
	.attach_chip = vf610_nfc_attach_chip,
	.exec_op = vf610_nfc_exec_op,

पूर्ण;

अटल पूर्णांक vf610_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vf610_nfc *nfc;
	काष्ठा resource *res;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *chip;
	काष्ठा device_node *child;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक err;
	पूर्णांक irq;

	nfc = devm_kzalloc(&pdev->dev, माप(*nfc), GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nfc->dev = &pdev->dev;
	chip = &nfc->chip;
	mtd = nand_to_mtd(chip);

	mtd->owner = THIS_MODULE;
	mtd->dev.parent = nfc->dev;
	mtd->name = DRV_NAME;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	nfc->regs = devm_ioremap_resource(nfc->dev, res);
	अगर (IS_ERR(nfc->regs))
		वापस PTR_ERR(nfc->regs);

	nfc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(nfc->clk))
		वापस PTR_ERR(nfc->clk);

	err = clk_prepare_enable(nfc->clk);
	अगर (err) अणु
		dev_err(nfc->dev, "Unable to enable clock!\n");
		वापस err;
	पूर्ण

	of_id = of_match_device(vf610_nfc_dt_ids, &pdev->dev);
	अगर (!of_id) अणु
		err = -ENODEV;
		जाओ err_disable_clk;
	पूर्ण

	nfc->variant = (क्रमागत vf610_nfc_variant)of_id->data;

	क्रम_each_available_child_of_node(nfc->dev->of_node, child) अणु
		अगर (of_device_is_compatible(child, "fsl,vf610-nfc-nandcs")) अणु

			अगर (nand_get_flash_node(chip)) अणु
				dev_err(nfc->dev,
					"Only one NAND chip supported!\n");
				err = -EINVAL;
				of_node_put(child);
				जाओ err_disable_clk;
			पूर्ण

			nand_set_flash_node(chip, child);
		पूर्ण
	पूर्ण

	अगर (!nand_get_flash_node(chip)) अणु
		dev_err(nfc->dev, "NAND chip sub-node missing!\n");
		err = -ENODEV;
		जाओ err_disable_clk;
	पूर्ण

	chip->options |= न_अंकD_NO_SUBPAGE_WRITE;

	init_completion(&nfc->cmd_करोne);

	err = devm_request_irq(nfc->dev, irq, vf610_nfc_irq, 0, DRV_NAME, nfc);
	अगर (err) अणु
		dev_err(nfc->dev, "Error requesting IRQ!\n");
		जाओ err_disable_clk;
	पूर्ण

	vf610_nfc_preinit_controller(nfc);

	nand_controller_init(&nfc->base);
	nfc->base.ops = &vf610_nfc_controller_ops;
	chip->controller = &nfc->base;

	/* Scan the न_अंकD chip */
	err = nand_scan(chip, 1);
	अगर (err)
		जाओ err_disable_clk;

	platक्रमm_set_drvdata(pdev, nfc);

	/* Register device in MTD */
	err = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (err)
		जाओ err_cleanup_nand;
	वापस 0;

err_cleanup_nand:
	nand_cleanup(chip);
err_disable_clk:
	clk_disable_unprepare(nfc->clk);
	वापस err;
पूर्ण

अटल पूर्णांक vf610_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vf610_nfc *nfc = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &nfc->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);
	clk_disable_unprepare(nfc->clk);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक vf610_nfc_suspend(काष्ठा device *dev)
अणु
	काष्ठा vf610_nfc *nfc = dev_get_drvdata(dev);

	clk_disable_unprepare(nfc->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक vf610_nfc_resume(काष्ठा device *dev)
अणु
	काष्ठा vf610_nfc *nfc = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_prepare_enable(nfc->clk);
	अगर (err)
		वापस err;

	vf610_nfc_preinit_controller(nfc);
	vf610_nfc_init_controller(nfc);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(vf610_nfc_pm_ops, vf610_nfc_suspend, vf610_nfc_resume);

अटल काष्ठा platक्रमm_driver vf610_nfc_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = vf610_nfc_dt_ids,
		.pm	= &vf610_nfc_pm_ops,
	पूर्ण,
	.probe		= vf610_nfc_probe,
	.हटाओ		= vf610_nfc_हटाओ,
पूर्ण;

module_platक्रमm_driver(vf610_nfc_driver);

MODULE_AUTHOR("Stefan Agner <stefan.agner@toradex.com>");
MODULE_DESCRIPTION("Freescale VF610/MPC5125 NFC MTD NAND driver");
MODULE_LICENSE("GPL");
