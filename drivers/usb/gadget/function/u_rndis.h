<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_rndis.h
 *
 * Utility definitions क्रम the subset function
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित U_RNDIS_H
#घोषणा U_RNDIS_H

#समावेश <linux/usb/composite.h>

काष्ठा f_rndis_opts अणु
	काष्ठा usb_function_instance	func_inst;
	u32				venकरोr_id;
	स्थिर अक्षर			*manufacturer;
	काष्ठा net_device		*net;
	bool				bound;
	bool				borrowed_net;

	काष्ठा config_group		*rndis_पूर्णांकerf_group;
	काष्ठा usb_os_desc		rndis_os_desc;
	अक्षर				rndis_ext_compat_id[16];

	u8				class;
	u8				subclass;
	u8				protocol;

	/*
	 * Read/ग_लिखो access to configfs attributes is handled by configfs.
	 *
	 * This is to protect the data from concurrent access by पढ़ो/ग_लिखो
	 * and create symlink/हटाओ symlink.
	 */
	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

व्योम rndis_borrow_net(काष्ठा usb_function_instance *f, काष्ठा net_device *net);

#पूर्ण_अगर /* U_RNDIS_H */
