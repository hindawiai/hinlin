<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the on-board अक्षरacter LCD found on some ARM reference boards
 * This is basically an Hitachi HD44780 LCD with a custom IP block to drive it
 * https://en.wikipedia.org/wiki/HD44780_Character_LCD
 * Currently it will just display the text "ARM Linux" and the linux version
 *
 * Author: Linus Walleij <triad@df.lth.se>
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <generated/utsrelease.h>

#घोषणा DRIVERNAME "arm-charlcd"
#घोषणा CHARLCD_TIMEOUT (msecs_to_jअगरfies(1000))

/* Offsets to रेजिस्टरs */
#घोषणा CHAR_COM	0x00U
#घोषणा CHAR_DAT	0x04U
#घोषणा CHAR_RD		0x08U
#घोषणा CHAR_RAW	0x0CU
#घोषणा CHAR_MASK	0x10U
#घोषणा CHAR_STAT	0x14U

#घोषणा CHAR_RAW_CLEAR	0x00000000U
#घोषणा CHAR_RAW_VALID	0x00000100U

/* Hitachi HD44780 display commands */
#घोषणा HD_CLEAR			0x01U
#घोषणा HD_HOME				0x02U
#घोषणा HD_ENTRYMODE			0x04U
#घोषणा HD_ENTRYMODE_INCREMENT		0x02U
#घोषणा HD_ENTRYMODE_SHIFT		0x01U
#घोषणा HD_DISPCTRL			0x08U
#घोषणा HD_DISPCTRL_ON			0x04U
#घोषणा HD_DISPCTRL_CURSOR_ON		0x02U
#घोषणा HD_DISPCTRL_CURSOR_BLINK	0x01U
#घोषणा HD_CRSR_SHIFT			0x10U
#घोषणा HD_CRSR_SHIFT_DISPLAY		0x08U
#घोषणा HD_CRSR_SHIFT_DISPLAY_RIGHT	0x04U
#घोषणा HD_FUNCSET			0x20U
#घोषणा HD_FUNCSET_8BIT			0x10U
#घोषणा HD_FUNCSET_2_LINES		0x08U
#घोषणा HD_FUNCSET_FONT_5X10		0x04U
#घोषणा HD_SET_CGRAM			0x40U
#घोषणा HD_SET_DDRAM			0x80U
#घोषणा HD_BUSY_FLAG			0x80U

/**
 * काष्ठा अक्षरlcd - Private data काष्ठाure
 * @dev: a poपूर्णांकer back to containing device
 * @phybase: the offset to the controller in physical memory
 * @physize: the size of the physical page
 * @virtbase: the offset to the controller in भव memory
 * @irq: reserved पूर्णांकerrupt number
 * @complete: completion काष्ठाure क्रम the last LCD command
 * @init_work: delayed work काष्ठाure to initialize the display on boot
 */
काष्ठा अक्षरlcd अणु
	काष्ठा device *dev;
	u32 phybase;
	u32 physize;
	व्योम __iomem *virtbase;
	पूर्णांक irq;
	काष्ठा completion complete;
	काष्ठा delayed_work init_work;
पूर्ण;

अटल irqवापस_t अक्षरlcd_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा अक्षरlcd *lcd = data;
	u8 status;

	status = पढ़ोl(lcd->virtbase + CHAR_STAT) & 0x01;
	/* Clear IRQ */
	ग_लिखोl(CHAR_RAW_CLEAR, lcd->virtbase + CHAR_RAW);
	अगर (status)
		complete(&lcd->complete);
	अन्यथा
		dev_info(lcd->dev, "Spurious IRQ (%02x)\n", status);
	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम अक्षरlcd_रुको_complete_irq(काष्ठा अक्षरlcd *lcd)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&lcd->complete,
							CHARLCD_TIMEOUT);
	/* Disable IRQ after completion */
	ग_लिखोl(0x00, lcd->virtbase + CHAR_MASK);

	अगर (ret < 0) अणु
		dev_err(lcd->dev,
			"wait_for_completion_interruptible_timeout() "
			"returned %d waiting for ready\n", ret);
		वापस;
	पूर्ण

	अगर (ret == 0) अणु
		dev_err(lcd->dev, "charlcd controller timed out "
			"waiting for ready\n");
		वापस;
	पूर्ण
पूर्ण

अटल u8 अक्षरlcd_4bit_पढ़ो_अक्षर(काष्ठा अक्षरlcd *lcd)
अणु
	u8 data;
	u32 val;
	पूर्णांक i;

	/* If we can, use an IRQ to रुको क्रम the data, अन्यथा poll */
	अगर (lcd->irq >= 0)
		अक्षरlcd_रुको_complete_irq(lcd);
	अन्यथा अणु
		i = 0;
		val = 0;
		जबतक (!(val & CHAR_RAW_VALID) && i < 10) अणु
			udelay(100);
			val = पढ़ोl(lcd->virtbase + CHAR_RAW);
			i++;
		पूर्ण

		ग_लिखोl(CHAR_RAW_CLEAR, lcd->virtbase + CHAR_RAW);
	पूर्ण
	msleep(1);

	/* Read the 4 high bits of the data */
	data = पढ़ोl(lcd->virtbase + CHAR_RD) & 0xf0;

	/*
	 * The second पढ़ो क्रम the low bits करोes not trigger an IRQ
	 * so in this हाल we have to poll क्रम the 4 lower bits
	 */
	i = 0;
	val = 0;
	जबतक (!(val & CHAR_RAW_VALID) && i < 10) अणु
		udelay(100);
		val = पढ़ोl(lcd->virtbase + CHAR_RAW);
		i++;
	पूर्ण
	ग_लिखोl(CHAR_RAW_CLEAR, lcd->virtbase + CHAR_RAW);
	msleep(1);

	/* Read the 4 low bits of the data */
	data |= (पढ़ोl(lcd->virtbase + CHAR_RD) >> 4) & 0x0f;

	वापस data;
पूर्ण

अटल bool अक्षरlcd_4bit_पढ़ो_bf(काष्ठा अक्षरlcd *lcd)
अणु
	अगर (lcd->irq >= 0) अणु
		/*
		 * If we'll use IRQs to रुको क्रम the busyflag, clear any
		 * pending flag and enable IRQ
		 */
		ग_लिखोl(CHAR_RAW_CLEAR, lcd->virtbase + CHAR_RAW);
		init_completion(&lcd->complete);
		ग_लिखोl(0x01, lcd->virtbase + CHAR_MASK);
	पूर्ण
	पढ़ोl(lcd->virtbase + CHAR_COM);
	वापस अक्षरlcd_4bit_पढ़ो_अक्षर(lcd) & HD_BUSY_FLAG ? true : false;
पूर्ण

अटल व्योम अक्षरlcd_4bit_रुको_busy(काष्ठा अक्षरlcd *lcd)
अणु
	पूर्णांक retries = 50;

	udelay(100);
	जबतक (अक्षरlcd_4bit_पढ़ो_bf(lcd) && retries)
		retries--;
	अगर (!retries)
		dev_err(lcd->dev, "timeout waiting for busyflag\n");
पूर्ण

अटल व्योम अक्षरlcd_4bit_command(काष्ठा अक्षरlcd *lcd, u8 cmd)
अणु
	u32 cmdlo = (cmd << 4) & 0xf0;
	u32 cmdhi = (cmd & 0xf0);

	ग_लिखोl(cmdhi, lcd->virtbase + CHAR_COM);
	udelay(10);
	ग_लिखोl(cmdlo, lcd->virtbase + CHAR_COM);
	अक्षरlcd_4bit_रुको_busy(lcd);
पूर्ण

अटल व्योम अक्षरlcd_4bit_अक्षर(काष्ठा अक्षरlcd *lcd, u8 ch)
अणु
	u32 chlo = (ch << 4) & 0xf0;
	u32 chhi = (ch & 0xf0);

	ग_लिखोl(chhi, lcd->virtbase + CHAR_DAT);
	udelay(10);
	ग_लिखोl(chlo, lcd->virtbase + CHAR_DAT);
	अक्षरlcd_4bit_रुको_busy(lcd);
पूर्ण

अटल व्योम अक्षरlcd_4bit_prपूर्णांक(काष्ठा अक्षरlcd *lcd, पूर्णांक line, स्थिर अक्षर *str)
अणु
	u8 offset;
	पूर्णांक i;

	/*
	 * We support line 0, 1
	 * Line 1 runs from 0x00..0x27
	 * Line 2 runs from 0x28..0x4f
	 */
	अगर (line == 0)
		offset = 0;
	अन्यथा अगर (line == 1)
		offset = 0x28;
	अन्यथा
		वापस;

	/* Set offset */
	अक्षरlcd_4bit_command(lcd, HD_SET_DDRAM | offset);

	/* Send string */
	क्रम (i = 0; i < म_माप(str) && i < 0x28; i++)
		अक्षरlcd_4bit_अक्षर(lcd, str[i]);
पूर्ण

अटल व्योम अक्षरlcd_4bit_init(काष्ठा अक्षरlcd *lcd)
अणु
	/* These commands cannot be checked with the busy flag */
	ग_लिखोl(HD_FUNCSET | HD_FUNCSET_8BIT, lcd->virtbase + CHAR_COM);
	msleep(5);
	ग_लिखोl(HD_FUNCSET | HD_FUNCSET_8BIT, lcd->virtbase + CHAR_COM);
	udelay(100);
	ग_लिखोl(HD_FUNCSET | HD_FUNCSET_8BIT, lcd->virtbase + CHAR_COM);
	udelay(100);
	/* Go to 4bit mode */
	ग_लिखोl(HD_FUNCSET, lcd->virtbase + CHAR_COM);
	udelay(100);
	/*
	 * 4bit mode, 2 lines, 5x8 font, after this the number of lines
	 * and the font cannot be changed until the next initialization sequence
	 */
	अक्षरlcd_4bit_command(lcd, HD_FUNCSET | HD_FUNCSET_2_LINES);
	अक्षरlcd_4bit_command(lcd, HD_DISPCTRL | HD_DISPCTRL_ON);
	अक्षरlcd_4bit_command(lcd, HD_ENTRYMODE | HD_ENTRYMODE_INCREMENT);
	अक्षरlcd_4bit_command(lcd, HD_CLEAR);
	अक्षरlcd_4bit_command(lcd, HD_HOME);
	/* Put something useful in the display */
	अक्षरlcd_4bit_prपूर्णांक(lcd, 0, "ARM Linux");
	अक्षरlcd_4bit_prपूर्णांक(lcd, 1, UTS_RELEASE);
पूर्ण

अटल व्योम अक्षरlcd_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा अक्षरlcd *lcd =
		container_of(work, काष्ठा अक्षरlcd, init_work.work);

	अक्षरlcd_4bit_init(lcd);
पूर्ण

अटल पूर्णांक __init अक्षरlcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा अक्षरlcd *lcd;
	काष्ठा resource *res;

	lcd = kzalloc(माप(काष्ठा अक्षरlcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	lcd->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENOENT;
		जाओ out_no_resource;
	पूर्ण
	lcd->phybase = res->start;
	lcd->physize = resource_size(res);

	अगर (request_mem_region(lcd->phybase, lcd->physize,
			       DRIVERNAME) == शून्य) अणु
		ret = -EBUSY;
		जाओ out_no_memregion;
	पूर्ण

	lcd->virtbase = ioremap(lcd->phybase, lcd->physize);
	अगर (!lcd->virtbase) अणु
		ret = -ENOMEM;
		जाओ out_no_memregion;
	पूर्ण

	lcd->irq = platक्रमm_get_irq(pdev, 0);
	/* If no IRQ is supplied, we'll survive without it */
	अगर (lcd->irq >= 0) अणु
		अगर (request_irq(lcd->irq, अक्षरlcd_पूर्णांकerrupt, 0,
				DRIVERNAME, lcd)) अणु
			ret = -EIO;
			जाओ out_no_irq;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, lcd);

	/*
	 * Initialize the display in a delayed work, because
	 * it is VERY slow and would slow करोwn the boot of the प्रणाली.
	 */
	INIT_DELAYED_WORK(&lcd->init_work, अक्षरlcd_init_work);
	schedule_delayed_work(&lcd->init_work, 0);

	dev_info(&pdev->dev, "initialized ARM character LCD at %08x\n",
		lcd->phybase);

	वापस 0;

out_no_irq:
	iounmap(lcd->virtbase);
out_no_memregion:
	release_mem_region(lcd->phybase, SZ_4K);
out_no_resource:
	kमुक्त(lcd);
	वापस ret;
पूर्ण

अटल पूर्णांक अक्षरlcd_suspend(काष्ठा device *dev)
अणु
	काष्ठा अक्षरlcd *lcd = dev_get_drvdata(dev);

	/* Power the display off */
	अक्षरlcd_4bit_command(lcd, HD_DISPCTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक अक्षरlcd_resume(काष्ठा device *dev)
अणु
	काष्ठा अक्षरlcd *lcd = dev_get_drvdata(dev);

	/* Turn the display back on */
	अक्षरlcd_4bit_command(lcd, HD_DISPCTRL | HD_DISPCTRL_ON);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops अक्षरlcd_pm_ops = अणु
	.suspend = अक्षरlcd_suspend,
	.resume = अक्षरlcd_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id अक्षरlcd_match[] = अणु
	अणु .compatible = "arm,versatile-lcd", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver अक्षरlcd_driver = अणु
	.driver = अणु
		.name = DRIVERNAME,
		.pm = &अक्षरlcd_pm_ops,
		.suppress_bind_attrs = true,
		.of_match_table = of_match_ptr(अक्षरlcd_match),
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(अक्षरlcd_driver, अक्षरlcd_probe);
