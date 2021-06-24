<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  CLPS711X CPU idle driver
 *
 *  Copyright (C) 2014 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा CLPS711X_CPUIDLE_NAME	"clps711x-cpuidle"

अटल व्योम __iomem *clps711x_halt;

अटल पूर्णांक clps711x_cpuidle_halt(काष्ठा cpuidle_device *dev,
				 काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	ग_लिखोl(0xaa, clps711x_halt);

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver clps711x_idle_driver = अणु
	.name		= CLPS711X_CPUIDLE_NAME,
	.owner		= THIS_MODULE,
	.states[0]	= अणु
		.name		= "HALT",
		.desc		= "CLPS711X HALT",
		.enter		= clps711x_cpuidle_halt,
		.निकास_latency	= 1,
	पूर्ण,
	.state_count	= 1,
पूर्ण;

अटल पूर्णांक __init clps711x_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	clps711x_halt = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(clps711x_halt))
		वापस PTR_ERR(clps711x_halt);

	वापस cpuidle_रेजिस्टर(&clps711x_idle_driver, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver clps711x_cpuidle_driver = अणु
	.driver	= अणु
		.name	= CLPS711X_CPUIDLE_NAME,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(clps711x_cpuidle_driver, clps711x_cpuidle_probe);
