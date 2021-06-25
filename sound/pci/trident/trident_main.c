<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Maपूर्णांकained by Jaroslav Kysela <perex@perex.cz>
 *  Originated by audio@tridenपंचांगicro.com
 *  Fri Feb 19 15:55:28 MST 1999
 *  Routines क्रम control of Trident 4DWave (DX and NX) chip
 *
 *  BUGS:
 *
 *  TODO:
 *    ---
 *
 *  SiS7018 S/PDIF support by Thomas Winischhofer <thomas@winischhofer.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/gameport.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश "trident.h"
#समावेश <sound/asoundef.h>

अटल पूर्णांक snd_trident_pcm_mixer_build(काष्ठा snd_trident *trident,
				       काष्ठा snd_trident_voice * voice,
				       काष्ठा snd_pcm_substream *substream);
अटल पूर्णांक snd_trident_pcm_mixer_मुक्त(काष्ठा snd_trident *trident,
				      काष्ठा snd_trident_voice * voice,
				      काष्ठा snd_pcm_substream *substream);
अटल irqवापस_t snd_trident_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक snd_trident_sis_reset(काष्ठा snd_trident *trident);

अटल व्योम snd_trident_clear_voices(काष्ठा snd_trident * trident,
				     अचिन्हित लघु v_min, अचिन्हित लघु v_max);
अटल पूर्णांक snd_trident_मुक्त(काष्ठा snd_trident *trident);

/*
 *  common I/O routines
 */


#अगर 0
अटल व्योम snd_trident_prपूर्णांक_voice_regs(काष्ठा snd_trident *trident, पूर्णांक voice)
अणु
	अचिन्हित पूर्णांक val, पंचांगp;

	dev_dbg(trident->card->dev, "Trident voice %i:\n", voice);
	outb(voice, TRID_REG(trident, T4D_LFO_GC_CIR));
	val = inl(TRID_REG(trident, CH_LBA));
	dev_dbg(trident->card->dev, "LBA: 0x%x\n", val);
	val = inl(TRID_REG(trident, CH_GVSEL_PAN_VOL_CTRL_EC));
	dev_dbg(trident->card->dev, "GVSel: %i\n", val >> 31);
	dev_dbg(trident->card->dev, "Pan: 0x%x\n", (val >> 24) & 0x7f);
	dev_dbg(trident->card->dev, "Vol: 0x%x\n", (val >> 16) & 0xff);
	dev_dbg(trident->card->dev, "CTRL: 0x%x\n", (val >> 12) & 0x0f);
	dev_dbg(trident->card->dev, "EC: 0x%x\n", val & 0x0fff);
	अगर (trident->device != TRIDENT_DEVICE_ID_NX) अणु
		val = inl(TRID_REG(trident, CH_DX_CSO_ALPHA_FMS));
		dev_dbg(trident->card->dev, "CSO: 0x%x\n", val >> 16);
		dev_dbg(trident->card->dev, "Alpha: 0x%x\n", (val >> 4) & 0x0fff);
		dev_dbg(trident->card->dev, "FMS: 0x%x\n", val & 0x0f);
		val = inl(TRID_REG(trident, CH_DX_ESO_DELTA));
		dev_dbg(trident->card->dev, "ESO: 0x%x\n", val >> 16);
		dev_dbg(trident->card->dev, "Delta: 0x%x\n", val & 0xffff);
		val = inl(TRID_REG(trident, CH_DX_FMC_RVOL_CVOL));
	पूर्ण अन्यथा अणु		// TRIDENT_DEVICE_ID_NX
		val = inl(TRID_REG(trident, CH_NX_DELTA_CSO));
		पंचांगp = (val >> 24) & 0xff;
		dev_dbg(trident->card->dev, "CSO: 0x%x\n", val & 0x00ffffff);
		val = inl(TRID_REG(trident, CH_NX_DELTA_ESO));
		पंचांगp |= (val >> 16) & 0xff00;
		dev_dbg(trident->card->dev, "Delta: 0x%x\n", पंचांगp);
		dev_dbg(trident->card->dev, "ESO: 0x%x\n", val & 0x00ffffff);
		val = inl(TRID_REG(trident, CH_NX_ALPHA_FMS_FMC_RVOL_CVOL));
		dev_dbg(trident->card->dev, "Alpha: 0x%x\n", val >> 20);
		dev_dbg(trident->card->dev, "FMS: 0x%x\n", (val >> 16) & 0x0f);
	पूर्ण
	dev_dbg(trident->card->dev, "FMC: 0x%x\n", (val >> 14) & 3);
	dev_dbg(trident->card->dev, "RVol: 0x%x\n", (val >> 7) & 0x7f);
	dev_dbg(trident->card->dev, "CVol: 0x%x\n", val & 0x7f);
पूर्ण
#पूर्ण_अगर

/*---------------------------------------------------------------------------
   अचिन्हित लघु snd_trident_codec_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
  
   Description: This routine will करो all of the पढ़ोing from the बाह्यal
                CODEC (AC97).
  
   Parameters:  ac97 - ac97 codec काष्ठाure
                reg - CODEC रेजिस्टर index, from AC97 Hal.
 
   वापसs:     16 bit value पढ़ो from the AC97.
  
  ---------------------------------------------------------------------------*/
अटल अचिन्हित लघु snd_trident_codec_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	अचिन्हित पूर्णांक data = 0, treg;
	अचिन्हित लघु count = 0xffff;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_trident *trident = ac97->निजी_data;

	spin_lock_irqsave(&trident->reg_lock, flags);
	अगर (trident->device == TRIDENT_DEVICE_ID_DX) अणु
		data = (DX_AC97_BUSY_READ | (reg & 0x000000ff));
		outl(data, TRID_REG(trident, DX_ACR1_AC97_R));
		करो अणु
			data = inl(TRID_REG(trident, DX_ACR1_AC97_R));
			अगर ((data & DX_AC97_BUSY_READ) == 0)
				अवरोध;
		पूर्ण जबतक (--count);
	पूर्ण अन्यथा अगर (trident->device == TRIDENT_DEVICE_ID_NX) अणु
		data = (NX_AC97_BUSY_READ | (reg & 0x000000ff));
		treg = ac97->num == 0 ? NX_ACR2_AC97_R_PRIMARY : NX_ACR3_AC97_R_SECONDARY;
		outl(data, TRID_REG(trident, treg));
		करो अणु
			data = inl(TRID_REG(trident, treg));
			अगर ((data & 0x00000C00) == 0)
				अवरोध;
		पूर्ण जबतक (--count);
	पूर्ण अन्यथा अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		data = SI_AC97_BUSY_READ | SI_AC97_AUDIO_BUSY | (reg & 0x000000ff);
		अगर (ac97->num == 1)
			data |= SI_AC97_SECONDARY;
		outl(data, TRID_REG(trident, SI_AC97_READ));
		करो अणु
			data = inl(TRID_REG(trident, SI_AC97_READ));
			अगर ((data & (SI_AC97_BUSY_READ)) == 0)
				अवरोध;
		पूर्ण जबतक (--count);
	पूर्ण

	अगर (count == 0 && !trident->ac97_detect) अणु
		dev_err(trident->card->dev,
			"ac97 codec read TIMEOUT [0x%x/0x%x]!!!\n",
			   reg, data);
		data = 0;
	पूर्ण

	spin_unlock_irqrestore(&trident->reg_lock, flags);
	वापस ((अचिन्हित लघु) (data >> 16));
पूर्ण

/*---------------------------------------------------------------------------
   व्योम snd_trident_codec_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
   अचिन्हित लघु wdata)
  
   Description: This routine will करो all of the writing to the बाह्यal
                CODEC (AC97).
  
   Parameters:	ac97 - ac97 codec काष्ठाure
   	        reg - CODEC रेजिस्टर index, from AC97 Hal.
                data  - Lower 16 bits are the data to ग_लिखो to CODEC.
  
   वापसs:     TRUE अगर everything went ok, अन्यथा FALSE.
  
  ---------------------------------------------------------------------------*/
अटल व्योम snd_trident_codec_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
				    अचिन्हित लघु wdata)
अणु
	अचिन्हित पूर्णांक address, data;
	अचिन्हित लघु count = 0xffff;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_trident *trident = ac97->निजी_data;

	data = ((अचिन्हित दीर्घ) wdata) << 16;

	spin_lock_irqsave(&trident->reg_lock, flags);
	अगर (trident->device == TRIDENT_DEVICE_ID_DX) अणु
		address = DX_ACR0_AC97_W;

		/* पढ़ो AC-97 ग_लिखो रेजिस्टर status */
		करो अणु
			अगर ((inw(TRID_REG(trident, address)) & DX_AC97_BUSY_WRITE) == 0)
				अवरोध;
		पूर्ण जबतक (--count);

		data |= (DX_AC97_BUSY_WRITE | (reg & 0x000000ff));
	पूर्ण अन्यथा अगर (trident->device == TRIDENT_DEVICE_ID_NX) अणु
		address = NX_ACR1_AC97_W;

		/* पढ़ो AC-97 ग_लिखो रेजिस्टर status */
		करो अणु
			अगर ((inw(TRID_REG(trident, address)) & NX_AC97_BUSY_WRITE) == 0)
				अवरोध;
		पूर्ण जबतक (--count);

		data |= (NX_AC97_BUSY_WRITE | (ac97->num << 8) | (reg & 0x000000ff));
	पूर्ण अन्यथा अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		address = SI_AC97_WRITE;

		/* पढ़ो AC-97 ग_लिखो रेजिस्टर status */
		करो अणु
			अगर ((inw(TRID_REG(trident, address)) & (SI_AC97_BUSY_WRITE)) == 0)
				अवरोध;
		पूर्ण जबतक (--count);

		data |= SI_AC97_BUSY_WRITE | SI_AC97_AUDIO_BUSY | (reg & 0x000000ff);
		अगर (ac97->num == 1)
			data |= SI_AC97_SECONDARY;
	पूर्ण अन्यथा अणु
		address = 0;	/* keep GCC happy */
		count = 0;	/* वापस */
	पूर्ण

	अगर (count == 0) अणु
		spin_unlock_irqrestore(&trident->reg_lock, flags);
		वापस;
	पूर्ण
	outl(data, TRID_REG(trident, address));
	spin_unlock_irqrestore(&trident->reg_lock, flags);
पूर्ण

/*---------------------------------------------------------------------------
   व्योम snd_trident_enable_eso(काष्ठा snd_trident *trident)
  
   Description: This routine will enable end of loop पूर्णांकerrupts.
                End of loop पूर्णांकerrupts will occur when a running
                channel reaches ESO.
                Also enables middle of loop पूर्णांकerrupts.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_enable_eso(काष्ठा snd_trident * trident)
अणु
	अचिन्हित पूर्णांक val;

	val = inl(TRID_REG(trident, T4D_LFO_GC_CIR));
	val |= ENDLP_IE;
	val |= MIDLP_IE;
	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018)
		val |= BANK_B_EN;
	outl(val, TRID_REG(trident, T4D_LFO_GC_CIR));
पूर्ण

/*---------------------------------------------------------------------------
   व्योम snd_trident_disable_eso(काष्ठा snd_trident *trident)
  
   Description: This routine will disable end of loop पूर्णांकerrupts.
                End of loop पूर्णांकerrupts will occur when a running
                channel reaches ESO.
                Also disables middle of loop पूर्णांकerrupts.
  
   Parameters:  
                trident - poपूर्णांकer to target device class क्रम 4DWave.
  
   वापसs:     TRUE अगर everything went ok, अन्यथा FALSE.
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_disable_eso(काष्ठा snd_trident * trident)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = inl(TRID_REG(trident, T4D_LFO_GC_CIR));
	पंचांगp &= ~ENDLP_IE;
	पंचांगp &= ~MIDLP_IE;
	outl(पंचांगp, TRID_REG(trident, T4D_LFO_GC_CIR));
पूर्ण

/*---------------------------------------------------------------------------
   व्योम snd_trident_start_voice(काष्ठा snd_trident * trident, अचिन्हित पूर्णांक voice)

    Description: Start a voice, any channel 0 thru 63.
                 This routine स्वतःmatically handles the fact that there are
                 more than 32 channels available.

    Parameters : voice - Voice number 0 thru n.
                 trident - poपूर्णांकer to target device class क्रम 4DWave.

    Return Value: None.

  ---------------------------------------------------------------------------*/

व्योम snd_trident_start_voice(काष्ठा snd_trident * trident, अचिन्हित पूर्णांक voice)
अणु
	अचिन्हित पूर्णांक mask = 1 << (voice & 0x1f);
	अचिन्हित पूर्णांक reg = (voice & 0x20) ? T4D_START_B : T4D_START_A;

	outl(mask, TRID_REG(trident, reg));
पूर्ण

EXPORT_SYMBOL(snd_trident_start_voice);

/*---------------------------------------------------------------------------
   व्योम snd_trident_stop_voice(काष्ठा snd_trident * trident, अचिन्हित पूर्णांक voice)

    Description: Stop a voice, any channel 0 thru 63.
                 This routine स्वतःmatically handles the fact that there are
                 more than 32 channels available.

    Parameters : voice - Voice number 0 thru n.
                 trident - poपूर्णांकer to target device class क्रम 4DWave.

    Return Value: None.

  ---------------------------------------------------------------------------*/

व्योम snd_trident_stop_voice(काष्ठा snd_trident * trident, अचिन्हित पूर्णांक voice)
अणु
	अचिन्हित पूर्णांक mask = 1 << (voice & 0x1f);
	अचिन्हित पूर्णांक reg = (voice & 0x20) ? T4D_STOP_B : T4D_STOP_A;

	outl(mask, TRID_REG(trident, reg));
पूर्ण

EXPORT_SYMBOL(snd_trident_stop_voice);

/*---------------------------------------------------------------------------
    पूर्णांक snd_trident_allocate_pcm_channel(काष्ठा snd_trident *trident)
  
    Description: Allocate hardware channel in Bank B (32-63).
  
    Parameters :  trident - poपूर्णांकer to target device class क्रम 4DWave.
  
    Return Value: hardware channel - 32-63 or -1 when no channel is available
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_allocate_pcm_channel(काष्ठा snd_trident * trident)
अणु
	पूर्णांक idx;

	अगर (trident->ChanPCMcnt >= trident->ChanPCM)
		वापस -1;
	क्रम (idx = 31; idx >= 0; idx--) अणु
		अगर (!(trident->ChanMap[T4D_BANK_B] & (1 << idx))) अणु
			trident->ChanMap[T4D_BANK_B] |= 1 << idx;
			trident->ChanPCMcnt++;
			वापस idx + 32;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

/*---------------------------------------------------------------------------
    व्योम snd_trident_मुक्त_pcm_channel(पूर्णांक channel)
  
    Description: Free hardware channel in Bank B (32-63)
  
    Parameters :  trident - poपूर्णांकer to target device class क्रम 4DWave.
	          channel - hardware channel number 0-63
  
    Return Value: none
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_मुक्त_pcm_channel(काष्ठा snd_trident *trident, पूर्णांक channel)
अणु
	अगर (channel < 32 || channel > 63)
		वापस;
	channel &= 0x1f;
	अगर (trident->ChanMap[T4D_BANK_B] & (1 << channel)) अणु
		trident->ChanMap[T4D_BANK_B] &= ~(1 << channel);
		trident->ChanPCMcnt--;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------
    अचिन्हित पूर्णांक snd_trident_allocate_synth_channel(व्योम)
  
    Description: Allocate hardware channel in Bank A (0-31).
  
    Parameters :  trident - poपूर्णांकer to target device class क्रम 4DWave.
  
    Return Value: hardware channel - 0-31 or -1 when no channel is available
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_allocate_synth_channel(काष्ठा snd_trident * trident)
अणु
	पूर्णांक idx;

	क्रम (idx = 31; idx >= 0; idx--) अणु
		अगर (!(trident->ChanMap[T4D_BANK_A] & (1 << idx))) अणु
			trident->ChanMap[T4D_BANK_A] |= 1 << idx;
			trident->synth.ChanSynthCount++;
			वापस idx;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

/*---------------------------------------------------------------------------
    व्योम snd_trident_मुक्त_synth_channel( पूर्णांक channel )
  
    Description: Free hardware channel in Bank B (0-31).
  
    Parameters :  trident - poपूर्णांकer to target device class क्रम 4DWave.
	          channel - hardware channel number 0-63
  
    Return Value: none
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_मुक्त_synth_channel(काष्ठा snd_trident *trident, पूर्णांक channel)
अणु
	अगर (channel < 0 || channel > 31)
		वापस;
	channel &= 0x1f;
	अगर (trident->ChanMap[T4D_BANK_A] & (1 << channel)) अणु
		trident->ChanMap[T4D_BANK_A] &= ~(1 << channel);
		trident->synth.ChanSynthCount--;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_ग_लिखो_voice_regs
  
   Description: This routine will complete and ग_लिखो the 5 hardware channel
                रेजिस्टरs to hardware.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                voice - synthesizer voice काष्ठाure
                Each रेजिस्टर field.
  
  ---------------------------------------------------------------------------*/

व्योम snd_trident_ग_लिखो_voice_regs(काष्ठा snd_trident * trident,
				  काष्ठा snd_trident_voice * voice)
अणु
	अचिन्हित पूर्णांक FmcRvolCvol;
	अचिन्हित पूर्णांक regs[5];

	regs[1] = voice->LBA;
	regs[4] = (voice->GVSel << 31) |
		  ((voice->Pan & 0x0000007f) << 24) |
		  ((voice->CTRL & 0x0000000f) << 12);
	FmcRvolCvol = ((voice->FMC & 3) << 14) |
	              ((voice->RVol & 0x7f) << 7) |
	              (voice->CVol & 0x7f);

	चयन (trident->device) अणु
	हाल TRIDENT_DEVICE_ID_SI7018:
		regs[4] |= voice->number > 31 ?
				(voice->Vol & 0x000003ff) :
				((voice->Vol & 0x00003fc) << (16-2)) |
				(voice->EC & 0x00000fff);
		regs[0] = (voice->CSO << 16) | ((voice->Alpha & 0x00000fff) << 4) |
			(voice->FMS & 0x0000000f);
		regs[2] = (voice->ESO << 16) | (voice->Delta & 0x0ffff);
		regs[3] = (voice->Attribute << 16) | FmcRvolCvol;
		अवरोध;
	हाल TRIDENT_DEVICE_ID_DX:
		regs[4] |= ((voice->Vol & 0x000003fc) << (16-2)) |
			   (voice->EC & 0x00000fff);
		regs[0] = (voice->CSO << 16) | ((voice->Alpha & 0x00000fff) << 4) |
			(voice->FMS & 0x0000000f);
		regs[2] = (voice->ESO << 16) | (voice->Delta & 0x0ffff);
		regs[3] = FmcRvolCvol;
		अवरोध;
	हाल TRIDENT_DEVICE_ID_NX:
		regs[4] |= ((voice->Vol & 0x000003fc) << (16-2)) |
			   (voice->EC & 0x00000fff);
		regs[0] = (voice->Delta << 24) | (voice->CSO & 0x00ffffff);
		regs[2] = ((voice->Delta << 16) & 0xff000000) |
			(voice->ESO & 0x00ffffff);
		regs[3] = (voice->Alpha << 20) |
			((voice->FMS & 0x0000000f) << 16) | FmcRvolCvol;
		अवरोध;
	शेष:
		snd_BUG();
		वापस;
	पूर्ण

	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	outl(regs[0], TRID_REG(trident, CH_START + 0));
	outl(regs[1], TRID_REG(trident, CH_START + 4));
	outl(regs[2], TRID_REG(trident, CH_START + 8));
	outl(regs[3], TRID_REG(trident, CH_START + 12));
	outl(regs[4], TRID_REG(trident, CH_START + 16));

#अगर 0
	dev_dbg(trident->card->dev, "written %i channel:\n", voice->number);
	dev_dbg(trident->card->dev, "  regs[0] = 0x%x/0x%x\n",
	       regs[0], inl(TRID_REG(trident, CH_START + 0)));
	dev_dbg(trident->card->dev, "  regs[1] = 0x%x/0x%x\n",
	       regs[1], inl(TRID_REG(trident, CH_START + 4)));
	dev_dbg(trident->card->dev, "  regs[2] = 0x%x/0x%x\n",
	       regs[2], inl(TRID_REG(trident, CH_START + 8)));
	dev_dbg(trident->card->dev, "  regs[3] = 0x%x/0x%x\n",
	       regs[3], inl(TRID_REG(trident, CH_START + 12)));
	dev_dbg(trident->card->dev, "  regs[4] = 0x%x/0x%x\n",
	       regs[4], inl(TRID_REG(trident, CH_START + 16)));
#पूर्ण_अगर
पूर्ण

EXPORT_SYMBOL(snd_trident_ग_लिखो_voice_regs);

/*---------------------------------------------------------------------------
   snd_trident_ग_लिखो_cso_reg
  
   Description: This routine will ग_लिखो the new CSO offset
                रेजिस्टर to hardware.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                voice - synthesizer voice काष्ठाure
                CSO - new CSO value
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_ग_लिखो_cso_reg(काष्ठा snd_trident * trident,
				      काष्ठा snd_trident_voice * voice,
				      अचिन्हित पूर्णांक CSO)
अणु
	voice->CSO = CSO;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	अगर (trident->device != TRIDENT_DEVICE_ID_NX) अणु
		outw(voice->CSO, TRID_REG(trident, CH_DX_CSO_ALPHA_FMS) + 2);
	पूर्ण अन्यथा अणु
		outl((voice->Delta << 24) |
		     (voice->CSO & 0x00ffffff), TRID_REG(trident, CH_NX_DELTA_CSO));
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_ग_लिखो_eso_reg
  
   Description: This routine will ग_लिखो the new ESO offset
                रेजिस्टर to hardware.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                voice - synthesizer voice काष्ठाure
                ESO - new ESO value
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_ग_लिखो_eso_reg(काष्ठा snd_trident * trident,
				      काष्ठा snd_trident_voice * voice,
				      अचिन्हित पूर्णांक ESO)
अणु
	voice->ESO = ESO;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	अगर (trident->device != TRIDENT_DEVICE_ID_NX) अणु
		outw(voice->ESO, TRID_REG(trident, CH_DX_ESO_DELTA) + 2);
	पूर्ण अन्यथा अणु
		outl(((voice->Delta << 16) & 0xff000000) | (voice->ESO & 0x00ffffff),
		     TRID_REG(trident, CH_NX_DELTA_ESO));
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_ग_लिखो_vol_reg
  
   Description: This routine will ग_लिखो the new voice volume
                रेजिस्टर to hardware.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                voice - synthesizer voice काष्ठाure
                Vol - new voice volume
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_ग_लिखो_vol_reg(काष्ठा snd_trident * trident,
				      काष्ठा snd_trident_voice * voice,
				      अचिन्हित पूर्णांक Vol)
अणु
	voice->Vol = Vol;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	चयन (trident->device) अणु
	हाल TRIDENT_DEVICE_ID_DX:
	हाल TRIDENT_DEVICE_ID_NX:
		outb(voice->Vol >> 2, TRID_REG(trident, CH_GVSEL_PAN_VOL_CTRL_EC + 2));
		अवरोध;
	हाल TRIDENT_DEVICE_ID_SI7018:
		/* dev_dbg(trident->card->dev, "voice->Vol = 0x%x\n", voice->Vol); */
		outw((voice->CTRL << 12) | voice->Vol,
		     TRID_REG(trident, CH_GVSEL_PAN_VOL_CTRL_EC));
		अवरोध;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_ग_लिखो_pan_reg
  
   Description: This routine will ग_लिखो the new voice pan
                रेजिस्टर to hardware.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                voice - synthesizer voice काष्ठाure
                Pan - new pan value
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_ग_लिखो_pan_reg(काष्ठा snd_trident * trident,
				      काष्ठा snd_trident_voice * voice,
				      अचिन्हित पूर्णांक Pan)
अणु
	voice->Pan = Pan;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	outb(((voice->GVSel & 0x01) << 7) | (voice->Pan & 0x7f),
	     TRID_REG(trident, CH_GVSEL_PAN_VOL_CTRL_EC + 3));
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_ग_लिखो_rvol_reg
  
   Description: This routine will ग_लिखो the new reverb volume
                रेजिस्टर to hardware.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                voice - synthesizer voice काष्ठाure
                RVol - new reverb volume
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_ग_लिखो_rvol_reg(काष्ठा snd_trident * trident,
				       काष्ठा snd_trident_voice * voice,
				       अचिन्हित पूर्णांक RVol)
अणु
	voice->RVol = RVol;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	outw(((voice->FMC & 0x0003) << 14) | ((voice->RVol & 0x007f) << 7) |
	     (voice->CVol & 0x007f),
	     TRID_REG(trident, trident->device == TRIDENT_DEVICE_ID_NX ?
		      CH_NX_ALPHA_FMS_FMC_RVOL_CVOL : CH_DX_FMC_RVOL_CVOL));
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_ग_लिखो_cvol_reg
  
   Description: This routine will ग_लिखो the new chorus volume
                रेजिस्टर to hardware.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                voice - synthesizer voice काष्ठाure
                CVol - new chorus volume
  
  ---------------------------------------------------------------------------*/

अटल व्योम snd_trident_ग_लिखो_cvol_reg(काष्ठा snd_trident * trident,
				       काष्ठा snd_trident_voice * voice,
				       अचिन्हित पूर्णांक CVol)
अणु
	voice->CVol = CVol;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	outw(((voice->FMC & 0x0003) << 14) | ((voice->RVol & 0x007f) << 7) |
	     (voice->CVol & 0x007f),
	     TRID_REG(trident, trident->device == TRIDENT_DEVICE_ID_NX ?
		      CH_NX_ALPHA_FMS_FMC_RVOL_CVOL : CH_DX_FMC_RVOL_CVOL));
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_convert_rate

   Description: This routine converts rate in HZ to hardware delta value.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                rate - Real or Virtual channel number.
  
   Returns:     Delta value.
  
  ---------------------------------------------------------------------------*/
अटल अचिन्हित पूर्णांक snd_trident_convert_rate(अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक delta;

	// We special हाल 44100 and 8000 since rounding with the equation
	// करोes not give us an accurate enough value. For 11025 and 22050
	// the equation gives us the best answer. All other frequencies will
	// also use the equation. JDW
	अगर (rate == 44100)
		delta = 0xeb3;
	अन्यथा अगर (rate == 8000)
		delta = 0x2ab;
	अन्यथा अगर (rate == 48000)
		delta = 0x1000;
	अन्यथा
		delta = DIV_ROUND_CLOSEST(rate << 12, 48000) & 0x0000ffff;
	वापस delta;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_convert_adc_rate

   Description: This routine converts rate in HZ to hardware delta value.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                rate - Real or Virtual channel number.
  
   Returns:     Delta value.
  
  ---------------------------------------------------------------------------*/
अटल अचिन्हित पूर्णांक snd_trident_convert_adc_rate(अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक delta;

	// We special हाल 44100 and 8000 since rounding with the equation
	// करोes not give us an accurate enough value. For 11025 and 22050
	// the equation gives us the best answer. All other frequencies will
	// also use the equation. JDW
	अगर (rate == 44100)
		delta = 0x116a;
	अन्यथा अगर (rate == 8000)
		delta = 0x6000;
	अन्यथा अगर (rate == 48000)
		delta = 0x1000;
	अन्यथा
		delta = ((48000 << 12) / rate) & 0x0000ffff;
	वापस delta;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_spurious_threshold

   Description: This routine converts rate in HZ to spurious threshold.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                rate - Real or Virtual channel number.
  
   Returns:     Delta value.
  
  ---------------------------------------------------------------------------*/
अटल अचिन्हित पूर्णांक snd_trident_spurious_threshold(अचिन्हित पूर्णांक rate,
						   अचिन्हित पूर्णांक period_size)
अणु
	अचिन्हित पूर्णांक res = (rate * period_size) / 48000;
	अगर (res < 64)
		res = res / 2;
	अन्यथा
		res -= 32;
	वापस res;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_control_mode

   Description: This routine वापसs a control mode क्रम a PCM channel.
  
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.
                substream  - PCM substream
  
   Returns:     Control value.
  
  ---------------------------------------------------------------------------*/
अटल अचिन्हित पूर्णांक snd_trident_control_mode(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित पूर्णांक CTRL;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/* set ctrl mode
	   CTRL शेष: 8-bit (अचिन्हित) mono, loop mode enabled
	 */
	CTRL = 0x00000001;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		CTRL |= 0x00000008;	// 16-bit data
	अगर (snd_pcm_क्रमmat_चिन्हित(runसमय->क्रमmat))
		CTRL |= 0x00000002;	// चिन्हित data
	अगर (runसमय->channels > 1)
		CTRL |= 0x00000004;	// stereo data
	वापस CTRL;
पूर्ण

/*
 *  PCM part
 */

/*---------------------------------------------------------------------------
   snd_trident_allocate_pcm_mem
  
   Description: Allocate PCM ring buffer क्रम given substream
  
   Parameters:  substream  - PCM substream class
		hw_params  - hardware parameters
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_allocate_pcm_mem(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;

	अगर (trident->tlb.entries) अणु
		अगर (runसमय->buffer_changed) अणु
			अगर (voice->memblk)
				snd_trident_मुक्त_pages(trident, voice->memblk);
			voice->memblk = snd_trident_alloc_pages(trident, substream);
			अगर (voice->memblk == शून्य)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_allocate_evoice
  
   Description: Allocate extra voice as पूर्णांकerrupt generator
  
   Parameters:  substream  - PCM substream class
		hw_params  - hardware parameters
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_allocate_evoice(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	काष्ठा snd_trident_voice *evoice = voice->extra;

	/* voice management */

	अगर (params_buffer_size(hw_params) / 2 != params_period_size(hw_params)) अणु
		अगर (evoice == शून्य) अणु
			evoice = snd_trident_alloc_voice(trident, SNDRV_TRIDENT_VOICE_TYPE_PCM, 0, 0);
			अगर (evoice == शून्य)
				वापस -ENOMEM;
			voice->extra = evoice;
			evoice->substream = substream;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (evoice != शून्य) अणु
			snd_trident_मुक्त_voice(trident, evoice);
			voice->extra = evoice = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_hw_params
  
   Description: Set the hardware parameters क्रम the playback device.
  
   Parameters:  substream  - PCM substream class
		hw_params  - hardware parameters
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	पूर्णांक err;

	err = snd_trident_allocate_pcm_mem(substream, hw_params);
	अगर (err >= 0)
		err = snd_trident_allocate_evoice(substream, hw_params);
	वापस err;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_playback_hw_मुक्त
  
   Description: Release the hardware resources क्रम the playback device.
  
   Parameters:  substream  - PCM substream class
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	काष्ठा snd_trident_voice *evoice = voice ? voice->extra : शून्य;

	अगर (trident->tlb.entries) अणु
		अगर (voice && voice->memblk) अणु
			snd_trident_मुक्त_pages(trident, voice->memblk);
			voice->memblk = शून्य;
		पूर्ण
	पूर्ण
	अगर (evoice != शून्य) अणु
		snd_trident_मुक्त_voice(trident, evoice);
		voice->extra = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_playback_prepare
  
   Description: Prepare playback device क्रम playback.
  
   Parameters:  substream  - PCM substream class
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	काष्ठा snd_trident_voice *evoice = voice->extra;
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[substream->number];

	spin_lock_irq(&trident->reg_lock);	

	/* set delta (rate) value */
	voice->Delta = snd_trident_convert_rate(runसमय->rate);
	voice->spurious_threshold = snd_trident_spurious_threshold(runसमय->rate, runसमय->period_size);

	/* set Loop Begin Address */
	अगर (voice->memblk)
		voice->LBA = voice->memblk->offset;
	अन्यथा
		voice->LBA = runसमय->dma_addr;
 
	voice->CSO = 0;
	voice->ESO = runसमय->buffer_size - 1;	/* in samples */
	voice->CTRL = snd_trident_control_mode(substream);
	voice->FMC = 3;
	voice->GVSel = 1;
	voice->EC = 0;
	voice->Alpha = 0;
	voice->FMS = 0;
	voice->Vol = mix->vol;
	voice->RVol = mix->rvol;
	voice->CVol = mix->cvol;
	voice->Pan = mix->pan;
	voice->Attribute = 0;
#अगर 0
	voice->Attribute = (1<<(30-16))|(2<<(26-16))|
			   (0<<(24-16))|(0x1f<<(19-16));
#अन्यथा
	voice->Attribute = 0;
#पूर्ण_अगर

	snd_trident_ग_लिखो_voice_regs(trident, voice);

	अगर (evoice != शून्य) अणु
		evoice->Delta = voice->Delta;
		evoice->spurious_threshold = voice->spurious_threshold;
		evoice->LBA = voice->LBA;
		evoice->CSO = 0;
		evoice->ESO = (runसमय->period_size * 2) + 4 - 1; /* in samples */
		evoice->CTRL = voice->CTRL;
		evoice->FMC = 3;
		evoice->GVSel = trident->device == TRIDENT_DEVICE_ID_SI7018 ? 0 : 1;
		evoice->EC = 0;
		evoice->Alpha = 0;
		evoice->FMS = 0;
		evoice->Vol = 0x3ff;			/* mute */
		evoice->RVol = evoice->CVol = 0x7f;	/* mute */
		evoice->Pan = 0x7f;			/* mute */
#अगर 0
		evoice->Attribute = (1<<(30-16))|(2<<(26-16))|
				    (0<<(24-16))|(0x1f<<(19-16));
#अन्यथा
		evoice->Attribute = 0;
#पूर्ण_अगर
		snd_trident_ग_लिखो_voice_regs(trident, evoice);
		evoice->isync2 = 1;
		evoice->isync_mark = runसमय->period_size;
		evoice->ESO = (runसमय->period_size * 2) - 1;
	पूर्ण

	spin_unlock_irq(&trident->reg_lock);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_capture_hw_params
  
   Description: Set the hardware parameters क्रम the capture device.
  
   Parameters:  substream  - PCM substream class
		hw_params  - hardware parameters
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_capture_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	वापस snd_trident_allocate_pcm_mem(substream, hw_params);
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_capture_prepare
  
   Description: Prepare capture device क्रम playback.
  
   Parameters:  substream  - PCM substream class
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	अचिन्हित पूर्णांक val, ESO_bytes;

	spin_lock_irq(&trident->reg_lock);

	// Initialize the channel and set channel Mode
	outb(0, TRID_REG(trident, LEGACY_DMAR15));

	// Set DMA channel operation mode रेजिस्टर
	outb(0x54, TRID_REG(trident, LEGACY_DMAR11));

	// Set channel buffer Address, DMAR0 expects contiguous PCI memory area	
	voice->LBA = runसमय->dma_addr;
	outl(voice->LBA, TRID_REG(trident, LEGACY_DMAR0));
	अगर (voice->memblk)
		voice->LBA = voice->memblk->offset;

	// set ESO
	ESO_bytes = snd_pcm_lib_buffer_bytes(substream) - 1;
	outb((ESO_bytes & 0x00ff0000) >> 16, TRID_REG(trident, LEGACY_DMAR6));
	outw((ESO_bytes & 0x0000ffff), TRID_REG(trident, LEGACY_DMAR4));
	ESO_bytes++;

	// Set channel sample rate, 4.12 क्रमmat
	val = DIV_ROUND_CLOSEST(48000U << 12, runसमय->rate);
	outw(val, TRID_REG(trident, T4D_SBDELTA_DELTA_R));

	// Set channel पूर्णांकerrupt blk length
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16) अणु
		val = (अचिन्हित लघु) ((ESO_bytes >> 1) - 1);
	पूर्ण अन्यथा अणु
		val = (अचिन्हित लघु) (ESO_bytes - 1);
	पूर्ण

	outl((val << 16) | val, TRID_REG(trident, T4D_SBBL_SBCL));

	// Right now, set क्रमmat and start to run captureing, 
	// continuous run loop enable.
	trident->bDMAStart = 0x19;	// 0001 1001b

	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		trident->bDMAStart |= 0x80;
	अगर (snd_pcm_क्रमmat_चिन्हित(runसमय->क्रमmat))
		trident->bDMAStart |= 0x20;
	अगर (runसमय->channels > 1)
		trident->bDMAStart |= 0x40;

	// Prepare capture पूर्णांकr channel

	voice->Delta = snd_trident_convert_rate(runसमय->rate);
	voice->spurious_threshold = snd_trident_spurious_threshold(runसमय->rate, runसमय->period_size);
	voice->isync = 1;
	voice->isync_mark = runसमय->period_size;
	voice->isync_max = runसमय->buffer_size;

	// Set voice parameters
	voice->CSO = 0;
	voice->ESO = voice->isync_ESO = (runसमय->period_size * 2) + 6 - 1;
	voice->CTRL = snd_trident_control_mode(substream);
	voice->FMC = 3;
	voice->RVol = 0x7f;
	voice->CVol = 0x7f;
	voice->GVSel = 1;
	voice->Pan = 0x7f;		/* mute */
	voice->Vol = 0x3ff;		/* mute */
	voice->EC = 0;
	voice->Alpha = 0;
	voice->FMS = 0;
	voice->Attribute = 0;

	snd_trident_ग_लिखो_voice_regs(trident, voice);

	spin_unlock_irq(&trident->reg_lock);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_si7018_capture_hw_params
  
   Description: Set the hardware parameters क्रम the capture device.
  
   Parameters:  substream  - PCM substream class
		hw_params  - hardware parameters
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_si7018_capture_hw_params(काष्ठा snd_pcm_substream *substream,
						काष्ठा snd_pcm_hw_params *hw_params)
अणु
	वापस snd_trident_allocate_evoice(substream, hw_params);
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_si7018_capture_hw_मुक्त
  
   Description: Release the hardware resources क्रम the capture device.
  
   Parameters:  substream  - PCM substream class
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_si7018_capture_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	काष्ठा snd_trident_voice *evoice = voice ? voice->extra : शून्य;

	अगर (evoice != शून्य) अणु
		snd_trident_मुक्त_voice(trident, evoice);
		voice->extra = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_si7018_capture_prepare
  
   Description: Prepare capture device क्रम playback.
  
   Parameters:  substream  - PCM substream class
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_si7018_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	काष्ठा snd_trident_voice *evoice = voice->extra;

	spin_lock_irq(&trident->reg_lock);

	voice->LBA = runसमय->dma_addr;
	voice->Delta = snd_trident_convert_adc_rate(runसमय->rate);
	voice->spurious_threshold = snd_trident_spurious_threshold(runसमय->rate, runसमय->period_size);

	// Set voice parameters
	voice->CSO = 0;
	voice->ESO = runसमय->buffer_size - 1;		/* in samples */
	voice->CTRL = snd_trident_control_mode(substream);
	voice->FMC = 0;
	voice->RVol = 0;
	voice->CVol = 0;
	voice->GVSel = 1;
	voice->Pan = T4D_DEFAULT_PCM_PAN;
	voice->Vol = 0;
	voice->EC = 0;
	voice->Alpha = 0;
	voice->FMS = 0;

	voice->Attribute = (2 << (30-16)) |
			   (2 << (26-16)) |
			   (2 << (24-16)) |
			   (1 << (23-16));

	snd_trident_ग_लिखो_voice_regs(trident, voice);

	अगर (evoice != शून्य) अणु
		evoice->Delta = snd_trident_convert_rate(runसमय->rate);
		evoice->spurious_threshold = voice->spurious_threshold;
		evoice->LBA = voice->LBA;
		evoice->CSO = 0;
		evoice->ESO = (runसमय->period_size * 2) + 20 - 1; /* in samples, 20 means correction */
		evoice->CTRL = voice->CTRL;
		evoice->FMC = 3;
		evoice->GVSel = 0;
		evoice->EC = 0;
		evoice->Alpha = 0;
		evoice->FMS = 0;
		evoice->Vol = 0x3ff;			/* mute */
		evoice->RVol = evoice->CVol = 0x7f;	/* mute */
		evoice->Pan = 0x7f;			/* mute */
		evoice->Attribute = 0;
		snd_trident_ग_लिखो_voice_regs(trident, evoice);
		evoice->isync2 = 1;
		evoice->isync_mark = runसमय->period_size;
		evoice->ESO = (runसमय->period_size * 2) - 1;
	पूर्ण
	
	spin_unlock_irq(&trident->reg_lock);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_foldback_prepare
  
   Description: Prepare foldback capture device क्रम playback.
  
   Parameters:  substream  - PCM substream class
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_foldback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	काष्ठा snd_trident_voice *evoice = voice->extra;

	spin_lock_irq(&trident->reg_lock);

	/* Set channel buffer Address */
	अगर (voice->memblk)
		voice->LBA = voice->memblk->offset;
	अन्यथा
		voice->LBA = runसमय->dma_addr;

	/* set target ESO क्रम channel */
	voice->ESO = runसमय->buffer_size - 1;	/* in samples */

	/* set sample rate */
	voice->Delta = 0x1000;
	voice->spurious_threshold = snd_trident_spurious_threshold(48000, runसमय->period_size);

	voice->CSO = 0;
	voice->CTRL = snd_trident_control_mode(substream);
	voice->FMC = 3;
	voice->RVol = 0x7f;
	voice->CVol = 0x7f;
	voice->GVSel = 1;
	voice->Pan = 0x7f;	/* mute */
	voice->Vol = 0x3ff;	/* mute */
	voice->EC = 0;
	voice->Alpha = 0;
	voice->FMS = 0;
	voice->Attribute = 0;

	/* set up capture channel */
	outb(((voice->number & 0x3f) | 0x80), TRID_REG(trident, T4D_RCI + voice->foldback_chan));

	snd_trident_ग_लिखो_voice_regs(trident, voice);

	अगर (evoice != शून्य) अणु
		evoice->Delta = voice->Delta;
		evoice->spurious_threshold = voice->spurious_threshold;
		evoice->LBA = voice->LBA;
		evoice->CSO = 0;
		evoice->ESO = (runसमय->period_size * 2) + 4 - 1; /* in samples */
		evoice->CTRL = voice->CTRL;
		evoice->FMC = 3;
		evoice->GVSel = trident->device == TRIDENT_DEVICE_ID_SI7018 ? 0 : 1;
		evoice->EC = 0;
		evoice->Alpha = 0;
		evoice->FMS = 0;
		evoice->Vol = 0x3ff;			/* mute */
		evoice->RVol = evoice->CVol = 0x7f;	/* mute */
		evoice->Pan = 0x7f;			/* mute */
		evoice->Attribute = 0;
		snd_trident_ग_लिखो_voice_regs(trident, evoice);
		evoice->isync2 = 1;
		evoice->isync_mark = runसमय->period_size;
		evoice->ESO = (runसमय->period_size * 2) - 1;
	पूर्ण

	spin_unlock_irq(&trident->reg_lock);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_spdअगर_hw_params
  
   Description: Set the hardware parameters क्रम the spdअगर device.
  
   Parameters:  substream  - PCM substream class
		hw_params  - hardware parameters
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक old_bits = 0, change = 0;
	पूर्णांक err;

	err = snd_trident_allocate_pcm_mem(substream, hw_params);
	अगर (err < 0)
		वापस err;

	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		err = snd_trident_allocate_evoice(substream, hw_params);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* prepare SPDIF channel */
	spin_lock_irq(&trident->reg_lock);
	old_bits = trident->spdअगर_pcm_bits;
	अगर (old_bits & IEC958_AES0_PROFESSIONAL)
		trident->spdअगर_pcm_bits &= ~IEC958_AES0_PRO_FS;
	अन्यथा
		trident->spdअगर_pcm_bits &= ~(IEC958_AES3_CON_FS << 24);
	अगर (params_rate(hw_params) >= 48000) अणु
		trident->spdअगर_pcm_ctrl = 0x3c;	// 48000 Hz
		trident->spdअगर_pcm_bits |=
			trident->spdअगर_bits & IEC958_AES0_PROFESSIONAL ?
				IEC958_AES0_PRO_FS_48000 :
				(IEC958_AES3_CON_FS_48000 << 24);
	पूर्ण
	अन्यथा अगर (params_rate(hw_params) >= 44100) अणु
		trident->spdअगर_pcm_ctrl = 0x3e;	// 44100 Hz
		trident->spdअगर_pcm_bits |=
			trident->spdअगर_bits & IEC958_AES0_PROFESSIONAL ?
				IEC958_AES0_PRO_FS_44100 :
				(IEC958_AES3_CON_FS_44100 << 24);
	पूर्ण
	अन्यथा अणु
		trident->spdअगर_pcm_ctrl = 0x3d;	// 32000 Hz
		trident->spdअगर_pcm_bits |=
			trident->spdअगर_bits & IEC958_AES0_PROFESSIONAL ?
				IEC958_AES0_PRO_FS_32000 :
				(IEC958_AES3_CON_FS_32000 << 24);
	पूर्ण
	change = old_bits != trident->spdअगर_pcm_bits;
	spin_unlock_irq(&trident->reg_lock);

	अगर (change)
		snd_ctl_notअगरy(trident->card, SNDRV_CTL_EVENT_MASK_VALUE, &trident->spdअगर_pcm_ctl->id);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_spdअगर_prepare
  
   Description: Prepare SPDIF device क्रम playback.
  
   Parameters:  substream  - PCM substream class
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_spdअगर_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	काष्ठा snd_trident_voice *evoice = voice->extra;
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[substream->number];
	अचिन्हित पूर्णांक RESO, LBAO;
	अचिन्हित पूर्णांक temp;

	spin_lock_irq(&trident->reg_lock);

	अगर (trident->device != TRIDENT_DEVICE_ID_SI7018) अणु

		/* set delta (rate) value */
		voice->Delta = snd_trident_convert_rate(runसमय->rate);
		voice->spurious_threshold = snd_trident_spurious_threshold(runसमय->rate, runसमय->period_size);

		/* set Loop Back Address */
		LBAO = runसमय->dma_addr;
		अगर (voice->memblk)
			voice->LBA = voice->memblk->offset;
		अन्यथा
			voice->LBA = LBAO;

		voice->isync = 1;
		voice->isync3 = 1;
		voice->isync_mark = runसमय->period_size;
		voice->isync_max = runसमय->buffer_size;

		/* set target ESO क्रम channel */
		RESO = runसमय->buffer_size - 1;
		voice->ESO = voice->isync_ESO = (runसमय->period_size * 2) + 6 - 1;

		/* set ctrl mode */
		voice->CTRL = snd_trident_control_mode(substream);

		voice->FMC = 3;
		voice->RVol = 0x7f;
		voice->CVol = 0x7f;
		voice->GVSel = 1;
		voice->Pan = 0x7f;
		voice->Vol = 0x3ff;
		voice->EC = 0;
		voice->CSO = 0;
		voice->Alpha = 0;
		voice->FMS = 0;
		voice->Attribute = 0;

		/* prepare surrogate IRQ channel */
		snd_trident_ग_लिखो_voice_regs(trident, voice);

		outw((RESO & 0xffff), TRID_REG(trident, NX_SPESO));
		outb((RESO >> 16), TRID_REG(trident, NX_SPESO + 2));
		outl((LBAO & 0xfffffffc), TRID_REG(trident, NX_SPLBA));
		outw((voice->CSO & 0xffff), TRID_REG(trident, NX_SPCTRL_SPCSO));
		outb((voice->CSO >> 16), TRID_REG(trident, NX_SPCTRL_SPCSO + 2));

		/* set SPDIF setting */
		outb(trident->spdअगर_pcm_ctrl, TRID_REG(trident, NX_SPCTRL_SPCSO + 3));
		outl(trident->spdअगर_pcm_bits, TRID_REG(trident, NX_SPCSTATUS));

	पूर्ण अन्यथा अणु	/* SiS */
	
		/* set delta (rate) value */
		voice->Delta = 0x800;
		voice->spurious_threshold = snd_trident_spurious_threshold(48000, runसमय->period_size);

		/* set Loop Begin Address */
		अगर (voice->memblk)
			voice->LBA = voice->memblk->offset;
		अन्यथा
			voice->LBA = runसमय->dma_addr;

		voice->CSO = 0;
		voice->ESO = runसमय->buffer_size - 1;	/* in samples */
		voice->CTRL = snd_trident_control_mode(substream);
		voice->FMC = 3;
		voice->GVSel = 1;
		voice->EC = 0;
		voice->Alpha = 0;
		voice->FMS = 0;
		voice->Vol = mix->vol;
		voice->RVol = mix->rvol;
		voice->CVol = mix->cvol;
		voice->Pan = mix->pan;
		voice->Attribute = (1<<(30-16))|(7<<(26-16))|
				   (0<<(24-16))|(0<<(19-16));

		snd_trident_ग_लिखो_voice_regs(trident, voice);

		अगर (evoice != शून्य) अणु
			evoice->Delta = voice->Delta;
			evoice->spurious_threshold = voice->spurious_threshold;
			evoice->LBA = voice->LBA;
			evoice->CSO = 0;
			evoice->ESO = (runसमय->period_size * 2) + 4 - 1; /* in samples */
			evoice->CTRL = voice->CTRL;
			evoice->FMC = 3;
			evoice->GVSel = trident->device == TRIDENT_DEVICE_ID_SI7018 ? 0 : 1;
			evoice->EC = 0;
			evoice->Alpha = 0;
			evoice->FMS = 0;
			evoice->Vol = 0x3ff;			/* mute */
			evoice->RVol = evoice->CVol = 0x7f;	/* mute */
			evoice->Pan = 0x7f;			/* mute */
			evoice->Attribute = 0;
			snd_trident_ग_लिखो_voice_regs(trident, evoice);
			evoice->isync2 = 1;
			evoice->isync_mark = runसमय->period_size;
			evoice->ESO = (runसमय->period_size * 2) - 1;
		पूर्ण

		outl(trident->spdअगर_pcm_bits, TRID_REG(trident, SI_SPDIF_CS));
		temp = inl(TRID_REG(trident, T4D_LFO_GC_CIR));
		temp &= ~(1<<19);
		outl(temp, TRID_REG(trident, T4D_LFO_GC_CIR));
		temp = inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL));
		temp |= SPDIF_EN;
		outl(temp, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
	पूर्ण

	spin_unlock_irq(&trident->reg_lock);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_trigger
  
   Description: Start/stop devices
  
   Parameters:  substream  - PCM substream class
   		cmd	- trigger command (STOP, GO)
  
   Returns:     Error status
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd)
				    
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *s;
	अचिन्हित पूर्णांक what, whati, capture_flag, spdअगर_flag;
	काष्ठा snd_trident_voice *voice, *evoice;
	अचिन्हित पूर्णांक val, go;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		go = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		go = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	what = whati = capture_flag = spdअगर_flag = 0;
	spin_lock(&trident->reg_lock);
	val = inl(TRID_REG(trident, T4D_STIMER)) & 0x00ffffff;
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर ((काष्ठा snd_trident *) snd_pcm_substream_chip(s) == trident) अणु
			voice = s->runसमय->निजी_data;
			evoice = voice->extra;
			what |= 1 << (voice->number & 0x1f);
			अगर (evoice == शून्य) अणु
				whati |= 1 << (voice->number & 0x1f);
			पूर्ण अन्यथा अणु
				what |= 1 << (evoice->number & 0x1f);
				whati |= 1 << (evoice->number & 0x1f);
				अगर (go)
					evoice->sसमयr = val;
			पूर्ण
			अगर (go) अणु
				voice->running = 1;
				voice->sसमयr = val;
			पूर्ण अन्यथा अणु
				voice->running = 0;
			पूर्ण
			snd_pcm_trigger_करोne(s, substream);
			अगर (voice->capture)
				capture_flag = 1;
			अगर (voice->spdअगर)
				spdअगर_flag = 1;
		पूर्ण
	पूर्ण
	अगर (spdअगर_flag) अणु
		अगर (trident->device != TRIDENT_DEVICE_ID_SI7018) अणु
			outl(trident->spdअगर_pcm_bits, TRID_REG(trident, NX_SPCSTATUS));
			val = trident->spdअगर_pcm_ctrl;
			अगर (!go)
				val &= ~(0x28);
			outb(val, TRID_REG(trident, NX_SPCTRL_SPCSO + 3));
		पूर्ण अन्यथा अणु
			outl(trident->spdअगर_pcm_bits, TRID_REG(trident, SI_SPDIF_CS));
			val = inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)) | SPDIF_EN;
			outl(val, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
		पूर्ण
	पूर्ण
	अगर (!go)
		outl(what, TRID_REG(trident, T4D_STOP_B));
	val = inl(TRID_REG(trident, T4D_AINTEN_B));
	अगर (go) अणु
		val |= whati;
	पूर्ण अन्यथा अणु
		val &= ~whati;
	पूर्ण
	outl(val, TRID_REG(trident, T4D_AINTEN_B));
	अगर (go) अणु
		outl(what, TRID_REG(trident, T4D_START_B));

		अगर (capture_flag && trident->device != TRIDENT_DEVICE_ID_SI7018)
			outb(trident->bDMAStart, TRID_REG(trident, T4D_SBCTRL_SBE2R_SBDD));
	पूर्ण अन्यथा अणु
		अगर (capture_flag && trident->device != TRIDENT_DEVICE_ID_SI7018)
			outb(0x00, TRID_REG(trident, T4D_SBCTRL_SBE2R_SBDD));
	पूर्ण
	spin_unlock(&trident->reg_lock);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_playback_poपूर्णांकer
  
   Description: This routine वापस the playback position
                
   Parameters:	substream  - PCM substream class

   Returns:     position of buffer
  
  ---------------------------------------------------------------------------*/

अटल snd_pcm_uframes_t snd_trident_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	अचिन्हित पूर्णांक cso;

	अगर (!voice->running)
		वापस 0;

	spin_lock(&trident->reg_lock);

	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));

	अगर (trident->device != TRIDENT_DEVICE_ID_NX) अणु
		cso = inw(TRID_REG(trident, CH_DX_CSO_ALPHA_FMS + 2));
	पूर्ण अन्यथा अणु		// ID_4DWAVE_NX
		cso = (अचिन्हित पूर्णांक) inl(TRID_REG(trident, CH_NX_DELTA_CSO)) & 0x00ffffff;
	पूर्ण

	spin_unlock(&trident->reg_lock);

	अगर (cso >= runसमय->buffer_size)
		cso = 0;

	वापस cso;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_capture_poपूर्णांकer
  
   Description: This routine वापस the capture position
                
   Parameters:   pcm1    - PCM device class

   Returns:     position of buffer
  
  ---------------------------------------------------------------------------*/

अटल snd_pcm_uframes_t snd_trident_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	अचिन्हित पूर्णांक result;

	अगर (!voice->running)
		वापस 0;

	result = inw(TRID_REG(trident, T4D_SBBL_SBCL));
	अगर (runसमय->channels > 1)
		result >>= 1;
	अगर (result > 0)
		result = runसमय->buffer_size - result;

	वापस result;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_spdअगर_poपूर्णांकer
  
   Description: This routine वापस the SPDIF playback position
                
   Parameters:	substream  - PCM substream class

   Returns:     position of buffer
  
  ---------------------------------------------------------------------------*/

अटल snd_pcm_uframes_t snd_trident_spdअगर_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	अचिन्हित पूर्णांक result;

	अगर (!voice->running)
		वापस 0;

	result = inl(TRID_REG(trident, NX_SPCTRL_SPCSO)) & 0x00ffffff;

	वापस result;
पूर्ण

/*
 *  Playback support device description
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_trident_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_PAUSE /* | SNDRV_PCM_INFO_RESUME */),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |
				 SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(256*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(256*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/*
 *  Capture support device description
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_trident_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_PAUSE /* | SNDRV_PCM_INFO_RESUME */),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |
				 SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/*
 *  Foldback capture support device description
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_trident_foldback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_PAUSE /* | SNDRV_PCM_INFO_RESUME */),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/*
 *  SPDIF playback support device description
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_trident_spdअगर =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_PAUSE /* | SNDRV_PCM_INFO_RESUME */),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		(SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
				 SNDRV_PCM_RATE_48000),
	.rate_min =		32000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_trident_spdअगर_7018 =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_PAUSE /* | SNDRV_PCM_INFO_RESUME */),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल व्योम snd_trident_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;
	काष्ठा snd_trident *trident;

	अगर (voice) अणु
		trident = voice->trident;
		snd_trident_मुक्त_voice(trident, voice);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_trident_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice;

	voice = snd_trident_alloc_voice(trident, SNDRV_TRIDENT_VOICE_TYPE_PCM, 0, 0);
	अगर (voice == शून्य)
		वापस -EAGAIN;
	snd_trident_pcm_mixer_build(trident, voice, substream);
	voice->substream = substream;
	runसमय->निजी_data = voice;
	runसमय->निजी_मुक्त = snd_trident_pcm_मुक्त_substream;
	runसमय->hw = snd_trident_playback;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 64*1024);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_playback_बंद
  
   Description: This routine will बंद the 4DWave playback device. For now 
                we will simply मुक्त the dma transfer buffer.
                
   Parameters:	substream  - PCM substream class

  ---------------------------------------------------------------------------*/
अटल पूर्णांक snd_trident_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_trident_voice *voice = runसमय->निजी_data;

	snd_trident_pcm_mixer_मुक्त(trident, voice, substream);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_spdअगर_खोलो
  
   Description: This routine will खोलो the 4DWave SPDIF device.

   Parameters:	substream  - PCM substream class

   Returns:     status  - success or failure flag
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_trident_voice *voice;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	
	voice = snd_trident_alloc_voice(trident, SNDRV_TRIDENT_VOICE_TYPE_PCM, 0, 0);
	अगर (voice == शून्य)
		वापस -EAGAIN;
	voice->spdअगर = 1;
	voice->substream = substream;
	spin_lock_irq(&trident->reg_lock);
	trident->spdअगर_pcm_bits = trident->spdअगर_bits;
	spin_unlock_irq(&trident->reg_lock);

	runसमय->निजी_data = voice;
	runसमय->निजी_मुक्त = snd_trident_pcm_मुक्त_substream;
	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		runसमय->hw = snd_trident_spdअगर;
	पूर्ण अन्यथा अणु
		runसमय->hw = snd_trident_spdअगर_7018;
	पूर्ण

	trident->spdअगर_pcm_ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(trident->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &trident->spdअगर_pcm_ctl->id);

	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 64*1024);
	वापस 0;
पूर्ण


/*---------------------------------------------------------------------------
   snd_trident_spdअगर_बंद
  
   Description: This routine will बंद the 4DWave SPDIF device.
                
   Parameters:	substream  - PCM substream class

  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_spdअगर_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक temp;

	spin_lock_irq(&trident->reg_lock);
	// restore शेष SPDIF setting
	अगर (trident->device != TRIDENT_DEVICE_ID_SI7018) अणु
		outb(trident->spdअगर_ctrl, TRID_REG(trident, NX_SPCTRL_SPCSO + 3));
		outl(trident->spdअगर_bits, TRID_REG(trident, NX_SPCSTATUS));
	पूर्ण अन्यथा अणु
		outl(trident->spdअगर_bits, TRID_REG(trident, SI_SPDIF_CS));
		temp = inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL));
		अगर (trident->spdअगर_ctrl) अणु
			temp |= SPDIF_EN;
		पूर्ण अन्यथा अणु
			temp &= ~SPDIF_EN;
		पूर्ण
		outl(temp, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
	पूर्ण
	spin_unlock_irq(&trident->reg_lock);
	trident->spdअगर_pcm_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(trident->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &trident->spdअगर_pcm_ctl->id);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_capture_खोलो
  
   Description: This routine will खोलो the 4DWave capture device.

   Parameters:	substream  - PCM substream class

   Returns:     status  - success or failure flag

  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_trident_voice *voice;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	voice = snd_trident_alloc_voice(trident, SNDRV_TRIDENT_VOICE_TYPE_PCM, 0, 0);
	अगर (voice == शून्य)
		वापस -EAGAIN;
	voice->capture = 1;
	voice->substream = substream;
	runसमय->निजी_data = voice;
	runसमय->निजी_मुक्त = snd_trident_pcm_मुक्त_substream;
	runसमय->hw = snd_trident_capture;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 64*1024);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_capture_बंद
  
   Description: This routine will बंद the 4DWave capture device. For now 
                we will simply मुक्त the dma transfer buffer.
                
   Parameters:	substream  - PCM substream class

  ---------------------------------------------------------------------------*/
अटल पूर्णांक snd_trident_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_foldback_खोलो
  
   Description: This routine will खोलो the 4DWave foldback capture device.

   Parameters:	substream  - PCM substream class

   Returns:     status  - success or failure flag

  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_foldback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_trident_voice *voice;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	voice = snd_trident_alloc_voice(trident, SNDRV_TRIDENT_VOICE_TYPE_PCM, 0, 0);
	अगर (voice == शून्य)
		वापस -EAGAIN;
	voice->foldback_chan = substream->number;
	voice->substream = substream;
	runसमय->निजी_data = voice;
	runसमय->निजी_मुक्त = snd_trident_pcm_मुक्त_substream;
	runसमय->hw = snd_trident_foldback;
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 64*1024);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_foldback_बंद
  
   Description: This routine will बंद the 4DWave foldback capture device. 
		For now we will simply मुक्त the dma transfer buffer.
                
   Parameters:	substream  - PCM substream class

  ---------------------------------------------------------------------------*/
अटल पूर्णांक snd_trident_foldback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident *trident = snd_pcm_substream_chip(substream);
	काष्ठा snd_trident_voice *voice;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	voice = runसमय->निजी_data;
	
	/* stop capture channel */
	spin_lock_irq(&trident->reg_lock);
	outb(0x00, TRID_REG(trident, T4D_RCI + voice->foldback_chan));
	spin_unlock_irq(&trident->reg_lock);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   PCM operations
  ---------------------------------------------------------------------------*/

अटल स्थिर काष्ठा snd_pcm_ops snd_trident_playback_ops = अणु
	.खोलो =		snd_trident_playback_खोलो,
	.बंद =	snd_trident_playback_बंद,
	.hw_params =	snd_trident_hw_params,
	.hw_मुक्त =	snd_trident_hw_मुक्त,
	.prepare =	snd_trident_playback_prepare,
	.trigger =	snd_trident_trigger,
	.poपूर्णांकer =	snd_trident_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_trident_nx_playback_ops = अणु
	.खोलो =		snd_trident_playback_खोलो,
	.बंद =	snd_trident_playback_बंद,
	.hw_params =	snd_trident_hw_params,
	.hw_मुक्त =	snd_trident_hw_मुक्त,
	.prepare =	snd_trident_playback_prepare,
	.trigger =	snd_trident_trigger,
	.poपूर्णांकer =	snd_trident_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_trident_capture_ops = अणु
	.खोलो =		snd_trident_capture_खोलो,
	.बंद =	snd_trident_capture_बंद,
	.hw_params =	snd_trident_capture_hw_params,
	.hw_मुक्त =	snd_trident_hw_मुक्त,
	.prepare =	snd_trident_capture_prepare,
	.trigger =	snd_trident_trigger,
	.poपूर्णांकer =	snd_trident_capture_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_trident_si7018_capture_ops = अणु
	.खोलो =		snd_trident_capture_खोलो,
	.बंद =	snd_trident_capture_बंद,
	.hw_params =	snd_trident_si7018_capture_hw_params,
	.hw_मुक्त =	snd_trident_si7018_capture_hw_मुक्त,
	.prepare =	snd_trident_si7018_capture_prepare,
	.trigger =	snd_trident_trigger,
	.poपूर्णांकer =	snd_trident_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_trident_foldback_ops = अणु
	.खोलो =		snd_trident_foldback_खोलो,
	.बंद =	snd_trident_foldback_बंद,
	.hw_params =	snd_trident_hw_params,
	.hw_मुक्त =	snd_trident_hw_मुक्त,
	.prepare =	snd_trident_foldback_prepare,
	.trigger =	snd_trident_trigger,
	.poपूर्णांकer =	snd_trident_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_trident_nx_foldback_ops = अणु
	.खोलो =		snd_trident_foldback_खोलो,
	.बंद =	snd_trident_foldback_बंद,
	.hw_params =	snd_trident_hw_params,
	.hw_मुक्त =	snd_trident_hw_मुक्त,
	.prepare =	snd_trident_foldback_prepare,
	.trigger =	snd_trident_trigger,
	.poपूर्णांकer =	snd_trident_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_trident_spdअगर_ops = अणु
	.खोलो =		snd_trident_spdअगर_खोलो,
	.बंद =	snd_trident_spdअगर_बंद,
	.hw_params =	snd_trident_spdअगर_hw_params,
	.hw_मुक्त =	snd_trident_hw_मुक्त,
	.prepare =	snd_trident_spdअगर_prepare,
	.trigger =	snd_trident_trigger,
	.poपूर्णांकer =	snd_trident_spdअगर_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_trident_spdअगर_7018_ops = अणु
	.खोलो =		snd_trident_spdअगर_खोलो,
	.बंद =	snd_trident_spdअगर_बंद,
	.hw_params =	snd_trident_spdअगर_hw_params,
	.hw_मुक्त =	snd_trident_hw_मुक्त,
	.prepare =	snd_trident_spdअगर_prepare,
	.trigger =	snd_trident_trigger,
	.poपूर्णांकer =	snd_trident_playback_poपूर्णांकer,
पूर्ण;

/*---------------------------------------------------------------------------
   snd_trident_pcm
  
   Description: This routine रेजिस्टरs the 4DWave device क्रम PCM support.
                
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.

   Returns:     None
  
  ---------------------------------------------------------------------------*/

पूर्णांक snd_trident_pcm(काष्ठा snd_trident *trident, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(trident->card, "trident_dx_nx", device, trident->ChanPCM, 1, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = trident;

	अगर (trident->tlb.entries) अणु
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_trident_nx_playback_ops);
	पूर्ण अन्यथा अणु
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_trident_playback_ops);
	पूर्ण
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			trident->device != TRIDENT_DEVICE_ID_SI7018 ?
			&snd_trident_capture_ops :
			&snd_trident_si7018_capture_ops);

	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	म_नकल(pcm->name, "Trident 4DWave");
	trident->pcm = pcm;

	अगर (trident->tlb.entries) अणु
		काष्ठा snd_pcm_substream *substream;
		क्रम (substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; substream; substream = substream->next)
			snd_pcm_set_managed_buffer(substream, SNDRV_DMA_TYPE_DEV_SG,
						   &trident->pci->dev,
						   64*1024, 128*1024);
		snd_pcm_set_managed_buffer(pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream,
					   SNDRV_DMA_TYPE_DEV,
					   &trident->pci->dev,
					   64*1024, 128*1024);
	पूर्ण अन्यथा अणु
		snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
					       &trident->pci->dev,
					       64*1024, 128*1024);
	पूर्ण

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_foldback_pcm
  
   Description: This routine रेजिस्टरs the 4DWave device क्रम foldback PCM support.
                
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.

   Returns:     None
  
  ---------------------------------------------------------------------------*/

पूर्णांक snd_trident_foldback_pcm(काष्ठा snd_trident *trident, पूर्णांक device)
अणु
	काष्ठा snd_pcm *foldback;
	पूर्णांक err;
	पूर्णांक num_chan = 3;
	काष्ठा snd_pcm_substream *substream;

	अगर (trident->device == TRIDENT_DEVICE_ID_NX)
		num_chan = 4;
	अगर ((err = snd_pcm_new(trident->card, "trident_dx_nx", device, 0, num_chan, &foldback)) < 0)
		वापस err;

	foldback->निजी_data = trident;
	अगर (trident->tlb.entries)
		snd_pcm_set_ops(foldback, SNDRV_PCM_STREAM_CAPTURE, &snd_trident_nx_foldback_ops);
	अन्यथा
		snd_pcm_set_ops(foldback, SNDRV_PCM_STREAM_CAPTURE, &snd_trident_foldback_ops);
	foldback->info_flags = 0;
	म_नकल(foldback->name, "Trident 4DWave");
	substream = foldback->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	म_नकल(substream->name, "Front Mixer");
	substream = substream->next;
	म_नकल(substream->name, "Reverb Mixer");
	substream = substream->next;
	म_नकल(substream->name, "Chorus Mixer");
	अगर (num_chan == 4) अणु
		substream = substream->next;
		म_नकल(substream->name, "Second AC'97 ADC");
	पूर्ण
	trident->foldback = foldback;

	अगर (trident->tlb.entries)
		snd_pcm_set_managed_buffer_all(foldback, SNDRV_DMA_TYPE_DEV_SG,
					       &trident->pci->dev,
					       0, 128*1024);
	अन्यथा
		snd_pcm_set_managed_buffer_all(foldback, SNDRV_DMA_TYPE_DEV,
					       &trident->pci->dev,
					       64*1024, 128*1024);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_spdअगर
  
   Description: This routine रेजिस्टरs the 4DWave-NX device क्रम SPDIF support.
                
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave-NX.

   Returns:     None
  
  ---------------------------------------------------------------------------*/

पूर्णांक snd_trident_spdअगर_pcm(काष्ठा snd_trident *trident, पूर्णांक device)
अणु
	काष्ठा snd_pcm *spdअगर;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(trident->card, "trident_dx_nx IEC958", device, 1, 0, &spdअगर)) < 0)
		वापस err;

	spdअगर->निजी_data = trident;
	अगर (trident->device != TRIDENT_DEVICE_ID_SI7018) अणु
		snd_pcm_set_ops(spdअगर, SNDRV_PCM_STREAM_PLAYBACK, &snd_trident_spdअगर_ops);
	पूर्ण अन्यथा अणु
		snd_pcm_set_ops(spdअगर, SNDRV_PCM_STREAM_PLAYBACK, &snd_trident_spdअगर_7018_ops);
	पूर्ण
	spdअगर->info_flags = 0;
	म_नकल(spdअगर->name, "Trident 4DWave IEC958");
	trident->spdअगर = spdअगर;

	snd_pcm_set_managed_buffer_all(spdअगर, SNDRV_DMA_TYPE_DEV,
				       &trident->pci->dev, 64*1024, 128*1024);

	वापस 0;
पूर्ण

/*
 *  Mixer part
 */


/*---------------------------------------------------------------------------
    snd_trident_spdअगर_control

    Description: enable/disable S/PDIF out from ac97 mixer
  ---------------------------------------------------------------------------*/

#घोषणा snd_trident_spdअगर_control_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_trident_spdअगर_control_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;

	spin_lock_irq(&trident->reg_lock);
	val = trident->spdअगर_ctrl;
	ucontrol->value.पूर्णांकeger.value[0] = val == kcontrol->निजी_value;
	spin_unlock_irq(&trident->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_spdअगर_control_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
	पूर्णांक change;

	val = ucontrol->value.पूर्णांकeger.value[0] ? (अचिन्हित अक्षर) kcontrol->निजी_value : 0x00;
	spin_lock_irq(&trident->reg_lock);
	/* S/PDIF C Channel bits 0-31 : 48khz, SCMS disabled */
	change = trident->spdअगर_ctrl != val;
	trident->spdअगर_ctrl = val;
	अगर (trident->device != TRIDENT_DEVICE_ID_SI7018) अणु
		अगर ((inb(TRID_REG(trident, NX_SPCTRL_SPCSO + 3)) & 0x10) == 0) अणु
			outl(trident->spdअगर_bits, TRID_REG(trident, NX_SPCSTATUS));
			outb(trident->spdअगर_ctrl, TRID_REG(trident, NX_SPCTRL_SPCSO + 3));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (trident->spdअगर == शून्य) अणु
			अचिन्हित पूर्णांक temp;
			outl(trident->spdअगर_bits, TRID_REG(trident, SI_SPDIF_CS));
			temp = inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)) & ~SPDIF_EN;
			अगर (val)
				temp |= SPDIF_EN;
			outl(temp, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
		पूर्ण
	पूर्ण
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_spdअगर_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,SWITCH),
	.info =		snd_trident_spdअगर_control_info,
	.get =		snd_trident_spdअगर_control_get,
	.put =		snd_trident_spdअगर_control_put,
	.निजी_value = 0x28,
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_spdअगर_शेष

    Description: put/get the S/PDIF शेष settings
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_spdअगर_शेष_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&trident->reg_lock);
	ucontrol->value.iec958.status[0] = (trident->spdअगर_bits >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (trident->spdअगर_bits >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (trident->spdअगर_bits >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (trident->spdअगर_bits >> 24) & 0xff;
	spin_unlock_irq(&trident->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = (ucontrol->value.iec958.status[0] << 0) |
	      (ucontrol->value.iec958.status[1] << 8) |
	      (ucontrol->value.iec958.status[2] << 16) |
	      (ucontrol->value.iec958.status[3] << 24);
	spin_lock_irq(&trident->reg_lock);
	change = trident->spdअगर_bits != val;
	trident->spdअगर_bits = val;
	अगर (trident->device != TRIDENT_DEVICE_ID_SI7018) अणु
		अगर ((inb(TRID_REG(trident, NX_SPCTRL_SPCSO + 3)) & 0x10) == 0)
			outl(trident->spdअगर_bits, TRID_REG(trident, NX_SPCSTATUS));
	पूर्ण अन्यथा अणु
		अगर (trident->spdअगर == शून्य)
			outl(trident->spdअगर_bits, TRID_REG(trident, SI_SPDIF_CS));
	पूर्ण
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_spdअगर_शेष =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =		snd_trident_spdअगर_शेष_info,
	.get =		snd_trident_spdअगर_शेष_get,
	.put =		snd_trident_spdअगर_शेष_put
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_spdअगर_mask

    Description: put/get the S/PDIF mask
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_spdअगर_mask =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
	.info =		snd_trident_spdअगर_mask_info,
	.get =		snd_trident_spdअगर_mask_get,
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_spdअगर_stream

    Description: put/get the S/PDIF stream settings
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_spdअगर_stream_info(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&trident->reg_lock);
	ucontrol->value.iec958.status[0] = (trident->spdअगर_pcm_bits >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (trident->spdअगर_pcm_bits >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (trident->spdअगर_pcm_bits >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (trident->spdअगर_pcm_bits >> 24) & 0xff;
	spin_unlock_irq(&trident->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = (ucontrol->value.iec958.status[0] << 0) |
	      (ucontrol->value.iec958.status[1] << 8) |
	      (ucontrol->value.iec958.status[2] << 16) |
	      (ucontrol->value.iec958.status[3] << 24);
	spin_lock_irq(&trident->reg_lock);
	change = trident->spdअगर_pcm_bits != val;
	trident->spdअगर_pcm_bits = val;
	अगर (trident->spdअगर != शून्य) अणु
		अगर (trident->device != TRIDENT_DEVICE_ID_SI7018) अणु
			outl(trident->spdअगर_pcm_bits, TRID_REG(trident, NX_SPCSTATUS));
		पूर्ण अन्यथा अणु
			outl(trident->spdअगर_bits, TRID_REG(trident, SI_SPDIF_CS));
		पूर्ण
	पूर्ण
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_spdअगर_stream =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
	.info =		snd_trident_spdअगर_stream_info,
	.get =		snd_trident_spdअगर_stream_get,
	.put =		snd_trident_spdअगर_stream_put
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_ac97_control

    Description: enable/disable rear path क्रम ac97
  ---------------------------------------------------------------------------*/

#घोषणा snd_trident_ac97_control_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_trident_ac97_control_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;

	spin_lock_irq(&trident->reg_lock);
	val = trident->ac97_ctrl = inl(TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	ucontrol->value.पूर्णांकeger.value[0] = (val & (1 << kcontrol->निजी_value)) ? 1 : 0;
	spin_unlock_irq(&trident->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_ac97_control_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
	पूर्णांक change = 0;

	spin_lock_irq(&trident->reg_lock);
	val = trident->ac97_ctrl = inl(TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	val &= ~(1 << kcontrol->निजी_value);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= 1 << kcontrol->निजी_value;
	change = val != trident->ac97_ctrl;
	trident->ac97_ctrl = val;
	outl(trident->ac97_ctrl = val, TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_ac97_rear_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Rear Path",
	.info =		snd_trident_ac97_control_info,
	.get =		snd_trident_ac97_control_get,
	.put =		snd_trident_ac97_control_put,
	.निजी_value = 4,
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_vol_control

    Description: wave & music volume control
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_vol_control_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_vol_control_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;

	val = trident->musicvol_wavevol;
	ucontrol->value.पूर्णांकeger.value[0] = 255 - ((val >> kcontrol->निजी_value) & 0xff);
	ucontrol->value.पूर्णांकeger.value[1] = 255 - ((val >> (kcontrol->निजी_value + 8)) & 0xff);
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_gvol, -6375, 25, 0);

अटल पूर्णांक snd_trident_vol_control_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;

	spin_lock_irq(&trident->reg_lock);
	val = trident->musicvol_wavevol;
	val &= ~(0xffff << kcontrol->निजी_value);
	val |= ((255 - (ucontrol->value.पूर्णांकeger.value[0] & 0xff)) |
	        ((255 - (ucontrol->value.पूर्णांकeger.value[1] & 0xff)) << 8)) << kcontrol->निजी_value;
	change = val != trident->musicvol_wavevol;
	outl(trident->musicvol_wavevol = val, TRID_REG(trident, T4D_MUSICVOL_WAVEVOL));
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_vol_music_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Music Playback Volume",
	.info =		snd_trident_vol_control_info,
	.get =		snd_trident_vol_control_get,
	.put =		snd_trident_vol_control_put,
	.निजी_value = 16,
	.tlv = अणु .p = db_scale_gvol पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_vol_wave_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Wave Playback Volume",
	.info =		snd_trident_vol_control_info,
	.get =		snd_trident_vol_control_get,
	.put =		snd_trident_vol_control_put,
	.निजी_value = 0,
	.tlv = अणु .p = db_scale_gvol पूर्ण,
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_pcm_vol_control

    Description: PCM front volume control
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_pcm_vol_control_info(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018)
		uinfo->value.पूर्णांकeger.max = 1023;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_vol_control_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];

	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		ucontrol->value.पूर्णांकeger.value[0] = 1023 - mix->vol;
	पूर्ण अन्यथा अणु
		ucontrol->value.पूर्णांकeger.value[0] = 255 - (mix->vol>>2);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_vol_control_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;

	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		val = 1023 - (ucontrol->value.पूर्णांकeger.value[0] & 1023);
	पूर्ण अन्यथा अणु
		val = (255 - (ucontrol->value.पूर्णांकeger.value[0] & 255)) << 2;
	पूर्ण
	spin_lock_irq(&trident->reg_lock);
	change = val != mix->vol;
	mix->vol = val;
	अगर (mix->voice != शून्य)
		snd_trident_ग_लिखो_vol_reg(trident, mix->voice, val);
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_pcm_vol_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "PCM Front Playback Volume",
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.count =	32,
	.info =		snd_trident_pcm_vol_control_info,
	.get =		snd_trident_pcm_vol_control_get,
	.put =		snd_trident_pcm_vol_control_put,
	/* FIXME: no tlv yet */
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_pcm_pan_control

    Description: PCM front pan control
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_pcm_pan_control_info(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 127;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_pan_control_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];

	ucontrol->value.पूर्णांकeger.value[0] = mix->pan;
	अगर (ucontrol->value.पूर्णांकeger.value[0] & 0x40) अणु
		ucontrol->value.पूर्णांकeger.value[0] = (0x3f - (ucontrol->value.पूर्णांकeger.value[0] & 0x3f));
	पूर्ण अन्यथा अणु
		ucontrol->value.पूर्णांकeger.value[0] |= 0x40;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_pan_control_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];
	अचिन्हित अक्षर val;
	पूर्णांक change = 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0] & 0x40)
		val = ucontrol->value.पूर्णांकeger.value[0] & 0x3f;
	अन्यथा
		val = (0x3f - (ucontrol->value.पूर्णांकeger.value[0] & 0x3f)) | 0x40;
	spin_lock_irq(&trident->reg_lock);
	change = val != mix->pan;
	mix->pan = val;
	अगर (mix->voice != शून्य)
		snd_trident_ग_लिखो_pan_reg(trident, mix->voice, val);
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_pcm_pan_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "PCM Pan Playback Control",
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.count =	32,
	.info =		snd_trident_pcm_pan_control_info,
	.get =		snd_trident_pcm_pan_control_get,
	.put =		snd_trident_pcm_pan_control_put,
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_pcm_rvol_control

    Description: PCM reverb volume control
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_pcm_rvol_control_info(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 127;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_rvol_control_get(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];

	ucontrol->value.पूर्णांकeger.value[0] = 127 - mix->rvol;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_rvol_control_put(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];
	अचिन्हित लघु val;
	पूर्णांक change = 0;

	val = 0x7f - (ucontrol->value.पूर्णांकeger.value[0] & 0x7f);
	spin_lock_irq(&trident->reg_lock);
	change = val != mix->rvol;
	mix->rvol = val;
	अगर (mix->voice != शून्य)
		snd_trident_ग_लिखो_rvol_reg(trident, mix->voice, val);
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_crvol, -3175, 25, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_pcm_rvol_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "PCM Reverb Playback Volume",
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.count = 	32,
	.info =		snd_trident_pcm_rvol_control_info,
	.get =		snd_trident_pcm_rvol_control_get,
	.put =		snd_trident_pcm_rvol_control_put,
	.tlv = अणु .p = db_scale_crvol पूर्ण,
पूर्ण;

/*---------------------------------------------------------------------------
    snd_trident_pcm_cvol_control

    Description: PCM chorus volume control
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_pcm_cvol_control_info(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 127;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_cvol_control_get(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];

	ucontrol->value.पूर्णांकeger.value[0] = 127 - mix->cvol;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_cvol_control_put(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_trident *trident = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];
	अचिन्हित लघु val;
	पूर्णांक change = 0;

	val = 0x7f - (ucontrol->value.पूर्णांकeger.value[0] & 0x7f);
	spin_lock_irq(&trident->reg_lock);
	change = val != mix->cvol;
	mix->cvol = val;
	अगर (mix->voice != शून्य)
		snd_trident_ग_लिखो_cvol_reg(trident, mix->voice, val);
	spin_unlock_irq(&trident->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_trident_pcm_cvol_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "PCM Chorus Playback Volume",
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.count =	32,
	.info =		snd_trident_pcm_cvol_control_info,
	.get =		snd_trident_pcm_cvol_control_get,
	.put =		snd_trident_pcm_cvol_control_put,
	.tlv = अणु .p = db_scale_crvol पूर्ण,
पूर्ण;

अटल व्योम snd_trident_notअगरy_pcm_change1(काष्ठा snd_card *card,
					   काष्ठा snd_kcontrol *kctl,
					   पूर्णांक num, पूर्णांक activate)
अणु
	काष्ठा snd_ctl_elem_id id;

	अगर (! kctl)
		वापस;
	अगर (activate)
		kctl->vd[num].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	अन्यथा
		kctl->vd[num].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO,
		       snd_ctl_build_ioff(&id, kctl, num));
पूर्ण

अटल व्योम snd_trident_notअगरy_pcm_change(काष्ठा snd_trident *trident,
					  काष्ठा snd_trident_pcm_mixer *पंचांगix,
					  पूर्णांक num, पूर्णांक activate)
अणु
	snd_trident_notअगरy_pcm_change1(trident->card, trident->ctl_vol, num, activate);
	snd_trident_notअगरy_pcm_change1(trident->card, trident->ctl_pan, num, activate);
	snd_trident_notअगरy_pcm_change1(trident->card, trident->ctl_rvol, num, activate);
	snd_trident_notअगरy_pcm_change1(trident->card, trident->ctl_cvol, num, activate);
पूर्ण

अटल पूर्णांक snd_trident_pcm_mixer_build(काष्ठा snd_trident *trident,
				       काष्ठा snd_trident_voice *voice,
				       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident_pcm_mixer *पंचांगix;

	अगर (snd_BUG_ON(!trident || !voice || !substream))
		वापस -EINVAL;
	पंचांगix = &trident->pcm_mixer[substream->number];
	पंचांगix->voice = voice;
	पंचांगix->vol = T4D_DEFAULT_PCM_VOL;
	पंचांगix->pan = T4D_DEFAULT_PCM_PAN;
	पंचांगix->rvol = T4D_DEFAULT_PCM_RVOL;
	पंचांगix->cvol = T4D_DEFAULT_PCM_CVOL;
	snd_trident_notअगरy_pcm_change(trident, पंचांगix, substream->number, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_pcm_mixer_मुक्त(काष्ठा snd_trident *trident, काष्ठा snd_trident_voice *voice, काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_trident_pcm_mixer *पंचांगix;

	अगर (snd_BUG_ON(!trident || !substream))
		वापस -EINVAL;
	पंचांगix = &trident->pcm_mixer[substream->number];
	पंचांगix->voice = शून्य;
	snd_trident_notअगरy_pcm_change(trident, पंचांगix, substream->number, 0);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_mixer
  
   Description: This routine रेजिस्टरs the 4DWave device क्रम mixer support.
                
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.

   Returns:     None
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_mixer(काष्ठा snd_trident *trident, पूर्णांक pcm_spdअगर_device)
अणु
	काष्ठा snd_ac97_ढाँचा _ac97;
	काष्ठा snd_card *card = trident->card;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_ctl_elem_value *uctl;
	पूर्णांक idx, err, retries = 2;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_trident_codec_ग_लिखो,
		.पढ़ो = snd_trident_codec_पढ़ो,
	पूर्ण;

	uctl = kzalloc(माप(*uctl), GFP_KERNEL);
	अगर (!uctl)
		वापस -ENOMEM;

	अगर ((err = snd_ac97_bus(trident->card, 0, &ops, शून्य, &trident->ac97_bus)) < 0)
		जाओ __out;

	स_रखो(&_ac97, 0, माप(_ac97));
	_ac97.निजी_data = trident;
	trident->ac97_detect = 1;

      __again:
	अगर ((err = snd_ac97_mixer(trident->ac97_bus, &_ac97, &trident->ac97)) < 0) अणु
		अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
			अगर ((err = snd_trident_sis_reset(trident)) < 0)
				जाओ __out;
			अगर (retries-- > 0)
				जाओ __again;
			err = -EIO;
		पूर्ण
		जाओ __out;
	पूर्ण
	
	/* secondary codec? */
	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018 &&
	    (inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)) & SI_AC97_PRIMARY_READY) != 0) अणु
		_ac97.num = 1;
		err = snd_ac97_mixer(trident->ac97_bus, &_ac97, &trident->ac97_sec);
		अगर (err < 0)
			dev_err(trident->card->dev,
				"SI7018: the secondary codec - invalid access\n");
#अगर 0	// only क्रम my testing purpose --jk
		अणु
			काष्ठा snd_ac97 *mc97;
			err = snd_ac97_modem(trident->card, &_ac97, &mc97);
			अगर (err < 0)
				dev_err(trident->card->dev,
					"snd_ac97_modem returned error %i\n", err);
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	
	trident->ac97_detect = 0;

	अगर (trident->device != TRIDENT_DEVICE_ID_SI7018) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_trident_vol_wave_control, trident))) < 0)
			जाओ __out;
		kctl->put(kctl, uctl);
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_trident_vol_music_control, trident))) < 0)
			जाओ __out;
		kctl->put(kctl, uctl);
		outl(trident->musicvol_wavevol = 0x00000000, TRID_REG(trident, T4D_MUSICVOL_WAVEVOL));
	पूर्ण अन्यथा अणु
		outl(trident->musicvol_wavevol = 0xffff0000, TRID_REG(trident, T4D_MUSICVOL_WAVEVOL));
	पूर्ण

	क्रम (idx = 0; idx < 32; idx++) अणु
		काष्ठा snd_trident_pcm_mixer *पंचांगix;
		
		पंचांगix = &trident->pcm_mixer[idx];
		पंचांगix->voice = शून्य;
	पूर्ण
	अगर ((trident->ctl_vol = snd_ctl_new1(&snd_trident_pcm_vol_control, trident)) == शून्य)
		जाओ __nomem;
	अगर ((err = snd_ctl_add(card, trident->ctl_vol)))
		जाओ __out;
		
	अगर ((trident->ctl_pan = snd_ctl_new1(&snd_trident_pcm_pan_control, trident)) == शून्य)
		जाओ __nomem;
	अगर ((err = snd_ctl_add(card, trident->ctl_pan)))
		जाओ __out;

	अगर ((trident->ctl_rvol = snd_ctl_new1(&snd_trident_pcm_rvol_control, trident)) == शून्य)
		जाओ __nomem;
	अगर ((err = snd_ctl_add(card, trident->ctl_rvol)))
		जाओ __out;

	अगर ((trident->ctl_cvol = snd_ctl_new1(&snd_trident_pcm_cvol_control, trident)) == शून्य)
		जाओ __nomem;
	अगर ((err = snd_ctl_add(card, trident->ctl_cvol)))
		जाओ __out;

	अगर (trident->device == TRIDENT_DEVICE_ID_NX) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_trident_ac97_rear_control, trident))) < 0)
			जाओ __out;
		kctl->put(kctl, uctl);
	पूर्ण
	अगर (trident->device == TRIDENT_DEVICE_ID_NX || trident->device == TRIDENT_DEVICE_ID_SI7018) अणु

		kctl = snd_ctl_new1(&snd_trident_spdअगर_control, trident);
		अगर (kctl == शून्य) अणु
			err = -ENOMEM;
			जाओ __out;
		पूर्ण
		अगर (trident->ac97->ext_id & AC97_EI_SPDIF)
			kctl->id.index++;
		अगर (trident->ac97_sec && (trident->ac97_sec->ext_id & AC97_EI_SPDIF))
			kctl->id.index++;
		idx = kctl->id.index;
		अगर ((err = snd_ctl_add(card, kctl)) < 0)
			जाओ __out;
		kctl->put(kctl, uctl);

		kctl = snd_ctl_new1(&snd_trident_spdअगर_शेष, trident);
		अगर (kctl == शून्य) अणु
			err = -ENOMEM;
			जाओ __out;
		पूर्ण
		kctl->id.index = idx;
		kctl->id.device = pcm_spdअगर_device;
		अगर ((err = snd_ctl_add(card, kctl)) < 0)
			जाओ __out;

		kctl = snd_ctl_new1(&snd_trident_spdअगर_mask, trident);
		अगर (kctl == शून्य) अणु
			err = -ENOMEM;
			जाओ __out;
		पूर्ण
		kctl->id.index = idx;
		kctl->id.device = pcm_spdअगर_device;
		अगर ((err = snd_ctl_add(card, kctl)) < 0)
			जाओ __out;

		kctl = snd_ctl_new1(&snd_trident_spdअगर_stream, trident);
		अगर (kctl == शून्य) अणु
			err = -ENOMEM;
			जाओ __out;
		पूर्ण
		kctl->id.index = idx;
		kctl->id.device = pcm_spdअगर_device;
		अगर ((err = snd_ctl_add(card, kctl)) < 0)
			जाओ __out;
		trident->spdअगर_pcm_ctl = kctl;
	पूर्ण

	err = 0;
	जाओ __out;

 __nomem:
	err = -ENOMEM;

 __out:
	kमुक्त(uctl);

	वापस err;
पूर्ण

/*
 * gameport पूर्णांकerface
 */

#अगर IS_REACHABLE(CONFIG_GAMEPORT)

अटल अचिन्हित अक्षर snd_trident_gameport_पढ़ो(काष्ठा gameport *gameport)
अणु
	काष्ठा snd_trident *chip = gameport_get_port_data(gameport);

	अगर (snd_BUG_ON(!chip))
		वापस 0;
	वापस inb(TRID_REG(chip, GAMEPORT_LEGACY));
पूर्ण

अटल व्योम snd_trident_gameport_trigger(काष्ठा gameport *gameport)
अणु
	काष्ठा snd_trident *chip = gameport_get_port_data(gameport);

	अगर (snd_BUG_ON(!chip))
		वापस;
	outb(0xff, TRID_REG(chip, GAMEPORT_LEGACY));
पूर्ण

अटल पूर्णांक snd_trident_gameport_cooked_पढ़ो(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *buttons)
अणु
	काष्ठा snd_trident *chip = gameport_get_port_data(gameport);
	पूर्णांक i;

	अगर (snd_BUG_ON(!chip))
		वापस 0;

	*buttons = (~inb(TRID_REG(chip, GAMEPORT_LEGACY)) >> 4) & 0xf;

	क्रम (i = 0; i < 4; i++) अणु
		axes[i] = inw(TRID_REG(chip, GAMEPORT_AXES + i * 2));
		अगर (axes[i] == 0xffff) axes[i] = -1;
	पूर्ण
        
        वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_gameport_खोलो(काष्ठा gameport *gameport, पूर्णांक mode)
अणु
	काष्ठा snd_trident *chip = gameport_get_port_data(gameport);

	अगर (snd_BUG_ON(!chip))
		वापस 0;

	चयन (mode) अणु
		हाल GAMEPORT_MODE_COOKED:
			outb(GAMEPORT_MODE_ADC, TRID_REG(chip, GAMEPORT_GCR));
			msleep(20);
			वापस 0;
		हाल GAMEPORT_MODE_RAW:
			outb(0, TRID_REG(chip, GAMEPORT_GCR));
			वापस 0;
		शेष:
			वापस -1;
	पूर्ण
पूर्ण

पूर्णांक snd_trident_create_gameport(काष्ठा snd_trident *chip)
अणु
	काष्ठा gameport *gp;

	chip->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(chip->card->dev,
			"cannot allocate memory for gameport\n");
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "Trident 4DWave");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(chip->pci));
	gameport_set_dev_parent(gp, &chip->pci->dev);

	gameport_set_port_data(gp, chip);
	gp->fuzz = 64;
	gp->पढ़ो = snd_trident_gameport_पढ़ो;
	gp->trigger = snd_trident_gameport_trigger;
	gp->cooked_पढ़ो = snd_trident_gameport_cooked_पढ़ो;
	gp->खोलो = snd_trident_gameport_खोलो;

	gameport_रेजिस्टर_port(gp);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_trident_मुक्त_gameport(काष्ठा snd_trident *chip)
अणु
	अगर (chip->gameport) अणु
		gameport_unरेजिस्टर_port(chip->gameport);
		chip->gameport = शून्य;
	पूर्ण
पूर्ण
#अन्यथा
पूर्णांक snd_trident_create_gameport(काष्ठा snd_trident *chip) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_trident_मुक्त_gameport(काष्ठा snd_trident *chip) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_GAMEPORT */

/*
 * delay क्रम 1 tick
 */
अटल अंतरभूत व्योम करो_delay(काष्ठा snd_trident *chip)
अणु
	schedule_समयout_unपूर्णांकerruptible(1);
पूर्ण

/*
 *  SiS reset routine
 */

अटल पूर्णांक snd_trident_sis_reset(काष्ठा snd_trident *trident)
अणु
	अचिन्हित दीर्घ end_समय;
	अचिन्हित पूर्णांक i;
	पूर्णांक r;

	r = trident->in_suspend ? 0 : 2;	/* count of retries */
      __si7018_retry:
	pci_ग_लिखो_config_byte(trident->pci, 0x46, 0x04);	/* SOFTWARE RESET */
	udelay(100);
	pci_ग_लिखो_config_byte(trident->pci, 0x46, 0x00);
	udelay(100);
	/* disable AC97 GPIO पूर्णांकerrupt */
	outb(0x00, TRID_REG(trident, SI_AC97_GPIO));
	/* initialize serial पूर्णांकerface, क्रमce cold reset */
	i = PCMOUT|SURROUT|CENTEROUT|LFEOUT|SECONDARY_ID|COLD_RESET;
	outl(i, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
	udelay(1000);
	/* हटाओ cold reset */
	i &= ~COLD_RESET;
	outl(i, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
	udelay(2000);
	/* रुको, until the codec is पढ़ोy */
	end_समय = (jअगरfies + (HZ * 3) / 4) + 1;
	करो अणु
		अगर ((inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)) & SI_AC97_PRIMARY_READY) != 0)
			जाओ __si7018_ok;
		करो_delay(trident);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	dev_err(trident->card->dev, "AC'97 codec ready error [0x%x]\n",
		inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)));
	अगर (r-- > 0) अणु
		end_समय = jअगरfies + HZ;
		करो अणु
			करो_delay(trident);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
		जाओ __si7018_retry;
	पूर्ण
      __si7018_ok:
	/* रुको क्रम the second codec */
	करो अणु
		अगर ((inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)) & SI_AC97_SECONDARY_READY) != 0)
			अवरोध;
		करो_delay(trident);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	/* enable 64 channel mode */
	outl(BANK_B_EN, TRID_REG(trident, T4D_LFO_GC_CIR));
	वापस 0;
पूर्ण

/*  
 *  /proc पूर्णांकerface
 */

अटल व्योम snd_trident_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_trident *trident = entry->निजी_data;
	अक्षर *s;

	चयन (trident->device) अणु
	हाल TRIDENT_DEVICE_ID_SI7018:
		s = "SiS 7018 Audio";
		अवरोध;
	हाल TRIDENT_DEVICE_ID_DX:
		s = "Trident 4DWave PCI DX";
		अवरोध;
	हाल TRIDENT_DEVICE_ID_NX:
		s = "Trident 4DWave PCI NX";
		अवरोध;
	शेष:
		s = "???";
	पूर्ण
	snd_iम_लिखो(buffer, "%s\n\n", s);
	snd_iम_लिखो(buffer, "Spurious IRQs    : %d\n", trident->spurious_irq_count);
	snd_iम_लिखो(buffer, "Spurious IRQ dlta: %d\n", trident->spurious_irq_max_delta);
	अगर (trident->device == TRIDENT_DEVICE_ID_NX || trident->device == TRIDENT_DEVICE_ID_SI7018)
		snd_iम_लिखो(buffer, "IEC958 Mixer Out : %s\n", trident->spdअगर_ctrl == 0x28 ? "on" : "off");
	अगर (trident->device == TRIDENT_DEVICE_ID_NX) अणु
		snd_iम_लिखो(buffer, "Rear Speakers    : %s\n", trident->ac97_ctrl & 0x00000010 ? "on" : "off");
		अगर (trident->tlb.entries) अणु
			snd_iम_लिखो(buffer,"\nVirtual Memory\n");
			snd_iम_लिखो(buffer, "Memory Maximum : %d\n", trident->tlb.memhdr->size);
			snd_iम_लिखो(buffer, "Memory Used    : %d\n", trident->tlb.memhdr->used);
			snd_iम_लिखो(buffer, "Memory Free    : %d\n", snd_util_mem_avail(trident->tlb.memhdr));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_trident_proc_init(काष्ठा snd_trident *trident)
अणु
	स्थिर अक्षर *s = "trident";
	
	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018)
		s = "sis7018";
	snd_card_ro_proc_new(trident->card, s, trident, snd_trident_proc_पढ़ो);
पूर्ण

अटल पूर्णांक snd_trident_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_trident *trident = device->device_data;
	वापस snd_trident_मुक्त(trident);
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_tlb_alloc
  
   Description: Allocate and set up the TLB page table on 4D NX.
		Each entry has 4 bytes (physical PCI address).
                
   Parameters:  trident - poपूर्णांकer to target device class क्रम 4DWave.

   Returns:     0 or negative error code
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_tlb_alloc(काष्ठा snd_trident *trident)
अणु
	पूर्णांक i;

	/* TLB array must be aligned to 16kB !!! so we allocate
	   32kB region and correct offset when necessary */

	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &trident->pci->dev,
				2 * SNDRV_TRIDENT_MAX_PAGES * 4, &trident->tlb.buffer) < 0) अणु
		dev_err(trident->card->dev, "unable to allocate TLB buffer\n");
		वापस -ENOMEM;
	पूर्ण
	trident->tlb.entries = (__le32 *)ALIGN((अचिन्हित दीर्घ)trident->tlb.buffer.area, SNDRV_TRIDENT_MAX_PAGES * 4);
	trident->tlb.entries_dmaaddr = ALIGN(trident->tlb.buffer.addr, SNDRV_TRIDENT_MAX_PAGES * 4);
	/* allocate shaकरोw TLB page table (भव addresses) */
	trident->tlb.shaकरोw_entries =
		vदो_स्मृति(array_size(SNDRV_TRIDENT_MAX_PAGES,
				   माप(अचिन्हित दीर्घ)));
	अगर (!trident->tlb.shaकरोw_entries)
		वापस -ENOMEM;

	/* allocate and setup silent page and initialise TLB entries */
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &trident->pci->dev,
				SNDRV_TRIDENT_PAGE_SIZE, &trident->tlb.silent_page) < 0) अणु
		dev_err(trident->card->dev, "unable to allocate silent page\n");
		वापस -ENOMEM;
	पूर्ण
	स_रखो(trident->tlb.silent_page.area, 0, SNDRV_TRIDENT_PAGE_SIZE);
	क्रम (i = 0; i < SNDRV_TRIDENT_MAX_PAGES; i++) अणु
		trident->tlb.entries[i] = cpu_to_le32(trident->tlb.silent_page.addr & ~(SNDRV_TRIDENT_PAGE_SIZE-1));
		trident->tlb.shaकरोw_entries[i] = (अचिन्हित दीर्घ)trident->tlb.silent_page.area;
	पूर्ण

	/* use emu memory block manager code to manage tlb page allocation */
	trident->tlb.memhdr = snd_util_memhdr_new(SNDRV_TRIDENT_PAGE_SIZE * SNDRV_TRIDENT_MAX_PAGES);
	अगर (trident->tlb.memhdr == शून्य)
		वापस -ENOMEM;

	trident->tlb.memhdr->block_extra_size = माप(काष्ठा snd_trident_memblk_arg);
	वापस 0;
पूर्ण

/*
 * initialize 4D DX chip
 */

अटल व्योम snd_trident_stop_all_voices(काष्ठा snd_trident *trident)
अणु
	outl(0xffffffff, TRID_REG(trident, T4D_STOP_A));
	outl(0xffffffff, TRID_REG(trident, T4D_STOP_B));
	outl(0, TRID_REG(trident, T4D_AINTEN_A));
	outl(0, TRID_REG(trident, T4D_AINTEN_B));
पूर्ण

अटल पूर्णांक snd_trident_4d_dx_init(काष्ठा snd_trident *trident)
अणु
	काष्ठा pci_dev *pci = trident->pci;
	अचिन्हित दीर्घ end_समय;

	/* reset the legacy configuration and whole audio/wavetable block */
	pci_ग_लिखो_config_dword(pci, 0x40, 0);	/* DDMA */
	pci_ग_लिखो_config_byte(pci, 0x44, 0);	/* ports */
	pci_ग_लिखो_config_byte(pci, 0x45, 0);	/* Legacy DMA */
	pci_ग_लिखो_config_byte(pci, 0x46, 4); /* reset */
	udelay(100);
	pci_ग_लिखो_config_byte(pci, 0x46, 0); /* release reset */
	udelay(100);
	
	/* warm reset of the AC'97 codec */
	outl(0x00000001, TRID_REG(trident, DX_ACR2_AC97_COM_STAT));
	udelay(100);
	outl(0x00000000, TRID_REG(trident, DX_ACR2_AC97_COM_STAT));
	/* DAC on, disable SB IRQ and try to क्रमce ADC valid संकेत */
	trident->ac97_ctrl = 0x0000004a;
	outl(trident->ac97_ctrl, TRID_REG(trident, DX_ACR2_AC97_COM_STAT));
	/* रुको, until the codec is पढ़ोy */
	end_समय = (jअगरfies + (HZ * 3) / 4) + 1;
	करो अणु
		अगर ((inl(TRID_REG(trident, DX_ACR2_AC97_COM_STAT)) & 0x0010) != 0)
			जाओ __dx_ok;
		करो_delay(trident);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	dev_err(trident->card->dev, "AC'97 codec ready error\n");
	वापस -EIO;

 __dx_ok:
	snd_trident_stop_all_voices(trident);

	वापस 0;
पूर्ण

/*
 * initialize 4D NX chip
 */
अटल पूर्णांक snd_trident_4d_nx_init(काष्ठा snd_trident *trident)
अणु
	काष्ठा pci_dev *pci = trident->pci;
	अचिन्हित दीर्घ end_समय;

	/* reset the legacy configuration and whole audio/wavetable block */
	pci_ग_लिखो_config_dword(pci, 0x40, 0);	/* DDMA */
	pci_ग_लिखो_config_byte(pci, 0x44, 0);	/* ports */
	pci_ग_लिखो_config_byte(pci, 0x45, 0);	/* Legacy DMA */

	pci_ग_लिखो_config_byte(pci, 0x46, 1); /* reset */
	udelay(100);
	pci_ग_लिखो_config_byte(pci, 0x46, 0); /* release reset */
	udelay(100);

	/* warm reset of the AC'97 codec */
	outl(0x00000001, TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	udelay(100);
	outl(0x00000000, TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	/* रुको, until the codec is पढ़ोy */
	end_समय = (jअगरfies + (HZ * 3) / 4) + 1;
	करो अणु
		अगर ((inl(TRID_REG(trident, NX_ACR0_AC97_COM_STAT)) & 0x0008) != 0)
			जाओ __nx_ok;
		करो_delay(trident);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	dev_err(trident->card->dev, "AC'97 codec ready error [0x%x]\n",
		inl(TRID_REG(trident, NX_ACR0_AC97_COM_STAT)));
	वापस -EIO;

 __nx_ok:
	/* DAC on */
	trident->ac97_ctrl = 0x00000002;
	outl(trident->ac97_ctrl, TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	/* disable SB IRQ */
	outl(NX_SB_IRQ_DISABLE, TRID_REG(trident, T4D_MISCINT));

	snd_trident_stop_all_voices(trident);

	अगर (trident->tlb.entries != शून्य) अणु
		अचिन्हित पूर्णांक i;
		/* enable भव addressing via TLB */
		i = trident->tlb.entries_dmaaddr;
		i |= 0x00000001;
		outl(i, TRID_REG(trident, NX_TLBC));
	पूर्ण अन्यथा अणु
		outl(0, TRID_REG(trident, NX_TLBC));
	पूर्ण
	/* initialize S/PDIF */
	outl(trident->spdअगर_bits, TRID_REG(trident, NX_SPCSTATUS));
	outb(trident->spdअगर_ctrl, TRID_REG(trident, NX_SPCTRL_SPCSO + 3));

	वापस 0;
पूर्ण

/*
 * initialize sis7018 chip
 */
अटल पूर्णांक snd_trident_sis_init(काष्ठा snd_trident *trident)
अणु
	पूर्णांक err;

	अगर ((err = snd_trident_sis_reset(trident)) < 0)
		वापस err;

	snd_trident_stop_all_voices(trident);

	/* initialize S/PDIF */
	outl(trident->spdअगर_bits, TRID_REG(trident, SI_SPDIF_CS));

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_create
  
   Description: This routine will create the device specअगरic class क्रम
                the 4DWave card. It will also perक्रमm basic initialization.
                
   Parameters:  card  - which card to create
                pci   - पूर्णांकerface to PCI bus resource info
                dma1ptr - playback dma buffer
                dma2ptr - capture dma buffer
                irqptr  -  पूर्णांकerrupt resource info

   Returns:     4DWave device class निजी data
  
  ---------------------------------------------------------------------------*/

पूर्णांक snd_trident_create(काष्ठा snd_card *card,
		       काष्ठा pci_dev *pci,
		       पूर्णांक pcm_streams,
		       पूर्णांक pcm_spdअगर_device,
		       पूर्णांक max_wavetable_size,
		       काष्ठा snd_trident ** rtrident)
अणु
	काष्ठा snd_trident *trident;
	पूर्णांक i, err;
	काष्ठा snd_trident_voice *voice;
	काष्ठा snd_trident_pcm_mixer *पंचांगix;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_trident_dev_मुक्त,
	पूर्ण;

	*rtrident = शून्य;

	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	/* check, अगर we can restrict PCI DMA transfers to 30 bits */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(30))) अणु
		dev_err(card->dev,
			"architecture does not support 30bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण
	
	trident = kzalloc(माप(*trident), GFP_KERNEL);
	अगर (trident == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	trident->device = (pci->venकरोr << 16) | pci->device;
	trident->card = card;
	trident->pci = pci;
	spin_lock_init(&trident->reg_lock);
	spin_lock_init(&trident->event_lock);
	spin_lock_init(&trident->voice_alloc);
	अगर (pcm_streams < 1)
		pcm_streams = 1;
	अगर (pcm_streams > 32)
		pcm_streams = 32;
	trident->ChanPCM = pcm_streams;
	अगर (max_wavetable_size < 0 )
		max_wavetable_size = 0;
	trident->synth.max_size = max_wavetable_size * 1024;
	trident->irq = -1;

	trident->midi_port = TRID_REG(trident, T4D_MPU401_BASE);
	pci_set_master(pci);

	अगर ((err = pci_request_regions(pci, "Trident Audio")) < 0) अणु
		kमुक्त(trident);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	trident->port = pci_resource_start(pci, 0);

	अगर (request_irq(pci->irq, snd_trident_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, trident)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_trident_मुक्त(trident);
		वापस -EBUSY;
	पूर्ण
	trident->irq = pci->irq;
	card->sync_irq = trident->irq;

	/* allocate 16k-aligned TLB क्रम NX cards */
	trident->tlb.entries = शून्य;
	trident->tlb.buffer.area = शून्य;
	अगर (trident->device == TRIDENT_DEVICE_ID_NX) अणु
		अगर ((err = snd_trident_tlb_alloc(trident)) < 0) अणु
			snd_trident_मुक्त(trident);
			वापस err;
		पूर्ण
	पूर्ण

	trident->spdअगर_bits = trident->spdअगर_pcm_bits = SNDRV_PCM_DEFAULT_CON_SPDIF;

	/* initialize chip */
	चयन (trident->device) अणु
	हाल TRIDENT_DEVICE_ID_DX:
		err = snd_trident_4d_dx_init(trident);
		अवरोध;
	हाल TRIDENT_DEVICE_ID_NX:
		err = snd_trident_4d_nx_init(trident);
		अवरोध;
	हाल TRIDENT_DEVICE_ID_SI7018:
		err = snd_trident_sis_init(trident);
		अवरोध;
	शेष:
		snd_BUG();
		अवरोध;
	पूर्ण
	अगर (err < 0) अणु
		snd_trident_मुक्त(trident);
		वापस err;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, trident, &ops)) < 0) अणु
		snd_trident_मुक्त(trident);
		वापस err;
	पूर्ण

	अगर ((err = snd_trident_mixer(trident, pcm_spdअगर_device)) < 0)
		वापस err;
	
	/* initialise synth voices */
	क्रम (i = 0; i < 64; i++) अणु
		voice = &trident->synth.voices[i];
		voice->number = i;
		voice->trident = trident;
	पूर्ण
	/* initialize pcm mixer entries */
	क्रम (i = 0; i < 32; i++) अणु
		पंचांगix = &trident->pcm_mixer[i];
		पंचांगix->vol = T4D_DEFAULT_PCM_VOL;
		पंचांगix->pan = T4D_DEFAULT_PCM_PAN;
		पंचांगix->rvol = T4D_DEFAULT_PCM_RVOL;
		पंचांगix->cvol = T4D_DEFAULT_PCM_CVOL;
	पूर्ण

	snd_trident_enable_eso(trident);

	snd_trident_proc_init(trident);
	*rtrident = trident;
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_मुक्त
  
   Description: This routine will मुक्त the device specअगरic class क्रम
                the 4DWave card. 
                
   Parameters:  trident  - device specअगरic निजी data क्रम 4DWave card

   Returns:     None.
  
  ---------------------------------------------------------------------------*/

अटल पूर्णांक snd_trident_मुक्त(काष्ठा snd_trident *trident)
अणु
	snd_trident_मुक्त_gameport(trident);
	snd_trident_disable_eso(trident);
	// Disable S/PDIF out
	अगर (trident->device == TRIDENT_DEVICE_ID_NX)
		outb(0x00, TRID_REG(trident, NX_SPCTRL_SPCSO + 3));
	अन्यथा अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		outl(0, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
	पूर्ण
	अगर (trident->irq >= 0)
		मुक्त_irq(trident->irq, trident);
	अगर (trident->tlb.buffer.area) अणु
		outl(0, TRID_REG(trident, NX_TLBC));
		snd_util_memhdr_मुक्त(trident->tlb.memhdr);
		अगर (trident->tlb.silent_page.area)
			snd_dma_मुक्त_pages(&trident->tlb.silent_page);
		vमुक्त(trident->tlb.shaकरोw_entries);
		snd_dma_मुक्त_pages(&trident->tlb.buffer);
	पूर्ण
	pci_release_regions(trident->pci);
	pci_disable_device(trident->pci);
	kमुक्त(trident);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------
   snd_trident_पूर्णांकerrupt
  
   Description: ISR क्रम Trident 4DWave device
                
   Parameters:  trident  - device specअगरic निजी data क्रम 4DWave card

   Problems:    It seems that Trident chips generates पूर्णांकerrupts more than
                one समय in special हालs. The spurious पूर्णांकerrupts are
                detected via sample समयr (T4D_STIMER) and computing
                corresponding delta value. The limits are detected with
                the method try & fail so it is possible that it won't
                work on all computers. [jaroslav]

   Returns:     None.
  
  ---------------------------------------------------------------------------*/

अटल irqवापस_t snd_trident_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_trident *trident = dev_id;
	अचिन्हित पूर्णांक audio_पूर्णांक, chn_पूर्णांक, sसमयr, channel, mask, पंचांगp;
	पूर्णांक delta;
	काष्ठा snd_trident_voice *voice;

	audio_पूर्णांक = inl(TRID_REG(trident, T4D_MISCINT));
	अगर ((audio_पूर्णांक & (ADDRESS_IRQ|MPU401_IRQ)) == 0)
		वापस IRQ_NONE;
	अगर (audio_पूर्णांक & ADDRESS_IRQ) अणु
		// get पूर्णांकerrupt status क्रम all channels
		spin_lock(&trident->reg_lock);
		sसमयr = inl(TRID_REG(trident, T4D_STIMER)) & 0x00ffffff;
		chn_पूर्णांक = inl(TRID_REG(trident, T4D_AINT_A));
		अगर (chn_पूर्णांक == 0)
			जाओ __skip1;
		outl(chn_पूर्णांक, TRID_REG(trident, T4D_AINT_A));	/* ack */
	      __skip1:
		chn_पूर्णांक = inl(TRID_REG(trident, T4D_AINT_B));
		अगर (chn_पूर्णांक == 0)
			जाओ __skip2;
		क्रम (channel = 63; channel >= 32; channel--) अणु
			mask = 1 << (channel&0x1f);
			अगर ((chn_पूर्णांक & mask) == 0)
				जारी;
			voice = &trident->synth.voices[channel];
			अगर (!voice->pcm || voice->substream == शून्य) अणु
				outl(mask, TRID_REG(trident, T4D_STOP_B));
				जारी;
			पूर्ण
			delta = (पूर्णांक)sसमयr - (पूर्णांक)voice->sसमयr;
			अगर (delta < 0)
				delta = -delta;
			अगर ((अचिन्हित पूर्णांक)delta < voice->spurious_threshold) अणु
				/* करो some statistics here */
				trident->spurious_irq_count++;
				अगर (trident->spurious_irq_max_delta < (अचिन्हित पूर्णांक)delta)
					trident->spurious_irq_max_delta = delta;
				जारी;
			पूर्ण
			voice->sसमयr = sसमयr;
			अगर (voice->isync) अणु
				अगर (!voice->isync3) अणु
					पंचांगp = inw(TRID_REG(trident, T4D_SBBL_SBCL));
					अगर (trident->bDMAStart & 0x40)
						पंचांगp >>= 1;
					अगर (पंचांगp > 0)
						पंचांगp = voice->isync_max - पंचांगp;
				पूर्ण अन्यथा अणु
					पंचांगp = inl(TRID_REG(trident, NX_SPCTRL_SPCSO)) & 0x00ffffff;
				पूर्ण
				अगर (पंचांगp < voice->isync_mark) अणु
					अगर (पंचांगp > 0x10)
						पंचांगp = voice->isync_ESO - 7;
					अन्यथा
						पंचांगp = voice->isync_ESO + 2;
					/* update ESO क्रम IRQ voice to preserve sync */
					snd_trident_stop_voice(trident, voice->number);
					snd_trident_ग_लिखो_eso_reg(trident, voice, पंचांगp);
					snd_trident_start_voice(trident, voice->number);
				पूर्ण
			पूर्ण अन्यथा अगर (voice->isync2) अणु
				voice->isync2 = 0;
				/* ग_लिखो original ESO and update CSO क्रम IRQ voice to preserve sync */
				snd_trident_stop_voice(trident, voice->number);
				snd_trident_ग_लिखो_cso_reg(trident, voice, voice->isync_mark);
				snd_trident_ग_लिखो_eso_reg(trident, voice, voice->ESO);
				snd_trident_start_voice(trident, voice->number);
			पूर्ण
#अगर 0
			अगर (voice->extra) अणु
				/* update CSO क्रम extra voice to preserve sync */
				snd_trident_stop_voice(trident, voice->extra->number);
				snd_trident_ग_लिखो_cso_reg(trident, voice->extra, 0);
				snd_trident_start_voice(trident, voice->extra->number);
			पूर्ण
#पूर्ण_अगर
			spin_unlock(&trident->reg_lock);
			snd_pcm_period_elapsed(voice->substream);
			spin_lock(&trident->reg_lock);
		पूर्ण
		outl(chn_पूर्णांक, TRID_REG(trident, T4D_AINT_B));	/* ack */
	      __skip2:
		spin_unlock(&trident->reg_lock);
	पूर्ण
	अगर (audio_पूर्णांक & MPU401_IRQ) अणु
		अगर (trident->rmidi) अणु
			snd_mpu401_uart_पूर्णांकerrupt(irq, trident->rmidi->निजी_data);
		पूर्ण अन्यथा अणु
			inb(TRID_REG(trident, T4D_MPUR0));
		पूर्ण
	पूर्ण
	// outl((ST_TARGET_REACHED | MIXER_OVERFLOW | MIXER_UNDERFLOW), TRID_REG(trident, T4D_MISCINT));
	वापस IRQ_HANDLED;
पूर्ण

काष्ठा snd_trident_voice *snd_trident_alloc_voice(काष्ठा snd_trident * trident, पूर्णांक type, पूर्णांक client, पूर्णांक port)
अणु
	काष्ठा snd_trident_voice *pvoice;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	spin_lock_irqsave(&trident->voice_alloc, flags);
	अगर (type == SNDRV_TRIDENT_VOICE_TYPE_PCM) अणु
		idx = snd_trident_allocate_pcm_channel(trident);
		अगर(idx < 0) अणु
			spin_unlock_irqrestore(&trident->voice_alloc, flags);
			वापस शून्य;
		पूर्ण
		pvoice = &trident->synth.voices[idx];
		pvoice->use = 1;
		pvoice->pcm = 1;
		pvoice->capture = 0;
		pvoice->spdअगर = 0;
		pvoice->memblk = शून्य;
		pvoice->substream = शून्य;
		spin_unlock_irqrestore(&trident->voice_alloc, flags);
		वापस pvoice;
	पूर्ण
	अगर (type == SNDRV_TRIDENT_VOICE_TYPE_SYNTH) अणु
		idx = snd_trident_allocate_synth_channel(trident);
		अगर(idx < 0) अणु
			spin_unlock_irqrestore(&trident->voice_alloc, flags);
			वापस शून्य;
		पूर्ण
		pvoice = &trident->synth.voices[idx];
		pvoice->use = 1;
		pvoice->synth = 1;
		pvoice->client = client;
		pvoice->port = port;
		pvoice->memblk = शून्य;
		spin_unlock_irqrestore(&trident->voice_alloc, flags);
		वापस pvoice;
	पूर्ण
	अगर (type == SNDRV_TRIDENT_VOICE_TYPE_MIDI) अणु
	पूर्ण
	spin_unlock_irqrestore(&trident->voice_alloc, flags);
	वापस शून्य;
पूर्ण

EXPORT_SYMBOL(snd_trident_alloc_voice);

व्योम snd_trident_मुक्त_voice(काष्ठा snd_trident * trident, काष्ठा snd_trident_voice *voice)
अणु
	अचिन्हित दीर्घ flags;
	व्योम (*निजी_मुक्त)(काष्ठा snd_trident_voice *);

	अगर (voice == शून्य || !voice->use)
		वापस;
	snd_trident_clear_voices(trident, voice->number, voice->number);
	spin_lock_irqsave(&trident->voice_alloc, flags);
	निजी_मुक्त = voice->निजी_मुक्त;
	voice->निजी_मुक्त = शून्य;
	voice->निजी_data = शून्य;
	अगर (voice->pcm)
		snd_trident_मुक्त_pcm_channel(trident, voice->number);
	अगर (voice->synth)
		snd_trident_मुक्त_synth_channel(trident, voice->number);
	voice->use = voice->pcm = voice->synth = voice->midi = 0;
	voice->capture = voice->spdअगर = 0;
	voice->sample_ops = शून्य;
	voice->substream = शून्य;
	voice->extra = शून्य;
	spin_unlock_irqrestore(&trident->voice_alloc, flags);
	अगर (निजी_मुक्त)
		निजी_मुक्त(voice);
पूर्ण

EXPORT_SYMBOL(snd_trident_मुक्त_voice);

अटल व्योम snd_trident_clear_voices(काष्ठा snd_trident * trident, अचिन्हित लघु v_min, अचिन्हित लघु v_max)
अणु
	अचिन्हित पूर्णांक i, val, mask[2] = अणु 0, 0 पूर्ण;

	अगर (snd_BUG_ON(v_min > 63 || v_max > 63))
		वापस;
	क्रम (i = v_min; i <= v_max; i++)
		mask[i >> 5] |= 1 << (i & 0x1f);
	अगर (mask[0]) अणु
		outl(mask[0], TRID_REG(trident, T4D_STOP_A));
		val = inl(TRID_REG(trident, T4D_AINTEN_A));
		outl(val & ~mask[0], TRID_REG(trident, T4D_AINTEN_A));
	पूर्ण
	अगर (mask[1]) अणु
		outl(mask[1], TRID_REG(trident, T4D_STOP_B));
		val = inl(TRID_REG(trident, T4D_AINTEN_B));
		outl(val & ~mask[1], TRID_REG(trident, T4D_AINTEN_B));
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_trident_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_trident *trident = card->निजी_data;

	trident->in_suspend = 1;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(trident->ac97);
	snd_ac97_suspend(trident->ac97_sec);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_trident_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_trident *trident = card->निजी_data;

	चयन (trident->device) अणु
	हाल TRIDENT_DEVICE_ID_DX:
		snd_trident_4d_dx_init(trident);
		अवरोध;
	हाल TRIDENT_DEVICE_ID_NX:
		snd_trident_4d_nx_init(trident);
		अवरोध;
	हाल TRIDENT_DEVICE_ID_SI7018:
		snd_trident_sis_init(trident);
		अवरोध;
	पूर्ण

	snd_ac97_resume(trident->ac97);
	snd_ac97_resume(trident->ac97_sec);

	/* restore some रेजिस्टरs */
	outl(trident->musicvol_wavevol, TRID_REG(trident, T4D_MUSICVOL_WAVEVOL));

	snd_trident_enable_eso(trident);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	trident->in_suspend = 0;
	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(snd_trident_pm, snd_trident_suspend, snd_trident_resume);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
