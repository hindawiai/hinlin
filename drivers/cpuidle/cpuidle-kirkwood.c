<शैली गुरु>
/*
 * CPU idle Marvell Kirkwood SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * The cpu idle uses रुको-क्रम-पूर्णांकerrupt and DDR self refresh in order
 * to implement two idle states -
 * #1 रुको-क्रम-पूर्णांकerrupt
 * #2 रुको-क्रम-पूर्णांकerrupt and DDR self refresh
 *
 * Maपूर्णांकainer: Jason Cooper <jason@lakedaemon.net>
 * Maपूर्णांकainer: Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <यंत्र/cpuidle.h>

#घोषणा KIRKWOOD_MAX_STATES	2

अटल व्योम __iomem *ddr_operation_base;

/* Actual code that माला_दो the SoC in dअगरferent idle states */
अटल पूर्णांक kirkwood_enter_idle(काष्ठा cpuidle_device *dev,
			       काष्ठा cpuidle_driver *drv,
			       पूर्णांक index)
अणु
	ग_लिखोl(0x7, ddr_operation_base);
	cpu_करो_idle();

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver kirkwood_idle_driver = अणु
	.name			= "kirkwood_idle",
	.owner			= THIS_MODULE,
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[1]		= अणु
		.enter			= kirkwood_enter_idle,
		.निकास_latency		= 10,
		.target_residency	= 100000,
		.name			= "DDR SR",
		.desc			= "WFI and DDR Self Refresh",
	पूर्ण,
	.state_count = KIRKWOOD_MAX_STATES,
पूर्ण;

/* Initialize CPU idle by रेजिस्टरing the idle states */
अटल पूर्णांक kirkwood_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	ddr_operation_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ddr_operation_base))
		वापस PTR_ERR(ddr_operation_base);

	वापस cpuidle_रेजिस्टर(&kirkwood_idle_driver, शून्य);
पूर्ण

अटल पूर्णांक kirkwood_cpuidle_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpuidle_unरेजिस्टर(&kirkwood_idle_driver);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver kirkwood_cpuidle_driver = अणु
	.probe = kirkwood_cpuidle_probe,
	.हटाओ = kirkwood_cpuidle_हटाओ,
	.driver = अणु
		   .name = "kirkwood_cpuidle",
		   पूर्ण,
पूर्ण;

module_platक्रमm_driver(kirkwood_cpuidle_driver);

MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_DESCRIPTION("Kirkwood cpu idle driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:kirkwood-cpuidle");
