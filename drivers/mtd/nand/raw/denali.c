<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * न_अंकD Flash Controller Device Driver
 * Copyright तऊ 2009-2010, Intel Corporation and its suppliers.
 *
 * Copyright (c) 2017-2019 Socionext Inc.
 *   Reworked by Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "denali.h"

#घोषणा DENALI_न_अंकD_NAME    "denali-nand"

/* क्रम Indexed Addressing */
#घोषणा DENALI_INDEXED_CTRL	0x00
#घोषणा DENALI_INDEXED_DATA	0x10

#घोषणा DENALI_MAP00		(0 << 26)	/* direct access to buffer */
#घोषणा DENALI_MAP01		(1 << 26)	/* पढ़ो/ग_लिखो pages in PIO */
#घोषणा DENALI_MAP10		(2 << 26)	/* high-level control plane */
#घोषणा DENALI_MAP11		(3 << 26)	/* direct controller access */

/* MAP11 access cycle type */
#घोषणा DENALI_MAP11_CMD	((DENALI_MAP11) | 0)	/* command cycle */
#घोषणा DENALI_MAP11_ADDR	((DENALI_MAP11) | 1)	/* address cycle */
#घोषणा DENALI_MAP11_DATA	((DENALI_MAP11) | 2)	/* data cycle */

#घोषणा DENALI_BANK(denali)	((denali)->active_bank << 24)

#घोषणा DENALI_INVALID_BANK	-1

अटल काष्ठा denali_chip *to_denali_chip(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा denali_chip, chip);
पूर्ण

अटल काष्ठा denali_controller *to_denali_controller(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip->controller, काष्ठा denali_controller,
			    controller);
पूर्ण

/*
 * Direct Addressing - the slave address क्रमms the control inक्रमmation (command
 * type, bank, block, and page address).  The slave data is the actual data to
 * be transferred.  This mode requires 28 bits of address region allocated.
 */
अटल u32 denali_direct_पढ़ो(काष्ठा denali_controller *denali, u32 addr)
अणु
	वापस ioपढ़ो32(denali->host + addr);
पूर्ण

अटल व्योम denali_direct_ग_लिखो(काष्ठा denali_controller *denali, u32 addr,
				u32 data)
अणु
	ioग_लिखो32(data, denali->host + addr);
पूर्ण

/*
 * Indexed Addressing - address translation module पूर्णांकervenes in passing the
 * control inक्रमmation.  This mode reduces the required address range.  The
 * control inक्रमmation and transferred data are latched by the रेजिस्टरs in
 * the translation module.
 */
अटल u32 denali_indexed_पढ़ो(काष्ठा denali_controller *denali, u32 addr)
अणु
	ioग_लिखो32(addr, denali->host + DENALI_INDEXED_CTRL);
	वापस ioपढ़ो32(denali->host + DENALI_INDEXED_DATA);
पूर्ण

अटल व्योम denali_indexed_ग_लिखो(काष्ठा denali_controller *denali, u32 addr,
				 u32 data)
अणु
	ioग_लिखो32(addr, denali->host + DENALI_INDEXED_CTRL);
	ioग_लिखो32(data, denali->host + DENALI_INDEXED_DATA);
पूर्ण

अटल व्योम denali_enable_irq(काष्ठा denali_controller *denali)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < denali->nbanks; i++)
		ioग_लिखो32(U32_MAX, denali->reg + INTR_EN(i));
	ioग_लिखो32(GLOBAL_INT_EN_FLAG, denali->reg + GLOBAL_INT_ENABLE);
पूर्ण

अटल व्योम denali_disable_irq(काष्ठा denali_controller *denali)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < denali->nbanks; i++)
		ioग_लिखो32(0, denali->reg + INTR_EN(i));
	ioग_लिखो32(0, denali->reg + GLOBAL_INT_ENABLE);
पूर्ण

अटल व्योम denali_clear_irq(काष्ठा denali_controller *denali,
			     पूर्णांक bank, u32 irq_status)
अणु
	/* ग_लिखो one to clear bits */
	ioग_लिखो32(irq_status, denali->reg + INTR_STATUS(bank));
पूर्ण

अटल व्योम denali_clear_irq_all(काष्ठा denali_controller *denali)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < denali->nbanks; i++)
		denali_clear_irq(denali, i, U32_MAX);
पूर्ण

अटल irqवापस_t denali_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा denali_controller *denali = dev_id;
	irqवापस_t ret = IRQ_NONE;
	u32 irq_status;
	पूर्णांक i;

	spin_lock(&denali->irq_lock);

	क्रम (i = 0; i < denali->nbanks; i++) अणु
		irq_status = ioपढ़ो32(denali->reg + INTR_STATUS(i));
		अगर (irq_status)
			ret = IRQ_HANDLED;

		denali_clear_irq(denali, i, irq_status);

		अगर (i != denali->active_bank)
			जारी;

		denali->irq_status |= irq_status;

		अगर (denali->irq_status & denali->irq_mask)
			complete(&denali->complete);
	पूर्ण

	spin_unlock(&denali->irq_lock);

	वापस ret;
पूर्ण

अटल व्योम denali_reset_irq(काष्ठा denali_controller *denali)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&denali->irq_lock, flags);
	denali->irq_status = 0;
	denali->irq_mask = 0;
	spin_unlock_irqrestore(&denali->irq_lock, flags);
पूर्ण

अटल u32 denali_रुको_क्रम_irq(काष्ठा denali_controller *denali, u32 irq_mask)
अणु
	अचिन्हित दीर्घ समय_left, flags;
	u32 irq_status;

	spin_lock_irqsave(&denali->irq_lock, flags);

	irq_status = denali->irq_status;

	अगर (irq_mask & irq_status) अणु
		/* वापस immediately अगर the IRQ has alपढ़ोy happened. */
		spin_unlock_irqrestore(&denali->irq_lock, flags);
		वापस irq_status;
	पूर्ण

	denali->irq_mask = irq_mask;
	reinit_completion(&denali->complete);
	spin_unlock_irqrestore(&denali->irq_lock, flags);

	समय_left = रुको_क्रम_completion_समयout(&denali->complete,
						msecs_to_jअगरfies(1000));
	अगर (!समय_left) अणु
		dev_err(denali->dev, "timeout while waiting for irq 0x%x\n",
			irq_mask);
		वापस 0;
	पूर्ण

	वापस denali->irq_status;
पूर्ण

अटल व्योम denali_select_target(काष्ठा nand_chip *chip, पूर्णांक cs)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा denali_chip_sel *sel = &to_denali_chip(chip)->sels[cs];
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	denali->active_bank = sel->bank;

	ioग_लिखो32(1 << (chip->phys_erase_shअगरt - chip->page_shअगरt),
		  denali->reg + PAGES_PER_BLOCK);
	ioग_लिखो32(chip->options & न_अंकD_BUSWIDTH_16 ? 1 : 0,
		  denali->reg + DEVICE_WIDTH);
	ioग_लिखो32(mtd->ग_लिखोsize, denali->reg + DEVICE_MAIN_AREA_SIZE);
	ioग_लिखो32(mtd->oobsize, denali->reg + DEVICE_SPARE_AREA_SIZE);
	ioग_लिखो32(chip->options & न_अंकD_ROW_ADDR_3 ?
		  0 : TWO_ROW_ADDR_CYCLES__FLAG,
		  denali->reg + TWO_ROW_ADDR_CYCLES);
	ioग_लिखो32(FIELD_PREP(ECC_CORRECTION__ERASE_THRESHOLD, 1) |
		  FIELD_PREP(ECC_CORRECTION__VALUE, chip->ecc.strength),
		  denali->reg + ECC_CORRECTION);
	ioग_लिखो32(chip->ecc.size, denali->reg + CFG_DATA_BLOCK_SIZE);
	ioग_लिखो32(chip->ecc.size, denali->reg + CFG_LAST_DATA_BLOCK_SIZE);
	ioग_लिखो32(chip->ecc.steps, denali->reg + CFG_NUM_DATA_BLOCKS);

	अगर (chip->options & न_अंकD_KEEP_TIMINGS)
		वापस;

	/* update timing रेजिस्टरs unless न_अंकD_KEEP_TIMINGS is set */
	ioग_लिखो32(sel->hwhr2_and_we_2_re, denali->reg + TWHR2_AND_WE_2_RE);
	ioग_लिखो32(sel->tcwaw_and_addr_2_data,
		  denali->reg + TCWAW_AND_ADDR_2_DATA);
	ioग_लिखो32(sel->re_2_we, denali->reg + RE_2_WE);
	ioग_लिखो32(sel->acc_clks, denali->reg + ACC_CLKS);
	ioग_लिखो32(sel->rdwr_en_lo_cnt, denali->reg + RDWR_EN_LO_CNT);
	ioग_लिखो32(sel->rdwr_en_hi_cnt, denali->reg + RDWR_EN_HI_CNT);
	ioग_लिखो32(sel->cs_setup_cnt, denali->reg + CS_SETUP_CNT);
	ioग_लिखो32(sel->re_2_re, denali->reg + RE_2_RE);
पूर्ण

अटल पूर्णांक denali_change_column(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक offset,
				व्योम *buf, अचिन्हित पूर्णांक len, bool ग_लिखो)
अणु
	अगर (ग_लिखो)
		वापस nand_change_ग_लिखो_column_op(chip, offset, buf, len,
						   false);
	अन्यथा
		वापस nand_change_पढ़ो_column_op(chip, offset, buf, len,
						  false);
पूर्ण

अटल पूर्णांक denali_payload_xfer(काष्ठा nand_chip *chip, व्योम *buf, bool ग_लिखो)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक ग_लिखोsize = mtd->ग_लिखोsize;
	पूर्णांक oob_skip = denali->oob_skip_bytes;
	पूर्णांक ret, i, pos, len;

	क्रम (i = 0; i < ecc->steps; i++) अणु
		pos = i * (ecc->size + ecc->bytes);
		len = ecc->size;

		अगर (pos >= ग_लिखोsize) अणु
			pos += oob_skip;
		पूर्ण अन्यथा अगर (pos + len > ग_लिखोsize) अणु
			/* This chunk overwraps the BBM area. Must be split */
			ret = denali_change_column(chip, pos, buf,
						   ग_लिखोsize - pos, ग_लिखो);
			अगर (ret)
				वापस ret;

			buf += ग_लिखोsize - pos;
			len -= ग_लिखोsize - pos;
			pos = ग_लिखोsize + oob_skip;
		पूर्ण

		ret = denali_change_column(chip, pos, buf, len, ग_लिखो);
		अगर (ret)
			वापस ret;

		buf += len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक denali_oob_xfer(काष्ठा nand_chip *chip, व्योम *buf, bool ग_लिखो)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक ग_लिखोsize = mtd->ग_लिखोsize;
	पूर्णांक oobsize = mtd->oobsize;
	पूर्णांक oob_skip = denali->oob_skip_bytes;
	पूर्णांक ret, i, pos, len;

	/* BBM at the beginning of the OOB area */
	ret = denali_change_column(chip, ग_लिखोsize, buf, oob_skip, ग_लिखो);
	अगर (ret)
		वापस ret;

	buf += oob_skip;

	क्रम (i = 0; i < ecc->steps; i++) अणु
		pos = ecc->size + i * (ecc->size + ecc->bytes);

		अगर (i == ecc->steps - 1)
			/* The last chunk includes OOB मुक्त */
			len = ग_लिखोsize + oobsize - pos - oob_skip;
		अन्यथा
			len = ecc->bytes;

		अगर (pos >= ग_लिखोsize) अणु
			pos += oob_skip;
		पूर्ण अन्यथा अगर (pos + len > ग_लिखोsize) अणु
			/* This chunk overwraps the BBM area. Must be split */
			ret = denali_change_column(chip, pos, buf,
						   ग_लिखोsize - pos, ग_लिखो);
			अगर (ret)
				वापस ret;

			buf += ग_लिखोsize - pos;
			len -= ग_लिखोsize - pos;
			pos = ग_लिखोsize + oob_skip;
		पूर्ण

		ret = denali_change_column(chip, pos, buf, len, ग_लिखो);
		अगर (ret)
			वापस ret;

		buf += len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक denali_पढ़ो_raw(काष्ठा nand_chip *chip, व्योम *buf, व्योम *oob_buf,
			   पूर्णांक page)
अणु
	पूर्णांक ret;

	अगर (!buf && !oob_buf)
		वापस -EINVAL;

	ret = nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	अगर (buf) अणु
		ret = denali_payload_xfer(chip, buf, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (oob_buf) अणु
		ret = denali_oob_xfer(chip, oob_buf, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक denali_ग_लिखो_raw(काष्ठा nand_chip *chip, स्थिर व्योम *buf,
			    स्थिर व्योम *oob_buf, पूर्णांक page)
अणु
	पूर्णांक ret;

	अगर (!buf && !oob_buf)
		वापस -EINVAL;

	ret = nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	अगर (buf) अणु
		ret = denali_payload_xfer(chip, (व्योम *)buf, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (oob_buf) अणु
		ret = denali_oob_xfer(chip, (व्योम *)oob_buf, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक denali_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf,
				पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस denali_पढ़ो_raw(chip, buf, oob_required ? chip->oob_poi : शून्य,
			       page);
पूर्ण

अटल पूर्णांक denali_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				 पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस denali_ग_लिखो_raw(chip, buf, oob_required ? chip->oob_poi : शून्य,
				page);
पूर्ण

अटल पूर्णांक denali_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस denali_पढ़ो_raw(chip, शून्य, chip->oob_poi, page);
पूर्ण

अटल पूर्णांक denali_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस denali_ग_लिखो_raw(chip, शून्य, chip->oob_poi, page);
पूर्ण

अटल पूर्णांक denali_check_erased_page(काष्ठा nand_chip *chip, u8 *buf,
				    अचिन्हित दीर्घ uncor_ecc_flags,
				    अचिन्हित पूर्णांक max_bitflips)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा mtd_ecc_stats *ecc_stats = &nand_to_mtd(chip)->ecc_stats;
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *ecc_code = chip->oob_poi + denali->oob_skip_bytes;
	पूर्णांक i, stat;

	क्रम (i = 0; i < ecc->steps; i++) अणु
		अगर (!(uncor_ecc_flags & BIT(i)))
			जारी;

		stat = nand_check_erased_ecc_chunk(buf, ecc->size, ecc_code,
						   ecc->bytes, शून्य, 0,
						   ecc->strength);
		अगर (stat < 0) अणु
			ecc_stats->failed++;
		पूर्ण अन्यथा अणु
			ecc_stats->corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण

		buf += ecc->size;
		ecc_code += ecc->bytes;
	पूर्ण

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक denali_hw_ecc_fixup(काष्ठा nand_chip *chip,
			       अचिन्हित दीर्घ *uncor_ecc_flags)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा mtd_ecc_stats *ecc_stats = &nand_to_mtd(chip)->ecc_stats;
	पूर्णांक bank = denali->active_bank;
	u32 ecc_cor;
	अचिन्हित पूर्णांक max_bitflips;

	ecc_cor = ioपढ़ो32(denali->reg + ECC_COR_INFO(bank));
	ecc_cor >>= ECC_COR_INFO__SHIFT(bank);

	अगर (ecc_cor & ECC_COR_INFO__UNCOR_ERR) अणु
		/*
		 * This flag is set when uncorrectable error occurs at least in
		 * one ECC sector.  We can not know "how many sectors", or
		 * "which sector(s)".  We need erase-page check क्रम all sectors.
		 */
		*uncor_ecc_flags = GENMASK(chip->ecc.steps - 1, 0);
		वापस 0;
	पूर्ण

	max_bitflips = FIELD_GET(ECC_COR_INFO__MAX_ERRORS, ecc_cor);

	/*
	 * The रेजिस्टर holds the maximum of per-sector corrected bitflips.
	 * This is suitable क्रम the वापस value of the ->पढ़ो_page() callback.
	 * Unक्रमtunately, we can not know the total number of corrected bits in
	 * the page.  Increase the stats by max_bitflips. (compromised solution)
	 */
	ecc_stats->corrected += max_bitflips;

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक denali_sw_ecc_fixup(काष्ठा nand_chip *chip,
			       अचिन्हित दीर्घ *uncor_ecc_flags, u8 *buf)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा mtd_ecc_stats *ecc_stats = &nand_to_mtd(chip)->ecc_stats;
	अचिन्हित पूर्णांक ecc_size = chip->ecc.size;
	अचिन्हित पूर्णांक bitflips = 0;
	अचिन्हित पूर्णांक max_bitflips = 0;
	u32 err_addr, err_cor_info;
	अचिन्हित पूर्णांक err_byte, err_sector, err_device;
	u8 err_cor_value;
	अचिन्हित पूर्णांक prev_sector = 0;
	u32 irq_status;

	denali_reset_irq(denali);

	करो अणु
		err_addr = ioपढ़ो32(denali->reg + ECC_ERROR_ADDRESS);
		err_sector = FIELD_GET(ECC_ERROR_ADDRESS__SECTOR, err_addr);
		err_byte = FIELD_GET(ECC_ERROR_ADDRESS__OFFSET, err_addr);

		err_cor_info = ioपढ़ो32(denali->reg + ERR_CORRECTION_INFO);
		err_cor_value = FIELD_GET(ERR_CORRECTION_INFO__BYTE,
					  err_cor_info);
		err_device = FIELD_GET(ERR_CORRECTION_INFO__DEVICE,
				       err_cor_info);

		/* reset the bitflip counter when crossing ECC sector */
		अगर (err_sector != prev_sector)
			bitflips = 0;

		अगर (err_cor_info & ERR_CORRECTION_INFO__UNCOR) अणु
			/*
			 * Check later अगर this is a real ECC error, or
			 * an erased sector.
			 */
			*uncor_ecc_flags |= BIT(err_sector);
		पूर्ण अन्यथा अगर (err_byte < ecc_size) अणु
			/*
			 * If err_byte is larger than ecc_size, means error
			 * happened in OOB, so we ignore it. It's no need क्रम
			 * us to correct it err_device is represented the न_अंकD
			 * error bits are happened in अगर there are more than
			 * one न_अंकD connected.
			 */
			पूर्णांक offset;
			अचिन्हित पूर्णांक flips_in_byte;

			offset = (err_sector * ecc_size + err_byte) *
					denali->devs_per_cs + err_device;

			/* correct the ECC error */
			flips_in_byte = hweight8(buf[offset] ^ err_cor_value);
			buf[offset] ^= err_cor_value;
			ecc_stats->corrected += flips_in_byte;
			bitflips += flips_in_byte;

			max_bitflips = max(max_bitflips, bitflips);
		पूर्ण

		prev_sector = err_sector;
	पूर्ण जबतक (!(err_cor_info & ERR_CORRECTION_INFO__LAST_ERR));

	/*
	 * Once handle all ECC errors, controller will trigger an
	 * ECC_TRANSACTION_DONE पूर्णांकerrupt.
	 */
	irq_status = denali_रुको_क्रम_irq(denali, INTR__ECC_TRANSACTION_DONE);
	अगर (!(irq_status & INTR__ECC_TRANSACTION_DONE))
		वापस -EIO;

	वापस max_bitflips;
पूर्ण

अटल व्योम denali_setup_dma64(काष्ठा denali_controller *denali,
			       dma_addr_t dma_addr, पूर्णांक page, bool ग_लिखो)
अणु
	u32 mode;
	स्थिर पूर्णांक page_count = 1;

	mode = DENALI_MAP10 | DENALI_BANK(denali) | page;

	/* DMA is a three step process */

	/*
	 * 1. setup transfer type, पूर्णांकerrupt when complete,
	 *    burst len = 64 bytes, the number of pages
	 */
	denali->host_ग_लिखो(denali, mode,
			   0x01002000 | (64 << 16) |
			   (ग_लिखो ? BIT(8) : 0) | page_count);

	/* 2. set memory low address */
	denali->host_ग_लिखो(denali, mode, lower_32_bits(dma_addr));

	/* 3. set memory high address */
	denali->host_ग_लिखो(denali, mode, upper_32_bits(dma_addr));
पूर्ण

अटल व्योम denali_setup_dma32(काष्ठा denali_controller *denali,
			       dma_addr_t dma_addr, पूर्णांक page, bool ग_लिखो)
अणु
	u32 mode;
	स्थिर पूर्णांक page_count = 1;

	mode = DENALI_MAP10 | DENALI_BANK(denali);

	/* DMA is a four step process */

	/* 1. setup transfer type and # of pages */
	denali->host_ग_लिखो(denali, mode | page,
			   0x2000 | (ग_लिखो ? BIT(8) : 0) | page_count);

	/* 2. set memory high address bits 23:8 */
	denali->host_ग_लिखो(denali, mode | ((dma_addr >> 16) << 8), 0x2200);

	/* 3. set memory low address bits 23:8 */
	denali->host_ग_लिखो(denali, mode | ((dma_addr & 0xffff) << 8), 0x2300);

	/* 4. पूर्णांकerrupt when complete, burst len = 64 bytes */
	denali->host_ग_लिखो(denali, mode | 0x14000, 0x2400);
पूर्ण

अटल पूर्णांक denali_pio_पढ़ो(काष्ठा denali_controller *denali, u32 *buf,
			   माप_प्रकार size, पूर्णांक page)
अणु
	u32 addr = DENALI_MAP01 | DENALI_BANK(denali) | page;
	u32 irq_status, ecc_err_mask;
	पूर्णांक i;

	अगर (denali->caps & DENALI_CAP_HW_ECC_FIXUP)
		ecc_err_mask = INTR__ECC_UNCOR_ERR;
	अन्यथा
		ecc_err_mask = INTR__ECC_ERR;

	denali_reset_irq(denali);

	क्रम (i = 0; i < size / 4; i++)
		buf[i] = denali->host_पढ़ो(denali, addr);

	irq_status = denali_रुको_क्रम_irq(denali, INTR__PAGE_XFER_INC);
	अगर (!(irq_status & INTR__PAGE_XFER_INC))
		वापस -EIO;

	अगर (irq_status & INTR__ERASED_PAGE)
		स_रखो(buf, 0xff, size);

	वापस irq_status & ecc_err_mask ? -EBADMSG : 0;
पूर्ण

अटल पूर्णांक denali_pio_ग_लिखो(काष्ठा denali_controller *denali, स्थिर u32 *buf,
			    माप_प्रकार size, पूर्णांक page)
अणु
	u32 addr = DENALI_MAP01 | DENALI_BANK(denali) | page;
	u32 irq_status;
	पूर्णांक i;

	denali_reset_irq(denali);

	क्रम (i = 0; i < size / 4; i++)
		denali->host_ग_लिखो(denali, addr, buf[i]);

	irq_status = denali_रुको_क्रम_irq(denali,
					 INTR__PROGRAM_COMP |
					 INTR__PROGRAM_FAIL);
	अगर (!(irq_status & INTR__PROGRAM_COMP))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक denali_pio_xfer(काष्ठा denali_controller *denali, व्योम *buf,
			   माप_प्रकार size, पूर्णांक page, bool ग_लिखो)
अणु
	अगर (ग_लिखो)
		वापस denali_pio_ग_लिखो(denali, buf, size, page);
	अन्यथा
		वापस denali_pio_पढ़ो(denali, buf, size, page);
पूर्ण

अटल पूर्णांक denali_dma_xfer(काष्ठा denali_controller *denali, व्योम *buf,
			   माप_प्रकार size, पूर्णांक page, bool ग_लिखो)
अणु
	dma_addr_t dma_addr;
	u32 irq_mask, irq_status, ecc_err_mask;
	क्रमागत dma_data_direction dir = ग_लिखो ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
	पूर्णांक ret = 0;

	dma_addr = dma_map_single(denali->dev, buf, size, dir);
	अगर (dma_mapping_error(denali->dev, dma_addr)) अणु
		dev_dbg(denali->dev, "Failed to DMA-map buffer. Trying PIO.\n");
		वापस denali_pio_xfer(denali, buf, size, page, ग_लिखो);
	पूर्ण

	अगर (ग_लिखो) अणु
		/*
		 * INTR__PROGRAM_COMP is never निश्चितed क्रम the DMA transfer.
		 * We can use INTR__DMA_CMD_COMP instead.  This flag is निश्चितed
		 * when the page program is completed.
		 */
		irq_mask = INTR__DMA_CMD_COMP | INTR__PROGRAM_FAIL;
		ecc_err_mask = 0;
	पूर्ण अन्यथा अगर (denali->caps & DENALI_CAP_HW_ECC_FIXUP) अणु
		irq_mask = INTR__DMA_CMD_COMP;
		ecc_err_mask = INTR__ECC_UNCOR_ERR;
	पूर्ण अन्यथा अणु
		irq_mask = INTR__DMA_CMD_COMP;
		ecc_err_mask = INTR__ECC_ERR;
	पूर्ण

	ioग_लिखो32(DMA_ENABLE__FLAG, denali->reg + DMA_ENABLE);
	/*
	 * The ->setup_dma() hook kicks DMA by using the data/command
	 * पूर्णांकerface, which beदीर्घs to a dअगरferent AXI port from the
	 * रेजिस्टर पूर्णांकerface.  Read back the रेजिस्टर to aव्योम a race.
	 */
	ioपढ़ो32(denali->reg + DMA_ENABLE);

	denali_reset_irq(denali);
	denali->setup_dma(denali, dma_addr, page, ग_लिखो);

	irq_status = denali_रुको_क्रम_irq(denali, irq_mask);
	अगर (!(irq_status & INTR__DMA_CMD_COMP))
		ret = -EIO;
	अन्यथा अगर (irq_status & ecc_err_mask)
		ret = -EBADMSG;

	ioग_लिखो32(0, denali->reg + DMA_ENABLE);

	dma_unmap_single(denali->dev, dma_addr, size, dir);

	अगर (irq_status & INTR__ERASED_PAGE)
		स_रखो(buf, 0xff, size);

	वापस ret;
पूर्ण

अटल पूर्णांक denali_page_xfer(काष्ठा nand_chip *chip, व्योम *buf, माप_प्रकार size,
			    पूर्णांक page, bool ग_लिखो)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);

	denali_select_target(chip, chip->cur_cs);

	अगर (denali->dma_avail)
		वापस denali_dma_xfer(denali, buf, size, page, ग_लिखो);
	अन्यथा
		वापस denali_pio_xfer(denali, buf, size, page, ग_लिखो);
पूर्ण

अटल पूर्णांक denali_पढ़ो_page(काष्ठा nand_chip *chip, u8 *buf,
			    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित दीर्घ uncor_ecc_flags = 0;
	पूर्णांक stat = 0;
	पूर्णांक ret;

	ret = denali_page_xfer(chip, buf, mtd->ग_लिखोsize, page, false);
	अगर (ret && ret != -EBADMSG)
		वापस ret;

	अगर (denali->caps & DENALI_CAP_HW_ECC_FIXUP)
		stat = denali_hw_ecc_fixup(chip, &uncor_ecc_flags);
	अन्यथा अगर (ret == -EBADMSG)
		stat = denali_sw_ecc_fixup(chip, &uncor_ecc_flags, buf);

	अगर (stat < 0)
		वापस stat;

	अगर (uncor_ecc_flags) अणु
		ret = denali_पढ़ो_oob(chip, page);
		अगर (ret)
			वापस ret;

		stat = denali_check_erased_page(chip, buf,
						uncor_ecc_flags, stat);
	पूर्ण

	वापस stat;
पूर्ण

अटल पूर्णांक denali_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर u8 *buf,
			     पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस denali_page_xfer(chip, (व्योम *)buf, mtd->ग_लिखोsize, page, true);
पूर्ण

अटल पूर्णांक denali_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr,
				  स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	अटल स्थिर अचिन्हित पूर्णांक data_setup_on_host = 10000;
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा denali_chip_sel *sel;
	स्थिर काष्ठा nand_sdr_timings *timings;
	अचिन्हित दीर्घ t_x, mult_x;
	पूर्णांक acc_clks, re_2_we, re_2_re, we_2_re, addr_2_data;
	पूर्णांक rdwr_en_lo, rdwr_en_hi, rdwr_en_lo_hi, cs_setup;
	पूर्णांक addr_2_data_mask;
	u32 पंचांगp;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस PTR_ERR(timings);

	/* clk_x period in picoseconds */
	t_x = DIV_ROUND_DOWN_ULL(1000000000000ULL, denali->clk_x_rate);
	अगर (!t_x)
		वापस -EINVAL;

	/*
	 * The bus पूर्णांकerface घड़ी, clk_x, is phase aligned with the core घड़ी.
	 * The clk_x is an पूर्णांकegral multiple N of the core clk.  The value N is
	 * configured at IP delivery समय, and its available value is 4, 5, 6.
	 */
	mult_x = DIV_ROUND_CLOSEST_ULL(denali->clk_x_rate, denali->clk_rate);
	अगर (mult_x < 4 || mult_x > 6)
		वापस -EINVAL;

	अगर (chipnr == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	sel = &to_denali_chip(chip)->sels[chipnr];

	/* tRWH -> RE_2_WE */
	re_2_we = DIV_ROUND_UP(timings->tRHW_min, t_x);
	re_2_we = min_t(पूर्णांक, re_2_we, RE_2_WE__VALUE);

	पंचांगp = ioपढ़ो32(denali->reg + RE_2_WE);
	पंचांगp &= ~RE_2_WE__VALUE;
	पंचांगp |= FIELD_PREP(RE_2_WE__VALUE, re_2_we);
	sel->re_2_we = पंचांगp;

	/* tRHZ -> RE_2_RE */
	re_2_re = DIV_ROUND_UP(timings->tRHZ_max, t_x);
	re_2_re = min_t(पूर्णांक, re_2_re, RE_2_RE__VALUE);

	पंचांगp = ioपढ़ो32(denali->reg + RE_2_RE);
	पंचांगp &= ~RE_2_RE__VALUE;
	पंचांगp |= FIELD_PREP(RE_2_RE__VALUE, re_2_re);
	sel->re_2_re = पंचांगp;

	/*
	 * tCCS, tWHR -> WE_2_RE
	 *
	 * With WE_2_RE properly set, the Denali controller स्वतःmatically takes
	 * care of the delay; the driver need not set न_अंकD_WAIT_TCCS.
	 */
	we_2_re = DIV_ROUND_UP(max(timings->tCCS_min, timings->tWHR_min), t_x);
	we_2_re = min_t(पूर्णांक, we_2_re, TWHR2_AND_WE_2_RE__WE_2_RE);

	पंचांगp = ioपढ़ो32(denali->reg + TWHR2_AND_WE_2_RE);
	पंचांगp &= ~TWHR2_AND_WE_2_RE__WE_2_RE;
	पंचांगp |= FIELD_PREP(TWHR2_AND_WE_2_RE__WE_2_RE, we_2_re);
	sel->hwhr2_and_we_2_re = पंचांगp;

	/* tADL -> ADDR_2_DATA */

	/* क्रम older versions, ADDR_2_DATA is only 6 bit wide */
	addr_2_data_mask = TCWAW_AND_ADDR_2_DATA__ADDR_2_DATA;
	अगर (denali->revision < 0x0501)
		addr_2_data_mask >>= 1;

	addr_2_data = DIV_ROUND_UP(timings->tADL_min, t_x);
	addr_2_data = min_t(पूर्णांक, addr_2_data, addr_2_data_mask);

	पंचांगp = ioपढ़ो32(denali->reg + TCWAW_AND_ADDR_2_DATA);
	पंचांगp &= ~TCWAW_AND_ADDR_2_DATA__ADDR_2_DATA;
	पंचांगp |= FIELD_PREP(TCWAW_AND_ADDR_2_DATA__ADDR_2_DATA, addr_2_data);
	sel->tcwaw_and_addr_2_data = पंचांगp;

	/* tREH, tWH -> RDWR_EN_HI_CNT */
	rdwr_en_hi = DIV_ROUND_UP(max(timings->tREH_min, timings->tWH_min),
				  t_x);
	rdwr_en_hi = min_t(पूर्णांक, rdwr_en_hi, RDWR_EN_HI_CNT__VALUE);

	पंचांगp = ioपढ़ो32(denali->reg + RDWR_EN_HI_CNT);
	पंचांगp &= ~RDWR_EN_HI_CNT__VALUE;
	पंचांगp |= FIELD_PREP(RDWR_EN_HI_CNT__VALUE, rdwr_en_hi);
	sel->rdwr_en_hi_cnt = पंचांगp;

	/*
	 * tREA -> ACC_CLKS
	 * tRP, tWP, tRHOH, tRC, tWC -> RDWR_EN_LO_CNT
	 */

	/*
	 * Determine the minimum of acc_clks to meet the setup timing when
	 * capturing the incoming data.
	 *
	 * The delay on the chip side is well-defined as tREA, but we need to
	 * take additional delay पूर्णांकo account. This includes a certain degree
	 * of unknowledge, such as संकेत propagation delays on the PCB and
	 * in the SoC, load capacity of the I/O pins, etc.
	 */
	acc_clks = DIV_ROUND_UP(timings->tREA_max + data_setup_on_host, t_x);

	/* Determine the minimum of rdwr_en_lo_cnt from RE#/WE# pulse width */
	rdwr_en_lo = DIV_ROUND_UP(max(timings->tRP_min, timings->tWP_min), t_x);

	/* Extend rdwr_en_lo to meet the data hold timing */
	rdwr_en_lo = max_t(पूर्णांक, rdwr_en_lo,
			   acc_clks - timings->tRHOH_min / t_x);

	/* Extend rdwr_en_lo to meet the requirement क्रम RE#/WE# cycle समय */
	rdwr_en_lo_hi = DIV_ROUND_UP(max(timings->tRC_min, timings->tWC_min),
				     t_x);
	rdwr_en_lo = max(rdwr_en_lo, rdwr_en_lo_hi - rdwr_en_hi);
	rdwr_en_lo = min_t(पूर्णांक, rdwr_en_lo, RDWR_EN_LO_CNT__VALUE);

	/* Center the data latch timing क्रम extra safety */
	acc_clks = (acc_clks + rdwr_en_lo +
		    DIV_ROUND_UP(timings->tRHOH_min, t_x)) / 2;
	acc_clks = min_t(पूर्णांक, acc_clks, ACC_CLKS__VALUE);

	पंचांगp = ioपढ़ो32(denali->reg + ACC_CLKS);
	पंचांगp &= ~ACC_CLKS__VALUE;
	पंचांगp |= FIELD_PREP(ACC_CLKS__VALUE, acc_clks);
	sel->acc_clks = पंचांगp;

	पंचांगp = ioपढ़ो32(denali->reg + RDWR_EN_LO_CNT);
	पंचांगp &= ~RDWR_EN_LO_CNT__VALUE;
	पंचांगp |= FIELD_PREP(RDWR_EN_LO_CNT__VALUE, rdwr_en_lo);
	sel->rdwr_en_lo_cnt = पंचांगp;

	/* tCS, tCEA -> CS_SETUP_CNT */
	cs_setup = max3((पूर्णांक)DIV_ROUND_UP(timings->tCS_min, t_x) - rdwr_en_lo,
			(पूर्णांक)DIV_ROUND_UP(timings->tCEA_max, t_x) - acc_clks,
			0);
	cs_setup = min_t(पूर्णांक, cs_setup, CS_SETUP_CNT__VALUE);

	पंचांगp = ioपढ़ो32(denali->reg + CS_SETUP_CNT);
	पंचांगp &= ~CS_SETUP_CNT__VALUE;
	पंचांगp |= FIELD_PREP(CS_SETUP_CNT__VALUE, cs_setup);
	sel->cs_setup_cnt = पंचांगp;

	वापस 0;
पूर्ण

पूर्णांक denali_calc_ecc_bytes(पूर्णांक step_size, पूर्णांक strength)
अणु
	/* BCH code.  Denali requires ecc.bytes to be multiple of 2 */
	वापस DIV_ROUND_UP(strength * fls(step_size * 8), 16) * 2;
पूर्ण
EXPORT_SYMBOL(denali_calc_ecc_bytes);

अटल पूर्णांक denali_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा denali_controller *denali = to_denali_controller(chip);

	अगर (section > 0)
		वापस -दुस्फल;

	oobregion->offset = denali->oob_skip_bytes;
	oobregion->length = chip->ecc.total;

	वापस 0;
पूर्ण

अटल पूर्णांक denali_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा denali_controller *denali = to_denali_controller(chip);

	अगर (section > 0)
		वापस -दुस्फल;

	oobregion->offset = chip->ecc.total + denali->oob_skip_bytes;
	oobregion->length = mtd->oobsize - oobregion->offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops denali_ooblayout_ops = अणु
	.ecc = denali_ooblayout_ecc,
	.मुक्त = denali_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक denali_multidev_fixup(काष्ठा nand_chip *chip)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_memory_organization *memorg;

	memorg = nanddev_get_memorg(&chip->base);

	/*
	 * Support क्रम multi device:
	 * When the IP configuration is x16 capable and two x8 chips are
	 * connected in parallel, DEVICES_CONNECTED should be set to 2.
	 * In this हाल, the core framework knows nothing about this fact,
	 * so we should tell it the _logical_ pagesize and anything necessary.
	 */
	denali->devs_per_cs = ioपढ़ो32(denali->reg + DEVICES_CONNECTED);

	/*
	 * On some SoCs, DEVICES_CONNECTED is not स्वतः-detected.
	 * For those, DEVICES_CONNECTED is left to 0.  Set 1 अगर it is the हाल.
	 */
	अगर (denali->devs_per_cs == 0) अणु
		denali->devs_per_cs = 1;
		ioग_लिखो32(1, denali->reg + DEVICES_CONNECTED);
	पूर्ण

	अगर (denali->devs_per_cs == 1)
		वापस 0;

	अगर (denali->devs_per_cs != 2) अणु
		dev_err(denali->dev, "unsupported number of devices %d\n",
			denali->devs_per_cs);
		वापस -EINVAL;
	पूर्ण

	/* 2 chips in parallel */
	memorg->pagesize <<= 1;
	memorg->oobsize <<= 1;
	mtd->size <<= 1;
	mtd->erasesize <<= 1;
	mtd->ग_लिखोsize <<= 1;
	mtd->oobsize <<= 1;
	chip->page_shअगरt += 1;
	chip->phys_erase_shअगरt += 1;
	chip->bbt_erase_shअगरt += 1;
	chip->chip_shअगरt += 1;
	chip->pagemask <<= 1;
	chip->ecc.size <<= 1;
	chip->ecc.bytes <<= 1;
	chip->ecc.strength <<= 1;
	denali->oob_skip_bytes <<= 1;

	वापस 0;
पूर्ण

अटल पूर्णांक denali_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = nand_ecc_choose_conf(chip, denali->ecc_caps,
				   mtd->oobsize - denali->oob_skip_bytes);
	अगर (ret) अणु
		dev_err(denali->dev, "Failed to setup ECC settings.\n");
		वापस ret;
	पूर्ण

	dev_dbg(denali->dev,
		"chosen ECC settings: step=%d, strength=%d, bytes=%d\n",
		chip->ecc.size, chip->ecc.strength, chip->ecc.bytes);

	ret = denali_multidev_fixup(chip);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम denali_exec_in8(काष्ठा denali_controller *denali, u32 type,
			    u8 *buf, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		buf[i] = denali->host_पढ़ो(denali, type | DENALI_BANK(denali));
पूर्ण

अटल व्योम denali_exec_in16(काष्ठा denali_controller *denali, u32 type,
			     u8 *buf, अचिन्हित पूर्णांक len)
अणु
	u32 data;
	पूर्णांक i;

	क्रम (i = 0; i < len; i += 2) अणु
		data = denali->host_पढ़ो(denali, type | DENALI_BANK(denali));
		/* bit 31:24 and 15:8 are used क्रम DDR */
		buf[i] = data;
		buf[i + 1] = data >> 16;
	पूर्ण
पूर्ण

अटल व्योम denali_exec_in(काष्ठा denali_controller *denali, u32 type,
			   u8 *buf, अचिन्हित पूर्णांक len, bool width16)
अणु
	अगर (width16)
		denali_exec_in16(denali, type, buf, len);
	अन्यथा
		denali_exec_in8(denali, type, buf, len);
पूर्ण

अटल व्योम denali_exec_out8(काष्ठा denali_controller *denali, u32 type,
			     स्थिर u8 *buf, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		denali->host_ग_लिखो(denali, type | DENALI_BANK(denali), buf[i]);
पूर्ण

अटल व्योम denali_exec_out16(काष्ठा denali_controller *denali, u32 type,
			      स्थिर u8 *buf, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i += 2)
		denali->host_ग_लिखो(denali, type | DENALI_BANK(denali),
				   buf[i + 1] << 16 | buf[i]);
पूर्ण

अटल व्योम denali_exec_out(काष्ठा denali_controller *denali, u32 type,
			    स्थिर u8 *buf, अचिन्हित पूर्णांक len, bool width16)
अणु
	अगर (width16)
		denali_exec_out16(denali, type, buf, len);
	अन्यथा
		denali_exec_out8(denali, type, buf, len);
पूर्ण

अटल पूर्णांक denali_exec_रुकोrdy(काष्ठा denali_controller *denali)
अणु
	u32 irq_stat;

	/* R/B# pin transitioned from low to high? */
	irq_stat = denali_रुको_क्रम_irq(denali, INTR__INT_ACT);

	/* Just in हाल nand_operation has multiple न_अंकD_OP_WAITRDY_INSTR. */
	denali_reset_irq(denali);

	वापस irq_stat & INTR__INT_ACT ? 0 : -EIO;
पूर्ण

अटल पूर्णांक denali_exec_instr(काष्ठा nand_chip *chip,
			     स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा denali_controller *denali = to_denali_controller(chip);

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		denali_exec_out8(denali, DENALI_MAP11_CMD,
				 &instr->ctx.cmd.opcode, 1);
		वापस 0;
	हाल न_अंकD_OP_ADDR_INSTR:
		denali_exec_out8(denali, DENALI_MAP11_ADDR,
				 instr->ctx.addr.addrs,
				 instr->ctx.addr.naddrs);
		वापस 0;
	हाल न_अंकD_OP_DATA_IN_INSTR:
		denali_exec_in(denali, DENALI_MAP11_DATA,
			       instr->ctx.data.buf.in,
			       instr->ctx.data.len,
			       !instr->ctx.data.क्रमce_8bit &&
			       chip->options & न_अंकD_BUSWIDTH_16);
		वापस 0;
	हाल न_अंकD_OP_DATA_OUT_INSTR:
		denali_exec_out(denali, DENALI_MAP11_DATA,
				instr->ctx.data.buf.out,
				instr->ctx.data.len,
				!instr->ctx.data.क्रमce_8bit &&
				chip->options & न_अंकD_BUSWIDTH_16);
		वापस 0;
	हाल न_अंकD_OP_WAITRDY_INSTR:
		वापस denali_exec_रुकोrdy(denali);
	शेष:
		WARN_ONCE(1, "unsupported NAND instruction type: %d\n",
			  instr->type);

		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक denali_exec_op(काष्ठा nand_chip *chip,
			  स्थिर काष्ठा nand_operation *op, bool check_only)
अणु
	पूर्णांक i, ret;

	अगर (check_only)
		वापस 0;

	denali_select_target(chip, op->cs);

	/*
	 * Some commands contain न_अंकD_OP_WAITRDY_INSTR.
	 * irq must be cleared here to catch the R/B# पूर्णांकerrupt there.
	 */
	denali_reset_irq(to_denali_controller(chip));

	क्रम (i = 0; i < op->ninstrs; i++) अणु
		ret = denali_exec_instr(chip, &op->instrs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops denali_controller_ops = अणु
	.attach_chip = denali_attach_chip,
	.exec_op = denali_exec_op,
	.setup_पूर्णांकerface = denali_setup_पूर्णांकerface,
पूर्ण;

पूर्णांक denali_chip_init(काष्ठा denali_controller *denali,
		     काष्ठा denali_chip *dchip)
अणु
	काष्ठा nand_chip *chip = &dchip->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा denali_chip *dchip2;
	पूर्णांक i, j, ret;

	chip->controller = &denali->controller;

	/* sanity checks क्रम bank numbers */
	क्रम (i = 0; i < dchip->nsels; i++) अणु
		अचिन्हित पूर्णांक bank = dchip->sels[i].bank;

		अगर (bank >= denali->nbanks) अणु
			dev_err(denali->dev, "unsupported bank %d\n", bank);
			वापस -EINVAL;
		पूर्ण

		क्रम (j = 0; j < i; j++) अणु
			अगर (bank == dchip->sels[j].bank) अणु
				dev_err(denali->dev,
					"bank %d is assigned twice in the same chip\n",
					bank);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		list_क्रम_each_entry(dchip2, &denali->chips, node) अणु
			क्रम (j = 0; j < dchip2->nsels; j++) अणु
				अगर (bank == dchip2->sels[j].bank) अणु
					dev_err(denali->dev,
						"bank %d is already used\n",
						bank);
					वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	mtd->dev.parent = denali->dev;

	/*
	 * Fallback to the शेष name अगर DT did not give "label" property.
	 * Use "label" property अगर multiple chips are connected.
	 */
	अगर (!mtd->name && list_empty(&denali->chips))
		mtd->name = "denali-nand";

	अगर (denali->dma_avail) अणु
		chip->options |= न_अंकD_USES_DMA;
		chip->buf_align = 16;
	पूर्ण

	/* clk rate info is needed क्रम setup_पूर्णांकerface */
	अगर (!denali->clk_rate || !denali->clk_x_rate)
		chip->options |= न_अंकD_KEEP_TIMINGS;

	chip->bbt_options |= न_अंकD_BBT_USE_FLASH;
	chip->bbt_options |= न_अंकD_BBT_NO_OOB;
	chip->options |= न_अंकD_NO_SUBPAGE_WRITE;
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	chip->ecc.placement = न_अंकD_ECC_PLACEMENT_INTERLEAVED;
	chip->ecc.पढ़ो_page = denali_पढ़ो_page;
	chip->ecc.ग_लिखो_page = denali_ग_लिखो_page;
	chip->ecc.पढ़ो_page_raw = denali_पढ़ो_page_raw;
	chip->ecc.ग_लिखो_page_raw = denali_ग_लिखो_page_raw;
	chip->ecc.पढ़ो_oob = denali_पढ़ो_oob;
	chip->ecc.ग_लिखो_oob = denali_ग_लिखो_oob;

	mtd_set_ooblayout(mtd, &denali_ooblayout_ops);

	ret = nand_scan(chip, dchip->nsels);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(denali->dev, "Failed to register MTD: %d\n", ret);
		जाओ cleanup_nand;
	पूर्ण

	list_add_tail(&dchip->node, &denali->chips);

	वापस 0;

cleanup_nand:
	nand_cleanup(chip);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(denali_chip_init);

पूर्णांक denali_init(काष्ठा denali_controller *denali)
अणु
	u32 features = ioपढ़ो32(denali->reg + FEATURES);
	पूर्णांक ret;

	nand_controller_init(&denali->controller);
	denali->controller.ops = &denali_controller_ops;
	init_completion(&denali->complete);
	spin_lock_init(&denali->irq_lock);
	INIT_LIST_HEAD(&denali->chips);
	denali->active_bank = DENALI_INVALID_BANK;

	/*
	 * The REVISION रेजिस्टर may not be reliable. Platक्रमms are allowed to
	 * override it.
	 */
	अगर (!denali->revision)
		denali->revision = swab16(ioपढ़ो32(denali->reg + REVISION));

	denali->nbanks = 1 << FIELD_GET(FEATURES__N_BANKS, features);

	/* the encoding changed from rev 5.0 to 5.1 */
	अगर (denali->revision < 0x0501)
		denali->nbanks <<= 1;

	अगर (features & FEATURES__DMA)
		denali->dma_avail = true;

	अगर (denali->dma_avail) अणु
		पूर्णांक dma_bit = denali->caps & DENALI_CAP_DMA_64BIT ? 64 : 32;

		ret = dma_set_mask(denali->dev, DMA_BIT_MASK(dma_bit));
		अगर (ret) अणु
			dev_info(denali->dev,
				 "Failed to set DMA mask. Disabling DMA.\n");
			denali->dma_avail = false;
		पूर्ण
	पूर्ण

	अगर (denali->dma_avail) अणु
		अगर (denali->caps & DENALI_CAP_DMA_64BIT)
			denali->setup_dma = denali_setup_dma64;
		अन्यथा
			denali->setup_dma = denali_setup_dma32;
	पूर्ण

	अगर (features & FEATURES__INDEX_ADDR) अणु
		denali->host_पढ़ो = denali_indexed_पढ़ो;
		denali->host_ग_लिखो = denali_indexed_ग_लिखो;
	पूर्ण अन्यथा अणु
		denali->host_पढ़ो = denali_direct_पढ़ो;
		denali->host_ग_लिखो = denali_direct_ग_लिखो;
	पूर्ण

	/*
	 * Set how many bytes should be skipped beक्रमe writing data in OOB.
	 * If a platक्रमm requests a non-zero value, set it to the रेजिस्टर.
	 * Otherwise, पढ़ो the value out, expecting it has alपढ़ोy been set up
	 * by firmware.
	 */
	अगर (denali->oob_skip_bytes)
		ioग_लिखो32(denali->oob_skip_bytes,
			  denali->reg + SPARE_AREA_SKIP_BYTES);
	अन्यथा
		denali->oob_skip_bytes = ioपढ़ो32(denali->reg +
						  SPARE_AREA_SKIP_BYTES);

	ioग_लिखो32(0, denali->reg + TRANSFER_SPARE_REG);
	ioग_लिखो32(GENMASK(denali->nbanks - 1, 0), denali->reg + RB_PIN_ENABLED);
	ioग_लिखो32(CHIP_EN_DONT_CARE__FLAG, denali->reg + CHIP_ENABLE_DONT_CARE);
	ioग_लिखो32(ECC_ENABLE__FLAG, denali->reg + ECC_ENABLE);
	ioग_लिखो32(0xffff, denali->reg + SPARE_AREA_MARKER);
	ioग_लिखो32(WRITE_PROTECT__FLAG, denali->reg + WRITE_PROTECT);

	denali_clear_irq_all(denali);

	ret = devm_request_irq(denali->dev, denali->irq, denali_isr,
			       IRQF_SHARED, DENALI_न_अंकD_NAME, denali);
	अगर (ret) अणु
		dev_err(denali->dev, "Unable to request IRQ\n");
		वापस ret;
	पूर्ण

	denali_enable_irq(denali);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(denali_init);

व्योम denali_हटाओ(काष्ठा denali_controller *denali)
अणु
	काष्ठा denali_chip *dchip, *पंचांगp;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(dchip, पंचांगp, &denali->chips, node) अणु
		chip = &dchip->chip;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		list_del(&dchip->node);
	पूर्ण

	denali_disable_irq(denali);
पूर्ण
EXPORT_SYMBOL(denali_हटाओ);

MODULE_DESCRIPTION("Driver core for Denali NAND controller");
MODULE_AUTHOR("Intel Corporation and its suppliers");
MODULE_LICENSE("GPL v2");
