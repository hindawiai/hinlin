<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#समावेश <माला.स>
#समावेश <मानककोष.स>

#समावेश <arch/elf.h>
#समावेश <objtool/builtin.h>
#समावेश <objtool/cfi.h>
#समावेश <objtool/arch.h>
#समावेश <objtool/check.h>
#समावेश <objtool/special.h>
#समावेश <objtool/warn.h>
#समावेश <objtool/endianness.h>

#समावेश <linux/objtool.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अटल_call_types.h>

काष्ठा alternative अणु
	काष्ठा list_head list;
	काष्ठा inकाष्ठाion *insn;
	bool skip_orig;
पूर्ण;

काष्ठा cfi_init_state initial_func_cfi;

काष्ठा inकाष्ठाion *find_insn(काष्ठा objtool_file *file,
			      काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	काष्ठा inकाष्ठाion *insn;

	hash_क्रम_each_possible(file->insn_hash, insn, hash, sec_offset_hash(sec, offset)) अणु
		अगर (insn->sec == sec && insn->offset == offset)
			वापस insn;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा inकाष्ठाion *next_insn_same_sec(काष्ठा objtool_file *file,
					      काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा inकाष्ठाion *next = list_next_entry(insn, list);

	अगर (!next || &next->list == &file->insn_list || next->sec != insn->sec)
		वापस शून्य;

	वापस next;
पूर्ण

अटल काष्ठा inकाष्ठाion *next_insn_same_func(काष्ठा objtool_file *file,
					       काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा inकाष्ठाion *next = list_next_entry(insn, list);
	काष्ठा symbol *func = insn->func;

	अगर (!func)
		वापस शून्य;

	अगर (&next->list != &file->insn_list && next->func == func)
		वापस next;

	/* Check अगर we're alपढ़ोy in the subfunction: */
	अगर (func == func->cfunc)
		वापस शून्य;

	/* Move to the subfunction: */
	वापस find_insn(file, func->cfunc->sec, func->cfunc->offset);
पूर्ण

अटल काष्ठा inकाष्ठाion *prev_insn_same_sym(काष्ठा objtool_file *file,
					       काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा inकाष्ठाion *prev = list_prev_entry(insn, list);

	अगर (&prev->list != &file->insn_list && prev->func == insn->func)
		वापस prev;

	वापस शून्य;
पूर्ण

#घोषणा func_क्रम_each_insn(file, func, insn)				\
	क्रम (insn = find_insn(file, func->sec, func->offset);		\
	     insn;							\
	     insn = next_insn_same_func(file, insn))

#घोषणा sym_क्रम_each_insn(file, sym, insn)				\
	क्रम (insn = find_insn(file, sym->sec, sym->offset);		\
	     insn && &insn->list != &file->insn_list &&			\
		insn->sec == sym->sec &&				\
		insn->offset < sym->offset + sym->len;			\
	     insn = list_next_entry(insn, list))

#घोषणा sym_क्रम_each_insn_जारी_reverse(file, sym, insn)		\
	क्रम (insn = list_prev_entry(insn, list);			\
	     &insn->list != &file->insn_list &&				\
		insn->sec == sym->sec && insn->offset >= sym->offset;	\
	     insn = list_prev_entry(insn, list))

#घोषणा sec_क्रम_each_insn_from(file, insn)				\
	क्रम (; insn; insn = next_insn_same_sec(file, insn))

#घोषणा sec_क्रम_each_insn_जारी(file, insn)				\
	क्रम (insn = next_insn_same_sec(file, insn); insn;		\
	     insn = next_insn_same_sec(file, insn))

अटल bool is_jump_table_jump(काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा alt_group *alt_group = insn->alt_group;

	अगर (insn->jump_table)
		वापस true;

	/* Retpoline alternative क्रम a jump table? */
	वापस alt_group && alt_group->orig_group &&
	       alt_group->orig_group->first_insn->jump_table;
पूर्ण

अटल bool is_sibling_call(काष्ठा inकाष्ठाion *insn)
अणु
	/*
	 * Assume only ELF functions can make sibling calls.  This ensures
	 * sibling call detection consistency between vmlinux.o and inभागidual
	 * objects.
	 */
	अगर (!insn->func)
		वापस false;

	/* An indirect jump is either a sibling call or a jump to a table. */
	अगर (insn->type == INSN_JUMP_DYNAMIC)
		वापस !is_jump_table_jump(insn);

	/* add_jump_destinations() sets insn->call_dest क्रम sibling calls. */
	वापस (is_अटल_jump(insn) && insn->call_dest);
पूर्ण

/*
 * This checks to see अगर the given function is a "noreturn" function.
 *
 * For global functions which are outside the scope of this object file, we
 * have to keep a manual list of them.
 *
 * For local functions, we have to detect them manually by simply looking क्रम
 * the lack of a वापस inकाष्ठाion.
 */
अटल bool __dead_end_function(काष्ठा objtool_file *file, काष्ठा symbol *func,
				पूर्णांक recursion)
अणु
	पूर्णांक i;
	काष्ठा inकाष्ठाion *insn;
	bool empty = true;

	/*
	 * Unक्रमtunately these have to be hard coded because the noवापस
	 * attribute isn't provided in ELF data.
	 */
	अटल स्थिर अक्षर * स्थिर global_noवापसs[] = अणु
		"__stack_chk_fail",
		"panic",
		"do_exit",
		"do_task_dead",
		"__module_put_and_exit",
		"complete_and_exit",
		"__reiserfs_panic",
		"lbug_with_loc",
		"fortify_panic",
		"usercopy_abort",
		"machine_real_restart",
		"rewind_stack_do_exit",
		"kunit_try_catch_throw",
		"xen_start_kernel",
	पूर्ण;

	अगर (!func)
		वापस false;

	अगर (func->bind == STB_WEAK)
		वापस false;

	अगर (func->bind == STB_GLOBAL)
		क्रम (i = 0; i < ARRAY_SIZE(global_noवापसs); i++)
			अगर (!म_भेद(func->name, global_noवापसs[i]))
				वापस true;

	अगर (!func->len)
		वापस false;

	insn = find_insn(file, func->sec, func->offset);
	अगर (!insn->func)
		वापस false;

	func_क्रम_each_insn(file, func, insn) अणु
		empty = false;

		अगर (insn->type == INSN_RETURN)
			वापस false;
	पूर्ण

	अगर (empty)
		वापस false;

	/*
	 * A function can have a sibling call instead of a वापस.  In that
	 * हाल, the function's dead-end status depends on whether the target
	 * of the sibling call वापसs.
	 */
	func_क्रम_each_insn(file, func, insn) अणु
		अगर (is_sibling_call(insn)) अणु
			काष्ठा inकाष्ठाion *dest = insn->jump_dest;

			अगर (!dest)
				/* sibling call to another file */
				वापस false;

			/* local sibling call */
			अगर (recursion == 5) अणु
				/*
				 * Infinite recursion: two functions have
				 * sibling calls to each other.  This is a very
				 * rare हाल.  It means they aren't dead ends.
				 */
				वापस false;
			पूर्ण

			वापस __dead_end_function(file, dest->func, recursion+1);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool dead_end_function(काष्ठा objtool_file *file, काष्ठा symbol *func)
अणु
	वापस __dead_end_function(file, func, 0);
पूर्ण

अटल व्योम init_cfi_state(काष्ठा cfi_state *cfi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CFI_NUM_REGS; i++) अणु
		cfi->regs[i].base = CFI_UNDEFINED;
		cfi->vals[i].base = CFI_UNDEFINED;
	पूर्ण
	cfi->cfa.base = CFI_UNDEFINED;
	cfi->drap_reg = CFI_UNDEFINED;
	cfi->drap_offset = -1;
पूर्ण

अटल व्योम init_insn_state(काष्ठा insn_state *state, काष्ठा section *sec)
अणु
	स_रखो(state, 0, माप(*state));
	init_cfi_state(&state->cfi);

	/*
	 * We need the full vmlinux क्रम noinstr validation, otherwise we can
	 * not correctly determine insn->call_dest->sec (बाह्यal symbols करो
	 * not have a section).
	 */
	अगर (vmlinux && noinstr && sec)
		state->noinstr = sec->noinstr;
पूर्ण

/*
 * Call the arch-specअगरic inकाष्ठाion decoder क्रम all the inकाष्ठाions and add
 * them to the global inकाष्ठाion list.
 */
अटल पूर्णांक decode_inकाष्ठाions(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	काष्ठा symbol *func;
	अचिन्हित दीर्घ offset;
	काष्ठा inकाष्ठाion *insn;
	अचिन्हित दीर्घ nr_insns = 0;
	पूर्णांक ret;

	क्रम_each_sec(file, sec) अणु

		अगर (!(sec->sh.sh_flags & SHF_EXECINSTR))
			जारी;

		अगर (म_भेद(sec->name, ".altinstr_replacement") &&
		    म_भेद(sec->name, ".altinstr_aux") &&
		    म_भेदन(sec->name, ".discard.", 9))
			sec->text = true;

		अगर (!म_भेद(sec->name, ".noinstr.text") ||
		    !म_भेद(sec->name, ".entry.text"))
			sec->noinstr = true;

		क्रम (offset = 0; offset < sec->len; offset += insn->len) अणु
			insn = दो_स्मृति(माप(*insn));
			अगर (!insn) अणु
				WARN("malloc failed");
				वापस -1;
			पूर्ण
			स_रखो(insn, 0, माप(*insn));
			INIT_LIST_HEAD(&insn->alts);
			INIT_LIST_HEAD(&insn->stack_ops);
			init_cfi_state(&insn->cfi);

			insn->sec = sec;
			insn->offset = offset;

			ret = arch_decode_inकाष्ठाion(file->elf, sec, offset,
						      sec->len - offset,
						      &insn->len, &insn->type,
						      &insn->immediate,
						      &insn->stack_ops);
			अगर (ret)
				जाओ err;

			hash_add(file->insn_hash, &insn->hash, sec_offset_hash(sec, insn->offset));
			list_add_tail(&insn->list, &file->insn_list);
			nr_insns++;
		पूर्ण

		list_क्रम_each_entry(func, &sec->symbol_list, list) अणु
			अगर (func->type != STT_FUNC || func->alias != func)
				जारी;

			अगर (!find_insn(file, sec, func->offset)) अणु
				WARN("%s(): can't find starting instruction",
				     func->name);
				वापस -1;
			पूर्ण

			sym_क्रम_each_insn(file, func, insn)
				insn->func = func;
		पूर्ण
	पूर्ण

	अगर (stats)
		म_लिखो("nr_insns: %lu\n", nr_insns);

	वापस 0;

err:
	मुक्त(insn);
	वापस ret;
पूर्ण

अटल काष्ठा inकाष्ठाion *find_last_insn(काष्ठा objtool_file *file,
					  काष्ठा section *sec)
अणु
	काष्ठा inकाष्ठाion *insn = शून्य;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक end = (sec->len > 10) ? sec->len - 10 : 0;

	क्रम (offset = sec->len - 1; offset >= end && !insn; offset--)
		insn = find_insn(file, sec, offset);

	वापस insn;
पूर्ण

/*
 * Mark "ud2" inकाष्ठाions and manually annotated dead ends.
 */
अटल पूर्णांक add_dead_ends(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	काष्ठा reloc *reloc;
	काष्ठा inकाष्ठाion *insn;

	/*
	 * By शेष, "ud2" is a dead end unless otherwise annotated, because
	 * GCC 7 inserts it क्रम certain भागide-by-zero हालs.
	 */
	क्रम_each_insn(file, insn)
		अगर (insn->type == INSN_BUG)
			insn->dead_end = true;

	/*
	 * Check क्रम manually annotated dead ends.
	 */
	sec = find_section_by_name(file->elf, ".rela.discard.unreachable");
	अगर (!sec)
		जाओ reachable;

	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		अगर (reloc->sym->type != STT_SECTION) अणु
			WARN("unexpected relocation symbol type in %s", sec->name);
			वापस -1;
		पूर्ण
		insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (insn)
			insn = list_prev_entry(insn, list);
		अन्यथा अगर (reloc->addend == reloc->sym->sec->len) अणु
			insn = find_last_insn(file, reloc->sym->sec);
			अगर (!insn) अणु
				WARN("can't find unreachable insn at %s+0x%x",
				     reloc->sym->sec->name, reloc->addend);
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			WARN("can't find unreachable insn at %s+0x%x",
			     reloc->sym->sec->name, reloc->addend);
			वापस -1;
		पूर्ण

		insn->dead_end = true;
	पूर्ण

reachable:
	/*
	 * These manually annotated reachable checks are needed क्रम GCC 4.4,
	 * where the Linux unreachable() macro isn't supported.  In that हाल
	 * GCC करोesn't know the "ud2" is fatal, so it generates code as if it's
	 * not a dead end.
	 */
	sec = find_section_by_name(file->elf, ".rela.discard.reachable");
	अगर (!sec)
		वापस 0;

	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		अगर (reloc->sym->type != STT_SECTION) अणु
			WARN("unexpected relocation symbol type in %s", sec->name);
			वापस -1;
		पूर्ण
		insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (insn)
			insn = list_prev_entry(insn, list);
		अन्यथा अगर (reloc->addend == reloc->sym->sec->len) अणु
			insn = find_last_insn(file, reloc->sym->sec);
			अगर (!insn) अणु
				WARN("can't find reachable insn at %s+0x%x",
				     reloc->sym->sec->name, reloc->addend);
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			WARN("can't find reachable insn at %s+0x%x",
			     reloc->sym->sec->name, reloc->addend);
			वापस -1;
		पूर्ण

		insn->dead_end = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक create_अटल_call_sections(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	काष्ठा अटल_call_site *site;
	काष्ठा inकाष्ठाion *insn;
	काष्ठा symbol *key_sym;
	अक्षर *key_name, *पंचांगp;
	पूर्णांक idx;

	sec = find_section_by_name(file->elf, ".static_call_sites");
	अगर (sec) अणु
		INIT_LIST_HEAD(&file->अटल_call_list);
		WARN("file already has .static_call_sites section, skipping");
		वापस 0;
	पूर्ण

	अगर (list_empty(&file->अटल_call_list))
		वापस 0;

	idx = 0;
	list_क्रम_each_entry(insn, &file->अटल_call_list, call_node)
		idx++;

	sec = elf_create_section(file->elf, ".static_call_sites", SHF_WRITE,
				 माप(काष्ठा अटल_call_site), idx);
	अगर (!sec)
		वापस -1;

	idx = 0;
	list_क्रम_each_entry(insn, &file->अटल_call_list, call_node) अणु

		site = (काष्ठा अटल_call_site *)sec->data->d_buf + idx;
		स_रखो(site, 0, माप(काष्ठा अटल_call_site));

		/* populate reloc क्रम 'addr' */
		अगर (elf_add_reloc_to_insn(file->elf, sec,
					  idx * माप(काष्ठा अटल_call_site),
					  R_X86_64_PC32,
					  insn->sec, insn->offset))
			वापस -1;

		/* find key symbol */
		key_name = strdup(insn->call_dest->name);
		अगर (!key_name) अणु
			लिखो_त्रुटि("strdup");
			वापस -1;
		पूर्ण
		अगर (म_भेदन(key_name, STATIC_CALL_TRAMP_PREFIX_STR,
			    STATIC_CALL_TRAMP_PREFIX_LEN)) अणु
			WARN("static_call: trampoline name malformed: %s", key_name);
			वापस -1;
		पूर्ण
		पंचांगp = key_name + STATIC_CALL_TRAMP_PREFIX_LEN - STATIC_CALL_KEY_PREFIX_LEN;
		स_नकल(पंचांगp, STATIC_CALL_KEY_PREFIX_STR, STATIC_CALL_KEY_PREFIX_LEN);

		key_sym = find_symbol_by_name(file->elf, पंचांगp);
		अगर (!key_sym) अणु
			अगर (!module) अणु
				WARN("static_call: can't find static_call_key symbol: %s", पंचांगp);
				वापस -1;
			पूर्ण

			/*
			 * For modules(), the key might not be exported, which
			 * means the module can make अटल calls but isn't
			 * allowed to change them.
			 *
			 * In that हाल we temporarily set the key to be the
			 * trampoline address.  This is fixed up in
			 * अटल_call_add_module().
			 */
			key_sym = insn->call_dest;
		पूर्ण
		मुक्त(key_name);

		/* populate reloc क्रम 'key' */
		अगर (elf_add_reloc(file->elf, sec,
				  idx * माप(काष्ठा अटल_call_site) + 4,
				  R_X86_64_PC32, key_sym,
				  is_sibling_call(insn) * STATIC_CALL_SITE_TAIL))
			वापस -1;

		idx++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक create_mcount_loc_sections(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	अचिन्हित दीर्घ *loc;
	काष्ठा inकाष्ठाion *insn;
	पूर्णांक idx;

	sec = find_section_by_name(file->elf, "__mcount_loc");
	अगर (sec) अणु
		INIT_LIST_HEAD(&file->mcount_loc_list);
		WARN("file already has __mcount_loc section, skipping");
		वापस 0;
	पूर्ण

	अगर (list_empty(&file->mcount_loc_list))
		वापस 0;

	idx = 0;
	list_क्रम_each_entry(insn, &file->mcount_loc_list, mcount_loc_node)
		idx++;

	sec = elf_create_section(file->elf, "__mcount_loc", 0, माप(अचिन्हित दीर्घ), idx);
	अगर (!sec)
		वापस -1;

	idx = 0;
	list_क्रम_each_entry(insn, &file->mcount_loc_list, mcount_loc_node) अणु

		loc = (अचिन्हित दीर्घ *)sec->data->d_buf + idx;
		स_रखो(loc, 0, माप(अचिन्हित दीर्घ));

		अगर (elf_add_reloc_to_insn(file->elf, sec,
					  idx * माप(अचिन्हित दीर्घ),
					  R_X86_64_64,
					  insn->sec, insn->offset))
			वापस -1;

		idx++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Warnings shouldn't be reported क्रम ignored functions.
 */
अटल व्योम add_ignores(काष्ठा objtool_file *file)
अणु
	काष्ठा inकाष्ठाion *insn;
	काष्ठा section *sec;
	काष्ठा symbol *func;
	काष्ठा reloc *reloc;

	sec = find_section_by_name(file->elf, ".rela.discard.func_stack_frame_non_standard");
	अगर (!sec)
		वापस;

	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		चयन (reloc->sym->type) अणु
		हाल STT_FUNC:
			func = reloc->sym;
			अवरोध;

		हाल STT_SECTION:
			func = find_func_by_offset(reloc->sym->sec, reloc->addend);
			अगर (!func)
				जारी;
			अवरोध;

		शेष:
			WARN("unexpected relocation symbol type in %s: %d", sec->name, reloc->sym->type);
			जारी;
		पूर्ण

		func_क्रम_each_insn(file, func, insn)
			insn->ignore = true;
	पूर्ण
पूर्ण

/*
 * This is a whitelist of functions that is allowed to be called with AC set.
 * The list is meant to be minimal and only contains compiler instrumentation
 * ABI and a few functions used to implement *_अणुto,fromपूर्ण_user() functions.
 *
 * These functions must not directly change AC, but may PUSHF/POPF.
 */
अटल स्थिर अक्षर *uaccess_safe_builtin[] = अणु
	/* KASAN */
	"kasan_report",
	"kasan_check_range",
	/* KASAN out-of-line */
	"__asan_loadN_noabort",
	"__asan_load1_noabort",
	"__asan_load2_noabort",
	"__asan_load4_noabort",
	"__asan_load8_noabort",
	"__asan_load16_noabort",
	"__asan_storeN_noabort",
	"__asan_store1_noabort",
	"__asan_store2_noabort",
	"__asan_store4_noabort",
	"__asan_store8_noabort",
	"__asan_store16_noabort",
	"__kasan_check_read",
	"__kasan_check_write",
	/* KASAN in-line */
	"__asan_report_load_n_noabort",
	"__asan_report_load1_noabort",
	"__asan_report_load2_noabort",
	"__asan_report_load4_noabort",
	"__asan_report_load8_noabort",
	"__asan_report_load16_noabort",
	"__asan_report_store_n_noabort",
	"__asan_report_store1_noabort",
	"__asan_report_store2_noabort",
	"__asan_report_store4_noabort",
	"__asan_report_store8_noabort",
	"__asan_report_store16_noabort",
	/* KCSAN */
	"__kcsan_check_access",
	"kcsan_found_watchpoint",
	"kcsan_setup_watchpoint",
	"kcsan_check_scoped_accesses",
	"kcsan_disable_current",
	"kcsan_enable_current_nowarn",
	/* KCSAN/TSAN */
	"__tsan_func_entry",
	"__tsan_func_exit",
	"__tsan_read_range",
	"__tsan_write_range",
	"__tsan_read1",
	"__tsan_read2",
	"__tsan_read4",
	"__tsan_read8",
	"__tsan_read16",
	"__tsan_write1",
	"__tsan_write2",
	"__tsan_write4",
	"__tsan_write8",
	"__tsan_write16",
	"__tsan_read_write1",
	"__tsan_read_write2",
	"__tsan_read_write4",
	"__tsan_read_write8",
	"__tsan_read_write16",
	"__tsan_atomic8_load",
	"__tsan_atomic16_load",
	"__tsan_atomic32_load",
	"__tsan_atomic64_load",
	"__tsan_atomic8_store",
	"__tsan_atomic16_store",
	"__tsan_atomic32_store",
	"__tsan_atomic64_store",
	"__tsan_atomic8_exchange",
	"__tsan_atomic16_exchange",
	"__tsan_atomic32_exchange",
	"__tsan_atomic64_exchange",
	"__tsan_atomic8_fetch_add",
	"__tsan_atomic16_fetch_add",
	"__tsan_atomic32_fetch_add",
	"__tsan_atomic64_fetch_add",
	"__tsan_atomic8_fetch_sub",
	"__tsan_atomic16_fetch_sub",
	"__tsan_atomic32_fetch_sub",
	"__tsan_atomic64_fetch_sub",
	"__tsan_atomic8_fetch_and",
	"__tsan_atomic16_fetch_and",
	"__tsan_atomic32_fetch_and",
	"__tsan_atomic64_fetch_and",
	"__tsan_atomic8_fetch_or",
	"__tsan_atomic16_fetch_or",
	"__tsan_atomic32_fetch_or",
	"__tsan_atomic64_fetch_or",
	"__tsan_atomic8_fetch_xor",
	"__tsan_atomic16_fetch_xor",
	"__tsan_atomic32_fetch_xor",
	"__tsan_atomic64_fetch_xor",
	"__tsan_atomic8_fetch_nand",
	"__tsan_atomic16_fetch_nand",
	"__tsan_atomic32_fetch_nand",
	"__tsan_atomic64_fetch_nand",
	"__tsan_atomic8_compare_exchange_strong",
	"__tsan_atomic16_compare_exchange_strong",
	"__tsan_atomic32_compare_exchange_strong",
	"__tsan_atomic64_compare_exchange_strong",
	"__tsan_atomic8_compare_exchange_weak",
	"__tsan_atomic16_compare_exchange_weak",
	"__tsan_atomic32_compare_exchange_weak",
	"__tsan_atomic64_compare_exchange_weak",
	"__tsan_atomic8_compare_exchange_val",
	"__tsan_atomic16_compare_exchange_val",
	"__tsan_atomic32_compare_exchange_val",
	"__tsan_atomic64_compare_exchange_val",
	"__tsan_atomic_thread_fence",
	"__tsan_atomic_signal_fence",
	/* KCOV */
	"write_comp_data",
	"check_kcov_mode",
	"__sanitizer_cov_trace_pc",
	"__sanitizer_cov_trace_const_cmp1",
	"__sanitizer_cov_trace_const_cmp2",
	"__sanitizer_cov_trace_const_cmp4",
	"__sanitizer_cov_trace_const_cmp8",
	"__sanitizer_cov_trace_cmp1",
	"__sanitizer_cov_trace_cmp2",
	"__sanitizer_cov_trace_cmp4",
	"__sanitizer_cov_trace_cmp8",
	"__sanitizer_cov_trace_switch",
	/* UBSAN */
	"ubsan_type_mismatch_common",
	"__ubsan_handle_type_mismatch",
	"__ubsan_handle_type_mismatch_v1",
	"__ubsan_handle_shift_out_of_bounds",
	/* misc */
	"csum_partial_copy_generic",
	"copy_mc_fragile",
	"copy_mc_fragile_handle_tail",
	"copy_mc_enhanced_fast_string",
	"ftrace_likely_update", /* CONFIG_TRACE_BRANCH_PROFILING */
	शून्य
पूर्ण;

अटल व्योम add_uaccess_safe(काष्ठा objtool_file *file)
अणु
	काष्ठा symbol *func;
	स्थिर अक्षर **name;

	अगर (!uaccess)
		वापस;

	क्रम (name = uaccess_safe_builtin; *name; name++) अणु
		func = find_symbol_by_name(file->elf, *name);
		अगर (!func)
			जारी;

		func->uaccess_safe = true;
	पूर्ण
पूर्ण

/*
 * FIXME: For now, just ignore any alternatives which add retpolines.  This is
 * a temporary hack, as it करोesn't allow ORC to unwind from inside a retpoline.
 * But it at least allows objtool to understand the control flow *around* the
 * retpoline.
 */
अटल पूर्णांक add_ignore_alternatives(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	काष्ठा reloc *reloc;
	काष्ठा inकाष्ठाion *insn;

	sec = find_section_by_name(file->elf, ".rela.discard.ignore_alts");
	अगर (!sec)
		वापस 0;

	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		अगर (reloc->sym->type != STT_SECTION) अणु
			WARN("unexpected relocation symbol type in %s", sec->name);
			वापस -1;
		पूर्ण

		insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (!insn) अणु
			WARN("bad .discard.ignore_alts entry");
			वापस -1;
		पूर्ण

		insn->ignore_alts = true;
	पूर्ण

	वापस 0;
पूर्ण

__weak bool arch_is_retpoline(काष्ठा symbol *sym)
अणु
	वापस false;
पूर्ण

#घोषणा NEGATIVE_RELOC	((व्योम *)-1L)

अटल काष्ठा reloc *insn_reloc(काष्ठा objtool_file *file, काष्ठा inकाष्ठाion *insn)
अणु
	अगर (insn->reloc == NEGATIVE_RELOC)
		वापस शून्य;

	अगर (!insn->reloc) अणु
		insn->reloc = find_reloc_by_dest_range(file->elf, insn->sec,
						       insn->offset, insn->len);
		अगर (!insn->reloc) अणु
			insn->reloc = NEGATIVE_RELOC;
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस insn->reloc;
पूर्ण

/*
 * Find the destination inकाष्ठाions क्रम all jumps.
 */
अटल पूर्णांक add_jump_destinations(काष्ठा objtool_file *file)
अणु
	काष्ठा inकाष्ठाion *insn;
	काष्ठा reloc *reloc;
	काष्ठा section *dest_sec;
	अचिन्हित दीर्घ dest_off;

	क्रम_each_insn(file, insn) अणु
		अगर (!is_अटल_jump(insn))
			जारी;

		reloc = insn_reloc(file, insn);
		अगर (!reloc) अणु
			dest_sec = insn->sec;
			dest_off = arch_jump_destination(insn);
		पूर्ण अन्यथा अगर (reloc->sym->type == STT_SECTION) अणु
			dest_sec = reloc->sym->sec;
			dest_off = arch_dest_reloc_offset(reloc->addend);
		पूर्ण अन्यथा अगर (arch_is_retpoline(reloc->sym)) अणु
			/*
			 * Retpoline jumps are really dynamic jumps in
			 * disguise, so convert them accordingly.
			 */
			अगर (insn->type == INSN_JUMP_UNCONDITIONAL)
				insn->type = INSN_JUMP_DYNAMIC;
			अन्यथा
				insn->type = INSN_JUMP_DYNAMIC_CONDITIONAL;

			list_add_tail(&insn->call_node,
				      &file->retpoline_call_list);

			insn->retpoline_safe = true;
			जारी;
		पूर्ण अन्यथा अगर (insn->func) अणु
			/* पूर्णांकernal or बाह्यal sibling call (with reloc) */
			insn->call_dest = reloc->sym;
			अगर (insn->call_dest->अटल_call_tramp) अणु
				list_add_tail(&insn->call_node,
					      &file->अटल_call_list);
			पूर्ण
			जारी;
		पूर्ण अन्यथा अगर (reloc->sym->sec->idx) अणु
			dest_sec = reloc->sym->sec;
			dest_off = reloc->sym->sym.st_value +
				   arch_dest_reloc_offset(reloc->addend);
		पूर्ण अन्यथा अणु
			/* non-func यंत्र code jumping to another file */
			जारी;
		पूर्ण

		insn->jump_dest = find_insn(file, dest_sec, dest_off);
		अगर (!insn->jump_dest) अणु

			/*
			 * This is a special हाल where an alt inकाष्ठाion
			 * jumps past the end of the section.  These are
			 * handled later in handle_group_alt().
			 */
			अगर (!म_भेद(insn->sec->name, ".altinstr_replacement"))
				जारी;

			WARN_FUNC("can't find jump dest instruction at %s+0x%lx",
				  insn->sec, insn->offset, dest_sec->name,
				  dest_off);
			वापस -1;
		पूर्ण

		/*
		 * Cross-function jump.
		 */
		अगर (insn->func && insn->jump_dest->func &&
		    insn->func != insn->jump_dest->func) अणु

			/*
			 * For GCC 8+, create parent/child links क्रम any cold
			 * subfunctions.  This is _mostly_ redundant with a
			 * similar initialization in पढ़ो_symbols().
			 *
			 * If a function has aliases, we want the *first* such
			 * function in the symbol table to be the subfunction's
			 * parent.  In that हाल we overग_लिखो the
			 * initialization करोne in पढ़ो_symbols().
			 *
			 * However this code can't completely replace the
			 * पढ़ो_symbols() code because this करोesn't detect the
			 * हाल where the parent function's only reference to a
			 * subfunction is through a jump table.
			 */
			अगर (!म_माला(insn->func->name, ".cold") &&
			    म_माला(insn->jump_dest->func->name, ".cold")) अणु
				insn->func->cfunc = insn->jump_dest->func;
				insn->jump_dest->func->pfunc = insn->func;

			पूर्ण अन्यथा अगर (insn->jump_dest->func->pfunc != insn->func->pfunc &&
				   insn->jump_dest->offset == insn->jump_dest->func->offset) अणु

				/* पूर्णांकernal sibling call (without reloc) */
				insn->call_dest = insn->jump_dest->func;
				अगर (insn->call_dest->अटल_call_tramp) अणु
					list_add_tail(&insn->call_node,
						      &file->अटल_call_list);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम हटाओ_insn_ops(काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा stack_op *op, *पंचांगp;

	list_क्रम_each_entry_safe(op, पंचांगp, &insn->stack_ops, list) अणु
		list_del(&op->list);
		मुक्त(op);
	पूर्ण
पूर्ण

अटल काष्ठा symbol *find_call_destination(काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	काष्ठा symbol *call_dest;

	call_dest = find_func_by_offset(sec, offset);
	अगर (!call_dest)
		call_dest = find_symbol_by_offset(sec, offset);

	वापस call_dest;
पूर्ण

/*
 * Find the destination inकाष्ठाions क्रम all calls.
 */
अटल पूर्णांक add_call_destinations(काष्ठा objtool_file *file)
अणु
	काष्ठा inकाष्ठाion *insn;
	अचिन्हित दीर्घ dest_off;
	काष्ठा reloc *reloc;

	क्रम_each_insn(file, insn) अणु
		अगर (insn->type != INSN_CALL)
			जारी;

		reloc = insn_reloc(file, insn);
		अगर (!reloc) अणु
			dest_off = arch_jump_destination(insn);
			insn->call_dest = find_call_destination(insn->sec, dest_off);

			अगर (insn->ignore)
				जारी;

			अगर (!insn->call_dest) अणु
				WARN_FUNC("unannotated intra-function call", insn->sec, insn->offset);
				वापस -1;
			पूर्ण

			अगर (insn->func && insn->call_dest->type != STT_FUNC) अणु
				WARN_FUNC("unsupported call to non-function",
					  insn->sec, insn->offset);
				वापस -1;
			पूर्ण

		पूर्ण अन्यथा अगर (reloc->sym->type == STT_SECTION) अणु
			dest_off = arch_dest_reloc_offset(reloc->addend);
			insn->call_dest = find_call_destination(reloc->sym->sec,
								dest_off);
			अगर (!insn->call_dest) अणु
				WARN_FUNC("can't find call dest symbol at %s+0x%lx",
					  insn->sec, insn->offset,
					  reloc->sym->sec->name,
					  dest_off);
				वापस -1;
			पूर्ण

		पूर्ण अन्यथा अगर (arch_is_retpoline(reloc->sym)) अणु
			/*
			 * Retpoline calls are really dynamic calls in
			 * disguise, so convert them accordingly.
			 */
			insn->type = INSN_CALL_DYNAMIC;
			insn->retpoline_safe = true;

			list_add_tail(&insn->call_node,
				      &file->retpoline_call_list);

			हटाओ_insn_ops(insn);
			जारी;

		पूर्ण अन्यथा
			insn->call_dest = reloc->sym;

		अगर (insn->call_dest && insn->call_dest->अटल_call_tramp) अणु
			list_add_tail(&insn->call_node,
				      &file->अटल_call_list);
		पूर्ण

		/*
		 * Many compilers cannot disable KCOV with a function attribute
		 * so they need a little help, NOP out any KCOV calls from noinstr
		 * text.
		 */
		अगर (insn->sec->noinstr &&
		    !म_भेदन(insn->call_dest->name, "__sanitizer_cov_", 16)) अणु
			अगर (reloc) अणु
				reloc->type = R_NONE;
				elf_ग_लिखो_reloc(file->elf, reloc);
			पूर्ण

			elf_ग_लिखो_insn(file->elf, insn->sec,
				       insn->offset, insn->len,
				       arch_nop_insn(insn->len));
			insn->type = INSN_NOP;
		पूर्ण

		अगर (mcount && !म_भेद(insn->call_dest->name, "__fentry__")) अणु
			अगर (reloc) अणु
				reloc->type = R_NONE;
				elf_ग_लिखो_reloc(file->elf, reloc);
			पूर्ण

			elf_ग_लिखो_insn(file->elf, insn->sec,
				       insn->offset, insn->len,
				       arch_nop_insn(insn->len));

			insn->type = INSN_NOP;

			list_add_tail(&insn->mcount_loc_node,
				      &file->mcount_loc_list);
		पूर्ण

		/*
		 * Whatever stack impact regular CALLs have, should be unकरोne
		 * by the RETURN of the called function.
		 *
		 * Annotated पूर्णांकra-function calls retain the stack_ops but
		 * are converted to JUMP, see पढ़ो_पूर्णांकra_function_calls().
		 */
		हटाओ_insn_ops(insn);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The .alternatives section requires some extra special care over and above
 * other special sections because alternatives are patched in place.
 */
अटल पूर्णांक handle_group_alt(काष्ठा objtool_file *file,
			    काष्ठा special_alt *special_alt,
			    काष्ठा inकाष्ठाion *orig_insn,
			    काष्ठा inकाष्ठाion **new_insn)
अणु
	काष्ठा inकाष्ठाion *last_orig_insn, *last_new_insn = शून्य, *insn, *nop = शून्य;
	काष्ठा alt_group *orig_alt_group, *new_alt_group;
	अचिन्हित दीर्घ dest_off;


	orig_alt_group = दो_स्मृति(माप(*orig_alt_group));
	अगर (!orig_alt_group) अणु
		WARN("malloc failed");
		वापस -1;
	पूर्ण
	orig_alt_group->cfi = सुस्मृति(special_alt->orig_len,
				     माप(काष्ठा cfi_state *));
	अगर (!orig_alt_group->cfi) अणु
		WARN("calloc failed");
		वापस -1;
	पूर्ण

	last_orig_insn = शून्य;
	insn = orig_insn;
	sec_क्रम_each_insn_from(file, insn) अणु
		अगर (insn->offset >= special_alt->orig_off + special_alt->orig_len)
			अवरोध;

		insn->alt_group = orig_alt_group;
		last_orig_insn = insn;
	पूर्ण
	orig_alt_group->orig_group = शून्य;
	orig_alt_group->first_insn = orig_insn;
	orig_alt_group->last_insn = last_orig_insn;


	new_alt_group = दो_स्मृति(माप(*new_alt_group));
	अगर (!new_alt_group) अणु
		WARN("malloc failed");
		वापस -1;
	पूर्ण

	अगर (special_alt->new_len < special_alt->orig_len) अणु
		/*
		 * Insert a fake nop at the end to make the replacement
		 * alt_group the same size as the original.  This is needed to
		 * allow propagate_alt_cfi() to करो its magic.  When the last
		 * inकाष्ठाion affects the stack, the inकाष्ठाion after it (the
		 * nop) will propagate the new state to the shared CFI array.
		 */
		nop = दो_स्मृति(माप(*nop));
		अगर (!nop) अणु
			WARN("malloc failed");
			वापस -1;
		पूर्ण
		स_रखो(nop, 0, माप(*nop));
		INIT_LIST_HEAD(&nop->alts);
		INIT_LIST_HEAD(&nop->stack_ops);
		init_cfi_state(&nop->cfi);

		nop->sec = special_alt->new_sec;
		nop->offset = special_alt->new_off + special_alt->new_len;
		nop->len = special_alt->orig_len - special_alt->new_len;
		nop->type = INSN_NOP;
		nop->func = orig_insn->func;
		nop->alt_group = new_alt_group;
		nop->ignore = orig_insn->ignore_alts;
	पूर्ण

	अगर (!special_alt->new_len) अणु
		*new_insn = nop;
		जाओ end;
	पूर्ण

	insn = *new_insn;
	sec_क्रम_each_insn_from(file, insn) अणु
		काष्ठा reloc *alt_reloc;

		अगर (insn->offset >= special_alt->new_off + special_alt->new_len)
			अवरोध;

		last_new_insn = insn;

		insn->ignore = orig_insn->ignore_alts;
		insn->func = orig_insn->func;
		insn->alt_group = new_alt_group;

		/*
		 * Since alternative replacement code is copy/pasted by the
		 * kernel after applying relocations, generally such code can't
		 * have relative-address relocation references to outside the
		 * .altinstr_replacement section, unless the arch's
		 * alternatives code can adjust the relative offsets
		 * accordingly.
		 */
		alt_reloc = insn_reloc(file, insn);
		अगर (alt_reloc &&
		    !arch_support_alt_relocation(special_alt, insn, alt_reloc)) अणु

			WARN_FUNC("unsupported relocation in alternatives section",
				  insn->sec, insn->offset);
			वापस -1;
		पूर्ण

		अगर (!is_अटल_jump(insn))
			जारी;

		अगर (!insn->immediate)
			जारी;

		dest_off = arch_jump_destination(insn);
		अगर (dest_off == special_alt->new_off + special_alt->new_len)
			insn->jump_dest = next_insn_same_sec(file, last_orig_insn);

		अगर (!insn->jump_dest) अणु
			WARN_FUNC("can't find alternative jump destination",
				  insn->sec, insn->offset);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (!last_new_insn) अणु
		WARN_FUNC("can't find last new alternative instruction",
			  special_alt->new_sec, special_alt->new_off);
		वापस -1;
	पूर्ण

	अगर (nop)
		list_add(&nop->list, &last_new_insn->list);
end:
	new_alt_group->orig_group = orig_alt_group;
	new_alt_group->first_insn = *new_insn;
	new_alt_group->last_insn = nop ? : last_new_insn;
	new_alt_group->cfi = orig_alt_group->cfi;
	वापस 0;
पूर्ण

/*
 * A jump table entry can either convert a nop to a jump or a jump to a nop.
 * If the original inकाष्ठाion is a jump, make the alt entry an effective nop
 * by just skipping the original inकाष्ठाion.
 */
अटल पूर्णांक handle_jump_alt(काष्ठा objtool_file *file,
			   काष्ठा special_alt *special_alt,
			   काष्ठा inकाष्ठाion *orig_insn,
			   काष्ठा inकाष्ठाion **new_insn)
अणु
	अगर (orig_insn->type == INSN_NOP)
		वापस 0;

	अगर (orig_insn->type != INSN_JUMP_UNCONDITIONAL) अणु
		WARN_FUNC("unsupported instruction at jump label",
			  orig_insn->sec, orig_insn->offset);
		वापस -1;
	पूर्ण

	*new_insn = list_next_entry(orig_insn, list);
	वापस 0;
पूर्ण

/*
 * Read all the special sections which have alternate inकाष्ठाions which can be
 * patched in or redirected to at runसमय.  Each inकाष्ठाion having alternate
 * inकाष्ठाion(s) has them added to its insn->alts list, which will be
 * traversed in validate_branch().
 */
अटल पूर्णांक add_special_section_alts(काष्ठा objtool_file *file)
अणु
	काष्ठा list_head special_alts;
	काष्ठा inकाष्ठाion *orig_insn, *new_insn;
	काष्ठा special_alt *special_alt, *पंचांगp;
	काष्ठा alternative *alt;
	पूर्णांक ret;

	ret = special_get_alts(file->elf, &special_alts);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry_safe(special_alt, पंचांगp, &special_alts, list) अणु

		orig_insn = find_insn(file, special_alt->orig_sec,
				      special_alt->orig_off);
		अगर (!orig_insn) अणु
			WARN_FUNC("special: can't find orig instruction",
				  special_alt->orig_sec, special_alt->orig_off);
			ret = -1;
			जाओ out;
		पूर्ण

		new_insn = शून्य;
		अगर (!special_alt->group || special_alt->new_len) अणु
			new_insn = find_insn(file, special_alt->new_sec,
					     special_alt->new_off);
			अगर (!new_insn) अणु
				WARN_FUNC("special: can't find new instruction",
					  special_alt->new_sec,
					  special_alt->new_off);
				ret = -1;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (special_alt->group) अणु
			अगर (!special_alt->orig_len) अणु
				WARN_FUNC("empty alternative entry",
					  orig_insn->sec, orig_insn->offset);
				जारी;
			पूर्ण

			ret = handle_group_alt(file, special_alt, orig_insn,
					       &new_insn);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अगर (special_alt->jump_or_nop) अणु
			ret = handle_jump_alt(file, special_alt, orig_insn,
					      &new_insn);
			अगर (ret)
				जाओ out;
		पूर्ण

		alt = दो_स्मृति(माप(*alt));
		अगर (!alt) अणु
			WARN("malloc failed");
			ret = -1;
			जाओ out;
		पूर्ण

		alt->insn = new_insn;
		alt->skip_orig = special_alt->skip_orig;
		orig_insn->ignore_alts |= special_alt->skip_alt;
		list_add_tail(&alt->list, &orig_insn->alts);

		list_del(&special_alt->list);
		मुक्त(special_alt);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक add_jump_table(काष्ठा objtool_file *file, काष्ठा inकाष्ठाion *insn,
			    काष्ठा reloc *table)
अणु
	काष्ठा reloc *reloc = table;
	काष्ठा inकाष्ठाion *dest_insn;
	काष्ठा alternative *alt;
	काष्ठा symbol *pfunc = insn->func->pfunc;
	अचिन्हित पूर्णांक prev_offset = 0;

	/*
	 * Each @reloc is a चयन table relocation which poपूर्णांकs to the target
	 * inकाष्ठाion.
	 */
	list_क्रम_each_entry_from(reloc, &table->sec->reloc_list, list) अणु

		/* Check क्रम the end of the table: */
		अगर (reloc != table && reloc->jump_table_start)
			अवरोध;

		/* Make sure the table entries are consecutive: */
		अगर (prev_offset && reloc->offset != prev_offset + 8)
			अवरोध;

		/* Detect function poपूर्णांकers from contiguous objects: */
		अगर (reloc->sym->sec == pfunc->sec &&
		    reloc->addend == pfunc->offset)
			अवरोध;

		dest_insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (!dest_insn)
			अवरोध;

		/* Make sure the destination is in the same function: */
		अगर (!dest_insn->func || dest_insn->func->pfunc != pfunc)
			अवरोध;

		alt = दो_स्मृति(माप(*alt));
		अगर (!alt) अणु
			WARN("malloc failed");
			वापस -1;
		पूर्ण

		alt->insn = dest_insn;
		list_add_tail(&alt->list, &insn->alts);
		prev_offset = reloc->offset;
	पूर्ण

	अगर (!prev_offset) अणु
		WARN_FUNC("can't find switch jump table",
			  insn->sec, insn->offset);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * find_jump_table() - Given a dynamic jump, find the चयन jump table
 * associated with it.
 */
अटल काष्ठा reloc *find_jump_table(काष्ठा objtool_file *file,
				      काष्ठा symbol *func,
				      काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा reloc *table_reloc;
	काष्ठा inकाष्ठाion *dest_insn, *orig_insn = insn;

	/*
	 * Backward search using the @first_jump_src links, these help aव्योम
	 * much of the 'in between' code. Which aव्योमs us getting confused by
	 * it.
	 */
	क्रम (;
	     insn && insn->func && insn->func->pfunc == func;
	     insn = insn->first_jump_src ?: prev_insn_same_sym(file, insn)) अणु

		अगर (insn != orig_insn && insn->type == INSN_JUMP_DYNAMIC)
			अवरोध;

		/* allow small jumps within the range */
		अगर (insn->type == INSN_JUMP_UNCONDITIONAL &&
		    insn->jump_dest &&
		    (insn->jump_dest->offset <= insn->offset ||
		     insn->jump_dest->offset > orig_insn->offset))
		    अवरोध;

		table_reloc = arch_find_चयन_table(file, insn);
		अगर (!table_reloc)
			जारी;
		dest_insn = find_insn(file, table_reloc->sym->sec, table_reloc->addend);
		अगर (!dest_insn || !dest_insn->func || dest_insn->func->pfunc != func)
			जारी;

		वापस table_reloc;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * First pass: Mark the head of each jump table so that in the next pass,
 * we know when a given jump table ends and the next one starts.
 */
अटल व्योम mark_func_jump_tables(काष्ठा objtool_file *file,
				    काष्ठा symbol *func)
अणु
	काष्ठा inकाष्ठाion *insn, *last = शून्य;
	काष्ठा reloc *reloc;

	func_क्रम_each_insn(file, func, insn) अणु
		अगर (!last)
			last = insn;

		/*
		 * Store back-poपूर्णांकers क्रम unconditional क्रमward jumps such
		 * that find_jump_table() can back-track using those and
		 * aव्योम some potentially confusing code.
		 */
		अगर (insn->type == INSN_JUMP_UNCONDITIONAL && insn->jump_dest &&
		    insn->offset > last->offset &&
		    insn->jump_dest->offset > insn->offset &&
		    !insn->jump_dest->first_jump_src) अणु

			insn->jump_dest->first_jump_src = insn;
			last = insn->jump_dest;
		पूर्ण

		अगर (insn->type != INSN_JUMP_DYNAMIC)
			जारी;

		reloc = find_jump_table(file, func, insn);
		अगर (reloc) अणु
			reloc->jump_table_start = true;
			insn->jump_table = reloc;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक add_func_jump_tables(काष्ठा objtool_file *file,
				  काष्ठा symbol *func)
अणु
	काष्ठा inकाष्ठाion *insn;
	पूर्णांक ret;

	func_क्रम_each_insn(file, func, insn) अणु
		अगर (!insn->jump_table)
			जारी;

		ret = add_jump_table(file, insn, insn->jump_table);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * For some चयन statements, gcc generates a jump table in the .rodata
 * section which contains a list of addresses within the function to jump to.
 * This finds these jump tables and adds them to the insn->alts lists.
 */
अटल पूर्णांक add_jump_table_alts(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	काष्ठा symbol *func;
	पूर्णांक ret;

	अगर (!file->rodata)
		वापस 0;

	क्रम_each_sec(file, sec) अणु
		list_क्रम_each_entry(func, &sec->symbol_list, list) अणु
			अगर (func->type != STT_FUNC)
				जारी;

			mark_func_jump_tables(file, func);
			ret = add_func_jump_tables(file, func);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_func_state(काष्ठा cfi_state *state)
अणु
	state->cfa = initial_func_cfi.cfa;
	स_नकल(&state->regs, &initial_func_cfi.regs,
	       CFI_NUM_REGS * माप(काष्ठा cfi_reg));
	state->stack_size = initial_func_cfi.cfa.offset;
पूर्ण

अटल पूर्णांक पढ़ो_unwind_hपूर्णांकs(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec, *relocsec;
	काष्ठा reloc *reloc;
	काष्ठा unwind_hपूर्णांक *hपूर्णांक;
	काष्ठा inकाष्ठाion *insn;
	पूर्णांक i;

	sec = find_section_by_name(file->elf, ".discard.unwind_hints");
	अगर (!sec)
		वापस 0;

	relocsec = sec->reloc;
	अगर (!relocsec) अणु
		WARN("missing .rela.discard.unwind_hints section");
		वापस -1;
	पूर्ण

	अगर (sec->len % माप(काष्ठा unwind_hपूर्णांक)) अणु
		WARN("struct unwind_hint size mismatch");
		वापस -1;
	पूर्ण

	file->hपूर्णांकs = true;

	क्रम (i = 0; i < sec->len / माप(काष्ठा unwind_hपूर्णांक); i++) अणु
		hपूर्णांक = (काष्ठा unwind_hपूर्णांक *)sec->data->d_buf + i;

		reloc = find_reloc_by_dest(file->elf, sec, i * माप(*hपूर्णांक));
		अगर (!reloc) अणु
			WARN("can't find reloc for unwind_hints[%d]", i);
			वापस -1;
		पूर्ण

		insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (!insn) अणु
			WARN("can't find insn for unwind_hints[%d]", i);
			वापस -1;
		पूर्ण

		insn->hपूर्णांक = true;

		अगर (hपूर्णांक->type == UNWIND_HINT_TYPE_FUNC) अणु
			set_func_state(&insn->cfi);
			जारी;
		पूर्ण

		अगर (arch_decode_hपूर्णांक_reg(insn, hपूर्णांक->sp_reg)) अणु
			WARN_FUNC("unsupported unwind_hint sp base reg %d",
				  insn->sec, insn->offset, hपूर्णांक->sp_reg);
			वापस -1;
		पूर्ण

		insn->cfi.cfa.offset = bswap_अगर_needed(hपूर्णांक->sp_offset);
		insn->cfi.type = hपूर्णांक->type;
		insn->cfi.end = hपूर्णांक->end;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_retpoline_hपूर्णांकs(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	काष्ठा inकाष्ठाion *insn;
	काष्ठा reloc *reloc;

	sec = find_section_by_name(file->elf, ".rela.discard.retpoline_safe");
	अगर (!sec)
		वापस 0;

	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		अगर (reloc->sym->type != STT_SECTION) अणु
			WARN("unexpected relocation symbol type in %s", sec->name);
			वापस -1;
		पूर्ण

		insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (!insn) अणु
			WARN("bad .discard.retpoline_safe entry");
			वापस -1;
		पूर्ण

		अगर (insn->type != INSN_JUMP_DYNAMIC &&
		    insn->type != INSN_CALL_DYNAMIC) अणु
			WARN_FUNC("retpoline_safe hint not an indirect jump/call",
				  insn->sec, insn->offset);
			वापस -1;
		पूर्ण

		insn->retpoline_safe = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_instr_hपूर्णांकs(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	काष्ठा inकाष्ठाion *insn;
	काष्ठा reloc *reloc;

	sec = find_section_by_name(file->elf, ".rela.discard.instr_end");
	अगर (!sec)
		वापस 0;

	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		अगर (reloc->sym->type != STT_SECTION) अणु
			WARN("unexpected relocation symbol type in %s", sec->name);
			वापस -1;
		पूर्ण

		insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (!insn) अणु
			WARN("bad .discard.instr_end entry");
			वापस -1;
		पूर्ण

		insn->instr--;
	पूर्ण

	sec = find_section_by_name(file->elf, ".rela.discard.instr_begin");
	अगर (!sec)
		वापस 0;

	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		अगर (reloc->sym->type != STT_SECTION) अणु
			WARN("unexpected relocation symbol type in %s", sec->name);
			वापस -1;
		पूर्ण

		insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (!insn) अणु
			WARN("bad .discard.instr_begin entry");
			वापस -1;
		पूर्ण

		insn->instr++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_पूर्णांकra_function_calls(काष्ठा objtool_file *file)
अणु
	काष्ठा inकाष्ठाion *insn;
	काष्ठा section *sec;
	काष्ठा reloc *reloc;

	sec = find_section_by_name(file->elf, ".rela.discard.intra_function_calls");
	अगर (!sec)
		वापस 0;

	list_क्रम_each_entry(reloc, &sec->reloc_list, list) अणु
		अचिन्हित दीर्घ dest_off;

		अगर (reloc->sym->type != STT_SECTION) अणु
			WARN("unexpected relocation symbol type in %s",
			     sec->name);
			वापस -1;
		पूर्ण

		insn = find_insn(file, reloc->sym->sec, reloc->addend);
		अगर (!insn) अणु
			WARN("bad .discard.intra_function_call entry");
			वापस -1;
		पूर्ण

		अगर (insn->type != INSN_CALL) अणु
			WARN_FUNC("intra_function_call not a direct call",
				  insn->sec, insn->offset);
			वापस -1;
		पूर्ण

		/*
		 * Treat पूर्णांकra-function CALLs as JMPs, but with a stack_op.
		 * See add_call_destinations(), which strips stack_ops from
		 * normal CALLs.
		 */
		insn->type = INSN_JUMP_UNCONDITIONAL;

		dest_off = insn->offset + insn->len + insn->immediate;
		insn->jump_dest = find_insn(file, insn->sec, dest_off);
		अगर (!insn->jump_dest) अणु
			WARN_FUNC("can't find call dest at %s+0x%lx",
				  insn->sec, insn->offset,
				  insn->sec->name, dest_off);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_अटल_call_tramps(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	काष्ठा symbol *func;

	क्रम_each_sec(file, sec) अणु
		list_क्रम_each_entry(func, &sec->symbol_list, list) अणु
			अगर (func->bind == STB_GLOBAL &&
			    !म_भेदन(func->name, STATIC_CALL_TRAMP_PREFIX_STR,
				     म_माप(STATIC_CALL_TRAMP_PREFIX_STR)))
				func->अटल_call_tramp = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mark_rodata(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	bool found = false;

	/*
	 * Search क्रम the following rodata sections, each of which can
	 * potentially contain jump tables:
	 *
	 * - .rodata: can contain GCC चयन tables
	 * - .rodata.<func>: same, अगर -fdata-sections is being used
	 * - .rodata..c_jump_table: contains C annotated jump tables
	 *
	 * .rodata.str1.* sections are ignored; they करोn't contain jump tables.
	 */
	क्रम_each_sec(file, sec) अणु
		अगर (!म_भेदन(sec->name, ".rodata", 7) &&
		    !म_माला(sec->name, ".str1.")) अणु
			sec->rodata = true;
			found = true;
		पूर्ण
	पूर्ण

	file->rodata = found;
पूर्ण

__weak पूर्णांक arch_reग_लिखो_retpolines(काष्ठा objtool_file *file)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक decode_sections(काष्ठा objtool_file *file)
अणु
	पूर्णांक ret;

	mark_rodata(file);

	ret = decode_inकाष्ठाions(file);
	अगर (ret)
		वापस ret;

	ret = add_dead_ends(file);
	अगर (ret)
		वापस ret;

	add_ignores(file);
	add_uaccess_safe(file);

	ret = add_ignore_alternatives(file);
	अगर (ret)
		वापस ret;

	/*
	 * Must be beक्रमe add_अणुjump_callपूर्ण_destination.
	 */
	ret = पढ़ो_अटल_call_tramps(file);
	अगर (ret)
		वापस ret;

	/*
	 * Must be beक्रमe add_special_section_alts() as that depends on
	 * jump_dest being set.
	 */
	ret = add_jump_destinations(file);
	अगर (ret)
		वापस ret;

	ret = add_special_section_alts(file);
	अगर (ret)
		वापस ret;

	/*
	 * Must be beक्रमe add_call_destination(); it changes INSN_CALL to
	 * INSN_JUMP.
	 */
	ret = पढ़ो_पूर्णांकra_function_calls(file);
	अगर (ret)
		वापस ret;

	ret = add_call_destinations(file);
	अगर (ret)
		वापस ret;

	ret = add_jump_table_alts(file);
	अगर (ret)
		वापस ret;

	ret = पढ़ो_unwind_hपूर्णांकs(file);
	अगर (ret)
		वापस ret;

	ret = पढ़ो_retpoline_hपूर्णांकs(file);
	अगर (ret)
		वापस ret;

	ret = पढ़ो_instr_hपूर्णांकs(file);
	अगर (ret)
		वापस ret;

	/*
	 * Must be after add_special_section_alts(), since this will emit
	 * alternatives. Must be after add_अणुjump,callपूर्ण_destination(), since
	 * those create the call insn lists.
	 */
	ret = arch_reग_लिखो_retpolines(file);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल bool is_fentry_call(काष्ठा inकाष्ठाion *insn)
अणु
	अगर (insn->type == INSN_CALL && insn->call_dest &&
	    insn->call_dest->type == STT_NOTYPE &&
	    !म_भेद(insn->call_dest->name, "__fentry__"))
		वापस true;

	वापस false;
पूर्ण

अटल bool has_modअगरied_stack_frame(काष्ठा inकाष्ठाion *insn, काष्ठा insn_state *state)
अणु
	काष्ठा cfi_state *cfi = &state->cfi;
	पूर्णांक i;

	अगर (cfi->cfa.base != initial_func_cfi.cfa.base || cfi->drap)
		वापस true;

	अगर (cfi->cfa.offset != initial_func_cfi.cfa.offset)
		वापस true;

	अगर (cfi->stack_size != initial_func_cfi.cfa.offset)
		वापस true;

	क्रम (i = 0; i < CFI_NUM_REGS; i++) अणु
		अगर (cfi->regs[i].base != initial_func_cfi.regs[i].base ||
		    cfi->regs[i].offset != initial_func_cfi.regs[i].offset)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool check_reg_frame_pos(स्थिर काष्ठा cfi_reg *reg,
				पूर्णांक expected_offset)
अणु
	वापस reg->base == CFI_CFA &&
	       reg->offset == expected_offset;
पूर्ण

अटल bool has_valid_stack_frame(काष्ठा insn_state *state)
अणु
	काष्ठा cfi_state *cfi = &state->cfi;

	अगर (cfi->cfa.base == CFI_BP &&
	    check_reg_frame_pos(&cfi->regs[CFI_BP], -cfi->cfa.offset) &&
	    check_reg_frame_pos(&cfi->regs[CFI_RA], -cfi->cfa.offset + 8))
		वापस true;

	अगर (cfi->drap && cfi->regs[CFI_BP].base == CFI_BP)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक update_cfi_state_regs(काष्ठा inकाष्ठाion *insn,
				  काष्ठा cfi_state *cfi,
				  काष्ठा stack_op *op)
अणु
	काष्ठा cfi_reg *cfa = &cfi->cfa;

	अगर (cfa->base != CFI_SP && cfa->base != CFI_SP_INसूचीECT)
		वापस 0;

	/* push */
	अगर (op->dest.type == OP_DEST_PUSH || op->dest.type == OP_DEST_PUSHF)
		cfa->offset += 8;

	/* pop */
	अगर (op->src.type == OP_SRC_POP || op->src.type == OP_SRC_POPF)
		cfa->offset -= 8;

	/* add immediate to sp */
	अगर (op->dest.type == OP_DEST_REG && op->src.type == OP_SRC_ADD &&
	    op->dest.reg == CFI_SP && op->src.reg == CFI_SP)
		cfa->offset -= op->src.offset;

	वापस 0;
पूर्ण

अटल व्योम save_reg(काष्ठा cfi_state *cfi, अचिन्हित अक्षर reg, पूर्णांक base, पूर्णांक offset)
अणु
	अगर (arch_callee_saved_reg(reg) &&
	    cfi->regs[reg].base == CFI_UNDEFINED) अणु
		cfi->regs[reg].base = base;
		cfi->regs[reg].offset = offset;
	पूर्ण
पूर्ण

अटल व्योम restore_reg(काष्ठा cfi_state *cfi, अचिन्हित अक्षर reg)
अणु
	cfi->regs[reg].base = initial_func_cfi.regs[reg].base;
	cfi->regs[reg].offset = initial_func_cfi.regs[reg].offset;
पूर्ण

/*
 * A note about DRAP stack alignment:
 *
 * GCC has the concept of a DRAP रेजिस्टर, which is used to help keep track of
 * the stack poपूर्णांकer when aligning the stack.  r10 or r13 is used as the DRAP
 * रेजिस्टर.  The typical DRAP pattern is:
 *
 *   4c 8d 54 24 08		lea    0x8(%rsp),%r10
 *   48 83 e4 c0		and    $0xffffffffffffffc0,%rsp
 *   41 ff 72 f8		pushq  -0x8(%r10)
 *   55				push   %rbp
 *   48 89 e5			mov    %rsp,%rbp
 *				(more pushes)
 *   41 52			push   %r10
 *				...
 *   41 5a			pop    %r10
 *				(more pops)
 *   5d				pop    %rbp
 *   49 8d 62 f8		lea    -0x8(%r10),%rsp
 *   c3				retq
 *
 * There are some variations in the epilogues, like:
 *
 *   5b				pop    %rbx
 *   41 5a			pop    %r10
 *   41 5c			pop    %r12
 *   41 5d			pop    %r13
 *   41 5e			pop    %r14
 *   c9				leaveq
 *   49 8d 62 f8		lea    -0x8(%r10),%rsp
 *   c3				retq
 *
 * and:
 *
 *   4c 8b 55 e8		mov    -0x18(%rbp),%r10
 *   48 8b 5d e0		mov    -0x20(%rbp),%rbx
 *   4c 8b 65 f0		mov    -0x10(%rbp),%r12
 *   4c 8b 6d f8		mov    -0x8(%rbp),%r13
 *   c9				leaveq
 *   49 8d 62 f8		lea    -0x8(%r10),%rsp
 *   c3				retq
 *
 * Someबार r13 is used as the DRAP रेजिस्टर, in which हाल it's saved and
 * restored beक्रमehand:
 *
 *   41 55			push   %r13
 *   4c 8d 6c 24 10		lea    0x10(%rsp),%r13
 *   48 83 e4 f0		and    $0xfffffffffffffff0,%rsp
 *				...
 *   49 8d 65 f0		lea    -0x10(%r13),%rsp
 *   41 5d			pop    %r13
 *   c3				retq
 */
अटल पूर्णांक update_cfi_state(काष्ठा inकाष्ठाion *insn,
			    काष्ठा inकाष्ठाion *next_insn,
			    काष्ठा cfi_state *cfi, काष्ठा stack_op *op)
अणु
	काष्ठा cfi_reg *cfa = &cfi->cfa;
	काष्ठा cfi_reg *regs = cfi->regs;

	/* stack operations करोn't make sense with an undefined CFA */
	अगर (cfa->base == CFI_UNDEFINED) अणु
		अगर (insn->func) अणु
			WARN_FUNC("undefined stack state", insn->sec, insn->offset);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (cfi->type == UNWIND_HINT_TYPE_REGS ||
	    cfi->type == UNWIND_HINT_TYPE_REGS_PARTIAL)
		वापस update_cfi_state_regs(insn, cfi, op);

	चयन (op->dest.type) अणु

	हाल OP_DEST_REG:
		चयन (op->src.type) अणु

		हाल OP_SRC_REG:
			अगर (op->src.reg == CFI_SP && op->dest.reg == CFI_BP &&
			    cfa->base == CFI_SP &&
			    check_reg_frame_pos(&regs[CFI_BP], -cfa->offset)) अणु

				/* mov %rsp, %rbp */
				cfa->base = op->dest.reg;
				cfi->bp_scratch = false;
			पूर्ण

			अन्यथा अगर (op->src.reg == CFI_SP &&
				 op->dest.reg == CFI_BP && cfi->drap) अणु

				/* drap: mov %rsp, %rbp */
				regs[CFI_BP].base = CFI_BP;
				regs[CFI_BP].offset = -cfi->stack_size;
				cfi->bp_scratch = false;
			पूर्ण

			अन्यथा अगर (op->src.reg == CFI_SP && cfa->base == CFI_SP) अणु

				/*
				 * mov %rsp, %reg
				 *
				 * This is needed क्रम the rare हाल where GCC
				 * करोes:
				 *
				 *   mov    %rsp, %rax
				 *   ...
				 *   mov    %rax, %rsp
				 */
				cfi->vals[op->dest.reg].base = CFI_CFA;
				cfi->vals[op->dest.reg].offset = -cfi->stack_size;
			पूर्ण

			अन्यथा अगर (op->src.reg == CFI_BP && op->dest.reg == CFI_SP &&
				 (cfa->base == CFI_BP || cfa->base == cfi->drap_reg)) अणु

				/*
				 * mov %rbp, %rsp
				 *
				 * Restore the original stack poपूर्णांकer (Clang).
				 */
				cfi->stack_size = -cfi->regs[CFI_BP].offset;
			पूर्ण

			अन्यथा अगर (op->dest.reg == cfa->base) अणु

				/* mov %reg, %rsp */
				अगर (cfa->base == CFI_SP &&
				    cfi->vals[op->src.reg].base == CFI_CFA) अणु

					/*
					 * This is needed क्रम the rare हाल
					 * where GCC करोes something dumb like:
					 *
					 *   lea    0x8(%rsp), %rcx
					 *   ...
					 *   mov    %rcx, %rsp
					 */
					cfa->offset = -cfi->vals[op->src.reg].offset;
					cfi->stack_size = cfa->offset;

				पूर्ण अन्यथा अगर (cfa->base == CFI_SP &&
					   cfi->vals[op->src.reg].base == CFI_SP_INसूचीECT &&
					   cfi->vals[op->src.reg].offset == cfa->offset) अणु

					/*
					 * Stack swizzle:
					 *
					 * 1: mov %rsp, (%[tos])
					 * 2: mov %[tos], %rsp
					 *    ...
					 * 3: pop %rsp
					 *
					 * Where:
					 *
					 * 1 - places a poपूर्णांकer to the previous
					 *     stack at the Top-of-Stack of the
					 *     new stack.
					 *
					 * 2 - चयनes to the new stack.
					 *
					 * 3 - pops the Top-of-Stack to restore
					 *     the original stack.
					 *
					 * Note: we set base to SP_INसूचीECT
					 * here and preserve offset. Thereक्रमe
					 * when the unwinder reaches ToS it
					 * will dereference SP and then add the
					 * offset to find the next frame, IOW:
					 * (%rsp) + offset.
					 */
					cfa->base = CFI_SP_INसूचीECT;

				पूर्ण अन्यथा अणु
					cfa->base = CFI_UNDEFINED;
					cfa->offset = 0;
				पूर्ण
			पूर्ण

			अन्यथा अगर (op->dest.reg == CFI_SP &&
				 cfi->vals[op->src.reg].base == CFI_SP_INसूचीECT &&
				 cfi->vals[op->src.reg].offset == cfa->offset) अणु

				/*
				 * The same stack swizzle हाल 2) as above. But
				 * because we can't change cfa->base, हाल 3)
				 * will become a regular POP. Pretend we're a
				 * PUSH so things करोn't go unbalanced.
				 */
				cfi->stack_size += 8;
			पूर्ण


			अवरोध;

		हाल OP_SRC_ADD:
			अगर (op->dest.reg == CFI_SP && op->src.reg == CFI_SP) अणु

				/* add imm, %rsp */
				cfi->stack_size -= op->src.offset;
				अगर (cfa->base == CFI_SP)
					cfa->offset -= op->src.offset;
				अवरोध;
			पूर्ण

			अगर (op->dest.reg == CFI_SP && op->src.reg == CFI_BP) अणु

				/* lea disp(%rbp), %rsp */
				cfi->stack_size = -(op->src.offset + regs[CFI_BP].offset);
				अवरोध;
			पूर्ण

			अगर (!cfi->drap && op->src.reg == CFI_SP &&
			    op->dest.reg == CFI_BP && cfa->base == CFI_SP &&
			    check_reg_frame_pos(&regs[CFI_BP], -cfa->offset + op->src.offset)) अणु

				/* lea disp(%rsp), %rbp */
				cfa->base = CFI_BP;
				cfa->offset -= op->src.offset;
				cfi->bp_scratch = false;
				अवरोध;
			पूर्ण

			अगर (op->src.reg == CFI_SP && cfa->base == CFI_SP) अणु

				/* drap: lea disp(%rsp), %drap */
				cfi->drap_reg = op->dest.reg;

				/*
				 * lea disp(%rsp), %reg
				 *
				 * This is needed क्रम the rare हाल where GCC
				 * करोes something dumb like:
				 *
				 *   lea    0x8(%rsp), %rcx
				 *   ...
				 *   mov    %rcx, %rsp
				 */
				cfi->vals[op->dest.reg].base = CFI_CFA;
				cfi->vals[op->dest.reg].offset = \
					-cfi->stack_size + op->src.offset;

				अवरोध;
			पूर्ण

			अगर (cfi->drap && op->dest.reg == CFI_SP &&
			    op->src.reg == cfi->drap_reg) अणु

				 /* drap: lea disp(%drap), %rsp */
				cfa->base = CFI_SP;
				cfa->offset = cfi->stack_size = -op->src.offset;
				cfi->drap_reg = CFI_UNDEFINED;
				cfi->drap = false;
				अवरोध;
			पूर्ण

			अगर (op->dest.reg == cfi->cfa.base && !(next_insn && next_insn->hपूर्णांक)) अणु
				WARN_FUNC("unsupported stack register modification",
					  insn->sec, insn->offset);
				वापस -1;
			पूर्ण

			अवरोध;

		हाल OP_SRC_AND:
			अगर (op->dest.reg != CFI_SP ||
			    (cfi->drap_reg != CFI_UNDEFINED && cfa->base != CFI_SP) ||
			    (cfi->drap_reg == CFI_UNDEFINED && cfa->base != CFI_BP)) अणु
				WARN_FUNC("unsupported stack pointer realignment",
					  insn->sec, insn->offset);
				वापस -1;
			पूर्ण

			अगर (cfi->drap_reg != CFI_UNDEFINED) अणु
				/* drap: and imm, %rsp */
				cfa->base = cfi->drap_reg;
				cfa->offset = cfi->stack_size = 0;
				cfi->drap = true;
			पूर्ण

			/*
			 * Older versions of GCC (4.8ish) realign the stack
			 * without DRAP, with a frame poपूर्णांकer.
			 */

			अवरोध;

		हाल OP_SRC_POP:
		हाल OP_SRC_POPF:
			अगर (op->dest.reg == CFI_SP && cfa->base == CFI_SP_INसूचीECT) अणु

				/* pop %rsp; # restore from a stack swizzle */
				cfa->base = CFI_SP;
				अवरोध;
			पूर्ण

			अगर (!cfi->drap && op->dest.reg == cfa->base) अणु

				/* pop %rbp */
				cfa->base = CFI_SP;
			पूर्ण

			अगर (cfi->drap && cfa->base == CFI_BP_INसूचीECT &&
			    op->dest.reg == cfi->drap_reg &&
			    cfi->drap_offset == -cfi->stack_size) अणु

				/* drap: pop %drap */
				cfa->base = cfi->drap_reg;
				cfa->offset = 0;
				cfi->drap_offset = -1;

			पूर्ण अन्यथा अगर (cfi->stack_size == -regs[op->dest.reg].offset) अणु

				/* pop %reg */
				restore_reg(cfi, op->dest.reg);
			पूर्ण

			cfi->stack_size -= 8;
			अगर (cfa->base == CFI_SP)
				cfa->offset -= 8;

			अवरोध;

		हाल OP_SRC_REG_INसूचीECT:
			अगर (!cfi->drap && op->dest.reg == cfa->base &&
			    op->dest.reg == CFI_BP) अणु

				/* mov disp(%rsp), %rbp */
				cfa->base = CFI_SP;
				cfa->offset = cfi->stack_size;
			पूर्ण

			अगर (cfi->drap && op->src.reg == CFI_BP &&
			    op->src.offset == cfi->drap_offset) अणु

				/* drap: mov disp(%rbp), %drap */
				cfa->base = cfi->drap_reg;
				cfa->offset = 0;
				cfi->drap_offset = -1;
			पूर्ण

			अगर (cfi->drap && op->src.reg == CFI_BP &&
			    op->src.offset == regs[op->dest.reg].offset) अणु

				/* drap: mov disp(%rbp), %reg */
				restore_reg(cfi, op->dest.reg);

			पूर्ण अन्यथा अगर (op->src.reg == cfa->base &&
			    op->src.offset == regs[op->dest.reg].offset + cfa->offset) अणु

				/* mov disp(%rbp), %reg */
				/* mov disp(%rsp), %reg */
				restore_reg(cfi, op->dest.reg);

			पूर्ण अन्यथा अगर (op->src.reg == CFI_SP &&
				   op->src.offset == regs[op->dest.reg].offset + cfi->stack_size) अणु

				/* mov disp(%rsp), %reg */
				restore_reg(cfi, op->dest.reg);
			पूर्ण

			अवरोध;

		शेष:
			WARN_FUNC("unknown stack-related instruction",
				  insn->sec, insn->offset);
			वापस -1;
		पूर्ण

		अवरोध;

	हाल OP_DEST_PUSH:
	हाल OP_DEST_PUSHF:
		cfi->stack_size += 8;
		अगर (cfa->base == CFI_SP)
			cfa->offset += 8;

		अगर (op->src.type != OP_SRC_REG)
			अवरोध;

		अगर (cfi->drap) अणु
			अगर (op->src.reg == cfa->base && op->src.reg == cfi->drap_reg) अणु

				/* drap: push %drap */
				cfa->base = CFI_BP_INसूचीECT;
				cfa->offset = -cfi->stack_size;

				/* save drap so we know when to restore it */
				cfi->drap_offset = -cfi->stack_size;

			पूर्ण अन्यथा अगर (op->src.reg == CFI_BP && cfa->base == cfi->drap_reg) अणु

				/* drap: push %rbp */
				cfi->stack_size = 0;

			पूर्ण अन्यथा अणु

				/* drap: push %reg */
				save_reg(cfi, op->src.reg, CFI_BP, -cfi->stack_size);
			पूर्ण

		पूर्ण अन्यथा अणु

			/* push %reg */
			save_reg(cfi, op->src.reg, CFI_CFA, -cfi->stack_size);
		पूर्ण

		/* detect when यंत्र code uses rbp as a scratch रेजिस्टर */
		अगर (!no_fp && insn->func && op->src.reg == CFI_BP &&
		    cfa->base != CFI_BP)
			cfi->bp_scratch = true;
		अवरोध;

	हाल OP_DEST_REG_INसूचीECT:

		अगर (cfi->drap) अणु
			अगर (op->src.reg == cfa->base && op->src.reg == cfi->drap_reg) अणु

				/* drap: mov %drap, disp(%rbp) */
				cfa->base = CFI_BP_INसूचीECT;
				cfa->offset = op->dest.offset;

				/* save drap offset so we know when to restore it */
				cfi->drap_offset = op->dest.offset;
			पूर्ण अन्यथा अणु

				/* drap: mov reg, disp(%rbp) */
				save_reg(cfi, op->src.reg, CFI_BP, op->dest.offset);
			पूर्ण

		पूर्ण अन्यथा अगर (op->dest.reg == cfa->base) अणु

			/* mov reg, disp(%rbp) */
			/* mov reg, disp(%rsp) */
			save_reg(cfi, op->src.reg, CFI_CFA,
				 op->dest.offset - cfi->cfa.offset);

		पूर्ण अन्यथा अगर (op->dest.reg == CFI_SP) अणु

			/* mov reg, disp(%rsp) */
			save_reg(cfi, op->src.reg, CFI_CFA,
				 op->dest.offset - cfi->stack_size);

		पूर्ण अन्यथा अगर (op->src.reg == CFI_SP && op->dest.offset == 0) अणु

			/* mov %rsp, (%reg); # setup a stack swizzle. */
			cfi->vals[op->dest.reg].base = CFI_SP_INसूचीECT;
			cfi->vals[op->dest.reg].offset = cfa->offset;
		पूर्ण

		अवरोध;

	हाल OP_DEST_MEM:
		अगर (op->src.type != OP_SRC_POP && op->src.type != OP_SRC_POPF) अणु
			WARN_FUNC("unknown stack-related memory operation",
				  insn->sec, insn->offset);
			वापस -1;
		पूर्ण

		/* pop mem */
		cfi->stack_size -= 8;
		अगर (cfa->base == CFI_SP)
			cfa->offset -= 8;

		अवरोध;

	शेष:
		WARN_FUNC("unknown stack-related instruction",
			  insn->sec, insn->offset);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The stack layouts of alternatives inकाष्ठाions can someबार भागerge when
 * they have stack modअगरications.  That's fine as दीर्घ as the potential stack
 * layouts करोn't conflict at any given potential inकाष्ठाion boundary.
 *
 * Flatten the CFIs of the dअगरferent alternative code streams (both original
 * and replacement) पूर्णांकo a single shared CFI array which can be used to detect
 * conflicts and nicely feed a linear array of ORC entries to the unwinder.
 */
अटल पूर्णांक propagate_alt_cfi(काष्ठा objtool_file *file, काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा cfi_state **alt_cfi;
	पूर्णांक group_off;

	अगर (!insn->alt_group)
		वापस 0;

	alt_cfi = insn->alt_group->cfi;
	group_off = insn->offset - insn->alt_group->first_insn->offset;

	अगर (!alt_cfi[group_off]) अणु
		alt_cfi[group_off] = &insn->cfi;
	पूर्ण अन्यथा अणु
		अगर (स_भेद(alt_cfi[group_off], &insn->cfi, माप(काष्ठा cfi_state))) अणु
			WARN_FUNC("stack layout conflict in alternatives",
				  insn->sec, insn->offset);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक handle_insn_ops(काष्ठा inकाष्ठाion *insn,
			   काष्ठा inकाष्ठाion *next_insn,
			   काष्ठा insn_state *state)
अणु
	काष्ठा stack_op *op;

	list_क्रम_each_entry(op, &insn->stack_ops, list) अणु

		अगर (update_cfi_state(insn, next_insn, &state->cfi, op))
			वापस 1;

		अगर (!insn->alt_group)
			जारी;

		अगर (op->dest.type == OP_DEST_PUSHF) अणु
			अगर (!state->uaccess_stack) अणु
				state->uaccess_stack = 1;
			पूर्ण अन्यथा अगर (state->uaccess_stack >> 31) अणु
				WARN_FUNC("PUSHF stack exhausted",
					  insn->sec, insn->offset);
				वापस 1;
			पूर्ण
			state->uaccess_stack <<= 1;
			state->uaccess_stack  |= state->uaccess;
		पूर्ण

		अगर (op->src.type == OP_SRC_POPF) अणु
			अगर (state->uaccess_stack) अणु
				state->uaccess = state->uaccess_stack & 1;
				state->uaccess_stack >>= 1;
				अगर (state->uaccess_stack == 1)
					state->uaccess_stack = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool insn_cfi_match(काष्ठा inकाष्ठाion *insn, काष्ठा cfi_state *cfi2)
अणु
	काष्ठा cfi_state *cfi1 = &insn->cfi;
	पूर्णांक i;

	अगर (स_भेद(&cfi1->cfa, &cfi2->cfa, माप(cfi1->cfa))) अणु

		WARN_FUNC("stack state mismatch: cfa1=%d%+d cfa2=%d%+d",
			  insn->sec, insn->offset,
			  cfi1->cfa.base, cfi1->cfa.offset,
			  cfi2->cfa.base, cfi2->cfa.offset);

	पूर्ण अन्यथा अगर (स_भेद(&cfi1->regs, &cfi2->regs, माप(cfi1->regs))) अणु
		क्रम (i = 0; i < CFI_NUM_REGS; i++) अणु
			अगर (!स_भेद(&cfi1->regs[i], &cfi2->regs[i],
				    माप(काष्ठा cfi_reg)))
				जारी;

			WARN_FUNC("stack state mismatch: reg1[%d]=%d%+d reg2[%d]=%d%+d",
				  insn->sec, insn->offset,
				  i, cfi1->regs[i].base, cfi1->regs[i].offset,
				  i, cfi2->regs[i].base, cfi2->regs[i].offset);
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अगर (cfi1->type != cfi2->type) अणु

		WARN_FUNC("stack state mismatch: type1=%d type2=%d",
			  insn->sec, insn->offset, cfi1->type, cfi2->type);

	पूर्ण अन्यथा अगर (cfi1->drap != cfi2->drap ||
		   (cfi1->drap && cfi1->drap_reg != cfi2->drap_reg) ||
		   (cfi1->drap && cfi1->drap_offset != cfi2->drap_offset)) अणु

		WARN_FUNC("stack state mismatch: drap1=%d(%d,%d) drap2=%d(%d,%d)",
			  insn->sec, insn->offset,
			  cfi1->drap, cfi1->drap_reg, cfi1->drap_offset,
			  cfi2->drap, cfi2->drap_reg, cfi2->drap_offset);

	पूर्ण अन्यथा
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool func_uaccess_safe(काष्ठा symbol *func)
अणु
	अगर (func)
		वापस func->uaccess_safe;

	वापस false;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *call_dest_name(काष्ठा inकाष्ठाion *insn)
अणु
	अगर (insn->call_dest)
		वापस insn->call_dest->name;

	वापस "{dynamic}";
पूर्ण

अटल अंतरभूत bool noinstr_call_dest(काष्ठा symbol *func)
अणु
	/*
	 * We can't deal with indirect function calls at present;
	 * assume they're instrumented.
	 */
	अगर (!func)
		वापस false;

	/*
	 * If the symbol is from a noinstr section; we good.
	 */
	अगर (func->sec->noinstr)
		वापस true;

	/*
	 * The __ubsan_handle_*() calls are like WARN(), they only happen when
	 * something 'BAD' happened. At the risk of taking the machine करोwn,
	 * let them proceed to get the message out.
	 */
	अगर (!म_भेदन(func->name, "__ubsan_handle_", 15))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक validate_call(काष्ठा inकाष्ठाion *insn, काष्ठा insn_state *state)
अणु
	अगर (state->noinstr && state->instr <= 0 &&
	    !noinstr_call_dest(insn->call_dest)) अणु
		WARN_FUNC("call to %s() leaves .noinstr.text section",
				insn->sec, insn->offset, call_dest_name(insn));
		वापस 1;
	पूर्ण

	अगर (state->uaccess && !func_uaccess_safe(insn->call_dest)) अणु
		WARN_FUNC("call to %s() with UACCESS enabled",
				insn->sec, insn->offset, call_dest_name(insn));
		वापस 1;
	पूर्ण

	अगर (state->df) अणु
		WARN_FUNC("call to %s() with DF set",
				insn->sec, insn->offset, call_dest_name(insn));
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक validate_sibling_call(काष्ठा inकाष्ठाion *insn, काष्ठा insn_state *state)
अणु
	अगर (has_modअगरied_stack_frame(insn, state)) अणु
		WARN_FUNC("sibling call from callable instruction with modified stack frame",
				insn->sec, insn->offset);
		वापस 1;
	पूर्ण

	वापस validate_call(insn, state);
पूर्ण

अटल पूर्णांक validate_वापस(काष्ठा symbol *func, काष्ठा inकाष्ठाion *insn, काष्ठा insn_state *state)
अणु
	अगर (state->noinstr && state->instr > 0) अणु
		WARN_FUNC("return with instrumentation enabled",
			  insn->sec, insn->offset);
		वापस 1;
	पूर्ण

	अगर (state->uaccess && !func_uaccess_safe(func)) अणु
		WARN_FUNC("return with UACCESS enabled",
			  insn->sec, insn->offset);
		वापस 1;
	पूर्ण

	अगर (!state->uaccess && func_uaccess_safe(func)) अणु
		WARN_FUNC("return with UACCESS disabled from a UACCESS-safe function",
			  insn->sec, insn->offset);
		वापस 1;
	पूर्ण

	अगर (state->df) अणु
		WARN_FUNC("return with DF set",
			  insn->sec, insn->offset);
		वापस 1;
	पूर्ण

	अगर (func && has_modअगरied_stack_frame(insn, state)) अणु
		WARN_FUNC("return with modified stack frame",
			  insn->sec, insn->offset);
		वापस 1;
	पूर्ण

	अगर (state->cfi.bp_scratch) अणु
		WARN_FUNC("BP used as a scratch register",
			  insn->sec, insn->offset);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा inकाष्ठाion *next_insn_to_validate(काष्ठा objtool_file *file,
						 काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा alt_group *alt_group = insn->alt_group;

	/*
	 * Simulate the fact that alternatives are patched in-place.  When the
	 * end of a replacement alt_group is reached, redirect objtool flow to
	 * the end of the original alt_group.
	 */
	अगर (alt_group && insn == alt_group->last_insn && alt_group->orig_group)
		वापस next_insn_same_sec(file, alt_group->orig_group->last_insn);

	वापस next_insn_same_sec(file, insn);
पूर्ण

/*
 * Follow the branch starting at the given inकाष्ठाion, and recursively follow
 * any other branches (jumps).  Meanजबतक, track the frame poपूर्णांकer state at
 * each inकाष्ठाion and validate all the rules described in
 * tools/objtool/Documentation/stack-validation.txt.
 */
अटल पूर्णांक validate_branch(काष्ठा objtool_file *file, काष्ठा symbol *func,
			   काष्ठा inकाष्ठाion *insn, काष्ठा insn_state state)
अणु
	काष्ठा alternative *alt;
	काष्ठा inकाष्ठाion *next_insn;
	काष्ठा section *sec;
	u8 visited;
	पूर्णांक ret;

	sec = insn->sec;

	जबतक (1) अणु
		next_insn = next_insn_to_validate(file, insn);

		अगर (file->c_file && func && insn->func && func != insn->func->pfunc) अणु
			WARN("%s() falls through to next function %s()",
			     func->name, insn->func->name);
			वापस 1;
		पूर्ण

		अगर (func && insn->ignore) अणु
			WARN_FUNC("BUG: why am I validating an ignored function?",
				  sec, insn->offset);
			वापस 1;
		पूर्ण

		visited = 1 << state.uaccess;
		अगर (insn->visited) अणु
			अगर (!insn->hपूर्णांक && !insn_cfi_match(insn, &state.cfi))
				वापस 1;

			अगर (insn->visited & visited)
				वापस 0;
		पूर्ण

		अगर (state.noinstr)
			state.instr += insn->instr;

		अगर (insn->hपूर्णांक)
			state.cfi = insn->cfi;
		अन्यथा
			insn->cfi = state.cfi;

		insn->visited |= visited;

		अगर (propagate_alt_cfi(file, insn))
			वापस 1;

		अगर (!insn->ignore_alts && !list_empty(&insn->alts)) अणु
			bool skip_orig = false;

			list_क्रम_each_entry(alt, &insn->alts, list) अणु
				अगर (alt->skip_orig)
					skip_orig = true;

				ret = validate_branch(file, func, alt->insn, state);
				अगर (ret) अणु
					अगर (backtrace)
						BT_FUNC("(alt)", insn);
					वापस ret;
				पूर्ण
			पूर्ण

			अगर (skip_orig)
				वापस 0;
		पूर्ण

		अगर (handle_insn_ops(insn, next_insn, &state))
			वापस 1;

		चयन (insn->type) अणु

		हाल INSN_RETURN:
			वापस validate_वापस(func, insn, &state);

		हाल INSN_CALL:
		हाल INSN_CALL_DYNAMIC:
			ret = validate_call(insn, &state);
			अगर (ret)
				वापस ret;

			अगर (!no_fp && func && !is_fentry_call(insn) &&
			    !has_valid_stack_frame(&state)) अणु
				WARN_FUNC("call without frame pointer save/setup",
					  sec, insn->offset);
				वापस 1;
			पूर्ण

			अगर (dead_end_function(file, insn->call_dest))
				वापस 0;

			अवरोध;

		हाल INSN_JUMP_CONDITIONAL:
		हाल INSN_JUMP_UNCONDITIONAL:
			अगर (is_sibling_call(insn)) अणु
				ret = validate_sibling_call(insn, &state);
				अगर (ret)
					वापस ret;

			पूर्ण अन्यथा अगर (insn->jump_dest) अणु
				ret = validate_branch(file, func,
						      insn->jump_dest, state);
				अगर (ret) अणु
					अगर (backtrace)
						BT_FUNC("(branch)", insn);
					वापस ret;
				पूर्ण
			पूर्ण

			अगर (insn->type == INSN_JUMP_UNCONDITIONAL)
				वापस 0;

			अवरोध;

		हाल INSN_JUMP_DYNAMIC:
		हाल INSN_JUMP_DYNAMIC_CONDITIONAL:
			अगर (is_sibling_call(insn)) अणु
				ret = validate_sibling_call(insn, &state);
				अगर (ret)
					वापस ret;
			पूर्ण

			अगर (insn->type == INSN_JUMP_DYNAMIC)
				वापस 0;

			अवरोध;

		हाल INSN_CONTEXT_SWITCH:
			अगर (func && (!next_insn || !next_insn->hपूर्णांक)) अणु
				WARN_FUNC("unsupported instruction in callable function",
					  sec, insn->offset);
				वापस 1;
			पूर्ण
			वापस 0;

		हाल INSN_STAC:
			अगर (state.uaccess) अणु
				WARN_FUNC("recursive UACCESS enable", sec, insn->offset);
				वापस 1;
			पूर्ण

			state.uaccess = true;
			अवरोध;

		हाल INSN_CLAC:
			अगर (!state.uaccess && func) अणु
				WARN_FUNC("redundant UACCESS disable", sec, insn->offset);
				वापस 1;
			पूर्ण

			अगर (func_uaccess_safe(func) && !state.uaccess_stack) अणु
				WARN_FUNC("UACCESS-safe disables UACCESS", sec, insn->offset);
				वापस 1;
			पूर्ण

			state.uaccess = false;
			अवरोध;

		हाल INSN_STD:
			अगर (state.df) अणु
				WARN_FUNC("recursive STD", sec, insn->offset);
				वापस 1;
			पूर्ण

			state.df = true;
			अवरोध;

		हाल INSN_CLD:
			अगर (!state.df && func) अणु
				WARN_FUNC("redundant CLD", sec, insn->offset);
				वापस 1;
			पूर्ण

			state.df = false;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (insn->dead_end)
			वापस 0;

		अगर (!next_insn) अणु
			अगर (state.cfi.cfa.base == CFI_UNDEFINED)
				वापस 0;
			WARN("%s: unexpected end of section", sec->name);
			वापस 1;
		पूर्ण

		insn = next_insn;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक validate_unwind_hपूर्णांकs(काष्ठा objtool_file *file, काष्ठा section *sec)
अणु
	काष्ठा inकाष्ठाion *insn;
	काष्ठा insn_state state;
	पूर्णांक ret, warnings = 0;

	अगर (!file->hपूर्णांकs)
		वापस 0;

	init_insn_state(&state, sec);

	अगर (sec) अणु
		insn = find_insn(file, sec, 0);
		अगर (!insn)
			वापस 0;
	पूर्ण अन्यथा अणु
		insn = list_first_entry(&file->insn_list, typeof(*insn), list);
	पूर्ण

	जबतक (&insn->list != &file->insn_list && (!sec || insn->sec == sec)) अणु
		अगर (insn->hपूर्णांक && !insn->visited) अणु
			ret = validate_branch(file, insn->func, insn, state);
			अगर (ret && backtrace)
				BT_FUNC("<=== (hint)", insn);
			warnings += ret;
		पूर्ण

		insn = list_next_entry(insn, list);
	पूर्ण

	वापस warnings;
पूर्ण

अटल पूर्णांक validate_retpoline(काष्ठा objtool_file *file)
अणु
	काष्ठा inकाष्ठाion *insn;
	पूर्णांक warnings = 0;

	क्रम_each_insn(file, insn) अणु
		अगर (insn->type != INSN_JUMP_DYNAMIC &&
		    insn->type != INSN_CALL_DYNAMIC)
			जारी;

		अगर (insn->retpoline_safe)
			जारी;

		/*
		 * .init.text code is ran beक्रमe userspace and thus करोesn't
		 * strictly need retpolines, except क्रम modules which are
		 * loaded late, they very much करो need retpoline in their
		 * .init.text
		 */
		अगर (!म_भेद(insn->sec->name, ".init.text") && !module)
			जारी;

		WARN_FUNC("indirect %s found in RETPOLINE build",
			  insn->sec, insn->offset,
			  insn->type == INSN_JUMP_DYNAMIC ? "jump" : "call");

		warnings++;
	पूर्ण

	वापस warnings;
पूर्ण

अटल bool is_kasan_insn(काष्ठा inकाष्ठाion *insn)
अणु
	वापस (insn->type == INSN_CALL &&
		!म_भेद(insn->call_dest->name, "__asan_handle_no_return"));
पूर्ण

अटल bool is_ubsan_insn(काष्ठा inकाष्ठाion *insn)
अणु
	वापस (insn->type == INSN_CALL &&
		!म_भेद(insn->call_dest->name,
			"__ubsan_handle_builtin_unreachable"));
पूर्ण

अटल bool ignore_unreachable_insn(काष्ठा objtool_file *file, काष्ठा inकाष्ठाion *insn)
अणु
	पूर्णांक i;
	काष्ठा inकाष्ठाion *prev_insn;

	अगर (insn->ignore || insn->type == INSN_NOP)
		वापस true;

	/*
	 * Ignore any unused exceptions.  This can happen when a whitelisted
	 * function has an exception table entry.
	 *
	 * Also ignore alternative replacement inकाष्ठाions.  This can happen
	 * when a whitelisted function uses one of the ALTERNATIVE macros.
	 */
	अगर (!म_भेद(insn->sec->name, ".fixup") ||
	    !म_भेद(insn->sec->name, ".altinstr_replacement") ||
	    !म_भेद(insn->sec->name, ".altinstr_aux"))
		वापस true;

	अगर (!insn->func)
		वापस false;

	/*
	 * CONFIG_UBSAN_TRAP inserts a UD2 when it sees
	 * __builtin_unreachable().  The BUG() macro has an unreachable() after
	 * the UD2, which causes GCC's undefined trap logic to emit another UD2
	 * (or occasionally a JMP to UD2).
	 *
	 * It may also insert a UD2 after calling a __noवापस function.
	 */
	prev_insn = list_prev_entry(insn, list);
	अगर ((prev_insn->dead_end || dead_end_function(file, prev_insn->call_dest)) &&
	    (insn->type == INSN_BUG ||
	     (insn->type == INSN_JUMP_UNCONDITIONAL &&
	      insn->jump_dest && insn->jump_dest->type == INSN_BUG)))
		वापस true;

	/*
	 * Check अगर this (or a subsequent) inकाष्ठाion is related to
	 * CONFIG_UBSAN or CONFIG_KASAN.
	 *
	 * End the search at 5 inकाष्ठाions to aव्योम going पूर्णांकo the weeds.
	 */
	क्रम (i = 0; i < 5; i++) अणु

		अगर (is_kasan_insn(insn) || is_ubsan_insn(insn))
			वापस true;

		अगर (insn->type == INSN_JUMP_UNCONDITIONAL) अणु
			अगर (insn->jump_dest &&
			    insn->jump_dest->func == insn->func) अणु
				insn = insn->jump_dest;
				जारी;
			पूर्ण

			अवरोध;
		पूर्ण

		अगर (insn->offset + insn->len >= insn->func->offset + insn->func->len)
			अवरोध;

		insn = list_next_entry(insn, list);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक validate_symbol(काष्ठा objtool_file *file, काष्ठा section *sec,
			   काष्ठा symbol *sym, काष्ठा insn_state *state)
अणु
	काष्ठा inकाष्ठाion *insn;
	पूर्णांक ret;

	अगर (!sym->len) अणु
		WARN("%s() is missing an ELF size annotation", sym->name);
		वापस 1;
	पूर्ण

	अगर (sym->pfunc != sym || sym->alias != sym)
		वापस 0;

	insn = find_insn(file, sec, sym->offset);
	अगर (!insn || insn->ignore || insn->visited)
		वापस 0;

	state->uaccess = sym->uaccess_safe;

	ret = validate_branch(file, insn->func, insn, *state);
	अगर (ret && backtrace)
		BT_FUNC("<=== (sym)", insn);
	वापस ret;
पूर्ण

अटल पूर्णांक validate_section(काष्ठा objtool_file *file, काष्ठा section *sec)
अणु
	काष्ठा insn_state state;
	काष्ठा symbol *func;
	पूर्णांक warnings = 0;

	list_क्रम_each_entry(func, &sec->symbol_list, list) अणु
		अगर (func->type != STT_FUNC)
			जारी;

		init_insn_state(&state, sec);
		set_func_state(&state.cfi);

		warnings += validate_symbol(file, sec, func, &state);
	पूर्ण

	वापस warnings;
पूर्ण

अटल पूर्णांक validate_vmlinux_functions(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	पूर्णांक warnings = 0;

	sec = find_section_by_name(file->elf, ".noinstr.text");
	अगर (sec) अणु
		warnings += validate_section(file, sec);
		warnings += validate_unwind_hपूर्णांकs(file, sec);
	पूर्ण

	sec = find_section_by_name(file->elf, ".entry.text");
	अगर (sec) अणु
		warnings += validate_section(file, sec);
		warnings += validate_unwind_hपूर्णांकs(file, sec);
	पूर्ण

	वापस warnings;
पूर्ण

अटल पूर्णांक validate_functions(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec;
	पूर्णांक warnings = 0;

	क्रम_each_sec(file, sec) अणु
		अगर (!(sec->sh.sh_flags & SHF_EXECINSTR))
			जारी;

		warnings += validate_section(file, sec);
	पूर्ण

	वापस warnings;
पूर्ण

अटल पूर्णांक validate_reachable_inकाष्ठाions(काष्ठा objtool_file *file)
अणु
	काष्ठा inकाष्ठाion *insn;

	अगर (file->ignore_unreachables)
		वापस 0;

	क्रम_each_insn(file, insn) अणु
		अगर (insn->visited || ignore_unreachable_insn(file, insn))
			जारी;

		WARN_FUNC("unreachable instruction", insn->sec, insn->offset);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक check(काष्ठा objtool_file *file)
अणु
	पूर्णांक ret, warnings = 0;

	arch_initial_func_cfi_state(&initial_func_cfi);

	ret = decode_sections(file);
	अगर (ret < 0)
		जाओ out;
	warnings += ret;

	अगर (list_empty(&file->insn_list))
		जाओ out;

	अगर (vmlinux && !validate_dup) अणु
		ret = validate_vmlinux_functions(file);
		अगर (ret < 0)
			जाओ out;

		warnings += ret;
		जाओ out;
	पूर्ण

	अगर (retpoline) अणु
		ret = validate_retpoline(file);
		अगर (ret < 0)
			वापस ret;
		warnings += ret;
	पूर्ण

	ret = validate_functions(file);
	अगर (ret < 0)
		जाओ out;
	warnings += ret;

	ret = validate_unwind_hपूर्णांकs(file, शून्य);
	अगर (ret < 0)
		जाओ out;
	warnings += ret;

	अगर (!warnings) अणु
		ret = validate_reachable_inकाष्ठाions(file);
		अगर (ret < 0)
			जाओ out;
		warnings += ret;
	पूर्ण

	ret = create_अटल_call_sections(file);
	अगर (ret < 0)
		जाओ out;
	warnings += ret;

	अगर (mcount) अणु
		ret = create_mcount_loc_sections(file);
		अगर (ret < 0)
			जाओ out;
		warnings += ret;
	पूर्ण

out:
	/*
	 *  For now, करोn't fail the kernel build on fatal warnings.  These
	 *  errors are still fairly common due to the growing matrix of
	 *  supported toolchains and their recent pace of change.
	 */
	वापस 0;
पूर्ण
