<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>

अटल पूर्णांक s390_call__parse(काष्ठा arch *arch, काष्ठा ins_opeअक्रमs *ops,
			    काष्ठा map_symbol *ms)
अणु
	अक्षर *endptr, *tok, *name;
	काष्ठा map *map = ms->map;
	काष्ठा addr_map_symbol target = अणु
		.ms = अणु .map = map, पूर्ण,
	पूर्ण;

	tok = म_अक्षर(ops->raw, ',');
	अगर (!tok)
		वापस -1;

	ops->target.addr = म_से_अदीर्घl(tok + 1, &endptr, 16);

	name = म_अक्षर(endptr, '<');
	अगर (name == शून्य)
		वापस -1;

	name++;

	अगर (arch->objdump.skip_functions_अक्षर &&
	    म_अक्षर(name, arch->objdump.skip_functions_अक्षर))
		वापस -1;

	tok = म_अक्षर(name, '>');
	अगर (tok == शून्य)
		वापस -1;

	*tok = '\0';
	ops->target.name = strdup(name);
	*tok = '>';

	अगर (ops->target.name == शून्य)
		वापस -1;
	target.addr = map__objdump_2mem(map, ops->target.addr);

	अगर (maps__find_ams(ms->maps, &target) == 0 &&
	    map__rip_2objdump(target.ms.map, map->map_ip(target.ms.map, target.addr)) == ops->target.addr)
		ops->target.sym = target.ms.sym;

	वापस 0;
पूर्ण

अटल पूर्णांक call__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			   काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name);

अटल काष्ठा ins_ops s390_call_ops = अणु
	.parse	   = s390_call__parse,
	.scnम_लिखो = call__scnम_लिखो,
पूर्ण;

अटल पूर्णांक s390_mov__parse(काष्ठा arch *arch __maybe_unused,
			   काष्ठा ins_opeअक्रमs *ops,
			   काष्ठा map_symbol *ms __maybe_unused)
अणु
	अक्षर *s = म_अक्षर(ops->raw, ','), *target, *endptr;

	अगर (s == शून्य)
		वापस -1;

	*s = '\0';
	ops->source.raw = strdup(ops->raw);
	*s = ',';

	अगर (ops->source.raw == शून्य)
		वापस -1;

	target = ++s;
	ops->target.raw = strdup(target);
	अगर (ops->target.raw == शून्य)
		जाओ out_मुक्त_source;

	ops->target.addr = म_से_अदीर्घl(target, &endptr, 16);
	अगर (endptr == target)
		जाओ out_मुक्त_target;

	s = म_अक्षर(endptr, '<');
	अगर (s == शून्य)
		जाओ out_मुक्त_target;
	endptr = म_अक्षर(s + 1, '>');
	अगर (endptr == शून्य)
		जाओ out_मुक्त_target;

	*endptr = '\0';
	ops->target.name = strdup(s + 1);
	*endptr = '>';
	अगर (ops->target.name == शून्य)
		जाओ out_मुक्त_target;

	वापस 0;

out_मुक्त_target:
	zमुक्त(&ops->target.raw);
out_मुक्त_source:
	zमुक्त(&ops->source.raw);
	वापस -1;
पूर्ण


अटल काष्ठा ins_ops s390_mov_ops = अणु
	.parse	   = s390_mov__parse,
	.scnम_लिखो = mov__scnम_लिखो,
पूर्ण;

अटल काष्ठा ins_ops *s390__associate_ins_ops(काष्ठा arch *arch, स्थिर अक्षर *name)
अणु
	काष्ठा ins_ops *ops = शून्य;

	/* catch all kind of jumps */
	अगर (म_अक्षर(name, 'j') ||
	    !म_भेदन(name, "bct", 3) ||
	    !म_भेदन(name, "br", 2))
		ops = &jump_ops;
	/* override call/वापसs */
	अगर (!म_भेद(name, "bras") ||
	    !म_भेद(name, "brasl") ||
	    !म_भेद(name, "basr"))
		ops = &s390_call_ops;
	अगर (!म_भेद(name, "br"))
		ops = &ret_ops;
	/* override load/store relative to PC */
	अगर (!म_भेद(name, "lrl") ||
	    !म_भेद(name, "lgrl") ||
	    !म_भेद(name, "lgfrl") ||
	    !म_भेद(name, "llgfrl") ||
	    !म_भेद(name, "strl") ||
	    !म_भेद(name, "stgrl"))
		ops = &s390_mov_ops;

	अगर (ops)
		arch__associate_ins_ops(arch, name, ops);
	वापस ops;
पूर्ण

अटल पूर्णांक s390__cpuid_parse(काष्ठा arch *arch, अक्षर *cpuid)
अणु
	अचिन्हित पूर्णांक family;
	अक्षर model[16], model_c[16], cpumf_v[16], cpumf_a[16];
	पूर्णांक ret;

	/*
	 * cpuid string क्रमmat:
	 * "IBM,family,model-capacity,model[,cpum_cf-version,cpum_cf-authorization]"
	 */
	ret = माला_पूछो(cpuid, "%*[^,],%u,%[^,],%[^,],%[^,],%s", &family, model_c,
		     model, cpumf_v, cpumf_a);
	अगर (ret >= 2) अणु
		arch->family = family;
		arch->model = 0;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक s390__annotate_init(काष्ठा arch *arch, अक्षर *cpuid __maybe_unused)
अणु
	पूर्णांक err = 0;

	अगर (!arch->initialized) अणु
		arch->initialized = true;
		arch->associate_inकाष्ठाion_ops = s390__associate_ins_ops;
		अगर (cpuid) अणु
			अगर (s390__cpuid_parse(arch, cpuid))
				err = SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_CPUID_PARSING;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण
