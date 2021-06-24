<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/sound/oss/dmasound/dmasound_paula.c
 *
 *  Amiga `Paula' DMA Sound Driver
 *
 *  See linux/sound/oss/dmasound/dmasound_core.c क्रम copyright and credits
 *  prior to 28/01/2001
 *
 *  28/01/2001 [0.1] Iain Sanकरोe
 *		     - added versioning
 *		     - put in and populated the hardware_afmts field.
 *             [0.2] - put in SNDCTL_DSP_GETCAPS value.
 *	       [0.3] - put in स्थिरraपूर्णांक on state buffer usage.
 *	       [0.4] - put in शेष hard/soft settings
*/


#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/soundcard.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/machdep.h>

#समावेश "dmasound.h"

#घोषणा DMASOUND_PAULA_REVISION 0
#घोषणा DMASOUND_PAULA_EDITION 4

#घोषणा custom amiga_custom
   /*
    *	The minimum period क्रम audio depends on htotal (क्रम OCS/ECS/AGA)
    *	(Imported from arch/m68k/amiga/amisound.c)
    */

बाह्य अस्थिर u_लघु amiga_audio_min_period;


   /*
    *	amiga_mksound() should be able to restore the period after beeping
    *	(Imported from arch/m68k/amiga/amisound.c)
    */

बाह्य u_लघु amiga_audio_period;


   /*
    *	Audio DMA masks
    */

#घोषणा AMI_AUDIO_OFF	(DMAF_AUD0 | DMAF_AUD1 | DMAF_AUD2 | DMAF_AUD3)
#घोषणा AMI_AUDIO_8	(DMAF_SETCLR | DMAF_MASTER | DMAF_AUD0 | DMAF_AUD1)
#घोषणा AMI_AUDIO_14	(AMI_AUDIO_8 | DMAF_AUD2 | DMAF_AUD3)


    /*
     *  Helper poपूर्णांकers क्रम 16(14)-bit sound
     */

अटल पूर्णांक ग_लिखो_sq_block_size_half, ग_लिखो_sq_block_size_quarter;


/*** Low level stuff *********************************************************/


अटल व्योम *AmiAlloc(अचिन्हित पूर्णांक size, gfp_t flags);
अटल व्योम AmiFree(व्योम *obj, अचिन्हित पूर्णांक size);
अटल पूर्णांक AmiIrqInit(व्योम);
#अगर_घोषित MODULE
अटल व्योम AmiIrqCleanUp(व्योम);
#पूर्ण_अगर
अटल व्योम AmiSilence(व्योम);
अटल व्योम AmiInit(व्योम);
अटल पूर्णांक AmiSetFormat(पूर्णांक क्रमmat);
अटल पूर्णांक AmiSetVolume(पूर्णांक volume);
अटल पूर्णांक AmiSetTreble(पूर्णांक treble);
अटल व्योम AmiPlayNextFrame(पूर्णांक index);
अटल व्योम AmiPlay(व्योम);
अटल irqवापस_t AmiInterrupt(पूर्णांक irq, व्योम *dummy);

#अगर_घोषित CONFIG_HEARTBEAT

    /*
     *  Heartbeat पूर्णांकerferes with sound since the 7 kHz low-pass filter and the
     *  घातer LED are controlled by the same line.
     */

अटल व्योम (*saved_heartbeat)(पूर्णांक) = शून्य;

अटल अंतरभूत व्योम disable_heartbeat(व्योम)
अणु
	अगर (mach_heartbeat) अणु
	    saved_heartbeat = mach_heartbeat;
	    mach_heartbeat = शून्य;
	पूर्ण
	AmiSetTreble(dmasound.treble);
पूर्ण

अटल अंतरभूत व्योम enable_heartbeat(व्योम)
अणु
	अगर (saved_heartbeat)
	    mach_heartbeat = saved_heartbeat;
पूर्ण
#अन्यथा /* !CONFIG_HEARTBEAT */
#घोषणा disable_heartbeat()	करो अणु पूर्ण जबतक (0)
#घोषणा enable_heartbeat()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* !CONFIG_HEARTBEAT */


/*** Mid level stuff *********************************************************/

अटल व्योम AmiMixerInit(व्योम);
अटल पूर्णांक AmiMixerIoctl(u_पूर्णांक cmd, u_दीर्घ arg);
अटल पूर्णांक AmiWriteSqSetup(व्योम);
अटल पूर्णांक AmiStateInfo(अक्षर *buffer, माप_प्रकार space);


/*** Translations ************************************************************/

/* ++TeSche: radically changed क्रम new expanding purposes...
 *
 * These two routines now deal with copying/expanding/translating the samples
 * from user space पूर्णांकo our buffer at the right frequency. They take care about
 * how much data there's actually to पढ़ो, how much buffer space there is and
 * to convert samples पूर्णांकo the right frequency/encoding. They will only work on
 * complete samples so it may happen they leave some bytes in the input stream
 * अगर the user didn't ग_लिखो a multiple of the current sample size. They both
 * वापस the number of bytes they've used from both streams so you may detect
 * such a situation. Luckily all programs should be able to cope with that.
 *
 * I think I've optimized anything as far as one can करो in plain C, all
 * variables should fit in रेजिस्टरs and the loops are really लघु. There's
 * one loop क्रम every possible situation. Writing a more generalized and thus
 * parameterized loop would only produce slower code. Feel मुक्त to optimize
 * this in assembler अगर you like. :)
 *
 * I think these routines beदीर्घ here because they're not yet really hardware
 * independent, especially the fact that the Falcon can play 16bit samples
 * only in stereo is hardcoded in both of them!
 *
 * ++geert: split in even more functions (one per क्रमmat)
 */


    /*
     *  Native क्रमmat
     */

अटल sमाप_प्रकार ami_ct_s8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			 u_अक्षर frame[], sमाप_प्रकार *frameUsed, sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;

	अगर (!dmasound.soft.stereo) अणु
		व्योम *p = &frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft) & ~1;
		used = count;
		अगर (copy_from_user(p, userPtr, count))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		u_अक्षर *left = &frame[*frameUsed>>1];
		u_अक्षर *right = left+ग_लिखो_sq_block_size_half;
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>1 & ~1;
		used = count*2;
		जबतक (count > 0) अणु
			अगर (get_user(*left++, userPtr++)
			    || get_user(*right++, userPtr++))
				वापस -EFAULT;
			count--;
		पूर्ण
	पूर्ण
	*frameUsed += used;
	वापस used;
पूर्ण


    /*
     *  Copy and convert 8 bit data
     */

#घोषणा GENERATE_AMI_CT8(funcname, convsample)				\
अटल sमाप_प्रकार funcname(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,	\
			u_अक्षर frame[], sमाप_प्रकार *frameUsed,		\
			sमाप_प्रकार frameLeft)				\
अणु									\
	sमाप_प्रकार count, used;						\
									\
	अगर (!dmasound.soft.stereo) अणु					\
		u_अक्षर *p = &frame[*frameUsed];				\
		count = min_t(माप_प्रकार, userCount, frameLeft) & ~1;	\
		used = count;						\
		जबतक (count > 0) अणु					\
			u_अक्षर data;					\
			अगर (get_user(data, userPtr++))			\
				वापस -EFAULT;				\
			*p++ = convsample(data);			\
			count--;					\
		पूर्ण							\
	पूर्ण अन्यथा अणु							\
		u_अक्षर *left = &frame[*frameUsed>>1];			\
		u_अक्षर *right = left+ग_लिखो_sq_block_size_half;		\
		count = min_t(माप_प्रकार, userCount, frameLeft)>>1 & ~1;	\
		used = count*2;						\
		जबतक (count > 0) अणु					\
			u_अक्षर data;					\
			अगर (get_user(data, userPtr++))			\
				वापस -EFAULT;				\
			*left++ = convsample(data);			\
			अगर (get_user(data, userPtr++))			\
				वापस -EFAULT;				\
			*right++ = convsample(data);			\
			count--;					\
		पूर्ण							\
	पूर्ण								\
	*frameUsed += used;						\
	वापस used;							\
पूर्ण

#घोषणा AMI_CT_ULAW(x)	(dmasound_ulaw2dma8[(x)])
#घोषणा AMI_CT_ALAW(x)	(dmasound_alaw2dma8[(x)])
#घोषणा AMI_CT_U8(x)	((x) ^ 0x80)

GENERATE_AMI_CT8(ami_ct_ulaw, AMI_CT_ULAW)
GENERATE_AMI_CT8(ami_ct_alaw, AMI_CT_ALAW)
GENERATE_AMI_CT8(ami_ct_u8, AMI_CT_U8)


    /*
     *  Copy and convert 16 bit data
     */

#घोषणा GENERATE_AMI_CT_16(funcname, convsample)			\
अटल sमाप_प्रकार funcname(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,	\
			u_अक्षर frame[], sमाप_प्रकार *frameUsed,		\
			sमाप_प्रकार frameLeft)				\
अणु									\
	स्थिर u_लघु __user *ptr = (स्थिर u_लघु __user *)userPtr;	\
	sमाप_प्रकार count, used;						\
	u_लघु data;							\
									\
	अगर (!dmasound.soft.stereo) अणु					\
		u_अक्षर *high = &frame[*frameUsed>>1];			\
		u_अक्षर *low = high+ग_लिखो_sq_block_size_half;		\
		count = min_t(माप_प्रकार, userCount, frameLeft)>>1 & ~1;	\
		used = count*2;						\
		जबतक (count > 0) अणु					\
			अगर (get_user(data, ptr++))			\
				वापस -EFAULT;				\
			data = convsample(data);			\
			*high++ = data>>8;				\
			*low++ = (data>>2) & 0x3f;			\
			count--;					\
		पूर्ण							\
	पूर्ण अन्यथा अणु							\
		u_अक्षर *lefth = &frame[*frameUsed>>2];			\
		u_अक्षर *leftl = lefth+ग_लिखो_sq_block_size_quarter;	\
		u_अक्षर *righth = lefth+ग_लिखो_sq_block_size_half;	\
		u_अक्षर *rightl = righth+ग_लिखो_sq_block_size_quarter;	\
		count = min_t(माप_प्रकार, userCount, frameLeft)>>2 & ~1;	\
		used = count*4;						\
		जबतक (count > 0) अणु					\
			अगर (get_user(data, ptr++))			\
				वापस -EFAULT;				\
			data = convsample(data);			\
			*lefth++ = data>>8;				\
			*leftl++ = (data>>2) & 0x3f;			\
			अगर (get_user(data, ptr++))			\
				वापस -EFAULT;				\
			data = convsample(data);			\
			*righth++ = data>>8;				\
			*rightl++ = (data>>2) & 0x3f;			\
			count--;					\
		पूर्ण							\
	पूर्ण								\
	*frameUsed += used;						\
	वापस used;							\
पूर्ण

#घोषणा AMI_CT_S16BE(x)	(x)
#घोषणा AMI_CT_U16BE(x)	((x) ^ 0x8000)
#घोषणा AMI_CT_S16LE(x)	(le2be16((x)))
#घोषणा AMI_CT_U16LE(x)	(le2be16((x)) ^ 0x8000)

GENERATE_AMI_CT_16(ami_ct_s16be, AMI_CT_S16BE)
GENERATE_AMI_CT_16(ami_ct_u16be, AMI_CT_U16BE)
GENERATE_AMI_CT_16(ami_ct_s16le, AMI_CT_S16LE)
GENERATE_AMI_CT_16(ami_ct_u16le, AMI_CT_U16LE)


अटल TRANS transAmiga = अणु
	.ct_ulaw	= ami_ct_ulaw,
	.ct_alaw	= ami_ct_alaw,
	.ct_s8		= ami_ct_s8,
	.ct_u8		= ami_ct_u8,
	.ct_s16be	= ami_ct_s16be,
	.ct_u16be	= ami_ct_u16be,
	.ct_s16le	= ami_ct_s16le,
	.ct_u16le	= ami_ct_u16le,
पूर्ण;

/*** Low level stuff *********************************************************/

अटल अंतरभूत व्योम StopDMA(व्योम)
अणु
	custom.aud[0].audvol = custom.aud[1].audvol = 0;
	custom.aud[2].audvol = custom.aud[3].audvol = 0;
	custom.dmacon = AMI_AUDIO_OFF;
	enable_heartbeat();
पूर्ण

अटल व्योम *AmiAlloc(अचिन्हित पूर्णांक size, gfp_t flags)
अणु
	वापस amiga_chip_alloc((दीर्घ)size, "dmasound [Paula]");
पूर्ण

अटल व्योम AmiFree(व्योम *obj, अचिन्हित पूर्णांक size)
अणु
	amiga_chip_मुक्त (obj);
पूर्ण

अटल पूर्णांक __init AmiIrqInit(व्योम)
अणु
	/* turn off DMA क्रम audio channels */
	StopDMA();

	/* Register पूर्णांकerrupt handler. */
	अगर (request_irq(IRQ_AMIGA_AUD0, AmiInterrupt, 0, "DMA sound",
			AmiInterrupt))
		वापस 0;
	वापस 1;
पूर्ण

#अगर_घोषित MODULE
अटल व्योम AmiIrqCleanUp(व्योम)
अणु
	/* turn off DMA क्रम audio channels */
	StopDMA();
	/* release the पूर्णांकerrupt */
	मुक्त_irq(IRQ_AMIGA_AUD0, AmiInterrupt);
पूर्ण
#पूर्ण_अगर /* MODULE */

अटल व्योम AmiSilence(व्योम)
अणु
	/* turn off DMA क्रम audio channels */
	StopDMA();
पूर्ण


अटल व्योम AmiInit(व्योम)
अणु
	पूर्णांक period, i;

	AmiSilence();

	अगर (dmasound.soft.speed)
		period = amiga_colorघड़ी/dmasound.soft.speed-1;
	अन्यथा
		period = amiga_audio_min_period;
	dmasound.hard = dmasound.soft;
	dmasound.trans_ग_लिखो = &transAmiga;

	अगर (period < amiga_audio_min_period) अणु
		/* we would need to squeeze the sound, but we won't करो that */
		period = amiga_audio_min_period;
	पूर्ण अन्यथा अगर (period > 65535) अणु
		period = 65535;
	पूर्ण
	dmasound.hard.speed = amiga_colorघड़ी/(period+1);

	क्रम (i = 0; i < 4; i++)
		custom.aud[i].audper = period;
	amiga_audio_period = period;
पूर्ण


अटल पूर्णांक AmiSetFormat(पूर्णांक क्रमmat)
अणु
	पूर्णांक size;

	/* Amiga sound DMA supports 8bit and 16bit (pseuकरो 14 bit) modes */

	चयन (क्रमmat) अणु
	हाल AFMT_QUERY:
		वापस dmasound.soft.क्रमmat;
	हाल AFMT_MU_LAW:
	हाल AFMT_A_LAW:
	हाल AFMT_U8:
	हाल AFMT_S8:
		size = 8;
		अवरोध;
	हाल AFMT_S16_BE:
	हाल AFMT_U16_BE:
	हाल AFMT_S16_LE:
	हाल AFMT_U16_LE:
		size = 16;
		अवरोध;
	शेष: /* :-) */
		size = 8;
		क्रमmat = AFMT_S8;
	पूर्ण

	dmasound.soft.क्रमmat = क्रमmat;
	dmasound.soft.size = size;
	अगर (dmasound.minDev == SND_DEV_DSP) अणु
		dmasound.dsp.क्रमmat = क्रमmat;
		dmasound.dsp.size = dmasound.soft.size;
	पूर्ण
	AmiInit();

	वापस क्रमmat;
पूर्ण


#घोषणा VOLUME_VOXWARE_TO_AMI(v) \
	(((v) < 0) ? 0 : ((v) > 100) ? 64 : ((v) * 64)/100)
#घोषणा VOLUME_AMI_TO_VOXWARE(v) ((v)*100/64)

अटल पूर्णांक AmiSetVolume(पूर्णांक volume)
अणु
	dmasound.volume_left = VOLUME_VOXWARE_TO_AMI(volume & 0xff);
	custom.aud[0].audvol = dmasound.volume_left;
	dmasound.volume_right = VOLUME_VOXWARE_TO_AMI((volume & 0xff00) >> 8);
	custom.aud[1].audvol = dmasound.volume_right;
	अगर (dmasound.hard.size == 16) अणु
		अगर (dmasound.volume_left == 64 && dmasound.volume_right == 64) अणु
			custom.aud[2].audvol = 1;
			custom.aud[3].audvol = 1;
		पूर्ण अन्यथा अणु
			custom.aud[2].audvol = 0;
			custom.aud[3].audvol = 0;
		पूर्ण
	पूर्ण
	वापस VOLUME_AMI_TO_VOXWARE(dmasound.volume_left) |
	       (VOLUME_AMI_TO_VOXWARE(dmasound.volume_right) << 8);
पूर्ण

अटल पूर्णांक AmiSetTreble(पूर्णांक treble)
अणु
	dmasound.treble = treble;
	अगर (treble < 50)
		ciaa.pra &= ~0x02;
	अन्यथा
		ciaa.pra |= 0x02;
	वापस treble;
पूर्ण


#घोषणा AMI_PLAY_LOADED		1
#घोषणा AMI_PLAY_PLAYING	2
#घोषणा AMI_PLAY_MASK		3


अटल व्योम AmiPlayNextFrame(पूर्णांक index)
अणु
	u_अक्षर *start, *ch0, *ch1, *ch2, *ch3;
	u_दीर्घ size;

	/* used by AmiPlay() अगर all करोubts whether there really is something
	 * to be played are alपढ़ोy wiped out.
	 */
	start = ग_लिखो_sq.buffers[ग_लिखो_sq.front];
	size = (ग_लिखो_sq.count == index ? ग_लिखो_sq.rear_size
					: ग_लिखो_sq.block_size)>>1;

	अगर (dmasound.hard.stereo) अणु
		ch0 = start;
		ch1 = start+ग_लिखो_sq_block_size_half;
		size >>= 1;
	पूर्ण अन्यथा अणु
		ch0 = start;
		ch1 = start;
	पूर्ण

	disable_heartbeat();
	custom.aud[0].audvol = dmasound.volume_left;
	custom.aud[1].audvol = dmasound.volume_right;
	अगर (dmasound.hard.size == 8) अणु
		custom.aud[0].audlc = (u_लघु *)ZTWO_PADDR(ch0);
		custom.aud[0].audlen = size;
		custom.aud[1].audlc = (u_लघु *)ZTWO_PADDR(ch1);
		custom.aud[1].audlen = size;
		custom.dmacon = AMI_AUDIO_8;
	पूर्ण अन्यथा अणु
		size >>= 1;
		custom.aud[0].audlc = (u_लघु *)ZTWO_PADDR(ch0);
		custom.aud[0].audlen = size;
		custom.aud[1].audlc = (u_लघु *)ZTWO_PADDR(ch1);
		custom.aud[1].audlen = size;
		अगर (dmasound.volume_left == 64 && dmasound.volume_right == 64) अणु
			/* We can play pseuकरो 14-bit only with the maximum volume */
			ch3 = ch0+ग_लिखो_sq_block_size_quarter;
			ch2 = ch1+ग_लिखो_sq_block_size_quarter;
			custom.aud[2].audvol = 1;  /* we are being affected by the beeps */
			custom.aud[3].audvol = 1;  /* restoring volume here helps a bit */
			custom.aud[2].audlc = (u_लघु *)ZTWO_PADDR(ch2);
			custom.aud[2].audlen = size;
			custom.aud[3].audlc = (u_लघु *)ZTWO_PADDR(ch3);
			custom.aud[3].audlen = size;
			custom.dmacon = AMI_AUDIO_14;
		पूर्ण अन्यथा अणु
			custom.aud[2].audvol = 0;
			custom.aud[3].audvol = 0;
			custom.dmacon = AMI_AUDIO_8;
		पूर्ण
	पूर्ण
	ग_लिखो_sq.front = (ग_लिखो_sq.front+1) % ग_लिखो_sq.max_count;
	ग_लिखो_sq.active |= AMI_PLAY_LOADED;
पूर्ण


अटल व्योम AmiPlay(व्योम)
अणु
	पूर्णांक minframes = 1;

	custom.पूर्णांकena = IF_AUD0;

	अगर (ग_लिखो_sq.active & AMI_PLAY_LOADED) अणु
		/* There's alपढ़ोy a frame loaded */
		custom.पूर्णांकena = IF_SETCLR | IF_AUD0;
		वापस;
	पूर्ण

	अगर (ग_लिखो_sq.active & AMI_PLAY_PLAYING)
		/* Increase threshold: frame 1 is alपढ़ोy being played */
		minframes = 2;

	अगर (ग_लिखो_sq.count < minframes) अणु
		/* Nothing to करो */
		custom.पूर्णांकena = IF_SETCLR | IF_AUD0;
		वापस;
	पूर्ण

	अगर (ग_लिखो_sq.count <= minframes &&
	    ग_लिखो_sq.rear_size < ग_लिखो_sq.block_size && !ग_लिखो_sq.syncing) अणु
		/* hmmm, the only existing frame is not
		 * yet filled and we're not syncing?
		 */
		custom.पूर्णांकena = IF_SETCLR | IF_AUD0;
		वापस;
	पूर्ण

	AmiPlayNextFrame(minframes);

	custom.पूर्णांकena = IF_SETCLR | IF_AUD0;
पूर्ण


अटल irqवापस_t AmiInterrupt(पूर्णांक irq, व्योम *dummy)
अणु
	पूर्णांक minframes = 1;

	custom.पूर्णांकena = IF_AUD0;

	अगर (!ग_लिखो_sq.active) अणु
		/* Playing was पूर्णांकerrupted and sq_reset() has alपढ़ोy cleared
		 * the sq variables, so better करोn't करो anything here.
		 */
		WAKE_UP(ग_लिखो_sq.sync_queue);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (ग_लिखो_sq.active & AMI_PLAY_PLAYING) अणु
		/* We've just finished a frame */
		ग_लिखो_sq.count--;
		WAKE_UP(ग_लिखो_sq.action_queue);
	पूर्ण

	अगर (ग_लिखो_sq.active & AMI_PLAY_LOADED)
		/* Increase threshold: frame 1 is alपढ़ोy being played */
		minframes = 2;

	/* Shअगरt the flags */
	ग_लिखो_sq.active = (ग_लिखो_sq.active<<1) & AMI_PLAY_MASK;

	अगर (!ग_लिखो_sq.active)
		/* No frame is playing, disable audio DMA */
		StopDMA();

	custom.पूर्णांकena = IF_SETCLR | IF_AUD0;

	अगर (ग_लिखो_sq.count >= minframes)
		/* Try to play the next frame */
		AmiPlay();

	अगर (!ग_लिखो_sq.active)
		/* Nothing to play anymore.
		   Wake up a process रुकोing क्रम audio output to drain. */
		WAKE_UP(ग_लिखो_sq.sync_queue);
	वापस IRQ_HANDLED;
पूर्ण

/*** Mid level stuff *********************************************************/


/*
 * /dev/mixer असलtraction
 */

अटल व्योम __init AmiMixerInit(व्योम)
अणु
	dmasound.volume_left = 64;
	dmasound.volume_right = 64;
	custom.aud[0].audvol = dmasound.volume_left;
	custom.aud[3].audvol = 1;	/* For pseuकरो 14bit */
	custom.aud[1].audvol = dmasound.volume_right;
	custom.aud[2].audvol = 1;	/* For pseuकरो 14bit */
	dmasound.treble = 50;
पूर्ण

अटल पूर्णांक AmiMixerIoctl(u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक data;
	चयन (cmd) अणु
	    हाल SOUND_MIXER_READ_DEVMASK:
		    वापस IOCTL_OUT(arg, SOUND_MASK_VOLUME | SOUND_MASK_TREBLE);
	    हाल SOUND_MIXER_READ_RECMASK:
		    वापस IOCTL_OUT(arg, 0);
	    हाल SOUND_MIXER_READ_STEREODEVS:
		    वापस IOCTL_OUT(arg, SOUND_MASK_VOLUME);
	    हाल SOUND_MIXER_READ_VOLUME:
		    वापस IOCTL_OUT(arg,
			    VOLUME_AMI_TO_VOXWARE(dmasound.volume_left) |
			    VOLUME_AMI_TO_VOXWARE(dmasound.volume_right) << 8);
	    हाल SOUND_MIXER_WRITE_VOLUME:
		    IOCTL_IN(arg, data);
		    वापस IOCTL_OUT(arg, dmasound_set_volume(data));
	    हाल SOUND_MIXER_READ_TREBLE:
		    वापस IOCTL_OUT(arg, dmasound.treble);
	    हाल SOUND_MIXER_WRITE_TREBLE:
		    IOCTL_IN(arg, data);
		    वापस IOCTL_OUT(arg, dmasound_set_treble(data));
	पूर्ण
	वापस -EINVAL;
पूर्ण


अटल पूर्णांक AmiWriteSqSetup(व्योम)
अणु
	ग_लिखो_sq_block_size_half = ग_लिखो_sq.block_size>>1;
	ग_लिखो_sq_block_size_quarter = ग_लिखो_sq_block_size_half>>1;
	वापस 0;
पूर्ण


अटल पूर्णांक AmiStateInfo(अक्षर *buffer, माप_प्रकार space)
अणु
	पूर्णांक len = 0;
	len += प्र_लिखो(buffer+len, "\tsound.volume_left = %d [0...64]\n",
		       dmasound.volume_left);
	len += प्र_लिखो(buffer+len, "\tsound.volume_right = %d [0...64]\n",
		       dmasound.volume_right);
	अगर (len >= space) अणु
		prपूर्णांकk(KERN_ERR "dmasound_paula: overflowed state buffer alloc.\n") ;
		len = space ;
	पूर्ण
	वापस len;
पूर्ण


/*** Machine definitions *****************************************************/

अटल SETTINGS def_hard = अणु
	.क्रमmat	= AFMT_S8,
	.stereo	= 0,
	.size	= 8,
	.speed	= 8000
पूर्ण ;

अटल SETTINGS def_soft = अणु
	.क्रमmat	= AFMT_U8,
	.stereo	= 0,
	.size	= 8,
	.speed	= 8000
पूर्ण ;

अटल MACHINE machAmiga = अणु
	.name		= "Amiga",
	.name2		= "AMIGA",
	.owner		= THIS_MODULE,
	.dma_alloc	= AmiAlloc,
	.dma_मुक्त	= AmiFree,
	.irqinit	= AmiIrqInit,
#अगर_घोषित MODULE
	.irqcleanup	= AmiIrqCleanUp,
#पूर्ण_अगर /* MODULE */
	.init		= AmiInit,
	.silence	= AmiSilence,
	.setFormat	= AmiSetFormat,
	.setVolume	= AmiSetVolume,
	.setTreble	= AmiSetTreble,
	.play		= AmiPlay,
	.mixer_init	= AmiMixerInit,
	.mixer_ioctl	= AmiMixerIoctl,
	.ग_लिखो_sq_setup	= AmiWriteSqSetup,
	.state_info	= AmiStateInfo,
	.min_dsp_speed	= 8000,
	.version	= ((DMASOUND_PAULA_REVISION<<8) | DMASOUND_PAULA_EDITION),
	.hardware_afmts	= (AFMT_S8 | AFMT_S16_BE), /* h'ware-supported क्रमmats *only* here */
	.capabilities	= DSP_CAP_BATCH          /* As per SNDCTL_DSP_GETCAPS */
पूर्ण;


/*** Config & Setup **********************************************************/


अटल पूर्णांक __init amiga_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	dmasound.mach = machAmiga;
	dmasound.mach.शेष_hard = def_hard ;
	dmasound.mach.शेष_soft = def_soft ;
	वापस dmasound_init();
पूर्ण

अटल पूर्णांक __निकास amiga_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dmasound_deinit();
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amiga_audio_driver = अणु
	.हटाओ = __निकास_p(amiga_audio_हटाओ),
	.driver   = अणु
		.name	= "amiga-audio",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amiga_audio_driver, amiga_audio_probe);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:amiga-audio");
