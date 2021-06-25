<शैली गुरु>
/*
 * Copyright (c) 2012 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _BRCM_LED_H_
#घोषणा _BRCM_LED_H_

काष्ठा gpio_desc;

काष्ठा brcms_led अणु
	अक्षर name[32];
	काष्ठा gpio_desc *gpiod;
पूर्ण;

#अगर_घोषित CONFIG_BCMA_DRIVER_GPIO
व्योम brcms_led_unरेजिस्टर(काष्ठा brcms_info *wl);
पूर्णांक brcms_led_रेजिस्टर(काष्ठा brcms_info *wl);
#अन्यथा
अटल अंतरभूत व्योम brcms_led_unरेजिस्टर(काष्ठा brcms_info *wl) अणुपूर्ण;
अटल अंतरभूत पूर्णांक brcms_led_रेजिस्टर(काष्ठा brcms_info *wl)
अणु
	वापस -ENOTSUPP;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* _BRCM_LED_H_ */
