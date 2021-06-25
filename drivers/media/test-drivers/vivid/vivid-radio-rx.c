<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-radio-rx.c - radio receiver support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-dv-timings.h>

#समावेश "vivid-core.h"
#समावेश "vivid-ctrls.h"
#समावेश "vivid-radio-common.h"
#समावेश "vivid-rds-gen.h"
#समावेश "vivid-radio-rx.h"

sमाप_प्रकार vivid_radio_rx_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार size, loff_t *offset)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_rds_data *data = dev->rds_gen.data;
	bool use_alternates;
	kसमय_प्रकार बारtamp;
	अचिन्हित blk;
	पूर्णांक perc;
	पूर्णांक i;

	अगर (dev->radio_rx_rds_controls)
		वापस -EINVAL;
	अगर (size < माप(*data))
		वापस 0;
	size = माप(*data) * (size / माप(*data));

	अगर (mutex_lock_पूर्णांकerruptible(&dev->mutex))
		वापस -ERESTARTSYS;
	अगर (dev->radio_rx_rds_owner &&
	    file->निजी_data != dev->radio_rx_rds_owner) अणु
		mutex_unlock(&dev->mutex);
		वापस -EBUSY;
	पूर्ण
	अगर (dev->radio_rx_rds_owner == शून्य) अणु
		vivid_radio_rds_init(dev);
		dev->radio_rx_rds_owner = file->निजी_data;
	पूर्ण

retry:
	बारtamp = kसमय_sub(kसमय_get(), dev->radio_rds_init_समय);
	blk = kसमय_भागns(बारtamp, VIVID_RDS_NSEC_PER_BLK);
	use_alternates = (blk % VIVID_RDS_GEN_BLOCKS) & 1;

	अगर (dev->radio_rx_rds_last_block == 0 ||
	    dev->radio_rx_rds_use_alternates != use_alternates) अणु
		dev->radio_rx_rds_use_alternates = use_alternates;
		/* Re-init the RDS generator */
		vivid_radio_rds_init(dev);
	पूर्ण
	अगर (blk >= dev->radio_rx_rds_last_block + VIVID_RDS_GEN_BLOCKS)
		dev->radio_rx_rds_last_block = blk - VIVID_RDS_GEN_BLOCKS + 1;

	/*
	 * No data is available अगर there hasn't been समय to get new data,
	 * or अगर the RDS receiver has been disabled, or अगर we use the data
	 * from the RDS transmitter and that RDS transmitter has been disabled,
	 * or अगर the संकेत quality is too weak.
	 */
	अगर (blk == dev->radio_rx_rds_last_block || !dev->radio_rx_rds_enabled ||
	    (dev->radio_rds_loop && !(dev->radio_tx_subchans & V4L2_TUNER_SUB_RDS)) ||
	    असल(dev->radio_rx_sig_qual) > 200) अणु
		mutex_unlock(&dev->mutex);
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EWOULDBLOCK;
		अगर (msleep_पूर्णांकerruptible(20) && संकेत_pending(current))
			वापस -EINTR;
		अगर (mutex_lock_पूर्णांकerruptible(&dev->mutex))
			वापस -ERESTARTSYS;
		जाओ retry;
	पूर्ण

	/* असल(dev->radio_rx_sig_qual) <= 200, map that to a 0-50% range */
	perc = असल(dev->radio_rx_sig_qual) / 4;

	क्रम (i = 0; i < size && blk > dev->radio_rx_rds_last_block;
			dev->radio_rx_rds_last_block++) अणु
		अचिन्हित data_blk = dev->radio_rx_rds_last_block % VIVID_RDS_GEN_BLOCKS;
		काष्ठा v4l2_rds_data rds = data[data_blk];

		अगर (data_blk == 0 && dev->radio_rds_loop)
			vivid_radio_rds_init(dev);
		अगर (perc && pअक्रमom_u32_max(100) < perc) अणु
			चयन (pअक्रमom_u32_max(4)) अणु
			हाल 0:
				rds.block |= V4L2_RDS_BLOCK_CORRECTED;
				अवरोध;
			हाल 1:
				rds.block |= V4L2_RDS_BLOCK_INVALID;
				अवरोध;
			हाल 2:
				rds.block |= V4L2_RDS_BLOCK_ERROR;
				rds.lsb = pअक्रमom_u32_max(256);
				rds.msb = pअक्रमom_u32_max(256);
				अवरोध;
			हाल 3: /* Skip block altogether */
				अगर (i)
					जारी;
				/*
				 * Must make sure at least one block is
				 * वापसed, otherwise the application
				 * might think that end-of-file occurred.
				 */
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (copy_to_user(buf + i, &rds, माप(rds))) अणु
			i = -EFAULT;
			अवरोध;
		पूर्ण
		i += माप(rds);
	पूर्ण
	mutex_unlock(&dev->mutex);
	वापस i;
पूर्ण

__poll_t vivid_radio_rx_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	वापस EPOLLIN | EPOLLRDNORM | v4l2_ctrl_poll(file, रुको);
पूर्ण

पूर्णांक vivid_radio_rx_क्रमागत_freq_bands(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency_band *band)
अणु
	अगर (band->tuner != 0)
		वापस -EINVAL;

	अगर (band->index >= TOT_BANDS)
		वापस -EINVAL;

	*band = vivid_radio_bands[band->index];
	वापस 0;
पूर्ण

पूर्णांक vivid_radio_rx_s_hw_freq_seek(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_hw_freq_seek *a)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	अचिन्हित low, high;
	अचिन्हित freq;
	अचिन्हित spacing;
	अचिन्हित band;

	अगर (a->tuner)
		वापस -EINVAL;
	अगर (a->wrap_around && dev->radio_rx_hw_seek_mode == VIVID_HW_SEEK_BOUNDED)
		वापस -EINVAL;

	अगर (!a->wrap_around && dev->radio_rx_hw_seek_mode == VIVID_HW_SEEK_WRAP)
		वापस -EINVAL;
	अगर (!a->rangelow ^ !a->rangehigh)
		वापस -EINVAL;

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EWOULDBLOCK;

	अगर (a->rangelow) अणु
		क्रम (band = 0; band < TOT_BANDS; band++)
			अगर (a->rangelow >= vivid_radio_bands[band].rangelow &&
			    a->rangehigh <= vivid_radio_bands[band].rangehigh)
				अवरोध;
		अगर (band == TOT_BANDS)
			वापस -EINVAL;
		अगर (!dev->radio_rx_hw_seek_prog_lim &&
		    (a->rangelow != vivid_radio_bands[band].rangelow ||
		     a->rangehigh != vivid_radio_bands[band].rangehigh))
			वापस -EINVAL;
		low = a->rangelow;
		high = a->rangehigh;
	पूर्ण अन्यथा अणु
		क्रम (band = 0; band < TOT_BANDS; band++)
			अगर (dev->radio_rx_freq >= vivid_radio_bands[band].rangelow &&
			    dev->radio_rx_freq <= vivid_radio_bands[band].rangehigh)
				अवरोध;
		अगर (band == TOT_BANDS)
			वापस -EINVAL;
		low = vivid_radio_bands[band].rangelow;
		high = vivid_radio_bands[band].rangehigh;
	पूर्ण
	spacing = band == BAND_AM ? 1600 : 16000;
	freq = clamp(dev->radio_rx_freq, low, high);

	अगर (a->seek_upward) अणु
		freq = spacing * (freq / spacing) + spacing;
		अगर (freq > high) अणु
			अगर (!a->wrap_around)
				वापस -ENODATA;
			freq = spacing * (low / spacing) + spacing;
			अगर (freq >= dev->radio_rx_freq)
				वापस -ENODATA;
		पूर्ण
	पूर्ण अन्यथा अणु
		freq = spacing * ((freq + spacing - 1) / spacing) - spacing;
		अगर (freq < low) अणु
			अगर (!a->wrap_around)
				वापस -ENODATA;
			freq = spacing * ((high + spacing - 1) / spacing) - spacing;
			अगर (freq <= dev->radio_rx_freq)
				वापस -ENODATA;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vivid_radio_rx_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	पूर्णांक delta = 800;
	पूर्णांक sig_qual;

	अगर (vt->index > 0)
		वापस -EINVAL;

	strscpy(vt->name, "AM/FM/SW Receiver", माप(vt->name));
	vt->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			 V4L2_TUNER_CAP_FREQ_BANDS | V4L2_TUNER_CAP_RDS |
			 (dev->radio_rx_rds_controls ?
				V4L2_TUNER_CAP_RDS_CONTROLS :
				V4L2_TUNER_CAP_RDS_BLOCK_IO) |
			 (dev->radio_rx_hw_seek_prog_lim ?
				V4L2_TUNER_CAP_HWSEEK_PROG_LIM : 0);
	चयन (dev->radio_rx_hw_seek_mode) अणु
	हाल VIVID_HW_SEEK_BOUNDED:
		vt->capability |= V4L2_TUNER_CAP_HWSEEK_BOUNDED;
		अवरोध;
	हाल VIVID_HW_SEEK_WRAP:
		vt->capability |= V4L2_TUNER_CAP_HWSEEK_WRAP;
		अवरोध;
	हाल VIVID_HW_SEEK_BOTH:
		vt->capability |= V4L2_TUNER_CAP_HWSEEK_WRAP |
				  V4L2_TUNER_CAP_HWSEEK_BOUNDED;
		अवरोध;
	पूर्ण
	vt->rangelow = AM_FREQ_RANGE_LOW;
	vt->rangehigh = FM_FREQ_RANGE_HIGH;
	sig_qual = dev->radio_rx_sig_qual;
	vt->संकेत = असल(sig_qual) > delta ? 0 :
		     0xffff - ((अचिन्हित)असल(sig_qual) * 0xffff) / delta;
	vt->afc = sig_qual > delta ? 0 : sig_qual;
	अगर (असल(sig_qual) > delta)
		vt->rxsubchans = 0;
	अन्यथा अगर (dev->radio_rx_freq < FM_FREQ_RANGE_LOW || vt->संकेत < 0x8000)
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	अन्यथा अगर (dev->radio_rds_loop && !(dev->radio_tx_subchans & V4L2_TUNER_SUB_STEREO))
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	अन्यथा
		vt->rxsubchans = V4L2_TUNER_SUB_STEREO;
	अगर (dev->radio_rx_rds_enabled &&
	    (!dev->radio_rds_loop || (dev->radio_tx_subchans & V4L2_TUNER_SUB_RDS)) &&
	    dev->radio_rx_freq >= FM_FREQ_RANGE_LOW && vt->संकेत >= 0xc000)
		vt->rxsubchans |= V4L2_TUNER_SUB_RDS;
	अगर (dev->radio_rx_rds_controls)
		vivid_radio_rds_init(dev);
	vt->audmode = dev->radio_rx_audmode;
	वापस 0;
पूर्ण

पूर्णांक vivid_radio_rx_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (vt->index)
		वापस -EINVAL;
	dev->radio_rx_audmode = vt->audmode >= V4L2_TUNER_MODE_STEREO;
	वापस 0;
पूर्ण
