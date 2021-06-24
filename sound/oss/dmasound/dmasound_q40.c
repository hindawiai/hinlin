<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/sound/oss/dmasound/dmasound_q40.c
 *
 *  Q40 DMA Sound Driver
 *
 *  See linux/sound/oss/dmasound/dmasound_core.c क्रम copyright and credits
 *  prior to 28/01/2001
 *
 *  28/01/2001 [0.1] Iain Sanकरोe
 *		     - added versioning
 *		     - put in and populated the hardware_afmts field.
 *             [0.2] - put in SNDCTL_DSP_GETCAPS value.
 *	       [0.3] - put in शेष hard/soft settings.
 */


#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/soundcard.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/q40पूर्णांकs.h>
#समावेश <यंत्र/q40_master.h>

#समावेश "dmasound.h"

#घोषणा DMASOUND_Q40_REVISION 0
#घोषणा DMASOUND_Q40_EDITION 3

अटल पूर्णांक expand_bal;	/* Balance factor क्रम expanding (not volume!) */
अटल पूर्णांक expand_data;	/* Data क्रम expanding */


/*** Low level stuff *********************************************************/


अटल व्योम *Q40Alloc(अचिन्हित पूर्णांक size, gfp_t flags);
अटल व्योम Q40Free(व्योम *, अचिन्हित पूर्णांक);
अटल पूर्णांक Q40IrqInit(व्योम);
#अगर_घोषित MODULE
अटल व्योम Q40IrqCleanUp(व्योम);
#पूर्ण_अगर
अटल व्योम Q40Silence(व्योम);
अटल व्योम Q40Init(व्योम);
अटल पूर्णांक Q40SetFormat(पूर्णांक क्रमmat);
अटल पूर्णांक Q40SetVolume(पूर्णांक volume);
अटल व्योम Q40PlayNextFrame(पूर्णांक index);
अटल व्योम Q40Play(व्योम);
अटल irqवापस_t Q40StereoInterrupt(पूर्णांक irq, व्योम *dummy);
अटल irqवापस_t Q40MonoInterrupt(पूर्णांक irq, व्योम *dummy);
अटल व्योम Q40Interrupt(व्योम);


/*** Mid level stuff *********************************************************/



/* userCount, frameUsed, frameLeft == byte counts */
अटल sमाप_प्रकार q40_ct_law(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			   u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			   sमाप_प्रकार frameLeft)
अणु
	अक्षर *table = dmasound.soft.क्रमmat == AFMT_MU_LAW ? dmasound_ulaw2dma8: dmasound_alaw2dma8;
	sमाप_प्रकार count, used;
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];

	used = count = min_t(माप_प्रकार, userCount, frameLeft);
	अगर (copy_from_user(p,userPtr,count))
	  वापस -EFAULT;
	जबतक (count > 0) अणु
		*p = table[*p]+128;
		p++;
		count--;
	पूर्ण
	*frameUsed += used ;
	वापस used;
पूर्ण


अटल sमाप_प्रकार q40_ct_s8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			  u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			  sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];

	used = count = min_t(माप_प्रकार, userCount, frameLeft);
	अगर (copy_from_user(p,userPtr,count))
	  वापस -EFAULT;
	जबतक (count > 0) अणु
		*p = *p + 128;
		p++;
		count--;
	पूर्ण
	*frameUsed += used;
	वापस used;
पूर्ण

अटल sमाप_प्रकार q40_ct_u8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			  u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			  sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार count, used;
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];

	used = count = min_t(माप_प्रकार, userCount, frameLeft);
	अगर (copy_from_user(p,userPtr,count))
	  वापस -EFAULT;
	*frameUsed += used;
	वापस used;
पूर्ण


/* a bit too complicated to optimise right now ..*/
अटल sमाप_प्रकार q40_ctx_law(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft)
अणु
	अचिन्हित अक्षर *table = (अचिन्हित अक्षर *)
		(dmasound.soft.क्रमmat == AFMT_MU_LAW ? dmasound_ulaw2dma8: dmasound_alaw2dma8);
	अचिन्हित पूर्णांक data = expand_data;
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];
	पूर्णांक bal = expand_bal;
	पूर्णांक hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	पूर्णांक utotal, ftotal;

	ftotal = frameLeft;
	utotal = userCount;
	जबतक (frameLeft) अणु
		u_अक्षर c;
		अगर (bal < 0) अणु
			अगर (userCount == 0)
				अवरोध;
			अगर (get_user(c, userPtr++))
				वापस -EFAULT;
			data = table[c];
			data += 0x80;
			userCount--;
			bal += hSpeed;
		पूर्ण
		*p++ = data;
		frameLeft--;
		bal -= sSpeed;
	पूर्ण
	expand_bal = bal;
	expand_data = data;
	*frameUsed += (ftotal - frameLeft);
	utotal -= userCount;
	वापस utotal;
पूर्ण


अटल sमाप_प्रकार q40_ctx_s8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			   u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			   sमाप_प्रकार frameLeft)
अणु
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];
	अचिन्हित पूर्णांक data = expand_data;
	पूर्णांक bal = expand_bal;
	पूर्णांक hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	पूर्णांक utotal, ftotal;


	ftotal = frameLeft;
	utotal = userCount;
	जबतक (frameLeft) अणु
		u_अक्षर c;
		अगर (bal < 0) अणु
			अगर (userCount == 0)
				अवरोध;
			अगर (get_user(c, userPtr++))
				वापस -EFAULT;
			data = c ;
			data += 0x80;
			userCount--;
			bal += hSpeed;
		पूर्ण
		*p++ = data;
		frameLeft--;
		bal -= sSpeed;
	पूर्ण
	expand_bal = bal;
	expand_data = data;
	*frameUsed += (ftotal - frameLeft);
	utotal -= userCount;
	वापस utotal;
पूर्ण


अटल sमाप_प्रकार q40_ctx_u8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			   u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			   sमाप_प्रकार frameLeft)
अणु
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];
	अचिन्हित पूर्णांक data = expand_data;
	पूर्णांक bal = expand_bal;
	पूर्णांक hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	पूर्णांक utotal, ftotal;

	ftotal = frameLeft;
	utotal = userCount;
	जबतक (frameLeft) अणु
		u_अक्षर c;
		अगर (bal < 0) अणु
			अगर (userCount == 0)
				अवरोध;
			अगर (get_user(c, userPtr++))
				वापस -EFAULT;
			data = c ;
			userCount--;
			bal += hSpeed;
		पूर्ण
		*p++ = data;
		frameLeft--;
		bal -= sSpeed;
	पूर्ण
	expand_bal = bal;
	expand_data = data;
	*frameUsed += (ftotal - frameLeft) ;
	utotal -= userCount;
	वापस utotal;
पूर्ण

/* compressing versions */
अटल sमाप_प्रकार q40_ctc_law(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			    u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			    sमाप_प्रकार frameLeft)
अणु
	अचिन्हित अक्षर *table = (अचिन्हित अक्षर *)
		(dmasound.soft.क्रमmat == AFMT_MU_LAW ? dmasound_ulaw2dma8: dmasound_alaw2dma8);
	अचिन्हित पूर्णांक data = expand_data;
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];
	पूर्णांक bal = expand_bal;
	पूर्णांक hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	पूर्णांक utotal, ftotal;
 
	ftotal = frameLeft;
	utotal = userCount;
	जबतक (frameLeft) अणु
		u_अक्षर c;
		जबतक(bal<0) अणु
			अगर (userCount == 0)
				जाओ lout;
			अगर (!(bal<(-hSpeed))) अणु
				अगर (get_user(c, userPtr))
					वापस -EFAULT;
				data = 0x80 + table[c];
			पूर्ण
			userPtr++;
			userCount--;
			bal += hSpeed;
		पूर्ण
		*p++ = data;
		frameLeft--;
		bal -= sSpeed;
	पूर्ण
 lout:
	expand_bal = bal;
	expand_data = data;
	*frameUsed += (ftotal - frameLeft);
	utotal -= userCount;
	वापस utotal;
पूर्ण


अटल sमाप_प्रकार q40_ctc_s8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			   u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			   sमाप_प्रकार frameLeft)
अणु
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];
	अचिन्हित पूर्णांक data = expand_data;
	पूर्णांक bal = expand_bal;
	पूर्णांक hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	पूर्णांक utotal, ftotal;

	ftotal = frameLeft;
	utotal = userCount;
	जबतक (frameLeft) अणु
		u_अक्षर c;
		जबतक (bal < 0) अणु
			अगर (userCount == 0)
				जाओ lout;
			अगर (!(bal<(-hSpeed))) अणु
				अगर (get_user(c, userPtr))
					वापस -EFAULT;
				data = c + 0x80;
			पूर्ण
			userPtr++;
			userCount--;
			bal += hSpeed;
		पूर्ण
		*p++ = data;
		frameLeft--;
		bal -= sSpeed;
	पूर्ण
 lout:
	expand_bal = bal;
	expand_data = data;
	*frameUsed += (ftotal - frameLeft);
	utotal -= userCount;
	वापस utotal;
पूर्ण


अटल sमाप_प्रकार q40_ctc_u8(स्थिर u_अक्षर __user *userPtr, माप_प्रकार userCount,
			   u_अक्षर frame[], sमाप_प्रकार *frameUsed,
			   sमाप_प्रकार frameLeft)
अणु
	u_अक्षर *p = (u_अक्षर *) &frame[*frameUsed];
	अचिन्हित पूर्णांक data = expand_data;
	पूर्णांक bal = expand_bal;
	पूर्णांक hSpeed = dmasound.hard.speed, sSpeed = dmasound.soft.speed;
	पूर्णांक utotal, ftotal;

	ftotal = frameLeft;
	utotal = userCount;
	जबतक (frameLeft) अणु
		u_अक्षर c;
		जबतक (bal < 0) अणु
			अगर (userCount == 0)
				जाओ lout;
			अगर (!(bal<(-hSpeed))) अणु
				अगर (get_user(c, userPtr))
					वापस -EFAULT;
				data = c ;
			पूर्ण
			userPtr++;
			userCount--;
			bal += hSpeed;
		पूर्ण
		*p++ = data;
		frameLeft--;
		bal -= sSpeed;
	पूर्ण
 lout:
	expand_bal = bal;
	expand_data = data;
	*frameUsed += (ftotal - frameLeft) ;
	utotal -= userCount;
	वापस utotal;
पूर्ण


अटल TRANS transQ40Normal = अणु
	q40_ct_law, q40_ct_law, q40_ct_s8, q40_ct_u8, शून्य, शून्य, शून्य, शून्य
पूर्ण;

अटल TRANS transQ40Expanding = अणु
	q40_ctx_law, q40_ctx_law, q40_ctx_s8, q40_ctx_u8, शून्य, शून्य, शून्य, शून्य
पूर्ण;

अटल TRANS transQ40Compressing = अणु
	q40_ctc_law, q40_ctc_law, q40_ctc_s8, q40_ctc_u8, शून्य, शून्य, शून्य, शून्य
पूर्ण;


/*** Low level stuff *********************************************************/

अटल व्योम *Q40Alloc(अचिन्हित पूर्णांक size, gfp_t flags)
अणु
         वापस kदो_स्मृति(size, flags); /* change to vदो_स्मृति */
पूर्ण

अटल व्योम Q40Free(व्योम *ptr, अचिन्हित पूर्णांक size)
अणु
	kमुक्त(ptr);
पूर्ण

अटल पूर्णांक __init Q40IrqInit(व्योम)
अणु
	/* Register पूर्णांकerrupt handler. */
	अगर (request_irq(Q40_IRQ_SAMPLE, Q40StereoInterrupt, 0,
		    "DMA sound", Q40Interrupt))
		वापस 0;

	वापस(1);
पूर्ण


#अगर_घोषित MODULE
अटल व्योम Q40IrqCleanUp(व्योम)
अणु
        master_outb(0,SAMPLE_ENABLE_REG);
	मुक्त_irq(Q40_IRQ_SAMPLE, Q40Interrupt);
पूर्ण
#पूर्ण_अगर /* MODULE */


अटल व्योम Q40Silence(व्योम)
अणु
        master_outb(0,SAMPLE_ENABLE_REG);
	*DAC_LEFT=*DAC_RIGHT=127;
पूर्ण

अटल अक्षर *q40_pp;
अटल अचिन्हित पूर्णांक q40_sc;

अटल व्योम Q40PlayNextFrame(पूर्णांक index)
अणु
	u_अक्षर *start;
	u_दीर्घ size;
	u_अक्षर speed;
	पूर्णांक error;

	/* used by Q40Play() अगर all करोubts whether there really is something
	 * to be played are alपढ़ोy wiped out.
	 */
	start = ग_लिखो_sq.buffers[ग_लिखो_sq.front];
	size = (ग_लिखो_sq.count == index ? ग_लिखो_sq.rear_size : ग_लिखो_sq.block_size);

	q40_pp=start;
	q40_sc=size;

	ग_लिखो_sq.front = (ग_लिखो_sq.front+1) % ग_लिखो_sq.max_count;
	ग_लिखो_sq.active++;

	speed=(dmasound.hard.speed==10000 ? 0 : 1);

	master_outb( 0,SAMPLE_ENABLE_REG);
	मुक्त_irq(Q40_IRQ_SAMPLE, Q40Interrupt);
	अगर (dmasound.soft.stereo)
		error = request_irq(Q40_IRQ_SAMPLE, Q40StereoInterrupt, 0,
				    "Q40 sound", Q40Interrupt);
	  अन्यथा
		error = request_irq(Q40_IRQ_SAMPLE, Q40MonoInterrupt, 0,
				    "Q40 sound", Q40Interrupt);
	अगर (error && prपूर्णांकk_ratelimit())
		pr_err("Couldn't register sound interrupt\n");

	master_outb( speed, SAMPLE_RATE_REG);
	master_outb( 1,SAMPLE_CLEAR_REG);
	master_outb( 1,SAMPLE_ENABLE_REG);
पूर्ण

अटल व्योम Q40Play(व्योम)
अणु
        अचिन्हित दीर्घ flags;

	अगर (ग_लिखो_sq.active || ग_लिखो_sq.count<=0 ) अणु
		/* There's alपढ़ोy a frame loaded */
		वापस;
	पूर्ण

	/* nothing in the queue */
	अगर (ग_लिखो_sq.count <= 1 && ग_लिखो_sq.rear_size < ग_लिखो_sq.block_size && !ग_लिखो_sq.syncing) अणु
	         /* hmmm, the only existing frame is not
		  * yet filled and we're not syncing?
		  */
	         वापस;
	पूर्ण
	spin_lock_irqsave(&dmasound.lock, flags);
	Q40PlayNextFrame(1);
	spin_unlock_irqrestore(&dmasound.lock, flags);
पूर्ण

अटल irqवापस_t Q40StereoInterrupt(पूर्णांक irq, व्योम *dummy)
अणु
	spin_lock(&dmasound.lock);
        अगर (q40_sc>1)अणु
            *DAC_LEFT=*q40_pp++;
	    *DAC_RIGHT=*q40_pp++;
	    q40_sc -=2;
	    master_outb(1,SAMPLE_CLEAR_REG);
	पूर्णअन्यथा Q40Interrupt();
	spin_unlock(&dmasound.lock);
	वापस IRQ_HANDLED;
पूर्ण
अटल irqवापस_t Q40MonoInterrupt(पूर्णांक irq, व्योम *dummy)
अणु
	spin_lock(&dmasound.lock);
        अगर (q40_sc>0)अणु
            *DAC_LEFT=*q40_pp;
	    *DAC_RIGHT=*q40_pp++;
	    q40_sc --;
	    master_outb(1,SAMPLE_CLEAR_REG);
	पूर्णअन्यथा Q40Interrupt();
	spin_unlock(&dmasound.lock);
	वापस IRQ_HANDLED;
पूर्ण
अटल व्योम Q40Interrupt(व्योम)
अणु
	अगर (!ग_लिखो_sq.active) अणु
	          /* playing was पूर्णांकerrupted and sq_reset() has alपढ़ोy cleared
		   * the sq variables, so better करोn't करो anything here.
		   */
	           WAKE_UP(ग_लिखो_sq.sync_queue);
		   master_outb(0,SAMPLE_ENABLE_REG); /* better safe */
		   जाओ निकास;
	पूर्ण अन्यथा ग_लिखो_sq.active=0;
	ग_लिखो_sq.count--;
	Q40Play();

	अगर (q40_sc<2)
	      अणु /* there was nothing to play, disable irq */
		master_outb(0,SAMPLE_ENABLE_REG);
		*DAC_LEFT=*DAC_RIGHT=127;
	      पूर्ण
	WAKE_UP(ग_लिखो_sq.action_queue);

 निकास:
	master_outb(1,SAMPLE_CLEAR_REG);
पूर्ण


अटल व्योम Q40Init(व्योम)
अणु
	पूर्णांक i, idx;
	स्थिर पूर्णांक freq[] = अणु10000, 20000पूर्ण;

	/* search a frequency that fits पूर्णांकo the allowed error range */

	idx = -1;
	क्रम (i = 0; i < 2; i++)
		अगर ((100 * असल(dmasound.soft.speed - freq[i]) / freq[i]) <= catchRadius)
			idx = i;

	dmasound.hard = dmasound.soft;
	/*sound.hard.stereo=1;*/ /* no दीर्घer true */
	dmasound.hard.size=8;

	अगर (idx > -1) अणु
		dmasound.soft.speed = freq[idx];
		dmasound.trans_ग_लिखो = &transQ40Normal;
	पूर्ण अन्यथा
		dmasound.trans_ग_लिखो = &transQ40Expanding;

	Q40Silence();

	अगर (dmasound.hard.speed > 20200) अणु
		/* squeeze the sound, we करो that */
		dmasound.hard.speed = 20000;
		dmasound.trans_ग_लिखो = &transQ40Compressing;
	पूर्ण अन्यथा अगर (dmasound.hard.speed > 10000) अणु
		dmasound.hard.speed = 20000;
	पूर्ण अन्यथा अणु
		dmasound.hard.speed = 10000;
	पूर्ण
	expand_bal = -dmasound.soft.speed;
पूर्ण


अटल पूर्णांक Q40SetFormat(पूर्णांक क्रमmat)
अणु
	/* Q40 sound supports only 8bit modes */

	चयन (क्रमmat) अणु
	हाल AFMT_QUERY:
		वापस(dmasound.soft.क्रमmat);
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
	Q40Init();

	वापस(क्रमmat);
पूर्ण

अटल पूर्णांक Q40SetVolume(पूर्णांक volume)
अणु
    वापस 0;
पूर्ण


/*** Machine definitions *****************************************************/

अटल SETTINGS def_hard = अणु
	.क्रमmat	= AFMT_U8,
	.stereo	= 0,
	.size	= 8,
	.speed	= 10000
पूर्ण ;

अटल SETTINGS def_soft = अणु
	.क्रमmat	= AFMT_U8,
	.stereo	= 0,
	.size	= 8,
	.speed	= 8000
पूर्ण ;

अटल MACHINE machQ40 = अणु
	.name		= "Q40",
	.name2		= "Q40",
	.owner		= THIS_MODULE,
	.dma_alloc	= Q40Alloc,
	.dma_मुक्त	= Q40Free,
	.irqinit	= Q40IrqInit,
#अगर_घोषित MODULE
	.irqcleanup	= Q40IrqCleanUp,
#पूर्ण_अगर /* MODULE */
	.init		= Q40Init,
	.silence	= Q40Silence,
	.setFormat	= Q40SetFormat,
	.setVolume	= Q40SetVolume,
	.play		= Q40Play,
 	.min_dsp_speed	= 10000,
	.version	= ((DMASOUND_Q40_REVISION<<8) | DMASOUND_Q40_EDITION),
	.hardware_afmts	= AFMT_U8, /* h'ware-supported क्रमmats *only* here */
	.capabilities	= DSP_CAP_BATCH  /* As per SNDCTL_DSP_GETCAPS */
पूर्ण;


/*** Config & Setup **********************************************************/


अटल पूर्णांक __init dmasound_q40_init(व्योम)
अणु
	अगर (MACH_IS_Q40) अणु
	    dmasound.mach = machQ40;
	    dmasound.mach.शेष_hard = def_hard ;
	    dmasound.mach.शेष_soft = def_soft ;
	    वापस dmasound_init();
	पूर्ण अन्यथा
	    वापस -ENODEV;
पूर्ण

अटल व्योम __निकास dmasound_q40_cleanup(व्योम)
अणु
	dmasound_deinit();
पूर्ण

module_init(dmasound_q40_init);
module_निकास(dmasound_q40_cleanup);

MODULE_DESCRIPTION("Q40/Q60 sound driver");
MODULE_LICENSE("GPL");
