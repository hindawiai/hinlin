<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic HDLC support routines क्रम Linux
 * Poपूर्णांक-to-poपूर्णांक protocol support
 *
 * Copyright (C) 1999 - 2008 Krzysztof Halasa <khc@pm.waw.pl>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hdlc.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/poll.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा DEBUG_CP		0 /* also bytes# to dump */
#घोषणा DEBUG_STATE		0
#घोषणा DEBUG_HARD_HEADER	0

#घोषणा HDLC_ADDR_ALLSTATIONS	0xFF
#घोषणा HDLC_CTRL_UI		0x03

#घोषणा PID_LCP			0xC021
#घोषणा PID_IP			0x0021
#घोषणा PID_IPCP		0x8021
#घोषणा PID_IPV6		0x0057
#घोषणा PID_IPV6CP		0x8057

क्रमागत अणुIDX_LCP = 0, IDX_IPCP, IDX_IPV6CP, IDX_COUNTपूर्ण;
क्रमागत अणुCP_CONF_REQ = 1, CP_CONF_ACK, CP_CONF_NAK, CP_CONF_REJ, CP_TERM_REQ,
      CP_TERM_ACK, CP_CODE_REJ, LCP_PROTO_REJ, LCP_ECHO_REQ, LCP_ECHO_REPLY,
      LCP_DISC_REQ, CP_CODESपूर्ण;
#अगर DEBUG_CP
अटल स्थिर अक्षर *स्थिर code_names[CP_CODES] = अणु
	"0", "ConfReq", "ConfAck", "ConfNak", "ConfRej", "TermReq",
	"TermAck", "CodeRej", "ProtoRej", "EchoReq", "EchoReply", "Discard"
पूर्ण;
अटल अक्षर debug_buffer[64 + 3 * DEBUG_CP];
#पूर्ण_अगर

क्रमागत अणुLCP_OPTION_MRU = 1, LCP_OPTION_ACCM, LCP_OPTION_MAGIC = 5पूर्ण;

काष्ठा hdlc_header अणु
	u8 address;
	u8 control;
	__be16 protocol;
पूर्ण;

काष्ठा cp_header अणु
	u8 code;
	u8 id;
	__be16 len;
पूर्ण;


काष्ठा proto अणु
	काष्ठा net_device *dev;
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ समयout;
	u16 pid;		/* protocol ID */
	u8 state;
	u8 cr_id;		/* ID of last Configuration-Request */
	u8 restart_counter;
पूर्ण;

काष्ठा ppp अणु
	काष्ठा proto protos[IDX_COUNT];
	spinlock_t lock;
	अचिन्हित दीर्घ last_pong;
	अचिन्हित पूर्णांक req_समयout, cr_retries, term_retries;
	अचिन्हित पूर्णांक keepalive_पूर्णांकerval, keepalive_समयout;
	u8 seq;			/* local sequence number क्रम requests */
	u8 echo_id;		/* ID of last Echo-Request (LCP) */
पूर्ण;

क्रमागत अणुCLOSED = 0, STOPPED, STOPPING, REQ_SENT, ACK_RECV, ACK_SENT, OPENED,
      STATES, STATE_MASK = 0xFपूर्ण;
क्रमागत अणुSTART = 0, STOP, TO_GOOD, TO_BAD, RCR_GOOD, RCR_BAD, RCA, RCN, RTR, RTA,
      RUC, RXJ_GOOD, RXJ_BAD, EVENTSपूर्ण;
क्रमागत अणुINV = 0x10, IRC = 0x20, ZRC = 0x40, SCR = 0x80, SCA = 0x100,
      SCN = 0x200, STR = 0x400, STA = 0x800, SCJ = 0x1000पूर्ण;

#अगर DEBUG_STATE
अटल स्थिर अक्षर *स्थिर state_names[STATES] = अणु
	"Closed", "Stopped", "Stopping", "ReqSent", "AckRecv", "AckSent",
	"Opened"
पूर्ण;
अटल स्थिर अक्षर *स्थिर event_names[EVENTS] = अणु
	"Start", "Stop", "TO+", "TO-", "RCR+", "RCR-", "RCA", "RCN",
	"RTR", "RTA", "RUC", "RXJ+", "RXJ-"
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा sk_buff_head tx_queue; /* used when holding the spin lock */

अटल पूर्णांक ppp_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr);

अटल अंतरभूत काष्ठा ppp* get_ppp(काष्ठा net_device *dev)
अणु
	वापस (काष्ठा ppp *)dev_to_hdlc(dev)->state;
पूर्ण

अटल अंतरभूत काष्ठा proto* get_proto(काष्ठा net_device *dev, u16 pid)
अणु
	काष्ठा ppp *ppp = get_ppp(dev);

	चयन (pid) अणु
	हाल PID_LCP:
		वापस &ppp->protos[IDX_LCP];
	हाल PID_IPCP:
		वापस &ppp->protos[IDX_IPCP];
	हाल PID_IPV6CP:
		वापस &ppp->protos[IDX_IPV6CP];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर* proto_name(u16 pid)
अणु
	चयन (pid) अणु
	हाल PID_LCP:
		वापस "LCP";
	हाल PID_IPCP:
		वापस "IPCP";
	हाल PID_IPV6CP:
		वापस "IPV6CP";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल __be16 ppp_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा hdlc_header *data = (काष्ठा hdlc_header*)skb->data;

	अगर (skb->len < माप(काष्ठा hdlc_header))
		वापस htons(ETH_P_HDLC);
	अगर (data->address != HDLC_ADDR_ALLSTATIONS ||
	    data->control != HDLC_CTRL_UI)
		वापस htons(ETH_P_HDLC);

	चयन (data->protocol) अणु
	हाल cpu_to_be16(PID_IP):
		skb_pull(skb, माप(काष्ठा hdlc_header));
		वापस htons(ETH_P_IP);

	हाल cpu_to_be16(PID_IPV6):
		skb_pull(skb, माप(काष्ठा hdlc_header));
		वापस htons(ETH_P_IPV6);

	शेष:
		वापस htons(ETH_P_HDLC);
	पूर्ण
पूर्ण


अटल पूर्णांक ppp_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   u16 type, स्थिर व्योम *daddr, स्थिर व्योम *saddr,
			   अचिन्हित पूर्णांक len)
अणु
	काष्ठा hdlc_header *data;
#अगर DEBUG_HARD_HEADER
	prपूर्णांकk(KERN_DEBUG "%s: ppp_hard_header() called\n", dev->name);
#पूर्ण_अगर

	skb_push(skb, माप(काष्ठा hdlc_header));
	data = (काष्ठा hdlc_header*)skb->data;

	data->address = HDLC_ADDR_ALLSTATIONS;
	data->control = HDLC_CTRL_UI;
	चयन (type) अणु
	हाल ETH_P_IP:
		data->protocol = htons(PID_IP);
		अवरोध;
	हाल ETH_P_IPV6:
		data->protocol = htons(PID_IPV6);
		अवरोध;
	हाल PID_LCP:
	हाल PID_IPCP:
	हाल PID_IPV6CP:
		data->protocol = htons(type);
		अवरोध;
	शेष:		/* unknown protocol */
		data->protocol = 0;
	पूर्ण
	वापस माप(काष्ठा hdlc_header);
पूर्ण


अटल व्योम ppp_tx_flush(व्योम)
अणु
	काष्ठा sk_buff *skb;
	जबतक ((skb = skb_dequeue(&tx_queue)) != शून्य)
		dev_queue_xmit(skb);
पूर्ण

अटल व्योम ppp_tx_cp(काष्ठा net_device *dev, u16 pid, u8 code,
		      u8 id, अचिन्हित पूर्णांक len, स्थिर व्योम *data)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cp_header *cp;
	अचिन्हित पूर्णांक magic_len = 0;
	अटल u32 magic;

#अगर DEBUG_CP
	पूर्णांक i;
	अक्षर *ptr;
#पूर्ण_अगर

	अगर (pid == PID_LCP && (code == LCP_ECHO_REQ || code == LCP_ECHO_REPLY))
		magic_len = माप(magic);

	skb = dev_alloc_skb(माप(काष्ठा hdlc_header) +
			    माप(काष्ठा cp_header) + magic_len + len);
	अगर (!skb) अणु
		netdev_warn(dev, "out of memory in ppp_tx_cp()\n");
		वापस;
	पूर्ण
	skb_reserve(skb, माप(काष्ठा hdlc_header));

	cp = skb_put(skb, माप(काष्ठा cp_header));
	cp->code = code;
	cp->id = id;
	cp->len = htons(माप(काष्ठा cp_header) + magic_len + len);

	अगर (magic_len)
		skb_put_data(skb, &magic, magic_len);
	अगर (len)
		skb_put_data(skb, data, len);

#अगर DEBUG_CP
	BUG_ON(code >= CP_CODES);
	ptr = debug_buffer;
	*ptr = '\x0';
	क्रम (i = 0; i < min_t(अचिन्हित पूर्णांक, magic_len + len, DEBUG_CP); i++) अणु
		प्र_लिखो(ptr, " %02X", skb->data[माप(काष्ठा cp_header) + i]);
		ptr += म_माप(ptr);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "%s: TX %s [%s id 0x%X]%s\n", dev->name,
	       proto_name(pid), code_names[code], id, debug_buffer);
#पूर्ण_अगर

	ppp_hard_header(skb, dev, pid, शून्य, शून्य, 0);

	skb->priority = TC_PRIO_CONTROL;
	skb->dev = dev;
	skb->protocol = htons(ETH_P_HDLC);
	skb_reset_network_header(skb);
	skb_queue_tail(&tx_queue, skb);
पूर्ण


/* State transition table (compare STD-51)
   Events                                   Actions
   TO+  = Timeout with counter > 0          irc = Initialize-Restart-Count
   TO-  = Timeout with counter expired      zrc = Zero-Restart-Count

   RCR+ = Receive-Configure-Request (Good)  scr = Send-Configure-Request
   RCR- = Receive-Configure-Request (Bad)
   RCA  = Receive-Configure-Ack             sca = Send-Configure-Ack
   RCN  = Receive-Configure-Nak/Rej         scn = Send-Configure-Nak/Rej

   RTR  = Receive-Terminate-Request         str = Send-Terminate-Request
   RTA  = Receive-Terminate-Ack             sta = Send-Terminate-Ack

   RUC  = Receive-Unknown-Code              scj = Send-Code-Reject
   RXJ+ = Receive-Code-Reject (permitted)
       or Receive-Protocol-Reject
   RXJ- = Receive-Code-Reject (catastrophic)
       or Receive-Protocol-Reject
*/
अटल पूर्णांक cp_table[EVENTS][STATES] = अणु
	/* CLOSED     STOPPED STOPPING REQ_SENT ACK_RECV ACK_SENT OPENED
	     0           1         2       3       4      5          6    */
	अणुIRC|SCR|3,     INV     , INV ,   INV   , INV ,  INV    ,   INV   पूर्ण, /* START */
	अणु   INV   ,      0      ,  0  ,    0    ,  0  ,   0     ,    0    पूर्ण, /* STOP */
	अणु   INV   ,     INV     ,STR|2,  SCR|3  ,SCR|3,  SCR|5  ,   INV   पूर्ण, /* TO+ */
	अणु   INV   ,     INV     ,  1  ,    1    ,  1  ,    1    ,   INV   पूर्ण, /* TO- */
	अणु  STA|0  ,IRC|SCR|SCA|5,  2  ,  SCA|5  ,SCA|6,  SCA|5  ,SCR|SCA|5पूर्ण, /* RCR+ */
	अणु  STA|0  ,IRC|SCR|SCN|3,  2  ,  SCN|3  ,SCN|4,  SCN|3  ,SCR|SCN|3पूर्ण, /* RCR- */
	अणु  STA|0  ,    STA|1    ,  2  ,  IRC|4  ,SCR|3,    6    , SCR|3   पूर्ण, /* RCA */
	अणु  STA|0  ,    STA|1    ,  2  ,IRC|SCR|3,SCR|3,IRC|SCR|5, SCR|3   पूर्ण, /* RCN */
	अणु  STA|0  ,    STA|1    ,STA|2,  STA|3  ,STA|3,  STA|3  ,ZRC|STA|2पूर्ण, /* RTR */
	अणु    0    ,      1      ,  1  ,    3    ,  3  ,    5    ,  SCR|3  पूर्ण, /* RTA */
	अणु  SCJ|0  ,    SCJ|1    ,SCJ|2,  SCJ|3  ,SCJ|4,  SCJ|5  ,  SCJ|6  पूर्ण, /* RUC */
	अणु    0    ,      1      ,  2  ,    3    ,  3  ,    5    ,    6    पूर्ण, /* RXJ+ */
	अणु    0    ,      1      ,  1  ,    1    ,  1  ,    1    ,IRC|STR|2पूर्ण, /* RXJ- */
पूर्ण;


/* SCA: RCR+ must supply id, len and data
   SCN: RCR- must supply code, id, len and data
   STA: RTR must supply id
   SCJ: RUC must supply CP packet len and data */
अटल व्योम ppp_cp_event(काष्ठा net_device *dev, u16 pid, u16 event, u8 code,
			 u8 id, अचिन्हित पूर्णांक len, स्थिर व्योम *data)
अणु
	पूर्णांक old_state, action;
	काष्ठा ppp *ppp = get_ppp(dev);
	काष्ठा proto *proto = get_proto(dev, pid);

	old_state = proto->state;
	BUG_ON(old_state >= STATES);
	BUG_ON(event >= EVENTS);

#अगर DEBUG_STATE
	prपूर्णांकk(KERN_DEBUG "%s: %s ppp_cp_event(%s) %s ...\n", dev->name,
	       proto_name(pid), event_names[event], state_names[proto->state]);
#पूर्ण_अगर

	action = cp_table[event][old_state];

	proto->state = action & STATE_MASK;
	अगर (action & (SCR | STR)) /* set Configure-Req/Terminate-Req समयr */
		mod_समयr(&proto->समयr, proto->समयout =
			  jअगरfies + ppp->req_समयout * HZ);
	अगर (action & ZRC)
		proto->restart_counter = 0;
	अगर (action & IRC)
		proto->restart_counter = (proto->state == STOPPING) ?
			ppp->term_retries : ppp->cr_retries;

	अगर (action & SCR)	/* send Configure-Request */
		ppp_tx_cp(dev, pid, CP_CONF_REQ, proto->cr_id = ++ppp->seq,
			  0, शून्य);
	अगर (action & SCA)	/* send Configure-Ack */
		ppp_tx_cp(dev, pid, CP_CONF_ACK, id, len, data);
	अगर (action & SCN)	/* send Configure-Nak/Reject */
		ppp_tx_cp(dev, pid, code, id, len, data);
	अगर (action & STR)	/* send Terminate-Request */
		ppp_tx_cp(dev, pid, CP_TERM_REQ, ++ppp->seq, 0, शून्य);
	अगर (action & STA)	/* send Terminate-Ack */
		ppp_tx_cp(dev, pid, CP_TERM_ACK, id, 0, शून्य);
	अगर (action & SCJ)	/* send Code-Reject */
		ppp_tx_cp(dev, pid, CP_CODE_REJ, ++ppp->seq, len, data);

	अगर (old_state != OPENED && proto->state == OPENED) अणु
		netdev_info(dev, "%s up\n", proto_name(pid));
		अगर (pid == PID_LCP) अणु
			netअगर_करोrmant_off(dev);
			ppp_cp_event(dev, PID_IPCP, START, 0, 0, 0, शून्य);
			ppp_cp_event(dev, PID_IPV6CP, START, 0, 0, 0, शून्य);
			ppp->last_pong = jअगरfies;
			mod_समयr(&proto->समयr, proto->समयout =
				  jअगरfies + ppp->keepalive_पूर्णांकerval * HZ);
		पूर्ण
	पूर्ण
	अगर (old_state == OPENED && proto->state != OPENED) अणु
		netdev_info(dev, "%s down\n", proto_name(pid));
		अगर (pid == PID_LCP) अणु
			netअगर_करोrmant_on(dev);
			ppp_cp_event(dev, PID_IPCP, STOP, 0, 0, 0, शून्य);
			ppp_cp_event(dev, PID_IPV6CP, STOP, 0, 0, 0, शून्य);
		पूर्ण
	पूर्ण
	अगर (old_state != CLOSED && proto->state == CLOSED)
		del_समयr(&proto->समयr);

#अगर DEBUG_STATE
	prपूर्णांकk(KERN_DEBUG "%s: %s ppp_cp_event(%s) ... %s\n", dev->name,
	       proto_name(pid), event_names[event], state_names[proto->state]);
#पूर्ण_अगर
पूर्ण


अटल व्योम ppp_cp_parse_cr(काष्ठा net_device *dev, u16 pid, u8 id,
			    अचिन्हित पूर्णांक req_len, स्थिर u8 *data)
अणु
	अटल u8 स्थिर valid_accm[6] = अणु LCP_OPTION_ACCM, 6, 0, 0, 0, 0 पूर्ण;
	स्थिर u8 *opt;
	u8 *out;
	अचिन्हित पूर्णांक len = req_len, nak_len = 0, rej_len = 0;

	अगर (!(out = kदो_स्मृति(len, GFP_ATOMIC))) अणु
		dev->stats.rx_dropped++;
		वापस;	/* out of memory, ignore CR packet */
	पूर्ण

	क्रम (opt = data; len; len -= opt[1], opt += opt[1]) अणु
		अगर (len < 2 || opt[1] < 2 || len < opt[1])
			जाओ err_out;

		अगर (pid == PID_LCP)
			चयन (opt[0]) अणु
			हाल LCP_OPTION_MRU:
				जारी; /* MRU always OK and > 1500 bytes? */

			हाल LCP_OPTION_ACCM: /* async control अक्षरacter map */
				अगर (opt[1] < माप(valid_accm))
					जाओ err_out;
				अगर (!स_भेद(opt, valid_accm,
					    माप(valid_accm)))
					जारी;
				अगर (!rej_len) अणु /* NAK it */
					स_नकल(out + nak_len, valid_accm,
					       माप(valid_accm));
					nak_len += माप(valid_accm);
					जारी;
				पूर्ण
				अवरोध;
			हाल LCP_OPTION_MAGIC:
				अगर (len < 6)
					जाओ err_out;
				अगर (opt[1] != 6 || (!opt[2] && !opt[3] &&
						    !opt[4] && !opt[5]))
					अवरोध; /* reject invalid magic number */
				जारी;
			पूर्ण
		/* reject this option */
		स_नकल(out + rej_len, opt, opt[1]);
		rej_len += opt[1];
	पूर्ण

	अगर (rej_len)
		ppp_cp_event(dev, pid, RCR_BAD, CP_CONF_REJ, id, rej_len, out);
	अन्यथा अगर (nak_len)
		ppp_cp_event(dev, pid, RCR_BAD, CP_CONF_NAK, id, nak_len, out);
	अन्यथा
		ppp_cp_event(dev, pid, RCR_GOOD, CP_CONF_ACK, id, req_len, data);

	kमुक्त(out);
	वापस;

err_out:
	dev->stats.rx_errors++;
	kमुक्त(out);
पूर्ण

अटल पूर्णांक ppp_rx(काष्ठा sk_buff *skb)
अणु
	काष्ठा hdlc_header *hdr = (काष्ठा hdlc_header*)skb->data;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा ppp *ppp = get_ppp(dev);
	काष्ठा proto *proto;
	काष्ठा cp_header *cp;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;
	u16 pid;
#अगर DEBUG_CP
	पूर्णांक i;
	अक्षर *ptr;
#पूर्ण_अगर

	spin_lock_irqsave(&ppp->lock, flags);
	/* Check HDLC header */
	अगर (skb->len < माप(काष्ठा hdlc_header))
		जाओ rx_error;
	cp = skb_pull(skb, माप(काष्ठा hdlc_header));
	अगर (hdr->address != HDLC_ADDR_ALLSTATIONS ||
	    hdr->control != HDLC_CTRL_UI)
		जाओ rx_error;

	pid = ntohs(hdr->protocol);
	proto = get_proto(dev, pid);
	अगर (!proto) अणु
		अगर (ppp->protos[IDX_LCP].state == OPENED)
			ppp_tx_cp(dev, PID_LCP, LCP_PROTO_REJ,
				  ++ppp->seq, skb->len + 2, &hdr->protocol);
		जाओ rx_error;
	पूर्ण

	len = ntohs(cp->len);
	अगर (len < माप(काष्ठा cp_header) /* no complete CP header? */ ||
	    skb->len < len /* truncated packet? */)
		जाओ rx_error;
	skb_pull(skb, माप(काष्ठा cp_header));
	len -= माप(काष्ठा cp_header);

	/* HDLC and CP headers stripped from skb */
#अगर DEBUG_CP
	अगर (cp->code < CP_CODES)
		प्र_लिखो(debug_buffer, "[%s id 0x%X]", code_names[cp->code],
			cp->id);
	अन्यथा
		प्र_लिखो(debug_buffer, "[code %u id 0x%X]", cp->code, cp->id);
	ptr = debug_buffer + म_माप(debug_buffer);
	क्रम (i = 0; i < min_t(अचिन्हित पूर्णांक, len, DEBUG_CP); i++) अणु
		प्र_लिखो(ptr, " %02X", skb->data[i]);
		ptr += म_माप(ptr);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "%s: RX %s %s\n", dev->name, proto_name(pid),
	       debug_buffer);
#पूर्ण_अगर

	/* LCP only */
	अगर (pid == PID_LCP)
		चयन (cp->code) अणु
		हाल LCP_PROTO_REJ:
			pid = ntohs(*(__be16*)skb->data);
			अगर (pid == PID_LCP || pid == PID_IPCP ||
			    pid == PID_IPV6CP)
				ppp_cp_event(dev, pid, RXJ_BAD, 0, 0,
					     0, शून्य);
			जाओ out;

		हाल LCP_ECHO_REQ: /* send Echo-Reply */
			अगर (len >= 4 && proto->state == OPENED)
				ppp_tx_cp(dev, PID_LCP, LCP_ECHO_REPLY,
					  cp->id, len - 4, skb->data + 4);
			जाओ out;

		हाल LCP_ECHO_REPLY:
			अगर (cp->id == ppp->echo_id)
				ppp->last_pong = jअगरfies;
			जाओ out;

		हाल LCP_DISC_REQ: /* discard */
			जाओ out;
		पूर्ण

	/* LCP, IPCP and IPV6CP */
	चयन (cp->code) अणु
	हाल CP_CONF_REQ:
		ppp_cp_parse_cr(dev, pid, cp->id, len, skb->data);
		अवरोध;

	हाल CP_CONF_ACK:
		अगर (cp->id == proto->cr_id)
			ppp_cp_event(dev, pid, RCA, 0, 0, 0, शून्य);
		अवरोध;

	हाल CP_CONF_REJ:
	हाल CP_CONF_NAK:
		अगर (cp->id == proto->cr_id)
			ppp_cp_event(dev, pid, RCN, 0, 0, 0, शून्य);
		अवरोध;

	हाल CP_TERM_REQ:
		ppp_cp_event(dev, pid, RTR, 0, cp->id, 0, शून्य);
		अवरोध;

	हाल CP_TERM_ACK:
		ppp_cp_event(dev, pid, RTA, 0, 0, 0, शून्य);
		अवरोध;

	हाल CP_CODE_REJ:
		ppp_cp_event(dev, pid, RXJ_BAD, 0, 0, 0, शून्य);
		अवरोध;

	शेष:
		len += माप(काष्ठा cp_header);
		अगर (len > dev->mtu)
			len = dev->mtu;
		ppp_cp_event(dev, pid, RUC, 0, 0, len, cp);
		अवरोध;
	पूर्ण
	जाओ out;

rx_error:
	dev->stats.rx_errors++;
out:
	spin_unlock_irqrestore(&ppp->lock, flags);
	dev_kमुक्त_skb_any(skb);
	ppp_tx_flush();
	वापस NET_RX_DROP;
पूर्ण

अटल व्योम ppp_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा proto *proto = from_समयr(proto, t, समयr);
	काष्ठा ppp *ppp = get_ppp(proto->dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppp->lock, flags);
	/* mod_समयr could be called after we entered this function but
	 * beक्रमe we got the lock.
	 */
	अगर (समयr_pending(&proto->समयr)) अणु
		spin_unlock_irqrestore(&ppp->lock, flags);
		वापस;
	पूर्ण
	चयन (proto->state) अणु
	हाल STOPPING:
	हाल REQ_SENT:
	हाल ACK_RECV:
	हाल ACK_SENT:
		अगर (proto->restart_counter) अणु
			ppp_cp_event(proto->dev, proto->pid, TO_GOOD, 0, 0,
				     0, शून्य);
			proto->restart_counter--;
		पूर्ण अन्यथा अगर (netअगर_carrier_ok(proto->dev))
			ppp_cp_event(proto->dev, proto->pid, TO_GOOD, 0, 0,
				     0, शून्य);
		अन्यथा
			ppp_cp_event(proto->dev, proto->pid, TO_BAD, 0, 0,
				     0, शून्य);
		अवरोध;

	हाल OPENED:
		अगर (proto->pid != PID_LCP)
			अवरोध;
		अगर (समय_after(jअगरfies, ppp->last_pong +
			       ppp->keepalive_समयout * HZ)) अणु
			netdev_info(proto->dev, "Link down\n");
			ppp_cp_event(proto->dev, PID_LCP, STOP, 0, 0, 0, शून्य);
			ppp_cp_event(proto->dev, PID_LCP, START, 0, 0, 0, शून्य);
		पूर्ण अन्यथा अणु	/* send keep-alive packet */
			ppp->echo_id = ++ppp->seq;
			ppp_tx_cp(proto->dev, PID_LCP, LCP_ECHO_REQ,
				  ppp->echo_id, 0, शून्य);
			proto->समयr.expires = jअगरfies +
				ppp->keepalive_पूर्णांकerval * HZ;
			add_समयr(&proto->समयr);
		पूर्ण
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ppp->lock, flags);
	ppp_tx_flush();
पूर्ण


अटल व्योम ppp_start(काष्ठा net_device *dev)
अणु
	काष्ठा ppp *ppp = get_ppp(dev);
	पूर्णांक i;

	क्रम (i = 0; i < IDX_COUNT; i++) अणु
		काष्ठा proto *proto = &ppp->protos[i];
		proto->dev = dev;
		समयr_setup(&proto->समयr, ppp_समयr, 0);
		proto->state = CLOSED;
	पूर्ण
	ppp->protos[IDX_LCP].pid = PID_LCP;
	ppp->protos[IDX_IPCP].pid = PID_IPCP;
	ppp->protos[IDX_IPV6CP].pid = PID_IPV6CP;

	ppp_cp_event(dev, PID_LCP, START, 0, 0, 0, शून्य);
पूर्ण

अटल व्योम ppp_stop(काष्ठा net_device *dev)
अणु
	ppp_cp_event(dev, PID_LCP, STOP, 0, 0, 0, शून्य);
पूर्ण

अटल व्योम ppp_बंद(काष्ठा net_device *dev)
अणु
	ppp_tx_flush();
पूर्ण

अटल काष्ठा hdlc_proto proto = अणु
	.start		= ppp_start,
	.stop		= ppp_stop,
	.बंद		= ppp_बंद,
	.type_trans	= ppp_type_trans,
	.ioctl		= ppp_ioctl,
	.netअगर_rx	= ppp_rx,
	.module		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा header_ops ppp_header_ops = अणु
	.create = ppp_hard_header,
पूर्ण;

अटल पूर्णांक ppp_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा ppp *ppp;
	पूर्णांक result;

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_GET_PROTO:
		अगर (dev_to_hdlc(dev)->proto != &proto)
			वापस -EINVAL;
		अगरr->अगरr_settings.type = IF_PROTO_PPP;
		वापस 0; /* वापस protocol only, no settable parameters */

	हाल IF_PROTO_PPP:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;

		/* no settable parameters */

		result = hdlc->attach(dev, ENCODING_NRZ,PARITY_CRC16_PR1_CCITT);
		अगर (result)
			वापस result;

		result = attach_hdlc_protocol(dev, &proto, माप(काष्ठा ppp));
		अगर (result)
			वापस result;

		ppp = get_ppp(dev);
		spin_lock_init(&ppp->lock);
		ppp->req_समयout = 2;
		ppp->cr_retries = 10;
		ppp->term_retries = 2;
		ppp->keepalive_पूर्णांकerval = 10;
		ppp->keepalive_समयout = 60;

		dev->hard_header_len = माप(काष्ठा hdlc_header);
		dev->header_ops = &ppp_header_ops;
		dev->type = ARPHRD_PPP;
		call_netdevice_notअगरiers(NETDEV_POST_TYPE_CHANGE, dev);
		netअगर_करोrmant_on(dev);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण


अटल पूर्णांक __init mod_init(व्योम)
अणु
	skb_queue_head_init(&tx_queue);
	रेजिस्टर_hdlc_protocol(&proto);
	वापस 0;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
	unरेजिस्टर_hdlc_protocol(&proto);
पूर्ण


module_init(mod_init);
module_निकास(mod_निकास);

MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("PPP protocol support for generic HDLC");
MODULE_LICENSE("GPL v2");
