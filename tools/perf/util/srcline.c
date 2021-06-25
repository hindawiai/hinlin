<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>

#समावेश "util/dso.h"
#समावेश "util/debug.h"
#समावेश "util/callchain.h"
#समावेश "util/symbol_conf.h"
#समावेश "srcline.h"
#समावेश "string2.h"
#समावेश "symbol.h"

bool srcline_full_filename;

अटल स्थिर अक्षर *dso__name(काष्ठा dso *dso)
अणु
	स्थिर अक्षर *dso_name;

	अगर (dso->symsrc_filename)
		dso_name = dso->symsrc_filename;
	अन्यथा
		dso_name = dso->दीर्घ_name;

	अगर (dso_name[0] == '[')
		वापस शून्य;

	अगर (!म_भेदन(dso_name, "/tmp/perf-", 10))
		वापस शून्य;

	वापस dso_name;
पूर्ण

अटल पूर्णांक अंतरभूत_list__append(काष्ठा symbol *symbol, अक्षर *srcline,
			       काष्ठा अंतरभूत_node *node)
अणु
	काष्ठा अंतरभूत_list *ilist;

	ilist = zalloc(माप(*ilist));
	अगर (ilist == शून्य)
		वापस -1;

	ilist->symbol = symbol;
	ilist->srcline = srcline;

	अगर (callchain_param.order == ORDER_CALLEE)
		list_add_tail(&ilist->list, &node->val);
	अन्यथा
		list_add(&ilist->list, &node->val);

	वापस 0;
पूर्ण

/* basename version that takes a स्थिर input string */
अटल स्थिर अक्षर *gnu_basename(स्थिर अक्षर *path)
अणु
	स्थिर अक्षर *base = म_खोजप(path, '/');

	वापस base ? base + 1 : path;
पूर्ण

अटल अक्षर *srcline_from_fileline(स्थिर अक्षर *file, अचिन्हित पूर्णांक line)
अणु
	अक्षर *srcline;

	अगर (!file)
		वापस शून्य;

	अगर (!srcline_full_filename)
		file = gnu_basename(file);

	अगर (aप्र_लिखो(&srcline, "%s:%u", file, line) < 0)
		वापस शून्य;

	वापस srcline;
पूर्ण

अटल काष्ठा symbol *new_अंतरभूत_sym(काष्ठा dso *dso,
				     काष्ठा symbol *base_sym,
				     स्थिर अक्षर *funcname)
अणु
	काष्ठा symbol *अंतरभूत_sym;
	अक्षर *demangled = शून्य;

	अगर (!funcname)
		funcname = "??";

	अगर (dso) अणु
		demangled = dso__demangle_sym(dso, 0, funcname);
		अगर (demangled)
			funcname = demangled;
	पूर्ण

	अगर (base_sym && म_भेद(funcname, base_sym->name) == 0) अणु
		/* reuse the real, existing symbol */
		अंतरभूत_sym = base_sym;
		/* ensure that we करोn't alias an अंतरभूतd symbol, which could
		 * lead to द्विगुन मुक्तs in अंतरभूत_node__delete
		 */
		निश्चित(!base_sym->अंतरभूतd);
	पूर्ण अन्यथा अणु
		/* create a fake symbol क्रम the अंतरभूत frame */
		अंतरभूत_sym = symbol__new(base_sym ? base_sym->start : 0,
					 base_sym ? (base_sym->end - base_sym->start) : 0,
					 base_sym ? base_sym->binding : 0,
					 base_sym ? base_sym->type : 0,
					 funcname);
		अगर (अंतरभूत_sym)
			अंतरभूत_sym->अंतरभूतd = 1;
	पूर्ण

	मुक्त(demangled);

	वापस अंतरभूत_sym;
पूर्ण

#अगर_घोषित HAVE_LIBBFD_SUPPORT

/*
 * Implement addr2line using libbfd.
 */
#घोषणा PACKAGE "perf"
#समावेश <bfd.h>

काष्ठा a2l_data अणु
	स्थिर अक्षर 	*input;
	u64	 	addr;

	bool 		found;
	स्थिर अक्षर 	*filename;
	स्थिर अक्षर 	*funcname;
	अचिन्हित 	line;

	bfd 		*abfd;
	asymbol 	**syms;
पूर्ण;

अटल पूर्णांक bfd_error(स्थिर अक्षर *string)
अणु
	स्थिर अक्षर *errmsg;

	errmsg = bfd_errmsg(bfd_get_error());
	ख_साफ(मानक_निकास);

	अगर (string)
		pr_debug("%s: %s\n", string, errmsg);
	अन्यथा
		pr_debug("%s\n", errmsg);

	वापस -1;
पूर्ण

अटल पूर्णांक slurp_symtab(bfd *abfd, काष्ठा a2l_data *a2l)
अणु
	दीर्घ storage;
	दीर्घ symcount;
	asymbol **syms;
	bfd_boolean dynamic = FALSE;

	अगर ((bfd_get_file_flags(abfd) & HAS_SYMS) == 0)
		वापस bfd_error(bfd_get_filename(abfd));

	storage = bfd_get_symtab_upper_bound(abfd);
	अगर (storage == 0L) अणु
		storage = bfd_get_dynamic_symtab_upper_bound(abfd);
		dynamic = TRUE;
	पूर्ण
	अगर (storage < 0L)
		वापस bfd_error(bfd_get_filename(abfd));

	syms = दो_स्मृति(storage);
	अगर (dynamic)
		symcount = bfd_canonicalize_dynamic_symtab(abfd, syms);
	अन्यथा
		symcount = bfd_canonicalize_symtab(abfd, syms);

	अगर (symcount < 0) अणु
		मुक्त(syms);
		वापस bfd_error(bfd_get_filename(abfd));
	पूर्ण

	a2l->syms = syms;
	वापस 0;
पूर्ण

अटल व्योम find_address_in_section(bfd *abfd, asection *section, व्योम *data)
अणु
	bfd_vma pc, vma;
	bfd_माप_प्रकारype size;
	काष्ठा a2l_data *a2l = data;
	flagword flags;

	अगर (a2l->found)
		वापस;

#अगर_घोषित bfd_get_section_flags
	flags = bfd_get_section_flags(abfd, section);
#अन्यथा
	flags = bfd_section_flags(section);
#पूर्ण_अगर
	अगर ((flags & SEC_ALLOC) == 0)
		वापस;

	pc = a2l->addr;
#अगर_घोषित bfd_get_section_vma
	vma = bfd_get_section_vma(abfd, section);
#अन्यथा
	vma = bfd_section_vma(section);
#पूर्ण_अगर
#अगर_घोषित bfd_get_section_size
	size = bfd_get_section_size(section);
#अन्यथा
	size = bfd_section_size(section);
#पूर्ण_अगर

	अगर (pc < vma || pc >= vma + size)
		वापस;

	a2l->found = bfd_find_nearest_line(abfd, section, a2l->syms, pc - vma,
					   &a2l->filename, &a2l->funcname,
					   &a2l->line);

	अगर (a2l->filename && !म_माप(a2l->filename))
		a2l->filename = शून्य;
पूर्ण

अटल काष्ठा a2l_data *addr2line_init(स्थिर अक्षर *path)
अणु
	bfd *abfd;
	काष्ठा a2l_data *a2l = शून्य;

	abfd = bfd_खोलोr(path, शून्य);
	अगर (abfd == शून्य)
		वापस शून्य;

	अगर (!bfd_check_क्रमmat(abfd, bfd_object))
		जाओ out;

	a2l = zalloc(माप(*a2l));
	अगर (a2l == शून्य)
		जाओ out;

	a2l->abfd = abfd;
	a2l->input = strdup(path);
	अगर (a2l->input == शून्य)
		जाओ out;

	अगर (slurp_symtab(abfd, a2l))
		जाओ out;

	वापस a2l;

out:
	अगर (a2l) अणु
		zमुक्त((अक्षर **)&a2l->input);
		मुक्त(a2l);
	पूर्ण
	bfd_बंद(abfd);
	वापस शून्य;
पूर्ण

अटल व्योम addr2line_cleanup(काष्ठा a2l_data *a2l)
अणु
	अगर (a2l->abfd)
		bfd_बंद(a2l->abfd);
	zमुक्त((अक्षर **)&a2l->input);
	zमुक्त(&a2l->syms);
	मुक्त(a2l);
पूर्ण

#घोषणा MAX_INLINE_NEST 1024

अटल पूर्णांक अंतरभूत_list__append_dso_a2l(काष्ठा dso *dso,
				       काष्ठा अंतरभूत_node *node,
				       काष्ठा symbol *sym)
अणु
	काष्ठा a2l_data *a2l = dso->a2l;
	काष्ठा symbol *अंतरभूत_sym = new_अंतरभूत_sym(dso, sym, a2l->funcname);
	अक्षर *srcline = शून्य;

	अगर (a2l->filename)
		srcline = srcline_from_fileline(a2l->filename, a2l->line);

	वापस अंतरभूत_list__append(अंतरभूत_sym, srcline, node);
पूर्ण

अटल पूर्णांक addr2line(स्थिर अक्षर *dso_name, u64 addr,
		     अक्षर **file, अचिन्हित पूर्णांक *line, काष्ठा dso *dso,
		     bool unwind_अंतरभूतs, काष्ठा अंतरभूत_node *node,
		     काष्ठा symbol *sym)
अणु
	पूर्णांक ret = 0;
	काष्ठा a2l_data *a2l = dso->a2l;

	अगर (!a2l) अणु
		dso->a2l = addr2line_init(dso_name);
		a2l = dso->a2l;
	पूर्ण

	अगर (a2l == शून्य) अणु
		अगर (!symbol_conf.disable_add2line_warn)
			pr_warning("addr2line_init failed for %s\n", dso_name);
		वापस 0;
	पूर्ण

	a2l->addr = addr;
	a2l->found = false;

	bfd_map_over_sections(a2l->abfd, find_address_in_section, a2l);

	अगर (!a2l->found)
		वापस 0;

	अगर (unwind_अंतरभूतs) अणु
		पूर्णांक cnt = 0;

		अगर (node && अंतरभूत_list__append_dso_a2l(dso, node, sym))
			वापस 0;

		जबतक (bfd_find_अंतरभूतr_info(a2l->abfd, &a2l->filename,
					     &a2l->funcname, &a2l->line) &&
		       cnt++ < MAX_INLINE_NEST) अणु

			अगर (a2l->filename && !म_माप(a2l->filename))
				a2l->filename = शून्य;

			अगर (node != शून्य) अणु
				अगर (अंतरभूत_list__append_dso_a2l(dso, node, sym))
					वापस 0;
				// found at least one अंतरभूत frame
				ret = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (file) अणु
		*file = a2l->filename ? strdup(a2l->filename) : शून्य;
		ret = *file ? 1 : 0;
	पूर्ण

	अगर (line)
		*line = a2l->line;

	वापस ret;
पूर्ण

व्योम dso__मुक्त_a2l(काष्ठा dso *dso)
अणु
	काष्ठा a2l_data *a2l = dso->a2l;

	अगर (!a2l)
		वापस;

	addr2line_cleanup(a2l);

	dso->a2l = शून्य;
पूर्ण

अटल काष्ठा अंतरभूत_node *addr2अंतरभूतs(स्थिर अक्षर *dso_name, u64 addr,
					काष्ठा dso *dso, काष्ठा symbol *sym)
अणु
	काष्ठा अंतरभूत_node *node;

	node = zalloc(माप(*node));
	अगर (node == शून्य) अणु
		लिखो_त्रुटि("not enough memory for the inline node");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&node->val);
	node->addr = addr;

	addr2line(dso_name, addr, शून्य, शून्य, dso, true, node, sym);
	वापस node;
पूर्ण

#अन्यथा /* HAVE_LIBBFD_SUPPORT */

अटल पूर्णांक filename_split(अक्षर *filename, अचिन्हित पूर्णांक *line_nr)
अणु
	अक्षर *sep;

	sep = म_अक्षर(filename, '\n');
	अगर (sep)
		*sep = '\0';

	अगर (!म_भेद(filename, "??:0"))
		वापस 0;

	sep = म_अक्षर(filename, ':');
	अगर (sep) अणु
		*sep++ = '\0';
		*line_nr = म_से_अदीर्घ(sep, शून्य, 0);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक addr2line(स्थिर अक्षर *dso_name, u64 addr,
		     अक्षर **file, अचिन्हित पूर्णांक *line_nr,
		     काष्ठा dso *dso __maybe_unused,
		     bool unwind_अंतरभूतs __maybe_unused,
		     काष्ठा अंतरभूत_node *node __maybe_unused,
		     काष्ठा symbol *sym __maybe_unused)
अणु
	खाता *fp;
	अक्षर cmd[PATH_MAX];
	अक्षर *filename = शून्य;
	माप_प्रकार len;
	पूर्णांक ret = 0;

	scnम_लिखो(cmd, माप(cmd), "addr2line -e %s %016"PRIx64,
		  dso_name, addr);

	fp = pखोलो(cmd, "r");
	अगर (fp == शून्य) अणु
		pr_warning("popen failed for %s\n", dso_name);
		वापस 0;
	पूर्ण

	अगर (getline(&filename, &len, fp) < 0 || !len) अणु
		pr_warning("addr2line has no output for %s\n", dso_name);
		जाओ out;
	पूर्ण

	ret = filename_split(filename, line_nr);
	अगर (ret != 1) अणु
		मुक्त(filename);
		जाओ out;
	पूर्ण

	*file = filename;

out:
	pबंद(fp);
	वापस ret;
पूर्ण

व्योम dso__मुक्त_a2l(काष्ठा dso *dso __maybe_unused)
अणु
पूर्ण

अटल काष्ठा अंतरभूत_node *addr2अंतरभूतs(स्थिर अक्षर *dso_name, u64 addr,
					काष्ठा dso *dso __maybe_unused,
					काष्ठा symbol *sym)
अणु
	खाता *fp;
	अक्षर cmd[PATH_MAX];
	काष्ठा अंतरभूत_node *node;
	अक्षर *filename = शून्य;
	अक्षर *funcname = शून्य;
	माप_प्रकार filelen, funclen;
	अचिन्हित पूर्णांक line_nr = 0;

	scnम_लिखो(cmd, माप(cmd), "addr2line -e %s -i -f %016"PRIx64,
		  dso_name, addr);

	fp = pखोलो(cmd, "r");
	अगर (fp == शून्य) अणु
		pr_err("popen failed for %s\n", dso_name);
		वापस शून्य;
	पूर्ण

	node = zalloc(माप(*node));
	अगर (node == शून्य) अणु
		लिखो_त्रुटि("not enough memory for the inline node");
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&node->val);
	node->addr = addr;

	/* addr2line -f generates two lines क्रम each अंतरभूतd functions */
	जबतक (getline(&funcname, &funclen, fp) != -1) अणु
		अक्षर *srcline;
		काष्ठा symbol *अंतरभूत_sym;

		strim(funcname);

		अगर (getline(&filename, &filelen, fp) == -1)
			जाओ out;

		अगर (filename_split(filename, &line_nr) != 1)
			जाओ out;

		srcline = srcline_from_fileline(filename, line_nr);
		अंतरभूत_sym = new_अंतरभूत_sym(dso, sym, funcname);

		अगर (अंतरभूत_list__append(अंतरभूत_sym, srcline, node) != 0) अणु
			मुक्त(srcline);
			अगर (अंतरभूत_sym && अंतरभूत_sym->अंतरभूतd)
				symbol__delete(अंतरभूत_sym);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	pबंद(fp);
	मुक्त(filename);
	मुक्त(funcname);

	वापस node;
पूर्ण

#पूर्ण_अगर /* HAVE_LIBBFD_SUPPORT */

/*
 * Number of addr2line failures (without success) beक्रमe disabling it क्रम that
 * dso.
 */
#घोषणा A2L_FAIL_LIMIT 123

अक्षर *__get_srcline(काष्ठा dso *dso, u64 addr, काष्ठा symbol *sym,
		  bool show_sym, bool show_addr, bool unwind_अंतरभूतs,
		  u64 ip)
अणु
	अक्षर *file = शून्य;
	अचिन्हित line = 0;
	अक्षर *srcline;
	स्थिर अक्षर *dso_name;

	अगर (!dso->has_srcline)
		जाओ out;

	dso_name = dso__name(dso);
	अगर (dso_name == शून्य)
		जाओ out;

	अगर (!addr2line(dso_name, addr, &file, &line, dso,
		       unwind_अंतरभूतs, शून्य, sym))
		जाओ out;

	srcline = srcline_from_fileline(file, line);
	मुक्त(file);

	अगर (!srcline)
		जाओ out;

	dso->a2l_fails = 0;

	वापस srcline;

out:
	अगर (dso->a2l_fails && ++dso->a2l_fails > A2L_FAIL_LIMIT) अणु
		dso->has_srcline = 0;
		dso__मुक्त_a2l(dso);
	पूर्ण

	अगर (!show_addr)
		वापस (show_sym && sym) ?
			    strndup(sym->name, sym->namelen) : शून्य;

	अगर (sym) अणु
		अगर (aप्र_लिखो(&srcline, "%s+%" PRIu64, show_sym ? sym->name : "",
					ip - sym->start) < 0)
			वापस SRCLINE_UNKNOWN;
	पूर्ण अन्यथा अगर (aप्र_लिखो(&srcline, "%s[%" PRIx64 "]", dso->लघु_name, addr) < 0)
		वापस SRCLINE_UNKNOWN;
	वापस srcline;
पूर्ण

/* Returns filename and fills in line number in line */
अक्षर *get_srcline_split(काष्ठा dso *dso, u64 addr, अचिन्हित *line)
अणु
	अक्षर *file = शून्य;
	स्थिर अक्षर *dso_name;

	अगर (!dso->has_srcline)
		जाओ out;

	dso_name = dso__name(dso);
	अगर (dso_name == शून्य)
		जाओ out;

	अगर (!addr2line(dso_name, addr, &file, line, dso, true, शून्य, शून्य))
		जाओ out;

	dso->a2l_fails = 0;
	वापस file;

out:
	अगर (dso->a2l_fails && ++dso->a2l_fails > A2L_FAIL_LIMIT) अणु
		dso->has_srcline = 0;
		dso__मुक्त_a2l(dso);
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम मुक्त_srcline(अक्षर *srcline)
अणु
	अगर (srcline && म_भेद(srcline, SRCLINE_UNKNOWN) != 0)
		मुक्त(srcline);
पूर्ण

अक्षर *get_srcline(काष्ठा dso *dso, u64 addr, काष्ठा symbol *sym,
		  bool show_sym, bool show_addr, u64 ip)
अणु
	वापस __get_srcline(dso, addr, sym, show_sym, show_addr, false, ip);
पूर्ण

काष्ठा srcline_node अणु
	u64			addr;
	अक्षर			*srcline;
	काष्ठा rb_node		rb_node;
पूर्ण;

व्योम srcline__tree_insert(काष्ठा rb_root_cached *tree, u64 addr, अक्षर *srcline)
अणु
	काष्ठा rb_node **p = &tree->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा srcline_node *i, *node;
	bool lefपंचांगost = true;

	node = zalloc(माप(काष्ठा srcline_node));
	अगर (!node) अणु
		लिखो_त्रुटि("not enough memory for the srcline node");
		वापस;
	पूर्ण

	node->addr = addr;
	node->srcline = srcline;

	जबतक (*p != शून्य) अणु
		parent = *p;
		i = rb_entry(parent, काष्ठा srcline_node, rb_node);
		अगर (addr < i->addr)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण
	rb_link_node(&node->rb_node, parent, p);
	rb_insert_color_cached(&node->rb_node, tree, lefपंचांगost);
पूर्ण

अक्षर *srcline__tree_find(काष्ठा rb_root_cached *tree, u64 addr)
अणु
	काष्ठा rb_node *n = tree->rb_root.rb_node;

	जबतक (n) अणु
		काष्ठा srcline_node *i = rb_entry(n, काष्ठा srcline_node,
						  rb_node);

		अगर (addr < i->addr)
			n = n->rb_left;
		अन्यथा अगर (addr > i->addr)
			n = n->rb_right;
		अन्यथा
			वापस i->srcline;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम srcline__tree_delete(काष्ठा rb_root_cached *tree)
अणु
	काष्ठा srcline_node *pos;
	काष्ठा rb_node *next = rb_first_cached(tree);

	जबतक (next) अणु
		pos = rb_entry(next, काष्ठा srcline_node, rb_node);
		next = rb_next(&pos->rb_node);
		rb_erase_cached(&pos->rb_node, tree);
		मुक्त_srcline(pos->srcline);
		zमुक्त(&pos);
	पूर्ण
पूर्ण

काष्ठा अंतरभूत_node *dso__parse_addr_अंतरभूतs(काष्ठा dso *dso, u64 addr,
					    काष्ठा symbol *sym)
अणु
	स्थिर अक्षर *dso_name;

	dso_name = dso__name(dso);
	अगर (dso_name == शून्य)
		वापस शून्य;

	वापस addr2अंतरभूतs(dso_name, addr, dso, sym);
पूर्ण

व्योम अंतरभूत_node__delete(काष्ठा अंतरभूत_node *node)
अणु
	काष्ठा अंतरभूत_list *ilist, *पंचांगp;

	list_क्रम_each_entry_safe(ilist, पंचांगp, &node->val, list) अणु
		list_del_init(&ilist->list);
		मुक्त_srcline(ilist->srcline);
		/* only the अंतरभूतd symbols are owned by the list */
		अगर (ilist->symbol && ilist->symbol->अंतरभूतd)
			symbol__delete(ilist->symbol);
		मुक्त(ilist);
	पूर्ण

	मुक्त(node);
पूर्ण

व्योम अंतरभूतs__tree_insert(काष्ठा rb_root_cached *tree,
			  काष्ठा अंतरभूत_node *अंतरभूतs)
अणु
	काष्ठा rb_node **p = &tree->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	स्थिर u64 addr = अंतरभूतs->addr;
	काष्ठा अंतरभूत_node *i;
	bool lefपंचांगost = true;

	जबतक (*p != शून्य) अणु
		parent = *p;
		i = rb_entry(parent, काष्ठा अंतरभूत_node, rb_node);
		अगर (addr < i->addr)
			p = &(*p)->rb_left;
		अन्यथा अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण
	rb_link_node(&अंतरभूतs->rb_node, parent, p);
	rb_insert_color_cached(&अंतरभूतs->rb_node, tree, lefपंचांगost);
पूर्ण

काष्ठा अंतरभूत_node *अंतरभूतs__tree_find(काष्ठा rb_root_cached *tree, u64 addr)
अणु
	काष्ठा rb_node *n = tree->rb_root.rb_node;

	जबतक (n) अणु
		काष्ठा अंतरभूत_node *i = rb_entry(n, काष्ठा अंतरभूत_node,
						 rb_node);

		अगर (addr < i->addr)
			n = n->rb_left;
		अन्यथा अगर (addr > i->addr)
			n = n->rb_right;
		अन्यथा
			वापस i;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम अंतरभूतs__tree_delete(काष्ठा rb_root_cached *tree)
अणु
	काष्ठा अंतरभूत_node *pos;
	काष्ठा rb_node *next = rb_first_cached(tree);

	जबतक (next) अणु
		pos = rb_entry(next, काष्ठा अंतरभूत_node, rb_node);
		next = rb_next(&pos->rb_node);
		rb_erase_cached(&pos->rb_node, tree);
		अंतरभूत_node__delete(pos);
	पूर्ण
पूर्ण
