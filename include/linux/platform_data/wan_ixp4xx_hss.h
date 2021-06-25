<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PLATFORM_DATA_WAN_IXP4XX_HSS_H
#घोषणा __PLATFORM_DATA_WAN_IXP4XX_HSS_H

#समावेश <linux/types.h>

/* Inक्रमmation about built-in HSS (synchronous serial) पूर्णांकerfaces */
काष्ठा hss_plat_info अणु
	पूर्णांक (*set_घड़ी)(पूर्णांक port, अचिन्हित पूर्णांक घड़ी_प्रकारype);
	पूर्णांक (*खोलो)(पूर्णांक port, व्योम *pdev,
		    व्योम (*set_carrier_cb)(व्योम *pdev, पूर्णांक carrier));
	व्योम (*बंद)(पूर्णांक port, व्योम *pdev);
	u8 txपढ़ोyq;
	u32 समयr_freq;
पूर्ण;

#पूर्ण_अगर
