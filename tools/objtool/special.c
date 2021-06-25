<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */

/*
 * This file पढ़ोs all the special sections which have alternate inकाष्ठाions
 * which can be patched in or redirected to at runसमय.
 */

#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <arch/special.h>
#समावेश <objtool/builtin.h>
#समावेश <objtool/special.h>
#समावेश <objtool/warn.h>
#समावेश <objtool/endianness.h>

काष्ठा special_entry अणु
	स्थिर अक्षर *sec;
	bool group, jump_or_nop;
	अचिन्हित अक्षर size, orig, new;
	अचिन्हित अक्षर orig_len, new_len; /* group only */
	अचिन्हित अक्षर feature; /* ALTERNATIVE macro CPU feature */
पूर्ण;

काष्ठा special_entry entries[] = अणु
	अणु
		.sec = ".altinstructions",
		.group = true,
		.size = ALT_ENTRY_SIZE,
		.orig = ALT_ORIG_OFFSET,
		.orig_len = ALT_ORIG_LEN_OFFSET,
		.new = ALT_NEW_OFFSET,
		.new_len = ALT_NEW_LEN_OFFSET,
		.feature = ALT_FEATURE_OFFSET,
	पूर्ण,
	अणु
		.sec = "__jump_table",
		.jump_or_nop = true,
		.size = JUMP_ENTRY_SIZE,
		.orig = JUMP_ORIG_OFFSET,
		.new = JUMP_NEW_OFFSET,
	पूर्ण,
	अणु
		.sec = "__ex_table",
		.size = EX_ENTRY_SIZE,
		.orig = EX_ORIG_OFFSET,
		.new = EX_NEW_OFFSET,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

व्योम __weak arch_handle_alternative(अचिन्हित लघु feature, काष्ठा special_alt *alt)
अणु
पूर्ण

अटल पूर्णांक get_alt_entry(काष्ठा elf *elf, काष्ठा special_entry *entry,
			 काष्ठा section *sec, पूर्णांक idx,
			 काष्ठा special_alt *alt)
अणु
	काष्ठा reloc *orig_reloc, *new_reloc;
	अचिन्हित दीर्घ offset;

	offset = idx * entry->size;

	alt->group = entry->group;
	alt->jump_or_nop = entry->jump_or_nop;

	अगर (alt->group) अणु
		alt->orig_len = *(अचिन्हित अक्षर *)(sec->data->d_buf + offset +
						   entry->orig_len);
		alt->new_len = *(अचिन्हित अक्षर *)(sec->data->d_buf + offset +
						  entry->new_len);
	पूर्ण

	अगर (entry->feature) अणु
		अचिन्हित लघु feature;

		feature = bswap_अगर_needed(*(अचिन्हित लघु *)(sec->data->d_buf +
							      offset +
							      entry->feature));
		arch_handle_alternative(feature, alt);
	पूर्ण

	orig_reloc = find_reloc_by_dest(elf, sec, offset + entry->orig);
	अगर (!orig_reloc) अणु
		WARN_FUNC("can't find orig reloc", sec, offset + entry->orig);
		वापस -1;
	पूर्ण
	अगर (orig_reloc->sym->type != STT_SECTION) अणु
		WARN_FUNC("don't know how to handle non-section reloc symbol %s",
			   sec, offset + entry->orig, orig_reloc->sym->name);
		वापस -1;
	पूर्ण

	alt->orig_sec = orig_reloc->sym->sec;
	alt->orig_off = orig_reloc->addend;

	अगर (!entry->group || alt->new_len) अणु
		new_reloc = find_reloc_by_dest(elf, sec, offset + entry->new);
		अगर (!new_reloc) अणु
			WARN_FUNC("can't find new reloc",
				  sec, offset + entry->new);
			वापस -1;
		पूर्ण

		/*
		 * Skip retpoline .altinstr_replacement... we alपढ़ोy reग_लिखो the
		 * inकाष्ठाions क्रम retpolines anyway, see arch_is_retpoline()
		 * usage in add_अणुcall,jumpपूर्ण_destinations().
		 */
		अगर (arch_is_retpoline(new_reloc->sym))
			वापस 1;

		alt->new_sec = new_reloc->sym->sec;
		alt->new_off = (अचिन्हित पूर्णांक)new_reloc->addend;

		/* _ASM_EXTABLE_EX hack */
		अगर (alt->new_off >= 0x7ffffff0)
			alt->new_off -= 0x7ffffff0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Read all the special sections and create a list of special_alt काष्ठाs which
 * describe all the alternate inकाष्ठाions which can be patched in or
 * redirected to at runसमय.
 */
पूर्णांक special_get_alts(काष्ठा elf *elf, काष्ठा list_head *alts)
अणु
	काष्ठा special_entry *entry;
	काष्ठा section *sec;
	अचिन्हित पूर्णांक nr_entries;
	काष्ठा special_alt *alt;
	पूर्णांक idx, ret;

	INIT_LIST_HEAD(alts);

	क्रम (entry = entries; entry->sec; entry++) अणु
		sec = find_section_by_name(elf, entry->sec);
		अगर (!sec)
			जारी;

		अगर (sec->len % entry->size != 0) अणु
			WARN("%s size not a multiple of %d",
			     sec->name, entry->size);
			वापस -1;
		पूर्ण

		nr_entries = sec->len / entry->size;

		क्रम (idx = 0; idx < nr_entries; idx++) अणु
			alt = दो_स्मृति(माप(*alt));
			अगर (!alt) अणु
				WARN("malloc failed");
				वापस -1;
			पूर्ण
			स_रखो(alt, 0, माप(*alt));

			ret = get_alt_entry(elf, entry, sec, idx, alt);
			अगर (ret > 0)
				जारी;
			अगर (ret < 0)
				वापस ret;

			list_add_tail(&alt->list, alts);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
