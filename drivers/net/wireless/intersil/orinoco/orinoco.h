<शैली गुरु>
/* orinoco.h
 *
 * Common definitions to all pieces of the various orinoco
 * drivers
 */

#अगर_अघोषित _ORINOCO_H
#घोषणा _ORINOCO_H

#घोषणा DRIVER_VERSION "0.15"

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/suspend.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>
#समावेश <net/cfg80211.h>

#समावेश "hermes.h"

/* To enable debug messages */
/*#घोषणा ORINOCO_DEBUG		3*/

#घोषणा WIRELESS_SPY		/* enable iwspy support */

#घोषणा MAX_SCAN_LEN		4096

#घोषणा ORINOCO_SEQ_LEN		8
#घोषणा ORINOCO_MAX_KEY_SIZE	14
#घोषणा ORINOCO_MAX_KEYS	4

काष्ठा orinoco_key अणु
	__le16 len;	/* always stored as little-endian */
	अक्षर data[ORINOCO_MAX_KEY_SIZE];
पूर्ण __packed;

#घोषणा TKIP_KEYLEN	16
#घोषणा MIC_KEYLEN	8

काष्ठा orinoco_tkip_key अणु
	u8 tkip[TKIP_KEYLEN];
	u8 tx_mic[MIC_KEYLEN];
	u8 rx_mic[MIC_KEYLEN];
पूर्ण;

क्रमागत orinoco_alg अणु
	ORINOCO_ALG_NONE,
	ORINOCO_ALG_WEP,
	ORINOCO_ALG_TKIP
पूर्ण;

क्रमागत fwtype अणु
	FIRMWARE_TYPE_AGERE,
	FIRMWARE_TYPE_INTERSIL,
	FIRMWARE_TYPE_SYMBOL
पूर्ण;

काष्ठा firmware;

काष्ठा orinoco_निजी अणु
	व्योम *card;	/* Poपूर्णांकer to card dependent काष्ठाure */
	काष्ठा device *dev;
	पूर्णांक (*hard_reset)(काष्ठा orinoco_निजी *);
	पूर्णांक (*stop_fw)(काष्ठा orinoco_निजी *, पूर्णांक);

	काष्ठा ieee80211_supported_band band;
	काष्ठा ieee80211_channel channels[14];
	u32 cipher_suites[3];

	/* Synchronisation stuff */
	spinlock_t lock;
	पूर्णांक hw_unavailable;
	काष्ठा work_काष्ठा reset_work;

	/* Interrupt tasklets */
	काष्ठा tasklet_काष्ठा rx_tasklet;
	काष्ठा list_head rx_list;

	/* driver state */
	पूर्णांक खोलो;
	u16 last_linkstatus;
	काष्ठा work_काष्ठा join_work;
	काष्ठा work_काष्ठा wevent_work;

	/* Net device stuff */
	काष्ठा net_device *ndev;
	काष्ठा iw_statistics wstats;

	/* Hardware control variables */
	काष्ठा hermes hw;
	u16 txfid;

	/* Capabilities of the hardware/firmware */
	क्रमागत fwtype firmware_type;
	पूर्णांक ibss_port;
	पूर्णांक nicbuf_size;
	u16 channel_mask;

	/* Boolean capabilities */
	अचिन्हित पूर्णांक has_ibss:1;
	अचिन्हित पूर्णांक has_port3:1;
	अचिन्हित पूर्णांक has_wep:1;
	अचिन्हित पूर्णांक has_big_wep:1;
	अचिन्हित पूर्णांक has_mwo:1;
	अचिन्हित पूर्णांक has_pm:1;
	अचिन्हित पूर्णांक has_preamble:1;
	अचिन्हित पूर्णांक has_sensitivity:1;
	अचिन्हित पूर्णांक has_hostscan:1;
	अचिन्हित पूर्णांक has_alt_txcntl:1;
	अचिन्हित पूर्णांक has_ext_scan:1;
	अचिन्हित पूर्णांक has_wpa:1;
	अचिन्हित पूर्णांक करो_fw_करोwnload:1;
	अचिन्हित पूर्णांक broken_disableport:1;
	अचिन्हित पूर्णांक broken_monitor:1;
	अचिन्हित पूर्णांक prefer_port3:1;

	/* Configuration paramaters */
	क्रमागत nl80211_अगरtype iw_mode;
	क्रमागत orinoco_alg encode_alg;
	u16 wep_restrict, tx_key;
	काष्ठा key_params keys[ORINOCO_MAX_KEYS];

	पूर्णांक bitratemode;
	अक्षर nick[IW_ESSID_MAX_SIZE + 1];
	अक्षर desired_essid[IW_ESSID_MAX_SIZE + 1];
	अक्षर desired_bssid[ETH_ALEN];
	पूर्णांक bssid_fixed;
	u16 frag_thresh, mwo_robust;
	u16 channel;
	u16 ap_density, rts_thresh;
	u16 pm_on, pm_mcast, pm_period, pm_समयout;
	u16 preamble;
	u16 लघु_retry_limit, दीर्घ_retry_limit;
	u16 retry_lअगरeसमय;
#अगर_घोषित WIRELESS_SPY
	काष्ठा iw_spy_data spy_data; /* iwspy support */
	काष्ठा iw_खुला_data	wireless_data;
#पूर्ण_अगर

	/* Configuration dependent variables */
	पूर्णांक port_type, createibss;
	पूर्णांक promiscuous, mc_count;

	/* Scanning support */
	काष्ठा cfg80211_scan_request *scan_request;
	काष्ठा work_काष्ठा process_scan;
	काष्ठा list_head scan_list;
	spinlock_t scan_lock; /* protects the scan list */

	/* WPA support */
	u8 *wpa_ie;
	पूर्णांक wpa_ie_len;

	काष्ठा crypto_shash *rx_tfm_mic;
	काष्ठा crypto_shash *tx_tfm_mic;

	अचिन्हित पूर्णांक wpa_enabled:1;
	अचिन्हित पूर्णांक tkip_cm_active:1;
	अचिन्हित पूर्णांक key_mgmt:3;

#अगर defined(CONFIG_HERMES_CACHE_FW_ON_INIT) || defined(CONFIG_PM_SLEEP)
	/* Cached in memory firmware to use during ->resume. */
	स्थिर काष्ठा firmware *cached_pri_fw;
	स्थिर काष्ठा firmware *cached_fw;
#पूर्ण_अगर

	काष्ठा notअगरier_block pm_notअगरier;
पूर्ण;

#अगर_घोषित ORINOCO_DEBUG
बाह्य पूर्णांक orinoco_debug;
#घोषणा DEBUG(n, args...) करो अणु \
	अगर (orinoco_debug > (n)) \
		prपूर्णांकk(KERN_DEBUG args); \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा DEBUG(n, args...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर	/* ORINOCO_DEBUG */

/********************************************************************/
/* Exported prototypes                                              */
/********************************************************************/

काष्ठा orinoco_निजी *alloc_orinocodev(पूर्णांक माप_card, काष्ठा device *device,
					 पूर्णांक (*hard_reset)(काष्ठा orinoco_निजी *),
					 पूर्णांक (*stop_fw)(काष्ठा orinoco_निजी *, पूर्णांक));
व्योम मुक्त_orinocodev(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_init(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_अगर_add(काष्ठा orinoco_निजी *priv, अचिन्हित दीर्घ base_addr,
		   अचिन्हित पूर्णांक irq, स्थिर काष्ठा net_device_ops *ops);
व्योम orinoco_अगर_del(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_up(काष्ठा orinoco_निजी *priv);
व्योम orinoco_करोwn(काष्ठा orinoco_निजी *priv);
irqवापस_t orinoco_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

व्योम __orinoco_ev_info(काष्ठा net_device *dev, काष्ठा hermes *hw);
व्योम __orinoco_ev_rx(काष्ठा net_device *dev, काष्ठा hermes *hw);

पूर्णांक orinoco_process_xmit_skb(काष्ठा sk_buff *skb,
			     काष्ठा net_device *dev,
			     काष्ठा orinoco_निजी *priv,
			     पूर्णांक *tx_control,
			     u8 *mic);

/* Common nकरो functions exported क्रम reuse by orinoco_usb */
पूर्णांक orinoco_खोलो(काष्ठा net_device *dev);
पूर्णांक orinoco_stop(काष्ठा net_device *dev);
व्योम orinoco_set_multicast_list(काष्ठा net_device *dev);
पूर्णांक orinoco_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);
व्योम orinoco_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

/********************************************************************/
/* Locking and synchronization functions                            */
/********************************************************************/

अटल अंतरभूत पूर्णांक orinoco_lock(काष्ठा orinoco_निजी *priv,
			       अचिन्हित दीर्घ *flags)
अणु
	priv->hw.ops->lock_irqsave(&priv->lock, flags);
	अगर (priv->hw_unavailable) अणु
		DEBUG(1, "orinoco_lock() called with hw_unavailable (dev=%p)\n",
		       priv->ndev);
		priv->hw.ops->unlock_irqrestore(&priv->lock, flags);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम orinoco_unlock(काष्ठा orinoco_निजी *priv,
				  अचिन्हित दीर्घ *flags)
अणु
	priv->hw.ops->unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल अंतरभूत व्योम orinoco_lock_irq(काष्ठा orinoco_निजी *priv)
अणु
	priv->hw.ops->lock_irq(&priv->lock);
पूर्ण

अटल अंतरभूत व्योम orinoco_unlock_irq(काष्ठा orinoco_निजी *priv)
अणु
	priv->hw.ops->unlock_irq(&priv->lock);
पूर्ण

/*** Navigate from net_device to orinoco_निजी ***/
अटल अंतरभूत काष्ठा orinoco_निजी *ndev_priv(काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = netdev_priv(dev);
	वापस wdev_priv(wdev);
पूर्ण
#पूर्ण_अगर /* _ORINOCO_H */
