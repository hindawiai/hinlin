<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/console.h>
#समावेश <यंत्र/hvsi.h>

#समावेश "hvc_console.h"

अटल पूर्णांक hvsi_send_packet(काष्ठा hvsi_priv *pv, काष्ठा hvsi_header *packet)
अणु
	packet->seqno = cpu_to_be16(atomic_inc_वापस(&pv->seqno));

	/* Assumes that always succeeds, works in practice */
	वापस pv->put_अक्षरs(pv->termno, (अक्षर *)packet, packet->len);
पूर्ण

अटल व्योम hvsi_start_handshake(काष्ठा hvsi_priv *pv)
अणु
	काष्ठा hvsi_query q;

	/* Reset state */
	pv->established = 0;
	atomic_set(&pv->seqno, 0);

	pr_devel("HVSI@%x: Handshaking started\n", pv->termno);

	/* Send version query */
	q.hdr.type = VS_QUERY_PACKET_HEADER;
	q.hdr.len = माप(काष्ठा hvsi_query);
	q.verb = cpu_to_be16(VSV_SEND_VERSION_NUMBER);
	hvsi_send_packet(pv, &q.hdr);
पूर्ण

अटल पूर्णांक hvsi_send_बंद(काष्ठा hvsi_priv *pv)
अणु
	काष्ठा hvsi_control ctrl;

	pv->established = 0;

	ctrl.hdr.type = VS_CONTROL_PACKET_HEADER;
	ctrl.hdr.len = माप(काष्ठा hvsi_control);
	ctrl.verb = cpu_to_be16(VSV_CLOSE_PROTOCOL);
	वापस hvsi_send_packet(pv, &ctrl.hdr);
पूर्ण

अटल व्योम hvsi_cd_change(काष्ठा hvsi_priv *pv, पूर्णांक cd)
अणु
	अगर (cd)
		pv->mctrl |= TIOCM_CD;
	अन्यथा अणु
		pv->mctrl &= ~TIOCM_CD;

		/* We copy the existing hvsi driver semantics
		 * here which are to trigger a hangup when
		 * we get a carrier loss.
		 * Closing our connection to the server will
		 * करो just that.
		 */
		अगर (!pv->is_console && pv->खोलोed) अणु
			pr_devel("HVSI@%x Carrier lost, hanging up !\n",
				 pv->termno);
			hvsi_send_बंद(pv);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hvsi_got_control(काष्ठा hvsi_priv *pv)
अणु
	काष्ठा hvsi_control *pkt = (काष्ठा hvsi_control *)pv->inbuf;

	चयन (be16_to_cpu(pkt->verb)) अणु
	हाल VSV_CLOSE_PROTOCOL:
		/* We restart the handshaking */
		hvsi_start_handshake(pv);
		अवरोध;
	हाल VSV_MODEM_CTL_UPDATE:
		/* Transition of carrier detect */
		hvsi_cd_change(pv, be32_to_cpu(pkt->word) & HVSI_TSCD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hvsi_got_query(काष्ठा hvsi_priv *pv)
अणु
	काष्ठा hvsi_query *pkt = (काष्ठा hvsi_query *)pv->inbuf;
	काष्ठा hvsi_query_response r;

	/* We only handle version queries */
	अगर (be16_to_cpu(pkt->verb) != VSV_SEND_VERSION_NUMBER)
		वापस;

	pr_devel("HVSI@%x: Got version query, sending response...\n",
		 pv->termno);

	/* Send version response */
	r.hdr.type = VS_QUERY_RESPONSE_PACKET_HEADER;
	r.hdr.len = माप(काष्ठा hvsi_query_response);
	r.verb = cpu_to_be16(VSV_SEND_VERSION_NUMBER);
	r.u.version = HVSI_VERSION;
	r.query_seqno = pkt->hdr.seqno;
	hvsi_send_packet(pv, &r.hdr);

	/* Assume protocol is खोलो now */
	pv->established = 1;
पूर्ण

अटल व्योम hvsi_got_response(काष्ठा hvsi_priv *pv)
अणु
	काष्ठा hvsi_query_response *r =
		(काष्ठा hvsi_query_response *)pv->inbuf;

	चयन(r->verb) अणु
	हाल VSV_SEND_MODEM_CTL_STATUS:
		hvsi_cd_change(pv, be32_to_cpu(r->u.mctrl_word) & HVSI_TSCD);
		pv->mctrl_update = 1;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक hvsi_check_packet(काष्ठा hvsi_priv *pv)
अणु
	u8 len, type;

	/* Check header validity. If it's invalid, we ditch
	 * the whole buffer and hope we eventually resync
	 */
	अगर (pv->inbuf[0] < 0xfc) अणु
		pv->inbuf_len = pv->inbuf_pktlen = 0;
		वापस 0;
	पूर्ण
	type = pv->inbuf[0];
	len = pv->inbuf[1];

	/* Packet incomplete ? */
	अगर (pv->inbuf_len < len)
		वापस 0;

	pr_devel("HVSI@%x: Got packet type %x len %d bytes:\n",
		 pv->termno, type, len);

	/* We have a packet, yay ! Handle it */
	चयन(type) अणु
	हाल VS_DATA_PACKET_HEADER:
		pv->inbuf_pktlen = len - 4;
		pv->inbuf_cur = 4;
		वापस 1;
	हाल VS_CONTROL_PACKET_HEADER:
		hvsi_got_control(pv);
		अवरोध;
	हाल VS_QUERY_PACKET_HEADER:
		hvsi_got_query(pv);
		अवरोध;
	हाल VS_QUERY_RESPONSE_PACKET_HEADER:
		hvsi_got_response(pv);
		अवरोध;
	पूर्ण

	/* Swallow packet and retry */
	pv->inbuf_len -= len;
	स_हटाओ(pv->inbuf, &pv->inbuf[len], pv->inbuf_len);
	वापस 1;
पूर्ण

अटल पूर्णांक hvsi_get_packet(काष्ठा hvsi_priv *pv)
अणु
	/* If we have room in the buffer, ask HV क्रम more */
	अगर (pv->inbuf_len < HVSI_INBUF_SIZE)
		pv->inbuf_len += pv->get_अक्षरs(pv->termno,
					     &pv->inbuf[pv->inbuf_len],
					     HVSI_INBUF_SIZE - pv->inbuf_len);
	/*
	 * If we have at least 4 bytes in the buffer, check क्रम
	 * a full packet and retry
	 */
	अगर (pv->inbuf_len >= 4)
		वापस hvsi_check_packet(pv);
	वापस 0;
पूर्ण

पूर्णांक hvsilib_get_अक्षरs(काष्ठा hvsi_priv *pv, अक्षर *buf, पूर्णांक count)
अणु
	अचिन्हित पूर्णांक tries, पढ़ो = 0;

	अगर (WARN_ON(!pv))
		वापस -ENXIO;

	/* If we aren't open, don't करो anything in order to aव्योम races
	 * with connection establishment. The hvc core will call this
	 * beक्रमe we have वापसed from notअगरier_add(), and we need to
	 * aव्योम multiple users playing with the receive buffer
	 */
	अगर (!pv->खोलोed)
		वापस 0;

	/* We try twice, once with what data we have and once more
	 * after we try to fetch some more from the hypervisor
	 */
	क्रम (tries = 1; count && tries < 2; tries++) अणु
		/* Consume existing data packet */
		अगर (pv->inbuf_pktlen) अणु
			अचिन्हित पूर्णांक l = min(count, (पूर्णांक)pv->inbuf_pktlen);
			स_नकल(&buf[पढ़ो], &pv->inbuf[pv->inbuf_cur], l);
			pv->inbuf_cur += l;
			pv->inbuf_pktlen -= l;
			count -= l;
			पढ़ो += l;
		पूर्ण
		अगर (count == 0)
			अवरोध;

		/* Data packet fully consumed, move करोwn remaning data */
		अगर (pv->inbuf_cur) अणु
			pv->inbuf_len -= pv->inbuf_cur;
			स_हटाओ(pv->inbuf, &pv->inbuf[pv->inbuf_cur],
				pv->inbuf_len);
			pv->inbuf_cur = 0;
		पूर्ण

		/* Try to get another packet */
		अगर (hvsi_get_packet(pv))
			tries--;
	पूर्ण
	अगर (!pv->established) अणु
		pr_devel("HVSI@%x: returning -EPIPE\n", pv->termno);
		वापस -EPIPE;
	पूर्ण
	वापस पढ़ो;
पूर्ण

पूर्णांक hvsilib_put_अक्षरs(काष्ठा hvsi_priv *pv, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvsi_data dp;
	पूर्णांक rc, adjcount = min(count, HVSI_MAX_OUTGOING_DATA);

	अगर (WARN_ON(!pv))
		वापस -ENODEV;

	dp.hdr.type = VS_DATA_PACKET_HEADER;
	dp.hdr.len = adjcount + माप(काष्ठा hvsi_header);
	स_नकल(dp.data, buf, adjcount);
	rc = hvsi_send_packet(pv, &dp.hdr);
	अगर (rc <= 0)
		वापस rc;
	वापस adjcount;
पूर्ण

अटल व्योम maybe_msleep(अचिन्हित दीर्घ ms)
अणु
	/* During early boot, IRQs are disabled, use mdelay */
	अगर (irqs_disabled())
		mdelay(ms);
	अन्यथा
		msleep(ms);
पूर्ण

पूर्णांक hvsilib_पढ़ो_mctrl(काष्ठा hvsi_priv *pv)
अणु
	काष्ठा hvsi_query q;
	पूर्णांक rc, समयout;

	pr_devel("HVSI@%x: Querying modem control status...\n",
		 pv->termno);

	pv->mctrl_update = 0;
	q.hdr.type = VS_QUERY_PACKET_HEADER;
	q.hdr.len = माप(काष्ठा hvsi_query);
	q.verb = cpu_to_be16(VSV_SEND_MODEM_CTL_STATUS);
	rc = hvsi_send_packet(pv, &q.hdr);
	अगर (rc <= 0) अणु
		pr_devel("HVSI@%x: Error %d...\n", pv->termno, rc);
		वापस rc;
	पूर्ण

	/* Try क्रम up to 200ms */
	क्रम (समयout = 0; समयout < 20; समयout++) अणु
		अगर (!pv->established)
			वापस -ENXIO;
		अगर (pv->mctrl_update)
			वापस 0;
		अगर (!hvsi_get_packet(pv))
			maybe_msleep(10);
	पूर्ण
	वापस -EIO;
पूर्ण

पूर्णांक hvsilib_ग_लिखो_mctrl(काष्ठा hvsi_priv *pv, पूर्णांक dtr)
अणु
	काष्ठा hvsi_control ctrl;
	अचिन्हित लघु mctrl;

	mctrl = pv->mctrl;
	अगर (dtr)
		mctrl |= TIOCM_DTR;
	अन्यथा
		mctrl &= ~TIOCM_DTR;
	अगर (mctrl == pv->mctrl)
		वापस 0;
	pv->mctrl = mctrl;

	pr_devel("HVSI@%x: %s DTR...\n", pv->termno,
		 dtr ? "Setting" : "Clearing");

	ctrl.hdr.type = VS_CONTROL_PACKET_HEADER,
	ctrl.hdr.len = माप(काष्ठा hvsi_control);
	ctrl.verb = cpu_to_be16(VSV_SET_MODEM_CTL);
	ctrl.mask = cpu_to_be32(HVSI_TSDTR);
	ctrl.word = cpu_to_be32(dtr ? HVSI_TSDTR : 0);
	वापस hvsi_send_packet(pv, &ctrl.hdr);
पूर्ण

व्योम hvsilib_establish(काष्ठा hvsi_priv *pv)
अणु
	पूर्णांक समयout;

	pr_devel("HVSI@%x: Establishing...\n", pv->termno);

	/* Try क्रम up to 200ms, there can be a packet to
	 * start the process रुकोing क्रम us...
	 */
	क्रम (समयout = 0; समयout < 20; समयout++) अणु
		अगर (pv->established)
			जाओ established;
		अगर (!hvsi_get_packet(pv))
			maybe_msleep(10);
	पूर्ण

	/* Failed, send a बंद connection packet just
	 * in हाल
	 */
	pr_devel("HVSI@%x:   ... sending close\n", pv->termno);

	hvsi_send_बंद(pv);

	/* Then restart handshake */

	pr_devel("HVSI@%x:   ... restarting handshake\n", pv->termno);

	hvsi_start_handshake(pv);

	pr_devel("HVSI@%x:   ... waiting handshake\n", pv->termno);

	/* Try क्रम up to 400ms */
	क्रम (समयout = 0; समयout < 40; समयout++) अणु
		अगर (pv->established)
			जाओ established;
		अगर (!hvsi_get_packet(pv))
			maybe_msleep(10);
	पूर्ण

	अगर (!pv->established) अणु
		pr_devel("HVSI@%x: Timeout handshaking, giving up !\n",
			 pv->termno);
		वापस;
	पूर्ण
 established:
	/* Query modem control lines */

	pr_devel("HVSI@%x:   ... established, reading mctrl\n", pv->termno);

	hvsilib_पढ़ो_mctrl(pv);

	/* Set our own DTR */

	pr_devel("HVSI@%x:   ... setting mctrl\n", pv->termno);

	hvsilib_ग_लिखो_mctrl(pv, 1);

	/* Set the खोलोed flag so पढ़ोs are allowed */
	wmb();
	pv->खोलोed = 1;
पूर्ण

पूर्णांक hvsilib_खोलो(काष्ठा hvsi_priv *pv, काष्ठा hvc_काष्ठा *hp)
अणु
	pr_devel("HVSI@%x: open !\n", pv->termno);

	/* Keep track of the tty data काष्ठाure */
	pv->tty = tty_port_tty_get(&hp->port);

	hvsilib_establish(pv);

	वापस 0;
पूर्ण

व्योम hvsilib_बंद(काष्ठा hvsi_priv *pv, काष्ठा hvc_काष्ठा *hp)
अणु
	अचिन्हित दीर्घ flags;

	pr_devel("HVSI@%x: close !\n", pv->termno);

	अगर (!pv->is_console) अणु
		pr_devel("HVSI@%x: Not a console, tearing down\n",
			 pv->termno);

		/* Clear खोलोed, synchronize with khvcd */
		spin_lock_irqsave(&hp->lock, flags);
		pv->खोलोed = 0;
		spin_unlock_irqrestore(&hp->lock, flags);

		/* Clear our own DTR */
		अगर (!pv->tty || (pv->tty->termios.c_cflag & HUPCL))
			hvsilib_ग_लिखो_mctrl(pv, 0);

		/* Tear करोwn the connection */
		hvsi_send_बंद(pv);
	पूर्ण

	tty_kref_put(pv->tty);
	pv->tty = शून्य;
पूर्ण

व्योम hvsilib_init(काष्ठा hvsi_priv *pv,
		  पूर्णांक (*get_अक्षरs)(uपूर्णांक32_t termno, अक्षर *buf, पूर्णांक count),
		  पूर्णांक (*put_अक्षरs)(uपूर्णांक32_t termno, स्थिर अक्षर *buf,
				   पूर्णांक count),
		  पूर्णांक termno, पूर्णांक is_console)
अणु
	स_रखो(pv, 0, माप(*pv));
	pv->get_अक्षरs = get_अक्षरs;
	pv->put_अक्षरs = put_अक्षरs;
	pv->termno = termno;
	pv->is_console = is_console;
पूर्ण
