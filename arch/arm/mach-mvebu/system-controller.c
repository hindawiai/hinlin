<शैली गुरु>
/*
 * System controller support क्रम Armada 370, 375 and XP platक्रमms.
 *
 * Copyright (C) 2012 Marvell
 *
 * Lior Amsalem <alior@marvell.com>
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * The Armada 370, 375 and Armada XP SoCs have a range of
 * miscellaneous रेजिस्टरs, that करो not beदीर्घ to a particular device,
 * but rather provide प्रणाली-level features. This basic
 * प्रणाली-controller driver provides a device tree binding क्रम those
 * रेजिस्टरs, and implements utility functions offering various
 * features related to those रेजिस्टरs.
 *
 * For now, the feature set is limited to restarting the platक्रमm by a
 * soft-reset, but it might be extended in the future.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>
#समावेश "common.h"
#समावेश "mvebu-soc-id.h"
#समावेश "pmsu.h"

#घोषणा ARMADA_375_CRYPT0_ENG_TARGET 41
#घोषणा ARMADA_375_CRYPT0_ENG_ATTR    1

अटल व्योम __iomem *प्रणाली_controller_base;
अटल phys_addr_t प्रणाली_controller_phys_base;

काष्ठा mvebu_प्रणाली_controller अणु
	u32 rstoutn_mask_offset;
	u32 प्रणाली_soft_reset_offset;

	u32 rstoutn_mask_reset_out_en;
	u32 प्रणाली_soft_reset;

	u32 resume_boot_addr;

	u32 dev_id;
	u32 rev_id;
पूर्ण;
अटल काष्ठा mvebu_प्रणाली_controller *mvebu_sc;

अटल स्थिर काष्ठा mvebu_प्रणाली_controller armada_370_xp_प्रणाली_controller = अणु
	.rstoutn_mask_offset = 0x60,
	.प्रणाली_soft_reset_offset = 0x64,
	.rstoutn_mask_reset_out_en = 0x1,
	.प्रणाली_soft_reset = 0x1,
	.dev_id = 0x38,
	.rev_id = 0x3c,
पूर्ण;

अटल स्थिर काष्ठा mvebu_प्रणाली_controller armada_375_प्रणाली_controller = अणु
	.rstoutn_mask_offset = 0x54,
	.प्रणाली_soft_reset_offset = 0x58,
	.rstoutn_mask_reset_out_en = 0x1,
	.प्रणाली_soft_reset = 0x1,
	.resume_boot_addr = 0xd4,
	.dev_id = 0x38,
	.rev_id = 0x3c,
पूर्ण;

अटल स्थिर काष्ठा mvebu_प्रणाली_controller orion_प्रणाली_controller = अणु
	.rstoutn_mask_offset = 0x108,
	.प्रणाली_soft_reset_offset = 0x10c,
	.rstoutn_mask_reset_out_en = 0x4,
	.प्रणाली_soft_reset = 0x1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_प्रणाली_controller_table[] = अणु
	अणु
		.compatible = "marvell,orion-system-controller",
		.data = (व्योम *) &orion_प्रणाली_controller,
	पूर्ण, अणु
		.compatible = "marvell,armada-370-xp-system-controller",
		.data = (व्योम *) &armada_370_xp_प्रणाली_controller,
	पूर्ण, अणु
		.compatible = "marvell,armada-375-system-controller",
		.data = (व्योम *) &armada_375_प्रणाली_controller,
	पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

व्योम mvebu_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (!प्रणाली_controller_base) अणु
		pr_err("Cannot restart, system-controller not available: check the device tree\n");
	पूर्ण अन्यथा अणु
		/*
		 * Enable soft reset to निश्चित RSTOUTn.
		 */
		ग_लिखोl(mvebu_sc->rstoutn_mask_reset_out_en,
			प्रणाली_controller_base +
			mvebu_sc->rstoutn_mask_offset);
		/*
		 * Assert soft reset.
		 */
		ग_लिखोl(mvebu_sc->प्रणाली_soft_reset,
			प्रणाली_controller_base +
			mvebu_sc->प्रणाली_soft_reset_offset);
	पूर्ण

	जबतक (1)
		;
पूर्ण

पूर्णांक mvebu_प्रणाली_controller_get_soc_id(u32 *dev, u32 *rev)
अणु
	अगर (of_machine_is_compatible("marvell,armada380") &&
		प्रणाली_controller_base) अणु
		*dev = पढ़ोl(प्रणाली_controller_base + mvebu_sc->dev_id) >> 16;
		*rev = (पढ़ोl(प्रणाली_controller_base + mvebu_sc->rev_id) >> 8)
			& 0xF;
		वापस 0;
	पूर्ण अन्यथा
		वापस -ENODEV;
पूर्ण

#अगर defined(CONFIG_SMP) && defined(CONFIG_MACH_MVEBU_V7)
अटल व्योम mvebu_armada375_smp_wa_init(व्योम)
अणु
	u32 dev, rev;
	phys_addr_t resume_addr_reg;

	अगर (mvebu_get_soc_id(&dev, &rev) != 0)
		वापस;

	अगर (rev != ARMADA_375_Z1_REV)
		वापस;

	resume_addr_reg = प्रणाली_controller_phys_base +
		mvebu_sc->resume_boot_addr;
	mvebu_setup_boot_addr_wa(ARMADA_375_CRYPT0_ENG_TARGET,
				 ARMADA_375_CRYPT0_ENG_ATTR,
				 resume_addr_reg);
पूर्ण

व्योम mvebu_प्रणाली_controller_set_cpu_boot_addr(व्योम *boot_addr)
अणु
	BUG_ON(प्रणाली_controller_base == शून्य);
	BUG_ON(mvebu_sc->resume_boot_addr == 0);

	अगर (of_machine_is_compatible("marvell,armada375"))
		mvebu_armada375_smp_wa_init();

	ग_लिखोl(__pa_symbol(boot_addr), प्रणाली_controller_base +
	       mvebu_sc->resume_boot_addr);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init mvebu_प्रणाली_controller_init(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;

	np = of_find_matching_node_and_match(शून्य, of_प्रणाली_controller_table,
					     &match);
	अगर (np) अणु
		काष्ठा resource res;
		प्रणाली_controller_base = of_iomap(np, 0);
		of_address_to_resource(np, 0, &res);
		प्रणाली_controller_phys_base = res.start;
		mvebu_sc = (काष्ठा mvebu_प्रणाली_controller *)match->data;
		of_node_put(np);
	पूर्ण

	वापस 0;
पूर्ण

early_initcall(mvebu_प्रणाली_controller_init);
