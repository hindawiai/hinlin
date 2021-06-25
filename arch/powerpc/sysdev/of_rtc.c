<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Instantiate mmio-mapped RTC chips based on device tree inक्रमmation
 *
 * Copyright 2007 David Gibson <dwg@au1.ibm.com>, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>

अटल __initdata काष्ठा अणु
	स्थिर अक्षर *compatible;
	अक्षर *plat_name;
पूर्ण of_rtc_table[] = अणु
	अणु "ds1743-nvram", "rtc-ds1742" पूर्ण,
पूर्ण;

व्योम __init of_instantiate_rtc(व्योम)
अणु
	काष्ठा device_node *node;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(of_rtc_table); i++) अणु
		अक्षर *plat_name = of_rtc_table[i].plat_name;

		क्रम_each_compatible_node(node, शून्य,
					 of_rtc_table[i].compatible) अणु
			काष्ठा resource *res;

			res = kदो_स्मृति(माप(*res), GFP_KERNEL);
			अगर (!res) अणु
				prपूर्णांकk(KERN_ERR "OF RTC: Out of memory "
				       "allocating resource structure for %pOF\n",
				       node);
				जारी;
			पूर्ण

			err = of_address_to_resource(node, 0, res);
			अगर (err) अणु
				prपूर्णांकk(KERN_ERR "OF RTC: Error "
				       "translating resources for %pOF\n",
				       node);
				जारी;
			पूर्ण

			prपूर्णांकk(KERN_INFO "OF_RTC: %pOF is a %s @ 0x%llx-0x%llx\n",
			       node, plat_name,
			       (अचिन्हित दीर्घ दीर्घ)res->start,
			       (अचिन्हित दीर्घ दीर्घ)res->end);
			platक्रमm_device_रेजिस्टर_simple(plat_name, -1, res, 1);
		पूर्ण
	पूर्ण
पूर्ण
