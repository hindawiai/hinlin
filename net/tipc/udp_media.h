<शैली गुरु>
/*
 * net/tipc/udp_media.h: Include file क्रम UDP bearer media
 *
 * Copyright (c) 1996-2006, 2013-2016, Ericsson AB
 * Copyright (c) 2005, 2010-2011, Wind River Systems
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

#अगर_घोषित CONFIG_TIPC_MEDIA_UDP
#अगर_अघोषित _TIPC_UDP_MEDIA_H
#घोषणा _TIPC_UDP_MEDIA_H

#समावेश <linux/ip.h>
#समावेश <linux/udp.h>

पूर्णांक tipc_udp_nl_bearer_add(काष्ठा tipc_bearer *b, काष्ठा nlattr *attr);
पूर्णांक tipc_udp_nl_add_bearer_data(काष्ठा tipc_nl_msg *msg, काष्ठा tipc_bearer *b);
पूर्णांक tipc_udp_nl_dump_remoteip(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);

/* check अगर configured MTU is too low क्रम tipc headers */
अटल अंतरभूत bool tipc_udp_mtu_bad(u32 mtu)
अणु
	अगर (mtu >= (TIPC_MIN_BEARER_MTU + माप(काष्ठा iphdr) +
	    माप(काष्ठा udphdr)))
		वापस false;

	pr_warn("MTU too low for tipc bearer\n");
	वापस true;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
