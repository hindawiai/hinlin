<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_uac1.h - Utility definitions क्रम UAC1 function
 *
 * Copyright (C) 2016 Ruslan Bilovol <ruslan.bilovol@gmail.com>
 */

#अगर_अघोषित __U_UAC1_H
#घोषणा __U_UAC1_H

#समावेश <linux/usb/composite.h>

#घोषणा UAC1_OUT_EP_MAX_PACKET_SIZE	200
#घोषणा UAC1_DEF_CCHMASK	0x3
#घोषणा UAC1_DEF_CSRATE		48000
#घोषणा UAC1_DEF_CSSIZE		2
#घोषणा UAC1_DEF_PCHMASK	0x3
#घोषणा UAC1_DEF_PSRATE		48000
#घोषणा UAC1_DEF_PSSIZE		2
#घोषणा UAC1_DEF_REQ_NUM	2


काष्ठा f_uac1_opts अणु
	काष्ठा usb_function_instance	func_inst;
	पूर्णांक				c_chmask;
	पूर्णांक				c_srate;
	पूर्णांक				c_ssize;
	पूर्णांक				p_chmask;
	पूर्णांक				p_srate;
	पूर्णांक				p_ssize;
	पूर्णांक				req_number;
	अचिन्हित			bound:1;

	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

#पूर्ण_अगर /* __U_UAC1_H */
