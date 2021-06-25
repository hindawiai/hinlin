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

#अगर_अघोषित _IA_CSS_RMGR_H
#घोषणा _IA_CSS_RMGR_H

#समावेश <ia_css_err.h>

#अगर_अघोषित __INLINE_RMGR__
#घोषणा STORAGE_CLASS_RMGR_H बाह्य
#घोषणा STORAGE_CLASS_RMGR_C
#अन्यथा				/* __INLINE_RMGR__ */
#घोषणा STORAGE_CLASS_RMGR_H अटल अंतरभूत
#घोषणा STORAGE_CLASS_RMGR_C अटल अंतरभूत
#पूर्ण_अगर				/* __INLINE_RMGR__ */

/**
 * @brief Initialize resource manager (host/common)
 */
पूर्णांक ia_css_rmgr_init(व्योम);

/**
 * @brief Uninitialize resource manager (host/common)
 */
व्योम ia_css_rmgr_uninit(व्योम);

/*****************************************************************
 * Interface definition - resource type (host/common)
 *****************************************************************
 *
 * काष्ठा ia_css_rmgr_<type>_pool;
 * काष्ठा ia_css_rmgr_<type>_handle;
 *
 * STORAGE_CLASS_RMGR_H व्योम ia_css_rmgr_init_<type>(
 *	काष्ठा ia_css_rmgr_<type>_pool *pool);
 *
 * STORAGE_CLASS_RMGR_H व्योम ia_css_rmgr_uninit_<type>(
 *	काष्ठा ia_css_rmgr_<type>_pool *pool);
 *
 * STORAGE_CLASS_RMGR_H व्योम ia_css_rmgr_acq_<type>(
 *	काष्ठा ia_css_rmgr_<type>_pool *pool,
 *	काष्ठा ia_css_rmgr_<type>_handle **handle);
 *
 * STORAGE_CLASS_RMGR_H व्योम ia_css_rmgr_rel_<type>(
 *	काष्ठा ia_css_rmgr_<type>_pool *pool,
 *	काष्ठा ia_css_rmgr_<type>_handle **handle);
 *
 *****************************************************************
 * Interface definition - refcounting (host/common)
 *****************************************************************
 *
 * व्योम ia_css_rmgr_refcount_retain_<type>(
 *	काष्ठा ia_css_rmgr_<type>_handle **handle);
 *
 * व्योम ia_css_rmgr_refcount_release_<type>(
 *	काष्ठा ia_css_rmgr_<type>_handle **handle);
 */

#समावेश "ia_css_rmgr_vbuf.h"

#पूर्ण_अगर	/* _IA_CSS_RMGR_H */
