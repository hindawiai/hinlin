<शैली गुरु>
/* Generate assembler source containing symbol inक्रमmation
 *
 * Copyright 2002       by Kai Germaschewski
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 * Usage: nm -n vmlinux | scripts/kallsyms [--all-symbols] > symbols.S
 *
 *      Table compression uses all the unused अक्षर codes on the symbols and
 *  maps these to the most used substrings (tokens). For instance, it might
 *  map अक्षर code 0xF7 to represent "write_" and then in every symbol where
 *  "write_" appears it can be replaced by 0xF7, saving 5 bytes.
 *      The used codes themselves are also placed in the table so that the
 *  decompresion can work without "special cases".
 *      Applied to kernel symbols, this usually produces a compression ratio
 *  of about 50%.
 *
 */

#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <सीमा.स>

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप(arr[0]))

#घोषणा KSYM_NAME_LEN		128

काष्ठा sym_entry अणु
	अचिन्हित दीर्घ दीर्घ addr;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक start_pos;
	अचिन्हित पूर्णांक percpu_असलolute;
	अचिन्हित अक्षर sym[];
पूर्ण;

काष्ठा addr_range अणु
	स्थिर अक्षर *start_sym, *end_sym;
	अचिन्हित दीर्घ दीर्घ start, end;
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ _text;
अटल अचिन्हित दीर्घ दीर्घ relative_base;
अटल काष्ठा addr_range text_ranges[] = अणु
	अणु "_stext",     "_etext"     पूर्ण,
	अणु "_sinittext", "_einittext" पूर्ण,
पूर्ण;
#घोषणा text_range_text     (&text_ranges[0])
#घोषणा text_range_inittext (&text_ranges[1])

अटल काष्ठा addr_range percpu_range = अणु
	"__per_cpu_start", "__per_cpu_end", -1ULL, 0
पूर्ण;

अटल काष्ठा sym_entry **table;
अटल अचिन्हित पूर्णांक table_size, table_cnt;
अटल पूर्णांक all_symbols;
अटल पूर्णांक असलolute_percpu;
अटल पूर्णांक base_relative;

अटल पूर्णांक token_profit[0x10000];

/* the table that holds the result of the compression */
अटल अचिन्हित अक्षर best_table[256][2];
अटल अचिन्हित अक्षर best_table_len[256];


अटल व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: kallsyms [--all-symbols] "
			"[--base-relative] < in.map > out.S\n");
	निकास(1);
पूर्ण

अटल अक्षर *sym_name(स्थिर काष्ठा sym_entry *s)
अणु
	वापस (अक्षर *)s->sym + 1;
पूर्ण

अटल bool is_ignored_symbol(स्थिर अक्षर *name, अक्षर type)
अणु
	/* Symbol names that exactly match to the following are ignored.*/
	अटल स्थिर अक्षर * स्थिर ignored_symbols[] = अणु
		/*
		 * Symbols which vary between passes. Passes 1 and 2 must have
		 * identical symbol lists. The kallsyms_* symbols below are
		 * only added after pass 1, they would be included in pass 2
		 * when --all-symbols is specअगरied so exclude them to get a
		 * stable symbol list.
		 */
		"kallsyms_addresses",
		"kallsyms_offsets",
		"kallsyms_relative_base",
		"kallsyms_num_syms",
		"kallsyms_names",
		"kallsyms_markers",
		"kallsyms_token_table",
		"kallsyms_token_index",
		/* Exclude linker generated symbols which vary between passes */
		"_SDA_BASE_",		/* ppc */
		"_SDA2_BASE_",		/* ppc */
		शून्य
	पूर्ण;

	/* Symbol names that begin with the following are ignored.*/
	अटल स्थिर अक्षर * स्थिर ignored_prefixes[] = अणु
		"$",			/* local symbols क्रम ARM, MIPS, etc. */
		".LASANPC",		/* s390 kasan local symbols */
		"__crc_",		/* modversions */
		"__efistub_",		/* arm64 EFI stub namespace */
		"__kvm_nvhe_",		/* arm64 non-VHE KVM namespace */
		"__AArch64ADRPThunk_",	/* arm64 lld */
		"__ARMV5PILongThunk_",	/* arm lld */
		"__ARMV7PILongThunk_",
		"__ThumbV7PILongThunk_",
		"__LA25Thunk_",		/* mips lld */
		"__microLA25Thunk_",
		शून्य
	पूर्ण;

	/* Symbol names that end with the following are ignored.*/
	अटल स्थिर अक्षर * स्थिर ignored_suffixes[] = अणु
		"_from_arm",		/* arm */
		"_from_thumb",		/* arm */
		"_veneer",		/* arm */
		शून्य
	पूर्ण;

	/* Symbol names that contain the following are ignored.*/
	अटल स्थिर अक्षर * स्थिर ignored_matches[] = अणु
		".long_branch.",	/* ppc stub */
		".plt_branch.",		/* ppc stub */
		शून्य
	पूर्ण;

	स्थिर अक्षर * स्थिर *p;

	क्रम (p = ignored_symbols; *p; p++)
		अगर (!म_भेद(name, *p))
			वापस true;

	क्रम (p = ignored_prefixes; *p; p++)
		अगर (!म_भेदन(name, *p, म_माप(*p)))
			वापस true;

	क्रम (p = ignored_suffixes; *p; p++) अणु
		पूर्णांक l = म_माप(name) - म_माप(*p);

		अगर (l >= 0 && !म_भेद(name + l, *p))
			वापस true;
	पूर्ण

	क्रम (p = ignored_matches; *p; p++) अणु
		अगर (म_माला(name, *p))
			वापस true;
	पूर्ण

	अगर (type == 'U' || type == 'u')
		वापस true;
	/* exclude debugging symbols */
	अगर (type == 'N' || type == 'n')
		वापस true;

	अगर (बड़े(type) == 'A') अणु
		/* Keep these useful असलolute symbols */
		अगर (म_भेद(name, "__kernel_syscall_via_break") &&
		    म_भेद(name, "__kernel_syscall_via_epc") &&
		    म_भेद(name, "__kernel_sigtramp") &&
		    म_भेद(name, "__gp"))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम check_symbol_range(स्थिर अक्षर *sym, अचिन्हित दीर्घ दीर्घ addr,
			       काष्ठा addr_range *ranges, पूर्णांक entries)
अणु
	माप_प्रकार i;
	काष्ठा addr_range *ar;

	क्रम (i = 0; i < entries; ++i) अणु
		ar = &ranges[i];

		अगर (म_भेद(sym, ar->start_sym) == 0) अणु
			ar->start = addr;
			वापस;
		पूर्ण अन्यथा अगर (म_भेद(sym, ar->end_sym) == 0) अणु
			ar->end = addr;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा sym_entry *पढ़ो_symbol(खाता *in)
अणु
	अक्षर name[500], type;
	अचिन्हित दीर्घ दीर्घ addr;
	अचिन्हित पूर्णांक len;
	काष्ठा sym_entry *sym;
	पूर्णांक rc;

	rc = ख_पूछो(in, "%llx %c %499s\n", &addr, &type, name);
	अगर (rc != 3) अणु
		अगर (rc != खातापूर्ण && ख_माला_लो(name, 500, in) == शून्य)
			ख_लिखो(मानक_त्रुटि, "Read error or end of file.\n");
		वापस शून्य;
	पूर्ण
	अगर (म_माप(name) >= KSYM_NAME_LEN) अणु
		ख_लिखो(मानक_त्रुटि, "Symbol %s too long for kallsyms (%zu >= %d).\n"
				"Please increase KSYM_NAME_LEN both in kernel and kallsyms.c\n",
			name, म_माप(name), KSYM_NAME_LEN);
		वापस शून्य;
	पूर्ण

	अगर (म_भेद(name, "_text") == 0)
		_text = addr;

	/* Ignore most असलolute/undefined (?) symbols. */
	अगर (is_ignored_symbol(name, type))
		वापस शून्य;

	check_symbol_range(name, addr, text_ranges, ARRAY_SIZE(text_ranges));
	check_symbol_range(name, addr, &percpu_range, 1);

	/* include the type field in the symbol name, so that it माला_लो
	 * compressed together */

	len = म_माप(name) + 1;

	sym = दो_स्मृति(माप(*sym) + len + 1);
	अगर (!sym) अणु
		ख_लिखो(मानक_त्रुटि, "kallsyms failure: "
			"unable to allocate required amount of memory\n");
		निकास(निकास_त्रुटि);
	पूर्ण
	sym->addr = addr;
	sym->len = len;
	sym->sym[0] = type;
	म_नकल(sym_name(sym), name);
	sym->percpu_असलolute = 0;

	वापस sym;
पूर्ण

अटल पूर्णांक symbol_in_range(स्थिर काष्ठा sym_entry *s,
			   स्थिर काष्ठा addr_range *ranges, पूर्णांक entries)
अणु
	माप_प्रकार i;
	स्थिर काष्ठा addr_range *ar;

	क्रम (i = 0; i < entries; ++i) अणु
		ar = &ranges[i];

		अगर (s->addr >= ar->start && s->addr <= ar->end)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक symbol_valid(स्थिर काष्ठा sym_entry *s)
अणु
	स्थिर अक्षर *name = sym_name(s);

	/* अगर --all-symbols is not specअगरied, then symbols outside the text
	 * and inittext sections are discarded */
	अगर (!all_symbols) अणु
		अगर (symbol_in_range(s, text_ranges,
				    ARRAY_SIZE(text_ranges)) == 0)
			वापस 0;
		/* Corner हाल.  Discard any symbols with the same value as
		 * _etext _einittext; they can move between pass 1 and 2 when
		 * the kallsyms data are added.  If these symbols move then
		 * they may get dropped in pass 2, which अवरोधs the kallsyms
		 * rules.
		 */
		अगर ((s->addr == text_range_text->end &&
		     म_भेद(name, text_range_text->end_sym)) ||
		    (s->addr == text_range_inittext->end &&
		     म_भेद(name, text_range_inittext->end_sym)))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* हटाओ all the invalid symbols from the table */
अटल व्योम shrink_table(व्योम)
अणु
	अचिन्हित पूर्णांक i, pos;

	pos = 0;
	क्रम (i = 0; i < table_cnt; i++) अणु
		अगर (symbol_valid(table[i])) अणु
			अगर (pos != i)
				table[pos] = table[i];
			pos++;
		पूर्ण अन्यथा अणु
			मुक्त(table[i]);
		पूर्ण
	पूर्ण
	table_cnt = pos;

	/* When valid symbol is not रेजिस्टरed, निकास to error */
	अगर (!table_cnt) अणु
		ख_लिखो(मानक_त्रुटि, "No valid symbol.\n");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_map(खाता *in)
अणु
	काष्ठा sym_entry *sym;

	जबतक (!ख_पूर्ण(in)) अणु
		sym = पढ़ो_symbol(in);
		अगर (!sym)
			जारी;

		sym->start_pos = table_cnt;

		अगर (table_cnt >= table_size) अणु
			table_size += 10000;
			table = पुनः_स्मृति(table, माप(*table) * table_size);
			अगर (!table) अणु
				ख_लिखो(मानक_त्रुटि, "out of memory\n");
				निकास (1);
			पूर्ण
		पूर्ण

		table[table_cnt++] = sym;
	पूर्ण
पूर्ण

अटल व्योम output_label(स्थिर अक्षर *label)
अणु
	म_लिखो(".globl %s\n", label);
	म_लिखो("\tALGN\n");
	म_लिखो("%s:\n", label);
पूर्ण

/* Provide proper symbols relocatability by their '_text' relativeness. */
अटल व्योम output_address(अचिन्हित दीर्घ दीर्घ addr)
अणु
	अगर (_text <= addr)
		म_लिखो("\tPTR\t_text + %#llx\n", addr - _text);
	अन्यथा
		म_लिखो("\tPTR\t_text - %#llx\n", _text - addr);
पूर्ण

/* uncompress a compressed symbol. When this function is called, the best table
 * might still be compressed itself, so the function needs to be recursive */
अटल पूर्णांक expand_symbol(स्थिर अचिन्हित अक्षर *data, पूर्णांक len, अक्षर *result)
अणु
	पूर्णांक c, rlen, total=0;

	जबतक (len) अणु
		c = *data;
		/* अगर the table holds a single अक्षर that is the same as the one
		 * we are looking क्रम, then end the search */
		अगर (best_table[c][0]==c && best_table_len[c]==1) अणु
			*result++ = c;
			total++;
		पूर्ण अन्यथा अणु
			/* अगर not, recurse and expand */
			rlen = expand_symbol(best_table[c], best_table_len[c], result);
			total += rlen;
			result += rlen;
		पूर्ण
		data++;
		len--;
	पूर्ण
	*result=0;

	वापस total;
पूर्ण

अटल पूर्णांक symbol_असलolute(स्थिर काष्ठा sym_entry *s)
अणु
	वापस s->percpu_असलolute;
पूर्ण

अटल व्योम ग_लिखो_src(व्योम)
अणु
	अचिन्हित पूर्णांक i, k, off;
	अचिन्हित पूर्णांक best_idx[256];
	अचिन्हित पूर्णांक *markers;
	अक्षर buf[KSYM_NAME_LEN];

	म_लिखो("#include <asm/bitsperlong.h>\n");
	म_लिखो("#if BITS_PER_LONG == 64\n");
	म_लिखो("#define PTR .quad\n");
	म_लिखो("#define ALGN .balign 8\n");
	म_लिखो("#else\n");
	म_लिखो("#define PTR .long\n");
	म_लिखो("#define ALGN .balign 4\n");
	म_लिखो("#endif\n");

	म_लिखो("\t.section .rodata, \"a\"\n");

	अगर (!base_relative)
		output_label("kallsyms_addresses");
	अन्यथा
		output_label("kallsyms_offsets");

	क्रम (i = 0; i < table_cnt; i++) अणु
		अगर (base_relative) अणु
			/*
			 * Use the offset relative to the lowest value
			 * encountered of all relative symbols, and emit
			 * non-relocatable fixed offsets that will be fixed
			 * up at runसमय.
			 */

			दीर्घ दीर्घ offset;
			पूर्णांक overflow;

			अगर (!असलolute_percpu) अणु
				offset = table[i]->addr - relative_base;
				overflow = (offset < 0 || offset > अच_पूर्णांक_उच्च);
			पूर्ण अन्यथा अगर (symbol_असलolute(table[i])) अणु
				offset = table[i]->addr;
				overflow = (offset < 0 || offset > पूर्णांक_उच्च);
			पूर्ण अन्यथा अणु
				offset = relative_base - table[i]->addr - 1;
				overflow = (offset < पूर्णांक_न्यून || offset >= 0);
			पूर्ण
			अगर (overflow) अणु
				ख_लिखो(मानक_त्रुटि, "kallsyms failure: "
					"%s symbol value %#llx out of range in relative mode\n",
					symbol_असलolute(table[i]) ? "absolute" : "relative",
					table[i]->addr);
				निकास(निकास_त्रुटि);
			पूर्ण
			म_लिखो("\t.long\t%#x\n", (पूर्णांक)offset);
		पूर्ण अन्यथा अगर (!symbol_असलolute(table[i])) अणु
			output_address(table[i]->addr);
		पूर्ण अन्यथा अणु
			म_लिखो("\tPTR\t%#llx\n", table[i]->addr);
		पूर्ण
	पूर्ण
	म_लिखो("\n");

	अगर (base_relative) अणु
		output_label("kallsyms_relative_base");
		output_address(relative_base);
		म_लिखो("\n");
	पूर्ण

	output_label("kallsyms_num_syms");
	म_लिखो("\t.long\t%u\n", table_cnt);
	म_लिखो("\n");

	/* table of offset markers, that give the offset in the compressed stream
	 * every 256 symbols */
	markers = दो_स्मृति(माप(अचिन्हित पूर्णांक) * ((table_cnt + 255) / 256));
	अगर (!markers) अणु
		ख_लिखो(मानक_त्रुटि, "kallsyms failure: "
			"unable to allocate required memory\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	output_label("kallsyms_names");
	off = 0;
	क्रम (i = 0; i < table_cnt; i++) अणु
		अगर ((i & 0xFF) == 0)
			markers[i >> 8] = off;

		म_लिखो("\t.byte 0x%02x", table[i]->len);
		क्रम (k = 0; k < table[i]->len; k++)
			म_लिखो(", 0x%02x", table[i]->sym[k]);
		म_लिखो("\n");

		off += table[i]->len + 1;
	पूर्ण
	म_लिखो("\n");

	output_label("kallsyms_markers");
	क्रम (i = 0; i < ((table_cnt + 255) >> 8); i++)
		म_लिखो("\t.long\t%u\n", markers[i]);
	म_लिखो("\n");

	मुक्त(markers);

	output_label("kallsyms_token_table");
	off = 0;
	क्रम (i = 0; i < 256; i++) अणु
		best_idx[i] = off;
		expand_symbol(best_table[i], best_table_len[i], buf);
		म_लिखो("\t.asciz\t\"%s\"\n", buf);
		off += म_माप(buf) + 1;
	पूर्ण
	म_लिखो("\n");

	output_label("kallsyms_token_index");
	क्रम (i = 0; i < 256; i++)
		म_लिखो("\t.short\t%d\n", best_idx[i]);
	म_लिखो("\n");
पूर्ण


/* table lookup compression functions */

/* count all the possible tokens in a symbol */
अटल व्योम learn_symbol(स्थिर अचिन्हित अक्षर *symbol, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len - 1; i++)
		token_profit[ symbol[i] + (symbol[i + 1] << 8) ]++;
पूर्ण

/* decrease the count क्रम all the possible tokens in a symbol */
अटल व्योम क्रमget_symbol(स्थिर अचिन्हित अक्षर *symbol, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len - 1; i++)
		token_profit[ symbol[i] + (symbol[i + 1] << 8) ]--;
पूर्ण

/* करो the initial token count */
अटल व्योम build_initial_tok_table(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table_cnt; i++)
		learn_symbol(table[i]->sym, table[i]->len);
पूर्ण

अटल अचिन्हित अक्षर *find_token(अचिन्हित अक्षर *str, पूर्णांक len,
				 स्थिर अचिन्हित अक्षर *token)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len - 1; i++) अणु
		अगर (str[i] == token[0] && str[i+1] == token[1])
			वापस &str[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/* replace a given token in all the valid symbols. Use the sampled symbols
 * to update the counts */
अटल व्योम compress_symbols(स्थिर अचिन्हित अक्षर *str, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक i, len, size;
	अचिन्हित अक्षर *p1, *p2;

	क्रम (i = 0; i < table_cnt; i++) अणु

		len = table[i]->len;
		p1 = table[i]->sym;

		/* find the token on the symbol */
		p2 = find_token(p1, len, str);
		अगर (!p2) जारी;

		/* decrease the counts क्रम this symbol's tokens */
		क्रमget_symbol(table[i]->sym, len);

		size = len;

		करो अणु
			*p2 = idx;
			p2++;
			size -= (p2 - p1);
			स_हटाओ(p2, p2 + 1, size);
			p1 = p2;
			len--;

			अगर (size < 2) अवरोध;

			/* find the token on the symbol */
			p2 = find_token(p1, size, str);

		पूर्ण जबतक (p2);

		table[i]->len = len;

		/* increase the counts क्रम this symbol's new tokens */
		learn_symbol(table[i]->sym, len);
	पूर्ण
पूर्ण

/* search the token with the maximum profit */
अटल पूर्णांक find_best_token(व्योम)
अणु
	पूर्णांक i, best, bestprofit;

	bestprofit=-10000;
	best = 0;

	क्रम (i = 0; i < 0x10000; i++) अणु
		अगर (token_profit[i] > bestprofit) अणु
			best = i;
			bestprofit = token_profit[i];
		पूर्ण
	पूर्ण
	वापस best;
पूर्ण

/* this is the core of the algorithm: calculate the "best" table */
अटल व्योम optimize_result(व्योम)
अणु
	पूर्णांक i, best;

	/* using the '\0' symbol last allows compress_symbols to use standard
	 * fast string functions */
	क्रम (i = 255; i >= 0; i--) अणु

		/* अगर this table slot is empty (it is not used by an actual
		 * original अक्षर code */
		अगर (!best_table_len[i]) अणु

			/* find the token with the best profit value */
			best = find_best_token();
			अगर (token_profit[best] == 0)
				अवरोध;

			/* place it in the "best" table */
			best_table_len[i] = 2;
			best_table[i][0] = best & 0xFF;
			best_table[i][1] = (best >> 8) & 0xFF;

			/* replace this token in all the valid symbols */
			compress_symbols(best_table[i], i);
		पूर्ण
	पूर्ण
पूर्ण

/* start by placing the symbols that are actually used on the table */
अटल व्योम insert_real_symbols_in_table(व्योम)
अणु
	अचिन्हित पूर्णांक i, j, c;

	क्रम (i = 0; i < table_cnt; i++) अणु
		क्रम (j = 0; j < table[i]->len; j++) अणु
			c = table[i]->sym[j];
			best_table[c][0]=c;
			best_table_len[c]=1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम optimize_token_table(व्योम)
अणु
	build_initial_tok_table();

	insert_real_symbols_in_table();

	optimize_result();
पूर्ण

/* guess क्रम "linker script provide" symbol */
अटल पूर्णांक may_be_linker_script_provide_symbol(स्थिर काष्ठा sym_entry *se)
अणु
	स्थिर अक्षर *symbol = sym_name(se);
	पूर्णांक len = se->len - 1;

	अगर (len < 8)
		वापस 0;

	अगर (symbol[0] != '_' || symbol[1] != '_')
		वापस 0;

	/* __start_XXXXX */
	अगर (!स_भेद(symbol + 2, "start_", 6))
		वापस 1;

	/* __stop_XXXXX */
	अगर (!स_भेद(symbol + 2, "stop_", 5))
		वापस 1;

	/* __end_XXXXX */
	अगर (!स_भेद(symbol + 2, "end_", 4))
		वापस 1;

	/* __XXXXX_start */
	अगर (!स_भेद(symbol + len - 6, "_start", 6))
		वापस 1;

	/* __XXXXX_end */
	अगर (!स_भेद(symbol + len - 4, "_end", 4))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक compare_symbols(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा sym_entry *sa = *(स्थिर काष्ठा sym_entry **)a;
	स्थिर काष्ठा sym_entry *sb = *(स्थिर काष्ठा sym_entry **)b;
	पूर्णांक wa, wb;

	/* sort by address first */
	अगर (sa->addr > sb->addr)
		वापस 1;
	अगर (sa->addr < sb->addr)
		वापस -1;

	/* sort by "weakness" type */
	wa = (sa->sym[0] == 'w') || (sa->sym[0] == 'W');
	wb = (sb->sym[0] == 'w') || (sb->sym[0] == 'W');
	अगर (wa != wb)
		वापस wa - wb;

	/* sort by "linker script provide" type */
	wa = may_be_linker_script_provide_symbol(sa);
	wb = may_be_linker_script_provide_symbol(sb);
	अगर (wa != wb)
		वापस wa - wb;

	/* sort by the number of prefix underscores */
	wa = म_अखोज(sym_name(sa), "_");
	wb = म_अखोज(sym_name(sb), "_");
	अगर (wa != wb)
		वापस wa - wb;

	/* sort by initial order, so that other symbols are left undisturbed */
	वापस sa->start_pos - sb->start_pos;
पूर्ण

अटल व्योम sort_symbols(व्योम)
अणु
	क्विक(table, table_cnt, माप(table[0]), compare_symbols);
पूर्ण

अटल व्योम make_percpus_असलolute(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table_cnt; i++)
		अगर (symbol_in_range(table[i], &percpu_range, 1)) अणु
			/*
			 * Keep the 'A' override क्रम percpu symbols to
			 * ensure consistent behavior compared to older
			 * versions of this tool.
			 */
			table[i]->sym[0] = 'A';
			table[i]->percpu_असलolute = 1;
		पूर्ण
पूर्ण

/* find the minimum non-असलolute symbol address */
अटल व्योम record_relative_base(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table_cnt; i++)
		अगर (!symbol_असलolute(table[i])) अणु
			/*
			 * The table is sorted by address.
			 * Take the first non-असलolute symbol value.
			 */
			relative_base = table[i]->addr;
			वापस;
		पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (argc >= 2) अणु
		पूर्णांक i;
		क्रम (i = 1; i < argc; i++) अणु
			अगर(म_भेद(argv[i], "--all-symbols") == 0)
				all_symbols = 1;
			अन्यथा अगर (म_भेद(argv[i], "--absolute-percpu") == 0)
				असलolute_percpu = 1;
			अन्यथा अगर (म_भेद(argv[i], "--base-relative") == 0)
				base_relative = 1;
			अन्यथा
				usage();
		पूर्ण
	पूर्ण अन्यथा अगर (argc != 1)
		usage();

	पढ़ो_map(मानक_निवेश);
	shrink_table();
	अगर (असलolute_percpu)
		make_percpus_असलolute();
	sort_symbols();
	अगर (base_relative)
		record_relative_base();
	optimize_token_table();
	ग_लिखो_src();

	वापस 0;
पूर्ण
