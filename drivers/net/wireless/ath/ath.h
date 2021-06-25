<शैली गुरु>
/*
 * Copyright (c) 2008-2009 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित ATH_H
#घोषणा ATH_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/spinlock.h>
#समावेश <net/mac80211.h>

/*
 * The key cache is used क्रम h/w cipher state and also क्रम
 * tracking station state such as the current tx antenna.
 * We also setup a mapping table between key cache slot indices
 * and station state to लघु-circuit node lookups on rx.
 * Dअगरferent parts have dअगरferent size key caches.  We handle
 * up to ATH_KEYMAX entries (could dynamically allocate state).
 */
#घोषणा	ATH_KEYMAX	        128     /* max key cache size we handle */

काष्ठा ath_ani अणु
	bool calकरोne;
	अचिन्हित पूर्णांक दीर्घcal_समयr;
	अचिन्हित पूर्णांक लघुcal_समयr;
	अचिन्हित पूर्णांक resetcal_समयr;
	अचिन्हित पूर्णांक checkani_समयr;
	काष्ठा समयr_list समयr;
पूर्ण;

काष्ठा ath_cycle_counters अणु
	u32 cycles;
	u32 rx_busy;
	u32 rx_frame;
	u32 tx_frame;
पूर्ण;

क्रमागत ath_device_state अणु
	ATH_HW_UNAVAILABLE,
	ATH_HW_INITIALIZED,
पूर्ण;

क्रमागत ath_op_flags अणु
	ATH_OP_INVALID,
	ATH_OP_BEACONS,
	ATH_OP_ANI_RUN,
	ATH_OP_PRIM_STA_VIF,
	ATH_OP_HW_RESET,
	ATH_OP_SCANNING,
	ATH_OP_MULTI_CHANNEL,
	ATH_OP_WOW_ENABLED,
पूर्ण;

क्रमागत ath_bus_type अणु
	ATH_PCI,
	ATH_AHB,
	ATH_USB,
पूर्ण;

काष्ठा reg_dmn_pair_mapping अणु
	u16 reg_करोमुख्य;
	u16 reg_5ghz_ctl;
	u16 reg_2ghz_ctl;
पूर्ण;

काष्ठा ath_regulatory अणु
	अक्षर alpha2[2];
	क्रमागत nl80211_dfs_regions region;
	u16 country_code;
	u16 max_घातer_level;
	u16 current_rd;
	पूर्णांक16_t घातer_limit;
	काष्ठा reg_dmn_pair_mapping *regpair;
पूर्ण;

क्रमागत ath_crypt_caps अणु
	ATH_CRYPT_CAP_CIPHER_AESCCM		= BIT(0),
	ATH_CRYPT_CAP_MIC_COMBINED		= BIT(1),
पूर्ण;

काष्ठा ath_keyval अणु
	u8 kv_type;
	u8 kv_pad;
	u16 kv_len;
	u8 kv_val[16]; /* TK */
	u8 kv_mic[8]; /* Michael MIC key */
	u8 kv_txmic[8]; /* Michael MIC TX key (used only अगर the hardware
			 * supports both MIC keys in the same key cache entry;
			 * in that हाल, kv_mic is the RX key) */
पूर्ण;

क्रमागत ath_cipher अणु
	ATH_CIPHER_WEP = 0,
	ATH_CIPHER_AES_OCB = 1,
	ATH_CIPHER_AES_CCM = 2,
	ATH_CIPHER_CKIP = 3,
	ATH_CIPHER_TKIP = 4,
	ATH_CIPHER_CLR = 5,
	ATH_CIPHER_MIC = 127
पूर्ण;

/**
 * काष्ठा ath_ops - Register पढ़ो/ग_लिखो operations
 *
 * @पढ़ो: Register पढ़ो
 * @multi_पढ़ो: Multiple रेजिस्टर पढ़ो
 * @ग_लिखो: Register ग_लिखो
 * @enable_ग_लिखो_buffer: Enable multiple रेजिस्टर ग_लिखोs
 * @ग_लिखो_flush: flush buffered रेजिस्टर ग_लिखोs and disable buffering
 */
काष्ठा ath_ops अणु
	अचिन्हित पूर्णांक (*पढ़ो)(व्योम *, u32 reg_offset);
	व्योम (*multi_पढ़ो)(व्योम *, u32 *addr, u32 *val, u16 count);
	व्योम (*ग_लिखो)(व्योम *, u32 val, u32 reg_offset);
	व्योम (*enable_ग_लिखो_buffer)(व्योम *);
	व्योम (*ग_लिखो_flush) (व्योम *);
	u32 (*rmw)(व्योम *, u32 reg_offset, u32 set, u32 clr);
	व्योम (*enable_rmw_buffer)(व्योम *);
	व्योम (*rmw_flush) (व्योम *);

पूर्ण;

काष्ठा ath_common;
काष्ठा ath_bus_ops;

काष्ठा ath_ps_ops अणु
	व्योम (*wakeup)(काष्ठा ath_common *common);
	व्योम (*restore)(काष्ठा ath_common *common);
पूर्ण;

काष्ठा ath_common अणु
	व्योम *ah;
	व्योम *priv;
	काष्ठा ieee80211_hw *hw;
	पूर्णांक debug_mask;
	क्रमागत ath_device_state state;
	अचिन्हित दीर्घ op_flags;

	काष्ठा ath_ani ani;

	u16 cachelsz;
	u16 curaid;
	u8 macaddr[ETH_ALEN];
	u8 curbssid[ETH_ALEN] __aligned(2);
	u8 bssidmask[ETH_ALEN];

	u32 rx_bufsize;

	u32 keymax;
	DECLARE_BITMAP(keymap, ATH_KEYMAX);
	DECLARE_BITMAP(tkip_keymap, ATH_KEYMAX);
	DECLARE_BITMAP(ccmp_keymap, ATH_KEYMAX);
	क्रमागत ath_crypt_caps crypt_caps;

	अचिन्हित पूर्णांक घड़ीrate;

	spinlock_t cc_lock;
	काष्ठा ath_cycle_counters cc_ani;
	काष्ठा ath_cycle_counters cc_survey;

	काष्ठा ath_regulatory regulatory;
	काष्ठा ath_regulatory reg_world_copy;
	स्थिर काष्ठा ath_ops *ops;
	स्थिर काष्ठा ath_bus_ops *bus_ops;
	स्थिर काष्ठा ath_ps_ops *ps_ops;

	bool btcoex_enabled;
	bool disable_ani;
	bool bt_ant_भागersity;

	पूर्णांक last_rssi;
	काष्ठा ieee80211_supported_band sbands[NUM_NL80211_BANDS];
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा ath_ps_ops *ath_ps_ops(काष्ठा ath_common *common)
अणु
	वापस common->ps_ops;
पूर्ण

काष्ठा sk_buff *ath_rxbuf_alloc(काष्ठा ath_common *common,
				u32 len,
				gfp_t gfp_mask);
bool ath_is_mybeacon(काष्ठा ath_common *common, काष्ठा ieee80211_hdr *hdr);

व्योम ath_hw_setbssidmask(काष्ठा ath_common *common);
व्योम ath_key_delete(काष्ठा ath_common *common, u8 hw_key_idx);
पूर्णांक ath_key_config(काष्ठा ath_common *common,
			  काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key);
bool ath_hw_keyreset(काष्ठा ath_common *common, u16 entry);
bool ath_hw_keyseपंचांगac(काष्ठा ath_common *common, u16 entry, स्थिर u8 *mac);
व्योम ath_hw_cycle_counters_update(काष्ठा ath_common *common);
पूर्णांक32_t ath_hw_get_listen_समय(काष्ठा ath_common *common);

__म_लिखो(3, 4)
व्योम ath_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा ath_common *common,
		स्थिर अक्षर *fmt, ...);

#घोषणा ath_emerg(common, fmt, ...)				\
	ath_prपूर्णांकk(KERN_EMERG, common, fmt, ##__VA_ARGS__)
#घोषणा ath_alert(common, fmt, ...)				\
	ath_prपूर्णांकk(KERN_ALERT, common, fmt, ##__VA_ARGS__)
#घोषणा ath_crit(common, fmt, ...)				\
	ath_prपूर्णांकk(KERN_CRIT, common, fmt, ##__VA_ARGS__)
#घोषणा ath_err(common, fmt, ...)				\
	ath_prपूर्णांकk(KERN_ERR, common, fmt, ##__VA_ARGS__)
#घोषणा ath_warn(common, fmt, ...)				\
	ath_prपूर्णांकk(KERN_WARNING, common, fmt, ##__VA_ARGS__)
#घोषणा ath_notice(common, fmt, ...)				\
	ath_prपूर्णांकk(KERN_NOTICE, common, fmt, ##__VA_ARGS__)
#घोषणा ath_info(common, fmt, ...)				\
	ath_prपूर्णांकk(KERN_INFO, common, fmt, ##__VA_ARGS__)

/**
 * क्रमागत ath_debug_level - atheros wireless debug level
 *
 * @ATH_DBG_RESET: reset processing
 * @ATH_DBG_QUEUE: hardware queue management
 * @ATH_DBG_EEPROM: eeprom processing
 * @ATH_DBG_CALIBRATE: periodic calibration
 * @ATH_DBG_INTERRUPT: पूर्णांकerrupt processing
 * @ATH_DBG_REGULATORY: regulatory processing
 * @ATH_DBG_ANI: adaptive noise immunitive processing
 * @ATH_DBG_XMIT: basic xmit operation
 * @ATH_DBG_BEACON: beacon handling
 * @ATH_DBG_CONFIG: configuration of the hardware
 * @ATH_DBG_FATAL: fatal errors, this is the शेष, DBG_DEFAULT
 * @ATH_DBG_PS: घातer save processing
 * @ATH_DBG_HWTIMER: hardware समयr handling
 * @ATH_DBG_BTCOEX: bluetooth coexistance
 * @ATH_DBG_BSTUCK: stuck beacons
 * @ATH_DBG_MCI: Message Coexistence Interface, a निजी protocol
 *	used exclusively क्रम WLAN-BT coexistence starting from
 *	AR9462.
 * @ATH_DBG_DFS: radar datection
 * @ATH_DBG_WOW: Wake on Wireless
 * @ATH_DBG_DYNACK: dynack handling
 * @ATH_DBG_SPECTRAL_SCAN: FFT spectral scan
 * @ATH_DBG_ANY: enable all debugging
 *
 * The debug level is used to control the amount and type of debugging output
 * we want to see. Each driver has its own method क्रम enabling debugging and
 * modअगरying debug level states -- but this is typically करोne through a
 * module parameter 'debug' along with a respective 'debug' debugfs file
 * entry.
 */
क्रमागत ATH_DEBUG अणु
	ATH_DBG_RESET		= 0x00000001,
	ATH_DBG_QUEUE		= 0x00000002,
	ATH_DBG_EEPROM		= 0x00000004,
	ATH_DBG_CALIBRATE	= 0x00000008,
	ATH_DBG_INTERRUPT	= 0x00000010,
	ATH_DBG_REGULATORY	= 0x00000020,
	ATH_DBG_ANI		= 0x00000040,
	ATH_DBG_XMIT		= 0x00000080,
	ATH_DBG_BEACON		= 0x00000100,
	ATH_DBG_CONFIG		= 0x00000200,
	ATH_DBG_FATAL		= 0x00000400,
	ATH_DBG_PS		= 0x00000800,
	ATH_DBG_BTCOEX		= 0x00001000,
	ATH_DBG_WMI		= 0x00002000,
	ATH_DBG_BSTUCK		= 0x00004000,
	ATH_DBG_MCI		= 0x00008000,
	ATH_DBG_DFS		= 0x00010000,
	ATH_DBG_WOW		= 0x00020000,
	ATH_DBG_CHAN_CTX	= 0x00040000,
	ATH_DBG_DYNACK		= 0x00080000,
	ATH_DBG_SPECTRAL_SCAN	= 0x00100000,
	ATH_DBG_ANY		= 0xffffffff
पूर्ण;

#घोषणा ATH_DBG_DEFAULT (ATH_DBG_FATAL)
#घोषणा ATH_DBG_MAX_LEN 512

#अगर_घोषित CONFIG_ATH_DEBUG

#घोषणा ath_dbg(common, dbg_mask, fmt, ...)				\
करो अणु									\
	अगर ((common)->debug_mask & ATH_DBG_##dbg_mask)			\
		ath_prपूर्णांकk(KERN_DEBUG, common, fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा ATH_DBG_WARN(foo, arg...) WARN(foo, arg)
#घोषणा ATH_DBG_WARN_ON_ONCE(foo) WARN_ON_ONCE(foo)

#अन्यथा

अटल अंतरभूत  __attribute__ ((क्रमmat (म_लिखो, 3, 4)))
व्योम _ath_dbg(काष्ठा ath_common *common, क्रमागत ATH_DEBUG dbg_mask,
	     स्थिर अक्षर *fmt, ...)
अणु
पूर्ण
#घोषणा ath_dbg(common, dbg_mask, fmt, ...)				\
	_ath_dbg(common, ATH_DBG_##dbg_mask, fmt, ##__VA_ARGS__)

#घोषणा ATH_DBG_WARN(foo, arg...) करो अणुपूर्ण जबतक (0)
#घोषणा ATH_DBG_WARN_ON_ONCE(foo) (अणु				\
	पूर्णांक __ret_warn_once = !!(foo);				\
	unlikely(__ret_warn_once);				\
पूर्ण)

#पूर्ण_अगर /* CONFIG_ATH_DEBUG */

/** Returns string describing opmode, or शून्य अगर unknown mode. */
#अगर_घोषित CONFIG_ATH_DEBUG
स्थिर अक्षर *ath_opmode_to_string(क्रमागत nl80211_अगरtype opmode);
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *ath_opmode_to_string(क्रमागत nl80211_अगरtype opmode)
अणु
	वापस "UNKNOWN";
पूर्ण
#पूर्ण_अगर

बाह्य स्थिर अक्षर *ath_bus_type_strings[];
अटल अंतरभूत स्थिर अक्षर *ath_bus_type_to_string(क्रमागत ath_bus_type bustype)
अणु
	वापस ath_bus_type_strings[bustype];
पूर्ण

#पूर्ण_अगर /* ATH_H */
