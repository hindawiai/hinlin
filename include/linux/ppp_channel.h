<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _PPP_CHANNEL_H_
#घोषणा _PPP_CHANNEL_H_
/*
 * Definitions क्रम the पूर्णांकerface between the generic PPP code
 * and a PPP channel.
 *
 * A PPP channel provides a way क्रम the generic PPP code to send
 * and receive packets over some sort of communications medium.
 * Packets are stored in sk_buffs and have the 2-byte PPP protocol
 * number at the start, but not the address and control bytes.
 *
 * Copyright 1999 Paul Mackerras.
 *
 * ==खाताVERSION 20000322==
 */

#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/poll.h>
#समावेश <net/net_namespace.h>

काष्ठा ppp_channel;

काष्ठा ppp_channel_ops अणु
	/* Send a packet (or multilink fragment) on this channel.
	   Returns 1 अगर it was accepted, 0 अगर not. */
	पूर्णांक	(*start_xmit)(काष्ठा ppp_channel *, काष्ठा sk_buff *);
	/* Handle an ioctl call that has come in via /dev/ppp. */
	पूर्णांक	(*ioctl)(काष्ठा ppp_channel *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
	पूर्णांक	(*fill_क्रमward_path)(काष्ठा net_device_path_ctx *,
				     काष्ठा net_device_path *,
				     स्थिर काष्ठा ppp_channel *);
पूर्ण;

काष्ठा ppp_channel अणु
	व्योम		*निजी;	/* channel निजी data */
	स्थिर काष्ठा ppp_channel_ops *ops; /* operations क्रम this channel */
	पूर्णांक		mtu;		/* max transmit packet size */
	पूर्णांक		hdrlen;		/* amount of headroom channel needs */
	व्योम		*ppp;		/* opaque to channel */
	पूर्णांक		speed;		/* transfer rate (bytes/second) */
	/* the following is not used at present */
	पूर्णांक		latency;	/* overhead समय in milliseconds */
पूर्ण;

#अगर_घोषित __KERNEL__
/* Called by the channel when it can send some more data. */
बाह्य व्योम ppp_output_wakeup(काष्ठा ppp_channel *);

/* Called by the channel to process a received PPP packet.
   The packet should have just the 2-byte PPP protocol header. */
बाह्य व्योम ppp_input(काष्ठा ppp_channel *, काष्ठा sk_buff *);

/* Called by the channel when an input error occurs, indicating
   that we may have missed a packet. */
बाह्य व्योम ppp_input_error(काष्ठा ppp_channel *, पूर्णांक code);

/* Attach a channel to a given PPP unit in specअगरied net. */
बाह्य पूर्णांक ppp_रेजिस्टर_net_channel(काष्ठा net *, काष्ठा ppp_channel *);

/* Attach a channel to a given PPP unit. */
बाह्य पूर्णांक ppp_रेजिस्टर_channel(काष्ठा ppp_channel *);

/* Detach a channel from its PPP unit (e.g. on hangup). */
बाह्य व्योम ppp_unरेजिस्टर_channel(काष्ठा ppp_channel *);

/* Get the channel number क्रम a channel */
बाह्य पूर्णांक ppp_channel_index(काष्ठा ppp_channel *);

/* Get the unit number associated with a channel, or -1 अगर none */
बाह्य पूर्णांक ppp_unit_number(काष्ठा ppp_channel *);

/* Get the device name associated with a channel, or शून्य अगर none */
बाह्य अक्षर *ppp_dev_name(काष्ठा ppp_channel *);

/*
 * SMP locking notes:
 * The channel code must ensure that when it calls ppp_unरेजिस्टर_channel,
 * nothing is executing in any of the procedures above, क्रम that
 * channel.  The generic layer will ensure that nothing is executing
 * in the start_xmit and ioctl routines क्रम the channel by the समय
 * that ppp_unरेजिस्टर_channel वापसs.
 */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
