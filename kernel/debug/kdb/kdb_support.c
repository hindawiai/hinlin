<शैली गुरु>
/*
 * Kernel Debugger Architecture Independent Support Functions
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1999-2004 Silicon Graphics, Inc.  All Rights Reserved.
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 * 03/02/13    added new 2.5 kallsyms <xavier.bru@bull.net>
 */

#समावेश <मानकतर्क.स>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kdb.h>
#समावेश <linux/slab.h>
#समावेश "kdb_private.h"

/*
 * kdbमाला_लोymval - Return the address of the given symbol.
 *
 * Parameters:
 *	symname	Character string containing symbol name
 *      symtab  Structure to receive results
 * Returns:
 *	0	Symbol not found, symtab zero filled
 *	1	Symbol mapped to module/symbol/section, data in symtab
 */
पूर्णांक kdbमाला_लोymval(स्थिर अक्षर *symname, kdb_symtab_t *symtab)
अणु
	kdb_dbg_म_लिखो(AR, "symname=%s, symtab=%px\n", symname, symtab);
	स_रखो(symtab, 0, माप(*symtab));
	symtab->sym_start = kallsyms_lookup_name(symname);
	अगर (symtab->sym_start) अणु
		kdb_dbg_म_लिखो(AR, "returns 1, symtab->sym_start=0x%lx\n",
			       symtab->sym_start);
		वापस 1;
	पूर्ण
	kdb_dbg_म_लिखो(AR, "returns 0\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kdbमाला_लोymval);

अटल अक्षर *kdb_name_table[100];	/* arbitrary size */

/*
 * kdbnearsym -	Return the name of the symbol with the nearest address
 *	less than 'addr'.
 *
 * Parameters:
 *	addr	Address to check क्रम symbol near
 *	symtab  Structure to receive results
 * Returns:
 *	0	No sections contain this address, symtab zero filled
 *	1	Address mapped to module/symbol/section, data in symtab
 * Remarks:
 *	2.6 kallsyms has a "feature" where it unpacks the name पूर्णांकo a
 *	string.  If that string is reused beक्रमe the caller expects it
 *	then the caller sees its string change without warning.  To
 *	aव्योम cluttering up the मुख्य kdb code with lots of kdb_strdup,
 *	tests and kमुक्त calls, kdbnearsym मुख्यtains an LRU list of the
 *	last few unique strings.  The list is sized large enough to
 *	hold active strings, no kdb caller of kdbnearsym makes more
 *	than ~20 later calls beक्रमe using a saved value.
 */
पूर्णांक kdbnearsym(अचिन्हित दीर्घ addr, kdb_symtab_t *symtab)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ symbolsize = 0;
	अचिन्हित दीर्घ offset = 0;
#घोषणा knt1_size 128		/* must be >= kallsyms table size */
	अक्षर *knt1 = शून्य;

	kdb_dbg_म_लिखो(AR, "addr=0x%lx, symtab=%px\n", addr, symtab);
	स_रखो(symtab, 0, माप(*symtab));

	अगर (addr < 4096)
		जाओ out;
	knt1 = debug_kदो_स्मृति(knt1_size, GFP_ATOMIC);
	अगर (!knt1) अणु
		kdb_func_म_लिखो("addr=0x%lx cannot kmalloc knt1\n", addr);
		जाओ out;
	पूर्ण
	symtab->sym_name = kallsyms_lookup(addr, &symbolsize , &offset,
				(अक्षर **)(&symtab->mod_name), knt1);
	अगर (offset > 8*1024*1024) अणु
		symtab->sym_name = शून्य;
		addr = offset = symbolsize = 0;
	पूर्ण
	symtab->sym_start = addr - offset;
	symtab->sym_end = symtab->sym_start + symbolsize;
	ret = symtab->sym_name != शून्य && *(symtab->sym_name) != '\0';

	अगर (ret) अणु
		पूर्णांक i;
		/* Another 2.6 kallsyms "feature".  Someबार the sym_name is
		 * set but the buffer passed पूर्णांकo kallsyms_lookup is not used,
		 * so it contains garbage.  The caller has to work out which
		 * buffer needs to be saved.
		 *
		 * What was Rusty smoking when he wrote that code?
		 */
		अगर (symtab->sym_name != knt1) अणु
			म_नकलन(knt1, symtab->sym_name, knt1_size);
			knt1[knt1_size-1] = '\0';
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(kdb_name_table); ++i) अणु
			अगर (kdb_name_table[i] &&
			    म_भेद(kdb_name_table[i], knt1) == 0)
				अवरोध;
		पूर्ण
		अगर (i >= ARRAY_SIZE(kdb_name_table)) अणु
			debug_kमुक्त(kdb_name_table[0]);
			स_हटाओ(kdb_name_table, kdb_name_table+1,
			       माप(kdb_name_table[0]) *
			       (ARRAY_SIZE(kdb_name_table)-1));
		पूर्ण अन्यथा अणु
			debug_kमुक्त(knt1);
			knt1 = kdb_name_table[i];
			स_हटाओ(kdb_name_table+i, kdb_name_table+i+1,
			       माप(kdb_name_table[0]) *
			       (ARRAY_SIZE(kdb_name_table)-i-1));
		पूर्ण
		i = ARRAY_SIZE(kdb_name_table) - 1;
		kdb_name_table[i] = knt1;
		symtab->sym_name = kdb_name_table[i];
		knt1 = शून्य;
	पूर्ण

	अगर (symtab->mod_name == शून्य)
		symtab->mod_name = "kernel";
	kdb_dbg_म_लिखो(AR, "returns %d symtab->sym_start=0x%lx, symtab->mod_name=%px, symtab->sym_name=%px (%s)\n",
		       ret, symtab->sym_start, symtab->mod_name, symtab->sym_name, symtab->sym_name);

out:
	debug_kमुक्त(knt1);
	वापस ret;
पूर्ण

व्योम kdbnearsym_cleanup(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(kdb_name_table); ++i) अणु
		अगर (kdb_name_table[i]) अणु
			debug_kमुक्त(kdb_name_table[i]);
			kdb_name_table[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल अक्षर ks_namebuf[KSYM_NAME_LEN+1], ks_namebuf_prev[KSYM_NAME_LEN+1];

/*
 * kallsyms_symbol_complete
 *
 * Parameters:
 *	prefix_name	prefix of a symbol name to lookup
 *	max_len		maximum length that can be वापसed
 * Returns:
 *	Number of symbols which match the given prefix.
 * Notes:
 *	prefix_name is changed to contain the दीर्घest unique prefix that
 *	starts with this prefix (tab completion).
 */
पूर्णांक kallsyms_symbol_complete(अक्षर *prefix_name, पूर्णांक max_len)
अणु
	loff_t pos = 0;
	पूर्णांक prefix_len = म_माप(prefix_name), prev_len = 0;
	पूर्णांक i, number = 0;
	स्थिर अक्षर *name;

	जबतक ((name = kdb_walk_kallsyms(&pos))) अणु
		अगर (म_भेदन(name, prefix_name, prefix_len) == 0) अणु
			strscpy(ks_namebuf, name, माप(ks_namebuf));
			/* Work out the दीर्घest name that matches the prefix */
			अगर (++number == 1) अणु
				prev_len = min_t(पूर्णांक, max_len-1,
						 म_माप(ks_namebuf));
				स_नकल(ks_namebuf_prev, ks_namebuf, prev_len);
				ks_namebuf_prev[prev_len] = '\0';
				जारी;
			पूर्ण
			क्रम (i = 0; i < prev_len; i++) अणु
				अगर (ks_namebuf[i] != ks_namebuf_prev[i]) अणु
					prev_len = i;
					ks_namebuf_prev[i] = '\0';
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (prev_len > prefix_len)
		स_नकल(prefix_name, ks_namebuf_prev, prev_len+1);
	वापस number;
पूर्ण

/*
 * kallsyms_symbol_next
 *
 * Parameters:
 *	prefix_name	prefix of a symbol name to lookup
 *	flag	0 means search from the head, 1 means जारी search.
 *	buf_size	maximum length that can be written to prefix_name
 *			buffer
 * Returns:
 *	1 अगर a symbol matches the given prefix.
 *	0 अगर no string found
 */
पूर्णांक kallsyms_symbol_next(अक्षर *prefix_name, पूर्णांक flag, पूर्णांक buf_size)
अणु
	पूर्णांक prefix_len = म_माप(prefix_name);
	अटल loff_t pos;
	स्थिर अक्षर *name;

	अगर (!flag)
		pos = 0;

	जबतक ((name = kdb_walk_kallsyms(&pos))) अणु
		अगर (!म_भेदन(name, prefix_name, prefix_len))
			वापस strscpy(prefix_name, name, buf_size);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * kdb_symbol_prपूर्णांक - Standard method क्रम prपूर्णांकing a symbol name and offset.
 * Inमाला_दो:
 *	addr	Address to be prपूर्णांकed.
 *	symtab	Address of symbol data, अगर शून्य this routine करोes its
 *		own lookup.
 *	punc	Punctuation क्रम string, bit field.
 * Remarks:
 *	The string and its punctuation is only prपूर्णांकed अगर the address
 *	is inside the kernel, except that the value is always prपूर्णांकed
 *	when requested.
 */
व्योम kdb_symbol_prपूर्णांक(अचिन्हित दीर्घ addr, स्थिर kdb_symtab_t *symtab_p,
		      अचिन्हित पूर्णांक punc)
अणु
	kdb_symtab_t symtab, *symtab_p2;
	अगर (symtab_p) अणु
		symtab_p2 = (kdb_symtab_t *)symtab_p;
	पूर्ण अन्यथा अणु
		symtab_p2 = &symtab;
		kdbnearsym(addr, symtab_p2);
	पूर्ण
	अगर (!(symtab_p2->sym_name || (punc & KDB_SP_VALUE)))
		वापस;
	अगर (punc & KDB_SP_SPACEB)
		kdb_म_लिखो(" ");
	अगर (punc & KDB_SP_VALUE)
		kdb_म_लिखो(kdb_machreg_fmt0, addr);
	अगर (symtab_p2->sym_name) अणु
		अगर (punc & KDB_SP_VALUE)
			kdb_म_लिखो(" ");
		अगर (punc & KDB_SP_PAREN)
			kdb_म_लिखो("(");
		अगर (म_भेद(symtab_p2->mod_name, "kernel"))
			kdb_म_लिखो("[%s]", symtab_p2->mod_name);
		kdb_म_लिखो("%s", symtab_p2->sym_name);
		अगर (addr != symtab_p2->sym_start)
			kdb_म_लिखो("+0x%lx", addr - symtab_p2->sym_start);
		अगर (punc & KDB_SP_SYMSIZE)
			kdb_म_लिखो("/0x%lx",
				   symtab_p2->sym_end - symtab_p2->sym_start);
		अगर (punc & KDB_SP_PAREN)
			kdb_म_लिखो(")");
	पूर्ण
	अगर (punc & KDB_SP_SPACEA)
		kdb_म_लिखो(" ");
	अगर (punc & KDB_SP_NEWLINE)
		kdb_म_लिखो("\n");
पूर्ण

/*
 * kdb_strdup - kdb equivalent of strdup, क्रम disयंत्र code.
 * Inमाला_दो:
 *	str	The string to duplicate.
 *	type	Flags to kदो_स्मृति क्रम the new string.
 * Returns:
 *	Address of the new string, शून्य अगर storage could not be allocated.
 * Remarks:
 *	This is not in lib/string.c because it uses kदो_स्मृति which is not
 *	available when string.o is used in boot loaders.
 */
अक्षर *kdb_strdup(स्थिर अक्षर *str, gfp_t type)
अणु
	पूर्णांक n = म_माप(str)+1;
	अक्षर *s = kदो_स्मृति(n, type);
	अगर (!s)
		वापस शून्य;
	वापस म_नकल(s, str);
पूर्ण

/*
 * kdb_getarea_size - Read an area of data.  The kdb equivalent of
 *	copy_from_user, with kdb messages क्रम invalid addresses.
 * Inमाला_दो:
 *	res	Poपूर्णांकer to the area to receive the result.
 *	addr	Address of the area to copy.
 *	size	Size of the area.
 * Returns:
 *	0 क्रम success, < 0 क्रम error.
 */
पूर्णांक kdb_getarea_size(व्योम *res, अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	पूर्णांक ret = copy_from_kernel_nofault((अक्षर *)res, (अक्षर *)addr, size);
	अगर (ret) अणु
		अगर (!KDB_STATE(SUPPRESS)) अणु
			kdb_func_म_लिखो("Bad address 0x%lx\n", addr);
			KDB_STATE_SET(SUPPRESS);
		पूर्ण
		ret = KDB_BADADDR;
	पूर्ण अन्यथा अणु
		KDB_STATE_CLEAR(SUPPRESS);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * kdb_putarea_size - Write an area of data.  The kdb equivalent of
 *	copy_to_user, with kdb messages क्रम invalid addresses.
 * Inमाला_दो:
 *	addr	Address of the area to ग_लिखो to.
 *	res	Poपूर्णांकer to the area holding the data.
 *	size	Size of the area.
 * Returns:
 *	0 क्रम success, < 0 क्रम error.
 */
पूर्णांक kdb_putarea_size(अचिन्हित दीर्घ addr, व्योम *res, माप_प्रकार size)
अणु
	पूर्णांक ret = copy_from_kernel_nofault((अक्षर *)addr, (अक्षर *)res, size);
	अगर (ret) अणु
		अगर (!KDB_STATE(SUPPRESS)) अणु
			kdb_func_म_लिखो("Bad address 0x%lx\n", addr);
			KDB_STATE_SET(SUPPRESS);
		पूर्ण
		ret = KDB_BADADDR;
	पूर्ण अन्यथा अणु
		KDB_STATE_CLEAR(SUPPRESS);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * kdb_getphys - Read data from a physical address. Validate the
 * 	address is in range, use kmap_atomic() to get data
 * 	similar to kdb_getarea() - but क्रम phys addresses
 * Inमाला_दो:
 * 	res	Poपूर्णांकer to the word to receive the result
 * 	addr	Physical address of the area to copy
 * 	size	Size of the area
 * Returns:
 *	0 क्रम success, < 0 क्रम error.
 */
अटल पूर्णांक kdb_getphys(व्योम *res, अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ pfn;
	व्योम *vaddr;
	काष्ठा page *page;

	pfn = (addr >> PAGE_SHIFT);
	अगर (!pfn_valid(pfn))
		वापस 1;
	page = pfn_to_page(pfn);
	vaddr = kmap_atomic(page);
	स_नकल(res, vaddr + (addr & (PAGE_SIZE - 1)), size);
	kunmap_atomic(vaddr);

	वापस 0;
पूर्ण

/*
 * kdb_getphysword
 * Inमाला_दो:
 *	word	Poपूर्णांकer to the word to receive the result.
 *	addr	Address of the area to copy.
 *	size	Size of the area.
 * Returns:
 *	0 क्रम success, < 0 क्रम error.
 */
पूर्णांक kdb_getphysword(अचिन्हित दीर्घ *word, अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	पूर्णांक diag;
	__u8  w1;
	__u16 w2;
	__u32 w4;
	__u64 w8;
	*word = 0;	/* Default value अगर addr or size is invalid */

	चयन (size) अणु
	हाल 1:
		diag = kdb_getphys(&w1, addr, माप(w1));
		अगर (!diag)
			*word = w1;
		अवरोध;
	हाल 2:
		diag = kdb_getphys(&w2, addr, माप(w2));
		अगर (!diag)
			*word = w2;
		अवरोध;
	हाल 4:
		diag = kdb_getphys(&w4, addr, माप(w4));
		अगर (!diag)
			*word = w4;
		अवरोध;
	हाल 8:
		अगर (size <= माप(*word)) अणु
			diag = kdb_getphys(&w8, addr, माप(w8));
			अगर (!diag)
				*word = w8;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		diag = KDB_BADWIDTH;
		kdb_func_म_लिखो("bad width %zu\n", size);
	पूर्ण
	वापस diag;
पूर्ण

/*
 * kdb_getword - Read a binary value.  Unlike kdb_getarea, this treats
 *	data as numbers.
 * Inमाला_दो:
 *	word	Poपूर्णांकer to the word to receive the result.
 *	addr	Address of the area to copy.
 *	size	Size of the area.
 * Returns:
 *	0 क्रम success, < 0 क्रम error.
 */
पूर्णांक kdb_getword(अचिन्हित दीर्घ *word, अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	पूर्णांक diag;
	__u8  w1;
	__u16 w2;
	__u32 w4;
	__u64 w8;
	*word = 0;	/* Default value अगर addr or size is invalid */
	चयन (size) अणु
	हाल 1:
		diag = kdb_getarea(w1, addr);
		अगर (!diag)
			*word = w1;
		अवरोध;
	हाल 2:
		diag = kdb_getarea(w2, addr);
		अगर (!diag)
			*word = w2;
		अवरोध;
	हाल 4:
		diag = kdb_getarea(w4, addr);
		अगर (!diag)
			*word = w4;
		अवरोध;
	हाल 8:
		अगर (size <= माप(*word)) अणु
			diag = kdb_getarea(w8, addr);
			अगर (!diag)
				*word = w8;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		diag = KDB_BADWIDTH;
		kdb_func_म_लिखो("bad width %zu\n", size);
	पूर्ण
	वापस diag;
पूर्ण

/*
 * kdb_putword - Write a binary value.  Unlike kdb_putarea, this
 *	treats data as numbers.
 * Inमाला_दो:
 *	addr	Address of the area to ग_लिखो to..
 *	word	The value to set.
 *	size	Size of the area.
 * Returns:
 *	0 क्रम success, < 0 क्रम error.
 */
पूर्णांक kdb_putword(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ word, माप_प्रकार size)
अणु
	पूर्णांक diag;
	__u8  w1;
	__u16 w2;
	__u32 w4;
	__u64 w8;
	चयन (size) अणु
	हाल 1:
		w1 = word;
		diag = kdb_putarea(addr, w1);
		अवरोध;
	हाल 2:
		w2 = word;
		diag = kdb_putarea(addr, w2);
		अवरोध;
	हाल 4:
		w4 = word;
		diag = kdb_putarea(addr, w4);
		अवरोध;
	हाल 8:
		अगर (size <= माप(word)) अणु
			w8 = word;
			diag = kdb_putarea(addr, w8);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		diag = KDB_BADWIDTH;
		kdb_func_म_लिखो("bad width %zu\n", size);
	पूर्ण
	वापस diag;
पूर्ण

/*
 * kdb_task_state_string - Convert a string containing any of the
 *	letters DRSTCZEUIMA to a mask क्रम the process state field and
 *	वापस the value.  If no argument is supplied, वापस the mask
 *	that corresponds to environment variable PS, DRSTCZEU by
 *	शेष.
 * Inमाला_दो:
 *	s	String to convert
 * Returns:
 *	Mask क्रम process state.
 * Notes:
 *	The mask folds data from several sources पूर्णांकo a single दीर्घ value, so
 *	be careful not to overlap the bits.  TASK_* bits are in the LSB,
 *	special हालs like UNRUNNABLE are in the MSB.  As of 2.6.10-rc1 there
 *	is no overlap between TASK_* and EXIT_* but that may not always be
 *	true, so EXIT_* bits are shअगरted left 16 bits beक्रमe being stored in
 *	the mask.
 */

/* unrunnable is < 0 */
#घोषणा UNRUNNABLE	(1UL << (8*माप(अचिन्हित दीर्घ) - 1))
#घोषणा RUNNING		(1UL << (8*माप(अचिन्हित दीर्घ) - 2))
#घोषणा IDLE		(1UL << (8*माप(अचिन्हित दीर्घ) - 3))
#घोषणा DAEMON		(1UL << (8*माप(अचिन्हित दीर्घ) - 4))

अचिन्हित दीर्घ kdb_task_state_string(स्थिर अक्षर *s)
अणु
	दीर्घ res = 0;
	अगर (!s) अणु
		s = kdbदो_पर्या("PS");
		अगर (!s)
			s = "DRSTCZEU";	/* शेष value क्रम ps */
	पूर्ण
	जबतक (*s) अणु
		चयन (*s) अणु
		हाल 'D':
			res |= TASK_UNINTERRUPTIBLE;
			अवरोध;
		हाल 'R':
			res |= RUNNING;
			अवरोध;
		हाल 'S':
			res |= TASK_INTERRUPTIBLE;
			अवरोध;
		हाल 'T':
			res |= TASK_STOPPED;
			अवरोध;
		हाल 'C':
			res |= TASK_TRACED;
			अवरोध;
		हाल 'Z':
			res |= EXIT_ZOMBIE << 16;
			अवरोध;
		हाल 'E':
			res |= EXIT_DEAD << 16;
			अवरोध;
		हाल 'U':
			res |= UNRUNNABLE;
			अवरोध;
		हाल 'I':
			res |= IDLE;
			अवरोध;
		हाल 'M':
			res |= DAEMON;
			अवरोध;
		हाल 'A':
			res = ~0UL;
			अवरोध;
		शेष:
			  kdb_func_म_लिखो("unknown flag '%c' ignored\n", *s);
			  अवरोध;
		पूर्ण
		++s;
	पूर्ण
	वापस res;
पूर्ण

/*
 * kdb_task_state_अक्षर - Return the अक्षरacter that represents the task state.
 * Inमाला_दो:
 *	p	काष्ठा task क्रम the process
 * Returns:
 *	One अक्षरacter to represent the task state.
 */
अक्षर kdb_task_state_अक्षर (स्थिर काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक cpu;
	अक्षर state;
	अचिन्हित दीर्घ पंचांगp;

	अगर (!p ||
	    copy_from_kernel_nofault(&पंचांगp, (अक्षर *)p, माप(अचिन्हित दीर्घ)))
		वापस 'E';

	cpu = kdb_process_cpu(p);
	state = (p->state == 0) ? 'R' :
		(p->state < 0) ? 'U' :
		(p->state & TASK_UNINTERRUPTIBLE) ? 'D' :
		(p->state & TASK_STOPPED) ? 'T' :
		(p->state & TASK_TRACED) ? 'C' :
		(p->निकास_state & EXIT_ZOMBIE) ? 'Z' :
		(p->निकास_state & EXIT_DEAD) ? 'E' :
		(p->state & TASK_INTERRUPTIBLE) ? 'S' : '?';
	अगर (is_idle_task(p)) अणु
		/* Idle task.  Is it really idle, apart from the kdb
		 * पूर्णांकerrupt? */
		अगर (!kdb_task_has_cpu(p) || kgdb_info[cpu].irq_depth == 1) अणु
			अगर (cpu != kdb_initial_cpu)
				state = 'I';	/* idle task */
		पूर्ण
	पूर्ण अन्यथा अगर (!p->mm && state == 'S') अणु
		state = 'M';	/* sleeping प्रणाली daemon */
	पूर्ण
	वापस state;
पूर्ण

/*
 * kdb_task_state - Return true अगर a process has the desired state
 *	given by the mask.
 * Inमाला_दो:
 *	p	काष्ठा task क्रम the process
 *	mask	mask from kdb_task_state_string to select processes
 * Returns:
 *	True अगर the process matches at least one criteria defined by the mask.
 */
अचिन्हित दीर्घ kdb_task_state(स्थिर काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ mask)
अणु
	अक्षर state[] = अणु kdb_task_state_अक्षर(p), '\0' पूर्ण;
	वापस (mask & kdb_task_state_string(state)) != 0;
पूर्ण

/* Last ditch allocator क्रम debugging, so we can still debug even when
 * the GFP_ATOMIC pool has been exhausted.  The algorithms are tuned
 * क्रम space usage, not क्रम speed.  One smallish memory pool, the मुक्त
 * chain is always in ascending address order to allow coalescing,
 * allocations are करोne in brute क्रमce best fit.
 */

काष्ठा debug_alloc_header अणु
	u32 next;	/* offset of next header from start of pool */
	u32 size;
	व्योम *caller;
पूर्ण;

/* The memory वापसed by this allocator must be aligned, which means
 * so must the header size.  Do not assume that माप(काष्ठा
 * debug_alloc_header) is a multiple of the alignment, explicitly
 * calculate the overhead of this header, including the alignment.
 * The rest of this code must not use माप() on any header or
 * poपूर्णांकer to a header.
 */
#घोषणा dah_align 8
#घोषणा dah_overhead ALIGN(माप(काष्ठा debug_alloc_header), dah_align)

अटल u64 debug_alloc_pool_aligned[256*1024/dah_align];	/* 256K pool */
अटल अक्षर *debug_alloc_pool = (अक्षर *)debug_alloc_pool_aligned;
अटल u32 dah_first, dah_first_call = 1, dah_used, dah_used_max;

/* Locking is awkward.  The debug code is called from all contexts,
 * including non maskable पूर्णांकerrupts.  A normal spinlock is not safe
 * in NMI context.  Try to get the debug allocator lock, अगर it cannot
 * be obtained after a second then give up.  If the lock could not be
 * previously obtained on this cpu then only try once.
 *
 * sparse has no annotation क्रम "this function _someबार_ acquires a
 * lock", so fudge the acquire/release notation.
 */
अटल DEFINE_SPINLOCK(dap_lock);
अटल पूर्णांक get_dap_lock(व्योम)
	__acquires(dap_lock)
अणु
	अटल पूर्णांक dap_locked = -1;
	पूर्णांक count;
	अगर (dap_locked == smp_processor_id())
		count = 1;
	अन्यथा
		count = 1000;
	जबतक (1) अणु
		अगर (spin_trylock(&dap_lock)) अणु
			dap_locked = -1;
			वापस 1;
		पूर्ण
		अगर (!count--)
			अवरोध;
		udelay(1000);
	पूर्ण
	dap_locked = smp_processor_id();
	__acquire(dap_lock);
	वापस 0;
पूर्ण

व्योम *debug_kदो_स्मृति(माप_प्रकार size, gfp_t flags)
अणु
	अचिन्हित पूर्णांक rem, h_offset;
	काष्ठा debug_alloc_header *best, *bestprev, *prev, *h;
	व्योम *p = शून्य;
	अगर (!get_dap_lock()) अणु
		__release(dap_lock);	/* we never actually got it */
		वापस शून्य;
	पूर्ण
	h = (काष्ठा debug_alloc_header *)(debug_alloc_pool + dah_first);
	अगर (dah_first_call) अणु
		h->size = माप(debug_alloc_pool_aligned) - dah_overhead;
		dah_first_call = 0;
	पूर्ण
	size = ALIGN(size, dah_align);
	prev = best = bestprev = शून्य;
	जबतक (1) अणु
		अगर (h->size >= size && (!best || h->size < best->size)) अणु
			best = h;
			bestprev = prev;
			अगर (h->size == size)
				अवरोध;
		पूर्ण
		अगर (!h->next)
			अवरोध;
		prev = h;
		h = (काष्ठा debug_alloc_header *)(debug_alloc_pool + h->next);
	पूर्ण
	अगर (!best)
		जाओ out;
	rem = best->size - size;
	/* The pool must always contain at least one header */
	अगर (best->next == 0 && bestprev == शून्य && rem < dah_overhead)
		जाओ out;
	अगर (rem >= dah_overhead) अणु
		best->size = size;
		h_offset = ((अक्षर *)best - debug_alloc_pool) +
			   dah_overhead + best->size;
		h = (काष्ठा debug_alloc_header *)(debug_alloc_pool + h_offset);
		h->size = rem - dah_overhead;
		h->next = best->next;
	पूर्ण अन्यथा
		h_offset = best->next;
	best->caller = __builtin_वापस_address(0);
	dah_used += best->size;
	dah_used_max = max(dah_used, dah_used_max);
	अगर (bestprev)
		bestprev->next = h_offset;
	अन्यथा
		dah_first = h_offset;
	p = (अक्षर *)best + dah_overhead;
	स_रखो(p, POISON_INUSE, best->size - 1);
	*((अक्षर *)p + best->size - 1) = POISON_END;
out:
	spin_unlock(&dap_lock);
	वापस p;
पूर्ण

व्योम debug_kमुक्त(व्योम *p)
अणु
	काष्ठा debug_alloc_header *h;
	अचिन्हित पूर्णांक h_offset;
	अगर (!p)
		वापस;
	अगर ((अक्षर *)p < debug_alloc_pool ||
	    (अक्षर *)p >= debug_alloc_pool + माप(debug_alloc_pool_aligned)) अणु
		kमुक्त(p);
		वापस;
	पूर्ण
	अगर (!get_dap_lock()) अणु
		__release(dap_lock);	/* we never actually got it */
		वापस;		/* memory leak, cannot be helped */
	पूर्ण
	h = (काष्ठा debug_alloc_header *)((अक्षर *)p - dah_overhead);
	स_रखो(p, POISON_FREE, h->size - 1);
	*((अक्षर *)p + h->size - 1) = POISON_END;
	h->caller = शून्य;
	dah_used -= h->size;
	h_offset = (अक्षर *)h - debug_alloc_pool;
	अगर (h_offset < dah_first) अणु
		h->next = dah_first;
		dah_first = h_offset;
	पूर्ण अन्यथा अणु
		काष्ठा debug_alloc_header *prev;
		अचिन्हित पूर्णांक prev_offset;
		prev = (काष्ठा debug_alloc_header *)(debug_alloc_pool +
						     dah_first);
		जबतक (1) अणु
			अगर (!prev->next || prev->next > h_offset)
				अवरोध;
			prev = (काष्ठा debug_alloc_header *)
				(debug_alloc_pool + prev->next);
		पूर्ण
		prev_offset = (अक्षर *)prev - debug_alloc_pool;
		अगर (prev_offset + dah_overhead + prev->size == h_offset) अणु
			prev->size += dah_overhead + h->size;
			स_रखो(h, POISON_FREE, dah_overhead - 1);
			*((अक्षर *)h + dah_overhead - 1) = POISON_END;
			h = prev;
			h_offset = prev_offset;
		पूर्ण अन्यथा अणु
			h->next = prev->next;
			prev->next = h_offset;
		पूर्ण
	पूर्ण
	अगर (h_offset + dah_overhead + h->size == h->next) अणु
		काष्ठा debug_alloc_header *next;
		next = (काष्ठा debug_alloc_header *)
			(debug_alloc_pool + h->next);
		h->size += dah_overhead + next->size;
		h->next = next->next;
		स_रखो(next, POISON_FREE, dah_overhead - 1);
		*((अक्षर *)next + dah_overhead - 1) = POISON_END;
	पूर्ण
	spin_unlock(&dap_lock);
पूर्ण

व्योम debug_kusage(व्योम)
अणु
	काष्ठा debug_alloc_header *h_मुक्त, *h_used;
#अगर_घोषित	CONFIG_IA64
	/* FIXME: using dah क्रम ia64 unwind always results in a memory leak.
	 * Fix that memory leak first, then set debug_kusage_one_समय = 1 क्रम
	 * all architectures.
	 */
	अटल पूर्णांक debug_kusage_one_समय;
#अन्यथा
	अटल पूर्णांक debug_kusage_one_समय = 1;
#पूर्ण_अगर
	अगर (!get_dap_lock()) अणु
		__release(dap_lock);	/* we never actually got it */
		वापस;
	पूर्ण
	h_मुक्त = (काष्ठा debug_alloc_header *)(debug_alloc_pool + dah_first);
	अगर (dah_first == 0 &&
	    (h_मुक्त->size == माप(debug_alloc_pool_aligned) - dah_overhead ||
	     dah_first_call))
		जाओ out;
	अगर (!debug_kusage_one_समय)
		जाओ out;
	debug_kusage_one_समय = 0;
	kdb_func_म_लिखो("debug_kmalloc memory leak dah_first %d\n", dah_first);
	अगर (dah_first) अणु
		h_used = (काष्ठा debug_alloc_header *)debug_alloc_pool;
		kdb_func_म_लिखो("h_used %px size %d\n", h_used, h_used->size);
	पूर्ण
	करो अणु
		h_used = (काष्ठा debug_alloc_header *)
			  ((अक्षर *)h_मुक्त + dah_overhead + h_मुक्त->size);
		kdb_func_म_लिखो("h_used %px size %d caller %px\n",
				h_used, h_used->size, h_used->caller);
		h_मुक्त = (काष्ठा debug_alloc_header *)
			  (debug_alloc_pool + h_मुक्त->next);
	पूर्ण जबतक (h_मुक्त->next);
	h_used = (काष्ठा debug_alloc_header *)
		  ((अक्षर *)h_मुक्त + dah_overhead + h_मुक्त->size);
	अगर ((अक्षर *)h_used - debug_alloc_pool !=
	    माप(debug_alloc_pool_aligned))
		kdb_func_म_लिखो("h_used %px size %d caller %px\n",
				h_used, h_used->size, h_used->caller);
out:
	spin_unlock(&dap_lock);
पूर्ण

/* Maपूर्णांकain a small stack of kdb_flags to allow recursion without disturbing
 * the global kdb state.
 */

अटल पूर्णांक kdb_flags_stack[4], kdb_flags_index;

व्योम kdb_save_flags(व्योम)
अणु
	BUG_ON(kdb_flags_index >= ARRAY_SIZE(kdb_flags_stack));
	kdb_flags_stack[kdb_flags_index++] = kdb_flags;
पूर्ण

व्योम kdb_restore_flags(व्योम)
अणु
	BUG_ON(kdb_flags_index <= 0);
	kdb_flags = kdb_flags_stack[--kdb_flags_index];
पूर्ण
