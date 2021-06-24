<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Common functions क्रम kernel modules using Dell SMBIOS
 *
 *  Copyright (c) Red Hat <mjg@redhat.com>
 *  Copyright (c) 2014 Gabriele Mazzotta <gabriele.mzt@gmail.com>
 *  Copyright (c) 2014 Pali Rohथँr <pali@kernel.org>
 *
 *  Based on करोcumentation in the libsmbios package:
 *  Copyright (C) 2005-2014 Dell Inc.
 */

#अगर_अघोषित _DELL_SMBIOS_H_
#घोषणा _DELL_SMBIOS_H_

#समावेश <linux/device.h>
#समावेश <uapi/linux/wmi.h>

/* Classes and selects used only in kernel drivers */
#घोषणा CLASS_KBD_BACKLIGHT 4
#घोषणा SELECT_KBD_BACKLIGHT 11

/* Tokens used in kernel drivers, any of these
 * should be filtered from userspace access
 */
#घोषणा BRIGHTNESS_TOKEN	0x007d
#घोषणा KBD_LED_AC_TOKEN	0x0451
#घोषणा KBD_LED_OFF_TOKEN	0x01E1
#घोषणा KBD_LED_ON_TOKEN	0x01E2
#घोषणा KBD_LED_AUTO_TOKEN	0x01E3
#घोषणा KBD_LED_AUTO_25_TOKEN	0x02EA
#घोषणा KBD_LED_AUTO_50_TOKEN	0x02EB
#घोषणा KBD_LED_AUTO_75_TOKEN	0x02EC
#घोषणा KBD_LED_AUTO_100_TOKEN	0x02F6
#घोषणा GLOBAL_MIC_MUTE_ENABLE	0x0364
#घोषणा GLOBAL_MIC_MUTE_DISABLE	0x0365

काष्ठा notअगरier_block;

काष्ठा calling_पूर्णांकerface_token अणु
	u16 tokenID;
	u16 location;
	जोड़ अणु
		u16 value;
		u16 stringlength;
	पूर्ण;
पूर्ण;

काष्ठा calling_पूर्णांकerface_काष्ठाure अणु
	काष्ठा dmi_header header;
	u16 cmdIOAddress;
	u8 cmdIOCode;
	u32 supportedCmds;
	काष्ठा calling_पूर्णांकerface_token tokens[];
पूर्ण __packed;

पूर्णांक dell_smbios_रेजिस्टर_device(काष्ठा device *d, व्योम *call_fn);
व्योम dell_smbios_unरेजिस्टर_device(काष्ठा device *d);

पूर्णांक dell_smbios_error(पूर्णांक value);
पूर्णांक dell_smbios_call_filter(काष्ठा device *d,
	काष्ठा calling_पूर्णांकerface_buffer *buffer);
पूर्णांक dell_smbios_call(काष्ठा calling_पूर्णांकerface_buffer *buffer);

काष्ठा calling_पूर्णांकerface_token *dell_smbios_find_token(पूर्णांक tokenid);

क्रमागत dell_laptop_notअगरier_actions अणु
	DELL_LAPTOP_KBD_BACKLIGHT_BRIGHTNESS_CHANGED,
पूर्ण;

पूर्णांक dell_laptop_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक dell_laptop_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
व्योम dell_laptop_call_notअगरier(अचिन्हित दीर्घ action, व्योम *data);

/* क्रम the supported backends */
#अगर_घोषित CONFIG_DELL_SMBIOS_WMI
पूर्णांक init_dell_smbios_wmi(व्योम);
व्योम निकास_dell_smbios_wmi(व्योम);
#अन्यथा /* CONFIG_DELL_SMBIOS_WMI */
अटल अंतरभूत पूर्णांक init_dell_smbios_wmi(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम निकास_dell_smbios_wmi(व्योम)
अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DELL_SMBIOS_WMI */

#अगर_घोषित CONFIG_DELL_SMBIOS_SMM
पूर्णांक init_dell_smbios_smm(व्योम);
व्योम निकास_dell_smbios_smm(व्योम);
#अन्यथा /* CONFIG_DELL_SMBIOS_SMM */
अटल अंतरभूत पूर्णांक init_dell_smbios_smm(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम निकास_dell_smbios_smm(व्योम)
अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DELL_SMBIOS_SMM */

#पूर्ण_अगर /* _DELL_SMBIOS_H_ */
