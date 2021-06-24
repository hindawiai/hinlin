<शैली गुरु>
/*
 *  linux/drivers/video/fb_notअगरy.c
 *
 *  Copyright (C) 2006 Antonino Daplas <adaplas@pol.net>
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/fb.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/export.h>

अटल BLOCKING_NOTIFIER_HEAD(fb_notअगरier_list);

/**
 *	fb_रेजिस्टर_client - रेजिस्टर a client notअगरier
 *	@nb: notअगरier block to callback on events
 *
 *	Return: 0 on success, negative error code on failure.
 */
पूर्णांक fb_रेजिस्टर_client(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&fb_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL(fb_रेजिस्टर_client);

/**
 *	fb_unरेजिस्टर_client - unरेजिस्टर a client notअगरier
 *	@nb: notअगरier block to callback on events
 *
 *	Return: 0 on success, negative error code on failure.
 */
पूर्णांक fb_unरेजिस्टर_client(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&fb_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL(fb_unरेजिस्टर_client);

/**
 * fb_notअगरier_call_chain - notअगरy clients of fb_events
 * @val: value passed to callback
 * @v: poपूर्णांकer passed to callback
 *
 * Return: The वापस value of the last notअगरier function
 */
पूर्णांक fb_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस blocking_notअगरier_call_chain(&fb_notअगरier_list, val, v);
पूर्ण
EXPORT_SYMBOL_GPL(fb_notअगरier_call_chain);
