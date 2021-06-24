<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <यंत्र/processor.h>
#समावेश "cpu.h"

/*
 * UMC chips appear to be only either 386 or 486,
 * so no special init takes place.
 */

अटल स्थिर काष्ठा cpu_dev umc_cpu_dev = अणु
	.c_venकरोr	= "UMC",
	.c_ident	= अणु "UMC UMC UMC" पूर्ण,
	.legacy_models	= अणु
		अणु .family = 4, .model_names =
		  अणु
			  [1] = "U5D",
			  [2] = "U5S",
		  पूर्ण
		पूर्ण,
	पूर्ण,
	.c_x86_venकरोr	= X86_VENDOR_UMC,
पूर्ण;

cpu_dev_रेजिस्टर(umc_cpu_dev);

