<शैली गुरु>
#अगर_अघोषित _SLHC_H
#घोषणा _SLHC_H
/*
 * Definitions क्रम tcp compression routines.
 *
 * $Header: slcompress.h,v 1.10 89/12/31 08:53:02 van Exp $
 *
 * Copyright (c) 1989 Regents of the University of Calअगरornia.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such क्रमms and that any करोcumentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Calअगरornia, Berkeley.  The name of the
 * University may not be used to enकरोrse or promote products derived
 * from this software without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Van Jacobson (van@helios.ee.lbl.gov), Dec 31, 1989:
 *	- Initial distribution.
 *
 *
 * modअगरied क्रम KA9Q Internet Software Package by
 * Katie Stevens (dkstevens@ucdavis.edu)
 * University of Calअगरornia, Davis
 * Computing Services
 *	- 01-31-90	initial adaptation
 *
 *	- Feb 1991	Bill_Simpson@um.cc.umich.edu
 *			variable number of conversation slots
 *			allow zero or one slots
 *			separate routines
 *			status display
 */

/*
 * Compressed packet क्रमmat:
 *
 * The first octet contains the packet type (top 3 bits), TCP
 * 'push' bit, and flags that indicate which of the 4 TCP sequence
 * numbers have changed (bottom 5 bits).  The next octet is a
 * conversation number that associates a saved IP/TCP header with
 * the compressed packet.  The next two octets are the TCP checksum
 * from the original datagram.  The next 0 to 15 octets are
 * sequence number changes, one change per bit set in the header
 * (there may be no changes and there are two special हालs where
 * the receiver implicitly knows what changed -- see below).
 *
 * There are 5 numbers which can change (they are always inserted
 * in the following order): TCP urgent poपूर्णांकer, winकरोw,
 * acknowledgment, sequence number and IP ID.  (The urgent poपूर्णांकer
 * is dअगरferent from the others in that its value is sent, not the
 * change in value.)  Since typical use of SLIP links is biased
 * toward small packets (see comments on MTU/MSS below), changes
 * use a variable length coding with one octet क्रम numbers in the
 * range 1 - 255 and 3 octets (0, MSB, LSB) क्रम numbers in the
 * range 256 - 65535 or 0.  (If the change in sequence number or
 * ack is more than 65535, an uncompressed packet is sent.)
 */

/*
 * Packet types (must not conflict with IP protocol version)
 *
 * The top nibble of the first octet is the packet type.  There are
 * three possible types: IP (not proto TCP or tcp with one of the
 * control flags set); uncompressed TCP (a normal IP/TCP packet but
 * with the 8-bit protocol field replaced by an 8-bit connection id --
 * this type of packet syncs the sender & receiver); and compressed
 * TCP (described above).
 *
 * LSB of 4-bit field is TCP "PUSH" bit (a worthless anachronism) and
 * is logically part of the 4-bit "changes" field that follows.  Top
 * three bits are actual packet type.  For backward compatibility
 * and in the पूर्णांकerest of conserving bits, numbers are chosen so the
 * IP protocol version number (4) which normally appears in this nibble
 * means "IP packet".
 */


#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>

/* SLIP compression masks क्रम len/vers byte */
#घोषणा SL_TYPE_IP 0x40
#घोषणा SL_TYPE_UNCOMPRESSED_TCP 0x70
#घोषणा SL_TYPE_COMPRESSED_TCP 0x80
#घोषणा SL_TYPE_ERROR 0x00

/* Bits in first octet of compressed packet */
#घोषणा NEW_C	0x40	/* flag bits क्रम what changed in a packet */
#घोषणा NEW_I	0x20
#घोषणा NEW_S	0x08
#घोषणा NEW_A	0x04
#घोषणा NEW_W	0x02
#घोषणा NEW_U	0x01

/* reserved, special-हाल values of above */
#घोषणा SPECIAL_I (NEW_S|NEW_W|NEW_U)		/* echoed पूर्णांकeractive traffic */
#घोषणा SPECIAL_D (NEW_S|NEW_A|NEW_W|NEW_U)	/* unidirectional data */
#घोषणा SPECIALS_MASK (NEW_S|NEW_A|NEW_W|NEW_U)

#घोषणा TCP_PUSH_BIT 0x10

/*
 * data type and sizes conversion assumptions:
 *
 *	VJ code		KA9Q style	generic
 *	u_अक्षर		byte_t		अचिन्हित अक्षर	 8 bits
 *	u_लघु		पूर्णांक16		अचिन्हित लघु	16 bits
 *	u_पूर्णांक		पूर्णांक16		अचिन्हित लघु	16 bits
 *	u_दीर्घ		अचिन्हित दीर्घ	अचिन्हित दीर्घ	32 bits
 *	पूर्णांक		पूर्णांक32		दीर्घ		32 bits
 */

प्रकार __u8 byte_t;
प्रकार __u32 पूर्णांक32;

/*
 * "state" data क्रम each active tcp conversation on the wire.  This is
 * basically a copy of the entire IP/TCP header from the last packet
 * we saw from the conversation together with a small identअगरier
 * the transmit & receive ends of the line use to locate saved header.
 */
काष्ठा cstate अणु
	byte_t	cs_this;	/* connection id number (xmit) */
	bool	initialized;	/* true अगर initialized */
	काष्ठा cstate *next;	/* next in ring (xmit) */
	काष्ठा iphdr cs_ip;	/* ip/tcp hdr from most recent packet */
	काष्ठा tcphdr cs_tcp;
	अचिन्हित अक्षर cs_ipopt[64];
	अचिन्हित अक्षर cs_tcpopt[64];
	पूर्णांक cs_hsize;
पूर्ण;
#घोषणा शून्यSLSTATE	(काष्ठा cstate *)0

/*
 * all the state data क्रम one serial line (we need one of these per line).
 */
काष्ठा slcompress अणु
	काष्ठा cstate *tstate;	/* transmit connection states (array)*/
	काष्ठा cstate *rstate;	/* receive connection states (array)*/

	byte_t tslot_limit;	/* highest transmit slot id (0-l)*/
	byte_t rslot_limit;	/* highest receive slot id (0-l)*/

	byte_t xmit_oldest;	/* oldest xmit in ring */
	byte_t xmit_current;	/* most recent xmit id */
	byte_t recv_current;	/* most recent rcvd id */

	byte_t flags;
#घोषणा SLF_TOSS	0x01	/* tossing rcvd frames until id received */

	पूर्णांक32 sls_o_nontcp;	/* outbound non-TCP packets */
	पूर्णांक32 sls_o_tcp;	/* outbound TCP packets */
	पूर्णांक32 sls_o_uncompressed;	/* outbound uncompressed packets */
	पूर्णांक32 sls_o_compressed;	/* outbound compressed packets */
	पूर्णांक32 sls_o_searches;	/* searches क्रम connection state */
	पूर्णांक32 sls_o_misses;	/* बार couldn't find conn. state */

	पूर्णांक32 sls_i_uncompressed;	/* inbound uncompressed packets */
	पूर्णांक32 sls_i_compressed;	/* inbound compressed packets */
	पूर्णांक32 sls_i_error;	/* inbound error packets */
	पूर्णांक32 sls_i_tossed;	/* inbound packets tossed because of error */

	पूर्णांक32 sls_i_runt;
	पूर्णांक32 sls_i_badcheck;
पूर्ण;
#घोषणा शून्यSLCOMPR	(काष्ठा slcompress *)0

/* In slhc.c: */
काष्ठा slcompress *slhc_init(पूर्णांक rslots, पूर्णांक tslots);
व्योम slhc_मुक्त(काष्ठा slcompress *comp);

पूर्णांक slhc_compress(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize,
		  अचिन्हित अक्षर *ocp, अचिन्हित अक्षर **cpp, पूर्णांक compress_cid);
पूर्णांक slhc_uncompress(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize);
पूर्णांक slhc_remember(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize);
पूर्णांक slhc_toss(काष्ठा slcompress *comp);

#पूर्ण_अगर	/* _SLHC_H */
