<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2005.
 */

#समावेश <sys/स्थिति.स>

#समावेश "dtc.h"
#समावेश "srcpos.h"

/*
 * Command line options
 */
पूर्णांक quiet;		/* Level of quietness */
पूर्णांक reservक्रमागत;		/* Number of memory reservation slots */
पूर्णांक minsize;		/* Minimum blob size */
पूर्णांक padsize;		/* Additional padding to blob */
पूर्णांक alignsize;		/* Additional padding to blob accroding to the alignsize */
पूर्णांक phandle_क्रमmat = PHANDLE_EPAPR;	/* Use linux,phandle or phandle properties */
पूर्णांक generate_symbols;	/* enable symbols & fixup support */
पूर्णांक generate_fixups;		/* suppress generation of fixups on symbol support */
पूर्णांक स्वतः_label_aliases;		/* स्वतः generate labels -> aliases */
पूर्णांक annotate;		/* Level of annotation: 1 क्रम input source location
			   >1 क्रम full input source location. */

अटल पूर्णांक is_घातer_of_2(पूर्णांक x)
अणु
	वापस (x > 0) && ((x & (x - 1)) == 0);
पूर्ण

अटल व्योम fill_fullpaths(काष्ठा node *tree, स्थिर अक्षर *prefix)
अणु
	काष्ठा node *child;
	स्थिर अक्षर *unit;

	tree->fullpath = join_path(prefix, tree->name);

	unit = म_अक्षर(tree->name, '@');
	अगर (unit)
		tree->basenamelen = unit - tree->name;
	अन्यथा
		tree->basenamelen = म_माप(tree->name);

	क्रम_each_child(tree, child)
		fill_fullpaths(child, tree->fullpath);
पूर्ण

/* Usage related data. */
अटल स्थिर अक्षर usage_synopsis[] = "dtc [options] <input file>";
अटल स्थिर अक्षर usage_लघु_opts[] = "qI:O:o:V:d:R:S:p:a:fb:i:H:sW:E:@AThv";
अटल काष्ठा option स्थिर usage_दीर्घ_opts[] = अणु
	अणु"quiet",            no_argument, शून्य, 'q'पूर्ण,
	अणु"in-format",         a_argument, शून्य, 'I'पूर्ण,
	अणु"out",               a_argument, शून्य, 'o'पूर्ण,
	अणु"out-format",        a_argument, शून्य, 'O'पूर्ण,
	अणु"out-version",       a_argument, शून्य, 'V'पूर्ण,
	अणु"out-dependency",    a_argument, शून्य, 'd'पूर्ण,
	अणु"reserve",           a_argument, शून्य, 'R'पूर्ण,
	अणु"space",             a_argument, शून्य, 'S'पूर्ण,
	अणु"pad",               a_argument, शून्य, 'p'पूर्ण,
	अणु"align",             a_argument, शून्य, 'a'पूर्ण,
	अणु"boot-cpu",          a_argument, शून्य, 'b'पूर्ण,
	अणु"force",            no_argument, शून्य, 'f'पूर्ण,
	अणु"include",           a_argument, शून्य, 'i'पूर्ण,
	अणु"sort",             no_argument, शून्य, 's'पूर्ण,
	अणु"phandle",           a_argument, शून्य, 'H'पूर्ण,
	अणु"warning",           a_argument, शून्य, 'W'पूर्ण,
	अणु"error",             a_argument, शून्य, 'E'पूर्ण,
	अणु"symbols",	     no_argument, शून्य, '@'पूर्ण,
	अणु"auto-alias",       no_argument, शून्य, 'A'पूर्ण,
	अणु"annotate",         no_argument, शून्य, 'T'पूर्ण,
	अणु"help",             no_argument, शून्य, 'h'पूर्ण,
	अणु"version",          no_argument, शून्य, 'v'पूर्ण,
	अणुशून्य,               no_argument, शून्य, 0x0पूर्ण,
पूर्ण;
अटल स्थिर अक्षर * स्थिर usage_opts_help[] = अणु
	"\n\tQuiet: -q suppress warnings, -qq errors, -qqq all",
	"\n\tInput formats are:\n"
	 "\t\tdts - device tree source text\n"
	 "\t\tdtb - device tree blob\n"
	 "\t\tfs  - /proc/device-tree style directory",
	"\n\tOutput file",
	"\n\tOutput formats are:\n"
	 "\t\tdts - device tree source text\n"
	 "\t\tdtb - device tree blob\n"
#अगर_अघोषित NO_YAML
	 "\t\tyaml - device tree encoded as YAML\n"
#पूर्ण_अगर
	 "\t\tasm - assembler source",
	"\n\tBlob version to produce, defaults to "stringअगरy(DEFAULT_FDT_VERSION)" (for dtb and asm output)",
	"\n\tOutput dependency file",
	"\n\tMake space for <number> reserve map entries (for dtb and asm output)",
	"\n\tMake the blob at least <bytes> long (extra space)",
	"\n\tAdd padding to the blob of <bytes> long (extra space)",
	"\n\tMake the blob align to the <bytes> (extra space)",
	"\n\tSet the physical boot cpu",
	"\n\tTry to produce output even if the input tree has errors",
	"\n\tAdd a path to search for include files",
	"\n\tSort nodes and properties before outputting (useful for comparing trees)",
	"\n\tValid phandle formats are:\n"
	 "\t\tlegacy - \"linux,phandle\" properties only\n"
	 "\t\tepapr  - \"phandle\" properties only\n"
	 "\t\tboth   - Both \"linux,phandle\" and \"phandle\" properties",
	"\n\tEnable/disable warnings (prefix with \"no-\")",
	"\n\tEnable/disable errors (prefix with \"no-\")",
	"\n\tEnable generation of symbols",
	"\n\tEnable auto-alias of labels",
	"\n\tAnnotate output .dts with input source file and line (-T -T for more details)",
	"\n\tPrint this help and exit",
	"\n\tPrint version and exit",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर *guess_type_by_name(स्थिर अक्षर *fname, स्थिर अक्षर *fallback)
अणु
	स्थिर अक्षर *s;

	s = म_खोजप(fname, '.');
	अगर (s == शून्य)
		वापस fallback;
	अगर (!strहालcmp(s, ".dts"))
		वापस "dts";
	अगर (!strहालcmp(s, ".yaml"))
		वापस "yaml";
	अगर (!strहालcmp(s, ".dtbo"))
		वापस "dtb";
	अगर (!strहालcmp(s, ".dtb"))
		वापस "dtb";
	वापस fallback;
पूर्ण

अटल स्थिर अक्षर *guess_input_क्रमmat(स्थिर अक्षर *fname, स्थिर अक्षर *fallback)
अणु
	काष्ठा stat statbuf;
	fdt32_t magic;
	खाता *f;

	अगर (stat(fname, &statbuf) != 0)
		वापस fallback;

	अगर (S_ISसूची(statbuf.st_mode))
		वापस "fs";

	अगर (!S_ISREG(statbuf.st_mode))
		वापस fallback;

	f = ख_खोलो(fname, "r");
	अगर (f == शून्य)
		वापस fallback;
	अगर (ख_पढ़ो(&magic, 4, 1, f) != 1) अणु
		ख_बंद(f);
		वापस fallback;
	पूर्ण
	ख_बंद(f);

	अगर (fdt32_to_cpu(magic) == FDT_MAGIC)
		वापस "dtb";

	वापस guess_type_by_name(fname, fallback);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा dt_info *dti;
	स्थिर अक्षर *inक्रमm = शून्य;
	स्थिर अक्षर *outक्रमm = शून्य;
	स्थिर अक्षर *outname = "-";
	स्थिर अक्षर *depname = शून्य;
	bool क्रमce = false, sort = false;
	स्थिर अक्षर *arg;
	पूर्णांक opt;
	खाता *outf = शून्य;
	पूर्णांक outversion = DEFAULT_FDT_VERSION;
	दीर्घ दीर्घ cmdline_boot_cpuid = -1;

	quiet      = 0;
	reservक्रमागत = 0;
	minsize    = 0;
	padsize    = 0;
	alignsize  = 0;

	जबतक ((opt = util_getopt_दीर्घ()) != खातापूर्ण) अणु
		चयन (opt) अणु
		हाल 'I':
			inक्रमm = optarg;
			अवरोध;
		हाल 'O':
			outक्रमm = optarg;
			अवरोध;
		हाल 'o':
			outname = optarg;
			अवरोध;
		हाल 'V':
			outversion = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'd':
			depname = optarg;
			अवरोध;
		हाल 'R':
			reservक्रमागत = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'S':
			minsize = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'p':
			padsize = म_से_दीर्घ(optarg, शून्य, 0);
			अवरोध;
		हाल 'a':
			alignsize = म_से_दीर्घ(optarg, शून्य, 0);
			अगर (!is_घातer_of_2(alignsize))
				die("Invalid argument \"%d\" to -a option\n",
				    alignsize);
			अवरोध;
		हाल 'f':
			क्रमce = true;
			अवरोध;
		हाल 'q':
			quiet++;
			अवरोध;
		हाल 'b':
			cmdline_boot_cpuid = म_से_दीर्घl(optarg, शून्य, 0);
			अवरोध;
		हाल 'i':
			srcfile_add_search_path(optarg);
			अवरोध;
		हाल 'v':
			util_version();
		हाल 'H':
			अगर (streq(optarg, "legacy"))
				phandle_क्रमmat = PHANDLE_LEGACY;
			अन्यथा अगर (streq(optarg, "epapr"))
				phandle_क्रमmat = PHANDLE_EPAPR;
			अन्यथा अगर (streq(optarg, "both"))
				phandle_क्रमmat = PHANDLE_BOTH;
			अन्यथा
				die("Invalid argument \"%s\" to -H option\n",
				    optarg);
			अवरोध;

		हाल 's':
			sort = true;
			अवरोध;

		हाल 'W':
			parse_checks_option(true, false, optarg);
			अवरोध;

		हाल 'E':
			parse_checks_option(false, true, optarg);
			अवरोध;

		हाल '@':
			generate_symbols = 1;
			अवरोध;
		हाल 'A':
			स्वतः_label_aliases = 1;
			अवरोध;
		हाल 'T':
			annotate++;
			अवरोध;

		हाल 'h':
			usage(शून्य);
		शेष:
			usage("unknown option");
		पूर्ण
	पूर्ण

	अगर (argc > (optind+1))
		usage("missing files");
	अन्यथा अगर (argc < (optind+1))
		arg = "-";
	अन्यथा
		arg = argv[optind];

	/* minsize and padsize are mutually exclusive */
	अगर (minsize && padsize)
		die("Can't set both -p and -S\n");

	अगर (depname) अणु
		depfile = ख_खोलो(depname, "w");
		अगर (!depfile)
			die("Couldn't open dependency file %s: %s\n", depname,
			    म_त्रुटि(त्रुटि_सं));
		ख_लिखो(depfile, "%s:", outname);
	पूर्ण

	अगर (inक्रमm == शून्य)
		inक्रमm = guess_input_क्रमmat(arg, "dts");
	अगर (outक्रमm == शून्य) अणु
		outक्रमm = guess_type_by_name(outname, शून्य);
		अगर (outक्रमm == शून्य) अणु
			अगर (streq(inक्रमm, "dts"))
				outक्रमm = "dtb";
			अन्यथा
				outक्रमm = "dts";
		पूर्ण
	पूर्ण
	अगर (annotate && (!streq(inक्रमm, "dts") || !streq(outक्रमm, "dts")))
		die("--annotate requires -I dts -O dts\n");
	अगर (streq(inक्रमm, "dts"))
		dti = dt_from_source(arg);
	अन्यथा अगर (streq(inक्रमm, "fs"))
		dti = dt_from_fs(arg);
	अन्यथा अगर(streq(inक्रमm, "dtb"))
		dti = dt_from_blob(arg);
	अन्यथा
		die("Unknown input format \"%s\"\n", inक्रमm);

	dti->outname = outname;

	अगर (depfile) अणु
		ख_अक्षर_दो('\n', depfile);
		ख_बंद(depfile);
	पूर्ण

	अगर (cmdline_boot_cpuid != -1)
		dti->boot_cpuid_phys = cmdline_boot_cpuid;

	fill_fullpaths(dti->dt, "");

	/* on a plugin, generate by शेष */
	अगर (dti->dtsflags & DTSF_PLUGIN) अणु
		generate_fixups = 1;
	पूर्ण

	process_checks(क्रमce, dti);

	अगर (स्वतः_label_aliases)
		generate_label_tree(dti, "aliases", false);

	अगर (generate_symbols)
		generate_label_tree(dti, "__symbols__", true);

	अगर (generate_fixups) अणु
		generate_fixups_tree(dti, "__fixups__");
		generate_local_fixups_tree(dti, "__local_fixups__");
	पूर्ण

	अगर (sort)
		sort_tree(dti);

	अगर (streq(outname, "-")) अणु
		outf = मानक_निकास;
	पूर्ण अन्यथा अणु
		outf = ख_खोलो(outname, "wb");
		अगर (! outf)
			die("Couldn't open output file %s: %s\n",
			    outname, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	अगर (streq(outक्रमm, "dts")) अणु
		dt_to_source(outf, dti);
#अगर_अघोषित NO_YAML
	पूर्ण अन्यथा अगर (streq(outक्रमm, "yaml")) अणु
		अगर (!streq(inक्रमm, "dts"))
			die("YAML output format requires dts input format\n");
		dt_to_yaml(outf, dti);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (streq(outक्रमm, "dtb")) अणु
		dt_to_blob(outf, dti, outversion);
	पूर्ण अन्यथा अगर (streq(outक्रमm, "dtbo")) अणु
		dt_to_blob(outf, dti, outversion);
	पूर्ण अन्यथा अगर (streq(outक्रमm, "asm")) अणु
		dt_to_यंत्र(outf, dti, outversion);
	पूर्ण अन्यथा अगर (streq(outक्रमm, "null")) अणु
		/* करो nothing */
	पूर्ण अन्यथा अणु
		die("Unknown output format \"%s\"\n", outक्रमm);
	पूर्ण

	निकास(0);
पूर्ण
