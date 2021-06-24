<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* radio-cadet.c - A video4linux driver क्रम the ADS Cadet AM/FM Radio Card
 *
 * by Fred Gleason <fredg@wava.com>
 * Version 0.3.3
 *
 * (Loosely) based on code क्रम the Aztech radio card by
 *
 * Russell Kroll    (rkroll@exploits.org)
 * Quay Ly
 * Donald Song
 * Jason Lewis      (jlewis@twilight.vtc.vsc.edu)
 * Scott McGrath    (smcgrath@twilight.vtc.vsc.edu)
 * William McGrath  (wmcgrath@twilight.vtc.vsc.edu)
 *
 * History:
 * 2000-04-29	Russell Kroll <rkroll@exploits.org>
 *		Added ISAPnP detection क्रम Linux 2.3/2.4
 *
 * 2001-01-10	Russell Kroll <rkroll@exploits.org>
 *		Removed dead CONFIG_RADIO_CADET_PORT code
 *		PnP detection on load is now शेष (no args necessary)
 *
 * 2002-01-17	Adam Belay <ambx1@neo.rr.com>
 *		Updated to latest pnp code
 *
 * 2003-01-31	Alan Cox <alan@lxorguk.ukuu.org.uk>
 *		Cleaned up locking, delay code, general odds and ends
 *
 * 2006-07-30	Hans J. Koch <koch@hjk-az.de>
 *		Changed API to V4L2
 */

#समावेश <linux/module.h>	/* Modules			*/
#समावेश <linux/init.h>		/* Initdata			*/
#समावेश <linux/ioport.h>	/* request_region		*/
#समावेश <linux/delay.h>	/* udelay			*/
#समावेश <linux/videodev2.h>	/* V4L2 API defs		*/
#समावेश <linux/param.h>
#समावेश <linux/pnp.h>
#समावेश <linux/sched.h>
#समावेश <linux/पन.स>		/* outb, outb_p			*/
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>

MODULE_AUTHOR("Fred Gleason, Russell Kroll, Quay Lu, Donald Song, Jason Lewis, Scott McGrath, William McGrath");
MODULE_DESCRIPTION("A driver for the ADS Cadet AM/FM/RDS radio card.");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.3.4");

अटल पूर्णांक io = -1;		/* शेष to isapnp activation */
अटल पूर्णांक radio_nr = -1;

module_param(io, पूर्णांक, 0);
MODULE_PARM_DESC(io, "I/O address of Cadet card (0x330,0x332,0x334,0x336,0x338,0x33a,0x33c,0x33e)");
module_param(radio_nr, पूर्णांक, 0);

#घोषणा RDS_BUFFER 256
#घोषणा RDS_RX_FLAG 1
#घोषणा MBS_RX_FLAG 2

काष्ठा cadet अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device vdev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	पूर्णांक io;
	bool is_fm_band;
	u32 curfreq;
	पूर्णांक tunestat;
	पूर्णांक sigstrength;
	रुको_queue_head_t पढ़ो_queue;
	काष्ठा समयr_list पढ़ोसमयr;
	u8 rdsin, rdsout, rdsstat;
	अचिन्हित अक्षर rdsbuf[RDS_BUFFER];
	काष्ठा mutex lock;
	पूर्णांक पढ़ोing;
पूर्ण;

अटल काष्ठा cadet cadet_card;

/*
 * Signal Strength Threshold Values
 * The V4L API spec करोes not define any particular unit क्रम the संकेत
 * strength value.  These values are in microvolts of RF at the tuner's input.
 */
अटल u16 sigtable[2][4] = अणु
	अणु 1835, 2621,  4128, 65535 पूर्ण,
	अणु 2185, 4369, 13107, 65535 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	अणु
		.index = 0,
		.type = V4L2_TUNER_RADIO,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow = 8320,      /* 520 kHz */
		.rangehigh = 26400,    /* 1650 kHz */
		.modulation = V4L2_BAND_MODULATION_AM,
	पूर्ण, अणु
		.index = 1,
		.type = V4L2_TUNER_RADIO,
		.capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_RDS |
			V4L2_TUNER_CAP_RDS_BLOCK_IO | V4L2_TUNER_CAP_LOW |
			V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow = 1400000,   /* 87.5 MHz */
		.rangehigh = 1728000,  /* 108.0 MHz */
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
पूर्ण;


अटल पूर्णांक cadet_माला_लोtereo(काष्ठा cadet *dev)
अणु
	पूर्णांक ret = V4L2_TUNER_SUB_MONO;

	अगर (!dev->is_fm_band)	/* Only FM has stereo capability! */
		वापस V4L2_TUNER_SUB_MONO;

	outb(7, dev->io);          /* Select tuner control */
	अगर ((inb(dev->io + 1) & 0x40) == 0)
		ret = V4L2_TUNER_SUB_STEREO;
	वापस ret;
पूर्ण

अटल अचिन्हित cadet_gettune(काष्ठा cadet *dev)
अणु
	पूर्णांक curvol, i;
	अचिन्हित fअगरo = 0;

	/*
	 * Prepare क्रम पढ़ो
	 */

	outb(7, dev->io);       /* Select tuner control */
	curvol = inb(dev->io + 1); /* Save current volume/mute setting */
	outb(0x00, dev->io + 1);  /* Ensure WRITE-ENABLE is LOW */
	dev->tunestat = 0xffff;

	/*
	 * Read the shअगरt रेजिस्टर
	 */
	क्रम (i = 0; i < 25; i++) अणु
		fअगरo = (fअगरo << 1) | ((inb(dev->io + 1) >> 7) & 0x01);
		अगर (i < 24) अणु
			outb(0x01, dev->io + 1);
			dev->tunestat &= inb(dev->io + 1);
			outb(0x00, dev->io + 1);
		पूर्ण
	पूर्ण

	/*
	 * Restore volume/mute setting
	 */
	outb(curvol, dev->io + 1);
	वापस fअगरo;
पूर्ण

अटल अचिन्हित cadet_getfreq(काष्ठा cadet *dev)
अणु
	पूर्णांक i;
	अचिन्हित freq = 0, test, fअगरo = 0;

	/*
	 * Read current tuning
	 */
	fअगरo = cadet_gettune(dev);

	/*
	 * Convert to actual frequency
	 */
	अगर (!dev->is_fm_band)    /* AM */
		वापस ((fअगरo & 0x7fff) - 450) * 16;

	test = 12500;
	क्रम (i = 0; i < 14; i++) अणु
		अगर ((fअगरo & 0x01) != 0)
			freq += test;
		test = test << 1;
		fअगरo = fअगरo >> 1;
	पूर्ण
	freq -= 10700000;           /* IF frequency is 10.7 MHz */
	freq = (freq * 16) / 1000;   /* Make it 1/16 kHz */
	वापस freq;
पूर्ण

अटल व्योम cadet_settune(काष्ठा cadet *dev, अचिन्हित fअगरo)
अणु
	पूर्णांक i;
	अचिन्हित test;

	outb(7, dev->io);                /* Select tuner control */
	/*
	 * Write the shअगरt रेजिस्टर
	 */
	test = 0;
	test = (fअगरo >> 23) & 0x02;      /* Align data क्रम SDO */
	test |= 0x1c;                /* SDM=1, SWE=1, SEN=1, SCK=0 */
	outb(7, dev->io);                /* Select tuner control */
	outb(test, dev->io + 1);           /* Initialize क्रम ग_लिखो */
	क्रम (i = 0; i < 25; i++) अणु
		test |= 0x01;              /* Toggle SCK High */
		outb(test, dev->io + 1);
		test &= 0xfe;              /* Toggle SCK Low */
		outb(test, dev->io + 1);
		fअगरo = fअगरo << 1;            /* Prepare the next bit */
		test = 0x1c | ((fअगरo >> 23) & 0x02);
		outb(test, dev->io + 1);
	पूर्ण
पूर्ण

अटल व्योम cadet_setfreq(काष्ठा cadet *dev, अचिन्हित freq)
अणु
	अचिन्हित fअगरo;
	पूर्णांक i, j, test;
	पूर्णांक curvol;

	freq = clamp(freq, bands[dev->is_fm_band].rangelow,
			   bands[dev->is_fm_band].rangehigh);
	dev->curfreq = freq;
	/*
	 * Formulate a fअगरo command
	 */
	fअगरo = 0;
	अगर (dev->is_fm_band) अणु    /* FM */
		test = 102400;
		freq = freq / 16;       /* Make it kHz */
		freq += 10700;               /* IF is 10700 kHz */
		क्रम (i = 0; i < 14; i++) अणु
			fअगरo = fअगरo << 1;
			अगर (freq >= test) अणु
				fअगरo |= 0x01;
				freq -= test;
			पूर्ण
			test = test >> 1;
		पूर्ण
	पूर्ण अन्यथा अणु	/* AM */
		fअगरo = (freq / 16) + 450;	/* Make it kHz */
		fअगरo |= 0x100000;		/* Select AM Band */
	पूर्ण

	/*
	 * Save current volume/mute setting
	 */

	outb(7, dev->io);                /* Select tuner control */
	curvol = inb(dev->io + 1);

	/*
	 * Tune the card
	 */
	क्रम (j = 3; j > -1; j--) अणु
		cadet_settune(dev, fअगरo | (j << 16));

		outb(7, dev->io);         /* Select tuner control */
		outb(curvol, dev->io + 1);

		msleep(100);

		cadet_gettune(dev);
		अगर ((dev->tunestat & 0x40) == 0) अणु   /* Tuned */
			dev->sigstrength = sigtable[dev->is_fm_band][j];
			जाओ reset_rds;
		पूर्ण
	पूर्ण
	dev->sigstrength = 0;
reset_rds:
	outb(3, dev->io);
	outb(inb(dev->io + 1) & 0x7f, dev->io + 1);
पूर्ण

अटल bool cadet_has_rds_data(काष्ठा cadet *dev)
अणु
	bool result;

	mutex_lock(&dev->lock);
	result = dev->rdsin != dev->rdsout;
	mutex_unlock(&dev->lock);
	वापस result;
पूर्ण


अटल व्योम cadet_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा cadet *dev = from_समयr(dev, t, पढ़ोसमयr);

	/* Service the RDS fअगरo */
	अगर (mutex_trylock(&dev->lock)) अणु
		outb(0x3, dev->io);       /* Select RDS Decoder Control */
		अगर ((inb(dev->io + 1) & 0x20) != 0)
			pr_err("cadet: RDS fifo overflow\n");
		outb(0x80, dev->io);      /* Select RDS fअगरo */

		जबतक ((inb(dev->io) & 0x80) != 0) अणु
			dev->rdsbuf[dev->rdsin] = inb(dev->io + 1);
			अगर (dev->rdsin + 1 != dev->rdsout)
				dev->rdsin++;
		पूर्ण
		mutex_unlock(&dev->lock);
	पूर्ण

	/*
	 * Service pending पढ़ो
	 */
	अगर (cadet_has_rds_data(dev))
		wake_up_पूर्णांकerruptible(&dev->पढ़ो_queue);

	/*
	 * Clean up and निकास
	 */
	dev->पढ़ोसमयr.expires = jअगरfies + msecs_to_jअगरfies(50);
	add_समयr(&dev->पढ़ोसमयr);
पूर्ण

अटल व्योम cadet_start_rds(काष्ठा cadet *dev)
अणु
	dev->rdsstat = 1;
	outb(0x80, dev->io);        /* Select RDS fअगरo */
	समयr_setup(&dev->पढ़ोसमयr, cadet_handler, 0);
	dev->पढ़ोसमयr.expires = jअगरfies + msecs_to_jअगरfies(50);
	add_समयr(&dev->पढ़ोसमयr);
पूर्ण

अटल sमाप_प्रकार cadet_पढ़ो(काष्ठा file *file, अक्षर __user *data, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cadet *dev = video_drvdata(file);
	अचिन्हित अक्षर पढ़ोbuf[RDS_BUFFER];
	पूर्णांक i = 0;

	mutex_lock(&dev->lock);
	अगर (dev->rdsstat == 0)
		cadet_start_rds(dev);
	mutex_unlock(&dev->lock);

	अगर (!cadet_has_rds_data(dev) && (file->f_flags & O_NONBLOCK))
		वापस -EWOULDBLOCK;
	i = रुको_event_पूर्णांकerruptible(dev->पढ़ो_queue, cadet_has_rds_data(dev));
	अगर (i)
		वापस i;

	mutex_lock(&dev->lock);
	जबतक (i < count && dev->rdsin != dev->rdsout)
		पढ़ोbuf[i++] = dev->rdsbuf[dev->rdsout++];
	mutex_unlock(&dev->lock);

	अगर (i && copy_to_user(data, पढ़ोbuf, i))
		वापस -EFAULT;
	वापस i;
पूर्ण


अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_capability *v)
अणु
	strscpy(v->driver, "ADS Cadet", माप(v->driver));
	strscpy(v->card, "ADS Cadet", माप(v->card));
	strscpy(v->bus_info, "ISA:radio-cadet", माप(v->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *v)
अणु
	काष्ठा cadet *dev = video_drvdata(file);

	अगर (v->index)
		वापस -EINVAL;
	v->type = V4L2_TUNER_RADIO;
	strscpy(v->name, "Radio", माप(v->name));
	v->capability = bands[0].capability | bands[1].capability;
	v->rangelow = bands[0].rangelow;	   /* 520 kHz (start of AM band) */
	v->rangehigh = bands[1].rangehigh;    /* 108.0 MHz (end of FM band) */
	अगर (dev->is_fm_band) अणु
		v->rxsubchans = cadet_माला_लोtereo(dev);
		outb(3, dev->io);
		outb(inb(dev->io + 1) & 0x7f, dev->io + 1);
		mdelay(100);
		outb(3, dev->io);
		अगर (inb(dev->io + 1) & 0x80)
			v->rxsubchans |= V4L2_TUNER_SUB_RDS;
	पूर्ण अन्यथा अणु
		v->rangelow = 8320;      /* 520 kHz */
		v->rangehigh = 26400;    /* 1650 kHz */
		v->rxsubchans = V4L2_TUNER_SUB_MONO;
	पूर्ण
	v->audmode = V4L2_TUNER_MODE_STEREO;
	v->संकेत = dev->sigstrength; /* We might need to modअगरy scaling of this */
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *v)
अणु
	वापस v->index ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency_band *band)
अणु
	अगर (band->tuner)
		वापस -EINVAL;
	अगर (band->index >= ARRAY_SIZE(bands))
		वापस -EINVAL;
	*band = bands[band->index];
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cadet *dev = video_drvdata(file);

	अगर (f->tuner)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = dev->curfreq;
	वापस 0;
पूर्ण


अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cadet *dev = video_drvdata(file);

	अगर (f->tuner)
		वापस -EINVAL;
	dev->is_fm_band =
		f->frequency >= (bands[0].rangehigh + bands[1].rangelow) / 2;
	cadet_setfreq(dev, f->frequency);
	वापस 0;
पूर्ण

अटल पूर्णांक cadet_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा cadet *dev = container_of(ctrl->handler, काष्ठा cadet, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		outb(7, dev->io);                /* Select tuner control */
		अगर (ctrl->val)
			outb(0x00, dev->io + 1);
		अन्यथा
			outb(0x20, dev->io + 1);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cadet_खोलो(काष्ठा file *file)
अणु
	काष्ठा cadet *dev = video_drvdata(file);
	पूर्णांक err;

	mutex_lock(&dev->lock);
	err = v4l2_fh_खोलो(file);
	अगर (err)
		जाओ fail;
	अगर (v4l2_fh_is_singular_file(file))
		init_रुकोqueue_head(&dev->पढ़ो_queue);
fail:
	mutex_unlock(&dev->lock);
	वापस err;
पूर्ण

अटल पूर्णांक cadet_release(काष्ठा file *file)
अणु
	काष्ठा cadet *dev = video_drvdata(file);

	mutex_lock(&dev->lock);
	अगर (v4l2_fh_is_singular_file(file) && dev->rdsstat) अणु
		del_समयr_sync(&dev->पढ़ोसमयr);
		dev->rdsstat = 0;
	पूर्ण
	v4l2_fh_release(file);
	mutex_unlock(&dev->lock);
	वापस 0;
पूर्ण

अटल __poll_t cadet_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा cadet *dev = video_drvdata(file);
	__poll_t req_events = poll_requested_events(रुको);
	__poll_t res = v4l2_ctrl_poll(file, रुको);

	poll_रुको(file, &dev->पढ़ो_queue, रुको);
	अगर (dev->rdsstat == 0 && (req_events & (EPOLLIN | EPOLLRDNORM))) अणु
		mutex_lock(&dev->lock);
		अगर (dev->rdsstat == 0)
			cadet_start_rds(dev);
		mutex_unlock(&dev->lock);
	पूर्ण
	अगर (cadet_has_rds_data(dev))
		res |= EPOLLIN | EPOLLRDNORM;
	वापस res;
पूर्ण


अटल स्थिर काष्ठा v4l2_file_operations cadet_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= cadet_खोलो,
	.release	= cadet_release,
	.पढ़ो		= cadet_पढ़ो,
	.unlocked_ioctl	= video_ioctl2,
	.poll		= cadet_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops cadet_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_tuner     = vidioc_g_tuner,
	.vidioc_s_tuner     = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_क्रमागत_freq_bands = vidioc_क्रमागत_freq_bands,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops cadet_ctrl_ops = अणु
	.s_ctrl = cadet_s_ctrl,
पूर्ण;

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_device_id cadet_pnp_devices[] = अणु
	/* ADS Cadet AM/FM Radio Card */
	अणु.id = "MSM0c24", .driver_data = 0पूर्ण,
	अणु.id = ""पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, cadet_pnp_devices);

अटल पूर्णांक cadet_pnp_probe(काष्ठा pnp_dev *dev, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	अगर (!dev)
		वापस -ENODEV;
	/* only support one device */
	अगर (io > 0)
		वापस -EBUSY;

	अगर (!pnp_port_valid(dev, 0))
		वापस -ENODEV;

	io = pnp_port_start(dev, 0);

	prपूर्णांकk(KERN_INFO "radio-cadet: PnP reports device at %#x\n", io);

	वापस io;
पूर्ण

अटल काष्ठा pnp_driver cadet_pnp_driver = अणु
	.name		= "radio-cadet",
	.id_table	= cadet_pnp_devices,
	.probe		= cadet_pnp_probe,
	.हटाओ		= शून्य,
पूर्ण;

#अन्यथा
अटल काष्ठा pnp_driver cadet_pnp_driver;
#पूर्ण_अगर

अटल व्योम cadet_probe(काष्ठा cadet *dev)
अणु
	अटल पूर्णांक iovals[8] = अणु 0x330, 0x332, 0x334, 0x336, 0x338, 0x33a, 0x33c, 0x33e पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		dev->io = iovals[i];
		अगर (request_region(dev->io, 2, "cadet-probe")) अणु
			cadet_setfreq(dev, bands[1].rangelow);
			अगर (cadet_getfreq(dev) == bands[1].rangelow) अणु
				release_region(dev->io, 2);
				वापस;
			पूर्ण
			release_region(dev->io, 2);
		पूर्ण
	पूर्ण
	dev->io = -1;
पूर्ण

/*
 * io should only be set अगर the user has used something like
 * isapnp (the userspace program) to initialize this card क्रम us
 */

अटल पूर्णांक __init cadet_init(व्योम)
अणु
	काष्ठा cadet *dev = &cadet_card;
	काष्ठा v4l2_device *v4l2_dev = &dev->v4l2_dev;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक res = -ENODEV;

	strscpy(v4l2_dev->name, "cadet", माप(v4l2_dev->name));
	mutex_init(&dev->lock);

	/* If a probe was requested then probe ISAPnP first (safest) */
	अगर (io < 0)
		pnp_रेजिस्टर_driver(&cadet_pnp_driver);
	dev->io = io;

	/* If that fails then probe unsafely अगर probe is requested */
	अगर (dev->io < 0)
		cadet_probe(dev);

	/* Else we bail out */
	अगर (dev->io < 0) अणु
#अगर_घोषित MODULE
		v4l2_err(v4l2_dev, "you must set an I/O address with io=0x330, 0x332, 0x334,\n");
		v4l2_err(v4l2_dev, "0x336, 0x338, 0x33a, 0x33c or 0x33e\n");
#पूर्ण_अगर
		जाओ fail;
	पूर्ण
	अगर (!request_region(dev->io, 2, "cadet"))
		जाओ fail;

	res = v4l2_device_रेजिस्टर(शून्य, v4l2_dev);
	अगर (res < 0) अणु
		release_region(dev->io, 2);
		v4l2_err(v4l2_dev, "could not register v4l2_device\n");
		जाओ fail;
	पूर्ण

	hdl = &dev->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 2);
	v4l2_ctrl_new_std(hdl, &cadet_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4l2_dev->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		res = hdl->error;
		v4l2_err(v4l2_dev, "Could not register controls\n");
		जाओ err_hdl;
	पूर्ण

	dev->is_fm_band = true;
	dev->curfreq = bands[dev->is_fm_band].rangelow;
	cadet_setfreq(dev, dev->curfreq);
	strscpy(dev->vdev.name, v4l2_dev->name, माप(dev->vdev.name));
	dev->vdev.v4l2_dev = v4l2_dev;
	dev->vdev.fops = &cadet_fops;
	dev->vdev.ioctl_ops = &cadet_ioctl_ops;
	dev->vdev.release = video_device_release_empty;
	dev->vdev.lock = &dev->lock;
	dev->vdev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO |
				V4L2_CAP_READWRITE | V4L2_CAP_RDS_CAPTURE;
	video_set_drvdata(&dev->vdev, dev);

	res = video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_RADIO, radio_nr);
	अगर (res < 0)
		जाओ err_hdl;
	v4l2_info(v4l2_dev, "ADS Cadet Radio Card at 0x%x\n", dev->io);
	वापस 0;
err_hdl:
	v4l2_ctrl_handler_मुक्त(hdl);
	v4l2_device_unरेजिस्टर(v4l2_dev);
	release_region(dev->io, 2);
fail:
	pnp_unरेजिस्टर_driver(&cadet_pnp_driver);
	वापस res;
पूर्ण

अटल व्योम __निकास cadet_निकास(व्योम)
अणु
	काष्ठा cadet *dev = &cadet_card;

	video_unरेजिस्टर_device(&dev->vdev);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	outb(7, dev->io);	/* Mute */
	outb(0x00, dev->io + 1);
	release_region(dev->io, 2);
	pnp_unरेजिस्टर_driver(&cadet_pnp_driver);
पूर्ण

module_init(cadet_init);
module_निकास(cadet_निकास);

