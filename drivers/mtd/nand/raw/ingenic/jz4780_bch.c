<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * JZ4780 BCH controller driver
 *
 * Copyright (c) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ingenic_ecc.h"

#घोषणा BCH_BHCR			0x0
#घोषणा BCH_BHCCR			0x8
#घोषणा BCH_BHCNT			0xc
#घोषणा BCH_BHDR			0x10
#घोषणा BCH_BHPAR0			0x14
#घोषणा BCH_BHERR0			0x84
#घोषणा BCH_BHINT			0x184
#घोषणा BCH_BHINTES			0x188
#घोषणा BCH_BHINTEC			0x18c
#घोषणा BCH_BHINTE			0x190

#घोषणा BCH_BHCR_BSEL_SHIFT		4
#घोषणा BCH_BHCR_BSEL_MASK		(0x7f << BCH_BHCR_BSEL_SHIFT)
#घोषणा BCH_BHCR_ENCE			BIT(2)
#घोषणा BCH_BHCR_INIT			BIT(1)
#घोषणा BCH_BHCR_BCHE			BIT(0)

#घोषणा BCH_BHCNT_PARITYSIZE_SHIFT	16
#घोषणा BCH_BHCNT_PARITYSIZE_MASK	(0x7f << BCH_BHCNT_PARITYSIZE_SHIFT)
#घोषणा BCH_BHCNT_BLOCKSIZE_SHIFT	0
#घोषणा BCH_BHCNT_BLOCKSIZE_MASK	(0x7ff << BCH_BHCNT_BLOCKSIZE_SHIFT)

#घोषणा BCH_BHERR_MASK_SHIFT		16
#घोषणा BCH_BHERR_MASK_MASK		(0xffff << BCH_BHERR_MASK_SHIFT)
#घोषणा BCH_BHERR_INDEX_SHIFT		0
#घोषणा BCH_BHERR_INDEX_MASK		(0x7ff << BCH_BHERR_INDEX_SHIFT)

#घोषणा BCH_BHINT_ERRC_SHIFT		24
#घोषणा BCH_BHINT_ERRC_MASK		(0x7f << BCH_BHINT_ERRC_SHIFT)
#घोषणा BCH_BHINT_TERRC_SHIFT		16
#घोषणा BCH_BHINT_TERRC_MASK		(0x7f << BCH_BHINT_TERRC_SHIFT)
#घोषणा BCH_BHINT_DECF			BIT(3)
#घोषणा BCH_BHINT_ENCF			BIT(2)
#घोषणा BCH_BHINT_UNCOR			BIT(1)
#घोषणा BCH_BHINT_ERR			BIT(0)

#घोषणा BCH_CLK_RATE			(200 * 1000 * 1000)

/* Timeout क्रम BCH calculation/correction. */
#घोषणा BCH_TIMEOUT_US			100000

अटल व्योम jz4780_bch_reset(काष्ठा ingenic_ecc *bch,
			     काष्ठा ingenic_ecc_params *params, bool encode)
अणु
	u32 reg;

	/* Clear पूर्णांकerrupt status. */
	ग_लिखोl(पढ़ोl(bch->base + BCH_BHINT), bch->base + BCH_BHINT);

	/* Set up BCH count रेजिस्टर. */
	reg = params->size << BCH_BHCNT_BLOCKSIZE_SHIFT;
	reg |= params->bytes << BCH_BHCNT_PARITYSIZE_SHIFT;
	ग_लिखोl(reg, bch->base + BCH_BHCNT);

	/* Initialise and enable BCH. */
	reg = BCH_BHCR_BCHE | BCH_BHCR_INIT;
	reg |= params->strength << BCH_BHCR_BSEL_SHIFT;
	अगर (encode)
		reg |= BCH_BHCR_ENCE;
	ग_लिखोl(reg, bch->base + BCH_BHCR);
पूर्ण

अटल व्योम jz4780_bch_disable(काष्ठा ingenic_ecc *bch)
अणु
	ग_लिखोl(पढ़ोl(bch->base + BCH_BHINT), bch->base + BCH_BHINT);
	ग_लिखोl(BCH_BHCR_BCHE, bch->base + BCH_BHCCR);
पूर्ण

अटल व्योम jz4780_bch_ग_लिखो_data(काष्ठा ingenic_ecc *bch, स्थिर व्योम *buf,
				  माप_प्रकार size)
अणु
	माप_प्रकार size32 = size / माप(u32);
	माप_प्रकार size8 = size % माप(u32);
	स्थिर u32 *src32;
	स्थिर u8 *src8;

	src32 = (स्थिर u32 *)buf;
	जबतक (size32--)
		ग_लिखोl(*src32++, bch->base + BCH_BHDR);

	src8 = (स्थिर u8 *)src32;
	जबतक (size8--)
		ग_लिखोb(*src8++, bch->base + BCH_BHDR);
पूर्ण

अटल व्योम jz4780_bch_पढ़ो_parity(काष्ठा ingenic_ecc *bch, व्योम *buf,
				   माप_प्रकार size)
अणु
	माप_प्रकार size32 = size / माप(u32);
	माप_प्रकार size8 = size % माप(u32);
	u32 *dest32;
	u8 *dest8;
	u32 val, offset = 0;

	dest32 = (u32 *)buf;
	जबतक (size32--) अणु
		*dest32++ = पढ़ोl(bch->base + BCH_BHPAR0 + offset);
		offset += माप(u32);
	पूर्ण

	dest8 = (u8 *)dest32;
	val = पढ़ोl(bch->base + BCH_BHPAR0 + offset);
	चयन (size8) अणु
	हाल 3:
		dest8[2] = (val >> 16) & 0xff;
		fallthrough;
	हाल 2:
		dest8[1] = (val >> 8) & 0xff;
		fallthrough;
	हाल 1:
		dest8[0] = val & 0xff;
		अवरोध;
	पूर्ण
पूर्ण

अटल bool jz4780_bch_रुको_complete(काष्ठा ingenic_ecc *bch, अचिन्हित पूर्णांक irq,
				     u32 *status)
अणु
	u32 reg;
	पूर्णांक ret;

	/*
	 * While we could use पूर्णांकerrupts here and sleep until the operation
	 * completes, the controller works fairly quickly (usually a few
	 * microseconds) and so the overhead of sleeping until we get an
	 * पूर्णांकerrupt quite noticeably decreases perक्रमmance.
	 */
	ret = पढ़ोl_poll_समयout(bch->base + BCH_BHINT, reg,
				 (reg & irq) == irq, 0, BCH_TIMEOUT_US);
	अगर (ret)
		वापस false;

	अगर (status)
		*status = reg;

	ग_लिखोl(reg, bch->base + BCH_BHINT);
	वापस true;
पूर्ण

अटल पूर्णांक jz4780_calculate(काष्ठा ingenic_ecc *bch,
			    काष्ठा ingenic_ecc_params *params,
			    स्थिर u8 *buf, u8 *ecc_code)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&bch->lock);

	jz4780_bch_reset(bch, params, true);
	jz4780_bch_ग_लिखो_data(bch, buf, params->size);

	अगर (jz4780_bch_रुको_complete(bch, BCH_BHINT_ENCF, शून्य)) अणु
		jz4780_bch_पढ़ो_parity(bch, ecc_code, params->bytes);
	पूर्ण अन्यथा अणु
		dev_err(bch->dev, "timed out while calculating ECC\n");
		ret = -ETIMEDOUT;
	पूर्ण

	jz4780_bch_disable(bch);
	mutex_unlock(&bch->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक jz4780_correct(काष्ठा ingenic_ecc *bch,
			  काष्ठा ingenic_ecc_params *params,
			  u8 *buf, u8 *ecc_code)
अणु
	u32 reg, mask, index;
	पूर्णांक i, ret, count;

	mutex_lock(&bch->lock);

	jz4780_bch_reset(bch, params, false);
	jz4780_bch_ग_लिखो_data(bch, buf, params->size);
	jz4780_bch_ग_लिखो_data(bch, ecc_code, params->bytes);

	अगर (!jz4780_bch_रुको_complete(bch, BCH_BHINT_DECF, &reg)) अणु
		dev_err(bch->dev, "timed out while correcting data\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	अगर (reg & BCH_BHINT_UNCOR) अणु
		dev_warn(bch->dev, "uncorrectable ECC error\n");
		ret = -EBADMSG;
		जाओ out;
	पूर्ण

	/* Correct any detected errors. */
	अगर (reg & BCH_BHINT_ERR) अणु
		count = (reg & BCH_BHINT_ERRC_MASK) >> BCH_BHINT_ERRC_SHIFT;
		ret = (reg & BCH_BHINT_TERRC_MASK) >> BCH_BHINT_TERRC_SHIFT;

		क्रम (i = 0; i < count; i++) अणु
			reg = पढ़ोl(bch->base + BCH_BHERR0 + (i * 4));
			mask = (reg & BCH_BHERR_MASK_MASK) >>
						BCH_BHERR_MASK_SHIFT;
			index = (reg & BCH_BHERR_INDEX_MASK) >>
						BCH_BHERR_INDEX_SHIFT;
			buf[(index * 2) + 0] ^= mask;
			buf[(index * 2) + 1] ^= mask >> 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

out:
	jz4780_bch_disable(bch);
	mutex_unlock(&bch->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक jz4780_bch_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ingenic_ecc *bch;
	पूर्णांक ret;

	ret = ingenic_ecc_probe(pdev);
	अगर (ret)
		वापस ret;

	bch = platक्रमm_get_drvdata(pdev);
	clk_set_rate(bch->clk, BCH_CLK_RATE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ingenic_ecc_ops jz4780_bch_ops = अणु
	.disable = jz4780_bch_disable,
	.calculate = jz4780_calculate,
	.correct = jz4780_correct,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jz4780_bch_dt_match[] = अणु
	अणु .compatible = "ingenic,jz4780-bch", .data = &jz4780_bch_ops पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4780_bch_dt_match);

अटल काष्ठा platक्रमm_driver jz4780_bch_driver = अणु
	.probe		= jz4780_bch_probe,
	.driver	= अणु
		.name	= "jz4780-bch",
		.of_match_table = of_match_ptr(jz4780_bch_dt_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(jz4780_bch_driver);

MODULE_AUTHOR("Alex Smith <alex@alex-smith.me.uk>");
MODULE_AUTHOR("Harvey Hunt <harveyhuntnexus@gmail.com>");
MODULE_DESCRIPTION("Ingenic JZ4780 BCH error correction driver");
MODULE_LICENSE("GPL v2");
