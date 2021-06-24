<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Juergen Beisert, kernel@pengutronix.de
 */

/*
 * i.MX27 specअगरic CPU detection code
 */

#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/module.h>

#समावेश "hardware.h"

अटल पूर्णांक mx27_cpu_rev = -1;
अटल पूर्णांक mx27_cpu_partnumber;

#घोषणा SYS_CHIP_ID             0x00    /* The offset of CHIP ID रेजिस्टर */
#घोषणा SYSCTRL_OFFSET		0x800	/* Offset from CCM base address */

अटल पूर्णांक mx27_पढ़ो_cpu_rev(व्योम)
अणु
	व्योम __iomem *ccm_base;
	काष्ठा device_node *np;
	u32 val;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx27-ccm");
	ccm_base = of_iomap(np, 0);
	BUG_ON(!ccm_base);
	/*
	 * now we have access to the IO रेजिस्टरs. As we need
	 * the silicon revision very early we पढ़ो it here to
	 * aव्योम any further hooks
	*/
	val = imx_पढ़ोl(ccm_base + SYSCTRL_OFFSET + SYS_CHIP_ID);

	mx27_cpu_partnumber = (पूर्णांक)((val >> 12) & 0xFFFF);

	चयन (val >> 28) अणु
	हाल 0:
		वापस IMX_CHIP_REVISION_1_0;
	हाल 1:
		वापस IMX_CHIP_REVISION_2_0;
	हाल 2:
		वापस IMX_CHIP_REVISION_2_1;
	शेष:
		वापस IMX_CHIP_REVISION_UNKNOWN;
	पूर्ण
पूर्ण

/*
 * Returns:
 *	the silicon revision of the cpu
 *	-EINVAL - not a mx27
 */
पूर्णांक mx27_revision(व्योम)
अणु
	अगर (mx27_cpu_rev == -1)
		mx27_cpu_rev = mx27_पढ़ो_cpu_rev();

	अगर (mx27_cpu_partnumber != 0x8821)
		वापस -EINVAL;

	वापस mx27_cpu_rev;
पूर्ण
EXPORT_SYMBOL(mx27_revision);
