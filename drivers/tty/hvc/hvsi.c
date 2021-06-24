<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2004 Hollis Blanअक्षरd <hollisb@us.ibm.com>, IBM
 */

/* Host Virtual Serial Interface (HVSI) is a protocol between the hosted OS
 * and the service processor on IBM pSeries servers. On these servers, there
 * are no serial ports under the OS's control, and someबार there is no other
 * console available either. However, the service processor has two standard
 * serial ports, so this over-complicated protocol allows the OS to control
 * those ports by proxy.
 *
 * Besides data, the procotol supports the पढ़ोing/writing of the serial
 * port's DTR line, and the पढ़ोing of the CD line. This is to allow the OS to
 * control a modem attached to the service processor's serial port. Note that
 * the OS cannot change the speed of the port through this protocol.
 */

#अघोषित DEBUG

#समावेश <linux/console.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/major.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/hvconsole.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/hvsi.h>

#घोषणा HVSI_MAJOR	229
#घोषणा HVSI_MINOR	128
#घोषणा MAX_NR_HVSI_CONSOLES 4

#घोषणा HVSI_TIMEOUT (5*HZ)
#घोषणा HVSI_VERSION 1
#घोषणा HVSI_MAX_PACKET 256
#घोषणा HVSI_MAX_READ 16
#घोषणा HVSI_MAX_OUTGOING_DATA 12
#घोषणा N_OUTBUF 12

/*
 * we pass data via two 8-byte रेजिस्टरs, so we would like our अक्षर arrays
 * properly aligned क्रम those loads.
 */
#घोषणा __ALIGNED__	__attribute__((__aligned__(माप(दीर्घ))))

काष्ठा hvsi_काष्ठा अणु
	काष्ठा tty_port port;
	काष्ठा delayed_work ग_लिखोr;
	काष्ठा work_काष्ठा handshaker;
	रुको_queue_head_t emptyq; /* woken when outbuf is emptied */
	रुको_queue_head_t stateq; /* woken when HVSI state changes */
	spinlock_t lock;
	पूर्णांक index;
	uपूर्णांक8_t throttle_buf[128];
	uपूर्णांक8_t outbuf[N_OUTBUF]; /* to implement ग_लिखो_room and अक्षरs_in_buffer */
	/* inbuf is क्रम packet reassembly. leave a little room क्रम leftovers. */
	uपूर्णांक8_t inbuf[HVSI_MAX_PACKET + HVSI_MAX_READ];
	uपूर्णांक8_t *inbuf_end;
	पूर्णांक n_throttle;
	पूर्णांक n_outbuf;
	uपूर्णांक32_t vtermno;
	uपूर्णांक32_t virq;
	atomic_t seqno; /* HVSI packet sequence number */
	uपूर्णांक16_t mctrl;
	uपूर्णांक8_t state;  /* HVSI protocol state */
	uपूर्णांक8_t flags;
#अगर_घोषित CONFIG_MAGIC_SYSRQ
	uपूर्णांक8_t sysrq;
#पूर्ण_अगर /* CONFIG_MAGIC_SYSRQ */
पूर्ण;
अटल काष्ठा hvsi_काष्ठा hvsi_ports[MAX_NR_HVSI_CONSOLES];

अटल काष्ठा tty_driver *hvsi_driver;
अटल पूर्णांक hvsi_count;
अटल पूर्णांक (*hvsi_रुको)(काष्ठा hvsi_काष्ठा *hp, पूर्णांक state);

क्रमागत HVSI_PROTOCOL_STATE अणु
	HVSI_CLOSED,
	HVSI_WAIT_FOR_VER_RESPONSE,
	HVSI_WAIT_FOR_VER_QUERY,
	HVSI_OPEN,
	HVSI_WAIT_FOR_MCTRL_RESPONSE,
	HVSI_FSP_DIED,
पूर्ण;
#घोषणा HVSI_CONSOLE 0x1

अटल अंतरभूत पूर्णांक is_console(काष्ठा hvsi_काष्ठा *hp)
अणु
	वापस hp->flags & HVSI_CONSOLE;
पूर्ण

अटल अंतरभूत पूर्णांक is_खोलो(काष्ठा hvsi_काष्ठा *hp)
अणु
	/* अगर we're waiting for an mctrl then we're alपढ़ोy खोलो */
	वापस (hp->state == HVSI_OPEN)
			|| (hp->state == HVSI_WAIT_FOR_MCTRL_RESPONSE);
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_state(काष्ठा hvsi_काष्ठा *hp)
अणु
#अगर_घोषित DEBUG
	अटल स्थिर अक्षर *state_names[] = अणु
		"HVSI_CLOSED",
		"HVSI_WAIT_FOR_VER_RESPONSE",
		"HVSI_WAIT_FOR_VER_QUERY",
		"HVSI_OPEN",
		"HVSI_WAIT_FOR_MCTRL_RESPONSE",
		"HVSI_FSP_DIED",
	पूर्ण;
	स्थिर अक्षर *name = (hp->state < ARRAY_SIZE(state_names))
		? state_names[hp->state] : "UNKNOWN";

	pr_debug("hvsi%i: state = %s\n", hp->index, name);
#पूर्ण_अगर /* DEBUG */
पूर्ण

अटल अंतरभूत व्योम __set_state(काष्ठा hvsi_काष्ठा *hp, पूर्णांक state)
अणु
	hp->state = state;
	prपूर्णांक_state(hp);
	wake_up_all(&hp->stateq);
पूर्ण

अटल अंतरभूत व्योम set_state(काष्ठा hvsi_काष्ठा *hp, पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hp->lock, flags);
	__set_state(hp, state);
	spin_unlock_irqrestore(&hp->lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक len_packet(स्थिर uपूर्णांक8_t *packet)
अणु
	वापस (पूर्णांक)((काष्ठा hvsi_header *)packet)->len;
पूर्ण

अटल अंतरभूत पूर्णांक is_header(स्थिर uपूर्णांक8_t *packet)
अणु
	काष्ठा hvsi_header *header = (काष्ठा hvsi_header *)packet;
	वापस header->type >= VS_QUERY_RESPONSE_PACKET_HEADER;
पूर्ण

अटल अंतरभूत पूर्णांक got_packet(स्थिर काष्ठा hvsi_काष्ठा *hp, uपूर्णांक8_t *packet)
अणु
	अगर (hp->inbuf_end < packet + माप(काष्ठा hvsi_header))
		वापस 0; /* करोn't even have the packet header */

	अगर (hp->inbuf_end < (packet + len_packet(packet)))
		वापस 0; /* करोn't have the rest of the packet */

	वापस 1;
पूर्ण

/* shअगरt reमुख्यing bytes in packetbuf करोwn */
अटल व्योम compact_inbuf(काष्ठा hvsi_काष्ठा *hp, uपूर्णांक8_t *पढ़ो_to)
अणु
	पूर्णांक reमुख्यing = (पूर्णांक)(hp->inbuf_end - पढ़ो_to);

	pr_debug("%s: %i chars remain\n", __func__, reमुख्यing);

	अगर (पढ़ो_to != hp->inbuf)
		स_हटाओ(hp->inbuf, पढ़ो_to, reमुख्यing);

	hp->inbuf_end = hp->inbuf + reमुख्यing;
पूर्ण

#अगर_घोषित DEBUG
#घोषणा dbg_dump_packet(packet) dump_packet(packet)
#घोषणा dbg_dump_hex(data, len) dump_hex(data, len)
#अन्यथा
#घोषणा dbg_dump_packet(packet) करो अणु पूर्ण जबतक (0)
#घोषणा dbg_dump_hex(data, len) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम dump_hex(स्थिर uपूर्णांक8_t *data, पूर्णांक len)
अणु
	पूर्णांक i;

	prपूर्णांकk("    ");
	क्रम (i=0; i < len; i++)
		prपूर्णांकk("%.2x", data[i]);

	prपूर्णांकk("\n    ");
	क्रम (i=0; i < len; i++) अणु
		अगर (है_छाप(data[i]))
			prपूर्णांकk("%c", data[i]);
		अन्यथा
			prपूर्णांकk(".");
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम dump_packet(uपूर्णांक8_t *packet)
अणु
	काष्ठा hvsi_header *header = (काष्ठा hvsi_header *)packet;

	prपूर्णांकk("type 0x%x, len %i, seqno %i:\n", header->type, header->len,
			header->seqno);

	dump_hex(packet, header->len);
पूर्ण

अटल पूर्णांक hvsi_पढ़ो(काष्ठा hvsi_काष्ठा *hp, अक्षर *buf, पूर्णांक count)
अणु
	अचिन्हित दीर्घ got;

	got = hvc_get_अक्षरs(hp->vtermno, buf, count);

	वापस got;
पूर्ण

अटल व्योम hvsi_recv_control(काष्ठा hvsi_काष्ठा *hp, uपूर्णांक8_t *packet,
	काष्ठा tty_काष्ठा *tty, काष्ठा hvsi_काष्ठा **to_handshake)
अणु
	काष्ठा hvsi_control *header = (काष्ठा hvsi_control *)packet;

	चयन (be16_to_cpu(header->verb)) अणु
		हाल VSV_MODEM_CTL_UPDATE:
			अगर ((be32_to_cpu(header->word) & HVSI_TSCD) == 0) अणु
				/* CD went away; no more connection */
				pr_debug("hvsi%i: CD dropped\n", hp->index);
				hp->mctrl &= TIOCM_CD;
				अगर (tty && !C_CLOCAL(tty))
					tty_hangup(tty);
			पूर्ण
			अवरोध;
		हाल VSV_CLOSE_PROTOCOL:
			pr_debug("hvsi%i: service processor came back\n", hp->index);
			अगर (hp->state != HVSI_CLOSED) अणु
				*to_handshake = hp;
			पूर्ण
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING "hvsi%i: unknown HVSI control packet: ",
				hp->index);
			dump_packet(packet);
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hvsi_recv_response(काष्ठा hvsi_काष्ठा *hp, uपूर्णांक8_t *packet)
अणु
	काष्ठा hvsi_query_response *resp = (काष्ठा hvsi_query_response *)packet;
	uपूर्णांक32_t mctrl_word;

	चयन (hp->state) अणु
		हाल HVSI_WAIT_FOR_VER_RESPONSE:
			__set_state(hp, HVSI_WAIT_FOR_VER_QUERY);
			अवरोध;
		हाल HVSI_WAIT_FOR_MCTRL_RESPONSE:
			hp->mctrl = 0;
			mctrl_word = be32_to_cpu(resp->u.mctrl_word);
			अगर (mctrl_word & HVSI_TSDTR)
				hp->mctrl |= TIOCM_DTR;
			अगर (mctrl_word & HVSI_TSCD)
				hp->mctrl |= TIOCM_CD;
			__set_state(hp, HVSI_OPEN);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "hvsi%i: unexpected query response: ", hp->index);
			dump_packet(packet);
			अवरोध;
	पूर्ण
पूर्ण

/* respond to service processor's version query */
अटल पूर्णांक hvsi_version_respond(काष्ठा hvsi_काष्ठा *hp, uपूर्णांक16_t query_seqno)
अणु
	काष्ठा hvsi_query_response packet __ALIGNED__;
	पूर्णांक wrote;

	packet.hdr.type = VS_QUERY_RESPONSE_PACKET_HEADER;
	packet.hdr.len = माप(काष्ठा hvsi_query_response);
	packet.hdr.seqno = cpu_to_be16(atomic_inc_वापस(&hp->seqno));
	packet.verb = cpu_to_be16(VSV_SEND_VERSION_NUMBER);
	packet.u.version = HVSI_VERSION;
	packet.query_seqno = cpu_to_be16(query_seqno+1);

	pr_debug("%s: sending %i bytes\n", __func__, packet.hdr.len);
	dbg_dump_hex((uपूर्णांक8_t*)&packet, packet.hdr.len);

	wrote = hvc_put_अक्षरs(hp->vtermno, (अक्षर *)&packet, packet.hdr.len);
	अगर (wrote != packet.hdr.len) अणु
		prपूर्णांकk(KERN_ERR "hvsi%i: couldn't send query response!\n",
			hp->index);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hvsi_recv_query(काष्ठा hvsi_काष्ठा *hp, uपूर्णांक8_t *packet)
अणु
	काष्ठा hvsi_query *query = (काष्ठा hvsi_query *)packet;

	चयन (hp->state) अणु
		हाल HVSI_WAIT_FOR_VER_QUERY:
			hvsi_version_respond(hp, be16_to_cpu(query->hdr.seqno));
			__set_state(hp, HVSI_OPEN);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "hvsi%i: unexpected query: ", hp->index);
			dump_packet(packet);
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hvsi_insert_अक्षरs(काष्ठा hvsi_काष्ठा *hp, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i=0; i < len; i++) अणु
		अक्षर c = buf[i];
#अगर_घोषित CONFIG_MAGIC_SYSRQ
		अगर (c == '\0') अणु
			hp->sysrq = 1;
			जारी;
		पूर्ण अन्यथा अगर (hp->sysrq) अणु
			handle_sysrq(c);
			hp->sysrq = 0;
			जारी;
		पूर्ण
#पूर्ण_अगर /* CONFIG_MAGIC_SYSRQ */
		tty_insert_flip_अक्षर(&hp->port, c, 0);
	पूर्ण
पूर्ण

/*
 * We could get 252 bytes of data at once here. But the tty layer only
 * throttles us at TTY_THRESHOLD_THROTTLE (128) bytes, so we could overflow
 * it. Accordingly we won't send more than 128 bytes at a समय to the flip
 * buffer, which will give the tty buffer a chance to throttle us. Should the
 * value of TTY_THRESHOLD_THROTTLE change in n_tty.c, this code should be
 * revisited.
 */
#घोषणा TTY_THRESHOLD_THROTTLE 128
अटल bool hvsi_recv_data(काष्ठा hvsi_काष्ठा *hp, स्थिर uपूर्णांक8_t *packet)
अणु
	स्थिर काष्ठा hvsi_header *header = (स्थिर काष्ठा hvsi_header *)packet;
	स्थिर uपूर्णांक8_t *data = packet + माप(काष्ठा hvsi_header);
	पूर्णांक datalen = header->len - माप(काष्ठा hvsi_header);
	पूर्णांक overflow = datalen - TTY_THRESHOLD_THROTTLE;

	pr_debug("queueing %i chars '%.*s'\n", datalen, datalen, data);

	अगर (datalen == 0)
		वापस false;

	अगर (overflow > 0) अणु
		pr_debug("%s: got >TTY_THRESHOLD_THROTTLE bytes\n", __func__);
		datalen = TTY_THRESHOLD_THROTTLE;
	पूर्ण

	hvsi_insert_अक्षरs(hp, data, datalen);

	अगर (overflow > 0) अणु
		/*
		 * we still have more data to deliver, so we need to save off the
		 * overflow and send it later
		 */
		pr_debug("%s: deferring overflow\n", __func__);
		स_नकल(hp->throttle_buf, data + TTY_THRESHOLD_THROTTLE, overflow);
		hp->n_throttle = overflow;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Returns true/false indicating data successfully पढ़ो from hypervisor.
 * Used both to get packets क्रम tty connections and to advance the state
 * machine during console handshaking (in which हाल tty = शून्य and we ignore
 * incoming data).
 */
अटल पूर्णांक hvsi_load_chunk(काष्ठा hvsi_काष्ठा *hp, काष्ठा tty_काष्ठा *tty,
		काष्ठा hvsi_काष्ठा **handshake)
अणु
	uपूर्णांक8_t *packet = hp->inbuf;
	पूर्णांक chunklen;
	bool flip = false;

	*handshake = शून्य;

	chunklen = hvsi_पढ़ो(hp, hp->inbuf_end, HVSI_MAX_READ);
	अगर (chunklen == 0) अणु
		pr_debug("%s: 0-length read\n", __func__);
		वापस 0;
	पूर्ण

	pr_debug("%s: got %i bytes\n", __func__, chunklen);
	dbg_dump_hex(hp->inbuf_end, chunklen);

	hp->inbuf_end += chunklen;

	/* handle all completed packets */
	जबतक ((packet < hp->inbuf_end) && got_packet(hp, packet)) अणु
		काष्ठा hvsi_header *header = (काष्ठा hvsi_header *)packet;

		अगर (!is_header(packet)) अणु
			prपूर्णांकk(KERN_ERR "hvsi%i: got malformed packet\n", hp->index);
			/* skip bytes until we find a header or run out of data */
			जबतक ((packet < hp->inbuf_end) && (!is_header(packet)))
				packet++;
			जारी;
		पूर्ण

		pr_debug("%s: handling %i-byte packet\n", __func__,
				len_packet(packet));
		dbg_dump_packet(packet);

		चयन (header->type) अणु
			हाल VS_DATA_PACKET_HEADER:
				अगर (!is_खोलो(hp))
					अवरोध;
				flip = hvsi_recv_data(hp, packet);
				अवरोध;
			हाल VS_CONTROL_PACKET_HEADER:
				hvsi_recv_control(hp, packet, tty, handshake);
				अवरोध;
			हाल VS_QUERY_RESPONSE_PACKET_HEADER:
				hvsi_recv_response(hp, packet);
				अवरोध;
			हाल VS_QUERY_PACKET_HEADER:
				hvsi_recv_query(hp, packet);
				अवरोध;
			शेष:
				prपूर्णांकk(KERN_ERR "hvsi%i: unknown HVSI packet type 0x%x\n",
						hp->index, header->type);
				dump_packet(packet);
				अवरोध;
		पूर्ण

		packet += len_packet(packet);

		अगर (*handshake) अणु
			pr_debug("%s: handshake\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण

	compact_inbuf(hp, packet);

	अगर (flip)
		tty_flip_buffer_push(&hp->port);

	वापस 1;
पूर्ण

अटल व्योम hvsi_send_overflow(काष्ठा hvsi_काष्ठा *hp)
अणु
	pr_debug("%s: delivering %i bytes overflow\n", __func__,
			hp->n_throttle);

	hvsi_insert_अक्षरs(hp, hp->throttle_buf, hp->n_throttle);
	hp->n_throttle = 0;
पूर्ण

/*
 * must get all pending data because we only get an irq on empty->non-empty
 * transition
 */
अटल irqवापस_t hvsi_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hvsi_काष्ठा *hp = (काष्ठा hvsi_काष्ठा *)arg;
	काष्ठा hvsi_काष्ठा *handshake;
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित दीर्घ flags;
	पूर्णांक again = 1;

	pr_debug("%s\n", __func__);

	tty = tty_port_tty_get(&hp->port);

	जबतक (again) अणु
		spin_lock_irqsave(&hp->lock, flags);
		again = hvsi_load_chunk(hp, tty, &handshake);
		spin_unlock_irqrestore(&hp->lock, flags);

		अगर (handshake) अणु
			pr_debug("hvsi%i: attempting re-handshake\n", handshake->index);
			schedule_work(&handshake->handshaker);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&hp->lock, flags);
	अगर (tty && hp->n_throttle && !tty_throttled(tty)) अणु
		/* we weren't hung up and we weren't throttled, so we can
		 * deliver the rest now */
		hvsi_send_overflow(hp);
		tty_flip_buffer_push(&hp->port);
	पूर्ण
	spin_unlock_irqrestore(&hp->lock, flags);

	tty_kref_put(tty);

	वापस IRQ_HANDLED;
पूर्ण

/* क्रम boot console, beक्रमe the irq handler is running */
अटल पूर्णांक __init poll_क्रम_state(काष्ठा hvsi_काष्ठा *hp, पूर्णांक state)
अणु
	अचिन्हित दीर्घ end_jअगरfies = jअगरfies + HVSI_TIMEOUT;

	क्रम (;;) अणु
		hvsi_पूर्णांकerrupt(hp->virq, (व्योम *)hp); /* get pending data */

		अगर (hp->state == state)
			वापस 0;

		mdelay(5);
		अगर (समय_after(jअगरfies, end_jअगरfies))
			वापस -EIO;
	पूर्ण
पूर्ण

/* रुको क्रम irq handler to change our state */
अटल पूर्णांक रुको_क्रम_state(काष्ठा hvsi_काष्ठा *hp, पूर्णांक state)
अणु
	पूर्णांक ret = 0;

	अगर (!रुको_event_समयout(hp->stateq, (hp->state == state), HVSI_TIMEOUT))
		ret = -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक hvsi_query(काष्ठा hvsi_काष्ठा *hp, uपूर्णांक16_t verb)
अणु
	काष्ठा hvsi_query packet __ALIGNED__;
	पूर्णांक wrote;

	packet.hdr.type = VS_QUERY_PACKET_HEADER;
	packet.hdr.len = माप(काष्ठा hvsi_query);
	packet.hdr.seqno = cpu_to_be16(atomic_inc_वापस(&hp->seqno));
	packet.verb = cpu_to_be16(verb);

	pr_debug("%s: sending %i bytes\n", __func__, packet.hdr.len);
	dbg_dump_hex((uपूर्णांक8_t*)&packet, packet.hdr.len);

	wrote = hvc_put_अक्षरs(hp->vtermno, (अक्षर *)&packet, packet.hdr.len);
	अगर (wrote != packet.hdr.len) अणु
		prपूर्णांकk(KERN_ERR "hvsi%i: couldn't send query (%i)!\n", hp->index,
			wrote);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hvsi_get_mctrl(काष्ठा hvsi_काष्ठा *hp)
अणु
	पूर्णांक ret;

	set_state(hp, HVSI_WAIT_FOR_MCTRL_RESPONSE);
	hvsi_query(hp, VSV_SEND_MODEM_CTL_STATUS);

	ret = hvsi_रुको(hp, HVSI_OPEN);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "hvsi%i: didn't get modem flags\n", hp->index);
		set_state(hp, HVSI_OPEN);
		वापस ret;
	पूर्ण

	pr_debug("%s: mctrl 0x%x\n", __func__, hp->mctrl);

	वापस 0;
पूर्ण

/* note that we can only set DTR */
अटल पूर्णांक hvsi_set_mctrl(काष्ठा hvsi_काष्ठा *hp, uपूर्णांक16_t mctrl)
अणु
	काष्ठा hvsi_control packet __ALIGNED__;
	पूर्णांक wrote;

	packet.hdr.type = VS_CONTROL_PACKET_HEADER;
	packet.hdr.seqno = cpu_to_be16(atomic_inc_वापस(&hp->seqno));
	packet.hdr.len = माप(काष्ठा hvsi_control);
	packet.verb = cpu_to_be16(VSV_SET_MODEM_CTL);
	packet.mask = cpu_to_be32(HVSI_TSDTR);

	अगर (mctrl & TIOCM_DTR)
		packet.word = cpu_to_be32(HVSI_TSDTR);

	pr_debug("%s: sending %i bytes\n", __func__, packet.hdr.len);
	dbg_dump_hex((uपूर्णांक8_t*)&packet, packet.hdr.len);

	wrote = hvc_put_अक्षरs(hp->vtermno, (अक्षर *)&packet, packet.hdr.len);
	अगर (wrote != packet.hdr.len) अणु
		prपूर्णांकk(KERN_ERR "hvsi%i: couldn't set DTR!\n", hp->index);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hvsi_drain_input(काष्ठा hvsi_काष्ठा *hp)
अणु
	uपूर्णांक8_t buf[HVSI_MAX_READ] __ALIGNED__;
	अचिन्हित दीर्घ end_jअगरfies = jअगरfies + HVSI_TIMEOUT;

	जबतक (समय_beक्रमe(end_jअगरfies, jअगरfies))
		अगर (0 == hvsi_पढ़ो(hp, buf, HVSI_MAX_READ))
			अवरोध;
पूर्ण

अटल पूर्णांक hvsi_handshake(काष्ठा hvsi_काष्ठा *hp)
अणु
	पूर्णांक ret;

	/*
	 * We could have a CLOSE or other data रुकोing क्रम us beक्रमe we even try
	 * to खोलो; try to throw it all away so we करोn't get confused. (CLOSE
	 * is the first message sent up the pipe when the FSP comes online. We
	 * need to distinguish between "it came up a जबतक ago and we're the first
	 * user" and "it was just reset beक्रमe it saw our handshake packet".)
	 */
	hvsi_drain_input(hp);

	set_state(hp, HVSI_WAIT_FOR_VER_RESPONSE);
	ret = hvsi_query(hp, VSV_SEND_VERSION_NUMBER);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "hvsi%i: couldn't send version query\n", hp->index);
		वापस ret;
	पूर्ण

	ret = hvsi_रुको(hp, HVSI_OPEN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम hvsi_handshaker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hvsi_काष्ठा *hp =
		container_of(work, काष्ठा hvsi_काष्ठा, handshaker);

	अगर (hvsi_handshake(hp) >= 0)
		वापस;

	prपूर्णांकk(KERN_ERR "hvsi%i: re-handshaking failed\n", hp->index);
	अगर (is_console(hp)) अणु
		/*
		 * ttys will re-attempt the handshake via hvsi_खोलो, but
		 * the console will not.
		 */
		prपूर्णांकk(KERN_ERR "hvsi%i: lost console!\n", hp->index);
	पूर्ण
पूर्ण

अटल पूर्णांक hvsi_put_अक्षरs(काष्ठा hvsi_काष्ठा *hp, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvsi_data packet __ALIGNED__;
	पूर्णांक ret;

	BUG_ON(count > HVSI_MAX_OUTGOING_DATA);

	packet.hdr.type = VS_DATA_PACKET_HEADER;
	packet.hdr.seqno = cpu_to_be16(atomic_inc_वापस(&hp->seqno));
	packet.hdr.len = count + माप(काष्ठा hvsi_header);
	स_नकल(&packet.data, buf, count);

	ret = hvc_put_अक्षरs(hp->vtermno, (अक्षर *)&packet, packet.hdr.len);
	अगर (ret == packet.hdr.len) अणु
		/* वापस the number of अक्षरs written, not the packet length */
		वापस count;
	पूर्ण
	वापस ret; /* वापस any errors */
पूर्ण

अटल व्योम hvsi_बंद_protocol(काष्ठा hvsi_काष्ठा *hp)
अणु
	काष्ठा hvsi_control packet __ALIGNED__;

	packet.hdr.type = VS_CONTROL_PACKET_HEADER;
	packet.hdr.seqno = cpu_to_be16(atomic_inc_वापस(&hp->seqno));
	packet.hdr.len = 6;
	packet.verb = cpu_to_be16(VSV_CLOSE_PROTOCOL);

	pr_debug("%s: sending %i bytes\n", __func__, packet.hdr.len);
	dbg_dump_hex((uपूर्णांक8_t*)&packet, packet.hdr.len);

	hvc_put_अक्षरs(hp->vtermno, (अक्षर *)&packet, packet.hdr.len);
पूर्ण

अटल पूर्णांक hvsi_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा hvsi_काष्ठा *hp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	pr_debug("%s\n", __func__);

	hp = &hvsi_ports[tty->index];

	tty->driver_data = hp;

	mb();
	अगर (hp->state == HVSI_FSP_DIED)
		वापस -EIO;

	tty_port_tty_set(&hp->port, tty);
	spin_lock_irqsave(&hp->lock, flags);
	hp->port.count++;
	atomic_set(&hp->seqno, 0);
	h_vio_संकेत(hp->vtermno, VIO_IRQ_ENABLE);
	spin_unlock_irqrestore(&hp->lock, flags);

	अगर (is_console(hp))
		वापस 0; /* this has alपढ़ोy been handshaked as the console */

	ret = hvsi_handshake(hp);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: HVSI handshaking failed\n", tty->name);
		वापस ret;
	पूर्ण

	ret = hvsi_get_mctrl(hp);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: couldn't get initial modem flags\n", tty->name);
		वापस ret;
	पूर्ण

	ret = hvsi_set_mctrl(hp, hp->mctrl | TIOCM_DTR);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: couldn't set DTR\n", tty->name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* रुको क्रम hvsi_ग_लिखो_worker to empty hp->outbuf */
अटल व्योम hvsi_flush_output(काष्ठा hvsi_काष्ठा *hp)
अणु
	रुको_event_समयout(hp->emptyq, (hp->n_outbuf <= 0), HVSI_TIMEOUT);

	/* 'writer' could still be pending if it didn't see n_outbuf = 0 yet */
	cancel_delayed_work_sync(&hp->ग_लिखोr);
	flush_work(&hp->handshaker);

	/*
	 * it's also possible that our समयout expired and hvsi_ग_लिखो_worker
	 * didn't manage to push outbuf. poof.
	 */
	hp->n_outbuf = 0;
पूर्ण

अटल व्योम hvsi_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;
	अचिन्हित दीर्घ flags;

	pr_debug("%s\n", __func__);

	अगर (tty_hung_up_p(filp))
		वापस;

	spin_lock_irqsave(&hp->lock, flags);

	अगर (--hp->port.count == 0) अणु
		tty_port_tty_set(&hp->port, शून्य);
		hp->inbuf_end = hp->inbuf; /* discard reमुख्यing partial packets */

		/* only बंद करोwn connection अगर it is not the console */
		अगर (!is_console(hp)) अणु
			h_vio_संकेत(hp->vtermno, VIO_IRQ_DISABLE); /* no more irqs */
			__set_state(hp, HVSI_CLOSED);
			/*
			 * any data delivered to the tty layer after this will be
			 * discarded (except क्रम XON/XOFF)
			 */
			tty->closing = 1;

			spin_unlock_irqrestore(&hp->lock, flags);

			/* let any existing irq handlers finish. no more will start. */
			synchronize_irq(hp->virq);

			/* hvsi_ग_लिखो_worker will re-schedule until outbuf is empty. */
			hvsi_flush_output(hp);

			/* tell FSP to stop sending data */
			hvsi_बंद_protocol(hp);

			/*
			 * drain anything FSP is still in the middle of sending, and let
			 * hvsi_handshake drain the rest on the next खोलो.
			 */
			hvsi_drain_input(hp);

			spin_lock_irqsave(&hp->lock, flags);
		पूर्ण
	पूर्ण अन्यथा अगर (hp->port.count < 0)
		prपूर्णांकk(KERN_ERR "hvsi_close %lu: oops, count is %d\n",
		       hp - hvsi_ports, hp->port.count);

	spin_unlock_irqrestore(&hp->lock, flags);
पूर्ण

अटल व्योम hvsi_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;
	अचिन्हित दीर्घ flags;

	pr_debug("%s\n", __func__);

	tty_port_tty_set(&hp->port, शून्य);

	spin_lock_irqsave(&hp->lock, flags);
	hp->port.count = 0;
	hp->n_outbuf = 0;
	spin_unlock_irqrestore(&hp->lock, flags);
पूर्ण

/* called with hp->lock held */
अटल व्योम hvsi_push(काष्ठा hvsi_काष्ठा *hp)
अणु
	पूर्णांक n;

	अगर (hp->n_outbuf <= 0)
		वापस;

	n = hvsi_put_अक्षरs(hp, hp->outbuf, hp->n_outbuf);
	अगर (n > 0) अणु
		/* success */
		pr_debug("%s: wrote %i chars\n", __func__, n);
		hp->n_outbuf = 0;
	पूर्ण अन्यथा अगर (n == -EIO) अणु
		__set_state(hp, HVSI_FSP_DIED);
		prपूर्णांकk(KERN_ERR "hvsi%i: service processor died\n", hp->index);
	पूर्ण
पूर्ण

/* hvsi_ग_लिखो_worker will keep rescheduling itself until outbuf is empty */
अटल व्योम hvsi_ग_लिखो_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hvsi_काष्ठा *hp =
		container_of(work, काष्ठा hvsi_काष्ठा, ग_लिखोr.work);
	अचिन्हित दीर्घ flags;
#अगर_घोषित DEBUG
	अटल दीर्घ start_j = 0;

	अगर (start_j == 0)
		start_j = jअगरfies;
#पूर्ण_अगर /* DEBUG */

	spin_lock_irqsave(&hp->lock, flags);

	pr_debug("%s: %i chars in buffer\n", __func__, hp->n_outbuf);

	अगर (!is_खोलो(hp)) अणु
		/*
		 * We could have a non-खोलो connection अगर the service processor died
		 * जबतक we were busily scheduling ourselves. In that हाल, it could
		 * be minutes beक्रमe the service processor comes back, so only try
		 * again once a second.
		 */
		schedule_delayed_work(&hp->ग_लिखोr, HZ);
		जाओ out;
	पूर्ण

	hvsi_push(hp);
	अगर (hp->n_outbuf > 0)
		schedule_delayed_work(&hp->ग_लिखोr, 10);
	अन्यथा अणु
#अगर_घोषित DEBUG
		pr_debug("%s: outbuf emptied after %li jiffies\n", __func__,
				jअगरfies - start_j);
		start_j = 0;
#पूर्ण_अगर /* DEBUG */
		wake_up_all(&hp->emptyq);
		tty_port_tty_wakeup(&hp->port);
	पूर्ण

out:
	spin_unlock_irqrestore(&hp->lock, flags);
पूर्ण

अटल पूर्णांक hvsi_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;

	वापस N_OUTBUF - hp->n_outbuf;
पूर्ण

अटल पूर्णांक hvsi_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;

	वापस hp->n_outbuf;
पूर्ण

अटल पूर्णांक hvsi_ग_लिखो(काष्ठा tty_काष्ठा *tty,
		     स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;
	स्थिर अक्षर *source = buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक total = 0;
	पूर्णांक origcount = count;

	spin_lock_irqsave(&hp->lock, flags);

	pr_debug("%s: %i chars in buffer\n", __func__, hp->n_outbuf);

	अगर (!is_खोलो(hp)) अणु
		/* we're either closing or not yet open; don't accept data */
		pr_debug("%s: not open\n", __func__);
		जाओ out;
	पूर्ण

	/*
	 * when the hypervisor buffer (16K) fills, data will stay in hp->outbuf
	 * and hvsi_ग_लिखो_worker will be scheduled. subsequent hvsi_ग_लिखो() calls
	 * will see there is no room in outbuf and वापस.
	 */
	जबतक ((count > 0) && (hvsi_ग_लिखो_room(tty) > 0)) अणु
		पूर्णांक chunksize = min(count, hvsi_ग_लिखो_room(tty));

		BUG_ON(hp->n_outbuf < 0);
		स_नकल(hp->outbuf + hp->n_outbuf, source, chunksize);
		hp->n_outbuf += chunksize;

		total += chunksize;
		source += chunksize;
		count -= chunksize;
		hvsi_push(hp);
	पूर्ण

	अगर (hp->n_outbuf > 0) अणु
		/*
		 * we weren't able to ग_लिखो it all to the hypervisor.
		 * schedule another push attempt.
		 */
		schedule_delayed_work(&hp->ग_लिखोr, 10);
	पूर्ण

out:
	spin_unlock_irqrestore(&hp->lock, flags);

	अगर (total != origcount)
		pr_debug("%s: wanted %i, only wrote %i\n", __func__, origcount,
			total);

	वापस total;
पूर्ण

/*
 * I have never seen throttle or unthrottle called, so this little throttle
 * buffering scheme may or may not work.
 */
अटल व्योम hvsi_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;

	pr_debug("%s\n", __func__);

	h_vio_संकेत(hp->vtermno, VIO_IRQ_DISABLE);
पूर्ण

अटल व्योम hvsi_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;
	अचिन्हित दीर्घ flags;

	pr_debug("%s\n", __func__);

	spin_lock_irqsave(&hp->lock, flags);
	अगर (hp->n_throttle) अणु
		hvsi_send_overflow(hp);
		tty_flip_buffer_push(&hp->port);
	पूर्ण
	spin_unlock_irqrestore(&hp->lock, flags);


	h_vio_संकेत(hp->vtermno, VIO_IRQ_ENABLE);
पूर्ण

अटल पूर्णांक hvsi_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;

	hvsi_get_mctrl(hp);
	वापस hp->mctrl;
पूर्ण

अटल पूर्णांक hvsi_tiocmset(काष्ठा tty_काष्ठा *tty,
				अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा hvsi_काष्ठा *hp = tty->driver_data;
	अचिन्हित दीर्घ flags;
	uपूर्णांक16_t new_mctrl;

	/* we can only alter DTR */
	clear &= TIOCM_DTR;
	set &= TIOCM_DTR;

	spin_lock_irqsave(&hp->lock, flags);

	new_mctrl = (hp->mctrl & ~clear) | set;

	अगर (hp->mctrl != new_mctrl) अणु
		hvsi_set_mctrl(hp, new_mctrl);
		hp->mctrl = new_mctrl;
	पूर्ण
	spin_unlock_irqrestore(&hp->lock, flags);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा tty_operations hvsi_ops = अणु
	.खोलो = hvsi_खोलो,
	.बंद = hvsi_बंद,
	.ग_लिखो = hvsi_ग_लिखो,
	.hangup = hvsi_hangup,
	.ग_लिखो_room = hvsi_ग_लिखो_room,
	.अक्षरs_in_buffer = hvsi_अक्षरs_in_buffer,
	.throttle = hvsi_throttle,
	.unthrottle = hvsi_unthrottle,
	.tiocmget = hvsi_tiocmget,
	.tiocmset = hvsi_tiocmset,
पूर्ण;

अटल पूर्णांक __init hvsi_init(व्योम)
अणु
	पूर्णांक i;

	hvsi_driver = alloc_tty_driver(hvsi_count);
	अगर (!hvsi_driver)
		वापस -ENOMEM;

	hvsi_driver->driver_name = "hvsi";
	hvsi_driver->name = "hvsi";
	hvsi_driver->major = HVSI_MAJOR;
	hvsi_driver->minor_start = HVSI_MINOR;
	hvsi_driver->type = TTY_DRIVER_TYPE_SYSTEM;
	hvsi_driver->init_termios = tty_std_termios;
	hvsi_driver->init_termios.c_cflag = B9600 | CS8 | CREAD | HUPCL;
	hvsi_driver->init_termios.c_ispeed = 9600;
	hvsi_driver->init_termios.c_ospeed = 9600;
	hvsi_driver->flags = TTY_DRIVER_REAL_RAW;
	tty_set_operations(hvsi_driver, &hvsi_ops);

	क्रम (i=0; i < hvsi_count; i++) अणु
		काष्ठा hvsi_काष्ठा *hp = &hvsi_ports[i];
		पूर्णांक ret = 1;

		tty_port_link_device(&hp->port, hvsi_driver, i);

		ret = request_irq(hp->virq, hvsi_पूर्णांकerrupt, 0, "hvsi", hp);
		अगर (ret)
			prपूर्णांकk(KERN_ERR "HVSI: couldn't reserve irq 0x%x (error %i)\n",
				hp->virq, ret);
	पूर्ण
	hvsi_रुको = रुको_क्रम_state; /* irqs active now */

	अगर (tty_रेजिस्टर_driver(hvsi_driver))
		panic("Couldn't register hvsi console driver\n");

	prपूर्णांकk(KERN_DEBUG "HVSI: registered %i devices\n", hvsi_count);

	वापस 0;
पूर्ण
device_initcall(hvsi_init);

/***** console (not tty) code: *****/

अटल व्योम hvsi_console_prपूर्णांक(काष्ठा console *console, स्थिर अक्षर *buf,
		अचिन्हित पूर्णांक count)
अणु
	काष्ठा hvsi_काष्ठा *hp = &hvsi_ports[console->index];
	अक्षर c[HVSI_MAX_OUTGOING_DATA] __ALIGNED__;
	अचिन्हित पूर्णांक i = 0, n = 0;
	पूर्णांक ret, करोnecr = 0;

	mb();
	अगर (!is_खोलो(hp))
		वापस;

	/*
	 * ugh, we have to translate LF -> CRLF ourselves, in place.
	 * copied from hvc_console.c:
	 */
	जबतक (count > 0 || i > 0) अणु
		अगर (count > 0 && i < माप(c)) अणु
			अगर (buf[n] == '\n' && !करोnecr) अणु
				c[i++] = '\r';
				करोnecr = 1;
			पूर्ण अन्यथा अणु
				c[i++] = buf[n++];
				करोnecr = 0;
				--count;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = hvsi_put_अक्षरs(hp, c, i);
			अगर (ret < 0)
				i = 0;
			i -= ret;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा tty_driver *hvsi_console_device(काष्ठा console *console,
	पूर्णांक *index)
अणु
	*index = console->index;
	वापस hvsi_driver;
पूर्ण

अटल पूर्णांक __init hvsi_console_setup(काष्ठा console *console, अक्षर *options)
अणु
	काष्ठा hvsi_काष्ठा *hp;
	पूर्णांक ret;

	अगर (console->index < 0 || console->index >= hvsi_count)
		वापस -EINVAL;
	hp = &hvsi_ports[console->index];

	/* give the FSP a chance to change the baud rate when we re-खोलो */
	hvsi_बंद_protocol(hp);

	ret = hvsi_handshake(hp);
	अगर (ret < 0)
		वापस ret;

	ret = hvsi_get_mctrl(hp);
	अगर (ret < 0)
		वापस ret;

	ret = hvsi_set_mctrl(hp, hp->mctrl | TIOCM_DTR);
	अगर (ret < 0)
		वापस ret;

	hp->flags |= HVSI_CONSOLE;

	वापस 0;
पूर्ण

अटल काष्ठा console hvsi_console = अणु
	.name		= "hvsi",
	.ग_लिखो		= hvsi_console_prपूर्णांक,
	.device		= hvsi_console_device,
	.setup		= hvsi_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
पूर्ण;

अटल पूर्णांक __init hvsi_console_init(व्योम)
अणु
	काष्ठा device_node *vty;

	hvsi_रुको = poll_क्रम_state; /* no irqs yet; must poll */

	/* search device tree क्रम vty nodes */
	क्रम_each_compatible_node(vty, "serial", "hvterm-protocol") अणु
		काष्ठा hvsi_काष्ठा *hp;
		स्थिर __be32 *vtermno, *irq;

		vtermno = of_get_property(vty, "reg", शून्य);
		irq = of_get_property(vty, "interrupts", शून्य);
		अगर (!vtermno || !irq)
			जारी;

		अगर (hvsi_count >= MAX_NR_HVSI_CONSOLES) अणु
			of_node_put(vty);
			अवरोध;
		पूर्ण

		hp = &hvsi_ports[hvsi_count];
		INIT_DELAYED_WORK(&hp->ग_लिखोr, hvsi_ग_लिखो_worker);
		INIT_WORK(&hp->handshaker, hvsi_handshaker);
		init_रुकोqueue_head(&hp->emptyq);
		init_रुकोqueue_head(&hp->stateq);
		spin_lock_init(&hp->lock);
		tty_port_init(&hp->port);
		hp->index = hvsi_count;
		hp->inbuf_end = hp->inbuf;
		hp->state = HVSI_CLOSED;
		hp->vtermno = be32_to_cpup(vtermno);
		hp->virq = irq_create_mapping(शून्य, be32_to_cpup(irq));
		अगर (hp->virq == 0) अणु
			prपूर्णांकk(KERN_ERR "%s: couldn't create irq mapping for 0x%x\n",
			       __func__, be32_to_cpup(irq));
			tty_port_destroy(&hp->port);
			जारी;
		पूर्ण

		hvsi_count++;
	पूर्ण

	अगर (hvsi_count)
		रेजिस्टर_console(&hvsi_console);
	वापस 0;
पूर्ण
console_initcall(hvsi_console_init);
