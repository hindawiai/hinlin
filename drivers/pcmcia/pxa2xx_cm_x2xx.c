<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa/pxa_cm_x2xx.c
 *
 * Compulab Ltd., 2003, 2007, 2008
 * Mike Rapoport <mike@compulab.co.il>
 */

#समावेश <linux/module.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>

पूर्णांक cmx255_pcmcia_init(व्योम);
पूर्णांक cmx270_pcmcia_init(व्योम);
व्योम cmx255_pcmcia_निकास(व्योम);
व्योम cmx270_pcmcia_निकास(व्योम);

अटल पूर्णांक __init cmx2xx_pcmcia_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (machine_is_armcore() && cpu_is_pxa25x())
		ret = cmx255_pcmcia_init();
	अन्यथा अगर (machine_is_armcore() && cpu_is_pxa27x())
		ret = cmx270_pcmcia_init();

	वापस ret;
पूर्ण

अटल व्योम __निकास cmx2xx_pcmcia_निकास(व्योम)
अणु
	अगर (machine_is_armcore() && cpu_is_pxa25x())
		cmx255_pcmcia_निकास();
	अन्यथा अगर (machine_is_armcore() && cpu_is_pxa27x())
		cmx270_pcmcia_निकास();
पूर्ण

module_init(cmx2xx_pcmcia_init);
module_निकास(cmx2xx_pcmcia_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_DESCRIPTION("CM-x2xx PCMCIA driver");
