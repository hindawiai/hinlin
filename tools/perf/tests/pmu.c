<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "parse-events.h"
#समावेश "pmu.h"
#समावेश "tests.h"
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>

/* Simulated क्रमmat definitions. */
अटल काष्ठा test_क्रमmat अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *value;
पूर्ण test_क्रमmats[] = अणु
	अणु "krava01", "config:0-1,62-63\n", पूर्ण,
	अणु "krava02", "config:10-17\n", पूर्ण,
	अणु "krava03", "config:5\n", पूर्ण,
	अणु "krava11", "config1:0,2,4,6,8,20-28\n", पूर्ण,
	अणु "krava12", "config1:63\n", पूर्ण,
	अणु "krava13", "config1:45-47\n", पूर्ण,
	अणु "krava21", "config2:0-3,10-13,20-23,30-33,40-43,50-53,60-63\n", पूर्ण,
	अणु "krava22", "config2:8,18,48,58\n", पूर्ण,
	अणु "krava23", "config2:28-29,38\n", पूर्ण,
पूर्ण;

/* Simulated users input. */
अटल काष्ठा parse_events_term test_terms[] = अणु
	अणु
		.config    = (अक्षर *) "krava01",
		.val.num   = 15,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
	अणु
		.config    = (अक्षर *) "krava02",
		.val.num   = 170,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
	अणु
		.config    = (अक्षर *) "krava03",
		.val.num   = 1,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
	अणु
		.config    = (अक्षर *) "krava11",
		.val.num   = 27,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
	अणु
		.config    = (अक्षर *) "krava12",
		.val.num   = 1,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
	अणु
		.config    = (अक्षर *) "krava13",
		.val.num   = 2,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
	अणु
		.config    = (अक्षर *) "krava21",
		.val.num   = 119,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
	अणु
		.config    = (अक्षर *) "krava22",
		.val.num   = 11,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
	अणु
		.config    = (अक्षर *) "krava23",
		.val.num   = 2,
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = PARSE_EVENTS__TERM_TYPE_USER,
	पूर्ण,
पूर्ण;

/*
 * Prepare क्रमmat directory data, exported by kernel
 * at /sys/bus/event_source/devices/<dev>/क्रमmat.
 */
अटल अक्षर *test_क्रमmat_dir_get(व्योम)
अणु
	अटल अक्षर dir[PATH_MAX];
	अचिन्हित पूर्णांक i;

	snम_लिखो(dir, PATH_MAX, "/tmp/perf-pmu-test-format-XXXXXX");
	अगर (!mkdtemp(dir))
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(test_क्रमmats); i++) अणु
		अटल अक्षर name[PATH_MAX];
		काष्ठा test_क्रमmat *क्रमmat = &test_क्रमmats[i];
		खाता *file;

		scnम_लिखो(name, PATH_MAX, "%s/%s", dir, क्रमmat->name);

		file = ख_खोलो(name, "w");
		अगर (!file)
			वापस शून्य;

		अगर (1 != ख_डालो(क्रमmat->value, म_माप(क्रमmat->value), 1, file))
			अवरोध;

		ख_बंद(file);
	पूर्ण

	वापस dir;
पूर्ण

/* Cleanup क्रमmat directory. */
अटल पूर्णांक test_क्रमmat_dir_put(अक्षर *dir)
अणु
	अक्षर buf[PATH_MAX];
	snम_लिखो(buf, PATH_MAX, "rm -f %s/*\n", dir);
	अगर (प्रणाली(buf))
		वापस -1;

	snम_लिखो(buf, PATH_MAX, "rmdir %s\n", dir);
	वापस प्रणाली(buf);
पूर्ण

अटल काष्ठा list_head *test_terms_list(व्योम)
अणु
	अटल LIST_HEAD(terms);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(test_terms); i++)
		list_add_tail(&test_terms[i].list, &terms);

	वापस &terms;
पूर्ण

पूर्णांक test__pmu(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	अक्षर *क्रमmat = test_क्रमmat_dir_get();
	LIST_HEAD(क्रमmats);
	काष्ठा list_head *terms = test_terms_list();
	पूर्णांक ret;

	अगर (!क्रमmat)
		वापस -EINVAL;

	करो अणु
		काष्ठा perf_event_attr attr;

		स_रखो(&attr, 0, माप(attr));

		ret = perf_pmu__क्रमmat_parse(क्रमmat, &क्रमmats);
		अगर (ret)
			अवरोध;

		ret = perf_pmu__config_terms("perf-pmu-test", &क्रमmats, &attr,
					     terms, false, शून्य);
		अगर (ret)
			अवरोध;

		ret = -EINVAL;

		अगर (attr.config  != 0xc00000000002a823)
			अवरोध;
		अगर (attr.config1 != 0x8000400000000145)
			अवरोध;
		अगर (attr.config2 != 0x0400000020041d07)
			अवरोध;

		ret = 0;
	पूर्ण जबतक (0);

	perf_pmu__del_क्रमmats(&क्रमmats);
	test_क्रमmat_dir_put(क्रमmat);
	वापस ret;
पूर्ण
