<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 PA Semi, Inc
 *
 * Parts based on arch/घातerpc/sysdev/fsl_soc.c:
 *
 * 2006 (c) MontaVista Software, Inc.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/i2c.h>

#अगर_घोषित CONFIG_I2C_BOARDINFO
/* The below is from fsl_soc.c.  It's copied because since there are no
 * official bus bindings at this समय it करोesn't make sense to share across
 * the platक्रमms, even though they happen to be common.
 */
काष्ठा i2c_driver_device अणु
	अक्षर    *of_device;
	अक्षर    *i2c_type;
पूर्ण;

अटल काष्ठा i2c_driver_device i2c_devices[] __initdata = अणु
	अणु"dallas,ds1338",  "ds1338"पूर्ण,
पूर्ण;

अटल पूर्णांक __init find_i2c_driver(काष्ठा device_node *node,
				     काष्ठा i2c_board_info *info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(i2c_devices); i++) अणु
		अगर (!of_device_is_compatible(node, i2c_devices[i].of_device))
			जारी;
		अगर (strlcpy(info->type, i2c_devices[i].i2c_type,
			    I2C_NAME_SIZE) >= I2C_NAME_SIZE)
			वापस -ENOMEM;
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __init pasemi_रेजिस्टर_i2c_devices(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा device_node *adap_node;
	काष्ठा device_node *node;

	pdev = शून्य;
	जबतक ((pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa003, pdev))) अणु
		adap_node = pci_device_to_OF_node(pdev);

		अगर (!adap_node)
			जारी;

		क्रम_each_child_of_node(adap_node, node) अणु
			काष्ठा i2c_board_info info = अणुपूर्ण;
			स्थिर u32 *addr;
			पूर्णांक len;

			addr = of_get_property(node, "reg", &len);
			अगर (!addr || len < माप(पूर्णांक) ||
			    *addr > (1 << 10) - 1) अणु
				pr_warn("pasemi_register_i2c_devices: invalid i2c device entry\n");
				जारी;
			पूर्ण

			info.irq = irq_of_parse_and_map(node, 0);
			अगर (!info.irq)
				info.irq = -1;

			अगर (find_i2c_driver(node, &info) < 0)
				जारी;

			info.addr = *addr;

			i2c_रेजिस्टर_board_info(PCI_FUNC(pdev->devfn), &info,
						1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(pasemi_रेजिस्टर_i2c_devices);
#पूर्ण_अगर
