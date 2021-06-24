<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dwarf-aux.c : libdw auxiliary पूर्णांकerfaces
 */

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश "debug.h"
#समावेश "dwarf-aux.h"
#समावेश "strbuf.h"
#समावेश "string2.h"

/**
 * cu_find_realpath - Find the realpath of the target file
 * @cu_die: A DIE(dwarf inक्रमmation entry) of CU(compilation Unit)
 * @fname:  The tail filename of the target file
 *
 * Find the real(दीर्घ) path of @fname in @cu_die.
 */
स्थिर अक्षर *cu_find_realpath(Dwarf_Die *cu_die, स्थिर अक्षर *fname)
अणु
	Dwarf_Files *files;
	माप_प्रकार nfiles, i;
	स्थिर अक्षर *src = शून्य;
	पूर्णांक ret;

	अगर (!fname)
		वापस शून्य;

	ret = dwarf_माला_लोrcfiles(cu_die, &files, &nfiles);
	अगर (ret != 0)
		वापस शून्य;

	क्रम (i = 0; i < nfiles; i++) अणु
		src = dwarf_filesrc(files, i, शून्य, शून्य);
		अगर (strtailcmp(src, fname) == 0)
			अवरोध;
	पूर्ण
	अगर (i == nfiles)
		वापस शून्य;
	वापस src;
पूर्ण

/**
 * cu_get_comp_dir - Get the path of compilation directory
 * @cu_die: a CU DIE
 *
 * Get the path of compilation directory of given @cu_die.
 * Since this depends on DW_AT_comp_dir, older gcc will not
 * embedded it. In that हाल, this वापसs शून्य.
 */
स्थिर अक्षर *cu_get_comp_dir(Dwarf_Die *cu_die)
अणु
	Dwarf_Attribute attr;
	अगर (dwarf_attr(cu_die, DW_AT_comp_dir, &attr) == शून्य)
		वापस शून्य;
	वापस dwarf_क्रमmstring(&attr);
पूर्ण

/* Unlike dwarf_माला_लोrc_die(), cu_माला_लोrc_die() only वापसs statement line */
अटल Dwarf_Line *cu_माला_लोrc_die(Dwarf_Die *cu_die, Dwarf_Addr addr)
अणु
	Dwarf_Addr laddr;
	Dwarf_Lines *lines;
	Dwarf_Line *line;
	माप_प्रकार nlines, l, u, n;
	bool flag;

	अगर (dwarf_माला_लोrclines(cu_die, &lines, &nlines) != 0 ||
	    nlines == 0)
		वापस शून्य;

	/* Lines are sorted by address, use binary search */
	l = 0; u = nlines - 1;
	जबतक (l < u) अणु
		n = u - (u - l) / 2;
		line = dwarf_onesrcline(lines, n);
		अगर (!line || dwarf_lineaddr(line, &laddr) != 0)
			वापस शून्य;
		अगर (addr < laddr)
			u = n - 1;
		अन्यथा
			l = n;
	पूर्ण
	/* Going backward to find the lowest line */
	करो अणु
		line = dwarf_onesrcline(lines, --l);
		अगर (!line || dwarf_lineaddr(line, &laddr) != 0)
			वापस शून्य;
	पूर्ण जबतक (laddr == addr);
	l++;
	/* Going क्रमward to find the statement line */
	करो अणु
		line = dwarf_onesrcline(lines, l++);
		अगर (!line || dwarf_lineaddr(line, &laddr) != 0 ||
		    dwarf_linebeginstatement(line, &flag) != 0)
			वापस शून्य;
		अगर (laddr > addr)
			वापस शून्य;
	पूर्ण जबतक (!flag);

	वापस line;
पूर्ण

/**
 * cu_find_lineinfo - Get a line number and file name क्रम given address
 * @cu_die: a CU DIE
 * @addr: An address
 * @fname: a poपूर्णांकer which वापसs the file name string
 * @lineno: a poपूर्णांकer which वापसs the line number
 *
 * Find a line number and file name क्रम @addr in @cu_die.
 */
पूर्णांक cu_find_lineinfo(Dwarf_Die *cu_die, अचिन्हित दीर्घ addr,
		    स्थिर अक्षर **fname, पूर्णांक *lineno)
अणु
	Dwarf_Line *line;
	Dwarf_Die die_mem;
	Dwarf_Addr faddr;

	अगर (die_find_realfunc(cu_die, (Dwarf_Addr)addr, &die_mem)
	    && die_entrypc(&die_mem, &faddr) == 0 &&
	    faddr == addr) अणु
		*fname = dwarf_decl_file(&die_mem);
		dwarf_decl_line(&die_mem, lineno);
		जाओ out;
	पूर्ण

	line = cu_माला_लोrc_die(cu_die, (Dwarf_Addr)addr);
	अगर (line && dwarf_lineno(line, lineno) == 0) अणु
		*fname = dwarf_linesrc(line, शून्य, शून्य);
		अगर (!*fname)
			/* line number is useless without filename */
			*lineno = 0;
	पूर्ण

out:
	वापस *lineno ?: -ENOENT;
पूर्ण

अटल पूर्णांक __die_find_अंतरभूत_cb(Dwarf_Die *die_mem, व्योम *data);

/**
 * cu_walk_functions_at - Walk on function DIEs at given address
 * @cu_die: A CU DIE
 * @addr: An address
 * @callback: A callback which called with found DIEs
 * @data: A user data
 *
 * Walk on function DIEs at given @addr in @cu_die. Passed DIEs
 * should be subprogram or अंतरभूतd-subroutines.
 */
पूर्णांक cu_walk_functions_at(Dwarf_Die *cu_die, Dwarf_Addr addr,
		    पूर्णांक (*callback)(Dwarf_Die *, व्योम *), व्योम *data)
अणु
	Dwarf_Die die_mem;
	Dwarf_Die *sc_die;
	पूर्णांक ret = -ENOENT;

	/* Inlined function could be recursive. Trace it until fail */
	क्रम (sc_die = die_find_realfunc(cu_die, addr, &die_mem);
	     sc_die != शून्य;
	     sc_die = die_find_child(sc_die, __die_find_अंतरभूत_cb, &addr,
				     &die_mem)) अणु
		ret = callback(sc_die, data);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;

पूर्ण

/**
 * die_get_linkage_name - Get the linkage name of the object
 * @dw_die: A DIE of the object
 *
 * Get the linkage name attribute of given @dw_die.
 * For C++ binary, the linkage name will be the mangled symbol.
 */
स्थिर अक्षर *die_get_linkage_name(Dwarf_Die *dw_die)
अणु
	Dwarf_Attribute attr;

	अगर (dwarf_attr_पूर्णांकegrate(dw_die, DW_AT_linkage_name, &attr) == शून्य)
		वापस शून्य;
	वापस dwarf_क्रमmstring(&attr);
पूर्ण

/**
 * die_compare_name - Compare diename and tname
 * @dw_die: a DIE
 * @tname: a string of target name
 *
 * Compare the name of @dw_die and @tname. Return false अगर @dw_die has no name.
 */
bool die_compare_name(Dwarf_Die *dw_die, स्थिर अक्षर *tname)
अणु
	स्थिर अक्षर *name;

	name = dwarf_diename(dw_die);
	वापस name ? (म_भेद(tname, name) == 0) : false;
पूर्ण

/**
 * die_match_name - Match diename/linkage name and glob
 * @dw_die: a DIE
 * @glob: a string of target glob pattern
 *
 * Glob matching the name of @dw_die and @glob. Return false अगर matching fail.
 * This also match linkage name.
 */
bool die_match_name(Dwarf_Die *dw_die, स्थिर अक्षर *glob)
अणु
	स्थिर अक्षर *name;

	name = dwarf_diename(dw_die);
	अगर (name && strglobmatch(name, glob))
		वापस true;
	/* fall back to check linkage name */
	name = die_get_linkage_name(dw_die);
	अगर (name && strglobmatch(name, glob))
		वापस true;

	वापस false;
पूर्ण

/**
 * die_get_call_lineno - Get callsite line number of अंतरभूत-function instance
 * @in_die: a DIE of an अंतरभूतd function instance
 *
 * Get call-site line number of @in_die. This means from where the अंतरभूत
 * function is called.
 */
पूर्णांक die_get_call_lineno(Dwarf_Die *in_die)
अणु
	Dwarf_Attribute attr;
	Dwarf_Word ret;

	अगर (!dwarf_attr(in_die, DW_AT_call_line, &attr))
		वापस -ENOENT;

	dwarf_क्रमmudata(&attr, &ret);
	वापस (पूर्णांक)ret;
पूर्ण

/**
 * die_get_type - Get type DIE
 * @vr_die: a DIE of a variable
 * @die_mem: where to store a type DIE
 *
 * Get a DIE of the type of given variable (@vr_die), and store
 * it to die_mem. Return शून्य अगर fails to get a type DIE.
 */
Dwarf_Die *die_get_type(Dwarf_Die *vr_die, Dwarf_Die *die_mem)
अणु
	Dwarf_Attribute attr;

	अगर (dwarf_attr_पूर्णांकegrate(vr_die, DW_AT_type, &attr) &&
	    dwarf_क्रमmref_die(&attr, die_mem))
		वापस die_mem;
	अन्यथा
		वापस शून्य;
पूर्ण

/* Get a type die, but skip qualअगरiers */
अटल Dwarf_Die *__die_get_real_type(Dwarf_Die *vr_die, Dwarf_Die *die_mem)
अणु
	पूर्णांक tag;

	करो अणु
		vr_die = die_get_type(vr_die, die_mem);
		अगर (!vr_die)
			अवरोध;
		tag = dwarf_tag(vr_die);
	पूर्ण जबतक (tag == DW_TAG_स्थिर_type ||
		 tag == DW_TAG_restrict_type ||
		 tag == DW_TAG_अस्थिर_type ||
		 tag == DW_TAG_shared_type);

	वापस vr_die;
पूर्ण

/**
 * die_get_real_type - Get a type die, but skip qualअगरiers and प्रकार
 * @vr_die: a DIE of a variable
 * @die_mem: where to store a type DIE
 *
 * Get a DIE of the type of given variable (@vr_die), and store
 * it to die_mem. Return शून्य अगर fails to get a type DIE.
 * If the type is qualअगरiers (e.g. स्थिर) or प्रकार, this skips it
 * and tries to find real type (काष्ठाure or basic types, e.g. पूर्णांक).
 */
Dwarf_Die *die_get_real_type(Dwarf_Die *vr_die, Dwarf_Die *die_mem)
अणु
	करो अणु
		vr_die = __die_get_real_type(vr_die, die_mem);
	पूर्ण जबतक (vr_die && dwarf_tag(vr_die) == DW_TAG_प्रकार);

	वापस vr_die;
पूर्ण

/* Get attribute and translate it as a udata */
अटल पूर्णांक die_get_attr_udata(Dwarf_Die *tp_die, अचिन्हित पूर्णांक attr_name,
			      Dwarf_Word *result)
अणु
	Dwarf_Attribute attr;

	अगर (dwarf_attr(tp_die, attr_name, &attr) == शून्य ||
	    dwarf_क्रमmudata(&attr, result) != 0)
		वापस -ENOENT;

	वापस 0;
पूर्ण

/* Get attribute and translate it as a sdata */
अटल पूर्णांक die_get_attr_sdata(Dwarf_Die *tp_die, अचिन्हित पूर्णांक attr_name,
			      Dwarf_Sword *result)
अणु
	Dwarf_Attribute attr;

	अगर (dwarf_attr(tp_die, attr_name, &attr) == शून्य ||
	    dwarf_क्रमmsdata(&attr, result) != 0)
		वापस -ENOENT;

	वापस 0;
पूर्ण

/**
 * die_is_चिन्हित_type - Check whether a type DIE is चिन्हित or not
 * @tp_die: a DIE of a type
 *
 * Get the encoding of @tp_die and वापस true अगर the encoding
 * is चिन्हित.
 */
bool die_is_चिन्हित_type(Dwarf_Die *tp_die)
अणु
	Dwarf_Word ret;

	अगर (die_get_attr_udata(tp_die, DW_AT_encoding, &ret))
		वापस false;

	वापस (ret == DW_ATE_चिन्हित_अक्षर || ret == DW_ATE_चिन्हित ||
		ret == DW_ATE_चिन्हित_fixed);
पूर्ण

/**
 * die_is_func_def - Ensure that this DIE is a subprogram and definition
 * @dw_die: a DIE
 *
 * Ensure that this DIE is a subprogram and NOT a declaration. This
 * वापसs true अगर @dw_die is a function definition.
 **/
bool die_is_func_def(Dwarf_Die *dw_die)
अणु
	Dwarf_Attribute attr;
	Dwarf_Addr addr = 0;

	अगर (dwarf_tag(dw_die) != DW_TAG_subprogram)
		वापस false;

	अगर (dwarf_attr(dw_die, DW_AT_declaration, &attr))
		वापस false;

	/*
	 * DW_AT_declaration can be lost from function declaration
	 * by gcc's bug #97060.
	 * So we need to check this subprogram DIE has DW_AT_अंतरभूत
	 * or an entry address.
	 */
	अगर (!dwarf_attr(dw_die, DW_AT_अंतरभूत, &attr) &&
	    die_entrypc(dw_die, &addr) < 0)
		वापस false;

	वापस true;
पूर्ण

/**
 * die_entrypc - Returns entry PC (the lowest address) of a DIE
 * @dw_die: a DIE
 * @addr: where to store entry PC
 *
 * Since dwarf_entrypc() करोes not वापस entry PC अगर the DIE has only address
 * range, we have to use this to retrieve the lowest address from the address
 * range attribute.
 */
पूर्णांक die_entrypc(Dwarf_Die *dw_die, Dwarf_Addr *addr)
अणु
	Dwarf_Addr base, end;
	Dwarf_Attribute attr;

	अगर (!addr)
		वापस -EINVAL;

	अगर (dwarf_entrypc(dw_die, addr) == 0)
		वापस 0;

	/*
	 *  Since the dwarf_ranges() will वापस 0 अगर there is no
	 * DW_AT_ranges attribute, we should check it first.
	 */
	अगर (!dwarf_attr(dw_die, DW_AT_ranges, &attr))
		वापस -ENOENT;

	वापस dwarf_ranges(dw_die, 0, &base, addr, &end) < 0 ? -ENOENT : 0;
पूर्ण

/**
 * die_is_func_instance - Ensure that this DIE is an instance of a subprogram
 * @dw_die: a DIE
 *
 * Ensure that this DIE is an instance (which has an entry address).
 * This वापसs true अगर @dw_die is a function instance. If not, the @dw_die
 * must be a prototype. You can use die_walk_instances() to find actual
 * instances.
 **/
bool die_is_func_instance(Dwarf_Die *dw_die)
अणु
	Dwarf_Addr पंचांगp;
	Dwarf_Attribute attr_mem;
	पूर्णांक tag = dwarf_tag(dw_die);

	अगर (tag != DW_TAG_subprogram &&
	    tag != DW_TAG_अंतरभूतd_subroutine)
		वापस false;

	वापस dwarf_entrypc(dw_die, &पंचांगp) == 0 ||
		dwarf_attr(dw_die, DW_AT_ranges, &attr_mem) != शून्य;
पूर्ण

/**
 * die_get_data_member_location - Get the data-member offset
 * @mb_die: a DIE of a member of a data काष्ठाure
 * @offs: The offset of the member in the data काष्ठाure
 *
 * Get the offset of @mb_die in the data काष्ठाure including @mb_die, and
 * stores result offset to @offs. If any error occurs this वापसs त्रुटि_सं.
 */
पूर्णांक die_get_data_member_location(Dwarf_Die *mb_die, Dwarf_Word *offs)
अणु
	Dwarf_Attribute attr;
	Dwarf_Op *expr;
	माप_प्रकार nexpr;
	पूर्णांक ret;

	अगर (dwarf_attr(mb_die, DW_AT_data_member_location, &attr) == शून्य)
		वापस -ENOENT;

	अगर (dwarf_क्रमmudata(&attr, offs) != 0) अणु
		/* DW_AT_data_member_location should be DW_OP_plus_uस्थिर */
		ret = dwarf_getlocation(&attr, &expr, &nexpr);
		अगर (ret < 0 || nexpr == 0)
			वापस -ENOENT;

		अगर (expr[0].atom != DW_OP_plus_uस्थिर || nexpr != 1) अणु
			pr_debug("Unable to get offset:Unexpected OP %x (%zd)\n",
				 expr[0].atom, nexpr);
			वापस -ENOTSUP;
		पूर्ण
		*offs = (Dwarf_Word)expr[0].number;
	पूर्ण
	वापस 0;
पूर्ण

/* Get the call file index number in CU DIE */
अटल पूर्णांक die_get_call_fileno(Dwarf_Die *in_die)
अणु
	Dwarf_Sword idx;

	अगर (die_get_attr_sdata(in_die, DW_AT_call_file, &idx) == 0)
		वापस (पूर्णांक)idx;
	अन्यथा
		वापस -ENOENT;
पूर्ण

/* Get the declared file index number in CU DIE */
अटल पूर्णांक die_get_decl_fileno(Dwarf_Die *pdie)
अणु
	Dwarf_Sword idx;

	अगर (die_get_attr_sdata(pdie, DW_AT_decl_file, &idx) == 0)
		वापस (पूर्णांक)idx;
	अन्यथा
		वापस -ENOENT;
पूर्ण

/**
 * die_get_call_file - Get callsite file name of अंतरभूतd function instance
 * @in_die: a DIE of an अंतरभूतd function instance
 *
 * Get call-site file name of @in_die. This means from which file the अंतरभूत
 * function is called.
 */
स्थिर अक्षर *die_get_call_file(Dwarf_Die *in_die)
अणु
	Dwarf_Die cu_die;
	Dwarf_Files *files;
	पूर्णांक idx;

	idx = die_get_call_fileno(in_die);
	अगर (idx < 0 || !dwarf_diecu(in_die, &cu_die, शून्य, शून्य) ||
	    dwarf_माला_लोrcfiles(&cu_die, &files, शून्य) != 0)
		वापस शून्य;

	वापस dwarf_filesrc(files, idx, शून्य, शून्य);
पूर्ण


/**
 * die_find_child - Generic DIE search function in DIE tree
 * @rt_die: a root DIE
 * @callback: a callback function
 * @data: a user data passed to the callback function
 * @die_mem: a buffer क्रम result DIE
 *
 * Trace DIE tree from @rt_die and call @callback क्रम each child DIE.
 * If @callback वापसs DIE_FIND_CB_END, this stores the DIE पूर्णांकo
 * @die_mem and वापसs it. If @callback वापसs DIE_FIND_CB_CONTINUE,
 * this जारीs to trace the tree. Optionally, @callback can वापस
 * DIE_FIND_CB_CHILD and DIE_FIND_CB_SIBLING, those means trace only
 * the children and trace only the siblings respectively.
 * Returns शून्य अगर @callback can't find any appropriate DIE.
 */
Dwarf_Die *die_find_child(Dwarf_Die *rt_die,
			  पूर्णांक (*callback)(Dwarf_Die *, व्योम *),
			  व्योम *data, Dwarf_Die *die_mem)
अणु
	Dwarf_Die child_die;
	पूर्णांक ret;

	ret = dwarf_child(rt_die, die_mem);
	अगर (ret != 0)
		वापस शून्य;

	करो अणु
		ret = callback(die_mem, data);
		अगर (ret == DIE_FIND_CB_END)
			वापस die_mem;

		अगर ((ret & DIE_FIND_CB_CHILD) &&
		    die_find_child(die_mem, callback, data, &child_die)) अणु
			स_नकल(die_mem, &child_die, माप(Dwarf_Die));
			वापस die_mem;
		पूर्ण
	पूर्ण जबतक ((ret & DIE_FIND_CB_SIBLING) &&
		 dwarf_siblingof(die_mem, die_mem) == 0);

	वापस शून्य;
पूर्ण

काष्ठा __addr_die_search_param अणु
	Dwarf_Addr	addr;
	Dwarf_Die	*die_mem;
पूर्ण;

अटल पूर्णांक __die_search_func_tail_cb(Dwarf_Die *fn_die, व्योम *data)
अणु
	काष्ठा __addr_die_search_param *ad = data;
	Dwarf_Addr addr = 0;

	अगर (dwarf_tag(fn_die) == DW_TAG_subprogram &&
	    !dwarf_highpc(fn_die, &addr) &&
	    addr == ad->addr) अणु
		स_नकल(ad->die_mem, fn_die, माप(Dwarf_Die));
		वापस DWARF_CB_ABORT;
	पूर्ण
	वापस DWARF_CB_OK;
पूर्ण

/**
 * die_find_tailfunc - Search क्रम a non-अंतरभूतd function with tail call at
 * given address
 * @cu_die: a CU DIE which including @addr
 * @addr: target address
 * @die_mem: a buffer क्रम result DIE
 *
 * Search क्रम a non-अंतरभूतd function DIE with tail call at @addr. Stores the
 * DIE to @die_mem and वापसs it अगर found. Returns शून्य अगर failed.
 */
Dwarf_Die *die_find_tailfunc(Dwarf_Die *cu_die, Dwarf_Addr addr,
				    Dwarf_Die *die_mem)
अणु
	काष्ठा __addr_die_search_param ad;
	ad.addr = addr;
	ad.die_mem = die_mem;
	/* dwarf_माला_लोcopes can't find subprogram. */
	अगर (!dwarf_getfuncs(cu_die, __die_search_func_tail_cb, &ad, 0))
		वापस शून्य;
	अन्यथा
		वापस die_mem;
पूर्ण

/* die_find callback क्रम non-अंतरभूतd function search */
अटल पूर्णांक __die_search_func_cb(Dwarf_Die *fn_die, व्योम *data)
अणु
	काष्ठा __addr_die_search_param *ad = data;

	/*
	 * Since a declaration entry करोesn't has given pc, this always वापसs
	 * function definition entry.
	 */
	अगर (dwarf_tag(fn_die) == DW_TAG_subprogram &&
	    dwarf_haspc(fn_die, ad->addr)) अणु
		स_नकल(ad->die_mem, fn_die, माप(Dwarf_Die));
		वापस DWARF_CB_ABORT;
	पूर्ण
	वापस DWARF_CB_OK;
पूर्ण

/**
 * die_find_realfunc - Search a non-अंतरभूतd function at given address
 * @cu_die: a CU DIE which including @addr
 * @addr: target address
 * @die_mem: a buffer क्रम result DIE
 *
 * Search a non-अंतरभूतd function DIE which includes @addr. Stores the
 * DIE to @die_mem and वापसs it अगर found. Returns शून्य अगर failed.
 */
Dwarf_Die *die_find_realfunc(Dwarf_Die *cu_die, Dwarf_Addr addr,
				    Dwarf_Die *die_mem)
अणु
	काष्ठा __addr_die_search_param ad;
	ad.addr = addr;
	ad.die_mem = die_mem;
	/* dwarf_माला_लोcopes can't find subprogram. */
	अगर (!dwarf_getfuncs(cu_die, __die_search_func_cb, &ad, 0))
		वापस शून्य;
	अन्यथा
		वापस die_mem;
पूर्ण

/* die_find callback क्रम अंतरभूत function search */
अटल पूर्णांक __die_find_अंतरभूत_cb(Dwarf_Die *die_mem, व्योम *data)
अणु
	Dwarf_Addr *addr = data;

	अगर (dwarf_tag(die_mem) == DW_TAG_अंतरभूतd_subroutine &&
	    dwarf_haspc(die_mem, *addr))
		वापस DIE_FIND_CB_END;

	वापस DIE_FIND_CB_CONTINUE;
पूर्ण

/**
 * die_find_top_अंतरभूतfunc - Search the top अंतरभूतd function at given address
 * @sp_die: a subprogram DIE which including @addr
 * @addr: target address
 * @die_mem: a buffer क्रम result DIE
 *
 * Search an अंतरभूतd function DIE which includes @addr. Stores the
 * DIE to @die_mem and वापसs it अगर found. Returns शून्य अगर failed.
 * Even अगर several अंतरभूतd functions are expanded recursively, this
 * करोesn't trace it करोwn, and वापसs the topmost one.
 */
Dwarf_Die *die_find_top_अंतरभूतfunc(Dwarf_Die *sp_die, Dwarf_Addr addr,
				   Dwarf_Die *die_mem)
अणु
	वापस die_find_child(sp_die, __die_find_अंतरभूत_cb, &addr, die_mem);
पूर्ण

/**
 * die_find_अंतरभूतfunc - Search an अंतरभूतd function at given address
 * @sp_die: a subprogram DIE which including @addr
 * @addr: target address
 * @die_mem: a buffer क्रम result DIE
 *
 * Search an अंतरभूतd function DIE which includes @addr. Stores the
 * DIE to @die_mem and वापसs it अगर found. Returns शून्य अगर failed.
 * If several अंतरभूतd functions are expanded recursively, this trace
 * it करोwn and वापसs deepest one.
 */
Dwarf_Die *die_find_अंतरभूतfunc(Dwarf_Die *sp_die, Dwarf_Addr addr,
			       Dwarf_Die *die_mem)
अणु
	Dwarf_Die पंचांगp_die;

	sp_die = die_find_child(sp_die, __die_find_अंतरभूत_cb, &addr, &पंचांगp_die);
	अगर (!sp_die)
		वापस शून्य;

	/* Inlined function could be recursive. Trace it until fail */
	जबतक (sp_die) अणु
		स_नकल(die_mem, sp_die, माप(Dwarf_Die));
		sp_die = die_find_child(sp_die, __die_find_अंतरभूत_cb, &addr,
					&पंचांगp_die);
	पूर्ण

	वापस die_mem;
पूर्ण

काष्ठा __instance_walk_param अणु
	व्योम    *addr;
	पूर्णांक	(*callback)(Dwarf_Die *, व्योम *);
	व्योम    *data;
	पूर्णांक	retval;
पूर्ण;

अटल पूर्णांक __die_walk_instances_cb(Dwarf_Die *inst, व्योम *data)
अणु
	काष्ठा __instance_walk_param *iwp = data;
	Dwarf_Attribute attr_mem;
	Dwarf_Die origin_mem;
	Dwarf_Attribute *attr;
	Dwarf_Die *origin;
	पूर्णांक पंचांगp;

	अगर (!die_is_func_instance(inst))
		वापस DIE_FIND_CB_CONTINUE;

	attr = dwarf_attr(inst, DW_AT_असलtract_origin, &attr_mem);
	अगर (attr == शून्य)
		वापस DIE_FIND_CB_CONTINUE;

	origin = dwarf_क्रमmref_die(attr, &origin_mem);
	अगर (origin == शून्य || origin->addr != iwp->addr)
		वापस DIE_FIND_CB_CONTINUE;

	/* Ignore redundant instances */
	अगर (dwarf_tag(inst) == DW_TAG_अंतरभूतd_subroutine) अणु
		dwarf_decl_line(origin, &पंचांगp);
		अगर (die_get_call_lineno(inst) == पंचांगp) अणु
			पंचांगp = die_get_decl_fileno(origin);
			अगर (die_get_call_fileno(inst) == पंचांगp)
				वापस DIE_FIND_CB_CONTINUE;
		पूर्ण
	पूर्ण

	iwp->retval = iwp->callback(inst, iwp->data);

	वापस (iwp->retval) ? DIE_FIND_CB_END : DIE_FIND_CB_CONTINUE;
पूर्ण

/**
 * die_walk_instances - Walk on instances of given DIE
 * @or_die: an असलtract original DIE
 * @callback: a callback function which is called with instance DIE
 * @data: user data
 *
 * Walk on the instances of give @in_die. @in_die must be an अंतरभूतd function
 * declaration. This वापसs the वापस value of @callback अगर it वापसs
 * non-zero value, or -ENOENT अगर there is no instance.
 */
पूर्णांक die_walk_instances(Dwarf_Die *or_die, पूर्णांक (*callback)(Dwarf_Die *, व्योम *),
		       व्योम *data)
अणु
	Dwarf_Die cu_die;
	Dwarf_Die die_mem;
	काष्ठा __instance_walk_param iwp = अणु
		.addr = or_die->addr,
		.callback = callback,
		.data = data,
		.retval = -ENOENT,
	पूर्ण;

	अगर (dwarf_diecu(or_die, &cu_die, शून्य, शून्य) == शून्य)
		वापस -ENOENT;

	die_find_child(&cu_die, __die_walk_instances_cb, &iwp, &die_mem);

	वापस iwp.retval;
पूर्ण

/* Line walker पूर्णांकernal parameters */
काष्ठा __line_walk_param अणु
	bool recursive;
	line_walk_callback_t callback;
	व्योम *data;
	पूर्णांक retval;
पूर्ण;

अटल पूर्णांक __die_walk_funclines_cb(Dwarf_Die *in_die, व्योम *data)
अणु
	काष्ठा __line_walk_param *lw = data;
	Dwarf_Addr addr = 0;
	स्थिर अक्षर *fname;
	पूर्णांक lineno;

	अगर (dwarf_tag(in_die) == DW_TAG_अंतरभूतd_subroutine) अणु
		fname = die_get_call_file(in_die);
		lineno = die_get_call_lineno(in_die);
		अगर (fname && lineno > 0 && die_entrypc(in_die, &addr) == 0) अणु
			lw->retval = lw->callback(fname, lineno, addr, lw->data);
			अगर (lw->retval != 0)
				वापस DIE_FIND_CB_END;
		पूर्ण
		अगर (!lw->recursive)
			वापस DIE_FIND_CB_SIBLING;
	पूर्ण

	अगर (addr) अणु
		fname = dwarf_decl_file(in_die);
		अगर (fname && dwarf_decl_line(in_die, &lineno) == 0) अणु
			lw->retval = lw->callback(fname, lineno, addr, lw->data);
			अगर (lw->retval != 0)
				वापस DIE_FIND_CB_END;
		पूर्ण
	पूर्ण

	/* Continue to search nested अंतरभूतd function call-sites */
	वापस DIE_FIND_CB_CONTINUE;
पूर्ण

/* Walk on lines of blocks included in given DIE */
अटल पूर्णांक __die_walk_funclines(Dwarf_Die *sp_die, bool recursive,
				line_walk_callback_t callback, व्योम *data)
अणु
	काष्ठा __line_walk_param lw = अणु
		.recursive = recursive,
		.callback = callback,
		.data = data,
		.retval = 0,
	पूर्ण;
	Dwarf_Die die_mem;
	Dwarf_Addr addr;
	स्थिर अक्षर *fname;
	पूर्णांक lineno;

	/* Handle function declaration line */
	fname = dwarf_decl_file(sp_die);
	अगर (fname && dwarf_decl_line(sp_die, &lineno) == 0 &&
	    die_entrypc(sp_die, &addr) == 0) अणु
		lw.retval = callback(fname, lineno, addr, data);
		अगर (lw.retval != 0)
			जाओ करोne;
	पूर्ण
	die_find_child(sp_die, __die_walk_funclines_cb, &lw, &die_mem);
करोne:
	वापस lw.retval;
पूर्ण

अटल पूर्णांक __die_walk_culines_cb(Dwarf_Die *sp_die, व्योम *data)
अणु
	काष्ठा __line_walk_param *lw = data;

	/*
	 * Since अंतरभूतd function can include another अंतरभूतd function in
	 * the same file, we need to walk in it recursively.
	 */
	lw->retval = __die_walk_funclines(sp_die, true, lw->callback, lw->data);
	अगर (lw->retval != 0)
		वापस DWARF_CB_ABORT;

	वापस DWARF_CB_OK;
पूर्ण

/**
 * die_walk_lines - Walk on lines inside given DIE
 * @rt_die: a root DIE (CU, subprogram or अंतरभूतd_subroutine)
 * @callback: callback routine
 * @data: user data
 *
 * Walk on all lines inside given @rt_die and call @callback on each line.
 * If the @rt_die is a function, walk only on the lines inside the function,
 * otherwise @rt_die must be a CU DIE.
 * Note that this walks not only dwarf line list, but also function entries
 * and अंतरभूत call-site.
 */
पूर्णांक die_walk_lines(Dwarf_Die *rt_die, line_walk_callback_t callback, व्योम *data)
अणु
	Dwarf_Lines *lines;
	Dwarf_Line *line;
	Dwarf_Addr addr;
	स्थिर अक्षर *fname, *decf = शून्य, *inf = शून्य;
	पूर्णांक lineno, ret = 0;
	पूर्णांक decl = 0, inl;
	Dwarf_Die die_mem, *cu_die;
	माप_प्रकार nlines, i;
	bool flag;

	/* Get the CU die */
	अगर (dwarf_tag(rt_die) != DW_TAG_compile_unit) अणु
		cu_die = dwarf_diecu(rt_die, &die_mem, शून्य, शून्य);
		dwarf_decl_line(rt_die, &decl);
		decf = dwarf_decl_file(rt_die);
	पूर्ण अन्यथा
		cu_die = rt_die;
	अगर (!cu_die) अणु
		pr_debug2("Failed to get CU from given DIE.\n");
		वापस -EINVAL;
	पूर्ण

	/* Get lines list in the CU */
	अगर (dwarf_माला_लोrclines(cu_die, &lines, &nlines) != 0) अणु
		pr_debug2("Failed to get source lines on this CU.\n");
		वापस -ENOENT;
	पूर्ण
	pr_debug2("Get %zd lines from this CU\n", nlines);

	/* Walk on the lines on lines list */
	क्रम (i = 0; i < nlines; i++) अणु
		line = dwarf_onesrcline(lines, i);
		अगर (line == शून्य ||
		    dwarf_lineno(line, &lineno) != 0 ||
		    dwarf_lineaddr(line, &addr) != 0) अणु
			pr_debug2("Failed to get line info. "
				  "Possible error in debuginfo.\n");
			जारी;
		पूर्ण
		/* Skip end-of-sequence */
		अगर (dwarf_lineendsequence(line, &flag) != 0 || flag)
			जारी;
		/* Skip Non statement line-info */
		अगर (dwarf_linebeginstatement(line, &flag) != 0 || !flag)
			जारी;
		/* Filter lines based on address */
		अगर (rt_die != cu_die) अणु
			/*
			 * Address filtering
			 * The line is included in given function, and
			 * no अंतरभूत block includes it.
			 */
			अगर (!dwarf_haspc(rt_die, addr))
				जारी;

			अगर (die_find_अंतरभूतfunc(rt_die, addr, &die_mem)) अणु
				/* Call-site check */
				inf = die_get_call_file(&die_mem);
				अगर ((inf && !म_भेद(inf, decf)) &&
				    die_get_call_lineno(&die_mem) == lineno)
					जाओ found;

				dwarf_decl_line(&die_mem, &inl);
				अगर (inl != decl ||
				    decf != dwarf_decl_file(&die_mem))
					जारी;
			पूर्ण
		पूर्ण
found:
		/* Get source line */
		fname = dwarf_linesrc(line, शून्य, शून्य);

		ret = callback(fname, lineno, addr, data);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	/*
	 * Dwarf lines करोesn't include function declarations and अंतरभूतd
	 * subroutines. We have to check functions list or given function.
	 */
	अगर (rt_die != cu_die)
		/*
		 * Don't need walk अंतरभूतd functions recursively, because
		 * inner अंतरभूतd functions करोn't have the lines of the
		 * specअगरied function.
		 */
		ret = __die_walk_funclines(rt_die, false, callback, data);
	अन्यथा अणु
		काष्ठा __line_walk_param param = अणु
			.callback = callback,
			.data = data,
			.retval = 0,
		पूर्ण;
		dwarf_getfuncs(cu_die, __die_walk_culines_cb, &param, 0);
		ret = param.retval;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा __find_variable_param अणु
	स्थिर अक्षर *name;
	Dwarf_Addr addr;
पूर्ण;

अटल पूर्णांक __die_find_variable_cb(Dwarf_Die *die_mem, व्योम *data)
अणु
	काष्ठा __find_variable_param *fvp = data;
	Dwarf_Attribute attr;
	पूर्णांक tag;

	tag = dwarf_tag(die_mem);
	अगर ((tag == DW_TAG_क्रमmal_parameter ||
	     tag == DW_TAG_variable) &&
	    die_compare_name(die_mem, fvp->name) &&
	/*
	 * Does the DIE have location inक्रमmation or स्थिर value
	 * or बाह्यal instance?
	 */
	    (dwarf_attr(die_mem, DW_AT_बाह्यal, &attr) ||
	     dwarf_attr(die_mem, DW_AT_location, &attr) ||
	     dwarf_attr(die_mem, DW_AT_स्थिर_value, &attr)))
		वापस DIE_FIND_CB_END;
	अगर (dwarf_haspc(die_mem, fvp->addr))
		वापस DIE_FIND_CB_CONTINUE;
	अन्यथा
		वापस DIE_FIND_CB_SIBLING;
पूर्ण

/**
 * die_find_variable_at - Find a given name variable at given address
 * @sp_die: a function DIE
 * @name: variable name
 * @addr: address
 * @die_mem: a buffer क्रम result DIE
 *
 * Find a variable DIE called @name at @addr in @sp_die.
 */
Dwarf_Die *die_find_variable_at(Dwarf_Die *sp_die, स्थिर अक्षर *name,
				Dwarf_Addr addr, Dwarf_Die *die_mem)
अणु
	काष्ठा __find_variable_param fvp = अणु .name = name, .addr = addrपूर्ण;

	वापस die_find_child(sp_die, __die_find_variable_cb, (व्योम *)&fvp,
			      die_mem);
पूर्ण

अटल पूर्णांक __die_find_member_cb(Dwarf_Die *die_mem, व्योम *data)
अणु
	स्थिर अक्षर *name = data;

	अगर (dwarf_tag(die_mem) == DW_TAG_member) अणु
		अगर (die_compare_name(die_mem, name))
			वापस DIE_FIND_CB_END;
		अन्यथा अगर (!dwarf_diename(die_mem)) अणु	/* Unnamed काष्ठाure */
			Dwarf_Die type_die, पंचांगp_die;
			अगर (die_get_type(die_mem, &type_die) &&
			    die_find_member(&type_die, name, &पंचांगp_die))
				वापस DIE_FIND_CB_END;
		पूर्ण
	पूर्ण
	वापस DIE_FIND_CB_SIBLING;
पूर्ण

/**
 * die_find_member - Find a given name member in a data काष्ठाure
 * @st_die: a data काष्ठाure type DIE
 * @name: member name
 * @die_mem: a buffer क्रम result DIE
 *
 * Find a member DIE called @name in @st_die.
 */
Dwarf_Die *die_find_member(Dwarf_Die *st_die, स्थिर अक्षर *name,
			   Dwarf_Die *die_mem)
अणु
	वापस die_find_child(st_die, __die_find_member_cb, (व्योम *)name,
			      die_mem);
पूर्ण

/**
 * die_get_typename - Get the name of given variable DIE
 * @vr_die: a variable DIE
 * @buf: a strbuf क्रम result type name
 *
 * Get the name of @vr_die and stores it to @buf. Return 0 अगर succeeded.
 * and Return -ENOENT अगर failed to find type name.
 * Note that the result will stores प्रकार name अगर possible, and stores
 * "*(function_type)" अगर the type is a function poपूर्णांकer.
 */
पूर्णांक die_get_typename(Dwarf_Die *vr_die, काष्ठा strbuf *buf)
अणु
	Dwarf_Die type;
	पूर्णांक tag, ret;
	स्थिर अक्षर *पंचांगp = "";

	अगर (__die_get_real_type(vr_die, &type) == शून्य)
		वापस -ENOENT;

	tag = dwarf_tag(&type);
	अगर (tag == DW_TAG_array_type || tag == DW_TAG_poपूर्णांकer_type)
		पंचांगp = "*";
	अन्यथा अगर (tag == DW_TAG_subroutine_type) अणु
		/* Function poपूर्णांकer */
		वापस strbuf_add(buf, "(function_type)", 15);
	पूर्ण अन्यथा अणु
		अगर (!dwarf_diename(&type))
			वापस -ENOENT;
		अगर (tag == DW_TAG_जोड़_type)
			पंचांगp = "union ";
		अन्यथा अगर (tag == DW_TAG_काष्ठाure_type)
			पंचांगp = "struct ";
		अन्यथा अगर (tag == DW_TAG_क्रमागतeration_type)
			पंचांगp = "enum ";
		/* Write a base name */
		वापस strbuf_addf(buf, "%s%s", पंचांगp, dwarf_diename(&type));
	पूर्ण
	ret = die_get_typename(&type, buf);
	वापस ret ? ret : strbuf_addstr(buf, पंचांगp);
पूर्ण

/**
 * die_get_varname - Get the name and type of given variable DIE
 * @vr_die: a variable DIE
 * @buf: a strbuf क्रम type and variable name
 *
 * Get the name and type of @vr_die and stores it in @buf as "type\tname".
 */
पूर्णांक die_get_varname(Dwarf_Die *vr_die, काष्ठा strbuf *buf)
अणु
	पूर्णांक ret;

	ret = die_get_typename(vr_die, buf);
	अगर (ret < 0) अणु
		pr_debug("Failed to get type, make it unknown.\n");
		ret = strbuf_add(buf, " (unknown_type)", 14);
	पूर्ण

	वापस ret < 0 ? ret : strbuf_addf(buf, "\t%s", dwarf_diename(vr_die));
पूर्ण

#अगर_घोषित HAVE_DWARF_GETLOCATIONS_SUPPORT
/**
 * die_get_var_innermost_scope - Get innermost scope range of given variable DIE
 * @sp_die: a subprogram DIE
 * @vr_die: a variable DIE
 * @buf: a strbuf क्रम variable byte offset range
 *
 * Get the innermost scope range of @vr_die and stores it in @buf as
 * "@<function_name+[NN-NN,NN-NN]>".
 */
अटल पूर्णांक die_get_var_innermost_scope(Dwarf_Die *sp_die, Dwarf_Die *vr_die,
				काष्ठा strbuf *buf)
अणु
	Dwarf_Die *scopes;
	पूर्णांक count;
	माप_प्रकार offset = 0;
	Dwarf_Addr base;
	Dwarf_Addr start, end;
	Dwarf_Addr entry;
	पूर्णांक ret;
	bool first = true;
	स्थिर अक्षर *name;

	ret = die_entrypc(sp_die, &entry);
	अगर (ret)
		वापस ret;

	name = dwarf_diename(sp_die);
	अगर (!name)
		वापस -ENOENT;

	count = dwarf_माला_लोcopes_die(vr_die, &scopes);

	/* (*SCOPES)[1] is the DIE क्रम the scope containing that scope */
	अगर (count <= 1) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	जबतक ((offset = dwarf_ranges(&scopes[1], offset, &base,
					&start, &end)) > 0) अणु
		start -= entry;
		end -= entry;

		अगर (first) अणु
			ret = strbuf_addf(buf, "@<%s+[%" PRIu64 "-%" PRIu64,
					  name, start, end);
			first = false;
		पूर्ण अन्यथा अणु
			ret = strbuf_addf(buf, ",%" PRIu64 "-%" PRIu64,
					  start, end);
		पूर्ण
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (!first)
		ret = strbuf_add(buf, "]>", 2);

out:
	मुक्त(scopes);
	वापस ret;
पूर्ण

/**
 * die_get_var_range - Get byte offset range of given variable DIE
 * @sp_die: a subprogram DIE
 * @vr_die: a variable DIE
 * @buf: a strbuf क्रम type and variable name and byte offset range
 *
 * Get the byte offset range of @vr_die and stores it in @buf as
 * "@<function_name+[NN-NN,NN-NN]>".
 */
पूर्णांक die_get_var_range(Dwarf_Die *sp_die, Dwarf_Die *vr_die, काष्ठा strbuf *buf)
अणु
	पूर्णांक ret = 0;
	Dwarf_Addr base;
	Dwarf_Addr start, end;
	Dwarf_Addr entry;
	Dwarf_Op *op;
	माप_प्रकार nops;
	माप_प्रकार offset = 0;
	Dwarf_Attribute attr;
	bool first = true;
	स्थिर अक्षर *name;

	ret = die_entrypc(sp_die, &entry);
	अगर (ret)
		वापस ret;

	name = dwarf_diename(sp_die);
	अगर (!name)
		वापस -ENOENT;

	अगर (dwarf_attr(vr_die, DW_AT_location, &attr) == शून्य)
		वापस -EINVAL;

	जबतक ((offset = dwarf_getlocations(&attr, offset, &base,
					&start, &end, &op, &nops)) > 0) अणु
		अगर (start == 0) अणु
			/* Single Location Descriptions */
			ret = die_get_var_innermost_scope(sp_die, vr_die, buf);
			जाओ out;
		पूर्ण

		/* Location Lists */
		start -= entry;
		end -= entry;
		अगर (first) अणु
			ret = strbuf_addf(buf, "@<%s+[%" PRIu64 "-%" PRIu64,
					  name, start, end);
			first = false;
		पूर्ण अन्यथा अणु
			ret = strbuf_addf(buf, ",%" PRIu64 "-%" PRIu64,
					  start, end);
		पूर्ण
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (!first)
		ret = strbuf_add(buf, "]>", 2);
out:
	वापस ret;
पूर्ण
#अन्यथा
पूर्णांक die_get_var_range(Dwarf_Die *sp_die __maybe_unused,
		      Dwarf_Die *vr_die __maybe_unused,
		      काष्ठा strbuf *buf __maybe_unused)
अणु
	वापस -ENOTSUP;
पूर्ण
#पूर्ण_अगर

/*
 * die_has_loclist - Check अगर DW_AT_location of @vr_die is a location list
 * @vr_die: a variable DIE
 */
अटल bool die_has_loclist(Dwarf_Die *vr_die)
अणु
	Dwarf_Attribute loc;
	पूर्णांक tag = dwarf_tag(vr_die);

	अगर (tag != DW_TAG_क्रमmal_parameter &&
	    tag != DW_TAG_variable)
		वापस false;

	वापस (dwarf_attr_पूर्णांकegrate(vr_die, DW_AT_location, &loc) &&
		dwarf_whatक्रमm(&loc) == DW_FORM_sec_offset);
पूर्ण

/*
 * die_is_optimized_target - Check अगर target program is compiled with
 * optimization
 * @cu_die: a CU DIE
 *
 * For any object in given CU whose DW_AT_location is a location list,
 * target program is compiled with optimization. This is applicable to
 * clang as well.
 */
bool die_is_optimized_target(Dwarf_Die *cu_die)
अणु
	Dwarf_Die पंचांगp_die;

	अगर (die_has_loclist(cu_die))
		वापस true;

	अगर (!dwarf_child(cu_die, &पंचांगp_die) &&
	    die_is_optimized_target(&पंचांगp_die))
		वापस true;

	अगर (!dwarf_siblingof(cu_die, &पंचांगp_die) &&
	    die_is_optimized_target(&पंचांगp_die))
		वापस true;

	वापस false;
पूर्ण

/*
 * die_search_idx - Search index of given line address
 * @lines: Line records of single CU
 * @nr_lines: Number of @lines
 * @addr: address we are looking क्रम
 * @idx: index to be set by this function (वापस value)
 *
 * Search क्रम @addr by looping over every lines of CU. If address
 * matches, set index of that line in @idx. Note that single source
 * line can have multiple line records. i.e. single source line can
 * have multiple index.
 */
अटल bool die_search_idx(Dwarf_Lines *lines, अचिन्हित दीर्घ nr_lines,
			   Dwarf_Addr addr, अचिन्हित दीर्घ *idx)
अणु
	अचिन्हित दीर्घ i;
	Dwarf_Addr पंचांगp;

	क्रम (i = 0; i < nr_lines; i++) अणु
		अगर (dwarf_lineaddr(dwarf_onesrcline(lines, i), &पंचांगp))
			वापस false;

		अगर (पंचांगp == addr) अणु
			*idx = i;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/*
 * die_get_postprologue_addr - Search next address after function prologue
 * @entrypc_idx: entrypc index
 * @lines: Line records of single CU
 * @nr_lines: Number of @lines
 * @hignpc: high PC address of function
 * @postprologue_addr: Next address after function prologue (वापस value)
 *
 * Look क्रम prologue-end marker. If there is no explicit marker, वापस
 * address of next line record or next source line.
 */
अटल bool die_get_postprologue_addr(अचिन्हित दीर्घ entrypc_idx,
				      Dwarf_Lines *lines,
				      अचिन्हित दीर्घ nr_lines,
				      Dwarf_Addr highpc,
				      Dwarf_Addr *postprologue_addr)
अणु
	अचिन्हित दीर्घ i;
	पूर्णांक entrypc_lno, lno;
	Dwarf_Line *line;
	Dwarf_Addr addr;
	bool p_end;

	/* entrypc_lno is actual source line number */
	line = dwarf_onesrcline(lines, entrypc_idx);
	अगर (dwarf_lineno(line, &entrypc_lno))
		वापस false;

	क्रम (i = entrypc_idx; i < nr_lines; i++) अणु
		line = dwarf_onesrcline(lines, i);

		अगर (dwarf_lineaddr(line, &addr) ||
		    dwarf_lineno(line, &lno)    ||
		    dwarf_lineprologueend(line, &p_end))
			वापस false;

		/* highpc is exclusive. [entrypc,highpc) */
		अगर (addr >= highpc)
			अवरोध;

		/* clang supports prologue-end marker */
		अगर (p_end)
			अवरोध;

		/* Actual next line in source */
		अगर (lno != entrypc_lno)
			अवरोध;

		/*
		 * Single source line can have multiple line records.
		 * For Example,
		 *     व्योम foo() अणु म_लिखो("hello\n"); पूर्ण
		 * contains two line records. One poपूर्णांकs to declaration and
		 * other poपूर्णांकs to म_लिखो() line. Variable 'lno' won't get
		 * incremented in this हाल but 'i' will.
		 */
		अगर (i != entrypc_idx)
			अवरोध;
	पूर्ण

	dwarf_lineaddr(line, postprologue_addr);
	अगर (*postprologue_addr >= highpc)
		dwarf_lineaddr(dwarf_onesrcline(lines, i - 1),
			       postprologue_addr);

	वापस true;
पूर्ण

/*
 * die_skip_prologue - Use next address after prologue as probe location
 * @sp_die: a subprogram DIE
 * @cu_die: a CU DIE
 * @entrypc: entrypc of the function
 *
 * Function prologue prepares stack and रेजिस्टरs beक्रमe executing function
 * logic. When target program is compiled without optimization, function
 * parameter inक्रमmation is only valid after prologue. When we probe entrypc
 * of the function, and try to record function parameter, it contains
 * garbage value.
 */
व्योम die_skip_prologue(Dwarf_Die *sp_die, Dwarf_Die *cu_die,
		       Dwarf_Addr *entrypc)
अणु
	माप_प्रकार nr_lines = 0;
	अचिन्हित दीर्घ entrypc_idx = 0;
	Dwarf_Lines *lines = शून्य;
	Dwarf_Addr postprologue_addr;
	Dwarf_Addr highpc;

	अगर (dwarf_highpc(sp_die, &highpc))
		वापस;

	अगर (dwarf_माला_लोrclines(cu_die, &lines, &nr_lines))
		वापस;

	अगर (!die_search_idx(lines, nr_lines, *entrypc, &entrypc_idx))
		वापस;

	अगर (!die_get_postprologue_addr(entrypc_idx, lines, nr_lines,
				       highpc, &postprologue_addr))
		वापस;

	*entrypc = postprologue_addr;
पूर्ण
