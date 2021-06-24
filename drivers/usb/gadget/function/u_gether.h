<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_gether.h
 *
 * Utility definitions क्रम the subset function
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित U_GETHER_H
#घोषणा U_GETHER_H

#समावेश <linux/usb/composite.h>

काष्ठा f_gether_opts अणु
	काष्ठा usb_function_instance	func_inst;
	काष्ठा net_device		*net;
	bool				bound;

	/*
	 * Read/ग_लिखो access to configfs attributes is handled by configfs.
	 *
	 * This is to protect the data from concurrent access by पढ़ो/ग_लिखो
	 * and create symlink/हटाओ symlink.
	 */
	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

#पूर्ण_अगर /* U_GETHER_H */
