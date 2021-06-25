<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014 Marvell Technology Group Ltd.
 *
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 */
#अगर_अघोषित __BERLIN2_PLL_H
#घोषणा __BERLIN2_PLL_H

काष्ठा berlin2_pll_map अणु
	स्थिर u8 vcoभाग[16];
	u8 mult;
	u8 fbभाग_shअगरt;
	u8 rfभाग_shअगरt;
	u8 भागsel_shअगरt;
पूर्ण;

पूर्णांक berlin2_pll_रेजिस्टर(स्थिर काष्ठा berlin2_pll_map *map,
			 व्योम __iomem *base, स्थिर अक्षर *name,
			 स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags);

#पूर्ण_अगर /* __BERLIN2_PLL_H */
