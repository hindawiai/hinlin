<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google Corporation
 */

#घोषणा MSFT_FEATURE_MASK_BREDR_RSSI_MONITOR		BIT(0)
#घोषणा MSFT_FEATURE_MASK_LE_CONN_RSSI_MONITOR		BIT(1)
#घोषणा MSFT_FEATURE_MASK_LE_ADV_RSSI_MONITOR		BIT(2)
#घोषणा MSFT_FEATURE_MASK_LE_ADV_MONITOR		BIT(3)
#घोषणा MSFT_FEATURE_MASK_CURVE_VALIDITY		BIT(4)
#घोषणा MSFT_FEATURE_MASK_CONCURRENT_ADV_MONITOR	BIT(5)

#अगर IS_ENABLED(CONFIG_BT_MSFTEXT)

bool msft_monitor_supported(काष्ठा hci_dev *hdev);
व्योम msft_करो_खोलो(काष्ठा hci_dev *hdev);
व्योम msft_करो_बंद(काष्ठा hci_dev *hdev);
व्योम msft_venकरोr_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
__u64 msft_get_features(काष्ठा hci_dev *hdev);
पूर्णांक msft_add_monitor_pattern(काष्ठा hci_dev *hdev, काष्ठा adv_monitor *monitor);
पूर्णांक msft_हटाओ_monitor(काष्ठा hci_dev *hdev, काष्ठा adv_monitor *monitor,
			u16 handle);
व्योम msft_req_add_set_filter_enable(काष्ठा hci_request *req, bool enable);
पूर्णांक msft_set_filter_enable(काष्ठा hci_dev *hdev, bool enable);
bool msft_curve_validity(काष्ठा hci_dev *hdev);

#अन्यथा

अटल अंतरभूत bool msft_monitor_supported(काष्ठा hci_dev *hdev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम msft_करो_खोलो(काष्ठा hci_dev *hdev) अणुपूर्ण
अटल अंतरभूत व्योम msft_करो_बंद(काष्ठा hci_dev *hdev) अणुपूर्ण
अटल अंतरभूत व्योम msft_venकरोr_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb) अणुपूर्ण
अटल अंतरभूत __u64 msft_get_features(काष्ठा hci_dev *hdev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक msft_add_monitor_pattern(काष्ठा hci_dev *hdev,
					   काष्ठा adv_monitor *monitor)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक msft_हटाओ_monitor(काष्ठा hci_dev *hdev,
				      काष्ठा adv_monitor *monitor,
				      u16 handle)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम msft_req_add_set_filter_enable(काष्ठा hci_request *req,
						  bool enable) अणुपूर्ण
अटल अंतरभूत पूर्णांक msft_set_filter_enable(काष्ठा hci_dev *hdev, bool enable)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool msft_curve_validity(काष्ठा hci_dev *hdev)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर
