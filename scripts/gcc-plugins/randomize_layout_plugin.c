<शैली गुरु>
/*
 * Copyright 2014-2016 by Open Source Security, Inc., Brad Spengler <spender@grsecurity.net>
 *                   and PaX Team <pageexec@मुक्तmail.hu>
 * Licensed under the GPL v2
 *
 * Note: the choice of the license means that the compilation process is
 *       NOT 'eligible' as defined by gcc's library exception to the GPL v3,
 *       but क्रम the kernel it करोesn't matter since it doesn't link against
 *       any of the gcc libraries
 *
 * Usage:
 * $ # क्रम 4.5/4.6/C based 4.7
 * $ gcc -I`gcc -prपूर्णांक-file-name=plugin`/include -I`gcc -prपूर्णांक-file-name=plugin`/include/c-family -fPIC -shared -O2 -o अक्रमomize_layout_plugin.so अक्रमomize_layout_plugin.c
 * $ # क्रम C++ based 4.7/4.8+
 * $ g++ -I`g++ -prपूर्णांक-file-name=plugin`/include -I`g++ -prपूर्णांक-file-name=plugin`/include/c-family -fPIC -shared -O2 -o अक्रमomize_layout_plugin.so अक्रमomize_layout_plugin.c
 * $ gcc -fplugin=./अक्रमomize_layout_plugin.so test.c -O2
 */

#समावेश "gcc-common.h"
#समावेश "randomize_layout_seed.h"

#अगर BUILDING_GCC_MAJOR < 4 || (BUILDING_GCC_MAJOR == 4 && BUILDING_GCC_MINOR < 7)
#त्रुटि "The RANDSTRUCT plugin requires GCC 4.7 or newer."
#पूर्ण_अगर

#घोषणा ORIG_TYPE_NAME(node) \
	(TYPE_NAME(TYPE_MAIN_VARIANT(node)) != शून्य_TREE ? ((स्थिर अचिन्हित अक्षर *)IDENTIFIER_POINTER(TYPE_NAME(TYPE_MAIN_VARIANT(node)))) : (स्थिर अचिन्हित अक्षर *)"anonymous")

#घोषणा INFORM(loc, msg, ...)	inक्रमm(loc, "randstruct: " msg, ##__VA_ARGS__)
#घोषणा MISMATCH(loc, how, ...)	INFORM(loc, "casting between randomized structure pointer types (" how "): %qT and %qT\n", __VA_ARGS__)

__visible पूर्णांक plugin_is_GPL_compatible;

अटल पूर्णांक perक्रमmance_mode;

अटल काष्ठा plugin_info अक्रमomize_layout_plugin_info = अणु
	.version	= "201402201816vanilla",
	.help		= "disable\t\t\tdo not activate plugin\n"
			  "performance-mode\tenable cacheline-aware layout randomization\n"
पूर्ण;

काष्ठा whitelist_entry अणु
	स्थिर अक्षर *pathname;
	स्थिर अक्षर *lhs;
	स्थिर अक्षर *rhs;
पूर्ण;

अटल स्थिर काष्ठा whitelist_entry whitelist[] = अणु
	/* NIU overloads mapping with page काष्ठा */
	अणु "drivers/net/ethernet/sun/niu.c", "page", "address_space" पूर्ण,
	/* unix_skb_parms via UNIXCB() buffer */
	अणु "net/unix/af_unix.c", "unix_skb_parms", "char" पूर्ण,
	/* big_key payload.data काष्ठा splashing */
	अणु "security/keys/big_key.c", "path", "void *" पूर्ण,
	/* walk काष्ठा security_hook_heads as an array of काष्ठा hlist_head */
	अणु "security/security.c", "hlist_head", "security_hook_heads" पूर्ण,
	अणु पूर्ण
पूर्ण;

/* from old Linux dcache.h */
अटल अंतरभूत अचिन्हित दीर्घ
partial_name_hash(अचिन्हित दीर्घ c, अचिन्हित दीर्घ prevhash)
अणु
	वापस (prevhash + (c << 4) + (c >> 4)) * 11;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक
name_hash(स्थिर अचिन्हित अक्षर *name)
अणु
	अचिन्हित दीर्घ hash = 0;
	अचिन्हित पूर्णांक len = म_माप((स्थिर अक्षर *)name);
	जबतक (len--)
		hash = partial_name_hash(*name++, hash);
	वापस (अचिन्हित पूर्णांक)hash;
पूर्ण

अटल tree handle_अक्रमomize_layout_attr(tree *node, tree name, tree args, पूर्णांक flags, bool *no_add_attrs)
अणु
	tree type;

	*no_add_attrs = true;
	अगर (TREE_CODE(*node) == FUNCTION_DECL) अणु
		error("%qE attribute does not apply to functions (%qF)", name, *node);
		वापस शून्य_TREE;
	पूर्ण

	अगर (TREE_CODE(*node) == PARM_DECL) अणु
		error("%qE attribute does not apply to function parameters (%qD)", name, *node);
		वापस शून्य_TREE;
	पूर्ण

	अगर (TREE_CODE(*node) == VAR_DECL) अणु
		error("%qE attribute does not apply to variables (%qD)", name, *node);
		वापस शून्य_TREE;
	पूर्ण

	अगर (TYPE_P(*node)) अणु
		type = *node;
	पूर्ण अन्यथा अणु
		gcc_निश्चित(TREE_CODE(*node) == TYPE_DECL);
		type = TREE_TYPE(*node);
	पूर्ण

	अगर (TREE_CODE(type) != RECORD_TYPE) अणु
		error("%qE attribute used on %qT applies to struct types only", name, type);
		वापस शून्य_TREE;
	पूर्ण

	अगर (lookup_attribute(IDENTIFIER_POINTER(name), TYPE_ATTRIBUTES(type))) अणु
		error("%qE attribute is already applied to the type %qT", name, type);
		वापस शून्य_TREE;
	पूर्ण

	*no_add_attrs = false;

	वापस शून्य_TREE;
पूर्ण

/* set on complete types that we करोn't need to inspect further at all */
अटल tree handle_अक्रमomize_considered_attr(tree *node, tree name, tree args, पूर्णांक flags, bool *no_add_attrs)
अणु
	*no_add_attrs = false;
	वापस शून्य_TREE;
पूर्ण

/*
 * set on types that we've perक्रमmed a shuffle on, to prevent re-shuffling
 * this करोes not preclude us from inspecting its fields क्रम potential shuffles
 */
अटल tree handle_अक्रमomize_perक्रमmed_attr(tree *node, tree name, tree args, पूर्णांक flags, bool *no_add_attrs)
अणु
	*no_add_attrs = false;
	वापस शून्य_TREE;
पूर्ण

/*
 * 64bit variant of Bob Jenkins' खुला करोमुख्य PRNG
 * 256 bits of पूर्णांकernal state
 */

प्रकार अचिन्हित दीर्घ दीर्घ u64;

प्रकार काष्ठा ranctx अणु u64 a; u64 b; u64 c; u64 d; पूर्ण ranctx;

#घोषणा rot(x,k) (((x)<<(k))|((x)>>(64-(k))))
अटल u64 ranval(ranctx *x) अणु
	u64 e = x->a - rot(x->b, 7);
	x->a = x->b ^ rot(x->c, 13);
	x->b = x->c + rot(x->d, 37);
	x->c = x->d + e;
	x->d = e + x->a;
	वापस x->d;
पूर्ण

अटल व्योम raninit(ranctx *x, u64 *seed) अणु
	पूर्णांक i;

	x->a = seed[0];
	x->b = seed[1];
	x->c = seed[2];
	x->d = seed[3];

	क्रम (i=0; i < 30; ++i)
		(व्योम)ranval(x);
पूर्ण

अटल u64 shuffle_seed[4];

काष्ठा partition_group अणु
	tree tree_start;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ length;
पूर्ण;

अटल व्योम partition_काष्ठा(tree *fields, अचिन्हित दीर्घ length, काष्ठा partition_group *size_groups, अचिन्हित दीर्घ *num_groups)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ accum_size = 0;
	अचिन्हित दीर्घ accum_length = 0;
	अचिन्हित दीर्घ group_idx = 0;

	gcc_निश्चित(length < पूर्णांक_उच्च);

	स_रखो(size_groups, 0, माप(काष्ठा partition_group) * length);

	क्रम (i = 0; i < length; i++) अणु
		अगर (size_groups[group_idx].tree_start == शून्य_TREE) अणु
			size_groups[group_idx].tree_start = fields[i];
			size_groups[group_idx].start = i;
			accum_length = 0;
			accum_size = 0;
		पूर्ण
		accum_size += (अचिन्हित दीर्घ)पूर्णांक_size_in_bytes(TREE_TYPE(fields[i]));
		accum_length++;
		अगर (accum_size >= 64) अणु
			size_groups[group_idx].length = accum_length;
			accum_length = 0;
			group_idx++;
		पूर्ण
	पूर्ण

	अगर (size_groups[group_idx].tree_start != शून्य_TREE &&
	    !size_groups[group_idx].length) अणु
		size_groups[group_idx].length = accum_length;
		group_idx++;
	पूर्ण

	*num_groups = group_idx;
पूर्ण

अटल व्योम perक्रमmance_shuffle(tree *newtree, अचिन्हित दीर्घ length, ranctx *prng_state)
अणु
	अचिन्हित दीर्घ i, x;
	काष्ठा partition_group size_group[length];
	अचिन्हित दीर्घ num_groups = 0;
	अचिन्हित दीर्घ अक्रमnum;

	partition_काष्ठा(newtree, length, (काष्ठा partition_group *)&size_group, &num_groups);
	क्रम (i = num_groups - 1; i > 0; i--) अणु
		काष्ठा partition_group पंचांगp;
		अक्रमnum = ranval(prng_state) % (i + 1);
		पंचांगp = size_group[i];
		size_group[i] = size_group[अक्रमnum];
		size_group[अक्रमnum] = पंचांगp;
	पूर्ण

	क्रम (x = 0; x < num_groups; x++) अणु
		क्रम (i = size_group[x].start + size_group[x].length - 1; i > size_group[x].start; i--) अणु
			tree पंचांगp;
			अगर (DECL_BIT_FIELD_TYPE(newtree[i]))
				जारी;
			अक्रमnum = ranval(prng_state) % (i + 1);
			// we could handle this हाल dअगरferently अगर desired
			अगर (DECL_BIT_FIELD_TYPE(newtree[अक्रमnum]))
				जारी;
			पंचांगp = newtree[i];
			newtree[i] = newtree[अक्रमnum];
			newtree[अक्रमnum] = पंचांगp;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम full_shuffle(tree *newtree, अचिन्हित दीर्घ length, ranctx *prng_state)
अणु
	अचिन्हित दीर्घ i, अक्रमnum;

	क्रम (i = length - 1; i > 0; i--) अणु
		tree पंचांगp;
		अक्रमnum = ranval(prng_state) % (i + 1);
		पंचांगp = newtree[i];
		newtree[i] = newtree[अक्रमnum];
		newtree[अक्रमnum] = पंचांगp;
	पूर्ण
पूर्ण

/* modern in-place Fisher-Yates shuffle */
अटल व्योम shuffle(स्थिर_tree type, tree *newtree, अचिन्हित दीर्घ length)
अणु
	अचिन्हित दीर्घ i;
	u64 seed[4];
	ranctx prng_state;
	स्थिर अचिन्हित अक्षर *काष्ठाname;

	अगर (length == 0)
		वापस;

	gcc_निश्चित(TREE_CODE(type) == RECORD_TYPE);

	काष्ठाname = ORIG_TYPE_NAME(type);

#अगर_घोषित __DEBUG_PLUGIN
	ख_लिखो(मानक_त्रुटि, "Shuffling struct %s %p\n", (स्थिर अक्षर *)काष्ठाname, type);
#अगर_घोषित __DEBUG_VERBOSE
	debug_tree((tree)type);
#पूर्ण_अगर
#पूर्ण_अगर

	क्रम (i = 0; i < 4; i++) अणु
		seed[i] = shuffle_seed[i];
		seed[i] ^= name_hash(काष्ठाname);
	पूर्ण

	raninit(&prng_state, (u64 *)&seed);

	अगर (perक्रमmance_mode)
		perक्रमmance_shuffle(newtree, length, &prng_state);
	अन्यथा
		full_shuffle(newtree, length, &prng_state);
पूर्ण

अटल bool is_flexible_array(स्थिर_tree field)
अणु
	स्थिर_tree fieldtype;
	स्थिर_tree typesize;
	स्थिर_tree elemtype;
	स्थिर_tree elemsize;

	fieldtype = TREE_TYPE(field);
	typesize = TYPE_SIZE(fieldtype);

	अगर (TREE_CODE(fieldtype) != ARRAY_TYPE)
		वापस false;

	elemtype = TREE_TYPE(fieldtype);
	elemsize = TYPE_SIZE(elemtype);

	/* size of type is represented in bits */

	अगर (typesize == शून्य_TREE && TYPE_DOMAIN(fieldtype) != शून्य_TREE &&
	    TYPE_MAX_VALUE(TYPE_DOMAIN(fieldtype)) == शून्य_TREE)
		वापस true;

	अगर (typesize != शून्य_TREE &&
	    (TREE_CONSTANT(typesize) && (!tree_to_uhwi(typesize) ||
	     tree_to_uhwi(typesize) == tree_to_uhwi(elemsize))))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक relayout_काष्ठा(tree type)
अणु
	अचिन्हित दीर्घ num_fields = (अचिन्हित दीर्घ)list_length(TYPE_FIELDS(type));
	अचिन्हित दीर्घ shuffle_length = num_fields;
	tree field;
	tree newtree[num_fields];
	अचिन्हित दीर्घ i;
	tree list;
	tree variant;
	tree मुख्य_variant;
	expanded_location xloc;
	bool has_flexarray = false;

	अगर (TYPE_FIELDS(type) == शून्य_TREE)
		वापस 0;

	अगर (num_fields < 2)
		वापस 0;

	gcc_निश्चित(TREE_CODE(type) == RECORD_TYPE);

	gcc_निश्चित(num_fields < पूर्णांक_उच्च);

	अगर (lookup_attribute("randomize_performed", TYPE_ATTRIBUTES(type)) ||
	    lookup_attribute("no_randomize_layout", TYPE_ATTRIBUTES(TYPE_MAIN_VARIANT(type))))
		वापस 0;

	/* Workaround क्रम 3rd-party VirtualBox source that we can't modअगरy ourselves */
	अगर (!म_भेद((स्थिर अक्षर *)ORIG_TYPE_NAME(type), "INTNETTRUNKFACTORY") ||
	    !म_भेद((स्थिर अक्षर *)ORIG_TYPE_NAME(type), "RAWPCIFACTORY"))
		वापस 0;

	/* throw out any काष्ठाs in uapi */
	xloc = expand_location(DECL_SOURCE_LOCATION(TYPE_FIELDS(type)));

	अगर (म_माला(xloc.file, "/uapi/"))
		error(G_("attempted to randomize userland API struct %s"), ORIG_TYPE_NAME(type));

	क्रम (field = TYPE_FIELDS(type), i = 0; field; field = TREE_CHAIN(field), i++) अणु
		gcc_निश्चित(TREE_CODE(field) == FIELD_DECL);
		newtree[i] = field;
	पूर्ण

	/*
	 * enक्रमce that we करोn't अक्रमomize the layout of the last
	 * element of a काष्ठा अगर it's a 0 or 1-length array
	 * or a proper flexible array
	 */
	अगर (is_flexible_array(newtree[num_fields - 1])) अणु
		has_flexarray = true;
		shuffle_length--;
	पूर्ण

	shuffle(type, (tree *)newtree, shuffle_length);

	/*
	 * set up a bogus anonymous काष्ठा field deचिन्हित to error out on unnamed काष्ठा initializers
	 * as gcc provides no other way to detect such code
	 */
	list = make_node(FIELD_DECL);
	TREE_CHAIN(list) = newtree[0];
	TREE_TYPE(list) = व्योम_type_node;
	DECL_SIZE(list) = bitsize_zero_node;
	DECL_NONADDRESSABLE_P(list) = 1;
	DECL_FIELD_BIT_OFFSET(list) = bitsize_zero_node;
	DECL_SIZE_UNIT(list) = size_zero_node;
	DECL_FIELD_OFFSET(list) = size_zero_node;
	DECL_CONTEXT(list) = type;
	// to satisfy the स्थिरअगरy plugin
	TREE_READONLY(list) = 1;

	क्रम (i = 0; i < num_fields - 1; i++)
		TREE_CHAIN(newtree[i]) = newtree[i+1];
	TREE_CHAIN(newtree[num_fields - 1]) = शून्य_TREE;

	मुख्य_variant = TYPE_MAIN_VARIANT(type);
	क्रम (variant = मुख्य_variant; variant; variant = TYPE_NEXT_VARIANT(variant)) अणु
		TYPE_FIELDS(variant) = list;
		TYPE_ATTRIBUTES(variant) = copy_list(TYPE_ATTRIBUTES(variant));
		TYPE_ATTRIBUTES(variant) = tree_cons(get_identअगरier("randomize_performed"), शून्य_TREE, TYPE_ATTRIBUTES(variant));
		TYPE_ATTRIBUTES(variant) = tree_cons(get_identअगरier("designated_init"), शून्य_TREE, TYPE_ATTRIBUTES(variant));
		अगर (has_flexarray)
			TYPE_ATTRIBUTES(type) = tree_cons(get_identअगरier("has_flexarray"), शून्य_TREE, TYPE_ATTRIBUTES(type));
	पूर्ण

	/*
	 * क्रमce a re-layout of the मुख्य variant
	 * the TYPE_SIZE क्रम all variants will be recomputed
	 * by finalize_type_size()
	 */
	TYPE_SIZE(मुख्य_variant) = शून्य_TREE;
	layout_type(मुख्य_variant);
	gcc_निश्चित(TYPE_SIZE(मुख्य_variant) != शून्य_TREE);

	वापस 1;
पूर्ण

/* from स्थिरअगरy plugin */
अटल स्थिर_tree get_field_type(स्थिर_tree field)
अणु
	वापस strip_array_types(TREE_TYPE(field));
पूर्ण

/* from स्थिरअगरy plugin */
अटल bool is_fptr(स्थिर_tree fieldtype)
अणु
	अगर (TREE_CODE(fieldtype) != POINTER_TYPE)
		वापस false;

	वापस TREE_CODE(TREE_TYPE(fieldtype)) == FUNCTION_TYPE;
पूर्ण

/* derived from स्थिरअगरy plugin */
अटल पूर्णांक is_pure_ops_काष्ठा(स्थिर_tree node)
अणु
	स्थिर_tree field;

	gcc_निश्चित(TREE_CODE(node) == RECORD_TYPE || TREE_CODE(node) == UNION_TYPE);

	क्रम (field = TYPE_FIELDS(node); field; field = TREE_CHAIN(field)) अणु
		स्थिर_tree fieldtype = get_field_type(field);
		क्रमागत tree_code code = TREE_CODE(fieldtype);

		अगर (node == fieldtype)
			जारी;

		अगर (code == RECORD_TYPE || code == UNION_TYPE) अणु
			अगर (!is_pure_ops_काष्ठा(fieldtype))
				वापस 0;
			जारी;
		पूर्ण

		अगर (!is_fptr(fieldtype))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम अक्रमomize_type(tree type)
अणु
	tree variant;

	gcc_निश्चित(TREE_CODE(type) == RECORD_TYPE);

	अगर (lookup_attribute("randomize_considered", TYPE_ATTRIBUTES(type)))
		वापस;

	अगर (lookup_attribute("randomize_layout", TYPE_ATTRIBUTES(TYPE_MAIN_VARIANT(type))) || is_pure_ops_काष्ठा(type))
		relayout_काष्ठा(type);

	क्रम (variant = TYPE_MAIN_VARIANT(type); variant; variant = TYPE_NEXT_VARIANT(variant)) अणु
		TYPE_ATTRIBUTES(type) = copy_list(TYPE_ATTRIBUTES(type));
		TYPE_ATTRIBUTES(type) = tree_cons(get_identअगरier("randomize_considered"), शून्य_TREE, TYPE_ATTRIBUTES(type));
	पूर्ण
#अगर_घोषित __DEBUG_PLUGIN
	ख_लिखो(मानक_त्रुटि, "Marking randomize_considered on struct %s\n", ORIG_TYPE_NAME(type));
#अगर_घोषित __DEBUG_VERBOSE
	debug_tree(type);
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

अटल व्योम update_decl_size(tree decl)
अणु
	tree lastval, lastidx, field, init, type, flexsize;
	अचिन्हित HOST_WIDE_INT len;

	type = TREE_TYPE(decl);

	अगर (!lookup_attribute("has_flexarray", TYPE_ATTRIBUTES(type)))
		वापस;

	init = DECL_INITIAL(decl);
	अगर (init == शून्य_TREE || init == error_mark_node)
		वापस;

	अगर (TREE_CODE(init) != CONSTRUCTOR)
		वापस;

	len = CONSTRUCTOR_NELTS(init);
        अगर (!len)
		वापस;

	lastval = CONSTRUCTOR_ELT(init, CONSTRUCTOR_NELTS(init) - 1)->value;
	lastidx = CONSTRUCTOR_ELT(init, CONSTRUCTOR_NELTS(init) - 1)->index;

	क्रम (field = TYPE_FIELDS(TREE_TYPE(decl)); TREE_CHAIN(field); field = TREE_CHAIN(field))
		;

	अगर (lastidx != field)
		वापस;

	अगर (TREE_CODE(lastval) != STRING_CST) अणु
		error("Only string constants are supported as initializers "
		      "for randomized structures with flexible arrays");
		वापस;
	पूर्ण

	flexsize = bitsize_पूर्णांक(TREE_STRING_LENGTH(lastval) *
		tree_to_uhwi(TYPE_SIZE(TREE_TYPE(TREE_TYPE(lastval)))));

	DECL_SIZE(decl) = size_binop(PLUS_EXPR, TYPE_SIZE(type), flexsize);

	वापस;
पूर्ण


अटल व्योम अक्रमomize_layout_finish_decl(व्योम *event_data, व्योम *data)
अणु
	tree decl = (tree)event_data;
	tree type;

	अगर (decl == शून्य_TREE || decl == error_mark_node)
		वापस;

	type = TREE_TYPE(decl);

	अगर (TREE_CODE(decl) != VAR_DECL)
		वापस;

	अगर (TREE_CODE(type) != RECORD_TYPE && TREE_CODE(type) != UNION_TYPE)
		वापस;

	अगर (!lookup_attribute("randomize_performed", TYPE_ATTRIBUTES(type)))
		वापस;

	DECL_SIZE(decl) = 0;
	DECL_SIZE_UNIT(decl) = 0;
	SET_DECL_ALIGN(decl, 0);
	SET_DECL_MODE (decl, VOIDmode);
	SET_DECL_RTL(decl, 0);
	update_decl_size(decl);
	layout_decl(decl, 0);
पूर्ण

अटल व्योम finish_type(व्योम *event_data, व्योम *data)
अणु
	tree type = (tree)event_data;

	अगर (type == शून्य_TREE || type == error_mark_node)
		वापस;

	अगर (TREE_CODE(type) != RECORD_TYPE)
		वापस;

	अगर (TYPE_FIELDS(type) == शून्य_TREE)
		वापस;

	अगर (lookup_attribute("randomize_considered", TYPE_ATTRIBUTES(type)))
		वापस;

#अगर_घोषित __DEBUG_PLUGIN
	ख_लिखो(मानक_त्रुटि, "Calling randomize_type on %s\n", ORIG_TYPE_NAME(type));
#पूर्ण_अगर
#अगर_घोषित __DEBUG_VERBOSE
	debug_tree(type);
#पूर्ण_अगर
	अक्रमomize_type(type);

	वापस;
पूर्ण

अटल काष्ठा attribute_spec अक्रमomize_layout_attr = अणु पूर्ण;
अटल काष्ठा attribute_spec no_अक्रमomize_layout_attr = अणु पूर्ण;
अटल काष्ठा attribute_spec अक्रमomize_considered_attr = अणु पूर्ण;
अटल काष्ठा attribute_spec अक्रमomize_perक्रमmed_attr = अणु पूर्ण;

अटल व्योम रेजिस्टर_attributes(व्योम *event_data, व्योम *data)
अणु
	अक्रमomize_layout_attr.name		= "randomize_layout";
	अक्रमomize_layout_attr.type_required	= true;
	अक्रमomize_layout_attr.handler		= handle_अक्रमomize_layout_attr;
	अक्रमomize_layout_attr.affects_type_identity = true;

	no_अक्रमomize_layout_attr.name		= "no_randomize_layout";
	no_अक्रमomize_layout_attr.type_required	= true;
	no_अक्रमomize_layout_attr.handler	= handle_अक्रमomize_layout_attr;
	no_अक्रमomize_layout_attr.affects_type_identity = true;

	अक्रमomize_considered_attr.name		= "randomize_considered";
	अक्रमomize_considered_attr.type_required	= true;
	अक्रमomize_considered_attr.handler	= handle_अक्रमomize_considered_attr;

	अक्रमomize_perक्रमmed_attr.name		= "randomize_performed";
	अक्रमomize_perक्रमmed_attr.type_required	= true;
	अक्रमomize_perक्रमmed_attr.handler	= handle_अक्रमomize_perक्रमmed_attr;

	रेजिस्टर_attribute(&अक्रमomize_layout_attr);
	रेजिस्टर_attribute(&no_अक्रमomize_layout_attr);
	रेजिस्टर_attribute(&अक्रमomize_considered_attr);
	रेजिस्टर_attribute(&अक्रमomize_perक्रमmed_attr);
पूर्ण

अटल व्योम check_bad_casts_in_स्थिरructor(tree var, tree init)
अणु
	अचिन्हित HOST_WIDE_INT idx;
	tree field, val;
	tree field_type, val_type;

	FOR_EACH_CONSTRUCTOR_ELT(CONSTRUCTOR_ELTS(init), idx, field, val) अणु
		अगर (TREE_CODE(val) == CONSTRUCTOR) अणु
			check_bad_casts_in_स्थिरructor(var, val);
			जारी;
		पूर्ण

		/* pipacs' plugin creates franken-arrays that dअगरfer from those produced by
		   normal code which all have valid 'field' trees. work around this */
		अगर (field == शून्य_TREE)
			जारी;
		field_type = TREE_TYPE(field);
		val_type = TREE_TYPE(val);

		अगर (TREE_CODE(field_type) != POINTER_TYPE || TREE_CODE(val_type) != POINTER_TYPE)
			जारी;

		अगर (field_type == val_type)
			जारी;

		field_type = TYPE_MAIN_VARIANT(strip_array_types(TYPE_MAIN_VARIANT(TREE_TYPE(field_type))));
		val_type = TYPE_MAIN_VARIANT(strip_array_types(TYPE_MAIN_VARIANT(TREE_TYPE(val_type))));

		अगर (field_type == व्योम_type_node)
			जारी;
		अगर (field_type == val_type)
			जारी;
		अगर (TREE_CODE(val_type) != RECORD_TYPE)
			जारी;

		अगर (!lookup_attribute("randomize_performed", TYPE_ATTRIBUTES(val_type)))
			जारी;
		MISMATCH(DECL_SOURCE_LOCATION(var), "constructor\n", TYPE_MAIN_VARIANT(field_type), TYPE_MAIN_VARIANT(val_type));
	पूर्ण
पूर्ण

/* derived from the स्थिरअगरy plugin */
अटल व्योम check_global_variables(व्योम *event_data, व्योम *data)
अणु
	काष्ठा varpool_node *node;
	tree init;

	FOR_EACH_VARIABLE(node) अणु
		tree var = NODE_DECL(node);
		init = DECL_INITIAL(var);
		अगर (init == शून्य_TREE)
			जारी;

		अगर (TREE_CODE(init) != CONSTRUCTOR)
			जारी;

		check_bad_casts_in_स्थिरructor(var, init);
	पूर्ण
पूर्ण

अटल bool करोminated_by_is_err(स्थिर_tree rhs, basic_block bb)
अणु
	basic_block करोm;
	gimple करोm_sपंचांगt;
	gimple call_sपंचांगt;
	स्थिर_tree करोm_lhs;
	स्थिर_tree poss_is_err_cond;
	स्थिर_tree poss_is_err_func;
	स्थिर_tree is_err_arg;

	करोm = get_immediate_करोminator(CDI_DOMINATORS, bb);
	अगर (!करोm)
		वापस false;

	करोm_sपंचांगt = last_sपंचांगt(करोm);
	अगर (!करोm_sपंचांगt)
		वापस false;

	अगर (gimple_code(करोm_sपंचांगt) != GIMPLE_COND)
		वापस false;

	अगर (gimple_cond_code(करोm_sपंचांगt) != NE_EXPR)
		वापस false;

	अगर (!पूर्णांकeger_zerop(gimple_cond_rhs(करोm_sपंचांगt)))
		वापस false;

	poss_is_err_cond = gimple_cond_lhs(करोm_sपंचांगt);

	अगर (TREE_CODE(poss_is_err_cond) != SSA_NAME)
		वापस false;

	call_sपंचांगt = SSA_NAME_DEF_STMT(poss_is_err_cond);

	अगर (gimple_code(call_sपंचांगt) != GIMPLE_CALL)
		वापस false;

	करोm_lhs = gimple_get_lhs(call_sपंचांगt);
	poss_is_err_func = gimple_call_fndecl(call_sपंचांगt);
	अगर (!poss_is_err_func)
		वापस false;
	अगर (करोm_lhs != poss_is_err_cond)
		वापस false;
	अगर (म_भेद(DECL_NAME_POINTER(poss_is_err_func), "IS_ERR"))
		वापस false;

	is_err_arg = gimple_call_arg(call_sपंचांगt, 0);
	अगर (!is_err_arg)
		वापस false;

	अगर (is_err_arg != rhs)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम handle_local_var_initializers(व्योम)
अणु
	tree var;
	अचिन्हित पूर्णांक i;

	FOR_EACH_LOCAL_DECL(cfun, i, var) अणु
		tree init = DECL_INITIAL(var);
		अगर (!init)
			जारी;
		अगर (TREE_CODE(init) != CONSTRUCTOR)
			जारी;
		check_bad_casts_in_स्थिरructor(var, init);
	पूर्ण
पूर्ण

अटल bool type_name_eq(gimple sपंचांगt, स्थिर_tree type_tree, स्थिर अक्षर *wanted_name)
अणु
	स्थिर अक्षर *type_name;

	अगर (type_tree == शून्य_TREE)
		वापस false;

	चयन (TREE_CODE(type_tree)) अणु
	हाल RECORD_TYPE:
		type_name = TYPE_NAME_POINTER(type_tree);
		अवरोध;
	हाल INTEGER_TYPE:
		अगर (TYPE_PRECISION(type_tree) == CHAR_TYPE_SIZE)
			type_name = "char";
		अन्यथा अणु
			INFORM(gimple_location(sपंचांगt), "found non-char INTEGER_TYPE cast comparison: %qT\n", type_tree);
			debug_tree(type_tree);
			वापस false;
		पूर्ण
		अवरोध;
	हाल POINTER_TYPE:
		अगर (TREE_CODE(TREE_TYPE(type_tree)) == VOID_TYPE) अणु
			type_name = "void *";
			अवरोध;
		पूर्ण अन्यथा अणु
			INFORM(gimple_location(sपंचांगt), "found non-void POINTER_TYPE cast comparison %qT\n", type_tree);
			debug_tree(type_tree);
			वापस false;
		पूर्ण
	शेष:
		INFORM(gimple_location(sपंचांगt), "unhandled cast comparison: %qT\n", type_tree);
		debug_tree(type_tree);
		वापस false;
	पूर्ण

	वापस म_भेद(type_name, wanted_name) == 0;
पूर्ण

अटल bool whitelisted_cast(gimple sपंचांगt, स्थिर_tree lhs_tree, स्थिर_tree rhs_tree)
अणु
	स्थिर काष्ठा whitelist_entry *entry;
	expanded_location xloc = expand_location(gimple_location(sपंचांगt));

	क्रम (entry = whitelist; entry->pathname; entry++) अणु
		अगर (!म_माला(xloc.file, entry->pathname))
			जारी;

		अगर (type_name_eq(sपंचांगt, lhs_tree, entry->lhs) && type_name_eq(sपंचांगt, rhs_tree, entry->rhs))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * iterate over all statements to find "bad" casts:
 * those where the address of the start of a काष्ठाure is cast
 * to a poपूर्णांकer of a काष्ठाure of a dअगरferent type, or a
 * काष्ठाure poपूर्णांकer type is cast to a dअगरferent काष्ठाure poपूर्णांकer type
 */
अटल अचिन्हित पूर्णांक find_bad_casts_execute(व्योम)
अणु
	basic_block bb;

	handle_local_var_initializers();

	FOR_EACH_BB_FN(bb, cfun) अणु
		gimple_sपंचांगt_iterator gsi;

		क्रम (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) अणु
			gimple sपंचांगt;
			स्थिर_tree lhs;
			स्थिर_tree lhs_type;
			स्थिर_tree rhs1;
			स्थिर_tree rhs_type;
			स्थिर_tree ptr_lhs_type;
			स्थिर_tree ptr_rhs_type;
			स्थिर_tree op0;
			स्थिर_tree op0_type;
			क्रमागत tree_code rhs_code;

			sपंचांगt = gsi_sपंचांगt(gsi);

#अगर_घोषित __DEBUG_PLUGIN
#अगर_घोषित __DEBUG_VERBOSE
			debug_gimple_sपंचांगt(sपंचांगt);
			debug_tree(gimple_get_lhs(sपंचांगt));
#पूर्ण_अगर
#पूर्ण_अगर

			अगर (gimple_code(sपंचांगt) != GIMPLE_ASSIGN)
				जारी;

#अगर_घोषित __DEBUG_PLUGIN
#अगर_घोषित __DEBUG_VERBOSE
			debug_tree(gimple_assign_rhs1(sपंचांगt));
#पूर्ण_अगर
#पूर्ण_अगर


			rhs_code = gimple_assign_rhs_code(sपंचांगt);

			अगर (rhs_code != ADDR_EXPR && rhs_code != SSA_NAME)
				जारी;

			lhs = gimple_get_lhs(sपंचांगt);
			lhs_type = TREE_TYPE(lhs);
			rhs1 = gimple_assign_rhs1(sपंचांगt);
			rhs_type = TREE_TYPE(rhs1);

			अगर (TREE_CODE(rhs_type) != POINTER_TYPE ||
			    TREE_CODE(lhs_type) != POINTER_TYPE)
				जारी;

			ptr_lhs_type = TYPE_MAIN_VARIANT(strip_array_types(TYPE_MAIN_VARIANT(TREE_TYPE(lhs_type))));
			ptr_rhs_type = TYPE_MAIN_VARIANT(strip_array_types(TYPE_MAIN_VARIANT(TREE_TYPE(rhs_type))));

			अगर (ptr_rhs_type == व्योम_type_node)
				जारी;

			अगर (ptr_lhs_type == व्योम_type_node)
				जारी;

			अगर (करोminated_by_is_err(rhs1, bb))
				जारी;

			अगर (TREE_CODE(ptr_rhs_type) != RECORD_TYPE) अणु
#अगर_अघोषित __DEBUG_PLUGIN
				अगर (lookup_attribute("randomize_performed", TYPE_ATTRIBUTES(ptr_lhs_type)))
#पूर्ण_अगर
				अणु
					अगर (!whitelisted_cast(sपंचांगt, ptr_lhs_type, ptr_rhs_type))
						MISMATCH(gimple_location(sपंचांगt), "rhs", ptr_lhs_type, ptr_rhs_type);
				पूर्ण
				जारी;
			पूर्ण

			अगर (rhs_code == SSA_NAME && ptr_lhs_type == ptr_rhs_type)
				जारी;

			अगर (rhs_code == ADDR_EXPR) अणु
				op0 = TREE_OPERAND(rhs1, 0);

				अगर (op0 == शून्य_TREE)
					जारी;

				अगर (TREE_CODE(op0) != VAR_DECL)
					जारी;

				op0_type = TYPE_MAIN_VARIANT(strip_array_types(TYPE_MAIN_VARIANT(TREE_TYPE(op0))));
				अगर (op0_type == ptr_lhs_type)
					जारी;

#अगर_अघोषित __DEBUG_PLUGIN
				अगर (lookup_attribute("randomize_performed", TYPE_ATTRIBUTES(op0_type)))
#पूर्ण_अगर
				अणु
					अगर (!whitelisted_cast(sपंचांगt, ptr_lhs_type, op0_type))
						MISMATCH(gimple_location(sपंचांगt), "op0", ptr_lhs_type, op0_type);
				पूर्ण
			पूर्ण अन्यथा अणु
				स्थिर_tree ssa_name_var = SSA_NAME_VAR(rhs1);
				/* skip bogus type casts पूर्णांकroduced by container_of */
				अगर (ssa_name_var != शून्य_TREE && DECL_NAME(ssa_name_var) && 
				    !म_भेद((स्थिर अक्षर *)DECL_NAME_POINTER(ssa_name_var), "__mptr"))
					जारी;
#अगर_अघोषित __DEBUG_PLUGIN
				अगर (lookup_attribute("randomize_performed", TYPE_ATTRIBUTES(ptr_rhs_type)))
#पूर्ण_अगर
				अणु
					अगर (!whitelisted_cast(sपंचांगt, ptr_lhs_type, ptr_rhs_type))
						MISMATCH(gimple_location(sपंचांगt), "ssa", ptr_lhs_type, ptr_rhs_type);
				पूर्ण
			पूर्ण

		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा PASS_NAME find_bad_casts
#घोषणा NO_GATE
#घोषणा TODO_FLAGS_FINISH TODO_dump_func
#समावेश "gcc-generate-gimple-pass.h"

__visible पूर्णांक plugin_init(काष्ठा plugin_name_args *plugin_info, काष्ठा plugin_gcc_version *version)
अणु
	पूर्णांक i;
	स्थिर अक्षर * स्थिर plugin_name = plugin_info->base_name;
	स्थिर पूर्णांक argc = plugin_info->argc;
	स्थिर काष्ठा plugin_argument * स्थिर argv = plugin_info->argv;
	bool enable = true;
	पूर्णांक obtained_seed = 0;
	काष्ठा रेजिस्टर_pass_info find_bad_casts_pass_info;

	find_bad_casts_pass_info.pass			= make_find_bad_casts_pass();
	find_bad_casts_pass_info.reference_pass_name	= "ssa";
	find_bad_casts_pass_info.ref_pass_instance_number	= 1;
	find_bad_casts_pass_info.pos_op			= PASS_POS_INSERT_AFTER;

	अगर (!plugin_शेष_version_check(version, &gcc_version)) अणु
		error(G_("incompatible gcc/plugin versions"));
		वापस 1;
	पूर्ण

	अगर (म_भेदन(lang_hooks.name, "GNU C", 5) && !म_भेदन(lang_hooks.name, "GNU C+", 6)) अणु
		inक्रमm(UNKNOWN_LOCATION, G_("%s supports C only, not %s"), plugin_name, lang_hooks.name);
		enable = false;
	पूर्ण

	क्रम (i = 0; i < argc; ++i) अणु
		अगर (!म_भेद(argv[i].key, "disable")) अणु
			enable = false;
			जारी;
		पूर्ण
		अगर (!म_भेद(argv[i].key, "performance-mode")) अणु
			perक्रमmance_mode = 1;
			जारी;
		पूर्ण
		error(G_("unknown option '-fplugin-arg-%s-%s'"), plugin_name, argv[i].key);
	पूर्ण

	अगर (म_माप(अक्रमकाष्ठा_seed) != 64) अणु
		error(G_("invalid seed value supplied for %s plugin"), plugin_name);
		वापस 1;
	पूर्ण
	obtained_seed = माला_पूछो(अक्रमकाष्ठा_seed, "%016llx%016llx%016llx%016llx",
		&shuffle_seed[0], &shuffle_seed[1], &shuffle_seed[2], &shuffle_seed[3]);
	अगर (obtained_seed != 4) अणु
		error(G_("Invalid seed supplied for %s plugin"), plugin_name);
		वापस 1;
	पूर्ण

	रेजिस्टर_callback(plugin_name, PLUGIN_INFO, शून्य, &अक्रमomize_layout_plugin_info);
	अगर (enable) अणु
		रेजिस्टर_callback(plugin_name, PLUGIN_ALL_IPA_PASSES_START, check_global_variables, शून्य);
		रेजिस्टर_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, शून्य, &find_bad_casts_pass_info);
		रेजिस्टर_callback(plugin_name, PLUGIN_FINISH_TYPE, finish_type, शून्य);
		रेजिस्टर_callback(plugin_name, PLUGIN_FINISH_DECL, अक्रमomize_layout_finish_decl, शून्य);
	पूर्ण
	रेजिस्टर_callback(plugin_name, PLUGIN_ATTRIBUTES, रेजिस्टर_attributes, शून्य);

	वापस 0;
पूर्ण
