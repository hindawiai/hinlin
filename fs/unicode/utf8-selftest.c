<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel module क्रम testing utf-8 support.
 *
 * Copyright 2017 Collabora Ltd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/unicode.h>
#समावेश <linux/dcache.h>

#समावेश "utf8n.h"

अचिन्हित पूर्णांक failed_tests;
अचिन्हित पूर्णांक total_tests;

/* Tests will be based on this version. */
#घोषणा latest_maj 12
#घोषणा latest_min 1
#घोषणा latest_rev 0

#घोषणा _test(cond, func, line, fmt, ...) करो अणु				\
		total_tests++;						\
		अगर (!cond) अणु						\
			failed_tests++;					\
			pr_err("test %s:%d Failed: %s%s",		\
			       func, line, #cond, (fmt?":":"."));	\
			अगर (fmt)					\
				pr_err(fmt, ##__VA_ARGS__);		\
		पूर्ण							\
	पूर्ण जबतक (0)
#घोषणा test_f(cond, fmt, ...) _test(cond, __func__, __LINE__, fmt, ##__VA_ARGS__)
#घोषणा test(cond) _test(cond, __func__, __LINE__, "")

अटल स्थिर काष्ठा अणु
	/* UTF-8 strings in this vector _must_ be शून्य-terminated. */
	अचिन्हित अक्षर str[10];
	अचिन्हित अक्षर dec[10];
पूर्ण nfdi_test_data[] = अणु
	/* Trivial sequence */
	अणु
		/* "ABba" decomposes to itself */
		.str = "aBba",
		.dec = "aBba",
	पूर्ण,
	/* Simple equivalent sequences */
	अणु
               /* 'VULGAR FRACTION ONE QUARTER' cannot decompose to
                  'NUMBER 1' + 'FRACTION SLASH' + 'NUMBER 4' on
                  canonical decomposition */
               .str = अणु0xc2, 0xbc, 0x00पूर्ण,
	       .dec = अणु0xc2, 0xbc, 0x00पूर्ण,
	पूर्ण,
	अणु
		/* 'LATIN SMALL LETTER A WITH DIAERESIS' decomposes to
		   'LETTER A' + 'COMBINING DIAERESIS' */
		.str = अणु0xc3, 0xa4, 0x00पूर्ण,
		.dec = अणु0x61, 0xcc, 0x88, 0x00पूर्ण,
	पूर्ण,
	अणु
		/* 'LATIN SMALL LETTER LJ' can't decompose to
		   'LETTER L' + 'LETTER J' on canonical decomposition */
		.str = अणु0xC7, 0x89, 0x00पूर्ण,
		.dec = अणु0xC7, 0x89, 0x00पूर्ण,
	पूर्ण,
	अणु
		/* GREEK ANO TELEIA decomposes to MIDDLE DOT */
		.str = अणु0xCE, 0x87, 0x00पूर्ण,
		.dec = अणु0xC2, 0xB7, 0x00पूर्ण
	पूर्ण,
	/* Canonical ordering */
	अणु
		/* A + 'COMBINING ACUTE ACCENT' + 'COMBINING OGONEK' decomposes
		   to A + 'COMBINING OGONEK' + 'COMBINING ACUTE ACCENT' */
		.str = अणु0x41, 0xcc, 0x81, 0xcc, 0xa8, 0x0पूर्ण,
		.dec = अणु0x41, 0xcc, 0xa8, 0xcc, 0x81, 0x0पूर्ण,
	पूर्ण,
	अणु
		/* 'LATIN SMALL LETTER A WITH DIAERESIS' + 'COMBINING OGONEK'
		   decomposes to
		   'LETTER A' + 'COMBINING OGONEK' + 'COMBINING DIAERESIS' */
		.str = अणु0xc3, 0xa4, 0xCC, 0xA8, 0x00पूर्ण,

		.dec = अणु0x61, 0xCC, 0xA8, 0xcc, 0x88, 0x00पूर्ण,
	पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा अणु
	/* UTF-8 strings in this vector _must_ be शून्य-terminated. */
	अचिन्हित अक्षर str[30];
	अचिन्हित अक्षर ncf[30];
पूर्ण nfdicf_test_data[] = अणु
	/* Trivial sequences */
	अणु
		/* "ABba" folds to lowerहाल */
		.str = अणु0x41, 0x42, 0x62, 0x61, 0x00पूर्ण,
		.ncf = अणु0x61, 0x62, 0x62, 0x61, 0x00पूर्ण,
	पूर्ण,
	अणु
		/* All ASCII folds to lower-हाल */
		.str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0.1",
		.ncf = "abcdefghijklmnopqrstuvwxyz0.1",
	पूर्ण,
	अणु
		/* LATIN SMALL LETTER SHARP S folds to
		   LATIN SMALL LETTER S + LATIN SMALL LETTER S */
		.str = अणु0xc3, 0x9f, 0x00पूर्ण,
		.ncf = अणु0x73, 0x73, 0x00पूर्ण,
	पूर्ण,
	अणु
		/* LATIN CAPITAL LETTER A WITH RING ABOVE folds to
		   LATIN SMALL LETTER A + COMBINING RING ABOVE */
		.str = अणु0xC3, 0x85, 0x00पूर्ण,
		.ncf = अणु0x61, 0xcc, 0x8a, 0x00पूर्ण,
	पूर्ण,
	/* Introduced by UTF-8.0.0. */
	/* Cherokee letters are पूर्णांकeresting test-हालs because they fold
	   to upper-हाल.  Beक्रमe 8.0.0, Cherokee lowerहाल were
	   undefined, thus, the folding from LC is not stable between
	   7.0.0 -> 8.0.0, but it is from UC. */
	अणु
		/* CHEROKEE SMALL LETTER A folds to CHEROKEE LETTER A */
		.str = अणु0xea, 0xad, 0xb0, 0x00पूर्ण,
		.ncf = अणु0xe1, 0x8e, 0xa0, 0x00पूर्ण,
	पूर्ण,
	अणु
		/* CHEROKEE SMALL LETTER YE folds to CHEROKEE LETTER YE */
		.str = अणु0xe1, 0x8f, 0xb8, 0x00पूर्ण,
		.ncf = अणु0xe1, 0x8f, 0xb0, 0x00पूर्ण,
	पूर्ण,
	अणु
		/* OLD HUNGARIAN CAPITAL LETTER AMB folds to
		   OLD HUNGARIAN SMALL LETTER AMB */
		.str = अणु0xf0, 0x90, 0xb2, 0x83, 0x00पूर्ण,
		.ncf = अणु0xf0, 0x90, 0xb3, 0x83, 0x00पूर्ण,
	पूर्ण,
	/* Introduced by UTF-9.0.0. */
	अणु
		/* OSAGE CAPITAL LETTER CHA folds to
		   OSAGE SMALL LETTER CHA */
		.str = अणु0xf0, 0x90, 0x92, 0xb5, 0x00पूर्ण,
		.ncf = अणु0xf0, 0x90, 0x93, 0x9d, 0x00पूर्ण,
	पूर्ण,
	अणु
		/* LATIN CAPITAL LETTER SMALL CAPITAL I folds to
		   LATIN LETTER SMALL CAPITAL I */
		.str = अणु0xea, 0x9e, 0xae, 0x00पूर्ण,
		.ncf = अणु0xc9, 0xaa, 0x00पूर्ण,
	पूर्ण,
	/* Introduced by UTF-11.0.0. */
	अणु
		/* GEORGIAN SMALL LETTER AN folds to GEORGIAN MTAVRULI
		   CAPITAL LETTER AN */
		.str = अणु0xe1, 0xb2, 0x90, 0x00पूर्ण,
		.ncf = अणु0xe1, 0x83, 0x90, 0x00पूर्ण,
	पूर्ण
पूर्ण;

अटल व्योम check_utf8_nfdi(व्योम)
अणु
	पूर्णांक i;
	काष्ठा utf8cursor u8c;
	स्थिर काष्ठा utf8data *data;

	data = utf8nfdi(UNICODE_AGE(latest_maj, latest_min, latest_rev));
	अगर (!data) अणु
		pr_err("%s: Unable to load utf8-%d.%d.%d. Skipping.\n",
		       __func__, latest_maj, latest_min, latest_rev);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(nfdi_test_data); i++) अणु
		पूर्णांक len = म_माप(nfdi_test_data[i].str);
		पूर्णांक nlen = म_माप(nfdi_test_data[i].dec);
		पूर्णांक j = 0;
		अचिन्हित अक्षर c;

		test((utf8len(data, nfdi_test_data[i].str) == nlen));
		test((utf8nlen(data, nfdi_test_data[i].str, len) == nlen));

		अगर (utf8cursor(&u8c, data, nfdi_test_data[i].str) < 0)
			pr_err("can't create cursor\n");

		जबतक ((c = utf8byte(&u8c)) > 0) अणु
			test_f((c == nfdi_test_data[i].dec[j]),
			       "Unexpected byte 0x%x should be 0x%x\n",
			       c, nfdi_test_data[i].dec[j]);
			j++;
		पूर्ण

		test((j == nlen));
	पूर्ण
पूर्ण

अटल व्योम check_utf8_nfdicf(व्योम)
अणु
	पूर्णांक i;
	काष्ठा utf8cursor u8c;
	स्थिर काष्ठा utf8data *data;

	data = utf8nfdicf(UNICODE_AGE(latest_maj, latest_min, latest_rev));
	अगर (!data) अणु
		pr_err("%s: Unable to load utf8-%d.%d.%d. Skipping.\n",
		       __func__, latest_maj, latest_min, latest_rev);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(nfdicf_test_data); i++) अणु
		पूर्णांक len = म_माप(nfdicf_test_data[i].str);
		पूर्णांक nlen = म_माप(nfdicf_test_data[i].ncf);
		पूर्णांक j = 0;
		अचिन्हित अक्षर c;

		test((utf8len(data, nfdicf_test_data[i].str) == nlen));
		test((utf8nlen(data, nfdicf_test_data[i].str, len) == nlen));

		अगर (utf8cursor(&u8c, data, nfdicf_test_data[i].str) < 0)
			pr_err("can't create cursor\n");

		जबतक ((c = utf8byte(&u8c)) > 0) अणु
			test_f((c == nfdicf_test_data[i].ncf[j]),
			       "Unexpected byte 0x%x should be 0x%x\n",
			       c, nfdicf_test_data[i].ncf[j]);
			j++;
		पूर्ण

		test((j == nlen));
	पूर्ण
पूर्ण

अटल व्योम check_utf8_comparisons(व्योम)
अणु
	पूर्णांक i;
	काष्ठा unicode_map *table = utf8_load("12.1.0");

	अगर (IS_ERR(table)) अणु
		pr_err("%s: Unable to load utf8 %d.%d.%d. Skipping.\n",
		       __func__, latest_maj, latest_min, latest_rev);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(nfdi_test_data); i++) अणु
		स्थिर काष्ठा qstr s1 = अणु.name = nfdi_test_data[i].str,
					.len = माप(nfdi_test_data[i].str)पूर्ण;
		स्थिर काष्ठा qstr s2 = अणु.name = nfdi_test_data[i].dec,
					.len = माप(nfdi_test_data[i].dec)पूर्ण;

		test_f(!utf8_म_भेदन(table, &s1, &s2),
		       "%s %s comparison mismatch\n", s1.name, s2.name);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(nfdicf_test_data); i++) अणु
		स्थिर काष्ठा qstr s1 = अणु.name = nfdicf_test_data[i].str,
					.len = माप(nfdicf_test_data[i].str)पूर्ण;
		स्थिर काष्ठा qstr s2 = अणु.name = nfdicf_test_data[i].ncf,
					.len = माप(nfdicf_test_data[i].ncf)पूर्ण;

		test_f(!utf8_strnहालcmp(table, &s1, &s2),
		       "%s %s comparison mismatch\n", s1.name, s2.name);
	पूर्ण

	utf8_unload(table);
पूर्ण

अटल व्योम check_supported_versions(व्योम)
अणु
	/* Unicode 7.0.0 should be supported. */
	test(utf8version_is_supported(7, 0, 0));

	/* Unicode 9.0.0 should be supported. */
	test(utf8version_is_supported(9, 0, 0));

	/* Unicode 1x.0.0 (the latest version) should be supported. */
	test(utf8version_is_supported(latest_maj, latest_min, latest_rev));

	/* Next versions करोn't exist. */
	test(!utf8version_is_supported(13, 0, 0));
	test(!utf8version_is_supported(0, 0, 0));
	test(!utf8version_is_supported(-1, -1, -1));
पूर्ण

अटल पूर्णांक __init init_test_ucd(व्योम)
अणु
	failed_tests = 0;
	total_tests = 0;

	check_supported_versions();
	check_utf8_nfdi();
	check_utf8_nfdicf();
	check_utf8_comparisons();

	अगर (!failed_tests)
		pr_info("All %u tests passed\n", total_tests);
	अन्यथा
		pr_err("%u out of %u tests failed\n", failed_tests,
		       total_tests);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_test_ucd(व्योम)
अणु
पूर्ण

module_init(init_test_ucd);
module_निकास(निकास_test_ucd);

MODULE_AUTHOR("Gabriel Krisman Bertazi <krisman@collabora.co.uk>");
MODULE_LICENSE("GPL");
