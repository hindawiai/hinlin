<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mtu3_dr.h - dual role चयन and host glue layer header
 *
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#अगर_अघोषित _MTU3_DR_H_
#घोषणा _MTU3_DR_H_

#अगर IS_ENABLED(CONFIG_USB_MTU3_HOST) || IS_ENABLED(CONFIG_USB_MTU3_DUAL_ROLE)

पूर्णांक ssusb_host_init(काष्ठा ssusb_mtk *ssusb, काष्ठा device_node *parent_dn);
व्योम ssusb_host_निकास(काष्ठा ssusb_mtk *ssusb);
पूर्णांक ssusb_wakeup_of_property_parse(काष्ठा ssusb_mtk *ssusb,
				काष्ठा device_node *dn);
पूर्णांक ssusb_host_enable(काष्ठा ssusb_mtk *ssusb);
पूर्णांक ssusb_host_disable(काष्ठा ssusb_mtk *ssusb, bool suspend);
व्योम ssusb_wakeup_set(काष्ठा ssusb_mtk *ssusb, bool enable);

#अन्यथा

अटल अंतरभूत पूर्णांक ssusb_host_init(काष्ठा ssusb_mtk *ssusb,

	काष्ठा device_node *parent_dn)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ssusb_host_निकास(काष्ठा ssusb_mtk *ssusb)
अणुपूर्ण

अटल अंतरभूत पूर्णांक ssusb_wakeup_of_property_parse(
	काष्ठा ssusb_mtk *ssusb, काष्ठा device_node *dn)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ssusb_host_enable(काष्ठा ssusb_mtk *ssusb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ssusb_host_disable(काष्ठा ssusb_mtk *ssusb, bool suspend)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ssusb_wakeup_set(काष्ठा ssusb_mtk *ssusb, bool enable)
अणुपूर्ण

#पूर्ण_अगर


#अगर IS_ENABLED(CONFIG_USB_MTU3_GADGET) || IS_ENABLED(CONFIG_USB_MTU3_DUAL_ROLE)
पूर्णांक ssusb_gadget_init(काष्ठा ssusb_mtk *ssusb);
व्योम ssusb_gadget_निकास(काष्ठा ssusb_mtk *ssusb);
#अन्यथा
अटल अंतरभूत पूर्णांक ssusb_gadget_init(काष्ठा ssusb_mtk *ssusb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ssusb_gadget_निकास(काष्ठा ssusb_mtk *ssusb)
अणुपूर्ण
#पूर्ण_अगर


#अगर IS_ENABLED(CONFIG_USB_MTU3_DUAL_ROLE)
पूर्णांक ssusb_otg_चयन_init(काष्ठा ssusb_mtk *ssusb);
व्योम ssusb_otg_चयन_निकास(काष्ठा ssusb_mtk *ssusb);
व्योम ssusb_mode_चयन(काष्ठा ssusb_mtk *ssusb, पूर्णांक to_host);
पूर्णांक ssusb_set_vbus(काष्ठा otg_चयन_mtk *otg_sx, पूर्णांक is_on);
व्योम ssusb_set_क्रमce_mode(काष्ठा ssusb_mtk *ssusb,
			  क्रमागत mtu3_dr_क्रमce_mode mode);

#अन्यथा

अटल अंतरभूत पूर्णांक ssusb_otg_चयन_init(काष्ठा ssusb_mtk *ssusb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ssusb_otg_चयन_निकास(काष्ठा ssusb_mtk *ssusb)
अणुपूर्ण

अटल अंतरभूत व्योम ssusb_mode_चयन(काष्ठा ssusb_mtk *ssusb, पूर्णांक to_host)
अणुपूर्ण

अटल अंतरभूत पूर्णांक ssusb_set_vbus(काष्ठा otg_चयन_mtk *otg_sx, पूर्णांक is_on)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
ssusb_set_क्रमce_mode(काष्ठा ssusb_mtk *ssusb, क्रमागत mtu3_dr_क्रमce_mode mode)
अणुपूर्ण

#पूर्ण_अगर

#पूर्ण_अगर		/* _MTU3_DR_H_ */
