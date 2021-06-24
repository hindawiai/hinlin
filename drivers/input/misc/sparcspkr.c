<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम PC-speaker like devices found on various Sparc प्रणालीs.
 *
 *  Copyright (c) 2002 Vojtech Pavlik
 *  Copyright (c) 2002, 2006, 2008 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>

MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_DESCRIPTION("Sparc Speaker beeper driver");
MODULE_LICENSE("GPL");

काष्ठा grover_beep_info अणु
	व्योम __iomem	*freq_regs;
	व्योम __iomem	*enable_reg;
पूर्ण;

काष्ठा bbc_beep_info अणु
	u32		घड़ी_freq;
	व्योम __iomem	*regs;
पूर्ण;

काष्ठा sparcspkr_state अणु
	स्थिर अक्षर		*name;
	पूर्णांक (*event)(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value);
	spinlock_t		lock;
	काष्ठा input_dev	*input_dev;
	जोड़ अणु
		काष्ठा grover_beep_info grover;
		काष्ठा bbc_beep_info bbc;
	पूर्ण u;
पूर्ण;

अटल u32 bbc_count_to_reg(काष्ठा bbc_beep_info *info, अचिन्हित पूर्णांक count)
अणु
	u32 val, घड़ी_freq = info->घड़ी_freq;
	पूर्णांक i;

	अगर (!count)
		वापस 0;

	अगर (count <= घड़ी_freq >> 20)
		वापस 1 << 18;

	अगर (count >= घड़ी_freq >> 12)
		वापस 1 << 10;

	val = 1 << 18;
	क्रम (i = 19; i >= 11; i--) अणु
		val >>= 1;
		अगर (count <= घड़ी_freq >> i)
			अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक bbc_spkr_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा sparcspkr_state *state = dev_get_drvdata(dev->dev.parent);
	काष्ठा bbc_beep_info *info = &state->u.bbc;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;

	अगर (type != EV_SND)
		वापस -1;

	चयन (code) अणु
		हाल SND_BELL: अगर (value) value = 1000;
		हाल SND_TONE: अवरोध;
		शेष: वापस -1;
	पूर्ण

	अगर (value > 20 && value < 32767)
		count = 1193182 / value;

	count = bbc_count_to_reg(info, count);

	spin_lock_irqsave(&state->lock, flags);

	अगर (count) अणु
		sbus_ग_लिखोb(0x01,                 info->regs + 0);
		sbus_ग_लिखोb(0x00,                 info->regs + 2);
		sbus_ग_लिखोb((count >> 16) & 0xff, info->regs + 3);
		sbus_ग_लिखोb((count >>  8) & 0xff, info->regs + 4);
		sbus_ग_लिखोb(0x00,                 info->regs + 5);
	पूर्ण अन्यथा अणु
		sbus_ग_लिखोb(0x00,                 info->regs + 0);
	पूर्ण

	spin_unlock_irqrestore(&state->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक grover_spkr_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा sparcspkr_state *state = dev_get_drvdata(dev->dev.parent);
	काष्ठा grover_beep_info *info = &state->u.grover;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;

	अगर (type != EV_SND)
		वापस -1;

	चयन (code) अणु
		हाल SND_BELL: अगर (value) value = 1000;
		हाल SND_TONE: अवरोध;
		शेष: वापस -1;
	पूर्ण

	अगर (value > 20 && value < 32767)
		count = 1193182 / value;

	spin_lock_irqsave(&state->lock, flags);

	अगर (count) अणु
		/* enable counter 2 */
		sbus_ग_लिखोb(sbus_पढ़ोb(info->enable_reg) | 3, info->enable_reg);
		/* set command क्रम counter 2, 2 byte ग_लिखो */
		sbus_ग_लिखोb(0xB6, info->freq_regs + 1);
		/* select desired HZ */
		sbus_ग_लिखोb(count & 0xff, info->freq_regs + 0);
		sbus_ग_लिखोb((count >> 8) & 0xff, info->freq_regs + 0);
	पूर्ण अन्यथा अणु
		/* disable counter 2 */
		sbus_ग_लिखोb(sbus_पढ़ोb(info->enable_reg) & 0xFC, info->enable_reg);
	पूर्ण

	spin_unlock_irqrestore(&state->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sparcspkr_probe(काष्ठा device *dev)
अणु
	काष्ठा sparcspkr_state *state = dev_get_drvdata(dev);
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = state->name;
	input_dev->phys = "sparc/input0";
	input_dev->id.bustype = BUS_ISA;
	input_dev->id.venकरोr = 0x001f;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = dev;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);

	input_dev->event = state->event;

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		input_मुक्त_device(input_dev);
		वापस error;
	पूर्ण

	state->input_dev = input_dev;

	वापस 0;
पूर्ण

अटल व्योम sparcspkr_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sparcspkr_state *state = platक्रमm_get_drvdata(dev);
	काष्ठा input_dev *input_dev = state->input_dev;

	/* turn off the speaker */
	state->event(input_dev, EV_SND, SND_BELL, 0);
पूर्ण

अटल पूर्णांक bbc_beep_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा sparcspkr_state *state;
	काष्ठा bbc_beep_info *info;
	काष्ठा device_node *dp;
	पूर्णांक err = -ENOMEM;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		जाओ out_err;

	state->name = "Sparc BBC Speaker";
	state->event = bbc_spkr_event;
	spin_lock_init(&state->lock);

	dp = of_find_node_by_path("/");
	err = -ENODEV;
	अगर (!dp)
		जाओ out_मुक्त;

	info = &state->u.bbc;
	info->घड़ी_freq = of_getपूर्णांकprop_शेष(dp, "clock-frequency", 0);
	अगर (!info->घड़ी_freq)
		जाओ out_मुक्त;

	info->regs = of_ioremap(&op->resource[0], 0, 6, "bbc beep");
	अगर (!info->regs)
		जाओ out_मुक्त;

	platक्रमm_set_drvdata(op, state);

	err = sparcspkr_probe(&op->dev);
	अगर (err)
		जाओ out_clear_drvdata;

	वापस 0;

out_clear_drvdata:
	of_iounmap(&op->resource[0], info->regs, 6);

out_मुक्त:
	kमुक्त(state);
out_err:
	वापस err;
पूर्ण

अटल पूर्णांक bbc_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा sparcspkr_state *state = platक्रमm_get_drvdata(op);
	काष्ठा input_dev *input_dev = state->input_dev;
	काष्ठा bbc_beep_info *info = &state->u.bbc;

	/* turn off the speaker */
	state->event(input_dev, EV_SND, SND_BELL, 0);

	input_unरेजिस्टर_device(input_dev);

	of_iounmap(&op->resource[0], info->regs, 6);

	kमुक्त(state);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bbc_beep_match[] = अणु
	अणु
		.name = "beep",
		.compatible = "SUNW,bbc-beep",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bbc_beep_match);

अटल काष्ठा platक्रमm_driver bbc_beep_driver = अणु
	.driver = अणु
		.name = "bbcbeep",
		.of_match_table = bbc_beep_match,
	पूर्ण,
	.probe		= bbc_beep_probe,
	.हटाओ		= bbc_हटाओ,
	.shutकरोwn	= sparcspkr_shutकरोwn,
पूर्ण;

अटल पूर्णांक grover_beep_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा sparcspkr_state *state;
	काष्ठा grover_beep_info *info;
	पूर्णांक err = -ENOMEM;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		जाओ out_err;

	state->name = "Sparc Grover Speaker";
	state->event = grover_spkr_event;
	spin_lock_init(&state->lock);

	info = &state->u.grover;
	info->freq_regs = of_ioremap(&op->resource[2], 0, 2, "grover beep freq");
	अगर (!info->freq_regs)
		जाओ out_मुक्त;

	info->enable_reg = of_ioremap(&op->resource[3], 0, 1, "grover beep enable");
	अगर (!info->enable_reg)
		जाओ out_unmap_freq_regs;

	platक्रमm_set_drvdata(op, state);

	err = sparcspkr_probe(&op->dev);
	अगर (err)
		जाओ out_clear_drvdata;

	वापस 0;

out_clear_drvdata:
	of_iounmap(&op->resource[3], info->enable_reg, 1);

out_unmap_freq_regs:
	of_iounmap(&op->resource[2], info->freq_regs, 2);
out_मुक्त:
	kमुक्त(state);
out_err:
	वापस err;
पूर्ण

अटल पूर्णांक grover_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा sparcspkr_state *state = platक्रमm_get_drvdata(op);
	काष्ठा grover_beep_info *info = &state->u.grover;
	काष्ठा input_dev *input_dev = state->input_dev;

	/* turn off the speaker */
	state->event(input_dev, EV_SND, SND_BELL, 0);

	input_unरेजिस्टर_device(input_dev);

	of_iounmap(&op->resource[3], info->enable_reg, 1);
	of_iounmap(&op->resource[2], info->freq_regs, 2);

	kमुक्त(state);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id grover_beep_match[] = अणु
	अणु
		.name = "beep",
		.compatible = "SUNW,smbus-beep",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, grover_beep_match);

अटल काष्ठा platक्रमm_driver grover_beep_driver = अणु
	.driver = अणु
		.name = "groverbeep",
		.of_match_table = grover_beep_match,
	पूर्ण,
	.probe		= grover_beep_probe,
	.हटाओ		= grover_हटाओ,
	.shutकरोwn	= sparcspkr_shutकरोwn,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&bbc_beep_driver,
	&grover_beep_driver,
पूर्ण;

अटल पूर्णांक __init sparcspkr_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

अटल व्योम __निकास sparcspkr_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

module_init(sparcspkr_init);
module_निकास(sparcspkr_निकास);
