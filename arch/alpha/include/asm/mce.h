<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_MCE_H
#घोषणा __ALPHA_MCE_H

/*
 * This is the logout header that should be common to all platक्रमms
 * (assuming they are running OSF/1 PALcode, I guess).
 */
काष्ठा el_common अणु
	अचिन्हित पूर्णांक	size;		/* size in bytes of logout area */
	अचिन्हित पूर्णांक	sbz1	: 30;	/* should be zero */
	अचिन्हित पूर्णांक	err2	:  1;	/* second error */
	अचिन्हित पूर्णांक	retry	:  1;	/* retry flag */
	अचिन्हित पूर्णांक	proc_offset;	/* processor-specअगरic offset */
	अचिन्हित पूर्णांक	sys_offset;	/* प्रणाली-specअगरic offset */
	अचिन्हित पूर्णांक	code;		/* machine check code */
	अचिन्हित पूर्णांक	frame_rev;	/* frame revision */
पूर्ण;

/* Machine Check Frame क्रम uncorrectable errors (Large क्रमmat)
 *      --- This is used to log uncorrectable errors such as
 *          द्विगुन bit ECC errors.
 *      --- These errors are detected by both processor and प्रणालीs.
 */
काष्ठा el_common_EV5_uncorrectable_mcheck अणु
        अचिन्हित दीर्घ   shaकरोw[8];        /* Shaकरोw reg. 8-14, 25           */
        अचिन्हित दीर्घ   paltemp[24];      /* PAL TEMP REGS.                 */
        अचिन्हित दीर्घ   exc_addr;         /* Address of excepting inकाष्ठाion*/
        अचिन्हित दीर्घ   exc_sum;          /* Summary of arithmetic traps.   */
        अचिन्हित दीर्घ   exc_mask;         /* Exception mask (from exc_sum). */
        अचिन्हित दीर्घ   pal_base;         /* Base address क्रम PALcode.      */
        अचिन्हित दीर्घ   isr;              /* Interrupt Status Reg.          */
        अचिन्हित दीर्घ   icsr;             /* CURRENT SETUP OF EV5 IBOX      */
        अचिन्हित दीर्घ   ic_perr_stat;     /* I-CACHE Reg. <11> set Data parity
                                                         <12> set TAG parity*/
        अचिन्हित दीर्घ   dc_perr_stat;     /* D-CACHE error Reg. Bits set to 1:
                                                     <2> Data error in bank 0
                                                     <3> Data error in bank 1
                                                     <4> Tag error in bank 0
                                                     <5> Tag error in bank 1 */
        अचिन्हित दीर्घ   va;               /* Effective VA of fault or miss. */
        अचिन्हित दीर्घ   mm_stat;          /* Holds the reason क्रम D-stream 
                                             fault or D-cache parity errors */
        अचिन्हित दीर्घ   sc_addr;          /* Address that was being accessed
                                             when EV5 detected Secondary cache
                                             failure.                 */
        अचिन्हित दीर्घ   sc_stat;          /* Helps determine अगर the error was
                                             TAG/Data parity(Secondary Cache)*/
        अचिन्हित दीर्घ   bc_tag_addr;      /* Contents of EV5 BC_TAG_ADDR    */
        अचिन्हित दीर्घ   ei_addr;          /* Physical address of any transfer
                                             that is logged in EV5 EI_STAT */
        अचिन्हित दीर्घ   fill_syndrome;    /* For correcting ECC errors.     */
        अचिन्हित दीर्घ   ei_stat;          /* Helps identअगरy reason of any 
                                             processor uncorrectable error
                                             at its बाह्यal पूर्णांकerface.     */
        अचिन्हित दीर्घ   ld_lock;          /* Contents of EV5 LD_LOCK रेजिस्टर*/
पूर्ण;

काष्ठा el_common_EV6_mcheck अणु
	अचिन्हित पूर्णांक FrameSize;		/* Bytes, including this field */
	अचिन्हित पूर्णांक FrameFlags;	/* <31> = Retry, <30> = Second Error */
	अचिन्हित पूर्णांक CpuOffset;		/* Offset to CPU-specअगरic info */
	अचिन्हित पूर्णांक SystemOffset;	/* Offset to प्रणाली-specअगरic info */
	अचिन्हित पूर्णांक MCHK_Code;
	अचिन्हित पूर्णांक MCHK_Frame_Rev;
	अचिन्हित दीर्घ I_STAT;		/* EV6 Internal Processor Registers */
	अचिन्हित दीर्घ DC_STAT;		/* (See the 21264 Spec) */
	अचिन्हित दीर्घ C_ADDR;
	अचिन्हित दीर्घ DC1_SYNDROME;
	अचिन्हित दीर्घ DC0_SYNDROME;
	अचिन्हित दीर्घ C_STAT;
	अचिन्हित दीर्घ C_STS;
	अचिन्हित दीर्घ MM_STAT;
	अचिन्हित दीर्घ EXC_ADDR;
	अचिन्हित दीर्घ IER_CM;
	अचिन्हित दीर्घ ISUM;
	अचिन्हित दीर्घ RESERVED0;
	अचिन्हित दीर्घ PAL_BASE;
	अचिन्हित दीर्घ I_CTL;
	अचिन्हित दीर्घ PCTX;
पूर्ण;


#पूर्ण_अगर /* __ALPHA_MCE_H */
