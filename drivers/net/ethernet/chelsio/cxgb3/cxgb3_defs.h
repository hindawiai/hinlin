<शैली गुरु>
/*
 * Copyright (c) 2006-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#अगर_अघोषित _CHELSIO_DEFS_H
#घोषणा _CHELSIO_DEFS_H

#समावेश <linux/skbuff.h>
#समावेश <net/tcp.h>

#समावेश "t3cdev.h"

#समावेश "cxgb3_offload.h"

#घोषणा VALIDATE_TID 1

/*
 * Map an ATID or STID to their entries in the corresponding TID tables.
 */
अटल अंतरभूत जोड़ active_खोलो_entry *atid2entry(स्थिर काष्ठा tid_info *t,
						  अचिन्हित पूर्णांक atid)
अणु
	वापस &t->atid_tab[atid - t->atid_base];
पूर्ण

अटल अंतरभूत जोड़ listen_entry *stid2entry(स्थिर काष्ठा tid_info *t,
					     अचिन्हित पूर्णांक stid)
अणु
	वापस &t->stid_tab[stid - t->stid_base];
पूर्ण

/*
 * Find the connection corresponding to a TID.
 */
अटल अंतरभूत काष्ठा t3c_tid_entry *lookup_tid(स्थिर काष्ठा tid_info *t,
					       अचिन्हित पूर्णांक tid)
अणु
	काष्ठा t3c_tid_entry *t3c_tid = tid < t->ntids ?
	    &(t->tid_tab[tid]) : शून्य;

	वापस (t3c_tid && t3c_tid->client) ? t3c_tid : शून्य;
पूर्ण

/*
 * Find the connection corresponding to a server TID.
 */
अटल अंतरभूत काष्ठा t3c_tid_entry *lookup_stid(स्थिर काष्ठा tid_info *t,
						अचिन्हित पूर्णांक tid)
अणु
	जोड़ listen_entry *e;

	अगर (tid < t->stid_base || tid >= t->stid_base + t->nstids)
		वापस शून्य;

	e = stid2entry(t, tid);
	अगर ((व्योम *)e->next >= (व्योम *)t->tid_tab &&
	    (व्योम *)e->next < (व्योम *)&t->atid_tab[t->natids])
		वापस शून्य;

	वापस &e->t3c_tid;
पूर्ण

/*
 * Find the connection corresponding to an active-खोलो TID.
 */
अटल अंतरभूत काष्ठा t3c_tid_entry *lookup_atid(स्थिर काष्ठा tid_info *t,
						अचिन्हित पूर्णांक tid)
अणु
	जोड़ active_खोलो_entry *e;

	अगर (tid < t->atid_base || tid >= t->atid_base + t->natids)
		वापस शून्य;

	e = atid2entry(t, tid);
	अगर ((व्योम *)e->next >= (व्योम *)t->tid_tab &&
	    (व्योम *)e->next < (व्योम *)&t->atid_tab[t->natids])
		वापस शून्य;

	वापस &e->t3c_tid;
पूर्ण

पूर्णांक attach_t3cdev(काष्ठा t3cdev *dev);
व्योम detach_t3cdev(काष्ठा t3cdev *dev);
#पूर्ण_अगर
