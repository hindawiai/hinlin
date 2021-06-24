<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AMCC SoC PPC4xx Crypto Driver
 *
 * Copyright (c) 2008 Applied Micro Circuits Corporation.
 * All rights reserved. James Hsiao <jhsiao@amcc.com>
 *
 * This file defines the security context
 * associate क्रमmat.
 */

#अगर_अघोषित __CRYPTO4XX_TRNG_H__
#घोषणा __CRYPTO4XX_TRNG_H__

#अगर_घोषित CONFIG_HW_RANDOM_PPC4XX
व्योम ppc4xx_trng_probe(काष्ठा crypto4xx_core_device *core_dev);
व्योम ppc4xx_trng_हटाओ(काष्ठा crypto4xx_core_device *core_dev);
#अन्यथा
अटल अंतरभूत व्योम ppc4xx_trng_probe(
	काष्ठा crypto4xx_core_device *dev __maybe_unused) अणु पूर्ण
अटल अंतरभूत व्योम ppc4xx_trng_हटाओ(
	काष्ठा crypto4xx_core_device *dev __maybe_unused) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
