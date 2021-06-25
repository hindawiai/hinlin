<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-radio-tx.c - radio transmitter support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-dv-timings.h>

#समावेश "vivid-core.h"
#समावेश "vivid-ctrls.h"
#समावेश "vivid-radio-common.h"
#समावेश "vivid-radio-tx.h"

sमाप_प्रकार vivid_radio_tx_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार size, loff_t *offset)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_rds_data *data = dev->rds_gen.data;
	kसमय_प्रकार बारtamp;
	अचिन्हित blk;
	पूर्णांक i;

	अगर (dev->radio_tx_rds_controls)
		वापस -EINVAL;

	अगर (size < माप(*data))
		वापस -EINVAL;
	size = माप(*data) * (size / माप(*data));

	अगर (mutex_lock_पूर्णांकerruptible(&dev->mutex))
		वापस -ERESTARTSYS;
	अगर (dev->radio_tx_rds_owner &&
	    file->निजी_data != dev->radio_tx_rds_owner) अणु
		mutex_unlock(&dev->mutex);
		वापस -EBUSY;
	पूर्ण
	dev->radio_tx_rds_owner = file->निजी_data;

retry:
	बारtamp = kसमय_sub(kसमय_get(), dev->radio_rds_init_समय);
	blk = kसमय_भागns(बारtamp, VIVID_RDS_NSEC_PER_BLK);
	अगर (blk - VIVID_RDS_GEN_BLOCKS >= dev->radio_tx_rds_last_block)
		dev->radio_tx_rds_last_block = blk - VIVID_RDS_GEN_BLOCKS + 1;

	/*
	 * No data is available अगर there hasn't been समय to get new data,
	 * or अगर the RDS receiver has been disabled, or अगर we use the data
	 * from the RDS transmitter and that RDS transmitter has been disabled,
	 * or अगर the संकेत quality is too weak.
	 */
	अगर (blk == dev->radio_tx_rds_last_block ||
	    !(dev->radio_tx_subchans & V4L2_TUNER_SUB_RDS)) अणु
		mutex_unlock(&dev->mutex);
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EWOULDBLOCK;
		अगर (msleep_पूर्णांकerruptible(20) && संकेत_pending(current))
			वापस -EINTR;
		अगर (mutex_lock_पूर्णांकerruptible(&dev->mutex))
			वापस -ERESTARTSYS;
		जाओ retry;
	पूर्ण

	क्रम (i = 0; i < size && blk > dev->radio_tx_rds_last_block;
			dev->radio_tx_rds_last_block++) अणु
		अचिन्हित data_blk = dev->radio_tx_rds_last_block % VIVID_RDS_GEN_BLOCKS;
		काष्ठा v4l2_rds_data rds;

		अगर (copy_from_user(&rds, buf + i, माप(rds))) अणु
			i = -EFAULT;
			अवरोध;
		पूर्ण
		i += माप(rds);
		अगर (!dev->radio_rds_loop)
			जारी;
		अगर ((rds.block & V4L2_RDS_BLOCK_MSK) == V4L2_RDS_BLOCK_INVALID ||
		    (rds.block & V4L2_RDS_BLOCK_ERROR))
			जारी;
		rds.block &= V4L2_RDS_BLOCK_MSK;
		data[data_blk] = rds;
	पूर्ण
	mutex_unlock(&dev->mutex);
	वापस i;
पूर्ण

__poll_t vivid_radio_tx_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	वापस EPOLLOUT | EPOLLWRNORM | v4l2_ctrl_poll(file, रुको);
पूर्ण

पूर्णांक vidioc_g_modulator(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_modulator *a)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (a->index > 0)
		वापस -EINVAL;

	strscpy(a->name, "AM/FM/SW Transmitter", माप(a->name));
	a->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_FREQ_BANDS | V4L2_TUNER_CAP_RDS |
			(dev->radio_tx_rds_controls ?
				V4L2_TUNER_CAP_RDS_CONTROLS :
				V4L2_TUNER_CAP_RDS_BLOCK_IO);
	a->rangelow = AM_FREQ_RANGE_LOW;
	a->rangehigh = FM_FREQ_RANGE_HIGH;
	a->txsubchans = dev->radio_tx_subchans;
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_modulator(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_modulator *a)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (a->index)
		वापस -EINVAL;
	अगर (a->txsubchans & ~0x13)
		वापस -EINVAL;
	dev->radio_tx_subchans = a->txsubchans;
	वापस 0;
पूर्ण
