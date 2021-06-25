<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+
 *
 * include/यंत्र-sh/watchकरोg.h
 *
 * Copyright (C) 2002, 2003 Paul Mundt
 * Copyright (C) 2009 Siemens AG
 * Copyright (C) 2009 Valentin Sitdikov
 */
#अगर_अघोषित __ASM_SH_WATCHDOG_H
#घोषणा __ASM_SH_WATCHDOG_H

#समावेश <linux/types.h>
#समावेश <linux/पन.स>

#घोषणा WTCNT_HIGH	0x5a
#घोषणा WTCSR_HIGH	0xa5

#घोषणा WTCSR_CKS2	0x04
#घोषणा WTCSR_CKS1	0x02
#घोषणा WTCSR_CKS0	0x01

#समावेश <cpu/watchकरोg.h>

/*
 * See cpu-sh2/watchकरोg.h क्रम explanation of this stupidity..
 */
#अगर_अघोषित WTCNT_R
#  define WTCNT_R	WTCNT
#पूर्ण_अगर

#अगर_अघोषित WTCSR_R
#  define WTCSR_R	WTCSR
#पूर्ण_अगर

/*
 * CKS0-2 supports a number of घड़ी भागision ratios. At the समय the watchकरोg
 * is enabled, it शेषs to a 41 usec overflow period .. we overload this to
 * something a little more reasonable, and really can't deal with anything
 * lower than WTCSR_CKS_1024, अन्यथा we drop back पूर्णांकo the usec range.
 *
 * Clock Division Ratio         Overflow Period
 * --------------------------------------------
 *     1/32 (initial value)       41 usecs
 *     1/64                       82 usecs
 *     1/128                     164 usecs
 *     1/256                     328 usecs
 *     1/512                     656 usecs
 *     1/1024                   1.31 msecs
 *     1/2048                   2.62 msecs
 *     1/4096                   5.25 msecs
 */
#घोषणा WTCSR_CKS_32	0x00
#घोषणा WTCSR_CKS_64	0x01
#घोषणा WTCSR_CKS_128	0x02
#घोषणा WTCSR_CKS_256	0x03
#घोषणा WTCSR_CKS_512	0x04
#घोषणा WTCSR_CKS_1024	0x05
#घोषणा WTCSR_CKS_2048	0x06
#घोषणा WTCSR_CKS_4096	0x07

#अगर defined(CONFIG_CPU_SUBTYPE_SH7785) || defined(CONFIG_CPU_SUBTYPE_SH7780)
/**
 * 	sh_wdt_पढ़ो_cnt - Read from Counter
 * 	Reads back the WTCNT value.
 */
अटल अंतरभूत __u32 sh_wdt_पढ़ो_cnt(व्योम)
अणु
	वापस __raw_पढ़ोl(WTCNT_R);
पूर्ण

/**
 *	sh_wdt_ग_लिखो_cnt - Write to Counter
 *	@val: Value to ग_लिखो
 *
 *	Writes the given value @val to the lower byte of the समयr counter.
 *	The upper byte is set manually on each ग_लिखो.
 */
अटल अंतरभूत व्योम sh_wdt_ग_लिखो_cnt(__u32 val)
अणु
	__raw_ग_लिखोl((WTCNT_HIGH << 24) | (__u32)val, WTCNT);
पूर्ण

/**
 *	sh_wdt_ग_लिखो_bst - Write to Counter
 *	@val: Value to ग_लिखो
 *
 *	Writes the given value @val to the lower byte of the समयr counter.
 *	The upper byte is set manually on each ग_लिखो.
 */
अटल अंतरभूत व्योम sh_wdt_ग_लिखो_bst(__u32 val)
अणु
	__raw_ग_लिखोl((WTBST_HIGH << 24) | (__u32)val, WTBST);
पूर्ण
/**
 * 	sh_wdt_पढ़ो_csr - Read from Control/Status Register
 *
 *	Reads back the WTCSR value.
 */
अटल अंतरभूत __u32 sh_wdt_पढ़ो_csr(व्योम)
अणु
	वापस __raw_पढ़ोl(WTCSR_R);
पूर्ण

/**
 * 	sh_wdt_ग_लिखो_csr - Write to Control/Status Register
 * 	@val: Value to ग_लिखो
 *
 * 	Writes the given value @val to the lower byte of the control/status
 * 	रेजिस्टर. The upper byte is set manually on each ग_लिखो.
 */
अटल अंतरभूत व्योम sh_wdt_ग_लिखो_csr(__u32 val)
अणु
	__raw_ग_लिखोl((WTCSR_HIGH << 24) | (__u32)val, WTCSR);
पूर्ण
#अन्यथा
/**
 * 	sh_wdt_पढ़ो_cnt - Read from Counter
 * 	Reads back the WTCNT value.
 */
अटल अंतरभूत __u8 sh_wdt_पढ़ो_cnt(व्योम)
अणु
	वापस __raw_पढ़ोb(WTCNT_R);
पूर्ण

/**
 *	sh_wdt_ग_लिखो_cnt - Write to Counter
 *	@val: Value to ग_लिखो
 *
 *	Writes the given value @val to the lower byte of the समयr counter.
 *	The upper byte is set manually on each ग_लिखो.
 */
अटल अंतरभूत व्योम sh_wdt_ग_लिखो_cnt(__u8 val)
अणु
	__raw_ग_लिखोw((WTCNT_HIGH << 8) | (__u16)val, WTCNT);
पूर्ण

/**
 * 	sh_wdt_पढ़ो_csr - Read from Control/Status Register
 *
 *	Reads back the WTCSR value.
 */
अटल अंतरभूत __u8 sh_wdt_पढ़ो_csr(व्योम)
अणु
	वापस __raw_पढ़ोb(WTCSR_R);
पूर्ण

/**
 * 	sh_wdt_ग_लिखो_csr - Write to Control/Status Register
 * 	@val: Value to ग_लिखो
 *
 * 	Writes the given value @val to the lower byte of the control/status
 * 	रेजिस्टर. The upper byte is set manually on each ग_लिखो.
 */
अटल अंतरभूत व्योम sh_wdt_ग_लिखो_csr(__u8 val)
अणु
	__raw_ग_लिखोw((WTCSR_HIGH << 8) | (__u16)val, WTCSR);
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_SUBTYPE_SH7785 || CONFIG_CPU_SUBTYPE_SH7780 */
#पूर्ण_अगर /* __ASM_SH_WATCHDOG_H */
