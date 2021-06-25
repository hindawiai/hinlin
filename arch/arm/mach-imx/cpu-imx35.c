<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MX35 CPU type detection
 *
 * Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 */
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>

#समावेश "hardware.h"
#समावेश "iim.h"

अटल पूर्णांक mx35_cpu_rev = -1;

अटल पूर्णांक mx35_पढ़ो_cpu_rev(व्योम)
अणु
	व्योम __iomem *iim_base;
	काष्ठा device_node *np;
	u32 rev;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx35-iim");
	iim_base = of_iomap(np, 0);
	BUG_ON(!iim_base);

	rev = imx_पढ़ोl(iim_base + MXC_IIMSREV);
	चयन (rev) अणु
	हाल 0x00:
		वापस IMX_CHIP_REVISION_1_0;
	हाल 0x10:
		वापस IMX_CHIP_REVISION_2_0;
	हाल 0x11:
		वापस IMX_CHIP_REVISION_2_1;
	शेष:
		वापस IMX_CHIP_REVISION_UNKNOWN;
	पूर्ण
पूर्ण

पूर्णांक mx35_revision(व्योम)
अणु
	अगर (mx35_cpu_rev == -1)
		mx35_cpu_rev = mx35_पढ़ो_cpu_rev();

	वापस mx35_cpu_rev;
पूर्ण
EXPORT_SYMBOL(mx35_revision);
