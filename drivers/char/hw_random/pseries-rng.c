<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Michael Neuling IBM Corporation
 *
 * Driver क्रम the pseries hardware RNG क्रम POWER7+ and above
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <यंत्र/vपन.स>


अटल पूर्णांक pseries_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	u64 buffer[PLPAR_HCALL_बफ_मानE];
	पूर्णांक rc;

	rc = plpar_hcall(H_RANDOM, (अचिन्हित दीर्घ *)buffer);
	अगर (rc != H_SUCCESS) अणु
		pr_err_ratelimited("H_RANDOM call failed %d\n", rc);
		वापस -EIO;
	पूर्ण
	स_नकल(data, buffer, 8);

	/* The hypervisor पूर्णांकerface वापसs 64 bits */
	वापस 8;
पूर्ण

/**
 * pseries_rng_get_desired_dma - Return desired DMA allocate क्रम CMO operations
 *
 * This is a required function क्रम a driver to operate in a CMO environment
 * but this device करोes not make use of DMA allocations, वापस 0.
 *
 * Return value:
 *	Number of bytes of IO data the driver will need to perक्रमm well -> 0
 */
अटल अचिन्हित दीर्घ pseries_rng_get_desired_dma(काष्ठा vio_dev *vdev)
अणु
	वापस 0;
पूर्ण;

अटल काष्ठा hwrng pseries_rng = अणु
	.name		= KBUILD_MODNAME,
	.पढ़ो		= pseries_rng_पढ़ो,
पूर्ण;

अटल पूर्णांक pseries_rng_probe(काष्ठा vio_dev *dev,
		स्थिर काष्ठा vio_device_id *id)
अणु
	वापस hwrng_रेजिस्टर(&pseries_rng);
पूर्ण

अटल व्योम pseries_rng_हटाओ(काष्ठा vio_dev *dev)
अणु
	hwrng_unरेजिस्टर(&pseries_rng);
पूर्ण

अटल स्थिर काष्ठा vio_device_id pseries_rng_driver_ids[] = अणु
	अणु "ibm,random-v1", "ibm,random"पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, pseries_rng_driver_ids);

अटल काष्ठा vio_driver pseries_rng_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = pseries_rng_probe,
	.हटाओ = pseries_rng_हटाओ,
	.get_desired_dma = pseries_rng_get_desired_dma,
	.id_table = pseries_rng_driver_ids
पूर्ण;

अटल पूर्णांक __init rng_init(व्योम)
अणु
	pr_info("Registering IBM pSeries RNG driver\n");
	वापस vio_रेजिस्टर_driver(&pseries_rng_driver);
पूर्ण

module_init(rng_init);

अटल व्योम __निकास rng_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&pseries_rng_driver);
पूर्ण
module_निकास(rng_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Neuling <mikey@neuling.org>");
MODULE_DESCRIPTION("H/W RNG driver for IBM pSeries processors");
