<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MX25 CPU type detection
 *
 * Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 * Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved
 */
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "iim.h"
#समावेश "hardware.h"

अटल पूर्णांक mx25_cpu_rev = -1;

अटल पूर्णांक mx25_पढ़ो_cpu_rev(व्योम)
अणु
	u32 rev;
	व्योम __iomem *iim_base;
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx25-iim");
	iim_base = of_iomap(np, 0);
	BUG_ON(!iim_base);
	rev = पढ़ोl(iim_base + MXC_IIMSREV);
	iounmap(iim_base);

	चयन (rev) अणु
	हाल 0x00:
		वापस IMX_CHIP_REVISION_1_0;
	हाल 0x01:
		वापस IMX_CHIP_REVISION_1_1;
	शेष:
		वापस IMX_CHIP_REVISION_UNKNOWN;
	पूर्ण
पूर्ण

पूर्णांक mx25_revision(व्योम)
अणु
	अगर (mx25_cpu_rev == -1)
		mx25_cpu_rev = mx25_पढ़ो_cpu_rev();

	वापस mx25_cpu_rev;
पूर्ण
EXPORT_SYMBOL(mx25_revision);
