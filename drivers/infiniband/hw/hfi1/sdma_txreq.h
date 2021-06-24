<शैली गुरु>
/*
 * Copyright(c) 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#अगर_अघोषित HFI1_SDMA_TXREQ_H
#घोषणा HFI1_SDMA_TXREQ_H

/* increased क्रम AHG */
#घोषणा NUM_DESC 6

/*
 * काष्ठा sdma_desc - canonical fragment descriptor
 *
 * This is the descriptor carried in the tx request
 * corresponding to each fragment.
 *
 */
काष्ठा sdma_desc अणु
	/* निजी:  करोn't use directly */
	u64 qw[2];
पूर्ण;

/**
 * काष्ठा sdma_txreq - the sdma_txreq काष्ठाure (one per packet)
 * @list: क्रम use by user and by queuing क्रम रुको
 *
 * This is the representation of a packet which consists of some
 * number of fragments.   Storage is provided to within the काष्ठाure.
 * क्रम all fragments.
 *
 * The storage क्रम the descriptors are स्वतःmatically extended as needed
 * when the currently allocation is exceeded.
 *
 * The user (Verbs or PSM) may overload this काष्ठाure with fields
 * specअगरic to their use by putting this काष्ठा first in their काष्ठा.
 * The method of allocation of the overloaded काष्ठाure is user dependent
 *
 * The list is the only खुला field in the काष्ठाure.
 *
 */

#घोषणा SDMA_TXREQ_S_OK        0
#घोषणा SDMA_TXREQ_S_SENDERROR 1
#घोषणा SDMA_TXREQ_S_ABORTED   2
#घोषणा SDMA_TXREQ_S_SHUTDOWN  3

/* flags bits */
#घोषणा SDMA_TXREQ_F_URGENT       0x0001
#घोषणा SDMA_TXREQ_F_AHG_COPY     0x0002
#घोषणा SDMA_TXREQ_F_USE_AHG      0x0004
#घोषणा SDMA_TXREQ_F_VIP          0x0010

काष्ठा sdma_txreq;
प्रकार व्योम (*callback_t)(काष्ठा sdma_txreq *, पूर्णांक);

काष्ठा ioरुको;
काष्ठा sdma_txreq अणु
	काष्ठा list_head list;
	/* निजी: */
	काष्ठा sdma_desc *descp;
	/* निजी: */
	व्योम *coalesce_buf;
	/* निजी: */
	काष्ठा ioरुको *रुको;
	/* निजी: */
	callback_t                  complete;
#अगर_घोषित CONFIG_HFI1_DEBUG_SDMA_ORDER
	u64 sn;
#पूर्ण_अगर
	/* निजी: - used in coalesce/pad processing */
	u16                         packet_len;
	/* निजी: - करोwn-counted to trigger last */
	u16                         tlen;
	/* निजी: */
	u16                         num_desc;
	/* निजी: */
	u16                         desc_limit;
	/* निजी: */
	u16                         next_descq_idx;
	/* निजी: */
	u16 coalesce_idx;
	/* निजी: flags */
	u16                         flags;
	/* निजी: */
	काष्ठा sdma_desc descs[NUM_DESC];
पूर्ण;

अटल अंतरभूत पूर्णांक sdma_txreq_built(काष्ठा sdma_txreq *tx)
अणु
	वापस tx->num_desc;
पूर्ण

#पूर्ण_अगर                          /* HFI1_SDMA_TXREQ_H */
