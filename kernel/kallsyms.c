<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kallsyms.c: in-kernel prपूर्णांकing of symbolic oopses and stack traces.
 *
 * Rewritten and vastly simplअगरied by Rusty Russell क्रम in-kernel
 * module loader:
 *   Copyright 2002 Rusty Russell <rusty@rustcorp.com.au> IBM Corporation
 *
 * ChangeLog:
 *
 * (25/Aug/2004) Paulo Marques <pmarques@grupopie.com>
 *      Changed the compression method from stem compression to "table lookup"
 *      compression (see scripts/kallsyms.c क्रम a more complete description)
 */
#समावेश <linux/kallsyms.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/kdb.h>
#समावेश <linux/err.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sched.h>	/* क्रम cond_resched */
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/filter.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/compiler.h>

/*
 * These will be re-linked against their real values
 * during the second link stage.
 */
बाह्य स्थिर अचिन्हित दीर्घ kallsyms_addresses[] __weak;
बाह्य स्थिर पूर्णांक kallsyms_offsets[] __weak;
बाह्य स्थिर u8 kallsyms_names[] __weak;

/*
 * Tell the compiler that the count isn't in the small data section अगर the arch
 * has one (eg: FRV).
 */
बाह्य स्थिर अचिन्हित पूर्णांक kallsyms_num_syms
__section(".rodata") __attribute__((weak));

बाह्य स्थिर अचिन्हित दीर्घ kallsyms_relative_base
__section(".rodata") __attribute__((weak));

बाह्य स्थिर अक्षर kallsyms_token_table[] __weak;
बाह्य स्थिर u16 kallsyms_token_index[] __weak;

बाह्य स्थिर अचिन्हित पूर्णांक kallsyms_markers[] __weak;

/*
 * Expand a compressed symbol data पूर्णांकo the resulting uncompressed string,
 * अगर uncompressed string is too दीर्घ (>= maxlen), it will be truncated,
 * given the offset to where the symbol is in the compressed stream.
 */
अटल अचिन्हित पूर्णांक kallsyms_expand_symbol(अचिन्हित पूर्णांक off,
					   अक्षर *result, माप_प्रकार maxlen)
अणु
	पूर्णांक len, skipped_first = 0;
	स्थिर अक्षर *tptr;
	स्थिर u8 *data;

	/* Get the compressed symbol length from the first symbol byte. */
	data = &kallsyms_names[off];
	len = *data;
	data++;

	/*
	 * Update the offset to वापस the offset क्रम the next symbol on
	 * the compressed stream.
	 */
	off += len + 1;

	/*
	 * For every byte on the compressed symbol data, copy the table
	 * entry क्रम that byte.
	 */
	जबतक (len) अणु
		tptr = &kallsyms_token_table[kallsyms_token_index[*data]];
		data++;
		len--;

		जबतक (*tptr) अणु
			अगर (skipped_first) अणु
				अगर (maxlen <= 1)
					जाओ tail;
				*result = *tptr;
				result++;
				maxlen--;
			पूर्ण अन्यथा
				skipped_first = 1;
			tptr++;
		पूर्ण
	पूर्ण

tail:
	अगर (maxlen)
		*result = '\0';

	/* Return to offset to the next symbol. */
	वापस off;
पूर्ण

/*
 * Get symbol type inक्रमmation. This is encoded as a single अक्षर at the
 * beginning of the symbol name.
 */
अटल अक्षर kallsyms_get_symbol_type(अचिन्हित पूर्णांक off)
अणु
	/*
	 * Get just the first code, look it up in the token table,
	 * and वापस the first अक्षर from this token.
	 */
	वापस kallsyms_token_table[kallsyms_token_index[kallsyms_names[off + 1]]];
पूर्ण


/*
 * Find the offset on the compressed stream given and index in the
 * kallsyms array.
 */
अटल अचिन्हित पूर्णांक get_symbol_offset(अचिन्हित दीर्घ pos)
अणु
	स्थिर u8 *name;
	पूर्णांक i;

	/*
	 * Use the बंदst marker we have. We have markers every 256 positions,
	 * so that should be बंद enough.
	 */
	name = &kallsyms_names[kallsyms_markers[pos >> 8]];

	/*
	 * Sequentially scan all the symbols up to the poपूर्णांक we're searching
	 * क्रम. Every symbol is stored in a [<len>][<len> bytes of data] क्रमmat,
	 * so we just need to add the len to the current poपूर्णांकer क्रम every
	 * symbol we wish to skip.
	 */
	क्रम (i = 0; i < (pos & 0xFF); i++)
		name = name + (*name) + 1;

	वापस name - kallsyms_names;
पूर्ण

अटल अचिन्हित दीर्घ kallsyms_sym_address(पूर्णांक idx)
अणु
	अगर (!IS_ENABLED(CONFIG_KALLSYMS_BASE_RELATIVE))
		वापस kallsyms_addresses[idx];

	/* values are अचिन्हित offsets अगर --असलolute-percpu is not in effect */
	अगर (!IS_ENABLED(CONFIG_KALLSYMS_ABSOLUTE_PERCPU))
		वापस kallsyms_relative_base + (u32)kallsyms_offsets[idx];

	/* ...otherwise, positive offsets are असलolute values */
	अगर (kallsyms_offsets[idx] >= 0)
		वापस kallsyms_offsets[idx];

	/* ...and negative offsets are relative to kallsyms_relative_base - 1 */
	वापस kallsyms_relative_base - 1 - kallsyms_offsets[idx];
पूर्ण

#अगर defined(CONFIG_CFI_CLANG) && defined(CONFIG_LTO_CLANG_THIN)
/*
 * LLVM appends a hash to अटल function names when ThinLTO and CFI are
 * both enabled, i.e. foo() becomes foo$707af9a22804d33c81801f27dcfe489b.
 * This causes confusion and potentially अवरोधs user space tools, so we
 * strip the suffix from expanded symbol names.
 */
अटल अंतरभूत bool cleanup_symbol_name(अक्षर *s)
अणु
	अक्षर *res;

	res = म_खोजप(s, '$');
	अगर (res)
		*res = '\0';

	वापस res != शून्य;
पूर्ण
#अन्यथा
अटल अंतरभूत bool cleanup_symbol_name(अक्षर *s) अणु वापस false; पूर्ण
#पूर्ण_अगर

/* Lookup the address क्रम this symbol. Returns 0 अगर not found. */
अचिन्हित दीर्घ kallsyms_lookup_name(स्थिर अक्षर *name)
अणु
	अक्षर namebuf[KSYM_NAME_LEN];
	अचिन्हित दीर्घ i;
	अचिन्हित पूर्णांक off;

	क्रम (i = 0, off = 0; i < kallsyms_num_syms; i++) अणु
		off = kallsyms_expand_symbol(off, namebuf, ARRAY_SIZE(namebuf));

		अगर (म_भेद(namebuf, name) == 0)
			वापस kallsyms_sym_address(i);

		अगर (cleanup_symbol_name(namebuf) && म_भेद(namebuf, name) == 0)
			वापस kallsyms_sym_address(i);
	पूर्ण
	वापस module_kallsyms_lookup_name(name);
पूर्ण

#अगर_घोषित CONFIG_LIVEPATCH
/*
 * Iterate over all symbols in vmlinux.  For symbols from modules use
 * module_kallsyms_on_each_symbol instead.
 */
पूर्णांक kallsyms_on_each_symbol(पूर्णांक (*fn)(व्योम *, स्थिर अक्षर *, काष्ठा module *,
				      अचिन्हित दीर्घ),
			    व्योम *data)
अणु
	अक्षर namebuf[KSYM_NAME_LEN];
	अचिन्हित दीर्घ i;
	अचिन्हित पूर्णांक off;
	पूर्णांक ret;

	क्रम (i = 0, off = 0; i < kallsyms_num_syms; i++) अणु
		off = kallsyms_expand_symbol(off, namebuf, ARRAY_SIZE(namebuf));
		ret = fn(data, namebuf, शून्य, kallsyms_sym_address(i));
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_LIVEPATCH */

अटल अचिन्हित दीर्घ get_symbol_pos(अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ *symbolsize,
				    अचिन्हित दीर्घ *offset)
अणु
	अचिन्हित दीर्घ symbol_start = 0, symbol_end = 0;
	अचिन्हित दीर्घ i, low, high, mid;

	/* This kernel should never had been booted. */
	अगर (!IS_ENABLED(CONFIG_KALLSYMS_BASE_RELATIVE))
		BUG_ON(!kallsyms_addresses);
	अन्यथा
		BUG_ON(!kallsyms_offsets);

	/* Do a binary search on the sorted kallsyms_addresses array. */
	low = 0;
	high = kallsyms_num_syms;

	जबतक (high - low > 1) अणु
		mid = low + (high - low) / 2;
		अगर (kallsyms_sym_address(mid) <= addr)
			low = mid;
		अन्यथा
			high = mid;
	पूर्ण

	/*
	 * Search क्रम the first aliased symbol. Aliased
	 * symbols are symbols with the same address.
	 */
	जबतक (low && kallsyms_sym_address(low-1) == kallsyms_sym_address(low))
		--low;

	symbol_start = kallsyms_sym_address(low);

	/* Search क्रम next non-aliased symbol. */
	क्रम (i = low + 1; i < kallsyms_num_syms; i++) अणु
		अगर (kallsyms_sym_address(i) > symbol_start) अणु
			symbol_end = kallsyms_sym_address(i);
			अवरोध;
		पूर्ण
	पूर्ण

	/* If we found no next symbol, we use the end of the section. */
	अगर (!symbol_end) अणु
		अगर (is_kernel_inittext(addr))
			symbol_end = (अचिन्हित दीर्घ)_einittext;
		अन्यथा अगर (IS_ENABLED(CONFIG_KALLSYMS_ALL))
			symbol_end = (अचिन्हित दीर्घ)_end;
		अन्यथा
			symbol_end = (अचिन्हित दीर्घ)_etext;
	पूर्ण

	अगर (symbolsize)
		*symbolsize = symbol_end - symbol_start;
	अगर (offset)
		*offset = addr - symbol_start;

	वापस low;
पूर्ण

/*
 * Lookup an address but करोn't bother to find any names.
 */
पूर्णांक kallsyms_lookup_size_offset(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *symbolsize,
				अचिन्हित दीर्घ *offset)
अणु
	अक्षर namebuf[KSYM_NAME_LEN];

	अगर (is_ksym_addr(addr)) अणु
		get_symbol_pos(addr, symbolsize, offset);
		वापस 1;
	पूर्ण
	वापस !!module_address_lookup(addr, symbolsize, offset, शून्य, namebuf) ||
	       !!__bpf_address_lookup(addr, symbolsize, offset, namebuf);
पूर्ण

/*
 * Lookup an address
 * - modname is set to शून्य अगर it's in the kernel.
 * - We guarantee that the वापसed name is valid until we reschedule even अगर.
 *   It resides in a module.
 * - We also guarantee that modname will be valid until rescheduled.
 */
स्थिर अक्षर *kallsyms_lookup(अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ *symbolsize,
			    अचिन्हित दीर्घ *offset,
			    अक्षर **modname, अक्षर *namebuf)
अणु
	स्थिर अक्षर *ret;

	namebuf[KSYM_NAME_LEN - 1] = 0;
	namebuf[0] = 0;

	अगर (is_ksym_addr(addr)) अणु
		अचिन्हित दीर्घ pos;

		pos = get_symbol_pos(addr, symbolsize, offset);
		/* Grab name */
		kallsyms_expand_symbol(get_symbol_offset(pos),
				       namebuf, KSYM_NAME_LEN);
		अगर (modname)
			*modname = शून्य;

		ret = namebuf;
		जाओ found;
	पूर्ण

	/* See अगर it's in a module or a BPF JITed image. */
	ret = module_address_lookup(addr, symbolsize, offset,
				    modname, namebuf);
	अगर (!ret)
		ret = bpf_address_lookup(addr, symbolsize,
					 offset, modname, namebuf);

	अगर (!ret)
		ret = ftrace_mod_address_lookup(addr, symbolsize,
						offset, modname, namebuf);

found:
	cleanup_symbol_name(namebuf);
	वापस ret;
पूर्ण

पूर्णांक lookup_symbol_name(अचिन्हित दीर्घ addr, अक्षर *symname)
अणु
	पूर्णांक res;

	symname[0] = '\0';
	symname[KSYM_NAME_LEN - 1] = '\0';

	अगर (is_ksym_addr(addr)) अणु
		अचिन्हित दीर्घ pos;

		pos = get_symbol_pos(addr, शून्य, शून्य);
		/* Grab name */
		kallsyms_expand_symbol(get_symbol_offset(pos),
				       symname, KSYM_NAME_LEN);
		जाओ found;
	पूर्ण
	/* See अगर it's in a module. */
	res = lookup_module_symbol_name(addr, symname);
	अगर (res)
		वापस res;

found:
	cleanup_symbol_name(symname);
	वापस 0;
पूर्ण

पूर्णांक lookup_symbol_attrs(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
			अचिन्हित दीर्घ *offset, अक्षर *modname, अक्षर *name)
अणु
	पूर्णांक res;

	name[0] = '\0';
	name[KSYM_NAME_LEN - 1] = '\0';

	अगर (is_ksym_addr(addr)) अणु
		अचिन्हित दीर्घ pos;

		pos = get_symbol_pos(addr, size, offset);
		/* Grab name */
		kallsyms_expand_symbol(get_symbol_offset(pos),
				       name, KSYM_NAME_LEN);
		modname[0] = '\0';
		जाओ found;
	पूर्ण
	/* See अगर it's in a module. */
	res = lookup_module_symbol_attrs(addr, size, offset, modname, name);
	अगर (res)
		वापस res;

found:
	cleanup_symbol_name(name);
	वापस 0;
पूर्ण

/* Look up a kernel symbol and वापस it in a text buffer. */
अटल पूर्णांक __sprपूर्णांक_symbol(अक्षर *buffer, अचिन्हित दीर्घ address,
			   पूर्णांक symbol_offset, पूर्णांक add_offset)
अणु
	अक्षर *modname;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ offset, size;
	पूर्णांक len;

	address += symbol_offset;
	name = kallsyms_lookup(address, &size, &offset, &modname, buffer);
	अगर (!name)
		वापस प्र_लिखो(buffer, "0x%lx", address - symbol_offset);

	अगर (name != buffer)
		म_नकल(buffer, name);
	len = म_माप(buffer);
	offset -= symbol_offset;

	अगर (add_offset)
		len += प्र_लिखो(buffer + len, "+%#lx/%#lx", offset, size);

	अगर (modname)
		len += प्र_लिखो(buffer + len, " [%s]", modname);

	वापस len;
पूर्ण

/**
 * sprपूर्णांक_symbol - Look up a kernel symbol and वापस it in a text buffer
 * @buffer: buffer to be stored
 * @address: address to lookup
 *
 * This function looks up a kernel symbol with @address and stores its name,
 * offset, size and module name to @buffer अगर possible. If no symbol was found,
 * just saves its @address as is.
 *
 * This function वापसs the number of bytes stored in @buffer.
 */
पूर्णांक sprपूर्णांक_symbol(अक्षर *buffer, अचिन्हित दीर्घ address)
अणु
	वापस __sprपूर्णांक_symbol(buffer, address, 0, 1);
पूर्ण
EXPORT_SYMBOL_GPL(sprपूर्णांक_symbol);

/**
 * sprपूर्णांक_symbol_no_offset - Look up a kernel symbol and वापस it in a text buffer
 * @buffer: buffer to be stored
 * @address: address to lookup
 *
 * This function looks up a kernel symbol with @address and stores its name
 * and module name to @buffer अगर possible. If no symbol was found, just saves
 * its @address as is.
 *
 * This function वापसs the number of bytes stored in @buffer.
 */
पूर्णांक sprपूर्णांक_symbol_no_offset(अक्षर *buffer, अचिन्हित दीर्घ address)
अणु
	वापस __sprपूर्णांक_symbol(buffer, address, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sprपूर्णांक_symbol_no_offset);

/**
 * sprपूर्णांक_backtrace - Look up a backtrace symbol and वापस it in a text buffer
 * @buffer: buffer to be stored
 * @address: address to lookup
 *
 * This function is क्रम stack backtrace and करोes the same thing as
 * sprपूर्णांक_symbol() but with modअगरied/decreased @address. If there is a
 * tail-call to the function marked "noreturn", gcc optimized out code after
 * the call so that the stack-saved वापस address could poपूर्णांक outside of the
 * caller. This function ensures that kallsyms will find the original caller
 * by decreasing @address.
 *
 * This function वापसs the number of bytes stored in @buffer.
 */
पूर्णांक sprपूर्णांक_backtrace(अक्षर *buffer, अचिन्हित दीर्घ address)
अणु
	वापस __sprपूर्णांक_symbol(buffer, address, -1, 1);
पूर्ण

/* To aव्योम using get_symbol_offset क्रम every symbol, we carry prefix aदीर्घ. */
काष्ठा kallsym_iter अणु
	loff_t pos;
	loff_t pos_arch_end;
	loff_t pos_mod_end;
	loff_t pos_ftrace_mod_end;
	loff_t pos_bpf_end;
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक nameoff; /* If iterating in core kernel symbols. */
	अक्षर type;
	अक्षर name[KSYM_NAME_LEN];
	अक्षर module_name[MODULE_NAME_LEN];
	पूर्णांक exported;
	पूर्णांक show_value;
पूर्ण;

पूर्णांक __weak arch_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value,
			    अक्षर *type, अक्षर *name)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_ksymbol_arch(काष्ठा kallsym_iter *iter)
अणु
	पूर्णांक ret = arch_get_kallsym(iter->pos - kallsyms_num_syms,
				   &iter->value, &iter->type,
				   iter->name);

	अगर (ret < 0) अणु
		iter->pos_arch_end = iter->pos;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक get_ksymbol_mod(काष्ठा kallsym_iter *iter)
अणु
	पूर्णांक ret = module_get_kallsym(iter->pos - iter->pos_arch_end,
				     &iter->value, &iter->type,
				     iter->name, iter->module_name,
				     &iter->exported);
	अगर (ret < 0) अणु
		iter->pos_mod_end = iter->pos;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * ftrace_mod_get_kallsym() may also get symbols क्रम pages allocated क्रम ftrace
 * purposes. In that हाल "__builtin__ftrace" is used as a module name, even
 * though "__builtin__ftrace" is not a module.
 */
अटल पूर्णांक get_ksymbol_ftrace_mod(काष्ठा kallsym_iter *iter)
अणु
	पूर्णांक ret = ftrace_mod_get_kallsym(iter->pos - iter->pos_mod_end,
					 &iter->value, &iter->type,
					 iter->name, iter->module_name,
					 &iter->exported);
	अगर (ret < 0) अणु
		iter->pos_ftrace_mod_end = iter->pos;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक get_ksymbol_bpf(काष्ठा kallsym_iter *iter)
अणु
	पूर्णांक ret;

	strlcpy(iter->module_name, "bpf", MODULE_NAME_LEN);
	iter->exported = 0;
	ret = bpf_get_kallsym(iter->pos - iter->pos_ftrace_mod_end,
			      &iter->value, &iter->type,
			      iter->name);
	अगर (ret < 0) अणु
		iter->pos_bpf_end = iter->pos;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * This uses "__builtin__kprobes" as a module name क्रम symbols क्रम pages
 * allocated क्रम kprobes' purposes, even though "__builtin__kprobes" is not a
 * module.
 */
अटल पूर्णांक get_ksymbol_kprobe(काष्ठा kallsym_iter *iter)
अणु
	strlcpy(iter->module_name, "__builtin__kprobes", MODULE_NAME_LEN);
	iter->exported = 0;
	वापस kprobe_get_kallsym(iter->pos - iter->pos_bpf_end,
				  &iter->value, &iter->type,
				  iter->name) < 0 ? 0 : 1;
पूर्ण

/* Returns space to next name. */
अटल अचिन्हित दीर्घ get_ksymbol_core(काष्ठा kallsym_iter *iter)
अणु
	अचिन्हित off = iter->nameoff;

	iter->module_name[0] = '\0';
	iter->value = kallsyms_sym_address(iter->pos);

	iter->type = kallsyms_get_symbol_type(off);

	off = kallsyms_expand_symbol(off, iter->name, ARRAY_SIZE(iter->name));

	वापस off - iter->nameoff;
पूर्ण

अटल व्योम reset_iter(काष्ठा kallsym_iter *iter, loff_t new_pos)
अणु
	iter->name[0] = '\0';
	iter->nameoff = get_symbol_offset(new_pos);
	iter->pos = new_pos;
	अगर (new_pos == 0) अणु
		iter->pos_arch_end = 0;
		iter->pos_mod_end = 0;
		iter->pos_ftrace_mod_end = 0;
		iter->pos_bpf_end = 0;
	पूर्ण
पूर्ण

/*
 * The end position (last + 1) of each additional kallsyms section is recorded
 * in iter->pos_..._end as each section is added, and so can be used to
 * determine which get_ksymbol_...() function to call next.
 */
अटल पूर्णांक update_iter_mod(काष्ठा kallsym_iter *iter, loff_t pos)
अणु
	iter->pos = pos;

	अगर ((!iter->pos_arch_end || iter->pos_arch_end > pos) &&
	    get_ksymbol_arch(iter))
		वापस 1;

	अगर ((!iter->pos_mod_end || iter->pos_mod_end > pos) &&
	    get_ksymbol_mod(iter))
		वापस 1;

	अगर ((!iter->pos_ftrace_mod_end || iter->pos_ftrace_mod_end > pos) &&
	    get_ksymbol_ftrace_mod(iter))
		वापस 1;

	अगर ((!iter->pos_bpf_end || iter->pos_bpf_end > pos) &&
	    get_ksymbol_bpf(iter))
		वापस 1;

	वापस get_ksymbol_kprobe(iter);
पूर्ण

/* Returns false अगर pos at or past end of file. */
अटल पूर्णांक update_iter(काष्ठा kallsym_iter *iter, loff_t pos)
अणु
	/* Module symbols can be accessed अक्रमomly. */
	अगर (pos >= kallsyms_num_syms)
		वापस update_iter_mod(iter, pos);

	/* If we're not on the desired position, reset to new position. */
	अगर (pos != iter->pos)
		reset_iter(iter, pos);

	iter->nameoff += get_ksymbol_core(iter);
	iter->pos++;

	वापस 1;
पूर्ण

अटल व्योम *s_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	(*pos)++;

	अगर (!update_iter(m->निजी, *pos))
		वापस शून्य;
	वापस p;
पूर्ण

अटल व्योम *s_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अगर (!update_iter(m->निजी, *pos))
		वापस शून्य;
	वापस m->निजी;
पूर्ण

अटल व्योम s_stop(काष्ठा seq_file *m, व्योम *p)
अणु
पूर्ण

अटल पूर्णांक s_show(काष्ठा seq_file *m, व्योम *p)
अणु
	व्योम *value;
	काष्ठा kallsym_iter *iter = m->निजी;

	/* Some debugging symbols have no name.  Ignore them. */
	अगर (!iter->name[0])
		वापस 0;

	value = iter->show_value ? (व्योम *)iter->value : शून्य;

	अगर (iter->module_name[0]) अणु
		अक्षर type;

		/*
		 * Label it "global" अगर it is exported,
		 * "local" अगर not exported.
		 */
		type = iter->exported ? बड़े(iter->type) :
					छोटे(iter->type);
		seq_म_लिखो(m, "%px %c %s\t[%s]\n", value,
			   type, iter->name, iter->module_name);
	पूर्ण अन्यथा
		seq_म_लिखो(m, "%px %c %s\n", value,
			   iter->type, iter->name);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations kallsyms_op = अणु
	.start = s_start,
	.next = s_next,
	.stop = s_stop,
	.show = s_show
पूर्ण;

अटल अंतरभूत पूर्णांक kallsyms_क्रम_perf(व्योम)
अणु
#अगर_घोषित CONFIG_PERF_EVENTS
	बाह्य पूर्णांक sysctl_perf_event_paranoid;
	अगर (sysctl_perf_event_paranoid <= 1)
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * We show kallsyms inक्रमmation even to normal users अगर we've enabled
 * kernel profiling and are explicitly not paranoid (so kptr_restrict
 * is clear, and sysctl_perf_event_paranoid isn't set).
 *
 * Otherwise, require CAP_SYSLOG (assuming kptr_restrict isn't set to
 * block even that).
 */
bool kallsyms_show_value(स्थिर काष्ठा cred *cred)
अणु
	चयन (kptr_restrict) अणु
	हाल 0:
		अगर (kallsyms_क्रम_perf())
			वापस true;
		fallthrough;
	हाल 1:
		अगर (security_capable(cred, &init_user_ns, CAP_SYSLOG,
				     CAP_OPT_NOAUDIT) == 0)
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक kallsyms_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * We keep iterator in m->निजी, since normal हाल is to
	 * s_start from where we left off, so we aव्योम करोing
	 * using get_symbol_offset क्रम every symbol.
	 */
	काष्ठा kallsym_iter *iter;
	iter = __seq_खोलो_निजी(file, &kallsyms_op, माप(*iter));
	अगर (!iter)
		वापस -ENOMEM;
	reset_iter(iter, 0);

	/*
	 * Instead of checking this on every s_show() call, cache
	 * the result here at खोलो समय.
	 */
	iter->show_value = kallsyms_show_value(file->f_cred);
	वापस 0;
पूर्ण

#अगर_घोषित	CONFIG_KGDB_KDB
स्थिर अक्षर *kdb_walk_kallsyms(loff_t *pos)
अणु
	अटल काष्ठा kallsym_iter kdb_walk_kallsyms_iter;
	अगर (*pos == 0) अणु
		स_रखो(&kdb_walk_kallsyms_iter, 0,
		       माप(kdb_walk_kallsyms_iter));
		reset_iter(&kdb_walk_kallsyms_iter, 0);
	पूर्ण
	जबतक (1) अणु
		अगर (!update_iter(&kdb_walk_kallsyms_iter, *pos))
			वापस शून्य;
		++*pos;
		/* Some debugging symbols have no name.  Ignore them. */
		अगर (kdb_walk_kallsyms_iter.name[0])
			वापस kdb_walk_kallsyms_iter.name;
	पूर्ण
पूर्ण
#पूर्ण_अगर	/* CONFIG_KGDB_KDB */

अटल स्थिर काष्ठा proc_ops kallsyms_proc_ops = अणु
	.proc_खोलो	= kallsyms_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release_निजी,
पूर्ण;

अटल पूर्णांक __init kallsyms_init(व्योम)
अणु
	proc_create("kallsyms", 0444, शून्य, &kallsyms_proc_ops);
	वापस 0;
पूर्ण
device_initcall(kallsyms_init);
