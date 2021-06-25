<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _CCID_H
#घोषणा _CCID_H
/*
 *  net/dccp/ccid.h
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 *  CCID infraकाष्ठाure
 */

#समावेश <net/sock.h>
#समावेश <linux/compiler.h>
#समावेश <linux/dccp.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>

/* maximum value क्रम a CCID (RFC 4340, 19.5) */
#घोषणा CCID_MAX		255
#घोषणा CCID_SLAB_NAME_LENGTH	32

काष्ठा tcp_info;

/**
 *  काष्ठा ccid_operations  -  Interface to Congestion-Control Infraकाष्ठाure
 *
 *  @ccid_id: numerical CCID ID (up to %CCID_MAX, cf. table 5 in RFC 4340, 10.)
 *  @ccid_ccmps: the CCMPS including network/transport headers (0 when disabled)
 *  @ccid_name: alphabetical identअगरier string क्रम @ccid_id
 *  @ccid_hc_अणुr,tपूर्णx_slab: memory pool क्रम the receiver/sender half-connection
 *  @ccid_hc_अणुr,tपूर्णx_obj_size: size of the receiver/sender half-connection socket
 *
 *  @ccid_hc_अणुr,tपूर्णx_init: CCID-specअगरic initialisation routine (beक्रमe startup)
 *  @ccid_hc_अणुr,tपूर्णx_निकास: CCID-specअगरic cleanup routine (beक्रमe deकाष्ठाion)
 *  @ccid_hc_rx_packet_recv: implements the HC-receiver side
 *  @ccid_hc_अणुr,tपूर्णx_parse_options: parsing routine क्रम CCID/HC-specअगरic options
 *  @ccid_hc_अणुr,tपूर्णx_insert_options: insert routine क्रम CCID/HC-specअगरic options
 *  @ccid_hc_tx_packet_recv: implements feedback processing क्रम the HC-sender
 *  @ccid_hc_tx_send_packet: implements the sending part of the HC-sender
 *  @ccid_hc_tx_packet_sent: करोes accounting क्रम packets in flight by HC-sender
 *  @ccid_hc_अणुr,tपूर्णx_get_info: INET_DIAG inक्रमmation क्रम HC-receiver/sender
 *  @ccid_hc_अणुr,tपूर्णx_माला_लोockopt: socket options specअगरic to HC-receiver/sender
 */
काष्ठा ccid_operations अणु
	अचिन्हित अक्षर		ccid_id;
	__u32			ccid_ccmps;
	स्थिर अक्षर		*ccid_name;
	काष्ठा kmem_cache	*ccid_hc_rx_slab,
				*ccid_hc_tx_slab;
	अक्षर			ccid_hc_rx_slab_name[CCID_SLAB_NAME_LENGTH];
	अक्षर			ccid_hc_tx_slab_name[CCID_SLAB_NAME_LENGTH];
	__u32			ccid_hc_rx_obj_size,
				ccid_hc_tx_obj_size;
	/* Interface Routines */
	पूर्णांक		(*ccid_hc_rx_init)(काष्ठा ccid *ccid, काष्ठा sock *sk);
	पूर्णांक		(*ccid_hc_tx_init)(काष्ठा ccid *ccid, काष्ठा sock *sk);
	व्योम		(*ccid_hc_rx_निकास)(काष्ठा sock *sk);
	व्योम		(*ccid_hc_tx_निकास)(काष्ठा sock *sk);
	व्योम		(*ccid_hc_rx_packet_recv)(काष्ठा sock *sk,
						  काष्ठा sk_buff *skb);
	पूर्णांक		(*ccid_hc_rx_parse_options)(काष्ठा sock *sk, u8 pkt,
						    u8 opt, u8 *val, u8 len);
	पूर्णांक		(*ccid_hc_rx_insert_options)(काष्ठा sock *sk,
						     काष्ठा sk_buff *skb);
	व्योम		(*ccid_hc_tx_packet_recv)(काष्ठा sock *sk,
						  काष्ठा sk_buff *skb);
	पूर्णांक		(*ccid_hc_tx_parse_options)(काष्ठा sock *sk, u8 pkt,
						    u8 opt, u8 *val, u8 len);
	पूर्णांक		(*ccid_hc_tx_send_packet)(काष्ठा sock *sk,
						  काष्ठा sk_buff *skb);
	व्योम		(*ccid_hc_tx_packet_sent)(काष्ठा sock *sk,
						  अचिन्हित पूर्णांक len);
	व्योम		(*ccid_hc_rx_get_info)(काष्ठा sock *sk,
					       काष्ठा tcp_info *info);
	व्योम		(*ccid_hc_tx_get_info)(काष्ठा sock *sk,
					       काष्ठा tcp_info *info);
	पूर्णांक		(*ccid_hc_rx_माला_लोockopt)(काष्ठा sock *sk,
						 स्थिर पूर्णांक optname, पूर्णांक len,
						 u32 __user *optval,
						 पूर्णांक __user *optlen);
	पूर्णांक		(*ccid_hc_tx_माला_लोockopt)(काष्ठा sock *sk,
						 स्थिर पूर्णांक optname, पूर्णांक len,
						 u32 __user *optval,
						 पूर्णांक __user *optlen);
पूर्ण;

बाह्य काष्ठा ccid_operations ccid2_ops;
#अगर_घोषित CONFIG_IP_DCCP_CCID3
बाह्य काष्ठा ccid_operations ccid3_ops;
#पूर्ण_अगर

पूर्णांक ccid_initialize_builtins(व्योम);
व्योम ccid_cleanup_builtins(व्योम);

काष्ठा ccid अणु
	काष्ठा ccid_operations *ccid_ops;
	अक्षर		       ccid_priv[];
पूर्ण;

अटल अंतरभूत व्योम *ccid_priv(स्थिर काष्ठा ccid *ccid)
अणु
	वापस (व्योम *)ccid->ccid_priv;
पूर्ण

bool ccid_support_check(u8 स्थिर *ccid_array, u8 array_len);
पूर्णांक ccid_get_builtin_ccids(u8 **ccid_array, u8 *array_len);
पूर्णांक ccid_माला_लोockopt_builtin_ccids(काष्ठा sock *sk, पूर्णांक len,
				  अक्षर __user *, पूर्णांक __user *);

काष्ठा ccid *ccid_new(स्थिर u8 id, काष्ठा sock *sk, bool rx);

अटल अंतरभूत पूर्णांक ccid_get_current_rx_ccid(काष्ठा dccp_sock *dp)
अणु
	काष्ठा ccid *ccid = dp->dccps_hc_rx_ccid;

	अगर (ccid == शून्य || ccid->ccid_ops == शून्य)
		वापस -1;
	वापस ccid->ccid_ops->ccid_id;
पूर्ण

अटल अंतरभूत पूर्णांक ccid_get_current_tx_ccid(काष्ठा dccp_sock *dp)
अणु
	काष्ठा ccid *ccid = dp->dccps_hc_tx_ccid;

	अगर (ccid == शून्य || ccid->ccid_ops == शून्य)
		वापस -1;
	वापस ccid->ccid_ops->ccid_id;
पूर्ण

व्योम ccid_hc_rx_delete(काष्ठा ccid *ccid, काष्ठा sock *sk);
व्योम ccid_hc_tx_delete(काष्ठा ccid *ccid, काष्ठा sock *sk);

/*
 * Congestion control of queued data packets via CCID decision.
 *
 * The TX CCID perक्रमms its congestion-control by indicating whether and when a
 * queued packet may be sent, using the वापस code of ccid_hc_tx_send_packet().
 * The following modes are supported via the symbolic स्थिरants below:
 * - समयr-based pacing    (CCID वापसs a delay value in milliseconds);
 * - स्वतःnomous dequeueing (CCID पूर्णांकernally schedules dccps_xmitlet).
 */

क्रमागत ccid_dequeueing_decision अणु
	CCID_PACKET_SEND_AT_ONCE =	 0x00000,  /* "green light": no delay */
	CCID_PACKET_DELAY_MAX =		 0x0FFFF,  /* maximum delay in msecs  */
	CCID_PACKET_DELAY =		 0x10000,  /* CCID msec-delay mode */
	CCID_PACKET_WILL_DEQUEUE_LATER = 0x20000,  /* CCID स्वतःnomous mode */
	CCID_PACKET_ERR =		 0xF0000,  /* error condition */
पूर्ण;

अटल अंतरभूत पूर्णांक ccid_packet_dequeue_eval(स्थिर पूर्णांक वापस_code)
अणु
	अगर (वापस_code < 0)
		वापस CCID_PACKET_ERR;
	अगर (वापस_code == 0)
		वापस CCID_PACKET_SEND_AT_ONCE;
	अगर (वापस_code <= CCID_PACKET_DELAY_MAX)
		वापस CCID_PACKET_DELAY;
	वापस वापस_code;
पूर्ण

अटल अंतरभूत पूर्णांक ccid_hc_tx_send_packet(काष्ठा ccid *ccid, काष्ठा sock *sk,
					 काष्ठा sk_buff *skb)
अणु
	अगर (ccid->ccid_ops->ccid_hc_tx_send_packet != शून्य)
		वापस ccid->ccid_ops->ccid_hc_tx_send_packet(sk, skb);
	वापस CCID_PACKET_SEND_AT_ONCE;
पूर्ण

अटल अंतरभूत व्योम ccid_hc_tx_packet_sent(काष्ठा ccid *ccid, काष्ठा sock *sk,
					  अचिन्हित पूर्णांक len)
अणु
	अगर (ccid->ccid_ops->ccid_hc_tx_packet_sent != शून्य)
		ccid->ccid_ops->ccid_hc_tx_packet_sent(sk, len);
पूर्ण

अटल अंतरभूत व्योम ccid_hc_rx_packet_recv(काष्ठा ccid *ccid, काष्ठा sock *sk,
					  काष्ठा sk_buff *skb)
अणु
	अगर (ccid->ccid_ops->ccid_hc_rx_packet_recv != शून्य)
		ccid->ccid_ops->ccid_hc_rx_packet_recv(sk, skb);
पूर्ण

अटल अंतरभूत व्योम ccid_hc_tx_packet_recv(काष्ठा ccid *ccid, काष्ठा sock *sk,
					  काष्ठा sk_buff *skb)
अणु
	अगर (ccid->ccid_ops->ccid_hc_tx_packet_recv != शून्य)
		ccid->ccid_ops->ccid_hc_tx_packet_recv(sk, skb);
पूर्ण

/**
 * ccid_hc_tx_parse_options  -  Parse CCID-specअगरic options sent by the receiver
 * @pkt: type of packet that @opt appears on (RFC 4340, 5.1)
 * @opt: the CCID-specअगरic option type (RFC 4340, 5.8 and 10.3)
 * @val: value of @opt
 * @len: length of @val in bytes
 */
अटल अंतरभूत पूर्णांक ccid_hc_tx_parse_options(काष्ठा ccid *ccid, काष्ठा sock *sk,
					   u8 pkt, u8 opt, u8 *val, u8 len)
अणु
	अगर (!ccid || !ccid->ccid_ops->ccid_hc_tx_parse_options)
		वापस 0;
	वापस ccid->ccid_ops->ccid_hc_tx_parse_options(sk, pkt, opt, val, len);
पूर्ण

/**
 * ccid_hc_rx_parse_options  -  Parse CCID-specअगरic options sent by the sender
 * Arguments are analogous to ccid_hc_tx_parse_options()
 */
अटल अंतरभूत पूर्णांक ccid_hc_rx_parse_options(काष्ठा ccid *ccid, काष्ठा sock *sk,
					   u8 pkt, u8 opt, u8 *val, u8 len)
अणु
	अगर (!ccid || !ccid->ccid_ops->ccid_hc_rx_parse_options)
		वापस 0;
	वापस ccid->ccid_ops->ccid_hc_rx_parse_options(sk, pkt, opt, val, len);
पूर्ण

अटल अंतरभूत पूर्णांक ccid_hc_rx_insert_options(काष्ठा ccid *ccid, काष्ठा sock *sk,
					    काष्ठा sk_buff *skb)
अणु
	अगर (ccid->ccid_ops->ccid_hc_rx_insert_options != शून्य)
		वापस ccid->ccid_ops->ccid_hc_rx_insert_options(sk, skb);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ccid_hc_rx_get_info(काष्ठा ccid *ccid, काष्ठा sock *sk,
				       काष्ठा tcp_info *info)
अणु
	अगर (ccid->ccid_ops->ccid_hc_rx_get_info != शून्य)
		ccid->ccid_ops->ccid_hc_rx_get_info(sk, info);
पूर्ण

अटल अंतरभूत व्योम ccid_hc_tx_get_info(काष्ठा ccid *ccid, काष्ठा sock *sk,
				       काष्ठा tcp_info *info)
अणु
	अगर (ccid->ccid_ops->ccid_hc_tx_get_info != शून्य)
		ccid->ccid_ops->ccid_hc_tx_get_info(sk, info);
पूर्ण

अटल अंतरभूत पूर्णांक ccid_hc_rx_माला_लोockopt(काष्ठा ccid *ccid, काष्ठा sock *sk,
					स्थिर पूर्णांक optname, पूर्णांक len,
					u32 __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक rc = -ENOPROTOOPT;
	अगर (ccid != शून्य && ccid->ccid_ops->ccid_hc_rx_माला_लोockopt != शून्य)
		rc = ccid->ccid_ops->ccid_hc_rx_माला_लोockopt(sk, optname, len,
						 optval, optlen);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक ccid_hc_tx_माला_लोockopt(काष्ठा ccid *ccid, काष्ठा sock *sk,
					स्थिर पूर्णांक optname, पूर्णांक len,
					u32 __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक rc = -ENOPROTOOPT;
	अगर (ccid != शून्य && ccid->ccid_ops->ccid_hc_tx_माला_लोockopt != शून्य)
		rc = ccid->ccid_ops->ccid_hc_tx_माला_लोockopt(sk, optname, len,
						 optval, optlen);
	वापस rc;
पूर्ण
#पूर्ण_अगर /* _CCID_H */
