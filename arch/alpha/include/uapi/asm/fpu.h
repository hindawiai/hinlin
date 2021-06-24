<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__ASM_ALPHA_FPU_H
#घोषणा _UAPI__ASM_ALPHA_FPU_H


/*
 * Alpha भग्नing-poपूर्णांक control रेजिस्टर defines:
 */
#घोषणा FPCR_DNOD	(1UL<<47)	/* denorm INV trap disable */
#घोषणा FPCR_DNZ	(1UL<<48)	/* denorms to zero */
#घोषणा FPCR_INVD	(1UL<<49)	/* invalid op disable (opt.) */
#घोषणा FPCR_DZED	(1UL<<50)	/* भागision by zero disable (opt.) */
#घोषणा FPCR_OVFD	(1UL<<51)	/* overflow disable (optional) */
#घोषणा FPCR_INV	(1UL<<52)	/* invalid operation */
#घोषणा FPCR_DZE	(1UL<<53)	/* भागision by zero */
#घोषणा FPCR_OVF	(1UL<<54)	/* overflow */
#घोषणा FPCR_UNF	(1UL<<55)	/* underflow */
#घोषणा FPCR_INE	(1UL<<56)	/* inexact */
#घोषणा FPCR_IOV	(1UL<<57)	/* पूर्णांकeger overflow */
#घोषणा FPCR_UNDZ	(1UL<<60)	/* underflow to zero (opt.) */
#घोषणा FPCR_UNFD	(1UL<<61)	/* underflow disable (opt.) */
#घोषणा FPCR_INED	(1UL<<62)	/* inexact disable (opt.) */
#घोषणा FPCR_SUM	(1UL<<63)	/* summary bit */

#घोषणा FPCR_DYN_SHIFT	58		/* first dynamic rounding mode bit */
#घोषणा FPCR_DYN_CHOPPED (0x0UL << FPCR_DYN_SHIFT)	/* towards 0 */
#घोषणा FPCR_DYN_MINUS	 (0x1UL << FPCR_DYN_SHIFT)	/* towards -INF */
#घोषणा FPCR_DYN_NORMAL	 (0x2UL << FPCR_DYN_SHIFT)	/* towards nearest */
#घोषणा FPCR_DYN_PLUS	 (0x3UL << FPCR_DYN_SHIFT)	/* towards +INF */
#घोषणा FPCR_DYN_MASK	 (0x3UL << FPCR_DYN_SHIFT)

#घोषणा FPCR_MASK	0xffff800000000000L

/*
 * IEEE trap enables are implemented in software.  These per-thपढ़ो
 * bits are stored in the "ieee_state" field of "struct thread_info".
 * Thus, the bits are defined so as not to conflict with the
 * भग्नing-poपूर्णांक enable bit (which is architected).  On top of that,
 * we want to make these bits compatible with OSF/1 so
 * ieee_set_fp_control() etc. can be implemented easily and
 * compatibly.  The corresponding definitions are in
 * /usr/include/machine/fpu.h under OSF/1.
 */
#घोषणा IEEE_TRAP_ENABLE_INV	(1UL<<1)	/* invalid op */
#घोषणा IEEE_TRAP_ENABLE_DZE	(1UL<<2)	/* भागision by zero */
#घोषणा IEEE_TRAP_ENABLE_OVF	(1UL<<3)	/* overflow */
#घोषणा IEEE_TRAP_ENABLE_UNF	(1UL<<4)	/* underflow */
#घोषणा IEEE_TRAP_ENABLE_INE	(1UL<<5)	/* inexact */
#घोषणा IEEE_TRAP_ENABLE_DNO	(1UL<<6)	/* denorm */
#घोषणा IEEE_TRAP_ENABLE_MASK	(IEEE_TRAP_ENABLE_INV | IEEE_TRAP_ENABLE_DZE |\
				 IEEE_TRAP_ENABLE_OVF | IEEE_TRAP_ENABLE_UNF |\
				 IEEE_TRAP_ENABLE_INE | IEEE_TRAP_ENABLE_DNO)

/* Denorm and Underflow flushing */
#घोषणा IEEE_MAP_DMZ		(1UL<<12)	/* Map denorm inमाला_दो to zero */
#घोषणा IEEE_MAP_UMZ		(1UL<<13)	/* Map underflowed outमाला_दो to zero */

#घोषणा IEEE_MAP_MASK		(IEEE_MAP_DMZ | IEEE_MAP_UMZ)

/* status bits coming from fpcr: */
#घोषणा IEEE_STATUS_INV		(1UL<<17)
#घोषणा IEEE_STATUS_DZE		(1UL<<18)
#घोषणा IEEE_STATUS_OVF		(1UL<<19)
#घोषणा IEEE_STATUS_UNF		(1UL<<20)
#घोषणा IEEE_STATUS_INE		(1UL<<21)
#घोषणा IEEE_STATUS_DNO		(1UL<<22)

#घोषणा IEEE_STATUS_MASK	(IEEE_STATUS_INV | IEEE_STATUS_DZE |	\
				 IEEE_STATUS_OVF | IEEE_STATUS_UNF |	\
				 IEEE_STATUS_INE | IEEE_STATUS_DNO)

#घोषणा IEEE_SW_MASK		(IEEE_TRAP_ENABLE_MASK |		\
				 IEEE_STATUS_MASK | IEEE_MAP_MASK)

#घोषणा IEEE_CURRENT_RM_SHIFT	32
#घोषणा IEEE_CURRENT_RM_MASK	(3UL<<IEEE_CURRENT_RM_SHIFT)

#घोषणा IEEE_STATUS_TO_EXCSUM_SHIFT	16

#घोषणा IEEE_INHERIT    (1UL<<63)	/* inherit on thपढ़ो create? */

/*
 * Convert the software IEEE trap enable and status bits पूर्णांकo the
 * hardware fpcr क्रमmat. 
 *
 * Digital Unix engineers receive my thanks क्रम not defining the
 * software bits identical to the hardware bits.  The chip designers
 * receive my thanks क्रम making all the not-implemented fpcr bits
 * RAZ क्रमcing us to use प्रणाली calls to पढ़ो/ग_लिखो this value.
 */

अटल अंतरभूत अचिन्हित दीर्घ
ieee_swcr_to_fpcr(अचिन्हित दीर्घ sw)
अणु
	अचिन्हित दीर्घ fp;
	fp = (sw & IEEE_STATUS_MASK) << 35;
	fp |= (sw & IEEE_MAP_DMZ) << 36;
	fp |= (sw & IEEE_STATUS_MASK ? FPCR_SUM : 0);
	fp |= (~sw & (IEEE_TRAP_ENABLE_INV
		      | IEEE_TRAP_ENABLE_DZE
		      | IEEE_TRAP_ENABLE_OVF)) << 48;
	fp |= (~sw & (IEEE_TRAP_ENABLE_UNF | IEEE_TRAP_ENABLE_INE)) << 57;
	fp |= (sw & IEEE_MAP_UMZ ? FPCR_UNDZ | FPCR_UNFD : 0);
	fp |= (~sw & IEEE_TRAP_ENABLE_DNO) << 41;
	वापस fp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
ieee_fpcr_to_swcr(अचिन्हित दीर्घ fp)
अणु
	अचिन्हित दीर्घ sw;
	sw = (fp >> 35) & IEEE_STATUS_MASK;
	sw |= (fp >> 36) & IEEE_MAP_DMZ;
	sw |= (~fp >> 48) & (IEEE_TRAP_ENABLE_INV
			     | IEEE_TRAP_ENABLE_DZE
			     | IEEE_TRAP_ENABLE_OVF);
	sw |= (~fp >> 57) & (IEEE_TRAP_ENABLE_UNF | IEEE_TRAP_ENABLE_INE);
	sw |= (fp >> 47) & IEEE_MAP_UMZ;
	sw |= (~fp >> 41) & IEEE_TRAP_ENABLE_DNO;
	वापस sw;
पूर्ण


#पूर्ण_अगर /* _UAPI__ASM_ALPHA_FPU_H */
