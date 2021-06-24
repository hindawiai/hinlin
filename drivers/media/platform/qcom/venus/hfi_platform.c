<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */
#समावेश "hfi_platform.h"

स्थिर काष्ठा hfi_platक्रमm *hfi_platक्रमm_get(क्रमागत hfi_version version)
अणु
	चयन (version) अणु
	हाल HFI_VERSION_4XX:
		वापस &hfi_plat_v4;
	हाल HFI_VERSION_6XX:
		वापस &hfi_plat_v6;
	शेष:
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अचिन्हित दीर्घ
hfi_platक्रमm_get_codec_vpp_freq(क्रमागत hfi_version version, u32 codec, u32 session_type)
अणु
	स्थिर काष्ठा hfi_platक्रमm *plat;
	अचिन्हित दीर्घ freq = 0;

	plat = hfi_platक्रमm_get(version);
	अगर (!plat)
		वापस 0;

	अगर (plat->codec_vpp_freq)
		freq = plat->codec_vpp_freq(session_type, codec);

	वापस freq;
पूर्ण

अचिन्हित दीर्घ
hfi_platक्रमm_get_codec_vsp_freq(क्रमागत hfi_version version, u32 codec, u32 session_type)
अणु
	स्थिर काष्ठा hfi_platक्रमm *plat;
	अचिन्हित दीर्घ freq = 0;

	plat = hfi_platक्रमm_get(version);
	अगर (!plat)
		वापस 0;

	अगर (plat->codec_vpp_freq)
		freq = plat->codec_vsp_freq(session_type, codec);

	वापस freq;
पूर्ण

u8 hfi_platक्रमm_num_vpp_pipes(क्रमागत hfi_version version)
अणु
	स्थिर काष्ठा hfi_platक्रमm *plat;

	plat = hfi_platक्रमm_get(version);
	अगर (!plat)
		वापस 0;

	अगर (plat->num_vpp_pipes)
		वापस plat->num_vpp_pipes();

	वापस 0;
पूर्ण
