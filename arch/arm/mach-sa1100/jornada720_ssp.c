<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 *  arch/arm/mac-sa1100/jornada720_ssp.c
 *
 *  Copyright (C) 2006/2007 Kristoffer Ericson <Kristoffer.Ericson@gmail.com>
 *   Copyright (C) 2006 Filip Zyzniewski <filip.zyzniewski@tefnet.pl>
 *
 *  SSP driver क्रम the HP Jornada 710/720/728
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <mach/jornada720.h>
#समावेश <यंत्र/hardware/ssp.h>

अटल DEFINE_SPINLOCK(jornada_ssp_lock);
अटल अचिन्हित दीर्घ jornada_ssp_flags;

/**
 * jornada_ssp_reverse - reverses input byte
 *
 * we need to reverse all data we receive from the mcu due to its physical location
 * वापसs : 01110111 -> 11101110
 */
अंतरभूत u8 jornada_ssp_reverse(u8 byte)
अणु
	वापस
		((0x80 & byte) >> 7) |
		((0x40 & byte) >> 5) |
		((0x20 & byte) >> 3) |
		((0x10 & byte) >> 1) |
		((0x08 & byte) << 1) |
		((0x04 & byte) << 3) |
		((0x02 & byte) << 5) |
		((0x01 & byte) << 7);
पूर्ण;
EXPORT_SYMBOL(jornada_ssp_reverse);

/**
 * jornada_ssp_byte - रुकोs क्रम पढ़ोy ssp bus and sends byte
 *
 * रुकोs क्रम fअगरo buffer to clear and then transmits, अगर it करोesn't then we will
 * समयout after <समयout> rounds. Needs mcu running beक्रमe its called.
 *
 * वापसs : %mcu output on success
 *	   : %-ETIMEDOUT on समयout
 */
पूर्णांक jornada_ssp_byte(u8 byte)
अणु
	पूर्णांक समयout = 400000;
	u16 ret;

	जबतक ((GPLR & GPIO_GPIO10)) अणु
		अगर (!--समयout) अणु
			prपूर्णांकk(KERN_WARNING "SSP: timeout while waiting for transmit\n");
			वापस -ETIMEDOUT;
		पूर्ण
		cpu_relax();
	पूर्ण

	ret = jornada_ssp_reverse(byte) << 8;

	ssp_ग_लिखो_word(ret);
	ssp_पढ़ो_word(&ret);

	वापस jornada_ssp_reverse(ret);
पूर्ण;
EXPORT_SYMBOL(jornada_ssp_byte);

/**
 * jornada_ssp_inout - decide अगर input is command or trading byte
 *
 * वापसs : (jornada_ssp_byte(byte)) on success
 *         : %-ETIMEDOUT on समयout failure
 */
पूर्णांक jornada_ssp_inout(u8 byte)
अणु
	पूर्णांक ret, i;

	/* true means command byte */
	अगर (byte != TXDUMMY) अणु
		ret = jornada_ssp_byte(byte);
		/* Proper वापस to commands is TxDummy */
		अगर (ret != TXDUMMY) अणु
			क्रम (i = 0; i < 256; i++)/* flushing bus */
				अगर (jornada_ssp_byte(TXDUMMY) == -1)
					अवरोध;
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा /* Exchange TxDummy क्रम data */
		ret = jornada_ssp_byte(TXDUMMY);

	वापस ret;
पूर्ण;
EXPORT_SYMBOL(jornada_ssp_inout);

/**
 * jornada_ssp_start - enable mcu
 *
 */
व्योम jornada_ssp_start(व्योम)
अणु
	spin_lock_irqsave(&jornada_ssp_lock, jornada_ssp_flags);
	GPCR = GPIO_GPIO25;
	udelay(50);
	वापस;
पूर्ण;
EXPORT_SYMBOL(jornada_ssp_start);

/**
 * jornada_ssp_end - disable mcu and turn off lock
 *
 */
व्योम jornada_ssp_end(व्योम)
अणु
	GPSR = GPIO_GPIO25;
	spin_unlock_irqrestore(&jornada_ssp_lock, jornada_ssp_flags);
	वापस;
पूर्ण;
EXPORT_SYMBOL(jornada_ssp_end);

अटल पूर्णांक jornada_ssp_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	GPSR = GPIO_GPIO25;

	ret = ssp_init();

	/* worked fine, lets not bother with anything अन्यथा */
	अगर (!ret) अणु
		prपूर्णांकk(KERN_INFO "SSP: device initialized with irq\n");
		वापस ret;
	पूर्ण

	prपूर्णांकk(KERN_WARNING "SSP: initialization failed, trying non-irq solution \n");

	/* init of Serial 4 port */
	Ser4MCCR0 = 0;
	Ser4SSCR0 = 0x0387;
	Ser4SSCR1 = 0x18;

	/* clear out any left over data */
	ssp_flush();

	/* enable MCU */
	jornada_ssp_start();

	/* see अगर वापस value makes sense */
	ret = jornada_ssp_inout(GETBRIGHTNESS);

	/* seems like it worked, just feed it with TxDummy to get rid of data */
	अगर (ret == TXDUMMY)
		jornada_ssp_inout(TXDUMMY);

	jornada_ssp_end();

	/* failed, lets just समाप्त everything */
	अगर (ret == -ETIMEDOUT) अणु
		prपूर्णांकk(KERN_WARNING "SSP: attempts failed, bailing\n");
		ssp_निकास();
		वापस -ENODEV;
	पूर्ण

	/* all fine */
	prपूर्णांकk(KERN_INFO "SSP: device initialized\n");
	वापस 0;
पूर्ण;

अटल पूर्णांक jornada_ssp_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	/* Note that this करोesn't actually हटाओ the driver, since theres nothing to हटाओ
	 * It just makes sure everything is turned off */
	GPSR = GPIO_GPIO25;
	ssp_निकास();
	वापस 0;
पूर्ण;

काष्ठा platक्रमm_driver jornadassp_driver = अणु
	.probe	= jornada_ssp_probe,
	.हटाओ	= jornada_ssp_हटाओ,
	.driver	= अणु
		.name	= "jornada_ssp",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init jornada_ssp_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&jornadassp_driver);
पूर्ण

module_init(jornada_ssp_init);
