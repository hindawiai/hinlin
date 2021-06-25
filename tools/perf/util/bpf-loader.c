<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bpf-loader.c
 *
 * Copyright (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015 Huawei Inc.
 */

#समावेश <linux/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "bpf-loader.h"
#समावेश "bpf-prologue.h"
#समावेश "probe-event.h"
#समावेश "probe-finder.h" // क्रम MAX_PROBES
#समावेश "parse-events.h"
#समावेश "strfilter.h"
#समावेश "util.h"
#समावेश "llvm-utils.h"
#समावेश "c++/clang-c.h"

#समावेश <पूर्णांकernal/xyarray.h>

अटल पूर्णांक libbpf_perf_prपूर्णांक(क्रमागत libbpf_prपूर्णांक_level level __attribute__((unused)),
			      स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस veम_लिखो(1, verbose, pr_fmt(fmt), args);
पूर्ण

काष्ठा bpf_prog_priv अणु
	bool is_tp;
	अक्षर *sys_name;
	अक्षर *evt_name;
	काष्ठा perf_probe_event pev;
	bool need_prologue;
	काष्ठा bpf_insn *insns_buf;
	पूर्णांक nr_types;
	पूर्णांक *type_mapping;
पूर्ण;

अटल bool libbpf_initialized;

काष्ठा bpf_object *
bpf__prepare_load_buffer(व्योम *obj_buf, माप_प्रकार obj_buf_sz, स्थिर अक्षर *name)
अणु
	काष्ठा bpf_object *obj;

	अगर (!libbpf_initialized) अणु
		libbpf_set_prपूर्णांक(libbpf_perf_prपूर्णांक);
		libbpf_initialized = true;
	पूर्ण

	obj = bpf_object__खोलो_buffer(obj_buf, obj_buf_sz, name);
	अगर (IS_ERR_OR_शून्य(obj)) अणु
		pr_debug("bpf: failed to load buffer\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस obj;
पूर्ण

काष्ठा bpf_object *bpf__prepare_load(स्थिर अक्षर *filename, bool source)
अणु
	काष्ठा bpf_object *obj;

	अगर (!libbpf_initialized) अणु
		libbpf_set_prपूर्णांक(libbpf_perf_prपूर्णांक);
		libbpf_initialized = true;
	पूर्ण

	अगर (source) अणु
		पूर्णांक err;
		व्योम *obj_buf;
		माप_प्रकार obj_buf_sz;

		perf_clang__init();
		err = perf_clang__compile_bpf(filename, &obj_buf, &obj_buf_sz);
		perf_clang__cleanup();
		अगर (err) अणु
			pr_debug("bpf: builtin compilation failed: %d, try external compiler\n", err);
			err = llvm__compile_bpf(filename, &obj_buf, &obj_buf_sz);
			अगर (err)
				वापस ERR_PTR(-BPF_LOADER_ERRNO__COMPILE);
		पूर्ण अन्यथा
			pr_debug("bpf: successful builtin compilation\n");
		obj = bpf_object__खोलो_buffer(obj_buf, obj_buf_sz, filename);

		अगर (!IS_ERR_OR_शून्य(obj) && llvm_param.dump_obj)
			llvm__dump_obj(filename, obj_buf, obj_buf_sz);

		मुक्त(obj_buf);
	पूर्ण अन्यथा
		obj = bpf_object__खोलो(filename);

	अगर (IS_ERR_OR_शून्य(obj)) अणु
		pr_debug("bpf: failed to load %s\n", filename);
		वापस obj;
	पूर्ण

	वापस obj;
पूर्ण

व्योम bpf__clear(व्योम)
अणु
	काष्ठा bpf_object *obj, *पंचांगp;

	bpf_object__क्रम_each_safe(obj, पंचांगp) अणु
		bpf__unprobe(obj);
		bpf_object__बंद(obj);
	पूर्ण
पूर्ण

अटल व्योम
clear_prog_priv(काष्ठा bpf_program *prog __maybe_unused,
		व्योम *_priv)
अणु
	काष्ठा bpf_prog_priv *priv = _priv;

	cleanup_perf_probe_events(&priv->pev, 1);
	zमुक्त(&priv->insns_buf);
	zमुक्त(&priv->type_mapping);
	zमुक्त(&priv->sys_name);
	zमुक्त(&priv->evt_name);
	मुक्त(priv);
पूर्ण

अटल पूर्णांक
prog_config__exec(स्थिर अक्षर *value, काष्ठा perf_probe_event *pev)
अणु
	pev->uprobes = true;
	pev->target = strdup(value);
	अगर (!pev->target)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक
prog_config__module(स्थिर अक्षर *value, काष्ठा perf_probe_event *pev)
अणु
	pev->uprobes = false;
	pev->target = strdup(value);
	अगर (!pev->target)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक
prog_config__bool(स्थिर अक्षर *value, bool *pbool, bool invert)
अणु
	पूर्णांक err;
	bool bool_value;

	अगर (!pbool)
		वापस -EINVAL;

	err = strtobool(value, &bool_value);
	अगर (err)
		वापस err;

	*pbool = invert ? !bool_value : bool_value;
	वापस 0;
पूर्ण

अटल पूर्णांक
prog_config__अंतरभूतs(स्थिर अक्षर *value,
		     काष्ठा perf_probe_event *pev __maybe_unused)
अणु
	वापस prog_config__bool(value, &probe_conf.no_अंतरभूतs, true);
पूर्ण

अटल पूर्णांक
prog_config__क्रमce(स्थिर अक्षर *value,
		   काष्ठा perf_probe_event *pev __maybe_unused)
अणु
	वापस prog_config__bool(value, &probe_conf.क्रमce_add, false);
पूर्ण

अटल काष्ठा अणु
	स्थिर अक्षर *key;
	स्थिर अक्षर *usage;
	स्थिर अक्षर *desc;
	पूर्णांक (*func)(स्थिर अक्षर *, काष्ठा perf_probe_event *);
पूर्ण bpf_prog_config_terms[] = अणु
	अणु
		.key	= "exec",
		.usage	= "exec=<full path of file>",
		.desc	= "Set uprobe target",
		.func	= prog_config__exec,
	पूर्ण,
	अणु
		.key	= "module",
		.usage	= "module=<module name>    ",
		.desc	= "Set kprobe module",
		.func	= prog_config__module,
	पूर्ण,
	अणु
		.key	= "inlines",
		.usage	= "inlines=[yes|no]        ",
		.desc	= "Probe at inline symbol",
		.func	= prog_config__अंतरभूतs,
	पूर्ण,
	अणु
		.key	= "force",
		.usage	= "force=[yes|no]          ",
		.desc	= "Forcibly add events with existing name",
		.func	= prog_config__क्रमce,
	पूर्ण,
पूर्ण;

अटल पूर्णांक
करो_prog_config(स्थिर अक्षर *key, स्थिर अक्षर *value,
	       काष्ठा perf_probe_event *pev)
अणु
	अचिन्हित पूर्णांक i;

	pr_debug("config bpf program: %s=%s\n", key, value);
	क्रम (i = 0; i < ARRAY_SIZE(bpf_prog_config_terms); i++)
		अगर (म_भेद(key, bpf_prog_config_terms[i].key) == 0)
			वापस bpf_prog_config_terms[i].func(value, pev);

	pr_debug("BPF: ERROR: invalid program config option: %s=%s\n",
		 key, value);

	pr_debug("\nHint: Valid options are:\n");
	क्रम (i = 0; i < ARRAY_SIZE(bpf_prog_config_terms); i++)
		pr_debug("\t%s:\t%s\n", bpf_prog_config_terms[i].usage,
			 bpf_prog_config_terms[i].desc);
	pr_debug("\n");

	वापस -BPF_LOADER_ERRNO__PROGCONF_TERM;
पूर्ण

अटल स्थिर अक्षर *
parse_prog_config_kvpair(स्थिर अक्षर *config_str, काष्ठा perf_probe_event *pev)
अणु
	अक्षर *text = strdup(config_str);
	अक्षर *sep, *line;
	स्थिर अक्षर *मुख्य_str = शून्य;
	पूर्णांक err = 0;

	अगर (!text) अणु
		pr_debug("Not enough memory: dup config_str failed\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	line = text;
	जबतक ((sep = म_अक्षर(line, ';'))) अणु
		अक्षर *equ;

		*sep = '\0';
		equ = म_अक्षर(line, '=');
		अगर (!equ) अणु
			pr_warning("WARNING: invalid config in BPF object: %s\n",
				   line);
			pr_warning("\tShould be 'key=value'.\n");
			जाओ nextline;
		पूर्ण
		*equ = '\0';

		err = करो_prog_config(line, equ + 1, pev);
		अगर (err)
			अवरोध;
nextline:
		line = sep + 1;
	पूर्ण

	अगर (!err)
		मुख्य_str = config_str + (line - text);
	मुक्त(text);

	वापस err ? ERR_PTR(err) : मुख्य_str;
पूर्ण

अटल पूर्णांक
parse_prog_config(स्थिर अक्षर *config_str, स्थिर अक्षर **p_मुख्य_str,
		  bool *is_tp, काष्ठा perf_probe_event *pev)
अणु
	पूर्णांक err;
	स्थिर अक्षर *मुख्य_str = parse_prog_config_kvpair(config_str, pev);

	अगर (IS_ERR(मुख्य_str))
		वापस PTR_ERR(मुख्य_str);

	*p_मुख्य_str = मुख्य_str;
	अगर (!म_अक्षर(मुख्य_str, '=')) अणु
		/* Is a tracepoपूर्णांक event? */
		स्थिर अक्षर *s = म_अक्षर(मुख्य_str, ':');

		अगर (!s) अणु
			pr_debug("bpf: '%s' is not a valid tracepoint\n",
				 config_str);
			वापस -BPF_LOADER_ERRNO__CONFIG;
		पूर्ण

		*is_tp = true;
		वापस 0;
	पूर्ण

	*is_tp = false;
	err = parse_perf_probe_command(मुख्य_str, pev);
	अगर (err < 0) अणु
		pr_debug("bpf: '%s' is not a valid config string\n",
			 config_str);
		/* parse failed, करोn't need clear pev. */
		वापस -BPF_LOADER_ERRNO__CONFIG;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
config_bpf_program(काष्ठा bpf_program *prog)
अणु
	काष्ठा perf_probe_event *pev = शून्य;
	काष्ठा bpf_prog_priv *priv = शून्य;
	स्थिर अक्षर *config_str, *मुख्य_str;
	bool is_tp = false;
	पूर्णांक err;

	/* Initialize per-program probing setting */
	probe_conf.no_अंतरभूतs = false;
	probe_conf.क्रमce_add = false;

	priv = सुस्मृति(माप(*priv), 1);
	अगर (!priv) अणु
		pr_debug("bpf: failed to alloc priv\n");
		वापस -ENOMEM;
	पूर्ण
	pev = &priv->pev;

	config_str = bpf_program__section_name(prog);
	pr_debug("bpf: config program '%s'\n", config_str);
	err = parse_prog_config(config_str, &मुख्य_str, &is_tp, pev);
	अगर (err)
		जाओ errout;

	अगर (is_tp) अणु
		अक्षर *s = म_अक्षर(मुख्य_str, ':');

		priv->is_tp = true;
		priv->sys_name = strndup(मुख्य_str, s - मुख्य_str);
		priv->evt_name = strdup(s + 1);
		जाओ set_priv;
	पूर्ण

	अगर (pev->group && म_भेद(pev->group, PERF_BPF_PROBE_GROUP)) अणु
		pr_debug("bpf: '%s': group for event is set and not '%s'.\n",
			 config_str, PERF_BPF_PROBE_GROUP);
		err = -BPF_LOADER_ERRNO__GROUP;
		जाओ errout;
	पूर्ण अन्यथा अगर (!pev->group)
		pev->group = strdup(PERF_BPF_PROBE_GROUP);

	अगर (!pev->group) अणु
		pr_debug("bpf: strdup failed\n");
		err = -ENOMEM;
		जाओ errout;
	पूर्ण

	अगर (!pev->event) अणु
		pr_debug("bpf: '%s': event name is missing. Section name should be 'key=value'\n",
			 config_str);
		err = -BPF_LOADER_ERRNO__EVENTNAME;
		जाओ errout;
	पूर्ण
	pr_debug("bpf: config '%s' is ok\n", config_str);

set_priv:
	err = bpf_program__set_priv(prog, priv, clear_prog_priv);
	अगर (err) अणु
		pr_debug("Failed to set priv for program '%s'\n", config_str);
		जाओ errout;
	पूर्ण

	वापस 0;

errout:
	अगर (pev)
		clear_perf_probe_event(pev);
	मुक्त(priv);
	वापस err;
पूर्ण

अटल पूर्णांक bpf__prepare_probe(व्योम)
अणु
	अटल पूर्णांक err = 0;
	अटल bool initialized = false;

	/*
	 * Make err अटल, so अगर init failed the first, bpf__prepare_probe()
	 * fails each समय without calling init_probe_symbol_maps multiple
	 * बार.
	 */
	अगर (initialized)
		वापस err;

	initialized = true;
	err = init_probe_symbol_maps(false);
	अगर (err < 0)
		pr_debug("Failed to init_probe_symbol_maps\n");
	probe_conf.max_probes = MAX_PROBES;
	वापस err;
पूर्ण

अटल पूर्णांक
preproc_gen_prologue(काष्ठा bpf_program *prog, पूर्णांक n,
		     काष्ठा bpf_insn *orig_insns, पूर्णांक orig_insns_cnt,
		     काष्ठा bpf_prog_prep_result *res)
अणु
	काष्ठा bpf_prog_priv *priv = bpf_program__priv(prog);
	काष्ठा probe_trace_event *tev;
	काष्ठा perf_probe_event *pev;
	काष्ठा bpf_insn *buf;
	माप_प्रकार prologue_cnt = 0;
	पूर्णांक i, err;

	अगर (IS_ERR(priv) || !priv || priv->is_tp)
		जाओ errout;

	pev = &priv->pev;

	अगर (n < 0 || n >= priv->nr_types)
		जाओ errout;

	/* Find a tev beदीर्घs to that type */
	क्रम (i = 0; i < pev->ntevs; i++) अणु
		अगर (priv->type_mapping[i] == n)
			अवरोध;
	पूर्ण

	अगर (i >= pev->ntevs) अणु
		pr_debug("Internal error: prologue type %d not found\n", n);
		वापस -BPF_LOADER_ERRNO__PROLOGUE;
	पूर्ण

	tev = &pev->tevs[i];

	buf = priv->insns_buf;
	err = bpf__gen_prologue(tev->args, tev->nargs,
				buf, &prologue_cnt,
				BPF_MAXINSNS - orig_insns_cnt);
	अगर (err) अणु
		स्थिर अक्षर *title;

		title = bpf_program__section_name(prog);
		pr_debug("Failed to generate prologue for program %s\n",
			 title);
		वापस err;
	पूर्ण

	स_नकल(&buf[prologue_cnt], orig_insns,
	       माप(काष्ठा bpf_insn) * orig_insns_cnt);

	res->new_insn_ptr = buf;
	res->new_insn_cnt = prologue_cnt + orig_insns_cnt;
	res->pfd = शून्य;
	वापस 0;

errout:
	pr_debug("Internal error in preproc_gen_prologue\n");
	वापस -BPF_LOADER_ERRNO__PROLOGUE;
पूर्ण

/*
 * compare_tev_args is reflexive, transitive and antisymmetric.
 * I can proof it but this margin is too narrow to contain.
 */
अटल पूर्णांक compare_tev_args(स्थिर व्योम *ptev1, स्थिर व्योम *ptev2)
अणु
	पूर्णांक i, ret;
	स्थिर काष्ठा probe_trace_event *tev1 =
		*(स्थिर काष्ठा probe_trace_event **)ptev1;
	स्थिर काष्ठा probe_trace_event *tev2 =
		*(स्थिर काष्ठा probe_trace_event **)ptev2;

	ret = tev2->nargs - tev1->nargs;
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < tev1->nargs; i++) अणु
		काष्ठा probe_trace_arg *arg1, *arg2;
		काष्ठा probe_trace_arg_ref *ref1, *ref2;

		arg1 = &tev1->args[i];
		arg2 = &tev2->args[i];

		ret = म_भेद(arg1->value, arg2->value);
		अगर (ret)
			वापस ret;

		ref1 = arg1->ref;
		ref2 = arg2->ref;

		जबतक (ref1 && ref2) अणु
			ret = ref2->offset - ref1->offset;
			अगर (ret)
				वापस ret;

			ref1 = ref1->next;
			ref2 = ref2->next;
		पूर्ण

		अगर (ref1 || ref2)
			वापस ref2 ? 1 : -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Assign a type number to each tevs in a pev.
 * mapping is an array with same slots as tevs in that pev.
 * nr_types will be set to number of types.
 */
अटल पूर्णांक map_prologue(काष्ठा perf_probe_event *pev, पूर्णांक *mapping,
			पूर्णांक *nr_types)
अणु
	पूर्णांक i, type = 0;
	काष्ठा probe_trace_event **ptevs;

	माप_प्रकार array_sz = माप(*ptevs) * pev->ntevs;

	ptevs = दो_स्मृति(array_sz);
	अगर (!ptevs) अणु
		pr_debug("Not enough memory: alloc ptevs failed\n");
		वापस -ENOMEM;
	पूर्ण

	pr_debug("In map_prologue, ntevs=%d\n", pev->ntevs);
	क्रम (i = 0; i < pev->ntevs; i++)
		ptevs[i] = &pev->tevs[i];

	क्विक(ptevs, pev->ntevs, माप(*ptevs),
	      compare_tev_args);

	क्रम (i = 0; i < pev->ntevs; i++) अणु
		पूर्णांक n;

		n = ptevs[i] - pev->tevs;
		अगर (i == 0) अणु
			mapping[n] = type;
			pr_debug("mapping[%d]=%d\n", n, type);
			जारी;
		पूर्ण

		अगर (compare_tev_args(ptevs + i, ptevs + i - 1) == 0)
			mapping[n] = type;
		अन्यथा
			mapping[n] = ++type;

		pr_debug("mapping[%d]=%d\n", n, mapping[n]);
	पूर्ण
	मुक्त(ptevs);
	*nr_types = type + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक hook_load_preprocessor(काष्ठा bpf_program *prog)
अणु
	काष्ठा bpf_prog_priv *priv = bpf_program__priv(prog);
	काष्ठा perf_probe_event *pev;
	bool need_prologue = false;
	पूर्णांक err, i;

	अगर (IS_ERR(priv) || !priv) अणु
		pr_debug("Internal error when hook preprocessor\n");
		वापस -BPF_LOADER_ERRNO__INTERNAL;
	पूर्ण

	अगर (priv->is_tp) अणु
		priv->need_prologue = false;
		वापस 0;
	पूर्ण

	pev = &priv->pev;
	क्रम (i = 0; i < pev->ntevs; i++) अणु
		काष्ठा probe_trace_event *tev = &pev->tevs[i];

		अगर (tev->nargs > 0) अणु
			need_prologue = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Since all tevs करोn't have argument, we don't need generate
	 * prologue.
	 */
	अगर (!need_prologue) अणु
		priv->need_prologue = false;
		वापस 0;
	पूर्ण

	priv->need_prologue = true;
	priv->insns_buf = दो_स्मृति(माप(काष्ठा bpf_insn) * BPF_MAXINSNS);
	अगर (!priv->insns_buf) अणु
		pr_debug("Not enough memory: alloc insns_buf failed\n");
		वापस -ENOMEM;
	पूर्ण

	priv->type_mapping = दो_स्मृति(माप(पूर्णांक) * pev->ntevs);
	अगर (!priv->type_mapping) अणु
		pr_debug("Not enough memory: alloc type_mapping failed\n");
		वापस -ENOMEM;
	पूर्ण
	स_रखो(priv->type_mapping, -1,
	       माप(पूर्णांक) * pev->ntevs);

	err = map_prologue(pev, priv->type_mapping, &priv->nr_types);
	अगर (err)
		वापस err;

	err = bpf_program__set_prep(prog, priv->nr_types,
				    preproc_gen_prologue);
	वापस err;
पूर्ण

पूर्णांक bpf__probe(काष्ठा bpf_object *obj)
अणु
	पूर्णांक err = 0;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_prog_priv *priv;
	काष्ठा perf_probe_event *pev;

	err = bpf__prepare_probe();
	अगर (err) अणु
		pr_debug("bpf__prepare_probe failed\n");
		वापस err;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		err = config_bpf_program(prog);
		अगर (err)
			जाओ out;

		priv = bpf_program__priv(prog);
		अगर (IS_ERR(priv) || !priv) अणु
			err = PTR_ERR(priv);
			जाओ out;
		पूर्ण

		अगर (priv->is_tp) अणु
			bpf_program__set_tracepoपूर्णांक(prog);
			जारी;
		पूर्ण

		bpf_program__set_kprobe(prog);
		pev = &priv->pev;

		err = convert_perf_probe_events(pev, 1);
		अगर (err < 0) अणु
			pr_debug("bpf_probe: failed to convert perf probe events\n");
			जाओ out;
		पूर्ण

		err = apply_perf_probe_events(pev, 1);
		अगर (err < 0) अणु
			pr_debug("bpf_probe: failed to apply perf probe events\n");
			जाओ out;
		पूर्ण

		/*
		 * After probing, let's consider prologue, which
		 * adds program fetcher to BPF programs.
		 *
		 * hook_load_preprocessor() hooks pre-processor
		 * to bpf_program, let it generate prologue
		 * dynamically during loading.
		 */
		err = hook_load_preprocessor(prog);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	वापस err < 0 ? err : 0;
पूर्ण

#घोषणा EVENTS_WRITE_बफ_मानE  4096
पूर्णांक bpf__unprobe(काष्ठा bpf_object *obj)
अणु
	पूर्णांक err, ret = 0;
	काष्ठा bpf_program *prog;

	bpf_object__क्रम_each_program(prog, obj) अणु
		काष्ठा bpf_prog_priv *priv = bpf_program__priv(prog);
		पूर्णांक i;

		अगर (IS_ERR(priv) || !priv || priv->is_tp)
			जारी;

		क्रम (i = 0; i < priv->pev.ntevs; i++) अणु
			काष्ठा probe_trace_event *tev = &priv->pev.tevs[i];
			अक्षर name_buf[EVENTS_WRITE_बफ_मानE];
			काष्ठा strfilter *delfilter;

			snम_लिखो(name_buf, EVENTS_WRITE_बफ_मानE,
				 "%s:%s", tev->group, tev->event);
			name_buf[EVENTS_WRITE_बफ_मानE - 1] = '\0';

			delfilter = strfilter__new(name_buf, शून्य);
			अगर (!delfilter) अणु
				pr_debug("Failed to create filter for unprobing\n");
				ret = -ENOMEM;
				जारी;
			पूर्ण

			err = del_perf_probe_events(delfilter);
			strfilter__delete(delfilter);
			अगर (err) अणु
				pr_debug("Failed to delete %s\n", name_buf);
				ret = err;
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक bpf__load(काष्ठा bpf_object *obj)
अणु
	पूर्णांक err;

	err = bpf_object__load(obj);
	अगर (err) अणु
		अक्षर bf[128];
		libbpf_म_त्रुटि(err, bf, माप(bf));
		pr_debug("bpf: load objects failed: err=%d: (%s)\n", err, bf);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bpf__क्रमeach_event(काष्ठा bpf_object *obj,
		       bpf_prog_iter_callback_t func,
		       व्योम *arg)
अणु
	काष्ठा bpf_program *prog;
	पूर्णांक err;

	bpf_object__क्रम_each_program(prog, obj) अणु
		काष्ठा bpf_prog_priv *priv = bpf_program__priv(prog);
		काष्ठा probe_trace_event *tev;
		काष्ठा perf_probe_event *pev;
		पूर्णांक i, fd;

		अगर (IS_ERR(priv) || !priv) अणु
			pr_debug("bpf: failed to get private field\n");
			वापस -BPF_LOADER_ERRNO__INTERNAL;
		पूर्ण

		अगर (priv->is_tp) अणु
			fd = bpf_program__fd(prog);
			err = (*func)(priv->sys_name, priv->evt_name, fd, obj, arg);
			अगर (err) अणु
				pr_debug("bpf: tracepoint call back failed, stop iterate\n");
				वापस err;
			पूर्ण
			जारी;
		पूर्ण

		pev = &priv->pev;
		क्रम (i = 0; i < pev->ntevs; i++) अणु
			tev = &pev->tevs[i];

			अगर (priv->need_prologue) अणु
				पूर्णांक type = priv->type_mapping[i];

				fd = bpf_program__nth_fd(prog, type);
			पूर्ण अन्यथा अणु
				fd = bpf_program__fd(prog);
			पूर्ण

			अगर (fd < 0) अणु
				pr_debug("bpf: failed to get file descriptor\n");
				वापस fd;
			पूर्ण

			err = (*func)(tev->group, tev->event, fd, obj, arg);
			अगर (err) अणु
				pr_debug("bpf: call back failed, stop iterate\n");
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत bpf_map_op_type अणु
	BPF_MAP_OP_SET_VALUE,
	BPF_MAP_OP_SET_EVSEL,
पूर्ण;

क्रमागत bpf_map_key_type अणु
	BPF_MAP_KEY_ALL,
	BPF_MAP_KEY_RANGES,
पूर्ण;

काष्ठा bpf_map_op अणु
	काष्ठा list_head list;
	क्रमागत bpf_map_op_type op_type;
	क्रमागत bpf_map_key_type key_type;
	जोड़ अणु
		काष्ठा parse_events_array array;
	पूर्ण k;
	जोड़ अणु
		u64 value;
		काष्ठा evsel *evsel;
	पूर्ण v;
पूर्ण;

काष्ठा bpf_map_priv अणु
	काष्ठा list_head ops_list;
पूर्ण;

अटल व्योम
bpf_map_op__delete(काष्ठा bpf_map_op *op)
अणु
	अगर (!list_empty(&op->list))
		list_del_init(&op->list);
	अगर (op->key_type == BPF_MAP_KEY_RANGES)
		parse_events__clear_array(&op->k.array);
	मुक्त(op);
पूर्ण

अटल व्योम
bpf_map_priv__purge(काष्ठा bpf_map_priv *priv)
अणु
	काष्ठा bpf_map_op *pos, *n;

	list_क्रम_each_entry_safe(pos, n, &priv->ops_list, list) अणु
		list_del_init(&pos->list);
		bpf_map_op__delete(pos);
	पूर्ण
पूर्ण

अटल व्योम
bpf_map_priv__clear(काष्ठा bpf_map *map __maybe_unused,
		    व्योम *_priv)
अणु
	काष्ठा bpf_map_priv *priv = _priv;

	bpf_map_priv__purge(priv);
	मुक्त(priv);
पूर्ण

अटल पूर्णांक
bpf_map_op_setkey(काष्ठा bpf_map_op *op, काष्ठा parse_events_term *term)
अणु
	op->key_type = BPF_MAP_KEY_ALL;
	अगर (!term)
		वापस 0;

	अगर (term->array.nr_ranges) अणु
		माप_प्रकार memsz = term->array.nr_ranges *
				माप(op->k.array.ranges[0]);

		op->k.array.ranges = memdup(term->array.ranges, memsz);
		अगर (!op->k.array.ranges) अणु
			pr_debug("Not enough memory to alloc indices for map\n");
			वापस -ENOMEM;
		पूर्ण
		op->key_type = BPF_MAP_KEY_RANGES;
		op->k.array.nr_ranges = term->array.nr_ranges;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा bpf_map_op *
bpf_map_op__new(काष्ठा parse_events_term *term)
अणु
	काष्ठा bpf_map_op *op;
	पूर्णांक err;

	op = zalloc(माप(*op));
	अगर (!op) अणु
		pr_debug("Failed to alloc bpf_map_op\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	INIT_LIST_HEAD(&op->list);

	err = bpf_map_op_setkey(op, term);
	अगर (err) अणु
		मुक्त(op);
		वापस ERR_PTR(err);
	पूर्ण
	वापस op;
पूर्ण

अटल काष्ठा bpf_map_op *
bpf_map_op__clone(काष्ठा bpf_map_op *op)
अणु
	काष्ठा bpf_map_op *newop;

	newop = memdup(op, माप(*op));
	अगर (!newop) अणु
		pr_debug("Failed to alloc bpf_map_op\n");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&newop->list);
	अगर (op->key_type == BPF_MAP_KEY_RANGES) अणु
		माप_प्रकार memsz = op->k.array.nr_ranges *
			       माप(op->k.array.ranges[0]);

		newop->k.array.ranges = memdup(op->k.array.ranges, memsz);
		अगर (!newop->k.array.ranges) अणु
			pr_debug("Failed to alloc indices for map\n");
			मुक्त(newop);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस newop;
पूर्ण

अटल काष्ठा bpf_map_priv *
bpf_map_priv__clone(काष्ठा bpf_map_priv *priv)
अणु
	काष्ठा bpf_map_priv *newpriv;
	काष्ठा bpf_map_op *pos, *newop;

	newpriv = zalloc(माप(*newpriv));
	अगर (!newpriv) अणु
		pr_debug("Not enough memory to alloc map private\n");
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&newpriv->ops_list);

	list_क्रम_each_entry(pos, &priv->ops_list, list) अणु
		newop = bpf_map_op__clone(pos);
		अगर (!newop) अणु
			bpf_map_priv__purge(newpriv);
			वापस शून्य;
		पूर्ण
		list_add_tail(&newop->list, &newpriv->ops_list);
	पूर्ण

	वापस newpriv;
पूर्ण

अटल पूर्णांक
bpf_map__add_op(काष्ठा bpf_map *map, काष्ठा bpf_map_op *op)
अणु
	स्थिर अक्षर *map_name = bpf_map__name(map);
	काष्ठा bpf_map_priv *priv = bpf_map__priv(map);

	अगर (IS_ERR(priv)) अणु
		pr_debug("Failed to get private from map %s\n", map_name);
		वापस PTR_ERR(priv);
	पूर्ण

	अगर (!priv) अणु
		priv = zalloc(माप(*priv));
		अगर (!priv) अणु
			pr_debug("Not enough memory to alloc map private\n");
			वापस -ENOMEM;
		पूर्ण
		INIT_LIST_HEAD(&priv->ops_list);

		अगर (bpf_map__set_priv(map, priv, bpf_map_priv__clear)) अणु
			मुक्त(priv);
			वापस -BPF_LOADER_ERRNO__INTERNAL;
		पूर्ण
	पूर्ण

	list_add_tail(&op->list, &priv->ops_list);
	वापस 0;
पूर्ण

अटल काष्ठा bpf_map_op *
bpf_map__add_newop(काष्ठा bpf_map *map, काष्ठा parse_events_term *term)
अणु
	काष्ठा bpf_map_op *op;
	पूर्णांक err;

	op = bpf_map_op__new(term);
	अगर (IS_ERR(op))
		वापस op;

	err = bpf_map__add_op(map, op);
	अगर (err) अणु
		bpf_map_op__delete(op);
		वापस ERR_PTR(err);
	पूर्ण
	वापस op;
पूर्ण

अटल पूर्णांक
__bpf_map__config_value(काष्ठा bpf_map *map,
			काष्ठा parse_events_term *term)
अणु
	काष्ठा bpf_map_op *op;
	स्थिर अक्षर *map_name = bpf_map__name(map);
	स्थिर काष्ठा bpf_map_def *def = bpf_map__def(map);

	अगर (IS_ERR(def)) अणु
		pr_debug("Unable to get map definition from '%s'\n",
			 map_name);
		वापस -BPF_LOADER_ERRNO__INTERNAL;
	पूर्ण

	अगर (def->type != BPF_MAP_TYPE_ARRAY) अणु
		pr_debug("Map %s type is not BPF_MAP_TYPE_ARRAY\n",
			 map_name);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_TYPE;
	पूर्ण
	अगर (def->key_size < माप(अचिन्हित पूर्णांक)) अणु
		pr_debug("Map %s has incorrect key size\n", map_name);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_KEYSIZE;
	पूर्ण
	चयन (def->value_size) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		अवरोध;
	शेष:
		pr_debug("Map %s has incorrect value size\n", map_name);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_VALUESIZE;
	पूर्ण

	op = bpf_map__add_newop(map, term);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);
	op->op_type = BPF_MAP_OP_SET_VALUE;
	op->v.value = term->val.num;
	वापस 0;
पूर्ण

अटल पूर्णांक
bpf_map__config_value(काष्ठा bpf_map *map,
		      काष्ठा parse_events_term *term,
		      काष्ठा evlist *evlist __maybe_unused)
अणु
	अगर (!term->err_val) अणु
		pr_debug("Config value not set\n");
		वापस -BPF_LOADER_ERRNO__OBJCONF_CONF;
	पूर्ण

	अगर (term->type_val != PARSE_EVENTS__TERM_TYPE_NUM) अणु
		pr_debug("ERROR: wrong value type for 'value'\n");
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_VALUE;
	पूर्ण

	वापस __bpf_map__config_value(map, term);
पूर्ण

अटल पूर्णांक
__bpf_map__config_event(काष्ठा bpf_map *map,
			काष्ठा parse_events_term *term,
			काष्ठा evlist *evlist)
अणु
	स्थिर काष्ठा bpf_map_def *def;
	काष्ठा bpf_map_op *op;
	स्थिर अक्षर *map_name = bpf_map__name(map);
	काष्ठा evsel *evsel = evlist__find_evsel_by_str(evlist, term->val.str);

	अगर (!evsel) अणु
		pr_debug("Event (for '%s') '%s' doesn't exist\n",
			 map_name, term->val.str);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_NOEVT;
	पूर्ण

	def = bpf_map__def(map);
	अगर (IS_ERR(def)) अणु
		pr_debug("Unable to get map definition from '%s'\n",
			 map_name);
		वापस PTR_ERR(def);
	पूर्ण

	/*
	 * No need to check key_size and value_size:
	 * kernel has alपढ़ोy checked them.
	 */
	अगर (def->type != BPF_MAP_TYPE_PERF_EVENT_ARRAY) अणु
		pr_debug("Map %s type is not BPF_MAP_TYPE_PERF_EVENT_ARRAY\n",
			 map_name);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_TYPE;
	पूर्ण

	op = bpf_map__add_newop(map, term);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);
	op->op_type = BPF_MAP_OP_SET_EVSEL;
	op->v.evsel = evsel;
	वापस 0;
पूर्ण

अटल पूर्णांक
bpf_map__config_event(काष्ठा bpf_map *map,
		      काष्ठा parse_events_term *term,
		      काष्ठा evlist *evlist)
अणु
	अगर (!term->err_val) अणु
		pr_debug("Config value not set\n");
		वापस -BPF_LOADER_ERRNO__OBJCONF_CONF;
	पूर्ण

	अगर (term->type_val != PARSE_EVENTS__TERM_TYPE_STR) अणु
		pr_debug("ERROR: wrong value type for 'event'\n");
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_VALUE;
	पूर्ण

	वापस __bpf_map__config_event(map, term, evlist);
पूर्ण

काष्ठा bpf_obj_config__map_func अणु
	स्थिर अक्षर *config_opt;
	पूर्णांक (*config_func)(काष्ठा bpf_map *, काष्ठा parse_events_term *,
			   काष्ठा evlist *);
पूर्ण;

काष्ठा bpf_obj_config__map_func bpf_obj_config__map_funcs[] = अणु
	अणु"value", bpf_map__config_valueपूर्ण,
	अणु"event", bpf_map__config_eventपूर्ण,
पूर्ण;

अटल पूर्णांक
config_map_indices_range_check(काष्ठा parse_events_term *term,
			       काष्ठा bpf_map *map,
			       स्थिर अक्षर *map_name)
अणु
	काष्ठा parse_events_array *array = &term->array;
	स्थिर काष्ठा bpf_map_def *def;
	अचिन्हित पूर्णांक i;

	अगर (!array->nr_ranges)
		वापस 0;
	अगर (!array->ranges) अणु
		pr_debug("ERROR: map %s: array->nr_ranges is %d but range array is NULL\n",
			 map_name, (पूर्णांक)array->nr_ranges);
		वापस -BPF_LOADER_ERRNO__INTERNAL;
	पूर्ण

	def = bpf_map__def(map);
	अगर (IS_ERR(def)) अणु
		pr_debug("ERROR: Unable to get map definition from '%s'\n",
			 map_name);
		वापस -BPF_LOADER_ERRNO__INTERNAL;
	पूर्ण

	क्रम (i = 0; i < array->nr_ranges; i++) अणु
		अचिन्हित पूर्णांक start = array->ranges[i].start;
		माप_प्रकार length = array->ranges[i].length;
		अचिन्हित पूर्णांक idx = start + length - 1;

		अगर (idx >= def->max_entries) अणु
			pr_debug("ERROR: index %d too large\n", idx);
			वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_IDX2BIG;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bpf__obj_config_map(काष्ठा bpf_object *obj,
		    काष्ठा parse_events_term *term,
		    काष्ठा evlist *evlist,
		    पूर्णांक *key_scan_pos)
अणु
	/* key is "map:<mapname>.<config opt>" */
	अक्षर *map_name = strdup(term->config + माप("map:") - 1);
	काष्ठा bpf_map *map;
	पूर्णांक err = -BPF_LOADER_ERRNO__OBJCONF_OPT;
	अक्षर *map_opt;
	माप_प्रकार i;

	अगर (!map_name)
		वापस -ENOMEM;

	map_opt = म_अक्षर(map_name, '.');
	अगर (!map_opt) अणु
		pr_debug("ERROR: Invalid map config: %s\n", map_name);
		जाओ out;
	पूर्ण

	*map_opt++ = '\0';
	अगर (*map_opt == '\0') अणु
		pr_debug("ERROR: Invalid map option: %s\n", term->config);
		जाओ out;
	पूर्ण

	map = bpf_object__find_map_by_name(obj, map_name);
	अगर (!map) अणु
		pr_debug("ERROR: Map %s doesn't exist\n", map_name);
		err = -BPF_LOADER_ERRNO__OBJCONF_MAP_NOTEXIST;
		जाओ out;
	पूर्ण

	*key_scan_pos += म_माप(map_opt);
	err = config_map_indices_range_check(term, map, map_name);
	अगर (err)
		जाओ out;
	*key_scan_pos -= म_माप(map_opt);

	क्रम (i = 0; i < ARRAY_SIZE(bpf_obj_config__map_funcs); i++) अणु
		काष्ठा bpf_obj_config__map_func *func =
				&bpf_obj_config__map_funcs[i];

		अगर (म_भेद(map_opt, func->config_opt) == 0) अणु
			err = func->config_func(map, term, evlist);
			जाओ out;
		पूर्ण
	पूर्ण

	pr_debug("ERROR: Invalid map config option '%s'\n", map_opt);
	err = -BPF_LOADER_ERRNO__OBJCONF_MAP_OPT;
out:
	मुक्त(map_name);
	अगर (!err)
		*key_scan_pos += म_माप(map_opt);
	वापस err;
पूर्ण

पूर्णांक bpf__config_obj(काष्ठा bpf_object *obj,
		    काष्ठा parse_events_term *term,
		    काष्ठा evlist *evlist,
		    पूर्णांक *error_pos)
अणु
	पूर्णांक key_scan_pos = 0;
	पूर्णांक err;

	अगर (!obj || !term || !term->config)
		वापस -EINVAL;

	अगर (strstarts(term->config, "map:")) अणु
		key_scan_pos = माप("map:") - 1;
		err = bpf__obj_config_map(obj, term, evlist, &key_scan_pos);
		जाओ out;
	पूर्ण
	err = -BPF_LOADER_ERRNO__OBJCONF_OPT;
out:
	अगर (error_pos)
		*error_pos = key_scan_pos;
	वापस err;

पूर्ण

प्रकार पूर्णांक (*map_config_func_t)(स्थिर अक्षर *name, पूर्णांक map_fd,
				 स्थिर काष्ठा bpf_map_def *pdef,
				 काष्ठा bpf_map_op *op,
				 व्योम *pkey, व्योम *arg);

अटल पूर्णांक
क्रमeach_key_array_all(map_config_func_t func,
		      व्योम *arg, स्थिर अक्षर *name,
		      पूर्णांक map_fd, स्थिर काष्ठा bpf_map_def *pdef,
		      काष्ठा bpf_map_op *op)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < pdef->max_entries; i++) अणु
		err = func(name, map_fd, pdef, op, &i, arg);
		अगर (err) अणु
			pr_debug("ERROR: failed to insert value to %s[%u]\n",
				 name, i);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
क्रमeach_key_array_ranges(map_config_func_t func, व्योम *arg,
			 स्थिर अक्षर *name, पूर्णांक map_fd,
			 स्थिर काष्ठा bpf_map_def *pdef,
			 काष्ठा bpf_map_op *op)
अणु
	अचिन्हित पूर्णांक i, j;
	पूर्णांक err;

	क्रम (i = 0; i < op->k.array.nr_ranges; i++) अणु
		अचिन्हित पूर्णांक start = op->k.array.ranges[i].start;
		माप_प्रकार length = op->k.array.ranges[i].length;

		क्रम (j = 0; j < length; j++) अणु
			अचिन्हित पूर्णांक idx = start + j;

			err = func(name, map_fd, pdef, op, &idx, arg);
			अगर (err) अणु
				pr_debug("ERROR: failed to insert value to %s[%u]\n",
					 name, idx);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bpf_map_config_क्रमeach_key(काष्ठा bpf_map *map,
			   map_config_func_t func,
			   व्योम *arg)
अणु
	पूर्णांक err, map_fd;
	काष्ठा bpf_map_op *op;
	स्थिर काष्ठा bpf_map_def *def;
	स्थिर अक्षर *name = bpf_map__name(map);
	काष्ठा bpf_map_priv *priv = bpf_map__priv(map);

	अगर (IS_ERR(priv)) अणु
		pr_debug("ERROR: failed to get private from map %s\n", name);
		वापस -BPF_LOADER_ERRNO__INTERNAL;
	पूर्ण
	अगर (!priv || list_empty(&priv->ops_list)) अणु
		pr_debug("INFO: nothing to config for map %s\n", name);
		वापस 0;
	पूर्ण

	def = bpf_map__def(map);
	अगर (IS_ERR(def)) अणु
		pr_debug("ERROR: failed to get definition from map %s\n", name);
		वापस -BPF_LOADER_ERRNO__INTERNAL;
	पूर्ण
	map_fd = bpf_map__fd(map);
	अगर (map_fd < 0) अणु
		pr_debug("ERROR: failed to get fd from map %s\n", name);
		वापस map_fd;
	पूर्ण

	list_क्रम_each_entry(op, &priv->ops_list, list) अणु
		चयन (def->type) अणु
		हाल BPF_MAP_TYPE_ARRAY:
		हाल BPF_MAP_TYPE_PERF_EVENT_ARRAY:
			चयन (op->key_type) अणु
			हाल BPF_MAP_KEY_ALL:
				err = क्रमeach_key_array_all(func, arg, name,
							    map_fd, def, op);
				अवरोध;
			हाल BPF_MAP_KEY_RANGES:
				err = क्रमeach_key_array_ranges(func, arg, name,
							       map_fd, def,
							       op);
				अवरोध;
			शेष:
				pr_debug("ERROR: keytype for map '%s' invalid\n",
					 name);
				वापस -BPF_LOADER_ERRNO__INTERNAL;
			पूर्ण
			अगर (err)
				वापस err;
			अवरोध;
		शेष:
			pr_debug("ERROR: type of '%s' incorrect\n", name);
			वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_TYPE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
apply_config_value_क्रम_key(पूर्णांक map_fd, व्योम *pkey,
			   माप_प्रकार val_size, u64 val)
अणु
	पूर्णांक err = 0;

	चयन (val_size) अणु
	हाल 1: अणु
		u8 _val = (u8)(val);
		err = bpf_map_update_elem(map_fd, pkey, &_val, BPF_ANY);
		अवरोध;
	पूर्ण
	हाल 2: अणु
		u16 _val = (u16)(val);
		err = bpf_map_update_elem(map_fd, pkey, &_val, BPF_ANY);
		अवरोध;
	पूर्ण
	हाल 4: अणु
		u32 _val = (u32)(val);
		err = bpf_map_update_elem(map_fd, pkey, &_val, BPF_ANY);
		अवरोध;
	पूर्ण
	हाल 8: अणु
		err = bpf_map_update_elem(map_fd, pkey, &val, BPF_ANY);
		अवरोध;
	पूर्ण
	शेष:
		pr_debug("ERROR: invalid value size\n");
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_VALUESIZE;
	पूर्ण
	अगर (err && त्रुटि_सं)
		err = -त्रुटि_सं;
	वापस err;
पूर्ण

अटल पूर्णांक
apply_config_evsel_क्रम_key(स्थिर अक्षर *name, पूर्णांक map_fd, व्योम *pkey,
			   काष्ठा evsel *evsel)
अणु
	काष्ठा xyarray *xy = evsel->core.fd;
	काष्ठा perf_event_attr *attr;
	अचिन्हित पूर्णांक key, events;
	bool check_pass = false;
	पूर्णांक *evt_fd;
	पूर्णांक err;

	अगर (!xy) अणु
		pr_debug("ERROR: evsel not ready for map %s\n", name);
		वापस -BPF_LOADER_ERRNO__INTERNAL;
	पूर्ण

	अगर (xy->row_size / xy->entry_size != 1) अणु
		pr_debug("ERROR: Dimension of target event is incorrect for map %s\n",
			 name);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_EVTDIM;
	पूर्ण

	attr = &evsel->core.attr;
	अगर (attr->inherit) अणु
		pr_debug("ERROR: Can't put inherit event into map %s\n", name);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_EVTINH;
	पूर्ण

	अगर (evsel__is_bpf_output(evsel))
		check_pass = true;
	अगर (attr->type == PERF_TYPE_RAW)
		check_pass = true;
	अगर (attr->type == PERF_TYPE_HARDWARE)
		check_pass = true;
	अगर (!check_pass) अणु
		pr_debug("ERROR: Event type is wrong for map %s\n", name);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_EVTTYPE;
	पूर्ण

	events = xy->entries / (xy->row_size / xy->entry_size);
	key = *((अचिन्हित पूर्णांक *)pkey);
	अगर (key >= events) अणु
		pr_debug("ERROR: there is no event %d for map %s\n",
			 key, name);
		वापस -BPF_LOADER_ERRNO__OBJCONF_MAP_MAPSIZE;
	पूर्ण
	evt_fd = xyarray__entry(xy, key, 0);
	err = bpf_map_update_elem(map_fd, pkey, evt_fd, BPF_ANY);
	अगर (err && त्रुटि_सं)
		err = -त्रुटि_सं;
	वापस err;
पूर्ण

अटल पूर्णांक
apply_obj_config_map_क्रम_key(स्थिर अक्षर *name, पूर्णांक map_fd,
			     स्थिर काष्ठा bpf_map_def *pdef,
			     काष्ठा bpf_map_op *op,
			     व्योम *pkey, व्योम *arg __maybe_unused)
अणु
	पूर्णांक err;

	चयन (op->op_type) अणु
	हाल BPF_MAP_OP_SET_VALUE:
		err = apply_config_value_क्रम_key(map_fd, pkey,
						 pdef->value_size,
						 op->v.value);
		अवरोध;
	हाल BPF_MAP_OP_SET_EVSEL:
		err = apply_config_evsel_क्रम_key(name, map_fd, pkey,
						 op->v.evsel);
		अवरोध;
	शेष:
		pr_debug("ERROR: unknown value type for '%s'\n", name);
		err = -BPF_LOADER_ERRNO__INTERNAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
apply_obj_config_map(काष्ठा bpf_map *map)
अणु
	वापस bpf_map_config_क्रमeach_key(map,
					  apply_obj_config_map_क्रम_key,
					  शून्य);
पूर्ण

अटल पूर्णांक
apply_obj_config_object(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_map *map;
	पूर्णांक err;

	bpf_object__क्रम_each_map(map, obj) अणु
		err = apply_obj_config_map(map);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bpf__apply_obj_config(व्योम)
अणु
	काष्ठा bpf_object *obj, *पंचांगp;
	पूर्णांक err;

	bpf_object__क्रम_each_safe(obj, पंचांगp) अणु
		err = apply_obj_config_object(obj);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा bpf__क्रम_each_map(pos, obj, objपंचांगp)	\
	bpf_object__क्रम_each_safe(obj, objपंचांगp)	\
		bpf_object__क्रम_each_map(pos, obj)

#घोषणा bpf__क्रम_each_map_named(pos, obj, objपंचांगp, name)	\
	bpf__क्रम_each_map(pos, obj, objपंचांगp) 		\
		अगर (bpf_map__name(pos) && 		\
			(म_भेद(name, 			\
				bpf_map__name(pos)) == 0))

काष्ठा evsel *bpf__setup_output_event(काष्ठा evlist *evlist, स्थिर अक्षर *name)
अणु
	काष्ठा bpf_map_priv *पंचांगpl_priv = शून्य;
	काष्ठा bpf_object *obj, *पंचांगp;
	काष्ठा evsel *evsel = शून्य;
	काष्ठा bpf_map *map;
	पूर्णांक err;
	bool need_init = false;

	bpf__क्रम_each_map_named(map, obj, पंचांगp, name) अणु
		काष्ठा bpf_map_priv *priv = bpf_map__priv(map);

		अगर (IS_ERR(priv))
			वापस ERR_PTR(-BPF_LOADER_ERRNO__INTERNAL);

		/*
		 * No need to check map type: type should have been
		 * verअगरied by kernel.
		 */
		अगर (!need_init && !priv)
			need_init = !priv;
		अगर (!पंचांगpl_priv && priv)
			पंचांगpl_priv = priv;
	पूर्ण

	अगर (!need_init)
		वापस शून्य;

	अगर (!पंचांगpl_priv) अणु
		अक्षर *event_definition = शून्य;

		अगर (aप्र_लिखो(&event_definition, "bpf-output/no-inherit=1,name=%s/", name) < 0)
			वापस ERR_PTR(-ENOMEM);

		err = parse_events(evlist, event_definition, शून्य);
		मुक्त(event_definition);

		अगर (err) अणु
			pr_debug("ERROR: failed to create the \"%s\" bpf-output event\n", name);
			वापस ERR_PTR(-err);
		पूर्ण

		evsel = evlist__last(evlist);
	पूर्ण

	bpf__क्रम_each_map_named(map, obj, पंचांगp, name) अणु
		काष्ठा bpf_map_priv *priv = bpf_map__priv(map);

		अगर (IS_ERR(priv))
			वापस ERR_PTR(-BPF_LOADER_ERRNO__INTERNAL);
		अगर (priv)
			जारी;

		अगर (पंचांगpl_priv) अणु
			priv = bpf_map_priv__clone(पंचांगpl_priv);
			अगर (!priv)
				वापस ERR_PTR(-ENOMEM);

			err = bpf_map__set_priv(map, priv, bpf_map_priv__clear);
			अगर (err) अणु
				bpf_map_priv__clear(map, priv);
				वापस ERR_PTR(err);
			पूर्ण
		पूर्ण अन्यथा अगर (evsel) अणु
			काष्ठा bpf_map_op *op;

			op = bpf_map__add_newop(map, शून्य);
			अगर (IS_ERR(op))
				वापस ERR_CAST(op);
			op->op_type = BPF_MAP_OP_SET_EVSEL;
			op->v.evsel = evsel;
		पूर्ण
	पूर्ण

	वापस evsel;
पूर्ण

पूर्णांक bpf__setup_मानक_निकास(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = bpf__setup_output_event(evlist, "__bpf_stdout__");
	वापस PTR_ERR_OR_ZERO(evsel);
पूर्ण

#घोषणा ERRNO_OFFSET(e)		((e) - __BPF_LOADER_ERRNO__START)
#घोषणा ERRCODE_OFFSET(c)	ERRNO_OFFSET(BPF_LOADER_ERRNO__##c)
#घोषणा NR_ERRNO	(__BPF_LOADER_ERRNO__END - __BPF_LOADER_ERRNO__START)

अटल स्थिर अक्षर *bpf_loader_म_त्रुटि_table[NR_ERRNO] = अणु
	[ERRCODE_OFFSET(CONFIG)]	= "Invalid config string",
	[ERRCODE_OFFSET(GROUP)]		= "Invalid group name",
	[ERRCODE_OFFSET(EVENTNAME)]	= "No event name found in config string",
	[ERRCODE_OFFSET(INTERNAL)]	= "BPF loader internal error",
	[ERRCODE_OFFSET(COMPILE)]	= "Error when compiling BPF scriptlet",
	[ERRCODE_OFFSET(PROGCONF_TERM)]	= "Invalid program config term in config string",
	[ERRCODE_OFFSET(PROLOGUE)]	= "Failed to generate prologue",
	[ERRCODE_OFFSET(PROLOGUE2BIG)]	= "Prologue too big for program",
	[ERRCODE_OFFSET(PROLOGUEOOB)]	= "Offset out of bound for prologue",
	[ERRCODE_OFFSET(OBJCONF_OPT)]	= "Invalid object config option",
	[ERRCODE_OFFSET(OBJCONF_CONF)]	= "Config value not set (missing '=')",
	[ERRCODE_OFFSET(OBJCONF_MAP_OPT)]	= "Invalid object map config option",
	[ERRCODE_OFFSET(OBJCONF_MAP_NOTEXIST)]	= "Target map doesn't exist",
	[ERRCODE_OFFSET(OBJCONF_MAP_VALUE)]	= "Incorrect value type for map",
	[ERRCODE_OFFSET(OBJCONF_MAP_TYPE)]	= "Incorrect map type",
	[ERRCODE_OFFSET(OBJCONF_MAP_KEYSIZE)]	= "Incorrect map key size",
	[ERRCODE_OFFSET(OBJCONF_MAP_VALUESIZE)]	= "Incorrect map value size",
	[ERRCODE_OFFSET(OBJCONF_MAP_NOEVT)]	= "Event not found for map setting",
	[ERRCODE_OFFSET(OBJCONF_MAP_MAPSIZE)]	= "Invalid map size for event setting",
	[ERRCODE_OFFSET(OBJCONF_MAP_EVTDIM)]	= "Event dimension too large",
	[ERRCODE_OFFSET(OBJCONF_MAP_EVTINH)]	= "Doesn't support inherit event",
	[ERRCODE_OFFSET(OBJCONF_MAP_EVTTYPE)]	= "Wrong event type for map",
	[ERRCODE_OFFSET(OBJCONF_MAP_IDX2BIG)]	= "Index too large",
पूर्ण;

अटल पूर्णांक
bpf_loader_म_त्रुटि(पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर sbuf[STRERR_बफ_मानE];
	स्थिर अक्षर *msg;

	अगर (!buf || !size)
		वापस -1;

	err = err > 0 ? err : -err;

	अगर (err >= __LIBBPF_ERRNO__START)
		वापस libbpf_म_त्रुटि(err, buf, size);

	अगर (err >= __BPF_LOADER_ERRNO__START && err < __BPF_LOADER_ERRNO__END) अणु
		msg = bpf_loader_म_त्रुटि_table[ERRNO_OFFSET(err)];
		snम_लिखो(buf, size, "%s", msg);
		buf[size - 1] = '\0';
		वापस 0;
	पूर्ण

	अगर (err >= __BPF_LOADER_ERRNO__END)
		snम_लिखो(buf, size, "Unknown bpf loader error %d", err);
	अन्यथा
		snम_लिखो(buf, size, "%s",
			 str_error_r(err, sbuf, माप(sbuf)));

	buf[size - 1] = '\0';
	वापस -1;
पूर्ण

#घोषणा bpf__म_त्रुटि_head(err, buf, size) \
	अक्षर sbuf[STRERR_बफ_मानE], *emsg;\
	अगर (!size)\
		वापस 0;\
	अगर (err < 0)\
		err = -err;\
	bpf_loader_म_त्रुटि(err, sbuf, माप(sbuf));\
	emsg = sbuf;\
	चयन (err) अणु\
	शेष:\
		scnम_लिखो(buf, size, "%s", emsg);\
		अवरोध;

#घोषणा bpf__म_त्रुटि_entry(val, fmt...)\
	हाल val: अणु\
		scnम_लिखो(buf, size, fmt);\
		अवरोध;\
	पूर्ण

#घोषणा bpf__म_त्रुटि_end(buf, size)\
	पूर्ण\
	buf[size - 1] = '\0';

पूर्णांक bpf__म_त्रुटि_prepare_load(स्थिर अक्षर *filename, bool source,
			       पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	माप_प्रकार n;
	पूर्णांक ret;

	n = snम_लिखो(buf, size, "Failed to load %s%s: ",
			 filename, source ? " from source" : "");
	अगर (n >= size) अणु
		buf[size - 1] = '\0';
		वापस 0;
	पूर्ण
	buf += n;
	size -= n;

	ret = bpf_loader_म_त्रुटि(err, buf, size);
	buf[size - 1] = '\0';
	वापस ret;
पूर्ण

पूर्णांक bpf__म_त्रुटि_probe(काष्ठा bpf_object *obj __maybe_unused,
			पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	bpf__म_त्रुटि_head(err, buf, size);
	हाल BPF_LOADER_ERRNO__PROGCONF_TERM: अणु
		scnम_लिखो(buf, size, "%s (add -v to see detail)", emsg);
		अवरोध;
	पूर्ण
	bpf__म_त्रुटि_entry(EEXIST, "Probe point exist. Try 'perf probe -d \"*\"' and set 'force=yes'");
	bpf__म_त्रुटि_entry(EACCES, "You need to be root");
	bpf__म_त्रुटि_entry(EPERM, "You need to be root, and /proc/sys/kernel/kptr_restrict should be 0");
	bpf__म_त्रुटि_entry(ENOENT, "You need to check probing points in BPF file");
	bpf__म_त्रुटि_end(buf, size);
	वापस 0;
पूर्ण

पूर्णांक bpf__म_त्रुटि_load(काष्ठा bpf_object *obj,
		       पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	bpf__म_त्रुटि_head(err, buf, size);
	हाल LIBBPF_ERRNO__KVER: अणु
		अचिन्हित पूर्णांक obj_kver = bpf_object__kversion(obj);
		अचिन्हित पूर्णांक real_kver;

		अगर (fetch_kernel_version(&real_kver, शून्य, 0)) अणु
			scnम_लिखो(buf, size, "Unable to fetch kernel version");
			अवरोध;
		पूर्ण

		अगर (obj_kver != real_kver) अणु
			scnम_लिखो(buf, size,
				  "'version' ("KVER_FMT") doesn't match running kernel ("KVER_FMT")",
				  KVER_PARAM(obj_kver),
				  KVER_PARAM(real_kver));
			अवरोध;
		पूर्ण

		scnम_लिखो(buf, size, "Failed to load program for unknown reason");
		अवरोध;
	पूर्ण
	bpf__म_त्रुटि_end(buf, size);
	वापस 0;
पूर्ण

पूर्णांक bpf__म_त्रुटि_config_obj(काष्ठा bpf_object *obj __maybe_unused,
			     काष्ठा parse_events_term *term __maybe_unused,
			     काष्ठा evlist *evlist __maybe_unused,
			     पूर्णांक *error_pos __maybe_unused, पूर्णांक err,
			     अक्षर *buf, माप_प्रकार size)
अणु
	bpf__म_त्रुटि_head(err, buf, size);
	bpf__म_त्रुटि_entry(BPF_LOADER_ERRNO__OBJCONF_MAP_TYPE,
			    "Can't use this config term with this map type");
	bpf__म_त्रुटि_end(buf, size);
	वापस 0;
पूर्ण

पूर्णांक bpf__म_त्रुटि_apply_obj_config(पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	bpf__म_त्रुटि_head(err, buf, size);
	bpf__म_त्रुटि_entry(BPF_LOADER_ERRNO__OBJCONF_MAP_EVTDIM,
			    "Cannot set event to BPF map in multi-thread tracing");
	bpf__म_त्रुटि_entry(BPF_LOADER_ERRNO__OBJCONF_MAP_EVTINH,
			    "%s (Hint: use -i to turn off inherit)", emsg);
	bpf__म_त्रुटि_entry(BPF_LOADER_ERRNO__OBJCONF_MAP_EVTTYPE,
			    "Can only put raw, hardware and BPF output event into a BPF map");
	bpf__म_त्रुटि_end(buf, size);
	वापस 0;
पूर्ण

पूर्णांक bpf__म_त्रुटि_setup_output_event(काष्ठा evlist *evlist __maybe_unused,
				     पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	bpf__म_त्रुटि_head(err, buf, size);
	bpf__म_त्रुटि_end(buf, size);
	वापस 0;
पूर्ण
