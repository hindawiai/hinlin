<शैली गुरु>
#अगर_अघोषित __NET_SCHED_CODEL_H
#घोषणा __NET_SCHED_CODEL_H

/*
 * Codel - The Controlled-Delay Active Queue Management algorithm
 *
 *  Copyright (C) 2011-2012 Kathleen Nichols <nichols@pollere.com>
 *  Copyright (C) 2011-2012 Van Jacobson <van@pollere.net>
 *  Copyright (C) 2012 Michael D. Taht <dave.taht@bufferbloat.net>
 *  Copyright (C) 2012,2015 Eric Dumazet <edumazet@google.com>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the authors may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
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

#समावेश <linux/types.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/inet_ecn.h>

/* Controlling Queue Delay (CoDel) algorithm
 * =========================================
 * Source : Kathleen Nichols and Van Jacobson
 * http://queue.acm.org/detail.cfm?id=2209336
 *
 * Implemented on linux by Dave Taht and Eric Dumazet
 */


/* CoDel uses a 1024 nsec घड़ी, encoded in u32
 * This gives a range of 2199 seconds, because of चिन्हित compares
 */
प्रकार u32 codel_समय_प्रकार;
प्रकार s32 codel_tdअगरf_t;
#घोषणा CODEL_SHIFT 10
#घोषणा MS2TIME(a) ((a * NSEC_PER_MSEC) >> CODEL_SHIFT)

अटल अंतरभूत codel_समय_प्रकार codel_get_समय(व्योम)
अणु
	u64 ns = kसमय_get_ns();

	वापस ns >> CODEL_SHIFT;
पूर्ण

/* Dealing with समयr wrapping, according to RFC 1982, as desc in wikipedia:
 *  https://en.wikipedia.org/wiki/Serial_number_arithmetic#General_Solution
 * codel_समय_after(a,b) वापसs true अगर the समय a is after समय b.
 */
#घोषणा codel_समय_after(a, b)						\
	(typecheck(codel_समय_प्रकार, a) &&					\
	 typecheck(codel_समय_प्रकार, b) &&					\
	 ((s32)((a) - (b)) > 0))
#घोषणा codel_समय_beक्रमe(a, b) 	codel_समय_after(b, a)

#घोषणा codel_समय_after_eq(a, b)					\
	(typecheck(codel_समय_प्रकार, a) &&					\
	 typecheck(codel_समय_प्रकार, b) &&					\
	 ((s32)((a) - (b)) >= 0))
#घोषणा codel_समय_beक्रमe_eq(a, b)	codel_समय_after_eq(b, a)

अटल अंतरभूत u32 codel_समय_प्रकारo_us(codel_समय_प्रकार val)
अणु
	u64 valns = ((u64)val << CODEL_SHIFT);

	करो_भाग(valns, NSEC_PER_USEC);
	वापस (u32)valns;
पूर्ण

/**
 * काष्ठा codel_params - contains codel parameters
 * @target:	target queue size (in समय units)
 * @ce_threshold:  threshold क्रम marking packets with ECN CE
 * @पूर्णांकerval:	width of moving समय winकरोw
 * @mtu:	device mtu, or minimal queue backlog in bytes.
 * @ecn:	is Explicit Congestion Notअगरication enabled
 */
काष्ठा codel_params अणु
	codel_समय_प्रकार	target;
	codel_समय_प्रकार	ce_threshold;
	codel_समय_प्रकार	पूर्णांकerval;
	u32		mtu;
	bool		ecn;
पूर्ण;

/**
 * काष्ठा codel_vars - contains codel variables
 * @count:		how many drops we've करोne since the last समय we
 *			entered dropping state
 * @lastcount:		count at entry to dropping state
 * @dropping:		set to true अगर in dropping state
 * @rec_inv_वर्ग_मूल:	reciprocal value of वर्ग_मूल(count) >> 1
 * @first_above_समय:	when we went (or will go) continuously above target
 *			क्रम पूर्णांकerval
 * @drop_next:		समय to drop next packet, or when we dropped last
 * @ldelay:		sojourn समय of last dequeued packet
 */
काष्ठा codel_vars अणु
	u32		count;
	u32		lastcount;
	bool		dropping;
	u16		rec_inv_वर्ग_मूल;
	codel_समय_प्रकार	first_above_समय;
	codel_समय_प्रकार	drop_next;
	codel_समय_प्रकार	ldelay;
पूर्ण;

#घोषणा REC_INV_SQRT_BITS (8 * माप(u16)) /* or माप_in_bits(rec_inv_वर्ग_मूल) */
/* needed shअगरt to get a Q0.32 number from rec_inv_वर्ग_मूल */
#घोषणा REC_INV_SQRT_SHIFT (32 - REC_INV_SQRT_BITS)

/**
 * काष्ठा codel_stats - contains codel shared variables and stats
 * @maxpacket:	largest packet we've seen so far
 * @drop_count:	temp count of dropped packets in dequeue()
 * @drop_len:	bytes of dropped packets in dequeue()
 * ecn_mark:	number of packets we ECN marked instead of dropping
 * ce_mark:	number of packets CE marked because sojourn समय was above ce_threshold
 */
काष्ठा codel_stats अणु
	u32		maxpacket;
	u32		drop_count;
	u32		drop_len;
	u32		ecn_mark;
	u32		ce_mark;
पूर्ण;

#घोषणा CODEL_DISABLED_THRESHOLD पूर्णांक_उच्च

प्रकार u32 (*codel_skb_len_t)(स्थिर काष्ठा sk_buff *skb);
प्रकार codel_समय_प्रकार (*codel_skb_समय_प्रकार)(स्थिर काष्ठा sk_buff *skb);
प्रकार व्योम (*codel_skb_drop_t)(काष्ठा sk_buff *skb, व्योम *ctx);
प्रकार काष्ठा sk_buff * (*codel_skb_dequeue_t)(काष्ठा codel_vars *vars,
						व्योम *ctx);

#पूर्ण_अगर
