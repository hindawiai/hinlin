<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * camss.h
 *
 * Qualcomm MSM Camera Subप्रणाली - Core
 *
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#अगर_अघोषित QC_MSM_CAMSS_H
#घोषणा QC_MSM_CAMSS_H

#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/media-device.h>
#समावेश <media/media-entity.h>

#समावेश "camss-csid.h"
#समावेश "camss-csiphy.h"
#समावेश "camss-ispif.h"
#समावेश "camss-vfe.h"

#घोषणा to_camss(ptr_module)	\
	container_of(ptr_module, काष्ठा camss, ptr_module)

#घोषणा to_device(ptr_module)	\
	(to_camss(ptr_module)->dev)

#घोषणा module_poपूर्णांकer(ptr_module, index)	\
	((स्थिर काष्ठा ptr_module##_device (*)[]) &(ptr_module[-(index)]))

#घोषणा to_camss_index(ptr_module, index)	\
	container_of(module_poपूर्णांकer(ptr_module, index),	\
		     काष्ठा camss, ptr_module)

#घोषणा to_device_index(ptr_module, index)	\
	(to_camss_index(ptr_module, index)->dev)

#घोषणा CAMSS_RES_MAX 17

काष्ठा resources अणु
	अक्षर *regulator[CAMSS_RES_MAX];
	अक्षर *घड़ी[CAMSS_RES_MAX];
	u32 घड़ी_rate[CAMSS_RES_MAX][CAMSS_RES_MAX];
	अक्षर *reg[CAMSS_RES_MAX];
	अक्षर *पूर्णांकerrupt[CAMSS_RES_MAX];
पूर्ण;

काष्ठा resources_ispअगर अणु
	अक्षर *घड़ी[CAMSS_RES_MAX];
	अक्षर *घड़ी_क्रम_reset[CAMSS_RES_MAX];
	अक्षर *reg[CAMSS_RES_MAX];
	अक्षर *पूर्णांकerrupt;
पूर्ण;

क्रमागत pm_करोमुख्य अणु
	PM_DOMAIN_VFE0 = 0,
	PM_DOMAIN_VFE1 = 1,
	PM_DOMAIN_GEN1_COUNT = 2,	/* CAMSS series of ISPs */
	PM_DOMAIN_VFELITE = 2,		/* VFELITE / TOP GDSC */
	PM_DOMAIN_GEN2_COUNT = 3,	/* Titan series of ISPs */
पूर्ण;

क्रमागत camss_version अणु
	CAMSS_8x16,
	CAMSS_8x96,
	CAMSS_660,
	CAMSS_845,
पूर्ण;

काष्ठा camss अणु
	क्रमागत camss_version version;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा media_device media_dev;
	काष्ठा device *dev;
	पूर्णांक csiphy_num;
	काष्ठा csiphy_device *csiphy;
	पूर्णांक csid_num;
	काष्ठा csid_device *csid;
	काष्ठा ispअगर_device *ispअगर;
	पूर्णांक vfe_num;
	काष्ठा vfe_device *vfe;
	atomic_t ref_count;
	काष्ठा device *genpd[PM_DOMAIN_GEN2_COUNT];
	काष्ठा device_link *genpd_link[PM_DOMAIN_GEN2_COUNT];
पूर्ण;

काष्ठा camss_camera_पूर्णांकerface अणु
	u8 csiphy_id;
	काष्ठा csiphy_csi2_cfg csi2;
पूर्ण;

काष्ठा camss_async_subdev अणु
	काष्ठा v4l2_async_subdev asd; /* must be first */
	काष्ठा camss_camera_पूर्णांकerface पूर्णांकerface;
पूर्ण;

काष्ठा camss_घड़ी अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *name;
	u32 *freq;
	u32 nfreqs;
पूर्ण;

व्योम camss_add_घड़ी_margin(u64 *rate);
पूर्णांक camss_enable_घड़ीs(पूर्णांक nघड़ीs, काष्ठा camss_घड़ी *घड़ी,
			काष्ठा device *dev);
व्योम camss_disable_घड़ीs(पूर्णांक nघड़ीs, काष्ठा camss_घड़ी *घड़ी);
काष्ठा media_entity *camss_find_sensor(काष्ठा media_entity *entity);
s64 camss_get_link_freq(काष्ठा media_entity *entity, अचिन्हित पूर्णांक bpp,
			अचिन्हित पूर्णांक lanes);
पूर्णांक camss_get_pixel_घड़ी(काष्ठा media_entity *entity, u64 *pixel_घड़ी);
पूर्णांक camss_pm_करोमुख्य_on(काष्ठा camss *camss, पूर्णांक id);
व्योम camss_pm_करोमुख्य_off(काष्ठा camss *camss, पूर्णांक id);
व्योम camss_delete(काष्ठा camss *camss);

#पूर्ण_अगर /* QC_MSM_CAMSS_H */
