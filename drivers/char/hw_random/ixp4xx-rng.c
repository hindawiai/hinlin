<शैली गुरु>
/*
 * drivers/अक्षर/hw_अक्रमom/ixp4xx-rng.c
 *
 * RNG driver क्रम Intel IXP4xx family of NPUs
 *
 * Author: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 * Copyright 2005 (c) MontaVista Software, Inc.
 *
 * Fixes by Michael Buesch
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/hw_अक्रमom.h>

#समावेश <यंत्र/पन.स>
#समावेश <mach/hardware.h>


अटल पूर्णांक ixp4xx_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *buffer)
अणु
	व्योम __iomem * rng_base = (व्योम __iomem *)rng->priv;

	*buffer = __raw_पढ़ोl(rng_base);

	वापस 4;
पूर्ण

अटल काष्ठा hwrng ixp4xx_rng_ops = अणु
	.name		= "ixp4xx",
	.data_पढ़ो	= ixp4xx_rng_data_पढ़ो,
पूर्ण;

अटल पूर्णांक __init ixp4xx_rng_init(व्योम)
अणु
	व्योम __iomem * rng_base;
	पूर्णांक err;

	अगर (!cpu_is_ixp46x()) /* includes IXP455 */
		वापस -ENOSYS;

	rng_base = ioremap(0x70002100, 4);
	अगर (!rng_base)
		वापस -ENOMEM;
	ixp4xx_rng_ops.priv = (अचिन्हित दीर्घ)rng_base;
	err = hwrng_रेजिस्टर(&ixp4xx_rng_ops);
	अगर (err)
		iounmap(rng_base);

	वापस err;
पूर्ण

अटल व्योम __निकास ixp4xx_rng_निकास(व्योम)
अणु
	व्योम __iomem * rng_base = (व्योम __iomem *)ixp4xx_rng_ops.priv;

	hwrng_unरेजिस्टर(&ixp4xx_rng_ops);
	iounmap(rng_base);
पूर्ण

module_init(ixp4xx_rng_init);
module_निकास(ixp4xx_rng_निकास);

MODULE_AUTHOR("Deepak Saxena <dsaxena@plexity.net>");
MODULE_DESCRIPTION("H/W Pseudo-Random Number Generator (RNG) driver for IXP45x/46x");
MODULE_LICENSE("GPL");
