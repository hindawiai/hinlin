<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/sysdev/qe_lib/qe_io.c
 *
 * QE Parallel I/O ports configuration routines
 *
 * Copyright 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Li Yang <LeoLi@मुक्तscale.com>
 * Based on code from Shlomi Gridish <gridish@मुक्तscale.com>
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/पन.स>
#समावेश <soc/fsl/qe/qe.h>

#अघोषित DEBUG

अटल काष्ठा qe_pio_regs __iomem *par_io;
अटल पूर्णांक num_par_io_ports = 0;

पूर्णांक par_io_init(काष्ठा device_node *np)
अणु
	काष्ठा resource res;
	पूर्णांक ret;
	u32 num_ports;

	/* Map Parallel I/O ports रेजिस्टरs */
	ret = of_address_to_resource(np, 0, &res);
	अगर (ret)
		वापस ret;
	par_io = ioremap(res.start, resource_size(&res));

	अगर (!of_property_पढ़ो_u32(np, "num-ports", &num_ports))
		num_par_io_ports = num_ports;

	वापस 0;
पूर्ण

व्योम __par_io_config_pin(काष्ठा qe_pio_regs __iomem *par_io, u8 pin, पूर्णांक dir,
			 पूर्णांक खोलो_drain, पूर्णांक assignment, पूर्णांक has_irq)
अणु
	u32 pin_mask1bit;
	u32 pin_mask2bits;
	u32 new_mask2bits;
	u32 पंचांगp_val;

	/* calculate pin location क्रम single and 2 bits inक्रमmation */
	pin_mask1bit = (u32) (1 << (QE_PIO_PINS - (pin + 1)));

	/* Set खोलो drain, अगर required */
	पंचांगp_val = ioपढ़ो32be(&par_io->cpodr);
	अगर (खोलो_drain)
		ioग_लिखो32be(pin_mask1bit | पंचांगp_val, &par_io->cpodr);
	अन्यथा
		ioग_लिखो32be(~pin_mask1bit & पंचांगp_val, &par_io->cpodr);

	/* define direction */
	पंचांगp_val = (pin > (QE_PIO_PINS / 2) - 1) ?
		ioपढ़ो32be(&par_io->cpdir2) :
		ioपढ़ो32be(&par_io->cpdir1);

	/* get all bits mask क्रम 2 bit per port */
	pin_mask2bits = (u32) (0x3 << (QE_PIO_PINS -
				(pin % (QE_PIO_PINS / 2) + 1) * 2));

	/* Get the final mask we need क्रम the right definition */
	new_mask2bits = (u32) (dir << (QE_PIO_PINS -
				(pin % (QE_PIO_PINS / 2) + 1) * 2));

	/* clear and set 2 bits mask */
	अगर (pin > (QE_PIO_PINS / 2) - 1) अणु
		ioग_लिखो32be(~pin_mask2bits & पंचांगp_val, &par_io->cpdir2);
		पंचांगp_val &= ~pin_mask2bits;
		ioग_लिखो32be(new_mask2bits | पंचांगp_val, &par_io->cpdir2);
	पूर्ण अन्यथा अणु
		ioग_लिखो32be(~pin_mask2bits & पंचांगp_val, &par_io->cpdir1);
		पंचांगp_val &= ~pin_mask2bits;
		ioग_लिखो32be(new_mask2bits | पंचांगp_val, &par_io->cpdir1);
	पूर्ण
	/* define pin assignment */
	पंचांगp_val = (pin > (QE_PIO_PINS / 2) - 1) ?
		ioपढ़ो32be(&par_io->cppar2) :
		ioपढ़ो32be(&par_io->cppar1);

	new_mask2bits = (u32) (assignment << (QE_PIO_PINS -
			(pin % (QE_PIO_PINS / 2) + 1) * 2));
	/* clear and set 2 bits mask */
	अगर (pin > (QE_PIO_PINS / 2) - 1) अणु
		ioग_लिखो32be(~pin_mask2bits & पंचांगp_val, &par_io->cppar2);
		पंचांगp_val &= ~pin_mask2bits;
		ioग_लिखो32be(new_mask2bits | पंचांगp_val, &par_io->cppar2);
	पूर्ण अन्यथा अणु
		ioग_लिखो32be(~pin_mask2bits & पंचांगp_val, &par_io->cppar1);
		पंचांगp_val &= ~pin_mask2bits;
		ioग_लिखो32be(new_mask2bits | पंचांगp_val, &par_io->cppar1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__par_io_config_pin);

पूर्णांक par_io_config_pin(u8 port, u8 pin, पूर्णांक dir, पूर्णांक खोलो_drain,
		      पूर्णांक assignment, पूर्णांक has_irq)
अणु
	अगर (!par_io || port >= num_par_io_ports)
		वापस -EINVAL;

	__par_io_config_pin(&par_io[port], pin, dir, खोलो_drain, assignment,
			    has_irq);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(par_io_config_pin);

पूर्णांक par_io_data_set(u8 port, u8 pin, u8 val)
अणु
	u32 pin_mask, पंचांगp_val;

	अगर (port >= num_par_io_ports)
		वापस -EINVAL;
	अगर (pin >= QE_PIO_PINS)
		वापस -EINVAL;
	/* calculate pin location */
	pin_mask = (u32) (1 << (QE_PIO_PINS - 1 - pin));

	पंचांगp_val = ioपढ़ो32be(&par_io[port].cpdata);

	अगर (val == 0)		/* clear */
		ioग_लिखो32be(~pin_mask & पंचांगp_val, &par_io[port].cpdata);
	अन्यथा			/* set */
		ioग_लिखो32be(pin_mask | पंचांगp_val, &par_io[port].cpdata);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(par_io_data_set);

पूर्णांक par_io_of_config(काष्ठा device_node *np)
अणु
	काष्ठा device_node *pio;
	पूर्णांक pio_map_len;
	स्थिर __be32 *pio_map;

	अगर (par_io == शून्य) अणु
		prपूर्णांकk(KERN_ERR "par_io not initialized\n");
		वापस -1;
	पूर्ण

	pio = of_parse_phandle(np, "pio-handle", 0);
	अगर (pio == शून्य) अणु
		prपूर्णांकk(KERN_ERR "pio-handle not available\n");
		वापस -1;
	पूर्ण

	pio_map = of_get_property(pio, "pio-map", &pio_map_len);
	अगर (pio_map == शून्य) अणु
		prपूर्णांकk(KERN_ERR "pio-map is not set!\n");
		वापस -1;
	पूर्ण
	pio_map_len /= माप(अचिन्हित पूर्णांक);
	अगर ((pio_map_len % 6) != 0) अणु
		prपूर्णांकk(KERN_ERR "pio-map format wrong!\n");
		वापस -1;
	पूर्ण

	जबतक (pio_map_len > 0) अणु
		u8 port        = be32_to_cpu(pio_map[0]);
		u8 pin         = be32_to_cpu(pio_map[1]);
		पूर्णांक dir        = be32_to_cpu(pio_map[2]);
		पूर्णांक खोलो_drain = be32_to_cpu(pio_map[3]);
		पूर्णांक assignment = be32_to_cpu(pio_map[4]);
		पूर्णांक has_irq    = be32_to_cpu(pio_map[5]);

		par_io_config_pin(port, pin, dir, खोलो_drain,
				  assignment, has_irq);
		pio_map += 6;
		pio_map_len -= 6;
	पूर्ण
	of_node_put(pio);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(par_io_of_config);
