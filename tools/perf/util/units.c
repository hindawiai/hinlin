<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "units.h"
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/समय64.h>

अचिन्हित दीर्घ parse_tag_value(स्थिर अक्षर *str, काष्ठा parse_tag *tags)
अणु
	काष्ठा parse_tag *i = tags;

	जबतक (i->tag) अणु
		अक्षर *s = म_अक्षर(str, i->tag);

		अगर (s) अणु
			अचिन्हित दीर्घ पूर्णांक value;
			अक्षर *endptr;

			value = म_से_अदीर्घ(str, &endptr, 10);
			अगर (s != endptr)
				अवरोध;

			अगर (value > अच_दीर्घ_उच्च / i->mult)
				अवरोध;
			value *= i->mult;
			वापस value;
		पूर्ण
		i++;
	पूर्ण

	वापस (अचिन्हित दीर्घ) -1;
पूर्ण

द्विगुन convert_unit_द्विगुन(द्विगुन value, अक्षर *unit)
अणु
	*unit = ' ';

	अगर (value > 1000.0) अणु
		value /= 1000.0;
		*unit = 'K';
	पूर्ण

	अगर (value > 1000.0) अणु
		value /= 1000.0;
		*unit = 'M';
	पूर्ण

	अगर (value > 1000.0) अणु
		value /= 1000.0;
		*unit = 'G';
	पूर्ण

	वापस value;
पूर्ण

अचिन्हित दीर्घ convert_unit(अचिन्हित दीर्घ value, अक्षर *unit)
अणु
	द्विगुन v = convert_unit_द्विगुन((द्विगुन)value, unit);

	वापस (अचिन्हित दीर्घ)v;
पूर्ण

पूर्णांक unit_number__scnम_लिखो(अक्षर *buf, माप_प्रकार size, u64 n)
अणु
	अक्षर unit[4] = "BKMG";
	पूर्णांक i = 0;

	जबतक (((n / 1024) > 1) && (i < 3)) अणु
		n /= 1024;
		i++;
	पूर्ण

	वापस scnम_लिखो(buf, size, "%" PRIu64 "%c", n, unit[i]);
पूर्ण
