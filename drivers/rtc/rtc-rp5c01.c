<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Ricoh RP5C01 RTC Driver
 *
 *  Copyright 2009 Geert Uytterhoeven
 *
 *  Based on the A3000 TOD code in arch/m68k/amiga/config.c
 *  Copyright (C) 1993 Hamish Macकरोnald
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>


क्रमागत अणु
	RP5C01_1_SECOND		= 0x0,	/* MODE 00 */
	RP5C01_10_SECOND	= 0x1,	/* MODE 00 */
	RP5C01_1_MINUTE		= 0x2,	/* MODE 00 and MODE 01 */
	RP5C01_10_MINUTE	= 0x3,	/* MODE 00 and MODE 01 */
	RP5C01_1_HOUR		= 0x4,	/* MODE 00 and MODE 01 */
	RP5C01_10_HOUR		= 0x5,	/* MODE 00 and MODE 01 */
	RP5C01_DAY_OF_WEEK	= 0x6,	/* MODE 00 and MODE 01 */
	RP5C01_1_DAY		= 0x7,	/* MODE 00 and MODE 01 */
	RP5C01_10_DAY		= 0x8,	/* MODE 00 and MODE 01 */
	RP5C01_1_MONTH		= 0x9,	/* MODE 00 */
	RP5C01_10_MONTH		= 0xa,	/* MODE 00 */
	RP5C01_1_YEAR		= 0xb,	/* MODE 00 */
	RP5C01_10_YEAR		= 0xc,	/* MODE 00 */

	RP5C01_12_24_SELECT	= 0xa,	/* MODE 01 */
	RP5C01_LEAP_YEAR	= 0xb,	/* MODE 01 */

	RP5C01_MODE		= 0xd,	/* all modes */
	RP5C01_TEST		= 0xe,	/* all modes */
	RP5C01_RESET		= 0xf,	/* all modes */
पूर्ण;

#घोषणा RP5C01_12_24_SELECT_12	(0 << 0)
#घोषणा RP5C01_12_24_SELECT_24	(1 << 0)

#घोषणा RP5C01_10_HOUR_AM	(0 << 1)
#घोषणा RP5C01_10_HOUR_PM	(1 << 1)

#घोषणा RP5C01_MODE_TIMER_EN	(1 << 3)	/* समयr enable */
#घोषणा RP5C01_MODE_ALARM_EN	(1 << 2)	/* alarm enable */

#घोषणा RP5C01_MODE_MODE_MASK	(3 << 0)
#घोषणा RP5C01_MODE_MODE00	(0 << 0)	/* समय */
#घोषणा RP5C01_MODE_MODE01	(1 << 0)	/* alarm, 12h/24h, leap year */
#घोषणा RP5C01_MODE_RAM_BLOCK10	(2 << 0)	/* RAM 4 bits x 13 */
#घोषणा RP5C01_MODE_RAM_BLOCK11	(3 << 0)	/* RAM 4 bits x 13 */

#घोषणा RP5C01_RESET_1HZ_PULSE	(1 << 3)
#घोषणा RP5C01_RESET_16HZ_PULSE	(1 << 2)
#घोषणा RP5C01_RESET_SECOND	(1 << 1)	/* reset भागider stages क्रम */
						/* seconds or smaller units */
#घोषणा RP5C01_RESET_ALARM	(1 << 0)	/* reset all alarm रेजिस्टरs */


काष्ठा rp5c01_priv अणु
	u32 __iomem *regs;
	काष्ठा rtc_device *rtc;
	spinlock_t lock;	/* against concurrent RTC/NVRAM access */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक rp5c01_पढ़ो(काष्ठा rp5c01_priv *priv,
				       अचिन्हित पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(&priv->regs[reg]) & 0xf;
पूर्ण

अटल अंतरभूत व्योम rp5c01_ग_लिखो(काष्ठा rp5c01_priv *priv, अचिन्हित पूर्णांक val,
				अचिन्हित पूर्णांक reg)
अणु
	__raw_ग_लिखोl(val, &priv->regs[reg]);
पूर्ण

अटल व्योम rp5c01_lock(काष्ठा rp5c01_priv *priv)
अणु
	rp5c01_ग_लिखो(priv, RP5C01_MODE_MODE00, RP5C01_MODE);
पूर्ण

अटल व्योम rp5c01_unlock(काष्ठा rp5c01_priv *priv)
अणु
	rp5c01_ग_लिखो(priv, RP5C01_MODE_TIMER_EN | RP5C01_MODE_MODE01,
		     RP5C01_MODE);
पूर्ण

अटल पूर्णांक rp5c01_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rp5c01_priv *priv = dev_get_drvdata(dev);

	spin_lock_irq(&priv->lock);
	rp5c01_lock(priv);

	पंचांग->पंचांग_sec  = rp5c01_पढ़ो(priv, RP5C01_10_SECOND) * 10 +
		      rp5c01_पढ़ो(priv, RP5C01_1_SECOND);
	पंचांग->पंचांग_min  = rp5c01_पढ़ो(priv, RP5C01_10_MINUTE) * 10 +
		      rp5c01_पढ़ो(priv, RP5C01_1_MINUTE);
	पंचांग->पंचांग_hour = rp5c01_पढ़ो(priv, RP5C01_10_HOUR) * 10 +
		      rp5c01_पढ़ो(priv, RP5C01_1_HOUR);
	पंचांग->पंचांग_mday = rp5c01_पढ़ो(priv, RP5C01_10_DAY) * 10 +
		      rp5c01_पढ़ो(priv, RP5C01_1_DAY);
	पंचांग->पंचांग_wday = rp5c01_पढ़ो(priv, RP5C01_DAY_OF_WEEK);
	पंचांग->पंचांग_mon  = rp5c01_पढ़ो(priv, RP5C01_10_MONTH) * 10 +
		      rp5c01_पढ़ो(priv, RP5C01_1_MONTH) - 1;
	पंचांग->पंचांग_year = rp5c01_पढ़ो(priv, RP5C01_10_YEAR) * 10 +
		      rp5c01_पढ़ो(priv, RP5C01_1_YEAR);
	अगर (पंचांग->पंचांग_year <= 69)
		पंचांग->पंचांग_year += 100;

	rp5c01_unlock(priv);
	spin_unlock_irq(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rp5c01_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rp5c01_priv *priv = dev_get_drvdata(dev);

	spin_lock_irq(&priv->lock);
	rp5c01_lock(priv);

	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_sec / 10, RP5C01_10_SECOND);
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_sec % 10, RP5C01_1_SECOND);
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_min / 10, RP5C01_10_MINUTE);
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_min % 10, RP5C01_1_MINUTE);
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_hour / 10, RP5C01_10_HOUR);
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_hour % 10, RP5C01_1_HOUR);
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_mday / 10, RP5C01_10_DAY);
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_mday % 10, RP5C01_1_DAY);
	अगर (पंचांग->पंचांग_wday != -1)
		rp5c01_ग_लिखो(priv, पंचांग->पंचांग_wday, RP5C01_DAY_OF_WEEK);
	rp5c01_ग_लिखो(priv, (पंचांग->पंचांग_mon + 1) / 10, RP5C01_10_MONTH);
	rp5c01_ग_लिखो(priv, (पंचांग->पंचांग_mon + 1) % 10, RP5C01_1_MONTH);
	अगर (पंचांग->पंचांग_year >= 100)
		पंचांग->पंचांग_year -= 100;
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_year / 10, RP5C01_10_YEAR);
	rp5c01_ग_लिखो(priv, पंचांग->पंचांग_year % 10, RP5C01_1_YEAR);

	rp5c01_unlock(priv);
	spin_unlock_irq(&priv->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rp5c01_rtc_ops = अणु
	.पढ़ो_समय	= rp5c01_पढ़ो_समय,
	.set_समय	= rp5c01_set_समय,
पूर्ण;


/*
 * The NVRAM is organized as 2 blocks of 13 nibbles of 4 bits.
 * We provide access to them like AmigaOS करोes: the high nibble of each 8-bit
 * byte is stored in BLOCK10, the low nibble in BLOCK11.
 */

अटल पूर्णांक rp5c01_nvram_पढ़ो(व्योम *_priv, अचिन्हित पूर्णांक pos, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा rp5c01_priv *priv = _priv;
	u8 *buf = val;

	spin_lock_irq(&priv->lock);

	क्रम (; bytes; bytes--) अणु
		u8 data;

		rp5c01_ग_लिखो(priv,
			     RP5C01_MODE_TIMER_EN | RP5C01_MODE_RAM_BLOCK10,
			     RP5C01_MODE);
		data = rp5c01_पढ़ो(priv, pos) << 4;
		rp5c01_ग_लिखो(priv,
			     RP5C01_MODE_TIMER_EN | RP5C01_MODE_RAM_BLOCK11,
			     RP5C01_MODE);
		data |= rp5c01_पढ़ो(priv, pos++);
		rp5c01_ग_लिखो(priv, RP5C01_MODE_TIMER_EN | RP5C01_MODE_MODE01,
			     RP5C01_MODE);
		*buf++ = data;
	पूर्ण

	spin_unlock_irq(&priv->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक rp5c01_nvram_ग_लिखो(व्योम *_priv, अचिन्हित पूर्णांक pos, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा rp5c01_priv *priv = _priv;
	u8 *buf = val;

	spin_lock_irq(&priv->lock);

	क्रम (; bytes; bytes--) अणु
		u8 data = *buf++;

		rp5c01_ग_लिखो(priv,
			     RP5C01_MODE_TIMER_EN | RP5C01_MODE_RAM_BLOCK10,
			     RP5C01_MODE);
		rp5c01_ग_लिखो(priv, data >> 4, pos);
		rp5c01_ग_लिखो(priv,
			     RP5C01_MODE_TIMER_EN | RP5C01_MODE_RAM_BLOCK11,
			     RP5C01_MODE);
		rp5c01_ग_लिखो(priv, data & 0xf, pos++);
		rp5c01_ग_लिखो(priv, RP5C01_MODE_TIMER_EN | RP5C01_MODE_MODE01,
			     RP5C01_MODE);
	पूर्ण

	spin_unlock_irq(&priv->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __init rp5c01_rtc_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा resource *res;
	काष्ठा rp5c01_priv *priv;
	काष्ठा rtc_device *rtc;
	पूर्णांक error;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "rp5c01_nvram",
		.word_size = 1,
		.stride = 1,
		.size = RP5C01_MODE,
		.reg_पढ़ो = rp5c01_nvram_पढ़ो,
		.reg_ग_लिखो = rp5c01_nvram_ग_लिखो,
	पूर्ण;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	priv = devm_kzalloc(&dev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regs = devm_ioremap(&dev->dev, res->start, resource_size(res));
	अगर (!priv->regs)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);

	platक्रमm_set_drvdata(dev, priv);

	rtc = devm_rtc_allocate_device(&dev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = &rp5c01_rtc_ops;

	priv->rtc = rtc;

	nvmem_cfg.priv = priv;
	error = devm_rtc_nvmem_रेजिस्टर(rtc, &nvmem_cfg);
	अगर (error)
		वापस error;

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver rp5c01_rtc_driver = अणु
	.driver	= अणु
		.name	= "rtc-rp5c01",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(rp5c01_rtc_driver, rp5c01_rtc_probe);

MODULE_AUTHOR("Geert Uytterhoeven <geert@linux-m68k.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ricoh RP5C01 RTC driver");
MODULE_ALIAS("platform:rtc-rp5c01");
