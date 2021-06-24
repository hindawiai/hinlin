<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CSIO_DEFS_H__
#घोषणा __CSIO_DEFS_H__

#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/bug.h>
#समावेश <linux/pci.h>
#समावेश <linux/jअगरfies.h>

#घोषणा CSIO_INVALID_IDX		0xFFFFFFFF
#घोषणा CSIO_INC_STATS(elem, val)	((elem)->stats.val++)
#घोषणा CSIO_DEC_STATS(elem, val)	((elem)->stats.val--)
#घोषणा CSIO_VALID_WWN(__n)		((*__n >> 4) == 0x5 ? true : false)
#घोषणा CSIO_DID_MASK			0xFFFFFF
#घोषणा CSIO_WORD_TO_BYTE		4

#अगर_अघोषित पढ़ोq
अटल अंतरभूत u64 पढ़ोq(व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr) + ((u64)पढ़ोl(addr + 4) << 32);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोq(u64 val, व्योम __iomem *addr)
अणु
	ग_लिखोl(val, addr);
	ग_लिखोl(val >> 32, addr + 4);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक
csio_list_deleted(काष्ठा list_head *list)
अणु
	वापस ((list->next == list) && (list->prev == list));
पूर्ण

#घोषणा csio_list_next(elem)	(((काष्ठा list_head *)(elem))->next)
#घोषणा csio_list_prev(elem)	(((काष्ठा list_head *)(elem))->prev)

/* State machine */
प्रकार व्योम (*csio_sm_state_t)(व्योम *, uपूर्णांक32_t);

काष्ठा csio_sm अणु
	काष्ठा list_head	sm_list;
	csio_sm_state_t		sm_state;
पूर्ण;

अटल अंतरभूत व्योम
csio_set_state(व्योम *smp, व्योम *state)
अणु
	((काष्ठा csio_sm *)smp)->sm_state = (csio_sm_state_t)state;
पूर्ण

अटल अंतरभूत व्योम
csio_init_state(काष्ठा csio_sm *smp, व्योम *state)
अणु
	csio_set_state(smp, state);
पूर्ण

अटल अंतरभूत व्योम
csio_post_event(व्योम *smp, uपूर्णांक32_t evt)
अणु
	((काष्ठा csio_sm *)smp)->sm_state(smp, evt);
पूर्ण

अटल अंतरभूत csio_sm_state_t
csio_get_state(व्योम *smp)
अणु
	वापस ((काष्ठा csio_sm *)smp)->sm_state;
पूर्ण

अटल अंतरभूत bool
csio_match_state(व्योम *smp, व्योम *state)
अणु
	वापस (csio_get_state(smp) == (csio_sm_state_t)state);
पूर्ण

#घोषणा	CSIO_ASSERT(cond)		BUG_ON(!(cond))

#अगर_घोषित __CSIO_DEBUG__
#घोषणा CSIO_DB_ASSERT(__c)		CSIO_ASSERT((__c))
#अन्यथा
#घोषणा CSIO_DB_ASSERT(__c)
#पूर्ण_अगर

#पूर्ण_अगर /* अगरndef __CSIO_DEFS_H__ */
