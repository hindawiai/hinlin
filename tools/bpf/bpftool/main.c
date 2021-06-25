<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <linux/bpf.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/btf.h>

#समावेश "main.h"

#घोषणा BATCH_LINE_LEN_MAX 65536
#घोषणा BATCH_ARG_NB_MAX 4096

स्थिर अक्षर *bin_name;
अटल पूर्णांक last_argc;
अटल अक्षर **last_argv;
अटल पूर्णांक (*last_करो_help)(पूर्णांक argc, अक्षर **argv);
json_ग_लिखोr_t *json_wtr;
bool pretty_output;
bool json_output;
bool show_pinned;
bool block_mount;
bool verअगरier_logs;
bool relaxed_maps;
काष्ठा btf *base_btf;
काष्ठा pinned_obj_table prog_table;
काष्ठा pinned_obj_table map_table;
काष्ठा pinned_obj_table link_table;
काष्ठा obj_refs_table refs_table;

अटल व्योम __noवापस clean_and_निकास(पूर्णांक i)
अणु
	अगर (json_output)
		jsonw_destroy(&json_wtr);

	निकास(i);
पूर्ण

व्योम usage(व्योम)
अणु
	last_करो_help(last_argc - 1, last_argv + 1);

	clean_and_निकास(-1);
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %s [OPTIONS] OBJECT { COMMAND | help }\n"
		"       %s batch file FILE\n"
		"       %s version\n"
		"\n"
		"       OBJECT := { prog | map | link | cgroup | perf | net | feature | btf | gen | struct_ops | iter }\n"
		"       " HELP_SPEC_OPTIONS "\n"
		"",
		bin_name, bin_name, bin_name);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_version(पूर्णांक argc, अक्षर **argv)
अणु
#अगर_घोषित HAVE_LIBBFD_SUPPORT
	स्थिर bool has_libbfd = true;
#अन्यथा
	स्थिर bool has_libbfd = false;
#पूर्ण_अगर
#अगर_घोषित BPFTOOL_WITHOUT_SKELETONS
	स्थिर bool has_skeletons = false;
#अन्यथा
	स्थिर bool has_skeletons = true;
#पूर्ण_अगर

	अगर (json_output) अणु
		jsonw_start_object(json_wtr);	/* root object */

		jsonw_name(json_wtr, "version");
		jsonw_म_लिखो(json_wtr, "\"%s\"", BPFTOOL_VERSION);

		jsonw_name(json_wtr, "features");
		jsonw_start_object(json_wtr);	/* features */
		jsonw_bool_field(json_wtr, "libbfd", has_libbfd);
		jsonw_bool_field(json_wtr, "skeletons", has_skeletons);
		jsonw_end_object(json_wtr);	/* features */

		jsonw_end_object(json_wtr);	/* root object */
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक nb_features = 0;

		म_लिखो("%s v%s\n", bin_name, BPFTOOL_VERSION);
		म_लिखो("features:");
		अगर (has_libbfd) अणु
			म_लिखो(" libbfd");
			nb_features++;
		पूर्ण
		अगर (has_skeletons)
			म_लिखो("%s skeletons", nb_features++ ? "," : "");
		म_लिखो("\n");
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cmd_select(स्थिर काष्ठा cmd *cmds, पूर्णांक argc, अक्षर **argv,
	       पूर्णांक (*help)(पूर्णांक argc, अक्षर **argv))
अणु
	अचिन्हित पूर्णांक i;

	last_argc = argc;
	last_argv = argv;
	last_करो_help = help;

	अगर (argc < 1 && cmds[0].func)
		वापस cmds[0].func(argc, argv);

	क्रम (i = 0; cmds[i].cmd; i++) अणु
		अगर (is_prefix(*argv, cmds[i].cmd)) अणु
			अगर (!cmds[i].func) अणु
				p_err("command '%s' is not supported in bootstrap mode",
				      cmds[i].cmd);
				वापस -1;
			पूर्ण
			वापस cmds[i].func(argc - 1, argv + 1);
		पूर्ण
	पूर्ण

	help(argc - 1, argv + 1);

	वापस -1;
पूर्ण

bool is_prefix(स्थिर अक्षर *pfx, स्थिर अक्षर *str)
अणु
	अगर (!pfx)
		वापस false;
	अगर (म_माप(str) < म_माप(pfx))
		वापस false;

	वापस !स_भेद(str, pfx, म_माप(pfx));
पूर्ण

/* Last argument MUST be शून्य poपूर्णांकer */
पूर्णांक detect_common_prefix(स्थिर अक्षर *arg, ...)
अणु
	अचिन्हित पूर्णांक count = 0;
	स्थिर अक्षर *ref;
	अक्षर msg[256];
	बहु_सूची ap;

	snम_लिखो(msg, माप(msg), "ambiguous prefix: '%s' could be '", arg);
	बहु_शुरू(ap, arg);
	जबतक ((ref = बहु_तर्क(ap, स्थिर अक्षर *))) अणु
		अगर (!is_prefix(arg, ref))
			जारी;
		count++;
		अगर (count > 1)
			म_जोड़न(msg, "' or '", माप(msg) - म_माप(msg) - 1);
		म_जोड़न(msg, ref, माप(msg) - म_माप(msg) - 1);
	पूर्ण
	बहु_पूर्ण(ap);
	म_जोड़न(msg, "'", माप(msg) - म_माप(msg) - 1);

	अगर (count >= 2) अणु
		p_err("%s", msg);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम fprपूर्णांक_hex(खाता *f, व्योम *arg, अचिन्हित पूर्णांक n, स्थिर अक्षर *sep)
अणु
	अचिन्हित अक्षर *data = arg;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		स्थिर अक्षर *pfx = "";

		अगर (!i)
			/* nothing */;
		अन्यथा अगर (!(i % 16))
			ख_लिखो(f, "\n");
		अन्यथा अगर (!(i % 8))
			ख_लिखो(f, "  ");
		अन्यथा
			pfx = sep;

		ख_लिखो(f, "%s%02hhx", i ? pfx : "", data[i]);
	पूर्ण
पूर्ण

/* Split command line पूर्णांकo argument vector. */
अटल पूर्णांक make_args(अक्षर *line, अक्षर *n_argv[], पूर्णांक maxargs, पूर्णांक cmd_nb)
अणु
	अटल स्थिर अक्षर ws[] = " \t\r\n";
	अक्षर *cp = line;
	पूर्णांक n_argc = 0;

	जबतक (*cp) अणु
		/* Skip leading whitespace. */
		cp += म_अखोज(cp, ws);

		अगर (*cp == '\0')
			अवरोध;

		अगर (n_argc >= (maxargs - 1)) अणु
			p_err("too many arguments to command %d", cmd_nb);
			वापस -1;
		पूर्ण

		/* Word begins with quote. */
		अगर (*cp == '\'' || *cp == '"') अणु
			अक्षर quote = *cp++;

			n_argv[n_argc++] = cp;
			/* Find ending quote. */
			cp = म_अक्षर(cp, quote);
			अगर (!cp) अणु
				p_err("unterminated quoted string in command %d",
				      cmd_nb);
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			n_argv[n_argc++] = cp;

			/* Find end of word. */
			cp += म_खोज(cp, ws);
			अगर (*cp == '\0')
				अवरोध;
		पूर्ण

		/* Separate words. */
		*cp++ = 0;
	पूर्ण
	n_argv[n_argc] = शून्य;

	वापस n_argc;
पूर्ण

अटल पूर्णांक करो_batch(पूर्णांक argc, अक्षर **argv);

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "help",	करो_help पूर्ण,
	अणु "batch",	करो_batch पूर्ण,
	अणु "prog",	करो_prog पूर्ण,
	अणु "map",	करो_map पूर्ण,
	अणु "link",	करो_link पूर्ण,
	अणु "cgroup",	करो_cgroup पूर्ण,
	अणु "perf",	करो_perf पूर्ण,
	अणु "net",	करो_net पूर्ण,
	अणु "feature",	करो_feature पूर्ण,
	अणु "btf",	करो_btf पूर्ण,
	अणु "gen",	करो_gen पूर्ण,
	अणु "struct_ops",	करो_काष्ठा_ops पूर्ण,
	अणु "iter",	करो_iter पूर्ण,
	अणु "version",	करो_version पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल पूर्णांक करो_batch(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर buf[BATCH_LINE_LEN_MAX], contline[BATCH_LINE_LEN_MAX];
	अक्षर *n_argv[BATCH_ARG_NB_MAX];
	अचिन्हित पूर्णांक lines = 0;
	पूर्णांक n_argc;
	खाता *fp;
	अक्षर *cp;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (argc < 2) अणु
		p_err("too few parameters for batch");
		वापस -1;
	पूर्ण अन्यथा अगर (!is_prefix(*argv, "file")) अणु
		p_err("expected 'file', got: %s", *argv);
		वापस -1;
	पूर्ण अन्यथा अगर (argc > 2) अणु
		p_err("too many parameters for batch");
		वापस -1;
	पूर्ण
	NEXT_ARG();

	अगर (!म_भेद(*argv, "-"))
		fp = मानक_निवेश;
	अन्यथा
		fp = ख_खोलो(*argv, "r");
	अगर (!fp) अणु
		p_err("Can't open file (%s): %s", *argv, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	अगर (json_output)
		jsonw_start_array(json_wtr);
	जबतक (ख_माला_लो(buf, माप(buf), fp)) अणु
		cp = म_अक्षर(buf, '#');
		अगर (cp)
			*cp = '\0';

		अगर (म_माप(buf) == माप(buf) - 1) अणु
			त्रुटि_सं = E2BIG;
			अवरोध;
		पूर्ण

		/* Append continuation lines अगर any (coming after a line ending
		 * with '\' in the batch file).
		 */
		जबतक ((cp = म_माला(buf, "\\\n")) != शून्य) अणु
			अगर (!ख_माला_लो(contline, माप(contline), fp) ||
			    म_माप(contline) == 0) अणु
				p_err("missing continuation line on command %d",
				      lines);
				err = -1;
				जाओ err_बंद;
			पूर्ण

			cp = म_अक्षर(contline, '#');
			अगर (cp)
				*cp = '\0';

			अगर (म_माप(buf) + म_माप(contline) + 1 > माप(buf)) अणु
				p_err("command %d is too long", lines);
				err = -1;
				जाओ err_बंद;
			पूर्ण
			buf[म_माप(buf) - 2] = '\0';
			म_जोड़ो(buf, contline);
		पूर्ण

		n_argc = make_args(buf, n_argv, BATCH_ARG_NB_MAX, lines);
		अगर (!n_argc)
			जारी;
		अगर (n_argc < 0)
			जाओ err_बंद;

		अगर (json_output) अणु
			jsonw_start_object(json_wtr);
			jsonw_name(json_wtr, "command");
			jsonw_start_array(json_wtr);
			क्रम (i = 0; i < n_argc; i++)
				jsonw_string(json_wtr, n_argv[i]);
			jsonw_end_array(json_wtr);
			jsonw_name(json_wtr, "output");
		पूर्ण

		err = cmd_select(cmds, n_argc, n_argv, करो_help);

		अगर (json_output)
			jsonw_end_object(json_wtr);

		अगर (err)
			जाओ err_बंद;

		lines++;
	पूर्ण

	अगर (त्रुटि_सं && त्रुटि_सं != ENOENT) अणु
		p_err("reading batch file failed: %s", म_त्रुटि(त्रुटि_सं));
		err = -1;
	पूर्ण अन्यथा अणु
		अगर (!json_output)
			म_लिखो("processed %d commands\n", lines);
	पूर्ण
err_बंद:
	अगर (fp != मानक_निवेश)
		ख_बंद(fp);

	अगर (json_output)
		jsonw_end_array(json_wtr);

	वापस err;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अटल स्थिर काष्ठा option options[] = अणु
		अणु "json",	no_argument,	शून्य,	'j' पूर्ण,
		अणु "help",	no_argument,	शून्य,	'h' पूर्ण,
		अणु "pretty",	no_argument,	शून्य,	'p' पूर्ण,
		अणु "version",	no_argument,	शून्य,	'V' पूर्ण,
		अणु "bpffs",	no_argument,	शून्य,	'f' पूर्ण,
		अणु "mapcompat",	no_argument,	शून्य,	'm' पूर्ण,
		अणु "nomount",	no_argument,	शून्य,	'n' पूर्ण,
		अणु "debug",	no_argument,	शून्य,	'd' पूर्ण,
		अणु "base-btf",	required_argument, शून्य, 'B' पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	पूर्णांक opt, ret;

	last_करो_help = करो_help;
	pretty_output = false;
	json_output = false;
	show_pinned = false;
	block_mount = false;
	bin_name = argv[0];

	hash_init(prog_table.table);
	hash_init(map_table.table);
	hash_init(link_table.table);

	opterr = 0;
	जबतक ((opt = getopt_दीर्घ(argc, argv, "VhpjfmndB:",
				  options, शून्य)) >= 0) अणु
		चयन (opt) अणु
		हाल 'V':
			वापस करो_version(argc, argv);
		हाल 'h':
			वापस करो_help(argc, argv);
		हाल 'p':
			pretty_output = true;
			/* fall through */
		हाल 'j':
			अगर (!json_output) अणु
				json_wtr = jsonw_new(मानक_निकास);
				अगर (!json_wtr) अणु
					p_err("failed to create JSON writer");
					वापस -1;
				पूर्ण
				json_output = true;
			पूर्ण
			jsonw_pretty(json_wtr, pretty_output);
			अवरोध;
		हाल 'f':
			show_pinned = true;
			अवरोध;
		हाल 'm':
			relaxed_maps = true;
			अवरोध;
		हाल 'n':
			block_mount = true;
			अवरोध;
		हाल 'd':
			libbpf_set_prपूर्णांक(prपूर्णांक_all_levels);
			verअगरier_logs = true;
			अवरोध;
		हाल 'B':
			base_btf = btf__parse(optarg, शून्य);
			अगर (libbpf_get_error(base_btf)) अणु
				p_err("failed to parse base BTF at '%s': %ld\n",
				      optarg, libbpf_get_error(base_btf));
				base_btf = शून्य;
				वापस -1;
			पूर्ण
			अवरोध;
		शेष:
			p_err("unrecognized option '%s'", argv[optind - 1]);
			अगर (json_output)
				clean_and_निकास(-1);
			अन्यथा
				usage();
		पूर्ण
	पूर्ण

	argc -= optind;
	argv += optind;
	अगर (argc < 0)
		usage();

	ret = cmd_select(cmds, argc, argv, करो_help);

	अगर (json_output)
		jsonw_destroy(&json_wtr);

	अगर (show_pinned) अणु
		delete_pinned_obj_table(&prog_table);
		delete_pinned_obj_table(&map_table);
		delete_pinned_obj_table(&link_table);
	पूर्ण
	btf__मुक्त(base_btf);

	वापस ret;
पूर्ण
