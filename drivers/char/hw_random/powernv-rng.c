<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Michael Ellerman, Guo Chao, IBM Corp.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/hw_अक्रमom.h>

अटल पूर्णांक घातernv_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	अचिन्हित दीर्घ *buf;
	पूर्णांक i, len;

	/* We rely on rng_buffer_size() being >= माप(अचिन्हित दीर्घ) */
	len = max / माप(अचिन्हित दीर्घ);

	buf = (अचिन्हित दीर्घ *)data;

	क्रम (i = 0; i < len; i++)
		घातernv_get_अक्रमom_दीर्घ(buf++);

	वापस len * माप(अचिन्हित दीर्घ);
पूर्ण

अटल काष्ठा hwrng घातernv_hwrng = अणु
	.name = "powernv-rng",
	.पढ़ो = घातernv_rng_पढ़ो,
पूर्ण;

अटल पूर्णांक घातernv_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;

	rc = devm_hwrng_रेजिस्टर(&pdev->dev, &घातernv_hwrng);
	अगर (rc) अणु
		/* We only रेजिस्टर one device, ignore any others */
		अगर (rc == -EEXIST)
			rc = -ENODEV;

		वापस rc;
	पूर्ण

	pr_info("Registered powernv hwrng.\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id घातernv_rng_match[] = अणु
	अणु .compatible	= "ibm,power-rng",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, घातernv_rng_match);

अटल काष्ठा platक्रमm_driver घातernv_rng_driver = अणु
	.driver = अणु
		.name = "powernv_rng",
		.of_match_table = घातernv_rng_match,
	पूर्ण,
	.probe	= घातernv_rng_probe,
पूर्ण;
module_platक्रमm_driver(घातernv_rng_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Bare metal HWRNG driver for POWER7+ and above");
