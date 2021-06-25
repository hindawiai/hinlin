<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_MCF_ESDHC_H__
#घोषणा __LINUX_PLATFORM_DATA_MCF_ESDHC_H__

क्रमागत cd_types अणु
	ESDHC_CD_NONE,		/* no CD, neither controller nor gpio */
	ESDHC_CD_CONTROLLER,	/* mmc controller पूर्णांकernal CD */
	ESDHC_CD_PERMANENT,	/* no CD, card permanently wired to host */
पूर्ण;

काष्ठा mcf_esdhc_platक्रमm_data अणु
	पूर्णांक max_bus_width;
	पूर्णांक cd_type;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PLATFORM_DATA_MCF_ESDHC_H__ */
