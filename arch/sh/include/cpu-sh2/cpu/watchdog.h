<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh2/watchकरोg.h
 *
 * Copyright (C) 2002, 2003 Paul Mundt
 */
#अगर_अघोषित __ASM_CPU_SH2_WATCHDOG_H
#घोषणा __ASM_CPU_SH2_WATCHDOG_H

/*
 * More SH-2 brilliance .. its not good enough that we can't पढ़ो
 * and ग_लिखो the same sizes to WTCNT, now we have to पढ़ो and ग_लिखो
 * with dअगरferent sizes at dअगरferent addresses क्रम WTCNT _and_ RSTCSR.
 *
 * At least on the bright side no one has managed to screw over WTCSR
 * in this fashion .. yet.
 */
/* Register definitions */
#घोषणा WTCNT		0xfffffe80
#घोषणा WTCSR		0xfffffe80
#घोषणा RSTCSR		0xfffffe82

#घोषणा WTCNT_R		(WTCNT + 1)
#घोषणा RSTCSR_R	(RSTCSR + 1)

/* Bit definitions */
#घोषणा WTCSR_IOVF	0x80
#घोषणा WTCSR_WT	0x40
#घोषणा WTCSR_TME	0x20
#घोषणा WTCSR_RSTS	0x00

#घोषणा RSTCSR_RSTS	0x20

/**
 * 	sh_wdt_पढ़ो_rstcsr - Read from Reset Control/Status Register
 *
 *	Reads back the RSTCSR value.
 */
अटल अंतरभूत __u8 sh_wdt_पढ़ो_rstcsr(व्योम)
अणु
	/*
	 * Same पढ़ो/ग_लिखो brain-damage as क्रम WTCNT here..
	 */
	वापस __raw_पढ़ोb(RSTCSR_R);
पूर्ण

/**
 * 	sh_wdt_ग_लिखो_csr - Write to Reset Control/Status Register
 *
 * 	@val: Value to ग_लिखो
 *
 * 	Writes the given value @val to the lower byte of the control/status
 * 	रेजिस्टर. The upper byte is set manually on each ग_लिखो.
 */
अटल अंतरभूत व्योम sh_wdt_ग_लिखो_rstcsr(__u8 val)
अणु
	/*
	 * Note: Due to the brain-damaged nature of this रेजिस्टर,
	 * we can't presently touch the WOVF bit, since the upper byte
	 * has to be swapped क्रम this. So just leave it alone..
	 */
	__raw_ग_लिखोb((WTCNT_HIGH << 8) | (__u16)val, RSTCSR);
पूर्ण

#पूर्ण_अगर /* __ASM_CPU_SH2_WATCHDOG_H */

