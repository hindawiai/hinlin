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

#अगर_अघोषित _IA_CSS_REFCOUNT_H_
#घोषणा _IA_CSS_REFCOUNT_H_

#समावेश <type_support.h>
#समावेश <प्रणाली_local.h>
#समावेश <ia_css_err.h>
#समावेश <ia_css_types.h>

प्रकार व्योम (*clear_func)(ia_css_ptr ptr);

/*! \मrief Function क्रम initializing refcount list
 *
 * \param[in]	size		Size of the refcount list.
 * \लeturn				ia_css_err
 */
पूर्णांक ia_css_refcount_init(uपूर्णांक32_t size);

/*! \मrief Function क्रम de-initializing refcount list
 *
 * \लeturn				None
 */
व्योम ia_css_refcount_uninit(व्योम);

/*! \मrief Function क्रम increasing reference by 1.
 *
 * \param[in]	id		ID of the object.
 * \param[in]	ptr		Data of the object (ptr).
 * \लeturn				ia_css_ptr (saved address)
 */
ia_css_ptr ia_css_refcount_increment(s32 id, ia_css_ptr ptr);

/*! \मrief Function क्रम decrease reference by 1.
 *
 * \param[in]	id		ID of the object.
 * \param[in]	ptr		Data of the object (ptr).
 *
 *	- true, अगर it is successful.
 *	- false, otherwise.
 */
bool ia_css_refcount_decrement(s32 id, ia_css_ptr ptr);

/*! \मrief Function to check अगर reference count is 1.
 *
 * \param[in]	ptr		Data of the object (ptr).
 *
 *	- true, अगर it is successful.
 *	- false, otherwise.
 */
bool ia_css_refcount_is_single(ia_css_ptr ptr);

/*! \मrief Function to clear reference list objects.
 *
 * \param[in]	id			ID of the object.
 * \param[in] clear_func	function to be run to मुक्त reference objects.
 *
 *  वापस				None
 */
व्योम ia_css_refcount_clear(s32 id,
			   clear_func clear_func_ptr);

/*! \मrief Function to verअगरy अगर object is valid
 *
 * \param[in] ptr       Data of the object (ptr)
 *
 *      - true, अगर valid
 *      - false, अगर invalid
 */
bool ia_css_refcount_is_valid(ia_css_ptr ptr);

#पूर्ण_अगर /* _IA_CSS_REFCOUNT_H_ */
