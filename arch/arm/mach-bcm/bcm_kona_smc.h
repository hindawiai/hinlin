<शैली गुरु>
/*
 * Copyright (C) 2013 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित BCM_KONA_SMC_H
#घोषणा BCM_KONA_SMC_H

#समावेश <linux/types.h>

/* Broadcom Secure Service API service IDs, वापस codes, and निकास codes */
#घोषणा SSAPI_ENABLE_L2_CACHE		0x01000002
#घोषणा SEC_ROM_RET_OK			0x00000001
#घोषणा SEC_EXIT_NORMAL			0x1

बाह्य पूर्णांक __init bcm_kona_smc_init(व्योम);

बाह्य अचिन्हित bcm_kona_smc(अचिन्हित service_id,
			     अचिन्हित arg0,
			     अचिन्हित arg1,
			     अचिन्हित arg2,
			     अचिन्हित arg3);

#पूर्ण_अगर /* BCM_KONA_SMC_H */
