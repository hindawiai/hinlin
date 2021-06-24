<शैली गुरु>
/*
 * i.MX27 Power Management Routines
 *
 * Based on Freescale's BSP
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License.
 */

#समावेश <linux/of_address.h>
#समावेश <linux/kernel.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पन.स>

#समावेश "common.h"
#समावेश "hardware.h"

अटल पूर्णांक mx27_suspend_enter(suspend_state_t state)
अणु
	व्योम __iomem *ccm_base;
	काष्ठा device_node *np;
	u32 cscr;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx27-ccm");
	ccm_base = of_iomap(np, 0);
	BUG_ON(!ccm_base);

	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		/* Clear MPEN and SPEN to disable MPLL/SPLL */
		cscr = imx_पढ़ोl(ccm_base);
		cscr &= 0xFFFFFFFC;
		imx_ग_लिखोl(cscr, ccm_base);
		/* Executes WFI */
		cpu_करो_idle();
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops mx27_suspend_ops = अणु
	.enter = mx27_suspend_enter,
	.valid = suspend_valid_only_mem,
पूर्ण;

व्योम __init imx27_pm_init(व्योम)
अणु
	suspend_set_ops(&mx27_suspend_ops);
पूर्ण
