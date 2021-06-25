<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014 Marvell Technology Group Ltd.
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 */
#अगर_अघोषित __BERLIN2_AVPLL_H
#घोषणा __BERLIN2_AVPLL_H

#घोषणा BERLIN2_AVPLL_BIT_QUIRK		BIT(0)
#घोषणा BERLIN2_AVPLL_SCRAMBLE_QUIRK	BIT(1)

पूर्णांक berlin2_avpll_vco_रेजिस्टर(व्योम __iomem *base, स्थिर अक्षर *name,
	   स्थिर अक्षर *parent_name, u8 vco_flags, अचिन्हित दीर्घ flags);

पूर्णांक berlin2_avpll_channel_रेजिस्टर(व्योम __iomem *base, स्थिर अक्षर *name,
		       u8 index, स्थिर अक्षर *parent_name, u8 ch_flags,
		       अचिन्हित दीर्घ flags);

#पूर्ण_अगर /* __BERLIN2_AVPLL_H */
