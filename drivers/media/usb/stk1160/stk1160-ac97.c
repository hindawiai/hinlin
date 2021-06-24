<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STK1160 driver
 *
 * Copyright (C) 2012 Ezequiel Garcia
 * <elezegarcia--a.t--gmail.com>
 *
 * Copyright (C) 2016 Marcel Hasler
 * <mahasler--a.t--gmail.com>
 *
 * Based on Easycap driver by R.M. Thomas
 *	Copyright (C) 2010 R.M. Thomas
 *	<rmthomas--a.t--sciolus.org>
 */

#समावेश <linux/delay.h>

#समावेश "stk1160.h"
#समावेश "stk1160-reg.h"

अटल पूर्णांक stk1160_ac97_रुको_transfer_complete(काष्ठा stk1160 *dev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(STK1160_AC97_TIMEOUT);
	u8 value;

	/* Wait क्रम AC97 transfer to complete */
	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		stk1160_पढ़ो_reg(dev, STK1160_AC97CTL_0, &value);

		अगर (!(value & (STK1160_AC97CTL_0_CR | STK1160_AC97CTL_0_CW)))
			वापस 0;

		usleep_range(50, 100);
	पूर्ण

	stk1160_err("AC97 transfer took too long, this should never happen!");
	वापस -EBUSY;
पूर्ण

अटल व्योम stk1160_ग_लिखो_ac97(काष्ठा stk1160 *dev, u16 reg, u16 value)
अणु
	/* Set codec रेजिस्टर address */
	stk1160_ग_लिखो_reg(dev, STK1160_AC97_ADDR, reg);

	/* Set codec command */
	stk1160_ग_लिखो_reg(dev, STK1160_AC97_CMD, value & 0xff);
	stk1160_ग_लिखो_reg(dev, STK1160_AC97_CMD + 1, (value & 0xff00) >> 8);

	/* Set command ग_लिखो bit to initiate ग_लिखो operation */
	stk1160_ग_लिखो_reg(dev, STK1160_AC97CTL_0, 0x8c);

	/* Wait क्रम command ग_लिखो bit to be cleared */
	stk1160_ac97_रुको_transfer_complete(dev);
पूर्ण

#अगर_घोषित DEBUG
अटल u16 stk1160_पढ़ो_ac97(काष्ठा stk1160 *dev, u16 reg)
अणु
	u8 vall = 0;
	u8 valh = 0;

	/* Set codec रेजिस्टर address */
	stk1160_ग_लिखो_reg(dev, STK1160_AC97_ADDR, reg);

	/* Set command पढ़ो bit to initiate पढ़ो operation */
	stk1160_ग_लिखो_reg(dev, STK1160_AC97CTL_0, 0x8b);

	/* Wait क्रम command पढ़ो bit to be cleared */
	अगर (stk1160_ac97_रुको_transfer_complete(dev) < 0)
		वापस 0;


	/* Retrieve रेजिस्टर value */
	stk1160_पढ़ो_reg(dev, STK1160_AC97_CMD, &vall);
	stk1160_पढ़ो_reg(dev, STK1160_AC97_CMD + 1, &valh);

	वापस (valh << 8) | vall;
पूर्ण

व्योम stk1160_ac97_dump_regs(काष्ठा stk1160 *dev)
अणु
	u16 value;

	value = stk1160_पढ़ो_ac97(dev, 0x12); /* CD volume */
	stk1160_dbg("0x12 == 0x%04x", value);

	value = stk1160_पढ़ो_ac97(dev, 0x10); /* Line-in volume */
	stk1160_dbg("0x10 == 0x%04x", value);

	value = stk1160_पढ़ो_ac97(dev, 0x0e); /* MIC volume (mono) */
	stk1160_dbg("0x0e == 0x%04x", value);

	value = stk1160_पढ़ो_ac97(dev, 0x16); /* Aux volume */
	stk1160_dbg("0x16 == 0x%04x", value);

	value = stk1160_पढ़ो_ac97(dev, 0x1a); /* Record select */
	stk1160_dbg("0x1a == 0x%04x", value);

	value = stk1160_पढ़ो_ac97(dev, 0x02); /* Master volume */
	stk1160_dbg("0x02 == 0x%04x", value);

	value = stk1160_पढ़ो_ac97(dev, 0x1c); /* Record gain */
	stk1160_dbg("0x1c == 0x%04x", value);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक stk1160_has_audio(काष्ठा stk1160 *dev)
अणु
	u8 value;

	stk1160_पढ़ो_reg(dev, STK1160_POSV_L, &value);
	वापस !(value & STK1160_POSV_L_ACDOUT);
पूर्ण

अटल पूर्णांक stk1160_has_ac97(काष्ठा stk1160 *dev)
अणु
	u8 value;

	stk1160_पढ़ो_reg(dev, STK1160_POSV_L, &value);
	वापस !(value & STK1160_POSV_L_ACSYNC);
पूर्ण

व्योम stk1160_ac97_setup(काष्ठा stk1160 *dev)
अणु
	अगर (!stk1160_has_audio(dev)) अणु
		stk1160_info("Device doesn't support audio, skipping AC97 setup.");
		वापस;
	पूर्ण

	अगर (!stk1160_has_ac97(dev)) अणु
		stk1160_info("Device uses internal 8-bit ADC, skipping AC97 setup.");
		वापस;
	पूर्ण

	/* Two-step reset AC97 पूर्णांकerface and hardware codec */
	stk1160_ग_लिखो_reg(dev, STK1160_AC97CTL_0, 0x94);
	stk1160_ग_लिखो_reg(dev, STK1160_AC97CTL_0, 0x8c);

	/* Set 16-bit audio data and choose L&R channel*/
	stk1160_ग_लिखो_reg(dev, STK1160_AC97CTL_1 + 2, 0x01);
	stk1160_ग_लिखो_reg(dev, STK1160_AC97CTL_1 + 3, 0x00);

	/* Setup channels */
	stk1160_ग_लिखो_ac97(dev, 0x12, 0x8808); /* CD volume */
	stk1160_ग_लिखो_ac97(dev, 0x10, 0x0808); /* Line-in volume */
	stk1160_ग_लिखो_ac97(dev, 0x0e, 0x0008); /* MIC volume (mono) */
	stk1160_ग_लिखो_ac97(dev, 0x16, 0x0808); /* Aux volume */
	stk1160_ग_लिखो_ac97(dev, 0x1a, 0x0404); /* Record select */
	stk1160_ग_लिखो_ac97(dev, 0x02, 0x0000); /* Master volume */
	stk1160_ग_लिखो_ac97(dev, 0x1c, 0x0808); /* Record gain */

#अगर_घोषित DEBUG
	stk1160_ac97_dump_regs(dev);
#पूर्ण_अगर
पूर्ण
