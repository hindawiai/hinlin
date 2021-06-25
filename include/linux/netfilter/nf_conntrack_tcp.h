<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_TCP_H
#घोषणा _NF_CONNTRACK_TCP_H

#समावेश <uapi/linux/netfilter/nf_conntrack_tcp.h>


काष्ठा ip_ct_tcp_state अणु
	u_पूर्णांक32_t	td_end;		/* max of seq + len */
	u_पूर्णांक32_t	td_maxend;	/* max of ack + max(win, 1) */
	u_पूर्णांक32_t	td_maxwin;	/* max(win) */
	u_पूर्णांक32_t	td_maxack;	/* max of ack */
	u_पूर्णांक8_t	td_scale;	/* winकरोw scale factor */
	u_पूर्णांक8_t	flags;		/* per direction options */
पूर्ण;

काष्ठा ip_ct_tcp अणु
	काष्ठा ip_ct_tcp_state seen[2];	/* connection parameters per direction */
	u_पूर्णांक8_t	state;		/* state of the connection (क्रमागत tcp_conntrack) */
	/* For detecting stale connections */
	u_पूर्णांक8_t	last_dir;	/* Direction of the last packet (क्रमागत ip_conntrack_dir) */
	u_पूर्णांक8_t	retrans;	/* Number of retransmitted packets */
	u_पूर्णांक8_t	last_index;	/* Index of the last packet */
	u_पूर्णांक32_t	last_seq;	/* Last sequence number seen in dir */
	u_पूर्णांक32_t	last_ack;	/* Last sequence number seen in opposite dir */
	u_पूर्णांक32_t	last_end;	/* Last seq + len */
	u_पूर्णांक16_t	last_win;	/* Last winकरोw advertisement seen in dir */
	/* For SYN packets जबतक we may be out-of-sync */
	u_पूर्णांक8_t	last_wscale;	/* Last winकरोw scaling factor seen */
	u_पूर्णांक8_t	last_flags;	/* Last flags set */
पूर्ण;

#पूर्ण_अगर /* _NF_CONNTRACK_TCP_H */
