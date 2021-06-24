<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* SF16-FMR2 and SF16-FMD2 radio driver क्रम Linux
 * Copyright (c) 2011 Ondrej Zary
 *
 * Original driver was (c) 2000-2002 Ziglio Frediano, freddy77@angelfire.com
 * but almost nothing reमुख्यed here after conversion to generic TEA575x
 * implementation
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>	/* Modules			*/
#समावेश <linux/init.h>		/* Initdata			*/
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>	/* request_region		*/
#समावेश <linux/पन.स>		/* outb, outb_p			*/
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <media/drv-पूर्णांकf/tea575x.h>

MODULE_AUTHOR("Ondrej Zary");
MODULE_DESCRIPTION("MediaForte SF16-FMR2 and SF16-FMD2 FM radio card driver");
MODULE_LICENSE("GPL");

/* these cards can only use two dअगरferent ports (0x384 and 0x284) */
#घोषणा FMR2_MAX 2

अटल पूर्णांक radio_nr[FMR2_MAX] = अणु [0 ... (FMR2_MAX - 1)] = -1 पूर्ण;
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");

काष्ठा fmr2 अणु
	पूर्णांक io;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा snd_tea575x tea;
	काष्ठा v4l2_ctrl *volume;
	काष्ठा v4l2_ctrl *balance;
	bool is_fmd2;
पूर्ण;

अटल पूर्णांक num_fmr2_cards;
अटल काष्ठा fmr2 *fmr2_cards[FMR2_MAX];
अटल bool isa_रेजिस्टरed;
अटल bool pnp_रेजिस्टरed;

/* the port is hardwired on SF16-FMR2 */
#घोषणा FMR2_PORT	0x384

/* TEA575x tuner pins */
#घोषणा STR_DATA	(1 << 0)
#घोषणा STR_CLK		(1 << 1)
#घोषणा STR_WREN	(1 << 2)
#घोषणा STR_MOST	(1 << 3)
/* PT2254A/TC9154A volume control pins */
#घोषणा PT_ST		(1 << 4)
#घोषणा PT_CK		(1 << 5)
#घोषणा PT_DATA		(1 << 6)
/* volume control presence pin */
#घोषणा FMR2_HASVOL	(1 << 7)

अटल व्योम fmr2_tea575x_set_pins(काष्ठा snd_tea575x *tea, u8 pins)
अणु
	काष्ठा fmr2 *fmr2 = tea->निजी_data;
	u8 bits = 0;

	bits |= (pins & TEA575X_DATA) ? STR_DATA : 0;
	bits |= (pins & TEA575X_CLK)  ? STR_CLK  : 0;
	/* WRITE_ENABLE is inverted, DATA must be high during पढ़ो */
	bits |= (pins & TEA575X_WREN) ? 0 : STR_WREN | STR_DATA;

	outb(bits, fmr2->io);
पूर्ण

अटल u8 fmr2_tea575x_get_pins(काष्ठा snd_tea575x *tea)
अणु
	काष्ठा fmr2 *fmr2 = tea->निजी_data;
	u8 bits = inb(fmr2->io);

	वापस  ((bits & STR_DATA) ? TEA575X_DATA : 0) |
		((bits & STR_MOST) ? TEA575X_MOST : 0);
पूर्ण

अटल व्योम fmr2_tea575x_set_direction(काष्ठा snd_tea575x *tea, bool output)
अणु
पूर्ण

अटल स्थिर काष्ठा snd_tea575x_ops fmr2_tea_ops = अणु
	.set_pins = fmr2_tea575x_set_pins,
	.get_pins = fmr2_tea575x_get_pins,
	.set_direction = fmr2_tea575x_set_direction,
पूर्ण;

/* TC9154A/PT2254A volume control */

/* 18-bit shअगरt रेजिस्टर bit definitions */
#घोषणा TC9154A_ATT_MAJ_0DB	(1 << 0)
#घोषणा TC9154A_ATT_MAJ_10DB	(1 << 1)
#घोषणा TC9154A_ATT_MAJ_20DB	(1 << 2)
#घोषणा TC9154A_ATT_MAJ_30DB	(1 << 3)
#घोषणा TC9154A_ATT_MAJ_40DB	(1 << 4)
#घोषणा TC9154A_ATT_MAJ_50DB	(1 << 5)
#घोषणा TC9154A_ATT_MAJ_60DB	(1 << 6)

#घोषणा TC9154A_ATT_MIN_0DB	(1 << 7)
#घोषणा TC9154A_ATT_MIN_2DB	(1 << 8)
#घोषणा TC9154A_ATT_MIN_4DB	(1 << 9)
#घोषणा TC9154A_ATT_MIN_6DB	(1 << 10)
#घोषणा TC9154A_ATT_MIN_8DB	(1 << 11)
/* bit 12 is ignored */
#घोषणा TC9154A_CHANNEL_LEFT	(1 << 13)
#घोषणा TC9154A_CHANNEL_RIGHT	(1 << 14)
/* bits 15, 16, 17 must be 0 */

#घोषणा	TC9154A_ATT_MAJ(x)	(1 << x)
#घोषणा TC9154A_ATT_MIN(x)	(1 << (7 + x))

अटल व्योम tc9154a_set_pins(काष्ठा fmr2 *fmr2, u8 pins)
अणु
	अगर (!fmr2->tea.mute)
		pins |= STR_WREN;

	outb(pins, fmr2->io);
पूर्ण

अटल व्योम tc9154a_set_attenuation(काष्ठा fmr2 *fmr2, पूर्णांक att, u32 channel)
अणु
	पूर्णांक i;
	u32 reg;
	u8 bit;

	reg = TC9154A_ATT_MAJ(att / 10) | TC9154A_ATT_MIN((att % 10) / 2);
	reg |= channel;
	/* ग_लिखो 18-bit shअगरt रेजिस्टर, LSB first */
	क्रम (i = 0; i < 18; i++) अणु
		bit = reg & (1 << i) ? PT_DATA : 0;
		tc9154a_set_pins(fmr2, bit);
		udelay(5);
		tc9154a_set_pins(fmr2, bit | PT_CK);
		udelay(5);
		tc9154a_set_pins(fmr2, bit);
	पूर्ण

	/* latch रेजिस्टर data */
	udelay(5);
	tc9154a_set_pins(fmr2, PT_ST);
	udelay(5);
	tc9154a_set_pins(fmr2, 0);
पूर्ण

अटल पूर्णांक fmr2_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा snd_tea575x *tea = container_of(ctrl->handler, काष्ठा snd_tea575x, ctrl_handler);
	काष्ठा fmr2 *fmr2 = tea->निजी_data;
	पूर्णांक volume, balance, left, right;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_VOLUME:
		volume = ctrl->val;
		balance = fmr2->balance->cur.val;
		अवरोध;
	हाल V4L2_CID_AUDIO_BALANCE:
		balance = ctrl->val;
		volume = fmr2->volume->cur.val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	left = right = volume;
	अगर (balance < 0)
		right = max(0, right + balance);
	अगर (balance > 0)
		left = max(0, left - balance);

	tc9154a_set_attenuation(fmr2, असल(left - 68), TC9154A_CHANNEL_LEFT);
	tc9154a_set_attenuation(fmr2, असल(right - 68), TC9154A_CHANNEL_RIGHT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops fmr2_ctrl_ops = अणु
	.s_ctrl = fmr2_s_ctrl,
पूर्ण;

अटल पूर्णांक fmr2_tea_ext_init(काष्ठा snd_tea575x *tea)
अणु
	काष्ठा fmr2 *fmr2 = tea->निजी_data;

	/* FMR2 can have volume control, FMD2 can't (uses SB16 mixer) */
	अगर (!fmr2->is_fmd2 && inb(fmr2->io) & FMR2_HASVOL) अणु
		fmr2->volume = v4l2_ctrl_new_std(&tea->ctrl_handler, &fmr2_ctrl_ops, V4L2_CID_AUDIO_VOLUME, 0, 68, 2, 56);
		fmr2->balance = v4l2_ctrl_new_std(&tea->ctrl_handler, &fmr2_ctrl_ops, V4L2_CID_AUDIO_BALANCE, -68, 68, 2, 0);
		अगर (tea->ctrl_handler.error) अणु
			prपूर्णांकk(KERN_ERR "radio-sf16fmr2: can't initialize controls\n");
			वापस tea->ctrl_handler.error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pnp_device_id fmr2_pnp_ids[] = अणु
	अणु .id = "MFRad13" पूर्ण, /* tuner subdevice of SF16-FMD2 */
	अणु .id = "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pnp, fmr2_pnp_ids);

अटल पूर्णांक fmr2_probe(काष्ठा fmr2 *fmr2, काष्ठा device *pdev, पूर्णांक io)
अणु
	पूर्णांक err, i;
	अक्षर *card_name = fmr2->is_fmd2 ? "SF16-FMD2" : "SF16-FMR2";

	/* aव्योम errors अगर a card was alपढ़ोy रेजिस्टरed at given port */
	क्रम (i = 0; i < num_fmr2_cards; i++)
		अगर (io == fmr2_cards[i]->io)
			वापस -EBUSY;

	strscpy(fmr2->v4l2_dev.name, "radio-sf16fmr2",
		माप(fmr2->v4l2_dev.name));
	fmr2->io = io;

	अगर (!request_region(fmr2->io, 2, fmr2->v4l2_dev.name)) अणु
		prपूर्णांकk(KERN_ERR "radio-sf16fmr2: I/O port 0x%x already in use\n", fmr2->io);
		वापस -EBUSY;
	पूर्ण

	dev_set_drvdata(pdev, fmr2);
	err = v4l2_device_रेजिस्टर(pdev, &fmr2->v4l2_dev);
	अगर (err < 0) अणु
		v4l2_err(&fmr2->v4l2_dev, "Could not register v4l2_device\n");
		release_region(fmr2->io, 2);
		वापस err;
	पूर्ण
	fmr2->tea.v4l2_dev = &fmr2->v4l2_dev;
	fmr2->tea.निजी_data = fmr2;
	fmr2->tea.radio_nr = radio_nr[num_fmr2_cards];
	fmr2->tea.ops = &fmr2_tea_ops;
	fmr2->tea.ext_init = fmr2_tea_ext_init;
	strscpy(fmr2->tea.card, card_name, माप(fmr2->tea.card));
	snम_लिखो(fmr2->tea.bus_info, माप(fmr2->tea.bus_info), "%s:%s",
			fmr2->is_fmd2 ? "PnP" : "ISA", dev_name(pdev));

	अगर (snd_tea575x_init(&fmr2->tea, THIS_MODULE)) अणु
		prपूर्णांकk(KERN_ERR "radio-sf16fmr2: Unable to detect TEA575x tuner\n");
		release_region(fmr2->io, 2);
		वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(KERN_INFO "radio-sf16fmr2: %s radio card at 0x%x.\n",
			card_name, fmr2->io);
	वापस 0;
पूर्ण

अटल पूर्णांक fmr2_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक ndev)
अणु
	काष्ठा fmr2 *fmr2 = kzalloc(माप(*fmr2), GFP_KERNEL);
	अगर (!fmr2)
		वापस 0;

	अगर (fmr2_probe(fmr2, pdev, FMR2_PORT)) अणु
		kमुक्त(fmr2);
		वापस 0;
	पूर्ण
	dev_set_drvdata(pdev, fmr2);
	fmr2_cards[num_fmr2_cards++] = fmr2;

	वापस 1;
पूर्ण

अटल पूर्णांक fmr2_pnp_probe(काष्ठा pnp_dev *pdev, स्थिर काष्ठा pnp_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा fmr2 *fmr2 = kzalloc(माप(*fmr2), GFP_KERNEL);
	अगर (!fmr2)
		वापस -ENOMEM;

	fmr2->is_fmd2 = true;
	ret = fmr2_probe(fmr2, &pdev->dev, pnp_port_start(pdev, 0));
	अगर (ret) अणु
		kमुक्त(fmr2);
		वापस ret;
	पूर्ण
	pnp_set_drvdata(pdev, fmr2);
	fmr2_cards[num_fmr2_cards++] = fmr2;

	वापस 0;
पूर्ण

अटल व्योम fmr2_हटाओ(काष्ठा fmr2 *fmr2)
अणु
	snd_tea575x_निकास(&fmr2->tea);
	release_region(fmr2->io, 2);
	v4l2_device_unरेजिस्टर(&fmr2->v4l2_dev);
	kमुक्त(fmr2);
पूर्ण

अटल व्योम fmr2_isa_हटाओ(काष्ठा device *pdev, अचिन्हित पूर्णांक ndev)
अणु
	fmr2_हटाओ(dev_get_drvdata(pdev));
पूर्ण

अटल व्योम fmr2_pnp_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	fmr2_हटाओ(pnp_get_drvdata(pdev));
	pnp_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा isa_driver fmr2_isa_driver = अणु
	.match		= fmr2_isa_match,
	.हटाओ		= fmr2_isa_हटाओ,
	.driver		= अणु
		.name	= "radio-sf16fmr2",
	पूर्ण,
पूर्ण;

अटल काष्ठा pnp_driver fmr2_pnp_driver = अणु
	.name		= "radio-sf16fmr2",
	.id_table	= fmr2_pnp_ids,
	.probe		= fmr2_pnp_probe,
	.हटाओ		= fmr2_pnp_हटाओ,
पूर्ण;

अटल पूर्णांक __init fmr2_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pnp_रेजिस्टर_driver(&fmr2_pnp_driver);
	अगर (!ret)
		pnp_रेजिस्टरed = true;
	ret = isa_रेजिस्टर_driver(&fmr2_isa_driver, 1);
	अगर (!ret)
		isa_रेजिस्टरed = true;

	वापस (pnp_रेजिस्टरed || isa_रेजिस्टरed) ? 0 : ret;
पूर्ण

अटल व्योम __निकास fmr2_निकास(व्योम)
अणु
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&fmr2_pnp_driver);
	अगर (isa_रेजिस्टरed)
		isa_unरेजिस्टर_driver(&fmr2_isa_driver);
पूर्ण

module_init(fmr2_init);
module_निकास(fmr2_निकास);
