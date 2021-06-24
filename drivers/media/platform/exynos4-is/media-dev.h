<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 - 2012 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित FIMC_MDEVICE_H_
#घोषणा FIMC_MDEVICE_H_

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <media/media-device.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

#समावेश "fimc-core.h"
#समावेश "fimc-lite.h"
#समावेश "mipi-csis.h"

#घोषणा FIMC_OF_NODE_NAME	"fimc"
#घोषणा FIMC_LITE_OF_NODE_NAME	"fimc-lite"
#घोषणा FIMC_IS_OF_NODE_NAME	"fimc-is"
#घोषणा CSIS_OF_NODE_NAME	"csis"

#घोषणा FIMC_MAX_SENSORS	4
#घोषणा FIMC_MAX_CAMCLKS	2
#घोषणा DEFAULT_SENSOR_CLK_FREQ	24000000U

/* LCD/ISP Writeback घड़ीs (PIXELASYNCMx) */
क्रमागत अणु
	CLK_IDX_WB_A,
	CLK_IDX_WB_B,
	FIMC_MAX_WBCLKS
पूर्ण;

क्रमागत fimc_subdev_index अणु
	IDX_SENSOR,
	IDX_CSIS,
	IDX_FLITE,
	IDX_IS_ISP,
	IDX_FIMC,
	IDX_MAX,
पूर्ण;

/*
 * This काष्ठाure represents a chain of media entities, including a data
 * source entity (e.g. an image sensor subdevice), a data capture entity
 * - a video capture device node and any reमुख्यing entities.
 */
काष्ठा fimc_pipeline अणु
	काष्ठा exynos_media_pipeline ep;
	काष्ठा list_head list;
	काष्ठा media_entity *vdev_entity;
	काष्ठा v4l2_subdev *subdevs[IDX_MAX];
पूर्ण;

#घोषणा to_fimc_pipeline(_ep) container_of(_ep, काष्ठा fimc_pipeline, ep)

काष्ठा fimc_csis_info अणु
	काष्ठा v4l2_subdev *sd;
	पूर्णांक id;
पूर्ण;

काष्ठा fimc_camclk_info अणु
	काष्ठा clk *घड़ी;
	पूर्णांक use_count;
	अचिन्हित दीर्घ frequency;
पूर्ण;

/**
 * काष्ठा fimc_sensor_info - image data source subdev inक्रमmation
 * @pdata: sensor's attributes passed as media device's platक्रमm data
 * @asd: asynchronous subdev registration data काष्ठाure
 * @subdev: image sensor v4l2 subdev
 * @host: fimc device the sensor is currently linked to
 *
 * This data काष्ठाure applies to image sensor and the ग_लिखोback subdevs.
 */
काष्ठा fimc_sensor_info अणु
	काष्ठा fimc_source_info pdata;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा fimc_dev *host;
पूर्ण;

काष्ठा cam_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा fimc_md *fmd;
पूर्ण;
#घोषणा to_cam_clk(_hw) container_of(_hw, काष्ठा cam_clk, hw)

/**
 * काष्ठा fimc_md - fimc media device inक्रमmation
 * @csis: MIPI CSIS subdevs data
 * @sensor: array of रेजिस्टरed sensor subdevs
 * @num_sensors: actual number of रेजिस्टरed sensors
 * @camclk: बाह्यal sensor घड़ी inक्रमmation
 * @wbclk: बाह्यal ग_लिखोback घड़ी inक्रमmation
 * @fimc_lite: array of रेजिस्टरed fimc-lite devices
 * @fimc: array of रेजिस्टरed fimc devices
 * @fimc_is: fimc-is data काष्ठाure
 * @use_isp: set to true when FIMC-IS subप्रणाली is used
 * @pmf: handle to the CAMCLK घड़ी control FIMC helper device
 * @media_dev: top level media device
 * @v4l2_dev: top level v4l2_device holding up the subdevs
 * @pdev: platक्रमm device this media device is hooked up पूर्णांकo
 * @clk_provider: CAMCLK घड़ी provider काष्ठाure
 * @subdev_notअगरier: notअगरier क्रम the subdevs
 * @user_subdev_api: true अगर subdevs are not configured by the host driver
 * @slock: spinlock protecting @sensor array
 * @pipelines: list of pipelines
 * @link_setup_graph: graph iterator
 */
काष्ठा fimc_md अणु
	काष्ठा fimc_csis_info csis[CSIS_MAX_ENTITIES];
	काष्ठा fimc_sensor_info sensor[FIMC_MAX_SENSORS];
	पूर्णांक num_sensors;
	काष्ठा fimc_camclk_info camclk[FIMC_MAX_CAMCLKS];
	काष्ठा clk *wbclk[FIMC_MAX_WBCLKS];
	काष्ठा fimc_lite *fimc_lite[FIMC_LITE_MAX_DEVS];
	काष्ठा fimc_dev *fimc[FIMC_MAX_DEVS];
	काष्ठा fimc_is *fimc_is;
	bool use_isp;
	काष्ठा device *pmf;
	काष्ठा media_device media_dev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा platक्रमm_device *pdev;

	काष्ठा cam_clk_provider अणु
		काष्ठा clk *clks[FIMC_MAX_CAMCLKS];
		काष्ठा clk_onecell_data clk_data;
		काष्ठा device_node *of_node;
		काष्ठा cam_clk camclk[FIMC_MAX_CAMCLKS];
		पूर्णांक num_घड़ीs;
	पूर्ण clk_provider;

	काष्ठा v4l2_async_notअगरier subdev_notअगरier;

	bool user_subdev_api;
	spinlock_t slock;
	काष्ठा list_head pipelines;
	काष्ठा media_graph link_setup_graph;
पूर्ण;

अटल अंतरभूत
काष्ठा fimc_sensor_info *source_to_sensor_info(काष्ठा fimc_source_info *si)
अणु
	वापस container_of(si, काष्ठा fimc_sensor_info, pdata);
पूर्ण

अटल अंतरभूत काष्ठा fimc_md *entity_to_fimc_mdev(काष्ठा media_entity *me)
अणु
	वापस me->graph_obj.mdev == शून्य ? शून्य :
		container_of(me->graph_obj.mdev, काष्ठा fimc_md, media_dev);
पूर्ण

अटल अंतरभूत काष्ठा fimc_md *notअगरier_to_fimc_md(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा fimc_md, subdev_notअगरier);
पूर्ण

अटल अंतरभूत व्योम fimc_md_graph_lock(काष्ठा exynos_video_entity *ve)
अणु
	mutex_lock(&ve->vdev.entity.graph_obj.mdev->graph_mutex);
पूर्ण

अटल अंतरभूत व्योम fimc_md_graph_unlock(काष्ठा exynos_video_entity *ve)
अणु
	mutex_unlock(&ve->vdev.entity.graph_obj.mdev->graph_mutex);
पूर्ण

पूर्णांक fimc_md_set_camclk(काष्ठा v4l2_subdev *sd, bool on);

#अगर_घोषित CONFIG_OF
अटल अंतरभूत bool fimc_md_is_isp_available(काष्ठा device_node *node)
अणु
	node = of_get_child_by_name(node, FIMC_IS_OF_NODE_NAME);
	वापस node ? of_device_is_available(node) : false;
पूर्ण
#अन्यथा
#घोषणा fimc_md_is_isp_available(node) (false)
#पूर्ण_अगर /* CONFIG_OF */

अटल अंतरभूत काष्ठा v4l2_subdev *__fimc_md_get_subdev(
				काष्ठा exynos_media_pipeline *ep,
				अचिन्हित पूर्णांक index)
अणु
	काष्ठा fimc_pipeline *p = to_fimc_pipeline(ep);

	अगर (!p || index >= IDX_MAX)
		वापस शून्य;
	अन्यथा
		वापस p->subdevs[index];
पूर्ण

#पूर्ण_अगर
