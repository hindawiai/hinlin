<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MIPS support क्रम CONFIG_OF device tree support
 *
 * Copyright (C) 2010 Cisco Systems Inc. <dediao@cisco.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/memblock.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prom.h>

अटल अक्षर mips_machine_name[64] = "Unknown";

__init व्योम mips_set_machine_name(स्थिर अक्षर *name)
अणु
	अगर (name == शून्य)
		वापस;

	strlcpy(mips_machine_name, name, माप(mips_machine_name));
	pr_info("MIPS: machine is %s\n", mips_get_machine_name());
पूर्ण

अक्षर *mips_get_machine_name(व्योम)
अणु
	वापस mips_machine_name;
पूर्ण

#अगर_घोषित CONFIG_USE_OF

व्योम __init __dt_setup_arch(व्योम *bph)
अणु
	अगर (!early_init_dt_scan(bph))
		वापस;

	mips_set_machine_name(of_flat_dt_get_machine_name());
पूर्ण

पूर्णांक __init __dt_रेजिस्टर_buses(स्थिर अक्षर *bus0, स्थिर अक्षर *bus1)
अणु
	अटल काष्ठा of_device_id of_ids[3];

	अगर (!of_have_populated_dt())
		panic("device tree not present");

	strlcpy(of_ids[0].compatible, bus0, माप(of_ids[0].compatible));
	अगर (bus1) अणु
		strlcpy(of_ids[1].compatible, bus1,
			माप(of_ids[1].compatible));
	पूर्ण

	अगर (of_platक्रमm_populate(शून्य, of_ids, शून्य, शून्य))
		panic("failed to populate DT");

	वापस 0;
पूर्ण

#पूर्ण_अगर
