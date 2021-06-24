<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Minimal BPF assembler
 *
 * Instead of libpcap high-level filter expressions, it can be quite
 * useful to define filters in low-level BPF assembler (that is kept
 * बंद to Steven McCanne and Van Jacobson's original BPF paper).
 * In particular क्रम BPF JIT implementors, JIT security auditors, or
 * just क्रम defining BPF expressions that contain extensions which are
 * not supported by compilers.
 *
 * How to get पूर्णांकo it:
 *
 * 1) पढ़ो Documentation/networking/filter.rst
 * 2) Run `bpf_यंत्र [-c] <filter-prog file>` to translate पूर्णांकo binary
 *    blob that is loadable with xt_bpf, cls_bpf et al. Note: -c will
 *    pretty prपूर्णांक a C-like स्थिरruct.
 *
 * Copyright 2013 Daniel Borkmann <borkmann@redhat.com>
 */

#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>

बाह्य व्योम bpf_यंत्र_compile(खाता *fp, bool cstyle);

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	खाता *fp = मानक_निवेश;
	bool cstyle = false;
	पूर्णांक i;

	क्रम (i = 1; i < argc; i++) अणु
		अगर (!म_भेदन("-c", argv[i], 2)) अणु
			cstyle = true;
			जारी;
		पूर्ण

		fp = ख_खोलो(argv[i], "r");
		अगर (!fp) अणु
			fp = मानक_निवेश;
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	bpf_यंत्र_compile(fp, cstyle);

	वापस 0;
पूर्ण
