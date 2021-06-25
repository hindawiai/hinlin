<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_prपूर्णांकer.h
 *
 * Utility definitions क्रम the prपूर्णांकer function
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित U_PRINTER_H
#घोषणा U_PRINTER_H

#समावेश <linux/usb/composite.h>

काष्ठा f_prपूर्णांकer_opts अणु
	काष्ठा usb_function_instance	func_inst;
	पूर्णांक				minor;
	अक्षर				*pnp_string;
	bool				pnp_string_allocated;
	अचिन्हित			q_len;

	/*
	 * Protect the data from concurrent access by पढ़ो/ग_लिखो
	 * and create symlink/हटाओ symlink
	 */
	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

#पूर्ण_अगर /* U_PRINTER_H */
