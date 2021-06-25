<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <regex.h>

#समावेश "../../../util/debug.h"
#समावेश "../../../util/header.h"

अटल अंतरभूत व्योम
cpuid(अचिन्हित पूर्णांक op, अचिन्हित पूर्णांक *a, अचिन्हित पूर्णांक *b, अचिन्हित पूर्णांक *c,
      अचिन्हित पूर्णांक *d)
अणु
	__यंत्र__ __अस्थिर__ (".byte 0x53\n\tcpuid\n\t"
			      "movl %%ebx, %%esi\n\t.byte 0x5b"
			: "=a" (*a),
			"=S" (*b),
			"=c" (*c),
			"=d" (*d)
			: "a" (op));
पूर्ण

अटल पूर्णांक
__get_cpuid(अक्षर *buffer, माप_प्रकार sz, स्थिर अक्षर *fmt)
अणु
	अचिन्हित पूर्णांक a, b, c, d, lvl;
	पूर्णांक family = -1, model = -1, step = -1;
	पूर्णांक nb;
	अक्षर venकरोr[16];

	cpuid(0, &lvl, &b, &c, &d);
	म_नकलन(&venकरोr[0], (अक्षर *)(&b), 4);
	म_नकलन(&venकरोr[4], (अक्षर *)(&d), 4);
	म_नकलन(&venकरोr[8], (अक्षर *)(&c), 4);
	venकरोr[12] = '\0';

	अगर (lvl >= 1) अणु
		cpuid(1, &a, &b, &c, &d);

		family = (a >> 8) & 0xf;  /* bits 11 - 8 */
		model  = (a >> 4) & 0xf;  /* Bits  7 - 4 */
		step   = a & 0xf;

		/* extended family */
		अगर (family == 0xf)
			family += (a >> 20) & 0xff;

		/* extended model */
		अगर (family >= 0x6)
			model += ((a >> 16) & 0xf) << 4;
	पूर्ण
	nb = scnम_लिखो(buffer, sz, fmt, venकरोr, family, model, step);

	/* look क्रम end marker to ensure the entire data fit */
	अगर (म_अक्षर(buffer, '$')) अणु
		buffer[nb-1] = '\0';
		वापस 0;
	पूर्ण
	वापस ENOBUFS;
पूर्ण

पूर्णांक
get_cpuid(अक्षर *buffer, माप_प्रकार sz)
अणु
	वापस __get_cpuid(buffer, sz, "%s,%u,%u,%u$");
पूर्ण

अक्षर *
get_cpuid_str(काष्ठा perf_pmu *pmu __maybe_unused)
अणु
	अक्षर *buf = दो_स्मृति(128);

	अगर (buf && __get_cpuid(buf, 128, "%s-%u-%X-%X$") < 0) अणु
		मुक्त(buf);
		वापस शून्य;
	पूर्ण
	वापस buf;
पूर्ण

/* Full CPUID क्रमmat क्रम x86 is venकरोr-family-model-stepping */
अटल bool is_full_cpuid(स्थिर अक्षर *id)
अणु
	स्थिर अक्षर *पंचांगp = id;
	पूर्णांक count = 0;

	जबतक ((पंचांगp = म_अक्षर(पंचांगp, '-')) != शून्य) अणु
		count++;
		पंचांगp++;
	पूर्ण

	अगर (count == 3)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक म_भेद_cpuid_str(स्थिर अक्षर *mapcpuid, स्थिर अक्षर *id)
अणु
	regex_t re;
	regmatch_t pmatch[1];
	पूर्णांक match;
	bool full_mapcpuid = is_full_cpuid(mapcpuid);
	bool full_cpuid = is_full_cpuid(id);

	/*
	 * Full CPUID क्रमmat is required to identअगरy a platक्रमm.
	 * Error out अगर the cpuid string is incomplete.
	 */
	अगर (full_mapcpuid && !full_cpuid) अणु
		pr_info("Invalid CPUID %s. Full CPUID is required, "
			"vendor-family-model-stepping\n", id);
		वापस 1;
	पूर्ण

	अगर (regcomp(&re, mapcpuid, REG_EXTENDED) != 0) अणु
		/* Warn unable to generate match particular string. */
		pr_info("Invalid regular expression %s\n", mapcpuid);
		वापस 1;
	पूर्ण

	match = !regexec(&re, id, 1, pmatch, 0);
	regमुक्त(&re);
	अगर (match) अणु
		माप_प्रकार match_len = (pmatch[0].rm_eo - pmatch[0].rm_so);
		माप_प्रकार cpuid_len;

		/* If the full CPUID क्रमmat isn't required,
		 * ignoring the stepping.
		 */
		अगर (!full_mapcpuid && full_cpuid)
			cpuid_len = म_खोजप(id, '-') - id;
		अन्यथा
			cpuid_len = म_माप(id);

		/* Verअगरy the entire string matched. */
		अगर (match_len == cpuid_len)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
