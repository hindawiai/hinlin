<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Freescale SOC support functions
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "types.h"
#समावेश "fsl-soc.h"
#समावेश "stdio.h"

अटल u32 prop_buf[MAX_PROP_LEN / 4];

u32 *fsl_get_immr(व्योम)
अणु
	व्योम *soc;
	अचिन्हित दीर्घ ret = 0;

	soc = find_node_by_devtype(शून्य, "soc");
	अगर (soc) अणु
		पूर्णांक size;
		u32 naddr;

		size = getprop(soc, "#address-cells", prop_buf, MAX_PROP_LEN);
		अगर (size == 4)
			naddr = prop_buf[0];
		अन्यथा
			naddr = 2;

		अगर (naddr != 1 && naddr != 2)
			जाओ err;

		size = getprop(soc, "ranges", prop_buf, MAX_PROP_LEN);

		अगर (size < 12)
			जाओ err;
		अगर (prop_buf[0] != 0)
			जाओ err;
		अगर (naddr == 2 && prop_buf[1] != 0)
			जाओ err;

		अगर (!dt_xlate_addr(soc, prop_buf + naddr, 8, &ret))
			ret = 0;
	पूर्ण

err:
	अगर (!ret)
		म_लिखो("fsl_get_immr: Failed to find immr base\r\n");

	वापस (u32 *)ret;
पूर्ण
