<शैली गुरु>
/*
 * include/linux/parman.h - Manager क्रम linear priority array areas
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2017 Jiri Pirko <jiri@mellanox.com>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _PARMAN_H
#घोषणा _PARMAN_H

#समावेश <linux/list.h>

क्रमागत parman_algo_type अणु
	PARMAN_ALGO_TYPE_LSORT,
पूर्ण;

काष्ठा parman_item अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ index;
पूर्ण;

काष्ठा parman_prio अणु
	काष्ठा list_head list;
	काष्ठा list_head item_list;
	अचिन्हित दीर्घ priority;
पूर्ण;

काष्ठा parman_ops अणु
	अचिन्हित दीर्घ base_count;
	अचिन्हित दीर्घ resize_step;
	पूर्णांक (*resize)(व्योम *priv, अचिन्हित दीर्घ new_count);
	व्योम (*move)(व्योम *priv, अचिन्हित दीर्घ from_index,
		     अचिन्हित दीर्घ to_index, अचिन्हित दीर्घ count);
	क्रमागत parman_algo_type algo;
पूर्ण;

काष्ठा parman;

काष्ठा parman *parman_create(स्थिर काष्ठा parman_ops *ops, व्योम *priv);
व्योम parman_destroy(काष्ठा parman *parman);
व्योम parman_prio_init(काष्ठा parman *parman, काष्ठा parman_prio *prio,
		      अचिन्हित दीर्घ priority);
व्योम parman_prio_fini(काष्ठा parman_prio *prio);
पूर्णांक parman_item_add(काष्ठा parman *parman, काष्ठा parman_prio *prio,
		    काष्ठा parman_item *item);
व्योम parman_item_हटाओ(काष्ठा parman *parman, काष्ठा parman_prio *prio,
			काष्ठा parman_item *item);

#पूर्ण_अगर
