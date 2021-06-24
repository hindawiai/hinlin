<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  I/O routines क्रम GF1/InterWave synthesizer chips
 */

#समावेश <linux/delay.h>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>

व्योम snd_gf1_delay(काष्ठा snd_gus_card * gus)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		mb();
		inb(GUSP(gus, DRAM));
	पूर्ण
पूर्ण

/*
 *  =======================================================================
 */

/*
 *  ok.. stop of control रेजिस्टरs (wave & ramp) need some special things..
 *       big UltraClick (पंचांग) elimination...
 */

अटल अंतरभूत व्योम __snd_gf1_ctrl_stop(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर value;

	outb(reg | 0x80, gus->gf1.reg_regsel);
	mb();
	value = inb(gus->gf1.reg_data8);
	mb();
	outb(reg, gus->gf1.reg_regsel);
	mb();
	outb((value | 0x03) & ~(0x80 | 0x20), gus->gf1.reg_data8);
	mb();
पूर्ण

अटल अंतरभूत व्योम __snd_gf1_ग_लिखो8(काष्ठा snd_gus_card * gus,
				    अचिन्हित अक्षर reg,
				    अचिन्हित अक्षर data)
अणु
	outb(reg, gus->gf1.reg_regsel);
	mb();
	outb(data, gus->gf1.reg_data8);
	mb();
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर __snd_gf1_look8(काष्ठा snd_gus_card * gus,
					    अचिन्हित अक्षर reg)
अणु
	outb(reg, gus->gf1.reg_regsel);
	mb();
	वापस inb(gus->gf1.reg_data8);
पूर्ण

अटल अंतरभूत व्योम __snd_gf1_ग_लिखो16(काष्ठा snd_gus_card * gus,
				     अचिन्हित अक्षर reg, अचिन्हित पूर्णांक data)
अणु
	outb(reg, gus->gf1.reg_regsel);
	mb();
	outw((अचिन्हित लघु) data, gus->gf1.reg_data16);
	mb();
पूर्ण

अटल अंतरभूत अचिन्हित लघु __snd_gf1_look16(काष्ठा snd_gus_card * gus,
					      अचिन्हित अक्षर reg)
अणु
	outb(reg, gus->gf1.reg_regsel);
	mb();
	वापस inw(gus->gf1.reg_data16);
पूर्ण

अटल अंतरभूत व्योम __snd_gf1_adlib_ग_लिखो(काष्ठा snd_gus_card * gus,
					 अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	outb(reg, gus->gf1.reg_समयrctrl);
	inb(gus->gf1.reg_समयrctrl);
	inb(gus->gf1.reg_समयrctrl);
	outb(data, gus->gf1.reg_समयrdata);
	inb(gus->gf1.reg_समयrctrl);
	inb(gus->gf1.reg_समयrctrl);
पूर्ण

अटल अंतरभूत व्योम __snd_gf1_ग_लिखो_addr(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg,
                                        अचिन्हित पूर्णांक addr, पूर्णांक w_16bit)
अणु
	अगर (gus->gf1.enh_mode) अणु
		अगर (w_16bit)
			addr = ((addr >> 1) & ~0x0000000f) | (addr & 0x0000000f);
		__snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_UPPER_ADDRESS, (अचिन्हित अक्षर) ((addr >> 26) & 0x03));
	पूर्ण अन्यथा अगर (w_16bit)
		addr = (addr & 0x00c0000f) | ((addr & 0x003ffff0) >> 1);
	__snd_gf1_ग_लिखो16(gus, reg, (अचिन्हित लघु) (addr >> 11));
	__snd_gf1_ग_लिखो16(gus, reg + 1, (अचिन्हित लघु) (addr << 5));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __snd_gf1_पढ़ो_addr(काष्ठा snd_gus_card * gus,
					       अचिन्हित अक्षर reg, लघु w_16bit)
अणु
	अचिन्हित पूर्णांक res;

	res = ((अचिन्हित पूर्णांक) __snd_gf1_look16(gus, reg | 0x80) << 11) & 0xfff800;
	res |= ((अचिन्हित पूर्णांक) __snd_gf1_look16(gus, (reg + 1) | 0x80) >> 5) & 0x0007ff;
	अगर (gus->gf1.enh_mode) अणु
		res |= (अचिन्हित पूर्णांक) __snd_gf1_look8(gus, SNDRV_GF1_VB_UPPER_ADDRESS | 0x80) << 26;
		अगर (w_16bit)
			res = ((res << 1) & 0xffffffe0) | (res & 0x0000000f);
	पूर्ण अन्यथा अगर (w_16bit)
		res = ((res & 0x001ffff0) << 1) | (res & 0x00c0000f);
	वापस res;
पूर्ण


/*
 *  =======================================================================
 */

व्योम snd_gf1_ctrl_stop(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	__snd_gf1_ctrl_stop(gus, reg);
पूर्ण

व्योम snd_gf1_ग_लिखो8(काष्ठा snd_gus_card * gus,
		    अचिन्हित अक्षर reg,
		    अचिन्हित अक्षर data)
अणु
	__snd_gf1_ग_लिखो8(gus, reg, data);
पूर्ण

अचिन्हित अक्षर snd_gf1_look8(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	वापस __snd_gf1_look8(gus, reg);
पूर्ण

व्योम snd_gf1_ग_लिखो16(काष्ठा snd_gus_card * gus,
		     अचिन्हित अक्षर reg,
		     अचिन्हित पूर्णांक data)
अणु
	__snd_gf1_ग_लिखो16(gus, reg, data);
पूर्ण

अचिन्हित लघु snd_gf1_look16(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	वापस __snd_gf1_look16(gus, reg);
पूर्ण

व्योम snd_gf1_adlib_ग_लिखो(काष्ठा snd_gus_card * gus,
                         अचिन्हित अक्षर reg,
                         अचिन्हित अक्षर data)
अणु
	__snd_gf1_adlib_ग_लिखो(gus, reg, data);
पूर्ण

व्योम snd_gf1_ग_लिखो_addr(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg,
                        अचिन्हित पूर्णांक addr, लघु w_16bit)
अणु
	__snd_gf1_ग_लिखो_addr(gus, reg, addr, w_16bit);
पूर्ण

अचिन्हित पूर्णांक snd_gf1_पढ़ो_addr(काष्ठा snd_gus_card * gus,
                               अचिन्हित अक्षर reg,
                               लघु w_16bit)
अणु
	वापस __snd_gf1_पढ़ो_addr(gus, reg, w_16bit);
पूर्ण

/*

 */

व्योम snd_gf1_i_ctrl_stop(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	__snd_gf1_ctrl_stop(gus, reg);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

व्योम snd_gf1_i_ग_लिखो8(काष्ठा snd_gus_card * gus,
		      अचिन्हित अक्षर reg,
                      अचिन्हित अक्षर data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	__snd_gf1_ग_लिखो8(gus, reg, data);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

अचिन्हित अक्षर snd_gf1_i_look8(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर res;

	spin_lock_irqsave(&gus->reg_lock, flags);
	res = __snd_gf1_look8(gus, reg);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस res;
पूर्ण

व्योम snd_gf1_i_ग_लिखो16(काष्ठा snd_gus_card * gus,
		       अचिन्हित अक्षर reg,
		       अचिन्हित पूर्णांक data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	__snd_gf1_ग_लिखो16(gus, reg, data);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

अचिन्हित लघु snd_gf1_i_look16(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु res;

	spin_lock_irqsave(&gus->reg_lock, flags);
	res = __snd_gf1_look16(gus, reg);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस res;
पूर्ण

#अगर 0

व्योम snd_gf1_i_adlib_ग_लिखो(काष्ठा snd_gus_card * gus,
		           अचिन्हित अक्षर reg,
		           अचिन्हित अक्षर data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	__snd_gf1_adlib_ग_लिखो(gus, reg, data);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

व्योम snd_gf1_i_ग_लिखो_addr(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg,
			  अचिन्हित पूर्णांक addr, लघु w_16bit)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	__snd_gf1_ग_लिखो_addr(gus, reg, addr, w_16bit);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

#पूर्ण_अगर  /*  0  */

#अगर_घोषित CONFIG_SND_DEBUG
अटल अचिन्हित पूर्णांक snd_gf1_i_पढ़ो_addr(काष्ठा snd_gus_card * gus,
					अचिन्हित अक्षर reg, लघु w_16bit)
अणु
	अचिन्हित पूर्णांक res;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	res = __snd_gf1_पढ़ो_addr(gus, reg, w_16bit);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस res;
पूर्ण
#पूर्ण_अगर

/*

 */

व्योम snd_gf1_dram_addr(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr)
अणु
	outb(0x43, gus->gf1.reg_regsel);
	mb();
	outw((अचिन्हित लघु) addr, gus->gf1.reg_data16);
	mb();
	outb(0x44, gus->gf1.reg_regsel);
	mb();
	outb((अचिन्हित अक्षर) (addr >> 16), gus->gf1.reg_data8);
	mb();
पूर्ण

व्योम snd_gf1_poke(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr, अचिन्हित अक्षर data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(SNDRV_GF1_GW_DRAM_IO_LOW, gus->gf1.reg_regsel);
	mb();
	outw((अचिन्हित लघु) addr, gus->gf1.reg_data16);
	mb();
	outb(SNDRV_GF1_GB_DRAM_IO_HIGH, gus->gf1.reg_regsel);
	mb();
	outb((अचिन्हित अक्षर) (addr >> 16), gus->gf1.reg_data8);
	mb();
	outb(data, gus->gf1.reg_dram);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

अचिन्हित अक्षर snd_gf1_peek(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर res;

	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(SNDRV_GF1_GW_DRAM_IO_LOW, gus->gf1.reg_regsel);
	mb();
	outw((अचिन्हित लघु) addr, gus->gf1.reg_data16);
	mb();
	outb(SNDRV_GF1_GB_DRAM_IO_HIGH, gus->gf1.reg_regsel);
	mb();
	outb((अचिन्हित अक्षर) (addr >> 16), gus->gf1.reg_data8);
	mb();
	res = inb(gus->gf1.reg_dram);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस res;
पूर्ण

#अगर 0

व्योम snd_gf1_pokew(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr, अचिन्हित लघु data)
अणु
	अचिन्हित दीर्घ flags;

#अगर_घोषित CONFIG_SND_DEBUG
	अगर (!gus->पूर्णांकerwave)
		snd_prपूर्णांकk(KERN_DEBUG "snd_gf1_pokew - GF1!!!\n");
#पूर्ण_अगर
	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(SNDRV_GF1_GW_DRAM_IO_LOW, gus->gf1.reg_regsel);
	mb();
	outw((अचिन्हित लघु) addr, gus->gf1.reg_data16);
	mb();
	outb(SNDRV_GF1_GB_DRAM_IO_HIGH, gus->gf1.reg_regsel);
	mb();
	outb((अचिन्हित अक्षर) (addr >> 16), gus->gf1.reg_data8);
	mb();
	outb(SNDRV_GF1_GW_DRAM_IO16, gus->gf1.reg_regsel);
	mb();
	outw(data, gus->gf1.reg_data16);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

अचिन्हित लघु snd_gf1_peekw(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु res;

#अगर_घोषित CONFIG_SND_DEBUG
	अगर (!gus->पूर्णांकerwave)
		snd_prपूर्णांकk(KERN_DEBUG "snd_gf1_peekw - GF1!!!\n");
#पूर्ण_अगर
	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(SNDRV_GF1_GW_DRAM_IO_LOW, gus->gf1.reg_regsel);
	mb();
	outw((अचिन्हित लघु) addr, gus->gf1.reg_data16);
	mb();
	outb(SNDRV_GF1_GB_DRAM_IO_HIGH, gus->gf1.reg_regsel);
	mb();
	outb((अचिन्हित अक्षर) (addr >> 16), gus->gf1.reg_data8);
	mb();
	outb(SNDRV_GF1_GW_DRAM_IO16, gus->gf1.reg_regsel);
	mb();
	res = inw(gus->gf1.reg_data16);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस res;
पूर्ण

व्योम snd_gf1_dram_seपंचांगem(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr,
			 अचिन्हित लघु value, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ port;
	अचिन्हित दीर्घ flags;

#अगर_घोषित CONFIG_SND_DEBUG
	अगर (!gus->पूर्णांकerwave)
		snd_prपूर्णांकk(KERN_DEBUG "snd_gf1_dram_setmem - GF1!!!\n");
#पूर्ण_अगर
	addr &= ~1;
	count >>= 1;
	port = GUSP(gus, GF1DATALOW);
	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(SNDRV_GF1_GW_DRAM_IO_LOW, gus->gf1.reg_regsel);
	mb();
	outw((अचिन्हित लघु) addr, gus->gf1.reg_data16);
	mb();
	outb(SNDRV_GF1_GB_DRAM_IO_HIGH, gus->gf1.reg_regsel);
	mb();
	outb((अचिन्हित अक्षर) (addr >> 16), gus->gf1.reg_data8);
	mb();
	outb(SNDRV_GF1_GW_DRAM_IO16, gus->gf1.reg_regsel);
	जबतक (count--)
		outw(value, port);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

#पूर्ण_अगर  /*  0  */

व्योम snd_gf1_select_active_voices(काष्ठा snd_gus_card * gus)
अणु
	अचिन्हित लघु voices;

	अटल स्थिर अचिन्हित लघु voices_tbl[32 - 14 + 1] =
	अणु
	    44100, 41160, 38587, 36317, 34300, 32494, 30870, 29400, 28063, 26843,
	    25725, 24696, 23746, 22866, 22050, 21289, 20580, 19916, 19293
	पूर्ण;

	voices = gus->gf1.active_voices;
	अगर (voices > 32)
		voices = 32;
	अगर (voices < 14)
		voices = 14;
	अगर (gus->gf1.enh_mode)
		voices = 32;
	gus->gf1.active_voices = voices;
	gus->gf1.playback_freq =
	    gus->gf1.enh_mode ? 44100 : voices_tbl[voices - 14];
	अगर (!gus->gf1.enh_mode) अणु
		snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_ACTIVE_VOICES, 0xc0 | (voices - 1));
		udelay(100);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG

व्योम snd_gf1_prपूर्णांक_voice_रेजिस्टरs(काष्ठा snd_gus_card * gus)
अणु
	अचिन्हित अक्षर mode;
	पूर्णांक voice, ctrl;

	voice = gus->gf1.active_voice;
	prपूर्णांकk(KERN_INFO " -%i- GF1  voice ctrl, ramp ctrl  = 0x%x, 0x%x\n", voice, ctrl = snd_gf1_i_पढ़ो8(gus, 0), snd_gf1_i_पढ़ो8(gus, 0x0d));
	prपूर्णांकk(KERN_INFO " -%i- GF1  frequency              = 0x%x\n", voice, snd_gf1_i_पढ़ो16(gus, 1));
	prपूर्णांकk(KERN_INFO " -%i- GF1  loop start, end        = 0x%x (0x%x), 0x%x (0x%x)\n", voice, snd_gf1_i_पढ़ो_addr(gus, 2, ctrl & 4), snd_gf1_i_पढ़ो_addr(gus, 2, (ctrl & 4) ^ 4), snd_gf1_i_पढ़ो_addr(gus, 4, ctrl & 4), snd_gf1_i_पढ़ो_addr(gus, 4, (ctrl & 4) ^ 4));
	prपूर्णांकk(KERN_INFO " -%i- GF1  ramp start, end, rate  = 0x%x, 0x%x, 0x%x\n", voice, snd_gf1_i_पढ़ो8(gus, 7), snd_gf1_i_पढ़ो8(gus, 8), snd_gf1_i_पढ़ो8(gus, 6));
	prपूर्णांकk(KERN_INFO" -%i- GF1  volume                 = 0x%x\n", voice, snd_gf1_i_पढ़ो16(gus, 9));
	prपूर्णांकk(KERN_INFO " -%i- GF1  position               = 0x%x (0x%x)\n", voice, snd_gf1_i_पढ़ो_addr(gus, 0x0a, ctrl & 4), snd_gf1_i_पढ़ो_addr(gus, 0x0a, (ctrl & 4) ^ 4));
	अगर (gus->पूर्णांकerwave && snd_gf1_i_पढ़ो8(gus, 0x19) & 0x01) अणु	/* enhanced mode */
		mode = snd_gf1_i_पढ़ो8(gus, 0x15);
		prपूर्णांकk(KERN_INFO " -%i- GFA1 mode                   = 0x%x\n", voice, mode);
		अगर (mode & 0x01) अणु	/* Effect processor */
			prपूर्णांकk(KERN_INFO " -%i- GFA1 effect address         = 0x%x\n", voice, snd_gf1_i_पढ़ो_addr(gus, 0x11, ctrl & 4));
			prपूर्णांकk(KERN_INFO " -%i- GFA1 effect volume          = 0x%x\n", voice, snd_gf1_i_पढ़ो16(gus, 0x16));
			prपूर्णांकk(KERN_INFO " -%i- GFA1 effect volume final    = 0x%x\n", voice, snd_gf1_i_पढ़ो16(gus, 0x1d));
			prपूर्णांकk(KERN_INFO " -%i- GFA1 effect accumulator     = 0x%x\n", voice, snd_gf1_i_पढ़ो8(gus, 0x14));
		पूर्ण
		अगर (mode & 0x20) अणु
			prपूर्णांकk(KERN_INFO " -%i- GFA1 left offset            = 0x%x (%i)\n", voice, snd_gf1_i_पढ़ो16(gus, 0x13), snd_gf1_i_पढ़ो16(gus, 0x13) >> 4);
			prपूर्णांकk(KERN_INFO " -%i- GFA1 left offset final      = 0x%x (%i)\n", voice, snd_gf1_i_पढ़ो16(gus, 0x1c), snd_gf1_i_पढ़ो16(gus, 0x1c) >> 4);
			prपूर्णांकk(KERN_INFO " -%i- GFA1 right offset           = 0x%x (%i)\n", voice, snd_gf1_i_पढ़ो16(gus, 0x0c), snd_gf1_i_पढ़ो16(gus, 0x0c) >> 4);
			prपूर्णांकk(KERN_INFO " -%i- GFA1 right offset final     = 0x%x (%i)\n", voice, snd_gf1_i_पढ़ो16(gus, 0x1b), snd_gf1_i_पढ़ो16(gus, 0x1b) >> 4);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_INFO " -%i- GF1  pan                    = 0x%x\n", voice, snd_gf1_i_पढ़ो8(gus, 0x0c));
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO " -%i- GF1  pan                    = 0x%x\n", voice, snd_gf1_i_पढ़ो8(gus, 0x0c));
पूर्ण

#अगर 0

व्योम snd_gf1_prपूर्णांक_global_रेजिस्टरs(काष्ठा snd_gus_card * gus)
अणु
	अचिन्हित अक्षर global_mode = 0x00;

	prपूर्णांकk(KERN_INFO " -G- GF1 active voices            = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_ACTIVE_VOICES));
	अगर (gus->पूर्णांकerwave) अणु
		global_mode = snd_gf1_i_पढ़ो8(gus, SNDRV_GF1_GB_GLOBAL_MODE);
		prपूर्णांकk(KERN_INFO " -G- GF1 global mode              = 0x%x\n", global_mode);
	पूर्ण
	अगर (global_mode & 0x02)	/* LFO enabled? */
		prपूर्णांकk(KERN_INFO " -G- GF1 LFO base                 = 0x%x\n", snd_gf1_i_look16(gus, SNDRV_GF1_GW_LFO_BASE));
	prपूर्णांकk(KERN_INFO " -G- GF1 voices IRQ read          = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_VOICES_IRQ_READ));
	prपूर्णांकk(KERN_INFO " -G- GF1 DRAM DMA control         = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_DRAM_DMA_CONTROL));
	prपूर्णांकk(KERN_INFO " -G- GF1 DRAM DMA high/low        = 0x%x/0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_DRAM_DMA_HIGH), snd_gf1_i_पढ़ो16(gus, SNDRV_GF1_GW_DRAM_DMA_LOW));
	prपूर्णांकk(KERN_INFO " -G- GF1 DRAM IO high/low         = 0x%x/0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_DRAM_IO_HIGH), snd_gf1_i_पढ़ो16(gus, SNDRV_GF1_GW_DRAM_IO_LOW));
	अगर (!gus->पूर्णांकerwave)
		prपूर्णांकk(KERN_INFO " -G- GF1 record DMA control       = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL));
	prपूर्णांकk(KERN_INFO " -G- GF1 DRAM IO 16               = 0x%x\n", snd_gf1_i_look16(gus, SNDRV_GF1_GW_DRAM_IO16));
	अगर (gus->gf1.enh_mode) अणु
		prपूर्णांकk(KERN_INFO " -G- GFA1 memory config           = 0x%x\n", snd_gf1_i_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG));
		prपूर्णांकk(KERN_INFO " -G- GFA1 memory control          = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_MEMORY_CONTROL));
		prपूर्णांकk(KERN_INFO " -G- GFA1 FIFO record base        = 0x%x\n", snd_gf1_i_look16(gus, SNDRV_GF1_GW_FIFO_RECORD_BASE_ADDR));
		prपूर्णांकk(KERN_INFO " -G- GFA1 FIFO playback base      = 0x%x\n", snd_gf1_i_look16(gus, SNDRV_GF1_GW_FIFO_PLAY_BASE_ADDR));
		prपूर्णांकk(KERN_INFO " -G- GFA1 interleave control      = 0x%x\n", snd_gf1_i_look16(gus, SNDRV_GF1_GW_INTERLEAVE));
	पूर्ण
पूर्ण

व्योम snd_gf1_prपूर्णांक_setup_रेजिस्टरs(काष्ठा snd_gus_card * gus)
अणु
	prपूर्णांकk(KERN_INFO " -S- mix control                  = 0x%x\n", inb(GUSP(gus, MIXCNTRLREG)));
	prपूर्णांकk(KERN_INFO " -S- IRQ status                   = 0x%x\n", inb(GUSP(gus, IRQSTAT)));
	prपूर्णांकk(KERN_INFO " -S- timer control                = 0x%x\n", inb(GUSP(gus, TIMERCNTRL)));
	prपूर्णांकk(KERN_INFO " -S- timer data                   = 0x%x\n", inb(GUSP(gus, TIMERDATA)));
	prपूर्णांकk(KERN_INFO " -S- status read                  = 0x%x\n", inb(GUSP(gus, REGCNTRLS)));
	prपूर्णांकk(KERN_INFO " -S- Sound Blaster control        = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL));
	prपूर्णांकk(KERN_INFO " -S- AdLib timer 1/2              = 0x%x/0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_ADLIB_TIMER_1), snd_gf1_i_look8(gus, SNDRV_GF1_GB_ADLIB_TIMER_2));
	prपूर्णांकk(KERN_INFO " -S- reset                        = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET));
	अगर (gus->पूर्णांकerwave) अणु
		prपूर्णांकk(KERN_INFO " -S- compatibility                = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_COMPATIBILITY));
		prपूर्णांकk(KERN_INFO " -S- decode control               = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_DECODE_CONTROL));
		prपूर्णांकk(KERN_INFO " -S- version number               = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_VERSION_NUMBER));
		prपूर्णांकk(KERN_INFO " -S- MPU-401 emul. control A/B    = 0x%x/0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_MPU401_CONTROL_A), snd_gf1_i_look8(gus, SNDRV_GF1_GB_MPU401_CONTROL_B));
		prपूर्णांकk(KERN_INFO " -S- emulation IRQ                = 0x%x\n", snd_gf1_i_look8(gus, SNDRV_GF1_GB_EMULATION_IRQ));
	पूर्ण
पूर्ण

व्योम snd_gf1_peek_prपूर्णांक_block(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr, पूर्णांक count, पूर्णांक w_16bit)
अणु
	अगर (!w_16bit) अणु
		जबतक (count-- > 0)
			prपूर्णांकk(count > 0 ? "%02x:" : "%02x", snd_gf1_peek(gus, addr++));
	पूर्ण अन्यथा अणु
		जबतक (count-- > 0) अणु
			prपूर्णांकk(count > 0 ? "%04x:" : "%04x", snd_gf1_peek(gus, addr) | (snd_gf1_peek(gus, addr + 1) << 8));
			addr += 2;
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर  /*  0  */

#पूर्ण_अगर
