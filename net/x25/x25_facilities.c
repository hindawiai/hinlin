<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	X.25 Packet Layer release 002
 *
 *	This is ALPHA test software. This code may अवरोध your machine,
 *	अक्रमomly fail to work with new releases, misbehave and/or generally
 *	screw up. It might even work.
 *
 *	This code REQUIRES 2.1.15 or higher
 *
 *	History
 *	X.25 001	Split from x25_subr.c
 *	mar/20/00	Daniela Squassoni Disabling/enabling of facilities
 *					  negotiation.
 *	apr/14/05	Shaun Pereira - Allow fast select with no restriction
 *					on response.
 */

#घोषणा pr_fmt(fmt) "X25: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/x25.h>

/**
 * x25_parse_facilities - Parse facilities from skb पूर्णांकo the facilities काष्ठाs
 *
 * @skb: sk_buff to parse
 * @facilities: Regular facilities, updated as facilities are found
 * @dte_facs: ITU DTE facilities, updated as DTE facilities are found
 * @vc_fac_mask: mask is updated with all facilities found
 *
 * Return codes:
 *  -1 - Parsing error, caller should drop call and clean up
 *   0 - Parse OK, this skb has no facilities
 *  >0 - Parse OK, वापसs the length of the facilities header
 *
 */
पूर्णांक x25_parse_facilities(काष्ठा sk_buff *skb, काष्ठा x25_facilities *facilities,
		काष्ठा x25_dte_facilities *dte_facs, अचिन्हित दीर्घ *vc_fac_mask)
अणु
	अचिन्हित अक्षर *p;
	अचिन्हित पूर्णांक len;

	*vc_fac_mask = 0;

	/*
	 * The kernel knows which facilities were set on an incoming call but
	 * currently this inक्रमmation is not available to userspace.  Here we
	 * give userspace who पढ़ो incoming call facilities 0 length to indicate
	 * it wasn't set.
	 */
	dte_facs->calling_len = 0;
	dte_facs->called_len = 0;
	स_रखो(dte_facs->called_ae, '\0', माप(dte_facs->called_ae));
	स_रखो(dte_facs->calling_ae, '\0', माप(dte_facs->calling_ae));

	अगर (!pskb_may_pull(skb, 1))
		वापस 0;

	len = skb->data[0];

	अगर (!pskb_may_pull(skb, 1 + len))
		वापस -1;

	p = skb->data + 1;

	जबतक (len > 0) अणु
		चयन (*p & X25_FAC_CLASS_MASK) अणु
		हाल X25_FAC_CLASS_A:
			अगर (len < 2)
				वापस -1;
			चयन (*p) अणु
			हाल X25_FAC_REVERSE:
				अगर((p[1] & 0x81) == 0x81) अणु
					facilities->reverse = p[1] & 0x81;
					*vc_fac_mask |= X25_MASK_REVERSE;
					अवरोध;
				पूर्ण

				अगर((p[1] & 0x01) == 0x01) अणु
					facilities->reverse = p[1] & 0x01;
					*vc_fac_mask |= X25_MASK_REVERSE;
					अवरोध;
				पूर्ण

				अगर((p[1] & 0x80) == 0x80) अणु
					facilities->reverse = p[1] & 0x80;
					*vc_fac_mask |= X25_MASK_REVERSE;
					अवरोध;
				पूर्ण

				अगर(p[1] == 0x00) अणु
					facilities->reverse
						= X25_DEFAULT_REVERSE;
					*vc_fac_mask |= X25_MASK_REVERSE;
					अवरोध;
				पूर्ण
				fallthrough;
			हाल X25_FAC_THROUGHPUT:
				facilities->throughput = p[1];
				*vc_fac_mask |= X25_MASK_THROUGHPUT;
				अवरोध;
			हाल X25_MARKER:
				अवरोध;
			शेष:
				pr_debug("unknown facility "
				       "%02X, value %02X\n",
				       p[0], p[1]);
				अवरोध;
			पूर्ण
			p   += 2;
			len -= 2;
			अवरोध;
		हाल X25_FAC_CLASS_B:
			अगर (len < 3)
				वापस -1;
			चयन (*p) अणु
			हाल X25_FAC_PACKET_SIZE:
				facilities->pacsize_in  = p[1];
				facilities->pacsize_out = p[2];
				*vc_fac_mask |= X25_MASK_PACKET_SIZE;
				अवरोध;
			हाल X25_FAC_WINDOW_SIZE:
				facilities->winsize_in  = p[1];
				facilities->winsize_out = p[2];
				*vc_fac_mask |= X25_MASK_WINDOW_SIZE;
				अवरोध;
			शेष:
				pr_debug("unknown facility "
				       "%02X, values %02X, %02X\n",
				       p[0], p[1], p[2]);
				अवरोध;
			पूर्ण
			p   += 3;
			len -= 3;
			अवरोध;
		हाल X25_FAC_CLASS_C:
			अगर (len < 4)
				वापस -1;
			pr_debug("unknown facility %02X, "
			       "values %02X, %02X, %02X\n",
			       p[0], p[1], p[2], p[3]);
			p   += 4;
			len -= 4;
			अवरोध;
		हाल X25_FAC_CLASS_D:
			अगर (len < p[1] + 2)
				वापस -1;
			चयन (*p) अणु
			हाल X25_FAC_CALLING_AE:
				अगर (p[1] > X25_MAX_DTE_FACIL_LEN || p[1] <= 1)
					वापस -1;
				अगर (p[2] > X25_MAX_AE_LEN)
					वापस -1;
				dte_facs->calling_len = p[2];
				स_नकल(dte_facs->calling_ae, &p[3], p[1] - 1);
				*vc_fac_mask |= X25_MASK_CALLING_AE;
				अवरोध;
			हाल X25_FAC_CALLED_AE:
				अगर (p[1] > X25_MAX_DTE_FACIL_LEN || p[1] <= 1)
					वापस -1;
				अगर (p[2] > X25_MAX_AE_LEN)
					वापस -1;
				dte_facs->called_len = p[2];
				स_नकल(dte_facs->called_ae, &p[3], p[1] - 1);
				*vc_fac_mask |= X25_MASK_CALLED_AE;
				अवरोध;
			शेष:
				pr_debug("unknown facility %02X,"
					"length %d\n", p[0], p[1]);
				अवरोध;
			पूर्ण
			len -= p[1] + 2;
			p += p[1] + 2;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस p - skb->data;
पूर्ण

/*
 *	Create a set of facilities.
 */
पूर्णांक x25_create_facilities(अचिन्हित अक्षर *buffer,
		काष्ठा x25_facilities *facilities,
		काष्ठा x25_dte_facilities *dte_facs, अचिन्हित दीर्घ facil_mask)
अणु
	अचिन्हित अक्षर *p = buffer + 1;
	पूर्णांक len;

	अगर (!facil_mask) अणु
		/*
		 * Length of the facilities field in call_req or
		 * call_accept packets
		 */
		buffer[0] = 0;
		len = 1; /* 1 byte क्रम the length field */
		वापस len;
	पूर्ण

	अगर (facilities->reverse && (facil_mask & X25_MASK_REVERSE)) अणु
		*p++ = X25_FAC_REVERSE;
		*p++ = facilities->reverse;
	पूर्ण

	अगर (facilities->throughput && (facil_mask & X25_MASK_THROUGHPUT)) अणु
		*p++ = X25_FAC_THROUGHPUT;
		*p++ = facilities->throughput;
	पूर्ण

	अगर ((facilities->pacsize_in || facilities->pacsize_out) &&
	    (facil_mask & X25_MASK_PACKET_SIZE)) अणु
		*p++ = X25_FAC_PACKET_SIZE;
		*p++ = facilities->pacsize_in ? : facilities->pacsize_out;
		*p++ = facilities->pacsize_out ? : facilities->pacsize_in;
	पूर्ण

	अगर ((facilities->winsize_in || facilities->winsize_out) &&
	    (facil_mask & X25_MASK_WINDOW_SIZE)) अणु
		*p++ = X25_FAC_WINDOW_SIZE;
		*p++ = facilities->winsize_in ? : facilities->winsize_out;
		*p++ = facilities->winsize_out ? : facilities->winsize_in;
	पूर्ण

	अगर (facil_mask & (X25_MASK_CALLING_AE|X25_MASK_CALLED_AE)) अणु
		*p++ = X25_MARKER;
		*p++ = X25_DTE_SERVICES;
	पूर्ण

	अगर (dte_facs->calling_len && (facil_mask & X25_MASK_CALLING_AE)) अणु
		अचिन्हित पूर्णांक bytecount = (dte_facs->calling_len + 1) >> 1;
		*p++ = X25_FAC_CALLING_AE;
		*p++ = 1 + bytecount;
		*p++ = dte_facs->calling_len;
		स_नकल(p, dte_facs->calling_ae, bytecount);
		p += bytecount;
	पूर्ण

	अगर (dte_facs->called_len && (facil_mask & X25_MASK_CALLED_AE)) अणु
		अचिन्हित पूर्णांक bytecount = (dte_facs->called_len % 2) ?
		dte_facs->called_len / 2 + 1 :
		dte_facs->called_len / 2;
		*p++ = X25_FAC_CALLED_AE;
		*p++ = 1 + bytecount;
		*p++ = dte_facs->called_len;
		स_नकल(p, dte_facs->called_ae, bytecount);
		p+=bytecount;
	पूर्ण

	len       = p - buffer;
	buffer[0] = len - 1;

	वापस len;
पूर्ण

/*
 *	Try to reach a compromise on a set of facilities.
 *
 *	The only real problem is with reverse अक्षरging.
 */
पूर्णांक x25_negotiate_facilities(काष्ठा sk_buff *skb, काष्ठा sock *sk,
		काष्ठा x25_facilities *new, काष्ठा x25_dte_facilities *dte)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);
	काष्ठा x25_facilities *ours = &x25->facilities;
	काष्ठा x25_facilities theirs;
	पूर्णांक len;

	स_रखो(&theirs, 0, माप(theirs));
	स_नकल(new, ours, माप(*new));
	स_रखो(dte, 0, माप(*dte));

	len = x25_parse_facilities(skb, &theirs, dte, &x25->vc_facil_mask);
	अगर (len < 0)
		वापस len;

	/*
	 *	They want reverse अक्षरging, we won't accept it.
	 */
	अगर ((theirs.reverse & 0x01 ) && (ours->reverse & 0x01)) अणु
		SOCK_DEBUG(sk, "X.25: rejecting reverse charging request\n");
		वापस -1;
	पूर्ण

	new->reverse = theirs.reverse;

	अगर (theirs.throughput) अणु
		पूर्णांक theirs_in =  theirs.throughput & 0x0f;
		पूर्णांक theirs_out = theirs.throughput & 0xf0;
		पूर्णांक ours_in  = ours->throughput & 0x0f;
		पूर्णांक ours_out = ours->throughput & 0xf0;
		अगर (!ours_in || theirs_in < ours_in) अणु
			SOCK_DEBUG(sk, "X.25: inbound throughput negotiated\n");
			new->throughput = (new->throughput & 0xf0) | theirs_in;
		पूर्ण
		अगर (!ours_out || theirs_out < ours_out) अणु
			SOCK_DEBUG(sk,
				"X.25: outbound throughput negotiated\n");
			new->throughput = (new->throughput & 0x0f) | theirs_out;
		पूर्ण
	पूर्ण

	अगर (theirs.pacsize_in && theirs.pacsize_out) अणु
		अगर (theirs.pacsize_in < ours->pacsize_in) अणु
			SOCK_DEBUG(sk, "X.25: packet size inwards negotiated down\n");
			new->pacsize_in = theirs.pacsize_in;
		पूर्ण
		अगर (theirs.pacsize_out < ours->pacsize_out) अणु
			SOCK_DEBUG(sk, "X.25: packet size outwards negotiated down\n");
			new->pacsize_out = theirs.pacsize_out;
		पूर्ण
	पूर्ण

	अगर (theirs.winsize_in && theirs.winsize_out) अणु
		अगर (theirs.winsize_in < ours->winsize_in) अणु
			SOCK_DEBUG(sk, "X.25: window size inwards negotiated down\n");
			new->winsize_in = theirs.winsize_in;
		पूर्ण
		अगर (theirs.winsize_out < ours->winsize_out) अणु
			SOCK_DEBUG(sk, "X.25: window size outwards negotiated down\n");
			new->winsize_out = theirs.winsize_out;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

/*
 *	Limit values of certain facilities according to the capability of the
 *      currently attached x25 link.
 */
व्योम x25_limit_facilities(काष्ठा x25_facilities *facilities,
			  काष्ठा x25_neigh *nb)
अणु

	अगर (!nb->extended) अणु
		अगर (facilities->winsize_in  > 7) अणु
			pr_debug("incoming winsize limited to 7\n");
			facilities->winsize_in = 7;
		पूर्ण
		अगर (facilities->winsize_out > 7) अणु
			facilities->winsize_out = 7;
			pr_debug("outgoing winsize limited to 7\n");
		पूर्ण
	पूर्ण
पूर्ण
