<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.com, 1998-1999
    
    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#अगर_अघोषित __FPA11_H__
#घोषणा __FPA11_H__

#घोषणा GET_FPA11() ((FPA11 *)(&current_thपढ़ो_info()->fpstate))

/*
 * The processes रेजिस्टरs are always at the very top of the 8K
 * stack+task काष्ठा.  Use the same method as 'current' uses to
 * reach them.
 */
#घोषणा GET_USERREG() ((काष्ठा pt_regs *)(THREAD_START_SP + (अचिन्हित दीर्घ)current_thपढ़ो_info()) - 1)

#समावेश <linux/thपढ़ो_info.h>

/* includes */
#समावेश "fpsr.h"		/* FP control and status रेजिस्टर definitions */
#समावेश "milieu.h"

काष्ठा roundingData अणु
    पूर्णांक8 mode;
    पूर्णांक8 precision;
    चिन्हित अक्षर exception;
पूर्ण;

#समावेश "softfloat.h"

#घोषणा		typeNone		0x00
#घोषणा		typeSingle		0x01
#घोषणा		typeDouble		0x02
#घोषणा		typeExtended		0x03

/*
 * This must be no more and no less than 12 bytes.
 */
प्रकार जोड़ tagFPREG अणु
	भग्न32 fSingle;
	भग्न64 fDouble;
#अगर_घोषित CONFIG_FPE_NWFPE_XP
	भग्नx80 fExtended;
#अन्यथा
	u32 padding[3];
#पूर्ण_अगर
पूर्ण __attribute__ ((packed,aligned(4))) FPREG;

/*
 * FPA11 device model.
 *
 * This काष्ठाure is exported to user space.  Do not re-order.
 * Only add new stuff to the end, and करो not change the size of
 * any element.  Elements of this काष्ठाure are used by user
 * space, and must match काष्ठा user_fp in <यंत्र/user.h>.
 * We include the byte offsets below क्रम करोcumentation purposes.
 *
 * The size of this काष्ठाure and FPREG are checked by fpmodule.c
 * on initialisation.  If the rules have been broken, NWFPE will
 * not initialise.
 */
प्रकार काष्ठा tagFPA11 अणु
/*   0 */ FPREG fpreg[8];	/* 8 भग्नing poपूर्णांक रेजिस्टरs */
/*  96 */ FPSR fpsr;		/* भग्नing poपूर्णांक status रेजिस्टर */
/* 100 */ FPCR fpcr;		/* भग्नing poपूर्णांक control रेजिस्टर */
/* 104 */ अचिन्हित अक्षर fType[8];	/* type of भग्नing poपूर्णांक value held in
					   भग्नing poपूर्णांक रेजिस्टरs.  One of
					   none, single, द्विगुन or extended. */
/* 112 */ पूर्णांक initflag;		/* this is special.  The kernel guarantees
				   to set it to 0 when a thपढ़ो is launched,
				   so we can use it to detect whether this
				   instance of the emulator needs to be
				   initialised. */
पूर्ण __attribute__ ((packed,aligned(4))) FPA11;

बाह्य पूर्णांक8 SetRoundingMode(स्थिर अचिन्हित पूर्णांक);
बाह्य पूर्णांक8 SetRoundingPrecision(स्थिर अचिन्हित पूर्णांक);
बाह्य व्योम nwfpe_init_fpa(जोड़ fp_state *fp);

बाह्य अचिन्हित पूर्णांक EmulateAll(अचिन्हित पूर्णांक opcode);

बाह्य अचिन्हित पूर्णांक EmulateCPDT(स्थिर अचिन्हित पूर्णांक opcode);
बाह्य अचिन्हित पूर्णांक EmulateCPDO(स्थिर अचिन्हित पूर्णांक opcode);
बाह्य अचिन्हित पूर्णांक EmulateCPRT(स्थिर अचिन्हित पूर्णांक opcode);

/* fpa11_cpdt.c */
बाह्य अचिन्हित पूर्णांक Perक्रमmLDF(स्थिर अचिन्हित पूर्णांक opcode);
बाह्य अचिन्हित पूर्णांक Perक्रमmSTF(स्थिर अचिन्हित पूर्णांक opcode);
बाह्य अचिन्हित पूर्णांक Perक्रमmLFM(स्थिर अचिन्हित पूर्णांक opcode);
बाह्य अचिन्हित पूर्णांक Perक्रमmSFM(स्थिर अचिन्हित पूर्णांक opcode);

/* single_cpकरो.c */

बाह्य अचिन्हित पूर्णांक SingleCPDO(काष्ठा roundingData *roundData,
			       स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd);
/* द्विगुन_cpकरो.c */
बाह्य अचिन्हित पूर्णांक DoubleCPDO(काष्ठा roundingData *roundData,
			       स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd);

/* extneded_cpकरो.c */
बाह्य अचिन्हित पूर्णांक ExtendedCPDO(काष्ठा roundingData *roundData,
				 स्थिर अचिन्हित पूर्णांक opcode, FPREG * rFd);

#पूर्ण_अगर
