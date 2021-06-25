<शैली गुरु>
/*
 * RNG driver क्रम AMD RNGs
 *
 * Copyright 2005 (c) MontaVista Software, Inc.
 *
 * with the majority of the code coming from:
 *
 * Hardware driver क्रम the Intel/AMD/VIA Ranकरोm Number Generators (RNG)
 * (c) Copyright 2003 Red Hat Inc <jgarzik@redhat.com>
 *
 * derived from
 *
 * Hardware driver क्रम the AMD 768 Ranकरोm Number Generator (RNG)
 * (c) Copyright 2001 Red Hat Inc
 *
 * derived from
 *
 * Hardware driver क्रम Intel i810 Ranकरोm Number Generator (RNG)
 * Copyright 2000,2001 Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2000,2001 Philipp Rumpf <prumpf@mandrakesoft.com>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/delay.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#घोषणा DRV_NAME "AMD768-HWRNG"

#घोषणा RNGDATA		0x00
#घोषणा RNGDONE		0x04
#घोषणा PMBASE_OFFSET	0xF0
#घोषणा PMBASE_SIZE	8

/*
 * Data क्रम PCI driver पूर्णांकerface
 *
 * This data only exists क्रम exporting the supported
 * PCI ids via MODULE_DEVICE_TABLE.  We करो not actually
 * रेजिस्टर a pci_driver, because someone अन्यथा might one day
 * want to रेजिस्टर another driver on the same PCI id.
 */
अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	अणु PCI_VDEVICE(AMD, 0x7443), 0, पूर्ण,
	अणु PCI_VDEVICE(AMD, 0x746b), 0, पूर्ण,
	अणु 0, पूर्ण,	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_tbl);

काष्ठा amd768_priv अणु
	व्योम __iomem *iobase;
	काष्ठा pci_dev *pcidev;
	u32 pmbase;
पूर्ण;

अटल पूर्णांक amd_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	u32 *data = buf;
	काष्ठा amd768_priv *priv = (काष्ठा amd768_priv *)rng->priv;
	माप_प्रकार पढ़ो = 0;
	/* We will रुको at maximum one समय per पढ़ो */
	पूर्णांक समयout = max / 4 + 1;

	/*
	 * RNG data is available when RNGDONE is set to 1
	 * New अक्रमom numbers are generated approximately 128 microseconds
	 * after RNGDATA is पढ़ो
	 */
	जबतक (पढ़ो < max) अणु
		अगर (ioपढ़ो32(priv->iobase + RNGDONE) == 0) अणु
			अगर (रुको) अणु
				/* Delay given by datasheet */
				usleep_range(128, 196);
				अगर (समयout-- == 0)
					वापस पढ़ो;
			पूर्ण अन्यथा अणु
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			*data = ioपढ़ो32(priv->iobase + RNGDATA);
			data++;
			पढ़ो += 4;
		पूर्ण
	पूर्ण

	वापस पढ़ो;
पूर्ण

अटल पूर्णांक amd_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा amd768_priv *priv = (काष्ठा amd768_priv *)rng->priv;
	u8 rnen;

	pci_पढ़ो_config_byte(priv->pcidev, 0x40, &rnen);
	rnen |= BIT(7);	/* RNG on */
	pci_ग_लिखो_config_byte(priv->pcidev, 0x40, rnen);

	pci_पढ़ो_config_byte(priv->pcidev, 0x41, &rnen);
	rnen |= BIT(7);	/* PMIO enable */
	pci_ग_लिखो_config_byte(priv->pcidev, 0x41, rnen);

	वापस 0;
पूर्ण

अटल व्योम amd_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा amd768_priv *priv = (काष्ठा amd768_priv *)rng->priv;
	u8 rnen;

	pci_पढ़ो_config_byte(priv->pcidev, 0x40, &rnen);
	rnen &= ~BIT(7);	/* RNG off */
	pci_ग_लिखो_config_byte(priv->pcidev, 0x40, rnen);
पूर्ण

अटल काष्ठा hwrng amd_rng = अणु
	.name		= "amd",
	.init		= amd_rng_init,
	.cleanup	= amd_rng_cleanup,
	.पढ़ो		= amd_rng_पढ़ो,
पूर्ण;

अटल पूर्णांक __init mod_init(व्योम)
अणु
	पूर्णांक err = -ENODEV;
	काष्ठा pci_dev *pdev = शून्य;
	स्थिर काष्ठा pci_device_id *ent;
	u32 pmbase;
	काष्ठा amd768_priv *priv;

	क्रम_each_pci_dev(pdev) अणु
		ent = pci_match_id(pci_tbl, pdev);
		अगर (ent)
			जाओ found;
	पूर्ण
	/* Device not found. */
	वापस -ENODEV;

found:
	err = pci_पढ़ो_config_dword(pdev, 0x58, &pmbase);
	अगर (err)
		वापस err;

	pmbase &= 0x0000FF00;
	अगर (pmbase == 0)
		वापस -EIO;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (!request_region(pmbase + PMBASE_OFFSET, PMBASE_SIZE, DRV_NAME)) अणु
		dev_err(&pdev->dev, DRV_NAME " region 0x%x already in use!\n",
			pmbase + 0xF0);
		err = -EBUSY;
		जाओ out;
	पूर्ण

	priv->iobase = ioport_map(pmbase + PMBASE_OFFSET, PMBASE_SIZE);
	अगर (!priv->iobase) अणु
		pr_err(DRV_NAME "Cannot map ioport\n");
		err = -EINVAL;
		जाओ err_iomap;
	पूर्ण

	amd_rng.priv = (अचिन्हित दीर्घ)priv;
	priv->pmbase = pmbase;
	priv->pcidev = pdev;

	pr_info(DRV_NAME " detected\n");
	err = hwrng_रेजिस्टर(&amd_rng);
	अगर (err) अणु
		pr_err(DRV_NAME " registering failed (%d)\n", err);
		जाओ err_hwrng;
	पूर्ण
	वापस 0;

err_hwrng:
	ioport_unmap(priv->iobase);
err_iomap:
	release_region(pmbase + PMBASE_OFFSET, PMBASE_SIZE);
out:
	kमुक्त(priv);
	वापस err;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
	काष्ठा amd768_priv *priv;

	priv = (काष्ठा amd768_priv *)amd_rng.priv;

	hwrng_unरेजिस्टर(&amd_rng);

	ioport_unmap(priv->iobase);

	release_region(priv->pmbase + PMBASE_OFFSET, PMBASE_SIZE);

	kमुक्त(priv);
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);

MODULE_AUTHOR("The Linux Kernel team");
MODULE_DESCRIPTION("H/W RNG driver for AMD chipsets");
MODULE_LICENSE("GPL");
