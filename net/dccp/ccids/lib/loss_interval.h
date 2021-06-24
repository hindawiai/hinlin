<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _DCCP_LI_HIST_
#घोषणा _DCCP_LI_HIST_
/*
 *  Copyright (c) 2007   The University of Aberdeen, Scotland, UK
 *  Copyright (c) 2005-7 The University of Waikato, Hamilton, New Zealand.
 *  Copyright (c) 2005-7 Ian McDonald <ian.mcकरोnald@jandi.co.nz>
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

/*
 * Number of loss पूर्णांकervals (RFC 4342, 8.6.1). The history size is one more than
 * NINTERVAL, since the `खोलो' पूर्णांकerval I_0 is always stored as the first entry.
 */
#घोषणा NINTERVAL	8
#घोषणा LIH_SIZE	(NINTERVAL + 1)

/**
 *  tfrc_loss_पूर्णांकerval  -  Loss history record क्रम TFRC-based protocols
 *  @li_seqno:		Highest received seqno beक्रमe the start of loss
 *  @li_ccval:		The CCVal beदीर्घing to @li_seqno
 *  @li_is_बंदd:	Whether @li_seqno is older than 1 RTT
 *  @li_length:		Loss पूर्णांकerval sequence length
 */
काष्ठा tfrc_loss_पूर्णांकerval अणु
	u64		 li_seqno:48,
			 li_ccval:4,
			 li_is_बंदd:1;
	u32		 li_length;
पूर्ण;

/**
 *  tfrc_loss_hist  -  Loss record database
 *  @ring:	Circular queue managed in LIFO manner
 *  @counter:	Current count of entries (can be more than %LIH_SIZE)
 *  @i_mean:	Current Average Loss Interval [RFC 3448, 5.4]
 */
काष्ठा tfrc_loss_hist अणु
	काष्ठा tfrc_loss_पूर्णांकerval	*ring[LIH_SIZE];
	u8				counter;
	u32				i_mean;
पूर्ण;

अटल अंतरभूत व्योम tfrc_lh_init(काष्ठा tfrc_loss_hist *lh)
अणु
	स_रखो(lh, 0, माप(काष्ठा tfrc_loss_hist));
पूर्ण

अटल अंतरभूत u8 tfrc_lh_is_initialised(काष्ठा tfrc_loss_hist *lh)
अणु
	वापस lh->counter > 0;
पूर्ण

अटल अंतरभूत u8 tfrc_lh_length(काष्ठा tfrc_loss_hist *lh)
अणु
	वापस min(lh->counter, (u8)LIH_SIZE);
पूर्ण

काष्ठा tfrc_rx_hist;

पूर्णांक tfrc_lh_पूर्णांकerval_add(काष्ठा tfrc_loss_hist *, काष्ठा tfrc_rx_hist *,
			 u32 (*first_li)(काष्ठा sock *), काष्ठा sock *);
u8 tfrc_lh_update_i_mean(काष्ठा tfrc_loss_hist *lh, काष्ठा sk_buff *);
व्योम tfrc_lh_cleanup(काष्ठा tfrc_loss_hist *lh);

#पूर्ण_अगर /* _DCCP_LI_HIST_ */
