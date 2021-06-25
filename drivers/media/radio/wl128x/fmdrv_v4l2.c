<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  FM Driver क्रम Connectivity chip of Texas Instruments.
 *  This file provides पूर्णांकerfaces to V4L2 subप्रणाली.
 *
 *  This module रेजिस्टरs with V4L2 subप्रणाली as Radio
 *  data प्रणाली पूर्णांकerface (/dev/radio). During the registration,
 *  it will expose two set of function poपूर्णांकers.
 *
 *    1) File operation related API (खोलो, बंद, पढ़ो, ग_लिखो, poll...etc).
 *    2) Set of V4L2 IOCTL complaपूर्णांक API.
 *
 *  Copyright (C) 2011 Texas Instruments
 *  Author: Raja Mani <raja_mani@ti.com>
 *  Author: Manjunatha Halli <manjunatha_halli@ti.com>
 */

#समावेश <linux/export.h>

#समावेश "fmdrv.h"
#समावेश "fmdrv_v4l2.h"
#समावेश "fmdrv_common.h"
#समावेश "fmdrv_rx.h"
#समावेश "fmdrv_tx.h"

अटल काष्ठा video_device gradio_dev;
अटल u8 radio_disconnected;

/* -- V4L2 RADIO (/dev/radioX) device file operation पूर्णांकerfaces --- */

/* Read RX RDS data */
अटल sमाप_प्रकार fm_v4l2_fops_पढ़ो(काष्ठा file *file, अक्षर __user * buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	u8 rds_mode;
	पूर्णांक ret;
	काष्ठा fmdev *fmdev;

	fmdev = video_drvdata(file);

	अगर (!radio_disconnected) अणु
		fmerr("FM device is already disconnected\n");
		वापस -EIO;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&fmdev->mutex))
		वापस -ERESTARTSYS;

	/* Turn on RDS mode अगर it is disabled */
	ret = fm_rx_get_rds_mode(fmdev, &rds_mode);
	अगर (ret < 0) अणु
		fmerr("Unable to read current rds mode\n");
		जाओ पढ़ो_unlock;
	पूर्ण

	अगर (rds_mode == FM_RDS_DISABLE) अणु
		ret = fmc_set_rds_mode(fmdev, FM_RDS_ENABLE);
		अगर (ret < 0) अणु
			fmerr("Failed to enable rds mode\n");
			जाओ पढ़ो_unlock;
		पूर्ण
	पूर्ण

	/* Copy RDS data from पूर्णांकernal buffer to user buffer */
	ret = fmc_transfer_rds_from_पूर्णांकernal_buff(fmdev, file, buf, count);
पढ़ो_unlock:
	mutex_unlock(&fmdev->mutex);
	वापस ret;
पूर्ण

/* Write TX RDS data */
अटल sमाप_प्रकार fm_v4l2_fops_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user * buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा tx_rds rds;
	पूर्णांक ret;
	काष्ठा fmdev *fmdev;

	ret = copy_from_user(&rds, buf, माप(rds));
	rds.text[माप(rds.text) - 1] = '\0';
	fmdbg("(%d)type: %d, text %s, af %d\n",
		   ret, rds.text_type, rds.text, rds.af_freq);
	अगर (ret)
		वापस -EFAULT;

	fmdev = video_drvdata(file);
	अगर (mutex_lock_पूर्णांकerruptible(&fmdev->mutex))
		वापस -ERESTARTSYS;
	fm_tx_set_radio_text(fmdev, rds.text, rds.text_type);
	fm_tx_set_af(fmdev, rds.af_freq);
	mutex_unlock(&fmdev->mutex);

	वापस माप(rds);
पूर्ण

अटल __poll_t fm_v4l2_fops_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *pts)
अणु
	पूर्णांक ret;
	काष्ठा fmdev *fmdev;

	fmdev = video_drvdata(file);
	mutex_lock(&fmdev->mutex);
	ret = fmc_is_rds_data_available(fmdev, file, pts);
	mutex_unlock(&fmdev->mutex);
	अगर (ret < 0)
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

/*
 * Handle खोलो request क्रम "/dev/radioX" device.
 * Start with FM RX mode as शेष.
 */
अटल पूर्णांक fm_v4l2_fops_खोलो(काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा fmdev *fmdev = शून्य;

	/* Don't allow multiple खोलो */
	अगर (radio_disconnected) अणु
		fmerr("FM device is already opened\n");
		वापस -EBUSY;
	पूर्ण

	fmdev = video_drvdata(file);

	अगर (mutex_lock_पूर्णांकerruptible(&fmdev->mutex))
		वापस -ERESTARTSYS;
	ret = fmc_prepare(fmdev);
	अगर (ret < 0) अणु
		fmerr("Unable to prepare FM CORE\n");
		जाओ खोलो_unlock;
	पूर्ण

	fmdbg("Load FM RX firmware..\n");

	ret = fmc_set_mode(fmdev, FM_MODE_RX);
	अगर (ret < 0) अणु
		fmerr("Unable to load FM RX firmware\n");
		जाओ खोलो_unlock;
	पूर्ण
	radio_disconnected = 1;

खोलो_unlock:
	mutex_unlock(&fmdev->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक fm_v4l2_fops_release(काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा fmdev *fmdev;

	fmdev = video_drvdata(file);
	अगर (!radio_disconnected) अणु
		fmdbg("FM device is already closed\n");
		वापस 0;
	पूर्ण

	mutex_lock(&fmdev->mutex);
	ret = fmc_set_mode(fmdev, FM_MODE_OFF);
	अगर (ret < 0) अणु
		fmerr("Unable to turn off the chip\n");
		जाओ release_unlock;
	पूर्ण

	ret = fmc_release(fmdev);
	अगर (ret < 0) अणु
		fmerr("FM CORE release failed\n");
		जाओ release_unlock;
	पूर्ण
	radio_disconnected = 0;

release_unlock:
	mutex_unlock(&fmdev->mutex);
	वापस ret;
पूर्ण

/* V4L2 RADIO (/dev/radioX) device IOCTL पूर्णांकerfaces */
अटल पूर्णांक fm_v4l2_vidioc_querycap(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_capability *capability)
अणु
	strscpy(capability->driver, FM_DRV_NAME, माप(capability->driver));
	strscpy(capability->card, FM_DRV_CARD_SHORT_NAME,
		माप(capability->card));
	प्र_लिखो(capability->bus_info, "UART");
	वापस 0;
पूर्ण

अटल पूर्णांक fm_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fmdev *fmdev = container_of(ctrl->handler,
			काष्ठा fmdev, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल  V4L2_CID_TUNE_ANTENNA_CAPACITOR:
		ctrl->val = fm_tx_get_tune_cap_val(fmdev);
		अवरोध;
	शेष:
		fmwarn("%s: Unknown IOCTL: %d\n", __func__, ctrl->id);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm_v4l2_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fmdev *fmdev = container_of(ctrl->handler,
			काष्ठा fmdev, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_VOLUME:	/* set volume */
		वापस fm_rx_set_volume(fmdev, (u16)ctrl->val);

	हाल V4L2_CID_AUDIO_MUTE:	/* set mute */
		वापस fmc_set_mute_mode(fmdev, (u8)ctrl->val);

	हाल V4L2_CID_TUNE_POWER_LEVEL:
		/* set TX घातer level - ext control */
		वापस fm_tx_set_pwr_lvl(fmdev, (u8)ctrl->val);

	हाल V4L2_CID_TUNE_PREEMPHASIS:
		वापस fm_tx_set_preemph_filter(fmdev, (u8) ctrl->val);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक fm_v4l2_vidioc_g_audio(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_audio *audio)
अणु
	स_रखो(audio, 0, माप(*audio));
	strscpy(audio->name, "Radio", माप(audio->name));
	audio->capability = V4L2_AUDCAP_STEREO;

	वापस 0;
पूर्ण

अटल पूर्णांक fm_v4l2_vidioc_s_audio(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_audio *audio)
अणु
	अगर (audio->index != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Get tuner attributes. If current mode is NOT RX, वापस error */
अटल पूर्णांक fm_v4l2_vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा fmdev *fmdev = video_drvdata(file);
	u32 bottom_freq;
	u32 top_freq;
	u16 stereo_mono_mode;
	u16 rssilvl;
	पूर्णांक ret;

	अगर (tuner->index != 0)
		वापस -EINVAL;

	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	ret = fm_rx_get_band_freq_range(fmdev, &bottom_freq, &top_freq);
	अगर (ret != 0)
		वापस ret;

	ret = fm_rx_get_stereo_mono(fmdev, &stereo_mono_mode);
	अगर (ret != 0)
		वापस ret;

	ret = fm_rx_get_rssi_level(fmdev, &rssilvl);
	अगर (ret != 0)
		वापस ret;

	strscpy(tuner->name, "FM", माप(tuner->name));
	tuner->type = V4L2_TUNER_RADIO;
	/* Store rangelow and rangehigh freq in unit of 62.5 Hz */
	tuner->rangelow = bottom_freq * 16;
	tuner->rangehigh = top_freq * 16;
	tuner->rxsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO |
	((fmdev->rx.rds.flag == FM_RDS_ENABLE) ? V4L2_TUNER_SUB_RDS : 0);
	tuner->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_RDS |
			    V4L2_TUNER_CAP_LOW |
			    V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			    V4L2_TUNER_CAP_HWSEEK_WRAP;
	tuner->audmode = (stereo_mono_mode ?
			  V4L2_TUNER_MODE_MONO : V4L2_TUNER_MODE_STEREO);

	/*
	 * Actual rssi value lies in between -128 to +127.
	 * Convert this range from 0 to 255 by adding +128
	 */
	rssilvl += 128;

	/*
	 * Return संकेत strength value should be within 0 to 65535.
	 * Find out correct संकेत radio by multiplying (65535/255) = 257
	 */
	tuner->संकेत = rssilvl * 257;
	tuner->afc = 0;

	वापस ret;
पूर्ण

/*
 * Set tuner attributes. If current mode is NOT RX, set to RX.
 * Currently, we set only audio mode (mono/stereo) and RDS state (on/off).
 * Should we set other tuner attributes, too?
 */
अटल पूर्णांक fm_v4l2_vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा fmdev *fmdev = video_drvdata(file);
	u16 aud_mode;
	u8 rds_mode;
	पूर्णांक ret;

	अगर (tuner->index != 0)
		वापस -EINVAL;

	aud_mode = (tuner->audmode == V4L2_TUNER_MODE_STEREO) ?
			FM_STEREO_MODE : FM_MONO_MODE;
	rds_mode = (tuner->rxsubchans & V4L2_TUNER_SUB_RDS) ?
			FM_RDS_ENABLE : FM_RDS_DISABLE;

	अगर (fmdev->curr_fmmode != FM_MODE_RX) अणु
		ret = fmc_set_mode(fmdev, FM_MODE_RX);
		अगर (ret < 0) अणु
			fmerr("Failed to set RX mode\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = fmc_set_stereo_mono(fmdev, aud_mode);
	अगर (ret < 0) अणु
		fmerr("Failed to set RX stereo/mono mode\n");
		वापस ret;
	पूर्ण

	ret = fmc_set_rds_mode(fmdev, rds_mode);
	अगर (ret < 0)
		fmerr("Failed to set RX RDS mode\n");

	वापस ret;
पूर्ण

/* Get tuner or modulator radio frequency */
अटल पूर्णांक fm_v4l2_vidioc_g_freq(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा fmdev *fmdev = video_drvdata(file);
	पूर्णांक ret;

	ret = fmc_get_freq(fmdev, &freq->frequency);
	अगर (ret < 0) अणु
		fmerr("Failed to get frequency\n");
		वापस ret;
	पूर्ण

	/* Frequency unit of 62.5 Hz*/
	freq->frequency = (u32) freq->frequency * 16;

	वापस 0;
पूर्ण

/* Set tuner or modulator radio frequency */
अटल पूर्णांक fm_v4l2_vidioc_s_freq(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा fmdev *fmdev = video_drvdata(file);

	/*
	 * As V4L2_TUNER_CAP_LOW is set 1 user sends the frequency
	 * in units of 62.5 Hz.
	 */
	वापस fmc_set_freq(fmdev, freq->frequency / 16);
पूर्ण

/* Set hardware frequency seek. If current mode is NOT RX, set it RX. */
अटल पूर्णांक fm_v4l2_vidioc_s_hw_freq_seek(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_hw_freq_seek *seek)
अणु
	काष्ठा fmdev *fmdev = video_drvdata(file);
	पूर्णांक ret;

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EWOULDBLOCK;

	अगर (fmdev->curr_fmmode != FM_MODE_RX) अणु
		ret = fmc_set_mode(fmdev, FM_MODE_RX);
		अगर (ret != 0) अणु
			fmerr("Failed to set RX mode\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = fm_rx_seek(fmdev, seek->seek_upward, seek->wrap_around,
			seek->spacing);
	अगर (ret < 0)
		fmerr("RX seek failed - %d\n", ret);

	वापस ret;
पूर्ण
/* Get modulator attributes. If mode is not TX, वापस no attributes. */
अटल पूर्णांक fm_v4l2_vidioc_g_modulator(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_modulator *mod)
अणु
	काष्ठा fmdev *fmdev = video_drvdata(file);

	अगर (mod->index != 0)
		वापस -EINVAL;

	अगर (fmdev->curr_fmmode != FM_MODE_TX)
		वापस -EPERM;

	mod->txsubchans = ((fmdev->tx_data.aud_mode == FM_STEREO_MODE) ?
				V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO) |
				((fmdev->tx_data.rds.flag == FM_RDS_ENABLE) ?
				V4L2_TUNER_SUB_RDS : 0);

	mod->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_RDS |
				V4L2_TUNER_CAP_LOW;

	वापस 0;
पूर्ण

/* Set modulator attributes. If mode is not TX, set to TX. */
अटल पूर्णांक fm_v4l2_vidioc_s_modulator(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_modulator *mod)
अणु
	काष्ठा fmdev *fmdev = video_drvdata(file);
	u8 rds_mode;
	u16 aud_mode;
	पूर्णांक ret;

	अगर (mod->index != 0)
		वापस -EINVAL;

	अगर (fmdev->curr_fmmode != FM_MODE_TX) अणु
		ret = fmc_set_mode(fmdev, FM_MODE_TX);
		अगर (ret != 0) अणु
			fmerr("Failed to set TX mode\n");
			वापस ret;
		पूर्ण
	पूर्ण

	aud_mode = (mod->txsubchans & V4L2_TUNER_SUB_STEREO) ?
			FM_STEREO_MODE : FM_MONO_MODE;
	rds_mode = (mod->txsubchans & V4L2_TUNER_SUB_RDS) ?
			FM_RDS_ENABLE : FM_RDS_DISABLE;
	ret = fm_tx_set_stereo_mono(fmdev, aud_mode);
	अगर (ret < 0) अणु
		fmerr("Failed to set mono/stereo mode for TX\n");
		वापस ret;
	पूर्ण
	ret = fm_tx_set_rds_mode(fmdev, rds_mode);
	अगर (ret < 0)
		fmerr("Failed to set rds mode for TX\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations fm_drv_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = fm_v4l2_fops_पढ़ो,
	.ग_लिखो = fm_v4l2_fops_ग_लिखो,
	.poll = fm_v4l2_fops_poll,
	.unlocked_ioctl = video_ioctl2,
	.खोलो = fm_v4l2_fops_खोलो,
	.release = fm_v4l2_fops_release,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops fm_ctrl_ops = अणु
	.s_ctrl = fm_v4l2_s_ctrl,
	.g_अस्थिर_ctrl = fm_g_अस्थिर_ctrl,
पूर्ण;
अटल स्थिर काष्ठा v4l2_ioctl_ops fm_drv_ioctl_ops = अणु
	.vidioc_querycap = fm_v4l2_vidioc_querycap,
	.vidioc_g_audio = fm_v4l2_vidioc_g_audio,
	.vidioc_s_audio = fm_v4l2_vidioc_s_audio,
	.vidioc_g_tuner = fm_v4l2_vidioc_g_tuner,
	.vidioc_s_tuner = fm_v4l2_vidioc_s_tuner,
	.vidioc_g_frequency = fm_v4l2_vidioc_g_freq,
	.vidioc_s_frequency = fm_v4l2_vidioc_s_freq,
	.vidioc_s_hw_freq_seek = fm_v4l2_vidioc_s_hw_freq_seek,
	.vidioc_g_modulator = fm_v4l2_vidioc_g_modulator,
	.vidioc_s_modulator = fm_v4l2_vidioc_s_modulator
पूर्ण;

/* V4L2 RADIO device parent काष्ठाure */
अटल स्थिर काष्ठा video_device fm_viddev_ढाँचा = अणु
	.fops = &fm_drv_fops,
	.ioctl_ops = &fm_drv_ioctl_ops,
	.name = FM_DRV_NAME,
	.release = video_device_release_empty,
	/*
	 * To ensure both the tuner and modulator ioctls are accessible we
	 * set the vfl_dir to M2M to indicate this.
	 *
	 * It is not really a mem2mem device of course, but it can both receive
	 * and transmit using the same radio device. It's the only radio driver
	 * that करोes this and it should really be split in two radio devices,
	 * but that would affect applications using this driver.
	 */
	.vfl_dir = VFL_सूची_M2M,
	.device_caps = V4L2_CAP_HW_FREQ_SEEK | V4L2_CAP_TUNER | V4L2_CAP_RADIO |
		       V4L2_CAP_MODULATOR | V4L2_CAP_AUDIO |
		       V4L2_CAP_READWRITE | V4L2_CAP_RDS_CAPTURE,
पूर्ण;

पूर्णांक fm_v4l2_init_video_device(काष्ठा fmdev *fmdev, पूर्णांक radio_nr)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret;

	strscpy(fmdev->v4l2_dev.name, FM_DRV_NAME,
		माप(fmdev->v4l2_dev.name));
	ret = v4l2_device_रेजिस्टर(शून्य, &fmdev->v4l2_dev);
	अगर (ret < 0)
		वापस ret;

	/* Init mutex क्रम core locking */
	mutex_init(&fmdev->mutex);

	/* Setup FM driver's V4L2 properties */
	gradio_dev = fm_viddev_ढाँचा;

	video_set_drvdata(&gradio_dev, fmdev);

	gradio_dev.lock = &fmdev->mutex;
	gradio_dev.v4l2_dev = &fmdev->v4l2_dev;

	/* Register with V4L2 subप्रणाली as RADIO device */
	अगर (video_रेजिस्टर_device(&gradio_dev, VFL_TYPE_RADIO, radio_nr)) अणु
		v4l2_device_unरेजिस्टर(&fmdev->v4l2_dev);
		fmerr("Could not register video device\n");
		वापस -ENOMEM;
	पूर्ण

	fmdev->radio_dev = &gradio_dev;

	/* Register to v4l2 ctrl handler framework */
	fmdev->radio_dev->ctrl_handler = &fmdev->ctrl_handler;

	ret = v4l2_ctrl_handler_init(&fmdev->ctrl_handler, 5);
	अगर (ret < 0) अणु
		fmerr("(fmdev): Can't init ctrl handler\n");
		v4l2_ctrl_handler_मुक्त(&fmdev->ctrl_handler);
		video_unरेजिस्टर_device(fmdev->radio_dev);
		v4l2_device_unरेजिस्टर(&fmdev->v4l2_dev);
		वापस -EBUSY;
	पूर्ण

	/*
	 * Following controls are handled by V4L2 control framework.
	 * Added in ascending ID order.
	 */
	v4l2_ctrl_new_std(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, FM_RX_VOLUME_MIN,
			FM_RX_VOLUME_MAX, 1, FM_RX_VOLUME_MAX);

	v4l2_ctrl_new_std(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);

	v4l2_ctrl_new_std_menu(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_TUNE_PREEMPHASIS, V4L2_PREEMPHASIS_75_uS,
			0, V4L2_PREEMPHASIS_75_uS);

	v4l2_ctrl_new_std(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_TUNE_POWER_LEVEL, FM_PWR_LVL_LOW,
			FM_PWR_LVL_HIGH, 1, FM_PWR_LVL_HIGH);

	ctrl = v4l2_ctrl_new_std(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_TUNE_ANTENNA_CAPACITOR, 0,
			255, 1, 255);

	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	वापस 0;
पूर्ण

व्योम *fm_v4l2_deinit_video_device(व्योम)
अणु
	काष्ठा fmdev *fmdev;


	fmdev = video_get_drvdata(&gradio_dev);

	/* Unरेजिस्टर to v4l2 ctrl handler framework*/
	v4l2_ctrl_handler_मुक्त(&fmdev->ctrl_handler);

	/* Unरेजिस्टर RADIO device from V4L2 subप्रणाली */
	video_unरेजिस्टर_device(&gradio_dev);

	v4l2_device_unरेजिस्टर(&fmdev->v4l2_dev);

	वापस fmdev;
पूर्ण
