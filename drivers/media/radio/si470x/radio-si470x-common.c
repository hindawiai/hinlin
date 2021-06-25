<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  drivers/media/radio/si470x/radio-si470x-common.c
 *
 *  Driver क्रम radios with Silicon Lअसल Si470x FM Radio Receivers
 *
 *  Copyright (c) 2009 Tobias Lorenz <tobias.lorenz@gmx.net>
 *  Copyright (c) 2012 Hans de Goede <hdegoede@redhat.com>
 */


/*
 * History:
 * 2008-01-12	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Version 1.0.0
 *		- First working version
 * 2008-01-13	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Version 1.0.1
 *		- Improved error handling, every function now वापसs त्रुटि_सं
 *		- Improved multi user access (start/mute/stop)
 *		- Channel करोesn't get lost anymore after start/mute/stop
 *		- RDS support added (polling mode via पूर्णांकerrupt EP 1)
 *		- marked शेष module parameters with *value*
 *		- चयनed from bit काष्ठाs to bit masks
 *		- header file cleaned and पूर्णांकegrated
 * 2008-01-14	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Version 1.0.2
 *		- hex values are now lower हाल
 *		- commented USB ID क्रम ADS/Tech moved on toकरो list
 *		- blacklisted si470x in hid-quirks.c
 *		- rds buffer handling functions पूर्णांकegrated पूर्णांकo *_work, *_पढ़ो
 *		- rds_command in si470x_poll exchanged against simple retval
 *		- check क्रम firmware version 15
 *		- code order and prototypes still reमुख्य the same
 *		- spacing and bottom of band codes reमुख्य the same
 * 2008-01-16	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Version 1.0.3
 *		- code reordered to aव्योम function prototypes
 *		- चयन/हाल शेषs are now more user-मित्रly
 *		- unअगरied comment style
 *		- applied all checkpatch.pl v1.12 suggestions
 *		  except the warning about the too दीर्घ lines with bit comments
 *		- नामd FMRADIO to RADIO to cut line length (checkpatch.pl)
 * 2008-01-22	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Version 1.0.4
 *		- aव्योम poss. locking when करोing copy_to_user which may sleep
 *		- RDS is स्वतःmatically activated on पढ़ो now
 *		- code cleaned of unnecessary rds_commands
 *		- USB Venकरोr/Product ID क्रम ADS/Tech FM Radio Receiver verअगरied
 *		  (thanks to Guillaume RAMOUSSE)
 * 2008-01-27	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Version 1.0.5
 *		- number of seek_retries changed to tune_समयout
 *		- fixed problem with incomplete tune operations by own buffers
 *		- optimization of variables and म_लिखो types
 *		- improved error logging
 * 2008-01-31	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Oliver Neukum <oliver@neukum.org>
 *		Version 1.0.6
 *		- fixed coverity checker warnings in *_usb_driver_disconnect
 *		- probe()/खोलो() race by correct ordering in probe()
 *		- DMA coherency rules by separate allocation of all buffers
 *		- use of endianness macros
 *		- abuse of spinlock, replaced by mutex
 *		- racy handling of समयr in disconnect,
 *		  replaced by delayed_work
 *		- racy पूर्णांकerruptible_sleep_on(),
 *		  replaced with रुको_event_पूर्णांकerruptible()
 *		- handle संकेतs in पढ़ो()
 * 2008-02-08	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Oliver Neukum <oliver@neukum.org>
 *		Version 1.0.7
 *		- usb स्वतःsuspend support
 *		- unplugging fixed
 * 2008-05-07	Tobias Lorenz <tobias.lorenz@gmx.net>
 *		Version 1.0.8
 *		- hardware frequency seek support
 *		- afc indication
 *		- more safety checks, let si470x_get_freq वापस त्रुटि_सं
 *		- vidioc behavior corrected according to v4l2 spec
 * 2008-10-20	Alexey Klimov <klimov.linux@gmail.com>
 *		- add support क्रम KWorld USB FM Radio FM700
 *		- blacklisted KWorld radio in hid-core.c and hid-ids.h
 * 2008-12-03	Mark Lord <mlord@pobox.com>
 *		- add support क्रम DealExtreme USB Radio
 * 2009-01-31	Bob Ross <pigiron@gmx.com>
 *		- correction of stereo detection/setting
 *		- correction of संकेत strength indicator scaling
 * 2009-01-31	Rick Bronson <rick@efn.org>
 *		Tobias Lorenz <tobias.lorenz@gmx.net>
 *		- add LED status output
 *		- get HW/SW version from scratchpad
 * 2009-06-16   Eकरोuard Lafargue <eकरोuard@lafargue.name>
 *		Version 1.0.10
 *		- add support क्रम पूर्णांकerrupt mode क्रम RDS endpoपूर्णांक,
 *                instead of polling.
 *                Improves RDS reception signअगरicantly
 */


/* kernel includes */
#समावेश "radio-si470x.h"

/**************************************************************************
 * Module Parameters
 **************************************************************************/

/* Spacing (kHz) */
/* 0: 200 kHz (USA, Australia) */
/* 1: 100 kHz (Europe, Japan) */
/* 2:  50 kHz */
अटल अचिन्हित लघु space = 2;
module_param(space, uलघु, 0444);
MODULE_PARM_DESC(space, "Spacing: 0=200kHz 1=100kHz *2=50kHz*");

/* De-emphasis */
/* 0: 75 us (USA) */
/* 1: 50 us (Europe, Australia, Japan) */
अटल अचिन्हित लघु de = 1;
module_param(de, uलघु, 0444);
MODULE_PARM_DESC(de, "De-emphasis: 0=75us *1=50us*");

/* Tune समयout */
अटल अचिन्हित पूर्णांक tune_समयout = 3000;
module_param(tune_समयout, uपूर्णांक, 0644);
MODULE_PARM_DESC(tune_समयout, "Tune timeout: *3000*");

/* Seek समयout */
अटल अचिन्हित पूर्णांक seek_समयout = 5000;
module_param(seek_समयout, uपूर्णांक, 0644);
MODULE_PARM_DESC(seek_समयout, "Seek timeout: *5000*");

अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 0,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			    V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_BLOCK_IO |
			    V4L2_TUNER_CAP_FREQ_BANDS |
			    V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			    V4L2_TUNER_CAP_HWSEEK_WRAP,
		.rangelow   =  87500 * 16,
		.rangehigh  = 108000 * 16,
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 1,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			    V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_BLOCK_IO |
			    V4L2_TUNER_CAP_FREQ_BANDS |
			    V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			    V4L2_TUNER_CAP_HWSEEK_WRAP,
		.rangelow   =  76000 * 16,
		.rangehigh  = 108000 * 16,
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 2,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			    V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_BLOCK_IO |
			    V4L2_TUNER_CAP_FREQ_BANDS |
			    V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			    V4L2_TUNER_CAP_HWSEEK_WRAP,
		.rangelow   =  76000 * 16,
		.rangehigh  =  90000 * 16,
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
पूर्ण;

/**************************************************************************
 * Generic Functions
 **************************************************************************/

/*
 * si470x_set_band - set the band
 */
अटल पूर्णांक si470x_set_band(काष्ठा si470x_device *radio, पूर्णांक band)
अणु
	अगर (radio->band == band)
		वापस 0;

	radio->band = band;
	radio->रेजिस्टरs[SYSCONFIG2] &= ~SYSCONFIG2_BAND;
	radio->रेजिस्टरs[SYSCONFIG2] |= radio->band << 6;
	वापस radio->set_रेजिस्टर(radio, SYSCONFIG2);
पूर्ण

/*
 * si470x_set_chan - set the channel
 */
अटल पूर्णांक si470x_set_chan(काष्ठा si470x_device *radio, अचिन्हित लघु chan)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ समय_left;
	bool समयd_out = false;

	retval = radio->get_रेजिस्टर(radio, POWERCFG);
	अगर (retval)
		वापस retval;

	अगर ((radio->रेजिस्टरs[POWERCFG] & (POWERCFG_ENABLE|POWERCFG_DMUTE))
		!= (POWERCFG_ENABLE|POWERCFG_DMUTE)) अणु
		वापस 0;
	पूर्ण

	/* start tuning */
	radio->रेजिस्टरs[CHANNEL] &= ~CHANNEL_CHAN;
	radio->रेजिस्टरs[CHANNEL] |= CHANNEL_TUNE | chan;
	retval = radio->set_रेजिस्टर(radio, CHANNEL);
	अगर (retval < 0)
		जाओ करोne;

	/* रुको till tune operation has completed */
	reinit_completion(&radio->completion);
	समय_left = रुको_क्रम_completion_समयout(&radio->completion,
						msecs_to_jअगरfies(tune_समयout));
	अगर (समय_left == 0)
		समयd_out = true;

	अगर ((radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_STC) == 0)
		dev_warn(&radio->videodev.dev, "tune does not complete\n");
	अगर (समयd_out)
		dev_warn(&radio->videodev.dev,
			"tune timed out after %u ms\n", tune_समयout);

	/* stop tuning */
	radio->रेजिस्टरs[CHANNEL] &= ~CHANNEL_TUNE;
	retval = radio->set_रेजिस्टर(radio, CHANNEL);

करोne:
	वापस retval;
पूर्ण

/*
 * si470x_get_step - get channel spacing
 */
अटल अचिन्हित पूर्णांक si470x_get_step(काष्ठा si470x_device *radio)
अणु
	/* Spacing (kHz) */
	चयन ((radio->रेजिस्टरs[SYSCONFIG2] & SYSCONFIG2_SPACE) >> 4) अणु
	/* 0: 200 kHz (USA, Australia) */
	हाल 0:
		वापस 200 * 16;
	/* 1: 100 kHz (Europe, Japan) */
	हाल 1:
		वापस 100 * 16;
	/* 2:  50 kHz */
	शेष:
		वापस 50 * 16;
	पूर्ण
पूर्ण


/*
 * si470x_get_freq - get the frequency
 */
अटल पूर्णांक si470x_get_freq(काष्ठा si470x_device *radio, अचिन्हित पूर्णांक *freq)
अणु
	पूर्णांक chan, retval;

	/* पढ़ो channel */
	retval = radio->get_रेजिस्टर(radio, READCHAN);
	chan = radio->रेजिस्टरs[READCHAN] & READCHAN_READCHAN;

	/* Frequency (MHz) = Spacing (kHz) x Channel + Bottom of Band (MHz) */
	*freq = chan * si470x_get_step(radio) + bands[radio->band].rangelow;

	वापस retval;
पूर्ण


/*
 * si470x_set_freq - set the frequency
 */
पूर्णांक si470x_set_freq(काष्ठा si470x_device *radio, अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित लघु chan;

	freq = clamp(freq, bands[radio->band].rangelow,
			   bands[radio->band].rangehigh);
	/* Chan = [ Freq (Mhz) - Bottom of Band (MHz) ] / Spacing (kHz) */
	chan = (freq - bands[radio->band].rangelow) / si470x_get_step(radio);

	वापस si470x_set_chan(radio, chan);
पूर्ण
EXPORT_SYMBOL_GPL(si470x_set_freq);


/*
 * si470x_set_seek - set seek
 */
अटल पूर्णांक si470x_set_seek(काष्ठा si470x_device *radio,
			   स्थिर काष्ठा v4l2_hw_freq_seek *seek)
अणु
	पूर्णांक band, retval;
	अचिन्हित पूर्णांक freq;
	bool समयd_out = false;
	अचिन्हित दीर्घ समय_left;

	/* set band */
	अगर (seek->rangelow || seek->rangehigh) अणु
		क्रम (band = 0; band < ARRAY_SIZE(bands); band++) अणु
			अगर (bands[band].rangelow  == seek->rangelow &&
			    bands[band].rangehigh == seek->rangehigh)
				अवरोध;
		पूर्ण
		अगर (band == ARRAY_SIZE(bands))
			वापस -EINVAL; /* No matching band found */
	पूर्ण अन्यथा
		band = 1; /* If nothing is specअगरied seek 76 - 108 Mhz */

	अगर (radio->band != band) अणु
		retval = si470x_get_freq(radio, &freq);
		अगर (retval)
			वापस retval;
		retval = si470x_set_band(radio, band);
		अगर (retval)
			वापस retval;
		retval = si470x_set_freq(radio, freq);
		अगर (retval)
			वापस retval;
	पूर्ण

	/* start seeking */
	radio->रेजिस्टरs[POWERCFG] |= POWERCFG_SEEK;
	अगर (seek->wrap_around)
		radio->रेजिस्टरs[POWERCFG] &= ~POWERCFG_SKMODE;
	अन्यथा
		radio->रेजिस्टरs[POWERCFG] |= POWERCFG_SKMODE;
	अगर (seek->seek_upward)
		radio->रेजिस्टरs[POWERCFG] |= POWERCFG_SEEKUP;
	अन्यथा
		radio->रेजिस्टरs[POWERCFG] &= ~POWERCFG_SEEKUP;
	retval = radio->set_रेजिस्टर(radio, POWERCFG);
	अगर (retval < 0)
		वापस retval;

	/* रुको till tune operation has completed */
	reinit_completion(&radio->completion);
	समय_left = रुको_क्रम_completion_समयout(&radio->completion,
						msecs_to_jअगरfies(seek_समयout));
	अगर (समय_left == 0)
		समयd_out = true;

	अगर ((radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_STC) == 0)
		dev_warn(&radio->videodev.dev, "seek does not complete\n");
	अगर (radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_SF)
		dev_warn(&radio->videodev.dev,
			"seek failed / band limit reached\n");

	/* stop seeking */
	radio->रेजिस्टरs[POWERCFG] &= ~POWERCFG_SEEK;
	retval = radio->set_रेजिस्टर(radio, POWERCFG);

	/* try again, अगर समयd out */
	अगर (retval == 0 && समयd_out)
		वापस -ENODATA;
	वापस retval;
पूर्ण


/*
 * si470x_start - चयन on radio
 */
पूर्णांक si470x_start(काष्ठा si470x_device *radio)
अणु
	पूर्णांक retval;

	/* घातercfg */
	radio->रेजिस्टरs[POWERCFG] =
		POWERCFG_DMUTE | POWERCFG_ENABLE | POWERCFG_RDSM;
	retval = radio->set_रेजिस्टर(radio, POWERCFG);
	अगर (retval < 0)
		जाओ करोne;

	/* sysconfig 1 */
	radio->रेजिस्टरs[SYSCONFIG1] |= SYSCONFIG1_RDSIEN | SYSCONFIG1_STCIEN |
					SYSCONFIG1_RDS;
	radio->रेजिस्टरs[SYSCONFIG1] &= ~SYSCONFIG1_GPIO2;
	radio->रेजिस्टरs[SYSCONFIG1] |= SYSCONFIG1_GPIO2_INT;
	अगर (de)
		radio->रेजिस्टरs[SYSCONFIG1] |= SYSCONFIG1_DE;
	retval = radio->set_रेजिस्टर(radio, SYSCONFIG1);
	अगर (retval < 0)
		जाओ करोne;

	/* sysconfig 2 */
	radio->रेजिस्टरs[SYSCONFIG2] =
		(0x1f  << 8) |				/* SEEKTH */
		((radio->band << 6) & SYSCONFIG2_BAND) |/* BAND */
		((space << 4) & SYSCONFIG2_SPACE) |	/* SPACE */
		15;					/* VOLUME (max) */
	retval = radio->set_रेजिस्टर(radio, SYSCONFIG2);
	अगर (retval < 0)
		जाओ करोne;

	/* reset last channel */
	retval = si470x_set_chan(radio,
		radio->रेजिस्टरs[CHANNEL] & CHANNEL_CHAN);

करोne:
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(si470x_start);


/*
 * si470x_stop - चयन off radio
 */
पूर्णांक si470x_stop(काष्ठा si470x_device *radio)
अणु
	पूर्णांक retval;

	/* sysconfig 1 */
	radio->रेजिस्टरs[SYSCONFIG1] &= ~SYSCONFIG1_RDS;
	retval = radio->set_रेजिस्टर(radio, SYSCONFIG1);
	अगर (retval < 0)
		जाओ करोne;

	/* घातercfg */
	radio->रेजिस्टरs[POWERCFG] &= ~POWERCFG_DMUTE;
	/* POWERCFG_ENABLE has to स्वतःmatically go low */
	radio->रेजिस्टरs[POWERCFG] |= POWERCFG_ENABLE |	POWERCFG_DISABLE;
	retval = radio->set_रेजिस्टर(radio, POWERCFG);

करोne:
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(si470x_stop);


/*
 * si470x_rds_on - चयन on rds reception
 */
अटल पूर्णांक si470x_rds_on(काष्ठा si470x_device *radio)
अणु
	पूर्णांक retval;

	/* sysconfig 1 */
	radio->रेजिस्टरs[SYSCONFIG1] |= SYSCONFIG1_RDS;
	retval = radio->set_रेजिस्टर(radio, SYSCONFIG1);
	अगर (retval < 0)
		radio->रेजिस्टरs[SYSCONFIG1] &= ~SYSCONFIG1_RDS;

	वापस retval;
पूर्ण



/**************************************************************************
 * File Operations Interface
 **************************************************************************/

/*
 * si470x_fops_पढ़ो - पढ़ो RDS data
 */
अटल sमाप_प्रकार si470x_fops_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक block_count = 0;

	/* चयन on rds reception */
	अगर ((radio->रेजिस्टरs[SYSCONFIG1] & SYSCONFIG1_RDS) == 0)
		si470x_rds_on(radio);

	/* block अगर no new data available */
	जबतक (radio->wr_index == radio->rd_index) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EWOULDBLOCK;
			जाओ करोne;
		पूर्ण
		अगर (रुको_event_पूर्णांकerruptible(radio->पढ़ो_queue,
			radio->wr_index != radio->rd_index) < 0) अणु
			retval = -EINTR;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* calculate block count from byte count */
	count /= 3;

	/* copy RDS block out of पूर्णांकernal buffer and to user buffer */
	जबतक (block_count < count) अणु
		अगर (radio->rd_index == radio->wr_index)
			अवरोध;

		/* always transfer rds complete blocks */
		अगर (copy_to_user(buf, &radio->buffer[radio->rd_index], 3))
			/* retval = -EFAULT; */
			अवरोध;

		/* increment and wrap पढ़ो poपूर्णांकer */
		radio->rd_index += 3;
		अगर (radio->rd_index >= radio->buf_size)
			radio->rd_index = 0;

		/* increment counters */
		block_count++;
		buf += 3;
		retval += 3;
	पूर्ण

करोne:
	वापस retval;
पूर्ण


/*
 * si470x_fops_poll - poll RDS data
 */
अटल __poll_t si470x_fops_poll(काष्ठा file *file,
		काष्ठा poll_table_काष्ठा *pts)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);
	__poll_t req_events = poll_requested_events(pts);
	__poll_t retval = v4l2_ctrl_poll(file, pts);

	अगर (req_events & (EPOLLIN | EPOLLRDNORM)) अणु
		/* चयन on rds reception */
		अगर ((radio->रेजिस्टरs[SYSCONFIG1] & SYSCONFIG1_RDS) == 0)
			si470x_rds_on(radio);

		poll_रुको(file, &radio->पढ़ो_queue, pts);

		अगर (radio->rd_index != radio->wr_index)
			retval |= EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस retval;
पूर्ण


अटल पूर्णांक si470x_fops_खोलो(काष्ठा file *file)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);

	वापस radio->fops_खोलो(file);
पूर्ण


/*
 * si470x_fops_release - file release
 */
अटल पूर्णांक si470x_fops_release(काष्ठा file *file)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);

	वापस radio->fops_release(file);
पूर्ण


/*
 * si470x_fops - file operations पूर्णांकerface
 */
अटल स्थिर काष्ठा v4l2_file_operations si470x_fops = अणु
	.owner			= THIS_MODULE,
	.पढ़ो			= si470x_fops_पढ़ो,
	.poll			= si470x_fops_poll,
	.unlocked_ioctl		= video_ioctl2,
	.खोलो			= si470x_fops_खोलो,
	.release		= si470x_fops_release,
पूर्ण;



/**************************************************************************
 * Video4Linux Interface
 **************************************************************************/


अटल पूर्णांक si470x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा si470x_device *radio =
		container_of(ctrl->handler, काष्ठा si470x_device, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_VOLUME:
		radio->रेजिस्टरs[SYSCONFIG2] &= ~SYSCONFIG2_VOLUME;
		radio->रेजिस्टरs[SYSCONFIG2] |= ctrl->val;
		वापस radio->set_रेजिस्टर(radio, SYSCONFIG2);
	हाल V4L2_CID_AUDIO_MUTE:
		अगर (ctrl->val)
			radio->रेजिस्टरs[POWERCFG] &= ~POWERCFG_DMUTE;
		अन्यथा
			radio->रेजिस्टरs[POWERCFG] |= POWERCFG_DMUTE;
		वापस radio->set_रेजिस्टर(radio, POWERCFG);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण


/*
 * si470x_vidioc_g_tuner - get tuner attributes
 */
अटल पूर्णांक si470x_vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);
	पूर्णांक retval = 0;

	अगर (tuner->index != 0)
		वापस -EINVAL;

	अगर (!radio->status_rssi_स्वतः_update) अणु
		retval = radio->get_रेजिस्टर(radio, STATUSRSSI);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	/* driver स्थिरants */
	strscpy(tuner->name, "FM", माप(tuner->name));
	tuner->type = V4L2_TUNER_RADIO;
	tuner->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			    V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_BLOCK_IO |
			    V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			    V4L2_TUNER_CAP_HWSEEK_WRAP;
	tuner->rangelow  =  76 * FREQ_MUL;
	tuner->rangehigh = 108 * FREQ_MUL;

	/* stereo indicator == stereo (instead of mono) */
	अगर ((radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_ST) == 0)
		tuner->rxsubchans = V4L2_TUNER_SUB_MONO;
	अन्यथा
		tuner->rxsubchans = V4L2_TUNER_SUB_STEREO;
	/* If there is a reliable method of detecting an RDS channel,
	   then this code should check क्रम that beक्रमe setting this
	   RDS subchannel. */
	tuner->rxsubchans |= V4L2_TUNER_SUB_RDS;

	/* mono/stereo selector */
	अगर ((radio->रेजिस्टरs[POWERCFG] & POWERCFG_MONO) == 0)
		tuner->audmode = V4L2_TUNER_MODE_STEREO;
	अन्यथा
		tuner->audmode = V4L2_TUNER_MODE_MONO;

	/* min is worst, max is best; संकेत:0..0xffff; rssi: 0..0xff */
	/* measured in units of dbतगV in 1 db increments (max at ~75 dbतगV) */
	tuner->संकेत = (radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_RSSI);
	/* the ideal factor is 0xffff/75 = 873,8 */
	tuner->संकेत = (tuner->संकेत * 873) + (8 * tuner->संकेत / 10);
	अगर (tuner->संकेत > 0xffff)
		tuner->संकेत = 0xffff;

	/* स्वतःmatic frequency control: -1: freq to low, 1 freq to high */
	/* AFCRL करोes only indicate that freq. dअगरfers, not अगर too low/high */
	tuner->afc = (radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_AFCRL) ? 1 : 0;

	वापस retval;
पूर्ण


/*
 * si470x_vidioc_s_tuner - set tuner attributes
 */
अटल पूर्णांक si470x_vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);

	अगर (tuner->index != 0)
		वापस -EINVAL;

	/* mono/stereo selector */
	चयन (tuner->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		radio->रेजिस्टरs[POWERCFG] |= POWERCFG_MONO;  /* क्रमce mono */
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
	शेष:
		radio->रेजिस्टरs[POWERCFG] &= ~POWERCFG_MONO; /* try stereo */
		अवरोध;
	पूर्ण

	वापस radio->set_रेजिस्टर(radio, POWERCFG);
पूर्ण


/*
 * si470x_vidioc_g_frequency - get tuner or modulator radio frequency
 */
अटल पूर्णांक si470x_vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);

	अगर (freq->tuner != 0)
		वापस -EINVAL;

	freq->type = V4L2_TUNER_RADIO;
	वापस si470x_get_freq(radio, &freq->frequency);
पूर्ण


/*
 * si470x_vidioc_s_frequency - set tuner or modulator radio frequency
 */
अटल पूर्णांक si470x_vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);
	पूर्णांक retval;

	अगर (freq->tuner != 0)
		वापस -EINVAL;

	अगर (freq->frequency < bands[radio->band].rangelow ||
	    freq->frequency > bands[radio->band].rangehigh) अणु
		/* Switch to band 1 which covers everything we support */
		retval = si470x_set_band(radio, 1);
		अगर (retval)
			वापस retval;
	पूर्ण
	वापस si470x_set_freq(radio, freq->frequency);
पूर्ण


/*
 * si470x_vidioc_s_hw_freq_seek - set hardware frequency seek
 */
अटल पूर्णांक si470x_vidioc_s_hw_freq_seek(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_hw_freq_seek *seek)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);

	अगर (seek->tuner != 0)
		वापस -EINVAL;

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EWOULDBLOCK;

	वापस si470x_set_seek(radio, seek);
पूर्ण

/*
 * si470x_vidioc_क्रमागत_freq_bands - क्रमागतerate supported bands
 */
अटल पूर्णांक si470x_vidioc_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_frequency_band *band)
अणु
	अगर (band->tuner != 0)
		वापस -EINVAL;
	अगर (band->index >= ARRAY_SIZE(bands))
		वापस -EINVAL;
	*band = bands[band->index];
	वापस 0;
पूर्ण

स्थिर काष्ठा v4l2_ctrl_ops si470x_ctrl_ops = अणु
	.s_ctrl = si470x_s_ctrl,
पूर्ण;
EXPORT_SYMBOL_GPL(si470x_ctrl_ops);

अटल पूर्णांक si470x_vidioc_querycap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_capability *capability)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);

	वापस radio->vidioc_querycap(file, priv, capability);
पूर्ण;

/*
 * si470x_ioctl_ops - video device ioctl operations
 */
अटल स्थिर काष्ठा v4l2_ioctl_ops si470x_ioctl_ops = अणु
	.vidioc_querycap	= si470x_vidioc_querycap,
	.vidioc_g_tuner		= si470x_vidioc_g_tuner,
	.vidioc_s_tuner		= si470x_vidioc_s_tuner,
	.vidioc_g_frequency	= si470x_vidioc_g_frequency,
	.vidioc_s_frequency	= si470x_vidioc_s_frequency,
	.vidioc_s_hw_freq_seek	= si470x_vidioc_s_hw_freq_seek,
	.vidioc_क्रमागत_freq_bands = si470x_vidioc_क्रमागत_freq_bands,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;


/*
 * si470x_viddev_ढाँचा - video device पूर्णांकerface
 */
स्थिर काष्ठा video_device si470x_viddev_ढाँचा = अणु
	.fops			= &si470x_fops,
	.name			= DRIVER_NAME,
	.release		= video_device_release_empty,
	.ioctl_ops		= &si470x_ioctl_ops,
पूर्ण;
EXPORT_SYMBOL_GPL(si470x_viddev_ढाँचा);

MODULE_LICENSE("GPL");
