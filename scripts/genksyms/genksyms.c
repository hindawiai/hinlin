<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Generate kernel symbol version hashes.
   Copyright 1996, 1997 Linux International.

   New implementation contributed by Riअक्षरd Henderson <rth@tamu.edu>
   Based on original work by Bjorn Ekwall <bj0rn@blox.se>

   This file was part of the Linux modutils 2.4.22: moved back पूर्णांकo the
   kernel sources by Rusty Russell/Kai Germaschewski.

 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <मानकतर्क.स>
#अगर_घोषित __GNU_LIBRARY__
#समावेश <getopt.h>
#पूर्ण_अगर				/* __GNU_LIBRARY__ */

#समावेश "genksyms.h"
/*----------------------------------------------------------------------*/

#घोषणा HASH_BUCKETS  4096

अटल काष्ठा symbol *symtab[HASH_BUCKETS];
अटल खाता *debugfile;

पूर्णांक cur_line = 1;
अक्षर *cur_filename;
पूर्णांक in_source_file;

अटल पूर्णांक flag_debug, flag_dump_defs, flag_reference, flag_dump_types,
	   flag_preserve, flag_warnings, flag_rel_crcs;

अटल पूर्णांक errors;
अटल पूर्णांक nsyms;

अटल काष्ठा symbol *expansion_trail;
अटल काष्ठा symbol *visited_symbols;

अटल स्थिर काष्ठा अणु
	पूर्णांक n;
	स्थिर अक्षर *name;
पूर्ण symbol_types[] = अणु
	[SYM_NORMAL]     = अणु 0, शून्यपूर्ण,
	[SYM_TYPEDEF]    = अणु't', "typedef"पूर्ण,
	[SYM_ENUM]       = अणु'e', "enum"पूर्ण,
	[SYM_STRUCT]     = अणु's', "struct"पूर्ण,
	[SYM_UNION]      = अणु'u', "union"पूर्ण,
	[SYM_ENUM_CONST] = अणु'E', "enum constant"पूर्ण,
पूर्ण;

अटल पूर्णांक equal_list(काष्ठा string_list *a, काष्ठा string_list *b);
अटल व्योम prपूर्णांक_list(खाता * f, काष्ठा string_list *list);
अटल काष्ठा string_list *concat_list(काष्ठा string_list *start, ...);
अटल काष्ठा string_list *mk_node(स्थिर अक्षर *string);
अटल व्योम prपूर्णांक_location(व्योम);
अटल व्योम prपूर्णांक_type_name(क्रमागत symbol_type type, स्थिर अक्षर *name);

/*----------------------------------------------------------------------*/

अटल स्थिर अचिन्हित पूर्णांक crctab32[] = अणु
	0x00000000U, 0x77073096U, 0xee0e612cU, 0x990951baU, 0x076dc419U,
	0x706af48fU, 0xe963a535U, 0x9e6495a3U, 0x0edb8832U, 0x79dcb8a4U,
	0xe0d5e91eU, 0x97d2d988U, 0x09b64c2bU, 0x7eb17cbdU, 0xe7b82d07U,
	0x90bf1d91U, 0x1db71064U, 0x6ab020f2U, 0xf3b97148U, 0x84be41deU,
	0x1adad47dU, 0x6ddde4ebU, 0xf4d4b551U, 0x83d385c7U, 0x136c9856U,
	0x646ba8c0U, 0xfd62f97aU, 0x8a65c9ecU, 0x14015c4fU, 0x63066cd9U,
	0xfa0f3d63U, 0x8d080df5U, 0x3b6e20c8U, 0x4c69105eU, 0xd56041e4U,
	0xa2677172U, 0x3c03e4d1U, 0x4b04d447U, 0xd20d85fdU, 0xa50ab56bU,
	0x35b5a8faU, 0x42b2986cU, 0xdbbbc9d6U, 0xacbcf940U, 0x32d86ce3U,
	0x45df5c75U, 0xdcd60dcfU, 0xabd13d59U, 0x26d930acU, 0x51de003aU,
	0xc8d75180U, 0xbfd06116U, 0x21b4f4b5U, 0x56b3c423U, 0xcfba9599U,
	0xb8bda50fU, 0x2802b89eU, 0x5f058808U, 0xc60cd9b2U, 0xb10be924U,
	0x2f6f7c87U, 0x58684c11U, 0xc1611dabU, 0xb6662d3dU, 0x76dc4190U,
	0x01db7106U, 0x98d220bcU, 0xefd5102aU, 0x71b18589U, 0x06b6b51fU,
	0x9fbfe4a5U, 0xe8b8d433U, 0x7807c9a2U, 0x0f00f934U, 0x9609a88eU,
	0xe10e9818U, 0x7f6a0dbbU, 0x086d3d2dU, 0x91646c97U, 0xe6635c01U,
	0x6b6b51f4U, 0x1c6c6162U, 0x856530d8U, 0xf262004eU, 0x6c0695edU,
	0x1b01a57bU, 0x8208f4c1U, 0xf50fc457U, 0x65b0d9c6U, 0x12b7e950U,
	0x8bbeb8eaU, 0xfcb9887cU, 0x62dd1ddfU, 0x15da2d49U, 0x8cd37cf3U,
	0xfbd44c65U, 0x4db26158U, 0x3ab551ceU, 0xa3bc0074U, 0xd4bb30e2U,
	0x4adfa541U, 0x3dd895d7U, 0xa4d1c46dU, 0xd3d6f4fbU, 0x4369e96aU,
	0x346ed9fcU, 0xad678846U, 0xda60b8d0U, 0x44042d73U, 0x33031de5U,
	0xaa0a4c5fU, 0xdd0d7cc9U, 0x5005713cU, 0x270241aaU, 0xbe0b1010U,
	0xc90c2086U, 0x5768b525U, 0x206f85b3U, 0xb966d409U, 0xce61e49fU,
	0x5edef90eU, 0x29d9c998U, 0xb0d09822U, 0xc7d7a8b4U, 0x59b33d17U,
	0x2eb40d81U, 0xb7bd5c3bU, 0xc0ba6cadU, 0xedb88320U, 0x9abfb3b6U,
	0x03b6e20cU, 0x74b1d29aU, 0xead54739U, 0x9dd277afU, 0x04db2615U,
	0x73dc1683U, 0xe3630b12U, 0x94643b84U, 0x0d6d6a3eU, 0x7a6a5aa8U,
	0xe40ecf0bU, 0x9309ff9dU, 0x0a00ae27U, 0x7d079eb1U, 0xf00f9344U,
	0x8708a3d2U, 0x1e01f268U, 0x6906c2feU, 0xf762575dU, 0x806567cbU,
	0x196c3671U, 0x6e6b06e7U, 0xfed41b76U, 0x89d32be0U, 0x10da7a5aU,
	0x67dd4accU, 0xf9b9df6fU, 0x8ebeeff9U, 0x17b7be43U, 0x60b08ed5U,
	0xd6d6a3e8U, 0xa1d1937eU, 0x38d8c2c4U, 0x4fdff252U, 0xd1bb67f1U,
	0xa6bc5767U, 0x3fb506ddU, 0x48b2364bU, 0xd80d2bdaU, 0xaf0a1b4cU,
	0x36034af6U, 0x41047a60U, 0xdf60efc3U, 0xa867df55U, 0x316e8eefU,
	0x4669be79U, 0xcb61b38cU, 0xbc66831aU, 0x256fd2a0U, 0x5268e236U,
	0xcc0c7795U, 0xbb0b4703U, 0x220216b9U, 0x5505262fU, 0xc5ba3bbeU,
	0xb2bd0b28U, 0x2bb45a92U, 0x5cb36a04U, 0xc2d7ffa7U, 0xb5d0cf31U,
	0x2cd99e8bU, 0x5bdeae1dU, 0x9b64c2b0U, 0xec63f226U, 0x756aa39cU,
	0x026d930aU, 0x9c0906a9U, 0xeb0e363fU, 0x72076785U, 0x05005713U,
	0x95bf4a82U, 0xe2b87a14U, 0x7bb12baeU, 0x0cb61b38U, 0x92d28e9bU,
	0xe5d5be0dU, 0x7cdcefb7U, 0x0bdbdf21U, 0x86d3d2d4U, 0xf1d4e242U,
	0x68ddb3f8U, 0x1fda836eU, 0x81be16cdU, 0xf6b9265bU, 0x6fb077e1U,
	0x18b74777U, 0x88085ae6U, 0xff0f6a70U, 0x66063bcaU, 0x11010b5cU,
	0x8f659effU, 0xf862ae69U, 0x616bffd3U, 0x166ccf45U, 0xa00ae278U,
	0xd70dd2eeU, 0x4e048354U, 0x3903b3c2U, 0xa7672661U, 0xd06016f7U,
	0x4969474dU, 0x3e6e77dbU, 0xaed16a4aU, 0xd9d65adcU, 0x40df0b66U,
	0x37d83bf0U, 0xa9bcae53U, 0xdebb9ec5U, 0x47b2cf7fU, 0x30b5ffe9U,
	0xbdbdf21cU, 0xcabac28aU, 0x53b39330U, 0x24b4a3a6U, 0xbad03605U,
	0xcdd70693U, 0x54de5729U, 0x23d967bfU, 0xb3667a2eU, 0xc4614ab8U,
	0x5d681b02U, 0x2a6f2b94U, 0xb40bbe37U, 0xc30c8ea1U, 0x5a05df1bU,
	0x2d02ef8dU
पूर्ण;

अटल अचिन्हित दीर्घ partial_crc32_one(अचिन्हित अक्षर c, अचिन्हित दीर्घ crc)
अणु
	वापस crctab32[(crc ^ c) & 0xff] ^ (crc >> 8);
पूर्ण

अटल अचिन्हित दीर्घ partial_crc32(स्थिर अक्षर *s, अचिन्हित दीर्घ crc)
अणु
	जबतक (*s)
		crc = partial_crc32_one(*s++, crc);
	वापस crc;
पूर्ण

अटल अचिन्हित दीर्घ crc32(स्थिर अक्षर *s)
अणु
	वापस partial_crc32(s, 0xffffffff) ^ 0xffffffff;
पूर्ण

/*----------------------------------------------------------------------*/

अटल क्रमागत symbol_type map_to_ns(क्रमागत symbol_type t)
अणु
	चयन (t) अणु
	हाल SYM_ENUM_CONST:
	हाल SYM_NORMAL:
	हाल SYM_TYPEDEF:
		वापस SYM_NORMAL;
	हाल SYM_ENUM:
	हाल SYM_STRUCT:
	हाल SYM_UNION:
		वापस SYM_STRUCT;
	पूर्ण
	वापस t;
पूर्ण

काष्ठा symbol *find_symbol(स्थिर अक्षर *name, क्रमागत symbol_type ns, पूर्णांक exact)
अणु
	अचिन्हित दीर्घ h = crc32(name) % HASH_BUCKETS;
	काष्ठा symbol *sym;

	क्रम (sym = symtab[h]; sym; sym = sym->hash_next)
		अगर (map_to_ns(sym->type) == map_to_ns(ns) &&
		    म_भेद(name, sym->name) == 0 &&
		    sym->is_declared)
			अवरोध;

	अगर (exact && sym && sym->type != ns)
		वापस शून्य;
	वापस sym;
पूर्ण

अटल पूर्णांक is_unknown_symbol(काष्ठा symbol *sym)
अणु
	काष्ठा string_list *defn;

	वापस ((sym->type == SYM_STRUCT ||
		 sym->type == SYM_UNION ||
		 sym->type == SYM_ENUM) &&
		(defn = sym->defn)  && defn->tag == SYM_NORMAL &&
			म_भेद(defn->string, "}") == 0 &&
		(defn = defn->next) && defn->tag == SYM_NORMAL &&
			म_भेद(defn->string, "UNKNOWN") == 0 &&
		(defn = defn->next) && defn->tag == SYM_NORMAL &&
			म_भेद(defn->string, "{") == 0);
पूर्ण

अटल काष्ठा symbol *__add_symbol(स्थिर अक्षर *name, क्रमागत symbol_type type,
			    काष्ठा string_list *defn, पूर्णांक is_बाह्य,
			    पूर्णांक is_reference)
अणु
	अचिन्हित दीर्घ h;
	काष्ठा symbol *sym;
	क्रमागत symbol_status status = STATUS_UNCHANGED;
	/* The parser adds symbols in the order their declaration completes,
	 * so it is safe to store the value of the previous क्रमागत स्थिरant in
	 * a अटल variable.
	 */
	अटल पूर्णांक क्रमागत_counter;
	अटल काष्ठा string_list *last_क्रमागत_expr;

	अगर (type == SYM_ENUM_CONST) अणु
		अगर (defn) अणु
			मुक्त_list(last_क्रमागत_expr, शून्य);
			last_क्रमागत_expr = copy_list_range(defn, शून्य);
			क्रमागत_counter = 1;
		पूर्ण अन्यथा अणु
			काष्ठा string_list *expr;
			अक्षर buf[20];

			snम_लिखो(buf, माप(buf), "%d", क्रमागत_counter++);
			अगर (last_क्रमागत_expr) अणु
				expr = copy_list_range(last_क्रमागत_expr, शून्य);
				defn = concat_list(mk_node("("),
						   expr,
						   mk_node(")"),
						   mk_node("+"),
						   mk_node(buf), शून्य);
			पूर्ण अन्यथा अणु
				defn = mk_node(buf);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (type == SYM_ENUM) अणु
		मुक्त_list(last_क्रमागत_expr, शून्य);
		last_क्रमागत_expr = शून्य;
		क्रमागत_counter = 0;
		अगर (!name)
			/* Anonymous क्रमागत definition, nothing more to करो */
			वापस शून्य;
	पूर्ण

	h = crc32(name) % HASH_BUCKETS;
	क्रम (sym = symtab[h]; sym; sym = sym->hash_next) अणु
		अगर (map_to_ns(sym->type) == map_to_ns(type) &&
		    म_भेद(name, sym->name) == 0) अणु
			अगर (is_reference)
				/* fall through */ ;
			अन्यथा अगर (sym->type == type &&
				 equal_list(sym->defn, defn)) अणु
				अगर (!sym->is_declared && sym->is_override) अणु
					prपूर्णांक_location();
					prपूर्णांक_type_name(type, name);
					ख_लिखो(मानक_त्रुटि, " modversion is "
						"unchanged\n");
				पूर्ण
				sym->is_declared = 1;
				वापस sym;
			पूर्ण अन्यथा अगर (!sym->is_declared) अणु
				अगर (sym->is_override && flag_preserve) अणु
					prपूर्णांक_location();
					ख_लिखो(मानक_त्रुटि, "ignoring ");
					prपूर्णांक_type_name(type, name);
					ख_लिखो(मानक_त्रुटि, " modversion change\n");
					sym->is_declared = 1;
					वापस sym;
				पूर्ण अन्यथा अणु
					status = is_unknown_symbol(sym) ?
						STATUS_DEFINED : STATUS_MODIFIED;
				पूर्ण
			पूर्ण अन्यथा अणु
				error_with_pos("redefinition of %s", name);
				वापस sym;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (sym) अणु
		काष्ठा symbol **psym;

		क्रम (psym = &symtab[h]; *psym; psym = &(*psym)->hash_next) अणु
			अगर (*psym == sym) अणु
				*psym = sym->hash_next;
				अवरोध;
			पूर्ण
		पूर्ण
		--nsyms;
	पूर्ण

	sym = xदो_स्मृति(माप(*sym));
	sym->name = name;
	sym->type = type;
	sym->defn = defn;
	sym->expansion_trail = शून्य;
	sym->visited = शून्य;
	sym->is_बाह्य = is_बाह्य;

	sym->hash_next = symtab[h];
	symtab[h] = sym;

	sym->is_declared = !is_reference;
	sym->status = status;
	sym->is_override = 0;

	अगर (flag_debug) अणु
		अगर (symbol_types[type].name)
			ख_लिखो(debugfile, "Defn for %s %s == <",
				symbol_types[type].name, name);
		अन्यथा
			ख_लिखो(debugfile, "Defn for type%d %s == <",
				type, name);
		अगर (is_बाह्य)
			ख_माला_दो("extern ", debugfile);
		prपूर्णांक_list(debugfile, defn);
		ख_माला_दो(">\n", debugfile);
	पूर्ण

	++nsyms;
	वापस sym;
पूर्ण

काष्ठा symbol *add_symbol(स्थिर अक्षर *name, क्रमागत symbol_type type,
			  काष्ठा string_list *defn, पूर्णांक is_बाह्य)
अणु
	वापस __add_symbol(name, type, defn, is_बाह्य, 0);
पूर्ण

अटल काष्ठा symbol *add_reference_symbol(स्थिर अक्षर *name, क्रमागत symbol_type type,
				    काष्ठा string_list *defn, पूर्णांक is_बाह्य)
अणु
	वापस __add_symbol(name, type, defn, is_बाह्य, 1);
पूर्ण

/*----------------------------------------------------------------------*/

व्योम मुक्त_node(काष्ठा string_list *node)
अणु
	मुक्त(node->string);
	मुक्त(node);
पूर्ण

व्योम मुक्त_list(काष्ठा string_list *s, काष्ठा string_list *e)
अणु
	जबतक (s != e) अणु
		काष्ठा string_list *next = s->next;
		मुक्त_node(s);
		s = next;
	पूर्ण
पूर्ण

अटल काष्ठा string_list *mk_node(स्थिर अक्षर *string)
अणु
	काष्ठा string_list *newnode;

	newnode = xदो_स्मृति(माप(*newnode));
	newnode->string = xstrdup(string);
	newnode->tag = SYM_NORMAL;
	newnode->next = शून्य;

	वापस newnode;
पूर्ण

अटल काष्ठा string_list *concat_list(काष्ठा string_list *start, ...)
अणु
	बहु_सूची ap;
	काष्ठा string_list *n, *n2;

	अगर (!start)
		वापस शून्य;
	क्रम (बहु_शुरू(ap, start); (n = बहु_तर्क(ap, काष्ठा string_list *));) अणु
		क्रम (n2 = n; n2->next; n2 = n2->next)
			;
		n2->next = start;
		start = n;
	पूर्ण
	बहु_पूर्ण(ap);
	वापस start;
पूर्ण

काष्ठा string_list *copy_node(काष्ठा string_list *node)
अणु
	काष्ठा string_list *newnode;

	newnode = xदो_स्मृति(माप(*newnode));
	newnode->string = xstrdup(node->string);
	newnode->tag = node->tag;

	वापस newnode;
पूर्ण

काष्ठा string_list *copy_list_range(काष्ठा string_list *start,
				    काष्ठा string_list *end)
अणु
	काष्ठा string_list *res, *n;

	अगर (start == end)
		वापस शून्य;
	n = res = copy_node(start);
	क्रम (start = start->next; start != end; start = start->next) अणु
		n->next = copy_node(start);
		n = n->next;
	पूर्ण
	n->next = शून्य;
	वापस res;
पूर्ण

अटल पूर्णांक equal_list(काष्ठा string_list *a, काष्ठा string_list *b)
अणु
	जबतक (a && b) अणु
		अगर (a->tag != b->tag || म_भेद(a->string, b->string))
			वापस 0;
		a = a->next;
		b = b->next;
	पूर्ण

	वापस !a && !b;
पूर्ण

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

अटल काष्ठा string_list *पढ़ो_node(खाता *f)
अणु
	अक्षर buffer[256];
	काष्ठा string_list node = अणु
		.string = buffer,
		.tag = SYM_NORMAL पूर्ण;
	पूर्णांक c, in_string = 0;

	जबतक ((c = ख_अक्षर_लो(f)) != खातापूर्ण) अणु
		अगर (!in_string && c == ' ') अणु
			अगर (node.string == buffer)
				जारी;
			अवरोध;
		पूर्ण अन्यथा अगर (c == '"') अणु
			in_string = !in_string;
		पूर्ण अन्यथा अगर (c == '\n') अणु
			अगर (node.string == buffer)
				वापस शून्य;
			अक्षर_वापस(c, f);
			अवरोध;
		पूर्ण
		अगर (node.string >= buffer + माप(buffer) - 1) अणु
			ख_लिखो(मानक_त्रुटि, "Token too long\n");
			निकास(1);
		पूर्ण
		*node.string++ = c;
	पूर्ण
	अगर (node.string == buffer)
		वापस शून्य;
	*node.string = 0;
	node.string = buffer;

	अगर (node.string[1] == '#') अणु
		माप_प्रकार n;

		क्रम (n = 0; n < ARRAY_SIZE(symbol_types); n++) अणु
			अगर (node.string[0] == symbol_types[n].n) अणु
				node.tag = n;
				node.string += 2;
				वापस copy_node(&node);
			पूर्ण
		पूर्ण
		ख_लिखो(मानक_त्रुटि, "Unknown type %c\n", node.string[0]);
		निकास(1);
	पूर्ण
	वापस copy_node(&node);
पूर्ण

अटल व्योम पढ़ो_reference(खाता *f)
अणु
	जबतक (!ख_पूर्ण(f)) अणु
		काष्ठा string_list *defn = शून्य;
		काष्ठा string_list *sym, *def;
		पूर्णांक is_बाह्य = 0, is_override = 0;
		काष्ठा symbol *subsym;

		sym = पढ़ो_node(f);
		अगर (sym && sym->tag == SYM_NORMAL &&
		    !म_भेद(sym->string, "override")) अणु
			is_override = 1;
			मुक्त_node(sym);
			sym = पढ़ो_node(f);
		पूर्ण
		अगर (!sym)
			जारी;
		def = पढ़ो_node(f);
		अगर (def && def->tag == SYM_NORMAL &&
		    !म_भेद(def->string, "extern")) अणु
			is_बाह्य = 1;
			मुक्त_node(def);
			def = पढ़ो_node(f);
		पूर्ण
		जबतक (def) अणु
			def->next = defn;
			defn = def;
			def = पढ़ो_node(f);
		पूर्ण
		subsym = add_reference_symbol(xstrdup(sym->string), sym->tag,
					      defn, is_बाह्य);
		subsym->is_override = is_override;
		मुक्त_node(sym);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_node(खाता * f, काष्ठा string_list *list)
अणु
	अगर (symbol_types[list->tag].n) अणु
		अ_दो(symbol_types[list->tag].n, f);
		अ_दो('#', f);
	पूर्ण
	ख_माला_दो(list->string, f);
पूर्ण

अटल व्योम prपूर्णांक_list(खाता * f, काष्ठा string_list *list)
अणु
	काष्ठा string_list **e, **b;
	काष्ठा string_list *पंचांगp, **पंचांगp2;
	पूर्णांक elem = 1;

	अगर (list == शून्य) अणु
		ख_माला_दो("(nil)", f);
		वापस;
	पूर्ण

	पंचांगp = list;
	जबतक ((पंचांगp = पंचांगp->next) != शून्य)
		elem++;

	b = alloca(elem * माप(*e));
	e = b + elem;
	पंचांगp2 = e - 1;

	(*पंचांगp2--) = list;
	जबतक ((list = list->next) != शून्य)
		*(पंचांगp2--) = list;

	जबतक (b != e) अणु
		prपूर्णांक_node(f, *b++);
		अ_दो(' ', f);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ expand_and_crc_sym(काष्ठा symbol *sym, अचिन्हित दीर्घ crc)
अणु
	काष्ठा string_list *list = sym->defn;
	काष्ठा string_list **e, **b;
	काष्ठा string_list *पंचांगp, **पंचांगp2;
	पूर्णांक elem = 1;

	अगर (!list)
		वापस crc;

	पंचांगp = list;
	जबतक ((पंचांगp = पंचांगp->next) != शून्य)
		elem++;

	b = alloca(elem * माप(*e));
	e = b + elem;
	पंचांगp2 = e - 1;

	*(पंचांगp2--) = list;
	जबतक ((list = list->next) != शून्य)
		*(पंचांगp2--) = list;

	जबतक (b != e) अणु
		काष्ठा string_list *cur;
		काष्ठा symbol *subsym;

		cur = *(b++);
		चयन (cur->tag) अणु
		हाल SYM_NORMAL:
			अगर (flag_dump_defs)
				ख_लिखो(debugfile, "%s ", cur->string);
			crc = partial_crc32(cur->string, crc);
			crc = partial_crc32_one(' ', crc);
			अवरोध;

		हाल SYM_ENUM_CONST:
		हाल SYM_TYPEDEF:
			subsym = find_symbol(cur->string, cur->tag, 0);
			/* FIXME: Bad reference files can segfault here. */
			अगर (subsym->expansion_trail) अणु
				अगर (flag_dump_defs)
					ख_लिखो(debugfile, "%s ", cur->string);
				crc = partial_crc32(cur->string, crc);
				crc = partial_crc32_one(' ', crc);
			पूर्ण अन्यथा अणु
				subsym->expansion_trail = expansion_trail;
				expansion_trail = subsym;
				crc = expand_and_crc_sym(subsym, crc);
			पूर्ण
			अवरोध;

		हाल SYM_STRUCT:
		हाल SYM_UNION:
		हाल SYM_ENUM:
			subsym = find_symbol(cur->string, cur->tag, 0);
			अगर (!subsym) अणु
				काष्ठा string_list *n;

				error_with_pos("expand undefined %s %s",
					       symbol_types[cur->tag].name,
					       cur->string);
				n = concat_list(mk_node
						(symbol_types[cur->tag].name),
						mk_node(cur->string),
						mk_node("{"),
						mk_node("UNKNOWN"),
						mk_node("}"), शून्य);
				subsym =
				    add_symbol(cur->string, cur->tag, n, 0);
			पूर्ण
			अगर (subsym->expansion_trail) अणु
				अगर (flag_dump_defs) अणु
					ख_लिखो(debugfile, "%s %s ",
						symbol_types[cur->tag].name,
						cur->string);
				पूर्ण

				crc = partial_crc32(symbol_types[cur->tag].name,
						    crc);
				crc = partial_crc32_one(' ', crc);
				crc = partial_crc32(cur->string, crc);
				crc = partial_crc32_one(' ', crc);
			पूर्ण अन्यथा अणु
				subsym->expansion_trail = expansion_trail;
				expansion_trail = subsym;
				crc = expand_and_crc_sym(subsym, crc);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अणु
		अटल काष्ठा symbol **end = &visited_symbols;

		अगर (!sym->visited) अणु
			*end = sym;
			end = &sym->visited;
			sym->visited = (काष्ठा symbol *)-1L;
		पूर्ण
	पूर्ण

	वापस crc;
पूर्ण

व्योम export_symbol(स्थिर अक्षर *name)
अणु
	काष्ठा symbol *sym;

	sym = find_symbol(name, SYM_NORMAL, 0);
	अगर (!sym)
		error_with_pos("export undefined symbol %s", name);
	अन्यथा अणु
		अचिन्हित दीर्घ crc;
		पूर्णांक has_changed = 0;

		अगर (flag_dump_defs)
			ख_लिखो(debugfile, "Export %s == <", name);

		expansion_trail = (काष्ठा symbol *)-1L;

		sym->expansion_trail = expansion_trail;
		expansion_trail = sym;
		crc = expand_and_crc_sym(sym, 0xffffffff) ^ 0xffffffff;

		sym = expansion_trail;
		जबतक (sym != (काष्ठा symbol *)-1L) अणु
			काष्ठा symbol *n = sym->expansion_trail;

			अगर (sym->status != STATUS_UNCHANGED) अणु
				अगर (!has_changed) अणु
					prपूर्णांक_location();
					ख_लिखो(मानक_त्रुटि, "%s: %s: modversion "
						"changed because of changes "
						"in ", flag_preserve ? "error" :
						       "warning", name);
				पूर्ण अन्यथा
					ख_लिखो(मानक_त्रुटि, ", ");
				prपूर्णांक_type_name(sym->type, sym->name);
				अगर (sym->status == STATUS_DEFINED)
					ख_लिखो(मानक_त्रुटि, " (became defined)");
				has_changed = 1;
				अगर (flag_preserve)
					errors++;
			पूर्ण
			sym->expansion_trail = 0;
			sym = n;
		पूर्ण
		अगर (has_changed)
			ख_लिखो(मानक_त्रुटि, "\n");

		अगर (flag_dump_defs)
			ख_माला_दो(">\n", debugfile);

		/* Used as a linker script. */
		म_लिखो(!flag_rel_crcs ? "__crc_%s = 0x%08lx;\n" :
		       "SECTIONS { .rodata : ALIGN(4) { "
		       "__crc_%s = .; LONG(0x%08lx); } }\n",
		       name, crc);
	पूर्ण
पूर्ण

/*----------------------------------------------------------------------*/

अटल व्योम prपूर्णांक_location(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "%s:%d: ", cur_filename ? : "<stdin>", cur_line);
पूर्ण

अटल व्योम prपूर्णांक_type_name(क्रमागत symbol_type type, स्थिर अक्षर *name)
अणु
	अगर (symbol_types[type].name)
		ख_लिखो(मानक_त्रुटि, "%s %s", symbol_types[type].name, name);
	अन्यथा
		ख_लिखो(मानक_त्रुटि, "%s", name);
पूर्ण

व्योम error_with_pos(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (flag_warnings) अणु
		prपूर्णांक_location();

		बहु_शुरू(args, fmt);
		भख_लिखो(मानक_त्रुटि, fmt, args);
		बहु_पूर्ण(args);
		अ_दो('\n', मानक_त्रुटि);

		errors++;
	पूर्ण
पूर्ण

अटल व्योम genksyms_usage(व्योम)
अणु
	ख_माला_दो("Usage:\n" "genksyms [-adDTwqhVR] > /path/to/.tmp_obj.ver\n" "\n"
#अगर_घोषित __GNU_LIBRARY__
	      "  -s, --symbol-prefix   Select symbol prefix\n"
	      "  -d, --debug           Increment the debug level (repeatable)\n"
	      "  -D, --dump            Dump expanded symbol defs (for debugging only)\n"
	      "  -r, --reference file  Read reference symbols from a file\n"
	      "  -T, --dump-types file Dump expanded types into file\n"
	      "  -p, --preserve        Preserve reference modversions or fail\n"
	      "  -w, --warnings        Enable warnings\n"
	      "  -q, --quiet           Disable warnings (default)\n"
	      "  -h, --help            Print this message\n"
	      "  -V, --version         Print the release version\n"
	      "  -R, --relative-crc    Emit section relative symbol CRCs\n"
#अन्यथा				/* __GNU_LIBRARY__ */
	      "  -s                    Select symbol prefix\n"
	      "  -d                    Increment the debug level (repeatable)\n"
	      "  -D                    Dump expanded symbol defs (for debugging only)\n"
	      "  -r file               Read reference symbols from a file\n"
	      "  -T file               Dump expanded types into file\n"
	      "  -p                    Preserve reference modversions or fail\n"
	      "  -w                    Enable warnings\n"
	      "  -q                    Disable warnings (default)\n"
	      "  -h                    Print this message\n"
	      "  -V                    Print the release version\n"
	      "  -R                    Emit section relative symbol CRCs\n"
#पूर्ण_अगर				/* __GNU_LIBRARY__ */
	      , मानक_त्रुटि);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	खाता *dumpfile = शून्य, *ref_file = शून्य;
	पूर्णांक o;

#अगर_घोषित __GNU_LIBRARY__
	काष्ठा option दीर्घ_opts[] = अणु
		अणु"debug", 0, 0, 'd'पूर्ण,
		अणु"warnings", 0, 0, 'w'पूर्ण,
		अणु"quiet", 0, 0, 'q'पूर्ण,
		अणु"dump", 0, 0, 'D'पूर्ण,
		अणु"reference", 1, 0, 'r'पूर्ण,
		अणु"dump-types", 1, 0, 'T'पूर्ण,
		अणु"preserve", 0, 0, 'p'पूर्ण,
		अणु"version", 0, 0, 'V'पूर्ण,
		अणु"help", 0, 0, 'h'पूर्ण,
		अणु"relative-crc", 0, 0, 'R'पूर्ण,
		अणु0, 0, 0, 0पूर्ण
	पूर्ण;

	जबतक ((o = getopt_दीर्घ(argc, argv, "s:dwqVDr:T:phR",
				&दीर्घ_opts[0], शून्य)) != खातापूर्ण)
#अन्यथा				/* __GNU_LIBRARY__ */
	जबतक ((o = getopt(argc, argv, "s:dwqVDr:T:phR")) != खातापूर्ण)
#पूर्ण_अगर				/* __GNU_LIBRARY__ */
		चयन (o) अणु
		हाल 'd':
			flag_debug++;
			अवरोध;
		हाल 'w':
			flag_warnings = 1;
			अवरोध;
		हाल 'q':
			flag_warnings = 0;
			अवरोध;
		हाल 'V':
			ख_माला_दो("genksyms version 2.5.60\n", मानक_त्रुटि);
			अवरोध;
		हाल 'D':
			flag_dump_defs = 1;
			अवरोध;
		हाल 'r':
			flag_reference = 1;
			ref_file = ख_खोलो(optarg, "r");
			अगर (!ref_file) अणु
				लिखो_त्रुटि(optarg);
				वापस 1;
			पूर्ण
			अवरोध;
		हाल 'T':
			flag_dump_types = 1;
			dumpfile = ख_खोलो(optarg, "w");
			अगर (!dumpfile) अणु
				लिखो_त्रुटि(optarg);
				वापस 1;
			पूर्ण
			अवरोध;
		हाल 'p':
			flag_preserve = 1;
			अवरोध;
		हाल 'h':
			genksyms_usage();
			वापस 0;
		हाल 'R':
			flag_rel_crcs = 1;
			अवरोध;
		शेष:
			genksyms_usage();
			वापस 1;
		पूर्ण
	अणु
		बाह्य पूर्णांक yydebug;
		बाह्य पूर्णांक yy_flex_debug;

		yydebug = (flag_debug > 1);
		yy_flex_debug = (flag_debug > 2);

		debugfile = मानक_त्रुटि;
		/* setlinebuf(debugfile); */
	पूर्ण

	अगर (flag_reference) अणु
		पढ़ो_reference(ref_file);
		ख_बंद(ref_file);
	पूर्ण

	yyparse();

	अगर (flag_dump_types && visited_symbols) अणु
		जबतक (visited_symbols != (काष्ठा symbol *)-1L) अणु
			काष्ठा symbol *sym = visited_symbols;

			अगर (sym->is_override)
				ख_माला_दो("override ", dumpfile);
			अगर (symbol_types[sym->type].n) अणु
				अ_दो(symbol_types[sym->type].n, dumpfile);
				अ_दो('#', dumpfile);
			पूर्ण
			ख_माला_दो(sym->name, dumpfile);
			अ_दो(' ', dumpfile);
			अगर (sym->is_बाह्य)
				ख_माला_दो("extern ", dumpfile);
			prपूर्णांक_list(dumpfile, sym->defn);
			अ_दो('\n', dumpfile);

			visited_symbols = sym->visited;
			sym->visited = शून्य;
		पूर्ण
	पूर्ण

	अगर (flag_debug) अणु
		ख_लिखो(debugfile, "Hash table occupancy %d/%d = %g\n",
			nsyms, HASH_BUCKETS,
			(द्विगुन)nsyms / (द्विगुन)HASH_BUCKETS);
	पूर्ण

	अगर (dumpfile)
		ख_बंद(dumpfile);

	वापस errors != 0;
पूर्ण
