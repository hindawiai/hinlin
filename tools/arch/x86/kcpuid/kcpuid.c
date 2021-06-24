<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <getopt.h>

#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))

प्रकार अचिन्हित पूर्णांक u32;
प्रकार अचिन्हित दीर्घ दीर्घ u64;

अक्षर *def_csv = "/usr/share/misc/cpuid.csv";
अक्षर *user_csv;


/* Cover both single-bit flag and multiple-bits fields */
काष्ठा bits_desc अणु
	/* start and end bits */
	पूर्णांक start, end;
	/* 0 or 1 क्रम 1-bit flag */
	पूर्णांक value;
	अक्षर simp[32];
	अक्षर detail[256];
पूर्ण;

/* descriptor info क्रम eax/ebx/ecx/edx */
काष्ठा reg_desc अणु
	/* number of valid entries */
	पूर्णांक nr;
	काष्ठा bits_desc descs[32];
पूर्ण;

क्रमागत अणु
	R_EAX = 0,
	R_EBX,
	R_ECX,
	R_EDX,
	NR_REGS
पूर्ण;

काष्ठा subleaf अणु
	u32 index;
	u32 sub;
	u32 eax, ebx, ecx, edx;
	काष्ठा reg_desc info[NR_REGS];
पूर्ण;

/* Represent one leaf (basic or extended) */
काष्ठा cpuid_func अणु
	/*
	 * Array of subleafs क्रम this func, अगर there is no subleafs
	 * then the leafs[0] is the मुख्य leaf
	 */
	काष्ठा subleaf *leafs;
	पूर्णांक nr;
पूर्ण;

काष्ठा cpuid_range अणु
	/* array of मुख्य leafs */
	काष्ठा cpuid_func *funcs;
	/* number of valid leafs */
	पूर्णांक nr;
	bool is_ext;
पूर्ण;

/*
 * basic:  basic functions range: [0... ]
 * ext:    extended functions range: [0x80000000... ]
 */
काष्ठा cpuid_range *leafs_basic, *leafs_ext;

अटल पूर्णांक num_leafs;
अटल bool is_amd;
अटल bool show_details;
अटल bool show_raw;
अटल bool show_flags_only = true;
अटल u32 user_index = 0xFFFFFFFF;
अटल u32 user_sub = 0xFFFFFFFF;
अटल पूर्णांक flines;

अटल अंतरभूत व्योम cpuid(u32 *eax, u32 *ebx, u32 *ecx, u32 *edx)
अणु
	/* ecx is often an input as well as an output. */
	यंत्र अस्थिर("cpuid"
	    : "=a" (*eax),
	      "=b" (*ebx),
	      "=c" (*ecx),
	      "=d" (*edx)
	    : "0" (*eax), "2" (*ecx));
पूर्ण

अटल अंतरभूत bool has_subleafs(u32 f)
अणु
	अगर (f == 0x7 || f == 0xd)
		वापस true;

	अगर (is_amd) अणु
		अगर (f == 0x8000001d)
			वापस true;
		वापस false;
	पूर्ण

	चयन (f) अणु
	हाल 0x4:
	हाल 0xb:
	हाल 0xf:
	हाल 0x10:
	हाल 0x14:
	हाल 0x18:
	हाल 0x1f:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम leaf_prपूर्णांक_raw(काष्ठा subleaf *leaf)
अणु
	अगर (has_subleafs(leaf->index)) अणु
		अगर (leaf->sub == 0)
			म_लिखो("0x%08x: subleafs:\n", leaf->index);

		म_लिखो(" %2d: EAX=0x%08x, EBX=0x%08x, ECX=0x%08x, EDX=0x%08x\n",
			leaf->sub, leaf->eax, leaf->ebx, leaf->ecx, leaf->edx);
	पूर्ण अन्यथा अणु
		म_लिखो("0x%08x: EAX=0x%08x, EBX=0x%08x, ECX=0x%08x, EDX=0x%08x\n",
			leaf->index, leaf->eax, leaf->ebx, leaf->ecx, leaf->edx);
	पूर्ण
पूर्ण

/* Return true is the input eax/ebx/ecx/edx are all zero */
अटल bool cpuid_store(काष्ठा cpuid_range *range, u32 f, पूर्णांक subleaf,
			u32 a, u32 b, u32 c, u32 d)
अणु
	काष्ठा cpuid_func *func;
	काष्ठा subleaf *leaf;
	पूर्णांक s = 0;

	अगर (a == 0 && b == 0 && c == 0 && d == 0)
		वापस true;

	/*
	 * Cut off venकरोr-prefix from CPUID function as we're using it as an
	 * index पूर्णांकo ->funcs.
	 */
	func = &range->funcs[f & 0xffff];

	अगर (!func->leafs) अणु
		func->leafs = दो_स्मृति(माप(काष्ठा subleaf));
		अगर (!func->leafs)
			लिखो_त्रुटि("malloc func leaf");

		func->nr = 1;
	पूर्ण अन्यथा अणु
		s = func->nr;
		func->leafs = पुनः_स्मृति(func->leafs, (s + 1) * माप(*leaf));
		अगर (!func->leafs)
			लिखो_त्रुटि("realloc f->leafs");

		func->nr++;
	पूर्ण

	leaf = &func->leafs[s];

	leaf->index = f;
	leaf->sub = subleaf;
	leaf->eax = a;
	leaf->ebx = b;
	leaf->ecx = c;
	leaf->edx = d;

	वापस false;
पूर्ण

अटल व्योम raw_dump_range(काष्ठा cpuid_range *range)
अणु
	u32 f;
	पूर्णांक i;

	म_लिखो("%s Leafs :\n", range->is_ext ? "Extended" : "Basic");
	म_लिखो("================\n");

	क्रम (f = 0; (पूर्णांक)f < range->nr; f++) अणु
		काष्ठा cpuid_func *func = &range->funcs[f];
		u32 index = f;

		अगर (range->is_ext)
			index += 0x80000000;

		/* Skip leaf without valid items */
		अगर (!func->nr)
			जारी;

		/* First item is the मुख्य leaf, followed by all subleafs */
		क्रम (i = 0; i < func->nr; i++)
			leaf_prपूर्णांक_raw(&func->leafs[i]);
	पूर्ण
पूर्ण

#घोषणा MAX_SUBLEAF_NUM		32
काष्ठा cpuid_range *setup_cpuid_range(u32 input_eax)
अणु
	u32 max_func, idx_func;
	पूर्णांक subleaf;
	काष्ठा cpuid_range *range;
	u32 eax, ebx, ecx, edx;
	u32 f = input_eax;
	पूर्णांक max_subleaf;
	bool allzero;

	eax = input_eax;
	ebx = ecx = edx = 0;

	cpuid(&eax, &ebx, &ecx, &edx);
	max_func = eax;
	idx_func = (max_func & 0xffff) + 1;

	range = दो_स्मृति(माप(काष्ठा cpuid_range));
	अगर (!range)
		लिखो_त्रुटि("malloc range");

	अगर (input_eax & 0x80000000)
		range->is_ext = true;
	अन्यथा
		range->is_ext = false;

	range->funcs = दो_स्मृति(माप(काष्ठा cpuid_func) * idx_func);
	अगर (!range->funcs)
		लिखो_त्रुटि("malloc range->funcs");

	range->nr = idx_func;
	स_रखो(range->funcs, 0, माप(काष्ठा cpuid_func) * idx_func);

	क्रम (; f <= max_func; f++) अणु
		eax = f;
		subleaf = ecx = 0;

		cpuid(&eax, &ebx, &ecx, &edx);
		allzero = cpuid_store(range, f, subleaf, eax, ebx, ecx, edx);
		अगर (allzero)
			जारी;
		num_leafs++;

		अगर (!has_subleafs(f))
			जारी;

		max_subleaf = MAX_SUBLEAF_NUM;

		/*
		 * Some can provide the exact number of subleafs,
		 * others have to be tried (0xf)
		 */
		अगर (f == 0x7 || f == 0x14 || f == 0x17 || f == 0x18)
			max_subleaf = (eax & 0xff) + 1;

		अगर (f == 0xb)
			max_subleaf = 2;

		क्रम (subleaf = 1; subleaf < max_subleaf; subleaf++) अणु
			eax = f;
			ecx = subleaf;

			cpuid(&eax, &ebx, &ecx, &edx);
			allzero = cpuid_store(range, f, subleaf,
						eax, ebx, ecx, edx);
			अगर (allzero)
				जारी;
			num_leafs++;
		पूर्ण

	पूर्ण

	वापस range;
पूर्ण

/*
 * The basic row क्रमmat क्रम cpuid.csv  is
 *	LEAF,SUBLEAF,रेजिस्टर_name,bits,लघु name,दीर्घ description
 *
 * like:
 *	0,    0,  EAX,   31:0, max_basic_leafs,  Max input value क्रम supported subleafs
 *	1,    0,  ECX,      0, sse3,  Streaming SIMD Extensions 3(SSE3)
 */
अटल पूर्णांक parse_line(अक्षर *line)
अणु
	अक्षर *str;
	पूर्णांक i;
	काष्ठा cpuid_range *range;
	काष्ठा cpuid_func *func;
	काष्ठा subleaf *leaf;
	u32 index;
	u32 sub;
	अक्षर buffer[512];
	अक्षर *buf;
	/*
	 * Tokens:
	 *  1. leaf
	 *  2. subleaf
	 *  3. रेजिस्टर
	 *  4. bits
	 *  5. लघु name
	 *  6. दीर्घ detail
	 */
	अक्षर *tokens[6];
	काष्ठा reg_desc *reg;
	काष्ठा bits_desc *bdesc;
	पूर्णांक reg_index;
	अक्षर *start, *end;

	/* Skip comments and शून्य line */
	अगर (line[0] == '#' || line[0] == '\n')
		वापस 0;

	म_नकलन(buffer, line, 511);
	buffer[511] = 0;
	str = buffer;
	क्रम (i = 0; i < 5; i++) अणु
		tokens[i] = म_मोहर(str, ",");
		अगर (!tokens[i])
			जाओ err_निकास;
		str = शून्य;
	पूर्ण
	tokens[5] = म_मोहर(str, "\n");
	अगर (!tokens[5])
		जाओ err_निकास;

	/* index/मुख्य-leaf */
	index = म_से_अदीर्घl(tokens[0], शून्य, 0);

	अगर (index & 0x80000000)
		range = leafs_ext;
	अन्यथा
		range = leafs_basic;

	index &= 0x7FFFFFFF;
	/* Skip line parsing क्रम non-existing indexes */
	अगर ((पूर्णांक)index >= range->nr)
		वापस -1;

	func = &range->funcs[index];

	/* Return अगर the index has no valid item on this platक्रमm */
	अगर (!func->nr)
		वापस 0;

	/* subleaf */
	sub = म_से_अदीर्घ(tokens[1], शून्य, 0);
	अगर ((पूर्णांक)sub > func->nr)
		वापस -1;

	leaf = &func->leafs[sub];
	buf = tokens[2];

	अगर (strहालstr(buf, "EAX"))
		reg_index = R_EAX;
	अन्यथा अगर (strहालstr(buf, "EBX"))
		reg_index = R_EBX;
	अन्यथा अगर (strहालstr(buf, "ECX"))
		reg_index = R_ECX;
	अन्यथा अगर (strहालstr(buf, "EDX"))
		reg_index = R_EDX;
	अन्यथा
		जाओ err_निकास;

	reg = &leaf->info[reg_index];
	bdesc = &reg->descs[reg->nr++];

	/* bit flag or bits field */
	buf = tokens[3];

	end = म_मोहर(buf, ":");
	bdesc->end = म_से_अदीर्घ(end, शून्य, 0);
	bdesc->start = bdesc->end;

	/* start != शून्य means it is bit fields */
	start = म_मोहर(शून्य, ":");
	अगर (start)
		bdesc->start = म_से_अदीर्घ(start, शून्य, 0);

	म_नकल(bdesc->simp, tokens[4]);
	म_नकल(bdesc->detail, tokens[5]);
	वापस 0;

err_निकास:
	म_लिखो("Warning: wrong line format:\n");
	म_लिखो("\tline[%d]: %s\n", flines, line);
	वापस -1;
पूर्ण

/* Parse csv file, and स्थिरruct the array of all leafs and subleafs */
अटल व्योम parse_text(व्योम)
अणु
	खाता *file;
	अक्षर *filename, *line = शून्य;
	माप_प्रकार len = 0;
	पूर्णांक ret;

	अगर (show_raw)
		वापस;

	filename = user_csv ? user_csv : def_csv;
	file = ख_खोलो(filename, "r");
	अगर (!file) अणु
		/* Fallback to a csv in the same dir */
		file = ख_खोलो("./cpuid.csv", "r");
	पूर्ण

	अगर (!file) अणु
		म_लिखो("Fail to open '%s'\n", filename);
		वापस;
	पूर्ण

	जबतक (1) अणु
		ret = getline(&line, &len, file);
		flines++;
		अगर (ret > 0)
			parse_line(line);

		अगर (ख_पूर्ण(file))
			अवरोध;
	पूर्ण

	ख_बंद(file);
पूर्ण


/* Decode every eax/ebx/ecx/edx */
अटल व्योम decode_bits(u32 value, काष्ठा reg_desc *rdesc)
अणु
	काष्ठा bits_desc *bdesc;
	पूर्णांक start, end, i;
	u32 mask;

	क्रम (i = 0; i < rdesc->nr; i++) अणु
		bdesc = &rdesc->descs[i];

		start = bdesc->start;
		end = bdesc->end;
		अगर (start == end) अणु
			/* single bit flag */
			अगर (value & (1 << start))
				म_लिखो("\t%-20s %s%s\n",
					bdesc->simp,
					show_details ? "-" : "",
					show_details ? bdesc->detail : ""
					);
		पूर्ण अन्यथा अणु
			/* bit fields */
			अगर (show_flags_only)
				जारी;

			mask = ((u64)1 << (end - start + 1)) - 1;
			म_लिखो("\t%-20s\t: 0x%-8x\t%s%s\n",
					bdesc->simp,
					(value >> start) & mask,
					show_details ? "-" : "",
					show_details ? bdesc->detail : ""
					);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम show_leaf(काष्ठा subleaf *leaf)
अणु
	अगर (!leaf)
		वापस;

	अगर (show_raw)
		leaf_prपूर्णांक_raw(leaf);

	decode_bits(leaf->eax, &leaf->info[R_EAX]);
	decode_bits(leaf->ebx, &leaf->info[R_EBX]);
	decode_bits(leaf->ecx, &leaf->info[R_ECX]);
	decode_bits(leaf->edx, &leaf->info[R_EDX]);
पूर्ण

अटल व्योम show_func(काष्ठा cpuid_func *func)
अणु
	पूर्णांक i;

	अगर (!func)
		वापस;

	क्रम (i = 0; i < func->nr; i++)
		show_leaf(&func->leafs[i]);
पूर्ण

अटल व्योम show_range(काष्ठा cpuid_range *range)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < range->nr; i++)
		show_func(&range->funcs[i]);
पूर्ण

अटल अंतरभूत काष्ठा cpuid_func *index_to_func(u32 index)
अणु
	काष्ठा cpuid_range *range;

	range = (index & 0x80000000) ? leafs_ext : leafs_basic;
	index &= 0x7FFFFFFF;

	अगर (((index & 0xFFFF) + 1) > (u32)range->nr) अणु
		म_लिखो("ERR: invalid input index (0x%x)\n", index);
		वापस शून्य;
	पूर्ण
	वापस &range->funcs[index];
पूर्ण

अटल व्योम show_info(व्योम)
अणु
	काष्ठा cpuid_func *func;

	अगर (show_raw) अणु
		/* Show all of the raw output of 'cpuid' instr */
		raw_dump_range(leafs_basic);
		raw_dump_range(leafs_ext);
		वापस;
	पूर्ण

	अगर (user_index != 0xFFFFFFFF) अणु
		/* Only show specअगरic leaf/subleaf info */
		func = index_to_func(user_index);
		अगर (!func)
			वापस;

		/* Dump the raw data also */
		show_raw = true;

		अगर (user_sub != 0xFFFFFFFF) अणु
			अगर (user_sub + 1 <= (u32)func->nr) अणु
				show_leaf(&func->leafs[user_sub]);
				वापस;
			पूर्ण

			म_लिखो("ERR: invalid input subleaf (0x%x)\n", user_sub);
		पूर्ण

		show_func(func);
		वापस;
	पूर्ण

	म_लिखो("CPU features:\n=============\n\n");
	show_range(leafs_basic);
	show_range(leafs_ext);
पूर्ण

अटल व्योम setup_platक्रमm_cpuid(व्योम)
अणु
	 u32 eax, ebx, ecx, edx;

	/* Check venकरोr */
	eax = ebx = ecx = edx = 0;
	cpuid(&eax, &ebx, &ecx, &edx);

	/* "htuA" */
	अगर (ebx == 0x68747541)
		is_amd = true;

	/* Setup leafs क्रम the basic and extended range */
	leafs_basic = setup_cpuid_range(0x0);
	leafs_ext = setup_cpuid_range(0x80000000);
पूर्ण

अटल व्योम usage(व्योम)
अणु
	म_लिखो("kcpuid [-abdfhr] [-l leaf] [-s subleaf]\n"
		"\t-a|--all             Show both bit flags and complex bit fields info\n"
		"\t-b|--bitflags        Show boolean flags only\n"
		"\t-d|--detail          Show details of the flag/fields (default)\n"
		"\t-f|--flags           Specify the cpuid csv file\n"
		"\t-h|--help            Show usage info\n"
		"\t-l|--leaf=index      Specify the leaf you want to check\n"
		"\t-r|--raw             Show raw cpuid data\n"
		"\t-s|--subleaf=sub     Specify the subleaf you want to check\n"
	);
पूर्ण

अटल काष्ठा option opts[] = अणु
	अणु "all", no_argument, शून्य, 'a' पूर्ण,		/* show both bit flags and fields */
	अणु "bitflags", no_argument, शून्य, 'b' पूर्ण,		/* only show bit flags, शेष on */
	अणु "detail", no_argument, शून्य, 'd' पूर्ण,		/* show detail descriptions */
	अणु "file", required_argument, शून्य, 'f' },	/* use user's cpuid file */
	अणु "help", no_argument, शून्य, 'h'पूर्ण,		/* show usage */
	अणु "leaf", required_argument, शून्य, 'l'पूर्ण,	/* only check a specअगरic leaf */
	अणु "raw", no_argument, शून्य, 'r'पूर्ण,		/* show raw CPUID leaf data */
	अणु "subleaf", required_argument, शून्य, 's'पूर्ण,	/* check a specअगरic subleaf */
	अणु शून्य, 0, शून्य, 0 पूर्ण
पूर्ण;

अटल पूर्णांक parse_options(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक c;

	जबतक ((c = getopt_दीर्घ(argc, argv, "abdf:hl:rs:",
					opts, शून्य)) != -1)
		चयन (c) अणु
		हाल 'a':
			show_flags_only = false;
			अवरोध;
		हाल 'b':
			show_flags_only = true;
			अवरोध;
		हाल 'd':
			show_details = true;
			अवरोध;
		हाल 'f':
			user_csv = optarg;
			अवरोध;
		हाल 'h':
			usage();
			निकास(1);
			अवरोध;
		हाल 'l':
			/* मुख्य leaf */
			user_index = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'r':
			show_raw = true;
			अवरोध;
		हाल 's':
			/* subleaf */
			user_sub = म_से_अदीर्घ(optarg, शून्य, 0);
			अवरोध;
		शेष:
			म_लिखो("%s: Invalid option '%c'\n", argv[0], optopt);
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Do 4 things in turn:
 * 1. Parse user options
 * 2. Parse and store all the CPUID leaf data supported on this platक्रमm
 * 2. Parse the csv file, जबतक skipping leafs which are not available
 *    on this platक्रमm
 * 3. Prपूर्णांक leafs info based on user options
 */
पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (parse_options(argc, argv))
		वापस -1;

	/* Setup the cpuid leafs of current platक्रमm */
	setup_platक्रमm_cpuid();

	/* Read and parse the 'cpuid.csv' */
	parse_text();

	show_info();
	वापस 0;
पूर्ण
