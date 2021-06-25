<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * WL3501 Wireless LAN PCMCIA Card Driver क्रम Linux
 * Written originally क्रम Linux 2.0.30 by Fox Chen, mhchen@golf.ccl.itri.org.tw
 * Ported to 2.2, 2.4 & 2.5 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 * Wireless extensions in 2.4 by Gustavo Niemeyer <niemeyer@conectiva.com>
 *
 * References used by Fox Chen जबतक writing the original driver क्रम 2.0.30:
 *
 *   1. WL24xx packet drivers (tooयंत्र.यंत्र)
 *   2. Access Poपूर्णांक Firmware Interface Specअगरication क्रम IEEE 802.11 SUTRO
 *   3. IEEE 802.11
 *   4. Linux network driver (/usr/src/linux/drivers/net)
 *   5. ISA card driver - wl24.c
 *   6. Linux PCMCIA skeleton driver - skeleton.c
 *   7. Linux PCMCIA 3c589 network driver - 3c589_cs.c
 *
 * Tested with WL2400 firmware 1.2, Linux 2.0.30, and pcmcia-cs-2.9.12
 *   1. Perक्रमmance: about 165 Kbytes/sec in TCP/IP with Ad-Hoc mode.
 *      rsh 192.168.1.3 "dd if=/dev/zero bs=1k count=1000" > /dev/null
 *      (Specअगरication 2M bits/sec. is about 250 Kbytes/sec., but we must deduct
 *       ETHER/IP/UDP/TCP header, and acknowledgement overhead)
 *
 * Tested with Planet AP in 2.4.17, 184 Kbytes/s in UDP in Infraकाष्ठाure mode,
 * 173 Kbytes/s in TCP.
 *
 * Tested with Planet AP in 2.5.73-bk, 216 Kbytes/s in Infraकाष्ठाure mode
 * with a SMP machine (dual pentium 100), using pktgen, 432 pps (pkt_size = 60)
 */

#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/wireless.h>
#समावेश <net/cfg80211.h>

#समावेश <net/iw_handler.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश "wl3501.h"

#अगर_अघोषित __i386__
#घोषणा slow_करोwn_io()
#पूर्ण_अगर

/* For rough स्थिरant delay */
#घोषणा WL3501_NOPLOOP(n) अणु पूर्णांक x = 0; जबतक (x++ < n) slow_करोwn_io(); पूर्ण



#घोषणा wl3501_outb(a, b) अणु outb(a, b); slow_करोwn_io(); पूर्ण
#घोषणा wl3501_outb_p(a, b) अणु outb_p(a, b); slow_करोwn_io(); पूर्ण
#घोषणा wl3501_outsb(a, b, c) अणु outsb(a, b, c); slow_करोwn_io(); पूर्ण

#घोषणा WL3501_RELEASE_TIMEOUT (25 * HZ)
#घोषणा WL3501_MAX_ADHOC_TRIES 16

#घोषणा WL3501_RESUME	0
#घोषणा WL3501_SUSPEND	1

अटल पूर्णांक wl3501_config(काष्ठा pcmcia_device *link);
अटल व्योम wl3501_release(काष्ठा pcmcia_device *link);

अटल स्थिर काष्ठा अणु
	पूर्णांक reg_करोमुख्य;
	पूर्णांक min, max, deflt;
पूर्ण iw_channel_table[] = अणु
	अणु
		.reg_करोमुख्य = IW_REG_DOMAIN_FCC,
		.min	    = 1,
		.max	    = 11,
		.deflt	    = 1,
	पूर्ण,
	अणु
		.reg_करोमुख्य = IW_REG_DOMAIN_DOC,
		.min	    = 1,
		.max	    = 11,
		.deflt	    = 1,
	पूर्ण,
	अणु
		.reg_करोमुख्य = IW_REG_DOMAIN_ETSI,
		.min	    = 1,
		.max	    = 13,
		.deflt	    = 1,
	पूर्ण,
	अणु
		.reg_करोमुख्य = IW_REG_DOMAIN_SPAIN,
		.min	    = 10,
		.max	    = 11,
		.deflt	    = 10,
	पूर्ण,
	अणु
		.reg_करोमुख्य = IW_REG_DOMAIN_FRANCE,
		.min	    = 10,
		.max	    = 13,
		.deflt	    = 10,
	पूर्ण,
	अणु
		.reg_करोमुख्य = IW_REG_DOMAIN_MKK,
		.min	    = 14,
		.max	    = 14,
		.deflt	    = 14,
	पूर्ण,
	अणु
		.reg_करोमुख्य = IW_REG_DOMAIN_MKK1,
		.min	    = 1,
		.max	    = 14,
		.deflt	    = 1,
	पूर्ण,
	अणु
		.reg_करोमुख्य = IW_REG_DOMAIN_ISRAEL,
		.min	    = 3,
		.max	    = 9,
		.deflt	    = 9,
	पूर्ण,
पूर्ण;

/**
 * iw_valid_channel - validate channel in regulatory करोमुख्य
 * @reg_करोमुख्य: regulatory करोमुख्य
 * @channel: channel to validate
 *
 * Returns 0 अगर invalid in the specअगरied regulatory करोमुख्य, non-zero अगर valid.
 */
अटल पूर्णांक iw_valid_channel(पूर्णांक reg_करोमुख्य, पूर्णांक channel)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < ARRAY_SIZE(iw_channel_table); i++)
		अगर (reg_करोमुख्य == iw_channel_table[i].reg_करोमुख्य) अणु
			rc = channel >= iw_channel_table[i].min &&
			     channel <= iw_channel_table[i].max;
			अवरोध;
		पूर्ण
	वापस rc;
पूर्ण

/**
 * iw_शेष_channel - get शेष channel क्रम a regulatory करोमुख्य
 * @reg_करोमुख्य: regulatory करोमुख्य
 *
 * Returns the शेष channel क्रम a regulatory करोमुख्य
 */
अटल पूर्णांक iw_शेष_channel(पूर्णांक reg_करोमुख्य)
अणु
	पूर्णांक i, rc = 1;

	क्रम (i = 0; i < ARRAY_SIZE(iw_channel_table); i++)
		अगर (reg_करोमुख्य == iw_channel_table[i].reg_करोमुख्य) अणु
			rc = iw_channel_table[i].deflt;
			अवरोध;
		पूर्ण
	वापस rc;
पूर्ण

अटल व्योम iw_set_mgmt_info_element(क्रमागत iw_mgmt_info_element_ids id,
				     काष्ठा iw_mgmt_info_element *el,
				     व्योम *value, पूर्णांक len)
अणु
	el->id  = id;
	el->len = len;
	स_नकल(el->data, value, len);
पूर्ण

अटल व्योम iw_copy_mgmt_info_element(काष्ठा iw_mgmt_info_element *to,
				      काष्ठा iw_mgmt_info_element *from)
अणु
	iw_set_mgmt_info_element(from->id, to, from->data, from->len);
पूर्ण

अटल अंतरभूत व्योम wl3501_चयन_page(काष्ठा wl3501_card *this, u8 page)
अणु
	wl3501_outb(page, this->base_addr + WL3501_NIC_BSS);
पूर्ण

/*
 * Get Ethernet MAC address.
 *
 * WARNING: We चयन to FPAGE0 and switc back again.
 *          Making sure there is no other WL function beening called by ISR.
 */
अटल पूर्णांक wl3501_get_flash_mac_addr(काष्ठा wl3501_card *this)
अणु
	पूर्णांक base_addr = this->base_addr;

	/* get MAC addr */
	wl3501_outb(WL3501_BSS_FPAGE3, base_addr + WL3501_NIC_BSS); /* BSS */
	wl3501_outb(0x00, base_addr + WL3501_NIC_LMAL);	/* LMAL */
	wl3501_outb(0x40, base_addr + WL3501_NIC_LMAH);	/* LMAH */

	/* रुको क्रम पढ़ोing EEPROM */
	WL3501_NOPLOOP(100);
	this->mac_addr[0] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[1] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[2] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[3] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[4] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->mac_addr[5] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->reg_करोमुख्य = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	wl3501_outb(WL3501_BSS_FPAGE0, base_addr + WL3501_NIC_BSS);
	wl3501_outb(0x04, base_addr + WL3501_NIC_LMAL);
	wl3501_outb(0x40, base_addr + WL3501_NIC_LMAH);
	WL3501_NOPLOOP(100);
	this->version[0] = inb(base_addr + WL3501_NIC_IODPA);
	WL3501_NOPLOOP(100);
	this->version[1] = inb(base_addr + WL3501_NIC_IODPA);
	/* चयन to SRAM Page 0 (क्रम safety) */
	wl3501_चयन_page(this, WL3501_BSS_SPAGE0);

	/* The MAC addr should be 00:60:... */
	वापस this->mac_addr[0] == 0x00 && this->mac_addr[1] == 0x60;
पूर्ण

/**
 * wl3501_set_to_wla - Move 'size' bytes from PC to card
 * @this: Card
 * @dest: Card addressing space
 * @src: PC addressing space
 * @size: Bytes to move
 *
 * Move 'size' bytes from PC to card. (Shouldn't be पूर्णांकerrupted)
 */
अटल व्योम wl3501_set_to_wla(काष्ठा wl3501_card *this, u16 dest, व्योम *src,
			      पूर्णांक size)
अणु
	/* चयन to SRAM Page 0 */
	wl3501_चयन_page(this, (dest & 0x8000) ? WL3501_BSS_SPAGE1 :
						   WL3501_BSS_SPAGE0);
	/* set LMAL and LMAH */
	wl3501_outb(dest & 0xff, this->base_addr + WL3501_NIC_LMAL);
	wl3501_outb(((dest >> 8) & 0x7f), this->base_addr + WL3501_NIC_LMAH);

	/* rep out to Port A */
	wl3501_outsb(this->base_addr + WL3501_NIC_IODPA, src, size);
पूर्ण

/**
 * wl3501_get_from_wla - Move 'size' bytes from card to PC
 * @this: Card
 * @src: Card addressing space
 * @dest: PC addressing space
 * @size: Bytes to move
 *
 * Move 'size' bytes from card to PC. (Shouldn't be पूर्णांकerrupted)
 */
अटल व्योम wl3501_get_from_wla(काष्ठा wl3501_card *this, u16 src, व्योम *dest,
				पूर्णांक size)
अणु
	/* चयन to SRAM Page 0 */
	wl3501_चयन_page(this, (src & 0x8000) ? WL3501_BSS_SPAGE1 :
						  WL3501_BSS_SPAGE0);
	/* set LMAL and LMAH */
	wl3501_outb(src & 0xff, this->base_addr + WL3501_NIC_LMAL);
	wl3501_outb((src >> 8) & 0x7f, this->base_addr + WL3501_NIC_LMAH);

	/* rep get from Port A */
	insb(this->base_addr + WL3501_NIC_IODPA, dest, size);
पूर्ण

/*
 * Get/Allocate a मुक्त Tx Data Buffer
 *
 *  *--------------*-----------------*----------------------------------*
 *  |    PLCP      |    MAC Header   |  DST  SRC         Data ...       |
 *  |  (24 bytes)  |    (30 bytes)   |  (6)  (6)  (Ethernet Row Data)   |
 *  *--------------*-----------------*----------------------------------*
 *  \               \- IEEE 802.11 -/ \-------------- len --------------/
 *   \-काष्ठा wl3501_80211_tx_hdr--/   \-------- Ethernet Frame -------/
 *
 * Return = Position in Card
 */
अटल u16 wl3501_get_tx_buffer(काष्ठा wl3501_card *this, u16 len)
अणु
	u16 next, blk_cnt = 0, zero = 0;
	u16 full_len = माप(काष्ठा wl3501_80211_tx_hdr) + len;
	u16 ret = 0;

	अगर (full_len > this->tx_buffer_cnt * 254)
		जाओ out;
	ret = this->tx_buffer_head;
	जबतक (full_len) अणु
		अगर (full_len < 254)
			full_len = 0;
		अन्यथा
			full_len -= 254;
		wl3501_get_from_wla(this, this->tx_buffer_head, &next,
				    माप(next));
		अगर (!full_len)
			wl3501_set_to_wla(this, this->tx_buffer_head, &zero,
					  माप(zero));
		this->tx_buffer_head = next;
		blk_cnt++;
		/* अगर buffer is not enough */
		अगर (!next && full_len) अणु
			this->tx_buffer_head = ret;
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	this->tx_buffer_cnt -= blk_cnt;
out:
	वापस ret;
पूर्ण

/*
 * Free an allocated Tx Buffer. ptr must be correct position.
 */
अटल व्योम wl3501_मुक्त_tx_buffer(काष्ठा wl3501_card *this, u16 ptr)
अणु
	/* check अगर all space is not मुक्त */
	अगर (!this->tx_buffer_head)
		this->tx_buffer_head = ptr;
	अन्यथा
		wl3501_set_to_wla(this, this->tx_buffer_tail,
				  &ptr, माप(ptr));
	जबतक (ptr) अणु
		u16 next;

		this->tx_buffer_cnt++;
		wl3501_get_from_wla(this, ptr, &next, माप(next));
		this->tx_buffer_tail = ptr;
		ptr = next;
	पूर्ण
पूर्ण

अटल पूर्णांक wl3501_esbq_req_test(काष्ठा wl3501_card *this)
अणु
	u8 पंचांगp = 0;

	wl3501_get_from_wla(this, this->esbq_req_head + 3, &पंचांगp, माप(पंचांगp));
	वापस पंचांगp & 0x80;
पूर्ण

अटल व्योम wl3501_esbq_req(काष्ठा wl3501_card *this, u16 *ptr)
अणु
	u16 पंचांगp = 0;

	wl3501_set_to_wla(this, this->esbq_req_head, ptr, 2);
	wl3501_set_to_wla(this, this->esbq_req_head + 2, &पंचांगp, माप(पंचांगp));
	this->esbq_req_head += 4;
	अगर (this->esbq_req_head >= this->esbq_req_end)
		this->esbq_req_head = this->esbq_req_start;
पूर्ण

अटल पूर्णांक wl3501_esbq_exec(काष्ठा wl3501_card *this, व्योम *sig, पूर्णांक sig_size)
अणु
	पूर्णांक rc = -EIO;

	अगर (wl3501_esbq_req_test(this)) अणु
		u16 ptr = wl3501_get_tx_buffer(this, sig_size);
		अगर (ptr) अणु
			wl3501_set_to_wla(this, ptr, sig, sig_size);
			wl3501_esbq_req(this, &ptr);
			rc = 0;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_request_mib(काष्ठा wl3501_card *this, u8 index, व्योम *bf)
अणु
	काष्ठा wl3501_get_req sig = अणु
		.sig_id	    = WL3501_SIG_GET_REQ,
		.mib_attrib = index,
	पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -EIO;

	spin_lock_irqsave(&this->lock, flags);
	अगर (wl3501_esbq_req_test(this)) अणु
		u16 ptr = wl3501_get_tx_buffer(this, माप(sig));
		अगर (ptr) अणु
			wl3501_set_to_wla(this, ptr, &sig, माप(sig));
			wl3501_esbq_req(this, &ptr);
			this->sig_get_confirm.mib_status = 255;
			rc = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&this->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_mib_value(काष्ठा wl3501_card *this, u8 index,
				व्योम *bf, पूर्णांक size)
अणु
	पूर्णांक rc;

	rc = wl3501_request_mib(this, index, bf);
	अगर (rc)
		वापस rc;

	rc = रुको_event_पूर्णांकerruptible(this->रुको,
		this->sig_get_confirm.mib_status != 255);
	अगर (rc)
		वापस rc;

	स_नकल(bf, this->sig_get_confirm.mib_value, size);
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_pwr_mgmt(काष्ठा wl3501_card *this, पूर्णांक suspend)
अणु
	काष्ठा wl3501_pwr_mgmt_req sig = अणु
		.sig_id		= WL3501_SIG_PWR_MGMT_REQ,
		.pwr_save	= suspend,
		.wake_up	= !suspend,
		.receive_dtims	= 10,
	पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -EIO;

	spin_lock_irqsave(&this->lock, flags);
	अगर (wl3501_esbq_req_test(this)) अणु
		u16 ptr = wl3501_get_tx_buffer(this, माप(sig));
		अगर (ptr) अणु
			wl3501_set_to_wla(this, ptr, &sig, माप(sig));
			wl3501_esbq_req(this, &ptr);
			this->sig_pwr_mgmt_confirm.status = 255;
			spin_unlock_irqrestore(&this->lock, flags);
			rc = रुको_event_पूर्णांकerruptible(this->रुको,
				this->sig_pwr_mgmt_confirm.status != 255);
			prपूर्णांकk(KERN_INFO "%s: %s status=%d\n", __func__,
			       suspend ? "suspend" : "resume",
			       this->sig_pwr_mgmt_confirm.status);
			जाओ out;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&this->lock, flags);
out:
	वापस rc;
पूर्ण

/**
 * wl3501_send_pkt - Send a packet.
 * @this: Card
 * @data: Ethernet raw frame.  (e.g. data[0] - data[5] is Dest MAC Addr,
 *                                   data[6] - data[11] is Src MAC Addr)
 * @len: Packet length
 * Ref: IEEE 802.11
 */
अटल पूर्णांक wl3501_send_pkt(काष्ठा wl3501_card *this, u8 *data, u16 len)
अणु
	u16 bf, sig_bf, next, पंचांगplen, pktlen;
	काष्ठा wl3501_md_req sig = अणु
		.sig_id = WL3501_SIG_MD_REQ,
	पूर्ण;
	माप_प्रकार sig_addr_len = माप(sig.addr);
	u8 *pdata = (अक्षर *)data;
	पूर्णांक rc = -EIO;

	अगर (wl3501_esbq_req_test(this)) अणु
		sig_bf = wl3501_get_tx_buffer(this, माप(sig));
		rc = -ENOMEM;
		अगर (!sig_bf)	/* No मुक्त buffer available */
			जाओ out;
		bf = wl3501_get_tx_buffer(this, len + 26 + 24);
		अगर (!bf) अणु
			/* No मुक्त buffer available */
			wl3501_मुक्त_tx_buffer(this, sig_bf);
			जाओ out;
		पूर्ण
		rc = 0;
		स_नकल(&sig.addr, pdata, sig_addr_len);
		pktlen = len - sig_addr_len;
		pdata += sig_addr_len;
		sig.data = bf;
		अगर (((*pdata) * 256 + (*(pdata + 1))) > 1500) अणु
			u8 addr4[ETH_ALEN] = अणु
				[0] = 0xAA, [1] = 0xAA, [2] = 0x03, [4] = 0x00,
			पूर्ण;

			wl3501_set_to_wla(this, bf + 2 +
					  दुरत्व(काष्ठा wl3501_tx_hdr, addr4),
					  addr4, माप(addr4));
			sig.size = pktlen + 24 + 4 + 6;
			अगर (pktlen > (254 - माप(काष्ठा wl3501_tx_hdr))) अणु
				पंचांगplen = 254 - माप(काष्ठा wl3501_tx_hdr);
				pktlen -= पंचांगplen;
			पूर्ण अन्यथा अणु
				पंचांगplen = pktlen;
				pktlen = 0;
			पूर्ण
			wl3501_set_to_wla(this,
					  bf + 2 + माप(काष्ठा wl3501_tx_hdr),
					  pdata, पंचांगplen);
			pdata += पंचांगplen;
			wl3501_get_from_wla(this, bf, &next, माप(next));
			bf = next;
		पूर्ण अन्यथा अणु
			sig.size = pktlen + 24 + 4 - 2;
			pdata += 2;
			pktlen -= 2;
			अगर (pktlen > (254 - माप(काष्ठा wl3501_tx_hdr) + 6)) अणु
				पंचांगplen = 254 - माप(काष्ठा wl3501_tx_hdr) + 6;
				pktlen -= पंचांगplen;
			पूर्ण अन्यथा अणु
				पंचांगplen = pktlen;
				pktlen = 0;
			पूर्ण
			wl3501_set_to_wla(this, bf + 2 +
					  दुरत्व(काष्ठा wl3501_tx_hdr, addr4),
					  pdata, पंचांगplen);
			pdata += पंचांगplen;
			wl3501_get_from_wla(this, bf, &next, माप(next));
			bf = next;
		पूर्ण
		जबतक (pktlen > 0) अणु
			अगर (pktlen > 254) अणु
				पंचांगplen = 254;
				pktlen -= 254;
			पूर्ण अन्यथा अणु
				पंचांगplen = pktlen;
				pktlen = 0;
			पूर्ण
			wl3501_set_to_wla(this, bf + 2, pdata, पंचांगplen);
			pdata += पंचांगplen;
			wl3501_get_from_wla(this, bf, &next, माप(next));
			bf = next;
		पूर्ण
		wl3501_set_to_wla(this, sig_bf, &sig, माप(sig));
		wl3501_esbq_req(this, &sig_bf);
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_mgmt_resync(काष्ठा wl3501_card *this)
अणु
	काष्ठा wl3501_resync_req sig = अणु
		.sig_id = WL3501_SIG_RESYNC_REQ,
	पूर्ण;

	वापस wl3501_esbq_exec(this, &sig, माप(sig));
पूर्ण

अटल अंतरभूत पूर्णांक wl3501_fw_bss_type(काष्ठा wl3501_card *this)
अणु
	वापस this->net_type == IW_MODE_INFRA ? WL3501_NET_TYPE_INFRA :
						 WL3501_NET_TYPE_ADHOC;
पूर्ण

अटल अंतरभूत पूर्णांक wl3501_fw_cap_info(काष्ठा wl3501_card *this)
अणु
	वापस this->net_type == IW_MODE_INFRA ? WL3501_MGMT_CAPABILITY_ESS :
						 WL3501_MGMT_CAPABILITY_IBSS;
पूर्ण

अटल पूर्णांक wl3501_mgmt_scan(काष्ठा wl3501_card *this, u16 chan_समय)
अणु
	काष्ठा wl3501_scan_req sig = अणु
		.sig_id		= WL3501_SIG_SCAN_REQ,
		.scan_type	= WL3501_SCAN_TYPE_ACTIVE,
		.probe_delay	= 0x10,
		.min_chan_समय	= chan_समय,
		.max_chan_समय	= chan_समय,
		.bss_type	= wl3501_fw_bss_type(this),
	पूर्ण;

	this->bss_cnt = this->join_sta_bss = 0;
	वापस wl3501_esbq_exec(this, &sig, माप(sig));
पूर्ण

अटल पूर्णांक wl3501_mgmt_join(काष्ठा wl3501_card *this, u16 stas)
अणु
	काष्ठा wl3501_join_req sig = अणु
		.sig_id		  = WL3501_SIG_JOIN_REQ,
		.समयout	  = 10,
		.req.ds_pset = अणु
			.el = अणु
				.id  = IW_MGMT_INFO_ELEMENT_DS_PARAMETER_SET,
				.len = 1,
			पूर्ण,
			.chan	= this->chan,
		पूर्ण,
	पूर्ण;

	स_नकल(&sig.req, &this->bss_set[stas].req, माप(sig.req));
	वापस wl3501_esbq_exec(this, &sig, माप(sig));
पूर्ण

अटल पूर्णांक wl3501_mgmt_start(काष्ठा wl3501_card *this)
अणु
	काष्ठा wl3501_start_req sig = अणु
		.sig_id			= WL3501_SIG_START_REQ,
		.beacon_period		= 400,
		.dtim_period		= 1,
		.ds_pset = अणु
			.el = अणु
				.id  = IW_MGMT_INFO_ELEMENT_DS_PARAMETER_SET,
				.len = 1,
			पूर्ण,
			.chan	= this->chan,
		पूर्ण,
		.bss_basic_rset	= अणु
			.el = अणु
				.id	= IW_MGMT_INFO_ELEMENT_SUPPORTED_RATES,
				.len = 2,
			पूर्ण,
			.data_rate_labels = अणु
				[0] = IW_MGMT_RATE_LABEL_MANDATORY |
				      IW_MGMT_RATE_LABEL_1MBIT,
				[1] = IW_MGMT_RATE_LABEL_MANDATORY |
				      IW_MGMT_RATE_LABEL_2MBIT,
			पूर्ण,
		पूर्ण,
		.operational_rset	= अणु
			.el = अणु
				.id	= IW_MGMT_INFO_ELEMENT_SUPPORTED_RATES,
				.len = 2,
			पूर्ण,
			.data_rate_labels = अणु
				[0] = IW_MGMT_RATE_LABEL_MANDATORY |
				      IW_MGMT_RATE_LABEL_1MBIT,
				[1] = IW_MGMT_RATE_LABEL_MANDATORY |
				      IW_MGMT_RATE_LABEL_2MBIT,
			पूर्ण,
		पूर्ण,
		.ibss_pset		= अणु
			.el = अणु
				.id	 = IW_MGMT_INFO_ELEMENT_IBSS_PARAMETER_SET,
				.len     = 2,
			पूर्ण,
			.atim_winकरोw = 10,
		पूर्ण,
		.bss_type		= wl3501_fw_bss_type(this),
		.cap_info		= wl3501_fw_cap_info(this),
	पूर्ण;

	iw_copy_mgmt_info_element(&sig.ssid.el, &this->essid.el);
	iw_copy_mgmt_info_element(&this->keep_essid.el, &this->essid.el);
	वापस wl3501_esbq_exec(this, &sig, माप(sig));
पूर्ण

अटल व्योम wl3501_mgmt_scan_confirm(काष्ठा wl3501_card *this, u16 addr)
अणु
	u16 i = 0;
	पूर्णांक matchflag = 0;
	काष्ठा wl3501_scan_confirm sig;

	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &sig, माप(sig));
	अगर (sig.status == WL3501_STATUS_SUCCESS) अणु
		pr_debug("success");
		अगर ((this->net_type == IW_MODE_INFRA &&
		     (sig.req.cap_info & WL3501_MGMT_CAPABILITY_ESS)) ||
		    (this->net_type == IW_MODE_ADHOC &&
		     (sig.req.cap_info & WL3501_MGMT_CAPABILITY_IBSS)) ||
		    this->net_type == IW_MODE_AUTO) अणु
			अगर (!this->essid.el.len)
				matchflag = 1;
			अन्यथा अगर (this->essid.el.len == 3 &&
				 !स_भेद(this->essid.essid, "ANY", 3))
				matchflag = 1;
			अन्यथा अगर (this->essid.el.len != sig.req.ssid.el.len)
				matchflag = 0;
			अन्यथा अगर (स_भेद(this->essid.essid, sig.req.ssid.essid,
					this->essid.el.len))
				matchflag = 0;
			अन्यथा
				matchflag = 1;
			अगर (matchflag) अणु
				क्रम (i = 0; i < this->bss_cnt; i++) अणु
					अगर (ether_addr_equal_unaligned(this->bss_set[i].req.bssid,
								       sig.req.bssid)) अणु
						matchflag = 0;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (matchflag && (i < 20)) अणु
				स_नकल(&this->bss_set[i].req,
				       &sig.req, माप(sig.req));
				this->bss_cnt++;
				this->rssi = sig.rssi;
				this->bss_set[i].rssi = sig.rssi;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (sig.status == WL3501_STATUS_TIMEOUT) अणु
		pr_debug("timeout");
		this->join_sta_bss = 0;
		क्रम (i = this->join_sta_bss; i < this->bss_cnt; i++)
			अगर (!wl3501_mgmt_join(this, i))
				अवरोध;
		this->join_sta_bss = i;
		अगर (this->join_sta_bss == this->bss_cnt) अणु
			अगर (this->net_type == IW_MODE_INFRA)
				wl3501_mgmt_scan(this, 100);
			अन्यथा अणु
				this->adhoc_बार++;
				अगर (this->adhoc_बार > WL3501_MAX_ADHOC_TRIES)
					wl3501_mgmt_start(this);
				अन्यथा
					wl3501_mgmt_scan(this, 100);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * wl3501_block_पूर्णांकerrupt - Mask पूर्णांकerrupt from SUTRO
 * @this: Card
 *
 * Mask पूर्णांकerrupt from SUTRO. (i.e. SUTRO cannot पूर्णांकerrupt the HOST)
 * Return: 1 अगर पूर्णांकerrupt is originally enabled
 */
अटल पूर्णांक wl3501_block_पूर्णांकerrupt(काष्ठा wl3501_card *this)
अणु
	u8 old = inb(this->base_addr + WL3501_NIC_GCR);
	u8 new = old & (~(WL3501_GCR_ECINT | WL3501_GCR_INT2EC |
			WL3501_GCR_ENECINT));

	wl3501_outb(new, this->base_addr + WL3501_NIC_GCR);
	वापस old & WL3501_GCR_ENECINT;
पूर्ण

/**
 * wl3501_unblock_पूर्णांकerrupt - Enable पूर्णांकerrupt from SUTRO
 * @this: Card
 *
 * Enable पूर्णांकerrupt from SUTRO. (i.e. SUTRO can पूर्णांकerrupt the HOST)
 * Return: 1 अगर पूर्णांकerrupt is originally enabled
 */
अटल पूर्णांक wl3501_unblock_पूर्णांकerrupt(काष्ठा wl3501_card *this)
अणु
	u8 old = inb(this->base_addr + WL3501_NIC_GCR);
	u8 new = (old & ~(WL3501_GCR_ECINT | WL3501_GCR_INT2EC)) |
		  WL3501_GCR_ENECINT;

	wl3501_outb(new, this->base_addr + WL3501_NIC_GCR);
	वापस old & WL3501_GCR_ENECINT;
पूर्ण

/**
 * wl3501_receive - Receive data from Receive Queue.
 *
 * Receive data from Receive Queue.
 *
 * @this: card
 * @bf: address of host
 * @size: size of buffer.
 */
अटल u16 wl3501_receive(काष्ठा wl3501_card *this, u8 *bf, u16 size)
अणु
	u16 next_addr, next_addr1;
	u8 *data = bf + 12;

	size -= 12;
	wl3501_get_from_wla(this, this->start_seg + 2,
			    &next_addr, माप(next_addr));
	अगर (size > WL3501_BLKSZ - माप(काष्ठा wl3501_rx_hdr)) अणु
		wl3501_get_from_wla(this,
				    this->start_seg +
					माप(काष्ठा wl3501_rx_hdr), data,
				    WL3501_BLKSZ -
					माप(काष्ठा wl3501_rx_hdr));
		size -= WL3501_BLKSZ - माप(काष्ठा wl3501_rx_hdr);
		data += WL3501_BLKSZ - माप(काष्ठा wl3501_rx_hdr);
	पूर्ण अन्यथा अणु
		wl3501_get_from_wla(this,
				    this->start_seg +
					माप(काष्ठा wl3501_rx_hdr),
				    data, size);
		size = 0;
	पूर्ण
	जबतक (size > 0) अणु
		अगर (size > WL3501_BLKSZ - 5) अणु
			wl3501_get_from_wla(this, next_addr + 5, data,
					    WL3501_BLKSZ - 5);
			size -= WL3501_BLKSZ - 5;
			data += WL3501_BLKSZ - 5;
			wl3501_get_from_wla(this, next_addr + 2, &next_addr1,
					    माप(next_addr1));
			next_addr = next_addr1;
		पूर्ण अन्यथा अणु
			wl3501_get_from_wla(this, next_addr + 5, data, size);
			size = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम wl3501_esbq_req_मुक्त(काष्ठा wl3501_card *this)
अणु
	u8 पंचांगp;
	u16 addr;

	अगर (this->esbq_req_head == this->esbq_req_tail)
		जाओ out;
	wl3501_get_from_wla(this, this->esbq_req_tail + 3, &पंचांगp, माप(पंचांगp));
	अगर (!(पंचांगp & 0x80))
		जाओ out;
	wl3501_get_from_wla(this, this->esbq_req_tail, &addr, माप(addr));
	wl3501_मुक्त_tx_buffer(this, addr);
	this->esbq_req_tail += 4;
	अगर (this->esbq_req_tail >= this->esbq_req_end)
		this->esbq_req_tail = this->esbq_req_start;
out:
	वापस;
पूर्ण

अटल पूर्णांक wl3501_esbq_confirm(काष्ठा wl3501_card *this)
अणु
	u8 पंचांगp;

	wl3501_get_from_wla(this, this->esbq_confirm + 3, &पंचांगp, माप(पंचांगp));
	वापस पंचांगp & 0x80;
पूर्ण

अटल व्योम wl3501_online(काष्ठा net_device *dev)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);

	prपूर्णांकk(KERN_INFO "%s: Wireless LAN online. BSSID: %pM\n",
	       dev->name, this->bssid);
	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम wl3501_esbq_confirm_करोne(काष्ठा wl3501_card *this)
अणु
	u8 पंचांगp = 0;

	wl3501_set_to_wla(this, this->esbq_confirm + 3, &पंचांगp, माप(पंचांगp));
	this->esbq_confirm += 4;
	अगर (this->esbq_confirm >= this->esbq_confirm_end)
		this->esbq_confirm = this->esbq_confirm_start;
पूर्ण

अटल पूर्णांक wl3501_mgmt_auth(काष्ठा wl3501_card *this)
अणु
	काष्ठा wl3501_auth_req sig = अणु
		.sig_id	 = WL3501_SIG_AUTH_REQ,
		.type	 = WL3501_SYS_TYPE_OPEN,
		.समयout = 1000,
	पूर्ण;

	pr_debug("entry");
	स_नकल(sig.mac_addr, this->bssid, ETH_ALEN);
	वापस wl3501_esbq_exec(this, &sig, माप(sig));
पूर्ण

अटल पूर्णांक wl3501_mgmt_association(काष्ठा wl3501_card *this)
अणु
	काष्ठा wl3501_assoc_req sig = अणु
		.sig_id		 = WL3501_SIG_ASSOC_REQ,
		.समयout	 = 1000,
		.listen_पूर्णांकerval = 5,
		.cap_info	 = this->cap_info,
	पूर्ण;

	pr_debug("entry");
	स_नकल(sig.mac_addr, this->bssid, ETH_ALEN);
	वापस wl3501_esbq_exec(this, &sig, माप(sig));
पूर्ण

अटल व्योम wl3501_mgmt_join_confirm(काष्ठा net_device *dev, u16 addr)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	काष्ठा wl3501_join_confirm sig;

	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &sig, माप(sig));
	अगर (sig.status == WL3501_STATUS_SUCCESS) अणु
		अगर (this->net_type == IW_MODE_INFRA) अणु
			अगर (this->join_sta_bss < this->bss_cnt) अणु
				स्थिर पूर्णांक i = this->join_sta_bss;
				स_नकल(this->bssid,
				       this->bss_set[i].req.bssid, ETH_ALEN);
				this->chan = this->bss_set[i].req.ds_pset.chan;
				iw_copy_mgmt_info_element(&this->keep_essid.el,
						     &this->bss_set[i].req.ssid.el);
				wl3501_mgmt_auth(this);
			पूर्ण
		पूर्ण अन्यथा अणु
			स्थिर पूर्णांक i = this->join_sta_bss;

			स_नकल(&this->bssid, &this->bss_set[i].req.bssid, ETH_ALEN);
			this->chan = this->bss_set[i].req.ds_pset.chan;
			iw_copy_mgmt_info_element(&this->keep_essid.el,
						  &this->bss_set[i].req.ssid.el);
			wl3501_online(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		this->join_sta_bss++;
		क्रम (i = this->join_sta_bss; i < this->bss_cnt; i++)
			अगर (!wl3501_mgmt_join(this, i))
				अवरोध;
		this->join_sta_bss = i;
		अगर (this->join_sta_bss == this->bss_cnt) अणु
			अगर (this->net_type == IW_MODE_INFRA)
				wl3501_mgmt_scan(this, 100);
			अन्यथा अणु
				this->adhoc_बार++;
				अगर (this->adhoc_बार > WL3501_MAX_ADHOC_TRIES)
					wl3501_mgmt_start(this);
				अन्यथा
					wl3501_mgmt_scan(this, 100);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम wl3501_alarm_पूर्णांकerrupt(काष्ठा net_device *dev,
					  काष्ठा wl3501_card *this)
अणु
	अगर (this->net_type == IW_MODE_INFRA) अणु
		prपूर्णांकk(KERN_INFO "Wireless LAN offline\n");
		netअगर_stop_queue(dev);
		wl3501_mgmt_resync(this);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम wl3501_md_confirm_पूर्णांकerrupt(काष्ठा net_device *dev,
					       काष्ठा wl3501_card *this,
					       u16 addr)
अणु
	काष्ठा wl3501_md_confirm sig;

	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &sig, माप(sig));
	wl3501_मुक्त_tx_buffer(this, sig.data);
	अगर (netअगर_queue_stopped(dev))
		netअगर_wake_queue(dev);
पूर्ण

अटल अंतरभूत व्योम wl3501_md_ind_पूर्णांकerrupt(काष्ठा net_device *dev,
					   काष्ठा wl3501_card *this, u16 addr)
अणु
	काष्ठा wl3501_md_ind sig;
	काष्ठा sk_buff *skb;
	u8 rssi, addr4[ETH_ALEN];
	u16 pkt_len;

	wl3501_get_from_wla(this, addr, &sig, माप(sig));
	this->start_seg = sig.data;
	wl3501_get_from_wla(this,
			    sig.data + दुरत्व(काष्ठा wl3501_rx_hdr, rssi),
			    &rssi, माप(rssi));
	this->rssi = rssi <= 63 ? (rssi * 100) / 64 : 255;

	wl3501_get_from_wla(this,
			    sig.data +
				दुरत्व(काष्ठा wl3501_rx_hdr, addr4),
			    &addr4, माप(addr4));
	अगर (!(addr4[0] == 0xAA && addr4[1] == 0xAA &&
	      addr4[2] == 0x03 && addr4[4] == 0x00)) अणु
		prपूर्णांकk(KERN_INFO "Unsupported packet type!\n");
		वापस;
	पूर्ण
	pkt_len = sig.size + 12 - 24 - 4 - 6;

	skb = dev_alloc_skb(pkt_len + 5);

	अगर (!skb) अणु
		prपूर्णांकk(KERN_WARNING "%s: Can't alloc a sk_buff of size %d.\n",
		       dev->name, pkt_len);
		dev->stats.rx_dropped++;
	पूर्ण अन्यथा अणु
		skb->dev = dev;
		skb_reserve(skb, 2); /* IP headers on 16 bytes boundaries */
		skb_copy_to_linear_data(skb, (अचिन्हित अक्षर *)&sig.addr,
					माप(sig.addr));
		wl3501_receive(this, skb->data, pkt_len);
		skb_put(skb, pkt_len);
		skb->protocol	= eth_type_trans(skb, dev);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		netअगर_rx(skb);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम wl3501_get_confirm_पूर्णांकerrupt(काष्ठा wl3501_card *this,
						u16 addr, व्योम *sig, पूर्णांक size)
अणु
	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &this->sig_get_confirm,
			    माप(this->sig_get_confirm));
	wake_up(&this->रुको);
पूर्ण

अटल अंतरभूत व्योम wl3501_start_confirm_पूर्णांकerrupt(काष्ठा net_device *dev,
						  काष्ठा wl3501_card *this,
						  u16 addr)
अणु
	काष्ठा wl3501_start_confirm sig;

	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &sig, माप(sig));
	अगर (sig.status == WL3501_STATUS_SUCCESS)
		netअगर_wake_queue(dev);
पूर्ण

अटल अंतरभूत व्योम wl3501_assoc_confirm_पूर्णांकerrupt(काष्ठा net_device *dev,
						  u16 addr)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	काष्ठा wl3501_assoc_confirm sig;

	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &sig, माप(sig));

	अगर (sig.status == WL3501_STATUS_SUCCESS)
		wl3501_online(dev);
पूर्ण

अटल अंतरभूत व्योम wl3501_auth_confirm_पूर्णांकerrupt(काष्ठा wl3501_card *this,
						 u16 addr)
अणु
	काष्ठा wl3501_auth_confirm sig;

	pr_debug("entry");
	wl3501_get_from_wla(this, addr, &sig, माप(sig));

	अगर (sig.status == WL3501_STATUS_SUCCESS)
		wl3501_mgmt_association(this);
	अन्यथा
		wl3501_mgmt_resync(this);
पूर्ण

अटल अंतरभूत व्योम wl3501_rx_पूर्णांकerrupt(काष्ठा net_device *dev)
अणु
	पूर्णांक morepkts;
	u16 addr;
	u8 sig_id;
	काष्ठा wl3501_card *this = netdev_priv(dev);

	pr_debug("entry");
loop:
	morepkts = 0;
	अगर (!wl3501_esbq_confirm(this))
		जाओ मुक्त;
	wl3501_get_from_wla(this, this->esbq_confirm, &addr, माप(addr));
	wl3501_get_from_wla(this, addr + 2, &sig_id, माप(sig_id));

	चयन (sig_id) अणु
	हाल WL3501_SIG_DEAUTH_IND:
	हाल WL3501_SIG_DISASSOC_IND:
	हाल WL3501_SIG_ALARM:
		wl3501_alarm_पूर्णांकerrupt(dev, this);
		अवरोध;
	हाल WL3501_SIG_MD_CONFIRM:
		wl3501_md_confirm_पूर्णांकerrupt(dev, this, addr);
		अवरोध;
	हाल WL3501_SIG_MD_IND:
		wl3501_md_ind_पूर्णांकerrupt(dev, this, addr);
		अवरोध;
	हाल WL3501_SIG_GET_CONFIRM:
		wl3501_get_confirm_पूर्णांकerrupt(this, addr,
					     &this->sig_get_confirm,
					     माप(this->sig_get_confirm));
		अवरोध;
	हाल WL3501_SIG_PWR_MGMT_CONFIRM:
		wl3501_get_confirm_पूर्णांकerrupt(this, addr,
					     &this->sig_pwr_mgmt_confirm,
					    माप(this->sig_pwr_mgmt_confirm));
		अवरोध;
	हाल WL3501_SIG_START_CONFIRM:
		wl3501_start_confirm_पूर्णांकerrupt(dev, this, addr);
		अवरोध;
	हाल WL3501_SIG_SCAN_CONFIRM:
		wl3501_mgmt_scan_confirm(this, addr);
		अवरोध;
	हाल WL3501_SIG_JOIN_CONFIRM:
		wl3501_mgmt_join_confirm(dev, addr);
		अवरोध;
	हाल WL3501_SIG_ASSOC_CONFIRM:
		wl3501_assoc_confirm_पूर्णांकerrupt(dev, addr);
		अवरोध;
	हाल WL3501_SIG_AUTH_CONFIRM:
		wl3501_auth_confirm_पूर्णांकerrupt(this, addr);
		अवरोध;
	हाल WL3501_SIG_RESYNC_CONFIRM:
		wl3501_mgmt_resync(this); /* FIXME: should be resync_confirm */
		अवरोध;
	पूर्ण
	wl3501_esbq_confirm_करोne(this);
	morepkts = 1;
	/* मुक्त request अगर necessary */
मुक्त:
	wl3501_esbq_req_मुक्त(this);
	अगर (morepkts)
		जाओ loop;
पूर्ण

अटल अंतरभूत व्योम wl3501_ack_पूर्णांकerrupt(काष्ठा wl3501_card *this)
अणु
	wl3501_outb(WL3501_GCR_ECINT, this->base_addr + WL3501_NIC_GCR);
पूर्ण

/**
 * wl3501_पूर्णांकerrupt - Hardware पूर्णांकerrupt from card.
 * @irq: Interrupt number
 * @dev_id: net_device
 *
 * We must acknowledge the पूर्णांकerrupt as soon as possible, and block the
 * पूर्णांकerrupt from the same card immediately to prevent re-entry.
 *
 * Beक्रमe accessing the Control_Status_Block, we must lock SUTRO first.
 * On the other hand, to prevent SUTRO from malfunctioning, we must
 * unlock the SUTRO as soon as possible.
 */
अटल irqवापस_t wl3501_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा wl3501_card *this;

	this = netdev_priv(dev);
	spin_lock(&this->lock);
	wl3501_ack_पूर्णांकerrupt(this);
	wl3501_block_पूर्णांकerrupt(this);
	wl3501_rx_पूर्णांकerrupt(dev);
	wl3501_unblock_पूर्णांकerrupt(this);
	spin_unlock(&this->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wl3501_reset_board(काष्ठा wl3501_card *this)
अणु
	u8 पंचांगp = 0;
	पूर्णांक i, rc = 0;

	/* Coreset */
	wl3501_outb_p(WL3501_GCR_CORESET, this->base_addr + WL3501_NIC_GCR);
	wl3501_outb_p(0, this->base_addr + WL3501_NIC_GCR);
	wl3501_outb_p(WL3501_GCR_CORESET, this->base_addr + WL3501_NIC_GCR);

	/* Reset SRAM 0x480 to zero */
	wl3501_set_to_wla(this, 0x480, &पंचांगp, माप(पंचांगp));

	/* Start up */
	wl3501_outb_p(0, this->base_addr + WL3501_NIC_GCR);

	WL3501_NOPLOOP(1024 * 50);

	wl3501_unblock_पूर्णांकerrupt(this);	/* acme: was commented */

	/* Polling Self_Test_Status */
	क्रम (i = 0; i < 10000; i++) अणु
		wl3501_get_from_wla(this, 0x480, &पंचांगp, माप(पंचांगp));

		अगर (पंचांगp == 'W') अणु
			/* firmware complete all test successfully */
			पंचांगp = 'A';
			wl3501_set_to_wla(this, 0x480, &पंचांगp, माप(पंचांगp));
			जाओ out;
		पूर्ण
		WL3501_NOPLOOP(10);
	पूर्ण
	prपूर्णांकk(KERN_WARNING "%s: failed to reset the board!\n", __func__);
	rc = -ENODEV;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_init_firmware(काष्ठा wl3501_card *this)
अणु
	u16 ptr, next;
	पूर्णांक rc = wl3501_reset_board(this);

	अगर (rc)
		जाओ fail;
	this->card_name[0] = '\0';
	wl3501_get_from_wla(this, 0x1a00,
			    this->card_name, माप(this->card_name));
	this->card_name[माप(this->card_name) - 1] = '\0';
	this->firmware_date[0] = '\0';
	wl3501_get_from_wla(this, 0x1a40,
			    this->firmware_date, माप(this->firmware_date));
	this->firmware_date[माप(this->firmware_date) - 1] = '\0';
	/* Switch to SRAM Page 0 */
	wl3501_चयन_page(this, WL3501_BSS_SPAGE0);
	/* Read parameter from card */
	wl3501_get_from_wla(this, 0x482, &this->esbq_req_start, 2);
	wl3501_get_from_wla(this, 0x486, &this->esbq_req_end, 2);
	wl3501_get_from_wla(this, 0x488, &this->esbq_confirm_start, 2);
	wl3501_get_from_wla(this, 0x48c, &this->esbq_confirm_end, 2);
	wl3501_get_from_wla(this, 0x48e, &this->tx_buffer_head, 2);
	wl3501_get_from_wla(this, 0x492, &this->tx_buffer_size, 2);
	this->esbq_req_tail	= this->esbq_req_head = this->esbq_req_start;
	this->esbq_req_end     += this->esbq_req_start;
	this->esbq_confirm	= this->esbq_confirm_start;
	this->esbq_confirm_end += this->esbq_confirm_start;
	/* Initial Tx Buffer */
	this->tx_buffer_cnt = 1;
	ptr = this->tx_buffer_head;
	next = ptr + WL3501_BLKSZ;
	जबतक ((next - this->tx_buffer_head) < this->tx_buffer_size) अणु
		this->tx_buffer_cnt++;
		wl3501_set_to_wla(this, ptr, &next, माप(next));
		ptr = next;
		next = ptr + WL3501_BLKSZ;
	पूर्ण
	rc = 0;
	next = 0;
	wl3501_set_to_wla(this, ptr, &next, माप(next));
	this->tx_buffer_tail = ptr;
out:
	वापस rc;
fail:
	prपूर्णांकk(KERN_WARNING "%s: failed!\n", __func__);
	जाओ out;
पूर्ण

अटल पूर्णांक wl3501_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा pcmcia_device *link;
	link = this->p_dev;

	spin_lock_irqsave(&this->lock, flags);
	link->खोलो--;

	/* Stop wl3501_hard_start_xmit() from now on */
	netअगर_stop_queue(dev);
	wl3501_ack_पूर्णांकerrupt(this);

	/* Mask पूर्णांकerrupts from the SUTRO */
	wl3501_block_पूर्णांकerrupt(this);

	prपूर्णांकk(KERN_INFO "%s: WL3501 closed\n", dev->name);
	spin_unlock_irqrestore(&this->lock, flags);
	वापस 0;
पूर्ण

/**
 * wl3501_reset - Reset the SUTRO.
 * @dev: network device
 *
 * It is almost the same as wl3501_खोलो(). In fact, we may just wl3501_बंद()
 * and wl3501_खोलो() again, but I wouldn't like to मुक्त_irq() when the driver
 * is running. It seems to be dangerous.
 */
अटल पूर्णांक wl3501_reset(काष्ठा net_device *dev)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक rc = -ENODEV;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&this->lock, flags);
	wl3501_block_पूर्णांकerrupt(this);

	अगर (wl3501_init_firmware(this)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Can't initialize Firmware!\n",
		       dev->name);
		/* Free IRQ, and mark IRQ as unused */
		मुक्त_irq(dev->irq, dev);
		जाओ out;
	पूर्ण

	/*
	 * Queue has to be started only when the Card is Started
	 */
	netअगर_stop_queue(dev);
	this->adhoc_बार = 0;
	wl3501_ack_पूर्णांकerrupt(this);
	wl3501_unblock_पूर्णांकerrupt(this);
	wl3501_mgmt_scan(this, 100);
	pr_debug("%s: device reset", dev->name);
	rc = 0;
out:
	spin_unlock_irqrestore(&this->lock, flags);
	वापस rc;
पूर्ण

अटल व्योम wl3501_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	पूर्णांक rc;

	stats->tx_errors++;
	rc = wl3501_reset(dev);
	अगर (rc)
		prपूर्णांकk(KERN_ERR "%s: Error %d resetting card on Tx timeout!\n",
		       dev->name, rc);
	अन्यथा अणु
		netअगर_trans_update(dev); /* prevent tx समयout */
		netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

/*
 * Return : 0 - OK
 *	    1 - Could not transmit (dev_queue_xmit will queue it)
 *		and try to sent it later
 */
अटल netdev_tx_t wl3501_hard_start_xmit(काष्ठा sk_buff *skb,
						काष्ठा net_device *dev)
अणु
	पूर्णांक enabled, rc;
	काष्ठा wl3501_card *this = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&this->lock, flags);
	enabled = wl3501_block_पूर्णांकerrupt(this);
	rc = wl3501_send_pkt(this, skb->data, skb->len);
	अगर (enabled)
		wl3501_unblock_पूर्णांकerrupt(this);
	अगर (rc) अणु
		++dev->stats.tx_dropped;
		netअगर_stop_queue(dev);
	पूर्ण अन्यथा अणु
		++dev->stats.tx_packets;
		dev->stats.tx_bytes += skb->len;
		kमुक्त_skb(skb);

		अगर (this->tx_buffer_cnt < 2)
			netअगर_stop_queue(dev);
	पूर्ण
	spin_unlock_irqrestore(&this->lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक wl3501_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा wl3501_card *this = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा pcmcia_device *link;
	link = this->p_dev;

	spin_lock_irqsave(&this->lock, flags);
	अगर (!pcmcia_dev_present(link))
		जाओ out;
	netअगर_device_attach(dev);
	link->खोलो++;

	/* Initial WL3501 firmware */
	pr_debug("%s: Initialize WL3501 firmware...", dev->name);
	अगर (wl3501_init_firmware(this))
		जाओ fail;
	/* Initial device variables */
	this->adhoc_बार = 0;
	/* Acknowledge Interrupt, क्रम cleaning last state */
	wl3501_ack_पूर्णांकerrupt(this);

	/* Enable पूर्णांकerrupt from card after all */
	wl3501_unblock_पूर्णांकerrupt(this);
	wl3501_mgmt_scan(this, 100);
	rc = 0;
	pr_debug("%s: WL3501 opened", dev->name);
	prपूर्णांकk(KERN_INFO "%s: Card Name: %s\n"
			 "%s: Firmware Date: %s\n",
			 dev->name, this->card_name,
			 dev->name, this->firmware_date);
out:
	spin_unlock_irqrestore(&this->lock, flags);
	वापस rc;
fail:
	prपूर्णांकk(KERN_WARNING "%s: Can't initialize firmware!\n", dev->name);
	जाओ out;
पूर्ण

अटल काष्ठा iw_statistics *wl3501_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	काष्ठा iw_statistics *wstats = &this->wstats;
	u32 value; /* size checked: it is u32 */

	स_रखो(wstats, 0, माप(*wstats));
	wstats->status = netअगर_running(dev);
	अगर (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_WEP_ICV_ERROR_COUNT,
				  &value, माप(value)))
		wstats->discard.code += value;
	अगर (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_WEP_UNDECRYPTABLE_COUNT,
				  &value, माप(value)))
		wstats->discard.code += value;
	अगर (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_WEP_EXCLUDED_COUNT,
				  &value, माप(value)))
		wstats->discard.code += value;
	अगर (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_RETRY_COUNT,
				  &value, माप(value)))
		wstats->discard.retries	= value;
	अगर (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_FAILED_COUNT,
				  &value, माप(value)))
		wstats->discard.misc += value;
	अगर (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_RTS_FAILURE_COUNT,
				  &value, माप(value)))
		wstats->discard.misc += value;
	अगर (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_ACK_FAILURE_COUNT,
				  &value, माप(value)))
		wstats->discard.misc += value;
	अगर (!wl3501_get_mib_value(this, WL3501_MIB_ATTR_FRAME_DUPLICATE_COUNT,
				  &value, माप(value)))
		wstats->discard.misc += value;
	वापस wstats;
पूर्ण

/**
 * wl3501_detach - deletes a driver "instance"
 * @link: FILL_IN
 *
 * This deletes a driver "instance". The device is de-रेजिस्टरed with Card
 * Services. If it has been released, all local data काष्ठाures are मुक्तd.
 * Otherwise, the काष्ठाures will be मुक्तd when the device is released.
 */
अटल व्योम wl3501_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	/* If the device is currently configured and active, we won't actually
	 * delete it yet.  Instead, it is marked so that when the release()
	 * function is called, that will trigger a proper detach(). */

	जबतक (link->खोलो > 0)
		wl3501_बंद(dev);

	netअगर_device_detach(dev);
	wl3501_release(link);

	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक wl3501_get_name(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	strlcpy(wrqu->name, "IEEE 802.11-DS", माप(wrqu->name));
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_set_freq(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक channel = wrqu->freq.m;
	पूर्णांक rc = -EINVAL;

	अगर (iw_valid_channel(this->reg_करोमुख्य, channel)) अणु
		this->chan = channel;
		rc = wl3501_reset(dev);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_freq(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);

	wrqu->freq.m = 100000 *
		ieee80211_channel_to_frequency(this->chan, NL80211_BAND_2GHZ);
	wrqu->freq.e = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_set_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक rc = -EINVAL;

	अगर (wrqu->mode == IW_MODE_INFRA ||
	    wrqu->mode == IW_MODE_ADHOC ||
	    wrqu->mode == IW_MODE_AUTO) अणु
		काष्ठा wl3501_card *this = netdev_priv(dev);

		this->net_type = wrqu->mode;
		rc = wl3501_reset(dev);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);

	wrqu->mode = this->net_type;
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_get_sens(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);

	wrqu->sens.value = this->rssi;
	wrqu->sens.disabled = !wrqu->sens.value;
	wrqu->sens.fixed = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_get_range(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;

	/* Set the length (very important क्रम backward compatibility) */
	wrqu->data.length = माप(*range);

	/* Set all the info we करोn't care or don't know about to zero */
	स_रखो(range, 0, माप(*range));

	/* Set the Wireless Extension versions */
	range->we_version_compiled	= WIRELESS_EXT;
	range->we_version_source	= 1;
	range->throughput		= 2 * 1000 * 1000;     /* ~2 Mb/s */
	/* FIXME: study the code to fill in more fields... */
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_set_wap(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक rc = -EINVAL;

	/* FIXME: we support other ARPHRDs...*/
	अगर (wrqu->ap_addr.sa_family != ARPHRD_ETHER)
		जाओ out;
	अगर (is_broadcast_ether_addr(wrqu->ap_addr.sa_data)) अणु
		/* FIXME: rescan? */
	पूर्ण अन्यथा
		स_नकल(this->bssid, wrqu->ap_addr.sa_data, ETH_ALEN);
		/* FIXME: rescan? deassoc & scan? */
	rc = 0;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_wap(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);

	wrqu->ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(wrqu->ap_addr.sa_data, this->bssid, ETH_ALEN);
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_set_scan(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * FIXME: trigger scanning with a reset, yes, I'm lazy
	 */
	वापस wl3501_reset(dev);
पूर्ण

अटल पूर्णांक wl3501_get_scan(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक i;
	अक्षर *current_ev = extra;
	काष्ठा iw_event iwe;

	क्रम (i = 0; i < this->bss_cnt; ++i) अणु
		iwe.cmd			= SIOCGIWAP;
		iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
		स_नकल(iwe.u.ap_addr.sa_data, this->bss_set[i].req.bssid, ETH_ALEN);
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_ADDR_LEN);
		iwe.cmd		  = SIOCGIWESSID;
		iwe.u.data.flags  = 1;
		iwe.u.data.length = this->bss_set[i].req.ssid.el.len;
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe,
						  this->bss_set[i].req.ssid.essid);
		iwe.cmd	   = SIOCGIWMODE;
		iwe.u.mode = this->bss_set[i].req.bss_type;
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_UINT_LEN);
		iwe.cmd = SIOCGIWFREQ;
		iwe.u.freq.m = this->bss_set[i].req.ds_pset.chan;
		iwe.u.freq.e = 0;
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_FREQ_LEN);
		iwe.cmd = SIOCGIWENCODE;
		अगर (this->bss_set[i].req.cap_info & WL3501_MGMT_CAPABILITY_PRIVACY)
			iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
		अन्यथा
			iwe.u.data.flags = IW_ENCODE_DISABLED;
		iwe.u.data.length = 0;
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, शून्य);
	पूर्ण
	/* Length of data */
	wrqu->data.length = (current_ev - extra);
	wrqu->data.flags = 0; /* FIXME: set properly these flags */
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_set_essid(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);

	अगर (wrqu->data.flags) अणु
		iw_set_mgmt_info_element(IW_MGMT_INFO_ELEMENT_SSID,
					 &this->essid.el,
					 extra, wrqu->data.length);
	पूर्ण अन्यथा अणु /* We accept any ESSID */
		iw_set_mgmt_info_element(IW_MGMT_INFO_ELEMENT_SSID,
					 &this->essid.el, "ANY", 3);
	पूर्ण
	वापस wl3501_reset(dev);
पूर्ण

अटल पूर्णांक wl3501_get_essid(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&this->lock, flags);
	wrqu->essid.flags  = 1;
	wrqu->essid.length = this->essid.el.len;
	स_नकल(extra, this->essid.essid, this->essid.el.len);
	spin_unlock_irqrestore(&this->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_set_nick(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);

	अगर (wrqu->data.length > माप(this->nick))
		वापस -E2BIG;
	strlcpy(this->nick, extra, wrqu->data.length);
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_get_nick(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा wl3501_card *this = netdev_priv(dev);

	strlcpy(extra, this->nick, 32);
	wrqu->data.length = म_माप(extra);
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_get_rate(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/*
	 * FIXME: have to see from where to get this info, perhaps this card
	 * works at 1 Mbit/s too... क्रम now leave at 2 Mbit/s that is the most
	 * common with the Planet Access Poपूर्णांकs. -acme
	 */
	wrqu->bitrate.value = 2000000;
	wrqu->bitrate.fixed = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_get_rts_threshold(काष्ठा net_device *dev,
				    काष्ठा iw_request_info *info,
				    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u16 threshold; /* size checked: it is u16 */
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक rc = wl3501_get_mib_value(this, WL3501_MIB_ATTR_RTS_THRESHOLD,
				      &threshold, माप(threshold));
	अगर (!rc) अणु
		wrqu->rts.value = threshold;
		wrqu->rts.disabled = threshold >= 2347;
		wrqu->rts.fixed = 1;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_frag_threshold(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u16 threshold; /* size checked: it is u16 */
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक rc = wl3501_get_mib_value(this, WL3501_MIB_ATTR_FRAG_THRESHOLD,
				      &threshold, माप(threshold));
	अगर (!rc) अणु
		wrqu->frag.value = threshold;
		wrqu->frag.disabled = threshold >= 2346;
		wrqu->frag.fixed = 1;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_txघात(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u16 txघात;
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक rc = wl3501_get_mib_value(this,
				      WL3501_MIB_ATTR_CURRENT_TX_PWR_LEVEL,
				      &txघात, माप(txघात));
	अगर (!rc) अणु
		wrqu->txघातer.value = txघात;
		wrqu->txघातer.disabled = 0;
		/*
		 * From the MIB values I think this can be configurable,
		 * as it lists several tx घातer levels -acme
		 */
		wrqu->txघातer.fixed = 0;
		wrqu->txघातer.flags = IW_TXPOW_MWATT;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_retry(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u8 retry; /* size checked: it is u8 */
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक rc = wl3501_get_mib_value(this,
				      WL3501_MIB_ATTR_LONG_RETRY_LIMIT,
				      &retry, माप(retry));
	अगर (rc)
		जाओ out;
	अगर (wrqu->retry.flags & IW_RETRY_LONG) अणु
		wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
		जाओ set_value;
	पूर्ण
	rc = wl3501_get_mib_value(this, WL3501_MIB_ATTR_SHORT_RETRY_LIMIT,
				  &retry, माप(retry));
	अगर (rc)
		जाओ out;
	wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_SHORT;
set_value:
	wrqu->retry.value = retry;
	wrqu->retry.disabled = 0;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_encode(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u8 implemented, restricted, keys[100], len_keys, tocopy;
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक rc = wl3501_get_mib_value(this,
				      WL3501_MIB_ATTR_PRIV_OPT_IMPLEMENTED,
				      &implemented, माप(implemented));
	अगर (rc)
		जाओ out;
	अगर (!implemented) अणु
		wrqu->encoding.flags = IW_ENCODE_DISABLED;
		जाओ out;
	पूर्ण
	rc = wl3501_get_mib_value(this, WL3501_MIB_ATTR_EXCLUDE_UNENCRYPTED,
				  &restricted, माप(restricted));
	अगर (rc)
		जाओ out;
	wrqu->encoding.flags = restricted ? IW_ENCODE_RESTRICTED :
					    IW_ENCODE_OPEN;
	rc = wl3501_get_mib_value(this, WL3501_MIB_ATTR_WEP_KEY_MAPPINGS_LEN,
				  &len_keys, माप(len_keys));
	अगर (rc)
		जाओ out;
	rc = wl3501_get_mib_value(this, WL3501_MIB_ATTR_WEP_KEY_MAPPINGS,
				  keys, len_keys);
	अगर (rc)
		जाओ out;
	tocopy = min_t(u16, len_keys, wrqu->encoding.length);
	tocopy = min_t(u8, tocopy, 100);
	wrqu->encoding.length = tocopy;
	स_नकल(extra, keys, tocopy);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक wl3501_get_घातer(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u8 pwr_state;
	काष्ठा wl3501_card *this = netdev_priv(dev);
	पूर्णांक rc = wl3501_get_mib_value(this,
				      WL3501_MIB_ATTR_CURRENT_PWR_STATE,
				      &pwr_state, माप(pwr_state));
	अगर (rc)
		जाओ out;
	wrqu->घातer.disabled = !pwr_state;
	wrqu->घातer.flags = IW_POWER_ON;
out:
	वापस rc;
पूर्ण

अटल स्थिर iw_handler	wl3501_handler[] = अणु
	IW_HANDLER(SIOCGIWNAME, wl3501_get_name),
	IW_HANDLER(SIOCSIWFREQ, wl3501_set_freq),
	IW_HANDLER(SIOCGIWFREQ, wl3501_get_freq),
	IW_HANDLER(SIOCSIWMODE, wl3501_set_mode),
	IW_HANDLER(SIOCGIWMODE, wl3501_get_mode),
	IW_HANDLER(SIOCGIWSENS, wl3501_get_sens),
	IW_HANDLER(SIOCGIWRANGE, wl3501_get_range),
	IW_HANDLER(SIOCSIWSPY, iw_handler_set_spy),
	IW_HANDLER(SIOCGIWSPY, iw_handler_get_spy),
	IW_HANDLER(SIOCSIWTHRSPY, iw_handler_set_thrspy),
	IW_HANDLER(SIOCGIWTHRSPY, iw_handler_get_thrspy),
	IW_HANDLER(SIOCSIWAP, wl3501_set_wap),
	IW_HANDLER(SIOCGIWAP, wl3501_get_wap),
	IW_HANDLER(SIOCSIWSCAN, wl3501_set_scan),
	IW_HANDLER(SIOCGIWSCAN, wl3501_get_scan),
	IW_HANDLER(SIOCSIWESSID, wl3501_set_essid),
	IW_HANDLER(SIOCGIWESSID, wl3501_get_essid),
	IW_HANDLER(SIOCSIWNICKN, wl3501_set_nick),
	IW_HANDLER(SIOCGIWNICKN, wl3501_get_nick),
	IW_HANDLER(SIOCGIWRATE, wl3501_get_rate),
	IW_HANDLER(SIOCGIWRTS, wl3501_get_rts_threshold),
	IW_HANDLER(SIOCGIWFRAG, wl3501_get_frag_threshold),
	IW_HANDLER(SIOCGIWTXPOW, wl3501_get_txघात),
	IW_HANDLER(SIOCGIWRETRY, wl3501_get_retry),
	IW_HANDLER(SIOCGIWENCODE, wl3501_get_encode),
	IW_HANDLER(SIOCGIWPOWER, wl3501_get_घातer),
पूर्ण;

अटल स्थिर काष्ठा iw_handler_def wl3501_handler_def = अणु
	.num_standard	= ARRAY_SIZE(wl3501_handler),
	.standard	= (iw_handler *)wl3501_handler,
	.get_wireless_stats = wl3501_get_wireless_stats,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops wl3501_netdev_ops = अणु
	.nकरो_खोलो		= wl3501_खोलो,
	.nकरो_stop		= wl3501_बंद,
	.nकरो_start_xmit		= wl3501_hard_start_xmit,
	.nकरो_tx_समयout		= wl3501_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक wl3501_probe(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा net_device *dev;
	काष्ठा wl3501_card *this;

	/* The io काष्ठाure describes IO port mapping */
	p_dev->resource[0]->end	= 16;
	p_dev->resource[0]->flags	= IO_DATA_PATH_WIDTH_8;

	/* General socket configuration */
	p_dev->config_flags	= CONF_ENABLE_IRQ;
	p_dev->config_index	= 1;

	dev = alloc_etherdev(माप(काष्ठा wl3501_card));
	अगर (!dev)
		जाओ out_link;


	dev->netdev_ops		= &wl3501_netdev_ops;
	dev->watchकरोg_समयo	= 5 * HZ;

	this = netdev_priv(dev);
	this->wireless_data.spy_data = &this->spy_data;
	this->p_dev = p_dev;
	dev->wireless_data	= &this->wireless_data;
	dev->wireless_handlers	= &wl3501_handler_def;
	netअगर_stop_queue(dev);
	p_dev->priv = dev;

	वापस wl3501_config(p_dev);
out_link:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक wl3501_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;
	पूर्णांक i = 0, j, ret;
	काष्ठा wl3501_card *this;

	/* Try allocating IO ports.  This tries a few fixed addresses.  If you
	 * want, you can also पढ़ो the card's config table to pick addresses --
	 * see the serial driver क्रम an example. */
	link->io_lines = 5;

	क्रम (j = 0x280; j < 0x400; j += 0x20) अणु
		/* The '^0x300' is so that we probe 0x300-0x3ff first, then
		 * 0x200-0x2ff, and so on, because this seems safer */
		link->resource[0]->start = j;
		link->resource[1]->start = link->resource[0]->start + 0x10;
		i = pcmcia_request_io(link);
		अगर (i == 0)
			अवरोध;
	पूर्ण
	अगर (i != 0)
		जाओ failed;

	/* Now allocate an पूर्णांकerrupt line. Note that this करोes not actually
	 * assign a handler to the पूर्णांकerrupt. */

	ret = pcmcia_request_irq(link, wl3501_पूर्णांकerrupt);
	अगर (ret)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	dev->irq = link->irq;
	dev->base_addr = link->resource[0]->start;
	SET_NETDEV_DEV(dev, &link->dev);
	अगर (रेजिस्टर_netdev(dev)) अणु
		prपूर्णांकk(KERN_NOTICE "wl3501_cs: register_netdev() failed\n");
		जाओ failed;
	पूर्ण

	this = netdev_priv(dev);

	this->base_addr = dev->base_addr;

	अगर (!wl3501_get_flash_mac_addr(this)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Can't read MAC addr in flash ROM?\n",
		       dev->name);
		unरेजिस्टर_netdev(dev);
		जाओ failed;
	पूर्ण

	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = ((अक्षर *)&this->mac_addr)[i];

	/* prपूर्णांक probe inक्रमmation */
	prपूर्णांकk(KERN_INFO "%s: wl3501 @ 0x%3.3x, IRQ %d, "
	       "MAC addr in flash ROM:%pM\n",
	       dev->name, this->base_addr, (पूर्णांक)dev->irq,
	       dev->dev_addr);
	/*
	 * Initialize card parameters - added by jss
	 */
	this->net_type		= IW_MODE_INFRA;
	this->bss_cnt		= 0;
	this->join_sta_bss	= 0;
	this->adhoc_बार	= 0;
	iw_set_mgmt_info_element(IW_MGMT_INFO_ELEMENT_SSID, &this->essid.el,
				 "ANY", 3);
	this->card_name[0]	= '\0';
	this->firmware_date[0]	= '\0';
	this->rssi		= 255;
	this->chan		= iw_शेष_channel(this->reg_करोमुख्य);
	strlcpy(this->nick, "Planet WL3501", माप(this->nick));
	spin_lock_init(&this->lock);
	init_रुकोqueue_head(&this->रुको);
	netअगर_start_queue(dev);
	वापस 0;

failed:
	wl3501_release(link);
	वापस -ENODEV;
पूर्ण

अटल व्योम wl3501_release(काष्ठा pcmcia_device *link)
अणु
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक wl3501_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	wl3501_pwr_mgmt(netdev_priv(dev), WL3501_SUSPEND);
	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक wl3501_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	wl3501_pwr_mgmt(netdev_priv(dev), WL3501_RESUME);
	अगर (link->खोलो) अणु
		wl3501_reset(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा pcmcia_device_id wl3501_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0xd601, 0x0001),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, wl3501_ids);

अटल काष्ठा pcmcia_driver wl3501_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "wl3501_cs",
	.probe		= wl3501_probe,
	.हटाओ		= wl3501_detach,
	.id_table	= wl3501_ids,
	.suspend	= wl3501_suspend,
	.resume		= wl3501_resume,
पूर्ण;
module_pcmcia_driver(wl3501_driver);

MODULE_AUTHOR("Fox Chen <mhchen@golf.ccl.itri.org.tw>, "
	      "Arnaldo Carvalho de Melo <acme@conectiva.com.br>,"
	      "Gustavo Niemeyer <niemeyer@conectiva.com>");
MODULE_DESCRIPTION("Planet wl3501 wireless driver");
MODULE_LICENSE("GPL");
