<शैली गुरु>
/*
 * Hardware Ranकरोm Number Generator support क्रम Cavium Inc.
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

#घोषणा THUNDERX_RNM_ENT_EN     0x1
#घोषणा THUNDERX_RNM_RNG_EN     0x2

काष्ठा cavium_rng_pf अणु
	व्योम __iomem *control_status;
पूर्ण;

/* Enable the RNG hardware and activate the VF */
अटल पूर्णांक cavium_rng_probe(काष्ठा pci_dev *pdev,
			स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा	cavium_rng_pf *rng;
	पूर्णांक	iov_err;

	rng = devm_kzalloc(&pdev->dev, माप(*rng), GFP_KERNEL);
	अगर (!rng)
		वापस -ENOMEM;

	/*Map the RNG control */
	rng->control_status = pcim_iomap(pdev, 0, 0);
	अगर (!rng->control_status) अणु
		dev_err(&pdev->dev,
			"Error iomap failed retrieving control_status.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Enable the RNG hardware and entropy source */
	ग_लिखोq(THUNDERX_RNM_RNG_EN | THUNDERX_RNM_ENT_EN,
		rng->control_status);

	pci_set_drvdata(pdev, rng);

	/* Enable the Cavium RNG as a VF */
	iov_err = pci_enable_sriov(pdev, 1);
	अगर (iov_err != 0) अणु
		/* Disable the RNG hardware and entropy source */
		ग_लिखोq(0, rng->control_status);
		dev_err(&pdev->dev,
			"Error initializing RNG virtual function,(%i).\n",
			iov_err);
		वापस iov_err;
	पूर्ण

	वापस 0;
पूर्ण

/* Disable VF and RNG Hardware */
अटल व्योम cavium_rng_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cavium_rng_pf *rng;

	rng = pci_get_drvdata(pdev);

	/* Remove the VF */
	pci_disable_sriov(pdev);

	/* Disable the RNG hardware and entropy source */
	ग_लिखोq(0, rng->control_status);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cavium_rng_pf_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, 0xa018), 0, 0, 0पूर्ण, /* Thunder RNM */
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, cavium_rng_pf_id_table);

अटल काष्ठा pci_driver cavium_rng_pf_driver = अणु
	.name		= "cavium_rng_pf",
	.id_table	= cavium_rng_pf_id_table,
	.probe		= cavium_rng_probe,
	.हटाओ		= cavium_rng_हटाओ,
पूर्ण;

module_pci_driver(cavium_rng_pf_driver);
MODULE_AUTHOR("Omer Khaliq <okhaliq@caviumnetworks.com>");
MODULE_LICENSE("GPL");
