<शैली गुरु>
/*
* Copyright (C) 2015 Broadcom Corporation
*
* This program is मुक्त software; you can redistribute it and/or
* modअगरy it under the terms of the GNU General Public License as
* published by the Free Software Foundation version 2.
*
* This program is distributed "as is" WITHOUT ANY WARRANTY of any
* kind, whether express or implied; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License क्रम more details.
*/
/*
 * DESCRIPTION: The Broadcom iProc RNG200 Driver
 */

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>

/* Registers */
#घोषणा RNG_CTRL_OFFSET					0x00
#घोषणा RNG_CTRL_RNG_RBGEN_MASK				0x00001FFF
#घोषणा RNG_CTRL_RNG_RBGEN_ENABLE			0x00000001

#घोषणा RNG_SOFT_RESET_OFFSET				0x04
#घोषणा RNG_SOFT_RESET					0x00000001

#घोषणा RBG_SOFT_RESET_OFFSET				0x08
#घोषणा RBG_SOFT_RESET					0x00000001

#घोषणा RNG_INT_STATUS_OFFSET				0x18
#घोषणा RNG_INT_STATUS_MASTER_FAIL_LOCKOUT_IRQ_MASK	0x80000000
#घोषणा RNG_INT_STATUS_STARTUP_TRANSITIONS_MET_IRQ_MASK	0x00020000
#घोषणा RNG_INT_STATUS_NIST_FAIL_IRQ_MASK		0x00000020
#घोषणा RNG_INT_STATUS_TOTAL_BITS_COUNT_IRQ_MASK	0x00000001

#घोषणा RNG_FIFO_DATA_OFFSET				0x20

#घोषणा RNG_FIFO_COUNT_OFFSET				0x24
#घोषणा RNG_FIFO_COUNT_RNG_FIFO_COUNT_MASK		0x000000FF

काष्ठा iproc_rng200_dev अणु
	काष्ठा hwrng rng;
	व्योम __iomem *base;
पूर्ण;

#घोषणा to_rng_priv(rng)	container_of(rng, काष्ठा iproc_rng200_dev, rng)

अटल व्योम iproc_rng200_enable_set(व्योम __iomem *rng_base, bool enable)
अणु
	u32 val;

	val = ioपढ़ो32(rng_base + RNG_CTRL_OFFSET);
	val &= ~RNG_CTRL_RNG_RBGEN_MASK;

	अगर (enable)
		val |= RNG_CTRL_RNG_RBGEN_ENABLE;

	ioग_लिखो32(val, rng_base + RNG_CTRL_OFFSET);
पूर्ण

अटल व्योम iproc_rng200_restart(व्योम __iomem *rng_base)
अणु
	uपूर्णांक32_t val;

	iproc_rng200_enable_set(rng_base, false);

	/* Clear all पूर्णांकerrupt status */
	ioग_लिखो32(0xFFFFFFFFUL, rng_base + RNG_INT_STATUS_OFFSET);

	/* Reset RNG and RBG */
	val = ioपढ़ो32(rng_base + RBG_SOFT_RESET_OFFSET);
	val |= RBG_SOFT_RESET;
	ioग_लिखो32(val, rng_base + RBG_SOFT_RESET_OFFSET);

	val = ioपढ़ो32(rng_base + RNG_SOFT_RESET_OFFSET);
	val |= RNG_SOFT_RESET;
	ioग_लिखो32(val, rng_base + RNG_SOFT_RESET_OFFSET);

	val = ioपढ़ो32(rng_base + RNG_SOFT_RESET_OFFSET);
	val &= ~RNG_SOFT_RESET;
	ioग_लिखो32(val, rng_base + RNG_SOFT_RESET_OFFSET);

	val = ioपढ़ो32(rng_base + RBG_SOFT_RESET_OFFSET);
	val &= ~RBG_SOFT_RESET;
	ioग_लिखो32(val, rng_base + RBG_SOFT_RESET_OFFSET);

	iproc_rng200_enable_set(rng_base, true);
पूर्ण

अटल पूर्णांक iproc_rng200_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max,
			     bool रुको)
अणु
	काष्ठा iproc_rng200_dev *priv = to_rng_priv(rng);
	uपूर्णांक32_t num_reमुख्यing = max;
	uपूर्णांक32_t status;

	#घोषणा MAX_RESETS_PER_READ	1
	uपूर्णांक32_t num_resets = 0;

	#घोषणा MAX_IDLE_TIME	(1 * HZ)
	अचिन्हित दीर्घ idle_endसमय = jअगरfies + MAX_IDLE_TIME;

	जबतक ((num_reमुख्यing > 0) && समय_beक्रमe(jअगरfies, idle_endसमय)) अणु

		/* Is RNG sane? If not, reset it. */
		status = ioपढ़ो32(priv->base + RNG_INT_STATUS_OFFSET);
		अगर ((status & (RNG_INT_STATUS_MASTER_FAIL_LOCKOUT_IRQ_MASK |
			RNG_INT_STATUS_NIST_FAIL_IRQ_MASK)) != 0) अणु

			अगर (num_resets >= MAX_RESETS_PER_READ)
				वापस max - num_reमुख्यing;

			iproc_rng200_restart(priv->base);
			num_resets++;
		पूर्ण

		/* Are there any अक्रमom numbers available? */
		अगर ((ioपढ़ो32(priv->base + RNG_FIFO_COUNT_OFFSET) &
				RNG_FIFO_COUNT_RNG_FIFO_COUNT_MASK) > 0) अणु

			अगर (num_reमुख्यing >= माप(uपूर्णांक32_t)) अणु
				/* Buffer has room to store entire word */
				*(uपूर्णांक32_t *)buf = ioपढ़ो32(priv->base +
							RNG_FIFO_DATA_OFFSET);
				buf += माप(uपूर्णांक32_t);
				num_reमुख्यing -= माप(uपूर्णांक32_t);
			पूर्ण अन्यथा अणु
				/* Buffer can only store partial word */
				uपूर्णांक32_t rnd_number = ioपढ़ो32(priv->base +
							RNG_FIFO_DATA_OFFSET);
				स_नकल(buf, &rnd_number, num_reमुख्यing);
				buf += num_reमुख्यing;
				num_reमुख्यing = 0;
			पूर्ण

			/* Reset the IDLE समयout */
			idle_endसमय = jअगरfies + MAX_IDLE_TIME;
		पूर्ण अन्यथा अणु
			अगर (!रुको)
				/* Cannot रुको, वापस immediately */
				वापस max - num_reमुख्यing;

			/* Can रुको, give others chance to run */
			usleep_range(min(num_reमुख्यing * 10, 500U), 500);
		पूर्ण
	पूर्ण

	वापस max - num_reमुख्यing;
पूर्ण

अटल पूर्णांक iproc_rng200_init(काष्ठा hwrng *rng)
अणु
	काष्ठा iproc_rng200_dev *priv = to_rng_priv(rng);

	iproc_rng200_enable_set(priv->base, true);

	वापस 0;
पूर्ण

अटल व्योम iproc_rng200_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा iproc_rng200_dev *priv = to_rng_priv(rng);

	iproc_rng200_enable_set(priv->base, false);
पूर्ण

अटल पूर्णांक iproc_rng200_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_rng200_dev *priv;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Map peripheral */
	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		dev_err(dev, "failed to remap rng regs\n");
		वापस PTR_ERR(priv->base);
	पूर्ण

	priv->rng.name = "iproc-rng200";
	priv->rng.पढ़ो = iproc_rng200_पढ़ो;
	priv->rng.init = iproc_rng200_init;
	priv->rng.cleanup = iproc_rng200_cleanup;

	/* Register driver */
	ret = devm_hwrng_रेजिस्टर(dev, &priv->rng);
	अगर (ret) अणु
		dev_err(dev, "hwrng registration failed\n");
		वापस ret;
	पूर्ण

	dev_info(dev, "hwrng registered\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id iproc_rng200_of_match[] = अणु
	अणु .compatible = "brcm,bcm2711-rng200", पूर्ण,
	अणु .compatible = "brcm,bcm7211-rng200", पूर्ण,
	अणु .compatible = "brcm,bcm7278-rng200", पूर्ण,
	अणु .compatible = "brcm,iproc-rng200", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, iproc_rng200_of_match);

अटल काष्ठा platक्रमm_driver iproc_rng200_driver = अणु
	.driver = अणु
		.name		= "iproc-rng200",
		.of_match_table = iproc_rng200_of_match,
	पूर्ण,
	.probe		= iproc_rng200_probe,
पूर्ण;
module_platक्रमm_driver(iproc_rng200_driver);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("iProc RNG200 Random Number Generator driver");
MODULE_LICENSE("GPL v2");
