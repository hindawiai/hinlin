<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Parts came from builtin-annotate.c, see those files क्रम further
 * copyright notes.
 */

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <libgen.h>
#समावेश <मानककोष.स>
#समावेश "util.h" // hex_width()
#समावेश "ui/ui.h"
#समावेश "sort.h"
#समावेश "build-id.h"
#समावेश "color.h"
#समावेश "config.h"
#समावेश "dso.h"
#समावेश "env.h"
#समावेश "map.h"
#समावेश "maps.h"
#समावेश "symbol.h"
#समावेश "srcline.h"
#समावेश "units.h"
#समावेश "debug.h"
#समावेश "annotate.h"
#समावेश "evsel.h"
#समावेश "evlist.h"
#समावेश "bpf-event.h"
#समावेश "block-range.h"
#समावेश "string2.h"
#समावेश "util/event.h"
#समावेश "arch/common.h"
#समावेश <regex.h>
#समावेश <pthपढ़ो.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <subcmd/parse-options.h>
#समावेश <subcmd/run-command.h>

/* FIXME: For the HE_COLORSET */
#समावेश "ui/browser.h"

/*
 * FIXME: Using the same values as slang.h,
 * but that header may not be available everywhere
 */
#घोषणा LARROW_CHAR	((अचिन्हित अक्षर)',')
#घोषणा RARROW_CHAR	((अचिन्हित अक्षर)'+')
#घोषणा DARROW_CHAR	((अचिन्हित अक्षर)'.')
#घोषणा UARROW_CHAR	((अचिन्हित अक्षर)'-')

#समावेश <linux/प्रकार.स>

काष्ठा annotation_options annotation__शेष_options = अणु
	.use_offset     = true,
	.jump_arrows    = true,
	.annotate_src	= true,
	.offset_level	= ANNOTATION__OFFSET_JUMP_TARGETS,
	.percent_type	= PERCENT_PERIOD_LOCAL,
पूर्ण;

अटल regex_t	 file_lineno;

अटल काष्ठा ins_ops *ins__find(काष्ठा arch *arch, स्थिर अक्षर *name);
अटल व्योम ins__sort(काष्ठा arch *arch);
अटल पूर्णांक disयंत्र_line__parse(अक्षर *line, स्थिर अक्षर **namep, अक्षर **rawp);

काष्ठा arch अणु
	स्थिर अक्षर	*name;
	काष्ठा ins	*inकाष्ठाions;
	माप_प्रकार		nr_inकाष्ठाions;
	माप_प्रकार		nr_inकाष्ठाions_allocated;
	काष्ठा ins_ops  *(*associate_inकाष्ठाion_ops)(काष्ठा arch *arch, स्थिर अक्षर *name);
	bool		sorted_inकाष्ठाions;
	bool		initialized;
	व्योम		*priv;
	अचिन्हित पूर्णांक	model;
	अचिन्हित पूर्णांक	family;
	पूर्णांक		(*init)(काष्ठा arch *arch, अक्षर *cpuid);
	bool		(*ins_is_fused)(काष्ठा arch *arch, स्थिर अक्षर *ins1,
					स्थिर अक्षर *ins2);
	काष्ठा		अणु
		अक्षर comment_अक्षर;
		अक्षर skip_functions_अक्षर;
	पूर्ण objdump;
पूर्ण;

अटल काष्ठा ins_ops call_ops;
अटल काष्ठा ins_ops dec_ops;
अटल काष्ठा ins_ops jump_ops;
अटल काष्ठा ins_ops mov_ops;
अटल काष्ठा ins_ops nop_ops;
अटल काष्ठा ins_ops lock_ops;
अटल काष्ठा ins_ops ret_ops;

अटल पूर्णांक arch__grow_inकाष्ठाions(काष्ठा arch *arch)
अणु
	काष्ठा ins *new_inकाष्ठाions;
	माप_प्रकार new_nr_allocated;

	अगर (arch->nr_inकाष्ठाions_allocated == 0 && arch->inकाष्ठाions)
		जाओ grow_from_non_allocated_table;

	new_nr_allocated = arch->nr_inकाष्ठाions_allocated + 128;
	new_inकाष्ठाions = पुनः_स्मृति(arch->inकाष्ठाions, new_nr_allocated * माप(काष्ठा ins));
	अगर (new_inकाष्ठाions == शून्य)
		वापस -1;

out_update_inकाष्ठाions:
	arch->inकाष्ठाions = new_inकाष्ठाions;
	arch->nr_inकाष्ठाions_allocated = new_nr_allocated;
	वापस 0;

grow_from_non_allocated_table:
	new_nr_allocated = arch->nr_inकाष्ठाions + 128;
	new_inकाष्ठाions = सुस्मृति(new_nr_allocated, माप(काष्ठा ins));
	अगर (new_inकाष्ठाions == शून्य)
		वापस -1;

	स_नकल(new_inकाष्ठाions, arch->inकाष्ठाions, arch->nr_inकाष्ठाions);
	जाओ out_update_inकाष्ठाions;
पूर्ण

अटल पूर्णांक arch__associate_ins_ops(काष्ठा arch* arch, स्थिर अक्षर *name, काष्ठा ins_ops *ops)
अणु
	काष्ठा ins *ins;

	अगर (arch->nr_inकाष्ठाions == arch->nr_inकाष्ठाions_allocated &&
	    arch__grow_inकाष्ठाions(arch))
		वापस -1;

	ins = &arch->inकाष्ठाions[arch->nr_inकाष्ठाions];
	ins->name = strdup(name);
	अगर (!ins->name)
		वापस -1;

	ins->ops  = ops;
	arch->nr_inकाष्ठाions++;

	ins__sort(arch);
	वापस 0;
पूर्ण

#समावेश "arch/arc/annotate/instructions.c"
#समावेश "arch/arm/annotate/instructions.c"
#समावेश "arch/arm64/annotate/instructions.c"
#समावेश "arch/csky/annotate/instructions.c"
#समावेश "arch/mips/annotate/instructions.c"
#समावेश "arch/x86/annotate/instructions.c"
#समावेश "arch/powerpc/annotate/instructions.c"
#समावेश "arch/s390/annotate/instructions.c"
#समावेश "arch/sparc/annotate/instructions.c"

अटल काष्ठा arch architectures[] = अणु
	अणु
		.name = "arc",
		.init = arc__annotate_init,
	पूर्ण,
	अणु
		.name = "arm",
		.init = arm__annotate_init,
	पूर्ण,
	अणु
		.name = "arm64",
		.init = arm64__annotate_init,
	पूर्ण,
	अणु
		.name = "csky",
		.init = csky__annotate_init,
	पूर्ण,
	अणु
		.name = "mips",
		.init = mips__annotate_init,
		.objdump = अणु
			.comment_अक्षर = '#',
		पूर्ण,
	पूर्ण,
	अणु
		.name = "x86",
		.init = x86__annotate_init,
		.inकाष्ठाions = x86__inकाष्ठाions,
		.nr_inकाष्ठाions = ARRAY_SIZE(x86__inकाष्ठाions),
		.ins_is_fused = x86__ins_is_fused,
		.objdump =  अणु
			.comment_अक्षर = '#',
		पूर्ण,
	पूर्ण,
	अणु
		.name = "powerpc",
		.init = घातerpc__annotate_init,
	पूर्ण,
	अणु
		.name = "s390",
		.init = s390__annotate_init,
		.objdump =  अणु
			.comment_अक्षर = '#',
		पूर्ण,
	पूर्ण,
	अणु
		.name = "sparc",
		.init = sparc__annotate_init,
		.objdump = अणु
			.comment_अक्षर = '#',
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम ins__delete(काष्ठा ins_opeअक्रमs *ops)
अणु
	अगर (ops == शून्य)
		वापस;
	zमुक्त(&ops->source.raw);
	zमुक्त(&ops->source.name);
	zमुक्त(&ops->target.raw);
	zमुक्त(&ops->target.name);
पूर्ण

अटल पूर्णांक ins__raw_scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			      काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name)
अणु
	वापस scnम_लिखो(bf, size, "%-*s %s", max_ins_name, ins->name, ops->raw);
पूर्ण

पूर्णांक ins__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
		   काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name)
अणु
	अगर (ins->ops->scnम_लिखो)
		वापस ins->ops->scnम_लिखो(ins, bf, size, ops, max_ins_name);

	वापस ins__raw_scnम_लिखो(ins, bf, size, ops, max_ins_name);
पूर्ण

bool ins__is_fused(काष्ठा arch *arch, स्थिर अक्षर *ins1, स्थिर अक्षर *ins2)
अणु
	अगर (!arch || !arch->ins_is_fused)
		वापस false;

	वापस arch->ins_is_fused(arch, ins1, ins2);
पूर्ण

अटल पूर्णांक call__parse(काष्ठा arch *arch, काष्ठा ins_opeअक्रमs *ops, काष्ठा map_symbol *ms)
अणु
	अक्षर *endptr, *tok, *name;
	काष्ठा map *map = ms->map;
	काष्ठा addr_map_symbol target = अणु
		.ms = अणु .map = map, पूर्ण,
	पूर्ण;

	ops->target.addr = म_से_अदीर्घl(ops->raw, &endptr, 16);

	name = म_अक्षर(endptr, '<');
	अगर (name == शून्य)
		जाओ indirect_call;

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
find_target:
	target.addr = map__objdump_2mem(map, ops->target.addr);

	अगर (maps__find_ams(ms->maps, &target) == 0 &&
	    map__rip_2objdump(target.ms.map, map->map_ip(target.ms.map, target.addr)) == ops->target.addr)
		ops->target.sym = target.ms.sym;

	वापस 0;

indirect_call:
	tok = म_अक्षर(endptr, '*');
	अगर (tok != शून्य) अणु
		endptr++;

		/* Indirect call can use a non-rip रेजिस्टर and offset: callq  *0x8(%rbx).
		 * Do not parse such inकाष्ठाion.  */
		अगर (म_माला(endptr, "(%r") == शून्य)
			ops->target.addr = म_से_अदीर्घl(endptr, शून्य, 16);
	पूर्ण
	जाओ find_target;
पूर्ण

अटल पूर्णांक call__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			   काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name)
अणु
	अगर (ops->target.sym)
		वापस scnम_लिखो(bf, size, "%-*s %s", max_ins_name, ins->name, ops->target.sym->name);

	अगर (ops->target.addr == 0)
		वापस ins__raw_scnम_लिखो(ins, bf, size, ops, max_ins_name);

	अगर (ops->target.name)
		वापस scnम_लिखो(bf, size, "%-*s %s", max_ins_name, ins->name, ops->target.name);

	वापस scnम_लिखो(bf, size, "%-*s *%" PRIx64, max_ins_name, ins->name, ops->target.addr);
पूर्ण

अटल काष्ठा ins_ops call_ops = अणु
	.parse	   = call__parse,
	.scnम_लिखो = call__scnम_लिखो,
पूर्ण;

bool ins__is_call(स्थिर काष्ठा ins *ins)
अणु
	वापस ins->ops == &call_ops || ins->ops == &s390_call_ops;
पूर्ण

/*
 * Prevents from matching commas in the comment section, e.g.:
 * ffff200008446e70:       b.cs    ffff2000084470f4 <generic_exec_single+0x314>  // b.hs, b.nlast
 *
 * and skip comma as part of function arguments, e.g.:
 * 1d8b4ac <linemap_lookup(line_maps स्थिर*, अचिन्हित पूर्णांक)+0xcc>
 */
अटल अंतरभूत स्थिर अक्षर *validate_comma(स्थिर अक्षर *c, काष्ठा ins_opeअक्रमs *ops)
अणु
	अगर (ops->raw_comment && c > ops->raw_comment)
		वापस शून्य;

	अगर (ops->raw_func_start && c > ops->raw_func_start)
		वापस शून्य;

	वापस c;
पूर्ण

अटल पूर्णांक jump__parse(काष्ठा arch *arch, काष्ठा ins_opeअक्रमs *ops, काष्ठा map_symbol *ms)
अणु
	काष्ठा map *map = ms->map;
	काष्ठा symbol *sym = ms->sym;
	काष्ठा addr_map_symbol target = अणु
		.ms = अणु .map = map, पूर्ण,
	पूर्ण;
	स्थिर अक्षर *c = म_अक्षर(ops->raw, ',');
	u64 start, end;

	ops->raw_comment = म_अक्षर(ops->raw, arch->objdump.comment_अक्षर);
	ops->raw_func_start = म_अक्षर(ops->raw, '<');

	c = validate_comma(c, ops);

	/*
	 * Examples of lines to parse क्रम the _cpp_lex_token@@Base
	 * function:
	 *
	 * 1159e6c: jne    115aa32 <_cpp_lex_token@@Base+0xf92>
	 * 1159e8b: jne    c469be <cpp_named_चालक2name@@Base+0xa72>
	 *
	 * The first is a jump to an offset inside the same function,
	 * the second is to another function, i.e. that 0xa72 is an
	 * offset in the cpp_named_चालक2name@@base function.
	 */
	/*
	 * skip over possible up to 2 opeअक्रमs to get to address, e.g.:
	 * tbnz	 w0, #26, ffff0000083cd190 <security_file_permission+0xd0>
	 */
	अगर (c++ != शून्य) अणु
		ops->target.addr = म_से_अदीर्घl(c, शून्य, 16);
		अगर (!ops->target.addr) अणु
			c = म_अक्षर(c, ',');
			c = validate_comma(c, ops);
			अगर (c++ != शून्य)
				ops->target.addr = म_से_अदीर्घl(c, शून्य, 16);
		पूर्ण
	पूर्ण अन्यथा अणु
		ops->target.addr = म_से_अदीर्घl(ops->raw, शून्य, 16);
	पूर्ण

	target.addr = map__objdump_2mem(map, ops->target.addr);
	start = map->unmap_ip(map, sym->start),
	end = map->unmap_ip(map, sym->end);

	ops->target.outside = target.addr < start || target.addr > end;

	/*
	 * FIXME: things like this in _cpp_lex_token (gcc's cc1 program):

		cpp_named_चालक2name@@Base+0xa72

	 * Poपूर्णांक to a place that is after the cpp_named_चालक2name
	 * boundaries, i.e.  in the ELF symbol table क्रम cc1
	 * cpp_named_चालक2name is marked as being 32-bytes दीर्घ, but it in
	 * fact is much larger than that, so we seem to need a symbols__find()
	 * routine that looks क्रम >= current->start and  < next_symbol->start,
	 * possibly just क्रम C++ objects?
	 *
	 * For now lets just make some progress by marking jumps to outside the
	 * current function as call like.
	 *
	 * Actual navigation will come next, with further understanding of how
	 * the symbol searching and disassembly should be करोne.
	 */
	अगर (maps__find_ams(ms->maps, &target) == 0 &&
	    map__rip_2objdump(target.ms.map, map->map_ip(target.ms.map, target.addr)) == ops->target.addr)
		ops->target.sym = target.ms.sym;

	अगर (!ops->target.outside) अणु
		ops->target.offset = target.addr - start;
		ops->target.offset_avail = true;
	पूर्ण अन्यथा अणु
		ops->target.offset_avail = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jump__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			   काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name)
अणु
	स्थिर अक्षर *c;

	अगर (!ops->target.addr || ops->target.offset < 0)
		वापस ins__raw_scnम_लिखो(ins, bf, size, ops, max_ins_name);

	अगर (ops->target.outside && ops->target.sym != शून्य)
		वापस scnम_लिखो(bf, size, "%-*s %s", max_ins_name, ins->name, ops->target.sym->name);

	c = म_अक्षर(ops->raw, ',');
	c = validate_comma(c, ops);

	अगर (c != शून्य) अणु
		स्थिर अक्षर *c2 = म_अक्षर(c + 1, ',');

		c2 = validate_comma(c2, ops);
		/* check क्रम 3-op insn */
		अगर (c2 != शून्य)
			c = c2;
		c++;

		/* mirror arch objdump's space-after-comma style */
		अगर (*c == ' ')
			c++;
	पूर्ण

	वापस scnम_लिखो(bf, size, "%-*s %.*s%" PRIx64, max_ins_name,
			 ins->name, c ? c - ops->raw : 0, ops->raw,
			 ops->target.offset);
पूर्ण

अटल काष्ठा ins_ops jump_ops = अणु
	.parse	   = jump__parse,
	.scnम_लिखो = jump__scnम_लिखो,
पूर्ण;

bool ins__is_jump(स्थिर काष्ठा ins *ins)
अणु
	वापस ins->ops == &jump_ops;
पूर्ण

अटल पूर्णांक comment__symbol(अक्षर *raw, अक्षर *comment, u64 *addrp, अक्षर **namep)
अणु
	अक्षर *endptr, *name, *t;

	अगर (म_माला(raw, "(%rip)") == शून्य)
		वापस 0;

	*addrp = म_से_अदीर्घl(comment, &endptr, 16);
	अगर (endptr == comment)
		वापस 0;
	name = म_अक्षर(endptr, '<');
	अगर (name == शून्य)
		वापस -1;

	name++;

	t = म_अक्षर(name, '>');
	अगर (t == शून्य)
		वापस 0;

	*t = '\0';
	*namep = strdup(name);
	*t = '>';

	वापस 0;
पूर्ण

अटल पूर्णांक lock__parse(काष्ठा arch *arch, काष्ठा ins_opeअक्रमs *ops, काष्ठा map_symbol *ms)
अणु
	ops->locked.ops = zalloc(माप(*ops->locked.ops));
	अगर (ops->locked.ops == शून्य)
		वापस 0;

	अगर (disयंत्र_line__parse(ops->raw, &ops->locked.ins.name, &ops->locked.ops->raw) < 0)
		जाओ out_मुक्त_ops;

	ops->locked.ins.ops = ins__find(arch, ops->locked.ins.name);

	अगर (ops->locked.ins.ops == शून्य)
		जाओ out_मुक्त_ops;

	अगर (ops->locked.ins.ops->parse &&
	    ops->locked.ins.ops->parse(arch, ops->locked.ops, ms) < 0)
		जाओ out_मुक्त_ops;

	वापस 0;

out_मुक्त_ops:
	zमुक्त(&ops->locked.ops);
	वापस 0;
पूर्ण

अटल पूर्णांक lock__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			   काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name)
अणु
	पूर्णांक prपूर्णांकed;

	अगर (ops->locked.ins.ops == शून्य)
		वापस ins__raw_scnम_लिखो(ins, bf, size, ops, max_ins_name);

	prपूर्णांकed = scnम_लिखो(bf, size, "%-*s ", max_ins_name, ins->name);
	वापस prपूर्णांकed + ins__scnम_लिखो(&ops->locked.ins, bf + prपूर्णांकed,
					size - prपूर्णांकed, ops->locked.ops, max_ins_name);
पूर्ण

अटल व्योम lock__delete(काष्ठा ins_opeअक्रमs *ops)
अणु
	काष्ठा ins *ins = &ops->locked.ins;

	अगर (ins->ops && ins->ops->मुक्त)
		ins->ops->मुक्त(ops->locked.ops);
	अन्यथा
		ins__delete(ops->locked.ops);

	zमुक्त(&ops->locked.ops);
	zमुक्त(&ops->target.raw);
	zमुक्त(&ops->target.name);
पूर्ण

अटल काष्ठा ins_ops lock_ops = अणु
	.मुक्त	   = lock__delete,
	.parse	   = lock__parse,
	.scnम_लिखो = lock__scnम_लिखो,
पूर्ण;

अटल पूर्णांक mov__parse(काष्ठा arch *arch, काष्ठा ins_opeअक्रमs *ops, काष्ठा map_symbol *ms __maybe_unused)
अणु
	अक्षर *s = म_अक्षर(ops->raw, ','), *target, *comment, prev;

	अगर (s == शून्य)
		वापस -1;

	*s = '\0';
	ops->source.raw = strdup(ops->raw);
	*s = ',';

	अगर (ops->source.raw == शून्य)
		वापस -1;

	target = ++s;
	comment = म_अक्षर(s, arch->objdump.comment_अक्षर);

	अगर (comment != शून्य)
		s = comment - 1;
	अन्यथा
		s = म_अक्षर(s, '\0') - 1;

	जबतक (s > target && है_खाली(s[0]))
		--s;
	s++;
	prev = *s;
	*s = '\0';

	ops->target.raw = strdup(target);
	*s = prev;

	अगर (ops->target.raw == शून्य)
		जाओ out_मुक्त_source;

	अगर (comment == शून्य)
		वापस 0;

	comment = skip_spaces(comment);
	comment__symbol(ops->source.raw, comment + 1, &ops->source.addr, &ops->source.name);
	comment__symbol(ops->target.raw, comment + 1, &ops->target.addr, &ops->target.name);

	वापस 0;

out_मुक्त_source:
	zमुक्त(&ops->source.raw);
	वापस -1;
पूर्ण

अटल पूर्णांक mov__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			   काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name)
अणु
	वापस scnम_लिखो(bf, size, "%-*s %s,%s", max_ins_name, ins->name,
			 ops->source.name ?: ops->source.raw,
			 ops->target.name ?: ops->target.raw);
पूर्ण

अटल काष्ठा ins_ops mov_ops = अणु
	.parse	   = mov__parse,
	.scnम_लिखो = mov__scnम_लिखो,
पूर्ण;

अटल पूर्णांक dec__parse(काष्ठा arch *arch __maybe_unused, काष्ठा ins_opeअक्रमs *ops, काष्ठा map_symbol *ms __maybe_unused)
अणु
	अक्षर *target, *comment, *s, prev;

	target = s = ops->raw;

	जबतक (s[0] != '\0' && !है_खाली(s[0]))
		++s;
	prev = *s;
	*s = '\0';

	ops->target.raw = strdup(target);
	*s = prev;

	अगर (ops->target.raw == शून्य)
		वापस -1;

	comment = म_अक्षर(s, arch->objdump.comment_अक्षर);
	अगर (comment == शून्य)
		वापस 0;

	comment = skip_spaces(comment);
	comment__symbol(ops->target.raw, comment + 1, &ops->target.addr, &ops->target.name);

	वापस 0;
पूर्ण

अटल पूर्णांक dec__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			   काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name)
अणु
	वापस scnम_लिखो(bf, size, "%-*s %s", max_ins_name, ins->name,
			 ops->target.name ?: ops->target.raw);
पूर्ण

अटल काष्ठा ins_ops dec_ops = अणु
	.parse	   = dec__parse,
	.scnम_लिखो = dec__scnम_लिखो,
पूर्ण;

अटल पूर्णांक nop__scnम_लिखो(काष्ठा ins *ins __maybe_unused, अक्षर *bf, माप_प्रकार size,
			  काष्ठा ins_opeअक्रमs *ops __maybe_unused, पूर्णांक max_ins_name)
अणु
	वापस scnम_लिखो(bf, size, "%-*s", max_ins_name, "nop");
पूर्ण

अटल काष्ठा ins_ops nop_ops = अणु
	.scnम_लिखो = nop__scnम_लिखो,
पूर्ण;

अटल काष्ठा ins_ops ret_ops = अणु
	.scnम_लिखो = ins__raw_scnम_लिखो,
पूर्ण;

bool ins__is_ret(स्थिर काष्ठा ins *ins)
अणु
	वापस ins->ops == &ret_ops;
पूर्ण

bool ins__is_lock(स्थिर काष्ठा ins *ins)
अणु
	वापस ins->ops == &lock_ops;
पूर्ण

अटल पूर्णांक ins__key_cmp(स्थिर व्योम *name, स्थिर व्योम *insp)
अणु
	स्थिर काष्ठा ins *ins = insp;

	वापस म_भेद(name, ins->name);
पूर्ण

अटल पूर्णांक ins__cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा ins *ia = a;
	स्थिर काष्ठा ins *ib = b;

	वापस म_भेद(ia->name, ib->name);
पूर्ण

अटल व्योम ins__sort(काष्ठा arch *arch)
अणु
	स्थिर पूर्णांक nmemb = arch->nr_inकाष्ठाions;

	क्विक(arch->inकाष्ठाions, nmemb, माप(काष्ठा ins), ins__cmp);
पूर्ण

अटल काष्ठा ins_ops *__ins__find(काष्ठा arch *arch, स्थिर अक्षर *name)
अणु
	काष्ठा ins *ins;
	स्थिर पूर्णांक nmemb = arch->nr_inकाष्ठाions;

	अगर (!arch->sorted_inकाष्ठाions) अणु
		ins__sort(arch);
		arch->sorted_inकाष्ठाions = true;
	पूर्ण

	ins = द्वा_खोज(name, arch->inकाष्ठाions, nmemb, माप(काष्ठा ins), ins__key_cmp);
	वापस ins ? ins->ops : शून्य;
पूर्ण

अटल काष्ठा ins_ops *ins__find(काष्ठा arch *arch, स्थिर अक्षर *name)
अणु
	काष्ठा ins_ops *ops = __ins__find(arch, name);

	अगर (!ops && arch->associate_inकाष्ठाion_ops)
		ops = arch->associate_inकाष्ठाion_ops(arch, name);

	वापस ops;
पूर्ण

अटल पूर्णांक arch__key_cmp(स्थिर व्योम *name, स्थिर व्योम *archp)
अणु
	स्थिर काष्ठा arch *arch = archp;

	वापस म_भेद(name, arch->name);
पूर्ण

अटल पूर्णांक arch__cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा arch *aa = a;
	स्थिर काष्ठा arch *ab = b;

	वापस म_भेद(aa->name, ab->name);
पूर्ण

अटल व्योम arch__sort(व्योम)
अणु
	स्थिर पूर्णांक nmemb = ARRAY_SIZE(architectures);

	क्विक(architectures, nmemb, माप(काष्ठा arch), arch__cmp);
पूर्ण

अटल काष्ठा arch *arch__find(स्थिर अक्षर *name)
अणु
	स्थिर पूर्णांक nmemb = ARRAY_SIZE(architectures);
	अटल bool sorted;

	अगर (!sorted) अणु
		arch__sort();
		sorted = true;
	पूर्ण

	वापस द्वा_खोज(name, architectures, nmemb, माप(काष्ठा arch), arch__key_cmp);
पूर्ण

अटल काष्ठा annotated_source *annotated_source__new(व्योम)
अणु
	काष्ठा annotated_source *src = zalloc(माप(*src));

	अगर (src != शून्य)
		INIT_LIST_HEAD(&src->source);

	वापस src;
पूर्ण

अटल __maybe_unused व्योम annotated_source__delete(काष्ठा annotated_source *src)
अणु
	अगर (src == शून्य)
		वापस;
	zमुक्त(&src->histograms);
	zमुक्त(&src->cycles_hist);
	मुक्त(src);
पूर्ण

अटल पूर्णांक annotated_source__alloc_histograms(काष्ठा annotated_source *src,
					      माप_प्रकार size, पूर्णांक nr_hists)
अणु
	माप_प्रकार माप_sym_hist;

	/*
	 * Add buffer of one element क्रम zero length symbol.
	 * When sample is taken from first inकाष्ठाion of
	 * zero length symbol, perf still resolves it and
	 * shows symbol name in perf report and allows to
	 * annotate it.
	 */
	अगर (size == 0)
		size = 1;

	/* Check क्रम overflow when calculating माप_sym_hist */
	अगर (size > (SIZE_MAX - माप(काष्ठा sym_hist)) / माप(काष्ठा sym_hist_entry))
		वापस -1;

	माप_sym_hist = (माप(काष्ठा sym_hist) + size * माप(काष्ठा sym_hist_entry));

	/* Check क्रम overflow in zalloc argument */
	अगर (माप_sym_hist > SIZE_MAX / nr_hists)
		वापस -1;

	src->माप_sym_hist = माप_sym_hist;
	src->nr_histograms   = nr_hists;
	src->histograms	     = सुस्मृति(nr_hists, माप_sym_hist) ;
	वापस src->histograms ? 0 : -1;
पूर्ण

/* The cycles histogram is lazily allocated. */
अटल पूर्णांक symbol__alloc_hist_cycles(काष्ठा symbol *sym)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);
	स्थिर माप_प्रकार size = symbol__size(sym);

	notes->src->cycles_hist = सुस्मृति(size, माप(काष्ठा cyc_hist));
	अगर (notes->src->cycles_hist == शून्य)
		वापस -1;
	वापस 0;
पूर्ण

व्योम symbol__annotate_zero_histograms(काष्ठा symbol *sym)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);

	pthपढ़ो_mutex_lock(&notes->lock);
	अगर (notes->src != शून्य) अणु
		स_रखो(notes->src->histograms, 0,
		       notes->src->nr_histograms * notes->src->माप_sym_hist);
		अगर (notes->src->cycles_hist)
			स_रखो(notes->src->cycles_hist, 0,
				symbol__size(sym) * माप(काष्ठा cyc_hist));
	पूर्ण
	pthपढ़ो_mutex_unlock(&notes->lock);
पूर्ण

अटल पूर्णांक __symbol__account_cycles(काष्ठा cyc_hist *ch,
				    u64 start,
				    अचिन्हित offset, अचिन्हित cycles,
				    अचिन्हित have_start)
अणु
	/*
	 * For now we can only account one basic block per
	 * final jump. But multiple could be overlapping.
	 * Always account the दीर्घest one. So when
	 * a लघुer one has been alपढ़ोy seen throw it away.
	 *
	 * We separately always account the full cycles.
	 */
	ch[offset].num_aggr++;
	ch[offset].cycles_aggr += cycles;

	अगर (cycles > ch[offset].cycles_max)
		ch[offset].cycles_max = cycles;

	अगर (ch[offset].cycles_min) अणु
		अगर (cycles && cycles < ch[offset].cycles_min)
			ch[offset].cycles_min = cycles;
	पूर्ण अन्यथा
		ch[offset].cycles_min = cycles;

	अगर (!have_start && ch[offset].have_start)
		वापस 0;
	अगर (ch[offset].num) अणु
		अगर (have_start && (!ch[offset].have_start ||
				   ch[offset].start > start)) अणु
			ch[offset].have_start = 0;
			ch[offset].cycles = 0;
			ch[offset].num = 0;
			अगर (ch[offset].reset < 0xffff)
				ch[offset].reset++;
		पूर्ण अन्यथा अगर (have_start &&
			   ch[offset].start < start)
			वापस 0;
	पूर्ण

	अगर (ch[offset].num < NUM_SPARKS)
		ch[offset].cycles_spark[ch[offset].num] = cycles;

	ch[offset].have_start = have_start;
	ch[offset].start = start;
	ch[offset].cycles += cycles;
	ch[offset].num++;
	वापस 0;
पूर्ण

अटल पूर्णांक __symbol__inc_addr_samples(काष्ठा map_symbol *ms,
				      काष्ठा annotated_source *src, पूर्णांक evidx, u64 addr,
				      काष्ठा perf_sample *sample)
अणु
	काष्ठा symbol *sym = ms->sym;
	अचिन्हित offset;
	काष्ठा sym_hist *h;

	pr_debug3("%s: addr=%#" PRIx64 "\n", __func__, ms->map->unmap_ip(ms->map, addr));

	अगर ((addr < sym->start || addr >= sym->end) &&
	    (addr != sym->end || sym->start != sym->end)) अणु
		pr_debug("%s(%d): ERANGE! sym->name=%s, start=%#" PRIx64 ", addr=%#" PRIx64 ", end=%#" PRIx64 "\n",
		       __func__, __LINE__, sym->name, sym->start, addr, sym->end);
		वापस -दुस्फल;
	पूर्ण

	offset = addr - sym->start;
	h = annotated_source__histogram(src, evidx);
	अगर (h == शून्य) अणु
		pr_debug("%s(%d): ENOMEM! sym->name=%s, start=%#" PRIx64 ", addr=%#" PRIx64 ", end=%#" PRIx64 ", func: %d\n",
			 __func__, __LINE__, sym->name, sym->start, addr, sym->end, sym->type == STT_FUNC);
		वापस -ENOMEM;
	पूर्ण
	h->nr_samples++;
	h->addr[offset].nr_samples++;
	h->period += sample->period;
	h->addr[offset].period += sample->period;

	pr_debug3("%#" PRIx64 " %s: period++ [addr: %#" PRIx64 ", %#" PRIx64
		  ", evidx=%d] => nr_samples: %" PRIu64 ", period: %" PRIu64 "\n",
		  sym->start, sym->name, addr, addr - sym->start, evidx,
		  h->addr[offset].nr_samples, h->addr[offset].period);
	वापस 0;
पूर्ण

अटल काष्ठा cyc_hist *symbol__cycles_hist(काष्ठा symbol *sym)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);

	अगर (notes->src == शून्य) अणु
		notes->src = annotated_source__new();
		अगर (notes->src == शून्य)
			वापस शून्य;
		जाओ alloc_cycles_hist;
	पूर्ण

	अगर (!notes->src->cycles_hist) अणु
alloc_cycles_hist:
		symbol__alloc_hist_cycles(sym);
	पूर्ण

	वापस notes->src->cycles_hist;
पूर्ण

काष्ठा annotated_source *symbol__hists(काष्ठा symbol *sym, पूर्णांक nr_hists)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);

	अगर (notes->src == शून्य) अणु
		notes->src = annotated_source__new();
		अगर (notes->src == शून्य)
			वापस शून्य;
		जाओ alloc_histograms;
	पूर्ण

	अगर (notes->src->histograms == शून्य) अणु
alloc_histograms:
		annotated_source__alloc_histograms(notes->src, symbol__size(sym),
						   nr_hists);
	पूर्ण

	वापस notes->src;
पूर्ण

अटल पूर्णांक symbol__inc_addr_samples(काष्ठा map_symbol *ms,
				    काष्ठा evsel *evsel, u64 addr,
				    काष्ठा perf_sample *sample)
अणु
	काष्ठा symbol *sym = ms->sym;
	काष्ठा annotated_source *src;

	अगर (sym == शून्य)
		वापस 0;
	src = symbol__hists(sym, evsel->evlist->core.nr_entries);
	वापस src ? __symbol__inc_addr_samples(ms, src, evsel->idx, addr, sample) : 0;
पूर्ण

अटल पूर्णांक symbol__account_cycles(u64 addr, u64 start,
				  काष्ठा symbol *sym, अचिन्हित cycles)
अणु
	काष्ठा cyc_hist *cycles_hist;
	अचिन्हित offset;

	अगर (sym == शून्य)
		वापस 0;
	cycles_hist = symbol__cycles_hist(sym);
	अगर (cycles_hist == शून्य)
		वापस -ENOMEM;
	अगर (addr < sym->start || addr >= sym->end)
		वापस -दुस्फल;

	अगर (start) अणु
		अगर (start < sym->start || start >= sym->end)
			वापस -दुस्फल;
		अगर (start >= addr)
			start = 0;
	पूर्ण
	offset = addr - sym->start;
	वापस __symbol__account_cycles(cycles_hist,
					start ? start - sym->start : 0,
					offset, cycles,
					!!start);
पूर्ण

पूर्णांक addr_map_symbol__account_cycles(काष्ठा addr_map_symbol *ams,
				    काष्ठा addr_map_symbol *start,
				    अचिन्हित cycles)
अणु
	u64 saddr = 0;
	पूर्णांक err;

	अगर (!cycles)
		वापस 0;

	/*
	 * Only set start when IPC can be computed. We can only
	 * compute it when the basic block is completely in a single
	 * function.
	 * Special हाल the हाल when the jump is अन्यथाwhere, but
	 * it starts on the function start.
	 */
	अगर (start &&
		(start->ms.sym == ams->ms.sym ||
		 (ams->ms.sym &&
		   start->addr == ams->ms.sym->start + ams->ms.map->start)))
		saddr = start->al_addr;
	अगर (saddr == 0)
		pr_debug2("BB with bad start: addr %"PRIx64" start %"PRIx64" sym %"PRIx64" saddr %"PRIx64"\n",
			ams->addr,
			start ? start->addr : 0,
			ams->ms.sym ? ams->ms.sym->start + ams->ms.map->start : 0,
			saddr);
	err = symbol__account_cycles(ams->al_addr, saddr, ams->ms.sym, cycles);
	अगर (err)
		pr_debug2("account_cycles failed %d\n", err);
	वापस err;
पूर्ण

अटल अचिन्हित annotation__count_insn(काष्ठा annotation *notes, u64 start, u64 end)
अणु
	अचिन्हित n_insn = 0;
	u64 offset;

	क्रम (offset = start; offset <= end; offset++) अणु
		अगर (notes->offsets[offset])
			n_insn++;
	पूर्ण
	वापस n_insn;
पूर्ण

अटल व्योम annotation__count_and_fill(काष्ठा annotation *notes, u64 start, u64 end, काष्ठा cyc_hist *ch)
अणु
	अचिन्हित n_insn;
	अचिन्हित पूर्णांक cover_insn = 0;
	u64 offset;

	n_insn = annotation__count_insn(notes, start, end);
	अगर (n_insn && ch->num && ch->cycles) अणु
		भग्न ipc = n_insn / ((द्विगुन)ch->cycles / (द्विगुन)ch->num);

		/* Hide data when there are too many overlaps. */
		अगर (ch->reset >= 0x7fff)
			वापस;

		क्रम (offset = start; offset <= end; offset++) अणु
			काष्ठा annotation_line *al = notes->offsets[offset];

			अगर (al && al->ipc == 0.0) अणु
				al->ipc = ipc;
				cover_insn++;
			पूर्ण
		पूर्ण

		अगर (cover_insn) अणु
			notes->hit_cycles += ch->cycles;
			notes->hit_insn += n_insn * ch->num;
			notes->cover_insn += cover_insn;
		पूर्ण
	पूर्ण
पूर्ण

व्योम annotation__compute_ipc(काष्ठा annotation *notes, माप_प्रकार size)
अणु
	s64 offset;

	अगर (!notes->src || !notes->src->cycles_hist)
		वापस;

	notes->total_insn = annotation__count_insn(notes, 0, size - 1);
	notes->hit_cycles = 0;
	notes->hit_insn = 0;
	notes->cover_insn = 0;

	pthपढ़ो_mutex_lock(&notes->lock);
	क्रम (offset = size - 1; offset >= 0; --offset) अणु
		काष्ठा cyc_hist *ch;

		ch = &notes->src->cycles_hist[offset];
		अगर (ch && ch->cycles) अणु
			काष्ठा annotation_line *al;

			अगर (ch->have_start)
				annotation__count_and_fill(notes, ch->start, offset, ch);
			al = notes->offsets[offset];
			अगर (al && ch->num_aggr) अणु
				al->cycles = ch->cycles_aggr / ch->num_aggr;
				al->cycles_max = ch->cycles_max;
				al->cycles_min = ch->cycles_min;
			पूर्ण
			notes->have_cycles = true;
		पूर्ण
	पूर्ण
	pthपढ़ो_mutex_unlock(&notes->lock);
पूर्ण

पूर्णांक addr_map_symbol__inc_samples(काष्ठा addr_map_symbol *ams, काष्ठा perf_sample *sample,
				 काष्ठा evsel *evsel)
अणु
	वापस symbol__inc_addr_samples(&ams->ms, evsel, ams->al_addr, sample);
पूर्ण

पूर्णांक hist_entry__inc_addr_samples(काष्ठा hist_entry *he, काष्ठा perf_sample *sample,
				 काष्ठा evsel *evsel, u64 ip)
अणु
	वापस symbol__inc_addr_samples(&he->ms, evsel, ip, sample);
पूर्ण

अटल व्योम disयंत्र_line__init_ins(काष्ठा disयंत्र_line *dl, काष्ठा arch *arch, काष्ठा map_symbol *ms)
अणु
	dl->ins.ops = ins__find(arch, dl->ins.name);

	अगर (!dl->ins.ops)
		वापस;

	अगर (dl->ins.ops->parse && dl->ins.ops->parse(arch, &dl->ops, ms) < 0)
		dl->ins.ops = शून्य;
पूर्ण

अटल पूर्णांक disयंत्र_line__parse(अक्षर *line, स्थिर अक्षर **namep, अक्षर **rawp)
अणु
	अक्षर पंचांगp, *name = skip_spaces(line);

	अगर (name[0] == '\0')
		वापस -1;

	*rawp = name + 1;

	जबतक ((*rawp)[0] != '\0' && !है_खाली((*rawp)[0]))
		++*rawp;

	पंचांगp = (*rawp)[0];
	(*rawp)[0] = '\0';
	*namep = strdup(name);

	अगर (*namep == शून्य)
		जाओ out;

	(*rawp)[0] = पंचांगp;
	*rawp = strim(*rawp);

	वापस 0;

out:
	वापस -1;
पूर्ण

काष्ठा annotate_args अणु
	काष्ठा arch		  *arch;
	काष्ठा map_symbol	  ms;
	काष्ठा evsel		  *evsel;
	काष्ठा annotation_options *options;
	s64			  offset;
	अक्षर			  *line;
	पूर्णांक			  line_nr;
	अक्षर			  *fileloc;
पूर्ण;

अटल व्योम annotation_line__init(काष्ठा annotation_line *al,
				  काष्ठा annotate_args *args,
				  पूर्णांक nr)
अणु
	al->offset = args->offset;
	al->line = strdup(args->line);
	al->line_nr = args->line_nr;
	al->fileloc = args->fileloc;
	al->data_nr = nr;
पूर्ण

अटल व्योम annotation_line__निकास(काष्ठा annotation_line *al)
अणु
	मुक्त_srcline(al->path);
	zमुक्त(&al->line);
पूर्ण

अटल माप_प्रकार disयंत्र_line_size(पूर्णांक nr)
अणु
	काष्ठा annotation_line *al;

	वापस (माप(काष्ठा disयंत्र_line) + (माप(al->data[0]) * nr));
पूर्ण

/*
 * Allocating the disयंत्र annotation line data with
 * following काष्ठाure:
 *
 *    -------------------------------------------
 *    काष्ठा disयंत्र_line | काष्ठा annotation_line
 *    -------------------------------------------
 *
 * We have 'struct annotation_line' member as last member
 * of 'struct disasm_line' to have an easy access.
 */
अटल काष्ठा disयंत्र_line *disयंत्र_line__new(काष्ठा annotate_args *args)
अणु
	काष्ठा disयंत्र_line *dl = शून्य;
	पूर्णांक nr = 1;

	अगर (evsel__is_group_event(args->evsel))
		nr = args->evsel->core.nr_members;

	dl = zalloc(disयंत्र_line_size(nr));
	अगर (!dl)
		वापस शून्य;

	annotation_line__init(&dl->al, args, nr);
	अगर (dl->al.line == शून्य)
		जाओ out_delete;

	अगर (args->offset != -1) अणु
		अगर (disयंत्र_line__parse(dl->al.line, &dl->ins.name, &dl->ops.raw) < 0)
			जाओ out_मुक्त_line;

		disयंत्र_line__init_ins(dl, args->arch, &args->ms);
	पूर्ण

	वापस dl;

out_मुक्त_line:
	zमुक्त(&dl->al.line);
out_delete:
	मुक्त(dl);
	वापस शून्य;
पूर्ण

व्योम disयंत्र_line__मुक्त(काष्ठा disयंत्र_line *dl)
अणु
	अगर (dl->ins.ops && dl->ins.ops->मुक्त)
		dl->ins.ops->मुक्त(&dl->ops);
	अन्यथा
		ins__delete(&dl->ops);
	zमुक्त(&dl->ins.name);
	annotation_line__निकास(&dl->al);
	मुक्त(dl);
पूर्ण

पूर्णांक disयंत्र_line__scnम_लिखो(काष्ठा disयंत्र_line *dl, अक्षर *bf, माप_प्रकार size, bool raw, पूर्णांक max_ins_name)
अणु
	अगर (raw || !dl->ins.ops)
		वापस scnम_लिखो(bf, size, "%-*s %s", max_ins_name, dl->ins.name, dl->ops.raw);

	वापस ins__scnम_लिखो(&dl->ins, bf, size, &dl->ops, max_ins_name);
पूर्ण

अटल व्योम annotation_line__add(काष्ठा annotation_line *al, काष्ठा list_head *head)
अणु
	list_add_tail(&al->node, head);
पूर्ण

काष्ठा annotation_line *
annotation_line__next(काष्ठा annotation_line *pos, काष्ठा list_head *head)
अणु
	list_क्रम_each_entry_जारी(pos, head, node)
		अगर (pos->offset >= 0)
			वापस pos;

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *annotate__address_color(काष्ठा block_range *br)
अणु
	द्विगुन cov = block_range__coverage(br);

	अगर (cov >= 0) अणु
		/* mark red क्रम >75% coverage */
		अगर (cov > 0.75)
			वापस PERF_COLOR_RED;

		/* mark dull क्रम <1% coverage */
		अगर (cov < 0.01)
			वापस PERF_COLOR_NORMAL;
	पूर्ण

	वापस PERF_COLOR_MAGENTA;
पूर्ण

अटल स्थिर अक्षर *annotate__यंत्र_color(काष्ठा block_range *br)
अणु
	द्विगुन cov = block_range__coverage(br);

	अगर (cov >= 0) अणु
		/* mark dull क्रम <1% coverage */
		अगर (cov < 0.01)
			वापस PERF_COLOR_NORMAL;
	पूर्ण

	वापस PERF_COLOR_BLUE;
पूर्ण

अटल व्योम annotate__branch_म_लिखो(काष्ठा block_range *br, u64 addr)
अणु
	bool emit_comment = true;

	अगर (!br)
		वापस;

#अगर 1
	अगर (br->is_target && br->start == addr) अणु
		काष्ठा block_range *branch = br;
		द्विगुन p;

		/*
		 * Find matching branch to our target.
		 */
		जबतक (!branch->is_branch)
			branch = block_range__next(branch);

		p = 100 *(द्विगुन)br->entry / branch->coverage;

		अगर (p > 0.1) अणु
			अगर (emit_comment) अणु
				emit_comment = false;
				म_लिखो("\t#");
			पूर्ण

			/*
			 * The percentage of coverage joined at this target in relation
			 * to the next branch.
			 */
			म_लिखो(" +%.2f%%", p);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (br->is_branch && br->end == addr) अणु
		द्विगुन p = 100*(द्विगुन)br->taken / br->coverage;

		अगर (p > 0.1) अणु
			अगर (emit_comment) अणु
				emit_comment = false;
				म_लिखो("\t#");
			पूर्ण

			/*
			 * The percentage of coverage leaving at this branch, and
			 * its prediction ratio.
			 */
			म_लिखो(" -%.2f%% (p:%.2f%%)", p, 100*(द्विगुन)br->pred  / br->taken);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक disयंत्र_line__prपूर्णांक(काष्ठा disयंत्र_line *dl, u64 start, पूर्णांक addr_fmt_width)
अणु
	s64 offset = dl->al.offset;
	स्थिर u64 addr = start + offset;
	काष्ठा block_range *br;

	br = block_range__find(addr);
	color_ख_लिखो(मानक_निकास, annotate__address_color(br), "  %*" PRIx64 ":", addr_fmt_width, addr);
	color_ख_लिखो(मानक_निकास, annotate__यंत्र_color(br), "%s", dl->al.line);
	annotate__branch_म_लिखो(br, addr);
	वापस 0;
पूर्ण

अटल पूर्णांक
annotation_line__prपूर्णांक(काष्ठा annotation_line *al, काष्ठा symbol *sym, u64 start,
		       काष्ठा evsel *evsel, u64 len, पूर्णांक min_pcnt, पूर्णांक prपूर्णांकed,
		       पूर्णांक max_lines, काष्ठा annotation_line *queue, पूर्णांक addr_fmt_width,
		       पूर्णांक percent_type)
अणु
	काष्ठा disयंत्र_line *dl = container_of(al, काष्ठा disयंत्र_line, al);
	अटल स्थिर अक्षर *prev_line;

	अगर (al->offset != -1) अणु
		द्विगुन max_percent = 0.0;
		पूर्णांक i, nr_percent = 1;
		स्थिर अक्षर *color;
		काष्ठा annotation *notes = symbol__annotation(sym);

		क्रम (i = 0; i < al->data_nr; i++) अणु
			द्विगुन percent;

			percent = annotation_data__percent(&al->data[i],
							   percent_type);

			अगर (percent > max_percent)
				max_percent = percent;
		पूर्ण

		अगर (al->data_nr > nr_percent)
			nr_percent = al->data_nr;

		अगर (max_percent < min_pcnt)
			वापस -1;

		अगर (max_lines && prपूर्णांकed >= max_lines)
			वापस 1;

		अगर (queue != शून्य) अणु
			list_क्रम_each_entry_from(queue, &notes->src->source, node) अणु
				अगर (queue == al)
					अवरोध;
				annotation_line__prपूर्णांक(queue, sym, start, evsel, len,
						       0, 0, 1, शून्य, addr_fmt_width,
						       percent_type);
			पूर्ण
		पूर्ण

		color = get_percent_color(max_percent);

		क्रम (i = 0; i < nr_percent; i++) अणु
			काष्ठा annotation_data *data = &al->data[i];
			द्विगुन percent;

			percent = annotation_data__percent(data, percent_type);
			color = get_percent_color(percent);

			अगर (symbol_conf.show_total_period)
				color_ख_लिखो(मानक_निकास, color, " %11" PRIu64,
					      data->he.period);
			अन्यथा अगर (symbol_conf.show_nr_samples)
				color_ख_लिखो(मानक_निकास, color, " %7" PRIu64,
					      data->he.nr_samples);
			अन्यथा
				color_ख_लिखो(मानक_निकास, color, " %7.2f", percent);
		पूर्ण

		म_लिखो(" : ");

		disयंत्र_line__prपूर्णांक(dl, start, addr_fmt_width);

		/*
		 * Also color the filename and line अगर needed, with
		 * the same color than the percentage. Don't prपूर्णांक it
		 * twice क्रम बंद colored addr with the same filename:line
		 */
		अगर (al->path) अणु
			अगर (!prev_line || म_भेद(prev_line, al->path)) अणु
				color_ख_लिखो(मानक_निकास, color, " // %s", al->path);
				prev_line = al->path;
			पूर्ण
		पूर्ण

		म_लिखो("\n");
	पूर्ण अन्यथा अगर (max_lines && prपूर्णांकed >= max_lines)
		वापस 1;
	अन्यथा अणु
		पूर्णांक width = symbol_conf.show_total_period ? 12 : 8;

		अगर (queue)
			वापस -1;

		अगर (evsel__is_group_event(evsel))
			width *= evsel->core.nr_members;

		अगर (!*al->line)
			म_लिखो(" %*s:\n", width, " ");
		अन्यथा
			म_लिखो(" %*s: %-*d %s\n", width, " ", addr_fmt_width, al->line_nr, al->line);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * symbol__parse_objdump_line() parses objdump output (with -d --no-show-raw)
 * which looks like following
 *
 *  0000000000415500 <_init>:
 *    415500:       sub    $0x8,%rsp
 *    415504:       mov    0x2f5ad5(%rip),%rax        # 70afe0 <_DYNAMIC+0x2f8>
 *    41550b:       test   %rax,%rax
 *    41550e:       je     415515 <_init+0x15>
 *    415510:       callq  416e70 <__gmon_start__@plt>
 *    415515:       add    $0x8,%rsp
 *    415519:       retq
 *
 * it will be parsed and saved पूर्णांकo काष्ठा disयंत्र_line as
 *  <offset>       <name>  <ops.raw>
 *
 * The offset will be a relative offset from the start of the symbol and -1
 * means that it's not a disassembly line so should be treated dअगरferently.
 * The ops.raw part will be parsed further according to type of the inकाष्ठाion.
 */
अटल पूर्णांक symbol__parse_objdump_line(काष्ठा symbol *sym,
				      काष्ठा annotate_args *args,
				      अक्षर *parsed_line, पूर्णांक *line_nr, अक्षर **fileloc)
अणु
	काष्ठा map *map = args->ms.map;
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा disयंत्र_line *dl;
	अक्षर *पंचांगp;
	s64 line_ip, offset = -1;
	regmatch_t match[2];

	/* /filename:linenr ? Save line number and ignore. */
	अगर (regexec(&file_lineno, parsed_line, 2, match, 0) == 0) अणु
		*line_nr = म_से_प(parsed_line + match[1].rm_so);
		*fileloc = strdup(parsed_line);
		वापस 0;
	पूर्ण

	/* Process hex address followed by ':'. */
	line_ip = म_से_अदीर्घl(parsed_line, &पंचांगp, 16);
	अगर (parsed_line != पंचांगp && पंचांगp[0] == ':' && tmp[1] != '\0') अणु
		u64 start = map__rip_2objdump(map, sym->start),
		    end = map__rip_2objdump(map, sym->end);

		offset = line_ip - start;
		अगर ((u64)line_ip < start || (u64)line_ip >= end)
			offset = -1;
		अन्यथा
			parsed_line = पंचांगp + 1;
	पूर्ण

	args->offset  = offset;
	args->line    = parsed_line;
	args->line_nr = *line_nr;
	args->fileloc = *fileloc;
	args->ms.sym  = sym;

	dl = disयंत्र_line__new(args);
	(*line_nr)++;

	अगर (dl == शून्य)
		वापस -1;

	अगर (!disयंत्र_line__has_local_offset(dl)) अणु
		dl->ops.target.offset = dl->ops.target.addr -
					map__rip_2objdump(map, sym->start);
		dl->ops.target.offset_avail = true;
	पूर्ण

	/* kcore has no symbols, so add the call target symbol */
	अगर (dl->ins.ops && ins__is_call(&dl->ins) && !dl->ops.target.sym) अणु
		काष्ठा addr_map_symbol target = अणु
			.addr = dl->ops.target.addr,
			.ms = अणु .map = map, पूर्ण,
		पूर्ण;

		अगर (!maps__find_ams(args->ms.maps, &target) &&
		    target.ms.sym->start == target.al_addr)
			dl->ops.target.sym = target.ms.sym;
	पूर्ण

	annotation_line__add(&dl->al, &notes->src->source);

	वापस 0;
पूर्ण

अटल __attribute__((स्थिरructor)) व्योम symbol__init_regexpr(व्योम)
अणु
	regcomp(&file_lineno, "^/[^:]+:([0-9]+)", REG_EXTENDED);
पूर्ण

अटल व्योम delete_last_nop(काष्ठा symbol *sym)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा list_head *list = &notes->src->source;
	काष्ठा disयंत्र_line *dl;

	जबतक (!list_empty(list)) अणु
		dl = list_entry(list->prev, काष्ठा disयंत्र_line, al.node);

		अगर (dl->ins.ops) अणु
			अगर (dl->ins.ops != &nop_ops)
				वापस;
		पूर्ण अन्यथा अणु
			अगर (!म_माला(dl->al.line, " nop ") &&
			    !म_माला(dl->al.line, " nopl ") &&
			    !म_माला(dl->al.line, " nopw "))
				वापस;
		पूर्ण

		list_del_init(&dl->al.node);
		disयंत्र_line__मुक्त(dl);
	पूर्ण
पूर्ण

पूर्णांक symbol__म_त्रुटि_disassemble(काष्ठा map_symbol *ms, पूर्णांक errnum, अक्षर *buf, माप_प्रकार buflen)
अणु
	काष्ठा dso *dso = ms->map->dso;

	BUG_ON(buflen == 0);

	अगर (errnum >= 0) अणु
		str_error_r(errnum, buf, buflen);
		वापस 0;
	पूर्ण

	चयन (errnum) अणु
	हाल SYMBOL_ANNOTATE_ERRNO__NO_VMLINUX: अणु
		अक्षर bf[SBUILD_ID_SIZE + 15] = " with build id ";
		अक्षर *build_id_msg = शून्य;

		अगर (dso->has_build_id) अणु
			build_id__प्र_लिखो(&dso->bid, bf + 15);
			build_id_msg = bf;
		पूर्ण
		scnम_लिखो(buf, buflen,
			  "No vmlinux file%s\nwas found in the path.\n\n"
			  "Note that annotation using /proc/kcore requires CAP_SYS_RAWIO capability.\n\n"
			  "Please use:\n\n"
			  "  perf buildid-cache -vu vmlinux\n\n"
			  "or:\n\n"
			  "  --vmlinux vmlinux\n", build_id_msg ?: "");
	पूर्ण
		अवरोध;
	हाल SYMBOL_ANNOTATE_ERRNO__NO_LIBOPCODES_FOR_BPF:
		scnम_लिखो(buf, buflen, "Please link with binutils's libopcode to enable BPF annotation");
		अवरोध;
	हाल SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_REGEXP:
		scnम_लिखो(buf, buflen, "Problems with arch specific instruction name regular expressions.");
		अवरोध;
	हाल SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_CPUID_PARSING:
		scnम_लिखो(buf, buflen, "Problems while parsing the CPUID in the arch specific initialization.");
		अवरोध;
	हाल SYMBOL_ANNOTATE_ERRNO__BPF_INVALID_खाता:
		scnम_लिखो(buf, buflen, "Invalid BPF file: %s.", dso->दीर्घ_name);
		अवरोध;
	हाल SYMBOL_ANNOTATE_ERRNO__BPF_MISSING_BTF:
		scnम_लिखो(buf, buflen, "The %s BPF file has no BTF section, compile with -g or use pahole -J.",
			  dso->दीर्घ_name);
		अवरोध;
	शेष:
		scnम_लिखो(buf, buflen, "Internal error: Invalid %d error code\n", errnum);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dso__disassemble_filename(काष्ठा dso *dso, अक्षर *filename, माप_प्रकार filename_size)
अणु
	अक्षर linkname[PATH_MAX];
	अक्षर *build_id_filename;
	अक्षर *build_id_path = शून्य;
	अक्षर *pos;
	पूर्णांक len;

	अगर (dso->symtab_type == DSO_BINARY_TYPE__KALLSYMS &&
	    !dso__is_kcore(dso))
		वापस SYMBOL_ANNOTATE_ERRNO__NO_VMLINUX;

	build_id_filename = dso__build_id_filename(dso, शून्य, 0, false);
	अगर (build_id_filename) अणु
		__symbol__join_symfs(filename, filename_size, build_id_filename);
		मुक्त(build_id_filename);
	पूर्ण अन्यथा अणु
		अगर (dso->has_build_id)
			वापस ENOMEM;
		जाओ fallback;
	पूर्ण

	build_id_path = strdup(filename);
	अगर (!build_id_path)
		वापस ENOMEM;

	/*
	 * old style build-id cache has name of XX/XXXXXXX.. जबतक
	 * new style has XX/XXXXXXX../अणुelf,kallsyms,vdsoपूर्ण.
	 * extract the build-id part of स_नाम in the new style only.
	 */
	pos = म_खोजप(build_id_path, '/');
	अगर (pos && म_माप(pos) < SBUILD_ID_SIZE - 2)
		स_नाम(build_id_path);

	अगर (dso__is_kcore(dso))
		जाओ fallback;

	len = पढ़ोlink(build_id_path, linkname, माप(linkname) - 1);
	अगर (len < 0)
		जाओ fallback;

	linkname[len] = '\0';
	अगर (म_माला(linkname, DSO__NAME_KALLSYMS) ||
		access(filename, R_OK)) अणु
fallback:
		/*
		 * If we करोn't have build-ids or the build-id file isn't in the
		 * cache, or is just a kallsyms file, well, lets hope that this
		 * DSO is the same as when 'perf record' ran.
		 */
		__symbol__join_symfs(filename, filename_size, dso->दीर्घ_name);
	पूर्ण

	मुक्त(build_id_path);
	वापस 0;
पूर्ण

#अगर defined(HAVE_LIBBFD_SUPPORT) && defined(HAVE_LIBBPF_SUPPORT)
#घोषणा PACKAGE "perf"
#समावेश <bfd.h>
#समावेश <dis-यंत्र.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/btf.h>
#समावेश <bpf/libbpf.h>
#समावेश <linux/btf.h>

अटल पूर्णांक symbol__disassemble_bpf(काष्ठा symbol *sym,
				   काष्ठा annotate_args *args)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा annotation_options *opts = args->options;
	काष्ठा bpf_prog_info_linear *info_linear;
	काष्ठा bpf_prog_linfo *prog_linfo = शून्य;
	काष्ठा bpf_prog_info_node *info_node;
	पूर्णांक len = sym->end - sym->start;
	disassembler_ftype disassemble;
	काष्ठा map *map = args->ms.map;
	काष्ठा disassemble_info info;
	काष्ठा dso *dso = map->dso;
	पूर्णांक pc = 0, count, sub_id;
	काष्ठा btf *btf = शून्य;
	अक्षर tpath[PATH_MAX];
	माप_प्रकार buf_size;
	पूर्णांक nr_skip = 0;
	अक्षर *buf;
	bfd *bfdf;
	पूर्णांक ret;
	खाता *s;

	अगर (dso->binary_type != DSO_BINARY_TYPE__BPF_PROG_INFO)
		वापस SYMBOL_ANNOTATE_ERRNO__BPF_INVALID_खाता;

	pr_debug("%s: handling sym %s addr %" PRIx64 " len %" PRIx64 "\n", __func__,
		  sym->name, sym->start, sym->end - sym->start);

	स_रखो(tpath, 0, माप(tpath));
	perf_exe(tpath, माप(tpath));

	bfdf = bfd_खोलोr(tpath, शून्य);
	निश्चित(bfdf);
	निश्चित(bfd_check_क्रमmat(bfdf, bfd_object));

	s = खोलो_memstream(&buf, &buf_size);
	अगर (!s) अणु
		ret = त्रुटि_सं;
		जाओ out;
	पूर्ण
	init_disassemble_info(&info, s,
			      (ख_लिखो_ftype) ख_लिखो);

	info.arch = bfd_get_arch(bfdf);
	info.mach = bfd_get_mach(bfdf);

	info_node = perf_env__find_bpf_prog_info(dso->bpf_prog.env,
						 dso->bpf_prog.id);
	अगर (!info_node) अणु
		ret = SYMBOL_ANNOTATE_ERRNO__BPF_MISSING_BTF;
		जाओ out;
	पूर्ण
	info_linear = info_node->info_linear;
	sub_id = dso->bpf_prog.sub_id;

	info.buffer = (व्योम *)(uपूर्णांकptr_t)(info_linear->info.jited_prog_insns);
	info.buffer_length = info_linear->info.jited_prog_len;

	अगर (info_linear->info.nr_line_info)
		prog_linfo = bpf_prog_linfo__new(&info_linear->info);

	अगर (info_linear->info.btf_id) अणु
		काष्ठा btf_node *node;

		node = perf_env__find_btf(dso->bpf_prog.env,
					  info_linear->info.btf_id);
		अगर (node)
			btf = btf__new((__u8 *)(node->data),
				       node->data_size);
	पूर्ण

	disassemble_init_क्रम_target(&info);

#अगर_घोषित DISASM_FOUR_ARGS_SIGNATURE
	disassemble = disassembler(info.arch,
				   bfd_big_endian(bfdf),
				   info.mach,
				   bfdf);
#अन्यथा
	disassemble = disassembler(bfdf);
#पूर्ण_अगर
	निश्चित(disassemble);

	ख_साफ(s);
	करो अणु
		स्थिर काष्ठा bpf_line_info *linfo = शून्य;
		काष्ठा disयंत्र_line *dl;
		माप_प्रकार prev_buf_size;
		स्थिर अक्षर *srcline;
		u64 addr;

		addr = pc + ((u64 *)(uपूर्णांकptr_t)(info_linear->info.jited_ksyms))[sub_id];
		count = disassemble(pc, &info);

		अगर (prog_linfo)
			linfo = bpf_prog_linfo__lfind_addr_func(prog_linfo,
								addr, sub_id,
								nr_skip);

		अगर (linfo && btf) अणु
			srcline = btf__name_by_offset(btf, linfo->line_off);
			nr_skip++;
		पूर्ण अन्यथा
			srcline = शून्य;

		ख_लिखो(s, "\n");
		prev_buf_size = buf_size;
		ख_साफ(s);

		अगर (!opts->hide_src_code && srcline) अणु
			args->offset = -1;
			args->line = strdup(srcline);
			args->line_nr = 0;
			args->fileloc = शून्य;
			args->ms.sym  = sym;
			dl = disयंत्र_line__new(args);
			अगर (dl) अणु
				annotation_line__add(&dl->al,
						     &notes->src->source);
			पूर्ण
		पूर्ण

		args->offset = pc;
		args->line = buf + prev_buf_size;
		args->line_nr = 0;
		args->fileloc = शून्य;
		args->ms.sym  = sym;
		dl = disयंत्र_line__new(args);
		अगर (dl)
			annotation_line__add(&dl->al, &notes->src->source);

		pc += count;
	पूर्ण जबतक (count > 0 && pc < len);

	ret = 0;
out:
	मुक्त(prog_linfo);
	मुक्त(btf);
	ख_बंद(s);
	bfd_बंद(bfdf);
	वापस ret;
पूर्ण
#अन्यथा // defined(HAVE_LIBBFD_SUPPORT) && defined(HAVE_LIBBPF_SUPPORT)
अटल पूर्णांक symbol__disassemble_bpf(काष्ठा symbol *sym __maybe_unused,
				   काष्ठा annotate_args *args __maybe_unused)
अणु
	वापस SYMBOL_ANNOTATE_ERRNO__NO_LIBOPCODES_FOR_BPF;
पूर्ण
#पूर्ण_अगर // defined(HAVE_LIBBFD_SUPPORT) && defined(HAVE_LIBBPF_SUPPORT)

अटल पूर्णांक
symbol__disassemble_bpf_image(काष्ठा symbol *sym,
			      काष्ठा annotate_args *args)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा disयंत्र_line *dl;

	args->offset = -1;
	args->line = strdup("to be implemented");
	args->line_nr = 0;
	args->fileloc = शून्य;
	dl = disयंत्र_line__new(args);
	अगर (dl)
		annotation_line__add(&dl->al, &notes->src->source);

	मुक्त(args->line);
	वापस 0;
पूर्ण

/*
 * Possibly create a new version of line with tअसल expanded. Returns the
 * existing or new line, storage is updated अगर a new line is allocated. If
 * allocation fails then शून्य is वापसed.
 */
अटल अक्षर *expand_tअसल(अक्षर *line, अक्षर **storage, माप_प्रकार *storage_len)
अणु
	माप_प्रकार i, src, dst, len, new_storage_len, num_tअसल;
	अक्षर *new_line;
	माप_प्रकार line_len = म_माप(line);

	क्रम (num_tअसल = 0, i = 0; i < line_len; i++)
		अगर (line[i] == '\t')
			num_tअसल++;

	अगर (num_tअसल == 0)
		वापस line;

	/*
	 * Space क्रम the line and '\0', less the leading and trailing
	 * spaces. Each tab may पूर्णांकroduce 7 additional spaces.
	 */
	new_storage_len = line_len + 1 + (num_tअसल * 7);

	new_line = दो_स्मृति(new_storage_len);
	अगर (new_line == शून्य) अणु
		pr_err("Failure allocating memory for tab expansion\n");
		वापस शून्य;
	पूर्ण

	/*
	 * Copy regions starting at src and expand tअसल. If there are two
	 * adjacent tअसल then 'src == i', the स_नकल is of size 0 and the spaces
	 * are inserted.
	 */
	क्रम (i = 0, src = 0, dst = 0; i < line_len && num_tअसल; i++) अणु
		अगर (line[i] == '\t') अणु
			len = i - src;
			स_नकल(&new_line[dst], &line[src], len);
			dst += len;
			new_line[dst++] = ' ';
			जबतक (dst % 8 != 0)
				new_line[dst++] = ' ';
			src = i + 1;
			num_tअसल--;
		पूर्ण
	पूर्ण

	/* Expand the last region. */
	len = line_len - src;
	स_नकल(&new_line[dst], &line[src], len);
	dst += len;
	new_line[dst] = '\0';

	मुक्त(*storage);
	*storage = new_line;
	*storage_len = new_storage_len;
	वापस new_line;

पूर्ण

अटल पूर्णांक symbol__disassemble(काष्ठा symbol *sym, काष्ठा annotate_args *args)
अणु
	काष्ठा annotation_options *opts = args->options;
	काष्ठा map *map = args->ms.map;
	काष्ठा dso *dso = map->dso;
	अक्षर *command;
	खाता *file;
	अक्षर symfs_filename[PATH_MAX];
	काष्ठा kcore_extract kce;
	bool delete_extract = false;
	bool decomp = false;
	पूर्णांक lineno = 0;
	अक्षर *fileloc = शून्य;
	पूर्णांक nline;
	अक्षर *line;
	माप_प्रकार line_len;
	स्थिर अक्षर *objdump_argv[] = अणु
		"/bin/sh",
		"-c",
		शून्य, /* Will be the objdump command to run. */
		"--",
		शून्य, /* Will be the symfs path. */
		शून्य,
	पूर्ण;
	काष्ठा child_process objdump_process;
	पूर्णांक err = dso__disassemble_filename(dso, symfs_filename, माप(symfs_filename));

	अगर (err)
		वापस err;

	pr_debug("%s: filename=%s, sym=%s, start=%#" PRIx64 ", end=%#" PRIx64 "\n", __func__,
		 symfs_filename, sym->name, map->unmap_ip(map, sym->start),
		 map->unmap_ip(map, sym->end));

	pr_debug("annotating [%p] %30s : [%p] %30s\n",
		 dso, dso->दीर्घ_name, sym, sym->name);

	अगर (dso->binary_type == DSO_BINARY_TYPE__BPF_PROG_INFO) अणु
		वापस symbol__disassemble_bpf(sym, args);
	पूर्ण अन्यथा अगर (dso->binary_type == DSO_BINARY_TYPE__BPF_IMAGE) अणु
		वापस symbol__disassemble_bpf_image(sym, args);
	पूर्ण अन्यथा अगर (dso__is_kcore(dso)) अणु
		kce.kcore_filename = symfs_filename;
		kce.addr = map__rip_2objdump(map, sym->start);
		kce.offs = sym->start;
		kce.len = sym->end - sym->start;
		अगर (!kcore_extract__create(&kce)) अणु
			delete_extract = true;
			strlcpy(symfs_filename, kce.extract_filename,
				माप(symfs_filename));
		पूर्ण
	पूर्ण अन्यथा अगर (dso__needs_decompress(dso)) अणु
		अक्षर पंचांगp[KMOD_DECOMP_LEN];

		अगर (dso__decompress_kmodule_path(dso, symfs_filename,
						 पंचांगp, माप(पंचांगp)) < 0)
			वापस -1;

		decomp = true;
		म_नकल(symfs_filename, पंचांगp);
	पूर्ण

	err = aप्र_लिखो(&command,
		 "%s %s%s --start-address=0x%016" PRIx64
		 " --stop-address=0x%016" PRIx64
		 " -l -d %s %s %s %c%s%c %s%s -C \"$1\"",
		 opts->objdump_path ?: "objdump",
		 opts->disassembler_style ? "-M " : "",
		 opts->disassembler_style ?: "",
		 map__rip_2objdump(map, sym->start),
		 map__rip_2objdump(map, sym->end),
		 opts->show_यंत्र_raw ? "" : "--no-show-raw-insn",
		 opts->annotate_src ? "-S" : "",
		 opts->prefix ? "--prefix " : "",
		 opts->prefix ? '"' : ' ',
		 opts->prefix ?: "",
		 opts->prefix ? '"' : ' ',
		 opts->prefix_strip ? "--prefix-strip=" : "",
		 opts->prefix_strip ?: "");

	अगर (err < 0) अणु
		pr_err("Failure allocating memory for the command to run\n");
		जाओ out_हटाओ_पंचांगp;
	पूर्ण

	pr_debug("Executing: %s\n", command);

	objdump_argv[2] = command;
	objdump_argv[4] = symfs_filename;

	/* Create a pipe to पढ़ो from क्रम मानक_निकास */
	स_रखो(&objdump_process, 0, माप(objdump_process));
	objdump_process.argv = objdump_argv;
	objdump_process.out = -1;
	अगर (start_command(&objdump_process)) अणु
		pr_err("Failure starting to run %s\n", command);
		err = -1;
		जाओ out_मुक्त_command;
	पूर्ण

	file = fकरोpen(objdump_process.out, "r");
	अगर (!file) अणु
		pr_err("Failure creating FILE stream for %s\n", command);
		/*
		 * If we were using debug info should retry with
		 * original binary.
		 */
		err = -1;
		जाओ out_बंद_मानक_निकास;
	पूर्ण

	/* Storage क्रम getline. */
	line = शून्य;
	line_len = 0;

	nline = 0;
	जबतक (!ख_पूर्ण(file)) अणु
		स्थिर अक्षर *match;
		अक्षर *expanded_line;

		अगर (getline(&line, &line_len, file) < 0 || !line)
			अवरोध;

		/* Skip lines containing "filename:" */
		match = म_माला(line, symfs_filename);
		अगर (match && match[म_माप(symfs_filename)] == ':')
			जारी;

		expanded_line = strim(line);
		expanded_line = expand_tअसल(expanded_line, &line, &line_len);
		अगर (!expanded_line)
			अवरोध;

		/*
		 * The source code line number (lineno) needs to be kept in
		 * across calls to symbol__parse_objdump_line(), so that it
		 * can associate it with the inकाष्ठाions till the next one.
		 * See disयंत्र_line__new() and काष्ठा disयंत्र_line::line_nr.
		 */
		अगर (symbol__parse_objdump_line(sym, args, expanded_line,
					       &lineno, &fileloc) < 0)
			अवरोध;
		nline++;
	पूर्ण
	मुक्त(line);

	err = finish_command(&objdump_process);
	अगर (err)
		pr_err("Error running %s\n", command);

	अगर (nline == 0) अणु
		err = -1;
		pr_err("No output from %s\n", command);
	पूर्ण

	/*
	 * kallsyms करोes not have symbol sizes so there may a nop at the end.
	 * Remove it.
	 */
	अगर (dso__is_kcore(dso))
		delete_last_nop(sym);

	ख_बंद(file);

out_बंद_मानक_निकास:
	बंद(objdump_process.out);

out_मुक्त_command:
	मुक्त(command);

out_हटाओ_पंचांगp:
	अगर (decomp)
		unlink(symfs_filename);

	अगर (delete_extract)
		kcore_extract__delete(&kce);

	वापस err;
पूर्ण

अटल व्योम calc_percent(काष्ठा sym_hist *sym_hist,
			 काष्ठा hists *hists,
			 काष्ठा annotation_data *data,
			 s64 offset, s64 end)
अणु
	अचिन्हित पूर्णांक hits = 0;
	u64 period = 0;

	जबतक (offset < end) अणु
		hits   += sym_hist->addr[offset].nr_samples;
		period += sym_hist->addr[offset].period;
		++offset;
	पूर्ण

	अगर (sym_hist->nr_samples) अणु
		data->he.period     = period;
		data->he.nr_samples = hits;
		data->percent[PERCENT_HITS_LOCAL] = 100.0 * hits / sym_hist->nr_samples;
	पूर्ण

	अगर (hists->stats.nr_non_filtered_samples)
		data->percent[PERCENT_HITS_GLOBAL] = 100.0 * hits / hists->stats.nr_non_filtered_samples;

	अगर (sym_hist->period)
		data->percent[PERCENT_PERIOD_LOCAL] = 100.0 * period / sym_hist->period;

	अगर (hists->stats.total_period)
		data->percent[PERCENT_PERIOD_GLOBAL] = 100.0 * period / hists->stats.total_period;
पूर्ण

अटल व्योम annotation__calc_percent(काष्ठा annotation *notes,
				     काष्ठा evsel *leader, s64 len)
अणु
	काष्ठा annotation_line *al, *next;
	काष्ठा evsel *evsel;

	list_क्रम_each_entry(al, &notes->src->source, node) अणु
		s64 end;
		पूर्णांक i = 0;

		अगर (al->offset == -1)
			जारी;

		next = annotation_line__next(al, &notes->src->source);
		end  = next ? next->offset : len;

		क्रम_each_group_evsel(evsel, leader) अणु
			काष्ठा hists *hists = evsel__hists(evsel);
			काष्ठा annotation_data *data;
			काष्ठा sym_hist *sym_hist;

			BUG_ON(i >= al->data_nr);

			sym_hist = annotation__histogram(notes, evsel->idx);
			data = &al->data[i++];

			calc_percent(sym_hist, hists, data, al->offset, end);
		पूर्ण
	पूर्ण
पूर्ण

व्योम symbol__calc_percent(काष्ठा symbol *sym, काष्ठा evsel *evsel)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);

	annotation__calc_percent(notes, evsel, symbol__size(sym));
पूर्ण

पूर्णांक symbol__annotate(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
		     काष्ठा annotation_options *options, काष्ठा arch **parch)
अणु
	काष्ठा symbol *sym = ms->sym;
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा annotate_args args = अणु
		.evsel		= evsel,
		.options	= options,
	पूर्ण;
	काष्ठा perf_env *env = evsel__env(evsel);
	स्थिर अक्षर *arch_name = perf_env__arch(env);
	काष्ठा arch *arch;
	पूर्णांक err;

	अगर (!arch_name)
		वापस त्रुटि_सं;

	args.arch = arch = arch__find(arch_name);
	अगर (arch == शून्य)
		वापस ENOTSUP;

	अगर (parch)
		*parch = arch;

	अगर (arch->init) अणु
		err = arch->init(arch, env ? env->cpuid : शून्य);
		अगर (err) अणु
			pr_err("%s: failed to initialize %s arch priv area\n", __func__, arch->name);
			वापस err;
		पूर्ण
	पूर्ण

	args.ms = *ms;
	notes->start = map__rip_2objdump(ms->map, sym->start);

	वापस symbol__disassemble(sym, &args);
पूर्ण

अटल व्योम insert_source_line(काष्ठा rb_root *root, काष्ठा annotation_line *al,
			       काष्ठा annotation_options *opts)
अणु
	काष्ठा annotation_line *iter;
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	पूर्णांक i, ret;

	जबतक (*p != शून्य) अणु
		parent = *p;
		iter = rb_entry(parent, काष्ठा annotation_line, rb_node);

		ret = म_भेद(iter->path, al->path);
		अगर (ret == 0) अणु
			क्रम (i = 0; i < al->data_nr; i++) अणु
				iter->data[i].percent_sum += annotation_data__percent(&al->data[i],
										      opts->percent_type);
			पूर्ण
			वापस;
		पूर्ण

		अगर (ret < 0)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	क्रम (i = 0; i < al->data_nr; i++) अणु
		al->data[i].percent_sum = annotation_data__percent(&al->data[i],
								   opts->percent_type);
	पूर्ण

	rb_link_node(&al->rb_node, parent, p);
	rb_insert_color(&al->rb_node, root);
पूर्ण

अटल पूर्णांक cmp_source_line(काष्ठा annotation_line *a, काष्ठा annotation_line *b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < a->data_nr; i++) अणु
		अगर (a->data[i].percent_sum == b->data[i].percent_sum)
			जारी;
		वापस a->data[i].percent_sum > b->data[i].percent_sum;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __resort_source_line(काष्ठा rb_root *root, काष्ठा annotation_line *al)
अणु
	काष्ठा annotation_line *iter;
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;

	जबतक (*p != शून्य) अणु
		parent = *p;
		iter = rb_entry(parent, काष्ठा annotation_line, rb_node);

		अगर (cmp_source_line(al, iter))
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	rb_link_node(&al->rb_node, parent, p);
	rb_insert_color(&al->rb_node, root);
पूर्ण

अटल व्योम resort_source_line(काष्ठा rb_root *dest_root, काष्ठा rb_root *src_root)
अणु
	काष्ठा annotation_line *al;
	काष्ठा rb_node *node;

	node = rb_first(src_root);
	जबतक (node) अणु
		काष्ठा rb_node *next;

		al = rb_entry(node, काष्ठा annotation_line, rb_node);
		next = rb_next(node);
		rb_erase(node, src_root);

		__resort_source_line(dest_root, al);
		node = next;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_summary(काष्ठा rb_root *root, स्थिर अक्षर *filename)
अणु
	काष्ठा annotation_line *al;
	काष्ठा rb_node *node;

	म_लिखो("\nSorted summary for file %s\n", filename);
	म_लिखो("----------------------------------------------\n\n");

	अगर (RB_EMPTY_ROOT(root)) अणु
		म_लिखो(" Nothing higher than %1.1f%%\n", MIN_GREEN);
		वापस;
	पूर्ण

	node = rb_first(root);
	जबतक (node) अणु
		द्विगुन percent, percent_max = 0.0;
		स्थिर अक्षर *color;
		अक्षर *path;
		पूर्णांक i;

		al = rb_entry(node, काष्ठा annotation_line, rb_node);
		क्रम (i = 0; i < al->data_nr; i++) अणु
			percent = al->data[i].percent_sum;
			color = get_percent_color(percent);
			color_ख_लिखो(मानक_निकास, color, " %7.2f", percent);

			अगर (percent > percent_max)
				percent_max = percent;
		पूर्ण

		path = al->path;
		color = get_percent_color(percent_max);
		color_ख_लिखो(मानक_निकास, color, " %s\n", path);

		node = rb_next(node);
	पूर्ण
पूर्ण

अटल व्योम symbol__annotate_hits(काष्ठा symbol *sym, काष्ठा evsel *evsel)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा sym_hist *h = annotation__histogram(notes, evsel->idx);
	u64 len = symbol__size(sym), offset;

	क्रम (offset = 0; offset < len; ++offset)
		अगर (h->addr[offset].nr_samples != 0)
			म_लिखो("%*" PRIx64 ": %" PRIu64 "\n", BITS_PER_LONG / 2,
			       sym->start + offset, h->addr[offset].nr_samples);
	म_लिखो("%*s: %" PRIu64 "\n", BITS_PER_LONG / 2, "h->nr_samples", h->nr_samples);
पूर्ण

अटल पूर्णांक annotated_source__addr_fmt_width(काष्ठा list_head *lines, u64 start)
अणु
	अक्षर bf[32];
	काष्ठा annotation_line *line;

	list_क्रम_each_entry_reverse(line, lines, node) अणु
		अगर (line->offset != -1)
			वापस scnम_लिखो(bf, माप(bf), "%" PRIx64, start + line->offset);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक symbol__annotate_म_लिखो(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
			    काष्ठा annotation_options *opts)
अणु
	काष्ठा map *map = ms->map;
	काष्ठा symbol *sym = ms->sym;
	काष्ठा dso *dso = map->dso;
	अक्षर *filename;
	स्थिर अक्षर *d_filename;
	स्थिर अक्षर *evsel_name = evsel__name(evsel);
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा sym_hist *h = annotation__histogram(notes, evsel->idx);
	काष्ठा annotation_line *pos, *queue = शून्य;
	u64 start = map__rip_2objdump(map, sym->start);
	पूर्णांक prपूर्णांकed = 2, queue_len = 0, addr_fmt_width;
	पूर्णांक more = 0;
	bool context = opts->context;
	u64 len;
	पूर्णांक width = symbol_conf.show_total_period ? 12 : 8;
	पूर्णांक graph_करोtted_len;
	अक्षर buf[512];

	filename = strdup(dso->दीर्घ_name);
	अगर (!filename)
		वापस -ENOMEM;

	अगर (opts->full_path)
		d_filename = filename;
	अन्यथा
		d_filename = basename(filename);

	len = symbol__size(sym);

	अगर (evsel__is_group_event(evsel)) अणु
		width *= evsel->core.nr_members;
		evsel__group_desc(evsel, buf, माप(buf));
		evsel_name = buf;
	पूर्ण

	graph_करोtted_len = म_लिखो(" %-*.*s|	Source code & Disassembly of %s for %s (%" PRIu64 " samples, "
				  "percent: %s)\n",
				  width, width, symbol_conf.show_total_period ? "Period" :
				  symbol_conf.show_nr_samples ? "Samples" : "Percent",
				  d_filename, evsel_name, h->nr_samples,
				  percent_type_str(opts->percent_type));

	म_लिखो("%-*.*s----\n",
	       graph_करोtted_len, graph_करोtted_len, graph_करोtted_line);

	अगर (verbose > 0)
		symbol__annotate_hits(sym, evsel);

	addr_fmt_width = annotated_source__addr_fmt_width(&notes->src->source, start);

	list_क्रम_each_entry(pos, &notes->src->source, node) अणु
		पूर्णांक err;

		अगर (context && queue == शून्य) अणु
			queue = pos;
			queue_len = 0;
		पूर्ण

		err = annotation_line__prपूर्णांक(pos, sym, start, evsel, len,
					     opts->min_pcnt, prपूर्णांकed, opts->max_lines,
					     queue, addr_fmt_width, opts->percent_type);

		चयन (err) अणु
		हाल 0:
			++prपूर्णांकed;
			अगर (context) अणु
				prपूर्णांकed += queue_len;
				queue = शून्य;
				queue_len = 0;
			पूर्ण
			अवरोध;
		हाल 1:
			/* filtered by max_lines */
			++more;
			अवरोध;
		हाल -1:
		शेष:
			/*
			 * Filtered by min_pcnt or non IP lines when
			 * context != 0
			 */
			अगर (!context)
				अवरोध;
			अगर (queue_len == context)
				queue = list_entry(queue->node.next, typeof(*queue), node);
			अन्यथा
				++queue_len;
			अवरोध;
		पूर्ण
	पूर्ण

	मुक्त(filename);

	वापस more;
पूर्ण

अटल व्योम खाता__set_percent_color(व्योम *fp __maybe_unused,
				    द्विगुन percent __maybe_unused,
				    bool current __maybe_unused)
अणु
पूर्ण

अटल पूर्णांक खाता__set_jumps_percent_color(व्योम *fp __maybe_unused,
					 पूर्णांक nr __maybe_unused, bool current __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक खाता__set_color(व्योम *fp __maybe_unused, पूर्णांक color __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल व्योम खाता__म_लिखो(व्योम *fp, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	भख_लिखो(fp, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल व्योम खाता__ग_लिखो_graph(व्योम *fp, पूर्णांक graph)
अणु
	स्थिर अक्षर *s;
	चयन (graph) अणु

	हाल DARROW_CHAR: s = "ै"; अवरोध;
	हाल UARROW_CHAR: s = "ै"; अवरोध;
	हाल LARROW_CHAR: s = "ै"; अवरोध;
	हाल RARROW_CHAR: s = "ै"; अवरोध;
	शेष:		s = "?"; अवरोध;
	पूर्ण

	ख_माला_दो(s, fp);
पूर्ण

अटल पूर्णांक symbol__annotate_ख_लिखो2(काष्ठा symbol *sym, खाता *fp,
				     काष्ठा annotation_options *opts)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा annotation_ग_लिखो_ops wops = अणु
		.first_line		 = true,
		.obj			 = fp,
		.set_color		 = खाता__set_color,
		.set_percent_color	 = खाता__set_percent_color,
		.set_jumps_percent_color = खाता__set_jumps_percent_color,
		.म_लिखो			 = खाता__म_लिखो,
		.ग_लिखो_graph		 = खाता__ग_लिखो_graph,
	पूर्ण;
	काष्ठा annotation_line *al;

	list_क्रम_each_entry(al, &notes->src->source, node) अणु
		अगर (annotation_line__filter(al, notes))
			जारी;
		annotation_line__ग_लिखो(al, notes, &wops, opts);
		ख_अक्षर_दो('\n', fp);
		wops.first_line = false;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक map_symbol__annotation_dump(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
				काष्ठा annotation_options *opts)
अणु
	स्थिर अक्षर *ev_name = evsel__name(evsel);
	अक्षर buf[1024];
	अक्षर *filename;
	पूर्णांक err = -1;
	खाता *fp;

	अगर (aप्र_लिखो(&filename, "%s.annotation", ms->sym->name) < 0)
		वापस -1;

	fp = ख_खोलो(filename, "w");
	अगर (fp == शून्य)
		जाओ out_मुक्त_filename;

	अगर (evsel__is_group_event(evsel)) अणु
		evsel__group_desc(evsel, buf, माप(buf));
		ev_name = buf;
	पूर्ण

	ख_लिखो(fp, "%s() %s\nEvent: %s\n\n",
		ms->sym->name, ms->map->dso->दीर्घ_name, ev_name);
	symbol__annotate_ख_लिखो2(ms->sym, fp, opts);

	ख_बंद(fp);
	err = 0;
out_मुक्त_filename:
	मुक्त(filename);
	वापस err;
पूर्ण

व्योम symbol__annotate_zero_histogram(काष्ठा symbol *sym, पूर्णांक evidx)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा sym_hist *h = annotation__histogram(notes, evidx);

	स_रखो(h, 0, notes->src->माप_sym_hist);
पूर्ण

व्योम symbol__annotate_decay_histogram(काष्ठा symbol *sym, पूर्णांक evidx)
अणु
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा sym_hist *h = annotation__histogram(notes, evidx);
	पूर्णांक len = symbol__size(sym), offset;

	h->nr_samples = 0;
	क्रम (offset = 0; offset < len; ++offset) अणु
		h->addr[offset].nr_samples = h->addr[offset].nr_samples * 7 / 8;
		h->nr_samples += h->addr[offset].nr_samples;
	पूर्ण
पूर्ण

व्योम annotated_source__purge(काष्ठा annotated_source *as)
अणु
	काष्ठा annotation_line *al, *n;

	list_क्रम_each_entry_safe(al, n, &as->source, node) अणु
		list_del_init(&al->node);
		disयंत्र_line__मुक्त(disयंत्र_line(al));
	पूर्ण
पूर्ण

अटल माप_प्रकार disयंत्र_line__ख_लिखो(काष्ठा disयंत्र_line *dl, खाता *fp)
अणु
	माप_प्रकार prपूर्णांकed;

	अगर (dl->al.offset == -1)
		वापस ख_लिखो(fp, "%s\n", dl->al.line);

	prपूर्णांकed = ख_लिखो(fp, "%#" PRIx64 " %s", dl->al.offset, dl->ins.name);

	अगर (dl->ops.raw[0] != '\0') अणु
		prपूर्णांकed += ख_लिखो(fp, "%.*s %s\n", 6 - (पूर्णांक)prपूर्णांकed, " ",
				   dl->ops.raw);
	पूर्ण

	वापस prपूर्णांकed + ख_लिखो(fp, "\n");
पूर्ण

माप_प्रकार disयंत्र__ख_लिखो(काष्ठा list_head *head, खाता *fp)
अणु
	काष्ठा disयंत्र_line *pos;
	माप_प्रकार prपूर्णांकed = 0;

	list_क्रम_each_entry(pos, head, al.node)
		prपूर्णांकed += disयंत्र_line__ख_लिखो(pos, fp);

	वापस prपूर्णांकed;
पूर्ण

bool disयंत्र_line__is_valid_local_jump(काष्ठा disयंत्र_line *dl, काष्ठा symbol *sym)
अणु
	अगर (!dl || !dl->ins.ops || !ins__is_jump(&dl->ins) ||
	    !disयंत्र_line__has_local_offset(dl) || dl->ops.target.offset < 0 ||
	    dl->ops.target.offset >= (s64)symbol__size(sym))
		वापस false;

	वापस true;
पूर्ण

व्योम annotation__mark_jump_tarमाला_लो(काष्ठा annotation *notes, काष्ठा symbol *sym)
अणु
	u64 offset, size = symbol__size(sym);

	/* PLT symbols contain बाह्यal offsets */
	अगर (म_माला(sym->name, "@plt"))
		वापस;

	क्रम (offset = 0; offset < size; ++offset) अणु
		काष्ठा annotation_line *al = notes->offsets[offset];
		काष्ठा disयंत्र_line *dl;

		dl = disयंत्र_line(al);

		अगर (!disयंत्र_line__is_valid_local_jump(dl, sym))
			जारी;

		al = notes->offsets[dl->ops.target.offset];

		/*
		 * FIXME: Oops, no jump target? Buggy disassembler? Or करो we
		 * have to adjust to the previous offset?
		 */
		अगर (al == शून्य)
			जारी;

		अगर (++al->jump_sources > notes->max_jump_sources)
			notes->max_jump_sources = al->jump_sources;
	पूर्ण
पूर्ण

व्योम annotation__set_offsets(काष्ठा annotation *notes, s64 size)
अणु
	काष्ठा annotation_line *al;

	notes->max_line_len = 0;
	notes->nr_entries = 0;
	notes->nr_यंत्र_entries = 0;

	list_क्रम_each_entry(al, &notes->src->source, node) अणु
		माप_प्रकार line_len = म_माप(al->line);

		अगर (notes->max_line_len < line_len)
			notes->max_line_len = line_len;
		al->idx = notes->nr_entries++;
		अगर (al->offset != -1) अणु
			al->idx_यंत्र = notes->nr_यंत्र_entries++;
			/*
			 * FIXME: लघु term bandaid to cope with assembly
			 * routines that comes with labels in the same column
			 * as the address in objdump, sigh.
			 *
			 * E.g. copy_user_generic_unrolled
 			 */
			अगर (al->offset < size)
				notes->offsets[al->offset] = al;
		पूर्ण अन्यथा
			al->idx_यंत्र = -1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक width_jumps(पूर्णांक n)
अणु
	अगर (n >= 100)
		वापस 5;
	अगर (n / 10)
		वापस 2;
	वापस 1;
पूर्ण

अटल पूर्णांक annotation__max_ins_name(काष्ठा annotation *notes)
अणु
	पूर्णांक max_name = 0, len;
	काष्ठा annotation_line *al;

        list_क्रम_each_entry(al, &notes->src->source, node) अणु
		अगर (al->offset == -1)
			जारी;

		len = म_माप(disयंत्र_line(al)->ins.name);
		अगर (max_name < len)
			max_name = len;
	पूर्ण

	वापस max_name;
पूर्ण

व्योम annotation__init_column_widths(काष्ठा annotation *notes, काष्ठा symbol *sym)
अणु
	notes->widths.addr = notes->widths.target =
		notes->widths.min_addr = hex_width(symbol__size(sym));
	notes->widths.max_addr = hex_width(sym->end);
	notes->widths.jumps = width_jumps(notes->max_jump_sources);
	notes->widths.max_ins_name = annotation__max_ins_name(notes);
पूर्ण

व्योम annotation__update_column_widths(काष्ठा annotation *notes)
अणु
	अगर (notes->options->use_offset)
		notes->widths.target = notes->widths.min_addr;
	अन्यथा
		notes->widths.target = notes->widths.max_addr;

	notes->widths.addr = notes->widths.target;

	अगर (notes->options->show_nr_jumps)
		notes->widths.addr += notes->widths.jumps + 1;
पूर्ण

अटल व्योम annotation__calc_lines(काष्ठा annotation *notes, काष्ठा map *map,
				   काष्ठा rb_root *root,
				   काष्ठा annotation_options *opts)
अणु
	काष्ठा annotation_line *al;
	काष्ठा rb_root पंचांगp_root = RB_ROOT;

	list_क्रम_each_entry(al, &notes->src->source, node) अणु
		द्विगुन percent_max = 0.0;
		पूर्णांक i;

		क्रम (i = 0; i < al->data_nr; i++) अणु
			द्विगुन percent;

			percent = annotation_data__percent(&al->data[i],
							   opts->percent_type);

			अगर (percent > percent_max)
				percent_max = percent;
		पूर्ण

		अगर (percent_max <= 0.5)
			जारी;

		al->path = get_srcline(map->dso, notes->start + al->offset, शून्य,
				       false, true, notes->start + al->offset);
		insert_source_line(&पंचांगp_root, al, opts);
	पूर्ण

	resort_source_line(root, &पंचांगp_root);
पूर्ण

अटल व्योम symbol__calc_lines(काष्ठा map_symbol *ms, काष्ठा rb_root *root,
			       काष्ठा annotation_options *opts)
अणु
	काष्ठा annotation *notes = symbol__annotation(ms->sym);

	annotation__calc_lines(notes, ms->map, root, opts);
पूर्ण

पूर्णांक symbol__tty_annotate2(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
			  काष्ठा annotation_options *opts)
अणु
	काष्ठा dso *dso = ms->map->dso;
	काष्ठा symbol *sym = ms->sym;
	काष्ठा rb_root source_line = RB_ROOT;
	काष्ठा hists *hists = evsel__hists(evsel);
	अक्षर buf[1024];

	अगर (symbol__annotate2(ms, evsel, opts, शून्य) < 0)
		वापस -1;

	अगर (opts->prपूर्णांक_lines) अणु
		srcline_full_filename = opts->full_path;
		symbol__calc_lines(ms, &source_line, opts);
		prपूर्णांक_summary(&source_line, dso->दीर्घ_name);
	पूर्ण

	hists__scnम_लिखो_title(hists, buf, माप(buf));
	ख_लिखो(मानक_निकास, "%s, [percent: %s]\n%s() %s\n",
		buf, percent_type_str(opts->percent_type), sym->name, dso->दीर्घ_name);
	symbol__annotate_ख_लिखो2(sym, मानक_निकास, opts);

	annotated_source__purge(symbol__annotation(sym)->src);

	वापस 0;
पूर्ण

पूर्णांक symbol__tty_annotate(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
			 काष्ठा annotation_options *opts)
अणु
	काष्ठा dso *dso = ms->map->dso;
	काष्ठा symbol *sym = ms->sym;
	काष्ठा rb_root source_line = RB_ROOT;

	अगर (symbol__annotate(ms, evsel, opts, शून्य) < 0)
		वापस -1;

	symbol__calc_percent(sym, evsel);

	अगर (opts->prपूर्णांक_lines) अणु
		srcline_full_filename = opts->full_path;
		symbol__calc_lines(ms, &source_line, opts);
		prपूर्णांक_summary(&source_line, dso->दीर्घ_name);
	पूर्ण

	symbol__annotate_म_लिखो(ms, evsel, opts);

	annotated_source__purge(symbol__annotation(sym)->src);

	वापस 0;
पूर्ण

bool ui__has_annotation(व्योम)
अणु
	वापस use_browser == 1 && perf_hpp_list.sym;
पूर्ण


अटल द्विगुन annotation_line__max_percent(काष्ठा annotation_line *al,
					   काष्ठा annotation *notes,
					   अचिन्हित पूर्णांक percent_type)
अणु
	द्विगुन percent_max = 0.0;
	पूर्णांक i;

	क्रम (i = 0; i < notes->nr_events; i++) अणु
		द्विगुन percent;

		percent = annotation_data__percent(&al->data[i],
						   percent_type);

		अगर (percent > percent_max)
			percent_max = percent;
	पूर्ण

	वापस percent_max;
पूर्ण

अटल व्योम disयंत्र_line__ग_लिखो(काष्ठा disयंत्र_line *dl, काष्ठा annotation *notes,
			       व्योम *obj, अक्षर *bf, माप_प्रकार size,
			       व्योम (*obj__म_लिखो)(व्योम *obj, स्थिर अक्षर *fmt, ...),
			       व्योम (*obj__ग_लिखो_graph)(व्योम *obj, पूर्णांक graph))
अणु
	अगर (dl->ins.ops && dl->ins.ops->scnम_लिखो) अणु
		अगर (ins__is_jump(&dl->ins)) अणु
			bool fwd;

			अगर (dl->ops.target.outside)
				जाओ call_like;
			fwd = dl->ops.target.offset > dl->al.offset;
			obj__ग_लिखो_graph(obj, fwd ? DARROW_CHAR : UARROW_CHAR);
			obj__म_लिखो(obj, " ");
		पूर्ण अन्यथा अगर (ins__is_call(&dl->ins)) अणु
call_like:
			obj__ग_लिखो_graph(obj, RARROW_CHAR);
			obj__म_लिखो(obj, " ");
		पूर्ण अन्यथा अगर (ins__is_ret(&dl->ins)) अणु
			obj__ग_लिखो_graph(obj, LARROW_CHAR);
			obj__म_लिखो(obj, " ");
		पूर्ण अन्यथा अणु
			obj__म_लिखो(obj, "  ");
		पूर्ण
	पूर्ण अन्यथा अणु
		obj__म_लिखो(obj, "  ");
	पूर्ण

	disयंत्र_line__scnम_लिखो(dl, bf, size, !notes->options->use_offset, notes->widths.max_ins_name);
पूर्ण

अटल व्योम ipc_coverage_string(अक्षर *bf, पूर्णांक size, काष्ठा annotation *notes)
अणु
	द्विगुन ipc = 0.0, coverage = 0.0;

	अगर (notes->hit_cycles)
		ipc = notes->hit_insn / ((द्विगुन)notes->hit_cycles);

	अगर (notes->total_insn) अणु
		coverage = notes->cover_insn * 100.0 /
			((द्विगुन)notes->total_insn);
	पूर्ण

	scnम_लिखो(bf, size, "(Average IPC: %.2f, IPC Coverage: %.1f%%)",
		  ipc, coverage);
पूर्ण

अटल व्योम __annotation_line__ग_लिखो(काष्ठा annotation_line *al, काष्ठा annotation *notes,
				     bool first_line, bool current_entry, bool change_color, पूर्णांक width,
				     व्योम *obj, अचिन्हित पूर्णांक percent_type,
				     पूर्णांक  (*obj__set_color)(व्योम *obj, पूर्णांक color),
				     व्योम (*obj__set_percent_color)(व्योम *obj, द्विगुन percent, bool current),
				     पूर्णांक  (*obj__set_jumps_percent_color)(व्योम *obj, पूर्णांक nr, bool current),
				     व्योम (*obj__म_लिखो)(व्योम *obj, स्थिर अक्षर *fmt, ...),
				     व्योम (*obj__ग_लिखो_graph)(व्योम *obj, पूर्णांक graph))

अणु
	द्विगुन percent_max = annotation_line__max_percent(al, notes, percent_type);
	पूर्णांक pcnt_width = annotation__pcnt_width(notes),
	    cycles_width = annotation__cycles_width(notes);
	bool show_title = false;
	अक्षर bf[256];
	पूर्णांक prपूर्णांकed;

	अगर (first_line && (al->offset == -1 || percent_max == 0.0)) अणु
		अगर (notes->have_cycles) अणु
			अगर (al->ipc == 0.0 && al->cycles == 0)
				show_title = true;
		पूर्ण अन्यथा
			show_title = true;
	पूर्ण

	अगर (al->offset != -1 && percent_max != 0.0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < notes->nr_events; i++) अणु
			द्विगुन percent;

			percent = annotation_data__percent(&al->data[i], percent_type);

			obj__set_percent_color(obj, percent, current_entry);
			अगर (symbol_conf.show_total_period) अणु
				obj__म_लिखो(obj, "%11" PRIu64 " ", al->data[i].he.period);
			पूर्ण अन्यथा अगर (symbol_conf.show_nr_samples) अणु
				obj__म_लिखो(obj, "%6" PRIu64 " ",
						   al->data[i].he.nr_samples);
			पूर्ण अन्यथा अणु
				obj__म_लिखो(obj, "%6.2f ", percent);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		obj__set_percent_color(obj, 0, current_entry);

		अगर (!show_title)
			obj__म_लिखो(obj, "%-*s", pcnt_width, " ");
		अन्यथा अणु
			obj__म_लिखो(obj, "%-*s", pcnt_width,
					   symbol_conf.show_total_period ? "Period" :
					   symbol_conf.show_nr_samples ? "Samples" : "Percent");
		पूर्ण
	पूर्ण

	अगर (notes->have_cycles) अणु
		अगर (al->ipc)
			obj__म_लिखो(obj, "%*.2f ", ANNOTATION__IPC_WIDTH - 1, al->ipc);
		अन्यथा अगर (!show_title)
			obj__म_लिखो(obj, "%*s", ANNOTATION__IPC_WIDTH, " ");
		अन्यथा
			obj__म_लिखो(obj, "%*s ", ANNOTATION__IPC_WIDTH - 1, "IPC");

		अगर (!notes->options->show_minmax_cycle) अणु
			अगर (al->cycles)
				obj__म_लिखो(obj, "%*" PRIu64 " ",
					   ANNOTATION__CYCLES_WIDTH - 1, al->cycles);
			अन्यथा अगर (!show_title)
				obj__म_लिखो(obj, "%*s",
					    ANNOTATION__CYCLES_WIDTH, " ");
			अन्यथा
				obj__म_लिखो(obj, "%*s ",
					    ANNOTATION__CYCLES_WIDTH - 1,
					    "Cycle");
		पूर्ण अन्यथा अणु
			अगर (al->cycles) अणु
				अक्षर str[32];

				scnम_लिखो(str, माप(str),
					"%" PRIu64 "(%" PRIu64 "/%" PRIu64 ")",
					al->cycles, al->cycles_min,
					al->cycles_max);

				obj__म_लिखो(obj, "%*s ",
					    ANNOTATION__MINMAX_CYCLES_WIDTH - 1,
					    str);
			पूर्ण अन्यथा अगर (!show_title)
				obj__म_लिखो(obj, "%*s",
					    ANNOTATION__MINMAX_CYCLES_WIDTH,
					    " ");
			अन्यथा
				obj__म_लिखो(obj, "%*s ",
					    ANNOTATION__MINMAX_CYCLES_WIDTH - 1,
					    "Cycle(min/max)");
		पूर्ण

		अगर (show_title && !*al->line) अणु
			ipc_coverage_string(bf, माप(bf), notes);
			obj__म_लिखो(obj, "%*s", ANNOTATION__AVG_IPC_WIDTH, bf);
		पूर्ण
	पूर्ण

	obj__म_लिखो(obj, " ");

	अगर (!*al->line)
		obj__म_लिखो(obj, "%-*s", width - pcnt_width - cycles_width, " ");
	अन्यथा अगर (al->offset == -1) अणु
		अगर (al->line_nr && notes->options->show_linenr)
			prपूर्णांकed = scnम_लिखो(bf, माप(bf), "%-*d ", notes->widths.addr + 1, al->line_nr);
		अन्यथा
			prपूर्णांकed = scnम_लिखो(bf, माप(bf), "%-*s  ", notes->widths.addr, " ");
		obj__म_लिखो(obj, bf);
		obj__म_लिखो(obj, "%-*s", width - prपूर्णांकed - pcnt_width - cycles_width + 1, al->line);
	पूर्ण अन्यथा अणु
		u64 addr = al->offset;
		पूर्णांक color = -1;

		अगर (!notes->options->use_offset)
			addr += notes->start;

		अगर (!notes->options->use_offset) अणु
			prपूर्णांकed = scnम_लिखो(bf, माप(bf), "%" PRIx64 ": ", addr);
		पूर्ण अन्यथा अणु
			अगर (al->jump_sources &&
			    notes->options->offset_level >= ANNOTATION__OFFSET_JUMP_TARGETS) अणु
				अगर (notes->options->show_nr_jumps) अणु
					पूर्णांक prev;
					prपूर्णांकed = scnम_लिखो(bf, माप(bf), "%*d ",
							    notes->widths.jumps,
							    al->jump_sources);
					prev = obj__set_jumps_percent_color(obj, al->jump_sources,
									    current_entry);
					obj__म_लिखो(obj, bf);
					obj__set_color(obj, prev);
				पूर्ण
prपूर्णांक_addr:
				prपूर्णांकed = scnम_लिखो(bf, माप(bf), "%*" PRIx64 ": ",
						    notes->widths.target, addr);
			पूर्ण अन्यथा अगर (ins__is_call(&disयंत्र_line(al)->ins) &&
				   notes->options->offset_level >= ANNOTATION__OFFSET_CALL) अणु
				जाओ prपूर्णांक_addr;
			पूर्ण अन्यथा अगर (notes->options->offset_level == ANNOTATION__MAX_OFFSET_LEVEL) अणु
				जाओ prपूर्णांक_addr;
			पूर्ण अन्यथा अणु
				prपूर्णांकed = scnम_लिखो(bf, माप(bf), "%-*s  ",
						    notes->widths.addr, " ");
			पूर्ण
		पूर्ण

		अगर (change_color)
			color = obj__set_color(obj, HE_COLORSET_ADDR);
		obj__म_लिखो(obj, bf);
		अगर (change_color)
			obj__set_color(obj, color);

		disयंत्र_line__ग_लिखो(disयंत्र_line(al), notes, obj, bf, माप(bf), obj__म_लिखो, obj__ग_लिखो_graph);

		obj__म_लिखो(obj, "%-*s", width - pcnt_width - cycles_width - 3 - prपूर्णांकed, bf);
	पूर्ण

पूर्ण

व्योम annotation_line__ग_लिखो(काष्ठा annotation_line *al, काष्ठा annotation *notes,
			    काष्ठा annotation_ग_लिखो_ops *wops,
			    काष्ठा annotation_options *opts)
अणु
	__annotation_line__ग_लिखो(al, notes, wops->first_line, wops->current_entry,
				 wops->change_color, wops->width, wops->obj,
				 opts->percent_type,
				 wops->set_color, wops->set_percent_color,
				 wops->set_jumps_percent_color, wops->म_लिखो,
				 wops->ग_लिखो_graph);
पूर्ण

पूर्णांक symbol__annotate2(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
		      काष्ठा annotation_options *options, काष्ठा arch **parch)
अणु
	काष्ठा symbol *sym = ms->sym;
	काष्ठा annotation *notes = symbol__annotation(sym);
	माप_प्रकार size = symbol__size(sym);
	पूर्णांक nr_pcnt = 1, err;

	notes->offsets = zalloc(size * माप(काष्ठा annotation_line *));
	अगर (notes->offsets == शून्य)
		वापस ENOMEM;

	अगर (evsel__is_group_event(evsel))
		nr_pcnt = evsel->core.nr_members;

	err = symbol__annotate(ms, evsel, options, parch);
	अगर (err)
		जाओ out_मुक्त_offsets;

	notes->options = options;

	symbol__calc_percent(sym, evsel);

	annotation__set_offsets(notes, size);
	annotation__mark_jump_tarमाला_लो(notes, sym);
	annotation__compute_ipc(notes, size);
	annotation__init_column_widths(notes, sym);
	notes->nr_events = nr_pcnt;

	annotation__update_column_widths(notes);
	sym->annotate2 = true;

	वापस 0;

out_मुक्त_offsets:
	zमुक्त(&notes->offsets);
	वापस err;
पूर्ण

अटल पूर्णांक annotation__config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *data)
अणु
	काष्ठा annotation_options *opt = data;

	अगर (!strstarts(var, "annotate."))
		वापस 0;

	अगर (!म_भेद(var, "annotate.offset_level")) अणु
		perf_config_u8(&opt->offset_level, "offset_level", value);

		अगर (opt->offset_level > ANNOTATION__MAX_OFFSET_LEVEL)
			opt->offset_level = ANNOTATION__MAX_OFFSET_LEVEL;
		अन्यथा अगर (opt->offset_level < ANNOTATION__MIN_OFFSET_LEVEL)
			opt->offset_level = ANNOTATION__MIN_OFFSET_LEVEL;
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.hide_src_code")) अणु
		opt->hide_src_code = perf_config_bool("hide_src_code", value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.jump_arrows")) अणु
		opt->jump_arrows = perf_config_bool("jump_arrows", value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.show_linenr")) अणु
		opt->show_linenr = perf_config_bool("show_linenr", value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.show_nr_jumps")) अणु
		opt->show_nr_jumps = perf_config_bool("show_nr_jumps", value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.show_nr_samples")) अणु
		symbol_conf.show_nr_samples = perf_config_bool("show_nr_samples",
								value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.show_total_period")) अणु
		symbol_conf.show_total_period = perf_config_bool("show_total_period",
								value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.use_offset")) अणु
		opt->use_offset = perf_config_bool("use_offset", value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.disassembler_style")) अणु
		opt->disassembler_style = value;
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.demangle")) अणु
		symbol_conf.demangle = perf_config_bool("demangle", value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "annotate.demangle_kernel")) अणु
		symbol_conf.demangle_kernel = perf_config_bool("demangle_kernel", value);
	पूर्ण अन्यथा अणु
		pr_debug("%s variable unknown, ignoring...", var);
	पूर्ण

	वापस 0;
पूर्ण

व्योम annotation_config__init(काष्ठा annotation_options *opt)
अणु
	perf_config(annotation__config, opt);
पूर्ण

अटल अचिन्हित पूर्णांक parse_percent_type(अक्षर *str1, अक्षर *str2)
अणु
	अचिन्हित पूर्णांक type = (अचिन्हित पूर्णांक) -1;

	अगर (!म_भेद("period", str1)) अणु
		अगर (!म_भेद("local", str2))
			type = PERCENT_PERIOD_LOCAL;
		अन्यथा अगर (!म_भेद("global", str2))
			type = PERCENT_PERIOD_GLOBAL;
	पूर्ण

	अगर (!म_भेद("hits", str1)) अणु
		अगर (!म_भेद("local", str2))
			type = PERCENT_HITS_LOCAL;
		अन्यथा अगर (!म_भेद("global", str2))
			type = PERCENT_HITS_GLOBAL;
	पूर्ण

	वापस type;
पूर्ण

पूर्णांक annotate_parse_percent_type(स्थिर काष्ठा option *opt, स्थिर अक्षर *_str,
				पूर्णांक unset __maybe_unused)
अणु
	काष्ठा annotation_options *opts = opt->value;
	अचिन्हित पूर्णांक type;
	अक्षर *str1, *str2;
	पूर्णांक err = -1;

	str1 = strdup(_str);
	अगर (!str1)
		वापस -ENOMEM;

	str2 = म_अक्षर(str1, '-');
	अगर (!str2)
		जाओ out;

	*str2++ = 0;

	type = parse_percent_type(str1, str2);
	अगर (type == (अचिन्हित पूर्णांक) -1)
		type = parse_percent_type(str2, str1);
	अगर (type != (अचिन्हित पूर्णांक) -1) अणु
		opts->percent_type = type;
		err = 0;
	पूर्ण

out:
	मुक्त(str1);
	वापस err;
पूर्ण

पूर्णांक annotate_check_args(काष्ठा annotation_options *args)
अणु
	अगर (args->prefix_strip && !args->prefix) अणु
		pr_err("--prefix-strip requires --prefix\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
