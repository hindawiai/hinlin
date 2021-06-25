<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/bootinfo.h>

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	अचिन्हित पूर्णांक processor_id = (&current_cpu_data)->processor_id;

	चयन (processor_id & PRID_REV_MASK) अणु
	हाल PRID_REV_LOONGSON1B:
#अगर defined(CONFIG_LOONGSON1_LS1B)
		वापस "LOONGSON LS1B";
#या_अगर defined(CONFIG_LOONGSON1_LS1C)
		वापस "LOONGSON LS1C";
#पूर्ण_अगर
	शेष:
		वापस "LOONGSON (unknown)";
	पूर्ण
पूर्ण
