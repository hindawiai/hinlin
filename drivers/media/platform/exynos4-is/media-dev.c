<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * S5P/EXYNOS4 SoC series camera host पूर्णांकerface media device driver
 *
 * Copyright (C) 2011 - 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/media-device.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

#समावेश "media-dev.h"
#समावेश "fimc-core.h"
#समावेश "fimc-is.h"
#समावेश "fimc-lite.h"
#समावेश "mipi-csis.h"

/* Set up image sensor subdev -> FIMC capture node notअगरications. */
अटल व्योम __setup_sensor_notअगरication(काष्ठा fimc_md *fmd,
					काष्ठा v4l2_subdev *sensor,
					काष्ठा v4l2_subdev *fimc_sd)
अणु
	काष्ठा fimc_source_info *src_inf;
	काष्ठा fimc_sensor_info *md_si;
	अचिन्हित दीर्घ flags;

	src_inf = v4l2_get_subdev_hostdata(sensor);
	अगर (!src_inf || WARN_ON(fmd == शून्य))
		वापस;

	md_si = source_to_sensor_info(src_inf);
	spin_lock_irqsave(&fmd->slock, flags);
	md_si->host = v4l2_get_subdevdata(fimc_sd);
	spin_unlock_irqrestore(&fmd->slock, flags);
पूर्ण

/**
 * fimc_pipeline_prepare - update pipeline inक्रमmation with subdevice poपूर्णांकers
 * @p: fimc pipeline
 * @me: media entity terminating the pipeline
 *
 * Caller holds the graph mutex.
 */
अटल व्योम fimc_pipeline_prepare(काष्ठा fimc_pipeline *p,
					काष्ठा media_entity *me)
अणु
	काष्ठा fimc_md *fmd = entity_to_fimc_mdev(me);
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_subdev *sensor = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < IDX_MAX; i++)
		p->subdevs[i] = शून्य;

	जबतक (1) अणु
		काष्ठा media_pad *pad = शून्य;

		/* Find remote source pad */
		क्रम (i = 0; i < me->num_pads; i++) अणु
			काष्ठा media_pad *spad = &me->pads[i];
			अगर (!(spad->flags & MEDIA_PAD_FL_SINK))
				जारी;
			pad = media_entity_remote_pad(spad);
			अगर (pad)
				अवरोध;
		पूर्ण

		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;
		sd = media_entity_to_v4l2_subdev(pad->entity);

		चयन (sd->grp_id) अणु
		हाल GRP_ID_SENSOR:
			sensor = sd;
			fallthrough;
		हाल GRP_ID_FIMC_IS_SENSOR:
			p->subdevs[IDX_SENSOR] = sd;
			अवरोध;
		हाल GRP_ID_CSIS:
			p->subdevs[IDX_CSIS] = sd;
			अवरोध;
		हाल GRP_ID_FLITE:
			p->subdevs[IDX_FLITE] = sd;
			अवरोध;
		हाल GRP_ID_FIMC:
			p->subdevs[IDX_FIMC] = sd;
			अवरोध;
		हाल GRP_ID_FIMC_IS:
			p->subdevs[IDX_IS_ISP] = sd;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		me = &sd->entity;
		अगर (me->num_pads == 1)
			अवरोध;
	पूर्ण

	अगर (sensor && p->subdevs[IDX_FIMC])
		__setup_sensor_notअगरication(fmd, sensor, p->subdevs[IDX_FIMC]);
पूर्ण

/**
 * __subdev_set_घातer - change घातer state of a single subdev
 * @sd: subdevice to change घातer state क्रम
 * @on: 1 to enable घातer or 0 to disable
 *
 * Return result of s_घातer subdev operation or -ENXIO अगर sd argument
 * is शून्य. Return 0 अगर the subdevice करोes not implement s_घातer.
 */
अटल पूर्णांक __subdev_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	पूर्णांक *use_count;
	पूर्णांक ret;

	अगर (sd == शून्य)
		वापस -ENXIO;

	use_count = &sd->entity.use_count;
	अगर (on && (*use_count)++ > 0)
		वापस 0;
	अन्यथा अगर (!on && (*use_count == 0 || --(*use_count) > 0))
		वापस 0;
	ret = v4l2_subdev_call(sd, core, s_घातer, on);

	वापस ret != -ENOIOCTLCMD ? ret : 0;
पूर्ण

/**
 * fimc_pipeline_s_घातer - change घातer state of all pipeline subdevs
 * @p: fimc device terminating the pipeline
 * @on: true to घातer on, false to घातer off
 *
 * Needs to be called with the graph mutex held.
 */
अटल पूर्णांक fimc_pipeline_s_घातer(काष्ठा fimc_pipeline *p, bool on)
अणु
	अटल स्थिर u8 seq[2][IDX_MAX - 1] = अणु
		अणु IDX_IS_ISP, IDX_SENSOR, IDX_CSIS, IDX_FLITE पूर्ण,
		अणु IDX_CSIS, IDX_FLITE, IDX_SENSOR, IDX_IS_ISP पूर्ण,
	पूर्ण;
	पूर्णांक i, ret = 0;

	अगर (p->subdevs[IDX_SENSOR] == शून्य)
		वापस -ENXIO;

	क्रम (i = 0; i < IDX_MAX - 1; i++) अणु
		अचिन्हित पूर्णांक idx = seq[on][i];

		ret = __subdev_set_घातer(p->subdevs[idx], on);


		अगर (ret < 0 && ret != -ENXIO)
			जाओ error;
	पूर्ण
	वापस 0;
error:
	क्रम (; i >= 0; i--) अणु
		अचिन्हित पूर्णांक idx = seq[on][i];
		__subdev_set_घातer(p->subdevs[idx], !on);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * __fimc_pipeline_enable - enable घातer of all pipeline subdevs
 *			    and the sensor घड़ी
 * @ep: video pipeline काष्ठाure
 * @fmd: fimc media device
 *
 * Called with the graph mutex held.
 */
अटल पूर्णांक __fimc_pipeline_enable(काष्ठा exynos_media_pipeline *ep,
				  काष्ठा fimc_md *fmd)
अणु
	काष्ठा fimc_pipeline *p = to_fimc_pipeline(ep);
	पूर्णांक ret;

	/* Enable PXLASYNC घड़ी अगर this pipeline includes FIMC-IS */
	अगर (!IS_ERR(fmd->wbclk[CLK_IDX_WB_B]) && p->subdevs[IDX_IS_ISP]) अणु
		ret = clk_prepare_enable(fmd->wbclk[CLK_IDX_WB_B]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = fimc_pipeline_s_घातer(p, 1);
	अगर (!ret)
		वापस 0;

	अगर (!IS_ERR(fmd->wbclk[CLK_IDX_WB_B]) && p->subdevs[IDX_IS_ISP])
		clk_disable_unprepare(fmd->wbclk[CLK_IDX_WB_B]);

	वापस ret;
पूर्ण

/**
 * __fimc_pipeline_खोलो - update the pipeline inक्रमmation, enable घातer
 *                        of all pipeline subdevs and the sensor घड़ी
 * @ep: fimc device terminating the pipeline
 * @me: media entity to start graph walk with
 * @prepare: true to walk the current pipeline and acquire all subdevs
 *
 * Called with the graph mutex held.
 */
अटल पूर्णांक __fimc_pipeline_खोलो(काष्ठा exynos_media_pipeline *ep,
				काष्ठा media_entity *me, bool prepare)
अणु
	काष्ठा fimc_md *fmd = entity_to_fimc_mdev(me);
	काष्ठा fimc_pipeline *p = to_fimc_pipeline(ep);
	काष्ठा v4l2_subdev *sd;

	अगर (WARN_ON(p == शून्य || me == शून्य))
		वापस -EINVAL;

	अगर (prepare)
		fimc_pipeline_prepare(p, me);

	sd = p->subdevs[IDX_SENSOR];
	अगर (sd == शून्य) अणु
		pr_warn("%s(): No sensor subdev\n", __func__);
		/*
		 * Pipeline खोलो cannot fail so as to make it possible
		 * क्रम the user space to configure the pipeline.
		 */
		वापस 0;
	पूर्ण

	वापस __fimc_pipeline_enable(ep, fmd);
पूर्ण

/**
 * __fimc_pipeline_बंद - disable the sensor घड़ी and pipeline घातer
 * @ep: fimc device terminating the pipeline
 *
 * Disable घातer of all subdevs and turn the बाह्यal sensor घड़ी off.
 */
अटल पूर्णांक __fimc_pipeline_बंद(काष्ठा exynos_media_pipeline *ep)
अणु
	काष्ठा fimc_pipeline *p = to_fimc_pipeline(ep);
	काष्ठा v4l2_subdev *sd = p ? p->subdevs[IDX_SENSOR] : शून्य;
	काष्ठा fimc_md *fmd;
	पूर्णांक ret;

	अगर (sd == शून्य) अणु
		pr_warn("%s(): No sensor subdev\n", __func__);
		वापस 0;
	पूर्ण

	ret = fimc_pipeline_s_घातer(p, 0);

	fmd = entity_to_fimc_mdev(&sd->entity);

	/* Disable PXLASYNC घड़ी अगर this pipeline includes FIMC-IS */
	अगर (!IS_ERR(fmd->wbclk[CLK_IDX_WB_B]) && p->subdevs[IDX_IS_ISP])
		clk_disable_unprepare(fmd->wbclk[CLK_IDX_WB_B]);

	वापस ret == -ENXIO ? 0 : ret;
पूर्ण

/**
 * __fimc_pipeline_s_stream - call s_stream() on pipeline subdevs
 * @ep: video pipeline काष्ठाure
 * @on: passed as the s_stream() callback argument
 */
अटल पूर्णांक __fimc_pipeline_s_stream(काष्ठा exynos_media_pipeline *ep, bool on)
अणु
	अटल स्थिर u8 seq[2][IDX_MAX] = अणु
		अणु IDX_FIMC, IDX_SENSOR, IDX_IS_ISP, IDX_CSIS, IDX_FLITE पूर्ण,
		अणु IDX_CSIS, IDX_FLITE, IDX_FIMC, IDX_SENSOR, IDX_IS_ISP पूर्ण,
	पूर्ण;
	काष्ठा fimc_pipeline *p = to_fimc_pipeline(ep);
	क्रमागत fimc_subdev_index sd_id;
	पूर्णांक i, ret = 0;

	अगर (p->subdevs[IDX_SENSOR] == शून्य) अणु
		काष्ठा fimc_md *fmd;
		काष्ठा v4l2_subdev *sd = p->subdevs[IDX_CSIS];

		अगर (!sd)
			sd = p->subdevs[IDX_FIMC];

		अगर (!sd) अणु
			/*
			 * If neither CSIS nor FIMC was set up,
			 * it's impossible to have any sensors
			 */
			वापस -ENODEV;
		पूर्ण

		fmd = entity_to_fimc_mdev(&sd->entity);

		अगर (!fmd->user_subdev_api) अणु
			/*
			 * Sensor must be alपढ़ोy discovered अगर we
			 * aren't in the user_subdev_api mode
			 */
			वापस -ENODEV;
		पूर्ण

		/* Get pipeline sink entity */
		अगर (p->subdevs[IDX_FIMC])
			sd_id = IDX_FIMC;
		अन्यथा अगर (p->subdevs[IDX_IS_ISP])
			sd_id = IDX_IS_ISP;
		अन्यथा अगर (p->subdevs[IDX_FLITE])
			sd_id = IDX_FLITE;
		अन्यथा
			वापस -ENODEV;

		/*
		 * Sensor could have been linked between खोलो and STREAMON -
		 * check अगर this is the हाल.
		 */
		fimc_pipeline_prepare(p, &p->subdevs[sd_id]->entity);

		अगर (p->subdevs[IDX_SENSOR] == शून्य)
			वापस -ENODEV;

		ret = __fimc_pipeline_enable(ep, fmd);
		अगर (ret < 0)
			वापस ret;

	पूर्ण

	क्रम (i = 0; i < IDX_MAX; i++) अणु
		अचिन्हित पूर्णांक idx = seq[on][i];

		ret = v4l2_subdev_call(p->subdevs[idx], video, s_stream, on);

		अगर (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV)
			जाओ error;
	पूर्ण

	वापस 0;
error:
	fimc_pipeline_s_घातer(p, !on);
	क्रम (; i >= 0; i--) अणु
		अचिन्हित पूर्णांक idx = seq[on][i];
		v4l2_subdev_call(p->subdevs[idx], video, s_stream, !on);
	पूर्ण
	वापस ret;
पूर्ण

/* Media pipeline operations क्रम the FIMC/FIMC-LITE video device driver */
अटल स्थिर काष्ठा exynos_media_pipeline_ops fimc_pipeline_ops = अणु
	.खोलो		= __fimc_pipeline_खोलो,
	.बंद		= __fimc_pipeline_बंद,
	.set_stream	= __fimc_pipeline_s_stream,
पूर्ण;

अटल काष्ठा exynos_media_pipeline *fimc_md_pipeline_create(
						काष्ठा fimc_md *fmd)
अणु
	काष्ठा fimc_pipeline *p;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	list_add_tail(&p->list, &fmd->pipelines);

	p->ep.ops = &fimc_pipeline_ops;
	वापस &p->ep;
पूर्ण

अटल व्योम fimc_md_pipelines_मुक्त(काष्ठा fimc_md *fmd)
अणु
	जबतक (!list_empty(&fmd->pipelines)) अणु
		काष्ठा fimc_pipeline *p;

		p = list_entry(fmd->pipelines.next, typeof(*p), list);
		list_del(&p->list);
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल पूर्णांक fimc_md_parse_one_endpoपूर्णांक(काष्ठा fimc_md *fmd,
				   काष्ठा device_node *ep)
अणु
	पूर्णांक index = fmd->num_sensors;
	काष्ठा fimc_source_info *pd = &fmd->sensor[index].pdata;
	काष्ठा device_node *rem, *np;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा v4l2_fwnode_endpoपूर्णांक endpoपूर्णांक = अणु .bus_type = 0 पूर्ण;
	पूर्णांक ret;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep), &endpoपूर्णांक);
	अगर (ret) अणु
		of_node_put(ep);
		वापस ret;
	पूर्ण

	अगर (WARN_ON(endpoपूर्णांक.base.port == 0) || index >= FIMC_MAX_SENSORS) अणु
		of_node_put(ep);
		वापस -EINVAL;
	पूर्ण

	pd->mux_id = (endpoपूर्णांक.base.port - 1) & 0x1;

	rem = of_graph_get_remote_port_parent(ep);
	अगर (rem == शून्य) अणु
		v4l2_info(&fmd->v4l2_dev, "Remote device at %pOF not found\n",
							ep);
		of_node_put(ep);
		वापस 0;
	पूर्ण

	अगर (fimc_input_is_parallel(endpoपूर्णांक.base.port)) अणु
		अगर (endpoपूर्णांक.bus_type == V4L2_MBUS_PARALLEL)
			pd->sensor_bus_type = FIMC_BUS_TYPE_ITU_601;
		अन्यथा
			pd->sensor_bus_type = FIMC_BUS_TYPE_ITU_656;
		pd->flags = endpoपूर्णांक.bus.parallel.flags;
	पूर्ण अन्यथा अगर (fimc_input_is_mipi_csi(endpoपूर्णांक.base.port)) अणु
		/*
		 * MIPI CSI-2: only input mux selection and
		 * the sensor's घड़ी frequency is needed.
		 */
		pd->sensor_bus_type = FIMC_BUS_TYPE_MIPI_CSI2;
	पूर्ण अन्यथा अणु
		v4l2_err(&fmd->v4l2_dev, "Wrong port id (%u) at node %pOF\n",
			 endpoपूर्णांक.base.port, rem);
	पूर्ण
	/*
	 * For FIMC-IS handled sensors, that are placed under i2c-isp device
	 * node, FIMC is connected to the FIMC-IS through its ISP Writeback
	 * input. Sensors are attached to the FIMC-LITE hostdata पूर्णांकerface
	 * directly or through MIPI-CSIS, depending on the बाह्यal media bus
	 * used. This needs to be handled in a more reliable way, not by just
	 * checking parent's node name.
	 */
	np = of_get_parent(rem);
	of_node_put(rem);

	अगर (of_node_name_eq(np, "i2c-isp"))
		pd->fimc_bus_type = FIMC_BUS_TYPE_ISP_WRITEBACK;
	अन्यथा
		pd->fimc_bus_type = pd->sensor_bus_type;
	of_node_put(np);

	अगर (WARN_ON(index >= ARRAY_SIZE(fmd->sensor))) अणु
		of_node_put(ep);
		वापस -EINVAL;
	पूर्ण

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
		&fmd->subdev_notअगरier, of_fwnode_handle(ep),
		काष्ठा v4l2_async_subdev);

	of_node_put(ep);

	अगर (IS_ERR(asd))
		वापस PTR_ERR(asd);

	fmd->sensor[index].asd = asd;
	fmd->num_sensors++;

	वापस 0;
पूर्ण

/* Parse port node and रेजिस्टर as a sub-device any sensor specअगरied there. */
अटल पूर्णांक fimc_md_parse_port_node(काष्ठा fimc_md *fmd,
				   काष्ठा device_node *port)
अणु
	काष्ठा device_node *ep;
	पूर्णांक ret;

	क्रम_each_child_of_node(port, ep) अणु
		ret = fimc_md_parse_one_endpoपूर्णांक(fmd, ep);
		अगर (ret < 0) अणु
			of_node_put(ep);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Register all SoC बाह्यal sub-devices */
अटल पूर्णांक fimc_md_रेजिस्टर_sensor_entities(काष्ठा fimc_md *fmd)
अणु
	काष्ठा device_node *parent = fmd->pdev->dev.of_node;
	काष्ठा device_node *ports = शून्य;
	काष्ठा device_node *node;
	पूर्णांक ret;

	/*
	 * Runसमय resume one of the FIMC entities to make sure
	 * the sclk_cam घड़ीs are not globally disabled.
	 */
	अगर (!fmd->pmf)
		वापस -ENXIO;

	ret = pm_runसमय_get_sync(fmd->pmf);
	अगर (ret < 0) अणु
		pm_runसमय_put(fmd->pmf);
		वापस ret;
	पूर्ण

	fmd->num_sensors = 0;

	/* Attach sensors linked to MIPI CSI-2 receivers */
	क्रम_each_available_child_of_node(parent, node) अणु
		काष्ठा device_node *port;

		अगर (!of_node_name_eq(node, "csis"))
			जारी;
		/* The csis node can have only port subnode. */
		port = of_get_next_child(node, शून्य);
		अगर (!port)
			जारी;

		ret = fimc_md_parse_port_node(fmd, port);
		of_node_put(port);
		अगर (ret < 0) अणु
			of_node_put(node);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/* Attach sensors listed in the parallel-ports node */
	ports = of_get_child_by_name(parent, "parallel-ports");
	अगर (!ports)
		जाओ rpm_put;

	क्रम_each_child_of_node(ports, node) अणु
		ret = fimc_md_parse_port_node(fmd, node);
		अगर (ret < 0) अणु
			of_node_put(node);
			जाओ cleanup;
		पूर्ण
	पूर्ण
	of_node_put(ports);

rpm_put:
	pm_runसमय_put(fmd->pmf);
	वापस 0;

cleanup:
	of_node_put(ports);
	v4l2_async_notअगरier_cleanup(&fmd->subdev_notअगरier);
	pm_runसमय_put(fmd->pmf);
	वापस ret;
पूर्ण

अटल पूर्णांक __of_get_csis_id(काष्ठा device_node *np)
अणु
	u32 reg = 0;

	np = of_get_child_by_name(np, "port");
	अगर (!np)
		वापस -EINVAL;
	of_property_पढ़ो_u32(np, "reg", &reg);
	of_node_put(np);
	वापस reg - FIMC_INPUT_MIPI_CSI2_0;
पूर्ण

/*
 * MIPI-CSIS, FIMC and FIMC-LITE platक्रमm devices registration.
 */
अटल पूर्णांक रेजिस्टर_fimc_lite_entity(काष्ठा fimc_md *fmd,
				     काष्ठा fimc_lite *fimc_lite)
अणु
	काष्ठा v4l2_subdev *sd;
	काष्ठा exynos_media_pipeline *ep;
	पूर्णांक ret;

	अगर (WARN_ON(fimc_lite->index >= FIMC_LITE_MAX_DEVS ||
		    fmd->fimc_lite[fimc_lite->index]))
		वापस -EBUSY;

	sd = &fimc_lite->subdev;
	sd->grp_id = GRP_ID_FLITE;

	ep = fimc_md_pipeline_create(fmd);
	अगर (!ep)
		वापस -ENOMEM;

	v4l2_set_subdev_hostdata(sd, ep);

	ret = v4l2_device_रेजिस्टर_subdev(&fmd->v4l2_dev, sd);
	अगर (!ret)
		fmd->fimc_lite[fimc_lite->index] = fimc_lite;
	अन्यथा
		v4l2_err(&fmd->v4l2_dev, "Failed to register FIMC.LITE%d\n",
			 fimc_lite->index);
	वापस ret;
पूर्ण

अटल पूर्णांक रेजिस्टर_fimc_entity(काष्ठा fimc_md *fmd, काष्ठा fimc_dev *fimc)
अणु
	काष्ठा v4l2_subdev *sd;
	काष्ठा exynos_media_pipeline *ep;
	पूर्णांक ret;

	अगर (WARN_ON(fimc->id >= FIMC_MAX_DEVS || fmd->fimc[fimc->id]))
		वापस -EBUSY;

	sd = &fimc->vid_cap.subdev;
	sd->grp_id = GRP_ID_FIMC;

	ep = fimc_md_pipeline_create(fmd);
	अगर (!ep)
		वापस -ENOMEM;

	v4l2_set_subdev_hostdata(sd, ep);

	ret = v4l2_device_रेजिस्टर_subdev(&fmd->v4l2_dev, sd);
	अगर (!ret) अणु
		अगर (!fmd->pmf && fimc->pdev)
			fmd->pmf = &fimc->pdev->dev;
		fmd->fimc[fimc->id] = fimc;
		fimc->vid_cap.user_subdev_api = fmd->user_subdev_api;
	पूर्ण अन्यथा अणु
		v4l2_err(&fmd->v4l2_dev, "Failed to register FIMC.%d (%d)\n",
			 fimc->id, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक रेजिस्टर_csis_entity(काष्ठा fimc_md *fmd,
				काष्ठा platक्रमm_device *pdev,
				काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक id, ret;

	id = node ? __of_get_csis_id(node) : max(0, pdev->id);

	अगर (WARN_ON(id < 0 || id >= CSIS_MAX_ENTITIES))
		वापस -ENOENT;

	अगर (WARN_ON(fmd->csis[id].sd))
		वापस -EBUSY;

	sd->grp_id = GRP_ID_CSIS;
	ret = v4l2_device_रेजिस्टर_subdev(&fmd->v4l2_dev, sd);
	अगर (!ret)
		fmd->csis[id].sd = sd;
	अन्यथा
		v4l2_err(&fmd->v4l2_dev,
			 "Failed to register MIPI-CSIS.%d (%d)\n", id, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक रेजिस्टर_fimc_is_entity(काष्ठा fimc_md *fmd, काष्ठा fimc_is *is)
अणु
	काष्ठा v4l2_subdev *sd = &is->isp.subdev;
	काष्ठा exynos_media_pipeline *ep;
	पूर्णांक ret;

	/* Allocate pipeline object क्रम the ISP capture video node. */
	ep = fimc_md_pipeline_create(fmd);
	अगर (!ep)
		वापस -ENOMEM;

	v4l2_set_subdev_hostdata(sd, ep);

	ret = v4l2_device_रेजिस्टर_subdev(&fmd->v4l2_dev, sd);
	अगर (ret) अणु
		v4l2_err(&fmd->v4l2_dev,
			 "Failed to register FIMC-ISP (%d)\n", ret);
		वापस ret;
	पूर्ण

	fmd->fimc_is = is;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_md_रेजिस्टर_platक्रमm_entity(काष्ठा fimc_md *fmd,
					    काष्ठा platक्रमm_device *pdev,
					    पूर्णांक plat_entity)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret = -EPROBE_DEFER;
	व्योम *drvdata;

	/* Lock to ensure dev->driver won't change. */
	device_lock(dev);

	अगर (!dev->driver || !try_module_get(dev->driver->owner))
		जाओ dev_unlock;

	drvdata = dev_get_drvdata(dev);
	/* Some subdev didn't probe successfully id drvdata is शून्य */
	अगर (drvdata) अणु
		चयन (plat_entity) अणु
		हाल IDX_FIMC:
			ret = रेजिस्टर_fimc_entity(fmd, drvdata);
			अवरोध;
		हाल IDX_FLITE:
			ret = रेजिस्टर_fimc_lite_entity(fmd, drvdata);
			अवरोध;
		हाल IDX_CSIS:
			ret = रेजिस्टर_csis_entity(fmd, pdev, drvdata);
			अवरोध;
		हाल IDX_IS_ISP:
			ret = रेजिस्टर_fimc_is_entity(fmd, drvdata);
			अवरोध;
		शेष:
			ret = -ENODEV;
		पूर्ण
	पूर्ण

	module_put(dev->driver->owner);
dev_unlock:
	device_unlock(dev);
	अगर (ret == -EPROBE_DEFER)
		dev_info(&fmd->pdev->dev, "deferring %s device registration\n",
			dev_name(dev));
	अन्यथा अगर (ret < 0)
		dev_err(&fmd->pdev->dev, "%s device registration failed (%d)\n",
			dev_name(dev), ret);
	वापस ret;
पूर्ण

/* Register FIMC, FIMC-LITE and CSIS media entities */
अटल पूर्णांक fimc_md_रेजिस्टर_platक्रमm_entities(काष्ठा fimc_md *fmd,
					      काष्ठा device_node *parent)
अणु
	काष्ठा device_node *node;
	पूर्णांक ret = 0;

	क्रम_each_available_child_of_node(parent, node) अणु
		काष्ठा platक्रमm_device *pdev;
		पूर्णांक plat_entity = -1;

		pdev = of_find_device_by_node(node);
		अगर (!pdev)
			जारी;

		/* If driver of any entity isn't पढ़ोy try all again later. */
		अगर (of_node_name_eq(node, CSIS_OF_NODE_NAME))
			plat_entity = IDX_CSIS;
		अन्यथा अगर (of_node_name_eq(node, FIMC_IS_OF_NODE_NAME))
			plat_entity = IDX_IS_ISP;
		अन्यथा अगर (of_node_name_eq(node, FIMC_LITE_OF_NODE_NAME))
			plat_entity = IDX_FLITE;
		अन्यथा अगर (of_node_name_eq(node, FIMC_OF_NODE_NAME) &&
			 !of_property_पढ़ो_bool(node, "samsung,lcd-wb"))
			plat_entity = IDX_FIMC;

		अगर (plat_entity >= 0)
			ret = fimc_md_रेजिस्टर_platक्रमm_entity(fmd, pdev,
							plat_entity);
		put_device(&pdev->dev);
		अगर (ret < 0) अणु
			of_node_put(node);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम fimc_md_unरेजिस्टर_entities(काष्ठा fimc_md *fmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < FIMC_MAX_DEVS; i++) अणु
		काष्ठा fimc_dev *dev = fmd->fimc[i];
		अगर (dev == शून्य)
			जारी;
		v4l2_device_unरेजिस्टर_subdev(&dev->vid_cap.subdev);
		dev->vid_cap.ve.pipe = शून्य;
		fmd->fimc[i] = शून्य;
	पूर्ण
	क्रम (i = 0; i < FIMC_LITE_MAX_DEVS; i++) अणु
		काष्ठा fimc_lite *dev = fmd->fimc_lite[i];
		अगर (dev == शून्य)
			जारी;
		v4l2_device_unरेजिस्टर_subdev(&dev->subdev);
		dev->ve.pipe = शून्य;
		fmd->fimc_lite[i] = शून्य;
	पूर्ण
	क्रम (i = 0; i < CSIS_MAX_ENTITIES; i++) अणु
		अगर (fmd->csis[i].sd == शून्य)
			जारी;
		v4l2_device_unरेजिस्टर_subdev(fmd->csis[i].sd);
		fmd->csis[i].sd = शून्य;
	पूर्ण

	अगर (fmd->fimc_is)
		v4l2_device_unरेजिस्टर_subdev(&fmd->fimc_is->isp.subdev);

	v4l2_info(&fmd->v4l2_dev, "Unregistered all entities\n");
पूर्ण

/**
 * __fimc_md_create_fimc_sink_links - create links to all FIMC entities
 * @fmd: fimc media device
 * @source: the source entity to create links to all fimc entities from
 * @sensor: sensor subdev linked to FIMC[fimc_id] entity, may be null
 * @pad: the source entity pad index
 * @link_mask: biपंचांगask of the fimc devices क्रम which link should be enabled
 */
अटल पूर्णांक __fimc_md_create_fimc_sink_links(काष्ठा fimc_md *fmd,
					    काष्ठा media_entity *source,
					    काष्ठा v4l2_subdev *sensor,
					    पूर्णांक pad, पूर्णांक link_mask)
अणु
	काष्ठा fimc_source_info *si = शून्य;
	काष्ठा media_entity *sink;
	अचिन्हित पूर्णांक flags = 0;
	पूर्णांक i, ret = 0;

	अगर (sensor) अणु
		si = v4l2_get_subdev_hostdata(sensor);
		/* Skip direct FIMC links in the logical FIMC-IS sensor path */
		अगर (si && si->fimc_bus_type == FIMC_BUS_TYPE_ISP_WRITEBACK)
			ret = 1;
	पूर्ण

	क्रम (i = 0; !ret && i < FIMC_MAX_DEVS; i++) अणु
		अगर (!fmd->fimc[i])
			जारी;
		/*
		 * Some FIMC variants are not fitted with camera capture
		 * पूर्णांकerface. Skip creating a link from sensor क्रम those.
		 */
		अगर (!fmd->fimc[i]->variant->has_cam_अगर)
			जारी;

		flags = ((1 << i) & link_mask) ? MEDIA_LNK_FL_ENABLED : 0;

		sink = &fmd->fimc[i]->vid_cap.subdev.entity;
		ret = media_create_pad_link(source, pad, sink,
					      FIMC_SD_PAD_SINK_CAM, flags);
		अगर (ret)
			वापस ret;

		/* Notअगरy FIMC capture subdev entity */
		ret = media_entity_call(sink, link_setup, &sink->pads[0],
					&source->pads[pad], flags);
		अगर (ret)
			अवरोध;

		v4l2_info(&fmd->v4l2_dev, "created link [%s] %c> [%s]\n",
			  source->name, flags ? '=' : '-', sink->name);
	पूर्ण

	क्रम (i = 0; i < FIMC_LITE_MAX_DEVS; i++) अणु
		अगर (!fmd->fimc_lite[i])
			जारी;

		sink = &fmd->fimc_lite[i]->subdev.entity;
		ret = media_create_pad_link(source, pad, sink,
					       FLITE_SD_PAD_SINK, 0);
		अगर (ret)
			वापस ret;

		/* Notअगरy FIMC-LITE subdev entity */
		ret = media_entity_call(sink, link_setup, &sink->pads[0],
					&source->pads[pad], 0);
		अगर (ret)
			अवरोध;

		v4l2_info(&fmd->v4l2_dev, "created link [%s] -> [%s]\n",
			  source->name, sink->name);
	पूर्ण
	वापस 0;
पूर्ण

/* Create links from FIMC-LITE source pads to other entities */
अटल पूर्णांक __fimc_md_create_flite_source_links(काष्ठा fimc_md *fmd)
अणु
	काष्ठा media_entity *source, *sink;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < FIMC_LITE_MAX_DEVS; i++) अणु
		काष्ठा fimc_lite *fimc = fmd->fimc_lite[i];

		अगर (fimc == शून्य)
			जारी;

		source = &fimc->subdev.entity;
		sink = &fimc->ve.vdev.entity;
		/* FIMC-LITE's subdev and video node */
		ret = media_create_pad_link(source, FLITE_SD_PAD_SOURCE_DMA,
					       sink, 0, 0);
		अगर (ret)
			अवरोध;
		/* Link from FIMC-LITE to IS-ISP subdev */
		sink = &fmd->fimc_is->isp.subdev.entity;
		ret = media_create_pad_link(source, FLITE_SD_PAD_SOURCE_ISP,
					       sink, 0, 0);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Create FIMC-IS links */
अटल पूर्णांक __fimc_md_create_fimc_is_links(काष्ठा fimc_md *fmd)
अणु
	काष्ठा fimc_isp *isp = &fmd->fimc_is->isp;
	काष्ठा media_entity *source, *sink;
	पूर्णांक i, ret;

	source = &isp->subdev.entity;

	क्रम (i = 0; i < FIMC_MAX_DEVS; i++) अणु
		अगर (fmd->fimc[i] == शून्य)
			जारी;

		/* Link from FIMC-IS-ISP subdev to FIMC */
		sink = &fmd->fimc[i]->vid_cap.subdev.entity;
		ret = media_create_pad_link(source, FIMC_ISP_SD_PAD_SRC_FIFO,
					       sink, FIMC_SD_PAD_SINK_FIFO, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Link from FIMC-IS-ISP subdev to fimc-is-isp.capture video node */
	sink = &isp->video_capture.ve.vdev.entity;

	/* Skip this link अगर the fimc-is-isp video node driver isn't built-in */
	अगर (sink->num_pads == 0)
		वापस 0;

	वापस media_create_pad_link(source, FIMC_ISP_SD_PAD_SRC_DMA,
					sink, 0, 0);
पूर्ण

/**
 * fimc_md_create_links - create शेष links between रेजिस्टरed entities
 * @fmd: fimc media device
 *
 * Parallel पूर्णांकerface sensor entities are connected directly to FIMC capture
 * entities. The sensors using MIPI CSIS bus are connected through immutable
 * link with CSI receiver entity specअगरied by mux_id. Any रेजिस्टरed CSIS
 * entity has a link to each रेजिस्टरed FIMC capture entity. Enabled links
 * are created by शेष between each subsequent रेजिस्टरed sensor and
 * subsequent FIMC capture entity. The number of शेष active links is
 * determined by the number of available sensors or FIMC entities,
 * whichever is less.
 */
अटल पूर्णांक fimc_md_create_links(काष्ठा fimc_md *fmd)
अणु
	काष्ठा v4l2_subdev *csi_sensors[CSIS_MAX_ENTITIES] = अणु शून्य पूर्ण;
	काष्ठा v4l2_subdev *sensor, *csis;
	काष्ठा fimc_source_info *pdata;
	काष्ठा media_entity *source, *sink;
	पूर्णांक i, pad, fimc_id = 0, ret = 0;
	u32 flags, link_mask = 0;

	क्रम (i = 0; i < fmd->num_sensors; i++) अणु
		अगर (fmd->sensor[i].subdev == शून्य)
			जारी;

		sensor = fmd->sensor[i].subdev;
		pdata = v4l2_get_subdev_hostdata(sensor);
		अगर (!pdata)
			जारी;

		source = शून्य;

		चयन (pdata->sensor_bus_type) अणु
		हाल FIMC_BUS_TYPE_MIPI_CSI2:
			अगर (WARN(pdata->mux_id >= CSIS_MAX_ENTITIES,
				"Wrong CSI channel id: %d\n", pdata->mux_id))
				वापस -EINVAL;

			csis = fmd->csis[pdata->mux_id].sd;
			अगर (WARN(csis == शून्य,
				 "MIPI-CSI interface specified but s5p-csis module is not loaded!\n"))
				वापस -EINVAL;

			pad = sensor->entity.num_pads - 1;
			ret = media_create_pad_link(&sensor->entity, pad,
					      &csis->entity, CSIS_PAD_SINK,
					      MEDIA_LNK_FL_IMMUTABLE |
					      MEDIA_LNK_FL_ENABLED);
			अगर (ret)
				वापस ret;

			v4l2_info(&fmd->v4l2_dev, "created link [%s] => [%s]\n",
				  sensor->entity.name, csis->entity.name);

			source = शून्य;
			csi_sensors[pdata->mux_id] = sensor;
			अवरोध;

		हाल FIMC_BUS_TYPE_ITU_601...FIMC_BUS_TYPE_ITU_656:
			source = &sensor->entity;
			pad = 0;
			अवरोध;

		शेष:
			v4l2_err(&fmd->v4l2_dev, "Wrong bus_type: %x\n",
				 pdata->sensor_bus_type);
			वापस -EINVAL;
		पूर्ण
		अगर (source == शून्य)
			जारी;

		link_mask = 1 << fimc_id++;
		ret = __fimc_md_create_fimc_sink_links(fmd, source, sensor,
						       pad, link_mask);
	पूर्ण

	क्रम (i = 0; i < CSIS_MAX_ENTITIES; i++) अणु
		अगर (fmd->csis[i].sd == शून्य)
			जारी;

		source = &fmd->csis[i].sd->entity;
		pad = CSIS_PAD_SOURCE;
		sensor = csi_sensors[i];

		link_mask = 1 << fimc_id++;
		ret = __fimc_md_create_fimc_sink_links(fmd, source, sensor,
						       pad, link_mask);
	पूर्ण

	/* Create immutable links between each FIMC's subdev and video node */
	flags = MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED;
	क्रम (i = 0; i < FIMC_MAX_DEVS; i++) अणु
		अगर (!fmd->fimc[i])
			जारी;

		source = &fmd->fimc[i]->vid_cap.subdev.entity;
		sink = &fmd->fimc[i]->vid_cap.ve.vdev.entity;

		ret = media_create_pad_link(source, FIMC_SD_PAD_SOURCE,
					      sink, 0, flags);
		अगर (ret)
			अवरोध;
	पूर्ण

	ret = __fimc_md_create_flite_source_links(fmd);
	अगर (ret < 0)
		वापस ret;

	अगर (fmd->use_isp)
		ret = __fimc_md_create_fimc_is_links(fmd);

	वापस ret;
पूर्ण

/*
 * The peripheral sensor and CAM_BLK (PIXELASYNCMx) घड़ीs management.
 */
अटल व्योम fimc_md_put_घड़ीs(काष्ठा fimc_md *fmd)
अणु
	पूर्णांक i = FIMC_MAX_CAMCLKS;

	जबतक (--i >= 0) अणु
		अगर (IS_ERR(fmd->camclk[i].घड़ी))
			जारी;
		clk_put(fmd->camclk[i].घड़ी);
		fmd->camclk[i].घड़ी = ERR_PTR(-EINVAL);
	पूर्ण

	/* Writeback (PIXELASYNCMx) घड़ीs */
	क्रम (i = 0; i < FIMC_MAX_WBCLKS; i++) अणु
		अगर (IS_ERR(fmd->wbclk[i]))
			जारी;
		clk_put(fmd->wbclk[i]);
		fmd->wbclk[i] = ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक fimc_md_get_घड़ीs(काष्ठा fimc_md *fmd)
अणु
	काष्ठा device *dev = &fmd->pdev->dev;
	अक्षर clk_name[32];
	काष्ठा clk *घड़ी;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < FIMC_MAX_CAMCLKS; i++)
		fmd->camclk[i].घड़ी = ERR_PTR(-EINVAL);

	क्रम (i = 0; i < FIMC_MAX_CAMCLKS; i++) अणु
		snम_लिखो(clk_name, माप(clk_name), "sclk_cam%u", i);
		घड़ी = clk_get(dev, clk_name);

		अगर (IS_ERR(घड़ी)) अणु
			dev_err(dev, "Failed to get clock: %s\n", clk_name);
			ret = PTR_ERR(घड़ी);
			अवरोध;
		पूर्ण
		fmd->camclk[i].घड़ी = घड़ी;
	पूर्ण
	अगर (ret)
		fimc_md_put_घड़ीs(fmd);

	अगर (!fmd->use_isp)
		वापस 0;
	/*
	 * For now get only PIXELASYNCM1 घड़ी (Writeback B/ISP),
	 * leave PIXELASYNCM0 out क्रम the LCD Writeback driver.
	 */
	fmd->wbclk[CLK_IDX_WB_A] = ERR_PTR(-EINVAL);

	क्रम (i = CLK_IDX_WB_B; i < FIMC_MAX_WBCLKS; i++) अणु
		snम_लिखो(clk_name, माप(clk_name), "pxl_async%u", i);
		घड़ी = clk_get(dev, clk_name);
		अगर (IS_ERR(घड़ी)) अणु
			v4l2_err(&fmd->v4l2_dev, "Failed to get clock: %s\n",
				  clk_name);
			ret = PTR_ERR(घड़ी);
			अवरोध;
		पूर्ण
		fmd->wbclk[i] = घड़ी;
	पूर्ण
	अगर (ret)
		fimc_md_put_घड़ीs(fmd);

	वापस ret;
पूर्ण

अटल पूर्णांक __fimc_md_modअगरy_pipeline(काष्ठा media_entity *entity, bool enable)
अणु
	काष्ठा exynos_video_entity *ve;
	काष्ठा fimc_pipeline *p;
	काष्ठा video_device *vdev;
	पूर्णांक ret;

	vdev = media_entity_to_video_device(entity);
	अगर (vdev->entity.use_count == 0)
		वापस 0;

	ve = vdev_to_exynos_video_entity(vdev);
	p = to_fimc_pipeline(ve->pipe);
	/*
	 * Nothing to करो अगर we are disabling the pipeline, some link
	 * has been disconnected and p->subdevs array is cleared now.
	 */
	अगर (!enable && p->subdevs[IDX_SENSOR] == शून्य)
		वापस 0;

	अगर (enable)
		ret = __fimc_pipeline_खोलो(ve->pipe, entity, true);
	अन्यथा
		ret = __fimc_pipeline_बंद(ve->pipe);

	अगर (ret == 0 && !enable)
		स_रखो(p->subdevs, 0, माप(p->subdevs));

	वापस ret;
पूर्ण

/* Locking: called with entity->graph_obj.mdev->graph_mutex mutex held. */
अटल पूर्णांक __fimc_md_modअगरy_pipelines(काष्ठा media_entity *entity, bool enable,
				      काष्ठा media_graph *graph)
अणु
	काष्ठा media_entity *entity_err = entity;
	पूर्णांक ret;

	/*
	 * Walk current graph and call the pipeline खोलो/बंद routine क्रम each
	 * खोलोed video node that beदीर्घs to the graph of entities connected
	 * through active links. This is needed as we cannot घातer on/off the
	 * subdevs in अक्रमom order.
	 */
	media_graph_walk_start(graph, entity);

	जबतक ((entity = media_graph_walk_next(graph))) अणु
		अगर (!is_media_entity_v4l2_video_device(entity))
			जारी;

		ret  = __fimc_md_modअगरy_pipeline(entity, enable);

		अगर (ret < 0)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	media_graph_walk_start(graph, entity_err);

	जबतक ((entity_err = media_graph_walk_next(graph))) अणु
		अगर (!is_media_entity_v4l2_video_device(entity_err))
			जारी;

		__fimc_md_modअगरy_pipeline(entity_err, !enable);

		अगर (entity_err == entity)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fimc_md_link_notअगरy(काष्ठा media_link *link, अचिन्हित पूर्णांक flags,
				अचिन्हित पूर्णांक notअगरication)
अणु
	काष्ठा media_graph *graph =
		&container_of(link->graph_obj.mdev, काष्ठा fimc_md,
			      media_dev)->link_setup_graph;
	काष्ठा media_entity *sink = link->sink->entity;
	पूर्णांक ret = 0;

	/* Beक्रमe link disconnection */
	अगर (notअगरication == MEDIA_DEV_NOTIFY_PRE_LINK_CH) अणु
		ret = media_graph_walk_init(graph,
						   link->graph_obj.mdev);
		अगर (ret)
			वापस ret;
		अगर (!(flags & MEDIA_LNK_FL_ENABLED))
			ret = __fimc_md_modअगरy_pipelines(sink, false, graph);
#अगर 0
		अन्यथा
			/* TODO: Link state change validation */
#पूर्ण_अगर
	/* After link activation */
	पूर्ण अन्यथा अगर (notअगरication == MEDIA_DEV_NOTIFY_POST_LINK_CH) अणु
		अगर (link->flags & MEDIA_LNK_FL_ENABLED)
			ret = __fimc_md_modअगरy_pipelines(sink, true, graph);
		media_graph_walk_cleanup(graph);
	पूर्ण

	वापस ret ? -EPIPE : 0;
पूर्ण

अटल स्थिर काष्ठा media_device_ops fimc_md_ops = अणु
	.link_notअगरy = fimc_md_link_notअगरy,
पूर्ण;

अटल sमाप_प्रकार fimc_md_sysfs_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fimc_md *fmd = dev_get_drvdata(dev);

	अगर (fmd->user_subdev_api)
		वापस strscpy(buf, "Sub-device API (sub-dev)\n", PAGE_SIZE);

	वापस strscpy(buf, "V4L2 video node only API (vid-dev)\n", PAGE_SIZE);
पूर्ण

अटल sमाप_प्रकार fimc_md_sysfs_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fimc_md *fmd = dev_get_drvdata(dev);
	bool subdev_api;
	पूर्णांक i;

	अगर (!म_भेद(buf, "vid-dev\n"))
		subdev_api = false;
	अन्यथा अगर (!म_भेद(buf, "sub-dev\n"))
		subdev_api = true;
	अन्यथा
		वापस count;

	fmd->user_subdev_api = subdev_api;
	क्रम (i = 0; i < FIMC_MAX_DEVS; i++)
		अगर (fmd->fimc[i])
			fmd->fimc[i]->vid_cap.user_subdev_api = subdev_api;
	वापस count;
पूर्ण
/*
 * This device attribute is to select video pipeline configuration method.
 * There are following valid values:
 *  vid-dev - क्रम V4L2 video node API only, subdevice will be configured
 *  by the host driver.
 *  sub-dev - क्रम media controller API, subdevs must be configured in user
 *  space beक्रमe starting streaming.
 */
अटल DEVICE_ATTR(subdev_conf_mode, S_IWUSR | S_IRUGO,
		   fimc_md_sysfs_show, fimc_md_sysfs_store);

अटल पूर्णांक cam_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा cam_clk *camclk = to_cam_clk(hw);
	पूर्णांक ret;

	अगर (camclk->fmd->pmf == शून्य)
		वापस -ENODEV;

	ret = pm_runसमय_get_sync(camclk->fmd->pmf);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम cam_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा cam_clk *camclk = to_cam_clk(hw);

	अगर (camclk->fmd->pmf == शून्य)
		वापस;

	pm_runसमय_put_sync(camclk->fmd->pmf);
पूर्ण

अटल स्थिर काष्ठा clk_ops cam_clk_ops = अणु
	.prepare = cam_clk_prepare,
	.unprepare = cam_clk_unprepare,
पूर्ण;

अटल व्योम fimc_md_unरेजिस्टर_clk_provider(काष्ठा fimc_md *fmd)
अणु
	काष्ठा cam_clk_provider *cp = &fmd->clk_provider;
	अचिन्हित पूर्णांक i;

	अगर (cp->of_node)
		of_clk_del_provider(cp->of_node);

	क्रम (i = 0; i < cp->num_घड़ीs; i++)
		clk_unरेजिस्टर(cp->clks[i]);
पूर्ण

अटल पूर्णांक fimc_md_रेजिस्टर_clk_provider(काष्ठा fimc_md *fmd)
अणु
	काष्ठा cam_clk_provider *cp = &fmd->clk_provider;
	काष्ठा device *dev = &fmd->pdev->dev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < FIMC_MAX_CAMCLKS; i++) अणु
		काष्ठा cam_clk *camclk = &cp->camclk[i];
		काष्ठा clk_init_data init;
		स्थिर अक्षर *p_name;

		ret = of_property_पढ़ो_string_index(dev->of_node,
					"clock-output-names", i, &init.name);
		अगर (ret < 0)
			अवरोध;

		p_name = __clk_get_name(fmd->camclk[i].घड़ी);

		/* It's safe since clk_रेजिस्टर() will duplicate the string. */
		init.parent_names = &p_name;
		init.num_parents = 1;
		init.ops = &cam_clk_ops;
		init.flags = CLK_SET_RATE_PARENT;
		camclk->hw.init = &init;
		camclk->fmd = fmd;

		cp->clks[i] = clk_रेजिस्टर(शून्य, &camclk->hw);
		अगर (IS_ERR(cp->clks[i])) अणु
			dev_err(dev, "failed to register clock: %s (%ld)\n",
					init.name, PTR_ERR(cp->clks[i]));
			ret = PTR_ERR(cp->clks[i]);
			जाओ err;
		पूर्ण
		cp->num_घड़ीs++;
	पूर्ण

	अगर (cp->num_घड़ीs == 0) अणु
		dev_warn(dev, "clk provider not registered\n");
		वापस 0;
	पूर्ण

	cp->clk_data.clks = cp->clks;
	cp->clk_data.clk_num = cp->num_घड़ीs;
	cp->of_node = dev->of_node;
	ret = of_clk_add_provider(dev->of_node, of_clk_src_onecell_get,
				  &cp->clk_data);
	अगर (ret == 0)
		वापस 0;
err:
	fimc_md_unरेजिस्टर_clk_provider(fmd);
	वापस ret;
पूर्ण

अटल पूर्णांक subdev_notअगरier_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				 काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा fimc_md *fmd = notअगरier_to_fimc_md(notअगरier);
	काष्ठा fimc_sensor_info *si = शून्य;
	पूर्णांक i;

	/* Find platक्रमm data क्रम this sensor subdev */
	क्रम (i = 0; i < ARRAY_SIZE(fmd->sensor); i++)
		अगर (fmd->sensor[i].asd &&
		    fmd->sensor[i].asd->match.fwnode ==
		    of_fwnode_handle(subdev->dev->of_node))
			si = &fmd->sensor[i];

	अगर (si == शून्य)
		वापस -EINVAL;

	v4l2_set_subdev_hostdata(subdev, &si->pdata);

	अगर (si->pdata.fimc_bus_type == FIMC_BUS_TYPE_ISP_WRITEBACK)
		subdev->grp_id = GRP_ID_FIMC_IS_SENSOR;
	अन्यथा
		subdev->grp_id = GRP_ID_SENSOR;

	si->subdev = subdev;

	v4l2_info(&fmd->v4l2_dev, "Registered sensor subdevice: %s (%d)\n",
		  subdev->name, fmd->num_sensors);

	fmd->num_sensors++;

	वापस 0;
पूर्ण

अटल पूर्णांक subdev_notअगरier_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा fimc_md *fmd = notअगरier_to_fimc_md(notअगरier);
	पूर्णांक ret;

	mutex_lock(&fmd->media_dev.graph_mutex);

	ret = fimc_md_create_links(fmd);
	अगर (ret < 0)
		जाओ unlock;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&fmd->v4l2_dev);
unlock:
	mutex_unlock(&fmd->media_dev.graph_mutex);
	अगर (ret < 0)
		वापस ret;

	वापस media_device_रेजिस्टर(&fmd->media_dev);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations subdev_notअगरier_ops = अणु
	.bound = subdev_notअगरier_bound,
	.complete = subdev_notअगरier_complete,
पूर्ण;

अटल पूर्णांक fimc_md_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा pinctrl *pinctrl;
	काष्ठा fimc_md *fmd;
	पूर्णांक ret;

	fmd = devm_kzalloc(dev, माप(*fmd), GFP_KERNEL);
	अगर (!fmd)
		वापस -ENOMEM;

	spin_lock_init(&fmd->slock);
	INIT_LIST_HEAD(&fmd->pipelines);
	fmd->pdev = pdev;

	strscpy(fmd->media_dev.model, "Samsung S5P FIMC",
		माप(fmd->media_dev.model));
	fmd->media_dev.ops = &fimc_md_ops;
	fmd->media_dev.dev = dev;

	v4l2_dev = &fmd->v4l2_dev;
	v4l2_dev->mdev = &fmd->media_dev;
	v4l2_dev->notअगरy = fimc_sensor_notअगरy;
	strscpy(v4l2_dev->name, "s5p-fimc-md", माप(v4l2_dev->name));

	fmd->use_isp = fimc_md_is_isp_available(dev->of_node);
	fmd->user_subdev_api = true;

	media_device_init(&fmd->media_dev);

	ret = v4l2_device_रेजिस्टर(dev, &fmd->v4l2_dev);
	अगर (ret < 0) अणु
		v4l2_err(v4l2_dev, "Failed to register v4l2_device: %d\n", ret);
		जाओ err_md;
	पूर्ण

	ret = fimc_md_get_घड़ीs(fmd);
	अगर (ret)
		जाओ err_v4l2dev;

	pinctrl = devm_pinctrl_get(dev);
	अगर (IS_ERR(pinctrl)) अणु
		ret = PTR_ERR(pinctrl);
		अगर (ret != EPROBE_DEFER)
			dev_err(dev, "Failed to get pinctrl: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, fmd);

	v4l2_async_notअगरier_init(&fmd->subdev_notअगरier);

	ret = fimc_md_रेजिस्टर_platक्रमm_entities(fmd, dev->of_node);
	अगर (ret)
		जाओ err_clk;

	ret = fimc_md_रेजिस्टर_sensor_entities(fmd);
	अगर (ret)
		जाओ err_m_ent;

	ret = device_create_file(&pdev->dev, &dev_attr_subdev_conf_mode);
	अगर (ret)
		जाओ err_cleanup;
	/*
	 * FIMC platक्रमm devices need to be रेजिस्टरed beक्रमe the sclk_cam
	 * घड़ीs provider, as one of these devices needs to be activated
	 * to enable the घड़ी.
	 */
	ret = fimc_md_रेजिस्टर_clk_provider(fmd);
	अगर (ret < 0) अणु
		v4l2_err(v4l2_dev, "clock provider registration failed\n");
		जाओ err_attr;
	पूर्ण

	अगर (fmd->num_sensors > 0) अणु
		fmd->subdev_notअगरier.ops = &subdev_notअगरier_ops;
		fmd->num_sensors = 0;

		ret = v4l2_async_notअगरier_रेजिस्टर(&fmd->v4l2_dev,
						&fmd->subdev_notअगरier);
		अगर (ret)
			जाओ err_clk_p;
	पूर्ण

	वापस 0;

err_clk_p:
	fimc_md_unरेजिस्टर_clk_provider(fmd);
err_attr:
	device_हटाओ_file(&pdev->dev, &dev_attr_subdev_conf_mode);
err_cleanup:
	v4l2_async_notअगरier_cleanup(&fmd->subdev_notअगरier);
err_m_ent:
	fimc_md_unरेजिस्टर_entities(fmd);
err_clk:
	fimc_md_put_घड़ीs(fmd);
err_v4l2dev:
	v4l2_device_unरेजिस्टर(&fmd->v4l2_dev);
err_md:
	media_device_cleanup(&fmd->media_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_md_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fimc_md *fmd = platक्रमm_get_drvdata(pdev);

	अगर (!fmd)
		वापस 0;

	fimc_md_unरेजिस्टर_clk_provider(fmd);
	v4l2_async_notअगरier_unरेजिस्टर(&fmd->subdev_notअगरier);
	v4l2_async_notअगरier_cleanup(&fmd->subdev_notअगरier);

	v4l2_device_unरेजिस्टर(&fmd->v4l2_dev);
	device_हटाओ_file(&pdev->dev, &dev_attr_subdev_conf_mode);
	fimc_md_unरेजिस्टर_entities(fmd);
	fimc_md_pipelines_मुक्त(fmd);
	media_device_unरेजिस्टर(&fmd->media_dev);
	media_device_cleanup(&fmd->media_dev);
	fimc_md_put_घड़ीs(fmd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id fimc_driver_ids[] __always_unused = अणु
	अणु .name = "s5p-fimc-md" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, fimc_driver_ids);

अटल स्थिर काष्ठा of_device_id fimc_md_of_match[] = अणु
	अणु .compatible = "samsung,fimc" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fimc_md_of_match);

अटल काष्ठा platक्रमm_driver fimc_md_driver = अणु
	.probe		= fimc_md_probe,
	.हटाओ		= fimc_md_हटाओ,
	.driver = अणु
		.of_match_table = of_match_ptr(fimc_md_of_match),
		.name		= "s5p-fimc-md",
	पूर्ण
पूर्ण;

अटल पूर्णांक __init fimc_md_init(व्योम)
अणु
	पूर्णांक ret;

	request_module("s5p-csis");
	ret = fimc_रेजिस्टर_driver();
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&fimc_md_driver);
पूर्ण

अटल व्योम __निकास fimc_md_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fimc_md_driver);
	fimc_unरेजिस्टर_driver();
पूर्ण

module_init(fimc_md_init);
module_निकास(fimc_md_निकास);

MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_DESCRIPTION("S5P FIMC camera host interface/video postprocessor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("2.0.1");
