<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcfdebug.h -- ColdFire Debug Module support.
 *
 * 	(C) Copyright 2001, Lineo Inc. (www.lineo.com) 
 */

/****************************************************************************/
#अगर_अघोषित mcfdebug_h
#घोषणा mcfdebug_h
/****************************************************************************/

/* Define the debug module रेजिस्टरs */
#घोषणा MCFDEBUG_CSR	0x0			/* Configuration status		*/
#घोषणा MCFDEBUG_BAAR	0x5			/* BDM address attribute	*/
#घोषणा MCFDEBUG_AATR	0x6			/* Address attribute trigger	*/
#घोषणा MCFDEBUG_TDR	0x7			/* Trigger definition		*/
#घोषणा MCFDEBUG_PBR	0x8			/* PC अवरोधpoपूर्णांक		*/
#घोषणा MCFDEBUG_PBMR	0x9			/* PC अवरोधpoपूर्णांक mask		*/
#घोषणा MCFDEBUG_ABHR	0xc			/* High address अवरोधpoपूर्णांक	*/
#घोषणा MCFDEBUG_ABLR	0xd			/* Low address अवरोधpoपूर्णांक	*/
#घोषणा MCFDEBUG_DBR	0xe			/* Data अवरोधpoपूर्णांक		*/
#घोषणा MCFDEBUG_DBMR	0xf			/* Data अवरोधpoपूर्णांक mask		*/

/* Define some handy स्थिरants क्रम the trigger definition रेजिस्टर */
#घोषणा MCFDEBUG_TDR_TRC_DISP	0x00000000	/* display on DDATA only	*/
#घोषणा MCFDEBUG_TDR_TRC_HALT	0x40000000	/* Processor halt on BP		*/
#घोषणा MCFDEBUG_TDR_TRC_INTR	0x80000000	/* Debug पूर्णांकr on BP		*/
#घोषणा MCFDEBUG_TDR_LXT1	0x00004000	/* TDR level 1			*/
#घोषणा MCFDEBUG_TDR_LXT2	0x00008000	/* TDR level 2			*/
#घोषणा MCFDEBUG_TDR_EBL1	0x00002000	/* Enable अवरोधpoपूर्णांक level 1	*/
#घोषणा MCFDEBUG_TDR_EBL2	0x20000000	/* Enable अवरोधpoपूर्णांक level 2	*/
#घोषणा MCFDEBUG_TDR_EDLW1	0x00001000	/* Enable data BP दीर्घword	*/
#घोषणा MCFDEBUG_TDR_EDLW2	0x10000000
#घोषणा MCFDEBUG_TDR_EDWL1	0x00000800	/* Enable data BP lower word	*/
#घोषणा MCFDEBUG_TDR_EDWL2	0x08000000
#घोषणा MCFDEBUG_TDR_EDWU1	0x00000400	/* Enable data BP upper word	*/
#घोषणा MCFDEBUG_TDR_EDWU2	0x04000000
#घोषणा MCFDEBUG_TDR_EDLL1	0x00000200	/* Enable data BP low low byte	*/
#घोषणा MCFDEBUG_TDR_EDLL2	0x02000000
#घोषणा MCFDEBUG_TDR_EDLM1	0x00000100	/* Enable data BP low mid byte	*/
#घोषणा MCFDEBUG_TDR_EDLM2	0x01000000
#घोषणा MCFDEBUG_TDR_EDUM1	0x00000080	/* Enable data BP up mid byte	*/
#घोषणा MCFDEBUG_TDR_EDUM2	0x00800000
#घोषणा MCFDEBUG_TDR_EDUU1	0x00000040	/* Enable data BP up up byte	*/
#घोषणा MCFDEBUG_TDR_EDUU2	0x00400000
#घोषणा MCFDEBUG_TDR_DI1	0x00000020	/* Data BP invert		*/
#घोषणा MCFDEBUG_TDR_DI2	0x00200000
#घोषणा MCFDEBUG_TDR_EAI1	0x00000010	/* Enable address BP inverted	*/
#घोषणा MCFDEBUG_TDR_EAI2	0x00100000
#घोषणा MCFDEBUG_TDR_EAR1	0x00000008	/* Enable address BP range	*/
#घोषणा MCFDEBUG_TDR_EAR2	0x00080000
#घोषणा MCFDEBUG_TDR_EAL1	0x00000004	/* Enable address BP low	*/
#घोषणा MCFDEBUG_TDR_EAL2	0x00040000
#घोषणा MCFDEBUG_TDR_EPC1	0x00000002	/* Enable PC BP			*/
#घोषणा MCFDEBUG_TDR_EPC2	0x00020000
#घोषणा MCFDEBUG_TDR_PCI1	0x00000001	/* PC BP invert			*/
#घोषणा MCFDEBUG_TDR_PCI2	0x00010000

/* Constants क्रम the address attribute trigger रेजिस्टर */
#घोषणा MCFDEBUG_AAR_RESET	0x00000005
/* Fields not yet implemented */

/* And some definitions क्रम the writable sections of the CSR */
#घोषणा MCFDEBUG_CSR_RESET	0x00100000
#घोषणा MCFDEBUG_CSR_PSTCLK	0x00020000	/* PSTCLK disable		*/
#घोषणा MCFDEBUG_CSR_IPW	0x00010000	/* Inhibit processor ग_लिखोs	*/
#घोषणा MCFDEBUG_CSR_MAP	0x00008000	/* Processor refs in emul mode	*/
#घोषणा MCFDEBUG_CSR_TRC	0x00004000	/* Emul mode on trace exception	*/
#घोषणा MCFDEBUG_CSR_EMU	0x00002000	/* Force emulation mode		*/
#घोषणा MCFDEBUG_CSR_DDC_READ	0x00000800	/* Debug data control		*/
#घोषणा MCFDEBUG_CSR_DDC_WRITE	0x00001000
#घोषणा MCFDEBUG_CSR_UHE	0x00000400	/* User mode halt enable	*/
#घोषणा MCFDEBUG_CSR_BTB0	0x00000000	/* Branch target 0 bytes	*/
#घोषणा MCFDEBUG_CSR_BTB2	0x00000100	/* Branch target 2 bytes	*/
#घोषणा MCFDEBUG_CSR_BTB3	0x00000200	/* Branch target 3 bytes	*/
#घोषणा MCFDEBUG_CSR_BTB4	0x00000300	/* Branch target 4 bytes	*/
#घोषणा MCFDEBUG_CSR_NPL	0x00000040	/* Non-pipelined mode		*/
#घोषणा MCFDEBUG_CSR_SSM	0x00000010	/* Single step mode		*/

/* Constants क्रम the BDM address attribute रेजिस्टर */
#घोषणा MCFDEBUG_BAAR_RESET	0x00000005
/* Fields not yet implemented */


/* This routine wrappers up the wdebug यंत्र inकाष्ठाion so that the रेजिस्टर
 * and value can be relatively easily specअगरied.  The biggest hassle here is
 * that the debug module inकाष्ठाions (2 दीर्घs) must be दीर्घ word aligned and
 * some poपूर्णांकer fiddling is perक्रमmed to ensure this.
 */
अटल अंतरभूत व्योम wdebug(पूर्णांक reg, अचिन्हित दीर्घ data) अणु
	अचिन्हित लघु dbg_spc[6];
	अचिन्हित लघु *dbg;

	// Force alignment to दीर्घ word boundary
	dbg = (अचिन्हित लघु *)((((अचिन्हित दीर्घ)dbg_spc) + 3) & 0xfffffffc);

	// Build up the debug inकाष्ठाion
	dbg[0] = 0x2c80 | (reg & 0xf);
	dbg[1] = (data >> 16) & 0xffff;
	dbg[2] = data & 0xffff;
	dbg[3] = 0;

	// Perक्रमm the wdebug inकाष्ठाion
#अगर 0
	// This strain is क्रम gas which करोesn't have the wdebug inकाष्ठाions defined
	यंत्र(	"move.l	%0, %%a0\n\t"
		".word	0xfbd0\n\t"
		".word	0x0003\n\t"
	    :: "g" (dbg) : "a0");
#अन्यथा
	// And this is क्रम when it करोes
	यंत्र(	"wdebug	(%0)" :: "a" (dbg));
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर
