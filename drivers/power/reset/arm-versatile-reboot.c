<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Linaro Ltd.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>

#घोषणा INTEGRATOR_HDR_CTRL_OFFSET	0x0C
#घोषणा INTEGRATOR_HDR_LOCK_OFFSET	0x14
#घोषणा INTEGRATOR_CM_CTRL_RESET	(1 << 3)

#घोषणा VERSATILE_SYS_LOCK_OFFSET	0x20
#घोषणा VERSATILE_SYS_RESETCTL_OFFSET	0x40

/* Magic unlocking token used on all Versatile boards */
#घोषणा VERSATILE_LOCK_VAL		0xA05F

/*
 * We detect the dअगरferent syscon types from the compatible strings.
 */
क्रमागत versatile_reboot अणु
	INTEGRATOR_REBOOT_CM,
	VERSATILE_REBOOT_CM,
	REALVIEW_REBOOT_EB,
	REALVIEW_REBOOT_PB1176,
	REALVIEW_REBOOT_PB11MP,
	REALVIEW_REBOOT_PBA8,
	REALVIEW_REBOOT_PBX,
पूर्ण;

/* Poपूर्णांकer to the प्रणाली controller */
अटल काष्ठा regmap *syscon_regmap;
अटल क्रमागत versatile_reboot versatile_reboot_type;

अटल स्थिर काष्ठा of_device_id versatile_reboot_of_match[] = अणु
	अणु
		.compatible = "arm,core-module-integrator",
		.data = (व्योम *)INTEGRATOR_REBOOT_CM
	पूर्ण,
	अणु
		.compatible = "arm,core-module-versatile",
		.data = (व्योम *)VERSATILE_REBOOT_CM,
	पूर्ण,
	अणु
		.compatible = "arm,realview-eb-syscon",
		.data = (व्योम *)REALVIEW_REBOOT_EB,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pb1176-syscon",
		.data = (व्योम *)REALVIEW_REBOOT_PB1176,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pb11mp-syscon",
		.data = (व्योम *)REALVIEW_REBOOT_PB11MP,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pba8-syscon",
		.data = (व्योम *)REALVIEW_REBOOT_PBA8,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pbx-syscon",
		.data = (व्योम *)REALVIEW_REBOOT_PBX,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक versatile_reboot(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ mode,
			    व्योम *cmd)
अणु
	/* Unlock the reset रेजिस्टर */
	/* Then hit reset on the dअगरferent machines */
	चयन (versatile_reboot_type) अणु
	हाल INTEGRATOR_REBOOT_CM:
		regmap_ग_लिखो(syscon_regmap, INTEGRATOR_HDR_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_update_bits(syscon_regmap,
				   INTEGRATOR_HDR_CTRL_OFFSET,
				   INTEGRATOR_CM_CTRL_RESET,
				   INTEGRATOR_CM_CTRL_RESET);
		अवरोध;
	हाल VERSATILE_REBOOT_CM:
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_update_bits(syscon_regmap,
				   VERSATILE_SYS_RESETCTL_OFFSET,
				   0x0107,
				   0x0105);
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     0);
		अवरोध;
	हाल REALVIEW_REBOOT_EB:
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_ग_लिखो(syscon_regmap,
			     VERSATILE_SYS_RESETCTL_OFFSET, 0x0008);
		अवरोध;
	हाल REALVIEW_REBOOT_PB1176:
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_ग_लिखो(syscon_regmap,
			     VERSATILE_SYS_RESETCTL_OFFSET, 0x0100);
		अवरोध;
	हाल REALVIEW_REBOOT_PB11MP:
	हाल REALVIEW_REBOOT_PBA8:
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_RESETCTL_OFFSET,
			     0x0000);
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_RESETCTL_OFFSET,
			     0x0004);
		अवरोध;
	हाल REALVIEW_REBOOT_PBX:
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_RESETCTL_OFFSET,
			     0x00f0);
		regmap_ग_लिखो(syscon_regmap, VERSATILE_SYS_RESETCTL_OFFSET,
			     0x00f4);
		अवरोध;
	पूर्ण
	dsb();

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block versatile_reboot_nb = अणु
	.notअगरier_call = versatile_reboot,
	.priority = 192,
पूर्ण;

अटल पूर्णांक __init versatile_reboot_probe(व्योम)
अणु
	स्थिर काष्ठा of_device_id *reboot_id;
	काष्ठा device_node *np;
	पूर्णांक err;

	np = of_find_matching_node_and_match(शून्य, versatile_reboot_of_match,
						 &reboot_id);
	अगर (!np)
		वापस -ENODEV;
	versatile_reboot_type = (क्रमागत versatile_reboot)reboot_id->data;

	syscon_regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(syscon_regmap))
		वापस PTR_ERR(syscon_regmap);

	err = रेजिस्टर_restart_handler(&versatile_reboot_nb);
	अगर (err)
		वापस err;

	pr_info("versatile reboot driver registered\n");
	वापस 0;
पूर्ण
device_initcall(versatile_reboot_probe);
