<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Disassemble SPU inकाष्ठाions

   Copyright 2006 Free Software Foundation, Inc.

   This file is part of GDB, GAS, and the GNU binutils.

 */

#समावेश <linux/माला.स>
#समावेश "nonstdio.h"
#समावेश "ansidecl.h"
#समावेश "spu.h"
#समावेश "dis-asm.h"

/* This file provides a disassembler function which uses
   the disassembler पूर्णांकerface defined in dis-यंत्र.h.   */

बाह्य स्थिर काष्ठा spu_opcode spu_opcodes[];
बाह्य स्थिर पूर्णांक spu_num_opcodes;

#घोषणा SPU_DISASM_TBL_SIZE (1 << 11)
अटल स्थिर काष्ठा spu_opcode *spu_disassemble_table[SPU_DISASM_TBL_SIZE];

अटल व्योम
init_spu_disassemble (व्योम)
अणु
  पूर्णांक i;

  /* If two inकाष्ठाions have the same opcode then we prefer the first
   * one.  In most हालs it is just an alternate mnemonic. */
  क्रम (i = 0; i < spu_num_opcodes; i++)
    अणु
      पूर्णांक o = spu_opcodes[i].opcode;
      अगर (o >= SPU_DISASM_TBL_SIZE)
	जारी; /* पात (); */
      अगर (spu_disassemble_table[o] == 0)
	spu_disassemble_table[o] = &spu_opcodes[i];
    पूर्ण
पूर्ण

/* Determine the inकाष्ठाion from the 10 least signअगरicant bits. */
अटल स्थिर काष्ठा spu_opcode *
get_index_क्रम_opcode (अचिन्हित पूर्णांक insn)
अणु
  स्थिर काष्ठा spu_opcode *index;
  अचिन्हित पूर्णांक opcode = insn >> (32-11);

  /* Init the table.  This assumes that element 0/opcode 0 (currently
   * NOP) is always used */
  अगर (spu_disassemble_table[0] == 0)
    init_spu_disassemble ();

  अगर ((index = spu_disassemble_table[opcode & 0x780]) != 0
      && index->insn_type == RRR)
    वापस index;

  अगर ((index = spu_disassemble_table[opcode & 0x7f0]) != 0
      && (index->insn_type == RI18 || index->insn_type == LBT))
    वापस index;

  अगर ((index = spu_disassemble_table[opcode & 0x7f8]) != 0
      && index->insn_type == RI10)
    वापस index;

  अगर ((index = spu_disassemble_table[opcode & 0x7fc]) != 0
      && (index->insn_type == RI16))
    वापस index;

  अगर ((index = spu_disassemble_table[opcode & 0x7fe]) != 0
      && (index->insn_type == RI8))
    वापस index;

  अगर ((index = spu_disassemble_table[opcode & 0x7ff]) != 0)
    वापस index;

  वापस शून्य;
पूर्ण

/* Prपूर्णांक a Spu inकाष्ठाion.  */

पूर्णांक
prपूर्णांक_insn_spu (अचिन्हित दीर्घ insn, अचिन्हित दीर्घ memaddr)
अणु
  पूर्णांक value;
  पूर्णांक hex_value;
  स्थिर काष्ठा spu_opcode *index;
  क्रमागत spu_insns tag;

  index = get_index_क्रम_opcode (insn);

  अगर (index == 0)
    अणु
      म_लिखो(".long 0x%lx", insn);
    पूर्ण
  अन्यथा
    अणु
      पूर्णांक i;
      पूर्णांक paren = 0;
      tag = (क्रमागत spu_insns)(index - spu_opcodes);
      म_लिखो("%s", index->mnemonic);
      अगर (tag == M_BI || tag == M_BISL || tag == M_IRET || tag == M_BISLED
	  || tag == M_BIHNZ || tag == M_BIHZ || tag == M_BINZ || tag == M_BIZ
          || tag == M_SYNC || tag == M_HBR)
	अणु
	  पूर्णांक fb = (insn >> (32-18)) & 0x7f;
	  अगर (fb & 0x40)
	    म_लिखो(tag == M_SYNC ? "c" : "p");
	  अगर (fb & 0x20)
	    म_लिखो("d");
	  अगर (fb & 0x10)
	    म_लिखो("e");
	पूर्ण
      अगर (index->arg[0] != 0)
	म_लिखो("\t");
      hex_value = 0;
      क्रम (i = 1;  i <= index->arg[0]; i++)
	अणु
	  पूर्णांक arg = index->arg[i];
	  अगर (arg != A_P && !paren && i > 1)
	    म_लिखो(",");

	  चयन (arg)
	    अणु
	    हाल A_T:
	      म_लिखो("$%lu",
				     DECODE_INSN_RT (insn));
	      अवरोध;
	    हाल A_A:
	      म_लिखो("$%lu",
				     DECODE_INSN_RA (insn));
	      अवरोध;
	    हाल A_B:
	      म_लिखो("$%lu",
				     DECODE_INSN_RB (insn));
	      अवरोध;
	    हाल A_C:
	      म_लिखो("$%lu",
				     DECODE_INSN_RC (insn));
	      अवरोध;
	    हाल A_S:
	      म_लिखो("$sp%lu",
				     DECODE_INSN_RA (insn));
	      अवरोध;
	    हाल A_H:
	      म_लिखो("$ch%lu",
				     DECODE_INSN_RA (insn));
	      अवरोध;
	    हाल A_P:
	      paren++;
	      म_लिखो("(");
	      अवरोध;
	    हाल A_U7A:
	      म_लिखो("%lu",
				     173 - DECODE_INSN_U8 (insn));
	      अवरोध;
	    हाल A_U7B:
	      म_लिखो("%lu",
				     155 - DECODE_INSN_U8 (insn));
	      अवरोध;
	    हाल A_S3:
	    हाल A_S6:
	    हाल A_S7:
	    हाल A_S7N:
	    हाल A_U3:
	    हाल A_U5:
	    हाल A_U6:
	    हाल A_U7:
	      hex_value = DECODE_INSN_I7 (insn);
	      म_लिखो("%d", hex_value);
	      अवरोध;
	    हाल A_S11:
	      prपूर्णांक_address(memaddr + DECODE_INSN_I9a (insn) * 4);
	      अवरोध;
	    हाल A_S11I:
	      prपूर्णांक_address(memaddr + DECODE_INSN_I9b (insn) * 4);
	      अवरोध;
	    हाल A_S10:
	    हाल A_S10B:
	      hex_value = DECODE_INSN_I10 (insn);
	      म_लिखो("%d", hex_value);
	      अवरोध;
	    हाल A_S14:
	      hex_value = DECODE_INSN_I10 (insn) * 16;
	      म_लिखो("%d", hex_value);
	      अवरोध;
	    हाल A_S16:
	      hex_value = DECODE_INSN_I16 (insn);
	      म_लिखो("%d", hex_value);
	      अवरोध;
	    हाल A_X16:
	      hex_value = DECODE_INSN_U16 (insn);
	      म_लिखो("%u", hex_value);
	      अवरोध;
	    हाल A_R18:
	      value = DECODE_INSN_I16 (insn) * 4;
	      अगर (value == 0)
		म_लिखो("%d", value);
	      अन्यथा
		अणु
		  hex_value = memaddr + value;
		  prपूर्णांक_address(hex_value & 0x3ffff);
		पूर्ण
	      अवरोध;
	    हाल A_S18:
	      value = DECODE_INSN_U16 (insn) * 4;
	      अगर (value == 0)
		म_लिखो("%d", value);
	      अन्यथा
		prपूर्णांक_address(value);
	      अवरोध;
	    हाल A_U18:
	      value = DECODE_INSN_U18 (insn);
	      अगर (value == 0 || 1)
		अणु
		  hex_value = value;
		  म_लिखो("%u", value);
		पूर्ण
	      अन्यथा
		prपूर्णांक_address(value);
	      अवरोध;
	    हाल A_U14:
	      hex_value = DECODE_INSN_U14 (insn);
	      म_लिखो("%u", hex_value);
	      अवरोध;
	    पूर्ण
	  अगर (arg != A_P && paren)
	    अणु
	      म_लिखो(")");
	      paren--;
	    पूर्ण
	पूर्ण
      अगर (hex_value > 16)
	म_लिखो("\t# %x", hex_value);
    पूर्ण
  वापस 4;
पूर्ण
