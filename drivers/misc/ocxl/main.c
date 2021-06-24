<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/mmu.h>
#समावेश "ocxl_internal.h"

अटल पूर्णांक __init init_ocxl(व्योम)
अणु
	पूर्णांक rc = 0;

	अगर (!tlbie_capable)
		वापस -EINVAL;

	rc = ocxl_file_init();
	अगर (rc)
		वापस rc;

	rc = pci_रेजिस्टर_driver(&ocxl_pci_driver);
	अगर (rc) अणु
		ocxl_file_निकास();
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम निकास_ocxl(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ocxl_pci_driver);
	ocxl_file_निकास();
पूर्ण

module_init(init_ocxl);
module_निकास(निकास_ocxl);

MODULE_DESCRIPTION("Open Coherent Accelerator");
MODULE_LICENSE("GPL");
