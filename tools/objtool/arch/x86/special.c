<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#समावेश <माला.स>

#समावेश <objtool/special.h>
#समावेश <objtool/builtin.h>

#घोषणा X86_FEATURE_POPCNT (4 * 32 + 23)
#घोषणा X86_FEATURE_SMAP   (9 * 32 + 20)

व्योम arch_handle_alternative(अचिन्हित लघु feature, काष्ठा special_alt *alt)
अणु
	चयन (feature) अणु
	हाल X86_FEATURE_SMAP:
		/*
		 * If UACCESS validation is enabled; क्रमce that alternative;
		 * otherwise क्रमce it the other way.
		 *
		 * What we want to aव्योम is having both the original and the
		 * alternative code flow at the same समय, in that हाल we can
		 * find paths that see the STAC but take the NOP instead of
		 * CLAC and the other way around.
		 */
		अगर (uaccess)
			alt->skip_orig = true;
		अन्यथा
			alt->skip_alt = true;
		अवरोध;
	हाल X86_FEATURE_POPCNT:
		/*
		 * It has been requested that we करोn't validate the !POPCNT
		 * feature path which is a "very very small percentage of
		 * machines".
		 */
		alt->skip_orig = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

bool arch_support_alt_relocation(काष्ठा special_alt *special_alt,
				 काष्ठा inकाष्ठाion *insn,
				 काष्ठा reloc *reloc)
अणु
	/*
	 * The x86 alternatives code adjusts the offsets only when it
	 * encounters a branch inकाष्ठाion at the very beginning of the
	 * replacement group.
	 */
	वापस insn->offset == special_alt->new_off &&
	       (insn->type == INSN_CALL || is_jump(insn));
पूर्ण

/*
 * There are 3 basic jump table patterns:
 *
 * 1. jmpq *[rodata addr](,%reg,8)
 *
 *    This is the most common हाल by far.  It jumps to an address in a simple
 *    jump table which is stored in .rodata.
 *
 * 2. jmpq *[rodata addr](%rip)
 *
 *    This is caused by a rare GCC quirk, currently only seen in three driver
 *    functions in the kernel, only with certain obscure non-distro configs.
 *
 *    As part of an optimization, GCC makes a copy of an existing चयन jump
 *    table, modअगरies it, and then hard-codes the jump (albeit with an indirect
 *    jump) to use a single entry in the table.  The rest of the jump table and
 *    some of its jump tarमाला_लो reमुख्य as dead code.
 *
 *    In such a हाल we can just crudely ignore all unreachable inकाष्ठाion
 *    warnings क्रम the entire object file.  Ideally we would just ignore them
 *    क्रम the function, but that would require redesigning the code quite a
 *    bit.  And honestly that's just not worth करोing: unreachable inकाष्ठाion
 *    warnings are of questionable value anyway, and this is such a rare issue.
 *
 * 3. mov [rodata addr],%reg1
 *    ... some inकाष्ठाions ...
 *    jmpq *(%reg1,%reg2,8)
 *
 *    This is a fairly uncommon pattern which is new क्रम GCC 6.  As of this
 *    writing, there are 11 occurrences of it in the allmodconfig kernel.
 *
 *    As of GCC 7 there are quite a few more of these and the 'in between' code
 *    is signअगरicant. Esp. with KASAN enabled some of the code between the mov
 *    and jmpq uses .rodata itself, which can confuse things.
 *
 *    TODO: Once we have DWARF CFI and smarter inकाष्ठाion decoding logic,
 *    ensure the same रेजिस्टर is used in the mov and jump inकाष्ठाions.
 *
 *    NOTE: RETPOLINE made it harder still to decode dynamic jumps.
 */
काष्ठा reloc *arch_find_चयन_table(काष्ठा objtool_file *file,
				    काष्ठा inकाष्ठाion *insn)
अणु
	काष्ठा reloc  *text_reloc, *rodata_reloc;
	काष्ठा section *table_sec;
	अचिन्हित दीर्घ table_offset;

	/* look क्रम a relocation which references .rodata */
	text_reloc = find_reloc_by_dest_range(file->elf, insn->sec,
					      insn->offset, insn->len);
	अगर (!text_reloc || text_reloc->sym->type != STT_SECTION ||
	    !text_reloc->sym->sec->rodata)
		वापस शून्य;

	table_offset = text_reloc->addend;
	table_sec = text_reloc->sym->sec;

	अगर (text_reloc->type == R_X86_64_PC32)
		table_offset += 4;

	/*
	 * Make sure the .rodata address isn't associated with a
	 * symbol.  GCC jump tables are anonymous data.
	 *
	 * Also support C jump tables which are in the same क्रमmat as
	 * चयन jump tables.  For objtool to recognize them, they
	 * need to be placed in the C_JUMP_TABLE_SECTION section.  They
	 * have symbols associated with them.
	 */
	अगर (find_symbol_containing(table_sec, table_offset) &&
	    म_भेद(table_sec->name, C_JUMP_TABLE_SECTION))
		वापस शून्य;

	/*
	 * Each table entry has a rela associated with it.  The rela
	 * should reference text in the same function as the original
	 * inकाष्ठाion.
	 */
	rodata_reloc = find_reloc_by_dest(file->elf, table_sec, table_offset);
	अगर (!rodata_reloc)
		वापस शून्य;

	/*
	 * Use of RIP-relative चयन jumps is quite rare, and
	 * indicates a rare GCC quirk/bug which can leave dead
	 * code behind.
	 */
	अगर (text_reloc->type == R_X86_64_PC32)
		file->ignore_unreachables = true;

	वापस rodata_reloc;
पूर्ण
