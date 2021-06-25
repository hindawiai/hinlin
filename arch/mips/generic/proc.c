<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/of.h>

#समावेश <यंत्र/bootinfo.h>

अक्षर *प्रणाली_type;

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	स्थिर अक्षर *str;
	पूर्णांक err;

	अगर (प्रणाली_type)
		वापस प्रणाली_type;

	err = of_property_पढ़ो_string(of_root, "model", &str);
	अगर (!err)
		वापस str;

	err = of_property_पढ़ो_string_index(of_root, "compatible", 0, &str);
	अगर (!err)
		वापस str;

	वापस "Unknown";
पूर्ण
