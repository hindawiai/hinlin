<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PIKA Warp(पंचांग) board specअगरic routines
 *
 * Copyright (c) 2008-2009 PIKA Technologies
 *   Sean MacLennan <smaclennan@pikatech.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/uic.h>
#समावेश <यंत्र/ppc4xx.h>
#समावेश <यंत्र/dma.h>


अटल स्थिर काष्ठा of_device_id warp_of_bus[] __initस्थिर = अणु
	अणु .compatible = "ibm,plb4", पूर्ण,
	अणु .compatible = "ibm,opb", पूर्ण,
	अणु .compatible = "ibm,ebc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init warp_device_probe(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, warp_of_bus, शून्य);
	वापस 0;
पूर्ण
machine_device_initcall(warp, warp_device_probe);

अटल पूर्णांक __init warp_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("pika,warp"))
		वापस 0;

	वापस 1;
पूर्ण

define_machine(warp) अणु
	.name		= "Warp",
	.probe 		= warp_probe,
	.progress 	= udbg_progress,
	.init_IRQ 	= uic_init_tree,
	.get_irq 	= uic_get_irq,
	.restart	= ppc4xx_reset_प्रणाली,
	.calibrate_decr = generic_calibrate_decr,
पूर्ण;


अटल पूर्णांक __init warp_post_info(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *fpga;
	u32 post1, post2;

	/* Sighhhh... POST inक्रमmation is in the sd area. */
	np = of_find_compatible_node(शून्य, शून्य, "pika,fpga-sd");
	अगर (np == शून्य)
		वापस -ENOENT;

	fpga = of_iomap(np, 0);
	of_node_put(np);
	अगर (fpga == शून्य)
		वापस -ENOENT;

	post1 = in_be32(fpga + 0x40);
	post2 = in_be32(fpga + 0x44);

	iounmap(fpga);

	अगर (post1 || post2)
		prपूर्णांकk(KERN_INFO "Warp POST %08x %08x\n", post1, post2);
	अन्यथा
		prपूर्णांकk(KERN_INFO "Warp POST OK\n");

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_SENSORS_AD7414

अटल LIST_HEAD(dपंचांग_shutकरोwn_list);
अटल व्योम __iomem *dपंचांग_fpga;
अटल अचिन्हित green_led, red_led;


काष्ठा dपंचांग_shutकरोwn अणु
	काष्ठा list_head list;
	व्योम (*func)(व्योम *arg);
	व्योम *arg;
पूर्ण;


पूर्णांक pika_dपंचांग_रेजिस्टर_shutकरोwn(व्योम (*func)(व्योम *arg), व्योम *arg)
अणु
	काष्ठा dपंचांग_shutकरोwn *shutकरोwn;

	shutकरोwn = kदो_स्मृति(माप(काष्ठा dपंचांग_shutकरोwn), GFP_KERNEL);
	अगर (shutकरोwn == शून्य)
		वापस -ENOMEM;

	shutकरोwn->func = func;
	shutकरोwn->arg = arg;

	list_add(&shutकरोwn->list, &dपंचांग_shutकरोwn_list);

	वापस 0;
पूर्ण

पूर्णांक pika_dपंचांग_unरेजिस्टर_shutकरोwn(व्योम (*func)(व्योम *arg), व्योम *arg)
अणु
	काष्ठा dपंचांग_shutकरोwn *shutकरोwn;

	list_क्रम_each_entry(shutकरोwn, &dपंचांग_shutकरोwn_list, list)
		अगर (shutकरोwn->func == func && shutकरोwn->arg == arg) अणु
			list_del(&shutकरोwn->list);
			kमुक्त(shutकरोwn);
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t temp_isr(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा dपंचांग_shutकरोwn *shutकरोwn;
	पूर्णांक value = 1;

	local_irq_disable();

	gpio_set_value(green_led, 0);

	/* Run through the shutकरोwn list. */
	list_क्रम_each_entry(shutकरोwn, &dपंचांग_shutकरोwn_list, list)
		shutकरोwn->func(shutकरोwn->arg);

	prपूर्णांकk(KERN_EMERG "\n\nCritical Temperature Shutdown\n\n");

	जबतक (1) अणु
		अगर (dपंचांग_fpga) अणु
			अचिन्हित reset = in_be32(dपंचांग_fpga + 0x14);
			out_be32(dपंचांग_fpga + 0x14, reset);
		पूर्ण

		gpio_set_value(red_led, value);
		value ^= 1;
		mdelay(500);
	पूर्ण

	/* Not reached */
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pika_setup_leds(व्योम)
अणु
	काष्ठा device_node *np, *child;

	np = of_find_compatible_node(शून्य, शून्य, "gpio-leds");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR __खाता__ ": Unable to find leds\n");
		वापस -ENOENT;
	पूर्ण

	क्रम_each_child_of_node(np, child)
		अगर (of_node_name_eq(child, "green"))
			green_led = of_get_gpio(child, 0);
		अन्यथा अगर (of_node_name_eq(child, "red"))
			red_led = of_get_gpio(child, 0);

	of_node_put(np);

	वापस 0;
पूर्ण

अटल व्योम pika_setup_critical_temp(काष्ठा device_node *np,
				     काष्ठा i2c_client *client)
अणु
	पूर्णांक irq, rc;

	/* Do this beक्रमe enabling critical temp पूर्णांकerrupt since we
	 * may immediately पूर्णांकerrupt.
	 */
	pika_setup_leds();

	/* These रेजिस्टरs are in 1 degree increments. */
	i2c_smbus_ग_लिखो_byte_data(client, 2, 65); /* Thigh */
	i2c_smbus_ग_लिखो_byte_data(client, 3,  0); /* Tlow */

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		prपूर्णांकk(KERN_ERR __खाता__ ": Unable to get ad7414 irq\n");
		वापस;
	पूर्ण

	rc = request_irq(irq, temp_isr, 0, "ad7414", शून्य);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR __खाता__
		       ": Unable to request ad7414 irq %d = %d\n", irq, rc);
		वापस;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pika_dपंचांग_check_fan(व्योम __iomem *fpga)
अणु
	अटल पूर्णांक fan_state;
	u32 fan = in_be32(fpga + 0x34) & (1 << 14);

	अगर (fan_state != fan) अणु
		fan_state = fan;
		अगर (fan)
			prपूर्णांकk(KERN_WARNING "Fan rotation error detected."
				   " Please check hardware.\n");
	पूर्ण
पूर्ण

अटल पूर्णांक pika_dपंचांग_thपढ़ो(व्योम __iomem *fpga)
अणु
	काष्ठा device_node *np;
	काष्ठा i2c_client *client;

	np = of_find_compatible_node(शून्य, शून्य, "adi,ad7414");
	अगर (np == शून्य)
		वापस -ENOENT;

	client = of_find_i2c_device_by_node(np);
	अगर (client == शून्य) अणु
		of_node_put(np);
		वापस -ENOENT;
	पूर्ण

	pika_setup_critical_temp(np, client);

	of_node_put(np);

	prपूर्णांकk(KERN_INFO "Warp DTM thread running.\n");

	जबतक (!kthपढ़ो_should_stop()) अणु
		पूर्णांक val;

		val = i2c_smbus_पढ़ो_word_data(client, 0);
		अगर (val < 0)
			dev_dbg(&client->dev, "DTM read temp failed.\n");
		अन्यथा अणु
			s16 temp = swab16(val);
			out_be32(fpga + 0x20, temp);
		पूर्ण

		pika_dपंचांग_check_fan(fpga);

		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(HZ);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init pika_dपंचांग_start(व्योम)
अणु
	काष्ठा task_काष्ठा *dपंचांग_thपढ़ो;
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "pika,fpga");
	अगर (np == शून्य)
		वापस -ENOENT;

	dपंचांग_fpga = of_iomap(np, 0);
	of_node_put(np);
	अगर (dपंचांग_fpga == शून्य)
		वापस -ENOENT;

	/* Must get post info beक्रमe thपढ़ो starts. */
	warp_post_info();

	dपंचांग_thपढ़ो = kthपढ़ो_run(pika_dपंचांग_thपढ़ो, dपंचांग_fpga, "pika-dtm");
	अगर (IS_ERR(dपंचांग_thपढ़ो)) अणु
		iounmap(dपंचांग_fpga);
		वापस PTR_ERR(dपंचांग_thपढ़ो);
	पूर्ण

	वापस 0;
पूर्ण
machine_late_initcall(warp, pika_dपंचांग_start);

#अन्यथा /* !CONFIG_SENSORS_AD7414 */

पूर्णांक pika_dपंचांग_रेजिस्टर_shutकरोwn(व्योम (*func)(व्योम *arg), व्योम *arg)
अणु
	वापस 0;
पूर्ण

पूर्णांक pika_dपंचांग_unरेजिस्टर_shutकरोwn(व्योम (*func)(व्योम *arg), व्योम *arg)
अणु
	वापस 0;
पूर्ण

machine_late_initcall(warp, warp_post_info);

#पूर्ण_अगर

EXPORT_SYMBOL(pika_dपंचांग_रेजिस्टर_shutकरोwn);
EXPORT_SYMBOL(pika_dपंचांग_unरेजिस्टर_shutकरोwn);
