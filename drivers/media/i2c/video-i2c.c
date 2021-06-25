<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * video-i2c.c - Support क्रम I2C transport video devices
 *
 * Copyright (C) 2018 Matt Ranostay <matt.ranostay@konsulko.com>
 *
 * Supported:
 * - Panasonic AMG88xx Grid-Eye Sensors
 * - Melexis MLX90640 Thermal Cameras
 */

#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/i2c.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#घोषणा VIDEO_I2C_DRIVER	"video-i2c"

काष्ठा video_i2c_chip;

काष्ठा video_i2c_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा video_i2c_data अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा video_i2c_chip *chip;
	काष्ठा mutex lock;
	spinlock_t slock;
	अचिन्हित पूर्णांक sequence;
	काष्ठा mutex queue_lock;

	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device vdev;
	काष्ठा vb2_queue vb_vidq;

	काष्ठा task_काष्ठा *kthपढ़ो_vid_cap;
	काष्ठा list_head vid_cap_active;

	काष्ठा v4l2_fract frame_पूर्णांकerval;
पूर्ण;

अटल स्थिर काष्ठा v4l2_fmtdesc amg88xx_क्रमmat = अणु
	.pixelक्रमmat = V4L2_PIX_FMT_Y12,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frmsize_discrete amg88xx_size = अणु
	.width = 8,
	.height = 8,
पूर्ण;

अटल स्थिर काष्ठा v4l2_fmtdesc mlx90640_क्रमmat = अणु
	.pixelक्रमmat = V4L2_PIX_FMT_Y16_BE,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frmsize_discrete mlx90640_size = अणु
	.width = 32,
	.height = 26, /* 24 lines of pixel data + 2 lines of processing data */
पूर्ण;

अटल स्थिर काष्ठा regmap_config amg88xx_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xff
पूर्ण;

अटल स्थिर काष्ठा regmap_config mlx90640_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,
पूर्ण;

काष्ठा video_i2c_chip अणु
	/* video dimensions */
	स्थिर काष्ठा v4l2_fmtdesc *क्रमmat;
	स्थिर काष्ठा v4l2_frmsize_discrete *size;

	/* available frame पूर्णांकervals */
	स्थिर काष्ठा v4l2_fract *frame_पूर्णांकervals;
	अचिन्हित पूर्णांक num_frame_पूर्णांकervals;

	/* pixel buffer size */
	अचिन्हित पूर्णांक buffer_size;

	/* pixel size in bits */
	अचिन्हित पूर्णांक bpp;

	स्थिर काष्ठा regmap_config *regmap_config;
	काष्ठा nvmem_config *nvmem_config;

	/* setup function */
	पूर्णांक (*setup)(काष्ठा video_i2c_data *data);

	/* xfer function */
	पूर्णांक (*xfer)(काष्ठा video_i2c_data *data, अक्षर *buf);

	/* घातer control function */
	पूर्णांक (*set_घातer)(काष्ठा video_i2c_data *data, bool on);

	/* hwmon init function */
	पूर्णांक (*hwmon_init)(काष्ठा video_i2c_data *data);
पूर्ण;

अटल पूर्णांक mlx90640_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा video_i2c_data *data = priv;

	वापस regmap_bulk_पढ़ो(data->regmap, 0x2400 + offset, val, bytes);
पूर्ण

अटल काष्ठा nvmem_config mlx90640_nvram_config = अणु
	.name = "mlx90640_nvram",
	.word_size = 2,
	.stride = 1,
	.size = 1664,
	.reg_पढ़ो = mlx90640_nvram_पढ़ो,
पूर्ण;

/* Power control रेजिस्टर */
#घोषणा AMG88XX_REG_PCTL	0x00
#घोषणा AMG88XX_PCTL_NORMAL		0x00
#घोषणा AMG88XX_PCTL_SLEEP		0x10

/* Reset रेजिस्टर */
#घोषणा AMG88XX_REG_RST		0x01
#घोषणा AMG88XX_RST_FLAG		0x30
#घोषणा AMG88XX_RST_INIT		0x3f

/* Frame rate रेजिस्टर */
#घोषणा AMG88XX_REG_FPSC	0x02
#घोषणा AMG88XX_FPSC_1FPS		BIT(0)

/* Thermistor रेजिस्टर */
#घोषणा AMG88XX_REG_TTHL	0x0e

/* Temperature रेजिस्टर */
#घोषणा AMG88XX_REG_T01L	0x80

/* Control रेजिस्टर */
#घोषणा MLX90640_REG_CTL1		0x800d
#घोषणा MLX90640_REG_CTL1_MASK		0x0380
#घोषणा MLX90640_REG_CTL1_MASK_SHIFT	7

अटल पूर्णांक amg88xx_xfer(काष्ठा video_i2c_data *data, अक्षर *buf)
अणु
	वापस regmap_bulk_पढ़ो(data->regmap, AMG88XX_REG_T01L, buf,
				data->chip->buffer_size);
पूर्ण

अटल पूर्णांक mlx90640_xfer(काष्ठा video_i2c_data *data, अक्षर *buf)
अणु
	वापस regmap_bulk_पढ़ो(data->regmap, 0x400, buf,
				data->chip->buffer_size);
पूर्ण

अटल पूर्णांक amg88xx_setup(काष्ठा video_i2c_data *data)
अणु
	अचिन्हित पूर्णांक mask = AMG88XX_FPSC_1FPS;
	अचिन्हित पूर्णांक val;

	अगर (data->frame_पूर्णांकerval.numerator == data->frame_पूर्णांकerval.denominator)
		val = mask;
	अन्यथा
		val = 0;

	वापस regmap_update_bits(data->regmap, AMG88XX_REG_FPSC, mask, val);
पूर्ण

अटल पूर्णांक mlx90640_setup(काष्ठा video_i2c_data *data)
अणु
	अचिन्हित पूर्णांक n, idx;

	क्रम (n = 0; n < data->chip->num_frame_पूर्णांकervals - 1; n++) अणु
		अगर (V4L2_FRACT_COMPARE(data->frame_पूर्णांकerval, ==,
				       data->chip->frame_पूर्णांकervals[n]))
			अवरोध;
	पूर्ण

	idx = data->chip->num_frame_पूर्णांकervals - n - 1;

	वापस regmap_update_bits(data->regmap, MLX90640_REG_CTL1,
				  MLX90640_REG_CTL1_MASK,
				  idx << MLX90640_REG_CTL1_MASK_SHIFT);
पूर्ण

अटल पूर्णांक amg88xx_set_घातer_on(काष्ठा video_i2c_data *data)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, AMG88XX_REG_PCTL, AMG88XX_PCTL_NORMAL);
	अगर (ret)
		वापस ret;

	msleep(50);

	ret = regmap_ग_लिखो(data->regmap, AMG88XX_REG_RST, AMG88XX_RST_INIT);
	अगर (ret)
		वापस ret;

	usleep_range(2000, 3000);

	ret = regmap_ग_लिखो(data->regmap, AMG88XX_REG_RST, AMG88XX_RST_FLAG);
	अगर (ret)
		वापस ret;

	/*
	 * Wait two frames beक्रमe पढ़ोing thermistor and temperature रेजिस्टरs
	 */
	msleep(200);

	वापस 0;
पूर्ण

अटल पूर्णांक amg88xx_set_घातer_off(काष्ठा video_i2c_data *data)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, AMG88XX_REG_PCTL, AMG88XX_PCTL_SLEEP);
	अगर (ret)
		वापस ret;
	/*
	 * Wait क्रम a जबतक to aव्योम resuming normal mode immediately after
	 * entering sleep mode, otherwise the device occasionally goes wrong
	 * (thermistor and temperature रेजिस्टरs are not updated at all)
	 */
	msleep(100);

	वापस 0;
पूर्ण

अटल पूर्णांक amg88xx_set_घातer(काष्ठा video_i2c_data *data, bool on)
अणु
	अगर (on)
		वापस amg88xx_set_घातer_on(data);

	वापस amg88xx_set_घातer_off(data);
पूर्ण

#अगर IS_REACHABLE(CONFIG_HWMON)

अटल स्थिर u32 amg88xx_temp_config[] = अणु
	HWMON_T_INPUT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info amg88xx_temp = अणु
	.type = hwmon_temp,
	.config = amg88xx_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *amg88xx_info[] = अणु
	&amg88xx_temp,
	शून्य
पूर्ण;

अटल umode_t amg88xx_is_visible(स्थिर व्योम *drvdata,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	वापस 0444;
पूर्ण

अटल पूर्णांक amg88xx_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा video_i2c_data *data = dev_get_drvdata(dev);
	__le16 buf;
	पूर्णांक पंचांगp;

	पंचांगp = pm_runसमय_get_sync(regmap_get_device(data->regmap));
	अगर (पंचांगp < 0) अणु
		pm_runसमय_put_noidle(regmap_get_device(data->regmap));
		वापस पंचांगp;
	पूर्ण

	पंचांगp = regmap_bulk_पढ़ो(data->regmap, AMG88XX_REG_TTHL, &buf, 2);
	pm_runसमय_mark_last_busy(regmap_get_device(data->regmap));
	pm_runसमय_put_स्वतःsuspend(regmap_get_device(data->regmap));
	अगर (पंचांगp)
		वापस पंचांगp;

	पंचांगp = le16_to_cpu(buf);

	/*
	 * Check क्रम sign bit, this isn't a two's complement value but an
	 * असलolute temperature that needs to be inverted in the हाल of being
	 * negative.
	 */
	अगर (पंचांगp & BIT(11))
		पंचांगp = -(पंचांगp & 0x7ff);

	*val = (पंचांगp * 625) / 10;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops amg88xx_hwmon_ops = अणु
	.is_visible = amg88xx_is_visible,
	.पढ़ो = amg88xx_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info amg88xx_chip_info = अणु
	.ops = &amg88xx_hwmon_ops,
	.info = amg88xx_info,
पूर्ण;

अटल पूर्णांक amg88xx_hwmon_init(काष्ठा video_i2c_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	व्योम *hwmon = devm_hwmon_device_रेजिस्टर_with_info(dev, "amg88xx", data,
						&amg88xx_chip_info, शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon);
पूर्ण
#अन्यथा
#घोषणा	amg88xx_hwmon_init	शून्य
#पूर्ण_अगर

क्रमागत अणु
	AMG88XX,
	MLX90640,
पूर्ण;

अटल स्थिर काष्ठा v4l2_fract amg88xx_frame_पूर्णांकervals[] = अणु
	अणु 1, 10 पूर्ण,
	अणु 1, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_fract mlx90640_frame_पूर्णांकervals[] = अणु
	अणु 1, 64 पूर्ण,
	अणु 1, 32 पूर्ण,
	अणु 1, 16 पूर्ण,
	अणु 1, 8 पूर्ण,
	अणु 1, 4 पूर्ण,
	अणु 1, 2 पूर्ण,
	अणु 1, 1 पूर्ण,
	अणु 2, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा video_i2c_chip video_i2c_chip[] = अणु
	[AMG88XX] = अणु
		.size		= &amg88xx_size,
		.क्रमmat		= &amg88xx_क्रमmat,
		.frame_पूर्णांकervals	= amg88xx_frame_पूर्णांकervals,
		.num_frame_पूर्णांकervals	= ARRAY_SIZE(amg88xx_frame_पूर्णांकervals),
		.buffer_size	= 128,
		.bpp		= 16,
		.regmap_config	= &amg88xx_regmap_config,
		.setup		= &amg88xx_setup,
		.xfer		= &amg88xx_xfer,
		.set_घातer	= amg88xx_set_घातer,
		.hwmon_init	= amg88xx_hwmon_init,
	पूर्ण,
	[MLX90640] = अणु
		.size		= &mlx90640_size,
		.क्रमmat		= &mlx90640_क्रमmat,
		.frame_पूर्णांकervals	= mlx90640_frame_पूर्णांकervals,
		.num_frame_पूर्णांकervals	= ARRAY_SIZE(mlx90640_frame_पूर्णांकervals),
		.buffer_size	= 1664,
		.bpp		= 16,
		.regmap_config	= &mlx90640_regmap_config,
		.nvmem_config	= &mlx90640_nvram_config,
		.setup		= mlx90640_setup,
		.xfer		= mlx90640_xfer,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations video_i2c_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= vb2_fop_release,
	.poll		= vb2_fop_poll,
	.पढ़ो		= vb2_fop_पढ़ो,
	.mmap		= vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा video_i2c_data *data = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size = data->chip->buffer_size;

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा video_i2c_data *data = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित पूर्णांक size = data->chip->buffer_size;

	अगर (vb2_plane_size(vb, 0) < size)
		वापस -EINVAL;

	vbuf->field = V4L2_FIELD_NONE;
	vb2_set_plane_payload(vb, 0, size);

	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा video_i2c_data *data = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा video_i2c_buffer *buf =
			container_of(vbuf, काष्ठा video_i2c_buffer, vb);

	spin_lock(&data->slock);
	list_add_tail(&buf->list, &data->vid_cap_active);
	spin_unlock(&data->slock);
पूर्ण

अटल पूर्णांक video_i2c_thपढ़ो_vid_cap(व्योम *priv)
अणु
	काष्ठा video_i2c_data *data = priv;
	अचिन्हित पूर्णांक delay = mult_frac(HZ, data->frame_पूर्णांकerval.numerator,
				       data->frame_पूर्णांकerval.denominator);

	set_मुक्तzable();

	करो अणु
		अचिन्हित दीर्घ start_jअगरfies = jअगरfies;
		काष्ठा video_i2c_buffer *vid_cap_buf = शून्य;
		पूर्णांक schedule_delay;

		try_to_मुक्तze();

		spin_lock(&data->slock);

		अगर (!list_empty(&data->vid_cap_active)) अणु
			vid_cap_buf = list_last_entry(&data->vid_cap_active,
						 काष्ठा video_i2c_buffer, list);
			list_del(&vid_cap_buf->list);
		पूर्ण

		spin_unlock(&data->slock);

		अगर (vid_cap_buf) अणु
			काष्ठा vb2_buffer *vb2_buf = &vid_cap_buf->vb.vb2_buf;
			व्योम *vbuf = vb2_plane_vaddr(vb2_buf, 0);
			पूर्णांक ret;

			ret = data->chip->xfer(data, vbuf);
			vb2_buf->बारtamp = kसमय_get_ns();
			vid_cap_buf->vb.sequence = data->sequence++;
			vb2_buffer_करोne(vb2_buf, ret ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		पूर्ण

		schedule_delay = delay - (jअगरfies - start_jअगरfies);

		अगर (समय_after(jअगरfies, start_jअगरfies + delay))
			schedule_delay = delay;

		schedule_समयout_पूर्णांकerruptible(schedule_delay);
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	वापस 0;
पूर्ण

अटल व्योम video_i2c_del_list(काष्ठा vb2_queue *vq, क्रमागत vb2_buffer_state state)
अणु
	काष्ठा video_i2c_data *data = vb2_get_drv_priv(vq);
	काष्ठा video_i2c_buffer *buf, *पंचांगp;

	spin_lock(&data->slock);

	list_क्रम_each_entry_safe(buf, पंचांगp, &data->vid_cap_active, list) अणु
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	पूर्ण

	spin_unlock(&data->slock);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा video_i2c_data *data = vb2_get_drv_priv(vq);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	अगर (data->kthपढ़ो_vid_cap)
		वापस 0;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ error_del_list;
	पूर्ण

	ret = data->chip->setup(data);
	अगर (ret)
		जाओ error_rpm_put;

	data->sequence = 0;
	data->kthपढ़ो_vid_cap = kthपढ़ो_run(video_i2c_thपढ़ो_vid_cap, data,
					    "%s-vid-cap", data->v4l2_dev.name);
	ret = PTR_ERR_OR_ZERO(data->kthपढ़ो_vid_cap);
	अगर (!ret)
		वापस 0;

error_rpm_put:
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
error_del_list:
	video_i2c_del_list(vq, VB2_BUF_STATE_QUEUED);

	वापस ret;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा video_i2c_data *data = vb2_get_drv_priv(vq);

	अगर (data->kthपढ़ो_vid_cap == शून्य)
		वापस;

	kthपढ़ो_stop(data->kthपढ़ो_vid_cap);
	data->kthपढ़ो_vid_cap = शून्य;
	pm_runसमय_mark_last_busy(regmap_get_device(data->regmap));
	pm_runसमय_put_स्वतःsuspend(regmap_get_device(data->regmap));

	video_i2c_del_list(vq, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops video_i2c_video_qops = अणु
	.queue_setup		= queue_setup,
	.buf_prepare		= buffer_prepare,
	.buf_queue		= buffer_queue,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक video_i2c_querycap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_capability *vcap)
अणु
	काष्ठा video_i2c_data *data = video_drvdata(file);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	काष्ठा i2c_client *client = to_i2c_client(dev);

	strscpy(vcap->driver, data->v4l2_dev.name, माप(vcap->driver));
	strscpy(vcap->card, data->vdev.name, माप(vcap->card));

	प्र_लिखो(vcap->bus_info, "I2C:%d-%d", client->adapter->nr, client->addr);

	वापस 0;
पूर्ण

अटल पूर्णांक video_i2c_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *inp)
अणु
	*inp = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक video_i2c_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक inp)
अणु
	वापस (inp > 0) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक video_i2c_क्रमागत_input(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_input *vin)
अणु
	अगर (vin->index > 0)
		वापस -EINVAL;

	strscpy(vin->name, "Camera", माप(vin->name));

	vin->type = V4L2_INPUT_TYPE_CAMERA;

	वापस 0;
पूर्ण

अटल पूर्णांक video_i2c_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा video_i2c_data *data = video_drvdata(file);
	क्रमागत v4l2_buf_type type = fmt->type;

	अगर (fmt->index > 0)
		वापस -EINVAL;

	*fmt = *data->chip->क्रमmat;
	fmt->type = type;

	वापस 0;
पूर्ण

अटल पूर्णांक video_i2c_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	स्थिर काष्ठा video_i2c_data *data = video_drvdata(file);
	स्थिर काष्ठा v4l2_frmsize_discrete *size = data->chip->size;

	/* currently only one frame size is allowed */
	अगर (fsize->index > 0)
		वापस -EINVAL;

	अगर (fsize->pixel_क्रमmat != data->chip->क्रमmat->pixelक्रमmat)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = size->width;
	fsize->discrete.height = size->height;

	वापस 0;
पूर्ण

अटल पूर्णांक video_i2c_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv,
					   काष्ठा v4l2_frmivalक्रमागत *fe)
अणु
	स्थिर काष्ठा video_i2c_data *data = video_drvdata(file);
	स्थिर काष्ठा v4l2_frmsize_discrete *size = data->chip->size;

	अगर (fe->index >= data->chip->num_frame_पूर्णांकervals)
		वापस -EINVAL;

	अगर (fe->width != size->width || fe->height != size->height)
		वापस -EINVAL;

	fe->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fe->discrete = data->chip->frame_पूर्णांकervals[fe->index];

	वापस 0;
पूर्ण

अटल पूर्णांक video_i2c_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_क्रमmat *fmt)
अणु
	स्थिर काष्ठा video_i2c_data *data = video_drvdata(file);
	स्थिर काष्ठा v4l2_frmsize_discrete *size = data->chip->size;
	काष्ठा v4l2_pix_क्रमmat *pix = &fmt->fmt.pix;
	अचिन्हित पूर्णांक bpp = data->chip->bpp / 8;

	pix->width = size->width;
	pix->height = size->height;
	pix->pixelक्रमmat = data->chip->क्रमmat->pixelक्रमmat;
	pix->field = V4L2_FIELD_NONE;
	pix->bytesperline = pix->width * bpp;
	pix->sizeimage = pix->bytesperline * pix->height;
	pix->colorspace = V4L2_COLORSPACE_RAW;

	वापस 0;
पूर्ण

अटल पूर्णांक video_i2c_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_i2c_data *data = video_drvdata(file);

	अगर (vb2_is_busy(&data->vb_vidq))
		वापस -EBUSY;

	वापस video_i2c_try_fmt_vid_cap(file, fh, fmt);
पूर्ण

अटल पूर्णांक video_i2c_g_parm(काष्ठा file *filp, व्योम *priv,
			      काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा video_i2c_data *data = video_drvdata(filp);

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	parm->parm.capture.पढ़ोbuffers = 1;
	parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.समयperframe = data->frame_पूर्णांकerval;

	वापस 0;
पूर्ण

अटल पूर्णांक video_i2c_s_parm(काष्ठा file *filp, व्योम *priv,
			      काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा video_i2c_data *data = video_drvdata(filp);
	पूर्णांक i;

	क्रम (i = 0; i < data->chip->num_frame_पूर्णांकervals - 1; i++) अणु
		अगर (V4L2_FRACT_COMPARE(parm->parm.capture.समयperframe, <=,
				       data->chip->frame_पूर्णांकervals[i]))
			अवरोध;
	पूर्ण
	data->frame_पूर्णांकerval = data->chip->frame_पूर्णांकervals[i];

	वापस video_i2c_g_parm(filp, priv, parm);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops video_i2c_ioctl_ops = अणु
	.vidioc_querycap		= video_i2c_querycap,
	.vidioc_g_input			= video_i2c_g_input,
	.vidioc_s_input			= video_i2c_s_input,
	.vidioc_क्रमागत_input		= video_i2c_क्रमागत_input,
	.vidioc_क्रमागत_fmt_vid_cap	= video_i2c_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_framesizes		= video_i2c_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= video_i2c_क्रमागत_frameपूर्णांकervals,
	.vidioc_g_fmt_vid_cap		= video_i2c_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= video_i2c_s_fmt_vid_cap,
	.vidioc_g_parm			= video_i2c_g_parm,
	.vidioc_s_parm			= video_i2c_s_parm,
	.vidioc_try_fmt_vid_cap		= video_i2c_try_fmt_vid_cap,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
पूर्ण;

अटल व्योम video_i2c_release(काष्ठा video_device *vdev)
अणु
	काष्ठा video_i2c_data *data = video_get_drvdata(vdev);

	v4l2_device_unरेजिस्टर(&data->v4l2_dev);
	mutex_destroy(&data->lock);
	mutex_destroy(&data->queue_lock);
	regmap_निकास(data->regmap);
	kमुक्त(data);
पूर्ण

अटल पूर्णांक video_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा video_i2c_data *data;
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा vb2_queue *queue;
	पूर्णांक ret = -ENODEV;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (dev_fwnode(&client->dev))
		data->chip = device_get_match_data(&client->dev);
	अन्यथा अगर (id)
		data->chip = &video_i2c_chip[id->driver_data];
	अन्यथा
		जाओ error_मुक्त_device;

	data->regmap = regmap_init_i2c(client, data->chip->regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		ret = PTR_ERR(data->regmap);
		जाओ error_मुक्त_device;
	पूर्ण

	v4l2_dev = &data->v4l2_dev;
	strscpy(v4l2_dev->name, VIDEO_I2C_DRIVER, माप(v4l2_dev->name));

	ret = v4l2_device_रेजिस्टर(&client->dev, v4l2_dev);
	अगर (ret < 0)
		जाओ error_regmap_निकास;

	mutex_init(&data->lock);
	mutex_init(&data->queue_lock);

	queue = &data->vb_vidq;
	queue->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	queue->io_modes = VB2_DMABUF | VB2_MMAP | VB2_USERPTR | VB2_READ;
	queue->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	queue->drv_priv = data;
	queue->buf_काष्ठा_size = माप(काष्ठा video_i2c_buffer);
	queue->min_buffers_needed = 1;
	queue->ops = &video_i2c_video_qops;
	queue->mem_ops = &vb2_vदो_स्मृति_memops;

	ret = vb2_queue_init(queue);
	अगर (ret < 0)
		जाओ error_unरेजिस्टर_device;

	data->vdev.queue = queue;
	data->vdev.queue->lock = &data->queue_lock;

	snम_लिखो(data->vdev.name, माप(data->vdev.name),
				 "I2C %d-%d Transport Video",
				 client->adapter->nr, client->addr);

	data->vdev.v4l2_dev = v4l2_dev;
	data->vdev.fops = &video_i2c_fops;
	data->vdev.lock = &data->lock;
	data->vdev.ioctl_ops = &video_i2c_ioctl_ops;
	data->vdev.release = video_i2c_release;
	data->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE |
				 V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;

	spin_lock_init(&data->slock);
	INIT_LIST_HEAD(&data->vid_cap_active);

	data->frame_पूर्णांकerval = data->chip->frame_पूर्णांकervals[0];

	video_set_drvdata(&data->vdev, data);
	i2c_set_clientdata(client, data);

	अगर (data->chip->set_घातer) अणु
		ret = data->chip->set_घातer(data, true);
		अगर (ret)
			जाओ error_unरेजिस्टर_device;
	पूर्ण

	pm_runसमय_get_noresume(&client->dev);
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 2000);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	अगर (data->chip->hwmon_init) अणु
		ret = data->chip->hwmon_init(data);
		अगर (ret < 0) अणु
			dev_warn(&client->dev,
				 "failed to register hwmon device\n");
		पूर्ण
	पूर्ण

	अगर (data->chip->nvmem_config) अणु
		काष्ठा nvmem_config *config = data->chip->nvmem_config;
		काष्ठा nvmem_device *device;

		config->priv = data;
		config->dev = &client->dev;

		device = devm_nvmem_रेजिस्टर(&client->dev, config);

		अगर (IS_ERR(device)) अणु
			dev_warn(&client->dev,
				 "failed to register nvmem device\n");
		पूर्ण
	पूर्ण

	ret = video_रेजिस्टर_device(&data->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		जाओ error_pm_disable;

	pm_runसमय_mark_last_busy(&client->dev);
	pm_runसमय_put_स्वतःsuspend(&client->dev);

	वापस 0;

error_pm_disable:
	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	अगर (data->chip->set_घातer)
		data->chip->set_घातer(data, false);

error_unरेजिस्टर_device:
	v4l2_device_unरेजिस्टर(v4l2_dev);
	mutex_destroy(&data->lock);
	mutex_destroy(&data->queue_lock);

error_regmap_निकास:
	regmap_निकास(data->regmap);

error_मुक्त_device:
	kमुक्त(data);

	वापस ret;
पूर्ण

अटल पूर्णांक video_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा video_i2c_data *data = i2c_get_clientdata(client);

	pm_runसमय_get_sync(&client->dev);
	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	अगर (data->chip->set_घातer)
		data->chip->set_घातer(data, false);

	video_unरेजिस्टर_device(&data->vdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक video_i2c_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा video_i2c_data *data = i2c_get_clientdata(to_i2c_client(dev));

	अगर (!data->chip->set_घातer)
		वापस 0;

	वापस data->chip->set_घातer(data, false);
पूर्ण

अटल पूर्णांक video_i2c_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा video_i2c_data *data = i2c_get_clientdata(to_i2c_client(dev));

	अगर (!data->chip->set_घातer)
		वापस 0;

	वापस data->chip->set_घातer(data, true);
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops video_i2c_pm_ops = अणु
	SET_RUNTIME_PM_OPS(video_i2c_pm_runसमय_suspend,
			   video_i2c_pm_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id video_i2c_id_table[] = अणु
	अणु "amg88xx", AMG88XX पूर्ण,
	अणु "mlx90640", MLX90640 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, video_i2c_id_table);

अटल स्थिर काष्ठा of_device_id video_i2c_of_match[] = अणु
	अणु .compatible = "panasonic,amg88xx", .data = &video_i2c_chip[AMG88XX] पूर्ण,
	अणु .compatible = "melexis,mlx90640", .data = &video_i2c_chip[MLX90640] पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, video_i2c_of_match);

अटल काष्ठा i2c_driver video_i2c_driver = अणु
	.driver = अणु
		.name	= VIDEO_I2C_DRIVER,
		.of_match_table = video_i2c_of_match,
		.pm	= &video_i2c_pm_ops,
	पूर्ण,
	.probe		= video_i2c_probe,
	.हटाओ		= video_i2c_हटाओ,
	.id_table	= video_i2c_id_table,
पूर्ण;

module_i2c_driver(video_i2c_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("I2C transport video support");
MODULE_LICENSE("GPL v2");
