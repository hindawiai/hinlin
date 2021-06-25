<शैली गुरु>
/*
 * net/tipc/ib_media.c: Infiniband bearer support क्रम TIPC
 *
 * Copyright (c) 2013 Patrick McHardy <kaber@trash.net>
 *
 * Based on eth_media.c, which carries the following copyright notice:
 *
 * Copyright (c) 2001-2007, Ericsson AB
 * Copyright (c) 2005-2008, 2011, Wind River Systems
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

#समावेश <linux/अगर_infiniband.h>
#समावेश "core.h"
#समावेश "bearer.h"

#घोषणा TIPC_MAX_IB_LINK_WIN 500

/* convert InfiniBand address (media address क्रमmat) media address to string */
अटल पूर्णांक tipc_ib_addr2str(काष्ठा tipc_media_addr *a, अक्षर *str_buf,
			    पूर्णांक str_size)
अणु
	अगर (str_size < 60)	/* 60 = 19 * म_माप("xx:") + म_माप("xx\0") */
		वापस 1;

	प्र_लिखो(str_buf, "%20phC", a->value);

	वापस 0;
पूर्ण

/* Convert from media address क्रमmat to discovery message addr क्रमmat */
अटल पूर्णांक tipc_ib_addr2msg(अक्षर *msg, काष्ठा tipc_media_addr *addr)
अणु
	स_रखो(msg, 0, TIPC_MEDIA_INFO_SIZE);
	स_नकल(msg, addr->value, INFINIBAND_ALEN);
	वापस 0;
पूर्ण

/* Convert raw InfiniBand address क्रमmat to media addr क्रमmat */
अटल पूर्णांक tipc_ib_raw2addr(काष्ठा tipc_bearer *b,
			    काष्ठा tipc_media_addr *addr,
			    अक्षर *msg)
अणु
	स_रखो(addr, 0, माप(*addr));
	स_नकल(addr->value, msg, INFINIBAND_ALEN);
	addr->media_id = TIPC_MEDIA_TYPE_IB;
	addr->broadcast = !स_भेद(msg, b->bcast_addr.value,
				  INFINIBAND_ALEN);
	वापस 0;
पूर्ण

/* Convert discovery msg addr क्रमmat to InfiniBand media addr क्रमmat */
अटल पूर्णांक tipc_ib_msg2addr(काष्ठा tipc_bearer *b,
			    काष्ठा tipc_media_addr *addr,
			    अक्षर *msg)
अणु
	वापस tipc_ib_raw2addr(b, addr, msg);
पूर्ण

/* InfiniBand media registration info */
काष्ठा tipc_media ib_media_info = अणु
	.send_msg	= tipc_l2_send_msg,
	.enable_media	= tipc_enable_l2_media,
	.disable_media	= tipc_disable_l2_media,
	.addr2str	= tipc_ib_addr2str,
	.addr2msg	= tipc_ib_addr2msg,
	.msg2addr	= tipc_ib_msg2addr,
	.raw2addr	= tipc_ib_raw2addr,
	.priority	= TIPC_DEF_LINK_PRI,
	.tolerance	= TIPC_DEF_LINK_TOL,
	.min_win	= TIPC_DEF_LINK_WIN,
	.max_win	= TIPC_MAX_IB_LINK_WIN,
	.type_id	= TIPC_MEDIA_TYPE_IB,
	.hwaddr_len	= INFINIBAND_ALEN,
	.name		= "ib"
पूर्ण;
