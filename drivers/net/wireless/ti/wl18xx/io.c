<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments
 */

#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/io.h"

#समावेश "io.h"

पूर्णांक wl18xx_top_reg_ग_लिखो(काष्ठा wl1271 *wl, पूर्णांक addr, u16 val)
अणु
	u32 पंचांगp;
	पूर्णांक ret;

	अगर (WARN_ON(addr % 2))
		वापस -EINVAL;

	अगर ((addr % 4) == 0) अणु
		ret = wlcore_पढ़ो32(wl, addr, &पंचांगp);
		अगर (ret < 0)
			जाओ out;

		पंचांगp = (पंचांगp & 0xffff0000) | val;
		ret = wlcore_ग_लिखो32(wl, addr, पंचांगp);
	पूर्ण अन्यथा अणु
		ret = wlcore_पढ़ो32(wl, addr - 2, &पंचांगp);
		अगर (ret < 0)
			जाओ out;

		पंचांगp = (पंचांगp & 0xffff) | (val << 16);
		ret = wlcore_ग_लिखो32(wl, addr - 2, पंचांगp);
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक wl18xx_top_reg_पढ़ो(काष्ठा wl1271 *wl, पूर्णांक addr, u16 *out)
अणु
	u32 val = 0;
	पूर्णांक ret;

	अगर (WARN_ON(addr % 2))
		वापस -EINVAL;

	अगर ((addr % 4) == 0) अणु
		/* address is 4-bytes aligned */
		ret = wlcore_पढ़ो32(wl, addr, &val);
		अगर (ret >= 0 && out)
			*out = val & 0xffff;
	पूर्ण अन्यथा अणु
		ret = wlcore_पढ़ो32(wl, addr - 2, &val);
		अगर (ret >= 0 && out)
			*out = (val & 0xffff0000) >> 16;
	पूर्ण

	वापस ret;
पूर्ण
