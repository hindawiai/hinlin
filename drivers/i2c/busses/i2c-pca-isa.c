<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  i2c-pca-isa.c driver क्रम PCA9564 on ISA boards
 *    Copyright (C) 2004 Arcom Control Systems
 *    Copyright (C) 2008 Pengutronix
 */

#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/isa.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-pca.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>

#घोषणा DRIVER "i2c-pca-isa"
#घोषणा IO_SIZE 4

अटल अचिन्हित दीर्घ base;
अटल पूर्णांक irq = -1;

/* Data sheet recommends 59kHz क्रम 100kHz operation due to variation
 * in the actual घड़ी rate */
अटल पूर्णांक घड़ी  = 59000;

अटल काष्ठा i2c_adapter pca_isa_ops;
अटल रुको_queue_head_t pca_रुको;

अटल व्योम pca_isa_ग_लिखोbyte(व्योम *pd, पूर्णांक reg, पूर्णांक val)
अणु
#अगर_घोषित DEBUG_IO
	अटल अक्षर *names[] = अणु "T/O", "DAT", "ADR", "CON" पूर्ण;
	prपूर्णांकk(KERN_DEBUG "*** write %s at %#lx <= %#04x\n", names[reg],
	       base+reg, val);
#पूर्ण_अगर
	outb(val, base+reg);
पूर्ण

अटल पूर्णांक pca_isa_पढ़ोbyte(व्योम *pd, पूर्णांक reg)
अणु
	पूर्णांक res = inb(base+reg);
#अगर_घोषित DEBUG_IO
	अणु
		अटल अक्षर *names[] = अणु "STA", "DAT", "ADR", "CON" पूर्ण;
		prपूर्णांकk(KERN_DEBUG "*** read  %s => %#04x\n", names[reg], res);
	पूर्ण
#पूर्ण_अगर
	वापस res;
पूर्ण

अटल पूर्णांक pca_isa_रुकोक्रमcompletion(व्योम *pd)
अणु
	अचिन्हित दीर्घ समयout;
	दीर्घ ret;

	अगर (irq > -1) अणु
		ret = रुको_event_समयout(pca_रुको,
				pca_isa_पढ़ोbyte(pd, I2C_PCA_CON)
				& I2C_PCA_CON_SI, pca_isa_ops.समयout);
	पूर्ण अन्यथा अणु
		/* Do polling */
		समयout = jअगरfies + pca_isa_ops.समयout;
		करो अणु
			ret = समय_beक्रमe(jअगरfies, समयout);
			अगर (pca_isa_पढ़ोbyte(pd, I2C_PCA_CON)
					& I2C_PCA_CON_SI)
				अवरोध;
			udelay(100);
		पूर्ण जबतक (ret);
	पूर्ण

	वापस ret > 0;
पूर्ण

अटल व्योम pca_isa_resetchip(व्योम *pd)
अणु
	/* apparently only an बाह्यal reset will करो it. not a lot can be करोne */
	prपूर्णांकk(KERN_WARNING DRIVER ": Haven't figured out how to do a reset yet\n");
पूर्ण

अटल irqवापस_t pca_handler(पूर्णांक this_irq, व्योम *dev_id) अणु
	wake_up(&pca_रुको);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा i2c_algo_pca_data pca_isa_data = अणु
	/* .data पूर्णांकentionally left शून्य, not needed with ISA */
	.ग_लिखो_byte		= pca_isa_ग_लिखोbyte,
	.पढ़ो_byte		= pca_isa_पढ़ोbyte,
	.रुको_क्रम_completion	= pca_isa_रुकोक्रमcompletion,
	.reset_chip		= pca_isa_resetchip,
पूर्ण;

अटल काष्ठा i2c_adapter pca_isa_ops = अणु
	.owner          = THIS_MODULE,
	.algo_data	= &pca_isa_data,
	.name		= "PCA9564/PCA9665 ISA Adapter",
	.समयout	= HZ,
पूर्ण;

अटल पूर्णांक pca_isa_match(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक match = base != 0;

	अगर (match) अणु
		अगर (irq <= -1)
			dev_warn(dev, "Using polling mode (specify irq)\n");
	पूर्ण अन्यथा
		dev_err(dev, "Please specify I/O base\n");

	वापस match;
पूर्ण

अटल पूर्णांक pca_isa_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	init_रुकोqueue_head(&pca_रुको);

	dev_info(dev, "i/o base %#08lx. irq %d\n", base, irq);

#अगर_घोषित CONFIG_PPC
	अगर (check_legacy_ioport(base)) अणु
		dev_err(dev, "I/O address %#08lx is not available\n", base);
		जाओ out;
	पूर्ण
#पूर्ण_अगर

	अगर (!request_region(base, IO_SIZE, "i2c-pca-isa")) अणु
		dev_err(dev, "I/O address %#08lx is in use\n", base);
		जाओ out;
	पूर्ण

	अगर (irq > -1) अणु
		अगर (request_irq(irq, pca_handler, 0, "i2c-pca-isa", &pca_isa_ops) < 0) अणु
			dev_err(dev, "Request irq%d failed\n", irq);
			जाओ out_region;
		पूर्ण
	पूर्ण

	pca_isa_data.i2c_घड़ी = घड़ी;
	अगर (i2c_pca_add_bus(&pca_isa_ops) < 0) अणु
		dev_err(dev, "Failed to add i2c bus\n");
		जाओ out_irq;
	पूर्ण

	वापस 0;

 out_irq:
	अगर (irq > -1)
		मुक्त_irq(irq, &pca_isa_ops);
 out_region:
	release_region(base, IO_SIZE);
 out:
	वापस -ENODEV;
पूर्ण

अटल व्योम pca_isa_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	i2c_del_adapter(&pca_isa_ops);

	अगर (irq > -1) अणु
		disable_irq(irq);
		मुक्त_irq(irq, &pca_isa_ops);
	पूर्ण
	release_region(base, IO_SIZE);
पूर्ण

अटल काष्ठा isa_driver pca_isa_driver = अणु
	.match		= pca_isa_match,
	.probe		= pca_isa_probe,
	.हटाओ		= pca_isa_हटाओ,
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= DRIVER,
	पूर्ण
पूर्ण;

MODULE_AUTHOR("Ian Campbell <icampbell@arcom.com>");
MODULE_DESCRIPTION("ISA base PCA9564/PCA9665 driver");
MODULE_LICENSE("GPL");

module_param_hw(base, uदीर्घ, ioport, 0);
MODULE_PARM_DESC(base, "I/O base address");
module_param_hw(irq, पूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "IRQ");
module_param(घड़ी, पूर्णांक, 0);
MODULE_PARM_DESC(घड़ी, "Clock rate in hertz.\n\t\t"
		"For PCA9564: 330000,288000,217000,146000,"
		"88000,59000,44000,36000\n"
		"\t\tFor PCA9665:\tStandard: 60300 - 100099\n"
		"\t\t\t\tFast: 100100 - 400099\n"
		"\t\t\t\tFast+: 400100 - 10000099\n"
		"\t\t\t\tTurbo: Up to 1265800");
module_isa_driver(pca_isa_driver, 1);
