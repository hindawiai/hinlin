<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007 Intel Corporation
 *
 * Authers: Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */

#समावेश <linux/i2c.h>

#समावेश "psb_intel_drv.h"

/**
 * psb_पूर्णांकel_ddc_probe
 * @adapter:   Associated I2C adaptor
 */
bool psb_पूर्णांकel_ddc_probe(काष्ठा i2c_adapter *adapter)
अणु
	u8 out_buf[] = अणु 0x0, 0x0 पूर्ण;
	u8 buf[2];
	पूर्णांक ret;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
		 .addr = 0x50,
		 .flags = 0,
		 .len = 1,
		 .buf = out_buf,
		 पूर्ण,
		अणु
		 .addr = 0x50,
		 .flags = I2C_M_RD,
		 .len = 1,
		 .buf = buf,
		 पूर्ण
	पूर्ण;

	ret = i2c_transfer(adapter, msgs, 2);
	अगर (ret == 2)
		वापस true;

	वापस false;
पूर्ण

/**
 * psb_पूर्णांकel_ddc_get_modes - get modelist from monitor
 * @connector: DRM connector device to use
 * @adapter:   Associated I2C adaptor
 *
 * Fetch the EDID inक्रमmation from @connector using the DDC bus.
 */
पूर्णांक psb_पूर्णांकel_ddc_get_modes(काष्ठा drm_connector *connector,
			    काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा edid *edid;
	पूर्णांक ret = 0;

	edid = drm_get_edid(connector, adapter);
	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण
	वापस ret;
पूर्ण
