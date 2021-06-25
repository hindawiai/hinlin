<शैली गुरु>
/*
 * Hardware Ranकरोm Number Generator support क्रम Cavium Networks
 * Octeon processor family.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2009 Cavium Networks
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-rnm-defs.h>

काष्ठा octeon_rng अणु
	काष्ठा hwrng ops;
	व्योम __iomem *control_status;
	व्योम __iomem *result;
पूर्ण;

अटल पूर्णांक octeon_rng_init(काष्ठा hwrng *rng)
अणु
	जोड़ cvmx_rnm_ctl_status ctl;
	काष्ठा octeon_rng *p = container_of(rng, काष्ठा octeon_rng, ops);

	ctl.u64 = 0;
	ctl.s.ent_en = 1; /* Enable the entropy source.  */
	ctl.s.rng_en = 1; /* Enable the RNG hardware.  */
	cvmx_ग_लिखो_csr((__क्रमce u64)p->control_status, ctl.u64);
	वापस 0;
पूर्ण

अटल व्योम octeon_rng_cleanup(काष्ठा hwrng *rng)
अणु
	जोड़ cvmx_rnm_ctl_status ctl;
	काष्ठा octeon_rng *p = container_of(rng, काष्ठा octeon_rng, ops);

	ctl.u64 = 0;
	/* Disable everything.  */
	cvmx_ग_लिखो_csr((__क्रमce u64)p->control_status, ctl.u64);
पूर्ण

अटल पूर्णांक octeon_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा octeon_rng *p = container_of(rng, काष्ठा octeon_rng, ops);

	*data = cvmx_पढ़ो64_uपूर्णांक32((__क्रमce u64)p->result);
	वापस माप(u32);
पूर्ण

अटल पूर्णांक octeon_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res_ports;
	काष्ठा resource *res_result;
	काष्ठा octeon_rng *rng;
	पूर्णांक ret;
	काष्ठा hwrng ops = अणु
		.name = "octeon",
		.init = octeon_rng_init,
		.cleanup = octeon_rng_cleanup,
		.data_पढ़ो = octeon_rng_data_पढ़ो
	पूर्ण;

	rng = devm_kzalloc(&pdev->dev, माप(*rng), GFP_KERNEL);
	अगर (!rng)
		वापस -ENOMEM;

	res_ports = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_ports)
		वापस -ENOENT;

	res_result = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res_result)
		वापस -ENOENT;


	rng->control_status = devm_ioremap(&pdev->dev,
						   res_ports->start,
						   माप(u64));
	अगर (!rng->control_status)
		वापस -ENOENT;

	rng->result = devm_ioremap(&pdev->dev,
					   res_result->start,
					   माप(u64));
	अगर (!rng->result)
		वापस -ENOENT;

	rng->ops = ops;

	platक्रमm_set_drvdata(pdev, &rng->ops);
	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &rng->ops);
	अगर (ret)
		वापस -ENOENT;

	dev_info(&pdev->dev, "Octeon Random Number Generator\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver octeon_rng_driver = अणु
	.driver = अणु
		.name		= "octeon_rng",
	पूर्ण,
	.probe		= octeon_rng_probe,
पूर्ण;

module_platक्रमm_driver(octeon_rng_driver);

MODULE_AUTHOR("David Daney");
MODULE_LICENSE("GPL");
