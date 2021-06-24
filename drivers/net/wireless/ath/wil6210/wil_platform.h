<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2014-2017 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित __WIL_PLATFORM_H__
#घोषणा __WIL_PLATFORM_H__

काष्ठा device;

क्रमागत wil_platक्रमm_event अणु
	WIL_PLATFORM_EVT_FW_CRASH = 0,
	WIL_PLATFORM_EVT_PRE_RESET = 1,
	WIL_PLATFORM_EVT_FW_RDY = 2,
	WIL_PLATFORM_EVT_PRE_SUSPEND = 3,
	WIL_PLATFORM_EVT_POST_SUSPEND = 4,
पूर्ण;

क्रमागत wil_platक्रमm_features अणु
	WIL_PLATFORM_FEATURE_FW_EXT_CLK_CONTROL = 0,
	WIL_PLATFORM_FEATURE_TRIPLE_MSI = 1,
	WIL_PLATFORM_FEATURE_MAX,
पूर्ण;

क्रमागत wil_platक्रमm_capa अणु
	WIL_PLATFORM_CAPA_RADIO_ON_IN_SUSPEND = 0,
	WIL_PLATFORM_CAPA_T_PWR_ON_0 = 1,
	WIL_PLATFORM_CAPA_EXT_CLK = 2,
	WIL_PLATFORM_CAPA_MAX,
पूर्ण;

/**
 * काष्ठा wil_platक्रमm_ops - wil platक्रमm module calls from this
 * driver to platक्रमm driver
 */
काष्ठा wil_platक्रमm_ops अणु
	पूर्णांक (*bus_request)(व्योम *handle, uपूर्णांक32_t kbps /* KBytes/Sec */);
	पूर्णांक (*suspend)(व्योम *handle, bool keep_device_घातer);
	पूर्णांक (*resume)(व्योम *handle, bool device_घातered_on);
	व्योम (*uninit)(व्योम *handle);
	पूर्णांक (*notअगरy)(व्योम *handle, क्रमागत wil_platक्रमm_event evt);
	पूर्णांक (*get_capa)(व्योम *handle);
	व्योम (*set_features)(व्योम *handle, पूर्णांक features);
पूर्ण;

/**
 * काष्ठा wil_platक्रमm_rops - wil platक्रमm module callbacks from
 * platक्रमm driver to this driver
 * @ramdump: store a ramdump from the wil firmware. The platक्रमm
 *	driver may add additional data to the ramdump to
 *	generate the final crash dump.
 * @fw_recovery: start a firmware recovery process. Called as
 *      part of a crash recovery process which may include other
 *      related platक्रमm subप्रणालीs.
 */
काष्ठा wil_platक्रमm_rops अणु
	पूर्णांक (*ramdump)(व्योम *wil_handle, व्योम *buf, uपूर्णांक32_t size);
	पूर्णांक (*fw_recovery)(व्योम *wil_handle);
पूर्ण;

/**
 * wil_platक्रमm_init - initialize the platक्रमm driver
 *
 * @dev - poपूर्णांकer to the wil6210 device
 * @ops - काष्ठाure with platक्रमm driver operations. Platक्रमm
 *	driver will fill this काष्ठाure with function poपूर्णांकers.
 * @rops - काष्ठाure with callbacks from platक्रमm driver to
 *	this driver. The platक्रमm driver copies the काष्ठाure to
 *	its own storage. Can be शून्य अगर this driver करोes not
 *	support crash recovery.
 * @wil_handle - context क्रम this driver that will be passed
 *      when platक्रमm driver invokes one of the callbacks in
 *      rops. May be शून्य अगर rops is शून्य.
 */
व्योम *wil_platक्रमm_init(काष्ठा device *dev, काष्ठा wil_platक्रमm_ops *ops,
			स्थिर काष्ठा wil_platक्रमm_rops *rops, व्योम *wil_handle);

पूर्णांक __init wil_platक्रमm_modinit(व्योम);
व्योम wil_platक्रमm_modनिकास(व्योम);

#पूर्ण_अगर /* __WIL_PLATFORM_H__ */
