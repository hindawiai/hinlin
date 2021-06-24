<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * probe-finder.c : C expression to kprobe event converter
 *
 * Written by Masami Hiramatsu <mhiramat@redhat.com>
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <sys/utsname.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <dwarf-regs.h>

#समावेश <linux/bitops.h>
#समावेश <linux/zभाग.स>
#समावेश "event.h"
#समावेश "dso.h"
#समावेश "debug.h"
#समावेश "intlist.h"
#समावेश "strbuf.h"
#समावेश "strlist.h"
#समावेश "symbol.h"
#समावेश "probe-finder.h"
#समावेश "probe-file.h"
#समावेश "string2.h"

#अगर_घोषित HAVE_DEBUGINFOD_SUPPORT
#समावेश <elfutils/debuginfod.h>
#पूर्ण_अगर

/* Kprobe tracer basic type is up to u64 */
#घोषणा MAX_BASIC_TYPE_BITS	64

/* Dwarf FL wrappers */
अटल अक्षर *debuginfo_path;	/* Currently dummy */

अटल स्थिर Dwfl_Callbacks offline_callbacks = अणु
	.find_debuginfo = dwfl_standard_find_debuginfo,
	.debuginfo_path = &debuginfo_path,

	.section_address = dwfl_offline_section_address,

	/* We use this table क्रम core files too.  */
	.find_elf = dwfl_build_id_find_elf,
पूर्ण;

/* Get a Dwarf from offline image */
अटल पूर्णांक debuginfo__init_offline_dwarf(काष्ठा debuginfo *dbg,
					 स्थिर अक्षर *path)
अणु
	GElf_Addr dummy;
	पूर्णांक fd;

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0)
		वापस fd;

	dbg->dwfl = dwfl_begin(&offline_callbacks);
	अगर (!dbg->dwfl)
		जाओ error;

	dwfl_report_begin(dbg->dwfl);
	dbg->mod = dwfl_report_offline(dbg->dwfl, "", "", fd);
	अगर (!dbg->mod)
		जाओ error;

	dbg->dbg = dwfl_module_getdwarf(dbg->mod, &dbg->bias);
	अगर (!dbg->dbg)
		जाओ error;

	dwfl_module_build_id(dbg->mod, &dbg->build_id, &dummy);

	dwfl_report_end(dbg->dwfl, शून्य, शून्य);

	वापस 0;
error:
	अगर (dbg->dwfl)
		dwfl_end(dbg->dwfl);
	अन्यथा
		बंद(fd);
	स_रखो(dbg, 0, माप(*dbg));

	वापस -ENOENT;
पूर्ण

अटल काष्ठा debuginfo *__debuginfo__new(स्थिर अक्षर *path)
अणु
	काष्ठा debuginfo *dbg = zalloc(माप(*dbg));
	अगर (!dbg)
		वापस शून्य;

	अगर (debuginfo__init_offline_dwarf(dbg, path) < 0)
		zमुक्त(&dbg);
	अगर (dbg)
		pr_debug("Open Debuginfo file: %s\n", path);
	वापस dbg;
पूर्ण

क्रमागत dso_binary_type distro_dwarf_types[] = अणु
	DSO_BINARY_TYPE__FEDORA_DEBUGINFO,
	DSO_BINARY_TYPE__UBUNTU_DEBUGINFO,
	DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO,
	DSO_BINARY_TYPE__BUILDID_DEBUGINFO,
	DSO_BINARY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO,
	DSO_BINARY_TYPE__NOT_FOUND,
पूर्ण;

काष्ठा debuginfo *debuginfo__new(स्थिर अक्षर *path)
अणु
	क्रमागत dso_binary_type *type;
	अक्षर buf[PATH_MAX], nil = '\0';
	काष्ठा dso *dso;
	काष्ठा debuginfo *dinfo = शून्य;

	/* Try to खोलो distro debuginfo files */
	dso = dso__new(path);
	अगर (!dso)
		जाओ out;

	क्रम (type = distro_dwarf_types;
	     !dinfo && *type != DSO_BINARY_TYPE__NOT_FOUND;
	     type++) अणु
		अगर (dso__पढ़ो_binary_type_filename(dso, *type, &nil,
						   buf, PATH_MAX) < 0)
			जारी;
		dinfo = __debuginfo__new(buf);
	पूर्ण
	dso__put(dso);

out:
	/* अगर failed to खोलो all distro debuginfo, खोलो given binary */
	वापस dinfo ? : __debuginfo__new(path);
पूर्ण

व्योम debuginfo__delete(काष्ठा debuginfo *dbg)
अणु
	अगर (dbg) अणु
		अगर (dbg->dwfl)
			dwfl_end(dbg->dwfl);
		मुक्त(dbg);
	पूर्ण
पूर्ण

/*
 * Probe finder related functions
 */

अटल काष्ठा probe_trace_arg_ref *alloc_trace_arg_ref(दीर्घ offs)
अणु
	काष्ठा probe_trace_arg_ref *ref;
	ref = zalloc(माप(काष्ठा probe_trace_arg_ref));
	अगर (ref != शून्य)
		ref->offset = offs;
	वापस ref;
पूर्ण

/*
 * Convert a location पूर्णांकo trace_arg.
 * If tvar == शून्य, this just checks variable can be converted.
 * If fentry == true and vr_die is a parameter, करो heuristic search
 * क्रम the location fuzzed by function entry mcount.
 */
अटल पूर्णांक convert_variable_location(Dwarf_Die *vr_die, Dwarf_Addr addr,
				     Dwarf_Op *fb_ops, Dwarf_Die *sp_die,
				     अचिन्हित पूर्णांक machine,
				     काष्ठा probe_trace_arg *tvar)
अणु
	Dwarf_Attribute attr;
	Dwarf_Addr पंचांगp = 0;
	Dwarf_Op *op;
	माप_प्रकार nops;
	अचिन्हित पूर्णांक regn;
	Dwarf_Word offs = 0;
	bool ref = false;
	स्थिर अक्षर *regs;
	पूर्णांक ret, ret2 = 0;

	अगर (dwarf_attr(vr_die, DW_AT_बाह्यal, &attr) != शून्य)
		जाओ अटल_var;

	/* Constant value */
	अगर (dwarf_attr(vr_die, DW_AT_स्थिर_value, &attr) &&
	    immediate_value_is_supported()) अणु
		Dwarf_Sword snum;

		अगर (!tvar)
			वापस 0;

		dwarf_क्रमmsdata(&attr, &snum);
		ret = aप्र_लिखो(&tvar->value, "\\%ld", (दीर्घ)snum);

		वापस ret < 0 ? -ENOMEM : 0;
	पूर्ण

	/* TODO: handle more than 1 exprs */
	अगर (dwarf_attr(vr_die, DW_AT_location, &attr) == शून्य)
		वापस -EINVAL;	/* Broken DIE ? */
	अगर (dwarf_getlocation_addr(&attr, addr, &op, &nops, 1) <= 0) अणु
		ret = dwarf_entrypc(sp_die, &पंचांगp);
		अगर (ret)
			वापस -ENOENT;

		अगर (probe_conf.show_location_range &&
			(dwarf_tag(vr_die) == DW_TAG_variable)) अणु
			ret2 = -दुस्फल;
		पूर्ण अन्यथा अगर (addr != पंचांगp ||
			dwarf_tag(vr_die) != DW_TAG_क्रमmal_parameter) अणु
			वापस -ENOENT;
		पूर्ण

		ret = dwarf_highpc(sp_die, &पंचांगp);
		अगर (ret)
			वापस -ENOENT;
		/*
		 * This is fuzzed by fentry mcount. We try to find the
		 * parameter location at the earliest address.
		 */
		क्रम (addr += 1; addr <= पंचांगp; addr++) अणु
			अगर (dwarf_getlocation_addr(&attr, addr, &op,
						   &nops, 1) > 0)
				जाओ found;
		पूर्ण
		वापस -ENOENT;
	पूर्ण
found:
	अगर (nops == 0)
		/* TODO: Support स्थिर_value */
		वापस -ENOENT;

	अगर (op->atom == DW_OP_addr) अणु
अटल_var:
		अगर (!tvar)
			वापस ret2;
		/* Static variables on memory (not stack), make @varname */
		ret = म_माप(dwarf_diename(vr_die));
		tvar->value = zalloc(ret + 2);
		अगर (tvar->value == शून्य)
			वापस -ENOMEM;
		snम_लिखो(tvar->value, ret + 2, "@%s", dwarf_diename(vr_die));
		tvar->ref = alloc_trace_arg_ref((दीर्घ)offs);
		अगर (tvar->ref == शून्य)
			वापस -ENOMEM;
		वापस ret2;
	पूर्ण

	/* If this is based on frame buffer, set the offset */
	अगर (op->atom == DW_OP_fbreg) अणु
		अगर (fb_ops == शून्य)
			वापस -ENOTSUP;
		ref = true;
		offs = op->number;
		op = &fb_ops[0];
	पूर्ण

	अगर (op->atom >= DW_OP_breg0 && op->atom <= DW_OP_breg31) अणु
		regn = op->atom - DW_OP_breg0;
		offs += op->number;
		ref = true;
	पूर्ण अन्यथा अगर (op->atom >= DW_OP_reg0 && op->atom <= DW_OP_reg31) अणु
		regn = op->atom - DW_OP_reg0;
	पूर्ण अन्यथा अगर (op->atom == DW_OP_bregx) अणु
		regn = op->number;
		offs += op->number2;
		ref = true;
	पूर्ण अन्यथा अगर (op->atom == DW_OP_regx) अणु
		regn = op->number;
	पूर्ण अन्यथा अणु
		pr_debug("DW_OP %x is not supported.\n", op->atom);
		वापस -ENOTSUP;
	पूर्ण

	अगर (!tvar)
		वापस ret2;

	regs = get_dwarf_regstr(regn, machine);
	अगर (!regs) अणु
		/* This should be a bug in DWARF or this tool */
		pr_warning("Mapping for the register number %u "
			   "missing on this architecture.\n", regn);
		वापस -ENOTSUP;
	पूर्ण

	tvar->value = strdup(regs);
	अगर (tvar->value == शून्य)
		वापस -ENOMEM;

	अगर (ref) अणु
		tvar->ref = alloc_trace_arg_ref((दीर्घ)offs);
		अगर (tvar->ref == शून्य)
			वापस -ENOMEM;
	पूर्ण
	वापस ret2;
पूर्ण

#घोषणा BYTES_TO_BITS(nb)	((nb) * BITS_PER_LONG / माप(दीर्घ))

अटल पूर्णांक convert_variable_type(Dwarf_Die *vr_die,
				 काष्ठा probe_trace_arg *tvar,
				 स्थिर अक्षर *cast, bool user_access)
अणु
	काष्ठा probe_trace_arg_ref **ref_ptr = &tvar->ref;
	Dwarf_Die type;
	अक्षर buf[16];
	अक्षर sbuf[STRERR_बफ_मानE];
	पूर्णांक bsize, boffs, total;
	पूर्णांक ret;
	अक्षर prefix;

	/* TODO: check all types */
	अगर (cast && म_भेद(cast, "string") != 0 && म_भेद(cast, "ustring") &&
	    म_भेद(cast, "x") != 0 &&
	    म_भेद(cast, "s") != 0 && म_भेद(cast, "u") != 0) अणु
		/* Non string type is OK */
		/* and respect चिन्हितness/hexadecimal cast */
		tvar->type = strdup(cast);
		वापस (tvar->type == शून्य) ? -ENOMEM : 0;
	पूर्ण

	bsize = dwarf_bitsize(vr_die);
	अगर (bsize > 0) अणु
		/* This is a bitfield */
		boffs = dwarf_bitoffset(vr_die);
		total = dwarf_bytesize(vr_die);
		अगर (boffs < 0 || total < 0)
			वापस -ENOENT;
		ret = snम_लिखो(buf, 16, "b%d@%d/%zd", bsize, boffs,
				BYTES_TO_BITS(total));
		जाओ क्रमmatted;
	पूर्ण

	अगर (die_get_real_type(vr_die, &type) == शून्य) अणु
		pr_warning("Failed to get a type information of %s.\n",
			   dwarf_diename(vr_die));
		वापस -ENOENT;
	पूर्ण

	pr_debug("%s type is %s.\n",
		 dwarf_diename(vr_die), dwarf_diename(&type));

	अगर (cast && (!म_भेद(cast, "string") || !म_भेद(cast, "ustring"))) अणु
		/* String type */
		ret = dwarf_tag(&type);
		अगर (ret != DW_TAG_poपूर्णांकer_type &&
		    ret != DW_TAG_array_type) अणु
			pr_warning("Failed to cast into string: "
				   "%s(%s) is not a pointer nor array.\n",
				   dwarf_diename(vr_die), dwarf_diename(&type));
			वापस -EINVAL;
		पूर्ण
		अगर (die_get_real_type(&type, &type) == शून्य) अणु
			pr_warning("Failed to get a type"
				   " information.\n");
			वापस -ENOENT;
		पूर्ण
		अगर (ret == DW_TAG_poपूर्णांकer_type) अणु
			जबतक (*ref_ptr)
				ref_ptr = &(*ref_ptr)->next;
			/* Add new reference with offset +0 */
			*ref_ptr = zalloc(माप(काष्ठा probe_trace_arg_ref));
			अगर (*ref_ptr == शून्य) अणु
				pr_warning("Out of memory error\n");
				वापस -ENOMEM;
			पूर्ण
			(*ref_ptr)->user_access = user_access;
		पूर्ण
		अगर (!die_compare_name(&type, "char") &&
		    !die_compare_name(&type, "unsigned char")) अणु
			pr_warning("Failed to cast into string: "
				   "%s is not (unsigned) char *.\n",
				   dwarf_diename(vr_die));
			वापस -EINVAL;
		पूर्ण
		tvar->type = strdup(cast);
		वापस (tvar->type == शून्य) ? -ENOMEM : 0;
	पूर्ण

	अगर (cast && (म_भेद(cast, "u") == 0))
		prefix = 'u';
	अन्यथा अगर (cast && (म_भेद(cast, "s") == 0))
		prefix = 's';
	अन्यथा अगर (cast && (म_भेद(cast, "x") == 0) &&
		 probe_type_is_available(PROBE_TYPE_X))
		prefix = 'x';
	अन्यथा
		prefix = die_is_चिन्हित_type(&type) ? 's' :
			 probe_type_is_available(PROBE_TYPE_X) ? 'x' : 'u';

	ret = dwarf_bytesize(&type);
	अगर (ret <= 0)
		/* No size ... try to use शेष type */
		वापस 0;
	ret = BYTES_TO_BITS(ret);

	/* Check the bitwidth */
	अगर (ret > MAX_BASIC_TYPE_BITS) अणु
		pr_info("%s exceeds max-bitwidth. Cut down to %d bits.\n",
			dwarf_diename(&type), MAX_BASIC_TYPE_BITS);
		ret = MAX_BASIC_TYPE_BITS;
	पूर्ण
	ret = snम_लिखो(buf, 16, "%c%d", prefix, ret);

क्रमmatted:
	अगर (ret < 0 || ret >= 16) अणु
		अगर (ret >= 16)
			ret = -E2BIG;
		pr_warning("Failed to convert variable type: %s\n",
			   str_error_r(-ret, sbuf, माप(sbuf)));
		वापस ret;
	पूर्ण
	tvar->type = strdup(buf);
	अगर (tvar->type == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक convert_variable_fields(Dwarf_Die *vr_die, स्थिर अक्षर *varname,
				    काष्ठा perf_probe_arg_field *field,
				    काष्ठा probe_trace_arg_ref **ref_ptr,
				    Dwarf_Die *die_mem, bool user_access)
अणु
	काष्ठा probe_trace_arg_ref *ref = *ref_ptr;
	Dwarf_Die type;
	Dwarf_Word offs;
	पूर्णांक ret, tag;

	pr_debug("converting %s in %s\n", field->name, varname);
	अगर (die_get_real_type(vr_die, &type) == शून्य) अणु
		pr_warning("Failed to get the type of %s.\n", varname);
		वापस -ENOENT;
	पूर्ण
	pr_debug2("Var real type: %s (%x)\n", dwarf_diename(&type),
		  (अचिन्हित)dwarf_dieoffset(&type));
	tag = dwarf_tag(&type);

	अगर (field->name[0] == '[' &&
	    (tag == DW_TAG_array_type || tag == DW_TAG_poपूर्णांकer_type)) अणु
		/* Save original type क्रम next field or type */
		स_नकल(die_mem, &type, माप(*die_mem));
		/* Get the type of this array */
		अगर (die_get_real_type(&type, &type) == शून्य) अणु
			pr_warning("Failed to get the type of %s.\n", varname);
			वापस -ENOENT;
		पूर्ण
		pr_debug2("Array real type: %s (%x)\n", dwarf_diename(&type),
			 (अचिन्हित)dwarf_dieoffset(&type));
		अगर (tag == DW_TAG_poपूर्णांकer_type) अणु
			ref = zalloc(माप(काष्ठा probe_trace_arg_ref));
			अगर (ref == शून्य)
				वापस -ENOMEM;
			अगर (*ref_ptr)
				(*ref_ptr)->next = ref;
			अन्यथा
				*ref_ptr = ref;
		पूर्ण
		ref->offset += dwarf_bytesize(&type) * field->index;
		ref->user_access = user_access;
		जाओ next;
	पूर्ण अन्यथा अगर (tag == DW_TAG_poपूर्णांकer_type) अणु
		/* Check the poपूर्णांकer and dereference */
		अगर (!field->ref) अणु
			pr_err("Semantic error: %s must be referred by '->'\n",
			       field->name);
			वापस -EINVAL;
		पूर्ण
		/* Get the type poपूर्णांकed by this poपूर्णांकer */
		अगर (die_get_real_type(&type, &type) == शून्य) अणु
			pr_warning("Failed to get the type of %s.\n", varname);
			वापस -ENOENT;
		पूर्ण
		/* Verअगरy it is a data काष्ठाure  */
		tag = dwarf_tag(&type);
		अगर (tag != DW_TAG_काष्ठाure_type && tag != DW_TAG_जोड़_type) अणु
			pr_warning("%s is not a data structure nor a union.\n",
				   varname);
			वापस -EINVAL;
		पूर्ण

		ref = zalloc(माप(काष्ठा probe_trace_arg_ref));
		अगर (ref == शून्य)
			वापस -ENOMEM;
		अगर (*ref_ptr)
			(*ref_ptr)->next = ref;
		अन्यथा
			*ref_ptr = ref;
	पूर्ण अन्यथा अणु
		/* Verअगरy it is a data काष्ठाure  */
		अगर (tag != DW_TAG_काष्ठाure_type && tag != DW_TAG_जोड़_type) अणु
			pr_warning("%s is not a data structure nor a union.\n",
				   varname);
			वापस -EINVAL;
		पूर्ण
		अगर (field->name[0] == '[') अणु
			pr_err("Semantic error: %s is not a pointer"
			       " nor array.\n", varname);
			वापस -EINVAL;
		पूर्ण
		/* While processing unnamed field, we करोn't care about this */
		अगर (field->ref && dwarf_diename(vr_die)) अणु
			pr_err("Semantic error: %s must be referred by '.'\n",
			       field->name);
			वापस -EINVAL;
		पूर्ण
		अगर (!ref) अणु
			pr_warning("Structure on a register is not "
				   "supported yet.\n");
			वापस -ENOTSUP;
		पूर्ण
	पूर्ण

	अगर (die_find_member(&type, field->name, die_mem) == शून्य) अणु
		pr_warning("%s(type:%s) has no member %s.\n", varname,
			   dwarf_diename(&type), field->name);
		वापस -EINVAL;
	पूर्ण

	/* Get the offset of the field */
	अगर (tag == DW_TAG_जोड़_type) अणु
		offs = 0;
	पूर्ण अन्यथा अणु
		ret = die_get_data_member_location(die_mem, &offs);
		अगर (ret < 0) अणु
			pr_warning("Failed to get the offset of %s.\n",
				   field->name);
			वापस ret;
		पूर्ण
	पूर्ण
	ref->offset += (दीर्घ)offs;
	ref->user_access = user_access;

	/* If this member is unnamed, we need to reuse this field */
	अगर (!dwarf_diename(die_mem))
		वापस convert_variable_fields(die_mem, varname, field,
						&ref, die_mem, user_access);

next:
	/* Converting next field */
	अगर (field->next)
		वापस convert_variable_fields(die_mem, field->name,
				field->next, &ref, die_mem, user_access);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_var_not_found(स्थिर अक्षर *varname)
अणु
	pr_err("Failed to find the location of the '%s' variable at this address.\n"
	       " Perhaps it has been optimized out.\n"
	       " Use -V with the --range option to show '%s' location range.\n",
		varname, varname);
पूर्ण

/* Show a variables in kprobe event क्रमmat */
अटल पूर्णांक convert_variable(Dwarf_Die *vr_die, काष्ठा probe_finder *pf)
अणु
	Dwarf_Die die_mem;
	पूर्णांक ret;

	pr_debug("Converting variable %s into trace event.\n",
		 dwarf_diename(vr_die));

	ret = convert_variable_location(vr_die, pf->addr, pf->fb_ops,
					&pf->sp_die, pf->machine, pf->tvar);
	अगर (ret == -ENOENT && pf->skip_empty_arg)
		/* This can be found in other place. skip it */
		वापस 0;
	अगर (ret == -ENOENT || ret == -EINVAL) अणु
		prपूर्णांक_var_not_found(pf->pvar->var);
	पूर्ण अन्यथा अगर (ret == -ENOTSUP)
		pr_err("Sorry, we don't support this variable location yet.\n");
	अन्यथा अगर (ret == 0 && pf->pvar->field) अणु
		ret = convert_variable_fields(vr_die, pf->pvar->var,
					      pf->pvar->field, &pf->tvar->ref,
					      &die_mem, pf->pvar->user_access);
		vr_die = &die_mem;
	पूर्ण
	अगर (ret == 0)
		ret = convert_variable_type(vr_die, pf->tvar, pf->pvar->type,
					    pf->pvar->user_access);
	/* *expr will be cached in libdw. Don't मुक्त it. */
	वापस ret;
पूर्ण

/* Find a variable in a scope DIE */
अटल पूर्णांक find_variable(Dwarf_Die *sc_die, काष्ठा probe_finder *pf)
अणु
	Dwarf_Die vr_die;
	अक्षर *buf, *ptr;
	पूर्णांक ret = 0;

	/* Copy raw parameters */
	अगर (!is_c_varname(pf->pvar->var))
		वापस copy_to_probe_trace_arg(pf->tvar, pf->pvar);

	अगर (pf->pvar->name)
		pf->tvar->name = strdup(pf->pvar->name);
	अन्यथा अणु
		buf = synthesize_perf_probe_arg(pf->pvar);
		अगर (!buf)
			वापस -ENOMEM;
		ptr = म_अक्षर(buf, ':');	/* Change type separator to _ */
		अगर (ptr)
			*ptr = '_';
		pf->tvar->name = buf;
	पूर्ण
	अगर (pf->tvar->name == शून्य)
		वापस -ENOMEM;

	pr_debug("Searching '%s' variable in context.\n", pf->pvar->var);
	/* Search child die क्रम local variables and parameters. */
	अगर (!die_find_variable_at(sc_die, pf->pvar->var, pf->addr, &vr_die)) अणु
		/* Search again in global variables */
		अगर (!die_find_variable_at(&pf->cu_die, pf->pvar->var,
						0, &vr_die)) अणु
			अगर (pf->skip_empty_arg)
				वापस 0;
			pr_warning("Failed to find '%s' in this function.\n",
				   pf->pvar->var);
			ret = -ENOENT;
		पूर्ण
	पूर्ण
	अगर (ret >= 0)
		ret = convert_variable(&vr_die, pf);

	वापस ret;
पूर्ण

/* Convert subprogram DIE to trace poपूर्णांक */
अटल पूर्णांक convert_to_trace_poपूर्णांक(Dwarf_Die *sp_die, Dwfl_Module *mod,
				  Dwarf_Addr paddr, bool retprobe,
				  स्थिर अक्षर *function,
				  काष्ठा probe_trace_poपूर्णांक *tp)
अणु
	Dwarf_Addr eaddr;
	GElf_Sym sym;
	स्थिर अक्षर *symbol;

	/* Verअगरy the address is correct */
	अगर (!dwarf_haspc(sp_die, paddr)) अणु
		pr_warning("Specified offset is out of %s\n",
			   dwarf_diename(sp_die));
		वापस -EINVAL;
	पूर्ण

	अगर (dwarf_entrypc(sp_die, &eaddr) == 0) अणु
		/* If the DIE has entrypc, use it. */
		symbol = dwarf_diename(sp_die);
	पूर्ण अन्यथा अणु
		/* Try to get actual symbol name and address from symtab */
		symbol = dwfl_module_addrsym(mod, paddr, &sym, शून्य);
		eaddr = sym.st_value;
	पूर्ण
	अगर (!symbol) अणु
		pr_warning("Failed to find symbol at 0x%lx\n",
			   (अचिन्हित दीर्घ)paddr);
		वापस -ENOENT;
	पूर्ण

	tp->offset = (अचिन्हित दीर्घ)(paddr - eaddr);
	tp->address = (अचिन्हित दीर्घ)paddr;
	tp->symbol = strdup(symbol);
	अगर (!tp->symbol)
		वापस -ENOMEM;

	/* Return probe must be on the head of a subprogram */
	अगर (retprobe) अणु
		अगर (eaddr != paddr) अणु
			pr_warning("Failed to find \"%s%%return\",\n"
				   " because %s is an inlined function and"
				   " has no return point.\n", function,
				   function);
			वापस -EINVAL;
		पूर्ण
		tp->retprobe = true;
	पूर्ण

	वापस 0;
पूर्ण

/* Call probe_finder callback with scope DIE */
अटल पूर्णांक call_probe_finder(Dwarf_Die *sc_die, काष्ठा probe_finder *pf)
अणु
	Dwarf_Attribute fb_attr;
	Dwarf_Frame *frame = शून्य;
	माप_प्रकार nops;
	पूर्णांक ret;

	अगर (!sc_die) अणु
		pr_err("Caller must pass a scope DIE. Program error.\n");
		वापस -EINVAL;
	पूर्ण

	/* If not a real subprogram, find a real one */
	अगर (!die_is_func_def(sc_die)) अणु
		अगर (!die_find_realfunc(&pf->cu_die, pf->addr, &pf->sp_die)) अणु
			अगर (die_find_tailfunc(&pf->cu_die, pf->addr, &pf->sp_die)) अणु
				pr_warning("Ignoring tail call from %s\n",
						dwarf_diename(&pf->sp_die));
				वापस 0;
			पूर्ण अन्यथा अणु
				pr_warning("Failed to find probe point in any "
					   "functions.\n");
				वापस -ENOENT;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		स_नकल(&pf->sp_die, sc_die, माप(Dwarf_Die));

	/* Get the frame base attribute/ops from subprogram */
	dwarf_attr(&pf->sp_die, DW_AT_frame_base, &fb_attr);
	ret = dwarf_getlocation_addr(&fb_attr, pf->addr, &pf->fb_ops, &nops, 1);
	अगर (ret <= 0 || nops == 0) अणु
		pf->fb_ops = शून्य;
#अगर _ELFUTILS_PREREQ(0, 142)
	पूर्ण अन्यथा अगर (nops == 1 && pf->fb_ops[0].atom == DW_OP_call_frame_cfa &&
		   (pf->cfi_eh != शून्य || pf->cfi_dbg != शून्य)) अणु
		अगर ((dwarf_cfi_addrframe(pf->cfi_eh, pf->addr, &frame) != 0 &&
		     (dwarf_cfi_addrframe(pf->cfi_dbg, pf->addr, &frame) != 0)) ||
		    dwarf_frame_cfa(frame, &pf->fb_ops, &nops) != 0) अणु
			pr_warning("Failed to get call frame on 0x%jx\n",
				   (uपूर्णांकmax_t)pf->addr);
			मुक्त(frame);
			वापस -ENOENT;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Call finder's callback handler */
	ret = pf->callback(sc_die, pf);

	/* Since *pf->fb_ops can be a part of frame. we should मुक्त it here. */
	मुक्त(frame);
	pf->fb_ops = शून्य;

	वापस ret;
पूर्ण

काष्ठा find_scope_param अणु
	स्थिर अक्षर *function;
	स्थिर अक्षर *file;
	पूर्णांक line;
	पूर्णांक dअगरf;
	Dwarf_Die *die_mem;
	bool found;
पूर्ण;

अटल पूर्णांक find_best_scope_cb(Dwarf_Die *fn_die, व्योम *data)
अणु
	काष्ठा find_scope_param *fsp = data;
	स्थिर अक्षर *file;
	पूर्णांक lno;

	/* Skip अगर declared file name करोes not match */
	अगर (fsp->file) अणु
		file = dwarf_decl_file(fn_die);
		अगर (!file || म_भेद(fsp->file, file) != 0)
			वापस 0;
	पूर्ण
	/* If the function name is given, that's what user expects */
	अगर (fsp->function) अणु
		अगर (die_match_name(fn_die, fsp->function)) अणु
			स_नकल(fsp->die_mem, fn_die, माप(Dwarf_Die));
			fsp->found = true;
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* With the line number, find the nearest declared DIE */
		dwarf_decl_line(fn_die, &lno);
		अगर (lno < fsp->line && fsp->dअगरf > fsp->line - lno) अणु
			/* Keep a candidate and जारी */
			fsp->dअगरf = fsp->line - lno;
			स_नकल(fsp->die_mem, fn_die, माप(Dwarf_Die));
			fsp->found = true;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Return innermost DIE */
अटल पूर्णांक find_inner_scope_cb(Dwarf_Die *fn_die, व्योम *data)
अणु
	काष्ठा find_scope_param *fsp = data;

	स_नकल(fsp->die_mem, fn_die, माप(Dwarf_Die));
	fsp->found = true;
	वापस 1;
पूर्ण

/* Find an appropriate scope fits to given conditions */
अटल Dwarf_Die *find_best_scope(काष्ठा probe_finder *pf, Dwarf_Die *die_mem)
अणु
	काष्ठा find_scope_param fsp = अणु
		.function = pf->pev->poपूर्णांक.function,
		.file = pf->fname,
		.line = pf->lno,
		.dअगरf = पूर्णांक_उच्च,
		.die_mem = die_mem,
		.found = false,
	पूर्ण;
	पूर्णांक ret;

	ret = cu_walk_functions_at(&pf->cu_die, pf->addr, find_best_scope_cb,
				   &fsp);
	अगर (!ret && !fsp.found)
		cu_walk_functions_at(&pf->cu_die, pf->addr,
				     find_inner_scope_cb, &fsp);

	वापस fsp.found ? die_mem : शून्य;
पूर्ण

अटल पूर्णांक verअगरy_representive_line(काष्ठा probe_finder *pf, स्थिर अक्षर *fname,
				पूर्णांक lineno, Dwarf_Addr addr)
अणु
	स्थिर अक्षर *__fname, *__func = शून्य;
	Dwarf_Die die_mem;
	पूर्णांक __lineno;

	/* Verअगरy line number and address by reverse search */
	अगर (cu_find_lineinfo(&pf->cu_die, addr, &__fname, &__lineno) < 0)
		वापस 0;

	pr_debug2("Reversed line: %s:%d\n", __fname, __lineno);
	अगर (म_भेद(fname, __fname) || lineno == __lineno)
		वापस 0;

	pr_warning("This line is sharing the address with other lines.\n");

	अगर (pf->pev->poपूर्णांक.function) अणु
		/* Find best match function name and lines */
		pf->addr = addr;
		अगर (find_best_scope(pf, &die_mem)
		    && die_match_name(&die_mem, pf->pev->poपूर्णांक.function)
		    && dwarf_decl_line(&die_mem, &lineno) == 0) अणु
			__func = dwarf_diename(&die_mem);
			__lineno -= lineno;
		पूर्ण
	पूर्ण
	pr_warning("Please try to probe at %s:%d instead.\n",
		   __func ? : __fname, __lineno);

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक probe_poपूर्णांक_line_walker(स्थिर अक्षर *fname, पूर्णांक lineno,
				   Dwarf_Addr addr, व्योम *data)
अणु
	काष्ठा probe_finder *pf = data;
	Dwarf_Die *sc_die, die_mem;
	पूर्णांक ret;

	अगर (lineno != pf->lno || strtailcmp(fname, pf->fname) != 0)
		वापस 0;

	अगर (verअगरy_representive_line(pf, fname, lineno, addr))
		वापस -ENOENT;

	pf->addr = addr;
	sc_die = find_best_scope(pf, &die_mem);
	अगर (!sc_die) अणु
		pr_warning("Failed to find scope of probe point.\n");
		वापस -ENOENT;
	पूर्ण

	ret = call_probe_finder(sc_die, pf);

	/* Continue अगर no error, because the line will be in अंतरभूत function */
	वापस ret < 0 ? ret : 0;
पूर्ण

/* Find probe poपूर्णांक from its line number */
अटल पूर्णांक find_probe_poपूर्णांक_by_line(काष्ठा probe_finder *pf)
अणु
	वापस die_walk_lines(&pf->cu_die, probe_poपूर्णांक_line_walker, pf);
पूर्ण

/* Find lines which match lazy pattern */
अटल पूर्णांक find_lazy_match_lines(काष्ठा पूर्णांकlist *list,
				 स्थिर अक्षर *fname, स्थिर अक्षर *pat)
अणु
	खाता *fp;
	अक्षर *line = शून्य;
	माप_प्रकार line_len;
	sमाप_प्रकार len;
	पूर्णांक count = 0, linक्रमागत = 1;
	अक्षर sbuf[STRERR_बफ_मानE];

	fp = ख_खोलो(fname, "r");
	अगर (!fp) अणु
		pr_warning("Failed to open %s: %s\n", fname,
			   str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		वापस -त्रुटि_सं;
	पूर्ण

	जबतक ((len = getline(&line, &line_len, fp)) > 0) अणु

		अगर (line[len - 1] == '\n')
			line[len - 1] = '\0';

		अगर (strlazymatch(line, pat)) अणु
			पूर्णांकlist__add(list, linक्रमागत);
			count++;
		पूर्ण
		linक्रमागत++;
	पूर्ण

	अगर (ख_त्रुटि(fp))
		count = -त्रुटि_सं;
	मुक्त(line);
	ख_बंद(fp);

	अगर (count == 0)
		pr_debug("No matched lines found in %s.\n", fname);
	वापस count;
पूर्ण

अटल पूर्णांक probe_poपूर्णांक_lazy_walker(स्थिर अक्षर *fname, पूर्णांक lineno,
				   Dwarf_Addr addr, व्योम *data)
अणु
	काष्ठा probe_finder *pf = data;
	Dwarf_Die *sc_die, die_mem;
	पूर्णांक ret;

	अगर (!पूर्णांकlist__has_entry(pf->lcache, lineno) ||
	    strtailcmp(fname, pf->fname) != 0)
		वापस 0;

	pr_debug("Probe line found: line:%d addr:0x%llx\n",
		 lineno, (अचिन्हित दीर्घ दीर्घ)addr);
	pf->addr = addr;
	pf->lno = lineno;
	sc_die = find_best_scope(pf, &die_mem);
	अगर (!sc_die) अणु
		pr_warning("Failed to find scope of probe point.\n");
		वापस -ENOENT;
	पूर्ण

	ret = call_probe_finder(sc_die, pf);

	/*
	 * Continue अगर no error, because the lazy pattern will match
	 * to other lines
	 */
	वापस ret < 0 ? ret : 0;
पूर्ण

/* Find probe poपूर्णांकs from lazy pattern  */
अटल पूर्णांक find_probe_poपूर्णांक_lazy(Dwarf_Die *sp_die, काष्ठा probe_finder *pf)
अणु
	काष्ठा build_id bid;
	अक्षर sbuild_id[SBUILD_ID_SIZE] = "";
	पूर्णांक ret = 0;
	अक्षर *fpath;

	अगर (पूर्णांकlist__empty(pf->lcache)) अणु
		स्थिर अक्षर *comp_dir;

		comp_dir = cu_get_comp_dir(&pf->cu_die);
		अगर (pf->dbg->build_id) अणु
			build_id__init(&bid, pf->dbg->build_id, BUILD_ID_SIZE);
			build_id__प्र_लिखो(&bid, sbuild_id);
		पूर्ण
		ret = find_source_path(pf->fname, sbuild_id, comp_dir, &fpath);
		अगर (ret < 0) अणु
			pr_warning("Failed to find source file path.\n");
			वापस ret;
		पूर्ण

		/* Matching lazy line pattern */
		ret = find_lazy_match_lines(pf->lcache, fpath,
					    pf->pev->poपूर्णांक.lazy_line);
		मुक्त(fpath);
		अगर (ret <= 0)
			वापस ret;
	पूर्ण

	वापस die_walk_lines(sp_die, probe_poपूर्णांक_lazy_walker, pf);
पूर्ण

अटल व्योम skip_prologue(Dwarf_Die *sp_die, काष्ठा probe_finder *pf)
अणु
	काष्ठा perf_probe_poपूर्णांक *pp = &pf->pev->poपूर्णांक;

	/* Not uprobe? */
	अगर (!pf->pev->uprobes)
		वापस;

	/* Compiled with optimization? */
	अगर (die_is_optimized_target(&pf->cu_die))
		वापस;

	/* Don't know entrypc? */
	अगर (!pf->addr)
		वापस;

	/* Only FUNC and FUNC@SRC are eligible. */
	अगर (!pp->function || pp->line || pp->retprobe || pp->lazy_line ||
	    pp->offset || pp->असल_address)
		वापस;

	/* Not पूर्णांकerested in func parameter? */
	अगर (!perf_probe_with_var(pf->pev))
		वापस;

	pr_info("Target program is compiled without optimization. Skipping prologue.\n"
		"Probe on address 0x%" PRIx64 " to force probing at the function entry.\n\n",
		pf->addr);

	die_skip_prologue(sp_die, &pf->cu_die, &pf->addr);
पूर्ण

अटल पूर्णांक probe_poपूर्णांक_अंतरभूत_cb(Dwarf_Die *in_die, व्योम *data)
अणु
	काष्ठा probe_finder *pf = data;
	काष्ठा perf_probe_poपूर्णांक *pp = &pf->pev->poपूर्णांक;
	Dwarf_Addr addr;
	पूर्णांक ret;

	अगर (pp->lazy_line)
		ret = find_probe_poपूर्णांक_lazy(in_die, pf);
	अन्यथा अणु
		/* Get probe address */
		अगर (die_entrypc(in_die, &addr) != 0) अणु
			pr_warning("Failed to get entry address of %s.\n",
				   dwarf_diename(in_die));
			वापस -ENOENT;
		पूर्ण
		अगर (addr == 0) अणु
			pr_debug("%s has no valid entry address. skipped.\n",
				 dwarf_diename(in_die));
			वापस -ENOENT;
		पूर्ण
		pf->addr = addr;
		pf->addr += pp->offset;
		pr_debug("found inline addr: 0x%jx\n",
			 (uपूर्णांकmax_t)pf->addr);

		ret = call_probe_finder(in_die, pf);
	पूर्ण

	वापस ret;
पूर्ण

/* Callback parameter with वापस value क्रम libdw */
काष्ठा dwarf_callback_param अणु
	व्योम *data;
	पूर्णांक retval;
पूर्ण;

/* Search function from function name */
अटल पूर्णांक probe_poपूर्णांक_search_cb(Dwarf_Die *sp_die, व्योम *data)
अणु
	काष्ठा dwarf_callback_param *param = data;
	काष्ठा probe_finder *pf = param->data;
	काष्ठा perf_probe_poपूर्णांक *pp = &pf->pev->poपूर्णांक;

	/* Check tag and diename */
	अगर (!die_is_func_def(sp_die) ||
	    !die_match_name(sp_die, pp->function))
		वापस DWARF_CB_OK;

	/* Check declared file */
	अगर (pp->file && strtailcmp(pp->file, dwarf_decl_file(sp_die)))
		वापस DWARF_CB_OK;

	pr_debug("Matched function: %s [%lx]\n", dwarf_diename(sp_die),
		 (अचिन्हित दीर्घ)dwarf_dieoffset(sp_die));
	pf->fname = dwarf_decl_file(sp_die);
	अगर (pp->line) अणु /* Function relative line */
		dwarf_decl_line(sp_die, &pf->lno);
		pf->lno += pp->line;
		param->retval = find_probe_poपूर्णांक_by_line(pf);
	पूर्ण अन्यथा अगर (die_is_func_instance(sp_die)) अणु
		/* Instances always have the entry address */
		die_entrypc(sp_die, &pf->addr);
		/* But in some हाल the entry address is 0 */
		अगर (pf->addr == 0) अणु
			pr_debug("%s has no entry PC. Skipped\n",
				 dwarf_diename(sp_die));
			param->retval = 0;
		/* Real function */
		पूर्ण अन्यथा अगर (pp->lazy_line)
			param->retval = find_probe_poपूर्णांक_lazy(sp_die, pf);
		अन्यथा अणु
			skip_prologue(sp_die, pf);
			pf->addr += pp->offset;
			/* TODO: Check the address in this function */
			param->retval = call_probe_finder(sp_die, pf);
		पूर्ण
	पूर्ण अन्यथा अगर (!probe_conf.no_अंतरभूतs) अणु
		/* Inlined function: search instances */
		param->retval = die_walk_instances(sp_die,
					probe_poपूर्णांक_अंतरभूत_cb, (व्योम *)pf);
		/* This could be a non-existed अंतरभूत definition */
		अगर (param->retval == -ENOENT)
			param->retval = 0;
	पूर्ण

	/* We need to find other candidates */
	अगर (strisglob(pp->function) && param->retval >= 0) अणु
		param->retval = 0;	/* We have to clear the result */
		वापस DWARF_CB_OK;
	पूर्ण

	वापस DWARF_CB_ABORT; /* Exit; no same symbol in this CU. */
पूर्ण

अटल पूर्णांक find_probe_poपूर्णांक_by_func(काष्ठा probe_finder *pf)
अणु
	काष्ठा dwarf_callback_param _param = अणु.data = (व्योम *)pf,
					      .retval = 0पूर्ण;
	dwarf_getfuncs(&pf->cu_die, probe_poपूर्णांक_search_cb, &_param, 0);
	वापस _param.retval;
पूर्ण

काष्ठा pubname_callback_param अणु
	अक्षर *function;
	अक्षर *file;
	Dwarf_Die *cu_die;
	Dwarf_Die *sp_die;
	पूर्णांक found;
पूर्ण;

अटल पूर्णांक pubname_search_cb(Dwarf *dbg, Dwarf_Global *gl, व्योम *data)
अणु
	काष्ठा pubname_callback_param *param = data;

	अगर (dwarf_offdie(dbg, gl->die_offset, param->sp_die)) अणु
		अगर (dwarf_tag(param->sp_die) != DW_TAG_subprogram)
			वापस DWARF_CB_OK;

		अगर (die_match_name(param->sp_die, param->function)) अणु
			अगर (!dwarf_offdie(dbg, gl->cu_offset, param->cu_die))
				वापस DWARF_CB_OK;

			अगर (param->file &&
			    strtailcmp(param->file, dwarf_decl_file(param->sp_die)))
				वापस DWARF_CB_OK;

			param->found = 1;
			वापस DWARF_CB_ABORT;
		पूर्ण
	पूर्ण

	वापस DWARF_CB_OK;
पूर्ण

अटल पूर्णांक debuginfo__find_probe_location(काष्ठा debuginfo *dbg,
				  काष्ठा probe_finder *pf)
अणु
	काष्ठा perf_probe_poपूर्णांक *pp = &pf->pev->poपूर्णांक;
	Dwarf_Off off, noff;
	माप_प्रकार cuhl;
	Dwarf_Die *diep;
	पूर्णांक ret = 0;

	off = 0;
	pf->lcache = पूर्णांकlist__new(शून्य);
	अगर (!pf->lcache)
		वापस -ENOMEM;

	/* Fastpath: lookup by function name from .debug_pubnames section */
	अगर (pp->function && !strisglob(pp->function)) अणु
		काष्ठा pubname_callback_param pubname_param = अणु
			.function = pp->function,
			.file	  = pp->file,
			.cu_die	  = &pf->cu_die,
			.sp_die	  = &pf->sp_die,
			.found	  = 0,
		पूर्ण;
		काष्ठा dwarf_callback_param probe_param = अणु
			.data = pf,
		पूर्ण;

		dwarf_getpubnames(dbg->dbg, pubname_search_cb,
				  &pubname_param, 0);
		अगर (pubname_param.found) अणु
			ret = probe_poपूर्णांक_search_cb(&pf->sp_die, &probe_param);
			अगर (ret)
				जाओ found;
		पूर्ण
	पूर्ण

	/* Loop on CUs (Compilation Unit) */
	जबतक (!dwarf_nextcu(dbg->dbg, off, &noff, &cuhl, शून्य, शून्य, शून्य)) अणु
		/* Get the DIE(Debugging Inक्रमmation Entry) of this CU */
		diep = dwarf_offdie(dbg->dbg, off + cuhl, &pf->cu_die);
		अगर (!diep) अणु
			off = noff;
			जारी;
		पूर्ण

		/* Check अगर target file is included. */
		अगर (pp->file)
			pf->fname = cu_find_realpath(&pf->cu_die, pp->file);
		अन्यथा
			pf->fname = शून्य;

		अगर (!pp->file || pf->fname) अणु
			अगर (pp->function)
				ret = find_probe_poपूर्णांक_by_func(pf);
			अन्यथा अगर (pp->lazy_line)
				ret = find_probe_poपूर्णांक_lazy(&pf->cu_die, pf);
			अन्यथा अणु
				pf->lno = pp->line;
				ret = find_probe_poपूर्णांक_by_line(pf);
			पूर्ण
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		off = noff;
	पूर्ण

found:
	पूर्णांकlist__delete(pf->lcache);
	pf->lcache = शून्य;

	वापस ret;
पूर्ण

/* Find probe poपूर्णांकs from debuginfo */
अटल पूर्णांक debuginfo__find_probes(काष्ठा debuginfo *dbg,
				  काष्ठा probe_finder *pf)
अणु
	पूर्णांक ret = 0;
	Elf *elf;
	GElf_Ehdr ehdr;

	अगर (pf->cfi_eh || pf->cfi_dbg)
		वापस debuginfo__find_probe_location(dbg, pf);

	/* Get the call frame inक्रमmation from this dwarf */
	elf = dwarf_getelf(dbg->dbg);
	अगर (elf == शून्य)
		वापस -EINVAL;

	अगर (gelf_getehdr(elf, &ehdr) == शून्य)
		वापस -EINVAL;

	pf->machine = ehdr.e_machine;

#अगर _ELFUTILS_PREREQ(0, 142)
	करो अणु
		GElf_Shdr shdr;

		अगर (elf_section_by_name(elf, &ehdr, &shdr, ".eh_frame", शून्य) &&
		    shdr.sh_type == SHT_PROGBITS)
			pf->cfi_eh = dwarf_अ_लोfi_elf(elf);

		pf->cfi_dbg = dwarf_अ_लोfi(dbg->dbg);
	पूर्ण जबतक (0);
#पूर्ण_अगर

	ret = debuginfo__find_probe_location(dbg, pf);
	वापस ret;
पूर्ण

काष्ठा local_vars_finder अणु
	काष्ठा probe_finder *pf;
	काष्ठा perf_probe_arg *args;
	bool vars;
	पूर्णांक max_args;
	पूर्णांक nargs;
	पूर्णांक ret;
पूर्ण;

/* Collect available variables in this scope */
अटल पूर्णांक copy_variables_cb(Dwarf_Die *die_mem, व्योम *data)
अणु
	काष्ठा local_vars_finder *vf = data;
	काष्ठा probe_finder *pf = vf->pf;
	पूर्णांक tag;

	tag = dwarf_tag(die_mem);
	अगर (tag == DW_TAG_क्रमmal_parameter ||
	    (tag == DW_TAG_variable && vf->vars)) अणु
		अगर (convert_variable_location(die_mem, vf->pf->addr,
					      vf->pf->fb_ops, &pf->sp_die,
					      pf->machine, शून्य) == 0) अणु
			vf->args[vf->nargs].var = (अक्षर *)dwarf_diename(die_mem);
			अगर (vf->args[vf->nargs].var == शून्य) अणु
				vf->ret = -ENOMEM;
				वापस DIE_FIND_CB_END;
			पूर्ण
			pr_debug(" %s", vf->args[vf->nargs].var);
			vf->nargs++;
		पूर्ण
	पूर्ण

	अगर (dwarf_haspc(die_mem, vf->pf->addr))
		वापस DIE_FIND_CB_CONTINUE;
	अन्यथा
		वापस DIE_FIND_CB_SIBLING;
पूर्ण

अटल पूर्णांक expand_probe_args(Dwarf_Die *sc_die, काष्ठा probe_finder *pf,
			     काष्ठा perf_probe_arg *args)
अणु
	Dwarf_Die die_mem;
	पूर्णांक i;
	पूर्णांक n = 0;
	काष्ठा local_vars_finder vf = अणु.pf = pf, .args = args, .vars = false,
				.max_args = MAX_PROBE_ARGS, .ret = 0पूर्ण;

	क्रम (i = 0; i < pf->pev->nargs; i++) अणु
		/* var never be शून्य */
		अगर (म_भेद(pf->pev->args[i].var, PROBE_ARG_VARS) == 0)
			vf.vars = true;
		अन्यथा अगर (म_भेद(pf->pev->args[i].var, PROBE_ARG_PARAMS) != 0) अणु
			/* Copy normal argument */
			args[n] = pf->pev->args[i];
			n++;
			जारी;
		पूर्ण
		pr_debug("Expanding %s into:", pf->pev->args[i].var);
		vf.nargs = n;
		/* Special local variables */
		die_find_child(sc_die, copy_variables_cb, (व्योम *)&vf,
			       &die_mem);
		pr_debug(" (%d)\n", vf.nargs - n);
		अगर (vf.ret < 0)
			वापस vf.ret;
		n = vf.nargs;
	पूर्ण
	वापस n;
पूर्ण

अटल bool trace_event_finder_overlap(काष्ठा trace_event_finder *tf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tf->ntevs; i++) अणु
		अगर (tf->pf.addr == tf->tevs[i].poपूर्णांक.address)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Add a found probe poपूर्णांक पूर्णांकo trace event list */
अटल पूर्णांक add_probe_trace_event(Dwarf_Die *sc_die, काष्ठा probe_finder *pf)
अणु
	काष्ठा trace_event_finder *tf =
			container_of(pf, काष्ठा trace_event_finder, pf);
	काष्ठा perf_probe_poपूर्णांक *pp = &pf->pev->poपूर्णांक;
	काष्ठा probe_trace_event *tev;
	काष्ठा perf_probe_arg *args = शून्य;
	पूर्णांक ret, i;

	/*
	 * For some reason (e.g. dअगरferent column asचिन्हित to same address)
	 * This callback can be called with the address which alपढ़ोy passed.
	 * Ignore it first.
	 */
	अगर (trace_event_finder_overlap(tf))
		वापस 0;

	/* Check number of tevs */
	अगर (tf->ntevs == tf->max_tevs) अणु
		pr_warning("Too many( > %d) probe point found.\n",
			   tf->max_tevs);
		वापस -दुस्फल;
	पूर्ण
	tev = &tf->tevs[tf->ntevs++];

	/* Trace poपूर्णांक should be converted from subprogram DIE */
	ret = convert_to_trace_poपूर्णांक(&pf->sp_die, tf->mod, pf->addr,
				     pp->retprobe, pp->function, &tev->poपूर्णांक);
	अगर (ret < 0)
		जाओ end;

	tev->poपूर्णांक.realname = strdup(dwarf_diename(sc_die));
	अगर (!tev->poपूर्णांक.realname) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	pr_debug("Probe point found: %s+%lu\n", tev->poपूर्णांक.symbol,
		 tev->poपूर्णांक.offset);

	/* Expand special probe argument अगर exist */
	args = zalloc(माप(काष्ठा perf_probe_arg) * MAX_PROBE_ARGS);
	अगर (args == शून्य) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	ret = expand_probe_args(sc_die, pf, args);
	अगर (ret < 0)
		जाओ end;

	tev->nargs = ret;
	tev->args = zalloc(माप(काष्ठा probe_trace_arg) * tev->nargs);
	अगर (tev->args == शून्य) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	/* Find each argument */
	क्रम (i = 0; i < tev->nargs; i++) अणु
		pf->pvar = &args[i];
		pf->tvar = &tev->args[i];
		/* Variable should be found from scope DIE */
		ret = find_variable(sc_die, pf);
		अगर (ret != 0)
			अवरोध;
	पूर्ण

end:
	अगर (ret) अणु
		clear_probe_trace_event(tev);
		tf->ntevs--;
	पूर्ण
	मुक्त(args);
	वापस ret;
पूर्ण

अटल पूर्णांक fill_empty_trace_arg(काष्ठा perf_probe_event *pev,
				काष्ठा probe_trace_event *tevs, पूर्णांक ntevs)
अणु
	अक्षर **valp;
	अक्षर *type;
	पूर्णांक i, j, ret;

	अगर (!ntevs)
		वापस -ENOENT;

	क्रम (i = 0; i < pev->nargs; i++) अणु
		type = शून्य;
		क्रम (j = 0; j < ntevs; j++) अणु
			अगर (tevs[j].args[i].value) अणु
				type = tevs[j].args[i].type;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (j == ntevs) अणु
			prपूर्णांक_var_not_found(pev->args[i].var);
			वापस -ENOENT;
		पूर्ण
		क्रम (j = 0; j < ntevs; j++) अणु
			valp = &tevs[j].args[i].value;
			अगर (*valp)
				जारी;

			ret = aप्र_लिखो(valp, "\\%lx", probe_conf.magic_num);
			अगर (ret < 0)
				वापस -ENOMEM;
			/* Note that type can be शून्य */
			अगर (type) अणु
				tevs[j].args[i].type = strdup(type);
				अगर (!tevs[j].args[i].type)
					वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Find probe_trace_events specअगरied by perf_probe_event from debuginfo */
पूर्णांक debuginfo__find_trace_events(काष्ठा debuginfo *dbg,
				 काष्ठा perf_probe_event *pev,
				 काष्ठा probe_trace_event **tevs)
अणु
	काष्ठा trace_event_finder tf = अणु
			.pf = अणु.pev = pev, .dbg = dbg, .callback = add_probe_trace_eventपूर्ण,
			.max_tevs = probe_conf.max_probes, .mod = dbg->modपूर्ण;
	पूर्णांक ret, i;

	/* Allocate result tevs array */
	*tevs = zalloc(माप(काष्ठा probe_trace_event) * tf.max_tevs);
	अगर (*tevs == शून्य)
		वापस -ENOMEM;

	tf.tevs = *tevs;
	tf.ntevs = 0;

	अगर (pev->nargs != 0 && immediate_value_is_supported())
		tf.pf.skip_empty_arg = true;

	ret = debuginfo__find_probes(dbg, &tf.pf);
	अगर (ret >= 0 && tf.pf.skip_empty_arg)
		ret = fill_empty_trace_arg(pev, tf.tevs, tf.ntevs);

	अगर (ret < 0 || tf.ntevs == 0) अणु
		क्रम (i = 0; i < tf.ntevs; i++)
			clear_probe_trace_event(&tf.tevs[i]);
		zमुक्त(tevs);
		वापस ret;
	पूर्ण

	वापस (ret < 0) ? ret : tf.ntevs;
पूर्ण

/* Collect available variables in this scope */
अटल पूर्णांक collect_variables_cb(Dwarf_Die *die_mem, व्योम *data)
अणु
	काष्ठा available_var_finder *af = data;
	काष्ठा variable_list *vl;
	काष्ठा strbuf buf = STRBUF_INIT;
	पूर्णांक tag, ret;

	vl = &af->vls[af->nvls - 1];

	tag = dwarf_tag(die_mem);
	अगर (tag == DW_TAG_क्रमmal_parameter ||
	    tag == DW_TAG_variable) अणु
		ret = convert_variable_location(die_mem, af->pf.addr,
						af->pf.fb_ops, &af->pf.sp_die,
						af->pf.machine, शून्य);
		अगर (ret == 0 || ret == -दुस्फल) अणु
			पूर्णांक ret2;
			bool बाह्यs = !af->child;

			अगर (strbuf_init(&buf, 64) < 0)
				जाओ error;

			अगर (probe_conf.show_location_range) अणु
				अगर (!बाह्यs)
					ret2 = strbuf_add(&buf,
						ret ? "[INV]\t" : "[VAL]\t", 6);
				अन्यथा
					ret2 = strbuf_add(&buf, "[EXT]\t", 6);
				अगर (ret2)
					जाओ error;
			पूर्ण

			ret2 = die_get_varname(die_mem, &buf);

			अगर (!ret2 && probe_conf.show_location_range &&
				!बाह्यs) अणु
				अगर (strbuf_addch(&buf, '\t') < 0)
					जाओ error;
				ret2 = die_get_var_range(&af->pf.sp_die,
							die_mem, &buf);
			पूर्ण

			pr_debug("Add new var: %s\n", buf.buf);
			अगर (ret2 == 0) अणु
				strlist__add(vl->vars,
					strbuf_detach(&buf, शून्य));
			पूर्ण
			strbuf_release(&buf);
		पूर्ण
	पूर्ण

	अगर (af->child && dwarf_haspc(die_mem, af->pf.addr))
		वापस DIE_FIND_CB_CONTINUE;
	अन्यथा
		वापस DIE_FIND_CB_SIBLING;
error:
	strbuf_release(&buf);
	pr_debug("Error in strbuf\n");
	वापस DIE_FIND_CB_END;
पूर्ण

अटल bool available_var_finder_overlap(काष्ठा available_var_finder *af)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < af->nvls; i++) अणु
		अगर (af->pf.addr == af->vls[i].poपूर्णांक.address)
			वापस true;
	पूर्ण
	वापस false;

पूर्ण

/* Add a found vars पूर्णांकo available variables list */
अटल पूर्णांक add_available_vars(Dwarf_Die *sc_die, काष्ठा probe_finder *pf)
अणु
	काष्ठा available_var_finder *af =
			container_of(pf, काष्ठा available_var_finder, pf);
	काष्ठा perf_probe_poपूर्णांक *pp = &pf->pev->poपूर्णांक;
	काष्ठा variable_list *vl;
	Dwarf_Die die_mem;
	पूर्णांक ret;

	/*
	 * For some reason (e.g. dअगरferent column asचिन्हित to same address),
	 * this callback can be called with the address which alपढ़ोy passed.
	 * Ignore it first.
	 */
	अगर (available_var_finder_overlap(af))
		वापस 0;

	/* Check number of tevs */
	अगर (af->nvls == af->max_vls) अणु
		pr_warning("Too many( > %d) probe point found.\n", af->max_vls);
		वापस -दुस्फल;
	पूर्ण
	vl = &af->vls[af->nvls++];

	/* Trace poपूर्णांक should be converted from subprogram DIE */
	ret = convert_to_trace_poपूर्णांक(&pf->sp_die, af->mod, pf->addr,
				     pp->retprobe, pp->function, &vl->poपूर्णांक);
	अगर (ret < 0)
		वापस ret;

	pr_debug("Probe point found: %s+%lu\n", vl->poपूर्णांक.symbol,
		 vl->poपूर्णांक.offset);

	/* Find local variables */
	vl->vars = strlist__new(शून्य, शून्य);
	अगर (vl->vars == शून्य)
		वापस -ENOMEM;
	af->child = true;
	die_find_child(sc_die, collect_variables_cb, (व्योम *)af, &die_mem);

	/* Find बाह्यal variables */
	अगर (!probe_conf.show_ext_vars)
		जाओ out;
	/* Don't need to search child DIE क्रम बाह्यal vars. */
	af->child = false;
	die_find_child(&pf->cu_die, collect_variables_cb, (व्योम *)af, &die_mem);

out:
	अगर (strlist__empty(vl->vars)) अणु
		strlist__delete(vl->vars);
		vl->vars = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Find available variables at given probe poपूर्णांक
 * Return the number of found probe poपूर्णांकs. Return 0 अगर there is no
 * matched probe poपूर्णांक. Return <0 अगर an error occurs.
 */
पूर्णांक debuginfo__find_available_vars_at(काष्ठा debuginfo *dbg,
				      काष्ठा perf_probe_event *pev,
				      काष्ठा variable_list **vls)
अणु
	काष्ठा available_var_finder af = अणु
			.pf = अणु.pev = pev, .dbg = dbg, .callback = add_available_varsपूर्ण,
			.mod = dbg->mod,
			.max_vls = probe_conf.max_probesपूर्ण;
	पूर्णांक ret;

	/* Allocate result vls array */
	*vls = zalloc(माप(काष्ठा variable_list) * af.max_vls);
	अगर (*vls == शून्य)
		वापस -ENOMEM;

	af.vls = *vls;
	af.nvls = 0;

	ret = debuginfo__find_probes(dbg, &af.pf);
	अगर (ret < 0) अणु
		/* Free vlist क्रम error */
		जबतक (af.nvls--) अणु
			zमुक्त(&af.vls[af.nvls].poपूर्णांक.symbol);
			strlist__delete(af.vls[af.nvls].vars);
		पूर्ण
		zमुक्त(vls);
		वापस ret;
	पूर्ण

	वापस (ret < 0) ? ret : af.nvls;
पूर्ण

/* For the kernel module, we need a special code to get a DIE */
पूर्णांक debuginfo__get_text_offset(काष्ठा debuginfo *dbg, Dwarf_Addr *offs,
				bool adjust_offset)
अणु
	पूर्णांक n, i;
	Elf32_Word shndx;
	Elf_Scn *scn;
	Elf *elf;
	GElf_Shdr mem, *shdr;
	स्थिर अक्षर *p;

	elf = dwfl_module_getelf(dbg->mod, &dbg->bias);
	अगर (!elf)
		वापस -EINVAL;

	/* Get the number of relocations */
	n = dwfl_module_relocations(dbg->mod);
	अगर (n < 0)
		वापस -ENOENT;
	/* Search the relocation related .text section */
	क्रम (i = 0; i < n; i++) अणु
		p = dwfl_module_relocation_info(dbg->mod, i, &shndx);
		अगर (म_भेद(p, ".text") == 0) अणु
			/* OK, get the section header */
			scn = elf_माला_लोcn(elf, shndx);
			अगर (!scn)
				वापस -ENOENT;
			shdr = gelf_माला_लोhdr(scn, &mem);
			अगर (!shdr)
				वापस -ENOENT;
			*offs = shdr->sh_addr;
			अगर (adjust_offset)
				*offs -= shdr->sh_offset;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Reverse search */
पूर्णांक debuginfo__find_probe_poपूर्णांक(काष्ठा debuginfo *dbg, अचिन्हित दीर्घ addr,
				काष्ठा perf_probe_poपूर्णांक *ppt)
अणु
	Dwarf_Die cudie, spdie, indie;
	Dwarf_Addr _addr = 0, baseaddr = 0;
	स्थिर अक्षर *fname = शून्य, *func = शून्य, *basefunc = शून्य, *पंचांगp;
	पूर्णांक baseline = 0, lineno = 0, ret = 0;

	/* We always need to relocate the address क्रम aranges */
	अगर (debuginfo__get_text_offset(dbg, &baseaddr, false) == 0)
		addr += baseaddr;
	/* Find cu die */
	अगर (!dwarf_addrdie(dbg->dbg, (Dwarf_Addr)addr, &cudie)) अणु
		pr_warning("Failed to find debug information for address %lx\n",
			   addr);
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	/* Find a corresponding line (filename and lineno) */
	cu_find_lineinfo(&cudie, addr, &fname, &lineno);
	/* Don't care whether it failed or not */

	/* Find a corresponding function (name, baseline and baseaddr) */
	अगर (die_find_realfunc(&cudie, (Dwarf_Addr)addr, &spdie)) अणु
		/* Get function entry inक्रमmation */
		func = basefunc = dwarf_diename(&spdie);
		अगर (!func ||
		    die_entrypc(&spdie, &baseaddr) != 0 ||
		    dwarf_decl_line(&spdie, &baseline) != 0) अणु
			lineno = 0;
			जाओ post;
		पूर्ण

		fname = dwarf_decl_file(&spdie);
		अगर (addr == (अचिन्हित दीर्घ)baseaddr) अणु
			/* Function entry - Relative line number is 0 */
			lineno = baseline;
			जाओ post;
		पूर्ण

		/* Track करोwn the अंतरभूत functions step by step */
		जबतक (die_find_top_अंतरभूतfunc(&spdie, (Dwarf_Addr)addr,
						&indie)) अणु
			/* There is an अंतरभूत function */
			अगर (die_entrypc(&indie, &_addr) == 0 &&
			    _addr == addr) अणु
				/*
				 * addr is at an अंतरभूत function entry.
				 * In this हाल, lineno should be the call-site
				 * line number. (overग_लिखो lineinfo)
				 */
				lineno = die_get_call_lineno(&indie);
				fname = die_get_call_file(&indie);
				अवरोध;
			पूर्ण अन्यथा अणु
				/*
				 * addr is in an अंतरभूत function body.
				 * Since lineno poपूर्णांकs one of the lines
				 * of the अंतरभूत function, baseline should
				 * be the entry line of the अंतरभूत function.
				 */
				पंचांगp = dwarf_diename(&indie);
				अगर (!पंचांगp ||
				    dwarf_decl_line(&indie, &baseline) != 0)
					अवरोध;
				func = पंचांगp;
				spdie = indie;
			पूर्ण
		पूर्ण
		/* Verअगरy the lineno and baseline are in a same file */
		पंचांगp = dwarf_decl_file(&spdie);
		अगर (!पंचांगp || म_भेद(पंचांगp, fname) != 0)
			lineno = 0;
	पूर्ण

post:
	/* Make a relative line number or an offset */
	अगर (lineno)
		ppt->line = lineno - baseline;
	अन्यथा अगर (basefunc) अणु
		ppt->offset = addr - (अचिन्हित दीर्घ)baseaddr;
		func = basefunc;
	पूर्ण

	/* Duplicate strings */
	अगर (func) अणु
		ppt->function = strdup(func);
		अगर (ppt->function == शून्य) अणु
			ret = -ENOMEM;
			जाओ end;
		पूर्ण
	पूर्ण
	अगर (fname) अणु
		ppt->file = strdup(fname);
		अगर (ppt->file == शून्य) अणु
			zमुक्त(&ppt->function);
			ret = -ENOMEM;
			जाओ end;
		पूर्ण
	पूर्ण
end:
	अगर (ret == 0 && (fname || func))
		ret = 1;	/* Found a poपूर्णांक */
	वापस ret;
पूर्ण

/* Add a line and store the src path */
अटल पूर्णांक line_range_add_line(स्थिर अक्षर *src, अचिन्हित पूर्णांक lineno,
			       काष्ठा line_range *lr)
अणु
	/* Copy source path */
	अगर (!lr->path) अणु
		lr->path = strdup(src);
		अगर (lr->path == शून्य)
			वापस -ENOMEM;
	पूर्ण
	वापस पूर्णांकlist__add(lr->line_list, lineno);
पूर्ण

अटल पूर्णांक line_range_walk_cb(स्थिर अक्षर *fname, पूर्णांक lineno,
			      Dwarf_Addr addr __maybe_unused,
			      व्योम *data)
अणु
	काष्ठा line_finder *lf = data;
	स्थिर अक्षर *__fname;
	पूर्णांक __lineno;
	पूर्णांक err;

	अगर ((strtailcmp(fname, lf->fname) != 0) ||
	    (lf->lno_s > lineno || lf->lno_e < lineno))
		वापस 0;

	/* Make sure this line can be reversible */
	अगर (cu_find_lineinfo(&lf->cu_die, addr, &__fname, &__lineno) > 0
	    && (lineno != __lineno || म_भेद(fname, __fname)))
		वापस 0;

	err = line_range_add_line(fname, lineno, lf->lr);
	अगर (err < 0 && err != -EEXIST)
		वापस err;

	वापस 0;
पूर्ण

/* Find line range from its line number */
अटल पूर्णांक find_line_range_by_line(Dwarf_Die *sp_die, काष्ठा line_finder *lf)
अणु
	पूर्णांक ret;

	ret = die_walk_lines(sp_die ?: &lf->cu_die, line_range_walk_cb, lf);

	/* Update status */
	अगर (ret >= 0)
		अगर (!पूर्णांकlist__empty(lf->lr->line_list))
			ret = lf->found = 1;
		अन्यथा
			ret = 0;	/* Lines are not found */
	अन्यथा अणु
		zमुक्त(&lf->lr->path);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक line_range_अंतरभूत_cb(Dwarf_Die *in_die, व्योम *data)
अणु
	पूर्णांक ret = find_line_range_by_line(in_die, data);

	/*
	 * We have to check all instances of अंतरभूतd function, because
	 * some execution paths can be optimized out depends on the
	 * function argument of instances. However, अगर an error occurs,
	 * it should be handled by the caller.
	 */
	वापस ret < 0 ? ret : 0;
पूर्ण

/* Search function definition from function name */
अटल पूर्णांक line_range_search_cb(Dwarf_Die *sp_die, व्योम *data)
अणु
	काष्ठा dwarf_callback_param *param = data;
	काष्ठा line_finder *lf = param->data;
	काष्ठा line_range *lr = lf->lr;

	/* Check declared file */
	अगर (lr->file && strtailcmp(lr->file, dwarf_decl_file(sp_die)))
		वापस DWARF_CB_OK;

	अगर (die_match_name(sp_die, lr->function) && die_is_func_def(sp_die)) अणु
		lf->fname = dwarf_decl_file(sp_die);
		dwarf_decl_line(sp_die, &lr->offset);
		pr_debug("fname: %s, lineno:%d\n", lf->fname, lr->offset);
		lf->lno_s = lr->offset + lr->start;
		अगर (lf->lno_s < 0)	/* Overflow */
			lf->lno_s = पूर्णांक_उच्च;
		lf->lno_e = lr->offset + lr->end;
		अगर (lf->lno_e < 0)	/* Overflow */
			lf->lno_e = पूर्णांक_उच्च;
		pr_debug("New line range: %d to %d\n", lf->lno_s, lf->lno_e);
		lr->start = lf->lno_s;
		lr->end = lf->lno_e;
		अगर (!die_is_func_instance(sp_die))
			param->retval = die_walk_instances(sp_die,
						line_range_अंतरभूत_cb, lf);
		अन्यथा
			param->retval = find_line_range_by_line(sp_die, lf);
		वापस DWARF_CB_ABORT;
	पूर्ण
	वापस DWARF_CB_OK;
पूर्ण

अटल पूर्णांक find_line_range_by_func(काष्ठा line_finder *lf)
अणु
	काष्ठा dwarf_callback_param param = अणु.data = (व्योम *)lf, .retval = 0पूर्ण;
	dwarf_getfuncs(&lf->cu_die, line_range_search_cb, &param, 0);
	वापस param.retval;
पूर्ण

पूर्णांक debuginfo__find_line_range(काष्ठा debuginfo *dbg, काष्ठा line_range *lr)
अणु
	काष्ठा line_finder lf = अणु.lr = lr, .found = 0पूर्ण;
	पूर्णांक ret = 0;
	Dwarf_Off off = 0, noff;
	माप_प्रकार cuhl;
	Dwarf_Die *diep;
	स्थिर अक्षर *comp_dir;

	/* Fastpath: lookup by function name from .debug_pubnames section */
	अगर (lr->function) अणु
		काष्ठा pubname_callback_param pubname_param = अणु
			.function = lr->function, .file = lr->file,
			.cu_die = &lf.cu_die, .sp_die = &lf.sp_die, .found = 0पूर्ण;
		काष्ठा dwarf_callback_param line_range_param = अणु
			.data = (व्योम *)&lf, .retval = 0पूर्ण;

		dwarf_getpubnames(dbg->dbg, pubname_search_cb,
				  &pubname_param, 0);
		अगर (pubname_param.found) अणु
			line_range_search_cb(&lf.sp_die, &line_range_param);
			अगर (lf.found)
				जाओ found;
		पूर्ण
	पूर्ण

	/* Loop on CUs (Compilation Unit) */
	जबतक (!lf.found && ret >= 0) अणु
		अगर (dwarf_nextcu(dbg->dbg, off, &noff, &cuhl,
				 शून्य, शून्य, शून्य) != 0)
			अवरोध;

		/* Get the DIE(Debugging Inक्रमmation Entry) of this CU */
		diep = dwarf_offdie(dbg->dbg, off + cuhl, &lf.cu_die);
		अगर (!diep) अणु
			off = noff;
			जारी;
		पूर्ण

		/* Check अगर target file is included. */
		अगर (lr->file)
			lf.fname = cu_find_realpath(&lf.cu_die, lr->file);
		अन्यथा
			lf.fname = 0;

		अगर (!lr->file || lf.fname) अणु
			अगर (lr->function)
				ret = find_line_range_by_func(&lf);
			अन्यथा अणु
				lf.lno_s = lr->start;
				lf.lno_e = lr->end;
				ret = find_line_range_by_line(शून्य, &lf);
			पूर्ण
		पूर्ण
		off = noff;
	पूर्ण

found:
	/* Store comp_dir */
	अगर (lf.found) अणु
		comp_dir = cu_get_comp_dir(&lf.cu_die);
		अगर (comp_dir) अणु
			lr->comp_dir = strdup(comp_dir);
			अगर (!lr->comp_dir)
				ret = -ENOMEM;
		पूर्ण
	पूर्ण

	pr_debug("path: %s\n", lr->path);
	वापस (ret < 0) ? ret : lf.found;
पूर्ण

#अगर_घोषित HAVE_DEBUGINFOD_SUPPORT
/* debuginfod करोesn't require the comp_dir but buildid is required */
अटल पूर्णांक get_source_from_debuginfod(स्थिर अक्षर *raw_path,
				स्थिर अक्षर *sbuild_id, अक्षर **new_path)
अणु
	debuginfod_client *c = debuginfod_begin();
	स्थिर अक्षर *p = raw_path;
	पूर्णांक fd;

	अगर (!c)
		वापस -ENOMEM;

	fd = debuginfod_find_source(c, (स्थिर अचिन्हित अक्षर *)sbuild_id,
				0, p, new_path);
	pr_debug("Search %s from debuginfod -> %d\n", p, fd);
	अगर (fd >= 0)
		बंद(fd);
	debuginfod_end(c);
	अगर (fd < 0) अणु
		pr_debug("Failed to find %s in debuginfod (%s)\n",
			raw_path, sbuild_id);
		वापस -ENOENT;
	पूर्ण
	pr_debug("Got a source %s\n", *new_path);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक get_source_from_debuginfod(स्थिर अक्षर *raw_path __maybe_unused,
				स्थिर अक्षर *sbuild_id __maybe_unused,
				अक्षर **new_path __maybe_unused)
अणु
	वापस -ENOTSUP;
पूर्ण
#पूर्ण_अगर
/*
 * Find a src file from a DWARF tag path. Prepend optional source path prefix
 * and chop off leading directories that करो not exist. Result is passed back as
 * a newly allocated path on success.
 * Return 0 अगर file was found and पढ़ोable, -त्रुटि_सं otherwise.
 */
पूर्णांक find_source_path(स्थिर अक्षर *raw_path, स्थिर अक्षर *sbuild_id,
		स्थिर अक्षर *comp_dir, अक्षर **new_path)
अणु
	स्थिर अक्षर *prefix = symbol_conf.source_prefix;

	अगर (sbuild_id && !prefix) अणु
		अगर (!get_source_from_debuginfod(raw_path, sbuild_id, new_path))
			वापस 0;
	पूर्ण

	अगर (!prefix) अणु
		अगर (raw_path[0] != '/' && comp_dir)
			/* If not an असलolute path, try to use comp_dir */
			prefix = comp_dir;
		अन्यथा अणु
			अगर (access(raw_path, R_OK) == 0) अणु
				*new_path = strdup(raw_path);
				वापस *new_path ? 0 : -ENOMEM;
			पूर्ण अन्यथा
				वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण

	*new_path = दो_स्मृति((म_माप(prefix) + म_माप(raw_path) + 2));
	अगर (!*new_path)
		वापस -ENOMEM;

	क्रम (;;) अणु
		प्र_लिखो(*new_path, "%s/%s", prefix, raw_path);

		अगर (access(*new_path, R_OK) == 0)
			वापस 0;

		अगर (!symbol_conf.source_prefix) अणु
			/* In हाल of searching comp_dir, करोn't retry */
			zमुक्त(new_path);
			वापस -त्रुटि_सं;
		पूर्ण

		चयन (त्रुटि_सं) अणु
		हाल ENAMETOOLONG:
		हाल ENOENT:
		हाल EROFS:
		हाल EFAULT:
			raw_path = म_अक्षर(++raw_path, '/');
			अगर (!raw_path) अणु
				zमुक्त(new_path);
				वापस -ENOENT;
			पूर्ण
			जारी;

		शेष:
			zमुक्त(new_path);
			वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण
पूर्ण
