<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#समावेश <unistd.h>
#समावेश <linux/objtool.h>
#समावेश <यंत्र/orc_types.h>
#समावेश <objtool/objtool.h>
#समावेश <objtool/warn.h>
#समावेश <objtool/endianness.h>

अटल स्थिर अक्षर *reg_name(अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ORC_REG_PREV_SP:
		वापस "prevsp";
	हाल ORC_REG_DX:
		वापस "dx";
	हाल ORC_REG_DI:
		वापस "di";
	हाल ORC_REG_BP:
		वापस "bp";
	हाल ORC_REG_SP:
		वापस "sp";
	हाल ORC_REG_R10:
		वापस "r10";
	हाल ORC_REG_R13:
		वापस "r13";
	हाल ORC_REG_BP_INसूचीECT:
		वापस "bp(ind)";
	हाल ORC_REG_SP_INसूचीECT:
		वापस "sp(ind)";
	शेष:
		वापस "?";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *orc_type_name(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल UNWIND_HINT_TYPE_CALL:
		वापस "call";
	हाल UNWIND_HINT_TYPE_REGS:
		वापस "regs";
	हाल UNWIND_HINT_TYPE_REGS_PARTIAL:
		वापस "regs (partial)";
	शेष:
		वापस "?";
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_reg(अचिन्हित पूर्णांक reg, पूर्णांक offset)
अणु
	अगर (reg == ORC_REG_BP_INसूचीECT)
		म_लिखो("(bp%+d)", offset);
	अन्यथा अगर (reg == ORC_REG_SP_INसूचीECT)
		म_लिखो("(sp)%+d", offset);
	अन्यथा अगर (reg == ORC_REG_UNDEFINED)
		म_लिखो("(und)");
	अन्यथा
		म_लिखो("%s%+d", reg_name(reg), offset);
पूर्ण

पूर्णांक orc_dump(स्थिर अक्षर *_objname)
अणु
	पूर्णांक fd, nr_entries, i, *orc_ip = शून्य, orc_size = 0;
	काष्ठा orc_entry *orc = शून्य;
	अक्षर *name;
	माप_प्रकार nr_sections;
	Elf64_Addr orc_ip_addr = 0;
	माप_प्रकार shstrtab_idx, strtab_idx = 0;
	Elf *elf;
	Elf_Scn *scn;
	GElf_Shdr sh;
	GElf_Rela rela;
	GElf_Sym sym;
	Elf_Data *data, *symtab = शून्य, *rela_orc_ip = शून्य;


	objname = _objname;

	elf_version(EV_CURRENT);

	fd = खोलो(objname, O_RDONLY);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("open");
		वापस -1;
	पूर्ण

	elf = elf_begin(fd, ELF_C_READ_MMAP, शून्य);
	अगर (!elf) अणु
		WARN_ELF("elf_begin");
		वापस -1;
	पूर्ण

	अगर (elf_माला_लोhdrnum(elf, &nr_sections)) अणु
		WARN_ELF("elf_getshdrnum");
		वापस -1;
	पूर्ण

	अगर (elf_माला_लोhdrstrndx(elf, &shstrtab_idx)) अणु
		WARN_ELF("elf_getshdrstrndx");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < nr_sections; i++) अणु
		scn = elf_माला_लोcn(elf, i);
		अगर (!scn) अणु
			WARN_ELF("elf_getscn");
			वापस -1;
		पूर्ण

		अगर (!gelf_माला_लोhdr(scn, &sh)) अणु
			WARN_ELF("gelf_getshdr");
			वापस -1;
		पूर्ण

		name = elf_strptr(elf, shstrtab_idx, sh.sh_name);
		अगर (!name) अणु
			WARN_ELF("elf_strptr");
			वापस -1;
		पूर्ण

		data = elf_getdata(scn, शून्य);
		अगर (!data) अणु
			WARN_ELF("elf_getdata");
			वापस -1;
		पूर्ण

		अगर (!म_भेद(name, ".symtab")) अणु
			symtab = data;
		पूर्ण अन्यथा अगर (!म_भेद(name, ".strtab")) अणु
			strtab_idx = i;
		पूर्ण अन्यथा अगर (!म_भेद(name, ".orc_unwind")) अणु
			orc = data->d_buf;
			orc_size = sh.sh_size;
		पूर्ण अन्यथा अगर (!म_भेद(name, ".orc_unwind_ip")) अणु
			orc_ip = data->d_buf;
			orc_ip_addr = sh.sh_addr;
		पूर्ण अन्यथा अगर (!म_भेद(name, ".rela.orc_unwind_ip")) अणु
			rela_orc_ip = data;
		पूर्ण
	पूर्ण

	अगर (!symtab || !strtab_idx || !orc || !orc_ip)
		वापस 0;

	अगर (orc_size % माप(*orc) != 0) अणु
		WARN("bad .orc_unwind section size");
		वापस -1;
	पूर्ण

	nr_entries = orc_size / माप(*orc);
	क्रम (i = 0; i < nr_entries; i++) अणु
		अगर (rela_orc_ip) अणु
			अगर (!gelf_getrela(rela_orc_ip, i, &rela)) अणु
				WARN_ELF("gelf_getrela");
				वापस -1;
			पूर्ण

			अगर (!gelf_माला_लोym(symtab, GELF_R_SYM(rela.r_info), &sym)) अणु
				WARN_ELF("gelf_getsym");
				वापस -1;
			पूर्ण

			अगर (GELF_ST_TYPE(sym.st_info) == STT_SECTION) अणु
				scn = elf_माला_लोcn(elf, sym.st_shndx);
				अगर (!scn) अणु
					WARN_ELF("elf_getscn");
					वापस -1;
				पूर्ण

				अगर (!gelf_माला_लोhdr(scn, &sh)) अणु
					WARN_ELF("gelf_getshdr");
					वापस -1;
				पूर्ण

				name = elf_strptr(elf, shstrtab_idx, sh.sh_name);
				अगर (!name) अणु
					WARN_ELF("elf_strptr");
					वापस -1;
				पूर्ण
			पूर्ण अन्यथा अणु
				name = elf_strptr(elf, strtab_idx, sym.st_name);
				अगर (!name) अणु
					WARN_ELF("elf_strptr");
					वापस -1;
				पूर्ण
			पूर्ण

			म_लिखो("%s+%llx:", name, (अचिन्हित दीर्घ दीर्घ)rela.r_addend);

		पूर्ण अन्यथा अणु
			म_लिखो("%llx:", (अचिन्हित दीर्घ दीर्घ)(orc_ip_addr + (i * माप(पूर्णांक)) + orc_ip[i]));
		पूर्ण


		म_लिखो(" sp:");

		prपूर्णांक_reg(orc[i].sp_reg, bswap_अगर_needed(orc[i].sp_offset));

		म_लिखो(" bp:");

		prपूर्णांक_reg(orc[i].bp_reg, bswap_अगर_needed(orc[i].bp_offset));

		म_लिखो(" type:%s end:%d\n",
		       orc_type_name(orc[i].type), orc[i].end);
	पूर्ण

	elf_end(elf);
	बंद(fd);

	वापस 0;
पूर्ण
