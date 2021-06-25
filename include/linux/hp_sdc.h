<शैली गुरु>
/*
 * HP i8042 System Device Controller -- header
 *
 * Copyright (c) 2001 Brian S. Julin
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *
 * References:
 * 
 * HP-HIL Technical Reference Manual.  Hewlett Packard Product No. 45918A
 *
 * System Device Controller Microprocessor Firmware Theory of Operation
 * 	क्रम Part Number 1820-4784 Revision B.  Dwg No. A-1820-4784-2
 *
 */

#अगर_अघोषित _LINUX_HP_SDC_H
#घोषणा _LINUX_HP_SDC_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#अगर defined(__hppa__)
#समावेश <यंत्र/hardware.h>
#पूर्ण_अगर


/* No 4X status पढ़ोs take दीर्घer than this (in usec).
 */
#घोषणा HP_SDC_MAX_REG_DELAY 20000

प्रकार व्योम (hp_sdc_irqhook) (पूर्णांक irq, व्योम *dev_id, 
			       uपूर्णांक8_t status, uपूर्णांक8_t data);

पूर्णांक hp_sdc_request_समयr_irq(hp_sdc_irqhook *callback);
पूर्णांक hp_sdc_request_hil_irq(hp_sdc_irqhook *callback);
पूर्णांक hp_sdc_request_cooked_irq(hp_sdc_irqhook *callback);
पूर्णांक hp_sdc_release_समयr_irq(hp_sdc_irqhook *callback);
पूर्णांक hp_sdc_release_hil_irq(hp_sdc_irqhook *callback);
पूर्णांक hp_sdc_release_cooked_irq(hp_sdc_irqhook *callback);

प्रकार काष्ठा अणु
	पूर्णांक actidx;	/* Start of act.  Acts are atomic WRT I/O to SDC */
	पूर्णांक idx;	/* Index within the act */
	पूर्णांक endidx;	/* transaction is over and करोne अगर idx == endidx */
	uपूर्णांक8_t *seq;	/* commands/data क्रम the transaction */
	जोड़ अणु
	  hp_sdc_irqhook   *irqhook;	/* Callback, isr or tasklet context */
	  काष्ठा semaphore *semaphore;	/* Semaphore to sleep on. */
	पूर्ण act;
पूर्ण hp_sdc_transaction;
पूर्णांक __hp_sdc_enqueue_transaction(hp_sdc_transaction *this);
पूर्णांक hp_sdc_enqueue_transaction(hp_sdc_transaction *this);
पूर्णांक hp_sdc_dequeue_transaction(hp_sdc_transaction *this);

/* The HP_SDC_ACT* values are peculiar to this driver.
 * Nuance: never HP_SDC_ACT_DATAIN | HP_SDC_ACT_DEALLOC, use another
 * act to perक्रमm the dealloc.
 */
#घोषणा HP_SDC_ACT_PRECMD	0x01		/* Send a command first */
#घोषणा HP_SDC_ACT_DATAREG	0x02		/* Set data रेजिस्टरs */
#घोषणा HP_SDC_ACT_DATAOUT	0x04		/* Send data bytes */
#घोषणा HP_SDC_ACT_POSTCMD      0x08            /* Send command after */
#घोषणा HP_SDC_ACT_DATAIN	0x10		/* Collect data after */
#घोषणा HP_SDC_ACT_DURING	0x1f
#घोषणा HP_SDC_ACT_SEMAPHORE    0x20            /* Raise semaphore after */
#घोषणा HP_SDC_ACT_CALLBACK	0x40		/* Pass data to IRQ handler */
#घोषणा HP_SDC_ACT_DEALLOC	0x80		/* Destroy transaction after */
#घोषणा HP_SDC_ACT_AFTER	0xe0
#घोषणा HP_SDC_ACT_DEAD		0x60		/* Act समयd out. */

/* Rest of the flags are straightक्रमward representation of the SDC पूर्णांकerface */
#घोषणा HP_SDC_STATUS_IBF	0x02	/* Input buffer full */

#घोषणा HP_SDC_STATUS_IRQMASK	0xf0	/* Bits containing "level 1" irq */
#घोषणा HP_SDC_STATUS_PERIODIC  0x10    /* Periodic 10ms समयr */
#घोषणा HP_SDC_STATUS_USERTIMER 0x20    /* "Special purpose" समयr */
#घोषणा HP_SDC_STATUS_TIMER     0x30    /* Both PERIODIC and USERTIMER */
#घोषणा HP_SDC_STATUS_REG	0x40	/* Data from an i8042 रेजिस्टर */
#घोषणा HP_SDC_STATUS_HILCMD    0x50	/* Command from HIL MLC */
#घोषणा HP_SDC_STATUS_HILDATA   0x60	/* Data from HIL MLC */
#घोषणा HP_SDC_STATUS_PUP	0x70	/* Successful घातer-up self test */
#घोषणा HP_SDC_STATUS_KCOOKED	0x80	/* Key from cooked kbd */
#घोषणा HP_SDC_STATUS_KRPG	0xc0	/* Key from Repeat Gen */
#घोषणा HP_SDC_STATUS_KMOD_SUP	0x10	/* Shअगरt key is up */
#घोषणा HP_SDC_STATUS_KMOD_CUP	0x20	/* Control key is up */

#घोषणा HP_SDC_NMISTATUS_FHS	0x40	/* NMI is a fast handshake irq */

/* Internal i8042 रेजिस्टरs (there are more, but they are not too useful). */

#घोषणा HP_SDC_USE		0x02	/* Resource usage (including OB bit) */
#घोषणा HP_SDC_IM		0x04	/* Interrupt mask */
#घोषणा HP_SDC_CFG		0x11	/* Configuration रेजिस्टर */
#घोषणा HP_SDC_KBLANGUAGE	0x12	/* Keyboard language */

#घोषणा HP_SDC_D0		0x70	/* General purpose data buffer 0 */
#घोषणा HP_SDC_D1		0x71	/* General purpose data buffer 1 */
#घोषणा HP_SDC_D2		0x72	/* General purpose data buffer 2 */
#घोषणा HP_SDC_D3		0x73	/* General purpose data buffer 3 */
#घोषणा HP_SDC_VT1		0x74	/* Timer क्रम voice 1 */
#घोषणा HP_SDC_VT2		0x75	/* Timer क्रम voice 2 */
#घोषणा HP_SDC_VT3		0x76	/* Timer क्रम voice 3 */
#घोषणा HP_SDC_VT4		0x77	/* Timer क्रम voice 4 */
#घोषणा HP_SDC_KBN		0x78	/* Which HIL devs are Nimitz */
#घोषणा HP_SDC_KBC		0x79	/* Which HIL devs are cooked kbds */
#घोषणा HP_SDC_LPS		0x7a	/* i8042's view of HIL status */
#घोषणा HP_SDC_LPC		0x7b	/* i8042's view of HIL "control" */
#घोषणा HP_SDC_RSV  		0x7c	/* Reserved "for testing" */
#घोषणा HP_SDC_LPR		0x7d    /* i8042 count of HIL reconfigs */
#घोषणा HP_SDC_XTD		0x7e    /* "Extended Configuration" रेजिस्टर */
#घोषणा HP_SDC_STR		0x7f    /* i8042 self-test result */

/* Bitfields क्रम above रेजिस्टरs */
#घोषणा HP_SDC_USE_LOOP		0x04	/* Command is currently on the loop. */

#घोषणा HP_SDC_IM_MASK          0x1f    /* these bits not part of cmd/status */
#घोषणा HP_SDC_IM_FH		0x10	/* Mask the fast handshake irq */
#घोषणा HP_SDC_IM_PT		0x08	/* Mask the periodic समयr irq */
#घोषणा HP_SDC_IM_TIMERS	0x04	/* Mask the MT/DT/CT irq */
#घोषणा HP_SDC_IM_RESET		0x02	/* Mask the reset key irq */
#घोषणा HP_SDC_IM_HIL		0x01	/* Mask the HIL MLC irq */

#घोषणा HP_SDC_CFG_ROLLOVER	0x08	/* WTF is "N-key rollover"? */
#घोषणा HP_SDC_CFG_KBD		0x10	/* There is a keyboard */
#घोषणा HP_SDC_CFG_NEW		0x20	/* Supports/uses HIL MLC */
#घोषणा HP_SDC_CFG_KBD_OLD	0x03	/* keyboard code क्रम non-HIL */
#घोषणा HP_SDC_CFG_KBD_NEW	0x07	/* keyboard code from HIL स्वतःconfig */
#घोषणा HP_SDC_CFG_REV		0x40	/* Code revision bit */
#घोषणा HP_SDC_CFG_IDPROM	0x80	/* IDPROM present in kbd (not HIL) */

#घोषणा HP_SDC_LPS_NDEV		0x07	/* # devices स्वतःconfigured on HIL */
#घोषणा HP_SDC_LPS_ACSUCC	0x08	/* loop स्वतःconfigured successfully */
#घोषणा HP_SDC_LPS_ACFAIL	0x80	/* last loop स्वतःconfigure failed */

#घोषणा HP_SDC_LPC_APE_IPF	0x01	/* HIL MLC APE/IPF (स्वतःpoll) set */
#घोषणा HP_SDC_LPC_ARCONERR	0x02	/* i8042 स्वतःreconfigs loop on err */
#घोषणा HP_SDC_LPC_ARCQUIET	0x03	/* i8042 करोesn't report स्वतःreconfigs*/
#घोषणा HP_SDC_LPC_COOK		0x10	/* i8042 cooks devices in _KBN */
#घोषणा HP_SDC_LPC_RC		0x80	/* causes स्वतःreconfig */

#घोषणा HP_SDC_XTD_REV		0x07	/* contains revision code */
#घोषणा HP_SDC_XTD_REV_STRINGS(val, str) \
चयन (val) अणु						\
	हाल 0x1: str = "1820-3712"; अवरोध;		\
	हाल 0x2: str = "1820-4379"; अवरोध;		\
	हाल 0x3: str = "1820-4784"; अवरोध;		\
	शेष: str = "unknown";			\
पूर्ण;
#घोषणा HP_SDC_XTD_BEEPER	0x08	/* TI SN76494 beeper available */
#घोषणा HP_SDC_XTD_BBRTC	0x20	/* OKI MSM-58321 BBRTC present */

#घोषणा HP_SDC_CMD_LOAD_RT	0x31	/* Load real समय (from 8042) */
#घोषणा HP_SDC_CMD_LOAD_FHS	0x36	/* Load the fast handshake समयr */
#घोषणा HP_SDC_CMD_LOAD_MT	0x38	/* Load the match समयr */
#घोषणा HP_SDC_CMD_LOAD_DT	0x3B	/* Load the delay समयr */
#घोषणा HP_SDC_CMD_LOAD_CT	0x3E	/* Load the cycle समयr */

#घोषणा HP_SDC_CMD_SET_IM	0x40    /* 010xxxxx == set irq mask */

/* The करोcuments provided करो not explicitly state that all रेजिस्टरs betweem 
 * 0x01 and 0x1f inclusive can be पढ़ो by sending their रेजिस्टर index as a 
 * command, but this is implied and appears to be the हाल.
 */
#घोषणा HP_SDC_CMD_READ_RAM	0x00	/* Load from i8042 RAM (स्वतःinc) */
#घोषणा HP_SDC_CMD_READ_USE	0x02	/* Unकरोcumented! Load from usage reg */
#घोषणा HP_SDC_CMD_READ_IM	0x04	/* Load current पूर्णांकerrupt mask */
#घोषणा HP_SDC_CMD_READ_KCC	0x11	/* Load primary kbd config code */
#घोषणा HP_SDC_CMD_READ_KLC	0x12	/* Load primary kbd language code */
#घोषणा HP_SDC_CMD_READ_T1	0x13	/* Load समयr output buffer byte 1 */
#घोषणा HP_SDC_CMD_READ_T2	0x14	/* Load समयr output buffer byte 1 */
#घोषणा HP_SDC_CMD_READ_T3	0x15	/* Load समयr output buffer byte 1 */
#घोषणा HP_SDC_CMD_READ_T4	0x16	/* Load समयr output buffer byte 1 */
#घोषणा HP_SDC_CMD_READ_T5	0x17	/* Load समयr output buffer byte 1 */
#घोषणा HP_SDC_CMD_READ_D0	0xf0	/* Load from i8042 RAM location 0x70 */
#घोषणा HP_SDC_CMD_READ_D1	0xf1	/* Load from i8042 RAM location 0x71 */
#घोषणा HP_SDC_CMD_READ_D2	0xf2	/* Load from i8042 RAM location 0x72 */
#घोषणा HP_SDC_CMD_READ_D3	0xf3	/* Load from i8042 RAM location 0x73 */
#घोषणा HP_SDC_CMD_READ_VT1	0xf4	/* Load from i8042 RAM location 0x74 */
#घोषणा HP_SDC_CMD_READ_VT2	0xf5	/* Load from i8042 RAM location 0x75 */
#घोषणा HP_SDC_CMD_READ_VT3	0xf6	/* Load from i8042 RAM location 0x76 */
#घोषणा HP_SDC_CMD_READ_VT4	0xf7	/* Load from i8042 RAM location 0x77 */
#घोषणा HP_SDC_CMD_READ_KBN	0xf8	/* Load from i8042 RAM location 0x78 */
#घोषणा HP_SDC_CMD_READ_KBC	0xf9	/* Load from i8042 RAM location 0x79 */
#घोषणा HP_SDC_CMD_READ_LPS	0xfa	/* Load from i8042 RAM location 0x7a */
#घोषणा HP_SDC_CMD_READ_LPC	0xfb	/* Load from i8042 RAM location 0x7b */
#घोषणा HP_SDC_CMD_READ_RSV	0xfc	/* Load from i8042 RAM location 0x7c */
#घोषणा HP_SDC_CMD_READ_LPR	0xfd	/* Load from i8042 RAM location 0x7d */
#घोषणा HP_SDC_CMD_READ_XTD	0xfe	/* Load from i8042 RAM location 0x7e */
#घोषणा HP_SDC_CMD_READ_STR	0xff	/* Load from i8042 RAM location 0x7f */

#घोषणा HP_SDC_CMD_SET_ARD	0xA0	/* Set emulated स्वतःrepeat delay */
#घोषणा HP_SDC_CMD_SET_ARR	0xA2	/* Set emulated स्वतःrepeat rate */
#घोषणा HP_SDC_CMD_SET_BELL	0xA3	/* Set voice 3 params क्रम "beep" cmd */
#घोषणा HP_SDC_CMD_SET_RPGR	0xA6	/* Set "RPG" irq rate (करोesn't work) */
#घोषणा HP_SDC_CMD_SET_RTMS	0xAD	/* Set the RTC समय (milliseconds) */
#घोषणा HP_SDC_CMD_SET_RTD	0xAF	/* Set the RTC समय (days) */
#घोषणा HP_SDC_CMD_SET_FHS	0xB2	/* Set fast handshake समयr */
#घोषणा HP_SDC_CMD_SET_MT	0xB4	/* Set match समयr */
#घोषणा HP_SDC_CMD_SET_DT	0xB7	/* Set delay समयr */
#घोषणा HP_SDC_CMD_SET_CT	0xBA	/* Set cycle समयr */
#घोषणा HP_SDC_CMD_SET_RAMP	0xC1	/* Reset READ_RAM स्वतःinc counter */
#घोषणा HP_SDC_CMD_SET_D0	0xe0	/* Load to i8042 RAM location 0x70 */
#घोषणा HP_SDC_CMD_SET_D1	0xe1	/* Load to i8042 RAM location 0x71 */
#घोषणा HP_SDC_CMD_SET_D2	0xe2	/* Load to i8042 RAM location 0x72 */
#घोषणा HP_SDC_CMD_SET_D3	0xe3	/* Load to i8042 RAM location 0x73 */
#घोषणा HP_SDC_CMD_SET_VT1	0xe4	/* Load to i8042 RAM location 0x74 */
#घोषणा HP_SDC_CMD_SET_VT2	0xe5	/* Load to i8042 RAM location 0x75 */
#घोषणा HP_SDC_CMD_SET_VT3	0xe6	/* Load to i8042 RAM location 0x76 */
#घोषणा HP_SDC_CMD_SET_VT4	0xe7	/* Load to i8042 RAM location 0x77 */
#घोषणा HP_SDC_CMD_SET_KBN	0xe8	/* Load to i8042 RAM location 0x78 */
#घोषणा HP_SDC_CMD_SET_KBC	0xe9	/* Load to i8042 RAM location 0x79 */
#घोषणा HP_SDC_CMD_SET_LPS	0xea	/* Load to i8042 RAM location 0x7a */
#घोषणा HP_SDC_CMD_SET_LPC	0xeb	/* Load to i8042 RAM location 0x7b */
#घोषणा HP_SDC_CMD_SET_RSV	0xec	/* Load to i8042 RAM location 0x7c */
#घोषणा HP_SDC_CMD_SET_LPR	0xed	/* Load to i8042 RAM location 0x7d */
#घोषणा HP_SDC_CMD_SET_XTD	0xee	/* Load to i8042 RAM location 0x7e */
#घोषणा HP_SDC_CMD_SET_STR	0xef	/* Load to i8042 RAM location 0x7f */

#घोषणा HP_SDC_CMD_DO_RTCW	0xc2	/* i8042 RAM 0x70 --> RTC */
#घोषणा HP_SDC_CMD_DO_RTCR	0xc3	/* RTC[0x70 0:3] --> irq/status/data */
#घोषणा HP_SDC_CMD_DO_BEEP	0xc4	/* i8042 RAM 0x70-74  --> beeper,VT3 */
#घोषणा HP_SDC_CMD_DO_HIL	0xc5	/* i8042 RAM 0x70-73 --> 
					   HIL MLC R0,R1 i8042 HIL watchकरोg */

/* Values used to (de)mangle input/output to/from the HIL MLC */
#घोषणा HP_SDC_DATA		0x40	/* Data from an 8042 रेजिस्टर */
#घोषणा HP_SDC_HIL_CMD		0x50	/* Data from HIL MLC R1/8042 */
#घोषणा HP_SDC_HIL_R1MASK	0x0f	/* Contents of HIL MLC R1 0:3 */
#घोषणा HP_SDC_HIL_AUTO		0x10	/* Set अगर POL results from i8042 */   
#घोषणा HP_SDC_HIL_ISERR	0x80	/* Has meaning as in next 4 values */
#घोषणा HP_SDC_HIL_RC_DONE	0x80	/* i8042 स्वतः-configured loop */
#घोषणा HP_SDC_HIL_ERR		0x81	/* HIL MLC R2 had a bit set */
#घोषणा HP_SDC_HIL_TO		0x82	/* i8042 HIL watchकरोg expired */
#घोषणा HP_SDC_HIL_RC		0x84	/* i8042 is स्वतः-configuring loop */
#घोषणा HP_SDC_HIL_DAT		0x60	/* Data from HIL MLC R0 */


प्रकार काष्ठा अणु
	rwlock_t	ibf_lock;
	rwlock_t	lock;		/* user/tasklet lock */
	rwlock_t	rtq_lock;	/* isr/tasklet lock */
	rwlock_t	hook_lock;	/* isr/user lock क्रम handler add/del */

	अचिन्हित पूर्णांक	irq, nmi;	/* Our IRQ lines */
	अचिन्हित दीर्घ	base_io, status_io, data_io; /* Our IO ports */

	uपूर्णांक8_t		im;		/* Interrupt mask */
	पूर्णांक		set_im; 	/* Interrupt mask needs to be set. */

	पूर्णांक		ibf;		/* Last known status of IBF flag */
	uपूर्णांक8_t		wi;		/* current i8042 ग_लिखो index */
	uपूर्णांक8_t		r7[4];          /* current i8042[0x70 - 0x74] values */
	uपूर्णांक8_t		r11, r7e;	/* Values from version/revision regs */

	hp_sdc_irqhook	*समयr, *reg, *hil, *pup, *cooked;

#घोषणा HP_SDC_QUEUE_LEN 16
	hp_sdc_transaction *tq[HP_SDC_QUEUE_LEN]; /* All pending पढ़ो/ग_लिखोs */

	पूर्णांक		rcurr, rqty;	/* Current पढ़ो transact in process */
	kसमय_प्रकार		rसमय;		/* Time when current पढ़ो started */
	पूर्णांक		wcurr;		/* Current ग_लिखो transact in process */

	पूर्णांक		dev_err;	/* carries status from registration */
#अगर defined(__hppa__)
	काष्ठा parisc_device	*dev;
#या_अगर defined(__mc68000__)
	व्योम		*dev;
#अन्यथा
#त्रुटि No support क्रम device registration on this arch yet.
#पूर्ण_अगर

	काष्ठा समयr_list kicker;	/* Keeps below task alive */
	काष्ठा tasklet_काष्ठा	task;

पूर्ण hp_i8042_sdc;

#पूर्ण_अगर /* _LINUX_HP_SDC_H */
