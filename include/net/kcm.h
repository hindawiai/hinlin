<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Kernel Connection Multiplexor
 *
 * Copyright (c) 2016 Tom Herbert <tom@herbertland.com>
 */

#अगर_अघोषित __NET_KCM_H_
#घोषणा __NET_KCM_H_

#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/strparser.h>
#समावेश <uapi/linux/kcm.h>

बाह्य अचिन्हित पूर्णांक kcm_net_id;

#घोषणा KCM_STATS_ADD(stat, count) ((stat) += (count))
#घोषणा KCM_STATS_INCR(stat) ((stat)++)

काष्ठा kcm_psock_stats अणु
	अचिन्हित दीर्घ दीर्घ tx_msgs;
	अचिन्हित दीर्घ दीर्घ tx_bytes;
	अचिन्हित दीर्घ दीर्घ reserved;
	अचिन्हित दीर्घ दीर्घ unreserved;
	अचिन्हित पूर्णांक tx_पातs;
पूर्ण;

काष्ठा kcm_mux_stats अणु
	अचिन्हित दीर्घ दीर्घ rx_msgs;
	अचिन्हित दीर्घ दीर्घ rx_bytes;
	अचिन्हित दीर्घ दीर्घ tx_msgs;
	अचिन्हित दीर्घ दीर्घ tx_bytes;
	अचिन्हित पूर्णांक rx_पढ़ोy_drops;
	अचिन्हित पूर्णांक tx_retries;
	अचिन्हित पूर्णांक psock_attach;
	अचिन्हित पूर्णांक psock_unattach_rsvd;
	अचिन्हित पूर्णांक psock_unattach;
पूर्ण;

काष्ठा kcm_stats अणु
	अचिन्हित दीर्घ दीर्घ rx_msgs;
	अचिन्हित दीर्घ दीर्घ rx_bytes;
	अचिन्हित दीर्घ दीर्घ tx_msgs;
	अचिन्हित दीर्घ दीर्घ tx_bytes;
पूर्ण;

काष्ठा kcm_tx_msg अणु
	अचिन्हित पूर्णांक sent;
	अचिन्हित पूर्णांक fragidx;
	अचिन्हित पूर्णांक frag_offset;
	अचिन्हित पूर्णांक msg_flags;
	काष्ठा sk_buff *frag_skb;
	काष्ठा sk_buff *last_skb;
पूर्ण;

/* Socket काष्ठाure क्रम KCM client sockets */
काष्ठा kcm_sock अणु
	काष्ठा sock sk;
	काष्ठा kcm_mux *mux;
	काष्ठा list_head kcm_sock_list;
	पूर्णांक index;
	u32 करोne : 1;
	काष्ठा work_काष्ठा करोne_work;

	काष्ठा kcm_stats stats;

	/* Transmit */
	काष्ठा kcm_psock *tx_psock;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा list_head रुको_psock_list;
	काष्ठा sk_buff *seq_skb;
	u32 tx_stopped : 1;

	/* Don't use bit fields here, these are set under dअगरferent locks */
	bool tx_रुको;
	bool tx_रुको_more;

	/* Receive */
	काष्ठा kcm_psock *rx_psock;
	काष्ठा list_head रुको_rx_list; /* KCMs रुकोing क्रम receiving */
	bool rx_रुको;
	u32 rx_disabled : 1;
पूर्ण;

काष्ठा bpf_prog;

/* Structure क्रम an attached lower socket */
काष्ठा kcm_psock अणु
	काष्ठा sock *sk;
	काष्ठा strparser strp;
	काष्ठा kcm_mux *mux;
	पूर्णांक index;

	u32 tx_stopped : 1;
	u32 करोne : 1;
	u32 unattaching : 1;

	व्योम (*save_state_change)(काष्ठा sock *sk);
	व्योम (*save_data_पढ़ोy)(काष्ठा sock *sk);
	व्योम (*save_ग_लिखो_space)(काष्ठा sock *sk);

	काष्ठा list_head psock_list;

	काष्ठा kcm_psock_stats stats;

	/* Receive */
	काष्ठा list_head psock_पढ़ोy_list;
	काष्ठा bpf_prog *bpf_prog;
	काष्ठा kcm_sock *rx_kcm;
	अचिन्हित दीर्घ दीर्घ saved_rx_bytes;
	अचिन्हित दीर्घ दीर्घ saved_rx_msgs;
	काष्ठा sk_buff *पढ़ोy_rx_msg;

	/* Transmit */
	काष्ठा kcm_sock *tx_kcm;
	काष्ठा list_head psock_avail_list;
	अचिन्हित दीर्घ दीर्घ saved_tx_bytes;
	अचिन्हित दीर्घ दीर्घ saved_tx_msgs;
पूर्ण;

/* Per net MUX list */
काष्ठा kcm_net अणु
	काष्ठा mutex mutex;
	काष्ठा kcm_psock_stats aggregate_psock_stats;
	काष्ठा kcm_mux_stats aggregate_mux_stats;
	काष्ठा strp_aggr_stats aggregate_strp_stats;
	काष्ठा list_head mux_list;
	पूर्णांक count;
पूर्ण;

/* Structure क्रम a MUX */
काष्ठा kcm_mux अणु
	काष्ठा list_head kcm_mux_list;
	काष्ठा rcu_head rcu;
	काष्ठा kcm_net *knet;

	काष्ठा list_head kcm_socks;	/* All KCM sockets on MUX */
	पूर्णांक kcm_socks_cnt;		/* Total KCM socket count क्रम MUX */
	काष्ठा list_head psocks;	/* List of all psocks on MUX */
	पूर्णांक psocks_cnt;		/* Total attached sockets */

	काष्ठा kcm_mux_stats stats;
	काष्ठा kcm_psock_stats aggregate_psock_stats;
	काष्ठा strp_aggr_stats aggregate_strp_stats;

	/* Receive */
	spinlock_t rx_lock ____cacheline_aligned_in_smp;
	काष्ठा list_head kcm_rx_रुकोers; /* KCMs रुकोing क्रम receiving */
	काष्ठा list_head psocks_पढ़ोy;	/* List of psocks with a msg पढ़ोy */
	काष्ठा sk_buff_head rx_hold_queue;

	/* Transmit */
	spinlock_t  lock ____cacheline_aligned_in_smp;	/* TX and mux locking */
	काष्ठा list_head psocks_avail;	/* List of available psocks */
	काष्ठा list_head kcm_tx_रुकोers; /* KCMs रुकोing क्रम a TX psock */
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक kcm_proc_init(व्योम);
व्योम kcm_proc_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक kcm_proc_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम kcm_proc_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम aggregate_psock_stats(काष्ठा kcm_psock_stats *stats,
					 काष्ठा kcm_psock_stats *agg_stats)
अणु
	/* Save psock statistics in the mux when psock is being unattached. */

#घोषणा SAVE_PSOCK_STATS(_stat) (agg_stats->_stat += stats->_stat)
	SAVE_PSOCK_STATS(tx_msgs);
	SAVE_PSOCK_STATS(tx_bytes);
	SAVE_PSOCK_STATS(reserved);
	SAVE_PSOCK_STATS(unreserved);
	SAVE_PSOCK_STATS(tx_पातs);
#अघोषित SAVE_PSOCK_STATS
पूर्ण

अटल अंतरभूत व्योम aggregate_mux_stats(काष्ठा kcm_mux_stats *stats,
				       काष्ठा kcm_mux_stats *agg_stats)
अणु
	/* Save psock statistics in the mux when psock is being unattached. */

#घोषणा SAVE_MUX_STATS(_stat) (agg_stats->_stat += stats->_stat)
	SAVE_MUX_STATS(rx_msgs);
	SAVE_MUX_STATS(rx_bytes);
	SAVE_MUX_STATS(tx_msgs);
	SAVE_MUX_STATS(tx_bytes);
	SAVE_MUX_STATS(rx_पढ़ोy_drops);
	SAVE_MUX_STATS(psock_attach);
	SAVE_MUX_STATS(psock_unattach_rsvd);
	SAVE_MUX_STATS(psock_unattach);
#अघोषित SAVE_MUX_STATS
पूर्ण

#पूर्ण_अगर /* __NET_KCM_H_ */
