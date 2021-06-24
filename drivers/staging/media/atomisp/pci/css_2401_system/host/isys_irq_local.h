<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __ISYS_IRQ_LOCAL_H__
#घोषणा __ISYS_IRQ_LOCAL_H__

#समावेश <type_support.h>

#अगर defined(ISP2401)

प्रकार काष्ठा isys_irqc_state_s isys_irqc_state_t;

काष्ठा isys_irqc_state_s अणु
	hrt_data edge;
	hrt_data mask;
	hrt_data status;
	hrt_data enable;
	hrt_data level_no;
	/*hrt_data clear;	*/	/* ग_लिखो-only रेजिस्टर */
पूर्ण;

#पूर्ण_अगर /* defined(ISP2401) */

#पूर्ण_अगर	/* __ISYS_IRQ_LOCAL_H__ */
