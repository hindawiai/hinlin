<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 Hewlett-Packard Co
 * Copyright (C) 2000 David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * Generic IA-64 unwind info decoder.
 *
 * This file is used both by the Linux kernel and objdump.  Please keep
 * the two copies of this file in sync.
 *
 * You need to customize the decoder by defining the following
 * macros/स्थिरants beक्रमe including this file:
 *
 *  Types:
 *	unw_word	Unचिन्हित पूर्णांकeger type with at least 64 bits 
 *
 *  Register names:
 *	UNW_REG_BSP
 *	UNW_REG_BSPSTORE
 *	UNW_REG_FPSR
 *	UNW_REG_LC
 *	UNW_REG_PFS
 *	UNW_REG_PR
 *	UNW_REG_RNAT
 *	UNW_REG_PSP
 *	UNW_REG_RP
 *	UNW_REG_UNAT
 *
 *  Decoder action macros:
 *	UNW_DEC_BAD_CODE(code)
 *	UNW_DEC_ABI(fmt,abi,context,arg)
 *	UNW_DEC_BR_GR(fmt,brmask,gr,arg)
 *	UNW_DEC_BR_MEM(fmt,brmask,arg)
 *	UNW_DEC_COPY_STATE(fmt,label,arg)
 *	UNW_DEC_EPILOGUE(fmt,t,ecount,arg)
 *	UNW_DEC_FRGR_MEM(fmt,grmask,frmask,arg)
 *	UNW_DEC_FR_MEM(fmt,frmask,arg)
 *	UNW_DEC_GR_GR(fmt,grmask,gr,arg)
 *	UNW_DEC_GR_MEM(fmt,grmask,arg)
 *	UNW_DEC_LABEL_STATE(fmt,label,arg)
 *	UNW_DEC_MEM_STACK_F(fmt,t,size,arg)
 *	UNW_DEC_MEM_STACK_V(fmt,t,arg)
 *	UNW_DEC_PRIUNAT_GR(fmt,r,arg)
 *	UNW_DEC_PRIUNAT_WHEN_GR(fmt,t,arg)
 *	UNW_DEC_PRIUNAT_WHEN_MEM(fmt,t,arg)
 *	UNW_DEC_PRIUNAT_WHEN_PSPREL(fmt,pspoff,arg)
 *	UNW_DEC_PRIUNAT_WHEN_SPREL(fmt,spoff,arg)
 *	UNW_DEC_PROLOGUE(fmt,body,rlen,arg)
 *	UNW_DEC_PROLOGUE_GR(fmt,rlen,mask,grsave,arg)
 *	UNW_DEC_REG_PSPREL(fmt,reg,pspoff,arg)
 *	UNW_DEC_REG_REG(fmt,src,dst,arg)
 *	UNW_DEC_REG_SPREL(fmt,reg,spoff,arg)
 *	UNW_DEC_REG_WHEN(fmt,reg,t,arg)
 *	UNW_DEC_RESTORE(fmt,t,abreg,arg)
 *	UNW_DEC_RESTORE_P(fmt,qp,t,abreg,arg)
 *	UNW_DEC_SPILL_BASE(fmt,pspoff,arg)
 *	UNW_DEC_SPILL_MASK(fmt,imaskp,arg)
 *	UNW_DEC_SPILL_PSPREL(fmt,t,abreg,pspoff,arg)
 *	UNW_DEC_SPILL_PSPREL_P(fmt,qp,t,abreg,pspoff,arg)
 *	UNW_DEC_SPILL_REG(fmt,t,abreg,x,ytreg,arg)
 *	UNW_DEC_SPILL_REG_P(fmt,qp,t,abreg,x,ytreg,arg)
 *	UNW_DEC_SPILL_SPREL(fmt,t,abreg,spoff,arg)
 *	UNW_DEC_SPILL_SPREL_P(fmt,qp,t,abreg,pspoff,arg)
 */

अटल unw_word
unw_decode_uleb128 (अचिन्हित अक्षर **dpp)
अणु
  अचिन्हित shअगरt = 0;
  unw_word byte, result = 0;
  अचिन्हित अक्षर *bp = *dpp;

  जबतक (1)
    अणु
      byte = *bp++;
      result |= (byte & 0x7f) << shअगरt;
      अगर ((byte & 0x80) == 0)
	अवरोध;
      shअगरt += 7;
    पूर्ण
  *dpp = bp;
  वापस result;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_x1 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  अचिन्हित अक्षर byte1, abreg;
  unw_word t, off;

  byte1 = *dp++;
  t = unw_decode_uleb128 (&dp);
  off = unw_decode_uleb128 (&dp);
  abreg = (byte1 & 0x7f);
  अगर (byte1 & 0x80)
	  UNW_DEC_SPILL_SPREL(X1, t, abreg, off, arg);
  अन्यथा
	  UNW_DEC_SPILL_PSPREL(X1, t, abreg, off, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_x2 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  अचिन्हित अक्षर byte1, byte2, abreg, x, ytreg;
  unw_word t;

  byte1 = *dp++; byte2 = *dp++;
  t = unw_decode_uleb128 (&dp);
  abreg = (byte1 & 0x7f);
  ytreg = byte2;
  x = (byte1 >> 7) & 1;
  अगर ((byte1 & 0x80) == 0 && ytreg == 0)
    UNW_DEC_RESTORE(X2, t, abreg, arg);
  अन्यथा
    UNW_DEC_SPILL_REG(X2, t, abreg, x, ytreg, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_x3 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  अचिन्हित अक्षर byte1, byte2, abreg, qp;
  unw_word t, off;

  byte1 = *dp++; byte2 = *dp++;
  t = unw_decode_uleb128 (&dp);
  off = unw_decode_uleb128 (&dp);

  qp = (byte1 & 0x3f);
  abreg = (byte2 & 0x7f);

  अगर (byte1 & 0x80)
    UNW_DEC_SPILL_SPREL_P(X3, qp, t, abreg, off, arg);
  अन्यथा
    UNW_DEC_SPILL_PSPREL_P(X3, qp, t, abreg, off, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_x4 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  अचिन्हित अक्षर byte1, byte2, byte3, qp, abreg, x, ytreg;
  unw_word t;

  byte1 = *dp++; byte2 = *dp++; byte3 = *dp++;
  t = unw_decode_uleb128 (&dp);

  qp = (byte1 & 0x3f);
  abreg = (byte2 & 0x7f);
  x = (byte2 >> 7) & 1;
  ytreg = byte3;

  अगर ((byte2 & 0x80) == 0 && byte3 == 0)
    UNW_DEC_RESTORE_P(X4, qp, t, abreg, arg);
  अन्यथा
    UNW_DEC_SPILL_REG_P(X4, qp, t, abreg, x, ytreg, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_r1 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  पूर्णांक body = (code & 0x20) != 0;
  unw_word rlen;

  rlen = (code & 0x1f);
  UNW_DEC_PROLOGUE(R1, body, rlen, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_r2 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  अचिन्हित अक्षर byte1, mask, grsave;
  unw_word rlen;

  byte1 = *dp++;

  mask = ((code & 0x7) << 1) | ((byte1 >> 7) & 1);
  grsave = (byte1 & 0x7f);
  rlen = unw_decode_uleb128 (&dp);
  UNW_DEC_PROLOGUE_GR(R2, rlen, mask, grsave, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_r3 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  unw_word rlen;

  rlen = unw_decode_uleb128 (&dp);
  UNW_DEC_PROLOGUE(R3, ((code & 0x3) == 1), rlen, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_p1 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  अचिन्हित अक्षर brmask = (code & 0x1f);

  UNW_DEC_BR_MEM(P1, brmask, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_p2_p5 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  अगर ((code & 0x10) == 0)
    अणु
      अचिन्हित अक्षर byte1 = *dp++;

      UNW_DEC_BR_GR(P2, ((code & 0xf) << 1) | ((byte1 >> 7) & 1),
		    (byte1 & 0x7f), arg);
    पूर्ण
  अन्यथा अगर ((code & 0x08) == 0)
    अणु
      अचिन्हित अक्षर byte1 = *dp++, r, dst;

      r = ((code & 0x7) << 1) | ((byte1 >> 7) & 1);
      dst = (byte1 & 0x7f);
      चयन (r)
	अणु
	हाल 0: UNW_DEC_REG_GR(P3, UNW_REG_PSP, dst, arg); अवरोध;
	हाल 1: UNW_DEC_REG_GR(P3, UNW_REG_RP, dst, arg); अवरोध;
	हाल 2: UNW_DEC_REG_GR(P3, UNW_REG_PFS, dst, arg); अवरोध;
	हाल 3: UNW_DEC_REG_GR(P3, UNW_REG_PR, dst, arg); अवरोध;
	हाल 4: UNW_DEC_REG_GR(P3, UNW_REG_UNAT, dst, arg); अवरोध;
	हाल 5: UNW_DEC_REG_GR(P3, UNW_REG_LC, dst, arg); अवरोध;
	हाल 6: UNW_DEC_RP_BR(P3, dst, arg); अवरोध;
	हाल 7: UNW_DEC_REG_GR(P3, UNW_REG_RNAT, dst, arg); अवरोध;
	हाल 8: UNW_DEC_REG_GR(P3, UNW_REG_BSP, dst, arg); अवरोध;
	हाल 9: UNW_DEC_REG_GR(P3, UNW_REG_BSPSTORE, dst, arg); अवरोध;
	हाल 10: UNW_DEC_REG_GR(P3, UNW_REG_FPSR, dst, arg); अवरोध;
	हाल 11: UNW_DEC_PRIUNAT_GR(P3, dst, arg); अवरोध;
	शेष: UNW_DEC_BAD_CODE(r); अवरोध;
	पूर्ण
    पूर्ण
  अन्यथा अगर ((code & 0x7) == 0)
    UNW_DEC_SPILL_MASK(P4, dp, arg);
  अन्यथा अगर ((code & 0x7) == 1)
    अणु
      unw_word grmask, frmask, byte1, byte2, byte3;

      byte1 = *dp++; byte2 = *dp++; byte3 = *dp++;
      grmask = ((byte1 >> 4) & 0xf);
      frmask = ((byte1 & 0xf) << 16) | (byte2 << 8) | byte3;
      UNW_DEC_FRGR_MEM(P5, grmask, frmask, arg);
    पूर्ण
  अन्यथा
    UNW_DEC_BAD_CODE(code);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_p6 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  पूर्णांक gregs = (code & 0x10) != 0;
  अचिन्हित अक्षर mask = (code & 0x0f);

  अगर (gregs)
    UNW_DEC_GR_MEM(P6, mask, arg);
  अन्यथा
    UNW_DEC_FR_MEM(P6, mask, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_p7_p10 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  अचिन्हित अक्षर r, byte1, byte2;
  unw_word t, size;

  अगर ((code & 0x10) == 0)
    अणु
      r = (code & 0xf);
      t = unw_decode_uleb128 (&dp);
      चयन (r)
	अणु
	हाल 0:
	  size = unw_decode_uleb128 (&dp);
	  UNW_DEC_MEM_STACK_F(P7, t, size, arg);
	  अवरोध;

	हाल 1: UNW_DEC_MEM_STACK_V(P7, t, arg); अवरोध;
	हाल 2: UNW_DEC_SPILL_BASE(P7, t, arg); अवरोध;
	हाल 3: UNW_DEC_REG_SPREL(P7, UNW_REG_PSP, t, arg); अवरोध;
	हाल 4: UNW_DEC_REG_WHEN(P7, UNW_REG_RP, t, arg); अवरोध;
	हाल 5: UNW_DEC_REG_PSPREL(P7, UNW_REG_RP, t, arg); अवरोध;
	हाल 6: UNW_DEC_REG_WHEN(P7, UNW_REG_PFS, t, arg); अवरोध;
	हाल 7: UNW_DEC_REG_PSPREL(P7, UNW_REG_PFS, t, arg); अवरोध;
	हाल 8: UNW_DEC_REG_WHEN(P7, UNW_REG_PR, t, arg); अवरोध;
	हाल 9: UNW_DEC_REG_PSPREL(P7, UNW_REG_PR, t, arg); अवरोध;
	हाल 10: UNW_DEC_REG_WHEN(P7, UNW_REG_LC, t, arg); अवरोध;
	हाल 11: UNW_DEC_REG_PSPREL(P7, UNW_REG_LC, t, arg); अवरोध;
	हाल 12: UNW_DEC_REG_WHEN(P7, UNW_REG_UNAT, t, arg); अवरोध;
	हाल 13: UNW_DEC_REG_PSPREL(P7, UNW_REG_UNAT, t, arg); अवरोध;
	हाल 14: UNW_DEC_REG_WHEN(P7, UNW_REG_FPSR, t, arg); अवरोध;
	हाल 15: UNW_DEC_REG_PSPREL(P7, UNW_REG_FPSR, t, arg); अवरोध;
	शेष: UNW_DEC_BAD_CODE(r); अवरोध;
	पूर्ण
    पूर्ण
  अन्यथा
    अणु
      चयन (code & 0xf)
	अणु
	हाल 0x0: /* p8 */
	  अणु
	    r = *dp++;
	    t = unw_decode_uleb128 (&dp);
	    चयन (r)
	      अणु
	      हाल  1: UNW_DEC_REG_SPREL(P8, UNW_REG_RP, t, arg); अवरोध;
	      हाल  2: UNW_DEC_REG_SPREL(P8, UNW_REG_PFS, t, arg); अवरोध;
	      हाल  3: UNW_DEC_REG_SPREL(P8, UNW_REG_PR, t, arg); अवरोध;
	      हाल  4: UNW_DEC_REG_SPREL(P8, UNW_REG_LC, t, arg); अवरोध;
	      हाल  5: UNW_DEC_REG_SPREL(P8, UNW_REG_UNAT, t, arg); अवरोध;
	      हाल  6: UNW_DEC_REG_SPREL(P8, UNW_REG_FPSR, t, arg); अवरोध;
	      हाल  7: UNW_DEC_REG_WHEN(P8, UNW_REG_BSP, t, arg); अवरोध;
	      हाल  8: UNW_DEC_REG_PSPREL(P8, UNW_REG_BSP, t, arg); अवरोध;
	      हाल  9: UNW_DEC_REG_SPREL(P8, UNW_REG_BSP, t, arg); अवरोध;
	      हाल 10: UNW_DEC_REG_WHEN(P8, UNW_REG_BSPSTORE, t, arg); अवरोध;
	      हाल 11: UNW_DEC_REG_PSPREL(P8, UNW_REG_BSPSTORE, t, arg); अवरोध;
	      हाल 12: UNW_DEC_REG_SPREL(P8, UNW_REG_BSPSTORE, t, arg); अवरोध;
	      हाल 13: UNW_DEC_REG_WHEN(P8, UNW_REG_RNAT, t, arg); अवरोध;
	      हाल 14: UNW_DEC_REG_PSPREL(P8, UNW_REG_RNAT, t, arg); अवरोध;
	      हाल 15: UNW_DEC_REG_SPREL(P8, UNW_REG_RNAT, t, arg); अवरोध;
	      हाल 16: UNW_DEC_PRIUNAT_WHEN_GR(P8, t, arg); अवरोध;
	      हाल 17: UNW_DEC_PRIUNAT_PSPREL(P8, t, arg); अवरोध;
	      हाल 18: UNW_DEC_PRIUNAT_SPREL(P8, t, arg); अवरोध;
	      हाल 19: UNW_DEC_PRIUNAT_WHEN_MEM(P8, t, arg); अवरोध;
	      शेष: UNW_DEC_BAD_CODE(r); अवरोध;
	    पूर्ण
	  पूर्ण
	  अवरोध;

	हाल 0x1:
	  byte1 = *dp++; byte2 = *dp++;
	  UNW_DEC_GR_GR(P9, (byte1 & 0xf), (byte2 & 0x7f), arg);
	  अवरोध;

	हाल 0xf: /* p10 */
	  byte1 = *dp++; byte2 = *dp++;
	  UNW_DEC_ABI(P10, byte1, byte2, arg);
	  अवरोध;

	हाल 0x9:
	  वापस unw_decode_x1 (dp, code, arg);

	हाल 0xa:
	  वापस unw_decode_x2 (dp, code, arg);

	हाल 0xb:
	  वापस unw_decode_x3 (dp, code, arg);

	हाल 0xc:
	  वापस unw_decode_x4 (dp, code, arg);

	शेष:
	  UNW_DEC_BAD_CODE(code);
	  अवरोध;
	पूर्ण
    पूर्ण
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_b1 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  unw_word label = (code & 0x1f);

  अगर ((code & 0x20) != 0)
    UNW_DEC_COPY_STATE(B1, label, arg);
  अन्यथा
    UNW_DEC_LABEL_STATE(B1, label, arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_b2 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  unw_word t;

  t = unw_decode_uleb128 (&dp);
  UNW_DEC_EPILOGUE(B2, t, (code & 0x1f), arg);
  वापस dp;
पूर्ण

अटल अचिन्हित अक्षर *
unw_decode_b3_x4 (अचिन्हित अक्षर *dp, अचिन्हित अक्षर code, व्योम *arg)
अणु
  unw_word t, ecount, label;

  अगर ((code & 0x10) == 0)
    अणु
      t = unw_decode_uleb128 (&dp);
      ecount = unw_decode_uleb128 (&dp);
      UNW_DEC_EPILOGUE(B3, t, ecount, arg);
    पूर्ण
  अन्यथा अगर ((code & 0x07) == 0)
    अणु
      label = unw_decode_uleb128 (&dp);
      अगर ((code & 0x08) != 0)
	UNW_DEC_COPY_STATE(B4, label, arg);
      अन्यथा
	UNW_DEC_LABEL_STATE(B4, label, arg);
    पूर्ण
  अन्यथा
    चयन (code & 0x7)
      अणु
      हाल 1: वापस unw_decode_x1 (dp, code, arg);
      हाल 2: वापस unw_decode_x2 (dp, code, arg);
      हाल 3: वापस unw_decode_x3 (dp, code, arg);
      हाल 4: वापस unw_decode_x4 (dp, code, arg);
      शेष: UNW_DEC_BAD_CODE(code); अवरोध;
      पूर्ण
  वापस dp;
पूर्ण

प्रकार अचिन्हित अक्षर *(*unw_decoder) (अचिन्हित अक्षर *, अचिन्हित अक्षर, व्योम *);

अटल unw_decoder unw_decode_table[2][8] =
अणु
  /* prologue table: */
  अणु
    unw_decode_r1,	/* 0 */
    unw_decode_r1,
    unw_decode_r2,
    unw_decode_r3,
    unw_decode_p1,	/* 4 */
    unw_decode_p2_p5,
    unw_decode_p6,
    unw_decode_p7_p10
  पूर्ण,
  अणु
    unw_decode_r1,	/* 0 */
    unw_decode_r1,
    unw_decode_r2,
    unw_decode_r3,
    unw_decode_b1,	/* 4 */
    unw_decode_b1,
    unw_decode_b2,
    unw_decode_b3_x4
  पूर्ण
पूर्ण;

/*
 * Decode one descriptor and वापस address of next descriptor.
 */
अटल अंतरभूत अचिन्हित अक्षर *
unw_decode (अचिन्हित अक्षर *dp, पूर्णांक inside_body, व्योम *arg)
अणु
  unw_decoder decoder;
  अचिन्हित अक्षर code;

  code = *dp++;
  decoder = unw_decode_table[inside_body][code >> 5];
  dp = (*decoder) (dp, code, arg);
  वापस dp;
पूर्ण
