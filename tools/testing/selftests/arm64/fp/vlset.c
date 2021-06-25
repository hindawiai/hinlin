<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015-2019 ARM Limited.
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */
#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <getopt.h>
#समावेश <unistd.h>
#समावेश <sys/auxv.h>
#समावेश <sys/prctl.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/sigcontext.h>

अटल पूर्णांक inherit = 0;
अटल पूर्णांक no_inherit = 0;
अटल पूर्णांक क्रमce = 0;
अटल अचिन्हित दीर्घ vl;

अटल स्थिर काष्ठा option options[] = अणु
	अणु "force",	no_argument, शून्य, 'f' पूर्ण,
	अणु "inherit",	no_argument, शून्य, 'i' पूर्ण,
	अणु "max",	no_argument, शून्य, 'M' पूर्ण,
	अणु "no-inherit",	no_argument, &no_inherit, 1 पूर्ण,
	अणु "help",	no_argument, शून्य, '?' पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अक्षर स्थिर *program_name;

अटल पूर्णांक parse_options(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;
	अक्षर *rest;

	program_name = म_खोजप(argv[0], '/');
	अगर (program_name)
		++program_name;
	अन्यथा
		program_name = argv[0];

	जबतक ((c = getopt_दीर्घ(argc, argv, "Mfhi", options, शून्य)) != -1)
		चयन (c) अणु
		हाल 'M':	vl = SVE_VL_MAX; अवरोध;
		हाल 'f':	क्रमce = 1; अवरोध;
		हाल 'i':	inherit = 1; अवरोध;
		हाल 0:		अवरोध;
		शेष:	जाओ error;
		पूर्ण

	अगर (inherit && no_inherit)
		जाओ error;

	अगर (!vl) अणु
		/* vector length */
		अगर (optind >= argc)
			जाओ error;

		त्रुटि_सं = 0;
		vl = म_से_अदीर्घ(argv[optind], &rest, 0);
		अगर (*rest) अणु
			vl = अच_दीर्घ_उच्च;
			त्रुटि_सं = EINVAL;
		पूर्ण
		अगर (vl == अच_दीर्घ_उच्च && त्रुटि_सं) अणु
			ख_लिखो(मानक_त्रुटि, "%s: %s: %s\n",
				program_name, argv[optind], म_त्रुटि(त्रुटि_सं));
			जाओ error;
		पूर्ण

		++optind;
	पूर्ण

	/* command */
	अगर (optind >= argc)
		जाओ error;

	वापस 0;

error:
	ख_लिखो(मानक_त्रुटि,
		"Usage: %s [-f | --force] "
		"[-i | --inherit | --no-inherit] "
		"{-M | --max | <vector length>} "
		"<command> [<arguments> ...]\n",
		program_name);
	वापस -1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक ret = 126;	/* same as sh(1) command-not-executable error */
	दीर्घ flags;
	अक्षर *path;
	पूर्णांक t, e;

	अगर (parse_options(argc, argv))
		वापस 2;	/* same as sh(1) builtin incorrect-usage */

	अगर (vl & ~(vl & PR_SVE_VL_LEN_MASK)) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Invalid vector length %lu\n",
			program_name, vl);
		वापस 2;	/* same as sh(1) builtin incorrect-usage */
	पूर्ण

	अगर (!(getauxval(AT_HWCAP) & HWCAP_SVE)) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Scalable Vector Extension not present\n",
			program_name);

		अगर (!क्रमce)
			जाओ error;

		ख_माला_दो("Going ahead anyway (--force):  "
		      "This is a debug option.  Don't rely on it.\n",
		      मानक_त्रुटि);
	पूर्ण

	flags = PR_SVE_SET_VL_ONEXEC;
	अगर (inherit)
		flags |= PR_SVE_VL_INHERIT;

	t = prctl(PR_SVE_SET_VL, vl | flags);
	अगर (t < 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: PR_SVE_SET_VL: %s\n",
			program_name, म_त्रुटि(त्रुटि_सं));
		जाओ error;
	पूर्ण

	t = prctl(PR_SVE_GET_VL);
	अगर (t == -1) अणु
		ख_लिखो(मानक_त्रुटि, "%s: PR_SVE_GET_VL: %s\n",
			program_name, म_त्रुटि(त्रुटि_सं));
		जाओ error;
	पूर्ण
	flags = PR_SVE_VL_LEN_MASK;
	flags = t & ~flags;

	निश्चित(optind < argc);
	path = argv[optind];

	execvp(path, &argv[optind]);
	e = त्रुटि_सं;
	अगर (त्रुटि_सं == ENOENT)
		ret = 127;	/* same as sh(1) not-found error */
	ख_लिखो(मानक_त्रुटि, "%s: %s: %s\n", program_name, path, म_त्रुटि(e));

error:
	वापस ret;		/* same as sh(1) not-executable error */
पूर्ण
