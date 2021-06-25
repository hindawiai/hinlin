<शैली गुरु>
#अगर_अघोषित __NET_SCHED_CODEL_IMPL_H
#घोषणा __NET_SCHED_CODEL_IMPL_H

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

/* Controlling Queue Delay (CoDel) algorithm
 * =========================================
 * Source : Kathleen Nichols and Van Jacobson
 * http://queue.acm.org/detail.cfm?id=2209336
 *
 * Implemented on linux by Dave Taht and Eric Dumazet
 */

अटल व्योम codel_params_init(काष्ठा codel_params *params)
अणु
	params->पूर्णांकerval = MS2TIME(100);
	params->target = MS2TIME(5);
	params->ce_threshold = CODEL_DISABLED_THRESHOLD;
	params->ecn = false;
पूर्ण

अटल व्योम codel_vars_init(काष्ठा codel_vars *vars)
अणु
	स_रखो(vars, 0, माप(*vars));
पूर्ण

अटल व्योम codel_stats_init(काष्ठा codel_stats *stats)
अणु
	stats->maxpacket = 0;
पूर्ण

/*
 * http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Iterative_methods_क्रम_reciprocal_square_roots
 * new_invवर्ग_मूल = (invवर्ग_मूल / 2) * (3 - count * invवर्ग_मूल^2)
 *
 * Here, invवर्ग_मूल is a fixed poपूर्णांक number (< 1.0), 32bit mantissa, aka Q0.32
 */
अटल व्योम codel_Newton_step(काष्ठा codel_vars *vars)
अणु
	u32 invवर्ग_मूल = ((u32)vars->rec_inv_वर्ग_मूल) << REC_INV_SQRT_SHIFT;
	u32 invवर्ग_मूल2 = ((u64)invवर्ग_मूल * invवर्ग_मूल) >> 32;
	u64 val = (3LL << 32) - ((u64)vars->count * invवर्ग_मूल2);

	val >>= 2; /* aव्योम overflow in following multiply */
	val = (val * invवर्ग_मूल) >> (32 - 2 + 1);

	vars->rec_inv_वर्ग_मूल = val >> REC_INV_SQRT_SHIFT;
पूर्ण

/*
 * CoDel control_law is t + पूर्णांकerval/वर्ग_मूल(count)
 * We मुख्यtain in rec_inv_वर्ग_मूल the reciprocal value of वर्ग_मूल(count) to aव्योम
 * both वर्ग_मूल() and भागide operation.
 */
अटल codel_समय_प्रकार codel_control_law(codel_समय_प्रकार t,
				      codel_समय_प्रकार पूर्णांकerval,
				      u32 rec_inv_वर्ग_मूल)
अणु
	वापस t + reciprocal_scale(पूर्णांकerval, rec_inv_वर्ग_मूल << REC_INV_SQRT_SHIFT);
पूर्ण

अटल bool codel_should_drop(स्थिर काष्ठा sk_buff *skb,
			      व्योम *ctx,
			      काष्ठा codel_vars *vars,
			      काष्ठा codel_params *params,
			      काष्ठा codel_stats *stats,
			      codel_skb_len_t skb_len_func,
			      codel_skb_समय_प्रकार skb_समय_func,
			      u32 *backlog,
			      codel_समय_प्रकार now)
अणु
	bool ok_to_drop;
	u32 skb_len;

	अगर (!skb) अणु
		vars->first_above_समय = 0;
		वापस false;
	पूर्ण

	skb_len = skb_len_func(skb);
	vars->ldelay = now - skb_समय_func(skb);

	अगर (unlikely(skb_len > stats->maxpacket))
		stats->maxpacket = skb_len;

	अगर (codel_समय_beक्रमe(vars->ldelay, params->target) ||
	    *backlog <= params->mtu) अणु
		/* went below - stay below क्रम at least पूर्णांकerval */
		vars->first_above_समय = 0;
		वापस false;
	पूर्ण
	ok_to_drop = false;
	अगर (vars->first_above_समय == 0) अणु
		/* just went above from below. If we stay above
		 * क्रम at least पूर्णांकerval we'll say it's ok to drop
		 */
		vars->first_above_समय = now + params->पूर्णांकerval;
	पूर्ण अन्यथा अगर (codel_समय_after(now, vars->first_above_समय)) अणु
		ok_to_drop = true;
	पूर्ण
	वापस ok_to_drop;
पूर्ण

अटल काष्ठा sk_buff *codel_dequeue(व्योम *ctx,
				     u32 *backlog,
				     काष्ठा codel_params *params,
				     काष्ठा codel_vars *vars,
				     काष्ठा codel_stats *stats,
				     codel_skb_len_t skb_len_func,
				     codel_skb_समय_प्रकार skb_समय_func,
				     codel_skb_drop_t drop_func,
				     codel_skb_dequeue_t dequeue_func)
अणु
	काष्ठा sk_buff *skb = dequeue_func(vars, ctx);
	codel_समय_प्रकार now;
	bool drop;

	अगर (!skb) अणु
		vars->dropping = false;
		वापस skb;
	पूर्ण
	now = codel_get_समय();
	drop = codel_should_drop(skb, ctx, vars, params, stats,
				 skb_len_func, skb_समय_func, backlog, now);
	अगर (vars->dropping) अणु
		अगर (!drop) अणु
			/* sojourn समय below target - leave dropping state */
			vars->dropping = false;
		पूर्ण अन्यथा अगर (codel_समय_after_eq(now, vars->drop_next)) अणु
			/* It's समय क्रम the next drop. Drop the current
			 * packet and dequeue the next. The dequeue might
			 * take us out of dropping state.
			 * If not, schedule the next drop.
			 * A large backlog might result in drop rates so high
			 * that the next drop should happen now,
			 * hence the जबतक loop.
			 */
			जबतक (vars->dropping &&
			       codel_समय_after_eq(now, vars->drop_next)) अणु
				vars->count++; /* करोnt care of possible wrap
						* since there is no more भागide
						*/
				codel_Newton_step(vars);
				अगर (params->ecn && INET_ECN_set_ce(skb)) अणु
					stats->ecn_mark++;
					vars->drop_next =
						codel_control_law(vars->drop_next,
								  params->पूर्णांकerval,
								  vars->rec_inv_वर्ग_मूल);
					जाओ end;
				पूर्ण
				stats->drop_len += skb_len_func(skb);
				drop_func(skb, ctx);
				stats->drop_count++;
				skb = dequeue_func(vars, ctx);
				अगर (!codel_should_drop(skb, ctx,
						       vars, params, stats,
						       skb_len_func,
						       skb_समय_func,
						       backlog, now)) अणु
					/* leave dropping state */
					vars->dropping = false;
				पूर्ण अन्यथा अणु
					/* and schedule the next drop */
					vars->drop_next =
						codel_control_law(vars->drop_next,
								  params->पूर्णांकerval,
								  vars->rec_inv_वर्ग_मूल);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (drop) अणु
		u32 delta;

		अगर (params->ecn && INET_ECN_set_ce(skb)) अणु
			stats->ecn_mark++;
		पूर्ण अन्यथा अणु
			stats->drop_len += skb_len_func(skb);
			drop_func(skb, ctx);
			stats->drop_count++;

			skb = dequeue_func(vars, ctx);
			drop = codel_should_drop(skb, ctx, vars, params,
						 stats, skb_len_func,
						 skb_समय_func, backlog, now);
		पूर्ण
		vars->dropping = true;
		/* अगर min went above target बंद to when we last went below it
		 * assume that the drop rate that controlled the queue on the
		 * last cycle is a good starting poपूर्णांक to control it now.
		 */
		delta = vars->count - vars->lastcount;
		अगर (delta > 1 &&
		    codel_समय_beक्रमe(now - vars->drop_next,
				      16 * params->पूर्णांकerval)) अणु
			vars->count = delta;
			/* we करोnt care अगर rec_inv_वर्ग_मूल approximation
			 * is not very precise :
			 * Next Newton steps will correct it quadratically.
			 */
			codel_Newton_step(vars);
		पूर्ण अन्यथा अणु
			vars->count = 1;
			vars->rec_inv_वर्ग_मूल = ~0U >> REC_INV_SQRT_SHIFT;
		पूर्ण
		vars->lastcount = vars->count;
		vars->drop_next = codel_control_law(now, params->पूर्णांकerval,
						    vars->rec_inv_वर्ग_मूल);
	पूर्ण
end:
	अगर (skb && codel_समय_after(vars->ldelay, params->ce_threshold) &&
	    INET_ECN_set_ce(skb))
		stats->ce_mark++;
	वापस skb;
पूर्ण

#पूर्ण_अगर
