<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "version.h"
#समावेश "device.h"
#समावेश "noise.h"
#समावेश "queueing.h"
#समावेश "ratelimiter.h"
#समावेश "netlink.h"

#समावेश <uapi/linux/wireguard.h>

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/genetlink.h>
#समावेश <net/rtnetlink.h>

अटल पूर्णांक __init mod_init(व्योम)
अणु
	पूर्णांक ret;

	ret = wg_allowedips_slab_init();
	अगर (ret < 0)
		जाओ err_allowedips;

#अगर_घोषित DEBUG
	ret = -ENOTRECOVERABLE;
	अगर (!wg_allowedips_selftest() || !wg_packet_counter_selftest() ||
	    !wg_ratelimiter_selftest())
		जाओ err_peer;
#पूर्ण_अगर
	wg_noise_init();

	ret = wg_peer_init();
	अगर (ret < 0)
		जाओ err_peer;

	ret = wg_device_init();
	अगर (ret < 0)
		जाओ err_device;

	ret = wg_genetlink_init();
	अगर (ret < 0)
		जाओ err_netlink;

	pr_info("WireGuard " WIREGUARD_VERSION " loaded. See www.wireguard.com for information.\n");
	pr_info("Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.\n");

	वापस 0;

err_netlink:
	wg_device_uninit();
err_device:
	wg_peer_uninit();
err_peer:
	wg_allowedips_slab_uninit();
err_allowedips:
	वापस ret;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
	wg_genetlink_uninit();
	wg_device_uninit();
	wg_peer_uninit();
	wg_allowedips_slab_uninit();
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("WireGuard secure network tunnel");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
MODULE_VERSION(WIREGUARD_VERSION);
MODULE_ALIAS_RTNL_LINK(KBUILD_MODNAME);
MODULE_ALIAS_GENL_FAMILY(WG_GENL_NAME);
