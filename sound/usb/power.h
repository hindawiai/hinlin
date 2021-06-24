<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USBAUDIO_POWER_H
#घोषणा __USBAUDIO_POWER_H

काष्ठा snd_usb_घातer_करोमुख्य अणु
	पूर्णांक pd_id;              /* UAC3 Power Doमुख्य ID */
	पूर्णांक pd_d1d0_rec;        /* D1 to D0 recovery समय */
	पूर्णांक pd_d2d0_rec;        /* D2 to D0 recovery समय */
पूर्ण;

क्रमागत अणु
	UAC3_PD_STATE_D0,
	UAC3_PD_STATE_D1,
	UAC3_PD_STATE_D2,
पूर्ण;

पूर्णांक snd_usb_घातer_करोमुख्य_set(काष्ठा snd_usb_audio *chip,
			     काष्ठा snd_usb_घातer_करोमुख्य *pd,
			     अचिन्हित अक्षर state);
काष्ठा snd_usb_घातer_करोमुख्य *
snd_usb_find_घातer_करोमुख्य(काष्ठा usb_host_पूर्णांकerface *ctrl_अगरace,
			  अचिन्हित अक्षर id);

#अगर_घोषित CONFIG_PM
पूर्णांक snd_usb_स्वतःresume(काष्ठा snd_usb_audio *chip);
व्योम snd_usb_स्वतःsuspend(काष्ठा snd_usb_audio *chip);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_usb_स्वतःresume(काष्ठा snd_usb_audio *chip)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम snd_usb_स्वतःsuspend(काष्ठा snd_usb_audio *chip)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __USBAUDIO_POWER_H */
