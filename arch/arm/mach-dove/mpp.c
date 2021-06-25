<शैली गुरु>
/*
 * arch/arm/mach-करोve/mpp.c
 *
 * MPP functions क्रम Marvell Dove SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>
#समावेश <plat/mpp.h>
#समावेश <plat/orion-gpपन.स>
#समावेश "dove.h"
#समावेश "mpp.h"

काष्ठा करोve_mpp_grp अणु
	पूर्णांक start;
	पूर्णांक end;
पूर्ण;

/* Map a group to a range of GPIO pins in that group */
अटल स्थिर काष्ठा करोve_mpp_grp करोve_mpp_grp[] = अणु
	[MPP_24_39] = अणु
		.start	= 24,
		.end	= 39,
	पूर्ण,
	[MPP_40_45] = अणु
		.start	= 40,
		.end	= 45,
	पूर्ण,
	[MPP_46_51] = अणु
		.start	= 46,
		.end	= 51,
	पूर्ण,
	[MPP_58_61] = अणु
		.start	= 58,
		.end	= 61,
	पूर्ण,
	[MPP_62_63] = अणु
		.start	= 62,
		.end	= 63,
	पूर्ण,
पूर्ण;

/* Enable gpio क्रम a range of pins. mode should be a combination of
   GPIO_OUTPUT_OK | GPIO_INPUT_OK */
अटल व्योम __init करोve_mpp_gpio_mode(पूर्णांक start, पूर्णांक end, पूर्णांक gpio_mode)
अणु
	पूर्णांक i;

	क्रम (i = start; i <= end; i++)
		orion_gpio_set_valid(i, gpio_mode);
पूर्ण

/* Dump all the extra MPP रेजिस्टरs. The platक्रमm code will dump the
   रेजिस्टरs क्रम pins 0-23. */
अटल व्योम __init करोve_mpp_dump_regs(व्योम)
अणु
	pr_debug("PMU_CTRL4_CTRL: %08x\n",
		 पढ़ोl(DOVE_MPP_CTRL4_VIRT_BASE));

	pr_debug("PMU_MPP_GENERAL_CTRL: %08x\n",
		 पढ़ोl(DOVE_PMU_MPP_GENERAL_CTRL));

	pr_debug("MPP_GENERAL: %08x\n", पढ़ोl(DOVE_MPP_GENERAL_VIRT_BASE));
पूर्ण

अटल व्योम __init करोve_mpp_cfg_nfc(पूर्णांक sel)
अणु
	u32 mpp_gen_cfg = पढ़ोl(DOVE_MPP_GENERAL_VIRT_BASE);

	mpp_gen_cfg &= ~0x1;
	mpp_gen_cfg |= sel;
	ग_लिखोl(mpp_gen_cfg, DOVE_MPP_GENERAL_VIRT_BASE);

	करोve_mpp_gpio_mode(64, 71, GPIO_OUTPUT_OK);
पूर्ण

अटल व्योम __init करोve_mpp_cfg_au1(पूर्णांक sel)
अणु
	u32 mpp_ctrl4 = पढ़ोl(DOVE_MPP_CTRL4_VIRT_BASE);
	u32 ssp_ctrl1 = पढ़ोl(DOVE_SSP_CTRL_STATUS_1);
	u32 mpp_gen_ctrl = पढ़ोl(DOVE_MPP_GENERAL_VIRT_BASE);
	u32 global_cfg_2 = पढ़ोl(DOVE_GLOBAL_CONFIG_2);

	mpp_ctrl4 &= ~(DOVE_AU1_GPIO_SEL);
	ssp_ctrl1 &= ~(DOVE_SSP_ON_AU1);
	mpp_gen_ctrl &= ~(DOVE_AU1_SPDIFO_GPIO_EN);
	global_cfg_2 &= ~(DOVE_TWSI_OPTION3_GPIO);

	अगर (!sel || sel == 0x2)
		करोve_mpp_gpio_mode(52, 57, 0);
	अन्यथा
		करोve_mpp_gpio_mode(52, 57, GPIO_OUTPUT_OK | GPIO_INPUT_OK);

	अगर (sel & 0x1) अणु
		global_cfg_2 |= DOVE_TWSI_OPTION3_GPIO;
		करोve_mpp_gpio_mode(56, 57, 0);
	पूर्ण
	अगर (sel & 0x2) अणु
		mpp_gen_ctrl |= DOVE_AU1_SPDIFO_GPIO_EN;
		करोve_mpp_gpio_mode(57, 57, GPIO_OUTPUT_OK | GPIO_INPUT_OK);
	पूर्ण
	अगर (sel & 0x4) अणु
		ssp_ctrl1 |= DOVE_SSP_ON_AU1;
		करोve_mpp_gpio_mode(52, 55, 0);
	पूर्ण
	अगर (sel & 0x8)
		mpp_ctrl4 |= DOVE_AU1_GPIO_SEL;

	ग_लिखोl(mpp_ctrl4, DOVE_MPP_CTRL4_VIRT_BASE);
	ग_लिखोl(ssp_ctrl1, DOVE_SSP_CTRL_STATUS_1);
	ग_लिखोl(mpp_gen_ctrl, DOVE_MPP_GENERAL_VIRT_BASE);
	ग_लिखोl(global_cfg_2, DOVE_GLOBAL_CONFIG_2);
पूर्ण

/* Configure the group रेजिस्टरs, enabling GPIO अगर sel indicates the
   pin is to be used क्रम GPIO */
अटल व्योम __init करोve_mpp_conf_grp(अचिन्हित पूर्णांक *mpp_grp_list)
अणु
	u32 mpp_ctrl4 = पढ़ोl(DOVE_MPP_CTRL4_VIRT_BASE);
	पूर्णांक gpio_mode;

	क्रम ( ; *mpp_grp_list; mpp_grp_list++) अणु
		अचिन्हित पूर्णांक num = MPP_NUM(*mpp_grp_list);
		अचिन्हित पूर्णांक sel = MPP_SEL(*mpp_grp_list);

		अगर (num > MPP_GRP_MAX) अणु
			pr_err("dove: invalid MPP GRP number (%u)\n", num);
			जारी;
		पूर्ण

		mpp_ctrl4 &= ~(0x1 << num);
		mpp_ctrl4 |= sel << num;

		gpio_mode = sel ? GPIO_OUTPUT_OK | GPIO_INPUT_OK : 0;
		करोve_mpp_gpio_mode(करोve_mpp_grp[num].start,
				   करोve_mpp_grp[num].end, gpio_mode);
	पूर्ण
	ग_लिखोl(mpp_ctrl4, DOVE_MPP_CTRL4_VIRT_BASE);
पूर्ण

/* Configure the various MPP pins on Dove */
व्योम __init करोve_mpp_conf(अचिन्हित पूर्णांक *mpp_list,
			  अचिन्हित पूर्णांक *mpp_grp_list,
			  अचिन्हित पूर्णांक grp_au1_52_57,
			  अचिन्हित पूर्णांक grp_nfc_64_71)
अणु
	करोve_mpp_dump_regs();

	/* Use platक्रमm code क्रम pins 0-23 */
	orion_mpp_conf(mpp_list, 0, MPP_MAX, DOVE_MPP_VIRT_BASE);

	करोve_mpp_conf_grp(mpp_grp_list);
	करोve_mpp_cfg_au1(grp_au1_52_57);
	करोve_mpp_cfg_nfc(grp_nfc_64_71);

	करोve_mpp_dump_regs();
पूर्ण
