<शैली गुरु>
/*
 * linux/include/linux/netfilter/xt_IDLETIMER.h
 *
 * Header file क्रम Xtables समयr target module.
 *
 * Copyright (C) 2004, 2010 Nokia Corporation
 * Written by Timo Teras <ext-timo.teras@nokia.com>
 *
 * Converted to x_tables and क्रमward-ported to 2.6.34
 * by Luciano Coelho <luciano.coelho@nokia.com>
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA
 * 02110-1301 USA
 */

#अगर_अघोषित _XT_IDLETIMER_H
#घोषणा _XT_IDLETIMER_H

#समावेश <linux/types.h>

#घोषणा MAX_IDLETIMER_LABEL_SIZE 28
#घोषणा XT_IDLETIMER_ALARM 0x01

काष्ठा idleसमयr_tg_info अणु
	__u32 समयout;

	अक्षर label[MAX_IDLETIMER_LABEL_SIZE];

	/* क्रम kernel module पूर्णांकernal use only */
	काष्ठा idleसमयr_tg *समयr __attribute__((aligned(8)));
पूर्ण;

काष्ठा idleसमयr_tg_info_v1 अणु
	__u32 समयout;

	अक्षर label[MAX_IDLETIMER_LABEL_SIZE];

	__u8 send_nl_msg;   /* unused: क्रम compatibility with Android */
	__u8 समयr_type;

	/* क्रम kernel module पूर्णांकernal use only */
	काष्ठा idleसमयr_tg *समयr __attribute__((aligned(8)));
पूर्ण;
#पूर्ण_अगर
