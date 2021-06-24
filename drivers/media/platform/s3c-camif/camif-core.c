<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * s3c24xx/s3c64xx SoC series Camera Interface (CAMIF) driver
 *
 * Copyright (C) 2012 Sylwester Nawrocki <sylvester.nawrocki@gmail.com>
 * Copyright (C) 2012 Tomasz Figa <tomasz.figa@gmail.com>
 */
#घोषणा pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/version.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "camif-core.h"

अटल अक्षर *camअगर_घड़ीs[CLK_MAX_NUM] = अणु
	/* HCLK CAMIF घड़ी */
	[CLK_GATE]	= "camif",
	/* CAMIF / बाह्यal camera sensor master घड़ी */
	[CLK_CAM]	= "camera",
पूर्ण;

अटल स्थिर काष्ठा camअगर_fmt camअगर_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_YUV422P,
		.depth		= 16,
		.ybpp		= 1,
		.color		= IMG_FMT_YCBCR422P,
		.colplanes	= 3,
		.flags		= FMT_FL_S3C24XX_CODEC |
				  FMT_FL_S3C64XX,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YUV420,
		.depth		= 12,
		.ybpp		= 1,
		.color		= IMG_FMT_YCBCR420,
		.colplanes	= 3,
		.flags		= FMT_FL_S3C24XX_CODEC |
				  FMT_FL_S3C64XX,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YVU420,
		.depth		= 12,
		.ybpp		= 1,
		.color		= IMG_FMT_YCRCB420,
		.colplanes	= 3,
		.flags		= FMT_FL_S3C24XX_CODEC |
				  FMT_FL_S3C64XX,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB565X,
		.depth		= 16,
		.ybpp		= 2,
		.color		= IMG_FMT_RGB565,
		.colplanes	= 1,
		.flags		= FMT_FL_S3C24XX_PREVIEW |
				  FMT_FL_S3C64XX,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB32,
		.depth		= 32,
		.ybpp		= 4,
		.color		= IMG_FMT_XRGB8888,
		.colplanes	= 1,
		.flags		= FMT_FL_S3C24XX_PREVIEW |
				  FMT_FL_S3C64XX,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_BGR666,
		.depth		= 32,
		.ybpp		= 4,
		.color		= IMG_FMT_RGB666,
		.colplanes	= 1,
		.flags		= FMT_FL_S3C64XX,
	पूर्ण
पूर्ण;

/**
 * s3c_camअगर_find_क्रमmat() - lookup camअगर color क्रमmat by fourcc or an index
 * @vp: video path (DMA) description (codec/preview)
 * @pixelक्रमmat: fourcc to match, ignored अगर null
 * @index: index to the camअगर_क्रमmats array, ignored अगर negative
 */
स्थिर काष्ठा camअगर_fmt *s3c_camअगर_find_क्रमmat(काष्ठा camअगर_vp *vp,
					      स्थिर u32 *pixelक्रमmat,
					      पूर्णांक index)
अणु
	स्थिर काष्ठा camअगर_fmt *fmt, *def_fmt = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक id = 0;

	अगर (index >= (पूर्णांक)ARRAY_SIZE(camअगर_क्रमmats))
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(camअगर_क्रमmats); ++i) अणु
		fmt = &camअगर_क्रमmats[i];
		अगर (vp && !(vp->fmt_flags & fmt->flags))
			जारी;
		अगर (pixelक्रमmat && fmt->fourcc == *pixelक्रमmat)
			वापस fmt;
		अगर (index == id)
			def_fmt = fmt;
		id++;
	पूर्ण
	वापस def_fmt;
पूर्ण

अटल पूर्णांक camअगर_get_scaler_factor(u32 src, u32 tar, u32 *ratio, u32 *shअगरt)
अणु
	अचिन्हित पूर्णांक sh = 6;

	अगर (src >= 64 * tar)
		वापस -EINVAL;

	जबतक (sh--) अणु
		अचिन्हित पूर्णांक पंचांगp = 1 << sh;
		अगर (src >= tar * पंचांगp) अणु
			*shअगरt = sh;
			*ratio = पंचांगp;
			वापस 0;
		पूर्ण
	पूर्ण
	*shअगरt = 0;
	*ratio = 1;
	वापस 0;
पूर्ण

पूर्णांक s3c_camअगर_get_scaler_config(काष्ठा camअगर_vp *vp,
				काष्ठा camअगर_scaler *scaler)
अणु
	काष्ठा v4l2_rect *camअगर_crop = &vp->camअगर->camअगर_crop;
	पूर्णांक source_x = camअगर_crop->width;
	पूर्णांक source_y = camअगर_crop->height;
	पूर्णांक target_x = vp->out_frame.rect.width;
	पूर्णांक target_y = vp->out_frame.rect.height;
	पूर्णांक ret;

	अगर (vp->rotation == 90 || vp->rotation == 270)
		swap(target_x, target_y);

	ret = camअगर_get_scaler_factor(source_x, target_x, &scaler->pre_h_ratio,
				      &scaler->h_shअगरt);
	अगर (ret < 0)
		वापस ret;

	ret = camअगर_get_scaler_factor(source_y, target_y, &scaler->pre_v_ratio,
				      &scaler->v_shअगरt);
	अगर (ret < 0)
		वापस ret;

	scaler->pre_dst_width = source_x / scaler->pre_h_ratio;
	scaler->pre_dst_height = source_y / scaler->pre_v_ratio;

	scaler->मुख्य_h_ratio = (source_x << 8) / (target_x << scaler->h_shअगरt);
	scaler->मुख्य_v_ratio = (source_y << 8) / (target_y << scaler->v_shअगरt);

	scaler->scaleup_h = (target_x >= source_x);
	scaler->scaleup_v = (target_y >= source_y);

	scaler->copy = 0;

	pr_debug("H: ratio: %u, shift: %u. V: ratio: %u, shift: %u.\n",
		 scaler->pre_h_ratio, scaler->h_shअगरt,
		 scaler->pre_v_ratio, scaler->v_shअगरt);

	pr_debug("Source: %dx%d, Target: %dx%d, scaleup_h/v: %d/%d\n",
		 source_x, source_y, target_x, target_y,
		 scaler->scaleup_h, scaler->scaleup_v);

	वापस 0;
पूर्ण

अटल पूर्णांक camअगर_रेजिस्टर_sensor(काष्ठा camअगर_dev *camअगर)
अणु
	काष्ठा s3c_camअगर_sensor_info *sensor = &camअगर->pdata.sensor;
	काष्ठा v4l2_device *v4l2_dev = &camअगर->v4l2_dev;
	काष्ठा i2c_adapter *adapter;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	camअगर->sensor.sd = शून्य;

	अगर (sensor->i2c_board_info.addr == 0)
		वापस -EINVAL;

	adapter = i2c_get_adapter(sensor->i2c_bus_num);
	अगर (adapter == शून्य) अणु
		v4l2_warn(v4l2_dev, "failed to get I2C adapter %d\n",
			  sensor->i2c_bus_num);
		वापस -EPROBE_DEFER;
	पूर्ण

	sd = v4l2_i2c_new_subdev_board(v4l2_dev, adapter,
				       &sensor->i2c_board_info, शून्य);
	अगर (sd == शून्य) अणु
		i2c_put_adapter(adapter);
		v4l2_warn(v4l2_dev, "failed to acquire subdev %s\n",
			  sensor->i2c_board_info.type);
		वापस -EPROBE_DEFER;
	पूर्ण
	camअगर->sensor.sd = sd;

	v4l2_info(v4l2_dev, "registered sensor subdevice %s\n", sd->name);

	/* Get initial pixel क्रमmat and set it at the camअगर sink pad */
	क्रमmat.pad = 0;
	क्रमmat.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(sd, pad, get_fmt, शून्य, &क्रमmat);

	अगर (ret < 0)
		वापस 0;

	क्रमmat.pad = CAMIF_SD_PAD_SINK;
	v4l2_subdev_call(&camअगर->subdev, pad, set_fmt, शून्य, &क्रमmat);

	v4l2_info(sd, "Initial format from sensor: %dx%d, %#x\n",
		  क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height,
		  क्रमmat.क्रमmat.code);
	वापस 0;
पूर्ण

अटल व्योम camअगर_unरेजिस्टर_sensor(काष्ठा camअगर_dev *camअगर)
अणु
	काष्ठा v4l2_subdev *sd = camअगर->sensor.sd;
	काष्ठा i2c_client *client = sd ? v4l2_get_subdevdata(sd) : शून्य;
	काष्ठा i2c_adapter *adapter;

	अगर (client == शून्य)
		वापस;

	adapter = client->adapter;
	v4l2_device_unरेजिस्टर_subdev(sd);
	camअगर->sensor.sd = शून्य;
	i2c_unरेजिस्टर_device(client);
	i2c_put_adapter(adapter);
पूर्ण

अटल पूर्णांक camअगर_create_media_links(काष्ठा camअगर_dev *camअगर)
अणु
	पूर्णांक i, ret;

	ret = media_create_pad_link(&camअगर->sensor.sd->entity, 0,
				&camअगर->subdev.entity, CAMIF_SD_PAD_SINK,
				MEDIA_LNK_FL_IMMUTABLE |
				MEDIA_LNK_FL_ENABLED);
	अगर (ret)
		वापस ret;

	क्रम (i = 1; i < CAMIF_SD_PADS_NUM && !ret; i++) अणु
		ret = media_create_pad_link(&camअगर->subdev.entity, i,
				&camअगर->vp[i - 1].vdev.entity, 0,
				MEDIA_LNK_FL_IMMUTABLE |
				MEDIA_LNK_FL_ENABLED);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक camअगर_रेजिस्टर_video_nodes(काष्ठा camअगर_dev *camअगर)
अणु
	पूर्णांक ret = s3c_camअगर_रेजिस्टर_video_node(camअगर, VP_CODEC);
	अगर (ret < 0)
		वापस ret;

	वापस s3c_camअगर_रेजिस्टर_video_node(camअगर, VP_PREVIEW);
पूर्ण

अटल व्योम camअगर_unरेजिस्टर_video_nodes(काष्ठा camअगर_dev *camअगर)
अणु
	s3c_camअगर_unरेजिस्टर_video_node(camअगर, VP_CODEC);
	s3c_camअगर_unरेजिस्टर_video_node(camअगर, VP_PREVIEW);
पूर्ण

अटल व्योम camअगर_unरेजिस्टर_media_entities(काष्ठा camअगर_dev *camअगर)
अणु
	camअगर_unरेजिस्टर_video_nodes(camअगर);
	camअगर_unरेजिस्टर_sensor(camअगर);
	s3c_camअगर_unरेजिस्टर_subdev(camअगर);
पूर्ण

/*
 * Media device
 */
अटल पूर्णांक camअगर_media_dev_init(काष्ठा camअगर_dev *camअगर)
अणु
	काष्ठा media_device *md = &camअगर->media_dev;
	काष्ठा v4l2_device *v4l2_dev = &camअगर->v4l2_dev;
	अचिन्हित पूर्णांक ip_rev = camअगर->variant->ip_revision;
	पूर्णांक ret;

	स_रखो(md, 0, माप(*md));
	snम_लिखो(md->model, माप(md->model), "Samsung S3C%s CAMIF",
		 ip_rev == S3C6410_CAMIF_IP_REV ? "6410" : "244X");
	strscpy(md->bus_info, "platform", माप(md->bus_info));
	md->hw_revision = ip_rev;

	md->dev = camअगर->dev;

	strscpy(v4l2_dev->name, "s3c-camif", माप(v4l2_dev->name));
	v4l2_dev->mdev = md;

	media_device_init(md);

	ret = v4l2_device_रेजिस्टर(camअगर->dev, v4l2_dev);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल व्योम camअगर_clk_put(काष्ठा camअगर_dev *camअगर)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CLK_MAX_NUM; i++) अणु
		अगर (IS_ERR(camअगर->घड़ी[i]))
			जारी;
		clk_unprepare(camअगर->घड़ी[i]);
		clk_put(camअगर->घड़ी[i]);
		camअगर->घड़ी[i] = ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक camअगर_clk_get(काष्ठा camअगर_dev *camअगर)
अणु
	पूर्णांक ret, i;

	क्रम (i = 1; i < CLK_MAX_NUM; i++)
		camअगर->घड़ी[i] = ERR_PTR(-EINVAL);

	क्रम (i = 0; i < CLK_MAX_NUM; i++) अणु
		camअगर->घड़ी[i] = clk_get(camअगर->dev, camअगर_घड़ीs[i]);
		अगर (IS_ERR(camअगर->घड़ी[i])) अणु
			ret = PTR_ERR(camअगर->घड़ी[i]);
			जाओ err;
		पूर्ण
		ret = clk_prepare(camअगर->घड़ी[i]);
		अगर (ret < 0) अणु
			clk_put(camअगर->घड़ी[i]);
			camअगर->घड़ी[i] = शून्य;
			जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;
err:
	camअगर_clk_put(camअगर);
	dev_err(camअगर->dev, "failed to get clock: %s\n",
		camअगर_घड़ीs[i]);
	वापस ret;
पूर्ण

/*
 * The CAMIF device has two relatively independent data processing paths
 * that can source data from memory or the common camera input frontend.
 * Register पूर्णांकerrupts क्रम each data processing path (camअगर_vp).
 */
अटल पूर्णांक camअगर_request_irqs(काष्ठा platक्रमm_device *pdev,
			      काष्ठा camअगर_dev *camअगर)
अणु
	पूर्णांक irq, ret, i;

	क्रम (i = 0; i < CAMIF_VP_NUM; i++) अणु
		काष्ठा camअगर_vp *vp = &camअगर->vp[i];

		init_रुकोqueue_head(&vp->irq_queue);

		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq <= 0)
			वापस -ENXIO;

		ret = devm_request_irq(&pdev->dev, irq, s3c_camअगर_irq_handler,
				       0, dev_name(&pdev->dev), vp);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to install IRQ: %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s3c_camअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा s3c_camअगर_plat_data *pdata = dev->platक्रमm_data;
	काष्ठा s3c_camअगर_drvdata *drvdata;
	काष्ठा camअगर_dev *camअगर;
	काष्ठा resource *mres;
	पूर्णांक ret = 0;

	camअगर = devm_kzalloc(dev, माप(*camअगर), GFP_KERNEL);
	अगर (!camअगर)
		वापस -ENOMEM;

	spin_lock_init(&camअगर->slock);
	mutex_init(&camअगर->lock);

	camअगर->dev = dev;

	अगर (!pdata || !pdata->gpio_get || !pdata->gpio_put) अणु
		dev_err(dev, "wrong platform data\n");
		वापस -EINVAL;
	पूर्ण

	camअगर->pdata = *pdata;
	drvdata = (व्योम *)platक्रमm_get_device_id(pdev)->driver_data;
	camअगर->variant = drvdata->variant;

	mres = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	camअगर->io_base = devm_ioremap_resource(dev, mres);
	अगर (IS_ERR(camअगर->io_base))
		वापस PTR_ERR(camअगर->io_base);

	ret = camअगर_request_irqs(pdev, camअगर);
	अगर (ret < 0)
		वापस ret;

	ret = pdata->gpio_get();
	अगर (ret < 0)
		वापस ret;

	ret = s3c_camअगर_create_subdev(camअगर);
	अगर (ret < 0)
		जाओ err_sd;

	ret = camअगर_clk_get(camअगर);
	अगर (ret < 0)
		जाओ err_clk;

	platक्रमm_set_drvdata(pdev, camअगर);
	clk_set_rate(camअगर->घड़ी[CLK_CAM],
			camअगर->pdata.sensor.घड़ी_frequency);

	dev_info(dev, "sensor clock frequency: %lu\n",
		 clk_get_rate(camअगर->घड़ी[CLK_CAM]));
	/*
	 * Set initial pixel क्रमmat, resolution and crop rectangle.
	 * Must be करोne beक्रमe a sensor subdev is रेजिस्टरed as some
	 * settings are overrode with values from sensor subdev.
	 */
	s3c_camअगर_set_शेषs(camअगर);

	pm_runसमय_enable(dev);

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ err_pm;

	ret = camअगर_media_dev_init(camअगर);
	अगर (ret < 0)
		जाओ err_pm;

	ret = camअगर_रेजिस्टर_sensor(camअगर);
	अगर (ret < 0)
		जाओ err_sens;

	ret = v4l2_device_रेजिस्टर_subdev(&camअगर->v4l2_dev, &camअगर->subdev);
	अगर (ret < 0)
		जाओ err_sens;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&camअगर->v4l2_dev);
	अगर (ret < 0)
		जाओ err_sens;

	ret = camअगर_रेजिस्टर_video_nodes(camअगर);
	अगर (ret < 0)
		जाओ err_sens;

	ret = camअगर_create_media_links(camअगर);
	अगर (ret < 0)
		जाओ err_sens;

	ret = media_device_रेजिस्टर(&camअगर->media_dev);
	अगर (ret < 0)
		जाओ err_sens;

	pm_runसमय_put(dev);
	वापस 0;

err_sens:
	v4l2_device_unरेजिस्टर(&camअगर->v4l2_dev);
	media_device_unरेजिस्टर(&camअगर->media_dev);
	media_device_cleanup(&camअगर->media_dev);
	camअगर_unरेजिस्टर_media_entities(camअगर);
err_pm:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);
	camअगर_clk_put(camअगर);
err_clk:
	s3c_camअगर_unरेजिस्टर_subdev(camअगर);
err_sd:
	pdata->gpio_put();
	वापस ret;
पूर्ण

अटल पूर्णांक s3c_camअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा camअगर_dev *camअगर = platक्रमm_get_drvdata(pdev);
	काष्ठा s3c_camअगर_plat_data *pdata = &camअगर->pdata;

	media_device_unरेजिस्टर(&camअगर->media_dev);
	media_device_cleanup(&camअगर->media_dev);
	camअगर_unरेजिस्टर_media_entities(camअगर);
	v4l2_device_unरेजिस्टर(&camअगर->v4l2_dev);

	pm_runसमय_disable(&pdev->dev);
	camअगर_clk_put(camअगर);
	pdata->gpio_put();

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा camअगर_dev *camअगर = dev_get_drvdata(dev);

	clk_enable(camअगर->घड़ी[CLK_GATE]);
	/* null op on s3c244x */
	clk_enable(camअगर->घड़ी[CLK_CAM]);
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_camअगर_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा camअगर_dev *camअगर = dev_get_drvdata(dev);

	/* null op on s3c244x */
	clk_disable(camअगर->घड़ी[CLK_CAM]);

	clk_disable(camअगर->घड़ी[CLK_GATE]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा s3c_camअगर_variant s3c244x_camअगर_variant = अणु
	.vp_pix_limits = अणु
		[VP_CODEC] = अणु
			.max_out_width		= 4096,
			.max_sc_out_width	= 2048,
			.out_width_align	= 16,
			.min_out_width		= 16,
			.max_height		= 4096,
		पूर्ण,
		[VP_PREVIEW] = अणु
			.max_out_width		= 640,
			.max_sc_out_width	= 640,
			.out_width_align	= 16,
			.min_out_width		= 16,
			.max_height		= 480,
		पूर्ण
	पूर्ण,
	.pix_limits = अणु
		.win_hor_offset_align	= 8,
	पूर्ण,
	.ip_revision = S3C244X_CAMIF_IP_REV,
पूर्ण;

अटल काष्ठा s3c_camअगर_drvdata s3c244x_camअगर_drvdata = अणु
	.variant	= &s3c244x_camअगर_variant,
	.bus_clk_freq	= 24000000UL,
पूर्ण;

अटल स्थिर काष्ठा s3c_camअगर_variant s3c6410_camअगर_variant = अणु
	.vp_pix_limits = अणु
		[VP_CODEC] = अणु
			.max_out_width		= 4096,
			.max_sc_out_width	= 2048,
			.out_width_align	= 16,
			.min_out_width		= 16,
			.max_height		= 4096,
		पूर्ण,
		[VP_PREVIEW] = अणु
			.max_out_width		= 4096,
			.max_sc_out_width	= 720,
			.out_width_align	= 16,
			.min_out_width		= 16,
			.max_height		= 4096,
		पूर्ण
	पूर्ण,
	.pix_limits = अणु
		.win_hor_offset_align	= 8,
	पूर्ण,
	.ip_revision = S3C6410_CAMIF_IP_REV,
	.has_img_effect = 1,
	.vp_offset = 0x20,
पूर्ण;

अटल काष्ठा s3c_camअगर_drvdata s3c6410_camअगर_drvdata = अणु
	.variant	= &s3c6410_camअगर_variant,
	.bus_clk_freq	= 133000000UL,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id s3c_camअगर_driver_ids[] = अणु
	अणु
		.name		= "s3c2440-camif",
		.driver_data	= (अचिन्हित दीर्घ)&s3c244x_camअगर_drvdata,
	पूर्ण, अणु
		.name		= "s3c6410-camif",
		.driver_data	= (अचिन्हित दीर्घ)&s3c6410_camअगर_drvdata,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3c_camअगर_driver_ids);

अटल स्थिर काष्ठा dev_pm_ops s3c_camअगर_pm_ops = अणु
	.runसमय_suspend	= s3c_camअगर_runसमय_suspend,
	.runसमय_resume		= s3c_camअगर_runसमय_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver s3c_camअगर_driver = अणु
	.probe		= s3c_camअगर_probe,
	.हटाओ		= s3c_camअगर_हटाओ,
	.id_table	= s3c_camअगर_driver_ids,
	.driver = अणु
		.name	= S3C_CAMIF_DRIVER_NAME,
		.pm	= &s3c_camअगर_pm_ops,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(s3c_camअगर_driver);

MODULE_AUTHOR("Sylwester Nawrocki <sylvester.nawrocki@gmail.com>");
MODULE_AUTHOR("Tomasz Figa <tomasz.figa@gmail.com>");
MODULE_DESCRIPTION("S3C24XX/S3C64XX SoC camera interface driver");
MODULE_LICENSE("GPL");
