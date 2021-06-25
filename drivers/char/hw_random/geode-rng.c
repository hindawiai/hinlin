<शैली गुरु>
/*
 * RNG driver क्रम AMD Geode RNGs
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
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>


#घोषणा PFX	KBUILD_MODNAME ": "

#घोषणा GEODE_RNG_DATA_REG   0x50
#घोषणा GEODE_RNG_STATUS_REG 0x54

/*
 * Data क्रम PCI driver पूर्णांकerface
 *
 * This data only exists क्रम exporting the supported
 * PCI ids via MODULE_DEVICE_TABLE.  We करो not actually
 * रेजिस्टर a pci_driver, because someone अन्यथा might one day
 * want to रेजिस्टर another driver on the same PCI id.
 */
अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_LX_AES), 0, पूर्ण,
	अणु 0, पूर्ण,	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_tbl);


अटल पूर्णांक geode_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	व्योम __iomem *mem = (व्योम __iomem *)rng->priv;

	*data = पढ़ोl(mem + GEODE_RNG_DATA_REG);

	वापस 4;
पूर्ण

अटल पूर्णांक geode_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	व्योम __iomem *mem = (व्योम __iomem *)rng->priv;
	पूर्णांक data, i;

	क्रम (i = 0; i < 20; i++) अणु
		data = !!(पढ़ोl(mem + GEODE_RNG_STATUS_REG));
		अगर (data || !रुको)
			अवरोध;
		udelay(10);
	पूर्ण
	वापस data;
पूर्ण


अटल काष्ठा hwrng geode_rng = अणु
	.name		= "geode",
	.data_present	= geode_rng_data_present,
	.data_पढ़ो	= geode_rng_data_पढ़ो,
पूर्ण;


अटल पूर्णांक __init mod_init(व्योम)
अणु
	पूर्णांक err = -ENODEV;
	काष्ठा pci_dev *pdev = शून्य;
	स्थिर काष्ठा pci_device_id *ent;
	व्योम __iomem *mem;
	अचिन्हित दीर्घ rng_base;

	क्रम_each_pci_dev(pdev) अणु
		ent = pci_match_id(pci_tbl, pdev);
		अगर (ent)
			जाओ found;
	पूर्ण
	/* Device not found. */
	जाओ out;

found:
	rng_base = pci_resource_start(pdev, 0);
	अगर (rng_base == 0)
		जाओ out;
	err = -ENOMEM;
	mem = ioremap(rng_base, 0x58);
	अगर (!mem)
		जाओ out;
	geode_rng.priv = (अचिन्हित दीर्घ)mem;

	pr_info("AMD Geode RNG detected\n");
	err = hwrng_रेजिस्टर(&geode_rng);
	अगर (err) अणु
		pr_err(PFX "RNG registering failed (%d)\n",
		       err);
		जाओ err_unmap;
	पूर्ण
out:
	वापस err;

err_unmap:
	iounmap(mem);
	जाओ out;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
	व्योम __iomem *mem = (व्योम __iomem *)geode_rng.priv;

	hwrng_unरेजिस्टर(&geode_rng);
	iounmap(mem);
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);

MODULE_DESCRIPTION("H/W RNG driver for AMD Geode LX CPUs");
MODULE_LICENSE("GPL");
