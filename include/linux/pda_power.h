<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Common घातer driver क्रम PDAs and phones with one or two बाह्यal
 * घातer supplies (AC/USB) connected to मुख्य and backup batteries,
 * and optional builtin अक्षरger.
 *
 * Copyright तऊ 2007 Anton Vorontsov <cbou@mail.ru>
 */

#अगर_अघोषित __PDA_POWER_H__
#घोषणा __PDA_POWER_H__

#घोषणा PDA_POWER_CHARGE_AC  (1 << 0)
#घोषणा PDA_POWER_CHARGE_USB (1 << 1)

काष्ठा device;

काष्ठा pda_घातer_pdata अणु
	पूर्णांक (*init)(काष्ठा device *dev);
	पूर्णांक (*is_ac_online)(व्योम);
	पूर्णांक (*is_usb_online)(व्योम);
	व्योम (*set_अक्षरge)(पूर्णांक flags);
	व्योम (*निकास)(काष्ठा device *dev);
	पूर्णांक (*suspend)(pm_message_t state);
	पूर्णांक (*resume)(व्योम);

	अक्षर **supplied_to;
	माप_प्रकार num_supplicants;

	अचिन्हित पूर्णांक रुको_क्रम_status; /* msecs, शेष is 500 */
	अचिन्हित पूर्णांक रुको_क्रम_अक्षरger; /* msecs, शेष is 500 */
	अचिन्हित पूर्णांक polling_पूर्णांकerval; /* msecs, शेष is 2000 */

	अचिन्हित दीर्घ ac_max_uA; /* current to draw when on AC */

	bool use_otg_notअगरier;
पूर्ण;

#पूर्ण_अगर /* __PDA_POWER_H__ */
