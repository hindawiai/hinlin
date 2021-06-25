<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Flash support क्रम OMAP1
 */

#समावेश <linux/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>

#समावेश <mach/tc.h>
#समावेश "flash.h"

#समावेश <mach/hardware.h>

व्योम omap1_set_vpp(काष्ठा platक्रमm_device *pdev, पूर्णांक enable)
अणु
	u32 l;

	l = omap_पढ़ोl(EMIFS_CONFIG);
	अगर (enable)
		l |= OMAP_EMIFS_CONFIG_WP;
	अन्यथा
		l &= ~OMAP_EMIFS_CONFIG_WP;
	omap_ग_लिखोl(l, EMIFS_CONFIG);
पूर्ण
