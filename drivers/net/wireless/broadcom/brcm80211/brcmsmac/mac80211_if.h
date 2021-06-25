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

#अगर_अघोषित _BRCM_MAC80211_IF_H_
#घोषणा _BRCM_MAC80211_IF_H_

#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/leds.h>

#समावेश "ucode_loader.h"
#समावेश "led.h"
/*
 * Starting index क्रम 5G rates in the
 * legacy rate table.
 */
#घोषणा BRCMS_LEGACY_5G_RATE_OFFSET	4

/* sofपंचांगac ioctl definitions */
#घोषणा BRCMS_SET_SHORTSLOT_OVERRIDE		146

काष्ठा brcms_समयr अणु
	काष्ठा delayed_work dly_wrk;
	काष्ठा brcms_info *wl;
	व्योम (*fn) (व्योम *);	/* function called upon expiration */
	व्योम *arg;		/* fixed argument provided to called function */
	uपूर्णांक ms;
	bool periodic;
	bool set;		/* indicates अगर समयr is active */
	काष्ठा brcms_समयr *next;	/* क्रम मुक्तing on unload */
#अगर_घोषित DEBUG
	अक्षर *name;		/* Description of the समयr */
#पूर्ण_अगर
पूर्ण;

काष्ठा brcms_अगर अणु
	uपूर्णांक subunit;		/* WDS/BSS unit */
	काष्ठा pci_dev *pci_dev;
पूर्ण;

#घोषणा MAX_FW_IMAGES		4
काष्ठा brcms_firmware अणु
	u32 fw_cnt;
	स्थिर काष्ठा firmware *fw_bin[MAX_FW_IMAGES];
	स्थिर काष्ठा firmware *fw_hdr[MAX_FW_IMAGES];
	u32 hdr_num_entries[MAX_FW_IMAGES];
पूर्ण;

काष्ठा brcms_info अणु
	काष्ठा brcms_pub *pub;		/* poपूर्णांकer to खुला wlc state */
	काष्ठा brcms_c_info *wlc;	/* poपूर्णांकer to निजी common data */
	u32 magic;

	पूर्णांक irq;

	spinlock_t lock;	/* per-device perimeter lock */
	spinlock_t isr_lock;	/* per-device ISR synchronization lock */

	/* tx flush */
	रुको_queue_head_t tx_flush_wq;

	/* समयr related fields */
	atomic_t callbacks;	/* # outstanding callback functions */
	काष्ठा brcms_समयr *समयrs;	/* समयr cleanup queue */

	काष्ठा tasklet_काष्ठा tasklet;	/* dpc tasklet */
	bool resched;		/* dpc needs to be and is rescheduled */
	काष्ठा brcms_firmware fw;
	काष्ठा wiphy *wiphy;
	काष्ठा brcms_ucode ucode;
	bool mute_tx;
	काष्ठा brcms_led radio_led;
	काष्ठा led_classdev led_dev;
पूर्ण;

/* misc callbacks */
व्योम brcms_init(काष्ठा brcms_info *wl);
uपूर्णांक brcms_reset(काष्ठा brcms_info *wl);
व्योम brcms_पूर्णांकrson(काष्ठा brcms_info *wl);
u32 brcms_पूर्णांकrsoff(काष्ठा brcms_info *wl);
व्योम brcms_पूर्णांकrsrestore(काष्ठा brcms_info *wl, u32 macपूर्णांकmask);
पूर्णांक brcms_up(काष्ठा brcms_info *wl);
व्योम brcms_करोwn(काष्ठा brcms_info *wl);
व्योम brcms_txflowcontrol(काष्ठा brcms_info *wl, काष्ठा brcms_अगर *wlअगर,
			 bool state, पूर्णांक prio);
bool brcms_rfसमाप्त_set_hw_state(काष्ठा brcms_info *wl);

/* समयr functions */
काष्ठा brcms_समयr *brcms_init_समयr(काष्ठा brcms_info *wl,
				     व्योम (*fn) (व्योम *arg), व्योम *arg,
				     स्थिर अक्षर *name);
व्योम brcms_मुक्त_समयr(काष्ठा brcms_समयr *समयr);
व्योम brcms_add_समयr(काष्ठा brcms_समयr *समयr, uपूर्णांक ms, पूर्णांक periodic);
bool brcms_del_समयr(काष्ठा brcms_समयr *समयr);
व्योम brcms_dpc(काष्ठा tasklet_काष्ठा *t);
व्योम brcms_समयr(काष्ठा brcms_समयr *t);
व्योम brcms_fatal_error(काष्ठा brcms_info *wl);

#पूर्ण_अगर				/* _BRCM_MAC80211_IF_H_ */
