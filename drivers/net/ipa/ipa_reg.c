<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */

#समावेश <linux/पन.स>

#समावेश "ipa.h"
#समावेश "ipa_reg.h"

पूर्णांक ipa_reg_init(काष्ठा ipa *ipa)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	काष्ठा resource *res;

	/* Setup IPA रेजिस्टर memory  */
	res = platक्रमm_get_resource_byname(ipa->pdev, IORESOURCE_MEM,
					   "ipa-reg");
	अगर (!res) अणु
		dev_err(dev, "DT error getting \"ipa-reg\" memory property\n");
		वापस -ENODEV;
	पूर्ण

	ipa->reg_virt = ioremap(res->start, resource_size(res));
	अगर (!ipa->reg_virt) अणु
		dev_err(dev, "unable to remap \"ipa-reg\" memory\n");
		वापस -ENOMEM;
	पूर्ण
	ipa->reg_addr = res->start;

	वापस 0;
पूर्ण

व्योम ipa_reg_निकास(काष्ठा ipa *ipa)
अणु
	iounmap(ipa->reg_virt);
पूर्ण
