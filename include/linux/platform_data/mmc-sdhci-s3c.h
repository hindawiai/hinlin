<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PLATFORM_DATA_SDHCI_S3C_H
#घोषणा __PLATFORM_DATA_SDHCI_S3C_H

काष्ठा platक्रमm_device;

क्रमागत cd_types अणु
	S3C_SDHCI_CD_INTERNAL,	/* use mmc पूर्णांकernal CD line */
	S3C_SDHCI_CD_EXTERNAL,	/* use बाह्यal callback */
	S3C_SDHCI_CD_GPIO,	/* use बाह्यal gpio pin क्रम CD line */
	S3C_SDHCI_CD_NONE,	/* no CD line, use polling to detect card */
	S3C_SDHCI_CD_PERMANENT,	/* no CD line, card permanently wired to host */
पूर्ण;

/**
 * काष्ठा s3c_sdhci_platdata() - Platक्रमm device data क्रम Samsung SDHCI
 * @max_width: The maximum number of data bits supported.
 * @host_caps: Standard MMC host capabilities bit field.
 * @host_caps2: The second standard MMC host capabilities bit field.
 * @cd_type: Type of Card Detection method (see cd_types क्रमागत above)
 * @ext_cd_init: Initialize बाह्यal card detect subप्रणाली. Called on
 *		 sdhci-s3c driver probe when cd_type == S3C_SDHCI_CD_EXTERNAL.
 *		 notअगरy_func argument is a callback to the sdhci-s3c driver
 *		 that triggers the card detection event. Callback arguments:
 *		 dev is poपूर्णांकer to platक्रमm device of the host controller,
 *		 state is new state of the card (0 - हटाओd, 1 - inserted).
 * @ext_cd_cleanup: Cleanup बाह्यal card detect subप्रणाली. Called on
 *		 sdhci-s3c driver हटाओ when cd_type == S3C_SDHCI_CD_EXTERNAL.
 *		 notअगरy_func argument is the same callback as क्रम ext_cd_init.
 * @ext_cd_gpio: gpio pin used क्रम बाह्यal CD line, valid only अगर
 *		 cd_type == S3C_SDHCI_CD_GPIO
 * @ext_cd_gpio_invert: invert values क्रम बाह्यal CD gpio line
 * @cfg_gpio: Configure the GPIO क्रम a specअगरic card bit-width
 *
 * Initialisation data specअगरic to either the machine or the platक्रमm
 * क्रम the device driver to use or call-back when configuring gpio or
 * card speed inक्रमmation.
*/
काष्ठा s3c_sdhci_platdata अणु
	अचिन्हित पूर्णांक	max_width;
	अचिन्हित पूर्णांक	host_caps;
	अचिन्हित पूर्णांक	host_caps2;
	अचिन्हित पूर्णांक	pm_caps;
	क्रमागत cd_types	cd_type;

	पूर्णांक		ext_cd_gpio;
	bool		ext_cd_gpio_invert;
	पूर्णांक	(*ext_cd_init)(व्योम (*notअगरy_func)(काष्ठा platक्रमm_device *,
						   पूर्णांक state));
	पूर्णांक	(*ext_cd_cleanup)(व्योम (*notअगरy_func)(काष्ठा platक्रमm_device *,
						      पूर्णांक state));

	व्योम	(*cfg_gpio)(काष्ठा platक्रमm_device *dev, पूर्णांक width);
पूर्ण;


#पूर्ण_अगर /* __PLATFORM_DATA_SDHCI_S3C_H */
