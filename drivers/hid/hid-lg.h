<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __HID_LG_H
#घोषणा __HID_LG_H

काष्ठा lg_drv_data अणु
	अचिन्हित दीर्घ quirks;
	व्योम *device_props;	/* Device specअगरic properties */
पूर्ण;

#अगर_घोषित CONFIG_LOGITECH_FF
पूर्णांक lgff_init(काष्ठा hid_device *hdev);
#अन्यथा
अटल अंतरभूत पूर्णांक lgff_init(काष्ठा hid_device *hdev) अणु वापस -1; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_LOGIRUMBLEPAD2_FF
पूर्णांक lg2ff_init(काष्ठा hid_device *hdev);
#अन्यथा
अटल अंतरभूत पूर्णांक lg2ff_init(काष्ठा hid_device *hdev) अणु वापस -1; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_LOGIG940_FF
पूर्णांक lg3ff_init(काष्ठा hid_device *hdev);
#अन्यथा
अटल अंतरभूत पूर्णांक lg3ff_init(काष्ठा hid_device *hdev) अणु वापस -1; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
