<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ppc-opc.c -- PowerPC opcode list
   Copyright (C) 1994-2016 Free Software Foundation, Inc.
   Written by Ian Lance Taylor, Cygnus Support

   This file is part of GDB, GAS, and the GNU binutils.

 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश "nonstdio.h"
#समावेश "ppc.h"

#घोषणा ATTRIBUTE_UNUSED
#घोषणा _(x)	x

/* This file holds the PowerPC opcode table.  The opcode table
   includes almost all of the extended inकाष्ठाion mnemonics.  This
   permits the disassembler to use them, and simplअगरies the assembler
   logic, at the cost of increasing the table size.  The table is
   strictly स्थिरant data, so the compiler should be able to put it in
   the .text section.

   This file also holds the opeअक्रम table.  All knowledge about
   inserting opeअक्रमs पूर्णांकo inकाष्ठाions and vice-versa is kept in this
   file.  */

/* Local insertion and extraction functions.  */

अटल अचिन्हित दीर्घ insert_arx (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_arx (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_ary (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_ary (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_bat (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_bat (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_bba (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_bba (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_bdm (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_bdm (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_bdp (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_bdp (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_bo (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_bo (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_boe (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_boe (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_esync (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल अचिन्हित दीर्घ insert_dcmxs (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_dcmxs (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_dxd (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_dxd (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_dxdn (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_dxdn (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_fxm (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_fxm (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_li20 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_li20 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_ls (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल अचिन्हित दीर्घ insert_mbe (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_mbe (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_mb6 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_mb6 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल दीर्घ extract_nb (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_nbi (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल अचिन्हित दीर्घ insert_nsi (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_nsi (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_oimm (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_oimm (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_ral (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल अचिन्हित दीर्घ insert_ram (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल अचिन्हित दीर्घ insert_raq (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल अचिन्हित दीर्घ insert_ras (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल अचिन्हित दीर्घ insert_rbs (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_rbs (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_rbx (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल अचिन्हित दीर्घ insert_rx (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_rx (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_ry (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_ry (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_sh6 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_sh6 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_sci8 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_sci8 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_sci8n (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_sci8n (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_sd4h (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_sd4h (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_sd4w (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_sd4w (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_spr (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_spr (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_sprg (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_sprg (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_tbr (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_tbr (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_xt6 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_xt6 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_xtq6 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_xtq6 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_xa6 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_xa6 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_xb6 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_xb6 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_xb6s (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_xb6s (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_xc6 (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_xc6 (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_dm (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_dm (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_vlesi (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_vlesi (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_vlensi (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_vlensi (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_vleui (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_vleui (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);
अटल अचिन्हित दीर्घ insert_vleil (अचिन्हित दीर्घ, दीर्घ, ppc_cpu_t, स्थिर अक्षर **);
अटल दीर्घ extract_vleil (अचिन्हित दीर्घ, ppc_cpu_t, पूर्णांक *);

/* The opeअक्रमs table.

   The fields are biपंचांग, shअगरt, insert, extract, flags.

   We used to put parens around the various additions, like the one
   क्रम BA just below.  However, that caused trouble with feeble
   compilers with a limit on depth of a parenthesized expression, like
   (reportedly) the compiler in Microsoft Developer Studio 5.  So we
   omit the parens, since the macros are never used in a context where
   the addition will be ambiguous.  */

स्थिर काष्ठा घातerpc_opeअक्रम घातerpc_opeअक्रमs[] =
अणु
  /* The zero index is used to indicate the end of the list of
     opeअक्रमs.  */
#घोषणा UNUSED 0
  अणु 0, 0, शून्य, शून्य, 0 पूर्ण,

  /* The BA field in an XL क्रमm inकाष्ठाion.  */
#घोषणा BA UNUSED + 1
  /* The BI field in a B क्रमm or XL क्रमm inकाष्ठाion.  */
#घोषणा BI BA
#घोषणा BI_MASK (0x1f << 16)
  अणु 0x1f, 16, शून्य, शून्य, PPC_OPERAND_CR_BIT पूर्ण,

  /* The BA field in an XL क्रमm inकाष्ठाion when it must be the same
     as the BT field in the same inकाष्ठाion.  */
#घोषणा BAT BA + 1
  अणु 0x1f, 16, insert_bat, extract_bat, PPC_OPERAND_FAKE पूर्ण,

  /* The BB field in an XL क्रमm inकाष्ठाion.  */
#घोषणा BB BAT + 1
#घोषणा BB_MASK (0x1f << 11)
  अणु 0x1f, 11, शून्य, शून्य, PPC_OPERAND_CR_BIT पूर्ण,

  /* The BB field in an XL क्रमm inकाष्ठाion when it must be the same
     as the BA field in the same inकाष्ठाion.  */
#घोषणा BBA BB + 1
  /* The VB field in a VX क्रमm inकाष्ठाion when it must be the same
     as the VA field in the same inकाष्ठाion.  */
#घोषणा VBA BBA
  अणु 0x1f, 11, insert_bba, extract_bba, PPC_OPERAND_FAKE पूर्ण,

  /* The BD field in a B क्रमm inकाष्ठाion.  The lower two bits are
     क्रमced to zero.  */
#घोषणा BD BBA + 1
  अणु 0xfffc, 0, शून्य, शून्य, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The BD field in a B क्रमm inकाष्ठाion when असलolute addressing is
     used.  */
#घोषणा BDA BD + 1
  अणु 0xfffc, 0, शून्य, शून्य, PPC_OPERAND_ABSOLUTE | PPC_OPERAND_SIGNED पूर्ण,

  /* The BD field in a B क्रमm inकाष्ठाion when the - modअगरier is used.
     This sets the y bit of the BO field appropriately.  */
#घोषणा BDM BDA + 1
  अणु 0xfffc, 0, insert_bdm, extract_bdm,
    PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The BD field in a B क्रमm inकाष्ठाion when the - modअगरier is used
     and असलolute address is used.  */
#घोषणा BDMA BDM + 1
  अणु 0xfffc, 0, insert_bdm, extract_bdm,
    PPC_OPERAND_ABSOLUTE | PPC_OPERAND_SIGNED पूर्ण,

  /* The BD field in a B क्रमm inकाष्ठाion when the + modअगरier is used.
     This sets the y bit of the BO field appropriately.  */
#घोषणा BDP BDMA + 1
  अणु 0xfffc, 0, insert_bdp, extract_bdp,
    PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The BD field in a B क्रमm inकाष्ठाion when the + modअगरier is used
     and असलolute addressing is used.  */
#घोषणा BDPA BDP + 1
  अणु 0xfffc, 0, insert_bdp, extract_bdp,
    PPC_OPERAND_ABSOLUTE | PPC_OPERAND_SIGNED पूर्ण,

  /* The BF field in an X or XL क्रमm inकाष्ठाion.  */
#घोषणा BF BDPA + 1
  /* The CRFD field in an X क्रमm inकाष्ठाion.  */
#घोषणा CRFD BF
  /* The CRD field in an XL क्रमm inकाष्ठाion.  */
#घोषणा CRD BF
  अणु 0x7, 23, शून्य, शून्य, PPC_OPERAND_CR_REG पूर्ण,

  /* The BF field in an X or XL क्रमm inकाष्ठाion.  */
#घोषणा BFF BF + 1
  अणु 0x7, 23, शून्य, शून्य, 0 पूर्ण,

  /* An optional BF field.  This is used क्रम comparison inकाष्ठाions,
     in which an omitted BF field is taken as zero.  */
#घोषणा OBF BFF + 1
  अणु 0x7, 23, शून्य, शून्य, PPC_OPERAND_CR_REG | PPC_OPERAND_OPTIONAL पूर्ण,

  /* The BFA field in an X or XL क्रमm inकाष्ठाion.  */
#घोषणा BFA OBF + 1
  अणु 0x7, 18, शून्य, शून्य, PPC_OPERAND_CR_REG पूर्ण,

  /* The BO field in a B क्रमm inकाष्ठाion.  Certain values are
     illegal.  */
#घोषणा BO BFA + 1
#घोषणा BO_MASK (0x1f << 21)
  अणु 0x1f, 21, insert_bo, extract_bo, 0 पूर्ण,

  /* The BO field in a B क्रमm inकाष्ठाion when the + or - modअगरier is
     used.  This is like the BO field, but it must be even.  */
#घोषणा BOE BO + 1
  अणु 0x1e, 21, insert_boe, extract_boe, 0 पूर्ण,

  /* The RM field in an X क्रमm inकाष्ठाion.  */
#घोषणा RM BOE + 1
  अणु 0x3, 11, शून्य, शून्य, 0 पूर्ण,

#घोषणा BH RM + 1
  अणु 0x3, 11, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The BT field in an X or XL क्रमm inकाष्ठाion.  */
#घोषणा BT BH + 1
  अणु 0x1f, 21, शून्य, शून्य, PPC_OPERAND_CR_BIT पूर्ण,

  /* The BI16 field in a BD8 क्रमm inकाष्ठाion.  */
#घोषणा BI16 BT + 1
  अणु 0x3, 8, शून्य, शून्य, PPC_OPERAND_CR_BIT पूर्ण,

  /* The BI32 field in a BD15 क्रमm inकाष्ठाion.  */
#घोषणा BI32 BI16 + 1
  अणु 0xf, 16, शून्य, शून्य, PPC_OPERAND_CR_BIT पूर्ण,

  /* The BO32 field in a BD15 क्रमm inकाष्ठाion.  */
#घोषणा BO32 BI32 + 1
  अणु 0x3, 20, शून्य, शून्य, 0 पूर्ण,

  /* The B8 field in a BD8 क्रमm inकाष्ठाion.  */
#घोषणा B8 BO32 + 1
  अणु 0x1fe, -1, शून्य, शून्य, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The B15 field in a BD15 क्रमm inकाष्ठाion.  The lowest bit is
     क्रमced to zero.  */
#घोषणा B15 B8 + 1
  अणु 0xfffe, 0, शून्य, शून्य, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The B24 field in a BD24 क्रमm inकाष्ठाion.  The lowest bit is
     क्रमced to zero.  */
#घोषणा B24 B15 + 1
  अणु 0x1fffffe, 0, शून्य, शून्य, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The condition रेजिस्टर number portion of the BI field in a B क्रमm
     or XL क्रमm inकाष्ठाion.  This is used क्रम the extended
     conditional branch mnemonics, which set the lower two bits of the
     BI field.  This field is optional.  */
#घोषणा CR B24 + 1
  अणु 0x7, 18, शून्य, शून्य, PPC_OPERAND_CR_REG | PPC_OPERAND_OPTIONAL पूर्ण,

  /* The CRB field in an X क्रमm inकाष्ठाion.  */
#घोषणा CRB CR + 1
  /* The MB field in an M क्रमm inकाष्ठाion.  */
#घोषणा MB CRB
#घोषणा MB_MASK (0x1f << 6)
  अणु 0x1f, 6, शून्य, शून्य, 0 पूर्ण,

  /* The CRD32 field in an XL क्रमm inकाष्ठाion.  */
#घोषणा CRD32 CRB + 1
  अणु 0x3, 21, शून्य, शून्य, PPC_OPERAND_CR_REG पूर्ण,

  /* The CRFS field in an X क्रमm inकाष्ठाion.  */
#घोषणा CRFS CRD32 + 1
  अणु 0x7, 0, शून्य, शून्य, PPC_OPERAND_CR_REG पूर्ण,

#घोषणा CRS CRFS + 1
  अणु 0x3, 18, शून्य, शून्य, PPC_OPERAND_CR_REG | PPC_OPERAND_OPTIONAL पूर्ण,

  /* The CT field in an X क्रमm inकाष्ठाion.  */
#घोषणा CT CRS + 1
  /* The MO field in an mbar inकाष्ठाion.  */
#घोषणा MO CT
  अणु 0x1f, 21, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The D field in a D क्रमm inकाष्ठाion.  This is a displacement off
     a रेजिस्टर, and implies that the next opeअक्रम is a रेजिस्टर in
     parentheses.  */
#घोषणा D CT + 1
  अणु 0xffff, 0, शून्य, शून्य, PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED पूर्ण,

  /* The D8 field in a D क्रमm inकाष्ठाion.  This is a displacement off
     a रेजिस्टर, and implies that the next opeअक्रम is a रेजिस्टर in
     parentheses.  */
#घोषणा D8 D + 1
  अणु 0xff, 0, शून्य, शून्य, PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED पूर्ण,

  /* The DCMX field in an X क्रमm inकाष्ठाion.  */
#घोषणा DCMX D8 + 1
  अणु 0x7f, 16, शून्य, शून्य, 0 पूर्ण,

  /* The split DCMX field in an X क्रमm inकाष्ठाion.  */
#घोषणा DCMXS DCMX + 1
  अणु 0x7f, PPC_OPSHIFT_INV, insert_dcmxs, extract_dcmxs, 0 पूर्ण,

  /* The DQ field in a DQ क्रमm inकाष्ठाion.  This is like D, but the
     lower four bits are क्रमced to zero. */
#घोषणा DQ DCMXS + 1
  अणु 0xfff0, 0, शून्य, शून्य,
    PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED | PPC_OPERAND_DQ पूर्ण,

  /* The DS field in a DS क्रमm inकाष्ठाion.  This is like D, but the
     lower two bits are क्रमced to zero.  */
#घोषणा DS DQ + 1
  अणु 0xfffc, 0, शून्य, शून्य,
    PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED | PPC_OPERAND_DS पूर्ण,

  /* The DUIS or BHRBE fields in a XFX क्रमm inकाष्ठाion, 10 bits
     अचिन्हित imediate */
#घोषणा DUIS DS + 1
#घोषणा BHRBE DUIS
  अणु 0x3ff, 11, शून्य, शून्य, 0 पूर्ण,

  /* The split D field in a DX क्रमm inकाष्ठाion.  */
#घोषणा DXD DUIS + 1
  अणु 0xffff, PPC_OPSHIFT_INV, insert_dxd, extract_dxd,
    PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPTपूर्ण,

  /* The split ND field in a DX क्रमm inकाष्ठाion.
     This is the same as the DX field, only negated.  */
#घोषणा NDXD DXD + 1
  अणु 0xffff, PPC_OPSHIFT_INV, insert_dxdn, extract_dxdn,
    PPC_OPERAND_NEGATIVE | PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPTपूर्ण,

  /* The E field in a wrteei inकाष्ठाion.  */
  /* And the W bit in the pair singles inकाष्ठाions.  */
  /* And the ST field in a VX क्रमm inकाष्ठाion.  */
#घोषणा E NDXD + 1
#घोषणा PSW E
#घोषणा ST E
  अणु 0x1, 15, शून्य, शून्य, 0 पूर्ण,

  /* The FL1 field in a POWER SC क्रमm inकाष्ठाion.  */
#घोषणा FL1 E + 1
  /* The U field in an X क्रमm inकाष्ठाion.  */
#घोषणा U FL1
  अणु 0xf, 12, शून्य, शून्य, 0 पूर्ण,

  /* The FL2 field in a POWER SC क्रमm inकाष्ठाion.  */
#घोषणा FL2 FL1 + 1
  अणु 0x7, 2, शून्य, शून्य, 0 पूर्ण,

  /* The FLM field in an XFL क्रमm inकाष्ठाion.  */
#घोषणा FLM FL2 + 1
  अणु 0xff, 17, शून्य, शून्य, 0 पूर्ण,

  /* The FRA field in an X or A क्रमm inकाष्ठाion.  */
#घोषणा FRA FLM + 1
#घोषणा FRA_MASK (0x1f << 16)
  अणु 0x1f, 16, शून्य, शून्य, PPC_OPERAND_FPR पूर्ण,

  /* The FRAp field of DFP inकाष्ठाions.  */
#घोषणा FRAp FRA + 1
  अणु 0x1e, 16, शून्य, शून्य, PPC_OPERAND_FPR पूर्ण,

  /* The FRB field in an X or A क्रमm inकाष्ठाion.  */
#घोषणा FRB FRAp + 1
#घोषणा FRB_MASK (0x1f << 11)
  अणु 0x1f, 11, शून्य, शून्य, PPC_OPERAND_FPR पूर्ण,

  /* The FRBp field of DFP inकाष्ठाions.  */
#घोषणा FRBp FRB + 1
  अणु 0x1e, 11, शून्य, शून्य, PPC_OPERAND_FPR पूर्ण,

  /* The FRC field in an A क्रमm inकाष्ठाion.  */
#घोषणा FRC FRBp + 1
#घोषणा FRC_MASK (0x1f << 6)
  अणु 0x1f, 6, शून्य, शून्य, PPC_OPERAND_FPR पूर्ण,

  /* The FRS field in an X क्रमm inकाष्ठाion or the FRT field in a D, X
     or A क्रमm inकाष्ठाion.  */
#घोषणा FRS FRC + 1
#घोषणा FRT FRS
  अणु 0x1f, 21, शून्य, शून्य, PPC_OPERAND_FPR पूर्ण,

  /* The FRSp field of stfdp or the FRTp field of lfdp and DFP
     inकाष्ठाions.  */
#घोषणा FRSp FRS + 1
#घोषणा FRTp FRSp
  अणु 0x1e, 21, शून्य, शून्य, PPC_OPERAND_FPR पूर्ण,

  /* The FXM field in an XFX inकाष्ठाion.  */
#घोषणा FXM FRSp + 1
  अणु 0xff, 12, insert_fxm, extract_fxm, 0 पूर्ण,

  /* Power4 version क्रम mfcr.  */
#घोषणा FXM4 FXM + 1
  अणु 0xff, 12, insert_fxm, extract_fxm,
    PPC_OPERAND_OPTIONAL | PPC_OPERAND_OPTIONAL_VALUEपूर्ण,
  /* If the FXM4 opeअक्रम is ommitted, use the sentinel value -1.  */
  अणु -1, -1, शून्य, शून्य, 0पूर्ण,

  /* The IMM20 field in an LI inकाष्ठाion.  */
#घोषणा IMM20 FXM4 + 2
  अणु 0xfffff, PPC_OPSHIFT_INV, insert_li20, extract_li20, PPC_OPERAND_SIGNEDपूर्ण,

  /* The L field in a D or X क्रमm inकाष्ठाion.  */
#घोषणा L IMM20 + 1
  अणु 0x1, 21, शून्य, शून्य, 0 पूर्ण,

  /* The optional L field in tlbie and tlbiel inकाष्ठाions.  */
#घोषणा LOPT L + 1
  /* The R field in a HTM X क्रमm inकाष्ठाion.  */
#घोषणा HTM_R LOPT
  अणु 0x1, 21, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The optional (क्रम 32-bit) L field in cmp[l][i] inकाष्ठाions.  */
#घोषणा L32OPT LOPT + 1
  अणु 0x1, 21, शून्य, शून्य, PPC_OPERAND_OPTIONAL | PPC_OPERAND_OPTIONAL32 पूर्ण,

  /* The L field in dcbf inकाष्ठाion.  */
#घोषणा L2OPT L32OPT + 1
  अणु 0x3, 21, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The LEV field in a POWER SVC क्रमm inकाष्ठाion.  */
#घोषणा SVC_LEV L2OPT + 1
  अणु 0x7f, 5, शून्य, शून्य, 0 पूर्ण,

  /* The LEV field in an SC क्रमm inकाष्ठाion.  */
#घोषणा LEV SVC_LEV + 1
  अणु 0x7f, 5, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The LI field in an I क्रमm inकाष्ठाion.  The lower two bits are
     क्रमced to zero.  */
#घोषणा LI LEV + 1
  अणु 0x3fffffc, 0, शून्य, शून्य, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The LI field in an I क्रमm inकाष्ठाion when used as an असलolute
     address.  */
#घोषणा LIA LI + 1
  अणु 0x3fffffc, 0, शून्य, शून्य, PPC_OPERAND_ABSOLUTE | PPC_OPERAND_SIGNED पूर्ण,

  /* The LS or WC field in an X (sync or रुको) क्रमm inकाष्ठाion.  */
#घोषणा LS LIA + 1
#घोषणा WC LS
  अणु 0x3, 21, insert_ls, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The ME field in an M क्रमm inकाष्ठाion.  */
#घोषणा ME LS + 1
#घोषणा ME_MASK (0x1f << 1)
  अणु 0x1f, 1, शून्य, शून्य, 0 पूर्ण,

  /* The MB and ME fields in an M क्रमm inकाष्ठाion expressed a single
     opeअक्रम which is a biपंचांगask indicating which bits to select.  This
     is a two opeअक्रम क्रमm using PPC_OPERAND_NEXT.  See the
     description in opcode/ppc.h क्रम what this means.  */
#घोषणा MBE ME + 1
  अणु 0x1f, 6, शून्य, शून्य, PPC_OPERAND_OPTIONAL | PPC_OPERAND_NEXT पूर्ण,
  अणु -1, 0, insert_mbe, extract_mbe, 0 पूर्ण,

  /* The MB or ME field in an MD or MDS क्रमm inकाष्ठाion.  The high
     bit is wrapped to the low end.  */
#घोषणा MB6 MBE + 2
#घोषणा ME6 MB6
#घोषणा MB6_MASK (0x3f << 5)
  अणु 0x3f, 5, insert_mb6, extract_mb6, 0 पूर्ण,

  /* The NB field in an X क्रमm inकाष्ठाion.  The value 32 is stored as
     0.  */
#घोषणा NB MB6 + 1
  अणु 0x1f, 11, शून्य, extract_nb, PPC_OPERAND_PLUS1 पूर्ण,

  /* The NBI field in an lswi inकाष्ठाion, which has special value
     restrictions.  The value 32 is stored as 0.  */
#घोषणा NBI NB + 1
  अणु 0x1f, 11, insert_nbi, extract_nb, PPC_OPERAND_PLUS1 पूर्ण,

  /* The NSI field in a D क्रमm inकाष्ठाion.  This is the same as the
     SI field, only negated.  */
#घोषणा NSI NBI + 1
  अणु 0xffff, 0, insert_nsi, extract_nsi,
    PPC_OPERAND_NEGATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The NSI field in a D क्रमm inकाष्ठाion when we accept a wide range
     of positive values.  */
#घोषणा NSISIGNOPT NSI + 1
  अणु 0xffff, 0, insert_nsi, extract_nsi,
    PPC_OPERAND_NEGATIVE | PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPT पूर्ण,

  /* The RA field in an D, DS, DQ, X, XO, M, or MDS क्रमm inकाष्ठाion.  */
#घोषणा RA NSISIGNOPT + 1
#घोषणा RA_MASK (0x1f << 16)
  अणु 0x1f, 16, शून्य, शून्य, PPC_OPERAND_GPR पूर्ण,

  /* As above, but 0 in the RA field means zero, not r0.  */
#घोषणा RA0 RA + 1
  अणु 0x1f, 16, शून्य, शून्य, PPC_OPERAND_GPR_0 पूर्ण,

  /* The RA field in the DQ क्रमm lq or an lswx inकाष्ठाion, which have special
     value restrictions.  */
#घोषणा RAQ RA0 + 1
#घोषणा RAX RAQ
  अणु 0x1f, 16, insert_raq, शून्य, PPC_OPERAND_GPR_0 पूर्ण,

  /* The RA field in a D or X क्रमm inकाष्ठाion which is an updating
     load, which means that the RA field may not be zero and may not
     equal the RT field.  */
#घोषणा RAL RAQ + 1
  अणु 0x1f, 16, insert_ral, शून्य, PPC_OPERAND_GPR_0 पूर्ण,

  /* The RA field in an lmw inकाष्ठाion, which has special value
     restrictions.  */
#घोषणा RAM RAL + 1
  अणु 0x1f, 16, insert_ram, शून्य, PPC_OPERAND_GPR_0 पूर्ण,

  /* The RA field in a D or X क्रमm inकाष्ठाion which is an updating
     store or an updating भग्नing poपूर्णांक load, which means that the RA
     field may not be zero.  */
#घोषणा RAS RAM + 1
  अणु 0x1f, 16, insert_ras, शून्य, PPC_OPERAND_GPR_0 पूर्ण,

  /* The RA field of the tlbwe, dccci and iccci inकाष्ठाions,
     which are optional.  */
#घोषणा RAOPT RAS + 1
  अणु 0x1f, 16, शून्य, शून्य, PPC_OPERAND_GPR | PPC_OPERAND_OPTIONAL पूर्ण,

  /* The RB field in an X, XO, M, or MDS क्रमm inकाष्ठाion.  */
#घोषणा RB RAOPT + 1
#घोषणा RB_MASK (0x1f << 11)
  अणु 0x1f, 11, शून्य, शून्य, PPC_OPERAND_GPR पूर्ण,

  /* The RB field in an X क्रमm inकाष्ठाion when it must be the same as
     the RS field in the inकाष्ठाion.  This is used क्रम extended
     mnemonics like mr.  */
#घोषणा RBS RB + 1
  अणु 0x1f, 11, insert_rbs, extract_rbs, PPC_OPERAND_FAKE पूर्ण,

  /* The RB field in an lswx inकाष्ठाion, which has special value
     restrictions.  */
#घोषणा RBX RBS + 1
  अणु 0x1f, 11, insert_rbx, शून्य, PPC_OPERAND_GPR पूर्ण,

  /* The RB field of the dccci and iccci inकाष्ठाions, which are optional.  */
#घोषणा RBOPT RBX + 1
  अणु 0x1f, 11, शून्य, शून्य, PPC_OPERAND_GPR | PPC_OPERAND_OPTIONAL पूर्ण,

  /* The RC रेजिस्टर field in an maddld, maddhd or maddhdu inकाष्ठाion.  */
#घोषणा RC RBOPT + 1
  अणु 0x1f, 6, शून्य, शून्य, PPC_OPERAND_GPR पूर्ण,

  /* The RS field in a D, DS, X, XFX, XS, M, MD or MDS क्रमm
     inकाष्ठाion or the RT field in a D, DS, X, XFX or XO क्रमm
     inकाष्ठाion.  */
#घोषणा RS RC + 1
#घोषणा RT RS
#घोषणा RT_MASK (0x1f << 21)
#घोषणा RD RS
  अणु 0x1f, 21, शून्य, शून्य, PPC_OPERAND_GPR पूर्ण,

  /* The RS and RT fields of the DS क्रमm stq and DQ क्रमm lq inकाष्ठाions,
     which have special value restrictions.  */
#घोषणा RSQ RS + 1
#घोषणा RTQ RSQ
  अणु 0x1e, 21, शून्य, शून्य, PPC_OPERAND_GPR पूर्ण,

  /* The RS field of the tlbwe inकाष्ठाion, which is optional.  */
#घोषणा RSO RSQ + 1
#घोषणा RTO RSO
  अणु 0x1f, 21, शून्य, शून्य, PPC_OPERAND_GPR | PPC_OPERAND_OPTIONAL पूर्ण,

  /* The RX field of the SE_RR क्रमm inकाष्ठाion.  */
#घोषणा RX RSO + 1
  अणु 0x1f, PPC_OPSHIFT_INV, insert_rx, extract_rx, PPC_OPERAND_GPR पूर्ण,

  /* The ARX field of the SE_RR क्रमm inकाष्ठाion.  */
#घोषणा ARX RX + 1
  अणु 0x1f, PPC_OPSHIFT_INV, insert_arx, extract_arx, PPC_OPERAND_GPR पूर्ण,

  /* The RY field of the SE_RR क्रमm inकाष्ठाion.  */
#घोषणा RY ARX + 1
#घोषणा RZ RY
  अणु 0x1f, PPC_OPSHIFT_INV, insert_ry, extract_ry, PPC_OPERAND_GPR पूर्ण,

  /* The ARY field of the SE_RR क्रमm inकाष्ठाion.  */
#घोषणा ARY RY + 1
  अणु 0x1f, PPC_OPSHIFT_INV, insert_ary, extract_ary, PPC_OPERAND_GPR पूर्ण,

  /* The SCLSCI8 field in a D क्रमm inकाष्ठाion.  */
#घोषणा SCLSCI8 ARY + 1
  अणु 0xffffffff, PPC_OPSHIFT_INV, insert_sci8, extract_sci8, 0 पूर्ण,

  /* The SCLSCI8N field in a D क्रमm inकाष्ठाion.  This is the same as the
     SCLSCI8 field, only negated.  */
#घोषणा SCLSCI8N SCLSCI8 + 1
  अणु 0xffffffff, PPC_OPSHIFT_INV, insert_sci8n, extract_sci8n,
    PPC_OPERAND_NEGATIVE | PPC_OPERAND_SIGNED पूर्ण,

  /* The SD field of the SD4 क्रमm inकाष्ठाion.  */
#घोषणा SE_SD SCLSCI8N + 1
  अणु 0xf, 8, शून्य, शून्य, PPC_OPERAND_PARENS पूर्ण,

  /* The SD field of the SD4 क्रमm inकाष्ठाion, क्रम halfword.  */
#घोषणा SE_SDH SE_SD + 1
  अणु 0x1e, PPC_OPSHIFT_INV, insert_sd4h, extract_sd4h, PPC_OPERAND_PARENS पूर्ण,

  /* The SD field of the SD4 क्रमm inकाष्ठाion, क्रम word.  */
#घोषणा SE_SDW SE_SDH + 1
  अणु 0x3c, PPC_OPSHIFT_INV, insert_sd4w, extract_sd4w, PPC_OPERAND_PARENS पूर्ण,

  /* The SH field in an X or M क्रमm inकाष्ठाion.  */
#घोषणा SH SE_SDW + 1
#घोषणा SH_MASK (0x1f << 11)
  /* The other UIMM field in a EVX क्रमm inकाष्ठाion.  */
#घोषणा EVUIMM SH
  /* The FC field in an atomic X क्रमm inकाष्ठाion.  */
#घोषणा FC SH
  अणु 0x1f, 11, शून्य, शून्य, 0 पूर्ण,

  /* The SI field in a HTM X क्रमm inकाष्ठाion.  */
#घोषणा HTM_SI SH + 1
  अणु 0x1f, 11, शून्य, शून्य, PPC_OPERAND_SIGNED पूर्ण,

  /* The SH field in an MD क्रमm inकाष्ठाion.  This is split.  */
#घोषणा SH6 HTM_SI + 1
#घोषणा SH6_MASK ((0x1f << 11) | (1 << 1))
  अणु 0x3f, PPC_OPSHIFT_INV, insert_sh6, extract_sh6, 0 पूर्ण,

  /* The SH field of the tlbwe inकाष्ठाion, which is optional.  */
#घोषणा SHO SH6 + 1
  अणु 0x1f, 11, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The SI field in a D क्रमm inकाष्ठाion.  */
#घोषणा SI SHO + 1
  अणु 0xffff, 0, शून्य, शून्य, PPC_OPERAND_SIGNED पूर्ण,

  /* The SI field in a D क्रमm inकाष्ठाion when we accept a wide range
     of positive values.  */
#घोषणा SISIGNOPT SI + 1
  अणु 0xffff, 0, शून्य, शून्य, PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPT पूर्ण,

  /* The SI8 field in a D क्रमm inकाष्ठाion.  */
#घोषणा SI8 SISIGNOPT + 1
  अणु 0xff, 0, शून्य, शून्य, PPC_OPERAND_SIGNED पूर्ण,

  /* The SPR field in an XFX क्रमm inकाष्ठाion.  This is flipped--the
     lower 5 bits are stored in the upper 5 and vice- versa.  */
#घोषणा SPR SI8 + 1
#घोषणा PMR SPR
#घोषणा TMR SPR
#घोषणा SPR_MASK (0x3ff << 11)
  अणु 0x3ff, 11, insert_spr, extract_spr, 0 पूर्ण,

  /* The BAT index number in an XFX क्रमm m[ft]ibat[lu] inकाष्ठाion.  */
#घोषणा SPRBAT SPR + 1
#घोषणा SPRBAT_MASK (0x3 << 17)
  अणु 0x3, 17, शून्य, शून्य, 0 पूर्ण,

  /* The SPRG रेजिस्टर number in an XFX क्रमm m[ft]sprg inकाष्ठाion.  */
#घोषणा SPRG SPRBAT + 1
  अणु 0x1f, 16, insert_sprg, extract_sprg, 0 पूर्ण,

  /* The SR field in an X क्रमm inकाष्ठाion.  */
#घोषणा SR SPRG + 1
  /* The 4-bit UIMM field in a VX क्रमm inकाष्ठाion.  */
#घोषणा UIMM4 SR
  अणु 0xf, 16, शून्य, शून्य, 0 पूर्ण,

  /* The STRM field in an X AltiVec क्रमm inकाष्ठाion.  */
#घोषणा STRM SR + 1
  /* The T field in a tlbilx क्रमm inकाष्ठाion.  */
#घोषणा T STRM
  /* The L field in wclr inकाष्ठाions.  */
#घोषणा L2 STRM
  अणु 0x3, 21, शून्य, शून्य, 0 पूर्ण,

  /* The ESYNC field in an X (sync) क्रमm inकाष्ठाion.  */
#घोषणा ESYNC STRM + 1
  अणु 0xf, 16, insert_esync, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The SV field in a POWER SC क्रमm inकाष्ठाion.  */
#घोषणा SV ESYNC + 1
  अणु 0x3fff, 2, शून्य, शून्य, 0 पूर्ण,

  /* The TBR field in an XFX क्रमm inकाष्ठाion.  This is like the SPR
     field, but it is optional.  */
#घोषणा TBR SV + 1
  अणु 0x3ff, 11, insert_tbr, extract_tbr,
    PPC_OPERAND_OPTIONAL | PPC_OPERAND_OPTIONAL_VALUEपूर्ण,
  /* If the TBR opeअक्रम is ommitted, use the value 268.  */
  अणु -1, 268, शून्य, शून्य, 0पूर्ण,

  /* The TO field in a D or X क्रमm inकाष्ठाion.  */
#घोषणा TO TBR + 2
#घोषणा DUI TO
#घोषणा TO_MASK (0x1f << 21)
  अणु 0x1f, 21, शून्य, शून्य, 0 पूर्ण,

  /* The UI field in a D क्रमm inकाष्ठाion.  */
#घोषणा UI TO + 1
  अणु 0xffff, 0, शून्य, शून्य, 0 पूर्ण,

#घोषणा UISIGNOPT UI + 1
  अणु 0xffff, 0, शून्य, शून्य, PPC_OPERAND_SIGNOPT पूर्ण,

  /* The IMM field in an SE_IM5 inकाष्ठाion.  */
#घोषणा UI5 UISIGNOPT + 1
  अणु 0x1f, 4, शून्य, शून्य, 0 पूर्ण,

  /* The OIMM field in an SE_OIM5 inकाष्ठाion.  */
#घोषणा OIMM5 UI5 + 1
  अणु 0x1f, PPC_OPSHIFT_INV, insert_oimm, extract_oimm, PPC_OPERAND_PLUS1 पूर्ण,

  /* The UI7 field in an SE_LI inकाष्ठाion.  */
#घोषणा UI7 OIMM5 + 1
  अणु 0x7f, 4, शून्य, शून्य, 0 पूर्ण,

  /* The VA field in a VA, VX or VXR क्रमm inकाष्ठाion.  */
#घोषणा VA UI7 + 1
  अणु 0x1f, 16, शून्य, शून्य, PPC_OPERAND_VR पूर्ण,

  /* The VB field in a VA, VX or VXR क्रमm inकाष्ठाion.  */
#घोषणा VB VA + 1
  अणु 0x1f, 11, शून्य, शून्य, PPC_OPERAND_VR पूर्ण,

  /* The VC field in a VA क्रमm inकाष्ठाion.  */
#घोषणा VC VB + 1
  अणु 0x1f, 6, शून्य, शून्य, PPC_OPERAND_VR पूर्ण,

  /* The VD or VS field in a VA, VX, VXR or X क्रमm inकाष्ठाion.  */
#घोषणा VD VC + 1
#घोषणा VS VD
  अणु 0x1f, 21, शून्य, शून्य, PPC_OPERAND_VR पूर्ण,

  /* The SIMM field in a VX क्रमm inकाष्ठाion, and TE in Z क्रमm.  */
#घोषणा SIMM VD + 1
#घोषणा TE SIMM
  अणु 0x1f, 16, शून्य, शून्य, PPC_OPERAND_SIGNEDपूर्ण,

  /* The UIMM field in a VX क्रमm inकाष्ठाion.  */
#घोषणा UIMM SIMM + 1
#घोषणा DCTL UIMM
  अणु 0x1f, 16, शून्य, शून्य, 0 पूर्ण,

  /* The 3-bit UIMM field in a VX क्रमm inकाष्ठाion.  */
#घोषणा UIMM3 UIMM + 1
  अणु 0x7, 16, शून्य, शून्य, 0 पूर्ण,

  /* The 6-bit UIM field in a X क्रमm inकाष्ठाion.  */
#घोषणा UIM6 UIMM3 + 1
  अणु 0x3f, 16, शून्य, शून्य, 0 पूर्ण,

  /* The SIX field in a VX क्रमm inकाष्ठाion.  */
#घोषणा SIX UIM6 + 1
  अणु 0xf, 11, शून्य, शून्य, 0 पूर्ण,

  /* The PS field in a VX क्रमm inकाष्ठाion.  */
#घोषणा PS SIX + 1
  अणु 0x1, 9, शून्य, शून्य, 0 पूर्ण,

  /* The SHB field in a VA क्रमm inकाष्ठाion.  */
#घोषणा SHB PS + 1
  अणु 0xf, 6, शून्य, शून्य, 0 पूर्ण,

  /* The other UIMM field in a half word EVX क्रमm inकाष्ठाion.  */
#घोषणा EVUIMM_2 SHB + 1
  अणु 0x3e, 10, शून्य, शून्य, PPC_OPERAND_PARENS पूर्ण,

  /* The other UIMM field in a word EVX क्रमm inकाष्ठाion.  */
#घोषणा EVUIMM_4 EVUIMM_2 + 1
  अणु 0x7c, 9, शून्य, शून्य, PPC_OPERAND_PARENS पूर्ण,

  /* The other UIMM field in a द्विगुन EVX क्रमm inकाष्ठाion.  */
#घोषणा EVUIMM_8 EVUIMM_4 + 1
  अणु 0xf8, 8, शून्य, शून्य, PPC_OPERAND_PARENS पूर्ण,

  /* The WS or DRM field in an X क्रमm inकाष्ठाion.  */
#घोषणा WS EVUIMM_8 + 1
#घोषणा DRM WS
  अणु 0x7, 11, शून्य, शून्य, 0 पूर्ण,

  /* PowerPC paired singles extensions.  */
  /* W bit in the pair singles inकाष्ठाions क्रम x type inकाष्ठाions.  */
#घोषणा PSWM WS + 1
  /* The BO16 field in a BD8 क्रमm inकाष्ठाion.  */
#घोषणा BO16 PSWM
  अणु  0x1, 10, 0, 0, 0 पूर्ण,

  /* IDX bits क्रम quantization in the pair singles inकाष्ठाions.  */
#घोषणा PSQ PSWM + 1
  अणु  0x7, 12, 0, 0, 0 पूर्ण,

  /* IDX bits क्रम quantization in the pair singles x-type inकाष्ठाions.  */
#घोषणा PSQM PSQ + 1
  अणु  0x7, 7, 0, 0, 0 पूर्ण,

  /* Smaller D field क्रम quantization in the pair singles inकाष्ठाions.  */
#घोषणा PSD PSQM + 1
  अणु  0xfff, 0, 0, 0,  PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED पूर्ण,

  /* The L field in an mपंचांगsrd or A क्रमm inकाष्ठाion or R or W in an X क्रमm.  */
#घोषणा A_L PSD + 1
#घोषणा W A_L
#घोषणा X_R A_L
  अणु 0x1, 16, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The RMC or CY field in a Z23 क्रमm inकाष्ठाion.  */
#घोषणा RMC A_L + 1
#घोषणा CY RMC
  अणु 0x3, 9, शून्य, शून्य, 0 पूर्ण,

#घोषणा R RMC + 1
  अणु 0x1, 16, शून्य, शून्य, 0 पूर्ण,

#घोषणा RIC R + 1
  अणु 0x3, 18, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

#घोषणा PRS RIC + 1
  अणु 0x1, 17, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

#घोषणा SP PRS + 1
  अणु 0x3, 19, शून्य, शून्य, 0 पूर्ण,

#घोषणा S SP + 1
  अणु 0x1, 20, शून्य, शून्य, 0 पूर्ण,

  /* The S field in a XL क्रमm inकाष्ठाion.  */
#घोषणा SXL S + 1
  अणु 0x1, 11, शून्य, शून्य, PPC_OPERAND_OPTIONAL | PPC_OPERAND_OPTIONAL_VALUEपूर्ण,
  /* If the SXL opeअक्रम is ommitted, use the value 1.  */
  अणु -1, 1, शून्य, शून्य, 0पूर्ण,

  /* SH field starting at bit position 16.  */
#घोषणा SH16 SXL + 2
  /* The DCM and DGM fields in a Z क्रमm inकाष्ठाion.  */
#घोषणा DCM SH16
#घोषणा DGM DCM
  अणु 0x3f, 10, शून्य, शून्य, 0 पूर्ण,

  /* The EH field in larx inकाष्ठाion.  */
#घोषणा EH SH16 + 1
  अणु 0x1, 0, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The L field in an mtfsf or XFL क्रमm inकाष्ठाion.  */
  /* The A field in a HTM X क्रमm inकाष्ठाion.  */
#घोषणा XFL_L EH + 1
#घोषणा HTM_A XFL_L
  अणु 0x1, 25, शून्य, शून्य, PPC_OPERAND_OPTIONALपूर्ण,

  /* Xilinx APU related masks and macros */
#घोषणा FCRT XFL_L + 1
#घोषणा FCRT_MASK (0x1f << 21)
  अणु 0x1f, 21, 0, 0, PPC_OPERAND_FCR पूर्ण,

  /* Xilinx FSL related masks and macros */
#घोषणा FSL FCRT + 1
#घोषणा FSL_MASK (0x1f << 11)
  अणु 0x1f, 11, 0, 0, PPC_OPERAND_FSL पूर्ण,

  /* Xilinx UDI related masks and macros */
#घोषणा URT FSL + 1
  अणु 0x1f, 21, 0, 0, PPC_OPERAND_UDI पूर्ण,

#घोषणा URA URT + 1
  अणु 0x1f, 16, 0, 0, PPC_OPERAND_UDI पूर्ण,

#घोषणा URB URA + 1
  अणु 0x1f, 11, 0, 0, PPC_OPERAND_UDI पूर्ण,

#घोषणा URC URB + 1
  अणु 0x1f, 6, 0, 0, PPC_OPERAND_UDI पूर्ण,

  /* The VLESIMM field in a D क्रमm inकाष्ठाion.  */
#घोषणा VLESIMM URC + 1
  अणु 0xffff, PPC_OPSHIFT_INV, insert_vlesi, extract_vlesi,
    PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPT पूर्ण,

  /* The VLENSIMM field in a D क्रमm inकाष्ठाion.  */
#घोषणा VLENSIMM VLESIMM + 1
  अणु 0xffff, PPC_OPSHIFT_INV, insert_vlensi, extract_vlensi,
    PPC_OPERAND_NEGATIVE | PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPT पूर्ण,

  /* The VLEUIMM field in a D क्रमm inकाष्ठाion.  */
#घोषणा VLEUIMM VLENSIMM + 1
  अणु 0xffff, PPC_OPSHIFT_INV, insert_vleui, extract_vleui, 0 पूर्ण,

  /* The VLEUIMML field in a D क्रमm inकाष्ठाion.  */
#घोषणा VLEUIMML VLEUIMM + 1
  अणु 0xffff, PPC_OPSHIFT_INV, insert_vleil, extract_vleil, 0 पूर्ण,

  /* The XT and XS fields in an XX1 or XX3 क्रमm inकाष्ठाion.  This is split.  */
#घोषणा XS6 VLEUIMML + 1
#घोषणा XT6 XS6
  अणु 0x3f, PPC_OPSHIFT_INV, insert_xt6, extract_xt6, PPC_OPERAND_VSR पूर्ण,

  /* The XT and XS fields in an DQ क्रमm VSX inकाष्ठाion.  This is split.  */
#घोषणा XSQ6 XT6 + 1
#घोषणा XTQ6 XSQ6
  अणु 0x3f, PPC_OPSHIFT_INV, insert_xtq6, extract_xtq6, PPC_OPERAND_VSR पूर्ण,

  /* The XA field in an XX3 क्रमm inकाष्ठाion.  This is split.  */
#घोषणा XA6 XTQ6 + 1
  अणु 0x3f, PPC_OPSHIFT_INV, insert_xa6, extract_xa6, PPC_OPERAND_VSR पूर्ण,

  /* The XB field in an XX2 or XX3 क्रमm inकाष्ठाion.  This is split.  */
#घोषणा XB6 XA6 + 1
  अणु 0x3f, PPC_OPSHIFT_INV, insert_xb6, extract_xb6, PPC_OPERAND_VSR पूर्ण,

  /* The XB field in an XX3 क्रमm inकाष्ठाion when it must be the same as
     the XA field in the inकाष्ठाion.  This is used in extended mnemonics
     like xvmovdp.  This is split.  */
#घोषणा XB6S XB6 + 1
  अणु 0x3f, PPC_OPSHIFT_INV, insert_xb6s, extract_xb6s, PPC_OPERAND_FAKE पूर्ण,

  /* The XC field in an XX4 क्रमm inकाष्ठाion.  This is split.  */
#घोषणा XC6 XB6S + 1
  अणु 0x3f, PPC_OPSHIFT_INV, insert_xc6, extract_xc6, PPC_OPERAND_VSR पूर्ण,

  /* The DM or SHW field in an XX3 क्रमm inकाष्ठाion.  */
#घोषणा DM XC6 + 1
#घोषणा SHW DM
  अणु 0x3, 8, शून्य, शून्य, 0 पूर्ण,

  /* The DM field in an extended mnemonic XX3 क्रमm inकाष्ठाion.  */
#घोषणा DMEX DM + 1
  अणु 0x3, 8, insert_dm, extract_dm, 0 पूर्ण,

  /* The UIM field in an XX2 क्रमm inकाष्ठाion.  */
#घोषणा UIM DMEX + 1
  /* The 2-bit UIMM field in a VX क्रमm inकाष्ठाion.  */
#घोषणा UIMM2 UIM
  /* The 2-bit L field in a darn inकाष्ठाion.  */
#घोषणा LRAND UIM
  अणु 0x3, 16, शून्य, शून्य, 0 पूर्ण,

#घोषणा ERAT_T UIM + 1
  अणु 0x7, 21, शून्य, शून्य, 0 पूर्ण,

#घोषणा IH ERAT_T + 1
  अणु 0x7, 21, शून्य, शून्य, PPC_OPERAND_OPTIONAL पूर्ण,

  /* The 8-bit IMM8 field in a XX1 क्रमm inकाष्ठाion.  */
#घोषणा IMM8 IH + 1
  अणु 0xff, 11, शून्य, शून्य, PPC_OPERAND_SIGNOPT पूर्ण,
पूर्ण;

स्थिर अचिन्हित पूर्णांक num_घातerpc_opeअक्रमs = (माप (घातerpc_opeअक्रमs)
					   / माप (घातerpc_opeअक्रमs[0]));

/* The functions used to insert and extract complicated opeअक्रमs.  */

/* The ARX, ARY, RX and RY opeअक्रमs are alternate encodings of GPRs.  */

अटल अचिन्हित दीर्घ
insert_arx (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  अगर (value >= 8 && value < 24)
    वापस insn | ((value - 8) & 0xf);
  अन्यथा
    अणु
      *errmsg = _("invalid register");
      वापस 0;
    पूर्ण
पूर्ण

अटल दीर्घ
extract_arx (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस (insn & 0xf) + 8;
पूर्ण

अटल अचिन्हित दीर्घ
insert_ary (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  अगर (value >= 8 && value < 24)
    वापस insn | (((value - 8) & 0xf) << 4);
  अन्यथा
    अणु
      *errmsg = _("invalid register");
      वापस 0;
    पूर्ण
पूर्ण

अटल दीर्घ
extract_ary (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn >> 4) & 0xf) + 8;
पूर्ण

अटल अचिन्हित दीर्घ
insert_rx (अचिन्हित दीर्घ insn,
	   दीर्घ value,
	   ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	   स्थिर अक्षर **errmsg)
अणु
  अगर (value >= 0 && value < 8)
    वापस insn | value;
  अन्यथा अगर (value >= 24 && value <= 31)
    वापस insn | (value - 16);
  अन्यथा
    अणु
      *errmsg = _("invalid register");
      वापस 0;
    पूर्ण
पूर्ण

अटल दीर्घ
extract_rx (अचिन्हित दीर्घ insn,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  पूर्णांक value = insn & 0xf;
  अगर (value >= 0 && value < 8)
    वापस value;
  अन्यथा
    वापस value + 16;
पूर्ण

अटल अचिन्हित दीर्घ
insert_ry (अचिन्हित दीर्घ insn,
	   दीर्घ value,
	   ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	   स्थिर अक्षर **errmsg)
अणु
  अगर (value >= 0 && value < 8)
    वापस insn | (value << 4);
  अन्यथा अगर (value >= 24 && value <= 31)
    वापस insn | ((value - 16) << 4);
  अन्यथा
    अणु
      *errmsg = _("invalid register");
      वापस 0;
    पूर्ण
पूर्ण

अटल दीर्घ
extract_ry (अचिन्हित दीर्घ insn,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  पूर्णांक value = (insn >> 4) & 0xf;
  अगर (value >= 0 && value < 8)
    वापस value;
  अन्यथा
    वापस value + 16;
पूर्ण

/* The BA field in an XL क्रमm inकाष्ठाion when it must be the same as
   the BT field in the same inकाष्ठाion.  This opeअक्रम is marked FAKE.
   The insertion function just copies the BT field पूर्णांकo the BA field,
   and the extraction function just checks that the fields are the
   same.  */

अटल अचिन्हित दीर्घ
insert_bat (अचिन्हित दीर्घ insn,
	    दीर्घ value ATTRIBUTE_UNUSED,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | (((insn >> 21) & 0x1f) << 16);
पूर्ण

अटल दीर्घ
extract_bat (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid)
अणु
  अगर (((insn >> 21) & 0x1f) != ((insn >> 16) & 0x1f))
    *invalid = 1;
  वापस 0;
पूर्ण

/* The BB field in an XL क्रमm inकाष्ठाion when it must be the same as
   the BA field in the same inकाष्ठाion.  This opeअक्रम is marked FAKE.
   The insertion function just copies the BA field पूर्णांकo the BB field,
   and the extraction function just checks that the fields are the
   same.  */

अटल अचिन्हित दीर्घ
insert_bba (अचिन्हित दीर्घ insn,
	    दीर्घ value ATTRIBUTE_UNUSED,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | (((insn >> 16) & 0x1f) << 11);
पूर्ण

अटल दीर्घ
extract_bba (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid)
अणु
  अगर (((insn >> 16) & 0x1f) != ((insn >> 11) & 0x1f))
    *invalid = 1;
  वापस 0;
पूर्ण

/* The BD field in a B क्रमm inकाष्ठाion when the - modअगरier is used.
   This modअगरier means that the branch is not expected to be taken.
   For chips built to versions of the architecture prior to version 2
   (ie. not Power4 compatible), we set the y bit of the BO field to 1
   अगर the offset is negative.  When extracting, we require that the y
   bit be 1 and that the offset be positive, since अगर the y bit is 0
   we just want to prपूर्णांक the normal क्रमm of the inकाष्ठाion.
   Power4 compatible tarमाला_लो use two bits, "a", and "t", instead of
   the "y" bit.  "at" == 00 => no hपूर्णांक, "at" == 01 => unpredictable,
   "at" == 10 => not taken, "at" == 11 => taken.  The "t" bit is 00001
   in BO field, the "a" bit is 00010 क्रम branch on CR(BI) and 01000
   क्रम branch on CTR.  We only handle the taken/not-taken hपूर्णांक here.
   Note that we करोn't relax the conditions tested here when
   disassembling with -Many because insns using extract_bdm and
   extract_bdp always occur in pairs.  One or the other will always
   be valid.  */

#घोषणा ISA_V2 (PPC_OPCODE_POWER4 | PPC_OPCODE_E500MC | PPC_OPCODE_TITAN)

अटल अचिन्हित दीर्घ
insert_bdm (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  अगर ((dialect & ISA_V2) == 0)
    अणु
      अगर ((value & 0x8000) != 0)
	insn |= 1 << 21;
    पूर्ण
  अन्यथा
    अणु
      अगर ((insn & (0x14 << 21)) == (0x04 << 21))
	insn |= 0x02 << 21;
      अन्यथा अगर ((insn & (0x14 << 21)) == (0x10 << 21))
	insn |= 0x08 << 21;
    पूर्ण
  वापस insn | (value & 0xfffc);
पूर्ण

अटल दीर्घ
extract_bdm (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect,
	     पूर्णांक *invalid)
अणु
  अगर ((dialect & ISA_V2) == 0)
    अणु
      अगर (((insn & (1 << 21)) == 0) != ((insn & (1 << 15)) == 0))
	*invalid = 1;
    पूर्ण
  अन्यथा
    अणु
      अगर ((insn & (0x17 << 21)) != (0x06 << 21)
	  && (insn & (0x1d << 21)) != (0x18 << 21))
	*invalid = 1;
    पूर्ण

  वापस ((insn & 0xfffc) ^ 0x8000) - 0x8000;
पूर्ण

/* The BD field in a B क्रमm inकाष्ठाion when the + modअगरier is used.
   This is like BDM, above, except that the branch is expected to be
   taken.  */

अटल अचिन्हित दीर्घ
insert_bdp (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  अगर ((dialect & ISA_V2) == 0)
    अणु
      अगर ((value & 0x8000) == 0)
	insn |= 1 << 21;
    पूर्ण
  अन्यथा
    अणु
      अगर ((insn & (0x14 << 21)) == (0x04 << 21))
	insn |= 0x03 << 21;
      अन्यथा अगर ((insn & (0x14 << 21)) == (0x10 << 21))
	insn |= 0x09 << 21;
    पूर्ण
  वापस insn | (value & 0xfffc);
पूर्ण

अटल दीर्घ
extract_bdp (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect,
	     पूर्णांक *invalid)
अणु
  अगर ((dialect & ISA_V2) == 0)
    अणु
      अगर (((insn & (1 << 21)) == 0) == ((insn & (1 << 15)) == 0))
	*invalid = 1;
    पूर्ण
  अन्यथा
    अणु
      अगर ((insn & (0x17 << 21)) != (0x07 << 21)
	  && (insn & (0x1d << 21)) != (0x19 << 21))
	*invalid = 1;
    पूर्ण

  वापस ((insn & 0xfffc) ^ 0x8000) - 0x8000;
पूर्ण

अटल अंतरभूत पूर्णांक
valid_bo_pre_v2 (दीर्घ value)
अणु
  /* Certain encodings have bits that are required to be zero.
     These are (z must be zero, y may be anything):
	 0000y
	 0001y
	 001zy
	 0100y
	 0101y
	 011zy
	 1z00y
	 1z01y
	 1z1zz
  */
  अगर ((value & 0x14) == 0)
    वापस 1;
  अन्यथा अगर ((value & 0x14) == 0x4)
    वापस (value & 0x2) == 0;
  अन्यथा अगर ((value & 0x14) == 0x10)
    वापस (value & 0x8) == 0;
  अन्यथा
    वापस value == 0x14;
पूर्ण

अटल अंतरभूत पूर्णांक
valid_bo_post_v2 (दीर्घ value)
अणु
  /* Certain encodings have bits that are required to be zero.
     These are (z must be zero, a & t may be anything):
	 0000z
	 0001z
	 001at
	 0100z
	 0101z
	 011at
	 1a00t
	 1a01t
	 1z1zz
  */
  अगर ((value & 0x14) == 0)
    वापस (value & 0x1) == 0;
  अन्यथा अगर ((value & 0x14) == 0x14)
    वापस value == 0x14;
  अन्यथा
    वापस 1;
पूर्ण

/* Check क्रम legal values of a BO field.  */

अटल पूर्णांक
valid_bo (दीर्घ value, ppc_cpu_t dialect, पूर्णांक extract)
अणु
  पूर्णांक valid_y = valid_bo_pre_v2 (value);
  पूर्णांक valid_at = valid_bo_post_v2 (value);

  /* When disassembling with -Many, accept either encoding on the
     second pass through opcodes.  */
  अगर (extract && dialect == ~(ppc_cpu_t) PPC_OPCODE_ANY)
    वापस valid_y || valid_at;
  अगर ((dialect & ISA_V2) == 0)
    वापस valid_y;
  अन्यथा
    वापस valid_at;
पूर्ण

/* The BO field in a B क्रमm inकाष्ठाion.  Warn about attempts to set
   the field to an illegal value.  */

अटल अचिन्हित दीर्घ
insert_bo (अचिन्हित दीर्घ insn,
	   दीर्घ value,
	   ppc_cpu_t dialect,
	   स्थिर अक्षर **errmsg)
अणु
  अगर (!valid_bo (value, dialect, 0))
    *errmsg = _("invalid conditional option");
  अन्यथा अगर (PPC_OP (insn) == 19 && (insn & 0x400) && ! (value & 4))
    *errmsg = _("invalid counter access");
  वापस insn | ((value & 0x1f) << 21);
पूर्ण

अटल दीर्घ
extract_bo (अचिन्हित दीर्घ insn,
	    ppc_cpu_t dialect,
	    पूर्णांक *invalid)
अणु
  दीर्घ value;

  value = (insn >> 21) & 0x1f;
  अगर (!valid_bo (value, dialect, 1))
    *invalid = 1;
  वापस value;
पूर्ण

/* The BO field in a B क्रमm inकाष्ठाion when the + or - modअगरier is
   used.  This is like the BO field, but it must be even.  When
   extracting it, we क्रमce it to be even.  */

अटल अचिन्हित दीर्घ
insert_boe (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect,
	    स्थिर अक्षर **errmsg)
अणु
  अगर (!valid_bo (value, dialect, 0))
    *errmsg = _("invalid conditional option");
  अन्यथा अगर (PPC_OP (insn) == 19 && (insn & 0x400) && ! (value & 4))
    *errmsg = _("invalid counter access");
  अन्यथा अगर ((value & 1) != 0)
    *errmsg = _("attempt to set y bit when using + or - modifier");

  वापस insn | ((value & 0x1f) << 21);
पूर्ण

अटल दीर्घ
extract_boe (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect,
	     पूर्णांक *invalid)
अणु
  दीर्घ value;

  value = (insn >> 21) & 0x1f;
  अगर (!valid_bo (value, dialect, 1))
    *invalid = 1;
  वापस value & 0x1e;
पूर्ण

/* The DCMX field in a X क्रमm inकाष्ठाion when the field is split
   पूर्णांकo separate DC, DM and DX fields.  */

अटल अचिन्हित दीर्घ
insert_dcmxs (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1f) << 16) | ((value & 0x20) >> 3) | (value & 0x40);
पूर्ण

अटल दीर्घ
extract_dcmxs (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस (insn & 0x40) | ((insn << 3) & 0x20) | ((insn >> 16) & 0x1f);
पूर्ण

/* The D field in a DX क्रमm inकाष्ठाion when the field is split
   पूर्णांकo separate D0, D1 and D2 fields.  */

अटल अचिन्हित दीर्घ
insert_dxd (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | (value & 0xffc1) | ((value & 0x3e) << 15);
पूर्ण

अटल दीर्घ
extract_dxd (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  अचिन्हित दीर्घ dxd = (insn & 0xffc1) | ((insn >> 15) & 0x3e);
  वापस (dxd ^ 0x8000) - 0x8000;
पूर्ण

अटल अचिन्हित दीर्घ
insert_dxdn (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insert_dxd (insn, -value, dialect, errmsg);
पूर्ण

अटल दीर्घ
extract_dxdn (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस -extract_dxd (insn, dialect, invalid);
पूर्ण

/* FXM mask in mfcr and mtcrf inकाष्ठाions.  */

अटल अचिन्हित दीर्घ
insert_fxm (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect,
	    स्थिर अक्षर **errmsg)
अणु
  /* If we're handling the mfocrf and mtocrf insns ensure that exactly
     one bit of the mask field is set.  */
  अगर ((insn & (1 << 20)) != 0)
    अणु
      अगर (value == 0 || (value & -value) != value)
	अणु
	  *errmsg = _("invalid mask field");
	  value = 0;
	पूर्ण
    पूर्ण

  /* If only one bit of the FXM field is set, we can use the new क्रमm
     of the inकाष्ठाion, which is faster.  Unlike the Power4 branch hपूर्णांक
     encoding, this is not backward compatible.  Do not generate the
     new क्रमm unless -mघातer4 has been given, or -many and the two
     opeअक्रम क्रमm of mfcr was used.  */
  अन्यथा अगर (value > 0
	   && (value & -value) == value
	   && ((dialect & PPC_OPCODE_POWER4) != 0
	       || ((dialect & PPC_OPCODE_ANY) != 0
		   && (insn & (0x3ff << 1)) == 19 << 1)))
    insn |= 1 << 20;

  /* Any other value on mfcr is an error.  */
  अन्यथा अगर ((insn & (0x3ff << 1)) == 19 << 1)
    अणु
      /* A value of -1 means we used the one opeअक्रम क्रमm of
	 mfcr which is valid.  */
      अगर (value != -1)
        *errmsg = _("invalid mfcr mask");
      value = 0;
    पूर्ण

  वापस insn | ((value & 0xff) << 12);
पूर्ण

अटल दीर्घ
extract_fxm (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid)
अणु
  दीर्घ mask = (insn >> 12) & 0xff;

  /* Is this a Power4 insn?  */
  अगर ((insn & (1 << 20)) != 0)
    अणु
      /* Exactly one bit of MASK should be set.  */
      अगर (mask == 0 || (mask & -mask) != mask)
	*invalid = 1;
    पूर्ण

  /* Check that non-घातer4 क्रमm of mfcr has a zero MASK.  */
  अन्यथा अगर ((insn & (0x3ff << 1)) == 19 << 1)
    अणु
      अगर (mask != 0)
	*invalid = 1;
      अन्यथा
	mask = -1;
    पूर्ण

  वापस mask;
पूर्ण

अटल अचिन्हित दीर्घ
insert_li20 (अचिन्हित दीर्घ insn,
	     दीर्घ value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0xf0000) >> 5) | ((value & 0x0f800) << 5) | (value & 0x7ff);
पूर्ण

अटल दीर्घ
extract_li20 (अचिन्हित दीर्घ insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  दीर्घ ext = ((insn & 0x4000) == 0x4000) ? 0xfff00000 : 0x00000000;

  वापस ext
         | (((insn >> 11) & 0xf) << 16)
         | (((insn >> 17) & 0xf) << 12)
         | (((insn >> 16) & 0x1) << 11)
         | (insn & 0x7ff);
पूर्ण

/* The 2-bit L field in a SYNC or WC field in a WAIT inकाष्ठाion.
   For SYNC, some L values are reserved:
     * Value 3 is reserved on newer server cpus.
     * Values 2 and 3 are reserved on all other cpus.  */

अटल अचिन्हित दीर्घ
insert_ls (अचिन्हित दीर्घ insn,
	   दीर्घ value,
	   ppc_cpu_t dialect,
	   स्थिर अक्षर **errmsg)
अणु
  /* For SYNC, some L values are illegal.  */
  अगर (((insn >> 1) & 0x3ff) == 598)
    अणु
      दीर्घ max_lvalue = (dialect & PPC_OPCODE_POWER4) ? 2 : 1;
      अगर (value > max_lvalue)
	अणु
	  *errmsg = _("illegal L operand value");
	  वापस insn;
	पूर्ण
    पूर्ण

  वापस insn | ((value & 0x3) << 21);
पूर्ण

/* The 4-bit E field in a sync inकाष्ठाion that accepts 2 opeअक्रमs.
   If ESYNC is non-zero, then the L field must be either 0 or 1 and
   the complement of ESYNC-bit2.  */

अटल अचिन्हित दीर्घ
insert_esync (अचिन्हित दीर्घ insn,
	      दीर्घ value,
	      ppc_cpu_t dialect,
	      स्थिर अक्षर **errmsg)
अणु
  अचिन्हित दीर्घ ls = (insn >> 21) & 0x03;

  अगर (value == 0)
    अणु
      अगर (((dialect & PPC_OPCODE_E6500) != 0 && ls > 1)
	  || ((dialect & PPC_OPCODE_POWER9) != 0 && ls > 2))
        *errmsg = _("illegal L operand value");
      वापस insn;
    पूर्ण

  अगर ((ls & ~0x1)
      || (((value >> 1) & 0x1) ^ ls) == 0)
        *errmsg = _("incompatible L operand value");

  वापस insn | ((value & 0xf) << 16);
पूर्ण

/* The MB and ME fields in an M क्रमm inकाष्ठाion expressed as a single
   opeअक्रम which is itself a biपंचांगask.  The extraction function always
   marks it as invalid, since we never want to recognize an
   inकाष्ठाion which uses a field of this type.  */

अटल अचिन्हित दीर्घ
insert_mbe (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg)
अणु
  अचिन्हित दीर्घ uval, mask;
  पूर्णांक mb, me, mx, count, last;

  uval = value;

  अगर (uval == 0)
    अणु
      *errmsg = _("illegal bitmask");
      वापस insn;
    पूर्ण

  mb = 0;
  me = 32;
  अगर ((uval & 1) != 0)
    last = 1;
  अन्यथा
    last = 0;
  count = 0;

  /* mb: location of last 0->1 transition */
  /* me: location of last 1->0 transition */
  /* count: # transitions */

  क्रम (mx = 0, mask = 1L << 31; mx < 32; ++mx, mask >>= 1)
    अणु
      अगर ((uval & mask) && !last)
	अणु
	  ++count;
	  mb = mx;
	  last = 1;
	पूर्ण
      अन्यथा अगर (!(uval & mask) && last)
	अणु
	  ++count;
	  me = mx;
	  last = 0;
	पूर्ण
    पूर्ण
  अगर (me == 0)
    me = 32;

  अगर (count != 2 && (count != 0 || ! last))
    *errmsg = _("illegal bitmask");

  वापस insn | (mb << 6) | ((me - 1) << 1);
पूर्ण

अटल दीर्घ
extract_mbe (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid)
अणु
  दीर्घ ret;
  पूर्णांक mb, me;
  पूर्णांक i;

  *invalid = 1;

  mb = (insn >> 6) & 0x1f;
  me = (insn >> 1) & 0x1f;
  अगर (mb < me + 1)
    अणु
      ret = 0;
      क्रम (i = mb; i <= me; i++)
	ret |= 1L << (31 - i);
    पूर्ण
  अन्यथा अगर (mb == me + 1)
    ret = ~0;
  अन्यथा /* (mb > me + 1) */
    अणु
      ret = ~0;
      क्रम (i = me + 1; i < mb; i++)
	ret &= ~(1L << (31 - i));
    पूर्ण
  वापस ret;
पूर्ण

/* The MB or ME field in an MD or MDS क्रमm inकाष्ठाion.  The high bit
   is wrapped to the low end.  */

अटल अचिन्हित दीर्घ
insert_mb6 (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1f) << 6) | (value & 0x20);
पूर्ण

अटल दीर्घ
extract_mb6 (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn >> 6) & 0x1f) | (insn & 0x20);
पूर्ण

/* The NB field in an X क्रमm inकाष्ठाion.  The value 32 is stored as
   0.  */

अटल दीर्घ
extract_nb (अचिन्हित दीर्घ insn,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  दीर्घ ret;

  ret = (insn >> 11) & 0x1f;
  अगर (ret == 0)
    ret = 32;
  वापस ret;
पूर्ण

/* The NB field in an lswi inकाष्ठाion, which has special value
   restrictions.  The value 32 is stored as 0.  */

अटल अचिन्हित दीर्घ
insert_nbi (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  दीर्घ rtvalue = (insn & RT_MASK) >> 21;
  दीर्घ ravalue = (insn & RA_MASK) >> 16;

  अगर (value == 0)
    value = 32;
  अगर (rtvalue + (value + 3) / 4 > (rtvalue > ravalue ? ravalue + 32
						     : ravalue))
    *errmsg = _("address register in load range");
  वापस insn | ((value & 0x1f) << 11);
पूर्ण

/* The NSI field in a D क्रमm inकाष्ठाion.  This is the same as the SI
   field, only negated.  The extraction function always marks it as
   invalid, since we never want to recognize an inकाष्ठाion which uses
   a field of this type.  */

अटल अचिन्हित दीर्घ
insert_nsi (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | (-value & 0xffff);
पूर्ण

अटल दीर्घ
extract_nsi (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid)
अणु
  *invalid = 1;
  वापस -(((insn & 0xffff) ^ 0x8000) - 0x8000);
पूर्ण

/* The RA field in a D or X क्रमm inकाष्ठाion which is an updating
   load, which means that the RA field may not be zero and may not
   equal the RT field.  */

अटल अचिन्हित दीर्घ
insert_ral (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg)
अणु
  अगर (value == 0
      || (अचिन्हित दीर्घ) value == ((insn >> 21) & 0x1f))
    *errmsg = "invalid register operand when updating";
  वापस insn | ((value & 0x1f) << 16);
पूर्ण

/* The RA field in an lmw inकाष्ठाion, which has special value
   restrictions.  */

अटल अचिन्हित दीर्घ
insert_ram (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg)
अणु
  अगर ((अचिन्हित दीर्घ) value >= ((insn >> 21) & 0x1f))
    *errmsg = _("index register in load range");
  वापस insn | ((value & 0x1f) << 16);
पूर्ण

/* The RA field in the DQ क्रमm lq or an lswx inकाष्ठाion, which have special
   value restrictions.  */

अटल अचिन्हित दीर्घ
insert_raq (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg)
अणु
  दीर्घ rtvalue = (insn & RT_MASK) >> 21;

  अगर (value == rtvalue)
    *errmsg = _("source and target register operands must be different");
  वापस insn | ((value & 0x1f) << 16);
पूर्ण

/* The RA field in a D or X क्रमm inकाष्ठाion which is an updating
   store or an updating भग्नing poपूर्णांक load, which means that the RA
   field may not be zero.  */

अटल अचिन्हित दीर्घ
insert_ras (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg)
अणु
  अगर (value == 0)
    *errmsg = _("invalid register operand when updating");
  वापस insn | ((value & 0x1f) << 16);
पूर्ण

/* The RB field in an X क्रमm inकाष्ठाion when it must be the same as
   the RS field in the inकाष्ठाion.  This is used क्रम extended
   mnemonics like mr.  This opeअक्रम is marked FAKE.  The insertion
   function just copies the BT field पूर्णांकo the BA field, and the
   extraction function just checks that the fields are the same.  */

अटल अचिन्हित दीर्घ
insert_rbs (अचिन्हित दीर्घ insn,
	    दीर्घ value ATTRIBUTE_UNUSED,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | (((insn >> 21) & 0x1f) << 11);
पूर्ण

अटल दीर्घ
extract_rbs (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid)
अणु
  अगर (((insn >> 21) & 0x1f) != ((insn >> 11) & 0x1f))
    *invalid = 1;
  वापस 0;
पूर्ण

/* The RB field in an lswx inकाष्ठाion, which has special value
   restrictions.  */

अटल अचिन्हित दीर्घ
insert_rbx (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg)
अणु
  दीर्घ rtvalue = (insn & RT_MASK) >> 21;

  अगर (value == rtvalue)
    *errmsg = _("source and target register operands must be different");
  वापस insn | ((value & 0x1f) << 11);
पूर्ण

/* The SCI8 field is made up of SCL and अणुU,Nपूर्णI8 fields.  */
अटल अचिन्हित दीर्घ
insert_sci8 (अचिन्हित दीर्घ insn,
	     दीर्घ value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     स्थिर अक्षर **errmsg)
अणु
  अचिन्हित पूर्णांक fill_scale = 0;
  अचिन्हित दीर्घ ui8 = value;

  अगर ((ui8 & 0xffffff00) == 0)
    ;
  अन्यथा अगर ((ui8 & 0xffffff00) == 0xffffff00)
    fill_scale = 0x400;
  अन्यथा अगर ((ui8 & 0xffff00ff) == 0)
    अणु
      fill_scale = 1 << 8;
      ui8 >>= 8;
    पूर्ण
  अन्यथा अगर ((ui8 & 0xffff00ff) == 0xffff00ff)
    अणु
      fill_scale = 0x400 | (1 << 8);
      ui8 >>= 8;
    पूर्ण
  अन्यथा अगर ((ui8 & 0xff00ffff) == 0)
    अणु
      fill_scale = 2 << 8;
      ui8 >>= 16;
    पूर्ण
  अन्यथा अगर ((ui8 & 0xff00ffff) == 0xff00ffff)
    अणु
      fill_scale = 0x400 | (2 << 8);
      ui8 >>= 16;
    पूर्ण
  अन्यथा अगर ((ui8 & 0x00ffffff) == 0)
    अणु
      fill_scale = 3 << 8;
      ui8 >>= 24;
    पूर्ण
  अन्यथा अगर ((ui8 & 0x00ffffff) == 0x00ffffff)
    अणु
      fill_scale = 0x400 | (3 << 8);
      ui8 >>= 24;
    पूर्ण
  अन्यथा
    अणु
      *errmsg = _("illegal immediate value");
      ui8 = 0;
    पूर्ण

  वापस insn | fill_scale | (ui8 & 0xff);
पूर्ण

अटल दीर्घ
extract_sci8 (अचिन्हित दीर्घ insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  पूर्णांक fill = insn & 0x400;
  पूर्णांक scale_factor = (insn & 0x300) >> 5;
  दीर्घ value = (insn & 0xff) << scale_factor;

  अगर (fill != 0)
    value |= ~((दीर्घ) 0xff << scale_factor);
  वापस value;
पूर्ण

अटल अचिन्हित दीर्घ
insert_sci8n (अचिन्हित दीर्घ insn,
	      दीर्घ value,
	      ppc_cpu_t dialect,
	      स्थिर अक्षर **errmsg)
अणु
  वापस insert_sci8 (insn, -value, dialect, errmsg);
पूर्ण

अटल दीर्घ
extract_sci8n (अचिन्हित दीर्घ insn,
	       ppc_cpu_t dialect,
	       पूर्णांक *invalid)
अणु
  वापस -extract_sci8 (insn, dialect, invalid);
पूर्ण

अटल अचिन्हित दीर्घ
insert_sd4h (अचिन्हित दीर्घ insn,
	     दीर्घ value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1e) << 7);
पूर्ण

अटल दीर्घ
extract_sd4h (अचिन्हित दीर्घ insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn >> 8) & 0xf) << 1;
पूर्ण

अटल अचिन्हित दीर्घ
insert_sd4w (अचिन्हित दीर्घ insn,
	     दीर्घ value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x3c) << 6);
पूर्ण

अटल दीर्घ
extract_sd4w (अचिन्हित दीर्घ insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn >> 8) & 0xf) << 2;
पूर्ण

अटल अचिन्हित दीर्घ
insert_oimm (अचिन्हित दीर्घ insn,
	     दीर्घ value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | (((value - 1) & 0x1f) << 4);
पूर्ण

अटल दीर्घ
extract_oimm (अचिन्हित दीर्घ insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn >> 4) & 0x1f) + 1;
पूर्ण

/* The SH field in an MD क्रमm inकाष्ठाion.  This is split.  */

अटल अचिन्हित दीर्घ
insert_sh6 (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  /* SH6 opeअक्रम in the rldixor inकाष्ठाions.  */
  अगर (PPC_OP (insn) == 4)
    वापस insn | ((value & 0x1f) << 6) | ((value & 0x20) >> 5);
  अन्यथा
    वापस insn | ((value & 0x1f) << 11) | ((value & 0x20) >> 4);
पूर्ण

अटल दीर्घ
extract_sh6 (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  /* SH6 opeअक्रम in the rldixor inकाष्ठाions.  */
  अगर (PPC_OP (insn) == 4)
    वापस ((insn >> 6) & 0x1f) | ((insn << 5) & 0x20);
  अन्यथा
    वापस ((insn >> 11) & 0x1f) | ((insn << 4) & 0x20);
पूर्ण

/* The SPR field in an XFX क्रमm inकाष्ठाion.  This is flipped--the
   lower 5 bits are stored in the upper 5 and vice- versa.  */

अटल अचिन्हित दीर्घ
insert_spr (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1f) << 16) | ((value & 0x3e0) << 6);
पूर्ण

अटल दीर्घ
extract_spr (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn >> 16) & 0x1f) | ((insn >> 6) & 0x3e0);
पूर्ण

/* Some dialects have 8 SPRG रेजिस्टरs instead of the standard 4.  */
#घोषणा ALLOW8_SPRG (PPC_OPCODE_BOOKE | PPC_OPCODE_405)

अटल अचिन्हित दीर्घ
insert_sprg (अचिन्हित दीर्घ insn,
	     दीर्घ value,
	     ppc_cpu_t dialect,
	     स्थिर अक्षर **errmsg)
अणु
  अगर (value > 7
      || (value > 3 && (dialect & ALLOW8_SPRG) == 0))
    *errmsg = _("invalid sprg number");

  /* If this is mfsprg4..7 then use spr 260..263 which can be पढ़ो in
     user mode.  Anything अन्यथा must use spr 272..279.  */
  अगर (value <= 3 || (insn & 0x100) != 0)
    value |= 0x10;

  वापस insn | ((value & 0x17) << 16);
पूर्ण

अटल दीर्घ
extract_sprg (अचिन्हित दीर्घ insn,
	      ppc_cpu_t dialect,
	      पूर्णांक *invalid)
अणु
  अचिन्हित दीर्घ val = (insn >> 16) & 0x1f;

  /* mfsprg can use 260..263 and 272..279.  mtsprg only uses spr 272..279
     If not BOOKE, 405 or VLE, then both use only 272..275.  */
  अगर ((val - 0x10 > 3 && (dialect & ALLOW8_SPRG) == 0)
      || (val - 0x10 > 7 && (insn & 0x100) != 0)
      || val <= 3
      || (val & 8) != 0)
    *invalid = 1;
  वापस val & 7;
पूर्ण

/* The TBR field in an XFX inकाष्ठाion.  This is just like SPR, but it
   is optional.  */

अटल अचिन्हित दीर्घ
insert_tbr (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg)
अणु
  अगर (value != 268 && value != 269)
    *errmsg = _("invalid tbr number");
  वापस insn | ((value & 0x1f) << 16) | ((value & 0x3e0) << 6);
पूर्ण

अटल दीर्घ
extract_tbr (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid)
अणु
  दीर्घ ret;

  ret = ((insn >> 16) & 0x1f) | ((insn >> 6) & 0x3e0);
  अगर (ret != 268 && ret != 269)
    *invalid = 1;
  वापस ret;
पूर्ण

/* The XT and XS fields in an XX1 or XX3 क्रमm inकाष्ठाion.  This is split.  */

अटल अचिन्हित दीर्घ
insert_xt6 (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1f) << 21) | ((value & 0x20) >> 5);
पूर्ण

अटल दीर्घ
extract_xt6 (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn << 5) & 0x20) | ((insn >> 21) & 0x1f);
पूर्ण

/* The XT and XS fields in an DQ क्रमm VSX inकाष्ठाion.  This is split.  */
अटल अचिन्हित दीर्घ
insert_xtq6 (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1f) << 21) | ((value & 0x20) >> 2);
पूर्ण

अटल दीर्घ
extract_xtq6 (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn << 2) & 0x20) | ((insn >> 21) & 0x1f);
पूर्ण

/* The XA field in an XX3 क्रमm inकाष्ठाion.  This is split.  */

अटल अचिन्हित दीर्घ
insert_xa6 (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1f) << 16) | ((value & 0x20) >> 3);
पूर्ण

अटल दीर्घ
extract_xa6 (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn << 3) & 0x20) | ((insn >> 16) & 0x1f);
पूर्ण

/* The XB field in an XX3 क्रमm inकाष्ठाion.  This is split.  */

अटल अचिन्हित दीर्घ
insert_xb6 (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1f) << 11) | ((value & 0x20) >> 4);
पूर्ण

अटल दीर्घ
extract_xb6 (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn << 4) & 0x20) | ((insn >> 11) & 0x1f);
पूर्ण

/* The XB field in an XX3 क्रमm inकाष्ठाion when it must be the same as
   the XA field in the inकाष्ठाion.  This is used क्रम extended
   mnemonics like xvmovdp.  This opeअक्रम is marked FAKE.  The insertion
   function just copies the XA field पूर्णांकo the XB field, and the
   extraction function just checks that the fields are the same.  */

अटल अचिन्हित दीर्घ
insert_xb6s (अचिन्हित दीर्घ insn,
	    दीर्घ value ATTRIBUTE_UNUSED,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | (((insn >> 16) & 0x1f) << 11) | (((insn >> 2) & 0x1) << 1);
पूर्ण

अटल दीर्घ
extract_xb6s (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid)
अणु
  अगर ((((insn >> 16) & 0x1f) != ((insn >> 11) & 0x1f))
      || (((insn >> 2) & 0x1) != ((insn >> 1) & 0x1)))
    *invalid = 1;
  वापस 0;
पूर्ण

/* The XC field in an XX4 क्रमm inकाष्ठाion.  This is split.  */

अटल अचिन्हित दीर्घ
insert_xc6 (अचिन्हित दीर्घ insn,
	    दीर्घ value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0x1f) << 6) | ((value & 0x20) >> 2);
पूर्ण

अटल दीर्घ
extract_xc6 (अचिन्हित दीर्घ insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn << 2) & 0x20) | ((insn >> 6) & 0x1f);
पूर्ण

अटल अचिन्हित दीर्घ
insert_dm (अचिन्हित दीर्घ insn,
	   दीर्घ value,
	   ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	   स्थिर अक्षर **errmsg)
अणु
  अगर (value != 0 && value != 1)
    *errmsg = _("invalid constant");
  वापस insn | (((value) ? 3 : 0) << 8);
पूर्ण

अटल दीर्घ
extract_dm (अचिन्हित दीर्घ insn,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    पूर्णांक *invalid)
अणु
  दीर्घ value;

  value = (insn >> 8) & 3;
  अगर (value != 0 && value != 3)
    *invalid = 1;
  वापस (value) ? 1 : 0;
पूर्ण

/* The VLESIMM field in an I16A क्रमm inकाष्ठाion.  This is split.  */

अटल अचिन्हित दीर्घ
insert_vlesi (अचिन्हित दीर्घ insn,
            दीर्घ value,
            ppc_cpu_t dialect ATTRIBUTE_UNUSED,
            स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0xf800) << 10) | (value & 0x7ff);
पूर्ण

अटल दीर्घ
extract_vlesi (अचिन्हित दीर्घ insn,
             ppc_cpu_t dialect ATTRIBUTE_UNUSED,
             पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  दीर्घ value = ((insn >> 10) & 0xf800) | (insn & 0x7ff);
  value = (value ^ 0x8000) - 0x8000;
  वापस value;
पूर्ण

अटल अचिन्हित दीर्घ
insert_vlensi (अचिन्हित दीर्घ insn,
            दीर्घ value,
            ppc_cpu_t dialect ATTRIBUTE_UNUSED,
            स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  value = -value;
  वापस insn | ((value & 0xf800) << 10) | (value & 0x7ff);
पूर्ण
अटल दीर्घ
extract_vlensi (अचिन्हित दीर्घ insn,
             ppc_cpu_t dialect ATTRIBUTE_UNUSED,
             पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  दीर्घ value = ((insn >> 10) & 0xf800) | (insn & 0x7ff);
  value = (value ^ 0x8000) - 0x8000;
  /* Don't use क्रम disassembly.  */
  *invalid = 1;
  वापस -value;
पूर्ण

/* The VLEUIMM field in an I16A क्रमm inकाष्ठाion.  This is split.  */

अटल अचिन्हित दीर्घ
insert_vleui (अचिन्हित दीर्घ insn,
            दीर्घ value,
            ppc_cpu_t dialect ATTRIBUTE_UNUSED,
            स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0xf800) << 10) | (value & 0x7ff);
पूर्ण

अटल दीर्घ
extract_vleui (अचिन्हित दीर्घ insn,
             ppc_cpu_t dialect ATTRIBUTE_UNUSED,
             पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn >> 10) & 0xf800) | (insn & 0x7ff);
पूर्ण

/* The VLEUIMML field in an I16L क्रमm inकाष्ठाion.  This is split.  */

अटल अचिन्हित दीर्घ
insert_vleil (अचिन्हित दीर्घ insn,
            दीर्घ value,
            ppc_cpu_t dialect ATTRIBUTE_UNUSED,
            स्थिर अक्षर **errmsg ATTRIBUTE_UNUSED)
अणु
  वापस insn | ((value & 0xf800) << 5) | (value & 0x7ff);
पूर्ण

अटल दीर्घ
extract_vleil (अचिन्हित दीर्घ insn,
             ppc_cpu_t dialect ATTRIBUTE_UNUSED,
             पूर्णांक *invalid ATTRIBUTE_UNUSED)
अणु
  वापस ((insn >> 5) & 0xf800) | (insn & 0x7ff);
पूर्ण


/* Macros used to क्रमm opcodes.  */

/* The मुख्य opcode.  */
#घोषणा OP(x) ((((अचिन्हित दीर्घ)(x)) & 0x3f) << 26)
#घोषणा OP_MASK OP (0x3f)

/* The मुख्य opcode combined with a trap code in the TO field of a D
   क्रमm inकाष्ठाion.  Used क्रम extended mnemonics क्रम the trap
   inकाष्ठाions.  */
#घोषणा OPTO(x,to) (OP (x) | ((((अचिन्हित दीर्घ)(to)) & 0x1f) << 21))
#घोषणा OPTO_MASK (OP_MASK | TO_MASK)

/* The मुख्य opcode combined with a comparison size bit in the L field
   of a D क्रमm or X क्रमm inकाष्ठाion.  Used क्रम extended mnemonics क्रम
   the comparison inकाष्ठाions.  */
#घोषणा OPL(x,l) (OP (x) | ((((अचिन्हित दीर्घ)(l)) & 1) << 21))
#घोषणा OPL_MASK OPL (0x3f,1)

/* The मुख्य opcode combined with an update code in D क्रमm inकाष्ठाion.
   Used क्रम extended mnemonics क्रम VLE memory inकाष्ठाions.  */
#घोषणा OPVUP(x,vup) (OP (x) | ((((अचिन्हित दीर्घ)(vup)) & 0xff) << 8))
#घोषणा OPVUP_MASK OPVUP (0x3f,  0xff)

/* The मुख्य opcode combined with an update code and the RT fields specअगरied in
   D क्रमm inकाष्ठाion.  Used क्रम VLE अस्थिर context save/restore
   inकाष्ठाions.  */
#घोषणा OPVUPRT(x,vup,rt) (OPVUP (x, vup) | ((((अचिन्हित दीर्घ)(rt)) & 0x1f) << 21))
#घोषणा OPVUPRT_MASK OPVUPRT (0x3f, 0xff, 0x1f)

/* An A क्रमm inकाष्ठाion.  */
#घोषणा A(op, xop, rc) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1f) << 1) | (((अचिन्हित दीर्घ)(rc)) & 1))
#घोषणा A_MASK A (0x3f, 0x1f, 1)

/* An A_MASK with the FRB field fixed.  */
#घोषणा AFRB_MASK (A_MASK | FRB_MASK)

/* An A_MASK with the FRC field fixed.  */
#घोषणा AFRC_MASK (A_MASK | FRC_MASK)

/* An A_MASK with the FRA and FRC fields fixed.  */
#घोषणा AFRAFRC_MASK (A_MASK | FRA_MASK | FRC_MASK)

/* An AFRAFRC_MASK, but with L bit clear.  */
#घोषणा AFRALFRC_MASK (AFRAFRC_MASK & ~((अचिन्हित दीर्घ) 1 << 16))

/* A B क्रमm inकाष्ठाion.  */
#घोषणा B(op, aa, lk) (OP (op) | ((((अचिन्हित दीर्घ)(aa)) & 1) << 1) | ((lk) & 1))
#घोषणा B_MASK B (0x3f, 1, 1)

/* A BD8 क्रमm inकाष्ठाion.  This is a 16-bit inकाष्ठाion.  */
#घोषणा BD8(op, aa, lk) (((((अचिन्हित दीर्घ)(op)) & 0x3f) << 10) | (((aa) & 1) << 9) | (((lk) & 1) << 8))
#घोषणा BD8_MASK BD8 (0x3f, 1, 1)

/* Another BD8 क्रमm inकाष्ठाion.  This is a 16-bit inकाष्ठाion.  */
#घोषणा BD8IO(op) ((((अचिन्हित दीर्घ)(op)) & 0x1f) << 11)
#घोषणा BD8IO_MASK BD8IO (0x1f)

/* A BD8 क्रमm inकाष्ठाion क्रम simplअगरied mnemonics.  */
#घोषणा EBD8IO(op, bo, bi) (BD8IO ((op)) | ((bo) << 10) | ((bi) << 8))
/* A mask that excludes BO32 and BI32.  */
#घोषणा EBD8IO1_MASK 0xf800
/* A mask that includes BO32 and excludes BI32.  */
#घोषणा EBD8IO2_MASK 0xfc00
/* A mask that include BO32 AND BI32.  */
#घोषणा EBD8IO3_MASK 0xff00

/* A BD15 क्रमm inकाष्ठाion.  */
#घोषणा BD15(op, aa, lk) (OP (op) | ((((अचिन्हित दीर्घ)(aa)) & 0xf) << 22) | ((lk) & 1))
#घोषणा BD15_MASK BD15 (0x3f, 0xf, 1)

/* A BD15 क्रमm inकाष्ठाion क्रम extended conditional branch mnemonics.  */
#घोषणा EBD15(op, aa, bo, lk) (((op) & 0x3f) << 26) | (((aa) & 0xf) << 22) | (((bo) & 0x3) << 20) | ((lk) & 1)
#घोषणा EBD15_MASK 0xfff00001

/* A BD15 क्रमm inकाष्ठाion क्रम extended conditional branch mnemonics with BI.  */
#घोषणा EBD15BI(op, aa, bo, bi, lk) (((op) & 0x3f) << 26) \
                                    | (((aa) & 0xf) << 22) \
                                    | (((bo) & 0x3) << 20) \
                                    | (((bi) & 0x3) << 16) \
                                    | ((lk) & 1)
#घोषणा EBD15BI_MASK  0xfff30001

/* A BD24 क्रमm inकाष्ठाion.  */
#घोषणा BD24(op, aa, lk) (OP (op) | ((((अचिन्हित दीर्घ)(aa)) & 1) << 25) | ((lk) & 1))
#घोषणा BD24_MASK BD24 (0x3f, 1, 1)

/* A B क्रमm inकाष्ठाion setting the BO field.  */
#घोषणा BBO(op, bo, aa, lk) (B ((op), (aa), (lk)) | ((((अचिन्हित दीर्घ)(bo)) & 0x1f) << 21))
#घोषणा BBO_MASK BBO (0x3f, 0x1f, 1, 1)

/* A BBO_MASK with the y bit of the BO field हटाओd.  This permits
   matching a conditional branch regardless of the setting of the y
   bit.  Similarly क्रम the 'at' bits used क्रम घातer4 branch hपूर्णांकs.  */
#घोषणा Y_MASK	 (((अचिन्हित दीर्घ) 1) << 21)
#घोषणा AT1_MASK (((अचिन्हित दीर्घ) 3) << 21)
#घोषणा AT2_MASK (((अचिन्हित दीर्घ) 9) << 21)
#घोषणा BBOY_MASK  (BBO_MASK &~ Y_MASK)
#घोषणा BBOAT_MASK (BBO_MASK &~ AT1_MASK)

/* A B क्रमm inकाष्ठाion setting the BO field and the condition bits of
   the BI field.  */
#घोषणा BBOCB(op, bo, cb, aa, lk) \
  (BBO ((op), (bo), (aa), (lk)) | ((((अचिन्हित दीर्घ)(cb)) & 0x3) << 16))
#घोषणा BBOCB_MASK BBOCB (0x3f, 0x1f, 0x3, 1, 1)

/* A BBOCB_MASK with the y bit of the BO field हटाओd.  */
#घोषणा BBOYCB_MASK (BBOCB_MASK &~ Y_MASK)
#घोषणा BBOATCB_MASK (BBOCB_MASK &~ AT1_MASK)
#घोषणा BBOAT2CB_MASK (BBOCB_MASK &~ AT2_MASK)

/* A BBOYCB_MASK in which the BI field is fixed.  */
#घोषणा BBOYBI_MASK (BBOYCB_MASK | BI_MASK)
#घोषणा BBOATBI_MASK (BBOAT2CB_MASK | BI_MASK)

/* A VLE C क्रमm inकाष्ठाion.  */
#घोषणा C_LK(x, lk) (((((अचिन्हित दीर्घ)(x)) & 0x7fff) << 1) | ((lk) & 1))
#घोषणा C_LK_MASK C_LK(0x7fff, 1)
#घोषणा C(x) ((((अचिन्हित दीर्घ)(x)) & 0xffff))
#घोषणा C_MASK C(0xffff)

/* An Context क्रमm inकाष्ठाion.  */
#घोषणा CTX(op, xop)   (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x7))
#घोषणा CTX_MASK CTX(0x3f, 0x7)

/* A User Context क्रमm inकाष्ठाion.  */
#घोषणा UCTX(op, xop)  (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x1f))
#घोषणा UCTX_MASK UCTX(0x3f, 0x1f)

/* The मुख्य opcode mask with the RA field clear.  */
#घोषणा DRA_MASK (OP_MASK | RA_MASK)

/* A DQ क्रमm VSX inकाष्ठाion.  */
#घोषणा DQX(op, xop) (OP (op) | ((xop) & 0x7))
#घोषणा DQX_MASK DQX (0x3f, 7)

/* A DS क्रमm inकाष्ठाion.  */
#घोषणा DSO(op, xop) (OP (op) | ((xop) & 0x3))
#घोषणा DS_MASK DSO (0x3f, 3)

/* An DX क्रमm inकाष्ठाion.  */
#घोषणा DX(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1f) << 1))
#घोषणा DX_MASK DX (0x3f, 0x1f)

/* An EVSEL क्रमm inकाष्ठाion.  */
#घोषणा EVSEL(op, xop) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0xff) << 3)
#घोषणा EVSEL_MASK EVSEL(0x3f, 0xff)

/* An IA16 क्रमm inकाष्ठाion.  */
#घोषणा IA16(op, xop) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x1f) << 11)
#घोषणा IA16_MASK IA16(0x3f, 0x1f)

/* An I16A क्रमm inकाष्ठाion.  */
#घोषणा I16A(op, xop) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x1f) << 11)
#घोषणा I16A_MASK I16A(0x3f, 0x1f)

/* An I16L क्रमm inकाष्ठाion.  */
#घोषणा I16L(op, xop) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x1f) << 11)
#घोषणा I16L_MASK I16L(0x3f, 0x1f)

/* An IM7 क्रमm inकाष्ठाion.  */
#घोषणा IM7(op) ((((अचिन्हित दीर्घ)(op)) & 0x1f) << 11)
#घोषणा IM7_MASK IM7(0x1f)

/* An M क्रमm inकाष्ठाion.  */
#घोषणा M(op, rc) (OP (op) | ((rc) & 1))
#घोषणा M_MASK M (0x3f, 1)

/* An LI20 क्रमm inकाष्ठाion.  */
#घोषणा LI20(op, xop) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x1) << 15)
#घोषणा LI20_MASK LI20(0x3f, 0x1)

/* An M क्रमm inकाष्ठाion with the ME field specअगरied.  */
#घोषणा MME(op, me, rc) (M ((op), (rc)) | ((((अचिन्हित दीर्घ)(me)) & 0x1f) << 1))

/* An M_MASK with the MB and ME fields fixed.  */
#घोषणा MMBME_MASK (M_MASK | MB_MASK | ME_MASK)

/* An M_MASK with the SH and ME fields fixed.  */
#घोषणा MSHME_MASK (M_MASK | SH_MASK | ME_MASK)

/* An MD क्रमm inकाष्ठाion.  */
#घोषणा MD(op, xop, rc) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x7) << 2) | ((rc) & 1))
#घोषणा MD_MASK MD (0x3f, 0x7, 1)

/* An MD_MASK with the MB field fixed.  */
#घोषणा MDMB_MASK (MD_MASK | MB6_MASK)

/* An MD_MASK with the SH field fixed.  */
#घोषणा MDSH_MASK (MD_MASK | SH6_MASK)

/* An MDS क्रमm inकाष्ठाion.  */
#घोषणा MDS(op, xop, rc) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0xf) << 1) | ((rc) & 1))
#घोषणा MDS_MASK MDS (0x3f, 0xf, 1)

/* An MDS_MASK with the MB field fixed.  */
#घोषणा MDSMB_MASK (MDS_MASK | MB6_MASK)

/* An SC क्रमm inकाष्ठाion.  */
#घोषणा SC(op, sa, lk) (OP (op) | ((((अचिन्हित दीर्घ)(sa)) & 1) << 1) | ((lk) & 1))
#घोषणा SC_MASK (OP_MASK | (((अचिन्हित दीर्घ)0x3ff) << 16) | (((अचिन्हित दीर्घ)1) << 1) | 1)

/* An SCI8 क्रमm inकाष्ठाion.  */
#घोषणा SCI8(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1f) << 11))
#घोषणा SCI8_MASK SCI8(0x3f, 0x1f)

/* An SCI8 क्रमm inकाष्ठाion.  */
#घोषणा SCI8BF(op, fop, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1f) << 11) | (((fop) & 7) << 23))
#घोषणा SCI8BF_MASK SCI8BF(0x3f, 7, 0x1f)

/* An SD4 क्रमm inकाष्ठाion.  This is a 16-bit inकाष्ठाion.  */
#घोषणा SD4(op) ((((अचिन्हित दीर्घ)(op)) & 0xf) << 12)
#घोषणा SD4_MASK SD4(0xf)

/* An SE_IM5 क्रमm inकाष्ठाion.  This is a 16-bit inकाष्ठाion.  */
#घोषणा SE_IM5(op, xop) (((((अचिन्हित दीर्घ)(op)) & 0x3f) << 10) | (((xop) & 0x1) << 9))
#घोषणा SE_IM5_MASK SE_IM5(0x3f, 1)

/* An SE_R क्रमm inकाष्ठाion.  This is a 16-bit inकाष्ठाion.  */
#घोषणा SE_R(op, xop) (((((अचिन्हित दीर्घ)(op)) & 0x3f) << 10) | (((xop) & 0x3f) << 4))
#घोषणा SE_R_MASK SE_R(0x3f, 0x3f)

/* An SE_RR क्रमm inकाष्ठाion.  This is a 16-bit inकाष्ठाion.  */
#घोषणा SE_RR(op, xop) (((((अचिन्हित दीर्घ)(op)) & 0x3f) << 10) | (((xop) & 0x3) << 8))
#घोषणा SE_RR_MASK SE_RR(0x3f, 3)

/* A VX क्रमm inकाष्ठाion.  */
#घोषणा VX(op, xop) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x7ff))

/* The mask क्रम an VX क्रमm inकाष्ठाion.  */
#घोषणा VX_MASK	VX(0x3f, 0x7ff)

/* A VX_MASK with the VA field fixed.  */
#घोषणा VXVA_MASK (VX_MASK | (0x1f << 16))

/* A VX_MASK with the VB field fixed.  */
#घोषणा VXVB_MASK (VX_MASK | (0x1f << 11))

/* A VX_MASK with the VA and VB fields fixed.  */
#घोषणा VXVAVB_MASK (VX_MASK | (0x1f << 16) | (0x1f << 11))

/* A VX_MASK with the VD and VA fields fixed.  */
#घोषणा VXVDVA_MASK (VX_MASK | (0x1f << 21) | (0x1f << 16))

/* A VX_MASK with a UIMM4 field.  */
#घोषणा VXUIMM4_MASK (VX_MASK | (0x1 << 20))

/* A VX_MASK with a UIMM3 field.  */
#घोषणा VXUIMM3_MASK (VX_MASK | (0x3 << 19))

/* A VX_MASK with a UIMM2 field.  */
#घोषणा VXUIMM2_MASK (VX_MASK | (0x7 << 18))

/* A VX_MASK with a PS field.  */
#घोषणा VXPS_MASK (VX_MASK & ~(0x1 << 9))

/* A VX_MASK with the VA field fixed with a PS field.  */
#घोषणा VXVAPS_MASK ((VX_MASK | (0x1f << 16)) & ~(0x1 << 9))

/* A VA क्रमm inकाष्ठाion.  */
#घोषणा VXA(op, xop) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x03f))

/* The mask क्रम an VA क्रमm inकाष्ठाion.  */
#घोषणा VXA_MASK VXA(0x3f, 0x3f)

/* A VXA_MASK with a SHB field.  */
#घोषणा VXASHB_MASK (VXA_MASK | (1 << 10))

/* A VXR क्रमm inकाष्ठाion.  */
#घोषणा VXR(op, xop, rc) (OP (op) | (((rc) & 1) << 10) | (((अचिन्हित दीर्घ)(xop)) & 0x3ff))

/* The mask क्रम a VXR क्रमm inकाष्ठाion.  */
#घोषणा VXR_MASK VXR(0x3f, 0x3ff, 1)

/* A VX क्रमm inकाष्ठाion with a VA tertiary opcode.  */
#घोषणा VXVA(op, xop, vaop) (VX(op,xop) | (((vaop) & 0x1f) << 16))

#घोषणा VXASH(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1f) << 1))
#घोषणा VXASH_MASK VXASH (0x3f, 0x1f)

/* An X क्रमm inकाष्ठाion.  */
#घोषणा X(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x3ff) << 1))

/* A X क्रमm inकाष्ठाion क्रम Quad-Precision FP Inकाष्ठाions.  */
#घोषणा XVA(op, xop, vaop) (X(op,xop) | (((vaop) & 0x1f) << 16))

/* An EX क्रमm inकाष्ठाion.  */
#घोषणा EX(op, xop) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x7ff))

/* The mask क्रम an EX क्रमm inकाष्ठाion.  */
#घोषणा EX_MASK EX (0x3f, 0x7ff)

/* An XX2 क्रमm inकाष्ठाion.  */
#घोषणा XX2(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1ff) << 2))

/* A XX2 क्रमm inकाष्ठाion with the VA bits specअगरied.  */
#घोषणा XX2VA(op, xop, vaop) (XX2(op,xop) | (((vaop) & 0x1f) << 16))

/* An XX3 क्रमm inकाष्ठाion.  */
#घोषणा XX3(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0xff) << 3))

/* An XX3 क्रमm inकाष्ठाion with the RC bit specअगरied.  */
#घोषणा XX3RC(op, xop, rc) (OP (op) | (((rc) & 1) << 10) | ((((अचिन्हित दीर्घ)(xop)) & 0x7f) << 3))

/* An XX4 क्रमm inकाष्ठाion.  */
#घोषणा XX4(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x3) << 4))

/* A Z क्रमm inकाष्ठाion.  */
#घोषणा Z(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1ff) << 1))

/* An X क्रमm inकाष्ठाion with the RC bit specअगरied.  */
#घोषणा XRC(op, xop, rc) (X ((op), (xop)) | ((rc) & 1))

/* A X क्रमm inकाष्ठाion क्रम Quad-Precision FP Inकाष्ठाions with RC bit.  */
#घोषणा XVARC(op, xop, vaop, rc) (XVA ((op), (xop), (vaop)) | ((rc) & 1))

/* An X क्रमm inकाष्ठाion with the RA bits specअगरied as two ops.  */
#घोषणा XMMF(op, xop, mop0, mop1) (X ((op), (xop)) | ((mop0) & 3) << 19 | ((mop1) & 7) << 16)

/* A Z क्रमm inकाष्ठाion with the RC bit specअगरied.  */
#घोषणा ZRC(op, xop, rc) (Z ((op), (xop)) | ((rc) & 1))

/* The mask क्रम an X क्रमm inकाष्ठाion.  */
#घोषणा X_MASK XRC (0x3f, 0x3ff, 1)

/* The mask क्रम an X क्रमm inकाष्ठाion with the BF bits specअगरied.  */
#घोषणा XBF_MASK (X_MASK | (3 << 21))

/* An X क्रमm रुको inकाष्ठाion with everything filled in except the WC field.  */
#घोषणा XWC_MASK (XRC (0x3f, 0x3ff, 1) | (7 << 23) | RA_MASK | RB_MASK)

/* The mask क्रम an XX1 क्रमm inकाष्ठाion.  */
#घोषणा XX1_MASK X (0x3f, 0x3ff)

/* An XX1_MASK with the RB field fixed.  */
#घोषणा XX1RB_MASK (XX1_MASK | RB_MASK)

/* The mask क्रम an XX2 क्रमm inकाष्ठाion.  */
#घोषणा XX2_MASK (XX2 (0x3f, 0x1ff) | (0x1f << 16))

/* The mask क्रम an XX2 क्रमm inकाष्ठाion with the UIM bits specअगरied.  */
#घोषणा XX2UIM_MASK (XX2 (0x3f, 0x1ff) | (7 << 18))

/* The mask क्रम an XX2 क्रमm inकाष्ठाion with the 4 UIM bits specअगरied.  */
#घोषणा XX2UIM4_MASK (XX2 (0x3f, 0x1ff) | (1 << 20))

/* The mask क्रम an XX2 क्रमm inकाष्ठाion with the BF bits specअगरied.  */
#घोषणा XX2BF_MASK (XX2_MASK | (3 << 21) | (1))

/* The mask क्रम an XX2 क्रमm inकाष्ठाion with the BF and DCMX bits specअगरied.  */
#घोषणा XX2BFD_MASK (XX2 (0x3f, 0x1ff) | 1)

/* The mask क्रम an XX2 क्रमm inकाष्ठाion with a split DCMX bits specअगरied.  */
#घोषणा XX2DCMXS_MASK XX2 (0x3f, 0x1ee)

/* The mask क्रम an XX3 क्रमm inकाष्ठाion.  */
#घोषणा XX3_MASK XX3 (0x3f, 0xff)

/* The mask क्रम an XX3 क्रमm inकाष्ठाion with the BF bits specअगरied.  */
#घोषणा XX3BF_MASK (XX3 (0x3f, 0xff) | (3 << 21) | (1))

/* The mask क्रम an XX3 क्रमm inकाष्ठाion with the DM or SHW bits specअगरied.  */
#घोषणा XX3DM_MASK (XX3 (0x3f, 0x1f) | (1 << 10))
#घोषणा XX3SHW_MASK XX3DM_MASK

/* The mask क्रम an XX4 क्रमm inकाष्ठाion.  */
#घोषणा XX4_MASK XX4 (0x3f, 0x3)

/* An X क्रमm रुको inकाष्ठाion with everything filled in except the WC field.  */
#घोषणा XWC_MASK (XRC (0x3f, 0x3ff, 1) | (7 << 23) | RA_MASK | RB_MASK)

/* The mask क्रम an XMMF क्रमm inकाष्ठाion.  */
#घोषणा XMMF_MASK (XMMF (0x3f, 0x3ff, 3, 7) | (1))

/* The mask क्रम a Z क्रमm inकाष्ठाion.  */
#घोषणा Z_MASK ZRC (0x3f, 0x1ff, 1)
#घोषणा Z2_MASK ZRC (0x3f, 0xff, 1)

/* An X_MASK with the RA/VA field fixed.  */
#घोषणा XRA_MASK (X_MASK | RA_MASK)
#घोषणा XVA_MASK XRA_MASK

/* An XRA_MASK with the A_L/W field clear.  */
#घोषणा XWRA_MASK (XRA_MASK & ~((अचिन्हित दीर्घ) 1 << 16))
#घोषणा XRLA_MASK XWRA_MASK

/* An X_MASK with the RB field fixed.  */
#घोषणा XRB_MASK (X_MASK | RB_MASK)

/* An X_MASK with the RT field fixed.  */
#घोषणा XRT_MASK (X_MASK | RT_MASK)

/* An XRT_MASK mask with the L bits clear.  */
#घोषणा XLRT_MASK (XRT_MASK & ~((अचिन्हित दीर्घ) 0x3 << 21))

/* An X_MASK with the RA and RB fields fixed.  */
#घोषणा XRARB_MASK (X_MASK | RA_MASK | RB_MASK)

/* An XBF_MASK with the RA and RB fields fixed.  */
#घोषणा XBFRARB_MASK (XBF_MASK | RA_MASK | RB_MASK)

/* An XRARB_MASK, but with the L bit clear.  */
#घोषणा XRLARB_MASK (XRARB_MASK & ~((अचिन्हित दीर्घ) 1 << 16))

/* An XRARB_MASK, but with the L bits in a darn inकाष्ठाion clear.  */
#घोषणा XLRAND_MASK (XRARB_MASK & ~((अचिन्हित दीर्घ) 3 << 16))

/* An X_MASK with the RT and RA fields fixed.  */
#घोषणा XRTRA_MASK (X_MASK | RT_MASK | RA_MASK)

/* An X_MASK with the RT and RB fields fixed.  */
#घोषणा XRTRB_MASK (X_MASK | RT_MASK | RB_MASK)

/* An XRTRA_MASK, but with L bit clear.  */
#घोषणा XRTLRA_MASK (XRTRA_MASK & ~((अचिन्हित दीर्घ) 1 << 21))

/* An X_MASK with the RT, RA and RB fields fixed.  */
#घोषणा XRTRARB_MASK (X_MASK | RT_MASK | RA_MASK | RB_MASK)

/* An XRTRARB_MASK, but with L bit clear.  */
#घोषणा XRTLRARB_MASK (XRTRARB_MASK & ~((अचिन्हित दीर्घ) 1 << 21))

/* An XRTRARB_MASK, but with A bit clear.  */
#घोषणा XRTARARB_MASK (XRTRARB_MASK & ~((अचिन्हित दीर्घ) 1 << 25))

/* An XRTRARB_MASK, but with BF bits clear.  */
#घोषणा XRTBFRARB_MASK (XRTRARB_MASK & ~((अचिन्हित दीर्घ) 7 << 23))

/* An X क्रमm inकाष्ठाion with the L bit specअगरied.  */
#घोषणा XOPL(op, xop, l) (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(l)) & 1) << 21))

/* An X क्रमm inकाष्ठाion with the L bits specअगरied.  */
#घोषणा XOPL2(op, xop, l) (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(l)) & 3) << 21))

/* An X क्रमm inकाष्ठाion with the L bit and RC bit specअगरied.  */
#घोषणा XRCL(op, xop, l, rc) (XRC ((op), (xop), (rc)) | ((((अचिन्हित दीर्घ)(l)) & 1) << 21))

/* An X क्रमm inकाष्ठाion with RT fields specअगरied */
#घोषणा XRT(op, xop, rt) (X ((op), (xop)) \
        | ((((अचिन्हित दीर्घ)(rt)) & 0x1f) << 21))

/* An X क्रमm inकाष्ठाion with RT and RA fields specअगरied */
#घोषणा XRTRA(op, xop, rt, ra) (X ((op), (xop)) \
        | ((((अचिन्हित दीर्घ)(rt)) & 0x1f) << 21) \
        | ((((अचिन्हित दीर्घ)(ra)) & 0x1f) << 16))

/* The mask क्रम an X क्रमm comparison inकाष्ठाion.  */
#घोषणा XCMP_MASK (X_MASK | (((अचिन्हित दीर्घ)1) << 22))

/* The mask क्रम an X क्रमm comparison inकाष्ठाion with the L field
   fixed.  */
#घोषणा XCMPL_MASK (XCMP_MASK | (((अचिन्हित दीर्घ)1) << 21))

/* An X क्रमm trap inकाष्ठाion with the TO field specअगरied.  */
#घोषणा XTO(op, xop, to) (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(to)) & 0x1f) << 21))
#घोषणा XTO_MASK (X_MASK | TO_MASK)

/* An X क्रमm tlb inकाष्ठाion with the SH field specअगरied.  */
#घोषणा XTLB(op, xop, sh) (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(sh)) & 0x1f) << 11))
#घोषणा XTLB_MASK (X_MASK | SH_MASK)

/* An X क्रमm sync inकाष्ठाion.  */
#घोषणा XSYNC(op, xop, l) (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(l)) & 3) << 21))

/* An X क्रमm sync inकाष्ठाion with everything filled in except the LS field.  */
#घोषणा XSYNC_MASK (0xff9fffff)

/* An X क्रमm sync inकाष्ठाion with everything filled in except the L and E fields.  */
#घोषणा XSYNCLE_MASK (0xff90ffff)

/* An X_MASK, but with the EH bit clear.  */
#घोषणा XEH_MASK (X_MASK & ~((अचिन्हित दीर्घ )1))

/* An X क्रमm AltiVec dss inकाष्ठाion.  */
#घोषणा XDSS(op, xop, a) (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(a)) & 1) << 25))
#घोषणा XDSS_MASK XDSS(0x3f, 0x3ff, 1)

/* An XFL क्रमm inकाष्ठाion.  */
#घोषणा XFL(op, xop, rc) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x3ff) << 1) | (((अचिन्हित दीर्घ)(rc)) & 1))
#घोषणा XFL_MASK XFL (0x3f, 0x3ff, 1)

/* An X क्रमm isel inकाष्ठाion.  */
#घोषणा XISEL(op, xop)	(OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1f) << 1))
#घोषणा XISEL_MASK	XISEL(0x3f, 0x1f)

/* An XL क्रमm inकाष्ठाion with the LK field set to 0.  */
#घोषणा XL(op, xop) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x3ff) << 1))

/* An XL क्रमm inकाष्ठाion which uses the LK field.  */
#घोषणा XLLK(op, xop, lk) (XL ((op), (xop)) | ((lk) & 1))

/* The mask क्रम an XL क्रमm inकाष्ठाion.  */
#घोषणा XL_MASK XLLK (0x3f, 0x3ff, 1)

/* An XL_MASK with the RT, RA and RB fields fixed, but S bit clear.  */
#घोषणा XLS_MASK ((XL_MASK | RT_MASK | RA_MASK | RB_MASK) & ~(1 << 11))

/* An XL क्रमm inकाष्ठाion which explicitly sets the BO field.  */
#घोषणा XLO(op, bo, xop, lk) \
  (XLLK ((op), (xop), (lk)) | ((((अचिन्हित दीर्घ)(bo)) & 0x1f) << 21))
#घोषणा XLO_MASK (XL_MASK | BO_MASK)

/* An XL क्रमm inकाष्ठाion which explicitly sets the y bit of the BO
   field.  */
#घोषणा XLYLK(op, xop, y, lk) (XLLK ((op), (xop), (lk)) | ((((अचिन्हित दीर्घ)(y)) & 1) << 21))
#घोषणा XLYLK_MASK (XL_MASK | Y_MASK)

/* An XL क्रमm inकाष्ठाion which sets the BO field and the condition
   bits of the BI field.  */
#घोषणा XLOCB(op, bo, cb, xop, lk) \
  (XLO ((op), (bo), (xop), (lk)) | ((((अचिन्हित दीर्घ)(cb)) & 3) << 16))
#घोषणा XLOCB_MASK XLOCB (0x3f, 0x1f, 0x3, 0x3ff, 1)

/* An XL_MASK or XLYLK_MASK or XLOCB_MASK with the BB field fixed.  */
#घोषणा XLBB_MASK (XL_MASK | BB_MASK)
#घोषणा XLYBB_MASK (XLYLK_MASK | BB_MASK)
#घोषणा XLBOCBBB_MASK (XLOCB_MASK | BB_MASK)

/* A mask क्रम branch inकाष्ठाions using the BH field.  */
#घोषणा XLBH_MASK (XL_MASK | (0x1c << 11))

/* An XL_MASK with the BO and BB fields fixed.  */
#घोषणा XLBOBB_MASK (XL_MASK | BO_MASK | BB_MASK)

/* An XL_MASK with the BO, BI and BB fields fixed.  */
#घोषणा XLBOBIBB_MASK (XL_MASK | BO_MASK | BI_MASK | BB_MASK)

/* An X क्रमm mbar inकाष्ठाion with MO field.  */
#घोषणा XMBAR(op, xop, mo) (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(mo)) & 1) << 21))

/* An XO क्रमm inकाष्ठाion.  */
#घोषणा XO(op, xop, oe, rc) \
  (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1ff) << 1) | ((((अचिन्हित दीर्घ)(oe)) & 1) << 10) | (((अचिन्हित दीर्घ)(rc)) & 1))
#घोषणा XO_MASK XO (0x3f, 0x1ff, 1, 1)

/* An XO_MASK with the RB field fixed.  */
#घोषणा XORB_MASK (XO_MASK | RB_MASK)

/* An XOPS क्रमm inकाष्ठाion क्रम paired singles.  */
#घोषणा XOPS(op, xop, rc) \
  (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x3ff) << 1) | (((अचिन्हित दीर्घ)(rc)) & 1))
#घोषणा XOPS_MASK XOPS (0x3f, 0x3ff, 1)


/* An XS क्रमm inकाष्ठाion.  */
#घोषणा XS(op, xop, rc) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x1ff) << 2) | (((अचिन्हित दीर्घ)(rc)) & 1))
#घोषणा XS_MASK XS (0x3f, 0x1ff, 1)

/* A mask क्रम the FXM version of an XFX क्रमm inकाष्ठाion.  */
#घोषणा XFXFXM_MASK (X_MASK | (1 << 11) | (1 << 20))

/* An XFX क्रमm inकाष्ठाion with the FXM field filled in.  */
#घोषणा XFXM(op, xop, fxm, p4) \
  (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(fxm)) & 0xff) << 12) \
   | ((अचिन्हित दीर्घ)(p4) << 20))

/* An XFX क्रमm inकाष्ठाion with the SPR field filled in.  */
#घोषणा XSPR(op, xop, spr) \
  (X ((op), (xop)) | ((((अचिन्हित दीर्घ)(spr)) & 0x1f) << 16) | ((((अचिन्हित दीर्घ)(spr)) & 0x3e0) << 6))
#घोषणा XSPR_MASK (X_MASK | SPR_MASK)

/* An XFX क्रमm inकाष्ठाion with the SPR field filled in except क्रम the
   SPRBAT field.  */
#घोषणा XSPRBAT_MASK (XSPR_MASK &~ SPRBAT_MASK)

/* An XFX क्रमm inकाष्ठाion with the SPR field filled in except क्रम the
   SPRG field.  */
#घोषणा XSPRG_MASK (XSPR_MASK & ~(0x1f << 16))

/* An X क्रमm inकाष्ठाion with everything filled in except the E field.  */
#घोषणा XE_MASK (0xffff7fff)

/* An X क्रमm user context inकाष्ठाion.  */
#घोषणा XUC(op, xop)  (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x1f))
#घोषणा XUC_MASK      XUC(0x3f, 0x1f)

/* An XW क्रमm inकाष्ठाion.  */
#घोषणा XW(op, xop, rc) (OP (op) | ((((अचिन्हित दीर्घ)(xop)) & 0x3f) << 1) | ((rc) & 1))
/* The mask क्रम a G क्रमm inकाष्ठाion. rc not supported at present.  */
#घोषणा XW_MASK XW (0x3f, 0x3f, 0)

/* An APU क्रमm inकाष्ठाion.  */
#घोषणा APU(op, xop, rc) (OP (op) | (((अचिन्हित दीर्घ)(xop)) & 0x3ff) << 1 | ((rc) & 1))

/* The mask क्रम an APU क्रमm inकाष्ठाion.  */
#घोषणा APU_MASK APU (0x3f, 0x3ff, 1)
#घोषणा APU_RT_MASK (APU_MASK | RT_MASK)
#घोषणा APU_RA_MASK (APU_MASK | RA_MASK)

/* The BO encodings used in extended conditional branch mnemonics.  */
#घोषणा BODNZF	(0x0)
#घोषणा BODNZFP	(0x1)
#घोषणा BODZF	(0x2)
#घोषणा BODZFP	(0x3)
#घोषणा BODNZT	(0x8)
#घोषणा BODNZTP	(0x9)
#घोषणा BODZT	(0xa)
#घोषणा BODZTP	(0xb)

#घोषणा BOF	(0x4)
#घोषणा BOFP	(0x5)
#घोषणा BOFM4	(0x6)
#घोषणा BOFP4	(0x7)
#घोषणा BOT	(0xc)
#घोषणा BOTP	(0xd)
#घोषणा BOTM4	(0xe)
#घोषणा BOTP4	(0xf)

#घोषणा BODNZ	(0x10)
#घोषणा BODNZP	(0x11)
#घोषणा BODZ	(0x12)
#घोषणा BODZP	(0x13)
#घोषणा BODNZM4 (0x18)
#घोषणा BODNZP4 (0x19)
#घोषणा BODZM4	(0x1a)
#घोषणा BODZP4	(0x1b)

#घोषणा BOU	(0x14)

/* The BO16 encodings used in extended VLE conditional branch mnemonics.  */
#घोषणा BO16F   (0x0)
#घोषणा BO16T   (0x1)

/* The BO32 encodings used in extended VLE conditional branch mnemonics.  */
#घोषणा BO32F   (0x0)
#घोषणा BO32T   (0x1)
#घोषणा BO32DNZ (0x2)
#घोषणा BO32DZ  (0x3)

/* The BI condition bit encodings used in extended conditional branch
   mnemonics.  */
#घोषणा CBLT	(0)
#घोषणा CBGT	(1)
#घोषणा CBEQ	(2)
#घोषणा CBSO	(3)

/* The TO encodings used in extended trap mnemonics.  */
#घोषणा TOLGT	(0x1)
#घोषणा TOLLT	(0x2)
#घोषणा TOEQ	(0x4)
#घोषणा TOLGE	(0x5)
#घोषणा TOLNL	(0x5)
#घोषणा TOLLE	(0x6)
#घोषणा TOLNG	(0x6)
#घोषणा TOGT	(0x8)
#घोषणा TOGE	(0xc)
#घोषणा TONL	(0xc)
#घोषणा TOLT	(0x10)
#घोषणा TOLE	(0x14)
#घोषणा TONG	(0x14)
#घोषणा TONE	(0x18)
#घोषणा TOU	(0x1f)

/* Smaller names क्रम the flags so each entry in the opcodes table will
   fit on a single line.  */
#अघोषित	PPC
#घोषणा PPC	PPC_OPCODE_PPC
#घोषणा PPCCOM	PPC_OPCODE_PPC | PPC_OPCODE_COMMON
#घोषणा POWER4	PPC_OPCODE_POWER4
#घोषणा POWER5	PPC_OPCODE_POWER5
#घोषणा POWER6	PPC_OPCODE_POWER6
#घोषणा POWER7	PPC_OPCODE_POWER7
#घोषणा POWER8	PPC_OPCODE_POWER8
#घोषणा POWER9	PPC_OPCODE_POWER9
#घोषणा CELL	PPC_OPCODE_CELL
#घोषणा PPC64	PPC_OPCODE_64 | PPC_OPCODE_64_BRIDGE
#घोषणा NON32	(PPC_OPCODE_64 | PPC_OPCODE_POWER4	\
		 | PPC_OPCODE_EFS | PPC_OPCODE_E500MC | PPC_OPCODE_TITAN)
#घोषणा PPC403	PPC_OPCODE_403
#घोषणा PPC405	PPC_OPCODE_405
#घोषणा PPC440	PPC_OPCODE_440
#घोषणा PPC464	PPC440
#घोषणा PPC476	PPC_OPCODE_476
#घोषणा PPC750	PPC_OPCODE_750
#घोषणा PPC7450 PPC_OPCODE_7450
#घोषणा PPC860	PPC_OPCODE_860
#घोषणा PPCPS	PPC_OPCODE_PPCPS
#घोषणा PPCVEC	PPC_OPCODE_ALTIVEC
#घोषणा PPCVEC2	PPC_OPCODE_ALTIVEC2
#घोषणा PPCVEC3	PPC_OPCODE_ALTIVEC2
#घोषणा PPCVSX	PPC_OPCODE_VSX
#घोषणा PPCVSX2	PPC_OPCODE_VSX
#घोषणा PPCVSX3	PPC_OPCODE_VSX3
#घोषणा POWER	PPC_OPCODE_POWER
#घोषणा POWER2	PPC_OPCODE_POWER | PPC_OPCODE_POWER2
#घोषणा PWR2COM PPC_OPCODE_POWER | PPC_OPCODE_POWER2 | PPC_OPCODE_COMMON
#घोषणा PPCPWR2 PPC_OPCODE_PPC | PPC_OPCODE_POWER | PPC_OPCODE_POWER2 | PPC_OPCODE_COMMON
#घोषणा COM	PPC_OPCODE_POWER | PPC_OPCODE_PPC | PPC_OPCODE_COMMON
#घोषणा M601	PPC_OPCODE_POWER | PPC_OPCODE_601
#घोषणा PWRCOM	PPC_OPCODE_POWER | PPC_OPCODE_601 | PPC_OPCODE_COMMON
#घोषणा MFDEC1	PPC_OPCODE_POWER
#घोषणा MFDEC2	PPC_OPCODE_PPC | PPC_OPCODE_601 | PPC_OPCODE_BOOKE | PPC_OPCODE_TITAN
#घोषणा BOOKE	PPC_OPCODE_BOOKE
#घोषणा NO371	PPC_OPCODE_BOOKE | PPC_OPCODE_PPCPS | PPC_OPCODE_EFS
#घोषणा PPCE300 PPC_OPCODE_E300
#घोषणा PPCSPE	PPC_OPCODE_SPE
#घोषणा PPCISEL PPC_OPCODE_ISEL
#घोषणा PPCEFS	PPC_OPCODE_EFS
#घोषणा PPCBRLK PPC_OPCODE_BRLOCK
#घोषणा PPCPMR	PPC_OPCODE_PMR
#घोषणा PPCTMR  PPC_OPCODE_TMR
#घोषणा PPCCHLK PPC_OPCODE_CACHELCK
#घोषणा PPCRFMCI	PPC_OPCODE_RFMCI
#घोषणा E500MC  PPC_OPCODE_E500MC
#घोषणा PPCA2	PPC_OPCODE_A2
#घोषणा TITAN   PPC_OPCODE_TITAN
#घोषणा MULHW   PPC_OPCODE_405 | PPC_OPCODE_440 | TITAN
#घोषणा E500	PPC_OPCODE_E500
#घोषणा E6500	PPC_OPCODE_E6500
#घोषणा PPCVLE  PPC_OPCODE_VLE
#घोषणा PPCHTM  PPC_OPCODE_HTM
#घोषणा E200Z4  PPC_OPCODE_E200Z4
/* The list of embedded processors that use the embedded opeअक्रम ordering
   क्रम the 3 opeअक्रम dcbt and dcbtst inकाष्ठाions.  */
#घोषणा DCBT_EO	(PPC_OPCODE_E500 | PPC_OPCODE_E500MC | PPC_OPCODE_476 \
		 | PPC_OPCODE_A2)



/* The opcode table.

   The क्रमmat of the opcode table is:

   NAME		OPCODE		MASK	     FLAGS	ANTI		अणुOPERANDSपूर्ण

   NAME is the name of the inकाष्ठाion.
   OPCODE is the inकाष्ठाion opcode.
   MASK is the opcode mask; this is used to tell the disassembler
     which bits in the actual opcode must match OPCODE.
   FLAGS are flags indicating which processors support the inकाष्ठाion.
   ANTI indicates which processors करोn't support the inकाष्ठाion.
   OPERANDS is the list of opeअक्रमs.

   The disassembler पढ़ोs the table in order and prपूर्णांकs the first
   inकाष्ठाion which matches, so this table is sorted to put more
   specअगरic inकाष्ठाions beक्रमe more general inकाष्ठाions.

   This table must be sorted by major opcode.  Please try to keep it
   vaguely sorted within major opcode too, except of course where
   स्थिरrained otherwise by disassembler operation.  */

स्थिर काष्ठा घातerpc_opcode घातerpc_opcodes[] = अणु
अणु"attn",	X(0,256),	X_MASK,	  POWER4|PPCA2,	PPC476|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"tdlgti",	OPTO(2,TOLGT),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdllti",	OPTO(2,TOLLT),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdeqi",	OPTO(2,TOEQ),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdlgei",	OPTO(2,TOLGE),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdlnli",	OPTO(2,TOLNL),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdllei",	OPTO(2,TOLLE),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdlngi",	OPTO(2,TOLNG),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdgti",	OPTO(2,TOGT),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdgei",	OPTO(2,TOGE),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdnli",	OPTO(2,TONL),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdlti",	OPTO(2,TOLT),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdlei",	OPTO(2,TOLE),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdngi",	OPTO(2,TONG),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdnei",	OPTO(2,TONE),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdui",	OPTO(2,TOU),	OPTO_MASK,   PPC64,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tdi",		OP(2),		OP_MASK,     PPC64,	PPCVLE,		अणुTO, RA, SIपूर्णपूर्ण,

अणु"twlgti",	OPTO(3,TOLGT),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tlgti",	OPTO(3,TOLGT),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twllti",	OPTO(3,TOLLT),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tllti",	OPTO(3,TOLLT),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tweqi",	OPTO(3,TOEQ),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"teqi",	OPTO(3,TOEQ),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twlgei",	OPTO(3,TOLGE),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tlgei",	OPTO(3,TOLGE),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twlnli",	OPTO(3,TOLNL),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tlnli",	OPTO(3,TOLNL),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twllei",	OPTO(3,TOLLE),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tllei",	OPTO(3,TOLLE),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twlngi",	OPTO(3,TOLNG),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tlngi",	OPTO(3,TOLNG),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twgti",	OPTO(3,TOGT),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tgti",	OPTO(3,TOGT),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twgei",	OPTO(3,TOGE),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tgei",	OPTO(3,TOGE),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twnli",	OPTO(3,TONL),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tnli",	OPTO(3,TONL),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twlti",	OPTO(3,TOLT),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tlti",	OPTO(3,TOLT),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twlei",	OPTO(3,TOLE),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tlei",	OPTO(3,TOLE),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twngi",	OPTO(3,TONG),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tngi",	OPTO(3,TONG),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twnei",	OPTO(3,TONE),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tnei",	OPTO(3,TONE),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twui",	OPTO(3,TOU),	OPTO_MASK,   PPCCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"tui",		OPTO(3,TOU),	OPTO_MASK,   PWRCOM,	PPCVLE,		अणुRA, SIपूर्णपूर्ण,
अणु"twi",		OP(3),		OP_MASK,     PPCCOM,	PPCVLE,		अणुTO, RA, SIपूर्णपूर्ण,
अणु"ti",		OP(3),		OP_MASK,     PWRCOM,	PPCVLE,		अणुTO, RA, SIपूर्णपूर्ण,

अणु"ps_cmpu0",	X  (4,	 0),	XBF_MASK,    PPCPS,	0,		अणुBF, FRA, FRBपूर्णपूर्ण,
अणु"vaddubm",	VX (4,	 0),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmul10cuq",	VX (4,	 1),	VXVB_MASK,   PPCVEC3,	0,		अणुVD, VAपूर्णपूर्ण,
अणु"vmaxub",	VX (4,	 2),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrlb",	VX (4,	 4),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpequb",	VXR(4,	 6,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpneb",	VXR(4,	 7,0),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmuloub",	VX (4,	 8),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vaddfp",	VX (4,	10),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"psq_lx",	XW (4,	 6,0),	XW_MASK,     PPCPS,	0,		अणुFRT,RA,RB,PSWM,PSQMपूर्णपूर्ण,
अणु"vmrghb",	VX (4,	12),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"psq_stx",	XW (4,	 7,0),	XW_MASK,     PPCPS,	0,		अणुFRS,RA,RB,PSWM,PSQMपूर्णपूर्ण,
अणु"vpkuhum",	VX (4,	14),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"mulhhwu",	XRC(4,	 8,0),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulhhwu.",	XRC(4,	 8,1),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_sum0",	A  (4,	10,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_sum0.",	A  (4,	10,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_sum1",	A  (4,	11,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_sum1.",	A  (4,	11,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_muls0",	A  (4,	12,0),	AFRB_MASK,   PPCPS,	0,		अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"machhwu",	XO (4,	12,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_muls0.",	A  (4,	12,1),	AFRB_MASK,   PPCPS,	0,		अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"machhwu.",	XO (4,	12,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_muls1",	A  (4,	13,0),	AFRB_MASK,   PPCPS,	0,		अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"ps_muls1.",	A  (4,	13,1),	AFRB_MASK,   PPCPS,	0,		अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"ps_madds0",	A  (4,	14,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_madds0.",	A  (4,	14,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_madds1",	A  (4,	15,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_madds1.",	A  (4,	15,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"vmhaddshs",	VXA(4,	32),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"vmhraddshs",	VXA(4,	33),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"vmladduhm",	VXA(4,	34),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"vmsumudm",	VXA(4,	35),	VXA_MASK,    PPCVEC3,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_div",	A  (4,	18,0),	AFRC_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"vmsumubm",	VXA(4,	36),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_div.",	A  (4,	18,1),	AFRC_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"vmsummbm",	VXA(4,	37),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"vmsumuhm",	VXA(4,	38),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"vmsumuhs",	VXA(4,	39),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_sub",	A  (4,	20,0),	AFRC_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"vmsumshm",	VXA(4,	40),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_sub.",	A  (4,	20,1),	AFRC_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"vmsumshs",	VXA(4,	41),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_add",	A  (4,	21,0),	AFRC_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"vsel",	VXA(4,	42),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_add.",	A  (4,	21,1),	AFRC_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"vperm",	VXA(4,	43),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"vsldoi",	VXA(4,	44),	VXASHB_MASK, PPCVEC,	0,		अणुVD, VA, VB, SHBपूर्णपूर्ण,
अणु"vpermxor",	VXA(4,	45),	VXA_MASK,    PPCVEC2,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_sel",	A  (4,	23,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"vmaddfp",	VXA(4,	46),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VC, VBपूर्णपूर्ण,
अणु"ps_sel.",	A  (4,	23,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"vnmsubfp",	VXA(4,	47),	VXA_MASK,    PPCVEC,	0,		अणुVD, VA, VC, VBपूर्णपूर्ण,
अणु"ps_res",	A  (4,	24,0), AFRAFRC_MASK, PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"maddhd",	VXA(4,	48),	VXA_MASK,    POWER9,	0,		अणुRT, RA, RB, RCपूर्णपूर्ण,
अणु"ps_res.",	A  (4,	24,1), AFRAFRC_MASK, PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"maddhdu",	VXA(4,	49),	VXA_MASK,    POWER9,	0,		अणुRT, RA, RB, RCपूर्णपूर्ण,
अणु"ps_mul",	A  (4,	25,0),	AFRB_MASK,   PPCPS,	0,		अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"ps_mul.",	A  (4,	25,1),	AFRB_MASK,   PPCPS,	0,		अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"maddld",	VXA(4,	51),	VXA_MASK,    POWER9,	0,		अणुRT, RA, RB, RCपूर्णपूर्ण,
अणु"ps_rsqrte",	A  (4,	26,0), AFRAFRC_MASK, PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"ps_rsqrte.",	A  (4,	26,1), AFRAFRC_MASK, PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"ps_msub",	A  (4,	28,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_msub.",	A  (4,	28,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_madd",	A  (4,	29,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"ps_madd.",	A  (4,	29,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"vpermr",	VXA(4,	59),	VXA_MASK,    PPCVEC3,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_nmsub",	A  (4,	30,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"vaddeuqm",	VXA(4,	60),	VXA_MASK,    PPCVEC2,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_nmsub.",	A  (4,	30,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"vaddecuq",	VXA(4,	61),	VXA_MASK,    PPCVEC2,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_nmadd",	A  (4,	31,0),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"vsubeuqm",	VXA(4,	62),	VXA_MASK,    PPCVEC2,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_nmadd.",	A  (4,	31,1),	A_MASK,	     PPCPS,	0,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"vsubecuq",	VXA(4,	63),	VXA_MASK,    PPCVEC2,	0,		अणुVD, VA, VB, VCपूर्णपूर्ण,
अणु"ps_cmpo0",	X  (4,	32),	XBF_MASK,    PPCPS,	0,		अणुBF, FRA, FRBपूर्णपूर्ण,
अणु"vadduhm",	VX (4,	64),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmul10ecuq",	VX (4,	65),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmaxuh",	VX (4,	66),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrlh",	VX (4,	68),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpequh",	VXR(4,	70,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpneh",	VXR(4,	71,0),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmulouh",	VX (4,	72),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vsubfp",	VX (4,	74),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"psq_lux",	XW (4,	38,0),	XW_MASK,     PPCPS,	0,		अणुFRT,RA,RB,PSWM,PSQMपूर्णपूर्ण,
अणु"vmrghh",	VX (4,	76),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"psq_stux",	XW (4,	39,0),	XW_MASK,     PPCPS,	0,		अणुFRS,RA,RB,PSWM,PSQMपूर्णपूर्ण,
अणु"vpkuwum",	VX (4,	78),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"ps_neg",	XRC(4,	40,0),	XRA_MASK,    PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"mulhhw",	XRC(4,	40,0),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_neg.",	XRC(4,	40,1),	XRA_MASK,    PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"mulhhw.",	XRC(4,	40,1),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"machhw",	XO (4,	44,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"machhw.",	XO (4,	44,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmachhw",	XO (4,	46,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmachhw.",	XO (4,	46,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_cmpu1",	X  (4,	64),	XBF_MASK,    PPCPS,	0,		अणुBF, FRA, FRBपूर्णपूर्ण,
अणु"vadduwm",	VX (4,	128),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmaxuw",	VX (4,	130),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrlw",	VX (4,	132),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrlwmi",	VX (4,	133),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpequw",	VXR(4,	134,0), VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpnew",	VXR(4,	135,0),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmulouw",	VX (4,	136),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmuluwm",	VX (4,	137),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmrghw",	VX (4,	140),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vpkuhus",	VX (4,	142),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"ps_mr",	XRC(4,	72,0),	XRA_MASK,    PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"ps_mr.",	XRC(4,	72,1),	XRA_MASK,    PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"machhwsu",	XO (4,	76,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"machhwsu.",	XO (4,	76,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_cmpo1",	X  (4,	96),	XBF_MASK,    PPCPS,	0,		अणुBF, FRA, FRBपूर्णपूर्ण,
अणु"vaddudm",	VX (4, 192),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmaxud",	VX (4, 194),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrld",	VX (4, 196),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrldmi",	VX (4, 197),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpeqfp",	VXR(4, 198,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpequd",	VXR(4, 199,0),	VXR_MASK,    PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vpkuwus",	VX (4, 206),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"machhws",	XO (4, 108,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"machhws.",	XO (4, 108,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmachhws",	XO (4, 110,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmachhws.",	XO (4, 110,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vadduqm",	VX (4, 256),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmaxsb",	VX (4, 258),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vslb",	VX (4, 260),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpnezb",	VXR(4, 263,0),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmulosb",	VX (4, 264),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrefp",	VX (4, 266),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vmrglb",	VX (4, 268),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vpkshus",	VX (4, 270),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"ps_nabs",	XRC(4, 136,0),	XRA_MASK,    PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"mulchwu",	XRC(4, 136,0),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_nabs.",	XRC(4, 136,1),	XRA_MASK,    PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"mulchwu.",	XRC(4, 136,1),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"macchwu",	XO (4, 140,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"macchwu.",	XO (4, 140,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vaddcuq",	VX (4, 320),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmaxsh",	VX (4, 322),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vslh",	VX (4, 324),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpnezh",	VXR(4, 327,0),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmulosh",	VX (4, 328),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrsqrtefp",	VX (4, 330),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vmrglh",	VX (4, 332),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vpkswus",	VX (4, 334),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"mulchw",	XRC(4, 168,0),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulchw.",	XRC(4, 168,1),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"macchw",	XO (4, 172,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"macchw.",	XO (4, 172,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmacchw",	XO (4, 174,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmacchw.",	XO (4, 174,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vaddcuw",	VX (4, 384),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmaxsw",	VX (4, 386),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vslw",	VX (4, 388),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrlwnm",	VX (4, 389),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpnezw",	VXR(4, 391,0),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmulosw",	VX (4, 392),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vexptefp",	VX (4, 394),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vmrglw",	VX (4, 396),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vpkshss",	VX (4, 398),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"macchwsu",	XO (4, 204,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"macchwsu.",	XO (4, 204,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vmaxsd",	VX (4, 450),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vsl",		VX (4, 452),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrldnm",	VX (4, 453),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgefp",	VXR(4, 454,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vlogefp",	VX (4, 458),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vpkswss",	VX (4, 462),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"macchws",	XO (4, 236,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"macchws.",	XO (4, 236,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmacchws",	XO (4, 238,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmacchws.",	XO (4, 238,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evaddw",	VX (4, 512),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vaddubs",	VX (4, 512),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmul10uq",	VX (4, 513),	VXVB_MASK,   PPCVEC3,	0,		अणुVD, VAपूर्णपूर्ण,
अणु"evaddiw",	VX (4, 514),	VX_MASK,     PPCSPE,	0,		अणुRS, RB, UIMMपूर्णपूर्ण,
अणु"vminub",	VX (4, 514),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evsubfw",	VX (4, 516),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evsubw",	VX (4, 516),	VX_MASK,     PPCSPE,	0,		अणुRS, RB, RAपूर्णपूर्ण,
अणु"vsrb",	VX (4, 516),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evsubifw",	VX (4, 518),	VX_MASK,     PPCSPE,	0,		अणुRS, UIMM, RBपूर्णपूर्ण,
अणु"evsubiw",	VX (4, 518),	VX_MASK,     PPCSPE,	0,		अणुRS, RB, UIMMपूर्णपूर्ण,
अणु"vcmpgtub",	VXR(4, 518,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evabs",	VX (4, 520),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vmuleub",	VX (4, 520),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evneg",	VX (4, 521),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evextsb",	VX (4, 522),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vrfin",	VX (4, 522),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"evextsh",	VX (4, 523),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evrndw",	VX (4, 524),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vspltb",	VX (4, 524),   VXUIMM4_MASK, PPCVEC,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"vextractub",	VX (4, 525),   VXUIMM4_MASK, PPCVEC3,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"evcntlzw",	VX (4, 525),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evcntlsw",	VX (4, 526),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vupkhsb",	VX (4, 526),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"brinc",	VX (4, 527),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"ps_abs",	XRC(4, 264,0),	XRA_MASK,    PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"ps_abs.",	XRC(4, 264,1),	XRA_MASK,    PPCPS,	0,		अणुFRT, FRBपूर्णपूर्ण,
अणु"evand",	VX (4, 529),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evandc",	VX (4, 530),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evxor",	VX (4, 534),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmr",	VX (4, 535),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, BBAपूर्णपूर्ण,
अणु"evor",	VX (4, 535),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evnor",	VX (4, 536),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evnot",	VX (4, 536),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, BBAपूर्णपूर्ण,
अणु"get",		APU(4, 268,0),	APU_RA_MASK, PPC405,	0,		अणुRT, FSLपूर्णपूर्ण,
अणु"eveqv",	VX (4, 537),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evorc",	VX (4, 539),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evnand",	VX (4, 542),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evsrwu",	VX (4, 544),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evsrws",	VX (4, 545),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evsrwiu",	VX (4, 546),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, EVUIMMपूर्णपूर्ण,
अणु"evsrwis",	VX (4, 547),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, EVUIMMपूर्णपूर्ण,
अणु"evslw",	VX (4, 548),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evslwi",	VX (4, 550),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, EVUIMMपूर्णपूर्ण,
अणु"evrlw",	VX (4, 552),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evsplati",	VX (4, 553),	VX_MASK,     PPCSPE,	0,		अणुRS, SIMMपूर्णपूर्ण,
अणु"evrlwi",	VX (4, 554),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, EVUIMMपूर्णपूर्ण,
अणु"evsplatfi",	VX (4, 555),	VX_MASK,     PPCSPE,	0,		अणुRS, SIMMपूर्णपूर्ण,
अणु"evmergehi",	VX (4, 556),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmergelo",	VX (4, 557),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmergehilo",	VX (4, 558),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmergelohi",	VX (4, 559),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evcmpgtu",	VX (4, 560),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"evcmpgts",	VX (4, 561),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"evcmpltu",	VX (4, 562),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"evcmplts",	VX (4, 563),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"evcmpeq",	VX (4, 564),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"cget",	APU(4, 284,0),	APU_RA_MASK, PPC405,	0,		अणुRT, FSLपूर्णपूर्ण,
अणु"vadduhs",	VX (4, 576),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmul10euq",	VX (4, 577),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vminuh",	VX (4, 578),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vsrh",	VX (4, 580),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtuh",	VXR(4, 582,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmuleuh",	VX (4, 584),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vrfiz",	VX (4, 586),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vsplth",	VX (4, 588),   VXUIMM3_MASK, PPCVEC,	0,		अणुVD, VB, UIMM3पूर्णपूर्ण,
अणु"vextractuh",	VX (4, 589),   VXUIMM4_MASK, PPCVEC3,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"vupkhsh",	VX (4, 590),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"nget",	APU(4, 300,0),	APU_RA_MASK, PPC405,	0,		अणुRT, FSLपूर्णपूर्ण,
अणु"evsel",	EVSEL(4,79),	EVSEL_MASK,  PPCSPE,	0,		अणुRS, RA, RB, CRFSपूर्णपूर्ण,
अणु"ncget",	APU(4, 316,0),	APU_RA_MASK, PPC405,	0,		अणुRT, FSLपूर्णपूर्ण,
अणु"evfsadd",	VX (4, 640),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vadduws",	VX (4, 640),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evfssub",	VX (4, 641),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vminuw",	VX (4, 642),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evfsabs",	VX (4, 644),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vsrw",	VX (4, 644),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evfsnabs",	VX (4, 645),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evfsneg",	VX (4, 646),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vcmpgtuw",	VXR(4, 646,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmuleuw",	VX (4, 648),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evfsmul",	VX (4, 648),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evfsdiv",	VX (4, 649),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vrfip",	VX (4, 650),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"evfscmpgt",	VX (4, 652),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"vspltw",	VX (4, 652),   VXUIMM2_MASK, PPCVEC,	0,		अणुVD, VB, UIMM2पूर्णपूर्ण,
अणु"vextractuw",	VX (4, 653),   VXUIMM4_MASK, PPCVEC3,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"evfscmplt",	VX (4, 653),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"evfscmpeq",	VX (4, 654),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"vupklsb",	VX (4, 654),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"evfscfui",	VX (4, 656),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfscfsi",	VX (4, 657),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfscfuf",	VX (4, 658),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfscfsf",	VX (4, 659),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfsctui",	VX (4, 660),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfsctsi",	VX (4, 661),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfsctuf",	VX (4, 662),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfsctsf",	VX (4, 663),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfsctuiz",	VX (4, 664),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"put",		APU(4, 332,0),	APU_RT_MASK, PPC405,	0,		अणुRA, FSLपूर्णपूर्ण,
अणु"evfsctsiz",	VX (4, 666),	VX_MASK,     PPCSPE,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"evfststgt",	VX (4, 668),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"evfststlt",	VX (4, 669),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"evfststeq",	VX (4, 670),	VX_MASK,     PPCSPE,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"cput",	APU(4, 348,0),	APU_RT_MASK, PPC405,	0,		अणुRA, FSLपूर्णपूर्ण,
अणु"efsadd",	VX (4, 704),	VX_MASK,     PPCEFS,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"efssub",	VX (4, 705),	VX_MASK,     PPCEFS,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vminud",	VX (4, 706),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"efsabs",	VX (4, 708),	VX_MASK,     PPCEFS,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vsr",		VX (4, 708),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"efsnabs",	VX (4, 709),	VX_MASK,     PPCEFS,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"efsneg",	VX (4, 710),	VX_MASK,     PPCEFS,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vcmpgtfp",	VXR(4, 710,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtud",	VXR(4, 711,0),	VXR_MASK,    PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"efsmul",	VX (4, 712),	VX_MASK,     PPCEFS,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"efsdiv",	VX (4, 713),	VX_MASK,     PPCEFS,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vrfim",	VX (4, 714),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"efscmpgt",	VX (4, 716),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"vextractd",	VX (4, 717),   VXUIMM4_MASK, PPCVEC3,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"efscmplt",	VX (4, 717),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efscmpeq",	VX (4, 718),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"vupklsh",	VX (4, 718),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"efscfd",	VX (4, 719),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efscfui",	VX (4, 720),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efscfsi",	VX (4, 721),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efscfuf",	VX (4, 722),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efscfsf",	VX (4, 723),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efsctui",	VX (4, 724),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efsctsi",	VX (4, 725),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efsctuf",	VX (4, 726),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efsctsf",	VX (4, 727),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efsctuiz",	VX (4, 728),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"nput",	APU(4, 364,0),	APU_RT_MASK, PPC405,	0,		अणुRA, FSLपूर्णपूर्ण,
अणु"efsctsiz",	VX (4, 730),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efststgt",	VX (4, 732),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efststlt",	VX (4, 733),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efststeq",	VX (4, 734),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efdadd",	VX (4, 736),	VX_MASK,     PPCEFS,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"efdsub",	VX (4, 737),	VX_MASK,     PPCEFS,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"efdcfuid",	VX (4, 738),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdcfsid",	VX (4, 739),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdabs",	VX (4, 740),	VX_MASK,     PPCEFS,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"efdnabs",	VX (4, 741),	VX_MASK,     PPCEFS,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"efdneg",	VX (4, 742),	VX_MASK,     PPCEFS,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"efdmul",	VX (4, 744),	VX_MASK,     PPCEFS,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"efddiv",	VX (4, 745),	VX_MASK,     PPCEFS,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"efdctuidz",	VX (4, 746),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdctsidz",	VX (4, 747),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdcmpgt",	VX (4, 748),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efdcmplt",	VX (4, 749),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efdcmpeq",	VX (4, 750),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efdcfs",	VX (4, 751),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdcfui",	VX (4, 752),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdcfsi",	VX (4, 753),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdcfuf",	VX (4, 754),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdcfsf",	VX (4, 755),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdctui",	VX (4, 756),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdctsi",	VX (4, 757),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdctuf",	VX (4, 758),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdctsf",	VX (4, 759),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdctuiz",	VX (4, 760),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"ncput",	APU(4, 380,0),	APU_RT_MASK, PPC405,	0,		अणुRA, FSLपूर्णपूर्ण,
अणु"efdctsiz",	VX (4, 762),	VX_MASK,     PPCEFS,	0,		अणुRS, RBपूर्णपूर्ण,
अणु"efdtstgt",	VX (4, 764),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efdtstlt",	VX (4, 765),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"efdtsteq",	VX (4, 766),	VX_MASK,     PPCEFS,	0,		अणुCRFD, RA, RBपूर्णपूर्ण,
अणु"evlddx",	VX (4, 768),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vaddsbs",	VX (4, 768),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evldd",	VX (4, 769),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_8, RAपूर्णपूर्ण,
अणु"evldwx",	VX (4, 770),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vminsb",	VX (4, 770),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evldw",	VX (4, 771),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_8, RAपूर्णपूर्ण,
अणु"evldhx",	VX (4, 772),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vsrab",	VX (4, 772),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evldh",	VX (4, 773),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_8, RAपूर्णपूर्ण,
अणु"vcmpgtsb",	VXR(4, 774,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evlhhesplatx",VX (4, 776),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vmulesb",	VX (4, 776),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evlhhesplat",	VX (4, 777),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_2, RAपूर्णपूर्ण,
अणु"vcfux",	VX (4, 778),	VX_MASK,     PPCVEC,	0,		अणुVD, VB, UIMMपूर्णपूर्ण,
अणु"vcuxwfp",	VX (4, 778),	VX_MASK,     PPCVEC,	0,		अणुVD, VB, UIMMपूर्णपूर्ण,
अणु"evlhhousplatx",VX(4, 780),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vspltisb",	VX (4, 780),	VXVB_MASK,   PPCVEC,	0,		अणुVD, SIMMपूर्णपूर्ण,
अणु"vinsertb",	VX (4, 781),   VXUIMM4_MASK, PPCVEC3,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"evlhhousplat",VX (4, 781),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_2, RAपूर्णपूर्ण,
अणु"evlhhossplatx",VX(4, 782),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vpkpx",	VX (4, 782),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evlhhossplat",VX (4, 783),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_2, RAपूर्णपूर्ण,
अणु"mullhwu",	XRC(4, 392,0),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evlwhex",	VX (4, 784),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"mullhwu.",	XRC(4, 392,1),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evlwhe",	VX (4, 785),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"evlwhoux",	VX (4, 788),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evlwhou",	VX (4, 789),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"evlwhosx",	VX (4, 790),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evlwhos",	VX (4, 791),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"maclhwu",	XO (4, 396,0,0),XO_MASK,     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evlwwsplatx",	VX (4, 792),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"maclhwu.",	XO (4, 396,0,1),XO_MASK,     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evlwwsplat",	VX (4, 793),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"evlwhsplatx",	VX (4, 796),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evlwhsplat",	VX (4, 797),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"evstddx",	VX (4, 800),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evstdd",	VX (4, 801),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_8, RAपूर्णपूर्ण,
अणु"evstdwx",	VX (4, 802),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evstdw",	VX (4, 803),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_8, RAपूर्णपूर्ण,
अणु"evstdhx",	VX (4, 804),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evstdh",	VX (4, 805),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_8, RAपूर्णपूर्ण,
अणु"evstwhex",	VX (4, 816),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evstwhe",	VX (4, 817),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"evstwhox",	VX (4, 820),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evstwho",	VX (4, 821),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"evstwwex",	VX (4, 824),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evstwwe",	VX (4, 825),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"evstwwox",	VX (4, 828),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evstwwo",	VX (4, 829),	VX_MASK,     PPCSPE,	0,		अणुRS, EVUIMM_4, RAपूर्णपूर्ण,
अणु"vaddshs",	VX (4, 832),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"bcdcpsgn.",	VX (4, 833),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vminsh",	VX (4, 834),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vsrah",	VX (4, 836),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtsh",	VXR(4, 838,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmulesh",	VX (4, 840),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcfsx",	VX (4, 842),	VX_MASK,     PPCVEC,	0,		अणुVD, VB, UIMMपूर्णपूर्ण,
अणु"vcsxwfp",	VX (4, 842),	VX_MASK,     PPCVEC,	0,		अणुVD, VB, UIMMपूर्णपूर्ण,
अणु"vspltish",	VX (4, 844),	VXVB_MASK,   PPCVEC,	0,		अणुVD, SIMMपूर्णपूर्ण,
अणु"vinserth",	VX (4, 845),   VXUIMM4_MASK, PPCVEC3,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"vupkhpx",	VX (4, 846),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"mullhw",	XRC(4, 424,0),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mullhw.",	XRC(4, 424,1),	X_MASK,	     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"maclhw",	XO (4, 428,0,0),XO_MASK,     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"maclhw.",	XO (4, 428,0,1),XO_MASK,     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmaclhw",	XO (4, 430,0,0),XO_MASK,     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmaclhw.",	XO (4, 430,0,1),XO_MASK,     MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vaddsws",	VX (4, 896),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vminsw",	VX (4, 898),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vsraw",	VX (4, 900),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtsw",	VXR(4, 902,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmulesw",	VX (4, 904),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vctuxs",	VX (4, 906),	VX_MASK,     PPCVEC,	0,		अणुVD, VB, UIMMपूर्णपूर्ण,
अणु"vcfpuxws",	VX (4, 906),	VX_MASK,     PPCVEC,	0,		अणुVD, VB, UIMMपूर्णपूर्ण,
अणु"vspltisw",	VX (4, 908),	VXVB_MASK,   PPCVEC,	0,		अणुVD, SIMMपूर्णपूर्ण,
अणु"vinsertw",	VX (4, 909),   VXUIMM4_MASK, PPCVEC3,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"maclhwsu",	XO (4, 460,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"maclhwsu.",	XO (4, 460,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vminsd",	VX (4, 962),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vsrad",	VX (4, 964),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpbfp",	VXR(4, 966,0),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtsd",	VXR(4, 967,0),	VXR_MASK,    PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vctsxs",	VX (4, 970),	VX_MASK,     PPCVEC,	0,		अणुVD, VB, UIMMपूर्णपूर्ण,
अणु"vcfpsxws",	VX (4, 970),	VX_MASK,     PPCVEC,	0,		अणुVD, VB, UIMMपूर्णपूर्ण,
अणु"vinsertd",	VX (4, 973),   VXUIMM4_MASK, PPCVEC3,	0,		अणुVD, VB, UIMM4पूर्णपूर्ण,
अणु"vupklpx",	VX (4, 974),	VXVA_MASK,   PPCVEC,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"maclhws",	XO (4, 492,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"maclhws.",	XO (4, 492,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmaclhws",	XO (4, 494,0,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmaclhws.",	XO (4, 494,0,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vsububm",	VX (4,1024),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"bcdadd.",	VX (4,1025),	VXPS_MASK,   PPCVEC2,	0,		अणुVD, VA, VB, PSपूर्णपूर्ण,
अणु"vavgub",	VX (4,1026),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vabsdub",	VX (4,1027),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhessf",	VX (4,1027),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vand",	VX (4,1028),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpequb.",	VXR(4,	 6,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpneb.",	VXR(4,	 7,1),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi0fcm.",	APU(4, 515,0),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi0fcm",	APU(4, 515,1),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"evmhossf",	VX (4,1031),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vpmsumb",	VX (4,1032),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmheumi",	VX (4,1032),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhesmi",	VX (4,1033),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vmaxfp",	VX (4,1034),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhesmf",	VX (4,1035),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhoumi",	VX (4,1036),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vslo",	VX (4,1036),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhosmi",	VX (4,1037),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhosmf",	VX (4,1039),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"machhwuo",	XO (4,	12,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"machhwuo.",	XO (4,	12,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_merge00",	XOPS(4,528,0),	XOPS_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"ps_merge00.",	XOPS(4,528,1),	XOPS_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"evmhessfa",	VX (4,1059),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhossfa",	VX (4,1063),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmheumia",	VX (4,1064),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhesmia",	VX (4,1065),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhesmfa",	VX (4,1067),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhoumia",	VX (4,1068),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhosmia",	VX (4,1069),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhosmfa",	VX (4,1071),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vsubuhm",	VX (4,1088),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"bcdsub.",	VX (4,1089),	VXPS_MASK,   PPCVEC2,	0,		अणुVD, VA, VB, PSपूर्णपूर्ण,
अणु"vavguh",	VX (4,1090),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vabsduh",	VX (4,1091),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vandc",	VX (4,1092),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpequh.",	VXR(4,	70,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi1fcm.",	APU(4, 547,0),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi1fcm",	APU(4, 547,1),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"vcmpneh.",	VXR(4,	71,1),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwhssf",	VX (4,1095),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vpmsumh",	VX (4,1096),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwlumi",	VX (4,1096),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vminfp",	VX (4,1098),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwhumi",	VX (4,1100),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vsro",	VX (4,1100),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwhsmi",	VX (4,1101),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vpkudum",	VX (4,1102),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwhsmf",	VX (4,1103),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwssf",	VX (4,1107),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"machhwo",	XO (4,	44,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmwumi",	VX (4,1112),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"machhwo.",	XO (4,	44,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmwsmi",	VX (4,1113),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwsmf",	VX (4,1115),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"nmachhwo",	XO (4,	46,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmachhwo.",	XO (4,	46,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_merge01",	XOPS(4,560,0),	XOPS_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"ps_merge01.",	XOPS(4,560,1),	XOPS_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"evmwhssfa",	VX (4,1127),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwlumia",	VX (4,1128),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwhumia",	VX (4,1132),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwhsmia",	VX (4,1133),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwhsmfa",	VX (4,1135),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwssfa",	VX (4,1139),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwumia",	VX (4,1144),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwsmia",	VX (4,1145),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwsmfa",	VX (4,1147),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vsubuwm",	VX (4,1152),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"bcdus.",	VX (4,1153),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vavguw",	VX (4,1154),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vabsduw",	VX (4,1155),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmr",		VX (4,1156),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBAपूर्णपूर्ण,
अणु"vor",		VX (4,1156),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpnew.",	VXR(4, 135,1),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vpmsumw",	VX (4,1160),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpequw.",	VXR(4, 134,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi2fcm.",	APU(4, 579,0),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi2fcm",	APU(4, 579,1),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"machhwsuo",	XO (4,	76,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"machhwsuo.",	XO (4,	76,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_merge10",	XOPS(4,592,0),	XOPS_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"ps_merge10.",	XOPS(4,592,1),	XOPS_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"vsubudm",	VX (4,1216),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evaddusiaaw",	VX (4,1216),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"bcds.",	VX (4,1217),	VXPS_MASK,   PPCVEC3,	0,		अणुVD, VA, VB, PSपूर्णपूर्ण,
अणु"evaddssiaaw",	VX (4,1217),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evsubfusiaaw",VX (4,1218),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evsubfssiaaw",VX (4,1219),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evmra",	VX (4,1220),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vxor",	VX (4,1220),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evdivws",	VX (4,1222),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vcmpeqfp.",	VXR(4, 198,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi3fcm.",	APU(4, 611,0),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"vcmpequd.",	VXR(4, 199,1),	VXR_MASK,    PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi3fcm",	APU(4, 611,1),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"evdivwu",	VX (4,1223),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vpmsumd",	VX (4,1224),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evaddumiaaw",	VX (4,1224),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evaddsmiaaw",	VX (4,1225),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evsubfumiaaw",VX (4,1226),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"evsubfsmiaaw",VX (4,1227),	VX_MASK,     PPCSPE,	0,		अणुRS, RAपूर्णपूर्ण,
अणु"vpkudus",	VX (4,1230),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"machhwso",	XO (4, 108,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"machhwso.",	XO (4, 108,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmachhwso",	XO (4, 110,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmachhwso.",	XO (4, 110,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ps_merge11",	XOPS(4,624,0),	XOPS_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"ps_merge11.",	XOPS(4,624,1),	XOPS_MASK,   PPCPS,	0,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"vsubuqm",	VX (4,1280),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmheusiaaw",	VX (4,1280),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"bcdtrunc.",	VX (4,1281),	VXPS_MASK,   PPCVEC3,	0,		अणुVD, VA, VB, PSपूर्णपूर्ण,
अणु"evmhessiaaw",	VX (4,1281),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vavgsb",	VX (4,1282),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhessfaaw",	VX (4,1283),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhousiaaw",	VX (4,1284),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vnot",	VX (4,1284),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBAपूर्णपूर्ण,
अणु"vnor",	VX (4,1284),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhossiaaw",	VX (4,1285),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"udi4fcm.",	APU(4, 643,0),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi4fcm",	APU(4, 643,1),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"vcmpnezb.",	VXR(4, 263,1),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhossfaaw",	VX (4,1287),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmheumiaaw",	VX (4,1288),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vcipher",	VX (4,1288),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcipherlast",	VX (4,1289),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhesmiaaw",	VX (4,1289),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhesmfaaw",	VX (4,1291),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vgbbd",	VX (4,1292),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"evmhoumiaaw",	VX (4,1292),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhosmiaaw",	VX (4,1293),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhosmfaaw",	VX (4,1295),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"macchwuo",	XO (4, 140,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"macchwuo.",	XO (4, 140,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmhegumiaa",	VX (4,1320),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhegsmiaa",	VX (4,1321),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhegsmfaa",	VX (4,1323),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhogumiaa",	VX (4,1324),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhogsmiaa",	VX (4,1325),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhogsmfaa",	VX (4,1327),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vsubcuq",	VX (4,1344),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwlusiaaw",	VX (4,1344),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"bcdutrunc.",	VX (4,1345),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwlssiaaw",	VX (4,1345),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vavgsh",	VX (4,1346),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vorc",	VX (4,1348),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi5fcm.",	APU(4, 675,0),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi5fcm",	APU(4, 675,1),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"vcmpnezh.",	VXR(4, 327,1),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vncipher",	VX (4,1352),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwlumiaaw",	VX (4,1352),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vncipherlast",VX (4,1353),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwlsmiaaw",	VX (4,1353),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vbpermq",	VX (4,1356),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vpksdus",	VX (4,1358),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwssfaa",	VX (4,1363),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"macchwo",	XO (4, 172,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmwumiaa",	VX (4,1368),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"macchwo.",	XO (4, 172,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmwsmiaa",	VX (4,1369),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwsmfaa",	VX (4,1371),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"nmacchwo",	XO (4, 174,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmacchwo.",	XO (4, 174,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmheusianw",	VX (4,1408),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vsubcuw",	VX (4,1408),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhessianw",	VX (4,1409),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"bcdctsq.",	VXVA(4,1409,0),	VXVA_MASK,   PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"bcdcfsq.",	VXVA(4,1409,2),	VXVAPS_MASK, PPCVEC3,	0,		अणुVD, VB, PSपूर्णपूर्ण,
अणु"bcdctz.",	VXVA(4,1409,4),	VXVAPS_MASK, PPCVEC3,	0,		अणुVD, VB, PSपूर्णपूर्ण,
अणु"bcdctn.",	VXVA(4,1409,5),	VXVA_MASK,   PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"bcdcfz.",	VXVA(4,1409,6),	VXVAPS_MASK, PPCVEC3,	0,		अणुVD, VB, PSपूर्णपूर्ण,
अणु"bcdcfn.",	VXVA(4,1409,7),	VXVAPS_MASK, PPCVEC3,	0,		अणुVD, VB, PSपूर्णपूर्ण,
अणु"bcdsetsgn.",	VXVA(4,1409,31), VXVAPS_MASK, PPCVEC3,	0,		अणुVD, VB, PSपूर्णपूर्ण,
अणु"vavgsw",	VX (4,1410),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhessfanw",	VX (4,1411),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vnand",	VX (4,1412),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhousianw",	VX (4,1412),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhossianw",	VX (4,1413),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"udi6fcm.",	APU(4, 707,0),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi6fcm",	APU(4, 707,1),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"vcmpnezw.",	VXR(4, 391,1),	VXR_MASK,    PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmhossfanw",	VX (4,1415),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmheumianw",	VX (4,1416),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhesmianw",	VX (4,1417),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhesmfanw",	VX (4,1419),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhoumianw",	VX (4,1420),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhosmianw",	VX (4,1421),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhosmfanw",	VX (4,1423),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"macchwsuo",	XO (4, 204,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"macchwsuo.",	XO (4, 204,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmhegumian",	VX (4,1448),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhegsmian",	VX (4,1449),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhegsmfan",	VX (4,1451),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhogumian",	VX (4,1452),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhogsmian",	VX (4,1453),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmhogsmfan",	VX (4,1455),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwlusianw",	VX (4,1472),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"bcdsr.",	VX (4,1473),	VXPS_MASK,   PPCVEC3,	0,		अणुVD, VA, VB, PSपूर्णपूर्ण,
अणु"evmwlssianw",	VX (4,1473),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vsld",	VX (4,1476),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgefp.",	VXR(4, 454,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi7fcm.",	APU(4, 739,0),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi7fcm",	APU(4, 739,1),	APU_MASK, PPC405|PPC440, PPC476,	अणुURT, URA, URBपूर्णपूर्ण,
अणु"vsbox",	VX (4,1480),	VXVB_MASK,   PPCVEC2,	0,		अणुVD, VAपूर्णपूर्ण,
अणु"evmwlumianw",	VX (4,1480),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwlsmianw",	VX (4,1481),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"vbpermd",	VX (4,1484),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vpksdss",	VX (4,1486),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"evmwssfan",	VX (4,1491),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"macchwso",	XO (4, 236,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmwumian",	VX (4,1496),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"macchwso.",	XO (4, 236,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"evmwsmian",	VX (4,1497),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"evmwsmfan",	VX (4,1499),	VX_MASK,     PPCSPE,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"nmacchwso",	XO (4, 238,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmacchwso.",	XO (4, 238,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vsububs",	VX (4,1536),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vclzlsbb",	VXVA(4,1538,0), VXVA_MASK,   PPCVEC3,	0,		अणुRT, VBपूर्णपूर्ण,
अणु"vctzlsbb",	VXVA(4,1538,1), VXVA_MASK,   PPCVEC3,	0,		अणुRT, VBपूर्णपूर्ण,
अणु"vnegw",	VXVA(4,1538,6), VXVA_MASK,   PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vnegd",	VXVA(4,1538,7), VXVA_MASK,   PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vprtybw",	VXVA(4,1538,8), VXVA_MASK,   PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vprtybd",	VXVA(4,1538,9), VXVA_MASK,   PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vprtybq",	VXVA(4,1538,10), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vextsb2w",	VXVA(4,1538,16), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vextsh2w",	VXVA(4,1538,17), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vextsb2d",	VXVA(4,1538,24), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vextsh2d",	VXVA(4,1538,25), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vextsw2d",	VXVA(4,1538,26), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vctzb",	VXVA(4,1538,28), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vctzh",	VXVA(4,1538,29), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vctzw",	VXVA(4,1538,30), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vctzd",	VXVA(4,1538,31), VXVA_MASK,  PPCVEC3,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"mfvscr",	VX (4,1540),	VXVAVB_MASK, PPCVEC,	0,		अणुVDपूर्णपूर्ण,
अणु"vcmpgtub.",	VXR(4, 518,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi8fcm.",	APU(4, 771,0),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi8fcm",	APU(4, 771,1),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"vsum4ubs",	VX (4,1544),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vextublx",	VX (4,1549),	VX_MASK,     PPCVEC3,	0,		अणुRT, RA, VBपूर्णपूर्ण,
अणु"vsubuhs",	VX (4,1600),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"mtvscr",	VX (4,1604),	VXVDVA_MASK, PPCVEC,	0,		अणुVBपूर्णपूर्ण,
अणु"vcmpgtuh.",	VXR(4, 582,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vsum4shs",	VX (4,1608),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi9fcm.",	APU(4, 804,0),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi9fcm",	APU(4, 804,1),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"vextuhlx",	VX (4,1613),	VX_MASK,     PPCVEC3,	0,		अणुRT, RA, VBपूर्णपूर्ण,
अणु"vupkhsw",	VX (4,1614),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vsubuws",	VX (4,1664),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vshasigmaw",	VX (4,1666),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, ST, SIXपूर्णपूर्ण,
अणु"veqv",	VX (4,1668),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtuw.",	VXR(4, 646,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi10fcm.",	APU(4, 835,0),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi10fcm",	APU(4, 835,1),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"vsum2sws",	VX (4,1672),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmrgow",	VX (4,1676),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vextuwlx",	VX (4,1677),	VX_MASK,     PPCVEC3,	0,		अणुRT, RA, VBपूर्णपूर्ण,
अणु"vshasigmad",	VX (4,1730),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, ST, SIXपूर्णपूर्ण,
अणु"vsrd",	VX (4,1732),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtfp.",	VXR(4, 710,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi11fcm.",	APU(4, 867,0),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"vcmpgtud.",	VXR(4, 711,1),	VXR_MASK,    PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi11fcm",	APU(4, 867,1),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"vupklsw",	VX (4,1742),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vsubsbs",	VX (4,1792),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vclzb",	VX (4,1794),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vpopcntb",	VX (4,1795),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vsrv",	VX (4,1796),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtsb.",	VXR(4, 774,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi12fcm.",	APU(4, 899,0),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi12fcm",	APU(4, 899,1),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"vsum4sbs",	VX (4,1800),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vextubrx",	VX (4,1805),	VX_MASK,     PPCVEC3,	0,		अणुRT, RA, VBपूर्णपूर्ण,
अणु"maclhwuo",	XO (4, 396,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"maclhwuo.",	XO (4, 396,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vsubshs",	VX (4,1856),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vclzh",	VX (4,1858),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vpopcnth",	VX (4,1859),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vslv",	VX (4,1860),	VX_MASK,     PPCVEC3,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vcmpgtsh.",	VXR(4, 838,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vextuhrx",	VX (4,1869),	VX_MASK,     PPCVEC3,	0,		अणुRT, RA, VBपूर्णपूर्ण,
अणु"udi13fcm.",	APU(4, 931,0),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi13fcm",	APU(4, 931,1),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"maclhwo",	XO (4, 428,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"maclhwo.",	XO (4, 428,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmaclhwo",	XO (4, 430,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmaclhwo.",	XO (4, 430,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vsubsws",	VX (4,1920),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vclzw",	VX (4,1922),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vpopcntw",	VX (4,1923),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vcmpgtsw.",	VXR(4, 902,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi14fcm.",	APU(4, 963,0),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"udi14fcm",	APU(4, 963,1),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"vsumsws",	VX (4,1928),	VX_MASK,     PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vmrgew",	VX (4,1932),	VX_MASK,     PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"vextuwrx",	VX (4,1933),	VX_MASK,     PPCVEC3,	0,		अणुRT, RA, VBपूर्णपूर्ण,
अणु"maclhwsuo",	XO (4, 460,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"maclhwsuo.",	XO (4, 460,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"vclzd",	VX (4,1986),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vpopcntd",	VX (4,1987),	VXVA_MASK,   PPCVEC2,	0,		अणुVD, VBपूर्णपूर्ण,
अणु"vcmpbfp.",	VXR(4, 966,1),	VXR_MASK,    PPCVEC,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi15fcm.",	APU(4, 995,0),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"vcmpgtsd.",	VXR(4, 967,1),	VXR_MASK,    PPCVEC2,	0,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"udi15fcm",	APU(4, 995,1),	APU_MASK,    PPC440,	PPC476,		अणुURT, URA, URBपूर्णपूर्ण,
अणु"maclhwso",	XO (4, 492,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"maclhwso.",	XO (4, 492,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmaclhwso",	XO (4, 494,1,0), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"nmaclhwso.",	XO (4, 494,1,1), XO_MASK,    MULHW,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"dcbz_l",	X  (4,1014),	XRT_MASK,    PPCPS,	0,		अणुRA, RBपूर्णपूर्ण,

अणु"mulli",	OP(7),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,
अणु"muli",	OP(7),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,

अणु"subfic",	OP(8),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,
अणु"sfi",		OP(8),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,

अणु"dozi",	OP(9),		OP_MASK,     M601,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,

अणु"cmplwi",	OPL(10,0),	OPL_MASK,    PPCCOM,	PPCVLE,		अणुOBF, RA, UISIGNOPTपूर्णपूर्ण,
अणु"cmpldi",	OPL(10,1),	OPL_MASK,    PPC64,	PPCVLE,		अणुOBF, RA, UISIGNOPTपूर्णपूर्ण,
अणु"cmpli",	OP(10),		OP_MASK,     PPC,	PPCVLE,		अणुBF, L32OPT, RA, UISIGNOPTपूर्णपूर्ण,
अणु"cmpli",	OP(10),		OP_MASK,     PWRCOM,	PPC|PPCVLE,	अणुBF, RA, UISIGNOPTपूर्णपूर्ण,

अणु"cmpwi",	OPL(11,0),	OPL_MASK,    PPCCOM,	PPCVLE,		अणुOBF, RA, SIपूर्णपूर्ण,
अणु"cmpdi",	OPL(11,1),	OPL_MASK,    PPC64,	PPCVLE,		अणुOBF, RA, SIपूर्णपूर्ण,
अणु"cmpi",	OP(11),		OP_MASK,     PPC,	PPCVLE,		अणुBF, L32OPT, RA, SIपूर्णपूर्ण,
अणु"cmpi",	OP(11),		OP_MASK,     PWRCOM,	PPC|PPCVLE,	अणुBF, RA, SIपूर्णपूर्ण,

अणु"addic",	OP(12),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,
अणु"ai",		OP(12),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,
अणु"subic",	OP(12),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA, NSIपूर्णपूर्ण,

अणु"addic.",	OP(13),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,
अणु"ai.",		OP(13),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, RA, SIपूर्णपूर्ण,
अणु"subic.",	OP(13),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA, NSIपूर्णपूर्ण,

अणु"li",		OP(14),		DRA_MASK,    PPCCOM,	PPCVLE,		अणुRT, SIपूर्णपूर्ण,
अणु"lil",		OP(14),		DRA_MASK,    PWRCOM,	PPCVLE,		अणुRT, SIपूर्णपूर्ण,
अणु"addi",	OP(14),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA0, SIपूर्णपूर्ण,
अणु"cal",		OP(14),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,
अणु"subi",	OP(14),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA0, NSIपूर्णपूर्ण,
अणु"la",		OP(14),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"lis",		OP(15),		DRA_MASK,    PPCCOM,	PPCVLE,		अणुRT, SISIGNOPTपूर्णपूर्ण,
अणु"liu",		OP(15),		DRA_MASK,    PWRCOM,	PPCVLE,		अणुRT, SISIGNOPTपूर्णपूर्ण,
अणु"addis",	OP(15),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA0, SISIGNOPTपूर्णपूर्ण,
अणु"cau",		OP(15),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, RA0, SISIGNOPTपूर्णपूर्ण,
अणु"subis",	OP(15),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, RA0, NSISIGNOPTपूर्णपूर्ण,

अणु"bdnz-",    BBO(16,BODNZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDMपूर्णपूर्ण,
अणु"bdnz+",    BBO(16,BODNZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDPपूर्णपूर्ण,
अणु"bdnz",     BBO(16,BODNZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDपूर्णपूर्ण,
अणु"bdn",	     BBO(16,BODNZ,0,0),		BBOATBI_MASK,  PWRCOM,	 PPCVLE,	अणुBDपूर्णपूर्ण,
अणु"bdnzl-",   BBO(16,BODNZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDMपूर्णपूर्ण,
अणु"bdnzl+",   BBO(16,BODNZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDPपूर्णपूर्ण,
अणु"bdnzl",    BBO(16,BODNZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDपूर्णपूर्ण,
अणु"bdnl",     BBO(16,BODNZ,0,1),		BBOATBI_MASK,  PWRCOM,	 PPCVLE,	अणुBDपूर्णपूर्ण,
अणु"bdnza-",   BBO(16,BODNZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDMAपूर्णपूर्ण,
अणु"bdnza+",   BBO(16,BODNZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDPAपूर्णपूर्ण,
अणु"bdnza",    BBO(16,BODNZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDAपूर्णपूर्ण,
अणु"bdna",     BBO(16,BODNZ,1,0),		BBOATBI_MASK,  PWRCOM,	 PPCVLE,	अणुBDAपूर्णपूर्ण,
अणु"bdnzla-",  BBO(16,BODNZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDMAपूर्णपूर्ण,
अणु"bdnzla+",  BBO(16,BODNZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDPAपूर्णपूर्ण,
अणु"bdnzla",   BBO(16,BODNZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDAपूर्णपूर्ण,
अणु"bdnla",    BBO(16,BODNZ,1,1),		BBOATBI_MASK,  PWRCOM,	 PPCVLE,	अणुBDAपूर्णपूर्ण,
अणु"bdz-",     BBO(16,BODZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDMपूर्णपूर्ण,
अणु"bdz+",     BBO(16,BODZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDPपूर्णपूर्ण,
अणु"bdz",	     BBO(16,BODZ,0,0),		BBOATBI_MASK,  COM,	 PPCVLE,	अणुBDपूर्णपूर्ण,
अणु"bdzl-",    BBO(16,BODZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDMपूर्णपूर्ण,
अणु"bdzl+",    BBO(16,BODZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDPपूर्णपूर्ण,
अणु"bdzl",     BBO(16,BODZ,0,1),		BBOATBI_MASK,  COM,	 PPCVLE,	अणुBDपूर्णपूर्ण,
अणु"bdza-",    BBO(16,BODZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDMAपूर्णपूर्ण,
अणु"bdza+",    BBO(16,BODZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDPAपूर्णपूर्ण,
अणु"bdza",     BBO(16,BODZ,1,0),		BBOATBI_MASK,  COM,	 PPCVLE,	अणुBDAपूर्णपूर्ण,
अणु"bdzla-",   BBO(16,BODZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDMAपूर्णपूर्ण,
अणु"bdzla+",   BBO(16,BODZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCVLE,	अणुBDPAपूर्णपूर्ण,
अणु"bdzla",    BBO(16,BODZ,1,1),		BBOATBI_MASK,  COM,	 PPCVLE,	अणुBDAपूर्णपूर्ण,

अणु"bge-",     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bge+",     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bge",	     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bnl-",     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bnl+",     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bnl",	     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bgel-",    BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bgel+",    BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bgel",     BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bnll-",    BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bnll+",    BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bnll",     BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bgea-",    BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bgea+",    BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bgea",     BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bnla-",    BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnla+",    BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnla",     BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bgela-",   BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bgela+",   BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bgela",    BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bnlla-",   BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnlla+",   BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnlla",    BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"ble-",     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"ble+",     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"ble",	     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bng-",     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bng+",     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bng",	     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"blel-",    BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"blel+",    BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"blel",     BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bngl-",    BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bngl+",    BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bngl",     BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"blea-",    BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"blea+",    BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"blea",     BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bnga-",    BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnga+",    BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnga",     BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"blela-",   BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"blela+",   BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"blela",    BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bngla-",   BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bngla+",   BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bngla",    BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bne-",     BBOCB(16,BOF,CBEQ,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bne+",     BBOCB(16,BOF,CBEQ,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bne",	     BBOCB(16,BOF,CBEQ,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bnel-",    BBOCB(16,BOF,CBEQ,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bnel+",    BBOCB(16,BOF,CBEQ,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bnel",     BBOCB(16,BOF,CBEQ,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bnea-",    BBOCB(16,BOF,CBEQ,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnea+",    BBOCB(16,BOF,CBEQ,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnea",     BBOCB(16,BOF,CBEQ,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bnela-",   BBOCB(16,BOF,CBEQ,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnela+",   BBOCB(16,BOF,CBEQ,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnela",    BBOCB(16,BOF,CBEQ,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bns-",     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bns+",     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bns",	     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bnu-",     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bnu+",     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bnu",	     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bnsl-",    BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bnsl+",    BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bnsl",     BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bnul-",    BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bnul+",    BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bnul",     BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bnsa-",    BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnsa+",    BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnsa",     BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bnua-",    BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnua+",    BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnua",     BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bnsla-",   BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnsla+",   BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnsla",    BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bnula-",   BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bnula+",   BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bnula",    BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,

अणु"blt-",     BBOCB(16,BOT,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"blt+",     BBOCB(16,BOT,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"blt",	     BBOCB(16,BOT,CBLT,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bltl-",    BBOCB(16,BOT,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bltl+",    BBOCB(16,BOT,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bltl",     BBOCB(16,BOT,CBLT,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"blta-",    BBOCB(16,BOT,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"blta+",    BBOCB(16,BOT,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"blta",     BBOCB(16,BOT,CBLT,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bltla-",   BBOCB(16,BOT,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bltla+",   BBOCB(16,BOT,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bltla",    BBOCB(16,BOT,CBLT,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bgt-",     BBOCB(16,BOT,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bgt+",     BBOCB(16,BOT,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bgt",	     BBOCB(16,BOT,CBGT,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bgtl-",    BBOCB(16,BOT,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bgtl+",    BBOCB(16,BOT,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bgtl",     BBOCB(16,BOT,CBGT,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bgta-",    BBOCB(16,BOT,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bgta+",    BBOCB(16,BOT,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bgta",     BBOCB(16,BOT,CBGT,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bgtla-",   BBOCB(16,BOT,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bgtla+",   BBOCB(16,BOT,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bgtla",    BBOCB(16,BOT,CBGT,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"beq-",     BBOCB(16,BOT,CBEQ,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"beq+",     BBOCB(16,BOT,CBEQ,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"beq",	     BBOCB(16,BOT,CBEQ,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"beql-",    BBOCB(16,BOT,CBEQ,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"beql+",    BBOCB(16,BOT,CBEQ,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"beql",     BBOCB(16,BOT,CBEQ,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"beqa-",    BBOCB(16,BOT,CBEQ,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"beqa+",    BBOCB(16,BOT,CBEQ,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"beqa",     BBOCB(16,BOT,CBEQ,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"beqla-",   BBOCB(16,BOT,CBEQ,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"beqla+",   BBOCB(16,BOT,CBEQ,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"beqla",    BBOCB(16,BOT,CBEQ,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bso-",     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bso+",     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bso",	     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bun-",     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bun+",     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bun",	     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bsol-",    BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bsol+",    BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bsol",     BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bunl-",    BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMपूर्णपूर्ण,
अणु"bunl+",    BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPपूर्णपूर्ण,
अणु"bunl",     BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDपूर्णपूर्ण,
अणु"bsoa-",    BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bsoa+",    BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bsoa",     BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"buna-",    BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"buna+",    BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"buna",     BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bsola-",   BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bsola+",   BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bsola",    BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  COM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,
अणु"bunla-",   BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDMAपूर्णपूर्ण,
अणु"bunla+",   BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDPAपूर्णपूर्ण,
अणु"bunla",    BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCVLE,	अणुCR, BDAपूर्णपूर्ण,

अणु"bdnzf-",   BBO(16,BODNZF,0,0),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bdnzf+",   BBO(16,BODNZF,0,0),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bdnzf",    BBO(16,BODNZF,0,0),	BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bdnzfl-",  BBO(16,BODNZF,0,1),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bdnzfl+",  BBO(16,BODNZF,0,1),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bdnzfl",   BBO(16,BODNZF,0,1),	BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bdnzfa-",  BBO(16,BODNZF,1,0),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bdnzfa+",  BBO(16,BODNZF,1,0),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bdnzfa",   BBO(16,BODNZF,1,0),	BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bdnzfla-", BBO(16,BODNZF,1,1),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bdnzfla+", BBO(16,BODNZF,1,1),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bdnzfla",  BBO(16,BODNZF,1,1),	BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bdzf-",    BBO(16,BODZF,0,0),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bdzf+",    BBO(16,BODZF,0,0),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bdzf",     BBO(16,BODZF,0,0),		BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bdzfl-",   BBO(16,BODZF,0,1),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bdzfl+",   BBO(16,BODZF,0,1),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bdzfl",    BBO(16,BODZF,0,1),		BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bdzfa-",   BBO(16,BODZF,1,0),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bdzfa+",   BBO(16,BODZF,1,0),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bdzfa",    BBO(16,BODZF,1,0),		BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bdzfla-",  BBO(16,BODZF,1,1),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bdzfla+",  BBO(16,BODZF,1,1),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bdzfla",   BBO(16,BODZF,1,1),		BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,

अणु"bf-",	     BBO(16,BOF,0,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bf+",	     BBO(16,BOF,0,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bf",	     BBO(16,BOF,0,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bbf",	     BBO(16,BOF,0,0),		BBOAT_MASK,    PWRCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bfl-",     BBO(16,BOF,0,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bfl+",     BBO(16,BOF,0,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bfl",	     BBO(16,BOF,0,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bbfl",     BBO(16,BOF,0,1),		BBOAT_MASK,    PWRCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bfa-",     BBO(16,BOF,1,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bfa+",     BBO(16,BOF,1,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bfa",	     BBO(16,BOF,1,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bbfa",     BBO(16,BOF,1,0),		BBOAT_MASK,    PWRCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bfla-",    BBO(16,BOF,1,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bfla+",    BBO(16,BOF,1,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bfla",     BBO(16,BOF,1,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bbfla",    BBO(16,BOF,1,1),		BBOAT_MASK,    PWRCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,

अणु"bdnzt-",   BBO(16,BODNZT,0,0),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bdnzt+",   BBO(16,BODNZT,0,0),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bdnzt",    BBO(16,BODNZT,0,0),	BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bdnztl-",  BBO(16,BODNZT,0,1),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bdnztl+",  BBO(16,BODNZT,0,1),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bdnztl",   BBO(16,BODNZT,0,1),	BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bdnzta-",  BBO(16,BODNZT,1,0),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bdnzta+",  BBO(16,BODNZT,1,0),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bdnzta",   BBO(16,BODNZT,1,0),	BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bdnztla-", BBO(16,BODNZT,1,1),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bdnztla+", BBO(16,BODNZT,1,1),	BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bdnztla",  BBO(16,BODNZT,1,1),	BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bdzt-",    BBO(16,BODZT,0,0),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bdzt+",    BBO(16,BODZT,0,0),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bdzt",     BBO(16,BODZT,0,0),		BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bdztl-",   BBO(16,BODZT,0,1),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bdztl+",   BBO(16,BODZT,0,1),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bdztl",    BBO(16,BODZT,0,1),		BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bdzta-",   BBO(16,BODZT,1,0),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bdzta+",   BBO(16,BODZT,1,0),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bdzta",    BBO(16,BODZT,1,0),		BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bdztla-",  BBO(16,BODZT,1,1),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bdztla+",  BBO(16,BODZT,1,1),		BBOY_MASK,     PPCCOM,	 ISA_V2|PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bdztla",   BBO(16,BODZT,1,1),		BBOY_MASK,     PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,

अणु"bt-",	     BBO(16,BOT,0,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"bt+",	     BBO(16,BOT,0,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"bt",	     BBO(16,BOT,0,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bbt",	     BBO(16,BOT,0,0),		BBOAT_MASK,    PWRCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"btl-",     BBO(16,BOT,0,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDMपूर्णपूर्ण,
अणु"btl+",     BBO(16,BOT,0,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDPपूर्णपूर्ण,
अणु"btl",	     BBO(16,BOT,0,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bbtl",     BBO(16,BOT,0,1),		BBOAT_MASK,    PWRCOM,	 PPCVLE,	अणुBI, BDपूर्णपूर्ण,
अणु"bta-",     BBO(16,BOT,1,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"bta+",     BBO(16,BOT,1,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"bta",	     BBO(16,BOT,1,0),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bbta",     BBO(16,BOT,1,0),		BBOAT_MASK,    PWRCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"btla-",    BBO(16,BOT,1,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDMAपूर्णपूर्ण,
अणु"btla+",    BBO(16,BOT,1,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDPAपूर्णपूर्ण,
अणु"btla",     BBO(16,BOT,1,1),		BBOAT_MASK,    PPCCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,
अणु"bbtla",    BBO(16,BOT,1,1),		BBOAT_MASK,    PWRCOM,	 PPCVLE,	अणुBI, BDAपूर्णपूर्ण,

अणु"bc-",		B(16,0,0),	B_MASK,	     PPCCOM,	PPCVLE,		अणुBOE, BI, BDMपूर्णपूर्ण,
अणु"bc+",		B(16,0,0),	B_MASK,	     PPCCOM,	PPCVLE,		अणुBOE, BI, BDPपूर्णपूर्ण,
अणु"bc",		B(16,0,0),	B_MASK,	     COM,	PPCVLE,		अणुBO, BI, BDपूर्णपूर्ण,
अणु"bcl-",	B(16,0,1),	B_MASK,	     PPCCOM,	PPCVLE,		अणुBOE, BI, BDMपूर्णपूर्ण,
अणु"bcl+",	B(16,0,1),	B_MASK,	     PPCCOM,	PPCVLE,		अणुBOE, BI, BDPपूर्णपूर्ण,
अणु"bcl",		B(16,0,1),	B_MASK,	     COM,	PPCVLE,		अणुBO, BI, BDपूर्णपूर्ण,
अणु"bca-",	B(16,1,0),	B_MASK,	     PPCCOM,	PPCVLE,		अणुBOE, BI, BDMAपूर्णपूर्ण,
अणु"bca+",	B(16,1,0),	B_MASK,	     PPCCOM,	PPCVLE,		अणुBOE, BI, BDPAपूर्णपूर्ण,
अणु"bca",		B(16,1,0),	B_MASK,	     COM,	PPCVLE,		अणुBO, BI, BDAपूर्णपूर्ण,
अणु"bcla-",	B(16,1,1),	B_MASK,	     PPCCOM,	PPCVLE,		अणुBOE, BI, BDMAपूर्णपूर्ण,
अणु"bcla+",	B(16,1,1),	B_MASK,	     PPCCOM,	PPCVLE,		अणुBOE, BI, BDPAपूर्णपूर्ण,
अणु"bcla",	B(16,1,1),	B_MASK,	     COM,	PPCVLE,		अणुBO, BI, BDAपूर्णपूर्ण,

अणु"svc",		SC(17,0,0),	SC_MASK,     POWER,	PPCVLE,		अणुSVC_LEV, FL1, FL2पूर्णपूर्ण,
अणु"svcl",	SC(17,0,1),	SC_MASK,     POWER,	PPCVLE,		अणुSVC_LEV, FL1, FL2पूर्णपूर्ण,
अणु"sc",		SC(17,1,0),	SC_MASK,     PPC,	PPCVLE,		अणुLEVपूर्णपूर्ण,
अणु"svca",	SC(17,1,0),	SC_MASK,     PWRCOM,	PPCVLE,		अणुSVपूर्णपूर्ण,
अणु"svcla",	SC(17,1,1),	SC_MASK,     POWER,	PPCVLE,		अणुSVपूर्णपूर्ण,

अणु"b",		B(18,0,0),	B_MASK,	     COM,	PPCVLE,		अणुLIपूर्णपूर्ण,
अणु"bl",		B(18,0,1),	B_MASK,	     COM,	PPCVLE,		अणुLIपूर्णपूर्ण,
अणु"ba",		B(18,1,0),	B_MASK,	     COM,	PPCVLE,		अणुLIAपूर्णपूर्ण,
अणु"bla",		B(18,1,1),	B_MASK,	     COM,	PPCVLE,		अणुLIAपूर्णपूर्ण,

अणु"mcrf",     XL(19,0), XLBB_MASK|(3<<21)|(3<<16), COM,	PPCVLE,		अणुBF, BFAपूर्णपूर्ण,

अणु"addpcis",  DX(19,2),		DX_MASK,     POWER9,	PPCVLE,		अणुRT, DXDपूर्णपूर्ण,
अणु"subpcis",  DX(19,2),		DX_MASK,     POWER9,	PPCVLE,		अणुRT, NDXDपूर्णपूर्ण,

अणु"bdnzlr",   XLO(19,BODNZ,16,0),	XLBOBIBB_MASK, PPCCOM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlr-",  XLO(19,BODNZ,16,0),	XLBOBIBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlrl",  XLO(19,BODNZ,16,1),	XLBOBIBB_MASK, PPCCOM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlrl-", XLO(19,BODNZ,16,1),	XLBOBIBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlr+",  XLO(19,BODNZP,16,0),	XLBOBIBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlrl+", XLO(19,BODNZP,16,1),	XLBOBIBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlr",    XLO(19,BODZ,16,0),		XLBOBIBB_MASK, PPCCOM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlr-",   XLO(19,BODZ,16,0),		XLBOBIBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlrl",   XLO(19,BODZ,16,1),		XLBOBIBB_MASK, PPCCOM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlrl-",  XLO(19,BODZ,16,1),		XLBOBIBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlr+",   XLO(19,BODZP,16,0),	XLBOBIBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlrl+",  XLO(19,BODZP,16,1),	XLBOBIBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"blr",	     XLO(19,BOU,16,0),		XLBOBIBB_MASK, PPCCOM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"br",	     XLO(19,BOU,16,0),		XLBOBIBB_MASK, PWRCOM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"blrl",     XLO(19,BOU,16,1),		XLBOBIBB_MASK, PPCCOM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"brl",	     XLO(19,BOU,16,1),		XLBOBIBB_MASK, PWRCOM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlr-",  XLO(19,BODNZM4,16,0),	XLBOBIBB_MASK, ISA_V2,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlrl-", XLO(19,BODNZM4,16,1),	XLBOBIBB_MASK, ISA_V2,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlr+",  XLO(19,BODNZP4,16,0),	XLBOBIBB_MASK, ISA_V2,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdnzlrl+", XLO(19,BODNZP4,16,1),	XLBOBIBB_MASK, ISA_V2,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlr-",   XLO(19,BODZM4,16,0),	XLBOBIBB_MASK, ISA_V2,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlrl-",  XLO(19,BODZM4,16,1),	XLBOBIBB_MASK, ISA_V2,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlr+",   XLO(19,BODZP4,16,0),	XLBOBIBB_MASK, ISA_V2,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bdzlrl+",  XLO(19,BODZP4,16,1),	XLBOBIBB_MASK, ISA_V2,	 PPCVLE,	अणु0पूर्णपूर्ण,

अणु"bgelr",    XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelr-",   XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bger",     XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllr",    XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllr-",   XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlr",     XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelrl",   XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelrl-",  XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgerl",    XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllrl",   XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllrl-",  XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlrl",    XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelr",    XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelr-",   XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bler",     XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglr",    XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglr-",   XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngr",     XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelrl",   XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelrl-",  XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blerl",    XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglrl",   XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglrl-",  XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngrl",    XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelr",    XLOCB(19,BOF,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelr-",   XLOCB(19,BOF,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bner",     XLOCB(19,BOF,CBEQ,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelrl",   XLOCB(19,BOF,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelrl-",  XLOCB(19,BOF,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnerl",    XLOCB(19,BOF,CBEQ,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslr",    XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslr-",   XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsr",     XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulr",    XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulr-",   XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslrl",   XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslrl-",  XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsrl",    XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulrl",   XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulrl-",  XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelr+",   XLOCB(19,BOFP,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllr+",   XLOCB(19,BOFP,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelrl+",  XLOCB(19,BOFP,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllrl+",  XLOCB(19,BOFP,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelr+",   XLOCB(19,BOFP,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglr+",   XLOCB(19,BOFP,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelrl+",  XLOCB(19,BOFP,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglrl+",  XLOCB(19,BOFP,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelr+",   XLOCB(19,BOFP,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelrl+",  XLOCB(19,BOFP,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslr+",   XLOCB(19,BOFP,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulr+",   XLOCB(19,BOFP,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslrl+",  XLOCB(19,BOFP,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulrl+",  XLOCB(19,BOFP,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelr-",   XLOCB(19,BOFM4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllr-",   XLOCB(19,BOFM4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelrl-",  XLOCB(19,BOFM4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllrl-",  XLOCB(19,BOFM4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelr-",   XLOCB(19,BOFM4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglr-",   XLOCB(19,BOFM4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelrl-",  XLOCB(19,BOFM4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglrl-",  XLOCB(19,BOFM4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelr-",   XLOCB(19,BOFM4,CBEQ,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelrl-",  XLOCB(19,BOFM4,CBEQ,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslr-",   XLOCB(19,BOFM4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulr-",   XLOCB(19,BOFM4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslrl-",  XLOCB(19,BOFM4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulrl-",  XLOCB(19,BOFM4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelr+",   XLOCB(19,BOFP4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllr+",   XLOCB(19,BOFP4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgelrl+",  XLOCB(19,BOFP4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnllrl+",  XLOCB(19,BOFP4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelr+",   XLOCB(19,BOFP4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglr+",   XLOCB(19,BOFP4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blelrl+",  XLOCB(19,BOFP4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnglrl+",  XLOCB(19,BOFP4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelr+",   XLOCB(19,BOFP4,CBEQ,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnelrl+",  XLOCB(19,BOFP4,CBEQ,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslr+",   XLOCB(19,BOFP4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulr+",   XLOCB(19,BOFP4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnslrl+",  XLOCB(19,BOFP4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnulrl+",  XLOCB(19,BOFP4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlr",    XLOCB(19,BOT,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlr-",   XLOCB(19,BOT,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltr",     XLOCB(19,BOT,CBLT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlrl",   XLOCB(19,BOT,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlrl-",  XLOCB(19,BOT,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltrl",    XLOCB(19,BOT,CBLT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlr",    XLOCB(19,BOT,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlr-",   XLOCB(19,BOT,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtr",     XLOCB(19,BOT,CBGT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlrl",   XLOCB(19,BOT,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlrl-",  XLOCB(19,BOT,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtrl",    XLOCB(19,BOT,CBGT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlr",    XLOCB(19,BOT,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlr-",   XLOCB(19,BOT,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqr",     XLOCB(19,BOT,CBEQ,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlrl",   XLOCB(19,BOT,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlrl-",  XLOCB(19,BOT,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqrl",    XLOCB(19,BOT,CBEQ,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolr",    XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolr-",   XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsor",     XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlr",    XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlr-",   XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolrl",   XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolrl-",  XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsorl",    XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlrl",   XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlrl-",  XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlr+",   XLOCB(19,BOTP,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlrl+",  XLOCB(19,BOTP,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlr+",   XLOCB(19,BOTP,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlrl+",  XLOCB(19,BOTP,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlr+",   XLOCB(19,BOTP,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlrl+",  XLOCB(19,BOTP,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolr+",   XLOCB(19,BOTP,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlr+",   XLOCB(19,BOTP,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolrl+",  XLOCB(19,BOTP,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlrl+",  XLOCB(19,BOTP,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlr-",   XLOCB(19,BOTM4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlrl-",  XLOCB(19,BOTM4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlr-",   XLOCB(19,BOTM4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlrl-",  XLOCB(19,BOTM4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlr-",   XLOCB(19,BOTM4,CBEQ,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlrl-",  XLOCB(19,BOTM4,CBEQ,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolr-",   XLOCB(19,BOTM4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlr-",   XLOCB(19,BOTM4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolrl-",  XLOCB(19,BOTM4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlrl-",  XLOCB(19,BOTM4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlr+",   XLOCB(19,BOTP4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltlrl+",  XLOCB(19,BOTP4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlr+",   XLOCB(19,BOTP4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtlrl+",  XLOCB(19,BOTP4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlr+",   XLOCB(19,BOTP4,CBEQ,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqlrl+",  XLOCB(19,BOTP4,CBEQ,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolr+",   XLOCB(19,BOTP4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlr+",   XLOCB(19,BOTP4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsolrl+",  XLOCB(19,BOTP4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunlrl+",  XLOCB(19,BOTP4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,

अणु"bdnzflr",  XLO(19,BODNZF,16,0),	XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnzflr-", XLO(19,BODNZF,16,0),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnzflrl", XLO(19,BODNZF,16,1),	XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnzflrl-",XLO(19,BODNZF,16,1),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnzflr+", XLO(19,BODNZFP,16,0),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnzflrl+",XLO(19,BODNZFP,16,1),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdzflr",   XLO(19,BODZF,16,0),	XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdzflr-",  XLO(19,BODZF,16,0),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdzflrl",  XLO(19,BODZF,16,1),	XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdzflrl-", XLO(19,BODZF,16,1),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdzflr+",  XLO(19,BODZFP,16,0),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdzflrl+", XLO(19,BODZFP,16,1),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflr",     XLO(19,BOF,16,0),		XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflr-",    XLO(19,BOF,16,0),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bbfr",     XLO(19,BOF,16,0),		XLBOBB_MASK,   PWRCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflrl",    XLO(19,BOF,16,1),		XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflrl-",   XLO(19,BOF,16,1),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bbfrl",    XLO(19,BOF,16,1),		XLBOBB_MASK,   PWRCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflr+",    XLO(19,BOFP,16,0),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflrl+",   XLO(19,BOFP,16,1),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflr-",    XLO(19,BOFM4,16,0),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflrl-",   XLO(19,BOFM4,16,1),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflr+",    XLO(19,BOFP4,16,0),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bflrl+",   XLO(19,BOFP4,16,1),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnztlr",  XLO(19,BODNZT,16,0),	XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnztlr-", XLO(19,BODNZT,16,0),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnztlrl", XLO(19,BODNZT,16,1),	XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnztlrl-", XLO(19,BODNZT,16,1),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnztlr+", XLO(19,BODNZTP,16,0),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdnztlrl+", XLO(19,BODNZTP,16,1),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdztlr",   XLO(19,BODZT,16,0),	XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdztlr-",  XLO(19,BODZT,16,0),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdztlrl",  XLO(19,BODZT,16,1),	XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdztlrl-", XLO(19,BODZT,16,1),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdztlr+",  XLO(19,BODZTP,16,0),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bdztlrl+", XLO(19,BODZTP,16,1),	XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlr",     XLO(19,BOT,16,0),		XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlr-",    XLO(19,BOT,16,0),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bbtr",     XLO(19,BOT,16,0),		XLBOBB_MASK,   PWRCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlrl",    XLO(19,BOT,16,1),		XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlrl-",   XLO(19,BOT,16,1),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bbtrl",    XLO(19,BOT,16,1),		XLBOBB_MASK,   PWRCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlr+",    XLO(19,BOTP,16,0),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlrl+",   XLO(19,BOTP,16,1),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlr-",    XLO(19,BOTM4,16,0),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlrl-",   XLO(19,BOTM4,16,1),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlr+",    XLO(19,BOTP4,16,0),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btlrl+",   XLO(19,BOTP4,16,1),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,

अणु"bclr-",    XLYLK(19,16,0,0),		XLYBB_MASK,    PPCCOM,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bclrl-",   XLYLK(19,16,0,1),		XLYBB_MASK,    PPCCOM,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bclr+",    XLYLK(19,16,1,0),		XLYBB_MASK,    PPCCOM,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bclrl+",   XLYLK(19,16,1,1),		XLYBB_MASK,    PPCCOM,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bclr",     XLLK(19,16,0),		XLBH_MASK,     PPCCOM,	 PPCVLE,	अणुBO, BI, BHपूर्णपूर्ण,
अणु"bcr",	     XLLK(19,16,0),		XLBB_MASK,     PWRCOM,	 PPCVLE,	अणुBO, BIपूर्णपूर्ण,
अणु"bclrl",    XLLK(19,16,1),		XLBH_MASK,     PPCCOM,	 PPCVLE,	अणुBO, BI, BHपूर्णपूर्ण,
अणु"bcrl",     XLLK(19,16,1),		XLBB_MASK,     PWRCOM,	 PPCVLE,	अणुBO, BIपूर्णपूर्ण,

अणु"rfid",	XL(19,18),	0xffffffff,  PPC64,	PPCVLE,	अणु0पूर्णपूर्ण,

अणु"crnot",	XL(19,33),	XL_MASK,     PPCCOM,	PPCVLE,		अणुBT, BA, BBAपूर्णपूर्ण,
अणु"crnor",	XL(19,33),	XL_MASK,     COM,	PPCVLE,		अणुBT, BA, BBपूर्णपूर्ण,
अणु"rfmci",	X(19,38),    0xffffffff, PPCRFMCI|PPCA2|PPC476, PPCVLE,	अणु0पूर्णपूर्ण,

अणु"rfdi",	XL(19,39),	0xffffffff,  E500MC,	PPCVLE,		अणु0पूर्णपूर्ण,
अणु"rfi",		XL(19,50),	0xffffffff,  COM,	PPCVLE,		अणु0पूर्णपूर्ण,
अणु"rfci",	XL(19,51), 0xffffffff, PPC403|BOOKE|PPCE300|PPCA2|PPC476, PPCVLE, अणु0पूर्णपूर्ण,

अणु"rfsvc",	XL(19,82),	0xffffffff,  POWER,	PPCVLE,		अणु0पूर्णपूर्ण,

अणु"rfgi",	XL(19,102),   0xffffffff, E500MC|PPCA2,	PPCVLE,		अणु0पूर्णपूर्ण,

अणु"crandc",	XL(19,129),	XL_MASK,     COM,	PPCVLE,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"rfebb",	XL(19,146),	XLS_MASK,    POWER8,	PPCVLE,		अणुSXLपूर्णपूर्ण,

अणु"isync",	XL(19,150),	0xffffffff,  PPCCOM,	PPCVLE,		अणु0पूर्णपूर्ण,
अणु"ics",		XL(19,150),	0xffffffff,  PWRCOM,	PPCVLE,		अणु0पूर्णपूर्ण,

अणु"crclr",	XL(19,193),	XL_MASK,     PPCCOM,	PPCVLE,		अणुBT, BAT, BBAपूर्णपूर्ण,
अणु"crxor",	XL(19,193),	XL_MASK,     COM,	PPCVLE,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"dnh",		X(19,198),	X_MASK,	     E500MC,	PPCVLE,		अणुDUI, DUISपूर्णपूर्ण,

अणु"crnand",	XL(19,225),	XL_MASK,     COM,	PPCVLE,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"crand",	XL(19,257),	XL_MASK,     COM,	PPCVLE,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"hrfid",	XL(19,274),    0xffffffff, POWER5|CELL, PPC476|PPCVLE,	अणु0पूर्णपूर्ण,

अणु"crset",	XL(19,289),	XL_MASK,     PPCCOM,	PPCVLE,		अणुBT, BAT, BBAपूर्णपूर्ण,
अणु"creqv",	XL(19,289),	XL_MASK,     COM,	PPCVLE,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"urfid",	XL(19,306),	0xffffffff,  POWER9,	PPCVLE,		अणु0पूर्णपूर्ण,
अणु"stop",	XL(19,370),	0xffffffff,  POWER9,	PPCVLE,		अणु0पूर्णपूर्ण,

अणु"doze",	XL(19,402),	0xffffffff,  POWER6,	POWER9|PPCVLE,	अणु0पूर्णपूर्ण,

अणु"crorc",	XL(19,417),	XL_MASK,     COM,	PPCVLE,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"nap",		XL(19,434),	0xffffffff,  POWER6,	POWER9|PPCVLE,	अणु0पूर्णपूर्ण,

अणु"crmove",	XL(19,449),	XL_MASK,     PPCCOM,	PPCVLE,		अणुBT, BA, BBAपूर्णपूर्ण,
अणु"cror",	XL(19,449),	XL_MASK,     COM,	PPCVLE,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"sleep",	XL(19,466),	0xffffffff,  POWER6,	POWER9|PPCVLE,	अणु0पूर्णपूर्ण,
अणु"rvwinkle",	XL(19,498),	0xffffffff,  POWER6,	POWER9|PPCVLE,	अणु0पूर्णपूर्ण,

अणु"bctr",    XLO(19,BOU,528,0),		XLBOBIBB_MASK, COM,	 PPCVLE,	अणु0पूर्णपूर्ण,
अणु"bctrl",   XLO(19,BOU,528,1),		XLBOBIBB_MASK, COM,	 PPCVLE,	अणु0पूर्णपूर्ण,

अणु"bgectr",  XLOCB(19,BOF,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectr-", XLOCB(19,BOF,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctr",  XLOCB(19,BOF,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctr-", XLOCB(19,BOF,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectrl", XLOCB(19,BOF,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectrl-",XLOCB(19,BOF,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctrl", XLOCB(19,BOF,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctrl-",XLOCB(19,BOF,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectr",  XLOCB(19,BOF,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectr-", XLOCB(19,BOF,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctr",  XLOCB(19,BOF,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctr-", XLOCB(19,BOF,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectrl", XLOCB(19,BOF,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectrl-",XLOCB(19,BOF,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctrl", XLOCB(19,BOF,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctrl-",XLOCB(19,BOF,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectr",  XLOCB(19,BOF,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectr-", XLOCB(19,BOF,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectrl", XLOCB(19,BOF,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectrl-",XLOCB(19,BOF,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctr",  XLOCB(19,BOF,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctr-", XLOCB(19,BOF,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctr",  XLOCB(19,BOF,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctr-", XLOCB(19,BOF,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctrl", XLOCB(19,BOF,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctrl-",XLOCB(19,BOF,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctrl", XLOCB(19,BOF,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctrl-",XLOCB(19,BOF,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectr+", XLOCB(19,BOFP,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctr+", XLOCB(19,BOFP,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectrl+",XLOCB(19,BOFP,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctrl+",XLOCB(19,BOFP,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectr+", XLOCB(19,BOFP,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctr+", XLOCB(19,BOFP,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectrl+",XLOCB(19,BOFP,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctrl+",XLOCB(19,BOFP,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectr+", XLOCB(19,BOFP,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectrl+",XLOCB(19,BOFP,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctr+", XLOCB(19,BOFP,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctr+", XLOCB(19,BOFP,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctrl+",XLOCB(19,BOFP,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctrl+",XLOCB(19,BOFP,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectr-", XLOCB(19,BOFM4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctr-", XLOCB(19,BOFM4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectrl-",XLOCB(19,BOFM4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctrl-",XLOCB(19,BOFM4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectr-", XLOCB(19,BOFM4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctr-", XLOCB(19,BOFM4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectrl-",XLOCB(19,BOFM4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctrl-",XLOCB(19,BOFM4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectr-", XLOCB(19,BOFM4,CBEQ,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectrl-",XLOCB(19,BOFM4,CBEQ,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctr-", XLOCB(19,BOFM4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctr-", XLOCB(19,BOFM4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctrl-",XLOCB(19,BOFM4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctrl-",XLOCB(19,BOFM4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectr+", XLOCB(19,BOFP4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctr+", XLOCB(19,BOFP4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgectrl+",XLOCB(19,BOFP4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnlctrl+",XLOCB(19,BOFP4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectr+", XLOCB(19,BOFP4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctr+", XLOCB(19,BOFP4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"blectrl+",XLOCB(19,BOFP4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bngctrl+",XLOCB(19,BOFP4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectr+", XLOCB(19,BOFP4,CBEQ,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnectrl+",XLOCB(19,BOFP4,CBEQ,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctr+", XLOCB(19,BOFP4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctr+", XLOCB(19,BOFP4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnsctrl+",XLOCB(19,BOFP4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bnuctrl+",XLOCB(19,BOFP4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctr",  XLOCB(19,BOT,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctr-", XLOCB(19,BOT,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctrl", XLOCB(19,BOT,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctrl-",XLOCB(19,BOT,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctr",  XLOCB(19,BOT,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctr-", XLOCB(19,BOT,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctrl", XLOCB(19,BOT,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctrl-",XLOCB(19,BOT,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctr",  XLOCB(19,BOT,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctr-", XLOCB(19,BOT,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctrl", XLOCB(19,BOT,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctrl-",XLOCB(19,BOT,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctr",  XLOCB(19,BOT,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctr-", XLOCB(19,BOT,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctr",  XLOCB(19,BOT,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctr-", XLOCB(19,BOT,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctrl", XLOCB(19,BOT,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctrl-",XLOCB(19,BOT,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctrl", XLOCB(19,BOT,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctrl-",XLOCB(19,BOT,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctr+", XLOCB(19,BOTP,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctrl+",XLOCB(19,BOTP,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctr+", XLOCB(19,BOTP,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctrl+",XLOCB(19,BOTP,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctr+", XLOCB(19,BOTP,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctrl+",XLOCB(19,BOTP,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctr+", XLOCB(19,BOTP,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctr+", XLOCB(19,BOTP,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctrl+",XLOCB(19,BOTP,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctrl+",XLOCB(19,BOTP,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 ISA_V2|PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctr-", XLOCB(19,BOTM4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctrl-",XLOCB(19,BOTM4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctr-", XLOCB(19,BOTM4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctrl-",XLOCB(19,BOTM4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctr-", XLOCB(19,BOTM4,CBEQ,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctrl-",XLOCB(19,BOTM4,CBEQ,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctr-", XLOCB(19,BOTM4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctr-", XLOCB(19,BOTM4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctrl-",XLOCB(19,BOTM4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctrl-",XLOCB(19,BOTM4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctr+", XLOCB(19,BOTP4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bltctrl+",XLOCB(19,BOTP4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctr+", XLOCB(19,BOTP4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bgtctrl+",XLOCB(19,BOTP4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctr+", XLOCB(19,BOTP4,CBEQ,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"beqctrl+",XLOCB(19,BOTP4,CBEQ,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctr+", XLOCB(19,BOTP4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctr+", XLOCB(19,BOTP4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bsoctrl+",XLOCB(19,BOTP4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,
अणु"bunctrl+",XLOCB(19,BOTP4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCVLE,	अणुCRपूर्णपूर्ण,

अणु"bfctr",   XLO(19,BOF,528,0),		XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctr-",  XLO(19,BOF,528,0),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctrl",  XLO(19,BOF,528,1),		XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctrl-", XLO(19,BOF,528,1),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctr+",  XLO(19,BOFP,528,0),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctrl+", XLO(19,BOFP,528,1),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctr-",  XLO(19,BOFM4,528,0),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctrl-", XLO(19,BOFM4,528,1),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctr+",  XLO(19,BOFP4,528,0),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"bfctrl+", XLO(19,BOFP4,528,1),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctr",   XLO(19,BOT,528,0),		XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctr-",  XLO(19,BOT,528,0),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctrl",  XLO(19,BOT,528,1),		XLBOBB_MASK,   PPCCOM,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctrl-", XLO(19,BOT,528,1),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctr+",  XLO(19,BOTP,528,0),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctrl+", XLO(19,BOTP,528,1),		XLBOBB_MASK,   PPCCOM,	 ISA_V2|PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctr-",  XLO(19,BOTM4,528,0),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctrl-", XLO(19,BOTM4,528,1),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctr+",  XLO(19,BOTP4,528,0),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,
अणु"btctrl+", XLO(19,BOTP4,528,1),	XLBOBB_MASK,   ISA_V2,	 PPCVLE,	अणुBIपूर्णपूर्ण,

अणु"bcctr-",  XLYLK(19,528,0,0),		XLYBB_MASK,    PPCCOM,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bcctrl-", XLYLK(19,528,0,1),		XLYBB_MASK,    PPCCOM,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bcctr+",  XLYLK(19,528,1,0),		XLYBB_MASK,    PPCCOM,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bcctrl+", XLYLK(19,528,1,1),		XLYBB_MASK,    PPCCOM,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bcctr",   XLLK(19,528,0),		XLBH_MASK,     PPCCOM,	 PPCVLE,	अणुBO, BI, BHपूर्णपूर्ण,
अणु"bcc",	    XLLK(19,528,0),		XLBB_MASK,     PWRCOM,	 PPCVLE,	अणुBO, BIपूर्णपूर्ण,
अणु"bcctrl",  XLLK(19,528,1),		XLBH_MASK,     PPCCOM,	 PPCVLE,	अणुBO, BI, BHपूर्णपूर्ण,
अणु"bccl",    XLLK(19,528,1),		XLBB_MASK,     PWRCOM,	 PPCVLE,	अणुBO, BIपूर्णपूर्ण,

अणु"bctar-",  XLYLK(19,560,0,0),		XLYBB_MASK,    POWER8,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bctarl-", XLYLK(19,560,0,1),		XLYBB_MASK,    POWER8,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bctar+",  XLYLK(19,560,1,0),		XLYBB_MASK,    POWER8,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bctarl+", XLYLK(19,560,1,1),		XLYBB_MASK,    POWER8,	 PPCVLE,	अणुBOE, BIपूर्णपूर्ण,
अणु"bctar",   XLLK(19,560,0),		XLBH_MASK,     POWER8,	 PPCVLE,	अणुBO, BI, BHपूर्णपूर्ण,
अणु"bctarl",  XLLK(19,560,1),		XLBH_MASK,     POWER8,	 PPCVLE,	अणुBO, BI, BHपूर्णपूर्ण,

अणु"rlwimi",	M(20,0),	M_MASK,	     PPCCOM,	PPCVLE,		अणुRA, RS, SH, MBE, MEपूर्णपूर्ण,
अणु"rlimi",	M(20,0),	M_MASK,	     PWRCOM,	PPCVLE,		अणुRA, RS, SH, MBE, MEपूर्णपूर्ण,

अणु"rlwimi.",	M(20,1),	M_MASK,	     PPCCOM,	PPCVLE,		अणुRA, RS, SH, MBE, MEपूर्णपूर्ण,
अणु"rlimi.",	M(20,1),	M_MASK,	     PWRCOM,	PPCVLE,		अणुRA, RS, SH, MBE, MEपूर्णपूर्ण,

अणु"rotlwi",	MME(21,31,0),	MMBME_MASK,  PPCCOM,	PPCVLE,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"clrlwi",	MME(21,31,0),	MSHME_MASK,  PPCCOM,	PPCVLE,		अणुRA, RS, MBपूर्णपूर्ण,
अणु"rlwinm",	M(21,0),	M_MASK,	     PPCCOM,	PPCVLE,		अणुRA, RS, SH, MBE, MEपूर्णपूर्ण,
अणु"rlinm",	M(21,0),	M_MASK,	     PWRCOM,	PPCVLE,		अणुRA, RS, SH, MBE, MEपूर्णपूर्ण,
अणु"rotlwi.",	MME(21,31,1),	MMBME_MASK,  PPCCOM,	PPCVLE,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"clrlwi.",	MME(21,31,1),	MSHME_MASK,  PPCCOM,	PPCVLE,		अणुRA, RS, MBपूर्णपूर्ण,
अणु"rlwinm.",	M(21,1),	M_MASK,	     PPCCOM,	PPCVLE,		अणुRA, RS, SH, MBE, MEपूर्णपूर्ण,
अणु"rlinm.",	M(21,1),	M_MASK,	     PWRCOM,	PPCVLE,		अणुRA, RS, SH, MBE, MEपूर्णपूर्ण,

अणु"rlmi",	M(22,0),	M_MASK,	     M601,	PPCVLE,		अणुRA, RS, RB, MBE, MEपूर्णपूर्ण,
अणु"rlmi.",	M(22,1),	M_MASK,	     M601,	PPCVLE,		अणुRA, RS, RB, MBE, MEपूर्णपूर्ण,

अणु"rotlw",	MME(23,31,0),	MMBME_MASK,  PPCCOM,	PPCVLE,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"rlwnm",	M(23,0),	M_MASK,	     PPCCOM,	PPCVLE,		अणुRA, RS, RB, MBE, MEपूर्णपूर्ण,
अणु"rlnm",	M(23,0),	M_MASK,	     PWRCOM,	PPCVLE,		अणुRA, RS, RB, MBE, MEपूर्णपूर्ण,
अणु"rotlw.",	MME(23,31,1),	MMBME_MASK,  PPCCOM,	PPCVLE,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"rlwnm.",	M(23,1),	M_MASK,	     PPCCOM,	PPCVLE,		अणुRA, RS, RB, MBE, MEपूर्णपूर्ण,
अणु"rlnm.",	M(23,1),	M_MASK,	     PWRCOM,	PPCVLE,		अणुRA, RS, RB, MBE, MEपूर्णपूर्ण,

अणु"nop",		OP(24),		0xffffffff,  PPCCOM,	PPCVLE,		अणु0पूर्णपूर्ण,
अणु"ori",		OP(24),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,
अणु"oril",	OP(24),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,

अणु"oris",	OP(25),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,
अणु"oriu",	OP(25),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,

अणु"xnop",	OP(26),		0xffffffff,  PPCCOM,	PPCVLE,		अणु0पूर्णपूर्ण,
अणु"xori",	OP(26),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,
अणु"xoril",	OP(26),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,

अणु"xoris",	OP(27),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,
अणु"xoriu",	OP(27),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,

अणु"andi.",	OP(28),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,
अणु"andil.",	OP(28),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,

अणु"andis.",	OP(29),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,
अणु"andiu.",	OP(29),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRA, RS, UIपूर्णपूर्ण,

अणु"rotldi",	MD(30,0,0),	MDMB_MASK,   PPC64,	PPCVLE,		अणुRA, RS, SH6पूर्णपूर्ण,
अणु"clrldi",	MD(30,0,0),	MDSH_MASK,   PPC64,	PPCVLE,		अणुRA, RS, MB6पूर्णपूर्ण,
अणु"rldicl",	MD(30,0,0),	MD_MASK,     PPC64,	PPCVLE,		अणुRA, RS, SH6, MB6पूर्णपूर्ण,
अणु"rotldi.",	MD(30,0,1),	MDMB_MASK,   PPC64,	PPCVLE,		अणुRA, RS, SH6पूर्णपूर्ण,
अणु"clrldi.",	MD(30,0,1),	MDSH_MASK,   PPC64,	PPCVLE,		अणुRA, RS, MB6पूर्णपूर्ण,
अणु"rldicl.",	MD(30,0,1),	MD_MASK,     PPC64,	PPCVLE,		अणुRA, RS, SH6, MB6पूर्णपूर्ण,

अणु"rldicr",	MD(30,1,0),	MD_MASK,     PPC64,	PPCVLE,		अणुRA, RS, SH6, ME6पूर्णपूर्ण,
अणु"rldicr.",	MD(30,1,1),	MD_MASK,     PPC64,	PPCVLE,		अणुRA, RS, SH6, ME6पूर्णपूर्ण,

अणु"rldic",	MD(30,2,0),	MD_MASK,     PPC64,	PPCVLE,		अणुRA, RS, SH6, MB6पूर्णपूर्ण,
अणु"rldic.",	MD(30,2,1),	MD_MASK,     PPC64,	PPCVLE,		अणुRA, RS, SH6, MB6पूर्णपूर्ण,

अणु"rldimi",	MD(30,3,0),	MD_MASK,     PPC64,	PPCVLE,		अणुRA, RS, SH6, MB6पूर्णपूर्ण,
अणु"rldimi.",	MD(30,3,1),	MD_MASK,     PPC64,	PPCVLE,		अणुRA, RS, SH6, MB6पूर्णपूर्ण,

अणु"rotld",	MDS(30,8,0),	MDSMB_MASK,  PPC64,	PPCVLE,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"rldcl",	MDS(30,8,0),	MDS_MASK,    PPC64,	PPCVLE,		अणुRA, RS, RB, MB6पूर्णपूर्ण,
अणु"rotld.",	MDS(30,8,1),	MDSMB_MASK,  PPC64,	PPCVLE,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"rldcl.",	MDS(30,8,1),	MDS_MASK,    PPC64,	PPCVLE,		अणुRA, RS, RB, MB6पूर्णपूर्ण,

अणु"rldcr",	MDS(30,9,0),	MDS_MASK,    PPC64,	PPCVLE,		अणुRA, RS, RB, ME6पूर्णपूर्ण,
अणु"rldcr.",	MDS(30,9,1),	MDS_MASK,    PPC64,	PPCVLE,		अणुRA, RS, RB, ME6पूर्णपूर्ण,

अणु"cmpw",	XOPL(31,0,0),	XCMPL_MASK,  PPCCOM,	0,		अणुOBF, RA, RBपूर्णपूर्ण,
अणु"cmpd",	XOPL(31,0,1),	XCMPL_MASK,  PPC64,	0,		अणुOBF, RA, RBपूर्णपूर्ण,
अणु"cmp",		X(31,0),	XCMP_MASK,   PPC,	0,		अणुBF, L32OPT, RA, RBपूर्णपूर्ण,
अणु"cmp",		X(31,0),	XCMPL_MASK,  PWRCOM,	PPC,		अणुBF, RA, RBपूर्णपूर्ण,

अणु"twlgt",	XTO(31,4,TOLGT), XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tlgt",	XTO(31,4,TOLGT), XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twllt",	XTO(31,4,TOLLT), XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tllt",	XTO(31,4,TOLLT), XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tweq",	XTO(31,4,TOEQ),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"teq",		XTO(31,4,TOEQ),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twlge",	XTO(31,4,TOLGE), XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tlge",	XTO(31,4,TOLGE), XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twlnl",	XTO(31,4,TOLNL), XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tlnl",	XTO(31,4,TOLNL), XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twlle",	XTO(31,4,TOLLE), XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tlle",	XTO(31,4,TOLLE), XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twlng",	XTO(31,4,TOLNG), XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tlng",	XTO(31,4,TOLNG), XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twgt",	XTO(31,4,TOGT),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tgt",		XTO(31,4,TOGT),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twge",	XTO(31,4,TOGE),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tge",		XTO(31,4,TOGE),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twnl",	XTO(31,4,TONL),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tnl",		XTO(31,4,TONL),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twlt",	XTO(31,4,TOLT),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tlt",		XTO(31,4,TOLT),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twle",	XTO(31,4,TOLE),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tle",		XTO(31,4,TOLE),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twng",	XTO(31,4,TONG),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tng",		XTO(31,4,TONG),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"twne",	XTO(31,4,TONE),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tne",		XTO(31,4,TONE),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"trap",	XTO(31,4,TOU),	 0xffffffff, PPCCOM,	0,		अणु0पूर्णपूर्ण,
अणु"twu",		XTO(31,4,TOU),	 XTO_MASK,   PPCCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tu",		XTO(31,4,TOU),	 XTO_MASK,   PWRCOM,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tw",		X(31,4),	 X_MASK,     PPCCOM,	0,		अणुTO, RA, RBपूर्णपूर्ण,
अणु"t",		X(31,4),	 X_MASK,     PWRCOM,	0,		अणुTO, RA, RBपूर्णपूर्ण,

अणु"lvsl",	X(31,6),	X_MASK,	     PPCVEC,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"lvebx",	X(31,7),	X_MASK,	     PPCVEC,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"lbfcmx",	APU(31,7,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"subfc",	XO(31,8,0,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sf",		XO(31,8,0,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"subc",	XO(31,8,0,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RB, RAपूर्णपूर्ण,
अणु"subfc.",	XO(31,8,0,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sf.",		XO(31,8,0,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"subc.",	XO(31,8,0,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RB, RAपूर्णपूर्ण,

अणु"mulhdu",	XO(31,9,0,0),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulhdu.",	XO(31,9,0,1),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"addc",	XO(31,10,0,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"a",		XO(31,10,0,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"addc.",	XO(31,10,0,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"a.",		XO(31,10,0,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"mulhwu",	XO(31,11,0,0),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulhwu.",	XO(31,11,0,1),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxsiwzx",	X(31,12),	XX1_MASK,    PPCVSX2,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"isellt",	X(31,15),	X_MASK,	     PPCISEL,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"tlbilxlpid",	XTO(31,18,0),	XTO_MASK, E500MC|PPCA2,	0,		अणु0पूर्णपूर्ण,
अणु"tlbilxpid",	XTO(31,18,1),	XTO_MASK, E500MC|PPCA2,	0,		अणु0पूर्णपूर्ण,
अणु"tlbilxva",	XTO(31,18,3),	XTO_MASK, E500MC|PPCA2,	0,		अणुRA0, RBपूर्णपूर्ण,
अणु"tlbilx",	X(31,18),	X_MASK,	  E500MC|PPCA2,	0,		अणुT, RA0, RBपूर्णपूर्ण,

अणु"mfcr",	XFXM(31,19,0,0), XFXFXM_MASK, COM,	0,		अणुRT, FXM4पूर्णपूर्ण,
अणु"mfocrf",	XFXM(31,19,0,1), XFXFXM_MASK, COM,	0,		अणुRT, FXMपूर्णपूर्ण,

अणु"lwarx",	X(31,20),	XEH_MASK,    PPC,	0,		अणुRT, RA0, RB, EHपूर्णपूर्ण,

अणु"ldx",		X(31,21),	X_MASK,	     PPC64,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"icbt",	X(31,22),  X_MASK, BOOKE|PPCE300|PPCA2|PPC476, 0,	अणुCT, RA0, RBपूर्णपूर्ण,

अणु"lwzx",	X(31,23),	X_MASK,	     PPCCOM,	0,		अणुRT, RA0, RBपूर्णपूर्ण,
अणु"lx",		X(31,23),	X_MASK,	     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"slw",		XRC(31,24,0),	X_MASK,	     PPCCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sl",		XRC(31,24,0),	X_MASK,	     PWRCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"slw.",	XRC(31,24,1),	X_MASK,	     PPCCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sl.",		XRC(31,24,1),	X_MASK,	     PWRCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"cntlzw",	XRC(31,26,0),	XRB_MASK,    PPCCOM,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"cntlz",	XRC(31,26,0),	XRB_MASK,    PWRCOM,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"cntlzw.",	XRC(31,26,1),	XRB_MASK,    PPCCOM,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"cntlz.",	XRC(31,26,1),	XRB_MASK,    PWRCOM,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"sld",		XRC(31,27,0),	X_MASK,	     PPC64,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sld.",	XRC(31,27,1),	X_MASK,	     PPC64,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"and",		XRC(31,28,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"and.",	XRC(31,28,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"maskg",	XRC(31,29,0),	X_MASK,	     M601,	PPCA2,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"maskg.",	XRC(31,29,1),	X_MASK,	     M601,	PPCA2,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"ldepx",	X(31,29),	X_MASK,	  E500MC|PPCA2, 0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"waitasec",	X(31,30),      XRTRARB_MASK, POWER8,	POWER9,		अणु0पूर्णपूर्ण,
अणु"wait",	X(31,30),	XWC_MASK,    POWER9,	0,		अणुWCपूर्णपूर्ण,

अणु"lwepx",	X(31,31),	X_MASK,	  E500MC|PPCA2, 0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"cmplw",	XOPL(31,32,0),	XCMPL_MASK,  PPCCOM,	0,		अणुOBF, RA, RBपूर्णपूर्ण,
अणु"cmpld",	XOPL(31,32,1),	XCMPL_MASK,  PPC64,	0,		अणुOBF, RA, RBपूर्णपूर्ण,
अणु"cmpl",	X(31,32),	XCMP_MASK,   PPC,	0,		अणुBF, L32OPT, RA, RBपूर्णपूर्ण,
अणु"cmpl",	X(31,32),	XCMPL_MASK,  PWRCOM,	PPC,		अणुBF, RA, RBपूर्णपूर्ण,

अणु"lvsr",	X(31,38),	X_MASK,	     PPCVEC,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"lvehx",	X(31,39),	X_MASK,	     PPCVEC,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"lhfcmx",	APU(31,39,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"mviwsplt",	X(31,46),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA, RBपूर्णपूर्ण,

अणु"iselgt",	X(31,47),	X_MASK,	     PPCISEL,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"lvewx",	X(31,71),	X_MASK,	     PPCVEC,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"addg6s",	XO(31,74,0,0),	XO_MASK,     POWER6,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxsiwax",	X(31,76),	XX1_MASK,    PPCVSX2,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"iseleq",	X(31,79),	X_MASK,	     PPCISEL,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"isel",	XISEL(31,15), XISEL_MASK, PPCISEL|TITAN, 0,		अणुRT, RA0, RB, CRBपूर्णपूर्ण,

अणु"subf",	XO(31,40,0,0),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sub",		XO(31,40,0,0),	XO_MASK,     PPC,	0,		अणुRT, RB, RAपूर्णपूर्ण,
अणु"subf.",	XO(31,40,0,1),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sub.",	XO(31,40,0,1),	XO_MASK,     PPC,	0,		अणुRT, RB, RAपूर्णपूर्ण,

अणु"mfvsrd",	X(31,51),	XX1RB_MASK,   PPCVSX2,	0,		अणुRA, XS6पूर्णपूर्ण,
अणु"mffprd",	X(31,51),	XX1RB_MASK|1, PPCVSX2,	0,		अणुRA, FRSपूर्णपूर्ण,
अणु"mfvrd",	X(31,51)|1,	XX1RB_MASK|1, PPCVSX2,	0,		अणुRA, VSपूर्णपूर्ण,
अणु"eratilx",	X(31,51),	X_MASK,	     PPCA2,	0,		अणुERAT_T, RA, RBपूर्णपूर्ण,

अणु"lbarx",	X(31,52),	XEH_MASK, POWER8|E6500, 0,		अणुRT, RA0, RB, EHपूर्णपूर्ण,

अणु"ldux",	X(31,53),	X_MASK,	     PPC64,	0,		अणुRT, RAL, RBपूर्णपूर्ण,

अणु"dcbst",	X(31,54),	XRT_MASK,    PPC,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"lwzux",	X(31,55),	X_MASK,	     PPCCOM,	0,		अणुRT, RAL, RBपूर्णपूर्ण,
अणु"lux",		X(31,55),	X_MASK,	     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"cntlzd",	XRC(31,58,0),	XRB_MASK,    PPC64,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"cntlzd.",	XRC(31,58,1),	XRB_MASK,    PPC64,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"andc",	XRC(31,60,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"andc.",	XRC(31,60,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"waitrsv",	X(31,62)|(1<<21), 0xffffffff, E500MC|PPCA2, 0,		अणु0पूर्णपूर्ण,
अणु"waitimpl",	X(31,62)|(2<<21), 0xffffffff, E500MC|PPCA2, 0,		अणु0पूर्णपूर्ण,
अणु"wait",	X(31,62),	XWC_MASK,    E500MC|PPCA2, 0,		अणुWCपूर्णपूर्ण,

अणु"dcbstep",	XRT(31,63,0),	XRT_MASK,    E500MC|PPCA2, 0,		अणुRA0, RBपूर्णपूर्ण,

अणु"tdlgt",	XTO(31,68,TOLGT), XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdllt",	XTO(31,68,TOLLT), XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdeq",	XTO(31,68,TOEQ),  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdlge",	XTO(31,68,TOLGE), XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdlnl",	XTO(31,68,TOLNL), XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdlle",	XTO(31,68,TOLLE), XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdlng",	XTO(31,68,TOLNG), XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdgt",	XTO(31,68,TOGT),  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdge",	XTO(31,68,TOGE),  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdnl",	XTO(31,68,TONL),  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdlt",	XTO(31,68,TOLT),  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdle",	XTO(31,68,TOLE),  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdng",	XTO(31,68,TONG),  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdne",	XTO(31,68,TONE),  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"tdu",		XTO(31,68,TOU),	  XTO_MASK,  PPC64,	0,		अणुRA, RBपूर्णपूर्ण,
अणु"td",		X(31,68),	X_MASK,	     PPC64,	0,		अणुTO, RA, RBपूर्णपूर्ण,

अणु"lwfcmx",	APU(31,71,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,
अणु"mulhd",	XO(31,73,0,0),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulhd.",	XO(31,73,0,1),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"mulhw",	XO(31,75,0,0),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulhw.",	XO(31,75,0,1),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"dlmzb",	XRC(31,78,0), X_MASK, PPC403|PPC440|TITAN, 0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"dlmzb.",	XRC(31,78,1), X_MASK, PPC403|PPC440|TITAN, 0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"mtsrd",	X(31,82),  XRB_MASK|(1<<20), PPC64,	0,		अणुSR, RSपूर्णपूर्ण,

अणु"mfmsr",	X(31,83),	XRARB_MASK,  COM,	0,		अणुRTपूर्णपूर्ण,

अणु"ldarx",	X(31,84),	XEH_MASK,    PPC64,	0,		अणुRT, RA0, RB, EHपूर्णपूर्ण,

अणु"dcbfl",	XOPL(31,86,1),	XRT_MASK,    POWER5,	PPC476,		अणुRA0, RBपूर्णपूर्ण,
अणु"dcbf",	X(31,86),	XLRT_MASK,   PPC,	0,		अणुRA0, RB, L2OPTपूर्णपूर्ण,

अणु"lbzx",	X(31,87),	X_MASK,	     COM,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"lbepx",	X(31,95),	X_MASK,	  E500MC|PPCA2, 0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"dni",		XRC(31,97,1),	XRB_MASK,    E6500,	0,		अणुDUI, DCTLपूर्णपूर्ण,

अणु"lvx",		X(31,103),	X_MASK,	     PPCVEC,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"lqfcmx",	APU(31,103,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"neg",		XO(31,104,0,0),	XORB_MASK,   COM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"neg.",	XO(31,104,0,1),	XORB_MASK,   COM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"mul",		XO(31,107,0,0),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mul.",	XO(31,107,0,1),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"mvidsplt",	X(31,110),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA, RBपूर्णपूर्ण,

अणु"mtsrdin",	X(31,114),	XRA_MASK,    PPC64,	0,		अणुRS, RBपूर्णपूर्ण,

अणु"mffprwz",	X(31,115),	XX1RB_MASK|1, PPCVSX2,	0,		अणुRA, FRSपूर्णपूर्ण,
अणु"mfvrwz",	X(31,115)|1,	XX1RB_MASK|1, PPCVSX2,	0,		अणुRA, VSपूर्णपूर्ण,
अणु"mfvsrwz",	X(31,115),	XX1RB_MASK,   PPCVSX2,	0,		अणुRA, XS6पूर्णपूर्ण,

अणु"lharx",	X(31,116),	XEH_MASK, POWER8|E6500, 0,		अणुRT, RA0, RB, EHपूर्णपूर्ण,

अणु"clf",		X(31,118),	XTO_MASK,    POWER,	0,		अणुRA, RBपूर्णपूर्ण,

अणु"lbzux",	X(31,119),	X_MASK,	     COM,	0,		अणुRT, RAL, RBपूर्णपूर्ण,

अणु"popcntb",	X(31,122),	XRB_MASK,    POWER5,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"not",		XRC(31,124,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBSपूर्णपूर्ण,
अणु"nor",		XRC(31,124,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"not.",	XRC(31,124,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBSपूर्णपूर्ण,
अणु"nor.",	XRC(31,124,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"dcbfep",	XRT(31,127,0),	XRT_MASK, E500MC|PPCA2, 0,		अणुRA0, RBपूर्णपूर्ण,

अणु"setb",	X(31,128),	XRB_MASK|(3<<16), POWER9, 0,		अणुRT, BFAपूर्णपूर्ण,

अणु"wrtee",	X(31,131), XRARB_MASK, PPC403|BOOKE|PPCA2|PPC476, 0,	अणुRSपूर्णपूर्ण,

अणु"dcbtstls",	X(31,134),	X_MASK, PPCCHLK|PPC476|TITAN, 0,	अणुCT, RA0, RBपूर्णपूर्ण,

अणु"stvebx",	X(31,135),	X_MASK,	     PPCVEC,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"stbfcmx",	APU(31,135,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"subfe",	XO(31,136,0,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sfe",		XO(31,136,0,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"subfe.",	XO(31,136,0,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sfe.",	XO(31,136,0,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"adde",	XO(31,138,0,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ae",		XO(31,138,0,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"adde.",	XO(31,138,0,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ae.",		XO(31,138,0,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"stxsiwx",	X(31,140),	XX1_MASK,    PPCVSX2,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"msgsndp",	XRTRA(31,142,0,0), XRTRA_MASK, POWER8,	0,		अणुRBपूर्णपूर्ण,
अणु"dcbtstlse",	X(31,142),	X_MASK,	     PPCCHLK,	E500MC,		अणुCT, RA0, RBपूर्णपूर्ण,

अणु"mtcr",	XFXM(31,144,0xff,0), XRARB_MASK, COM,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcrf",	XFXM(31,144,0,0), XFXFXM_MASK, COM,	0,		अणुFXM, RSपूर्णपूर्ण,
अणु"mtocrf",	XFXM(31,144,0,1), XFXFXM_MASK, COM,	0,		अणुFXM, RSपूर्णपूर्ण,

अणु"mtmsr",	X(31,146),	XRLARB_MASK, COM,	0,		अणुRS, A_Lपूर्णपूर्ण,

अणु"mtsle",	X(31,147),    XRTLRARB_MASK, POWER8,	0,		अणुLपूर्णपूर्ण,

अणु"eratsx",	XRC(31,147,0),	X_MASK,	     PPCA2,	0,		अणुRT, RA0, RBपूर्णपूर्ण,
अणु"eratsx.",	XRC(31,147,1),	X_MASK,	     PPCA2,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"stdx",	X(31,149),	X_MASK,	     PPC64,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stwcx.",	XRC(31,150,1),	X_MASK,	     PPC,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stwx",	X(31,151),	X_MASK,	     PPCCOM,	0,		अणुRS, RA0, RBपूर्णपूर्ण,
अणु"stx",		X(31,151),	X_MASK,	     PWRCOM,	0,		अणुRS, RA, RBपूर्णपूर्ण,

अणु"slq",		XRC(31,152,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"slq.",	XRC(31,152,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"sle",		XRC(31,153,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sle.",	XRC(31,153,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"prtyw",	X(31,154),    XRB_MASK, POWER6|PPCA2|PPC476, 0,		अणुRA, RSपूर्णपूर्ण,

अणु"stdepx",	X(31,157),	X_MASK,	  E500MC|PPCA2, 0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stwepx",	X(31,159),	X_MASK,	  E500MC|PPCA2, 0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"wrteei",	X(31,163), XE_MASK, PPC403|BOOKE|PPCA2|PPC476, 0,	अणुEपूर्णपूर्ण,

अणु"dcbtls",	X(31,166),	X_MASK,	 PPCCHLK|PPC476|TITAN, 0,	अणुCT, RA0, RBपूर्णपूर्ण,

अणु"stvehx",	X(31,167),	X_MASK,	     PPCVEC,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"sthfcmx",	APU(31,167,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"addex",	ZRC(31,170,0),	Z2_MASK,     POWER9,	0,		अणुRT, RA, RB, CYपूर्णपूर्ण,

अणु"msgclrp",	XRTRA(31,174,0,0), XRTRA_MASK, POWER8,	0,		अणुRBपूर्णपूर्ण,
अणु"dcbtlse",	X(31,174),	X_MASK,	     PPCCHLK,	E500MC,		अणुCT, RA0, RBपूर्णपूर्ण,

अणु"mtmsrd",	X(31,178),	XRLARB_MASK, PPC64,	0,		अणुRS, A_Lपूर्णपूर्ण,

अणु"mtvsrd",	X(31,179),	XX1RB_MASK,   PPCVSX2,	0,		अणुXT6, RAपूर्णपूर्ण,
अणु"mtfprd",	X(31,179),	XX1RB_MASK|1, PPCVSX2,	0,		अणुFRT, RAपूर्णपूर्ण,
अणु"mtvrd",	X(31,179)|1,	XX1RB_MASK|1, PPCVSX2,	0,		अणुVD, RAपूर्णपूर्ण,
अणु"eratre",	X(31,179),	X_MASK,	     PPCA2,	0,		अणुRT, RA, WSपूर्णपूर्ण,

अणु"stdux",	X(31,181),	X_MASK,	     PPC64,	0,		अणुRS, RAS, RBपूर्णपूर्ण,

अणु"stqcx.",	XRC(31,182,1),	X_MASK,	     POWER8,	0,		अणुRSQ, RA0, RBपूर्णपूर्ण,
अणु"wchkall",	X(31,182),	X_MASK,	     PPCA2,	0,		अणुOBFपूर्णपूर्ण,

अणु"stwux",	X(31,183),	X_MASK,	     PPCCOM,	0,		अणुRS, RAS, RBपूर्णपूर्ण,
अणु"stux",	X(31,183),	X_MASK,	     PWRCOM,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"sliq",	XRC(31,184,0),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"sliq.",	XRC(31,184,1),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"prtyd",	X(31,186),	XRB_MASK, POWER6|PPCA2,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"cmprb",	X(31,192),	XCMP_MASK,   POWER9,	0,		अणुBF, L, RA, RBपूर्णपूर्ण,

अणु"icblq.",	XRC(31,198,1),	X_MASK,	     E6500,	0,		अणुCT, RA0, RBपूर्णपूर्ण,

अणु"stvewx",	X(31,199),	X_MASK,	     PPCVEC,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"stwfcmx",	APU(31,199,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"subfze",	XO(31,200,0,0),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"sfze",	XO(31,200,0,0),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"subfze.",	XO(31,200,0,1),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"sfze.",	XO(31,200,0,1),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"addze",	XO(31,202,0,0),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"aze",		XO(31,202,0,0),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"addze.",	XO(31,202,0,1),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"aze.",	XO(31,202,0,1),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"msgsnd",	XRTRA(31,206,0,0), XRTRA_MASK, E500MC|PPCA2|POWER8, 0,	अणुRBपूर्णपूर्ण,

अणु"mtsr",	X(31,210), XRB_MASK|(1<<20), COM,	NON32,		अणुSR, RSपूर्णपूर्ण,

अणु"mtfprwa",	X(31,211),	XX1RB_MASK|1, PPCVSX2,	0,		अणुFRT, RAपूर्णपूर्ण,
अणु"mtvrwa",	X(31,211)|1,	XX1RB_MASK|1, PPCVSX2,	0,		अणुVD, RAपूर्णपूर्ण,
अणु"mtvsrwa",	X(31,211),	XX1RB_MASK,   PPCVSX2,	0,		अणुXT6, RAपूर्णपूर्ण,
अणु"eratwe",	X(31,211),	X_MASK,	     PPCA2,	0,		अणुRS, RA, WSपूर्णपूर्ण,

अणु"ldawx.",	XRC(31,212,1),	X_MASK,	     PPCA2,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"stdcx.",	XRC(31,214,1),	X_MASK,	     PPC64,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stbx",	X(31,215),	X_MASK,	     COM,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"sllq",	XRC(31,216,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sllq.",	XRC(31,216,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"sleq",	XRC(31,217,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sleq.",	XRC(31,217,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"stbepx",	X(31,223),	X_MASK,	  E500MC|PPCA2, 0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"cmpeqb",	X(31,224),	XCMPL_MASK,  POWER9,	0,		अणुBF, RA, RBपूर्णपूर्ण,

अणु"icblc",	X(31,230),	X_MASK,	PPCCHLK|PPC476|TITAN, 0,	अणुCT, RA0, RBपूर्णपूर्ण,

अणु"stvx",	X(31,231),	X_MASK,	     PPCVEC,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"stqfcmx",	APU(31,231,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"subfme",	XO(31,232,0,0),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"sfme",	XO(31,232,0,0),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"subfme.",	XO(31,232,0,1),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"sfme.",	XO(31,232,0,1),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"mulld",	XO(31,233,0,0),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulld.",	XO(31,233,0,1),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"addme",	XO(31,234,0,0),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"ame",		XO(31,234,0,0),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"addme.",	XO(31,234,0,1),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"ame.",	XO(31,234,0,1),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"mullw",	XO(31,235,0,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"muls",	XO(31,235,0,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mullw.",	XO(31,235,0,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"muls.",	XO(31,235,0,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"icblce",	X(31,238),	X_MASK,	     PPCCHLK,	E500MC|PPCA2,	अणुCT, RA, RBपूर्णपूर्ण,
अणु"msgclr",	XRTRA(31,238,0,0), XRTRA_MASK, E500MC|PPCA2|POWER8, 0,	अणुRBपूर्णपूर्ण,
अणु"mtsrin",	X(31,242),	XRA_MASK,    PPC,	NON32,		अणुRS, RBपूर्णपूर्ण,
अणु"mtsri",	X(31,242),	XRA_MASK,    POWER,	NON32,		अणुRS, RBपूर्णपूर्ण,

अणु"mtfprwz",	X(31,243),	XX1RB_MASK|1, PPCVSX2,	0,		अणुFRT, RAपूर्णपूर्ण,
अणु"mtvrwz",	X(31,243)|1,	XX1RB_MASK|1, PPCVSX2,	0,		अणुVD, RAपूर्णपूर्ण,
अणु"mtvsrwz",	X(31,243),	XX1RB_MASK,   PPCVSX2,	0,		अणुXT6, RAपूर्णपूर्ण,

अणु"dcbtstt",	XRT(31,246,0x10), XRT_MASK,  POWER7,	0,		अणुRA0, RBपूर्णपूर्ण,
अणु"dcbtst",	X(31,246),	X_MASK,	     POWER4,	DCBT_EO,	अणुRA0, RB, CTपूर्णपूर्ण,
अणु"dcbtst",	X(31,246),	X_MASK,	     DCBT_EO,	0,		अणुCT, RA0, RBपूर्णपूर्ण,
अणु"dcbtst",	X(31,246),	X_MASK,	     PPC,	POWER4|DCBT_EO,	अणुRA0, RBपूर्णपूर्ण,

अणु"stbux",	X(31,247),	X_MASK,	     COM,	0,		अणुRS, RAS, RBपूर्णपूर्ण,

अणु"slliq",	XRC(31,248,0),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"slliq.",	XRC(31,248,1),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"bpermd",	X(31,252),	X_MASK,	  POWER7|PPCA2,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"dcbtstep",	XRT(31,255,0),	X_MASK,	  E500MC|PPCA2, 0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"mfdcrx",	X(31,259),	X_MASK, BOOKE|PPCA2|PPC476, TITAN,	अणुRS, RAपूर्णपूर्ण,
अणु"mfdcrx.",	XRC(31,259,1),	X_MASK,	     PPCA2,	0,		अणुRS, RAपूर्णपूर्ण,

अणु"lvexbx",	X(31,261),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"icbt",	X(31,262),	XRT_MASK,    PPC403,	0,		अणुRA, RBपूर्णपूर्ण,

अणु"lvepxl",	X(31,263),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"ldfcmx",	APU(31,263,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,
अणु"doz",		XO(31,264,0,0),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"doz.",	XO(31,264,0,1),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"modud",	X(31,265),	X_MASK,	     POWER9,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"add",		XO(31,266,0,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"cax",		XO(31,266,0,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"add.",	XO(31,266,0,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"cax.",	XO(31,266,0,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"moduw",	X(31,267),	X_MASK,	     POWER9,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxvx",	X(31,268),	XX1_MASK|1<<6, PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,
अणु"lxvl",	X(31,269),	XX1_MASK,    PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"ehpriv",	X(31,270),	0xffffffff,  E500MC|PPCA2, 0,		अणु0पूर्णपूर्ण,

अणु"tlbiel",	X(31,274),	X_MASK|1<<20,POWER9,	PPC476,		अणुRB, RSO, RIC, PRS, X_Rपूर्णपूर्ण,
अणु"tlbiel",	X(31,274),	XRTLRA_MASK, POWER4,	POWER9|PPC476,	अणुRB, LOPTपूर्णपूर्ण,

अणु"mfapidi",	X(31,275),	X_MASK,	     BOOKE,	E500|TITAN,	अणुRT, RAपूर्णपूर्ण,

अणु"lqarx",	X(31,276),	XEH_MASK,    POWER8,	0,		अणुRTQ, RAX, RBX, EHपूर्णपूर्ण,

अणु"lscbx",	XRC(31,277,0),	X_MASK,	     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"lscbx.",	XRC(31,277,1),	X_MASK,	     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"dcbtt",	XRT(31,278,0x10), XRT_MASK,  POWER7,	0,		अणुRA0, RBपूर्णपूर्ण,
अणु"dcbt",	X(31,278),	X_MASK,	     POWER4,	DCBT_EO,	अणुRA0, RB, CTपूर्णपूर्ण,
अणु"dcbt",	X(31,278),	X_MASK,	     DCBT_EO,	0,		अणुCT, RA0, RBपूर्णपूर्ण,
अणु"dcbt",	X(31,278),	X_MASK,	     PPC,	POWER4|DCBT_EO,	अणुRA0, RBपूर्णपूर्ण,

अणु"lhzx",	X(31,279),	X_MASK,	     COM,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"cdtbcd",	X(31,282),	XRB_MASK,    POWER6,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"eqv",		XRC(31,284,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"eqv.",	XRC(31,284,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"lhepx",	X(31,287),	X_MASK,	  E500MC|PPCA2, 0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"mfdcrux",	X(31,291),	X_MASK,	     PPC464,	0,		अणुRS, RAपूर्णपूर्ण,

अणु"lvexhx",	X(31,293),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"lvepx",	X(31,295),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"lxvll",	X(31,301),	XX1_MASK,    PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"mfbhrbe",	X(31,302),	X_MASK,	     POWER8,	0,		अणुRT, BHRBEपूर्णपूर्ण,

अणु"tlbie",	X(31,306),	X_MASK|1<<20,POWER9,	TITAN,		अणुRB, RS, RIC, PRS, X_Rपूर्णपूर्ण,
अणु"tlbie",	X(31,306),	XRA_MASK,    POWER7,	POWER9|TITAN,	अणुRB, RSपूर्णपूर्ण,
अणु"tlbie",	X(31,306),	XRTLRA_MASK, PPC,    E500|POWER7|TITAN,	अणुRB, LOPTपूर्णपूर्ण,
अणु"tlbi",	X(31,306),	XRT_MASK,    POWER,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"mfvsrld",	X(31,307),	XX1RB_MASK,  PPCVSX3,	0,		अणुRA, XS6पूर्णपूर्ण,

अणु"ldmx",	X(31,309),	X_MASK,	     POWER9,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"eciwx",	X(31,310),	X_MASK,	     PPC,	E500|TITAN,	अणुRT, RA0, RBपूर्णपूर्ण,

अणु"lhzux",	X(31,311),	X_MASK,	     COM,	0,		अणुRT, RAL, RBपूर्णपूर्ण,

अणु"cbcdtd",	X(31,314),	XRB_MASK,    POWER6,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"xor",		XRC(31,316,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"xor.",	XRC(31,316,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"dcbtep",	XRT(31,319,0),	X_MASK,	  E500MC|PPCA2, 0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"mfexisr",	XSPR(31,323, 64), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfexier",	XSPR(31,323, 66), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbr0",	XSPR(31,323,128), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbr1",	XSPR(31,323,129), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbr2",	XSPR(31,323,130), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbr3",	XSPR(31,323,131), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbr4",	XSPR(31,323,132), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbr5",	XSPR(31,323,133), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbr6",	XSPR(31,323,134), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbr7",	XSPR(31,323,135), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbear",	XSPR(31,323,144), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbesr",	XSPR(31,323,145), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfiocr",	XSPR(31,323,160), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmacr0",	XSPR(31,323,192), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmact0",	XSPR(31,323,193), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmada0",	XSPR(31,323,194), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmasa0",	XSPR(31,323,195), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmacc0",	XSPR(31,323,196), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmacr1",	XSPR(31,323,200), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmact1",	XSPR(31,323,201), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmada1",	XSPR(31,323,202), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmasa1",	XSPR(31,323,203), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmacc1",	XSPR(31,323,204), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmacr2",	XSPR(31,323,208), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmact2",	XSPR(31,323,209), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmada2",	XSPR(31,323,210), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmasa2",	XSPR(31,323,211), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmacc2",	XSPR(31,323,212), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmacr3",	XSPR(31,323,216), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmact3",	XSPR(31,323,217), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmada3",	XSPR(31,323,218), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmasa3",	XSPR(31,323,219), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmacc3",	XSPR(31,323,220), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdmasr",	XSPR(31,323,224), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdcr",	X(31,323), X_MASK, PPC403|BOOKE|PPCA2|PPC476, E500|TITAN, अणुRT, SPRपूर्णपूर्ण,
अणु"mfdcr.",	XRC(31,323,1),	X_MASK,	     PPCA2,	0,		अणुRT, SPRपूर्णपूर्ण,

अणु"lvexwx",	X(31,325),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"dcread",	X(31,326),	X_MASK,	  PPC476|TITAN,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"div",		XO(31,331,0,0),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"div.",	XO(31,331,0,1),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxvdsx",	X(31,332),	XX1_MASK,    PPCVSX,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"mfpmr",	X(31,334),	X_MASK, PPCPMR|PPCE300, 0,		अणुRT, PMRपूर्णपूर्ण,
अणु"mftmr",	X(31,366),	X_MASK,	PPCTMR|E6500,	0,		अणुRT, TMRपूर्णपूर्ण,

अणु"slbsync",	X(31,338),	0xffffffff,  POWER9,	0,		अणु0पूर्णपूर्ण,

अणु"mfmq",	XSPR(31,339,  0), XSPR_MASK, M601,	0,		अणुRTपूर्णपूर्ण,
अणु"mfxer",	XSPR(31,339,  1), XSPR_MASK, COM,	0,		अणुRTपूर्णपूर्ण,
अणु"mfrtcu",	XSPR(31,339,  4), XSPR_MASK, COM,	TITAN,		अणुRTपूर्णपूर्ण,
अणु"mfrtcl",	XSPR(31,339,  5), XSPR_MASK, COM,	TITAN,		अणुRTपूर्णपूर्ण,
अणु"mfdec",	XSPR(31,339,  6), XSPR_MASK, MFDEC1,	0,		अणुRTपूर्णपूर्ण,
अणु"mflr",	XSPR(31,339,  8), XSPR_MASK, COM,	0,		अणुRTपूर्णपूर्ण,
अणु"mfctr",	XSPR(31,339,  9), XSPR_MASK, COM,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdscr",	XSPR(31,339, 17), XSPR_MASK, POWER6,	0,		अणुRTपूर्णपूर्ण,
अणु"mftid",	XSPR(31,339, 17), XSPR_MASK, POWER,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdsisr",	XSPR(31,339, 18), XSPR_MASK, COM,	TITAN,		अणुRTपूर्णपूर्ण,
अणु"mfdar",	XSPR(31,339, 19), XSPR_MASK, COM,	TITAN,		अणुRTपूर्णपूर्ण,
अणु"mfdec",	XSPR(31,339, 22), XSPR_MASK, MFDEC2,	MFDEC1,		अणुRTपूर्णपूर्ण,
अणु"mfsdr0",	XSPR(31,339, 24), XSPR_MASK, POWER,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsdr1",	XSPR(31,339, 25), XSPR_MASK, COM,	TITAN,		अणुRTपूर्णपूर्ण,
अणु"mfsrr0",	XSPR(31,339, 26), XSPR_MASK, COM,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsrr1",	XSPR(31,339, 27), XSPR_MASK, COM,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcfar",	XSPR(31,339, 28), XSPR_MASK, POWER6,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpid",	XSPR(31,339, 48), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcsrr0",	XSPR(31,339, 58), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcsrr1",	XSPR(31,339, 59), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdear",	XSPR(31,339, 61), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfesr",	XSPR(31,339, 62), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivpr",	XSPR(31,339, 63), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfctrl",	XSPR(31,339,136), XSPR_MASK, POWER4,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcmpa",	XSPR(31,339,144), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcmpb",	XSPR(31,339,145), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcmpc",	XSPR(31,339,146), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcmpd",	XSPR(31,339,147), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mficr",	XSPR(31,339,148), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfder",	XSPR(31,339,149), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcounta",	XSPR(31,339,150), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcountb",	XSPR(31,339,151), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcmpe",	XSPR(31,339,152), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcmpf",	XSPR(31,339,153), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcmpg",	XSPR(31,339,154), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcmph",	XSPR(31,339,155), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mflctrl1",	XSPR(31,339,156), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mflctrl2",	XSPR(31,339,157), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfictrl",	XSPR(31,339,158), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbar",	XSPR(31,339,159), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfvrsave",	XSPR(31,339,256), XSPR_MASK, PPCVEC,	0,		अणुRTपूर्णपूर्ण,
अणु"mfusprg0",	XSPR(31,339,256), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsprg",	XSPR(31,339,256), XSPRG_MASK, PPC,	0,		अणुRT, SPRGपूर्णपूर्ण,
अणु"mfsprg4",	XSPR(31,339,260), XSPR_MASK, PPC405|BOOKE, 0,		अणुRTपूर्णपूर्ण,
अणु"mfsprg5",	XSPR(31,339,261), XSPR_MASK, PPC405|BOOKE, 0,		अणुRTपूर्णपूर्ण,
अणु"mfsprg6",	XSPR(31,339,262), XSPR_MASK, PPC405|BOOKE, 0,		अणुRTपूर्णपूर्ण,
अणु"mfsprg7",	XSPR(31,339,263), XSPR_MASK, PPC405|BOOKE, 0,		अणुRTपूर्णपूर्ण,
अणु"mftbu",	XSPR(31,339,269), XSPR_MASK, POWER4|BOOKE, 0,		अणुRTपूर्णपूर्ण,
अणु"mftb",	X(31,339),	  X_MASK,    POWER4|BOOKE, 0,		अणुRT, TBRपूर्णपूर्ण,
अणु"mftbl",	XSPR(31,339,268), XSPR_MASK, POWER4|BOOKE, 0,		अणुRTपूर्णपूर्ण,
अणु"mfsprg0",	XSPR(31,339,272), XSPR_MASK, PPC,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsprg1",	XSPR(31,339,273), XSPR_MASK, PPC,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsprg2",	XSPR(31,339,274), XSPR_MASK, PPC,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsprg3",	XSPR(31,339,275), XSPR_MASK, PPC,	0,		अणुRTपूर्णपूर्ण,
अणु"mfasr",	XSPR(31,339,280), XSPR_MASK, PPC64,	0,		अणुRTपूर्णपूर्ण,
अणु"mfear",	XSPR(31,339,282), XSPR_MASK, PPC,	TITAN,		अणुRTपूर्णपूर्ण,
अणु"mfpir",	XSPR(31,339,286), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpvr",	XSPR(31,339,287), XSPR_MASK, PPC,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbsr",	XSPR(31,339,304), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbcr0",	XSPR(31,339,308), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbcr1",	XSPR(31,339,309), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbcr2",	XSPR(31,339,310), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfiac1",	XSPR(31,339,312), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfiac2",	XSPR(31,339,313), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfiac3",	XSPR(31,339,314), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfiac4",	XSPR(31,339,315), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdac1",	XSPR(31,339,316), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdac2",	XSPR(31,339,317), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdvc1",	XSPR(31,339,318), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdvc2",	XSPR(31,339,319), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mftsr",	XSPR(31,339,336), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mftcr",	XSPR(31,339,340), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor0",	XSPR(31,339,400), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor1",	XSPR(31,339,401), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor2",	XSPR(31,339,402), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor3",	XSPR(31,339,403), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor4",	XSPR(31,339,404), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor5",	XSPR(31,339,405), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor6",	XSPR(31,339,406), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor7",	XSPR(31,339,407), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor8",	XSPR(31,339,408), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor9",	XSPR(31,339,409), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor10",	XSPR(31,339,410), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor11",	XSPR(31,339,411), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor12",	XSPR(31,339,412), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor13",	XSPR(31,339,413), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor14",	XSPR(31,339,414), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor15",	XSPR(31,339,415), XSPR_MASK, BOOKE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfspefscr",	XSPR(31,339,512), XSPR_MASK, PPCSPE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbbear",	XSPR(31,339,513), XSPR_MASK, PPCBRLK,	0,		अणुRTपूर्णपूर्ण,
अणु"mfbbtar",	XSPR(31,339,514), XSPR_MASK, PPCBRLK,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor32",	XSPR(31,339,528), XSPR_MASK, PPCSPE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfibatu",	XSPR(31,339,528), XSPRBAT_MASK, PPC,	TITAN,		अणुRT, SPRBATपूर्णपूर्ण,
अणु"mfivor33",	XSPR(31,339,529), XSPR_MASK, PPCSPE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfibatl",	XSPR(31,339,529), XSPRBAT_MASK, PPC,	TITAN,		अणुRT, SPRBATपूर्णपूर्ण,
अणु"mfivor34",	XSPR(31,339,530), XSPR_MASK, PPCSPE,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivor35",	XSPR(31,339,531), XSPR_MASK, PPCPMR,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbatu",	XSPR(31,339,536), XSPRBAT_MASK, PPC,	TITAN,		अणुRT, SPRBATपूर्णपूर्ण,
अणु"mfdbatl",	XSPR(31,339,537), XSPRBAT_MASK, PPC,	TITAN,		अणुRT, SPRBATपूर्णपूर्ण,
अणु"mfic_cst",	XSPR(31,339,560), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfic_adr",	XSPR(31,339,561), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfic_dat",	XSPR(31,339,562), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdc_cst",	XSPR(31,339,568), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdc_adr",	XSPR(31,339,569), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdc_dat",	XSPR(31,339,570), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmcsrr0",	XSPR(31,339,570), XSPR_MASK, PPCRFMCI,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmcsrr1",	XSPR(31,339,571), XSPR_MASK, PPCRFMCI,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmcsr",	XSPR(31,339,572), XSPR_MASK, PPCRFMCI,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmcar",	XSPR(31,339,573), XSPR_MASK, PPCRFMCI,	TITAN,		अणुRTपूर्णपूर्ण,
अणु"mfdpdr",	XSPR(31,339,630), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdpir",	XSPR(31,339,631), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfimmr",	XSPR(31,339,638), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmi_ctr",	XSPR(31,339,784), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmi_ap",	XSPR(31,339,786), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmi_epn",	XSPR(31,339,787), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmi_twc",	XSPR(31,339,789), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmi_rpn",	XSPR(31,339,790), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_ctr",	XSPR(31,339,792), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfm_casid",	XSPR(31,339,793), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_ap",	XSPR(31,339,794), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_epn",	XSPR(31,339,795), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_twb",	XSPR(31,339,796), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_twc",	XSPR(31,339,797), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_rpn",	XSPR(31,339,798), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfm_tw",	XSPR(31,339,799), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmi_dbcam",	XSPR(31,339,816), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmi_dbram0",	XSPR(31,339,817), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmi_dbram1",	XSPR(31,339,818), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_dbcam",	XSPR(31,339,824), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_dbram0",	XSPR(31,339,825), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmd_dbram1",	XSPR(31,339,826), XSPR_MASK, PPC860,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivndx",	XSPR(31,339,880), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdvndx",	XSPR(31,339,881), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfivlim",	XSPR(31,339,882), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdvlim",	XSPR(31,339,883), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfclcsr",	XSPR(31,339,884), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfccr1",	XSPR(31,339,888), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfppr",	XSPR(31,339,896), XSPR_MASK, POWER7,	0,		अणुRTपूर्णपूर्ण,
अणु"mfppr32",	XSPR(31,339,898), XSPR_MASK, POWER7,	0,		अणुRTपूर्णपूर्ण,
अणु"mfrstcfg",	XSPR(31,339,923), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdcdbtrl",	XSPR(31,339,924), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdcdbtrh",	XSPR(31,339,925), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mficdbtr",	XSPR(31,339,927), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfummcr0",	XSPR(31,339,936), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfupmc1",	XSPR(31,339,937), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfupmc2",	XSPR(31,339,938), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfusia",	XSPR(31,339,939), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfummcr1",	XSPR(31,339,940), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfupmc3",	XSPR(31,339,941), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfupmc4",	XSPR(31,339,942), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfzpr",	XSPR(31,339,944), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpid",	XSPR(31,339,945), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmmucr",	XSPR(31,339,946), XSPR_MASK, TITAN,	0,		अणुRTपूर्णपूर्ण,
अणु"mfccr0",	XSPR(31,339,947), XSPR_MASK, PPC405|TITAN, 0,		अणुRTपूर्णपूर्ण,
अणु"mfiac3",	XSPR(31,339,948), XSPR_MASK, PPC405,	0,		अणुRTपूर्णपूर्ण,
अणु"mfiac4",	XSPR(31,339,949), XSPR_MASK, PPC405,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdvc1",	XSPR(31,339,950), XSPR_MASK, PPC405,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdvc2",	XSPR(31,339,951), XSPR_MASK, PPC405,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmmcr0",	XSPR(31,339,952), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpmc1",	XSPR(31,339,953), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsgr",	XSPR(31,339,953), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdcwr",	XSPR(31,339,954), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpmc2",	XSPR(31,339,954), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsia",	XSPR(31,339,955), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsler",	XSPR(31,339,955), XSPR_MASK, PPC405,	0,		अणुRTपूर्णपूर्ण,
अणु"mfmmcr1",	XSPR(31,339,956), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsu0r",	XSPR(31,339,956), XSPR_MASK, PPC405,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbcr1",	XSPR(31,339,957), XSPR_MASK, PPC405,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpmc3",	XSPR(31,339,957), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpmc4",	XSPR(31,339,958), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mficdbdr",	XSPR(31,339,979), XSPR_MASK, PPC403|TITAN, 0,		अणुRTपूर्णपूर्ण,
अणु"mfesr",	XSPR(31,339,980), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdear",	XSPR(31,339,981), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfevpr",	XSPR(31,339,982), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfcdbcr",	XSPR(31,339,983), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mftsr",	XSPR(31,339,984), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mftcr",	XSPR(31,339,986), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpit",	XSPR(31,339,987), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mftbhi",	XSPR(31,339,988), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mftblo",	XSPR(31,339,989), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsrr2",	XSPR(31,339,990), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfsrr3",	XSPR(31,339,991), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbsr",	XSPR(31,339,1008), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbcr0",	XSPR(31,339,1010), XSPR_MASK, PPC405,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdbdr",	XSPR(31,339,1011), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mfiac1",	XSPR(31,339,1012), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfiac2",	XSPR(31,339,1013), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdac1",	XSPR(31,339,1014), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdac2",	XSPR(31,339,1015), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfl2cr",	XSPR(31,339,1017), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfdccr",	XSPR(31,339,1018), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mficcr",	XSPR(31,339,1019), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfictc",	XSPR(31,339,1019), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpbl1",	XSPR(31,339,1020), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfthrm1",	XSPR(31,339,1020), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpbu1",	XSPR(31,339,1021), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfthrm2",	XSPR(31,339,1021), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpbl2",	XSPR(31,339,1022), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfthrm3",	XSPR(31,339,1022), XSPR_MASK, PPC750,	0,		अणुRTपूर्णपूर्ण,
अणु"mfpbu2",	XSPR(31,339,1023), XSPR_MASK, PPC403,	0,		अणुRTपूर्णपूर्ण,
अणु"mfspr",	X(31,339),	X_MASK,	     COM,	0,		अणुRT, SPRपूर्णपूर्ण,

अणु"lwax",	X(31,341),	X_MASK,	     PPC64,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"dst",		XDSS(31,342,0),	XDSS_MASK,   PPCVEC,	0,		अणुRA, RB, STRMपूर्णपूर्ण,

अणु"lhax",	X(31,343),	X_MASK,	     COM,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"lvxl",	X(31,359),	X_MASK,	     PPCVEC,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"abs",		XO(31,360,0,0),	XORB_MASK,   M601,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"abs.",	XO(31,360,0,1),	XORB_MASK,   M601,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"divs",	XO(31,363,0,0),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divs.",	XO(31,363,0,1),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxvwsx",	X(31,364),	XX1_MASK,    PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"tlbia",	X(31,370),	0xffffffff,  PPC,	E500|TITAN,	अणु0पूर्णपूर्ण,

अणु"mftbu",	XSPR(31,371,269), XSPR_MASK, PPC,	NO371|POWER4,	अणुRTपूर्णपूर्ण,
अणु"mftb",	X(31,371),	X_MASK,	     PPC,	NO371|POWER4,	अणुRT, TBRपूर्णपूर्ण,
अणु"mftbl",	XSPR(31,371,268), XSPR_MASK, PPC,	NO371|POWER4,	अणुRTपूर्णपूर्ण,

अणु"lwaux",	X(31,373),	X_MASK,	     PPC64,	0,		अणुRT, RAL, RBपूर्णपूर्ण,

अणु"dstst",	XDSS(31,374,0),	XDSS_MASK,   PPCVEC,	0,		अणुRA, RB, STRMपूर्णपूर्ण,

अणु"lhaux",	X(31,375),	X_MASK,	     COM,	0,		अणुRT, RAL, RBपूर्णपूर्ण,

अणु"popcntw",	X(31,378),	XRB_MASK,    POWER7|PPCA2, 0,		अणुRA, RSपूर्णपूर्ण,

अणु"mtdcrx",	X(31,387),	X_MASK,	     BOOKE|PPCA2|PPC476, TITAN,	अणुRA, RSपूर्णपूर्ण,
अणु"mtdcrx.",	XRC(31,387,1),	X_MASK,	     PPCA2,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"stvexbx",	X(31,389),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"dcblc",	X(31,390),	X_MASK,	 PPCCHLK|PPC476|TITAN, 0,	अणुCT, RA0, RBपूर्णपूर्ण,
अणु"stdfcmx",	APU(31,391,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"divdeu",	XO(31,393,0,0),	XO_MASK,     POWER7|PPCA2, 0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divdeu.",	XO(31,393,0,1),	XO_MASK,     POWER7|PPCA2, 0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divweu",	XO(31,395,0,0),	XO_MASK,     POWER7|PPCA2, 0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divweu.",	XO(31,395,0,1),	XO_MASK,     POWER7|PPCA2, 0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"stxvx",	X(31,396),	XX1_MASK,    PPCVSX3,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,
अणु"stxvl",	X(31,397),	XX1_MASK,    PPCVSX3,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"dcblce",	X(31,398),	X_MASK,	     PPCCHLK,	E500MC,		अणुCT, RA, RBपूर्णपूर्ण,

अणु"slbmte",	X(31,402),	XRA_MASK,    PPC64,	0,		अणुRS, RBपूर्णपूर्ण,

अणु"mtvsrws",	X(31,403),	XX1RB_MASK,  PPCVSX3,	0,		अणुXT6, RAपूर्णपूर्ण,

अणु"pbt.",	XRC(31,404,1),	X_MASK,	     POWER8,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"icswx",	XRC(31,406,0),	X_MASK,	  POWER7|PPCA2,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"icswx.",	XRC(31,406,1),	X_MASK,	  POWER7|PPCA2,	0,		अणुRS, RA, RBपूर्णपूर्ण,

अणु"sthx",	X(31,407),	X_MASK,	     COM,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"orc",		XRC(31,412,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"orc.",	XRC(31,412,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"sthepx",	X(31,415),	X_MASK,	  E500MC|PPCA2, 0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"mtdcrux",	X(31,419),	X_MASK,	     PPC464,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"stvexhx",	X(31,421),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"dcblq.",	XRC(31,422,1),	X_MASK,	     E6500,	0,		अणुCT, RA0, RBपूर्णपूर्ण,

अणु"divde",	XO(31,425,0,0),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divde.",	XO(31,425,0,1),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divwe",	XO(31,427,0,0),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divwe.",	XO(31,427,0,1),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"stxvll",	X(31,429),	XX1_MASK,    PPCVSX3,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"clrbhrb",	X(31,430),	0xffffffff,  POWER8,	0,		अणु0पूर्णपूर्ण,

अणु"slbie",	X(31,434),	XRTRA_MASK,  PPC64,	0,		अणुRBपूर्णपूर्ण,

अणु"mtvsrdd",	X(31,435),	XX1_MASK,    PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"ecowx",	X(31,438),	X_MASK,	     PPC,	E500|TITAN,	अणुRT, RA0, RBपूर्णपूर्ण,

अणु"sthux",	X(31,439),	X_MASK,	     COM,	0,		अणुRS, RAS, RBपूर्णपूर्ण,

अणु"mdors",	0x7f9ce378,	0xffffffff,  E500MC,	0,		अणु0पूर्णपूर्ण,

अणु"miso",	0x7f5ad378,	0xffffffff,  E6500,	0,		अणु0पूर्णपूर्ण,

/* The "yield", "mdoio" and "mdoom" inकाष्ठाions are extended mnemonics क्रम
   "or rX,rX,rX", with rX being r27, r29 and r30 respectively.	*/
अणु"yield",	0x7f7bdb78,	0xffffffff,  POWER7,	0,		अणु0पूर्णपूर्ण,
अणु"mdoio",	0x7fbdeb78,	0xffffffff,  POWER7,	0,		अणु0पूर्णपूर्ण,
अणु"mdoom",	0x7fdef378,	0xffffffff,  POWER7,	0,		अणु0पूर्णपूर्ण,
अणु"mr",		XRC(31,444,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBSपूर्णपूर्ण,
अणु"or",		XRC(31,444,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"mr.",		XRC(31,444,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBSपूर्णपूर्ण,
अणु"or.",		XRC(31,444,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"mtexisr",	XSPR(31,451, 64), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtexier",	XSPR(31,451, 66), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbr0",	XSPR(31,451,128), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbr1",	XSPR(31,451,129), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbr2",	XSPR(31,451,130), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbr3",	XSPR(31,451,131), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbr4",	XSPR(31,451,132), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbr5",	XSPR(31,451,133), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbr6",	XSPR(31,451,134), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbr7",	XSPR(31,451,135), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbear",	XSPR(31,451,144), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbesr",	XSPR(31,451,145), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtiocr",	XSPR(31,451,160), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmacr0",	XSPR(31,451,192), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmact0",	XSPR(31,451,193), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmada0",	XSPR(31,451,194), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmasa0",	XSPR(31,451,195), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmacc0",	XSPR(31,451,196), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmacr1",	XSPR(31,451,200), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmact1",	XSPR(31,451,201), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmada1",	XSPR(31,451,202), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmasa1",	XSPR(31,451,203), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmacc1",	XSPR(31,451,204), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmacr2",	XSPR(31,451,208), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmact2",	XSPR(31,451,209), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmada2",	XSPR(31,451,210), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmasa2",	XSPR(31,451,211), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmacc2",	XSPR(31,451,212), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmacr3",	XSPR(31,451,216), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmact3",	XSPR(31,451,217), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmada3",	XSPR(31,451,218), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmasa3",	XSPR(31,451,219), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmacc3",	XSPR(31,451,220), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdmasr",	XSPR(31,451,224), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdcr",	X(31,451), X_MASK, PPC403|BOOKE|PPCA2|PPC476, E500|TITAN, अणुSPR, RSपूर्णपूर्ण,
अणु"mtdcr.",	XRC(31,451,1), X_MASK,	     PPCA2,	0,		अणुSPR, RSपूर्णपूर्ण,

अणु"stvexwx",	X(31,453),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"dccci",	X(31,454), XRT_MASK, PPC403|PPC440|TITAN|PPCA2, 0,	अणुRAOPT, RBOPTपूर्णपूर्ण,
अणु"dci",		X(31,454),	XRARB_MASK, PPCA2|PPC476, 0,		अणुCTपूर्णपूर्ण,

अणु"divdu",	XO(31,457,0,0),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divdu.",	XO(31,457,0,1),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"divwu",	XO(31,459,0,0),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divwu.",	XO(31,459,0,1),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"mtpmr",	X(31,462),	X_MASK, PPCPMR|PPCE300, 0,		अणुPMR, RSपूर्णपूर्ण,
अणु"mttmr",	X(31,494),	X_MASK,	PPCTMR|E6500,	0,		अणुTMR, RSपूर्णपूर्ण,

अणु"slbieg",	X(31,466),	XRA_MASK,    POWER9,	0,		अणुRS, RBपूर्णपूर्ण,

अणु"mtmq",	XSPR(31,467,  0), XSPR_MASK, M601,	0,		अणुRSपूर्णपूर्ण,
अणु"mtxer",	XSPR(31,467,  1), XSPR_MASK, COM,	0,		अणुRSपूर्णपूर्ण,
अणु"mtlr",	XSPR(31,467,  8), XSPR_MASK, COM,	0,		अणुRSपूर्णपूर्ण,
अणु"mtctr",	XSPR(31,467,  9), XSPR_MASK, COM,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdscr",	XSPR(31,467, 17), XSPR_MASK, POWER6,	0,		अणुRSपूर्णपूर्ण,
अणु"mttid",	XSPR(31,467, 17), XSPR_MASK, POWER,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdsisr",	XSPR(31,467, 18), XSPR_MASK, COM,	TITAN,		अणुRSपूर्णपूर्ण,
अणु"mtdar",	XSPR(31,467, 19), XSPR_MASK, COM,	TITAN,		अणुRSपूर्णपूर्ण,
अणु"mtrtcu",	XSPR(31,467, 20), XSPR_MASK, COM,	TITAN,		अणुRSपूर्णपूर्ण,
अणु"mtrtcl",	XSPR(31,467, 21), XSPR_MASK, COM,	TITAN,		अणुRSपूर्णपूर्ण,
अणु"mtdec",	XSPR(31,467, 22), XSPR_MASK, COM,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsdr0",	XSPR(31,467, 24), XSPR_MASK, POWER,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsdr1",	XSPR(31,467, 25), XSPR_MASK, COM,	TITAN,		अणुRSपूर्णपूर्ण,
अणु"mtsrr0",	XSPR(31,467, 26), XSPR_MASK, COM,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsrr1",	XSPR(31,467, 27), XSPR_MASK, COM,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcfar",	XSPR(31,467, 28), XSPR_MASK, POWER6,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpid",	XSPR(31,467, 48), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdecar",	XSPR(31,467, 54), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcsrr0",	XSPR(31,467, 58), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcsrr1",	XSPR(31,467, 59), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdear",	XSPR(31,467, 61), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtesr",	XSPR(31,467, 62), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivpr",	XSPR(31,467, 63), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcmpa",	XSPR(31,467,144), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcmpb",	XSPR(31,467,145), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcmpc",	XSPR(31,467,146), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcmpd",	XSPR(31,467,147), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mticr",	XSPR(31,467,148), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtder",	XSPR(31,467,149), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcounta",	XSPR(31,467,150), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcountb",	XSPR(31,467,151), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtctrl",	XSPR(31,467,152), XSPR_MASK, POWER4,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcmpe",	XSPR(31,467,152), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcmpf",	XSPR(31,467,153), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcmpg",	XSPR(31,467,154), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcmph",	XSPR(31,467,155), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtlctrl1",	XSPR(31,467,156), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtlctrl2",	XSPR(31,467,157), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtictrl",	XSPR(31,467,158), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbar",	XSPR(31,467,159), XSPR_MASK, PPC860,	0,		अणुRSपूर्णपूर्ण,
अणु"mtvrsave",	XSPR(31,467,256), XSPR_MASK, PPCVEC,	0,		अणुRSपूर्णपूर्ण,
अणु"mtusprg0",	XSPR(31,467,256), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsprg",	XSPR(31,467,256), XSPRG_MASK, PPC,	0,		अणुSPRG, RSपूर्णपूर्ण,
अणु"mtsprg0",	XSPR(31,467,272), XSPR_MASK, PPC,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsprg1",	XSPR(31,467,273), XSPR_MASK, PPC,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsprg2",	XSPR(31,467,274), XSPR_MASK, PPC,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsprg3",	XSPR(31,467,275), XSPR_MASK, PPC,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsprg4",	XSPR(31,467,276), XSPR_MASK, PPC405|BOOKE, 0,		अणुRSपूर्णपूर्ण,
अणु"mtsprg5",	XSPR(31,467,277), XSPR_MASK, PPC405|BOOKE, 0,		अणुRSपूर्णपूर्ण,
अणु"mtsprg6",	XSPR(31,467,278), XSPR_MASK, PPC405|BOOKE, 0,		अणुRSपूर्णपूर्ण,
अणु"mtsprg7",	XSPR(31,467,279), XSPR_MASK, PPC405|BOOKE, 0,		अणुRSपूर्णपूर्ण,
अणु"mtasr",	XSPR(31,467,280), XSPR_MASK, PPC64,	0,		अणुRSपूर्णपूर्ण,
अणु"mtear",	XSPR(31,467,282), XSPR_MASK, PPC,	TITAN,		अणुRSपूर्णपूर्ण,
अणु"mttbl",	XSPR(31,467,284), XSPR_MASK, PPC,	0,		अणुRSपूर्णपूर्ण,
अणु"mttbu",	XSPR(31,467,285), XSPR_MASK, PPC,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbsr",	XSPR(31,467,304), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbcr0",	XSPR(31,467,308), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbcr1",	XSPR(31,467,309), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbcr2",	XSPR(31,467,310), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtiac1",	XSPR(31,467,312), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtiac2",	XSPR(31,467,313), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtiac3",	XSPR(31,467,314), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtiac4",	XSPR(31,467,315), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdac1",	XSPR(31,467,316), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdac2",	XSPR(31,467,317), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdvc1",	XSPR(31,467,318), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdvc2",	XSPR(31,467,319), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mttsr",	XSPR(31,467,336), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mttcr",	XSPR(31,467,340), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor0",	XSPR(31,467,400), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor1",	XSPR(31,467,401), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor2",	XSPR(31,467,402), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor3",	XSPR(31,467,403), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor4",	XSPR(31,467,404), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor5",	XSPR(31,467,405), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor6",	XSPR(31,467,406), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor7",	XSPR(31,467,407), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor8",	XSPR(31,467,408), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor9",	XSPR(31,467,409), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor10",	XSPR(31,467,410), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor11",	XSPR(31,467,411), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor12",	XSPR(31,467,412), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor13",	XSPR(31,467,413), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor14",	XSPR(31,467,414), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor15",	XSPR(31,467,415), XSPR_MASK, BOOKE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtspefscr",	XSPR(31,467,512), XSPR_MASK, PPCSPE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbbear",	XSPR(31,467,513), XSPR_MASK, PPCBRLK,	0,		अणुRSपूर्णपूर्ण,
अणु"mtbbtar",	XSPR(31,467,514), XSPR_MASK, PPCBRLK,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor32",	XSPR(31,467,528), XSPR_MASK, PPCSPE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtibatu",	XSPR(31,467,528), XSPRBAT_MASK, PPC,	TITAN,		अणुSPRBAT, RSपूर्णपूर्ण,
अणु"mtivor33",	XSPR(31,467,529), XSPR_MASK, PPCSPE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtibatl",	XSPR(31,467,529), XSPRBAT_MASK, PPC,	TITAN,		अणुSPRBAT, RSपूर्णपूर्ण,
अणु"mtivor34",	XSPR(31,467,530), XSPR_MASK, PPCSPE,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivor35",	XSPR(31,467,531), XSPR_MASK, PPCPMR,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbatu",	XSPR(31,467,536), XSPRBAT_MASK, PPC,	TITAN,		अणुSPRBAT, RSपूर्णपूर्ण,
अणु"mtdbatl",	XSPR(31,467,537), XSPRBAT_MASK, PPC,	TITAN,		अणुSPRBAT, RSपूर्णपूर्ण,
अणु"mtmcsrr0",	XSPR(31,467,570), XSPR_MASK, PPCRFMCI,	0,		अणुRSपूर्णपूर्ण,
अणु"mtmcsrr1",	XSPR(31,467,571), XSPR_MASK, PPCRFMCI,	0,		अणुRSपूर्णपूर्ण,
अणु"mtmcsr",	XSPR(31,467,572), XSPR_MASK, PPCRFMCI,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivndx",	XSPR(31,467,880), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdvndx",	XSPR(31,467,881), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mtivlim",	XSPR(31,467,882), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdvlim",	XSPR(31,467,883), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mtclcsr",	XSPR(31,467,884), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mtccr1",	XSPR(31,467,888), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mtppr",	XSPR(31,467,896), XSPR_MASK, POWER7,	0,		अणुRSपूर्णपूर्ण,
अणु"mtppr32",	XSPR(31,467,898), XSPR_MASK, POWER7,	0,		अणुRSपूर्णपूर्ण,
अणु"mtummcr0",	XSPR(31,467,936), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtupmc1",	XSPR(31,467,937), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtupmc2",	XSPR(31,467,938), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtusia",	XSPR(31,467,939), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtummcr1",	XSPR(31,467,940), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtupmc3",	XSPR(31,467,941), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtupmc4",	XSPR(31,467,942), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtzpr",	XSPR(31,467,944), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpid",	XSPR(31,467,945), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtrmmucr",	XSPR(31,467,946), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mtccr0",	XSPR(31,467,947), XSPR_MASK, PPC405|TITAN, 0,		अणुRSपूर्णपूर्ण,
अणु"mtiac3",	XSPR(31,467,948), XSPR_MASK, PPC405,	0,		अणुRSपूर्णपूर्ण,
अणु"mtiac4",	XSPR(31,467,949), XSPR_MASK, PPC405,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdvc1",	XSPR(31,467,950), XSPR_MASK, PPC405,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdvc2",	XSPR(31,467,951), XSPR_MASK, PPC405,	0,		अणुRSपूर्णपूर्ण,
अणु"mtmmcr0",	XSPR(31,467,952), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpmc1",	XSPR(31,467,953), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsgr",	XSPR(31,467,953), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdcwr",	XSPR(31,467,954), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpmc2",	XSPR(31,467,954), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsia",	XSPR(31,467,955), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsler",	XSPR(31,467,955), XSPR_MASK, PPC405,	0,		अणुRSपूर्णपूर्ण,
अणु"mtmmcr1",	XSPR(31,467,956), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsu0r",	XSPR(31,467,956), XSPR_MASK, PPC405,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbcr1",	XSPR(31,467,957), XSPR_MASK, PPC405,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpmc3",	XSPR(31,467,957), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpmc4",	XSPR(31,467,958), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mticdbdr",	XSPR(31,467,979), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtesr",	XSPR(31,467,980), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdear",	XSPR(31,467,981), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtevpr",	XSPR(31,467,982), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtcdbcr",	XSPR(31,467,983), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mttsr",	XSPR(31,467,984), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mttcr",	XSPR(31,467,986), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpit",	XSPR(31,467,987), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mttbhi",	XSPR(31,467,988), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mttblo",	XSPR(31,467,989), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsrr2",	XSPR(31,467,990), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtsrr3",	XSPR(31,467,991), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbsr",	XSPR(31,467,1008), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbdr",	XSPR(31,467,1011), XSPR_MASK, TITAN,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdbcr0",	XSPR(31,467,1010), XSPR_MASK, PPC405,	0,		अणुRSपूर्णपूर्ण,
अणु"mtiac1",	XSPR(31,467,1012), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtiac2",	XSPR(31,467,1013), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdac1",	XSPR(31,467,1014), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdac2",	XSPR(31,467,1015), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtl2cr",	XSPR(31,467,1017), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtdccr",	XSPR(31,467,1018), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mticcr",	XSPR(31,467,1019), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtictc",	XSPR(31,467,1019), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpbl1",	XSPR(31,467,1020), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtthrm1",	XSPR(31,467,1020), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpbu1",	XSPR(31,467,1021), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtthrm2",	XSPR(31,467,1021), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpbl2",	XSPR(31,467,1022), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtthrm3",	XSPR(31,467,1022), XSPR_MASK, PPC750,	0,		अणुRSपूर्णपूर्ण,
अणु"mtpbu2",	XSPR(31,467,1023), XSPR_MASK, PPC403,	0,		अणुRSपूर्णपूर्ण,
अणु"mtspr",	X(31,467),	X_MASK,	     COM,	0,		अणुSPR, RSपूर्णपूर्ण,

अणु"dcbi",	X(31,470),	XRT_MASK,    PPC,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"nand",	XRC(31,476,0),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"nand.",	XRC(31,476,1),	X_MASK,	     COM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"dsn",		X(31,483),	XRT_MASK,    E500MC,	0,		अणुRA, RBपूर्णपूर्ण,

अणु"dcread",	X(31,486),	X_MASK,	 PPC403|PPC440, PPCA2|PPC476,	अणुRT, RA0, RBपूर्णपूर्ण,

अणु"icbtls",	X(31,486),	X_MASK,	 PPCCHLK|PPC476|TITAN, 0,	अणुCT, RA0, RBपूर्णपूर्ण,

अणु"stvxl",	X(31,487),	X_MASK,	     PPCVEC,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"nabs",	XO(31,488,0,0),	XORB_MASK,   M601,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"nabs.",	XO(31,488,0,1),	XORB_MASK,   M601,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"divd",	XO(31,489,0,0),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divd.",	XO(31,489,0,1),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"divw",	XO(31,491,0,0),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divw.",	XO(31,491,0,1),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"icbtlse",	X(31,494),	X_MASK,	     PPCCHLK,	E500MC,		अणुCT, RA, RBपूर्णपूर्ण,

अणु"slbia",	X(31,498),	0xff1fffff,  POWER6,	0,		अणुIHपूर्णपूर्ण,
अणु"slbia",	X(31,498),	0xffffffff,  PPC64,	POWER6,		अणु0पूर्णपूर्ण,

अणु"cli",		X(31,502),	XRB_MASK,    POWER,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"popcntd",	X(31,506),	XRB_MASK, POWER7|PPCA2,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"cmpb",	X(31,508),	X_MASK, POWER6|PPCA2|PPC476, 0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"mcrxr",	X(31,512),	XBFRARB_MASK, COM,	POWER7,		अणुBFपूर्णपूर्ण,

अणु"lbdcbx",	X(31,514),	X_MASK,      E200Z4,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"lbdx",	X(31,515),	X_MASK,	     E500MC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"bblels",	X(31,518),	X_MASK,	     PPCBRLK,	0,		अणु0पूर्णपूर्ण,

अणु"lvlx",	X(31,519),	X_MASK,	     CELL,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"lbfcmux",	APU(31,519,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"subfco",	XO(31,8,1,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sfo",		XO(31,8,1,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"subco",	XO(31,8,1,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RB, RAपूर्णपूर्ण,
अणु"subfco.",	XO(31,8,1,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sfo.",	XO(31,8,1,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"subco.",	XO(31,8,1,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RB, RAपूर्णपूर्ण,

अणु"addco",	XO(31,10,1,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ao",		XO(31,10,1,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"addco.",	XO(31,10,1,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"ao.",		XO(31,10,1,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxsspx",	X(31,524),	XX1_MASK,    PPCVSX2,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"clcs",	X(31,531),	XRB_MASK,    M601,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"ldbrx",	X(31,532),	X_MASK, CELL|POWER7|PPCA2, 0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"lswx",	X(31,533),	X_MASK,	     PPCCOM,	E500|E500MC,	अणुRT, RAX, RBXपूर्णपूर्ण,
अणु"lsx",		X(31,533),	X_MASK,	     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lwbrx",	X(31,534),	X_MASK,	     PPCCOM,	0,		अणुRT, RA0, RBपूर्णपूर्ण,
अणु"lbrx",	X(31,534),	X_MASK,	     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lfsx",	X(31,535),	X_MASK,	     COM,	PPCEFS,		अणुFRT, RA0, RBपूर्णपूर्ण,

अणु"srw",		XRC(31,536,0),	X_MASK,	     PPCCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sr",		XRC(31,536,0),	X_MASK,	     PWRCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"srw.",	XRC(31,536,1),	X_MASK,	     PPCCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sr.",		XRC(31,536,1),	X_MASK,	     PWRCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"rrib",	XRC(31,537,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"rrib.",	XRC(31,537,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"cnttzw",	XRC(31,538,0),	XRB_MASK,    POWER9,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"cnttzw.",	XRC(31,538,1),	XRB_MASK,    POWER9,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"srd",		XRC(31,539,0),	X_MASK,	     PPC64,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"srd.",	XRC(31,539,1),	X_MASK,	     PPC64,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"maskir",	XRC(31,541,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"maskir.",	XRC(31,541,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"lhdcbx",	X(31,546),	X_MASK,      E200Z4,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"lhdx",	X(31,547),	X_MASK,	     E500MC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lvtrx",	X(31,549),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"bbelr",	X(31,550),	X_MASK,	     PPCBRLK,	0,		अणु0पूर्णपूर्ण,

अणु"lvrx",	X(31,551),	X_MASK,	     CELL,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"lhfcmux",	APU(31,551,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"subfo",	XO(31,40,1,0),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"subo",	XO(31,40,1,0),	XO_MASK,     PPC,	0,		अणुRT, RB, RAपूर्णपूर्ण,
अणु"subfo.",	XO(31,40,1,1),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"subo.",	XO(31,40,1,1),	XO_MASK,     PPC,	0,		अणुRT, RB, RAपूर्णपूर्ण,

अणु"tlbsync",	X(31,566),	0xffffffff,  PPC,	0,		अणु0पूर्णपूर्ण,

अणु"lfsux",	X(31,567),	X_MASK,	     COM,	PPCEFS,		अणुFRT, RAS, RBपूर्णपूर्ण,

अणु"cnttzd",	XRC(31,570,0),	XRB_MASK,    POWER9,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"cnttzd.",	XRC(31,570,1),	XRB_MASK,    POWER9,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"mcrxrx",	X(31,576),     XBFRARB_MASK, POWER9,	0,		अणुBFपूर्णपूर्ण,

अणु"lwdcbx",	X(31,578),	X_MASK,      E200Z4,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"lwdx",	X(31,579),	X_MASK,	     E500MC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lvtlx",	X(31,581),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"lwat",	X(31,582),	X_MASK,	     POWER9,	0,		अणुRT, RA0, FCपूर्णपूर्ण,

अणु"lwfcmux",	APU(31,583,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"lxsdx",	X(31,588),	XX1_MASK,    PPCVSX,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"mfsr",	X(31,595), XRB_MASK|(1<<20), COM,	NON32,		अणुRT, SRपूर्णपूर्ण,

अणु"lswi",	X(31,597),	X_MASK,	     PPCCOM,	E500|E500MC,	अणुRT, RAX, NBIपूर्णपूर्ण,
अणु"lsi",		X(31,597),	X_MASK,	     PWRCOM,	0,		अणुRT, RA0, NBपूर्णपूर्ण,

अणु"hwsync",	XSYNC(31,598,0), 0xffffffff, POWER4,	BOOKE|PPC476,	अणु0पूर्णपूर्ण,
अणु"lwsync",	XSYNC(31,598,1), 0xffffffff, PPC,	E500,		अणु0पूर्णपूर्ण,
अणु"ptesync",	XSYNC(31,598,2), 0xffffffff, PPC64,	0,		अणु0पूर्णपूर्ण,
अणु"sync",	X(31,598),     XSYNCLE_MASK, E6500,	0,		अणुLS, ESYNCपूर्णपूर्ण,
अणु"sync",	X(31,598),     XSYNC_MASK,   PPCCOM,	BOOKE|PPC476,	अणुLSपूर्णपूर्ण,
अणु"msync",	X(31,598),     0xffffffff, BOOKE|PPCA2|PPC476, 0,	अणु0पूर्णपूर्ण,
अणु"sync",	X(31,598),     0xffffffff,   BOOKE|PPC476, E6500,	अणु0पूर्णपूर्ण,
अणु"lwsync",	X(31,598),     0xffffffff,   E500,	0,		अणु0पूर्णपूर्ण,
अणु"dcs",		X(31,598),     0xffffffff,   PWRCOM,	0,		अणु0पूर्णपूर्ण,

अणु"lfdx",	X(31,599),	X_MASK,	     COM,	PPCEFS,		अणुFRT, RA0, RBपूर्णपूर्ण,

अणु"mffgpr",	XRC(31,607,0),	XRA_MASK,    POWER6,	POWER7,		अणुFRT, RBपूर्णपूर्ण,
अणु"lfdepx",	X(31,607),	X_MASK,	  E500MC|PPCA2, 0,		अणुFRT, RA0, RBपूर्णपूर्ण,

अणु"lddx",	X(31,611),	X_MASK,	     E500MC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lvswx",	X(31,613),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"ldat",	X(31,614),	X_MASK,	     POWER9,	0,		अणुRT, RA0, FCपूर्णपूर्ण,

अणु"lqfcmux",	APU(31,615,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"nego",	XO(31,104,1,0),	XORB_MASK,   COM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"nego.",	XO(31,104,1,1),	XORB_MASK,   COM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"mulo",	XO(31,107,1,0),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulo.",	XO(31,107,1,1),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"mfsri",	X(31,627),	X_MASK,	     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"dclst",	X(31,630),	XRB_MASK,    M601,	0,		अणुRS, RAपूर्णपूर्ण,

अणु"lfdux",	X(31,631),	X_MASK,	     COM,	PPCEFS,		अणुFRT, RAS, RBपूर्णपूर्ण,

अणु"stbdcbx",	X(31,642),	X_MASK,      E200Z4,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"stbdx",	X(31,643),	X_MASK,	     E500MC,	0,		अणुRS, RA, RBपूर्णपूर्ण,

अणु"stvlx",	X(31,647),	X_MASK,	     CELL,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"stbfcmux",	APU(31,647,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"stxsspx",	X(31,652),	XX1_MASK,    PPCVSX2,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"tbegin.",	XRC(31,654,1), XRTLRARB_MASK, PPCHTM,	0,		अणुHTM_Rपूर्णपूर्ण,

अणु"subfeo",	XO(31,136,1,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sfeo",	XO(31,136,1,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"subfeo.",	XO(31,136,1,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"sfeo.",	XO(31,136,1,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"addeo",	XO(31,138,1,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"aeo",		XO(31,138,1,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"addeo.",	XO(31,138,1,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"aeo.",	XO(31,138,1,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"mfsrin",	X(31,659),	XRA_MASK,    PPC,	NON32,		अणुRT, RBपूर्णपूर्ण,

अणु"stdbrx",	X(31,660),	X_MASK, CELL|POWER7|PPCA2, 0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stswx",	X(31,661),	X_MASK,	     PPCCOM,	E500|E500MC,	अणुRS, RA0, RBपूर्णपूर्ण,
अणु"stsx",	X(31,661),	X_MASK,	     PWRCOM,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stwbrx",	X(31,662),	X_MASK,	     PPCCOM,	0,		अणुRS, RA0, RBपूर्णपूर्ण,
अणु"stbrx",	X(31,662),	X_MASK,	     PWRCOM,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stfsx",	X(31,663),	X_MASK,	     COM,	PPCEFS,		अणुFRS, RA0, RBपूर्णपूर्ण,

अणु"srq",		XRC(31,664,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"srq.",	XRC(31,664,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"sre",		XRC(31,665,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sre.",	XRC(31,665,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"sthdcbx",	X(31,674),	X_MASK,      E200Z4,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"sthdx",	X(31,675),	X_MASK,	     E500MC,	0,		अणुRS, RA, RBपूर्णपूर्ण,

अणु"stvfrx",	X(31,677),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"stvrx",	X(31,679),	X_MASK,	     CELL,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"sthfcmux",	APU(31,679,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"tendall.",	XRC(31,686,1)|(1<<25), XRTRARB_MASK, PPCHTM, 0,		अणु0पूर्णपूर्ण,
अणु"tend.",	XRC(31,686,1), XRTARARB_MASK, PPCHTM,	0,		अणुHTM_Aपूर्णपूर्ण,

अणु"stbcx.",	XRC(31,694,1),	X_MASK,	  POWER8|E6500, 0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stfsux",	X(31,695),	X_MASK,	     COM,	PPCEFS,		अणुFRS, RAS, RBपूर्णपूर्ण,

अणु"sriq",	XRC(31,696,0),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"sriq.",	XRC(31,696,1),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"stwdcbx",	X(31,706),	X_MASK,	     E200Z4,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"stwdx",	X(31,707),	X_MASK,	     E500MC,	0,		अणुRS, RA, RBपूर्णपूर्ण,

अणु"stvflx",	X(31,709),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"stwat",	X(31,710),	X_MASK,	     POWER9,	0,		अणुRS, RA0, FCपूर्णपूर्ण,

अणु"stwfcmux",	APU(31,711,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"stxsdx",	X(31,716),	XX1_MASK,    PPCVSX,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"tcheck",	X(31,718),   XRTBFRARB_MASK, PPCHTM,	0,		अणुBFपूर्णपूर्ण,

अणु"subfzeo",	XO(31,200,1,0),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"sfzeo",	XO(31,200,1,0),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"subfzeo.",	XO(31,200,1,1),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"sfzeo.",	XO(31,200,1,1),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"addzeo",	XO(31,202,1,0),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"azeo",	XO(31,202,1,0),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"addzeo.",	XO(31,202,1,1),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"azeo.",	XO(31,202,1,1),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"stswi",	X(31,725),	X_MASK,	     PPCCOM,	E500|E500MC,	अणुRS, RA0, NBपूर्णपूर्ण,
अणु"stsi",	X(31,725),	X_MASK,	     PWRCOM,	0,		अणुRS, RA0, NBपूर्णपूर्ण,

अणु"sthcx.",	XRC(31,726,1),	X_MASK,	  POWER8|E6500, 0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stfdx",	X(31,727),	X_MASK,	     COM,	PPCEFS,		अणुFRS, RA0, RBपूर्णपूर्ण,

अणु"srlq",	XRC(31,728,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"srlq.",	XRC(31,728,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"sreq",	XRC(31,729,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sreq.",	XRC(31,729,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"mftgpr",	XRC(31,735,0),	XRA_MASK,    POWER6,	POWER7,		अणुRT, FRBपूर्णपूर्ण,
अणु"stfdepx",	X(31,735),	X_MASK,	  E500MC|PPCA2, 0,		अणुFRS, RA0, RBपूर्णपूर्ण,

अणु"stddx",	X(31,739),	X_MASK,	     E500MC,	0,		अणुRS, RA, RBपूर्णपूर्ण,

अणु"stvswx",	X(31,741),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"stdat",	X(31,742),	X_MASK,	     POWER9,	0,		अणुRS, RA0, FCपूर्णपूर्ण,

अणु"stqfcmux",	APU(31,743,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"subfmeo",	XO(31,232,1,0),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"sfmeo",	XO(31,232,1,0),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"subfmeo.",	XO(31,232,1,1),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"sfmeo.",	XO(31,232,1,1),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"mulldo",	XO(31,233,1,0),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulldo.",	XO(31,233,1,1),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"addmeo",	XO(31,234,1,0),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"ameo",	XO(31,234,1,0),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"addmeo.",	XO(31,234,1,1),	XORB_MASK,   PPCCOM,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"ameo.",	XO(31,234,1,1),	XORB_MASK,   PWRCOM,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"mullwo",	XO(31,235,1,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulso",	XO(31,235,1,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mullwo.",	XO(31,235,1,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"mulso.",	XO(31,235,1,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"tsuspend.",	XRCL(31,750,0,1), XRTRARB_MASK,PPCHTM,	0,		अणु0पूर्णपूर्ण,
अणु"tresume.",	XRCL(31,750,1,1), XRTRARB_MASK,PPCHTM,	0,		अणु0पूर्णपूर्ण,
अणु"tsr.",	XRC(31,750,1),	  XRTLRARB_MASK,PPCHTM,	0,		अणुLपूर्णपूर्ण,

अणु"darn",	X(31,755),	XLRAND_MASK, POWER9,	0,		अणुRT, LRANDपूर्णपूर्ण,

अणु"dcba",	X(31,758), XRT_MASK, PPC405|PPC7450|BOOKE|PPCA2|PPC476, 0, अणुRA0, RBपूर्णपूर्ण,
अणु"dcbal",	XOPL(31,758,1), XRT_MASK,    E500MC,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"stfdux",	X(31,759),	X_MASK,	     COM,	PPCEFS,		अणुFRS, RAS, RBपूर्णपूर्ण,

अणु"srliq",	XRC(31,760,0),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"srliq.",	XRC(31,760,1),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"lvsm",	X(31,773),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"copy",	XOPL(31,774,1),	XRT_MASK,    POWER9,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"stvepxl",	X(31,775),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"lvlxl",	X(31,775),	X_MASK,	     CELL,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"ldfcmux",	APU(31,775,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"dozo",	XO(31,264,1,0),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"dozo.",	XO(31,264,1,1),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"addo",	XO(31,266,1,0),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"caxo",	XO(31,266,1,0),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"addo.",	XO(31,266,1,1),	XO_MASK,     PPCCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"caxo.",	XO(31,266,1,1),	XO_MASK,     PWRCOM,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"modsd",	X(31,777),	X_MASK,	     POWER9,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"modsw",	X(31,779),	X_MASK,	     POWER9,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxvw4x",	X(31,780),	XX1_MASK,    PPCVSX,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,
अणु"lxsibzx",	X(31,781),	XX1_MASK,    PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"tabortwc.",	XRC(31,782,1),	X_MASK,	     PPCHTM,	0,		अणुTO, RA, RBपूर्णपूर्ण,

अणु"tlbivax",	X(31,786),	XRT_MASK, BOOKE|PPCA2|PPC476, 0,	अणुRA0, RBपूर्णपूर्ण,

अणु"lwzcix",	X(31,789),	X_MASK,	     POWER6,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"lhbrx",	X(31,790),	X_MASK,	     COM,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"lfdpx",	X(31,791),	X_MASK,	     POWER6,	POWER7,		अणुFRTp, RA0, RBपूर्णपूर्ण,
अणु"lfqx",	X(31,791),	X_MASK,	     POWER2,	0,		अणुFRT, RA, RBपूर्णपूर्ण,

अणु"sraw",	XRC(31,792,0),	X_MASK,	     PPCCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sra",		XRC(31,792,0),	X_MASK,	     PWRCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sraw.",	XRC(31,792,1),	X_MASK,	     PPCCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sra.",	XRC(31,792,1),	X_MASK,	     PWRCOM,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"srad",	XRC(31,794,0),	X_MASK,	     PPC64,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"srad.",	XRC(31,794,1),	X_MASK,	     PPC64,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"lfddx",	X(31,803),	X_MASK,	     E500MC,	0,		अणुFRT, RA, RBपूर्णपूर्ण,

अणु"lvtrxl",	X(31,805),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,
अणु"stvepx",	X(31,807),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"lvrxl",	X(31,807),	X_MASK,	     CELL,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"lxvh8x",	X(31,812),	XX1_MASK,    PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,
अणु"lxsihzx",	X(31,813),	XX1_MASK,    PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"tabortdc.",	XRC(31,814,1),	X_MASK,	     PPCHTM,	0,		अणुTO, RA, RBपूर्णपूर्ण,

अणु"rac",		X(31,818),	X_MASK,	     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"erativax",	X(31,819),	X_MASK,	     PPCA2,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"lhzcix",	X(31,821),	X_MASK,	     POWER6,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"dss",		XDSS(31,822,0),	XDSS_MASK,   PPCVEC,	0,		अणुSTRMपूर्णपूर्ण,

अणु"lfqux",	X(31,823),	X_MASK,	     POWER2,	0,		अणुFRT, RA, RBपूर्णपूर्ण,

अणु"srawi",	XRC(31,824,0),	X_MASK,	     PPCCOM,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"srai",	XRC(31,824,0),	X_MASK,	     PWRCOM,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"srawi.",	XRC(31,824,1),	X_MASK,	     PPCCOM,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"srai.",	XRC(31,824,1),	X_MASK,	     PWRCOM,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"sradi",	XS(31,413,0),	XS_MASK,     PPC64,	0,		अणुRA, RS, SH6पूर्णपूर्ण,
अणु"sradi.",	XS(31,413,1),	XS_MASK,     PPC64,	0,		अणुRA, RS, SH6पूर्णपूर्ण,

अणु"lvtlxl",	X(31,837),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"cpabort",	X(31,838),	XRTRARB_MASK,POWER9,	0,		अणु0पूर्णपूर्ण,

अणु"divo",	XO(31,331,1,0),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divo.",	XO(31,331,1,1),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxvd2x",	X(31,844),	XX1_MASK,    PPCVSX,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,
अणु"lxvx",	X(31,844),	XX1_MASK,    POWER8,	POWER9|PPCVSX3,	अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"tabortwci.",	XRC(31,846,1),	X_MASK,	     PPCHTM,	0,		अणुTO, RA, HTM_SIपूर्णपूर्ण,

अणु"tlbsrx.",	XRC(31,850,1),	XRT_MASK,    PPCA2,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"slbiag",	X(31,850),	XRARB_MASK,  POWER9,	0,		अणुRSपूर्णपूर्ण,
अणु"slbmfev",	X(31,851),	XRLA_MASK,   POWER9,	0,		अणुRT, RB, A_Lपूर्णपूर्ण,
अणु"slbmfev",	X(31,851),	XRA_MASK,    PPC64,	POWER9,		अणुRT, RBपूर्णपूर्ण,

अणु"lbzcix",	X(31,853),	X_MASK,	     POWER6,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"eieio",	X(31,854),	0xffffffff,  PPC,   BOOKE|PPCA2|PPC476,	अणु0पूर्णपूर्ण,
अणु"mbar",	X(31,854),	X_MASK,	   BOOKE|PPCA2|PPC476, 0,	अणुMOपूर्णपूर्ण,
अणु"eieio",	XMBAR(31,854,1),0xffffffff,  E500,	0,		अणु0पूर्णपूर्ण,
अणु"eieio",	X(31,854),	0xffffffff, PPCA2|PPC476, 0,		अणु0पूर्णपूर्ण,

अणु"lfiwax",	X(31,855),	X_MASK, POWER6|PPCA2|PPC476, 0,		अणुFRT, RA0, RBपूर्णपूर्ण,

अणु"lvswxl",	X(31,869),	X_MASK,	     PPCVEC2,	0,		अणुVD, RA0, RBपूर्णपूर्ण,

अणु"abso",	XO(31,360,1,0),	XORB_MASK,   M601,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"abso.",	XO(31,360,1,1),	XORB_MASK,   M601,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"divso",	XO(31,363,1,0),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divso.",	XO(31,363,1,1),	XO_MASK,     M601,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"lxvb16x",	X(31,876),	XX1_MASK,    PPCVSX3,	0,		अणुXT6, RA0, RBपूर्णपूर्ण,

अणु"tabortdci.",	XRC(31,878,1),	X_MASK,	     PPCHTM,	0,		अणुTO, RA, HTM_SIपूर्णपूर्ण,

अणु"rmieg",	X(31,882),	XRTRA_MASK,  POWER9,	0,		अणुRBपूर्णपूर्ण,

अणु"ldcix",	X(31,885),	X_MASK,	     POWER6,	0,		अणुRT, RA0, RBपूर्णपूर्ण,

अणु"msgsync",	X(31,886),	0xffffffff,  POWER9,	0,		अणु0पूर्णपूर्ण,

अणु"lfiwzx",	X(31,887),	X_MASK,	  POWER7|PPCA2,	0,		अणुFRT, RA0, RBपूर्णपूर्ण,

अणु"extswsli",	XS(31,445,0),	XS_MASK,     POWER9,	0,		अणुRA, RS, SH6पूर्णपूर्ण,
अणु"extswsli.",	XS(31,445,1),	XS_MASK,     POWER9,	0,		अणुRA, RS, SH6पूर्णपूर्ण,

अणु"paste.",	XRCL(31,902,1,1),XRT_MASK,   POWER9,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"stvlxl",	X(31,903),	X_MASK,	     CELL,	0,		अणुVS, RA0, RBपूर्णपूर्ण,
अणु"stdfcmux",	APU(31,903,0),	APU_MASK,    PPC405,	0,		अणुFCRT, RA, RBपूर्णपूर्ण,

अणु"divdeuo",	XO(31,393,1,0),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divdeuo.",	XO(31,393,1,1),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divweuo",	XO(31,395,1,0),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divweuo.",	XO(31,395,1,1),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"stxvw4x",	X(31,908),	XX1_MASK,    PPCVSX,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,
अणु"stxsibx",	X(31,909),	XX1_MASK,    PPCVSX3,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"tabort.",	XRC(31,910,1),	XRTRB_MASK,  PPCHTM,	0,		अणुRAपूर्णपूर्ण,

अणु"tlbsx",	XRC(31,914,0),	X_MASK, PPC403|BOOKE|PPCA2|PPC476, 0,	अणुRTO, RA0, RBपूर्णपूर्ण,
अणु"tlbsx.",	XRC(31,914,1),	X_MASK, PPC403|BOOKE|PPCA2|PPC476, 0,	अणुRTO, RA0, RBपूर्णपूर्ण,

अणु"slbmfee",	X(31,915),	XRLA_MASK,   POWER9,	0,		अणुRT, RB, A_Lपूर्णपूर्ण,
अणु"slbmfee",	X(31,915),	XRA_MASK,    PPC64,	POWER9,		अणुRT, RBपूर्णपूर्ण,

अणु"stwcix",	X(31,917),	X_MASK,	     POWER6,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"sthbrx",	X(31,918),	X_MASK,	     COM,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"stfdpx",	X(31,919),	X_MASK,	     POWER6,	POWER7,		अणुFRSp, RA0, RBपूर्णपूर्ण,
अणु"stfqx",	X(31,919),	X_MASK,	     POWER2,	0,		अणुFRS, RA0, RBपूर्णपूर्ण,

अणु"sraq",	XRC(31,920,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"sraq.",	XRC(31,920,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"srea",	XRC(31,921,0),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"srea.",	XRC(31,921,1),	X_MASK,	     M601,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"extsh",	XRC(31,922,0),	XRB_MASK,    PPCCOM,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"exts",	XRC(31,922,0),	XRB_MASK,    PWRCOM,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"extsh.",	XRC(31,922,1),	XRB_MASK,    PPCCOM,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"exts.",	XRC(31,922,1),	XRB_MASK,    PWRCOM,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"stfddx",	X(31,931),	X_MASK,	     E500MC,	0,		अणुFRS, RA, RBपूर्णपूर्ण,

अणु"stvfrxl",	X(31,933),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"wclrone",	XOPL2(31,934,2),XRT_MASK,    PPCA2,	0,		अणुRA0, RBपूर्णपूर्ण,
अणु"wclrall",	X(31,934),	XRARB_MASK,  PPCA2,	0,		अणुL2पूर्णपूर्ण,
अणु"wclr",	X(31,934),	X_MASK,	     PPCA2,	0,		अणुL2, RA0, RBपूर्णपूर्ण,

अणु"stvrxl",	X(31,935),	X_MASK,	     CELL,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"divdeo",	XO(31,425,1,0),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divdeo.",	XO(31,425,1,1),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divweo",	XO(31,427,1,0),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divweo.",	XO(31,427,1,1),	XO_MASK,  POWER7|PPCA2,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"stxvh8x",	X(31,940),	XX1_MASK,    PPCVSX3,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,
अणु"stxsihx",	X(31,941),	XX1_MASK,    PPCVSX3,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"treclaim.",	XRC(31,942,1),	XRTRB_MASK,  PPCHTM,	0,		अणुRAपूर्णपूर्ण,

अणु"tlbrehi",	XTLB(31,946,0),	XTLB_MASK,   PPC403,	PPCA2,		अणुRT, RAपूर्णपूर्ण,
अणु"tlbrelo",	XTLB(31,946,1),	XTLB_MASK,   PPC403,	PPCA2,		अणुRT, RAपूर्णपूर्ण,
अणु"tlbre",	X(31,946),  X_MASK, PPC403|BOOKE|PPCA2|PPC476, 0,	अणुRSO, RAOPT, SHOपूर्णपूर्ण,

अणु"sthcix",	X(31,949),	X_MASK,	     POWER6,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"icswepx",	XRC(31,950,0),	X_MASK,	     PPCA2,	0,		अणुRS, RA, RBपूर्णपूर्ण,
अणु"icswepx.",	XRC(31,950,1),	X_MASK,	     PPCA2,	0,		अणुRS, RA, RBपूर्णपूर्ण,

अणु"stfqux",	X(31,951),	X_MASK,	     POWER2,	0,		अणुFRS, RA, RBपूर्णपूर्ण,

अणु"sraiq",	XRC(31,952,0),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"sraiq.",	XRC(31,952,1),	X_MASK,	     M601,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"extsb",	XRC(31,954,0),	XRB_MASK,    PPC,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"extsb.",	XRC(31,954,1),	XRB_MASK,    PPC,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"stvflxl",	X(31,965),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"iccci",	X(31,966), XRT_MASK, PPC403|PPC440|TITAN|PPCA2, 0,	 अणुRAOPT, RBOPTपूर्णपूर्ण,
अणु"ici",		X(31,966),	XRARB_MASK,  PPCA2|PPC476, 0,		अणुCTपूर्णपूर्ण,

अणु"divduo",	XO(31,457,1,0),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divduo.",	XO(31,457,1,1),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"divwuo",	XO(31,459,1,0),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divwuo.",	XO(31,459,1,1),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"stxvd2x",	X(31,972),	XX1_MASK,    PPCVSX,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,
अणु"stxvx",	X(31,972),	XX1_MASK,    POWER8,	POWER9|PPCVSX3,	अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"tlbld",	X(31,978),	XRTRA_MASK,  PPC, PPC403|BOOKE|PPCA2|PPC476, अणुRBपूर्णपूर्ण,
अणु"tlbwehi",	XTLB(31,978,0),	XTLB_MASK,   PPC403,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"tlbwelo",	XTLB(31,978,1),	XTLB_MASK,   PPC403,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"tlbwe",	X(31,978),  X_MASK, PPC403|BOOKE|PPCA2|PPC476, 0,	अणुRSO, RAOPT, SHOपूर्णपूर्ण,

अणु"slbfee.",	XRC(31,979,1),	XRA_MASK,    POWER6,	0,		अणुRT, RBपूर्णपूर्ण,

अणु"stbcix",	X(31,981),	X_MASK,	     POWER6,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"icbi",	X(31,982),	XRT_MASK,    PPC,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"stfiwx",	X(31,983),	X_MASK,	     PPC,	PPCEFS,		अणुFRS, RA0, RBपूर्णपूर्ण,

अणु"extsw",	XRC(31,986,0),	XRB_MASK,    PPC64,	0,		अणुRA, RSपूर्णपूर्ण,
अणु"extsw.",	XRC(31,986,1),	XRB_MASK,    PPC64,	0,		अणुRA, RSपूर्णपूर्ण,

अणु"icbiep",	XRT(31,991,0),	XRT_MASK,    E500MC|PPCA2, 0,		अणुRA0, RBपूर्णपूर्ण,

अणु"stvswxl",	X(31,997),	X_MASK,	     PPCVEC2,	0,		अणुVS, RA0, RBपूर्णपूर्ण,

अणु"icread",	X(31,998),     XRT_MASK, PPC403|PPC440|PPC476|TITAN, 0,	अणुRA0, RBपूर्णपूर्ण,

अणु"nabso",	XO(31,488,1,0),	XORB_MASK,   M601,	0,		अणुRT, RAपूर्णपूर्ण,
अणु"nabso.",	XO(31,488,1,1),	XORB_MASK,   M601,	0,		अणुRT, RAपूर्णपूर्ण,

अणु"divdo",	XO(31,489,1,0),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divdo.",	XO(31,489,1,1),	XO_MASK,     PPC64,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"divwo",	XO(31,491,1,0),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,
अणु"divwo.",	XO(31,491,1,1),	XO_MASK,     PPC,	0,		अणुRT, RA, RBपूर्णपूर्ण,

अणु"stxvb16x",	X(31,1004),	XX1_MASK,    PPCVSX3,	0,		अणुXS6, RA0, RBपूर्णपूर्ण,

अणु"trechkpt.",	XRC(31,1006,1),	XRTRARB_MASK,PPCHTM,	0,		अणु0पूर्णपूर्ण,

अणु"tlbli",	X(31,1010),	XRTRA_MASK,  PPC,	TITAN,		अणुRBपूर्णपूर्ण,

अणु"stdcix",	X(31,1013),	X_MASK,	     POWER6,	0,		अणुRS, RA0, RBपूर्णपूर्ण,

अणु"dcbz",	X(31,1014),	XRT_MASK,    PPC,	0,		अणुRA0, RBपूर्णपूर्ण,
अणु"dclz",	X(31,1014),	XRT_MASK,    PPC,	0,		अणुRA0, RBपूर्णपूर्ण,

अणु"dcbzep",	XRT(31,1023,0),	XRT_MASK,    E500MC|PPCA2, 0,		अणुRA0, RBपूर्णपूर्ण,

अणु"dcbzl",	XOPL(31,1014,1), XRT_MASK,   POWER4|E500MC, PPC476,	अणुRA0, RBपूर्णपूर्ण,

अणु"cctpl",	0x7c210b78,	0xffffffff,  CELL,	0,		अणु0पूर्णपूर्ण,
अणु"cctpm",	0x7c421378,	0xffffffff,  CELL,	0,		अणु0पूर्णपूर्ण,
अणु"cctph",	0x7c631b78,	0xffffffff,  CELL,	0,		अणु0पूर्णपूर्ण,

अणु"dstt",	XDSS(31,342,1),	XDSS_MASK,   PPCVEC,	0,		अणुRA, RB, STRMपूर्णपूर्ण,
अणु"dststt",	XDSS(31,374,1),	XDSS_MASK,   PPCVEC,	0,		अणुRA, RB, STRMपूर्णपूर्ण,
अणु"dssall",	XDSS(31,822,1),	XDSS_MASK,   PPCVEC,	0,		अणु0पूर्णपूर्ण,

अणु"db8cyc",	0x7f9ce378,	0xffffffff,  CELL,	0,		अणु0पूर्णपूर्ण,
अणु"db10cyc",	0x7fbdeb78,	0xffffffff,  CELL,	0,		अणु0पूर्णपूर्ण,
अणु"db12cyc",	0x7fdef378,	0xffffffff,  CELL,	0,		अणु0पूर्णपूर्ण,
अणु"db16cyc",	0x7ffffb78,	0xffffffff,  CELL,	0,		अणु0पूर्णपूर्ण,

अणु"lwz",		OP(32),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,
अणु"l",		OP(32),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"lwzu",	OP(33),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, D, RALपूर्णपूर्ण,
अणु"lu",		OP(33),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"lbz",		OP(34),		OP_MASK,     COM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"lbzu",	OP(35),		OP_MASK,     COM,	PPCVLE,		अणुRT, D, RALपूर्णपूर्ण,

अणु"stw",		OP(36),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRS, D, RA0पूर्णपूर्ण,
अणु"st",		OP(36),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRS, D, RA0पूर्णपूर्ण,

अणु"stwu",	OP(37),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRS, D, RASपूर्णपूर्ण,
अणु"stu",		OP(37),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRS, D, RA0पूर्णपूर्ण,

अणु"stb",		OP(38),		OP_MASK,     COM,	PPCVLE,		अणुRS, D, RA0पूर्णपूर्ण,

अणु"stbu",	OP(39),		OP_MASK,     COM,	PPCVLE,		अणुRS, D, RASपूर्णपूर्ण,

अणु"lhz",		OP(40),		OP_MASK,     COM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"lhzu",	OP(41),		OP_MASK,     COM,	PPCVLE,		अणुRT, D, RALपूर्णपूर्ण,

अणु"lha",		OP(42),		OP_MASK,     COM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"lhau",	OP(43),		OP_MASK,     COM,	PPCVLE,		अणुRT, D, RALपूर्णपूर्ण,

अणु"sth",		OP(44),		OP_MASK,     COM,	PPCVLE,		अणुRS, D, RA0पूर्णपूर्ण,

अणु"sthu",	OP(45),		OP_MASK,     COM,	PPCVLE,		अणुRS, D, RASपूर्णपूर्ण,

अणु"lmw",		OP(46),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRT, D, RAMपूर्णपूर्ण,
अणु"lm",		OP(46),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"stmw",	OP(47),		OP_MASK,     PPCCOM,	PPCVLE,		अणुRS, D, RA0पूर्णपूर्ण,
अणु"stm",		OP(47),		OP_MASK,     PWRCOM,	PPCVLE,		अणुRS, D, RA0पूर्णपूर्ण,

अणु"lfs",		OP(48),		OP_MASK,     COM,	PPCEFS|PPCVLE,	अणुFRT, D, RA0पूर्णपूर्ण,

अणु"lfsu",	OP(49),		OP_MASK,     COM,	PPCEFS|PPCVLE,	अणुFRT, D, RASपूर्णपूर्ण,

अणु"lfd",		OP(50),		OP_MASK,     COM,	PPCEFS|PPCVLE,	अणुFRT, D, RA0पूर्णपूर्ण,

अणु"lfdu",	OP(51),		OP_MASK,     COM,	PPCEFS|PPCVLE,	अणुFRT, D, RASपूर्णपूर्ण,

अणु"stfs",	OP(52),		OP_MASK,     COM,	PPCEFS|PPCVLE,	अणुFRS, D, RA0पूर्णपूर्ण,

अणु"stfsu",	OP(53),		OP_MASK,     COM,	PPCEFS|PPCVLE,	अणुFRS, D, RASपूर्णपूर्ण,

अणु"stfd",	OP(54),		OP_MASK,     COM,	PPCEFS|PPCVLE,	अणुFRS, D, RA0पूर्णपूर्ण,

अणु"stfdu",	OP(55),		OP_MASK,     COM,	PPCEFS|PPCVLE,	अणुFRS, D, RASपूर्णपूर्ण,

अणु"lq",		OP(56),		OP_MASK,     POWER4,	PPC476|PPCVLE,	अणुRTQ, DQ, RAQपूर्णपूर्ण,
अणु"psq_l",	OP(56),		OP_MASK,     PPCPS,	PPCVLE,		अणुFRT,PSD,RA,PSW,PSQपूर्णपूर्ण,
अणु"lfq",		OP(56),		OP_MASK,     POWER2,	PPCVLE,		अणुFRT, D, RA0पूर्णपूर्ण,

अणु"lxsd",	DSO(57,2),	DS_MASK,     PPCVSX3,	PPCVLE,		अणुVD, DS, RA0पूर्णपूर्ण,
अणु"lxssp",	DSO(57,3),	DS_MASK,     PPCVSX3,	PPCVLE,		अणुVD, DS, RA0पूर्णपूर्ण,
अणु"lfdp",	OP(57),		OP_MASK,     POWER6,	POWER7|PPCVLE,	अणुFRTp, DS, RA0पूर्णपूर्ण,
अणु"psq_lu",	OP(57),		OP_MASK,     PPCPS,	PPCVLE,		अणुFRT,PSD,RA,PSW,PSQपूर्णपूर्ण,
अणु"lfqu",	OP(57),		OP_MASK,     POWER2,	PPCVLE,		अणुFRT, D, RA0पूर्णपूर्ण,

अणु"ld",		DSO(58,0),	DS_MASK,     PPC64,	PPCVLE,		अणुRT, DS, RA0पूर्णपूर्ण,
अणु"ldu",		DSO(58,1),	DS_MASK,     PPC64,	PPCVLE,		अणुRT, DS, RALपूर्णपूर्ण,
अणु"lwa",		DSO(58,2),	DS_MASK,     PPC64,	PPCVLE,		अणुRT, DS, RA0पूर्णपूर्ण,

अणु"dadd",	XRC(59,2,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"dadd.",	XRC(59,2,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"dqua",	ZRC(59,3,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुFRT,FRA,FRB,RMCपूर्णपूर्ण,
अणु"dqua.",	ZRC(59,3,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुFRT,FRA,FRB,RMCपूर्णपूर्ण,

अणु"fdivs",	A(59,18,0),	AFRC_MASK,   PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fdivs.",	A(59,18,1),	AFRC_MASK,   PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fsubs",	A(59,20,0),	AFRC_MASK,   PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fsubs.",	A(59,20,1),	AFRC_MASK,   PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fadds",	A(59,21,0),	AFRC_MASK,   PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fadds.",	A(59,21,1),	AFRC_MASK,   PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fsqrts",	A(59,22,0),    AFRAFRC_MASK, PPC,	TITAN|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fsqrts.",	A(59,22,1),    AFRAFRC_MASK, PPC,	TITAN|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,

अणु"fres",	A(59,24,0),   AFRAFRC_MASK,  POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fres",	A(59,24,0),   AFRALFRC_MASK, PPC,	POWER7|PPCVLE,	अणुFRT, FRB, A_Lपूर्णपूर्ण,
अणु"fres.",	A(59,24,1),   AFRAFRC_MASK,  POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fres.",	A(59,24,1),   AFRALFRC_MASK, PPC,	POWER7|PPCVLE,	अणुFRT, FRB, A_Lपूर्णपूर्ण,

अणु"fmuls",	A(59,25,0),	AFRB_MASK,   PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"fmuls.",	A(59,25,1),	AFRB_MASK,   PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRCपूर्णपूर्ण,

अणु"frsqrtes",	A(59,26,0),   AFRAFRC_MASK,  POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"frsqrtes",	A(59,26,0),   AFRALFRC_MASK, POWER5,	POWER7|PPCVLE,	अणुFRT, FRB, A_Lपूर्णपूर्ण,
अणु"frsqrtes.",	A(59,26,1),   AFRAFRC_MASK,  POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"frsqrtes.",	A(59,26,1),   AFRALFRC_MASK, POWER5,	POWER7|PPCVLE,	अणुFRT, FRB, A_Lपूर्णपूर्ण,

अणु"fmsubs",	A(59,28,0),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fmsubs.",	A(59,28,1),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"fmadds",	A(59,29,0),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fmadds.",	A(59,29,1),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"fnmsubs",	A(59,30,0),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fnmsubs.",	A(59,30,1),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"fnmadds",	A(59,31,0),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fnmadds.",	A(59,31,1),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"dmul",	XRC(59,34,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"dmul.",	XRC(59,34,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"drrnd",	ZRC(59,35,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुFRT, FRA, FRB, RMCपूर्णपूर्ण,
अणु"drrnd.",	ZRC(59,35,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुFRT, FRA, FRB, RMCपूर्णपूर्ण,

अणु"dscli",	ZRC(59,66,0),	Z_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, SH16पूर्णपूर्ण,
अणु"dscli.",	ZRC(59,66,1),	Z_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, SH16पूर्णपूर्ण,

अणु"dquai",	ZRC(59,67,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुTE, FRT,FRB,RMCपूर्णपूर्ण,
अणु"dquai.",	ZRC(59,67,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुTE, FRT,FRB,RMCपूर्णपूर्ण,

अणु"dscri",	ZRC(59,98,0),	Z_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, SH16पूर्णपूर्ण,
अणु"dscri.",	ZRC(59,98,1),	Z_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, SH16पूर्णपूर्ण,

अणु"drintx",	ZRC(59,99,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुR, FRT, FRB, RMCपूर्णपूर्ण,
अणु"drintx.",	ZRC(59,99,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुR, FRT, FRB, RMCपूर्णपूर्ण,

अणु"dcmpo",	X(59,130),	X_MASK,	     POWER6,	PPCVLE,		अणुBF,  FRA, FRBपूर्णपूर्ण,

अणु"dtstex",	X(59,162),	X_MASK,	     POWER6,	PPCVLE,		अणुBF,  FRA, FRBपूर्णपूर्ण,
अणु"dtstdc",	Z(59,194),	Z_MASK,	     POWER6,	PPCVLE,		अणुBF,  FRA, DCMपूर्णपूर्ण,
अणु"dtstdg",	Z(59,226),	Z_MASK,	     POWER6,	PPCVLE,		अणुBF,  FRA, DGMपूर्णपूर्ण,

अणु"drintn",	ZRC(59,227,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुR, FRT, FRB, RMCपूर्णपूर्ण,
अणु"drintn.",	ZRC(59,227,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुR, FRT, FRB, RMCपूर्णपूर्ण,

अणु"dctdp",	XRC(59,258,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"dctdp.",	XRC(59,258,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"dctfix",	XRC(59,290,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"dctfix.",	XRC(59,290,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"ddedpd",	XRC(59,322,0),	X_MASK,	     POWER6,	PPCVLE,		अणुSP, FRT, FRBपूर्णपूर्ण,
अणु"ddedpd.",	XRC(59,322,1),	X_MASK,	     POWER6,	PPCVLE,		अणुSP, FRT, FRBपूर्णपूर्ण,

अणु"dxex",	XRC(59,354,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"dxex.",	XRC(59,354,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"dsub",	XRC(59,514,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"dsub.",	XRC(59,514,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"ddiv",	XRC(59,546,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"ddiv.",	XRC(59,546,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"dcmpu",	X(59,642),	X_MASK,	     POWER6,	PPCVLE,		अणुBF,  FRA, FRBपूर्णपूर्ण,

अणु"dtstsf",	X(59,674),	X_MASK,	     POWER6,	PPCVLE,		अणुBF,  FRA, FRBपूर्णपूर्ण,
अणु"dtstsfi",	X(59,675),	X_MASK|1<<22,POWER9,	PPCVLE,		अणुBF, UIM6, FRBपूर्णपूर्ण,

अणु"drsp",	XRC(59,770,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"drsp.",	XRC(59,770,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"dcffix",	XRC(59,802,0), X_MASK|FRA_MASK, POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"dcffix.",	XRC(59,802,1), X_MASK|FRA_MASK, POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"denbcd",	XRC(59,834,0),	X_MASK,	     POWER6,	PPCVLE,		अणुS, FRT, FRBपूर्णपूर्ण,
अणु"denbcd.",	XRC(59,834,1),	X_MASK,	     POWER6,	PPCVLE,		अणुS, FRT, FRBपूर्णपूर्ण,

अणु"fcfids",	XRC(59,846,0),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fcfids.",	XRC(59,846,1),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"diex",	XRC(59,866,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"diex.",	XRC(59,866,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fcfidus",	XRC(59,974,0),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fcfidus.",	XRC(59,974,1),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"xsaddsp",	XX3(60,0),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsmaddasp",	XX3(60,1),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxsldwi",	XX3(60,2),	XX3SHW_MASK, PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6, SHWपूर्णपूर्ण,
अणु"xscmpeqdp",	XX3(60,3),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsrsqrtesp",	XX2(60,10),	XX2_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xssqrtsp",	XX2(60,11),	XX2_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xxsel",	XX4(60,3),	XX4_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6, XC6पूर्णपूर्ण,
अणु"xssubsp",	XX3(60,8),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsmaddmsp",	XX3(60,9),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxspltd",	XX3(60,10),	XX3DM_MASK,  PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6S, DMEXपूर्णपूर्ण,
अणु"xxmrghd",	XX3(60,10),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxswapd",	XX3(60,10)|(2<<8), XX3_MASK, PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6Sपूर्णपूर्ण,
अणु"xxmrgld",	XX3(60,10)|(3<<8), XX3_MASK, PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxpermdi",	XX3(60,10),	XX3DM_MASK,  PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6, DMपूर्णपूर्ण,
अणु"xscmpgtdp",	XX3(60,11),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsresp",	XX2(60,26),	XX2_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsmulsp",	XX3(60,16),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsmsubasp",	XX3(60,17),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxmrghw",	XX3(60,18),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscmpgedp",	XX3(60,19),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsdivsp",	XX3(60,24),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsmsubmsp",	XX3(60,25),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxperm",	XX3(60,26),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsadddp",	XX3(60,32),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsmaddadp",	XX3(60,33),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscmpudp",	XX3(60,35),	XX3BF_MASK,  PPCVSX,	PPCVLE,		अणुBF, XA6, XB6पूर्णपूर्ण,
अणु"xscvdpuxws",	XX2(60,72),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsrdpi",	XX2(60,73),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsrsqrtedp",	XX2(60,74),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xssqrtdp",	XX2(60,75),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xssubdp",	XX3(60,40),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsmaddmdp",	XX3(60,41),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscmpodp",	XX3(60,43),	XX3BF_MASK,  PPCVSX,	PPCVLE,		अणुBF, XA6, XB6पूर्णपूर्ण,
अणु"xscvdpsxws",	XX2(60,88),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsrdpiz",	XX2(60,89),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsredp",	XX2(60,90),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsmuldp",	XX3(60,48),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsmsubadp",	XX3(60,49),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxmrglw",	XX3(60,50),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsrdpip",	XX2(60,105),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xstsqrtdp",	XX2(60,106),	XX2BF_MASK,  PPCVSX,	PPCVLE,		अणुBF, XB6पूर्णपूर्ण,
अणु"xsrdpic",	XX2(60,107),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsdivdp",	XX3(60,56),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsmsubmdp",	XX3(60,57),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxpermr",	XX3(60,58),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscmpexpdp",	XX3(60,59),	XX3BF_MASK,  PPCVSX3,	PPCVLE,		अणुBF, XA6, XB6पूर्णपूर्ण,
अणु"xsrdpim",	XX2(60,121),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xstdivdp",	XX3(60,61),	XX3BF_MASK,  PPCVSX,	PPCVLE,		अणुBF, XA6, XB6पूर्णपूर्ण,
अणु"xvaddsp",	XX3(60,64),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvmaddasp",	XX3(60,65),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpeqsp",	XX3RC(60,67,0),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpeqsp.",	XX3RC(60,67,1),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvspuxws",	XX2(60,136),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrspi",	XX2(60,137),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrsqrtesp",	XX2(60,138),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvsqrtsp",	XX2(60,139),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvsubsp",	XX3(60,72),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvmaddmsp",	XX3(60,73),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpgtsp",	XX3RC(60,75,0),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpgtsp.",	XX3RC(60,75,1),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvspsxws",	XX2(60,152),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrspiz",	XX2(60,153),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvresp",	XX2(60,154),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvmulsp",	XX3(60,80),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvmsubasp",	XX3(60,81),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxspltw",	XX2(60,164),	XX2UIM_MASK, PPCVSX,	PPCVLE,		अणुXT6, XB6, UIMपूर्णपूर्ण,
अणु"xxextractuw",	XX2(60,165),   XX2UIM4_MASK, PPCVSX3,	PPCVLE,		अणुXT6, XB6, UIMM4पूर्णपूर्ण,
अणु"xvcmpgesp",	XX3RC(60,83,0),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpgesp.",	XX3RC(60,83,1),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvuxwsp",	XX2(60,168),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrspip",	XX2(60,169),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvtsqrtsp",	XX2(60,170),	XX2BF_MASK,  PPCVSX,	PPCVLE,		अणुBF, XB6पूर्णपूर्ण,
अणु"xvrspic",	XX2(60,171),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvdivsp",	XX3(60,88),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvmsubmsp",	XX3(60,89),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxspltib",	X(60,360),   XX1_MASK|3<<19, PPCVSX3,	PPCVLE,		अणुXT6, IMM8पूर्णपूर्ण,
अणु"xxinsertw",	XX2(60,181),   XX2UIM4_MASK, PPCVSX3,	PPCVLE,		अणुXT6, XB6, UIMM4पूर्णपूर्ण,
अणु"xvcvsxwsp",	XX2(60,184),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrspim",	XX2(60,185),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvtdivsp",	XX3(60,93),	XX3BF_MASK,  PPCVSX,	PPCVLE,		अणुBF, XA6, XB6पूर्णपूर्ण,
अणु"xvadddp",	XX3(60,96),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvmaddadp",	XX3(60,97),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpeqdp",	XX3RC(60,99,0),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpeqdp.",	XX3RC(60,99,1),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvdpuxws",	XX2(60,200),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrdpi",	XX2(60,201),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrsqrtedp",	XX2(60,202),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvsqrtdp",	XX2(60,203),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvsubdp",	XX3(60,104),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvmaddmdp",	XX3(60,105),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpgtdp",	XX3RC(60,107,0), XX3_MASK,   PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpgtdp.",	XX3RC(60,107,1), XX3_MASK,   PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvdpsxws",	XX2(60,216),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrdpiz",	XX2(60,217),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvredp",	XX2(60,218),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvmuldp",	XX3(60,112),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvmsubadp",	XX3(60,113),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpgedp",	XX3RC(60,115,0), XX3_MASK,   PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcmpgedp.",	XX3RC(60,115,1), XX3_MASK,   PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvuxwdp",	XX2(60,232),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrdpip",	XX2(60,233),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvtsqrtdp",	XX2(60,234),	XX2BF_MASK,  PPCVSX,	PPCVLE,		अणुBF, XB6पूर्णपूर्ण,
अणु"xvrdpic",	XX2(60,235),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvdivdp",	XX3(60,120),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvmsubmdp",	XX3(60,121),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvsxwdp",	XX2(60,248),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvrdpim",	XX2(60,249),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvtdivdp",	XX3(60,125),	XX3BF_MASK,  PPCVSX,	PPCVLE,		अणुBF, XA6, XB6पूर्णपूर्ण,
अणु"xsmaxcdp",	XX3(60,128),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsnmaddasp",	XX3(60,129),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxland",	XX3(60,130),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscvdpsp",	XX2(60,265),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xscvdpspn",	XX2(60,267),	XX2_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsmincdp",	XX3(60,136),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsnmaddmsp",	XX3(60,137),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxlandc",	XX3(60,138),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsrsp",	XX2(60,281),	XX2_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsmaxjdp",	XX3(60,144),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsnmsubasp",	XX3(60,145),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxlor",	XX3(60,146),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscvuxdsp",	XX2(60,296),	XX2_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xststdcsp",	XX2(60,298),	XX2BFD_MASK, PPCVSX3,	PPCVLE,		अणुBF, XB6, DCMXपूर्णपूर्ण,
अणु"xsminjdp",	XX3(60,152),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsnmsubmsp",	XX3(60,153),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxlxor",	XX3(60,154),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscvsxdsp",	XX2(60,312),	XX2_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsmaxdp",	XX3(60,160),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsnmaddadp",	XX3(60,161),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxlnor",	XX3(60,162),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscvdpuxds",	XX2(60,328),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xscvspdp",	XX2(60,329),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xscvspdpn",	XX2(60,331),	XX2_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsmindp",	XX3(60,168),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsnmaddmdp",	XX3(60,169),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxlorc",	XX3(60,170),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscvdpsxds",	XX2(60,344),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsabsdp",	XX2(60,345),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsxexpdp",	XX2VA(60,347,0),XX2_MASK|1,  PPCVSX3,	PPCVLE,		अणुRT, XB6पूर्णपूर्ण,
अणु"xsxsigdp",	XX2VA(60,347,1),XX2_MASK|1,  PPCVSX3,	PPCVLE,		अणुRT, XB6पूर्णपूर्ण,
अणु"xscvhpdp",	XX2VA(60,347,16),XX2_MASK,   PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xscvdphp",	XX2VA(60,347,17),XX2_MASK,   PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xscpsgndp",	XX3(60,176),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xsnmsubadp",	XX3(60,177),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxlnand",	XX3(60,178),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscvuxddp",	XX2(60,360),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsnabsdp",	XX2(60,361),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xststdcdp",	XX2(60,362),	XX2BFD_MASK, PPCVSX3,	PPCVLE,		अणुBF, XB6, DCMXपूर्णपूर्ण,
अणु"xsnmsubmdp",	XX3(60,185),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xxleqv",	XX3(60,186),	XX3_MASK,    PPCVSX2,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xscvsxddp",	XX2(60,376),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsnegdp",	XX2(60,377),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvmaxsp",	XX3(60,192),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvnmaddasp",	XX3(60,193),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvspuxds",	XX2(60,392),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvcvdpsp",	XX2(60,393),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvminsp",	XX3(60,200),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvnmaddmsp",	XX3(60,201),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvspsxds",	XX2(60,408),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvabssp",	XX2(60,409),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvmovsp",	XX3(60,208),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6Sपूर्णपूर्ण,
अणु"xvcpsgnsp",	XX3(60,208),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvnmsubasp",	XX3(60,209),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvuxdsp",	XX2(60,424),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvnabssp",	XX2(60,425),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvtstdcsp",	XX2(60,426),  XX2DCMXS_MASK, PPCVSX3,	PPCVLE,		अणुXT6, XB6, DCMXSपूर्णपूर्ण,
अणु"xviexpsp",	XX3(60,216),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvnmsubmsp",	XX3(60,217),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvsxdsp",	XX2(60,440),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvnegsp",	XX2(60,441),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvmaxdp",	XX3(60,224),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvnmaddadp",	XX3(60,225),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvdpuxds",	XX2(60,456),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvcvspdp",	XX2(60,457),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xsiexpdp",	X(60,918),	XX1_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, RA, RBपूर्णपूर्ण,
अणु"xvmindp",	XX3(60,232),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvnmaddmdp",	XX3(60,233),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvdpsxds",	XX2(60,472),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvabsdp",	XX2(60,473),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvxexpdp",	XX2VA(60,475,0),XX2_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvxsigdp",	XX2VA(60,475,1),XX2_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xxbrh",	XX2VA(60,475,7),XX2_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvxexpsp",	XX2VA(60,475,8),XX2_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvxsigsp",	XX2VA(60,475,9),XX2_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xxbrw",	XX2VA(60,475,15),XX2_MASK,   PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xxbrd",	XX2VA(60,475,23),XX2_MASK,   PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvcvhpsp",	XX2VA(60,475,24),XX2_MASK,   PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvcvsphp",	XX2VA(60,475,25),XX2_MASK,   PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xxbrq",	XX2VA(60,475,31),XX2_MASK,   PPCVSX3,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvmovdp",	XX3(60,240),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6Sपूर्णपूर्ण,
अणु"xvcpsgndp",	XX3(60,240),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvnmsubadp",	XX3(60,241),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvuxddp",	XX2(60,488),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvnabsdp",	XX2(60,489),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvtstdcdp",	XX2(60,490),  XX2DCMXS_MASK, PPCVSX3,	PPCVLE,		अणुXT6, XB6, DCMXSपूर्णपूर्ण,
अणु"xviexpdp",	XX3(60,248),	XX3_MASK,    PPCVSX3,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvnmsubmdp",	XX3(60,249),	XX3_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XA6, XB6पूर्णपूर्ण,
अणु"xvcvsxddp",	XX2(60,504),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,
अणु"xvnegdp",	XX2(60,505),	XX2_MASK,    PPCVSX,	PPCVLE,		अणुXT6, XB6पूर्णपूर्ण,

अणु"psq_st",	OP(60),		OP_MASK,     PPCPS,	PPCVLE,		अणुFRS,PSD,RA,PSW,PSQपूर्णपूर्ण,
अणु"stfq",	OP(60),		OP_MASK,     POWER2,	PPCVLE,		अणुFRS, D, RAपूर्णपूर्ण,

अणु"lxv",		DQX(61,1),	DQX_MASK,    PPCVSX3,	PPCVLE,		अणुXTQ6, DQ, RA0पूर्णपूर्ण,
अणु"stxv",	DQX(61,5),	DQX_MASK,    PPCVSX3,	PPCVLE,		अणुXSQ6, DQ, RA0पूर्णपूर्ण,
अणु"stxsd",	DSO(61,2),	DS_MASK,     PPCVSX3,	PPCVLE,		अणुVS, DS, RA0पूर्णपूर्ण,
अणु"stxssp",	DSO(61,3),	DS_MASK,     PPCVSX3,	PPCVLE,		अणुVS, DS, RA0पूर्णपूर्ण,
अणु"stfdp",	OP(61),		OP_MASK,     POWER6,	POWER7|PPCVLE,	अणुFRSp, DS, RA0पूर्णपूर्ण,
अणु"psq_stu",	OP(61),		OP_MASK,     PPCPS,	PPCVLE,		अणुFRS,PSD,RA,PSW,PSQपूर्णपूर्ण,
अणु"stfqu",	OP(61),		OP_MASK,     POWER2,	PPCVLE,		अणुFRS, D, RAपूर्णपूर्ण,

अणु"std",		DSO(62,0),	DS_MASK,     PPC64,	PPCVLE,		अणुRS, DS, RA0पूर्णपूर्ण,
अणु"stdu",	DSO(62,1),	DS_MASK,     PPC64,	PPCVLE,		अणुRS, DS, RASपूर्णपूर्ण,
अणु"stq",		DSO(62,2),	DS_MASK,     POWER4,	PPC476|PPCVLE,	अणुRSQ, DS, RA0पूर्णपूर्ण,

अणु"fcmpu",	X(63,0),	XBF_MASK,    COM,	PPCEFS|PPCVLE,	अणुBF, FRA, FRBपूर्णपूर्ण,

अणु"daddq",	XRC(63,2,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBpपूर्णपूर्ण,
अणु"daddq.",	XRC(63,2,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBpपूर्णपूर्ण,

अणु"dquaq",	ZRC(63,3,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBp, RMCपूर्णपूर्ण,
अणु"dquaq.",	ZRC(63,3,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBp, RMCपूर्णपूर्ण,

अणु"xsaddqp",	XRC(63,4,0),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"xsaddqpo",	XRC(63,4,1),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"xsrqpi",	ZRC(63,5,0),	Z2_MASK,     PPCVSX3,	PPCVLE,		अणुR, VD, VB, RMCपूर्णपूर्ण,
अणु"xsrqpix",	ZRC(63,5,1),	Z2_MASK,     PPCVSX3,	PPCVLE,		अणुR, VD, VB, RMCपूर्णपूर्ण,

अणु"fcpsgn",	XRC(63,8,0),	X_MASK, POWER6|PPCA2|PPC476, PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fcpsgn.",	XRC(63,8,1),	X_MASK, POWER6|PPCA2|PPC476, PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"frsp",	XRC(63,12,0),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"frsp.",	XRC(63,12,1),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,

अणु"fctiw",	XRC(63,14,0),	XRA_MASK,    PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fcir",	XRC(63,14,0),	XRA_MASK,    PWR2COM,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctiw.",	XRC(63,14,1),	XRA_MASK,    PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fcir.",	XRC(63,14,1),	XRA_MASK,    PWR2COM,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"fctiwz",	XRC(63,15,0),	XRA_MASK,    PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fcirz",	XRC(63,15,0),	XRA_MASK,    PWR2COM,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctiwz.",	XRC(63,15,1),	XRA_MASK,    PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fcirz.",	XRC(63,15,1),	XRA_MASK,    PWR2COM,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"fdiv",	A(63,18,0),	AFRC_MASK,   PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fd",		A(63,18,0),	AFRC_MASK,   PWRCOM,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fdiv.",	A(63,18,1),	AFRC_MASK,   PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fd.",		A(63,18,1),	AFRC_MASK,   PWRCOM,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fsub",	A(63,20,0),	AFRC_MASK,   PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fs",		A(63,20,0),	AFRC_MASK,   PWRCOM,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fsub.",	A(63,20,1),	AFRC_MASK,   PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fs.",		A(63,20,1),	AFRC_MASK,   PWRCOM,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fadd",	A(63,21,0),	AFRC_MASK,   PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fa",		A(63,21,0),	AFRC_MASK,   PWRCOM,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fadd.",	A(63,21,1),	AFRC_MASK,   PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRBपूर्णपूर्ण,
अणु"fa.",		A(63,21,1),	AFRC_MASK,   PWRCOM,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fsqrt",	A(63,22,0),    AFRAFRC_MASK, PPCPWR2,	TITAN|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fsqrt.",	A(63,22,1),    AFRAFRC_MASK, PPCPWR2,	TITAN|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,

अणु"fsel",	A(63,23,0),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fsel.",	A(63,23,1),	A_MASK,	     PPC,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"fre",		A(63,24,0),   AFRAFRC_MASK,  POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fre",		A(63,24,0),   AFRALFRC_MASK, POWER5,	POWER7|PPCVLE,	अणुFRT, FRB, A_Lपूर्णपूर्ण,
अणु"fre.",	A(63,24,1),   AFRAFRC_MASK,  POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fre.",	A(63,24,1),   AFRALFRC_MASK, POWER5,	POWER7|PPCVLE,	अणुFRT, FRB, A_Lपूर्णपूर्ण,

अणु"fmul",	A(63,25,0),	AFRB_MASK,   PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"fm",		A(63,25,0),	AFRB_MASK,   PWRCOM,	PPCVLE|PPCVLE,	अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"fmul.",	A(63,25,1),	AFRB_MASK,   PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRCपूर्णपूर्ण,
अणु"fm.",		A(63,25,1),	AFRB_MASK,   PWRCOM,	PPCVLE|PPCVLE,	अणुFRT, FRA, FRCपूर्णपूर्ण,

अणु"frsqrte",	A(63,26,0),   AFRAFRC_MASK,  POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"frsqrte",	A(63,26,0),   AFRALFRC_MASK, PPC,	POWER7|PPCVLE,	अणुFRT, FRB, A_Lपूर्णपूर्ण,
अणु"frsqrte.",	A(63,26,1),   AFRAFRC_MASK,  POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"frsqrte.",	A(63,26,1),   AFRALFRC_MASK, PPC,	POWER7|PPCVLE,	अणुFRT, FRB, A_Lपूर्णपूर्ण,

अणु"fmsub",	A(63,28,0),	A_MASK,	     PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fms",		A(63,28,0),	A_MASK,	     PWRCOM,	PPCVLE,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fmsub.",	A(63,28,1),	A_MASK,	     PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fms.",	A(63,28,1),	A_MASK,	     PWRCOM,	PPCVLE,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"fmadd",	A(63,29,0),	A_MASK,	     PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fma",		A(63,29,0),	A_MASK,	     PWRCOM,	PPCVLE,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fmadd.",	A(63,29,1),	A_MASK,	     PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fma.",	A(63,29,1),	A_MASK,	     PWRCOM,	PPCVLE,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"fnmsub",	A(63,30,0),	A_MASK,	     PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fnms",	A(63,30,0),	A_MASK,	     PWRCOM,	PPCVLE,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fnmsub.",	A(63,30,1),	A_MASK,	     PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fnms.",	A(63,30,1),	A_MASK,	     PWRCOM,	PPCVLE,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"fnmadd",	A(63,31,0),	A_MASK,	     PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fnma",	A(63,31,0),	A_MASK,	     PWRCOM,	PPCVLE,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fnmadd.",	A(63,31,1),	A_MASK,	     PPCCOM,	PPCEFS|PPCVLE,	अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,
अणु"fnma.",	A(63,31,1),	A_MASK,	     PWRCOM,	PPCVLE,		अणुFRT, FRA, FRC, FRBपूर्णपूर्ण,

अणु"fcmpo",	X(63,32),	XBF_MASK,    COM,	PPCEFS|PPCVLE,	अणुBF, FRA, FRBपूर्णपूर्ण,

अणु"dmulq",	XRC(63,34,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBpपूर्णपूर्ण,
अणु"dmulq.",	XRC(63,34,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBpपूर्णपूर्ण,

अणु"drrndq",	ZRC(63,35,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुFRTp, FRA, FRBp, RMCपूर्णपूर्ण,
अणु"drrndq.",	ZRC(63,35,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुFRTp, FRA, FRBp, RMCपूर्णपूर्ण,

अणु"xsmulqp",	XRC(63,36,0),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"xsmulqpo",	XRC(63,36,1),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"xsrqpxp",	Z(63,37),	Z2_MASK,     PPCVSX3,	PPCVLE,		अणुR, VD, VB, RMCपूर्णपूर्ण,

अणु"mtfsb1",	XRC(63,38,0),	XRARB_MASK,  COM,	PPCVLE,		अणुBTपूर्णपूर्ण,
अणु"mtfsb1.",	XRC(63,38,1),	XRARB_MASK,  COM,	PPCVLE,		अणुBTपूर्णपूर्ण,

अणु"fneg",	XRC(63,40,0),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fneg.",	XRC(63,40,1),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,

अणु"mcrfs",      X(63,64), XRB_MASK|(3<<21)|(3<<16), COM,	PPCVLE,		अणुBF, BFAपूर्णपूर्ण,

अणु"dscliq",	ZRC(63,66,0),	Z_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, SH16पूर्णपूर्ण,
अणु"dscliq.",	ZRC(63,66,1),	Z_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, SH16पूर्णपूर्ण,

अणु"dquaiq",	ZRC(63,67,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुTE, FRTp, FRBp, RMCपूर्णपूर्ण,
अणु"dquaiq.",	ZRC(63,67,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुTE, FRTp, FRBp, RMCपूर्णपूर्ण,

अणु"mtfsb0",	XRC(63,70,0),	XRARB_MASK,  COM,	PPCVLE,		अणुBTपूर्णपूर्ण,
अणु"mtfsb0.",	XRC(63,70,1),	XRARB_MASK,  COM,	PPCVLE,		अणुBTपूर्णपूर्ण,

अणु"fmr",		XRC(63,72,0),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fmr.",	XRC(63,72,1),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,

अणु"dscriq",	ZRC(63,98,0),	Z_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, SH16पूर्णपूर्ण,
अणु"dscriq.",	ZRC(63,98,1),	Z_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, SH16पूर्णपूर्ण,

अणु"drintxq",	ZRC(63,99,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुR, FRTp, FRBp, RMCपूर्णपूर्ण,
अणु"drintxq.",	ZRC(63,99,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुR, FRTp, FRBp, RMCपूर्णपूर्ण,

अणु"xscpsgnqp",	X(63,100),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"ftdiv",	X(63,128),	XBF_MASK,    POWER7,	PPCVLE,		अणुBF, FRA, FRBपूर्णपूर्ण,

अणु"dcmpoq",	X(63,130),	X_MASK,	     POWER6,	PPCVLE,		अणुBF, FRAp, FRBpपूर्णपूर्ण,

अणु"xscmpoqp",	X(63,132),	XBF_MASK,    PPCVSX3,	PPCVLE,		अणुBF, VA, VBपूर्णपूर्ण,

अणु"mtfsfi",  XRC(63,134,0), XWRA_MASK|(3<<21)|(1<<11), POWER6|PPCA2|PPC476, PPCVLE, अणुBFF, U, Wपूर्णपूर्ण,
अणु"mtfsfi",  XRC(63,134,0), XRA_MASK|(3<<21)|(1<<11), COM, POWER6|PPCA2|PPC476|PPCVLE, अणुBFF, Uपूर्णपूर्ण,
अणु"mtfsfi.", XRC(63,134,1), XWRA_MASK|(3<<21)|(1<<11), POWER6|PPCA2|PPC476, PPCVLE, अणुBFF, U, Wपूर्णपूर्ण,
अणु"mtfsfi.", XRC(63,134,1), XRA_MASK|(3<<21)|(1<<11), COM, POWER6|PPCA2|PPC476|PPCVLE, अणुBFF, Uपूर्णपूर्ण,

अणु"fnabs",	XRC(63,136,0),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fnabs.",	XRC(63,136,1),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,

अणु"fctiwu",	XRC(63,142,0),	XRA_MASK,    POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctiwu.",	XRC(63,142,1),	XRA_MASK,    POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctiwuz",	XRC(63,143,0),	XRA_MASK,    POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctiwuz.",	XRC(63,143,1),	XRA_MASK,    POWER7,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"ftsqrt",	X(63,160),	XBF_MASK|FRA_MASK, POWER7, PPCVLE,	अणुBF, FRBपूर्णपूर्ण,

अणु"dtstexq",	X(63,162),	X_MASK,	     POWER6,	PPCVLE,		अणुBF, FRAp, FRBpपूर्णपूर्ण,

अणु"xscmpexpqp",	X(63,164),	XBF_MASK,    PPCVSX3,	PPCVLE,		अणुBF, VA, VBपूर्णपूर्ण,

अणु"dtstdcq",	Z(63,194),	Z_MASK,	     POWER6,	PPCVLE,		अणुBF, FRAp, DCMपूर्णपूर्ण,
अणु"dtstdgq",	Z(63,226),	Z_MASK,	     POWER6,	PPCVLE,		अणुBF, FRAp, DGMपूर्णपूर्ण,

अणु"drintnq",	ZRC(63,227,0),	Z2_MASK,     POWER6,	PPCVLE,		अणुR, FRTp, FRBp, RMCपूर्णपूर्ण,
अणु"drintnq.",	ZRC(63,227,1),	Z2_MASK,     POWER6,	PPCVLE,		अणुR, FRTp, FRBp, RMCपूर्णपूर्ण,

अणु"dctqpq",	XRC(63,258,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRBपूर्णपूर्ण,
अणु"dctqpq.",	XRC(63,258,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRBपूर्णपूर्ण,

अणु"fabs",	XRC(63,264,0),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"fabs.",	XRC(63,264,1),	XRA_MASK,    COM,	PPCEFS|PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,

अणु"dctfixq",	XRC(63,290,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBpपूर्णपूर्ण,
अणु"dctfixq.",	XRC(63,290,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBpपूर्णपूर्ण,

अणु"ddedpdq",	XRC(63,322,0),	X_MASK,	     POWER6,	PPCVLE,		अणुSP, FRTp, FRBpपूर्णपूर्ण,
अणु"ddedpdq.",	XRC(63,322,1),	X_MASK,	     POWER6,	PPCVLE,		अणुSP, FRTp, FRBpपूर्णपूर्ण,

अणु"dxexq",	XRC(63,354,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBpपूर्णपूर्ण,
अणु"dxexq.",	XRC(63,354,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRT, FRBpपूर्णपूर्ण,

अणु"xsmaddqp",	XRC(63,388,0),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"xsmaddqpo",	XRC(63,388,1),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"frin",	XRC(63,392,0),	XRA_MASK,    POWER5,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"frin.",	XRC(63,392,1),	XRA_MASK,    POWER5,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"xsmsubqp",	XRC(63,420,0),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"xsmsubqpo",	XRC(63,420,1),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"friz",	XRC(63,424,0),	XRA_MASK,    POWER5,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"friz.",	XRC(63,424,1),	XRA_MASK,    POWER5,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"xsnmaddqp",	XRC(63,452,0),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"xsnmaddqpo",	XRC(63,452,1),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"frip",	XRC(63,456,0),	XRA_MASK,    POWER5,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"frip.",	XRC(63,456,1),	XRA_MASK,    POWER5,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"xsnmsubqp",	XRC(63,484,0),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"xsnmsubqpo",	XRC(63,484,1),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"frim",	XRC(63,488,0),	XRA_MASK,    POWER5,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"frim.",	XRC(63,488,1),	XRA_MASK,    POWER5,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"dsubq",	XRC(63,514,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBpपूर्णपूर्ण,
अणु"dsubq.",	XRC(63,514,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBpपूर्णपूर्ण,

अणु"xssubqp",	XRC(63,516,0),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"xssubqpo",	XRC(63,516,1),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"ddivq",	XRC(63,546,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBpपूर्णपूर्ण,
अणु"ddivq.",	XRC(63,546,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRAp, FRBpपूर्णपूर्ण,

अणु"xsdivqp",	XRC(63,548,0),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,
अणु"xsdivqpo",	XRC(63,548,1),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"mffs",	XRC(63,583,0),	XRARB_MASK,  COM,	PPCEFS|PPCVLE,	अणुFRTपूर्णपूर्ण,
अणु"mffs.",	XRC(63,583,1),	XRARB_MASK,  COM,	PPCEFS|PPCVLE,	अणुFRTपूर्णपूर्ण,

अणु"mffsce",	XMMF(63,583,0,1), XMMF_MASK|RB_MASK, POWER9, PPCVLE,	अणुFRTपूर्णपूर्ण,
अणु"mffscdrn",	XMMF(63,583,2,4), XMMF_MASK,         POWER9, PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"mffscdrni",	XMMF(63,583,2,5), XMMF_MASK|(3<<14), POWER9, PPCVLE,	अणुFRT, DRMपूर्णपूर्ण,
अणु"mffscrn",	XMMF(63,583,2,6), XMMF_MASK,         POWER9, PPCVLE,	अणुFRT, FRBपूर्णपूर्ण,
अणु"mffscrni",	XMMF(63,583,2,7), XMMF_MASK|(7<<13), POWER9, PPCVLE,	अणुFRT, RMपूर्णपूर्ण,
अणु"mffsl",	XMMF(63,583,3,0), XMMF_MASK|RB_MASK, POWER9, PPCVLE,	अणुFRTपूर्णपूर्ण,

अणु"dcmpuq",	X(63,642),	X_MASK,	     POWER6,	PPCVLE,		अणुBF, FRAp, FRBpपूर्णपूर्ण,

अणु"xscmpuqp",	X(63,644),	XBF_MASK,    PPCVSX3,	PPCVLE,		अणुBF, VA, VBपूर्णपूर्ण,

अणु"dtstsfq",	X(63,674),	X_MASK,	     POWER6,	PPCVLE,		अणुBF, FRA, FRBpपूर्णपूर्ण,
अणु"dtstsfiq",	X(63,675),	X_MASK|1<<22,POWER9,	PPCVLE,		अणुBF, UIM6, FRBpपूर्णपूर्ण,

अणु"xststdcqp",	X(63,708),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुBF, VB, DCMXपूर्णपूर्ण,

अणु"mtfsf",	XFL(63,711,0),	XFL_MASK, POWER6|PPCA2|PPC476, PPCVLE,	अणुFLM, FRB, XFL_L, Wपूर्णपूर्ण,
अणु"mtfsf",	XFL(63,711,0),	XFL_MASK,    COM, POWER6|PPCA2|PPC476|PPCEFS|PPCVLE, अणुFLM, FRBपूर्णपूर्ण,
अणु"mtfsf.",	XFL(63,711,1),	XFL_MASK, POWER6|PPCA2|PPC476, PPCVLE,	अणुFLM, FRB, XFL_L, Wपूर्णपूर्ण,
अणु"mtfsf.",	XFL(63,711,1),	XFL_MASK,    COM, POWER6|PPCA2|PPC476|PPCEFS|PPCVLE, अणुFLM, FRBपूर्णपूर्ण,

अणु"drdpq",	XRC(63,770,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRBpपूर्णपूर्ण,
अणु"drdpq.",	XRC(63,770,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRBpपूर्णपूर्ण,

अणु"dcffixq",	XRC(63,802,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRBपूर्णपूर्ण,
अणु"dcffixq.",	XRC(63,802,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRBपूर्णपूर्ण,

अणु"xsabsqp",	XVA(63,804,0),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xsxexpqp",	XVA(63,804,2),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xsnabsqp",	XVA(63,804,8),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xsnegqp",	XVA(63,804,16),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xsxsigqp",	XVA(63,804,18),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xssqrtqp",	XVARC(63,804,27,0), XVA_MASK, PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xssqrtqpo",	XVARC(63,804,27,1), XVA_MASK, PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,

अणु"fctid",	XRC(63,814,0),	XRA_MASK,    PPC64,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctid",	XRC(63,814,0),	XRA_MASK,    PPC476,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctid.",	XRC(63,814,1),	XRA_MASK,    PPC64,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctid.",	XRC(63,814,1),	XRA_MASK,    PPC476,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"fctidz",	XRC(63,815,0),	XRA_MASK,    PPC64,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctidz",	XRC(63,815,0),	XRA_MASK,    PPC476,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctidz.",	XRC(63,815,1),	XRA_MASK,    PPC64,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctidz.",	XRC(63,815,1),	XRA_MASK,    PPC476,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"denbcdq",	XRC(63,834,0),	X_MASK,	     POWER6,	PPCVLE,		अणुS, FRTp, FRBpपूर्णपूर्ण,
अणु"denbcdq.",	XRC(63,834,1),	X_MASK,	     POWER6,	PPCVLE,		अणुS, FRTp, FRBpपूर्णपूर्ण,

अणु"xscvqpuwz",	XVA(63,836,1),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xscvudqp",	XVA(63,836,2),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xscvqpswz",	XVA(63,836,9),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xscvsdqp",	XVA(63,836,10),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xscvqpudz",	XVA(63,836,17),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xscvqpdp",	XVARC(63,836,20,0), XVA_MASK, PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xscvqpdpo",	XVARC(63,836,20,1), XVA_MASK, PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xscvdpqp",	XVA(63,836,22),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,
अणु"xscvqpsdz",	XVA(63,836,25),	XVA_MASK,    PPCVSX3,	PPCVLE,		अणुVD, VBपूर्णपूर्ण,

अणु"fmrgow",	X(63,838),	X_MASK,	     PPCVSX2,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fcfid",	XRC(63,846,0),	XRA_MASK,    PPC64,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fcfid",	XRC(63,846,0),	XRA_MASK,    PPC476,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fcfid.",	XRC(63,846,1),	XRA_MASK,    PPC64,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fcfid.",	XRC(63,846,1),	XRA_MASK,    PPC476,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"diexq",	XRC(63,866,0),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRA, FRBpपूर्णपूर्ण,
अणु"diexq.",	XRC(63,866,1),	X_MASK,	     POWER6,	PPCVLE,		अणुFRTp, FRA, FRBpपूर्णपूर्ण,

अणु"xsiexpqp",	X(63,868),	X_MASK,	     PPCVSX3,	PPCVLE,		अणुVD, VA, VBपूर्णपूर्ण,

अणु"fctidu",	XRC(63,942,0),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctidu.",	XRC(63,942,1),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"fctiduz",	XRC(63,943,0),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fctiduz.",	XRC(63,943,1),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,

अणु"fmrgew",	X(63,966),	X_MASK,	     PPCVSX2,	PPCVLE,		अणुFRT, FRA, FRBपूर्णपूर्ण,

अणु"fcfidu",	XRC(63,974,0),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
अणु"fcfidu.",	XRC(63,974,1),	XRA_MASK, POWER7|PPCA2,	PPCVLE,		अणुFRT, FRBपूर्णपूर्ण,
पूर्ण;

स्थिर पूर्णांक घातerpc_num_opcodes =
  माप (घातerpc_opcodes) / माप (घातerpc_opcodes[0]);

/* The VLE opcode table.

   The क्रमmat of this opcode table is the same as the मुख्य opcode table.  */

स्थिर काष्ठा घातerpc_opcode vle_opcodes[] = अणु
अणु"se_illegal",	C(0),		C_MASK,		PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_isync",	C(1),		C_MASK,		PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_sc",	C(2),		C_MASK,		PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_blr",	C_LK(2,0),	C_LK_MASK,	PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_blrl",	C_LK(2,1),	C_LK_MASK,	PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_bctr",	C_LK(3,0),	C_LK_MASK,	PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_bctrl",	C_LK(3,1),	C_LK_MASK,	PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_rfi",	C(8),		C_MASK,		PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_rfci",	C(9),		C_MASK,		PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_rfdi",	C(10),		C_MASK,		PPCVLE,	0,		अणुपूर्णपूर्ण,
अणु"se_rfmci",	C(11),		C_MASK, PPCRFMCI|PPCVLE, 0,		अणुपूर्णपूर्ण,
अणु"se_not",	SE_R(0,2),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_neg",	SE_R(0,3),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_mflr",	SE_R(0,8),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_mtlr",	SE_R(0,9),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_mfctr",	SE_R(0,10),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_mtctr",	SE_R(0,11),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_extzb",	SE_R(0,12),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_extsb",	SE_R(0,13),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_extzh",	SE_R(0,14),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_extsh",	SE_R(0,15),	SE_R_MASK,	PPCVLE,	0,		अणुRXपूर्णपूर्ण,
अणु"se_mr",	SE_RR(0,1),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_mtar",	SE_RR(0,2),	SE_RR_MASK,	PPCVLE,	0,		अणुARX, RYपूर्णपूर्ण,
अणु"se_mfar",	SE_RR(0,3),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, ARYपूर्णपूर्ण,
अणु"se_add",	SE_RR(1,0),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_mullw",	SE_RR(1,1),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_sub",	SE_RR(1,2),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_subf",	SE_RR(1,3),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_cmp",	SE_RR(3,0),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_cmpl",	SE_RR(3,1),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_cmph",	SE_RR(3,2),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_cmphl",	SE_RR(3,3),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,

अणु"e_cmpi",	SCI8BF(6,0,21),	SCI8BF_MASK,	PPCVLE,	0,		अणुCRD32, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_cmpwi",	SCI8BF(6,0,21),	SCI8BF_MASK,	PPCVLE,	0,		अणुCRD32, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_cmpli",	SCI8BF(6,1,21),	SCI8BF_MASK,	PPCVLE,	0,		अणुCRD32, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_cmplwi",	SCI8BF(6,1,21),	SCI8BF_MASK,	PPCVLE,	0,		अणुCRD32, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_addi",	SCI8(6,16),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_subi",	SCI8(6,16),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8Nपूर्णपूर्ण,
अणु"e_addi.",	SCI8(6,17),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_addic",	SCI8(6,18),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_subic",	SCI8(6,18),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8Nपूर्णपूर्ण,
अणु"e_addic.",	SCI8(6,19),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_subic.",	SCI8(6,19),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8Nपूर्णपूर्ण,
अणु"e_mulli",	SCI8(6,20),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_subfic",	SCI8(6,22),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_subfic.",	SCI8(6,23),	SCI8_MASK,	PPCVLE,	0,		अणुRT, RA, SCLSCI8पूर्णपूर्ण,
अणु"e_andi",	SCI8(6,24),	SCI8_MASK,	PPCVLE,	0,		अणुRA, RS, SCLSCI8पूर्णपूर्ण,
अणु"e_andi.",	SCI8(6,25),	SCI8_MASK,	PPCVLE,	0,		अणुRA, RS, SCLSCI8पूर्णपूर्ण,
अणु"e_nop",	SCI8(6,26),	0xffffffff,	PPCVLE,	0,		अणु0पूर्णपूर्ण,
अणु"e_ori",	SCI8(6,26),	SCI8_MASK,	PPCVLE,	0,		अणुRA, RS, SCLSCI8पूर्णपूर्ण,
अणु"e_ori.",	SCI8(6,27),	SCI8_MASK,	PPCVLE,	0,		अणुRA, RS, SCLSCI8पूर्णपूर्ण,
अणु"e_xori",	SCI8(6,28),	SCI8_MASK,	PPCVLE,	0,		अणुRA, RS, SCLSCI8पूर्णपूर्ण,
अणु"e_xori.",	SCI8(6,29),	SCI8_MASK,	PPCVLE,	0,		अणुRA, RS, SCLSCI8पूर्णपूर्ण,
अणु"e_lbzu",	OPVUP(6,0),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_lhau",	OPVUP(6,3),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_lhzu",	OPVUP(6,1),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_lmw",	OPVUP(6,8),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_lwzu",	OPVUP(6,2),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_stbu",	OPVUP(6,4),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_sthu",	OPVUP(6,5),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_stwu",	OPVUP(6,6),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_stmw",	OPVUP(6,9),	OPVUP_MASK,	PPCVLE,	0,		अणुRT, D8, RA0पूर्णपूर्ण,
अणु"e_ldmvgprw",	OPVUPRT(6,16,0),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_stmvgprw",	OPVUPRT(6,17,0),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_ldmvsprw",	OPVUPRT(6,16,1),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_stmvsprw",	OPVUPRT(6,17,1),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_ldmvsrrw",	OPVUPRT(6,16,4),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_stmvsrrw",	OPVUPRT(6,17,4),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_ldmvcsrrw",	OPVUPRT(6,16,5),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_stmvcsrrw",	OPVUPRT(6,17,5),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_ldmvdsrrw",	OPVUPRT(6,16,6),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_stmvdsrrw",	OPVUPRT(6,17,6),OPVUPRT_MASK,	PPCVLE,	0,		अणुD8, RA0पूर्णपूर्ण,
अणु"e_add16i",	OP(7),		OP_MASK,	PPCVLE,	0,		अणुRT, RA, SIपूर्णपूर्ण,
अणु"e_la",	OP(7),		OP_MASK,	PPCVLE,	0,		अणुRT, D, RA0पूर्णपूर्ण,
अणु"e_sub16i",	OP(7),		OP_MASK,	PPCVLE,	0,		अणुRT, RA, NSIपूर्णपूर्ण,

अणु"se_addi",	SE_IM5(8,0),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, OIMM5पूर्णपूर्ण,
अणु"se_cmpli",	SE_IM5(8,1),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, OIMM5पूर्णपूर्ण,
अणु"se_subi",	SE_IM5(9,0),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, OIMM5पूर्णपूर्ण,
अणु"se_subi.",	SE_IM5(9,1),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, OIMM5पूर्णपूर्ण,
अणु"se_cmpi",	SE_IM5(10,1),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,
अणु"se_bmaski",	SE_IM5(11,0),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,
अणु"se_andi",	SE_IM5(11,1),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,

अणु"e_lbz",	OP(12),		OP_MASK,	PPCVLE,	0,		अणुRT, D, RA0पूर्णपूर्ण,
अणु"e_stb",	OP(13),		OP_MASK,	PPCVLE,	0,		अणुRT, D, RA0पूर्णपूर्ण,
अणु"e_lha",	OP(14),		OP_MASK,	PPCVLE,	0,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"se_srw",	SE_RR(16,0),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_sraw",	SE_RR(16,1),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_slw",	SE_RR(16,2),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_nop",	SE_RR(17,0),	0xffff,		PPCVLE,	0,		अणु0पूर्णपूर्ण,
अणु"se_or",	SE_RR(17,0),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_andc",	SE_RR(17,1),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_and",	SE_RR(17,2),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_and.",	SE_RR(17,3),	SE_RR_MASK,	PPCVLE,	0,		अणुRX, RYपूर्णपूर्ण,
अणु"se_li",	IM7(9),		IM7_MASK,	PPCVLE,	0,		अणुRX, UI7पूर्णपूर्ण,

अणु"e_lwz",	OP(20),		OP_MASK,	PPCVLE,	0,		अणुRT, D, RA0पूर्णपूर्ण,
अणु"e_stw",	OP(21),		OP_MASK,	PPCVLE,	0,		अणुRT, D, RA0पूर्णपूर्ण,
अणु"e_lhz",	OP(22),		OP_MASK,	PPCVLE,	0,		अणुRT, D, RA0पूर्णपूर्ण,
अणु"e_sth",	OP(23),		OP_MASK,	PPCVLE,	0,		अणुRT, D, RA0पूर्णपूर्ण,

अणु"se_bclri",	SE_IM5(24,0),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,
अणु"se_bgeni",	SE_IM5(24,1),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,
अणु"se_bseti",	SE_IM5(25,0),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,
अणु"se_btsti",	SE_IM5(25,1),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,
अणु"se_srwi",	SE_IM5(26,0),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,
अणु"se_srawi",	SE_IM5(26,1),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,
अणु"se_slwi",	SE_IM5(27,0),	SE_IM5_MASK,	PPCVLE,	0,		अणुRX, UI5पूर्णपूर्ण,

अणु"e_lis",	I16L(28,28),	I16L_MASK,	PPCVLE,	0,		अणुRD, VLEUIMMLपूर्णपूर्ण,
अणु"e_and2is.",	I16L(28,29),	I16L_MASK,	PPCVLE,	0,		अणुRD, VLEUIMMLपूर्णपूर्ण,
अणु"e_or2is",	I16L(28,26),	I16L_MASK,	PPCVLE,	0,		अणुRD, VLEUIMMLपूर्णपूर्ण,
अणु"e_and2i.",	I16L(28,25),	I16L_MASK,	PPCVLE,	0,		अणुRD, VLEUIMMLपूर्णपूर्ण,
अणु"e_or2i",	I16L(28,24),	I16L_MASK,	PPCVLE,	0,		अणुRD, VLEUIMMLपूर्णपूर्ण,
अणु"e_cmphl16i",	IA16(28,23),	IA16_MASK,	PPCVLE,	0,		अणुRA, VLEUIMMपूर्णपूर्ण,
अणु"e_cmph16i",	IA16(28,22),	IA16_MASK,	PPCVLE,	0,		अणुRA, VLESIMMपूर्णपूर्ण,
अणु"e_cmpl16i",	I16A(28,21),	I16A_MASK,	PPCVLE,	0,		अणुRA, VLEUIMMपूर्णपूर्ण,
अणु"e_mull2i",	I16A(28,20),	I16A_MASK,	PPCVLE,	0,		अणुRA, VLESIMMपूर्णपूर्ण,
अणु"e_cmp16i",	IA16(28,19),	IA16_MASK,	PPCVLE,	0,		अणुRA, VLESIMMपूर्णपूर्ण,
अणु"e_sub2is",	I16A(28,18),	I16A_MASK,	PPCVLE,	0,		अणुRA, VLENSIMMपूर्णपूर्ण,
अणु"e_add2is",	I16A(28,18),	I16A_MASK,	PPCVLE,	0,		अणुRA, VLESIMMपूर्णपूर्ण,
अणु"e_sub2i.",	I16A(28,17),	I16A_MASK,	PPCVLE,	0,		अणुRA, VLENSIMMपूर्णपूर्ण,
अणु"e_add2i.",	I16A(28,17),	I16A_MASK,	PPCVLE,	0,		अणुRA, VLESIMMपूर्णपूर्ण,
अणु"e_li",	LI20(28,0),	LI20_MASK,	PPCVLE,	0,		अणुRT, IMM20पूर्णपूर्ण,
अणु"e_rlwimi",	M(29,0),	M_MASK,		PPCVLE,	0,		अणुRA, RS, SH, MB, MEपूर्णपूर्ण,
अणु"e_rlwinm",	M(29,1),	M_MASK,		PPCVLE,	0,		अणुRA, RT, SH, MBE, MEपूर्णपूर्ण,
अणु"e_b",		BD24(30,0,0),	BD24_MASK,	PPCVLE,	0,		अणुB24पूर्णपूर्ण,
अणु"e_bl",	BD24(30,0,1),	BD24_MASK,	PPCVLE,	0,		अणुB24पूर्णपूर्ण,
अणु"e_bdnz",	EBD15(30,8,BO32DNZ,0),	EBD15_MASK, PPCVLE, 0,		अणुB15पूर्णपूर्ण,
अणु"e_bdnzl",	EBD15(30,8,BO32DNZ,1),	EBD15_MASK, PPCVLE, 0,		अणुB15पूर्णपूर्ण,
अणु"e_bdz",	EBD15(30,8,BO32DZ,0),	EBD15_MASK, PPCVLE, 0,		अणुB15पूर्णपूर्ण,
अणु"e_bdzl",	EBD15(30,8,BO32DZ,1),	EBD15_MASK, PPCVLE, 0,		अणुB15पूर्णपूर्ण,
अणु"e_bge",	EBD15BI(30,8,BO32F,CBLT,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bgel",	EBD15BI(30,8,BO32F,CBLT,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bnl",	EBD15BI(30,8,BO32F,CBLT,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bnll",	EBD15BI(30,8,BO32F,CBLT,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_blt",	EBD15BI(30,8,BO32T,CBLT,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bltl",	EBD15BI(30,8,BO32T,CBLT,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bgt",	EBD15BI(30,8,BO32T,CBGT,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bgtl",	EBD15BI(30,8,BO32T,CBGT,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_ble",	EBD15BI(30,8,BO32F,CBGT,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_blel",	EBD15BI(30,8,BO32F,CBGT,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bng",	EBD15BI(30,8,BO32F,CBGT,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bngl",	EBD15BI(30,8,BO32F,CBGT,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bne",	EBD15BI(30,8,BO32F,CBEQ,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bnel",	EBD15BI(30,8,BO32F,CBEQ,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_beq",	EBD15BI(30,8,BO32T,CBEQ,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_beql",	EBD15BI(30,8,BO32T,CBEQ,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bso",	EBD15BI(30,8,BO32T,CBSO,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bsol",	EBD15BI(30,8,BO32T,CBSO,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bun",	EBD15BI(30,8,BO32T,CBSO,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bunl",	EBD15BI(30,8,BO32T,CBSO,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bns",	EBD15BI(30,8,BO32F,CBSO,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bnsl",	EBD15BI(30,8,BO32F,CBSO,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bnu",	EBD15BI(30,8,BO32F,CBSO,0), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bnul",	EBD15BI(30,8,BO32F,CBSO,1), EBD15BI_MASK, PPCVLE, 0,	अणुCRS,B15पूर्णपूर्ण,
अणु"e_bc",	BD15(30,8,0),	BD15_MASK,	PPCVLE,	0,		अणुBO32, BI32, B15पूर्णपूर्ण,
अणु"e_bcl",	BD15(30,8,1),	BD15_MASK,	PPCVLE,	0,		अणुBO32, BI32, B15पूर्णपूर्ण,

अणु"e_bf",	EBD15(30,8,BO32F,0), EBD15_MASK, PPCVLE, 0,		अणुBI32,B15पूर्णपूर्ण,
अणु"e_bfl",	EBD15(30,8,BO32F,1), EBD15_MASK, PPCVLE, 0,		अणुBI32,B15पूर्णपूर्ण,
अणु"e_bt",	EBD15(30,8,BO32T,0), EBD15_MASK, PPCVLE, 0,		अणुBI32,B15पूर्णपूर्ण,
अणु"e_btl",	EBD15(30,8,BO32T,1), EBD15_MASK, PPCVLE, 0,		अणुBI32,B15पूर्णपूर्ण,

अणु"e_cmph",	X(31,14),	X_MASK,		PPCVLE,	0,		अणुCRD, RA, RBपूर्णपूर्ण,
अणु"e_cmphl",	X(31,46),	X_MASK,		PPCVLE,	0,		अणुCRD, RA, RBपूर्णपूर्ण,
अणु"e_crandc",	XL(31,129),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBपूर्णपूर्ण,
अणु"e_crnand",	XL(31,225),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBपूर्णपूर्ण,
अणु"e_crnot",	XL(31,33),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBAपूर्णपूर्ण,
अणु"e_crnor",	XL(31,33),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBपूर्णपूर्ण,
अणु"e_crclr",	XL(31,193),	XL_MASK,	PPCVLE,	0,		अणुBT, BAT, BBAपूर्णपूर्ण,
अणु"e_crxor",	XL(31,193),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBपूर्णपूर्ण,
अणु"e_mcrf",	XL(31,16),	XL_MASK,	PPCVLE,	0,		अणुCRD, CRपूर्णपूर्ण,
अणु"e_slwi",	EX(31,112),	EX_MASK,	PPCVLE,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"e_slwi.",	EX(31,113),	EX_MASK,	PPCVLE,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"e_crand",	XL(31,257),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"e_rlw",	EX(31,560),	EX_MASK,	PPCVLE,	0,		अणुRA, RS, RBपूर्णपूर्ण,
अणु"e_rlw.",	EX(31,561),	EX_MASK,	PPCVLE,	0,		अणुRA, RS, RBपूर्णपूर्ण,

अणु"e_crset",	XL(31,289),	XL_MASK,	PPCVLE,	0,		अणुBT, BAT, BBAपूर्णपूर्ण,
अणु"e_creqv",	XL(31,289),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"e_rlwi",	EX(31,624),	EX_MASK,	PPCVLE,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"e_rlwi.",	EX(31,625),	EX_MASK,	PPCVLE,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"e_crorc",	XL(31,417),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"e_crmove",	XL(31,449),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBAपूर्णपूर्ण,
अणु"e_cror",	XL(31,449),	XL_MASK,	PPCVLE,	0,		अणुBT, BA, BBपूर्णपूर्ण,

अणु"mtmas1",	XSPR(31,467,625), XSPR_MASK,	PPCVLE,	0,		अणुRSपूर्णपूर्ण,

अणु"e_srwi",	EX(31,1136),	EX_MASK,	PPCVLE,	0,		अणुRA, RS, SHपूर्णपूर्ण,
अणु"e_srwi.",	EX(31,1137),	EX_MASK,	PPCVLE,	0,		अणुRA, RS, SHपूर्णपूर्ण,

अणु"se_lbz",	SD4(8),		SD4_MASK,	PPCVLE,	0,		अणुRZ, SE_SD, RXपूर्णपूर्ण,

अणु"se_stb",	SD4(9),		SD4_MASK,	PPCVLE,	0,		अणुRZ, SE_SD, RXपूर्णपूर्ण,

अणु"se_lhz",	SD4(10),	SD4_MASK,	PPCVLE,	0,		अणुRZ, SE_SDH, RXपूर्णपूर्ण,

अणु"se_sth",	SD4(11),	SD4_MASK,	PPCVLE,	0,		अणुRZ, SE_SDH, RXपूर्णपूर्ण,

अणु"se_lwz",	SD4(12),	SD4_MASK,	PPCVLE,	0,		अणुRZ, SE_SDW, RXपूर्णपूर्ण,

अणु"se_stw",	SD4(13),	SD4_MASK,	PPCVLE,	0,		अणुRZ, SE_SDW, RXपूर्णपूर्ण,

अणु"se_bge",	EBD8IO(28,0,0),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bnl",	EBD8IO(28,0,0),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_ble",	EBD8IO(28,0,1),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bng",	EBD8IO(28,0,1),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bne",	EBD8IO(28,0,2),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bns",	EBD8IO(28,0,3),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bnu",	EBD8IO(28,0,3),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bf",	EBD8IO(28,0,0),	EBD8IO2_MASK,	PPCVLE,	0,		अणुBI16, B8पूर्णपूर्ण,
अणु"se_blt",	EBD8IO(28,1,0),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bgt",	EBD8IO(28,1,1),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_beq",	EBD8IO(28,1,2),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bso",	EBD8IO(28,1,3),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bun",	EBD8IO(28,1,3),	EBD8IO3_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bt",	EBD8IO(28,1,0),	EBD8IO2_MASK,	PPCVLE,	0,		अणुBI16, B8पूर्णपूर्ण,
अणु"se_bc",	BD8IO(28),	BD8IO_MASK,	PPCVLE,	0,		अणुBO16, BI16, B8पूर्णपूर्ण,
अणु"se_b",	BD8(58,0,0),	BD8_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
अणु"se_bl",	BD8(58,0,1),	BD8_MASK,	PPCVLE,	0,		अणुB8पूर्णपूर्ण,
पूर्ण;

स्थिर पूर्णांक vle_num_opcodes =
  माप (vle_opcodes) / माप (vle_opcodes[0]);

/* The macro table.  This is only used by the assembler.  */

/* The expressions of the क्रमm (-x ! 31) & (x | 31) have the value 0
   when x=0; 32-x when x is between 1 and 31; are negative अगर x is
   negative; and are 32 or more otherwise.  This is what you want
   when, क्रम instance, you are emulating a right shअगरt by a
   rotate-left-and-mask, because the underlying inकाष्ठाions support
   shअगरts of size 0 but not shअगरts of size 32.  By comparison, when
   extracting x bits from some word you want to use just 32-x, because
   the underlying inकाष्ठाions करोn't support extracting 0 bits but करो
   support extracting the whole word (32 bits in this हाल).  */

स्थिर काष्ठा घातerpc_macro घातerpc_macros[] = अणु
अणु"extldi",   4,	PPC64,	"rldicr %0,%1,%3,(%2)-1"पूर्ण,
अणु"extldi.",  4,	PPC64,	"rldicr. %0,%1,%3,(%2)-1"पूर्ण,
अणु"extrdi",   4,	PPC64,	"rldicl %0,%1,((%2)+(%3))&((%2)+(%3)<>64),64-(%2)"पूर्ण,
अणु"extrdi.",  4,	PPC64,	"rldicl. %0,%1,((%2)+(%3))&((%2)+(%3)<>64),64-(%2)"पूर्ण,
अणु"insrdi",   4,	PPC64,	"rldimi %0,%1,64-((%2)+(%3)),%3"पूर्ण,
अणु"insrdi.",  4,	PPC64,	"rldimi. %0,%1,64-((%2)+(%3)),%3"पूर्ण,
अणु"rotrdi",   3,	PPC64,	"rldicl %0,%1,(-(%2)!63)&((%2)|63),0"पूर्ण,
अणु"rotrdi.",  3,	PPC64,	"rldicl. %0,%1,(-(%2)!63)&((%2)|63),0"पूर्ण,
अणु"sldi",     3,	PPC64,	"rldicr %0,%1,%2,63-(%2)"पूर्ण,
अणु"sldi.",    3,	PPC64,	"rldicr. %0,%1,%2,63-(%2)"पूर्ण,
अणु"srdi",     3,	PPC64,	"rldicl %0,%1,(-(%2)!63)&((%2)|63),%2"पूर्ण,
अणु"srdi.",    3,	PPC64,	"rldicl. %0,%1,(-(%2)!63)&((%2)|63),%2"पूर्ण,
अणु"clrrdi",   3,	PPC64,	"rldicr %0,%1,0,63-(%2)"पूर्ण,
अणु"clrrdi.",  3,	PPC64,	"rldicr. %0,%1,0,63-(%2)"पूर्ण,
अणु"clrlsldi", 4,	PPC64,	"rldic %0,%1,%3,(%2)-(%3)"पूर्ण,
अणु"clrlsldi.",4,	PPC64,	"rldic. %0,%1,%3,(%2)-(%3)"पूर्ण,

अणु"extlwi",   4,	PPCCOM,	"rlwinm %0,%1,%3,0,(%2)-1"पूर्ण,
अणु"extlwi.",  4,	PPCCOM,	"rlwinm. %0,%1,%3,0,(%2)-1"पूर्ण,
अणु"extrwi",   4,	PPCCOM,	"rlwinm %0,%1,((%2)+(%3))&((%2)+(%3)<>32),32-(%2),31"पूर्ण,
अणु"extrwi.",  4,	PPCCOM,	"rlwinm. %0,%1,((%2)+(%3))&((%2)+(%3)<>32),32-(%2),31"पूर्ण,
अणु"inslwi",   4,	PPCCOM,	"rlwimi %0,%1,(-(%3)!31)&((%3)|31),%3,(%2)+(%3)-1"पूर्ण,
अणु"inslwi.",  4,	PPCCOM,	"rlwimi. %0,%1,(-(%3)!31)&((%3)|31),%3,(%2)+(%3)-1"पूर्ण,
अणु"insrwi",   4,	PPCCOM,	"rlwimi %0,%1,32-((%2)+(%3)),%3,(%2)+(%3)-1"पूर्ण,
अणु"insrwi.",  4,	PPCCOM,	"rlwimi. %0,%1,32-((%2)+(%3)),%3,(%2)+(%3)-1"पूर्ण,
अणु"rotrwi",   3,	PPCCOM,	"rlwinm %0,%1,(-(%2)!31)&((%2)|31),0,31"पूर्ण,
अणु"rotrwi.",  3,	PPCCOM,	"rlwinm. %0,%1,(-(%2)!31)&((%2)|31),0,31"पूर्ण,
अणु"slwi",     3,	PPCCOM,	"rlwinm %0,%1,%2,0,31-(%2)"पूर्ण,
अणु"sli",      3,	PWRCOM,	"rlinm %0,%1,%2,0,31-(%2)"पूर्ण,
अणु"slwi.",    3,	PPCCOM,	"rlwinm. %0,%1,%2,0,31-(%2)"पूर्ण,
अणु"sli.",     3,	PWRCOM,	"rlinm. %0,%1,%2,0,31-(%2)"पूर्ण,
अणु"srwi",     3,	PPCCOM,	"rlwinm %0,%1,(-(%2)!31)&((%2)|31),%2,31"पूर्ण,
अणु"sri",      3,	PWRCOM,	"rlinm %0,%1,(-(%2)!31)&((%2)|31),%2,31"पूर्ण,
अणु"srwi.",    3,	PPCCOM,	"rlwinm. %0,%1,(-(%2)!31)&((%2)|31),%2,31"पूर्ण,
अणु"sri.",     3,	PWRCOM,	"rlinm. %0,%1,(-(%2)!31)&((%2)|31),%2,31"पूर्ण,
अणु"clrrwi",   3,	PPCCOM,	"rlwinm %0,%1,0,0,31-(%2)"पूर्ण,
अणु"clrrwi.",  3,	PPCCOM,	"rlwinm. %0,%1,0,0,31-(%2)"पूर्ण,
अणु"clrlslwi", 4,	PPCCOM,	"rlwinm %0,%1,%3,(%2)-(%3),31-(%3)"पूर्ण,
अणु"clrlslwi.",4, PPCCOM,	"rlwinm. %0,%1,%3,(%2)-(%3),31-(%3)"पूर्ण,

अणु"e_extlwi", 4,	PPCVLE, "e_rlwinm %0,%1,%3,0,(%2)-1"पूर्ण,
अणु"e_extrwi", 4,	PPCVLE, "e_rlwinm %0,%1,((%2)+(%3))&((%2)+(%3)<>32),32-(%2),31"पूर्ण,
अणु"e_inslwi", 4,	PPCVLE, "e_rlwimi %0,%1,(-(%3)!31)&((%3)|31),%3,(%2)+(%3)-1"पूर्ण,
अणु"e_insrwi", 4,	PPCVLE, "e_rlwimi %0,%1,32-((%2)+(%3)),%3,(%2)+(%3)-1"पूर्ण,
अणु"e_rotlwi", 3,	PPCVLE, "e_rlwinm %0,%1,%2,0,31"पूर्ण,
अणु"e_rotrwi", 3,	PPCVLE, "e_rlwinm %0,%1,(-(%2)!31)&((%2)|31),0,31"पूर्ण,
अणु"e_slwi",   3,	PPCVLE, "e_rlwinm %0,%1,%2,0,31-(%2)"पूर्ण,
अणु"e_srwi",   3,	PPCVLE, "e_rlwinm %0,%1,(-(%2)!31)&((%2)|31),%2,31"पूर्ण,
अणु"e_clrlwi", 3,	PPCVLE, "e_rlwinm %0,%1,0,%2,31"पूर्ण,
अणु"e_clrrwi", 3,	PPCVLE, "e_rlwinm %0,%1,0,0,31-(%2)"पूर्ण,
अणु"e_clrlslwi",4, PPCVLE, "e_rlwinm %0,%1,%3,(%2)-(%3),31-(%3)"पूर्ण,
पूर्ण;

स्थिर पूर्णांक घातerpc_num_macros =
  माप (घातerpc_macros) / माप (घातerpc_macros[0]);
