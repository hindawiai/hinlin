<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __HID_LG4FF_H
#घोषणा __HID_LG4FF_H

#अगर_घोषित CONFIG_LOGIWHEELS_FF
बाह्य पूर्णांक lg4ff_no_स्वतःचयन; /* From hid-lg.c */

पूर्णांक lg4ff_adjust_input_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
			     काष्ठा hid_usage *usage, s32 value, काष्ठा lg_drv_data *drv_data);
पूर्णांक lg4ff_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *rd, पूर्णांक size, काष्ठा lg_drv_data *drv_data);
पूर्णांक lg4ff_init(काष्ठा hid_device *hdev);
पूर्णांक lg4ff_deinit(काष्ठा hid_device *hdev);
#अन्यथा
अटल अंतरभूत पूर्णांक lg4ff_adjust_input_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
					   काष्ठा hid_usage *usage, s32 value, काष्ठा lg_drv_data *drv_data) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक lg4ff_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *rd, पूर्णांक size, काष्ठा lg_drv_data *drv_data) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक lg4ff_init(काष्ठा hid_device *hdev) अणु वापस -1; पूर्ण
अटल अंतरभूत पूर्णांक lg4ff_deinit(काष्ठा hid_device *hdev) अणु वापस -1; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
