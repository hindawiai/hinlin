<शैली गुरु>
/*======================================================================

    Device driver क्रम the PCMCIA control functionality of StrongARM
    SA-1100 microprocessors.

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License क्रम the specअगरic language governing
    rights and limitations under the License.

    The initial developer of the original code is John G. Dorsey
    <john+@cs.cmu.edu>.  Portions created by John G. Dorsey are
    Copyright (C) 1999 John G. Dorsey.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU Public License version 2 (the "GPL"), in which
    हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.
    
======================================================================*/

#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <pcmcia/ss.h>

#समावेश <यंत्र/hardware/scoop.h>

#समावेश "sa1100_generic.h"

अटल स्थिर अक्षर *sa11x0_cf_gpio_names[] = अणु
	[SOC_STAT_CD] = "detect",
	[SOC_STAT_BVD1] = "bvd1",
	[SOC_STAT_BVD2] = "bvd2",
	[SOC_STAT_RDY] = "ready",
पूर्ण;

अटल पूर्णांक sa11x0_cf_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा device *dev = skt->socket.dev.parent;
	पूर्णांक i;

	skt->gpio_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(skt->gpio_reset))
		वापस PTR_ERR(skt->gpio_reset);

	skt->gpio_bus_enable = devm_gpiod_get_optional(dev, "bus-enable",
						       GPIOD_OUT_HIGH);
	अगर (IS_ERR(skt->gpio_bus_enable))
		वापस PTR_ERR(skt->gpio_bus_enable);

	skt->vcc.reg = devm_regulator_get_optional(dev, "vcc");
	अगर (IS_ERR(skt->vcc.reg))
		वापस PTR_ERR(skt->vcc.reg);

	अगर (!skt->vcc.reg)
		dev_warn(dev,
			 "no Vcc regulator provided, ignoring Vcc controls\n");

	क्रम (i = 0; i < ARRAY_SIZE(sa11x0_cf_gpio_names); i++) अणु
		skt->stat[i].name = sa11x0_cf_gpio_names[i];
		skt->stat[i].desc = devm_gpiod_get_optional(dev,
					sa11x0_cf_gpio_names[i], GPIOD_IN);
		अगर (IS_ERR(skt->stat[i].desc))
			वापस PTR_ERR(skt->stat[i].desc);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sa11x0_cf_configure_socket(काष्ठा soc_pcmcia_socket *skt,
	स्थिर socket_state_t *state)
अणु
	वापस soc_pcmcia_regulator_set(skt, &skt->vcc, state->Vcc);
पूर्ण

अटल काष्ठा pcmcia_low_level sa11x0_cf_ops = अणु
	.owner = THIS_MODULE,
	.hw_init = sa11x0_cf_hw_init,
	.socket_state = soc_common_cf_socket_state,
	.configure_socket = sa11x0_cf_configure_socket,
पूर्ण;

पूर्णांक __init pcmcia_collie_init(काष्ठा device *dev);

अटल पूर्णांक (*sa11x0_pcmcia_legacy_hw_init[])(काष्ठा device *dev) = अणु
#अगर defined(CONFIG_SA1100_H3100) || defined(CONFIG_SA1100_H3600)
	pcmcia_h3600_init,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SA1100_SIMPAD
	pcmcia_simpad_init,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SA1100_COLLIE
       pcmcia_collie_init,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sa11x0_drv_pcmcia_legacy_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक i, ret = -ENODEV;

	/*
	 * Initialise any "on-board" PCMCIA sockets.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(sa11x0_pcmcia_legacy_hw_init); i++) अणु
		ret = sa11x0_pcmcia_legacy_hw_init[i](&dev->dev);
		अगर (ret == 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sa11x0_drv_pcmcia_legacy_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा skt_dev_info *sinfo = platक्रमm_get_drvdata(dev);
	पूर्णांक i;

	platक्रमm_set_drvdata(dev, शून्य);

	क्रम (i = 0; i < sinfo->nskt; i++)
		soc_pcmcia_हटाओ_one(&sinfo->skt[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक sa11x0_drv_pcmcia_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा soc_pcmcia_socket *skt;
	काष्ठा device *dev = &pdev->dev;

	अगर (pdev->id == -1)
		वापस sa11x0_drv_pcmcia_legacy_probe(pdev);

	skt = devm_kzalloc(dev, माप(*skt), GFP_KERNEL);
	अगर (!skt)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, skt);

	skt->nr = pdev->id;
	skt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(skt->clk))
		वापस PTR_ERR(skt->clk);

	sa11xx_drv_pcmcia_ops(&sa11x0_cf_ops);
	soc_pcmcia_init_one(skt, &sa11x0_cf_ops, dev);

	वापस sa11xx_drv_pcmcia_add_one(skt);
पूर्ण

अटल पूर्णांक sa11x0_drv_pcmcia_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा soc_pcmcia_socket *skt;

	अगर (dev->id == -1)
		वापस sa11x0_drv_pcmcia_legacy_हटाओ(dev);

	skt = platक्रमm_get_drvdata(dev);

	soc_pcmcia_हटाओ_one(skt);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sa11x0_pcmcia_driver = अणु
	.driver = अणु
		.name		= "sa11x0-pcmcia",
	पूर्ण,
	.probe		= sa11x0_drv_pcmcia_probe,
	.हटाओ		= sa11x0_drv_pcmcia_हटाओ,
पूर्ण;

/* sa11x0_pcmcia_init()
 * ^^^^^^^^^^^^^^^^^^^^
 *
 * This routine perक्रमms low-level PCMCIA initialization and then
 * रेजिस्टरs this socket driver with Card Services.
 *
 * Returns: 0 on success, -ve error code on failure
 */
अटल पूर्णांक __init sa11x0_pcmcia_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sa11x0_pcmcia_driver);
पूर्ण

/* sa11x0_pcmcia_निकास()
 * ^^^^^^^^^^^^^^^^^^^^
 * Invokes the low-level kernel service to मुक्त IRQs associated with this
 * socket controller and reset GPIO edge detection.
 */
अटल व्योम __निकास sa11x0_pcmcia_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sa11x0_pcmcia_driver);
पूर्ण

MODULE_AUTHOR("John Dorsey <john+@cs.cmu.edu>");
MODULE_DESCRIPTION("Linux PCMCIA Card Services: SA-11x0 Socket Controller");
MODULE_LICENSE("Dual MPL/GPL");

fs_initcall(sa11x0_pcmcia_init);
module_निकास(sa11x0_pcmcia_निकास);
