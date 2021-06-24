<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, Christoph Hellwig.
 * Copyright (c) 2015, Intel Corporation.
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>

अटल पूर्णांक found(काष्ठा resource *res, व्योम *data)
अणु
	वापस 1;
पूर्ण

अटल __init पूर्णांक रेजिस्टर_e820_pmem(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक rc;

	rc = walk_iomem_res_desc(IORES_DESC_PERSISTENT_MEMORY_LEGACY,
				 IORESOURCE_MEM, 0, -1, शून्य, found);
	अगर (rc <= 0)
		वापस 0;

	/*
	 * See drivers/nvdimm/e820.c क्रम the implementation, this is
	 * simply here to trigger the module to load on demand.
	 */
	pdev = platक्रमm_device_alloc("e820_pmem", -1);
	वापस platक्रमm_device_add(pdev);
पूर्ण
device_initcall(रेजिस्टर_e820_pmem);
