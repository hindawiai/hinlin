<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Rockchip न_अंकD Flash controller driver.
 * Copyright (C) 2020 Rockchip Inc.
 * Author: Yअगरeng Zhao <yअगरeng.zhao@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/*
 * NFC Page Data Layout:
 *	1024 bytes data + 4Bytes sys data + 28Bytes~124Bytes ECC data +
 *	1024 bytes data + 4Bytes sys data + 28Bytes~124Bytes ECC data +
 *	......
 * न_अंकD Page Data Layout:
 *	1024 * n data + m Bytes oob
 * Original Bad Block Mask Location:
 *	First byte of oob(spare).
 * nand_chip->oob_poi data layout:
 *	4Bytes sys data + .... + 4Bytes sys data + ECC data.
 */

/* न_अंकD controller रेजिस्टर definition */
#घोषणा NFC_READ			(0)
#घोषणा NFC_WRITE			(1)

#घोषणा NFC_FMCTL			(0x00)
#घोषणा   FMCTL_CE_SEL_M		0xFF
#घोषणा   FMCTL_CE_SEL(x)		(1 << (x))
#घोषणा   FMCTL_WP			BIT(8)
#घोषणा   FMCTL_RDY			BIT(9)

#घोषणा NFC_FMWAIT			(0x04)
#घोषणा   FLCTL_RST			BIT(0)
#घोषणा   FLCTL_WR			(1)	/* 0: पढ़ो, 1: ग_लिखो */
#घोषणा   FLCTL_XFER_ST			BIT(2)
#घोषणा   FLCTL_XFER_EN			BIT(3)
#घोषणा   FLCTL_ACORRECT		BIT(10) /* Auto correct error bits. */
#घोषणा   FLCTL_XFER_READY		BIT(20)
#घोषणा   FLCTL_XFER_SECTOR		(22)
#घोषणा   FLCTL_TOG_FIX			BIT(29)

#घोषणा   BCHCTL_BANK_M			(7 << 5)
#घोषणा   BCHCTL_BANK			(5)

#घोषणा   DMA_ST			BIT(0)
#घोषणा   DMA_WR			(1)	/* 0: ग_लिखो, 1: पढ़ो */
#घोषणा   DMA_EN			BIT(2)
#घोषणा   DMA_AHB_SIZE			(3)	/* 0: 1, 1: 2, 2: 4 */
#घोषणा   DMA_BURST_SIZE		(6)	/* 0: 1, 3: 4, 5: 8, 7: 16 */
#घोषणा   DMA_INC_NUM			(9)	/* 1 - 16 */

#घोषणा ECC_ERR_CNT(x, e) ((((x) >> (e).low) & (e).low_mask) |\
	  (((x) >> (e).high) & (e).high_mask) << (e).low_bn)
#घोषणा   INT_DMA			BIT(0)
#घोषणा NFC_BANK			(0x800)
#घोषणा NFC_BANK_STEP			(0x100)
#घोषणा   BANK_DATA			(0x00)
#घोषणा   BANK_ADDR			(0x04)
#घोषणा   BANK_CMD			(0x08)
#घोषणा NFC_SRAM0			(0x1000)
#घोषणा NFC_SRAM1			(0x1400)
#घोषणा NFC_SRAM_SIZE			(0x400)
#घोषणा NFC_TIMEOUT			(500000)
#घोषणा NFC_MAX_OOB_PER_STEP		128
#घोषणा NFC_MIN_OOB_PER_STEP		64
#घोषणा MAX_DATA_SIZE			0xFFFC
#घोषणा MAX_ADDRESS_CYC			6
#घोषणा NFC_ECC_MAX_MODES		4
#घोषणा NFC_MAX_NSELS			(8) /* Some Socs only have 1 or 2 CSs. */
#घोषणा NFC_SYS_DATA_SIZE		(4) /* 4 bytes sys data in oob pre 1024 data.*/
#घोषणा RK_DEFAULT_CLOCK_RATE		(150 * 1000 * 1000) /* 150 Mhz */
#घोषणा ACCTIMING(csrw, rwpw, rwcs)	((csrw) << 12 | (rwpw) << 5 | (rwcs))

क्रमागत nfc_type अणु
	NFC_V6,
	NFC_V8,
	NFC_V9,
पूर्ण;

/**
 * काष्ठा rk_ecc_cnt_status: represent a ecc status data.
 * @err_flag_bit: error flag bit index at रेजिस्टर.
 * @low: ECC count low bit index at रेजिस्टर.
 * @low_mask: mask bit.
 * @low_bn: ECC count low bit number.
 * @high: ECC count high bit index at रेजिस्टर.
 * @high_mask: mask bit
 */
काष्ठा ecc_cnt_status अणु
	u8 err_flag_bit;
	u8 low;
	u8 low_mask;
	u8 low_bn;
	u8 high;
	u8 high_mask;
पूर्ण;

/**
 * @type: NFC version
 * @ecc_strengths: ECC strengths
 * @ecc_cfgs: ECC config values
 * @flctl_off: FLCTL रेजिस्टर offset
 * @bchctl_off: BCHCTL रेजिस्टर offset
 * @dma_data_buf_off: DMA_DATA_BUF रेजिस्टर offset
 * @dma_oob_buf_off: DMA_OOB_BUF रेजिस्टर offset
 * @dma_cfg_off: DMA_CFG रेजिस्टर offset
 * @dma_st_off: DMA_ST रेजिस्टर offset
 * @bch_st_off: BCG_ST रेजिस्टर offset
 * @अक्रमmz_off: RANDMZ रेजिस्टर offset
 * @पूर्णांक_en_off: पूर्णांकerrupt enable रेजिस्टर offset
 * @पूर्णांक_clr_off: पूर्णांकerrupt clean रेजिस्टर offset
 * @पूर्णांक_st_off: पूर्णांकerrupt status रेजिस्टर offset
 * @oob0_off: oob0 रेजिस्टर offset
 * @oob1_off: oob1 रेजिस्टर offset
 * @ecc0: represent ECC0 status data
 * @ecc1: represent ECC1 status data
 */
काष्ठा nfc_cfg अणु
	क्रमागत nfc_type type;
	u8 ecc_strengths[NFC_ECC_MAX_MODES];
	u32 ecc_cfgs[NFC_ECC_MAX_MODES];
	u32 flctl_off;
	u32 bchctl_off;
	u32 dma_cfg_off;
	u32 dma_data_buf_off;
	u32 dma_oob_buf_off;
	u32 dma_st_off;
	u32 bch_st_off;
	u32 अक्रमmz_off;
	u32 पूर्णांक_en_off;
	u32 पूर्णांक_clr_off;
	u32 पूर्णांक_st_off;
	u32 oob0_off;
	u32 oob1_off;
	काष्ठा ecc_cnt_status ecc0;
	काष्ठा ecc_cnt_status ecc1;
पूर्ण;

काष्ठा rk_nfc_nand_chip अणु
	काष्ठा list_head node;
	काष्ठा nand_chip chip;

	u16 boot_blks;
	u16 metadata_size;
	u32 boot_ecc;
	u32 timing;

	u8 nsels;
	u8 sels[];
	/* Nothing after this field. */
पूर्ण;

काष्ठा rk_nfc अणु
	काष्ठा nand_controller controller;
	स्थिर काष्ठा nfc_cfg *cfg;
	काष्ठा device *dev;

	काष्ठा clk *nfc_clk;
	काष्ठा clk *ahb_clk;
	व्योम __iomem *regs;

	u32 selected_bank;
	u32 band_offset;
	u32 cur_ecc;
	u32 cur_timing;

	काष्ठा completion करोne;
	काष्ठा list_head chips;

	u8 *page_buf;
	u32 *oob_buf;
	u32 page_buf_size;
	u32 oob_buf_size;

	अचिन्हित दीर्घ asचिन्हित_cs;
पूर्ण;

अटल अंतरभूत काष्ठा rk_nfc_nand_chip *rk_nfc_to_rknand(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा rk_nfc_nand_chip, chip);
पूर्ण

अटल अंतरभूत u8 *rk_nfc_buf_to_data_ptr(काष्ठा nand_chip *chip, स्थिर u8 *p, पूर्णांक i)
अणु
	वापस (u8 *)p + i * chip->ecc.size;
पूर्ण

अटल अंतरभूत u8 *rk_nfc_buf_to_oob_ptr(काष्ठा nand_chip *chip, पूर्णांक i)
अणु
	u8 *poi;

	poi = chip->oob_poi + i * NFC_SYS_DATA_SIZE;

	वापस poi;
पूर्ण

अटल अंतरभूत u8 *rk_nfc_buf_to_oob_ecc_ptr(काष्ठा nand_chip *chip, पूर्णांक i)
अणु
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);
	u8 *poi;

	poi = chip->oob_poi + rknand->metadata_size + chip->ecc.bytes * i;

	वापस poi;
पूर्ण

अटल अंतरभूत पूर्णांक rk_nfc_data_len(काष्ठा nand_chip *chip)
अणु
	वापस chip->ecc.size + chip->ecc.bytes + NFC_SYS_DATA_SIZE;
पूर्ण

अटल अंतरभूत u8 *rk_nfc_data_ptr(काष्ठा nand_chip *chip, पूर्णांक i)
अणु
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);

	वापस nfc->page_buf + i * rk_nfc_data_len(chip);
पूर्ण

अटल अंतरभूत u8 *rk_nfc_oob_ptr(काष्ठा nand_chip *chip, पूर्णांक i)
अणु
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);

	वापस nfc->page_buf + i * rk_nfc_data_len(chip) + chip->ecc.size;
पूर्ण

अटल पूर्णांक rk_nfc_hw_ecc_setup(काष्ठा nand_chip *chip, u32 strength)
अणु
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	u32 reg, i;

	क्रम (i = 0; i < NFC_ECC_MAX_MODES; i++) अणु
		अगर (strength == nfc->cfg->ecc_strengths[i]) अणु
			reg = nfc->cfg->ecc_cfgs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= NFC_ECC_MAX_MODES)
		वापस -EINVAL;

	ग_लिखोl(reg, nfc->regs + nfc->cfg->bchctl_off);

	/* Save chip ECC setting */
	nfc->cur_ecc = strength;

	वापस 0;
पूर्ण

अटल व्योम rk_nfc_select_chip(काष्ठा nand_chip *chip, पूर्णांक cs)
अणु
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	u32 val;

	अगर (cs < 0) अणु
		nfc->selected_bank = -1;
		/* Deselect the currently selected target. */
		val = पढ़ोl_relaxed(nfc->regs + NFC_FMCTL);
		val &= ~FMCTL_CE_SEL_M;
		ग_लिखोl(val, nfc->regs + NFC_FMCTL);
		वापस;
	पूर्ण

	nfc->selected_bank = rknand->sels[cs];
	nfc->band_offset = NFC_BANK + nfc->selected_bank * NFC_BANK_STEP;

	val = पढ़ोl_relaxed(nfc->regs + NFC_FMCTL);
	val &= ~FMCTL_CE_SEL_M;
	val |= FMCTL_CE_SEL(nfc->selected_bank);

	ग_लिखोl(val, nfc->regs + NFC_FMCTL);

	/*
	 * Compare current chip timing with selected chip timing and
	 * change अगर needed.
	 */
	अगर (nfc->cur_timing != rknand->timing) अणु
		ग_लिखोl(rknand->timing, nfc->regs + NFC_FMWAIT);
		nfc->cur_timing = rknand->timing;
	पूर्ण

	/*
	 * Compare current chip ECC setting with selected chip ECC setting and
	 * change अगर needed.
	 */
	अगर (nfc->cur_ecc != ecc->strength)
		rk_nfc_hw_ecc_setup(chip, ecc->strength);
पूर्ण

अटल अंतरभूत पूर्णांक rk_nfc_रुको_ioपढ़ोy(काष्ठा rk_nfc *nfc)
अणु
	पूर्णांक rc;
	u32 val;

	rc = पढ़ोl_relaxed_poll_समयout(nfc->regs + NFC_FMCTL, val,
					val & FMCTL_RDY, 10, NFC_TIMEOUT);

	वापस rc;
पूर्ण

अटल व्योम rk_nfc_पढ़ो_buf(काष्ठा rk_nfc *nfc, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		buf[i] = पढ़ोb_relaxed(nfc->regs + nfc->band_offset +
				       BANK_DATA);
पूर्ण

अटल व्योम rk_nfc_ग_लिखो_buf(काष्ठा rk_nfc *nfc, स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ग_लिखोb(buf[i], nfc->regs + nfc->band_offset + BANK_DATA);
पूर्ण

अटल पूर्णांक rk_nfc_cmd(काष्ठा nand_chip *chip,
		      स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	अचिन्हित पूर्णांक i, j, reमुख्यing, start;
	पूर्णांक reg_offset = nfc->band_offset;
	u8 *inbuf = शून्य;
	स्थिर u8 *outbuf;
	u32 cnt = 0;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < subop->ninstrs; i++) अणु
		स्थिर काष्ठा nand_op_instr *instr = &subop->instrs[i];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			ग_लिखोb(instr->ctx.cmd.opcode,
			       nfc->regs + reg_offset + BANK_CMD);
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			reमुख्यing = nand_subop_get_num_addr_cyc(subop, i);
			start = nand_subop_get_addr_start_off(subop, i);

			क्रम (j = 0; j < 8 && j + start < reमुख्यing; j++)
				ग_लिखोb(instr->ctx.addr.addrs[j + start],
				       nfc->regs + reg_offset + BANK_ADDR);
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
		हाल न_अंकD_OP_DATA_OUT_INSTR:
			start = nand_subop_get_data_start_off(subop, i);
			cnt = nand_subop_get_data_len(subop, i);

			अगर (instr->type == न_अंकD_OP_DATA_OUT_INSTR) अणु
				outbuf = instr->ctx.data.buf.out + start;
				rk_nfc_ग_लिखो_buf(nfc, outbuf, cnt);
			पूर्ण अन्यथा अणु
				inbuf = instr->ctx.data.buf.in + start;
				rk_nfc_पढ़ो_buf(nfc, inbuf, cnt);
			पूर्ण
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			अगर (rk_nfc_रुको_ioपढ़ोy(nfc) < 0) अणु
				ret = -ETIMEDOUT;
				dev_err(nfc->dev, "IO not ready\n");
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nand_op_parser rk_nfc_op_parser = न_अंकD_OP_PARSER(
	न_अंकD_OP_PARSER_PATTERN(
		rk_nfc_cmd,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, MAX_ADDRESS_CYC),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(true, MAX_DATA_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		rk_nfc_cmd,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, MAX_ADDRESS_CYC),
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(true, MAX_DATA_SIZE),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true)),
);

अटल पूर्णांक rk_nfc_exec_op(काष्ठा nand_chip *chip,
			  स्थिर काष्ठा nand_operation *op,
			  bool check_only)
अणु
	अगर (!check_only)
		rk_nfc_select_chip(chip, op->cs);

	वापस nand_op_parser_exec_op(chip, &rk_nfc_op_parser, op,
				      check_only);
पूर्ण

अटल पूर्णांक rk_nfc_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक target,
				  स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	स्थिर काष्ठा nand_sdr_timings *timings;
	u32 rate, tc2rw, trwpw, trw2c;
	u32 temp;

	अगर (target < 0)
		वापस 0;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस -EOPNOTSUPP;

	अगर (IS_ERR(nfc->nfc_clk))
		rate = clk_get_rate(nfc->ahb_clk);
	अन्यथा
		rate = clk_get_rate(nfc->nfc_clk);

	/* Turn घड़ी rate पूर्णांकo kHz. */
	rate /= 1000;

	tc2rw = 1;
	trw2c = 1;

	trwpw = max(timings->tWC_min, timings->tRC_min) / 1000;
	trwpw = DIV_ROUND_UP(trwpw * rate, 1000000);

	temp = timings->tREA_max / 1000;
	temp = DIV_ROUND_UP(temp * rate, 1000000);

	अगर (trwpw < temp)
		trwpw = temp;

	/*
	 * ACCON: access timing control रेजिस्टर
	 * -------------------------------------
	 * 31:18: reserved
	 * 17:12: csrw, घड़ी cycles from the falling edge of CSn to the
	 *   falling edge of RDn or WRn
	 * 11:11: reserved
	 * 10:05: rwpw, the width of RDn or WRn in processor घड़ी cycles
	 * 04:00: rwcs, घड़ी cycles from the rising edge of RDn or WRn to the
	 *   rising edge of CSn
	 */

	/* Save chip timing */
	rknand->timing = ACCTIMING(tc2rw, trwpw, trw2c);

	वापस 0;
पूर्ण

अटल व्योम rk_nfc_xfer_start(काष्ठा rk_nfc *nfc, u8 rw, u8 n_KB,
			      dma_addr_t dma_data, dma_addr_t dma_oob)
अणु
	u32 dma_reg, fl_reg, bch_reg;

	dma_reg = DMA_ST | ((!rw) << DMA_WR) | DMA_EN | (2 << DMA_AHB_SIZE) |
	      (7 << DMA_BURST_SIZE) | (16 << DMA_INC_NUM);

	fl_reg = (rw << FLCTL_WR) | FLCTL_XFER_EN | FLCTL_ACORRECT |
		 (n_KB << FLCTL_XFER_SECTOR) | FLCTL_TOG_FIX;

	अगर (nfc->cfg->type == NFC_V6 || nfc->cfg->type == NFC_V8) अणु
		bch_reg = पढ़ोl_relaxed(nfc->regs + nfc->cfg->bchctl_off);
		bch_reg = (bch_reg & (~BCHCTL_BANK_M)) |
			  (nfc->selected_bank << BCHCTL_BANK);
		ग_लिखोl(bch_reg, nfc->regs + nfc->cfg->bchctl_off);
	पूर्ण

	ग_लिखोl(dma_reg, nfc->regs + nfc->cfg->dma_cfg_off);
	ग_लिखोl((u32)dma_data, nfc->regs + nfc->cfg->dma_data_buf_off);
	ग_लिखोl((u32)dma_oob, nfc->regs + nfc->cfg->dma_oob_buf_off);
	ग_लिखोl(fl_reg, nfc->regs + nfc->cfg->flctl_off);
	fl_reg |= FLCTL_XFER_ST;
	ग_लिखोl(fl_reg, nfc->regs + nfc->cfg->flctl_off);
पूर्ण

अटल पूर्णांक rk_nfc_रुको_क्रम_xfer_करोne(काष्ठा rk_nfc *nfc)
अणु
	व्योम __iomem *ptr;
	u32 reg;

	ptr = nfc->regs + nfc->cfg->flctl_off;

	वापस पढ़ोl_relaxed_poll_समयout(ptr, reg,
					 reg & FLCTL_XFER_READY,
					 10, NFC_TIMEOUT);
पूर्ण

अटल पूर्णांक rk_nfc_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				 पूर्णांक oob_on, पूर्णांक page)
अणु
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक i, pages_per_blk;

	pages_per_blk = mtd->erasesize / mtd->ग_लिखोsize;
	अगर ((chip->options & न_अंकD_IS_BOOT_MEDIUM) &&
	    (page < (pages_per_blk * rknand->boot_blks)) &&
	    rknand->boot_ecc != ecc->strength) अणु
		/*
		 * There's currently no method to notअगरy the MTD framework that
		 * a dअगरferent ECC strength is in use क्रम the boot blocks.
		 */
		वापस -EIO;
	पूर्ण

	अगर (!buf)
		स_रखो(nfc->page_buf, 0xff, mtd->ग_लिखोsize + mtd->oobsize);

	क्रम (i = 0; i < ecc->steps; i++) अणु
		/* Copy data to the NFC buffer. */
		अगर (buf)
			स_नकल(rk_nfc_data_ptr(chip, i),
			       rk_nfc_buf_to_data_ptr(chip, buf, i),
			       ecc->size);
		/*
		 * The first four bytes of OOB are reserved क्रम the
		 * boot ROM. In some debugging हालs, such as with a
		 * पढ़ो, erase and ग_लिखो back test these 4 bytes stored
		 * in OOB also need to be written back.
		 *
		 * The function nand_block_bad detects bad blocks like:
		 *
		 * bad = chip->oob_poi[chip->badblockpos];
		 *
		 * chip->badblockpos == 0 क्रम a large page न_अंकD Flash,
		 * so chip->oob_poi[0] is the bad block mask (BBM).
		 *
		 * The OOB data layout on the NFC is:
		 *
		 *    PA0  PA1  PA2  PA3  | BBM OOB1 OOB2 OOB3 | ...
		 *
		 * or
		 *
		 *    0xFF 0xFF 0xFF 0xFF | BBM OOB1 OOB2 OOB3 | ...
		 *
		 * The code here just swaps the first 4 bytes with the last
		 * 4 bytes without losing any data.
		 *
		 * The chip->oob_poi data layout:
		 *
		 *    BBM  OOB1 OOB2 OOB3 |......|  PA0  PA1  PA2  PA3
		 *
		 * The rk_nfc_ooblayout_मुक्त() function alपढ़ोy has reserved
		 * these 4 bytes with:
		 *
		 * oob_region->offset = NFC_SYS_DATA_SIZE + 2;
		 */
		अगर (!i)
			स_नकल(rk_nfc_oob_ptr(chip, i),
			       rk_nfc_buf_to_oob_ptr(chip, ecc->steps - 1),
			       NFC_SYS_DATA_SIZE);
		अन्यथा
			स_नकल(rk_nfc_oob_ptr(chip, i),
			       rk_nfc_buf_to_oob_ptr(chip, i - 1),
			       NFC_SYS_DATA_SIZE);
		/* Copy ECC data to the NFC buffer. */
		स_नकल(rk_nfc_oob_ptr(chip, i) + NFC_SYS_DATA_SIZE,
		       rk_nfc_buf_to_oob_ecc_ptr(chip, i),
		       ecc->bytes);
	पूर्ण

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	rk_nfc_ग_लिखो_buf(nfc, buf, mtd->ग_लिखोsize + mtd->oobsize);
	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक rk_nfc_ग_लिखो_page_hwecc(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				   पूर्णांक oob_on, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक oob_step = (ecc->bytes > 60) ? NFC_MAX_OOB_PER_STEP :
			NFC_MIN_OOB_PER_STEP;
	पूर्णांक pages_per_blk = mtd->erasesize / mtd->ग_लिखोsize;
	पूर्णांक ret = 0, i, boot_rom_mode = 0;
	dma_addr_t dma_data, dma_oob;
	u32 reg;
	u8 *oob;

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	अगर (buf)
		स_नकल(nfc->page_buf, buf, mtd->ग_लिखोsize);
	अन्यथा
		स_रखो(nfc->page_buf, 0xFF, mtd->ग_लिखोsize);

	/*
	 * The first blocks (4, 8 or 16 depending on the device) are used
	 * by the boot ROM and the first 32 bits of OOB need to link to
	 * the next page address in the same block. We can't directly copy
	 * OOB data from the MTD framework, because this page address
	 * conflicts क्रम example with the bad block marker (BBM),
	 * so we shअगरt all OOB data including the BBM with 4 byte positions.
	 * As a consequence the OOB size available to the MTD framework is
	 * also reduced with 4 bytes.
	 *
	 *    PA0  PA1  PA2  PA3 | BBM OOB1 OOB2 OOB3 | ...
	 *
	 * If a न_अंकD is not a boot medium or the page is not a boot block,
	 * the first 4 bytes are left untouched by writing 0xFF to them.
	 *
	 *   0xFF 0xFF 0xFF 0xFF | BBM OOB1 OOB2 OOB3 | ...
	 *
	 * Configure the ECC algorithm supported by the boot ROM.
	 */
	अगर ((page < (pages_per_blk * rknand->boot_blks)) &&
	    (chip->options & न_अंकD_IS_BOOT_MEDIUM)) अणु
		boot_rom_mode = 1;
		अगर (rknand->boot_ecc != ecc->strength)
			rk_nfc_hw_ecc_setup(chip, rknand->boot_ecc);
	पूर्ण

	क्रम (i = 0; i < ecc->steps; i++) अणु
		अगर (!i) अणु
			reg = 0xFFFFFFFF;
		पूर्ण अन्यथा अणु
			oob = chip->oob_poi + (i - 1) * NFC_SYS_DATA_SIZE;
			reg = oob[0] | oob[1] << 8 | oob[2] << 16 |
			      oob[3] << 24;
		पूर्ण

		अगर (!i && boot_rom_mode)
			reg = (page & (pages_per_blk - 1)) * 4;

		अगर (nfc->cfg->type == NFC_V9)
			nfc->oob_buf[i] = reg;
		अन्यथा
			nfc->oob_buf[i * (oob_step / 4)] = reg;
	पूर्ण

	dma_data = dma_map_single(nfc->dev, (व्योम *)nfc->page_buf,
				  mtd->ग_लिखोsize, DMA_TO_DEVICE);
	dma_oob = dma_map_single(nfc->dev, nfc->oob_buf,
				 ecc->steps * oob_step,
				 DMA_TO_DEVICE);

	reinit_completion(&nfc->करोne);
	ग_लिखोl(INT_DMA, nfc->regs + nfc->cfg->पूर्णांक_en_off);

	rk_nfc_xfer_start(nfc, NFC_WRITE, ecc->steps, dma_data,
			  dma_oob);
	ret = रुको_क्रम_completion_समयout(&nfc->करोne,
					  msecs_to_jअगरfies(100));
	अगर (!ret)
		dev_warn(nfc->dev, "write: wait dma done timeout.\n");
	/*
	 * Whether the DMA transfer is completed or not. The driver
	 * needs to check the NFC`s status रेजिस्टर to see अगर the data
	 * transfer was completed.
	 */
	ret = rk_nfc_रुको_क्रम_xfer_करोne(nfc);

	dma_unmap_single(nfc->dev, dma_data, mtd->ग_लिखोsize,
			 DMA_TO_DEVICE);
	dma_unmap_single(nfc->dev, dma_oob, ecc->steps * oob_step,
			 DMA_TO_DEVICE);

	अगर (boot_rom_mode && rknand->boot_ecc != ecc->strength)
		rk_nfc_hw_ecc_setup(chip, ecc->strength);

	अगर (ret) अणु
		dev_err(nfc->dev, "write: wait transfer done timeout.\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक rk_nfc_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस rk_nfc_ग_लिखो_page_hwecc(chip, शून्य, 1, page);
पूर्ण

अटल पूर्णांक rk_nfc_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf, पूर्णांक oob_on,
				पूर्णांक page)
अणु
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक i, pages_per_blk;

	pages_per_blk = mtd->erasesize / mtd->ग_लिखोsize;
	अगर ((chip->options & न_अंकD_IS_BOOT_MEDIUM) &&
	    (page < (pages_per_blk * rknand->boot_blks)) &&
	    rknand->boot_ecc != ecc->strength) अणु
		/*
		 * There's currently no method to notअगरy the MTD framework that
		 * a dअगरferent ECC strength is in use क्रम the boot blocks.
		 */
		वापस -EIO;
	पूर्ण

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	rk_nfc_पढ़ो_buf(nfc, nfc->page_buf, mtd->ग_लिखोsize + mtd->oobsize);
	क्रम (i = 0; i < ecc->steps; i++) अणु
		/*
		 * The first four bytes of OOB are reserved क्रम the
		 * boot ROM. In some debugging हालs, such as with a पढ़ो,
		 * erase and ग_लिखो back test, these 4 bytes also must be
		 * saved somewhere, otherwise this inक्रमmation will be
		 * lost during a ग_लिखो back.
		 */
		अगर (!i)
			स_नकल(rk_nfc_buf_to_oob_ptr(chip, ecc->steps - 1),
			       rk_nfc_oob_ptr(chip, i),
			       NFC_SYS_DATA_SIZE);
		अन्यथा
			स_नकल(rk_nfc_buf_to_oob_ptr(chip, i - 1),
			       rk_nfc_oob_ptr(chip, i),
			       NFC_SYS_DATA_SIZE);

		/* Copy ECC data from the NFC buffer. */
		स_नकल(rk_nfc_buf_to_oob_ecc_ptr(chip, i),
		       rk_nfc_oob_ptr(chip, i) + NFC_SYS_DATA_SIZE,
		       ecc->bytes);

		/* Copy data from the NFC buffer. */
		अगर (buf)
			स_नकल(rk_nfc_buf_to_data_ptr(chip, buf, i),
			       rk_nfc_data_ptr(chip, i),
			       ecc->size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rk_nfc_पढ़ो_page_hwecc(काष्ठा nand_chip *chip, u8 *buf, पूर्णांक oob_on,
				  पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक oob_step = (ecc->bytes > 60) ? NFC_MAX_OOB_PER_STEP :
			NFC_MIN_OOB_PER_STEP;
	पूर्णांक pages_per_blk = mtd->erasesize / mtd->ग_लिखोsize;
	dma_addr_t dma_data, dma_oob;
	पूर्णांक ret = 0, i, cnt, boot_rom_mode = 0;
	पूर्णांक max_bitflips = 0, bch_st, ecc_fail = 0;
	u8 *oob;
	u32 पंचांगp;

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	dma_data = dma_map_single(nfc->dev, nfc->page_buf,
				  mtd->ग_लिखोsize,
				  DMA_FROM_DEVICE);
	dma_oob = dma_map_single(nfc->dev, nfc->oob_buf,
				 ecc->steps * oob_step,
				 DMA_FROM_DEVICE);

	/*
	 * The first blocks (4, 8 or 16 depending on the device)
	 * are used by the boot ROM.
	 * Configure the ECC algorithm supported by the boot ROM.
	 */
	अगर ((page < (pages_per_blk * rknand->boot_blks)) &&
	    (chip->options & न_अंकD_IS_BOOT_MEDIUM)) अणु
		boot_rom_mode = 1;
		अगर (rknand->boot_ecc != ecc->strength)
			rk_nfc_hw_ecc_setup(chip, rknand->boot_ecc);
	पूर्ण

	reinit_completion(&nfc->करोne);
	ग_लिखोl(INT_DMA, nfc->regs + nfc->cfg->पूर्णांक_en_off);
	rk_nfc_xfer_start(nfc, NFC_READ, ecc->steps, dma_data,
			  dma_oob);
	ret = रुको_क्रम_completion_समयout(&nfc->करोne,
					  msecs_to_jअगरfies(100));
	अगर (!ret)
		dev_warn(nfc->dev, "read: wait dma done timeout.\n");
	/*
	 * Whether the DMA transfer is completed or not. The driver
	 * needs to check the NFC`s status रेजिस्टर to see अगर the data
	 * transfer was completed.
	 */
	ret = rk_nfc_रुको_क्रम_xfer_करोne(nfc);

	dma_unmap_single(nfc->dev, dma_data, mtd->ग_लिखोsize,
			 DMA_FROM_DEVICE);
	dma_unmap_single(nfc->dev, dma_oob, ecc->steps * oob_step,
			 DMA_FROM_DEVICE);

	अगर (ret) अणु
		ret = -ETIMEDOUT;
		dev_err(nfc->dev, "read: wait transfer done timeout.\n");
		जाओ समयout_err;
	पूर्ण

	क्रम (i = 1; i < ecc->steps; i++) अणु
		oob = chip->oob_poi + (i - 1) * NFC_SYS_DATA_SIZE;
		अगर (nfc->cfg->type == NFC_V9)
			पंचांगp = nfc->oob_buf[i];
		अन्यथा
			पंचांगp = nfc->oob_buf[i * (oob_step / 4)];
		*oob++ = (u8)पंचांगp;
		*oob++ = (u8)(पंचांगp >> 8);
		*oob++ = (u8)(पंचांगp >> 16);
		*oob++ = (u8)(पंचांगp >> 24);
	पूर्ण

	क्रम (i = 0; i < (ecc->steps / 2); i++) अणु
		bch_st = पढ़ोl_relaxed(nfc->regs +
				       nfc->cfg->bch_st_off + i * 4);
		अगर (bch_st & BIT(nfc->cfg->ecc0.err_flag_bit) ||
		    bch_st & BIT(nfc->cfg->ecc1.err_flag_bit)) अणु
			mtd->ecc_stats.failed++;
			ecc_fail = 1;
		पूर्ण अन्यथा अणु
			cnt = ECC_ERR_CNT(bch_st, nfc->cfg->ecc0);
			mtd->ecc_stats.corrected += cnt;
			max_bitflips = max_t(u32, max_bitflips, cnt);

			cnt = ECC_ERR_CNT(bch_st, nfc->cfg->ecc1);
			mtd->ecc_stats.corrected += cnt;
			max_bitflips = max_t(u32, max_bitflips, cnt);
		पूर्ण
	पूर्ण

	अगर (buf)
		स_नकल(buf, nfc->page_buf, mtd->ग_लिखोsize);

समयout_err:
	अगर (boot_rom_mode && rknand->boot_ecc != ecc->strength)
		rk_nfc_hw_ecc_setup(chip, ecc->strength);

	अगर (ret)
		वापस ret;

	अगर (ecc_fail) अणु
		dev_err(nfc->dev, "read page: %x ecc error!\n", page);
		वापस 0;
	पूर्ण

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक rk_nfc_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस rk_nfc_पढ़ो_page_hwecc(chip, शून्य, 1, page);
पूर्ण

अटल अंतरभूत व्योम rk_nfc_hw_init(काष्ठा rk_nfc *nfc)
अणु
	/* Disable flash wp. */
	ग_लिखोl(FMCTL_WP, nfc->regs + NFC_FMCTL);
	/* Config शेष timing 40ns at 150 Mhz NFC घड़ी. */
	ग_लिखोl(0x1081, nfc->regs + NFC_FMWAIT);
	nfc->cur_timing = 0x1081;
	/* Disable अक्रमomizer and DMA. */
	ग_लिखोl(0, nfc->regs + nfc->cfg->अक्रमmz_off);
	ग_लिखोl(0, nfc->regs + nfc->cfg->dma_cfg_off);
	ग_लिखोl(FLCTL_RST, nfc->regs + nfc->cfg->flctl_off);
पूर्ण

अटल irqवापस_t rk_nfc_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा rk_nfc *nfc = id;
	u32 sta, ien;

	sta = पढ़ोl_relaxed(nfc->regs + nfc->cfg->पूर्णांक_st_off);
	ien = पढ़ोl_relaxed(nfc->regs + nfc->cfg->पूर्णांक_en_off);

	अगर (!(sta & ien))
		वापस IRQ_NONE;

	ग_लिखोl(sta, nfc->regs + nfc->cfg->पूर्णांक_clr_off);
	ग_लिखोl(~sta & ien, nfc->regs + nfc->cfg->पूर्णांक_en_off);

	complete(&nfc->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rk_nfc_enable_clks(काष्ठा device *dev, काष्ठा rk_nfc *nfc)
अणु
	पूर्णांक ret;

	अगर (!IS_ERR(nfc->nfc_clk)) अणु
		ret = clk_prepare_enable(nfc->nfc_clk);
		अगर (ret) अणु
			dev_err(dev, "failed to enable NFC clk\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(nfc->ahb_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable ahb clk\n");
		अगर (!IS_ERR(nfc->nfc_clk))
			clk_disable_unprepare(nfc->nfc_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rk_nfc_disable_clks(काष्ठा rk_nfc *nfc)
अणु
	अगर (!IS_ERR(nfc->nfc_clk))
		clk_disable_unprepare(nfc->nfc_clk);
	clk_disable_unprepare(nfc->ahb_clk);
पूर्ण

अटल पूर्णांक rk_nfc_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oob_region)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);

	अगर (section)
		वापस -दुस्फल;

	/*
	 * The beginning of the OOB area stores the reserved data क्रम the NFC,
	 * the size of the reserved data is NFC_SYS_DATA_SIZE bytes.
	 */
	oob_region->length = rknand->metadata_size - NFC_SYS_DATA_SIZE - 2;
	oob_region->offset = NFC_SYS_DATA_SIZE + 2;

	वापस 0;
पूर्ण

अटल पूर्णांक rk_nfc_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				काष्ठा mtd_oob_region *oob_region)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);

	अगर (section)
		वापस -दुस्फल;

	oob_region->length = mtd->oobsize - rknand->metadata_size;
	oob_region->offset = rknand->metadata_size;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops rk_nfc_ooblayout_ops = अणु
	.मुक्त = rk_nfc_ooblayout_मुक्त,
	.ecc = rk_nfc_ooblayout_ecc,
पूर्ण;

अटल पूर्णांक rk_nfc_ecc_init(काष्ठा device *dev, काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	स्थिर u8 *strengths = nfc->cfg->ecc_strengths;
	u8 max_strength, nfc_max_strength;
	पूर्णांक i;

	nfc_max_strength = nfc->cfg->ecc_strengths[0];
	/* If optional dt settings not present. */
	अगर (!ecc->size || !ecc->strength ||
	    ecc->strength > nfc_max_strength) अणु
		chip->ecc.size = 1024;
		ecc->steps = mtd->ग_लिखोsize / ecc->size;

		/*
		 * HW ECC always requests the number of ECC bytes per 1024 byte
		 * blocks. The first 4 OOB bytes are reserved क्रम sys data.
		 */
		max_strength = ((mtd->oobsize / ecc->steps) - 4) * 8 /
				 fls(8 * 1024);
		अगर (max_strength > nfc_max_strength)
			max_strength = nfc_max_strength;

		क्रम (i = 0; i < 4; i++) अणु
			अगर (max_strength >= strengths[i])
				अवरोध;
		पूर्ण

		अगर (i >= 4) अणु
			dev_err(nfc->dev, "unsupported ECC strength\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		ecc->strength = strengths[i];
	पूर्ण
	ecc->steps = mtd->ग_लिखोsize / ecc->size;
	ecc->bytes = DIV_ROUND_UP(ecc->strength * fls(8 * chip->ecc.size), 8);

	वापस 0;
पूर्ण

अटल पूर्णांक rk_nfc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा device *dev = mtd->dev.parent;
	काष्ठा rk_nfc *nfc = nand_get_controller_data(chip);
	काष्ठा rk_nfc_nand_chip *rknand = rk_nfc_to_rknand(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक new_page_len, new_oob_len;
	व्योम *buf;
	पूर्णांक ret;

	अगर (chip->options & न_अंकD_BUSWIDTH_16) अणु
		dev_err(dev, "16 bits bus width not supported");
		वापस -EINVAL;
	पूर्ण

	अगर (ecc->engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	ret = rk_nfc_ecc_init(dev, mtd);
	अगर (ret)
		वापस ret;

	rknand->metadata_size = NFC_SYS_DATA_SIZE * ecc->steps;

	अगर (rknand->metadata_size < NFC_SYS_DATA_SIZE + 2) अणु
		dev_err(dev,
			"driver needs at least %d bytes of meta data\n",
			NFC_SYS_DATA_SIZE + 2);
		वापस -EIO;
	पूर्ण

	/* Check buffer first, aव्योम duplicate alloc buffer. */
	new_page_len = mtd->ग_लिखोsize + mtd->oobsize;
	अगर (nfc->page_buf && new_page_len > nfc->page_buf_size) अणु
		buf = kपुनः_स्मृति(nfc->page_buf, new_page_len,
			       GFP_KERNEL | GFP_DMA);
		अगर (!buf)
			वापस -ENOMEM;
		nfc->page_buf = buf;
		nfc->page_buf_size = new_page_len;
	पूर्ण

	new_oob_len = ecc->steps * NFC_MAX_OOB_PER_STEP;
	अगर (nfc->oob_buf && new_oob_len > nfc->oob_buf_size) अणु
		buf = kपुनः_स्मृति(nfc->oob_buf, new_oob_len,
			       GFP_KERNEL | GFP_DMA);
		अगर (!buf) अणु
			kमुक्त(nfc->page_buf);
			nfc->page_buf = शून्य;
			वापस -ENOMEM;
		पूर्ण
		nfc->oob_buf = buf;
		nfc->oob_buf_size = new_oob_len;
	पूर्ण

	अगर (!nfc->page_buf) अणु
		nfc->page_buf = kzalloc(new_page_len, GFP_KERNEL | GFP_DMA);
		अगर (!nfc->page_buf)
			वापस -ENOMEM;
		nfc->page_buf_size = new_page_len;
	पूर्ण

	अगर (!nfc->oob_buf) अणु
		nfc->oob_buf = kzalloc(new_oob_len, GFP_KERNEL | GFP_DMA);
		अगर (!nfc->oob_buf) अणु
			kमुक्त(nfc->page_buf);
			nfc->page_buf = शून्य;
			वापस -ENOMEM;
		पूर्ण
		nfc->oob_buf_size = new_oob_len;
	पूर्ण

	chip->ecc.ग_लिखो_page_raw = rk_nfc_ग_लिखो_page_raw;
	chip->ecc.ग_लिखो_page = rk_nfc_ग_लिखो_page_hwecc;
	chip->ecc.ग_लिखो_oob = rk_nfc_ग_लिखो_oob;

	chip->ecc.पढ़ो_page_raw = rk_nfc_पढ़ो_page_raw;
	chip->ecc.पढ़ो_page = rk_nfc_पढ़ो_page_hwecc;
	chip->ecc.पढ़ो_oob = rk_nfc_पढ़ो_oob;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops rk_nfc_controller_ops = अणु
	.attach_chip = rk_nfc_attach_chip,
	.exec_op = rk_nfc_exec_op,
	.setup_पूर्णांकerface = rk_nfc_setup_पूर्णांकerface,
पूर्ण;

अटल पूर्णांक rk_nfc_nand_chip_init(काष्ठा device *dev, काष्ठा rk_nfc *nfc,
				 काष्ठा device_node *np)
अणु
	काष्ठा rk_nfc_nand_chip *rknand;
	काष्ठा nand_chip *chip;
	काष्ठा mtd_info *mtd;
	पूर्णांक nsels;
	u32 पंचांगp;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!of_get_property(np, "reg", &nsels))
		वापस -ENODEV;
	nsels /= माप(u32);
	अगर (!nsels || nsels > NFC_MAX_NSELS) अणु
		dev_err(dev, "invalid reg property size %d\n", nsels);
		वापस -EINVAL;
	पूर्ण

	rknand = devm_kzalloc(dev, माप(*rknand) + nsels * माप(u8),
			      GFP_KERNEL);
	अगर (!rknand)
		वापस -ENOMEM;

	rknand->nsels = nsels;
	क्रम (i = 0; i < nsels; i++) अणु
		ret = of_property_पढ़ो_u32_index(np, "reg", i, &पंचांगp);
		अगर (ret) अणु
			dev_err(dev, "reg property failure : %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (पंचांगp >= NFC_MAX_NSELS) अणु
			dev_err(dev, "invalid CS: %u\n", पंचांगp);
			वापस -EINVAL;
		पूर्ण

		अगर (test_and_set_bit(पंचांगp, &nfc->asचिन्हित_cs)) अणु
			dev_err(dev, "CS %u already assigned\n", पंचांगp);
			वापस -EINVAL;
		पूर्ण

		rknand->sels[i] = पंचांगp;
	पूर्ण

	chip = &rknand->chip;
	chip->controller = &nfc->controller;

	nand_set_flash_node(chip, np);

	nand_set_controller_data(chip, nfc);

	chip->options |= न_अंकD_USES_DMA | न_अंकD_NO_SUBPAGE_WRITE;
	chip->bbt_options = न_अंकD_BBT_USE_FLASH | न_अंकD_BBT_NO_OOB;

	/* Set शेष mode in हाल dt entry is missing. */
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;

	mtd = nand_to_mtd(chip);
	mtd->owner = THIS_MODULE;
	mtd->dev.parent = dev;

	अगर (!mtd->name) अणु
		dev_err(nfc->dev, "NAND label property is mandatory\n");
		वापस -EINVAL;
	पूर्ण

	mtd_set_ooblayout(mtd, &rk_nfc_ooblayout_ops);
	rk_nfc_hw_init(nfc);
	ret = nand_scan(chip, nsels);
	अगर (ret)
		वापस ret;

	अगर (chip->options & न_अंकD_IS_BOOT_MEDIUM) अणु
		ret = of_property_पढ़ो_u32(np, "rockchip,boot-blks", &पंचांगp);
		rknand->boot_blks = ret ? 0 : पंचांगp;

		ret = of_property_पढ़ो_u32(np, "rockchip,boot-ecc-strength",
					   &पंचांगp);
		rknand->boot_ecc = ret ? chip->ecc.strength : पंचांगp;
	पूर्ण

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "MTD parse partition error\n");
		nand_cleanup(chip);
		वापस ret;
	पूर्ण

	list_add_tail(&rknand->node, &nfc->chips);

	वापस 0;
पूर्ण

अटल व्योम rk_nfc_chips_cleanup(काष्ठा rk_nfc *nfc)
अणु
	काष्ठा rk_nfc_nand_chip *rknand, *पंचांगp;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(rknand, पंचांगp, &nfc->chips, node) अणु
		chip = &rknand->chip;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		list_del(&rknand->node);
	पूर्ण
पूर्ण

अटल पूर्णांक rk_nfc_nand_chips_init(काष्ठा device *dev, काष्ठा rk_nfc *nfc)
अणु
	काष्ठा device_node *np = dev->of_node, *nand_np;
	पूर्णांक nchips = of_get_child_count(np);
	पूर्णांक ret;

	अगर (!nchips || nchips > NFC_MAX_NSELS) अणु
		dev_err(nfc->dev, "incorrect number of NAND chips (%d)\n",
			nchips);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(np, nand_np) अणु
		ret = rk_nfc_nand_chip_init(dev, nfc, nand_np);
		अगर (ret) अणु
			of_node_put(nand_np);
			rk_nfc_chips_cleanup(nfc);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nfc_cfg nfc_v6_cfg = अणु
		.type			= NFC_V6,
		.ecc_strengths		= अणु60, 40, 24, 16पूर्ण,
		.ecc_cfgs		= अणु
			0x00040011, 0x00040001, 0x00000011, 0x00000001,
		पूर्ण,
		.flctl_off		= 0x08,
		.bchctl_off		= 0x0C,
		.dma_cfg_off		= 0x10,
		.dma_data_buf_off	= 0x14,
		.dma_oob_buf_off	= 0x18,
		.dma_st_off		= 0x1C,
		.bch_st_off		= 0x20,
		.अक्रमmz_off		= 0x150,
		.पूर्णांक_en_off		= 0x16C,
		.पूर्णांक_clr_off		= 0x170,
		.पूर्णांक_st_off		= 0x174,
		.oob0_off		= 0x200,
		.oob1_off		= 0x230,
		.ecc0			= अणु
			.err_flag_bit	= 2,
			.low		= 3,
			.low_mask	= 0x1F,
			.low_bn		= 5,
			.high		= 27,
			.high_mask	= 0x1,
		पूर्ण,
		.ecc1			= अणु
			.err_flag_bit	= 15,
			.low		= 16,
			.low_mask	= 0x1F,
			.low_bn		= 5,
			.high		= 29,
			.high_mask	= 0x1,
		पूर्ण,
पूर्ण;

अटल काष्ठा nfc_cfg nfc_v8_cfg = अणु
		.type			= NFC_V8,
		.ecc_strengths		= अणु16, 16, 16, 16पूर्ण,
		.ecc_cfgs		= अणु
			0x00000001, 0x00000001, 0x00000001, 0x00000001,
		पूर्ण,
		.flctl_off		= 0x08,
		.bchctl_off		= 0x0C,
		.dma_cfg_off		= 0x10,
		.dma_data_buf_off	= 0x14,
		.dma_oob_buf_off	= 0x18,
		.dma_st_off		= 0x1C,
		.bch_st_off		= 0x20,
		.अक्रमmz_off		= 0x150,
		.पूर्णांक_en_off		= 0x16C,
		.पूर्णांक_clr_off		= 0x170,
		.पूर्णांक_st_off		= 0x174,
		.oob0_off		= 0x200,
		.oob1_off		= 0x230,
		.ecc0			= अणु
			.err_flag_bit	= 2,
			.low		= 3,
			.low_mask	= 0x1F,
			.low_bn		= 5,
			.high		= 27,
			.high_mask	= 0x1,
		पूर्ण,
		.ecc1			= अणु
			.err_flag_bit	= 15,
			.low		= 16,
			.low_mask	= 0x1F,
			.low_bn		= 5,
			.high		= 29,
			.high_mask	= 0x1,
		पूर्ण,
पूर्ण;

अटल काष्ठा nfc_cfg nfc_v9_cfg = अणु
		.type			= NFC_V9,
		.ecc_strengths		= अणु70, 60, 40, 16पूर्ण,
		.ecc_cfgs		= अणु
			0x00000001, 0x06000001, 0x04000001, 0x02000001,
		पूर्ण,
		.flctl_off		= 0x10,
		.bchctl_off		= 0x20,
		.dma_cfg_off		= 0x30,
		.dma_data_buf_off	= 0x34,
		.dma_oob_buf_off	= 0x38,
		.dma_st_off		= 0x3C,
		.bch_st_off		= 0x150,
		.अक्रमmz_off		= 0x208,
		.पूर्णांक_en_off		= 0x120,
		.पूर्णांक_clr_off		= 0x124,
		.पूर्णांक_st_off		= 0x128,
		.oob0_off		= 0x200,
		.oob1_off		= 0x204,
		.ecc0			= अणु
			.err_flag_bit	= 2,
			.low		= 3,
			.low_mask	= 0x7F,
			.low_bn		= 7,
			.high		= 0,
			.high_mask	= 0x0,
		पूर्ण,
		.ecc1			= अणु
			.err_flag_bit	= 18,
			.low		= 19,
			.low_mask	= 0x7F,
			.low_bn		= 7,
			.high		= 0,
			.high_mask	= 0x0,
		पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rk_nfc_id_table[] = अणु
	अणु
		.compatible = "rockchip,px30-nfc",
		.data = &nfc_v9_cfg
	पूर्ण,
	अणु
		.compatible = "rockchip,rk2928-nfc",
		.data = &nfc_v6_cfg
	पूर्ण,
	अणु
		.compatible = "rockchip,rv1108-nfc",
		.data = &nfc_v8_cfg
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rk_nfc_id_table);

अटल पूर्णांक rk_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rk_nfc *nfc;
	पूर्णांक ret, irq;

	nfc = devm_kzalloc(dev, माप(*nfc), GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nand_controller_init(&nfc->controller);
	INIT_LIST_HEAD(&nfc->chips);
	nfc->controller.ops = &rk_nfc_controller_ops;

	nfc->cfg = of_device_get_match_data(dev);
	nfc->dev = dev;

	init_completion(&nfc->करोne);

	nfc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(nfc->regs)) अणु
		ret = PTR_ERR(nfc->regs);
		जाओ release_nfc;
	पूर्ण

	nfc->nfc_clk = devm_clk_get(dev, "nfc");
	अगर (IS_ERR(nfc->nfc_clk)) अणु
		dev_dbg(dev, "no NFC clk\n");
		/* Some earlier models, such as rk3066, have no NFC clk. */
	पूर्ण

	nfc->ahb_clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(nfc->ahb_clk)) अणु
		dev_err(dev, "no ahb clk\n");
		ret = PTR_ERR(nfc->ahb_clk);
		जाओ release_nfc;
	पूर्ण

	ret = rk_nfc_enable_clks(dev, nfc);
	अगर (ret)
		जाओ release_nfc;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(dev, "no NFC irq resource\n");
		ret = -EINVAL;
		जाओ clk_disable;
	पूर्ण

	ग_लिखोl(0, nfc->regs + nfc->cfg->पूर्णांक_en_off);
	ret = devm_request_irq(dev, irq, rk_nfc_irq, 0x0, "rk-nand", nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to request NFC irq\n");
		जाओ clk_disable;
	पूर्ण

	platक्रमm_set_drvdata(pdev, nfc);

	ret = rk_nfc_nand_chips_init(dev, nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to init NAND chips\n");
		जाओ clk_disable;
	पूर्ण
	वापस 0;

clk_disable:
	rk_nfc_disable_clks(nfc);
release_nfc:
	वापस ret;
पूर्ण

अटल पूर्णांक rk_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk_nfc *nfc = platक्रमm_get_drvdata(pdev);

	kमुक्त(nfc->page_buf);
	kमुक्त(nfc->oob_buf);
	rk_nfc_chips_cleanup(nfc);
	rk_nfc_disable_clks(nfc);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rk_nfc_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk_nfc *nfc = dev_get_drvdata(dev);

	rk_nfc_disable_clks(nfc);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rk_nfc_resume(काष्ठा device *dev)
अणु
	काष्ठा rk_nfc *nfc = dev_get_drvdata(dev);
	काष्ठा rk_nfc_nand_chip *rknand;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;
	u32 i;

	ret = rk_nfc_enable_clks(dev, nfc);
	अगर (ret)
		वापस ret;

	/* Reset न_अंकD chip अगर VCC was घातered off. */
	list_क्रम_each_entry(rknand, &nfc->chips, node) अणु
		chip = &rknand->chip;
		क्रम (i = 0; i < rknand->nsels; i++)
			nand_reset(chip, i);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rk_nfc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rk_nfc_suspend, rk_nfc_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver rk_nfc_driver = अणु
	.probe = rk_nfc_probe,
	.हटाओ = rk_nfc_हटाओ,
	.driver = अणु
		.name = "rockchip-nfc",
		.of_match_table = rk_nfc_id_table,
		.pm = &rk_nfc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rk_nfc_driver);

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Yifeng Zhao <yifeng.zhao@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip Nand Flash Controller Driver");
MODULE_ALIAS("platform:rockchip-nand-controller");
