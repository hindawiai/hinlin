<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) IBM Corporation, 2009
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>

#घोषणा unlikely(cond) (cond)

#समावेश <यंत्र/insn.h>
#समावेश <inat.c>
#समावेश <insn.c>

/*
 * Test of inकाष्ठाion analysis in general and insn_get_length() in
 * particular.  See अगर insn_get_length() and the disassembler agree
 * on the length of each inकाष्ठाion in an elf disassembly.
 *
 * Usage: objdump -d a.out | awk -f objdump_reक्रमmat.awk | ./insn_decoder_test
 */

स्थिर अक्षर *prog;
अटल पूर्णांक verbose;
अटल पूर्णांक x86_64;

अटल व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: objdump -d a.out | awk -f objdump_reformat.awk"
		" | %s [-y|-n] [-v]\n", prog);
	ख_लिखो(मानक_त्रुटि, "\t-y	64bit mode\n");
	ख_लिखो(मानक_त्रुटि, "\t-n	32bit mode\n");
	ख_लिखो(मानक_त्रुटि, "\t-v	verbose mode\n");
	निकास(1);
पूर्ण

अटल व्योम malक्रमmed_line(स्थिर अक्षर *line, पूर्णांक line_nr)
अणु
	ख_लिखो(मानक_त्रुटि, "%s: error: malformed line %d:\n%s",
		prog, line_nr, line);
	निकास(3);
पूर्ण

अटल व्योम pr_warn(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	ख_लिखो(मानक_त्रुटि, "%s: warning: ", prog);
	बहु_शुरू(ap, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

अटल व्योम dump_field(खाता *fp, स्थिर अक्षर *name, स्थिर अक्षर *indent,
		       काष्ठा insn_field *field)
अणु
	ख_लिखो(fp, "%s.%s = {\n", indent, name);
	ख_लिखो(fp, "%s\t.value = %d, bytes[] = {%x, %x, %x, %x},\n",
		indent, field->value, field->bytes[0], field->bytes[1],
		field->bytes[2], field->bytes[3]);
	ख_लिखो(fp, "%s\t.got = %d, .nbytes = %d},\n", indent,
		field->got, field->nbytes);
पूर्ण

अटल व्योम dump_insn(खाता *fp, काष्ठा insn *insn)
अणु
	ख_लिखो(fp, "Instruction = {\n");
	dump_field(fp, "prefixes", "\t",	&insn->prefixes);
	dump_field(fp, "rex_prefix", "\t",	&insn->rex_prefix);
	dump_field(fp, "vex_prefix", "\t",	&insn->vex_prefix);
	dump_field(fp, "opcode", "\t",		&insn->opcode);
	dump_field(fp, "modrm", "\t",		&insn->modrm);
	dump_field(fp, "sib", "\t",		&insn->sib);
	dump_field(fp, "displacement", "\t",	&insn->displacement);
	dump_field(fp, "immediate1", "\t",	&insn->immediate1);
	dump_field(fp, "immediate2", "\t",	&insn->immediate2);
	ख_लिखो(fp, "\t.attr = %x, .opnd_bytes = %d, .addr_bytes = %d,\n",
		insn->attr, insn->opnd_bytes, insn->addr_bytes);
	ख_लिखो(fp, "\t.length = %d, .x86_64 = %d, .kaddr = %p}\n",
		insn->length, insn->x86_64, insn->kaddr);
पूर्ण

अटल व्योम parse_args(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;
	prog = argv[0];
	जबतक ((c = getopt(argc, argv, "ynv")) != -1) अणु
		चयन (c) अणु
		हाल 'y':
			x86_64 = 1;
			अवरोध;
		हाल 'n':
			x86_64 = 0;
			अवरोध;
		हाल 'v':
			verbose = 1;
			अवरोध;
		शेष:
			usage();
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा बफ_मानE 256

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर line[बफ_मानE], sym[बफ_मानE] = "<unknown>";
	अचिन्हित अक्षर insn_buff[16];
	काष्ठा insn insn;
	पूर्णांक insns = 0;
	पूर्णांक warnings = 0;

	parse_args(argc, argv);

	जबतक (ख_माला_लो(line, बफ_मानE, मानक_निवेश)) अणु
		अक्षर copy[बफ_मानE], *s, *tab1, *tab2;
		पूर्णांक nb = 0, ret;
		अचिन्हित पूर्णांक b;

		अगर (line[0] == '<') अणु
			/* Symbol line */
			म_नकल(sym, line);
			जारी;
		पूर्ण

		insns++;
		स_रखो(insn_buff, 0, 16);
		म_नकल(copy, line);
		tab1 = म_अक्षर(copy, '\t');
		अगर (!tab1)
			malक्रमmed_line(line, insns);
		s = tab1 + 1;
		s += म_अखोज(s, " ");
		tab2 = म_अक्षर(s, '\t');
		अगर (!tab2)
			malक्रमmed_line(line, insns);
		*tab2 = '\0';	/* Characters beyond tab2 aren't examined */
		जबतक (s < tab2) अणु
			अगर (माला_पूछो(s, "%x", &b) == 1) अणु
				insn_buff[nb++] = (अचिन्हित अक्षर) b;
				s += 3;
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण

		/* Decode an inकाष्ठाion */
		ret = insn_decode(&insn, insn_buff, माप(insn_buff),
				  x86_64 ? INSN_MODE_64 : INSN_MODE_32);

		अगर (ret < 0 || insn.length != nb) अणु
			warnings++;
			pr_warn("Found an x86 instruction decoder bug, "
				"please report this.\n", sym);
			pr_warn("%s", line);
			pr_warn("objdump says %d bytes, but insn_get_length() "
				"says %d\n", nb, insn.length);
			अगर (verbose)
				dump_insn(मानक_त्रुटि, &insn);
		पूर्ण
	पूर्ण
	अगर (warnings)
		pr_warn("Decoded and checked %d instructions with %d "
			"failures\n", insns, warnings);
	अन्यथा
		ख_लिखो(मानक_निकास, "%s: success: Decoded and checked %d"
			" instructions\n", prog, insns);
	वापस 0;
पूर्ण
