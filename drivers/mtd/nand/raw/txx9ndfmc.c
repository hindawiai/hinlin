<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TXx9 न_अंकD flash memory controller driver
 * Based on RBTX49xx patch from CELF patch archive.
 *
 * (C) Copyright TOSHIBA CORPORATION 2004-2007
 * All Rights Reserved.
 */
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/txx9/ndfmc.h>

/* TXX9 NDFMC Registers */
#घोषणा TXX9_NDFDTR	0x00
#घोषणा TXX9_NDFMCR	0x04
#घोषणा TXX9_NDFSR	0x08
#घोषणा TXX9_NDFISR	0x0c
#घोषणा TXX9_NDFIMR	0x10
#घोषणा TXX9_NDFSPR	0x14
#घोषणा TXX9_NDFRSTR	0x18	/* not TX4939 */

/* NDFMCR : NDFMC Mode Control */
#घोषणा TXX9_NDFMCR_WE	0x80
#घोषणा TXX9_NDFMCR_ECC_ALL	0x60
#घोषणा TXX9_NDFMCR_ECC_RESET	0x60
#घोषणा TXX9_NDFMCR_ECC_READ	0x40
#घोषणा TXX9_NDFMCR_ECC_ON	0x20
#घोषणा TXX9_NDFMCR_ECC_OFF	0x00
#घोषणा TXX9_NDFMCR_CE	0x10
#घोषणा TXX9_NDFMCR_BSPRT	0x04	/* TX4925/TX4926 only */
#घोषणा TXX9_NDFMCR_ALE	0x02
#घोषणा TXX9_NDFMCR_CLE	0x01
/* TX4939 only */
#घोषणा TXX9_NDFMCR_X16	0x0400
#घोषणा TXX9_NDFMCR_DMAREQ_MASK	0x0300
#घोषणा TXX9_NDFMCR_DMAREQ_NODMA	0x0000
#घोषणा TXX9_NDFMCR_DMAREQ_128	0x0100
#घोषणा TXX9_NDFMCR_DMAREQ_256	0x0200
#घोषणा TXX9_NDFMCR_DMAREQ_512	0x0300
#घोषणा TXX9_NDFMCR_CS_MASK	0x0c
#घोषणा TXX9_NDFMCR_CS(ch)	((ch) << 2)

/* NDFMCR : NDFMC Status */
#घोषणा TXX9_NDFSR_BUSY	0x80
/* TX4939 only */
#घोषणा TXX9_NDFSR_DMARUN	0x40

/* NDFMCR : NDFMC Reset */
#घोषणा TXX9_NDFRSTR_RST	0x01

काष्ठा txx9ndfmc_priv अणु
	काष्ठा platक्रमm_device *dev;
	काष्ठा nand_chip chip;
	पूर्णांक cs;
	स्थिर अक्षर *mtdname;
पूर्ण;

#घोषणा MAX_TXX9NDFMC_DEV	4
काष्ठा txx9ndfmc_drvdata अणु
	काष्ठा mtd_info *mtds[MAX_TXX9NDFMC_DEV];
	व्योम __iomem *base;
	अचिन्हित अक्षर hold;	/* in gbusघड़ी */
	अचिन्हित अक्षर spw;	/* in gbusघड़ी */
	काष्ठा nand_controller controller;
पूर्ण;

अटल काष्ठा platक्रमm_device *mtd_to_platdev(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा txx9ndfmc_priv *txx9_priv = nand_get_controller_data(chip);
	वापस txx9_priv->dev;
पूर्ण

अटल व्योम __iomem *ndregaddr(काष्ठा platक्रमm_device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा txx9ndfmc_drvdata *drvdata = platक्रमm_get_drvdata(dev);
	काष्ठा txx9ndfmc_platक्रमm_data *plat = dev_get_platdata(&dev->dev);

	वापस drvdata->base + (reg << plat->shअगरt);
पूर्ण

अटल u32 txx9ndfmc_पढ़ो(काष्ठा platक्रमm_device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(ndregaddr(dev, reg));
पूर्ण

अटल व्योम txx9ndfmc_ग_लिखो(काष्ठा platक्रमm_device *dev,
			    u32 val, अचिन्हित पूर्णांक reg)
अणु
	__raw_ग_लिखोl(val, ndregaddr(dev, reg));
पूर्ण

अटल uपूर्णांक8_t txx9ndfmc_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा platक्रमm_device *dev = mtd_to_platdev(nand_to_mtd(chip));

	वापस txx9ndfmc_पढ़ो(dev, TXX9_NDFDTR);
पूर्ण

अटल व्योम txx9ndfmc_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				पूर्णांक len)
अणु
	काष्ठा platक्रमm_device *dev = mtd_to_platdev(nand_to_mtd(chip));
	व्योम __iomem *ndfdtr = ndregaddr(dev, TXX9_NDFDTR);
	u32 mcr = txx9ndfmc_पढ़ो(dev, TXX9_NDFMCR);

	txx9ndfmc_ग_लिखो(dev, mcr | TXX9_NDFMCR_WE, TXX9_NDFMCR);
	जबतक (len--)
		__raw_ग_लिखोl(*buf++, ndfdtr);
	txx9ndfmc_ग_लिखो(dev, mcr, TXX9_NDFMCR);
पूर्ण

अटल व्योम txx9ndfmc_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा platक्रमm_device *dev = mtd_to_platdev(nand_to_mtd(chip));
	व्योम __iomem *ndfdtr = ndregaddr(dev, TXX9_NDFDTR);

	जबतक (len--)
		*buf++ = __raw_पढ़ोl(ndfdtr);
पूर्ण

अटल व्योम txx9ndfmc_cmd_ctrl(काष्ठा nand_chip *chip, पूर्णांक cmd,
			       अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा txx9ndfmc_priv *txx9_priv = nand_get_controller_data(chip);
	काष्ठा platक्रमm_device *dev = txx9_priv->dev;
	काष्ठा txx9ndfmc_platक्रमm_data *plat = dev_get_platdata(&dev->dev);

	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		u32 mcr = txx9ndfmc_पढ़ो(dev, TXX9_NDFMCR);

		mcr &= ~(TXX9_NDFMCR_CLE | TXX9_NDFMCR_ALE | TXX9_NDFMCR_CE);
		mcr |= ctrl & न_अंकD_CLE ? TXX9_NDFMCR_CLE : 0;
		mcr |= ctrl & न_अंकD_ALE ? TXX9_NDFMCR_ALE : 0;
		/* TXX9_NDFMCR_CE bit is 0:high 1:low */
		mcr |= ctrl & न_अंकD_NCE ? TXX9_NDFMCR_CE : 0;
		अगर (txx9_priv->cs >= 0 && (ctrl & न_अंकD_NCE)) अणु
			mcr &= ~TXX9_NDFMCR_CS_MASK;
			mcr |= TXX9_NDFMCR_CS(txx9_priv->cs);
		पूर्ण
		txx9ndfmc_ग_लिखो(dev, mcr, TXX9_NDFMCR);
	पूर्ण
	अगर (cmd != न_अंकD_CMD_NONE)
		txx9ndfmc_ग_लिखो(dev, cmd & 0xff, TXX9_NDFDTR);
	अगर (plat->flags & NDFMC_PLAT_FLAG_DUMMYWRITE) अणु
		/* dummy ग_लिखो to update बाह्यal latch */
		अगर ((ctrl & न_अंकD_CTRL_CHANGE) && cmd == न_अंकD_CMD_NONE)
			txx9ndfmc_ग_लिखो(dev, 0, TXX9_NDFDTR);
	पूर्ण
पूर्ण

अटल पूर्णांक txx9ndfmc_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा platक्रमm_device *dev = mtd_to_platdev(nand_to_mtd(chip));

	वापस !(txx9ndfmc_पढ़ो(dev, TXX9_NDFSR) & TXX9_NDFSR_BUSY);
पूर्ण

अटल पूर्णांक txx9ndfmc_calculate_ecc(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *dat,
				   uपूर्णांक8_t *ecc_code)
अणु
	काष्ठा platक्रमm_device *dev = mtd_to_platdev(nand_to_mtd(chip));
	पूर्णांक eccbytes;
	u32 mcr = txx9ndfmc_पढ़ो(dev, TXX9_NDFMCR);

	mcr &= ~TXX9_NDFMCR_ECC_ALL;
	txx9ndfmc_ग_लिखो(dev, mcr | TXX9_NDFMCR_ECC_OFF, TXX9_NDFMCR);
	txx9ndfmc_ग_लिखो(dev, mcr | TXX9_NDFMCR_ECC_READ, TXX9_NDFMCR);
	क्रम (eccbytes = chip->ecc.bytes; eccbytes > 0; eccbytes -= 3) अणु
		ecc_code[1] = txx9ndfmc_पढ़ो(dev, TXX9_NDFDTR);
		ecc_code[0] = txx9ndfmc_पढ़ो(dev, TXX9_NDFDTR);
		ecc_code[2] = txx9ndfmc_पढ़ो(dev, TXX9_NDFDTR);
		ecc_code += 3;
	पूर्ण
	txx9ndfmc_ग_लिखो(dev, mcr | TXX9_NDFMCR_ECC_OFF, TXX9_NDFMCR);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9ndfmc_correct_data(काष्ठा nand_chip *chip, अचिन्हित अक्षर *buf,
				  अचिन्हित अक्षर *पढ़ो_ecc,
				  अचिन्हित अक्षर *calc_ecc)
अणु
	पूर्णांक eccsize;
	पूर्णांक corrected = 0;
	पूर्णांक stat;

	क्रम (eccsize = chip->ecc.size; eccsize > 0; eccsize -= 256) अणु
		stat = ecc_sw_hamming_correct(buf, पढ़ो_ecc, calc_ecc,
					      chip->ecc.size, false);
		अगर (stat < 0)
			वापस stat;
		corrected += stat;
		buf += 256;
		पढ़ो_ecc += 3;
		calc_ecc += 3;
	पूर्ण
	वापस corrected;
पूर्ण

अटल व्योम txx9ndfmc_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा platक्रमm_device *dev = mtd_to_platdev(nand_to_mtd(chip));
	u32 mcr = txx9ndfmc_पढ़ो(dev, TXX9_NDFMCR);

	mcr &= ~TXX9_NDFMCR_ECC_ALL;
	txx9ndfmc_ग_लिखो(dev, mcr | TXX9_NDFMCR_ECC_RESET, TXX9_NDFMCR);
	txx9ndfmc_ग_लिखो(dev, mcr | TXX9_NDFMCR_ECC_OFF, TXX9_NDFMCR);
	txx9ndfmc_ग_लिखो(dev, mcr | TXX9_NDFMCR_ECC_ON, TXX9_NDFMCR);
पूर्ण

अटल व्योम txx9ndfmc_initialize(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा txx9ndfmc_platक्रमm_data *plat = dev_get_platdata(&dev->dev);
	काष्ठा txx9ndfmc_drvdata *drvdata = platक्रमm_get_drvdata(dev);
	पूर्णांक पंचांगout = 100;

	अगर (plat->flags & NDFMC_PLAT_FLAG_NO_RSTR)
		; /* no NDFRSTR.  Write to NDFSPR resets the NDFMC. */
	अन्यथा अणु
		/* reset NDFMC */
		txx9ndfmc_ग_लिखो(dev,
				txx9ndfmc_पढ़ो(dev, TXX9_NDFRSTR) |
				TXX9_NDFRSTR_RST,
				TXX9_NDFRSTR);
		जबतक (txx9ndfmc_पढ़ो(dev, TXX9_NDFRSTR) & TXX9_NDFRSTR_RST) अणु
			अगर (--पंचांगout == 0) अणु
				dev_err(&dev->dev, "reset failed.\n");
				अवरोध;
			पूर्ण
			udelay(1);
		पूर्ण
	पूर्ण
	/* setup Hold Time, Strobe Pulse Width */
	txx9ndfmc_ग_लिखो(dev, (drvdata->hold << 4) | drvdata->spw, TXX9_NDFSPR);
	txx9ndfmc_ग_लिखो(dev,
			(plat->flags & NDFMC_PLAT_FLAG_USE_BSPRT) ?
			TXX9_NDFMCR_BSPRT : 0, TXX9_NDFMCR);
पूर्ण

#घोषणा TXX9NDFMC_NS_TO_CYC(gbusclk, ns) \
	DIV_ROUND_UP((ns) * DIV_ROUND_UP(gbusclk, 1000), 1000000)

अटल पूर्णांक txx9ndfmc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	chip->ecc.strength = 1;

	अगर (mtd->ग_लिखोsize >= 512) अणु
		chip->ecc.size = 512;
		chip->ecc.bytes = 6;
	पूर्ण अन्यथा अणु
		chip->ecc.size = 256;
		chip->ecc.bytes = 3;
	पूर्ण

	chip->ecc.calculate = txx9ndfmc_calculate_ecc;
	chip->ecc.correct = txx9ndfmc_correct_data;
	chip->ecc.hwctl = txx9ndfmc_enable_hwecc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops txx9ndfmc_controller_ops = अणु
	.attach_chip = txx9ndfmc_attach_chip,
पूर्ण;

अटल पूर्णांक __init txx9ndfmc_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा txx9ndfmc_platक्रमm_data *plat = dev_get_platdata(&dev->dev);
	पूर्णांक hold, spw;
	पूर्णांक i;
	काष्ठा txx9ndfmc_drvdata *drvdata;
	अचिन्हित दीर्घ gbusclk = plat->gbus_घड़ी;
	काष्ठा resource *res;

	drvdata = devm_kzalloc(&dev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;
	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	drvdata->base = devm_ioremap_resource(&dev->dev, res);
	अगर (IS_ERR(drvdata->base))
		वापस PTR_ERR(drvdata->base);

	hold = plat->hold ?: 20; /* tDH */
	spw = plat->spw ?: 90; /* max(tREADID, tWP, tRP) */

	hold = TXX9NDFMC_NS_TO_CYC(gbusclk, hold);
	spw = TXX9NDFMC_NS_TO_CYC(gbusclk, spw);
	अगर (plat->flags & NDFMC_PLAT_FLAG_HOLDADD)
		hold -= 2;	/* actual hold समय : (HOLD + 2) BUSCLK */
	spw -= 1;	/* actual रुको समय : (SPW + 1) BUSCLK */
	hold = clamp(hold, 1, 15);
	drvdata->hold = hold;
	spw = clamp(spw, 1, 15);
	drvdata->spw = spw;
	dev_info(&dev->dev, "CLK:%ldMHz HOLD:%d SPW:%d\n",
		 (gbusclk + 500000) / 1000000, hold, spw);

	nand_controller_init(&drvdata->controller);
	drvdata->controller.ops = &txx9ndfmc_controller_ops;

	platक्रमm_set_drvdata(dev, drvdata);
	txx9ndfmc_initialize(dev);

	क्रम (i = 0; i < MAX_TXX9NDFMC_DEV; i++) अणु
		काष्ठा txx9ndfmc_priv *txx9_priv;
		काष्ठा nand_chip *chip;
		काष्ठा mtd_info *mtd;

		अगर (!(plat->ch_mask & (1 << i)))
			जारी;
		txx9_priv = kzalloc(माप(काष्ठा txx9ndfmc_priv),
				    GFP_KERNEL);
		अगर (!txx9_priv)
			जारी;
		chip = &txx9_priv->chip;
		mtd = nand_to_mtd(chip);
		mtd->dev.parent = &dev->dev;

		chip->legacy.पढ़ो_byte = txx9ndfmc_पढ़ो_byte;
		chip->legacy.पढ़ो_buf = txx9ndfmc_पढ़ो_buf;
		chip->legacy.ग_लिखो_buf = txx9ndfmc_ग_लिखो_buf;
		chip->legacy.cmd_ctrl = txx9ndfmc_cmd_ctrl;
		chip->legacy.dev_पढ़ोy = txx9ndfmc_dev_पढ़ोy;
		chip->legacy.chip_delay = 100;
		chip->controller = &drvdata->controller;

		nand_set_controller_data(chip, txx9_priv);
		txx9_priv->dev = dev;

		अगर (plat->ch_mask != 1) अणु
			txx9_priv->cs = i;
			txx9_priv->mtdname = kaप्र_लिखो(GFP_KERNEL, "%s.%u",
						       dev_name(&dev->dev), i);
		पूर्ण अन्यथा अणु
			txx9_priv->cs = -1;
			txx9_priv->mtdname = kstrdup(dev_name(&dev->dev),
						     GFP_KERNEL);
		पूर्ण
		अगर (!txx9_priv->mtdname) अणु
			kमुक्त(txx9_priv);
			dev_err(&dev->dev, "Unable to allocate MTD name.\n");
			जारी;
		पूर्ण
		अगर (plat->wide_mask & (1 << i))
			chip->options |= न_अंकD_BUSWIDTH_16;

		अगर (nand_scan(chip, 1)) अणु
			kमुक्त(txx9_priv->mtdname);
			kमुक्त(txx9_priv);
			जारी;
		पूर्ण
		mtd->name = txx9_priv->mtdname;

		mtd_device_रेजिस्टर(mtd, शून्य, 0);
		drvdata->mtds[i] = mtd;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास txx9ndfmc_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा txx9ndfmc_drvdata *drvdata = platक्रमm_get_drvdata(dev);
	पूर्णांक ret, i;

	अगर (!drvdata)
		वापस 0;
	क्रम (i = 0; i < MAX_TXX9NDFMC_DEV; i++) अणु
		काष्ठा mtd_info *mtd = drvdata->mtds[i];
		काष्ठा nand_chip *chip;
		काष्ठा txx9ndfmc_priv *txx9_priv;

		अगर (!mtd)
			जारी;
		chip = mtd_to_nand(mtd);
		txx9_priv = nand_get_controller_data(chip);

		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		kमुक्त(txx9_priv->mtdname);
		kमुक्त(txx9_priv);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक txx9ndfmc_resume(काष्ठा platक्रमm_device *dev)
अणु
	अगर (platक्रमm_get_drvdata(dev))
		txx9ndfmc_initialize(dev);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा txx9ndfmc_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver txx9ndfmc_driver = अणु
	.हटाओ		= __निकास_p(txx9ndfmc_हटाओ),
	.resume		= txx9ndfmc_resume,
	.driver		= अणु
		.name	= "txx9ndfmc",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(txx9ndfmc_driver, txx9ndfmc_probe);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TXx9 SoC NAND flash controller driver");
MODULE_ALIAS("platform:txx9ndfmc");
