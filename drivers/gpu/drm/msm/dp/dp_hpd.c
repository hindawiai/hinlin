<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm-dp] %s: " fmt, __func__

#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#समावेश "dp_hpd.h"

/* DP specअगरic VDM commands */
#घोषणा DP_USBPD_VDM_STATUS	0x10
#घोषणा DP_USBPD_VDM_CONFIGURE	0x11

/* USBPD-TypeC specअगरic Macros */
#घोषणा VDM_VERSION		0x0
#घोषणा USB_C_DP_SID		0xFF01

काष्ठा dp_hpd_निजी अणु
	काष्ठा device *dev;
	काष्ठा dp_usbpd_cb *dp_cb;
	काष्ठा dp_usbpd dp_usbpd;
पूर्ण;

पूर्णांक dp_hpd_connect(काष्ठा dp_usbpd *dp_usbpd, bool hpd)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_hpd_निजी *hpd_priv;

	hpd_priv = container_of(dp_usbpd, काष्ठा dp_hpd_निजी,
					dp_usbpd);

	dp_usbpd->hpd_high = hpd;

	अगर (!hpd_priv->dp_cb || !hpd_priv->dp_cb->configure
				|| !hpd_priv->dp_cb->disconnect) अणु
		pr_err("hpd dp_cb not initialized\n");
		वापस -EINVAL;
	पूर्ण
	अगर (hpd)
		hpd_priv->dp_cb->configure(hpd_priv->dev);
	अन्यथा
		hpd_priv->dp_cb->disconnect(hpd_priv->dev);

	वापस rc;
पूर्ण

काष्ठा dp_usbpd *dp_hpd_get(काष्ठा device *dev, काष्ठा dp_usbpd_cb *cb)
अणु
	काष्ठा dp_hpd_निजी *dp_hpd;

	अगर (!cb) अणु
		pr_err("invalid cb data\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	dp_hpd = devm_kzalloc(dev, माप(*dp_hpd), GFP_KERNEL);
	अगर (!dp_hpd)
		वापस ERR_PTR(-ENOMEM);

	dp_hpd->dev = dev;
	dp_hpd->dp_cb = cb;

	dp_hpd->dp_usbpd.connect = dp_hpd_connect;

	वापस &dp_hpd->dp_usbpd;
पूर्ण
