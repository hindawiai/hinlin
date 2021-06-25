<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Silex Insight

#समावेश <linux/delay.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>

#घोषणा BA431_RESET_DELAY			1 /* usec */
#घोषणा BA431_RESET_READ_STATUS_TIMEOUT		1000 /* usec */
#घोषणा BA431_RESET_READ_STATUS_INTERVAL	10 /* usec */
#घोषणा BA431_READ_RETRY_INTERVAL		1 /* usec */

#घोषणा BA431_REG_CTRL				0x00
#घोषणा BA431_REG_FIFO_LEVEL			0x04
#घोषणा BA431_REG_STATUS			0x30
#घोषणा BA431_REG_FIFODATA			0x80

#घोषणा BA431_CTRL_ENABLE			BIT(0)
#घोषणा BA431_CTRL_SOFTRESET			BIT(8)

#घोषणा BA431_STATUS_STATE_MASK			(BIT(1) | BIT(2) | BIT(3))
#घोषणा BA431_STATUS_STATE_OFFSET		1

क्रमागत ba431_state अणु
	BA431_STATE_RESET,
	BA431_STATE_STARTUP,
	BA431_STATE_FIFOFULLON,
	BA431_STATE_FIFOFULLOFF,
	BA431_STATE_RUNNING,
	BA431_STATE_ERROR
पूर्ण;

काष्ठा ba431_trng अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा hwrng rng;
	atomic_t reset_pending;
	काष्ठा work_काष्ठा reset_work;
पूर्ण;

अटल अंतरभूत u32 ba431_trng_पढ़ो_reg(काष्ठा ba431_trng *ba431, u32 reg)
अणु
	वापस ioपढ़ो32(ba431->base + reg);
पूर्ण

अटल अंतरभूत व्योम ba431_trng_ग_लिखो_reg(काष्ठा ba431_trng *ba431, u32 reg,
					u32 val)
अणु
	ioग_लिखो32(val, ba431->base + reg);
पूर्ण

अटल अंतरभूत क्रमागत ba431_state ba431_trng_get_state(काष्ठा ba431_trng *ba431)
अणु
	u32 status = ba431_trng_पढ़ो_reg(ba431, BA431_REG_STATUS);

	वापस (status & BA431_STATUS_STATE_MASK) >> BA431_STATUS_STATE_OFFSET;
पूर्ण

अटल पूर्णांक ba431_trng_is_in_error(काष्ठा ba431_trng *ba431)
अणु
	क्रमागत ba431_state state = ba431_trng_get_state(ba431);

	अगर ((state < BA431_STATE_STARTUP) ||
	    (state >= BA431_STATE_ERROR))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ba431_trng_reset(काष्ठा ba431_trng *ba431)
अणु
	पूर्णांक ret;

	/* Disable पूर्णांकerrupts, अक्रमom generation and enable the softreset */
	ba431_trng_ग_लिखो_reg(ba431, BA431_REG_CTRL, BA431_CTRL_SOFTRESET);
	udelay(BA431_RESET_DELAY);
	ba431_trng_ग_लिखो_reg(ba431, BA431_REG_CTRL, BA431_CTRL_ENABLE);

	/* Wait until the state changed */
	अगर (पढ़ोx_poll_समयout(ba431_trng_is_in_error, ba431, ret, !ret,
			       BA431_RESET_READ_STATUS_INTERVAL,
			       BA431_RESET_READ_STATUS_TIMEOUT)) अणु
		dev_err(ba431->dev, "reset failed (state: %d)\n",
			ba431_trng_get_state(ba431));
		वापस -ETIMEDOUT;
	पूर्ण

	dev_info(ba431->dev, "reset done\n");

	वापस 0;
पूर्ण

अटल व्योम ba431_trng_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ba431_trng *ba431 = container_of(work, काष्ठा ba431_trng,
						reset_work);
	ba431_trng_reset(ba431);
	atomic_set(&ba431->reset_pending, 0);
पूर्ण

अटल व्योम ba431_trng_schedule_reset(काष्ठा ba431_trng *ba431)
अणु
	अगर (atomic_cmpxchg(&ba431->reset_pending, 0, 1))
		वापस;

	schedule_work(&ba431->reset_work);
पूर्ण

अटल पूर्णांक ba431_trng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा ba431_trng *ba431 = container_of(rng, काष्ठा ba431_trng, rng);
	u32 *data = buf;
	अचिन्हित पूर्णांक level, i;
	पूर्णांक n = 0;

	जबतक (max > 0) अणु
		level = ba431_trng_पढ़ो_reg(ba431, BA431_REG_FIFO_LEVEL);
		अगर (!level) अणु
			अगर (ba431_trng_is_in_error(ba431)) अणु
				ba431_trng_schedule_reset(ba431);
				अवरोध;
			पूर्ण

			अगर (!रुको)
				अवरोध;

			udelay(BA431_READ_RETRY_INTERVAL);
			जारी;
		पूर्ण

		i = level;
		करो अणु
			data[n++] = ba431_trng_पढ़ो_reg(ba431,
							BA431_REG_FIFODATA);
			max -= माप(*data);
		पूर्ण जबतक (--i && (max > 0));

		अगर (ba431_trng_is_in_error(ba431)) अणु
			n -= (level - i);
			ba431_trng_schedule_reset(ba431);
			अवरोध;
		पूर्ण
	पूर्ण

	n *= माप(data);
	वापस (n || !रुको) ? n : -EIO;
पूर्ण

अटल व्योम ba431_trng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा ba431_trng *ba431 = container_of(rng, काष्ठा ba431_trng, rng);

	ba431_trng_ग_लिखो_reg(ba431, BA431_REG_CTRL, 0);
	cancel_work_sync(&ba431->reset_work);
पूर्ण

अटल पूर्णांक ba431_trng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा ba431_trng *ba431 = container_of(rng, काष्ठा ba431_trng, rng);

	वापस ba431_trng_reset(ba431);
पूर्ण

अटल पूर्णांक ba431_trng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ba431_trng *ba431;
	पूर्णांक ret;

	ba431 = devm_kzalloc(&pdev->dev, माप(*ba431), GFP_KERNEL);
	अगर (!ba431)
		वापस -ENOMEM;

	ba431->dev = &pdev->dev;

	ba431->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ba431->base))
		वापस PTR_ERR(ba431->base);

	atomic_set(&ba431->reset_pending, 0);
	INIT_WORK(&ba431->reset_work, ba431_trng_reset_work);
	ba431->rng.name = pdev->name;
	ba431->rng.init = ba431_trng_init;
	ba431->rng.cleanup = ba431_trng_cleanup;
	ba431->rng.पढ़ो = ba431_trng_पढ़ो;

	platक्रमm_set_drvdata(pdev, ba431);

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &ba431->rng);
	अगर (ret) अणु
		dev_err(&pdev->dev, "BA431 registration failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "BA431 TRNG registered\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ba431_trng_dt_ids[] = अणु
	अणु .compatible = "silex-insight,ba431-rng", .data = शून्य पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ba431_trng_dt_ids);

अटल काष्ठा platक्रमm_driver ba431_trng_driver = अणु
	.driver = अणु
		.name = "ba431-rng",
		.of_match_table = ba431_trng_dt_ids,
	पूर्ण,
	.probe = ba431_trng_probe,
पूर्ण;

module_platक्रमm_driver(ba431_trng_driver);

MODULE_AUTHOR("Olivier Sobrie <olivier@sobrie.be>");
MODULE_DESCRIPTION("TRNG driver for Silex Insight BA431");
MODULE_LICENSE("GPL");
