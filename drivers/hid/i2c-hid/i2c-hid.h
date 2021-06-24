<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#अगर_अघोषित I2C_HID_H
#घोषणा I2C_HID_H

#समावेश <linux/i2c.h>

#अगर_घोषित CONFIG_DMI
काष्ठा i2c_hid_desc *i2c_hid_get_dmi_i2c_hid_desc_override(uपूर्णांक8_t *i2c_name);
अक्षर *i2c_hid_get_dmi_hid_report_desc_override(uपूर्णांक8_t *i2c_name,
					       अचिन्हित पूर्णांक *size);
#अन्यथा
अटल अंतरभूत काष्ठा i2c_hid_desc
		   *i2c_hid_get_dmi_i2c_hid_desc_override(uपूर्णांक8_t *i2c_name)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत अक्षर *i2c_hid_get_dmi_hid_report_desc_override(uपूर्णांक8_t *i2c_name,
							     अचिन्हित पूर्णांक *size)
अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

/**
 * काष्ठा i2chid_ops - Ops provided to the core.
 *
 * @घातer_up: करो sequencing to घातer up the device.
 * @घातer_करोwn: करो sequencing to घातer करोwn the device.
 * @shutकरोwn_tail: called at the end of shutकरोwn.
 */
काष्ठा i2chid_ops अणु
	पूर्णांक (*घातer_up)(काष्ठा i2chid_ops *ops);
	व्योम (*घातer_करोwn)(काष्ठा i2chid_ops *ops);
	व्योम (*shutकरोwn_tail)(काष्ठा i2chid_ops *ops);
पूर्ण;

पूर्णांक i2c_hid_core_probe(काष्ठा i2c_client *client, काष्ठा i2chid_ops *ops,
		       u16 hid_descriptor_address);
पूर्णांक i2c_hid_core_हटाओ(काष्ठा i2c_client *client);

व्योम i2c_hid_core_shutकरोwn(काष्ठा i2c_client *client);

बाह्य स्थिर काष्ठा dev_pm_ops i2c_hid_core_pm;

#पूर्ण_अगर
