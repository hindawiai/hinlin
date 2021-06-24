<शैली गुरु>
/* Copyright (c) 2012 Coraid, Inc.  See COPYING क्रम GPL terms. */
/*
 * aoeमुख्य.c
 * Module initialization routines, discover समयr
 */

#समावेश <linux/hdreg.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश "aoe.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sam Hopkins <sah@coraid.com>");
MODULE_DESCRIPTION("AoE block/char driver for 2.6.2 and newer 2.6 kernels");
MODULE_VERSION(VERSION);

अटल काष्ठा समयr_list समयr;

अटल व्योम discover_समयr(काष्ठा समयr_list *t)
अणु
	mod_समयr(t, jअगरfies + HZ * 60); /* one minute */

	aoecmd_cfg(0xffff, 0xff);
पूर्ण

अटल व्योम __निकास
aoe_निकास(व्योम)
अणु
	del_समयr_sync(&समयr);

	aoenet_निकास();
	unरेजिस्टर_blkdev(AOE_MAJOR, DEVICE_NAME);
	aoecmd_निकास();
	aoechr_निकास();
	aoedev_निकास();
	aoeblk_निकास();		/* मुक्त cache after de-allocating bufs */
पूर्ण

अटल पूर्णांक __init
aoe_init(व्योम)
अणु
	पूर्णांक ret;

	ret = aoedev_init();
	अगर (ret)
		वापस ret;
	ret = aoechr_init();
	अगर (ret)
		जाओ chr_fail;
	ret = aoeblk_init();
	अगर (ret)
		जाओ blk_fail;
	ret = aoenet_init();
	अगर (ret)
		जाओ net_fail;
	ret = aoecmd_init();
	अगर (ret)
		जाओ cmd_fail;
	ret = रेजिस्टर_blkdev(AOE_MAJOR, DEVICE_NAME);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "aoe: can't register major\n");
		जाओ blkreg_fail;
	पूर्ण
	prपूर्णांकk(KERN_INFO "aoe: AoE v%s initialised.\n", VERSION);

	समयr_setup(&समयr, discover_समयr, 0);
	discover_समयr(&समयr);
	वापस 0;
 blkreg_fail:
	aoecmd_निकास();
 cmd_fail:
	aoenet_निकास();
 net_fail:
	aoeblk_निकास();
 blk_fail:
	aoechr_निकास();
 chr_fail:
	aoedev_निकास();

	prपूर्णांकk(KERN_INFO "aoe: initialisation failure.\n");
	वापस ret;
पूर्ण

module_init(aoe_init);
module_निकास(aoe_निकास);

