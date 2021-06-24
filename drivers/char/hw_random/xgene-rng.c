<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * APM X-Gene SoC RNG Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Rameshwar Prasad Sahu <rsahu@apm.com>
 *	   Shamal Winchurkar <swinchurkar@apm.com>
 *	   Feng Kan <fkan@apm.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/समयr.h>

#घोषणा RNG_MAX_DATUM			4
#घोषणा MAX_TRY				100
#घोषणा XGENE_RNG_RETRY_COUNT		20
#घोषणा XGENE_RNG_RETRY_INTERVAL	10

/* RNG  Registers */
#घोषणा RNG_INOUT_0			0x00
#घोषणा RNG_INTR_STS_ACK		0x10
#घोषणा RNG_CONTROL			0x14
#घोषणा RNG_CONFIG			0x18
#घोषणा RNG_ALARMCNT			0x1c
#घोषणा RNG_FROENABLE			0x20
#घोषणा RNG_FRODETUNE			0x24
#घोषणा RNG_ALARMMASK			0x28
#घोषणा RNG_ALARMSTOP			0x2c
#घोषणा RNG_OPTIONS			0x78
#घोषणा RNG_EIP_REV			0x7c

#घोषणा MONOBIT_FAIL_MASK		BIT(7)
#घोषणा POKER_FAIL_MASK			BIT(6)
#घोषणा LONG_RUN_FAIL_MASK		BIT(5)
#घोषणा RUN_FAIL_MASK			BIT(4)
#घोषणा NOISE_FAIL_MASK			BIT(3)
#घोषणा STUCK_OUT_MASK			BIT(2)
#घोषणा SHUTDOWN_OFLO_MASK		BIT(1)
#घोषणा READY_MASK			BIT(0)

#घोषणा MAJOR_HW_REV_RD(src)		(((src) & 0x0f000000) >> 24)
#घोषणा MINOR_HW_REV_RD(src)		(((src) & 0x00f00000) >> 20)
#घोषणा HW_PATCH_LEVEL_RD(src)		(((src) & 0x000f0000) >> 16)
#घोषणा MAX_REFILL_CYCLES_SET(dst, src) \
			((dst & ~0xffff0000) | (((u32)src << 16) & 0xffff0000))
#घोषणा MIN_REFILL_CYCLES_SET(dst, src) \
			((dst & ~0x000000ff) | (((u32)src) & 0x000000ff))
#घोषणा ALARM_THRESHOLD_SET(dst, src) \
			((dst & ~0x000000ff) | (((u32)src) & 0x000000ff))
#घोषणा ENABLE_RNG_SET(dst, src) \
			((dst & ~BIT(10)) | (((u32)src << 10) & BIT(10)))
#घोषणा REGSPEC_TEST_MODE_SET(dst, src) \
			((dst & ~BIT(8)) | (((u32)src << 8) & BIT(8)))
#घोषणा MONOBIT_FAIL_MASK_SET(dst, src) \
			((dst & ~BIT(7)) | (((u32)src << 7) & BIT(7)))
#घोषणा POKER_FAIL_MASK_SET(dst, src) \
			((dst & ~BIT(6)) | (((u32)src << 6) & BIT(6)))
#घोषणा LONG_RUN_FAIL_MASK_SET(dst, src) \
			((dst & ~BIT(5)) | (((u32)src << 5) & BIT(5)))
#घोषणा RUN_FAIL_MASK_SET(dst, src) \
			((dst & ~BIT(4)) | (((u32)src << 4) & BIT(4)))
#घोषणा NOISE_FAIL_MASK_SET(dst, src) \
			((dst & ~BIT(3)) | (((u32)src << 3) & BIT(3)))
#घोषणा STUCK_OUT_MASK_SET(dst, src) \
			((dst & ~BIT(2)) | (((u32)src << 2) & BIT(2)))
#घोषणा SHUTDOWN_OFLO_MASK_SET(dst, src) \
			((dst & ~BIT(1)) | (((u32)src << 1) & BIT(1)))

काष्ठा xgene_rng_dev अणु
	u32 irq;
	व्योम  __iomem *csr_base;
	u32 revision;
	u32 datum_size;
	u32 failure_cnt;	/* Failure count last minute */
	अचिन्हित दीर्घ failure_ts;/* First failure बारtamp */
	काष्ठा समयr_list failure_समयr;
	काष्ठा device *dev;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम xgene_rng_expired_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा xgene_rng_dev *ctx = from_समयr(ctx, t, failure_समयr);

	/* Clear failure counter as समयr expired */
	disable_irq(ctx->irq);
	ctx->failure_cnt = 0;
	del_समयr(&ctx->failure_समयr);
	enable_irq(ctx->irq);
पूर्ण

अटल व्योम xgene_rng_start_समयr(काष्ठा xgene_rng_dev *ctx)
अणु
	ctx->failure_समयr.expires = jअगरfies + 120 * HZ;
	add_समयr(&ctx->failure_समयr);
पूर्ण

/*
 * Initialize or reinit मुक्त running oscillators (FROs)
 */
अटल व्योम xgene_rng_init_fro(काष्ठा xgene_rng_dev *ctx, u32 fro_val)
अणु
	ग_लिखोl(fro_val, ctx->csr_base + RNG_FRODETUNE);
	ग_लिखोl(0x00000000, ctx->csr_base + RNG_ALARMMASK);
	ग_लिखोl(0x00000000, ctx->csr_base + RNG_ALARMSTOP);
	ग_लिखोl(0xFFFFFFFF, ctx->csr_base + RNG_FROENABLE);
पूर्ण

अटल व्योम xgene_rng_chk_overflow(काष्ठा xgene_rng_dev *ctx)
अणु
	u32 val;

	val = पढ़ोl(ctx->csr_base + RNG_INTR_STS_ACK);
	अगर (val & MONOBIT_FAIL_MASK)
		/*
		 * LFSR detected an out-of-bounds number of 1s after
		 * checking 20,000 bits (test T1 as specअगरied in the
		 * AIS-31 standard)
		 */
		dev_err(ctx->dev, "test monobit failure error 0x%08X\n", val);
	अगर (val & POKER_FAIL_MASK)
		/*
		 * LFSR detected an out-of-bounds value in at least one
		 * of the 16 poker_count_X counters or an out of bounds sum
		 * of squares value after checking 20,000 bits (test T2 as
		 * specअगरied in the AIS-31 standard)
		 */
		dev_err(ctx->dev, "test poker failure error 0x%08X\n", val);
	अगर (val & LONG_RUN_FAIL_MASK)
		/*
		 * LFSR detected a sequence of 34 identical bits
		 * (test T4 as specअगरied in the AIS-31 standard)
		 */
		dev_err(ctx->dev, "test long run failure error 0x%08X\n", val);
	अगर (val & RUN_FAIL_MASK)
		/*
		 * LFSR detected an outof-bounds value क्रम at least one
		 * of the running counters after checking 20,000 bits
		 * (test T3 as specअगरied in the AIS-31 standard)
		 */
		dev_err(ctx->dev, "test run failure error 0x%08X\n", val);
	अगर (val & NOISE_FAIL_MASK)
		/* LFSR detected a sequence of 48 identical bits */
		dev_err(ctx->dev, "noise failure error 0x%08X\n", val);
	अगर (val & STUCK_OUT_MASK)
		/*
		 * Detected output data रेजिस्टरs generated same value twice
		 * in a row
		 */
		dev_err(ctx->dev, "stuck out failure error 0x%08X\n", val);

	अगर (val & SHUTDOWN_OFLO_MASK) अणु
		u32 frostopped;

		/* FROs shut करोwn after a second error event. Try recover. */
		अगर (++ctx->failure_cnt == 1) अणु
			/* 1st समय, just recover */
			ctx->failure_ts = jअगरfies;
			frostopped = पढ़ोl(ctx->csr_base + RNG_ALARMSTOP);
			xgene_rng_init_fro(ctx, frostopped);

			/*
			 * We must start a समयr to clear out this error
			 * in हाल the प्रणाली समयr wrap around
			 */
			xgene_rng_start_समयr(ctx);
		पूर्ण अन्यथा अणु
			/* 2nd समय failure in lesser than 1 minute? */
			अगर (समय_after(ctx->failure_ts + 60 * HZ, jअगरfies)) अणु
				dev_err(ctx->dev,
					"FRO shutdown failure error 0x%08X\n",
					val);
			पूर्ण अन्यथा अणु
				/* 2nd समय failure after 1 minutes, recover */
				ctx->failure_ts = jअगरfies;
				ctx->failure_cnt = 1;
				/*
				 * We must start a समयr to clear out this
				 * error in हाल the प्रणाली समयr wrap
				 * around
				 */
				xgene_rng_start_समयr(ctx);
			पूर्ण
			frostopped = पढ़ोl(ctx->csr_base + RNG_ALARMSTOP);
			xgene_rng_init_fro(ctx, frostopped);
		पूर्ण
	पूर्ण
	/* Clear them all */
	ग_लिखोl(val, ctx->csr_base + RNG_INTR_STS_ACK);
पूर्ण

अटल irqवापस_t xgene_rng_irq_handler(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा xgene_rng_dev *ctx = (काष्ठा xgene_rng_dev *) id;

	/* RNG Alarm Counter overflow */
	xgene_rng_chk_overflow(ctx);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xgene_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	काष्ठा xgene_rng_dev *ctx = (काष्ठा xgene_rng_dev *) rng->priv;
	u32 i, val = 0;

	क्रम (i = 0; i < XGENE_RNG_RETRY_COUNT; i++) अणु
		val = पढ़ोl(ctx->csr_base + RNG_INTR_STS_ACK);
		अगर ((val & READY_MASK) || !रुको)
			अवरोध;
		udelay(XGENE_RNG_RETRY_INTERVAL);
	पूर्ण

	वापस (val & READY_MASK);
पूर्ण

अटल पूर्णांक xgene_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा xgene_rng_dev *ctx = (काष्ठा xgene_rng_dev *) rng->priv;
	पूर्णांक i;

	क्रम (i = 0; i < ctx->datum_size; i++)
		data[i] = पढ़ोl(ctx->csr_base + RNG_INOUT_0 + i * 4);

	/* Clear पढ़ोy bit to start next transaction */
	ग_लिखोl(READY_MASK, ctx->csr_base + RNG_INTR_STS_ACK);

	वापस ctx->datum_size << 2;
पूर्ण

अटल व्योम xgene_rng_init_पूर्णांकernal(काष्ठा xgene_rng_dev *ctx)
अणु
	u32 val;

	ग_लिखोl(0x00000000, ctx->csr_base + RNG_CONTROL);

	val = MAX_REFILL_CYCLES_SET(0, 10);
	val = MIN_REFILL_CYCLES_SET(val, 10);
	ग_लिखोl(val, ctx->csr_base + RNG_CONFIG);

	val = ALARM_THRESHOLD_SET(0, 0xFF);
	ग_लिखोl(val, ctx->csr_base + RNG_ALARMCNT);

	xgene_rng_init_fro(ctx, 0);

	ग_लिखोl(MONOBIT_FAIL_MASK |
		POKER_FAIL_MASK	|
		LONG_RUN_FAIL_MASK |
		RUN_FAIL_MASK |
		NOISE_FAIL_MASK |
		STUCK_OUT_MASK |
		SHUTDOWN_OFLO_MASK |
		READY_MASK, ctx->csr_base + RNG_INTR_STS_ACK);

	val = ENABLE_RNG_SET(0, 1);
	val = MONOBIT_FAIL_MASK_SET(val, 1);
	val = POKER_FAIL_MASK_SET(val, 1);
	val = LONG_RUN_FAIL_MASK_SET(val, 1);
	val = RUN_FAIL_MASK_SET(val, 1);
	val = NOISE_FAIL_MASK_SET(val, 1);
	val = STUCK_OUT_MASK_SET(val, 1);
	val = SHUTDOWN_OFLO_MASK_SET(val, 1);
	ग_लिखोl(val, ctx->csr_base + RNG_CONTROL);
पूर्ण

अटल पूर्णांक xgene_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा xgene_rng_dev *ctx = (काष्ठा xgene_rng_dev *) rng->priv;

	ctx->failure_cnt = 0;
	समयr_setup(&ctx->failure_समयr, xgene_rng_expired_समयr, 0);

	ctx->revision = पढ़ोl(ctx->csr_base + RNG_EIP_REV);

	dev_dbg(ctx->dev, "Rev %d.%d.%d\n",
		MAJOR_HW_REV_RD(ctx->revision),
		MINOR_HW_REV_RD(ctx->revision),
		HW_PATCH_LEVEL_RD(ctx->revision));

	dev_dbg(ctx->dev, "Options 0x%08X",
		पढ़ोl(ctx->csr_base + RNG_OPTIONS));

	xgene_rng_init_पूर्णांकernal(ctx);

	ctx->datum_size = RNG_MAX_DATUM;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_rng_acpi_match[] = अणु
	अणु "APMC0D18", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgene_rng_acpi_match);
#पूर्ण_अगर

अटल काष्ठा hwrng xgene_rng_func = अणु
	.name		= "xgene-rng",
	.init		= xgene_rng_init,
	.data_present	= xgene_rng_data_present,
	.data_पढ़ो	= xgene_rng_data_पढ़ो,
पूर्ण;

अटल पूर्णांक xgene_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_rng_dev *ctx;
	पूर्णांक rc = 0;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ctx);

	ctx->csr_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctx->csr_base))
		वापस PTR_ERR(ctx->csr_base);

	rc = platक्रमm_get_irq(pdev, 0);
	अगर (rc < 0)
		वापस rc;
	ctx->irq = rc;

	dev_dbg(&pdev->dev, "APM X-Gene RNG BASE %p ALARM IRQ %d",
		ctx->csr_base, ctx->irq);

	rc = devm_request_irq(&pdev->dev, ctx->irq, xgene_rng_irq_handler, 0,
				dev_name(&pdev->dev), ctx);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Could not request RNG alarm IRQ\n");
		वापस rc;
	पूर्ण

	/* Enable IP घड़ी */
	ctx->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ctx->clk)) अणु
		dev_warn(&pdev->dev, "Couldn't get the clock for RNG\n");
	पूर्ण अन्यथा अणु
		rc = clk_prepare_enable(ctx->clk);
		अगर (rc) अणु
			dev_warn(&pdev->dev,
				 "clock prepare enable failed for RNG");
			वापस rc;
		पूर्ण
	पूर्ण

	xgene_rng_func.priv = (अचिन्हित दीर्घ) ctx;

	rc = devm_hwrng_रेजिस्टर(&pdev->dev, &xgene_rng_func);
	अगर (rc) अणु
		dev_err(&pdev->dev, "RNG registering failed error %d\n", rc);
		अगर (!IS_ERR(ctx->clk))
			clk_disable_unprepare(ctx->clk);
		वापस rc;
	पूर्ण

	rc = device_init_wakeup(&pdev->dev, 1);
	अगर (rc) अणु
		dev_err(&pdev->dev, "RNG device_init_wakeup failed error %d\n",
			rc);
		अगर (!IS_ERR(ctx->clk))
			clk_disable_unprepare(ctx->clk);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_rng_dev *ctx = platक्रमm_get_drvdata(pdev);
	पूर्णांक rc;

	rc = device_init_wakeup(&pdev->dev, 0);
	अगर (rc)
		dev_err(&pdev->dev, "RNG init wakeup failed error %d\n", rc);
	अगर (!IS_ERR(ctx->clk))
		clk_disable_unprepare(ctx->clk);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_rng_of_match[] = अणु
	अणु .compatible = "apm,xgene-rng" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, xgene_rng_of_match);

अटल काष्ठा platक्रमm_driver xgene_rng_driver = अणु
	.probe = xgene_rng_probe,
	.हटाओ	= xgene_rng_हटाओ,
	.driver = अणु
		.name		= "xgene-rng",
		.of_match_table = xgene_rng_of_match,
		.acpi_match_table = ACPI_PTR(xgene_rng_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xgene_rng_driver);
MODULE_DESCRIPTION("APM X-Gene RNG driver");
MODULE_LICENSE("GPL");
