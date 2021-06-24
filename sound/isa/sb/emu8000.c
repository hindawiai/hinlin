<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *     and (c) 1999 Steve Ratclअगरfe <steve@parabola.demon.co.uk>
 *  Copyright (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Routines क्रम control of EMU8000 chip
 */

#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/emu8000.h>
#समावेश <sound/emu8000_reg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>

/*
 * emu8000 रेजिस्टर controls
 */

/*
 * The following routines पढ़ो and ग_लिखो रेजिस्टरs on the emu8000.  They
 * should always be called via the EMU8000*READ/WRITE macros and never
 * directly.  The macros handle the port number and command word.
 */
/* Write a word */
व्योम snd_emu8000_poke(काष्ठा snd_emu8000 *emu, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&emu->reg_lock, flags);
	अगर (reg != emu->last_reg) अणु
		outw((अचिन्हित लघु)reg, EMU8000_PTR(emu)); /* Set रेजिस्टर */
		emu->last_reg = reg;
	पूर्ण
	outw((अचिन्हित लघु)val, port); /* Send data */
	spin_unlock_irqrestore(&emu->reg_lock, flags);
पूर्ण

/* Read a word */
अचिन्हित लघु snd_emu8000_peek(काष्ठा snd_emu8000 *emu, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित लघु res;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&emu->reg_lock, flags);
	अगर (reg != emu->last_reg) अणु
		outw((अचिन्हित लघु)reg, EMU8000_PTR(emu)); /* Set रेजिस्टर */
		emu->last_reg = reg;
	पूर्ण
	res = inw(port);	/* Read data */
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस res;
पूर्ण

/* Write a द्विगुन word */
व्योम snd_emu8000_poke_dw(काष्ठा snd_emu8000 *emu, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&emu->reg_lock, flags);
	अगर (reg != emu->last_reg) अणु
		outw((अचिन्हित लघु)reg, EMU8000_PTR(emu)); /* Set रेजिस्टर */
		emu->last_reg = reg;
	पूर्ण
	outw((अचिन्हित लघु)val, port); /* Send low word of data */
	outw((अचिन्हित लघु)(val>>16), port+2); /* Send high word of data */
	spin_unlock_irqrestore(&emu->reg_lock, flags);
पूर्ण

/* Read a द्विगुन word */
अचिन्हित पूर्णांक snd_emu8000_peek_dw(काष्ठा snd_emu8000 *emu, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित लघु low;
	अचिन्हित पूर्णांक res;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&emu->reg_lock, flags);
	अगर (reg != emu->last_reg) अणु
		outw((अचिन्हित लघु)reg, EMU8000_PTR(emu)); /* Set रेजिस्टर */
		emu->last_reg = reg;
	पूर्ण
	low = inw(port);	/* Read low word of data */
	res = low + (inw(port+2) << 16);
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस res;
पूर्ण

/*
 * Set up / बंद a channel to be used क्रम DMA.
 */
/*exported*/ व्योम
snd_emu8000_dma_chan(काष्ठा snd_emu8000 *emu, पूर्णांक ch, पूर्णांक mode)
अणु
	अचिन्हित right_bit = (mode & EMU8000_RAM_RIGHT) ? 0x01000000 : 0;
	mode &= EMU8000_RAM_MODE_MASK;
	अगर (mode == EMU8000_RAM_CLOSE) अणु
		EMU8000_CCCA_WRITE(emu, ch, 0);
		EMU8000_DCYSUSV_WRITE(emu, ch, 0x807F);
		वापस;
	पूर्ण
	EMU8000_DCYSUSV_WRITE(emu, ch, 0x80);
	EMU8000_VTFT_WRITE(emu, ch, 0);
	EMU8000_CVCF_WRITE(emu, ch, 0);
	EMU8000_PTRX_WRITE(emu, ch, 0x40000000);
	EMU8000_CPF_WRITE(emu, ch, 0x40000000);
	EMU8000_PSST_WRITE(emu, ch, 0);
	EMU8000_CSL_WRITE(emu, ch, 0);
	अगर (mode == EMU8000_RAM_WRITE) /* DMA ग_लिखो */
		EMU8000_CCCA_WRITE(emu, ch, 0x06000000 | right_bit);
	अन्यथा	   /* DMA पढ़ो */
		EMU8000_CCCA_WRITE(emu, ch, 0x04000000 | right_bit);
पूर्ण

/*
 */
अटल व्योम
snd_emu8000_पढ़ो_रुको(काष्ठा snd_emu8000 *emu)
अणु
	जबतक ((EMU8000_SMALR_READ(emu) & 0x80000000) != 0) अणु
		schedule_समयout_पूर्णांकerruptible(1);
		अगर (संकेत_pending(current))
			अवरोध;
	पूर्ण
पूर्ण

/*
 */
अटल व्योम
snd_emu8000_ग_लिखो_रुको(काष्ठा snd_emu8000 *emu)
अणु
	जबतक ((EMU8000_SMALW_READ(emu) & 0x80000000) != 0) अणु
		schedule_समयout_पूर्णांकerruptible(1);
		अगर (संकेत_pending(current))
			अवरोध;
	पूर्ण
पूर्ण

/*
 * detect a card at the given port
 */
अटल पूर्णांक
snd_emu8000_detect(काष्ठा snd_emu8000 *emu)
अणु
	/* Initialise */
	EMU8000_HWCF1_WRITE(emu, 0x0059);
	EMU8000_HWCF2_WRITE(emu, 0x0020);
	EMU8000_HWCF3_WRITE(emu, 0x0000);
	/* Check क्रम a recognisable emu8000 */
	/*
	अगर ((EMU8000_U1_READ(emu) & 0x000f) != 0x000c)
		वापस -ENODEV;
		*/
	अगर ((EMU8000_HWCF1_READ(emu) & 0x007e) != 0x0058)
		वापस -ENODEV;
	अगर ((EMU8000_HWCF2_READ(emu) & 0x0003) != 0x0003)
		वापस -ENODEV;

	snd_prपूर्णांकdd("EMU8000 [0x%lx]: Synth chip found\n",
                    emu->port1);
	वापस 0;
पूर्ण


/*
 * पूर्णांकiailize audio channels
 */
अटल व्योम
init_audio(काष्ठा snd_emu8000 *emu)
अणु
	पूर्णांक ch;

	/* turn off envelope engines */
	क्रम (ch = 0; ch < EMU8000_CHANNELS; ch++)
		EMU8000_DCYSUSV_WRITE(emu, ch, 0x80);
  
	/* reset all other parameters to zero */
	क्रम (ch = 0; ch < EMU8000_CHANNELS; ch++) अणु
		EMU8000_ENVVOL_WRITE(emu, ch, 0);
		EMU8000_ENVVAL_WRITE(emu, ch, 0);
		EMU8000_DCYSUS_WRITE(emu, ch, 0);
		EMU8000_ATKHLDV_WRITE(emu, ch, 0);
		EMU8000_LFO1VAL_WRITE(emu, ch, 0);
		EMU8000_ATKHLD_WRITE(emu, ch, 0);
		EMU8000_LFO2VAL_WRITE(emu, ch, 0);
		EMU8000_IP_WRITE(emu, ch, 0);
		EMU8000_IFATN_WRITE(emu, ch, 0);
		EMU8000_PEFE_WRITE(emu, ch, 0);
		EMU8000_FMMOD_WRITE(emu, ch, 0);
		EMU8000_TREMFRQ_WRITE(emu, ch, 0);
		EMU8000_FM2FRQ2_WRITE(emu, ch, 0);
		EMU8000_PTRX_WRITE(emu, ch, 0);
		EMU8000_VTFT_WRITE(emu, ch, 0);
		EMU8000_PSST_WRITE(emu, ch, 0);
		EMU8000_CSL_WRITE(emu, ch, 0);
		EMU8000_CCCA_WRITE(emu, ch, 0);
	पूर्ण

	क्रम (ch = 0; ch < EMU8000_CHANNELS; ch++) अणु
		EMU8000_CPF_WRITE(emu, ch, 0);
		EMU8000_CVCF_WRITE(emu, ch, 0);
	पूर्ण
पूर्ण


/*
 * initialize DMA address
 */
अटल व्योम
init_dma(काष्ठा snd_emu8000 *emu)
अणु
	EMU8000_SMALR_WRITE(emu, 0);
	EMU8000_SMARR_WRITE(emu, 0);
	EMU8000_SMALW_WRITE(emu, 0);
	EMU8000_SMARW_WRITE(emu, 0);
पूर्ण

/*
 * initialization arrays; from ADIP
 */
अटल स्थिर अचिन्हित लघु init1[128] = अणु
	0x03ff, 0x0030,  0x07ff, 0x0130, 0x0bff, 0x0230,  0x0fff, 0x0330,
	0x13ff, 0x0430,  0x17ff, 0x0530, 0x1bff, 0x0630,  0x1fff, 0x0730,
	0x23ff, 0x0830,  0x27ff, 0x0930, 0x2bff, 0x0a30,  0x2fff, 0x0b30,
	0x33ff, 0x0c30,  0x37ff, 0x0d30, 0x3bff, 0x0e30,  0x3fff, 0x0f30,

	0x43ff, 0x0030,  0x47ff, 0x0130, 0x4bff, 0x0230,  0x4fff, 0x0330,
	0x53ff, 0x0430,  0x57ff, 0x0530, 0x5bff, 0x0630,  0x5fff, 0x0730,
	0x63ff, 0x0830,  0x67ff, 0x0930, 0x6bff, 0x0a30,  0x6fff, 0x0b30,
	0x73ff, 0x0c30,  0x77ff, 0x0d30, 0x7bff, 0x0e30,  0x7fff, 0x0f30,

	0x83ff, 0x0030,  0x87ff, 0x0130, 0x8bff, 0x0230,  0x8fff, 0x0330,
	0x93ff, 0x0430,  0x97ff, 0x0530, 0x9bff, 0x0630,  0x9fff, 0x0730,
	0xa3ff, 0x0830,  0xa7ff, 0x0930, 0xabff, 0x0a30,  0xafff, 0x0b30,
	0xb3ff, 0x0c30,  0xb7ff, 0x0d30, 0xbbff, 0x0e30,  0xbfff, 0x0f30,

	0xc3ff, 0x0030,  0xc7ff, 0x0130, 0xcbff, 0x0230,  0xcfff, 0x0330,
	0xd3ff, 0x0430,  0xd7ff, 0x0530, 0xdbff, 0x0630,  0xdfff, 0x0730,
	0xe3ff, 0x0830,  0xe7ff, 0x0930, 0xebff, 0x0a30,  0xefff, 0x0b30,
	0xf3ff, 0x0c30,  0xf7ff, 0x0d30, 0xfbff, 0x0e30,  0xffff, 0x0f30,
पूर्ण;

अटल स्थिर अचिन्हित लघु init2[128] = अणु
	0x03ff, 0x8030, 0x07ff, 0x8130, 0x0bff, 0x8230, 0x0fff, 0x8330,
	0x13ff, 0x8430, 0x17ff, 0x8530, 0x1bff, 0x8630, 0x1fff, 0x8730,
	0x23ff, 0x8830, 0x27ff, 0x8930, 0x2bff, 0x8a30, 0x2fff, 0x8b30,
	0x33ff, 0x8c30, 0x37ff, 0x8d30, 0x3bff, 0x8e30, 0x3fff, 0x8f30,

	0x43ff, 0x8030, 0x47ff, 0x8130, 0x4bff, 0x8230, 0x4fff, 0x8330,
	0x53ff, 0x8430, 0x57ff, 0x8530, 0x5bff, 0x8630, 0x5fff, 0x8730,
	0x63ff, 0x8830, 0x67ff, 0x8930, 0x6bff, 0x8a30, 0x6fff, 0x8b30,
	0x73ff, 0x8c30, 0x77ff, 0x8d30, 0x7bff, 0x8e30, 0x7fff, 0x8f30,

	0x83ff, 0x8030, 0x87ff, 0x8130, 0x8bff, 0x8230, 0x8fff, 0x8330,
	0x93ff, 0x8430, 0x97ff, 0x8530, 0x9bff, 0x8630, 0x9fff, 0x8730,
	0xa3ff, 0x8830, 0xa7ff, 0x8930, 0xabff, 0x8a30, 0xafff, 0x8b30,
	0xb3ff, 0x8c30, 0xb7ff, 0x8d30, 0xbbff, 0x8e30, 0xbfff, 0x8f30,

	0xc3ff, 0x8030, 0xc7ff, 0x8130, 0xcbff, 0x8230, 0xcfff, 0x8330,
	0xd3ff, 0x8430, 0xd7ff, 0x8530, 0xdbff, 0x8630, 0xdfff, 0x8730,
	0xe3ff, 0x8830, 0xe7ff, 0x8930, 0xebff, 0x8a30, 0xefff, 0x8b30,
	0xf3ff, 0x8c30, 0xf7ff, 0x8d30, 0xfbff, 0x8e30, 0xffff, 0x8f30,
पूर्ण;

अटल स्थिर अचिन्हित लघु init3[128] = अणु
	0x0C10, 0x8470, 0x14FE, 0xB488, 0x167F, 0xA470, 0x18E7, 0x84B5,
	0x1B6E, 0x842A, 0x1F1D, 0x852A, 0x0DA3, 0x8F7C, 0x167E, 0xF254,
	0x0000, 0x842A, 0x0001, 0x852A, 0x18E6, 0x8BAA, 0x1B6D, 0xF234,
	0x229F, 0x8429, 0x2746, 0x8529, 0x1F1C, 0x86E7, 0x229E, 0xF224,

	0x0DA4, 0x8429, 0x2C29, 0x8529, 0x2745, 0x87F6, 0x2C28, 0xF254,
	0x383B, 0x8428, 0x320F, 0x8528, 0x320E, 0x8F02, 0x1341, 0xF264,
	0x3EB6, 0x8428, 0x3EB9, 0x8528, 0x383A, 0x8FA9, 0x3EB5, 0xF294,
	0x3EB7, 0x8474, 0x3EBA, 0x8575, 0x3EB8, 0xC4C3, 0x3EBB, 0xC5C3,

	0x0000, 0xA404, 0x0001, 0xA504, 0x141F, 0x8671, 0x14FD, 0x8287,
	0x3EBC, 0xE610, 0x3EC8, 0x8C7B, 0x031A, 0x87E6, 0x3EC8, 0x86F7,
	0x3EC0, 0x821E, 0x3EBE, 0xD208, 0x3EBD, 0x821F, 0x3ECA, 0x8386,
	0x3EC1, 0x8C03, 0x3EC9, 0x831E, 0x3ECA, 0x8C4C, 0x3EBF, 0x8C55,

	0x3EC9, 0xC208, 0x3EC4, 0xBC84, 0x3EC8, 0x8EAD, 0x3EC8, 0xD308,
	0x3EC2, 0x8F7E, 0x3ECB, 0x8219, 0x3ECB, 0xD26E, 0x3EC5, 0x831F,
	0x3EC6, 0xC308, 0x3EC3, 0xB2FF, 0x3EC9, 0x8265, 0x3EC9, 0x8319,
	0x1342, 0xD36E, 0x3EC7, 0xB3FF, 0x0000, 0x8365, 0x1420, 0x9570,
पूर्ण;

अटल स्थिर अचिन्हित लघु init4[128] = अणु
	0x0C10, 0x8470, 0x14FE, 0xB488, 0x167F, 0xA470, 0x18E7, 0x84B5,
	0x1B6E, 0x842A, 0x1F1D, 0x852A, 0x0DA3, 0x0F7C, 0x167E, 0x7254,
	0x0000, 0x842A, 0x0001, 0x852A, 0x18E6, 0x0BAA, 0x1B6D, 0x7234,
	0x229F, 0x8429, 0x2746, 0x8529, 0x1F1C, 0x06E7, 0x229E, 0x7224,

	0x0DA4, 0x8429, 0x2C29, 0x8529, 0x2745, 0x07F6, 0x2C28, 0x7254,
	0x383B, 0x8428, 0x320F, 0x8528, 0x320E, 0x0F02, 0x1341, 0x7264,
	0x3EB6, 0x8428, 0x3EB9, 0x8528, 0x383A, 0x0FA9, 0x3EB5, 0x7294,
	0x3EB7, 0x8474, 0x3EBA, 0x8575, 0x3EB8, 0x44C3, 0x3EBB, 0x45C3,

	0x0000, 0xA404, 0x0001, 0xA504, 0x141F, 0x0671, 0x14FD, 0x0287,
	0x3EBC, 0xE610, 0x3EC8, 0x0C7B, 0x031A, 0x07E6, 0x3EC8, 0x86F7,
	0x3EC0, 0x821E, 0x3EBE, 0xD208, 0x3EBD, 0x021F, 0x3ECA, 0x0386,
	0x3EC1, 0x0C03, 0x3EC9, 0x031E, 0x3ECA, 0x8C4C, 0x3EBF, 0x0C55,

	0x3EC9, 0xC208, 0x3EC4, 0xBC84, 0x3EC8, 0x0EAD, 0x3EC8, 0xD308,
	0x3EC2, 0x8F7E, 0x3ECB, 0x0219, 0x3ECB, 0xD26E, 0x3EC5, 0x031F,
	0x3EC6, 0xC308, 0x3EC3, 0x32FF, 0x3EC9, 0x0265, 0x3EC9, 0x8319,
	0x1342, 0xD36E, 0x3EC7, 0x33FF, 0x0000, 0x8365, 0x1420, 0x9570,
पूर्ण;

/* send an initialization array
 * Taken from the oss driver, not obvious from the करोc how this
 * is meant to work
 */
अटल व्योम
send_array(काष्ठा snd_emu8000 *emu, स्थिर अचिन्हित लघु *data, पूर्णांक size)
अणु
	पूर्णांक i;
	स्थिर अचिन्हित लघु *p;

	p = data;
	क्रम (i = 0; i < size; i++, p++)
		EMU8000_INIT1_WRITE(emu, i, *p);
	क्रम (i = 0; i < size; i++, p++)
		EMU8000_INIT2_WRITE(emu, i, *p);
	क्रम (i = 0; i < size; i++, p++)
		EMU8000_INIT3_WRITE(emu, i, *p);
	क्रम (i = 0; i < size; i++, p++)
		EMU8000_INIT4_WRITE(emu, i, *p);
पूर्ण


/*
 * Send initialization arrays to start up, this just follows the
 * initialisation sequence in the adip.
 */
अटल व्योम
init_arrays(काष्ठा snd_emu8000 *emu)
अणु
	send_array(emu, init1, ARRAY_SIZE(init1)/4);

	msleep((1024 * 1000) / 44100); /* रुको क्रम 1024 घड़ीs */
	send_array(emu, init2, ARRAY_SIZE(init2)/4);
	send_array(emu, init3, ARRAY_SIZE(init3)/4);

	EMU8000_HWCF4_WRITE(emu, 0);
	EMU8000_HWCF5_WRITE(emu, 0x83);
	EMU8000_HWCF6_WRITE(emu, 0x8000);

	send_array(emu, init4, ARRAY_SIZE(init4)/4);
पूर्ण


#घोषणा UNIQUE_ID1	0xa5b9
#घोषणा UNIQUE_ID2	0x9d53

/*
 * Size the onboard memory.
 * This is written so as not to need arbitrary delays after the ग_लिखो. It
 * seems that the only way to करो this is to use the one channel and keep
 * पुनः_स्मृतिating between पढ़ो and ग_लिखो.
 */
अटल व्योम
size_dram(काष्ठा snd_emu8000 *emu)
अणु
	पूर्णांक i, size;

	अगर (emu->dram_checked)
		वापस;

	size = 0;

	/* ग_लिखो out a magic number */
	snd_emu8000_dma_chan(emu, 0, EMU8000_RAM_WRITE);
	snd_emu8000_dma_chan(emu, 1, EMU8000_RAM_READ);
	EMU8000_SMALW_WRITE(emu, EMU8000_DRAM_OFFSET);
	EMU8000_SMLD_WRITE(emu, UNIQUE_ID1);
	snd_emu8000_init_fm(emu); /* This must really be here and not 2 lines back even */
	snd_emu8000_ग_लिखो_रुको(emu);

	/*
	 * Detect first 512 KiB.  If a ग_लिखो succeeds at the beginning of a
	 * 512 KiB page we assume that the whole page is there.
	 */
	EMU8000_SMALR_WRITE(emu, EMU8000_DRAM_OFFSET);
	EMU8000_SMLD_READ(emu); /* discard stale data  */
	अगर (EMU8000_SMLD_READ(emu) != UNIQUE_ID1)
		जाओ skip_detect;   /* No RAM */
	snd_emu8000_पढ़ो_रुको(emu);

	क्रम (size = 512 * 1024; size < EMU8000_MAX_DRAM; size += 512 * 1024) अणु

		/* Write a unique data on the test address.
		 * अगर the address is out of range, the data is written on
		 * 0x200000(=EMU8000_DRAM_OFFSET).  Then the id word is
		 * changed by this data.
		 */
		/*snd_emu8000_dma_chan(emu, 0, EMU8000_RAM_WRITE);*/
		EMU8000_SMALW_WRITE(emu, EMU8000_DRAM_OFFSET + (size>>1));
		EMU8000_SMLD_WRITE(emu, UNIQUE_ID2);
		snd_emu8000_ग_लिखो_रुको(emu);

		/*
		 * पढ़ो the data on the just written DRAM address
		 * अगर not the same then we have reached the end of ram.
		 */
		/*snd_emu8000_dma_chan(emu, 0, EMU8000_RAM_READ);*/
		EMU8000_SMALR_WRITE(emu, EMU8000_DRAM_OFFSET + (size>>1));
		/*snd_emu8000_पढ़ो_रुको(emu);*/
		EMU8000_SMLD_READ(emu); /* discard stale data  */
		अगर (EMU8000_SMLD_READ(emu) != UNIQUE_ID2)
			अवरोध; /* no memory at this address */
		snd_emu8000_पढ़ो_रुको(emu);

		/*
		 * If it is the same it could be that the address just
		 * wraps back to the beginning; so check to see अगर the
		 * initial value has been overwritten.
		 */
		EMU8000_SMALR_WRITE(emu, EMU8000_DRAM_OFFSET);
		EMU8000_SMLD_READ(emu); /* discard stale data  */
		अगर (EMU8000_SMLD_READ(emu) != UNIQUE_ID1)
			अवरोध; /* we must have wrapped around */
		snd_emu8000_पढ़ो_रुको(emu);

		/* Otherwise, it's valid memory. */
	पूर्ण

skip_detect:
	/* रुको until FULL bit in SMAxW रेजिस्टर is false */
	क्रम (i = 0; i < 10000; i++) अणु
		अगर ((EMU8000_SMALW_READ(emu) & 0x80000000) == 0)
			अवरोध;
		schedule_समयout_पूर्णांकerruptible(1);
		अगर (संकेत_pending(current))
			अवरोध;
	पूर्ण
	snd_emu8000_dma_chan(emu, 0, EMU8000_RAM_CLOSE);
	snd_emu8000_dma_chan(emu, 1, EMU8000_RAM_CLOSE);

	pr_info("EMU8000 [0x%lx]: %d KiB on-board DRAM detected\n",
		    emu->port1, size/1024);

	emu->mem_size = size;
	emu->dram_checked = 1;
पूर्ण


/*
 * Initiailise the FM section.  You have to करो this to use sample RAM
 * and thereक्रमe lose 2 voices.
 */
/*exported*/ व्योम
snd_emu8000_init_fm(काष्ठा snd_emu8000 *emu)
अणु
	अचिन्हित दीर्घ flags;

	/* Initialize the last two channels क्रम DRAM refresh and producing
	   the reverb and chorus effects क्रम Yamaha OPL-3 synthesizer */

	/* 31: FM left channel, 0xffffe0-0xffffe8 */
	EMU8000_DCYSUSV_WRITE(emu, 30, 0x80);
	EMU8000_PSST_WRITE(emu, 30, 0xFFFFFFE0); /* full left */
	EMU8000_CSL_WRITE(emu, 30, 0x00FFFFE8 | (emu->fm_chorus_depth << 24));
	EMU8000_PTRX_WRITE(emu, 30, (emu->fm_reverb_depth << 8));
	EMU8000_CPF_WRITE(emu, 30, 0);
	EMU8000_CCCA_WRITE(emu, 30, 0x00FFFFE3);

	/* 32: FM right channel, 0xfffff0-0xfffff8 */
	EMU8000_DCYSUSV_WRITE(emu, 31, 0x80);
	EMU8000_PSST_WRITE(emu, 31, 0x00FFFFF0); /* full right */
	EMU8000_CSL_WRITE(emu, 31, 0x00FFFFF8 | (emu->fm_chorus_depth << 24));
	EMU8000_PTRX_WRITE(emu, 31, (emu->fm_reverb_depth << 8));
	EMU8000_CPF_WRITE(emu, 31, 0x8000);
	EMU8000_CCCA_WRITE(emu, 31, 0x00FFFFF3);

	snd_emu8000_poke((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (30)), 0);

	spin_lock_irqsave(&emu->reg_lock, flags);
	जबतक (!(inw(EMU8000_PTR(emu)) & 0x1000))
		;
	जबतक ((inw(EMU8000_PTR(emu)) & 0x1000))
		;
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	snd_emu8000_poke((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (30)), 0x4828);
	/* this is really odd part.. */
	outb(0x3C, EMU8000_PTR(emu));
	outb(0, EMU8000_DATA1(emu));

	/* skew volume & cutoff */
	EMU8000_VTFT_WRITE(emu, 30, 0x8000FFFF);
	EMU8000_VTFT_WRITE(emu, 31, 0x8000FFFF);
पूर्ण


/*
 * The मुख्य initialization routine.
 */
अटल व्योम
snd_emu8000_init_hw(काष्ठा snd_emu8000 *emu)
अणु
	पूर्णांक i;

	emu->last_reg = 0xffff; /* reset the last रेजिस्टर index */

	/* initialize hardware configuration */
	EMU8000_HWCF1_WRITE(emu, 0x0059);
	EMU8000_HWCF2_WRITE(emu, 0x0020);

	/* disable audio; this seems to reduce a clicking noise a bit.. */
	EMU8000_HWCF3_WRITE(emu, 0);

	/* initialize audio channels */
	init_audio(emu);

	/* initialize DMA */
	init_dma(emu);

	/* initialize init arrays */
	init_arrays(emu);

	/*
	 * Initialize the FM section of the AWE32, this is needed
	 * क्रम DRAM refresh as well
	 */
	snd_emu8000_init_fm(emu);

	/* terminate all voices */
	क्रम (i = 0; i < EMU8000_DRAM_VOICES; i++)
		EMU8000_DCYSUSV_WRITE(emu, 0, 0x807F);
	
	/* check DRAM memory size */
	size_dram(emu);

	/* enable audio */
	EMU8000_HWCF3_WRITE(emu, 0x4);

	/* set equzlier, chorus and reverb modes */
	snd_emu8000_update_equalizer(emu);
	snd_emu8000_update_chorus_mode(emu);
	snd_emu8000_update_reverb_mode(emu);
पूर्ण


/*----------------------------------------------------------------
 * Bass/Treble Equalizer
 *----------------------------------------------------------------*/

अटल स्थिर अचिन्हित लघु bass_parm[12][3] = अणु
	अणु0xD26A, 0xD36A, 0x0000पूर्ण, /* -12 dB */
	अणु0xD25B, 0xD35B, 0x0000पूर्ण, /*  -8 */
	अणु0xD24C, 0xD34C, 0x0000पूर्ण, /*  -6 */
	अणु0xD23D, 0xD33D, 0x0000पूर्ण, /*  -4 */
	अणु0xD21F, 0xD31F, 0x0000पूर्ण, /*  -2 */
	अणु0xC208, 0xC308, 0x0001पूर्ण, /*   0 (HW शेष) */
	अणु0xC219, 0xC319, 0x0001पूर्ण, /*  +2 */
	अणु0xC22A, 0xC32A, 0x0001पूर्ण, /*  +4 */
	अणु0xC24C, 0xC34C, 0x0001पूर्ण, /*  +6 */
	अणु0xC26E, 0xC36E, 0x0001पूर्ण, /*  +8 */
	अणु0xC248, 0xC384, 0x0002पूर्ण, /* +10 */
	अणु0xC26A, 0xC36A, 0x0002पूर्ण, /* +12 dB */
पूर्ण;

अटल स्थिर अचिन्हित लघु treble_parm[12][9] = अणु
	अणु0x821E, 0xC26A, 0x031E, 0xC36A, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001पूर्ण, /* -12 dB */
	अणु0x821E, 0xC25B, 0x031E, 0xC35B, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001पूर्ण,
	अणु0x821E, 0xC24C, 0x031E, 0xC34C, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001पूर्ण,
	अणु0x821E, 0xC23D, 0x031E, 0xC33D, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001पूर्ण,
	अणु0x821E, 0xC21F, 0x031E, 0xC31F, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001पूर्ण,
	अणु0x821E, 0xD208, 0x031E, 0xD308, 0x021E, 0xD208, 0x831E, 0xD308, 0x0002पूर्ण,
	अणु0x821E, 0xD208, 0x031E, 0xD308, 0x021D, 0xD219, 0x831D, 0xD319, 0x0002पूर्ण,
	अणु0x821E, 0xD208, 0x031E, 0xD308, 0x021C, 0xD22A, 0x831C, 0xD32A, 0x0002पूर्ण,
	अणु0x821E, 0xD208, 0x031E, 0xD308, 0x021A, 0xD24C, 0x831A, 0xD34C, 0x0002पूर्ण,
	अणु0x821E, 0xD208, 0x031E, 0xD308, 0x0219, 0xD26E, 0x8319, 0xD36E, 0x0002पूर्ण, /* +8 (HW शेष) */
	अणु0x821D, 0xD219, 0x031D, 0xD319, 0x0219, 0xD26E, 0x8319, 0xD36E, 0x0002पूर्ण,
	अणु0x821C, 0xD22A, 0x031C, 0xD32A, 0x0219, 0xD26E, 0x8319, 0xD36E, 0x0002पूर्ण  /* +12 dB */
पूर्ण;


/*
 * set Emu8000 digital equalizer; from 0 to 11 [-12dB - 12dB]
 */
/*exported*/ व्योम
snd_emu8000_update_equalizer(काष्ठा snd_emu8000 *emu)
अणु
	अचिन्हित लघु w;
	पूर्णांक bass = emu->bass_level;
	पूर्णांक treble = emu->treble_level;

	अगर (bass < 0 || bass > 11 || treble < 0 || treble > 11)
		वापस;
	EMU8000_INIT4_WRITE(emu, 0x01, bass_parm[bass][0]);
	EMU8000_INIT4_WRITE(emu, 0x11, bass_parm[bass][1]);
	EMU8000_INIT3_WRITE(emu, 0x11, treble_parm[treble][0]);
	EMU8000_INIT3_WRITE(emu, 0x13, treble_parm[treble][1]);
	EMU8000_INIT3_WRITE(emu, 0x1b, treble_parm[treble][2]);
	EMU8000_INIT4_WRITE(emu, 0x07, treble_parm[treble][3]);
	EMU8000_INIT4_WRITE(emu, 0x0b, treble_parm[treble][4]);
	EMU8000_INIT4_WRITE(emu, 0x0d, treble_parm[treble][5]);
	EMU8000_INIT4_WRITE(emu, 0x17, treble_parm[treble][6]);
	EMU8000_INIT4_WRITE(emu, 0x19, treble_parm[treble][7]);
	w = bass_parm[bass][2] + treble_parm[treble][8];
	EMU8000_INIT4_WRITE(emu, 0x15, (अचिन्हित लघु)(w + 0x0262));
	EMU8000_INIT4_WRITE(emu, 0x1d, (अचिन्हित लघु)(w + 0x8362));
पूर्ण


/*----------------------------------------------------------------
 * Chorus mode control
 *----------------------------------------------------------------*/

/*
 * chorus mode parameters
 */
#घोषणा SNDRV_EMU8000_CHORUS_1		0
#घोषणा	SNDRV_EMU8000_CHORUS_2		1
#घोषणा	SNDRV_EMU8000_CHORUS_3		2
#घोषणा	SNDRV_EMU8000_CHORUS_4		3
#घोषणा	SNDRV_EMU8000_CHORUS_FEEDBACK	4
#घोषणा	SNDRV_EMU8000_CHORUS_FLANGER	5
#घोषणा	SNDRV_EMU8000_CHORUS_SHORTDELAY	6
#घोषणा	SNDRV_EMU8000_CHORUS_SHORTDELAY2	7
#घोषणा SNDRV_EMU8000_CHORUS_PREDEFINED	8
/* user can define chorus modes up to 32 */
#घोषणा SNDRV_EMU8000_CHORUS_NUMBERS	32

काष्ठा soundfont_chorus_fx अणु
	अचिन्हित लघु feedback;	/* feedback level (0xE600-0xE6FF) */
	अचिन्हित लघु delay_offset;	/* delay (0-0x0DA3) [1/44100 sec] */
	अचिन्हित लघु lfo_depth;	/* LFO depth (0xBC00-0xBCFF) */
	अचिन्हित पूर्णांक delay;	/* right delay (0-0xFFFFFFFF) [1/256/44100 sec] */
	अचिन्हित पूर्णांक lfo_freq;		/* LFO freq LFO freq (0-0xFFFFFFFF) */
पूर्ण;

/* 5 parameters क्रम each chorus mode; 3 x 16bit, 2 x 32bit */
अटल अक्षर chorus_defined[SNDRV_EMU8000_CHORUS_NUMBERS];
अटल काष्ठा soundfont_chorus_fx chorus_parm[SNDRV_EMU8000_CHORUS_NUMBERS] = अणु
	अणु0xE600, 0x03F6, 0xBC2C ,0x00000000, 0x0000006Dपूर्ण, /* chorus 1 */
	अणु0xE608, 0x031A, 0xBC6E, 0x00000000, 0x0000017Cपूर्ण, /* chorus 2 */
	अणु0xE610, 0x031A, 0xBC84, 0x00000000, 0x00000083पूर्ण, /* chorus 3 */
	अणु0xE620, 0x0269, 0xBC6E, 0x00000000, 0x0000017Cपूर्ण, /* chorus 4 */
	अणु0xE680, 0x04D3, 0xBCA6, 0x00000000, 0x0000005Bपूर्ण, /* feedback */
	अणु0xE6E0, 0x044E, 0xBC37, 0x00000000, 0x00000026पूर्ण, /* flanger */
	अणु0xE600, 0x0B06, 0xBC00, 0x0006E000, 0x00000083पूर्ण, /* लघु delay */
	अणु0xE6C0, 0x0B06, 0xBC00, 0x0006E000, 0x00000083पूर्ण, /* लघु delay + feedback */
पूर्ण;

/*exported*/ पूर्णांक
snd_emu8000_load_chorus_fx(काष्ठा snd_emu8000 *emu, पूर्णांक mode, स्थिर व्योम __user *buf, दीर्घ len)
अणु
	काष्ठा soundfont_chorus_fx rec;
	अगर (mode < SNDRV_EMU8000_CHORUS_PREDEFINED || mode >= SNDRV_EMU8000_CHORUS_NUMBERS) अणु
		snd_prपूर्णांकk(KERN_WARNING "invalid chorus mode %d for uploading\n", mode);
		वापस -EINVAL;
	पूर्ण
	अगर (len < (दीर्घ)माप(rec) || copy_from_user(&rec, buf, माप(rec)))
		वापस -EFAULT;
	chorus_parm[mode] = rec;
	chorus_defined[mode] = 1;
	वापस 0;
पूर्ण

/*exported*/ व्योम
snd_emu8000_update_chorus_mode(काष्ठा snd_emu8000 *emu)
अणु
	पूर्णांक effect = emu->chorus_mode;
	अगर (effect < 0 || effect >= SNDRV_EMU8000_CHORUS_NUMBERS ||
	    (effect >= SNDRV_EMU8000_CHORUS_PREDEFINED && !chorus_defined[effect]))
		वापस;
	EMU8000_INIT3_WRITE(emu, 0x09, chorus_parm[effect].feedback);
	EMU8000_INIT3_WRITE(emu, 0x0c, chorus_parm[effect].delay_offset);
	EMU8000_INIT4_WRITE(emu, 0x03, chorus_parm[effect].lfo_depth);
	EMU8000_HWCF4_WRITE(emu, chorus_parm[effect].delay);
	EMU8000_HWCF5_WRITE(emu, chorus_parm[effect].lfo_freq);
	EMU8000_HWCF6_WRITE(emu, 0x8000);
	EMU8000_HWCF7_WRITE(emu, 0x0000);
पूर्ण

/*----------------------------------------------------------------
 * Reverb mode control
 *----------------------------------------------------------------*/

/*
 * reverb mode parameters
 */
#घोषणा	SNDRV_EMU8000_REVERB_ROOM1	0
#घोषणा SNDRV_EMU8000_REVERB_ROOM2	1
#घोषणा	SNDRV_EMU8000_REVERB_ROOM3	2
#घोषणा	SNDRV_EMU8000_REVERB_HALL1	3
#घोषणा	SNDRV_EMU8000_REVERB_HALL2	4
#घोषणा	SNDRV_EMU8000_REVERB_PLATE	5
#घोषणा	SNDRV_EMU8000_REVERB_DELAY	6
#घोषणा	SNDRV_EMU8000_REVERB_PANNINGDELAY 7
#घोषणा SNDRV_EMU8000_REVERB_PREDEFINED	8
/* user can define reverb modes up to 32 */
#घोषणा SNDRV_EMU8000_REVERB_NUMBERS	32

काष्ठा soundfont_reverb_fx अणु
	अचिन्हित लघु parms[28];
पूर्ण;

/* reverb mode settings; ग_लिखो the following 28 data of 16 bit length
 *   on the corresponding ports in the reverb_cmds array
 */
अटल अक्षर reverb_defined[SNDRV_EMU8000_CHORUS_NUMBERS];
अटल काष्ठा soundfont_reverb_fx reverb_parm[SNDRV_EMU8000_REVERB_NUMBERS] = अणु
अणुअणु  /* room 1 */
	0xB488, 0xA450, 0x9550, 0x84B5, 0x383A, 0x3EB5, 0x72F4,
	0x72A4, 0x7254, 0x7204, 0x7204, 0x7204, 0x4416, 0x4516,
	0xA490, 0xA590, 0x842A, 0x852A, 0x842A, 0x852A, 0x8429,
	0x8529, 0x8429, 0x8529, 0x8428, 0x8528, 0x8428, 0x8528,
पूर्णपूर्ण,
अणुअणु  /* room 2 */
	0xB488, 0xA458, 0x9558, 0x84B5, 0x383A, 0x3EB5, 0x7284,
	0x7254, 0x7224, 0x7224, 0x7254, 0x7284, 0x4448, 0x4548,
	0xA440, 0xA540, 0x842A, 0x852A, 0x842A, 0x852A, 0x8429,
	0x8529, 0x8429, 0x8529, 0x8428, 0x8528, 0x8428, 0x8528,
पूर्णपूर्ण,
अणुअणु  /* room 3 */
	0xB488, 0xA460, 0x9560, 0x84B5, 0x383A, 0x3EB5, 0x7284,
	0x7254, 0x7224, 0x7224, 0x7254, 0x7284, 0x4416, 0x4516,
	0xA490, 0xA590, 0x842C, 0x852C, 0x842C, 0x852C, 0x842B,
	0x852B, 0x842B, 0x852B, 0x842A, 0x852A, 0x842A, 0x852A,
पूर्णपूर्ण,
अणुअणु  /* hall 1 */
	0xB488, 0xA470, 0x9570, 0x84B5, 0x383A, 0x3EB5, 0x7284,
	0x7254, 0x7224, 0x7224, 0x7254, 0x7284, 0x4448, 0x4548,
	0xA440, 0xA540, 0x842B, 0x852B, 0x842B, 0x852B, 0x842A,
	0x852A, 0x842A, 0x852A, 0x8429, 0x8529, 0x8429, 0x8529,
पूर्णपूर्ण,
अणुअणु  /* hall 2 */
	0xB488, 0xA470, 0x9570, 0x84B5, 0x383A, 0x3EB5, 0x7254,
	0x7234, 0x7224, 0x7254, 0x7264, 0x7294, 0x44C3, 0x45C3,
	0xA404, 0xA504, 0x842A, 0x852A, 0x842A, 0x852A, 0x8429,
	0x8529, 0x8429, 0x8529, 0x8428, 0x8528, 0x8428, 0x8528,
पूर्णपूर्ण,
अणुअणु  /* plate */
	0xB4FF, 0xA470, 0x9570, 0x84B5, 0x383A, 0x3EB5, 0x7234,
	0x7234, 0x7234, 0x7234, 0x7234, 0x7234, 0x4448, 0x4548,
	0xA440, 0xA540, 0x842A, 0x852A, 0x842A, 0x852A, 0x8429,
	0x8529, 0x8429, 0x8529, 0x8428, 0x8528, 0x8428, 0x8528,
पूर्णपूर्ण,
अणुअणु  /* delay */
	0xB4FF, 0xA470, 0x9500, 0x84B5, 0x333A, 0x39B5, 0x7204,
	0x7204, 0x7204, 0x7204, 0x7204, 0x72F4, 0x4400, 0x4500,
	0xA4FF, 0xA5FF, 0x8420, 0x8520, 0x8420, 0x8520, 0x8420,
	0x8520, 0x8420, 0x8520, 0x8420, 0x8520, 0x8420, 0x8520,
पूर्णपूर्ण,
अणुअणु  /* panning delay */
	0xB4FF, 0xA490, 0x9590, 0x8474, 0x333A, 0x39B5, 0x7204,
	0x7204, 0x7204, 0x7204, 0x7204, 0x72F4, 0x4400, 0x4500,
	0xA4FF, 0xA5FF, 0x8420, 0x8520, 0x8420, 0x8520, 0x8420,
	0x8520, 0x8420, 0x8520, 0x8420, 0x8520, 0x8420, 0x8520,
पूर्णपूर्ण,
पूर्ण;

क्रमागत अणु DATA1, DATA2 पूर्ण;
#घोषणा AWE_INIT1(c)	EMU8000_CMD(2,c), DATA1
#घोषणा AWE_INIT2(c)	EMU8000_CMD(2,c), DATA2
#घोषणा AWE_INIT3(c)	EMU8000_CMD(3,c), DATA1
#घोषणा AWE_INIT4(c)	EMU8000_CMD(3,c), DATA2

अटल काष्ठा reverb_cmd_pair अणु
	अचिन्हित लघु cmd, port;
पूर्ण reverb_cmds[28] = अणु
  अणुAWE_INIT1(0x03)पूर्ण, अणुAWE_INIT1(0x05)पूर्ण, अणुAWE_INIT4(0x1F)पूर्ण, अणुAWE_INIT1(0x07)पूर्ण,
  अणुAWE_INIT2(0x14)पूर्ण, अणुAWE_INIT2(0x16)पूर्ण, अणुAWE_INIT1(0x0F)पूर्ण, अणुAWE_INIT1(0x17)पूर्ण,
  अणुAWE_INIT1(0x1F)पूर्ण, अणुAWE_INIT2(0x07)पूर्ण, अणुAWE_INIT2(0x0F)पूर्ण, अणुAWE_INIT2(0x17)पूर्ण,
  अणुAWE_INIT2(0x1D)पूर्ण, अणुAWE_INIT2(0x1F)पूर्ण, अणुAWE_INIT3(0x01)पूर्ण, अणुAWE_INIT3(0x03)पूर्ण,
  अणुAWE_INIT1(0x09)पूर्ण, अणुAWE_INIT1(0x0B)पूर्ण, अणुAWE_INIT1(0x11)पूर्ण, अणुAWE_INIT1(0x13)पूर्ण,
  अणुAWE_INIT1(0x19)पूर्ण, अणुAWE_INIT1(0x1B)पूर्ण, अणुAWE_INIT2(0x01)पूर्ण, अणुAWE_INIT2(0x03)पूर्ण,
  अणुAWE_INIT2(0x09)पूर्ण, अणुAWE_INIT2(0x0B)पूर्ण, अणुAWE_INIT2(0x11)पूर्ण, अणुAWE_INIT2(0x13)पूर्ण,
पूर्ण;

/*exported*/ पूर्णांक
snd_emu8000_load_reverb_fx(काष्ठा snd_emu8000 *emu, पूर्णांक mode, स्थिर व्योम __user *buf, दीर्घ len)
अणु
	काष्ठा soundfont_reverb_fx rec;

	अगर (mode < SNDRV_EMU8000_REVERB_PREDEFINED || mode >= SNDRV_EMU8000_REVERB_NUMBERS) अणु
		snd_prपूर्णांकk(KERN_WARNING "invalid reverb mode %d for uploading\n", mode);
		वापस -EINVAL;
	पूर्ण
	अगर (len < (दीर्घ)माप(rec) || copy_from_user(&rec, buf, माप(rec)))
		वापस -EFAULT;
	reverb_parm[mode] = rec;
	reverb_defined[mode] = 1;
	वापस 0;
पूर्ण

/*exported*/ व्योम
snd_emu8000_update_reverb_mode(काष्ठा snd_emu8000 *emu)
अणु
	पूर्णांक effect = emu->reverb_mode;
	पूर्णांक i;

	अगर (effect < 0 || effect >= SNDRV_EMU8000_REVERB_NUMBERS ||
	    (effect >= SNDRV_EMU8000_REVERB_PREDEFINED && !reverb_defined[effect]))
		वापस;
	क्रम (i = 0; i < 28; i++) अणु
		पूर्णांक port;
		अगर (reverb_cmds[i].port == DATA1)
			port = EMU8000_DATA1(emu);
		अन्यथा
			port = EMU8000_DATA2(emu);
		snd_emu8000_poke(emu, port, reverb_cmds[i].cmd, reverb_parm[effect].parms[i]);
	पूर्ण
पूर्ण


/*----------------------------------------------------------------
 * mixer पूर्णांकerface
 *----------------------------------------------------------------*/

/*
 * bass/treble
 */
अटल पूर्णांक mixer_bass_treble_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 11;
	वापस 0;
पूर्ण

अटल पूर्णांक mixer_bass_treble_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu8000 *emu = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] = kcontrol->निजी_value ? emu->treble_level : emu->bass_level;
	वापस 0;
पूर्ण

अटल पूर्णांक mixer_bass_treble_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu8000 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित लघु val1;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] % 12;
	spin_lock_irqsave(&emu->control_lock, flags);
	अगर (kcontrol->निजी_value) अणु
		change = val1 != emu->treble_level;
		emu->treble_level = val1;
	पूर्ण अन्यथा अणु
		change = val1 != emu->bass_level;
		emu->bass_level = val1;
	पूर्ण
	spin_unlock_irqrestore(&emu->control_lock, flags);
	snd_emu8000_update_equalizer(emu);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mixer_bass_control =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Synth Tone Control - Bass",
	.info = mixer_bass_treble_info,
	.get = mixer_bass_treble_get,
	.put = mixer_bass_treble_put,
	.निजी_value = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mixer_treble_control =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Synth Tone Control - Treble",
	.info = mixer_bass_treble_info,
	.get = mixer_bass_treble_get,
	.put = mixer_bass_treble_put,
	.निजी_value = 1,
पूर्ण;

/*
 * chorus/reverb mode
 */
अटल पूर्णांक mixer_chorus_reverb_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = kcontrol->निजी_value ? (SNDRV_EMU8000_CHORUS_NUMBERS-1) : (SNDRV_EMU8000_REVERB_NUMBERS-1);
	वापस 0;
पूर्ण

अटल पूर्णांक mixer_chorus_reverb_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu8000 *emu = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] = kcontrol->निजी_value ? emu->chorus_mode : emu->reverb_mode;
	वापस 0;
पूर्ण

अटल पूर्णांक mixer_chorus_reverb_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu8000 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित लघु val1;
	
	spin_lock_irqsave(&emu->control_lock, flags);
	अगर (kcontrol->निजी_value) अणु
		val1 = ucontrol->value.पूर्णांकeger.value[0] % SNDRV_EMU8000_CHORUS_NUMBERS;
		change = val1 != emu->chorus_mode;
		emu->chorus_mode = val1;
	पूर्ण अन्यथा अणु
		val1 = ucontrol->value.पूर्णांकeger.value[0] % SNDRV_EMU8000_REVERB_NUMBERS;
		change = val1 != emu->reverb_mode;
		emu->reverb_mode = val1;
	पूर्ण
	spin_unlock_irqrestore(&emu->control_lock, flags);
	अगर (change) अणु
		अगर (kcontrol->निजी_value)
			snd_emu8000_update_chorus_mode(emu);
		अन्यथा
			snd_emu8000_update_reverb_mode(emu);
	पूर्ण
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mixer_chorus_mode_control =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Chorus Mode",
	.info = mixer_chorus_reverb_info,
	.get = mixer_chorus_reverb_get,
	.put = mixer_chorus_reverb_put,
	.निजी_value = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mixer_reverb_mode_control =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Reverb Mode",
	.info = mixer_chorus_reverb_info,
	.get = mixer_chorus_reverb_get,
	.put = mixer_chorus_reverb_put,
	.निजी_value = 0,
पूर्ण;

/*
 * FM OPL3 chorus/reverb depth
 */
अटल पूर्णांक mixer_fm_depth_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक mixer_fm_depth_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu8000 *emu = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] = kcontrol->निजी_value ? emu->fm_chorus_depth : emu->fm_reverb_depth;
	वापस 0;
पूर्ण

अटल पूर्णांक mixer_fm_depth_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu8000 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित लघु val1;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] % 256;
	spin_lock_irqsave(&emu->control_lock, flags);
	अगर (kcontrol->निजी_value) अणु
		change = val1 != emu->fm_chorus_depth;
		emu->fm_chorus_depth = val1;
	पूर्ण अन्यथा अणु
		change = val1 != emu->fm_reverb_depth;
		emu->fm_reverb_depth = val1;
	पूर्ण
	spin_unlock_irqrestore(&emu->control_lock, flags);
	अगर (change)
		snd_emu8000_init_fm(emu);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mixer_fm_chorus_depth_control =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "FM Chorus Depth",
	.info = mixer_fm_depth_info,
	.get = mixer_fm_depth_get,
	.put = mixer_fm_depth_put,
	.निजी_value = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mixer_fm_reverb_depth_control =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "FM Reverb Depth",
	.info = mixer_fm_depth_info,
	.get = mixer_fm_depth_get,
	.put = mixer_fm_depth_put,
	.निजी_value = 0,
पूर्ण;


अटल स्थिर काष्ठा snd_kcontrol_new *mixer_defs[EMU8000_NUM_CONTROLS] = अणु
	&mixer_bass_control,
	&mixer_treble_control,
	&mixer_chorus_mode_control,
	&mixer_reverb_mode_control,
	&mixer_fm_chorus_depth_control,
	&mixer_fm_reverb_depth_control,
पूर्ण;

/*
 * create and attach mixer elements क्रम WaveTable treble/bass controls
 */
अटल पूर्णांक
snd_emu8000_create_mixer(काष्ठा snd_card *card, काष्ठा snd_emu8000 *emu)
अणु
	पूर्णांक i, err = 0;

	अगर (snd_BUG_ON(!emu || !card))
		वापस -EINVAL;

	spin_lock_init(&emu->control_lock);

	स_रखो(emu->controls, 0, माप(emu->controls));
	क्रम (i = 0; i < EMU8000_NUM_CONTROLS; i++) अणु
		अगर ((err = snd_ctl_add(card, emu->controls[i] = snd_ctl_new1(mixer_defs[i], emu))) < 0) अणु
			emu->controls[i] = शून्य;
			जाओ __error;
		पूर्ण
	पूर्ण
	वापस 0;

__error:
	क्रम (i = 0; i < EMU8000_NUM_CONTROLS; i++) अणु
		करोwn_ग_लिखो(&card->controls_rwsem);
		अगर (emu->controls[i])
			snd_ctl_हटाओ(card, emu->controls[i]);
		up_ग_लिखो(&card->controls_rwsem);
	पूर्ण
	वापस err;
पूर्ण


/*
 * मुक्त resources
 */
अटल पूर्णांक snd_emu8000_मुक्त(काष्ठा snd_emu8000 *hw)
अणु
	release_and_मुक्त_resource(hw->res_port1);
	release_and_मुक्त_resource(hw->res_port2);
	release_and_मुक्त_resource(hw->res_port3);
	kमुक्त(hw);
	वापस 0;
पूर्ण

/*
 */
अटल पूर्णांक snd_emu8000_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_emu8000 *hw = device->device_data;
	वापस snd_emu8000_मुक्त(hw);
पूर्ण

/*
 * initialize and रेजिस्टर emu8000 synth device.
 */
पूर्णांक
snd_emu8000_new(काष्ठा snd_card *card, पूर्णांक index, दीर्घ port, पूर्णांक seq_ports,
		काष्ठा snd_seq_device **awe_ret)
अणु
	काष्ठा snd_seq_device *awe;
	काष्ठा snd_emu8000 *hw;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_emu8000_dev_मुक्त,
	पूर्ण;

	अगर (awe_ret)
		*awe_ret = शून्य;

	अगर (seq_ports <= 0)
		वापस 0;

	hw = kzalloc(माप(*hw), GFP_KERNEL);
	अगर (hw == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&hw->reg_lock);
	hw->index = index;
	hw->port1 = port;
	hw->port2 = port + 0x400;
	hw->port3 = port + 0x800;
	अगर (!(hw->res_port1 = request_region(hw->port1, 4, "Emu8000-1")) ||
	    !(hw->res_port2 = request_region(hw->port2, 4, "Emu8000-2")) ||
	    !(hw->res_port3 = request_region(hw->port3, 4, "Emu8000-3"))) अणु
		snd_prपूर्णांकk(KERN_ERR "sbawe: can't grab ports 0x%lx, 0x%lx, 0x%lx\n", hw->port1, hw->port2, hw->port3);
		snd_emu8000_मुक्त(hw);
		वापस -EBUSY;
	पूर्ण
	hw->mem_size = 0;
	hw->card = card;
	hw->seq_ports = seq_ports;
	hw->bass_level = 5;
	hw->treble_level = 9;
	hw->chorus_mode = 2;
	hw->reverb_mode = 4;
	hw->fm_chorus_depth = 0;
	hw->fm_reverb_depth = 0;

	अगर (snd_emu8000_detect(hw) < 0) अणु
		snd_emu8000_मुक्त(hw);
		वापस -ENODEV;
	पूर्ण

	snd_emu8000_init_hw(hw);
	अगर ((err = snd_emu8000_create_mixer(card, hw)) < 0) अणु
		snd_emu8000_मुक्त(hw);
		वापस err;
	पूर्ण
	
	अगर ((err = snd_device_new(card, SNDRV_DEV_CODEC, hw, &ops)) < 0) अणु
		snd_emu8000_मुक्त(hw);
		वापस err;
	पूर्ण
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
	अगर (snd_seq_device_new(card, index, SNDRV_SEQ_DEV_ID_EMU8000,
			       माप(काष्ठा snd_emu8000*), &awe) >= 0) अणु
		म_नकल(awe->name, "EMU-8000");
		*(काष्ठा snd_emu8000 **)SNDRV_SEQ_DEVICE_ARGPTR(awe) = hw;
	पूर्ण
#अन्यथा
	awe = शून्य;
#पूर्ण_अगर
	अगर (awe_ret)
		*awe_ret = awe;

	वापस 0;
पूर्ण


/*
 * exported stuff
 */

EXPORT_SYMBOL(snd_emu8000_poke);
EXPORT_SYMBOL(snd_emu8000_peek);
EXPORT_SYMBOL(snd_emu8000_poke_dw);
EXPORT_SYMBOL(snd_emu8000_peek_dw);
EXPORT_SYMBOL(snd_emu8000_dma_chan);
EXPORT_SYMBOL(snd_emu8000_init_fm);
EXPORT_SYMBOL(snd_emu8000_load_chorus_fx);
EXPORT_SYMBOL(snd_emu8000_load_reverb_fx);
EXPORT_SYMBOL(snd_emu8000_update_chorus_mode);
EXPORT_SYMBOL(snd_emu8000_update_reverb_mode);
EXPORT_SYMBOL(snd_emu8000_update_equalizer);
