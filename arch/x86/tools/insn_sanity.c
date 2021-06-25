<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * x86 decoder sanity test - based on test_get_insn.c
 *
 * Copyright (C) IBM Corporation, 2009
 * Copyright (C) Hitachi, Ltd., 2011
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <यंत्र/insn.h>
#समावेश <inat.c>
#समावेश <insn.c>

/*
 * Test of inकाष्ठाion analysis against tampering.
 * Feed अक्रमom binary to inकाष्ठाion decoder and ensure not to
 * access out-of-inकाष्ठाion-buffer.
 */

#घोषणा DEFAULT_MAX_ITER	10000
#घोषणा INSN_NOP 0x90

अटल स्थिर अक्षर	*prog;		/* Program name */
अटल पूर्णांक		verbose;	/* Verbosity */
अटल पूर्णांक		x86_64;		/* x86-64 bit mode flag */
अटल अचिन्हित पूर्णांक	seed;		/* Ranकरोm seed */
अटल अचिन्हित दीर्घ	iter_start;	/* Start of iteration number */
अटल अचिन्हित दीर्घ	iter_end = DEFAULT_MAX_ITER;	/* End of iteration number */
अटल खाता		*input_file;	/* Input file name */

अटल व्योम usage(स्थिर अक्षर *err)
अणु
	अगर (err)
		ख_लिखो(मानक_त्रुटि, "%s: Error: %s\n\n", prog, err);
	ख_लिखो(मानक_त्रुटि, "Usage: %s [-y|-n|-v] [-s seed[,no]] [-m max] [-i input]\n", prog);
	ख_लिखो(मानक_त्रुटि, "\t-y	64bit mode\n");
	ख_लिखो(मानक_त्रुटि, "\t-n	32bit mode\n");
	ख_लिखो(मानक_त्रुटि, "\t-v	Verbosity(-vv dumps any decoded result)\n");
	ख_लिखो(मानक_त्रुटि, "\t-s	Give a random seed (and iteration number)\n");
	ख_लिखो(मानक_त्रुटि, "\t-m	Give a maximum iteration number\n");
	ख_लिखो(मानक_त्रुटि, "\t-i	Give an input file with decoded binary\n");
	निकास(1);
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

अटल व्योम dump_stream(खाता *fp, स्थिर अक्षर *msg, अचिन्हित दीर्घ nr_iter,
			अचिन्हित अक्षर *insn_buff, काष्ठा insn *insn)
अणु
	पूर्णांक i;

	ख_लिखो(fp, "%s:\n", msg);

	dump_insn(fp, insn);

	ख_लिखो(fp, "You can reproduce this with below command(s);\n");

	/* Input a decoded inकाष्ठाion sequence directly */
	ख_लिखो(fp, " $ echo ");
	क्रम (i = 0; i < MAX_INSN_SIZE; i++)
		ख_लिखो(fp, " %02x", insn_buff[i]);
	ख_लिखो(fp, " | %s -i -\n", prog);

	अगर (!input_file) अणु
		ख_लिखो(fp, "Or \n");
		/* Give a seed and iteration number */
		ख_लिखो(fp, " $ %s -s 0x%x,%lu\n", prog, seed, nr_iter);
	पूर्ण
पूर्ण

अटल व्योम init_अक्रमom_seed(व्योम)
अणु
	पूर्णांक fd;

	fd = खोलो("/dev/urandom", O_RDONLY);
	अगर (fd < 0)
		जाओ fail;

	अगर (पढ़ो(fd, &seed, माप(seed)) != माप(seed))
		जाओ fail;

	बंद(fd);
	वापस;
fail:
	usage("Failed to open /dev/urandom");
पूर्ण

/* Read given inकाष्ठाion sequence from the input file */
अटल पूर्णांक पढ़ो_next_insn(अचिन्हित अक्षर *insn_buff)
अणु
	अक्षर buf[256]  = "", *पंचांगp;
	पूर्णांक i;

	पंचांगp = ख_माला_लो(buf, ARRAY_SIZE(buf), input_file);
	अगर (पंचांगp == शून्य || ख_पूर्ण(input_file))
		वापस 0;

	क्रम (i = 0; i < MAX_INSN_SIZE; i++) अणु
		insn_buff[i] = (अचिन्हित अक्षर)म_से_अदीर्घ(पंचांगp, &पंचांगp, 16);
		अगर (*पंचांगp != ' ')
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक generate_insn(अचिन्हित अक्षर *insn_buff)
अणु
	पूर्णांक i;

	अगर (input_file)
		वापस पढ़ो_next_insn(insn_buff);

	/* Fills buffer with अक्रमom binary up to MAX_INSN_SIZE */
	क्रम (i = 0; i < MAX_INSN_SIZE - 1; i += 2)
		*(अचिन्हित लघु *)(&insn_buff[i]) = अक्रमom() & 0xffff;

	जबतक (i < MAX_INSN_SIZE)
		insn_buff[i++] = अक्रमom() & 0xff;

	वापस i;
पूर्ण

अटल व्योम parse_args(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;
	अक्षर *पंचांगp = शून्य;
	पूर्णांक set_seed = 0;

	prog = argv[0];
	जबतक ((c = getopt(argc, argv, "ynvs:m:i:")) != -1) अणु
		चयन (c) अणु
		हाल 'y':
			x86_64 = 1;
			अवरोध;
		हाल 'n':
			x86_64 = 0;
			अवरोध;
		हाल 'v':
			verbose++;
			अवरोध;
		हाल 'i':
			अगर (म_भेद("-", optarg) == 0)
				input_file = मानक_निवेश;
			अन्यथा
				input_file = ख_खोलो(optarg, "r");
			अगर (!input_file)
				usage("Failed to open input file");
			अवरोध;
		हाल 's':
			seed = (अचिन्हित पूर्णांक)म_से_अदीर्घ(optarg, &पंचांगp, 0);
			अगर (*पंचांगp == ',') अणु
				optarg = पंचांगp + 1;
				iter_start = म_से_अदीर्घ(optarg, &पंचांगp, 0);
			पूर्ण
			अगर (*पंचांगp != '\0' || पंचांगp == optarg)
				usage("Failed to parse seed");
			set_seed = 1;
			अवरोध;
		हाल 'm':
			iter_end = म_से_अदीर्घ(optarg, &पंचांगp, 0);
			अगर (*पंचांगp != '\0' || पंचांगp == optarg)
				usage("Failed to parse max_iter");
			अवरोध;
		शेष:
			usage(शून्य);
		पूर्ण
	पूर्ण

	/* Check errors */
	अगर (iter_end < iter_start)
		usage("Max iteration number must be bigger than iter-num");

	अगर (set_seed && input_file)
		usage("Don't use input file (-i) with random seed (-s)");

	/* Initialize अक्रमom seed */
	अगर (!input_file) अणु
		अगर (!set_seed)	/* No seed is given */
			init_अक्रमom_seed();
		बेक्रम(seed);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक insns = 0, ret;
	काष्ठा insn insn;
	पूर्णांक errors = 0;
	अचिन्हित दीर्घ i;
	अचिन्हित अक्षर insn_buff[MAX_INSN_SIZE * 2];

	parse_args(argc, argv);

	/* Prepare stop bytes with NOPs */
	स_रखो(insn_buff + MAX_INSN_SIZE, INSN_NOP, MAX_INSN_SIZE);

	क्रम (i = 0; i < iter_end; i++) अणु
		अगर (generate_insn(insn_buff) <= 0)
			अवरोध;

		अगर (i < iter_start)	/* Skip to given iteration number */
			जारी;

		/* Decode an inकाष्ठाion */
		ret = insn_decode(&insn, insn_buff, माप(insn_buff),
				  x86_64 ? INSN_MODE_64 : INSN_MODE_32);

		अगर (insn.next_byte <= insn.kaddr ||
		    insn.kaddr + MAX_INSN_SIZE < insn.next_byte) अणु
			/* Access out-of-range memory */
			dump_stream(मानक_त्रुटि, "Error: Found an access violation", i, insn_buff, &insn);
			errors++;
		पूर्ण अन्यथा अगर (verbose && ret < 0)
			dump_stream(मानक_निकास, "Info: Found an undecodable input", i, insn_buff, &insn);
		अन्यथा अगर (verbose >= 2)
			dump_insn(मानक_निकास, &insn);
		insns++;
	पूर्ण

	ख_लिखो((errors) ? मानक_त्रुटि : मानक_निकास,
		"%s: %s: decoded and checked %d %s instructions with %d errors (seed:0x%x)\n",
		prog,
		(errors) ? "Failure" : "Success",
		insns,
		(input_file) ? "given" : "random",
		errors,
		seed);

	वापस errors ? 1 : 0;
पूर्ण
