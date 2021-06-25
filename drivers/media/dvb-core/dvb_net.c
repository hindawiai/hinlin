<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dvb_net.c
 *
 * Copyright (C) 2001 Convergence पूर्णांकegrated media GmbH
 *                    Ralph Metzler <ralph@convergence.de>
 * Copyright (C) 2002 Ralph Metzler <rjkm@metzlerbros.de>
 *
 * ULE Decapsulation code:
 * Copyright (C) 2003, 2004 gcs - Global Communication & Services GmbH.
 *                      and Deparपंचांगent of Scientअगरic Computing
 *                          Paris Lodron University of Salzburg.
 *                          Hilmar Linder <hlinder@cosy.sbg.ac.at>
 *                      and Wolfram Stering <wstering@cosy.sbg.ac.at>
 *
 * ULE Decaps according to RFC 4326.
 */

/*
 * ULE ChangeLog:
 * Feb 2004: hl/ws v1: Implementing draft-fair-ipdvb-ule-01.txt
 *
 * Dec 2004: hl/ws v2: Implementing draft-ietf-ipdvb-ule-03.txt:
 *                       ULE Extension header handling.
 *                     Bugreports by Moritz Vieth and Hanno Tersteegen,
 *                       Fraunhofer Institute क्रम Open Communication Systems
 *                       Competence Center क्रम Advanced Satellite Communications.
 *                     Bugfixes and robustness improvements.
 *                     Filtering on dest MAC addresses, अगर present (D-Bit = 0)
 *                     DVB_ULE_DEBUG compile-समय option.
 * Apr 2006: cp v3:    Bugfixes and compliency with RFC 4326 (ULE) by
 *                       Christian Praehauser <cpraehaus@cosy.sbg.ac.at>,
 *                       Paris Lodron University of Salzburg.
 */

/*
 * FIXME / TODO (dvb_net.c):
 *
 * Unloading करोes not work क्रम 2.6.9 kernels: a refcount करोesn't go to zero.
 *
 */

#घोषणा pr_fmt(fmt) "dvb_net: " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/dvb/net.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>

#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>

अटल अंतरभूत __u32 iov_crc32( __u32 c, काष्ठा kvec *iov, अचिन्हित पूर्णांक cnt )
अणु
	अचिन्हित पूर्णांक j;
	क्रम (j = 0; j < cnt; j++)
		c = crc32_be( c, iov[j].iov_base, iov[j].iov_len );
	वापस c;
पूर्ण


#घोषणा DVB_NET_MULTICAST_MAX 10

#अगर_घोषित DVB_ULE_DEBUG
/*
 * The code inside DVB_ULE_DEBUG keeps a history of the
 * last 100 TS cells processed.
 */
अटल अचिन्हित अक्षर ule_hist[100*TS_SZ] = अणु 0 पूर्ण;
अटल अचिन्हित अक्षर *ule_where = ule_hist, ule_dump;

अटल व्योम hexdump(स्थिर अचिन्हित अक्षर *buf, अचिन्हित लघु len)
अणु
	prपूर्णांक_hex_dump_debug("", DUMP_PREFIX_OFFSET, 16, 1, buf, len, true);
पूर्ण
#पूर्ण_अगर

काष्ठा dvb_net_priv अणु
	पूर्णांक in_use;
	u16 pid;
	काष्ठा net_device *net;
	काष्ठा dvb_net *host;
	काष्ठा dmx_demux *demux;
	काष्ठा dmx_section_feed *secfeed;
	काष्ठा dmx_section_filter *secfilter;
	काष्ठा dmx_ts_feed *tsfeed;
	पूर्णांक multi_num;
	काष्ठा dmx_section_filter *multi_secfilter[DVB_NET_MULTICAST_MAX];
	अचिन्हित अक्षर multi_macs[DVB_NET_MULTICAST_MAX][6];
	पूर्णांक rx_mode;
#घोषणा RX_MODE_UNI 0
#घोषणा RX_MODE_MULTI 1
#घोषणा RX_MODE_ALL_MULTI 2
#घोषणा RX_MODE_PROMISC 3
	काष्ठा work_काष्ठा set_multicast_list_wq;
	काष्ठा work_काष्ठा restart_net_feed_wq;
	अचिन्हित अक्षर feedtype;			/* Either FEED_TYPE_ or FEED_TYPE_ULE */
	पूर्णांक need_pusi;				/* Set to 1, अगर synchronization on PUSI required. */
	अचिन्हित अक्षर tscc;			/* TS continuity counter after sync on PUSI. */
	काष्ठा sk_buff *ule_skb;		/* ULE SNDU decodes पूर्णांकo this buffer. */
	अचिन्हित अक्षर *ule_next_hdr;		/* Poपूर्णांकer पूर्णांकo skb to next ULE extension header. */
	अचिन्हित लघु ule_sndu_len;		/* ULE SNDU length in bytes, w/o D-Bit. */
	अचिन्हित लघु ule_sndu_type;		/* ULE SNDU type field, complete. */
	अचिन्हित अक्षर ule_sndu_type_1;		/* ULE SNDU type field, अगर split across 2 TS cells. */
	अचिन्हित अक्षर ule_dbit;			/* Whether the DestMAC address present
						 * or not (bit is set). */
	अचिन्हित अक्षर ule_bridged;		/* Whether the ULE_BRIDGED extension header was found. */
	पूर्णांक ule_sndu_reमुख्य;			/* Nr. of bytes still required क्रम current ULE SNDU. */
	अचिन्हित दीर्घ ts_count;			/* Current ts cell counter. */
	काष्ठा mutex mutex;
पूर्ण;


/*
 *	Determine the packet's protocol ID. The rule here is that we
 *	assume 802.3 अगर the type field is लघु enough to be a length.
 *	This is normal practice and works क्रम any 'now in use' protocol.
 *
 *  stolen from eth.c out of the linux kernel, hacked क्रम dvb-device
 *  by Michael Holzt <kju@debian.org>
 */
अटल __be16 dvb_net_eth_type_trans(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा ethhdr *eth;
	अचिन्हित अक्षर *rawp;

	skb_reset_mac_header(skb);
	skb_pull(skb,dev->hard_header_len);
	eth = eth_hdr(skb);

	अगर (*eth->h_dest & 1) अणु
		अगर(ether_addr_equal(eth->h_dest,dev->broadcast))
			skb->pkt_type=PACKET_BROADCAST;
		अन्यथा
			skb->pkt_type=PACKET_MULTICAST;
	पूर्ण

	अगर (ntohs(eth->h_proto) >= ETH_P_802_3_MIN)
		वापस eth->h_proto;

	rawp = skb->data;

	/*
	 *	This is a magic hack to spot IPX packets. Older Novell अवरोधs
	 *	the protocol design and runs IPX over 802.3 without an 802.2 LLC
	 *	layer. We look क्रम FFFF which isn't a used 802.2 SSAP/DSAP. This
	 *	won't work क्रम fault tolerant netware but करोes क्रम the rest.
	 */
	अगर (*(अचिन्हित लघु *)rawp == 0xFFFF)
		वापस htons(ETH_P_802_3);

	/*
	 *	Real 802.2 LLC
	 */
	वापस htons(ETH_P_802_2);
पूर्ण

#घोषणा TS_SZ	188
#घोषणा TS_SYNC	0x47
#घोषणा TS_TEI	0x80
#घोषणा TS_SC	0xC0
#घोषणा TS_PUSI	0x40
#घोषणा TS_AF_A	0x20
#घोषणा TS_AF_D	0x10

/* ULE Extension Header handlers. */

#घोषणा ULE_TEST	0
#घोषणा ULE_BRIDGED	1

#घोषणा ULE_OPTEXTHDR_PADDING 0

अटल पूर्णांक ule_test_sndu( काष्ठा dvb_net_priv *p )
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक ule_bridged_sndu( काष्ठा dvb_net_priv *p )
अणु
	काष्ठा ethhdr *hdr = (काष्ठा ethhdr*) p->ule_next_hdr;
	अगर(ntohs(hdr->h_proto) < ETH_P_802_3_MIN) अणु
		पूर्णांक framelen = p->ule_sndu_len - ((p->ule_next_hdr+माप(काष्ठा ethhdr)) - p->ule_skb->data);
		/* A frame Type < ETH_P_802_3_MIN क्रम a bridged frame, पूर्णांकroduces a LLC Length field. */
		अगर(framelen != ntohs(hdr->h_proto)) अणु
			वापस -1;
		पूर्ण
	पूर्ण
	/* Note:
	 * From RFC4326:
	 *  "A bridged SNDU is a Mandatory Extension Header of Type 1.
	 *   It must be the final (or only) extension header specअगरied in the header chain of a SNDU."
	 * The 'ule_bridged' flag will cause the extension header processing loop to terminate.
	 */
	p->ule_bridged = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ule_exthdr_padding(काष्ठा dvb_net_priv *p)
अणु
	वापस 0;
पूर्ण

/*
 * Handle ULE extension headers.
 *  Function is called after a successful CRC32 verअगरication of an ULE SNDU to complete its decoding.
 *  Returns: >= 0: nr. of bytes consumed by next extension header
 *	     -1:   Mandatory extension header that is not recognized or TEST SNDU; discard.
 */
अटल पूर्णांक handle_one_ule_extension( काष्ठा dvb_net_priv *p )
अणु
	/* Table of mandatory extension header handlers.  The header type is the index. */
	अटल पूर्णांक (*ule_mandatory_ext_handlers[255])( काष्ठा dvb_net_priv *p ) =
		अणु [0] = ule_test_sndu, [1] = ule_bridged_sndu, [2] = शून्य,  पूर्ण;

	/* Table of optional extension header handlers.  The header type is the index. */
	अटल पूर्णांक (*ule_optional_ext_handlers[255])( काष्ठा dvb_net_priv *p ) =
		अणु [0] = ule_exthdr_padding, [1] = शून्य, पूर्ण;

	पूर्णांक ext_len = 0;
	अचिन्हित अक्षर hlen = (p->ule_sndu_type & 0x0700) >> 8;
	अचिन्हित अक्षर htype = p->ule_sndu_type & 0x00FF;

	/* Discriminate mandatory and optional extension headers. */
	अगर (hlen == 0) अणु
		/* Mandatory extension header */
		अगर (ule_mandatory_ext_handlers[htype]) अणु
			ext_len = ule_mandatory_ext_handlers[htype]( p );
			अगर(ext_len >= 0) अणु
				p->ule_next_hdr += ext_len;
				अगर (!p->ule_bridged) अणु
					p->ule_sndu_type = ntohs(*(__be16 *)p->ule_next_hdr);
					p->ule_next_hdr += 2;
				पूर्ण अन्यथा अणु
					p->ule_sndu_type = ntohs(*(__be16 *)(p->ule_next_hdr + ((p->ule_dbit ? 2 : 3) * ETH_ALEN)));
					/* This assures the extension handling loop will terminate. */
				पूर्ण
			पूर्ण
			// अन्यथा: extension handler failed or SNDU should be discarded
		पूर्ण अन्यथा
			ext_len = -1;	/* SNDU has to be discarded. */
	पूर्ण अन्यथा अणु
		/* Optional extension header.  Calculate the length. */
		ext_len = hlen << 1;
		/* Process the optional extension header according to its type. */
		अगर (ule_optional_ext_handlers[htype])
			(व्योम)ule_optional_ext_handlers[htype]( p );
		p->ule_next_hdr += ext_len;
		p->ule_sndu_type = ntohs( *(__be16 *)(p->ule_next_hdr-2) );
		/*
		 * note: the length of the next header type is included in the
		 * length of THIS optional extension header
		 */
	पूर्ण

	वापस ext_len;
पूर्ण

अटल पूर्णांक handle_ule_extensions( काष्ठा dvb_net_priv *p )
अणु
	पूर्णांक total_ext_len = 0, l;

	p->ule_next_hdr = p->ule_skb->data;
	करो अणु
		l = handle_one_ule_extension( p );
		अगर (l < 0)
			वापस l;	/* Stop extension header processing and discard SNDU. */
		total_ext_len += l;
		pr_debug("ule_next_hdr=%p, ule_sndu_type=%i, l=%i, total_ext_len=%i\n",
			 p->ule_next_hdr, (पूर्णांक)p->ule_sndu_type,
			 l, total_ext_len);

	पूर्ण जबतक (p->ule_sndu_type < ETH_P_802_3_MIN);

	वापस total_ext_len;
पूर्ण


/* Prepare क्रम a new ULE SNDU: reset the decoder state. */
अटल अंतरभूत व्योम reset_ule( काष्ठा dvb_net_priv *p )
अणु
	p->ule_skb = शून्य;
	p->ule_next_hdr = शून्य;
	p->ule_sndu_len = 0;
	p->ule_sndu_type = 0;
	p->ule_sndu_type_1 = 0;
	p->ule_sndu_reमुख्य = 0;
	p->ule_dbit = 0xFF;
	p->ule_bridged = 0;
पूर्ण

/*
 * Decode ULE SNDUs according to draft-ietf-ipdvb-ule-03.txt from a sequence of
 * TS cells of a single PID.
 */

काष्ठा dvb_net_ule_handle अणु
	काष्ठा net_device *dev;
	काष्ठा dvb_net_priv *priv;
	काष्ठा ethhdr *ethh;
	स्थिर u8 *buf;
	माप_प्रकार buf_len;
	अचिन्हित दीर्घ skipped;
	स्थिर u8 *ts, *ts_end, *from_where;
	u8 ts_reमुख्य, how_much, new_ts;
	bool error;
पूर्ण;

अटल पूर्णांक dvb_net_ule_new_ts_cell(काष्ठा dvb_net_ule_handle *h)
अणु
	/* We are about to process a new TS cell. */

#अगर_घोषित DVB_ULE_DEBUG
	अगर (ule_where >= &ule_hist[100*TS_SZ])
		ule_where = ule_hist;
	स_नकल(ule_where, h->ts, TS_SZ);
	अगर (ule_dump) अणु
		hexdump(ule_where, TS_SZ);
		ule_dump = 0;
	पूर्ण
	ule_where += TS_SZ;
#पूर्ण_अगर

	/*
	 * Check TS h->error conditions: sync_byte, transport_error_indicator,
	 * scrambling_control .
	 */
	अगर ((h->ts[0] != TS_SYNC) || (h->ts[1] & TS_TEI) ||
	    ((h->ts[3] & TS_SC) != 0)) अणु
		pr_warn("%lu: Invalid TS cell: SYNC %#x, TEI %u, SC %#x.\n",
			h->priv->ts_count, h->ts[0],
			(h->ts[1] & TS_TEI) >> 7,
			(h->ts[3] & TS_SC) >> 6);

		/* Drop partly decoded SNDU, reset state, resync on PUSI. */
		अगर (h->priv->ule_skb) अणु
			dev_kमुक्त_skb(h->priv->ule_skb);
			/* Prepare क्रम next SNDU. */
			h->dev->stats.rx_errors++;
			h->dev->stats.rx_frame_errors++;
		पूर्ण
		reset_ule(h->priv);
		h->priv->need_pusi = 1;

		/* Continue with next TS cell. */
		h->ts += TS_SZ;
		h->priv->ts_count++;
		वापस 1;
	पूर्ण

	h->ts_reमुख्य = 184;
	h->from_where = h->ts + 4;

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_net_ule_ts_pusi(काष्ठा dvb_net_ule_handle *h)
अणु
	अगर (h->ts[1] & TS_PUSI) अणु
		/* Find beginning of first ULE SNDU in current TS cell. */
		/* Synchronize continuity counter. */
		h->priv->tscc = h->ts[3] & 0x0F;
		/* There is a poपूर्णांकer field here. */
		अगर (h->ts[4] > h->ts_reमुख्य) अणु
			pr_err("%lu: Invalid ULE packet (pointer field %d)\n",
				h->priv->ts_count, h->ts[4]);
			h->ts += TS_SZ;
			h->priv->ts_count++;
			वापस 1;
		पूर्ण
		/* Skip to destination of poपूर्णांकer field. */
		h->from_where = &h->ts[5] + h->ts[4];
		h->ts_reमुख्य -= 1 + h->ts[4];
		h->skipped = 0;
	पूर्ण अन्यथा अणु
		h->skipped++;
		h->ts += TS_SZ;
		h->priv->ts_count++;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_net_ule_new_ts(काष्ठा dvb_net_ule_handle *h)
अणु
	/* Check continuity counter. */
	अगर ((h->ts[3] & 0x0F) == h->priv->tscc)
		h->priv->tscc = (h->priv->tscc + 1) & 0x0F;
	अन्यथा अणु
		/* TS discontinuity handling: */
		pr_warn("%lu: TS discontinuity: got %#x, expected %#x.\n",
			h->priv->ts_count, h->ts[3] & 0x0F,
			h->priv->tscc);
		/* Drop partly decoded SNDU, reset state, resync on PUSI. */
		अगर (h->priv->ule_skb) अणु
			dev_kमुक्त_skb(h->priv->ule_skb);
			/* Prepare क्रम next SNDU. */
			// reset_ule(h->priv);  moved to below.
			h->dev->stats.rx_errors++;
			h->dev->stats.rx_frame_errors++;
		पूर्ण
		reset_ule(h->priv);
		/* skip to next PUSI. */
		h->priv->need_pusi = 1;
		वापस 1;
	पूर्ण
	/*
	 * If we still have an incomplete payload, but PUSI is
	 * set; some TS cells are missing.
	 * This is only possible here, अगर we missed exactly 16 TS
	 * cells (continuity counter wrap).
	 */
	अगर (h->ts[1] & TS_PUSI) अणु
		अगर (!h->priv->need_pusi) अणु
			अगर (!(*h->from_where < (h->ts_reमुख्य-1)) ||
			    *h->from_where != h->priv->ule_sndu_reमुख्य) अणु
				/*
				 * Poपूर्णांकer field is invalid.
				 * Drop this TS cell and any started ULE SNDU.
				 */
				pr_warn("%lu: Invalid pointer field: %u.\n",
					h->priv->ts_count,
					*h->from_where);

				/*
				 * Drop partly decoded SNDU, reset state,
				 * resync on PUSI.
				 */
				अगर (h->priv->ule_skb) अणु
					h->error = true;
					dev_kमुक्त_skb(h->priv->ule_skb);
				पूर्ण

				अगर (h->error || h->priv->ule_sndu_reमुख्य) अणु
					h->dev->stats.rx_errors++;
					h->dev->stats.rx_frame_errors++;
					h->error = false;
				पूर्ण

				reset_ule(h->priv);
				h->priv->need_pusi = 1;
				वापस 1;
			पूर्ण
			/*
			 * Skip poपूर्णांकer field (we're processing a
			 * packed payload).
			 */
			h->from_where += 1;
			h->ts_reमुख्य -= 1;
		पूर्ण अन्यथा
			h->priv->need_pusi = 0;

		अगर (h->priv->ule_sndu_reमुख्य > 183) अणु
			/*
			 * Current SNDU lacks more data than there
			 * could be available in the current TS cell.
			 */
			h->dev->stats.rx_errors++;
			h->dev->stats.rx_length_errors++;
			pr_warn("%lu: Expected %d more SNDU bytes, but got PUSI (pf %d, h->ts_remain %d).  Flushing incomplete payload.\n",
				h->priv->ts_count,
				h->priv->ule_sndu_reमुख्य,
				h->ts[4], h->ts_reमुख्य);
			dev_kमुक्त_skb(h->priv->ule_skb);
			/* Prepare क्रम next SNDU. */
			reset_ule(h->priv);
			/*
			 * Resync: go to where poपूर्णांकer field poपूर्णांकs to:
			 * start of next ULE SNDU.
			 */
			h->from_where += h->ts[4];
			h->ts_reमुख्य -= h->ts[4];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/*
 * Start a new payload with skb.
 * Find ULE header.  It is only guaranteed that the
 * length field (2 bytes) is contained in the current
 * TS.
 * Check h.ts_reमुख्य has to be >= 2 here.
 */
अटल पूर्णांक dvb_net_ule_new_payload(काष्ठा dvb_net_ule_handle *h)
अणु
	अगर (h->ts_reमुख्य < 2) अणु
		pr_warn("Invalid payload packing: only %d bytes left in TS.  Resyncing.\n",
			h->ts_reमुख्य);
		h->priv->ule_sndu_len = 0;
		h->priv->need_pusi = 1;
		h->ts += TS_SZ;
		वापस 1;
	पूर्ण

	अगर (!h->priv->ule_sndu_len) अणु
		/* Got at least two bytes, thus extrace the SNDU length. */
		h->priv->ule_sndu_len = h->from_where[0] << 8 |
					h->from_where[1];
		अगर (h->priv->ule_sndu_len & 0x8000) अणु
			/* D-Bit is set: no dest mac present. */
			h->priv->ule_sndu_len &= 0x7FFF;
			h->priv->ule_dbit = 1;
		पूर्ण अन्यथा
			h->priv->ule_dbit = 0;

		अगर (h->priv->ule_sndu_len < 5) अणु
			pr_warn("%lu: Invalid ULE SNDU length %u. Resyncing.\n",
				h->priv->ts_count,
				h->priv->ule_sndu_len);
			h->dev->stats.rx_errors++;
			h->dev->stats.rx_length_errors++;
			h->priv->ule_sndu_len = 0;
			h->priv->need_pusi = 1;
			h->new_ts = 1;
			h->ts += TS_SZ;
			h->priv->ts_count++;
			वापस 1;
		पूर्ण
		h->ts_reमुख्य -= 2;	/* consume the 2 bytes SNDU length. */
		h->from_where += 2;
	पूर्ण

	h->priv->ule_sndu_reमुख्य = h->priv->ule_sndu_len + 2;
	/*
	 * State of current TS:
	 *   h->ts_reमुख्य (reमुख्यing bytes in the current TS cell)
	 *   0	ule_type is not available now, we need the next TS cell
	 *   1	the first byte of the ule_type is present
	 * >=2	full ULE header present, maybe some payload data as well.
	 */
	चयन (h->ts_reमुख्य) अणु
	हाल 1:
		h->priv->ule_sndu_reमुख्य--;
		h->priv->ule_sndu_type = h->from_where[0] << 8;

		/* first byte of ule_type is set. */
		h->priv->ule_sndu_type_1 = 1;
		h->ts_reमुख्य -= 1;
		h->from_where += 1;
		fallthrough;
	हाल 0:
		h->new_ts = 1;
		h->ts += TS_SZ;
		h->priv->ts_count++;
		वापस 1;

	शेष: /* complete ULE header is present in current TS. */
		/* Extract ULE type field. */
		अगर (h->priv->ule_sndu_type_1) अणु
			h->priv->ule_sndu_type_1 = 0;
			h->priv->ule_sndu_type |= h->from_where[0];
			h->from_where += 1; /* poपूर्णांकs to payload start. */
			h->ts_reमुख्य -= 1;
		पूर्ण अन्यथा अणु
			/* Complete type is present in new TS. */
			h->priv->ule_sndu_type = h->from_where[0] << 8 |
						 h->from_where[1];
			h->from_where += 2; /* poपूर्णांकs to payload start. */
			h->ts_reमुख्य -= 2;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * Allocate the skb (decoder target buffer) with the correct size,
	 * as follows:
	 *
	 * prepare क्रम the largest हाल: bridged SNDU with MAC address
	 * (dbit = 0).
	 */
	h->priv->ule_skb = dev_alloc_skb(h->priv->ule_sndu_len +
					 ETH_HLEN + ETH_ALEN);
	अगर (!h->priv->ule_skb) अणु
		pr_notice("%s: Memory squeeze, dropping packet.\n",
			  h->dev->name);
		h->dev->stats.rx_dropped++;
		वापस -1;
	पूर्ण

	/* This includes the CRC32 _and_ dest mac, अगर !dbit. */
	h->priv->ule_sndu_reमुख्य = h->priv->ule_sndu_len;
	h->priv->ule_skb->dev = h->dev;
	/*
	 * Leave space क्रम Ethernet or bridged SNDU header
	 * (eth hdr plus one MAC addr).
	 */
	skb_reserve(h->priv->ule_skb, ETH_HLEN + ETH_ALEN);

	वापस 0;
पूर्ण


अटल पूर्णांक dvb_net_ule_should_drop(काष्ठा dvb_net_ule_handle *h)
अणु
	अटल स्थिर u8 bc_addr[ETH_ALEN] = अणु [0 ... ETH_ALEN - 1] = 0xff पूर्ण;

	/*
	 * The destination MAC address is the next data in the skb.  It comes
	 * beक्रमe any extension headers.
	 *
	 * Check अगर the payload of this SNDU should be passed up the stack.
	 */
	अगर (h->priv->rx_mode == RX_MODE_PROMISC)
		वापस 0;

	अगर (h->priv->ule_skb->data[0] & 0x01) अणु
		/* multicast or broadcast */
		अगर (!ether_addr_equal(h->priv->ule_skb->data, bc_addr)) अणु
			/* multicast */
			अगर (h->priv->rx_mode == RX_MODE_MULTI) अणु
				पूर्णांक i;

				क्रम (i = 0; i < h->priv->multi_num &&
				     !ether_addr_equal(h->priv->ule_skb->data,
						       h->priv->multi_macs[i]);
				     i++)
					;
				अगर (i == h->priv->multi_num)
					वापस 1;
			पूर्ण अन्यथा अगर (h->priv->rx_mode != RX_MODE_ALL_MULTI)
				वापस 1; /* no broadcast; */
			/*
			 * अन्यथा:
			 * all multicast mode: accept all multicast packets
			 */
		पूर्ण
		/* अन्यथा: broadcast */
	पूर्ण अन्यथा अगर (!ether_addr_equal(h->priv->ule_skb->data, h->dev->dev_addr))
		वापस 1;

	वापस 0;
पूर्ण


अटल व्योम dvb_net_ule_check_crc(काष्ठा dvb_net_ule_handle *h,
				  काष्ठा kvec iov[3],
				  u32 ule_crc, u32 expected_crc)
अणु
	u8 dest_addr[ETH_ALEN];

	अगर (ule_crc != expected_crc) अणु
		pr_warn("%lu: CRC32 check FAILED: %08x / %08x, SNDU len %d type %#x, ts_remain %d, next 2: %x.\n",
			h->priv->ts_count, ule_crc, expected_crc,
			h->priv->ule_sndu_len, h->priv->ule_sndu_type,
			h->ts_reमुख्य,
			h->ts_reमुख्य > 2 ?
				*(अचिन्हित लघु *)h->from_where : 0);

	#अगर_घोषित DVB_ULE_DEBUG
		hexdump(iov[0].iov_base, iov[0].iov_len);
		hexdump(iov[1].iov_base, iov[1].iov_len);
		hexdump(iov[2].iov_base, iov[2].iov_len);

		अगर (ule_where == ule_hist) अणु
			hexdump(&ule_hist[98*TS_SZ], TS_SZ);
			hexdump(&ule_hist[99*TS_SZ], TS_SZ);
		पूर्ण अन्यथा अगर (ule_where == &ule_hist[TS_SZ]) अणु
			hexdump(&ule_hist[99*TS_SZ], TS_SZ);
			hexdump(ule_hist, TS_SZ);
		पूर्ण अन्यथा अणु
			hexdump(ule_where - TS_SZ - TS_SZ, TS_SZ);
			hexdump(ule_where - TS_SZ, TS_SZ);
		पूर्ण
		ule_dump = 1;
	#पूर्ण_अगर

		h->dev->stats.rx_errors++;
		h->dev->stats.rx_crc_errors++;
		dev_kमुक्त_skb(h->priv->ule_skb);

		वापस;
	पूर्ण

	/* CRC32 verअगरied OK. */

	/* CRC32 was OK, so हटाओ it from skb. */
	h->priv->ule_skb->tail -= 4;
	h->priv->ule_skb->len -= 4;

	अगर (!h->priv->ule_dbit) अणु
		अगर (dvb_net_ule_should_drop(h)) अणु
			netdev_dbg(h->dev,
				   "Dropping SNDU: MAC destination address does not match: dest addr: %pM, h->dev addr: %pM\n",
				   h->priv->ule_skb->data, h->dev->dev_addr);
			dev_kमुक्त_skb(h->priv->ule_skb);
			वापस;
		पूर्ण

		skb_copy_from_linear_data(h->priv->ule_skb, dest_addr,
					  ETH_ALEN);
		skb_pull(h->priv->ule_skb, ETH_ALEN);
	पूर्ण अन्यथा अणु
		/* dest_addr buffer is only valid अगर h->priv->ule_dbit == 0 */
		eth_zero_addr(dest_addr);
	पूर्ण

	/* Handle ULE Extension Headers. */
	अगर (h->priv->ule_sndu_type < ETH_P_802_3_MIN) अणु
		/* There is an extension header.  Handle it accordingly. */
		पूर्णांक l = handle_ule_extensions(h->priv);

		अगर (l < 0) अणु
			/*
			 * Mandatory extension header unknown or TEST SNDU.
			 * Drop it.
			 */

			// pr_warn("Dropping SNDU, extension headers.\n" );
			dev_kमुक्त_skb(h->priv->ule_skb);
			वापस;
		पूर्ण
		skb_pull(h->priv->ule_skb, l);
	पूर्ण

	/*
	 * Conकाष्ठा/assure correct ethernet header.
	 * Note: in bridged mode (h->priv->ule_bridged != 0)
	 * we alपढ़ोy have the (original) ethernet
	 * header at the start of the payload (after
	 * optional dest. address and any extension
	 * headers).
	 */
	अगर (!h->priv->ule_bridged) अणु
		skb_push(h->priv->ule_skb, ETH_HLEN);
		h->ethh = (काष्ठा ethhdr *)h->priv->ule_skb->data;
		स_नकल(h->ethh->h_dest, dest_addr, ETH_ALEN);
		eth_zero_addr(h->ethh->h_source);
		h->ethh->h_proto = htons(h->priv->ule_sndu_type);
	पूर्ण
	/* अन्यथा:  skb is in correct state; nothing to करो. */
	h->priv->ule_bridged = 0;

	/* Stuff पूर्णांकo kernel's protocol stack. */
	h->priv->ule_skb->protocol = dvb_net_eth_type_trans(h->priv->ule_skb,
							   h->dev);
	/*
	 * If D-bit is set (i.e. destination MAC address not present),
	 * receive the packet anyhow.
	 */
#अगर 0
	अगर (h->priv->ule_dbit && skb->pkt_type == PACKET_OTHERHOST)
		h->priv->ule_skb->pkt_type = PACKET_HOST;
#पूर्ण_अगर
	h->dev->stats.rx_packets++;
	h->dev->stats.rx_bytes += h->priv->ule_skb->len;
	netअगर_rx(h->priv->ule_skb);
पूर्ण

अटल व्योम dvb_net_ule(काष्ठा net_device *dev, स्थिर u8 *buf, माप_प्रकार buf_len)
अणु
	पूर्णांक ret;
	काष्ठा dvb_net_ule_handle h = अणु
		.dev = dev,
		.priv = netdev_priv(dev),
		.ethh = शून्य,
		.buf = buf,
		.buf_len = buf_len,
		.skipped = 0L,
		.ts = शून्य,
		.ts_end = शून्य,
		.from_where = शून्य,
		.ts_reमुख्य = 0,
		.how_much = 0,
		.new_ts = 1,
		.error = false,
	पूर्ण;

	/*
	 * For all TS cells in current buffer.
	 * Appearently, we are called क्रम every single TS cell.
	 */
	क्रम (h.ts = h.buf, h.ts_end = h.buf + h.buf_len;
	     h.ts < h.ts_end; /* no incr. */) अणु
		अगर (h.new_ts) अणु
			/* We are about to process a new TS cell. */
			अगर (dvb_net_ule_new_ts_cell(&h))
				जारी;
		पूर्ण

		/* Synchronize on PUSI, अगर required. */
		अगर (h.priv->need_pusi) अणु
			अगर (dvb_net_ule_ts_pusi(&h))
				जारी;
		पूर्ण

		अगर (h.new_ts) अणु
			अगर (dvb_net_ule_new_ts(&h))
				जारी;
		पूर्ण

		/* Check अगर new payload needs to be started. */
		अगर (h.priv->ule_skb == शून्य) अणु
			ret = dvb_net_ule_new_payload(&h);
			अगर (ret < 0)
				वापस;
			अगर (ret)
				जारी;
		पूर्ण

		/* Copy data पूर्णांकo our current skb. */
		h.how_much = min(h.priv->ule_sndu_reमुख्य, (पूर्णांक)h.ts_reमुख्य);
		skb_put_data(h.priv->ule_skb, h.from_where, h.how_much);
		h.priv->ule_sndu_reमुख्य -= h.how_much;
		h.ts_reमुख्य -= h.how_much;
		h.from_where += h.how_much;

		/* Check क्रम complete payload. */
		अगर (h.priv->ule_sndu_reमुख्य <= 0) अणु
			/* Check CRC32, we've got it in our skb alपढ़ोy. */
			__be16 ulen = htons(h.priv->ule_sndu_len);
			__be16 utype = htons(h.priv->ule_sndu_type);
			स्थिर u8 *tail;
			काष्ठा kvec iov[3] = अणु
				अणु &ulen, माप ulen पूर्ण,
				अणु &utype, माप utype पूर्ण,
				अणु h.priv->ule_skb->data,
				  h.priv->ule_skb->len - 4 पूर्ण
			पूर्ण;
			u32 ule_crc = ~0L, expected_crc;
			अगर (h.priv->ule_dbit) अणु
				/* Set D-bit क्रम CRC32 verअगरication,
				 * अगर it was set originally. */
				ulen |= htons(0x8000);
			पूर्ण

			ule_crc = iov_crc32(ule_crc, iov, 3);
			tail = skb_tail_poपूर्णांकer(h.priv->ule_skb);
			expected_crc = *(tail - 4) << 24 |
				       *(tail - 3) << 16 |
				       *(tail - 2) << 8 |
				       *(tail - 1);

			dvb_net_ule_check_crc(&h, iov, ule_crc, expected_crc);

			/* Prepare क्रम next SNDU. */
			reset_ule(h.priv);
		पूर्ण

		/* More data in current TS (look at the bytes following the CRC32)? */
		अगर (h.ts_reमुख्य >= 2 && *((अचिन्हित लघु *)h.from_where) != 0xFFFF) अणु
			/* Next ULE SNDU starts right there. */
			h.new_ts = 0;
			h.priv->ule_skb = शून्य;
			h.priv->ule_sndu_type_1 = 0;
			h.priv->ule_sndu_len = 0;
			// pr_warn("More data in current TS: [%#x %#x %#x %#x]\n",
			//	*(h.from_where + 0), *(h.from_where + 1),
			//	*(h.from_where + 2), *(h.from_where + 3));
			// pr_warn("h.ts @ %p, stopped @ %p:\n", h.ts, h.from_where + 0);
			// hexdump(h.ts, 188);
		पूर्ण अन्यथा अणु
			h.new_ts = 1;
			h.ts += TS_SZ;
			h.priv->ts_count++;
			अगर (h.priv->ule_skb == शून्य) अणु
				h.priv->need_pusi = 1;
				h.priv->ule_sndu_type_1 = 0;
				h.priv->ule_sndu_len = 0;
			पूर्ण
		पूर्ण
	पूर्ण	/* क्रम all available TS cells */
पूर्ण

अटल पूर्णांक dvb_net_ts_callback(स्थिर u8 *buffer1, माप_प्रकार buffer1_len,
			       स्थिर u8 *buffer2, माप_प्रकार buffer2_len,
			       काष्ठा dmx_ts_feed *feed,
			       u32 *buffer_flags)
अणु
	काष्ठा net_device *dev = feed->priv;

	अगर (buffer2)
		pr_warn("buffer2 not NULL: %p.\n", buffer2);
	अगर (buffer1_len > 32768)
		pr_warn("length > 32k: %zu.\n", buffer1_len);
	/* pr_info("TS callback: %u bytes, %u TS cells @ %p.\n",
		  buffer1_len, buffer1_len / TS_SZ, buffer1); */
	dvb_net_ule(dev, buffer1, buffer1_len);
	वापस 0;
पूर्ण


अटल व्योम dvb_net_sec(काष्ठा net_device *dev,
			स्थिर u8 *pkt, पूर्णांक pkt_len)
अणु
	u8 *eth;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats = &dev->stats;
	पूर्णांक snap = 0;

	/* note: pkt_len includes a 32bit checksum */
	अगर (pkt_len < 16) अणु
		pr_warn("%s: IP/MPE packet length = %d too small.\n",
			dev->name, pkt_len);
		stats->rx_errors++;
		stats->rx_length_errors++;
		वापस;
	पूर्ण
/* it seems some ISPs manage to screw up here, so we have to
 * relax the error checks... */
#अगर 0
	अगर ((pkt[5] & 0xfd) != 0xc1) अणु
		/* drop scrambled or broken packets */
#अन्यथा
	अगर ((pkt[5] & 0x3c) != 0x00) अणु
		/* drop scrambled */
#पूर्ण_अगर
		stats->rx_errors++;
		stats->rx_crc_errors++;
		वापस;
	पूर्ण
	अगर (pkt[5] & 0x02) अणु
		/* handle LLC/SNAP, see rfc-1042 */
		अगर (pkt_len < 24 || स_भेद(&pkt[12], "\xaa\xaa\x03\0\0\0", 6)) अणु
			stats->rx_dropped++;
			वापस;
		पूर्ण
		snap = 8;
	पूर्ण
	अगर (pkt[7]) अणु
		/* FIXME: assemble datagram from multiple sections */
		stats->rx_errors++;
		stats->rx_frame_errors++;
		वापस;
	पूर्ण

	/* we have 14 byte ethernet header (ip header follows);
	 * 12 byte MPE header; 4 byte checksum; + 2 byte alignment, 8 byte LLC/SNAP
	 */
	अगर (!(skb = dev_alloc_skb(pkt_len - 4 - 12 + 14 + 2 - snap))) अणु
		//pr_notice("%s: Memory squeeze, dropping packet.\n", dev->name);
		stats->rx_dropped++;
		वापस;
	पूर्ण
	skb_reserve(skb, 2);    /* दीर्घword align L3 header */
	skb->dev = dev;

	/* copy L3 payload */
	eth = skb_put(skb, pkt_len - 12 - 4 + 14 - snap);
	स_नकल(eth + 14, pkt + 12 + snap, pkt_len - 12 - 4 - snap);

	/* create ethernet header: */
	eth[0]=pkt[0x0b];
	eth[1]=pkt[0x0a];
	eth[2]=pkt[0x09];
	eth[3]=pkt[0x08];
	eth[4]=pkt[0x04];
	eth[5]=pkt[0x03];

	eth[6]=eth[7]=eth[8]=eth[9]=eth[10]=eth[11]=0;

	अगर (snap) अणु
		eth[12] = pkt[18];
		eth[13] = pkt[19];
	पूर्ण अन्यथा अणु
		/* protocol numbers are from rfc-1700 or
		 * http://www.iana.org/assignments/ethernet-numbers
		 */
		अगर (pkt[12] >> 4 == 6) अणु /* version field from IP header */
			eth[12] = 0x86;	/* IPv6 */
			eth[13] = 0xdd;
		पूर्ण अन्यथा अणु
			eth[12] = 0x08;	/* IPv4 */
			eth[13] = 0x00;
		पूर्ण
	पूर्ण

	skb->protocol = dvb_net_eth_type_trans(skb, dev);

	stats->rx_packets++;
	stats->rx_bytes+=skb->len;
	netअगर_rx(skb);
पूर्ण

अटल पूर्णांक dvb_net_sec_callback(स्थिर u8 *buffer1, माप_प्रकार buffer1_len,
		 स्थिर u8 *buffer2, माप_प्रकार buffer2_len,
		 काष्ठा dmx_section_filter *filter, u32 *buffer_flags)
अणु
	काष्ठा net_device *dev = filter->priv;

	/*
	 * we rely on the DVB API definition where exactly one complete
	 * section is delivered in buffer1
	 */
	dvb_net_sec (dev, buffer1, buffer1_len);
	वापस 0;
पूर्ण

अटल netdev_tx_t dvb_net_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल u8 mask_normal[6]=अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
अटल u8 mask_allmulti[6]=अणु0xff, 0xff, 0xff, 0x00, 0x00, 0x00पूर्ण;
अटल u8 mac_allmulti[6]=अणु0x01, 0x00, 0x5e, 0x00, 0x00, 0x00पूर्ण;
अटल u8 mask_promisc[6]=अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;

अटल पूर्णांक dvb_net_filter_sec_set(काष्ठा net_device *dev,
		   काष्ठा dmx_section_filter **secfilter,
		   u8 *mac, u8 *mac_mask)
अणु
	काष्ठा dvb_net_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	*secfilter=शून्य;
	ret = priv->secfeed->allocate_filter(priv->secfeed, secfilter);
	अगर (ret<0) अणु
		pr_err("%s: could not get filter\n", dev->name);
		वापस ret;
	पूर्ण

	(*secfilter)->priv=(व्योम *) dev;

	स_रखो((*secfilter)->filter_value, 0x00, DMX_MAX_FILTER_SIZE);
	स_रखो((*secfilter)->filter_mask,  0x00, DMX_MAX_FILTER_SIZE);
	स_रखो((*secfilter)->filter_mode,  0xff, DMX_MAX_FILTER_SIZE);

	(*secfilter)->filter_value[0]=0x3e;
	(*secfilter)->filter_value[3]=mac[5];
	(*secfilter)->filter_value[4]=mac[4];
	(*secfilter)->filter_value[8]=mac[3];
	(*secfilter)->filter_value[9]=mac[2];
	(*secfilter)->filter_value[10]=mac[1];
	(*secfilter)->filter_value[11]=mac[0];

	(*secfilter)->filter_mask[0] = 0xff;
	(*secfilter)->filter_mask[3] = mac_mask[5];
	(*secfilter)->filter_mask[4] = mac_mask[4];
	(*secfilter)->filter_mask[8] = mac_mask[3];
	(*secfilter)->filter_mask[9] = mac_mask[2];
	(*secfilter)->filter_mask[10] = mac_mask[1];
	(*secfilter)->filter_mask[11]=mac_mask[0];

	netdev_dbg(dev, "filter mac=%pM mask=%pM\n", mac, mac_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_net_feed_start(काष्ठा net_device *dev)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा dvb_net_priv *priv = netdev_priv(dev);
	काष्ठा dmx_demux *demux = priv->demux;
	अचिन्हित अक्षर *mac = (अचिन्हित अक्षर *) dev->dev_addr;

	netdev_dbg(dev, "rx_mode %i\n", priv->rx_mode);
	mutex_lock(&priv->mutex);
	अगर (priv->tsfeed || priv->secfeed || priv->secfilter || priv->multi_secfilter[0])
		pr_err("%s: BUG %d\n", __func__, __LINE__);

	priv->secfeed=शून्य;
	priv->secfilter=शून्य;
	priv->tsfeed = शून्य;

	अगर (priv->feedtype == DVB_NET_FEEDTYPE_MPE) अणु
		netdev_dbg(dev, "alloc secfeed\n");
		ret=demux->allocate_section_feed(demux, &priv->secfeed,
					 dvb_net_sec_callback);
		अगर (ret<0) अणु
			pr_err("%s: could not allocate section feed\n",
			       dev->name);
			जाओ error;
		पूर्ण

		ret = priv->secfeed->set(priv->secfeed, priv->pid, 1);

		अगर (ret<0) अणु
			pr_err("%s: could not set section feed\n", dev->name);
			priv->demux->release_section_feed(priv->demux, priv->secfeed);
			priv->secfeed=शून्य;
			जाओ error;
		पूर्ण

		अगर (priv->rx_mode != RX_MODE_PROMISC) अणु
			netdev_dbg(dev, "set secfilter\n");
			dvb_net_filter_sec_set(dev, &priv->secfilter, mac, mask_normal);
		पूर्ण

		चयन (priv->rx_mode) अणु
		हाल RX_MODE_MULTI:
			क्रम (i = 0; i < priv->multi_num; i++) अणु
				netdev_dbg(dev, "set multi_secfilter[%d]\n", i);
				dvb_net_filter_sec_set(dev, &priv->multi_secfilter[i],
						       priv->multi_macs[i], mask_normal);
			पूर्ण
			अवरोध;
		हाल RX_MODE_ALL_MULTI:
			priv->multi_num=1;
			netdev_dbg(dev, "set multi_secfilter[0]\n");
			dvb_net_filter_sec_set(dev, &priv->multi_secfilter[0],
					       mac_allmulti, mask_allmulti);
			अवरोध;
		हाल RX_MODE_PROMISC:
			priv->multi_num=0;
			netdev_dbg(dev, "set secfilter\n");
			dvb_net_filter_sec_set(dev, &priv->secfilter, mac, mask_promisc);
			अवरोध;
		पूर्ण

		netdev_dbg(dev, "start filtering\n");
		priv->secfeed->start_filtering(priv->secfeed);
	पूर्ण अन्यथा अगर (priv->feedtype == DVB_NET_FEEDTYPE_ULE) अणु
		kसमय_प्रकार समयout = ns_to_kसमय(10 * NSEC_PER_MSEC);

		/* we have payloads encapsulated in TS */
		netdev_dbg(dev, "alloc tsfeed\n");
		ret = demux->allocate_ts_feed(demux, &priv->tsfeed, dvb_net_ts_callback);
		अगर (ret < 0) अणु
			pr_err("%s: could not allocate ts feed\n", dev->name);
			जाओ error;
		पूर्ण

		/* Set netdevice poपूर्णांकer क्रम ts decaps callback. */
		priv->tsfeed->priv = (व्योम *)dev;
		ret = priv->tsfeed->set(priv->tsfeed,
					priv->pid, /* pid */
					TS_PACKET, /* type */
					DMX_PES_OTHER, /* pes type */
					समयout    /* समयout */
					);

		अगर (ret < 0) अणु
			pr_err("%s: could not set ts feed\n", dev->name);
			priv->demux->release_ts_feed(priv->demux, priv->tsfeed);
			priv->tsfeed = शून्य;
			जाओ error;
		पूर्ण

		netdev_dbg(dev, "start filtering\n");
		priv->tsfeed->start_filtering(priv->tsfeed);
	पूर्ण अन्यथा
		ret = -EINVAL;

error:
	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_net_feed_stop(काष्ठा net_device *dev)
अणु
	काष्ठा dvb_net_priv *priv = netdev_priv(dev);
	पूर्णांक i, ret = 0;

	mutex_lock(&priv->mutex);
	अगर (priv->feedtype == DVB_NET_FEEDTYPE_MPE) अणु
		अगर (priv->secfeed) अणु
			अगर (priv->secfeed->is_filtering) अणु
				netdev_dbg(dev, "stop secfeed\n");
				priv->secfeed->stop_filtering(priv->secfeed);
			पूर्ण

			अगर (priv->secfilter) अणु
				netdev_dbg(dev, "release secfilter\n");
				priv->secfeed->release_filter(priv->secfeed,
							      priv->secfilter);
				priv->secfilter=शून्य;
			पूर्ण

			क्रम (i=0; i<priv->multi_num; i++) अणु
				अगर (priv->multi_secfilter[i]) अणु
					netdev_dbg(dev, "release multi_filter[%d]\n",
						   i);
					priv->secfeed->release_filter(priv->secfeed,
								      priv->multi_secfilter[i]);
					priv->multi_secfilter[i] = शून्य;
				पूर्ण
			पूर्ण

			priv->demux->release_section_feed(priv->demux, priv->secfeed);
			priv->secfeed = शून्य;
		पूर्ण अन्यथा
			pr_err("%s: no feed to stop\n", dev->name);
	पूर्ण अन्यथा अगर (priv->feedtype == DVB_NET_FEEDTYPE_ULE) अणु
		अगर (priv->tsfeed) अणु
			अगर (priv->tsfeed->is_filtering) अणु
				netdev_dbg(dev, "stop tsfeed\n");
				priv->tsfeed->stop_filtering(priv->tsfeed);
			पूर्ण
			priv->demux->release_ts_feed(priv->demux, priv->tsfeed);
			priv->tsfeed = शून्य;
		पूर्ण
		अन्यथा
			pr_err("%s: no ts feed to stop\n", dev->name);
	पूर्ण अन्यथा
		ret = -EINVAL;
	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण


अटल पूर्णांक dvb_set_mc_filter(काष्ठा net_device *dev, अचिन्हित अक्षर *addr)
अणु
	काष्ठा dvb_net_priv *priv = netdev_priv(dev);

	अगर (priv->multi_num == DVB_NET_MULTICAST_MAX)
		वापस -ENOMEM;

	स_नकल(priv->multi_macs[priv->multi_num], addr, ETH_ALEN);

	priv->multi_num++;
	वापस 0;
पूर्ण


अटल व्योम wq_set_multicast_list (काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dvb_net_priv *priv =
		container_of(work, काष्ठा dvb_net_priv, set_multicast_list_wq);
	काष्ठा net_device *dev = priv->net;

	dvb_net_feed_stop(dev);
	priv->rx_mode = RX_MODE_UNI;
	netअगर_addr_lock_bh(dev);

	अगर (dev->flags & IFF_PROMISC) अणु
		netdev_dbg(dev, "promiscuous mode\n");
		priv->rx_mode = RX_MODE_PROMISC;
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI)) अणु
		netdev_dbg(dev, "allmulti mode\n");
		priv->rx_mode = RX_MODE_ALL_MULTI;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;

		netdev_dbg(dev, "set_mc_list, %d entries\n",
			   netdev_mc_count(dev));

		priv->rx_mode = RX_MODE_MULTI;
		priv->multi_num = 0;

		netdev_क्रम_each_mc_addr(ha, dev)
			dvb_set_mc_filter(dev, ha->addr);
	पूर्ण

	netअगर_addr_unlock_bh(dev);
	dvb_net_feed_start(dev);
पूर्ण


अटल व्योम dvb_net_set_multicast_list (काष्ठा net_device *dev)
अणु
	काष्ठा dvb_net_priv *priv = netdev_priv(dev);
	schedule_work(&priv->set_multicast_list_wq);
पूर्ण


अटल व्योम wq_restart_net_feed (काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dvb_net_priv *priv =
		container_of(work, काष्ठा dvb_net_priv, restart_net_feed_wq);
	काष्ठा net_device *dev = priv->net;

	अगर (netअगर_running(dev)) अणु
		dvb_net_feed_stop(dev);
		dvb_net_feed_start(dev);
	पूर्ण
पूर्ण


अटल पूर्णांक dvb_net_set_mac (काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा dvb_net_priv *priv = netdev_priv(dev);
	काष्ठा sockaddr *addr=p;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	अगर (netअगर_running(dev))
		schedule_work(&priv->restart_net_feed_wq);

	वापस 0;
पूर्ण


अटल पूर्णांक dvb_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा dvb_net_priv *priv = netdev_priv(dev);

	priv->in_use++;
	dvb_net_feed_start(dev);
	वापस 0;
पूर्ण


अटल पूर्णांक dvb_net_stop(काष्ठा net_device *dev)
अणु
	काष्ठा dvb_net_priv *priv = netdev_priv(dev);

	priv->in_use--;
	वापस dvb_net_feed_stop(dev);
पूर्ण

अटल स्थिर काष्ठा header_ops dvb_header_ops = अणु
	.create		= eth_header,
	.parse		= eth_header_parse,
पूर्ण;


अटल स्थिर काष्ठा net_device_ops dvb_netdev_ops = अणु
	.nकरो_खोलो		= dvb_net_खोलो,
	.nकरो_stop		= dvb_net_stop,
	.nकरो_start_xmit		= dvb_net_tx,
	.nकरो_set_rx_mode	= dvb_net_set_multicast_list,
	.nकरो_set_mac_address    = dvb_net_set_mac,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल व्योम dvb_net_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	dev->header_ops		= &dvb_header_ops;
	dev->netdev_ops		= &dvb_netdev_ops;
	dev->mtu		= 4096;
	dev->max_mtu		= 4096;

	dev->flags |= IFF_NOARP;
पूर्ण

अटल पूर्णांक get_अगर(काष्ठा dvb_net *dvbnet)
अणु
	पूर्णांक i;

	क्रम (i=0; i<DVB_NET_DEVICES_MAX; i++)
		अगर (!dvbnet->state[i])
			अवरोध;

	अगर (i == DVB_NET_DEVICES_MAX)
		वापस -1;

	dvbnet->state[i]=1;
	वापस i;
पूर्ण

अटल पूर्णांक dvb_net_add_अगर(काष्ठा dvb_net *dvbnet, u16 pid, u8 feedtype)
अणु
	काष्ठा net_device *net;
	काष्ठा dvb_net_priv *priv;
	पूर्णांक result;
	पूर्णांक अगर_num;

	अगर (feedtype != DVB_NET_FEEDTYPE_MPE && feedtype != DVB_NET_FEEDTYPE_ULE)
		वापस -EINVAL;
	अगर ((अगर_num = get_अगर(dvbnet)) < 0)
		वापस -EINVAL;

	net = alloc_netdev(माप(काष्ठा dvb_net_priv), "dvb",
			   NET_NAME_UNKNOWN, dvb_net_setup);
	अगर (!net)
		वापस -ENOMEM;

	अगर (dvbnet->dvbdev->id)
		snम_लिखो(net->name, IFNAMSIZ, "dvb%d%u%d",
			 dvbnet->dvbdev->adapter->num, dvbnet->dvbdev->id, अगर_num);
	अन्यथा
		/* compatibility fix to keep dvb0_0 क्रमmat */
		snम_लिखो(net->name, IFNAMSIZ, "dvb%d_%d",
			 dvbnet->dvbdev->adapter->num, अगर_num);

	net->addr_len = 6;
	स_नकल(net->dev_addr, dvbnet->dvbdev->adapter->proposed_mac, 6);

	dvbnet->device[अगर_num] = net;

	priv = netdev_priv(net);
	priv->net = net;
	priv->demux = dvbnet->demux;
	priv->pid = pid;
	priv->rx_mode = RX_MODE_UNI;
	priv->need_pusi = 1;
	priv->tscc = 0;
	priv->feedtype = feedtype;
	reset_ule(priv);

	INIT_WORK(&priv->set_multicast_list_wq, wq_set_multicast_list);
	INIT_WORK(&priv->restart_net_feed_wq, wq_restart_net_feed);
	mutex_init(&priv->mutex);

	net->base_addr = pid;

	अगर ((result = रेजिस्टर_netdev(net)) < 0) अणु
		dvbnet->device[अगर_num] = शून्य;
		मुक्त_netdev(net);
		वापस result;
	पूर्ण
	pr_info("created network interface %s\n", net->name);

	वापस अगर_num;
पूर्ण

अटल पूर्णांक dvb_net_हटाओ_अगर(काष्ठा dvb_net *dvbnet, अचिन्हित दीर्घ num)
अणु
	काष्ठा net_device *net = dvbnet->device[num];
	काष्ठा dvb_net_priv *priv;

	अगर (!dvbnet->state[num])
		वापस -EINVAL;
	priv = netdev_priv(net);
	अगर (priv->in_use)
		वापस -EBUSY;

	dvb_net_stop(net);
	flush_work(&priv->set_multicast_list_wq);
	flush_work(&priv->restart_net_feed_wq);
	pr_info("removed network interface %s\n", net->name);
	unरेजिस्टर_netdev(net);
	dvbnet->state[num]=0;
	dvbnet->device[num] = शून्य;
	मुक्त_netdev(net);

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_net_करो_ioctl(काष्ठा file *file,
		  अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_net *dvbnet = dvbdev->priv;
	पूर्णांक ret = 0;

	अगर (((file->f_flags&O_ACCMODE)==O_RDONLY))
		वापस -EPERM;

	अगर (mutex_lock_पूर्णांकerruptible(&dvbnet->ioctl_mutex))
		वापस -ERESTARTSYS;

	चयन (cmd) अणु
	हाल NET_ADD_IF:
	अणु
		काष्ठा dvb_net_अगर *dvbnetअगर = parg;
		पूर्णांक result;

		अगर (!capable(CAP_SYS_ADMIN)) अणु
			ret = -EPERM;
			जाओ ioctl_error;
		पूर्ण

		अगर (!try_module_get(dvbdev->adapter->module)) अणु
			ret = -EPERM;
			जाओ ioctl_error;
		पूर्ण

		result=dvb_net_add_अगर(dvbnet, dvbnetअगर->pid, dvbnetअगर->feedtype);
		अगर (result<0) अणु
			module_put(dvbdev->adapter->module);
			ret = result;
			जाओ ioctl_error;
		पूर्ण
		dvbnetअगर->अगर_num=result;
		अवरोध;
	पूर्ण
	हाल NET_GET_IF:
	अणु
		काष्ठा net_device *netdev;
		काष्ठा dvb_net_priv *priv_data;
		काष्ठा dvb_net_अगर *dvbnetअगर = parg;

		अगर (dvbnetअगर->अगर_num >= DVB_NET_DEVICES_MAX ||
		    !dvbnet->state[dvbnetअगर->अगर_num]) अणु
			ret = -EINVAL;
			जाओ ioctl_error;
		पूर्ण

		netdev = dvbnet->device[dvbnetअगर->अगर_num];

		priv_data = netdev_priv(netdev);
		dvbnetअगर->pid=priv_data->pid;
		dvbnetअगर->feedtype=priv_data->feedtype;
		अवरोध;
	पूर्ण
	हाल NET_REMOVE_IF:
	अणु
		अगर (!capable(CAP_SYS_ADMIN)) अणु
			ret = -EPERM;
			जाओ ioctl_error;
		पूर्ण
		अगर ((अचिन्हित दीर्घ) parg >= DVB_NET_DEVICES_MAX) अणु
			ret = -EINVAL;
			जाओ ioctl_error;
		पूर्ण
		ret = dvb_net_हटाओ_अगर(dvbnet, (अचिन्हित दीर्घ) parg);
		अगर (!ret)
			module_put(dvbdev->adapter->module);
		अवरोध;
	पूर्ण

	/* binary compatibility cruft */
	हाल __NET_ADD_IF_OLD:
	अणु
		काष्ठा __dvb_net_अगर_old *dvbnetअगर = parg;
		पूर्णांक result;

		अगर (!capable(CAP_SYS_ADMIN)) अणु
			ret = -EPERM;
			जाओ ioctl_error;
		पूर्ण

		अगर (!try_module_get(dvbdev->adapter->module)) अणु
			ret = -EPERM;
			जाओ ioctl_error;
		पूर्ण

		result=dvb_net_add_अगर(dvbnet, dvbnetअगर->pid, DVB_NET_FEEDTYPE_MPE);
		अगर (result<0) अणु
			module_put(dvbdev->adapter->module);
			ret = result;
			जाओ ioctl_error;
		पूर्ण
		dvbnetअगर->अगर_num=result;
		अवरोध;
	पूर्ण
	हाल __NET_GET_IF_OLD:
	अणु
		काष्ठा net_device *netdev;
		काष्ठा dvb_net_priv *priv_data;
		काष्ठा __dvb_net_अगर_old *dvbnetअगर = parg;

		अगर (dvbnetअगर->अगर_num >= DVB_NET_DEVICES_MAX ||
		    !dvbnet->state[dvbnetअगर->अगर_num]) अणु
			ret = -EINVAL;
			जाओ ioctl_error;
		पूर्ण

		netdev = dvbnet->device[dvbnetअगर->अगर_num];

		priv_data = netdev_priv(netdev);
		dvbnetअगर->pid=priv_data->pid;
		अवरोध;
	पूर्ण
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण

ioctl_error:
	mutex_unlock(&dvbnet->ioctl_mutex);
	वापस ret;
पूर्ण

अटल दीर्घ dvb_net_ioctl(काष्ठा file *file,
	      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस dvb_usercopy(file, cmd, arg, dvb_net_करो_ioctl);
पूर्ण

अटल पूर्णांक dvb_net_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_net *dvbnet = dvbdev->priv;

	dvb_generic_release(inode, file);

	अगर(dvbdev->users == 1 && dvbnet->निकास == 1)
		wake_up(&dvbdev->रुको_queue);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations dvb_net_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = dvb_net_ioctl,
	.खोलो =	dvb_generic_खोलो,
	.release = dvb_net_बंद,
	.llseek = noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा dvb_device dvbdev_net = अणु
	.priv = शून्य,
	.users = 1,
	.ग_लिखोrs = 1,
#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-net",
#पूर्ण_अगर
	.fops = &dvb_net_fops,
पूर्ण;

व्योम dvb_net_release (काष्ठा dvb_net *dvbnet)
अणु
	पूर्णांक i;

	dvbnet->निकास = 1;
	अगर (dvbnet->dvbdev->users < 1)
		रुको_event(dvbnet->dvbdev->रुको_queue,
				dvbnet->dvbdev->users==1);

	dvb_unरेजिस्टर_device(dvbnet->dvbdev);

	क्रम (i=0; i<DVB_NET_DEVICES_MAX; i++) अणु
		अगर (!dvbnet->state[i])
			जारी;
		dvb_net_हटाओ_अगर(dvbnet, i);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dvb_net_release);


पूर्णांक dvb_net_init (काष्ठा dvb_adapter *adap, काष्ठा dvb_net *dvbnet,
		  काष्ठा dmx_demux *dmx)
अणु
	पूर्णांक i;

	mutex_init(&dvbnet->ioctl_mutex);
	dvbnet->demux = dmx;

	क्रम (i=0; i<DVB_NET_DEVICES_MAX; i++)
		dvbnet->state[i] = 0;

	वापस dvb_रेजिस्टर_device(adap, &dvbnet->dvbdev, &dvbdev_net,
			     dvbnet, DVB_DEVICE_NET, 0);
पूर्ण
EXPORT_SYMBOL(dvb_net_init);
