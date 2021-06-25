<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <endian.h>
#समावेश <elf.h>

#समावेश "relocs.h"

व्योम die(अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	बहु_पूर्ण(ap);
	निकास(1);
पूर्ण

अटल व्योम usage(व्योम)
अणु
	die("relocs [--reloc-info|--text|--bin|--keep] vmlinux\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक show_reloc_info, as_text, as_bin, keep_relocs;
	स्थिर अक्षर *fname;
	खाता *fp;
	पूर्णांक i;
	अचिन्हित अक्षर e_ident[EI_NIDENT];

	show_reloc_info = 0;
	as_text = 0;
	as_bin = 0;
	keep_relocs = 0;
	fname = शून्य;
	क्रम (i = 1; i < argc; i++) अणु
		अक्षर *arg = argv[i];

		अगर (*arg == '-') अणु
			अगर (म_भेद(arg, "--reloc-info") == 0) अणु
				show_reloc_info = 1;
				जारी;
			पूर्ण
			अगर (म_भेद(arg, "--text") == 0) अणु
				as_text = 1;
				जारी;
			पूर्ण
			अगर (म_भेद(arg, "--bin") == 0) अणु
				as_bin = 1;
				जारी;
			पूर्ण
			अगर (म_भेद(arg, "--keep") == 0) अणु
				keep_relocs = 1;
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (!fname) अणु
			fname = arg;
			जारी;
		पूर्ण
		usage();
	पूर्ण
	अगर (!fname)
		usage();

	fp = ख_खोलो(fname, "r+");
	अगर (!fp)
		die("Cannot open %s: %s\n", fname, म_त्रुटि(त्रुटि_सं));

	अगर (ख_पढ़ो(&e_ident, 1, EI_NIDENT, fp) != EI_NIDENT)
		die("Cannot read %s: %s", fname, म_त्रुटि(त्रुटि_सं));

	शुरुआत(fp);
	अगर (e_ident[EI_CLASS] == ELFCLASS64)
		process_64(fp, as_text,  as_bin, show_reloc_info, keep_relocs);
	अन्यथा
		process_32(fp, as_text, as_bin, show_reloc_info, keep_relocs);
	ख_बंद(fp);
	वापस 0;
पूर्ण
