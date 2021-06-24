<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * JZ4725B BCH controller driver
 *
 * Copyright (C) 2019 Paul Cercueil <paul@crapouillou.net>
 *
 * Based on jz4780_bch.c
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ingenic_ecc.h"

#घोषणा BCH_BHCR			0x0
#घोषणा BCH_BHCSR			0x4
#घोषणा BCH_BHCCR			0x8
#घोषणा BCH_BHCNT			0xc
#घोषणा BCH_BHDR			0x10
#घोषणा BCH_BHPAR0			0x14
#घोषणा BCH_BHERR0			0x28
#घोषणा BCH_BHINT			0x24
#घोषणा BCH_BHINTES			0x3c
#घोषणा BCH_BHINTEC			0x40
#घोषणा BCH_BHINTE			0x38

#घोषणा BCH_BHCR_ENCE			BIT(3)
#घोषणा BCH_BHCR_BSEL			BIT(2)
#घोषणा BCH_BHCR_INIT			BIT(1)
#घोषणा BCH_BHCR_BCHE			BIT(0)

#घोषणा BCH_BHCNT_DEC_COUNT_SHIFT	16
#घोषणा BCH_BHCNT_DEC_COUNT_MASK	(0x3ff << BCH_BHCNT_DEC_COUNT_SHIFT)
#घोषणा BCH_BHCNT_ENC_COUNT_SHIFT	0
#घोषणा BCH_BHCNT_ENC_COUNT_MASK	(0x3ff << BCH_BHCNT_ENC_COUNT_SHIFT)

#घोषणा BCH_BHERR_INDEX0_SHIFT		0
#घोषणा BCH_BHERR_INDEX0_MASK		(0x1fff << BCH_BHERR_INDEX0_SHIFT)
#घोषणा BCH_BHERR_INDEX1_SHIFT		16
#घोषणा BCH_BHERR_INDEX1_MASK		(0x1fff << BCH_BHERR_INDEX1_SHIFT)

#घोषणा BCH_BHINT_ERRC_SHIFT		28
#घोषणा BCH_BHINT_ERRC_MASK		(0xf << BCH_BHINT_ERRC_SHIFT)
#घोषणा BCH_BHINT_TERRC_SHIFT		16
#घोषणा BCH_BHINT_TERRC_MASK		(0x7f << BCH_BHINT_TERRC_SHIFT)
#घोषणा BCH_BHINT_ALL_0			BIT(5)
#घोषणा BCH_BHINT_ALL_F			BIT(4)
#घोषणा BCH_BHINT_DECF			BIT(3)
#घोषणा BCH_BHINT_ENCF			BIT(2)
#घोषणा BCH_BHINT_UNCOR			BIT(1)
#घोषणा BCH_BHINT_ERR			BIT(0)

/* Timeout क्रम BCH calculation/correction. */
#घोषणा BCH_TIMEOUT_US			100000

अटल अंतरभूत व्योम jz4725b_bch_config_set(काष्ठा ingenic_ecc *bch, u32 cfg)
अणु
	ग_लिखोl(cfg, bch->base + BCH_BHCSR);
पूर्ण

अटल अंतरभूत व्योम jz4725b_bch_config_clear(काष्ठा ingenic_ecc *bch, u32 cfg)
अणु
	ग_लिखोl(cfg, bch->base + BCH_BHCCR);
पूर्ण

अटल पूर्णांक jz4725b_bch_reset(काष्ठा ingenic_ecc *bch,
			     काष्ठा ingenic_ecc_params *params, bool calc_ecc)
अणु
	u32 reg, max_value;

	/* Clear पूर्णांकerrupt status. */
	ग_लिखोl(पढ़ोl(bch->base + BCH_BHINT), bch->base + BCH_BHINT);

	/* Initialise and enable BCH. */
	jz4725b_bch_config_clear(bch, 0x1f);
	jz4725b_bch_config_set(bch, BCH_BHCR_BCHE);

	अगर (params->strength == 8)
		jz4725b_bch_config_set(bch, BCH_BHCR_BSEL);
	अन्यथा
		jz4725b_bch_config_clear(bch, BCH_BHCR_BSEL);

	अगर (calc_ecc) /* calculate ECC from data */
		jz4725b_bch_config_set(bch, BCH_BHCR_ENCE);
	अन्यथा /* correct data from ECC */
		jz4725b_bch_config_clear(bch, BCH_BHCR_ENCE);

	jz4725b_bch_config_set(bch, BCH_BHCR_INIT);

	max_value = BCH_BHCNT_ENC_COUNT_MASK >> BCH_BHCNT_ENC_COUNT_SHIFT;
	अगर (params->size > max_value)
		वापस -EINVAL;

	max_value = BCH_BHCNT_DEC_COUNT_MASK >> BCH_BHCNT_DEC_COUNT_SHIFT;
	अगर (params->size + params->bytes > max_value)
		वापस -EINVAL;

	/* Set up BCH count रेजिस्टर. */
	reg = params->size << BCH_BHCNT_ENC_COUNT_SHIFT;
	reg |= (params->size + params->bytes) << BCH_BHCNT_DEC_COUNT_SHIFT;
	ग_लिखोl(reg, bch->base + BCH_BHCNT);

	वापस 0;
पूर्ण

अटल व्योम jz4725b_bch_disable(काष्ठा ingenic_ecc *bch)
अणु
	/* Clear पूर्णांकerrupts */
	ग_लिखोl(पढ़ोl(bch->base + BCH_BHINT), bch->base + BCH_BHINT);

	/* Disable the hardware */
	jz4725b_bch_config_clear(bch, BCH_BHCR_BCHE);
पूर्ण

अटल व्योम jz4725b_bch_ग_लिखो_data(काष्ठा ingenic_ecc *bch, स्थिर u8 *buf,
				   माप_प्रकार size)
अणु
	जबतक (size--)
		ग_लिखोb(*buf++, bch->base + BCH_BHDR);
पूर्ण

अटल व्योम jz4725b_bch_पढ़ो_parity(काष्ठा ingenic_ecc *bch, u8 *buf,
				    माप_प्रकार size)
अणु
	माप_प्रकार size32 = size / माप(u32);
	माप_प्रकार size8 = size % माप(u32);
	u32 *dest32;
	u8 *dest8;
	u32 val, offset = 0;

	dest32 = (u32 *)buf;
	जबतक (size32--) अणु
		*dest32++ = पढ़ोl_relaxed(bch->base + BCH_BHPAR0 + offset);
		offset += माप(u32);
	पूर्ण

	dest8 = (u8 *)dest32;
	val = पढ़ोl_relaxed(bch->base + BCH_BHPAR0 + offset);
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

अटल पूर्णांक jz4725b_bch_रुको_complete(काष्ठा ingenic_ecc *bch, अचिन्हित पूर्णांक irq,
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
	ret = पढ़ोl_relaxed_poll_समयout(bch->base + BCH_BHINT, reg,
					 reg & irq, 0, BCH_TIMEOUT_US);
	अगर (ret)
		वापस ret;

	अगर (status)
		*status = reg;

	ग_लिखोl(reg, bch->base + BCH_BHINT);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4725b_calculate(काष्ठा ingenic_ecc *bch,
			     काष्ठा ingenic_ecc_params *params,
			     स्थिर u8 *buf, u8 *ecc_code)
अणु
	पूर्णांक ret;

	mutex_lock(&bch->lock);

	ret = jz4725b_bch_reset(bch, params, true);
	अगर (ret) अणु
		dev_err(bch->dev, "Unable to init BCH with given parameters\n");
		जाओ out_disable;
	पूर्ण

	jz4725b_bch_ग_लिखो_data(bch, buf, params->size);

	ret = jz4725b_bch_रुको_complete(bch, BCH_BHINT_ENCF, शून्य);
	अगर (ret) अणु
		dev_err(bch->dev, "timed out while calculating ECC\n");
		जाओ out_disable;
	पूर्ण

	jz4725b_bch_पढ़ो_parity(bch, ecc_code, params->bytes);

out_disable:
	jz4725b_bch_disable(bch);
	mutex_unlock(&bch->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक jz4725b_correct(काष्ठा ingenic_ecc *bch,
			   काष्ठा ingenic_ecc_params *params,
			   u8 *buf, u8 *ecc_code)
अणु
	u32 reg, errors, bit;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	mutex_lock(&bch->lock);

	ret = jz4725b_bch_reset(bch, params, false);
	अगर (ret) अणु
		dev_err(bch->dev, "Unable to init BCH with given parameters\n");
		जाओ out;
	पूर्ण

	jz4725b_bch_ग_लिखो_data(bch, buf, params->size);
	jz4725b_bch_ग_लिखो_data(bch, ecc_code, params->bytes);

	ret = jz4725b_bch_रुको_complete(bch, BCH_BHINT_DECF, &reg);
	अगर (ret) अणु
		dev_err(bch->dev, "timed out while correcting data\n");
		जाओ out;
	पूर्ण

	अगर (reg & (BCH_BHINT_ALL_F | BCH_BHINT_ALL_0)) अणु
		/* Data and ECC is all 0xff or 0x00 - nothing to correct */
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (reg & BCH_BHINT_UNCOR) अणु
		/* Uncorrectable ECC error */
		ret = -EBADMSG;
		जाओ out;
	पूर्ण

	errors = (reg & BCH_BHINT_ERRC_MASK) >> BCH_BHINT_ERRC_SHIFT;

	/* Correct any detected errors. */
	क्रम (i = 0; i < errors; i++) अणु
		अगर (i & 1) अणु
			bit = (reg & BCH_BHERR_INDEX1_MASK) >> BCH_BHERR_INDEX1_SHIFT;
		पूर्ण अन्यथा अणु
			reg = पढ़ोl(bch->base + BCH_BHERR0 + (i * 4));
			bit = (reg & BCH_BHERR_INDEX0_MASK) >> BCH_BHERR_INDEX0_SHIFT;
		पूर्ण

		buf[(bit >> 3)] ^= BIT(bit & 0x7);
	पूर्ण

out:
	jz4725b_bch_disable(bch);
	mutex_unlock(&bch->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ingenic_ecc_ops jz4725b_bch_ops = अणु
	.disable = jz4725b_bch_disable,
	.calculate = jz4725b_calculate,
	.correct = jz4725b_correct,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jz4725b_bch_dt_match[] = अणु
	अणु .compatible = "ingenic,jz4725b-bch", .data = &jz4725b_bch_ops पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4725b_bch_dt_match);

अटल काष्ठा platक्रमm_driver jz4725b_bch_driver = अणु
	.probe		= ingenic_ecc_probe,
	.driver	= अणु
		.name	= "jz4725b-bch",
		.of_match_table = jz4725b_bch_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(jz4725b_bch_driver);

MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_DESCRIPTION("Ingenic JZ4725B BCH controller driver");
MODULE_LICENSE("GPL v2");
