<शैली गुरु>
/**************************************************************************
 *
 * Copyright 2006 Tungsten Graphics, Inc., Bismack, ND. USA.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 **************************************************************************/
/*
 * Simple खोलो hash tab implementation.
 *
 * Authors:
 * Thomas Hellstrथघm <thomas-at-tungstengraphics-करोt-com>
 */

#अगर_अघोषित DRM_HASHTAB_H
#घोषणा DRM_HASHTAB_H

#समावेश <linux/list.h>

#घोषणा drm_hash_entry(_ptr, _type, _member) container_of(_ptr, _type, _member)

काष्ठा drm_hash_item अणु
	काष्ठा hlist_node head;
	अचिन्हित दीर्घ key;
पूर्ण;

काष्ठा drm_खोलो_hash अणु
	काष्ठा hlist_head *table;
	u8 order;
पूर्ण;

पूर्णांक drm_ht_create(काष्ठा drm_खोलो_hash *ht, अचिन्हित पूर्णांक order);
पूर्णांक drm_ht_insert_item(काष्ठा drm_खोलो_hash *ht, काष्ठा drm_hash_item *item);
पूर्णांक drm_ht_just_insert_please(काष्ठा drm_खोलो_hash *ht, काष्ठा drm_hash_item *item,
			      अचिन्हित दीर्घ seed, पूर्णांक bits, पूर्णांक shअगरt,
			      अचिन्हित दीर्घ add);
पूर्णांक drm_ht_find_item(काष्ठा drm_खोलो_hash *ht, अचिन्हित दीर्घ key, काष्ठा drm_hash_item **item);

व्योम drm_ht_verbose_list(काष्ठा drm_खोलो_hash *ht, अचिन्हित दीर्घ key);
पूर्णांक drm_ht_हटाओ_key(काष्ठा drm_खोलो_hash *ht, अचिन्हित दीर्घ key);
पूर्णांक drm_ht_हटाओ_item(काष्ठा drm_खोलो_hash *ht, काष्ठा drm_hash_item *item);
व्योम drm_ht_हटाओ(काष्ठा drm_खोलो_hash *ht);

/*
 * RCU-safe पूर्णांकerface
 *
 * The user of this API needs to make sure that two or more instances of the
 * hash table manipulation functions are never run simultaneously.
 * The lookup function drm_ht_find_item_rcu may, however, run simultaneously
 * with any of the manipulation functions as दीर्घ as it's called from within
 * an RCU पढ़ो-locked section.
 */
#घोषणा drm_ht_insert_item_rcu drm_ht_insert_item
#घोषणा drm_ht_just_insert_please_rcu drm_ht_just_insert_please
#घोषणा drm_ht_हटाओ_key_rcu drm_ht_हटाओ_key
#घोषणा drm_ht_हटाओ_item_rcu drm_ht_हटाओ_item
#घोषणा drm_ht_find_item_rcu drm_ht_find_item

#पूर्ण_अगर
