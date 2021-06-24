<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2020 Intel Corporation
 */
#अगर_अघोषित __iwl_modparams_h__
#घोषणा __iwl_modparams_h__

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/gfp.h>

बाह्य काष्ठा iwl_mod_params iwlwअगरi_mod_params;

क्रमागत iwl_घातer_level अणु
	IWL_POWER_INDEX_1,
	IWL_POWER_INDEX_2,
	IWL_POWER_INDEX_3,
	IWL_POWER_INDEX_4,
	IWL_POWER_INDEX_5,
	IWL_POWER_NUM
पूर्ण;

क्रमागत iwl_disable_11n अणु
	IWL_DISABLE_HT_ALL	 = BIT(0),
	IWL_DISABLE_HT_TXAGG	 = BIT(1),
	IWL_DISABLE_HT_RXAGG	 = BIT(2),
	IWL_ENABLE_HT_TXAGG	 = BIT(3),
पूर्ण;

क्रमागत iwl_amsdu_size अणु
	IWL_AMSDU_DEF = 0,
	IWL_AMSDU_4K = 1,
	IWL_AMSDU_8K = 2,
	IWL_AMSDU_12K = 3,
	/* Add 2K at the end to aव्योम अवरोधing current API */
	IWL_AMSDU_2K = 4,
पूर्ण;

क्रमागत iwl_uapsd_disable अणु
	IWL_DISABLE_UAPSD_BSS		= BIT(0),
	IWL_DISABLE_UAPSD_P2P_CLIENT	= BIT(1),
पूर्ण;

/**
 * काष्ठा iwl_mod_params
 *
 * Holds the module parameters
 *
 * @swcrypto: using hardware encryption, शेष = 0
 * @disable_11n: disable 11n capabilities, शेष = 0,
 *	use IWL_[DIS,EN]ABLE_HT_* स्थिरants
 * @amsdu_size: See &क्रमागत iwl_amsdu_size.
 * @fw_restart: restart firmware, शेष = 1
 * @bt_coex_active: enable bt coex, शेष = true
 * @led_mode: प्रणाली शेष, शेष = 0
 * @घातer_save: enable घातer save, शेष = false
 * @घातer_level: घातer level, शेष = 1
 * @debug_level: levels are IWL_DL_*
 * @nvm_file: specअगरies a बाह्यal NVM file
 * @uapsd_disable: disable U-APSD, see &क्रमागत iwl_uapsd_disable, शेष =
 *	IWL_DISABLE_UAPSD_BSS | IWL_DISABLE_UAPSD_P2P_CLIENT
 * @disable_11ac: disable VHT capabilities, शेष = false.
 * @हटाओ_when_gone: हटाओ an inaccessible device from the PCIe bus.
 * @enable_ini: enable new FW debug infratructure (INI TLVs)
 */
काष्ठा iwl_mod_params अणु
	पूर्णांक swcrypto;
	अचिन्हित पूर्णांक disable_11n;
	पूर्णांक amsdu_size;
	bool fw_restart;
	bool bt_coex_active;
	पूर्णांक led_mode;
	bool घातer_save;
	पूर्णांक घातer_level;
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	u32 debug_level;
#पूर्ण_अगर
	अक्षर *nvm_file;
	u32 uapsd_disable;
	bool disable_11ac;
	/**
	 * @disable_11ax: disable HE capabilities, शेष = false
	 */
	bool disable_11ax;
	bool हटाओ_when_gone;
	bool enable_ini;
पूर्ण;

अटल अंतरभूत bool iwl_enable_rx_ampdu(व्योम)
अणु
	अगर (iwlwअगरi_mod_params.disable_11n & IWL_DISABLE_HT_RXAGG)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool iwl_enable_tx_ampdu(व्योम)
अणु
	अगर (iwlwअगरi_mod_params.disable_11n & IWL_DISABLE_HT_TXAGG)
		वापस false;
	अगर (iwlwअगरi_mod_params.disable_11n & IWL_ENABLE_HT_TXAGG)
		वापस true;

	/* enabled by शेष */
	वापस true;
पूर्ण

#पूर्ण_अगर /* #__iwl_modparams_h__ */
