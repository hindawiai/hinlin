<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MX31 CPU type detection
 *
 * Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>

#समावेश "common.h"
#समावेश "hardware.h"
#समावेश "iim.h"

अटल पूर्णांक mx31_cpu_rev = -1;

अटल काष्ठा अणु
	u8 srev;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक rev;
पूर्ण mx31_cpu_type[] = अणु
	अणु .srev = 0x00, .name = "i.MX31(L)", .rev = IMX_CHIP_REVISION_1_0 पूर्ण,
	अणु .srev = 0x10, .name = "i.MX31",    .rev = IMX_CHIP_REVISION_1_1 पूर्ण,
	अणु .srev = 0x11, .name = "i.MX31L",   .rev = IMX_CHIP_REVISION_1_1 पूर्ण,
	अणु .srev = 0x12, .name = "i.MX31",    .rev = IMX_CHIP_REVISION_1_1 पूर्ण,
	अणु .srev = 0x13, .name = "i.MX31L",   .rev = IMX_CHIP_REVISION_1_1 पूर्ण,
	अणु .srev = 0x14, .name = "i.MX31",    .rev = IMX_CHIP_REVISION_1_2 पूर्ण,
	अणु .srev = 0x15, .name = "i.MX31L",   .rev = IMX_CHIP_REVISION_1_2 पूर्ण,
	अणु .srev = 0x28, .name = "i.MX31",    .rev = IMX_CHIP_REVISION_2_0 पूर्ण,
	अणु .srev = 0x29, .name = "i.MX31L",   .rev = IMX_CHIP_REVISION_2_0 पूर्ण,
पूर्ण;

अटल पूर्णांक mx31_पढ़ो_cpu_rev(व्योम)
अणु
	व्योम __iomem *iim_base;
	काष्ठा device_node *np;
	u32 i, srev;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx31-iim");
	iim_base = of_iomap(np, 0);
	BUG_ON(!iim_base);

	/* पढ़ो SREV रेजिस्टर from IIM module */
	srev = imx_पढ़ोl(iim_base + MXC_IIMSREV);
	srev &= 0xff;

	क्रम (i = 0; i < ARRAY_SIZE(mx31_cpu_type); i++)
		अगर (srev == mx31_cpu_type[i].srev) अणु
			imx_prपूर्णांक_silicon_rev(mx31_cpu_type[i].name,
						mx31_cpu_type[i].rev);
			वापस mx31_cpu_type[i].rev;
		पूर्ण

	imx_prपूर्णांक_silicon_rev("i.MX31", IMX_CHIP_REVISION_UNKNOWN);
	वापस IMX_CHIP_REVISION_UNKNOWN;
पूर्ण

पूर्णांक mx31_revision(व्योम)
अणु
	अगर (mx31_cpu_rev == -1)
		mx31_cpu_rev = mx31_पढ़ो_cpu_rev();

	वापस mx31_cpu_rev;
पूर्ण
EXPORT_SYMBOL(mx31_revision);
