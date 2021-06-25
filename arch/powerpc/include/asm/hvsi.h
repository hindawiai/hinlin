<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _HVSI_H
#घोषणा _HVSI_H

#घोषणा VS_DATA_PACKET_HEADER           0xff
#घोषणा VS_CONTROL_PACKET_HEADER        0xfe
#घोषणा VS_QUERY_PACKET_HEADER          0xfd
#घोषणा VS_QUERY_RESPONSE_PACKET_HEADER 0xfc

/* control verbs */
#घोषणा VSV_SET_MODEM_CTL    1 /* to service processor only */
#घोषणा VSV_MODEM_CTL_UPDATE 2 /* from service processor only */
#घोषणा VSV_CLOSE_PROTOCOL   3

/* query verbs */
#घोषणा VSV_SEND_VERSION_NUMBER 1
#घोषणा VSV_SEND_MODEM_CTL_STATUS 2

/* yes, these masks are not consecutive. */
#घोषणा HVSI_TSDTR 0x01
#घोषणा HVSI_TSCD  0x20

#घोषणा HVSI_MAX_OUTGOING_DATA 12
#घोषणा HVSI_VERSION 1

काष्ठा hvsi_header अणु
	uपूर्णांक8_t  type;
	uपूर्णांक8_t  len;
	__be16 seqno;
पूर्ण __attribute__((packed));

काष्ठा hvsi_data अणु
	काष्ठा hvsi_header hdr;
	uपूर्णांक8_t  data[HVSI_MAX_OUTGOING_DATA];
पूर्ण __attribute__((packed));

काष्ठा hvsi_control अणु
	काष्ठा hvsi_header hdr;
	__be16 verb;
	/* optional depending on verb: */
	__be32 word;
	__be32 mask;
पूर्ण __attribute__((packed));

काष्ठा hvsi_query अणु
	काष्ठा hvsi_header hdr;
	__be16 verb;
पूर्ण __attribute__((packed));

काष्ठा hvsi_query_response अणु
	काष्ठा hvsi_header hdr;
	__be16 verb;
	__be16 query_seqno;
	जोड़ अणु
		uपूर्णांक8_t  version;
		__be32 mctrl_word;
	पूर्ण u;
पूर्ण __attribute__((packed));

/* hvsi lib काष्ठा definitions */
#घोषणा HVSI_INBUF_SIZE		255
काष्ठा tty_काष्ठा;
काष्ठा hvsi_priv अणु
	अचिन्हित पूर्णांक	inbuf_len;	/* data in input buffer */
	अचिन्हित अक्षर	inbuf[HVSI_INBUF_SIZE];
	अचिन्हित पूर्णांक	inbuf_cur;	/* Cursor in input buffer */
	अचिन्हित पूर्णांक	inbuf_pktlen;	/* packet length from cursor */
	atomic_t	seqno;		/* packet sequence number */
	अचिन्हित पूर्णांक	खोलोed:1;	/* driver खोलोed */
	अचिन्हित पूर्णांक	established:1;	/* protocol established */
	अचिन्हित पूर्णांक 	is_console:1;	/* used as a kernel console device */
	अचिन्हित पूर्णांक	mctrl_update:1;	/* modem control updated */
	अचिन्हित लघु	mctrl;		/* modem control */
	काष्ठा tty_काष्ठा *tty;		/* tty काष्ठाure */
	पूर्णांक (*get_अक्षरs)(uपूर्णांक32_t termno, अक्षर *buf, पूर्णांक count);
	पूर्णांक (*put_अक्षरs)(uपूर्णांक32_t termno, स्थिर अक्षर *buf, पूर्णांक count);
	uपूर्णांक32_t	termno;
पूर्ण;

/* hvsi lib functions */
काष्ठा hvc_काष्ठा;
बाह्य व्योम hvsilib_init(काष्ठा hvsi_priv *pv,
			 पूर्णांक (*get_अक्षरs)(uपूर्णांक32_t termno, अक्षर *buf, पूर्णांक count),
			 पूर्णांक (*put_अक्षरs)(uपूर्णांक32_t termno, स्थिर अक्षर *buf,
					  पूर्णांक count),
			 पूर्णांक termno, पूर्णांक is_console);
बाह्य पूर्णांक hvsilib_खोलो(काष्ठा hvsi_priv *pv, काष्ठा hvc_काष्ठा *hp);
बाह्य व्योम hvsilib_बंद(काष्ठा hvsi_priv *pv, काष्ठा hvc_काष्ठा *hp);
बाह्य पूर्णांक hvsilib_पढ़ो_mctrl(काष्ठा hvsi_priv *pv);
बाह्य पूर्णांक hvsilib_ग_लिखो_mctrl(काष्ठा hvsi_priv *pv, पूर्णांक dtr);
बाह्य व्योम hvsilib_establish(काष्ठा hvsi_priv *pv);
बाह्य पूर्णांक hvsilib_get_अक्षरs(काष्ठा hvsi_priv *pv, अक्षर *buf, पूर्णांक count);
बाह्य पूर्णांक hvsilib_put_अक्षरs(काष्ठा hvsi_priv *pv, स्थिर अक्षर *buf, पूर्णांक count);

#पूर्ण_अगर /* _HVSI_H */
