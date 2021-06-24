<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम the four N64 controllers.
 *
 * Copyright (c) 2021 Lauri Kasanen
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

MODULE_AUTHOR("Lauri Kasanen <cand@gmx.com>");
MODULE_DESCRIPTION("Driver for N64 controllers");
MODULE_LICENSE("GPL");

#घोषणा PIF_RAM 0x1fc007c0

#घोषणा SI_DRAM_REG 0
#घोषणा SI_READ_REG 1
#घोषणा SI_WRITE_REG 4
#घोषणा SI_STATUS_REG 6

#घोषणा SI_STATUS_DMA_BUSY  BIT(0)
#घोषणा SI_STATUS_IO_BUSY   BIT(1)

#घोषणा N64_CONTROLLER_ID 0x0500

#घोषणा MAX_CONTROLLERS 4

अटल स्थिर अक्षर *n64joy_phys[MAX_CONTROLLERS] = अणु
	"n64joy/port0",
	"n64joy/port1",
	"n64joy/port2",
	"n64joy/port3",
पूर्ण;

काष्ठा n64joy_priv अणु
	u64 si_buf[8] ____cacheline_aligned;
	काष्ठा समयr_list समयr;
	काष्ठा mutex n64joy_mutex;
	काष्ठा input_dev *n64joy_dev[MAX_CONTROLLERS];
	u32 __iomem *reg_base;
	u8 n64joy_खोलोed;
पूर्ण;

काष्ठा joydata अणु
	अचिन्हित पूर्णांक: 16; /* unused */
	अचिन्हित पूर्णांक err: 2;
	अचिन्हित पूर्णांक: 14; /* unused */

	जोड़ अणु
		u32 data;

		काष्ठा अणु
			अचिन्हित पूर्णांक a: 1;
			अचिन्हित पूर्णांक b: 1;
			अचिन्हित पूर्णांक z: 1;
			अचिन्हित पूर्णांक start: 1;
			अचिन्हित पूर्णांक up: 1;
			अचिन्हित पूर्णांक करोwn: 1;
			अचिन्हित पूर्णांक left: 1;
			अचिन्हित पूर्णांक right: 1;
			अचिन्हित पूर्णांक: 2; /* unused */
			अचिन्हित पूर्णांक l: 1;
			अचिन्हित पूर्णांक r: 1;
			अचिन्हित पूर्णांक c_up: 1;
			अचिन्हित पूर्णांक c_करोwn: 1;
			अचिन्हित पूर्णांक c_left: 1;
			अचिन्हित पूर्णांक c_right: 1;
			चिन्हित पूर्णांक x: 8;
			चिन्हित पूर्णांक y: 8;
		पूर्ण;
	पूर्ण;
पूर्ण;

अटल व्योम n64joy_ग_लिखो_reg(u32 __iomem *reg_base, स्थिर u8 reg, स्थिर u32 value)
अणु
	ग_लिखोl(value, reg_base + reg);
पूर्ण

अटल u32 n64joy_पढ़ो_reg(u32 __iomem *reg_base, स्थिर u8 reg)
अणु
	वापस पढ़ोl(reg_base + reg);
पूर्ण

अटल व्योम n64joy_रुको_si_dma(u32 __iomem *reg_base)
अणु
	जबतक (n64joy_पढ़ो_reg(reg_base, SI_STATUS_REG) &
	       (SI_STATUS_DMA_BUSY | SI_STATUS_IO_BUSY))
		cpu_relax();
पूर्ण

अटल व्योम n64joy_exec_pअगर(काष्ठा n64joy_priv *priv, स्थिर u64 in[8])
अणु
	अचिन्हित दीर्घ flags;

	dma_cache_wback_inv((अचिन्हित दीर्घ) in, 8 * 8);
	dma_cache_inv((अचिन्हित दीर्घ) priv->si_buf, 8 * 8);

	local_irq_save(flags);

	n64joy_रुको_si_dma(priv->reg_base);

	barrier();
	n64joy_ग_लिखो_reg(priv->reg_base, SI_DRAM_REG, virt_to_phys(in));
	barrier();
	n64joy_ग_लिखो_reg(priv->reg_base, SI_WRITE_REG, PIF_RAM);
	barrier();

	n64joy_रुको_si_dma(priv->reg_base);

	barrier();
	n64joy_ग_लिखो_reg(priv->reg_base, SI_DRAM_REG, virt_to_phys(priv->si_buf));
	barrier();
	n64joy_ग_लिखो_reg(priv->reg_base, SI_READ_REG, PIF_RAM);
	barrier();

	n64joy_रुको_si_dma(priv->reg_base);

	local_irq_restore(flags);
पूर्ण

अटल स्थिर u64 polldata[] ____cacheline_aligned = अणु
	0xff010401ffffffff,
	0xff010401ffffffff,
	0xff010401ffffffff,
	0xff010401ffffffff,
	0xfe00000000000000,
	0,
	0,
	1
पूर्ण;

अटल व्योम n64joy_poll(काष्ठा समयr_list *t)
अणु
	स्थिर काष्ठा joydata *data;
	काष्ठा n64joy_priv *priv = container_of(t, काष्ठा n64joy_priv, समयr);
	काष्ठा input_dev *dev;
	u32 i;

	n64joy_exec_pअगर(priv, polldata);

	data = (काष्ठा joydata *) priv->si_buf;

	क्रम (i = 0; i < MAX_CONTROLLERS; i++) अणु
		अगर (!priv->n64joy_dev[i])
			जारी;

		dev = priv->n64joy_dev[i];

		/* d-pad */
		input_report_key(dev, BTN_DPAD_UP, data[i].up);
		input_report_key(dev, BTN_DPAD_DOWN, data[i].करोwn);
		input_report_key(dev, BTN_DPAD_LEFT, data[i].left);
		input_report_key(dev, BTN_DPAD_RIGHT, data[i].right);

		/* c buttons */
		input_report_key(dev, BTN_FORWARD, data[i].c_up);
		input_report_key(dev, BTN_BACK, data[i].c_करोwn);
		input_report_key(dev, BTN_LEFT, data[i].c_left);
		input_report_key(dev, BTN_RIGHT, data[i].c_right);

		/* matching buttons */
		input_report_key(dev, BTN_START, data[i].start);
		input_report_key(dev, BTN_Z, data[i].z);

		/* reमुख्यing ones: a, b, l, r */
		input_report_key(dev, BTN_0, data[i].a);
		input_report_key(dev, BTN_1, data[i].b);
		input_report_key(dev, BTN_2, data[i].l);
		input_report_key(dev, BTN_3, data[i].r);

		input_report_असल(dev, ABS_X, data[i].x);
		input_report_असल(dev, ABS_Y, data[i].y);

		input_sync(dev);
	पूर्ण

	mod_समयr(&priv->समयr, jअगरfies + msecs_to_jअगरfies(16));
पूर्ण

अटल पूर्णांक n64joy_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा n64joy_priv *priv = input_get_drvdata(dev);
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&priv->n64joy_mutex);
	अगर (err)
		वापस err;

	अगर (!priv->n64joy_खोलोed) अणु
		/*
		 * We could use the vblank irq, but it's not important अगर
		 * the poll poपूर्णांक slightly changes.
		 */
		समयr_setup(&priv->समयr, n64joy_poll, 0);
		mod_समयr(&priv->समयr, jअगरfies + msecs_to_jअगरfies(16));
	पूर्ण

	priv->n64joy_खोलोed++;

	mutex_unlock(&priv->n64joy_mutex);
	वापस err;
पूर्ण

अटल व्योम n64joy_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा n64joy_priv *priv = input_get_drvdata(dev);

	mutex_lock(&priv->n64joy_mutex);
	अगर (!--priv->n64joy_खोलोed)
		del_समयr_sync(&priv->समयr);
	mutex_unlock(&priv->n64joy_mutex);
पूर्ण

अटल स्थिर u64 __initस्थिर scandata[] ____cacheline_aligned = अणु
	0xff010300ffffffff,
	0xff010300ffffffff,
	0xff010300ffffffff,
	0xff010300ffffffff,
	0xfe00000000000000,
	0,
	0,
	1
पूर्ण;

/*
 * The target device is embedded and RAM-स्थिरrained. We save RAM
 * by initializing in __init code that माला_लो dropped late in boot.
 * For the same reason there is no module or unloading support.
 */
अटल पूर्णांक __init n64joy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा joydata *data;
	काष्ठा n64joy_priv *priv;
	काष्ठा input_dev *dev;
	पूर्णांक err = 0;
	u32 i, j, found = 0;

	priv = kzalloc(माप(काष्ठा n64joy_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	mutex_init(&priv->n64joy_mutex);

	priv->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->reg_base)) अणु
		err = PTR_ERR(priv->reg_base);
		जाओ fail;
	पूर्ण

	/* The controllers are not hotpluggable, so we can scan in init */
	n64joy_exec_pअगर(priv, scandata);

	data = (काष्ठा joydata *) priv->si_buf;

	क्रम (i = 0; i < MAX_CONTROLLERS; i++) अणु
		अगर (!data[i].err && data[i].data >> 16 == N64_CONTROLLER_ID) अणु
			found++;

			dev = priv->n64joy_dev[i] = input_allocate_device();
			अगर (!priv->n64joy_dev[i]) अणु
				err = -ENOMEM;
				जाओ fail;
			पूर्ण

			input_set_drvdata(dev, priv);

			dev->name = "N64 controller";
			dev->phys = n64joy_phys[i];
			dev->id.bustype = BUS_HOST;
			dev->id.venकरोr = 0;
			dev->id.product = data[i].data >> 16;
			dev->id.version = 0;
			dev->dev.parent = &pdev->dev;

			dev->खोलो = n64joy_खोलो;
			dev->बंद = n64joy_बंद;

			/* d-pad */
			input_set_capability(dev, EV_KEY, BTN_DPAD_UP);
			input_set_capability(dev, EV_KEY, BTN_DPAD_DOWN);
			input_set_capability(dev, EV_KEY, BTN_DPAD_LEFT);
			input_set_capability(dev, EV_KEY, BTN_DPAD_RIGHT);
			/* c buttons */
			input_set_capability(dev, EV_KEY, BTN_LEFT);
			input_set_capability(dev, EV_KEY, BTN_RIGHT);
			input_set_capability(dev, EV_KEY, BTN_FORWARD);
			input_set_capability(dev, EV_KEY, BTN_BACK);
			/* matching buttons */
			input_set_capability(dev, EV_KEY, BTN_START);
			input_set_capability(dev, EV_KEY, BTN_Z);
			/* reमुख्यing ones: a, b, l, r */
			input_set_capability(dev, EV_KEY, BTN_0);
			input_set_capability(dev, EV_KEY, BTN_1);
			input_set_capability(dev, EV_KEY, BTN_2);
			input_set_capability(dev, EV_KEY, BTN_3);

			क्रम (j = 0; j < 2; j++)
				input_set_असल_params(dev, ABS_X + j,
						     S8_MIN, S8_MAX, 0, 0);

			err = input_रेजिस्टर_device(dev);
			अगर (err) अणु
				input_मुक्त_device(dev);
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	pr_info("%u controller(s) connected\n", found);

	अगर (!found)
		वापस -ENODEV;

	वापस 0;
fail:
	क्रम (i = 0; i < MAX_CONTROLLERS; i++) अणु
		अगर (!priv->n64joy_dev[i])
			जारी;
		input_unरेजिस्टर_device(priv->n64joy_dev[i]);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver n64joy_driver = अणु
	.driver = अणु
		.name = "n64joy",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init n64joy_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&n64joy_driver, n64joy_probe);
पूर्ण

module_init(n64joy_init);
