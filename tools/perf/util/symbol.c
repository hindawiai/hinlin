<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mman.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय64.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/param.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>
#समावेश "annotate.h"
#समावेश "build-id.h"
#समावेश "cap.h"
#समावेश "dso.h"
#समावेश "util.h" // lsdir()
#समावेश "debug.h"
#समावेश "event.h"
#समावेश "machine.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "map_symbol.h"
#समावेश "mem-events.h"
#समावेश "symsrc.h"
#समावेश "strlist.h"
#समावेश "intlist.h"
#समावेश "namespaces.h"
#समावेश "header.h"
#समावेश "path.h"
#समावेश <linux/प्रकार.स>
#समावेश <linux/zभाग.स>

#समावेश <elf.h>
#समावेश <सीमा.स>
#समावेश <symbol/kallsyms.h>
#समावेश <sys/utsname.h>

अटल पूर्णांक dso__load_kernel_sym(काष्ठा dso *dso, काष्ठा map *map);
अटल पूर्णांक dso__load_guest_kernel_sym(काष्ठा dso *dso, काष्ठा map *map);
अटल bool symbol__is_idle(स्थिर अक्षर *name);

पूर्णांक vmlinux_path__nr_entries;
अक्षर **vmlinux_path;

काष्ठा symbol_conf symbol_conf = अणु
	.nanosecs		= false,
	.use_modules		= true,
	.try_vmlinux_path	= true,
	.demangle		= true,
	.demangle_kernel	= false,
	.cumulate_callchain	= true,
	.समय_quantum		= 100 * NSEC_PER_MSEC, /* 100ms */
	.show_hist_headers	= true,
	.symfs			= "",
	.event_group		= true,
	.अंतरभूत_name		= true,
	.res_sample		= 0,
पूर्ण;

अटल क्रमागत dso_binary_type binary_type_symtab[] = अणु
	DSO_BINARY_TYPE__KALLSYMS,
	DSO_BINARY_TYPE__GUEST_KALLSYMS,
	DSO_BINARY_TYPE__JAVA_JIT,
	DSO_BINARY_TYPE__DEBUGLINK,
	DSO_BINARY_TYPE__BUILD_ID_CACHE,
	DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO,
	DSO_BINARY_TYPE__FEDORA_DEBUGINFO,
	DSO_BINARY_TYPE__UBUNTU_DEBUGINFO,
	DSO_BINARY_TYPE__BUILDID_DEBUGINFO,
	DSO_BINARY_TYPE__SYSTEM_PATH_DSO,
	DSO_BINARY_TYPE__GUEST_KMODULE,
	DSO_BINARY_TYPE__GUEST_KMODULE_COMP,
	DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE,
	DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP,
	DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO,
	DSO_BINARY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO,
	DSO_BINARY_TYPE__NOT_FOUND,
पूर्ण;

#घोषणा DSO_BINARY_TYPE__SYMTAB_CNT ARRAY_SIZE(binary_type_symtab)

अटल bool symbol_type__filter(अक्षर symbol_type)
अणु
	symbol_type = बड़े(symbol_type);
	वापस symbol_type == 'T' || symbol_type == 'W' || symbol_type == 'D' || symbol_type == 'B';
पूर्ण

अटल पूर्णांक prefix_underscores_count(स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *tail = str;

	जबतक (*tail == '_')
		tail++;

	वापस tail - str;
पूर्ण

व्योम __weak arch__symbols__fixup_end(काष्ठा symbol *p, काष्ठा symbol *c)
अणु
	p->end = c->start;
पूर्ण

स्थिर अक्षर * __weak arch__normalize_symbol_name(स्थिर अक्षर *name)
अणु
	वापस name;
पूर्ण

पूर्णांक __weak arch__compare_symbol_names(स्थिर अक्षर *namea, स्थिर अक्षर *nameb)
अणु
	वापस म_भेद(namea, nameb);
पूर्ण

पूर्णांक __weak arch__compare_symbol_names_n(स्थिर अक्षर *namea, स्थिर अक्षर *nameb,
					अचिन्हित पूर्णांक n)
अणु
	वापस म_भेदन(namea, nameb, n);
पूर्ण

पूर्णांक __weak arch__choose_best_symbol(काष्ठा symbol *syma,
				    काष्ठा symbol *symb __maybe_unused)
अणु
	/* Aव्योम "SyS" kernel syscall aliases */
	अगर (म_माप(syma->name) >= 3 && !म_भेदन(syma->name, "SyS", 3))
		वापस SYMBOL_B;
	अगर (म_माप(syma->name) >= 10 && !म_भेदन(syma->name, "compat_SyS", 10))
		वापस SYMBOL_B;

	वापस SYMBOL_A;
पूर्ण

अटल पूर्णांक choose_best_symbol(काष्ठा symbol *syma, काष्ठा symbol *symb)
अणु
	s64 a;
	s64 b;
	माप_प्रकार na, nb;

	/* Prefer a symbol with non zero length */
	a = syma->end - syma->start;
	b = symb->end - symb->start;
	अगर ((b == 0) && (a > 0))
		वापस SYMBOL_A;
	अन्यथा अगर ((a == 0) && (b > 0))
		वापस SYMBOL_B;

	/* Prefer a non weak symbol over a weak one */
	a = syma->binding == STB_WEAK;
	b = symb->binding == STB_WEAK;
	अगर (b && !a)
		वापस SYMBOL_A;
	अगर (a && !b)
		वापस SYMBOL_B;

	/* Prefer a global symbol over a non global one */
	a = syma->binding == STB_GLOBAL;
	b = symb->binding == STB_GLOBAL;
	अगर (a && !b)
		वापस SYMBOL_A;
	अगर (b && !a)
		वापस SYMBOL_B;

	/* Prefer a symbol with less underscores */
	a = prefix_underscores_count(syma->name);
	b = prefix_underscores_count(symb->name);
	अगर (b > a)
		वापस SYMBOL_A;
	अन्यथा अगर (a > b)
		वापस SYMBOL_B;

	/* Choose the symbol with the दीर्घest name */
	na = म_माप(syma->name);
	nb = म_माप(symb->name);
	अगर (na > nb)
		वापस SYMBOL_A;
	अन्यथा अगर (na < nb)
		वापस SYMBOL_B;

	वापस arch__choose_best_symbol(syma, symb);
पूर्ण

व्योम symbols__fixup_duplicate(काष्ठा rb_root_cached *symbols)
अणु
	काष्ठा rb_node *nd;
	काष्ठा symbol *curr, *next;

	अगर (symbol_conf.allow_aliases)
		वापस;

	nd = rb_first_cached(symbols);

	जबतक (nd) अणु
		curr = rb_entry(nd, काष्ठा symbol, rb_node);
again:
		nd = rb_next(&curr->rb_node);
		next = rb_entry(nd, काष्ठा symbol, rb_node);

		अगर (!nd)
			अवरोध;

		अगर (curr->start != next->start)
			जारी;

		अगर (choose_best_symbol(curr, next) == SYMBOL_A) अणु
			rb_erase_cached(&next->rb_node, symbols);
			symbol__delete(next);
			जाओ again;
		पूर्ण अन्यथा अणु
			nd = rb_next(&curr->rb_node);
			rb_erase_cached(&curr->rb_node, symbols);
			symbol__delete(curr);
		पूर्ण
	पूर्ण
पूर्ण

व्योम symbols__fixup_end(काष्ठा rb_root_cached *symbols)
अणु
	काष्ठा rb_node *nd, *prevnd = rb_first_cached(symbols);
	काष्ठा symbol *curr, *prev;

	अगर (prevnd == शून्य)
		वापस;

	curr = rb_entry(prevnd, काष्ठा symbol, rb_node);

	क्रम (nd = rb_next(prevnd); nd; nd = rb_next(nd)) अणु
		prev = curr;
		curr = rb_entry(nd, काष्ठा symbol, rb_node);

		अगर (prev->end == prev->start && prev->end != curr->start)
			arch__symbols__fixup_end(prev, curr);
	पूर्ण

	/* Last entry */
	अगर (curr->end == curr->start)
		curr->end = roundup(curr->start, 4096) + 4096;
पूर्ण

व्योम maps__fixup_end(काष्ठा maps *maps)
अणु
	काष्ठा map *prev = शून्य, *curr;

	करोwn_ग_लिखो(&maps->lock);

	maps__क्रम_each_entry(maps, curr) अणु
		अगर (prev != शून्य && !prev->end)
			prev->end = curr->start;

		prev = curr;
	पूर्ण

	/*
	 * We still haven't the actual symbols, so guess the
	 * last map final address.
	 */
	अगर (curr && !curr->end)
		curr->end = ~0ULL;

	up_ग_लिखो(&maps->lock);
पूर्ण

काष्ठा symbol *symbol__new(u64 start, u64 len, u8 binding, u8 type, स्थिर अक्षर *name)
अणु
	माप_प्रकार namelen = म_माप(name) + 1;
	काष्ठा symbol *sym = सुस्मृति(1, (symbol_conf.priv_size +
					माप(*sym) + namelen));
	अगर (sym == शून्य)
		वापस शून्य;

	अगर (symbol_conf.priv_size) अणु
		अगर (symbol_conf.init_annotation) अणु
			काष्ठा annotation *notes = (व्योम *)sym;
			pthपढ़ो_mutex_init(&notes->lock, शून्य);
		पूर्ण
		sym = ((व्योम *)sym) + symbol_conf.priv_size;
	पूर्ण

	sym->start   = start;
	sym->end     = len ? start + len : start;
	sym->type    = type;
	sym->binding = binding;
	sym->namelen = namelen - 1;

	pr_debug4("%s: %s %#" PRIx64 "-%#" PRIx64 "\n",
		  __func__, name, start, sym->end);
	स_नकल(sym->name, name, namelen);

	वापस sym;
पूर्ण

व्योम symbol__delete(काष्ठा symbol *sym)
अणु
	मुक्त(((व्योम *)sym) - symbol_conf.priv_size);
पूर्ण

व्योम symbols__delete(काष्ठा rb_root_cached *symbols)
अणु
	काष्ठा symbol *pos;
	काष्ठा rb_node *next = rb_first_cached(symbols);

	जबतक (next) अणु
		pos = rb_entry(next, काष्ठा symbol, rb_node);
		next = rb_next(&pos->rb_node);
		rb_erase_cached(&pos->rb_node, symbols);
		symbol__delete(pos);
	पूर्ण
पूर्ण

व्योम __symbols__insert(काष्ठा rb_root_cached *symbols,
		       काष्ठा symbol *sym, bool kernel)
अणु
	काष्ठा rb_node **p = &symbols->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	स्थिर u64 ip = sym->start;
	काष्ठा symbol *s;
	bool lefपंचांगost = true;

	अगर (kernel) अणु
		स्थिर अक्षर *name = sym->name;
		/*
		 * ppc64 uses function descriptors and appends a '.' to the
		 * start of every inकाष्ठाion address. Remove it.
		 */
		अगर (name[0] == '.')
			name++;
		sym->idle = symbol__is_idle(name);
	पूर्ण

	जबतक (*p != शून्य) अणु
		parent = *p;
		s = rb_entry(parent, काष्ठा symbol, rb_node);
		अगर (ip < s->start)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण
	rb_link_node(&sym->rb_node, parent, p);
	rb_insert_color_cached(&sym->rb_node, symbols, lefपंचांगost);
पूर्ण

व्योम symbols__insert(काष्ठा rb_root_cached *symbols, काष्ठा symbol *sym)
अणु
	__symbols__insert(symbols, sym, false);
पूर्ण

अटल काष्ठा symbol *symbols__find(काष्ठा rb_root_cached *symbols, u64 ip)
अणु
	काष्ठा rb_node *n;

	अगर (symbols == शून्य)
		वापस शून्य;

	n = symbols->rb_root.rb_node;

	जबतक (n) अणु
		काष्ठा symbol *s = rb_entry(n, काष्ठा symbol, rb_node);

		अगर (ip < s->start)
			n = n->rb_left;
		अन्यथा अगर (ip > s->end || (ip == s->end && ip != s->start))
			n = n->rb_right;
		अन्यथा
			वापस s;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा symbol *symbols__first(काष्ठा rb_root_cached *symbols)
अणु
	काष्ठा rb_node *n = rb_first_cached(symbols);

	अगर (n)
		वापस rb_entry(n, काष्ठा symbol, rb_node);

	वापस शून्य;
पूर्ण

अटल काष्ठा symbol *symbols__last(काष्ठा rb_root_cached *symbols)
अणु
	काष्ठा rb_node *n = rb_last(&symbols->rb_root);

	अगर (n)
		वापस rb_entry(n, काष्ठा symbol, rb_node);

	वापस शून्य;
पूर्ण

अटल काष्ठा symbol *symbols__next(काष्ठा symbol *sym)
अणु
	काष्ठा rb_node *n = rb_next(&sym->rb_node);

	अगर (n)
		वापस rb_entry(n, काष्ठा symbol, rb_node);

	वापस शून्य;
पूर्ण

अटल व्योम symbols__insert_by_name(काष्ठा rb_root_cached *symbols, काष्ठा symbol *sym)
अणु
	काष्ठा rb_node **p = &symbols->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा symbol_name_rb_node *symn, *s;
	bool lefपंचांगost = true;

	symn = container_of(sym, काष्ठा symbol_name_rb_node, sym);

	जबतक (*p != शून्य) अणु
		parent = *p;
		s = rb_entry(parent, काष्ठा symbol_name_rb_node, rb_node);
		अगर (म_भेद(sym->name, s->sym.name) < 0)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण
	rb_link_node(&symn->rb_node, parent, p);
	rb_insert_color_cached(&symn->rb_node, symbols, lefपंचांगost);
पूर्ण

अटल व्योम symbols__sort_by_name(काष्ठा rb_root_cached *symbols,
				  काष्ठा rb_root_cached *source)
अणु
	काष्ठा rb_node *nd;

	क्रम (nd = rb_first_cached(source); nd; nd = rb_next(nd)) अणु
		काष्ठा symbol *pos = rb_entry(nd, काष्ठा symbol, rb_node);
		symbols__insert_by_name(symbols, pos);
	पूर्ण
पूर्ण

पूर्णांक symbol__match_symbol_name(स्थिर अक्षर *name, स्थिर अक्षर *str,
			      क्रमागत symbol_tag_include includes)
अणु
	स्थिर अक्षर *versioning;

	अगर (includes == SYMBOL_TAG_INCLUDE__DEFAULT_ONLY &&
	    (versioning = म_माला(name, "@@"))) अणु
		पूर्णांक len = म_माप(str);

		अगर (len < versioning - name)
			len = versioning - name;

		वापस arch__compare_symbol_names_n(name, str, len);
	पूर्ण अन्यथा
		वापस arch__compare_symbol_names(name, str);
पूर्ण

अटल काष्ठा symbol *symbols__find_by_name(काष्ठा rb_root_cached *symbols,
					    स्थिर अक्षर *name,
					    क्रमागत symbol_tag_include includes)
अणु
	काष्ठा rb_node *n;
	काष्ठा symbol_name_rb_node *s = शून्य;

	अगर (symbols == शून्य)
		वापस शून्य;

	n = symbols->rb_root.rb_node;

	जबतक (n) अणु
		पूर्णांक cmp;

		s = rb_entry(n, काष्ठा symbol_name_rb_node, rb_node);
		cmp = symbol__match_symbol_name(s->sym.name, name, includes);

		अगर (cmp > 0)
			n = n->rb_left;
		अन्यथा अगर (cmp < 0)
			n = n->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (n == शून्य)
		वापस शून्य;

	अगर (includes != SYMBOL_TAG_INCLUDE__DEFAULT_ONLY)
		/* वापस first symbol that has same name (अगर any) */
		क्रम (n = rb_prev(n); n; n = rb_prev(n)) अणु
			काष्ठा symbol_name_rb_node *पंचांगp;

			पंचांगp = rb_entry(n, काष्ठा symbol_name_rb_node, rb_node);
			अगर (arch__compare_symbol_names(पंचांगp->sym.name, s->sym.name))
				अवरोध;

			s = पंचांगp;
		पूर्ण

	वापस &s->sym;
पूर्ण

व्योम dso__reset_find_symbol_cache(काष्ठा dso *dso)
अणु
	dso->last_find_result.addr   = 0;
	dso->last_find_result.symbol = शून्य;
पूर्ण

व्योम dso__insert_symbol(काष्ठा dso *dso, काष्ठा symbol *sym)
अणु
	__symbols__insert(&dso->symbols, sym, dso->kernel);

	/* update the symbol cache अगर necessary */
	अगर (dso->last_find_result.addr >= sym->start &&
	    (dso->last_find_result.addr < sym->end ||
	    sym->start == sym->end)) अणु
		dso->last_find_result.symbol = sym;
	पूर्ण
पूर्ण

व्योम dso__delete_symbol(काष्ठा dso *dso, काष्ठा symbol *sym)
अणु
	rb_erase_cached(&sym->rb_node, &dso->symbols);
	symbol__delete(sym);
	dso__reset_find_symbol_cache(dso);
पूर्ण

काष्ठा symbol *dso__find_symbol(काष्ठा dso *dso, u64 addr)
अणु
	अगर (dso->last_find_result.addr != addr || dso->last_find_result.symbol == शून्य) अणु
		dso->last_find_result.addr   = addr;
		dso->last_find_result.symbol = symbols__find(&dso->symbols, addr);
	पूर्ण

	वापस dso->last_find_result.symbol;
पूर्ण

काष्ठा symbol *dso__first_symbol(काष्ठा dso *dso)
अणु
	वापस symbols__first(&dso->symbols);
पूर्ण

काष्ठा symbol *dso__last_symbol(काष्ठा dso *dso)
अणु
	वापस symbols__last(&dso->symbols);
पूर्ण

काष्ठा symbol *dso__next_symbol(काष्ठा symbol *sym)
अणु
	वापस symbols__next(sym);
पूर्ण

काष्ठा symbol *symbol__next_by_name(काष्ठा symbol *sym)
अणु
	काष्ठा symbol_name_rb_node *s = container_of(sym, काष्ठा symbol_name_rb_node, sym);
	काष्ठा rb_node *n = rb_next(&s->rb_node);

	वापस n ? &rb_entry(n, काष्ठा symbol_name_rb_node, rb_node)->sym : शून्य;
पूर्ण

 /*
  * Returns first symbol that matched with @name.
  */
काष्ठा symbol *dso__find_symbol_by_name(काष्ठा dso *dso, स्थिर अक्षर *name)
अणु
	काष्ठा symbol *s = symbols__find_by_name(&dso->symbol_names, name,
						 SYMBOL_TAG_INCLUDE__NONE);
	अगर (!s)
		s = symbols__find_by_name(&dso->symbol_names, name,
					  SYMBOL_TAG_INCLUDE__DEFAULT_ONLY);
	वापस s;
पूर्ण

व्योम dso__sort_by_name(काष्ठा dso *dso)
अणु
	dso__set_sorted_by_name(dso);
	वापस symbols__sort_by_name(&dso->symbol_names, &dso->symbols);
पूर्ण

/*
 * While we find nice hex अक्षरs, build a दीर्घ_val.
 * Return number of अक्षरs processed.
 */
अटल पूर्णांक hex2u64(स्थिर अक्षर *ptr, u64 *दीर्घ_val)
अणु
	अक्षर *p;

	*दीर्घ_val = म_से_अदीर्घl(ptr, &p, 16);

	वापस p - ptr;
पूर्ण


पूर्णांक modules__parse(स्थिर अक्षर *filename, व्योम *arg,
		   पूर्णांक (*process_module)(व्योम *arg, स्थिर अक्षर *name,
					 u64 start, u64 size))
अणु
	अक्षर *line = शून्य;
	माप_प्रकार n;
	खाता *file;
	पूर्णांक err = 0;

	file = ख_खोलो(filename, "r");
	अगर (file == शून्य)
		वापस -1;

	जबतक (1) अणु
		अक्षर name[PATH_MAX];
		u64 start, size;
		अक्षर *sep, *endptr;
		sमाप_प्रकार line_len;

		line_len = getline(&line, &n, file);
		अगर (line_len < 0) अणु
			अगर (ख_पूर्ण(file))
				अवरोध;
			err = -1;
			जाओ out;
		पूर्ण

		अगर (!line) अणु
			err = -1;
			जाओ out;
		पूर्ण

		line[--line_len] = '\0'; /* \न */

		sep = म_खोजप(line, 'x');
		अगर (sep == शून्य)
			जारी;

		hex2u64(sep + 1, &start);

		sep = म_अक्षर(line, ' ');
		अगर (sep == शून्य)
			जारी;

		*sep = '\0';

		scnम_लिखो(name, माप(name), "[%s]", line);

		size = म_से_अदीर्घ(sep + 1, &endptr, 0);
		अगर (*endptr != ' ' && *endptr != '\t')
			जारी;

		err = process_module(arg, name, start, size);
		अगर (err)
			अवरोध;
	पूर्ण
out:
	मुक्त(line);
	ख_बंद(file);
	वापस err;
पूर्ण

/*
 * These are symbols in the kernel image, so make sure that
 * sym is from a kernel DSO.
 */
अटल bool symbol__is_idle(स्थिर अक्षर *name)
अणु
	स्थिर अक्षर * स्थिर idle_symbols[] = अणु
		"acpi_idle_do_entry",
		"acpi_processor_ffh_cstate_enter",
		"arch_cpu_idle",
		"cpu_idle",
		"cpu_startup_entry",
		"idle_cpu",
		"intel_idle",
		"default_idle",
		"native_safe_halt",
		"enter_idle",
		"exit_idle",
		"mwait_idle",
		"mwait_idle_with_hints",
		"mwait_idle_with_hints.constprop.0",
		"poll_idle",
		"ppc64_runlatch_off",
		"pseries_dedicated_idle_sleep",
		"psw_idle",
		"psw_idle_exit",
		शून्य
	पूर्ण;
	पूर्णांक i;
	अटल काष्ठा strlist *idle_symbols_list;

	अगर (idle_symbols_list)
		वापस strlist__has_entry(idle_symbols_list, name);

	idle_symbols_list = strlist__new(शून्य, शून्य);

	क्रम (i = 0; idle_symbols[i]; i++)
		strlist__add(idle_symbols_list, idle_symbols[i]);

	वापस strlist__has_entry(idle_symbols_list, name);
पूर्ण

अटल पूर्णांक map__process_kallsym_symbol(व्योम *arg, स्थिर अक्षर *name,
				       अक्षर type, u64 start)
अणु
	काष्ठा symbol *sym;
	काष्ठा dso *dso = arg;
	काष्ठा rb_root_cached *root = &dso->symbols;

	अगर (!symbol_type__filter(type))
		वापस 0;

	/*
	 * module symbols are not sorted so we add all
	 * symbols, setting length to 0, and rely on
	 * symbols__fixup_end() to fix it up.
	 */
	sym = symbol__new(start, 0, kallsyms2elf_binding(type), kallsyms2elf_type(type), name);
	अगर (sym == शून्य)
		वापस -ENOMEM;
	/*
	 * We will pass the symbols to the filter later, in
	 * map__split_kallsyms, when we have split the maps per module
	 */
	__symbols__insert(root, sym, !म_अक्षर(name, '['));

	वापस 0;
पूर्ण

/*
 * Loads the function entries in /proc/kallsyms पूर्णांकo kernel_map->dso,
 * so that we can in the next step set the symbol ->end address and then
 * call kernel_maps__split_kallsyms.
 */
अटल पूर्णांक dso__load_all_kallsyms(काष्ठा dso *dso, स्थिर अक्षर *filename)
अणु
	वापस kallsyms__parse(filename, dso, map__process_kallsym_symbol);
पूर्ण

अटल पूर्णांक maps__split_kallsyms_क्रम_kcore(काष्ठा maps *kmaps, काष्ठा dso *dso)
अणु
	काष्ठा map *curr_map;
	काष्ठा symbol *pos;
	पूर्णांक count = 0;
	काष्ठा rb_root_cached old_root = dso->symbols;
	काष्ठा rb_root_cached *root = &dso->symbols;
	काष्ठा rb_node *next = rb_first_cached(root);

	अगर (!kmaps)
		वापस -1;

	*root = RB_ROOT_CACHED;

	जबतक (next) अणु
		अक्षर *module;

		pos = rb_entry(next, काष्ठा symbol, rb_node);
		next = rb_next(&pos->rb_node);

		rb_erase_cached(&pos->rb_node, &old_root);
		RB_CLEAR_NODE(&pos->rb_node);
		module = म_अक्षर(pos->name, '\t');
		अगर (module)
			*module = '\0';

		curr_map = maps__find(kmaps, pos->start);

		अगर (!curr_map) अणु
			symbol__delete(pos);
			जारी;
		पूर्ण

		pos->start -= curr_map->start - curr_map->pgoff;
		अगर (pos->end > curr_map->end)
			pos->end = curr_map->end;
		अगर (pos->end)
			pos->end -= curr_map->start - curr_map->pgoff;
		symbols__insert(&curr_map->dso->symbols, pos);
		++count;
	पूर्ण

	/* Symbols have been adjusted */
	dso->adjust_symbols = 1;

	वापस count;
पूर्ण

/*
 * Split the symbols पूर्णांकo maps, making sure there are no overlaps, i.e. the
 * kernel range is broken in several maps, named [kernel].N, as we करोn't have
 * the original ELF section names vmlinux have.
 */
अटल पूर्णांक maps__split_kallsyms(काष्ठा maps *kmaps, काष्ठा dso *dso, u64 delta,
				काष्ठा map *initial_map)
अणु
	काष्ठा machine *machine;
	काष्ठा map *curr_map = initial_map;
	काष्ठा symbol *pos;
	पूर्णांक count = 0, moved = 0;
	काष्ठा rb_root_cached *root = &dso->symbols;
	काष्ठा rb_node *next = rb_first_cached(root);
	पूर्णांक kernel_range = 0;
	bool x86_64;

	अगर (!kmaps)
		वापस -1;

	machine = kmaps->machine;

	x86_64 = machine__is(machine, "x86_64");

	जबतक (next) अणु
		अक्षर *module;

		pos = rb_entry(next, काष्ठा symbol, rb_node);
		next = rb_next(&pos->rb_node);

		module = म_अक्षर(pos->name, '\t');
		अगर (module) अणु
			अगर (!symbol_conf.use_modules)
				जाओ discard_symbol;

			*module++ = '\0';

			अगर (म_भेद(curr_map->dso->लघु_name, module)) अणु
				अगर (curr_map != initial_map &&
				    dso->kernel == DSO_SPACE__KERNEL_GUEST &&
				    machine__is_शेष_guest(machine)) अणु
					/*
					 * We assume all symbols of a module are
					 * continuous in * kallsyms, so curr_map
					 * poपूर्णांकs to a module and all its
					 * symbols are in its kmap. Mark it as
					 * loaded.
					 */
					dso__set_loaded(curr_map->dso);
				पूर्ण

				curr_map = maps__find_by_name(kmaps, module);
				अगर (curr_map == शून्य) अणु
					pr_debug("%s/proc/{kallsyms,modules} "
					         "inconsistency while looking "
						 "for \"%s\" module!\n",
						 machine->root_dir, module);
					curr_map = initial_map;
					जाओ discard_symbol;
				पूर्ण

				अगर (curr_map->dso->loaded &&
				    !machine__is_शेष_guest(machine))
					जाओ discard_symbol;
			पूर्ण
			/*
			 * So that we look just like we get from .ko files,
			 * i.e. not prelinked, relative to initial_map->start.
			 */
			pos->start = curr_map->map_ip(curr_map, pos->start);
			pos->end   = curr_map->map_ip(curr_map, pos->end);
		पूर्ण अन्यथा अगर (x86_64 && is_entry_trampoline(pos->name)) अणु
			/*
			 * These symbols are not needed anymore since the
			 * trampoline maps refer to the text section and it's
			 * symbols instead. Aव्योम having to deal with
			 * relocations, and the assumption that the first symbol
			 * is the start of kernel text, by simply removing the
			 * symbols at this poपूर्णांक.
			 */
			जाओ discard_symbol;
		पूर्ण अन्यथा अगर (curr_map != initial_map) अणु
			अक्षर dso_name[PATH_MAX];
			काष्ठा dso *ndso;

			अगर (delta) अणु
				/* Kernel was relocated at boot समय */
				pos->start -= delta;
				pos->end -= delta;
			पूर्ण

			अगर (count == 0) अणु
				curr_map = initial_map;
				जाओ add_symbol;
			पूर्ण

			अगर (dso->kernel == DSO_SPACE__KERNEL_GUEST)
				snम_लिखो(dso_name, माप(dso_name),
					"[guest.kernel].%d",
					kernel_range++);
			अन्यथा
				snम_लिखो(dso_name, माप(dso_name),
					"[kernel].%d",
					kernel_range++);

			ndso = dso__new(dso_name);
			अगर (ndso == शून्य)
				वापस -1;

			ndso->kernel = dso->kernel;

			curr_map = map__new2(pos->start, ndso);
			अगर (curr_map == शून्य) अणु
				dso__put(ndso);
				वापस -1;
			पूर्ण

			curr_map->map_ip = curr_map->unmap_ip = identity__map_ip;
			maps__insert(kmaps, curr_map);
			++kernel_range;
		पूर्ण अन्यथा अगर (delta) अणु
			/* Kernel was relocated at boot समय */
			pos->start -= delta;
			pos->end -= delta;
		पूर्ण
add_symbol:
		अगर (curr_map != initial_map) अणु
			rb_erase_cached(&pos->rb_node, root);
			symbols__insert(&curr_map->dso->symbols, pos);
			++moved;
		पूर्ण अन्यथा
			++count;

		जारी;
discard_symbol:
		rb_erase_cached(&pos->rb_node, root);
		symbol__delete(pos);
	पूर्ण

	अगर (curr_map != initial_map &&
	    dso->kernel == DSO_SPACE__KERNEL_GUEST &&
	    machine__is_शेष_guest(kmaps->machine)) अणु
		dso__set_loaded(curr_map->dso);
	पूर्ण

	वापस count + moved;
पूर्ण

bool symbol__restricted_filename(स्थिर अक्षर *filename,
				 स्थिर अक्षर *restricted_filename)
अणु
	bool restricted = false;

	अगर (symbol_conf.kptr_restrict) अणु
		अक्षर *r = realpath(filename, शून्य);

		अगर (r != शून्य) अणु
			restricted = म_भेद(r, restricted_filename) == 0;
			मुक्त(r);
			वापस restricted;
		पूर्ण
	पूर्ण

	वापस restricted;
पूर्ण

काष्ठा module_info अणु
	काष्ठा rb_node rb_node;
	अक्षर *name;
	u64 start;
पूर्ण;

अटल व्योम add_module(काष्ठा module_info *mi, काष्ठा rb_root *modules)
अणु
	काष्ठा rb_node **p = &modules->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा module_info *m;

	जबतक (*p != शून्य) अणु
		parent = *p;
		m = rb_entry(parent, काष्ठा module_info, rb_node);
		अगर (म_भेद(mi->name, m->name) < 0)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण
	rb_link_node(&mi->rb_node, parent, p);
	rb_insert_color(&mi->rb_node, modules);
पूर्ण

अटल व्योम delete_modules(काष्ठा rb_root *modules)
अणु
	काष्ठा module_info *mi;
	काष्ठा rb_node *next = rb_first(modules);

	जबतक (next) अणु
		mi = rb_entry(next, काष्ठा module_info, rb_node);
		next = rb_next(&mi->rb_node);
		rb_erase(&mi->rb_node, modules);
		zमुक्त(&mi->name);
		मुक्त(mi);
	पूर्ण
पूर्ण

अटल काष्ठा module_info *find_module(स्थिर अक्षर *name,
				       काष्ठा rb_root *modules)
अणु
	काष्ठा rb_node *n = modules->rb_node;

	जबतक (n) अणु
		काष्ठा module_info *m;
		पूर्णांक cmp;

		m = rb_entry(n, काष्ठा module_info, rb_node);
		cmp = म_भेद(name, m->name);
		अगर (cmp < 0)
			n = n->rb_left;
		अन्यथा अगर (cmp > 0)
			n = n->rb_right;
		अन्यथा
			वापस m;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __पढ़ो_proc_modules(व्योम *arg, स्थिर अक्षर *name, u64 start,
			       u64 size __maybe_unused)
अणु
	काष्ठा rb_root *modules = arg;
	काष्ठा module_info *mi;

	mi = zalloc(माप(काष्ठा module_info));
	अगर (!mi)
		वापस -ENOMEM;

	mi->name = strdup(name);
	mi->start = start;

	अगर (!mi->name) अणु
		मुक्त(mi);
		वापस -ENOMEM;
	पूर्ण

	add_module(mi, modules);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_proc_modules(स्थिर अक्षर *filename, काष्ठा rb_root *modules)
अणु
	अगर (symbol__restricted_filename(filename, "/proc/modules"))
		वापस -1;

	अगर (modules__parse(filename, modules, __पढ़ो_proc_modules)) अणु
		delete_modules(modules);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक compare_proc_modules(स्थिर अक्षर *from, स्थिर अक्षर *to)
अणु
	काष्ठा rb_root from_modules = RB_ROOT;
	काष्ठा rb_root to_modules = RB_ROOT;
	काष्ठा rb_node *from_node, *to_node;
	काष्ठा module_info *from_m, *to_m;
	पूर्णांक ret = -1;

	अगर (पढ़ो_proc_modules(from, &from_modules))
		वापस -1;

	अगर (पढ़ो_proc_modules(to, &to_modules))
		जाओ out_delete_from;

	from_node = rb_first(&from_modules);
	to_node = rb_first(&to_modules);
	जबतक (from_node) अणु
		अगर (!to_node)
			अवरोध;

		from_m = rb_entry(from_node, काष्ठा module_info, rb_node);
		to_m = rb_entry(to_node, काष्ठा module_info, rb_node);

		अगर (from_m->start != to_m->start ||
		    म_भेद(from_m->name, to_m->name))
			अवरोध;

		from_node = rb_next(from_node);
		to_node = rb_next(to_node);
	पूर्ण

	अगर (!from_node && !to_node)
		ret = 0;

	delete_modules(&to_modules);
out_delete_from:
	delete_modules(&from_modules);

	वापस ret;
पूर्ण

अटल पूर्णांक करो_validate_kcore_modules(स्थिर अक्षर *filename, काष्ठा maps *kmaps)
अणु
	काष्ठा rb_root modules = RB_ROOT;
	काष्ठा map *old_map;
	पूर्णांक err;

	err = पढ़ो_proc_modules(filename, &modules);
	अगर (err)
		वापस err;

	maps__क्रम_each_entry(kmaps, old_map) अणु
		काष्ठा module_info *mi;

		अगर (!__map__is_kmodule(old_map)) अणु
			जारी;
		पूर्ण

		/* Module must be in memory at the same address */
		mi = find_module(old_map->dso->लघु_name, &modules);
		अगर (!mi || mi->start != old_map->start) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	delete_modules(&modules);
	वापस err;
पूर्ण

/*
 * If kallsyms is referenced by name then we look क्रम filename in the same
 * directory.
 */
अटल bool filename_from_kallsyms_filename(अक्षर *filename,
					    स्थिर अक्षर *base_name,
					    स्थिर अक्षर *kallsyms_filename)
अणु
	अक्षर *name;

	म_नकल(filename, kallsyms_filename);
	name = म_खोजप(filename, '/');
	अगर (!name)
		वापस false;

	name += 1;

	अगर (!म_भेद(name, "kallsyms")) अणु
		म_नकल(name, base_name);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक validate_kcore_modules(स्थिर अक्षर *kallsyms_filename,
				  काष्ठा map *map)
अणु
	काष्ठा maps *kmaps = map__kmaps(map);
	अक्षर modules_filename[PATH_MAX];

	अगर (!kmaps)
		वापस -EINVAL;

	अगर (!filename_from_kallsyms_filename(modules_filename, "modules",
					     kallsyms_filename))
		वापस -EINVAL;

	अगर (करो_validate_kcore_modules(modules_filename, kmaps))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक validate_kcore_addresses(स्थिर अक्षर *kallsyms_filename,
				    काष्ठा map *map)
अणु
	काष्ठा kmap *kmap = map__kmap(map);

	अगर (!kmap)
		वापस -EINVAL;

	अगर (kmap->ref_reloc_sym && kmap->ref_reloc_sym->name) अणु
		u64 start;

		अगर (kallsyms__get_function_start(kallsyms_filename,
						 kmap->ref_reloc_sym->name, &start))
			वापस -ENOENT;
		अगर (start != kmap->ref_reloc_sym->addr)
			वापस -EINVAL;
	पूर्ण

	वापस validate_kcore_modules(kallsyms_filename, map);
पूर्ण

काष्ठा kcore_mapfn_data अणु
	काष्ठा dso *dso;
	काष्ठा list_head maps;
पूर्ण;

अटल पूर्णांक kcore_mapfn(u64 start, u64 len, u64 pgoff, व्योम *data)
अणु
	काष्ठा kcore_mapfn_data *md = data;
	काष्ठा map *map;

	map = map__new2(start, md->dso);
	अगर (map == शून्य)
		वापस -ENOMEM;

	map->end = map->start + len;
	map->pgoff = pgoff;

	list_add(&map->node, &md->maps);

	वापस 0;
पूर्ण

/*
 * Merges map पूर्णांकo maps by splitting the new map within the existing map
 * regions.
 */
पूर्णांक maps__merge_in(काष्ठा maps *kmaps, काष्ठा map *new_map)
अणु
	काष्ठा map *old_map;
	LIST_HEAD(merged);

	maps__क्रम_each_entry(kmaps, old_map) अणु
		/* no overload with this one */
		अगर (new_map->end < old_map->start ||
		    new_map->start >= old_map->end)
			जारी;

		अगर (new_map->start < old_map->start) अणु
			/*
			 * |new......
			 *       |old....
			 */
			अगर (new_map->end < old_map->end) अणु
				/*
				 * |new......|     -> |new..|
				 *       |old....| ->       |old....|
				 */
				new_map->end = old_map->start;
			पूर्ण अन्यथा अणु
				/*
				 * |new.............| -> |new..|       |new..|
				 *       |old....|    ->       |old....|
				 */
				काष्ठा map *m = map__clone(new_map);

				अगर (!m)
					वापस -ENOMEM;

				m->end = old_map->start;
				list_add_tail(&m->node, &merged);
				new_map->pgoff += old_map->end - new_map->start;
				new_map->start = old_map->end;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 *      |new......
			 * |old....
			 */
			अगर (new_map->end < old_map->end) अणु
				/*
				 *      |new..|   -> x
				 * |old.........| -> |old.........|
				 */
				map__put(new_map);
				new_map = शून्य;
				अवरोध;
			पूर्ण अन्यथा अणु
				/*
				 *      |new......| ->         |new...|
				 * |old....|        -> |old....|
				 */
				new_map->pgoff += old_map->end - new_map->start;
				new_map->start = old_map->end;
			पूर्ण
		पूर्ण
	पूर्ण

	जबतक (!list_empty(&merged)) अणु
		old_map = list_entry(merged.next, काष्ठा map, node);
		list_del_init(&old_map->node);
		maps__insert(kmaps, old_map);
		map__put(old_map);
	पूर्ण

	अगर (new_map) अणु
		maps__insert(kmaps, new_map);
		map__put(new_map);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dso__load_kcore(काष्ठा dso *dso, काष्ठा map *map,
			   स्थिर अक्षर *kallsyms_filename)
अणु
	काष्ठा maps *kmaps = map__kmaps(map);
	काष्ठा kcore_mapfn_data md;
	काष्ठा map *old_map, *new_map, *replacement_map = शून्य, *next;
	काष्ठा machine *machine;
	bool is_64_bit;
	पूर्णांक err, fd;
	अक्षर kcore_filename[PATH_MAX];
	u64 stext;

	अगर (!kmaps)
		वापस -EINVAL;

	machine = kmaps->machine;

	/* This function requires that the map is the kernel map */
	अगर (!__map__is_kernel(map))
		वापस -EINVAL;

	अगर (!filename_from_kallsyms_filename(kcore_filename, "kcore",
					     kallsyms_filename))
		वापस -EINVAL;

	/* Modules and kernel must be present at their original addresses */
	अगर (validate_kcore_addresses(kallsyms_filename, map))
		वापस -EINVAL;

	md.dso = dso;
	INIT_LIST_HEAD(&md.maps);

	fd = खोलो(kcore_filename, O_RDONLY);
	अगर (fd < 0) अणु
		pr_debug("Failed to open %s. Note /proc/kcore requires CAP_SYS_RAWIO capability to access.\n",
			 kcore_filename);
		वापस -EINVAL;
	पूर्ण

	/* Read new maps पूर्णांकo temporary lists */
	err = file__पढ़ो_maps(fd, map->prot & PROT_EXEC, kcore_mapfn, &md,
			      &is_64_bit);
	अगर (err)
		जाओ out_err;
	dso->is_64_bit = is_64_bit;

	अगर (list_empty(&md.maps)) अणु
		err = -EINVAL;
		जाओ out_err;
	पूर्ण

	/* Remove old maps */
	maps__क्रम_each_entry_safe(kmaps, old_map, next) अणु
		/*
		 * We need to preserve eBPF maps even अगर they are
		 * covered by kcore, because we need to access
		 * eBPF dso क्रम source data.
		 */
		अगर (old_map != map && !__map__is_bpf_prog(old_map))
			maps__हटाओ(kmaps, old_map);
	पूर्ण
	machine->trampolines_mapped = false;

	/* Find the kernel map using the '_stext' symbol */
	अगर (!kallsyms__get_function_start(kallsyms_filename, "_stext", &stext)) अणु
		list_क्रम_each_entry(new_map, &md.maps, node) अणु
			अगर (stext >= new_map->start && stext < new_map->end) अणु
				replacement_map = new_map;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!replacement_map)
		replacement_map = list_entry(md.maps.next, काष्ठा map, node);

	/* Add new maps */
	जबतक (!list_empty(&md.maps)) अणु
		new_map = list_entry(md.maps.next, काष्ठा map, node);
		list_del_init(&new_map->node);
		अगर (new_map == replacement_map) अणु
			map->start	= new_map->start;
			map->end	= new_map->end;
			map->pgoff	= new_map->pgoff;
			map->map_ip	= new_map->map_ip;
			map->unmap_ip	= new_map->unmap_ip;
			/* Ensure maps are correctly ordered */
			map__get(map);
			maps__हटाओ(kmaps, map);
			maps__insert(kmaps, map);
			map__put(map);
			map__put(new_map);
		पूर्ण अन्यथा अणु
			/*
			 * Merge kcore map पूर्णांकo existing maps,
			 * and ensure that current maps (eBPF)
			 * stay पूर्णांकact.
			 */
			अगर (maps__merge_in(kmaps, new_map))
				जाओ out_err;
		पूर्ण
	पूर्ण

	अगर (machine__is(machine, "x86_64")) अणु
		u64 addr;

		/*
		 * If one of the corresponding symbols is there, assume the
		 * entry trampoline maps are too.
		 */
		अगर (!kallsyms__get_function_start(kallsyms_filename,
						  ENTRY_TRAMPOLINE_NAME,
						  &addr))
			machine->trampolines_mapped = true;
	पूर्ण

	/*
	 * Set the data type and दीर्घ name so that kcore can be पढ़ो via
	 * dso__data_पढ़ो_addr().
	 */
	अगर (dso->kernel == DSO_SPACE__KERNEL_GUEST)
		dso->binary_type = DSO_BINARY_TYPE__GUEST_KCORE;
	अन्यथा
		dso->binary_type = DSO_BINARY_TYPE__KCORE;
	dso__set_दीर्घ_name(dso, strdup(kcore_filename), true);

	बंद(fd);

	अगर (map->prot & PROT_EXEC)
		pr_debug("Using %s for kernel object code\n", kcore_filename);
	अन्यथा
		pr_debug("Using %s for kernel data\n", kcore_filename);

	वापस 0;

out_err:
	जबतक (!list_empty(&md.maps)) अणु
		map = list_entry(md.maps.next, काष्ठा map, node);
		list_del_init(&map->node);
		map__put(map);
	पूर्ण
	बंद(fd);
	वापस -EINVAL;
पूर्ण

/*
 * If the kernel is relocated at boot समय, kallsyms won't match.  Compute the
 * delta based on the relocation reference symbol.
 */
अटल पूर्णांक kallsyms__delta(काष्ठा kmap *kmap, स्थिर अक्षर *filename, u64 *delta)
अणु
	u64 addr;

	अगर (!kmap->ref_reloc_sym || !kmap->ref_reloc_sym->name)
		वापस 0;

	अगर (kallsyms__get_function_start(filename, kmap->ref_reloc_sym->name, &addr))
		वापस -1;

	*delta = addr - kmap->ref_reloc_sym->addr;
	वापस 0;
पूर्ण

पूर्णांक __dso__load_kallsyms(काष्ठा dso *dso, स्थिर अक्षर *filename,
			 काष्ठा map *map, bool no_kcore)
अणु
	काष्ठा kmap *kmap = map__kmap(map);
	u64 delta = 0;

	अगर (symbol__restricted_filename(filename, "/proc/kallsyms"))
		वापस -1;

	अगर (!kmap || !kmap->kmaps)
		वापस -1;

	अगर (dso__load_all_kallsyms(dso, filename) < 0)
		वापस -1;

	अगर (kallsyms__delta(kmap, filename, &delta))
		वापस -1;

	symbols__fixup_end(&dso->symbols);
	symbols__fixup_duplicate(&dso->symbols);

	अगर (dso->kernel == DSO_SPACE__KERNEL_GUEST)
		dso->symtab_type = DSO_BINARY_TYPE__GUEST_KALLSYMS;
	अन्यथा
		dso->symtab_type = DSO_BINARY_TYPE__KALLSYMS;

	अगर (!no_kcore && !dso__load_kcore(dso, map, filename))
		वापस maps__split_kallsyms_क्रम_kcore(kmap->kmaps, dso);
	अन्यथा
		वापस maps__split_kallsyms(kmap->kmaps, dso, delta, map);
पूर्ण

पूर्णांक dso__load_kallsyms(काष्ठा dso *dso, स्थिर अक्षर *filename,
		       काष्ठा map *map)
अणु
	वापस __dso__load_kallsyms(dso, filename, map, false);
पूर्ण

अटल पूर्णांक dso__load_perf_map(स्थिर अक्षर *map_path, काष्ठा dso *dso)
अणु
	अक्षर *line = शून्य;
	माप_प्रकार n;
	खाता *file;
	पूर्णांक nr_syms = 0;

	file = ख_खोलो(map_path, "r");
	अगर (file == शून्य)
		जाओ out_failure;

	जबतक (!ख_पूर्ण(file)) अणु
		u64 start, size;
		काष्ठा symbol *sym;
		पूर्णांक line_len, len;

		line_len = getline(&line, &n, file);
		अगर (line_len < 0)
			अवरोध;

		अगर (!line)
			जाओ out_failure;

		line[--line_len] = '\0'; /* \न */

		len = hex2u64(line, &start);

		len++;
		अगर (len + 2 >= line_len)
			जारी;

		len += hex2u64(line + len, &size);

		len++;
		अगर (len + 2 >= line_len)
			जारी;

		sym = symbol__new(start, size, STB_GLOBAL, STT_FUNC, line + len);

		अगर (sym == शून्य)
			जाओ out_delete_line;

		symbols__insert(&dso->symbols, sym);
		nr_syms++;
	पूर्ण

	मुक्त(line);
	ख_बंद(file);

	वापस nr_syms;

out_delete_line:
	मुक्त(line);
out_failure:
	वापस -1;
पूर्ण

#अगर_घोषित HAVE_LIBBFD_SUPPORT
#घोषणा PACKAGE 'perf'
#समावेश <bfd.h>

अटल पूर्णांक bfd_symbols__cmpvalue(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर asymbol *as = *(स्थिर asymbol **)a, *bs = *(स्थिर asymbol **)b;

	अगर (bfd_asymbol_value(as) != bfd_asymbol_value(bs))
		वापस bfd_asymbol_value(as) - bfd_asymbol_value(bs);

	वापस bfd_asymbol_name(as)[0] - bfd_asymbol_name(bs)[0];
पूर्ण

अटल पूर्णांक bfd2elf_binding(asymbol *symbol)
अणु
	अगर (symbol->flags & BSF_WEAK)
		वापस STB_WEAK;
	अगर (symbol->flags & BSF_GLOBAL)
		वापस STB_GLOBAL;
	अगर (symbol->flags & BSF_LOCAL)
		वापस STB_LOCAL;
	वापस -1;
पूर्ण

पूर्णांक dso__load_bfd_symbols(काष्ठा dso *dso, स्थिर अक्षर *debugfile)
अणु
	पूर्णांक err = -1;
	दीर्घ symbols_size, symbols_count, i;
	asection *section;
	asymbol **symbols, *sym;
	काष्ठा symbol *symbol;
	bfd *abfd;
	u64 start, len;

	abfd = bfd_खोलोr(debugfile, शून्य);
	अगर (!abfd)
		वापस -1;

	अगर (!bfd_check_क्रमmat(abfd, bfd_object)) अणु
		pr_debug2("%s: cannot read %s bfd file.\n", __func__,
			  dso->दीर्घ_name);
		जाओ out_बंद;
	पूर्ण

	अगर (bfd_get_flavour(abfd) == bfd_target_elf_flavour)
		जाओ out_बंद;

	section = bfd_get_section_by_name(abfd, ".text");
	अगर (section)
		dso->text_offset = section->vma - section->filepos;

	symbols_size = bfd_get_symtab_upper_bound(abfd);
	अगर (symbols_size == 0) अणु
		bfd_बंद(abfd);
		वापस 0;
	पूर्ण

	अगर (symbols_size < 0)
		जाओ out_बंद;

	symbols = दो_स्मृति(symbols_size);
	अगर (!symbols)
		जाओ out_बंद;

	symbols_count = bfd_canonicalize_symtab(abfd, symbols);
	अगर (symbols_count < 0)
		जाओ out_मुक्त;

	क्विक(symbols, symbols_count, माप(asymbol *), bfd_symbols__cmpvalue);

#अगर_घोषित bfd_get_section
#घोषणा bfd_asymbol_section bfd_get_section
#पूर्ण_अगर
	क्रम (i = 0; i < symbols_count; ++i) अणु
		sym = symbols[i];
		section = bfd_asymbol_section(sym);
		अगर (bfd2elf_binding(sym) < 0)
			जारी;

		जबतक (i + 1 < symbols_count &&
		       bfd_asymbol_section(symbols[i + 1]) == section &&
		       bfd2elf_binding(symbols[i + 1]) < 0)
			i++;

		अगर (i + 1 < symbols_count &&
		    bfd_asymbol_section(symbols[i + 1]) == section)
			len = symbols[i + 1]->value - sym->value;
		अन्यथा
			len = section->size - sym->value;

		start = bfd_asymbol_value(sym) - dso->text_offset;
		symbol = symbol__new(start, len, bfd2elf_binding(sym), STT_FUNC,
				     bfd_asymbol_name(sym));
		अगर (!symbol)
			जाओ out_मुक्त;

		symbols__insert(&dso->symbols, symbol);
	पूर्ण
#अगर_घोषित bfd_get_section
#अघोषित bfd_asymbol_section
#पूर्ण_अगर

	symbols__fixup_end(&dso->symbols);
	symbols__fixup_duplicate(&dso->symbols);
	dso->adjust_symbols = 1;

	err = 0;
out_मुक्त:
	मुक्त(symbols);
out_बंद:
	bfd_बंद(abfd);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल bool dso__is_compatible_symtab_type(काष्ठा dso *dso, bool kmod,
					   क्रमागत dso_binary_type type)
अणु
	चयन (type) अणु
	हाल DSO_BINARY_TYPE__JAVA_JIT:
	हाल DSO_BINARY_TYPE__DEBUGLINK:
	हाल DSO_BINARY_TYPE__SYSTEM_PATH_DSO:
	हाल DSO_BINARY_TYPE__FEDORA_DEBUGINFO:
	हाल DSO_BINARY_TYPE__UBUNTU_DEBUGINFO:
	हाल DSO_BINARY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO:
	हाल DSO_BINARY_TYPE__BUILDID_DEBUGINFO:
	हाल DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO:
		वापस !kmod && dso->kernel == DSO_SPACE__USER;

	हाल DSO_BINARY_TYPE__KALLSYMS:
	हाल DSO_BINARY_TYPE__VMLINUX:
	हाल DSO_BINARY_TYPE__KCORE:
		वापस dso->kernel == DSO_SPACE__KERNEL;

	हाल DSO_BINARY_TYPE__GUEST_KALLSYMS:
	हाल DSO_BINARY_TYPE__GUEST_VMLINUX:
	हाल DSO_BINARY_TYPE__GUEST_KCORE:
		वापस dso->kernel == DSO_SPACE__KERNEL_GUEST;

	हाल DSO_BINARY_TYPE__GUEST_KMODULE:
	हाल DSO_BINARY_TYPE__GUEST_KMODULE_COMP:
	हाल DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE:
	हाल DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP:
		/*
		 * kernel modules know their symtab type - it's set when
		 * creating a module dso in machine__addnew_module_map().
		 */
		वापस kmod && dso->symtab_type == type;

	हाल DSO_BINARY_TYPE__BUILD_ID_CACHE:
	हाल DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO:
		वापस true;

	हाल DSO_BINARY_TYPE__BPF_PROG_INFO:
	हाल DSO_BINARY_TYPE__BPF_IMAGE:
	हाल DSO_BINARY_TYPE__OOL:
	हाल DSO_BINARY_TYPE__NOT_FOUND:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* Checks क्रम the existence of the perf-<pid>.map file in two dअगरferent
 * locations.  First, अगर the process is a separate mount namespace, check in
 * that namespace using the pid of the innermost pid namespace.  If's not in a
 * namespace, or the file can't be found there, try in the mount namespace of
 * the tracing process using our view of its pid.
 */
अटल पूर्णांक dso__find_perf_map(अक्षर *filebuf, माप_प्रकार bufsz,
			      काष्ठा nsinfo **nsip)
अणु
	काष्ठा nscookie nsc;
	काष्ठा nsinfo *nsi;
	काष्ठा nsinfo *nnsi;
	पूर्णांक rc = -1;

	nsi = *nsip;

	अगर (nsi->need_setns) अणु
		snम_लिखो(filebuf, bufsz, "/tmp/perf-%d.map", nsi->nstgid);
		nsinfo__mountns_enter(nsi, &nsc);
		rc = access(filebuf, R_OK);
		nsinfo__mountns_निकास(&nsc);
		अगर (rc == 0)
			वापस rc;
	पूर्ण

	nnsi = nsinfo__copy(nsi);
	अगर (nnsi) अणु
		nsinfo__put(nsi);

		nnsi->need_setns = false;
		snम_लिखो(filebuf, bufsz, "/tmp/perf-%d.map", nnsi->tgid);
		*nsip = nnsi;
		rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक dso__load(काष्ठा dso *dso, काष्ठा map *map)
अणु
	अक्षर *name;
	पूर्णांक ret = -1;
	u_पूर्णांक i;
	काष्ठा machine *machine = शून्य;
	अक्षर *root_dir = (अक्षर *) "";
	पूर्णांक ss_pos = 0;
	काष्ठा symsrc ss_[2];
	काष्ठा symsrc *syms_ss = शून्य, *runसमय_ss = शून्य;
	bool kmod;
	bool perfmap;
	काष्ठा build_id bid;
	काष्ठा nscookie nsc;
	अक्षर newmapname[PATH_MAX];
	स्थिर अक्षर *map_path = dso->दीर्घ_name;

	perfmap = म_भेदन(dso->name, "/tmp/perf-", 10) == 0;
	अगर (perfmap) अणु
		अगर (dso->nsinfo && (dso__find_perf_map(newmapname,
		    माप(newmapname), &dso->nsinfo) == 0)) अणु
			map_path = newmapname;
		पूर्ण
	पूर्ण

	nsinfo__mountns_enter(dso->nsinfo, &nsc);
	pthपढ़ो_mutex_lock(&dso->lock);

	/* check again under the dso->lock */
	अगर (dso__loaded(dso)) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	kmod = dso->symtab_type == DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE ||
		dso->symtab_type == DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP ||
		dso->symtab_type == DSO_BINARY_TYPE__GUEST_KMODULE ||
		dso->symtab_type == DSO_BINARY_TYPE__GUEST_KMODULE_COMP;

	अगर (dso->kernel && !kmod) अणु
		अगर (dso->kernel == DSO_SPACE__KERNEL)
			ret = dso__load_kernel_sym(dso, map);
		अन्यथा अगर (dso->kernel == DSO_SPACE__KERNEL_GUEST)
			ret = dso__load_guest_kernel_sym(dso, map);

		machine = map__kmaps(map)->machine;
		अगर (machine__is(machine, "x86_64"))
			machine__map_x86_64_entry_trampolines(machine, dso);
		जाओ out;
	पूर्ण

	dso->adjust_symbols = 0;

	अगर (perfmap) अणु
		ret = dso__load_perf_map(map_path, dso);
		dso->symtab_type = ret > 0 ? DSO_BINARY_TYPE__JAVA_JIT :
					     DSO_BINARY_TYPE__NOT_FOUND;
		जाओ out;
	पूर्ण

	अगर (machine)
		root_dir = machine->root_dir;

	name = दो_स्मृति(PATH_MAX);
	अगर (!name)
		जाओ out;

	/*
	 * Read the build id अगर possible. This is required क्रम
	 * DSO_BINARY_TYPE__BUILDID_DEBUGINFO to work
	 */
	अगर (!dso->has_build_id &&
	    is_regular_file(dso->दीर्घ_name)) अणु
	    __symbol__join_symfs(name, PATH_MAX, dso->दीर्घ_name);
		अगर (filename__पढ़ो_build_id(name, &bid) > 0)
			dso__set_build_id(dso, &bid);
	पूर्ण

	/*
	 * Iterate over candidate debug images.
	 * Keep track of "interesting" ones (those which have a symtab, dynsym,
	 * and/or opd section) क्रम processing.
	 */
	क्रम (i = 0; i < DSO_BINARY_TYPE__SYMTAB_CNT; i++) अणु
		काष्ठा symsrc *ss = &ss_[ss_pos];
		bool next_slot = false;
		bool is_reg;
		bool nsनिकास;
		पूर्णांक bfdrc = -1;
		पूर्णांक sirc = -1;

		क्रमागत dso_binary_type symtab_type = binary_type_symtab[i];

		nsनिकास = (symtab_type == DSO_BINARY_TYPE__BUILD_ID_CACHE ||
		    symtab_type == DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO);

		अगर (!dso__is_compatible_symtab_type(dso, kmod, symtab_type))
			जारी;

		अगर (dso__पढ़ो_binary_type_filename(dso, symtab_type,
						   root_dir, name, PATH_MAX))
			जारी;

		अगर (nsनिकास)
			nsinfo__mountns_निकास(&nsc);

		is_reg = is_regular_file(name);
#अगर_घोषित HAVE_LIBBFD_SUPPORT
		अगर (is_reg)
			bfdrc = dso__load_bfd_symbols(dso, name);
#पूर्ण_अगर
		अगर (is_reg && bfdrc < 0)
			sirc = symsrc__init(ss, dso, name, symtab_type);

		अगर (nsनिकास)
			nsinfo__mountns_enter(dso->nsinfo, &nsc);

		अगर (bfdrc == 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (!is_reg || sirc < 0)
			जारी;

		अगर (!syms_ss && symsrc__has_symtab(ss)) अणु
			syms_ss = ss;
			next_slot = true;
			अगर (!dso->symsrc_filename)
				dso->symsrc_filename = strdup(name);
		पूर्ण

		अगर (!runसमय_ss && symsrc__possibly_runसमय(ss)) अणु
			runसमय_ss = ss;
			next_slot = true;
		पूर्ण

		अगर (next_slot) अणु
			ss_pos++;

			अगर (syms_ss && runसमय_ss)
				अवरोध;
		पूर्ण अन्यथा अणु
			symsrc__destroy(ss);
		पूर्ण

	पूर्ण

	अगर (!runसमय_ss && !syms_ss)
		जाओ out_मुक्त;

	अगर (runसमय_ss && !syms_ss) अणु
		syms_ss = runसमय_ss;
	पूर्ण

	/* We'll have to hope क्रम the best */
	अगर (!runसमय_ss && syms_ss)
		runसमय_ss = syms_ss;

	अगर (syms_ss)
		ret = dso__load_sym(dso, map, syms_ss, runसमय_ss, kmod);
	अन्यथा
		ret = -1;

	अगर (ret > 0) अणु
		पूर्णांक nr_plt;

		nr_plt = dso__synthesize_plt_symbols(dso, runसमय_ss);
		अगर (nr_plt > 0)
			ret += nr_plt;
	पूर्ण

	क्रम (; ss_pos > 0; ss_pos--)
		symsrc__destroy(&ss_[ss_pos - 1]);
out_मुक्त:
	मुक्त(name);
	अगर (ret < 0 && म_माला(dso->name, " (deleted)") != शून्य)
		ret = 0;
out:
	dso__set_loaded(dso);
	pthपढ़ो_mutex_unlock(&dso->lock);
	nsinfo__mountns_निकास(&nsc);

	वापस ret;
पूर्ण

अटल पूर्णांक map__म_भेद(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा map *ma = *(स्थिर काष्ठा map **)a, *mb = *(स्थिर काष्ठा map **)b;
	वापस म_भेद(ma->dso->लघु_name, mb->dso->लघु_name);
पूर्ण

अटल पूर्णांक map__म_भेद_name(स्थिर व्योम *name, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा map *map = *(स्थिर काष्ठा map **)b;
	वापस म_भेद(name, map->dso->लघु_name);
पूर्ण

व्योम __maps__sort_by_name(काष्ठा maps *maps)
अणु
	क्विक(maps->maps_by_name, maps->nr_maps, माप(काष्ठा map *), map__म_भेद);
पूर्ण

अटल पूर्णांक map__groups__sort_by_name_from_rbtree(काष्ठा maps *maps)
अणु
	काष्ठा map *map;
	काष्ठा map **maps_by_name = पुनः_स्मृति(maps->maps_by_name, maps->nr_maps * माप(map));
	पूर्णांक i = 0;

	अगर (maps_by_name == शून्य)
		वापस -1;

	maps->maps_by_name = maps_by_name;
	maps->nr_maps_allocated = maps->nr_maps;

	maps__क्रम_each_entry(maps, map)
		maps_by_name[i++] = map;

	__maps__sort_by_name(maps);
	वापस 0;
पूर्ण

अटल काष्ठा map *__maps__find_by_name(काष्ठा maps *maps, स्थिर अक्षर *name)
अणु
	काष्ठा map **mapp;

	अगर (maps->maps_by_name == शून्य &&
	    map__groups__sort_by_name_from_rbtree(maps))
		वापस शून्य;

	mapp = द्वा_खोज(name, maps->maps_by_name, maps->nr_maps, माप(*mapp), map__म_भेद_name);
	अगर (mapp)
		वापस *mapp;
	वापस शून्य;
पूर्ण

काष्ठा map *maps__find_by_name(काष्ठा maps *maps, स्थिर अक्षर *name)
अणु
	काष्ठा map *map;

	करोwn_पढ़ो(&maps->lock);

	अगर (maps->last_search_by_name && म_भेद(maps->last_search_by_name->dso->लघु_name, name) == 0) अणु
		map = maps->last_search_by_name;
		जाओ out_unlock;
	पूर्ण
	/*
	 * If we have maps->maps_by_name, then the name isn't in the rbtree,
	 * as maps->maps_by_name mirrors the rbtree when lookups by name are
	 * made.
	 */
	map = __maps__find_by_name(maps, name);
	अगर (map || maps->maps_by_name != शून्य)
		जाओ out_unlock;

	/* Fallback to traversing the rbtree... */
	maps__क्रम_each_entry(maps, map)
		अगर (म_भेद(map->dso->लघु_name, name) == 0) अणु
			maps->last_search_by_name = map;
			जाओ out_unlock;
		पूर्ण

	map = शून्य;

out_unlock:
	up_पढ़ो(&maps->lock);
	वापस map;
पूर्ण

पूर्णांक dso__load_vmlinux(काष्ठा dso *dso, काष्ठा map *map,
		      स्थिर अक्षर *vmlinux, bool vmlinux_allocated)
अणु
	पूर्णांक err = -1;
	काष्ठा symsrc ss;
	अक्षर symfs_vmlinux[PATH_MAX];
	क्रमागत dso_binary_type symtab_type;

	अगर (vmlinux[0] == '/')
		snम_लिखो(symfs_vmlinux, माप(symfs_vmlinux), "%s", vmlinux);
	अन्यथा
		symbol__join_symfs(symfs_vmlinux, vmlinux);

	अगर (dso->kernel == DSO_SPACE__KERNEL_GUEST)
		symtab_type = DSO_BINARY_TYPE__GUEST_VMLINUX;
	अन्यथा
		symtab_type = DSO_BINARY_TYPE__VMLINUX;

	अगर (symsrc__init(&ss, dso, symfs_vmlinux, symtab_type))
		वापस -1;

	err = dso__load_sym(dso, map, &ss, &ss, 0);
	symsrc__destroy(&ss);

	अगर (err > 0) अणु
		अगर (dso->kernel == DSO_SPACE__KERNEL_GUEST)
			dso->binary_type = DSO_BINARY_TYPE__GUEST_VMLINUX;
		अन्यथा
			dso->binary_type = DSO_BINARY_TYPE__VMLINUX;
		dso__set_दीर्घ_name(dso, vmlinux, vmlinux_allocated);
		dso__set_loaded(dso);
		pr_debug("Using %s for symbols\n", symfs_vmlinux);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक dso__load_vmlinux_path(काष्ठा dso *dso, काष्ठा map *map)
अणु
	पूर्णांक i, err = 0;
	अक्षर *filename = शून्य;

	pr_debug("Looking at the vmlinux_path (%d entries long)\n",
		 vmlinux_path__nr_entries + 1);

	क्रम (i = 0; i < vmlinux_path__nr_entries; ++i) अणु
		err = dso__load_vmlinux(dso, map, vmlinux_path[i], false);
		अगर (err > 0)
			जाओ out;
	पूर्ण

	अगर (!symbol_conf.ignore_vmlinux_buildid)
		filename = dso__build_id_filename(dso, शून्य, 0, false);
	अगर (filename != शून्य) अणु
		err = dso__load_vmlinux(dso, map, filename, true);
		अगर (err > 0)
			जाओ out;
		मुक्त(filename);
	पूर्ण
out:
	वापस err;
पूर्ण

अटल bool visible_dir_filter(स्थिर अक्षर *name, काष्ठा dirent *d)
अणु
	अगर (d->d_type != DT_सूची)
		वापस false;
	वापस lsdir_no_करोt_filter(name, d);
पूर्ण

अटल पूर्णांक find_matching_kcore(काष्ठा map *map, अक्षर *dir, माप_प्रकार dir_sz)
अणु
	अक्षर kallsyms_filename[PATH_MAX];
	पूर्णांक ret = -1;
	काष्ठा strlist *dirs;
	काष्ठा str_node *nd;

	dirs = lsdir(dir, visible_dir_filter);
	अगर (!dirs)
		वापस -1;

	strlist__क्रम_each_entry(nd, dirs) अणु
		scnम_लिखो(kallsyms_filename, माप(kallsyms_filename),
			  "%s/%s/kallsyms", dir, nd->s);
		अगर (!validate_kcore_addresses(kallsyms_filename, map)) अणु
			strlcpy(dir, kallsyms_filename, dir_sz);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	strlist__delete(dirs);

	वापस ret;
पूर्ण

/*
 * Use खोलो(O_RDONLY) to check पढ़ोability directly instead of access(R_OK)
 * since access(R_OK) only checks with real UID/GID but खोलो() use effective
 * UID/GID and actual capabilities (e.g. /proc/kcore requires CAP_SYS_RAWIO).
 */
अटल bool filename__पढ़ोable(स्थिर अक्षर *file)
अणु
	पूर्णांक fd = खोलो(file, O_RDONLY);
	अगर (fd < 0)
		वापस false;
	बंद(fd);
	वापस true;
पूर्ण

अटल अक्षर *dso__find_kallsyms(काष्ठा dso *dso, काष्ठा map *map)
अणु
	काष्ठा build_id bid;
	अक्षर sbuild_id[SBUILD_ID_SIZE];
	bool is_host = false;
	अक्षर path[PATH_MAX];

	अगर (!dso->has_build_id) अणु
		/*
		 * Last resort, अगर we करोn't have a build-id and couldn't find
		 * any vmlinux file, try the running kernel kallsyms table.
		 */
		जाओ proc_kallsyms;
	पूर्ण

	अगर (sysfs__पढ़ो_build_id("/sys/kernel/notes", &bid) == 0)
		is_host = dso__build_id_equal(dso, &bid);

	/* Try a fast path क्रम /proc/kallsyms अगर possible */
	अगर (is_host) अणु
		/*
		 * Do not check the build-id cache, unless we know we cannot use
		 * /proc/kcore or module maps करोn't match to /proc/kallsyms.
		 * To check पढ़ोability of /proc/kcore, करो not use access(R_OK)
		 * since /proc/kcore requires CAP_SYS_RAWIO to पढ़ो and access
		 * can't check it.
		 */
		अगर (filename__पढ़ोable("/proc/kcore") &&
		    !validate_kcore_addresses("/proc/kallsyms", map))
			जाओ proc_kallsyms;
	पूर्ण

	build_id__प्र_लिखो(&dso->bid, sbuild_id);

	/* Find kallsyms in build-id cache with kcore */
	scnम_लिखो(path, माप(path), "%s/%s/%s",
		  buildid_dir, DSO__NAME_KCORE, sbuild_id);

	अगर (!find_matching_kcore(map, path, माप(path)))
		वापस strdup(path);

	/* Use current /proc/kallsyms अगर possible */
	अगर (is_host) अणु
proc_kallsyms:
		वापस strdup("/proc/kallsyms");
	पूर्ण

	/* Finally, find a cache of kallsyms */
	अगर (!build_id_cache__kallsyms_path(sbuild_id, path, माप(path))) अणु
		pr_err("No kallsyms or vmlinux with build-id %s was found\n",
		       sbuild_id);
		वापस शून्य;
	पूर्ण

	वापस strdup(path);
पूर्ण

अटल पूर्णांक dso__load_kernel_sym(काष्ठा dso *dso, काष्ठा map *map)
अणु
	पूर्णांक err;
	स्थिर अक्षर *kallsyms_filename = शून्य;
	अक्षर *kallsyms_allocated_filename = शून्य;
	अक्षर *filename = शून्य;

	/*
	 * Step 1: अगर the user specअगरied a kallsyms or vmlinux filename, use
	 * it and only it, reporting errors to the user अगर it cannot be used.
	 *
	 * For instance, try to analyse an ARM perf.data file _without_ a
	 * build-id, or अगर the user specअगरies the wrong path to the right
	 * vmlinux file, obviously we can't fallback to another vmlinux (a
	 * x86_86 one, on the machine where analysis is being perक्रमmed, say),
	 * or worse, /proc/kallsyms.
	 *
	 * If the specअगरied file _has_ a build-id and there is a build-id
	 * section in the perf.data file, we will still करो the expected
	 * validation in dso__load_vmlinux and will bail out अगर they करोn't
	 * match.
	 */
	अगर (symbol_conf.kallsyms_name != शून्य) अणु
		kallsyms_filename = symbol_conf.kallsyms_name;
		जाओ करो_kallsyms;
	पूर्ण

	अगर (!symbol_conf.ignore_vmlinux && symbol_conf.vmlinux_name != शून्य) अणु
		वापस dso__load_vmlinux(dso, map, symbol_conf.vmlinux_name, false);
	पूर्ण

	/*
	 * Beक्रमe checking on common vmlinux locations, check अगर it's
	 * stored as standard build id binary (not kallsyms) under
	 * .debug cache.
	 */
	अगर (!symbol_conf.ignore_vmlinux_buildid)
		filename = __dso__build_id_filename(dso, शून्य, 0, false, false);
	अगर (filename != शून्य) अणु
		err = dso__load_vmlinux(dso, map, filename, true);
		अगर (err > 0)
			वापस err;
		मुक्त(filename);
	पूर्ण

	अगर (!symbol_conf.ignore_vmlinux && vmlinux_path != शून्य) अणु
		err = dso__load_vmlinux_path(dso, map);
		अगर (err > 0)
			वापस err;
	पूर्ण

	/* करो not try local files अगर a symfs was given */
	अगर (symbol_conf.symfs[0] != 0)
		वापस -1;

	kallsyms_allocated_filename = dso__find_kallsyms(dso, map);
	अगर (!kallsyms_allocated_filename)
		वापस -1;

	kallsyms_filename = kallsyms_allocated_filename;

करो_kallsyms:
	err = dso__load_kallsyms(dso, kallsyms_filename, map);
	अगर (err > 0)
		pr_debug("Using %s for symbols\n", kallsyms_filename);
	मुक्त(kallsyms_allocated_filename);

	अगर (err > 0 && !dso__is_kcore(dso)) अणु
		dso->binary_type = DSO_BINARY_TYPE__KALLSYMS;
		dso__set_दीर्घ_name(dso, DSO__NAME_KALLSYMS, false);
		map__fixup_start(map);
		map__fixup_end(map);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dso__load_guest_kernel_sym(काष्ठा dso *dso, काष्ठा map *map)
अणु
	पूर्णांक err;
	स्थिर अक्षर *kallsyms_filename = शून्य;
	काष्ठा machine *machine = map__kmaps(map)->machine;
	अक्षर path[PATH_MAX];

	अगर (machine__is_शेष_guest(machine)) अणु
		/*
		 * अगर the user specअगरied a vmlinux filename, use it and only
		 * it, reporting errors to the user अगर it cannot be used.
		 * Or use file guest_kallsyms inputted by user on commandline
		 */
		अगर (symbol_conf.शेष_guest_vmlinux_name != शून्य) अणु
			err = dso__load_vmlinux(dso, map,
						symbol_conf.शेष_guest_vmlinux_name,
						false);
			वापस err;
		पूर्ण

		kallsyms_filename = symbol_conf.शेष_guest_kallsyms;
		अगर (!kallsyms_filename)
			वापस -1;
	पूर्ण अन्यथा अणु
		प्र_लिखो(path, "%s/proc/kallsyms", machine->root_dir);
		kallsyms_filename = path;
	पूर्ण

	err = dso__load_kallsyms(dso, kallsyms_filename, map);
	अगर (err > 0)
		pr_debug("Using %s for symbols\n", kallsyms_filename);
	अगर (err > 0 && !dso__is_kcore(dso)) अणु
		dso->binary_type = DSO_BINARY_TYPE__GUEST_KALLSYMS;
		dso__set_दीर्घ_name(dso, machine->mmap_name, false);
		map__fixup_start(map);
		map__fixup_end(map);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम vmlinux_path__निकास(व्योम)
अणु
	जबतक (--vmlinux_path__nr_entries >= 0)
		zमुक्त(&vmlinux_path[vmlinux_path__nr_entries]);
	vmlinux_path__nr_entries = 0;

	zमुक्त(&vmlinux_path);
पूर्ण

अटल स्थिर अक्षर * स्थिर vmlinux_paths[] = अणु
	"vmlinux",
	"/boot/vmlinux"
पूर्ण;

अटल स्थिर अक्षर * स्थिर vmlinux_paths_upd[] = अणु
	"/boot/vmlinux-%s",
	"/usr/lib/debug/boot/vmlinux-%s",
	"/lib/modules/%s/build/vmlinux",
	"/usr/lib/debug/lib/modules/%s/vmlinux",
	"/usr/lib/debug/boot/vmlinux-%s.debug"
पूर्ण;

अटल पूर्णांक vmlinux_path__add(स्थिर अक्षर *new_entry)
अणु
	vmlinux_path[vmlinux_path__nr_entries] = strdup(new_entry);
	अगर (vmlinux_path[vmlinux_path__nr_entries] == शून्य)
		वापस -1;
	++vmlinux_path__nr_entries;

	वापस 0;
पूर्ण

अटल पूर्णांक vmlinux_path__init(काष्ठा perf_env *env)
अणु
	काष्ठा utsname uts;
	अक्षर bf[PATH_MAX];
	अक्षर *kernel_version;
	अचिन्हित पूर्णांक i;

	vmlinux_path = दो_स्मृति(माप(अक्षर *) * (ARRAY_SIZE(vmlinux_paths) +
			      ARRAY_SIZE(vmlinux_paths_upd)));
	अगर (vmlinux_path == शून्य)
		वापस -1;

	क्रम (i = 0; i < ARRAY_SIZE(vmlinux_paths); i++)
		अगर (vmlinux_path__add(vmlinux_paths[i]) < 0)
			जाओ out_fail;

	/* only try kernel version अगर no symfs was given */
	अगर (symbol_conf.symfs[0] != 0)
		वापस 0;

	अगर (env) अणु
		kernel_version = env->os_release;
	पूर्ण अन्यथा अणु
		अगर (uname(&uts) < 0)
			जाओ out_fail;

		kernel_version = uts.release;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vmlinux_paths_upd); i++) अणु
		snम_लिखो(bf, माप(bf), vmlinux_paths_upd[i], kernel_version);
		अगर (vmlinux_path__add(bf) < 0)
			जाओ out_fail;
	पूर्ण

	वापस 0;

out_fail:
	vmlinux_path__निकास();
	वापस -1;
पूर्ण

पूर्णांक setup_list(काष्ठा strlist **list, स्थिर अक्षर *list_str,
		      स्थिर अक्षर *list_name)
अणु
	अगर (list_str == शून्य)
		वापस 0;

	*list = strlist__new(list_str, शून्य);
	अगर (!*list) अणु
		pr_err("problems parsing %s list\n", list_name);
		वापस -1;
	पूर्ण

	symbol_conf.has_filter = true;
	वापस 0;
पूर्ण

पूर्णांक setup_पूर्णांकlist(काष्ठा पूर्णांकlist **list, स्थिर अक्षर *list_str,
		  स्थिर अक्षर *list_name)
अणु
	अगर (list_str == शून्य)
		वापस 0;

	*list = पूर्णांकlist__new(list_str);
	अगर (!*list) अणु
		pr_err("problems parsing %s list\n", list_name);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक setup_addrlist(काष्ठा पूर्णांकlist **addr_list, काष्ठा strlist *sym_list)
अणु
	काष्ठा str_node *pos, *पंचांगp;
	अचिन्हित दीर्घ val;
	अक्षर *sep;
	स्थिर अक्षर *end;
	पूर्णांक i = 0, err;

	*addr_list = पूर्णांकlist__new(शून्य);
	अगर (!*addr_list)
		वापस -1;

	strlist__क्रम_each_entry_safe(pos, पंचांगp, sym_list) अणु
		त्रुटि_सं = 0;
		val = म_से_अदीर्घ(pos->s, &sep, 16);
		अगर (त्रुटि_सं || (sep == pos->s))
			जारी;

		अगर (*sep != '\0') अणु
			end = pos->s + म_माप(pos->s) - 1;
			जबतक (end >= sep && है_खाली(*end))
				end--;

			अगर (end >= sep)
				जारी;
		पूर्ण

		err = पूर्णांकlist__add(*addr_list, val);
		अगर (err)
			अवरोध;

		strlist__हटाओ(sym_list, pos);
		i++;
	पूर्ण

	अगर (i == 0) अणु
		पूर्णांकlist__delete(*addr_list);
		*addr_list = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool symbol__पढ़ो_kptr_restrict(व्योम)
अणु
	bool value = false;
	खाता *fp = ख_खोलो("/proc/sys/kernel/kptr_restrict", "r");

	अगर (fp != शून्य) अणु
		अक्षर line[8];

		अगर (ख_माला_लो(line, माप(line), fp) != शून्य)
			value = perf_cap__capable(CAP_SYSLOG) ?
					(म_से_प(line) >= 2) :
					(म_से_प(line) != 0);

		ख_बंद(fp);
	पूर्ण

	/* Per kernel/kallsyms.c:
	 * we also restrict when perf_event_paranoid > 1 w/o CAP_SYSLOG
	 */
	अगर (perf_event_paranoid() > 1 && !perf_cap__capable(CAP_SYSLOG))
		value = true;

	वापस value;
पूर्ण

पूर्णांक symbol__annotation_init(व्योम)
अणु
	अगर (symbol_conf.init_annotation)
		वापस 0;

	अगर (symbol_conf.initialized) अणु
		pr_err("Annotation needs to be init before symbol__init()\n");
		वापस -1;
	पूर्ण

	symbol_conf.priv_size += माप(काष्ठा annotation);
	symbol_conf.init_annotation = true;
	वापस 0;
पूर्ण

पूर्णांक symbol__init(काष्ठा perf_env *env)
अणु
	स्थिर अक्षर *symfs;

	अगर (symbol_conf.initialized)
		वापस 0;

	symbol_conf.priv_size = PERF_ALIGN(symbol_conf.priv_size, माप(u64));

	symbol__elf_init();

	अगर (symbol_conf.sort_by_name)
		symbol_conf.priv_size += (माप(काष्ठा symbol_name_rb_node) -
					  माप(काष्ठा symbol));

	अगर (symbol_conf.try_vmlinux_path && vmlinux_path__init(env) < 0)
		वापस -1;

	अगर (symbol_conf.field_sep && *symbol_conf.field_sep == '.') अणु
		pr_err("'.' is the only non valid --field-separator argument\n");
		वापस -1;
	पूर्ण

	अगर (setup_list(&symbol_conf.dso_list,
		       symbol_conf.dso_list_str, "dso") < 0)
		वापस -1;

	अगर (setup_list(&symbol_conf.comm_list,
		       symbol_conf.comm_list_str, "comm") < 0)
		जाओ out_मुक्त_dso_list;

	अगर (setup_पूर्णांकlist(&symbol_conf.pid_list,
		       symbol_conf.pid_list_str, "pid") < 0)
		जाओ out_मुक्त_comm_list;

	अगर (setup_पूर्णांकlist(&symbol_conf.tid_list,
		       symbol_conf.tid_list_str, "tid") < 0)
		जाओ out_मुक्त_pid_list;

	अगर (setup_list(&symbol_conf.sym_list,
		       symbol_conf.sym_list_str, "symbol") < 0)
		जाओ out_मुक्त_tid_list;

	अगर (symbol_conf.sym_list &&
	    setup_addrlist(&symbol_conf.addr_list, symbol_conf.sym_list) < 0)
		जाओ out_मुक्त_sym_list;

	अगर (setup_list(&symbol_conf.bt_stop_list,
		       symbol_conf.bt_stop_list_str, "symbol") < 0)
		जाओ out_मुक्त_sym_list;

	/*
	 * A path to symbols of "/" is identical to ""
	 * reset here क्रम simplicity.
	 */
	symfs = realpath(symbol_conf.symfs, शून्य);
	अगर (symfs == शून्य)
		symfs = symbol_conf.symfs;
	अगर (म_भेद(symfs, "/") == 0)
		symbol_conf.symfs = "";
	अगर (symfs != symbol_conf.symfs)
		मुक्त((व्योम *)symfs);

	symbol_conf.kptr_restrict = symbol__पढ़ो_kptr_restrict();

	symbol_conf.initialized = true;
	वापस 0;

out_मुक्त_sym_list:
	strlist__delete(symbol_conf.sym_list);
	पूर्णांकlist__delete(symbol_conf.addr_list);
out_मुक्त_tid_list:
	पूर्णांकlist__delete(symbol_conf.tid_list);
out_मुक्त_pid_list:
	पूर्णांकlist__delete(symbol_conf.pid_list);
out_मुक्त_comm_list:
	strlist__delete(symbol_conf.comm_list);
out_मुक्त_dso_list:
	strlist__delete(symbol_conf.dso_list);
	वापस -1;
पूर्ण

व्योम symbol__निकास(व्योम)
अणु
	अगर (!symbol_conf.initialized)
		वापस;
	strlist__delete(symbol_conf.bt_stop_list);
	strlist__delete(symbol_conf.sym_list);
	strlist__delete(symbol_conf.dso_list);
	strlist__delete(symbol_conf.comm_list);
	पूर्णांकlist__delete(symbol_conf.tid_list);
	पूर्णांकlist__delete(symbol_conf.pid_list);
	पूर्णांकlist__delete(symbol_conf.addr_list);
	vmlinux_path__निकास();
	symbol_conf.sym_list = symbol_conf.dso_list = symbol_conf.comm_list = शून्य;
	symbol_conf.bt_stop_list = शून्य;
	symbol_conf.initialized = false;
पूर्ण

पूर्णांक symbol__config_symfs(स्थिर काष्ठा option *opt __maybe_unused,
			 स्थिर अक्षर *dir, पूर्णांक unset __maybe_unused)
अणु
	अक्षर *bf = शून्य;
	पूर्णांक ret;

	symbol_conf.symfs = strdup(dir);
	अगर (symbol_conf.symfs == शून्य)
		वापस -ENOMEM;

	/* skip the locally configured cache अगर a symfs is given, and
	 * config buildid dir to symfs/.debug
	 */
	ret = aप्र_लिखो(&bf, "%s/%s", dir, ".debug");
	अगर (ret < 0)
		वापस -ENOMEM;

	set_buildid_dir(bf);

	मुक्त(bf);
	वापस 0;
पूर्ण

काष्ठा mem_info *mem_info__get(काष्ठा mem_info *mi)
अणु
	अगर (mi)
		refcount_inc(&mi->refcnt);
	वापस mi;
पूर्ण

व्योम mem_info__put(काष्ठा mem_info *mi)
अणु
	अगर (mi && refcount_dec_and_test(&mi->refcnt))
		मुक्त(mi);
पूर्ण

काष्ठा mem_info *mem_info__new(व्योम)
अणु
	काष्ठा mem_info *mi = zalloc(माप(*mi));

	अगर (mi)
		refcount_set(&mi->refcnt, 1);
	वापस mi;
पूर्ण
