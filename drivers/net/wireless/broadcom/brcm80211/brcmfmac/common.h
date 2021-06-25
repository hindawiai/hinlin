<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */
#अगर_अघोषित BRCMFMAC_COMMON_H
#घोषणा BRCMFMAC_COMMON_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/brcmfmac.h>
#समावेश "fwil_types.h"

#घोषणा BRCMF_FW_ALTPATH_LEN			256

/* Definitions क्रम the module global and device specअगरic settings are defined
 * here. Two काष्ठाs are used क्रम them. brcmf_mp_global_t and brcmf_mp_device.
 * The mp_global is instantiated once in a global काष्ठा and माला_लो initialized
 * by the common_attach function which should be called beक्रमe any other
 * (module) initiliazation takes place. The device specअगरic settings is part
 * of the drvr काष्ठा and should be initialized on every brcmf_attach.
 */

/**
 * काष्ठा brcmf_mp_global_t - Global module paramaters.
 *
 * @firmware_path: Alternative firmware path.
 */
काष्ठा brcmf_mp_global_t अणु
	अक्षर	firmware_path[BRCMF_FW_ALTPATH_LEN];
पूर्ण;

बाह्य काष्ठा brcmf_mp_global_t brcmf_mp_global;

/**
 * काष्ठा brcmf_mp_device - Device module paramaters.
 *
 * @p2p_enable: Legacy P2P0 enable (old wpa_supplicant).
 * @feature_disable: Feature_disable biपंचांगask.
 * @fcmode: FWS flow control.
 * @roamoff: Firmware roaming off?
 * @ignore_probe_fail: Ignore probe failure.
 * @country_codes: If available, poपूर्णांकer to काष्ठा क्रम translating country codes
 * @bus: Bus specअगरic platक्रमm data. Only SDIO at the mmoment.
 */
काष्ठा brcmf_mp_device अणु
	bool		p2p_enable;
	अचिन्हित पूर्णांक	feature_disable;
	पूर्णांक		fcmode;
	bool		roamoff;
	bool		iapp;
	bool		ignore_probe_fail;
	काष्ठा brcmfmac_pd_cc *country_codes;
	स्थिर अक्षर	*board_type;
	जोड़ अणु
		काष्ठा brcmfmac_sdio_pd sdio;
	पूर्ण bus;
पूर्ण;

व्योम brcmf_c_set_joinpref_शेष(काष्ठा brcmf_अगर *अगरp);

काष्ठा brcmf_mp_device *brcmf_get_module_param(काष्ठा device *dev,
					       क्रमागत brcmf_bus_type bus_type,
					       u32 chip, u32 chiprev);
व्योम brcmf_release_module_param(काष्ठा brcmf_mp_device *module_param);

/* Sets करोngle media info (drv_version, mac address). */
पूर्णांक brcmf_c_preinit_dcmds(काष्ठा brcmf_अगर *अगरp);

#अगर_घोषित CONFIG_DMI
व्योम brcmf_dmi_probe(काष्ठा brcmf_mp_device *settings, u32 chip, u32 chiprev);
#अन्यथा
अटल अंतरभूत व्योम
brcmf_dmi_probe(काष्ठा brcmf_mp_device *settings, u32 chip, u32 chiprev) अणुपूर्ण
#पूर्ण_अगर

u8 brcmf_map_prio_to_prec(व्योम *cfg, u8 prio);

u8 brcmf_map_prio_to_aci(व्योम *cfg, u8 prio);

#पूर्ण_अगर /* BRCMFMAC_COMMON_H */
