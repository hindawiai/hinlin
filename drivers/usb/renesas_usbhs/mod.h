<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ */
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Copyright (C) 2019 Renesas Electronics Corporation
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#अगर_अघोषित RENESAS_USB_MOD_H
#घोषणा RENESAS_USB_MOD_H

#समावेश <linux/spinlock.h>
#समावेश <linux/usb/renesas_usbhs.h>
#समावेश "common.h"

/*
 *	काष्ठा
 */
काष्ठा usbhs_irq_state अणु
	u16 पूर्णांकsts0;
	u16 पूर्णांकsts1;
	u16 brdysts;
	u16 nrdysts;
	u16 bempsts;
पूर्ण;

काष्ठा usbhs_mod अणु
	अक्षर *name;

	/*
	 * entry poपूर्णांक from common.c
	 */
	पूर्णांक (*start)(काष्ठा usbhs_priv *priv);
	पूर्णांक (*stop)(काष्ठा usbhs_priv *priv);

	/*
	 * INTSTS0
	 */

	/* DVST (DVSQ) */
	पूर्णांक (*irq_dev_state)(काष्ठा usbhs_priv *priv,
			     काष्ठा usbhs_irq_state *irq_state);

	/* CTRT (CTSQ) */
	पूर्णांक (*irq_ctrl_stage)(काष्ठा usbhs_priv *priv,
			      काष्ठा usbhs_irq_state *irq_state);

	/* BEMP / BEMPSTS */
	पूर्णांक (*irq_empty)(काष्ठा usbhs_priv *priv,
			 काष्ठा usbhs_irq_state *irq_state);
	u16 irq_bempsts;

	/* BRDY / BRDYSTS */
	पूर्णांक (*irq_पढ़ोy)(काष्ठा usbhs_priv *priv,
			 काष्ठा usbhs_irq_state *irq_state);
	u16 irq_brdysts;

	/*
	 * INTSTS1
	 */

	/* ATTCHE */
	पूर्णांक (*irq_attch)(काष्ठा usbhs_priv *priv,
			 काष्ठा usbhs_irq_state *irq_state);

	/* DTCHE */
	पूर्णांक (*irq_dtch)(काष्ठा usbhs_priv *priv,
			काष्ठा usbhs_irq_state *irq_state);

	/* SIGN */
	पूर्णांक (*irq_sign)(काष्ठा usbhs_priv *priv,
			काष्ठा usbhs_irq_state *irq_state);

	/* SACK */
	पूर्णांक (*irq_sack)(काष्ठा usbhs_priv *priv,
			काष्ठा usbhs_irq_state *irq_state);

	काष्ठा usbhs_priv *priv;
पूर्ण;

काष्ठा usbhs_mod_info अणु
	काष्ठा usbhs_mod *mod[USBHS_MAX];
	काष्ठा usbhs_mod *curt; /* current mod */

	/*
	 * INTSTS0 :: VBINT
	 *
	 * This function will be used as स्वतःnomy mode (runसमय_pwctrl == 0)
	 * when the platक्रमm करोesn't have own get_vbus function.
	 *
	 * This callback cannot be member of "struct usbhs_mod" because it
	 * will be used even though host/gadget has not been selected.
	 */
	पूर्णांक (*irq_vbus)(काष्ठा usbhs_priv *priv,
			काष्ठा usbhs_irq_state *irq_state);

	/*
	 * This function will be used on any gadget mode. To simplअगरy the code,
	 * this member is in here.
	 */
	पूर्णांक (*get_vbus)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

/*
 *		क्रम host/gadget module
 */
काष्ठा usbhs_mod *usbhs_mod_get(काष्ठा usbhs_priv *priv, पूर्णांक id);
काष्ठा usbhs_mod *usbhs_mod_get_current(काष्ठा usbhs_priv *priv);
व्योम usbhs_mod_रेजिस्टर(काष्ठा usbhs_priv *priv, काष्ठा usbhs_mod *usb, पूर्णांक id);
पूर्णांक usbhs_mod_is_host(काष्ठा usbhs_priv *priv);
पूर्णांक usbhs_mod_change(काष्ठा usbhs_priv *priv, पूर्णांक id);
पूर्णांक usbhs_mod_probe(काष्ठा usbhs_priv *priv);
व्योम usbhs_mod_हटाओ(काष्ठा usbhs_priv *priv);

व्योम usbhs_mod_स्वतःnomy_mode(काष्ठा usbhs_priv *priv);
व्योम usbhs_mod_non_स्वतःnomy_mode(काष्ठा usbhs_priv *priv);

/*
 *		status functions
 */
पूर्णांक usbhs_status_get_device_state(काष्ठा usbhs_irq_state *irq_state);
पूर्णांक usbhs_status_get_ctrl_stage(काष्ठा usbhs_irq_state *irq_state);

/*
 *		callback functions
 */
व्योम usbhs_irq_callback_update(काष्ठा usbhs_priv *priv, काष्ठा usbhs_mod *mod);


#घोषणा usbhs_mod_call(priv, func, param...)		\
	(अणु						\
		काष्ठा usbhs_mod *mod;			\
		mod = usbhs_mod_get_current(priv);	\
		!mod		? -ENODEV :		\
		!mod->func	? 0 :			\
		 mod->func(param);			\
	पूर्ण)

#घोषणा usbhs_priv_to_modinfo(priv) (&priv->mod_info)
#घोषणा usbhs_mod_info_call(priv, func, param...)	\
(अणु							\
	काष्ठा usbhs_mod_info *info;			\
	info = usbhs_priv_to_modinfo(priv);		\
	!info->func ? 0 :				\
	 info->func(param);				\
पूर्ण)

/*
 * host / gadget control
 */
#अगर	defined(CONFIG_USB_RENESAS_USBHS_HCD) || \
	defined(CONFIG_USB_RENESAS_USBHS_HCD_MODULE)
बाह्य पूर्णांक usbhs_mod_host_probe(काष्ठा usbhs_priv *priv);
बाह्य पूर्णांक usbhs_mod_host_हटाओ(काष्ठा usbhs_priv *priv);
#अन्यथा
अटल अंतरभूत पूर्णांक usbhs_mod_host_probe(काष्ठा usbhs_priv *priv)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम usbhs_mod_host_हटाओ(काष्ठा usbhs_priv *priv)
अणु
पूर्ण
#पूर्ण_अगर

#अगर	defined(CONFIG_USB_RENESAS_USBHS_UDC) || \
	defined(CONFIG_USB_RENESAS_USBHS_UDC_MODULE)
बाह्य पूर्णांक usbhs_mod_gadget_probe(काष्ठा usbhs_priv *priv);
बाह्य व्योम usbhs_mod_gadget_हटाओ(काष्ठा usbhs_priv *priv);
#अन्यथा
अटल अंतरभूत पूर्णांक usbhs_mod_gadget_probe(काष्ठा usbhs_priv *priv)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम usbhs_mod_gadget_हटाओ(काष्ठा usbhs_priv *priv)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* RENESAS_USB_MOD_H */
