<शैली गुरु>
/*
 * Hardware Ranकरोm Number Generator support क्रम Cavium, Inc.
 * Thunder processor family.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2016 Cavium, Inc.
 */

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>

काष्ठा cavium_rng अणु
	काष्ठा hwrng ops;
	व्योम __iomem *result;
पूर्ण;

/* Read data from the RNG unit */
अटल पूर्णांक cavium_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *dat, माप_प्रकार max, bool रुको)
अणु
	काष्ठा cavium_rng *p = container_of(rng, काष्ठा cavium_rng, ops);
	अचिन्हित पूर्णांक size = max;

	जबतक (size >= 8) अणु
		*((u64 *)dat) = पढ़ोq(p->result);
		size -= 8;
		dat += 8;
	पूर्ण
	जबतक (size > 0) अणु
		*((u8 *)dat) = पढ़ोb(p->result);
		size--;
		dat++;
	पूर्ण
	वापस max;
पूर्ण

/* Map Cavium RNG to an HWRNG object */
अटल पूर्णांक cavium_rng_probe_vf(काष्ठा	pci_dev		*pdev,
			 स्थिर काष्ठा	pci_device_id	*id)
अणु
	काष्ठा	cavium_rng *rng;
	पूर्णांक	ret;

	rng = devm_kzalloc(&pdev->dev, माप(*rng), GFP_KERNEL);
	अगर (!rng)
		वापस -ENOMEM;

	/* Map the RNG result */
	rng->result = pcim_iomap(pdev, 0, 0);
	अगर (!rng->result) अणु
		dev_err(&pdev->dev, "Error iomap failed retrieving result.\n");
		वापस -ENOMEM;
	पूर्ण

	rng->ops.name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
				       "cavium-rng-%s", dev_name(&pdev->dev));
	अगर (!rng->ops.name)
		वापस -ENOMEM;

	rng->ops.पढ़ो    = cavium_rng_पढ़ो;
	rng->ops.quality = 1000;

	pci_set_drvdata(pdev, rng);

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &rng->ops);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error registering device as HWRNG.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा pci_device_id cavium_rng_vf_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, 0xa033), 0, 0, 0पूर्ण,
	अणु0,पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, cavium_rng_vf_id_table);

अटल काष्ठा pci_driver cavium_rng_vf_driver = अणु
	.name		= "cavium_rng_vf",
	.id_table	= cavium_rng_vf_id_table,
	.probe		= cavium_rng_probe_vf,
पूर्ण;
module_pci_driver(cavium_rng_vf_driver);

MODULE_AUTHOR("Omer Khaliq <okhaliq@caviumnetworks.com>");
MODULE_LICENSE("GPL");
