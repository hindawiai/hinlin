<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SPU ELF support क्रम BFD.

   Copyright 2006 Free Software Foundation, Inc.

   This file is part of GDB, GAS, and the GNU binutils.

 */


/* These two क्रमागतs are from rel_apu/common/spu_यंत्र_क्रमmat.h */
/* definition of inकाष्ठाion क्रमmat */
प्रकार क्रमागत अणु
  RRR,
  RI18,
  RI16,
  RI10,
  RI8,
  RI7,
  RR,
  LBT,
  LBTI,
  IDATA,
  UNKNOWN_IFORMAT
पूर्ण spu_अगरormat;

/* These values describe assembly inकाष्ठाion arguments.  They indicate
 * how to encode, range checking and which relocation to use. */
प्रकार क्रमागत अणु
  A_T,  /* रेजिस्टर at pos 0 */
  A_A,  /* रेजिस्टर at pos 7 */
  A_B,  /* रेजिस्टर at pos 14 */
  A_C,  /* रेजिस्टर at pos 21 */
  A_S,  /* special purpose रेजिस्टर at pos 7 */
  A_H,  /* channel रेजिस्टर at pos 7 */
  A_P,  /* parenthesis, this has to separate regs from immediates */
  A_S3,
  A_S6,
  A_S7N,
  A_S7,
  A_U7A,
  A_U7B,
  A_S10B,
  A_S10,
  A_S11,
  A_S11I,
  A_S14,
  A_S16,
  A_S18,
  A_R18,
  A_U3,
  A_U5,
  A_U6,
  A_U7,
  A_U14,
  A_X16,
  A_U18,
  A_MAX
पूर्ण spu_aक्रमmat;

क्रमागत spu_insns अणु
#घोषणा APUOP(TAG,MACFORMAT,OPCODE,MNEMONIC,ASMFORMAT,DEP,PIPE) \
	TAG,
#घोषणा APUOPFB(TAG,MACFORMAT,OPCODE,FB,MNEMONIC,ASMFORMAT,DEP,PIPE) \
	TAG,
#समावेश "spu-insns.h"
#अघोषित APUOP
#अघोषित APUOPFB
        M_SPU_MAX
पूर्ण;

काष्ठा spu_opcode
अणु
   spu_अगरormat insn_type;
   अचिन्हित पूर्णांक opcode;
   अक्षर *mnemonic;
   पूर्णांक arg[5];
पूर्ण;

#घोषणा SIGNED_EXTRACT(insn,size,pos) (((पूर्णांक)((insn) << (32-size-pos))) >> (32-size))
#घोषणा UNSIGNED_EXTRACT(insn,size,pos) (((insn) >> pos) & ((1 << size)-1))

#घोषणा DECODE_INSN_RT(insn) (insn & 0x7f)
#घोषणा DECODE_INSN_RA(insn) ((insn >> 7) & 0x7f)
#घोषणा DECODE_INSN_RB(insn) ((insn >> 14) & 0x7f)
#घोषणा DECODE_INSN_RC(insn) ((insn >> 21) & 0x7f)

#घोषणा DECODE_INSN_I10(insn) SIGNED_EXTRACT(insn,10,14)
#घोषणा DECODE_INSN_U10(insn) UNSIGNED_EXTRACT(insn,10,14)

/* For branching, immediate loads, hbr and  lqa/stqa. */
#घोषणा DECODE_INSN_I16(insn) SIGNED_EXTRACT(insn,16,7)
#घोषणा DECODE_INSN_U16(insn) UNSIGNED_EXTRACT(insn,16,7)

/* क्रम stop */
#घोषणा DECODE_INSN_U14(insn) UNSIGNED_EXTRACT(insn,14,0)

/* For ila */
#घोषणा DECODE_INSN_I18(insn) SIGNED_EXTRACT(insn,18,7)
#घोषणा DECODE_INSN_U18(insn) UNSIGNED_EXTRACT(insn,18,7)

/* For rotate and shअगरt and generate control mask */
#घोषणा DECODE_INSN_I7(insn) SIGNED_EXTRACT(insn,7,14)
#घोषणा DECODE_INSN_U7(insn) UNSIGNED_EXTRACT(insn,7,14)

/* For भग्न <-> पूर्णांक conversion */
#घोषणा DECODE_INSN_I8(insn)  SIGNED_EXTRACT(insn,8,14)
#घोषणा DECODE_INSN_U8(insn) UNSIGNED_EXTRACT(insn,8,14)

/* For hbr  */
#घोषणा DECODE_INSN_I9a(insn) ((SIGNED_EXTRACT(insn,2,23) << 7) | UNSIGNED_EXTRACT(insn,7,0))
#घोषणा DECODE_INSN_I9b(insn) ((SIGNED_EXTRACT(insn,2,14) << 7) | UNSIGNED_EXTRACT(insn,7,0))
#घोषणा DECODE_INSN_U9a(insn) ((UNSIGNED_EXTRACT(insn,2,23) << 7) | UNSIGNED_EXTRACT(insn,7,0))
#घोषणा DECODE_INSN_U9b(insn) ((UNSIGNED_EXTRACT(insn,2,14) << 7) | UNSIGNED_EXTRACT(insn,7,0))

