<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश "hmm.h"
#समावेश "ia_css_rmgr.h"

#समावेश <type_support.h>
#समावेश <निश्चित_support.h>
#समावेश <platक्रमm_support.h> /* स_रखो */
#समावेश <ia_css_debug.h>

/*
 * @brief VBUF resource handles
 */
#घोषणा NUM_HANDLES 1000
अटल काष्ठा ia_css_rmgr_vbuf_handle handle_table[NUM_HANDLES];

/*
 * @brief VBUF resource pool - refpool
 */
अटल काष्ठा ia_css_rmgr_vbuf_pool refpool;

/*
 * @brief VBUF resource pool - ग_लिखोpool
 */
अटल काष्ठा ia_css_rmgr_vbuf_pool ग_लिखोpool = अणु
	.copy_on_ग_लिखो	= true,
पूर्ण;

/*
 * @brief VBUF resource pool - hmmbufferpool
 */
अटल काष्ठा ia_css_rmgr_vbuf_pool hmmbufferpool = अणु
	.copy_on_ग_लिखो	= true,
	.recycle	= true,
	.size		= 32,
पूर्ण;

काष्ठा ia_css_rmgr_vbuf_pool *vbuf_ref = &refpool;
काष्ठा ia_css_rmgr_vbuf_pool *vbuf_ग_लिखो = &ग_लिखोpool;
काष्ठा ia_css_rmgr_vbuf_pool *hmm_buffer_pool = &hmmbufferpool;

/*
 * @brief Initialize the reference count (host, vbuf)
 */
अटल व्योम rmgr_refcount_init_vbuf(व्योम)
अणु
	/* initialize the refcount table */
	स_रखो(&handle_table, 0, माप(handle_table));
पूर्ण

/*
 * @brief Retain the reference count क्रम a handle (host, vbuf)
 *
 * @param handle	The poपूर्णांकer to the handle
 */
व्योम ia_css_rmgr_refcount_retain_vbuf(काष्ठा ia_css_rmgr_vbuf_handle **handle)
अणु
	पूर्णांक i;
	काष्ठा ia_css_rmgr_vbuf_handle *h;

	अगर ((!handle) || (!*handle)) अणु
		IA_CSS_LOG("Invalid inputs");
		वापस;
	पूर्ण
	/* new vbuf to count on */
	अगर ((*handle)->count == 0) अणु
		h = *handle;
		*handle = शून्य;
		क्रम (i = 0; i < NUM_HANDLES; i++) अणु
			अगर (handle_table[i].count == 0) अणु
				*handle = &handle_table[i];
				अवरोध;
			पूर्ण
		पूर्ण
		/* अगर the loop dus not अवरोध and *handle == शून्य
		 * this is an error handle and report it.
		 */
		अगर (!*handle) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR,
					    "ia_css_i_host_refcount_retain_vbuf() failed to find empty slot!\n");
			वापस;
		पूर्ण
		(*handle)->vptr = h->vptr;
		(*handle)->size = h->size;
	पूर्ण
	(*handle)->count++;
पूर्ण

/*
 * @brief Release the reference count क्रम a handle (host, vbuf)
 *
 * @param handle	The poपूर्णांकer to the handle
 */
व्योम ia_css_rmgr_refcount_release_vbuf(काष्ठा ia_css_rmgr_vbuf_handle **handle)
अणु
	अगर ((!handle) || ((*handle) == शून्य) || (((*handle)->count) == 0)) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR, "%s invalid arguments!\n", __func__);
		वापस;
	पूर्ण
	/* decrease reference count */
	(*handle)->count--;
	/* हटाओ from admin */
	अगर ((*handle)->count == 0) अणु
		(*handle)->vptr = 0x0;
		(*handle)->size = 0;
		*handle = शून्य;
	पूर्ण
पूर्ण

/*
 * @brief Initialize the resource pool (host, vbuf)
 *
 * @param pool	The poपूर्णांकer to the pool
 */
पूर्णांक ia_css_rmgr_init_vbuf(काष्ठा ia_css_rmgr_vbuf_pool *pool)
अणु
	पूर्णांक err = 0;
	माप_प्रकार bytes_needed;

	rmgr_refcount_init_vbuf();
	निश्चित(pool);
	अगर (!pool)
		वापस -EINVAL;
	/* initialize the recycle pool अगर used */
	अगर (pool->recycle && pool->size) अणु
		/* allocate memory क्रम storing the handles */
		bytes_needed =
		    माप(व्योम *) *
		    pool->size;
		pool->handles = kvदो_स्मृति(bytes_needed, GFP_KERNEL);
		अगर (pool->handles)
			स_रखो(pool->handles, 0, bytes_needed);
		अन्यथा
			err = -ENOMEM;
	पूर्ण अन्यथा अणु
		/* just in हाल, set the size to 0 */
		pool->size = 0;
		pool->handles = शून्य;
	पूर्ण
	वापस err;
पूर्ण

/*
 * @brief Uninitialize the resource pool (host, vbuf)
 *
 * @param pool	The poपूर्णांकer to the pool
 */
व्योम ia_css_rmgr_uninit_vbuf(काष्ठा ia_css_rmgr_vbuf_pool *pool)
अणु
	u32 i;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s\n", __func__);
	अगर (!pool) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR, "%s NULL argument\n", __func__);
		वापस;
	पूर्ण
	अगर (pool->handles) अणु
		/* मुक्त the hmm buffers */
		क्रम (i = 0; i < pool->size; i++) अणु
			अगर (pool->handles[i]) अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "   freeing/releasing %x (count=%d)\n",
						    pool->handles[i]->vptr,
						    pool->handles[i]->count);
				/* मुक्त memory */
				hmm_मुक्त(pool->handles[i]->vptr);
				/* हटाओ from refcount admin */
				ia_css_rmgr_refcount_release_vbuf(&pool->handles[i]);
			पूर्ण
		पूर्ण
		/* now मुक्त the pool handles list */
		kvमुक्त(pool->handles);
		pool->handles = शून्य;
	पूर्ण
पूर्ण

/*
 * @brief Push a handle to the pool
 *
 * @param pool		The poपूर्णांकer to the pool
 * @param handle	The poपूर्णांकer to the handle
 */
अटल
व्योम rmgr_push_handle(काष्ठा ia_css_rmgr_vbuf_pool *pool,
		      काष्ठा ia_css_rmgr_vbuf_handle **handle)
अणु
	u32 i;
	bool succes = false;

	निश्चित(pool);
	निश्चित(pool->recycle);
	निश्चित(pool->handles);
	निश्चित(handle);
	क्रम (i = 0; i < pool->size; i++) अणु
		अगर (!pool->handles[i]) अणु
			ia_css_rmgr_refcount_retain_vbuf(handle);
			pool->handles[i] = *handle;
			succes = true;
			अवरोध;
		पूर्ण
	पूर्ण
	निश्चित(succes);
पूर्ण

/*
 * @brief Pop a handle from the pool
 *
 * @param pool		The poपूर्णांकer to the pool
 * @param handle	The poपूर्णांकer to the handle
 */
अटल
व्योम rmgr_pop_handle(काष्ठा ia_css_rmgr_vbuf_pool *pool,
		     काष्ठा ia_css_rmgr_vbuf_handle **handle)
अणु
	u32 i;

	निश्चित(pool);
	निश्चित(pool->recycle);
	निश्चित(pool->handles);
	निश्चित(handle);
	निश्चित(*handle);
	क्रम (i = 0; i < pool->size; i++) अणु
		अगर ((pool->handles[i]) &&
		    (pool->handles[i]->size == (*handle)->size)) अणु
			*handle = pool->handles[i];
			pool->handles[i] = शून्य;
			/* करोnt release, we are वापसing it...
			 * ia_css_rmgr_refcount_release_vbuf(handle);
			 */
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * @brief Acquire a handle from the pool (host, vbuf)
 *
 * @param pool		The poपूर्णांकer to the pool
 * @param handle	The poपूर्णांकer to the handle
 */
व्योम ia_css_rmgr_acq_vbuf(काष्ठा ia_css_rmgr_vbuf_pool *pool,
			  काष्ठा ia_css_rmgr_vbuf_handle **handle)
अणु
	काष्ठा ia_css_rmgr_vbuf_handle h;

	अगर ((!pool) || (!handle) || (!*handle)) अणु
		IA_CSS_LOG("Invalid inputs");
		वापस;
	पूर्ण

	अगर (pool->copy_on_ग_लिखो) अणु
		/* only one reference, reuse (no new retain) */
		अगर ((*handle)->count == 1)
			वापस;
		/* more than one reference, release current buffer */
		अगर ((*handle)->count > 1) अणु
			/* store current values */
			h.vptr = 0x0;
			h.size = (*handle)->size;
			/* release ref to current buffer */
			ia_css_rmgr_refcount_release_vbuf(handle);
			*handle = &h;
		पूर्ण
		/* get new buffer क्रम needed size */
		अगर ((*handle)->vptr == 0x0) अणु
			अगर (pool->recycle) अणु
				/* try and pop from pool */
				rmgr_pop_handle(pool, handle);
			पूर्ण
			अगर ((*handle)->vptr == 0x0) अणु
				/* we need to allocate */
				(*handle)->vptr = hmm_alloc((*handle)->size,
							     HMM_BO_PRIVATE, 0, शून्य, 0);
			पूर्ण अन्यथा अणु
				/* we popped a buffer */
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Note that handle will change to an पूर्णांकernally मुख्यtained one */
	ia_css_rmgr_refcount_retain_vbuf(handle);
पूर्ण

/*
 * @brief Release a handle to the pool (host, vbuf)
 *
 * @param pool		The poपूर्णांकer to the pool
 * @param handle	The poपूर्णांकer to the handle
 */
व्योम ia_css_rmgr_rel_vbuf(काष्ठा ia_css_rmgr_vbuf_pool *pool,
			  काष्ठा ia_css_rmgr_vbuf_handle **handle)
अणु
	अगर ((!pool) || (!handle) || (!*handle)) अणु
		IA_CSS_LOG("Invalid inputs");
		वापस;
	पूर्ण
	/* release the handle */
	अगर ((*handle)->count == 1) अणु
		अगर (!pool->recycle) अणु
			/* non recycling pool, मुक्त mem */
			hmm_मुक्त((*handle)->vptr);
		पूर्ण अन्यथा अणु
			/* recycle to pool */
			rmgr_push_handle(pool, handle);
		पूर्ण
	पूर्ण
	ia_css_rmgr_refcount_release_vbuf(handle);
	*handle = शून्य;
पूर्ण
