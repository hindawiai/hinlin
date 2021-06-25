<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <bpf/btf.h>
#समावेश "bpf/libbpf_internal.h"

अटल पूर्णांक duration = 0;

अटल व्योम validate_mask(पूर्णांक हाल_nr, स्थिर अक्षर *exp, bool *mask, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; exp[i]; i++) अणु
		अगर (exp[i] == '1') अणु
			अगर (CHECK(i + 1 > n, "mask_short",
				  "case #%d: mask too short, got n=%d, need at least %d\n",
				  हाल_nr, n, i + 1))
				वापस;
			CHECK(!mask[i], "cpu_not_set",
			      "case #%d: mask differs, expected cpu#%d SET\n",
			      हाल_nr, i);
		पूर्ण अन्यथा अणु
			CHECK(i < n && mask[i], "cpu_set",
			      "case #%d: mask differs, expected cpu#%d UNSET\n",
			      हाल_nr, i);
		पूर्ण
	पूर्ण
	CHECK(i < n, "mask_long",
	      "case #%d: mask too long, got n=%d, expected at most %d\n",
	      हाल_nr, n, i);
पूर्ण

अटल काष्ठा अणु
	स्थिर अक्षर *cpu_mask;
	स्थिर अक्षर *expect;
	bool fails;
पूर्ण test_हालs[] = अणु
	अणु "0\n", "1", false पूर्ण,
	अणु "0,2\n", "101", false पूर्ण,
	अणु "0-2\n", "111", false पूर्ण,
	अणु "0-2,3-4\n", "11111", false पूर्ण,
	अणु "0", "1", false पूर्ण,
	अणु "0-2", "111", false पूर्ण,
	अणु "0,2", "101", false पूर्ण,
	अणु "0,1-3", "1111", false पूर्ण,
	अणु "0,1,2,3", "1111", false पूर्ण,
	अणु "0,2-3,5", "101101", false पूर्ण,
	अणु "3-3", "0001", false पूर्ण,
	अणु "2-4,6,9-10", "00111010011", false पूर्ण,
	/* failure हालs */
	अणु "", "", true पूर्ण,
	अणु "0-", "", true पूर्ण,
	अणु "0 ", "", true पूर्ण,
	अणु "0_1", "", true पूर्ण,
	अणु "1-0", "", true पूर्ण,
	अणु "-1", "", true पूर्ण,
पूर्ण;

व्योम test_cpu_mask()
अणु
	पूर्णांक i, err, n;
	bool *mask;

	क्रम (i = 0; i < ARRAY_SIZE(test_हालs); i++) अणु
		mask = शून्य;
		err = parse_cpu_mask_str(test_हालs[i].cpu_mask, &mask, &n);
		अगर (test_हालs[i].fails) अणु
			CHECK(!err, "should_fail",
			      "case #%d: parsing should fail!\n", i + 1);
		पूर्ण अन्यथा अणु
			अगर (CHECK(err, "parse_err",
				  "case #%d: cpu mask parsing failed: %d\n",
				  i + 1, err))
				जारी;
			validate_mask(i + 1, test_हालs[i].expect, mask, n);
		पूर्ण
		मुक्त(mask);
	पूर्ण
पूर्ण
