<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <माला.स>
#समावेश "tests.h"
#समावेश "units.h"
#समावेश "debug.h"

पूर्णांक test__unit_number__scnprपूर्णांक(काष्ठा test *t __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा अणु
		u64		 n;
		स्थिर अक्षर	*str;
	पूर्ण test[] = अणु
		अणु 1,			"1B"	पूर्ण,
		अणु 10*1024,		"10K"	पूर्ण,
		अणु 20*1024*1024,		"20M"	पूर्ण,
		अणु 30*1024*1024*1024ULL,	"30G"	पूर्ण,
		अणु 0,			"0B"	पूर्ण,
		अणु 0,			शून्य	पूर्ण,
	पूर्ण;
	अचिन्हित i = 0;

	जबतक (test[i].str) अणु
		अक्षर buf[100];

		unit_number__scnम_लिखो(buf, माप(buf), test[i].n);

		pr_debug("n %" PRIu64 ", str '%s', buf '%s'\n",
			 test[i].n, test[i].str, buf);

		अगर (म_भेद(test[i].str, buf))
			वापस TEST_FAIL;

		i++;
	पूर्ण

	वापस TEST_OK;
पूर्ण
