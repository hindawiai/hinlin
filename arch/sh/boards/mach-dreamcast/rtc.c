<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/dreamcast/rtc.c
 *
 * Dreamcast AICA RTC routines.
 *
 * Copyright (c) 2001, 2002 M. R. Brown <mrbrown@0xd6.org>
 * Copyright (c) 2002 Paul Mundt <lethal@chaoticdreams.org>
 */

#समावेश <linux/समय.स>
#समावेश <linux/rtc.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>

/* The AICA RTC has an Epoch of 1/1/1950, so we must subtract 20 years (in
   seconds) to get the standard Unix Epoch when getting the समय, and add
   20 years when setting the समय. */
#घोषणा TWENTY_YEARS ((20 * 365LU + 5) * 86400)

/* The AICA RTC is represented by a 32-bit seconds counter stored in 2 16-bit
   रेजिस्टरs.*/
#घोषणा AICA_RTC_SECS_H		0xa0710000
#घोषणा AICA_RTC_SECS_L		0xa0710004

/**
 * aica_rtc_समय_लोofday - Get the समय from the AICA RTC
 * @dev: the RTC device (ignored)
 * @पंचांग: poपूर्णांकer to resulting RTC समय काष्ठाure
 *
 * Grअसल the current RTC seconds counter and adjusts it to the Unix Epoch.
 */
अटल पूर्णांक aica_rtc_समय_लोofday(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ val1, val2;
	समय64_t t;

	करो अणु
		val1 = ((__raw_पढ़ोl(AICA_RTC_SECS_H) & 0xffff) << 16) |
			(__raw_पढ़ोl(AICA_RTC_SECS_L) & 0xffff);

		val2 = ((__raw_पढ़ोl(AICA_RTC_SECS_H) & 0xffff) << 16) |
			(__raw_पढ़ोl(AICA_RTC_SECS_L) & 0xffff);
	पूर्ण जबतक (val1 != val2);

	/* normalize to 1970..2106 समय range */
	t = (u32)(val1 - TWENTY_YEARS);

	rtc_समय64_to_पंचांग(t, पंचांग);

	वापस 0;
पूर्ण

/**
 * aica_rtc_समय_रखोofday - Set the AICA RTC to the current समय
 * @dev: the RTC device (ignored)
 * @पंचांग: poपूर्णांकer to new RTC समय काष्ठाure
 *
 * Adjusts the given @tv to the AICA Epoch and sets the RTC seconds counter.
 */
अटल पूर्णांक aica_rtc_समय_रखोofday(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ val1, val2;
	समय64_t secs = rtc_पंचांग_to_समय64(पंचांग);
	u32 adj = secs + TWENTY_YEARS;

	करो अणु
		__raw_ग_लिखोl((adj & 0xffff0000) >> 16, AICA_RTC_SECS_H);
		__raw_ग_लिखोl((adj & 0xffff), AICA_RTC_SECS_L);

		val1 = ((__raw_पढ़ोl(AICA_RTC_SECS_H) & 0xffff) << 16) |
			(__raw_पढ़ोl(AICA_RTC_SECS_L) & 0xffff);

		val2 = ((__raw_पढ़ोl(AICA_RTC_SECS_H) & 0xffff) << 16) |
			(__raw_पढ़ोl(AICA_RTC_SECS_L) & 0xffff);
	पूर्ण जबतक (val1 != val2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtc_generic_ops = अणु
	.पढ़ो_समय = aica_rtc_समय_लोofday,
	.set_समय = aica_rtc_समय_रखोofday,
पूर्ण;

अटल पूर्णांक __init aica_समय_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "rtc-generic", -1,
					     &rtc_generic_ops,
					     माप(rtc_generic_ops));

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
arch_initcall(aica_समय_init);
