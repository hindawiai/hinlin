<शैली गुरु>
/*
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2011 Thomas Chou
 * Copyright (C) 2011 Walter Goossens
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>

अटल स्थिर काष्ठा of_device_id clk_match[] __initस्थिर = अणु
	अणु .compatible = "fixed-clock", .data = of_fixed_clk_setup, पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init nios2_soc_device_init(व्योम)
अणु
	काष्ठा soc_device *soc_dev;
	काष्ठा soc_device_attribute *soc_dev_attr;
	स्थिर अक्षर *machine;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (soc_dev_attr) अणु
		machine = of_flat_dt_get_machine_name();
		अगर (machine)
			soc_dev_attr->machine = kaप्र_लिखो(GFP_KERNEL, "%s",
						machine);

		soc_dev_attr->family = "Nios II";

		soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
		अगर (IS_ERR(soc_dev)) अणु
			kमुक्त(soc_dev_attr->machine);
			kमुक्त(soc_dev_attr);
		पूर्ण
	पूर्ण

	of_clk_init(clk_match);

	वापस 0;
पूर्ण

device_initcall(nios2_soc_device_init);
