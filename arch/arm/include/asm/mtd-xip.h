<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MTD primitives क्रम XIP support. Architecture specअगरic functions
 *
 * Do not include this file directly. It's included from linux/mtd/xip.h
 * 
 * Author:	Nicolas Pitre
 * Created:	Nov 2, 2004
 * Copyright:	(C) 2004 MontaVista Software, Inc.
 */

#अगर_अघोषित __ARM_MTD_XIP_H__
#घोषणा __ARM_MTD_XIP_H__

#समावेश <mach/mtd-xip.h>

/* fill inकाष्ठाion prefetch */
#घोषणा xip_iprefetch() 	करो अणु यंत्र अस्थिर (".rep 8; nop; .endr"); पूर्ण जबतक (0)

#पूर्ण_अगर /* __ARM_MTD_XIP_H__ */
