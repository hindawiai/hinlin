<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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
	die("relocs [--abs-syms|--abs-relocs|--reloc-info|--text|--realmode]" \
	    " vmlinux\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक show_असलolute_syms, show_असलolute_relocs, show_reloc_info;
	पूर्णांक as_text, use_real_mode;
	स्थिर अक्षर *fname;
	खाता *fp;
	पूर्णांक i;
	अचिन्हित अक्षर e_ident[EI_NIDENT];

	show_असलolute_syms = 0;
	show_असलolute_relocs = 0;
	show_reloc_info = 0;
	as_text = 0;
	use_real_mode = 0;
	fname = शून्य;
	क्रम (i = 1; i < argc; i++) अणु
		अक्षर *arg = argv[i];
		अगर (*arg == '-') अणु
			अगर (म_भेद(arg, "--abs-syms") == 0) अणु
				show_असलolute_syms = 1;
				जारी;
			पूर्ण
			अगर (म_भेद(arg, "--abs-relocs") == 0) अणु
				show_असलolute_relocs = 1;
				जारी;
			पूर्ण
			अगर (म_भेद(arg, "--reloc-info") == 0) अणु
				show_reloc_info = 1;
				जारी;
			पूर्ण
			अगर (म_भेद(arg, "--text") == 0) अणु
				as_text = 1;
				जारी;
			पूर्ण
			अगर (म_भेद(arg, "--realmode") == 0) अणु
				use_real_mode = 1;
				जारी;
			पूर्ण
		पूर्ण
		अन्यथा अगर (!fname) अणु
			fname = arg;
			जारी;
		पूर्ण
		usage();
	पूर्ण
	अगर (!fname) अणु
		usage();
	पूर्ण
	fp = ख_खोलो(fname, "r");
	अगर (!fp) अणु
		die("Cannot open %s: %s\n", fname, म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (ख_पढ़ो(&e_ident, 1, EI_NIDENT, fp) != EI_NIDENT) अणु
		die("Cannot read %s: %s", fname, म_त्रुटि(त्रुटि_सं));
	पूर्ण
	शुरुआत(fp);
	अगर (e_ident[EI_CLASS] == ELFCLASS64)
		process_64(fp, use_real_mode, as_text,
			   show_असलolute_syms, show_असलolute_relocs,
			   show_reloc_info);
	अन्यथा
		process_32(fp, use_real_mode, as_text,
			   show_असलolute_syms, show_असलolute_relocs,
			   show_reloc_info);
	ख_बंद(fp);
	वापस 0;
पूर्ण
