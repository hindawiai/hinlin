<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI driver क्रम the Intel SCU.
 *
 * Copyright (C) 2008-2010, 2015, 2020 Intel Corporation
 * Authors: Sreedhara DS (sreedhara.ds@पूर्णांकel.com)
 *	    Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/पूर्णांकel-mid.h>
#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

अटल पूर्णांक पूर्णांकel_scu_pci_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा पूर्णांकel_scu_ipc_data scu_data = अणुपूर्ण;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	scu_data.mem = pdev->resource[0];
	scu_data.irq = pdev->irq;

	scu = पूर्णांकel_scu_ipc_रेजिस्टर(&pdev->dev, &scu_data);
	वापस PTR_ERR_OR_ZERO(scu);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x080e) पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x08ea) पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0a94) पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x11a0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1a94) पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5a94) पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा pci_driver पूर्णांकel_scu_pci_driver = अणु
	.driver = अणु
		.suppress_bind_attrs = true,
	पूर्ण,
	.name = "intel_scu",
	.id_table = pci_ids,
	.probe = पूर्णांकel_scu_pci_probe,
पूर्ण;

builtin_pci_driver(पूर्णांकel_scu_pci_driver);
