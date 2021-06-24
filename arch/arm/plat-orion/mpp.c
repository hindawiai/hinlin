<शैली गुरु>
/*
 * arch/arm/plat-orion/mpp.c
 *
 * MPP functions क्रम Marvell orion SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mbus.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <plat/orion-gpपन.स>
#समावेश <plat/mpp.h>

/* Address of the ith MPP control रेजिस्टर */
अटल __init व्योम __iomem *mpp_ctrl_addr(अचिन्हित पूर्णांक i,
					  व्योम __iomem *dev_bus)
अणु
	वापस dev_bus + (i) * 4;
पूर्ण


व्योम __init orion_mpp_conf(अचिन्हित पूर्णांक *mpp_list, अचिन्हित पूर्णांक variant_mask,
			   अचिन्हित पूर्णांक mpp_max, व्योम __iomem *dev_bus)
अणु
	अचिन्हित पूर्णांक mpp_nr_regs = (1 + mpp_max/8);
	u32 mpp_ctrl[8];
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "initial MPP regs:");
	अगर (mpp_nr_regs > ARRAY_SIZE(mpp_ctrl)) अणु
		prपूर्णांकk(KERN_ERR "orion_mpp_conf: invalid mpp_max\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < mpp_nr_regs; i++) अणु
		mpp_ctrl[i] = पढ़ोl(mpp_ctrl_addr(i, dev_bus));
		prपूर्णांकk(" %08x", mpp_ctrl[i]);
	पूर्ण
	prपूर्णांकk("\n");

	क्रम ( ; *mpp_list; mpp_list++) अणु
		अचिन्हित पूर्णांक num = MPP_NUM(*mpp_list);
		अचिन्हित पूर्णांक sel = MPP_SEL(*mpp_list);
		पूर्णांक shअगरt, gpio_mode;

		अगर (num > mpp_max) अणु
			prपूर्णांकk(KERN_ERR "orion_mpp_conf: invalid MPP "
					"number (%u)\n", num);
			जारी;
		पूर्ण
		अगर (variant_mask && !(*mpp_list & variant_mask)) अणु
			prपूर्णांकk(KERN_WARNING
			       "orion_mpp_conf: requested MPP%u config "
			       "unavailable on this hardware\n", num);
			जारी;
		पूर्ण

		shअगरt = (num & 7) << 2;
		mpp_ctrl[num / 8] &= ~(0xf << shअगरt);
		mpp_ctrl[num / 8] |= sel << shअगरt;

		gpio_mode = 0;
		अगर (*mpp_list & MPP_INPUT_MASK)
			gpio_mode |= GPIO_INPUT_OK;
		अगर (*mpp_list & MPP_OUTPUT_MASK)
			gpio_mode |= GPIO_OUTPUT_OK;

		orion_gpio_set_valid(num, gpio_mode);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "  final MPP regs:");
	क्रम (i = 0; i < mpp_nr_regs; i++) अणु
		ग_लिखोl(mpp_ctrl[i], mpp_ctrl_addr(i, dev_bus));
		prपूर्णांकk(" %08x", mpp_ctrl[i]);
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण
