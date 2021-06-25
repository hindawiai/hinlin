<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_BACKOFF_H
#घोषणा _SPARC64_BACKOFF_H

/* The macros in this file implement an exponential backoff facility
 * क्रम atomic operations.
 *
 * When multiple thपढ़ोs compete on an atomic operation, it is
 * possible क्रम one thपढ़ो to be continually denied a successful
 * completion of the compare-and-swap inकाष्ठाion.  Heavily
 * thपढ़ोed cpu implementations like Niagara can compound this
 * problem even further.
 *
 * When an atomic operation fails and needs to be retried, we spin a
 * certain number of बार.  At each subsequent failure of the same
 * operation we द्विगुन the spin count, realizing an exponential
 * backoff.
 *
 * When we spin, we try to use an operation that will cause the
 * current cpu stअक्रम to block, and thereक्रमe make the core fully
 * available to any other runnable stअक्रमs.  There are two
 * options, based upon cpu capabilities.
 *
 * On all cpus prior to SPARC-T4 we करो three dummy पढ़ोs of the
 * condition code रेजिस्टर.  Each पढ़ो blocks the stअक्रम क्रम something
 * between 40 and 50 cpu cycles.
 *
 * For SPARC-T4 and later we have a special "pause" inकाष्ठाion
 * available.  This is implemented using ग_लिखोs to रेजिस्टर %asr27.
 * The cpu will block the number of cycles written पूर्णांकo the रेजिस्टर,
 * unless a disrupting trap happens first.  SPARC-T4 specअगरically
 * implements छोड़ो with a granularity of 8 cycles.  Each stअक्रम has
 * an पूर्णांकernal छोड़ो counter which decrements every 8 cycles.  So the
 * chip shअगरts the %asr27 value करोwn by 3 bits, and ग_लिखोs the result
 * पूर्णांकo the छोड़ो counter.  If a value smaller than 8 is written, the
 * chip blocks क्रम 1 cycle.
 *
 * To achieve the same amount of backoff as the three %ccr पढ़ोs give
 * on earlier chips, we shअगरt the backoff value up by 7 bits.  (Three
 * %ccr पढ़ोs block क्रम about 128 cycles, 1 << 7 == 128) We ग_लिखो the
 * whole amount we want to block पूर्णांकo the छोड़ो रेजिस्टर, rather than
 * loop writing 128 each समय.
 */

#घोषणा BACKOFF_LIMIT	(4 * 1024)

#अगर_घोषित CONFIG_SMP

#घोषणा BACKOFF_SETUP(reg)	\
	mov	1, reg

#घोषणा BACKOFF_LABEL(spin_label, जारी_label) \
	spin_label

#घोषणा BACKOFF_SPIN(reg, पंचांगp, label)		\
	mov		reg, पंचांगp;		\
88:	rd		%ccr, %g0;		\
	rd		%ccr, %g0;		\
	rd		%ccr, %g0;		\
	.section	.छोड़ो_3insn_patch,"ax";\
	.word		88b;			\
	sllx		पंचांगp, 7, पंचांगp;		\
	wr		पंचांगp, 0, %asr27;		\
	clr		पंचांगp;			\
	.previous;				\
	brnz,pt		पंचांगp, 88b;		\
	 sub		पंचांगp, 1, पंचांगp;		\
	set		BACKOFF_LIMIT, पंचांगp;	\
	cmp		reg, पंचांगp;		\
	bg,pn		%xcc, label;		\
	 nop;					\
	ba,pt		%xcc, label;		\
	 sllx		reg, 1, reg;

#अन्यथा

#घोषणा BACKOFF_SETUP(reg)

#घोषणा BACKOFF_LABEL(spin_label, जारी_label) \
	जारी_label

#घोषणा BACKOFF_SPIN(reg, पंचांगp, label)

#पूर्ण_अगर

#पूर्ण_अगर /* _SPARC64_BACKOFF_H */
