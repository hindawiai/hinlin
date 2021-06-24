<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * apple_bl exported symbols
 */

#अगर_अघोषित _LINUX_APPLE_BL_H
#घोषणा _LINUX_APPLE_BL_H

#अगर defined(CONFIG_BACKLIGHT_APPLE) || defined(CONFIG_BACKLIGHT_APPLE_MODULE)

बाह्य पूर्णांक apple_bl_रेजिस्टर(व्योम);
बाह्य व्योम apple_bl_unरेजिस्टर(व्योम);

#अन्यथा /* !CONFIG_BACKLIGHT_APPLE */

अटल अंतरभूत पूर्णांक apple_bl_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम apple_bl_unरेजिस्टर(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* !CONFIG_BACKLIGHT_APPLE */

#पूर्ण_अगर /* _LINUX_APPLE_BL_H */
