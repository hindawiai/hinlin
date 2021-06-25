<शैली गुरु>
/*
 *  linux/sound/oss/dmasound/dmasound_core.c
 *
 *
 *  OSS/Free compatible Atari TT/Falcon and Amiga DMA sound driver क्रम
 *  Linux/m68k
 *  Extended to support Power Macपूर्णांकosh क्रम Linux/ppc by Paul Mackerras
 *
 *  (c) 1995 by Michael Schlueter & Michael Marte
 *
 *  Michael Schlueter (michael@duck.syd.de) did the basic काष्ठाure of the VFS
 *  पूर्णांकerface and the u-law to चिन्हित byte conversion.
 *
 *  Michael Marte (marte@inक्रमmatik.uni-muenchen.de) did the sound queue,
 *  /dev/mixer, /dev/sndstat and complemented the VFS पूर्णांकerface. He would like
 *  to thank:
 *    - Michael Schlueter क्रम initial ideas and करोcumentation on the MFP and
 *	the DMA sound hardware.
 *    - Therapy? क्रम their CD 'Troublegum' which really made me rock.
 *
 *  /dev/sndstat is based on code by Hannu Savolainen, the author of the
 *  VoxWare family of drivers.
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 *
 *  History:
 *
 *	1995/8/25	First release
 *
 *	1995/9/02	Roman Hodek:
 *			  - Fixed atari_stram_alloc() call, the समयr
 *			    programming and several race conditions
 *	1995/9/14	Roman Hodek:
 *			  - After some discussion with Michael Schlueter,
 *			    revised the पूर्णांकerrupt disabling
 *			  - Slightly speeded up U8->S8 translation by using
 *			    दीर्घ operations where possible
 *			  - Added 4:3 पूर्णांकerpolation क्रम /dev/audio
 *
 *	1995/9/20	Torsten Scherer:
 *			  - Fixed a bug in sq_ग_लिखो and changed /dev/audio
 *			    converting to play at 12517Hz instead of 6258Hz.
 *
 *	1995/9/23	Torsten Scherer:
 *			  - Changed sq_पूर्णांकerrupt() and sq_play() to pre-program
 *			    the DMA क्रम another frame जबतक there's still one
 *			    running. This allows the IRQ response to be
 *			    arbitrarily delayed and playing will still जारी.
 *
 *	1995/10/14	Guenther Kelleter, Torsten Scherer:
 *			  - Better support क्रम Falcon audio (the Falcon करोesn't
 *			    उठाओ an IRQ at the end of a frame, but at the
 *			    beginning instead!). uses 'if (codec_dma)' in lots
 *			    of places to simply चयन between Falcon and TT
 *			    code.
 *
 *	1995/11/06	Torsten Scherer:
 *			  - Started पूर्णांकroducing a hardware असलtraction scheme
 *			    (may perhaps also serve क्रम Amigas?)
 *			  - Can now play samples at almost all frequencies by
 *			    means of a more generalized expand routine
 *			  - Takes a good deal of care to cut data only at
 *			    sample sizes
 *			  - Buffer size is now a kernel runसमय option
 *			  - Implemented fsync() & several minor improvements
 *			Guenther Kelleter:
 *			  - Useful hपूर्णांकs and bug fixes
 *			  - Cross-checked it क्रम Falcons
 *
 *	1996/3/9	Geert Uytterhoeven:
 *			  - Support added क्रम Amiga, A-law, 16-bit little
 *			    endian.
 *			  - Unअगरication to drivers/sound/dmasound.c.
 *
 *	1996/4/6	Martin Mitchell:
 *			  - Updated to 1.3 kernel.
 *
 *	1996/6/13       Topi Kanerva:
 *			  - Fixed things that were broken (मुख्यly the amiga
 *			    14-bit routines)
 *			  - /dev/sndstat shows now the real hardware frequency
 *			  - The lowpass filter is disabled by शेष now
 *
 *	1996/9/25	Geert Uytterhoeven:
 *			  - Modularization
 *
 *	1998/6/10	Andreas Schwab:
 *			  - Converted to use sound_core
 *
 *	1999/12/28	Riअक्षरd Zidlicky:
 *			  - Added support क्रम Q40
 *
 *	2000/2/27	Geert Uytterhoeven:
 *			  - Clean up and split the code पूर्णांकo 4 parts:
 *			      o dmasound_core: machine-independent code
 *			      o dmasound_atari: Atari TT and Falcon support
 *			      o dmasound_awacs: Apple PowerMac support
 *			      o dmasound_paula: Amiga support
 *
 *	2000/3/25	Geert Uytterhoeven:
 *			  - Integration of dmasound_q40
 *			  - Small clean ups
 *
 *	2001/01/26 [1.0] Iain Sanकरोe
 *			  - make /dev/sndstat show revision & edition info.
 *			  - since dmasound.mach.sq_setup() can fail on pmac
 *			    its type has been changed to पूर्णांक and the वापसs
 *			    are checked.
 *		   [1.1]  - stop missing translations from being called.
 *	2001/02/08 [1.2]  - हटाओ unused translation tables & move machine-
 *			    specअगरic tables to low-level.
 *			  - वापस correct info. क्रम SNDCTL_DSP_GETFMTS.
 *		   [1.3]  - implement SNDCTL_DSP_GETCAPS fully.
 *		   [1.4]  - make /dev/sndstat text length usage deterministic.
 *			  - make /dev/sndstat call to low-level
 *			    dmasound.mach.state_info() pass max space to ll driver.
 *			  - tidy startup banners and output info.
 *		   [1.5]  - tidy up a little (हटाओd some unused #घोषणाs in
 *			    dmasound.h)
 *			  - fix up HAS_RECORD conditionalisation.
 *			  - add record code in places it is missing...
 *			  - change buf-sizes to bytes to allow < 1kb क्रम pmac
 *			    अगर user param entry is < 256 the value is taken to
 *			    be in kb > 256 is taken to be in bytes.
 *			  - make शेष buff/frag params conditional on
 *			    machine to allow smaller values क्रम pmac.
 *			  - made the ioctls, पढ़ो & ग_लिखो comply with the OSS
 *			    rules on setting params.
 *			  - added parsing of _setup() params क्रम record.
 *	2001/04/04 [1.6]  - fix bug where sample rates higher than maximum were
 *			    being reported as OK.
 *			  - fix खोलो() to वापस -EBUSY as per OSS करोc. when
 *			    audio is in use - this is independent of O_NOBLOCK.
 *			  - fix bug where SNDCTL_DSP_POST was blocking.
 */

 /* Record capability notes 30/01/2001:
  * At present these observations apply only to pmac LL driver (the only one
  * that can करो record, at present).  However, अगर other LL drivers क्रम machines
  * with record are added they may apply.
  *
  * The fragment parameters क्रम the record and play channels are separate.
  * However, अगर the driver is खोलोed O_RDWR there is no way (in the current OSS
  * API) to specअगरy their values independently क्रम the record and playback
  * channels.  Since the only common factor between the input & output is the
  * sample rate (on pmac) it should be possible to खोलो /dev/dspX O_WRONLY and
  * /dev/dspY O_RDONLY.  The input & output channels could then have dअगरferent
  * अक्षरacteristics (other than the first that sets sample rate claiming the
  * right to set it क्रम ever).  As it stands, the क्रमmat, channels, number of
  * bits & sample rate are assumed to be common.  In the future perhaps these
  * should be the responsibility of the LL driver - and then अगर a card really
  * करोes not share items between record & playback they can be specअगरied
  * separately.
*/

/* Thपढ़ो-safeness of shared_resources notes: 31/01/2001
 * If the user खोलोs O_RDWR and then splits record & play between two thपढ़ोs
 * both of which inherit the fd - and then starts changing things from both
 * - we will have dअगरficulty telling.
 *
 * It's bad application coding - but ...
 * TODO: think about how to sort this out... without bogging everything करोwn in
 * semaphores.
 *
 * Similarly, the OSS spec says "all changes to parameters must be between
 * खोलो() and the first पढ़ो() or ग_लिखो(). - and a bit later on (by
 * implication) "between SNDCTL_DSP_RESET and the first पढ़ो() or ग_लिखो() after
 * it".  If the app is multi-thपढ़ोed and this rule is broken between thपढ़ोs
 * we will have trouble spotting it - and the fault will be rather obscure :-(
 *
 * We will try and put out at least a kmsg अगर we see it happen... but I think
 * it will be quite hard to trap it with an -EXXX वापस... because we can't
 * see the fault until after the damage is करोne.
*/

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sound.h>
#समावेश <linux/init.h>
#समावेश <linux/soundcard.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <linux/uaccess.h>

#समावेश "dmasound.h"

#घोषणा DMASOUND_CORE_REVISION 1
#घोषणा DMASOUND_CORE_EDITION 6

    /*
     *  Declarations
     */

अटल DEFINE_MUTEX(dmasound_core_mutex);
पूर्णांक dmasound_catchRadius = 0;
module_param(dmasound_catchRadius, पूर्णांक, 0);

अटल अचिन्हित पूर्णांक numWriteBufs = DEFAULT_N_BUFFERS;
module_param(numWriteBufs, पूर्णांक, 0);
अटल अचिन्हित पूर्णांक ग_लिखोBufSize = DEFAULT_BUFF_SIZE ;	/* in bytes */
module_param(ग_लिखोBufSize, पूर्णांक, 0);

MODULE_LICENSE("GPL");

#अगर_घोषित MODULE
अटल पूर्णांक sq_unit = -1;
अटल पूर्णांक mixer_unit = -1;
अटल पूर्णांक state_unit = -1;
अटल पूर्णांक irq_installed;
#पूर्ण_अगर /* MODULE */

/* control over who can modअगरy resources shared between play/record */
अटल भ_शेषe_t shared_resource_owner;
अटल पूर्णांक shared_resources_initialised;

    /*
     *  Mid level stuff
     */

काष्ठा sound_settings dmasound = अणु
	.lock = __SPIN_LOCK_UNLOCKED(dmasound.lock)
पूर्ण;

अटल अंतरभूत व्योम sound_silence(व्योम)
अणु
	dmasound.mach.silence(); /* _MUST_ stop DMA */
पूर्ण

अटल अंतरभूत पूर्णांक sound_set_क्रमmat(पूर्णांक क्रमmat)
अणु
	वापस dmasound.mach.setFormat(क्रमmat);
पूर्ण


अटल पूर्णांक sound_set_speed(पूर्णांक speed)
अणु
	अगर (speed < 0)
		वापस dmasound.soft.speed;

	/* trap out-of-range speed settings.
	   at present we allow (arbitrarily) low rates - using soft
	   up-conversion - but we can't allow > max because there is
	   no soft करोwn-conversion.
	*/
	अगर (dmasound.mach.max_dsp_speed &&
	   (speed > dmasound.mach.max_dsp_speed))
		speed = dmasound.mach.max_dsp_speed ;

	dmasound.soft.speed = speed;

	अगर (dmasound.minDev == SND_DEV_DSP)
		dmasound.dsp.speed = dmasound.soft.speed;

	वापस dmasound.soft.speed;
पूर्ण

अटल पूर्णांक sound_set_stereo(पूर्णांक stereo)
अणु
	अगर (stereo < 0)
		वापस dmasound.soft.stereo;

	stereo = !!stereo;    /* should be 0 or 1 now */

	dmasound.soft.stereo = stereo;
	अगर (dmasound.minDev == SND_DEV_DSP)
		dmasound.dsp.stereo = stereo;

	वापस stereo;
पूर्ण

अटल sमाप_प्रकार sound_copy_translate(TRANS *trans, स्थिर u_अक्षर __user *userPtr,
				    माप_प्रकार userCount, u_अक्षर frame[],
				    sमाप_प्रकार *frameUsed, sमाप_प्रकार frameLeft)
अणु
	sमाप_प्रकार (*ct_func)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);

	चयन (dmasound.soft.क्रमmat) अणु
	    हाल AFMT_MU_LAW:
		ct_func = trans->ct_ulaw;
		अवरोध;
	    हाल AFMT_A_LAW:
		ct_func = trans->ct_alaw;
		अवरोध;
	    हाल AFMT_S8:
		ct_func = trans->ct_s8;
		अवरोध;
	    हाल AFMT_U8:
		ct_func = trans->ct_u8;
		अवरोध;
	    हाल AFMT_S16_BE:
		ct_func = trans->ct_s16be;
		अवरोध;
	    हाल AFMT_U16_BE:
		ct_func = trans->ct_u16be;
		अवरोध;
	    हाल AFMT_S16_LE:
		ct_func = trans->ct_s16le;
		अवरोध;
	    हाल AFMT_U16_LE:
		ct_func = trans->ct_u16le;
		अवरोध;
	    शेष:
		वापस 0;
	पूर्ण
	/* अगर the user has requested a non-existent translation करोn't try
	   to call it but just वापस 0 bytes moved
	*/
	अगर (ct_func)
		वापस ct_func(userPtr, userCount, frame, frameUsed, frameLeft);
	वापस 0;
पूर्ण

    /*
     *  /dev/mixer असलtraction
     */

अटल काष्ठा अणु
    पूर्णांक busy;
    पूर्णांक modअगरy_counter;
पूर्ण mixer;

अटल पूर्णांक mixer_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&dmasound_core_mutex);
	अगर (!try_module_get(dmasound.mach.owner)) अणु
		mutex_unlock(&dmasound_core_mutex);
		वापस -ENODEV;
	पूर्ण
	mixer.busy = 1;
	mutex_unlock(&dmasound_core_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mixer_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&dmasound_core_mutex);
	mixer.busy = 0;
	module_put(dmasound.mach.owner);
	mutex_unlock(&dmasound_core_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mixer_ioctl(काष्ठा file *file, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	अगर (_SIOC_सूची(cmd) & _SIOC_WRITE)
	    mixer.modअगरy_counter++;
	चयन (cmd) अणु
	    हाल OSS_GETVERSION:
		वापस IOCTL_OUT(arg, SOUND_VERSION);
	    हाल SOUND_MIXER_INFO:
		अणु
		    mixer_info info;
		    स_रखो(&info, 0, माप(info));
		    strscpy(info.id, dmasound.mach.name2, माप(info.id));
		    strscpy(info.name, dmasound.mach.name2, माप(info.name));
		    info.modअगरy_counter = mixer.modअगरy_counter;
		    अगर (copy_to_user((व्योम __user *)arg, &info, माप(info)))
			    वापस -EFAULT;
		    वापस 0;
		पूर्ण
	पूर्ण
	अगर (dmasound.mach.mixer_ioctl)
	    वापस dmasound.mach.mixer_ioctl(cmd, arg);
	वापस -EINVAL;
पूर्ण

अटल दीर्घ mixer_unlocked_ioctl(काष्ठा file *file, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&dmasound_core_mutex);
	ret = mixer_ioctl(file, cmd, arg);
	mutex_unlock(&dmasound_core_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations mixer_fops =
अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.unlocked_ioctl	= mixer_unlocked_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= mixer_खोलो,
	.release	= mixer_release,
पूर्ण;

अटल व्योम mixer_init(व्योम)
अणु
#अगर_अघोषित MODULE
	पूर्णांक mixer_unit;
#पूर्ण_अगर
	mixer_unit = रेजिस्टर_sound_mixer(&mixer_fops, -1);
	अगर (mixer_unit < 0)
		वापस;

	mixer.busy = 0;
	dmasound.treble = 0;
	dmasound.bass = 0;
	अगर (dmasound.mach.mixer_init)
	    dmasound.mach.mixer_init();
पूर्ण


    /*
     *  Sound queue stuff, the heart of the driver
     */

काष्ठा sound_queue dmasound_ग_लिखो_sq;
अटल व्योम sq_reset_output(व्योम) ;

अटल पूर्णांक sq_allocate_buffers(काष्ठा sound_queue *sq, पूर्णांक num, पूर्णांक size)
अणु
	पूर्णांक i;

	अगर (sq->buffers)
		वापस 0;
	sq->numBufs = num;
	sq->bufSize = size;
	sq->buffers = kदो_स्मृति_array (num, माप(अक्षर *), GFP_KERNEL);
	अगर (!sq->buffers)
		वापस -ENOMEM;
	क्रम (i = 0; i < num; i++) अणु
		sq->buffers[i] = dmasound.mach.dma_alloc(size, GFP_KERNEL);
		अगर (!sq->buffers[i]) अणु
			जबतक (i--)
				dmasound.mach.dma_मुक्त(sq->buffers[i], size);
			kमुक्त(sq->buffers);
			sq->buffers = शून्य;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sq_release_buffers(काष्ठा sound_queue *sq)
अणु
	पूर्णांक i;

	अगर (sq->buffers) अणु
		क्रम (i = 0; i < sq->numBufs; i++)
			dmasound.mach.dma_मुक्त(sq->buffers[i], sq->bufSize);
		kमुक्त(sq->buffers);
		sq->buffers = शून्य;
	पूर्ण
पूर्ण


अटल पूर्णांक sq_setup(काष्ठा sound_queue *sq)
अणु
	पूर्णांक (*setup_func)(व्योम) = शून्य;
	पूर्णांक hard_frame ;

	अगर (sq->locked) अणु /* are we alपढ़ोy set? - and not changeable */
#अगर_घोषित DEBUG_DMASOUND
prपूर्णांकk("dmasound_core: tried to sq_setup a locked queue\n") ;
#पूर्ण_अगर
		वापस -EINVAL ;
	पूर्ण
	sq->locked = 1 ; /* करोn't think we have a race prob. here _check_ */

	/* make sure that the parameters are set up
	   This should have been करोne alपढ़ोy...
	*/

	dmasound.mach.init();

	/* OK.  If the user has set fragment parameters explicitly, then we
	   should leave them alone... as दीर्घ as they are valid.
	   Invalid user fragment params can occur अगर we allow the whole buffer
	   to be used when the user requests the fragments sizes (with no soft
	   x-lation) and then the user subsequently sets a soft x-lation that
	   requires increased पूर्णांकernal buffering.

	   Othwerwise (अगर the user did not set them) OSS says that we should
	   select frag params on the basis of 0.5 s output & 0.1 s input
	   latency. (TODO.  For now we will copy in the शेषs.)
	*/

	अगर (sq->user_frags <= 0) अणु
		sq->max_count = sq->numBufs ;
		sq->max_active = sq->numBufs ;
		sq->block_size = sq->bufSize;
		/* set up the user info */
		sq->user_frags = sq->numBufs ;
		sq->user_frag_size = sq->bufSize ;
		sq->user_frag_size *=
			(dmasound.soft.size * (dmasound.soft.stereo+1) ) ;
		sq->user_frag_size /=
			(dmasound.hard.size * (dmasound.hard.stereo+1) ) ;
	पूर्ण अन्यथा अणु
		/* work out requested block size */
		sq->block_size = sq->user_frag_size ;
		sq->block_size *=
			(dmasound.hard.size * (dmasound.hard.stereo+1) ) ;
		sq->block_size /=
			(dmasound.soft.size * (dmasound.soft.stereo+1) ) ;
		/* the user wants to ग_लिखो frag-size chunks */
		sq->block_size *= dmasound.hard.speed ;
		sq->block_size /= dmasound.soft.speed ;
		/* this only works क्रम size values which are घातers of 2 */
		hard_frame =
			(dmasound.hard.size * (dmasound.hard.stereo+1))/8 ;
		sq->block_size +=  (hard_frame - 1) ;
		sq->block_size &= ~(hard_frame - 1) ; /* make sure we are aligned */
		/* let's just check क्रम obvious mistakes */
		अगर ( sq->block_size <= 0 || sq->block_size > sq->bufSize) अणु
#अगर_घोषित DEBUG_DMASOUND
prपूर्णांकk("dmasound_core: invalid frag size (user set %d)\n", sq->user_frag_size) ;
#पूर्ण_अगर
			sq->block_size = sq->bufSize ;
		पूर्ण
		अगर ( sq->user_frags <= sq->numBufs ) अणु
			sq->max_count = sq->user_frags ;
			/* अगर user has set max_active - then use it */
			sq->max_active = (sq->max_active <= sq->max_count) ?
				sq->max_active : sq->max_count ;
		पूर्ण अन्यथा अणु
#अगर_घोषित DEBUG_DMASOUND
prपूर्णांकk("dmasound_core: invalid frag count (user set %d)\n", sq->user_frags) ;
#पूर्ण_अगर
			sq->max_count =
			sq->max_active = sq->numBufs ;
		पूर्ण
	पूर्ण
	sq->front = sq->count = sq->rear_size = 0;
	sq->syncing = 0;
	sq->active = 0;

	अगर (sq == &ग_लिखो_sq) अणु
	    sq->rear = -1;
	    setup_func = dmasound.mach.ग_लिखो_sq_setup;
	पूर्ण
	अगर (setup_func)
	    वापस setup_func();
	वापस 0 ;
पूर्ण

अटल अंतरभूत व्योम sq_play(व्योम)
अणु
	dmasound.mach.play();
पूर्ण

अटल sमाप_प्रकार sq_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *src, माप_प्रकार uLeft,
			loff_t *ppos)
अणु
	sमाप_प्रकार uWritten = 0;
	u_अक्षर *dest;
	sमाप_प्रकार uUsed = 0, bUsed, bLeft;
	अचिन्हित दीर्घ flags ;

	/* ++TeSche: Is something like this necessary?
	 * Hey, that's an honest question! Or करोes any other part of the
	 * fileप्रणाली alपढ़ोy checks this situation? I really करोn't know.
	 */
	अगर (uLeft == 0)
		वापस 0;

	/* implement any changes we have made to the soft/hard params.
	   this is not satisfactory really, all we have करोne up to now is to
	   say what we would like - there hasn't been any real checking of capability
	*/

	अगर (shared_resources_initialised == 0) अणु
		dmasound.mach.init() ;
		shared_resources_initialised = 1 ;
	पूर्ण

	/* set up the sq अगर it is not alपढ़ोy करोne. This may seem a dumb place
	   to करो it - but it is what OSS requires.  It means that ग_लिखो() can
	   वापस memory allocation errors.  To aव्योम this possibility use the
	   GETBLKSIZE or GETOSPACE ioctls (after you've fiddled with all the
	   params you want to change) - these ioctls also क्रमce the setup.
	*/

	अगर (ग_लिखो_sq.locked == 0) अणु
		अगर ((uWritten = sq_setup(&ग_लिखो_sq)) < 0) वापस uWritten ;
		uWritten = 0 ;
	पूर्ण

/* FIXME: I think that this may be the wrong behaviour when we get strapped
	क्रम समय and the cpu is बंद to being (or actually) behind in sending data.
	- because we've lost the समय that the N samples, alपढ़ोy in the buffer,
	would have given us to get here with the next lot from the user.
*/
	/* The पूर्णांकerrupt करोesn't start to play the last, incomplete frame.
	 * Thus we can append to it without disabling the पूर्णांकerrupts! (Note
	 * also that ग_लिखो_sq.rear isn't affected by the पूर्णांकerrupt.)
	 */

	/* as of 1.6 this behaviour changes अगर SNDCTL_DSP_POST has been issued:
	   this will mimic the behaviour of syncing and allow the sq_play() to
	   queue a partial fragment.  Since sq_play() may/will be called from
	   the IRQ handler - at least on Pmac we have to deal with it.
	   The strategy - possibly not optimum - is to समाप्त _POST status अगर we
	   get here.  This seems, at least, reasonable - in the sense that POST
	   is supposed to indicate that we might not ग_लिखो beक्रमe the queue
	   is drained - and अगर we get here in समय then it करोes not apply.
	*/

	spin_lock_irqsave(&dmasound.lock, flags);
	ग_लिखो_sq.syncing &= ~2 ; /* take out POST status */
	spin_unlock_irqrestore(&dmasound.lock, flags);

	अगर (ग_लिखो_sq.count > 0 &&
	    (bLeft = ग_लिखो_sq.block_size-ग_लिखो_sq.rear_size) > 0) अणु
		dest = ग_लिखो_sq.buffers[ग_लिखो_sq.rear];
		bUsed = ग_लिखो_sq.rear_size;
		uUsed = sound_copy_translate(dmasound.trans_ग_लिखो, src, uLeft,
					     dest, &bUsed, bLeft);
		अगर (uUsed <= 0)
			वापस uUsed;
		src += uUsed;
		uWritten += uUsed;
		uLeft = (uUsed <= uLeft) ? (uLeft - uUsed) : 0 ; /* paranoia */
		ग_लिखो_sq.rear_size = bUsed;
	पूर्ण

	जबतक (uLeft) अणु
		DEFINE_WAIT(रुको);

		जबतक (ग_लिखो_sq.count >= ग_लिखो_sq.max_active) अणु
			prepare_to_रुको(&ग_लिखो_sq.action_queue, &रुको, TASK_INTERRUPTIBLE);
			sq_play();
			अगर (ग_लिखो_sq.non_blocking) अणु
				finish_रुको(&ग_लिखो_sq.action_queue, &रुको);
				वापस uWritten > 0 ? uWritten : -EAGAIN;
			पूर्ण
			अगर (ग_लिखो_sq.count < ग_लिखो_sq.max_active)
				अवरोध;

			schedule_समयout(HZ);
			अगर (संकेत_pending(current)) अणु
				finish_रुको(&ग_लिखो_sq.action_queue, &रुको);
				वापस uWritten > 0 ? uWritten : -EINTR;
			पूर्ण
		पूर्ण

		finish_रुको(&ग_लिखो_sq.action_queue, &रुको);

		/* Here, we can aव्योम disabling the पूर्णांकerrupt by first
		 * copying and translating the data, and then updating
		 * the ग_लिखो_sq variables. Until this is करोne, the पूर्णांकerrupt
		 * won't see the new frame and we can work on it
		 * undisturbed.
		 */

		dest = ग_लिखो_sq.buffers[(ग_लिखो_sq.rear+1) % ग_लिखो_sq.max_count];
		bUsed = 0;
		bLeft = ग_लिखो_sq.block_size;
		uUsed = sound_copy_translate(dmasound.trans_ग_लिखो, src, uLeft,
					     dest, &bUsed, bLeft);
		अगर (uUsed <= 0)
			अवरोध;
		src += uUsed;
		uWritten += uUsed;
		uLeft = (uUsed <= uLeft) ? (uLeft - uUsed) : 0 ; /* paranoia */
		अगर (bUsed) अणु
			ग_लिखो_sq.rear = (ग_लिखो_sq.rear+1) % ग_लिखो_sq.max_count;
			ग_लिखो_sq.rear_size = bUsed;
			ग_लिखो_sq.count++;
		पूर्ण
	पूर्ण /* uUsed may have been 0 */

	sq_play();

	वापस uUsed < 0? uUsed: uWritten;
पूर्ण

अटल __poll_t sq_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	__poll_t mask = 0;
	पूर्णांक retVal;
	
	अगर (ग_लिखो_sq.locked == 0) अणु
		अगर ((retVal = sq_setup(&ग_लिखो_sq)) < 0)
			वापस retVal;
		वापस 0;
	पूर्ण
	अगर (file->f_mode & FMODE_WRITE )
		poll_रुको(file, &ग_लिखो_sq.action_queue, रुको);
	अगर (file->f_mode & FMODE_WRITE)
		अगर (ग_लिखो_sq.count < ग_लिखो_sq.max_active || ग_लिखो_sq.block_size - ग_लिखो_sq.rear_size > 0)
			mask |= EPOLLOUT | EPOLLWRNORM;
	वापस mask;

पूर्ण

अटल अंतरभूत व्योम sq_init_रुकोqueue(काष्ठा sound_queue *sq)
अणु
	init_रुकोqueue_head(&sq->action_queue);
	init_रुकोqueue_head(&sq->खोलो_queue);
	init_रुकोqueue_head(&sq->sync_queue);
	sq->busy = 0;
पूर्ण

#अगर 0 /* blocking खोलो() */
अटल अंतरभूत व्योम sq_wake_up(काष्ठा sound_queue *sq, काष्ठा file *file,
			      भ_शेषe_t mode)
अणु
	अगर (file->f_mode & mode) अणु
		sq->busy = 0; /* CHECK: IS THIS OK??? */
		WAKE_UP(sq->खोलो_queue);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sq_खोलो2(काष्ठा sound_queue *sq, काष्ठा file *file, भ_शेषe_t mode,
		    पूर्णांक numbufs, पूर्णांक bufsize)
अणु
	पूर्णांक rc = 0;

	अगर (file->f_mode & mode) अणु
		अगर (sq->busy) अणु
#अगर 0 /* blocking खोलो() */
			rc = -EBUSY;
			अगर (file->f_flags & O_NONBLOCK)
				वापस rc;
			rc = -EINTR;
			अगर (रुको_event_पूर्णांकerruptible(sq->खोलो_queue, !sq->busy))
				वापस rc;
			rc = 0;
#अन्यथा
			/* OSS manual says we will वापस EBUSY regardless
			   of O_NOBLOCK.
			*/
			वापस -EBUSY ;
#पूर्ण_अगर
		पूर्ण
		sq->busy = 1; /* Let's play spot-the-race-condition */

		/* allocate the शेष number & size of buffers.
		   (i.e. specअगरied in _setup() or as module params)
		   can't be changed at the moment - but _could_ be perhaps
		   in the setfragments ioctl.
		*/
		अगर (( rc = sq_allocate_buffers(sq, numbufs, bufsize))) अणु
#अगर 0 /* blocking खोलो() */
			sq_wake_up(sq, file, mode);
#अन्यथा
			sq->busy = 0 ;
#पूर्ण_अगर
			वापस rc;
		पूर्ण

		sq->non_blocking = file->f_flags & O_NONBLOCK;
	पूर्ण
	वापस rc;
पूर्ण

#घोषणा ग_लिखो_sq_init_रुकोqueue()	sq_init_रुकोqueue(&ग_लिखो_sq)
#अगर 0 /* blocking खोलो() */
#घोषणा ग_लिखो_sq_wake_up(file)		sq_wake_up(&ग_लिखो_sq, file, FMODE_WRITE)
#पूर्ण_अगर
#घोषणा ग_लिखो_sq_release_buffers()	sq_release_buffers(&ग_लिखो_sq)
#घोषणा ग_लिखो_sq_खोलो(file)	\
	sq_खोलो2(&ग_लिखो_sq, file, FMODE_WRITE, numWriteBufs, ग_लिखोBufSize )

अटल पूर्णांक sq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc;

	mutex_lock(&dmasound_core_mutex);
	अगर (!try_module_get(dmasound.mach.owner)) अणु
		mutex_unlock(&dmasound_core_mutex);
		वापस -ENODEV;
	पूर्ण

	rc = ग_लिखो_sq_खोलो(file); /* checks the f_mode */
	अगर (rc)
		जाओ out;
	अगर (file->f_mode & FMODE_READ) अणु
		/* TODO: अगर O_RDWR, release any resources grabbed by ग_लिखो part */
		rc = -ENXIO ; /* I think this is what is required by खोलो(2) */
		जाओ out;
	पूर्ण

	अगर (dmasound.mach.sq_खोलो)
	    dmasound.mach.sq_खोलो(file->f_mode);

	/* CHECK whether this is sensible - in the हाल that dsp0 could be खोलोed
	  O_RDONLY and dsp1 could be खोलोed O_WRONLY
	*/

	dmasound.minDev = iminor(inode) & 0x0f;

	/* OK. - we should make some attempt at consistency. At least the H'ware
	   options should be set with a valid mode.  We will make it that the LL
	   driver must supply शेषs क्रम hard & soft params.
	*/

	अगर (shared_resource_owner == 0) अणु
		/* you can make this AFMT_U8/mono/8K अगर you want to mimic old
		   OSS behaviour - जबतक we still have soft translations ;-) */
		dmasound.soft = dmasound.mach.शेष_soft ;
		dmasound.dsp = dmasound.mach.शेष_soft ;
		dmasound.hard = dmasound.mach.शेष_hard ;
	पूर्ण

#अगर_अघोषित DMASOUND_STRICT_OSS_COMPLIANCE
	/* none of the current LL drivers can actually करो this "native" at the moment
	   OSS करोes not really require us to supply /dev/audio अगर we can't करो it.
	*/
	अगर (dmasound.minDev == SND_DEV_AUDIO) अणु
		sound_set_speed(8000);
		sound_set_stereo(0);
		sound_set_क्रमmat(AFMT_MU_LAW);
	पूर्ण
#पूर्ण_अगर
	mutex_unlock(&dmasound_core_mutex);
	वापस 0;
 out:
	module_put(dmasound.mach.owner);
	mutex_unlock(&dmasound_core_mutex);
	वापस rc;
पूर्ण

अटल व्योम sq_reset_output(व्योम)
अणु
	sound_silence(); /* this _must_ stop DMA, we might be about to lose the buffers */
	ग_लिखो_sq.active = 0;
	ग_लिखो_sq.count = 0;
	ग_लिखो_sq.rear_size = 0;
	/* ग_लिखो_sq.front = (ग_लिखो_sq.rear+1) % ग_लिखो_sq.max_count;*/
	ग_लिखो_sq.front = 0 ;
	ग_लिखो_sq.rear = -1 ; /* same as क्रम set-up */

	/* OK - we can unlock the parameters and fragment settings */
	ग_लिखो_sq.locked = 0 ;
	ग_लिखो_sq.user_frags = 0 ;
	ग_लिखो_sq.user_frag_size = 0 ;
पूर्ण

अटल व्योम sq_reset(व्योम)
अणु
	sq_reset_output() ;
	/* we could consider resetting the shared_resources_owner here... but I
	   think it is probably still rather non-obvious to application ग_लिखोr
	*/

	/* we release everything अन्यथा though */
	shared_resources_initialised = 0 ;
पूर्ण

अटल पूर्णांक sq_fsync(व्योम)
अणु
	पूर्णांक rc = 0;
	पूर्णांक समयout = 5;

	ग_लिखो_sq.syncing |= 1;
	sq_play();	/* there may be an incomplete frame रुकोing */

	जबतक (ग_लिखो_sq.active) अणु
		रुको_event_पूर्णांकerruptible_समयout(ग_लिखो_sq.sync_queue,
						 !ग_लिखो_sq.active, HZ);
		अगर (संकेत_pending(current)) अणु
			/* While रुकोing क्रम audio output to drain, an
			 * पूर्णांकerrupt occurred.  Stop audio output immediately
			 * and clear the queue. */
			sq_reset_output();
			rc = -EINTR;
			अवरोध;
		पूर्ण
		अगर (!--समयout) अणु
			prपूर्णांकk(KERN_WARNING "dmasound: Timeout draining output\n");
			sq_reset_output();
			rc = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	/* flag no sync regardless of whether we had a DSP_POST or not */
	ग_लिखो_sq.syncing = 0 ;
	वापस rc;
पूर्ण

अटल पूर्णांक sq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&dmasound_core_mutex);

	अगर (file->f_mode & FMODE_WRITE) अणु
		अगर (ग_लिखो_sq.busy)
			rc = sq_fsync();

		sq_reset_output() ; /* make sure dma is stopped and all is quiet */
		ग_लिखो_sq_release_buffers();
		ग_लिखो_sq.busy = 0;
	पूर्ण

	अगर (file->f_mode & shared_resource_owner) अणु /* it's us that has them */
		shared_resource_owner = 0 ;
		shared_resources_initialised = 0 ;
		dmasound.hard = dmasound.mach.शेष_hard ;
	पूर्ण

	module_put(dmasound.mach.owner);

#अगर 0 /* blocking खोलो() */
	/* Wake up a process रुकोing क्रम the queue being released.
	 * Note: There may be several processes रुकोing क्रम a call
	 * to खोलो() वापसing. */

	/* Iain: hmm I करोn't understand this next comment ... */
	/* There is probably a DOS atack here. They change the mode flag. */
	/* XXX add check here,*/
	पढ़ो_sq_wake_up(file); /* checks f_mode */
	ग_लिखो_sq_wake_up(file); /* checks f_mode */
#पूर्ण_अगर /* blocking खोलो() */

	mutex_unlock(&dmasound_core_mutex);

	वापस rc;
पूर्ण

/* here we see अगर we have a right to modअगरy क्रमmat, channels, size and so on
   अगर no-one अन्यथा has claimed it alपढ़ोy then we करो...

   TODO: We might change this to mask O_RDWR such that only one or the other channel
   is the owner - अगर we have problems.
*/

अटल पूर्णांक shared_resources_are_mine(भ_शेषe_t md)
अणु
	अगर (shared_resource_owner)
		वापस (shared_resource_owner & md) != 0;
	अन्यथा अणु
		shared_resource_owner = md ;
		वापस 1 ;
	पूर्ण
पूर्ण

/* अगर either queue is locked we must deny the right to change shared params
*/

अटल पूर्णांक queues_are_quiescent(व्योम)
अणु
	अगर (ग_लिखो_sq.locked)
		वापस 0 ;
	वापस 1 ;
पूर्ण

/* check and set a queue's fragments per user's wishes...
   we will check against the pre-defined literals and the actual sizes.
   This is a bit fraught - because soft translations can mess with our
   buffer requirements *after* this call - OSS says "call setfrags first"
*/

/* It is possible to replace all the -EINVAL वापसs with an override that
   just माला_दो the allowable value in.  This may be what many OSS apps require
*/

अटल पूर्णांक set_queue_frags(काष्ठा sound_queue *sq, पूर्णांक bufs, पूर्णांक size)
अणु
	अगर (sq->locked) अणु
#अगर_घोषित DEBUG_DMASOUND
prपूर्णांकk("dmasound_core: tried to set_queue_frags on a locked queue\n") ;
#पूर्ण_अगर
		वापस -EINVAL ;
	पूर्ण

	अगर ((size < MIN_FRAG_SIZE) || (size > MAX_FRAG_SIZE))
		वापस -EINVAL ;
	size = (1<<size) ; /* now in bytes */
	अगर (size > sq->bufSize)
		वापस -EINVAL ; /* this might still not work */

	अगर (bufs <= 0)
		वापस -EINVAL ;
	अगर (bufs > sq->numBufs) /* the user is allowed say "don't care" with 0x7fff */
		bufs = sq->numBufs ;

	/* there is, currently, no way to specअगरy max_active separately
	   from max_count.  This could be a LL driver issue - I guess
	   अगर there is a requirement क्रम these values to be dअगरferent then
	  we will have to pass that info. up to this level.
	*/
	sq->user_frags =
	sq->max_active = bufs ;
	sq->user_frag_size = size ;

	वापस 0 ;
पूर्ण

अटल पूर्णांक sq_ioctl(काष्ठा file *file, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक val, result;
	u_दीर्घ fmt;
	पूर्णांक data;
	पूर्णांक size, nbufs;
	audio_buf_info info;

	चयन (cmd) अणु
	हाल SNDCTL_DSP_RESET:
		sq_reset();
		वापस 0;
		अवरोध ;
	हाल SNDCTL_DSP_GETFMTS:
		fmt = dmasound.mach.hardware_afmts ; /* this is what OSS says.. */
		वापस IOCTL_OUT(arg, fmt);
		अवरोध ;
	हाल SNDCTL_DSP_GETBLKSIZE:
		/* this should tell the caller about bytes that the app can
		   पढ़ो/ग_लिखो - the app करोesn't care about our पूर्णांकernal buffers.
		   We क्रमce sq_setup() here as per OSS 1.1 (which should
		   compute the values necessary).
		   Since there is no mechanism to specअगरy पढ़ो/ग_लिखो separately, क्रम
		   fds खोलोed O_RDWR, the ग_लिखो_sq values will, arbitrarily, overग_लिखो
		   the पढ़ो_sq ones.
		*/
		size = 0 ;
		अगर (file->f_mode & FMODE_WRITE) अणु
			अगर ( !ग_लिखो_sq.locked )
				sq_setup(&ग_लिखो_sq) ;
			size = ग_लिखो_sq.user_frag_size ;
		पूर्ण
		वापस IOCTL_OUT(arg, size);
		अवरोध ;
	हाल SNDCTL_DSP_POST:
		/* all we are going to करो is to tell the LL that any
		   partial frags can be queued क्रम output.
		   The LL will have to clear this flag when last output
		   is queued.
		*/
		ग_लिखो_sq.syncing |= 0x2 ;
		sq_play() ;
		वापस 0 ;
	हाल SNDCTL_DSP_SYNC:
		/* This call, effectively, has the same behaviour as SNDCTL_DSP_RESET
		   except that it रुकोs क्रम output to finish beक्रमe resetting
		   everything - पढ़ो, however, is समाप्तed immediately.
		*/
		result = 0 ;
		अगर (file->f_mode & FMODE_WRITE) अणु
			result = sq_fsync();
			sq_reset_output() ;
		पूर्ण
		/* अगर we are the shared resource owner then release them */
		अगर (file->f_mode & shared_resource_owner)
			shared_resources_initialised = 0 ;
		वापस result ;
		अवरोध ;
	हाल SOUND_PCM_READ_RATE:
		वापस IOCTL_OUT(arg, dmasound.soft.speed);
	हाल SNDCTL_DSP_SPEED:
		/* changing this on the fly will have weird effects on the sound.
		   Where there are rate conversions implemented in soft क्रमm - it
		   will cause the _ctx_xxx() functions to be substituted.
		   However, there करोesn't appear to be any reason to dis-allow it from
		   a driver pov.
		*/
		अगर (shared_resources_are_mine(file->f_mode)) अणु
			IOCTL_IN(arg, data);
			data = sound_set_speed(data) ;
			shared_resources_initialised = 0 ;
			वापस IOCTL_OUT(arg, data);
		पूर्ण अन्यथा
			वापस -EINVAL ;
		अवरोध ;
	/* OSS says these next 4 actions are undefined when the device is
	   busy/active - we will just वापस -EINVAL.
	   To be allowed to change one - (a) you have to own the right
	    (b) the queue(s) must be quiescent
	*/
	हाल SNDCTL_DSP_STEREO:
		अगर (shared_resources_are_mine(file->f_mode) &&
		    queues_are_quiescent()) अणु
			IOCTL_IN(arg, data);
			shared_resources_initialised = 0 ;
			वापस IOCTL_OUT(arg, sound_set_stereo(data));
		पूर्ण अन्यथा
			वापस -EINVAL ;
		अवरोध ;
	हाल SOUND_PCM_WRITE_CHANNELS:
		अगर (shared_resources_are_mine(file->f_mode) &&
		    queues_are_quiescent()) अणु
			IOCTL_IN(arg, data);
			/* the user might ask क्रम 20 channels, we will वापस 1 or 2 */
			shared_resources_initialised = 0 ;
			वापस IOCTL_OUT(arg, sound_set_stereo(data-1)+1);
		पूर्ण अन्यथा
			वापस -EINVAL ;
		अवरोध ;
	हाल SNDCTL_DSP_SETFMT:
		अगर (shared_resources_are_mine(file->f_mode) &&
		    queues_are_quiescent()) अणु
		    	पूर्णांक क्रमmat;
			IOCTL_IN(arg, data);
			shared_resources_initialised = 0 ;
			क्रमmat = sound_set_क्रमmat(data);
			result = IOCTL_OUT(arg, क्रमmat);
			अगर (result < 0)
				वापस result;
			अगर (क्रमmat != data && data != AFMT_QUERY)
				वापस -EINVAL;
			वापस 0;
		पूर्ण अन्यथा
			वापस -EINVAL ;
	हाल SNDCTL_DSP_SUBDIVIDE:
		वापस -EINVAL ;
	हाल SNDCTL_DSP_SETFRAGMENT:
		/* we can करो this independently क्रम the two queues - with the
		   proviso that क्रम fds खोलोed O_RDWR we cannot separate the
		   actions and both queues will be set per the last call.
		   NOTE: this करोes *NOT* actually set the queue up - merely
		   रेजिस्टरs our पूर्णांकentions.
		*/
		IOCTL_IN(arg, data);
		result = 0 ;
		nbufs = (data >> 16) & 0x7fff ; /* 0x7fff is 'use maximum' */
		size = data & 0xffff;
		अगर (file->f_mode & FMODE_WRITE) अणु
			result = set_queue_frags(&ग_लिखो_sq, nbufs, size) ;
			अगर (result)
				वापस result ;
		पूर्ण
		/* NOTE: this वापस value is irrelevant - OSS specअगरically says that
		   the value is 'random' and that the user _must_ check the actual
		   frags values using SNDCTL_DSP_GETBLKSIZE or similar */
		वापस IOCTL_OUT(arg, data);
		अवरोध ;
	हाल SNDCTL_DSP_GETOSPACE:
		/*
		*/
		अगर (file->f_mode & FMODE_WRITE) अणु
			अगर ( !ग_लिखो_sq.locked )
				sq_setup(&ग_लिखो_sq) ;
			info.fragments = ग_लिखो_sq.max_active - ग_लिखो_sq.count;
			info.fragstotal = ग_लिखो_sq.max_active;
			info.fragsize = ग_लिखो_sq.user_frag_size;
			info.bytes = info.fragments * info.fragsize;
			अगर (copy_to_user((व्योम __user *)arg, &info, माप(info)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण अन्यथा
			वापस -EINVAL ;
		अवरोध ;
	हाल SNDCTL_DSP_GETCAPS:
		val = dmasound.mach.capabilities & 0xffffff00;
		वापस IOCTL_OUT(arg,val);

	शेष:
		वापस mixer_ioctl(file, cmd, arg);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल दीर्घ sq_unlocked_ioctl(काष्ठा file *file, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&dmasound_core_mutex);
	ret = sq_ioctl(file, cmd, arg);
	mutex_unlock(&dmasound_core_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations sq_fops =
अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= sq_ग_लिखो,
	.poll		= sq_poll,
	.unlocked_ioctl	= sq_unlocked_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= sq_खोलो,
	.release	= sq_release,
पूर्ण;

अटल पूर्णांक sq_init(व्योम)
अणु
	स्थिर काष्ठा file_operations *fops = &sq_fops;
#अगर_अघोषित MODULE
	पूर्णांक sq_unit;
#पूर्ण_अगर

	sq_unit = रेजिस्टर_sound_dsp(fops, -1);
	अगर (sq_unit < 0) अणु
		prपूर्णांकk(KERN_ERR "dmasound_core: couldn't register fops\n") ;
		वापस sq_unit ;
	पूर्ण

	ग_लिखो_sq_init_रुकोqueue();

	/* These parameters will be restored क्रम every clean खोलो()
	 * in the हाल of multiple खोलो()s (e.g. dsp0 & dsp1) they
	 * will be set so दीर्घ as the shared resources have no owner.
	 */

	अगर (shared_resource_owner == 0) अणु
		dmasound.soft = dmasound.mach.शेष_soft ;
		dmasound.hard = dmasound.mach.शेष_hard ;
		dmasound.dsp = dmasound.mach.शेष_soft ;
		shared_resources_initialised = 0 ;
	पूर्ण
	वापस 0 ;
पूर्ण


    /*
     *  /dev/sndstat
     */

/* we allow more space क्रम record-enabled because there are extra output lines.
   the number here must include the amount we are prepared to give to the low-level
   driver.
*/

#घोषणा STAT_BUFF_LEN 768

/* this is how much space we will allow the low-level driver to use
   in the stat buffer.  Currently, 2 * (80 अक्षरacter line + <NL>).
   We करो not police this (it is up to the ll driver to be honest).
*/

#घोषणा LOW_LEVEL_STAT_ALLOC 162

अटल काष्ठा अणु
    पूर्णांक busy;
    अक्षर buf[STAT_BUFF_LEN];	/* state.buf should not overflow! */
    पूर्णांक len, ptr;
पूर्ण state;

/* publish this function क्रम use by low-level code, अगर required */

अटल अक्षर *get_afmt_string(पूर्णांक afmt)
अणु
        चयन(afmt) अणु
            हाल AFMT_MU_LAW:
                वापस "mu-law";
                अवरोध;
            हाल AFMT_A_LAW:
                वापस "A-law";
                अवरोध;
            हाल AFMT_U8:
                वापस "unsigned 8 bit";
                अवरोध;
            हाल AFMT_S8:
                वापस "signed 8 bit";
                अवरोध;
            हाल AFMT_S16_BE:
                वापस "signed 16 bit BE";
                अवरोध;
            हाल AFMT_U16_BE:
                वापस "unsigned 16 bit BE";
                अवरोध;
            हाल AFMT_S16_LE:
                वापस "signed 16 bit LE";
                अवरोध;
            हाल AFMT_U16_LE:
                वापस "unsigned 16 bit LE";
                अवरोध;
	    हाल 0:
		वापस "format not set" ;
		अवरोध ;
            शेष:
                अवरोध ;
        पूर्ण
        वापस "ERROR: Unsupported AFMT_XXXX code" ;
पूर्ण

अटल पूर्णांक state_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अक्षर *buffer = state.buf;
	पूर्णांक len = 0;
	पूर्णांक ret;

	mutex_lock(&dmasound_core_mutex);
	ret = -EBUSY;
	अगर (state.busy)
		जाओ out;

	ret = -ENODEV;
	अगर (!try_module_get(dmasound.mach.owner))
		जाओ out;

	state.ptr = 0;
	state.busy = 1;

	len += प्र_लिखो(buffer+len, "%sDMA sound driver rev %03d :\n",
		dmasound.mach.name, (DMASOUND_CORE_REVISION<<4) +
		((dmasound.mach.version>>8) & 0x0f));
	len += प्र_लिखो(buffer+len,
		"Core driver edition %02d.%02d : %s driver edition %02d.%02d\n",
		DMASOUND_CORE_REVISION, DMASOUND_CORE_EDITION, dmasound.mach.name2,
		(dmasound.mach.version >> 8), (dmasound.mach.version & 0xff)) ;

	/* call the low-level module to fill in any stat info. that it has
	   अगर present.  Maximum buffer usage is specअगरied.
	*/

	अगर (dmasound.mach.state_info)
		len += dmasound.mach.state_info(buffer+len,
			(माप_प्रकार) LOW_LEVEL_STAT_ALLOC) ;

	/* make usage of the state buffer as deterministic as poss.
	   exceptional conditions could cause overrun - and this is flagged as
	   a kernel error.
	*/

	/* क्रमmats and settings */

	len += प्र_लिखो(buffer+len,"\t\t === Formats & settings ===\n") ;
	len += प्र_लिखो(buffer+len,"Parameter %20s%20s\n","soft","hard") ;
	len += प्र_लिखो(buffer+len,"Format   :%20s%20s\n",
		get_afmt_string(dmasound.soft.क्रमmat),
		get_afmt_string(dmasound.hard.क्रमmat));

	len += प्र_लिखो(buffer+len,"Samp Rate:%14d s/sec%14d s/sec\n",
		       dmasound.soft.speed, dmasound.hard.speed);

	len += प्र_लिखो(buffer+len,"Channels :%20s%20s\n",
		       dmasound.soft.stereo ? "stereo" : "mono",
		       dmasound.hard.stereo ? "stereo" : "mono" );

	/* sound queue status */

	len += प्र_लिखो(buffer+len,"\t\t === Sound Queue status ===\n");
	len += प्र_लिखो(buffer+len,"Allocated:%8s%6s\n","Buffers","Size") ;
	len += प्र_लिखो(buffer+len,"%9s:%8d%6d\n",
		"write", ग_लिखो_sq.numBufs, ग_लिखो_sq.bufSize) ;
	len += प्र_लिखो(buffer+len,
		"Current  : MaxFrg FragSiz MaxAct Frnt Rear "
		"Cnt RrSize A B S L  xruns\n") ;
	len += प्र_लिखो(buffer+len,"%9s:%7d%8d%7d%5d%5d%4d%7d%2d%2d%2d%2d%7d\n",
		"write", ग_लिखो_sq.max_count, ग_लिखो_sq.block_size,
		ग_लिखो_sq.max_active, ग_लिखो_sq.front, ग_लिखो_sq.rear,
		ग_लिखो_sq.count, ग_लिखो_sq.rear_size, ग_लिखो_sq.active,
		ग_लिखो_sq.busy, ग_लिखो_sq.syncing, ग_लिखो_sq.locked, ग_लिखो_sq.xruns) ;
#अगर_घोषित DEBUG_DMASOUND
prपूर्णांकk("dmasound: stat buffer used %d bytes\n", len) ;
#पूर्ण_अगर

	अगर (len >= STAT_BUFF_LEN)
		prपूर्णांकk(KERN_ERR "dmasound_core: stat buffer overflowed!\n");

	state.len = len;
	ret = 0;
out:
	mutex_unlock(&dmasound_core_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक state_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&dmasound_core_mutex);
	state.busy = 0;
	module_put(dmasound.mach.owner);
	mutex_unlock(&dmasound_core_mutex);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार state_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			  loff_t *ppos)
अणु
	पूर्णांक n = state.len - state.ptr;
	अगर (n > count)
		n = count;
	अगर (n <= 0)
		वापस 0;
	अगर (copy_to_user(buf, &state.buf[state.ptr], n))
		वापस -EFAULT;
	state.ptr += n;
	वापस n;
पूर्ण

अटल स्थिर काष्ठा file_operations state_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= state_पढ़ो,
	.खोलो		= state_खोलो,
	.release	= state_release,
पूर्ण;

अटल पूर्णांक state_init(व्योम)
अणु
#अगर_अघोषित MODULE
	पूर्णांक state_unit;
#पूर्ण_अगर
	state_unit = रेजिस्टर_sound_special(&state_fops, SND_DEV_STATUS);
	अगर (state_unit < 0)
		वापस state_unit ;
	state.busy = 0;
	वापस 0 ;
पूर्ण


    /*
     *  Config & Setup
     *
     *  This function is called by _one_ chipset-specअगरic driver
     */

पूर्णांक dmasound_init(व्योम)
अणु
	पूर्णांक res ;
#अगर_घोषित MODULE
	अगर (irq_installed)
		वापस -EBUSY;
#पूर्ण_अगर

	/* Set up sound queue, /dev/audio and /dev/dsp. */

	/* Set शेष settings. */
	अगर ((res = sq_init()) < 0)
		वापस res ;

	/* Set up /dev/sndstat. */
	अगर ((res = state_init()) < 0)
		वापस res ;

	/* Set up /dev/mixer. */
	mixer_init();

	अगर (!dmasound.mach.irqinit()) अणु
		prपूर्णांकk(KERN_ERR "DMA sound driver: Interrupt initialization failed\n");
		वापस -ENODEV;
	पूर्ण
#अगर_घोषित MODULE
	irq_installed = 1;
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "%s DMA sound driver rev %03d installed\n",
		dmasound.mach.name, (DMASOUND_CORE_REVISION<<4) +
		((dmasound.mach.version>>8) & 0x0f));
	prपूर्णांकk(KERN_INFO
		"Core driver edition %02d.%02d : %s driver edition %02d.%02d\n",
		DMASOUND_CORE_REVISION, DMASOUND_CORE_EDITION, dmasound.mach.name2,
		(dmasound.mach.version >> 8), (dmasound.mach.version & 0xff)) ;
	prपूर्णांकk(KERN_INFO "Write will use %4d fragments of %7d bytes as default\n",
		numWriteBufs, ग_लिखोBufSize) ;
	वापस 0;
पूर्ण

#अगर_घोषित MODULE

व्योम dmasound_deinit(व्योम)
अणु
	अगर (irq_installed) अणु
		sound_silence();
		dmasound.mach.irqcleanup();
		irq_installed = 0;
	पूर्ण

	ग_लिखो_sq_release_buffers();

	अगर (mixer_unit >= 0)
		unरेजिस्टर_sound_mixer(mixer_unit);
	अगर (state_unit >= 0)
		unरेजिस्टर_sound_special(state_unit);
	अगर (sq_unit >= 0)
		unरेजिस्टर_sound_dsp(sq_unit);
पूर्ण

#अन्यथा /* !MODULE */

अटल पूर्णांक dmasound_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[6], size;

	str = get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	/* check the bootstrap parameter क्रम "dmasound=" */

	/* FIXME: other than in the most naive of हालs there is no sense in these
	 *	  buffers being other than घातers of two.  This is not checked yet.
	 */

	चयन (पूर्णांकs[0]) अणु
	हाल 3:
		अगर ((पूर्णांकs[3] < 0) || (पूर्णांकs[3] > MAX_CATCH_RADIUS))
			prपूर्णांकk("dmasound_setup: invalid catch radius, using default = %d\n", catchRadius);
		अन्यथा
			catchRadius = पूर्णांकs[3];
		fallthrough;
	हाल 2:
		अगर (पूर्णांकs[1] < MIN_BUFFERS)
			prपूर्णांकk("dmasound_setup: invalid number of buffers, using default = %d\n", numWriteBufs);
		अन्यथा
			numWriteBufs = पूर्णांकs[1];
		fallthrough;
	हाल 1:
		अगर ((size = पूर्णांकs[2]) < 256) /* check क्रम small buffer specs */
			size <<= 10 ;
                अगर (size < MIN_बफ_मानE || size > MAX_बफ_मानE)
                        prपूर्णांकk("dmasound_setup: invalid write buffer size, using default = %d\n", ग_लिखोBufSize);
                अन्यथा
                        ग_लिखोBufSize = size;
	हाल 0:
		अवरोध;
	शेष:
		prपूर्णांकk("dmasound_setup: invalid number of arguments\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

__setup("dmasound=", dmasound_setup);

#पूर्ण_अगर /* !MODULE */

    /*
     *  Conversion tables
     */

#अगर_घोषित HAS_8BIT_TABLES
/* 8 bit mu-law */

अक्षर dmasound_ulaw2dma8[] = अणु
	-126,	-122,	-118,	-114,	-110,	-106,	-102,	-98,
	-94,	-90,	-86,	-82,	-78,	-74,	-70,	-66,
	-63,	-61,	-59,	-57,	-55,	-53,	-51,	-49,
	-47,	-45,	-43,	-41,	-39,	-37,	-35,	-33,
	-31,	-30,	-29,	-28,	-27,	-26,	-25,	-24,
	-23,	-22,	-21,	-20,	-19,	-18,	-17,	-16,
	-16,	-15,	-15,	-14,	-14,	-13,	-13,	-12,
	-12,	-11,	-11,	-10,	-10,	-9,	-9,	-8,
	-8,	-8,	-7,	-7,	-7,	-7,	-6,	-6,
	-6,	-6,	-5,	-5,	-5,	-5,	-4,	-4,
	-4,	-4,	-4,	-4,	-3,	-3,	-3,	-3,
	-3,	-3,	-3,	-3,	-2,	-2,	-2,	-2,
	-2,	-2,	-2,	-2,	-2,	-2,	-2,	-2,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	0,
	125,	121,	117,	113,	109,	105,	101,	97,
	93,	89,	85,	81,	77,	73,	69,	65,
	62,	60,	58,	56,	54,	52,	50,	48,
	46,	44,	42,	40,	38,	36,	34,	32,
	30,	29,	28,	27,	26,	25,	24,	23,
	22,	21,	20,	19,	18,	17,	16,	15,
	15,	14,	14,	13,	13,	12,	12,	11,
	11,	10,	10,	9,	9,	8,	8,	7,
	7,	7,	6,	6,	6,	6,	5,	5,
	5,	5,	4,	4,	4,	4,	3,	3,
	3,	3,	3,	3,	2,	2,	2,	2,
	2,	2,	2,	2,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0
पूर्ण;

/* 8 bit A-law */

अक्षर dmasound_alaw2dma8[] = अणु
	-22,	-21,	-24,	-23,	-18,	-17,	-20,	-19,
	-30,	-29,	-32,	-31,	-26,	-25,	-28,	-27,
	-11,	-11,	-12,	-12,	-9,	-9,	-10,	-10,
	-15,	-15,	-16,	-16,	-13,	-13,	-14,	-14,
	-86,	-82,	-94,	-90,	-70,	-66,	-78,	-74,
	-118,	-114,	-126,	-122,	-102,	-98,	-110,	-106,
	-43,	-41,	-47,	-45,	-35,	-33,	-39,	-37,
	-59,	-57,	-63,	-61,	-51,	-49,	-55,	-53,
	-2,	-2,	-2,	-2,	-2,	-2,	-2,	-2,
	-2,	-2,	-2,	-2,	-2,	-2,	-2,	-2,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-6,	-6,	-6,	-6,	-5,	-5,	-5,	-5,
	-8,	-8,	-8,	-8,	-7,	-7,	-7,	-7,
	-3,	-3,	-3,	-3,	-3,	-3,	-3,	-3,
	-4,	-4,	-4,	-4,	-4,	-4,	-4,	-4,
	21,	20,	23,	22,	17,	16,	19,	18,
	29,	28,	31,	30,	25,	24,	27,	26,
	10,	10,	11,	11,	8,	8,	9,	9,
	14,	14,	15,	15,	12,	12,	13,	13,
	86,	82,	94,	90,	70,	66,	78,	74,
	118,	114,	126,	122,	102,	98,	110,	106,
	43,	41,	47,	45,	35,	33,	39,	37,
	59,	57,	63,	61,	51,	49,	55,	53,
	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	5,	5,	5,	5,	4,	4,	4,	4,
	7,	7,	7,	7,	6,	6,	6,	6,
	2,	2,	2,	2,	2,	2,	2,	2,
	3,	3,	3,	3,	3,	3,	3,	3
पूर्ण;
#पूर्ण_अगर /* HAS_8BIT_TABLES */

    /*
     *  Visible symbols क्रम modules
     */

EXPORT_SYMBOL(dmasound);
EXPORT_SYMBOL(dmasound_init);
#अगर_घोषित MODULE
EXPORT_SYMBOL(dmasound_deinit);
#पूर्ण_अगर
EXPORT_SYMBOL(dmasound_ग_लिखो_sq);
EXPORT_SYMBOL(dmasound_catchRadius);
#अगर_घोषित HAS_8BIT_TABLES
EXPORT_SYMBOL(dmasound_ulaw2dma8);
EXPORT_SYMBOL(dmasound_alaw2dma8);
#पूर्ण_अगर
