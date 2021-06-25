<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2019-2020 ARM Limited or its affiliates. */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/completion.h>
#समावेश <linux/of.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/fips.h>

#समावेश "cctrng.h"

#घोषणा CC_REG_LOW(name)  (name ## _BIT_SHIFT)
#घोषणा CC_REG_HIGH(name) (CC_REG_LOW(name) + name ## _BIT_SIZE - 1)
#घोषणा CC_GENMASK(name)  GENMASK(CC_REG_HIGH(name), CC_REG_LOW(name))

#घोषणा CC_REG_FLD_GET(reg_name, fld_name, reg_val)     \
	(FIELD_GET(CC_GENMASK(CC_ ## reg_name ## _ ## fld_name), reg_val))

#घोषणा CC_HW_RESET_LOOP_COUNT 10
#घोषणा CC_TRNG_SUSPEND_TIMEOUT 3000

/* data circular buffer in words must be:
 *  - of a घातer-of-2 size (limitation of circ_buf.h macros)
 *  - at least 6, the size generated in the EHR according to HW implementation
 */
#घोषणा CCTRNG_DATA_BUF_WORDS 32

/* The समयout क्रम the TRNG operation should be calculated with the क्रमmula:
 * Timeout = EHR_NUM * VN_COEFF * EHR_LENGTH * SAMPLE_CNT * SCALE_VALUE
 * जबतक:
 *  - SAMPLE_CNT is input value from the अक्षरacterisation process
 *  - all the rest are स्थिरants
 */
#घोषणा EHR_NUM 1
#घोषणा VN_COEFF 4
#घोषणा EHR_LENGTH CC_TRNG_EHR_IN_BITS
#घोषणा SCALE_VALUE 2
#घोषणा CCTRNG_TIMEOUT(smpl_cnt) \
	(EHR_NUM * VN_COEFF * EHR_LENGTH * smpl_cnt * SCALE_VALUE)

काष्ठा cctrng_drvdata अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *cc_base;
	काष्ठा clk *clk;
	काष्ठा hwrng rng;
	u32 active_rosc;
	/* Sampling पूर्णांकerval क्रम each ring oscillator:
	 * count of ring oscillator cycles between consecutive bits sampling.
	 * Value of 0 indicates non-valid rosc
	 */
	u32 smpl_ratio[CC_TRNG_NUM_OF_ROSCS];

	u32 data_buf[CCTRNG_DATA_BUF_WORDS];
	काष्ठा circ_buf circ;
	काष्ठा work_काष्ठा compwork;
	काष्ठा work_काष्ठा startwork;

	/* pending_hw - 1 when HW is pending, 0 when it is idle */
	atomic_t pending_hw;

	/* protects against multiple concurrent consumers of data_buf */
	spinlock_t पढ़ो_lock;
पूर्ण;


/* functions क्रम ग_लिखो/पढ़ो CC रेजिस्टरs */
अटल अंतरभूत व्योम cc_ioग_लिखो(काष्ठा cctrng_drvdata *drvdata, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, (drvdata->cc_base + reg));
पूर्ण
अटल अंतरभूत u32 cc_ioपढ़ो(काष्ठा cctrng_drvdata *drvdata, u32 reg)
अणु
	वापस ioपढ़ो32(drvdata->cc_base + reg);
पूर्ण


अटल पूर्णांक cc_trng_pm_get(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;

	rc = pm_runसमय_get_sync(dev);

	/* pm_runसमय_get_sync() can वापस 1 as a valid वापस code */
	वापस (rc == 1 ? 0 : rc);
पूर्ण

अटल व्योम cc_trng_pm_put_suspend(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;

	pm_runसमय_mark_last_busy(dev);
	rc = pm_runसमय_put_स्वतःsuspend(dev);
	अगर (rc)
		dev_err(dev, "pm_runtime_put_autosuspend returned %x\n", rc);
पूर्ण

अटल पूर्णांक cc_trng_pm_init(काष्ठा cctrng_drvdata *drvdata)
अणु
	काष्ठा device *dev = &(drvdata->pdev->dev);

	/* must be beक्रमe the enabling to aव्योम redundant suspending */
	pm_runसमय_set_स्वतःsuspend_delay(dev, CC_TRNG_SUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(dev);
	/* set us as active - note we won't करो PM ops until cc_trng_pm_go()! */
	वापस pm_runसमय_set_active(dev);
पूर्ण

अटल व्योम cc_trng_pm_go(काष्ठा cctrng_drvdata *drvdata)
अणु
	काष्ठा device *dev = &(drvdata->pdev->dev);

	/* enable the PM module*/
	pm_runसमय_enable(dev);
पूर्ण

अटल व्योम cc_trng_pm_fini(काष्ठा cctrng_drvdata *drvdata)
अणु
	काष्ठा device *dev = &(drvdata->pdev->dev);

	pm_runसमय_disable(dev);
पूर्ण


अटल अंतरभूत पूर्णांक cc_trng_parse_sampling_ratio(काष्ठा cctrng_drvdata *drvdata)
अणु
	काष्ठा device *dev = &(drvdata->pdev->dev);
	काष्ठा device_node *np = drvdata->pdev->dev.of_node;
	पूर्णांक rc;
	पूर्णांक i;
	/* ret will be set to 0 अगर at least one rosc has (sampling ratio > 0) */
	पूर्णांक ret = -EINVAL;

	rc = of_property_पढ़ो_u32_array(np, "arm,rosc-ratio",
					drvdata->smpl_ratio,
					CC_TRNG_NUM_OF_ROSCS);
	अगर (rc) अणु
		/* arm,rosc-ratio was not found in device tree */
		वापस rc;
	पूर्ण

	/* verअगरy that at least one rosc has (sampling ratio > 0) */
	क्रम (i = 0; i < CC_TRNG_NUM_OF_ROSCS; ++i) अणु
		dev_dbg(dev, "rosc %d sampling ratio %u",
			i, drvdata->smpl_ratio[i]);

		अगर (drvdata->smpl_ratio[i] > 0)
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cc_trng_change_rosc(काष्ठा cctrng_drvdata *drvdata)
अणु
	काष्ठा device *dev = &(drvdata->pdev->dev);

	dev_dbg(dev, "cctrng change rosc (was %d)\n", drvdata->active_rosc);
	drvdata->active_rosc += 1;

	जबतक (drvdata->active_rosc < CC_TRNG_NUM_OF_ROSCS) अणु
		अगर (drvdata->smpl_ratio[drvdata->active_rosc] > 0)
			वापस 0;

		drvdata->active_rosc += 1;
	पूर्ण
	वापस -EINVAL;
पूर्ण


अटल व्योम cc_trng_enable_rnd_source(काष्ठा cctrng_drvdata *drvdata)
अणु
	u32 max_cycles;

	/* Set watchकरोg threshold to maximal allowed समय (in CPU cycles) */
	max_cycles = CCTRNG_TIMEOUT(drvdata->smpl_ratio[drvdata->active_rosc]);
	cc_ioग_लिखो(drvdata, CC_RNG_WATCHDOG_VAL_REG_OFFSET, max_cycles);

	/* enable the RND source */
	cc_ioग_लिखो(drvdata, CC_RND_SOURCE_ENABLE_REG_OFFSET, 0x1);

	/* unmask RNG पूर्णांकerrupts */
	cc_ioग_लिखो(drvdata, CC_RNG_IMR_REG_OFFSET, (u32)~CC_RNG_INT_MASK);
पूर्ण


/* increase circular data buffer index (head/tail) */
अटल अंतरभूत व्योम circ_idx_inc(पूर्णांक *idx, पूर्णांक bytes)
अणु
	*idx += (bytes + 3) >> 2;
	*idx &= (CCTRNG_DATA_BUF_WORDS - 1);
पूर्ण

अटल अंतरभूत माप_प्रकार circ_buf_space(काष्ठा cctrng_drvdata *drvdata)
अणु
	वापस CIRC_SPACE(drvdata->circ.head,
			  drvdata->circ.tail, CCTRNG_DATA_BUF_WORDS);

पूर्ण

अटल पूर्णांक cctrng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	/* current implementation ignores "wait" */

	काष्ठा cctrng_drvdata *drvdata = (काष्ठा cctrng_drvdata *)rng->priv;
	काष्ठा device *dev = &(drvdata->pdev->dev);
	u32 *buf = (u32 *)drvdata->circ.buf;
	माप_प्रकार copied = 0;
	माप_प्रकार cnt_w;
	माप_प्रकार size;
	माप_प्रकार left;

	अगर (!spin_trylock(&drvdata->पढ़ो_lock)) अणु
		/* concurrent consumers from data_buf cannot be served */
		dev_dbg_ratelimited(dev, "unable to hold lock\n");
		वापस 0;
	पूर्ण

	/* copy till end of data buffer (without wrap back) */
	cnt_w = CIRC_CNT_TO_END(drvdata->circ.head,
				drvdata->circ.tail, CCTRNG_DATA_BUF_WORDS);
	size = min((cnt_w<<2), max);
	स_नकल(data, &(buf[drvdata->circ.tail]), size);
	copied = size;
	circ_idx_inc(&drvdata->circ.tail, size);
	/* copy rest of data in data buffer */
	left = max - copied;
	अगर (left > 0) अणु
		cnt_w = CIRC_CNT(drvdata->circ.head,
				 drvdata->circ.tail, CCTRNG_DATA_BUF_WORDS);
		size = min((cnt_w<<2), left);
		स_नकल(data, &(buf[drvdata->circ.tail]), size);
		copied += size;
		circ_idx_inc(&drvdata->circ.tail, size);
	पूर्ण

	spin_unlock(&drvdata->पढ़ो_lock);

	अगर (circ_buf_space(drvdata) >= CC_TRNG_EHR_IN_WORDS) अणु
		अगर (atomic_cmpxchg(&drvdata->pending_hw, 0, 1) == 0) अणु
			/* re-check space in buffer to aव्योम potential race */
			अगर (circ_buf_space(drvdata) >= CC_TRNG_EHR_IN_WORDS) अणु
				/* increment device's usage counter */
				पूर्णांक rc = cc_trng_pm_get(dev);

				अगर (rc) अणु
					dev_err(dev,
						"cc_trng_pm_get returned %x\n",
						rc);
					वापस rc;
				पूर्ण

				/* schedule execution of deferred work handler
				 * क्रम filling of data buffer
				 */
				schedule_work(&drvdata->startwork);
			पूर्ण अन्यथा अणु
				atomic_set(&drvdata->pending_hw, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस copied;
पूर्ण

अटल व्योम cc_trng_hw_trigger(काष्ठा cctrng_drvdata *drvdata)
अणु
	u32 पंचांगp_smpl_cnt = 0;
	काष्ठा device *dev = &(drvdata->pdev->dev);

	dev_dbg(dev, "cctrng hw trigger.\n");

	/* enable the HW RND घड़ी */
	cc_ioग_लिखो(drvdata, CC_RNG_CLK_ENABLE_REG_OFFSET, 0x1);

	/* करो software reset */
	cc_ioग_लिखो(drvdata, CC_RNG_SW_RESET_REG_OFFSET, 0x1);
	/* in order to verअगरy that the reset has completed,
	 * the sample count need to be verअगरied
	 */
	करो अणु
		/* enable the HW RND घड़ी   */
		cc_ioग_लिखो(drvdata, CC_RNG_CLK_ENABLE_REG_OFFSET, 0x1);

		/* set sampling ratio (rng_घड़ीs) between consecutive bits */
		cc_ioग_लिखो(drvdata, CC_SAMPLE_CNT1_REG_OFFSET,
			   drvdata->smpl_ratio[drvdata->active_rosc]);

		/* पढ़ो the sampling ratio  */
		पंचांगp_smpl_cnt = cc_ioपढ़ो(drvdata, CC_SAMPLE_CNT1_REG_OFFSET);

	पूर्ण जबतक (पंचांगp_smpl_cnt != drvdata->smpl_ratio[drvdata->active_rosc]);

	/* disable the RND source क्रम setting new parameters in HW */
	cc_ioग_लिखो(drvdata, CC_RND_SOURCE_ENABLE_REG_OFFSET, 0);

	cc_ioग_लिखो(drvdata, CC_RNG_ICR_REG_OFFSET, 0xFFFFFFFF);

	cc_ioग_लिखो(drvdata, CC_TRNG_CONFIG_REG_OFFSET, drvdata->active_rosc);

	/* Debug Control रेजिस्टर: set to 0 - no bypasses */
	cc_ioग_लिखो(drvdata, CC_TRNG_DEBUG_CONTROL_REG_OFFSET, 0);

	cc_trng_enable_rnd_source(drvdata);
पूर्ण

अटल व्योम cc_trng_compwork_handler(काष्ठा work_काष्ठा *w)
अणु
	u32 isr = 0;
	u32 ehr_valid = 0;
	काष्ठा cctrng_drvdata *drvdata =
			container_of(w, काष्ठा cctrng_drvdata, compwork);
	काष्ठा device *dev = &(drvdata->pdev->dev);
	पूर्णांक i;

	/* stop DMA and the RNG source */
	cc_ioग_लिखो(drvdata, CC_RNG_DMA_ENABLE_REG_OFFSET, 0);
	cc_ioग_लिखो(drvdata, CC_RND_SOURCE_ENABLE_REG_OFFSET, 0);

	/* पढ़ो RNG_ISR and check क्रम errors */
	isr = cc_ioपढ़ो(drvdata, CC_RNG_ISR_REG_OFFSET);
	ehr_valid = CC_REG_FLD_GET(RNG_ISR, EHR_VALID, isr);
	dev_dbg(dev, "Got RNG_ISR=0x%08X (EHR_VALID=%u)\n", isr, ehr_valid);

	अगर (fips_enabled && CC_REG_FLD_GET(RNG_ISR, CRNGT_ERR, isr)) अणु
		fips_fail_notअगरy();
		/* FIPS error is fatal */
		panic("Got HW CRNGT error while fips is enabled!\n");
	पूर्ण

	/* Clear all pending RNG पूर्णांकerrupts */
	cc_ioग_लिखो(drvdata, CC_RNG_ICR_REG_OFFSET, isr);


	अगर (!ehr_valid) अणु
		/* in हाल of AUTOCORR/TIMEOUT error, try the next ROSC */
		अगर (CC_REG_FLD_GET(RNG_ISR, AUTOCORR_ERR, isr) ||
				CC_REG_FLD_GET(RNG_ISR, WATCHDOG, isr)) अणु
			dev_dbg(dev, "cctrng autocorr/timeout error.\n");
			जाओ next_rosc;
		पूर्ण

		/* in हाल of VN error, ignore it */
	पूर्ण

	/* पढ़ो EHR data from रेजिस्टरs */
	क्रम (i = 0; i < CC_TRNG_EHR_IN_WORDS; i++) अणु
		/* calc word ptr in data_buf */
		u32 *buf = (u32 *)drvdata->circ.buf;

		buf[drvdata->circ.head] = cc_ioपढ़ो(drvdata,
				CC_EHR_DATA_0_REG_OFFSET + (i*माप(u32)));

		/* EHR_DATA रेजिस्टरs are cleared on पढ़ो. In हाल 0 value was
		 * वापसed, restart the entropy collection.
		 */
		अगर (buf[drvdata->circ.head] == 0) अणु
			dev_dbg(dev, "Got 0 value in EHR. active_rosc %u\n",
				drvdata->active_rosc);
			जाओ next_rosc;
		पूर्ण

		circ_idx_inc(&drvdata->circ.head, 1<<2);
	पूर्ण

	atomic_set(&drvdata->pending_hw, 0);

	/* जारी to fill data buffer अगर needed */
	अगर (circ_buf_space(drvdata) >= CC_TRNG_EHR_IN_WORDS) अणु
		अगर (atomic_cmpxchg(&drvdata->pending_hw, 0, 1) == 0) अणु
			/* Re-enable rnd source */
			cc_trng_enable_rnd_source(drvdata);
			वापस;
		पूर्ण
	पूर्ण

	cc_trng_pm_put_suspend(dev);

	dev_dbg(dev, "compwork handler done\n");
	वापस;

next_rosc:
	अगर ((circ_buf_space(drvdata) >= CC_TRNG_EHR_IN_WORDS) &&
			(cc_trng_change_rosc(drvdata) == 0)) अणु
		/* trigger trng hw with next rosc */
		cc_trng_hw_trigger(drvdata);
	पूर्ण अन्यथा अणु
		atomic_set(&drvdata->pending_hw, 0);
		cc_trng_pm_put_suspend(dev);
	पूर्ण
पूर्ण

अटल irqवापस_t cc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cctrng_drvdata *drvdata = (काष्ठा cctrng_drvdata *)dev_id;
	काष्ठा device *dev = &(drvdata->pdev->dev);
	u32 irr;

	/* अगर driver suspended वापस, probably shared पूर्णांकerrupt */
	अगर (pm_runसमय_suspended(dev))
		वापस IRQ_NONE;

	/* पढ़ो the पूर्णांकerrupt status */
	irr = cc_ioपढ़ो(drvdata, CC_HOST_RGF_IRR_REG_OFFSET);
	dev_dbg(dev, "Got IRR=0x%08X\n", irr);

	अगर (irr == 0) /* Probably shared पूर्णांकerrupt line */
		वापस IRQ_NONE;

	/* clear पूर्णांकerrupt - must be beक्रमe processing events */
	cc_ioग_लिखो(drvdata, CC_HOST_RGF_ICR_REG_OFFSET, irr);

	/* RNG पूर्णांकerrupt - most probable */
	अगर (irr & CC_HOST_RNG_IRQ_MASK) अणु
		/* Mask RNG पूर्णांकerrupts - will be unmasked in deferred work */
		cc_ioग_लिखो(drvdata, CC_RNG_IMR_REG_OFFSET, 0xFFFFFFFF);

		/* We clear RNG पूर्णांकerrupt here,
		 * to aव्योम it from firing as we'll unmask RNG पूर्णांकerrupts.
		 */
		cc_ioग_लिखो(drvdata, CC_HOST_RGF_ICR_REG_OFFSET,
			   CC_HOST_RNG_IRQ_MASK);

		irr &= ~CC_HOST_RNG_IRQ_MASK;

		/* schedule execution of deferred work handler */
		schedule_work(&drvdata->compwork);
	पूर्ण

	अगर (irr) अणु
		dev_dbg_ratelimited(dev,
				"IRR includes unknown cause bits (0x%08X)\n",
				irr);
		/* Just warning */
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cc_trng_startwork_handler(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा cctrng_drvdata *drvdata =
			container_of(w, काष्ठा cctrng_drvdata, startwork);

	drvdata->active_rosc = 0;
	cc_trng_hw_trigger(drvdata);
पूर्ण


अटल पूर्णांक cc_trng_clk_init(काष्ठा cctrng_drvdata *drvdata)
अणु
	काष्ठा clk *clk;
	काष्ठा device *dev = &(drvdata->pdev->dev);
	पूर्णांक rc = 0;

	clk = devm_clk_get_optional(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(dev, PTR_ERR(clk),
				     "Error getting clock\n");

	drvdata->clk = clk;

	rc = clk_prepare_enable(drvdata->clk);
	अगर (rc) अणु
		dev_err(dev, "Failed to enable clock\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cc_trng_clk_fini(काष्ठा cctrng_drvdata *drvdata)
अणु
	clk_disable_unprepare(drvdata->clk);
पूर्ण


अटल पूर्णांक cctrng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cctrng_drvdata *drvdata;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक rc = 0;
	u32 val;
	पूर्णांक irq;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->rng.name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	अगर (!drvdata->rng.name)
		वापस -ENOMEM;

	drvdata->rng.पढ़ो = cctrng_पढ़ो;
	drvdata->rng.priv = (अचिन्हित दीर्घ)drvdata;
	drvdata->rng.quality = CC_TRNG_QUALITY;

	platक्रमm_set_drvdata(pdev, drvdata);
	drvdata->pdev = pdev;

	drvdata->circ.buf = (अक्षर *)drvdata->data_buf;

	drvdata->cc_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(drvdata->cc_base)) अणु
		dev_err(dev, "Failed to ioremap registers");
		वापस PTR_ERR(drvdata->cc_base);
	पूर्ण

	/* Then IRQ */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	/* parse sampling rate from device tree */
	rc = cc_trng_parse_sampling_ratio(drvdata);
	अगर (rc) अणु
		dev_err(dev, "Failed to get legal sampling ratio for rosc\n");
		वापस rc;
	पूर्ण

	rc = cc_trng_clk_init(drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_trng_clk_init failed\n");
		वापस rc;
	पूर्ण

	INIT_WORK(&drvdata->compwork, cc_trng_compwork_handler);
	INIT_WORK(&drvdata->startwork, cc_trng_startwork_handler);
	spin_lock_init(&drvdata->पढ़ो_lock);

	/* रेजिस्टर the driver isr function */
	rc = devm_request_irq(dev, irq, cc_isr, IRQF_SHARED, "cctrng", drvdata);
	अगर (rc) अणु
		dev_err(dev, "Could not register to interrupt %d\n", irq);
		जाओ post_clk_err;
	पूर्ण
	dev_dbg(dev, "Registered to IRQ: %d\n", irq);

	/* Clear all pending पूर्णांकerrupts */
	val = cc_ioपढ़ो(drvdata, CC_HOST_RGF_IRR_REG_OFFSET);
	dev_dbg(dev, "IRR=0x%08X\n", val);
	cc_ioग_लिखो(drvdata, CC_HOST_RGF_ICR_REG_OFFSET, val);

	/* unmask HOST RNG पूर्णांकerrupt */
	cc_ioग_लिखो(drvdata, CC_HOST_RGF_IMR_REG_OFFSET,
		   cc_ioपढ़ो(drvdata, CC_HOST_RGF_IMR_REG_OFFSET) &
		   ~CC_HOST_RNG_IRQ_MASK);

	/* init PM */
	rc = cc_trng_pm_init(drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_trng_pm_init failed\n");
		जाओ post_clk_err;
	पूर्ण

	/* increment device's usage counter */
	rc = cc_trng_pm_get(dev);
	अगर (rc) अणु
		dev_err(dev, "cc_trng_pm_get returned %x\n", rc);
		जाओ post_pm_err;
	पूर्ण

	/* set pending_hw to verअगरy that HW won't be triggered from पढ़ो */
	atomic_set(&drvdata->pending_hw, 1);

	/* registration of the hwrng device */
	rc = devm_hwrng_रेजिस्टर(dev, &drvdata->rng);
	अगर (rc) अणु
		dev_err(dev, "Could not register hwrng device.\n");
		जाओ post_pm_err;
	पूर्ण

	/* trigger HW to start generate data */
	drvdata->active_rosc = 0;
	cc_trng_hw_trigger(drvdata);

	/* All set, we can allow स्वतः-suspend */
	cc_trng_pm_go(drvdata);

	dev_info(dev, "ARM cctrng device initialized\n");

	वापस 0;

post_pm_err:
	cc_trng_pm_fini(drvdata);

post_clk_err:
	cc_trng_clk_fini(drvdata);

	वापस rc;
पूर्ण

अटल पूर्णांक cctrng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cctrng_drvdata *drvdata = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;

	dev_dbg(dev, "Releasing cctrng resources...\n");

	cc_trng_pm_fini(drvdata);

	cc_trng_clk_fini(drvdata);

	dev_info(dev, "ARM cctrng device terminated\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cctrng_suspend(काष्ठा device *dev)
अणु
	काष्ठा cctrng_drvdata *drvdata = dev_get_drvdata(dev);

	dev_dbg(dev, "set HOST_POWER_DOWN_EN\n");
	cc_ioग_लिखो(drvdata, CC_HOST_POWER_DOWN_EN_REG_OFFSET,
			POWER_DOWN_ENABLE);

	clk_disable_unprepare(drvdata->clk);

	वापस 0;
पूर्ण

अटल bool cctrng_रुको_क्रम_reset_completion(काष्ठा cctrng_drvdata *drvdata)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < CC_HW_RESET_LOOP_COUNT; i++) अणु
		/* in cc7x3 NVM_IS_IDLE indicates that CC reset is
		 *  completed and device is fully functional
		 */
		val = cc_ioपढ़ो(drvdata, CC_NVM_IS_IDLE_REG_OFFSET);
		अगर (val & BIT(CC_NVM_IS_IDLE_VALUE_BIT_SHIFT)) अणु
			/* hw indicate reset completed */
			वापस true;
		पूर्ण
		/* allow scheduling other process on the processor */
		schedule();
	पूर्ण
	/* reset not completed */
	वापस false;
पूर्ण

अटल पूर्णांक __maybe_unused cctrng_resume(काष्ठा device *dev)
अणु
	काष्ठा cctrng_drvdata *drvdata = dev_get_drvdata(dev);
	पूर्णांक rc;

	dev_dbg(dev, "unset HOST_POWER_DOWN_EN\n");
	/* Enables the device source clk */
	rc = clk_prepare_enable(drvdata->clk);
	अगर (rc) अणु
		dev_err(dev, "failed getting clock back on. We're toast.\n");
		वापस rc;
	पूर्ण

	/* रुको क्रम Cryptocell reset completion */
	अगर (!cctrng_रुको_क्रम_reset_completion(drvdata)) अणु
		dev_err(dev, "Cryptocell reset not completed");
		वापस -EBUSY;
	पूर्ण

	/* unmask HOST RNG पूर्णांकerrupt */
	cc_ioग_लिखो(drvdata, CC_HOST_RGF_IMR_REG_OFFSET,
		   cc_ioपढ़ो(drvdata, CC_HOST_RGF_IMR_REG_OFFSET) &
		   ~CC_HOST_RNG_IRQ_MASK);

	cc_ioग_लिखो(drvdata, CC_HOST_POWER_DOWN_EN_REG_OFFSET,
		   POWER_DOWN_DISABLE);

	वापस 0;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(cctrng_pm, cctrng_suspend, cctrng_resume, शून्य);

अटल स्थिर काष्ठा of_device_id arm_cctrng_dt_match[] = अणु
	अणु .compatible = "arm,cryptocell-713-trng", पूर्ण,
	अणु .compatible = "arm,cryptocell-703-trng", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_cctrng_dt_match);

अटल काष्ठा platक्रमm_driver cctrng_driver = अणु
	.driver = अणु
		.name = "cctrng",
		.of_match_table = arm_cctrng_dt_match,
		.pm = &cctrng_pm,
	पूर्ण,
	.probe = cctrng_probe,
	.हटाओ = cctrng_हटाओ,
पूर्ण;

अटल पूर्णांक __init cctrng_mod_init(व्योम)
अणु
	/* Compile समय निश्चितion checks */
	BUILD_BUG_ON(CCTRNG_DATA_BUF_WORDS < 6);
	BUILD_BUG_ON((CCTRNG_DATA_BUF_WORDS & (CCTRNG_DATA_BUF_WORDS-1)) != 0);

	वापस platक्रमm_driver_रेजिस्टर(&cctrng_driver);
पूर्ण
module_init(cctrng_mod_init);

अटल व्योम __निकास cctrng_mod_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cctrng_driver);
पूर्ण
module_निकास(cctrng_mod_निकास);

/* Module description */
MODULE_DESCRIPTION("ARM CryptoCell TRNG Driver");
MODULE_AUTHOR("ARM");
MODULE_LICENSE("GPL v2");
