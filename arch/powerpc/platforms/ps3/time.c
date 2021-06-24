<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 समय and rtc routines.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3.h>

#समावेश "platform.h"

व्योम __init ps3_calibrate_decr(व्योम)
अणु
	पूर्णांक result;
	u64 पंचांगp;

	result = ps3_repository_पढ़ो_be_tb_freq(0, &पंचांगp);
	BUG_ON(result);

	ppc_tb_freq = पंचांगp;
	ppc_proc_freq = ppc_tb_freq * 40;
पूर्ण

अटल u64 पढ़ो_rtc(व्योम)
अणु
	पूर्णांक result;
	u64 rtc_val;
	u64 tb_val;

	result = lv1_get_rtc(&rtc_val, &tb_val);
	BUG_ON(result);

	वापस rtc_val;
पूर्ण

समय64_t __init ps3_get_boot_समय(व्योम)
अणु
	वापस पढ़ो_rtc() + ps3_os_area_get_rtc_dअगरf();
पूर्ण

अटल पूर्णांक __init ps3_rtc_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	pdev = platक्रमm_device_रेजिस्टर_simple("rtc-ps3", -1, शून्य, 0);

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
device_initcall(ps3_rtc_init);
