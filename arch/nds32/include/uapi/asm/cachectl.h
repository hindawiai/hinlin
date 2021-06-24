<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
// Copyright (C) 1994, 1995, 1996 by Ralf Baechle
// Copyright (C) 2005-2017 Andes Technology Corporation
#अगर_अघोषित	_ASM_CACHECTL
#घोषणा	_ASM_CACHECTL

/*
 * Options क्रम cacheflush प्रणाली call
 */
#घोषणा	ICACHE	0		/* flush inकाष्ठाion cache        */
#घोषणा	DCACHE	1		/* ग_लिखोback and flush data cache */
#घोषणा	BCACHE	2		/* flush inकाष्ठाion cache + ग_लिखोback and flush data cache */

#पूर्ण_अगर /* _ASM_CACHECTL */
