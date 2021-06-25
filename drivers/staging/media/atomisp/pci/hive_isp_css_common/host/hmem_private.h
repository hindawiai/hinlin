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

#अगर_अघोषित __HMEM_PRIVATE_H_INCLUDED__
#घोषणा __HMEM_PRIVATE_H_INCLUDED__

#समावेश "hmem_public.h"

#समावेश "assert_support.h"

STORAGE_CLASS_HMEM_C माप_प्रकार माप_hmem(
    स्थिर hmem_ID_t		ID)
अणु
	निश्चित(ID < N_HMEM_ID);
	(व्योम)ID;
	वापस HMEM_SIZE * माप(hmem_data_t);
पूर्ण

#पूर्ण_अगर /* __HMEM_PRIVATE_H_INCLUDED__ */
