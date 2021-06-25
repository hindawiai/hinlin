<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200, G400 and G450.
 *
 * (c) 1998-2002 Petr Vandrovec <vandrove@vc.cvut.cz>
 *
 * Version: 1.64 2002/06/10
 *
 * See matroxfb_base.c क्रम contributors.
 *
 */

#समावेश "matroxfb_base.h"
#समावेश "matroxfb_maven.h"
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c-algo-bit.h>

/* MGA-TVO I2C क्रम G200, G400 */
#घोषणा MAT_CLK		0x20
#घोषणा MAT_DATA	0x10
/* primary head DDC क्रम Mystique(?), G100, G200, G400 */
#घोषणा DDC1_CLK	0x08
#घोषणा DDC1_DATA	0x02
/* primary head DDC क्रम Millennium, Millennium II */
#घोषणा DDC1B_CLK	0x10
#घोषणा DDC1B_DATA	0x04
/* secondary head DDC क्रम G400 */
#घोषणा DDC2_CLK	0x04
#घोषणा DDC2_DATA	0x01

/******************************************************/

काष्ठा matroxfb_dh_maven_info अणु
	काष्ठा i2c_bit_adapter	maven;
	काष्ठा i2c_bit_adapter	ddc1;
	काष्ठा i2c_bit_adapter	ddc2;
पूर्ण;

अटल पूर्णांक matroxfb_पढ़ो_gpio(काष्ठा matrox_fb_info* minfo) अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक v;

	matroxfb_DAC_lock_irqsave(flags);
	v = matroxfb_DAC_in(minfo, DAC_XGENIODATA);
	matroxfb_DAC_unlock_irqrestore(flags);
	वापस v;
पूर्ण

अटल व्योम matroxfb_set_gpio(काष्ठा matrox_fb_info* minfo, पूर्णांक mask, पूर्णांक val) अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक v;

	matroxfb_DAC_lock_irqsave(flags);
	v = (matroxfb_DAC_in(minfo, DAC_XGENIOCTRL) & mask) | val;
	matroxfb_DAC_out(minfo, DAC_XGENIOCTRL, v);
	/* We must reset GENIODATA very often... XFree plays with this रेजिस्टर */
	matroxfb_DAC_out(minfo, DAC_XGENIODATA, 0x00);
	matroxfb_DAC_unlock_irqrestore(flags);
पूर्ण

/* software I2C functions */
अटल अंतरभूत व्योम matroxfb_i2c_set(काष्ठा matrox_fb_info* minfo, पूर्णांक mask, पूर्णांक state) अणु
	अगर (state)
		state = 0;
	अन्यथा
		state = mask;
	matroxfb_set_gpio(minfo, ~mask, state);
पूर्ण

अटल व्योम matroxfb_gpio_setsda(व्योम* data, पूर्णांक state) अणु
	काष्ठा i2c_bit_adapter* b = data;
	matroxfb_i2c_set(b->minfo, b->mask.data, state);
पूर्ण

अटल व्योम matroxfb_gpio_setscl(व्योम* data, पूर्णांक state) अणु
	काष्ठा i2c_bit_adapter* b = data;
	matroxfb_i2c_set(b->minfo, b->mask.घड़ी, state);
पूर्ण

अटल पूर्णांक matroxfb_gpio_माला_लोda(व्योम* data) अणु
	काष्ठा i2c_bit_adapter* b = data;
	वापस (matroxfb_पढ़ो_gpio(b->minfo) & b->mask.data) ? 1 : 0;
पूर्ण

अटल पूर्णांक matroxfb_gpio_माला_लोcl(व्योम* data) अणु
	काष्ठा i2c_bit_adapter* b = data;
	वापस (matroxfb_पढ़ो_gpio(b->minfo) & b->mask.घड़ी) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा i2c_algo_bit_data matrox_i2c_algo_ढाँचा =
अणु
	.setsda		= matroxfb_gpio_setsda,
	.setscl		= matroxfb_gpio_setscl,
	.माला_लोda		= matroxfb_gpio_माला_लोda,
	.माला_लोcl		= matroxfb_gpio_माला_लोcl,
	.udelay		= 10,
	.समयout	= 100,
पूर्ण;

अटल पूर्णांक i2c_bus_reg(काष्ठा i2c_bit_adapter* b, काष्ठा matrox_fb_info* minfo, 
		अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक घड़ी, स्थिर अक्षर *name,
		पूर्णांक class)
अणु
	पूर्णांक err;

	b->minfo = minfo;
	b->mask.data = data;
	b->mask.घड़ी = घड़ी;
	b->adapter.owner = THIS_MODULE;
	snम_लिखो(b->adapter.name, माप(b->adapter.name), name,
		minfo->fbcon.node);
	i2c_set_adapdata(&b->adapter, b);
	b->adapter.class = class;
	b->adapter.algo_data = &b->bac;
	b->adapter.dev.parent = &minfo->pcidev->dev;
	b->bac = matrox_i2c_algo_ढाँचा;
	b->bac.data = b;
	err = i2c_bit_add_bus(&b->adapter);
	b->initialized = !err;
	वापस err;
पूर्ण

अटल व्योम i2c_bit_bus_del(काष्ठा i2c_bit_adapter* b) अणु
	अगर (b->initialized) अणु
		i2c_del_adapter(&b->adapter);
		b->initialized = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम i2c_maven_करोne(काष्ठा matroxfb_dh_maven_info* minfo2) अणु
	i2c_bit_bus_del(&minfo2->maven);
पूर्ण

अटल अंतरभूत व्योम i2c_ddc1_करोne(काष्ठा matroxfb_dh_maven_info* minfo2) अणु
	i2c_bit_bus_del(&minfo2->ddc1);
पूर्ण

अटल अंतरभूत व्योम i2c_ddc2_करोne(काष्ठा matroxfb_dh_maven_info* minfo2) अणु
	i2c_bit_bus_del(&minfo2->ddc2);
पूर्ण

अटल व्योम* i2c_matroxfb_probe(काष्ठा matrox_fb_info* minfo) अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा matroxfb_dh_maven_info* m2info;

	m2info = kzalloc(माप(*m2info), GFP_KERNEL);
	अगर (!m2info)
		वापस शून्य;

	matroxfb_DAC_lock_irqsave(flags);
	matroxfb_DAC_out(minfo, DAC_XGENIODATA, 0xFF);
	matroxfb_DAC_out(minfo, DAC_XGENIOCTRL, 0x00);
	matroxfb_DAC_unlock_irqrestore(flags);

	चयन (minfo->chip) अणु
		हाल MGA_2064:
		हाल MGA_2164:
			err = i2c_bus_reg(&m2info->ddc1, minfo,
					  DDC1B_DATA, DDC1B_CLK,
					  "DDC:fb%u #0", I2C_CLASS_DDC);
			अवरोध;
		शेष:
			err = i2c_bus_reg(&m2info->ddc1, minfo,
					  DDC1_DATA, DDC1_CLK,
					  "DDC:fb%u #0", I2C_CLASS_DDC);
			अवरोध;
	पूर्ण
	अगर (err)
		जाओ fail_ddc1;
	अगर (minfo->devflags.dualhead) अणु
		err = i2c_bus_reg(&m2info->ddc2, minfo,
				  DDC2_DATA, DDC2_CLK,
				  "DDC:fb%u #1", I2C_CLASS_DDC);
		अगर (err == -ENODEV) अणु
			prपूर्णांकk(KERN_INFO "i2c-matroxfb: VGA->TV plug detected, DDC unavailable.\n");
		पूर्ण अन्यथा अगर (err)
			prपूर्णांकk(KERN_INFO "i2c-matroxfb: Could not register secondary output i2c bus. Continuing anyway.\n");
		/* Register maven bus even on G450/G550 */
		err = i2c_bus_reg(&m2info->maven, minfo,
				  MAT_DATA, MAT_CLK, "MAVEN:fb%u", 0);
		अगर (err)
			prपूर्णांकk(KERN_INFO "i2c-matroxfb: Could not register Maven i2c bus. Continuing anyway.\n");
		अन्यथा अणु
			काष्ठा i2c_board_info maven_info = अणु
				I2C_BOARD_INFO("maven", 0x1b),
			पूर्ण;
			अचिन्हित लघु स्थिर addr_list[2] = अणु
				0x1b, I2C_CLIENT_END
			पूर्ण;

			i2c_new_scanned_device(&m2info->maven.adapter,
					       &maven_info, addr_list, शून्य);
		पूर्ण
	पूर्ण
	वापस m2info;
fail_ddc1:;
	kमुक्त(m2info);
	prपूर्णांकk(KERN_ERR "i2c-matroxfb: Could not register primary adapter DDC bus.\n");
	वापस शून्य;
पूर्ण

अटल व्योम i2c_matroxfb_हटाओ(काष्ठा matrox_fb_info* minfo, व्योम* data) अणु
	काष्ठा matroxfb_dh_maven_info* m2info = data;

	i2c_maven_करोne(m2info);
	i2c_ddc2_करोne(m2info);
	i2c_ddc1_करोne(m2info);
	kमुक्त(m2info);
पूर्ण

अटल काष्ठा matroxfb_driver i2c_matroxfb = अणु
	.node =		LIST_HEAD_INIT(i2c_matroxfb.node),
	.name =		"i2c-matroxfb",
	.probe = 	i2c_matroxfb_probe,
	.हटाओ =	i2c_matroxfb_हटाओ,
पूर्ण;

अटल पूर्णांक __init i2c_matroxfb_init(व्योम) अणु
	अगर (matroxfb_रेजिस्टर_driver(&i2c_matroxfb)) अणु
		prपूर्णांकk(KERN_ERR "i2c-matroxfb: failed to register driver\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास i2c_matroxfb_निकास(व्योम) अणु
	matroxfb_unरेजिस्टर_driver(&i2c_matroxfb);
पूर्ण

MODULE_AUTHOR("(c) 1999-2002 Petr Vandrovec <vandrove@vc.cvut.cz>");
MODULE_DESCRIPTION("Support module providing I2C buses present on Matrox videocards");

module_init(i2c_matroxfb_init);
module_निकास(i2c_matroxfb_निकास);
/* no __setup required */
MODULE_LICENSE("GPL");
