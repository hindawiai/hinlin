<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Bluetooth support क्रम Realtek devices
 *
 *  Copyright (C) 2015 Endless Mobile, Inc.
 */

#घोषणा RTL_FRAG_LEN 252

#घोषणा rtl_dev_err(dev, fmt, ...) bt_dev_err(dev, "RTL: " fmt, ##__VA_ARGS__)
#घोषणा rtl_dev_warn(dev, fmt, ...) bt_dev_warn(dev, "RTL: " fmt, ##__VA_ARGS__)
#घोषणा rtl_dev_info(dev, fmt, ...) bt_dev_info(dev, "RTL: " fmt, ##__VA_ARGS__)
#घोषणा rtl_dev_dbg(dev, fmt, ...) bt_dev_dbg(dev, "RTL: " fmt, ##__VA_ARGS__)

काष्ठा btrtl_device_info;

काष्ठा rtl_करोwnload_cmd अणु
	__u8 index;
	__u8 data[RTL_FRAG_LEN];
पूर्ण __packed;

काष्ठा rtl_करोwnload_response अणु
	__u8 status;
	__u8 index;
पूर्ण __packed;

काष्ठा rtl_rom_version_evt अणु
	__u8 status;
	__u8 version;
पूर्ण __packed;

काष्ठा rtl_epatch_header अणु
	__u8 signature[8];
	__le32 fw_version;
	__le16 num_patches;
पूर्ण __packed;

काष्ठा rtl_venकरोr_config_entry अणु
	__le16 offset;
	__u8 len;
	__u8 data[];
पूर्ण __packed;

काष्ठा rtl_venकरोr_config अणु
	__le32 signature;
	__le16 total_len;
	काष्ठा rtl_venकरोr_config_entry entry[];
पूर्ण __packed;

#अगर IS_ENABLED(CONFIG_BT_RTL)

काष्ठा btrtl_device_info *btrtl_initialize(काष्ठा hci_dev *hdev,
					   स्थिर अक्षर *postfix);
व्योम btrtl_मुक्त(काष्ठा btrtl_device_info *btrtl_dev);
पूर्णांक btrtl_करोwnload_firmware(काष्ठा hci_dev *hdev,
			    काष्ठा btrtl_device_info *btrtl_dev);
पूर्णांक btrtl_setup_realtek(काष्ठा hci_dev *hdev);
पूर्णांक btrtl_shutकरोwn_realtek(काष्ठा hci_dev *hdev);
पूर्णांक btrtl_get_uart_settings(काष्ठा hci_dev *hdev,
			    काष्ठा btrtl_device_info *btrtl_dev,
			    अचिन्हित पूर्णांक *controller_baudrate,
			    u32 *device_baudrate, bool *flow_control);

#अन्यथा

अटल अंतरभूत काष्ठा btrtl_device_info *btrtl_initialize(काष्ठा hci_dev *hdev,
							 स्थिर अक्षर *postfix)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम btrtl_मुक्त(काष्ठा btrtl_device_info *btrtl_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक btrtl_करोwnload_firmware(काष्ठा hci_dev *hdev,
					  काष्ठा btrtl_device_info *btrtl_dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btrtl_setup_realtek(काष्ठा hci_dev *hdev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btrtl_shutकरोwn_realtek(काष्ठा hci_dev *hdev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btrtl_get_uart_settings(काष्ठा hci_dev *hdev,
					  काष्ठा btrtl_device_info *btrtl_dev,
					  अचिन्हित पूर्णांक *controller_baudrate,
					  u32 *device_baudrate,
					  bool *flow_control)
अणु
	वापस -ENOENT;
पूर्ण

#पूर्ण_अगर
