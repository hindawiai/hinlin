<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 *
 * Copyright (c) 2009 Zhang Le <r0bertz@gentoo.org>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/bootinfo.h>

#समावेश <loongson.h>
#समावेश <machine.h>

/* please ensure the length of the machtype string is less than 50 */
#घोषणा MACHTYPE_LEN 50

अटल स्थिर अक्षर *प्रणाली_types[] = अणु
	[MACH_LOONGSON_UNKNOWN]	= "unknown loongson machine",
	[MACH_LEMOTE_FL2E]	= "lemote-fuloong-2e-box",
	[MACH_LEMOTE_FL2F]	= "lemote-fuloong-2f-box",
	[MACH_LEMOTE_ML2F7]	= "lemote-mengloong-2f-7inches",
	[MACH_LEMOTE_YL2F89]	= "lemote-yeeloong-2f-8.9inches",
	[MACH_DEXXON_GDIUM2F10]	= "dexxon-gdium-2f",
	[MACH_LEMOTE_NAS]	= "lemote-nas-2f",
	[MACH_LEMOTE_LL2F]	= "lemote-lynloong-2f",
	[MACH_LOONGSON_END]	= शून्य,
पूर्ण;

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस प्रणाली_types[mips_machtype];
पूर्ण

व्योम __weak __init mach_prom_init_machtype(व्योम)
अणु
पूर्ण

व्योम __init prom_init_machtype(व्योम)
अणु
	अक्षर *p, str[MACHTYPE_LEN + 1];
	पूर्णांक machtype = MACH_LEMOTE_FL2E;

	mips_machtype = LOONGSON_MACHTYPE;

	p = म_माला(arcs_cmdline, "machtype=");
	अगर (!p) अणु
		mach_prom_init_machtype();
		वापस;
	पूर्ण
	p += म_माप("machtype=");
	म_नकलन(str, p, MACHTYPE_LEN);
	str[MACHTYPE_LEN] = '\0';
	p = म_माला(str, " ");
	अगर (p)
		*p = '\0';

	क्रम (; प्रणाली_types[machtype]; machtype++)
		अगर (म_माला(प्रणाली_types[machtype], str)) अणु
			mips_machtype = machtype;
			अवरोध;
		पूर्ण
पूर्ण
