<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/sound/oss/dmasound/dmasound_atari.c
 *
 *  Atari TT and Falcon DMA Sound Driver
 *
 *  See linux/sound/oss/dmasound/dmasound_core.c क्रम copyright and credits
 *  prior to 28/01/2001
 *
 *  28/01/2001 [0.1] Iain Sanकरोe
 *		     - added versioning
 *		     - put in and populated the hardware_afmts field.
 *             [0.2] - put in SNDCTL_DSP_GETCAPS value.
 *  01/02/2001 [0.3] - put in शेष hard/soft settings.
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/soundcard.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atari_stram.h>

#समावेश "dmasound.h"

#घोषणा DMASOUND_ATARI_REVISION 0
#घोषणा DMASOUND_ATARI_EDITION 3

बाह्य व्योम atari_microwire_cmd(पूर्णांक cmd);

अटल पूर्णांक is_falcon;
अटल पूर्णांक ग_लिखो_sq_ignore_पूर्णांक;	/* ++TeSche: used क्रम Falcon */

अटल पूर्णांक expand_bal;	/* Balance factor क्रम expanding (not volume!) */
अटल पूर्णांक expand_data;	/* Data क्रम expanding */


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

अटल sमाप_प्रकार ata_ct_law(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			  u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			  sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ct_s8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			 u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			 sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ct_u8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			 u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			 sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ct_s16be(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ct_u16be(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ct_s16le(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ct_u16le(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ctx_law(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			   u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			   sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ctx_s8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			  u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			  sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ctx_u8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			  u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			  sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ctx_s16be(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			     u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			     sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ctx_u16be(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			     u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			     sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ctx_s16le(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			     u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			     sमाप_प्रकार frameLeft);
अटल sमाप_प्रकार ata_ctx_u16le(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			     u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			     sमाप_प्रकार frameLeft);


/*** Low level stuff *********************************************************/


अटल व्योम *AtaAlloc(अचिन्हित पूर्णांक size, gfp_t flags);
अटल व्योम AtaFree(व्योम *, अचिन्हित पूर्णांक size);
अटल पूर्णांक AtaIrqInit(व्योम);
#अगर_घोषित MODULE
अटल व्योम AtaIrqCleanUp(व्योम);
#पूर्ण_अगर /* MODULE */
अटल पूर्णांक AtaSetBass(पूर्णांक bass);
अटल पूर्णांक AtaSetTreble(पूर्णांक treble);
अटल व्योम TTSilence(व्योम);
अटल व्योम TTInit(व्योम);
अटल पूर्णांक TTSetFormat(पूर्णांक क्रमmat);
अटल पूर्णांक TTSetVolume(पूर्णांक volume);
अटल पूर्णांक TTSetGain(पूर्णांक gain);
अटल व्योम FalconSilence(व्योम);
अटल व्योम FalconInit(व्योम);
अटल पूर्णांक FalconSetFormat(पूर्णांक क्रमmat);
अटल पूर्णांक FalconSetVolume(पूर्णांक volume);
अटल व्योम AtaPlayNextFrame(पूर्णांक index);
अटल व्योम AtaPlay(व्योम);
अटल irqवापस_t AtaInterrupt(पूर्णांक irq, व्योम *dummy);

/*** Mid level stuff *********************************************************/

अटल व्योम TTMixerInit(व्योम);
अटल व्योम FalconMixerInit(व्योम);
अटल पूर्णांक AtaMixerIoctl(u_पूर्णांक cmd, u_दीर्घ arg);
अटल पूर्णांक TTMixerIoctl(u_पूर्णांक cmd, u_दीर्घ arg);
अटल पूर्णांक FalconMixerIoctl(u_पूर्णांक cmd, u_दीर्घ arg);
अटल पूर्णांक AtaWriteSqSetup(व्योम);
अटल पूर्णांक AtaSqOpen(भ_शेषe_t mode);
अटल पूर्णांक TTStateInfo(अक्षर *buffer, माप_प्रकार space);
अटल पूर्णांक FalconStateInfo(अक्षर *buffer, माप_प्रकार space);


/*** Translations ************************************************************/


अटल sमाप_प्रकार ata_ct_law(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			  u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			  sमाप_प्रकार frameLeft)
अणु
	अक्षर *table = dmasound.soft.क्रमmat == AFMT_MU_LAW ? dmasound_ulaw2dma8
							  : dmasound_alaw2dma8;
	sमाप_प्रकार count, used;
	u_अक्षर *p = &frame[*frameUsed];

	count = min_t(अचिन्हित दीर्घ, userCount, frameLeft);
	अगर (dmasound.soft.stereo)
		count &= ~1;
	used = count;
	जबतक (count > 0) अणु
		u_अक्षर data;
		अगर (get_user(data, userPtr++))
			वापस -EFAULT;
		*p++ = table[data];
		count--;
	पूर्ण
	*frameUsed += used;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ct_s8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			 u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			 sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;
	व्योम *p = &frame[*frameUsed];

	count = min_t(अचिन्हित दीर्घ, userCount, frameLeft);
	अगर (dmasound.soft.stereo)
		count &= ~1;
	used = count;
	अगर (copy_from_user(p, userPtr, count))
		वापस -EFAULT;
	*frameUsed += used;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ct_u8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			 u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			 sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;

	अगर (!dmasound.soft.stereo) अणु
		u_अक्षर *p = &frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft);
		used = count;
		जबतक (count > 0) अणु
			u_अक्षर data;
			अगर (get_user(data, userPtr++))
				वापस -EFAULT;
			*p++ = data ^ 0x80;
			count--;
		पूर्ण
	पूर्ण अन्यथा अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>1;
		used = count*2;
		जबतक (count > 0) अणु
			u_लघु data;
			अगर (get_user(data, (u_लघु __user *)userPtr))
				वापस -EFAULT;
			userPtr += 2;
			*p++ = data ^ 0x8080;
			count--;
		पूर्ण
	पूर्ण
	*frameUsed += used;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ct_s16be(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;

	अगर (!dmasound.soft.stereo) अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>1;
		used = count*2;
		जबतक (count > 0) अणु
			u_लघु data;
			अगर (get_user(data, (u_लघु __user *)userPtr))
				वापस -EFAULT;
			userPtr += 2;
			*p++ = data;
			*p++ = data;
			count--;
		पूर्ण
		*frameUsed += used*2;
	पूर्ण अन्यथा अणु
		व्योम *p = (u_लघु *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft) & ~3;
		used = count;
		अगर (copy_from_user(p, userPtr, count))
			वापस -EFAULT;
		*frameUsed += used;
	पूर्ण
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ct_u16be(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;

	अगर (!dmasound.soft.stereo) अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>1;
		used = count*2;
		जबतक (count > 0) अणु
			u_लघु data;
			अगर (get_user(data, (u_लघु __user *)userPtr))
				वापस -EFAULT;
			userPtr += 2;
			data ^= 0x8000;
			*p++ = data;
			*p++ = data;
			count--;
		पूर्ण
		*frameUsed += used*2;
	पूर्ण अन्यथा अणु
		u_दीर्घ *p = (u_दीर्घ *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>2;
		used = count*4;
		जबतक (count > 0) अणु
			u_पूर्णांक data;
			अगर (get_user(data, (u_पूर्णांक __user *)userPtr))
				वापस -EFAULT;
			userPtr += 4;
			*p++ = data ^ 0x80008000;
			count--;
		पूर्ण
		*frameUsed += used;
	पूर्ण
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ct_s16le(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;

	count = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>1;
		used = count*2;
		जबतक (count > 0) अणु
			u_लघु data;
			अगर (get_user(data, (u_लघु __user *)userPtr))
				वापस -EFAULT;
			userPtr += 2;
			data = le2be16(data);
			*p++ = data;
			*p++ = data;
			count--;
		पूर्ण
		*frameUsed += used*2;
	पूर्ण अन्यथा अणु
		u_दीर्घ *p = (u_दीर्घ *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>2;
		used = count*4;
		जबतक (count > 0) अणु
			u_दीर्घ data;
			अगर (get_user(data, (u_पूर्णांक __user *)userPtr))
				वापस -EFAULT;
			userPtr += 4;
			data = le2be16dbl(data);
			*p++ = data;
			count--;
		पूर्ण
		*frameUsed += used;
	पूर्ण
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ct_u16le(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;

	count = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>1;
		used = count*2;
		जबतक (count > 0) अणु
			u_लघु data;
			अगर (get_user(data, (u_लघु __user *)userPtr))
				वापस -EFAULT;
			userPtr += 2;
			data = le2be16(data) ^ 0x8000;
			*p++ = data;
			*p++ = data;
		पूर्ण
		*frameUsed += used*2;
	पूर्ण अन्यथा अणु
		u_दीर्घ *p = (u_दीर्घ *)&frame[*frameUsed];
		count = min_t(अचिन्हित दीर्घ, userCount, frameLeft)>>2;
		used = count;
		जबतक (count > 0) अणु
			u_दीर्घ data;
			अगर (get_user(data, (u_पूर्णांक __user *)userPtr))
				वापस -EFAULT;
			userPtr += 4;
			data = le2be16dbl(data) ^ 0x80008000;
			*p++ = data;
			count--;
		पूर्ण
		*frameUsed += used;
	पूर्ण
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ctx_law(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			   u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			   sमाप_प्रकार frameLeft)
अणु
	अक्षर *table = dmasound.soft.क्रमmat == AFMT_MU_LAW ? dmasound_ulaw2dma8
							  : dmasound_alaw2dma8;
	/* this should help gcc to stuff everything पूर्णांकo रेजिस्टरs */
	दीर्घ bal = expand_bal;
	दीर्घ hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	sमाप_प्रकार used, usedf;

	used = userCount;
	usedf = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_अक्षर *p = &frame[*frameUsed];
		u_अक्षर data = expand_data;
		जबतक (frameLeft) अणु
			u_अक्षर c;
			अगर (bal < 0) अणु
				अगर (!userCount)
					अवरोध;
				अगर (get_user(c, userPtr++))
					वापस -EFAULT;
				data = table[c];
				userCount--;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft--;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण अन्यथा अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		u_लघु data = expand_data;
		जबतक (frameLeft >= 2) अणु
			u_अक्षर c;
			अगर (bal < 0) अणु
				अगर (userCount < 2)
					अवरोध;
				अगर (get_user(c, userPtr++))
					वापस -EFAULT;
				data = table[c] << 8;
				अगर (get_user(c, userPtr++))
					वापस -EFAULT;
				data |= table[c];
				userCount -= 2;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft -= 2;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण
	expand_bal = bal;
	used -= userCount;
	*frameUsed += usedf-frameLeft;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ctx_s8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			  u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			  sमाप_प्रकार frameLeft)
अणु
	/* this should help gcc to stuff everything पूर्णांकo रेजिस्टरs */
	दीर्घ bal = expand_bal;
	दीर्घ hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	sमाप_प्रकार used, usedf;

	used = userCount;
	usedf = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_अक्षर *p = &frame[*frameUsed];
		u_अक्षर data = expand_data;
		जबतक (frameLeft) अणु
			अगर (bal < 0) अणु
				अगर (!userCount)
					अवरोध;
				अगर (get_user(data, userPtr++))
					वापस -EFAULT;
				userCount--;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft--;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण अन्यथा अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		u_लघु data = expand_data;
		जबतक (frameLeft >= 2) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 2)
					अवरोध;
				अगर (get_user(data, (u_लघु __user *)userPtr))
					वापस -EFAULT;
				userPtr += 2;
				userCount -= 2;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft -= 2;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण
	expand_bal = bal;
	used -= userCount;
	*frameUsed += usedf-frameLeft;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ctx_u8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			  u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			  sमाप_प्रकार frameLeft)
अणु
	/* this should help gcc to stuff everything पूर्णांकo रेजिस्टरs */
	दीर्घ bal = expand_bal;
	दीर्घ hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	sमाप_प्रकार used, usedf;

	used = userCount;
	usedf = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_अक्षर *p = &frame[*frameUsed];
		u_अक्षर data = expand_data;
		जबतक (frameLeft) अणु
			अगर (bal < 0) अणु
				अगर (!userCount)
					अवरोध;
				अगर (get_user(data, userPtr++))
					वापस -EFAULT;
				data ^= 0x80;
				userCount--;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft--;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण अन्यथा अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		u_लघु data = expand_data;
		जबतक (frameLeft >= 2) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 2)
					अवरोध;
				अगर (get_user(data, (u_लघु __user *)userPtr))
					वापस -EFAULT;
				userPtr += 2;
				data ^= 0x8080;
				userCount -= 2;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft -= 2;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण
	expand_bal = bal;
	used -= userCount;
	*frameUsed += usedf-frameLeft;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ctx_s16be(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			     u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			     sमाप_प्रकार frameLeft)
अणु
	/* this should help gcc to stuff everything पूर्णांकo रेजिस्टरs */
	दीर्घ bal = expand_bal;
	दीर्घ hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	sमाप_प्रकार used, usedf;

	used = userCount;
	usedf = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		u_लघु data = expand_data;
		जबतक (frameLeft >= 4) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 2)
					अवरोध;
				अगर (get_user(data, (u_लघु __user *)userPtr))
					वापस -EFAULT;
				userPtr += 2;
				userCount -= 2;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			*p++ = data;
			frameLeft -= 4;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण अन्यथा अणु
		u_दीर्घ *p = (u_दीर्घ *)&frame[*frameUsed];
		u_दीर्घ data = expand_data;
		जबतक (frameLeft >= 4) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 4)
					अवरोध;
				अगर (get_user(data, (u_पूर्णांक __user *)userPtr))
					वापस -EFAULT;
				userPtr += 4;
				userCount -= 4;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft -= 4;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण
	expand_bal = bal;
	used -= userCount;
	*frameUsed += usedf-frameLeft;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ctx_u16be(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			     u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			     sमाप_प्रकार frameLeft)
अणु
	/* this should help gcc to stuff everything पूर्णांकo रेजिस्टरs */
	दीर्घ bal = expand_bal;
	दीर्घ hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	sमाप_प्रकार used, usedf;

	used = userCount;
	usedf = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		u_लघु data = expand_data;
		जबतक (frameLeft >= 4) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 2)
					अवरोध;
				अगर (get_user(data, (u_लघु __user *)userPtr))
					वापस -EFAULT;
				userPtr += 2;
				data ^= 0x8000;
				userCount -= 2;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			*p++ = data;
			frameLeft -= 4;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण अन्यथा अणु
		u_दीर्घ *p = (u_दीर्घ *)&frame[*frameUsed];
		u_दीर्घ data = expand_data;
		जबतक (frameLeft >= 4) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 4)
					अवरोध;
				अगर (get_user(data, (u_पूर्णांक __user *)userPtr))
					वापस -EFAULT;
				userPtr += 4;
				data ^= 0x80008000;
				userCount -= 4;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft -= 4;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण
	expand_bal = bal;
	used -= userCount;
	*frameUsed += usedf-frameLeft;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ctx_s16le(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			     u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			     sमाप_प्रकार frameLeft)
अणु
	/* this should help gcc to stuff everything पूर्णांकo रेजिस्टरs */
	दीर्घ bal = expand_bal;
	दीर्घ hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	sमाप_प्रकार used, usedf;

	used = userCount;
	usedf = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		u_लघु data = expand_data;
		जबतक (frameLeft >= 4) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 2)
					अवरोध;
				अगर (get_user(data, (u_लघु __user *)userPtr))
					वापस -EFAULT;
				userPtr += 2;
				data = le2be16(data);
				userCount -= 2;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			*p++ = data;
			frameLeft -= 4;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण अन्यथा अणु
		u_दीर्घ *p = (u_दीर्घ *)&frame[*frameUsed];
		u_दीर्घ data = expand_data;
		जबतक (frameLeft >= 4) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 4)
					अवरोध;
				अगर (get_user(data, (u_पूर्णांक __user *)userPtr))
					वापस -EFAULT;
				userPtr += 4;
				data = le2be16dbl(data);
				userCount -= 4;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft -= 4;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण
	expand_bal = bal;
	used -= userCount;
	*frameUsed += usedf-frameLeft;
	वापस used;
पूर्ण


अटल sमाप_प्रकार ata_ctx_u16le(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			     u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			     sमाप_प्रकार frameLeft)
अणु
	/* this should help gcc to stuff everything पूर्णांकo रेजिस्टरs */
	दीर्घ bal = expand_bal;
	दीर्घ hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	sमाप_प्रकार used, usedf;

	used = userCount;
	usedf = frameLeft;
	अगर (!dmasound.soft.stereo) अणु
		u_लघु *p = (u_लघु *)&frame[*frameUsed];
		u_लघु data = expand_data;
		जबतक (frameLeft >= 4) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 2)
					अवरोध;
				अगर (get_user(data, (u_लघु __user *)userPtr))
					वापस -EFAULT;
				userPtr += 2;
				data = le2be16(data) ^ 0x8000;
				userCount -= 2;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			*p++ = data;
			frameLeft -= 4;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण अन्यथा अणु
		u_दीर्घ *p = (u_दीर्घ *)&frame[*frameUsed];
		u_दीर्घ data = expand_data;
		जबतक (frameLeft >= 4) अणु
			अगर (bal < 0) अणु
				अगर (userCount < 4)
					अवरोध;
				अगर (get_user(data, (u_पूर्णांक __user *)userPtr))
					वापस -EFAULT;
				userPtr += 4;
				data = le2be16dbl(data) ^ 0x80008000;
				userCount -= 4;
				bal += hSpeed;
			पूर्ण
			*p++ = data;
			frameLeft -= 4;
			bal -= sSpeed;
		पूर्ण
		expand_data = data;
	पूर्ण
	expand_bal = bal;
	used -= userCount;
	*frameUsed += usedf-frameLeft;
	वापस used;
पूर्ण


अटल TRANS transTTNormal = अणु
	.ct_ulaw	= ata_ct_law,
	.ct_alaw	= ata_ct_law,
	.ct_s8		= ata_ct_s8,
	.ct_u8		= ata_ct_u8,
पूर्ण;

अटल TRANS transTTExpanding = अणु
	.ct_ulaw	= ata_ctx_law,
	.ct_alaw	= ata_ctx_law,
	.ct_s8		= ata_ctx_s8,
	.ct_u8		= ata_ctx_u8,
पूर्ण;

अटल TRANS transFalconNormal = अणु
	.ct_ulaw	= ata_ct_law,
	.ct_alaw	= ata_ct_law,
	.ct_s8		= ata_ct_s8,
	.ct_u8		= ata_ct_u8,
	.ct_s16be	= ata_ct_s16be,
	.ct_u16be	= ata_ct_u16be,
	.ct_s16le	= ata_ct_s16le,
	.ct_u16le	= ata_ct_u16le
पूर्ण;

अटल TRANS transFalconExpanding = अणु
	.ct_ulaw	= ata_ctx_law,
	.ct_alaw	= ata_ctx_law,
	.ct_s8		= ata_ctx_s8,
	.ct_u8		= ata_ctx_u8,
	.ct_s16be	= ata_ctx_s16be,
	.ct_u16be	= ata_ctx_u16be,
	.ct_s16le	= ata_ctx_s16le,
	.ct_u16le	= ata_ctx_u16le,
पूर्ण;


/*** Low level stuff *********************************************************/



/*
 * Atari (TT/Falcon)
 */

अटल व्योम *AtaAlloc(अचिन्हित पूर्णांक size, gfp_t flags)
अणु
	वापस atari_stram_alloc(size, "dmasound");
पूर्ण

अटल व्योम AtaFree(व्योम *obj, अचिन्हित पूर्णांक size)
अणु
	atari_stram_मुक्त( obj );
पूर्ण

अटल पूर्णांक __init AtaIrqInit(व्योम)
अणु
	/* Set up समयr A. Timer A
	   will receive a संकेत upon end of playing from the sound
	   hardware. Furthermore Timer A is able to count events
	   and will cause an पूर्णांकerrupt after a programmed number
	   of events. So all we need to keep the music playing is
	   to provide the sound hardware with new data upon
	   an पूर्णांकerrupt from समयr A. */
	st_mfp.tim_ct_a = 0;	/* ++roman: Stop समयr beक्रमe programming! */
	st_mfp.tim_dt_a = 1;	/* Cause पूर्णांकerrupt after first event. */
	st_mfp.tim_ct_a = 8;	/* Turn on event counting. */
	/* Register पूर्णांकerrupt handler. */
	अगर (request_irq(IRQ_MFP_TIMA, AtaInterrupt, 0, "DMA sound",
			AtaInterrupt))
		वापस 0;
	st_mfp.पूर्णांक_en_a |= 0x20;	/* Turn पूर्णांकerrupt on. */
	st_mfp.पूर्णांक_mk_a |= 0x20;
	वापस 1;
पूर्ण

#अगर_घोषित MODULE
अटल व्योम AtaIrqCleanUp(व्योम)
अणु
	st_mfp.tim_ct_a = 0;		/* stop समयr */
	st_mfp.पूर्णांक_en_a &= ~0x20;	/* turn पूर्णांकerrupt off */
	मुक्त_irq(IRQ_MFP_TIMA, AtaInterrupt);
पूर्ण
#पूर्ण_अगर /* MODULE */


#घोषणा TONE_VOXWARE_TO_DB(v) \
	(((v) < 0) ? -12 : ((v) > 100) ? 12 : ((v) - 50) * 6 / 25)
#घोषणा TONE_DB_TO_VOXWARE(v) (((v) * 25 + ((v) > 0 ? 5 : -5)) / 6 + 50)


अटल पूर्णांक AtaSetBass(पूर्णांक bass)
अणु
	dmasound.bass = TONE_VOXWARE_TO_DB(bass);
	atari_microwire_cmd(MW_LM1992_BASS(dmasound.bass));
	वापस TONE_DB_TO_VOXWARE(dmasound.bass);
पूर्ण


अटल पूर्णांक AtaSetTreble(पूर्णांक treble)
अणु
	dmasound.treble = TONE_VOXWARE_TO_DB(treble);
	atari_microwire_cmd(MW_LM1992_TREBLE(dmasound.treble));
	वापस TONE_DB_TO_VOXWARE(dmasound.treble);
पूर्ण



/*
 * TT
 */


अटल व्योम TTSilence(व्योम)
अणु
	tt_dmasnd.ctrl = DMASND_CTRL_OFF;
	atari_microwire_cmd(MW_LM1992_PSG_HIGH); /* mix in PSG संकेत 1:1 */
पूर्ण


अटल व्योम TTInit(व्योम)
अणु
	पूर्णांक mode, i, idx;
	स्थिर पूर्णांक freq[4] = अणु50066, 25033, 12517, 6258पूर्ण;

	/* search a frequency that fits पूर्णांकo the allowed error range */

	idx = -1;
	क्रम (i = 0; i < ARRAY_SIZE(freq); i++)
		/* this isn't as much useful क्रम a TT than क्रम a Falcon, but
		 * then it करोesn't hurt very much to implement it क्रम a TT too.
		 */
		अगर ((100 * असल(dmasound.soft.speed - freq[i]) / freq[i]) < catchRadius)
			idx = i;
	अगर (idx > -1) अणु
		dmasound.soft.speed = freq[idx];
		dmasound.trans_ग_लिखो = &transTTNormal;
	पूर्ण अन्यथा
		dmasound.trans_ग_लिखो = &transTTExpanding;

	TTSilence();
	dmasound.hard = dmasound.soft;

	अगर (dmasound.hard.speed > 50066) अणु
		/* we would need to squeeze the sound, but we won't करो that */
		dmasound.hard.speed = 50066;
		mode = DMASND_MODE_50KHZ;
		dmasound.trans_ग_लिखो = &transTTNormal;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 25033) अणु
		dmasound.hard.speed = 50066;
		mode = DMASND_MODE_50KHZ;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 12517) अणु
		dmasound.hard.speed = 25033;
		mode = DMASND_MODE_25KHZ;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 6258) अणु
		dmasound.hard.speed = 12517;
		mode = DMASND_MODE_12KHZ;
	पूर्ण अन्यथा अणु
		dmasound.hard.speed = 6258;
		mode = DMASND_MODE_6KHZ;
	पूर्ण

	tt_dmasnd.mode = (dmasound.hard.stereo ?
			  DMASND_MODE_STEREO : DMASND_MODE_MONO) |
		DMASND_MODE_8BIT | mode;

	expand_bal = -dmasound.soft.speed;
पूर्ण


अटल पूर्णांक TTSetFormat(पूर्णांक क्रमmat)
अणु
	/* TT sound DMA supports only 8bit modes */

	चयन (क्रमmat) अणु
	हाल AFMT_QUERY:
		वापस dmasound.soft.क्रमmat;
	हाल AFMT_MU_LAW:
	हाल AFMT_A_LAW:
	हाल AFMT_S8:
	हाल AFMT_U8:
		अवरोध;
	शेष:
		क्रमmat = AFMT_S8;
	पूर्ण

	dmasound.soft.क्रमmat = क्रमmat;
	dmasound.soft.size = 8;
	अगर (dmasound.minDev == SND_DEV_DSP) अणु
		dmasound.dsp.क्रमmat = क्रमmat;
		dmasound.dsp.size = 8;
	पूर्ण
	TTInit();

	वापस क्रमmat;
पूर्ण


#घोषणा VOLUME_VOXWARE_TO_DB(v) \
	(((v) < 0) ? -40 : ((v) > 100) ? 0 : ((v) * 2) / 5 - 40)
#घोषणा VOLUME_DB_TO_VOXWARE(v) ((((v) + 40) * 5 + 1) / 2)


अटल पूर्णांक TTSetVolume(पूर्णांक volume)
अणु
	dmasound.volume_left = VOLUME_VOXWARE_TO_DB(volume & 0xff);
	atari_microwire_cmd(MW_LM1992_BALLEFT(dmasound.volume_left));
	dmasound.volume_right = VOLUME_VOXWARE_TO_DB((volume & 0xff00) >> 8);
	atari_microwire_cmd(MW_LM1992_BALRIGHT(dmasound.volume_right));
	वापस VOLUME_DB_TO_VOXWARE(dmasound.volume_left) |
	       (VOLUME_DB_TO_VOXWARE(dmasound.volume_right) << 8);
पूर्ण


#घोषणा GAIN_VOXWARE_TO_DB(v) \
	(((v) < 0) ? -80 : ((v) > 100) ? 0 : ((v) * 4) / 5 - 80)
#घोषणा GAIN_DB_TO_VOXWARE(v) ((((v) + 80) * 5 + 1) / 4)

अटल पूर्णांक TTSetGain(पूर्णांक gain)
अणु
	dmasound.gain = GAIN_VOXWARE_TO_DB(gain);
	atari_microwire_cmd(MW_LM1992_VOLUME(dmasound.gain));
	वापस GAIN_DB_TO_VOXWARE(dmasound.gain);
पूर्ण



/*
 * Falcon
 */


अटल व्योम FalconSilence(व्योम)
अणु
	/* stop playback, set sample rate 50kHz क्रम PSG sound */
	tt_dmasnd.ctrl = DMASND_CTRL_OFF;
	tt_dmasnd.mode = DMASND_MODE_50KHZ | DMASND_MODE_STEREO | DMASND_MODE_8BIT;
	tt_dmasnd.पूर्णांक_भाग = 0; /* STE compatible भागider */
	tt_dmasnd.पूर्णांक_ctrl = 0x0;
	tt_dmasnd.cbar_src = 0x0000; /* no matrix inमाला_दो */
	tt_dmasnd.cbar_dst = 0x0000; /* no matrix outमाला_दो */
	tt_dmasnd.dac_src = 1; /* connect ADC to DAC, disconnect matrix */
	tt_dmasnd.adc_src = 3; /* ADC Input = PSG */
पूर्ण


अटल व्योम FalconInit(व्योम)
अणु
	पूर्णांक भागider, i, idx;
	स्थिर पूर्णांक freq[8] = अणु49170, 32780, 24585, 19668, 16390, 12292, 9834, 8195पूर्ण;

	/* search a frequency that fits पूर्णांकo the allowed error range */

	idx = -1;
	क्रम (i = 0; i < ARRAY_SIZE(freq); i++)
		/* अगर we will tolerate 3% error 8000Hz->8195Hz (2.38%) would
		 * be playable without expanding, but that now a kernel runसमय
		 * option
		 */
		अगर ((100 * असल(dmasound.soft.speed - freq[i]) / freq[i]) < catchRadius)
			idx = i;
	अगर (idx > -1) अणु
		dmasound.soft.speed = freq[idx];
		dmasound.trans_ग_लिखो = &transFalconNormal;
	पूर्ण अन्यथा
		dmasound.trans_ग_लिखो = &transFalconExpanding;

	FalconSilence();
	dmasound.hard = dmasound.soft;

	अगर (dmasound.hard.size == 16) अणु
		/* the Falcon can play 16bit samples only in stereo */
		dmasound.hard.stereo = 1;
	पूर्ण

	अगर (dmasound.hard.speed > 49170) अणु
		/* we would need to squeeze the sound, but we won't करो that */
		dmasound.hard.speed = 49170;
		भागider = 1;
		dmasound.trans_ग_लिखो = &transFalconNormal;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 32780) अणु
		dmasound.hard.speed = 49170;
		भागider = 1;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 24585) अणु
		dmasound.hard.speed = 32780;
		भागider = 2;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 19668) अणु
		dmasound.hard.speed = 24585;
		भागider = 3;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 16390) अणु
		dmasound.hard.speed = 19668;
		भागider = 4;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 12292) अणु
		dmasound.hard.speed = 16390;
		भागider = 5;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 9834) अणु
		dmasound.hard.speed = 12292;
		भागider = 7;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 8195) अणु
		dmasound.hard.speed = 9834;
		भागider = 9;
	पूर्ण अन्यथा अणु
		dmasound.hard.speed = 8195;
		भागider = 11;
	पूर्ण
	tt_dmasnd.पूर्णांक_भाग = भागider;

	/* Setup Falcon sound DMA क्रम playback */
	tt_dmasnd.पूर्णांक_ctrl = 0x4; /* Timer A पूर्णांक at play end */
	tt_dmasnd.track_select = 0x0; /* play 1 track, track 1 */
	tt_dmasnd.cbar_src = 0x0001; /* DMA(25MHz) --> DAC */
	tt_dmasnd.cbar_dst = 0x0000;
	tt_dmasnd.rec_track_select = 0;
	tt_dmasnd.dac_src = 2; /* connect matrix to DAC */
	tt_dmasnd.adc_src = 0; /* ADC Input = Mic */

	tt_dmasnd.mode = (dmasound.hard.stereo ?
			  DMASND_MODE_STEREO : DMASND_MODE_MONO) |
		((dmasound.hard.size == 8) ?
		 DMASND_MODE_8BIT : DMASND_MODE_16BIT) |
		DMASND_MODE_6KHZ;

	expand_bal = -dmasound.soft.speed;
पूर्ण


अटल पूर्णांक FalconSetFormat(पूर्णांक क्रमmat)
अणु
	पूर्णांक size;
	/* Falcon sound DMA supports 8bit and 16bit modes */

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

	FalconInit();

	वापस क्रमmat;
पूर्ण


/* This is क्रम the Falcon output *attenuation* in 1.5dB steps,
 * i.e. output level from 0 to -22.5dB in -1.5dB steps.
 */
#घोषणा VOLUME_VOXWARE_TO_ATT(v) \
	((v) < 0 ? 15 : (v) > 100 ? 0 : 15 - (v) * 3 / 20)
#घोषणा VOLUME_ATT_TO_VOXWARE(v) (100 - (v) * 20 / 3)


अटल पूर्णांक FalconSetVolume(पूर्णांक volume)
अणु
	dmasound.volume_left = VOLUME_VOXWARE_TO_ATT(volume & 0xff);
	dmasound.volume_right = VOLUME_VOXWARE_TO_ATT((volume & 0xff00) >> 8);
	tt_dmasnd.output_atten = dmasound.volume_left << 8 | dmasound.volume_right << 4;
	वापस VOLUME_ATT_TO_VOXWARE(dmasound.volume_left) |
	       VOLUME_ATT_TO_VOXWARE(dmasound.volume_right) << 8;
पूर्ण


अटल व्योम AtaPlayNextFrame(पूर्णांक index)
अणु
	अक्षर *start, *end;

	/* used by AtaPlay() अगर all करोubts whether there really is something
	 * to be played are alपढ़ोy wiped out.
	 */
	start = ग_लिखो_sq.buffers[ग_लिखो_sq.front];
	end = start+((ग_लिखो_sq.count == index) ? ग_लिखो_sq.rear_size
					       : ग_लिखो_sq.block_size);
	/* end might not be a legal भव address. */
	DMASNDSetEnd(virt_to_phys(end - 1) + 1);
	DMASNDSetBase(virt_to_phys(start));
	/* Since only an even number of samples per frame can
	   be played, we might lose one byte here. (TO DO) */
	ग_लिखो_sq.front = (ग_लिखो_sq.front+1) % ग_लिखो_sq.max_count;
	ग_लिखो_sq.active++;
	tt_dmasnd.ctrl = DMASND_CTRL_ON | DMASND_CTRL_REPEAT;
पूर्ण


अटल व्योम AtaPlay(व्योम)
अणु
	/* ++TeSche: Note that ग_लिखो_sq.active is no दीर्घer just a flag but
	 * holds the number of frames the DMA is currently programmed क्रम
	 * instead, may be 0, 1 (currently being played) or 2 (pre-programmed).
	 *
	 * Changes करोne to ग_लिखो_sq.count and ग_लिखो_sq.active are a bit more
	 * subtle again so now I must admit I also prefer disabling the irq
	 * here rather than considering all possible situations. But the poपूर्णांक
	 * is that disabling the irq करोesn't have any bad influence on this
	 * version of the driver as we benefit from having pre-programmed the
	 * DMA wherever possible: There's no need to reload the DMA at the
	 * exact समय of an पूर्णांकerrupt but only at some समय जबतक the
	 * pre-programmed frame is playing!
	 */
	atari_disable_irq(IRQ_MFP_TIMA);

	अगर (ग_लिखो_sq.active == 2 ||	/* DMA is 'full' */
	    ग_लिखो_sq.count <= 0) अणु	/* nothing to करो */
		atari_enable_irq(IRQ_MFP_TIMA);
		वापस;
	पूर्ण

	अगर (ग_लिखो_sq.active == 0) अणु
		/* looks like there's nothing 'in' the DMA yet, so try
		 * to put two frames पूर्णांकo it (at least one is available).
		 */
		अगर (ग_लिखो_sq.count == 1 &&
		    ग_लिखो_sq.rear_size < ग_लिखो_sq.block_size &&
		    !ग_लिखो_sq.syncing) अणु
			/* hmmm, the only existing frame is not
			 * yet filled and we're not syncing?
			 */
			atari_enable_irq(IRQ_MFP_TIMA);
			वापस;
		पूर्ण
		AtaPlayNextFrame(1);
		अगर (ग_लिखो_sq.count == 1) अणु
			/* no more frames */
			atari_enable_irq(IRQ_MFP_TIMA);
			वापस;
		पूर्ण
		अगर (ग_लिखो_sq.count == 2 &&
		    ग_लिखो_sq.rear_size < ग_लिखो_sq.block_size &&
		    !ग_लिखो_sq.syncing) अणु
			/* hmmm, there were two frames, but the second
			 * one is not yet filled and we're not syncing?
			 */
			atari_enable_irq(IRQ_MFP_TIMA);
			वापस;
		पूर्ण
		AtaPlayNextFrame(2);
	पूर्ण अन्यथा अणु
		/* there's alपढ़ोy a frame being played so we may only stuff
		 * one new पूर्णांकo the DMA, but even अगर this may be the last
		 * frame existing the previous one is still on ग_लिखो_sq.count.
		 */
		अगर (ग_लिखो_sq.count == 2 &&
		    ग_लिखो_sq.rear_size < ग_लिखो_sq.block_size &&
		    !ग_लिखो_sq.syncing) अणु
			/* hmmm, the only existing frame is not
			 * yet filled and we're not syncing?
			 */
			atari_enable_irq(IRQ_MFP_TIMA);
			वापस;
		पूर्ण
		AtaPlayNextFrame(2);
	पूर्ण
	atari_enable_irq(IRQ_MFP_TIMA);
पूर्ण


अटल irqवापस_t AtaInterrupt(पूर्णांक irq, व्योम *dummy)
अणु
#अगर 0
	/* ++TeSche: अगर you should want to test this... */
	अटल पूर्णांक cnt;
	अगर (ग_लिखो_sq.active == 2)
		अगर (++cnt == 10) अणु
			/* simulate losing an पूर्णांकerrupt */
			cnt = 0;
			वापस IRQ_HANDLED;
		पूर्ण
#पूर्ण_अगर
	spin_lock(&dmasound.lock);
	अगर (ग_लिखो_sq_ignore_पूर्णांक && is_falcon) अणु
		/* ++TeSche: Falcon only: ignore first irq because it comes
		 * immediately after starting a frame. after that, irqs come
		 * (almost) like on the TT.
		 */
		ग_लिखो_sq_ignore_पूर्णांक = 0;
		जाओ out;
	पूर्ण

	अगर (!ग_लिखो_sq.active) अणु
		/* playing was पूर्णांकerrupted and sq_reset() has alपढ़ोy cleared
		 * the sq variables, so better करोn't करो anything here.
		 */
		WAKE_UP(ग_लिखो_sq.sync_queue);
		जाओ out;
	पूर्ण

	/* Probably ;) one frame is finished. Well, in fact it may be that a
	 * pre-programmed one is also finished because there has been a दीर्घ
	 * delay in पूर्णांकerrupt delivery and we've completely lost one, but
	 * there's no way to detect such a situation. In such a हाल the last
	 * frame will be played more than once and the situation will recover
	 * as soon as the irq माला_लो through.
	 */
	ग_लिखो_sq.count--;
	ग_लिखो_sq.active--;

	अगर (!ग_लिखो_sq.active) अणु
		tt_dmasnd.ctrl = DMASND_CTRL_OFF;
		ग_लिखो_sq_ignore_पूर्णांक = 1;
	पूर्ण

	WAKE_UP(ग_लिखो_sq.action_queue);
	/* At least one block of the queue is मुक्त now
	   so wake up a writing process blocked because
	   of a full queue. */

	अगर ((ग_लिखो_sq.active != 1) || (ग_लिखो_sq.count != 1))
		/* We must be a bit carefully here: ग_लिखो_sq.count indicates the
		 * number of buffers used and not the number of frames to be
		 * played. If ग_लिखो_sq.count==1 and ग_लिखो_sq.active==1 that
		 * means the only reमुख्यing frame was alपढ़ोy programmed
		 * earlier (and is currently running) so we mustn't call
		 * AtaPlay() here, otherwise we'll play one frame too much.
		 */
		AtaPlay();

	अगर (!ग_लिखो_sq.active) WAKE_UP(ग_लिखो_sq.sync_queue);
	/* We are not playing after AtaPlay(), so there
	   is nothing to play any more. Wake up a process
	   रुकोing क्रम audio output to drain. */
out:
	spin_unlock(&dmasound.lock);
	वापस IRQ_HANDLED;
पूर्ण


/*** Mid level stuff *********************************************************/


/*
 * /dev/mixer असलtraction
 */

#घोषणा RECLEVEL_VOXWARE_TO_GAIN(v)	\
	((v) < 0 ? 0 : (v) > 100 ? 15 : (v) * 3 / 20)
#घोषणा RECLEVEL_GAIN_TO_VOXWARE(v)	(((v) * 20 + 2) / 3)


अटल व्योम __init TTMixerInit(व्योम)
अणु
	atari_microwire_cmd(MW_LM1992_VOLUME(0));
	dmasound.volume_left = 0;
	atari_microwire_cmd(MW_LM1992_BALLEFT(0));
	dmasound.volume_right = 0;
	atari_microwire_cmd(MW_LM1992_BALRIGHT(0));
	atari_microwire_cmd(MW_LM1992_TREBLE(0));
	atari_microwire_cmd(MW_LM1992_BASS(0));
पूर्ण

अटल व्योम __init FalconMixerInit(व्योम)
अणु
	dmasound.volume_left = (tt_dmasnd.output_atten & 0xf00) >> 8;
	dmasound.volume_right = (tt_dmasnd.output_atten & 0xf0) >> 4;
पूर्ण

अटल पूर्णांक AtaMixerIoctl(u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक data;
	अचिन्हित दीर्घ flags;
	चयन (cmd) अणु
	    हाल SOUND_MIXER_READ_SPEAKER:
		    अगर (is_falcon || MACH_IS_TT) अणु
			    पूर्णांक porta;
			    spin_lock_irqsave(&dmasound.lock, flags);
			    sound_ym.rd_data_reg_sel = 14;
			    porta = sound_ym.rd_data_reg_sel;
			    spin_unlock_irqrestore(&dmasound.lock, flags);
			    वापस IOCTL_OUT(arg, porta & 0x40 ? 0 : 100);
		    पूर्ण
		    अवरोध;
	    हाल SOUND_MIXER_WRITE_VOLUME:
		    IOCTL_IN(arg, data);
		    वापस IOCTL_OUT(arg, dmasound_set_volume(data));
	    हाल SOUND_MIXER_WRITE_SPEAKER:
		    अगर (is_falcon || MACH_IS_TT) अणु
			    पूर्णांक porta;
			    IOCTL_IN(arg, data);
			    spin_lock_irqsave(&dmasound.lock, flags);
			    sound_ym.rd_data_reg_sel = 14;
			    porta = (sound_ym.rd_data_reg_sel & ~0x40) |
				    (data < 50 ? 0x40 : 0);
			    sound_ym.wd_data = porta;
			    spin_unlock_irqrestore(&dmasound.lock, flags);
			    वापस IOCTL_OUT(arg, porta & 0x40 ? 0 : 100);
		    पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण


अटल पूर्णांक TTMixerIoctl(u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक data;
	चयन (cmd) अणु
	    हाल SOUND_MIXER_READ_RECMASK:
		वापस IOCTL_OUT(arg, 0);
	    हाल SOUND_MIXER_READ_DEVMASK:
		वापस IOCTL_OUT(arg,
				 SOUND_MASK_VOLUME | SOUND_MASK_TREBLE | SOUND_MASK_BASS |
				 (MACH_IS_TT ? SOUND_MASK_SPEAKER : 0));
	    हाल SOUND_MIXER_READ_STEREODEVS:
		वापस IOCTL_OUT(arg, SOUND_MASK_VOLUME);
	    हाल SOUND_MIXER_READ_VOLUME:
		वापस IOCTL_OUT(arg,
				 VOLUME_DB_TO_VOXWARE(dmasound.volume_left) |
				 (VOLUME_DB_TO_VOXWARE(dmasound.volume_right) << 8));
	    हाल SOUND_MIXER_READ_BASS:
		वापस IOCTL_OUT(arg, TONE_DB_TO_VOXWARE(dmasound.bass));
	    हाल SOUND_MIXER_READ_TREBLE:
		वापस IOCTL_OUT(arg, TONE_DB_TO_VOXWARE(dmasound.treble));
	    हाल SOUND_MIXER_READ_OGAIN:
		वापस IOCTL_OUT(arg, GAIN_DB_TO_VOXWARE(dmasound.gain));
	    हाल SOUND_MIXER_WRITE_BASS:
		IOCTL_IN(arg, data);
		वापस IOCTL_OUT(arg, dmasound_set_bass(data));
	    हाल SOUND_MIXER_WRITE_TREBLE:
		IOCTL_IN(arg, data);
		वापस IOCTL_OUT(arg, dmasound_set_treble(data));
	    हाल SOUND_MIXER_WRITE_OGAIN:
		IOCTL_IN(arg, data);
		वापस IOCTL_OUT(arg, dmasound_set_gain(data));
	पूर्ण
	वापस AtaMixerIoctl(cmd, arg);
पूर्ण

अटल पूर्णांक FalconMixerIoctl(u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक data;
	चयन (cmd) अणु
	हाल SOUND_MIXER_READ_RECMASK:
		वापस IOCTL_OUT(arg, SOUND_MASK_MIC);
	हाल SOUND_MIXER_READ_DEVMASK:
		वापस IOCTL_OUT(arg, SOUND_MASK_VOLUME | SOUND_MASK_MIC | SOUND_MASK_SPEAKER);
	हाल SOUND_MIXER_READ_STEREODEVS:
		वापस IOCTL_OUT(arg, SOUND_MASK_VOLUME | SOUND_MASK_MIC);
	हाल SOUND_MIXER_READ_VOLUME:
		वापस IOCTL_OUT(arg,
			VOLUME_ATT_TO_VOXWARE(dmasound.volume_left) |
			VOLUME_ATT_TO_VOXWARE(dmasound.volume_right) << 8);
	हाल SOUND_MIXER_READ_CAPS:
		वापस IOCTL_OUT(arg, SOUND_CAP_EXCL_INPUT);
	हाल SOUND_MIXER_WRITE_MIC:
		IOCTL_IN(arg, data);
		tt_dmasnd.input_gain =
			RECLEVEL_VOXWARE_TO_GAIN(data & 0xff) << 4 |
			RECLEVEL_VOXWARE_TO_GAIN(data >> 8 & 0xff);
		fallthrough;	/* वापस set value */
	हाल SOUND_MIXER_READ_MIC:
		वापस IOCTL_OUT(arg,
			RECLEVEL_GAIN_TO_VOXWARE(tt_dmasnd.input_gain >> 4 & 0xf) |
			RECLEVEL_GAIN_TO_VOXWARE(tt_dmasnd.input_gain & 0xf) << 8);
	पूर्ण
	वापस AtaMixerIoctl(cmd, arg);
पूर्ण

अटल पूर्णांक AtaWriteSqSetup(व्योम)
अणु
	ग_लिखो_sq_ignore_पूर्णांक = 0;
	वापस 0 ;
पूर्ण

अटल पूर्णांक AtaSqOpen(भ_शेषe_t mode)
अणु
	ग_लिखो_sq_ignore_पूर्णांक = 1;
	वापस 0 ;
पूर्ण

अटल पूर्णांक TTStateInfo(अक्षर *buffer, माप_प्रकार space)
अणु
	पूर्णांक len = 0;
	len += प्र_लिखो(buffer+len, "\tvol left  %ddB [-40...  0]\n",
		       dmasound.volume_left);
	len += प्र_लिखो(buffer+len, "\tvol right %ddB [-40...  0]\n",
		       dmasound.volume_right);
	len += प्र_लिखो(buffer+len, "\tbass      %ddB [-12...+12]\n",
		       dmasound.bass);
	len += प्र_लिखो(buffer+len, "\ttreble    %ddB [-12...+12]\n",
		       dmasound.treble);
	अगर (len >= space) अणु
		prपूर्णांकk(KERN_ERR "dmasound_atari: overflowed state buffer alloc.\n") ;
		len = space ;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक FalconStateInfo(अक्षर *buffer, माप_प्रकार space)
अणु
	पूर्णांक len = 0;
	len += प्र_लिखो(buffer+len, "\tvol left  %ddB [-22.5 ... 0]\n",
		       dmasound.volume_left);
	len += प्र_लिखो(buffer+len, "\tvol right %ddB [-22.5 ... 0]\n",
		       dmasound.volume_right);
	अगर (len >= space) अणु
		prपूर्णांकk(KERN_ERR "dmasound_atari: overflowed state buffer alloc.\n") ;
		len = space ;
	पूर्ण
	वापस len;
पूर्ण


/*** Machine definitions *****************************************************/

अटल SETTINGS def_hard_falcon = अणु
	.क्रमmat		= AFMT_S8,
	.stereo		= 0,
	.size		= 8,
	.speed		= 8195
पूर्ण ;

अटल SETTINGS def_hard_tt = अणु
	.क्रमmat	= AFMT_S8,
	.stereo	= 0,
	.size	= 8,
	.speed	= 12517
पूर्ण ;

अटल SETTINGS def_soft = अणु
	.क्रमmat	= AFMT_U8,
	.stereo	= 0,
	.size	= 8,
	.speed	= 8000
पूर्ण ;

अटल __initdata MACHINE machTT = अणु
	.name		= "Atari",
	.name2		= "TT",
	.owner		= THIS_MODULE,
	.dma_alloc	= AtaAlloc,
	.dma_मुक्त	= AtaFree,
	.irqinit	= AtaIrqInit,
#अगर_घोषित MODULE
	.irqcleanup	= AtaIrqCleanUp,
#पूर्ण_अगर /* MODULE */
	.init		= TTInit,
	.silence	= TTSilence,
	.setFormat	= TTSetFormat,
	.setVolume	= TTSetVolume,
	.setBass	= AtaSetBass,
	.setTreble	= AtaSetTreble,
	.setGain	= TTSetGain,
	.play		= AtaPlay,
	.mixer_init	= TTMixerInit,
	.mixer_ioctl	= TTMixerIoctl,
	.ग_लिखो_sq_setup	= AtaWriteSqSetup,
	.sq_खोलो	= AtaSqOpen,
	.state_info	= TTStateInfo,
	.min_dsp_speed	= 6258,
	.version	= ((DMASOUND_ATARI_REVISION<<8) | DMASOUND_ATARI_EDITION),
	.hardware_afmts	= AFMT_S8,  /* h'ware-supported क्रमmats *only* here */
	.capabilities	=  DSP_CAP_BATCH	/* As per SNDCTL_DSP_GETCAPS */
पूर्ण;

अटल __initdata MACHINE machFalcon = अणु
	.name		= "Atari",
	.name2		= "FALCON",
	.dma_alloc	= AtaAlloc,
	.dma_मुक्त	= AtaFree,
	.irqinit	= AtaIrqInit,
#अगर_घोषित MODULE
	.irqcleanup	= AtaIrqCleanUp,
#पूर्ण_अगर /* MODULE */
	.init		= FalconInit,
	.silence	= FalconSilence,
	.setFormat	= FalconSetFormat,
	.setVolume	= FalconSetVolume,
	.setBass	= AtaSetBass,
	.setTreble	= AtaSetTreble,
	.play		= AtaPlay,
	.mixer_init	= FalconMixerInit,
	.mixer_ioctl	= FalconMixerIoctl,
	.ग_लिखो_sq_setup	= AtaWriteSqSetup,
	.sq_खोलो	= AtaSqOpen,
	.state_info	= FalconStateInfo,
	.min_dsp_speed	= 8195,
	.version	= ((DMASOUND_ATARI_REVISION<<8) | DMASOUND_ATARI_EDITION),
	.hardware_afmts	= (AFMT_S8 | AFMT_S16_BE), /* h'ware-supported क्रमmats *only* here */
	.capabilities	=  DSP_CAP_BATCH	/* As per SNDCTL_DSP_GETCAPS */
पूर्ण;


/*** Config & Setup **********************************************************/


अटल पूर्णांक __init dmasound_atari_init(व्योम)
अणु
	अगर (MACH_IS_ATARI && ATARIHW_PRESENT(PCM_8BIT)) अणु
	    अगर (ATARIHW_PRESENT(CODEC)) अणु
		dmasound.mach = machFalcon;
		dmasound.mach.शेष_soft = def_soft ;
		dmasound.mach.शेष_hard = def_hard_falcon ;
		is_falcon = 1;
	    पूर्ण अन्यथा अगर (ATARIHW_PRESENT(MICROWIRE)) अणु
		dmasound.mach = machTT;
		dmasound.mach.शेष_soft = def_soft ;
		dmasound.mach.शेष_hard = def_hard_tt ;
		is_falcon = 0;
	    पूर्ण अन्यथा
		वापस -ENODEV;
	    अगर ((st_mfp.पूर्णांक_en_a & st_mfp.पूर्णांक_mk_a & 0x20) == 0)
		वापस dmasound_init();
	    अन्यथा अणु
		prपूर्णांकk("DMA sound driver: Timer A interrupt already in use\n");
		वापस -EBUSY;
	    पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास dmasound_atari_cleanup(व्योम)
अणु
	dmasound_deinit();
पूर्ण

module_init(dmasound_atari_init);
module_निकास(dmasound_atari_cleanup);
MODULE_LICENSE("GPL");
