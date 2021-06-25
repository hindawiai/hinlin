<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _BRCM_SCB_H_
#घोषणा _BRCM_SCB_H_

#समावेश <linux/अगर_ether.h>
#समावेश <brcmu_utils.h>
#समावेश <defs.h>
#समावेश "types.h"

#घोषणा AMPDU_TX_BA_MAX_WSIZE	64	/* max Tx ba winकरोw size (in pdu) */

#घोषणा AMPDU_MAX_SCB_TID	NUMPRIO

/* scb flags */
#घोषणा SCB_WMECAP		0x0040
#घोषणा SCB_HTCAP		0x10000	/* HT (MIMO) capable device */
#घोषणा SCB_IS40		0x80000	/* 40MHz capable */
#घोषणा SCB_STBCCAP		0x40000000	/* STBC Capable */

#घोषणा SCB_MAGIC	0xbeefcafe

/* काष्ठाure to store per-tid state क्रम the ampdu initiator */
काष्ठा scb_ampdu_tid_ini अणु
	u8 tid;		  /* initiator tid क्रम easy lookup */
	/* tx retry count; indexed by seq modulo */
	u8 txretry[AMPDU_TX_BA_MAX_WSIZE];
	काष्ठा scb *scb;  /* backptr क्रम easy lookup */
	u8 ba_wsize;	  /* negotiated ba winकरोw size (in pdu) */
पूर्ण;

काष्ठा scb_ampdu अणु
	काष्ठा scb *scb;	/* back poपूर्णांकer क्रम easy reference */
	u8 mpdu_density;	/* mpdu density */
	u8 max_pdu;		/* max pdus allowed in ampdu */
	u8 release;		/* # of mpdus released at a समय */
	u16 min_len;		/* min mpdu len to support the density */
	u32 max_rx_ampdu_bytes;	/* max ampdu rcv length; 8k, 16k, 32k, 64k */

	/*
	 * This could easily be a ini[] poपूर्णांकer and we keep this info in wl
	 * itself instead of having mac80211 hold it क्रम us. Also could be made
	 * dynamic per tid instead of अटल.
	 */
	/* initiator info - per tid (NUMPRIO): */
	काष्ठा scb_ampdu_tid_ini ini[AMPDU_MAX_SCB_TID];
पूर्ण;

/* station control block - one per remote MAC address */
काष्ठा scb अणु
	u32 magic;
	u32 flags;	/* various bit flags as defined below */
	u32 flags2;	/* various bit flags2 as defined below */
	u8 state;	/* current state bitfield of auth/assoc process */
	u8 ea[ETH_ALEN];	/* station address */
	uपूर्णांक fragresid[NUMPRIO];/* #bytes unused in frag buffer per prio */

	u16 seqctl[NUMPRIO];	/* seqctl of last received frame (क्रम dups) */
	/* seqctl of last received frame (क्रम dups) क्रम non-QoS data and
	 * management */
	u16 seqctl_nonqos;
	u16 seqnum[NUMPRIO];/* WME: driver मुख्यtained sw seqnum per priority */

	काष्ठा scb_ampdu scb_ampdu;	/* AMPDU state including per tid info */
पूर्ण;

#पूर्ण_अगर				/* _BRCM_SCB_H_ */
