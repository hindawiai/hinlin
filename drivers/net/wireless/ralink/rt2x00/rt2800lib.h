<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2010 Willow Garage <http://www.willowgarage.com>
	Copyright (C) 2010 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2009 Bartlomiej Zolnierkiewicz

 */

#अगर_अघोषित RT2800LIB_H
#घोषणा RT2800LIB_H

/*
 * Hardware has 255 WCID table entries. First 32 entries are reserved क्रम
 * shared keys. Since parts of the pairwise key table might be shared with
 * the beacon frame buffers 6 & 7 we could only use the first 222 entries.
 */
#घोषणा WCID_START	33
#घोषणा WCID_END	222
#घोषणा STA_IDS_SIZE	(WCID_END - WCID_START + 2)

/* RT2800 driver data काष्ठाure */
काष्ठा rt2800_drv_data अणु
	u8 calibration_bw20;
	u8 calibration_bw40;
	अक्षर rx_calibration_bw20;
	अक्षर rx_calibration_bw40;
	अक्षर tx_calibration_bw20;
	अक्षर tx_calibration_bw40;
	u8 bbp25;
	u8 bbp26;
	u8 txmixer_gain_24g;
	u8 txmixer_gain_5g;
	u8 max_psdu;
	अचिन्हित पूर्णांक tbtt_tick;
	अचिन्हित पूर्णांक ampdu_factor_cnt[4];
	DECLARE_BITMAP(sta_ids, STA_IDS_SIZE);
	काष्ठा ieee80211_sta *wcid_to_sta[STA_IDS_SIZE];
पूर्ण;

काष्ठा rt2800_ops अणु
	u32 (*रेजिस्टर_पढ़ो)(काष्ठा rt2x00_dev *rt2x00dev,
			      स्थिर अचिन्हित पूर्णांक offset);
	u32 (*रेजिस्टर_पढ़ो_lock)(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर अचिन्हित पूर्णांक offset);
	व्योम (*रेजिस्टर_ग_लिखो)(काष्ठा rt2x00_dev *rt2x00dev,
			       स्थिर अचिन्हित पूर्णांक offset, u32 value);
	व्योम (*रेजिस्टर_ग_लिखो_lock)(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर अचिन्हित पूर्णांक offset, u32 value);

	व्योम (*रेजिस्टर_multiपढ़ो)(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर अचिन्हित पूर्णांक offset,
				   व्योम *value, स्थिर u32 length);
	व्योम (*रेजिस्टर_multiग_लिखो)(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर अचिन्हित पूर्णांक offset,
				    स्थिर व्योम *value, स्थिर u32 length);

	पूर्णांक (*regbusy_पढ़ो)(काष्ठा rt2x00_dev *rt2x00dev,
			    स्थिर अचिन्हित पूर्णांक offset,
			    स्थिर काष्ठा rt2x00_field32 field, u32 *reg);

	पूर्णांक (*पढ़ो_eeprom)(काष्ठा rt2x00_dev *rt2x00dev);
	bool (*hwcrypt_disabled)(काष्ठा rt2x00_dev *rt2x00dev);

	पूर्णांक (*drv_ग_लिखो_firmware)(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर u8 *data, स्थिर माप_प्रकार len);
	पूर्णांक (*drv_init_रेजिस्टरs)(काष्ठा rt2x00_dev *rt2x00dev);
	__le32 *(*drv_get_txwi)(काष्ठा queue_entry *entry);
	अचिन्हित पूर्णांक (*drv_get_dma_करोne)(काष्ठा data_queue *queue);
पूर्ण;

अटल अंतरभूत u32 rt2800_रेजिस्टर_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
				       स्थिर अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	वापस rt2800ops->रेजिस्टर_पढ़ो(rt2x00dev, offset);
पूर्ण

अटल अंतरभूत u32 rt2800_रेजिस्टर_पढ़ो_lock(काष्ठा rt2x00_dev *rt2x00dev,
					    स्थिर अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	वापस rt2800ops->रेजिस्टर_पढ़ो_lock(rt2x00dev, offset);
पूर्ण

अटल अंतरभूत व्योम rt2800_रेजिस्टर_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
					 स्थिर अचिन्हित पूर्णांक offset,
					 u32 value)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	rt2800ops->रेजिस्टर_ग_लिखो(rt2x00dev, offset, value);
पूर्ण

अटल अंतरभूत व्योम rt2800_रेजिस्टर_ग_लिखो_lock(काष्ठा rt2x00_dev *rt2x00dev,
					      स्थिर अचिन्हित पूर्णांक offset,
					      u32 value)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	rt2800ops->रेजिस्टर_ग_लिखो_lock(rt2x00dev, offset, value);
पूर्ण

अटल अंतरभूत व्योम rt2800_रेजिस्टर_multiपढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
					     स्थिर अचिन्हित पूर्णांक offset,
					     व्योम *value, स्थिर u32 length)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	rt2800ops->रेजिस्टर_multiपढ़ो(rt2x00dev, offset, value, length);
पूर्ण

अटल अंतरभूत व्योम rt2800_रेजिस्टर_multiग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
					      स्थिर अचिन्हित पूर्णांक offset,
					      स्थिर व्योम *value,
					      स्थिर u32 length)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	rt2800ops->रेजिस्टर_multiग_लिखो(rt2x00dev, offset, value, length);
पूर्ण

अटल अंतरभूत पूर्णांक rt2800_regbusy_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
				      स्थिर अचिन्हित पूर्णांक offset,
				      स्थिर काष्ठा rt2x00_field32 field,
				      u32 *reg)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	वापस rt2800ops->regbusy_पढ़ो(rt2x00dev, offset, field, reg);
पूर्ण

अटल अंतरभूत पूर्णांक rt2800_पढ़ो_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	वापस rt2800ops->पढ़ो_eeprom(rt2x00dev);
पूर्ण

अटल अंतरभूत bool rt2800_hwcrypt_disabled(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	वापस rt2800ops->hwcrypt_disabled(rt2x00dev);
पूर्ण

अटल अंतरभूत पूर्णांक rt2800_drv_ग_लिखो_firmware(काष्ठा rt2x00_dev *rt2x00dev,
					    स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	वापस rt2800ops->drv_ग_लिखो_firmware(rt2x00dev, data, len);
पूर्ण

अटल अंतरभूत पूर्णांक rt2800_drv_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	वापस rt2800ops->drv_init_रेजिस्टरs(rt2x00dev);
पूर्ण

अटल अंतरभूत __le32 *rt2800_drv_get_txwi(काष्ठा queue_entry *entry)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = entry->queue->rt2x00dev->ops->drv;

	वापस rt2800ops->drv_get_txwi(entry);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rt2800_drv_get_dma_करोne(काष्ठा data_queue *queue)
अणु
	स्थिर काष्ठा rt2800_ops *rt2800ops = queue->rt2x00dev->ops->drv;

	वापस rt2800ops->drv_get_dma_करोne(queue);
पूर्ण

व्योम rt2800_mcu_request(काष्ठा rt2x00_dev *rt2x00dev,
			स्थिर u8 command, स्थिर u8 token,
			स्थिर u8 arg0, स्थिर u8 arg1);

पूर्णांक rt2800_रुको_csr_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev);
पूर्णांक rt2800_रुको_wpdma_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev);

पूर्णांक rt2800_check_firmware(काष्ठा rt2x00_dev *rt2x00dev,
			  स्थिर u8 *data, स्थिर माप_प्रकार len);
पूर्णांक rt2800_load_firmware(काष्ठा rt2x00_dev *rt2x00dev,
			 स्थिर u8 *data, स्थिर माप_प्रकार len);

व्योम rt2800_ग_लिखो_tx_data(काष्ठा queue_entry *entry,
			  काष्ठा txentry_desc *txdesc);
व्योम rt2800_process_rxwi(काष्ठा queue_entry *entry, काष्ठा rxकरोne_entry_desc *txdesc);

व्योम rt2800_txकरोne_entry(काष्ठा queue_entry *entry, u32 status, __le32 *txwi,
			 bool match);
व्योम rt2800_txकरोne(काष्ठा rt2x00_dev *rt2x00dev, अचिन्हित पूर्णांक quota);
व्योम rt2800_txकरोne_nostatus(काष्ठा rt2x00_dev *rt2x00dev);
bool rt2800_txstatus_समयout(काष्ठा rt2x00_dev *rt2x00dev);
bool rt2800_txstatus_pending(काष्ठा rt2x00_dev *rt2x00dev);

व्योम rt2800_watchकरोg(काष्ठा rt2x00_dev *rt2x00dev);

व्योम rt2800_ग_लिखो_beacon(काष्ठा queue_entry *entry, काष्ठा txentry_desc *txdesc);
व्योम rt2800_clear_beacon(काष्ठा queue_entry *entry);

बाह्य स्थिर काष्ठा rt2x00debug rt2800_rt2x00debug;

पूर्णांक rt2800_rfसमाप्त_poll(काष्ठा rt2x00_dev *rt2x00dev);
पूर्णांक rt2800_config_shared_key(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा rt2x00lib_crypto *crypto,
			     काष्ठा ieee80211_key_conf *key);
पूर्णांक rt2800_config_pairwise_key(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा rt2x00lib_crypto *crypto,
			       काष्ठा ieee80211_key_conf *key);
पूर्णांक rt2800_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta);
पूर्णांक rt2800_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_sta *sta);
व्योम rt2800_config_filter(काष्ठा rt2x00_dev *rt2x00dev,
			  स्थिर अचिन्हित पूर्णांक filter_flags);
व्योम rt2800_config_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
			काष्ठा rt2x00पूर्णांकf_conf *conf, स्थिर अचिन्हित पूर्णांक flags);
व्योम rt2800_config_erp(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा rt2x00lib_erp *erp,
		       u32 changed);
व्योम rt2800_config_ant(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा antenna_setup *ant);
व्योम rt2800_config(काष्ठा rt2x00_dev *rt2x00dev,
		   काष्ठा rt2x00lib_conf *libconf,
		   स्थिर अचिन्हित पूर्णांक flags);
व्योम rt2800_link_stats(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा link_qual *qual);
व्योम rt2800_reset_tuner(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा link_qual *qual);
व्योम rt2800_link_tuner(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा link_qual *qual,
		       स्थिर u32 count);
व्योम rt2800_gain_calibration(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2800_vco_calibration(काष्ठा rt2x00_dev *rt2x00dev);

पूर्णांक rt2800_enable_radio(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2800_disable_radio(काष्ठा rt2x00_dev *rt2x00dev);

पूर्णांक rt2800_efuse_detect(काष्ठा rt2x00_dev *rt2x00dev);
पूर्णांक rt2800_पढ़ो_eeprom_efuse(काष्ठा rt2x00_dev *rt2x00dev);

पूर्णांक rt2800_probe_hw(काष्ठा rt2x00_dev *rt2x00dev);

व्योम rt2800_get_key_seq(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_key_conf *key,
			काष्ठा ieee80211_key_seq *seq);
पूर्णांक rt2800_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value);
पूर्णांक rt2800_conf_tx(काष्ठा ieee80211_hw *hw,
		   काष्ठा ieee80211_vअगर *vअगर, u16 queue_idx,
		   स्थिर काष्ठा ieee80211_tx_queue_params *params);
u64 rt2800_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक rt2800_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_ampdu_params *params);
पूर्णांक rt2800_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
		      काष्ठा survey_info *survey);
व्योम rt2800_disable_wpdma(काष्ठा rt2x00_dev *rt2x00dev);

व्योम rt2800_get_txwi_rxwi_size(काष्ठा rt2x00_dev *rt2x00dev,
			       अचिन्हित लघु *txwi_size,
			       अचिन्हित लघु *rxwi_size);
व्योम rt2800_pre_reset_hw(काष्ठा rt2x00_dev *rt2x00dev);

#पूर्ण_अगर /* RT2800LIB_H */
