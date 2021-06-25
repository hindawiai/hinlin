<शैली गुरु>
/*
 * Aic7xxx SCSI host adapter firmware assembler
 *
 * Copyright (c) 1997, 1998, 2000, 2001 Justin T. Gibbs.
 * Copyright (c) 2001, 2002 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aicयंत्र/aicयंत्र.c#23 $
 *
 * $FreeBSD$
 */
#समावेश <sys/types.h>
#समावेश <sys/mman.h>

#समावेश <प्रकार.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <regex.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sysनिकासs.h>
#समावेश <unistd.h>

#अगर linux
#समावेश <endian.h>
#अन्यथा
#समावेश <machine/endian.h>
#पूर्ण_अगर

#समावेश "aicasm.h"
#समावेश "aicasm_symbol.h"
#समावेश "aicasm_insformat.h"

प्रकार काष्ठा patch अणु
	STAILQ_ENTRY(patch) links;
	पूर्णांक		patch_func;
	u_पूर्णांक		begin;
	u_पूर्णांक		skip_instr;
	u_पूर्णांक		skip_patch;
पूर्ण patch_t;

STAILQ_HEAD(patch_list, patch) patches;

अटल व्योम usage(व्योम);
अटल व्योम back_patch(व्योम);
अटल व्योम output_code(व्योम);
अटल व्योम output_listing(अक्षर *अगरilename);
अटल व्योम dump_scope(scope_t *scope);
अटल व्योम emit_patch(scope_t *scope, पूर्णांक patch);
अटल पूर्णांक check_patch(patch_t **start_patch, पूर्णांक start_instr,
		       पूर्णांक *skip_addr, पूर्णांक *func_vals);

काष्ठा path_list search_path;
पूर्णांक includes_search_curdir;
अक्षर *appname;
अक्षर *stock_include_file;
खाता *ofile;
अक्षर *ofilename;
अक्षर *regfilename;
खाता *regfile;
अक्षर *listfilename;
खाता *listfile;
अक्षर *regdiagfilename;
खाता *regdiagfile;
पूर्णांक   src_mode;
पूर्णांक   dst_mode;

अटल STAILQ_HEAD(,inकाष्ठाion) seq_program;
काष्ठा cs_tailq cs_tailq;
काष्ठा scope_list scope_stack;
symlist_t patch_functions;

#अगर DEBUG
बाह्य पूर्णांक yy_flex_debug;
बाह्य पूर्णांक mm_flex_debug;
बाह्य पूर्णांक yydebug;
बाह्य पूर्णांक mmdebug;
#पूर्ण_अगर
बाह्य खाता *yyin;
बाह्य पूर्णांक yyparse(व्योम);

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[]);

पूर्णांक
मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	बाह्य अक्षर *optarg;
	बाह्य पूर्णांक optind;
	पूर्णांक  ch;
	पूर्णांक  retval;
	अक्षर *inputfilename;
	scope_t *sentinal;

	STAILQ_INIT(&patches);
	SLIST_INIT(&search_path);
	STAILQ_INIT(&seq_program);
	TAILQ_INIT(&cs_tailq);
	SLIST_INIT(&scope_stack);

	/* Set Sentinal scope node */
	sentinal = scope_alloc();
	sentinal->type = SCOPE_ROOT;
	
	includes_search_curdir = 1;
	appname = *argv;
	regfile = शून्य;
	listfile = शून्य;
#अगर DEBUG
	yy_flex_debug = 0;
	mm_flex_debug = 0;
	yydebug = 0;
	mmdebug = 0;
#पूर्ण_अगर
	जबतक ((ch = getopt(argc, argv, "d:i:l:n:o:p:r:I:")) != -1) अणु
		चयन(ch) अणु
		हाल 'd':
#अगर DEBUG
			अगर (म_भेद(optarg, "s") == 0) अणु
				yy_flex_debug = 1;
				mm_flex_debug = 1;
			पूर्ण अन्यथा अगर (म_भेद(optarg, "p") == 0) अणु
				yydebug = 1;
				mmdebug = 1;
			पूर्ण अन्यथा अणु
				ख_लिखो(मानक_त्रुटि, "%s: -d Requires either an "
					"'s' or 'p' argument\n", appname);
				usage();
			पूर्ण
#अन्यथा
			stop("-d: Assembler not built with debugging "
			     "information", EX_SOFTWARE);
#पूर्ण_अगर
			अवरोध;
		हाल 'i':
			stock_include_file = optarg;
			अवरोध;
		हाल 'l':
			/* Create a program listing */
			अगर ((listfile = ख_खोलो(optarg, "w")) == शून्य) अणु
				लिखो_त्रुटि(optarg);
				stop(शून्य, EX_CANTCREAT);
			पूर्ण
			listfilename = optarg;
			अवरोध;
		हाल 'n':
			/* Don't complain about the -noमानक_निवेशc directrive */
			अगर (म_भेद(optarg, "ostdinc")) अणु
				ख_लिखो(मानक_त्रुटि, "%s: Unknown option -%c%s\n",
					appname, ch, optarg);
				usage();
				/* NOTREACHED */
			पूर्ण
			अवरोध;
		हाल 'o':
			अगर ((ofile = ख_खोलो(optarg, "w")) == शून्य) अणु
				लिखो_त्रुटि(optarg);
				stop(शून्य, EX_CANTCREAT);
			पूर्ण
			ofilename = optarg;
			अवरोध;
		हाल 'p':
			/* Create Register Diagnostic "printing" Functions */
			अगर ((regdiagfile = ख_खोलो(optarg, "w")) == शून्य) अणु
				लिखो_त्रुटि(optarg);
				stop(शून्य, EX_CANTCREAT);
			पूर्ण
			regdiagfilename = optarg;
			अवरोध;
		हाल 'r':
			अगर ((regfile = ख_खोलो(optarg, "w")) == शून्य) अणु
				लिखो_त्रुटि(optarg);
				stop(शून्य, EX_CANTCREAT);
			पूर्ण
			regfilename = optarg;
			अवरोध;
		हाल 'I':
		अणु
			path_entry_t include_dir;

			अगर (म_भेद(optarg, "-") == 0) अणु
				अगर (includes_search_curdir == 0) अणु
					ख_लिखो(मानक_त्रुटि, "%s: Warning - '-I-' "
							"specified multiple "
							"times\n", appname);
				पूर्ण
				includes_search_curdir = 0;
				क्रम (include_dir = SLIST_FIRST(&search_path);
				     include_dir != शून्य;
				     include_dir = SLIST_NEXT(include_dir,
							      links))
					/*
					 * All entries beक्रमe a '-I-' only
					 * apply to includes specअगरied with
					 * quotes instead of "<>".
					 */
					include_dir->quoted_includes_only = 1;
			पूर्ण अन्यथा अणु
				include_dir =
				    (path_entry_t)दो_स्मृति(माप(*include_dir));
				अगर (include_dir == शून्य) अणु
					लिखो_त्रुटि(optarg);
					stop(शून्य, EX_OSERR);
				पूर्ण
				include_dir->directory = strdup(optarg);
				अगर (include_dir->directory == शून्य) अणु
					लिखो_त्रुटि(optarg);
					stop(शून्य, EX_OSERR);
				पूर्ण
				include_dir->quoted_includes_only = 0;
				SLIST_INSERT_HEAD(&search_path, include_dir,
						  links);
			पूर्ण
			अवरोध;
		पूर्ण
		हाल '?':
		शेष:
			usage();
			/* NOTREACHED */
		पूर्ण
	पूर्ण
	argc -= optind;
	argv += optind;

	अगर (argc != 1) अणु
		ख_लिखो(मानक_त्रुटि, "%s: No input file specified\n", appname);
		usage();
		/* NOTREACHED */
	पूर्ण

	अगर (regdiagfile != शून्य
	 && (regfile == शून्य || stock_include_file == शून्य)) अणु
		ख_लिखो(मानक_त्रुटि,
			"%s: The -p option requires the -r and -i options.\n",
			appname);
		usage();
		/* NOTREACHED */
	पूर्ण
	symtable_खोलो();
	inputfilename = *argv;
	include_file(*argv, SOURCE_खाता);
	retval = yyparse();
	अगर (retval == 0) अणु
		अगर (SLIST_FIRST(&scope_stack) == शून्य
		 || SLIST_FIRST(&scope_stack)->type != SCOPE_ROOT) अणु
			stop("Unterminated conditional expression", EX_DATAERR);
			/* NOTREACHED */
		पूर्ण

		/* Process ouपंचांगost scope */
		process_scope(SLIST_FIRST(&scope_stack));
		/*
		 * Decend the tree of scopes and insert/emit
		 * patches as appropriate.  We perक्रमm a depth first
		 * tranversal, recursively handling each scope.
		 */
		/* start at the root scope */
		dump_scope(SLIST_FIRST(&scope_stack));

		/* Patch up क्रमward jump addresses */
		back_patch();

		अगर (ofile != शून्य)
			output_code();
		अगर (regfile != शून्य)
			symtable_dump(regfile, regdiagfile);
		अगर (listfile != शून्य)
			output_listing(inputfilename);
	पूर्ण

	stop(शून्य, 0);
	/* NOTREACHED */
	वापस (0);
पूर्ण

अटल व्योम
usage()
अणु

	(व्योम)ख_लिखो(मानक_त्रुटि,
"usage: %-16s [-nostdinc] [-I-] [-I directory] [-o output_file]\n"
"	[-r register_output_file [-p register_diag_file -i includefile]]\n"
"	[-l program_list_file]\n"
"	input_file\n", appname);
	निकास(EX_USAGE);
पूर्ण

अटल व्योम
back_patch()
अणु
	काष्ठा inकाष्ठाion *cur_instr;

	क्रम (cur_instr = STAILQ_FIRST(&seq_program);
	     cur_instr != शून्य;
	     cur_instr = STAILQ_NEXT(cur_instr, links)) अणु
		अगर (cur_instr->patch_label != शून्य) अणु
			काष्ठा ins_क्रमmat3 *f3_instr;
			u_पूर्णांक address;

			अगर (cur_instr->patch_label->type != LABEL) अणु
				अक्षर buf[255];

				snम_लिखो(buf, माप(buf),
					 "Undefined label %s",
					 cur_instr->patch_label->name);
				stop(buf, EX_DATAERR);
				/* NOTREACHED */
			पूर्ण
			f3_instr = &cur_instr->क्रमmat.क्रमmat3;
			address = f3_instr->address;
			address += cur_instr->patch_label->info.linfo->address;
			f3_instr->address = address;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
output_code()
अणु
	काष्ठा inकाष्ठाion *cur_instr;
	patch_t *cur_patch;
	critical_section_t *cs;
	symbol_node_t *cur_node;
	पूर्णांक instrcount;

	instrcount = 0;
	ख_लिखो(ofile,
"/*\n"
" * DO NOT EDIT - This file is automatically generated\n"
" *		 from the following source files:\n"
" *\n"
"%s */\n", versions);

	ख_लिखो(ofile, "static const uint8_t seqprog[] = {\n");
	क्रम (cur_instr = STAILQ_FIRST(&seq_program);
	     cur_instr != शून्य;
	     cur_instr = STAILQ_NEXT(cur_instr, links)) अणु

		ख_लिखो(ofile, "%s\t0x%02x, 0x%02x, 0x%02x, 0x%02x",
			cur_instr == STAILQ_FIRST(&seq_program) ? "" : ",\n",
#अगर_घोषित __LITTLE_ENDIAN
			cur_instr->क्रमmat.bytes[0],
			cur_instr->क्रमmat.bytes[1],
			cur_instr->क्रमmat.bytes[2],
			cur_instr->क्रमmat.bytes[3]);
#अन्यथा
			cur_instr->क्रमmat.bytes[3],
			cur_instr->क्रमmat.bytes[2],
			cur_instr->क्रमmat.bytes[1],
			cur_instr->क्रमmat.bytes[0]);
#पूर्ण_अगर
		instrcount++;
	पूर्ण
	ख_लिखो(ofile, "\n};\n\n");

	अगर (patch_arg_list == शून्य)
		stop("Patch argument list not defined",
		     EX_DATAERR);

	/*
	 *  Output patch inक्रमmation.  Patch functions first.
	 */
	ख_लिखो(ofile,
"typedef int %spatch_func_t (%s);\n", prefix, patch_arg_list);

	क्रम (cur_node = SLIST_FIRST(&patch_functions);
	     cur_node != शून्य;
	     cur_node = SLIST_NEXT(cur_node,links)) अणु
		ख_लिखो(ofile,
"static %spatch_func_t %spatch%d_func;\n"
"\n"
"static int\n"
"%spatch%d_func(%s)\n"
"{\n"
"	return (%s);\n"
"}\n\n",
			prefix,
			prefix,
			cur_node->symbol->info.condinfo->func_num,
			prefix,
			cur_node->symbol->info.condinfo->func_num,
			patch_arg_list,
			cur_node->symbol->name);
	पूर्ण

	ख_लिखो(ofile,
"static const struct patch {\n"
"	%spatch_func_t		*patch_func;\n"
"	uint32_t		 begin		:10,\n"
"				 skip_instr	:10,\n"
"				 skip_patch	:12;\n"
"} patches[] = {\n", prefix);

	क्रम (cur_patch = STAILQ_FIRST(&patches);
	     cur_patch != शून्य;
	     cur_patch = STAILQ_NEXT(cur_patch,links)) अणु
		ख_लिखो(ofile, "%s\t{ %spatch%d_func, %d, %d, %d }",
			cur_patch == STAILQ_FIRST(&patches) ? "" : ",\n",
			prefix,
			cur_patch->patch_func, cur_patch->begin,
			cur_patch->skip_instr, cur_patch->skip_patch);
	पूर्ण

	ख_लिखो(ofile, "\n};\n\n");

	ख_लिखो(ofile,
"static const struct cs {\n"
"	uint16_t	begin;\n"
"	uint16_t	end;\n"
"} critical_sections[] = {\n");

	क्रम (cs = TAILQ_FIRST(&cs_tailq);
	     cs != शून्य;
	     cs = TAILQ_NEXT(cs, links)) अणु
		ख_लिखो(ofile, "%s\t{ %d, %d }",
			cs == TAILQ_FIRST(&cs_tailq) ? "" : ",\n",
			cs->begin_addr, cs->end_addr);
	पूर्ण

	ख_लिखो(ofile, "\n};\n\n");

	ख_लिखो(ofile,
	"#define NUM_CRITICAL_SECTIONS ARRAY_SIZE(critical_sections)\n");

	ख_लिखो(मानक_त्रुटि, "%s: %d instructions used\n", appname, instrcount);
पूर्ण

अटल व्योम
dump_scope(scope_t *scope)
अणु
	scope_t *cur_scope;

	/*
	 * Emit the first patch क्रम this scope
	 */
	emit_patch(scope, 0);

	/*
	 * Dump each scope within this one.
	 */
	cur_scope = TAILQ_FIRST(&scope->inner_scope);

	जबतक (cur_scope != शून्य) अणु

		dump_scope(cur_scope);

		cur_scope = TAILQ_NEXT(cur_scope, scope_links);
	पूर्ण

	/*
	 * Emit the second, closing, patch क्रम this scope
	 */
	emit_patch(scope, 1);
पूर्ण

व्योम
emit_patch(scope_t *scope, पूर्णांक patch)
अणु
	patch_info_t *pinfo;
	patch_t *new_patch;

	pinfo = &scope->patches[patch];

	अगर (pinfo->skip_instr == 0)
		/* No-Op patch */
		वापस;

	new_patch = (patch_t *)दो_स्मृति(माप(*new_patch));

	अगर (new_patch == शून्य)
		stop("Could not malloc patch structure", EX_OSERR);

	स_रखो(new_patch, 0, माप(*new_patch));

	अगर (patch == 0) अणु
		new_patch->patch_func = scope->func_num;
		new_patch->begin = scope->begin_addr;
	पूर्ण अन्यथा अणु
		new_patch->patch_func = 0;
		new_patch->begin = scope->end_addr;
	पूर्ण
	new_patch->skip_instr = pinfo->skip_instr;
	new_patch->skip_patch = pinfo->skip_patch;
	STAILQ_INSERT_TAIL(&patches, new_patch, links);
पूर्ण

व्योम
output_listing(अक्षर *अगरilename)
अणु
	अक्षर buf[1024];
	खाता *अगरile;
	काष्ठा inकाष्ठाion *cur_instr;
	patch_t *cur_patch;
	symbol_node_t *cur_func;
	पूर्णांक *func_values;
	पूर्णांक instrcount;
	पूर्णांक instrptr;
	पूर्णांक line;
	पूर्णांक func_count;
	पूर्णांक skip_addr;

	instrcount = 0;
	instrptr = 0;
	line = 1;
	skip_addr = 0;
	अगर ((अगरile = ख_खोलो(अगरilename, "r")) == शून्य) अणु
		लिखो_त्रुटि(अगरilename);
		stop(शून्य, EX_DATAERR);
	पूर्ण

	/*
	 * Determine which options to apply to this listing.
	 */
	क्रम (func_count = 0, cur_func = SLIST_FIRST(&patch_functions);
	    cur_func != शून्य;
	    cur_func = SLIST_NEXT(cur_func, links))
		func_count++;

	func_values = शून्य;
	अगर (func_count != 0) अणु
		func_values = (पूर्णांक *)दो_स्मृति(func_count * माप(पूर्णांक));

		अगर (func_values == शून्य)
			stop("Could not malloc", EX_OSERR);
		
		func_values[0] = 0; /* FALSE func */
		func_count--;

		/*
		 * Ask the user to fill in the वापस values क्रम
		 * the rest of the functions.
		 */
		
		
		क्रम (cur_func = SLIST_FIRST(&patch_functions);
		     cur_func != शून्य && SLIST_NEXT(cur_func, links) != शून्य;
		     cur_func = SLIST_NEXT(cur_func, links), func_count--) अणु
			पूर्णांक input;
			
			ख_लिखो(मानक_निकास, "\n(%s)\n", cur_func->symbol->name);
			ख_लिखो(मानक_निकास,
				"Enter the return value for "
				"this expression[T/F]:");

			जबतक (1) अणु

				input = अक्षर_लो();
				input = बड़े(input);

				अगर (input == 'T') अणु
					func_values[func_count] = 1;
					अवरोध;
				पूर्ण अन्यथा अगर (input == 'F') अणु
					func_values[func_count] = 0;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (isatty(fileno(मानक_निवेश)) == 0)
				अक्षर_दो(input);
		पूर्ण
		ख_लिखो(मानक_निकास, "\nThanks!\n");
	पूर्ण

	/* Now output the listing */
	cur_patch = STAILQ_FIRST(&patches);
	क्रम (cur_instr = STAILQ_FIRST(&seq_program);
	     cur_instr != शून्य;
	     cur_instr = STAILQ_NEXT(cur_instr, links), instrcount++) अणु

		अगर (check_patch(&cur_patch, instrcount,
				&skip_addr, func_values) == 0) अणु
			/* Don't count this inकाष्ठाion as it is in a patch
			 * that was हटाओd.
			 */
                        जारी;
		पूर्ण

		जबतक (line < cur_instr->srcline) अणु
			ख_माला_लो(buf, माप(buf), अगरile);
				ख_लिखो(listfile, "             \t%s", buf);
				line++;
		पूर्ण
		ख_लिखो(listfile, "%04x %02x%02x%02x%02x", instrptr,
#अगर_घोषित __LITTLE_ENDIAN
			cur_instr->क्रमmat.bytes[0],
			cur_instr->क्रमmat.bytes[1],
			cur_instr->क्रमmat.bytes[2],
			cur_instr->क्रमmat.bytes[3]);
#अन्यथा
			cur_instr->क्रमmat.bytes[3],
			cur_instr->क्रमmat.bytes[2],
			cur_instr->क्रमmat.bytes[1],
			cur_instr->क्रमmat.bytes[0]);
#पूर्ण_अगर
		/*
		 * Macro expansions can cause several inकाष्ठाions
		 * to be output क्रम a single source line.  Only
		 * advance the line once in these हालs.
		 */
		अगर (line == cur_instr->srcline) अणु
			ख_माला_लो(buf, माप(buf), अगरile);
			ख_लिखो(listfile, "\t%s", buf);
			line++;
		पूर्ण अन्यथा अणु
			ख_लिखो(listfile, "\n");
		पूर्ण
		instrptr++;
	पूर्ण
	/* Dump the reमुख्यder of the file */
	जबतक(ख_माला_लो(buf, माप(buf), अगरile) != शून्य)
		ख_लिखो(listfile, "             %s", buf);

	ख_बंद(अगरile);
पूर्ण

अटल पूर्णांक
check_patch(patch_t **start_patch, पूर्णांक start_instr,
	    पूर्णांक *skip_addr, पूर्णांक *func_vals)
अणु
	patch_t *cur_patch;

	cur_patch = *start_patch;

	जबतक (cur_patch != शून्य && start_instr == cur_patch->begin) अणु
		अगर (func_vals[cur_patch->patch_func] == 0) अणु
			पूर्णांक skip;

			/* Start rejecting code */
			*skip_addr = start_instr + cur_patch->skip_instr;
			क्रम (skip = cur_patch->skip_patch;
			     skip > 0 && cur_patch != शून्य;
			     skip--)
				cur_patch = STAILQ_NEXT(cur_patch, links);
		पूर्ण अन्यथा अणु
			/* Accepted this patch.  Advance to the next
			 * one and रुको क्रम our पूर्णांकruction poपूर्णांकer to
			 * hit this poपूर्णांक.
			 */
			cur_patch = STAILQ_NEXT(cur_patch, links);
		पूर्ण
	पूर्ण

	*start_patch = cur_patch;
	अगर (start_instr < *skip_addr)
		/* Still skipping */
		वापस (0);

	वापस (1);
पूर्ण

/*
 * Prपूर्णांक out error inक्रमmation अगर appropriate, and clean up beक्रमe
 * terminating the program.
 */
व्योम
stop(स्थिर अक्षर *string, पूर्णांक err_code)
अणु
	अगर (string != शून्य) अणु
		ख_लिखो(मानक_त्रुटि, "%s: ", appname);
		अगर (yyfilename != शून्य) अणु
			ख_लिखो(मानक_त्रुटि, "Stopped at file %s, line %d - ",
				yyfilename, yylineno);
		पूर्ण
		ख_लिखो(मानक_त्रुटि, "%s\n", string);
	पूर्ण

	अगर (ofile != शून्य) अणु
		ख_बंद(ofile);
		अगर (err_code != 0) अणु
			ख_लिखो(मानक_त्रुटि, "%s: Removing %s due to error\n",
				appname, ofilename);
			unlink(ofilename);
		पूर्ण
	पूर्ण

	अगर (regfile != शून्य) अणु
		ख_बंद(regfile);
		अगर (err_code != 0) अणु
			ख_लिखो(मानक_त्रुटि, "%s: Removing %s due to error\n",
				appname, regfilename);
			unlink(regfilename);
		पूर्ण
	पूर्ण

	अगर (listfile != शून्य) अणु
		ख_बंद(listfile);
		अगर (err_code != 0) अणु
			ख_लिखो(मानक_त्रुटि, "%s: Removing %s due to error\n",
				appname, listfilename);
			unlink(listfilename);
		पूर्ण
	पूर्ण

	symlist_मुक्त(&patch_functions);
	symtable_बंद();

	निकास(err_code);
पूर्ण

काष्ठा inकाष्ठाion *
seq_alloc()
अणु
	काष्ठा inकाष्ठाion *new_instr;

	new_instr = (काष्ठा inकाष्ठाion *)दो_स्मृति(माप(काष्ठा inकाष्ठाion));
	अगर (new_instr == शून्य)
		stop("Unable to malloc instruction object", EX_SOFTWARE);
	स_रखो(new_instr, 0, माप(*new_instr));
	STAILQ_INSERT_TAIL(&seq_program, new_instr, links);
	new_instr->srcline = yylineno;
	वापस new_instr;
पूर्ण

critical_section_t *
cs_alloc()
अणु
	critical_section_t *new_cs;

	new_cs= (critical_section_t *)दो_स्मृति(माप(critical_section_t));
	अगर (new_cs == शून्य)
		stop("Unable to malloc critical_section object", EX_SOFTWARE);
	स_रखो(new_cs, 0, माप(*new_cs));
	
	TAILQ_INSERT_TAIL(&cs_tailq, new_cs, links);
	वापस new_cs;
पूर्ण

scope_t *
scope_alloc()
अणु
	scope_t *new_scope;

	new_scope = (scope_t *)दो_स्मृति(माप(scope_t));
	अगर (new_scope == शून्य)
		stop("Unable to malloc scope object", EX_SOFTWARE);
	स_रखो(new_scope, 0, माप(*new_scope));
	TAILQ_INIT(&new_scope->inner_scope);
	
	अगर (SLIST_FIRST(&scope_stack) != शून्य) अणु
		TAILQ_INSERT_TAIL(&SLIST_FIRST(&scope_stack)->inner_scope,
				  new_scope, scope_links);
	पूर्ण
	/* This patch is now the current scope */
	SLIST_INSERT_HEAD(&scope_stack, new_scope, scope_stack_links);
	वापस new_scope;
पूर्ण

व्योम
process_scope(scope_t *scope)
अणु
	/*
	 * We are "leaving" this scope.  We should now have
	 * enough inक्रमmation to process the lists of scopes
	 * we encapsulate.
	 */
	scope_t *cur_scope;
	u_पूर्णांक skip_patch_count;
	u_पूर्णांक skip_instr_count;

	cur_scope = TAILQ_LAST(&scope->inner_scope, scope_tailq);
	skip_patch_count = 0;
	skip_instr_count = 0;
	जबतक (cur_scope != शून्य) अणु
		u_पूर्णांक patch0_patch_skip;

		patch0_patch_skip = 0;
		चयन (cur_scope->type) अणु
		हाल SCOPE_IF:
		हाल SCOPE_ELSE_IF:
			अगर (skip_instr_count != 0) अणु
				/* Create a tail patch */
				patch0_patch_skip++;
				cur_scope->patches[1].skip_patch =
				    skip_patch_count + 1;
				cur_scope->patches[1].skip_instr =
				    skip_instr_count;
			पूर्ण

			/* Count Head patch */
			patch0_patch_skip++;

			/* Count any patches contained in our inner scope */
			patch0_patch_skip += cur_scope->inner_scope_patches;

			cur_scope->patches[0].skip_patch = patch0_patch_skip;
			cur_scope->patches[0].skip_instr =
			    cur_scope->end_addr - cur_scope->begin_addr;

			skip_instr_count += cur_scope->patches[0].skip_instr;

			skip_patch_count += patch0_patch_skip;
			अगर (cur_scope->type == SCOPE_IF) अणु
				scope->inner_scope_patches += skip_patch_count;
				skip_patch_count = 0;
			        skip_instr_count = 0;
			पूर्ण
			अवरोध;
		हाल SCOPE_ELSE:
			/* Count any patches contained in our innter scope */
			skip_patch_count += cur_scope->inner_scope_patches;

			skip_instr_count += cur_scope->end_addr
					  - cur_scope->begin_addr;
			अवरोध;
		हाल SCOPE_ROOT:
			stop("Unexpected scope type encountered", EX_SOFTWARE);
			/* NOTREACHED */
		पूर्ण

		cur_scope = TAILQ_PREV(cur_scope, scope_tailq, scope_links);
	पूर्ण
पूर्ण
