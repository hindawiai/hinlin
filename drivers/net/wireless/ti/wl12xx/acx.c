<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#समावेश "../wlcore/cmd.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/acx.h"

#समावेश "acx.h"

पूर्णांक wl1271_acx_host_अगर_cfg_biपंचांगap(काष्ठा wl1271 *wl, u32 host_cfg_biपंचांगap)
अणु
	काष्ठा wl1271_acx_host_config_biपंचांगap *biपंचांगap_conf;
	पूर्णांक ret;

	biपंचांगap_conf = kzalloc(माप(*biपंचांगap_conf), GFP_KERNEL);
	अगर (!biपंचांगap_conf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	biपंचांगap_conf->host_cfg_biपंचांगap = cpu_to_le32(host_cfg_biपंचांगap);

	ret = wl1271_cmd_configure(wl, ACX_HOST_IF_CFG_BITMAP,
				   biपंचांगap_conf, माप(*biपंचांगap_conf));
	अगर (ret < 0) अणु
		wl1271_warning("wl1271 bitmap config opt failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(biपंचांगap_conf);

	वापस ret;
पूर्ण
