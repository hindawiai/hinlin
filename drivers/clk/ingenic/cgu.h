<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Ingenic SoC CGU driver
 *
 * Copyright (c) 2013-2015 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __DRIVERS_CLK_INGENIC_CGU_H__
#घोषणा __DRIVERS_CLK_INGENIC_CGU_H__

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/spinlock.h>

/**
 * काष्ठा ingenic_cgu_pll_info - inक्रमmation about a PLL
 * @reg: the offset of the PLL's control रेजिस्टर within the CGU
 * @rate_multiplier: the multiplier needed by pll rate calculation
 * @m_shअगरt: the number of bits to shअगरt the multiplier value by (ie. the
 *           index of the lowest bit of the multiplier value in the PLL's
 *           control रेजिस्टर)
 * @m_bits: the size of the multiplier field in bits
 * @m_offset: the multiplier value which encodes to 0 in the PLL's control
 *            रेजिस्टर
 * @n_shअगरt: the number of bits to shअगरt the भागider value by (ie. the
 *           index of the lowest bit of the भागider value in the PLL's
 *           control रेजिस्टर)
 * @n_bits: the size of the भागider field in bits
 * @n_offset: the भागider value which encodes to 0 in the PLL's control
 *            रेजिस्टर
 * @od_shअगरt: the number of bits to shअगरt the post-VCO भागider value by (ie.
 *            the index of the lowest bit of the post-VCO भागider value in
 *            the PLL's control रेजिस्टर)
 * @od_bits: the size of the post-VCO भागider field in bits
 * @od_max: the maximum post-VCO भागider value
 * @od_encoding: a poपूर्णांकer to an array mapping post-VCO भागider values to
 *               their encoded values in the PLL control रेजिस्टर, or -1 क्रम
 *               unsupported values
 * @bypass_reg: the offset of the bypass control रेजिस्टर within the CGU
 * @bypass_bit: the index of the bypass bit in the PLL control रेजिस्टर
 * @enable_bit: the index of the enable bit in the PLL control रेजिस्टर
 * @stable_bit: the index of the stable bit in the PLL control रेजिस्टर
 * @no_bypass_bit: अगर set, the PLL has no bypass functionality
 */
काष्ठा ingenic_cgu_pll_info अणु
	अचिन्हित reg;
	अचिन्हित rate_multiplier;
	स्थिर s8 *od_encoding;
	u8 m_shअगरt, m_bits, m_offset;
	u8 n_shअगरt, n_bits, n_offset;
	u8 od_shअगरt, od_bits, od_max;
	अचिन्हित bypass_reg;
	u8 bypass_bit;
	u8 enable_bit;
	u8 stable_bit;
	bool no_bypass_bit;
पूर्ण;

/**
 * काष्ठा ingenic_cgu_mux_info - inक्रमmation about a घड़ी mux
 * @reg: offset of the mux control रेजिस्टर within the CGU
 * @shअगरt: number of bits to shअगरt the mux value by (ie. the index of
 *         the lowest bit of the mux value within its control रेजिस्टर)
 * @bits: the size of the mux value in bits
 */
काष्ठा ingenic_cgu_mux_info अणु
	अचिन्हित reg;
	u8 shअगरt;
	u8 bits;
पूर्ण;

/**
 * काष्ठा ingenic_cgu_भाग_info - inक्रमmation about a भागider
 * @reg: offset of the भागider control रेजिस्टर within the CGU
 * @shअगरt: number of bits to left shअगरt the भागide value by (ie. the index of
 *         the lowest bit of the भागide value within its control रेजिस्टर)
 * @भाग: number to भागide the भागider value by (i.e. अगर the
 *	 effective भागider value is the value written to the रेजिस्टर
 *	 multiplied by some स्थिरant)
 * @bits: the size of the भागide value in bits
 * @ce_bit: the index of the change enable bit within reg, or -1 अगर there
 *          isn't one
 * @busy_bit: the index of the busy bit within reg, or -1 अगर there isn't one
 * @stop_bit: the index of the stop bit within reg, or -1 अगर there isn't one
 * @भाग_प्रकारable: optional table to map the value पढ़ो from the रेजिस्टर to the
 *             actual भागider value
 */
काष्ठा ingenic_cgu_भाग_info अणु
	अचिन्हित reg;
	u8 shअगरt;
	u8 भाग;
	u8 bits;
	s8 ce_bit;
	s8 busy_bit;
	s8 stop_bit;
	स्थिर u8 *भाग_प्रकारable;
पूर्ण;

/**
 * काष्ठा ingenic_cgu_fixभाग_info - inक्रमmation about a fixed भागider
 * @भाग: the भागider applied to the parent घड़ी
 */
काष्ठा ingenic_cgu_fixभाग_info अणु
	अचिन्हित भाग;
पूर्ण;

/**
 * काष्ठा ingenic_cgu_gate_info - inक्रमmation about a घड़ी gate
 * @reg: offset of the gate control रेजिस्टर within the CGU
 * @bit: offset of the bit in the रेजिस्टर that controls the gate
 * @clear_to_gate: अगर set, the घड़ी is gated when the bit is cleared
 * @delay_us: delay in microseconds after which the घड़ी is considered stable
 */
काष्ठा ingenic_cgu_gate_info अणु
	अचिन्हित reg;
	u8 bit;
	bool clear_to_gate;
	u16 delay_us;
पूर्ण;

/**
 * काष्ठा ingenic_cgu_custom_info - inक्रमmation about a custom (SoC) घड़ी
 * @clk_ops: custom घड़ी operation callbacks
 */
काष्ठा ingenic_cgu_custom_info अणु
	स्थिर काष्ठा clk_ops *clk_ops;
पूर्ण;

/**
 * काष्ठा ingenic_cgu_clk_info - inक्रमmation about a घड़ी
 * @name: name of the घड़ी
 * @type: a biपंचांगask क्रमmed from CGU_CLK_* values
 * @parents: an array of the indices of potential parents of this घड़ी
 *           within the घड़ी_info array of the CGU, or -1 in entries
 *           which correspond to no valid parent
 * @pll: inक्रमmation valid अगर type includes CGU_CLK_PLL
 * @gate: inक्रमmation valid अगर type includes CGU_CLK_GATE
 * @mux: inक्रमmation valid अगर type includes CGU_CLK_MUX
 * @भाग: inक्रमmation valid अगर type includes CGU_CLK_DIV
 * @fixभाग: inक्रमmation valid अगर type includes CGU_CLK_FIXDIV
 * @custom: inक्रमmation valid अगर type includes CGU_CLK_CUSTOM
 */
काष्ठा ingenic_cgu_clk_info अणु
	स्थिर अक्षर *name;

	क्रमागत अणु
		CGU_CLK_NONE		= 0,
		CGU_CLK_EXT		= BIT(0),
		CGU_CLK_PLL		= BIT(1),
		CGU_CLK_GATE		= BIT(2),
		CGU_CLK_MUX		= BIT(3),
		CGU_CLK_MUX_GLITCHFREE	= BIT(4),
		CGU_CLK_DIV		= BIT(5),
		CGU_CLK_FIXDIV		= BIT(6),
		CGU_CLK_CUSTOM		= BIT(7),
	पूर्ण type;

	पूर्णांक parents[4];

	जोड़ अणु
		काष्ठा ingenic_cgu_pll_info pll;

		काष्ठा अणु
			काष्ठा ingenic_cgu_gate_info gate;
			काष्ठा ingenic_cgu_mux_info mux;
			काष्ठा ingenic_cgu_भाग_info भाग;
			काष्ठा ingenic_cgu_fixभाग_info fixभाग;
		पूर्ण;

		काष्ठा ingenic_cgu_custom_info custom;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा ingenic_cgu - data about the CGU
 * @np: the device tree node that caused the CGU to be probed
 * @base: the ioremap'ed base address of the CGU रेजिस्टरs
 * @घड़ी_info: an array containing inक्रमmation about implemented घड़ीs
 * @घड़ीs: used to provide घड़ीs to DT, allows lookup of काष्ठा clk*
 * @lock: lock to be held whilst manipulating CGU रेजिस्टरs
 */
काष्ठा ingenic_cgu अणु
	काष्ठा device_node *np;
	व्योम __iomem *base;

	स्थिर काष्ठा ingenic_cgu_clk_info *घड़ी_info;
	काष्ठा clk_onecell_data घड़ीs;

	spinlock_t lock;
पूर्ण;

/**
 * काष्ठा ingenic_clk - निजी data क्रम a घड़ी
 * @hw: see Documentation/driver-api/clk.rst
 * @cgu: a poपूर्णांकer to the CGU data
 * @idx: the index of this घड़ी in cgu->घड़ी_info
 */
काष्ठा ingenic_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा ingenic_cgu *cgu;
	अचिन्हित idx;
पूर्ण;

#घोषणा to_ingenic_clk(_hw) container_of(_hw, काष्ठा ingenic_clk, hw)

/**
 * ingenic_cgu_new() - create a new CGU instance
 * @घड़ी_info: an array of घड़ी inक्रमmation काष्ठाures describing the घड़ीs
 *              which are implemented by the CGU
 * @num_घड़ीs: the number of entries in घड़ी_info
 * @np: the device tree node which causes this CGU to be probed
 *
 * Return: a poपूर्णांकer to the CGU instance अगर initialisation is successful,
 *         otherwise शून्य.
 */
काष्ठा ingenic_cgu *
ingenic_cgu_new(स्थिर काष्ठा ingenic_cgu_clk_info *घड़ी_info,
		अचिन्हित num_घड़ीs, काष्ठा device_node *np);

/**
 * ingenic_cgu_रेजिस्टर_घड़ीs() - Registers the घड़ीs
 * @cgu: poपूर्णांकer to cgu data
 *
 * Register the घड़ीs described by the CGU with the common घड़ी framework.
 *
 * Return: 0 on success or -त्रुटि_सं अगर unsuccesful.
 */
पूर्णांक ingenic_cgu_रेजिस्टर_घड़ीs(काष्ठा ingenic_cgu *cgu);

#पूर्ण_अगर /* __DRIVERS_CLK_INGENIC_CGU_H__ */
