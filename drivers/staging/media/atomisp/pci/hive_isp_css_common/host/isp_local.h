<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
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

#अगर_अघोषित __ISP_LOCAL_H_INCLUDED__
#घोषणा __ISP_LOCAL_H_INCLUDED__

#समावेश <stdbool.h>

#समावेश "isp_global.h"

#समावेश <isp2400_support.h>

#घोषणा HIVE_ISP_VMEM_MASK	((1U << ISP_VMEM_ELEMBITS) - 1)

प्रकार काष्ठा isp_state_s		isp_state_t;
प्रकार काष्ठा isp_stall_s		isp_stall_t;

काष्ठा isp_state_s अणु
	पूर्णांक	pc;
	पूर्णांक	status_रेजिस्टर;
	bool	is_broken;
	bool	is_idle;
	bool	is_sleeping;
	bool	is_stalling;
पूर्ण;

काष्ठा isp_stall_s अणु
	bool	fअगरo0;
	bool	fअगरo1;
	bool	fअगरo2;
	bool	fअगरo3;
	bool	fअगरo4;
	bool	fअगरo5;
	bool	fअगरo6;
	bool	stat_ctrl;
	bool	dmem;
	bool	vmem;
	bool	vamem1;
	bool	vamem2;
	bool	vamem3;
	bool	hmem;
	bool	pmem;
	bool	icache_master;
पूर्ण;

#पूर्ण_अगर /* __ISP_LOCAL_H_INCLUDED__ */
