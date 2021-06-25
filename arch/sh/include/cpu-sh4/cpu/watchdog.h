<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh4/watchकरोg.h
 *
 * Copyright (C) 2002, 2003 Paul Mundt
 * Copyright (C) 2009 Siemens AG
 * Copyright (C) 2009 Sitdikov Valentin
 */
#अगर_अघोषित __ASM_CPU_SH4_WATCHDOG_H
#घोषणा __ASM_CPU_SH4_WATCHDOG_H

#अगर defined(CONFIG_CPU_SUBTYPE_SH7785) || defined(CONFIG_CPU_SUBTYPE_SH7780)
/* Prefix definition */
#घोषणा WTBST_HIGH	0x55
/* Register definitions */
#घोषणा WTCNT_R		0xffcc0010 /*WDTCNT*/
#घोषणा WTCSR		0xffcc0004 /*WDTCSR*/
#घोषणा WTCNT		0xffcc0000 /*WDTST*/
#घोषणा WTST		WTCNT
#घोषणा WTBST		0xffcc0008 /*WDTBST*/
/* Register definitions */
#या_अगर	defined(CONFIG_CPU_SUBTYPE_SH7722) || \
	defined(CONFIG_CPU_SUBTYPE_SH7723) || \
	defined(CONFIG_CPU_SUBTYPE_SH7724)
#घोषणा WTCNT		0xa4520000
#घोषणा WTCSR		0xa4520004
#अन्यथा
/* Register definitions */
#घोषणा WTCNT		0xffc00008
#घोषणा WTCSR		0xffc0000c
#पूर्ण_अगर

/* Bit definitions */
#घोषणा WTCSR_TME	0x80
#घोषणा WTCSR_WT	0x40
#घोषणा WTCSR_RSTS	0x20
#घोषणा WTCSR_WOVF	0x10
#घोषणा WTCSR_IOVF	0x08

#पूर्ण_अगर /* __ASM_CPU_SH4_WATCHDOG_H */

