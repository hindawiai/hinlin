<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * resolve_btfids scans Elf object क्रम .BTF_ids section and resolves
 * its symbols with BTF ID values.
 *
 * Each symbol poपूर्णांकs to 4 bytes data and is expected to have
 * following name syntax:
 *
 * __BTF_ID__<type>__<symbol>[__<id>]
 *
 * type is:
 *
 *   func    - lookup BTF_KIND_FUNC symbol with <symbol> name
 *             and store its ID पूर्णांकo the data:
 *
 *             __BTF_ID__func__vfs_बंद__1:
 *             .zero 4
 *
 *   काष्ठा  - lookup BTF_KIND_STRUCT symbol with <symbol> name
 *             and store its ID पूर्णांकo the data:
 *
 *             __BTF_ID__काष्ठा__sk_buff__1:
 *             .zero 4
 *
 *   जोड़   - lookup BTF_KIND_UNION symbol with <symbol> name
 *             and store its ID पूर्णांकo the data:
 *
 *             __BTF_ID__जोड़__thपढ़ो_जोड़__1:
 *             .zero 4
 *
 *   प्रकार - lookup BTF_KIND_TYPEDEF symbol with <symbol> name
 *             and store its ID पूर्णांकo the data:
 *
 *             __BTF_ID__प्रकार__pid_t__1:
 *             .zero 4
 *
 *   set     - store symbol size पूर्णांकo first 4 bytes and sort following
 *             ID list
 *
 *             __BTF_ID__set__list:
 *             .zero 4
 *             list:
 *             __BTF_ID__func__vfs_getattr__3:
 *             .zero 4
 *             __BTF_ID__func__vfs_fallocate__4:
 *             .zero 4
 */

#घोषणा  _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <libelf.h>
#समावेश <gelf.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/rbtree.h>
#समावेश <linux/zभाग.स>
#समावेश <linux/err.h>
#समावेश <btf.h>
#समावेश <libbpf.h>
#समावेश <parse-options.h>

#घोषणा BTF_IDS_SECTION	".BTF_ids"
#घोषणा BTF_ID		"__BTF_ID__"

#घोषणा BTF_STRUCT	"struct"
#घोषणा BTF_UNION	"union"
#घोषणा BTF_TYPEDEF	"typedef"
#घोषणा BTF_FUNC	"func"
#घोषणा BTF_SET		"set"

#घोषणा ADDR_CNT	100

काष्ठा btf_id अणु
	काष्ठा rb_node	 rb_node;
	अक्षर		*name;
	जोड़ अणु
		पूर्णांक	 id;
		पूर्णांक	 cnt;
	पूर्ण;
	पूर्णांक		 addr_cnt;
	Elf64_Addr	 addr[ADDR_CNT];
पूर्ण;

काष्ठा object अणु
	स्थिर अक्षर *path;
	स्थिर अक्षर *btf;

	काष्ठा अणु
		पूर्णांक		 fd;
		Elf		*elf;
		Elf_Data	*symbols;
		Elf_Data	*idlist;
		पूर्णांक		 symbols_shndx;
		पूर्णांक		 idlist_shndx;
		माप_प्रकार		 strtabidx;
		अचिन्हित दीर्घ	 idlist_addr;
	पूर्ण efile;

	काष्ठा rb_root	sets;
	काष्ठा rb_root	काष्ठाs;
	काष्ठा rb_root	जोड़s;
	काष्ठा rb_root	प्रकारs;
	काष्ठा rb_root	funcs;

	पूर्णांक nr_funcs;
	पूर्णांक nr_काष्ठाs;
	पूर्णांक nr_जोड़s;
	पूर्णांक nr_प्रकारs;
पूर्ण;

अटल पूर्णांक verbose;

अटल पूर्णांक eम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक ret = 0;

	अगर (var >= level) अणु
		बहु_शुरू(args, fmt);
		ret = भख_लिखो(मानक_त्रुटि, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण
	वापस ret;
पूर्ण

#अगर_अघोषित pr_fmt
#घोषणा pr_fmt(fmt) fmt
#पूर्ण_अगर

#घोषणा pr_debug(fmt, ...) \
	eम_लिखो(1, verbose, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_debugN(n, fmt, ...) \
	eम_लिखो(n, verbose, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_debug2(fmt, ...) pr_debugN(2, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_err(fmt, ...) \
	eम_लिखो(0, verbose, pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_info(fmt, ...) \
	eम_लिखो(0, verbose, pr_fmt(fmt), ##__VA_ARGS__)

अटल bool is_btf_id(स्थिर अक्षर *name)
अणु
	वापस name && !म_भेदन(name, BTF_ID, माप(BTF_ID) - 1);
पूर्ण

अटल काष्ठा btf_id *btf_id__find(काष्ठा rb_root *root, स्थिर अक्षर *name)
अणु
	काष्ठा rb_node *p = root->rb_node;
	काष्ठा btf_id *id;
	पूर्णांक cmp;

	जबतक (p) अणु
		id = rb_entry(p, काष्ठा btf_id, rb_node);
		cmp = म_भेद(id->name, name);
		अगर (cmp < 0)
			p = p->rb_left;
		अन्यथा अगर (cmp > 0)
			p = p->rb_right;
		अन्यथा
			वापस id;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा btf_id*
btf_id__add(काष्ठा rb_root *root, अक्षर *name, bool unique)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा btf_id *id;
	पूर्णांक cmp;

	जबतक (*p != शून्य) अणु
		parent = *p;
		id = rb_entry(parent, काष्ठा btf_id, rb_node);
		cmp = म_भेद(id->name, name);
		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (cmp > 0)
			p = &(*p)->rb_right;
		अन्यथा
			वापस unique ? शून्य : id;
	पूर्ण

	id = zalloc(माप(*id));
	अगर (id) अणु
		pr_debug("adding symbol %s\n", name);
		id->name = name;
		rb_link_node(&id->rb_node, parent, p);
		rb_insert_color(&id->rb_node, root);
	पूर्ण
	वापस id;
पूर्ण

अटल अक्षर *get_id(स्थिर अक्षर *prefix_end)
अणु
	/*
	 * __BTF_ID__func__vfs_truncate__0
	 * prefix_end =  ^
	 * pos        =    ^
	 */
	पूर्णांक len = म_माप(prefix_end);
	पूर्णांक pos = माप("__") - 1;
	अक्षर *p, *id;

	अगर (pos >= len)
		वापस शून्य;

	id = strdup(prefix_end + pos);
	अगर (id) अणु
		/*
		 * __BTF_ID__func__vfs_truncate__0
		 * id =            ^
		 *
		 * cut the unique id part
		 */
		p = म_खोजप(id, '_');
		p--;
		अगर (*p != '_') अणु
			मुक्त(id);
			वापस शून्य;
		पूर्ण
		*p = '\0';
	पूर्ण
	वापस id;
पूर्ण

अटल काष्ठा btf_id *add_set(काष्ठा object *obj, अक्षर *name)
अणु
	/*
	 * __BTF_ID__set__name
	 * name =    ^
	 * id   =         ^
	 */
	अक्षर *id = name + माप(BTF_SET "__") - 1;
	पूर्णांक len = म_माप(name);

	अगर (id >= name + len) अणु
		pr_err("FAILED to parse set name: %s\n", name);
		वापस शून्य;
	पूर्ण

	वापस btf_id__add(&obj->sets, id, true);
पूर्ण

अटल काष्ठा btf_id *add_symbol(काष्ठा rb_root *root, अक्षर *name, माप_प्रकार size)
अणु
	अक्षर *id;

	id = get_id(name + size);
	अगर (!id) अणु
		pr_err("FAILED to parse symbol name: %s\n", name);
		वापस शून्य;
	पूर्ण

	वापस btf_id__add(root, id, false);
पूर्ण

/* Older libelf.h and glibc elf.h might not yet define the ELF compression types. */
#अगर_अघोषित SHF_COMPRESSED
#घोषणा SHF_COMPRESSED (1 << 11) /* Section with compressed data. */
#पूर्ण_अगर

/*
 * The data of compressed section should be aligned to 4
 * (क्रम 32bit) or 8 (क्रम 64 bit) bytes. The binutils ld
 * sets sh_addralign to 1, which makes libelf fail with
 * misaligned section error during the update:
 *    FAILED elf_update(WRITE): invalid section alignment
 *
 * While रुकोing क्रम ld fix, we fix the compressed sections
 * sh_addralign value manualy.
 */
अटल पूर्णांक compressed_section_fix(Elf *elf, Elf_Scn *scn, GElf_Shdr *sh)
अणु
	पूर्णांक expected = gelf_अ_लोlass(elf) == ELFCLASS32 ? 4 : 8;

	अगर (!(sh->sh_flags & SHF_COMPRESSED))
		वापस 0;

	अगर (sh->sh_addralign == expected)
		वापस 0;

	pr_debug2(" - fixing wrong alignment sh_addralign %u, expected %u\n",
		  sh->sh_addralign, expected);

	sh->sh_addralign = expected;

	अगर (gelf_update_shdr(scn, sh) == 0) अणु
		म_लिखो("FAILED cannot update section header: %s\n",
			elf_errmsg(-1));
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक elf_collect(काष्ठा object *obj)
अणु
	Elf_Scn *scn = शून्य;
	माप_प्रकार shdrstrndx;
	पूर्णांक idx = 0;
	Elf *elf;
	पूर्णांक fd;

	fd = खोलो(obj->path, O_RDWR, 0666);
	अगर (fd == -1) अणु
		pr_err("FAILED cannot open %s: %s\n",
			obj->path, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	elf_version(EV_CURRENT);

	elf = elf_begin(fd, ELF_C_RDWR_MMAP, शून्य);
	अगर (!elf) अणु
		pr_err("FAILED cannot create ELF descriptor: %s\n",
			elf_errmsg(-1));
		वापस -1;
	पूर्ण

	obj->efile.fd  = fd;
	obj->efile.elf = elf;

	elf_flagelf(elf, ELF_C_SET, ELF_F_LAYOUT);

	अगर (elf_माला_लोhdrstrndx(elf, &shdrstrndx) != 0) अणु
		pr_err("FAILED cannot get shdr str ndx\n");
		वापस -1;
	पूर्ण

	/*
	 * Scan all the elf sections and look क्रम save data
	 * from .BTF_ids section and symbols.
	 */
	जबतक ((scn = elf_nextscn(elf, scn)) != शून्य) अणु
		Elf_Data *data;
		GElf_Shdr sh;
		अक्षर *name;

		idx++;
		अगर (gelf_माला_लोhdr(scn, &sh) != &sh) अणु
			pr_err("FAILED get section(%d) header\n", idx);
			वापस -1;
		पूर्ण

		name = elf_strptr(elf, shdrstrndx, sh.sh_name);
		अगर (!name) अणु
			pr_err("FAILED get section(%d) name\n", idx);
			वापस -1;
		पूर्ण

		data = elf_getdata(scn, 0);
		अगर (!data) अणु
			pr_err("FAILED to get section(%d) data from %s\n",
				idx, name);
			वापस -1;
		पूर्ण

		pr_debug2("section(%d) %s, size %ld, link %d, flags %lx, type=%d\n",
			  idx, name, (अचिन्हित दीर्घ) data->d_size,
			  (पूर्णांक) sh.sh_link, (अचिन्हित दीर्घ) sh.sh_flags,
			  (पूर्णांक) sh.sh_type);

		अगर (sh.sh_type == SHT_SYMTAB) अणु
			obj->efile.symbols       = data;
			obj->efile.symbols_shndx = idx;
			obj->efile.strtabidx     = sh.sh_link;
		पूर्ण अन्यथा अगर (!म_भेद(name, BTF_IDS_SECTION)) अणु
			obj->efile.idlist       = data;
			obj->efile.idlist_shndx = idx;
			obj->efile.idlist_addr  = sh.sh_addr;
		पूर्ण

		अगर (compressed_section_fix(elf, scn, &sh))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक symbols_collect(काष्ठा object *obj)
अणु
	Elf_Scn *scn = शून्य;
	पूर्णांक n, i;
	GElf_Shdr sh;
	अक्षर *name;

	scn = elf_माला_लोcn(obj->efile.elf, obj->efile.symbols_shndx);
	अगर (!scn)
		वापस -1;

	अगर (gelf_माला_लोhdr(scn, &sh) != &sh)
		वापस -1;

	n = sh.sh_size / sh.sh_entsize;

	/*
	 * Scan symbols and look क्रम the ones starting with
	 * __BTF_ID__* over .BTF_ids section.
	 */
	क्रम (i = 0; i < n; i++) अणु
		अक्षर *prefix;
		काष्ठा btf_id *id;
		GElf_Sym sym;

		अगर (!gelf_माला_लोym(obj->efile.symbols, i, &sym))
			वापस -1;

		अगर (sym.st_shndx != obj->efile.idlist_shndx)
			जारी;

		name = elf_strptr(obj->efile.elf, obj->efile.strtabidx,
				  sym.st_name);

		अगर (!is_btf_id(name))
			जारी;

		/*
		 * __BTF_ID__TYPE__vfs_truncate__0
		 * prefix =  ^
		 */
		prefix = name + माप(BTF_ID) - 1;

		/* काष्ठा */
		अगर (!म_भेदन(prefix, BTF_STRUCT, माप(BTF_STRUCT) - 1)) अणु
			obj->nr_काष्ठाs++;
			id = add_symbol(&obj->काष्ठाs, prefix, माप(BTF_STRUCT) - 1);
		/* जोड़  */
		पूर्ण अन्यथा अगर (!म_भेदन(prefix, BTF_UNION, माप(BTF_UNION) - 1)) अणु
			obj->nr_जोड़s++;
			id = add_symbol(&obj->जोड़s, prefix, माप(BTF_UNION) - 1);
		/* प्रकार */
		पूर्ण अन्यथा अगर (!म_भेदन(prefix, BTF_TYPEDEF, माप(BTF_TYPEDEF) - 1)) अणु
			obj->nr_प्रकारs++;
			id = add_symbol(&obj->प्रकारs, prefix, माप(BTF_TYPEDEF) - 1);
		/* func */
		पूर्ण अन्यथा अगर (!म_भेदन(prefix, BTF_FUNC, माप(BTF_FUNC) - 1)) अणु
			obj->nr_funcs++;
			id = add_symbol(&obj->funcs, prefix, माप(BTF_FUNC) - 1);
		/* set */
		पूर्ण अन्यथा अगर (!म_भेदन(prefix, BTF_SET, माप(BTF_SET) - 1)) अणु
			id = add_set(obj, prefix);
			/*
			 * SET objects store list's count, which is encoded
			 * in symbol's size, together with 'cnt' field hence
			 * that - 1.
			 */
			अगर (id)
				id->cnt = sym.st_size / माप(पूर्णांक) - 1;
		पूर्ण अन्यथा अणु
			pr_err("FAILED unsupported prefix %s\n", prefix);
			वापस -1;
		पूर्ण

		अगर (!id)
			वापस -ENOMEM;

		अगर (id->addr_cnt >= ADDR_CNT) अणु
			pr_err("FAILED symbol %s crossed the number of allowed lists\n",
				id->name);
			वापस -1;
		पूर्ण
		id->addr[id->addr_cnt++] = sym.st_value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक symbols_resolve(काष्ठा object *obj)
अणु
	पूर्णांक nr_प्रकारs = obj->nr_प्रकारs;
	पूर्णांक nr_काष्ठाs  = obj->nr_काष्ठाs;
	पूर्णांक nr_जोड़s   = obj->nr_जोड़s;
	पूर्णांक nr_funcs    = obj->nr_funcs;
	पूर्णांक err, type_id;
	काष्ठा btf *btf;
	__u32 nr_types;

	btf = btf__parse(obj->btf ?: obj->path, शून्य);
	err = libbpf_get_error(btf);
	अगर (err) अणु
		pr_err("FAILED: load BTF from %s: %s\n",
			obj->path, म_त्रुटि(-err));
		वापस -1;
	पूर्ण

	err = -1;
	nr_types = btf__get_nr_types(btf);

	/*
	 * Iterate all the BTF types and search क्रम collected symbol IDs.
	 */
	क्रम (type_id = 1; type_id <= nr_types; type_id++) अणु
		स्थिर काष्ठा btf_type *type;
		काष्ठा rb_root *root;
		काष्ठा btf_id *id;
		स्थिर अक्षर *str;
		पूर्णांक *nr;

		type = btf__type_by_id(btf, type_id);
		अगर (!type) अणु
			pr_err("FAILED: malformed BTF, can't resolve type for ID %d\n",
				type_id);
			जाओ out;
		पूर्ण

		अगर (btf_is_func(type) && nr_funcs) अणु
			nr   = &nr_funcs;
			root = &obj->funcs;
		पूर्ण अन्यथा अगर (btf_is_काष्ठा(type) && nr_काष्ठाs) अणु
			nr   = &nr_काष्ठाs;
			root = &obj->काष्ठाs;
		पूर्ण अन्यथा अगर (btf_is_जोड़(type) && nr_जोड़s) अणु
			nr   = &nr_जोड़s;
			root = &obj->जोड़s;
		पूर्ण अन्यथा अगर (btf_is_प्रकार(type) && nr_प्रकारs) अणु
			nr   = &nr_प्रकारs;
			root = &obj->प्रकारs;
		पूर्ण अन्यथा
			जारी;

		str = btf__name_by_offset(btf, type->name_off);
		अगर (!str) अणु
			pr_err("FAILED: malformed BTF, can't resolve name for ID %d\n",
				type_id);
			जाओ out;
		पूर्ण

		id = btf_id__find(root, str);
		अगर (id) अणु
			अगर (id->id) अणु
				pr_info("WARN: multiple IDs found for '%s': %d, %d - using %d\n",
					str, id->id, type_id, id->id);
			पूर्ण अन्यथा अणु
				id->id = type_id;
				(*nr)--;
			पूर्ण
		पूर्ण
	पूर्ण

	err = 0;
out:
	btf__मुक्त(btf);
	वापस err;
पूर्ण

अटल पूर्णांक id_patch(काष्ठा object *obj, काष्ठा btf_id *id)
अणु
	Elf_Data *data = obj->efile.idlist;
	पूर्णांक *ptr = data->d_buf;
	पूर्णांक i;

	अगर (!id->id) अणु
		pr_err("FAILED unresolved symbol %s\n", id->name);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < id->addr_cnt; i++) अणु
		अचिन्हित दीर्घ addr = id->addr[i];
		अचिन्हित दीर्घ idx = addr - obj->efile.idlist_addr;

		pr_debug("patching addr %5lu: ID %7d [%s]\n",
			 idx, id->id, id->name);

		अगर (idx >= data->d_size) अणु
			pr_err("FAILED patching index %lu out of bounds %lu\n",
				idx, data->d_size);
			वापस -1;
		पूर्ण

		idx = idx / माप(पूर्णांक);
		ptr[idx] = id->id;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __symbols_patch(काष्ठा object *obj, काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *next;
	काष्ठा btf_id *id;

	next = rb_first(root);
	जबतक (next) अणु
		id = rb_entry(next, काष्ठा btf_id, rb_node);

		अगर (id_patch(obj, id))
			वापस -1;

		next = rb_next(next);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cmp_id(स्थिर व्योम *pa, स्थिर व्योम *pb)
अणु
	स्थिर पूर्णांक *a = pa, *b = pb;

	वापस *a - *b;
पूर्ण

अटल पूर्णांक sets_patch(काष्ठा object *obj)
अणु
	Elf_Data *data = obj->efile.idlist;
	पूर्णांक *ptr = data->d_buf;
	काष्ठा rb_node *next;

	next = rb_first(&obj->sets);
	जबतक (next) अणु
		अचिन्हित दीर्घ addr, idx;
		काष्ठा btf_id *id;
		पूर्णांक *base;
		पूर्णांक cnt;

		id   = rb_entry(next, काष्ठा btf_id, rb_node);
		addr = id->addr[0];
		idx  = addr - obj->efile.idlist_addr;

		/* sets are unique */
		अगर (id->addr_cnt != 1) अणु
			pr_err("FAILED malformed data for set '%s'\n",
				id->name);
			वापस -1;
		पूर्ण

		idx = idx / माप(पूर्णांक);
		base = &ptr[idx] + 1;
		cnt = ptr[idx];

		pr_debug("sorting  addr %5lu: cnt %6d [%s]\n",
			 (idx + 1) * माप(पूर्णांक), cnt, id->name);

		क्विक(base, cnt, माप(पूर्णांक), cmp_id);

		next = rb_next(next);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक symbols_patch(काष्ठा object *obj)
अणु
	पूर्णांक err;

	अगर (__symbols_patch(obj, &obj->काष्ठाs)  ||
	    __symbols_patch(obj, &obj->जोड़s)   ||
	    __symbols_patch(obj, &obj->प्रकारs) ||
	    __symbols_patch(obj, &obj->funcs)    ||
	    __symbols_patch(obj, &obj->sets))
		वापस -1;

	अगर (sets_patch(obj))
		वापस -1;

	elf_flagdata(obj->efile.idlist, ELF_C_SET, ELF_F_सूचीTY);

	err = elf_update(obj->efile.elf, ELF_C_WRITE);
	अगर (err < 0) अणु
		pr_err("FAILED elf_update(WRITE): %s\n",
			elf_errmsg(-1));
	पूर्ण

	pr_debug("update %s for %s\n",
		 err >= 0 ? "ok" : "failed", obj->path);
	वापस err < 0 ? -1 : 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर resolve_btfids_usage[] = अणु
	"resolve_btfids [<options>] <ELF object>",
	शून्य
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	bool no_fail = false;
	काष्ठा object obj = अणु
		.efile = अणु
			.idlist_shndx  = -1,
			.symbols_shndx = -1,
		पूर्ण,
		.काष्ठाs  = RB_ROOT,
		.जोड़s   = RB_ROOT,
		.प्रकारs = RB_ROOT,
		.funcs    = RB_ROOT,
		.sets     = RB_ROOT,
	पूर्ण;
	काष्ठा option btfid_options[] = अणु
		OPT_INCR('v', "verbose", &verbose,
			 "be more verbose (show errors, etc)"),
		OPT_STRING(0, "btf", &obj.btf, "BTF data",
			   "BTF data"),
		OPT_BOOLEAN(0, "no-fail", &no_fail,
			   "do not fail if " BTF_IDS_SECTION " section is not found"),
		OPT_END()
	पूर्ण;
	पूर्णांक err = -1;

	argc = parse_options(argc, argv, btfid_options, resolve_btfids_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (argc != 1)
		usage_with_options(resolve_btfids_usage, btfid_options);

	obj.path = argv[0];

	अगर (elf_collect(&obj))
		जाओ out;

	/*
	 * We did not find .BTF_ids section or symbols section,
	 * nothing to करो..
	 */
	अगर (obj.efile.idlist_shndx == -1 ||
	    obj.efile.symbols_shndx == -1) अणु
		अगर (no_fail)
			वापस 0;
		pr_err("FAILED to find needed sections\n");
		वापस -1;
	पूर्ण

	अगर (symbols_collect(&obj))
		जाओ out;

	अगर (symbols_resolve(&obj))
		जाओ out;

	अगर (symbols_patch(&obj))
		जाओ out;

	err = 0;
out:
	अगर (obj.efile.elf)
		elf_end(obj.efile.elf);
	बंद(obj.efile.fd);
	वापस err;
पूर्ण
