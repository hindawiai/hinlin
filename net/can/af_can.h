<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/* Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
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
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#अगर_अघोषित AF_CAN_H
#घोषणा AF_CAN_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/can.h>

/* af_can rx dispatcher काष्ठाures */

काष्ठा receiver अणु
	काष्ठा hlist_node list;
	canid_t can_id;
	canid_t mask;
	अचिन्हित दीर्घ matches;
	व्योम (*func)(काष्ठा sk_buff *skb, व्योम *data);
	व्योम *data;
	अक्षर *ident;
	काष्ठा sock *sk;
	काष्ठा rcu_head rcu;
पूर्ण;

/* statistic काष्ठाures */

/* can be reset e.g. by can_init_stats() */
काष्ठा can_pkg_stats अणु
	अचिन्हित दीर्घ jअगरfies_init;

	अचिन्हित दीर्घ rx_frames;
	अचिन्हित दीर्घ tx_frames;
	अचिन्हित दीर्घ matches;

	अचिन्हित दीर्घ total_rx_rate;
	अचिन्हित दीर्घ total_tx_rate;
	अचिन्हित दीर्घ total_rx_match_ratio;

	अचिन्हित दीर्घ current_rx_rate;
	अचिन्हित दीर्घ current_tx_rate;
	अचिन्हित दीर्घ current_rx_match_ratio;

	अचिन्हित दीर्घ max_rx_rate;
	अचिन्हित दीर्घ max_tx_rate;
	अचिन्हित दीर्घ max_rx_match_ratio;

	अचिन्हित दीर्घ rx_frames_delta;
	अचिन्हित दीर्घ tx_frames_delta;
	अचिन्हित दीर्घ matches_delta;
पूर्ण;

/* persistent statistics */
काष्ठा can_rcv_lists_stats अणु
	अचिन्हित दीर्घ stats_reset;
	अचिन्हित दीर्घ user_reset;
	अचिन्हित दीर्घ rcv_entries;
	अचिन्हित दीर्घ rcv_entries_max;
पूर्ण;

/* function prototypes क्रम the CAN networklayer procfs (proc.c) */
व्योम can_init_proc(काष्ठा net *net);
व्योम can_हटाओ_proc(काष्ठा net *net);
व्योम can_stat_update(काष्ठा समयr_list *t);

#पूर्ण_अगर /* AF_CAN_H */
