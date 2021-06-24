<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2019 IBM Corp.
#समावेश <linux/module.h>
#समावेश "ocxl_internal.h"

/*
 * Any खोलोcapi device which wants to use this 'generic' driver should
 * use the 0x062B device ID. Venकरोrs should define the subप्रणाली
 * venकरोr/device ID to help dअगरferentiate devices.
 */
अटल स्थिर काष्ठा pci_device_id ocxl_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, 0x062B), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ocxl_pci_tbl);

अटल पूर्णांक ocxl_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rc;
	काष्ठा ocxl_afu *afu, *पंचांगp;
	काष्ठा ocxl_fn *fn;
	काष्ठा list_head *afu_list;

	fn = ocxl_function_खोलो(dev);
	अगर (IS_ERR(fn))
		वापस PTR_ERR(fn);

	pci_set_drvdata(dev, fn);

	afu_list = ocxl_function_afu_list(fn);

	list_क्रम_each_entry_safe(afu, पंचांगp, afu_list, list) अणु
		// Cleanup handled within ocxl_file_रेजिस्टर_afu()
		rc = ocxl_file_रेजिस्टर_afu(afu);
		अगर (rc) अणु
			dev_err(&dev->dev, "Failed to register AFU '%s' index %d",
					afu->config.name, afu->config.idx);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ocxl_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ocxl_fn *fn;
	काष्ठा ocxl_afu *afu;
	काष्ठा list_head *afu_list;

	fn = pci_get_drvdata(dev);
	afu_list = ocxl_function_afu_list(fn);

	list_क्रम_each_entry(afu, afu_list, list) अणु
		ocxl_file_unरेजिस्टर_afu(afu);
	पूर्ण

	ocxl_function_बंद(fn);
पूर्ण

काष्ठा pci_driver ocxl_pci_driver = अणु
	.name = "ocxl",
	.id_table = ocxl_pci_tbl,
	.probe = ocxl_probe,
	.हटाओ = ocxl_हटाओ,
	.shutकरोwn = ocxl_हटाओ,
पूर्ण;
