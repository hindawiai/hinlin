<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *  Bluetooth support क्रम Broadcom devices
 *
 *  Copyright (C) 2015  Intel Corporation
 */

#घोषणा BCM_UART_CLOCK_48MHZ	0x01
#घोषणा BCM_UART_CLOCK_24MHZ	0x02

काष्ठा bcm_update_uart_baud_rate अणु
	__le16 zero;
	__le32 baud_rate;
पूर्ण __packed;

काष्ठा bcm_ग_लिखो_uart_घड़ी_setting अणु
	__u8 type;
पूर्ण __packed;

काष्ठा bcm_set_sleep_mode अणु
	__u8 sleep_mode;
	__u8 idle_host;
	__u8 idle_dev;
	__u8 bt_wake_active;
	__u8 host_wake_active;
	__u8 allow_host_sleep;
	__u8 combine_modes;
	__u8 tristate_control;
	__u8 usb_स्वतः_sleep;
	__u8 usb_resume_समयout;
	__u8 अवरोध_to_host;
	__u8 pulsed_host_wake;
पूर्ण __packed;

काष्ठा bcm_set_pcm_पूर्णांक_params अणु
	__u8 routing;
	__u8 rate;
	__u8 frame_sync;
	__u8 sync_mode;
	__u8 घड़ी_mode;
पूर्ण __packed;

काष्ठा bcm_set_pcm_क्रमmat_params अणु
	__u8 lsb_first;
	__u8 fill_value;
	__u8 fill_method;
	__u8 fill_num;
	__u8 right_justअगरy;
पूर्ण __packed;

#अगर IS_ENABLED(CONFIG_BT_BCM)

पूर्णांक btbcm_check_bdaddr(काष्ठा hci_dev *hdev);
पूर्णांक btbcm_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr);
पूर्णांक btbcm_patchram(काष्ठा hci_dev *hdev, स्थिर काष्ठा firmware *fw);
पूर्णांक btbcm_पढ़ो_pcm_पूर्णांक_params(काष्ठा hci_dev *hdev,
			      काष्ठा bcm_set_pcm_पूर्णांक_params *params);
पूर्णांक btbcm_ग_लिखो_pcm_पूर्णांक_params(काष्ठा hci_dev *hdev,
			       स्थिर काष्ठा bcm_set_pcm_पूर्णांक_params *params);

पूर्णांक btbcm_setup_patchram(काष्ठा hci_dev *hdev);
पूर्णांक btbcm_setup_apple(काष्ठा hci_dev *hdev);

पूर्णांक btbcm_initialize(काष्ठा hci_dev *hdev, bool *fw_load_करोne);
पूर्णांक btbcm_finalize(काष्ठा hci_dev *hdev, bool *fw_load_करोne);

#अन्यथा

अटल अंतरभूत पूर्णांक btbcm_check_bdaddr(काष्ठा hci_dev *hdev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btbcm_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btbcm_पढ़ो_pcm_पूर्णांक_params(काष्ठा hci_dev *hdev,
			      काष्ठा bcm_set_pcm_पूर्णांक_params *params)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btbcm_ग_लिखो_pcm_पूर्णांक_params(काष्ठा hci_dev *hdev,
			       स्थिर काष्ठा bcm_set_pcm_पूर्णांक_params *params)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btbcm_patchram(काष्ठा hci_dev *hdev, स्थिर काष्ठा firmware *fw)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btbcm_setup_patchram(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btbcm_setup_apple(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btbcm_initialize(काष्ठा hci_dev *hdev, bool *fw_load_करोne)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btbcm_finalize(काष्ठा hci_dev *hdev, bool *fw_load_करोne)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
