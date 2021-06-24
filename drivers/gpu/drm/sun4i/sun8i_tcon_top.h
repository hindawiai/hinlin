<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2018 Jernej Skrabec <jernej.skrabec@siol.net> */

#अगर_अघोषित _SUN8I_TCON_TOP_H_
#घोषणा _SUN8I_TCON_TOP_H_

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>

#घोषणा TCON_TOP_TCON_TV_SETUP_REG	0x00

#घोषणा TCON_TOP_PORT_SEL_REG		0x1C
#घोषणा TCON_TOP_PORT_DE0_MSK			GENMASK(1, 0)
#घोषणा TCON_TOP_PORT_DE1_MSK			GENMASK(5, 4)

#घोषणा TCON_TOP_GATE_SRC_REG		0x20
#घोषणा TCON_TOP_HDMI_SRC_MSK			GENMASK(29, 28)
#घोषणा TCON_TOP_TCON_TV1_GATE			24
#घोषणा TCON_TOP_TCON_TV0_GATE			20
#घोषणा TCON_TOP_TCON_DSI_GATE			16

#घोषणा CLK_NUM					3

काष्ठा sun8i_tcon_top अणु
	काष्ठा clk			*bus;
	काष्ठा clk_hw_onecell_data	*clk_data;
	व्योम __iomem			*regs;
	काष्ठा reset_control		*rst;

	/*
	 * spinlock is used to synchronize access to same
	 * रेजिस्टर where multiple घड़ी gates can be set.
	 */
	spinlock_t			reg_lock;
पूर्ण;

बाह्य स्थिर काष्ठा of_device_id sun8i_tcon_top_of_table[];

पूर्णांक sun8i_tcon_top_set_hdmi_src(काष्ठा device *dev, पूर्णांक tcon);
पूर्णांक sun8i_tcon_top_de_config(काष्ठा device *dev, पूर्णांक mixer, पूर्णांक tcon);

#पूर्ण_अगर /* _SUN8I_TCON_TOP_H_ */
