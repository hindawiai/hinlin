<शैली गुरु>
/*
 * dvb_demux.c - DVB kernel demux API
 *
 * Copyright (C) 2000-2001 Ralph  Metzler <ralph@convergence.de>
 *		       & Marcus Metzler <marcus@convergence.de>
 *			 क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#घोषणा pr_fmt(fmt) "dvb_demux: " fmt

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/माला.स>
#समावेश <linux/crc32.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_demux.h>

अटल पूर्णांक dvb_demux_tscheck;
module_param(dvb_demux_tscheck, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_demux_tscheck,
		"enable transport stream continuity and TEI check");

अटल पूर्णांक dvb_demux_speedcheck;
module_param(dvb_demux_speedcheck, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_demux_speedcheck,
		"enable transport stream speed check");

अटल पूर्णांक dvb_demux_feed_err_pkts = 1;
module_param(dvb_demux_feed_err_pkts, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_demux_feed_err_pkts,
		 "when set to 0, drop packets with the TEI bit set (1 by default)");

#घोषणा dprपूर्णांकk(fmt, arg...) \
	prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),  __func__, ##arg)

#घोषणा dprपूर्णांकk_tscheck(x...) करो अणु			\
	अगर (dvb_demux_tscheck && prपूर्णांकk_ratelimit())	\
		dprपूर्णांकk(x);				\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_DVB_DEMUX_SECTION_LOSS_LOG
#  define dprपूर्णांकk_sect_loss(x...) dprपूर्णांकk(x)
#अन्यथा
#  define dprपूर्णांकk_sect_loss(x...)
#पूर्ण_अगर

#घोषणा set_buf_flags(__feed, __flag)			\
	करो अणु						\
		(__feed)->buffer_flags |= (__flag);	\
	पूर्ण जबतक (0)

/******************************************************************************
 * अटल अंतरभूतd helper functions
 ******************************************************************************/

अटल अंतरभूत u16 section_length(स्थिर u8 *buf)
अणु
	वापस 3 + ((buf[1] & 0x0f) << 8) + buf[2];
पूर्ण

अटल अंतरभूत u16 ts_pid(स्थिर u8 *buf)
अणु
	वापस ((buf[1] & 0x1f) << 8) + buf[2];
पूर्ण

अटल अंतरभूत u8 payload(स्थिर u8 *tsp)
अणु
	अगर (!(tsp[3] & 0x10))	// no payload?
		वापस 0;

	अगर (tsp[3] & 0x20) अणु	// adaptation field?
		अगर (tsp[4] > 183)	// corrupted data?
			वापस 0;
		अन्यथा
			वापस 184 - 1 - tsp[4];
	पूर्ण

	वापस 184;
पूर्ण

अटल u32 dvb_dmx_crc32(काष्ठा dvb_demux_feed *f, स्थिर u8 *src, माप_प्रकार len)
अणु
	वापस (f->feed.sec.crc_val = crc32_be(f->feed.sec.crc_val, src, len));
पूर्ण

अटल व्योम dvb_dmx_memcopy(काष्ठा dvb_demux_feed *f, u8 *d, स्थिर u8 *s,
			    माप_प्रकार len)
अणु
	स_नकल(d, s, len);
पूर्ण

/******************************************************************************
 * Software filter functions
 ******************************************************************************/

अटल अंतरभूत पूर्णांक dvb_dmx_swfilter_payload(काष्ठा dvb_demux_feed *feed,
					   स्थिर u8 *buf)
अणु
	पूर्णांक count = payload(buf);
	पूर्णांक p;
	पूर्णांक ccok;
	u8 cc;

	अगर (count == 0)
		वापस -1;

	p = 188 - count;

	cc = buf[3] & 0x0f;
	ccok = ((feed->cc + 1) & 0x0f) == cc;
	feed->cc = cc;
	अगर (!ccok) अणु
		set_buf_flags(feed, DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED);
		dprपूर्णांकk_sect_loss("missed packet: %d instead of %d!\n",
				  cc, (feed->cc + 1) & 0x0f);
	पूर्ण

	अगर (buf[1] & 0x40)	// PUSI ?
		feed->peslen = 0xfffa;

	feed->peslen += count;

	वापस feed->cb.ts(&buf[p], count, शून्य, 0, &feed->feed.ts,
			   &feed->buffer_flags);
पूर्ण

अटल पूर्णांक dvb_dmx_swfilter_sectionfilter(काष्ठा dvb_demux_feed *feed,
					  काष्ठा dvb_demux_filter *f)
अणु
	u8 neq = 0;
	पूर्णांक i;

	क्रम (i = 0; i < DVB_DEMUX_MASK_MAX; i++) अणु
		u8 xor = f->filter.filter_value[i] ^ feed->feed.sec.secbuf[i];

		अगर (f->maskandmode[i] & xor)
			वापस 0;

		neq |= f->maskandnoपंचांगode[i] & xor;
	पूर्ण

	अगर (f->करोneq && !neq)
		वापस 0;

	वापस feed->cb.sec(feed->feed.sec.secbuf, feed->feed.sec.seclen,
			    शून्य, 0, &f->filter, &feed->buffer_flags);
पूर्ण

अटल अंतरभूत पूर्णांक dvb_dmx_swfilter_section_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा dvb_demux_filter *f = feed->filter;
	काष्ठा dmx_section_feed *sec = &feed->feed.sec;
	पूर्णांक section_syntax_indicator;

	अगर (!sec->is_filtering)
		वापस 0;

	अगर (!f)
		वापस 0;

	अगर (sec->check_crc) अणु
		section_syntax_indicator = ((sec->secbuf[1] & 0x80) != 0);
		अगर (section_syntax_indicator &&
		    demux->check_crc32(feed, sec->secbuf, sec->seclen)) अणु
			set_buf_flags(feed, DMX_BUFFER_FLAG_HAD_CRC32_DISCARD);
			वापस -1;
		पूर्ण
	पूर्ण

	करो अणु
		अगर (dvb_dmx_swfilter_sectionfilter(feed, f) < 0)
			वापस -1;
	पूर्ण जबतक ((f = f->next) && sec->is_filtering);

	sec->seclen = 0;

	वापस 0;
पूर्ण

अटल व्योम dvb_dmx_swfilter_section_new(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dmx_section_feed *sec = &feed->feed.sec;

	अगर (sec->secbufp < sec->tsfeedp) अणु
		पूर्णांक n = sec->tsfeedp - sec->secbufp;

		/*
		 * Section padding is करोne with 0xff bytes entirely.
		 * Due to speed reasons, we won't check all of them
		 * but just first and last.
		 */
		अगर (sec->secbuf[0] != 0xff || sec->secbuf[n - 1] != 0xff) अणु
			set_buf_flags(feed,
				      DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED);
			dprपूर्णांकk_sect_loss("section ts padding loss: %d/%d\n",
					  n, sec->tsfeedp);
			dprपूर्णांकk_sect_loss("pad data: %*ph\n", n, sec->secbuf);
		पूर्ण
	पूर्ण

	sec->tsfeedp = sec->secbufp = sec->seclen = 0;
	sec->secbuf = sec->secbuf_base;
पूर्ण

/*
 * Losless Section Demux 1.4.1 by Emard
 * Valsecchi Patrick:
 *  - middle of section A  (no PUSI)
 *  - end of section A and start of section B
 *    (with PUSI poपूर्णांकing to the start of the second section)
 *
 *  In this हाल, without feed->pusi_seen you'll receive a garbage section
 *  consisting of the end of section A. Basically because tsfeedp
 *  is incemented and the use=0 condition is not उठाओd
 *  when the second packet arrives.
 *
 * Fix:
 * when demux is started, let feed->pusi_seen = false to
 * prevent initial feeding of garbage from the end of
 * previous section. When you क्रम the first समय see PUSI=1
 * then set feed->pusi_seen = true
 */
अटल पूर्णांक dvb_dmx_swfilter_section_copy_dump(काष्ठा dvb_demux_feed *feed,
					      स्थिर u8 *buf, u8 len)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा dmx_section_feed *sec = &feed->feed.sec;
	u16 limit, seclen, n;

	अगर (sec->tsfeedp >= DMX_MAX_SECFEED_SIZE)
		वापस 0;

	अगर (sec->tsfeedp + len > DMX_MAX_SECFEED_SIZE) अणु
		set_buf_flags(feed, DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED);
		dprपूर्णांकk_sect_loss("section buffer full loss: %d/%d\n",
				  sec->tsfeedp + len - DMX_MAX_SECFEED_SIZE,
				  DMX_MAX_SECFEED_SIZE);
		len = DMX_MAX_SECFEED_SIZE - sec->tsfeedp;
	पूर्ण

	अगर (len <= 0)
		वापस 0;

	demux->memcopy(feed, sec->secbuf_base + sec->tsfeedp, buf, len);
	sec->tsfeedp += len;

	/*
	 * Dump all the sections we can find in the data (Emard)
	 */
	limit = sec->tsfeedp;
	अगर (limit > DMX_MAX_SECFEED_SIZE)
		वापस -1;	/* पूर्णांकernal error should never happen */

	/* to be sure always set secbuf */
	sec->secbuf = sec->secbuf_base + sec->secbufp;

	क्रम (n = 0; sec->secbufp + 2 < limit; n++) अणु
		seclen = section_length(sec->secbuf);
		अगर (seclen <= 0 || seclen > DMX_MAX_SECTION_SIZE
		    || seclen + sec->secbufp > limit)
			वापस 0;
		sec->seclen = seclen;
		sec->crc_val = ~0;
		/* dump [secbuf .. secbuf+seclen) */
		अगर (feed->pusi_seen) अणु
			dvb_dmx_swfilter_section_feed(feed);
		पूर्ण अन्यथा अणु
			set_buf_flags(feed,
				      DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED);
			dprपूर्णांकk_sect_loss("pusi not seen, discarding section data\n");
		पूर्ण
		sec->secbufp += seclen;	/* secbufp and secbuf moving together is */
		sec->secbuf += seclen;	/* redundant but saves poपूर्णांकer arithmetic */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_dmx_swfilter_section_packet(काष्ठा dvb_demux_feed *feed,
					   स्थिर u8 *buf)
अणु
	u8 p, count;
	पूर्णांक ccok, dc_i = 0;
	u8 cc;

	count = payload(buf);

	अगर (count == 0)		/* count == 0 अगर no payload or out of range */
		वापस -1;

	p = 188 - count;	/* payload start */

	cc = buf[3] & 0x0f;
	ccok = ((feed->cc + 1) & 0x0f) == cc;
	feed->cc = cc;

	अगर (buf[3] & 0x20) अणु
		/* adaption field present, check क्रम discontinuity_indicator */
		अगर ((buf[4] > 0) && (buf[5] & 0x80))
			dc_i = 1;
	पूर्ण

	अगर (!ccok || dc_i) अणु
		अगर (dc_i) अणु
			set_buf_flags(feed,
				      DMX_BUFFER_FLAG_DISCONTINUITY_INDICATOR);
			dprपूर्णांकk_sect_loss("%d frame with disconnect indicator\n",
				cc);
		पूर्ण अन्यथा अणु
			set_buf_flags(feed,
				      DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED);
			dprपूर्णांकk_sect_loss("discontinuity: %d instead of %d. %d bytes lost\n",
				cc, (feed->cc + 1) & 0x0f, count + 4);
		पूर्ण
		/*
		 * those bytes under some circumstances will again be reported
		 * in the following dvb_dmx_swfilter_section_new
		 */

		/*
		 * Discontinuity detected. Reset pusi_seen to
		 * stop feeding of suspicious data until next PUSI=1 arrives
		 *
		 * FIXME: करोes it make sense अगर the MPEG-TS is the one
		 *	reporting discontinuity?
		 */

		feed->pusi_seen = false;
		dvb_dmx_swfilter_section_new(feed);
	पूर्ण

	अगर (buf[1] & 0x40) अणु
		/* PUSI=1 (is set), section boundary is here */
		अगर (count > 1 && buf[p] < count) अणु
			स्थिर u8 *beक्रमe = &buf[p + 1];
			u8 beक्रमe_len = buf[p];
			स्थिर u8 *after = &beक्रमe[beक्रमe_len];
			u8 after_len = count - 1 - beक्रमe_len;

			dvb_dmx_swfilter_section_copy_dump(feed, beक्रमe,
							   beक्रमe_len);
			/* beक्रमe start of new section, set pusi_seen */
			feed->pusi_seen = true;
			dvb_dmx_swfilter_section_new(feed);
			dvb_dmx_swfilter_section_copy_dump(feed, after,
							   after_len);
		पूर्ण अन्यथा अगर (count > 0) अणु
			set_buf_flags(feed,
				      DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED);
			dprपूर्णांकk_sect_loss("PUSI=1 but %d bytes lost\n", count);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* PUSI=0 (is not set), no section boundary */
		dvb_dmx_swfilter_section_copy_dump(feed, &buf[p], count);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dvb_dmx_swfilter_packet_type(काष्ठा dvb_demux_feed *feed,
						स्थिर u8 *buf)
अणु
	चयन (feed->type) अणु
	हाल DMX_TYPE_TS:
		अगर (!feed->feed.ts.is_filtering)
			अवरोध;
		अगर (feed->ts_type & TS_PACKET) अणु
			अगर (feed->ts_type & TS_PAYLOAD_ONLY)
				dvb_dmx_swfilter_payload(feed, buf);
			अन्यथा
				feed->cb.ts(buf, 188, शून्य, 0, &feed->feed.ts,
					    &feed->buffer_flags);
		पूर्ण
		/* Used only on full-featured devices */
		अगर (feed->ts_type & TS_DECODER)
			अगर (feed->demux->ग_लिखो_to_decoder)
				feed->demux->ग_लिखो_to_decoder(feed, buf, 188);
		अवरोध;

	हाल DMX_TYPE_SEC:
		अगर (!feed->feed.sec.is_filtering)
			अवरोध;
		अगर (dvb_dmx_swfilter_section_packet(feed, buf) < 0)
			feed->feed.sec.seclen = feed->feed.sec.secbufp = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा DVR_FEED(f)							\
	(((f)->type == DMX_TYPE_TS) &&					\
	((f)->feed.ts.is_filtering) &&					\
	(((f)->ts_type & (TS_PACKET | TS_DEMUX)) == TS_PACKET))

अटल व्योम dvb_dmx_swfilter_packet(काष्ठा dvb_demux *demux, स्थिर u8 *buf)
अणु
	काष्ठा dvb_demux_feed *feed;
	u16 pid = ts_pid(buf);
	पूर्णांक dvr_करोne = 0;

	अगर (dvb_demux_speedcheck) अणु
		kसमय_प्रकार cur_समय;
		u64 speed_bytes, speed_समयdelta;

		demux->speed_pkts_cnt++;

		/* show speed every SPEED_PKTS_INTERVAL packets */
		अगर (!(demux->speed_pkts_cnt % SPEED_PKTS_INTERVAL)) अणु
			cur_समय = kसमय_get();

			अगर (kसमय_प्रकारo_ns(demux->speed_last_समय) != 0) अणु
				speed_bytes = (u64)demux->speed_pkts_cnt
					* 188 * 8;
				/* convert to 1024 basis */
				speed_bytes = 1000 * भाग64_u64(speed_bytes,
						1024);
				speed_समयdelta = kसमय_ms_delta(cur_समय,
							demux->speed_last_समय);
				अगर (speed_समयdelta)
					dprपूर्णांकk("TS speed %llu Kbits/sec \n",
						भाग64_u64(speed_bytes,
							  speed_समयdelta));
			पूर्ण

			demux->speed_last_समय = cur_समय;
			demux->speed_pkts_cnt = 0;
		पूर्ण
	पूर्ण

	अगर (buf[1] & 0x80) अणु
		list_क्रम_each_entry(feed, &demux->feed_list, list_head) अणु
			अगर ((feed->pid != pid) && (feed->pid != 0x2000))
				जारी;
			set_buf_flags(feed, DMX_BUFFER_FLAG_TEI);
		पूर्ण
		dprपूर्णांकk_tscheck("TEI detected. PID=0x%x data1=0x%x\n",
				pid, buf[1]);
		/* data in this packet can't be trusted - drop it unless
		 * module option dvb_demux_feed_err_pkts is set */
		अगर (!dvb_demux_feed_err_pkts)
			वापस;
	पूर्ण अन्यथा /* अगर TEI bit is set, pid may be wrong- skip pkt counter */
		अगर (demux->cnt_storage && dvb_demux_tscheck) अणु
			/* check pkt counter */
			अगर (pid < MAX_PID) अणु
				अगर (buf[3] & 0x10)
					demux->cnt_storage[pid] =
						(demux->cnt_storage[pid] + 1) & 0xf;

				अगर ((buf[3] & 0xf) != demux->cnt_storage[pid]) अणु
					list_क्रम_each_entry(feed, &demux->feed_list, list_head) अणु
						अगर ((feed->pid != pid) && (feed->pid != 0x2000))
							जारी;
						set_buf_flags(feed,
							      DMX_BUFFER_PKT_COUNTER_MISMATCH);
					पूर्ण

					dprपूर्णांकk_tscheck("TS packet counter mismatch. PID=0x%x expected 0x%x got 0x%x\n",
							pid, demux->cnt_storage[pid],
							buf[3] & 0xf);
					demux->cnt_storage[pid] = buf[3] & 0xf;
				पूर्ण
			पूर्ण
			/* end check */
		पूर्ण

	list_क्रम_each_entry(feed, &demux->feed_list, list_head) अणु
		अगर ((feed->pid != pid) && (feed->pid != 0x2000))
			जारी;

		/* copy each packet only once to the dvr device, even
		 * अगर a PID is in multiple filters (e.g. video + PCR) */
		अगर ((DVR_FEED(feed)) && (dvr_करोne++))
			जारी;

		अगर (feed->pid == pid)
			dvb_dmx_swfilter_packet_type(feed, buf);
		अन्यथा अगर (feed->pid == 0x2000)
			feed->cb.ts(buf, 188, शून्य, 0, &feed->feed.ts,
				    &feed->buffer_flags);
	पूर्ण
पूर्ण

व्योम dvb_dmx_swfilter_packets(काष्ठा dvb_demux *demux, स्थिर u8 *buf,
			      माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&demux->lock, flags);

	जबतक (count--) अणु
		अगर (buf[0] == 0x47)
			dvb_dmx_swfilter_packet(demux, buf);
		buf += 188;
	पूर्ण

	spin_unlock_irqrestore(&demux->lock, flags);
पूर्ण

EXPORT_SYMBOL(dvb_dmx_swfilter_packets);

अटल अंतरभूत पूर्णांक find_next_packet(स्थिर u8 *buf, पूर्णांक pos, माप_प्रकार count,
				   स्थिर पूर्णांक pktsize)
अणु
	पूर्णांक start = pos, lost;

	जबतक (pos < count) अणु
		अगर (buf[pos] == 0x47 ||
		    (pktsize == 204 && buf[pos] == 0xB8))
			अवरोध;
		pos++;
	पूर्ण

	lost = pos - start;
	अगर (lost) अणु
		/* This garbage is part of a valid packet? */
		पूर्णांक backtrack = pos - pktsize;
		अगर (backtrack >= 0 && (buf[backtrack] == 0x47 ||
		    (pktsize == 204 && buf[backtrack] == 0xB8)))
			वापस backtrack;
	पूर्ण

	वापस pos;
पूर्ण

/* Filter all pktsize= 188 or 204 sized packets and skip garbage. */
अटल अंतरभूत व्योम _dvb_dmx_swfilter(काष्ठा dvb_demux *demux, स्थिर u8 *buf,
		माप_प्रकार count, स्थिर पूर्णांक pktsize)
अणु
	पूर्णांक p = 0, i, j;
	स्थिर u8 *q;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&demux->lock, flags);

	अगर (demux->tsbufp) अणु /* tsbuf[0] is now 0x47. */
		i = demux->tsbufp;
		j = pktsize - i;
		अगर (count < j) अणु
			स_नकल(&demux->tsbuf[i], buf, count);
			demux->tsbufp += count;
			जाओ bailout;
		पूर्ण
		स_नकल(&demux->tsbuf[i], buf, j);
		अगर (demux->tsbuf[0] == 0x47) /* द्विगुन check */
			dvb_dmx_swfilter_packet(demux, demux->tsbuf);
		demux->tsbufp = 0;
		p += j;
	पूर्ण

	जबतक (1) अणु
		p = find_next_packet(buf, p, count, pktsize);
		अगर (p >= count)
			अवरोध;
		अगर (count - p < pktsize)
			अवरोध;

		q = &buf[p];

		अगर (pktsize == 204 && (*q == 0xB8)) अणु
			स_नकल(demux->tsbuf, q, 188);
			demux->tsbuf[0] = 0x47;
			q = demux->tsbuf;
		पूर्ण
		dvb_dmx_swfilter_packet(demux, q);
		p += pktsize;
	पूर्ण

	i = count - p;
	अगर (i) अणु
		स_नकल(demux->tsbuf, &buf[p], i);
		demux->tsbufp = i;
		अगर (pktsize == 204 && demux->tsbuf[0] == 0xB8)
			demux->tsbuf[0] = 0x47;
	पूर्ण

bailout:
	spin_unlock_irqrestore(&demux->lock, flags);
पूर्ण

व्योम dvb_dmx_swfilter(काष्ठा dvb_demux *demux, स्थिर u8 *buf, माप_प्रकार count)
अणु
	_dvb_dmx_swfilter(demux, buf, count, 188);
पूर्ण
EXPORT_SYMBOL(dvb_dmx_swfilter);

व्योम dvb_dmx_swfilter_204(काष्ठा dvb_demux *demux, स्थिर u8 *buf, माप_प्रकार count)
अणु
	_dvb_dmx_swfilter(demux, buf, count, 204);
पूर्ण
EXPORT_SYMBOL(dvb_dmx_swfilter_204);

व्योम dvb_dmx_swfilter_raw(काष्ठा dvb_demux *demux, स्थिर u8 *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&demux->lock, flags);

	demux->feed->cb.ts(buf, count, शून्य, 0, &demux->feed->feed.ts,
			   &demux->feed->buffer_flags);

	spin_unlock_irqrestore(&demux->lock, flags);
पूर्ण
EXPORT_SYMBOL(dvb_dmx_swfilter_raw);

अटल काष्ठा dvb_demux_filter *dvb_dmx_filter_alloc(काष्ठा dvb_demux *demux)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < demux->filternum; i++)
		अगर (demux->filter[i].state == DMX_STATE_FREE)
			अवरोध;

	अगर (i == demux->filternum)
		वापस शून्य;

	demux->filter[i].state = DMX_STATE_ALLOCATED;

	वापस &demux->filter[i];
पूर्ण

अटल काष्ठा dvb_demux_feed *dvb_dmx_feed_alloc(काष्ठा dvb_demux *demux)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < demux->feednum; i++)
		अगर (demux->feed[i].state == DMX_STATE_FREE)
			अवरोध;

	अगर (i == demux->feednum)
		वापस शून्य;

	demux->feed[i].state = DMX_STATE_ALLOCATED;

	वापस &demux->feed[i];
पूर्ण

अटल पूर्णांक dvb_demux_feed_find(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux_feed *entry;

	list_क्रम_each_entry(entry, &feed->demux->feed_list, list_head)
		अगर (entry == feed)
			वापस 1;

	वापस 0;
पूर्ण

अटल व्योम dvb_demux_feed_add(काष्ठा dvb_demux_feed *feed)
अणु
	spin_lock_irq(&feed->demux->lock);
	अगर (dvb_demux_feed_find(feed)) अणु
		pr_err("%s: feed already in list (type=%x state=%x pid=%x)\n",
		       __func__, feed->type, feed->state, feed->pid);
		जाओ out;
	पूर्ण

	list_add(&feed->list_head, &feed->demux->feed_list);
out:
	spin_unlock_irq(&feed->demux->lock);
पूर्ण

अटल व्योम dvb_demux_feed_del(काष्ठा dvb_demux_feed *feed)
अणु
	spin_lock_irq(&feed->demux->lock);
	अगर (!(dvb_demux_feed_find(feed))) अणु
		pr_err("%s: feed not in list (type=%x state=%x pid=%x)\n",
		       __func__, feed->type, feed->state, feed->pid);
		जाओ out;
	पूर्ण

	list_del(&feed->list_head);
out:
	spin_unlock_irq(&feed->demux->lock);
पूर्ण

अटल पूर्णांक dmx_ts_feed_set(काष्ठा dmx_ts_feed *ts_feed, u16 pid, पूर्णांक ts_type,
			   क्रमागत dmx_ts_pes pes_type, kसमय_प्रकार समयout)
अणु
	काष्ठा dvb_demux_feed *feed = (काष्ठा dvb_demux_feed *)ts_feed;
	काष्ठा dvb_demux *demux = feed->demux;

	अगर (pid > DMX_MAX_PID)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&demux->mutex))
		वापस -ERESTARTSYS;

	अगर (ts_type & TS_DECODER) अणु
		अगर (pes_type >= DMX_PES_OTHER) अणु
			mutex_unlock(&demux->mutex);
			वापस -EINVAL;
		पूर्ण

		अगर (demux->pesfilter[pes_type] &&
		    demux->pesfilter[pes_type] != feed) अणु
			mutex_unlock(&demux->mutex);
			वापस -EINVAL;
		पूर्ण

		demux->pesfilter[pes_type] = feed;
		demux->pids[pes_type] = pid;
	पूर्ण

	dvb_demux_feed_add(feed);

	feed->pid = pid;
	feed->समयout = समयout;
	feed->ts_type = ts_type;
	feed->pes_type = pes_type;

	feed->state = DMX_STATE_READY;
	mutex_unlock(&demux->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक dmx_ts_feed_start_filtering(काष्ठा dmx_ts_feed *ts_feed)
अणु
	काष्ठा dvb_demux_feed *feed = (काष्ठा dvb_demux_feed *)ts_feed;
	काष्ठा dvb_demux *demux = feed->demux;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&demux->mutex))
		वापस -ERESTARTSYS;

	अगर (feed->state != DMX_STATE_READY || feed->type != DMX_TYPE_TS) अणु
		mutex_unlock(&demux->mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (!demux->start_feed) अणु
		mutex_unlock(&demux->mutex);
		वापस -ENODEV;
	पूर्ण

	अगर ((ret = demux->start_feed(feed)) < 0) अणु
		mutex_unlock(&demux->mutex);
		वापस ret;
	पूर्ण

	spin_lock_irq(&demux->lock);
	ts_feed->is_filtering = 1;
	feed->state = DMX_STATE_GO;
	spin_unlock_irq(&demux->lock);
	mutex_unlock(&demux->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक dmx_ts_feed_stop_filtering(काष्ठा dmx_ts_feed *ts_feed)
अणु
	काष्ठा dvb_demux_feed *feed = (काष्ठा dvb_demux_feed *)ts_feed;
	काष्ठा dvb_demux *demux = feed->demux;
	पूर्णांक ret;

	mutex_lock(&demux->mutex);

	अगर (feed->state < DMX_STATE_GO) अणु
		mutex_unlock(&demux->mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (!demux->stop_feed) अणु
		mutex_unlock(&demux->mutex);
		वापस -ENODEV;
	पूर्ण

	ret = demux->stop_feed(feed);

	spin_lock_irq(&demux->lock);
	ts_feed->is_filtering = 0;
	feed->state = DMX_STATE_ALLOCATED;
	spin_unlock_irq(&demux->lock);
	mutex_unlock(&demux->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक dvbdmx_allocate_ts_feed(काष्ठा dmx_demux *dmx,
				   काष्ठा dmx_ts_feed **ts_feed,
				   dmx_ts_cb callback)
अणु
	काष्ठा dvb_demux *demux = (काष्ठा dvb_demux *)dmx;
	काष्ठा dvb_demux_feed *feed;

	अगर (mutex_lock_पूर्णांकerruptible(&demux->mutex))
		वापस -ERESTARTSYS;

	अगर (!(feed = dvb_dmx_feed_alloc(demux))) अणु
		mutex_unlock(&demux->mutex);
		वापस -EBUSY;
	पूर्ण

	feed->type = DMX_TYPE_TS;
	feed->cb.ts = callback;
	feed->demux = demux;
	feed->pid = 0xffff;
	feed->peslen = 0xfffa;
	feed->buffer_flags = 0;

	(*ts_feed) = &feed->feed.ts;
	(*ts_feed)->parent = dmx;
	(*ts_feed)->priv = शून्य;
	(*ts_feed)->is_filtering = 0;
	(*ts_feed)->start_filtering = dmx_ts_feed_start_filtering;
	(*ts_feed)->stop_filtering = dmx_ts_feed_stop_filtering;
	(*ts_feed)->set = dmx_ts_feed_set;

	अगर (!(feed->filter = dvb_dmx_filter_alloc(demux))) अणु
		feed->state = DMX_STATE_FREE;
		mutex_unlock(&demux->mutex);
		वापस -EBUSY;
	पूर्ण

	feed->filter->type = DMX_TYPE_TS;
	feed->filter->feed = feed;
	feed->filter->state = DMX_STATE_READY;

	mutex_unlock(&demux->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक dvbdmx_release_ts_feed(काष्ठा dmx_demux *dmx,
				  काष्ठा dmx_ts_feed *ts_feed)
अणु
	काष्ठा dvb_demux *demux = (काष्ठा dvb_demux *)dmx;
	काष्ठा dvb_demux_feed *feed = (काष्ठा dvb_demux_feed *)ts_feed;

	mutex_lock(&demux->mutex);

	अगर (feed->state == DMX_STATE_FREE) अणु
		mutex_unlock(&demux->mutex);
		वापस -EINVAL;
	पूर्ण

	feed->state = DMX_STATE_FREE;
	feed->filter->state = DMX_STATE_FREE;

	dvb_demux_feed_del(feed);

	feed->pid = 0xffff;

	अगर (feed->ts_type & TS_DECODER && feed->pes_type < DMX_PES_OTHER)
		demux->pesfilter[feed->pes_type] = शून्य;

	mutex_unlock(&demux->mutex);
	वापस 0;
पूर्ण

/******************************************************************************
 * dmx_section_feed API calls
 ******************************************************************************/

अटल पूर्णांक dmx_section_feed_allocate_filter(काष्ठा dmx_section_feed *feed,
					    काष्ठा dmx_section_filter **filter)
अणु
	काष्ठा dvb_demux_feed *dvbdmxfeed = (काष्ठा dvb_demux_feed *)feed;
	काष्ठा dvb_demux *dvbdemux = dvbdmxfeed->demux;
	काष्ठा dvb_demux_filter *dvbdmxfilter;

	अगर (mutex_lock_पूर्णांकerruptible(&dvbdemux->mutex))
		वापस -ERESTARTSYS;

	dvbdmxfilter = dvb_dmx_filter_alloc(dvbdemux);
	अगर (!dvbdmxfilter) अणु
		mutex_unlock(&dvbdemux->mutex);
		वापस -EBUSY;
	पूर्ण

	spin_lock_irq(&dvbdemux->lock);
	*filter = &dvbdmxfilter->filter;
	(*filter)->parent = feed;
	(*filter)->priv = शून्य;
	dvbdmxfilter->feed = dvbdmxfeed;
	dvbdmxfilter->type = DMX_TYPE_SEC;
	dvbdmxfilter->state = DMX_STATE_READY;
	dvbdmxfilter->next = dvbdmxfeed->filter;
	dvbdmxfeed->filter = dvbdmxfilter;
	spin_unlock_irq(&dvbdemux->lock);

	mutex_unlock(&dvbdemux->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dmx_section_feed_set(काष्ठा dmx_section_feed *feed,
				u16 pid, पूर्णांक check_crc)
अणु
	काष्ठा dvb_demux_feed *dvbdmxfeed = (काष्ठा dvb_demux_feed *)feed;
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;

	अगर (pid > 0x1fff)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&dvbdmx->mutex))
		वापस -ERESTARTSYS;

	dvb_demux_feed_add(dvbdmxfeed);

	dvbdmxfeed->pid = pid;
	dvbdmxfeed->feed.sec.check_crc = check_crc;

	dvbdmxfeed->state = DMX_STATE_READY;
	mutex_unlock(&dvbdmx->mutex);
	वापस 0;
पूर्ण

अटल व्योम prepare_secfilters(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	पूर्णांक i;
	काष्ठा dvb_demux_filter *f;
	काष्ठा dmx_section_filter *sf;
	u8 mask, mode, करोneq;

	अगर (!(f = dvbdmxfeed->filter))
		वापस;
	करो अणु
		sf = &f->filter;
		करोneq = false;
		क्रम (i = 0; i < DVB_DEMUX_MASK_MAX; i++) अणु
			mode = sf->filter_mode[i];
			mask = sf->filter_mask[i];
			f->maskandmode[i] = mask & mode;
			करोneq |= f->maskandnoपंचांगode[i] = mask & ~mode;
		पूर्ण
		f->करोneq = करोneq ? true : false;
	पूर्ण जबतक ((f = f->next));
पूर्ण

अटल पूर्णांक dmx_section_feed_start_filtering(काष्ठा dmx_section_feed *feed)
अणु
	काष्ठा dvb_demux_feed *dvbdmxfeed = (काष्ठा dvb_demux_feed *)feed;
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dvbdmx->mutex))
		वापस -ERESTARTSYS;

	अगर (feed->is_filtering) अणु
		mutex_unlock(&dvbdmx->mutex);
		वापस -EBUSY;
	पूर्ण

	अगर (!dvbdmxfeed->filter) अणु
		mutex_unlock(&dvbdmx->mutex);
		वापस -EINVAL;
	पूर्ण

	dvbdmxfeed->feed.sec.tsfeedp = 0;
	dvbdmxfeed->feed.sec.secbuf = dvbdmxfeed->feed.sec.secbuf_base;
	dvbdmxfeed->feed.sec.secbufp = 0;
	dvbdmxfeed->feed.sec.seclen = 0;
	dvbdmxfeed->pusi_seen = false;

	अगर (!dvbdmx->start_feed) अणु
		mutex_unlock(&dvbdmx->mutex);
		वापस -ENODEV;
	पूर्ण

	prepare_secfilters(dvbdmxfeed);

	अगर ((ret = dvbdmx->start_feed(dvbdmxfeed)) < 0) अणु
		mutex_unlock(&dvbdmx->mutex);
		वापस ret;
	पूर्ण

	spin_lock_irq(&dvbdmx->lock);
	feed->is_filtering = 1;
	dvbdmxfeed->state = DMX_STATE_GO;
	spin_unlock_irq(&dvbdmx->lock);

	mutex_unlock(&dvbdmx->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dmx_section_feed_stop_filtering(काष्ठा dmx_section_feed *feed)
अणु
	काष्ठा dvb_demux_feed *dvbdmxfeed = (काष्ठा dvb_demux_feed *)feed;
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	पूर्णांक ret;

	mutex_lock(&dvbdmx->mutex);

	अगर (!dvbdmx->stop_feed) अणु
		mutex_unlock(&dvbdmx->mutex);
		वापस -ENODEV;
	पूर्ण

	ret = dvbdmx->stop_feed(dvbdmxfeed);

	spin_lock_irq(&dvbdmx->lock);
	dvbdmxfeed->state = DMX_STATE_READY;
	feed->is_filtering = 0;
	spin_unlock_irq(&dvbdmx->lock);

	mutex_unlock(&dvbdmx->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dmx_section_feed_release_filter(काष्ठा dmx_section_feed *feed,
					   काष्ठा dmx_section_filter *filter)
अणु
	काष्ठा dvb_demux_filter *dvbdmxfilter = (काष्ठा dvb_demux_filter *)filter, *f;
	काष्ठा dvb_demux_feed *dvbdmxfeed = (काष्ठा dvb_demux_feed *)feed;
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;

	mutex_lock(&dvbdmx->mutex);

	अगर (dvbdmxfilter->feed != dvbdmxfeed) अणु
		mutex_unlock(&dvbdmx->mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (feed->is_filtering) अणु
		/* release dvbdmx->mutex as far as it is
		   acquired by stop_filtering() itself */
		mutex_unlock(&dvbdmx->mutex);
		feed->stop_filtering(feed);
		mutex_lock(&dvbdmx->mutex);
	पूर्ण

	spin_lock_irq(&dvbdmx->lock);
	f = dvbdmxfeed->filter;

	अगर (f == dvbdmxfilter) अणु
		dvbdmxfeed->filter = dvbdmxfilter->next;
	पूर्ण अन्यथा अणु
		जबतक (f->next != dvbdmxfilter)
			f = f->next;
		f->next = f->next->next;
	पूर्ण

	dvbdmxfilter->state = DMX_STATE_FREE;
	spin_unlock_irq(&dvbdmx->lock);
	mutex_unlock(&dvbdmx->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dvbdmx_allocate_section_feed(काष्ठा dmx_demux *demux,
					काष्ठा dmx_section_feed **feed,
					dmx_section_cb callback)
अणु
	काष्ठा dvb_demux *dvbdmx = (काष्ठा dvb_demux *)demux;
	काष्ठा dvb_demux_feed *dvbdmxfeed;

	अगर (mutex_lock_पूर्णांकerruptible(&dvbdmx->mutex))
		वापस -ERESTARTSYS;

	अगर (!(dvbdmxfeed = dvb_dmx_feed_alloc(dvbdmx))) अणु
		mutex_unlock(&dvbdmx->mutex);
		वापस -EBUSY;
	पूर्ण

	dvbdmxfeed->type = DMX_TYPE_SEC;
	dvbdmxfeed->cb.sec = callback;
	dvbdmxfeed->demux = dvbdmx;
	dvbdmxfeed->pid = 0xffff;
	dvbdmxfeed->buffer_flags = 0;
	dvbdmxfeed->feed.sec.secbuf = dvbdmxfeed->feed.sec.secbuf_base;
	dvbdmxfeed->feed.sec.secbufp = dvbdmxfeed->feed.sec.seclen = 0;
	dvbdmxfeed->feed.sec.tsfeedp = 0;
	dvbdmxfeed->filter = शून्य;

	(*feed) = &dvbdmxfeed->feed.sec;
	(*feed)->is_filtering = 0;
	(*feed)->parent = demux;
	(*feed)->priv = शून्य;

	(*feed)->set = dmx_section_feed_set;
	(*feed)->allocate_filter = dmx_section_feed_allocate_filter;
	(*feed)->start_filtering = dmx_section_feed_start_filtering;
	(*feed)->stop_filtering = dmx_section_feed_stop_filtering;
	(*feed)->release_filter = dmx_section_feed_release_filter;

	mutex_unlock(&dvbdmx->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dvbdmx_release_section_feed(काष्ठा dmx_demux *demux,
				       काष्ठा dmx_section_feed *feed)
अणु
	काष्ठा dvb_demux_feed *dvbdmxfeed = (काष्ठा dvb_demux_feed *)feed;
	काष्ठा dvb_demux *dvbdmx = (काष्ठा dvb_demux *)demux;

	mutex_lock(&dvbdmx->mutex);

	अगर (dvbdmxfeed->state == DMX_STATE_FREE) अणु
		mutex_unlock(&dvbdmx->mutex);
		वापस -EINVAL;
	पूर्ण
	dvbdmxfeed->state = DMX_STATE_FREE;

	dvb_demux_feed_del(dvbdmxfeed);

	dvbdmxfeed->pid = 0xffff;

	mutex_unlock(&dvbdmx->mutex);
	वापस 0;
पूर्ण

/******************************************************************************
 * dvb_demux kernel data API calls
 ******************************************************************************/

अटल पूर्णांक dvbdmx_खोलो(काष्ठा dmx_demux *demux)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;

	अगर (dvbdemux->users >= MAX_DVB_DEMUX_USERS)
		वापस -EUSERS;

	dvbdemux->users++;
	वापस 0;
पूर्ण

अटल पूर्णांक dvbdmx_बंद(काष्ठा dmx_demux *demux)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;

	अगर (dvbdemux->users == 0)
		वापस -ENODEV;

	dvbdemux->users--;
	//FIXME: release any unneeded resources अगर users==0
	वापस 0;
पूर्ण

अटल पूर्णांक dvbdmx_ग_लिखो(काष्ठा dmx_demux *demux, स्थिर अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;
	व्योम *p;

	अगर ((!demux->frontend) || (demux->frontend->source != DMX_MEMORY_FE))
		वापस -EINVAL;

	p = memdup_user(buf, count);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);
	अगर (mutex_lock_पूर्णांकerruptible(&dvbdemux->mutex)) अणु
		kमुक्त(p);
		वापस -ERESTARTSYS;
	पूर्ण
	dvb_dmx_swfilter(dvbdemux, p, count);
	kमुक्त(p);
	mutex_unlock(&dvbdemux->mutex);

	अगर (संकेत_pending(current))
		वापस -EINTR;
	वापस count;
पूर्ण

अटल पूर्णांक dvbdmx_add_frontend(काष्ठा dmx_demux *demux,
			       काष्ठा dmx_frontend *frontend)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;
	काष्ठा list_head *head = &dvbdemux->frontend_list;

	list_add(&(frontend->connectivity_list), head);

	वापस 0;
पूर्ण

अटल पूर्णांक dvbdmx_हटाओ_frontend(काष्ठा dmx_demux *demux,
				  काष्ठा dmx_frontend *frontend)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;
	काष्ठा list_head *pos, *n, *head = &dvbdemux->frontend_list;

	list_क्रम_each_safe(pos, n, head) अणु
		अगर (DMX_FE_ENTRY(pos) == frontend) अणु
			list_del(pos);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल काष्ठा list_head *dvbdmx_get_frontends(काष्ठा dmx_demux *demux)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;

	अगर (list_empty(&dvbdemux->frontend_list))
		वापस शून्य;

	वापस &dvbdemux->frontend_list;
पूर्ण

अटल पूर्णांक dvbdmx_connect_frontend(काष्ठा dmx_demux *demux,
				   काष्ठा dmx_frontend *frontend)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;

	अगर (demux->frontend)
		वापस -EINVAL;

	mutex_lock(&dvbdemux->mutex);

	demux->frontend = frontend;
	mutex_unlock(&dvbdemux->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dvbdmx_disconnect_frontend(काष्ठा dmx_demux *demux)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;

	mutex_lock(&dvbdemux->mutex);

	demux->frontend = शून्य;
	mutex_unlock(&dvbdemux->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dvbdmx_get_pes_pids(काष्ठा dmx_demux *demux, u16 * pids)
अणु
	काष्ठा dvb_demux *dvbdemux = (काष्ठा dvb_demux *)demux;

	स_नकल(pids, dvbdemux->pids, 5 * माप(u16));
	वापस 0;
पूर्ण

पूर्णांक dvb_dmx_init(काष्ठा dvb_demux *dvbdemux)
अणु
	पूर्णांक i;
	काष्ठा dmx_demux *dmx = &dvbdemux->dmx;

	dvbdemux->cnt_storage = शून्य;
	dvbdemux->users = 0;
	dvbdemux->filter = vदो_स्मृति(array_size(माप(काष्ठा dvb_demux_filter),
					      dvbdemux->filternum));

	अगर (!dvbdemux->filter)
		वापस -ENOMEM;

	dvbdemux->feed = vदो_स्मृति(array_size(माप(काष्ठा dvb_demux_feed),
					    dvbdemux->feednum));
	अगर (!dvbdemux->feed) अणु
		vमुक्त(dvbdemux->filter);
		dvbdemux->filter = शून्य;
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < dvbdemux->filternum; i++) अणु
		dvbdemux->filter[i].state = DMX_STATE_FREE;
		dvbdemux->filter[i].index = i;
	पूर्ण
	क्रम (i = 0; i < dvbdemux->feednum; i++) अणु
		dvbdemux->feed[i].state = DMX_STATE_FREE;
		dvbdemux->feed[i].index = i;
	पूर्ण

	dvbdemux->cnt_storage = vदो_स्मृति(MAX_PID + 1);
	अगर (!dvbdemux->cnt_storage)
		pr_warn("Couldn't allocate memory for TS/TEI check. Disabling it\n");

	INIT_LIST_HEAD(&dvbdemux->frontend_list);

	क्रम (i = 0; i < DMX_PES_OTHER; i++) अणु
		dvbdemux->pesfilter[i] = शून्य;
		dvbdemux->pids[i] = 0xffff;
	पूर्ण

	INIT_LIST_HEAD(&dvbdemux->feed_list);

	dvbdemux->playing = 0;
	dvbdemux->recording = 0;
	dvbdemux->tsbufp = 0;

	अगर (!dvbdemux->check_crc32)
		dvbdemux->check_crc32 = dvb_dmx_crc32;

	अगर (!dvbdemux->memcopy)
		dvbdemux->memcopy = dvb_dmx_memcopy;

	dmx->frontend = शून्य;
	dmx->priv = dvbdemux;
	dmx->खोलो = dvbdmx_खोलो;
	dmx->बंद = dvbdmx_बंद;
	dmx->ग_लिखो = dvbdmx_ग_लिखो;
	dmx->allocate_ts_feed = dvbdmx_allocate_ts_feed;
	dmx->release_ts_feed = dvbdmx_release_ts_feed;
	dmx->allocate_section_feed = dvbdmx_allocate_section_feed;
	dmx->release_section_feed = dvbdmx_release_section_feed;

	dmx->add_frontend = dvbdmx_add_frontend;
	dmx->हटाओ_frontend = dvbdmx_हटाओ_frontend;
	dmx->get_frontends = dvbdmx_get_frontends;
	dmx->connect_frontend = dvbdmx_connect_frontend;
	dmx->disconnect_frontend = dvbdmx_disconnect_frontend;
	dmx->get_pes_pids = dvbdmx_get_pes_pids;

	mutex_init(&dvbdemux->mutex);
	spin_lock_init(&dvbdemux->lock);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(dvb_dmx_init);

व्योम dvb_dmx_release(काष्ठा dvb_demux *dvbdemux)
अणु
	vमुक्त(dvbdemux->cnt_storage);
	vमुक्त(dvbdemux->filter);
	vमुक्त(dvbdemux->feed);
पूर्ण

EXPORT_SYMBOL(dvb_dmx_release);
