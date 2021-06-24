<शैली गुरु>
/*
 * RNG driver क्रम TX4939 Ranकरोm Number Generators (RNG)
 *
 * Copyright (C) 2009 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/gfp.h>

#घोषणा TX4939_RNG_RCSR		0x00000000
#घोषणा TX4939_RNG_ROR(n)	(0x00000018 + (n) * 8)

#घोषणा TX4939_RNG_RCSR_INTE	0x00000008
#घोषणा TX4939_RNG_RCSR_RST	0x00000004
#घोषणा TX4939_RNG_RCSR_FIN	0x00000002
#घोषणा TX4939_RNG_RCSR_ST	0x00000001

काष्ठा tx4939_rng अणु
	काष्ठा hwrng rng;
	व्योम __iomem *base;
	u64 databuf[3];
	अचिन्हित पूर्णांक data_avail;
पूर्ण;

अटल व्योम rng_io_start(व्योम)
अणु
#अगर_अघोषित CONFIG_64BIT
	/*
	 * पढ़ोq is पढ़ोing a 64-bit रेजिस्टर using a 64-bit load.  On
	 * a 32-bit kernel however पूर्णांकerrupts or any other processor
	 * exception would clobber the upper 32-bit of the processor
	 * रेजिस्टर so पूर्णांकerrupts need to be disabled.
	 */
	local_irq_disable();
#पूर्ण_अगर
पूर्ण

अटल व्योम rng_io_end(व्योम)
अणु
#अगर_अघोषित CONFIG_64BIT
	local_irq_enable();
#पूर्ण_अगर
पूर्ण

अटल u64 पढ़ो_rng(व्योम __iomem *base, अचिन्हित पूर्णांक offset)
अणु
	वापस ____raw_पढ़ोq(base + offset);
पूर्ण

अटल व्योम ग_लिखो_rng(u64 val, व्योम __iomem *base, अचिन्हित पूर्णांक offset)
अणु
	वापस ____raw_ग_लिखोq(val, base + offset);
पूर्ण

अटल पूर्णांक tx4939_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	काष्ठा tx4939_rng *rngdev = container_of(rng, काष्ठा tx4939_rng, rng);
	पूर्णांक i;

	अगर (rngdev->data_avail)
		वापस rngdev->data_avail;
	क्रम (i = 0; i < 20; i++) अणु
		rng_io_start();
		अगर (!(पढ़ो_rng(rngdev->base, TX4939_RNG_RCSR)
		      & TX4939_RNG_RCSR_ST)) अणु
			rngdev->databuf[0] =
				पढ़ो_rng(rngdev->base, TX4939_RNG_ROR(0));
			rngdev->databuf[1] =
				पढ़ो_rng(rngdev->base, TX4939_RNG_ROR(1));
			rngdev->databuf[2] =
				पढ़ो_rng(rngdev->base, TX4939_RNG_ROR(2));
			rngdev->data_avail =
				माप(rngdev->databuf) / माप(u32);
			/* Start RNG */
			ग_लिखो_rng(TX4939_RNG_RCSR_ST,
				  rngdev->base, TX4939_RNG_RCSR);
			रुको = 0;
		पूर्ण
		rng_io_end();
		अगर (!रुको)
			अवरोध;
		/* 90 bus घड़ी cycles by शेष क्रम generation */
		ndelay(90 * 5);
	पूर्ण
	वापस rngdev->data_avail;
पूर्ण

अटल पूर्णांक tx4939_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *buffer)
अणु
	काष्ठा tx4939_rng *rngdev = container_of(rng, काष्ठा tx4939_rng, rng);

	rngdev->data_avail--;
	*buffer = *((u32 *)&rngdev->databuf + rngdev->data_avail);
	वापस माप(u32);
पूर्ण

अटल पूर्णांक __init tx4939_rng_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tx4939_rng *rngdev;
	पूर्णांक i;

	rngdev = devm_kzalloc(&dev->dev, माप(*rngdev), GFP_KERNEL);
	अगर (!rngdev)
		वापस -ENOMEM;
	rngdev->base = devm_platक्रमm_ioremap_resource(dev, 0);
	अगर (IS_ERR(rngdev->base))
		वापस PTR_ERR(rngdev->base);

	rngdev->rng.name = dev_name(&dev->dev);
	rngdev->rng.data_present = tx4939_rng_data_present;
	rngdev->rng.data_पढ़ो = tx4939_rng_data_पढ़ो;

	rng_io_start();
	/* Reset RNG */
	ग_लिखो_rng(TX4939_RNG_RCSR_RST, rngdev->base, TX4939_RNG_RCSR);
	ग_लिखो_rng(0, rngdev->base, TX4939_RNG_RCSR);
	/* Start RNG */
	ग_लिखो_rng(TX4939_RNG_RCSR_ST, rngdev->base, TX4939_RNG_RCSR);
	rng_io_end();
	/*
	 * Drop first two results.  From the datasheet:
	 * The quality of the अक्रमom numbers generated immediately
	 * after reset can be insufficient.  Thereक्रमe, करो not use
	 * अक्रमom numbers obtained from the first and second
	 * generations; use the ones from the third or subsequent
	 * generation.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		rngdev->data_avail = 0;
		अगर (!tx4939_rng_data_present(&rngdev->rng, 1))
			वापस -EIO;
	पूर्ण

	platक्रमm_set_drvdata(dev, rngdev);
	वापस devm_hwrng_रेजिस्टर(&dev->dev, &rngdev->rng);
पूर्ण

अटल काष्ठा platक्रमm_driver tx4939_rng_driver = अणु
	.driver		= अणु
		.name	= "tx4939-rng",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(tx4939_rng_driver, tx4939_rng_probe);

MODULE_DESCRIPTION("H/W Random Number Generator (RNG) driver for TX4939");
MODULE_LICENSE("GPL");
