<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_hid.h
 *
 * Utility definitions क्रम the hid function
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित U_HID_H
#घोषणा U_HID_H

#समावेश <linux/usb/composite.h>

काष्ठा f_hid_opts अणु
	काष्ठा usb_function_instance	func_inst;
	पूर्णांक				minor;
	अचिन्हित अक्षर			subclass;
	अचिन्हित अक्षर			protocol;
	अचिन्हित लघु			report_length;
	अचिन्हित लघु			report_desc_length;
	अचिन्हित अक्षर			*report_desc;
	bool				report_desc_alloc;

	/*
	 * Protect the data क्रमm concurrent access by पढ़ो/ग_लिखो
	 * and create symlink/हटाओ symlink.
	 */
	 काष्ठा mutex			lock;
	 पूर्णांक				refcnt;
पूर्ण;

पूर्णांक ghid_setup(काष्ठा usb_gadget *g, पूर्णांक count);
व्योम ghid_cleanup(व्योम);

#पूर्ण_अगर /* U_HID_H */
