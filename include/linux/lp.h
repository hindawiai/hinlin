<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * usr/include/linux/lp.h c.1991-1992 James Wiegand
 * many modअगरications copyright (C) 1992 Michael K. Johnson
 * Interrupt support added 1993 Nigel Gamble
 * Removed 8255 status defines from inside __KERNEL__ Marcelo Tosatti 
 */
#अगर_अघोषित _LINUX_LP_H
#घोषणा _LINUX_LP_H


#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <uapi/linux/lp.h>

/* Magic numbers क्रम defining port-device mappings */
#घोषणा LP_PARPORT_UNSPEC -4
#घोषणा LP_PARPORT_AUTO -3
#घोषणा LP_PARPORT_OFF -2
#घोषणा LP_PARPORT_NONE -1

#घोषणा LP_F(minor)	lp_table[(minor)].flags		/* flags क्रम busy, etc. */
#घोषणा LP_CHAR(minor)	lp_table[(minor)].अक्षरs		/* busy समयout */
#घोषणा LP_TIME(minor)	lp_table[(minor)].समय		/* रुको समय */
#घोषणा LP_WAIT(minor)	lp_table[(minor)].रुको		/* strobe रुको */
#घोषणा LP_IRQ(minor)	lp_table[(minor)].dev->port->irq /* पूर्णांकerrupt # */
					/* PARPORT_IRQ_NONE means polled */
#अगर_घोषित LP_STATS
#घोषणा LP_STAT(minor)	lp_table[(minor)].stats		/* statistics area */
#पूर्ण_अगर
#घोषणा LP_BUFFER_SIZE PAGE_SIZE

#घोषणा LP_BASE(x)	lp_table[(x)].dev->port->base

#अगर_घोषित LP_STATS
काष्ठा lp_stats अणु
	अचिन्हित दीर्घ अक्षरs;
	अचिन्हित दीर्घ sleeps;
	अचिन्हित पूर्णांक maxrun;
	अचिन्हित पूर्णांक maxरुको;
	अचिन्हित पूर्णांक meanरुको;
	अचिन्हित पूर्णांक mdev;
पूर्ण;
#पूर्ण_अगर

काष्ठा lp_काष्ठा अणु
	काष्ठा pardevice *dev;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक अक्षरs;
	अचिन्हित पूर्णांक समय;
	अचिन्हित पूर्णांक रुको;
	अक्षर *lp_buffer;
#अगर_घोषित LP_STATS
	अचिन्हित पूर्णांक lastcall;
	अचिन्हित पूर्णांक runअक्षरs;
	काष्ठा lp_stats stats;
#पूर्ण_अगर
	रुको_queue_head_t रुकोq;
	अचिन्हित पूर्णांक last_error;
	काष्ठा mutex port_mutex;
	रुको_queue_head_t dataq;
	दीर्घ समयout;
	अचिन्हित पूर्णांक best_mode;
	अचिन्हित पूर्णांक current_mode;
	अचिन्हित दीर्घ bits;
पूर्ण;

/*
 * The following स्थिरants describe the various संकेतs of the prपूर्णांकer port
 * hardware.  Note that the hardware inverts some संकेतs and that some
 * संकेतs are active low.  An example is LP_STROBE, which must be programmed
 * with 1 क्रम being active and 0 क्रम being inactive, because the strobe संकेत
 * माला_लो inverted, but it is also active low.
 */


/* 
 * defines क्रम 8255 control port
 * base + 2 
 * accessed with LP_C(minor)
 */
#घोषणा LP_PINTEN	0x10  /* high to पढ़ो data in or-ed with data out */
#घोषणा LP_PSELECP	0x08  /* inverted output, active low */
#घोषणा LP_PINITP	0x04  /* unchanged output, active low */
#घोषणा LP_PAUTOLF	0x02  /* inverted output, active low */
#घोषणा LP_PSTROBE	0x01  /* लघु high output on raising edge */

/* 
 * the value written to ports to test existence. PC-style ports will 
 * वापस the value written. AT-style ports will वापस 0. so why not
 * make them the same ? 
 */
#घोषणा LP_DUMMY	0x00

/*
 * This is the port delay समय, in microseconds.
 * It is used only in the lp_init() and lp_reset() routine.
 */
#घोषणा LP_DELAY 	50

#पूर्ण_अगर
