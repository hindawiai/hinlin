<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hisilicon न_अंकD Flash controller driver
 *
 * Copyright तऊ 2012-2014 HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 *
 * Author: Zhou Wang <wangzhou.bry@gmail.com>
 * The initial developer of the original code is Zhiyong Cai
 * <caizhiyong@huawei.com>
 */
#समावेश <linux/of.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/sizes.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/partitions.h>

#घोषणा HINFC504_MAX_CHIP                               (4)
#घोषणा HINFC504_W_LATCH                                (5)
#घोषणा HINFC504_R_LATCH                                (7)
#घोषणा HINFC504_RW_LATCH                               (3)

#घोषणा HINFC504_NFC_TIMEOUT				(2 * HZ)
#घोषणा HINFC504_NFC_PM_TIMEOUT				(1 * HZ)
#घोषणा HINFC504_NFC_DMA_TIMEOUT			(5 * HZ)
#घोषणा HINFC504_CHIP_DELAY				(25)

#घोषणा HINFC504_REG_BASE_ADDRESS_LEN			(0x100)
#घोषणा HINFC504_BUFFER_BASE_ADDRESS_LEN		(2048 + 128)

#घोषणा HINFC504_ADDR_CYCLE_MASK			0x4

#घोषणा HINFC504_CON					0x00
#घोषणा HINFC504_CON_OP_MODE_NORMAL			BIT(0)
#घोषणा HINFC504_CON_PAGEISZE_SHIFT			(1)
#घोषणा HINFC504_CON_PAGESIZE_MASK			(0x07)
#घोषणा HINFC504_CON_BUS_WIDTH				BIT(4)
#घोषणा HINFC504_CON_READY_BUSY_SEL			BIT(8)
#घोषणा HINFC504_CON_ECCTYPE_SHIFT			(9)
#घोषणा HINFC504_CON_ECCTYPE_MASK			(0x07)

#घोषणा HINFC504_PWIDTH					0x04
#घोषणा SET_HINFC504_PWIDTH(_w_lcnt, _r_lcnt, _rw_hcnt) \
	((_w_lcnt) | (((_r_lcnt) & 0x0F) << 4) | (((_rw_hcnt) & 0x0F) << 8))

#घोषणा HINFC504_CMD					0x0C
#घोषणा HINFC504_ADDRL					0x10
#घोषणा HINFC504_ADDRH					0x14
#घोषणा HINFC504_DATA_NUM				0x18

#घोषणा HINFC504_OP					0x1C
#घोषणा HINFC504_OP_READ_DATA_EN			BIT(1)
#घोषणा HINFC504_OP_WAIT_READY_EN			BIT(2)
#घोषणा HINFC504_OP_CMD2_EN				BIT(3)
#घोषणा HINFC504_OP_WRITE_DATA_EN			BIT(4)
#घोषणा HINFC504_OP_ADDR_EN				BIT(5)
#घोषणा HINFC504_OP_CMD1_EN				BIT(6)
#घोषणा HINFC504_OP_NF_CS_SHIFT                         (7)
#घोषणा HINFC504_OP_NF_CS_MASK				(3)
#घोषणा HINFC504_OP_ADDR_CYCLE_SHIFT			(9)
#घोषणा HINFC504_OP_ADDR_CYCLE_MASK			(7)

#घोषणा HINFC504_STATUS                                 0x20
#घोषणा HINFC504_READY					BIT(0)

#घोषणा HINFC504_INTEN					0x24
#घोषणा HINFC504_INTEN_DMA				BIT(9)
#घोषणा HINFC504_INTEN_UE				BIT(6)
#घोषणा HINFC504_INTEN_CE				BIT(5)

#घोषणा HINFC504_INTS					0x28
#घोषणा HINFC504_INTS_DMA				BIT(9)
#घोषणा HINFC504_INTS_UE				BIT(6)
#घोषणा HINFC504_INTS_CE				BIT(5)

#घोषणा HINFC504_INTCLR                                 0x2C
#घोषणा HINFC504_INTCLR_DMA				BIT(9)
#घोषणा HINFC504_INTCLR_UE				BIT(6)
#घोषणा HINFC504_INTCLR_CE				BIT(5)

#घोषणा HINFC504_ECC_STATUS                             0x5C
#घोषणा HINFC504_ECC_16_BIT_SHIFT                       12

#घोषणा HINFC504_DMA_CTRL				0x60
#घोषणा HINFC504_DMA_CTRL_DMA_START			BIT(0)
#घोषणा HINFC504_DMA_CTRL_WE				BIT(1)
#घोषणा HINFC504_DMA_CTRL_DATA_AREA_EN			BIT(2)
#घोषणा HINFC504_DMA_CTRL_OOB_AREA_EN			BIT(3)
#घोषणा HINFC504_DMA_CTRL_BURST4_EN			BIT(4)
#घोषणा HINFC504_DMA_CTRL_BURST8_EN			BIT(5)
#घोषणा HINFC504_DMA_CTRL_BURST16_EN			BIT(6)
#घोषणा HINFC504_DMA_CTRL_ADDR_NUM_SHIFT		(7)
#घोषणा HINFC504_DMA_CTRL_ADDR_NUM_MASK                 (1)
#घोषणा HINFC504_DMA_CTRL_CS_SHIFT			(8)
#घोषणा HINFC504_DMA_CTRL_CS_MASK			(0x03)

#घोषणा HINFC504_DMA_ADDR_DATA				0x64
#घोषणा HINFC504_DMA_ADDR_OOB				0x68

#घोषणा HINFC504_DMA_LEN				0x6C
#घोषणा HINFC504_DMA_LEN_OOB_SHIFT			(16)
#घोषणा HINFC504_DMA_LEN_OOB_MASK			(0xFFF)

#घोषणा HINFC504_DMA_PARA				0x70
#घोषणा HINFC504_DMA_PARA_DATA_RW_EN			BIT(0)
#घोषणा HINFC504_DMA_PARA_OOB_RW_EN			BIT(1)
#घोषणा HINFC504_DMA_PARA_DATA_EDC_EN			BIT(2)
#घोषणा HINFC504_DMA_PARA_OOB_EDC_EN			BIT(3)
#घोषणा HINFC504_DMA_PARA_DATA_ECC_EN			BIT(4)
#घोषणा HINFC504_DMA_PARA_OOB_ECC_EN			BIT(5)

#घोषणा HINFC_VERSION                                   0x74
#घोषणा HINFC504_LOG_READ_ADDR				0x7C
#घोषणा HINFC504_LOG_READ_LEN				0x80

#घोषणा HINFC504_न_अंकDINFO_LEN				0x10

काष्ठा hinfc_host अणु
	काष्ठा nand_chip	chip;
	काष्ठा device		*dev;
	व्योम __iomem		*iobase;
	व्योम __iomem		*mmio;
	काष्ठा completion       cmd_complete;
	अचिन्हित पूर्णांक		offset;
	अचिन्हित पूर्णांक		command;
	पूर्णांक			chipselect;
	अचिन्हित पूर्णांक		addr_cycle;
	u32                     addr_value[2];
	u32                     cache_addr_value[2];
	अक्षर			*buffer;
	dma_addr_t		dma_buffer;
	dma_addr_t		dma_oob;
	पूर्णांक			version;
	अचिन्हित पूर्णांक            irq_status; /* पूर्णांकerrupt status */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक hinfc_पढ़ो(काष्ठा hinfc_host *host, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(host->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम hinfc_ग_लिखो(काष्ठा hinfc_host *host, अचिन्हित पूर्णांक value,
			       अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोl(value, host->iobase + reg);
पूर्ण

अटल व्योम रुको_controller_finished(काष्ठा hinfc_host *host)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HINFC504_NFC_TIMEOUT;
	पूर्णांक val;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		val = hinfc_पढ़ो(host, HINFC504_STATUS);
		अगर (host->command == न_अंकD_CMD_ERASE2) अणु
			/* nfc is पढ़ोy */
			जबतक (!(val & HINFC504_READY))	अणु
				usleep_range(500, 1000);
				val = hinfc_पढ़ो(host, HINFC504_STATUS);
			पूर्ण
			वापस;
		पूर्ण

		अगर (val & HINFC504_READY)
			वापस;
	पूर्ण

	/* रुको cmd समयout */
	dev_err(host->dev, "Wait NAND controller exec cmd timeout.\n");
पूर्ण

अटल व्योम hisi_nfc_dma_transfer(काष्ठा hinfc_host *host, पूर्णांक todev)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा mtd_info	*mtd = nand_to_mtd(chip);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	hinfc_ग_लिखो(host, host->dma_buffer, HINFC504_DMA_ADDR_DATA);
	hinfc_ग_लिखो(host, host->dma_oob, HINFC504_DMA_ADDR_OOB);

	अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_NONE) अणु
		hinfc_ग_लिखो(host, ((mtd->oobsize & HINFC504_DMA_LEN_OOB_MASK)
			<< HINFC504_DMA_LEN_OOB_SHIFT), HINFC504_DMA_LEN);

		hinfc_ग_लिखो(host, HINFC504_DMA_PARA_DATA_RW_EN
			| HINFC504_DMA_PARA_OOB_RW_EN, HINFC504_DMA_PARA);
	पूर्ण अन्यथा अणु
		अगर (host->command == न_अंकD_CMD_READOOB)
			hinfc_ग_लिखो(host, HINFC504_DMA_PARA_OOB_RW_EN
			| HINFC504_DMA_PARA_OOB_EDC_EN
			| HINFC504_DMA_PARA_OOB_ECC_EN, HINFC504_DMA_PARA);
		अन्यथा
			hinfc_ग_लिखो(host, HINFC504_DMA_PARA_DATA_RW_EN
			| HINFC504_DMA_PARA_OOB_RW_EN
			| HINFC504_DMA_PARA_DATA_EDC_EN
			| HINFC504_DMA_PARA_OOB_EDC_EN
			| HINFC504_DMA_PARA_DATA_ECC_EN
			| HINFC504_DMA_PARA_OOB_ECC_EN, HINFC504_DMA_PARA);

	पूर्ण

	val = (HINFC504_DMA_CTRL_DMA_START | HINFC504_DMA_CTRL_BURST4_EN
		| HINFC504_DMA_CTRL_BURST8_EN | HINFC504_DMA_CTRL_BURST16_EN
		| HINFC504_DMA_CTRL_DATA_AREA_EN | HINFC504_DMA_CTRL_OOB_AREA_EN
		| ((host->addr_cycle == 4 ? 1 : 0)
			<< HINFC504_DMA_CTRL_ADDR_NUM_SHIFT)
		| ((host->chipselect & HINFC504_DMA_CTRL_CS_MASK)
			<< HINFC504_DMA_CTRL_CS_SHIFT));

	अगर (todev)
		val |= HINFC504_DMA_CTRL_WE;

	init_completion(&host->cmd_complete);

	hinfc_ग_लिखो(host, val, HINFC504_DMA_CTRL);
	ret = रुको_क्रम_completion_समयout(&host->cmd_complete,
			HINFC504_NFC_DMA_TIMEOUT);

	अगर (!ret) अणु
		dev_err(host->dev, "DMA operation(irq) timeout!\n");
		/* sanity check */
		val = hinfc_पढ़ो(host, HINFC504_DMA_CTRL);
		अगर (!(val & HINFC504_DMA_CTRL_DMA_START))
			dev_err(host->dev, "DMA is already done but without irq ACK!\n");
		अन्यथा
			dev_err(host->dev, "DMA is really timeout!\n");
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_nfc_send_cmd_pageprog(काष्ठा hinfc_host *host)
अणु
	host->addr_value[0] &= 0xffff0000;

	hinfc_ग_लिखो(host, host->addr_value[0], HINFC504_ADDRL);
	hinfc_ग_लिखो(host, host->addr_value[1], HINFC504_ADDRH);
	hinfc_ग_लिखो(host, न_अंकD_CMD_PAGEPROG << 8 | न_अंकD_CMD_SEQIN,
		    HINFC504_CMD);

	hisi_nfc_dma_transfer(host, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_nfc_send_cmd_पढ़ोstart(काष्ठा hinfc_host *host)
अणु
	काष्ठा mtd_info	*mtd = nand_to_mtd(&host->chip);

	अगर ((host->addr_value[0] == host->cache_addr_value[0]) &&
	    (host->addr_value[1] == host->cache_addr_value[1]))
		वापस 0;

	host->addr_value[0] &= 0xffff0000;

	hinfc_ग_लिखो(host, host->addr_value[0], HINFC504_ADDRL);
	hinfc_ग_लिखो(host, host->addr_value[1], HINFC504_ADDRH);
	hinfc_ग_लिखो(host, न_अंकD_CMD_READSTART << 8 | न_अंकD_CMD_READ0,
		    HINFC504_CMD);

	hinfc_ग_लिखो(host, 0, HINFC504_LOG_READ_ADDR);
	hinfc_ग_लिखो(host, mtd->ग_लिखोsize + mtd->oobsize,
		    HINFC504_LOG_READ_LEN);

	hisi_nfc_dma_transfer(host, 0);

	host->cache_addr_value[0] = host->addr_value[0];
	host->cache_addr_value[1] = host->addr_value[1];

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_nfc_send_cmd_erase(काष्ठा hinfc_host *host)
अणु
	hinfc_ग_लिखो(host, host->addr_value[0], HINFC504_ADDRL);
	hinfc_ग_लिखो(host, (न_अंकD_CMD_ERASE2 << 8) | न_अंकD_CMD_ERASE1,
		    HINFC504_CMD);

	hinfc_ग_लिखो(host, HINFC504_OP_WAIT_READY_EN
		| HINFC504_OP_CMD2_EN
		| HINFC504_OP_CMD1_EN
		| HINFC504_OP_ADDR_EN
		| ((host->chipselect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT)
		| ((host->addr_cycle & HINFC504_OP_ADDR_CYCLE_MASK)
			<< HINFC504_OP_ADDR_CYCLE_SHIFT),
		HINFC504_OP);

	रुको_controller_finished(host);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_nfc_send_cmd_पढ़ोid(काष्ठा hinfc_host *host)
अणु
	hinfc_ग_लिखो(host, HINFC504_न_अंकDINFO_LEN, HINFC504_DATA_NUM);
	hinfc_ग_लिखो(host, न_अंकD_CMD_READID, HINFC504_CMD);
	hinfc_ग_लिखो(host, 0, HINFC504_ADDRL);

	hinfc_ग_लिखो(host, HINFC504_OP_CMD1_EN | HINFC504_OP_ADDR_EN
		| HINFC504_OP_READ_DATA_EN
		| ((host->chipselect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT)
		| 1 << HINFC504_OP_ADDR_CYCLE_SHIFT, HINFC504_OP);

	रुको_controller_finished(host);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_nfc_send_cmd_status(काष्ठा hinfc_host *host)
अणु
	hinfc_ग_लिखो(host, HINFC504_न_अंकDINFO_LEN, HINFC504_DATA_NUM);
	hinfc_ग_लिखो(host, न_अंकD_CMD_STATUS, HINFC504_CMD);
	hinfc_ग_लिखो(host, HINFC504_OP_CMD1_EN
		| HINFC504_OP_READ_DATA_EN
		| ((host->chipselect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT),
		HINFC504_OP);

	रुको_controller_finished(host);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_nfc_send_cmd_reset(काष्ठा hinfc_host *host, पूर्णांक chipselect)
अणु
	hinfc_ग_लिखो(host, न_अंकD_CMD_RESET, HINFC504_CMD);

	hinfc_ग_लिखो(host, HINFC504_OP_CMD1_EN
		| ((chipselect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT)
		| HINFC504_OP_WAIT_READY_EN,
		HINFC504_OP);

	रुको_controller_finished(host);

	वापस 0;
पूर्ण

अटल व्योम hisi_nfc_select_chip(काष्ठा nand_chip *chip, पूर्णांक chipselect)
अणु
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);

	अगर (chipselect < 0)
		वापस;

	host->chipselect = chipselect;
पूर्ण

अटल uपूर्णांक8_t hisi_nfc_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);

	अगर (host->command == न_अंकD_CMD_STATUS)
		वापस *(uपूर्णांक8_t *)(host->mmio);

	host->offset++;

	अगर (host->command == न_अंकD_CMD_READID)
		वापस *(uपूर्णांक8_t *)(host->mmio + host->offset - 1);

	वापस *(uपूर्णांक8_t *)(host->buffer + host->offset - 1);
पूर्ण

अटल व्योम
hisi_nfc_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);

	स_नकल(host->buffer + host->offset, buf, len);
	host->offset += len;
पूर्ण

अटल व्योम hisi_nfc_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);

	स_नकल(buf, host->buffer + host->offset, len);
	host->offset += len;
पूर्ण

अटल व्योम set_addr(काष्ठा mtd_info *mtd, पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);
	अचिन्हित पूर्णांक command = host->command;

	host->addr_cycle    = 0;
	host->addr_value[0] = 0;
	host->addr_value[1] = 0;

	/* Serially input address */
	अगर (column != -1) अणु
		/* Adjust columns क्रम 16 bit buswidth */
		अगर (chip->options & न_अंकD_BUSWIDTH_16 &&
				!nand_opcode_8bits(command))
			column >>= 1;

		host->addr_value[0] = column & 0xffff;
		host->addr_cycle    = 2;
	पूर्ण
	अगर (page_addr != -1) अणु
		host->addr_value[0] |= (page_addr & 0xffff)
			<< (host->addr_cycle * 8);
		host->addr_cycle    += 2;
		अगर (chip->options & न_अंकD_ROW_ADDR_3) अणु
			host->addr_cycle += 1;
			अगर (host->command == न_अंकD_CMD_ERASE1)
				host->addr_value[0] |= ((page_addr >> 16) & 0xff) << 16;
			अन्यथा
				host->addr_value[1] |= ((page_addr >> 16) & 0xff);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hisi_nfc_cmdfunc(काष्ठा nand_chip *chip, अचिन्हित command,
			     पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);
	पूर्णांक is_cache_invalid = 1;
	अचिन्हित पूर्णांक flag = 0;

	host->command =  command;

	चयन (command) अणु
	हाल न_अंकD_CMD_READ0:
	हाल न_अंकD_CMD_READOOB:
		अगर (command == न_अंकD_CMD_READ0)
			host->offset = column;
		अन्यथा
			host->offset = column + mtd->ग_लिखोsize;

		is_cache_invalid = 0;
		set_addr(mtd, column, page_addr);
		hisi_nfc_send_cmd_पढ़ोstart(host);
		अवरोध;

	हाल न_अंकD_CMD_SEQIN:
		host->offset = column;
		set_addr(mtd, column, page_addr);
		अवरोध;

	हाल न_अंकD_CMD_ERASE1:
		set_addr(mtd, column, page_addr);
		अवरोध;

	हाल न_अंकD_CMD_PAGEPROG:
		hisi_nfc_send_cmd_pageprog(host);
		अवरोध;

	हाल न_अंकD_CMD_ERASE2:
		hisi_nfc_send_cmd_erase(host);
		अवरोध;

	हाल न_अंकD_CMD_READID:
		host->offset = column;
		स_रखो(host->mmio, 0, 0x10);
		hisi_nfc_send_cmd_पढ़ोid(host);
		अवरोध;

	हाल न_अंकD_CMD_STATUS:
		flag = hinfc_पढ़ो(host, HINFC504_CON);
		अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
			hinfc_ग_लिखो(host,
				    flag & ~(HINFC504_CON_ECCTYPE_MASK <<
				    HINFC504_CON_ECCTYPE_SHIFT), HINFC504_CON);

		host->offset = 0;
		स_रखो(host->mmio, 0, 0x10);
		hisi_nfc_send_cmd_status(host);
		hinfc_ग_लिखो(host, flag, HINFC504_CON);
		अवरोध;

	हाल न_अंकD_CMD_RESET:
		hisi_nfc_send_cmd_reset(host, host->chipselect);
		अवरोध;

	शेष:
		dev_err(host->dev, "Error: unsupported cmd(cmd=%x, col=%x, page=%x)\n",
			command, column, page_addr);
	पूर्ण

	अगर (is_cache_invalid) अणु
		host->cache_addr_value[0] = ~0;
		host->cache_addr_value[1] = ~0;
	पूर्ण
पूर्ण

अटल irqवापस_t hinfc_irq_handle(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा hinfc_host *host = devid;
	अचिन्हित पूर्णांक flag;

	flag = hinfc_पढ़ो(host, HINFC504_INTS);
	/* store पूर्णांकerrupts state */
	host->irq_status |= flag;

	अगर (flag & HINFC504_INTS_DMA) अणु
		hinfc_ग_लिखो(host, HINFC504_INTCLR_DMA, HINFC504_INTCLR);
		complete(&host->cmd_complete);
	पूर्ण अन्यथा अगर (flag & HINFC504_INTS_CE) अणु
		hinfc_ग_लिखो(host, HINFC504_INTCLR_CE, HINFC504_INTCLR);
	पूर्ण अन्यथा अगर (flag & HINFC504_INTS_UE) अणु
		hinfc_ग_लिखो(host, HINFC504_INTCLR_UE, HINFC504_INTCLR);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hisi_nand_पढ़ो_page_hwecc(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				     पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);
	पूर्णांक max_bitflips = 0, stat = 0, stat_max = 0, status_ecc;
	पूर्णांक stat_1, stat_2;

	nand_पढ़ो_page_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	chip->legacy.पढ़ो_buf(chip, chip->oob_poi, mtd->oobsize);

	/* errors which can not be corrected by ECC */
	अगर (host->irq_status & HINFC504_INTS_UE) अणु
		mtd->ecc_stats.failed++;
	पूर्ण अन्यथा अगर (host->irq_status & HINFC504_INTS_CE) अणु
		/* TODO: need add other ECC modes! */
		चयन (chip->ecc.strength) अणु
		हाल 16:
			status_ecc = hinfc_पढ़ो(host, HINFC504_ECC_STATUS) >>
					HINFC504_ECC_16_BIT_SHIFT & 0x0fff;
			stat_2 = status_ecc & 0x3f;
			stat_1 = status_ecc >> 6 & 0x3f;
			stat = stat_1 + stat_2;
			stat_max = max_t(पूर्णांक, stat_1, stat_2);
		पूर्ण
		mtd->ecc_stats.corrected += stat;
		max_bitflips = max_t(पूर्णांक, max_bitflips, stat_max);
	पूर्ण
	host->irq_status = 0;

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक hisi_nand_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);

	nand_पढ़ो_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);

	अगर (host->irq_status & HINFC504_INTS_UE) अणु
		host->irq_status = 0;
		वापस -EBADMSG;
	पूर्ण

	host->irq_status = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक hisi_nand_ग_लिखो_page_hwecc(काष्ठा nand_chip *chip,
				      स्थिर uपूर्णांक8_t *buf, पूर्णांक oob_required,
				      पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	nand_prog_page_begin_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	अगर (oob_required)
		chip->legacy.ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल व्योम hisi_nfc_host_init(काष्ठा hinfc_host *host)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	अचिन्हित पूर्णांक flag = 0;

	host->version = hinfc_पढ़ो(host, HINFC_VERSION);
	host->addr_cycle		= 0;
	host->addr_value[0]		= 0;
	host->addr_value[1]		= 0;
	host->cache_addr_value[0]	= ~0;
	host->cache_addr_value[1]	= ~0;
	host->chipselect		= 0;

	/* शेष page size: 2K, ecc_none. need modअगरy */
	flag = HINFC504_CON_OP_MODE_NORMAL | HINFC504_CON_READY_BUSY_SEL
		| ((0x001 & HINFC504_CON_PAGESIZE_MASK)
			<< HINFC504_CON_PAGEISZE_SHIFT)
		| ((0x0 & HINFC504_CON_ECCTYPE_MASK)
			<< HINFC504_CON_ECCTYPE_SHIFT)
		| ((chip->options & न_अंकD_BUSWIDTH_16) ?
			HINFC504_CON_BUS_WIDTH : 0);
	hinfc_ग_लिखो(host, flag, HINFC504_CON);

	स_रखो(host->mmio, 0xff, HINFC504_BUFFER_BASE_ADDRESS_LEN);

	hinfc_ग_लिखो(host, SET_HINFC504_PWIDTH(HINFC504_W_LATCH,
		    HINFC504_R_LATCH, HINFC504_RW_LATCH), HINFC504_PWIDTH);

	/* enable DMA irq */
	hinfc_ग_लिखो(host, HINFC504_INTEN_DMA, HINFC504_INTEN);
पूर्ण

अटल पूर्णांक hisi_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
			      काष्ठा mtd_oob_region *oobregion)
अणु
	/* FIXME: add ECC bytes position */
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक hisi_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
			       काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 2;
	oobregion->length = 6;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops hisi_ooblayout_ops = अणु
	.ecc = hisi_ooblayout_ecc,
	.मुक्त = hisi_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक hisi_nfc_ecc_probe(काष्ठा hinfc_host *host)
अणु
	अचिन्हित पूर्णांक flag;
	पूर्णांक size, strength, ecc_bits;
	काष्ठा device *dev = host->dev;
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	size = chip->ecc.size;
	strength = chip->ecc.strength;
	अगर (size != 1024) अणु
		dev_err(dev, "error ecc size: %d\n", size);
		वापस -EINVAL;
	पूर्ण

	अगर ((size == 1024) && ((strength != 8) && (strength != 16) &&
				(strength != 24) && (strength != 40))) अणु
		dev_err(dev, "ecc size and strength do not match\n");
		वापस -EINVAL;
	पूर्ण

	chip->ecc.size = size;
	chip->ecc.strength = strength;

	chip->ecc.पढ़ो_page = hisi_nand_पढ़ो_page_hwecc;
	chip->ecc.पढ़ो_oob = hisi_nand_पढ़ो_oob;
	chip->ecc.ग_लिखो_page = hisi_nand_ग_लिखो_page_hwecc;

	चयन (chip->ecc.strength) अणु
	हाल 16:
		ecc_bits = 6;
		अगर (mtd->ग_लिखोsize == 2048)
			mtd_set_ooblayout(mtd, &hisi_ooblayout_ops);

		/* TODO: add more page size support */
		अवरोध;

	/* TODO: add more ecc strength support */
	शेष:
		dev_err(dev, "not support strength: %d\n", chip->ecc.strength);
		वापस -EINVAL;
	पूर्ण

	flag = hinfc_पढ़ो(host, HINFC504_CON);
	/* add ecc type configure */
	flag |= ((ecc_bits & HINFC504_CON_ECCTYPE_MASK)
						<< HINFC504_CON_ECCTYPE_SHIFT);
	hinfc_ग_लिखो(host, flag, HINFC504_CON);

	/* enable ecc irq */
	flag = hinfc_पढ़ो(host, HINFC504_INTEN) & 0xfff;
	hinfc_ग_लिखो(host, flag | HINFC504_INTEN_UE | HINFC504_INTEN_CE,
		    HINFC504_INTEN);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_nfc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा hinfc_host *host = nand_get_controller_data(chip);
	पूर्णांक flag;

	host->buffer = dmam_alloc_coherent(host->dev,
					   mtd->ग_लिखोsize + mtd->oobsize,
					   &host->dma_buffer, GFP_KERNEL);
	अगर (!host->buffer)
		वापस -ENOMEM;

	host->dma_oob = host->dma_buffer + mtd->ग_लिखोsize;
	स_रखो(host->buffer, 0xff, mtd->ग_लिखोsize + mtd->oobsize);

	flag = hinfc_पढ़ो(host, HINFC504_CON);
	flag &= ~(HINFC504_CON_PAGESIZE_MASK << HINFC504_CON_PAGEISZE_SHIFT);
	चयन (mtd->ग_लिखोsize) अणु
	हाल 2048:
		flag |= (0x001 << HINFC504_CON_PAGEISZE_SHIFT);
		अवरोध;
	/*
	 * TODO: add more pagesize support,
	 * शेष pagesize has been set in hisi_nfc_host_init
	 */
	शेष:
		dev_err(host->dev, "NON-2KB page size nand flash\n");
		वापस -EINVAL;
	पूर्ण
	hinfc_ग_लिखो(host, flag, HINFC504_CON);

	अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		hisi_nfc_ecc_probe(host);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops hisi_nfc_controller_ops = अणु
	.attach_chip = hisi_nfc_attach_chip,
पूर्ण;

अटल पूर्णांक hisi_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0, irq, max_chips = HINFC504_MAX_CHIP;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hinfc_host *host;
	काष्ठा nand_chip  *chip;
	काष्ठा mtd_info   *mtd;
	काष्ठा resource	  *res;
	काष्ठा device_node *np = dev->of_node;

	host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;
	host->dev = dev;

	platक्रमm_set_drvdata(pdev, host);
	chip = &host->chip;
	mtd  = nand_to_mtd(chip);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->iobase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(host->iobase))
		वापस PTR_ERR(host->iobase);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	host->mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(host->mmio)) अणु
		dev_err(dev, "devm_ioremap_resource[1] fail\n");
		वापस PTR_ERR(host->mmio);
	पूर्ण

	mtd->name		= "hisi_nand";
	mtd->dev.parent         = &pdev->dev;

	nand_set_controller_data(chip, host);
	nand_set_flash_node(chip, np);
	chip->legacy.cmdfunc	= hisi_nfc_cmdfunc;
	chip->legacy.select_chip	= hisi_nfc_select_chip;
	chip->legacy.पढ़ो_byte	= hisi_nfc_पढ़ो_byte;
	chip->legacy.ग_लिखो_buf	= hisi_nfc_ग_लिखो_buf;
	chip->legacy.पढ़ो_buf	= hisi_nfc_पढ़ो_buf;
	chip->legacy.chip_delay	= HINFC504_CHIP_DELAY;
	chip->legacy.set_features	= nand_get_set_features_notsupp;
	chip->legacy.get_features	= nand_get_set_features_notsupp;

	hisi_nfc_host_init(host);

	ret = devm_request_irq(dev, irq, hinfc_irq_handle, 0x0, "nandc", host);
	अगर (ret) अणु
		dev_err(dev, "failed to request IRQ\n");
		वापस ret;
	पूर्ण

	chip->legacy.dummy_controller.ops = &hisi_nfc_controller_ops;
	ret = nand_scan(chip, max_chips);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "Err MTD partition=%d\n", ret);
		nand_cleanup(chip);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hinfc_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &host->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hisi_nfc_suspend(काष्ठा device *dev)
अणु
	काष्ठा hinfc_host *host = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समयout = jअगरfies + HINFC504_NFC_PM_TIMEOUT;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (((hinfc_पढ़ो(host, HINFC504_STATUS) & 0x1) == 0x0) &&
		    (hinfc_पढ़ो(host, HINFC504_DMA_CTRL) &
		     HINFC504_DMA_CTRL_DMA_START)) अणु
			cond_resched();
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(host->dev, "nand controller suspend timeout.\n");

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक hisi_nfc_resume(काष्ठा device *dev)
अणु
	पूर्णांक cs;
	काष्ठा hinfc_host *host = dev_get_drvdata(dev);
	काष्ठा nand_chip *chip = &host->chip;

	क्रम (cs = 0; cs < nanddev_ntarमाला_लो(&chip->base); cs++)
		hisi_nfc_send_cmd_reset(host, cs);
	hinfc_ग_लिखो(host, SET_HINFC504_PWIDTH(HINFC504_W_LATCH,
		    HINFC504_R_LATCH, HINFC504_RW_LATCH), HINFC504_PWIDTH);

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(hisi_nfc_pm_ops, hisi_nfc_suspend, hisi_nfc_resume);

अटल स्थिर काष्ठा of_device_id nfc_id_table[] = अणु
	अणु .compatible = "hisilicon,504-nfc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nfc_id_table);

अटल काष्ठा platक्रमm_driver hisi_nfc_driver = अणु
	.driver = अणु
		.name  = "hisi_nand",
		.of_match_table = nfc_id_table,
		.pm = &hisi_nfc_pm_ops,
	पूर्ण,
	.probe		= hisi_nfc_probe,
	.हटाओ		= hisi_nfc_हटाओ,
पूर्ण;

module_platक्रमm_driver(hisi_nfc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhou Wang");
MODULE_AUTHOR("Zhiyong Cai");
MODULE_DESCRIPTION("Hisilicon Nand Flash Controller Driver");
