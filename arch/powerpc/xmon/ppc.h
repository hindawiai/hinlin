<शैली गुरु>
/* ppc.h -- Header file क्रम PowerPC opcode table
   Copyright (C) 1994-2016 Free Software Foundation, Inc.
   Written by Ian Lance Taylor, Cygnus Support

This file is part of GDB, GAS, and the GNU binutils.

GDB, GAS, and the GNU binutils are मुक्त software; you can redistribute
them and/or modअगरy them under the terms of the GNU General Public
License as published by the Free Software Foundation; either version
1, or (at your option) any later version.

GDB, GAS, and the GNU binutils are distributed in the hope that they
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
the GNU General Public License क्रम more details.

You should have received a copy of the GNU General Public License
aदीर्घ with this file; see the file COPYING.  If not, ग_लिखो to the Free
Software Foundation, 51 Franklin Street - Fअगरth Floor, Boston, MA 02110-1301, USA.  */

#अगर_अघोषित PPC_H
#घोषणा PPC_H

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

प्रकार uपूर्णांक64_t ppc_cpu_t;

/* The opcode table is an array of काष्ठा घातerpc_opcode.  */

काष्ठा घातerpc_opcode
अणु
  /* The opcode name.  */
  स्थिर अक्षर *name;

  /* The opcode itself.  Those bits which will be filled in with
     opeअक्रमs are zeroes.  */
  अचिन्हित दीर्घ opcode;

  /* The opcode mask.  This is used by the disassembler.  This is a
     mask containing ones indicating those bits which must match the
     opcode field, and zeroes indicating those bits which need not
     match (and are presumably filled in by opeअक्रमs).  */
  अचिन्हित दीर्घ mask;

  /* One bit flags क्रम the opcode.  These are used to indicate which
     specअगरic processors support the inकाष्ठाions.  The defined values
     are listed below.  */
  ppc_cpu_t flags;

  /* One bit flags क्रम the opcode.  These are used to indicate which
     specअगरic processors no दीर्घer support the inकाष्ठाions.  The defined
     values are listed below.  */
  ppc_cpu_t deprecated;

  /* An array of opeअक्रम codes.  Each code is an index पूर्णांकo the
     opeअक्रम table.  They appear in the order which the opeअक्रमs must
     appear in assembly code, and are terminated by a zero.  */
  अचिन्हित अक्षर opeअक्रमs[8];
पूर्ण;

/* The table itself is sorted by major opcode number, and is otherwise
   in the order in which the disassembler should consider
   inकाष्ठाions.  */
बाह्य स्थिर काष्ठा घातerpc_opcode घातerpc_opcodes[];
बाह्य स्थिर पूर्णांक घातerpc_num_opcodes;
बाह्य स्थिर काष्ठा घातerpc_opcode vle_opcodes[];
बाह्य स्थिर पूर्णांक vle_num_opcodes;

/* Values defined क्रम the flags field of a काष्ठा घातerpc_opcode.  */

/* Opcode is defined क्रम the PowerPC architecture.  */
#घोषणा PPC_OPCODE_PPC			 1

/* Opcode is defined क्रम the POWER (RS/6000) architecture.  */
#घोषणा PPC_OPCODE_POWER		 2

/* Opcode is defined क्रम the POWER2 (Rios 2) architecture.  */
#घोषणा PPC_OPCODE_POWER2		 4

/* Opcode is supported by the Motorola PowerPC 601 processor.  The 601
   is assumed to support all PowerPC (PPC_OPCODE_PPC) inकाष्ठाions,
   but it also supports many additional POWER inकाष्ठाions.  */
#घोषणा PPC_OPCODE_601			 8

/* Opcode is supported in both the Power and PowerPC architectures
   (ie, compiler's -mcpu=common or assembler's -mcom).  More than just
   the पूर्णांकersection of PPC_OPCODE_PPC with the जोड़ of PPC_OPCODE_POWER
   and PPC_OPCODE_POWER2 because many inकाष्ठाions changed mnemonics
   between POWER and POWERPC.  */
#घोषणा PPC_OPCODE_COMMON	      0x10

/* Opcode is supported क्रम any Power or PowerPC platक्रमm (this is
   क्रम the assembler's -many option, and it eliminates duplicates).  */
#घोषणा PPC_OPCODE_ANY		      0x20

/* Opcode is only defined on 64 bit architectures.  */
#घोषणा PPC_OPCODE_64		      0x40

/* Opcode is supported as part of the 64-bit bridge.  */
#घोषणा PPC_OPCODE_64_BRIDGE	      0x80

/* Opcode is supported by Altivec Vector Unit */
#घोषणा PPC_OPCODE_ALTIVEC	     0x100

/* Opcode is supported by PowerPC 403 processor.  */
#घोषणा PPC_OPCODE_403		     0x200

/* Opcode is supported by PowerPC BookE processor.  */
#घोषणा PPC_OPCODE_BOOKE	     0x400

/* Opcode is supported by PowerPC 440 processor.  */
#घोषणा PPC_OPCODE_440		     0x800

/* Opcode is only supported by Power4 architecture.  */
#घोषणा PPC_OPCODE_POWER4	    0x1000

/* Opcode is only supported by Power7 architecture.  */
#घोषणा PPC_OPCODE_POWER7	    0x2000

/* Opcode is only supported by e500x2 Core.  */
#घोषणा PPC_OPCODE_SPE		    0x4000

/* Opcode is supported by e500x2 Integer select APU.  */
#घोषणा PPC_OPCODE_ISEL		    0x8000

/* Opcode is an e500 SPE भग्नing poपूर्णांक inकाष्ठाion.  */
#घोषणा PPC_OPCODE_EFS		   0x10000

/* Opcode is supported by branch locking APU.  */
#घोषणा PPC_OPCODE_BRLOCK	   0x20000

/* Opcode is supported by perक्रमmance monitor APU.  */
#घोषणा PPC_OPCODE_PMR		   0x40000

/* Opcode is supported by cache locking APU.  */
#घोषणा PPC_OPCODE_CACHELCK	   0x80000

/* Opcode is supported by machine check APU.  */
#घोषणा PPC_OPCODE_RFMCI	  0x100000

/* Opcode is only supported by Power5 architecture.  */
#घोषणा PPC_OPCODE_POWER5	  0x200000

/* Opcode is supported by PowerPC e300 family.  */
#घोषणा PPC_OPCODE_E300           0x400000

/* Opcode is only supported by Power6 architecture.  */
#घोषणा PPC_OPCODE_POWER6	  0x800000

/* Opcode is only supported by PowerPC Cell family.  */
#घोषणा PPC_OPCODE_CELL		 0x1000000

/* Opcode is supported by CPUs with paired singles support.  */
#घोषणा PPC_OPCODE_PPCPS	 0x2000000

/* Opcode is supported by Power E500MC */
#घोषणा PPC_OPCODE_E500MC        0x4000000

/* Opcode is supported by PowerPC 405 processor.  */
#घोषणा PPC_OPCODE_405		 0x8000000

/* Opcode is supported by Vector-Scalar (VSX) Unit */
#घोषणा PPC_OPCODE_VSX		0x10000000

/* Opcode is supported by A2.  */
#घोषणा PPC_OPCODE_A2	 	0x20000000

/* Opcode is supported by PowerPC 476 processor.  */
#घोषणा PPC_OPCODE_476		0x40000000

/* Opcode is supported by AppliedMicro Titan core */
#घोषणा PPC_OPCODE_TITAN        0x80000000

/* Opcode which is supported by the e500 family */
#घोषणा PPC_OPCODE_E500	       0x100000000ull

/* Opcode is supported by Extended Altivec Vector Unit */
#घोषणा PPC_OPCODE_ALTIVEC2    0x200000000ull

/* Opcode is supported by Power E6500 */
#घोषणा PPC_OPCODE_E6500       0x400000000ull

/* Opcode is supported by Thपढ़ो management APU */
#घोषणा PPC_OPCODE_TMR         0x800000000ull

/* Opcode which is supported by the VLE extension.  */
#घोषणा PPC_OPCODE_VLE	      0x1000000000ull

/* Opcode is only supported by Power8 architecture.  */
#घोषणा PPC_OPCODE_POWER8     0x2000000000ull

/* Opcode which is supported by the Hardware Transactional Memory extension.  */
/* Currently, this is the same as the POWER8 mask.  If another cpu comes out
   that isn't a superset of POWER8, we can define this to its own mask.  */
#घोषणा PPC_OPCODE_HTM        PPC_OPCODE_POWER8

/* Opcode is supported by ppc750cl.  */
#घोषणा PPC_OPCODE_750	      0x4000000000ull

/* Opcode is supported by ppc7450.  */
#घोषणा PPC_OPCODE_7450	      0x8000000000ull

/* Opcode is supported by ppc821/850/860.  */
#घोषणा PPC_OPCODE_860	      0x10000000000ull

/* Opcode is only supported by Power9 architecture.  */
#घोषणा PPC_OPCODE_POWER9     0x20000000000ull

/* Opcode is supported by Vector-Scalar (VSX) Unit from ISA 2.08.  */
#घोषणा PPC_OPCODE_VSX3       0x40000000000ull

  /* Opcode is supported by e200z4.  */
#घोषणा PPC_OPCODE_E200Z4     0x80000000000ull

/* A macro to extract the major opcode from an inकाष्ठाion.  */
#घोषणा PPC_OP(i) (((i) >> 26) & 0x3f)

/* A macro to determine अगर the inकाष्ठाion is a 2-byte VLE insn.  */
#घोषणा PPC_OP_SE_VLE(m) ((m) <= 0xffff)

/* A macro to extract the major opcode from a VLE inकाष्ठाion.  */
#घोषणा VLE_OP(i,m) (((i) >> ((m) <= 0xffff ? 10 : 26)) & 0x3f)

/* A macro to convert a VLE opcode to a VLE opcode segment.  */
#घोषणा VLE_OP_TO_SEG(i) ((i) >> 1)

/* The opeअक्रमs table is an array of काष्ठा घातerpc_opeअक्रम.  */

काष्ठा घातerpc_opeअक्रम
अणु
  /* A biपंचांगask of bits in the opeअक्रम.  */
  अचिन्हित पूर्णांक biपंचांग;

  /* The shअगरt operation to be applied to the opeअक्रम.  No shअगरt
     is made अगर this is zero.  For positive values, the opeअक्रम
     is shअगरted left by SHIFT.  For negative values, the opeअक्रम
     is shअगरted right by -SHIFT.  Use PPC_OPSHIFT_INV to indicate
     that BITM and SHIFT cannot be used to determine where the
     opeअक्रम goes in the insn.  */
  पूर्णांक shअगरt;

  /* Insertion function.  This is used by the assembler.  To insert an
     opeअक्रम value पूर्णांकo an inकाष्ठाion, check this field.

     If it is शून्य, execute
	 अगर (o->shअगरt >= 0)
	   i |= (op & o->biपंचांग) << o->shअगरt;
	 अन्यथा
	   i |= (op & o->biपंचांग) >> -o->shअगरt;
     (i is the inकाष्ठाion which we are filling in, o is a poपूर्णांकer to
     this काष्ठाure, and op is the opeअक्रम value).

     If this field is not शून्य, then simply call it with the
     inकाष्ठाion and the opeअक्रम value.  It will वापस the new value
     of the inकाष्ठाion.  If the ERRMSG argument is not शून्य, then अगर
     the opeअक्रम value is illegal, *ERRMSG will be set to a warning
     string (the opeअक्रम will be inserted in any हाल).  If the
     opeअक्रम value is legal, *ERRMSG will be unchanged (most opeअक्रमs
     can accept any value).  */
  अचिन्हित दीर्घ (*insert)
    (अचिन्हित दीर्घ inकाष्ठाion, दीर्घ op, ppc_cpu_t dialect, स्थिर अक्षर **errmsg);

  /* Extraction function.  This is used by the disassembler.  To
     extract this opeअक्रम type from an inकाष्ठाion, check this field.

     If it is शून्य, compute
	 अगर (o->shअगरt >= 0)
	   op = (i >> o->shअगरt) & o->biपंचांग;
	 अन्यथा
	   op = (i << -o->shअगरt) & o->biपंचांग;
	 अगर ((o->flags & PPC_OPERAND_SIGNED) != 0)
	   sign_extend (op);
     (i is the inकाष्ठाion, o is a poपूर्णांकer to this काष्ठाure, and op
     is the result).

     If this field is not शून्य, then simply call it with the
     inकाष्ठाion value.  It will वापस the value of the opeअक्रम.  If
     the INVALID argument is not शून्य, *INVALID will be set to
     non-zero अगर this opeअक्रम type can not actually be extracted from
     this opeअक्रम (i.e., the inकाष्ठाion करोes not match).  If the
     opeअक्रम is valid, *INVALID will not be changed.  */
  दीर्घ (*extract) (अचिन्हित दीर्घ inकाष्ठाion, ppc_cpu_t dialect, पूर्णांक *invalid);

  /* One bit syntax flags.  */
  अचिन्हित दीर्घ flags;
पूर्ण;

/* Elements in the table are retrieved by indexing with values from
   the opeअक्रमs field of the घातerpc_opcodes table.  */

बाह्य स्थिर काष्ठा घातerpc_opeअक्रम घातerpc_opeअक्रमs[];
बाह्य स्थिर अचिन्हित पूर्णांक num_घातerpc_opeअक्रमs;

/* Use with the shअगरt field of a काष्ठा घातerpc_opeअक्रम to indicate
     that BITM and SHIFT cannot be used to determine where the opeअक्रम
     goes in the insn.  */
#घोषणा PPC_OPSHIFT_INV (-1U << 31)

/* Values defined क्रम the flags field of a काष्ठा घातerpc_opeअक्रम.  */

/* This opeअक्रम takes चिन्हित values.  */
#घोषणा PPC_OPERAND_SIGNED (0x1)

/* This opeअक्रम takes चिन्हित values, but also accepts a full positive
   range of values when running in 32 bit mode.  That is, अगर bits is
   16, it takes any value from -0x8000 to 0xffff.  In 64 bit mode,
   this flag is ignored.  */
#घोषणा PPC_OPERAND_SIGNOPT (0x2)

/* This opeअक्रम करोes not actually exist in the assembler input.  This
   is used to support extended mnemonics such as mr, क्रम which two
   opeअक्रमs fields are identical.  The assembler should call the
   insert function with any op value.  The disassembler should call
   the extract function, ignore the वापस value, and check the value
   placed in the valid argument.  */
#घोषणा PPC_OPERAND_FAKE (0x4)

/* The next opeअक्रम should be wrapped in parentheses rather than
   separated from this one by a comma.  This is used क्रम the load and
   store inकाष्ठाions which want their opeअक्रमs to look like
       reg,displacement(reg)
   */
#घोषणा PPC_OPERAND_PARENS (0x8)

/* This opeअक्रम may use the symbolic names क्रम the CR fields, which
   are
       lt  0	gt  1	eq  2	so  3	un  3
       cr0 0	cr1 1	cr2 2	cr3 3
       cr4 4	cr5 5	cr6 6	cr7 7
   These may be combined arithmetically, as in cr2*4+gt.  These are
   only supported on the PowerPC, not the POWER.  */
#घोषणा PPC_OPERAND_CR_BIT (0x10)

/* This opeअक्रम names a रेजिस्टर.  The disassembler uses this to prपूर्णांक
   रेजिस्टर names with a leading 'r'.  */
#घोषणा PPC_OPERAND_GPR (0x20)

/* Like PPC_OPERAND_GPR, but करोn't print a leading 'r' क्रम r0.  */
#घोषणा PPC_OPERAND_GPR_0 (0x40)

/* This opeअक्रम names a भग्नing poपूर्णांक रेजिस्टर.  The disassembler
   prपूर्णांकs these with a leading 'f'.  */
#घोषणा PPC_OPERAND_FPR (0x80)

/* This opeअक्रम is a relative branch displacement.  The disassembler
   prपूर्णांकs these symbolically अगर possible.  */
#घोषणा PPC_OPERAND_RELATIVE (0x100)

/* This opeअक्रम is an असलolute branch address.  The disassembler
   prपूर्णांकs these symbolically अगर possible.  */
#घोषणा PPC_OPERAND_ABSOLUTE (0x200)

/* This opeअक्रम is optional, and is zero अगर omitted.  This is used क्रम
   example, in the optional BF field in the comparison inकाष्ठाions.  The
   assembler must count the number of opeअक्रमs reमुख्यing on the line,
   and the number of opeअक्रमs reमुख्यing क्रम the opcode, and decide
   whether this opeअक्रम is present or not.  The disassembler should
   prपूर्णांक this opeअक्रम out only अगर it is not zero.  */
#घोषणा PPC_OPERAND_OPTIONAL (0x400)

/* This flag is only used with PPC_OPERAND_OPTIONAL.  If this opeअक्रम
   is omitted, then क्रम the next opeअक्रम use this opeअक्रम value plus
   1, ignoring the next opeअक्रम field क्रम the opcode.  This wretched
   hack is needed because the Power rotate inकाष्ठाions can take
   either 4 or 5 opeअक्रमs.  The disassembler should prपूर्णांक this opeअक्रम
   out regardless of the PPC_OPERAND_OPTIONAL field.  */
#घोषणा PPC_OPERAND_NEXT (0x800)

/* This opeअक्रम should be regarded as a negative number क्रम the
   purposes of overflow checking (i.e., the normal most negative
   number is disallowed and one more than the normal most positive
   number is allowed).  This flag will only be set क्रम a चिन्हित
   opeअक्रम.  */
#घोषणा PPC_OPERAND_NEGATIVE (0x1000)

/* This opeअक्रम names a vector unit रेजिस्टर.  The disassembler
   prपूर्णांकs these with a leading 'v'.  */
#घोषणा PPC_OPERAND_VR (0x2000)

/* This opeअक्रम is क्रम the DS field in a DS क्रमm inकाष्ठाion.  */
#घोषणा PPC_OPERAND_DS (0x4000)

/* This opeअक्रम is क्रम the DQ field in a DQ क्रमm inकाष्ठाion.  */
#घोषणा PPC_OPERAND_DQ (0x8000)

/* Valid range of opeअक्रम is 0..n rather than 0..n-1.  */
#घोषणा PPC_OPERAND_PLUS1 (0x10000)

/* Xilinx APU and FSL related opeअक्रमs */
#घोषणा PPC_OPERAND_FSL (0x20000)
#घोषणा PPC_OPERAND_FCR (0x40000)
#घोषणा PPC_OPERAND_UDI (0x80000)

/* This opeअक्रम names a vector-scalar unit रेजिस्टर.  The disassembler
   prपूर्णांकs these with a leading 'vs'.  */
#घोषणा PPC_OPERAND_VSR (0x100000)

/* This is a CR FIELD that करोes not use symbolic names.  */
#घोषणा PPC_OPERAND_CR_REG (0x200000)

/* This flag is only used with PPC_OPERAND_OPTIONAL.  If this opeअक्रम
   is omitted, then the value it should use क्रम the opeअक्रम is stored
   in the SHIFT field of the immediatly following opeअक्रम field.  */
#घोषणा PPC_OPERAND_OPTIONAL_VALUE (0x400000)

/* This flag is only used with PPC_OPERAND_OPTIONAL.  The opeअक्रम is
   only optional when generating 32-bit code.  */
#घोषणा PPC_OPERAND_OPTIONAL32 (0x800000)

/* The POWER and PowerPC assemblers use a few macros.  We keep them
   with the opeअक्रमs table क्रम simplicity.  The macro table is an
   array of काष्ठा घातerpc_macro.  */

काष्ठा घातerpc_macro
अणु
  /* The macro name.  */
  स्थिर अक्षर *name;

  /* The number of opeअक्रमs the macro takes.  */
  अचिन्हित पूर्णांक opeअक्रमs;

  /* One bit flags क्रम the opcode.  These are used to indicate which
     specअगरic processors support the inकाष्ठाions.  The values are the
     same as those क्रम the काष्ठा घातerpc_opcode flags field.  */
  ppc_cpu_t flags;

  /* A क्रमmat string to turn the macro पूर्णांकo a normal inकाष्ठाion.
     Each %N in the string is replaced with opeअक्रम number N (zero
     based).  */
  स्थिर अक्षर *क्रमmat;
पूर्ण;

बाह्य स्थिर काष्ठा घातerpc_macro घातerpc_macros[];
बाह्य स्थिर पूर्णांक घातerpc_num_macros;

बाह्य ppc_cpu_t ppc_parse_cpu (ppc_cpu_t, ppc_cpu_t *, स्थिर अक्षर *);

अटल अंतरभूत दीर्घ
ppc_optional_opeअक्रम_value (स्थिर काष्ठा घातerpc_opeअक्रम *opeअक्रम)
अणु
  अगर ((opeअक्रम->flags & PPC_OPERAND_OPTIONAL_VALUE) != 0)
    वापस (opeअक्रम+1)->shअगरt;
  वापस 0;
पूर्ण

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* PPC_H */
