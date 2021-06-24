<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_uac2.h
 *
 * Utility definitions क्रम UAC2 function
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित U_UAC2_H
#घोषणा U_UAC2_H

#समावेश <linux/usb/composite.h>

#घोषणा UAC2_DEF_PCHMASK 0x3
#घोषणा UAC2_DEF_PSRATE 48000
#घोषणा UAC2_DEF_PSSIZE 2
#घोषणा UAC2_DEF_CCHMASK 0x3
#घोषणा UAC2_DEF_CSRATE 64000
#घोषणा UAC2_DEF_CSSIZE 2
#घोषणा UAC2_DEF_REQ_NUM 2

काष्ठा f_uac2_opts अणु
	काष्ठा usb_function_instance	func_inst;
	पूर्णांक				p_chmask;
	पूर्णांक				p_srate;
	पूर्णांक				p_ssize;
	पूर्णांक				c_chmask;
	पूर्णांक				c_srate;
	पूर्णांक				c_ssize;
	पूर्णांक				req_number;
	bool				bound;

	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

#पूर्ण_अगर
