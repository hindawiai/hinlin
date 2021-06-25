<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2015,2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/crc32.h>
#समावेश "wil6210.h"
#समावेश "fw.h"

MODULE_FIRMWARE(WIL_FW_NAME_DEFAULT);
MODULE_FIRMWARE(WIL_FW_NAME_SPARROW_PLUS);
MODULE_FIRMWARE(WIL_BOARD_खाता_NAME);
MODULE_FIRMWARE(WIL_FW_NAME_TALYN);
MODULE_FIRMWARE(WIL_BRD_NAME_TALYN);

अटल
व्योम wil_स_रखो_toio_32(अस्थिर व्योम __iomem *dst, u32 val,
			माप_प्रकार count)
अणु
	अस्थिर u32 __iomem *d = dst;

	क्रम (count += 4; count > 4; count -= 4)
		__raw_ग_लिखोl(val, d++);
पूर्ण

#समावेश "fw_inc.c"
