<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * JZ4740 ECC controller driver
 *
 * Copyright (c) 2019 Paul Cercueil <paul@crapouillou.net>
 *
 * based on jz4740-nand.c
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ingenic_ecc.h"

#घोषणा JZ_REG_न_अंकD_ECC_CTRL	0x00
#घोषणा JZ_REG_न_अंकD_DATA	0x04
#घोषणा JZ_REG_न_अंकD_PAR0	0x08
#घोषणा JZ_REG_न_अंकD_PAR1	0x0C
#घोषणा JZ_REG_न_अंकD_PAR2	0x10
#घोषणा JZ_REG_न_अंकD_IRQ_STAT	0x14
#घोषणा JZ_REG_न_अंकD_IRQ_CTRL	0x18
#घोषणा JZ_REG_न_अंकD_ERR(x)	(0x1C + ((x) << 2))

#घोषणा JZ_न_अंकD_ECC_CTRL_PAR_READY	BIT(4)
#घोषणा JZ_न_अंकD_ECC_CTRL_ENCODING	BIT(3)
#घोषणा JZ_न_अंकD_ECC_CTRL_RS		BIT(2)
#घोषणा JZ_न_अंकD_ECC_CTRL_RESET		BIT(1)
#घोषणा JZ_न_अंकD_ECC_CTRL_ENABLE		BIT(0)

#घोषणा JZ_न_अंकD_STATUS_ERR_COUNT	(BIT(31) | BIT(30) | BIT(29))
#घोषणा JZ_न_अंकD_STATUS_PAD_FINISH	BIT(4)
#घोषणा JZ_न_अंकD_STATUS_DEC_FINISH	BIT(3)
#घोषणा JZ_न_अंकD_STATUS_ENC_FINISH	BIT(2)
#घोषणा JZ_न_अंकD_STATUS_UNCOR_ERROR	BIT(1)
#घोषणा JZ_न_अंकD_STATUS_ERROR		BIT(0)

अटल स्थिर uपूर्णांक8_t empty_block_ecc[] = अणु
	0xcd, 0x9d, 0x90, 0x58, 0xf4, 0x8b, 0xff, 0xb7, 0x6f
पूर्ण;

अटल व्योम jz4740_ecc_reset(काष्ठा ingenic_ecc *ecc, bool calc_ecc)
अणु
	uपूर्णांक32_t reg;

	/* Clear पूर्णांकerrupt status */
	ग_लिखोl(0, ecc->base + JZ_REG_न_अंकD_IRQ_STAT);

	/* Initialize and enable ECC hardware */
	reg = पढ़ोl(ecc->base + JZ_REG_न_अंकD_ECC_CTRL);
	reg |= JZ_न_अंकD_ECC_CTRL_RESET;
	reg |= JZ_न_अंकD_ECC_CTRL_ENABLE;
	reg |= JZ_न_अंकD_ECC_CTRL_RS;
	अगर (calc_ecc) /* calculate ECC from data */
		reg |= JZ_न_अंकD_ECC_CTRL_ENCODING;
	अन्यथा /* correct data from ECC */
		reg &= ~JZ_न_अंकD_ECC_CTRL_ENCODING;

	ग_लिखोl(reg, ecc->base + JZ_REG_न_अंकD_ECC_CTRL);
पूर्ण

अटल पूर्णांक jz4740_ecc_calculate(काष्ठा ingenic_ecc *ecc,
				काष्ठा ingenic_ecc_params *params,
				स्थिर u8 *buf, u8 *ecc_code)
अणु
	uपूर्णांक32_t reg, status;
	अचिन्हित पूर्णांक समयout = 1000;
	पूर्णांक i;

	jz4740_ecc_reset(ecc, true);

	करो अणु
		status = पढ़ोl(ecc->base + JZ_REG_न_अंकD_IRQ_STAT);
	पूर्ण जबतक (!(status & JZ_न_अंकD_STATUS_ENC_FINISH) && --समयout);

	अगर (समयout == 0)
		वापस -ETIMEDOUT;

	reg = पढ़ोl(ecc->base + JZ_REG_न_अंकD_ECC_CTRL);
	reg &= ~JZ_न_अंकD_ECC_CTRL_ENABLE;
	ग_लिखोl(reg, ecc->base + JZ_REG_न_अंकD_ECC_CTRL);

	क्रम (i = 0; i < params->bytes; ++i)
		ecc_code[i] = पढ़ोb(ecc->base + JZ_REG_न_अंकD_PAR0 + i);

	/*
	 * If the written data is completely 0xff, we also want to ग_लिखो 0xff as
	 * ECC, otherwise we will get in trouble when करोing subpage ग_लिखोs.
	 */
	अगर (स_भेद(ecc_code, empty_block_ecc, माप(empty_block_ecc)) == 0)
		स_रखो(ecc_code, 0xff, माप(empty_block_ecc));

	वापस 0;
पूर्ण

अटल व्योम jz_nand_correct_data(uपूर्णांक8_t *buf, पूर्णांक index, पूर्णांक mask)
अणु
	पूर्णांक offset = index & 0x7;
	uपूर्णांक16_t data;

	index += (index >> 3);

	data = buf[index];
	data |= buf[index + 1] << 8;

	mask ^= (data >> offset) & 0x1ff;
	data &= ~(0x1ff << offset);
	data |= (mask << offset);

	buf[index] = data & 0xff;
	buf[index + 1] = (data >> 8) & 0xff;
पूर्ण

अटल पूर्णांक jz4740_ecc_correct(काष्ठा ingenic_ecc *ecc,
			      काष्ठा ingenic_ecc_params *params,
			      u8 *buf, u8 *ecc_code)
अणु
	पूर्णांक i, error_count, index;
	uपूर्णांक32_t reg, status, error;
	अचिन्हित पूर्णांक समयout = 1000;

	jz4740_ecc_reset(ecc, false);

	क्रम (i = 0; i < params->bytes; ++i)
		ग_लिखोb(ecc_code[i], ecc->base + JZ_REG_न_अंकD_PAR0 + i);

	reg = पढ़ोl(ecc->base + JZ_REG_न_अंकD_ECC_CTRL);
	reg |= JZ_न_अंकD_ECC_CTRL_PAR_READY;
	ग_लिखोl(reg, ecc->base + JZ_REG_न_अंकD_ECC_CTRL);

	करो अणु
		status = पढ़ोl(ecc->base + JZ_REG_न_अंकD_IRQ_STAT);
	पूर्ण जबतक (!(status & JZ_न_अंकD_STATUS_DEC_FINISH) && --समयout);

	अगर (समयout == 0)
		वापस -ETIMEDOUT;

	reg = पढ़ोl(ecc->base + JZ_REG_न_अंकD_ECC_CTRL);
	reg &= ~JZ_न_अंकD_ECC_CTRL_ENABLE;
	ग_लिखोl(reg, ecc->base + JZ_REG_न_अंकD_ECC_CTRL);

	अगर (status & JZ_न_अंकD_STATUS_ERROR) अणु
		अगर (status & JZ_न_अंकD_STATUS_UNCOR_ERROR)
			वापस -EBADMSG;

		error_count = (status & JZ_न_अंकD_STATUS_ERR_COUNT) >> 29;

		क्रम (i = 0; i < error_count; ++i) अणु
			error = पढ़ोl(ecc->base + JZ_REG_न_अंकD_ERR(i));
			index = ((error >> 16) & 0x1ff) - 1;
			अगर (index >= 0 && index < params->size)
				jz_nand_correct_data(buf, index, error & 0x1ff);
		पूर्ण

		वापस error_count;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम jz4740_ecc_disable(काष्ठा ingenic_ecc *ecc)
अणु
	u32 reg;

	ग_लिखोl(0, ecc->base + JZ_REG_न_अंकD_IRQ_STAT);
	reg = पढ़ोl(ecc->base + JZ_REG_न_अंकD_ECC_CTRL);
	reg &= ~JZ_न_अंकD_ECC_CTRL_ENABLE;
	ग_लिखोl(reg, ecc->base + JZ_REG_न_अंकD_ECC_CTRL);
पूर्ण

अटल स्थिर काष्ठा ingenic_ecc_ops jz4740_ecc_ops = अणु
	.disable = jz4740_ecc_disable,
	.calculate = jz4740_ecc_calculate,
	.correct = jz4740_ecc_correct,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jz4740_ecc_dt_match[] = अणु
	अणु .compatible = "ingenic,jz4740-ecc", .data = &jz4740_ecc_ops पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4740_ecc_dt_match);

अटल काष्ठा platक्रमm_driver jz4740_ecc_driver = अणु
	.probe		= ingenic_ecc_probe,
	.driver	= अणु
		.name	= "jz4740-ecc",
		.of_match_table = jz4740_ecc_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(jz4740_ecc_driver);

MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_DESCRIPTION("Ingenic JZ4740 ECC controller driver");
MODULE_LICENSE("GPL v2");
