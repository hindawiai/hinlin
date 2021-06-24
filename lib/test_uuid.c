<शैली गुरु>
/*
 * Test हालs क्रम lib/uuid.c module.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/uuid.h>

काष्ठा test_uuid_data अणु
	स्थिर अक्षर *uuid;
	guid_t le;
	uuid_t be;
पूर्ण;

अटल स्थिर काष्ठा test_uuid_data test_uuid_test_data[] = अणु
	अणु
		.uuid = "c33f4995-3701-450e-9fbf-206a2e98e576",
		.le = GUID_INIT(0xc33f4995, 0x3701, 0x450e, 0x9f, 0xbf, 0x20, 0x6a, 0x2e, 0x98, 0xe5, 0x76),
		.be = UUID_INIT(0xc33f4995, 0x3701, 0x450e, 0x9f, 0xbf, 0x20, 0x6a, 0x2e, 0x98, 0xe5, 0x76),
	पूर्ण,
	अणु
		.uuid = "64b4371c-77c1-48f9-8221-29f054fc023b",
		.le = GUID_INIT(0x64b4371c, 0x77c1, 0x48f9, 0x82, 0x21, 0x29, 0xf0, 0x54, 0xfc, 0x02, 0x3b),
		.be = UUID_INIT(0x64b4371c, 0x77c1, 0x48f9, 0x82, 0x21, 0x29, 0xf0, 0x54, 0xfc, 0x02, 0x3b),
	पूर्ण,
	अणु
		.uuid = "0cb4ddff-a545-4401-9d06-688af53e7f84",
		.le = GUID_INIT(0x0cb4ddff, 0xa545, 0x4401, 0x9d, 0x06, 0x68, 0x8a, 0xf5, 0x3e, 0x7f, 0x84),
		.be = UUID_INIT(0x0cb4ddff, 0xa545, 0x4401, 0x9d, 0x06, 0x68, 0x8a, 0xf5, 0x3e, 0x7f, 0x84),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_uuid_wrong_data[] = अणु
	"c33f4995-3701-450e-9fbf206a2e98e576 ",	/* no hyphen(s) */
	"64b4371c-77c1-48f9-8221-29f054XX023b",	/* invalid अक्षरacter(s) */
	"0cb4ddff-a545-4401-9d06-688af53e",	/* not enough data */
पूर्ण;

अटल अचिन्हित total_tests __initdata;
अटल अचिन्हित failed_tests __initdata;

अटल व्योम __init test_uuid_failed(स्थिर अक्षर *prefix, bool wrong, bool be,
				    स्थिर अक्षर *data, स्थिर अक्षर *actual)
अणु
	pr_err("%s test #%u %s %s data: '%s'\n",
	       prefix,
	       total_tests,
	       wrong ? "passed on wrong" : "failed on",
	       be ? "BE" : "LE",
	       data);
	अगर (actual && *actual)
		pr_err("%s test #%u actual data: '%s'\n",
		       prefix,
		       total_tests,
		       actual);
	failed_tests++;
पूर्ण

अटल व्योम __init test_uuid_test(स्थिर काष्ठा test_uuid_data *data)
अणु
	guid_t le;
	uuid_t be;
	अक्षर buf[48];

	/* LE */
	total_tests++;
	अगर (guid_parse(data->uuid, &le))
		test_uuid_failed("conversion", false, false, data->uuid, शून्य);

	total_tests++;
	अगर (!guid_equal(&data->le, &le)) अणु
		प्र_लिखो(buf, "%pUl", &le);
		test_uuid_failed("cmp", false, false, data->uuid, buf);
	पूर्ण

	/* BE */
	total_tests++;
	अगर (uuid_parse(data->uuid, &be))
		test_uuid_failed("conversion", false, true, data->uuid, शून्य);

	total_tests++;
	अगर (!uuid_equal(&data->be, &be)) अणु
		प्र_लिखो(buf, "%pUb", &be);
		test_uuid_failed("cmp", false, true, data->uuid, buf);
	पूर्ण
पूर्ण

अटल व्योम __init test_uuid_wrong(स्थिर अक्षर *data)
अणु
	guid_t le;
	uuid_t be;

	/* LE */
	total_tests++;
	अगर (!guid_parse(data, &le))
		test_uuid_failed("negative", true, false, data, शून्य);

	/* BE */
	total_tests++;
	अगर (!uuid_parse(data, &be))
		test_uuid_failed("negative", true, true, data, शून्य);
पूर्ण

अटल पूर्णांक __init test_uuid_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(test_uuid_test_data); i++)
		test_uuid_test(&test_uuid_test_data[i]);

	क्रम (i = 0; i < ARRAY_SIZE(test_uuid_wrong_data); i++)
		test_uuid_wrong(test_uuid_wrong_data[i]);

	अगर (failed_tests == 0)
		pr_info("all %u tests passed\n", total_tests);
	अन्यथा
		pr_err("failed %u out of %u tests\n", failed_tests, total_tests);

	वापस failed_tests ? -EINVAL : 0;
पूर्ण
module_init(test_uuid_init);

अटल व्योम __निकास test_uuid_निकास(व्योम)
अणु
	/* करो nothing */
पूर्ण
module_निकास(test_uuid_निकास);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_LICENSE("Dual BSD/GPL");
