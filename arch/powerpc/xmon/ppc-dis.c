<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ppc-dis.c -- Disassemble PowerPC inकाष्ठाions
   Copyright (C) 1994-2016 Free Software Foundation, Inc.
   Written by Ian Lance Taylor, Cygnus Support

This file is part of GDB, GAS, and the GNU binutils.

 */

#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश "nonstdio.h"
#समावेश "ansidecl.h"
#समावेश "ppc.h"
#समावेश "dis-asm.h"

/* This file provides several disassembler functions, all of which use
   the disassembler पूर्णांकerface defined in dis-यंत्र.h.  Several functions
   are provided because this file handles disassembly क्रम the PowerPC
   in both big and little endian mode and also क्रम the POWER (RS/6000)
   chip.  */

/* Extract the opeअक्रम value from the PowerPC or POWER inकाष्ठाion.  */

अटल दीर्घ
opeअक्रम_value_घातerpc (स्थिर काष्ठा घातerpc_opeअक्रम *opeअक्रम,
		       अचिन्हित दीर्घ insn, ppc_cpu_t dialect)
अणु
  दीर्घ value;
  पूर्णांक invalid;
  /* Extract the value from the inकाष्ठाion.  */
  अगर (opeअक्रम->extract)
    value = (*opeअक्रम->extract) (insn, dialect, &invalid);
  अन्यथा
    अणु
      अगर (opeअक्रम->shअगरt >= 0)
	value = (insn >> opeअक्रम->shअगरt) & opeअक्रम->biपंचांग;
      अन्यथा
	value = (insn << -opeअक्रम->shअगरt) & opeअक्रम->biपंचांग;
      अगर ((opeअक्रम->flags & PPC_OPERAND_SIGNED) != 0)
	अणु
	  /* BITM is always some number of zeros followed by some
	     number of ones, followed by some number of zeros.  */
	  अचिन्हित दीर्घ top = opeअक्रम->biपंचांग;
	  /* top & -top gives the righपंचांगost 1 bit, so this
	     fills in any trailing zeros.  */
	  top |= (top & -top) - 1;
	  top &= ~(top >> 1);
	  value = (value ^ top) - top;
	पूर्ण
    पूर्ण

  वापस value;
पूर्ण

/* Determine whether the optional opeअक्रम(s) should be prपूर्णांकed.  */

अटल पूर्णांक
skip_optional_opeअक्रमs (स्थिर अचिन्हित अक्षर *opindex,
			अचिन्हित दीर्घ insn, ppc_cpu_t dialect)
अणु
  स्थिर काष्ठा घातerpc_opeअक्रम *opeअक्रम;

  क्रम (; *opindex != 0; opindex++)
    अणु
      opeअक्रम = &घातerpc_opeअक्रमs[*opindex];
      अगर ((opeअक्रम->flags & PPC_OPERAND_NEXT) != 0
	  || ((opeअक्रम->flags & PPC_OPERAND_OPTIONAL) != 0
	      && opeअक्रम_value_घातerpc (opeअक्रम, insn, dialect) !=
		 ppc_optional_opeअक्रम_value (opeअक्रम)))
	वापस 0;
    पूर्ण

  वापस 1;
पूर्ण

/* Find a match क्रम INSN in the opcode table, given machine DIALECT.
   A DIALECT of -1 is special, matching all machine opcode variations.  */

अटल स्थिर काष्ठा घातerpc_opcode *
lookup_घातerpc (अचिन्हित दीर्घ insn, ppc_cpu_t dialect)
अणु
  स्थिर काष्ठा घातerpc_opcode *opcode;
  स्थिर काष्ठा घातerpc_opcode *opcode_end;

  opcode_end = घातerpc_opcodes + घातerpc_num_opcodes;
  /* Find the first match in the opcode table क्रम this major opcode.  */
  क्रम (opcode = घातerpc_opcodes; opcode < opcode_end; ++opcode)
    अणु
      स्थिर अचिन्हित अक्षर *opindex;
      स्थिर काष्ठा घातerpc_opeअक्रम *opeअक्रम;
      पूर्णांक invalid;

      अगर ((insn & opcode->mask) != opcode->opcode
	  || (dialect != (ppc_cpu_t) -1
	      && ((opcode->flags & dialect) == 0
		  || (opcode->deprecated & dialect) != 0)))
	जारी;

      /* Check validity of opeअक्रमs.  */
      invalid = 0;
      क्रम (opindex = opcode->opeअक्रमs; *opindex != 0; opindex++)
	अणु
	  opeअक्रम = घातerpc_opeअक्रमs + *opindex;
	  अगर (opeअक्रम->extract)
	    (*opeअक्रम->extract) (insn, dialect, &invalid);
	पूर्ण
      अगर (invalid)
	जारी;

      वापस opcode;
    पूर्ण

  वापस शून्य;
पूर्ण

/* Prपूर्णांक a PowerPC or POWER inकाष्ठाion.  */

पूर्णांक prपूर्णांक_insn_घातerpc (अचिन्हित दीर्घ insn, अचिन्हित दीर्घ memaddr)
अणु
  स्थिर काष्ठा घातerpc_opcode *opcode;
  bool insn_is_लघु;
  ppc_cpu_t dialect;

  dialect = PPC_OPCODE_PPC | PPC_OPCODE_COMMON
            | PPC_OPCODE_64 | PPC_OPCODE_POWER4 | PPC_OPCODE_ALTIVEC;

  अगर (cpu_has_feature(CPU_FTRS_POWER5))
    dialect |= PPC_OPCODE_POWER5;

  अगर (cpu_has_feature(CPU_FTRS_CELL))
    dialect |= (PPC_OPCODE_CELL | PPC_OPCODE_ALTIVEC);

  अगर (cpu_has_feature(CPU_FTRS_POWER6))
    dialect |= (PPC_OPCODE_POWER5 | PPC_OPCODE_POWER6 | PPC_OPCODE_ALTIVEC);

  अगर (cpu_has_feature(CPU_FTRS_POWER7))
    dialect |= (PPC_OPCODE_POWER5 | PPC_OPCODE_POWER6 | PPC_OPCODE_POWER7
                | PPC_OPCODE_ALTIVEC | PPC_OPCODE_VSX);

  अगर (cpu_has_feature(CPU_FTRS_POWER8))
    dialect |= (PPC_OPCODE_POWER5 | PPC_OPCODE_POWER6 | PPC_OPCODE_POWER7
		| PPC_OPCODE_POWER8 | PPC_OPCODE_HTM
		| PPC_OPCODE_ALTIVEC | PPC_OPCODE_ALTIVEC2 | PPC_OPCODE_VSX);

  अगर (cpu_has_feature(CPU_FTRS_POWER9))
    dialect |= (PPC_OPCODE_POWER5 | PPC_OPCODE_POWER6 | PPC_OPCODE_POWER7
		| PPC_OPCODE_POWER8 | PPC_OPCODE_POWER9 | PPC_OPCODE_HTM
		| PPC_OPCODE_ALTIVEC | PPC_OPCODE_ALTIVEC2
		| PPC_OPCODE_VSX | PPC_OPCODE_VSX3);

  /* Get the major opcode of the insn.  */
  opcode = शून्य;
  insn_is_लघु = false;

  अगर (opcode == शून्य)
    opcode = lookup_घातerpc (insn, dialect);
  अगर (opcode == शून्य && (dialect & PPC_OPCODE_ANY) != 0)
    opcode = lookup_घातerpc (insn, (ppc_cpu_t) -1);

  अगर (opcode != शून्य)
    अणु
      स्थिर अचिन्हित अक्षर *opindex;
      स्थिर काष्ठा घातerpc_opeअक्रम *opeअक्रम;
      पूर्णांक need_comma;
      पूर्णांक need_paren;
      पूर्णांक skip_optional;

      अगर (opcode->opeअक्रमs[0] != 0)
	म_लिखो("%-7s ", opcode->name);
      अन्यथा
	म_लिखो("%s", opcode->name);

      अगर (insn_is_लघु)
        /* The opeअक्रमs will be fetched out of the 16-bit inकाष्ठाion.  */
        insn >>= 16;

      /* Now extract and prपूर्णांक the opeअक्रमs.  */
      need_comma = 0;
      need_paren = 0;
      skip_optional = -1;
      क्रम (opindex = opcode->opeअक्रमs; *opindex != 0; opindex++)
	अणु
	  दीर्घ value;

	  opeअक्रम = घातerpc_opeअक्रमs + *opindex;

	  /* Opeअक्रमs that are marked FAKE are simply ignored.  We
	     alपढ़ोy made sure that the extract function considered
	     the inकाष्ठाion to be valid.  */
	  अगर ((opeअक्रम->flags & PPC_OPERAND_FAKE) != 0)
	    जारी;

	  /* If all of the optional opeअक्रमs have the value zero,
	     then करोn't prपूर्णांक any of them.  */
	  अगर ((opeअक्रम->flags & PPC_OPERAND_OPTIONAL) != 0)
	    अणु
	      अगर (skip_optional < 0)
		skip_optional = skip_optional_opeअक्रमs (opindex, insn,
							dialect);
	      अगर (skip_optional)
		जारी;
	    पूर्ण

	  value = opeअक्रम_value_घातerpc (opeअक्रम, insn, dialect);

	  अगर (need_comma)
	    अणु
	      म_लिखो(",");
	      need_comma = 0;
	    पूर्ण

	  /* Prपूर्णांक the opeअक्रम as directed by the flags.  */
	  अगर ((opeअक्रम->flags & PPC_OPERAND_GPR) != 0
	      || ((opeअक्रम->flags & PPC_OPERAND_GPR_0) != 0 && value != 0))
	    म_लिखो("r%ld", value);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_FPR) != 0)
	    म_लिखो("f%ld", value);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_VR) != 0)
	    म_लिखो("v%ld", value);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_VSR) != 0)
	    म_लिखो("vs%ld", value);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_RELATIVE) != 0)
	    prपूर्णांक_address(memaddr + value);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_ABSOLUTE) != 0)
	    prपूर्णांक_address(value & 0xffffffff);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_FSL) != 0)
	    म_लिखो("fsl%ld", value);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_FCR) != 0)
	    म_लिखो("fcr%ld", value);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_UDI) != 0)
	    म_लिखो("%ld", value);
	  अन्यथा अगर ((opeअक्रम->flags & PPC_OPERAND_CR_REG) != 0
		   && (((dialect & PPC_OPCODE_PPC) != 0)
		       || ((dialect & PPC_OPCODE_VLE) != 0)))
	    म_लिखो("cr%ld", value);
	  अन्यथा अगर (((opeअक्रम->flags & PPC_OPERAND_CR_BIT) != 0)
		   && (((dialect & PPC_OPCODE_PPC) != 0)
		       || ((dialect & PPC_OPCODE_VLE) != 0)))
	    अणु
	      अटल स्थिर अक्षर *cbnames[4] = अणु "lt", "gt", "eq", "so" पूर्ण;
	      पूर्णांक cr;
	      पूर्णांक cc;

	      cr = value >> 2;
	      अगर (cr != 0)
		म_लिखो("4*cr%d+", cr);
	      cc = value & 3;
	      म_लिखो("%s", cbnames[cc]);
	    पूर्ण
	  अन्यथा
	    म_लिखो("%d", (पूर्णांक) value);

	  अगर (need_paren)
	    अणु
	      म_लिखो(")");
	      need_paren = 0;
	    पूर्ण

	  अगर ((opeअक्रम->flags & PPC_OPERAND_PARENS) == 0)
	    need_comma = 1;
	  अन्यथा
	    अणु
	      म_लिखो("(");
	      need_paren = 1;
	    पूर्ण
	पूर्ण

      /* We have found and prपूर्णांकed an inकाष्ठाion.
         If it was a लघु VLE inकाष्ठाion we have more to करो.  */
      अगर (insn_is_लघु)
        अणु
          memaddr += 2;
          वापस 2;
        पूर्ण
      अन्यथा
        /* Otherwise, वापस.  */
        वापस 4;
    पूर्ण

  /* We could not find a match.  */
  म_लिखो(".long 0x%lx", insn);

  वापस 4;
पूर्ण
