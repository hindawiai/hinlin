<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
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

#अगर_अघोषित _IA_CSS_RMGR_VBUF_H
#घोषणा _IA_CSS_RMGR_VBUF_H

#समावेश "ia_css_rmgr.h"
#समावेश <type_support.h>
#समावेश <ia_css_types.h>
#समावेश <प्रणाली_local.h>

/**
 * @brief Data काष्ठाure क्रम the resource handle (host, vbuf)
 */
काष्ठा ia_css_rmgr_vbuf_handle अणु
	ia_css_ptr vptr;
	u8 count;
	u32 size;
पूर्ण;

/**
 * @brief Data काष्ठाure क्रम the resource pool (host, vbuf)
 */
काष्ठा ia_css_rmgr_vbuf_pool अणु
	u8 copy_on_ग_लिखो;
	u8 recycle;
	u32 size;
	u32 index;
	काष्ठा ia_css_rmgr_vbuf_handle **handles;
पूर्ण;

/**
 * @brief VBUF resource pools
 */
बाह्य काष्ठा ia_css_rmgr_vbuf_pool *vbuf_ref;
बाह्य काष्ठा ia_css_rmgr_vbuf_pool *vbuf_ग_लिखो;
बाह्य काष्ठा ia_css_rmgr_vbuf_pool *hmm_buffer_pool;

/**
 * @brief Initialize the resource pool (host, vbuf)
 *
 * @param pool	The poपूर्णांकer to the pool
 */
STORAGE_CLASS_RMGR_H पूर्णांक ia_css_rmgr_init_vbuf(
    काष्ठा ia_css_rmgr_vbuf_pool *pool);

/**
 * @brief Uninitialize the resource pool (host, vbuf)
 *
 * @param pool	The poपूर्णांकer to the pool
 */
STORAGE_CLASS_RMGR_H व्योम ia_css_rmgr_uninit_vbuf(
    काष्ठा ia_css_rmgr_vbuf_pool *pool);

/**
 * @brief Acquire a handle from the pool (host, vbuf)
 *
 * @param pool		The poपूर्णांकer to the pool
 * @param handle	The poपूर्णांकer to the handle
 */
STORAGE_CLASS_RMGR_H व्योम ia_css_rmgr_acq_vbuf(
    काष्ठा ia_css_rmgr_vbuf_pool *pool,
    काष्ठा ia_css_rmgr_vbuf_handle **handle);

/**
 * @brief Release a handle to the pool (host, vbuf)
 *
 * @param pool		The poपूर्णांकer to the pool
 * @param handle	The poपूर्णांकer to the handle
 */
STORAGE_CLASS_RMGR_H व्योम ia_css_rmgr_rel_vbuf(
    काष्ठा ia_css_rmgr_vbuf_pool *pool,
    काष्ठा ia_css_rmgr_vbuf_handle **handle);

/**
 * @brief Retain the reference count क्रम a handle (host, vbuf)
 *
 * @param handle	The poपूर्णांकer to the handle
 */
व्योम ia_css_rmgr_refcount_retain_vbuf(काष्ठा ia_css_rmgr_vbuf_handle **handle);

/**
 * @brief Release the reference count क्रम a handle (host, vbuf)
 *
 * @param handle	The poपूर्णांकer to the handle
 */
व्योम ia_css_rmgr_refcount_release_vbuf(काष्ठा ia_css_rmgr_vbuf_handle **handle);

#पूर्ण_अगर	/* _IA_CSS_RMGR_VBUF_H */
