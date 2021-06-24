<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Sound Core PDAudioCF soundcard
 *
 * Copyright (c) 2003 by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/core.h>
#समावेश "pdaudiocf.h"
#समावेश <sound/initval.h>
#समावेश <यंत्र/irq_regs.h>

/*
 *
 */
irqवापस_t pdacf_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा snd_pdacf *chip = dev;
	अचिन्हित लघु stat;
	bool wake_thपढ़ो = false;

	अगर ((chip->chip_status & (PDAUDIOCF_STAT_IS_STALE|
				  PDAUDIOCF_STAT_IS_CONFIGURED|
				  PDAUDIOCF_STAT_IS_SUSPENDED)) != PDAUDIOCF_STAT_IS_CONFIGURED)
		वापस IRQ_HANDLED;	/* IRQ_NONE here? */

	stat = inw(chip->port + PDAUDIOCF_REG_ISR);
	अगर (stat & (PDAUDIOCF_IRQLVL|PDAUDIOCF_IRQOVR)) अणु
		अगर (stat & PDAUDIOCF_IRQOVR)	/* should never happen */
			snd_prपूर्णांकk(KERN_ERR "PDAUDIOCF SRAM buffer overrun detected!\n");
		अगर (chip->pcm_substream)
			wake_thपढ़ो = true;
		अगर (!(stat & PDAUDIOCF_IRQAKM))
			stat |= PDAUDIOCF_IRQAKM;	/* check rate */
	पूर्ण
	अगर (get_irq_regs() != शून्य)
		snd_ak4117_check_rate_and_errors(chip->ak4117, 0);
	वापस wake_thपढ़ो ? IRQ_WAKE_THREAD : IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_mono16(u16 *dst, u16 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	जबतक (size-- > 0) अणु
		*dst++ = inw(rdp_port) ^ xor;
		inw(rdp_port);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_mono32(u32 *dst, u32 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	रेजिस्टर u16 val1, val2;

	जबतक (size-- > 0) अणु
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		inw(rdp_port);
		*dst++ = ((((u32)val2 & 0xff) << 24) | ((u32)val1 << 8)) ^ xor;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_stereo16(u16 *dst, u16 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	जबतक (size-- > 0) अणु
		*dst++ = inw(rdp_port) ^ xor;
		*dst++ = inw(rdp_port) ^ xor;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_stereo32(u32 *dst, u32 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	रेजिस्टर u16 val1, val2, val3;

	जबतक (size-- > 0) अणु
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		val3 = inw(rdp_port);
		*dst++ = ((((u32)val2 & 0xff) << 24) | ((u32)val1 << 8)) ^ xor;
		*dst++ = (((u32)val3 << 16) | (val2 & 0xff00)) ^ xor;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_mono16sw(u16 *dst, u16 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	जबतक (size-- > 0) अणु
		*dst++ = swab16(inw(rdp_port) ^ xor);
		inw(rdp_port);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_mono32sw(u32 *dst, u32 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	रेजिस्टर u16 val1, val2;

	जबतक (size-- > 0) अणु
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		inw(rdp_port);
		*dst++ = swab32((((val2 & 0xff) << 24) | ((u32)val1 << 8)) ^ xor);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_stereo16sw(u16 *dst, u16 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	जबतक (size-- > 0) अणु
		*dst++ = swab16(inw(rdp_port) ^ xor);
		*dst++ = swab16(inw(rdp_port) ^ xor);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_stereo32sw(u32 *dst, u32 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	रेजिस्टर u16 val1, val2, val3;

	जबतक (size-- > 0) अणु
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		val3 = inw(rdp_port);
		*dst++ = swab32((((val2 & 0xff) << 24) | ((u32)val1 << 8)) ^ xor);
		*dst++ = swab32((((u32)val3 << 16) | (val2 & 0xff00)) ^ xor);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_mono24le(u8 *dst, u16 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	रेजिस्टर u16 val1, val2;
	रेजिस्टर u32 xval1;

	जबतक (size-- > 0) अणु
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		inw(rdp_port);
		xval1 = (((val2 & 0xff) << 8) | (val1 << 16)) ^ xor;
		*dst++ = (u8)(xval1 >> 8);
		*dst++ = (u8)(xval1 >> 16);
		*dst++ = (u8)(xval1 >> 24);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_mono24be(u8 *dst, u16 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	रेजिस्टर u16 val1, val2;
	रेजिस्टर u32 xval1;

	जबतक (size-- > 0) अणु
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		inw(rdp_port);
		xval1 = (((val2 & 0xff) << 8) | (val1 << 16)) ^ xor;
		*dst++ = (u8)(xval1 >> 24);
		*dst++ = (u8)(xval1 >> 16);
		*dst++ = (u8)(xval1 >> 8);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_stereo24le(u8 *dst, u32 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	रेजिस्टर u16 val1, val2, val3;
	रेजिस्टर u32 xval1, xval2;

	जबतक (size-- > 0) अणु
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		val3 = inw(rdp_port);
		xval1 = ((((u32)val2 & 0xff) << 24) | ((u32)val1 << 8)) ^ xor;
		xval2 = (((u32)val3 << 16) | (val2 & 0xff00)) ^ xor;
		*dst++ = (u8)(xval1 >> 8);
		*dst++ = (u8)(xval1 >> 16);
		*dst++ = (u8)(xval1 >> 24);
		*dst++ = (u8)(xval2 >> 8);
		*dst++ = (u8)(xval2 >> 16);
		*dst++ = (u8)(xval2 >> 24);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pdacf_transfer_stereo24be(u8 *dst, u32 xor, अचिन्हित पूर्णांक size, अचिन्हित दीर्घ rdp_port)
अणु
	रेजिस्टर u16 val1, val2, val3;
	रेजिस्टर u32 xval1, xval2;

	जबतक (size-- > 0) अणु
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		val3 = inw(rdp_port);
		xval1 = ((((u32)val2 & 0xff) << 24) | ((u32)val1 << 8)) ^ xor;
		xval2 = (((u32)val3 << 16) | (val2 & 0xff00)) ^ xor;
		*dst++ = (u8)(xval1 >> 24);
		*dst++ = (u8)(xval1 >> 16);
		*dst++ = (u8)(xval1 >> 8);
		*dst++ = (u8)(xval2 >> 24);
		*dst++ = (u8)(xval2 >> 16);
		*dst++ = (u8)(xval2 >> 8);
	पूर्ण
पूर्ण

अटल व्योम pdacf_transfer(काष्ठा snd_pdacf *chip, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक off)
अणु
	अचिन्हित दीर्घ rdp_port = chip->port + PDAUDIOCF_REG_MD;
	अचिन्हित पूर्णांक xor = chip->pcm_xor;

	अगर (chip->pcm_sample == 3) अणु
		अगर (chip->pcm_little) अणु
			अगर (chip->pcm_channels == 1) अणु
				pdacf_transfer_mono24le((अक्षर *)chip->pcm_area + (off * 3), xor, size, rdp_port);
			पूर्ण अन्यथा अणु
				pdacf_transfer_stereo24le((अक्षर *)chip->pcm_area + (off * 6), xor, size, rdp_port);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (chip->pcm_channels == 1) अणु
				pdacf_transfer_mono24be((अक्षर *)chip->pcm_area + (off * 3), xor, size, rdp_port);
			पूर्ण अन्यथा अणु
				pdacf_transfer_stereo24be((अक्षर *)chip->pcm_area + (off * 6), xor, size, rdp_port);
			पूर्ण			
		पूर्ण
		वापस;
	पूर्ण
	अगर (chip->pcm_swab == 0) अणु
		अगर (chip->pcm_channels == 1) अणु
			अगर (chip->pcm_frame == 2) अणु
				pdacf_transfer_mono16((u16 *)chip->pcm_area + off, xor, size, rdp_port);
			पूर्ण अन्यथा अणु
				pdacf_transfer_mono32((u32 *)chip->pcm_area + off, xor, size, rdp_port);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (chip->pcm_frame == 2) अणु
				pdacf_transfer_stereo16((u16 *)chip->pcm_area + (off * 2), xor, size, rdp_port);
			पूर्ण अन्यथा अणु
				pdacf_transfer_stereo32((u32 *)chip->pcm_area + (off * 2), xor, size, rdp_port);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->pcm_channels == 1) अणु
			अगर (chip->pcm_frame == 2) अणु
				pdacf_transfer_mono16sw((u16 *)chip->pcm_area + off, xor, size, rdp_port);
			पूर्ण अन्यथा अणु
				pdacf_transfer_mono32sw((u32 *)chip->pcm_area + off, xor, size, rdp_port);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (chip->pcm_frame == 2) अणु
				pdacf_transfer_stereo16sw((u16 *)chip->pcm_area + (off * 2), xor, size, rdp_port);
			पूर्ण अन्यथा अणु
				pdacf_transfer_stereo32sw((u32 *)chip->pcm_area + (off * 2), xor, size, rdp_port);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

irqवापस_t pdacf_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा snd_pdacf *chip = dev;
	पूर्णांक size, off, cont, rdp, wdp;

	अगर ((chip->chip_status & (PDAUDIOCF_STAT_IS_STALE|PDAUDIOCF_STAT_IS_CONFIGURED)) != PDAUDIOCF_STAT_IS_CONFIGURED)
		वापस IRQ_HANDLED;
	
	अगर (chip->pcm_substream == शून्य || chip->pcm_substream->runसमय == शून्य || !snd_pcm_running(chip->pcm_substream))
		वापस IRQ_HANDLED;

	rdp = inw(chip->port + PDAUDIOCF_REG_RDP);
	wdp = inw(chip->port + PDAUDIOCF_REG_WDP);
	/* prपूर्णांकk(KERN_DEBUG "TASKLET: rdp = %x, wdp = %x\n", rdp, wdp); */
	size = wdp - rdp;
	अगर (size < 0)
		size += 0x10000;
	अगर (size == 0)
		size = 0x10000;
	size /= chip->pcm_frame;
	अगर (size > 64)
		size -= 32;

#अगर 0
	chip->pcm_hwptr += size;
	chip->pcm_hwptr %= chip->pcm_size;
	chip->pcm_tकरोne += size;
	अगर (chip->pcm_frame == 2) अणु
		अचिन्हित दीर्घ rdp_port = chip->port + PDAUDIOCF_REG_MD;
		जबतक (size-- > 0) अणु
			inw(rdp_port);
			inw(rdp_port);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ rdp_port = chip->port + PDAUDIOCF_REG_MD;
		जबतक (size-- > 0) अणु
			inw(rdp_port);
			inw(rdp_port);
			inw(rdp_port);
		पूर्ण
	पूर्ण
#अन्यथा
	off = chip->pcm_hwptr + chip->pcm_tकरोne;
	off %= chip->pcm_size;
	chip->pcm_tकरोne += size;
	जबतक (size > 0) अणु
		cont = chip->pcm_size - off;
		अगर (cont > size)
			cont = size;
		pdacf_transfer(chip, cont, off);
		off += cont;
		off %= chip->pcm_size;
		size -= cont;
	पूर्ण
#पूर्ण_अगर
	mutex_lock(&chip->reg_lock);
	जबतक (chip->pcm_tकरोne >= chip->pcm_period) अणु
		chip->pcm_hwptr += chip->pcm_period;
		chip->pcm_hwptr %= chip->pcm_size;
		chip->pcm_tकरोne -= chip->pcm_period;
		mutex_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(chip->pcm_substream);
		mutex_lock(&chip->reg_lock);
	पूर्ण
	mutex_unlock(&chip->reg_lock);
	वापस IRQ_HANDLED;
पूर्ण
