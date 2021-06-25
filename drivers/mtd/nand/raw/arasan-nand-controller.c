<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Arasan न_अंकD Flash Controller Driver
 *
 * Copyright (C) 2014 - 2020 Xilinx, Inc.
 * Author:
 *   Miquel Raynal <miquel.raynal@bootlin.com>
 * Original work (fully rewritten):
 *   Punnaiah Choudary Kalluri <punnaia@xilinx.com>
 *   Naga Sureshkumar Relli <nagasure@xilinx.com>
 */

#समावेश <linux/bch.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा PKT_REG				0x00
#घोषणा   PKT_SIZE(x)			FIELD_PREP(GENMASK(10, 0), (x))
#घोषणा   PKT_STEPS(x)			FIELD_PREP(GENMASK(23, 12), (x))

#घोषणा MEM_ADDR1_REG			0x04

#घोषणा MEM_ADDR2_REG			0x08
#घोषणा   ADDR2_STRENGTH(x)		FIELD_PREP(GENMASK(27, 25), (x))
#घोषणा   ADDR2_CS(x)			FIELD_PREP(GENMASK(31, 30), (x))

#घोषणा CMD_REG				0x0C
#घोषणा   CMD_1(x)			FIELD_PREP(GENMASK(7, 0), (x))
#घोषणा   CMD_2(x)			FIELD_PREP(GENMASK(15, 8), (x))
#घोषणा   CMD_PAGE_SIZE(x)		FIELD_PREP(GENMASK(25, 23), (x))
#घोषणा   CMD_DMA_ENABLE		BIT(27)
#घोषणा   CMD_NADDRS(x)			FIELD_PREP(GENMASK(30, 28), (x))
#घोषणा   CMD_ECC_ENABLE		BIT(31)

#घोषणा PROG_REG			0x10
#घोषणा   PROG_PGRD			BIT(0)
#घोषणा   PROG_ERASE			BIT(2)
#घोषणा   PROG_STATUS			BIT(3)
#घोषणा   PROG_PGPROG			BIT(4)
#घोषणा   PROG_RDID			BIT(6)
#घोषणा   PROG_RDPARAM			BIT(7)
#घोषणा   PROG_RST			BIT(8)
#घोषणा   PROG_GET_FEATURE		BIT(9)
#घोषणा   PROG_SET_FEATURE		BIT(10)

#घोषणा INTR_STS_EN_REG			0x14
#घोषणा INTR_SIG_EN_REG			0x18
#घोषणा INTR_STS_REG			0x1C
#घोषणा   WRITE_READY			BIT(0)
#घोषणा   READ_READY			BIT(1)
#घोषणा   XFER_COMPLETE			BIT(2)
#घोषणा   DMA_BOUNDARY			BIT(6)
#घोषणा   EVENT_MASK			GENMASK(7, 0)

#घोषणा READY_STS_REG			0x20

#घोषणा DMA_ADDR0_REG			0x50
#घोषणा DMA_ADDR1_REG			0x24

#घोषणा FLASH_STS_REG			0x28

#घोषणा DATA_PORT_REG			0x30

#घोषणा ECC_CONF_REG			0x34
#घोषणा   ECC_CONF_COL(x)		FIELD_PREP(GENMASK(15, 0), (x))
#घोषणा   ECC_CONF_LEN(x)		FIELD_PREP(GENMASK(26, 16), (x))
#घोषणा   ECC_CONF_BCH_EN		BIT(27)

#घोषणा ECC_ERR_CNT_REG			0x38
#घोषणा   GET_PKT_ERR_CNT(x)		FIELD_GET(GENMASK(7, 0), (x))
#घोषणा   GET_PAGE_ERR_CNT(x)		FIELD_GET(GENMASK(16, 8), (x))

#घोषणा ECC_SP_REG			0x3C
#घोषणा   ECC_SP_CMD1(x)		FIELD_PREP(GENMASK(7, 0), (x))
#घोषणा   ECC_SP_CMD2(x)		FIELD_PREP(GENMASK(15, 8), (x))
#घोषणा   ECC_SP_ADDRS(x)		FIELD_PREP(GENMASK(30, 28), (x))

#घोषणा ECC_1ERR_CNT_REG		0x40
#घोषणा ECC_2ERR_CNT_REG		0x44

#घोषणा DATA_INTERFACE_REG		0x6C
#घोषणा   DIFACE_SDR_MODE(x)		FIELD_PREP(GENMASK(2, 0), (x))
#घोषणा   DIFACE_DDR_MODE(x)		FIELD_PREP(GENMASK(5, 3), (X))
#घोषणा   DIFACE_SDR			0
#घोषणा   DIFACE_NVDDR			BIT(9)

#घोषणा ANFC_MAX_CS			2
#घोषणा ANFC_DFLT_TIMEOUT_US		1000000
#घोषणा ANFC_MAX_CHUNK_SIZE		SZ_1M
#घोषणा ANFC_MAX_PARAM_SIZE		SZ_4K
#घोषणा ANFC_MAX_STEPS			SZ_2K
#घोषणा ANFC_MAX_PKT_SIZE		(SZ_2K - 1)
#घोषणा ANFC_MAX_ADDR_CYC		5U
#घोषणा ANFC_RSVD_ECC_BYTES		21

#घोषणा ANFC_XLNX_SDR_DFLT_CORE_CLK	100000000
#घोषणा ANFC_XLNX_SDR_HS_CORE_CLK	80000000

/**
 * काष्ठा anfc_op - Defines how to execute an operation
 * @pkt_reg: Packet रेजिस्टर
 * @addr1_reg: Memory address 1 रेजिस्टर
 * @addr2_reg: Memory address 2 रेजिस्टर
 * @cmd_reg: Command रेजिस्टर
 * @prog_reg: Program रेजिस्टर
 * @steps: Number of "packets" to पढ़ो/ग_लिखो
 * @rdy_समयout_ms: Timeout क्रम रुकोs on Ready/Busy pin
 * @len: Data transfer length
 * @पढ़ो: Data transfer direction from the controller poपूर्णांक of view
 * @buf: Data buffer
 */
काष्ठा anfc_op अणु
	u32 pkt_reg;
	u32 addr1_reg;
	u32 addr2_reg;
	u32 cmd_reg;
	u32 prog_reg;
	पूर्णांक steps;
	अचिन्हित पूर्णांक rdy_समयout_ms;
	अचिन्हित पूर्णांक len;
	bool पढ़ो;
	u8 *buf;
पूर्ण;

/**
 * काष्ठा anand - Defines the न_अंकD chip related inक्रमmation
 * @node:		Used to store न_अंकD chips पूर्णांकo a list
 * @chip:		न_अंकD chip inक्रमmation काष्ठाure
 * @cs:			Chip select line
 * @rb:			Ready-busy line
 * @page_sz:		Register value of the page_sz field to use
 * @clk:		Expected घड़ी frequency to use
 * @timings:		Data पूर्णांकerface timing mode to use
 * @ecc_conf:		Hardware ECC configuration value
 * @strength:		Register value of the ECC strength
 * @raddr_cycles:	Row address cycle inक्रमmation
 * @caddr_cycles:	Column address cycle inक्रमmation
 * @ecc_bits:		Exact number of ECC bits per syndrome
 * @ecc_total:		Total number of ECC bytes
 * @errloc:		Array of errors located with soft BCH
 * @hw_ecc:		Buffer to store syndromes computed by hardware
 * @bch:		BCH काष्ठाure
 */
काष्ठा anand अणु
	काष्ठा list_head node;
	काष्ठा nand_chip chip;
	अचिन्हित पूर्णांक cs;
	अचिन्हित पूर्णांक rb;
	अचिन्हित पूर्णांक page_sz;
	अचिन्हित दीर्घ clk;
	u32 timings;
	u32 ecc_conf;
	u32 strength;
	u16 raddr_cycles;
	u16 caddr_cycles;
	अचिन्हित पूर्णांक ecc_bits;
	अचिन्हित पूर्णांक ecc_total;
	अचिन्हित पूर्णांक *errloc;
	u8 *hw_ecc;
	काष्ठा bch_control *bch;
पूर्ण;

/**
 * काष्ठा arasan_nfc - Defines the Arasan न_अंकD flash controller driver instance
 * @dev:		Poपूर्णांकer to the device काष्ठाure
 * @base:		Remapped रेजिस्टर area
 * @controller_clk:		Poपूर्णांकer to the प्रणाली घड़ी
 * @bus_clk:		Poपूर्णांकer to the flash घड़ी
 * @controller:		Base controller काष्ठाure
 * @chips:		List of all न_अंकD chips attached to the controller
 * @asचिन्हित_cs:	Biपंचांगask describing alपढ़ोy asचिन्हित CS lines
 * @cur_clk:		Current घड़ी rate
 */
काष्ठा arasan_nfc अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *controller_clk;
	काष्ठा clk *bus_clk;
	काष्ठा nand_controller controller;
	काष्ठा list_head chips;
	अचिन्हित दीर्घ asचिन्हित_cs;
	अचिन्हित पूर्णांक cur_clk;
पूर्ण;

अटल काष्ठा anand *to_anand(काष्ठा nand_chip *nand)
अणु
	वापस container_of(nand, काष्ठा anand, chip);
पूर्ण

अटल काष्ठा arasan_nfc *to_anfc(काष्ठा nand_controller *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा arasan_nfc, controller);
पूर्ण

अटल पूर्णांक anfc_रुको_क्रम_event(काष्ठा arasan_nfc *nfc, अचिन्हित पूर्णांक event)
अणु
	u32 val;
	पूर्णांक ret;

	ret = पढ़ोl_relaxed_poll_समयout(nfc->base + INTR_STS_REG, val,
					 val & event, 0,
					 ANFC_DFLT_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(nfc->dev, "Timeout waiting for event 0x%x\n", event);
		वापस -ETIMEDOUT;
	पूर्ण

	ग_लिखोl_relaxed(event, nfc->base + INTR_STS_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक anfc_रुको_क्रम_rb(काष्ठा arasan_nfc *nfc, काष्ठा nand_chip *chip,
			    अचिन्हित पूर्णांक समयout_ms)
अणु
	काष्ठा anand *anand = to_anand(chip);
	u32 val;
	पूर्णांक ret;

	/* There is no R/B पूर्णांकerrupt, we must poll a रेजिस्टर */
	ret = पढ़ोl_relaxed_poll_समयout(nfc->base + READY_STS_REG, val,
					 val & BIT(anand->rb),
					 1, समयout_ms * 1000);
	अगर (ret) अणु
		dev_err(nfc->dev, "Timeout waiting for R/B 0x%x\n",
			पढ़ोl_relaxed(nfc->base + READY_STS_REG));
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम anfc_trigger_op(काष्ठा arasan_nfc *nfc, काष्ठा anfc_op *nfc_op)
अणु
	ग_लिखोl_relaxed(nfc_op->pkt_reg, nfc->base + PKT_REG);
	ग_लिखोl_relaxed(nfc_op->addr1_reg, nfc->base + MEM_ADDR1_REG);
	ग_लिखोl_relaxed(nfc_op->addr2_reg, nfc->base + MEM_ADDR2_REG);
	ग_लिखोl_relaxed(nfc_op->cmd_reg, nfc->base + CMD_REG);
	ग_लिखोl_relaxed(nfc_op->prog_reg, nfc->base + PROG_REG);
पूर्ण

अटल पूर्णांक anfc_pkt_len_config(अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक *steps,
			       अचिन्हित पूर्णांक *pktsize)
अणु
	अचिन्हित पूर्णांक nb, sz;

	क्रम (nb = 1; nb < ANFC_MAX_STEPS; nb *= 2) अणु
		sz = len / nb;
		अगर (sz <= ANFC_MAX_PKT_SIZE)
			अवरोध;
	पूर्ण

	अगर (sz * nb != len)
		वापस -ENOTSUPP;

	अगर (steps)
		*steps = nb;

	अगर (pktsize)
		*pktsize = sz;

	वापस 0;
पूर्ण

/*
 * When using the embedded hardware ECC engine, the controller is in अक्षरge of
 * feeding the engine with, first, the ECC residue present in the data array.
 * A typical पढ़ो operation is:
 * 1/ Assert the पढ़ो operation by sending the relevant command/address cycles
 *    but targeting the column of the first ECC bytes in the OOB area instead of
 *    the मुख्य data directly.
 * 2/ After having पढ़ो the relevant number of ECC bytes, the controller uses
 *    the RNDOUT/RNDSTART commands which are set पूर्णांकo the "ECC Spare Command
 *    Register" to move the poपूर्णांकer back at the beginning of the मुख्य data.
 * 3/ It will पढ़ो the content of the मुख्य area क्रम a given size (pktsize) and
 *    will feed the ECC engine with this buffer again.
 * 4/ The ECC engine derives the ECC bytes क्रम the given data and compare them
 *    with the ones alपढ़ोy received. It eventually trigger status flags and
 *    then set the "Buffer Read Ready" flag.
 * 5/ The corrected data is then available क्रम पढ़ोing from the data port
 *    रेजिस्टर.
 *
 * The hardware BCH ECC engine is known to be inस्थिरent in BCH mode and never
 * reports uncorrectable errors. Because of this bug, we have to use the
 * software BCH implementation in the पढ़ो path.
 */
अटल पूर्णांक anfc_पढ़ो_page_hw_ecc(काष्ठा nand_chip *chip, u8 *buf,
				 पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा anand *anand = to_anand(chip);
	अचिन्हित पूर्णांक len = mtd->ग_लिखोsize + (oob_required ? mtd->oobsize : 0);
	अचिन्हित पूर्णांक max_bitflips = 0;
	dma_addr_t dma_addr;
	पूर्णांक step, ret;
	काष्ठा anfc_op nfc_op = अणु
		.pkt_reg =
			PKT_SIZE(chip->ecc.size) |
			PKT_STEPS(chip->ecc.steps),
		.addr1_reg =
			(page & 0xFF) << (8 * (anand->caddr_cycles)) |
			(((page >> 8) & 0xFF) << (8 * (1 + anand->caddr_cycles))),
		.addr2_reg =
			((page >> 16) & 0xFF) |
			ADDR2_STRENGTH(anand->strength) |
			ADDR2_CS(anand->cs),
		.cmd_reg =
			CMD_1(न_अंकD_CMD_READ0) |
			CMD_2(न_अंकD_CMD_READSTART) |
			CMD_PAGE_SIZE(anand->page_sz) |
			CMD_DMA_ENABLE |
			CMD_NADDRS(anand->caddr_cycles +
				   anand->raddr_cycles),
		.prog_reg = PROG_PGRD,
	पूर्ण;

	dma_addr = dma_map_single(nfc->dev, (व्योम *)buf, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(nfc->dev, dma_addr)) अणु
		dev_err(nfc->dev, "Buffer mapping error");
		वापस -EIO;
	पूर्ण

	ग_लिखोl_relaxed(lower_32_bits(dma_addr), nfc->base + DMA_ADDR0_REG);
	ग_लिखोl_relaxed(upper_32_bits(dma_addr), nfc->base + DMA_ADDR1_REG);

	anfc_trigger_op(nfc, &nfc_op);

	ret = anfc_रुको_क्रम_event(nfc, XFER_COMPLETE);
	dma_unmap_single(nfc->dev, dma_addr, len, DMA_FROM_DEVICE);
	अगर (ret) अणु
		dev_err(nfc->dev, "Error reading page %d\n", page);
		वापस ret;
	पूर्ण

	/* Store the raw OOB bytes as well */
	ret = nand_change_पढ़ो_column_op(chip, mtd->ग_लिखोsize, chip->oob_poi,
					 mtd->oobsize, 0);
	अगर (ret)
		वापस ret;

	/*
	 * For each step, compute by softare the BCH syndrome over the raw data.
	 * Compare the theoretical amount of errors and compare with the
	 * hardware engine feedback.
	 */
	क्रम (step = 0; step < chip->ecc.steps; step++) अणु
		u8 *raw_buf = &buf[step * chip->ecc.size];
		अचिन्हित पूर्णांक bit, byte;
		पूर्णांक bf, i;

		/* Extract the syndrome, it is not necessarily aligned */
		स_रखो(anand->hw_ecc, 0, chip->ecc.bytes);
		nand_extract_bits(anand->hw_ecc, 0,
				  &chip->oob_poi[mtd->oobsize - anand->ecc_total],
				  anand->ecc_bits * step, anand->ecc_bits);

		bf = bch_decode(anand->bch, raw_buf, chip->ecc.size,
				anand->hw_ecc, शून्य, शून्य, anand->errloc);
		अगर (!bf) अणु
			जारी;
		पूर्ण अन्यथा अगर (bf > 0) अणु
			क्रम (i = 0; i < bf; i++) अणु
				/* Only correct the data, not the syndrome */
				अगर (anand->errloc[i] < (chip->ecc.size * 8)) अणु
					bit = BIT(anand->errloc[i] & 7);
					byte = anand->errloc[i] >> 3;
					raw_buf[byte] ^= bit;
				पूर्ण
			पूर्ण

			mtd->ecc_stats.corrected += bf;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, bf);

			जारी;
		पूर्ण

		bf = nand_check_erased_ecc_chunk(raw_buf, chip->ecc.size,
						 शून्य, 0, शून्य, 0,
						 chip->ecc.strength);
		अगर (bf > 0) अणु
			mtd->ecc_stats.corrected += bf;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, bf);
			स_रखो(raw_buf, 0xFF, chip->ecc.size);
		पूर्ण अन्यथा अगर (bf < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक anfc_ग_लिखो_page_hw_ecc(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा anand *anand = to_anand(chip);
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित पूर्णांक len = mtd->ग_लिखोsize + (oob_required ? mtd->oobsize : 0);
	dma_addr_t dma_addr;
	पूर्णांक ret;
	काष्ठा anfc_op nfc_op = अणु
		.pkt_reg =
			PKT_SIZE(chip->ecc.size) |
			PKT_STEPS(chip->ecc.steps),
		.addr1_reg =
			(page & 0xFF) << (8 * (anand->caddr_cycles)) |
			(((page >> 8) & 0xFF) << (8 * (1 + anand->caddr_cycles))),
		.addr2_reg =
			((page >> 16) & 0xFF) |
			ADDR2_STRENGTH(anand->strength) |
			ADDR2_CS(anand->cs),
		.cmd_reg =
			CMD_1(न_अंकD_CMD_SEQIN) |
			CMD_2(न_अंकD_CMD_PAGEPROG) |
			CMD_PAGE_SIZE(anand->page_sz) |
			CMD_DMA_ENABLE |
			CMD_NADDRS(anand->caddr_cycles +
				   anand->raddr_cycles) |
			CMD_ECC_ENABLE,
		.prog_reg = PROG_PGPROG,
	पूर्ण;

	ग_लिखोl_relaxed(anand->ecc_conf, nfc->base + ECC_CONF_REG);
	ग_लिखोl_relaxed(ECC_SP_CMD1(न_अंकD_CMD_RNDIN) |
		       ECC_SP_ADDRS(anand->caddr_cycles),
		       nfc->base + ECC_SP_REG);

	dma_addr = dma_map_single(nfc->dev, (व्योम *)buf, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(nfc->dev, dma_addr)) अणु
		dev_err(nfc->dev, "Buffer mapping error");
		वापस -EIO;
	पूर्ण

	ग_लिखोl_relaxed(lower_32_bits(dma_addr), nfc->base + DMA_ADDR0_REG);
	ग_लिखोl_relaxed(upper_32_bits(dma_addr), nfc->base + DMA_ADDR1_REG);

	anfc_trigger_op(nfc, &nfc_op);
	ret = anfc_रुको_क्रम_event(nfc, XFER_COMPLETE);
	dma_unmap_single(nfc->dev, dma_addr, len, DMA_TO_DEVICE);
	अगर (ret) अणु
		dev_err(nfc->dev, "Error writing page %d\n", page);
		वापस ret;
	पूर्ण

	/* Spare data is not रक्षित */
	अगर (oob_required)
		ret = nand_ग_लिखो_oob_std(chip, page);

	वापस ret;
पूर्ण

/* न_अंकD framework ->exec_op() hooks and related helpers */
अटल पूर्णांक anfc_parse_inकाष्ठाions(काष्ठा nand_chip *chip,
				   स्थिर काष्ठा nand_subop *subop,
				   काष्ठा anfc_op *nfc_op)
अणु
	काष्ठा anand *anand = to_anand(chip);
	स्थिर काष्ठा nand_op_instr *instr = शून्य;
	bool first_cmd = true;
	अचिन्हित पूर्णांक op_id;
	पूर्णांक ret, i;

	स_रखो(nfc_op, 0, माप(*nfc_op));
	nfc_op->addr2_reg = ADDR2_CS(anand->cs);
	nfc_op->cmd_reg = CMD_PAGE_SIZE(anand->page_sz);

	क्रम (op_id = 0; op_id < subop->ninstrs; op_id++) अणु
		अचिन्हित पूर्णांक offset, naddrs, pktsize;
		स्थिर u8 *addrs;
		u8 *buf;

		instr = &subop->instrs[op_id];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			अगर (first_cmd)
				nfc_op->cmd_reg |= CMD_1(instr->ctx.cmd.opcode);
			अन्यथा
				nfc_op->cmd_reg |= CMD_2(instr->ctx.cmd.opcode);

			first_cmd = false;
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			offset = nand_subop_get_addr_start_off(subop, op_id);
			naddrs = nand_subop_get_num_addr_cyc(subop, op_id);
			addrs = &instr->ctx.addr.addrs[offset];
			nfc_op->cmd_reg |= CMD_NADDRS(naddrs);

			क्रम (i = 0; i < min(ANFC_MAX_ADDR_CYC, naddrs); i++) अणु
				अगर (i < 4)
					nfc_op->addr1_reg |= (u32)addrs[i] << i * 8;
				अन्यथा
					nfc_op->addr2_reg |= addrs[i];
			पूर्ण

			अवरोध;
		हाल न_अंकD_OP_DATA_IN_INSTR:
			nfc_op->पढ़ो = true;
			fallthrough;
		हाल न_अंकD_OP_DATA_OUT_INSTR:
			offset = nand_subop_get_data_start_off(subop, op_id);
			buf = instr->ctx.data.buf.in;
			nfc_op->buf = &buf[offset];
			nfc_op->len = nand_subop_get_data_len(subop, op_id);
			ret = anfc_pkt_len_config(nfc_op->len, &nfc_op->steps,
						  &pktsize);
			अगर (ret)
				वापस ret;

			/*
			 * Number of DATA cycles must be aligned on 4, this
			 * means the controller might पढ़ो/ग_लिखो more than
			 * requested. This is harmless most of the समय as extra
			 * DATA are discarded in the ग_लिखो path and पढ़ो poपूर्णांकer
			 * adjusted in the पढ़ो path.
			 *
			 * FIXME: The core should mark operations where
			 * पढ़ोing/writing more is allowed so the exec_op()
			 * implementation can take the right decision when the
			 * alignment स्थिरraपूर्णांक is not met: adjust the number of
			 * DATA cycles when it's allowed, reject the operation
			 * otherwise.
			 */
			nfc_op->pkt_reg |= PKT_SIZE(round_up(pktsize, 4)) |
					   PKT_STEPS(nfc_op->steps);
			अवरोध;
		हाल न_अंकD_OP_WAITRDY_INSTR:
			nfc_op->rdy_समयout_ms = instr->ctx.रुकोrdy.समयout_ms;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक anfc_rw_pio_op(काष्ठा arasan_nfc *nfc, काष्ठा anfc_op *nfc_op)
अणु
	अचिन्हित पूर्णांक dwords = (nfc_op->len / 4) / nfc_op->steps;
	अचिन्हित पूर्णांक last_len = nfc_op->len % 4;
	अचिन्हित पूर्णांक offset, dir;
	u8 *buf = nfc_op->buf;
	पूर्णांक ret, i;

	क्रम (i = 0; i < nfc_op->steps; i++) अणु
		dir = nfc_op->पढ़ो ? READ_READY : WRITE_READY;
		ret = anfc_रुको_क्रम_event(nfc, dir);
		अगर (ret) अणु
			dev_err(nfc->dev, "PIO %s ready signal not received\n",
				nfc_op->पढ़ो ? "Read" : "Write");
			वापस ret;
		पूर्ण

		offset = i * (dwords * 4);
		अगर (nfc_op->पढ़ो)
			ioपढ़ो32_rep(nfc->base + DATA_PORT_REG, &buf[offset],
				     dwords);
		अन्यथा
			ioग_लिखो32_rep(nfc->base + DATA_PORT_REG, &buf[offset],
				      dwords);
	पूर्ण

	अगर (last_len) अणु
		u32 reमुख्यder;

		offset = nfc_op->len - last_len;

		अगर (nfc_op->पढ़ो) अणु
			reमुख्यder = पढ़ोl_relaxed(nfc->base + DATA_PORT_REG);
			स_नकल(&buf[offset], &reमुख्यder, last_len);
		पूर्ण अन्यथा अणु
			स_नकल(&reमुख्यder, &buf[offset], last_len);
			ग_लिखोl_relaxed(reमुख्यder, nfc->base + DATA_PORT_REG);
		पूर्ण
	पूर्ण

	वापस anfc_रुको_क्रम_event(nfc, XFER_COMPLETE);
पूर्ण

अटल पूर्णांक anfc_misc_data_type_exec(काष्ठा nand_chip *chip,
				    स्थिर काष्ठा nand_subop *subop,
				    u32 prog_reg)
अणु
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	काष्ठा anfc_op nfc_op = अणुपूर्ण;
	पूर्णांक ret;

	ret = anfc_parse_inकाष्ठाions(chip, subop, &nfc_op);
	अगर (ret)
		वापस ret;

	nfc_op.prog_reg = prog_reg;
	anfc_trigger_op(nfc, &nfc_op);

	अगर (nfc_op.rdy_समयout_ms) अणु
		ret = anfc_रुको_क्रम_rb(nfc, chip, nfc_op.rdy_समयout_ms);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस anfc_rw_pio_op(nfc, &nfc_op);
पूर्ण

अटल पूर्णांक anfc_param_पढ़ो_type_exec(काष्ठा nand_chip *chip,
				     स्थिर काष्ठा nand_subop *subop)
अणु
	वापस anfc_misc_data_type_exec(chip, subop, PROG_RDPARAM);
पूर्ण

अटल पूर्णांक anfc_data_पढ़ो_type_exec(काष्ठा nand_chip *chip,
				    स्थिर काष्ठा nand_subop *subop)
अणु
	वापस anfc_misc_data_type_exec(chip, subop, PROG_PGRD);
पूर्ण

अटल पूर्णांक anfc_param_ग_लिखो_type_exec(काष्ठा nand_chip *chip,
				      स्थिर काष्ठा nand_subop *subop)
अणु
	वापस anfc_misc_data_type_exec(chip, subop, PROG_SET_FEATURE);
पूर्ण

अटल पूर्णांक anfc_data_ग_लिखो_type_exec(काष्ठा nand_chip *chip,
				     स्थिर काष्ठा nand_subop *subop)
अणु
	वापस anfc_misc_data_type_exec(chip, subop, PROG_PGPROG);
पूर्ण

अटल पूर्णांक anfc_misc_zerolen_type_exec(काष्ठा nand_chip *chip,
				       स्थिर काष्ठा nand_subop *subop,
				       u32 prog_reg)
अणु
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	काष्ठा anfc_op nfc_op = अणुपूर्ण;
	पूर्णांक ret;

	ret = anfc_parse_inकाष्ठाions(chip, subop, &nfc_op);
	अगर (ret)
		वापस ret;

	nfc_op.prog_reg = prog_reg;
	anfc_trigger_op(nfc, &nfc_op);

	ret = anfc_रुको_क्रम_event(nfc, XFER_COMPLETE);
	अगर (ret)
		वापस ret;

	अगर (nfc_op.rdy_समयout_ms)
		ret = anfc_रुको_क्रम_rb(nfc, chip, nfc_op.rdy_समयout_ms);

	वापस ret;
पूर्ण

अटल पूर्णांक anfc_status_type_exec(काष्ठा nand_chip *chip,
				 स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	u32 पंचांगp;
	पूर्णांक ret;

	/* See anfc_check_op() क्रम details about this स्थिरraपूर्णांक */
	अगर (subop->instrs[0].ctx.cmd.opcode != न_अंकD_CMD_STATUS)
		वापस -ENOTSUPP;

	ret = anfc_misc_zerolen_type_exec(chip, subop, PROG_STATUS);
	अगर (ret)
		वापस ret;

	पंचांगp = पढ़ोl_relaxed(nfc->base + FLASH_STS_REG);
	स_नकल(subop->instrs[1].ctx.data.buf.in, &पंचांगp, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक anfc_reset_type_exec(काष्ठा nand_chip *chip,
				स्थिर काष्ठा nand_subop *subop)
अणु
	वापस anfc_misc_zerolen_type_exec(chip, subop, PROG_RST);
पूर्ण

अटल पूर्णांक anfc_erase_type_exec(काष्ठा nand_chip *chip,
				स्थिर काष्ठा nand_subop *subop)
अणु
	वापस anfc_misc_zerolen_type_exec(chip, subop, PROG_ERASE);
पूर्ण

अटल पूर्णांक anfc_रुको_type_exec(काष्ठा nand_chip *chip,
			       स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	काष्ठा anfc_op nfc_op = अणुपूर्ण;
	पूर्णांक ret;

	ret = anfc_parse_inकाष्ठाions(chip, subop, &nfc_op);
	अगर (ret)
		वापस ret;

	वापस anfc_रुको_क्रम_rb(nfc, chip, nfc_op.rdy_समयout_ms);
पूर्ण

अटल स्थिर काष्ठा nand_op_parser anfc_op_parser = न_अंकD_OP_PARSER(
	न_अंकD_OP_PARSER_PATTERN(
		anfc_param_पढ़ो_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, ANFC_MAX_ADDR_CYC),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(false, ANFC_MAX_CHUNK_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		anfc_param_ग_लिखो_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, ANFC_MAX_ADDR_CYC),
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(false, ANFC_MAX_PARAM_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		anfc_data_पढ़ो_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, ANFC_MAX_ADDR_CYC),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(true, ANFC_MAX_CHUNK_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		anfc_data_ग_लिखो_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, ANFC_MAX_ADDR_CYC),
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(false, ANFC_MAX_CHUNK_SIZE),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false)),
	न_अंकD_OP_PARSER_PATTERN(
		anfc_reset_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
	न_अंकD_OP_PARSER_PATTERN(
		anfc_erase_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, ANFC_MAX_ADDR_CYC),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
	न_अंकD_OP_PARSER_PATTERN(
		anfc_status_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(false, ANFC_MAX_CHUNK_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		anfc_रुको_type_exec,
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
	);

अटल पूर्णांक anfc_select_target(काष्ठा nand_chip *chip, पूर्णांक target)
अणु
	काष्ठा anand *anand = to_anand(chip);
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	पूर्णांक ret;

	/* Update the controller timings and the potential ECC configuration */
	ग_लिखोl_relaxed(anand->timings, nfc->base + DATA_INTERFACE_REG);

	/* Update घड़ी frequency */
	अगर (nfc->cur_clk != anand->clk) अणु
		clk_disable_unprepare(nfc->controller_clk);
		ret = clk_set_rate(nfc->controller_clk, anand->clk);
		अगर (ret) अणु
			dev_err(nfc->dev, "Failed to change clock rate\n");
			वापस ret;
		पूर्ण

		ret = clk_prepare_enable(nfc->controller_clk);
		अगर (ret) अणु
			dev_err(nfc->dev,
				"Failed to re-enable the controller clock\n");
			वापस ret;
		पूर्ण

		nfc->cur_clk = anand->clk;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक anfc_check_op(काष्ठा nand_chip *chip,
			 स्थिर काष्ठा nand_operation *op)
अणु
	स्थिर काष्ठा nand_op_instr *instr;
	पूर्णांक op_id;

	/*
	 * The controller असलtracts all the न_अंकD operations and करो not support
	 * data only operations.
	 *
	 * TODO: The nand_op_parser framework should be extended to
	 * support custom checks on DATA inकाष्ठाions.
	 */
	क्रम (op_id = 0; op_id < op->ninstrs; op_id++) अणु
		instr = &op->instrs[op_id];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_ADDR_INSTR:
			अगर (instr->ctx.addr.naddrs > ANFC_MAX_ADDR_CYC)
				वापस -ENOTSUPP;

			अवरोध;
		हाल न_अंकD_OP_DATA_IN_INSTR:
		हाल न_अंकD_OP_DATA_OUT_INSTR:
			अगर (instr->ctx.data.len > ANFC_MAX_CHUNK_SIZE)
				वापस -ENOTSUPP;

			अगर (anfc_pkt_len_config(instr->ctx.data.len, 0, 0))
				वापस -ENOTSUPP;

			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * The controller करोes not allow to proceed with a CMD+DATA_IN cycle
	 * manually on the bus by पढ़ोing data from the data रेजिस्टर. Instead,
	 * the controller असलtract a status पढ़ो operation with its own status
	 * रेजिस्टर after ordering a पढ़ो status operation. Hence, we cannot
	 * support any CMD+DATA_IN operation other than a READ STATUS.
	 *
	 * TODO: The nand_op_parser() framework should be extended to describe
	 * fixed patterns instead of खोलो-coding this check here.
	 */
	अगर (op->ninstrs == 2 &&
	    op->instrs[0].type == न_अंकD_OP_CMD_INSTR &&
	    op->instrs[0].ctx.cmd.opcode != न_अंकD_CMD_STATUS &&
	    op->instrs[1].type == न_अंकD_OP_DATA_IN_INSTR)
		वापस -ENOTSUPP;

	वापस nand_op_parser_exec_op(chip, &anfc_op_parser, op, true);
पूर्ण

अटल पूर्णांक anfc_exec_op(काष्ठा nand_chip *chip,
			स्थिर काष्ठा nand_operation *op,
			bool check_only)
अणु
	पूर्णांक ret;

	अगर (check_only)
		वापस anfc_check_op(chip, op);

	ret = anfc_select_target(chip, op->cs);
	अगर (ret)
		वापस ret;

	वापस nand_op_parser_exec_op(chip, &anfc_op_parser, op, check_only);
पूर्ण

अटल पूर्णांक anfc_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक target,
				स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा anand *anand = to_anand(chip);
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	काष्ठा device_node *np = nfc->dev->of_node;

	अगर (target < 0)
		वापस 0;

	anand->timings = DIFACE_SDR | DIFACE_SDR_MODE(conf->timings.mode);
	anand->clk = ANFC_XLNX_SDR_DFLT_CORE_CLK;

	/*
	 * Due to a hardware bug in the ZynqMP SoC, SDR timing modes 0-1 work
	 * with f > 90MHz (शेष घड़ी is 100MHz) but संकेतs are unstable
	 * with higher modes. Hence we decrease a little bit the घड़ी rate to
	 * 80MHz when using modes 2-5 with this SoC.
	 */
	अगर (of_device_is_compatible(np, "xlnx,zynqmp-nand-controller") &&
	    conf->timings.mode >= 2)
		anand->clk = ANFC_XLNX_SDR_HS_CORE_CLK;

	वापस 0;
पूर्ण

अटल पूर्णांक anfc_calc_hw_ecc_bytes(पूर्णांक step_size, पूर्णांक strength)
अणु
	अचिन्हित पूर्णांक bch_gf_mag, ecc_bits;

	चयन (step_size) अणु
	हाल SZ_512:
		bch_gf_mag = 13;
		अवरोध;
	हाल SZ_1K:
		bch_gf_mag = 14;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ecc_bits = bch_gf_mag * strength;

	वापस DIV_ROUND_UP(ecc_bits, 8);
पूर्ण

अटल स्थिर पूर्णांक anfc_hw_ecc_512_strengths[] = अणु4, 8, 12पूर्ण;

अटल स्थिर पूर्णांक anfc_hw_ecc_1024_strengths[] = अणु24पूर्ण;

अटल स्थिर काष्ठा nand_ecc_step_info anfc_hw_ecc_step_infos[] = अणु
	अणु
		.stepsize = SZ_512,
		.strengths = anfc_hw_ecc_512_strengths,
		.nstrengths = ARRAY_SIZE(anfc_hw_ecc_512_strengths),
	पूर्ण,
	अणु
		.stepsize = SZ_1K,
		.strengths = anfc_hw_ecc_1024_strengths,
		.nstrengths = ARRAY_SIZE(anfc_hw_ecc_1024_strengths),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nand_ecc_caps anfc_hw_ecc_caps = अणु
	.stepinfos = anfc_hw_ecc_step_infos,
	.nstepinfos = ARRAY_SIZE(anfc_hw_ecc_step_infos),
	.calc_ecc_bytes = anfc_calc_hw_ecc_bytes,
पूर्ण;

अटल पूर्णांक anfc_init_hw_ecc_controller(काष्ठा arasan_nfc *nfc,
				       काष्ठा nand_chip *chip)
अणु
	काष्ठा anand *anand = to_anand(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	अचिन्हित पूर्णांक bch_prim_poly = 0, bch_gf_mag = 0, ecc_offset;
	पूर्णांक ret;

	चयन (mtd->ग_लिखोsize) अणु
	हाल SZ_512:
	हाल SZ_2K:
	हाल SZ_4K:
	हाल SZ_8K:
	हाल SZ_16K:
		अवरोध;
	शेष:
		dev_err(nfc->dev, "Unsupported page size %d\n", mtd->ग_लिखोsize);
		वापस -EINVAL;
	पूर्ण

	ret = nand_ecc_choose_conf(chip, &anfc_hw_ecc_caps, mtd->oobsize);
	अगर (ret)
		वापस ret;

	चयन (ecc->strength) अणु
	हाल 12:
		anand->strength = 0x1;
		अवरोध;
	हाल 8:
		anand->strength = 0x2;
		अवरोध;
	हाल 4:
		anand->strength = 0x3;
		अवरोध;
	हाल 24:
		anand->strength = 0x4;
		अवरोध;
	शेष:
		dev_err(nfc->dev, "Unsupported strength %d\n", ecc->strength);
		वापस -EINVAL;
	पूर्ण

	चयन (ecc->size) अणु
	हाल SZ_512:
		bch_gf_mag = 13;
		bch_prim_poly = 0x201b;
		अवरोध;
	हाल SZ_1K:
		bch_gf_mag = 14;
		bch_prim_poly = 0x4443;
		अवरोध;
	शेष:
		dev_err(nfc->dev, "Unsupported step size %d\n", ecc->strength);
		वापस -EINVAL;
	पूर्ण

	mtd_set_ooblayout(mtd, nand_get_large_page_ooblayout());

	ecc->steps = mtd->ग_लिखोsize / ecc->size;
	ecc->algo = न_अंकD_ECC_ALGO_BCH;
	anand->ecc_bits = bch_gf_mag * ecc->strength;
	ecc->bytes = DIV_ROUND_UP(anand->ecc_bits, 8);
	anand->ecc_total = DIV_ROUND_UP(anand->ecc_bits * ecc->steps, 8);
	ecc_offset = mtd->ग_लिखोsize + mtd->oobsize - anand->ecc_total;
	anand->ecc_conf = ECC_CONF_COL(ecc_offset) |
			  ECC_CONF_LEN(anand->ecc_total) |
			  ECC_CONF_BCH_EN;

	anand->errloc = devm_kदो_स्मृति_array(nfc->dev, ecc->strength,
					   माप(*anand->errloc), GFP_KERNEL);
	अगर (!anand->errloc)
		वापस -ENOMEM;

	anand->hw_ecc = devm_kदो_स्मृति(nfc->dev, ecc->bytes, GFP_KERNEL);
	अगर (!anand->hw_ecc)
		वापस -ENOMEM;

	/* Enक्रमce bit swapping to fit the hardware */
	anand->bch = bch_init(bch_gf_mag, ecc->strength, bch_prim_poly, true);
	अगर (!anand->bch)
		वापस -EINVAL;

	ecc->पढ़ो_page = anfc_पढ़ो_page_hw_ecc;
	ecc->ग_लिखो_page = anfc_ग_लिखो_page_hw_ecc;

	वापस 0;
पूर्ण

अटल पूर्णांक anfc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा anand *anand = to_anand(chip);
	काष्ठा arasan_nfc *nfc = to_anfc(chip->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret = 0;

	अगर (mtd->ग_लिखोsize <= SZ_512)
		anand->caddr_cycles = 1;
	अन्यथा
		anand->caddr_cycles = 2;

	अगर (chip->options & न_अंकD_ROW_ADDR_3)
		anand->raddr_cycles = 3;
	अन्यथा
		anand->raddr_cycles = 2;

	चयन (mtd->ग_लिखोsize) अणु
	हाल 512:
		anand->page_sz = 0;
		अवरोध;
	हाल 1024:
		anand->page_sz = 5;
		अवरोध;
	हाल 2048:
		anand->page_sz = 1;
		अवरोध;
	हाल 4096:
		anand->page_sz = 2;
		अवरोध;
	हाल 8192:
		anand->page_sz = 3;
		अवरोध;
	हाल 16384:
		anand->page_sz = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* These hooks are valid क्रम all ECC providers */
	chip->ecc.पढ़ो_page_raw = nand_monolithic_पढ़ो_page_raw;
	chip->ecc.ग_लिखो_page_raw = nand_monolithic_ग_लिखो_page_raw;

	चयन (chip->ecc.engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_DIE:
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		ret = anfc_init_hw_ecc_controller(nfc, chip);
		अवरोध;
	शेष:
		dev_err(nfc->dev, "Unsupported ECC mode: %d\n",
			chip->ecc.engine_type);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम anfc_detach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा anand *anand = to_anand(chip);

	अगर (anand->bch)
		bch_मुक्त(anand->bch);
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops anfc_ops = अणु
	.exec_op = anfc_exec_op,
	.setup_पूर्णांकerface = anfc_setup_पूर्णांकerface,
	.attach_chip = anfc_attach_chip,
	.detach_chip = anfc_detach_chip,
पूर्ण;

अटल पूर्णांक anfc_chip_init(काष्ठा arasan_nfc *nfc, काष्ठा device_node *np)
अणु
	काष्ठा anand *anand;
	काष्ठा nand_chip *chip;
	काष्ठा mtd_info *mtd;
	पूर्णांक cs, rb, ret;

	anand = devm_kzalloc(nfc->dev, माप(*anand), GFP_KERNEL);
	अगर (!anand)
		वापस -ENOMEM;

	/* We करो not support multiple CS per chip yet */
	अगर (of_property_count_elems_of_size(np, "reg", माप(u32)) != 1) अणु
		dev_err(nfc->dev, "Invalid reg property\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "reg", &cs);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u32(np, "nand-rb", &rb);
	अगर (ret)
		वापस ret;

	अगर (cs >= ANFC_MAX_CS || rb >= ANFC_MAX_CS) अणु
		dev_err(nfc->dev, "Wrong CS %d or RB %d\n", cs, rb);
		वापस -EINVAL;
	पूर्ण

	अगर (test_and_set_bit(cs, &nfc->asचिन्हित_cs)) अणु
		dev_err(nfc->dev, "Already assigned CS %d\n", cs);
		वापस -EINVAL;
	पूर्ण

	anand->cs = cs;
	anand->rb = rb;

	chip = &anand->chip;
	mtd = nand_to_mtd(chip);
	mtd->dev.parent = nfc->dev;
	chip->controller = &nfc->controller;
	chip->options = न_अंकD_BUSWIDTH_AUTO | न_अंकD_NO_SUBPAGE_WRITE |
			न_अंकD_USES_DMA;

	nand_set_flash_node(chip, np);
	अगर (!mtd->name) अणु
		dev_err(nfc->dev, "NAND label property is mandatory\n");
		वापस -EINVAL;
	पूर्ण

	ret = nand_scan(chip, 1);
	अगर (ret) अणु
		dev_err(nfc->dev, "Scan operation failed\n");
		वापस ret;
	पूर्ण

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		nand_cleanup(chip);
		वापस ret;
	पूर्ण

	list_add_tail(&anand->node, &nfc->chips);

	वापस 0;
पूर्ण

अटल व्योम anfc_chips_cleanup(काष्ठा arasan_nfc *nfc)
अणु
	काष्ठा anand *anand, *पंचांगp;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(anand, पंचांगp, &nfc->chips, node) अणु
		chip = &anand->chip;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		list_del(&anand->node);
	पूर्ण
पूर्ण

अटल पूर्णांक anfc_chips_init(काष्ठा arasan_nfc *nfc)
अणु
	काष्ठा device_node *np = nfc->dev->of_node, *nand_np;
	पूर्णांक nchips = of_get_child_count(np);
	पूर्णांक ret;

	अगर (!nchips || nchips > ANFC_MAX_CS) अणु
		dev_err(nfc->dev, "Incorrect number of NAND chips (%d)\n",
			nchips);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(np, nand_np) अणु
		ret = anfc_chip_init(nfc, nand_np);
		अगर (ret) अणु
			of_node_put(nand_np);
			anfc_chips_cleanup(nfc);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम anfc_reset(काष्ठा arasan_nfc *nfc)
अणु
	/* Disable पूर्णांकerrupt संकेतs */
	ग_लिखोl_relaxed(0, nfc->base + INTR_SIG_EN_REG);

	/* Enable पूर्णांकerrupt status */
	ग_लिखोl_relaxed(EVENT_MASK, nfc->base + INTR_STS_EN_REG);
पूर्ण

अटल पूर्णांक anfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arasan_nfc *nfc;
	पूर्णांक ret;

	nfc = devm_kzalloc(&pdev->dev, माप(*nfc), GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nfc->dev = &pdev->dev;
	nand_controller_init(&nfc->controller);
	nfc->controller.ops = &anfc_ops;
	INIT_LIST_HEAD(&nfc->chips);

	nfc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(nfc->base))
		वापस PTR_ERR(nfc->base);

	anfc_reset(nfc);

	nfc->controller_clk = devm_clk_get(&pdev->dev, "controller");
	अगर (IS_ERR(nfc->controller_clk))
		वापस PTR_ERR(nfc->controller_clk);

	nfc->bus_clk = devm_clk_get(&pdev->dev, "bus");
	अगर (IS_ERR(nfc->bus_clk))
		वापस PTR_ERR(nfc->bus_clk);

	ret = clk_prepare_enable(nfc->controller_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(nfc->bus_clk);
	अगर (ret)
		जाओ disable_controller_clk;

	ret = anfc_chips_init(nfc);
	अगर (ret)
		जाओ disable_bus_clk;

	platक्रमm_set_drvdata(pdev, nfc);

	वापस 0;

disable_bus_clk:
	clk_disable_unprepare(nfc->bus_clk);

disable_controller_clk:
	clk_disable_unprepare(nfc->controller_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक anfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arasan_nfc *nfc = platक्रमm_get_drvdata(pdev);

	anfc_chips_cleanup(nfc);

	clk_disable_unprepare(nfc->bus_clk);
	clk_disable_unprepare(nfc->controller_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id anfc_ids[] = अणु
	अणु
		.compatible = "xlnx,zynqmp-nand-controller",
	पूर्ण,
	अणु
		.compatible = "arasan,nfc-v3p10",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, anfc_ids);

अटल काष्ठा platक्रमm_driver anfc_driver = अणु
	.driver = अणु
		.name = "arasan-nand-controller",
		.of_match_table = anfc_ids,
	पूर्ण,
	.probe = anfc_probe,
	.हटाओ = anfc_हटाओ,
पूर्ण;
module_platक्रमm_driver(anfc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Punnaiah Choudary Kalluri <punnaia@xilinx.com>");
MODULE_AUTHOR("Naga Sureshkumar Relli <nagasure@xilinx.com>");
MODULE_AUTHOR("Miquel Raynal <miquel.raynal@bootlin.com>");
MODULE_DESCRIPTION("Arasan NAND Flash Controller Driver");
