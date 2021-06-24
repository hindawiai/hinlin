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

#अगर_अघोषित __VMEM_LOCAL_H_INCLUDED__
#घोषणा __VMEM_LOCAL_H_INCLUDED__

#समावेश "type_support.h"
#समावेश "vmem_global.h"

प्रकार u16 t_vmem_elem;

#घोषणा VMEM_ARRAY(x, s)    t_vmem_elem x[s / ISP_NWAY][ISP_NWAY]

व्योम isp_vmem_load(
    स्थिर isp_ID_t		ID,
    स्थिर t_vmem_elem	*from,
    t_vmem_elem		*to,
    अचिन्हित पूर्णांक elems); /* In t_vmem_elem */

व्योम isp_vmem_store(
    स्थिर isp_ID_t		ID,
    t_vmem_elem		*to,
    स्थिर t_vmem_elem	*from,
    अचिन्हित पूर्णांक elems); /* In t_vmem_elem */

व्योम isp_vmem_2d_load(
    स्थिर isp_ID_t		ID,
    स्थिर t_vmem_elem	*from,
    t_vmem_elem		*to,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक stride_to,  /* In t_vmem_elem */

    अचिन्हित		stride_from /* In t_vmem_elem */);

व्योम isp_vmem_2d_store(
    स्थिर isp_ID_t		ID,
    t_vmem_elem		*to,
    स्थिर t_vmem_elem	*from,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक stride_to,  /* In t_vmem_elem */

    अचिन्हित		stride_from /* In t_vmem_elem */);

#पूर्ण_अगर /* __VMEM_LOCAL_H_INCLUDED__ */
