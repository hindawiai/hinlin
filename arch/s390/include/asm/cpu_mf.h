<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CPU-measurement facilities
 *
 *  Copyright IBM Corp. 2012, 2018
 *  Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 *	       Jan Glauber <jang@linux.vnet.ibm.com>
 */
#अगर_अघोषित _ASM_S390_CPU_MF_H
#घोषणा _ASM_S390_CPU_MF_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/facility.h>

यंत्र(".include \"asm/cpu_mf-insn.h\"\n");

#घोषणा CPU_MF_INT_SF_IAE	(1 << 31)	/* invalid entry address */
#घोषणा CPU_MF_INT_SF_ISE	(1 << 30)	/* incorrect SDBT entry */
#घोषणा CPU_MF_INT_SF_PRA	(1 << 29)	/* program request alert */
#घोषणा CPU_MF_INT_SF_SACA	(1 << 23)	/* sampler auth. change alert */
#घोषणा CPU_MF_INT_SF_LSDA	(1 << 22)	/* loss of sample data alert */
#घोषणा CPU_MF_INT_CF_MTDA	(1 << 15)	/* loss of MT ctr. data alert */
#घोषणा CPU_MF_INT_CF_CACA	(1 <<  7)	/* counter auth. change alert */
#घोषणा CPU_MF_INT_CF_LCDA	(1 <<  6)	/* loss of counter data alert */
#घोषणा CPU_MF_INT_CF_MASK	(CPU_MF_INT_CF_MTDA|CPU_MF_INT_CF_CACA| \
				 CPU_MF_INT_CF_LCDA)
#घोषणा CPU_MF_INT_SF_MASK	(CPU_MF_INT_SF_IAE|CPU_MF_INT_SF_ISE|	\
				 CPU_MF_INT_SF_PRA|CPU_MF_INT_SF_SACA|	\
				 CPU_MF_INT_SF_LSDA)

#घोषणा CPU_MF_SF_RIBM_NOTAV	0x1		/* Sampling unavailable */

/* CPU measurement facility support */
अटल अंतरभूत पूर्णांक cpum_cf_avail(व्योम)
अणु
	वापस test_facility(40) && test_facility(67);
पूर्ण

अटल अंतरभूत पूर्णांक cpum_sf_avail(व्योम)
अणु
	वापस test_facility(40) && test_facility(68);
पूर्ण


काष्ठा cpumf_ctr_info अणु
	u16   cfvn;
	u16   auth_ctl;
	u16   enable_ctl;
	u16   act_ctl;
	u16   max_cpu;
	u16   csvn;
	u16   max_cg;
	u16   reserved1;
	u32   reserved2[12];
पूर्ण __packed;

/* QUERY SAMPLING INFORMATION block */
काष्ठा hws_qsi_info_block अणु	    /* Bit(s) */
	अचिन्हित पूर्णांक b0_13:14;	    /* 0-13: zeros			 */
	अचिन्हित पूर्णांक as:1;	    /* 14: basic-sampling authorization	 */
	अचिन्हित पूर्णांक ad:1;	    /* 15: diag-sampling authorization	 */
	अचिन्हित पूर्णांक b16_21:6;	    /* 16-21: zeros			 */
	अचिन्हित पूर्णांक es:1;	    /* 22: basic-sampling enable control */
	अचिन्हित पूर्णांक ed:1;	    /* 23: diag-sampling enable control	 */
	अचिन्हित पूर्णांक b24_29:6;	    /* 24-29: zeros			 */
	अचिन्हित पूर्णांक cs:1;	    /* 30: basic-sampling activation control */
	अचिन्हित पूर्णांक cd:1;	    /* 31: diag-sampling activation control */
	अचिन्हित पूर्णांक bsdes:16;	    /* 4-5: size of basic sampling entry */
	अचिन्हित पूर्णांक dsdes:16;	    /* 6-7: size of diagnostic sampling entry */
	अचिन्हित दीर्घ min_sampl_rate; /* 8-15: minimum sampling पूर्णांकerval */
	अचिन्हित दीर्घ max_sampl_rate; /* 16-23: maximum sampling पूर्णांकerval*/
	अचिन्हित दीर्घ tear;	    /* 24-31: TEAR contents		 */
	अचिन्हित दीर्घ dear;	    /* 32-39: DEAR contents		 */
	अचिन्हित पूर्णांक rsvrd0:24;	    /* 40-42: reserved			 */
	अचिन्हित पूर्णांक ribm:8;	    /* 43: Reserved by IBM		 */
	अचिन्हित पूर्णांक cpu_speed;     /* 44-47: CPU speed			 */
	अचिन्हित दीर्घ दीर्घ rsvrd1;  /* 48-55: reserved			 */
	अचिन्हित दीर्घ दीर्घ rsvrd2;  /* 56-63: reserved			 */
पूर्ण __packed;

/* SET SAMPLING CONTROLS request block */
काष्ठा hws_lsctl_request_block अणु
	अचिन्हित पूर्णांक s:1;	    /* 0: maximum buffer indicator	 */
	अचिन्हित पूर्णांक h:1;	    /* 1: part. level reserved क्रम VM use*/
	अचिन्हित दीर्घ दीर्घ b2_53:52;/* 2-53: zeros			 */
	अचिन्हित पूर्णांक es:1;	    /* 54: basic-sampling enable control */
	अचिन्हित पूर्णांक ed:1;	    /* 55: diag-sampling enable control	 */
	अचिन्हित पूर्णांक b56_61:6;	    /* 56-61: - zeros			 */
	अचिन्हित पूर्णांक cs:1;	    /* 62: basic-sampling activation control */
	अचिन्हित पूर्णांक cd:1;	    /* 63: diag-sampling activation control  */
	अचिन्हित दीर्घ पूर्णांकerval;     /* 8-15: sampling पूर्णांकerval		 */
	अचिन्हित दीर्घ tear;	    /* 16-23: TEAR contents		 */
	अचिन्हित दीर्घ dear;	    /* 24-31: DEAR contents		 */
	/* 32-63:							 */
	अचिन्हित दीर्घ rsvrd1;	    /* reserved				 */
	अचिन्हित दीर्घ rsvrd2;	    /* reserved				 */
	अचिन्हित दीर्घ rsvrd3;	    /* reserved				 */
	अचिन्हित दीर्घ rsvrd4;	    /* reserved				 */
पूर्ण __packed;

काष्ठा hws_basic_entry अणु
	अचिन्हित पूर्णांक def:16;	    /* 0-15  Data Entry Format		 */
	अचिन्हित पूर्णांक R:4;	    /* 16-19 reserved			 */
	अचिन्हित पूर्णांक U:4;	    /* 20-23 Number of unique inकाष्ठा.  */
	अचिन्हित पूर्णांक z:2;	    /* zeros				 */
	अचिन्हित पूर्णांक T:1;	    /* 26 PSW DAT mode			 */
	अचिन्हित पूर्णांक W:1;	    /* 27 PSW रुको state		 */
	अचिन्हित पूर्णांक P:1;	    /* 28 PSW Problem state		 */
	अचिन्हित पूर्णांक AS:2;	    /* 29-30 PSW address-space control	 */
	अचिन्हित पूर्णांक I:1;	    /* 31 entry valid or invalid	 */
	अचिन्हित पूर्णांक CL:2;	    /* 32-33 Configuration Level	 */
	अचिन्हित पूर्णांक:14;
	अचिन्हित पूर्णांक prim_asn:16;   /* primary ASN			 */
	अचिन्हित दीर्घ दीर्घ ia;	    /* Inकाष्ठाion Address		 */
	अचिन्हित दीर्घ दीर्घ gpp;     /* Guest Program Parameter		 */
	अचिन्हित दीर्घ दीर्घ hpp;     /* Host Program Parameter		 */
पूर्ण __packed;

काष्ठा hws_diag_entry अणु
	अचिन्हित पूर्णांक def:16;	    /* 0-15  Data Entry Format		 */
	अचिन्हित पूर्णांक R:15;	    /* 16-19 and 20-30 reserved		 */
	अचिन्हित पूर्णांक I:1;	    /* 31 entry valid or invalid	 */
	u8	     data[];	    /* Machine-dependent sample data	 */
पूर्ण __packed;

काष्ठा hws_combined_entry अणु
	काष्ठा hws_basic_entry	basic;	/* Basic-sampling data entry */
	काष्ठा hws_diag_entry	diag;	/* Diagnostic-sampling data entry */
पूर्ण __packed;

काष्ठा hws_trailer_entry अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक f:1;	/* 0 - Block Full Indicator   */
			अचिन्हित पूर्णांक a:1;	/* 1 - Alert request control  */
			अचिन्हित पूर्णांक t:1;	/* 2 - Timestamp क्रमmat	      */
			अचिन्हित पूर्णांक :29;	/* 3 - 31: Reserved	      */
			अचिन्हित पूर्णांक bsdes:16;	/* 32-47: size of basic SDE   */
			अचिन्हित पूर्णांक dsdes:16;	/* 48-63: size of diagnostic SDE */
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ flags;	/* 0 - 63: All indicators     */
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ overflow;	 /* 64 - sample Overflow count	      */
	अचिन्हित अक्षर बारtamp[16];	 /* 16 - 31 बारtamp		      */
	अचिन्हित दीर्घ दीर्घ reserved1;	 /* 32 -Reserved		      */
	अचिन्हित दीर्घ दीर्घ reserved2;	 /*				      */
	जोड़ अणु				 /* 48 - reserved क्रम programming use */
		काष्ठा अणु
			अचिन्हित पूर्णांक घड़ी_base:1; /* in progusage2 */
			अचिन्हित दीर्घ दीर्घ progusage1:63;
			अचिन्हित दीर्घ दीर्घ progusage2;
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ progusage[2];
	पूर्ण;
पूर्ण __packed;

/* Load program parameter */
अटल अंतरभूत व्योम lpp(व्योम *pp)
अणु
	यंत्र अस्थिर(".insn s,0xb2800000,0(%0)\n":: "a" (pp) : "memory");
पूर्ण

/* Query counter inक्रमmation */
अटल अंतरभूत पूर्णांक qctri(काष्ठा cpumf_ctr_info *info)
अणु
	पूर्णांक rc = -EINVAL;

	यंत्र अस्थिर (
		"0:	.insn	s,0xb28e0000,%1\n"
		"1:	lhi	%0,0\n"
		"2:\n"
		EX_TABLE(1b, 2b)
		: "+d" (rc), "=Q" (*info));
	वापस rc;
पूर्ण

/* Load CPU-counter-set controls */
अटल अंतरभूत पूर्णांक lcctl(u64 ctl)
अणु
	पूर्णांक cc;

	यंत्र अस्थिर (
		"	.insn	s,0xb2840000,%1\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc) : "Q" (ctl) : "cc");
	वापस cc;
पूर्ण

/* Extract CPU counter */
अटल अंतरभूत पूर्णांक __ecctr(u64 ctr, u64 *content)
अणु
	u64 _content;
	पूर्णांक cc;

	यंत्र अस्थिर (
		"	.insn	rre,0xb2e40000,%0,%2\n"
		"	ipm	%1\n"
		"	srl	%1,28\n"
		: "=d" (_content), "=d" (cc) : "d" (ctr) : "cc");
	*content = _content;
	वापस cc;
पूर्ण

/* Extract CPU counter */
अटल अंतरभूत पूर्णांक ecctr(u64 ctr, u64 *val)
अणु
	u64 content;
	पूर्णांक cc;

	cc = __ecctr(ctr, &content);
	अगर (!cc)
		*val = content;
	वापस cc;
पूर्ण

/* Store CPU counter multiple क्रम a particular counter set */
क्रमागत stccपंचांग_ctr_set अणु
	EXTENDED = 0,
	BASIC = 1,
	PROBLEM_STATE = 2,
	CRYPTO_ACTIVITY = 3,
	MT_DIAG = 5,
	MT_DIAG_CLEARING = 9,	/* clears loss-of-MT-ctr-data alert */
पूर्ण;

अटल __always_अंतरभूत पूर्णांक stccपंचांग(क्रमागत stccपंचांग_ctr_set set, u64 range, u64 *dest)
अणु
	पूर्णांक cc;

	यंत्र अस्थिर (
		"	STCCTM	%2,%3,%1\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc)
		: "Q" (*dest), "d" (range), "i" (set)
		: "cc", "memory");
	वापस cc;
पूर्ण

/* Query sampling inक्रमmation */
अटल अंतरभूत पूर्णांक qsi(काष्ठा hws_qsi_info_block *info)
अणु
	पूर्णांक cc = 1;

	यंत्र अस्थिर(
		"0:	.insn	s,0xb2860000,%1\n"
		"1:	lhi	%0,0\n"
		"2:\n"
		EX_TABLE(0b, 2b) EX_TABLE(1b, 2b)
		: "+d" (cc), "+Q" (*info));
	वापस cc ? -EINVAL : 0;
पूर्ण

/* Load sampling controls */
अटल अंतरभूत पूर्णांक lsctl(काष्ठा hws_lsctl_request_block *req)
अणु
	पूर्णांक cc;

	cc = 1;
	यंत्र अस्थिर(
		"0:	.insn	s,0xb2870000,0(%1)\n"
		"1:	ipm	%0\n"
		"	srl	%0,28\n"
		"2:\n"
		EX_TABLE(0b, 2b) EX_TABLE(1b, 2b)
		: "+d" (cc), "+a" (req)
		: "m" (*req)
		: "cc", "memory");

	वापस cc ? -EINVAL : 0;
पूर्ण

/* Sampling control helper functions */

#समावेश <linux/समय.स>

अटल अंतरभूत अचिन्हित दीर्घ freq_to_sample_rate(काष्ठा hws_qsi_info_block *qsi,
						अचिन्हित दीर्घ freq)
अणु
	वापस (USEC_PER_SEC / freq) * qsi->cpu_speed;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sample_rate_to_freq(काष्ठा hws_qsi_info_block *qsi,
						अचिन्हित दीर्घ rate)
अणु
	वापस USEC_PER_SEC * qsi->cpu_speed / rate;
पूर्ण

#घोषणा SDB_TE_ALERT_REQ_MASK	0x4000000000000000UL
#घोषणा SDB_TE_BUFFER_FULL_MASK 0x8000000000000000UL

/* Return TOD बारtamp contained in an trailer entry */
अटल अंतरभूत अचिन्हित दीर्घ दीर्घ trailer_बारtamp(काष्ठा hws_trailer_entry *te)
अणु
	/* TOD in STCKE क्रमmat */
	अगर (te->t)
		वापस *((अचिन्हित दीर्घ दीर्घ *) &te->बारtamp[1]);

	/* TOD in STCK क्रमmat */
	वापस *((अचिन्हित दीर्घ दीर्घ *) &te->बारtamp[0]);
पूर्ण

/* Return poपूर्णांकer to trailer entry of an sample data block */
अटल अंतरभूत अचिन्हित दीर्घ *trailer_entry_ptr(अचिन्हित दीर्घ v)
अणु
	व्योम *ret;

	ret = (व्योम *) v;
	ret += PAGE_SIZE;
	ret -= माप(काष्ठा hws_trailer_entry);

	वापस (अचिन्हित दीर्घ *) ret;
पूर्ण

/* Return true अगर the entry in the sample data block table (sdbt)
 * is a link to the next sdbt */
अटल अंतरभूत पूर्णांक is_link_entry(अचिन्हित दीर्घ *s)
अणु
	वापस *s & 0x1ul ? 1 : 0;
पूर्ण

/* Return poपूर्णांकer to the linked sdbt */
अटल अंतरभूत अचिन्हित दीर्घ *get_next_sdbt(अचिन्हित दीर्घ *s)
अणु
	वापस (अचिन्हित दीर्घ *) (*s & ~0x1ul);
पूर्ण
#पूर्ण_अगर /* _ASM_S390_CPU_MF_H */
