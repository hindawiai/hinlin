<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2017 Andes Technology Corporation */

#अगर_अघोषित _ASM_RISCV_MODULE_H
#घोषणा _ASM_RISCV_MODULE_H

#समावेश <यंत्र-generic/module.h>

काष्ठा module;
अचिन्हित दीर्घ module_emit_got_entry(काष्ठा module *mod, अचिन्हित दीर्घ val);
अचिन्हित दीर्घ module_emit_plt_entry(काष्ठा module *mod, अचिन्हित दीर्घ val);

#अगर_घोषित CONFIG_MODULE_SECTIONS
काष्ठा mod_section अणु
	Elf_Shdr *shdr;
	पूर्णांक num_entries;
	पूर्णांक max_entries;
पूर्ण;

काष्ठा mod_arch_specअगरic अणु
	काष्ठा mod_section got;
	काष्ठा mod_section plt;
	काष्ठा mod_section got_plt;
पूर्ण;

काष्ठा got_entry अणु
	अचिन्हित दीर्घ symbol_addr;	/* the real variable address */
पूर्ण;

अटल अंतरभूत काष्ठा got_entry emit_got_entry(अचिन्हित दीर्घ val)
अणु
	वापस (काष्ठा got_entry) अणुvalपूर्ण;
पूर्ण

अटल अंतरभूत काष्ठा got_entry *get_got_entry(अचिन्हित दीर्घ val,
					      स्थिर काष्ठा mod_section *sec)
अणु
	काष्ठा got_entry *got = (काष्ठा got_entry *)(sec->shdr->sh_addr);
	पूर्णांक i;
	क्रम (i = 0; i < sec->num_entries; i++) अणु
		अगर (got[i].symbol_addr == val)
			वापस &got[i];
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा plt_entry अणु
	/*
	 * Trampoline code to real target address. The वापस address
	 * should be the original (pc+4) beक्रमe entring plt entry.
	 */
	u32 insn_auipc;		/* auipc t0, 0x0                       */
	u32 insn_ld;		/* ld    t1, 0x10(t0)                  */
	u32 insn_jr;		/* jr    t1                            */
पूर्ण;

#घोषणा OPC_AUIPC  0x0017
#घोषणा OPC_LD     0x3003
#घोषणा OPC_JALR   0x0067
#घोषणा REG_T0     0x5
#घोषणा REG_T1     0x6

अटल अंतरभूत काष्ठा plt_entry emit_plt_entry(अचिन्हित दीर्घ val,
					      अचिन्हित दीर्घ plt,
					      अचिन्हित दीर्घ got_plt)
अणु
	/*
	 * U-Type encoding:
	 * +------------+----------+----------+
	 * | imm[31:12] | rd[11:7] | opc[6:0] |
	 * +------------+----------+----------+
	 *
	 * I-Type encoding:
	 * +------------+------------+--------+----------+----------+
	 * | imm[31:20] | rs1[19:15] | funct3 | rd[11:7] | opc[6:0] |
	 * +------------+------------+--------+----------+----------+
	 *
	 */
	अचिन्हित दीर्घ offset = got_plt - plt;
	u32 hi20 = (offset + 0x800) & 0xfffff000;
	u32 lo12 = (offset - hi20);
	वापस (काष्ठा plt_entry) अणु
		OPC_AUIPC | (REG_T0 << 7) | hi20,
		OPC_LD | (lo12 << 20) | (REG_T0 << 15) | (REG_T1 << 7),
		OPC_JALR | (REG_T1 << 15)
	पूर्ण;
पूर्ण

अटल अंतरभूत पूर्णांक get_got_plt_idx(अचिन्हित दीर्घ val, स्थिर काष्ठा mod_section *sec)
अणु
	काष्ठा got_entry *got_plt = (काष्ठा got_entry *)sec->shdr->sh_addr;
	पूर्णांक i;
	क्रम (i = 0; i < sec->num_entries; i++) अणु
		अगर (got_plt[i].symbol_addr == val)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल अंतरभूत काष्ठा plt_entry *get_plt_entry(अचिन्हित दीर्घ val,
					      स्थिर काष्ठा mod_section *sec_plt,
					      स्थिर काष्ठा mod_section *sec_got_plt)
अणु
	काष्ठा plt_entry *plt = (काष्ठा plt_entry *)sec_plt->shdr->sh_addr;
	पूर्णांक got_plt_idx = get_got_plt_idx(val, sec_got_plt);
	अगर (got_plt_idx >= 0)
		वापस plt + got_plt_idx;
	अन्यथा
		वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_MODULE_SECTIONS */

#पूर्ण_अगर /* _ASM_RISCV_MODULE_H */
