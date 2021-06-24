<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित	__RTW_HCI_H__
#घोषणा __RTW_HCI_H__

/* ops क्रम PCI, USB and SDIO */
काष्ठा rtw_hci_ops अणु
	पूर्णांक (*tx_ग_लिखो)(काष्ठा rtw_dev *rtwdev,
			काष्ठा rtw_tx_pkt_info *pkt_info,
			काष्ठा sk_buff *skb);
	व्योम (*tx_kick_off)(काष्ठा rtw_dev *rtwdev);
	व्योम (*flush_queues)(काष्ठा rtw_dev *rtwdev, u32 queues, bool drop);
	पूर्णांक (*setup)(काष्ठा rtw_dev *rtwdev);
	पूर्णांक (*start)(काष्ठा rtw_dev *rtwdev);
	व्योम (*stop)(काष्ठा rtw_dev *rtwdev);
	व्योम (*deep_ps)(काष्ठा rtw_dev *rtwdev, bool enter);
	व्योम (*link_ps)(काष्ठा rtw_dev *rtwdev, bool enter);
	व्योम (*पूर्णांकerface_cfg)(काष्ठा rtw_dev *rtwdev);

	पूर्णांक (*ग_लिखो_data_rsvd_page)(काष्ठा rtw_dev *rtwdev, u8 *buf, u32 size);
	पूर्णांक (*ग_लिखो_data_h2c)(काष्ठा rtw_dev *rtwdev, u8 *buf, u32 size);

	u8 (*पढ़ो8)(काष्ठा rtw_dev *rtwdev, u32 addr);
	u16 (*पढ़ो16)(काष्ठा rtw_dev *rtwdev, u32 addr);
	u32 (*पढ़ो32)(काष्ठा rtw_dev *rtwdev, u32 addr);
	व्योम (*ग_लिखो8)(काष्ठा rtw_dev *rtwdev, u32 addr, u8 val);
	व्योम (*ग_लिखो16)(काष्ठा rtw_dev *rtwdev, u32 addr, u16 val);
	व्योम (*ग_लिखो32)(काष्ठा rtw_dev *rtwdev, u32 addr, u32 val);
पूर्ण;

अटल अंतरभूत पूर्णांक rtw_hci_tx_ग_लिखो(काष्ठा rtw_dev *rtwdev,
				   काष्ठा rtw_tx_pkt_info *pkt_info,
				   काष्ठा sk_buff *skb)
अणु
	वापस rtwdev->hci.ops->tx_ग_लिखो(rtwdev, pkt_info, skb);
पूर्ण

अटल अंतरभूत व्योम rtw_hci_tx_kick_off(काष्ठा rtw_dev *rtwdev)
अणु
	वापस rtwdev->hci.ops->tx_kick_off(rtwdev);
पूर्ण

अटल अंतरभूत पूर्णांक rtw_hci_setup(काष्ठा rtw_dev *rtwdev)
अणु
	वापस rtwdev->hci.ops->setup(rtwdev);
पूर्ण

अटल अंतरभूत पूर्णांक rtw_hci_start(काष्ठा rtw_dev *rtwdev)
अणु
	वापस rtwdev->hci.ops->start(rtwdev);
पूर्ण

अटल अंतरभूत व्योम rtw_hci_stop(काष्ठा rtw_dev *rtwdev)
अणु
	rtwdev->hci.ops->stop(rtwdev);
पूर्ण

अटल अंतरभूत व्योम rtw_hci_deep_ps(काष्ठा rtw_dev *rtwdev, bool enter)
अणु
	rtwdev->hci.ops->deep_ps(rtwdev, enter);
पूर्ण

अटल अंतरभूत व्योम rtw_hci_link_ps(काष्ठा rtw_dev *rtwdev, bool enter)
अणु
	rtwdev->hci.ops->link_ps(rtwdev, enter);
पूर्ण

अटल अंतरभूत व्योम rtw_hci_पूर्णांकerface_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	rtwdev->hci.ops->पूर्णांकerface_cfg(rtwdev);
पूर्ण

अटल अंतरभूत पूर्णांक
rtw_hci_ग_लिखो_data_rsvd_page(काष्ठा rtw_dev *rtwdev, u8 *buf, u32 size)
अणु
	वापस rtwdev->hci.ops->ग_लिखो_data_rsvd_page(rtwdev, buf, size);
पूर्ण

अटल अंतरभूत पूर्णांक
rtw_hci_ग_लिखो_data_h2c(काष्ठा rtw_dev *rtwdev, u8 *buf, u32 size)
अणु
	वापस rtwdev->hci.ops->ग_लिखो_data_h2c(rtwdev, buf, size);
पूर्ण

अटल अंतरभूत u8 rtw_पढ़ो8(काष्ठा rtw_dev *rtwdev, u32 addr)
अणु
	वापस rtwdev->hci.ops->पढ़ो8(rtwdev, addr);
पूर्ण

अटल अंतरभूत u16 rtw_पढ़ो16(काष्ठा rtw_dev *rtwdev, u32 addr)
अणु
	वापस rtwdev->hci.ops->पढ़ो16(rtwdev, addr);
पूर्ण

अटल अंतरभूत u32 rtw_पढ़ो32(काष्ठा rtw_dev *rtwdev, u32 addr)
अणु
	वापस rtwdev->hci.ops->पढ़ो32(rtwdev, addr);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो8(काष्ठा rtw_dev *rtwdev, u32 addr, u8 val)
अणु
	rtwdev->hci.ops->ग_लिखो8(rtwdev, addr, val);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो16(काष्ठा rtw_dev *rtwdev, u32 addr, u16 val)
अणु
	rtwdev->hci.ops->ग_लिखो16(rtwdev, addr, val);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो32(काष्ठा rtw_dev *rtwdev, u32 addr, u32 val)
अणु
	rtwdev->hci.ops->ग_लिखो32(rtwdev, addr, val);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो8_set(काष्ठा rtw_dev *rtwdev, u32 addr, u8 bit)
अणु
	u8 val;

	val = rtw_पढ़ो8(rtwdev, addr);
	rtw_ग_लिखो8(rtwdev, addr, val | bit);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो16_set(काष्ठा rtw_dev *rtwdev, u32 addr, u16 bit)
अणु
	u16 val;

	val = rtw_पढ़ो16(rtwdev, addr);
	rtw_ग_लिखो16(rtwdev, addr, val | bit);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो32_set(काष्ठा rtw_dev *rtwdev, u32 addr, u32 bit)
अणु
	u32 val;

	val = rtw_पढ़ो32(rtwdev, addr);
	rtw_ग_लिखो32(rtwdev, addr, val | bit);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो8_clr(काष्ठा rtw_dev *rtwdev, u32 addr, u8 bit)
अणु
	u8 val;

	val = rtw_पढ़ो8(rtwdev, addr);
	rtw_ग_लिखो8(rtwdev, addr, val & ~bit);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो16_clr(काष्ठा rtw_dev *rtwdev, u32 addr, u16 bit)
अणु
	u16 val;

	val = rtw_पढ़ो16(rtwdev, addr);
	rtw_ग_लिखो16(rtwdev, addr, val & ~bit);
पूर्ण

अटल अंतरभूत व्योम rtw_ग_लिखो32_clr(काष्ठा rtw_dev *rtwdev, u32 addr, u32 bit)
अणु
	u32 val;

	val = rtw_पढ़ो32(rtwdev, addr);
	rtw_ग_लिखो32(rtwdev, addr, val & ~bit);
पूर्ण

अटल अंतरभूत u32
rtw_पढ़ो_rf(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
	    u32 addr, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&rtwdev->rf_lock, flags);
	val = rtwdev->chip->ops->पढ़ो_rf(rtwdev, rf_path, addr, mask);
	spin_unlock_irqrestore(&rtwdev->rf_lock, flags);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम
rtw_ग_लिखो_rf(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
	     u32 addr, u32 mask, u32 data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtwdev->rf_lock, flags);
	rtwdev->chip->ops->ग_लिखो_rf(rtwdev, rf_path, addr, mask, data);
	spin_unlock_irqrestore(&rtwdev->rf_lock, flags);
पूर्ण

अटल अंतरभूत u32
rtw_पढ़ो32_mask(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask)
अणु
	u32 shअगरt = __ffs(mask);
	u32 orig;
	u32 ret;

	orig = rtw_पढ़ो32(rtwdev, addr);
	ret = (orig & mask) >> shअगरt;

	वापस ret;
पूर्ण

अटल अंतरभूत u16
rtw_पढ़ो16_mask(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask)
अणु
	u32 shअगरt = __ffs(mask);
	u32 orig;
	u32 ret;

	orig = rtw_पढ़ो16(rtwdev, addr);
	ret = (orig & mask) >> shअगरt;

	वापस ret;
पूर्ण

अटल अंतरभूत u8
rtw_पढ़ो8_mask(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask)
अणु
	u32 shअगरt = __ffs(mask);
	u32 orig;
	u32 ret;

	orig = rtw_पढ़ो8(rtwdev, addr);
	ret = (orig & mask) >> shअगरt;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
rtw_ग_लिखो32_mask(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask, u32 data)
अणु
	u32 shअगरt = __ffs(mask);
	u32 orig;
	u32 set;

	WARN(addr & 0x3, "should be 4-byte aligned, addr = 0x%08x\n", addr);

	orig = rtw_पढ़ो32(rtwdev, addr);
	set = (orig & ~mask) | ((data << shअगरt) & mask);
	rtw_ग_लिखो32(rtwdev, addr, set);
पूर्ण

अटल अंतरभूत व्योम
rtw_ग_लिखो8_mask(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask, u8 data)
अणु
	u32 shअगरt;
	u8 orig, set;

	mask &= 0xff;
	shअगरt = __ffs(mask);

	orig = rtw_पढ़ो8(rtwdev, addr);
	set = (orig & ~mask) | ((data << shअगरt) & mask);
	rtw_ग_लिखो8(rtwdev, addr, set);
पूर्ण

अटल अंतरभूत क्रमागत rtw_hci_type rtw_hci_type(काष्ठा rtw_dev *rtwdev)
अणु
	वापस rtwdev->hci.type;
पूर्ण

अटल अंतरभूत व्योम rtw_hci_flush_queues(काष्ठा rtw_dev *rtwdev, u32 queues,
					bool drop)
अणु
	अगर (rtwdev->hci.ops->flush_queues)
		rtwdev->hci.ops->flush_queues(rtwdev, queues, drop);
पूर्ण

अटल अंतरभूत व्योम rtw_hci_flush_all_queues(काष्ठा rtw_dev *rtwdev, bool drop)
अणु
	अगर (rtwdev->hci.ops->flush_queues)
		rtwdev->hci.ops->flush_queues(rtwdev,
					      BIT(rtwdev->hw->queues) - 1,
					      drop);
पूर्ण

#पूर्ण_अगर
