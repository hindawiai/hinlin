<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2007 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश "dlm_internal.h"
#समावेश "config.h"
#समावेश "memory.h"

अटल काष्ठा kmem_cache *lkb_cache;
अटल काष्ठा kmem_cache *rsb_cache;


पूर्णांक __init dlm_memory_init(व्योम)
अणु
	lkb_cache = kmem_cache_create("dlm_lkb", माप(काष्ठा dlm_lkb),
				__alignof__(काष्ठा dlm_lkb), 0, शून्य);
	अगर (!lkb_cache)
		वापस -ENOMEM;

	rsb_cache = kmem_cache_create("dlm_rsb", माप(काष्ठा dlm_rsb),
				__alignof__(काष्ठा dlm_rsb), 0, शून्य);
	अगर (!rsb_cache) अणु
		kmem_cache_destroy(lkb_cache);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dlm_memory_निकास(व्योम)
अणु
	kmem_cache_destroy(lkb_cache);
	kmem_cache_destroy(rsb_cache);
पूर्ण

अक्षर *dlm_allocate_lvb(काष्ठा dlm_ls *ls)
अणु
	अक्षर *p;

	p = kzalloc(ls->ls_lvblen, GFP_NOFS);
	वापस p;
पूर्ण

व्योम dlm_मुक्त_lvb(अक्षर *p)
अणु
	kमुक्त(p);
पूर्ण

काष्ठा dlm_rsb *dlm_allocate_rsb(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_rsb *r;

	r = kmem_cache_zalloc(rsb_cache, GFP_NOFS);
	वापस r;
पूर्ण

व्योम dlm_मुक्त_rsb(काष्ठा dlm_rsb *r)
अणु
	अगर (r->res_lvbptr)
		dlm_मुक्त_lvb(r->res_lvbptr);
	kmem_cache_मुक्त(rsb_cache, r);
पूर्ण

काष्ठा dlm_lkb *dlm_allocate_lkb(काष्ठा dlm_ls *ls)
अणु
	काष्ठा dlm_lkb *lkb;

	lkb = kmem_cache_zalloc(lkb_cache, GFP_NOFS);
	वापस lkb;
पूर्ण

व्योम dlm_मुक्त_lkb(काष्ठा dlm_lkb *lkb)
अणु
	अगर (lkb->lkb_flags & DLM_IFL_USER) अणु
		काष्ठा dlm_user_args *ua;
		ua = lkb->lkb_ua;
		अगर (ua) अणु
			kमुक्त(ua->lksb.sb_lvbptr);
			kमुक्त(ua);
		पूर्ण
	पूर्ण
	kmem_cache_मुक्त(lkb_cache, lkb);
पूर्ण

