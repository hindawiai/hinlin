<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __PINCTRL_MXS_H
#घोषणा __PINCTRL_MXS_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>

#घोषणा SET	0x4
#घोषणा CLR	0x8
#घोषणा TOG	0xc

#घोषणा MXS_PINCTRL_PIN(pin)	PINCTRL_PIN(pin, #pin)
#घोषणा PINID(bank, pin)	((bank) * 32 + (pin))

/*
 * pinmux-id bit field definitions
 *
 * bank:	15..12	(4)
 * pin:		11..4	(8)
 * muxsel:	3..0	(4)
 */
#घोषणा MUXID_TO_PINID(m)	PINID((m) >> 12 & 0xf, (m) >> 4 & 0xff)
#घोषणा MUXID_TO_MUXSEL(m)	((m) & 0xf)

#घोषणा PINID_TO_BANK(p)	((p) >> 5)
#घोषणा PINID_TO_PIN(p)		((p) % 32)

/*
 * pin config bit field definitions
 *
 * pull-up:	6..5	(2)
 * voltage:	4..3	(2)
 * mA:		2..0	(3)
 *
 * MSB of each field is presence bit क्रम the config.
 */
#घोषणा PULL_PRESENT		(1 << 6)
#घोषणा PULL_SHIFT		5
#घोषणा VOL_PRESENT		(1 << 4)
#घोषणा VOL_SHIFT		3
#घोषणा MA_PRESENT		(1 << 2)
#घोषणा MA_SHIFT		0
#घोषणा CONFIG_TO_PULL(c)	((c) >> PULL_SHIFT & 0x1)
#घोषणा CONFIG_TO_VOL(c)	((c) >> VOL_SHIFT & 0x1)
#घोषणा CONFIG_TO_MA(c)		((c) >> MA_SHIFT & 0x3)

काष्ठा mxs_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर **groups;
	अचिन्हित ngroups;
पूर्ण;

काष्ठा mxs_group अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक *pins;
	अचिन्हित npins;
	u8 *muxsel;
	u8 config;
पूर्ण;

काष्ठा mxs_regs अणु
	u16 muxsel;
	u16 drive;
	u16 pull;
पूर्ण;

काष्ठा mxs_pinctrl_soc_data अणु
	स्थिर काष्ठा mxs_regs *regs;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित npins;
	काष्ठा mxs_function *functions;
	अचिन्हित nfunctions;
	काष्ठा mxs_group *groups;
	अचिन्हित ngroups;
पूर्ण;

पूर्णांक mxs_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		      काष्ठा mxs_pinctrl_soc_data *soc);

#पूर्ण_अगर /* __PINCTRL_MXS_H */
