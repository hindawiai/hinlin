<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Stream Parser
 *
 * Copyright (c) 2016 Tom Herbert <tom@herbertland.com>
 */

#अगर_अघोषित __NET_STRPARSER_H_
#घोषणा __NET_STRPARSER_H_

#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>

#घोषणा STRP_STATS_ADD(stat, count) ((stat) += (count))
#घोषणा STRP_STATS_INCR(stat) ((stat)++)

काष्ठा strp_stats अणु
	अचिन्हित दीर्घ दीर्घ msgs;
	अचिन्हित दीर्घ दीर्घ bytes;
	अचिन्हित पूर्णांक mem_fail;
	अचिन्हित पूर्णांक need_more_hdr;
	अचिन्हित पूर्णांक msg_too_big;
	अचिन्हित पूर्णांक msg_समयouts;
	अचिन्हित पूर्णांक bad_hdr_len;
पूर्ण;

काष्ठा strp_aggr_stats अणु
	अचिन्हित दीर्घ दीर्घ msgs;
	अचिन्हित दीर्घ दीर्घ bytes;
	अचिन्हित पूर्णांक mem_fail;
	अचिन्हित पूर्णांक need_more_hdr;
	अचिन्हित पूर्णांक msg_too_big;
	अचिन्हित पूर्णांक msg_समयouts;
	अचिन्हित पूर्णांक bad_hdr_len;
	अचिन्हित पूर्णांक पातs;
	अचिन्हित पूर्णांक पूर्णांकerrupted;
	अचिन्हित पूर्णांक unrecov_पूर्णांकr;
पूर्ण;

काष्ठा strparser;

/* Callbacks are called with lock held क्रम the attached socket */
काष्ठा strp_callbacks अणु
	पूर्णांक (*parse_msg)(काष्ठा strparser *strp, काष्ठा sk_buff *skb);
	व्योम (*rcv_msg)(काष्ठा strparser *strp, काष्ठा sk_buff *skb);
	पूर्णांक (*पढ़ो_sock_करोne)(काष्ठा strparser *strp, पूर्णांक err);
	व्योम (*पात_parser)(काष्ठा strparser *strp, पूर्णांक err);
	व्योम (*lock)(काष्ठा strparser *strp);
	व्योम (*unlock)(काष्ठा strparser *strp);
पूर्ण;

काष्ठा strp_msg अणु
	पूर्णांक full_len;
	पूर्णांक offset;
पूर्ण;

अटल अंतरभूत काष्ठा strp_msg *strp_msg(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा strp_msg *)((व्योम *)skb->cb +
		दुरत्व(काष्ठा qdisc_skb_cb, data));
पूर्ण

/* Structure क्रम an attached lower socket */
काष्ठा strparser अणु
	काष्ठा sock *sk;

	u32 stopped : 1;
	u32 छोड़ोd : 1;
	u32 पातed : 1;
	u32 पूर्णांकerrupted : 1;
	u32 unrecov_पूर्णांकr : 1;

	काष्ठा sk_buff **skb_nextp;
	काष्ठा sk_buff *skb_head;
	अचिन्हित पूर्णांक need_bytes;
	काष्ठा delayed_work msg_समयr_work;
	काष्ठा work_काष्ठा work;
	काष्ठा strp_stats stats;
	काष्ठा strp_callbacks cb;
पूर्ण;

/* Must be called with lock held क्रम attached socket */
अटल अंतरभूत व्योम strp_छोड़ो(काष्ठा strparser *strp)
अणु
	strp->छोड़ोd = 1;
पूर्ण

/* May be called without holding lock क्रम attached socket */
व्योम strp_unछोड़ो(काष्ठा strparser *strp);
/* Must be called with process lock held (lock_sock) */
व्योम __strp_unछोड़ो(काष्ठा strparser *strp);

अटल अंतरभूत व्योम save_strp_stats(काष्ठा strparser *strp,
				   काष्ठा strp_aggr_stats *agg_stats)
अणु
	/* Save psock statistics in the mux when psock is being unattached. */

#घोषणा SAVE_PSOCK_STATS(_stat) (agg_stats->_stat +=		\
				 strp->stats._stat)
	SAVE_PSOCK_STATS(msgs);
	SAVE_PSOCK_STATS(bytes);
	SAVE_PSOCK_STATS(mem_fail);
	SAVE_PSOCK_STATS(need_more_hdr);
	SAVE_PSOCK_STATS(msg_too_big);
	SAVE_PSOCK_STATS(msg_समयouts);
	SAVE_PSOCK_STATS(bad_hdr_len);
#अघोषित SAVE_PSOCK_STATS

	अगर (strp->पातed)
		agg_stats->पातs++;
	अगर (strp->पूर्णांकerrupted)
		agg_stats->पूर्णांकerrupted++;
	अगर (strp->unrecov_पूर्णांकr)
		agg_stats->unrecov_पूर्णांकr++;
पूर्ण

अटल अंतरभूत व्योम aggregate_strp_stats(काष्ठा strp_aggr_stats *stats,
					काष्ठा strp_aggr_stats *agg_stats)
अणु
#घोषणा SAVE_PSOCK_STATS(_stat) (agg_stats->_stat += stats->_stat)
	SAVE_PSOCK_STATS(msgs);
	SAVE_PSOCK_STATS(bytes);
	SAVE_PSOCK_STATS(mem_fail);
	SAVE_PSOCK_STATS(need_more_hdr);
	SAVE_PSOCK_STATS(msg_too_big);
	SAVE_PSOCK_STATS(msg_समयouts);
	SAVE_PSOCK_STATS(bad_hdr_len);
	SAVE_PSOCK_STATS(पातs);
	SAVE_PSOCK_STATS(पूर्णांकerrupted);
	SAVE_PSOCK_STATS(unrecov_पूर्णांकr);
#अघोषित SAVE_PSOCK_STATS

पूर्ण

व्योम strp_करोne(काष्ठा strparser *strp);
व्योम strp_stop(काष्ठा strparser *strp);
व्योम strp_check_rcv(काष्ठा strparser *strp);
पूर्णांक strp_init(काष्ठा strparser *strp, काष्ठा sock *sk,
	      स्थिर काष्ठा strp_callbacks *cb);
व्योम strp_data_पढ़ोy(काष्ठा strparser *strp);
पूर्णांक strp_process(काष्ठा strparser *strp, काष्ठा sk_buff *orig_skb,
		 अचिन्हित पूर्णांक orig_offset, माप_प्रकार orig_len,
		 माप_प्रकार max_msg_size, दीर्घ समयo);

#पूर्ण_अगर /* __NET_STRPARSER_H_ */
