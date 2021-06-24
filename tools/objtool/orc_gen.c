<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <linux/objtool.h>
#समावेश <यंत्र/orc_types.h>

#समावेश <objtool/check.h>
#समावेश <objtool/warn.h>
#समावेश <objtool/endianness.h>

अटल पूर्णांक init_orc_entry(काष्ठा orc_entry *orc, काष्ठा cfi_state *cfi)
अणु
	काष्ठा inकाष्ठाion *insn = container_of(cfi, काष्ठा inकाष्ठाion, cfi);
	काष्ठा cfi_reg *bp = &cfi->regs[CFI_BP];

	स_रखो(orc, 0, माप(*orc));

	orc->end = cfi->end;

	अगर (cfi->cfa.base == CFI_UNDEFINED) अणु
		orc->sp_reg = ORC_REG_UNDEFINED;
		वापस 0;
	पूर्ण

	चयन (cfi->cfa.base) अणु
	हाल CFI_SP:
		orc->sp_reg = ORC_REG_SP;
		अवरोध;
	हाल CFI_SP_INसूचीECT:
		orc->sp_reg = ORC_REG_SP_INसूचीECT;
		अवरोध;
	हाल CFI_BP:
		orc->sp_reg = ORC_REG_BP;
		अवरोध;
	हाल CFI_BP_INसूचीECT:
		orc->sp_reg = ORC_REG_BP_INसूचीECT;
		अवरोध;
	हाल CFI_R10:
		orc->sp_reg = ORC_REG_R10;
		अवरोध;
	हाल CFI_R13:
		orc->sp_reg = ORC_REG_R13;
		अवरोध;
	हाल CFI_DI:
		orc->sp_reg = ORC_REG_DI;
		अवरोध;
	हाल CFI_DX:
		orc->sp_reg = ORC_REG_DX;
		अवरोध;
	शेष:
		WARN_FUNC("unknown CFA base reg %d",
			  insn->sec, insn->offset, cfi->cfa.base);
		वापस -1;
	पूर्ण

	चयन (bp->base) अणु
	हाल CFI_UNDEFINED:
		orc->bp_reg = ORC_REG_UNDEFINED;
		अवरोध;
	हाल CFI_CFA:
		orc->bp_reg = ORC_REG_PREV_SP;
		अवरोध;
	हाल CFI_BP:
		orc->bp_reg = ORC_REG_BP;
		अवरोध;
	शेष:
		WARN_FUNC("unknown BP base reg %d",
			  insn->sec, insn->offset, bp->base);
		वापस -1;
	पूर्ण

	orc->sp_offset = cfi->cfa.offset;
	orc->bp_offset = bp->offset;
	orc->type = cfi->type;

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_orc_entry(काष्ठा elf *elf, काष्ठा section *orc_sec,
			   काष्ठा section *ip_sec, अचिन्हित पूर्णांक idx,
			   काष्ठा section *insn_sec, अचिन्हित दीर्घ insn_off,
			   काष्ठा orc_entry *o)
अणु
	काष्ठा orc_entry *orc;

	/* populate ORC data */
	orc = (काष्ठा orc_entry *)orc_sec->data->d_buf + idx;
	स_नकल(orc, o, माप(*orc));
	orc->sp_offset = bswap_अगर_needed(orc->sp_offset);
	orc->bp_offset = bswap_अगर_needed(orc->bp_offset);

	/* populate reloc क्रम ip */
	अगर (elf_add_reloc_to_insn(elf, ip_sec, idx * माप(पूर्णांक), R_X86_64_PC32,
				  insn_sec, insn_off))
		वापस -1;

	वापस 0;
पूर्ण

काष्ठा orc_list_entry अणु
	काष्ठा list_head list;
	काष्ठा orc_entry orc;
	काष्ठा section *insn_sec;
	अचिन्हित दीर्घ insn_off;
पूर्ण;

अटल पूर्णांक orc_list_add(काष्ठा list_head *orc_list, काष्ठा orc_entry *orc,
			काष्ठा section *sec, अचिन्हित दीर्घ offset)
अणु
	काष्ठा orc_list_entry *entry = दो_स्मृति(माप(*entry));

	अगर (!entry) अणु
		WARN("malloc failed");
		वापस -1;
	पूर्ण

	entry->orc	= *orc;
	entry->insn_sec = sec;
	entry->insn_off = offset;

	list_add_tail(&entry->list, orc_list);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ alt_group_len(काष्ठा alt_group *alt_group)
अणु
	वापस alt_group->last_insn->offset +
	       alt_group->last_insn->len -
	       alt_group->first_insn->offset;
पूर्ण

पूर्णांक orc_create(काष्ठा objtool_file *file)
अणु
	काष्ठा section *sec, *orc_sec;
	अचिन्हित पूर्णांक nr = 0, idx = 0;
	काष्ठा orc_list_entry *entry;
	काष्ठा list_head orc_list;

	काष्ठा orc_entry null = अणु
		.sp_reg  = ORC_REG_UNDEFINED,
		.bp_reg  = ORC_REG_UNDEFINED,
		.type    = UNWIND_HINT_TYPE_CALL,
	पूर्ण;

	/* Build a deduplicated list of ORC entries: */
	INIT_LIST_HEAD(&orc_list);
	क्रम_each_sec(file, sec) अणु
		काष्ठा orc_entry orc, prev_orc = अणु0पूर्ण;
		काष्ठा inकाष्ठाion *insn;
		bool empty = true;

		अगर (!sec->text)
			जारी;

		sec_क्रम_each_insn(file, sec, insn) अणु
			काष्ठा alt_group *alt_group = insn->alt_group;
			पूर्णांक i;

			अगर (!alt_group) अणु
				अगर (init_orc_entry(&orc, &insn->cfi))
					वापस -1;
				अगर (!स_भेद(&prev_orc, &orc, माप(orc)))
					जारी;
				अगर (orc_list_add(&orc_list, &orc, sec,
						 insn->offset))
					वापस -1;
				nr++;
				prev_orc = orc;
				empty = false;
				जारी;
			पूर्ण

			/*
			 * Alternatives can have dअगरferent stack layout
			 * possibilities (but they shouldn't conflict).
			 * Instead of traversing the inकाष्ठाions, use the
			 * alt_group's flattened byte-offset-addressed CFI
			 * array.
			 */
			क्रम (i = 0; i < alt_group_len(alt_group); i++) अणु
				काष्ठा cfi_state *cfi = alt_group->cfi[i];
				अगर (!cfi)
					जारी;
				अगर (init_orc_entry(&orc, cfi))
					वापस -1;
				अगर (!स_भेद(&prev_orc, &orc, माप(orc)))
					जारी;
				अगर (orc_list_add(&orc_list, &orc, insn->sec,
						 insn->offset + i))
					वापस -1;
				nr++;
				prev_orc = orc;
				empty = false;
			पूर्ण

			/* Skip to the end of the alt_group */
			insn = alt_group->last_insn;
		पूर्ण

		/* Add a section terminator */
		अगर (!empty) अणु
			orc_list_add(&orc_list, &null, sec, sec->len);
			nr++;
		पूर्ण
	पूर्ण
	अगर (!nr)
		वापस 0;

	/* Create .orc_unwind, .orc_unwind_ip and .rela.orc_unwind_ip sections: */
	sec = find_section_by_name(file->elf, ".orc_unwind");
	अगर (sec) अणु
		WARN("file already has .orc_unwind section, skipping");
		वापस -1;
	पूर्ण
	orc_sec = elf_create_section(file->elf, ".orc_unwind", 0,
				     माप(काष्ठा orc_entry), nr);
	अगर (!orc_sec)
		वापस -1;

	sec = elf_create_section(file->elf, ".orc_unwind_ip", 0, माप(पूर्णांक), nr);
	अगर (!sec)
		वापस -1;

	/* Write ORC entries to sections: */
	list_क्रम_each_entry(entry, &orc_list, list) अणु
		अगर (ग_लिखो_orc_entry(file->elf, orc_sec, sec, idx++,
				    entry->insn_sec, entry->insn_off,
				    &entry->orc))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
