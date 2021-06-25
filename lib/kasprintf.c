<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/lib/kaप्र_लिखो.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <मानकतर्क.स>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>

/* Simplअगरied aप्र_लिखो. */
अक्षर *kvaप्र_लिखो(gfp_t gfp, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	अचिन्हित पूर्णांक first, second;
	अक्षर *p;
	बहु_सूची aq;

	va_copy(aq, ap);
	first = vsnम_लिखो(शून्य, 0, fmt, aq);
	बहु_पूर्ण(aq);

	p = kदो_स्मृति_track_caller(first+1, gfp);
	अगर (!p)
		वापस शून्य;

	second = vsnम_लिखो(p, first+1, fmt, ap);
	WARN(first != second, "different return values (%u and %u) from vsnprintf(\"%s\", ...)",
	     first, second, fmt);

	वापस p;
पूर्ण
EXPORT_SYMBOL(kvaप्र_लिखो);

/*
 * If fmt contains no % (or is exactly %s), use kstrdup_स्थिर. If fmt
 * (or the sole vararg) poपूर्णांकs to rodata, we will then save a memory
 * allocation and string copy. In any हाल, the वापस value should be
 * मुक्तd using kमुक्त_स्थिर().
 */
स्थिर अक्षर *kvaप्र_लिखो_स्थिर(gfp_t gfp, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	अगर (!म_अक्षर(fmt, '%'))
		वापस kstrdup_स्थिर(fmt, gfp);
	अगर (!म_भेद(fmt, "%s"))
		वापस kstrdup_स्थिर(बहु_तर्क(ap, स्थिर अक्षर*), gfp);
	वापस kvaप्र_लिखो(gfp, fmt, ap);
पूर्ण
EXPORT_SYMBOL(kvaप्र_लिखो_स्थिर);

अक्षर *kaप्र_लिखो(gfp_t gfp, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर *p;

	बहु_शुरू(ap, fmt);
	p = kvaप्र_लिखो(gfp, fmt, ap);
	बहु_पूर्ण(ap);

	वापस p;
पूर्ण
EXPORT_SYMBOL(kaप्र_लिखो);
