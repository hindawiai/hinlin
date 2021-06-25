<शैली गुरु>
/*
 *  linux/include/यंत्र/traps.h
 *
 *  Copyright (C) 1993        Hamish Macकरोnald
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _M68K_TRAPS_H
#घोषणा _M68K_TRAPS_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/linkage.h>
#समावेश <यंत्र/ptrace.h>

प्रकार व्योम (*e_vector)(व्योम);
बाह्य e_vector vectors[];
बाह्य e_vector *_ramvec;

यंत्रlinkage व्योम स्वतः_पूर्णांकhandler(व्योम);
यंत्रlinkage व्योम user_पूर्णांकhandler(व्योम);
यंत्रlinkage व्योम bad_पूर्णांकhandler(व्योम);

#पूर्ण_अगर

#घोषणा VEC_RESETSP (0)
#घोषणा VEC_RESETPC (1)
#घोषणा VEC_BUSERR  (2)
#घोषणा VEC_ADDRERR (3)
#घोषणा VEC_ILLEGAL (4)
#घोषणा VEC_ZERODIV (5)
#घोषणा VEC_CHK     (6)
#घोषणा VEC_TRAP    (7)
#घोषणा VEC_PRIV    (8)
#घोषणा VEC_TRACE   (9)
#घोषणा VEC_LINE10  (10)
#घोषणा VEC_LINE11  (11)
#घोषणा VEC_RESV12  (12)
#घोषणा VEC_COPROC  (13)
#घोषणा VEC_FORMAT  (14)
#घोषणा VEC_UNINT   (15)
#घोषणा VEC_RESV16  (16)
#घोषणा VEC_RESV17  (17)
#घोषणा VEC_RESV18  (18)
#घोषणा VEC_RESV19  (19)
#घोषणा VEC_RESV20  (20)
#घोषणा VEC_RESV21  (21)
#घोषणा VEC_RESV22  (22)
#घोषणा VEC_RESV23  (23)
#घोषणा VEC_SPUR    (24)
#घोषणा VEC_INT1    (25)
#घोषणा VEC_INT2    (26)
#घोषणा VEC_INT3    (27)
#घोषणा VEC_INT4    (28)
#घोषणा VEC_INT5    (29)
#घोषणा VEC_INT6    (30)
#घोषणा VEC_INT7    (31)
#घोषणा VEC_SYS     (32)
#घोषणा VEC_TRAP1   (33)
#घोषणा VEC_TRAP2   (34)
#घोषणा VEC_TRAP3   (35)
#घोषणा VEC_TRAP4   (36)
#घोषणा VEC_TRAP5   (37)
#घोषणा VEC_TRAP6   (38)
#घोषणा VEC_TRAP7   (39)
#घोषणा VEC_TRAP8   (40)
#घोषणा VEC_TRAP9   (41)
#घोषणा VEC_TRAP10  (42)
#घोषणा VEC_TRAP11  (43)
#घोषणा VEC_TRAP12  (44)
#घोषणा VEC_TRAP13  (45)
#घोषणा VEC_TRAP14  (46)
#घोषणा VEC_TRAP15  (47)
#घोषणा VEC_FPBRUC  (48)
#घोषणा VEC_FPIR    (49)
#घोषणा VEC_FPDIVZ  (50)
#घोषणा VEC_FPUNDER (51)
#घोषणा VEC_FPOE    (52)
#घोषणा VEC_FPOVER  (53)
#घोषणा VEC_FPन_अंक   (54)
#घोषणा VEC_FPUNSUP (55)
#घोषणा VEC_MMUCFG  (56)
#घोषणा VEC_MMUILL  (57)
#घोषणा VEC_MMUACC  (58)
#घोषणा VEC_RESV59  (59)
#घोषणा	VEC_UNIMPEA (60)
#घोषणा	VEC_UNIMPII (61)
#घोषणा VEC_RESV62  (62)
#घोषणा VEC_RESV63  (63)
#घोषणा VEC_USER    (64)

#घोषणा VECOFF(vec) ((vec)<<2)

#अगर_अघोषित __ASSEMBLY__

/* Status रेजिस्टर bits */
#घोषणा PS_T  (0x8000)
#घोषणा PS_S  (0x2000)
#घोषणा PS_M  (0x1000)
#घोषणा PS_C  (0x0001)

/* bits क्रम 68020/68030 special status word */

#घोषणा FC    (0x8000)
#घोषणा FB    (0x4000)
#घोषणा RC    (0x2000)
#घोषणा RB    (0x1000)
#घोषणा DF    (0x0100)
#घोषणा RM    (0x0080)
#घोषणा RW    (0x0040)
#घोषणा SZ    (0x0030)
#घोषणा DFC   (0x0007)

/* bits क्रम 68030 MMU status रेजिस्टर (mmusr,psr) */

#घोषणा MMU_B	     (0x8000)    /* bus error */
#घोषणा MMU_L	     (0x4000)    /* limit violation */
#घोषणा MMU_S	     (0x2000)    /* supervisor violation */
#घोषणा MMU_WP	     (0x0800)    /* ग_लिखो-रक्षित */
#घोषणा MMU_I	     (0x0400)    /* invalid descriptor */
#घोषणा MMU_M	     (0x0200)    /* ATC entry modअगरied */
#घोषणा MMU_T	     (0x0040)    /* transparent translation */
#घोषणा MMU_NUM      (0x0007)    /* number of levels traversed */


/* bits क्रम 68040 special status word */
#घोषणा CP_040	(0x8000)
#घोषणा CU_040	(0x4000)
#घोषणा CT_040	(0x2000)
#घोषणा CM_040	(0x1000)
#घोषणा MA_040	(0x0800)
#घोषणा ATC_040 (0x0400)
#घोषणा LK_040	(0x0200)
#घोषणा RW_040	(0x0100)
#घोषणा SIZ_040 (0x0060)
#घोषणा TT_040	(0x0018)
#घोषणा TM_040	(0x0007)

/* bits क्रम 68040 ग_लिखो back status word */
#घोषणा WBV_040   (0x80)
#घोषणा WBSIZ_040 (0x60)
#घोषणा WBBYT_040 (0x20)
#घोषणा WBWRD_040 (0x40)
#घोषणा WBLNG_040 (0x00)
#घोषणा WBTT_040  (0x18)
#घोषणा WBTM_040  (0x07)

/* bus access size codes */
#घोषणा BA_SIZE_BYTE    (0x20)
#घोषणा BA_SIZE_WORD    (0x40)
#घोषणा BA_SIZE_LONG    (0x00)
#घोषणा BA_SIZE_LINE    (0x60)

/* bus access transfer type codes */
#घोषणा BA_TT_MOVE16    (0x08)

/* bits क्रम 68040 MMU status रेजिस्टर (mmusr) */
#घोषणा MMU_B_040   (0x0800)
#घोषणा MMU_G_040   (0x0400)
#घोषणा MMU_S_040   (0x0080)
#घोषणा MMU_CM_040  (0x0060)
#घोषणा MMU_M_040   (0x0010)
#घोषणा MMU_WP_040  (0x0004)
#घोषणा MMU_T_040   (0x0002)
#घोषणा MMU_R_040   (0x0001)

/* bits in the 68060 fault status दीर्घ word (FSLW) */
#घोषणा	MMU060_MA	(0x08000000)	/* misaligned */
#घोषणा	MMU060_LK	(0x02000000)	/* locked transfer */
#घोषणा	MMU060_RW	(0x01800000)	/* पढ़ो/ग_लिखो */
# define MMU060_RW_W	(0x00800000)	/* ग_लिखो */
# define MMU060_RW_R	(0x01000000)	/* पढ़ो */
# define MMU060_RW_RMW	(0x01800000)	/* पढ़ो/modअगरy/ग_लिखो */
# define MMU060_W	(0x00800000)	/* general ग_लिखो, includes rmw */
#घोषणा	MMU060_SIZ	(0x00600000)	/* transfer size */
#घोषणा	MMU060_TT	(0x00180000)	/* transfer type (TT) bits */
#घोषणा	MMU060_TM	(0x00070000)	/* transfer modअगरier (TM) bits */
#घोषणा	MMU060_IO	(0x00008000)	/* inकाष्ठाion or opeअक्रम */
#घोषणा	MMU060_PBE	(0x00004000)	/* push buffer bus error */
#घोषणा	MMU060_SBE	(0x00002000)	/* store buffer bus error */
#घोषणा	MMU060_PTA	(0x00001000)	/* poपूर्णांकer A fault */
#घोषणा	MMU060_PTB	(0x00000800)	/* poपूर्णांकer B fault */
#घोषणा	MMU060_IL	(0x00000400)	/* द्विगुन indirect descr fault */
#घोषणा	MMU060_PF	(0x00000200)	/* page fault (invalid descr) */
#घोषणा	MMU060_SP	(0x00000100)	/* supervisor protection */
#घोषणा	MMU060_WP	(0x00000080)	/* ग_लिखो protection */
#घोषणा	MMU060_TWE	(0x00000040)	/* bus error on table search */
#घोषणा	MMU060_RE	(0x00000020)	/* bus error on पढ़ो */
#घोषणा	MMU060_WE	(0x00000010)	/* bus error on ग_लिखो */
#घोषणा	MMU060_TTR	(0x00000008)	/* error caused by TTR translation */
#घोषणा	MMU060_BPE	(0x00000004)	/* branch prediction error */
#घोषणा	MMU060_SEE	(0x00000001)	/* software emulated error */

/* हालs of missing or invalid descriptors */
#घोषणा MMU060_DESC_ERR (MMU060_PTA | MMU060_PTB | \
			 MMU060_IL  | MMU060_PF)
/* bits that indicate real errors */
#घोषणा MMU060_ERR_BITS (MMU060_PBE | MMU060_SBE | MMU060_DESC_ERR | MMU060_SP | \
			 MMU060_WP  | MMU060_TWE | MMU060_RE       | MMU060_WE)

/* काष्ठाure क्रम stack frames */

काष्ठा frame अणु
    काष्ठा pt_regs ptregs;
    जोड़ अणु
	    काष्ठा अणु
		    अचिन्हित दीर्घ  iaddr;    /* inकाष्ठाion address */
	    पूर्ण fmt2;
	    काष्ठा अणु
		    अचिन्हित दीर्घ  effaddr;  /* effective address */
	    पूर्ण fmt3;
	    काष्ठा अणु
		    अचिन्हित दीर्घ  effaddr;  /* effective address */
		    अचिन्हित दीर्घ  pc;	     /* pc of faulted instr */
	    पूर्ण fmt4;
	    काष्ठा अणु
		    अचिन्हित दीर्घ  effaddr;  /* effective address */
		    अचिन्हित लघु ssw;      /* special status word */
		    अचिन्हित लघु wb3s;     /* ग_लिखो back 3 status */
		    अचिन्हित लघु wb2s;     /* ग_लिखो back 2 status */
		    अचिन्हित लघु wb1s;     /* ग_लिखो back 1 status */
		    अचिन्हित दीर्घ  faddr;    /* fault address */
		    अचिन्हित दीर्घ  wb3a;     /* ग_लिखो back 3 address */
		    अचिन्हित दीर्घ  wb3d;     /* ग_लिखो back 3 data */
		    अचिन्हित दीर्घ  wb2a;     /* ग_लिखो back 2 address */
		    अचिन्हित दीर्घ  wb2d;     /* ग_लिखो back 2 data */
		    अचिन्हित दीर्घ  wb1a;     /* ग_लिखो back 1 address */
		    अचिन्हित दीर्घ  wb1dpd0;  /* ग_लिखो back 1 data/push data 0*/
		    अचिन्हित दीर्घ  pd1;      /* push data 1*/
		    अचिन्हित दीर्घ  pd2;      /* push data 2*/
		    अचिन्हित दीर्घ  pd3;      /* push data 3*/
	    पूर्ण fmt7;
	    काष्ठा अणु
		    अचिन्हित दीर्घ  iaddr;    /* inकाष्ठाion address */
		    अचिन्हित लघु पूर्णांक1[4];  /* पूर्णांकernal रेजिस्टरs */
	    पूर्ण fmt9;
	    काष्ठा अणु
		    अचिन्हित लघु पूर्णांक1;
		    अचिन्हित लघु ssw;      /* special status word */
		    अचिन्हित लघु isc;      /* inकाष्ठाion stage c */
		    अचिन्हित लघु isb;      /* inकाष्ठाion stage b */
		    अचिन्हित दीर्घ  daddr;    /* data cycle fault address */
		    अचिन्हित लघु पूर्णांक2[2];
		    अचिन्हित दीर्घ  करोbuf;    /* data cycle output buffer */
		    अचिन्हित लघु पूर्णांक3[2];
	    पूर्ण fmta;
	    काष्ठा अणु
		    अचिन्हित लघु पूर्णांक1;
		    अचिन्हित लघु ssw;     /* special status word */
		    अचिन्हित लघु isc;     /* inकाष्ठाion stage c */
		    अचिन्हित लघु isb;     /* inकाष्ठाion stage b */
		    अचिन्हित दीर्घ  daddr;   /* data cycle fault address */
		    अचिन्हित लघु पूर्णांक2[2];
		    अचिन्हित दीर्घ  करोbuf;   /* data cycle output buffer */
		    अचिन्हित लघु पूर्णांक3[4];
		    अचिन्हित दीर्घ  baddr;   /* stage B address */
		    अचिन्हित लघु पूर्णांक4[2];
		    अचिन्हित दीर्घ  dibuf;   /* data cycle input buffer */
		    अचिन्हित लघु पूर्णांक5[3];
		    अचिन्हित	   ver : 4; /* stack frame version # */
		    अचिन्हित	   पूर्णांक6:12;
		    अचिन्हित लघु पूर्णांक7[18];
	    पूर्ण fmtb;
    पूर्ण un;
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _M68K_TRAPS_H */
