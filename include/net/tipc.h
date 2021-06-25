<शैली गुरु>
/*
 * include/net/tipc.h: Include file क्रम TIPC message header routines
 *
 * Copyright (c) 2017 Ericsson AB
 * All rights reserved.
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

#अगर_अघोषित _TIPC_HDR_H
#घोषणा _TIPC_HDR_H

#समावेश <linux/अक्रमom.h>

#घोषणा KEEPALIVE_MSG_MASK 0x0e080000  /* LINK_PROTOCOL + MSG_IS_KEEPALIVE */

काष्ठा tipc_basic_hdr अणु
	__be32 w[4];
पूर्ण;

अटल अंतरभूत __be32 tipc_hdr_rps_key(काष्ठा tipc_basic_hdr *hdr)
अणु
	u32 w0 = ntohl(hdr->w[0]);
	bool keepalive_msg = (w0 & KEEPALIVE_MSG_MASK) == KEEPALIVE_MSG_MASK;
	__be32 key;

	/* Return source node identity as key */
	अगर (likely(!keepalive_msg))
		वापस hdr->w[3];

	/* Spपढ़ो PROBE/PROBE_REPLY messages across the cores */
	get_अक्रमom_bytes(&key, माप(key));
	वापस key;
पूर्ण

#पूर्ण_अगर
