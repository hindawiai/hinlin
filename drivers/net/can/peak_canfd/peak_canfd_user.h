<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* CAN driver क्रम PEAK System micro-CAN based adapters
 *
 * Copyright (C) 2003-2011 PEAK System-Technik GmbH
 * Copyright (C) 2011-2013 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 */
#अगर_अघोषित PEAK_CANFD_USER_H
#घोषणा PEAK_CANFD_USER_H

#समावेश <linux/can/dev/peak_canfd.h>

#घोषणा PCANFD_ECHO_SKB_DEF		-1

/* data काष्ठाure निजी to each uCAN पूर्णांकerface */
काष्ठा peak_canfd_priv अणु
	काष्ठा can_priv can;		/* socket-can निजी data */
	काष्ठा net_device *ndev;	/* network device */
	पूर्णांक index;			/* channel index */

	काष्ठा can_berr_counter bec;	/* rx/tx err counters */

	पूर्णांक echo_idx;			/* echo skb मुक्त slot index */
	spinlock_t echo_lock;

	पूर्णांक cmd_len;
	व्योम *cmd_buffer;
	पूर्णांक cmd_maxlen;

	पूर्णांक (*pre_cmd)(काष्ठा peak_canfd_priv *priv);
	पूर्णांक (*ग_लिखो_cmd)(काष्ठा peak_canfd_priv *priv);
	पूर्णांक (*post_cmd)(काष्ठा peak_canfd_priv *priv);

	पूर्णांक (*enable_tx_path)(काष्ठा peak_canfd_priv *priv);
	व्योम *(*alloc_tx_msg)(काष्ठा peak_canfd_priv *priv, u16 msg_size,
			      पूर्णांक *room_left);
	पूर्णांक (*ग_लिखो_tx_msg)(काष्ठा peak_canfd_priv *priv,
			    काष्ठा pucan_tx_msg *msg);
पूर्ण;

काष्ठा net_device *alloc_peak_canfd_dev(पूर्णांक माप_priv, पूर्णांक index,
					पूर्णांक echo_skb_max);
पूर्णांक peak_canfd_handle_msg(काष्ठा peak_canfd_priv *priv,
			  काष्ठा pucan_rx_msg *msg);
पूर्णांक peak_canfd_handle_msgs_list(काष्ठा peak_canfd_priv *priv,
				काष्ठा pucan_rx_msg *rx_msg, पूर्णांक rx_count);
#पूर्ण_अगर
