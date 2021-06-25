<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Sound Cors PDAudioCF soundcard
 *
 * Copyright (c) 2003 by Jaroslav Kysela <perex@perex.cz>
 */

#अगर_अघोषित __PDAUDIOCF_H
#घोषणा __PDAUDIOCF_H

#समावेश <sound/pcm.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश <sound/ak4117.h>

/* PDAUDIOCF रेजिस्टरs */
#घोषणा PDAUDIOCF_REG_MD	0x00	/* music data, R/O */
#घोषणा PDAUDIOCF_REG_WDP	0x02	/* ग_लिखो data poपूर्णांकer / 2, R/O */
#घोषणा PDAUDIOCF_REG_RDP	0x04	/* पढ़ो data poपूर्णांकer / 2, R/O */
#घोषणा PDAUDIOCF_REG_TCR	0x06	/* test control रेजिस्टर W/O */
#घोषणा PDAUDIOCF_REG_SCR	0x08	/* status and control, R/W (see bit description) */
#घोषणा PDAUDIOCF_REG_ISR	0x0a	/* पूर्णांकerrupt status, R/O */
#घोषणा PDAUDIOCF_REG_IER	0x0c	/* पूर्णांकerrupt enable, R/W */
#घोषणा PDAUDIOCF_REG_AK_IFR	0x0e	/* AK पूर्णांकerface रेजिस्टर, R/W */

/* PDAUDIOCF_REG_TCR */
#घोषणा PDAUDIOCF_ELIMAKMBIT	(1<<0)	/* simulate AKM music data */
#घोषणा PDAUDIOCF_TESTDATASEL	(1<<1)	/* test data selection, 0 = 0x55, 1 = pseuकरो-अक्रमom */

/* PDAUDIOCF_REG_SCR */
#घोषणा PDAUDIOCF_AK_SBP	(1<<0)	/* serial port busy flag */
#घोषणा PDAUDIOCF_RST		(1<<2)	/* FPGA, AKM + SRAM buffer reset */
#घोषणा PDAUDIOCF_PDN		(1<<3)	/* घातer करोwn bit */
#घोषणा PDAUDIOCF_CLKDIV0	(1<<4)	/* choose 24.576Mhz घड़ी भागided by 1,2,3 or 4 */
#घोषणा PDAUDIOCF_CLKDIV1	(1<<5)
#घोषणा PDAUDIOCF_RECORD	(1<<6)	/* start capturing to SRAM */
#घोषणा PDAUDIOCF_AK_SDD	(1<<7)	/* music data detected */
#घोषणा PDAUDIOCF_RED_LED_OFF	(1<<8)	/* red LED off override */
#घोषणा PDAUDIOCF_BLUE_LED_OFF	(1<<9)	/* blue LED off override */
#घोषणा PDAUDIOCF_DATAFMT0	(1<<10)	/* data क्रमmat bits: 00 = 16-bit, 01 = 18-bit */
#घोषणा PDAUDIOCF_DATAFMT1	(1<<11)	/* 10 = 20-bit, 11 = 24-bit, all right justअगरied */
#घोषणा PDAUDIOCF_FPGAREV(x)	((x>>12)&0x0f) /* FPGA revision */

/* PDAUDIOCF_REG_ISR */
#घोषणा PDAUDIOCF_IRQLVL	(1<<0)	/* Buffer level IRQ */
#घोषणा PDAUDIOCF_IRQOVR	(1<<1)	/* Overrun IRQ */
#घोषणा PDAUDIOCF_IRQAKM	(1<<2)	/* AKM IRQ */

/* PDAUDIOCF_REG_IER */
#घोषणा PDAUDIOCF_IRQLVLEN0	(1<<0)	/* fill threshold levels; 00 = none, 01 = 1/8th of buffer */
#घोषणा PDAUDIOCF_IRQLVLEN1	(1<<1)	/* 10 = 1/4th of buffer, 11 = 1/2th of buffer */
#घोषणा PDAUDIOCF_IRQOVREN	(1<<2)	/* enable overrun IRQ */
#घोषणा PDAUDIOCF_IRQAKMEN	(1<<3)	/* enable AKM IRQ */
#घोषणा PDAUDIOCF_BLUEDUTY0	(1<<8)	/* blue LED duty cycle; 00 = 100%, 01 = 50% */
#घोषणा PDAUDIOCF_BLUEDUTY1	(1<<9)	/* 02 = 25%, 11 = 12% */
#घोषणा PDAUDIOCF_REDDUTY0	(1<<10)	/* red LED duty cycle; 00 = 100%, 01 = 50% */
#घोषणा PDAUDIOCF_REDDUTY1	(1<<11)	/* 02 = 25%, 11 = 12% */
#घोषणा PDAUDIOCF_BLUESDD	(1<<12)	/* blue LED against SDD bit */
#घोषणा PDAUDIOCF_BLUEMODULATE	(1<<13)	/* save घातer when 100% duty cycle selected */
#घोषणा PDAUDIOCF_REDMODULATE	(1<<14)	/* save घातer when 100% duty cycle selected */
#घोषणा PDAUDIOCF_HALFRATE	(1<<15)	/* slow both LED blinks by half (also spdअगर detect rate) */

/* chip status */
#घोषणा PDAUDIOCF_STAT_IS_STALE	(1<<0)
#घोषणा PDAUDIOCF_STAT_IS_CONFIGURED (1<<1)
#घोषणा PDAUDIOCF_STAT_IS_SUSPENDED (1<<2)

काष्ठा snd_pdacf अणु
	काष्ठा snd_card *card;
	पूर्णांक index;

	अचिन्हित दीर्घ port;
	पूर्णांक irq;

	काष्ठा mutex reg_lock;
	अचिन्हित लघु regmap[8];
	अचिन्हित लघु suspend_reg_scr;

	spinlock_t ak4117_lock;
	काष्ठा ak4117 *ak4117;

	अचिन्हित पूर्णांक chip_status;

	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *pcm_substream;
	अचिन्हित पूर्णांक pcm_running: 1;
	अचिन्हित पूर्णांक pcm_channels;
	अचिन्हित पूर्णांक pcm_swab;
	अचिन्हित पूर्णांक pcm_little;
	अचिन्हित पूर्णांक pcm_frame;
	अचिन्हित पूर्णांक pcm_sample;
	अचिन्हित पूर्णांक pcm_xor;
	अचिन्हित पूर्णांक pcm_size;
	अचिन्हित पूर्णांक pcm_period;
	अचिन्हित पूर्णांक pcm_tकरोne;
	अचिन्हित पूर्णांक pcm_hwptr;
	व्योम *pcm_area;
	
	/* pcmcia stuff */
	काष्ठा pcmcia_device	*p_dev;
पूर्ण;

अटल अंतरभूत व्योम pdacf_reg_ग_लिखो(काष्ठा snd_pdacf *chip, अचिन्हित अक्षर reg, अचिन्हित लघु val)
अणु
	outw(chip->regmap[reg>>1] = val, chip->port + reg);
पूर्ण

अटल अंतरभूत अचिन्हित लघु pdacf_reg_पढ़ो(काष्ठा snd_pdacf *chip, अचिन्हित अक्षर reg)
अणु
	वापस inw(chip->port + reg);
पूर्ण

काष्ठा snd_pdacf *snd_pdacf_create(काष्ठा snd_card *card);
पूर्णांक snd_pdacf_ak4117_create(काष्ठा snd_pdacf *pdacf);
व्योम snd_pdacf_घातerकरोwn(काष्ठा snd_pdacf *chip);
#अगर_घोषित CONFIG_PM
पूर्णांक snd_pdacf_suspend(काष्ठा snd_pdacf *chip);
पूर्णांक snd_pdacf_resume(काष्ठा snd_pdacf *chip);
#पूर्ण_अगर
पूर्णांक snd_pdacf_pcm_new(काष्ठा snd_pdacf *chip);
irqवापस_t pdacf_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev);
irqवापस_t pdacf_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev);
व्योम pdacf_reinit(काष्ठा snd_pdacf *chip, पूर्णांक resume);

#पूर्ण_अगर /* __PDAUDIOCF_H */
