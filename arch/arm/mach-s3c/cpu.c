<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2009-2011 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// Samsung CPU Support

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <mach/map-base.h>
#समावेश "cpu.h"

अचिन्हित दीर्घ samsung_cpu_id;

व्योम __init s3c64xx_init_cpu(व्योम)
अणु
	samsung_cpu_id = पढ़ोl_relaxed(S3C_VA_SYS + 0x118);
	अगर (!samsung_cpu_id) अणु
		/*
		 * S3C6400 has the ID रेजिस्टर in a dअगरferent place,
		 * and needs a ग_लिखो beक्रमe it can be पढ़ो.
		 */
		ग_लिखोl_relaxed(0x0, S3C_VA_SYS + 0xA1C);
		samsung_cpu_id = पढ़ोl_relaxed(S3C_VA_SYS + 0xA1C);
	पूर्ण

	pr_info("Samsung CPU ID: 0x%08lx\n", samsung_cpu_id);
पूर्ण
