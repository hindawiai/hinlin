<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Sound Core PDAudioCF soundcard
 *
 * Copyright (c) 2003 by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश "pdaudiocf.h"
#समावेश <sound/initval.h>

/*
 *
 */
अटल अचिन्हित अक्षर pdacf_ak4117_पढ़ो(व्योम *निजी_data, अचिन्हित अक्षर reg)
अणु
	काष्ठा snd_pdacf *chip = निजी_data;
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर res;

	spin_lock_irqsave(&chip->ak4117_lock, flags);
	समयout = 1000;
	जबतक (pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_SCR) & PDAUDIOCF_AK_SBP) अणु
		udelay(5);
		अगर (--समयout == 0) अणु
			spin_unlock_irqrestore(&chip->ak4117_lock, flags);
			snd_prपूर्णांकk(KERN_ERR "AK4117 ready timeout (read)\n");
			वापस 0;
		पूर्ण
	पूर्ण
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_AK_IFR, (u16)reg << 8);
	समयout = 1000;
	जबतक (pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_SCR) & PDAUDIOCF_AK_SBP) अणु
		udelay(5);
		अगर (--समयout == 0) अणु
			spin_unlock_irqrestore(&chip->ak4117_lock, flags);
			snd_prपूर्णांकk(KERN_ERR "AK4117 read timeout (read2)\n");
			वापस 0;
		पूर्ण
	पूर्ण
	res = (अचिन्हित अक्षर)pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_AK_IFR);
	spin_unlock_irqrestore(&chip->ak4117_lock, flags);
	वापस res;
पूर्ण

अटल व्योम pdacf_ak4117_ग_लिखो(व्योम *निजी_data, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	काष्ठा snd_pdacf *chip = निजी_data;
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->ak4117_lock, flags);
	समयout = 1000;
	जबतक (inw(chip->port + PDAUDIOCF_REG_SCR) & PDAUDIOCF_AK_SBP) अणु
		udelay(5);
		अगर (--समयout == 0) अणु
			spin_unlock_irqrestore(&chip->ak4117_lock, flags);
			snd_prपूर्णांकk(KERN_ERR "AK4117 ready timeout (write)\n");
			वापस;
		पूर्ण
	पूर्ण
	outw((u16)reg << 8 | val | (1<<13), chip->port + PDAUDIOCF_REG_AK_IFR);
	spin_unlock_irqrestore(&chip->ak4117_lock, flags);
पूर्ण

#अगर 0
व्योम pdacf_dump(काष्ठा snd_pdacf *chip)
अणु
	prपूर्णांकk(KERN_DEBUG "PDAUDIOCF DUMP (0x%lx):\n", chip->port);
	prपूर्णांकk(KERN_DEBUG "WPD         : 0x%x\n",
	       inw(chip->port + PDAUDIOCF_REG_WDP));
	prपूर्णांकk(KERN_DEBUG "RDP         : 0x%x\n",
	       inw(chip->port + PDAUDIOCF_REG_RDP));
	prपूर्णांकk(KERN_DEBUG "TCR         : 0x%x\n",
	       inw(chip->port + PDAUDIOCF_REG_TCR));
	prपूर्णांकk(KERN_DEBUG "SCR         : 0x%x\n",
	       inw(chip->port + PDAUDIOCF_REG_SCR));
	prपूर्णांकk(KERN_DEBUG "ISR         : 0x%x\n",
	       inw(chip->port + PDAUDIOCF_REG_ISR));
	prपूर्णांकk(KERN_DEBUG "IER         : 0x%x\n",
	       inw(chip->port + PDAUDIOCF_REG_IER));
	prपूर्णांकk(KERN_DEBUG "AK_IFR      : 0x%x\n",
	       inw(chip->port + PDAUDIOCF_REG_AK_IFR));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pdacf_reset(काष्ठा snd_pdacf *chip, पूर्णांक घातerकरोwn)
अणु
	u16 val;
	
	val = pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_SCR);
	val |= PDAUDIOCF_PDN;
	val &= ~PDAUDIOCF_RECORD;		/* क्रम sure */
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, val);
	udelay(5);
	val |= PDAUDIOCF_RST;
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, val);
	udelay(200);
	val &= ~PDAUDIOCF_RST;
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, val);
	udelay(5);
	अगर (!घातerकरोwn) अणु
		val &= ~PDAUDIOCF_PDN;
		pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, val);
		udelay(200);
	पूर्ण
	वापस 0;
पूर्ण

व्योम pdacf_reinit(काष्ठा snd_pdacf *chip, पूर्णांक resume)
अणु
	pdacf_reset(chip, 0);
	अगर (resume)
		pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, chip->suspend_reg_scr);
	snd_ak4117_reinit(chip->ak4117);
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_TCR, chip->regmap[PDAUDIOCF_REG_TCR>>1]);
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_IER, chip->regmap[PDAUDIOCF_REG_IER>>1]);
पूर्ण

अटल व्योम pdacf_proc_पढ़ो(काष्ठा snd_info_entry * entry,
                            काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pdacf *chip = entry->निजी_data;
	u16 पंचांगp;

	snd_iम_लिखो(buffer, "PDAudioCF\n\n");
	पंचांगp = pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_SCR);
	snd_iम_लिखो(buffer, "FPGA revision      : 0x%x\n", PDAUDIOCF_FPGAREV(पंचांगp));
	                                   
पूर्ण

अटल व्योम pdacf_proc_init(काष्ठा snd_pdacf *chip)
अणु
	snd_card_ro_proc_new(chip->card, "pdaudiocf", chip, pdacf_proc_पढ़ो);
पूर्ण

काष्ठा snd_pdacf *snd_pdacf_create(काष्ठा snd_card *card)
अणु
	काष्ठा snd_pdacf *chip;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस शून्य;
	chip->card = card;
	mutex_init(&chip->reg_lock);
	spin_lock_init(&chip->ak4117_lock);
	card->निजी_data = chip;

	pdacf_proc_init(chip);
	वापस chip;
पूर्ण

अटल व्योम snd_pdacf_ak4117_change(काष्ठा ak4117 *ak4117, अचिन्हित अक्षर c0, अचिन्हित अक्षर c1)
अणु
	काष्ठा snd_pdacf *chip = ak4117->change_callback_निजी;
	u16 val;

	अगर (!(c0 & AK4117_UNLCK))
		वापस;
	mutex_lock(&chip->reg_lock);
	val = chip->regmap[PDAUDIOCF_REG_SCR>>1];
	अगर (ak4117->rcs0 & AK4117_UNLCK)
		val |= PDAUDIOCF_BLUE_LED_OFF;
	अन्यथा
		val &= ~PDAUDIOCF_BLUE_LED_OFF;
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, val);
	mutex_unlock(&chip->reg_lock);
पूर्ण

पूर्णांक snd_pdacf_ak4117_create(काष्ठा snd_pdacf *chip)
अणु
	पूर्णांक err;
	u16 val;
	/* design note: अगर we unmask PLL unlock, parity, valid, audio or स्वतः bit पूर्णांकerrupts */
	/* from AK4117 then INT1 pin from AK4117 will be high all समय, because PCMCIA पूर्णांकerrupts are */
	/* egde based and FPGA करोes logical OR क्रम all पूर्णांकerrupt sources, we cannot use these */
	/* high-rate sources */
	अटल स्थिर अचिन्हित अक्षर pgm[5] = अणु
		AK4117_XTL_24_576M | AK4117_EXCT,				/* AK4117_REG_PWRDN */
		AK4117_CM_PLL_XTAL | AK4117_PKCS_128fs | AK4117_XCKS_128fs,	/* AK4117_REQ_CLOCK */
		AK4117_EFH_1024LRCLK | AK4117_DIF_24R | AK4117_IPS,		/* AK4117_REG_IO */
		0xff,								/* AK4117_REG_INT0_MASK */
		AK4117_MAUTO | AK4117_MAUD | AK4117_MULK | AK4117_MPAR | AK4117_MV, /* AK4117_REG_INT1_MASK */
	पूर्ण;

	err = pdacf_reset(chip, 0);
	अगर (err < 0)
		वापस err;
	err = snd_ak4117_create(chip->card, pdacf_ak4117_पढ़ो, pdacf_ak4117_ग_लिखो, pgm, chip, &chip->ak4117);
	अगर (err < 0)
		वापस err;

	val = pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_TCR);
#अगर 1 /* normal operation */
	val &= ~(PDAUDIOCF_ELIMAKMBIT|PDAUDIOCF_TESTDATASEL);
#अन्यथा /* debug */
	val |= PDAUDIOCF_ELIMAKMBIT;
	val &= ~PDAUDIOCF_TESTDATASEL;
#पूर्ण_अगर
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_TCR, val);
	
	/* setup the FPGA to match AK4117 setup */
	val = pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_SCR);
	val &= ~(PDAUDIOCF_CLKDIV0 | PDAUDIOCF_CLKDIV1);		/* use 24.576Mhz घड़ी */
	val &= ~(PDAUDIOCF_RED_LED_OFF|PDAUDIOCF_BLUE_LED_OFF);
	val |= PDAUDIOCF_DATAFMT0 | PDAUDIOCF_DATAFMT1;			/* 24-bit data */
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, val);

	/* setup LEDs and IRQ */
	val = pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_IER);
	val &= ~(PDAUDIOCF_IRQLVLEN0 | PDAUDIOCF_IRQLVLEN1);
	val &= ~(PDAUDIOCF_BLUEDUTY0 | PDAUDIOCF_REDDUTY0 | PDAUDIOCF_REDDUTY1);
	val |= PDAUDIOCF_BLUEDUTY1 | PDAUDIOCF_HALFRATE;
	val |= PDAUDIOCF_IRQOVREN | PDAUDIOCF_IRQAKMEN;
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_IER, val);

	chip->ak4117->change_callback_निजी = chip;
	chip->ak4117->change_callback = snd_pdacf_ak4117_change;

	/* update LED status */
	snd_pdacf_ak4117_change(chip->ak4117, AK4117_UNLCK, 0);

	वापस 0;
पूर्ण

व्योम snd_pdacf_घातerकरोwn(काष्ठा snd_pdacf *chip)
अणु
	u16 val;

	val = pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_SCR);
	chip->suspend_reg_scr = val;
	val |= PDAUDIOCF_RED_LED_OFF | PDAUDIOCF_BLUE_LED_OFF;
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, val);
	/* disable पूर्णांकerrupts, but use direct ग_लिखो to preserve old रेजिस्टर value in chip->regmap */
	val = inw(chip->port + PDAUDIOCF_REG_IER);
	val &= ~(PDAUDIOCF_IRQOVREN|PDAUDIOCF_IRQAKMEN|PDAUDIOCF_IRQLVLEN0|PDAUDIOCF_IRQLVLEN1);
	outw(val, chip->port + PDAUDIOCF_REG_IER);
	pdacf_reset(chip, 1);
पूर्ण

#अगर_घोषित CONFIG_PM

पूर्णांक snd_pdacf_suspend(काष्ठा snd_pdacf *chip)
अणु
	u16 val;
	
	snd_घातer_change_state(chip->card, SNDRV_CTL_POWER_D3hot);
	/* disable पूर्णांकerrupts, but use direct ग_लिखो to preserve old रेजिस्टर value in chip->regmap */
	val = inw(chip->port + PDAUDIOCF_REG_IER);
	val &= ~(PDAUDIOCF_IRQOVREN|PDAUDIOCF_IRQAKMEN|PDAUDIOCF_IRQLVLEN0|PDAUDIOCF_IRQLVLEN1);
	outw(val, chip->port + PDAUDIOCF_REG_IER);
	chip->chip_status |= PDAUDIOCF_STAT_IS_SUSPENDED;	/* ignore पूर्णांकerrupts from now */
	snd_pdacf_घातerकरोwn(chip);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_संकेत(काष्ठा snd_pdacf *chip)
अणु
	वापस (chip->ak4117->rcs0 & AK4117_UNLCK) == 0;
पूर्ण

पूर्णांक snd_pdacf_resume(काष्ठा snd_pdacf *chip)
अणु
	पूर्णांक समयout = 40;

	pdacf_reinit(chip, 1);
	/* रुको क्रम AK4117's PLL */
	जबतक (समयout-- > 0 &&
	       (snd_ak4117_बाह्यal_rate(chip->ak4117) <= 0 || !check_संकेत(chip)))
		mdelay(1);
	chip->chip_status &= ~PDAUDIOCF_STAT_IS_SUSPENDED;
	snd_घातer_change_state(chip->card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर
