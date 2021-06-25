<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/hp6xx/setup.c
 *
 * Copyright (C) 2002 Andriy Skulysh
 * Copyright (C) 2007 Kristoffer Ericson <Kristoffer_e1@hoपंचांगail.com>
 *
 * Setup code क्रम HP620/HP660/HP680/HP690 (पूर्णांकernal peripherials only)
 */
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <sound/sh_dac_audपन.स>
#समावेश <यंत्र/hd64461.h>
#समावेश <यंत्र/पन.स>
#समावेश <mach/hp6xx.h>
#समावेश <cpu/dac.h>

#घोषणा	SCPCR	0xa4000116
#घोषणा	SCPDR	0xa4000136

/* CF Slot */
अटल काष्ठा resource cf_ide_resources[] = अणु
	[0] = अणु
		.start = 0x15000000 + 0x1f0,
		.end   = 0x15000000 + 0x1f0 + 0x08 - 0x01,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = 0x15000000 + 0x1fe,
		.end   = 0x15000000 + 0x1fe + 0x01,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start = evt2irq(0xba0),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device cf_ide_device = अणु
	.name		=  "pata_platform",
	.id		=  -1,
	.num_resources	= ARRAY_SIZE(cf_ide_resources),
	.resource	= cf_ide_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device jornadakbd_device = अणु
	.name		= "jornada680_kbd",
	.id		= -1,
पूर्ण;

अटल व्योम dac_audio_start(काष्ठा dac_audio_pdata *pdata)
अणु
	u16 v;
	u8 v8;

	/* HP Jornada 680/690 speaker on */
	v = inw(HD64461_GPADR);
	v &= ~HD64461_GPADR_SPEAKER;
	outw(v, HD64461_GPADR);

	/* HP Palmtop 620lx/660lx speaker on */
	v8 = inb(PKDR);
	v8 &= ~PKDR_SPEAKER;
	outb(v8, PKDR);

	sh_dac_enable(pdata->channel);
पूर्ण

अटल व्योम dac_audio_stop(काष्ठा dac_audio_pdata *pdata)
अणु
	u16 v;
	u8 v8;

	/* HP Jornada 680/690 speaker off */
	v = inw(HD64461_GPADR);
	v |= HD64461_GPADR_SPEAKER;
	outw(v, HD64461_GPADR);

	/* HP Palmtop 620lx/660lx speaker off */
	v8 = inb(PKDR);
	v8 |= PKDR_SPEAKER;
	outb(v8, PKDR);

	sh_dac_output(0, pdata->channel);
	sh_dac_disable(pdata->channel);
पूर्ण

अटल काष्ठा dac_audio_pdata dac_audio_platक्रमm_data = अणु
	.buffer_size		= 64000,
	.channel		= 1,
	.start			= dac_audio_start,
	.stop			= dac_audio_stop,
पूर्ण;

अटल काष्ठा platक्रमm_device dac_audio_device = अणु
	.name		= "dac_audio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &dac_audio_platक्रमm_data,
	पूर्ण

पूर्ण;

अटल काष्ठा platक्रमm_device *hp6xx_devices[] __initdata = अणु
	&cf_ide_device,
	&jornadakbd_device,
	&dac_audio_device,
पूर्ण;

अटल व्योम __init hp6xx_init_irq(व्योम)
अणु
	/* Gets touchscreen and घातerbutton IRQ working */
	plat_irq_setup_pins(IRQ_MODE_IRQ);
पूर्ण

अटल पूर्णांक __init hp6xx_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(hp6xx_devices, ARRAY_SIZE(hp6xx_devices));
पूर्ण

अटल व्योम __init hp6xx_setup(अक्षर **cmdline_p)
अणु
	u8 v8;
	u16 v;

	v = inw(HD64461_STBCR);
	v |=	HD64461_STBCR_SURTST | HD64461_STBCR_SIRST	|
		HD64461_STBCR_STM1ST | HD64461_STBCR_STM0ST	|
		HD64461_STBCR_SAFEST | HD64461_STBCR_SPC0ST	|
		HD64461_STBCR_SMIAST | HD64461_STBCR_SAFECKE_OST|
		HD64461_STBCR_SAFECKE_IST;
#अगर_अघोषित CONFIG_HD64461_ENABLER
	v |= HD64461_STBCR_SPC1ST;
#पूर्ण_अगर
	outw(v, HD64461_STBCR);
	v = inw(HD64461_GPADR);
	v |= HD64461_GPADR_SPEAKER | HD64461_GPADR_PCMCIA0;
	outw(v, HD64461_GPADR);

	outw(HD64461_PCCGCR_VCC0 | HD64461_PCCSCR_VCC1, HD64461_PCC0GCR);

#अगर_अघोषित CONFIG_HD64461_ENABLER
	outw(HD64461_PCCGCR_VCC0 | HD64461_PCCSCR_VCC1, HD64461_PCC1GCR);
#पूर्ण_अगर

	sh_dac_output(0, DAC_SPEAKER_VOLUME);
	sh_dac_disable(DAC_SPEAKER_VOLUME);
	v8 = __raw_पढ़ोb(DACR);
	v8 &= ~DACR_DAE;
	__raw_ग_लिखोb(v8,DACR);

	v8 = __raw_पढ़ोb(SCPDR);
	v8 |= SCPDR_TS_SCAN_X | SCPDR_TS_SCAN_Y;
	v8 &= ~SCPDR_TS_SCAN_ENABLE;
	__raw_ग_लिखोb(v8, SCPDR);

	v = __raw_पढ़ोw(SCPCR);
	v &= ~SCPCR_TS_MASK;
	v |= SCPCR_TS_ENABLE;
	__raw_ग_लिखोw(v, SCPCR);
पूर्ण
device_initcall(hp6xx_devices_setup);

अटल काष्ठा sh_machine_vector mv_hp6xx __iniपंचांगv = अणु
	.mv_name = "hp6xx",
	.mv_setup = hp6xx_setup,
	/* Enable IRQ0 -> IRQ3 in IRQ_MODE */
	.mv_init_irq = hp6xx_init_irq,
पूर्ण;
