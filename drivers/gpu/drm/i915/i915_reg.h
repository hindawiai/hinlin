<शैली गुरु>
/* Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _I915_REG_H_
#घोषणा _I915_REG_H_

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>

/**
 * DOC: The i915 रेजिस्टर macro definition style guide
 *
 * Follow the style described here क्रम new macros, and जबतक changing existing
 * macros. Do **not** mass change existing definitions just to update the style.
 *
 * File Layout
 * ~~~~~~~~~~~
 *
 * Keep helper macros near the top. For example, _PIPE() and मित्रs.
 *
 * Prefix macros that generally should not be used outside of this file with
 * underscore '_'. For example, _PIPE() and मित्रs, single instances of
 * रेजिस्टरs that are defined solely क्रम the use by function-like macros.
 *
 * Aव्योम using the underscore prefixed macros outside of this file. There are
 * exceptions, but keep them to a minimum.
 *
 * There are two basic types of रेजिस्टर definitions: Single रेजिस्टरs and
 * रेजिस्टर groups. Register groups are रेजिस्टरs which have two or more
 * instances, क्रम example one per pipe, port, transcoder, etc. Register groups
 * should be defined using function-like macros.
 *
 * For single रेजिस्टरs, define the रेजिस्टर offset first, followed by रेजिस्टर
 * contents.
 *
 * For रेजिस्टर groups, define the रेजिस्टर instance offsets first, prefixed
 * with underscore, followed by a function-like macro choosing the right
 * instance based on the parameter, followed by रेजिस्टर contents.
 *
 * Define the रेजिस्टर contents (i.e. bit and bit field macros) from most
 * signअगरicant to least signअगरicant bit. Indent the रेजिस्टर content macros
 * using two extra spaces between ``#घोषणा`` and the macro name.
 *
 * Define bit fields using ``REG_GENMASK(h, l)``. Define bit field contents
 * using ``REG_FIELD_PREP(mask, value)``. This will define the values alपढ़ोy
 * shअगरted in place, so they can be directly OR'd together. For convenience,
 * function-like macros may be used to define bit fields, but करो note that the
 * macros may be needed to पढ़ो as well as ग_लिखो the रेजिस्टर contents.
 *
 * Define bits using ``REG_BIT(N)``. Do **not** add ``_BIT`` suffix to the name.
 *
 * Group the रेजिस्टर and its contents together without blank lines, separate
 * from other रेजिस्टरs and their contents with one blank line.
 *
 * Indent macro values from macro names using TABs. Align values vertically. Use
 * braces in macro values as needed to aव्योम unपूर्णांकended precedence after macro
 * substitution. Use spaces in macro values according to kernel coding
 * style. Use lower हाल in hexadecimal values.
 *
 * Naming
 * ~~~~~~
 *
 * Try to name रेजिस्टरs according to the specs. If the रेजिस्टर name changes in
 * the specs from platक्रमm to another, stick to the original name.
 *
 * Try to re-use existing रेजिस्टर macro definitions. Only add new macros क्रम
 * new रेजिस्टर offsets, or when the रेजिस्टर contents have changed enough to
 * warrant a full redefinition.
 *
 * When a रेजिस्टर macro changes क्रम a new platक्रमm, prefix the new macro using
 * the platक्रमm acronym or generation. For example, ``SKL_`` or ``GEN8_``. The
 * prefix signअगरies the start platक्रमm/generation using the रेजिस्टर.
 *
 * When a bit (field) macro changes or माला_लो added क्रम a new platक्रमm, जबतक
 * retaining the existing रेजिस्टर macro, add a platक्रमm acronym or generation
 * suffix to the name. For example, ``_SKL`` or ``_GEN8``.
 *
 * Examples
 * ~~~~~~~~
 *
 * (Note that the values in the example are indented using spaces instead of
 * TABs to aव्योम misalignment in generated करोcumentation. Use TABs in the
 * definitions.)::
 *
 *  #घोषणा _FOO_A                      0xf000
 *  #घोषणा _FOO_B                      0xf001
 *  #घोषणा FOO(pipe)                   _MMIO_PIPE(pipe, _FOO_A, _FOO_B)
 *  #घोषणा   FOO_ENABLE                REG_BIT(31)
 *  #घोषणा   FOO_MODE_MASK             REG_GENMASK(19, 16)
 *  #घोषणा   FOO_MODE_BAR              REG_FIELD_PREP(FOO_MODE_MASK, 0)
 *  #घोषणा   FOO_MODE_BAZ              REG_FIELD_PREP(FOO_MODE_MASK, 1)
 *  #घोषणा   FOO_MODE_QUX_SNB          REG_FIELD_PREP(FOO_MODE_MASK, 2)
 *
 *  #घोषणा BAR                         _MMIO(0xb000)
 *  #घोषणा GEN8_BAR                    _MMIO(0xb888)
 */

/**
 * REG_BIT() - Prepare a u32 bit value
 * @__n: 0-based bit number
 *
 * Local wrapper क्रम BIT() to क्रमce u32, with compile समय checks.
 *
 * @वापस: Value with bit @__n set.
 */
#घोषणा REG_BIT(__n)							\
	((u32)(BIT(__n) +						\
	       BUILD_BUG_ON_ZERO(__is_स्थिरexpr(__n) &&		\
				 ((__n) < 0 || (__n) > 31))))

/**
 * REG_GENMASK() - Prepare a continuous u32 biपंचांगask
 * @__high: 0-based high bit
 * @__low: 0-based low bit
 *
 * Local wrapper क्रम GENMASK() to क्रमce u32, with compile समय checks.
 *
 * @वापस: Continuous biपंचांगask from @__high to @__low, inclusive.
 */
#घोषणा REG_GENMASK(__high, __low)					\
	((u32)(GENMASK(__high, __low) +					\
	       BUILD_BUG_ON_ZERO(__is_स्थिरexpr(__high) &&	\
				 __is_स्थिरexpr(__low) &&		\
				 ((__low) < 0 || (__high) > 31 || (__low) > (__high)))))

/*
 * Local पूर्णांकeger स्थिरant expression version of is_घातer_of_2().
 */
#घोषणा IS_POWER_OF_2(__x)		((__x) && (((__x) & ((__x) - 1)) == 0))

/**
 * REG_FIELD_PREP() - Prepare a u32 bitfield value
 * @__mask: shअगरted mask defining the field's length and position
 * @__val: value to put in the field
 *
 * Local copy of FIELD_PREP() to generate an पूर्णांकeger स्थिरant expression, क्रमce
 * u32 and क्रम consistency with REG_FIELD_GET(), REG_BIT() and REG_GENMASK().
 *
 * @वापस: @__val masked and shअगरted पूर्णांकo the field defined by @__mask.
 */
#घोषणा REG_FIELD_PREP(__mask, __val)						\
	((u32)((((typeof(__mask))(__val) << __bf_shf(__mask)) & (__mask)) +	\
	       BUILD_BUG_ON_ZERO(!__is_स्थिरexpr(__mask)) +		\
	       BUILD_BUG_ON_ZERO((__mask) == 0 || (__mask) > U32_MAX) +		\
	       BUILD_BUG_ON_ZERO(!IS_POWER_OF_2((__mask) + (1ULL << __bf_shf(__mask)))) + \
	       BUILD_BUG_ON_ZERO(__builtin_choose_expr(__is_स्थिरexpr(__val), (~((__mask) >> __bf_shf(__mask)) & (__val)), 0))))

/**
 * REG_FIELD_GET() - Extract a u32 bitfield value
 * @__mask: shअगरted mask defining the field's length and position
 * @__val: value to extract the bitfield value from
 *
 * Local wrapper क्रम FIELD_GET() to क्रमce u32 and क्रम consistency with
 * REG_FIELD_PREP(), REG_BIT() and REG_GENMASK().
 *
 * @वापस: Masked and shअगरted value of the field defined by @__mask in @__val.
 */
#घोषणा REG_FIELD_GET(__mask, __val)	((u32)FIELD_GET(__mask, __val))

प्रकार काष्ठा अणु
	u32 reg;
पूर्ण i915_reg_t;

#घोषणा _MMIO(r) ((स्थिर i915_reg_t)अणु .reg = (r) पूर्ण)

#घोषणा INVALID_MMIO_REG _MMIO(0)

अटल __always_अंतरभूत u32 i915_mmio_reg_offset(i915_reg_t reg)
अणु
	वापस reg.reg;
पूर्ण

अटल अंतरभूत bool i915_mmio_reg_equal(i915_reg_t a, i915_reg_t b)
अणु
	वापस i915_mmio_reg_offset(a) == i915_mmio_reg_offset(b);
पूर्ण

अटल अंतरभूत bool i915_mmio_reg_valid(i915_reg_t reg)
अणु
	वापस !i915_mmio_reg_equal(reg, INVALID_MMIO_REG);
पूर्ण

#घोषणा VLV_DISPLAY_BASE		0x180000
#घोषणा VLV_MIPI_BASE			VLV_DISPLAY_BASE
#घोषणा BXT_MIPI_BASE			0x60000

#घोषणा DISPLAY_MMIO_BASE(dev_priv)	(INTEL_INFO(dev_priv)->display_mmio_offset)

/*
 * Given the first two numbers __a and __b of arbitrarily many evenly spaced
 * numbers, pick the 0-based __index'th value.
 *
 * Always prefer this over _PICK() अगर the numbers are evenly spaced.
 */
#घोषणा _PICK_EVEN(__index, __a, __b) ((__a) + (__index) * ((__b) - (__a)))

/*
 * Given the arbitrary numbers in varargs, pick the 0-based __index'th number.
 *
 * Always prefer _PICK_EVEN() over this अगर the numbers are evenly spaced.
 */
#घोषणा _PICK(__index, ...) (((स्थिर u32 [])अणु __VA_ARGS__ पूर्ण)[__index])

/*
 * Named helper wrappers around _PICK_EVEN() and _PICK().
 */
#घोषणा _PIPE(pipe, a, b)		_PICK_EVEN(pipe, a, b)
#घोषणा _PLANE(plane, a, b)		_PICK_EVEN(plane, a, b)
#घोषणा _TRANS(tran, a, b)		_PICK_EVEN(tran, a, b)
#घोषणा _PORT(port, a, b)		_PICK_EVEN(port, a, b)
#घोषणा _PLL(pll, a, b)			_PICK_EVEN(pll, a, b)
#घोषणा _PHY(phy, a, b)			_PICK_EVEN(phy, a, b)

#घोषणा _MMIO_PIPE(pipe, a, b)		_MMIO(_PIPE(pipe, a, b))
#घोषणा _MMIO_PLANE(plane, a, b)	_MMIO(_PLANE(plane, a, b))
#घोषणा _MMIO_TRANS(tran, a, b)		_MMIO(_TRANS(tran, a, b))
#घोषणा _MMIO_PORT(port, a, b)		_MMIO(_PORT(port, a, b))
#घोषणा _MMIO_PLL(pll, a, b)		_MMIO(_PLL(pll, a, b))
#घोषणा _MMIO_PHY(phy, a, b)		_MMIO(_PHY(phy, a, b))

#घोषणा _PHY3(phy, ...)			_PICK(phy, __VA_ARGS__)

#घोषणा _MMIO_PIPE3(pipe, a, b, c)	_MMIO(_PICK(pipe, a, b, c))
#घोषणा _MMIO_PORT3(pipe, a, b, c)	_MMIO(_PICK(pipe, a, b, c))
#घोषणा _MMIO_PHY3(phy, a, b, c)	_MMIO(_PHY3(phy, a, b, c))
#घोषणा _MMIO_PLL3(pll, ...)		_MMIO(_PICK(pll, __VA_ARGS__))


/*
 * Device info offset array based helpers क्रम groups of रेजिस्टरs with unevenly
 * spaced base offsets.
 */
#घोषणा _MMIO_PIPE2(pipe, reg)		_MMIO(INTEL_INFO(dev_priv)->pipe_offsets[pipe] - \
					      INTEL_INFO(dev_priv)->pipe_offsets[PIPE_A] + (reg) + \
					      DISPLAY_MMIO_BASE(dev_priv))
#घोषणा _TRANS2(tran, reg)		(INTEL_INFO(dev_priv)->trans_offsets[(tran)] - \
					 INTEL_INFO(dev_priv)->trans_offsets[TRANSCODER_A] + (reg) + \
					 DISPLAY_MMIO_BASE(dev_priv))
#घोषणा _MMIO_TRANS2(tran, reg)		_MMIO(_TRANS2(tran, reg))
#घोषणा _CURSOR2(pipe, reg)		_MMIO(INTEL_INFO(dev_priv)->cursor_offsets[(pipe)] - \
					      INTEL_INFO(dev_priv)->cursor_offsets[PIPE_A] + (reg) + \
					      DISPLAY_MMIO_BASE(dev_priv))

#घोषणा __MASKED_FIELD(mask, value) ((mask) << 16 | (value))
#घोषणा _MASKED_FIELD(mask, value) (अणु					   \
	अगर (__builtin_स्थिरant_p(mask))					   \
		BUILD_BUG_ON_MSG(((mask) & 0xffff0000), "Incorrect mask"); \
	अगर (__builtin_स्थिरant_p(value))				   \
		BUILD_BUG_ON_MSG((value) & 0xffff0000, "Incorrect value"); \
	अगर (__builtin_स्थिरant_p(mask) && __builtin_स्थिरant_p(value))	   \
		BUILD_BUG_ON_MSG((value) & ~(mask),			   \
				 "Incorrect value for mask");		   \
	__MASKED_FIELD(mask, value); पूर्ण)
#घोषणा _MASKED_BIT_ENABLE(a)	(अणु typeof(a) _a = (a); _MASKED_FIELD(_a, _a); पूर्ण)
#घोषणा _MASKED_BIT_DISABLE(a)	(_MASKED_FIELD((a), 0))

/* PCI config space */

#घोषणा MCHBAR_I915 0x44
#घोषणा MCHBAR_I965 0x48
#घोषणा MCHBAR_SIZE (4 * 4096)

#घोषणा DEVEN 0x54
#घोषणा   DEVEN_MCHBAR_EN (1 << 28)

/* BSM in include/drm/i915_drm.h */

#घोषणा HPLLCC	0xc0 /* 85x only */
#घोषणा   GC_CLOCK_CONTROL_MASK		(0x7 << 0)
#घोषणा   GC_CLOCK_133_200		(0 << 0)
#घोषणा   GC_CLOCK_100_200		(1 << 0)
#घोषणा   GC_CLOCK_100_133		(2 << 0)
#घोषणा   GC_CLOCK_133_266		(3 << 0)
#घोषणा   GC_CLOCK_133_200_2		(4 << 0)
#घोषणा   GC_CLOCK_133_266_2		(5 << 0)
#घोषणा   GC_CLOCK_166_266		(6 << 0)
#घोषणा   GC_CLOCK_166_250		(7 << 0)

#घोषणा I915_GDRST 0xc0 /* PCI config रेजिस्टर */
#घोषणा   GRDOM_FULL		(0 << 2)
#घोषणा   GRDOM_RENDER		(1 << 2)
#घोषणा   GRDOM_MEDIA		(3 << 2)
#घोषणा   GRDOM_MASK		(3 << 2)
#घोषणा   GRDOM_RESET_STATUS	(1 << 1)
#घोषणा   GRDOM_RESET_ENABLE	(1 << 0)

/* BSpec only has रेजिस्टर offset, PCI device and bit found empirically */
#घोषणा I830_CLOCK_GATE	0xc8 /* device 0 */
#घोषणा   I830_L2_CACHE_CLOCK_GATE_DISABLE	(1 << 2)

#घोषणा GCDGMBUS 0xcc

#घोषणा GCFGC2	0xda
#घोषणा GCFGC	0xf0 /* 915+ only */
#घोषणा   GC_LOW_FREQUENCY_ENABLE	(1 << 7)
#घोषणा   GC_DISPLAY_CLOCK_190_200_MHZ	(0 << 4)
#घोषणा   GC_DISPLAY_CLOCK_333_320_MHZ	(4 << 4)
#घोषणा   GC_DISPLAY_CLOCK_267_MHZ_PNV	(0 << 4)
#घोषणा   GC_DISPLAY_CLOCK_333_MHZ_PNV	(1 << 4)
#घोषणा   GC_DISPLAY_CLOCK_444_MHZ_PNV	(2 << 4)
#घोषणा   GC_DISPLAY_CLOCK_200_MHZ_PNV	(5 << 4)
#घोषणा   GC_DISPLAY_CLOCK_133_MHZ_PNV	(6 << 4)
#घोषणा   GC_DISPLAY_CLOCK_167_MHZ_PNV	(7 << 4)
#घोषणा   GC_DISPLAY_CLOCK_MASK		(7 << 4)
#घोषणा   GM45_GC_RENDER_CLOCK_MASK	(0xf << 0)
#घोषणा   GM45_GC_RENDER_CLOCK_266_MHZ	(8 << 0)
#घोषणा   GM45_GC_RENDER_CLOCK_320_MHZ	(9 << 0)
#घोषणा   GM45_GC_RENDER_CLOCK_400_MHZ	(0xb << 0)
#घोषणा   GM45_GC_RENDER_CLOCK_533_MHZ	(0xc << 0)
#घोषणा   I965_GC_RENDER_CLOCK_MASK	(0xf << 0)
#घोषणा   I965_GC_RENDER_CLOCK_267_MHZ	(2 << 0)
#घोषणा   I965_GC_RENDER_CLOCK_333_MHZ	(3 << 0)
#घोषणा   I965_GC_RENDER_CLOCK_444_MHZ	(4 << 0)
#घोषणा   I965_GC_RENDER_CLOCK_533_MHZ	(5 << 0)
#घोषणा   I945_GC_RENDER_CLOCK_MASK	(7 << 0)
#घोषणा   I945_GC_RENDER_CLOCK_166_MHZ	(0 << 0)
#घोषणा   I945_GC_RENDER_CLOCK_200_MHZ	(1 << 0)
#घोषणा   I945_GC_RENDER_CLOCK_250_MHZ	(3 << 0)
#घोषणा   I945_GC_RENDER_CLOCK_400_MHZ	(5 << 0)
#घोषणा   I915_GC_RENDER_CLOCK_MASK	(7 << 0)
#घोषणा   I915_GC_RENDER_CLOCK_166_MHZ	(0 << 0)
#घोषणा   I915_GC_RENDER_CLOCK_200_MHZ	(1 << 0)
#घोषणा   I915_GC_RENDER_CLOCK_333_MHZ	(4 << 0)

#घोषणा ASLE	0xe4
#घोषणा ASLS	0xfc

#घोषणा SWSCI	0xe8
#घोषणा   SWSCI_SCISEL	(1 << 15)
#घोषणा   SWSCI_GSSCIE	(1 << 0)

#घोषणा LBPC 0xf4 /* legacy/combination backlight modes, also called LBB */


#घोषणा ILK_GDSR _MMIO(MCHBAR_MIRROR_BASE + 0x2ca4)
#घोषणा  ILK_GRDOM_FULL		(0 << 1)
#घोषणा  ILK_GRDOM_RENDER	(1 << 1)
#घोषणा  ILK_GRDOM_MEDIA	(3 << 1)
#घोषणा  ILK_GRDOM_MASK		(3 << 1)
#घोषणा  ILK_GRDOM_RESET_ENABLE (1 << 0)

#घोषणा GEN6_MBCUNIT_SNPCR	_MMIO(0x900c) /* क्रम LLC config */
#घोषणा   GEN6_MBC_SNPCR_SHIFT	21
#घोषणा   GEN6_MBC_SNPCR_MASK	(3 << 21)
#घोषणा   GEN6_MBC_SNPCR_MAX	(0 << 21)
#घोषणा   GEN6_MBC_SNPCR_MED	(1 << 21)
#घोषणा   GEN6_MBC_SNPCR_LOW	(2 << 21)
#घोषणा   GEN6_MBC_SNPCR_MIN	(3 << 21) /* only 1/16th of the cache is shared */

#घोषणा VLV_G3DCTL		_MMIO(0x9024)
#घोषणा VLV_GSCKGCTL		_MMIO(0x9028)

#घोषणा GEN6_MBCTL		_MMIO(0x0907c)
#घोषणा   GEN6_MBCTL_ENABLE_BOOT_FETCH	(1 << 4)
#घोषणा   GEN6_MBCTL_CTX_FETCH_NEEDED	(1 << 3)
#घोषणा   GEN6_MBCTL_BME_UPDATE_ENABLE	(1 << 2)
#घोषणा   GEN6_MBCTL_MAE_UPDATE_ENABLE	(1 << 1)
#घोषणा   GEN6_MBCTL_BOOT_FETCH_MECH	(1 << 0)

#घोषणा GEN6_GDRST	_MMIO(0x941c)
#घोषणा  GEN6_GRDOM_FULL		(1 << 0)
#घोषणा  GEN6_GRDOM_RENDER		(1 << 1)
#घोषणा  GEN6_GRDOM_MEDIA		(1 << 2)
#घोषणा  GEN6_GRDOM_BLT			(1 << 3)
#घोषणा  GEN6_GRDOM_VECS		(1 << 4)
#घोषणा  GEN9_GRDOM_GUC			(1 << 5)
#घोषणा  GEN8_GRDOM_MEDIA2		(1 << 7)
/* GEN11 changed all bit defs except क्रम FULL & RENDER */
#घोषणा  GEN11_GRDOM_FULL		GEN6_GRDOM_FULL
#घोषणा  GEN11_GRDOM_RENDER		GEN6_GRDOM_RENDER
#घोषणा  GEN11_GRDOM_BLT		(1 << 2)
#घोषणा  GEN11_GRDOM_GUC		(1 << 3)
#घोषणा  GEN11_GRDOM_MEDIA		(1 << 5)
#घोषणा  GEN11_GRDOM_MEDIA2		(1 << 6)
#घोषणा  GEN11_GRDOM_MEDIA3		(1 << 7)
#घोषणा  GEN11_GRDOM_MEDIA4		(1 << 8)
#घोषणा  GEN11_GRDOM_VECS		(1 << 13)
#घोषणा  GEN11_GRDOM_VECS2		(1 << 14)
#घोषणा  GEN11_GRDOM_SFC0		(1 << 17)
#घोषणा  GEN11_GRDOM_SFC1		(1 << 18)

#घोषणा  GEN11_VCS_SFC_RESET_BIT(instance)	(GEN11_GRDOM_SFC0 << ((instance) >> 1))
#घोषणा  GEN11_VECS_SFC_RESET_BIT(instance)	(GEN11_GRDOM_SFC0 << (instance))

#घोषणा GEN11_VCS_SFC_FORCED_LOCK(engine)	_MMIO((engine)->mmio_base + 0x88C)
#घोषणा   GEN11_VCS_SFC_FORCED_LOCK_BIT		(1 << 0)
#घोषणा GEN11_VCS_SFC_LOCK_STATUS(engine)	_MMIO((engine)->mmio_base + 0x890)
#घोषणा   GEN11_VCS_SFC_USAGE_BIT		(1 << 0)
#घोषणा   GEN11_VCS_SFC_LOCK_ACK_BIT		(1 << 1)

#घोषणा GEN11_VECS_SFC_FORCED_LOCK(engine)	_MMIO((engine)->mmio_base + 0x201C)
#घोषणा   GEN11_VECS_SFC_FORCED_LOCK_BIT	(1 << 0)
#घोषणा GEN11_VECS_SFC_LOCK_ACK(engine)		_MMIO((engine)->mmio_base + 0x2018)
#घोषणा   GEN11_VECS_SFC_LOCK_ACK_BIT		(1 << 0)
#घोषणा GEN11_VECS_SFC_USAGE(engine)		_MMIO((engine)->mmio_base + 0x2014)
#घोषणा   GEN11_VECS_SFC_USAGE_BIT		(1 << 0)

#घोषणा GEN12_SFC_DONE(n)		_MMIO(0x1cc00 + (n) * 0x100)
#घोषणा GEN12_SFC_DONE_MAX		4

#घोषणा RING_PP_सूची_BASE(base)		_MMIO((base) + 0x228)
#घोषणा RING_PP_सूची_BASE_READ(base)	_MMIO((base) + 0x518)
#घोषणा RING_PP_सूची_DCLV(base)		_MMIO((base) + 0x220)
#घोषणा   PP_सूची_DCLV_2G		0xffffffff

#घोषणा GEN8_RING_PDP_UDW(base, n)	_MMIO((base) + 0x270 + (n) * 8 + 4)
#घोषणा GEN8_RING_PDP_LDW(base, n)	_MMIO((base) + 0x270 + (n) * 8)

#घोषणा GEN8_R_PWR_CLK_STATE		_MMIO(0x20C8)
#घोषणा   GEN8_RPCS_ENABLE		(1 << 31)
#घोषणा   GEN8_RPCS_S_CNT_ENABLE	(1 << 18)
#घोषणा   GEN8_RPCS_S_CNT_SHIFT		15
#घोषणा   GEN8_RPCS_S_CNT_MASK		(0x7 << GEN8_RPCS_S_CNT_SHIFT)
#घोषणा   GEN11_RPCS_S_CNT_SHIFT	12
#घोषणा   GEN11_RPCS_S_CNT_MASK		(0x3f << GEN11_RPCS_S_CNT_SHIFT)
#घोषणा   GEN8_RPCS_SS_CNT_ENABLE	(1 << 11)
#घोषणा   GEN8_RPCS_SS_CNT_SHIFT	8
#घोषणा   GEN8_RPCS_SS_CNT_MASK		(0x7 << GEN8_RPCS_SS_CNT_SHIFT)
#घोषणा   GEN8_RPCS_EU_MAX_SHIFT	4
#घोषणा   GEN8_RPCS_EU_MAX_MASK		(0xf << GEN8_RPCS_EU_MAX_SHIFT)
#घोषणा   GEN8_RPCS_EU_MIN_SHIFT	0
#घोषणा   GEN8_RPCS_EU_MIN_MASK		(0xf << GEN8_RPCS_EU_MIN_SHIFT)

#घोषणा WAIT_FOR_RC6_EXIT		_MMIO(0x20CC)
/* HSW only */
#घोषणा   HSW_SELECTIVE_READ_ADDRESSING_SHIFT		2
#घोषणा   HSW_SELECTIVE_READ_ADDRESSING_MASK		(0x3 << HSW_SLECTIVE_READ_ADDRESSING_SHIFT)
#घोषणा   HSW_SELECTIVE_WRITE_ADDRESS_SHIFT		4
#घोषणा   HSW_SELECTIVE_WRITE_ADDRESS_MASK		(0x7 << HSW_SELECTIVE_WRITE_ADDRESS_SHIFT)
/* HSW+ */
#घोषणा   HSW_WAIT_FOR_RC6_EXIT_ENABLE			(1 << 0)
#घोषणा   HSW_RCS_CONTEXT_ENABLE			(1 << 7)
#घोषणा   HSW_RCS_INHIBIT				(1 << 8)
/* Gen8 */
#घोषणा   GEN8_SELECTIVE_WRITE_ADDRESS_SHIFT		4
#घोषणा   GEN8_SELECTIVE_WRITE_ADDRESS_MASK		(0x3 << GEN8_SELECTIVE_WRITE_ADDRESS_SHIFT)
#घोषणा   GEN8_SELECTIVE_WRITE_ADDRESS_SHIFT		4
#घोषणा   GEN8_SELECTIVE_WRITE_ADDRESS_MASK		(0x3 << GEN8_SELECTIVE_WRITE_ADDRESS_SHIFT)
#घोषणा   GEN8_SELECTIVE_WRITE_ADDRESSING_ENABLE	(1 << 6)
#घोषणा   GEN8_SELECTIVE_READ_SUBSLICE_SELECT_SHIFT	9
#घोषणा   GEN8_SELECTIVE_READ_SUBSLICE_SELECT_MASK	(0x3 << GEN8_SELECTIVE_READ_SUBSLICE_SELECT_SHIFT)
#घोषणा   GEN8_SELECTIVE_READ_SLICE_SELECT_SHIFT	11
#घोषणा   GEN8_SELECTIVE_READ_SLICE_SELECT_MASK		(0x3 << GEN8_SELECTIVE_READ_SLICE_SELECT_SHIFT)
#घोषणा   GEN8_SELECTIVE_READ_ADDRESSING_ENABLE         (1 << 13)

#घोषणा GAM_ECOCHK			_MMIO(0x4090)
#घोषणा   BDW_DISABLE_HDC_INVALIDATION	(1 << 25)
#घोषणा   ECOCHK_SNB_BIT		(1 << 10)
#घोषणा   ECOCHK_DIS_TLB		(1 << 8)
#घोषणा   HSW_ECOCHK_ARB_PRIO_SOL	(1 << 6)
#घोषणा   ECOCHK_PPGTT_CACHE64B		(0x3 << 3)
#घोषणा   ECOCHK_PPGTT_CACHE4B		(0x0 << 3)
#घोषणा   ECOCHK_PPGTT_GFDT_IVB		(0x1 << 4)
#घोषणा   ECOCHK_PPGTT_LLC_IVB		(0x1 << 3)
#घोषणा   ECOCHK_PPGTT_UC_HSW		(0x1 << 3)
#घोषणा   ECOCHK_PPGTT_WT_HSW		(0x2 << 3)
#घोषणा   ECOCHK_PPGTT_WB_HSW		(0x3 << 3)

#घोषणा GEN8_RC6_CTX_INFO		_MMIO(0x8504)

#घोषणा GAC_ECO_BITS			_MMIO(0x14090)
#घोषणा   ECOBITS_SNB_BIT		(1 << 13)
#घोषणा   ECOBITS_PPGTT_CACHE64B	(3 << 8)
#घोषणा   ECOBITS_PPGTT_CACHE4B		(0 << 8)

#घोषणा GAB_CTL				_MMIO(0x24000)
#घोषणा   GAB_CTL_CONT_AFTER_PAGEFAULT	(1 << 8)

#घोषणा GEN6_STOLEN_RESERVED		_MMIO(0x1082C0)
#घोषणा GEN6_STOLEN_RESERVED_ADDR_MASK	(0xFFF << 20)
#घोषणा GEN7_STOLEN_RESERVED_ADDR_MASK	(0x3FFF << 18)
#घोषणा GEN6_STOLEN_RESERVED_SIZE_MASK	(3 << 4)
#घोषणा GEN6_STOLEN_RESERVED_1M		(0 << 4)
#घोषणा GEN6_STOLEN_RESERVED_512K	(1 << 4)
#घोषणा GEN6_STOLEN_RESERVED_256K	(2 << 4)
#घोषणा GEN6_STOLEN_RESERVED_128K	(3 << 4)
#घोषणा GEN7_STOLEN_RESERVED_SIZE_MASK	(1 << 5)
#घोषणा GEN7_STOLEN_RESERVED_1M		(0 << 5)
#घोषणा GEN7_STOLEN_RESERVED_256K	(1 << 5)
#घोषणा GEN8_STOLEN_RESERVED_SIZE_MASK	(3 << 7)
#घोषणा GEN8_STOLEN_RESERVED_1M		(0 << 7)
#घोषणा GEN8_STOLEN_RESERVED_2M		(1 << 7)
#घोषणा GEN8_STOLEN_RESERVED_4M		(2 << 7)
#घोषणा GEN8_STOLEN_RESERVED_8M		(3 << 7)
#घोषणा GEN6_STOLEN_RESERVED_ENABLE	(1 << 0)
#घोषणा GEN11_STOLEN_RESERVED_ADDR_MASK	(0xFFFFFFFFFFFULL << 20)

/* VGA stuff */

#घोषणा VGA_ST01_MDA 0x3ba
#घोषणा VGA_ST01_CGA 0x3da

#घोषणा _VGA_MSR_WRITE _MMIO(0x3c2)
#घोषणा VGA_MSR_WRITE 0x3c2
#घोषणा VGA_MSR_READ 0x3cc
#घोषणा   VGA_MSR_MEM_EN (1 << 1)
#घोषणा   VGA_MSR_CGA_MODE (1 << 0)

#घोषणा VGA_SR_INDEX 0x3c4
#घोषणा SR01			1
#घोषणा VGA_SR_DATA 0x3c5

#घोषणा VGA_AR_INDEX 0x3c0
#घोषणा   VGA_AR_VID_EN (1 << 5)
#घोषणा VGA_AR_DATA_WRITE 0x3c0
#घोषणा VGA_AR_DATA_READ 0x3c1

#घोषणा VGA_GR_INDEX 0x3ce
#घोषणा VGA_GR_DATA 0x3cf
/* GR05 */
#घोषणा   VGA_GR_MEM_READ_MODE_SHIFT 3
#घोषणा     VGA_GR_MEM_READ_MODE_PLANE 1
/* GR06 */
#घोषणा   VGA_GR_MEM_MODE_MASK 0xc
#घोषणा   VGA_GR_MEM_MODE_SHIFT 2
#घोषणा   VGA_GR_MEM_A0000_AFFFF 0
#घोषणा   VGA_GR_MEM_A0000_BFFFF 1
#घोषणा   VGA_GR_MEM_B0000_B7FFF 2
#घोषणा   VGA_GR_MEM_B0000_BFFFF 3

#घोषणा VGA_DACMASK 0x3c6
#घोषणा VGA_DACRX 0x3c7
#घोषणा VGA_DACWX 0x3c8
#घोषणा VGA_DACDATA 0x3c9

#घोषणा VGA_CR_INDEX_MDA 0x3b4
#घोषणा VGA_CR_DATA_MDA 0x3b5
#घोषणा VGA_CR_INDEX_CGA 0x3d4
#घोषणा VGA_CR_DATA_CGA 0x3d5

#घोषणा MI_PREDICATE_SRC0	_MMIO(0x2400)
#घोषणा MI_PREDICATE_SRC0_UDW	_MMIO(0x2400 + 4)
#घोषणा MI_PREDICATE_SRC1	_MMIO(0x2408)
#घोषणा MI_PREDICATE_SRC1_UDW	_MMIO(0x2408 + 4)
#घोषणा MI_PREDICATE_DATA       _MMIO(0x2410)
#घोषणा MI_PREDICATE_RESULT     _MMIO(0x2418)
#घोषणा MI_PREDICATE_RESULT_1   _MMIO(0x241c)
#घोषणा MI_PREDICATE_RESULT_2	_MMIO(0x2214)
#घोषणा  LOWER_SLICE_ENABLED	(1 << 0)
#घोषणा  LOWER_SLICE_DISABLED	(0 << 0)

/*
 * Registers used only by the command parser
 */
#घोषणा BCS_SWCTRL _MMIO(0x22200)
#घोषणा   BCS_SRC_Y REG_BIT(0)
#घोषणा   BCS_DST_Y REG_BIT(1)

/* There are 16 GPR रेजिस्टरs */
#घोषणा BCS_GPR(n)	_MMIO(0x22600 + (n) * 8)
#घोषणा BCS_GPR_UDW(n)	_MMIO(0x22600 + (n) * 8 + 4)

#घोषणा GPGPU_THREADS_DISPATCHED        _MMIO(0x2290)
#घोषणा GPGPU_THREADS_DISPATCHED_UDW	_MMIO(0x2290 + 4)
#घोषणा HS_INVOCATION_COUNT             _MMIO(0x2300)
#घोषणा HS_INVOCATION_COUNT_UDW		_MMIO(0x2300 + 4)
#घोषणा DS_INVOCATION_COUNT             _MMIO(0x2308)
#घोषणा DS_INVOCATION_COUNT_UDW		_MMIO(0x2308 + 4)
#घोषणा IA_VERTICES_COUNT               _MMIO(0x2310)
#घोषणा IA_VERTICES_COUNT_UDW		_MMIO(0x2310 + 4)
#घोषणा IA_PRIMITIVES_COUNT             _MMIO(0x2318)
#घोषणा IA_PRIMITIVES_COUNT_UDW		_MMIO(0x2318 + 4)
#घोषणा VS_INVOCATION_COUNT             _MMIO(0x2320)
#घोषणा VS_INVOCATION_COUNT_UDW		_MMIO(0x2320 + 4)
#घोषणा GS_INVOCATION_COUNT             _MMIO(0x2328)
#घोषणा GS_INVOCATION_COUNT_UDW		_MMIO(0x2328 + 4)
#घोषणा GS_PRIMITIVES_COUNT             _MMIO(0x2330)
#घोषणा GS_PRIMITIVES_COUNT_UDW		_MMIO(0x2330 + 4)
#घोषणा CL_INVOCATION_COUNT             _MMIO(0x2338)
#घोषणा CL_INVOCATION_COUNT_UDW		_MMIO(0x2338 + 4)
#घोषणा CL_PRIMITIVES_COUNT             _MMIO(0x2340)
#घोषणा CL_PRIMITIVES_COUNT_UDW		_MMIO(0x2340 + 4)
#घोषणा PS_INVOCATION_COUNT             _MMIO(0x2348)
#घोषणा PS_INVOCATION_COUNT_UDW		_MMIO(0x2348 + 4)
#घोषणा PS_DEPTH_COUNT                  _MMIO(0x2350)
#घोषणा PS_DEPTH_COUNT_UDW		_MMIO(0x2350 + 4)

/* There are the 4 64-bit counter रेजिस्टरs, one क्रम each stream output */
#घोषणा GEN7_SO_NUM_PRIMS_WRITTEN(n)		_MMIO(0x5200 + (n) * 8)
#घोषणा GEN7_SO_NUM_PRIMS_WRITTEN_UDW(n)	_MMIO(0x5200 + (n) * 8 + 4)

#घोषणा GEN7_SO_PRIM_STORAGE_NEEDED(n)		_MMIO(0x5240 + (n) * 8)
#घोषणा GEN7_SO_PRIM_STORAGE_NEEDED_UDW(n)	_MMIO(0x5240 + (n) * 8 + 4)

#घोषणा GEN7_3DPRIM_END_OFFSET          _MMIO(0x2420)
#घोषणा GEN7_3DPRIM_START_VERTEX        _MMIO(0x2430)
#घोषणा GEN7_3DPRIM_VERTEX_COUNT        _MMIO(0x2434)
#घोषणा GEN7_3DPRIM_INSTANCE_COUNT      _MMIO(0x2438)
#घोषणा GEN7_3DPRIM_START_INSTANCE      _MMIO(0x243C)
#घोषणा GEN7_3DPRIM_BASE_VERTEX         _MMIO(0x2440)

#घोषणा GEN7_GPGPU_DISPATCHDIMX         _MMIO(0x2500)
#घोषणा GEN7_GPGPU_DISPATCHDIMY         _MMIO(0x2504)
#घोषणा GEN7_GPGPU_DISPATCHDIMZ         _MMIO(0x2508)

/* There are the 16 64-bit CS General Purpose Registers */
#घोषणा HSW_CS_GPR(n)                   _MMIO(0x2600 + (n) * 8)
#घोषणा HSW_CS_GPR_UDW(n)               _MMIO(0x2600 + (n) * 8 + 4)

#घोषणा GEN7_OACONTROL _MMIO(0x2360)
#घोषणा  GEN7_OACONTROL_CTX_MASK	    0xFFFFF000
#घोषणा  GEN7_OACONTROL_TIMER_PERIOD_MASK   0x3F
#घोषणा  GEN7_OACONTROL_TIMER_PERIOD_SHIFT  6
#घोषणा  GEN7_OACONTROL_TIMER_ENABLE	    (1 << 5)
#घोषणा  GEN7_OACONTROL_FORMAT_A13	    (0 << 2)
#घोषणा  GEN7_OACONTROL_FORMAT_A29	    (1 << 2)
#घोषणा  GEN7_OACONTROL_FORMAT_A13_B8_C8    (2 << 2)
#घोषणा  GEN7_OACONTROL_FORMAT_A29_B8_C8    (3 << 2)
#घोषणा  GEN7_OACONTROL_FORMAT_B4_C8	    (4 << 2)
#घोषणा  GEN7_OACONTROL_FORMAT_A45_B8_C8    (5 << 2)
#घोषणा  GEN7_OACONTROL_FORMAT_B4_C8_A16    (6 << 2)
#घोषणा  GEN7_OACONTROL_FORMAT_C4_B8	    (7 << 2)
#घोषणा  GEN7_OACONTROL_FORMAT_SHIFT	    2
#घोषणा  GEN7_OACONTROL_PER_CTX_ENABLE	    (1 << 1)
#घोषणा  GEN7_OACONTROL_ENABLE		    (1 << 0)

#घोषणा GEN8_OACTXID _MMIO(0x2364)

#घोषणा GEN8_OA_DEBUG _MMIO(0x2B04)
#घोषणा  GEN9_OA_DEBUG_DISABLE_CLK_RATIO_REPORTS    (1 << 5)
#घोषणा  GEN9_OA_DEBUG_INCLUDE_CLK_RATIO	    (1 << 6)
#घोषणा  GEN9_OA_DEBUG_DISABLE_GO_1_0_REPORTS	    (1 << 2)
#घोषणा  GEN9_OA_DEBUG_DISABLE_CTX_SWITCH_REPORTS   (1 << 1)

#घोषणा GEN8_OACONTROL _MMIO(0x2B00)
#घोषणा  GEN8_OA_REPORT_FORMAT_A12	    (0 << 2)
#घोषणा  GEN8_OA_REPORT_FORMAT_A12_B8_C8    (2 << 2)
#घोषणा  GEN8_OA_REPORT_FORMAT_A36_B8_C8    (5 << 2)
#घोषणा  GEN8_OA_REPORT_FORMAT_C4_B8	    (7 << 2)
#घोषणा  GEN8_OA_REPORT_FORMAT_SHIFT	    2
#घोषणा  GEN8_OA_SPECIFIC_CONTEXT_ENABLE    (1 << 1)
#घोषणा  GEN8_OA_COUNTER_ENABLE             (1 << 0)

#घोषणा GEN8_OACTXCONTROL _MMIO(0x2360)
#घोषणा  GEN8_OA_TIMER_PERIOD_MASK	    0x3F
#घोषणा  GEN8_OA_TIMER_PERIOD_SHIFT	    2
#घोषणा  GEN8_OA_TIMER_ENABLE		    (1 << 1)
#घोषणा  GEN8_OA_COUNTER_RESUME		    (1 << 0)

#घोषणा GEN7_OABUFFER _MMIO(0x23B0) /* R/W */
#घोषणा  GEN7_OABUFFER_OVERRUN_DISABLE	    (1 << 3)
#घोषणा  GEN7_OABUFFER_EDGE_TRIGGER	    (1 << 2)
#घोषणा  GEN7_OABUFFER_STOP_RESUME_ENABLE   (1 << 1)
#घोषणा  GEN7_OABUFFER_RESUME		    (1 << 0)

#घोषणा GEN8_OABUFFER_UDW _MMIO(0x23b4)
#घोषणा GEN8_OABUFFER _MMIO(0x2b14)
#घोषणा  GEN8_OABUFFER_MEM_SELECT_GGTT      (1 << 0)  /* 0: PPGTT, 1: GGTT */

#घोषणा GEN7_OASTATUS1 _MMIO(0x2364)
#घोषणा  GEN7_OASTATUS1_TAIL_MASK	    0xffffffc0
#घोषणा  GEN7_OASTATUS1_COUNTER_OVERFLOW    (1 << 2)
#घोषणा  GEN7_OASTATUS1_OABUFFER_OVERFLOW   (1 << 1)
#घोषणा  GEN7_OASTATUS1_REPORT_LOST	    (1 << 0)

#घोषणा GEN7_OASTATUS2 _MMIO(0x2368)
#घोषणा  GEN7_OASTATUS2_HEAD_MASK           0xffffffc0
#घोषणा  GEN7_OASTATUS2_MEM_SELECT_GGTT     (1 << 0) /* 0: PPGTT, 1: GGTT */

#घोषणा GEN8_OASTATUS _MMIO(0x2b08)
#घोषणा  GEN8_OASTATUS_TAIL_POINTER_WRAP    (1 << 17)
#घोषणा  GEN8_OASTATUS_HEAD_POINTER_WRAP    (1 << 16)
#घोषणा  GEN8_OASTATUS_OVERRUN_STATUS	    (1 << 3)
#घोषणा  GEN8_OASTATUS_COUNTER_OVERFLOW     (1 << 2)
#घोषणा  GEN8_OASTATUS_OABUFFER_OVERFLOW    (1 << 1)
#घोषणा  GEN8_OASTATUS_REPORT_LOST	    (1 << 0)

#घोषणा GEN8_OAHEADPTR _MMIO(0x2B0C)
#घोषणा GEN8_OAHEADPTR_MASK    0xffffffc0
#घोषणा GEN8_OATAILPTR _MMIO(0x2B10)
#घोषणा GEN8_OATAILPTR_MASK    0xffffffc0

#घोषणा OABUFFER_SIZE_128K  (0 << 3)
#घोषणा OABUFFER_SIZE_256K  (1 << 3)
#घोषणा OABUFFER_SIZE_512K  (2 << 3)
#घोषणा OABUFFER_SIZE_1M    (3 << 3)
#घोषणा OABUFFER_SIZE_2M    (4 << 3)
#घोषणा OABUFFER_SIZE_4M    (5 << 3)
#घोषणा OABUFFER_SIZE_8M    (6 << 3)
#घोषणा OABUFFER_SIZE_16M   (7 << 3)

#घोषणा GEN12_OA_TLB_INV_CR _MMIO(0xceec)

/* Gen12 OAR unit */
#घोषणा GEN12_OAR_OACONTROL _MMIO(0x2960)
#घोषणा  GEN12_OAR_OACONTROL_COUNTER_FORMAT_SHIFT 1
#घोषणा  GEN12_OAR_OACONTROL_COUNTER_ENABLE       (1 << 0)

#घोषणा GEN12_OACTXCONTROL _MMIO(0x2360)
#घोषणा GEN12_OAR_OASTATUS _MMIO(0x2968)

/* Gen12 OAG unit */
#घोषणा GEN12_OAG_OAHEADPTR _MMIO(0xdb00)
#घोषणा  GEN12_OAG_OAHEADPTR_MASK 0xffffffc0
#घोषणा GEN12_OAG_OATAILPTR _MMIO(0xdb04)
#घोषणा  GEN12_OAG_OATAILPTR_MASK 0xffffffc0

#घोषणा GEN12_OAG_OABUFFER  _MMIO(0xdb08)
#घोषणा  GEN12_OAG_OABUFFER_BUFFER_SIZE_MASK  (0x7)
#घोषणा  GEN12_OAG_OABUFFER_BUFFER_SIZE_SHIFT (3)
#घोषणा  GEN12_OAG_OABUFFER_MEMORY_SELECT     (1 << 0) /* 0: PPGTT, 1: GGTT */

#घोषणा GEN12_OAG_OAGLBCTXCTRL _MMIO(0x2b28)
#घोषणा  GEN12_OAG_OAGLBCTXCTRL_TIMER_PERIOD_SHIFT 2
#घोषणा  GEN12_OAG_OAGLBCTXCTRL_TIMER_ENABLE       (1 << 1)
#घोषणा  GEN12_OAG_OAGLBCTXCTRL_COUNTER_RESUME     (1 << 0)

#घोषणा GEN12_OAG_OACONTROL _MMIO(0xdaf4)
#घोषणा  GEN12_OAG_OACONTROL_OA_COUNTER_FORMAT_SHIFT 2
#घोषणा  GEN12_OAG_OACONTROL_OA_COUNTER_ENABLE       (1 << 0)

#घोषणा GEN12_OAG_OA_DEBUG _MMIO(0xdaf8)
#घोषणा  GEN12_OAG_OA_DEBUG_INCLUDE_CLK_RATIO          (1 << 6)
#घोषणा  GEN12_OAG_OA_DEBUG_DISABLE_CLK_RATIO_REPORTS  (1 << 5)
#घोषणा  GEN12_OAG_OA_DEBUG_DISABLE_GO_1_0_REPORTS     (1 << 2)
#घोषणा  GEN12_OAG_OA_DEBUG_DISABLE_CTX_SWITCH_REPORTS (1 << 1)

#घोषणा GEN12_OAG_OASTATUS _MMIO(0xdafc)
#घोषणा  GEN12_OAG_OASTATUS_COUNTER_OVERFLOW (1 << 2)
#घोषणा  GEN12_OAG_OASTATUS_BUFFER_OVERFLOW  (1 << 1)
#घोषणा  GEN12_OAG_OASTATUS_REPORT_LOST      (1 << 0)

/*
 * Flexible, Aggregate EU Counter Registers.
 * Note: these aren't contiguous
 */
#घोषणा EU_PERF_CNTL0	    _MMIO(0xe458)
#घोषणा EU_PERF_CNTL1	    _MMIO(0xe558)
#घोषणा EU_PERF_CNTL2	    _MMIO(0xe658)
#घोषणा EU_PERF_CNTL3	    _MMIO(0xe758)
#घोषणा EU_PERF_CNTL4	    _MMIO(0xe45c)
#घोषणा EU_PERF_CNTL5	    _MMIO(0xe55c)
#घोषणा EU_PERF_CNTL6	    _MMIO(0xe65c)

/*
 * OA Boolean state
 */

#घोषणा OASTARTTRIG1 _MMIO(0x2710)
#घोषणा OASTARTTRIG1_THRESHOLD_COUNT_MASK_MBZ 0xffff0000
#घोषणा OASTARTTRIG1_THRESHOLD_MASK	      0xffff

#घोषणा OASTARTTRIG2 _MMIO(0x2714)
#घोषणा OASTARTTRIG2_INVERT_A_0 (1 << 0)
#घोषणा OASTARTTRIG2_INVERT_A_1 (1 << 1)
#घोषणा OASTARTTRIG2_INVERT_A_2 (1 << 2)
#घोषणा OASTARTTRIG2_INVERT_A_3 (1 << 3)
#घोषणा OASTARTTRIG2_INVERT_A_4 (1 << 4)
#घोषणा OASTARTTRIG2_INVERT_A_5 (1 << 5)
#घोषणा OASTARTTRIG2_INVERT_A_6 (1 << 6)
#घोषणा OASTARTTRIG2_INVERT_A_7 (1 << 7)
#घोषणा OASTARTTRIG2_INVERT_A_8 (1 << 8)
#घोषणा OASTARTTRIG2_INVERT_A_9 (1 << 9)
#घोषणा OASTARTTRIG2_INVERT_A_10 (1 << 10)
#घोषणा OASTARTTRIG2_INVERT_A_11 (1 << 11)
#घोषणा OASTARTTRIG2_INVERT_A_12 (1 << 12)
#घोषणा OASTARTTRIG2_INVERT_A_13 (1 << 13)
#घोषणा OASTARTTRIG2_INVERT_A_14 (1 << 14)
#घोषणा OASTARTTRIG2_INVERT_A_15 (1 << 15)
#घोषणा OASTARTTRIG2_INVERT_B_0 (1 << 16)
#घोषणा OASTARTTRIG2_INVERT_B_1 (1 << 17)
#घोषणा OASTARTTRIG2_INVERT_B_2 (1 << 18)
#घोषणा OASTARTTRIG2_INVERT_B_3 (1 << 19)
#घोषणा OASTARTTRIG2_INVERT_C_0 (1 << 20)
#घोषणा OASTARTTRIG2_INVERT_C_1 (1 << 21)
#घोषणा OASTARTTRIG2_INVERT_D_0 (1 << 22)
#घोषणा OASTARTTRIG2_THRESHOLD_ENABLE	    (1 << 23)
#घोषणा OASTARTTRIG2_START_TRIG_FLAG_MBZ    (1 << 24)
#घोषणा OASTARTTRIG2_EVENT_SELECT_0  (1 << 28)
#घोषणा OASTARTTRIG2_EVENT_SELECT_1  (1 << 29)
#घोषणा OASTARTTRIG2_EVENT_SELECT_2  (1 << 30)
#घोषणा OASTARTTRIG2_EVENT_SELECT_3  (1 << 31)

#घोषणा OASTARTTRIG3 _MMIO(0x2718)
#घोषणा OASTARTTRIG3_NOA_SELECT_MASK	   0xf
#घोषणा OASTARTTRIG3_NOA_SELECT_8_SHIFT    0
#घोषणा OASTARTTRIG3_NOA_SELECT_9_SHIFT    4
#घोषणा OASTARTTRIG3_NOA_SELECT_10_SHIFT   8
#घोषणा OASTARTTRIG3_NOA_SELECT_11_SHIFT   12
#घोषणा OASTARTTRIG3_NOA_SELECT_12_SHIFT   16
#घोषणा OASTARTTRIG3_NOA_SELECT_13_SHIFT   20
#घोषणा OASTARTTRIG3_NOA_SELECT_14_SHIFT   24
#घोषणा OASTARTTRIG3_NOA_SELECT_15_SHIFT   28

#घोषणा OASTARTTRIG4 _MMIO(0x271c)
#घोषणा OASTARTTRIG4_NOA_SELECT_MASK	    0xf
#घोषणा OASTARTTRIG4_NOA_SELECT_0_SHIFT    0
#घोषणा OASTARTTRIG4_NOA_SELECT_1_SHIFT    4
#घोषणा OASTARTTRIG4_NOA_SELECT_2_SHIFT    8
#घोषणा OASTARTTRIG4_NOA_SELECT_3_SHIFT    12
#घोषणा OASTARTTRIG4_NOA_SELECT_4_SHIFT    16
#घोषणा OASTARTTRIG4_NOA_SELECT_5_SHIFT    20
#घोषणा OASTARTTRIG4_NOA_SELECT_6_SHIFT    24
#घोषणा OASTARTTRIG4_NOA_SELECT_7_SHIFT    28

#घोषणा OASTARTTRIG5 _MMIO(0x2720)
#घोषणा OASTARTTRIG5_THRESHOLD_COUNT_MASK_MBZ 0xffff0000
#घोषणा OASTARTTRIG5_THRESHOLD_MASK	      0xffff

#घोषणा OASTARTTRIG6 _MMIO(0x2724)
#घोषणा OASTARTTRIG6_INVERT_A_0 (1 << 0)
#घोषणा OASTARTTRIG6_INVERT_A_1 (1 << 1)
#घोषणा OASTARTTRIG6_INVERT_A_2 (1 << 2)
#घोषणा OASTARTTRIG6_INVERT_A_3 (1 << 3)
#घोषणा OASTARTTRIG6_INVERT_A_4 (1 << 4)
#घोषणा OASTARTTRIG6_INVERT_A_5 (1 << 5)
#घोषणा OASTARTTRIG6_INVERT_A_6 (1 << 6)
#घोषणा OASTARTTRIG6_INVERT_A_7 (1 << 7)
#घोषणा OASTARTTRIG6_INVERT_A_8 (1 << 8)
#घोषणा OASTARTTRIG6_INVERT_A_9 (1 << 9)
#घोषणा OASTARTTRIG6_INVERT_A_10 (1 << 10)
#घोषणा OASTARTTRIG6_INVERT_A_11 (1 << 11)
#घोषणा OASTARTTRIG6_INVERT_A_12 (1 << 12)
#घोषणा OASTARTTRIG6_INVERT_A_13 (1 << 13)
#घोषणा OASTARTTRIG6_INVERT_A_14 (1 << 14)
#घोषणा OASTARTTRIG6_INVERT_A_15 (1 << 15)
#घोषणा OASTARTTRIG6_INVERT_B_0 (1 << 16)
#घोषणा OASTARTTRIG6_INVERT_B_1 (1 << 17)
#घोषणा OASTARTTRIG6_INVERT_B_2 (1 << 18)
#घोषणा OASTARTTRIG6_INVERT_B_3 (1 << 19)
#घोषणा OASTARTTRIG6_INVERT_C_0 (1 << 20)
#घोषणा OASTARTTRIG6_INVERT_C_1 (1 << 21)
#घोषणा OASTARTTRIG6_INVERT_D_0 (1 << 22)
#घोषणा OASTARTTRIG6_THRESHOLD_ENABLE	    (1 << 23)
#घोषणा OASTARTTRIG6_START_TRIG_FLAG_MBZ    (1 << 24)
#घोषणा OASTARTTRIG6_EVENT_SELECT_4  (1 << 28)
#घोषणा OASTARTTRIG6_EVENT_SELECT_5  (1 << 29)
#घोषणा OASTARTTRIG6_EVENT_SELECT_6  (1 << 30)
#घोषणा OASTARTTRIG6_EVENT_SELECT_7  (1 << 31)

#घोषणा OASTARTTRIG7 _MMIO(0x2728)
#घोषणा OASTARTTRIG7_NOA_SELECT_MASK	   0xf
#घोषणा OASTARTTRIG7_NOA_SELECT_8_SHIFT    0
#घोषणा OASTARTTRIG7_NOA_SELECT_9_SHIFT    4
#घोषणा OASTARTTRIG7_NOA_SELECT_10_SHIFT   8
#घोषणा OASTARTTRIG7_NOA_SELECT_11_SHIFT   12
#घोषणा OASTARTTRIG7_NOA_SELECT_12_SHIFT   16
#घोषणा OASTARTTRIG7_NOA_SELECT_13_SHIFT   20
#घोषणा OASTARTTRIG7_NOA_SELECT_14_SHIFT   24
#घोषणा OASTARTTRIG7_NOA_SELECT_15_SHIFT   28

#घोषणा OASTARTTRIG8 _MMIO(0x272c)
#घोषणा OASTARTTRIG8_NOA_SELECT_MASK	   0xf
#घोषणा OASTARTTRIG8_NOA_SELECT_0_SHIFT    0
#घोषणा OASTARTTRIG8_NOA_SELECT_1_SHIFT    4
#घोषणा OASTARTTRIG8_NOA_SELECT_2_SHIFT    8
#घोषणा OASTARTTRIG8_NOA_SELECT_3_SHIFT    12
#घोषणा OASTARTTRIG8_NOA_SELECT_4_SHIFT    16
#घोषणा OASTARTTRIG8_NOA_SELECT_5_SHIFT    20
#घोषणा OASTARTTRIG8_NOA_SELECT_6_SHIFT    24
#घोषणा OASTARTTRIG8_NOA_SELECT_7_SHIFT    28

#घोषणा OAREPORTTRIG1 _MMIO(0x2740)
#घोषणा OAREPORTTRIG1_THRESHOLD_MASK 0xffff
#घोषणा OAREPORTTRIG1_EDGE_LEVEL_TRIGGER_SELECT_MASK 0xffff0000 /* 0=level */

#घोषणा OAREPORTTRIG2 _MMIO(0x2744)
#घोषणा OAREPORTTRIG2_INVERT_A_0  (1 << 0)
#घोषणा OAREPORTTRIG2_INVERT_A_1  (1 << 1)
#घोषणा OAREPORTTRIG2_INVERT_A_2  (1 << 2)
#घोषणा OAREPORTTRIG2_INVERT_A_3  (1 << 3)
#घोषणा OAREPORTTRIG2_INVERT_A_4  (1 << 4)
#घोषणा OAREPORTTRIG2_INVERT_A_5  (1 << 5)
#घोषणा OAREPORTTRIG2_INVERT_A_6  (1 << 6)
#घोषणा OAREPORTTRIG2_INVERT_A_7  (1 << 7)
#घोषणा OAREPORTTRIG2_INVERT_A_8  (1 << 8)
#घोषणा OAREPORTTRIG2_INVERT_A_9  (1 << 9)
#घोषणा OAREPORTTRIG2_INVERT_A_10 (1 << 10)
#घोषणा OAREPORTTRIG2_INVERT_A_11 (1 << 11)
#घोषणा OAREPORTTRIG2_INVERT_A_12 (1 << 12)
#घोषणा OAREPORTTRIG2_INVERT_A_13 (1 << 13)
#घोषणा OAREPORTTRIG2_INVERT_A_14 (1 << 14)
#घोषणा OAREPORTTRIG2_INVERT_A_15 (1 << 15)
#घोषणा OAREPORTTRIG2_INVERT_B_0  (1 << 16)
#घोषणा OAREPORTTRIG2_INVERT_B_1  (1 << 17)
#घोषणा OAREPORTTRIG2_INVERT_B_2  (1 << 18)
#घोषणा OAREPORTTRIG2_INVERT_B_3  (1 << 19)
#घोषणा OAREPORTTRIG2_INVERT_C_0  (1 << 20)
#घोषणा OAREPORTTRIG2_INVERT_C_1  (1 << 21)
#घोषणा OAREPORTTRIG2_INVERT_D_0  (1 << 22)
#घोषणा OAREPORTTRIG2_THRESHOLD_ENABLE	    (1 << 23)
#घोषणा OAREPORTTRIG2_REPORT_TRIGGER_ENABLE (1 << 31)

#घोषणा OAREPORTTRIG3 _MMIO(0x2748)
#घोषणा OAREPORTTRIG3_NOA_SELECT_MASK	    0xf
#घोषणा OAREPORTTRIG3_NOA_SELECT_8_SHIFT    0
#घोषणा OAREPORTTRIG3_NOA_SELECT_9_SHIFT    4
#घोषणा OAREPORTTRIG3_NOA_SELECT_10_SHIFT   8
#घोषणा OAREPORTTRIG3_NOA_SELECT_11_SHIFT   12
#घोषणा OAREPORTTRIG3_NOA_SELECT_12_SHIFT   16
#घोषणा OAREPORTTRIG3_NOA_SELECT_13_SHIFT   20
#घोषणा OAREPORTTRIG3_NOA_SELECT_14_SHIFT   24
#घोषणा OAREPORTTRIG3_NOA_SELECT_15_SHIFT   28

#घोषणा OAREPORTTRIG4 _MMIO(0x274c)
#घोषणा OAREPORTTRIG4_NOA_SELECT_MASK	    0xf
#घोषणा OAREPORTTRIG4_NOA_SELECT_0_SHIFT    0
#घोषणा OAREPORTTRIG4_NOA_SELECT_1_SHIFT    4
#घोषणा OAREPORTTRIG4_NOA_SELECT_2_SHIFT    8
#घोषणा OAREPORTTRIG4_NOA_SELECT_3_SHIFT    12
#घोषणा OAREPORTTRIG4_NOA_SELECT_4_SHIFT    16
#घोषणा OAREPORTTRIG4_NOA_SELECT_5_SHIFT    20
#घोषणा OAREPORTTRIG4_NOA_SELECT_6_SHIFT    24
#घोषणा OAREPORTTRIG4_NOA_SELECT_7_SHIFT    28

#घोषणा OAREPORTTRIG5 _MMIO(0x2750)
#घोषणा OAREPORTTRIG5_THRESHOLD_MASK 0xffff
#घोषणा OAREPORTTRIG5_EDGE_LEVEL_TRIGGER_SELECT_MASK 0xffff0000 /* 0=level */

#घोषणा OAREPORTTRIG6 _MMIO(0x2754)
#घोषणा OAREPORTTRIG6_INVERT_A_0  (1 << 0)
#घोषणा OAREPORTTRIG6_INVERT_A_1  (1 << 1)
#घोषणा OAREPORTTRIG6_INVERT_A_2  (1 << 2)
#घोषणा OAREPORTTRIG6_INVERT_A_3  (1 << 3)
#घोषणा OAREPORTTRIG6_INVERT_A_4  (1 << 4)
#घोषणा OAREPORTTRIG6_INVERT_A_5  (1 << 5)
#घोषणा OAREPORTTRIG6_INVERT_A_6  (1 << 6)
#घोषणा OAREPORTTRIG6_INVERT_A_7  (1 << 7)
#घोषणा OAREPORTTRIG6_INVERT_A_8  (1 << 8)
#घोषणा OAREPORTTRIG6_INVERT_A_9  (1 << 9)
#घोषणा OAREPORTTRIG6_INVERT_A_10 (1 << 10)
#घोषणा OAREPORTTRIG6_INVERT_A_11 (1 << 11)
#घोषणा OAREPORTTRIG6_INVERT_A_12 (1 << 12)
#घोषणा OAREPORTTRIG6_INVERT_A_13 (1 << 13)
#घोषणा OAREPORTTRIG6_INVERT_A_14 (1 << 14)
#घोषणा OAREPORTTRIG6_INVERT_A_15 (1 << 15)
#घोषणा OAREPORTTRIG6_INVERT_B_0  (1 << 16)
#घोषणा OAREPORTTRIG6_INVERT_B_1  (1 << 17)
#घोषणा OAREPORTTRIG6_INVERT_B_2  (1 << 18)
#घोषणा OAREPORTTRIG6_INVERT_B_3  (1 << 19)
#घोषणा OAREPORTTRIG6_INVERT_C_0  (1 << 20)
#घोषणा OAREPORTTRIG6_INVERT_C_1  (1 << 21)
#घोषणा OAREPORTTRIG6_INVERT_D_0  (1 << 22)
#घोषणा OAREPORTTRIG6_THRESHOLD_ENABLE	    (1 << 23)
#घोषणा OAREPORTTRIG6_REPORT_TRIGGER_ENABLE (1 << 31)

#घोषणा OAREPORTTRIG7 _MMIO(0x2758)
#घोषणा OAREPORTTRIG7_NOA_SELECT_MASK	    0xf
#घोषणा OAREPORTTRIG7_NOA_SELECT_8_SHIFT    0
#घोषणा OAREPORTTRIG7_NOA_SELECT_9_SHIFT    4
#घोषणा OAREPORTTRIG7_NOA_SELECT_10_SHIFT   8
#घोषणा OAREPORTTRIG7_NOA_SELECT_11_SHIFT   12
#घोषणा OAREPORTTRIG7_NOA_SELECT_12_SHIFT   16
#घोषणा OAREPORTTRIG7_NOA_SELECT_13_SHIFT   20
#घोषणा OAREPORTTRIG7_NOA_SELECT_14_SHIFT   24
#घोषणा OAREPORTTRIG7_NOA_SELECT_15_SHIFT   28

#घोषणा OAREPORTTRIG8 _MMIO(0x275c)
#घोषणा OAREPORTTRIG8_NOA_SELECT_MASK	    0xf
#घोषणा OAREPORTTRIG8_NOA_SELECT_0_SHIFT    0
#घोषणा OAREPORTTRIG8_NOA_SELECT_1_SHIFT    4
#घोषणा OAREPORTTRIG8_NOA_SELECT_2_SHIFT    8
#घोषणा OAREPORTTRIG8_NOA_SELECT_3_SHIFT    12
#घोषणा OAREPORTTRIG8_NOA_SELECT_4_SHIFT    16
#घोषणा OAREPORTTRIG8_NOA_SELECT_5_SHIFT    20
#घोषणा OAREPORTTRIG8_NOA_SELECT_6_SHIFT    24
#घोषणा OAREPORTTRIG8_NOA_SELECT_7_SHIFT    28

/* Same layout as OASTARTTRIGX */
#घोषणा GEN12_OAG_OASTARTTRIG1 _MMIO(0xd900)
#घोषणा GEN12_OAG_OASTARTTRIG2 _MMIO(0xd904)
#घोषणा GEN12_OAG_OASTARTTRIG3 _MMIO(0xd908)
#घोषणा GEN12_OAG_OASTARTTRIG4 _MMIO(0xd90c)
#घोषणा GEN12_OAG_OASTARTTRIG5 _MMIO(0xd910)
#घोषणा GEN12_OAG_OASTARTTRIG6 _MMIO(0xd914)
#घोषणा GEN12_OAG_OASTARTTRIG7 _MMIO(0xd918)
#घोषणा GEN12_OAG_OASTARTTRIG8 _MMIO(0xd91c)

/* Same layout as OAREPORTTRIGX */
#घोषणा GEN12_OAG_OAREPORTTRIG1 _MMIO(0xd920)
#घोषणा GEN12_OAG_OAREPORTTRIG2 _MMIO(0xd924)
#घोषणा GEN12_OAG_OAREPORTTRIG3 _MMIO(0xd928)
#घोषणा GEN12_OAG_OAREPORTTRIG4 _MMIO(0xd92c)
#घोषणा GEN12_OAG_OAREPORTTRIG5 _MMIO(0xd930)
#घोषणा GEN12_OAG_OAREPORTTRIG6 _MMIO(0xd934)
#घोषणा GEN12_OAG_OAREPORTTRIG7 _MMIO(0xd938)
#घोषणा GEN12_OAG_OAREPORTTRIG8 _MMIO(0xd93c)

/* CECX_0 */
#घोषणा OACEC_COMPARE_LESS_OR_EQUAL	6
#घोषणा OACEC_COMPARE_NOT_EQUAL		5
#घोषणा OACEC_COMPARE_LESS_THAN		4
#घोषणा OACEC_COMPARE_GREATER_OR_EQUAL	3
#घोषणा OACEC_COMPARE_EQUAL		2
#घोषणा OACEC_COMPARE_GREATER_THAN	1
#घोषणा OACEC_COMPARE_ANY_EQUAL		0

#घोषणा OACEC_COMPARE_VALUE_MASK    0xffff
#घोषणा OACEC_COMPARE_VALUE_SHIFT   3

#घोषणा OACEC_SELECT_NOA	(0 << 19)
#घोषणा OACEC_SELECT_PREV	(1 << 19)
#घोषणा OACEC_SELECT_BOOLEAN	(2 << 19)

/* 11-bit array 0: pass-through, 1: negated */
#घोषणा GEN12_OASCEC_NEGATE_MASK  0x7ff
#घोषणा GEN12_OASCEC_NEGATE_SHIFT 21

/* CECX_1 */
#घोषणा OACEC_MASK_MASK		    0xffff
#घोषणा OACEC_CONSIDERATIONS_MASK   0xffff
#घोषणा OACEC_CONSIDERATIONS_SHIFT  16

#घोषणा OACEC0_0 _MMIO(0x2770)
#घोषणा OACEC0_1 _MMIO(0x2774)
#घोषणा OACEC1_0 _MMIO(0x2778)
#घोषणा OACEC1_1 _MMIO(0x277c)
#घोषणा OACEC2_0 _MMIO(0x2780)
#घोषणा OACEC2_1 _MMIO(0x2784)
#घोषणा OACEC3_0 _MMIO(0x2788)
#घोषणा OACEC3_1 _MMIO(0x278c)
#घोषणा OACEC4_0 _MMIO(0x2790)
#घोषणा OACEC4_1 _MMIO(0x2794)
#घोषणा OACEC5_0 _MMIO(0x2798)
#घोषणा OACEC5_1 _MMIO(0x279c)
#घोषणा OACEC6_0 _MMIO(0x27a0)
#घोषणा OACEC6_1 _MMIO(0x27a4)
#घोषणा OACEC7_0 _MMIO(0x27a8)
#घोषणा OACEC7_1 _MMIO(0x27ac)

/* Same layout as CECX_Y */
#घोषणा GEN12_OAG_CEC0_0 _MMIO(0xd940)
#घोषणा GEN12_OAG_CEC0_1 _MMIO(0xd944)
#घोषणा GEN12_OAG_CEC1_0 _MMIO(0xd948)
#घोषणा GEN12_OAG_CEC1_1 _MMIO(0xd94c)
#घोषणा GEN12_OAG_CEC2_0 _MMIO(0xd950)
#घोषणा GEN12_OAG_CEC2_1 _MMIO(0xd954)
#घोषणा GEN12_OAG_CEC3_0 _MMIO(0xd958)
#घोषणा GEN12_OAG_CEC3_1 _MMIO(0xd95c)
#घोषणा GEN12_OAG_CEC4_0 _MMIO(0xd960)
#घोषणा GEN12_OAG_CEC4_1 _MMIO(0xd964)
#घोषणा GEN12_OAG_CEC5_0 _MMIO(0xd968)
#घोषणा GEN12_OAG_CEC5_1 _MMIO(0xd96c)
#घोषणा GEN12_OAG_CEC6_0 _MMIO(0xd970)
#घोषणा GEN12_OAG_CEC6_1 _MMIO(0xd974)
#घोषणा GEN12_OAG_CEC7_0 _MMIO(0xd978)
#घोषणा GEN12_OAG_CEC7_1 _MMIO(0xd97c)

/* Same layout as CECX_Y + negate 11-bit array */
#घोषणा GEN12_OAG_SCEC0_0 _MMIO(0xdc00)
#घोषणा GEN12_OAG_SCEC0_1 _MMIO(0xdc04)
#घोषणा GEN12_OAG_SCEC1_0 _MMIO(0xdc08)
#घोषणा GEN12_OAG_SCEC1_1 _MMIO(0xdc0c)
#घोषणा GEN12_OAG_SCEC2_0 _MMIO(0xdc10)
#घोषणा GEN12_OAG_SCEC2_1 _MMIO(0xdc14)
#घोषणा GEN12_OAG_SCEC3_0 _MMIO(0xdc18)
#घोषणा GEN12_OAG_SCEC3_1 _MMIO(0xdc1c)
#घोषणा GEN12_OAG_SCEC4_0 _MMIO(0xdc20)
#घोषणा GEN12_OAG_SCEC4_1 _MMIO(0xdc24)
#घोषणा GEN12_OAG_SCEC5_0 _MMIO(0xdc28)
#घोषणा GEN12_OAG_SCEC5_1 _MMIO(0xdc2c)
#घोषणा GEN12_OAG_SCEC6_0 _MMIO(0xdc30)
#घोषणा GEN12_OAG_SCEC6_1 _MMIO(0xdc34)
#घोषणा GEN12_OAG_SCEC7_0 _MMIO(0xdc38)
#घोषणा GEN12_OAG_SCEC7_1 _MMIO(0xdc3c)

/* OA perf counters */
#घोषणा OA_PERFCNT1_LO      _MMIO(0x91B8)
#घोषणा OA_PERFCNT1_HI      _MMIO(0x91BC)
#घोषणा OA_PERFCNT2_LO      _MMIO(0x91C0)
#घोषणा OA_PERFCNT2_HI      _MMIO(0x91C4)
#घोषणा OA_PERFCNT3_LO      _MMIO(0x91C8)
#घोषणा OA_PERFCNT3_HI      _MMIO(0x91CC)
#घोषणा OA_PERFCNT4_LO      _MMIO(0x91D8)
#घोषणा OA_PERFCNT4_HI      _MMIO(0x91DC)

#घोषणा OA_PERFMATRIX_LO    _MMIO(0x91C8)
#घोषणा OA_PERFMATRIX_HI    _MMIO(0x91CC)

/* RPM unit config (Gen8+) */
#घोषणा RPM_CONFIG0	    _MMIO(0x0D00)
#घोषणा  GEN9_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_SHIFT	3
#घोषणा  GEN9_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_MASK	(1 << GEN9_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_SHIFT)
#घोषणा  GEN9_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_19_2_MHZ	0
#घोषणा  GEN9_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_24_MHZ	1
#घोषणा  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_SHIFT	3
#घोषणा  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_MASK	(0x7 << GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_SHIFT)
#घोषणा  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_24_MHZ	0
#घोषणा  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_19_2_MHZ	1
#घोषणा  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_38_4_MHZ	2
#घोषणा  GEN11_RPM_CONFIG0_CRYSTAL_CLOCK_FREQ_25_MHZ	3
#घोषणा  GEN10_RPM_CONFIG0_CTC_SHIFT_PARAMETER_SHIFT	1
#घोषणा  GEN10_RPM_CONFIG0_CTC_SHIFT_PARAMETER_MASK	(0x3 << GEN10_RPM_CONFIG0_CTC_SHIFT_PARAMETER_SHIFT)

#घोषणा RPM_CONFIG1	    _MMIO(0x0D04)
#घोषणा  GEN10_GT_NOA_ENABLE  (1 << 9)

/* GPM unit config (Gen9+) */
#घोषणा CTC_MODE			_MMIO(0xA26C)
#घोषणा  CTC_SOURCE_PARAMETER_MASK 1
#घोषणा  CTC_SOURCE_CRYSTAL_CLOCK	0
#घोषणा  CTC_SOURCE_DIVIDE_LOGIC	1
#घोषणा  CTC_SHIFT_PARAMETER_SHIFT	1
#घोषणा  CTC_SHIFT_PARAMETER_MASK	(0x3 << CTC_SHIFT_PARAMETER_SHIFT)

/* RCP unit config (Gen8+) */
#घोषणा RCP_CONFIG	    _MMIO(0x0D08)

/* NOA (HSW) */
#घोषणा HSW_MBVID2_NOA0		_MMIO(0x9E80)
#घोषणा HSW_MBVID2_NOA1		_MMIO(0x9E84)
#घोषणा HSW_MBVID2_NOA2		_MMIO(0x9E88)
#घोषणा HSW_MBVID2_NOA3		_MMIO(0x9E8C)
#घोषणा HSW_MBVID2_NOA4		_MMIO(0x9E90)
#घोषणा HSW_MBVID2_NOA5		_MMIO(0x9E94)
#घोषणा HSW_MBVID2_NOA6		_MMIO(0x9E98)
#घोषणा HSW_MBVID2_NOA7		_MMIO(0x9E9C)
#घोषणा HSW_MBVID2_NOA8		_MMIO(0x9EA0)
#घोषणा HSW_MBVID2_NOA9		_MMIO(0x9EA4)

#घोषणा HSW_MBVID2_MISR0	_MMIO(0x9EC0)

/* NOA (Gen8+) */
#घोषणा NOA_CONFIG(i)	    _MMIO(0x0D0C + (i) * 4)

#घोषणा MICRO_BP0_0	    _MMIO(0x9800)
#घोषणा MICRO_BP0_2	    _MMIO(0x9804)
#घोषणा MICRO_BP0_1	    _MMIO(0x9808)

#घोषणा MICRO_BP1_0	    _MMIO(0x980C)
#घोषणा MICRO_BP1_2	    _MMIO(0x9810)
#घोषणा MICRO_BP1_1	    _MMIO(0x9814)

#घोषणा MICRO_BP2_0	    _MMIO(0x9818)
#घोषणा MICRO_BP2_2	    _MMIO(0x981C)
#घोषणा MICRO_BP2_1	    _MMIO(0x9820)

#घोषणा MICRO_BP3_0	    _MMIO(0x9824)
#घोषणा MICRO_BP3_2	    _MMIO(0x9828)
#घोषणा MICRO_BP3_1	    _MMIO(0x982C)

#घोषणा MICRO_BP_TRIGGER		_MMIO(0x9830)
#घोषणा MICRO_BP3_COUNT_STATUS01	_MMIO(0x9834)
#घोषणा MICRO_BP3_COUNT_STATUS23	_MMIO(0x9838)
#घोषणा MICRO_BP_FIRED_ARMED		_MMIO(0x983C)

#घोषणा GEN12_OAA_DBG_REG _MMIO(0xdc44)
#घोषणा GEN12_OAG_OA_PESS _MMIO(0x2b2c)
#घोषणा GEN12_OAG_SPCTR_CNF _MMIO(0xdc40)

#घोषणा GDT_CHICKEN_BITS    _MMIO(0x9840)
#घोषणा   GT_NOA_ENABLE	    0x00000080

#घोषणा NOA_DATA	    _MMIO(0x986C)
#घोषणा NOA_WRITE	    _MMIO(0x9888)
#घोषणा GEN10_NOA_WRITE_HIGH _MMIO(0x9884)

#घोषणा _GEN7_PIPEA_DE_LOAD_SL	0x70068
#घोषणा _GEN7_PIPEB_DE_LOAD_SL	0x71068
#घोषणा GEN7_PIPE_DE_LOAD_SL(pipe) _MMIO_PIPE(pipe, _GEN7_PIPEA_DE_LOAD_SL, _GEN7_PIPEB_DE_LOAD_SL)

/*
 * Reset रेजिस्टरs
 */
#घोषणा DEBUG_RESET_I830		_MMIO(0x6070)
#घोषणा  DEBUG_RESET_FULL		(1 << 7)
#घोषणा  DEBUG_RESET_RENDER		(1 << 8)
#घोषणा  DEBUG_RESET_DISPLAY		(1 << 9)

/*
 * IOSF sideband
 */
#घोषणा VLV_IOSF_DOORBELL_REQ			_MMIO(VLV_DISPLAY_BASE + 0x2100)
#घोषणा   IOSF_DEVFN_SHIFT			24
#घोषणा   IOSF_OPCODE_SHIFT			16
#घोषणा   IOSF_PORT_SHIFT			8
#घोषणा   IOSF_BYTE_ENABLES_SHIFT		4
#घोषणा   IOSF_BAR_SHIFT			1
#घोषणा   IOSF_SB_BUSY				(1 << 0)
#घोषणा   IOSF_PORT_BUNIT			0x03
#घोषणा   IOSF_PORT_PUNIT			0x04
#घोषणा   IOSF_PORT_NC				0x11
#घोषणा   IOSF_PORT_DPIO			0x12
#घोषणा   IOSF_PORT_GPIO_NC			0x13
#घोषणा   IOSF_PORT_CCK				0x14
#घोषणा   IOSF_PORT_DPIO_2			0x1a
#घोषणा   IOSF_PORT_FLISDSI			0x1b
#घोषणा   IOSF_PORT_GPIO_SC			0x48
#घोषणा   IOSF_PORT_GPIO_SUS			0xa8
#घोषणा   IOSF_PORT_CCU				0xa9
#घोषणा   CHV_IOSF_PORT_GPIO_N			0x13
#घोषणा   CHV_IOSF_PORT_GPIO_SE			0x48
#घोषणा   CHV_IOSF_PORT_GPIO_E			0xa8
#घोषणा   CHV_IOSF_PORT_GPIO_SW			0xb2
#घोषणा VLV_IOSF_DATA				_MMIO(VLV_DISPLAY_BASE + 0x2104)
#घोषणा VLV_IOSF_ADDR				_MMIO(VLV_DISPLAY_BASE + 0x2108)

/* See configdb bunit SB addr map */
#घोषणा BUNIT_REG_BISOC				0x11

/* PUNIT_REG_*SSPM0 */
#घोषणा   _SSPM0_SSC(val)			((val) << 0)
#घोषणा   SSPM0_SSC_MASK			_SSPM0_SSC(0x3)
#घोषणा   SSPM0_SSC_PWR_ON			_SSPM0_SSC(0x0)
#घोषणा   SSPM0_SSC_CLK_GATE			_SSPM0_SSC(0x1)
#घोषणा   SSPM0_SSC_RESET			_SSPM0_SSC(0x2)
#घोषणा   SSPM0_SSC_PWR_GATE			_SSPM0_SSC(0x3)
#घोषणा   _SSPM0_SSS(val)			((val) << 24)
#घोषणा   SSPM0_SSS_MASK			_SSPM0_SSS(0x3)
#घोषणा   SSPM0_SSS_PWR_ON			_SSPM0_SSS(0x0)
#घोषणा   SSPM0_SSS_CLK_GATE			_SSPM0_SSS(0x1)
#घोषणा   SSPM0_SSS_RESET			_SSPM0_SSS(0x2)
#घोषणा   SSPM0_SSS_PWR_GATE			_SSPM0_SSS(0x3)

/* PUNIT_REG_*SSPM1 */
#घोषणा   SSPM1_FREQSTAT_SHIFT			24
#घोषणा   SSPM1_FREQSTAT_MASK			(0x1f << SSPM1_FREQSTAT_SHIFT)
#घोषणा   SSPM1_FREQGUAR_SHIFT			8
#घोषणा   SSPM1_FREQGUAR_MASK			(0x1f << SSPM1_FREQGUAR_SHIFT)
#घोषणा   SSPM1_FREQ_SHIFT			0
#घोषणा   SSPM1_FREQ_MASK			(0x1f << SSPM1_FREQ_SHIFT)

#घोषणा PUNIT_REG_VEDSSPM0			0x32
#घोषणा PUNIT_REG_VEDSSPM1			0x33

#घोषणा PUNIT_REG_DSPSSPM			0x36
#घोषणा   DSPFREQSTAT_SHIFT_CHV			24
#घोषणा   DSPFREQSTAT_MASK_CHV			(0x1f << DSPFREQSTAT_SHIFT_CHV)
#घोषणा   DSPFREQGUAR_SHIFT_CHV			8
#घोषणा   DSPFREQGUAR_MASK_CHV			(0x1f << DSPFREQGUAR_SHIFT_CHV)
#घोषणा   DSPFREQSTAT_SHIFT			30
#घोषणा   DSPFREQSTAT_MASK			(0x3 << DSPFREQSTAT_SHIFT)
#घोषणा   DSPFREQGUAR_SHIFT			14
#घोषणा   DSPFREQGUAR_MASK			(0x3 << DSPFREQGUAR_SHIFT)
#घोषणा   DSP_MAXFIFO_PM5_STATUS		(1 << 22) /* chv */
#घोषणा   DSP_AUTO_CDCLK_GATE_DISABLE		(1 << 7) /* chv */
#घोषणा   DSP_MAXFIFO_PM5_ENABLE		(1 << 6) /* chv */
#घोषणा   _DP_SSC(val, pipe)			((val) << (2 * (pipe)))
#घोषणा   DP_SSC_MASK(pipe)			_DP_SSC(0x3, (pipe))
#घोषणा   DP_SSC_PWR_ON(pipe)			_DP_SSC(0x0, (pipe))
#घोषणा   DP_SSC_CLK_GATE(pipe)			_DP_SSC(0x1, (pipe))
#घोषणा   DP_SSC_RESET(pipe)			_DP_SSC(0x2, (pipe))
#घोषणा   DP_SSC_PWR_GATE(pipe)			_DP_SSC(0x3, (pipe))
#घोषणा   _DP_SSS(val, pipe)			((val) << (2 * (pipe) + 16))
#घोषणा   DP_SSS_MASK(pipe)			_DP_SSS(0x3, (pipe))
#घोषणा   DP_SSS_PWR_ON(pipe)			_DP_SSS(0x0, (pipe))
#घोषणा   DP_SSS_CLK_GATE(pipe)			_DP_SSS(0x1, (pipe))
#घोषणा   DP_SSS_RESET(pipe)			_DP_SSS(0x2, (pipe))
#घोषणा   DP_SSS_PWR_GATE(pipe)			_DP_SSS(0x3, (pipe))

#घोषणा PUNIT_REG_ISPSSPM0			0x39
#घोषणा PUNIT_REG_ISPSSPM1			0x3a

#घोषणा PUNIT_REG_PWRGT_CTRL			0x60
#घोषणा PUNIT_REG_PWRGT_STATUS			0x61
#घोषणा   PUNIT_PWRGT_MASK(pw_idx)		(3 << ((pw_idx) * 2))
#घोषणा   PUNIT_PWRGT_PWR_ON(pw_idx)		(0 << ((pw_idx) * 2))
#घोषणा   PUNIT_PWRGT_CLK_GATE(pw_idx)		(1 << ((pw_idx) * 2))
#घोषणा   PUNIT_PWRGT_RESET(pw_idx)		(2 << ((pw_idx) * 2))
#घोषणा   PUNIT_PWRGT_PWR_GATE(pw_idx)		(3 << ((pw_idx) * 2))

#घोषणा PUNIT_PWGT_IDX_RENDER			0
#घोषणा PUNIT_PWGT_IDX_MEDIA			1
#घोषणा PUNIT_PWGT_IDX_DISP2D			3
#घोषणा PUNIT_PWGT_IDX_DPIO_CMN_BC		5
#घोषणा PUNIT_PWGT_IDX_DPIO_TX_B_LANES_01	6
#घोषणा PUNIT_PWGT_IDX_DPIO_TX_B_LANES_23	7
#घोषणा PUNIT_PWGT_IDX_DPIO_TX_C_LANES_01	8
#घोषणा PUNIT_PWGT_IDX_DPIO_TX_C_LANES_23	9
#घोषणा PUNIT_PWGT_IDX_DPIO_RX0			10
#घोषणा PUNIT_PWGT_IDX_DPIO_RX1			11
#घोषणा PUNIT_PWGT_IDX_DPIO_CMN_D		12

#घोषणा PUNIT_REG_GPU_LFM			0xd3
#घोषणा PUNIT_REG_GPU_FREQ_REQ			0xd4
#घोषणा PUNIT_REG_GPU_FREQ_STS			0xd8
#घोषणा   GPLLENABLE				(1 << 4)
#घोषणा   GENFREQSTATUS				(1 << 0)
#घोषणा PUNIT_REG_MEDIA_TURBO_FREQ_REQ		0xdc
#घोषणा PUNIT_REG_CZ_TIMESTAMP			0xce

#घोषणा PUNIT_FUSE_BUS2				0xf6 /* bits 47:40 */
#घोषणा PUNIT_FUSE_BUS1				0xf5 /* bits 55:48 */

#घोषणा FB_GFX_FMAX_AT_VMAX_FUSE		0x136
#घोषणा FB_GFX_FREQ_FUSE_MASK			0xff
#घोषणा FB_GFX_FMAX_AT_VMAX_2SS4EU_FUSE_SHIFT	24
#घोषणा FB_GFX_FMAX_AT_VMAX_2SS6EU_FUSE_SHIFT	16
#घोषणा FB_GFX_FMAX_AT_VMAX_2SS8EU_FUSE_SHIFT	8

#घोषणा FB_GFX_FMIN_AT_VMIN_FUSE		0x137
#घोषणा FB_GFX_FMIN_AT_VMIN_FUSE_SHIFT		8

#घोषणा PUNIT_REG_DDR_SETUP2			0x139
#घोषणा   FORCE_DDR_FREQ_REQ_ACK		(1 << 8)
#घोषणा   FORCE_DDR_LOW_FREQ			(1 << 1)
#घोषणा   FORCE_DDR_HIGH_FREQ			(1 << 0)

#घोषणा PUNIT_GPU_STATUS_REG			0xdb
#घोषणा PUNIT_GPU_STATUS_MAX_FREQ_SHIFT	16
#घोषणा PUNIT_GPU_STATUS_MAX_FREQ_MASK		0xff
#घोषणा PUNIT_GPU_STATIS_GFX_MIN_FREQ_SHIFT	8
#घोषणा PUNIT_GPU_STATUS_GFX_MIN_FREQ_MASK	0xff

#घोषणा PUNIT_GPU_DUTYCYCLE_REG		0xdf
#घोषणा PUNIT_GPU_DUTYCYCLE_RPE_FREQ_SHIFT	8
#घोषणा PUNIT_GPU_DUTYCYCLE_RPE_FREQ_MASK	0xff

#घोषणा IOSF_NC_FB_GFX_FREQ_FUSE		0x1c
#घोषणा   FB_GFX_MAX_FREQ_FUSE_SHIFT		3
#घोषणा   FB_GFX_MAX_FREQ_FUSE_MASK		0x000007f8
#घोषणा   FB_GFX_FGUARANTEED_FREQ_FUSE_SHIFT	11
#घोषणा   FB_GFX_FGUARANTEED_FREQ_FUSE_MASK	0x0007f800
#घोषणा IOSF_NC_FB_GFX_FMAX_FUSE_HI		0x34
#घोषणा   FB_FMAX_VMIN_FREQ_HI_MASK		0x00000007
#घोषणा IOSF_NC_FB_GFX_FMAX_FUSE_LO		0x30
#घोषणा   FB_FMAX_VMIN_FREQ_LO_SHIFT		27
#घोषणा   FB_FMAX_VMIN_FREQ_LO_MASK		0xf8000000

#घोषणा VLV_TURBO_SOC_OVERRIDE		0x04
#घोषणा   VLV_OVERRIDE_EN		1
#घोषणा   VLV_SOC_TDP_EN		(1 << 1)
#घोषणा   VLV_BIAS_CPU_125_SOC_875	(6 << 2)
#घोषणा   CHV_BIAS_CPU_50_SOC_50	(3 << 2)

/* vlv2 north घड़ी has */
#घोषणा CCK_FUSE_REG				0x8
#घोषणा  CCK_FUSE_HPLL_FREQ_MASK		0x3
#घोषणा CCK_REG_DSI_PLL_FUSE			0x44
#घोषणा CCK_REG_DSI_PLL_CONTROL			0x48
#घोषणा  DSI_PLL_VCO_EN				(1 << 31)
#घोषणा  DSI_PLL_LDO_GATE			(1 << 30)
#घोषणा  DSI_PLL_P1_POST_DIV_SHIFT		17
#घोषणा  DSI_PLL_P1_POST_DIV_MASK		(0x1ff << 17)
#घोषणा  DSI_PLL_P2_MUX_DSI0_DIV2		(1 << 13)
#घोषणा  DSI_PLL_P3_MUX_DSI1_DIV2		(1 << 12)
#घोषणा  DSI_PLL_MUX_MASK			(3 << 9)
#घोषणा  DSI_PLL_MUX_DSI0_DSIPLL		(0 << 10)
#घोषणा  DSI_PLL_MUX_DSI0_CCK			(1 << 10)
#घोषणा  DSI_PLL_MUX_DSI1_DSIPLL		(0 << 9)
#घोषणा  DSI_PLL_MUX_DSI1_CCK			(1 << 9)
#घोषणा  DSI_PLL_CLK_GATE_MASK			(0xf << 5)
#घोषणा  DSI_PLL_CLK_GATE_DSI0_DSIPLL		(1 << 8)
#घोषणा  DSI_PLL_CLK_GATE_DSI1_DSIPLL		(1 << 7)
#घोषणा  DSI_PLL_CLK_GATE_DSI0_CCK		(1 << 6)
#घोषणा  DSI_PLL_CLK_GATE_DSI1_CCK		(1 << 5)
#घोषणा  DSI_PLL_LOCK				(1 << 0)
#घोषणा CCK_REG_DSI_PLL_DIVIDER			0x4c
#घोषणा  DSI_PLL_LFSR				(1 << 31)
#घोषणा  DSI_PLL_FRACTION_EN			(1 << 30)
#घोषणा  DSI_PLL_FRAC_COUNTER_SHIFT		27
#घोषणा  DSI_PLL_FRAC_COUNTER_MASK		(7 << 27)
#घोषणा  DSI_PLL_USYNC_CNT_SHIFT		18
#घोषणा  DSI_PLL_USYNC_CNT_MASK			(0x1ff << 18)
#घोषणा  DSI_PLL_N1_DIV_SHIFT			16
#घोषणा  DSI_PLL_N1_DIV_MASK			(3 << 16)
#घोषणा  DSI_PLL_M1_DIV_SHIFT			0
#घोषणा  DSI_PLL_M1_DIV_MASK			(0x1ff << 0)
#घोषणा CCK_CZ_CLOCK_CONTROL			0x62
#घोषणा CCK_GPLL_CLOCK_CONTROL			0x67
#घोषणा CCK_DISPLAY_CLOCK_CONTROL		0x6b
#घोषणा CCK_DISPLAY_REF_CLOCK_CONTROL		0x6c
#घोषणा  CCK_TRUNK_FORCE_ON			(1 << 17)
#घोषणा  CCK_TRUNK_FORCE_OFF			(1 << 16)
#घोषणा  CCK_FREQUENCY_STATUS			(0x1f << 8)
#घोषणा  CCK_FREQUENCY_STATUS_SHIFT		8
#घोषणा  CCK_FREQUENCY_VALUES			(0x1f << 0)

/* DPIO रेजिस्टरs */
#घोषणा DPIO_DEVFN			0

#घोषणा DPIO_CTL			_MMIO(VLV_DISPLAY_BASE + 0x2110)
#घोषणा  DPIO_MODSEL1			(1 << 3) /* अगर ref clk b == 27 */
#घोषणा  DPIO_MODSEL0			(1 << 2) /* अगर ref clk a == 27 */
#घोषणा  DPIO_SFR_BYPASS		(1 << 1)
#घोषणा  DPIO_CMNRST			(1 << 0)

#घोषणा DPIO_PHY(pipe)			((pipe) >> 1)

/*
 * Per pipe/PLL DPIO regs
 */
#घोषणा _VLV_PLL_DW3_CH0		0x800c
#घोषणा   DPIO_POST_DIV_SHIFT		(28) /* 3 bits */
#घोषणा   DPIO_POST_DIV_DAC		0
#घोषणा   DPIO_POST_DIV_HDMIDP		1 /* DAC 225-400M rate */
#घोषणा   DPIO_POST_DIV_LVDS1		2
#घोषणा   DPIO_POST_DIV_LVDS2		3
#घोषणा   DPIO_K_SHIFT			(24) /* 4 bits */
#घोषणा   DPIO_P1_SHIFT			(21) /* 3 bits */
#घोषणा   DPIO_P2_SHIFT			(16) /* 5 bits */
#घोषणा   DPIO_N_SHIFT			(12) /* 4 bits */
#घोषणा   DPIO_ENABLE_CALIBRATION	(1 << 11)
#घोषणा   DPIO_M1DIV_SHIFT		(8) /* 3 bits */
#घोषणा   DPIO_M2DIV_MASK		0xff
#घोषणा _VLV_PLL_DW3_CH1		0x802c
#घोषणा VLV_PLL_DW3(ch) _PIPE(ch, _VLV_PLL_DW3_CH0, _VLV_PLL_DW3_CH1)

#घोषणा _VLV_PLL_DW5_CH0		0x8014
#घोषणा   DPIO_REFSEL_OVERRIDE		27
#घोषणा   DPIO_PLL_MODESEL_SHIFT	24 /* 3 bits */
#घोषणा   DPIO_BIAS_CURRENT_CTL_SHIFT	21 /* 3 bits, always 0x7 */
#घोषणा   DPIO_PLL_REFCLK_SEL_SHIFT	16 /* 2 bits */
#घोषणा   DPIO_PLL_REFCLK_SEL_MASK	3
#घोषणा   DPIO_DRIVER_CTL_SHIFT		12 /* always set to 0x8 */
#घोषणा   DPIO_CLK_BIAS_CTL_SHIFT	8 /* always set to 0x5 */
#घोषणा _VLV_PLL_DW5_CH1		0x8034
#घोषणा VLV_PLL_DW5(ch) _PIPE(ch, _VLV_PLL_DW5_CH0, _VLV_PLL_DW5_CH1)

#घोषणा _VLV_PLL_DW7_CH0		0x801c
#घोषणा _VLV_PLL_DW7_CH1		0x803c
#घोषणा VLV_PLL_DW7(ch) _PIPE(ch, _VLV_PLL_DW7_CH0, _VLV_PLL_DW7_CH1)

#घोषणा _VLV_PLL_DW8_CH0		0x8040
#घोषणा _VLV_PLL_DW8_CH1		0x8060
#घोषणा VLV_PLL_DW8(ch) _PIPE(ch, _VLV_PLL_DW8_CH0, _VLV_PLL_DW8_CH1)

#घोषणा VLV_PLL_DW9_BCAST		0xc044
#घोषणा _VLV_PLL_DW9_CH0		0x8044
#घोषणा _VLV_PLL_DW9_CH1		0x8064
#घोषणा VLV_PLL_DW9(ch) _PIPE(ch, _VLV_PLL_DW9_CH0, _VLV_PLL_DW9_CH1)

#घोषणा _VLV_PLL_DW10_CH0		0x8048
#घोषणा _VLV_PLL_DW10_CH1		0x8068
#घोषणा VLV_PLL_DW10(ch) _PIPE(ch, _VLV_PLL_DW10_CH0, _VLV_PLL_DW10_CH1)

#घोषणा _VLV_PLL_DW11_CH0		0x804c
#घोषणा _VLV_PLL_DW11_CH1		0x806c
#घोषणा VLV_PLL_DW11(ch) _PIPE(ch, _VLV_PLL_DW11_CH0, _VLV_PLL_DW11_CH1)

/* Spec क्रम ref block start counts at DW10 */
#घोषणा VLV_REF_DW13			0x80ac

#घोषणा VLV_CMN_DW0			0x8100

/*
 * Per DDI channel DPIO regs
 */

#घोषणा _VLV_PCS_DW0_CH0		0x8200
#घोषणा _VLV_PCS_DW0_CH1		0x8400
#घोषणा   DPIO_PCS_TX_LANE2_RESET	(1 << 16)
#घोषणा   DPIO_PCS_TX_LANE1_RESET	(1 << 7)
#घोषणा   DPIO_LEFT_TXFIFO_RST_MASTER2	(1 << 4)
#घोषणा   DPIO_RIGHT_TXFIFO_RST_MASTER2	(1 << 3)
#घोषणा VLV_PCS_DW0(ch) _PORT(ch, _VLV_PCS_DW0_CH0, _VLV_PCS_DW0_CH1)

#घोषणा _VLV_PCS01_DW0_CH0		0x200
#घोषणा _VLV_PCS23_DW0_CH0		0x400
#घोषणा _VLV_PCS01_DW0_CH1		0x2600
#घोषणा _VLV_PCS23_DW0_CH1		0x2800
#घोषणा VLV_PCS01_DW0(ch) _PORT(ch, _VLV_PCS01_DW0_CH0, _VLV_PCS01_DW0_CH1)
#घोषणा VLV_PCS23_DW0(ch) _PORT(ch, _VLV_PCS23_DW0_CH0, _VLV_PCS23_DW0_CH1)

#घोषणा _VLV_PCS_DW1_CH0		0x8204
#घोषणा _VLV_PCS_DW1_CH1		0x8404
#घोषणा   CHV_PCS_REQ_SOFTRESET_EN	(1 << 23)
#घोषणा   DPIO_PCS_CLK_CRI_RXEB_EIOS_EN	(1 << 22)
#घोषणा   DPIO_PCS_CLK_CRI_RXDIGFILTSG_EN (1 << 21)
#घोषणा   DPIO_PCS_CLK_DATAWIDTH_SHIFT	(6)
#घोषणा   DPIO_PCS_CLK_SOFT_RESET	(1 << 5)
#घोषणा VLV_PCS_DW1(ch) _PORT(ch, _VLV_PCS_DW1_CH0, _VLV_PCS_DW1_CH1)

#घोषणा _VLV_PCS01_DW1_CH0		0x204
#घोषणा _VLV_PCS23_DW1_CH0		0x404
#घोषणा _VLV_PCS01_DW1_CH1		0x2604
#घोषणा _VLV_PCS23_DW1_CH1		0x2804
#घोषणा VLV_PCS01_DW1(ch) _PORT(ch, _VLV_PCS01_DW1_CH0, _VLV_PCS01_DW1_CH1)
#घोषणा VLV_PCS23_DW1(ch) _PORT(ch, _VLV_PCS23_DW1_CH0, _VLV_PCS23_DW1_CH1)

#घोषणा _VLV_PCS_DW8_CH0		0x8220
#घोषणा _VLV_PCS_DW8_CH1		0x8420
#घोषणा   CHV_PCS_USEDCLKCHANNEL_OVRRIDE	(1 << 20)
#घोषणा   CHV_PCS_USEDCLKCHANNEL		(1 << 21)
#घोषणा VLV_PCS_DW8(ch) _PORT(ch, _VLV_PCS_DW8_CH0, _VLV_PCS_DW8_CH1)

#घोषणा _VLV_PCS01_DW8_CH0		0x0220
#घोषणा _VLV_PCS23_DW8_CH0		0x0420
#घोषणा _VLV_PCS01_DW8_CH1		0x2620
#घोषणा _VLV_PCS23_DW8_CH1		0x2820
#घोषणा VLV_PCS01_DW8(port) _PORT(port, _VLV_PCS01_DW8_CH0, _VLV_PCS01_DW8_CH1)
#घोषणा VLV_PCS23_DW8(port) _PORT(port, _VLV_PCS23_DW8_CH0, _VLV_PCS23_DW8_CH1)

#घोषणा _VLV_PCS_DW9_CH0		0x8224
#घोषणा _VLV_PCS_DW9_CH1		0x8424
#घोषणा   DPIO_PCS_TX2MARGIN_MASK	(0x7 << 13)
#घोषणा   DPIO_PCS_TX2MARGIN_000	(0 << 13)
#घोषणा   DPIO_PCS_TX2MARGIN_101	(1 << 13)
#घोषणा   DPIO_PCS_TX1MARGIN_MASK	(0x7 << 10)
#घोषणा   DPIO_PCS_TX1MARGIN_000	(0 << 10)
#घोषणा   DPIO_PCS_TX1MARGIN_101	(1 << 10)
#घोषणा	VLV_PCS_DW9(ch) _PORT(ch, _VLV_PCS_DW9_CH0, _VLV_PCS_DW9_CH1)

#घोषणा _VLV_PCS01_DW9_CH0		0x224
#घोषणा _VLV_PCS23_DW9_CH0		0x424
#घोषणा _VLV_PCS01_DW9_CH1		0x2624
#घोषणा _VLV_PCS23_DW9_CH1		0x2824
#घोषणा VLV_PCS01_DW9(ch) _PORT(ch, _VLV_PCS01_DW9_CH0, _VLV_PCS01_DW9_CH1)
#घोषणा VLV_PCS23_DW9(ch) _PORT(ch, _VLV_PCS23_DW9_CH0, _VLV_PCS23_DW9_CH1)

#घोषणा _CHV_PCS_DW10_CH0		0x8228
#घोषणा _CHV_PCS_DW10_CH1		0x8428
#घोषणा   DPIO_PCS_SWING_CALC_TX0_TX2	(1 << 30)
#घोषणा   DPIO_PCS_SWING_CALC_TX1_TX3	(1 << 31)
#घोषणा   DPIO_PCS_TX2DEEMP_MASK	(0xf << 24)
#घोषणा   DPIO_PCS_TX2DEEMP_9P5		(0 << 24)
#घोषणा   DPIO_PCS_TX2DEEMP_6P0		(2 << 24)
#घोषणा   DPIO_PCS_TX1DEEMP_MASK	(0xf << 16)
#घोषणा   DPIO_PCS_TX1DEEMP_9P5		(0 << 16)
#घोषणा   DPIO_PCS_TX1DEEMP_6P0		(2 << 16)
#घोषणा CHV_PCS_DW10(ch) _PORT(ch, _CHV_PCS_DW10_CH0, _CHV_PCS_DW10_CH1)

#घोषणा _VLV_PCS01_DW10_CH0		0x0228
#घोषणा _VLV_PCS23_DW10_CH0		0x0428
#घोषणा _VLV_PCS01_DW10_CH1		0x2628
#घोषणा _VLV_PCS23_DW10_CH1		0x2828
#घोषणा VLV_PCS01_DW10(port) _PORT(port, _VLV_PCS01_DW10_CH0, _VLV_PCS01_DW10_CH1)
#घोषणा VLV_PCS23_DW10(port) _PORT(port, _VLV_PCS23_DW10_CH0, _VLV_PCS23_DW10_CH1)

#घोषणा _VLV_PCS_DW11_CH0		0x822c
#घोषणा _VLV_PCS_DW11_CH1		0x842c
#घोषणा   DPIO_TX2_STAGGER_MASK(x)	((x) << 24)
#घोषणा   DPIO_LANEDESKEW_STRAP_OVRD	(1 << 3)
#घोषणा   DPIO_LEFT_TXFIFO_RST_MASTER	(1 << 1)
#घोषणा   DPIO_RIGHT_TXFIFO_RST_MASTER	(1 << 0)
#घोषणा VLV_PCS_DW11(ch) _PORT(ch, _VLV_PCS_DW11_CH0, _VLV_PCS_DW11_CH1)

#घोषणा _VLV_PCS01_DW11_CH0		0x022c
#घोषणा _VLV_PCS23_DW11_CH0		0x042c
#घोषणा _VLV_PCS01_DW11_CH1		0x262c
#घोषणा _VLV_PCS23_DW11_CH1		0x282c
#घोषणा VLV_PCS01_DW11(ch) _PORT(ch, _VLV_PCS01_DW11_CH0, _VLV_PCS01_DW11_CH1)
#घोषणा VLV_PCS23_DW11(ch) _PORT(ch, _VLV_PCS23_DW11_CH0, _VLV_PCS23_DW11_CH1)

#घोषणा _VLV_PCS01_DW12_CH0		0x0230
#घोषणा _VLV_PCS23_DW12_CH0		0x0430
#घोषणा _VLV_PCS01_DW12_CH1		0x2630
#घोषणा _VLV_PCS23_DW12_CH1		0x2830
#घोषणा VLV_PCS01_DW12(ch) _PORT(ch, _VLV_PCS01_DW12_CH0, _VLV_PCS01_DW12_CH1)
#घोषणा VLV_PCS23_DW12(ch) _PORT(ch, _VLV_PCS23_DW12_CH0, _VLV_PCS23_DW12_CH1)

#घोषणा _VLV_PCS_DW12_CH0		0x8230
#घोषणा _VLV_PCS_DW12_CH1		0x8430
#घोषणा   DPIO_TX2_STAGGER_MULT(x)	((x) << 20)
#घोषणा   DPIO_TX1_STAGGER_MULT(x)	((x) << 16)
#घोषणा   DPIO_TX1_STAGGER_MASK(x)	((x) << 8)
#घोषणा   DPIO_LANESTAGGER_STRAP_OVRD	(1 << 6)
#घोषणा   DPIO_LANESTAGGER_STRAP(x)	((x) << 0)
#घोषणा VLV_PCS_DW12(ch) _PORT(ch, _VLV_PCS_DW12_CH0, _VLV_PCS_DW12_CH1)

#घोषणा _VLV_PCS_DW14_CH0		0x8238
#घोषणा _VLV_PCS_DW14_CH1		0x8438
#घोषणा	VLV_PCS_DW14(ch) _PORT(ch, _VLV_PCS_DW14_CH0, _VLV_PCS_DW14_CH1)

#घोषणा _VLV_PCS_DW23_CH0		0x825c
#घोषणा _VLV_PCS_DW23_CH1		0x845c
#घोषणा VLV_PCS_DW23(ch) _PORT(ch, _VLV_PCS_DW23_CH0, _VLV_PCS_DW23_CH1)

#घोषणा _VLV_TX_DW2_CH0			0x8288
#घोषणा _VLV_TX_DW2_CH1			0x8488
#घोषणा   DPIO_SWING_MARGIN000_SHIFT	16
#घोषणा   DPIO_SWING_MARGIN000_MASK	(0xff << DPIO_SWING_MARGIN000_SHIFT)
#घोषणा   DPIO_UNIQ_TRANS_SCALE_SHIFT	8
#घोषणा VLV_TX_DW2(ch) _PORT(ch, _VLV_TX_DW2_CH0, _VLV_TX_DW2_CH1)

#घोषणा _VLV_TX_DW3_CH0			0x828c
#घोषणा _VLV_TX_DW3_CH1			0x848c
/* The following bit क्रम CHV phy */
#घोषणा   DPIO_TX_UNIQ_TRANS_SCALE_EN	(1 << 27)
#घोषणा   DPIO_SWING_MARGIN101_SHIFT	16
#घोषणा   DPIO_SWING_MARGIN101_MASK	(0xff << DPIO_SWING_MARGIN101_SHIFT)
#घोषणा VLV_TX_DW3(ch) _PORT(ch, _VLV_TX_DW3_CH0, _VLV_TX_DW3_CH1)

#घोषणा _VLV_TX_DW4_CH0			0x8290
#घोषणा _VLV_TX_DW4_CH1			0x8490
#घोषणा   DPIO_SWING_DEEMPH9P5_SHIFT	24
#घोषणा   DPIO_SWING_DEEMPH9P5_MASK	(0xff << DPIO_SWING_DEEMPH9P5_SHIFT)
#घोषणा   DPIO_SWING_DEEMPH6P0_SHIFT	16
#घोषणा   DPIO_SWING_DEEMPH6P0_MASK	(0xff << DPIO_SWING_DEEMPH6P0_SHIFT)
#घोषणा VLV_TX_DW4(ch) _PORT(ch, _VLV_TX_DW4_CH0, _VLV_TX_DW4_CH1)

#घोषणा _VLV_TX3_DW4_CH0		0x690
#घोषणा _VLV_TX3_DW4_CH1		0x2a90
#घोषणा VLV_TX3_DW4(ch) _PORT(ch, _VLV_TX3_DW4_CH0, _VLV_TX3_DW4_CH1)

#घोषणा _VLV_TX_DW5_CH0			0x8294
#घोषणा _VLV_TX_DW5_CH1			0x8494
#घोषणा   DPIO_TX_OCALINIT_EN		(1 << 31)
#घोषणा VLV_TX_DW5(ch) _PORT(ch, _VLV_TX_DW5_CH0, _VLV_TX_DW5_CH1)

#घोषणा _VLV_TX_DW11_CH0		0x82ac
#घोषणा _VLV_TX_DW11_CH1		0x84ac
#घोषणा VLV_TX_DW11(ch) _PORT(ch, _VLV_TX_DW11_CH0, _VLV_TX_DW11_CH1)

#घोषणा _VLV_TX_DW14_CH0		0x82b8
#घोषणा _VLV_TX_DW14_CH1		0x84b8
#घोषणा VLV_TX_DW14(ch) _PORT(ch, _VLV_TX_DW14_CH0, _VLV_TX_DW14_CH1)

/* CHV dpPhy रेजिस्टरs */
#घोषणा _CHV_PLL_DW0_CH0		0x8000
#घोषणा _CHV_PLL_DW0_CH1		0x8180
#घोषणा CHV_PLL_DW0(ch) _PIPE(ch, _CHV_PLL_DW0_CH0, _CHV_PLL_DW0_CH1)

#घोषणा _CHV_PLL_DW1_CH0		0x8004
#घोषणा _CHV_PLL_DW1_CH1		0x8184
#घोषणा   DPIO_CHV_N_DIV_SHIFT		8
#घोषणा   DPIO_CHV_M1_DIV_BY_2		(0 << 0)
#घोषणा CHV_PLL_DW1(ch) _PIPE(ch, _CHV_PLL_DW1_CH0, _CHV_PLL_DW1_CH1)

#घोषणा _CHV_PLL_DW2_CH0		0x8008
#घोषणा _CHV_PLL_DW2_CH1		0x8188
#घोषणा CHV_PLL_DW2(ch) _PIPE(ch, _CHV_PLL_DW2_CH0, _CHV_PLL_DW2_CH1)

#घोषणा _CHV_PLL_DW3_CH0		0x800c
#घोषणा _CHV_PLL_DW3_CH1		0x818c
#घोषणा  DPIO_CHV_FRAC_DIV_EN		(1 << 16)
#घोषणा  DPIO_CHV_FIRST_MOD		(0 << 8)
#घोषणा  DPIO_CHV_SECOND_MOD		(1 << 8)
#घोषणा  DPIO_CHV_FEEDFWD_GAIN_SHIFT	0
#घोषणा  DPIO_CHV_FEEDFWD_GAIN_MASK		(0xF << 0)
#घोषणा CHV_PLL_DW3(ch) _PIPE(ch, _CHV_PLL_DW3_CH0, _CHV_PLL_DW3_CH1)

#घोषणा _CHV_PLL_DW6_CH0		0x8018
#घोषणा _CHV_PLL_DW6_CH1		0x8198
#घोषणा   DPIO_CHV_GAIN_CTRL_SHIFT	16
#घोषणा	  DPIO_CHV_INT_COEFF_SHIFT	8
#घोषणा   DPIO_CHV_PROP_COEFF_SHIFT	0
#घोषणा CHV_PLL_DW6(ch) _PIPE(ch, _CHV_PLL_DW6_CH0, _CHV_PLL_DW6_CH1)

#घोषणा _CHV_PLL_DW8_CH0		0x8020
#घोषणा _CHV_PLL_DW8_CH1		0x81A0
#घोषणा   DPIO_CHV_TDC_TARGET_CNT_SHIFT 0
#घोषणा   DPIO_CHV_TDC_TARGET_CNT_MASK  (0x3FF << 0)
#घोषणा CHV_PLL_DW8(ch) _PIPE(ch, _CHV_PLL_DW8_CH0, _CHV_PLL_DW8_CH1)

#घोषणा _CHV_PLL_DW9_CH0		0x8024
#घोषणा _CHV_PLL_DW9_CH1		0x81A4
#घोषणा  DPIO_CHV_INT_LOCK_THRESHOLD_SHIFT		1 /* 3 bits */
#घोषणा  DPIO_CHV_INT_LOCK_THRESHOLD_MASK		(7 << 1)
#घोषणा  DPIO_CHV_INT_LOCK_THRESHOLD_SEL_COARSE	1 /* 1: coarse & 0 : fine  */
#घोषणा CHV_PLL_DW9(ch) _PIPE(ch, _CHV_PLL_DW9_CH0, _CHV_PLL_DW9_CH1)

#घोषणा _CHV_CMN_DW0_CH0               0x8100
#घोषणा   DPIO_ALLDL_POWERDOWN_SHIFT_CH0	19
#घोषणा   DPIO_ANYDL_POWERDOWN_SHIFT_CH0	18
#घोषणा   DPIO_ALLDL_POWERDOWN			(1 << 1)
#घोषणा   DPIO_ANYDL_POWERDOWN			(1 << 0)

#घोषणा _CHV_CMN_DW5_CH0               0x8114
#घोषणा   CHV_BUFRIGHTENA1_DISABLE	(0 << 20)
#घोषणा   CHV_BUFRIGHTENA1_NORMAL	(1 << 20)
#घोषणा   CHV_BUFRIGHTENA1_FORCE	(3 << 20)
#घोषणा   CHV_BUFRIGHTENA1_MASK		(3 << 20)
#घोषणा   CHV_BUFLEFTENA1_DISABLE	(0 << 22)
#घोषणा   CHV_BUFLEFTENA1_NORMAL	(1 << 22)
#घोषणा   CHV_BUFLEFTENA1_FORCE		(3 << 22)
#घोषणा   CHV_BUFLEFTENA1_MASK		(3 << 22)

#घोषणा _CHV_CMN_DW13_CH0		0x8134
#घोषणा _CHV_CMN_DW0_CH1		0x8080
#घोषणा   DPIO_CHV_S1_DIV_SHIFT		21
#घोषणा   DPIO_CHV_P1_DIV_SHIFT		13 /* 3 bits */
#घोषणा   DPIO_CHV_P2_DIV_SHIFT		8  /* 5 bits */
#घोषणा   DPIO_CHV_K_DIV_SHIFT		4
#घोषणा   DPIO_PLL_FREQLOCK		(1 << 1)
#घोषणा   DPIO_PLL_LOCK			(1 << 0)
#घोषणा CHV_CMN_DW13(ch) _PIPE(ch, _CHV_CMN_DW13_CH0, _CHV_CMN_DW0_CH1)

#घोषणा _CHV_CMN_DW14_CH0		0x8138
#घोषणा _CHV_CMN_DW1_CH1		0x8084
#घोषणा   DPIO_AFC_RECAL		(1 << 14)
#घोषणा   DPIO_DCLKP_EN			(1 << 13)
#घोषणा   CHV_BUFLEFTENA2_DISABLE	(0 << 17) /* CL2 DW1 only */
#घोषणा   CHV_BUFLEFTENA2_NORMAL	(1 << 17) /* CL2 DW1 only */
#घोषणा   CHV_BUFLEFTENA2_FORCE		(3 << 17) /* CL2 DW1 only */
#घोषणा   CHV_BUFLEFTENA2_MASK		(3 << 17) /* CL2 DW1 only */
#घोषणा   CHV_BUFRIGHTENA2_DISABLE	(0 << 19) /* CL2 DW1 only */
#घोषणा   CHV_BUFRIGHTENA2_NORMAL	(1 << 19) /* CL2 DW1 only */
#घोषणा   CHV_BUFRIGHTENA2_FORCE	(3 << 19) /* CL2 DW1 only */
#घोषणा   CHV_BUFRIGHTENA2_MASK		(3 << 19) /* CL2 DW1 only */
#घोषणा CHV_CMN_DW14(ch) _PIPE(ch, _CHV_CMN_DW14_CH0, _CHV_CMN_DW1_CH1)

#घोषणा _CHV_CMN_DW19_CH0		0x814c
#घोषणा _CHV_CMN_DW6_CH1		0x8098
#घोषणा   DPIO_ALLDL_POWERDOWN_SHIFT_CH1	30 /* CL2 DW6 only */
#घोषणा   DPIO_ANYDL_POWERDOWN_SHIFT_CH1	29 /* CL2 DW6 only */
#घोषणा   DPIO_DYNPWRDOWNEN_CH1		(1 << 28) /* CL2 DW6 only */
#घोषणा   CHV_CMN_USEDCLKCHANNEL	(1 << 13)

#घोषणा CHV_CMN_DW19(ch) _PIPE(ch, _CHV_CMN_DW19_CH0, _CHV_CMN_DW6_CH1)

#घोषणा CHV_CMN_DW28			0x8170
#घोषणा   DPIO_CL1POWERDOWNEN		(1 << 23)
#घोषणा   DPIO_DYNPWRDOWNEN_CH0		(1 << 22)
#घोषणा   DPIO_SUS_CLK_CONFIG_ON		(0 << 0)
#घोषणा   DPIO_SUS_CLK_CONFIG_CLKREQ		(1 << 0)
#घोषणा   DPIO_SUS_CLK_CONFIG_GATE		(2 << 0)
#घोषणा   DPIO_SUS_CLK_CONFIG_GATE_CLKREQ	(3 << 0)

#घोषणा CHV_CMN_DW30			0x8178
#घोषणा   DPIO_CL2_LDOFUSE_PWRENB	(1 << 6)
#घोषणा   DPIO_LRC_BYPASS		(1 << 3)

#घोषणा _TXLANE(ch, lane, offset) ((ch ? 0x2400 : 0) + \
					(lane) * 0x200 + (offset))

#घोषणा CHV_TX_DW0(ch, lane) _TXLANE(ch, lane, 0x80)
#घोषणा CHV_TX_DW1(ch, lane) _TXLANE(ch, lane, 0x84)
#घोषणा CHV_TX_DW2(ch, lane) _TXLANE(ch, lane, 0x88)
#घोषणा CHV_TX_DW3(ch, lane) _TXLANE(ch, lane, 0x8c)
#घोषणा CHV_TX_DW4(ch, lane) _TXLANE(ch, lane, 0x90)
#घोषणा CHV_TX_DW5(ch, lane) _TXLANE(ch, lane, 0x94)
#घोषणा CHV_TX_DW6(ch, lane) _TXLANE(ch, lane, 0x98)
#घोषणा CHV_TX_DW7(ch, lane) _TXLANE(ch, lane, 0x9c)
#घोषणा CHV_TX_DW8(ch, lane) _TXLANE(ch, lane, 0xa0)
#घोषणा CHV_TX_DW9(ch, lane) _TXLANE(ch, lane, 0xa4)
#घोषणा CHV_TX_DW10(ch, lane) _TXLANE(ch, lane, 0xa8)
#घोषणा CHV_TX_DW11(ch, lane) _TXLANE(ch, lane, 0xac)
#घोषणा   DPIO_FRC_LATENCY_SHFIT	8
#घोषणा CHV_TX_DW14(ch, lane) _TXLANE(ch, lane, 0xb8)
#घोषणा   DPIO_UPAR_SHIFT		30

/* BXT PHY रेजिस्टरs */
#घोषणा _BXT_PHY0_BASE			0x6C000
#घोषणा _BXT_PHY1_BASE			0x162000
#घोषणा _BXT_PHY2_BASE			0x163000
#घोषणा BXT_PHY_BASE(phy)		_PHY3((phy), _BXT_PHY0_BASE, \
						     _BXT_PHY1_BASE, \
						     _BXT_PHY2_BASE)

#घोषणा _BXT_PHY(phy, reg)						\
	_MMIO(BXT_PHY_BASE(phy) - _BXT_PHY0_BASE + (reg))

#घोषणा _BXT_PHY_CH(phy, ch, reg_ch0, reg_ch1)		\
	(BXT_PHY_BASE(phy) + _PIPE((ch), (reg_ch0) - _BXT_PHY0_BASE,	\
					 (reg_ch1) - _BXT_PHY0_BASE))
#घोषणा _MMIO_BXT_PHY_CH(phy, ch, reg_ch0, reg_ch1)		\
	_MMIO(_BXT_PHY_CH(phy, ch, reg_ch0, reg_ch1))

#घोषणा BXT_P_CR_GT_DISP_PWRON		_MMIO(0x138090)
#घोषणा  MIPIO_RST_CTRL				(1 << 2)

#घोषणा _BXT_PHY_CTL_DDI_A		0x64C00
#घोषणा _BXT_PHY_CTL_DDI_B		0x64C10
#घोषणा _BXT_PHY_CTL_DDI_C		0x64C20
#घोषणा   BXT_PHY_CMNLANE_POWERDOWN_ACK	(1 << 10)
#घोषणा   BXT_PHY_LANE_POWERDOWN_ACK	(1 << 9)
#घोषणा   BXT_PHY_LANE_ENABLED		(1 << 8)
#घोषणा BXT_PHY_CTL(port)		_MMIO_PORT(port, _BXT_PHY_CTL_DDI_A, \
							 _BXT_PHY_CTL_DDI_B)

#घोषणा _PHY_CTL_FAMILY_EDP		0x64C80
#घोषणा _PHY_CTL_FAMILY_DDI		0x64C90
#घोषणा _PHY_CTL_FAMILY_DDI_C		0x64CA0
#घोषणा   COMMON_RESET_DIS		(1 << 31)
#घोषणा BXT_PHY_CTL_FAMILY(phy)		_MMIO_PHY3((phy), _PHY_CTL_FAMILY_DDI, \
							  _PHY_CTL_FAMILY_EDP, \
							  _PHY_CTL_FAMILY_DDI_C)

/* BXT PHY PLL रेजिस्टरs */
#घोषणा _PORT_PLL_A			0x46074
#घोषणा _PORT_PLL_B			0x46078
#घोषणा _PORT_PLL_C			0x4607c
#घोषणा   PORT_PLL_ENABLE		(1 << 31)
#घोषणा   PORT_PLL_LOCK			(1 << 30)
#घोषणा   PORT_PLL_REF_SEL		(1 << 27)
#घोषणा   PORT_PLL_POWER_ENABLE		(1 << 26)
#घोषणा   PORT_PLL_POWER_STATE		(1 << 25)
#घोषणा BXT_PORT_PLL_ENABLE(port)	_MMIO_PORT(port, _PORT_PLL_A, _PORT_PLL_B)

#घोषणा _PORT_PLL_EBB_0_A		0x162034
#घोषणा _PORT_PLL_EBB_0_B		0x6C034
#घोषणा _PORT_PLL_EBB_0_C		0x6C340
#घोषणा   PORT_PLL_P1_SHIFT		13
#घोषणा   PORT_PLL_P1_MASK		(0x07 << PORT_PLL_P1_SHIFT)
#घोषणा   PORT_PLL_P1(x)		((x)  << PORT_PLL_P1_SHIFT)
#घोषणा   PORT_PLL_P2_SHIFT		8
#घोषणा   PORT_PLL_P2_MASK		(0x1f << PORT_PLL_P2_SHIFT)
#घोषणा   PORT_PLL_P2(x)		((x)  << PORT_PLL_P2_SHIFT)
#घोषणा BXT_PORT_PLL_EBB_0(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_PLL_EBB_0_B, \
							 _PORT_PLL_EBB_0_C)

#घोषणा _PORT_PLL_EBB_4_A		0x162038
#घोषणा _PORT_PLL_EBB_4_B		0x6C038
#घोषणा _PORT_PLL_EBB_4_C		0x6C344
#घोषणा   PORT_PLL_10BIT_CLK_ENABLE	(1 << 13)
#घोषणा   PORT_PLL_RECALIBRATE		(1 << 14)
#घोषणा BXT_PORT_PLL_EBB_4(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_PLL_EBB_4_B, \
							 _PORT_PLL_EBB_4_C)

#घोषणा _PORT_PLL_0_A			0x162100
#घोषणा _PORT_PLL_0_B			0x6C100
#घोषणा _PORT_PLL_0_C			0x6C380
/* PORT_PLL_0_A */
#घोषणा   PORT_PLL_M2_MASK		0xFF
/* PORT_PLL_1_A */
#घोषणा   PORT_PLL_N_SHIFT		8
#घोषणा   PORT_PLL_N_MASK		(0x0F << PORT_PLL_N_SHIFT)
#घोषणा   PORT_PLL_N(x)			((x) << PORT_PLL_N_SHIFT)
/* PORT_PLL_2_A */
#घोषणा   PORT_PLL_M2_FRAC_MASK		0x3FFFFF
/* PORT_PLL_3_A */
#घोषणा   PORT_PLL_M2_FRAC_ENABLE	(1 << 16)
/* PORT_PLL_6_A */
#घोषणा   PORT_PLL_PROP_COEFF_MASK	0xF
#घोषणा   PORT_PLL_INT_COEFF_MASK	(0x1F << 8)
#घोषणा   PORT_PLL_INT_COEFF(x)		((x)  << 8)
#घोषणा   PORT_PLL_GAIN_CTL_MASK	(0x07 << 16)
#घोषणा   PORT_PLL_GAIN_CTL(x)		((x)  << 16)
/* PORT_PLL_8_A */
#घोषणा   PORT_PLL_TARGET_CNT_MASK	0x3FF
/* PORT_PLL_9_A */
#घोषणा  PORT_PLL_LOCK_THRESHOLD_SHIFT	1
#घोषणा  PORT_PLL_LOCK_THRESHOLD_MASK	(0x7 << PORT_PLL_LOCK_THRESHOLD_SHIFT)
/* PORT_PLL_10_A */
#घोषणा  PORT_PLL_DCO_AMP_OVR_EN_H	(1 << 27)
#घोषणा  PORT_PLL_DCO_AMP_DEFAULT	15
#घोषणा  PORT_PLL_DCO_AMP_MASK		0x3c00
#घोषणा  PORT_PLL_DCO_AMP(x)		((x) << 10)
#घोषणा _PORT_PLL_BASE(phy, ch)		_BXT_PHY_CH(phy, ch, \
						    _PORT_PLL_0_B, \
						    _PORT_PLL_0_C)
#घोषणा BXT_PORT_PLL(phy, ch, idx)	_MMIO(_PORT_PLL_BASE(phy, ch) + \
					      (idx) * 4)

/* BXT PHY common lane रेजिस्टरs */
#घोषणा _PORT_CL1CM_DW0_A		0x162000
#घोषणा _PORT_CL1CM_DW0_BC		0x6C000
#घोषणा   PHY_POWER_GOOD		(1 << 16)
#घोषणा   PHY_RESERVED			(1 << 7)
#घोषणा BXT_PORT_CL1CM_DW0(phy)		_BXT_PHY((phy), _PORT_CL1CM_DW0_BC)

#घोषणा _PORT_CL1CM_DW9_A		0x162024
#घोषणा _PORT_CL1CM_DW9_BC		0x6C024
#घोषणा   IREF0RC_OFFSET_SHIFT		8
#घोषणा   IREF0RC_OFFSET_MASK		(0xFF << IREF0RC_OFFSET_SHIFT)
#घोषणा BXT_PORT_CL1CM_DW9(phy)		_BXT_PHY((phy), _PORT_CL1CM_DW9_BC)

#घोषणा _PORT_CL1CM_DW10_A		0x162028
#घोषणा _PORT_CL1CM_DW10_BC		0x6C028
#घोषणा   IREF1RC_OFFSET_SHIFT		8
#घोषणा   IREF1RC_OFFSET_MASK		(0xFF << IREF1RC_OFFSET_SHIFT)
#घोषणा BXT_PORT_CL1CM_DW10(phy)	_BXT_PHY((phy), _PORT_CL1CM_DW10_BC)

#घोषणा _PORT_CL1CM_DW28_A		0x162070
#घोषणा _PORT_CL1CM_DW28_BC		0x6C070
#घोषणा   OCL1_POWER_DOWN_EN		(1 << 23)
#घोषणा   DW28_OLDO_DYN_PWR_DOWN_EN	(1 << 22)
#घोषणा   SUS_CLK_CONFIG		0x3
#घोषणा BXT_PORT_CL1CM_DW28(phy)	_BXT_PHY((phy), _PORT_CL1CM_DW28_BC)

#घोषणा _PORT_CL1CM_DW30_A		0x162078
#घोषणा _PORT_CL1CM_DW30_BC		0x6C078
#घोषणा   OCL2_LDOFUSE_PWR_DIS		(1 << 6)
#घोषणा BXT_PORT_CL1CM_DW30(phy)	_BXT_PHY((phy), _PORT_CL1CM_DW30_BC)

/*
 * CNL/ICL Port/COMBO-PHY Registers
 */
#घोषणा _ICL_COMBOPHY_A			0x162000
#घोषणा _ICL_COMBOPHY_B			0x6C000
#घोषणा _EHL_COMBOPHY_C			0x160000
#घोषणा _RKL_COMBOPHY_D			0x161000
#घोषणा _ADL_COMBOPHY_E			0x16B000

#घोषणा _ICL_COMBOPHY(phy)		_PICK(phy, _ICL_COMBOPHY_A, \
					      _ICL_COMBOPHY_B, \
					      _EHL_COMBOPHY_C, \
					      _RKL_COMBOPHY_D, \
					      _ADL_COMBOPHY_E)

/* CNL/ICL Port CL_DW रेजिस्टरs */
#घोषणा _ICL_PORT_CL_DW(dw, phy)	(_ICL_COMBOPHY(phy) + \
					 4 * (dw))

#घोषणा CNL_PORT_CL1CM_DW5		_MMIO(0x162014)
#घोषणा ICL_PORT_CL_DW5(phy)		_MMIO(_ICL_PORT_CL_DW(5, phy))
#घोषणा   CL_POWER_DOWN_ENABLE		(1 << 4)
#घोषणा   SUS_CLOCK_CONFIG		(3 << 0)

#घोषणा ICL_PORT_CL_DW10(phy)		_MMIO(_ICL_PORT_CL_DW(10, phy))
#घोषणा  PG_SEQ_DELAY_OVERRIDE_MASK	(3 << 25)
#घोषणा  PG_SEQ_DELAY_OVERRIDE_SHIFT	25
#घोषणा  PG_SEQ_DELAY_OVERRIDE_ENABLE	(1 << 24)
#घोषणा  PWR_UP_ALL_LANES		(0x0 << 4)
#घोषणा  PWR_DOWN_LN_3_2_1		(0xe << 4)
#घोषणा  PWR_DOWN_LN_3_2		(0xc << 4)
#घोषणा  PWR_DOWN_LN_3			(0x8 << 4)
#घोषणा  PWR_DOWN_LN_2_1_0		(0x7 << 4)
#घोषणा  PWR_DOWN_LN_1_0		(0x3 << 4)
#घोषणा  PWR_DOWN_LN_3_1		(0xa << 4)
#घोषणा  PWR_DOWN_LN_3_1_0		(0xb << 4)
#घोषणा  PWR_DOWN_LN_MASK		(0xf << 4)
#घोषणा  PWR_DOWN_LN_SHIFT		4
#घोषणा  EDP4K2K_MODE_OVRD_EN		(1 << 3)
#घोषणा  EDP4K2K_MODE_OVRD_OPTIMIZED	(1 << 2)

#घोषणा ICL_PORT_CL_DW12(phy)		_MMIO(_ICL_PORT_CL_DW(12, phy))
#घोषणा   ICL_LANE_ENABLE_AUX		(1 << 0)

/* CNL/ICL Port COMP_DW रेजिस्टरs */
#घोषणा _ICL_PORT_COMP			0x100
#घोषणा _ICL_PORT_COMP_DW(dw, phy)	(_ICL_COMBOPHY(phy) + \
					 _ICL_PORT_COMP + 4 * (dw))

#घोषणा CNL_PORT_COMP_DW0		_MMIO(0x162100)
#घोषणा ICL_PORT_COMP_DW0(phy)		_MMIO(_ICL_PORT_COMP_DW(0, phy))
#घोषणा   COMP_INIT			(1 << 31)

#घोषणा CNL_PORT_COMP_DW1		_MMIO(0x162104)
#घोषणा ICL_PORT_COMP_DW1(phy)		_MMIO(_ICL_PORT_COMP_DW(1, phy))

#घोषणा CNL_PORT_COMP_DW3		_MMIO(0x16210c)
#घोषणा ICL_PORT_COMP_DW3(phy)		_MMIO(_ICL_PORT_COMP_DW(3, phy))
#घोषणा   PROCESS_INFO_DOT_0		(0 << 26)
#घोषणा   PROCESS_INFO_DOT_1		(1 << 26)
#घोषणा   PROCESS_INFO_DOT_4		(2 << 26)
#घोषणा   PROCESS_INFO_MASK		(7 << 26)
#घोषणा   PROCESS_INFO_SHIFT		26
#घोषणा   VOLTAGE_INFO_0_85V		(0 << 24)
#घोषणा   VOLTAGE_INFO_0_95V		(1 << 24)
#घोषणा   VOLTAGE_INFO_1_05V		(2 << 24)
#घोषणा   VOLTAGE_INFO_MASK		(3 << 24)
#घोषणा   VOLTAGE_INFO_SHIFT		24

#घोषणा ICL_PORT_COMP_DW8(phy)		_MMIO(_ICL_PORT_COMP_DW(8, phy))
#घोषणा   IREFGEN			(1 << 24)

#घोषणा CNL_PORT_COMP_DW9		_MMIO(0x162124)
#घोषणा ICL_PORT_COMP_DW9(phy)		_MMIO(_ICL_PORT_COMP_DW(9, phy))

#घोषणा CNL_PORT_COMP_DW10		_MMIO(0x162128)
#घोषणा ICL_PORT_COMP_DW10(phy)		_MMIO(_ICL_PORT_COMP_DW(10, phy))

/* CNL/ICL Port PCS रेजिस्टरs */
#घोषणा _CNL_PORT_PCS_DW1_GRP_AE	0x162304
#घोषणा _CNL_PORT_PCS_DW1_GRP_B		0x162384
#घोषणा _CNL_PORT_PCS_DW1_GRP_C		0x162B04
#घोषणा _CNL_PORT_PCS_DW1_GRP_D		0x162B84
#घोषणा _CNL_PORT_PCS_DW1_GRP_F		0x162A04
#घोषणा _CNL_PORT_PCS_DW1_LN0_AE	0x162404
#घोषणा _CNL_PORT_PCS_DW1_LN0_B		0x162604
#घोषणा _CNL_PORT_PCS_DW1_LN0_C		0x162C04
#घोषणा _CNL_PORT_PCS_DW1_LN0_D		0x162E04
#घोषणा _CNL_PORT_PCS_DW1_LN0_F		0x162804
#घोषणा CNL_PORT_PCS_DW1_GRP(phy)	_MMIO(_PICK(phy, \
						    _CNL_PORT_PCS_DW1_GRP_AE, \
						    _CNL_PORT_PCS_DW1_GRP_B, \
						    _CNL_PORT_PCS_DW1_GRP_C, \
						    _CNL_PORT_PCS_DW1_GRP_D, \
						    _CNL_PORT_PCS_DW1_GRP_AE, \
						    _CNL_PORT_PCS_DW1_GRP_F))
#घोषणा CNL_PORT_PCS_DW1_LN0(phy)	_MMIO(_PICK(phy, \
						    _CNL_PORT_PCS_DW1_LN0_AE, \
						    _CNL_PORT_PCS_DW1_LN0_B, \
						    _CNL_PORT_PCS_DW1_LN0_C, \
						    _CNL_PORT_PCS_DW1_LN0_D, \
						    _CNL_PORT_PCS_DW1_LN0_AE, \
						    _CNL_PORT_PCS_DW1_LN0_F))

#घोषणा _ICL_PORT_PCS_AUX		0x300
#घोषणा _ICL_PORT_PCS_GRP		0x600
#घोषणा _ICL_PORT_PCS_LN(ln)		(0x800 + (ln) * 0x100)
#घोषणा _ICL_PORT_PCS_DW_AUX(dw, phy)	(_ICL_COMBOPHY(phy) + \
					 _ICL_PORT_PCS_AUX + 4 * (dw))
#घोषणा _ICL_PORT_PCS_DW_GRP(dw, phy)	(_ICL_COMBOPHY(phy) + \
					 _ICL_PORT_PCS_GRP + 4 * (dw))
#घोषणा _ICL_PORT_PCS_DW_LN(dw, ln, phy) (_ICL_COMBOPHY(phy) + \
					  _ICL_PORT_PCS_LN(ln) + 4 * (dw))
#घोषणा ICL_PORT_PCS_DW1_AUX(phy)	_MMIO(_ICL_PORT_PCS_DW_AUX(1, phy))
#घोषणा ICL_PORT_PCS_DW1_GRP(phy)	_MMIO(_ICL_PORT_PCS_DW_GRP(1, phy))
#घोषणा ICL_PORT_PCS_DW1_LN0(phy)	_MMIO(_ICL_PORT_PCS_DW_LN(1, 0, phy))
#घोषणा   DCC_MODE_SELECT_MASK		(0x3 << 20)
#घोषणा   DCC_MODE_SELECT_CONTINUOSLY	(0x3 << 20)
#घोषणा   COMMON_KEEPER_EN		(1 << 26)
#घोषणा   LATENCY_OPTIM_MASK		(0x3 << 2)
#घोषणा   LATENCY_OPTIM_VAL(x)		((x) << 2)

/* CNL/ICL Port TX रेजिस्टरs */
#घोषणा _CNL_PORT_TX_AE_GRP_OFFSET		0x162340
#घोषणा _CNL_PORT_TX_B_GRP_OFFSET		0x1623C0
#घोषणा _CNL_PORT_TX_C_GRP_OFFSET		0x162B40
#घोषणा _CNL_PORT_TX_D_GRP_OFFSET		0x162BC0
#घोषणा _CNL_PORT_TX_F_GRP_OFFSET		0x162A40
#घोषणा _CNL_PORT_TX_AE_LN0_OFFSET		0x162440
#घोषणा _CNL_PORT_TX_B_LN0_OFFSET		0x162640
#घोषणा _CNL_PORT_TX_C_LN0_OFFSET		0x162C40
#घोषणा _CNL_PORT_TX_D_LN0_OFFSET		0x162E40
#घोषणा _CNL_PORT_TX_F_LN0_OFFSET		0x162840
#घोषणा _CNL_PORT_TX_DW_GRP(dw, port)	(_PICK((port), \
					       _CNL_PORT_TX_AE_GRP_OFFSET, \
					       _CNL_PORT_TX_B_GRP_OFFSET, \
					       _CNL_PORT_TX_B_GRP_OFFSET, \
					       _CNL_PORT_TX_D_GRP_OFFSET, \
					       _CNL_PORT_TX_AE_GRP_OFFSET, \
					       _CNL_PORT_TX_F_GRP_OFFSET) + \
					       4 * (dw))
#घोषणा _CNL_PORT_TX_DW_LN0(dw, port)	(_PICK((port), \
					       _CNL_PORT_TX_AE_LN0_OFFSET, \
					       _CNL_PORT_TX_B_LN0_OFFSET, \
					       _CNL_PORT_TX_B_LN0_OFFSET, \
					       _CNL_PORT_TX_D_LN0_OFFSET, \
					       _CNL_PORT_TX_AE_LN0_OFFSET, \
					       _CNL_PORT_TX_F_LN0_OFFSET) + \
					       4 * (dw))

#घोषणा _ICL_PORT_TX_AUX		0x380
#घोषणा _ICL_PORT_TX_GRP		0x680
#घोषणा _ICL_PORT_TX_LN(ln)		(0x880 + (ln) * 0x100)

#घोषणा _ICL_PORT_TX_DW_AUX(dw, phy)	(_ICL_COMBOPHY(phy) + \
					 _ICL_PORT_TX_AUX + 4 * (dw))
#घोषणा _ICL_PORT_TX_DW_GRP(dw, phy)	(_ICL_COMBOPHY(phy) + \
					 _ICL_PORT_TX_GRP + 4 * (dw))
#घोषणा _ICL_PORT_TX_DW_LN(dw, ln, phy) (_ICL_COMBOPHY(phy) + \
					  _ICL_PORT_TX_LN(ln) + 4 * (dw))

#घोषणा CNL_PORT_TX_DW2_GRP(port)	_MMIO(_CNL_PORT_TX_DW_GRP(2, port))
#घोषणा CNL_PORT_TX_DW2_LN0(port)	_MMIO(_CNL_PORT_TX_DW_LN0(2, port))
#घोषणा ICL_PORT_TX_DW2_AUX(phy)	_MMIO(_ICL_PORT_TX_DW_AUX(2, phy))
#घोषणा ICL_PORT_TX_DW2_GRP(phy)	_MMIO(_ICL_PORT_TX_DW_GRP(2, phy))
#घोषणा ICL_PORT_TX_DW2_LN0(phy)	_MMIO(_ICL_PORT_TX_DW_LN(2, 0, phy))
#घोषणा   SWING_SEL_UPPER(x)		(((x) >> 3) << 15)
#घोषणा   SWING_SEL_UPPER_MASK		(1 << 15)
#घोषणा   SWING_SEL_LOWER(x)		(((x) & 0x7) << 11)
#घोषणा   SWING_SEL_LOWER_MASK		(0x7 << 11)
#घोषणा   FRC_LATENCY_OPTIM_MASK	(0x7 << 8)
#घोषणा   FRC_LATENCY_OPTIM_VAL(x)	((x) << 8)
#घोषणा   RCOMP_SCALAR(x)		((x) << 0)
#घोषणा   RCOMP_SCALAR_MASK		(0xFF << 0)

#घोषणा _CNL_PORT_TX_DW4_LN0_AE		0x162450
#घोषणा _CNL_PORT_TX_DW4_LN1_AE		0x1624D0
#घोषणा CNL_PORT_TX_DW4_GRP(port)	_MMIO(_CNL_PORT_TX_DW_GRP(4, (port)))
#घोषणा CNL_PORT_TX_DW4_LN0(port)	_MMIO(_CNL_PORT_TX_DW_LN0(4, (port)))
#घोषणा CNL_PORT_TX_DW4_LN(ln, port)   _MMIO(_CNL_PORT_TX_DW_LN0(4, (port)) + \
					   ((ln) * (_CNL_PORT_TX_DW4_LN1_AE - \
						    _CNL_PORT_TX_DW4_LN0_AE)))
#घोषणा ICL_PORT_TX_DW4_AUX(phy)	_MMIO(_ICL_PORT_TX_DW_AUX(4, phy))
#घोषणा ICL_PORT_TX_DW4_GRP(phy)	_MMIO(_ICL_PORT_TX_DW_GRP(4, phy))
#घोषणा ICL_PORT_TX_DW4_LN0(phy)	_MMIO(_ICL_PORT_TX_DW_LN(4, 0, phy))
#घोषणा ICL_PORT_TX_DW4_LN(ln, phy)	_MMIO(_ICL_PORT_TX_DW_LN(4, ln, phy))
#घोषणा   LOADGEN_SELECT		(1 << 31)
#घोषणा   POST_CURSOR_1(x)		((x) << 12)
#घोषणा   POST_CURSOR_1_MASK		(0x3F << 12)
#घोषणा   POST_CURSOR_2(x)		((x) << 6)
#घोषणा   POST_CURSOR_2_MASK		(0x3F << 6)
#घोषणा   CURSOR_COEFF(x)		((x) << 0)
#घोषणा   CURSOR_COEFF_MASK		(0x3F << 0)

#घोषणा CNL_PORT_TX_DW5_GRP(port)	_MMIO(_CNL_PORT_TX_DW_GRP(5, port))
#घोषणा CNL_PORT_TX_DW5_LN0(port)	_MMIO(_CNL_PORT_TX_DW_LN0(5, port))
#घोषणा ICL_PORT_TX_DW5_AUX(phy)	_MMIO(_ICL_PORT_TX_DW_AUX(5, phy))
#घोषणा ICL_PORT_TX_DW5_GRP(phy)	_MMIO(_ICL_PORT_TX_DW_GRP(5, phy))
#घोषणा ICL_PORT_TX_DW5_LN0(phy)	_MMIO(_ICL_PORT_TX_DW_LN(5, 0, phy))
#घोषणा   TX_TRAINING_EN		(1 << 31)
#घोषणा   TAP2_DISABLE			(1 << 30)
#घोषणा   TAP3_DISABLE			(1 << 29)
#घोषणा   SCALING_MODE_SEL(x)		((x) << 18)
#घोषणा   SCALING_MODE_SEL_MASK		(0x7 << 18)
#घोषणा   RTERM_SELECT(x)		((x) << 3)
#घोषणा   RTERM_SELECT_MASK		(0x7 << 3)

#घोषणा CNL_PORT_TX_DW7_GRP(port)	_MMIO(_CNL_PORT_TX_DW_GRP(7, (port)))
#घोषणा CNL_PORT_TX_DW7_LN0(port)	_MMIO(_CNL_PORT_TX_DW_LN0(7, (port)))
#घोषणा ICL_PORT_TX_DW7_AUX(phy)	_MMIO(_ICL_PORT_TX_DW_AUX(7, phy))
#घोषणा ICL_PORT_TX_DW7_GRP(phy)	_MMIO(_ICL_PORT_TX_DW_GRP(7, phy))
#घोषणा ICL_PORT_TX_DW7_LN0(phy)	_MMIO(_ICL_PORT_TX_DW_LN(7, 0, phy))
#घोषणा ICL_PORT_TX_DW7_LN(ln, phy)	_MMIO(_ICL_PORT_TX_DW_LN(7, ln, phy))
#घोषणा   N_SCALAR(x)			((x) << 24)
#घोषणा   N_SCALAR_MASK			(0x7F << 24)

#घोषणा ICL_PORT_TX_DW8_AUX(phy)		_MMIO(_ICL_PORT_TX_DW_AUX(8, phy))
#घोषणा ICL_PORT_TX_DW8_GRP(phy)		_MMIO(_ICL_PORT_TX_DW_GRP(8, phy))
#घोषणा ICL_PORT_TX_DW8_LN0(phy)		_MMIO(_ICL_PORT_TX_DW_LN(8, 0, phy))
#घोषणा   ICL_PORT_TX_DW8_ODCC_CLK_SEL		REG_BIT(31)
#घोषणा   ICL_PORT_TX_DW8_ODCC_CLK_DIV_SEL_MASK	REG_GENMASK(30, 29)
#घोषणा   ICL_PORT_TX_DW8_ODCC_CLK_DIV_SEL_DIV2	REG_FIELD_PREP(ICL_PORT_TX_DW8_ODCC_CLK_DIV_SEL_MASK, 0x1)

#घोषणा _ICL_DPHY_CHKN_REG			0x194
#घोषणा ICL_DPHY_CHKN(port)			_MMIO(_ICL_COMBOPHY(port) + _ICL_DPHY_CHKN_REG)
#घोषणा   ICL_DPHY_CHKN_AFE_OVER_PPI_STRAP	REG_BIT(7)

#घोषणा MG_PHY_PORT_LN(ln, tc_port, ln0p1, ln0p2, ln1p1) \
	_MMIO(_PORT(tc_port, ln0p1, ln0p2) + (ln) * ((ln1p1) - (ln0p1)))

#घोषणा MG_TX_LINK_PARAMS_TX1LN0_PORT1		0x16812C
#घोषणा MG_TX_LINK_PARAMS_TX1LN1_PORT1		0x16852C
#घोषणा MG_TX_LINK_PARAMS_TX1LN0_PORT2		0x16912C
#घोषणा MG_TX_LINK_PARAMS_TX1LN1_PORT2		0x16952C
#घोषणा MG_TX_LINK_PARAMS_TX1LN0_PORT3		0x16A12C
#घोषणा MG_TX_LINK_PARAMS_TX1LN1_PORT3		0x16A52C
#घोषणा MG_TX_LINK_PARAMS_TX1LN0_PORT4		0x16B12C
#घोषणा MG_TX_LINK_PARAMS_TX1LN1_PORT4		0x16B52C
#घोषणा MG_TX1_LINK_PARAMS(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_LINK_PARAMS_TX1LN0_PORT1, \
				    MG_TX_LINK_PARAMS_TX1LN0_PORT2, \
				    MG_TX_LINK_PARAMS_TX1LN1_PORT1)

#घोषणा MG_TX_LINK_PARAMS_TX2LN0_PORT1		0x1680AC
#घोषणा MG_TX_LINK_PARAMS_TX2LN1_PORT1		0x1684AC
#घोषणा MG_TX_LINK_PARAMS_TX2LN0_PORT2		0x1690AC
#घोषणा MG_TX_LINK_PARAMS_TX2LN1_PORT2		0x1694AC
#घोषणा MG_TX_LINK_PARAMS_TX2LN0_PORT3		0x16A0AC
#घोषणा MG_TX_LINK_PARAMS_TX2LN1_PORT3		0x16A4AC
#घोषणा MG_TX_LINK_PARAMS_TX2LN0_PORT4		0x16B0AC
#घोषणा MG_TX_LINK_PARAMS_TX2LN1_PORT4		0x16B4AC
#घोषणा MG_TX2_LINK_PARAMS(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_LINK_PARAMS_TX2LN0_PORT1, \
				    MG_TX_LINK_PARAMS_TX2LN0_PORT2, \
				    MG_TX_LINK_PARAMS_TX2LN1_PORT1)
#घोषणा   CRI_USE_FS32			(1 << 5)

#घोषणा MG_TX_PISO_READLOAD_TX1LN0_PORT1		0x16814C
#घोषणा MG_TX_PISO_READLOAD_TX1LN1_PORT1		0x16854C
#घोषणा MG_TX_PISO_READLOAD_TX1LN0_PORT2		0x16914C
#घोषणा MG_TX_PISO_READLOAD_TX1LN1_PORT2		0x16954C
#घोषणा MG_TX_PISO_READLOAD_TX1LN0_PORT3		0x16A14C
#घोषणा MG_TX_PISO_READLOAD_TX1LN1_PORT3		0x16A54C
#घोषणा MG_TX_PISO_READLOAD_TX1LN0_PORT4		0x16B14C
#घोषणा MG_TX_PISO_READLOAD_TX1LN1_PORT4		0x16B54C
#घोषणा MG_TX1_PISO_READLOAD(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_PISO_READLOAD_TX1LN0_PORT1, \
				    MG_TX_PISO_READLOAD_TX1LN0_PORT2, \
				    MG_TX_PISO_READLOAD_TX1LN1_PORT1)

#घोषणा MG_TX_PISO_READLOAD_TX2LN0_PORT1		0x1680CC
#घोषणा MG_TX_PISO_READLOAD_TX2LN1_PORT1		0x1684CC
#घोषणा MG_TX_PISO_READLOAD_TX2LN0_PORT2		0x1690CC
#घोषणा MG_TX_PISO_READLOAD_TX2LN1_PORT2		0x1694CC
#घोषणा MG_TX_PISO_READLOAD_TX2LN0_PORT3		0x16A0CC
#घोषणा MG_TX_PISO_READLOAD_TX2LN1_PORT3		0x16A4CC
#घोषणा MG_TX_PISO_READLOAD_TX2LN0_PORT4		0x16B0CC
#घोषणा MG_TX_PISO_READLOAD_TX2LN1_PORT4		0x16B4CC
#घोषणा MG_TX2_PISO_READLOAD(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_PISO_READLOAD_TX2LN0_PORT1, \
				    MG_TX_PISO_READLOAD_TX2LN0_PORT2, \
				    MG_TX_PISO_READLOAD_TX2LN1_PORT1)
#घोषणा   CRI_CALCINIT					(1 << 1)

#घोषणा MG_TX_SWINGCTRL_TX1LN0_PORT1		0x168148
#घोषणा MG_TX_SWINGCTRL_TX1LN1_PORT1		0x168548
#घोषणा MG_TX_SWINGCTRL_TX1LN0_PORT2		0x169148
#घोषणा MG_TX_SWINGCTRL_TX1LN1_PORT2		0x169548
#घोषणा MG_TX_SWINGCTRL_TX1LN0_PORT3		0x16A148
#घोषणा MG_TX_SWINGCTRL_TX1LN1_PORT3		0x16A548
#घोषणा MG_TX_SWINGCTRL_TX1LN0_PORT4		0x16B148
#घोषणा MG_TX_SWINGCTRL_TX1LN1_PORT4		0x16B548
#घोषणा MG_TX1_SWINGCTRL(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_SWINGCTRL_TX1LN0_PORT1, \
				    MG_TX_SWINGCTRL_TX1LN0_PORT2, \
				    MG_TX_SWINGCTRL_TX1LN1_PORT1)

#घोषणा MG_TX_SWINGCTRL_TX2LN0_PORT1		0x1680C8
#घोषणा MG_TX_SWINGCTRL_TX2LN1_PORT1		0x1684C8
#घोषणा MG_TX_SWINGCTRL_TX2LN0_PORT2		0x1690C8
#घोषणा MG_TX_SWINGCTRL_TX2LN1_PORT2		0x1694C8
#घोषणा MG_TX_SWINGCTRL_TX2LN0_PORT3		0x16A0C8
#घोषणा MG_TX_SWINGCTRL_TX2LN1_PORT3		0x16A4C8
#घोषणा MG_TX_SWINGCTRL_TX2LN0_PORT4		0x16B0C8
#घोषणा MG_TX_SWINGCTRL_TX2LN1_PORT4		0x16B4C8
#घोषणा MG_TX2_SWINGCTRL(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_SWINGCTRL_TX2LN0_PORT1, \
				    MG_TX_SWINGCTRL_TX2LN0_PORT2, \
				    MG_TX_SWINGCTRL_TX2LN1_PORT1)
#घोषणा   CRI_TXDEEMPH_OVERRIDE_17_12(x)		((x) << 0)
#घोषणा   CRI_TXDEEMPH_OVERRIDE_17_12_MASK		(0x3F << 0)

#घोषणा MG_TX_DRVCTRL_TX1LN0_TXPORT1			0x168144
#घोषणा MG_TX_DRVCTRL_TX1LN1_TXPORT1			0x168544
#घोषणा MG_TX_DRVCTRL_TX1LN0_TXPORT2			0x169144
#घोषणा MG_TX_DRVCTRL_TX1LN1_TXPORT2			0x169544
#घोषणा MG_TX_DRVCTRL_TX1LN0_TXPORT3			0x16A144
#घोषणा MG_TX_DRVCTRL_TX1LN1_TXPORT3			0x16A544
#घोषणा MG_TX_DRVCTRL_TX1LN0_TXPORT4			0x16B144
#घोषणा MG_TX_DRVCTRL_TX1LN1_TXPORT4			0x16B544
#घोषणा MG_TX1_DRVCTRL(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_DRVCTRL_TX1LN0_TXPORT1, \
				    MG_TX_DRVCTRL_TX1LN0_TXPORT2, \
				    MG_TX_DRVCTRL_TX1LN1_TXPORT1)

#घोषणा MG_TX_DRVCTRL_TX2LN0_PORT1			0x1680C4
#घोषणा MG_TX_DRVCTRL_TX2LN1_PORT1			0x1684C4
#घोषणा MG_TX_DRVCTRL_TX2LN0_PORT2			0x1690C4
#घोषणा MG_TX_DRVCTRL_TX2LN1_PORT2			0x1694C4
#घोषणा MG_TX_DRVCTRL_TX2LN0_PORT3			0x16A0C4
#घोषणा MG_TX_DRVCTRL_TX2LN1_PORT3			0x16A4C4
#घोषणा MG_TX_DRVCTRL_TX2LN0_PORT4			0x16B0C4
#घोषणा MG_TX_DRVCTRL_TX2LN1_PORT4			0x16B4C4
#घोषणा MG_TX2_DRVCTRL(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_DRVCTRL_TX2LN0_PORT1, \
				    MG_TX_DRVCTRL_TX2LN0_PORT2, \
				    MG_TX_DRVCTRL_TX2LN1_PORT1)
#घोषणा   CRI_TXDEEMPH_OVERRIDE_11_6(x)			((x) << 24)
#घोषणा   CRI_TXDEEMPH_OVERRIDE_11_6_MASK		(0x3F << 24)
#घोषणा   CRI_TXDEEMPH_OVERRIDE_EN			(1 << 22)
#घोषणा   CRI_TXDEEMPH_OVERRIDE_5_0(x)			((x) << 16)
#घोषणा   CRI_TXDEEMPH_OVERRIDE_5_0_MASK		(0x3F << 16)
#घोषणा   CRI_LOADGEN_SEL(x)				((x) << 12)
#घोषणा   CRI_LOADGEN_SEL_MASK				(0x3 << 12)

#घोषणा MG_CLKHUB_LN0_PORT1			0x16839C
#घोषणा MG_CLKHUB_LN1_PORT1			0x16879C
#घोषणा MG_CLKHUB_LN0_PORT2			0x16939C
#घोषणा MG_CLKHUB_LN1_PORT2			0x16979C
#घोषणा MG_CLKHUB_LN0_PORT3			0x16A39C
#घोषणा MG_CLKHUB_LN1_PORT3			0x16A79C
#घोषणा MG_CLKHUB_LN0_PORT4			0x16B39C
#घोषणा MG_CLKHUB_LN1_PORT4			0x16B79C
#घोषणा MG_CLKHUB(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_CLKHUB_LN0_PORT1, \
				    MG_CLKHUB_LN0_PORT2, \
				    MG_CLKHUB_LN1_PORT1)
#घोषणा   CFG_LOW_RATE_LKREN_EN				(1 << 11)

#घोषणा MG_TX_DCC_TX1LN0_PORT1			0x168110
#घोषणा MG_TX_DCC_TX1LN1_PORT1			0x168510
#घोषणा MG_TX_DCC_TX1LN0_PORT2			0x169110
#घोषणा MG_TX_DCC_TX1LN1_PORT2			0x169510
#घोषणा MG_TX_DCC_TX1LN0_PORT3			0x16A110
#घोषणा MG_TX_DCC_TX1LN1_PORT3			0x16A510
#घोषणा MG_TX_DCC_TX1LN0_PORT4			0x16B110
#घोषणा MG_TX_DCC_TX1LN1_PORT4			0x16B510
#घोषणा MG_TX1_DCC(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_DCC_TX1LN0_PORT1, \
				    MG_TX_DCC_TX1LN0_PORT2, \
				    MG_TX_DCC_TX1LN1_PORT1)
#घोषणा MG_TX_DCC_TX2LN0_PORT1			0x168090
#घोषणा MG_TX_DCC_TX2LN1_PORT1			0x168490
#घोषणा MG_TX_DCC_TX2LN0_PORT2			0x169090
#घोषणा MG_TX_DCC_TX2LN1_PORT2			0x169490
#घोषणा MG_TX_DCC_TX2LN0_PORT3			0x16A090
#घोषणा MG_TX_DCC_TX2LN1_PORT3			0x16A490
#घोषणा MG_TX_DCC_TX2LN0_PORT4			0x16B090
#घोषणा MG_TX_DCC_TX2LN1_PORT4			0x16B490
#घोषणा MG_TX2_DCC(ln, tc_port) \
	MG_PHY_PORT_LN(ln, tc_port, MG_TX_DCC_TX2LN0_PORT1, \
				    MG_TX_DCC_TX2LN0_PORT2, \
				    MG_TX_DCC_TX2LN1_PORT1)
#घोषणा   CFG_AMI_CK_DIV_OVERRIDE_VAL(x)	((x) << 25)
#घोषणा   CFG_AMI_CK_DIV_OVERRIDE_VAL_MASK	(0x3 << 25)
#घोषणा   CFG_AMI_CK_DIV_OVERRIDE_EN		(1 << 24)

#घोषणा MG_DP_MODE_LN0_ACU_PORT1			0x1683A0
#घोषणा MG_DP_MODE_LN1_ACU_PORT1			0x1687A0
#घोषणा MG_DP_MODE_LN0_ACU_PORT2			0x1693A0
#घोषणा MG_DP_MODE_LN1_ACU_PORT2			0x1697A0
#घोषणा MG_DP_MODE_LN0_ACU_PORT3			0x16A3A0
#घोषणा MG_DP_MODE_LN1_ACU_PORT3			0x16A7A0
#घोषणा MG_DP_MODE_LN0_ACU_PORT4			0x16B3A0
#घोषणा MG_DP_MODE_LN1_ACU_PORT4			0x16B7A0
#घोषणा MG_DP_MODE(ln, tc_port)	\
	MG_PHY_PORT_LN(ln, tc_port, MG_DP_MODE_LN0_ACU_PORT1, \
				    MG_DP_MODE_LN0_ACU_PORT2, \
				    MG_DP_MODE_LN1_ACU_PORT1)
#घोषणा   MG_DP_MODE_CFG_DP_X2_MODE			(1 << 7)
#घोषणा   MG_DP_MODE_CFG_DP_X1_MODE			(1 << 6)

/* The spec defines this only क्रम BXT PHY0, but lets assume that this
 * would exist क्रम PHY1 too अगर it had a second channel.
 */
#घोषणा _PORT_CL2CM_DW6_A		0x162358
#घोषणा _PORT_CL2CM_DW6_BC		0x6C358
#घोषणा BXT_PORT_CL2CM_DW6(phy)		_BXT_PHY((phy), _PORT_CL2CM_DW6_BC)
#घोषणा   DW6_OLDO_DYN_PWR_DOWN_EN	(1 << 28)

#घोषणा FIA1_BASE			0x163000
#घोषणा FIA2_BASE			0x16E000
#घोषणा FIA3_BASE			0x16F000
#घोषणा _FIA(fia)			_PICK((fia), FIA1_BASE, FIA2_BASE, FIA3_BASE)
#घोषणा _MMIO_FIA(fia, off)		_MMIO(_FIA(fia) + (off))

/* ICL PHY DFLEX रेजिस्टरs */
#घोषणा PORT_TX_DFLEXDPMLE1(fia)		_MMIO_FIA((fia),  0x008C0)
#घोषणा   DFLEXDPMLE1_DPMLETC_MASK(idx)		(0xf << (4 * (idx)))
#घोषणा   DFLEXDPMLE1_DPMLETC_ML0(idx)		(1 << (4 * (idx)))
#घोषणा   DFLEXDPMLE1_DPMLETC_ML1_0(idx)	(3 << (4 * (idx)))
#घोषणा   DFLEXDPMLE1_DPMLETC_ML3(idx)		(8 << (4 * (idx)))
#घोषणा   DFLEXDPMLE1_DPMLETC_ML3_2(idx)	(12 << (4 * (idx)))
#घोषणा   DFLEXDPMLE1_DPMLETC_ML3_0(idx)	(15 << (4 * (idx)))

/* BXT PHY Ref रेजिस्टरs */
#घोषणा _PORT_REF_DW3_A			0x16218C
#घोषणा _PORT_REF_DW3_BC		0x6C18C
#घोषणा   GRC_DONE			(1 << 22)
#घोषणा BXT_PORT_REF_DW3(phy)		_BXT_PHY((phy), _PORT_REF_DW3_BC)

#घोषणा _PORT_REF_DW6_A			0x162198
#घोषणा _PORT_REF_DW6_BC		0x6C198
#घोषणा   GRC_CODE_SHIFT		24
#घोषणा   GRC_CODE_MASK			(0xFF << GRC_CODE_SHIFT)
#घोषणा   GRC_CODE_FAST_SHIFT		16
#घोषणा   GRC_CODE_FAST_MASK		(0xFF << GRC_CODE_FAST_SHIFT)
#घोषणा   GRC_CODE_SLOW_SHIFT		8
#घोषणा   GRC_CODE_SLOW_MASK		(0xFF << GRC_CODE_SLOW_SHIFT)
#घोषणा   GRC_CODE_NOM_MASK		0xFF
#घोषणा BXT_PORT_REF_DW6(phy)		_BXT_PHY((phy), _PORT_REF_DW6_BC)

#घोषणा _PORT_REF_DW8_A			0x1621A0
#घोषणा _PORT_REF_DW8_BC		0x6C1A0
#घोषणा   GRC_DIS			(1 << 15)
#घोषणा   GRC_RDY_OVRD			(1 << 1)
#घोषणा BXT_PORT_REF_DW8(phy)		_BXT_PHY((phy), _PORT_REF_DW8_BC)

/* BXT PHY PCS रेजिस्टरs */
#घोषणा _PORT_PCS_DW10_LN01_A		0x162428
#घोषणा _PORT_PCS_DW10_LN01_B		0x6C428
#घोषणा _PORT_PCS_DW10_LN01_C		0x6C828
#घोषणा _PORT_PCS_DW10_GRP_A		0x162C28
#घोषणा _PORT_PCS_DW10_GRP_B		0x6CC28
#घोषणा _PORT_PCS_DW10_GRP_C		0x6CE28
#घोषणा BXT_PORT_PCS_DW10_LN01(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_PCS_DW10_LN01_B, \
							 _PORT_PCS_DW10_LN01_C)
#घोषणा BXT_PORT_PCS_DW10_GRP(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_PCS_DW10_GRP_B, \
							 _PORT_PCS_DW10_GRP_C)

#घोषणा   TX2_SWING_CALC_INIT		(1 << 31)
#घोषणा   TX1_SWING_CALC_INIT		(1 << 30)

#घोषणा _PORT_PCS_DW12_LN01_A		0x162430
#घोषणा _PORT_PCS_DW12_LN01_B		0x6C430
#घोषणा _PORT_PCS_DW12_LN01_C		0x6C830
#घोषणा _PORT_PCS_DW12_LN23_A		0x162630
#घोषणा _PORT_PCS_DW12_LN23_B		0x6C630
#घोषणा _PORT_PCS_DW12_LN23_C		0x6CA30
#घोषणा _PORT_PCS_DW12_GRP_A		0x162c30
#घोषणा _PORT_PCS_DW12_GRP_B		0x6CC30
#घोषणा _PORT_PCS_DW12_GRP_C		0x6CE30
#घोषणा   LANESTAGGER_STRAP_OVRD	(1 << 6)
#घोषणा   LANE_STAGGER_MASK		0x1F
#घोषणा BXT_PORT_PCS_DW12_LN01(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_PCS_DW12_LN01_B, \
							 _PORT_PCS_DW12_LN01_C)
#घोषणा BXT_PORT_PCS_DW12_LN23(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_PCS_DW12_LN23_B, \
							 _PORT_PCS_DW12_LN23_C)
#घोषणा BXT_PORT_PCS_DW12_GRP(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_PCS_DW12_GRP_B, \
							 _PORT_PCS_DW12_GRP_C)

/* BXT PHY TX रेजिस्टरs */
#घोषणा _BXT_LANE_OFFSET(lane)           (((lane) >> 1) * 0x200 +	\
					  ((lane) & 1) * 0x80)

#घोषणा _PORT_TX_DW2_LN0_A		0x162508
#घोषणा _PORT_TX_DW2_LN0_B		0x6C508
#घोषणा _PORT_TX_DW2_LN0_C		0x6C908
#घोषणा _PORT_TX_DW2_GRP_A		0x162D08
#घोषणा _PORT_TX_DW2_GRP_B		0x6CD08
#घोषणा _PORT_TX_DW2_GRP_C		0x6CF08
#घोषणा BXT_PORT_TX_DW2_LN0(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_TX_DW2_LN0_B, \
							 _PORT_TX_DW2_LN0_C)
#घोषणा BXT_PORT_TX_DW2_GRP(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_TX_DW2_GRP_B, \
							 _PORT_TX_DW2_GRP_C)
#घोषणा   MARGIN_000_SHIFT		16
#घोषणा   MARGIN_000			(0xFF << MARGIN_000_SHIFT)
#घोषणा   UNIQ_TRANS_SCALE_SHIFT	8
#घोषणा   UNIQ_TRANS_SCALE		(0xFF << UNIQ_TRANS_SCALE_SHIFT)

#घोषणा _PORT_TX_DW3_LN0_A		0x16250C
#घोषणा _PORT_TX_DW3_LN0_B		0x6C50C
#घोषणा _PORT_TX_DW3_LN0_C		0x6C90C
#घोषणा _PORT_TX_DW3_GRP_A		0x162D0C
#घोषणा _PORT_TX_DW3_GRP_B		0x6CD0C
#घोषणा _PORT_TX_DW3_GRP_C		0x6CF0C
#घोषणा BXT_PORT_TX_DW3_LN0(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_TX_DW3_LN0_B, \
							 _PORT_TX_DW3_LN0_C)
#घोषणा BXT_PORT_TX_DW3_GRP(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_TX_DW3_GRP_B, \
							 _PORT_TX_DW3_GRP_C)
#घोषणा   SCALE_DCOMP_METHOD		(1 << 26)
#घोषणा   UNIQUE_TRANGE_EN_METHOD	(1 << 27)

#घोषणा _PORT_TX_DW4_LN0_A		0x162510
#घोषणा _PORT_TX_DW4_LN0_B		0x6C510
#घोषणा _PORT_TX_DW4_LN0_C		0x6C910
#घोषणा _PORT_TX_DW4_GRP_A		0x162D10
#घोषणा _PORT_TX_DW4_GRP_B		0x6CD10
#घोषणा _PORT_TX_DW4_GRP_C		0x6CF10
#घोषणा BXT_PORT_TX_DW4_LN0(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_TX_DW4_LN0_B, \
							 _PORT_TX_DW4_LN0_C)
#घोषणा BXT_PORT_TX_DW4_GRP(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_TX_DW4_GRP_B, \
							 _PORT_TX_DW4_GRP_C)
#घोषणा   DEEMPH_SHIFT			24
#घोषणा   DE_EMPHASIS			(0xFF << DEEMPH_SHIFT)

#घोषणा _PORT_TX_DW5_LN0_A		0x162514
#घोषणा _PORT_TX_DW5_LN0_B		0x6C514
#घोषणा _PORT_TX_DW5_LN0_C		0x6C914
#घोषणा _PORT_TX_DW5_GRP_A		0x162D14
#घोषणा _PORT_TX_DW5_GRP_B		0x6CD14
#घोषणा _PORT_TX_DW5_GRP_C		0x6CF14
#घोषणा BXT_PORT_TX_DW5_LN0(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_TX_DW5_LN0_B, \
							 _PORT_TX_DW5_LN0_C)
#घोषणा BXT_PORT_TX_DW5_GRP(phy, ch)	_MMIO_BXT_PHY_CH(phy, ch, \
							 _PORT_TX_DW5_GRP_B, \
							 _PORT_TX_DW5_GRP_C)
#घोषणा   DCC_DELAY_RANGE_1		(1 << 9)
#घोषणा   DCC_DELAY_RANGE_2		(1 << 8)

#घोषणा _PORT_TX_DW14_LN0_A		0x162538
#घोषणा _PORT_TX_DW14_LN0_B		0x6C538
#घोषणा _PORT_TX_DW14_LN0_C		0x6C938
#घोषणा   LATENCY_OPTIM_SHIFT		30
#घोषणा   LATENCY_OPTIM			(1 << LATENCY_OPTIM_SHIFT)
#घोषणा BXT_PORT_TX_DW14_LN(phy, ch, lane)				\
	_MMIO(_BXT_PHY_CH(phy, ch, _PORT_TX_DW14_LN0_B,			\
				   _PORT_TX_DW14_LN0_C) +		\
	      _BXT_LANE_OFFSET(lane))

/* UAIMI scratch pad रेजिस्टर 1 */
#घोषणा UAIMI_SPR1			_MMIO(0x4F074)
/* SKL VccIO mask */
#घोषणा SKL_VCCIO_MASK			0x1
/* SKL balance leg रेजिस्टर */
#घोषणा DISPIO_CR_TX_BMU_CR0		_MMIO(0x6C00C)
/* I_boost values */
#घोषणा BALANCE_LEG_SHIFT(port)		(8 + 3 * (port))
#घोषणा BALANCE_LEG_MASK(port)		(7 << (8 + 3 * (port)))
/* Balance leg disable bits */
#घोषणा BALANCE_LEG_DISABLE_SHIFT	23
#घोषणा BALANCE_LEG_DISABLE(port)	(1 << (23 + (port)))

/*
 * Fence रेजिस्टरs
 * [0-7]  @ 0x2000 gen2,gen3
 * [8-15] @ 0x3000 945,g33,pnv
 *
 * [0-15] @ 0x3000 gen4,gen5
 *
 * [0-15] @ 0x100000 gen6,vlv,chv
 * [0-31] @ 0x100000 gen7+
 */
#घोषणा FENCE_REG(i)			_MMIO(0x2000 + (((i) & 8) << 9) + ((i) & 7) * 4)
#घोषणा   I830_FENCE_START_MASK		0x07f80000
#घोषणा   I830_FENCE_TILING_Y_SHIFT	12
#घोषणा   I830_FENCE_SIZE_BITS(size)	((ffs((size) >> 19) - 1) << 8)
#घोषणा   I830_FENCE_PITCH_SHIFT	4
#घोषणा   I830_FENCE_REG_VALID		(1 << 0)
#घोषणा   I915_FENCE_MAX_PITCH_VAL	4
#घोषणा   I830_FENCE_MAX_PITCH_VAL	6
#घोषणा   I830_FENCE_MAX_SIZE_VAL	(1 << 8)

#घोषणा   I915_FENCE_START_MASK		0x0ff00000
#घोषणा   I915_FENCE_SIZE_BITS(size)	((ffs((size) >> 20) - 1) << 8)

#घोषणा FENCE_REG_965_LO(i)		_MMIO(0x03000 + (i) * 8)
#घोषणा FENCE_REG_965_HI(i)		_MMIO(0x03000 + (i) * 8 + 4)
#घोषणा   I965_FENCE_PITCH_SHIFT	2
#घोषणा   I965_FENCE_TILING_Y_SHIFT	1
#घोषणा   I965_FENCE_REG_VALID		(1 << 0)
#घोषणा   I965_FENCE_MAX_PITCH_VAL	0x0400

#घोषणा FENCE_REG_GEN6_LO(i)		_MMIO(0x100000 + (i) * 8)
#घोषणा FENCE_REG_GEN6_HI(i)		_MMIO(0x100000 + (i) * 8 + 4)
#घोषणा   GEN6_FENCE_PITCH_SHIFT	32
#घोषणा   GEN7_FENCE_MAX_PITCH_VAL	0x0800


/* control रेजिस्टर क्रम cpu gtt access */
#घोषणा TILECTL				_MMIO(0x101000)
#घोषणा   TILECTL_SWZCTL			(1 << 0)
#घोषणा   TILECTL_TLBPF			(1 << 1)
#घोषणा   TILECTL_TLB_PREFETCH_DIS	(1 << 2)
#घोषणा   TILECTL_BACKSNOOP_DIS		(1 << 3)

/*
 * Inकाष्ठाion and पूर्णांकerrupt control regs
 */
#घोषणा PGTBL_CTL	_MMIO(0x02020)
#घोषणा   PGTBL_ADDRESS_LO_MASK	0xfffff000 /* bits [31:12] */
#घोषणा   PGTBL_ADDRESS_HI_MASK	0x000000f0 /* bits [35:32] (gen4) */
#घोषणा PGTBL_ER	_MMIO(0x02024)
#घोषणा PRB0_BASE	(0x2030 - 0x30)
#घोषणा PRB1_BASE	(0x2040 - 0x30) /* 830,gen3 */
#घोषणा PRB2_BASE	(0x2050 - 0x30) /* gen3 */
#घोषणा SRB0_BASE	(0x2100 - 0x30) /* gen2 */
#घोषणा SRB1_BASE	(0x2110 - 0x30) /* gen2 */
#घोषणा SRB2_BASE	(0x2120 - 0x30) /* 830 */
#घोषणा SRB3_BASE	(0x2130 - 0x30) /* 830 */
#घोषणा RENDER_RING_BASE	0x02000
#घोषणा BSD_RING_BASE		0x04000
#घोषणा GEN6_BSD_RING_BASE	0x12000
#घोषणा GEN8_BSD2_RING_BASE	0x1c000
#घोषणा GEN11_BSD_RING_BASE	0x1c0000
#घोषणा GEN11_BSD2_RING_BASE	0x1c4000
#घोषणा GEN11_BSD3_RING_BASE	0x1d0000
#घोषणा GEN11_BSD4_RING_BASE	0x1d4000
#घोषणा VEBOX_RING_BASE		0x1a000
#घोषणा GEN11_VEBOX_RING_BASE		0x1c8000
#घोषणा GEN11_VEBOX2_RING_BASE		0x1d8000
#घोषणा BLT_RING_BASE		0x22000
#घोषणा RING_TAIL(base)		_MMIO((base) + 0x30)
#घोषणा RING_HEAD(base)		_MMIO((base) + 0x34)
#घोषणा RING_START(base)	_MMIO((base) + 0x38)
#घोषणा RING_CTL(base)		_MMIO((base) + 0x3c)
#घोषणा   RING_CTL_SIZE(size)	((size) - PAGE_SIZE) /* in bytes -> pages */
#घोषणा RING_SYNC_0(base)	_MMIO((base) + 0x40)
#घोषणा RING_SYNC_1(base)	_MMIO((base) + 0x44)
#घोषणा RING_SYNC_2(base)	_MMIO((base) + 0x48)
#घोषणा GEN6_RVSYNC	(RING_SYNC_0(RENDER_RING_BASE))
#घोषणा GEN6_RBSYNC	(RING_SYNC_1(RENDER_RING_BASE))
#घोषणा GEN6_RVESYNC	(RING_SYNC_2(RENDER_RING_BASE))
#घोषणा GEN6_VBSYNC	(RING_SYNC_0(GEN6_BSD_RING_BASE))
#घोषणा GEN6_VRSYNC	(RING_SYNC_1(GEN6_BSD_RING_BASE))
#घोषणा GEN6_VVESYNC	(RING_SYNC_2(GEN6_BSD_RING_BASE))
#घोषणा GEN6_BRSYNC	(RING_SYNC_0(BLT_RING_BASE))
#घोषणा GEN6_BVSYNC	(RING_SYNC_1(BLT_RING_BASE))
#घोषणा GEN6_BVESYNC	(RING_SYNC_2(BLT_RING_BASE))
#घोषणा GEN6_VEBSYNC	(RING_SYNC_0(VEBOX_RING_BASE))
#घोषणा GEN6_VERSYNC	(RING_SYNC_1(VEBOX_RING_BASE))
#घोषणा GEN6_VEVSYNC	(RING_SYNC_2(VEBOX_RING_BASE))
#घोषणा GEN6_NOSYNC	INVALID_MMIO_REG
#घोषणा RING_PSMI_CTL(base)	_MMIO((base) + 0x50)
#घोषणा RING_MAX_IDLE(base)	_MMIO((base) + 0x54)
#घोषणा RING_HWS_PGA(base)	_MMIO((base) + 0x80)
#घोषणा RING_ID(base)		_MMIO((base) + 0x8c)
#घोषणा RING_HWS_PGA_GEN6(base)	_MMIO((base) + 0x2080)
#घोषणा RING_RESET_CTL(base)	_MMIO((base) + 0xd0)
#घोषणा   RESET_CTL_CAT_ERROR	   REG_BIT(2)
#घोषणा   RESET_CTL_READY_TO_RESET REG_BIT(1)
#घोषणा   RESET_CTL_REQUEST_RESET  REG_BIT(0)

#घोषणा RING_SEMA_WAIT_POLL(base) _MMIO((base) + 0x24c)

#घोषणा HSW_GTT_CACHE_EN	_MMIO(0x4024)
#घोषणा   GTT_CACHE_EN_ALL	0xF0007FFF
#घोषणा GEN7_WR_WATERMARK	_MMIO(0x4028)
#घोषणा GEN7_GFX_PRIO_CTRL	_MMIO(0x402C)
#घोषणा ARB_MODE		_MMIO(0x4030)
#घोषणा   ARB_MODE_SWIZZLE_SNB	(1 << 4)
#घोषणा   ARB_MODE_SWIZZLE_IVB	(1 << 5)
#घोषणा GEN7_GFX_PEND_TLB0	_MMIO(0x4034)
#घोषणा GEN7_GFX_PEND_TLB1	_MMIO(0x4038)
/* L3, CVS, ZTLB, RCC, CASC LRA min, max values */
#घोषणा GEN7_LRA_LIMITS(i)	_MMIO(0x403C + (i) * 4)
#घोषणा GEN7_LRA_LIMITS_REG_NUM	13
#घोषणा GEN7_MEDIA_MAX_REQ_COUNT	_MMIO(0x4070)
#घोषणा GEN7_GFX_MAX_REQ_COUNT		_MMIO(0x4074)

#घोषणा GAMTARBMODE		_MMIO(0x04a08)
#घोषणा   ARB_MODE_BWGTLB_DISABLE (1 << 9)
#घोषणा   ARB_MODE_SWIZZLE_BDW	(1 << 1)
#घोषणा RENDER_HWS_PGA_GEN7	_MMIO(0x04080)
#घोषणा RING_FAULT_REG(engine)	_MMIO(0x4094 + 0x100 * (engine)->hw_id)
#घोषणा GEN8_RING_FAULT_REG	_MMIO(0x4094)
#घोषणा GEN12_RING_FAULT_REG	_MMIO(0xcec4)
#घोषणा   GEN8_RING_FAULT_ENGINE_ID(x)	(((x) >> 12) & 0x7)
#घोषणा   RING_FAULT_GTTSEL_MASK (1 << 11)
#घोषणा   RING_FAULT_SRCID(x)	(((x) >> 3) & 0xff)
#घोषणा   RING_FAULT_FAULT_TYPE(x) (((x) >> 1) & 0x3)
#घोषणा   RING_FAULT_VALID	(1 << 0)
#घोषणा DONE_REG		_MMIO(0x40b0)
#घोषणा GEN12_GAM_DONE		_MMIO(0xcf68)
#घोषणा GEN8_PRIVATE_PAT_LO	_MMIO(0x40e0)
#घोषणा GEN8_PRIVATE_PAT_HI	_MMIO(0x40e0 + 4)
#घोषणा GEN10_PAT_INDEX(index)	_MMIO(0x40e0 + (index) * 4)
#घोषणा GEN12_PAT_INDEX(index)	_MMIO(0x4800 + (index) * 4)
#घोषणा BSD_HWS_PGA_GEN7	_MMIO(0x04180)
#घोषणा GEN12_GFX_CCS_AUX_NV	_MMIO(0x4208)
#घोषणा GEN12_VD0_AUX_NV	_MMIO(0x4218)
#घोषणा GEN12_VD1_AUX_NV	_MMIO(0x4228)
#घोषणा GEN12_VD2_AUX_NV	_MMIO(0x4298)
#घोषणा GEN12_VD3_AUX_NV	_MMIO(0x42A8)
#घोषणा GEN12_VE0_AUX_NV	_MMIO(0x4238)
#घोषणा GEN12_VE1_AUX_NV	_MMIO(0x42B8)
#घोषणा   AUX_INV		REG_BIT(0)
#घोषणा BLT_HWS_PGA_GEN7	_MMIO(0x04280)
#घोषणा VEBOX_HWS_PGA_GEN7	_MMIO(0x04380)
#घोषणा RING_ACTHD(base)	_MMIO((base) + 0x74)
#घोषणा RING_ACTHD_UDW(base)	_MMIO((base) + 0x5c)
#घोषणा RING_NOPID(base)	_MMIO((base) + 0x94)
#घोषणा RING_IMR(base)		_MMIO((base) + 0xa8)
#घोषणा RING_HWSTAM(base)	_MMIO((base) + 0x98)
#घोषणा RING_TIMESTAMP(base)		_MMIO((base) + 0x358)
#घोषणा RING_TIMESTAMP_UDW(base)	_MMIO((base) + 0x358 + 4)
#घोषणा   TAIL_ADDR		0x001FFFF8
#घोषणा   HEAD_WRAP_COUNT	0xFFE00000
#घोषणा   HEAD_WRAP_ONE		0x00200000
#घोषणा   HEAD_ADDR		0x001FFFFC
#घोषणा   RING_NR_PAGES		0x001FF000
#घोषणा   RING_REPORT_MASK	0x00000006
#घोषणा   RING_REPORT_64K	0x00000002
#घोषणा   RING_REPORT_128K	0x00000004
#घोषणा   RING_NO_REPORT	0x00000000
#घोषणा   RING_VALID_MASK	0x00000001
#घोषणा   RING_VALID		0x00000001
#घोषणा   RING_INVALID		0x00000000
#घोषणा   RING_WAIT_I8XX	(1 << 0) /* gen2, PRBx_HEAD */
#घोषणा   RING_WAIT		(1 << 11) /* gen3+, PRBx_CTL */
#घोषणा   RING_WAIT_SEMAPHORE	(1 << 10) /* gen6+ */

/* There are 16 64-bit CS General Purpose Registers per-engine on Gen8+ */
#घोषणा GEN8_RING_CS_GPR(base, n)	_MMIO((base) + 0x600 + (n) * 8)
#घोषणा GEN8_RING_CS_GPR_UDW(base, n)	_MMIO((base) + 0x600 + (n) * 8 + 4)

#घोषणा RING_FORCE_TO_NONPRIV(base, i) _MMIO(((base) + 0x4D0) + (i) * 4)
#घोषणा   RING_FORCE_TO_NONPRIV_ADDRESS_MASK	REG_GENMASK(25, 2)
#घोषणा   RING_FORCE_TO_NONPRIV_ACCESS_RW	(0 << 28)    /* CFL+ & Gen11+ */
#घोषणा   RING_FORCE_TO_NONPRIV_ACCESS_RD	(1 << 28)
#घोषणा   RING_FORCE_TO_NONPRIV_ACCESS_WR	(2 << 28)
#घोषणा   RING_FORCE_TO_NONPRIV_ACCESS_INVALID	(3 << 28)
#घोषणा   RING_FORCE_TO_NONPRIV_ACCESS_MASK	(3 << 28)
#घोषणा   RING_FORCE_TO_NONPRIV_RANGE_1		(0 << 0)     /* CFL+ & Gen11+ */
#घोषणा   RING_FORCE_TO_NONPRIV_RANGE_4		(1 << 0)
#घोषणा   RING_FORCE_TO_NONPRIV_RANGE_16	(2 << 0)
#घोषणा   RING_FORCE_TO_NONPRIV_RANGE_64	(3 << 0)
#घोषणा   RING_FORCE_TO_NONPRIV_RANGE_MASK	(3 << 0)
#घोषणा   RING_FORCE_TO_NONPRIV_MASK_VALID	\
					(RING_FORCE_TO_NONPRIV_RANGE_MASK \
					| RING_FORCE_TO_NONPRIV_ACCESS_MASK)
#घोषणा   RING_MAX_NONPRIV_SLOTS  12

#घोषणा GEN7_TLB_RD_ADDR	_MMIO(0x4700)

#घोषणा GEN9_GAMT_ECO_REG_RW_IA _MMIO(0x4ab0)
#घोषणा   GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS	(1 << 18)

#घोषणा GEN8_GAMW_ECO_DEV_RW_IA _MMIO(0x4080)
#घोषणा   GAMW_ECO_ENABLE_64K_IPS_FIELD 0xF
#घोषणा   GAMW_ECO_DEV_CTX_RELOAD_DISABLE	(1 << 7)

#घोषणा GAMT_CHKN_BIT_REG	_MMIO(0x4ab8)
#घोषणा   GAMT_CHKN_DISABLE_L3_COH_PIPE			(1 << 31)
#घोषणा   GAMT_CHKN_DISABLE_DYNAMIC_CREDIT_SHARING	(1 << 28)
#घोषणा   GAMT_CHKN_DISABLE_I2M_CYCLE_ON_WR_PORT	(1 << 24)

#अगर 0
#घोषणा PRB0_TAIL	_MMIO(0x2030)
#घोषणा PRB0_HEAD	_MMIO(0x2034)
#घोषणा PRB0_START	_MMIO(0x2038)
#घोषणा PRB0_CTL	_MMIO(0x203c)
#घोषणा PRB1_TAIL	_MMIO(0x2040) /* 915+ only */
#घोषणा PRB1_HEAD	_MMIO(0x2044) /* 915+ only */
#घोषणा PRB1_START	_MMIO(0x2048) /* 915+ only */
#घोषणा PRB1_CTL	_MMIO(0x204c) /* 915+ only */
#पूर्ण_अगर
#घोषणा IPEIR_I965	_MMIO(0x2064)
#घोषणा IPEHR_I965	_MMIO(0x2068)
#घोषणा GEN7_SC_INSTDONE	_MMIO(0x7100)
#घोषणा GEN12_SC_INSTDONE_EXTRA		_MMIO(0x7104)
#घोषणा GEN12_SC_INSTDONE_EXTRA2	_MMIO(0x7108)
#घोषणा GEN7_SAMPLER_INSTDONE	_MMIO(0xe160)
#घोषणा GEN7_ROW_INSTDONE	_MMIO(0xe164)
#घोषणा GEN8_MCR_SELECTOR		_MMIO(0xfdc)
#घोषणा   GEN8_MCR_SLICE(slice)		(((slice) & 3) << 26)
#घोषणा   GEN8_MCR_SLICE_MASK		GEN8_MCR_SLICE(3)
#घोषणा   GEN8_MCR_SUBSLICE(subslice)	(((subslice) & 3) << 24)
#घोषणा   GEN8_MCR_SUBSLICE_MASK	GEN8_MCR_SUBSLICE(3)
#घोषणा   GEN11_MCR_SLICE(slice)	(((slice) & 0xf) << 27)
#घोषणा   GEN11_MCR_SLICE_MASK		GEN11_MCR_SLICE(0xf)
#घोषणा   GEN11_MCR_SUBSLICE(subslice)	(((subslice) & 0x7) << 24)
#घोषणा   GEN11_MCR_SUBSLICE_MASK	GEN11_MCR_SUBSLICE(0x7)
#घोषणा RING_IPEIR(base)	_MMIO((base) + 0x64)
#घोषणा RING_IPEHR(base)	_MMIO((base) + 0x68)
#घोषणा RING_EIR(base)		_MMIO((base) + 0xb0)
#घोषणा RING_EMR(base)		_MMIO((base) + 0xb4)
#घोषणा RING_ESR(base)		_MMIO((base) + 0xb8)
/*
 * On GEN4, only the render ring INSTDONE exists and has a dअगरferent
 * layout than the GEN7+ version.
 * The GEN2 counterpart of this रेजिस्टर is GEN2_INSTDONE.
 */
#घोषणा RING_INSTDONE(base)	_MMIO((base) + 0x6c)
#घोषणा RING_INSTPS(base)	_MMIO((base) + 0x70)
#घोषणा RING_DMA_FADD(base)	_MMIO((base) + 0x78)
#घोषणा RING_DMA_FADD_UDW(base)	_MMIO((base) + 0x60) /* gen8+ */
#घोषणा RING_INSTPM(base)	_MMIO((base) + 0xc0)
#घोषणा RING_MI_MODE(base)	_MMIO((base) + 0x9c)
#घोषणा RING_CMD_BUF_CCTL(base) _MMIO((base) + 0x84)
#घोषणा INSTPS		_MMIO(0x2070) /* 965+ only */
#घोषणा GEN4_INSTDONE1	_MMIO(0x207c) /* 965+ only, aka INSTDONE_2 on SNB */
#घोषणा ACTHD_I965	_MMIO(0x2074)
#घोषणा HWS_PGA		_MMIO(0x2080)
#घोषणा HWS_ADDRESS_MASK	0xfffff000
#घोषणा HWS_START_ADDRESS_SHIFT	4
#घोषणा PWRCTXA		_MMIO(0x2088) /* 965GM+ only */
#घोषणा   PWRCTX_EN	(1 << 0)
#घोषणा IPEIR(base)	_MMIO((base) + 0x88)
#घोषणा IPEHR(base)	_MMIO((base) + 0x8c)
#घोषणा GEN2_INSTDONE	_MMIO(0x2090)
#घोषणा NOPID		_MMIO(0x2094)
#घोषणा HWSTAM		_MMIO(0x2098)
#घोषणा DMA_FADD_I8XX(base)	_MMIO((base) + 0xd0)
#घोषणा RING_BBSTATE(base)	_MMIO((base) + 0x110)
#घोषणा   RING_BB_PPGTT		(1 << 5)
#घोषणा RING_SBBADDR(base)	_MMIO((base) + 0x114) /* hsw+ */
#घोषणा RING_SBBSTATE(base)	_MMIO((base) + 0x118) /* hsw+ */
#घोषणा RING_SBBADDR_UDW(base)	_MMIO((base) + 0x11c) /* gen8+ */
#घोषणा RING_BBADDR(base)	_MMIO((base) + 0x140)
#घोषणा RING_BBADDR_UDW(base)	_MMIO((base) + 0x168) /* gen8+ */
#घोषणा RING_BB_PER_CTX_PTR(base)	_MMIO((base) + 0x1c0) /* gen8+ */
#घोषणा RING_INसूचीECT_CTX(base)		_MMIO((base) + 0x1c4) /* gen8+ */
#घोषणा RING_INसूचीECT_CTX_OFFSET(base)	_MMIO((base) + 0x1c8) /* gen8+ */
#घोषणा RING_CTX_TIMESTAMP(base)	_MMIO((base) + 0x3a8) /* gen8+ */

#घोषणा ERROR_GEN6	_MMIO(0x40a0)
#घोषणा GEN7_ERR_INT	_MMIO(0x44040)
#घोषणा   ERR_INT_POISON		(1 << 31)
#घोषणा   ERR_INT_MMIO_UNCLAIMED	(1 << 13)
#घोषणा   ERR_INT_PIPE_CRC_DONE_C	(1 << 8)
#घोषणा   ERR_INT_FIFO_UNDERRUN_C	(1 << 6)
#घोषणा   ERR_INT_PIPE_CRC_DONE_B	(1 << 5)
#घोषणा   ERR_INT_FIFO_UNDERRUN_B	(1 << 3)
#घोषणा   ERR_INT_PIPE_CRC_DONE_A	(1 << 2)
#घोषणा   ERR_INT_PIPE_CRC_DONE(pipe)	(1 << (2 + (pipe) * 3))
#घोषणा   ERR_INT_FIFO_UNDERRUN_A	(1 << 0)
#घोषणा   ERR_INT_FIFO_UNDERRUN(pipe)	(1 << ((pipe) * 3))

#घोषणा GEN8_FAULT_TLB_DATA0		_MMIO(0x4b10)
#घोषणा GEN8_FAULT_TLB_DATA1		_MMIO(0x4b14)
#घोषणा GEN12_FAULT_TLB_DATA0		_MMIO(0xceb8)
#घोषणा GEN12_FAULT_TLB_DATA1		_MMIO(0xcebc)
#घोषणा   FAULT_VA_HIGH_BITS		(0xf << 0)
#घोषणा   FAULT_GTT_SEL			(1 << 4)

#घोषणा GEN12_AUX_ERR_DBG		_MMIO(0x43f4)

#घोषणा FPGA_DBG		_MMIO(0x42300)
#घोषणा   FPGA_DBG_RM_NOCLAIM	(1 << 31)

#घोषणा CLAIM_ER		_MMIO(VLV_DISPLAY_BASE + 0x2028)
#घोषणा   CLAIM_ER_CLR		(1 << 31)
#घोषणा   CLAIM_ER_OVERFLOW	(1 << 16)
#घोषणा   CLAIM_ER_CTR_MASK	0xffff

#घोषणा DERRMR		_MMIO(0x44050)
/* Note that HBLANK events are reserved on bdw+ */
#घोषणा   DERRMR_PIPEA_SCANLINE		(1 << 0)
#घोषणा   DERRMR_PIPEA_PRI_FLIP_DONE	(1 << 1)
#घोषणा   DERRMR_PIPEA_SPR_FLIP_DONE	(1 << 2)
#घोषणा   DERRMR_PIPEA_VBLANK		(1 << 3)
#घोषणा   DERRMR_PIPEA_HBLANK		(1 << 5)
#घोषणा   DERRMR_PIPEB_SCANLINE		(1 << 8)
#घोषणा   DERRMR_PIPEB_PRI_FLIP_DONE	(1 << 9)
#घोषणा   DERRMR_PIPEB_SPR_FLIP_DONE	(1 << 10)
#घोषणा   DERRMR_PIPEB_VBLANK		(1 << 11)
#घोषणा   DERRMR_PIPEB_HBLANK		(1 << 13)
/* Note that PIPEC is not a simple translation of PIPEA/PIPEB */
#घोषणा   DERRMR_PIPEC_SCANLINE		(1 << 14)
#घोषणा   DERRMR_PIPEC_PRI_FLIP_DONE	(1 << 15)
#घोषणा   DERRMR_PIPEC_SPR_FLIP_DONE	(1 << 20)
#घोषणा   DERRMR_PIPEC_VBLANK		(1 << 21)
#घोषणा   DERRMR_PIPEC_HBLANK		(1 << 22)


/* GM45+ chicken bits -- debug workaround bits that may be required
 * क्रम various sorts of correct behavior.  The top 16 bits of each are
 * the enables क्रम writing to the corresponding low bit.
 */
#घोषणा _3D_CHICKEN	_MMIO(0x2084)
#घोषणा  _3D_CHICKEN_HIZ_PLANE_DISABLE_MSAA_4X_SNB	(1 << 10)
#घोषणा _3D_CHICKEN2	_MMIO(0x208c)

#घोषणा FF_SLICE_CHICKEN	_MMIO(0x2088)
#घोषणा  FF_SLICE_CHICKEN_CL_PROVOKING_VERTEX_FIX	(1 << 1)

/* Disables pipelining of पढ़ो flushes past the SF-WIZ पूर्णांकerface.
 * Required on all Ironlake steppings according to the B-Spec, but the
 * particular danger of not करोing so is not specअगरied.
 */
# define _3D_CHICKEN2_WM_READ_PIPELINED			(1 << 14)
#घोषणा _3D_CHICKEN3	_MMIO(0x2090)
#घोषणा  _3D_CHICKEN_SF_PROVOKING_VERTEX_FIX		(1 << 12)
#घोषणा  _3D_CHICKEN_SF_DISABLE_OBJEND_CULL		(1 << 10)
#घोषणा  _3D_CHICKEN3_AA_LINE_QUALITY_FIX_ENABLE	(1 << 5)
#घोषणा  _3D_CHICKEN3_SF_DISABLE_FASTCLIP_CULL		(1 << 5)
#घोषणा  _3D_CHICKEN_SDE_LIMIT_FIFO_POLY_DEPTH(x)	((x) << 1) /* gen8+ */
#घोषणा  _3D_CHICKEN3_SF_DISABLE_PIPELINED_ATTR_FETCH	(1 << 1) /* gen6 */

#घोषणा MI_MODE		_MMIO(0x209c)
# define VS_TIMER_DISPATCH				(1 << 6)
# define MI_FLUSH_ENABLE				(1 << 12)
# define ASYNC_FLIP_PERF_DISABLE			(1 << 14)
# define MODE_IDLE					(1 << 9)
# define STOP_RING					(1 << 8)

#घोषणा GEN6_GT_MODE	_MMIO(0x20d0)
#घोषणा GEN7_GT_MODE	_MMIO(0x7008)
#घोषणा   GEN6_WIZ_HASHING(hi, lo)			(((hi) << 9) | ((lo) << 7))
#घोषणा   GEN6_WIZ_HASHING_8x8				GEN6_WIZ_HASHING(0, 0)
#घोषणा   GEN6_WIZ_HASHING_8x4				GEN6_WIZ_HASHING(0, 1)
#घोषणा   GEN6_WIZ_HASHING_16x4				GEN6_WIZ_HASHING(1, 0)
#घोषणा   GEN6_WIZ_HASHING_MASK				GEN6_WIZ_HASHING(1, 1)
#घोषणा   GEN6_TD_FOUR_ROW_DISPATCH_DISABLE		(1 << 5)
#घोषणा   GEN9_IZ_HASHING_MASK(slice)			(0x3 << ((slice) * 2))
#घोषणा   GEN9_IZ_HASHING(slice, val)			((val) << ((slice) * 2))

/* chicken reg क्रम WaConextSwitchWithConcurrentTLBInvalidate */
#घोषणा GEN9_CSFE_CHICKEN1_RCS _MMIO(0x20D4)
#घोषणा   GEN9_PREEMPT_GPGPU_SYNC_SWITCH_DISABLE (1 << 2)
#घोषणा   GEN11_ENABLE_32_PLANE_MODE (1 << 7)

/* WaClearTdlStateAckDirtyBits */
#घोषणा GEN8_STATE_ACK		_MMIO(0x20F0)
#घोषणा GEN9_STATE_ACK_SLICE1	_MMIO(0x20F8)
#घोषणा GEN9_STATE_ACK_SLICE2	_MMIO(0x2100)
#घोषणा   GEN9_STATE_ACK_TDL0 (1 << 12)
#घोषणा   GEN9_STATE_ACK_TDL1 (1 << 13)
#घोषणा   GEN9_STATE_ACK_TDL2 (1 << 14)
#घोषणा   GEN9_STATE_ACK_TDL3 (1 << 15)
#घोषणा   GEN9_SUBSLICE_TDL_ACK_BITS \
	(GEN9_STATE_ACK_TDL3 | GEN9_STATE_ACK_TDL2 | \
	 GEN9_STATE_ACK_TDL1 | GEN9_STATE_ACK_TDL0)

#घोषणा GFX_MODE	_MMIO(0x2520)
#घोषणा GFX_MODE_GEN7	_MMIO(0x229c)
#घोषणा RING_MODE_GEN7(base)	_MMIO((base) + 0x29c)
#घोषणा   GFX_RUN_LIST_ENABLE		(1 << 15)
#घोषणा   GFX_INTERRUPT_STEERING	(1 << 14)
#घोषणा   GFX_TLB_INVALIDATE_EXPLICIT	(1 << 13)
#घोषणा   GFX_SURFACE_FAULT_ENABLE	(1 << 12)
#घोषणा   GFX_REPLAY_MODE		(1 << 11)
#घोषणा   GFX_PSMI_GRANULARITY		(1 << 10)
#घोषणा   GFX_PPGTT_ENABLE		(1 << 9)
#घोषणा   GEN8_GFX_PPGTT_48B		(1 << 7)

#घोषणा   GFX_FORWARD_VBLANK_MASK	(3 << 5)
#घोषणा   GFX_FORWARD_VBLANK_NEVER	(0 << 5)
#घोषणा   GFX_FORWARD_VBLANK_ALWAYS	(1 << 5)
#घोषणा   GFX_FORWARD_VBLANK_COND	(2 << 5)

#घोषणा   GEN11_GFX_DISABLE_LEGACY_MODE	(1 << 3)

#घोषणा VLV_GU_CTL0	_MMIO(VLV_DISPLAY_BASE + 0x2030)
#घोषणा VLV_GU_CTL1	_MMIO(VLV_DISPLAY_BASE + 0x2034)
#घोषणा SCPD0		_MMIO(0x209c) /* 915+ only */
#घोषणा  SCPD_FBC_IGNORE_3D			(1 << 6)
#घोषणा  CSTATE_RENDER_CLOCK_GATE_DISABLE	(1 << 5)
#घोषणा GEN2_IER	_MMIO(0x20a0)
#घोषणा GEN2_IIR	_MMIO(0x20a4)
#घोषणा GEN2_IMR	_MMIO(0x20a8)
#घोषणा GEN2_ISR	_MMIO(0x20ac)
#घोषणा VLV_GUNIT_CLOCK_GATE	_MMIO(VLV_DISPLAY_BASE + 0x2060)
#घोषणा   GINT_DIS		(1 << 22)
#घोषणा   GCFG_DIS		(1 << 8)
#घोषणा VLV_GUNIT_CLOCK_GATE2	_MMIO(VLV_DISPLAY_BASE + 0x2064)
#घोषणा VLV_IIR_RW	_MMIO(VLV_DISPLAY_BASE + 0x2084)
#घोषणा VLV_IER		_MMIO(VLV_DISPLAY_BASE + 0x20a0)
#घोषणा VLV_IIR		_MMIO(VLV_DISPLAY_BASE + 0x20a4)
#घोषणा VLV_IMR		_MMIO(VLV_DISPLAY_BASE + 0x20a8)
#घोषणा VLV_ISR		_MMIO(VLV_DISPLAY_BASE + 0x20ac)
#घोषणा VLV_PCBR	_MMIO(VLV_DISPLAY_BASE + 0x2120)
#घोषणा VLV_PCBR_ADDR_SHIFT	12

#घोषणा   DISPLAY_PLANE_FLIP_PENDING(plane) (1 << (11 - (plane))) /* A and B only */
#घोषणा EIR		_MMIO(0x20b0)
#घोषणा EMR		_MMIO(0x20b4)
#घोषणा ESR		_MMIO(0x20b8)
#घोषणा   GM45_ERROR_PAGE_TABLE				(1 << 5)
#घोषणा   GM45_ERROR_MEM_PRIV				(1 << 4)
#घोषणा   I915_ERROR_PAGE_TABLE				(1 << 4)
#घोषणा   GM45_ERROR_CP_PRIV				(1 << 3)
#घोषणा   I915_ERROR_MEMORY_REFRESH			(1 << 1)
#घोषणा   I915_ERROR_INSTRUCTION			(1 << 0)
#घोषणा INSTPM	        _MMIO(0x20c0)
#घोषणा   INSTPM_SELF_EN (1 << 12) /* 915GM only */
#घोषणा   INSTPM_AGPBUSY_INT_EN (1 << 11) /* gen3: when disabled, pending पूर्णांकerrupts
					will not निश्चित AGPBUSY# and will only
					be delivered when out of C3. */
#घोषणा   INSTPM_FORCE_ORDERING				(1 << 7) /* GEN6+ */
#घोषणा   INSTPM_TLB_INVALIDATE	(1 << 9)
#घोषणा   INSTPM_SYNC_FLUSH	(1 << 5)
#घोषणा ACTHD(base)	_MMIO((base) + 0xc8)
#घोषणा MEM_MODE	_MMIO(0x20cc)
#घोषणा   MEM_DISPLAY_B_TRICKLE_FEED_DISABLE (1 << 3) /* 830 only */
#घोषणा   MEM_DISPLAY_A_TRICKLE_FEED_DISABLE (1 << 2) /* 830/845 only */
#घोषणा   MEM_DISPLAY_TRICKLE_FEED_DISABLE (1 << 2) /* 85x only */
#घोषणा FW_BLC		_MMIO(0x20d8)
#घोषणा FW_BLC2		_MMIO(0x20dc)
#घोषणा FW_BLC_SELF	_MMIO(0x20e0) /* 915+ only */
#घोषणा   FW_BLC_SELF_EN_MASK      (1 << 31)
#घोषणा   FW_BLC_SELF_FIFO_MASK    (1 << 16) /* 945 only */
#घोषणा   FW_BLC_SELF_EN           (1 << 15) /* 945 only */
#घोषणा MM_BURST_LENGTH     0x00700000
#घोषणा MM_FIFO_WATERMARK   0x0001F000
#घोषणा LM_BURST_LENGTH     0x00000700
#घोषणा LM_FIFO_WATERMARK   0x0000001F
#घोषणा MI_ARB_STATE	_MMIO(0x20e4) /* 915+ only */

#घोषणा _MBUS_ABOX0_CTL			0x45038
#घोषणा _MBUS_ABOX1_CTL			0x45048
#घोषणा _MBUS_ABOX2_CTL			0x4504C
#घोषणा MBUS_ABOX_CTL(x)		_MMIO(_PICK(x, _MBUS_ABOX0_CTL, \
						    _MBUS_ABOX1_CTL, \
						    _MBUS_ABOX2_CTL))
#घोषणा MBUS_ABOX_BW_CREDIT_MASK	(3 << 20)
#घोषणा MBUS_ABOX_BW_CREDIT(x)		((x) << 20)
#घोषणा MBUS_ABOX_B_CREDIT_MASK		(0xF << 16)
#घोषणा MBUS_ABOX_B_CREDIT(x)		((x) << 16)
#घोषणा MBUS_ABOX_BT_CREDIT_POOL2_MASK	(0x1F << 8)
#घोषणा MBUS_ABOX_BT_CREDIT_POOL2(x)	((x) << 8)
#घोषणा MBUS_ABOX_BT_CREDIT_POOL1_MASK	(0x1F << 0)
#घोषणा MBUS_ABOX_BT_CREDIT_POOL1(x)	((x) << 0)

#घोषणा _PIPEA_MBUS_DBOX_CTL		0x7003C
#घोषणा _PIPEB_MBUS_DBOX_CTL		0x7103C
#घोषणा PIPE_MBUS_DBOX_CTL(pipe)	_MMIO_PIPE(pipe, _PIPEA_MBUS_DBOX_CTL, \
						   _PIPEB_MBUS_DBOX_CTL)
#घोषणा MBUS_DBOX_BW_CREDIT_MASK	(3 << 14)
#घोषणा MBUS_DBOX_BW_CREDIT(x)		((x) << 14)
#घोषणा MBUS_DBOX_B_CREDIT_MASK		(0x1F << 8)
#घोषणा MBUS_DBOX_B_CREDIT(x)		((x) << 8)
#घोषणा MBUS_DBOX_A_CREDIT_MASK		(0xF << 0)
#घोषणा MBUS_DBOX_A_CREDIT(x)		((x) << 0)

#घोषणा MBUS_UBOX_CTL			_MMIO(0x4503C)
#घोषणा MBUS_BBOX_CTL_S1		_MMIO(0x45040)
#घोषणा MBUS_BBOX_CTL_S2		_MMIO(0x45044)

#घोषणा HDPORT_STATE			_MMIO(0x45050)
#घोषणा   HDPORT_DPLL_USED_MASK		REG_GENMASK(15, 12)
#घोषणा   HDPORT_DDI_USED(phy)		REG_BIT(2 * (phy) + 1)
#घोषणा   HDPORT_ENABLED		REG_BIT(0)

/* Make render/texture TLB fetches lower priorty than associated data
 *   fetches. This is not turned on by शेष
 */
#घोषणा   MI_ARB_RENDER_TLB_LOW_PRIORITY	(1 << 15)

/* Isoch request रुको on GTT enable (Display A/B/C streams).
 * Make isoch requests stall on the TLB update. May cause
 * display underruns (test mode only)
 */
#घोषणा   MI_ARB_ISOCH_WAIT_GTT			(1 << 14)

/* Block grant count क्रम isoch requests when block count is
 * set to a finite value.
 */
#घोषणा   MI_ARB_BLOCK_GRANT_MASK		(3 << 12)
#घोषणा   MI_ARB_BLOCK_GRANT_8			(0 << 12)	/* क्रम 3 display planes */
#घोषणा   MI_ARB_BLOCK_GRANT_4			(1 << 12)	/* क्रम 2 display planes */
#घोषणा   MI_ARB_BLOCK_GRANT_2			(2 << 12)	/* क्रम 1 display plane */
#घोषणा   MI_ARB_BLOCK_GRANT_0			(3 << 12)	/* करोn't use */

/* Enable render ग_लिखोs to complete in C2/C3/C4 घातer states.
 * If this isn't enabled, render ग_लिखोs are prevented in low
 * घातer states. That seems bad to me.
 */
#घोषणा   MI_ARB_C3_LP_WRITE_ENABLE		(1 << 11)

/* This acknowledges an async flip immediately instead
 * of रुकोing क्रम 2TLB fetches.
 */
#घोषणा   MI_ARB_ASYNC_FLIP_ACK_IMMEDIATE	(1 << 10)

/* Enables non-sequential data पढ़ोs through arbiter
 */
#घोषणा   MI_ARB_DUAL_DATA_PHASE_DISABLE	(1 << 9)

/* Disable FSB snooping of cacheable ग_लिखो cycles from binner/render
 * command stream
 */
#घोषणा   MI_ARB_CACHE_SNOOP_DISABLE		(1 << 8)

/* Arbiter समय slice क्रम non-isoch streams */
#घोषणा   MI_ARB_TIME_SLICE_MASK		(7 << 5)
#घोषणा   MI_ARB_TIME_SLICE_1			(0 << 5)
#घोषणा   MI_ARB_TIME_SLICE_2			(1 << 5)
#घोषणा   MI_ARB_TIME_SLICE_4			(2 << 5)
#घोषणा   MI_ARB_TIME_SLICE_6			(3 << 5)
#घोषणा   MI_ARB_TIME_SLICE_8			(4 << 5)
#घोषणा   MI_ARB_TIME_SLICE_10			(5 << 5)
#घोषणा   MI_ARB_TIME_SLICE_14			(6 << 5)
#घोषणा   MI_ARB_TIME_SLICE_16			(7 << 5)

/* Low priority grace period page size */
#घोषणा   MI_ARB_LOW_PRIORITY_GRACE_4KB		(0 << 4)	/* शेष */
#घोषणा   MI_ARB_LOW_PRIORITY_GRACE_8KB		(1 << 4)

/* Disable display A/B trickle feed */
#घोषणा   MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE	(1 << 2)

/* Set display plane priority */
#घोषणा   MI_ARB_DISPLAY_PRIORITY_A_B		(0 << 0)	/* display A > display B */
#घोषणा   MI_ARB_DISPLAY_PRIORITY_B_A		(1 << 0)	/* display B > display A */

#घोषणा MI_STATE	_MMIO(0x20e4) /* gen2 only */
#घोषणा   MI_AGPBUSY_INT_EN			(1 << 1) /* 85x only */
#घोषणा   MI_AGPBUSY_830_MODE			(1 << 0) /* 85x only */

#घोषणा CACHE_MODE_0	_MMIO(0x2120) /* 915+ only */
#घोषणा   CM0_PIPELINED_RENDER_FLUSH_DISABLE (1 << 8)
#घोषणा   CM0_IZ_OPT_DISABLE      (1 << 6)
#घोषणा   CM0_ZR_OPT_DISABLE      (1 << 5)
#घोषणा	  CM0_STC_EVICT_DISABLE_LRA_SNB	(1 << 5)
#घोषणा   CM0_DEPTH_EVICT_DISABLE (1 << 4)
#घोषणा   CM0_COLOR_EVICT_DISABLE (1 << 3)
#घोषणा   CM0_DEPTH_WRITE_DISABLE (1 << 1)
#घोषणा   CM0_RC_OP_FLUSH_DISABLE (1 << 0)
#घोषणा GFX_FLSH_CNTL	_MMIO(0x2170) /* 915+ only */
#घोषणा GFX_FLSH_CNTL_GEN6	_MMIO(0x101008)
#घोषणा   GFX_FLSH_CNTL_EN	(1 << 0)
#घोषणा ECOSKPD		_MMIO(0x21d0)
#घोषणा   ECO_CONSTANT_BUFFER_SR_DISABLE REG_BIT(4)
#घोषणा   ECO_GATING_CX_ONLY	(1 << 3)
#घोषणा   ECO_FLIP_DONE		(1 << 0)

#घोषणा CACHE_MODE_0_GEN7	_MMIO(0x7000) /* IVB+ */
#घोषणा RC_OP_FLUSH_ENABLE (1 << 0)
#घोषणा   HIZ_RAW_STALL_OPT_DISABLE (1 << 2)
#घोषणा CACHE_MODE_1		_MMIO(0x7004) /* IVB+ */
#घोषणा   PIXEL_SUBSPAN_COLLECT_OPT_DISABLE	(1 << 6)
#घोषणा   GEN8_4x4_STC_OPTIMIZATION_DISABLE	(1 << 6)
#घोषणा   GEN9_PARTIAL_RESOLVE_IN_VC_DISABLE	(1 << 1)

#घोषणा GEN6_BLITTER_ECOSKPD	_MMIO(0x221d0)
#घोषणा   GEN6_BLITTER_LOCK_SHIFT			16
#घोषणा   GEN6_BLITTER_FBC_NOTIFY			(1 << 3)

#घोषणा GEN6_RC_SLEEP_PSMI_CONTROL	_MMIO(0x2050)
#घोषणा   GEN6_PSMI_SLEEP_MSG_DISABLE	(1 << 0)
#घोषणा   GEN12_WAIT_FOR_EVENT_POWER_DOWN_DISABLE REG_BIT(7)
#घोषणा   GEN8_RC_SEMA_IDLE_MSG_DISABLE	(1 << 12)
#घोषणा   GEN8_FF_DOP_CLOCK_GATE_DISABLE	(1 << 10)

#घोषणा GEN6_RCS_PWR_FSM _MMIO(0x22ac)
#घोषणा GEN9_RCS_FE_FSM2 _MMIO(0x22a4)

#घोषणा GEN10_CACHE_MODE_SS			_MMIO(0xe420)
#घोषणा   FLOAT_BLEND_OPTIMIZATION_ENABLE	(1 << 4)

/* Fuse पढ़ोout रेजिस्टरs क्रम GT */
#घोषणा HSW_PAVP_FUSE1			_MMIO(0x911C)
#घोषणा   HSW_F1_EU_DIS_SHIFT		16
#घोषणा   HSW_F1_EU_DIS_MASK		(0x3 << HSW_F1_EU_DIS_SHIFT)
#घोषणा   HSW_F1_EU_DIS_10EUS		0
#घोषणा   HSW_F1_EU_DIS_8EUS		1
#घोषणा   HSW_F1_EU_DIS_6EUS		2

#घोषणा CHV_FUSE_GT			_MMIO(VLV_DISPLAY_BASE + 0x2168)
#घोषणा   CHV_FGT_DISABLE_SS0		(1 << 10)
#घोषणा   CHV_FGT_DISABLE_SS1		(1 << 11)
#घोषणा   CHV_FGT_EU_DIS_SS0_R0_SHIFT	16
#घोषणा   CHV_FGT_EU_DIS_SS0_R0_MASK	(0xf << CHV_FGT_EU_DIS_SS0_R0_SHIFT)
#घोषणा   CHV_FGT_EU_DIS_SS0_R1_SHIFT	20
#घोषणा   CHV_FGT_EU_DIS_SS0_R1_MASK	(0xf << CHV_FGT_EU_DIS_SS0_R1_SHIFT)
#घोषणा   CHV_FGT_EU_DIS_SS1_R0_SHIFT	24
#घोषणा   CHV_FGT_EU_DIS_SS1_R0_MASK	(0xf << CHV_FGT_EU_DIS_SS1_R0_SHIFT)
#घोषणा   CHV_FGT_EU_DIS_SS1_R1_SHIFT	28
#घोषणा   CHV_FGT_EU_DIS_SS1_R1_MASK	(0xf << CHV_FGT_EU_DIS_SS1_R1_SHIFT)

#घोषणा GEN8_FUSE2			_MMIO(0x9120)
#घोषणा   GEN8_F2_SS_DIS_SHIFT		21
#घोषणा   GEN8_F2_SS_DIS_MASK		(0x7 << GEN8_F2_SS_DIS_SHIFT)
#घोषणा   GEN8_F2_S_ENA_SHIFT		25
#घोषणा   GEN8_F2_S_ENA_MASK		(0x7 << GEN8_F2_S_ENA_SHIFT)

#घोषणा   GEN9_F2_SS_DIS_SHIFT		20
#घोषणा   GEN9_F2_SS_DIS_MASK		(0xf << GEN9_F2_SS_DIS_SHIFT)

#घोषणा   GEN10_F2_S_ENA_SHIFT		22
#घोषणा   GEN10_F2_S_ENA_MASK		(0x3f << GEN10_F2_S_ENA_SHIFT)
#घोषणा   GEN10_F2_SS_DIS_SHIFT		18
#घोषणा   GEN10_F2_SS_DIS_MASK		(0xf << GEN10_F2_SS_DIS_SHIFT)

#घोषणा	GEN10_MIRROR_FUSE3		_MMIO(0x9118)
#घोषणा GEN10_L3BANK_PAIR_COUNT     4
#घोषणा GEN10_L3BANK_MASK   0x0F

#घोषणा GEN8_EU_DISABLE0		_MMIO(0x9134)
#घोषणा   GEN8_EU_DIS0_S0_MASK		0xffffff
#घोषणा   GEN8_EU_DIS0_S1_SHIFT		24
#घोषणा   GEN8_EU_DIS0_S1_MASK		(0xff << GEN8_EU_DIS0_S1_SHIFT)

#घोषणा GEN8_EU_DISABLE1		_MMIO(0x9138)
#घोषणा   GEN8_EU_DIS1_S1_MASK		0xffff
#घोषणा   GEN8_EU_DIS1_S2_SHIFT		16
#घोषणा   GEN8_EU_DIS1_S2_MASK		(0xffff << GEN8_EU_DIS1_S2_SHIFT)

#घोषणा GEN8_EU_DISABLE2		_MMIO(0x913c)
#घोषणा   GEN8_EU_DIS2_S2_MASK		0xff

#घोषणा GEN9_EU_DISABLE(slice)		_MMIO(0x9134 + (slice) * 0x4)

#घोषणा GEN10_EU_DISABLE3		_MMIO(0x9140)
#घोषणा   GEN10_EU_DIS_SS_MASK		0xff

#घोषणा GEN11_GT_VEBOX_VDBOX_DISABLE	_MMIO(0x9140)
#घोषणा   GEN11_GT_VDBOX_DISABLE_MASK	0xff
#घोषणा   GEN11_GT_VEBOX_DISABLE_SHIFT	16
#घोषणा   GEN11_GT_VEBOX_DISABLE_MASK	(0x0f << GEN11_GT_VEBOX_DISABLE_SHIFT)

#घोषणा GEN11_EU_DISABLE _MMIO(0x9134)
#घोषणा GEN11_EU_DIS_MASK 0xFF

#घोषणा GEN11_GT_SLICE_ENABLE _MMIO(0x9138)
#घोषणा GEN11_GT_S_ENA_MASK 0xFF

#घोषणा GEN11_GT_SUBSLICE_DISABLE _MMIO(0x913C)

#घोषणा GEN12_GT_DSS_ENABLE _MMIO(0x913C)

#घोषणा GEN6_BSD_SLEEP_PSMI_CONTROL	_MMIO(0x12050)
#घोषणा   GEN6_BSD_SLEEP_MSG_DISABLE	(1 << 0)
#घोषणा   GEN6_BSD_SLEEP_FLUSH_DISABLE	(1 << 2)
#घोषणा   GEN6_BSD_SLEEP_INDICATOR	(1 << 3)
#घोषणा   GEN6_BSD_GO_INDICATOR		(1 << 4)

/* On modern GEN architectures पूर्णांकerrupt control consists of two sets
 * of रेजिस्टरs. The first set pertains to the ring generating the
 * पूर्णांकerrupt. The second control is क्रम the functional block generating the
 * पूर्णांकerrupt. These are PM, GT, DE, etc.
 *
 * Luckily *knocks on wood* all the ring पूर्णांकerrupt bits match up with the
 * GT पूर्णांकerrupt bits, so we करोn't need to duplicate the defines.
 *
 * These defines should cover us well from SNB->HSW with minor exceptions
 * it can also work on ILK.
 */
#घोषणा GT_BLT_FLUSHDW_NOTIFY_INTERRUPT		(1 << 26)
#घोषणा GT_BLT_CS_ERROR_INTERRUPT		(1 << 25)
#घोषणा GT_BLT_USER_INTERRUPT			(1 << 22)
#घोषणा GT_BSD_CS_ERROR_INTERRUPT		(1 << 15)
#घोषणा GT_BSD_USER_INTERRUPT			(1 << 12)
#घोषणा GT_RENDER_L3_PARITY_ERROR_INTERRUPT_S1	(1 << 11) /* hsw+; rsvd on snb, ivb, vlv */
#घोषणा GT_WAIT_SEMAPHORE_INTERRUPT		REG_BIT(11) /* bdw+ */
#घोषणा GT_CONTEXT_SWITCH_INTERRUPT		(1 <<  8)
#घोषणा GT_RENDER_L3_PARITY_ERROR_INTERRUPT	(1 <<  5) /* !snb */
#घोषणा GT_RENDER_PIPECTL_NOTIFY_INTERRUPT	(1 <<  4)
#घोषणा GT_CS_MASTER_ERROR_INTERRUPT		REG_BIT(3)
#घोषणा GT_RENDER_SYNC_STATUS_INTERRUPT		(1 <<  2)
#घोषणा GT_RENDER_DEBUG_INTERRUPT		(1 <<  1)
#घोषणा GT_RENDER_USER_INTERRUPT		(1 <<  0)

#घोषणा PM_VEBOX_CS_ERROR_INTERRUPT		(1 << 12) /* hsw+ */
#घोषणा PM_VEBOX_USER_INTERRUPT			(1 << 10) /* hsw+ */

#घोषणा GT_PARITY_ERROR(dev_priv) \
	(GT_RENDER_L3_PARITY_ERROR_INTERRUPT | \
	 (IS_HASWELL(dev_priv) ? GT_RENDER_L3_PARITY_ERROR_INTERRUPT_S1 : 0))

/* These are all the "old" पूर्णांकerrupts */
#घोषणा ILK_BSD_USER_INTERRUPT				(1 << 5)

#घोषणा I915_PM_INTERRUPT				(1 << 31)
#घोषणा I915_ISP_INTERRUPT				(1 << 22)
#घोषणा I915_LPE_PIPE_B_INTERRUPT			(1 << 21)
#घोषणा I915_LPE_PIPE_A_INTERRUPT			(1 << 20)
#घोषणा I915_MIPIC_INTERRUPT				(1 << 19)
#घोषणा I915_MIPIA_INTERRUPT				(1 << 18)
#घोषणा I915_PIPE_CONTROL_NOTIFY_INTERRUPT		(1 << 18)
#घोषणा I915_DISPLAY_PORT_INTERRUPT			(1 << 17)
#घोषणा I915_DISPLAY_PIPE_C_HBLANK_INTERRUPT		(1 << 16)
#घोषणा I915_MASTER_ERROR_INTERRUPT			(1 << 15)
#घोषणा I915_DISPLAY_PIPE_B_HBLANK_INTERRUPT		(1 << 14)
#घोषणा I915_GMCH_THERMAL_SENSOR_EVENT_INTERRUPT	(1 << 14) /* p-state */
#घोषणा I915_DISPLAY_PIPE_A_HBLANK_INTERRUPT		(1 << 13)
#घोषणा I915_HWB_OOM_INTERRUPT				(1 << 13)
#घोषणा I915_LPE_PIPE_C_INTERRUPT			(1 << 12)
#घोषणा I915_SYNC_STATUS_INTERRUPT			(1 << 12)
#घोषणा I915_MISC_INTERRUPT				(1 << 11)
#घोषणा I915_DISPLAY_PLANE_A_FLIP_PENDING_INTERRUPT	(1 << 11)
#घोषणा I915_DISPLAY_PIPE_C_VBLANK_INTERRUPT		(1 << 10)
#घोषणा I915_DISPLAY_PLANE_B_FLIP_PENDING_INTERRUPT	(1 << 10)
#घोषणा I915_DISPLAY_PIPE_C_EVENT_INTERRUPT		(1 << 9)
#घोषणा I915_OVERLAY_PLANE_FLIP_PENDING_INTERRUPT	(1 << 9)
#घोषणा I915_DISPLAY_PIPE_C_DPBM_INTERRUPT		(1 << 8)
#घोषणा I915_DISPLAY_PLANE_C_FLIP_PENDING_INTERRUPT	(1 << 8)
#घोषणा I915_DISPLAY_PIPE_A_VBLANK_INTERRUPT		(1 << 7)
#घोषणा I915_DISPLAY_PIPE_A_EVENT_INTERRUPT		(1 << 6)
#घोषणा I915_DISPLAY_PIPE_B_VBLANK_INTERRUPT		(1 << 5)
#घोषणा I915_DISPLAY_PIPE_B_EVENT_INTERRUPT		(1 << 4)
#घोषणा I915_DISPLAY_PIPE_A_DPBM_INTERRUPT		(1 << 3)
#घोषणा I915_DISPLAY_PIPE_B_DPBM_INTERRUPT		(1 << 2)
#घोषणा I915_DEBUG_INTERRUPT				(1 << 2)
#घोषणा I915_WINVALID_INTERRUPT				(1 << 1)
#घोषणा I915_USER_INTERRUPT				(1 << 1)
#घोषणा I915_ASLE_INTERRUPT				(1 << 0)
#घोषणा I915_BSD_USER_INTERRUPT				(1 << 25)

#घोषणा I915_HDMI_LPE_AUDIO_BASE	(VLV_DISPLAY_BASE + 0x65000)
#घोषणा I915_HDMI_LPE_AUDIO_SIZE	0x1000

/* DisplayPort Audio w/ LPE */
#घोषणा VLV_AUD_CHICKEN_BIT_REG		_MMIO(VLV_DISPLAY_BASE + 0x62F38)
#घोषणा VLV_CHICKEN_BIT_DBG_ENABLE	(1 << 0)

#घोषणा _VLV_AUD_PORT_EN_B_DBG		(VLV_DISPLAY_BASE + 0x62F20)
#घोषणा _VLV_AUD_PORT_EN_C_DBG		(VLV_DISPLAY_BASE + 0x62F30)
#घोषणा _VLV_AUD_PORT_EN_D_DBG		(VLV_DISPLAY_BASE + 0x62F34)
#घोषणा VLV_AUD_PORT_EN_DBG(port)	_MMIO_PORT3((port) - PORT_B,	   \
						    _VLV_AUD_PORT_EN_B_DBG, \
						    _VLV_AUD_PORT_EN_C_DBG, \
						    _VLV_AUD_PORT_EN_D_DBG)
#घोषणा VLV_AMP_MUTE		        (1 << 1)

#घोषणा GEN6_BSD_RNCID			_MMIO(0x12198)

#घोषणा GEN7_FF_THREAD_MODE		_MMIO(0x20a0)
#घोषणा   GEN7_FF_SCHED_MASK		0x0077070
#घोषणा   GEN8_FF_DS_REF_CNT_FFME	(1 << 19)
#घोषणा   GEN12_FF_TESSELATION_DOP_GATE_DISABLE BIT(19)
#घोषणा   GEN7_FF_TS_SCHED_HS1		(0x5 << 16)
#घोषणा   GEN7_FF_TS_SCHED_HS0		(0x3 << 16)
#घोषणा   GEN7_FF_TS_SCHED_LOAD_BALANCE	(0x1 << 16)
#घोषणा   GEN7_FF_TS_SCHED_HW		(0x0 << 16) /* Default */
#घोषणा   GEN7_FF_VS_REF_CNT_FFME	(1 << 15)
#घोषणा   GEN7_FF_VS_SCHED_HS1		(0x5 << 12)
#घोषणा   GEN7_FF_VS_SCHED_HS0		(0x3 << 12)
#घोषणा   GEN7_FF_VS_SCHED_LOAD_BALANCE	(0x1 << 12) /* Default */
#घोषणा   GEN7_FF_VS_SCHED_HW		(0x0 << 12)
#घोषणा   GEN7_FF_DS_SCHED_HS1		(0x5 << 4)
#घोषणा   GEN7_FF_DS_SCHED_HS0		(0x3 << 4)
#घोषणा   GEN7_FF_DS_SCHED_LOAD_BALANCE	(0x1 << 4)  /* Default */
#घोषणा   GEN7_FF_DS_SCHED_HW		(0x0 << 4)

/*
 * Framebuffer compression (915+ only)
 */

#घोषणा FBC_CFB_BASE		_MMIO(0x3200) /* 4k page aligned */
#घोषणा FBC_LL_BASE		_MMIO(0x3204) /* 4k page aligned */
#घोषणा FBC_CONTROL		_MMIO(0x3208)
#घोषणा   FBC_CTL_EN		REG_BIT(31)
#घोषणा   FBC_CTL_PERIODIC	REG_BIT(30)
#घोषणा   FBC_CTL_INTERVAL_MASK	REG_GENMASK(29, 16)
#घोषणा   FBC_CTL_INTERVAL(x)	REG_FIELD_PREP(FBC_CTL_INTERVAL_MASK, (x))
#घोषणा   FBC_CTL_STOP_ON_MOD	REG_BIT(15)
#घोषणा   FBC_CTL_UNCOMPRESSIBLE REG_BIT(14) /* i915+ */
#घोषणा   FBC_CTL_C3_IDLE	REG_BIT(13) /* i945gm */
#घोषणा   FBC_CTL_STRIDE_MASK	REG_GENMASK(12, 5)
#घोषणा   FBC_CTL_STRIDE(x)	REG_FIELD_PREP(FBC_CTL_STRIDE_MASK, (x))
#घोषणा   FBC_CTL_FENCENO_MASK	REG_GENMASK(3, 0)
#घोषणा   FBC_CTL_FENCENO(x)	REG_FIELD_PREP(FBC_CTL_FENCENO_MASK, (x))
#घोषणा FBC_COMMAND		_MMIO(0x320c)
#घोषणा   FBC_CMD_COMPRESS	(1 << 0)
#घोषणा FBC_STATUS		_MMIO(0x3210)
#घोषणा   FBC_STAT_COMPRESSING	(1 << 31)
#घोषणा   FBC_STAT_COMPRESSED	(1 << 30)
#घोषणा   FBC_STAT_MODIFIED	(1 << 29)
#घोषणा   FBC_STAT_CURRENT_LINE_SHIFT	(0)
#घोषणा FBC_CONTROL2		_MMIO(0x3214)
#घोषणा   FBC_CTL_FENCE_DBL	(0 << 4)
#घोषणा   FBC_CTL_IDLE_IMM	(0 << 2)
#घोषणा   FBC_CTL_IDLE_FULL	(1 << 2)
#घोषणा   FBC_CTL_IDLE_LINE	(2 << 2)
#घोषणा   FBC_CTL_IDLE_DEBUG	(3 << 2)
#घोषणा   FBC_CTL_CPU_FENCE	(1 << 1)
#घोषणा   FBC_CTL_PLANE(plane)	((plane) << 0)
#घोषणा FBC_FENCE_OFF		_MMIO(0x3218) /* BSpec typo has 321Bh */
#घोषणा FBC_TAG(i)		_MMIO(0x3300 + (i) * 4)

#घोषणा FBC_LL_SIZE		(1536)

#घोषणा FBC_LLC_READ_CTRL	_MMIO(0x9044)
#घोषणा   FBC_LLC_FULLY_OPEN	(1 << 30)

/* Framebuffer compression क्रम GM45+ */
#घोषणा DPFC_CB_BASE		_MMIO(0x3200)
#घोषणा DPFC_CONTROL		_MMIO(0x3208)
#घोषणा   DPFC_CTL_EN		(1 << 31)
#घोषणा   DPFC_CTL_PLANE(plane)	((plane) << 30)
#घोषणा   IVB_DPFC_CTL_PLANE(plane)	((plane) << 29)
#घोषणा   DPFC_CTL_FENCE_EN	(1 << 29)
#घोषणा   IVB_DPFC_CTL_FENCE_EN	(1 << 28)
#घोषणा   DPFC_CTL_PERSISTENT_MODE	(1 << 25)
#घोषणा   DPFC_SR_EN		(1 << 10)
#घोषणा   DPFC_CTL_LIMIT_1X	(0 << 6)
#घोषणा   DPFC_CTL_LIMIT_2X	(1 << 6)
#घोषणा   DPFC_CTL_LIMIT_4X	(2 << 6)
#घोषणा DPFC_RECOMP_CTL		_MMIO(0x320c)
#घोषणा   DPFC_RECOMP_STALL_EN	(1 << 27)
#घोषणा   DPFC_RECOMP_STALL_WM_SHIFT (16)
#घोषणा   DPFC_RECOMP_STALL_WM_MASK (0x07ff0000)
#घोषणा   DPFC_RECOMP_TIMER_COUNT_SHIFT (0)
#घोषणा   DPFC_RECOMP_TIMER_COUNT_MASK (0x0000003f)
#घोषणा DPFC_STATUS		_MMIO(0x3210)
#घोषणा   DPFC_INVAL_SEG_SHIFT  (16)
#घोषणा   DPFC_INVAL_SEG_MASK	(0x07ff0000)
#घोषणा   DPFC_COMP_SEG_SHIFT	(0)
#घोषणा   DPFC_COMP_SEG_MASK	(0x000007ff)
#घोषणा DPFC_STATUS2		_MMIO(0x3214)
#घोषणा DPFC_FENCE_YOFF		_MMIO(0x3218)
#घोषणा DPFC_CHICKEN		_MMIO(0x3224)
#घोषणा   DPFC_HT_MODIFY	(1 << 31)

/* Framebuffer compression क्रम Ironlake */
#घोषणा ILK_DPFC_CB_BASE	_MMIO(0x43200)
#घोषणा ILK_DPFC_CONTROL	_MMIO(0x43208)
#घोषणा   FBC_CTL_FALSE_COLOR	(1 << 10)
/* The bit 28-8 is reserved */
#घोषणा   DPFC_RESERVED		(0x1FFFFF00)
#घोषणा ILK_DPFC_RECOMP_CTL	_MMIO(0x4320c)
#घोषणा ILK_DPFC_STATUS		_MMIO(0x43210)
#घोषणा  ILK_DPFC_COMP_SEG_MASK	0x7ff
#घोषणा IVB_FBC_STATUS2		_MMIO(0x43214)
#घोषणा  IVB_FBC_COMP_SEG_MASK	0x7ff
#घोषणा  BDW_FBC_COMP_SEG_MASK	0xfff
#घोषणा ILK_DPFC_FENCE_YOFF	_MMIO(0x43218)
#घोषणा ILK_DPFC_CHICKEN	_MMIO(0x43224)
#घोषणा   ILK_DPFC_DISABLE_DUMMY0 (1 << 8)
#घोषणा   ILK_DPFC_CHICKEN_COMP_DUMMY_PIXEL	(1 << 14)
#घोषणा   ILK_DPFC_NUKE_ON_ANY_MODIFICATION	(1 << 23)
#घोषणा ILK_FBC_RT_BASE		_MMIO(0x2128)
#घोषणा   ILK_FBC_RT_VALID	(1 << 0)
#घोषणा   SNB_FBC_FRONT_BUFFER	(1 << 1)

#घोषणा ILK_DISPLAY_CHICKEN1	_MMIO(0x42000)
#घोषणा   ILK_FBCQ_DIS		(1 << 22)
#घोषणा   ILK_PABSTRETCH_DIS	REG_BIT(21)
#घोषणा   ILK_SABSTRETCH_DIS	REG_BIT(20)
#घोषणा   IVB_PRI_STRETCH_MAX_MASK	REG_GENMASK(21, 20)
#घोषणा   IVB_PRI_STRETCH_MAX_X8	REG_FIELD_PREP(IVB_PRI_STRETCH_MAX_MASK, 0)
#घोषणा   IVB_PRI_STRETCH_MAX_X4	REG_FIELD_PREP(IVB_PRI_STRETCH_MAX_MASK, 1)
#घोषणा   IVB_PRI_STRETCH_MAX_X2	REG_FIELD_PREP(IVB_PRI_STRETCH_MAX_MASK, 2)
#घोषणा   IVB_PRI_STRETCH_MAX_X1	REG_FIELD_PREP(IVB_PRI_STRETCH_MAX_MASK, 3)
#घोषणा   IVB_SPR_STRETCH_MAX_MASK	REG_GENMASK(19, 18)
#घोषणा   IVB_SPR_STRETCH_MAX_X8	REG_FIELD_PREP(IVB_SPR_STRETCH_MAX_MASK, 0)
#घोषणा   IVB_SPR_STRETCH_MAX_X4	REG_FIELD_PREP(IVB_SPR_STRETCH_MAX_MASK, 1)
#घोषणा   IVB_SPR_STRETCH_MAX_X2	REG_FIELD_PREP(IVB_SPR_STRETCH_MAX_MASK, 2)
#घोषणा   IVB_SPR_STRETCH_MAX_X1	REG_FIELD_PREP(IVB_SPR_STRETCH_MAX_MASK, 3)


/*
 * Framebuffer compression क्रम Sandybridge
 *
 * The following two रेजिस्टरs are of type GTTMMADR
 */
#घोषणा SNB_DPFC_CTL_SA		_MMIO(0x100100)
#घोषणा   SNB_CPU_FENCE_ENABLE	(1 << 29)
#घोषणा DPFC_CPU_FENCE_OFFSET	_MMIO(0x100104)

/* Framebuffer compression क्रम Ivybridge */
#घोषणा IVB_FBC_RT_BASE			_MMIO(0x7020)
#घोषणा IVB_FBC_RT_BASE_UPPER		_MMIO(0x7024)

#घोषणा IPS_CTL		_MMIO(0x43408)
#घोषणा   IPS_ENABLE	(1 << 31)

#घोषणा MSG_FBC_REND_STATE	_MMIO(0x50380)
#घोषणा   FBC_REND_NUKE		(1 << 2)
#घोषणा   FBC_REND_CACHE_CLEAN	(1 << 1)

/*
 * GPIO regs
 */
#घोषणा GPIO(gpio)		_MMIO(dev_priv->gpio_mmio_base + 0x5010 + \
				      4 * (gpio))

# define GPIO_CLOCK_सूची_MASK		(1 << 0)
# define GPIO_CLOCK_सूची_IN		(0 << 1)
# define GPIO_CLOCK_सूची_OUT		(1 << 1)
# define GPIO_CLOCK_VAL_MASK		(1 << 2)
# define GPIO_CLOCK_VAL_OUT		(1 << 3)
# define GPIO_CLOCK_VAL_IN		(1 << 4)
# define GPIO_CLOCK_PULLUP_DISABLE	(1 << 5)
# define GPIO_DATA_सूची_MASK		(1 << 8)
# define GPIO_DATA_सूची_IN		(0 << 9)
# define GPIO_DATA_सूची_OUT		(1 << 9)
# define GPIO_DATA_VAL_MASK		(1 << 10)
# define GPIO_DATA_VAL_OUT		(1 << 11)
# define GPIO_DATA_VAL_IN		(1 << 12)
# define GPIO_DATA_PULLUP_DISABLE	(1 << 13)

#घोषणा GMBUS0			_MMIO(dev_priv->gpio_mmio_base + 0x5100) /* घड़ी/port select */
#घोषणा   GMBUS_AKSV_SELECT	(1 << 11)
#घोषणा   GMBUS_RATE_100KHZ	(0 << 8)
#घोषणा   GMBUS_RATE_50KHZ	(1 << 8)
#घोषणा   GMBUS_RATE_400KHZ	(2 << 8) /* reserved on Pineview */
#घोषणा   GMBUS_RATE_1MHZ	(3 << 8) /* reserved on Pineview */
#घोषणा   GMBUS_HOLD_EXT	(1 << 7) /* 300ns hold समय, rsvd on Pineview */
#घोषणा   GMBUS_BYTE_CNT_OVERRIDE (1 << 6)

#घोषणा GMBUS1			_MMIO(dev_priv->gpio_mmio_base + 0x5104) /* command/status */
#घोषणा   GMBUS_SW_CLR_INT	(1 << 31)
#घोषणा   GMBUS_SW_RDY		(1 << 30)
#घोषणा   GMBUS_ENT		(1 << 29) /* enable समयout */
#घोषणा   GMBUS_CYCLE_NONE	(0 << 25)
#घोषणा   GMBUS_CYCLE_WAIT	(1 << 25)
#घोषणा   GMBUS_CYCLE_INDEX	(2 << 25)
#घोषणा   GMBUS_CYCLE_STOP	(4 << 25)
#घोषणा   GMBUS_BYTE_COUNT_SHIFT 16
#घोषणा   GMBUS_BYTE_COUNT_MAX   256U
#घोषणा   GEN9_GMBUS_BYTE_COUNT_MAX 511U
#घोषणा   GMBUS_SLAVE_INDEX_SHIFT 8
#घोषणा   GMBUS_SLAVE_ADDR_SHIFT 1
#घोषणा   GMBUS_SLAVE_READ	(1 << 0)
#घोषणा   GMBUS_SLAVE_WRITE	(0 << 0)
#घोषणा GMBUS2			_MMIO(dev_priv->gpio_mmio_base + 0x5108) /* status */
#घोषणा   GMBUS_INUSE		(1 << 15)
#घोषणा   GMBUS_HW_WAIT_PHASE	(1 << 14)
#घोषणा   GMBUS_STALL_TIMEOUT	(1 << 13)
#घोषणा   GMBUS_INT		(1 << 12)
#घोषणा   GMBUS_HW_RDY		(1 << 11)
#घोषणा   GMBUS_SATOER		(1 << 10)
#घोषणा   GMBUS_ACTIVE		(1 << 9)
#घोषणा GMBUS3			_MMIO(dev_priv->gpio_mmio_base + 0x510c) /* data buffer bytes 3-0 */
#घोषणा GMBUS4			_MMIO(dev_priv->gpio_mmio_base + 0x5110) /* पूर्णांकerrupt mask (Pineview+) */
#घोषणा   GMBUS_SLAVE_TIMEOUT_EN (1 << 4)
#घोषणा   GMBUS_NAK_EN		(1 << 3)
#घोषणा   GMBUS_IDLE_EN		(1 << 2)
#घोषणा   GMBUS_HW_WAIT_EN	(1 << 1)
#घोषणा   GMBUS_HW_RDY_EN	(1 << 0)
#घोषणा GMBUS5			_MMIO(dev_priv->gpio_mmio_base + 0x5120) /* byte index */
#घोषणा   GMBUS_2BYTE_INDEX_EN	(1 << 31)

/*
 * Clock control & घातer management
 */
#घोषणा _DPLL_A (DISPLAY_MMIO_BASE(dev_priv) + 0x6014)
#घोषणा _DPLL_B (DISPLAY_MMIO_BASE(dev_priv) + 0x6018)
#घोषणा _CHV_DPLL_C (DISPLAY_MMIO_BASE(dev_priv) + 0x6030)
#घोषणा DPLL(pipe) _MMIO_PIPE3((pipe), _DPLL_A, _DPLL_B, _CHV_DPLL_C)

#घोषणा VGA0	_MMIO(0x6000)
#घोषणा VGA1	_MMIO(0x6004)
#घोषणा VGA_PD	_MMIO(0x6010)
#घोषणा   VGA0_PD_P2_DIV_4	(1 << 7)
#घोषणा   VGA0_PD_P1_DIV_2	(1 << 5)
#घोषणा   VGA0_PD_P1_SHIFT	0
#घोषणा   VGA0_PD_P1_MASK	(0x1f << 0)
#घोषणा   VGA1_PD_P2_DIV_4	(1 << 15)
#घोषणा   VGA1_PD_P1_DIV_2	(1 << 13)
#घोषणा   VGA1_PD_P1_SHIFT	8
#घोषणा   VGA1_PD_P1_MASK	(0x1f << 8)
#घोषणा   DPLL_VCO_ENABLE		(1 << 31)
#घोषणा   DPLL_SDVO_HIGH_SPEED		(1 << 30)
#घोषणा   DPLL_DVO_2X_MODE		(1 << 30)
#घोषणा   DPLL_EXT_BUFFER_ENABLE_VLV	(1 << 30)
#घोषणा   DPLL_SYNCLOCK_ENABLE		(1 << 29)
#घोषणा   DPLL_REF_CLK_ENABLE_VLV	(1 << 29)
#घोषणा   DPLL_VGA_MODE_DIS		(1 << 28)
#घोषणा   DPLLB_MODE_DAC_SERIAL		(1 << 26) /* i915 */
#घोषणा   DPLLB_MODE_LVDS		(2 << 26) /* i915 */
#घोषणा   DPLL_MODE_MASK		(3 << 26)
#घोषणा   DPLL_DAC_SERIAL_P2_CLOCK_DIV_10 (0 << 24) /* i915 */
#घोषणा   DPLL_DAC_SERIAL_P2_CLOCK_DIV_5 (1 << 24) /* i915 */
#घोषणा   DPLLB_LVDS_P2_CLOCK_DIV_14	(0 << 24) /* i915 */
#घोषणा   DPLLB_LVDS_P2_CLOCK_DIV_7	(1 << 24) /* i915 */
#घोषणा   DPLL_P2_CLOCK_DIV_MASK	0x03000000 /* i915 */
#घोषणा   DPLL_FPA01_P1_POST_DIV_MASK	0x00ff0000 /* i915 */
#घोषणा   DPLL_FPA01_P1_POST_DIV_MASK_PINEVIEW	0x00ff8000 /* Pineview */
#घोषणा   DPLL_LOCK_VLV			(1 << 15)
#घोषणा   DPLL_INTEGRATED_CRI_CLK_VLV	(1 << 14)
#घोषणा   DPLL_INTEGRATED_REF_CLK_VLV	(1 << 13)
#घोषणा   DPLL_SSC_REF_CLK_CHV		(1 << 13)
#घोषणा   DPLL_PORTC_READY_MASK		(0xf << 4)
#घोषणा   DPLL_PORTB_READY_MASK		(0xf)

#घोषणा   DPLL_FPA01_P1_POST_DIV_MASK_I830	0x001f0000

/* Additional CHV pll/phy रेजिस्टरs */
#घोषणा DPIO_PHY_STATUS			_MMIO(VLV_DISPLAY_BASE + 0x6240)
#घोषणा   DPLL_PORTD_READY_MASK		(0xf)
#घोषणा DISPLAY_PHY_CONTROL _MMIO(VLV_DISPLAY_BASE + 0x60100)
#घोषणा   PHY_CH_POWER_DOWN_OVRD_EN(phy, ch)	(1 << (2 * (phy) + (ch) + 27))
#घोषणा   PHY_LDO_DELAY_0NS			0x0
#घोषणा   PHY_LDO_DELAY_200NS			0x1
#घोषणा   PHY_LDO_DELAY_600NS			0x2
#घोषणा   PHY_LDO_SEQ_DELAY(delay, phy)		((delay) << (2 * (phy) + 23))
#घोषणा   PHY_CH_POWER_DOWN_OVRD(mask, phy, ch)	((mask) << (8 * (phy) + 4 * (ch) + 11))
#घोषणा   PHY_CH_SU_PSR				0x1
#घोषणा   PHY_CH_DEEP_PSR			0x7
#घोषणा   PHY_CH_POWER_MODE(mode, phy, ch)	((mode) << (6 * (phy) + 3 * (ch) + 2))
#घोषणा   PHY_COM_LANE_RESET_DEASSERT(phy)	(1 << (phy))
#घोषणा DISPLAY_PHY_STATUS _MMIO(VLV_DISPLAY_BASE + 0x60104)
#घोषणा   PHY_POWERGOOD(phy)	(((phy) == DPIO_PHY0) ? (1 << 31) : (1 << 30))
#घोषणा   PHY_STATUS_CMN_LDO(phy, ch)                   (1 << (6 - (6 * (phy) + 3 * (ch))))
#घोषणा   PHY_STATUS_SPLINE_LDO(phy, ch, spline)        (1 << (8 - (6 * (phy) + 3 * (ch) + (spline))))

/*
 * The i830 generation, in LVDS mode, defines P1 as the bit number set within
 * this field (only one bit may be set).
 */
#घोषणा   DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS	0x003f0000
#घोषणा   DPLL_FPA01_P1_POST_DIV_SHIFT	16
#घोषणा   DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW 15
/* i830, required in DVO non-gang */
#घोषणा   PLL_P2_DIVIDE_BY_4		(1 << 23)
#घोषणा   PLL_P1_DIVIDE_BY_TWO		(1 << 21) /* i830 */
#घोषणा   PLL_REF_INPUT_DREFCLK		(0 << 13)
#घोषणा   PLL_REF_INPUT_TVCLKINA	(1 << 13) /* i830 */
#घोषणा   PLL_REF_INPUT_TVCLKINBC	(2 << 13) /* SDVO TVCLKIN */
#घोषणा   PLLB_REF_INPUT_SPREADSPECTRUMIN (3 << 13)
#घोषणा   PLL_REF_INPUT_MASK		(3 << 13)
#घोषणा   PLL_LOAD_PULSE_PHASE_SHIFT		9
/* Ironlake */
# define PLL_REF_SDVO_HDMI_MULTIPLIER_SHIFT     9
# define PLL_REF_SDVO_HDMI_MULTIPLIER_MASK      (7 << 9)
# define PLL_REF_SDVO_HDMI_MULTIPLIER(x)	(((x) - 1) << 9)
# define DPLL_FPA1_P1_POST_DIV_SHIFT            0
# define DPLL_FPA1_P1_POST_DIV_MASK             0xff

/*
 * Parallel to Serial Load Pulse phase selection.
 * Selects the phase क्रम the 10X DPLL घड़ी क्रम the PCIe
 * digital display port. The range is 4 to 13; 10 or more
 * is just a flip delay. The शेष is 6
 */
#घोषणा   PLL_LOAD_PULSE_PHASE_MASK		(0xf << PLL_LOAD_PULSE_PHASE_SHIFT)
#घोषणा   DISPLAY_RATE_SELECT_FPA1		(1 << 8)
/*
 * SDVO multiplier क्रम 945G/GM. Not used on 965.
 */
#घोषणा   SDVO_MULTIPLIER_MASK			0x000000ff
#घोषणा   SDVO_MULTIPLIER_SHIFT_HIRES		4
#घोषणा   SDVO_MULTIPLIER_SHIFT_VGA		0

#घोषणा _DPLL_A_MD (DISPLAY_MMIO_BASE(dev_priv) + 0x601c)
#घोषणा _DPLL_B_MD (DISPLAY_MMIO_BASE(dev_priv) + 0x6020)
#घोषणा _CHV_DPLL_C_MD (DISPLAY_MMIO_BASE(dev_priv) + 0x603c)
#घोषणा DPLL_MD(pipe) _MMIO_PIPE3((pipe), _DPLL_A_MD, _DPLL_B_MD, _CHV_DPLL_C_MD)

/*
 * UDI pixel भागider, controlling how many pixels are stuffed पूर्णांकo a packet.
 *
 * Value is pixels minus 1.  Must be set to 1 pixel क्रम SDVO.
 */
#घोषणा   DPLL_MD_UDI_DIVIDER_MASK		0x3f000000
#घोषणा   DPLL_MD_UDI_DIVIDER_SHIFT		24
/* UDI pixel भागider क्रम VGA, same as DPLL_MD_UDI_DIVIDER_MASK. */
#घोषणा   DPLL_MD_VGA_UDI_DIVIDER_MASK		0x003f0000
#घोषणा   DPLL_MD_VGA_UDI_DIVIDER_SHIFT		16
/*
 * SDVO/UDI pixel multiplier.
 *
 * SDVO requires that the bus घड़ी rate be between 1 and 2 Ghz, and the bus
 * घड़ी rate is 10 बार the DPLL घड़ी.  At low resolution/refresh rate
 * modes, the bus rate would be below the limits, so SDVO allows क्रम stuffing
 * dummy bytes in the datastream at an increased घड़ी rate, with both sides of
 * the link knowing how many bytes are fill.
 *
 * So, क्रम a mode with a करोtघड़ी of 65Mhz, we would want to द्विगुन the घड़ी
 * rate to 130Mhz to get a bus rate of 1.30Ghz.  The DPLL घड़ी rate would be
 * set to 130Mhz, and the SDVO multiplier set to 2x in this रेजिस्टर and
 * through an SDVO command.
 *
 * This रेजिस्टर field has values of multiplication factor minus 1, with
 * a maximum multiplier of 5 क्रम SDVO.
 */
#घोषणा   DPLL_MD_UDI_MULTIPLIER_MASK		0x00003f00
#घोषणा   DPLL_MD_UDI_MULTIPLIER_SHIFT		8
/*
 * SDVO/UDI pixel multiplier क्रम VGA, same as DPLL_MD_UDI_MULTIPLIER_MASK.
 * This best be set to the शेष value (3) or the CRT won't work. No,
 * I करोn't entirely understand what this करोes...
 */
#घोषणा   DPLL_MD_VGA_UDI_MULTIPLIER_MASK	0x0000003f
#घोषणा   DPLL_MD_VGA_UDI_MULTIPLIER_SHIFT	0

#घोषणा RAWCLK_FREQ_VLV		_MMIO(VLV_DISPLAY_BASE + 0x6024)

#घोषणा _FPA0	0x6040
#घोषणा _FPA1	0x6044
#घोषणा _FPB0	0x6048
#घोषणा _FPB1	0x604c
#घोषणा FP0(pipe) _MMIO_PIPE(pipe, _FPA0, _FPB0)
#घोषणा FP1(pipe) _MMIO_PIPE(pipe, _FPA1, _FPB1)
#घोषणा   FP_N_DIV_MASK		0x003f0000
#घोषणा   FP_N_PINEVIEW_DIV_MASK	0x00ff0000
#घोषणा   FP_N_DIV_SHIFT		16
#घोषणा   FP_M1_DIV_MASK	0x00003f00
#घोषणा   FP_M1_DIV_SHIFT		 8
#घोषणा   FP_M2_DIV_MASK	0x0000003f
#घोषणा   FP_M2_PINEVIEW_DIV_MASK	0x000000ff
#घोषणा   FP_M2_DIV_SHIFT		 0
#घोषणा DPLL_TEST	_MMIO(0x606c)
#घोषणा   DPLLB_TEST_SDVO_DIV_1		(0 << 22)
#घोषणा   DPLLB_TEST_SDVO_DIV_2		(1 << 22)
#घोषणा   DPLLB_TEST_SDVO_DIV_4		(2 << 22)
#घोषणा   DPLLB_TEST_SDVO_DIV_MASK	(3 << 22)
#घोषणा   DPLLB_TEST_N_BYPASS		(1 << 19)
#घोषणा   DPLLB_TEST_M_BYPASS		(1 << 18)
#घोषणा   DPLLB_INPUT_BUFFER_ENABLE	(1 << 16)
#घोषणा   DPLLA_TEST_N_BYPASS		(1 << 3)
#घोषणा   DPLLA_TEST_M_BYPASS		(1 << 2)
#घोषणा   DPLLA_INPUT_BUFFER_ENABLE	(1 << 0)
#घोषणा D_STATE		_MMIO(0x6104)
#घोषणा  DSTATE_GFX_RESET_I830			(1 << 6)
#घोषणा  DSTATE_PLL_D3_OFF			(1 << 3)
#घोषणा  DSTATE_GFX_CLOCK_GATING		(1 << 1)
#घोषणा  DSTATE_DOT_CLOCK_GATING		(1 << 0)
#घोषणा DSPCLK_GATE_D	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x6200)
# define DPUNIT_B_CLOCK_GATE_DISABLE		(1 << 30) /* 965 */
# define VSUNIT_CLOCK_GATE_DISABLE		(1 << 29) /* 965 */
# define VRHUNIT_CLOCK_GATE_DISABLE		(1 << 28) /* 965 */
# define VRDUNIT_CLOCK_GATE_DISABLE		(1 << 27) /* 965 */
# define AUDUNIT_CLOCK_GATE_DISABLE		(1 << 26) /* 965 */
# define DPUNIT_A_CLOCK_GATE_DISABLE		(1 << 25) /* 965 */
# define DPCUNIT_CLOCK_GATE_DISABLE		(1 << 24) /* 965 */
# define PNV_GMBUSUNIT_CLOCK_GATE_DISABLE	(1 << 24) /* pnv */
# define TVRUNIT_CLOCK_GATE_DISABLE		(1 << 23) /* 915-945 */
# define TVCUNIT_CLOCK_GATE_DISABLE		(1 << 22) /* 915-945 */
# define TVFUNIT_CLOCK_GATE_DISABLE		(1 << 21) /* 915-945 */
# define TVEUNIT_CLOCK_GATE_DISABLE		(1 << 20) /* 915-945 */
# define DVSUNIT_CLOCK_GATE_DISABLE		(1 << 19) /* 915-945 */
# define DSSUNIT_CLOCK_GATE_DISABLE		(1 << 18) /* 915-945 */
# define DDBUNIT_CLOCK_GATE_DISABLE		(1 << 17) /* 915-945 */
# define DPRUNIT_CLOCK_GATE_DISABLE		(1 << 16) /* 915-945 */
# define DPFUNIT_CLOCK_GATE_DISABLE		(1 << 15) /* 915-945 */
# define DPBMUNIT_CLOCK_GATE_DISABLE		(1 << 14) /* 915-945 */
# define DPLSUNIT_CLOCK_GATE_DISABLE		(1 << 13) /* 915-945 */
# define DPLUNIT_CLOCK_GATE_DISABLE		(1 << 12) /* 915-945 */
# define DPOUNIT_CLOCK_GATE_DISABLE		(1 << 11)
# define DPBUNIT_CLOCK_GATE_DISABLE		(1 << 10)
# define DCUNIT_CLOCK_GATE_DISABLE		(1 << 9)
# define DPUNIT_CLOCK_GATE_DISABLE		(1 << 8)
# define VRUNIT_CLOCK_GATE_DISABLE		(1 << 7) /* 915+: reserved */
# define OVHUNIT_CLOCK_GATE_DISABLE		(1 << 6) /* 830-865 */
# define DPIOUNIT_CLOCK_GATE_DISABLE		(1 << 6) /* 915-945 */
# define OVFUNIT_CLOCK_GATE_DISABLE		(1 << 5)
# define OVBUNIT_CLOCK_GATE_DISABLE		(1 << 4)
/*
 * This bit must be set on the 830 to prevent hangs when turning off the
 * overlay scaler.
 */
# define OVRUNIT_CLOCK_GATE_DISABLE		(1 << 3)
# define OVCUNIT_CLOCK_GATE_DISABLE		(1 << 2)
# define OVUUNIT_CLOCK_GATE_DISABLE		(1 << 1)
# define ZVUNIT_CLOCK_GATE_DISABLE		(1 << 0) /* 830 */
# define OVLUNIT_CLOCK_GATE_DISABLE		(1 << 0) /* 845,865 */

#घोषणा RENCLK_GATE_D1		_MMIO(0x6204)
# define BLITTER_CLOCK_GATE_DISABLE		(1 << 13) /* 945GM only */
# define MPEG_CLOCK_GATE_DISABLE		(1 << 12) /* 945GM only */
# define PC_FE_CLOCK_GATE_DISABLE		(1 << 11)
# define PC_BE_CLOCK_GATE_DISABLE		(1 << 10)
# define WINDOWER_CLOCK_GATE_DISABLE		(1 << 9)
# define INTERPOLATOR_CLOCK_GATE_DISABLE	(1 << 8)
# define COLOR_CALCULATOR_CLOCK_GATE_DISABLE	(1 << 7)
# define MOTION_COMP_CLOCK_GATE_DISABLE		(1 << 6)
# define MAG_CLOCK_GATE_DISABLE			(1 << 5)
/* This bit must be unset on 855,865 */
# define MECI_CLOCK_GATE_DISABLE		(1 << 4)
# define DCMP_CLOCK_GATE_DISABLE		(1 << 3)
# define MEC_CLOCK_GATE_DISABLE			(1 << 2)
# define MECO_CLOCK_GATE_DISABLE		(1 << 1)
/* This bit must be set on 855,865. */
# define SV_CLOCK_GATE_DISABLE			(1 << 0)
# define I915_MPEG_CLOCK_GATE_DISABLE		(1 << 16)
# define I915_VLD_IP_PR_CLOCK_GATE_DISABLE	(1 << 15)
# define I915_MOTION_COMP_CLOCK_GATE_DISABLE	(1 << 14)
# define I915_BD_BF_CLOCK_GATE_DISABLE		(1 << 13)
# define I915_SF_SE_CLOCK_GATE_DISABLE		(1 << 12)
# define I915_WM_CLOCK_GATE_DISABLE		(1 << 11)
# define I915_IZ_CLOCK_GATE_DISABLE		(1 << 10)
# define I915_PI_CLOCK_GATE_DISABLE		(1 << 9)
# define I915_DI_CLOCK_GATE_DISABLE		(1 << 8)
# define I915_SH_SV_CLOCK_GATE_DISABLE		(1 << 7)
# define I915_PL_DG_QC_FT_CLOCK_GATE_DISABLE	(1 << 6)
# define I915_SC_CLOCK_GATE_DISABLE		(1 << 5)
# define I915_FL_CLOCK_GATE_DISABLE		(1 << 4)
# define I915_DM_CLOCK_GATE_DISABLE		(1 << 3)
# define I915_PS_CLOCK_GATE_DISABLE		(1 << 2)
# define I915_CC_CLOCK_GATE_DISABLE		(1 << 1)
# define I915_BY_CLOCK_GATE_DISABLE		(1 << 0)

# define I965_RCZ_CLOCK_GATE_DISABLE		(1 << 30)
/* This bit must always be set on 965G/965GM */
# define I965_RCC_CLOCK_GATE_DISABLE		(1 << 29)
# define I965_RCPB_CLOCK_GATE_DISABLE		(1 << 28)
# define I965_DAP_CLOCK_GATE_DISABLE		(1 << 27)
# define I965_ROC_CLOCK_GATE_DISABLE		(1 << 26)
# define I965_GW_CLOCK_GATE_DISABLE		(1 << 25)
# define I965_TD_CLOCK_GATE_DISABLE		(1 << 24)
/* This bit must always be set on 965G */
# define I965_ISC_CLOCK_GATE_DISABLE		(1 << 23)
# define I965_IC_CLOCK_GATE_DISABLE		(1 << 22)
# define I965_EU_CLOCK_GATE_DISABLE		(1 << 21)
# define I965_IF_CLOCK_GATE_DISABLE		(1 << 20)
# define I965_TC_CLOCK_GATE_DISABLE		(1 << 19)
# define I965_SO_CLOCK_GATE_DISABLE		(1 << 17)
# define I965_FBC_CLOCK_GATE_DISABLE		(1 << 16)
# define I965_MARI_CLOCK_GATE_DISABLE		(1 << 15)
# define I965_MASF_CLOCK_GATE_DISABLE		(1 << 14)
# define I965_MAWB_CLOCK_GATE_DISABLE		(1 << 13)
# define I965_EM_CLOCK_GATE_DISABLE		(1 << 12)
# define I965_UC_CLOCK_GATE_DISABLE		(1 << 11)
# define I965_SI_CLOCK_GATE_DISABLE		(1 << 6)
# define I965_MT_CLOCK_GATE_DISABLE		(1 << 5)
# define I965_PL_CLOCK_GATE_DISABLE		(1 << 4)
# define I965_DG_CLOCK_GATE_DISABLE		(1 << 3)
# define I965_QC_CLOCK_GATE_DISABLE		(1 << 2)
# define I965_FT_CLOCK_GATE_DISABLE		(1 << 1)
# define I965_DM_CLOCK_GATE_DISABLE		(1 << 0)

#घोषणा RENCLK_GATE_D2		_MMIO(0x6208)
#घोषणा VF_UNIT_CLOCK_GATE_DISABLE		(1 << 9)
#घोषणा GS_UNIT_CLOCK_GATE_DISABLE		(1 << 7)
#घोषणा CL_UNIT_CLOCK_GATE_DISABLE		(1 << 6)

#घोषणा VDECCLK_GATE_D		_MMIO(0x620C)		/* g4x only */
#घोषणा  VCP_UNIT_CLOCK_GATE_DISABLE		(1 << 4)

#घोषणा RAMCLK_GATE_D		_MMIO(0x6210)		/* CRL only */
#घोषणा DEUC			_MMIO(0x6214)          /* CRL only */

#घोषणा FW_BLC_SELF_VLV		_MMIO(VLV_DISPLAY_BASE + 0x6500)
#घोषणा  FW_CSPWRDWNEN		(1 << 15)

#घोषणा MI_ARB_VLV		_MMIO(VLV_DISPLAY_BASE + 0x6504)

#घोषणा CZCLK_CDCLK_FREQ_RATIO	_MMIO(VLV_DISPLAY_BASE + 0x6508)
#घोषणा   CDCLK_FREQ_SHIFT	4
#घोषणा   CDCLK_FREQ_MASK	(0x1f << CDCLK_FREQ_SHIFT)
#घोषणा   CZCLK_FREQ_MASK	0xf

#घोषणा GCI_CONTROL		_MMIO(VLV_DISPLAY_BASE + 0x650C)
#घोषणा   PFI_CREDIT_63		(9 << 28)		/* chv only */
#घोषणा   PFI_CREDIT_31		(8 << 28)		/* chv only */
#घोषणा   PFI_CREDIT(x)		(((x) - 8) << 28)	/* 8-15 */
#घोषणा   PFI_CREDIT_RESEND	(1 << 27)
#घोषणा   VGA_FAST_MODE_DISABLE	(1 << 14)

#घोषणा GMBUSFREQ_VLV		_MMIO(VLV_DISPLAY_BASE + 0x6510)

/*
 * Palette regs
 */
#घोषणा _PALETTE_A		0xa000
#घोषणा _PALETTE_B		0xa800
#घोषणा _CHV_PALETTE_C		0xc000
#घोषणा PALETTE_RED_MASK        REG_GENMASK(23, 16)
#घोषणा PALETTE_GREEN_MASK      REG_GENMASK(15, 8)
#घोषणा PALETTE_BLUE_MASK       REG_GENMASK(7, 0)
#घोषणा PALETTE(pipe, i)	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + \
				      _PICK((pipe), _PALETTE_A,		\
					    _PALETTE_B, _CHV_PALETTE_C) + \
				      (i) * 4)

/* MCH MMIO space */

/*
 * MCHBAR mirror.
 *
 * This mirrors the MCHBAR MMIO space whose location is determined by
 * device 0 function 0's pci config रेजिस्टर 0x44 or 0x48 and matches it in
 * every way.  It is not accessible from the CP रेजिस्टर पढ़ो inकाष्ठाions.
 *
 * Starting from Haswell, you can't ग_लिखो रेजिस्टरs using the MCHBAR mirror,
 * just पढ़ो.
 */
#घोषणा MCHBAR_MIRROR_BASE	0x10000

#घोषणा MCHBAR_MIRROR_BASE_SNB	0x140000

#घोषणा CTG_STOLEN_RESERVED		_MMIO(MCHBAR_MIRROR_BASE + 0x34)
#घोषणा ELK_STOLEN_RESERVED		_MMIO(MCHBAR_MIRROR_BASE + 0x48)
#घोषणा G4X_STOLEN_RESERVED_ADDR1_MASK	(0xFFFF << 16)
#घोषणा G4X_STOLEN_RESERVED_ADDR2_MASK	(0xFFF << 4)
#घोषणा G4X_STOLEN_RESERVED_ENABLE	(1 << 0)

/* Memory controller frequency in MCHBAR क्रम Haswell (possible SNB+) */
#घोषणा DCLK _MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5e04)

/* 915-945 and GM965 MCH रेजिस्टर controlling DRAM channel access */
#घोषणा DCC			_MMIO(MCHBAR_MIRROR_BASE + 0x200)
#घोषणा DCC_ADDRESSING_MODE_SINGLE_CHANNEL		(0 << 0)
#घोषणा DCC_ADDRESSING_MODE_DUAL_CHANNEL_ASYMMETRIC	(1 << 0)
#घोषणा DCC_ADDRESSING_MODE_DUAL_CHANNEL_INTERLEAVED	(2 << 0)
#घोषणा DCC_ADDRESSING_MODE_MASK			(3 << 0)
#घोषणा DCC_CHANNEL_XOR_DISABLE				(1 << 10)
#घोषणा DCC_CHANNEL_XOR_BIT_17				(1 << 9)
#घोषणा DCC2			_MMIO(MCHBAR_MIRROR_BASE + 0x204)
#घोषणा DCC2_MODIFIED_ENHANCED_DISABLE			(1 << 20)

/* Pineview MCH रेजिस्टर contains DDR3 setting */
#घोषणा CSHRDDR3CTL            _MMIO(MCHBAR_MIRROR_BASE + 0x1a8)
#घोषणा CSHRDDR3CTL_DDR3       (1 << 2)

/* 965 MCH रेजिस्टर controlling DRAM channel configuration */
#घोषणा C0DRB3			_MMIO(MCHBAR_MIRROR_BASE + 0x206)
#घोषणा C1DRB3			_MMIO(MCHBAR_MIRROR_BASE + 0x606)

/* snb MCH रेजिस्टरs क्रम पढ़ोing the DRAM channel configuration */
#घोषणा MAD_DIMM_C0			_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5004)
#घोषणा MAD_DIMM_C1			_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5008)
#घोषणा MAD_DIMM_C2			_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x500C)
#घोषणा   MAD_DIMM_ECC_MASK		(0x3 << 24)
#घोषणा   MAD_DIMM_ECC_OFF		(0x0 << 24)
#घोषणा   MAD_DIMM_ECC_IO_ON_LOGIC_OFF	(0x1 << 24)
#घोषणा   MAD_DIMM_ECC_IO_OFF_LOGIC_ON	(0x2 << 24)
#घोषणा   MAD_DIMM_ECC_ON		(0x3 << 24)
#घोषणा   MAD_DIMM_ENH_INTERLEAVE	(0x1 << 22)
#घोषणा   MAD_DIMM_RANK_INTERLEAVE	(0x1 << 21)
#घोषणा   MAD_DIMM_B_WIDTH_X16		(0x1 << 20) /* X8 chips अगर unset */
#घोषणा   MAD_DIMM_A_WIDTH_X16		(0x1 << 19) /* X8 chips अगर unset */
#घोषणा   MAD_DIMM_B_DUAL_RANK		(0x1 << 18)
#घोषणा   MAD_DIMM_A_DUAL_RANK		(0x1 << 17)
#घोषणा   MAD_DIMM_A_SELECT		(0x1 << 16)
/* DIMM sizes are in multiples of 256mb. */
#घोषणा   MAD_DIMM_B_SIZE_SHIFT		8
#घोषणा   MAD_DIMM_B_SIZE_MASK		(0xff << MAD_DIMM_B_SIZE_SHIFT)
#घोषणा   MAD_DIMM_A_SIZE_SHIFT		0
#घोषणा   MAD_DIMM_A_SIZE_MASK		(0xff << MAD_DIMM_A_SIZE_SHIFT)

/* snb MCH रेजिस्टरs क्रम priority tuning */
#घोषणा MCH_SSKPD			_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5d10)
#घोषणा   MCH_SSKPD_WM0_MASK		0x3f
#घोषणा   MCH_SSKPD_WM0_VAL		0xc

/* Clocking configuration रेजिस्टर */
#घोषणा CLKCFG			_MMIO(MCHBAR_MIRROR_BASE + 0xc00)
#घोषणा CLKCFG_FSB_400					(0 << 0)	/* hrawclk 100 */
#घोषणा CLKCFG_FSB_400_ALT				(5 << 0)	/* hrawclk 100 */
#घोषणा CLKCFG_FSB_533					(1 << 0)	/* hrawclk 133 */
#घोषणा CLKCFG_FSB_667					(3 << 0)	/* hrawclk 166 */
#घोषणा CLKCFG_FSB_800					(2 << 0)	/* hrawclk 200 */
#घोषणा CLKCFG_FSB_1067					(6 << 0)	/* hrawclk 266 */
#घोषणा CLKCFG_FSB_1067_ALT				(0 << 0)	/* hrawclk 266 */
#घोषणा CLKCFG_FSB_1333					(7 << 0)	/* hrawclk 333 */
#घोषणा CLKCFG_FSB_1333_ALT				(4 << 0)	/* hrawclk 333 */
#घोषणा CLKCFG_FSB_1600_ALT				(6 << 0)	/* hrawclk 400 */
#घोषणा CLKCFG_FSB_MASK					(7 << 0)
#घोषणा CLKCFG_MEM_533					(1 << 4)
#घोषणा CLKCFG_MEM_667					(2 << 4)
#घोषणा CLKCFG_MEM_800					(3 << 4)
#घोषणा CLKCFG_MEM_MASK					(7 << 4)

#घोषणा HPLLVCO                 _MMIO(MCHBAR_MIRROR_BASE + 0xc38)
#घोषणा HPLLVCO_MOBILE          _MMIO(MCHBAR_MIRROR_BASE + 0xc0f)

#घोषणा TSC1			_MMIO(0x11001)
#घोषणा   TSE			(1 << 0)
#घोषणा TR1			_MMIO(0x11006)
#घोषणा TSFS			_MMIO(0x11020)
#घोषणा   TSFS_SLOPE_MASK	0x0000ff00
#घोषणा   TSFS_SLOPE_SHIFT	8
#घोषणा   TSFS_INTR_MASK	0x000000ff

#घोषणा CRSTANDVID		_MMIO(0x11100)
#घोषणा PXVFREQ(fstart)		_MMIO(0x11110 + (fstart) * 4)  /* P[0-15]VIDFREQ (0x1114c) (Ironlake) */
#घोषणा   PXVFREQ_PX_MASK	0x7f000000
#घोषणा   PXVFREQ_PX_SHIFT	24
#घोषणा VIDFREQ_BASE		_MMIO(0x11110)
#घोषणा VIDFREQ1		_MMIO(0x11110) /* VIDFREQ1-4 (0x1111c) (Cantiga) */
#घोषणा VIDFREQ2		_MMIO(0x11114)
#घोषणा VIDFREQ3		_MMIO(0x11118)
#घोषणा VIDFREQ4		_MMIO(0x1111c)
#घोषणा   VIDFREQ_P0_MASK	0x1f000000
#घोषणा   VIDFREQ_P0_SHIFT	24
#घोषणा   VIDFREQ_P0_CSCLK_MASK	0x00f00000
#घोषणा   VIDFREQ_P0_CSCLK_SHIFT 20
#घोषणा   VIDFREQ_P0_CRCLK_MASK	0x000f0000
#घोषणा   VIDFREQ_P0_CRCLK_SHIFT 16
#घोषणा   VIDFREQ_P1_MASK	0x00001f00
#घोषणा   VIDFREQ_P1_SHIFT	8
#घोषणा   VIDFREQ_P1_CSCLK_MASK	0x000000f0
#घोषणा   VIDFREQ_P1_CSCLK_SHIFT 4
#घोषणा   VIDFREQ_P1_CRCLK_MASK	0x0000000f
#घोषणा INTTOEXT_BASE_ILK	_MMIO(0x11300)
#घोषणा INTTOEXT_BASE		_MMIO(0x11120) /* INTTOEXT1-8 (0x1113c) */
#घोषणा   INTTOEXT_MAP3_SHIFT	24
#घोषणा   INTTOEXT_MAP3_MASK	(0x1f << INTTOEXT_MAP3_SHIFT)
#घोषणा   INTTOEXT_MAP2_SHIFT	16
#घोषणा   INTTOEXT_MAP2_MASK	(0x1f << INTTOEXT_MAP2_SHIFT)
#घोषणा   INTTOEXT_MAP1_SHIFT	8
#घोषणा   INTTOEXT_MAP1_MASK	(0x1f << INTTOEXT_MAP1_SHIFT)
#घोषणा   INTTOEXT_MAP0_SHIFT	0
#घोषणा   INTTOEXT_MAP0_MASK	(0x1f << INTTOEXT_MAP0_SHIFT)
#घोषणा MEMSWCTL		_MMIO(0x11170) /* Ironlake only */
#घोषणा   MEMCTL_CMD_MASK	0xe000
#घोषणा   MEMCTL_CMD_SHIFT	13
#घोषणा   MEMCTL_CMD_RCLK_OFF	0
#घोषणा   MEMCTL_CMD_RCLK_ON	1
#घोषणा   MEMCTL_CMD_CHFREQ	2
#घोषणा   MEMCTL_CMD_CHVID	3
#घोषणा   MEMCTL_CMD_VMMOFF	4
#घोषणा   MEMCTL_CMD_VMMON	5
#घोषणा   MEMCTL_CMD_STS	(1 << 12) /* ग_लिखो 1 triggers command, clears
					   when command complete */
#घोषणा   MEMCTL_FREQ_MASK	0x0f00 /* jitter, from 0-15 */
#घोषणा   MEMCTL_FREQ_SHIFT	8
#घोषणा   MEMCTL_SFCAVM		(1 << 7)
#घोषणा   MEMCTL_TGT_VID_MASK	0x007f
#घोषणा MEMIHYST		_MMIO(0x1117c)
#घोषणा MEMINTREN		_MMIO(0x11180) /* 16 bits */
#घोषणा   MEMINT_RSEXIT_EN	(1 << 8)
#घोषणा   MEMINT_CX_SUPR_EN	(1 << 7)
#घोषणा   MEMINT_CONT_BUSY_EN	(1 << 6)
#घोषणा   MEMINT_AVG_BUSY_EN	(1 << 5)
#घोषणा   MEMINT_EVAL_CHG_EN	(1 << 4)
#घोषणा   MEMINT_MON_IDLE_EN	(1 << 3)
#घोषणा   MEMINT_UP_EVAL_EN	(1 << 2)
#घोषणा   MEMINT_DOWN_EVAL_EN	(1 << 1)
#घोषणा   MEMINT_SW_CMD_EN	(1 << 0)
#घोषणा MEMINTRSTR		_MMIO(0x11182) /* 16 bits */
#घोषणा   MEM_RSEXIT_MASK	0xc000
#घोषणा   MEM_RSEXIT_SHIFT	14
#घोषणा   MEM_CONT_BUSY_MASK	0x3000
#घोषणा   MEM_CONT_BUSY_SHIFT	12
#घोषणा   MEM_AVG_BUSY_MASK	0x0c00
#घोषणा   MEM_AVG_BUSY_SHIFT	10
#घोषणा   MEM_EVAL_CHG_MASK	0x0300
#घोषणा   MEM_EVAL_BUSY_SHIFT	8
#घोषणा   MEM_MON_IDLE_MASK	0x00c0
#घोषणा   MEM_MON_IDLE_SHIFT	6
#घोषणा   MEM_UP_EVAL_MASK	0x0030
#घोषणा   MEM_UP_EVAL_SHIFT	4
#घोषणा   MEM_DOWN_EVAL_MASK	0x000c
#घोषणा   MEM_DOWN_EVAL_SHIFT	2
#घोषणा   MEM_SW_CMD_MASK	0x0003
#घोषणा   MEM_INT_STEER_GFX	0
#घोषणा   MEM_INT_STEER_CMR	1
#घोषणा   MEM_INT_STEER_SMI	2
#घोषणा   MEM_INT_STEER_SCI	3
#घोषणा MEMINTRSTS		_MMIO(0x11184)
#घोषणा   MEMINT_RSEXIT		(1 << 7)
#घोषणा   MEMINT_CONT_BUSY	(1 << 6)
#घोषणा   MEMINT_AVG_BUSY	(1 << 5)
#घोषणा   MEMINT_EVAL_CHG	(1 << 4)
#घोषणा   MEMINT_MON_IDLE	(1 << 3)
#घोषणा   MEMINT_UP_EVAL	(1 << 2)
#घोषणा   MEMINT_DOWN_EVAL	(1 << 1)
#घोषणा   MEMINT_SW_CMD		(1 << 0)
#घोषणा MEMMODECTL		_MMIO(0x11190)
#घोषणा   MEMMODE_BOOST_EN	(1 << 31)
#घोषणा   MEMMODE_BOOST_FREQ_MASK 0x0f000000 /* jitter क्रम boost, 0-15 */
#घोषणा   MEMMODE_BOOST_FREQ_SHIFT 24
#घोषणा   MEMMODE_IDLE_MODE_MASK 0x00030000
#घोषणा   MEMMODE_IDLE_MODE_SHIFT 16
#घोषणा   MEMMODE_IDLE_MODE_EVAL 0
#घोषणा   MEMMODE_IDLE_MODE_CONT 1
#घोषणा   MEMMODE_HWIDLE_EN	(1 << 15)
#घोषणा   MEMMODE_SWMODE_EN	(1 << 14)
#घोषणा   MEMMODE_RCLK_GATE	(1 << 13)
#घोषणा   MEMMODE_HW_UPDATE	(1 << 12)
#घोषणा   MEMMODE_FSTART_MASK	0x00000f00 /* starting jitter, 0-15 */
#घोषणा   MEMMODE_FSTART_SHIFT	8
#घोषणा   MEMMODE_FMAX_MASK	0x000000f0 /* max jitter, 0-15 */
#घोषणा   MEMMODE_FMAX_SHIFT	4
#घोषणा   MEMMODE_FMIN_MASK	0x0000000f /* min jitter, 0-15 */
#घोषणा RCBMAXAVG		_MMIO(0x1119c)
#घोषणा MEMSWCTL2		_MMIO(0x1119e) /* Cantiga only */
#घोषणा   SWMEMCMD_RENDER_OFF	(0 << 13)
#घोषणा   SWMEMCMD_RENDER_ON	(1 << 13)
#घोषणा   SWMEMCMD_SWFREQ	(2 << 13)
#घोषणा   SWMEMCMD_TARVID	(3 << 13)
#घोषणा   SWMEMCMD_VRM_OFF	(4 << 13)
#घोषणा   SWMEMCMD_VRM_ON	(5 << 13)
#घोषणा   CMDSTS		(1 << 12)
#घोषणा   SFCAVM		(1 << 11)
#घोषणा   SWFREQ_MASK		0x0380 /* P0-7 */
#घोषणा   SWFREQ_SHIFT		7
#घोषणा   TARVID_MASK		0x001f
#घोषणा MEMSTAT_CTG		_MMIO(0x111a0)
#घोषणा RCBMINAVG		_MMIO(0x111a0)
#घोषणा RCUPEI			_MMIO(0x111b0)
#घोषणा RCDNEI			_MMIO(0x111b4)
#घोषणा RSTDBYCTL		_MMIO(0x111b8)
#घोषणा   RS1EN			(1 << 31)
#घोषणा   RS2EN			(1 << 30)
#घोषणा   RS3EN			(1 << 29)
#घोषणा   D3RS3EN		(1 << 28) /* Display D3 imlies RS3 */
#घोषणा   SWPROMORSX		(1 << 27) /* RSx promotion समयrs ignored */
#घोषणा   RCWAKERW		(1 << 26) /* Resetwarn from PCH causes wakeup */
#घोषणा   DPRSLPVREN		(1 << 25) /* Fast voltage ramp enable */
#घोषणा   GFXTGHYST		(1 << 24) /* Hysteresis to allow trunk gating */
#घोषणा   RCX_SW_EXIT		(1 << 23) /* Leave RSx and prevent re-entry */
#घोषणा   RSX_STATUS_MASK	(7 << 20)
#घोषणा   RSX_STATUS_ON		(0 << 20)
#घोषणा   RSX_STATUS_RC1	(1 << 20)
#घोषणा   RSX_STATUS_RC1E	(2 << 20)
#घोषणा   RSX_STATUS_RS1	(3 << 20)
#घोषणा   RSX_STATUS_RS2	(4 << 20) /* aka rc6 */
#घोषणा   RSX_STATUS_RSVD	(5 << 20) /* deep rc6 unsupported on ilk */
#घोषणा   RSX_STATUS_RS3	(6 << 20) /* rs3 unsupported on ilk */
#घोषणा   RSX_STATUS_RSVD2	(7 << 20)
#घोषणा   UWRCRSXE		(1 << 19) /* wake counter limit prevents rsx */
#घोषणा   RSCRP			(1 << 18) /* rs requests control on rs1/2 reqs */
#घोषणा   JRSC			(1 << 17) /* rsx coupled to cpu c-state */
#घोषणा   RS2INC0		(1 << 16) /* allow rs2 in cpu c0 */
#घोषणा   RS1CONTSAV_MASK	(3 << 14)
#घोषणा   RS1CONTSAV_NO_RS1	(0 << 14) /* rs1 करोesn't save/restore context */
#घोषणा   RS1CONTSAV_RSVD	(1 << 14)
#घोषणा   RS1CONTSAV_SAVE_RS1	(2 << 14) /* rs1 saves context */
#घोषणा   RS1CONTSAV_FULL_RS1	(3 << 14) /* rs1 saves and restores context */
#घोषणा   NORMSLEXLAT_MASK	(3 << 12)
#घोषणा   SLOW_RS123		(0 << 12)
#घोषणा   SLOW_RS23		(1 << 12)
#घोषणा   SLOW_RS3		(2 << 12)
#घोषणा   NORMAL_RS123		(3 << 12)
#घोषणा   RCMODE_TIMEOUT	(1 << 11) /* 0 is eval पूर्णांकerval method */
#घोषणा   IMPROMOEN		(1 << 10) /* promo is immediate or delayed until next idle पूर्णांकerval (only क्रम समयout method above) */
#घोषणा   RCENTSYNC		(1 << 9) /* rs coupled to cpu c-state (3/6/7) */
#घोषणा   STATELOCK		(1 << 7) /* locked to rs_cstate अगर 0 */
#घोषणा   RS_CSTATE_MASK	(3 << 4)
#घोषणा   RS_CSTATE_C367_RS1	(0 << 4)
#घोषणा   RS_CSTATE_C36_RS1_C7_RS2 (1 << 4)
#घोषणा   RS_CSTATE_RSVD	(2 << 4)
#घोषणा   RS_CSTATE_C367_RS2	(3 << 4)
#घोषणा   REDSAVES		(1 << 3) /* no context save अगर was idle during rs0 */
#घोषणा   REDRESTORES		(1 << 2) /* no restore अगर was idle during rs0 */
#घोषणा VIDCTL			_MMIO(0x111c0)
#घोषणा VIDSTS			_MMIO(0x111c8)
#घोषणा VIDSTART		_MMIO(0x111cc) /* 8 bits */
#घोषणा MEMSTAT_ILK		_MMIO(0x111f8)
#घोषणा   MEMSTAT_VID_MASK	0x7f00
#घोषणा   MEMSTAT_VID_SHIFT	8
#घोषणा   MEMSTAT_PSTATE_MASK	0x00f8
#घोषणा   MEMSTAT_PSTATE_SHIFT  3
#घोषणा   MEMSTAT_MON_ACTV	(1 << 2)
#घोषणा   MEMSTAT_SRC_CTL_MASK	0x0003
#घोषणा   MEMSTAT_SRC_CTL_CORE	0
#घोषणा   MEMSTAT_SRC_CTL_TRB	1
#घोषणा   MEMSTAT_SRC_CTL_THM	2
#घोषणा   MEMSTAT_SRC_CTL_STDBY 3
#घोषणा RCPREVBSYTUPAVG		_MMIO(0x113b8)
#घोषणा RCPREVBSYTDNAVG		_MMIO(0x113bc)
#घोषणा PMMISC			_MMIO(0x11214)
#घोषणा   MCPPCE_EN		(1 << 0) /* enable PM_MSG from PCH->MPC */
#घोषणा SDEW			_MMIO(0x1124c)
#घोषणा CSIEW0			_MMIO(0x11250)
#घोषणा CSIEW1			_MMIO(0x11254)
#घोषणा CSIEW2			_MMIO(0x11258)
#घोषणा PEW(i)			_MMIO(0x1125c + (i) * 4) /* 5 रेजिस्टरs */
#घोषणा DEW(i)			_MMIO(0x11270 + (i) * 4) /* 3 रेजिस्टरs */
#घोषणा MCHAFE			_MMIO(0x112c0)
#घोषणा CSIEC			_MMIO(0x112e0)
#घोषणा DMIEC			_MMIO(0x112e4)
#घोषणा DDREC			_MMIO(0x112e8)
#घोषणा PEG0EC			_MMIO(0x112ec)
#घोषणा PEG1EC			_MMIO(0x112f0)
#घोषणा GFXEC			_MMIO(0x112f4)
#घोषणा RPPREVBSYTUPAVG		_MMIO(0x113b8)
#घोषणा RPPREVBSYTDNAVG		_MMIO(0x113bc)
#घोषणा ECR			_MMIO(0x11600)
#घोषणा   ECR_GPFE		(1 << 31)
#घोषणा   ECR_IMONE		(1 << 30)
#घोषणा   ECR_CAP_MASK		0x0000001f /* Event range, 0-31 */
#घोषणा OGW0			_MMIO(0x11608)
#घोषणा OGW1			_MMIO(0x1160c)
#घोषणा EG0			_MMIO(0x11610)
#घोषणा EG1			_MMIO(0x11614)
#घोषणा EG2			_MMIO(0x11618)
#घोषणा EG3			_MMIO(0x1161c)
#घोषणा EG4			_MMIO(0x11620)
#घोषणा EG5			_MMIO(0x11624)
#घोषणा EG6			_MMIO(0x11628)
#घोषणा EG7			_MMIO(0x1162c)
#घोषणा PXW(i)			_MMIO(0x11664 + (i) * 4) /* 4 रेजिस्टरs */
#घोषणा PXWL(i)			_MMIO(0x11680 + (i) * 8) /* 8 रेजिस्टरs */
#घोषणा LCFUSE02		_MMIO(0x116c0)
#घोषणा   LCFUSE_HIV_MASK	0x000000ff
#घोषणा CSIPLL0			_MMIO(0x12c10)
#घोषणा DDRMPLL1		_MMIO(0X12c20)
#घोषणा PEG_BAND_GAP_DATA	_MMIO(0x14d68)

#घोषणा GEN6_GT_THREAD_STATUS_REG _MMIO(0x13805c)
#घोषणा GEN6_GT_THREAD_STATUS_CORE_MASK 0x7

#घोषणा GEN6_GT_PERF_STATUS	_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5948)
#घोषणा BXT_GT_PERF_STATUS      _MMIO(MCHBAR_MIRROR_BASE_SNB + 0x7070)
#घोषणा GEN6_RP_STATE_LIMITS	_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5994)
#घोषणा GEN6_RP_STATE_CAP	_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5998)
#घोषणा BXT_RP_STATE_CAP        _MMIO(0x138170)
#घोषणा GEN9_RP_STATE_LIMITS	_MMIO(0x138148)

/*
 * Logical Context regs
 */
#घोषणा CCID(base)			_MMIO((base) + 0x180)
#घोषणा   CCID_EN			BIT(0)
#घोषणा   CCID_EXTENDED_STATE_RESTORE	BIT(2)
#घोषणा   CCID_EXTENDED_STATE_SAVE	BIT(3)
/*
 * Notes on SNB/IVB/VLV context size:
 * - Power context is saved अन्यथाwhere (LLC or stolen)
 * - Ring/execlist context is saved on SNB, not on IVB
 * - Extended context size alपढ़ोy includes render context size
 * - We always need to follow the extended context size.
 *   SNB BSpec has comments indicating that we should use the
 *   render context size instead अगर execlists are disabled, but
 *   based on empirical testing that's just nonsense.
 * - Pipelined/VF state is saved on SNB/IVB respectively
 * - GT1 size just indicates how much of render context
 *   करोesn't need saving on GT1
 */
#घोषणा CXT_SIZE		_MMIO(0x21a0)
#घोषणा GEN6_CXT_POWER_SIZE(cxt_reg)	(((cxt_reg) >> 24) & 0x3f)
#घोषणा GEN6_CXT_RING_SIZE(cxt_reg)	(((cxt_reg) >> 18) & 0x3f)
#घोषणा GEN6_CXT_RENDER_SIZE(cxt_reg)	(((cxt_reg) >> 12) & 0x3f)
#घोषणा GEN6_CXT_EXTENDED_SIZE(cxt_reg)	(((cxt_reg) >> 6) & 0x3f)
#घोषणा GEN6_CXT_PIPELINE_SIZE(cxt_reg)	(((cxt_reg) >> 0) & 0x3f)
#घोषणा GEN6_CXT_TOTAL_SIZE(cxt_reg)	(GEN6_CXT_RING_SIZE(cxt_reg) + \
					GEN6_CXT_EXTENDED_SIZE(cxt_reg) + \
					GEN6_CXT_PIPELINE_SIZE(cxt_reg))
#घोषणा GEN7_CXT_SIZE		_MMIO(0x21a8)
#घोषणा GEN7_CXT_POWER_SIZE(ctx_reg)	(((ctx_reg) >> 25) & 0x7f)
#घोषणा GEN7_CXT_RING_SIZE(ctx_reg)	(((ctx_reg) >> 22) & 0x7)
#घोषणा GEN7_CXT_RENDER_SIZE(ctx_reg)	(((ctx_reg) >> 16) & 0x3f)
#घोषणा GEN7_CXT_EXTENDED_SIZE(ctx_reg)	(((ctx_reg) >> 9) & 0x7f)
#घोषणा GEN7_CXT_GT1_SIZE(ctx_reg)	(((ctx_reg) >> 6) & 0x7)
#घोषणा GEN7_CXT_VFSTATE_SIZE(ctx_reg)	(((ctx_reg) >> 0) & 0x3f)
#घोषणा GEN7_CXT_TOTAL_SIZE(ctx_reg)	(GEN7_CXT_EXTENDED_SIZE(ctx_reg) + \
					 GEN7_CXT_VFSTATE_SIZE(ctx_reg))

क्रमागत अणु
	INTEL_ADVANCED_CONTEXT = 0,
	INTEL_LEGACY_32B_CONTEXT,
	INTEL_ADVANCED_AD_CONTEXT,
	INTEL_LEGACY_64B_CONTEXT
पूर्ण;

क्रमागत अणु
	FAULT_AND_HANG = 0,
	FAULT_AND_HALT, /* Debug only */
	FAULT_AND_STREAM,
	FAULT_AND_CONTINUE /* Unsupported */
पूर्ण;

#घोषणा GEN8_CTX_VALID (1 << 0)
#घोषणा GEN8_CTX_FORCE_PD_RESTORE (1 << 1)
#घोषणा GEN8_CTX_FORCE_RESTORE (1 << 2)
#घोषणा GEN8_CTX_L3LLC_COHERENT (1 << 5)
#घोषणा GEN8_CTX_PRIVILEGE (1 << 8)
#घोषणा GEN8_CTX_ADDRESSING_MODE_SHIFT 3

#घोषणा GEN8_CTX_ID_SHIFT 32
#घोषणा GEN8_CTX_ID_WIDTH 21
#घोषणा GEN11_SW_CTX_ID_SHIFT 37
#घोषणा GEN11_SW_CTX_ID_WIDTH 11
#घोषणा GEN11_ENGINE_CLASS_SHIFT 61
#घोषणा GEN11_ENGINE_CLASS_WIDTH 3
#घोषणा GEN11_ENGINE_INSTANCE_SHIFT 48
#घोषणा GEN11_ENGINE_INSTANCE_WIDTH 6

#घोषणा CHV_CLK_CTL1			_MMIO(0x101100)
#घोषणा VLV_CLK_CTL2			_MMIO(0x101104)
#घोषणा   CLK_CTL2_CZCOUNT_30NS_SHIFT	28

/*
 * Overlay regs
 */

#घोषणा OVADD			_MMIO(0x30000)
#घोषणा DOVSTA			_MMIO(0x30008)
#घोषणा OC_BUF			(0x3 << 20)
#घोषणा OGAMC5			_MMIO(0x30010)
#घोषणा OGAMC4			_MMIO(0x30014)
#घोषणा OGAMC3			_MMIO(0x30018)
#घोषणा OGAMC2			_MMIO(0x3001c)
#घोषणा OGAMC1			_MMIO(0x30020)
#घोषणा OGAMC0			_MMIO(0x30024)

/*
 * GEN9 घड़ी gating regs
 */
#घोषणा GEN9_CLKGATE_DIS_0		_MMIO(0x46530)
#घोषणा   DARBF_GATING_DIS		(1 << 27)
#घोषणा   PWM2_GATING_DIS		(1 << 14)
#घोषणा   PWM1_GATING_DIS		(1 << 13)

#घोषणा GEN9_CLKGATE_DIS_3		_MMIO(0x46538)
#घोषणा   TGL_VRH_GATING_DIS		REG_BIT(31)
#घोषणा   DPT_GATING_DIS		REG_BIT(22)

#घोषणा GEN9_CLKGATE_DIS_4		_MMIO(0x4653C)
#घोषणा   BXT_GMBUS_GATING_DIS		(1 << 14)

#घोषणा _CLKGATE_DIS_PSL_A		0x46520
#घोषणा _CLKGATE_DIS_PSL_B		0x46524
#घोषणा _CLKGATE_DIS_PSL_C		0x46528
#घोषणा   DUPS1_GATING_DIS		(1 << 15)
#घोषणा   DUPS2_GATING_DIS		(1 << 19)
#घोषणा   DUPS3_GATING_DIS		(1 << 23)
#घोषणा   DPF_GATING_DIS		(1 << 10)
#घोषणा   DPF_RAM_GATING_DIS		(1 << 9)
#घोषणा   DPFR_GATING_DIS		(1 << 8)

#घोषणा CLKGATE_DIS_PSL(pipe) \
	_MMIO_PIPE(pipe, _CLKGATE_DIS_PSL_A, _CLKGATE_DIS_PSL_B)

/*
 * GEN10 घड़ी gating regs
 */
#घोषणा SLICE_UNIT_LEVEL_CLKGATE	_MMIO(0x94d4)
#घोषणा  SARBUNIT_CLKGATE_DIS		(1 << 5)
#घोषणा  RCCUNIT_CLKGATE_DIS		(1 << 7)
#घोषणा  MSCUNIT_CLKGATE_DIS		(1 << 10)
#घोषणा  L3_CLKGATE_DIS			REG_BIT(16)
#घोषणा  L3_CR2X_CLKGATE_DIS		REG_BIT(17)

#घोषणा SUBSLICE_UNIT_LEVEL_CLKGATE	_MMIO(0x9524)
#घोषणा  GWUNIT_CLKGATE_DIS		(1 << 16)

#घोषणा SUBSLICE_UNIT_LEVEL_CLKGATE2	_MMIO(0x9528)
#घोषणा  CPSSUNIT_CLKGATE_DIS		REG_BIT(9)

#घोषणा UNSLICE_UNIT_LEVEL_CLKGATE	_MMIO(0x9434)
#घोषणा   VFUNIT_CLKGATE_DIS		REG_BIT(20)
#घोषणा   HSUNIT_CLKGATE_DIS		REG_BIT(8)
#घोषणा   VSUNIT_CLKGATE_DIS		REG_BIT(3)

#घोषणा UNSLICE_UNIT_LEVEL_CLKGATE2	_MMIO(0x94e4)
#घोषणा   VSUNIT_CLKGATE_DIS_TGL	REG_BIT(19)
#घोषणा   PSDUNIT_CLKGATE_DIS		REG_BIT(5)

#घोषणा INF_UNIT_LEVEL_CLKGATE		_MMIO(0x9560)
#घोषणा   CGPSF_CLKGATE_DIS		(1 << 3)

/*
 * Display engine regs
 */

/* Pipe A CRC regs */
#घोषणा _PIPE_CRC_CTL_A			0x60050
#घोषणा   PIPE_CRC_ENABLE		(1 << 31)
/* skl+ source selection */
#घोषणा   PIPE_CRC_SOURCE_PLANE_1_SKL	(0 << 28)
#घोषणा   PIPE_CRC_SOURCE_PLANE_2_SKL	(2 << 28)
#घोषणा   PIPE_CRC_SOURCE_DMUX_SKL	(4 << 28)
#घोषणा   PIPE_CRC_SOURCE_PLANE_3_SKL	(6 << 28)
#घोषणा   PIPE_CRC_SOURCE_PLANE_4_SKL	(7 << 28)
#घोषणा   PIPE_CRC_SOURCE_PLANE_5_SKL	(5 << 28)
#घोषणा   PIPE_CRC_SOURCE_PLANE_6_SKL	(3 << 28)
#घोषणा   PIPE_CRC_SOURCE_PLANE_7_SKL	(1 << 28)
/* ivb+ source selection */
#घोषणा   PIPE_CRC_SOURCE_PRIMARY_IVB	(0 << 29)
#घोषणा   PIPE_CRC_SOURCE_SPRITE_IVB	(1 << 29)
#घोषणा   PIPE_CRC_SOURCE_PF_IVB	(2 << 29)
/* ilk+ source selection */
#घोषणा   PIPE_CRC_SOURCE_PRIMARY_ILK	(0 << 28)
#घोषणा   PIPE_CRC_SOURCE_SPRITE_ILK	(1 << 28)
#घोषणा   PIPE_CRC_SOURCE_PIPE_ILK	(2 << 28)
/* embedded DP port on the north display block, reserved on ivb */
#घोषणा   PIPE_CRC_SOURCE_PORT_A_ILK	(4 << 28)
#घोषणा   PIPE_CRC_SOURCE_FDI_ILK	(5 << 28) /* reserved on ivb */
/* vlv source selection */
#घोषणा   PIPE_CRC_SOURCE_PIPE_VLV	(0 << 27)
#घोषणा   PIPE_CRC_SOURCE_HDMIB_VLV	(1 << 27)
#घोषणा   PIPE_CRC_SOURCE_HDMIC_VLV	(2 << 27)
/* with DP port the pipe source is invalid */
#घोषणा   PIPE_CRC_SOURCE_DP_D_VLV	(3 << 27)
#घोषणा   PIPE_CRC_SOURCE_DP_B_VLV	(6 << 27)
#घोषणा   PIPE_CRC_SOURCE_DP_C_VLV	(7 << 27)
/* gen3+ source selection */
#घोषणा   PIPE_CRC_SOURCE_PIPE_I9XX	(0 << 28)
#घोषणा   PIPE_CRC_SOURCE_SDVOB_I9XX	(1 << 28)
#घोषणा   PIPE_CRC_SOURCE_SDVOC_I9XX	(2 << 28)
/* with DP/TV port the pipe source is invalid */
#घोषणा   PIPE_CRC_SOURCE_DP_D_G4X	(3 << 28)
#घोषणा   PIPE_CRC_SOURCE_TV_PRE	(4 << 28)
#घोषणा   PIPE_CRC_SOURCE_TV_POST	(5 << 28)
#घोषणा   PIPE_CRC_SOURCE_DP_B_G4X	(6 << 28)
#घोषणा   PIPE_CRC_SOURCE_DP_C_G4X	(7 << 28)
/* gen2 करोesn't have source selection bits */
#घोषणा   PIPE_CRC_INCLUDE_BORDER_I8XX	(1 << 30)

#घोषणा _PIPE_CRC_RES_1_A_IVB		0x60064
#घोषणा _PIPE_CRC_RES_2_A_IVB		0x60068
#घोषणा _PIPE_CRC_RES_3_A_IVB		0x6006c
#घोषणा _PIPE_CRC_RES_4_A_IVB		0x60070
#घोषणा _PIPE_CRC_RES_5_A_IVB		0x60074

#घोषणा _PIPE_CRC_RES_RED_A		0x60060
#घोषणा _PIPE_CRC_RES_GREEN_A		0x60064
#घोषणा _PIPE_CRC_RES_BLUE_A		0x60068
#घोषणा _PIPE_CRC_RES_RES1_A_I915	0x6006c
#घोषणा _PIPE_CRC_RES_RES2_A_G4X	0x60080

/* Pipe B CRC regs */
#घोषणा _PIPE_CRC_RES_1_B_IVB		0x61064
#घोषणा _PIPE_CRC_RES_2_B_IVB		0x61068
#घोषणा _PIPE_CRC_RES_3_B_IVB		0x6106c
#घोषणा _PIPE_CRC_RES_4_B_IVB		0x61070
#घोषणा _PIPE_CRC_RES_5_B_IVB		0x61074

#घोषणा PIPE_CRC_CTL(pipe)		_MMIO_TRANS2(pipe, _PIPE_CRC_CTL_A)
#घोषणा PIPE_CRC_RES_1_IVB(pipe)	_MMIO_TRANS2(pipe, _PIPE_CRC_RES_1_A_IVB)
#घोषणा PIPE_CRC_RES_2_IVB(pipe)	_MMIO_TRANS2(pipe, _PIPE_CRC_RES_2_A_IVB)
#घोषणा PIPE_CRC_RES_3_IVB(pipe)	_MMIO_TRANS2(pipe, _PIPE_CRC_RES_3_A_IVB)
#घोषणा PIPE_CRC_RES_4_IVB(pipe)	_MMIO_TRANS2(pipe, _PIPE_CRC_RES_4_A_IVB)
#घोषणा PIPE_CRC_RES_5_IVB(pipe)	_MMIO_TRANS2(pipe, _PIPE_CRC_RES_5_A_IVB)

#घोषणा PIPE_CRC_RES_RED(pipe)		_MMIO_TRANS2(pipe, _PIPE_CRC_RES_RED_A)
#घोषणा PIPE_CRC_RES_GREEN(pipe)	_MMIO_TRANS2(pipe, _PIPE_CRC_RES_GREEN_A)
#घोषणा PIPE_CRC_RES_BLUE(pipe)		_MMIO_TRANS2(pipe, _PIPE_CRC_RES_BLUE_A)
#घोषणा PIPE_CRC_RES_RES1_I915(pipe)	_MMIO_TRANS2(pipe, _PIPE_CRC_RES_RES1_A_I915)
#घोषणा PIPE_CRC_RES_RES2_G4X(pipe)	_MMIO_TRANS2(pipe, _PIPE_CRC_RES_RES2_A_G4X)

/* Pipe A timing regs */
#घोषणा _HTOTAL_A	0x60000
#घोषणा _HBLANK_A	0x60004
#घोषणा _HSYNC_A	0x60008
#घोषणा _VTOTAL_A	0x6000c
#घोषणा _VBLANK_A	0x60010
#घोषणा _VSYNC_A	0x60014
#घोषणा _EXITLINE_A	0x60018
#घोषणा _PIPEASRC	0x6001c
#घोषणा _BCLRPAT_A	0x60020
#घोषणा _VSYNCSHIFT_A	0x60028
#घोषणा _PIPE_MULT_A	0x6002c

/* Pipe B timing regs */
#घोषणा _HTOTAL_B	0x61000
#घोषणा _HBLANK_B	0x61004
#घोषणा _HSYNC_B	0x61008
#घोषणा _VTOTAL_B	0x6100c
#घोषणा _VBLANK_B	0x61010
#घोषणा _VSYNC_B	0x61014
#घोषणा _PIPEBSRC	0x6101c
#घोषणा _BCLRPAT_B	0x61020
#घोषणा _VSYNCSHIFT_B	0x61028
#घोषणा _PIPE_MULT_B	0x6102c

/* DSI 0 timing regs */
#घोषणा _HTOTAL_DSI0		0x6b000
#घोषणा _HSYNC_DSI0		0x6b008
#घोषणा _VTOTAL_DSI0		0x6b00c
#घोषणा _VSYNC_DSI0		0x6b014
#घोषणा _VSYNCSHIFT_DSI0	0x6b028

/* DSI 1 timing regs */
#घोषणा _HTOTAL_DSI1		0x6b800
#घोषणा _HSYNC_DSI1		0x6b808
#घोषणा _VTOTAL_DSI1		0x6b80c
#घोषणा _VSYNC_DSI1		0x6b814
#घोषणा _VSYNCSHIFT_DSI1	0x6b828

#घोषणा TRANSCODER_A_OFFSET 0x60000
#घोषणा TRANSCODER_B_OFFSET 0x61000
#घोषणा TRANSCODER_C_OFFSET 0x62000
#घोषणा CHV_TRANSCODER_C_OFFSET 0x63000
#घोषणा TRANSCODER_D_OFFSET 0x63000
#घोषणा TRANSCODER_EDP_OFFSET 0x6f000
#घोषणा TRANSCODER_DSI0_OFFSET	0x6b000
#घोषणा TRANSCODER_DSI1_OFFSET	0x6b800

#घोषणा HTOTAL(trans)		_MMIO_TRANS2(trans, _HTOTAL_A)
#घोषणा HBLANK(trans)		_MMIO_TRANS2(trans, _HBLANK_A)
#घोषणा HSYNC(trans)		_MMIO_TRANS2(trans, _HSYNC_A)
#घोषणा VTOTAL(trans)		_MMIO_TRANS2(trans, _VTOTAL_A)
#घोषणा VBLANK(trans)		_MMIO_TRANS2(trans, _VBLANK_A)
#घोषणा VSYNC(trans)		_MMIO_TRANS2(trans, _VSYNC_A)
#घोषणा BCLRPAT(trans)		_MMIO_TRANS2(trans, _BCLRPAT_A)
#घोषणा VSYNCSHIFT(trans)	_MMIO_TRANS2(trans, _VSYNCSHIFT_A)
#घोषणा PIPESRC(trans)		_MMIO_TRANS2(trans, _PIPEASRC)
#घोषणा PIPE_MULT(trans)	_MMIO_TRANS2(trans, _PIPE_MULT_A)

#घोषणा EXITLINE(trans)		_MMIO_TRANS2(trans, _EXITLINE_A)
#घोषणा   EXITLINE_ENABLE	REG_BIT(31)
#घोषणा   EXITLINE_MASK		REG_GENMASK(12, 0)
#घोषणा   EXITLINE_SHIFT	0

/* VRR रेजिस्टरs */
#घोषणा _TRANS_VRR_CTL_A		0x60420
#घोषणा _TRANS_VRR_CTL_B		0x61420
#घोषणा _TRANS_VRR_CTL_C		0x62420
#घोषणा _TRANS_VRR_CTL_D		0x63420
#घोषणा TRANS_VRR_CTL(trans)			_MMIO_TRANS2(trans, _TRANS_VRR_CTL_A)
#घोषणा   VRR_CTL_VRR_ENABLE			REG_BIT(31)
#घोषणा   VRR_CTL_IGN_MAX_SHIFT			REG_BIT(30)
#घोषणा   VRR_CTL_FLIP_LINE_EN			REG_BIT(29)
#घोषणा   VRR_CTL_PIPELINE_FULL_MASK		REG_GENMASK(10, 3)
#घोषणा   VRR_CTL_PIPELINE_FULL(x)		REG_FIELD_PREP(VRR_CTL_PIPELINE_FULL_MASK, (x))
#घोषणा   VRR_CTL_PIPELINE_FULL_OVERRIDE	REG_BIT(0)

#घोषणा _TRANS_VRR_VMAX_A		0x60424
#घोषणा _TRANS_VRR_VMAX_B		0x61424
#घोषणा _TRANS_VRR_VMAX_C		0x62424
#घोषणा _TRANS_VRR_VMAX_D		0x63424
#घोषणा TRANS_VRR_VMAX(trans)		_MMIO_TRANS2(trans, _TRANS_VRR_VMAX_A)
#घोषणा   VRR_VMAX_MASK			REG_GENMASK(19, 0)

#घोषणा _TRANS_VRR_VMIN_A		0x60434
#घोषणा _TRANS_VRR_VMIN_B		0x61434
#घोषणा _TRANS_VRR_VMIN_C		0x62434
#घोषणा _TRANS_VRR_VMIN_D		0x63434
#घोषणा TRANS_VRR_VMIN(trans)		_MMIO_TRANS2(trans, _TRANS_VRR_VMIN_A)
#घोषणा   VRR_VMIN_MASK			REG_GENMASK(15, 0)

#घोषणा _TRANS_VRR_VMAXSHIFT_A		0x60428
#घोषणा _TRANS_VRR_VMAXSHIFT_B		0x61428
#घोषणा _TRANS_VRR_VMAXSHIFT_C		0x62428
#घोषणा _TRANS_VRR_VMAXSHIFT_D		0x63428
#घोषणा TRANS_VRR_VMAXSHIFT(trans)	_MMIO_TRANS2(trans, \
					_TRANS_VRR_VMAXSHIFT_A)
#घोषणा   VRR_VMAXSHIFT_DEC_MASK	REG_GENMASK(29, 16)
#घोषणा   VRR_VMAXSHIFT_DEC		REG_BIT(16)
#घोषणा   VRR_VMAXSHIFT_INC_MASK	REG_GENMASK(12, 0)

#घोषणा _TRANS_VRR_STATUS_A		0x6042C
#घोषणा _TRANS_VRR_STATUS_B		0x6142C
#घोषणा _TRANS_VRR_STATUS_C		0x6242C
#घोषणा _TRANS_VRR_STATUS_D		0x6342C
#घोषणा TRANS_VRR_STATUS(trans)		_MMIO_TRANS2(trans, _TRANS_VRR_STATUS_A)
#घोषणा   VRR_STATUS_VMAX_REACHED	REG_BIT(31)
#घोषणा   VRR_STATUS_NOFLIP_TILL_BNDR	REG_BIT(30)
#घोषणा   VRR_STATUS_FLIP_BEF_BNDR	REG_BIT(29)
#घोषणा   VRR_STATUS_NO_FLIP_FRAME	REG_BIT(28)
#घोषणा   VRR_STATUS_VRR_EN_LIVE	REG_BIT(27)
#घोषणा   VRR_STATUS_FLIPS_SERVICED	REG_BIT(26)
#घोषणा   VRR_STATUS_VBLANK_MASK	REG_GENMASK(22, 20)
#घोषणा   STATUS_FSM_IDLE		REG_FIELD_PREP(VRR_STATUS_VBLANK_MASK, 0)
#घोषणा   STATUS_FSM_WAIT_TILL_FDB	REG_FIELD_PREP(VRR_STATUS_VBLANK_MASK, 1)
#घोषणा   STATUS_FSM_WAIT_TILL_FS	REG_FIELD_PREP(VRR_STATUS_VBLANK_MASK, 2)
#घोषणा   STATUS_FSM_WAIT_TILL_FLIP	REG_FIELD_PREP(VRR_STATUS_VBLANK_MASK, 3)
#घोषणा   STATUS_FSM_PIPELINE_FILL	REG_FIELD_PREP(VRR_STATUS_VBLANK_MASK, 4)
#घोषणा   STATUS_FSM_ACTIVE		REG_FIELD_PREP(VRR_STATUS_VBLANK_MASK, 5)
#घोषणा   STATUS_FSM_LEGACY_VBLANK	REG_FIELD_PREP(VRR_STATUS_VBLANK_MASK, 6)

#घोषणा _TRANS_VRR_VTOTAL_PREV_A	0x60480
#घोषणा _TRANS_VRR_VTOTAL_PREV_B	0x61480
#घोषणा _TRANS_VRR_VTOTAL_PREV_C	0x62480
#घोषणा _TRANS_VRR_VTOTAL_PREV_D	0x63480
#घोषणा TRANS_VRR_VTOTAL_PREV(trans)	_MMIO_TRANS2(trans, \
					_TRANS_VRR_VTOTAL_PREV_A)
#घोषणा   VRR_VTOTAL_FLIP_BEFR_BNDR	REG_BIT(31)
#घोषणा   VRR_VTOTAL_FLIP_AFTER_BNDR	REG_BIT(30)
#घोषणा   VRR_VTOTAL_FLIP_AFTER_DBLBUF	REG_BIT(29)
#घोषणा   VRR_VTOTAL_PREV_FRAME_MASK	REG_GENMASK(19, 0)

#घोषणा _TRANS_VRR_FLIPLINE_A		0x60438
#घोषणा _TRANS_VRR_FLIPLINE_B		0x61438
#घोषणा _TRANS_VRR_FLIPLINE_C		0x62438
#घोषणा _TRANS_VRR_FLIPLINE_D		0x63438
#घोषणा TRANS_VRR_FLIPLINE(trans)	_MMIO_TRANS2(trans, \
					_TRANS_VRR_FLIPLINE_A)
#घोषणा   VRR_FLIPLINE_MASK		REG_GENMASK(19, 0)

#घोषणा _TRANS_VRR_STATUS2_A		0x6043C
#घोषणा _TRANS_VRR_STATUS2_B		0x6143C
#घोषणा _TRANS_VRR_STATUS2_C		0x6243C
#घोषणा _TRANS_VRR_STATUS2_D		0x6343C
#घोषणा TRANS_VRR_STATUS2(trans)	_MMIO_TRANS2(trans, _TRANS_VRR_STATUS2_A)
#घोषणा   VRR_STATUS2_VERT_LN_CNT_MASK	REG_GENMASK(19, 0)

#घोषणा _TRANS_PUSH_A			0x60A70
#घोषणा _TRANS_PUSH_B			0x61A70
#घोषणा _TRANS_PUSH_C			0x62A70
#घोषणा _TRANS_PUSH_D			0x63A70
#घोषणा TRANS_PUSH(trans)		_MMIO_TRANS2(trans, _TRANS_PUSH_A)
#घोषणा   TRANS_PUSH_EN			REG_BIT(31)
#घोषणा   TRANS_PUSH_SEND		REG_BIT(30)

/*
 * HSW+ eDP PSR रेजिस्टरs
 *
 * HSW PSR रेजिस्टरs are relative to DDIA(_DDI_BUF_CTL_A + 0x800) with just one
 * instance of it
 */
#घोषणा _HSW_EDP_PSR_BASE			0x64800
#घोषणा _SRD_CTL_A				0x60800
#घोषणा _SRD_CTL_EDP				0x6f800
#घोषणा _PSR_ADJ(tran, reg)			(_TRANS2(tran, reg) - dev_priv->hsw_psr_mmio_adjust)
#घोषणा EDP_PSR_CTL(tran)			_MMIO(_PSR_ADJ(tran, _SRD_CTL_A))
#घोषणा   EDP_PSR_ENABLE			(1 << 31)
#घोषणा   BDW_PSR_SINGLE_FRAME			(1 << 30)
#घोषणा   EDP_PSR_RESTORE_PSR_ACTIVE_CTX_MASK	(1 << 29) /* SW can't modअगरy */
#घोषणा   EDP_PSR_LINK_STANDBY			(1 << 27)
#घोषणा   EDP_PSR_MIN_LINK_ENTRY_TIME_MASK	(3 << 25)
#घोषणा   EDP_PSR_MIN_LINK_ENTRY_TIME_8_LINES	(0 << 25)
#घोषणा   EDP_PSR_MIN_LINK_ENTRY_TIME_4_LINES	(1 << 25)
#घोषणा   EDP_PSR_MIN_LINK_ENTRY_TIME_2_LINES	(2 << 25)
#घोषणा   EDP_PSR_MIN_LINK_ENTRY_TIME_0_LINES	(3 << 25)
#घोषणा   EDP_PSR_MAX_SLEEP_TIME_SHIFT		20
#घोषणा   EDP_PSR_SKIP_AUX_EXIT			(1 << 12)
#घोषणा   EDP_PSR_TP1_TP2_SEL			(0 << 11)
#घोषणा   EDP_PSR_TP1_TP3_SEL			(1 << 11)
#घोषणा   EDP_PSR_CRC_ENABLE			(1 << 10) /* BDW+ */
#घोषणा   EDP_PSR_TP2_TP3_TIME_500us		(0 << 8)
#घोषणा   EDP_PSR_TP2_TP3_TIME_100us		(1 << 8)
#घोषणा   EDP_PSR_TP2_TP3_TIME_2500us		(2 << 8)
#घोषणा   EDP_PSR_TP2_TP3_TIME_0us		(3 << 8)
#घोषणा   EDP_PSR_TP4_TIME_0US			(3 << 6) /* ICL+ */
#घोषणा   EDP_PSR_TP1_TIME_500us		(0 << 4)
#घोषणा   EDP_PSR_TP1_TIME_100us		(1 << 4)
#घोषणा   EDP_PSR_TP1_TIME_2500us		(2 << 4)
#घोषणा   EDP_PSR_TP1_TIME_0us			(3 << 4)
#घोषणा   EDP_PSR_IDLE_FRAME_SHIFT		0

/*
 * Until TGL, IMR/IIR are fixed at 0x648xx. On TGL+ those रेजिस्टरs are relative
 * to transcoder and bits defined क्रम each one as अगर using no shअगरt (i.e. as अगर
 * it was क्रम TRANSCODER_EDP)
 */
#घोषणा EDP_PSR_IMR				_MMIO(0x64834)
#घोषणा EDP_PSR_IIR				_MMIO(0x64838)
#घोषणा _PSR_IMR_A				0x60814
#घोषणा _PSR_IIR_A				0x60818
#घोषणा TRANS_PSR_IMR(tran)			_MMIO_TRANS2(tran, _PSR_IMR_A)
#घोषणा TRANS_PSR_IIR(tran)			_MMIO_TRANS2(tran, _PSR_IIR_A)
#घोषणा   _EDP_PSR_TRANS_SHIFT(trans)		((trans) == TRANSCODER_EDP ? \
						 0 : ((trans) - TRANSCODER_A + 1) * 8)
#घोषणा   EDP_PSR_TRANS_MASK(trans)		(0x7 << _EDP_PSR_TRANS_SHIFT(trans))
#घोषणा   EDP_PSR_ERROR(trans)			(0x4 << _EDP_PSR_TRANS_SHIFT(trans))
#घोषणा   EDP_PSR_POST_EXIT(trans)		(0x2 << _EDP_PSR_TRANS_SHIFT(trans))
#घोषणा   EDP_PSR_PRE_ENTRY(trans)		(0x1 << _EDP_PSR_TRANS_SHIFT(trans))

#घोषणा _SRD_AUX_CTL_A				0x60810
#घोषणा _SRD_AUX_CTL_EDP			0x6f810
#घोषणा EDP_PSR_AUX_CTL(tran)			_MMIO(_PSR_ADJ(tran, _SRD_AUX_CTL_A))
#घोषणा   EDP_PSR_AUX_CTL_TIME_OUT_MASK		(3 << 26)
#घोषणा   EDP_PSR_AUX_CTL_MESSAGE_SIZE_MASK	(0x1f << 20)
#घोषणा   EDP_PSR_AUX_CTL_PRECHARGE_2US_MASK	(0xf << 16)
#घोषणा   EDP_PSR_AUX_CTL_ERROR_INTERRUPT	(1 << 11)
#घोषणा   EDP_PSR_AUX_CTL_BIT_CLOCK_2X_MASK	(0x7ff)

#घोषणा _SRD_AUX_DATA_A				0x60814
#घोषणा _SRD_AUX_DATA_EDP			0x6f814
#घोषणा EDP_PSR_AUX_DATA(tran, i)		_MMIO(_PSR_ADJ(tran, _SRD_AUX_DATA_A) + (i) + 4) /* 5 रेजिस्टरs */

#घोषणा _SRD_STATUS_A				0x60840
#घोषणा _SRD_STATUS_EDP				0x6f840
#घोषणा EDP_PSR_STATUS(tran)			_MMIO(_PSR_ADJ(tran, _SRD_STATUS_A))
#घोषणा   EDP_PSR_STATUS_STATE_MASK		(7 << 29)
#घोषणा   EDP_PSR_STATUS_STATE_SHIFT		29
#घोषणा   EDP_PSR_STATUS_STATE_IDLE		(0 << 29)
#घोषणा   EDP_PSR_STATUS_STATE_SRDONACK		(1 << 29)
#घोषणा   EDP_PSR_STATUS_STATE_SRDENT		(2 << 29)
#घोषणा   EDP_PSR_STATUS_STATE_BUFOFF		(3 << 29)
#घोषणा   EDP_PSR_STATUS_STATE_BUFON		(4 << 29)
#घोषणा   EDP_PSR_STATUS_STATE_AUXACK		(5 << 29)
#घोषणा   EDP_PSR_STATUS_STATE_SRDOFFACK	(6 << 29)
#घोषणा   EDP_PSR_STATUS_LINK_MASK		(3 << 26)
#घोषणा   EDP_PSR_STATUS_LINK_FULL_OFF		(0 << 26)
#घोषणा   EDP_PSR_STATUS_LINK_FULL_ON		(1 << 26)
#घोषणा   EDP_PSR_STATUS_LINK_STANDBY		(2 << 26)
#घोषणा   EDP_PSR_STATUS_MAX_SLEEP_TIMER_SHIFT	20
#घोषणा   EDP_PSR_STATUS_MAX_SLEEP_TIMER_MASK	0x1f
#घोषणा   EDP_PSR_STATUS_COUNT_SHIFT		16
#घोषणा   EDP_PSR_STATUS_COUNT_MASK		0xf
#घोषणा   EDP_PSR_STATUS_AUX_ERROR		(1 << 15)
#घोषणा   EDP_PSR_STATUS_AUX_SENDING		(1 << 12)
#घोषणा   EDP_PSR_STATUS_SENDING_IDLE		(1 << 9)
#घोषणा   EDP_PSR_STATUS_SENDING_TP2_TP3	(1 << 8)
#घोषणा   EDP_PSR_STATUS_SENDING_TP1		(1 << 4)
#घोषणा   EDP_PSR_STATUS_IDLE_MASK		0xf

#घोषणा _SRD_PERF_CNT_A			0x60844
#घोषणा _SRD_PERF_CNT_EDP		0x6f844
#घोषणा EDP_PSR_PERF_CNT(tran)		_MMIO(_PSR_ADJ(tran, _SRD_PERF_CNT_A))
#घोषणा   EDP_PSR_PERF_CNT_MASK		0xffffff

/* PSR_MASK on SKL+ */
#घोषणा _SRD_DEBUG_A				0x60860
#घोषणा _SRD_DEBUG_EDP				0x6f860
#घोषणा EDP_PSR_DEBUG(tran)			_MMIO(_PSR_ADJ(tran, _SRD_DEBUG_A))
#घोषणा   EDP_PSR_DEBUG_MASK_MAX_SLEEP         (1 << 28)
#घोषणा   EDP_PSR_DEBUG_MASK_LPSP              (1 << 27)
#घोषणा   EDP_PSR_DEBUG_MASK_MEMUP             (1 << 26)
#घोषणा   EDP_PSR_DEBUG_MASK_HPD               (1 << 25)
#घोषणा   EDP_PSR_DEBUG_MASK_DISP_REG_WRITE    (1 << 16) /* Reserved in ICL+ */
#घोषणा   EDP_PSR_DEBUG_EXIT_ON_PIXEL_UNDERRUN (1 << 15) /* SKL+ */

#घोषणा _PSR2_CTL_A				0x60900
#घोषणा _PSR2_CTL_EDP				0x6f900
#घोषणा EDP_PSR2_CTL(tran)			_MMIO_TRANS2(tran, _PSR2_CTL_A)
#घोषणा   EDP_PSR2_ENABLE			(1 << 31)
#घोषणा   EDP_SU_TRACK_ENABLE			(1 << 30)
#घोषणा   TGL_EDP_PSR2_BLOCK_COUNT_NUM_2	(0 << 28)
#घोषणा   TGL_EDP_PSR2_BLOCK_COUNT_NUM_3	(1 << 28)
#घोषणा   EDP_Y_COORDINATE_VALID		(1 << 26) /* GLK and CNL+ */
#घोषणा   EDP_Y_COORDINATE_ENABLE		(1 << 25) /* GLK and CNL+ */
#घोषणा   EDP_MAX_SU_DISABLE_TIME(t)		((t) << 20)
#घोषणा   EDP_MAX_SU_DISABLE_TIME_MASK		(0x1f << 20)
#घोषणा   EDP_PSR2_IO_BUFFER_WAKE_MAX_LINES	8
#घोषणा   EDP_PSR2_IO_BUFFER_WAKE(lines)	((EDP_PSR2_IO_BUFFER_WAKE_MAX_LINES - (lines)) << 13)
#घोषणा   EDP_PSR2_IO_BUFFER_WAKE_MASK		(3 << 13)
#घोषणा   TGL_EDP_PSR2_IO_BUFFER_WAKE_MIN_LINES	5
#घोषणा   TGL_EDP_PSR2_IO_BUFFER_WAKE(lines)	(((lines) - TGL_EDP_PSR2_IO_BUFFER_WAKE_MIN_LINES) << 13)
#घोषणा   TGL_EDP_PSR2_IO_BUFFER_WAKE_MASK	(7 << 13)
#घोषणा   EDP_PSR2_FAST_WAKE_MAX_LINES		8
#घोषणा   EDP_PSR2_FAST_WAKE(lines)		((EDP_PSR2_FAST_WAKE_MAX_LINES - (lines)) << 11)
#घोषणा   EDP_PSR2_FAST_WAKE_MASK		(3 << 11)
#घोषणा   TGL_EDP_PSR2_FAST_WAKE_MIN_LINES	5
#घोषणा   TGL_EDP_PSR2_FAST_WAKE(lines)		(((lines) - TGL_EDP_PSR2_FAST_WAKE_MIN_LINES) << 10)
#घोषणा   TGL_EDP_PSR2_FAST_WAKE_MASK		(7 << 10)
#घोषणा   EDP_PSR2_TP2_TIME_500us		(0 << 8)
#घोषणा   EDP_PSR2_TP2_TIME_100us		(1 << 8)
#घोषणा   EDP_PSR2_TP2_TIME_2500us		(2 << 8)
#घोषणा   EDP_PSR2_TP2_TIME_50us		(3 << 8)
#घोषणा   EDP_PSR2_TP2_TIME_MASK		(3 << 8)
#घोषणा   EDP_PSR2_FRAME_BEFORE_SU_SHIFT	4
#घोषणा   EDP_PSR2_FRAME_BEFORE_SU_MASK		(0xf << 4)
#घोषणा   EDP_PSR2_FRAME_BEFORE_SU(a)		((a) << 4)
#घोषणा   EDP_PSR2_IDLE_FRAME_MASK		0xf
#घोषणा   EDP_PSR2_IDLE_FRAME_SHIFT		0

#घोषणा _PSR_EVENT_TRANS_A			0x60848
#घोषणा _PSR_EVENT_TRANS_B			0x61848
#घोषणा _PSR_EVENT_TRANS_C			0x62848
#घोषणा _PSR_EVENT_TRANS_D			0x63848
#घोषणा _PSR_EVENT_TRANS_EDP			0x6f848
#घोषणा PSR_EVENT(tran)				_MMIO_TRANS2(tran, _PSR_EVENT_TRANS_A)
#घोषणा  PSR_EVENT_PSR2_WD_TIMER_EXPIRE		(1 << 17)
#घोषणा  PSR_EVENT_PSR2_DISABLED		(1 << 16)
#घोषणा  PSR_EVENT_SU_सूचीTY_FIFO_UNDERRUN	(1 << 15)
#घोषणा  PSR_EVENT_SU_CRC_FIFO_UNDERRUN		(1 << 14)
#घोषणा  PSR_EVENT_GRAPHICS_RESET		(1 << 12)
#घोषणा  PSR_EVENT_PCH_INTERRUPT		(1 << 11)
#घोषणा  PSR_EVENT_MEMORY_UP			(1 << 10)
#घोषणा  PSR_EVENT_FRONT_BUFFER_MODIFY		(1 << 9)
#घोषणा  PSR_EVENT_WD_TIMER_EXPIRE		(1 << 8)
#घोषणा  PSR_EVENT_PIPE_REGISTERS_UPDATE	(1 << 6)
#घोषणा  PSR_EVENT_REGISTER_UPDATE		(1 << 5) /* Reserved in ICL+ */
#घोषणा  PSR_EVENT_HDCP_ENABLE			(1 << 4)
#घोषणा  PSR_EVENT_KVMR_SESSION_ENABLE		(1 << 3)
#घोषणा  PSR_EVENT_VBI_ENABLE			(1 << 2)
#घोषणा  PSR_EVENT_LPSP_MODE_EXIT		(1 << 1)
#घोषणा  PSR_EVENT_PSR_DISABLE			(1 << 0)

#घोषणा _PSR2_STATUS_A			0x60940
#घोषणा _PSR2_STATUS_EDP		0x6f940
#घोषणा EDP_PSR2_STATUS(tran)		_MMIO_TRANS2(tran, _PSR2_STATUS_A)
#घोषणा EDP_PSR2_STATUS_STATE_MASK     (0xf << 28)
#घोषणा EDP_PSR2_STATUS_STATE_SHIFT    28

#घोषणा _PSR2_SU_STATUS_A		0x60914
#घोषणा _PSR2_SU_STATUS_EDP		0x6f914
#घोषणा _PSR2_SU_STATUS(tran, index)	_MMIO(_TRANS2(tran, _PSR2_SU_STATUS_A) + (index) * 4)
#घोषणा PSR2_SU_STATUS(tran, frame)	(_PSR2_SU_STATUS(tran, (frame) / 3))
#घोषणा PSR2_SU_STATUS_SHIFT(frame)	(((frame) % 3) * 10)
#घोषणा PSR2_SU_STATUS_MASK(frame)	(0x3ff << PSR2_SU_STATUS_SHIFT(frame))
#घोषणा PSR2_SU_STATUS_FRAMES		8

#घोषणा _PSR2_MAN_TRK_CTL_A				0x60910
#घोषणा _PSR2_MAN_TRK_CTL_EDP				0x6f910
#घोषणा PSR2_MAN_TRK_CTL(tran)				_MMIO_TRANS2(tran, _PSR2_MAN_TRK_CTL_A)
#घोषणा  PSR2_MAN_TRK_CTL_ENABLE			REG_BIT(31)
#घोषणा  PSR2_MAN_TRK_CTL_SU_REGION_START_ADDR_MASK	REG_GENMASK(30, 21)
#घोषणा  PSR2_MAN_TRK_CTL_SU_REGION_START_ADDR(val)	REG_FIELD_PREP(PSR2_MAN_TRK_CTL_SU_REGION_START_ADDR_MASK, val)
#घोषणा  PSR2_MAN_TRK_CTL_SU_REGION_END_ADDR_MASK		REG_GENMASK(20, 11)
#घोषणा  PSR2_MAN_TRK_CTL_SU_REGION_END_ADDR(val)		REG_FIELD_PREP(PSR2_MAN_TRK_CTL_SU_REGION_END_ADDR_MASK, val)
#घोषणा  PSR2_MAN_TRK_CTL_SF_SINGLE_FULL_FRAME		REG_BIT(3)
#घोषणा  PSR2_MAN_TRK_CTL_SF_CONTINUOS_FULL_FRAME	REG_BIT(2)
#घोषणा  PSR2_MAN_TRK_CTL_SF_PARTIAL_FRAME_UPDATE	REG_BIT(1)

/* Icelake DSC Rate Control Range Parameter Registers */
#घोषणा DSCA_RC_RANGE_PARAMETERS_0		_MMIO(0x6B240)
#घोषणा DSCA_RC_RANGE_PARAMETERS_0_UDW		_MMIO(0x6B240 + 4)
#घोषणा DSCC_RC_RANGE_PARAMETERS_0		_MMIO(0x6BA40)
#घोषणा DSCC_RC_RANGE_PARAMETERS_0_UDW		_MMIO(0x6BA40 + 4)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_0_PB	(0x78208)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_0_UDW_PB	(0x78208 + 4)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_0_PB	(0x78308)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_0_UDW_PB	(0x78308 + 4)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_0_PC	(0x78408)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_0_UDW_PC	(0x78408 + 4)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_0_PC	(0x78508)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_0_UDW_PC	(0x78508 + 4)
#घोषणा ICL_DSC0_RC_RANGE_PARAMETERS_0(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_0_PB, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_0_PC)
#घोषणा ICL_DSC0_RC_RANGE_PARAMETERS_0_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_0_UDW_PB, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_0_UDW_PC)
#घोषणा ICL_DSC1_RC_RANGE_PARAMETERS_0(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_0_PB, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_0_PC)
#घोषणा ICL_DSC1_RC_RANGE_PARAMETERS_0_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_0_UDW_PB, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_0_UDW_PC)
#घोषणा RC_BPG_OFFSET_SHIFT			10
#घोषणा RC_MAX_QP_SHIFT				5
#घोषणा RC_MIN_QP_SHIFT				0

#घोषणा DSCA_RC_RANGE_PARAMETERS_1		_MMIO(0x6B248)
#घोषणा DSCA_RC_RANGE_PARAMETERS_1_UDW		_MMIO(0x6B248 + 4)
#घोषणा DSCC_RC_RANGE_PARAMETERS_1		_MMIO(0x6BA48)
#घोषणा DSCC_RC_RANGE_PARAMETERS_1_UDW		_MMIO(0x6BA48 + 4)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_1_PB	(0x78210)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_1_UDW_PB	(0x78210 + 4)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_1_PB	(0x78310)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_1_UDW_PB	(0x78310 + 4)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_1_PC	(0x78410)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_1_UDW_PC	(0x78410 + 4)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_1_PC	(0x78510)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_1_UDW_PC	(0x78510 + 4)
#घोषणा ICL_DSC0_RC_RANGE_PARAMETERS_1(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_1_PB, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_1_PC)
#घोषणा ICL_DSC0_RC_RANGE_PARAMETERS_1_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_1_UDW_PB, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_1_UDW_PC)
#घोषणा ICL_DSC1_RC_RANGE_PARAMETERS_1(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_1_PB, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_1_PC)
#घोषणा ICL_DSC1_RC_RANGE_PARAMETERS_1_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_1_UDW_PB, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_1_UDW_PC)

#घोषणा DSCA_RC_RANGE_PARAMETERS_2		_MMIO(0x6B250)
#घोषणा DSCA_RC_RANGE_PARAMETERS_2_UDW		_MMIO(0x6B250 + 4)
#घोषणा DSCC_RC_RANGE_PARAMETERS_2		_MMIO(0x6BA50)
#घोषणा DSCC_RC_RANGE_PARAMETERS_2_UDW		_MMIO(0x6BA50 + 4)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_2_PB	(0x78218)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_2_UDW_PB	(0x78218 + 4)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_2_PB	(0x78318)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_2_UDW_PB	(0x78318 + 4)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_2_PC	(0x78418)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_2_UDW_PC	(0x78418 + 4)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_2_PC	(0x78518)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_2_UDW_PC	(0x78518 + 4)
#घोषणा ICL_DSC0_RC_RANGE_PARAMETERS_2(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_2_PB, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_2_PC)
#घोषणा ICL_DSC0_RC_RANGE_PARAMETERS_2_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_2_UDW_PB, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_2_UDW_PC)
#घोषणा ICL_DSC1_RC_RANGE_PARAMETERS_2(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_2_PB, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_2_PC)
#घोषणा ICL_DSC1_RC_RANGE_PARAMETERS_2_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_2_UDW_PB, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_2_UDW_PC)

#घोषणा DSCA_RC_RANGE_PARAMETERS_3		_MMIO(0x6B258)
#घोषणा DSCA_RC_RANGE_PARAMETERS_3_UDW		_MMIO(0x6B258 + 4)
#घोषणा DSCC_RC_RANGE_PARAMETERS_3		_MMIO(0x6BA58)
#घोषणा DSCC_RC_RANGE_PARAMETERS_3_UDW		_MMIO(0x6BA58 + 4)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_3_PB	(0x78220)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_3_UDW_PB	(0x78220 + 4)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_3_PB	(0x78320)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_3_UDW_PB	(0x78320 + 4)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_3_PC	(0x78420)
#घोषणा _ICL_DSC0_RC_RANGE_PARAMETERS_3_UDW_PC	(0x78420 + 4)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_3_PC	(0x78520)
#घोषणा _ICL_DSC1_RC_RANGE_PARAMETERS_3_UDW_PC	(0x78520 + 4)
#घोषणा ICL_DSC0_RC_RANGE_PARAMETERS_3(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_3_PB, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_3_PC)
#घोषणा ICL_DSC0_RC_RANGE_PARAMETERS_3_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_3_UDW_PB, \
							_ICL_DSC0_RC_RANGE_PARAMETERS_3_UDW_PC)
#घोषणा ICL_DSC1_RC_RANGE_PARAMETERS_3(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_3_PB, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_3_PC)
#घोषणा ICL_DSC1_RC_RANGE_PARAMETERS_3_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_3_UDW_PB, \
							_ICL_DSC1_RC_RANGE_PARAMETERS_3_UDW_PC)

/* VGA port control */
#घोषणा ADPA			_MMIO(0x61100)
#घोषणा PCH_ADPA                _MMIO(0xe1100)
#घोषणा VLV_ADPA		_MMIO(VLV_DISPLAY_BASE + 0x61100)

#घोषणा   ADPA_DAC_ENABLE	(1 << 31)
#घोषणा   ADPA_DAC_DISABLE	0
#घोषणा   ADPA_PIPE_SEL_SHIFT		30
#घोषणा   ADPA_PIPE_SEL_MASK		(1 << 30)
#घोषणा   ADPA_PIPE_SEL(pipe)		((pipe) << 30)
#घोषणा   ADPA_PIPE_SEL_SHIFT_CPT	29
#घोषणा   ADPA_PIPE_SEL_MASK_CPT	(3 << 29)
#घोषणा   ADPA_PIPE_SEL_CPT(pipe)	((pipe) << 29)
#घोषणा   ADPA_CRT_HOTPLUG_MASK  0x03ff0000 /* bit 25-16 */
#घोषणा   ADPA_CRT_HOTPLUG_MONITOR_NONE  (0 << 24)
#घोषणा   ADPA_CRT_HOTPLUG_MONITOR_MASK  (3 << 24)
#घोषणा   ADPA_CRT_HOTPLUG_MONITOR_COLOR (3 << 24)
#घोषणा   ADPA_CRT_HOTPLUG_MONITOR_MONO  (2 << 24)
#घोषणा   ADPA_CRT_HOTPLUG_ENABLE        (1 << 23)
#घोषणा   ADPA_CRT_HOTPLUG_PERIOD_64     (0 << 22)
#घोषणा   ADPA_CRT_HOTPLUG_PERIOD_128    (1 << 22)
#घोषणा   ADPA_CRT_HOTPLUG_WARMUP_5MS    (0 << 21)
#घोषणा   ADPA_CRT_HOTPLUG_WARMUP_10MS   (1 << 21)
#घोषणा   ADPA_CRT_HOTPLUG_SAMPLE_2S     (0 << 20)
#घोषणा   ADPA_CRT_HOTPLUG_SAMPLE_4S     (1 << 20)
#घोषणा   ADPA_CRT_HOTPLUG_VOLTAGE_40    (0 << 18)
#घोषणा   ADPA_CRT_HOTPLUG_VOLTAGE_50    (1 << 18)
#घोषणा   ADPA_CRT_HOTPLUG_VOLTAGE_60    (2 << 18)
#घोषणा   ADPA_CRT_HOTPLUG_VOLTAGE_70    (3 << 18)
#घोषणा   ADPA_CRT_HOTPLUG_VOLREF_325MV  (0 << 17)
#घोषणा   ADPA_CRT_HOTPLUG_VOLREF_475MV  (1 << 17)
#घोषणा   ADPA_CRT_HOTPLUG_FORCE_TRIGGER (1 << 16)
#घोषणा   ADPA_USE_VGA_HVPOLARITY (1 << 15)
#घोषणा   ADPA_SETS_HVPOLARITY	0
#घोषणा   ADPA_VSYNC_CNTL_DISABLE (1 << 10)
#घोषणा   ADPA_VSYNC_CNTL_ENABLE 0
#घोषणा   ADPA_HSYNC_CNTL_DISABLE (1 << 11)
#घोषणा   ADPA_HSYNC_CNTL_ENABLE 0
#घोषणा   ADPA_VSYNC_ACTIVE_HIGH (1 << 4)
#घोषणा   ADPA_VSYNC_ACTIVE_LOW	0
#घोषणा   ADPA_HSYNC_ACTIVE_HIGH (1 << 3)
#घोषणा   ADPA_HSYNC_ACTIVE_LOW	0
#घोषणा   ADPA_DPMS_MASK	(~(3 << 10))
#घोषणा   ADPA_DPMS_ON		(0 << 10)
#घोषणा   ADPA_DPMS_SUSPEND	(1 << 10)
#घोषणा   ADPA_DPMS_STANDBY	(2 << 10)
#घोषणा   ADPA_DPMS_OFF		(3 << 10)


/* Hotplug control (945+ only) */
#घोषणा PORT_HOTPLUG_EN		_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61110)
#घोषणा   PORTB_HOTPLUG_INT_EN			(1 << 29)
#घोषणा   PORTC_HOTPLUG_INT_EN			(1 << 28)
#घोषणा   PORTD_HOTPLUG_INT_EN			(1 << 27)
#घोषणा   SDVOB_HOTPLUG_INT_EN			(1 << 26)
#घोषणा   SDVOC_HOTPLUG_INT_EN			(1 << 25)
#घोषणा   TV_HOTPLUG_INT_EN			(1 << 18)
#घोषणा   CRT_HOTPLUG_INT_EN			(1 << 9)
#घोषणा HOTPLUG_INT_EN_MASK			(PORTB_HOTPLUG_INT_EN | \
						 PORTC_HOTPLUG_INT_EN | \
						 PORTD_HOTPLUG_INT_EN | \
						 SDVOC_HOTPLUG_INT_EN | \
						 SDVOB_HOTPLUG_INT_EN | \
						 CRT_HOTPLUG_INT_EN)
#घोषणा   CRT_HOTPLUG_FORCE_DETECT		(1 << 3)
#घोषणा CRT_HOTPLUG_ACTIVATION_PERIOD_32	(0 << 8)
/* must use period 64 on GM45 according to करोcs */
#घोषणा CRT_HOTPLUG_ACTIVATION_PERIOD_64	(1 << 8)
#घोषणा CRT_HOTPLUG_DAC_ON_TIME_2M		(0 << 7)
#घोषणा CRT_HOTPLUG_DAC_ON_TIME_4M		(1 << 7)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_40		(0 << 5)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_50		(1 << 5)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_60		(2 << 5)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_70		(3 << 5)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_MASK	(3 << 5)
#घोषणा CRT_HOTPLUG_DETECT_DELAY_1G		(0 << 4)
#घोषणा CRT_HOTPLUG_DETECT_DELAY_2G		(1 << 4)
#घोषणा CRT_HOTPLUG_DETECT_VOLTAGE_325MV	(0 << 2)
#घोषणा CRT_HOTPLUG_DETECT_VOLTAGE_475MV	(1 << 2)

#घोषणा PORT_HOTPLUG_STAT	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61114)
/*
 * HDMI/DP bits are g4x+
 *
 * WARNING: Bspec क्रम hpd status bits on gen4 seems to be completely confused.
 * Please check the detailed lore in the commit message क्रम क्रम experimental
 * evidence.
 */
/* Bspec says GM45 should match G4X/VLV/CHV, but reality disagrees */
#घोषणा   PORTD_HOTPLUG_LIVE_STATUS_GM45	(1 << 29)
#घोषणा   PORTC_HOTPLUG_LIVE_STATUS_GM45	(1 << 28)
#घोषणा   PORTB_HOTPLUG_LIVE_STATUS_GM45	(1 << 27)
/* G4X/VLV/CHV DP/HDMI bits again match Bspec */
#घोषणा   PORTD_HOTPLUG_LIVE_STATUS_G4X		(1 << 27)
#घोषणा   PORTC_HOTPLUG_LIVE_STATUS_G4X		(1 << 28)
#घोषणा   PORTB_HOTPLUG_LIVE_STATUS_G4X		(1 << 29)
#घोषणा   PORTD_HOTPLUG_INT_STATUS		(3 << 21)
#घोषणा   PORTD_HOTPLUG_INT_LONG_PULSE		(2 << 21)
#घोषणा   PORTD_HOTPLUG_INT_SHORT_PULSE		(1 << 21)
#घोषणा   PORTC_HOTPLUG_INT_STATUS		(3 << 19)
#घोषणा   PORTC_HOTPLUG_INT_LONG_PULSE		(2 << 19)
#घोषणा   PORTC_HOTPLUG_INT_SHORT_PULSE		(1 << 19)
#घोषणा   PORTB_HOTPLUG_INT_STATUS		(3 << 17)
#घोषणा   PORTB_HOTPLUG_INT_LONG_PULSE		(2 << 17)
#घोषणा   PORTB_HOTPLUG_INT_SHORT_PLUSE		(1 << 17)
/* CRT/TV common between gen3+ */
#घोषणा   CRT_HOTPLUG_INT_STATUS		(1 << 11)
#घोषणा   TV_HOTPLUG_INT_STATUS			(1 << 10)
#घोषणा   CRT_HOTPLUG_MONITOR_MASK		(3 << 8)
#घोषणा   CRT_HOTPLUG_MONITOR_COLOR		(3 << 8)
#घोषणा   CRT_HOTPLUG_MONITOR_MONO		(2 << 8)
#घोषणा   CRT_HOTPLUG_MONITOR_NONE		(0 << 8)
#घोषणा   DP_AUX_CHANNEL_D_INT_STATUS_G4X	(1 << 6)
#घोषणा   DP_AUX_CHANNEL_C_INT_STATUS_G4X	(1 << 5)
#घोषणा   DP_AUX_CHANNEL_B_INT_STATUS_G4X	(1 << 4)
#घोषणा   DP_AUX_CHANNEL_MASK_INT_STATUS_G4X	(7 << 4)

/* SDVO is dअगरferent across gen3/4 */
#घोषणा   SDVOC_HOTPLUG_INT_STATUS_G4X		(1 << 3)
#घोषणा   SDVOB_HOTPLUG_INT_STATUS_G4X		(1 << 2)
/*
 * Bspec seems to be seriously misleaded about the SDVO hpd bits on i965g/gm,
 * since reality corrobates that they're the same as on gen3. But keep these
 * bits here (and the comment!) to help any other lost wanderers back onto the
 * right tracks.
 */
#घोषणा   SDVOC_HOTPLUG_INT_STATUS_I965		(3 << 4)
#घोषणा   SDVOB_HOTPLUG_INT_STATUS_I965		(3 << 2)
#घोषणा   SDVOC_HOTPLUG_INT_STATUS_I915		(1 << 7)
#घोषणा   SDVOB_HOTPLUG_INT_STATUS_I915		(1 << 6)
#घोषणा   HOTPLUG_INT_STATUS_G4X		(CRT_HOTPLUG_INT_STATUS | \
						 SDVOB_HOTPLUG_INT_STATUS_G4X | \
						 SDVOC_HOTPLUG_INT_STATUS_G4X | \
						 PORTB_HOTPLUG_INT_STATUS | \
						 PORTC_HOTPLUG_INT_STATUS | \
						 PORTD_HOTPLUG_INT_STATUS)

#घोषणा HOTPLUG_INT_STATUS_I915			(CRT_HOTPLUG_INT_STATUS | \
						 SDVOB_HOTPLUG_INT_STATUS_I915 | \
						 SDVOC_HOTPLUG_INT_STATUS_I915 | \
						 PORTB_HOTPLUG_INT_STATUS | \
						 PORTC_HOTPLUG_INT_STATUS | \
						 PORTD_HOTPLUG_INT_STATUS)

/* SDVO and HDMI port control.
 * The same रेजिस्टर may be used क्रम SDVO or HDMI */
#घोषणा _GEN3_SDVOB	0x61140
#घोषणा _GEN3_SDVOC	0x61160
#घोषणा GEN3_SDVOB	_MMIO(_GEN3_SDVOB)
#घोषणा GEN3_SDVOC	_MMIO(_GEN3_SDVOC)
#घोषणा GEN4_HDMIB	GEN3_SDVOB
#घोषणा GEN4_HDMIC	GEN3_SDVOC
#घोषणा VLV_HDMIB	_MMIO(VLV_DISPLAY_BASE + 0x61140)
#घोषणा VLV_HDMIC	_MMIO(VLV_DISPLAY_BASE + 0x61160)
#घोषणा CHV_HDMID	_MMIO(VLV_DISPLAY_BASE + 0x6116C)
#घोषणा PCH_SDVOB	_MMIO(0xe1140)
#घोषणा PCH_HDMIB	PCH_SDVOB
#घोषणा PCH_HDMIC	_MMIO(0xe1150)
#घोषणा PCH_HDMID	_MMIO(0xe1160)

#घोषणा PORT_DFT_I9XX				_MMIO(0x61150)
#घोषणा   DC_BALANCE_RESET			(1 << 25)
#घोषणा PORT_DFT2_G4X		_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61154)
#घोषणा   DC_BALANCE_RESET_VLV			(1 << 31)
#घोषणा   PIPE_SCRAMBLE_RESET_MASK		((1 << 14) | (0x3 << 0))
#घोषणा   PIPE_C_SCRAMBLE_RESET			(1 << 14) /* chv */
#घोषणा   PIPE_B_SCRAMBLE_RESET			(1 << 1)
#घोषणा   PIPE_A_SCRAMBLE_RESET			(1 << 0)

/* Gen 3 SDVO bits: */
#घोषणा   SDVO_ENABLE				(1 << 31)
#घोषणा   SDVO_PIPE_SEL_SHIFT			30
#घोषणा   SDVO_PIPE_SEL_MASK			(1 << 30)
#घोषणा   SDVO_PIPE_SEL(pipe)			((pipe) << 30)
#घोषणा   SDVO_STALL_SELECT			(1 << 29)
#घोषणा   SDVO_INTERRUPT_ENABLE			(1 << 26)
/*
 * 915G/GM SDVO pixel multiplier.
 * Programmed value is multiplier - 1, up to 5x.
 * \sa DPLL_MD_UDI_MULTIPLIER_MASK
 */
#घोषणा   SDVO_PORT_MULTIPLY_MASK		(7 << 23)
#घोषणा   SDVO_PORT_MULTIPLY_SHIFT		23
#घोषणा   SDVO_PHASE_SELECT_MASK		(15 << 19)
#घोषणा   SDVO_PHASE_SELECT_DEFAULT		(6 << 19)
#घोषणा   SDVO_CLOCK_OUTPUT_INVERT		(1 << 18)
#घोषणा   SDVOC_GANG_MODE			(1 << 16) /* Port C only */
#घोषणा   SDVO_BORDER_ENABLE			(1 << 7) /* SDVO only */
#घोषणा   SDVOB_PCIE_CONCURRENCY		(1 << 3) /* Port B only */
#घोषणा   SDVO_DETECTED				(1 << 2)
/* Bits to be preserved when writing */
#घोषणा   SDVOB_PRESERVE_MASK ((1 << 17) | (1 << 16) | (1 << 14) | \
			       SDVO_INTERRUPT_ENABLE)
#घोषणा   SDVOC_PRESERVE_MASK ((1 << 17) | SDVO_INTERRUPT_ENABLE)

/* Gen 4 SDVO/HDMI bits: */
#घोषणा   SDVO_COLOR_FORMAT_8bpc		(0 << 26)
#घोषणा   SDVO_COLOR_FORMAT_MASK		(7 << 26)
#घोषणा   SDVO_ENCODING_SDVO			(0 << 10)
#घोषणा   SDVO_ENCODING_HDMI			(2 << 10)
#घोषणा   HDMI_MODE_SELECT_HDMI			(1 << 9) /* HDMI only */
#घोषणा   HDMI_MODE_SELECT_DVI			(0 << 9) /* HDMI only */
#घोषणा   HDMI_COLOR_RANGE_16_235		(1 << 8) /* HDMI only */
#घोषणा   HDMI_AUDIO_ENABLE			(1 << 6) /* HDMI only */
/* VSYNC/HSYNC bits new with 965, शेष is to be set */
#घोषणा   SDVO_VSYNC_ACTIVE_HIGH		(1 << 4)
#घोषणा   SDVO_HSYNC_ACTIVE_HIGH		(1 << 3)

/* Gen 5 (IBX) SDVO/HDMI bits: */
#घोषणा   HDMI_COLOR_FORMAT_12bpc		(3 << 26) /* HDMI only */
#घोषणा   SDVOB_HOTPLUG_ENABLE			(1 << 23) /* SDVO only */

/* Gen 6 (CPT) SDVO/HDMI bits: */
#घोषणा   SDVO_PIPE_SEL_SHIFT_CPT		29
#घोषणा   SDVO_PIPE_SEL_MASK_CPT		(3 << 29)
#घोषणा   SDVO_PIPE_SEL_CPT(pipe)		((pipe) << 29)

/* CHV SDVO/HDMI bits: */
#घोषणा   SDVO_PIPE_SEL_SHIFT_CHV		24
#घोषणा   SDVO_PIPE_SEL_MASK_CHV		(3 << 24)
#घोषणा   SDVO_PIPE_SEL_CHV(pipe)		((pipe) << 24)


/* DVO port control */
#घोषणा _DVOA			0x61120
#घोषणा DVOA			_MMIO(_DVOA)
#घोषणा _DVOB			0x61140
#घोषणा DVOB			_MMIO(_DVOB)
#घोषणा _DVOC			0x61160
#घोषणा DVOC			_MMIO(_DVOC)
#घोषणा   DVO_ENABLE			(1 << 31)
#घोषणा   DVO_PIPE_SEL_SHIFT		30
#घोषणा   DVO_PIPE_SEL_MASK		(1 << 30)
#घोषणा   DVO_PIPE_SEL(pipe)		((pipe) << 30)
#घोषणा   DVO_PIPE_STALL_UNUSED		(0 << 28)
#घोषणा   DVO_PIPE_STALL		(1 << 28)
#घोषणा   DVO_PIPE_STALL_TV		(2 << 28)
#घोषणा   DVO_PIPE_STALL_MASK		(3 << 28)
#घोषणा   DVO_USE_VGA_SYNC		(1 << 15)
#घोषणा   DVO_DATA_ORDER_I740		(0 << 14)
#घोषणा   DVO_DATA_ORDER_FP		(1 << 14)
#घोषणा   DVO_VSYNC_DISABLE		(1 << 11)
#घोषणा   DVO_HSYNC_DISABLE		(1 << 10)
#घोषणा   DVO_VSYNC_TRISTATE		(1 << 9)
#घोषणा   DVO_HSYNC_TRISTATE		(1 << 8)
#घोषणा   DVO_BORDER_ENABLE		(1 << 7)
#घोषणा   DVO_DATA_ORDER_GBRG		(1 << 6)
#घोषणा   DVO_DATA_ORDER_RGGB		(0 << 6)
#घोषणा   DVO_DATA_ORDER_GBRG_ERRATA	(0 << 6)
#घोषणा   DVO_DATA_ORDER_RGGB_ERRATA	(1 << 6)
#घोषणा   DVO_VSYNC_ACTIVE_HIGH		(1 << 4)
#घोषणा   DVO_HSYNC_ACTIVE_HIGH		(1 << 3)
#घोषणा   DVO_BLANK_ACTIVE_HIGH		(1 << 2)
#घोषणा   DVO_OUTPUT_CSTATE_PIXELS	(1 << 1)	/* SDG only */
#घोषणा   DVO_OUTPUT_SOURCE_SIZE_PIXELS	(1 << 0)	/* SDG only */
#घोषणा   DVO_PRESERVE_MASK		(0x7 << 24)
#घोषणा DVOA_SRCDIM		_MMIO(0x61124)
#घोषणा DVOB_SRCDIM		_MMIO(0x61144)
#घोषणा DVOC_SRCDIM		_MMIO(0x61164)
#घोषणा   DVO_SRCDIM_HORIZONTAL_SHIFT	12
#घोषणा   DVO_SRCDIM_VERTICAL_SHIFT	0

/* LVDS port control */
#घोषणा LVDS			_MMIO(0x61180)
/*
 * Enables the LVDS port.  This bit must be set beक्रमe DPLLs are enabled, as
 * the DPLL semantics change when the LVDS is asचिन्हित to that pipe.
 */
#घोषणा   LVDS_PORT_EN			(1 << 31)
/* Selects pipe B क्रम LVDS data.  Must be set on pre-965. */
#घोषणा   LVDS_PIPE_SEL_SHIFT		30
#घोषणा   LVDS_PIPE_SEL_MASK		(1 << 30)
#घोषणा   LVDS_PIPE_SEL(pipe)		((pipe) << 30)
#घोषणा   LVDS_PIPE_SEL_SHIFT_CPT	29
#घोषणा   LVDS_PIPE_SEL_MASK_CPT	(3 << 29)
#घोषणा   LVDS_PIPE_SEL_CPT(pipe)	((pipe) << 29)
/* LVDS dithering flag on 965/g4x platक्रमm */
#घोषणा   LVDS_ENABLE_DITHER		(1 << 25)
/* LVDS sync polarity flags. Set to invert (i.e. negative) */
#घोषणा   LVDS_VSYNC_POLARITY		(1 << 21)
#घोषणा   LVDS_HSYNC_POLARITY		(1 << 20)

/* Enable border क्रम unscaled (or aspect-scaled) display */
#घोषणा   LVDS_BORDER_ENABLE		(1 << 15)
/*
 * Enables the A0-A2 data pairs and CLKA, containing 18 bits of color data per
 * pixel.
 */
#घोषणा   LVDS_A0A2_CLKA_POWER_MASK	(3 << 8)
#घोषणा   LVDS_A0A2_CLKA_POWER_DOWN	(0 << 8)
#घोषणा   LVDS_A0A2_CLKA_POWER_UP	(3 << 8)
/*
 * Controls the A3 data pair, which contains the additional LSBs क्रम 24 bit
 * mode.  Only enabled अगर LVDS_A0A2_CLKA_POWER_UP also indicates it should be
 * on.
 */
#घोषणा   LVDS_A3_POWER_MASK		(3 << 6)
#घोषणा   LVDS_A3_POWER_DOWN		(0 << 6)
#घोषणा   LVDS_A3_POWER_UP		(3 << 6)
/*
 * Controls the CLKB pair.  This should only be set when LVDS_B0B3_POWER_UP
 * is set.
 */
#घोषणा   LVDS_CLKB_POWER_MASK		(3 << 4)
#घोषणा   LVDS_CLKB_POWER_DOWN		(0 << 4)
#घोषणा   LVDS_CLKB_POWER_UP		(3 << 4)
/*
 * Controls the B0-B3 data pairs.  This must be set to match the DPLL p2
 * setting क्रम whether we are in dual-channel mode.  The B3 pair will
 * additionally only be घातered up when LVDS_A3_POWER_UP is set.
 */
#घोषणा   LVDS_B0B3_POWER_MASK		(3 << 2)
#घोषणा   LVDS_B0B3_POWER_DOWN		(0 << 2)
#घोषणा   LVDS_B0B3_POWER_UP		(3 << 2)

/* Video Data Island Packet control */
#घोषणा VIDEO_DIP_DATA		_MMIO(0x61178)
/* Read the description of VIDEO_DIP_DATA (beक्रमe Haswell) or VIDEO_DIP_ECC
 * (Haswell and newer) to see which VIDEO_DIP_DATA byte corresponds to each byte
 * of the infoframe काष्ठाure specअगरied by CEA-861. */
#घोषणा   VIDEO_DIP_DATA_SIZE	32
#घोषणा   VIDEO_DIP_GMP_DATA_SIZE	36
#घोषणा   VIDEO_DIP_VSC_DATA_SIZE	36
#घोषणा   VIDEO_DIP_PPS_DATA_SIZE	132
#घोषणा VIDEO_DIP_CTL		_MMIO(0x61170)
/* Pre HSW: */
#घोषणा   VIDEO_DIP_ENABLE		(1 << 31)
#घोषणा   VIDEO_DIP_PORT(port)		((port) << 29)
#घोषणा   VIDEO_DIP_PORT_MASK		(3 << 29)
#घोषणा   VIDEO_DIP_ENABLE_GCP		(1 << 25) /* ilk+ */
#घोषणा   VIDEO_DIP_ENABLE_AVI		(1 << 21)
#घोषणा   VIDEO_DIP_ENABLE_VENDOR	(2 << 21)
#घोषणा   VIDEO_DIP_ENABLE_GAMUT	(4 << 21) /* ilk+ */
#घोषणा   VIDEO_DIP_ENABLE_SPD		(8 << 21)
#घोषणा   VIDEO_DIP_SELECT_AVI		(0 << 19)
#घोषणा   VIDEO_DIP_SELECT_VENDOR	(1 << 19)
#घोषणा   VIDEO_DIP_SELECT_GAMUT	(2 << 19)
#घोषणा   VIDEO_DIP_SELECT_SPD		(3 << 19)
#घोषणा   VIDEO_DIP_SELECT_MASK		(3 << 19)
#घोषणा   VIDEO_DIP_FREQ_ONCE		(0 << 16)
#घोषणा   VIDEO_DIP_FREQ_VSYNC		(1 << 16)
#घोषणा   VIDEO_DIP_FREQ_2VSYNC		(2 << 16)
#घोषणा   VIDEO_DIP_FREQ_MASK		(3 << 16)
/* HSW and later: */
#घोषणा   VIDEO_DIP_ENABLE_DRM_GLK	(1 << 28)
#घोषणा   PSR_VSC_BIT_7_SET		(1 << 27)
#घोषणा   VSC_SELECT_MASK		(0x3 << 25)
#घोषणा   VSC_SELECT_SHIFT		25
#घोषणा   VSC_DIP_HW_HEA_DATA		(0 << 25)
#घोषणा   VSC_DIP_HW_HEA_SW_DATA	(1 << 25)
#घोषणा   VSC_DIP_HW_DATA_SW_HEA	(2 << 25)
#घोषणा   VSC_DIP_SW_HEA_DATA		(3 << 25)
#घोषणा   VDIP_ENABLE_PPS		(1 << 24)
#घोषणा   VIDEO_DIP_ENABLE_VSC_HSW	(1 << 20)
#घोषणा   VIDEO_DIP_ENABLE_GCP_HSW	(1 << 16)
#घोषणा   VIDEO_DIP_ENABLE_AVI_HSW	(1 << 12)
#घोषणा   VIDEO_DIP_ENABLE_VS_HSW	(1 << 8)
#घोषणा   VIDEO_DIP_ENABLE_GMP_HSW	(1 << 4)
#घोषणा   VIDEO_DIP_ENABLE_SPD_HSW	(1 << 0)

/* Panel घातer sequencing */
#घोषणा PPS_BASE			0x61200
#घोषणा VLV_PPS_BASE			(VLV_DISPLAY_BASE + PPS_BASE)
#घोषणा PCH_PPS_BASE			0xC7200

#घोषणा _MMIO_PPS(pps_idx, reg)		_MMIO(dev_priv->pps_mmio_base -	\
					      PPS_BASE + (reg) +	\
					      (pps_idx) * 0x100)

#घोषणा _PP_STATUS			0x61200
#घोषणा PP_STATUS(pps_idx)		_MMIO_PPS(pps_idx, _PP_STATUS)
#घोषणा   PP_ON				REG_BIT(31)
/*
 * Indicates that all dependencies of the panel are on:
 *
 * - PLL enabled
 * - pipe enabled
 * - LVDS/DVOB/DVOC on
 */
#घोषणा   PP_READY			REG_BIT(30)
#घोषणा   PP_SEQUENCE_MASK		REG_GENMASK(29, 28)
#घोषणा   PP_SEQUENCE_NONE		REG_FIELD_PREP(PP_SEQUENCE_MASK, 0)
#घोषणा   PP_SEQUENCE_POWER_UP		REG_FIELD_PREP(PP_SEQUENCE_MASK, 1)
#घोषणा   PP_SEQUENCE_POWER_DOWN	REG_FIELD_PREP(PP_SEQUENCE_MASK, 2)
#घोषणा   PP_CYCLE_DELAY_ACTIVE		REG_BIT(27)
#घोषणा   PP_SEQUENCE_STATE_MASK	REG_GENMASK(3, 0)
#घोषणा   PP_SEQUENCE_STATE_OFF_IDLE	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0x0)
#घोषणा   PP_SEQUENCE_STATE_OFF_S0_1	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0x1)
#घोषणा   PP_SEQUENCE_STATE_OFF_S0_2	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0x2)
#घोषणा   PP_SEQUENCE_STATE_OFF_S0_3	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0x3)
#घोषणा   PP_SEQUENCE_STATE_ON_IDLE	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0x8)
#घोषणा   PP_SEQUENCE_STATE_ON_S1_1	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0x9)
#घोषणा   PP_SEQUENCE_STATE_ON_S1_2	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0xa)
#घोषणा   PP_SEQUENCE_STATE_ON_S1_3	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0xb)
#घोषणा   PP_SEQUENCE_STATE_RESET	REG_FIELD_PREP(PP_SEQUENCE_STATE_MASK, 0xf)

#घोषणा _PP_CONTROL			0x61204
#घोषणा PP_CONTROL(pps_idx)		_MMIO_PPS(pps_idx, _PP_CONTROL)
#घोषणा  PANEL_UNLOCK_MASK		REG_GENMASK(31, 16)
#घोषणा  PANEL_UNLOCK_REGS		REG_FIELD_PREP(PANEL_UNLOCK_MASK, 0xabcd)
#घोषणा  BXT_POWER_CYCLE_DELAY_MASK	REG_GENMASK(8, 4)
#घोषणा  EDP_FORCE_VDD			REG_BIT(3)
#घोषणा  EDP_BLC_ENABLE			REG_BIT(2)
#घोषणा  PANEL_POWER_RESET		REG_BIT(1)
#घोषणा  PANEL_POWER_ON			REG_BIT(0)

#घोषणा _PP_ON_DELAYS			0x61208
#घोषणा PP_ON_DELAYS(pps_idx)		_MMIO_PPS(pps_idx, _PP_ON_DELAYS)
#घोषणा  PANEL_PORT_SELECT_MASK		REG_GENMASK(31, 30)
#घोषणा  PANEL_PORT_SELECT_LVDS		REG_FIELD_PREP(PANEL_PORT_SELECT_MASK, 0)
#घोषणा  PANEL_PORT_SELECT_DPA		REG_FIELD_PREP(PANEL_PORT_SELECT_MASK, 1)
#घोषणा  PANEL_PORT_SELECT_DPC		REG_FIELD_PREP(PANEL_PORT_SELECT_MASK, 2)
#घोषणा  PANEL_PORT_SELECT_DPD		REG_FIELD_PREP(PANEL_PORT_SELECT_MASK, 3)
#घोषणा  PANEL_PORT_SELECT_VLV(port)	REG_FIELD_PREP(PANEL_PORT_SELECT_MASK, port)
#घोषणा  PANEL_POWER_UP_DELAY_MASK	REG_GENMASK(28, 16)
#घोषणा  PANEL_LIGHT_ON_DELAY_MASK	REG_GENMASK(12, 0)

#घोषणा _PP_OFF_DELAYS			0x6120C
#घोषणा PP_OFF_DELAYS(pps_idx)		_MMIO_PPS(pps_idx, _PP_OFF_DELAYS)
#घोषणा  PANEL_POWER_DOWN_DELAY_MASK	REG_GENMASK(28, 16)
#घोषणा  PANEL_LIGHT_OFF_DELAY_MASK	REG_GENMASK(12, 0)

#घोषणा _PP_DIVISOR			0x61210
#घोषणा PP_DIVISOR(pps_idx)		_MMIO_PPS(pps_idx, _PP_DIVISOR)
#घोषणा  PP_REFERENCE_DIVIDER_MASK	REG_GENMASK(31, 8)
#घोषणा  PANEL_POWER_CYCLE_DELAY_MASK	REG_GENMASK(4, 0)

/* Panel fitting */
#घोषणा PFIT_CONTROL	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61230)
#घोषणा   PFIT_ENABLE		(1 << 31)
#घोषणा   PFIT_PIPE_MASK	(3 << 29)
#घोषणा   PFIT_PIPE_SHIFT	29
#घोषणा   PFIT_PIPE(pipe)	((pipe) << 29)
#घोषणा   VERT_INTERP_DISABLE	(0 << 10)
#घोषणा   VERT_INTERP_BILINEAR	(1 << 10)
#घोषणा   VERT_INTERP_MASK	(3 << 10)
#घोषणा   VERT_AUTO_SCALE	(1 << 9)
#घोषणा   HORIZ_INTERP_DISABLE	(0 << 6)
#घोषणा   HORIZ_INTERP_BILINEAR	(1 << 6)
#घोषणा   HORIZ_INTERP_MASK	(3 << 6)
#घोषणा   HORIZ_AUTO_SCALE	(1 << 5)
#घोषणा   PANEL_8TO6_DITHER_ENABLE (1 << 3)
#घोषणा   PFIT_FILTER_FUZZY	(0 << 24)
#घोषणा   PFIT_SCALING_AUTO	(0 << 26)
#घोषणा   PFIT_SCALING_PROGRAMMED (1 << 26)
#घोषणा   PFIT_SCALING_PILLAR	(2 << 26)
#घोषणा   PFIT_SCALING_LETTER	(3 << 26)
#घोषणा PFIT_PGM_RATIOS _MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61234)
/* Pre-965 */
#घोषणा		PFIT_VERT_SCALE_SHIFT		20
#घोषणा		PFIT_VERT_SCALE_MASK		0xfff00000
#घोषणा		PFIT_HORIZ_SCALE_SHIFT		4
#घोषणा		PFIT_HORIZ_SCALE_MASK		0x0000fff0
/* 965+ */
#घोषणा		PFIT_VERT_SCALE_SHIFT_965	16
#घोषणा		PFIT_VERT_SCALE_MASK_965	0x1fff0000
#घोषणा		PFIT_HORIZ_SCALE_SHIFT_965	0
#घोषणा		PFIT_HORIZ_SCALE_MASK_965	0x00001fff

#घोषणा PFIT_AUTO_RATIOS _MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61238)

#घोषणा _VLV_BLC_PWM_CTL2_A (DISPLAY_MMIO_BASE(dev_priv) + 0x61250)
#घोषणा _VLV_BLC_PWM_CTL2_B (DISPLAY_MMIO_BASE(dev_priv) + 0x61350)
#घोषणा VLV_BLC_PWM_CTL2(pipe) _MMIO_PIPE(pipe, _VLV_BLC_PWM_CTL2_A, \
					 _VLV_BLC_PWM_CTL2_B)

#घोषणा _VLV_BLC_PWM_CTL_A (DISPLAY_MMIO_BASE(dev_priv) + 0x61254)
#घोषणा _VLV_BLC_PWM_CTL_B (DISPLAY_MMIO_BASE(dev_priv) + 0x61354)
#घोषणा VLV_BLC_PWM_CTL(pipe) _MMIO_PIPE(pipe, _VLV_BLC_PWM_CTL_A, \
					_VLV_BLC_PWM_CTL_B)

#घोषणा _VLV_BLC_HIST_CTL_A (DISPLAY_MMIO_BASE(dev_priv) + 0x61260)
#घोषणा _VLV_BLC_HIST_CTL_B (DISPLAY_MMIO_BASE(dev_priv) + 0x61360)
#घोषणा VLV_BLC_HIST_CTL(pipe) _MMIO_PIPE(pipe, _VLV_BLC_HIST_CTL_A, \
					 _VLV_BLC_HIST_CTL_B)

/* Backlight control */
#घोषणा BLC_PWM_CTL2	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61250) /* 965+ only */
#घोषणा   BLM_PWM_ENABLE		(1 << 31)
#घोषणा   BLM_COMBINATION_MODE		(1 << 30) /* gen4 only */
#घोषणा   BLM_PIPE_SELECT		(1 << 29)
#घोषणा   BLM_PIPE_SELECT_IVB		(3 << 29)
#घोषणा   BLM_PIPE_A			(0 << 29)
#घोषणा   BLM_PIPE_B			(1 << 29)
#घोषणा   BLM_PIPE_C			(2 << 29) /* ivb + */
#घोषणा   BLM_TRANSCODER_A		BLM_PIPE_A /* hsw */
#घोषणा   BLM_TRANSCODER_B		BLM_PIPE_B
#घोषणा   BLM_TRANSCODER_C		BLM_PIPE_C
#घोषणा   BLM_TRANSCODER_EDP		(3 << 29)
#घोषणा   BLM_PIPE(pipe)		((pipe) << 29)
#घोषणा   BLM_POLARITY_I965		(1 << 28) /* gen4 only */
#घोषणा   BLM_PHASE_IN_INTERUPT_STATUS	(1 << 26)
#घोषणा   BLM_PHASE_IN_ENABLE		(1 << 25)
#घोषणा   BLM_PHASE_IN_INTERUPT_ENABL	(1 << 24)
#घोषणा   BLM_PHASE_IN_TIME_BASE_SHIFT	(16)
#घोषणा   BLM_PHASE_IN_TIME_BASE_MASK	(0xff << 16)
#घोषणा   BLM_PHASE_IN_COUNT_SHIFT	(8)
#घोषणा   BLM_PHASE_IN_COUNT_MASK	(0xff << 8)
#घोषणा   BLM_PHASE_IN_INCR_SHIFT	(0)
#घोषणा   BLM_PHASE_IN_INCR_MASK	(0xff << 0)
#घोषणा BLC_PWM_CTL	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61254)
/*
 * This is the most signअगरicant 15 bits of the number of backlight cycles in a
 * complete cycle of the modulated backlight control.
 *
 * The actual value is this field multiplied by two.
 */
#घोषणा   BACKLIGHT_MODULATION_FREQ_SHIFT	(17)
#घोषणा   BACKLIGHT_MODULATION_FREQ_MASK	(0x7fff << 17)
#घोषणा   BLM_LEGACY_MODE			(1 << 16) /* gen2 only */
/*
 * This is the number of cycles out of the backlight modulation cycle क्रम which
 * the backlight is on.
 *
 * This field must be no greater than the number of cycles in the complete
 * backlight modulation cycle.
 */
#घोषणा   BACKLIGHT_DUTY_CYCLE_SHIFT		(0)
#घोषणा   BACKLIGHT_DUTY_CYCLE_MASK		(0xffff)
#घोषणा   BACKLIGHT_DUTY_CYCLE_MASK_PNV		(0xfffe)
#घोषणा   BLM_POLARITY_PNV			(1 << 0) /* pnv only */

#घोषणा BLC_HIST_CTL	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x61260)
#घोषणा  BLM_HISTOGRAM_ENABLE			(1 << 31)

/* New रेजिस्टरs क्रम PCH-split platक्रमms. Safe where new bits show up, the
 * रेजिस्टर layout machtes with gen4 BLC_PWM_CTL[12]. */
#घोषणा BLC_PWM_CPU_CTL2	_MMIO(0x48250)
#घोषणा BLC_PWM_CPU_CTL		_MMIO(0x48254)

#घोषणा HSW_BLC_PWM2_CTL	_MMIO(0x48350)

/* PCH CTL1 is totally dअगरferent, all but the below bits are reserved. CTL2 is
 * like the normal CTL from gen4 and earlier. Hooray क्रम confusing naming. */
#घोषणा BLC_PWM_PCH_CTL1	_MMIO(0xc8250)
#घोषणा   BLM_PCH_PWM_ENABLE			(1 << 31)
#घोषणा   BLM_PCH_OVERRIDE_ENABLE		(1 << 30)
#घोषणा   BLM_PCH_POLARITY			(1 << 29)
#घोषणा BLC_PWM_PCH_CTL2	_MMIO(0xc8254)

#घोषणा UTIL_PIN_CTL			_MMIO(0x48400)
#घोषणा   UTIL_PIN_ENABLE		(1 << 31)
#घोषणा   UTIL_PIN_PIPE_MASK		(3 << 29)
#घोषणा   UTIL_PIN_PIPE(x)		((x) << 29)
#घोषणा   UTIL_PIN_MODE_MASK		(0xf << 24)
#घोषणा   UTIL_PIN_MODE_DATA		(0 << 24)
#घोषणा   UTIL_PIN_MODE_PWM		(1 << 24)
#घोषणा   UTIL_PIN_MODE_VBLANK		(4 << 24)
#घोषणा   UTIL_PIN_MODE_VSYNC		(5 << 24)
#घोषणा   UTIL_PIN_MODE_EYE_LEVEL	(8 << 24)
#घोषणा   UTIL_PIN_OUTPUT_DATA		(1 << 23)
#घोषणा   UTIL_PIN_POLARITY		(1 << 22)
#घोषणा   UTIL_PIN_सूचीECTION_INPUT	(1 << 19)
#घोषणा   UTIL_PIN_INPUT_DATA		(1 << 16)

/* BXT backlight रेजिस्टर definition. */
#घोषणा _BXT_BLC_PWM_CTL1			0xC8250
#घोषणा   BXT_BLC_PWM_ENABLE			(1 << 31)
#घोषणा   BXT_BLC_PWM_POLARITY			(1 << 29)
#घोषणा _BXT_BLC_PWM_FREQ1			0xC8254
#घोषणा _BXT_BLC_PWM_DUTY1			0xC8258

#घोषणा _BXT_BLC_PWM_CTL2			0xC8350
#घोषणा _BXT_BLC_PWM_FREQ2			0xC8354
#घोषणा _BXT_BLC_PWM_DUTY2			0xC8358

#घोषणा BXT_BLC_PWM_CTL(controller)    _MMIO_PIPE(controller,		\
					_BXT_BLC_PWM_CTL1, _BXT_BLC_PWM_CTL2)
#घोषणा BXT_BLC_PWM_FREQ(controller)   _MMIO_PIPE(controller, \
					_BXT_BLC_PWM_FREQ1, _BXT_BLC_PWM_FREQ2)
#घोषणा BXT_BLC_PWM_DUTY(controller)   _MMIO_PIPE(controller, \
					_BXT_BLC_PWM_DUTY1, _BXT_BLC_PWM_DUTY2)

#घोषणा PCH_GTC_CTL		_MMIO(0xe7000)
#घोषणा   PCH_GTC_ENABLE	(1 << 31)

/* TV port control */
#घोषणा TV_CTL			_MMIO(0x68000)
/* Enables the TV encoder */
# define TV_ENC_ENABLE			(1 << 31)
/* Sources the TV encoder input from pipe B instead of A. */
# define TV_ENC_PIPE_SEL_SHIFT		30
# define TV_ENC_PIPE_SEL_MASK		(1 << 30)
# define TV_ENC_PIPE_SEL(pipe)		((pipe) << 30)
/* Outमाला_दो composite video (DAC A only) */
# define TV_ENC_OUTPUT_COMPOSITE	(0 << 28)
/* Outमाला_दो SVideo video (DAC B/C) */
# define TV_ENC_OUTPUT_SVIDEO		(1 << 28)
/* Outमाला_दो Component video (DAC A/B/C) */
# define TV_ENC_OUTPUT_COMPONENT	(2 << 28)
/* Outमाला_दो Composite and SVideo (DAC A/B/C) */
# define TV_ENC_OUTPUT_SVIDEO_COMPOSITE	(3 << 28)
# define TV_TRILEVEL_SYNC		(1 << 21)
/* Enables slow sync generation (945GM only) */
# define TV_SLOW_SYNC			(1 << 20)
/* Selects 4x oversampling क्रम 480i and 576p */
# define TV_OVERSAMPLE_4X		(0 << 18)
/* Selects 2x oversampling क्रम 720p and 1080i */
# define TV_OVERSAMPLE_2X		(1 << 18)
/* Selects no oversampling क्रम 1080p */
# define TV_OVERSAMPLE_NONE		(2 << 18)
/* Selects 8x oversampling */
# define TV_OVERSAMPLE_8X		(3 << 18)
# define TV_OVERSAMPLE_MASK		(3 << 18)
/* Selects progressive mode rather than पूर्णांकerlaced */
# define TV_PROGRESSIVE			(1 << 17)
/* Sets the colorburst to PAL mode.  Required क्रम non-M PAL modes. */
# define TV_PAL_BURST			(1 << 16)
/* Field क्रम setting delay of Y compared to C */
# define TV_YC_SKEW_MASK		(7 << 12)
/* Enables a fix क्रम 480p/576p standard definition modes on the 915GM only */
# define TV_ENC_SDP_FIX			(1 << 11)
/*
 * Enables a fix क्रम the 915GM only.
 *
 * Not sure what it करोes.
 */
# define TV_ENC_C0_FIX			(1 << 10)
/* Bits that must be preserved by software */
# define TV_CTL_SAVE			((1 << 11) | (3 << 9) | (7 << 6) | 0xf)
# define TV_FUSE_STATE_MASK		(3 << 4)
/* Read-only state that reports all features enabled */
# define TV_FUSE_STATE_ENABLED		(0 << 4)
/* Read-only state that reports that Macrovision is disabled in hardware*/
# define TV_FUSE_STATE_NO_MACROVISION	(1 << 4)
/* Read-only state that reports that TV-out is disabled in hardware. */
# define TV_FUSE_STATE_DISABLED		(2 << 4)
/* Normal operation */
# define TV_TEST_MODE_NORMAL		(0 << 0)
/* Encoder test pattern 1 - combo pattern */
# define TV_TEST_MODE_PATTERN_1		(1 << 0)
/* Encoder test pattern 2 - full screen vertical 75% color bars */
# define TV_TEST_MODE_PATTERN_2		(2 << 0)
/* Encoder test pattern 3 - full screen horizontal 75% color bars */
# define TV_TEST_MODE_PATTERN_3		(3 << 0)
/* Encoder test pattern 4 - अक्रमom noise */
# define TV_TEST_MODE_PATTERN_4		(4 << 0)
/* Encoder test pattern 5 - linear color ramps */
# define TV_TEST_MODE_PATTERN_5		(5 << 0)
/*
 * This test mode क्रमces the DACs to 50% of full output.
 *
 * This is used क्रम load detection in combination with TVDAC_SENSE_MASK
 */
# define TV_TEST_MODE_MONITOR_DETECT	(7 << 0)
# define TV_TEST_MODE_MASK		(7 << 0)

#घोषणा TV_DAC			_MMIO(0x68004)
# define TV_DAC_SAVE		0x00ffff00
/*
 * Reports that DAC state change logic has reported change (RO).
 *
 * This माला_लो cleared when TV_DAC_STATE_EN is cleared
*/
# define TVDAC_STATE_CHG		(1 << 31)
# define TVDAC_SENSE_MASK		(7 << 28)
/* Reports that DAC A voltage is above the detect threshold */
# define TVDAC_A_SENSE			(1 << 30)
/* Reports that DAC B voltage is above the detect threshold */
# define TVDAC_B_SENSE			(1 << 29)
/* Reports that DAC C voltage is above the detect threshold */
# define TVDAC_C_SENSE			(1 << 28)
/*
 * Enables DAC state detection logic, क्रम load-based TV detection.
 *
 * The PLL of the chosen pipe (in TV_CTL) must be running, and the encoder set
 * to off, क्रम load detection to work.
 */
# define TVDAC_STATE_CHG_EN		(1 << 27)
/* Sets the DAC A sense value to high */
# define TVDAC_A_SENSE_CTL		(1 << 26)
/* Sets the DAC B sense value to high */
# define TVDAC_B_SENSE_CTL		(1 << 25)
/* Sets the DAC C sense value to high */
# define TVDAC_C_SENSE_CTL		(1 << 24)
/* Overrides the ENC_ENABLE and DAC voltage levels */
# define DAC_CTL_OVERRIDE		(1 << 7)
/* Sets the slew rate.  Must be preserved in software */
# define ENC_TVDAC_SLEW_FAST		(1 << 6)
# define DAC_A_1_3_V			(0 << 4)
# define DAC_A_1_1_V			(1 << 4)
# define DAC_A_0_7_V			(2 << 4)
# define DAC_A_MASK			(3 << 4)
# define DAC_B_1_3_V			(0 << 2)
# define DAC_B_1_1_V			(1 << 2)
# define DAC_B_0_7_V			(2 << 2)
# define DAC_B_MASK			(3 << 2)
# define DAC_C_1_3_V			(0 << 0)
# define DAC_C_1_1_V			(1 << 0)
# define DAC_C_0_7_V			(2 << 0)
# define DAC_C_MASK			(3 << 0)

/*
 * CSC coefficients are stored in a भग्नing poपूर्णांक क्रमmat with 9 bits of
 * mantissa and 2 or 3 bits of exponent.  The exponent is represented as 2**-n,
 * where 2-bit exponents are अचिन्हित n, and 3-bit exponents are चिन्हित n with
 * -1 (0x3) being the only legal negative value.
 */
#घोषणा TV_CSC_Y		_MMIO(0x68010)
# define TV_RY_MASK			0x07ff0000
# define TV_RY_SHIFT			16
# define TV_GY_MASK			0x00000fff
# define TV_GY_SHIFT			0

#घोषणा TV_CSC_Y2		_MMIO(0x68014)
# define TV_BY_MASK			0x07ff0000
# define TV_BY_SHIFT			16
/*
 * Y attenuation क्रम component video.
 *
 * Stored in 1.9 fixed poपूर्णांक.
 */
# define TV_AY_MASK			0x000003ff
# define TV_AY_SHIFT			0

#घोषणा TV_CSC_U		_MMIO(0x68018)
# define TV_RU_MASK			0x07ff0000
# define TV_RU_SHIFT			16
# define TV_GU_MASK			0x000007ff
# define TV_GU_SHIFT			0

#घोषणा TV_CSC_U2		_MMIO(0x6801c)
# define TV_BU_MASK			0x07ff0000
# define TV_BU_SHIFT			16
/*
 * U attenuation क्रम component video.
 *
 * Stored in 1.9 fixed poपूर्णांक.
 */
# define TV_AU_MASK			0x000003ff
# define TV_AU_SHIFT			0

#घोषणा TV_CSC_V		_MMIO(0x68020)
# define TV_RV_MASK			0x0fff0000
# define TV_RV_SHIFT			16
# define TV_GV_MASK			0x000007ff
# define TV_GV_SHIFT			0

#घोषणा TV_CSC_V2		_MMIO(0x68024)
# define TV_BV_MASK			0x07ff0000
# define TV_BV_SHIFT			16
/*
 * V attenuation क्रम component video.
 *
 * Stored in 1.9 fixed poपूर्णांक.
 */
# define TV_AV_MASK			0x000007ff
# define TV_AV_SHIFT			0

#घोषणा TV_CLR_KNOBS		_MMIO(0x68028)
/* 2s-complement brightness adjusपंचांगent */
# define TV_BRIGHTNESS_MASK		0xff000000
# define TV_BRIGHTNESS_SHIFT		24
/* Contrast adjusपंचांगent, as a 2.6 अचिन्हित भग्नing poपूर्णांक number */
# define TV_CONTRAST_MASK		0x00ff0000
# define TV_CONTRAST_SHIFT		16
/* Saturation adjusपंचांगent, as a 2.6 अचिन्हित भग्नing poपूर्णांक number */
# define TV_SATURATION_MASK		0x0000ff00
# define TV_SATURATION_SHIFT		8
/* Hue adjusपंचांगent, as an पूर्णांकeger phase angle in degrees */
# define TV_HUE_MASK			0x000000ff
# define TV_HUE_SHIFT			0

#घोषणा TV_CLR_LEVEL		_MMIO(0x6802c)
/* Controls the DAC level क्रम black */
# define TV_BLACK_LEVEL_MASK		0x01ff0000
# define TV_BLACK_LEVEL_SHIFT		16
/* Controls the DAC level क्रम blanking */
# define TV_BLANK_LEVEL_MASK		0x000001ff
# define TV_BLANK_LEVEL_SHIFT		0

#घोषणा TV_H_CTL_1		_MMIO(0x68030)
/* Number of pixels in the hsync. */
# define TV_HSYNC_END_MASK		0x1fff0000
# define TV_HSYNC_END_SHIFT		16
/* Total number of pixels minus one in the line (display and blanking). */
# define TV_HTOTAL_MASK			0x00001fff
# define TV_HTOTAL_SHIFT		0

#घोषणा TV_H_CTL_2		_MMIO(0x68034)
/* Enables the colorburst (needed क्रम non-component color) */
# define TV_BURST_ENA			(1 << 31)
/* Offset of the colorburst from the start of hsync, in pixels minus one. */
# define TV_HBURST_START_SHIFT		16
# define TV_HBURST_START_MASK		0x1fff0000
/* Length of the colorburst */
# define TV_HBURST_LEN_SHIFT		0
# define TV_HBURST_LEN_MASK		0x0001fff

#घोषणा TV_H_CTL_3		_MMIO(0x68038)
/* End of hblank, measured in pixels minus one from start of hsync */
# define TV_HBLANK_END_SHIFT		16
# define TV_HBLANK_END_MASK		0x1fff0000
/* Start of hblank, measured in pixels minus one from start of hsync */
# define TV_HBLANK_START_SHIFT		0
# define TV_HBLANK_START_MASK		0x0001fff

#घोषणा TV_V_CTL_1		_MMIO(0x6803c)
/* XXX */
# define TV_NBR_END_SHIFT		16
# define TV_NBR_END_MASK		0x07ff0000
/* XXX */
# define TV_VI_END_F1_SHIFT		8
# define TV_VI_END_F1_MASK		0x00003f00
/* XXX */
# define TV_VI_END_F2_SHIFT		0
# define TV_VI_END_F2_MASK		0x0000003f

#घोषणा TV_V_CTL_2		_MMIO(0x68040)
/* Length of vsync, in half lines */
# define TV_VSYNC_LEN_MASK		0x07ff0000
# define TV_VSYNC_LEN_SHIFT		16
/* Offset of the start of vsync in field 1, measured in one less than the
 * number of half lines.
 */
# define TV_VSYNC_START_F1_MASK		0x00007f00
# define TV_VSYNC_START_F1_SHIFT	8
/*
 * Offset of the start of vsync in field 2, measured in one less than the
 * number of half lines.
 */
# define TV_VSYNC_START_F2_MASK		0x0000007f
# define TV_VSYNC_START_F2_SHIFT	0

#घोषणा TV_V_CTL_3		_MMIO(0x68044)
/* Enables generation of the equalization संकेत */
# define TV_EQUAL_ENA			(1 << 31)
/* Length of vsync, in half lines */
# define TV_VEQ_LEN_MASK		0x007f0000
# define TV_VEQ_LEN_SHIFT		16
/* Offset of the start of equalization in field 1, measured in one less than
 * the number of half lines.
 */
# define TV_VEQ_START_F1_MASK		0x0007f00
# define TV_VEQ_START_F1_SHIFT		8
/*
 * Offset of the start of equalization in field 2, measured in one less than
 * the number of half lines.
 */
# define TV_VEQ_START_F2_MASK		0x000007f
# define TV_VEQ_START_F2_SHIFT		0

#घोषणा TV_V_CTL_4		_MMIO(0x68048)
/*
 * Offset to start of vertical colorburst, measured in one less than the
 * number of lines from vertical start.
 */
# define TV_VBURST_START_F1_MASK	0x003f0000
# define TV_VBURST_START_F1_SHIFT	16
/*
 * Offset to the end of vertical colorburst, measured in one less than the
 * number of lines from the start of NBR.
 */
# define TV_VBURST_END_F1_MASK		0x000000ff
# define TV_VBURST_END_F1_SHIFT		0

#घोषणा TV_V_CTL_5		_MMIO(0x6804c)
/*
 * Offset to start of vertical colorburst, measured in one less than the
 * number of lines from vertical start.
 */
# define TV_VBURST_START_F2_MASK	0x003f0000
# define TV_VBURST_START_F2_SHIFT	16
/*
 * Offset to the end of vertical colorburst, measured in one less than the
 * number of lines from the start of NBR.
 */
# define TV_VBURST_END_F2_MASK		0x000000ff
# define TV_VBURST_END_F2_SHIFT		0

#घोषणा TV_V_CTL_6		_MMIO(0x68050)
/*
 * Offset to start of vertical colorburst, measured in one less than the
 * number of lines from vertical start.
 */
# define TV_VBURST_START_F3_MASK	0x003f0000
# define TV_VBURST_START_F3_SHIFT	16
/*
 * Offset to the end of vertical colorburst, measured in one less than the
 * number of lines from the start of NBR.
 */
# define TV_VBURST_END_F3_MASK		0x000000ff
# define TV_VBURST_END_F3_SHIFT		0

#घोषणा TV_V_CTL_7		_MMIO(0x68054)
/*
 * Offset to start of vertical colorburst, measured in one less than the
 * number of lines from vertical start.
 */
# define TV_VBURST_START_F4_MASK	0x003f0000
# define TV_VBURST_START_F4_SHIFT	16
/*
 * Offset to the end of vertical colorburst, measured in one less than the
 * number of lines from the start of NBR.
 */
# define TV_VBURST_END_F4_MASK		0x000000ff
# define TV_VBURST_END_F4_SHIFT		0

#घोषणा TV_SC_CTL_1		_MMIO(0x68060)
/* Turns on the first subcarrier phase generation DDA */
# define TV_SC_DDA1_EN			(1 << 31)
/* Turns on the first subcarrier phase generation DDA */
# define TV_SC_DDA2_EN			(1 << 30)
/* Turns on the first subcarrier phase generation DDA */
# define TV_SC_DDA3_EN			(1 << 29)
/* Sets the subcarrier DDA to reset frequency every other field */
# define TV_SC_RESET_EVERY_2		(0 << 24)
/* Sets the subcarrier DDA to reset frequency every fourth field */
# define TV_SC_RESET_EVERY_4		(1 << 24)
/* Sets the subcarrier DDA to reset frequency every eighth field */
# define TV_SC_RESET_EVERY_8		(2 << 24)
/* Sets the subcarrier DDA to never reset the frequency */
# define TV_SC_RESET_NEVER		(3 << 24)
/* Sets the peak amplitude of the colorburst.*/
# define TV_BURST_LEVEL_MASK		0x00ff0000
# define TV_BURST_LEVEL_SHIFT		16
/* Sets the increment of the first subcarrier phase generation DDA */
# define TV_SCDDA1_INC_MASK		0x00000fff
# define TV_SCDDA1_INC_SHIFT		0

#घोषणा TV_SC_CTL_2		_MMIO(0x68064)
/* Sets the rollover क्रम the second subcarrier phase generation DDA */
# define TV_SCDDA2_SIZE_MASK		0x7fff0000
# define TV_SCDDA2_SIZE_SHIFT		16
/* Sets the increent of the second subcarrier phase generation DDA */
# define TV_SCDDA2_INC_MASK		0x00007fff
# define TV_SCDDA2_INC_SHIFT		0

#घोषणा TV_SC_CTL_3		_MMIO(0x68068)
/* Sets the rollover क्रम the third subcarrier phase generation DDA */
# define TV_SCDDA3_SIZE_MASK		0x7fff0000
# define TV_SCDDA3_SIZE_SHIFT		16
/* Sets the increent of the third subcarrier phase generation DDA */
# define TV_SCDDA3_INC_MASK		0x00007fff
# define TV_SCDDA3_INC_SHIFT		0

#घोषणा TV_WIN_POS		_MMIO(0x68070)
/* X coordinate of the display from the start of horizontal active */
# define TV_XPOS_MASK			0x1fff0000
# define TV_XPOS_SHIFT			16
/* Y coordinate of the display from the start of vertical active (NBR) */
# define TV_YPOS_MASK			0x00000fff
# define TV_YPOS_SHIFT			0

#घोषणा TV_WIN_SIZE		_MMIO(0x68074)
/* Horizontal size of the display winकरोw, measured in pixels*/
# define TV_XSIZE_MASK			0x1fff0000
# define TV_XSIZE_SHIFT			16
/*
 * Vertical size of the display winकरोw, measured in pixels.
 *
 * Must be even क्रम पूर्णांकerlaced modes.
 */
# define TV_YSIZE_MASK			0x00000fff
# define TV_YSIZE_SHIFT			0

#घोषणा TV_FILTER_CTL_1		_MMIO(0x68080)
/*
 * Enables स्वतःmatic scaling calculation.
 *
 * If set, the rest of the रेजिस्टरs are ignored, and the calculated values can
 * be पढ़ो back from the रेजिस्टर.
 */
# define TV_AUTO_SCALE			(1 << 31)
/*
 * Disables the vertical filter.
 *
 * This is required on modes more than 1024 pixels wide */
# define TV_V_FILTER_BYPASS		(1 << 29)
/* Enables adaptive vertical filtering */
# define TV_VADAPT			(1 << 28)
# define TV_VADAPT_MODE_MASK		(3 << 26)
/* Selects the least adaptive vertical filtering mode */
# define TV_VADAPT_MODE_LEAST		(0 << 26)
/* Selects the moderately adaptive vertical filtering mode */
# define TV_VADAPT_MODE_MODERATE	(1 << 26)
/* Selects the most adaptive vertical filtering mode */
# define TV_VADAPT_MODE_MOST		(3 << 26)
/*
 * Sets the horizontal scaling factor.
 *
 * This should be the fractional part of the horizontal scaling factor भागided
 * by the oversampling rate.  TV_HSCALE should be less than 1, and set to:
 *
 * (src width - 1) / ((oversample * dest width) - 1)
 */
# define TV_HSCALE_FRAC_MASK		0x00003fff
# define TV_HSCALE_FRAC_SHIFT		0

#घोषणा TV_FILTER_CTL_2		_MMIO(0x68084)
/*
 * Sets the पूर्णांकeger part of the 3.15 fixed-poपूर्णांक vertical scaling factor.
 *
 * TV_VSCALE should be (src height - 1) / ((पूर्णांकerlace * dest height) - 1)
 */
# define TV_VSCALE_INT_MASK		0x00038000
# define TV_VSCALE_INT_SHIFT		15
/*
 * Sets the fractional part of the 3.15 fixed-poपूर्णांक vertical scaling factor.
 *
 * \sa TV_VSCALE_INT_MASK
 */
# define TV_VSCALE_FRAC_MASK		0x00007fff
# define TV_VSCALE_FRAC_SHIFT		0

#घोषणा TV_FILTER_CTL_3		_MMIO(0x68088)
/*
 * Sets the पूर्णांकeger part of the 3.15 fixed-poपूर्णांक vertical scaling factor.
 *
 * TV_VSCALE should be (src height - 1) / (1/4 * (dest height - 1))
 *
 * For progressive modes, TV_VSCALE_IP_INT should be set to zeroes.
 */
# define TV_VSCALE_IP_INT_MASK		0x00038000
# define TV_VSCALE_IP_INT_SHIFT		15
/*
 * Sets the fractional part of the 3.15 fixed-poपूर्णांक vertical scaling factor.
 *
 * For progressive modes, TV_VSCALE_IP_INT should be set to zeroes.
 *
 * \sa TV_VSCALE_IP_INT_MASK
 */
# define TV_VSCALE_IP_FRAC_MASK		0x00007fff
# define TV_VSCALE_IP_FRAC_SHIFT		0

#घोषणा TV_CC_CONTROL		_MMIO(0x68090)
# define TV_CC_ENABLE			(1 << 31)
/*
 * Specअगरies which field to send the CC data in.
 *
 * CC data is usually sent in field 0.
 */
# define TV_CC_FID_MASK			(1 << 27)
# define TV_CC_FID_SHIFT		27
/* Sets the horizontal position of the CC data.  Usually 135. */
# define TV_CC_HOFF_MASK		0x03ff0000
# define TV_CC_HOFF_SHIFT		16
/* Sets the vertical position of the CC data.  Usually 21 */
# define TV_CC_LINE_MASK		0x0000003f
# define TV_CC_LINE_SHIFT		0

#घोषणा TV_CC_DATA		_MMIO(0x68094)
# define TV_CC_RDY			(1 << 31)
/* Second word of CC data to be transmitted. */
# define TV_CC_DATA_2_MASK		0x007f0000
# define TV_CC_DATA_2_SHIFT		16
/* First word of CC data to be transmitted. */
# define TV_CC_DATA_1_MASK		0x0000007f
# define TV_CC_DATA_1_SHIFT		0

#घोषणा TV_H_LUMA(i)		_MMIO(0x68100 + (i) * 4) /* 60 रेजिस्टरs */
#घोषणा TV_H_CHROMA(i)		_MMIO(0x68200 + (i) * 4) /* 60 रेजिस्टरs */
#घोषणा TV_V_LUMA(i)		_MMIO(0x68300 + (i) * 4) /* 43 रेजिस्टरs */
#घोषणा TV_V_CHROMA(i)		_MMIO(0x68400 + (i) * 4) /* 43 रेजिस्टरs */

/* Display Port */
#घोषणा DP_A			_MMIO(0x64000) /* eDP */
#घोषणा DP_B			_MMIO(0x64100)
#घोषणा DP_C			_MMIO(0x64200)
#घोषणा DP_D			_MMIO(0x64300)

#घोषणा VLV_DP_B		_MMIO(VLV_DISPLAY_BASE + 0x64100)
#घोषणा VLV_DP_C		_MMIO(VLV_DISPLAY_BASE + 0x64200)
#घोषणा CHV_DP_D		_MMIO(VLV_DISPLAY_BASE + 0x64300)

#घोषणा   DP_PORT_EN			(1 << 31)
#घोषणा   DP_PIPE_SEL_SHIFT		30
#घोषणा   DP_PIPE_SEL_MASK		(1 << 30)
#घोषणा   DP_PIPE_SEL(pipe)		((pipe) << 30)
#घोषणा   DP_PIPE_SEL_SHIFT_IVB		29
#घोषणा   DP_PIPE_SEL_MASK_IVB		(3 << 29)
#घोषणा   DP_PIPE_SEL_IVB(pipe)		((pipe) << 29)
#घोषणा   DP_PIPE_SEL_SHIFT_CHV		16
#घोषणा   DP_PIPE_SEL_MASK_CHV		(3 << 16)
#घोषणा   DP_PIPE_SEL_CHV(pipe)		((pipe) << 16)

/* Link training mode - select a suitable mode क्रम each stage */
#घोषणा   DP_LINK_TRAIN_PAT_1		(0 << 28)
#घोषणा   DP_LINK_TRAIN_PAT_2		(1 << 28)
#घोषणा   DP_LINK_TRAIN_PAT_IDLE	(2 << 28)
#घोषणा   DP_LINK_TRAIN_OFF		(3 << 28)
#घोषणा   DP_LINK_TRAIN_MASK		(3 << 28)
#घोषणा   DP_LINK_TRAIN_SHIFT		28

/* CPT Link training mode */
#घोषणा   DP_LINK_TRAIN_PAT_1_CPT	(0 << 8)
#घोषणा   DP_LINK_TRAIN_PAT_2_CPT	(1 << 8)
#घोषणा   DP_LINK_TRAIN_PAT_IDLE_CPT	(2 << 8)
#घोषणा   DP_LINK_TRAIN_OFF_CPT		(3 << 8)
#घोषणा   DP_LINK_TRAIN_MASK_CPT	(7 << 8)
#घोषणा   DP_LINK_TRAIN_SHIFT_CPT	8

/* Signal voltages. These are mostly controlled by the other end */
#घोषणा   DP_VOLTAGE_0_4		(0 << 25)
#घोषणा   DP_VOLTAGE_0_6		(1 << 25)
#घोषणा   DP_VOLTAGE_0_8		(2 << 25)
#घोषणा   DP_VOLTAGE_1_2		(3 << 25)
#घोषणा   DP_VOLTAGE_MASK		(7 << 25)
#घोषणा   DP_VOLTAGE_SHIFT		25

/* Signal pre-emphasis levels, like voltages, the other end tells us what
 * they want
 */
#घोषणा   DP_PRE_EMPHASIS_0		(0 << 22)
#घोषणा   DP_PRE_EMPHASIS_3_5		(1 << 22)
#घोषणा   DP_PRE_EMPHASIS_6		(2 << 22)
#घोषणा   DP_PRE_EMPHASIS_9_5		(3 << 22)
#घोषणा   DP_PRE_EMPHASIS_MASK		(7 << 22)
#घोषणा   DP_PRE_EMPHASIS_SHIFT		22

/* How many wires to use. I guess 3 was too hard */
#घोषणा   DP_PORT_WIDTH(width)		(((width) - 1) << 19)
#घोषणा   DP_PORT_WIDTH_MASK		(7 << 19)
#घोषणा   DP_PORT_WIDTH_SHIFT		19

/* Mystic DPCD version 1.1 special mode */
#घोषणा   DP_ENHANCED_FRAMING		(1 << 18)

/* eDP */
#घोषणा   DP_PLL_FREQ_270MHZ		(0 << 16)
#घोषणा   DP_PLL_FREQ_162MHZ		(1 << 16)
#घोषणा   DP_PLL_FREQ_MASK		(3 << 16)

/* locked once port is enabled */
#घोषणा   DP_PORT_REVERSAL		(1 << 15)

/* eDP */
#घोषणा   DP_PLL_ENABLE			(1 << 14)

/* sends the घड़ी on lane 15 of the PEG क्रम debug */
#घोषणा   DP_CLOCK_OUTPUT_ENABLE	(1 << 13)

#घोषणा   DP_SCRAMBLING_DISABLE		(1 << 12)
#घोषणा   DP_SCRAMBLING_DISABLE_IRONLAKE	(1 << 7)

/* limit RGB values to aव्योम confusing TVs */
#घोषणा   DP_COLOR_RANGE_16_235		(1 << 8)

/* Turn on the audio link */
#घोषणा   DP_AUDIO_OUTPUT_ENABLE	(1 << 6)

/* vs and hs sync polarity */
#घोषणा   DP_SYNC_VS_HIGH		(1 << 4)
#घोषणा   DP_SYNC_HS_HIGH		(1 << 3)

/* A fantasy */
#घोषणा   DP_DETECTED			(1 << 2)

/* The aux channel provides a way to talk to the
 * संकेत sink क्रम DDC etc. Max packet size supported
 * is 20 bytes in each direction, hence the 5 fixed
 * data रेजिस्टरs
 */
#घोषणा _DPA_AUX_CH_CTL		(DISPLAY_MMIO_BASE(dev_priv) + 0x64010)
#घोषणा _DPA_AUX_CH_DATA1	(DISPLAY_MMIO_BASE(dev_priv) + 0x64014)

#घोषणा _DPB_AUX_CH_CTL		(DISPLAY_MMIO_BASE(dev_priv) + 0x64110)
#घोषणा _DPB_AUX_CH_DATA1	(DISPLAY_MMIO_BASE(dev_priv) + 0x64114)

#घोषणा DP_AUX_CH_CTL(aux_ch)	_MMIO_PORT(aux_ch, _DPA_AUX_CH_CTL, _DPB_AUX_CH_CTL)
#घोषणा DP_AUX_CH_DATA(aux_ch, i)	_MMIO(_PORT(aux_ch, _DPA_AUX_CH_DATA1, _DPB_AUX_CH_DATA1) + (i) * 4) /* 5 रेजिस्टरs */

#घोषणा   DP_AUX_CH_CTL_SEND_BUSY	    (1 << 31)
#घोषणा   DP_AUX_CH_CTL_DONE		    (1 << 30)
#घोषणा   DP_AUX_CH_CTL_INTERRUPT	    (1 << 29)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_ERROR	    (1 << 28)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_400us	    (0 << 26)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_600us	    (1 << 26)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_800us	    (2 << 26)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_MAX	    (3 << 26) /* Varies per platक्रमm */
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_MASK	    (3 << 26)
#घोषणा   DP_AUX_CH_CTL_RECEIVE_ERROR	    (1 << 25)
#घोषणा   DP_AUX_CH_CTL_MESSAGE_SIZE_MASK    (0x1f << 20)
#घोषणा   DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT   20
#घोषणा   DP_AUX_CH_CTL_PRECHARGE_2US_MASK   (0xf << 16)
#घोषणा   DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT  16
#घोषणा   DP_AUX_CH_CTL_AUX_AKSV_SELECT	    (1 << 15)
#घोषणा   DP_AUX_CH_CTL_MANCHESTER_TEST	    (1 << 14)
#घोषणा   DP_AUX_CH_CTL_SYNC_TEST	    (1 << 13)
#घोषणा   DP_AUX_CH_CTL_DEGLITCH_TEST	    (1 << 12)
#घोषणा   DP_AUX_CH_CTL_PRECHARGE_TEST	    (1 << 11)
#घोषणा   DP_AUX_CH_CTL_BIT_CLOCK_2X_MASK    (0x7ff)
#घोषणा   DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT   0
#घोषणा   DP_AUX_CH_CTL_PSR_DATA_AUX_REG_SKL	(1 << 14)
#घोषणा   DP_AUX_CH_CTL_FS_DATA_AUX_REG_SKL	(1 << 13)
#घोषणा   DP_AUX_CH_CTL_GTC_DATA_AUX_REG_SKL	(1 << 12)
#घोषणा   DP_AUX_CH_CTL_TBT_IO			(1 << 11)
#घोषणा   DP_AUX_CH_CTL_FW_SYNC_PULSE_SKL_MASK (0x1f << 5)
#घोषणा   DP_AUX_CH_CTL_FW_SYNC_PULSE_SKL(c) (((c) - 1) << 5)
#घोषणा   DP_AUX_CH_CTL_SYNC_PULSE_SKL(c)   ((c) - 1)

/*
 * Computing GMCH M and N values क्रम the Display Port link
 *
 * GMCH M/N = करोt घड़ी * bytes per pixel / ls_clk * # of lanes
 *
 * ls_clk (we assume) is the DP link घड़ी (1.62 or 2.7 GHz)
 *
 * The GMCH value is used पूर्णांकernally
 *
 * bytes_per_pixel is the number of bytes coming out of the plane,
 * which is after the LUTs, so we want the bytes क्रम our color क्रमmat.
 * For our current usage, this is always 3, one byte क्रम R, G and B.
 */
#घोषणा _PIPEA_DATA_M_G4X	0x70050
#घोषणा _PIPEB_DATA_M_G4X	0x71050

/* Transfer unit size क्रम display port - 1, शेष is 0x3f (क्रम TU size 64) */
#घोषणा  TU_SIZE(x)             (((x) - 1) << 25) /* शेष size 64 */
#घोषणा  TU_SIZE_SHIFT		25
#घोषणा  TU_SIZE_MASK           (0x3f << 25)

#घोषणा  DATA_LINK_M_N_MASK	(0xffffff)
#घोषणा  DATA_LINK_N_MAX	(0x800000)

#घोषणा _PIPEA_DATA_N_G4X	0x70054
#घोषणा _PIPEB_DATA_N_G4X	0x71054
#घोषणा   PIPE_GMCH_DATA_N_MASK			(0xffffff)

/*
 * Computing Link M and N values क्रम the Display Port link
 *
 * Link M / N = pixel_घड़ी / ls_clk
 *
 * (the DP spec calls pixel_घड़ी the 'strm_clk')
 *
 * The Link value is transmitted in the Main Stream
 * Attributes and VB-ID.
 */

#घोषणा _PIPEA_LINK_M_G4X	0x70060
#घोषणा _PIPEB_LINK_M_G4X	0x71060
#घोषणा   PIPEA_DP_LINK_M_MASK			(0xffffff)

#घोषणा _PIPEA_LINK_N_G4X	0x70064
#घोषणा _PIPEB_LINK_N_G4X	0x71064
#घोषणा   PIPEA_DP_LINK_N_MASK			(0xffffff)

#घोषणा PIPE_DATA_M_G4X(pipe) _MMIO_PIPE(pipe, _PIPEA_DATA_M_G4X, _PIPEB_DATA_M_G4X)
#घोषणा PIPE_DATA_N_G4X(pipe) _MMIO_PIPE(pipe, _PIPEA_DATA_N_G4X, _PIPEB_DATA_N_G4X)
#घोषणा PIPE_LINK_M_G4X(pipe) _MMIO_PIPE(pipe, _PIPEA_LINK_M_G4X, _PIPEB_LINK_M_G4X)
#घोषणा PIPE_LINK_N_G4X(pipe) _MMIO_PIPE(pipe, _PIPEA_LINK_N_G4X, _PIPEB_LINK_N_G4X)

/* Display & cursor control */

/* Pipe A */
#घोषणा _PIPEADSL		0x70000
#घोषणा   DSL_LINEMASK_GEN2	0x00000fff
#घोषणा   DSL_LINEMASK_GEN3	0x00001fff
#घोषणा _PIPEACONF		0x70008
#घोषणा   PIPECONF_ENABLE	(1 << 31)
#घोषणा   PIPECONF_DISABLE	0
#घोषणा   PIPECONF_DOUBLE_WIDE	(1 << 30)
#घोषणा   I965_PIPECONF_ACTIVE	(1 << 30)
#घोषणा   PIPECONF_DSI_PLL_LOCKED	(1 << 29) /* vlv & pipe A only */
#घोषणा   PIPECONF_FRAME_START_DELAY_MASK	(3 << 27) /* pre-hsw */
#घोषणा   PIPECONF_FRAME_START_DELAY(x)		((x) << 27) /* pre-hsw: 0-3 */
#घोषणा   PIPECONF_SINGLE_WIDE	0
#घोषणा   PIPECONF_PIPE_UNLOCKED 0
#घोषणा   PIPECONF_PIPE_LOCKED	(1 << 25)
#घोषणा   PIPECONF_FORCE_BORDER	(1 << 25)
#घोषणा   PIPECONF_GAMMA_MODE_MASK_I9XX	(1 << 24) /* gmch */
#घोषणा   PIPECONF_GAMMA_MODE_MASK_ILK	(3 << 24) /* ilk-ivb */
#घोषणा   PIPECONF_GAMMA_MODE_8BIT	(0 << 24) /* gmch,ilk-ivb */
#घोषणा   PIPECONF_GAMMA_MODE_10BIT	(1 << 24) /* gmch,ilk-ivb */
#घोषणा   PIPECONF_GAMMA_MODE_12BIT	(2 << 24) /* ilk-ivb */
#घोषणा   PIPECONF_GAMMA_MODE_SPLIT	(3 << 24) /* ivb */
#घोषणा   PIPECONF_GAMMA_MODE(x)	((x) << 24) /* pass in GAMMA_MODE_MODE_* */
#घोषणा   PIPECONF_GAMMA_MODE_SHIFT	24
#घोषणा   PIPECONF_INTERLACE_MASK	(7 << 21)
#घोषणा   PIPECONF_INTERLACE_MASK_HSW	(3 << 21)
/* Note that pre-gen3 करोes not support पूर्णांकerlaced display directly. Panel
 * fitting must be disabled on pre-ilk क्रम पूर्णांकerlaced. */
#घोषणा   PIPECONF_PROGRESSIVE			(0 << 21)
#घोषणा   PIPECONF_INTERLACE_W_SYNC_SHIFT_PANEL	(4 << 21) /* gen4 only */
#घोषणा   PIPECONF_INTERLACE_W_SYNC_SHIFT	(5 << 21) /* gen4 only */
#घोषणा   PIPECONF_INTERLACE_W_FIELD_INDICATION	(6 << 21)
#घोषणा   PIPECONF_INTERLACE_FIELD_0_ONLY	(7 << 21) /* gen3 only */
/* Ironlake and later have a complete new set of values क्रम पूर्णांकerlaced. PFIT
 * means panel fitter required, PF means progressive fetch, DBL means घातer
 * saving pixel करोubling. */
#घोषणा   PIPECONF_PFIT_PF_INTERLACED_ILK	(1 << 21)
#घोषणा   PIPECONF_INTERLACED_ILK		(3 << 21)
#घोषणा   PIPECONF_INTERLACED_DBL_ILK		(4 << 21) /* ilk/snb only */
#घोषणा   PIPECONF_PFIT_PF_INTERLACED_DBL_ILK	(5 << 21) /* ilk/snb only */
#घोषणा   PIPECONF_INTERLACE_MODE_MASK		(7 << 21)
#घोषणा   PIPECONF_EDP_RR_MODE_SWITCH		(1 << 20)
#घोषणा   PIPECONF_CXSR_DOWNCLOCK	(1 << 16)
#घोषणा   PIPECONF_EDP_RR_MODE_SWITCH_VLV	(1 << 14)
#घोषणा   PIPECONF_COLOR_RANGE_SELECT	(1 << 13)
#घोषणा   PIPECONF_OUTPUT_COLORSPACE_MASK	(3 << 11) /* ilk-ivb */
#घोषणा   PIPECONF_OUTPUT_COLORSPACE_RGB	(0 << 11) /* ilk-ivb */
#घोषणा   PIPECONF_OUTPUT_COLORSPACE_YUV601	(1 << 11) /* ilk-ivb */
#घोषणा   PIPECONF_OUTPUT_COLORSPACE_YUV709	(2 << 11) /* ilk-ivb */
#घोषणा   PIPECONF_OUTPUT_COLORSPACE_YUV_HSW	(1 << 11) /* hsw only */
#घोषणा   PIPECONF_BPC_MASK	(0x7 << 5)
#घोषणा   PIPECONF_8BPC		(0 << 5)
#घोषणा   PIPECONF_10BPC	(1 << 5)
#घोषणा   PIPECONF_6BPC		(2 << 5)
#घोषणा   PIPECONF_12BPC	(3 << 5)
#घोषणा   PIPECONF_DITHER_EN	(1 << 4)
#घोषणा   PIPECONF_DITHER_TYPE_MASK (0x0000000c)
#घोषणा   PIPECONF_DITHER_TYPE_SP (0 << 2)
#घोषणा   PIPECONF_DITHER_TYPE_ST1 (1 << 2)
#घोषणा   PIPECONF_DITHER_TYPE_ST2 (2 << 2)
#घोषणा   PIPECONF_DITHER_TYPE_TEMP (3 << 2)
#घोषणा _PIPEASTAT		0x70024
#घोषणा   PIPE_FIFO_UNDERRUN_STATUS		(1UL << 31)
#घोषणा   SPRITE1_FLIP_DONE_INT_EN_VLV		(1UL << 30)
#घोषणा   PIPE_CRC_ERROR_ENABLE			(1UL << 29)
#घोषणा   PIPE_CRC_DONE_ENABLE			(1UL << 28)
#घोषणा   PERF_COUNTER2_INTERRUPT_EN		(1UL << 27)
#घोषणा   PIPE_GMBUS_EVENT_ENABLE		(1UL << 27)
#घोषणा   PLANE_FLIP_DONE_INT_EN_VLV		(1UL << 26)
#घोषणा   PIPE_HOTPLUG_INTERRUPT_ENABLE		(1UL << 26)
#घोषणा   PIPE_VSYNC_INTERRUPT_ENABLE		(1UL << 25)
#घोषणा   PIPE_DISPLAY_LINE_COMPARE_ENABLE	(1UL << 24)
#घोषणा   PIPE_DPST_EVENT_ENABLE		(1UL << 23)
#घोषणा   SPRITE0_FLIP_DONE_INT_EN_VLV		(1UL << 22)
#घोषणा   PIPE_LEGACY_BLC_EVENT_ENABLE		(1UL << 22)
#घोषणा   PIPE_ODD_FIELD_INTERRUPT_ENABLE	(1UL << 21)
#घोषणा   PIPE_EVEN_FIELD_INTERRUPT_ENABLE	(1UL << 20)
#घोषणा   PIPE_B_PSR_INTERRUPT_ENABLE_VLV	(1UL << 19)
#घोषणा   PERF_COUNTER_INTERRUPT_EN		(1UL << 19)
#घोषणा   PIPE_HOTPLUG_TV_INTERRUPT_ENABLE	(1UL << 18) /* pre-965 */
#घोषणा   PIPE_START_VBLANK_INTERRUPT_ENABLE	(1UL << 18) /* 965 or later */
#घोषणा   PIPE_FRAMESTART_INTERRUPT_ENABLE	(1UL << 17)
#घोषणा   PIPE_VBLANK_INTERRUPT_ENABLE		(1UL << 17)
#घोषणा   PIPEA_HBLANK_INT_EN_VLV		(1UL << 16)
#घोषणा   PIPE_OVERLAY_UPDATED_ENABLE		(1UL << 16)
#घोषणा   SPRITE1_FLIP_DONE_INT_STATUS_VLV	(1UL << 15)
#घोषणा   SPRITE0_FLIP_DONE_INT_STATUS_VLV	(1UL << 14)
#घोषणा   PIPE_CRC_ERROR_INTERRUPT_STATUS	(1UL << 13)
#घोषणा   PIPE_CRC_DONE_INTERRUPT_STATUS	(1UL << 12)
#घोषणा   PERF_COUNTER2_INTERRUPT_STATUS	(1UL << 11)
#घोषणा   PIPE_GMBUS_INTERRUPT_STATUS		(1UL << 11)
#घोषणा   PLANE_FLIP_DONE_INT_STATUS_VLV	(1UL << 10)
#घोषणा   PIPE_HOTPLUG_INTERRUPT_STATUS		(1UL << 10)
#घोषणा   PIPE_VSYNC_INTERRUPT_STATUS		(1UL << 9)
#घोषणा   PIPE_DISPLAY_LINE_COMPARE_STATUS	(1UL << 8)
#घोषणा   PIPE_DPST_EVENT_STATUS		(1UL << 7)
#घोषणा   PIPE_A_PSR_STATUS_VLV			(1UL << 6)
#घोषणा   PIPE_LEGACY_BLC_EVENT_STATUS		(1UL << 6)
#घोषणा   PIPE_ODD_FIELD_INTERRUPT_STATUS	(1UL << 5)
#घोषणा   PIPE_EVEN_FIELD_INTERRUPT_STATUS	(1UL << 4)
#घोषणा   PIPE_B_PSR_STATUS_VLV			(1UL << 3)
#घोषणा   PERF_COUNTER_INTERRUPT_STATUS		(1UL << 3)
#घोषणा   PIPE_HOTPLUG_TV_INTERRUPT_STATUS	(1UL << 2) /* pre-965 */
#घोषणा   PIPE_START_VBLANK_INTERRUPT_STATUS	(1UL << 2) /* 965 or later */
#घोषणा   PIPE_FRAMESTART_INTERRUPT_STATUS	(1UL << 1)
#घोषणा   PIPE_VBLANK_INTERRUPT_STATUS		(1UL << 1)
#घोषणा   PIPE_HBLANK_INT_STATUS		(1UL << 0)
#घोषणा   PIPE_OVERLAY_UPDATED_STATUS		(1UL << 0)

#घोषणा PIPESTAT_INT_ENABLE_MASK		0x7fff0000
#घोषणा PIPESTAT_INT_STATUS_MASK		0x0000ffff

#घोषणा PIPE_A_OFFSET		0x70000
#घोषणा PIPE_B_OFFSET		0x71000
#घोषणा PIPE_C_OFFSET		0x72000
#घोषणा PIPE_D_OFFSET		0x73000
#घोषणा CHV_PIPE_C_OFFSET	0x74000
/*
 * There's actually no pipe EDP. Some pipe रेजिस्टरs have
 * simply shअगरted from the pipe to the transcoder, जबतक
 * keeping their original offset. Thus we need PIPE_EDP_OFFSET
 * to access such रेजिस्टरs in transcoder EDP.
 */
#घोषणा PIPE_EDP_OFFSET	0x7f000

/* ICL DSI 0 and 1 */
#घोषणा PIPE_DSI0_OFFSET	0x7b000
#घोषणा PIPE_DSI1_OFFSET	0x7b800

#घोषणा PIPECONF(pipe)		_MMIO_PIPE2(pipe, _PIPEACONF)
#घोषणा PIPEDSL(pipe)		_MMIO_PIPE2(pipe, _PIPEADSL)
#घोषणा PIPEFRAME(pipe)		_MMIO_PIPE2(pipe, _PIPEAFRAMEHIGH)
#घोषणा PIPEFRAMEPIXEL(pipe)	_MMIO_PIPE2(pipe, _PIPEAFRAMEPIXEL)
#घोषणा PIPESTAT(pipe)		_MMIO_PIPE2(pipe, _PIPEASTAT)

#घोषणा  _PIPEAGCMAX           0x70010
#घोषणा  _PIPEBGCMAX           0x71010
#घोषणा PIPEGCMAX(pipe, i)     _MMIO_PIPE2(pipe, _PIPEAGCMAX + (i) * 4)

#घोषणा _PIPE_MISC_A			0x70030
#घोषणा _PIPE_MISC_B			0x71030
#घोषणा   PIPEMISC_YUV420_ENABLE	(1 << 27) /* glk+ */
#घोषणा   PIPEMISC_YUV420_MODE_FULL_BLEND (1 << 26) /* glk+ */
#घोषणा   PIPEMISC_HDR_MODE_PRECISION	(1 << 23) /* icl+ */
#घोषणा   PIPEMISC_OUTPUT_COLORSPACE_YUV  (1 << 11)
#घोषणा   PIPEMISC_PIXEL_ROUNDING_TRUNC	REG_BIT(8) /* tgl+ */
#घोषणा   PIPEMISC_DITHER_BPC_MASK	(7 << 5)
#घोषणा   PIPEMISC_DITHER_8_BPC		(0 << 5)
#घोषणा   PIPEMISC_DITHER_10_BPC	(1 << 5)
#घोषणा   PIPEMISC_DITHER_6_BPC		(2 << 5)
#घोषणा   PIPEMISC_DITHER_12_BPC	(3 << 5)
#घोषणा   PIPEMISC_DITHER_ENABLE	(1 << 4)
#घोषणा   PIPEMISC_DITHER_TYPE_MASK	(3 << 2)
#घोषणा   PIPEMISC_DITHER_TYPE_SP	(0 << 2)
#घोषणा PIPEMISC(pipe)			_MMIO_PIPE2(pipe, _PIPE_MISC_A)

/* Skylake+ pipe bottom (background) color */
#घोषणा _SKL_BOTTOM_COLOR_A		0x70034
#घोषणा   SKL_BOTTOM_COLOR_GAMMA_ENABLE	(1 << 31)
#घोषणा   SKL_BOTTOM_COLOR_CSC_ENABLE	(1 << 30)
#घोषणा SKL_BOTTOM_COLOR(pipe)		_MMIO_PIPE2(pipe, _SKL_BOTTOM_COLOR_A)

#घोषणा VLV_DPFLIPSTAT				_MMIO(VLV_DISPLAY_BASE + 0x70028)
#घोषणा   PIPEB_LINE_COMPARE_INT_EN		(1 << 29)
#घोषणा   PIPEB_HLINE_INT_EN			(1 << 28)
#घोषणा   PIPEB_VBLANK_INT_EN			(1 << 27)
#घोषणा   SPRITED_FLIP_DONE_INT_EN		(1 << 26)
#घोषणा   SPRITEC_FLIP_DONE_INT_EN		(1 << 25)
#घोषणा   PLANEB_FLIP_DONE_INT_EN		(1 << 24)
#घोषणा   PIPE_PSR_INT_EN			(1 << 22)
#घोषणा   PIPEA_LINE_COMPARE_INT_EN		(1 << 21)
#घोषणा   PIPEA_HLINE_INT_EN			(1 << 20)
#घोषणा   PIPEA_VBLANK_INT_EN			(1 << 19)
#घोषणा   SPRITEB_FLIP_DONE_INT_EN		(1 << 18)
#घोषणा   SPRITEA_FLIP_DONE_INT_EN		(1 << 17)
#घोषणा   PLANEA_FLIPDONE_INT_EN		(1 << 16)
#घोषणा   PIPEC_LINE_COMPARE_INT_EN		(1 << 13)
#घोषणा   PIPEC_HLINE_INT_EN			(1 << 12)
#घोषणा   PIPEC_VBLANK_INT_EN			(1 << 11)
#घोषणा   SPRITEF_FLIPDONE_INT_EN		(1 << 10)
#घोषणा   SPRITEE_FLIPDONE_INT_EN		(1 << 9)
#घोषणा   PLANEC_FLIPDONE_INT_EN		(1 << 8)

#घोषणा DPINVGTT				_MMIO(VLV_DISPLAY_BASE + 0x7002c) /* VLV/CHV only */
#घोषणा   SPRITEF_INVALID_GTT_INT_EN		(1 << 27)
#घोषणा   SPRITEE_INVALID_GTT_INT_EN		(1 << 26)
#घोषणा   PLANEC_INVALID_GTT_INT_EN		(1 << 25)
#घोषणा   CURSORC_INVALID_GTT_INT_EN		(1 << 24)
#घोषणा   CURSORB_INVALID_GTT_INT_EN		(1 << 23)
#घोषणा   CURSORA_INVALID_GTT_INT_EN		(1 << 22)
#घोषणा   SPRITED_INVALID_GTT_INT_EN		(1 << 21)
#घोषणा   SPRITEC_INVALID_GTT_INT_EN		(1 << 20)
#घोषणा   PLANEB_INVALID_GTT_INT_EN		(1 << 19)
#घोषणा   SPRITEB_INVALID_GTT_INT_EN		(1 << 18)
#घोषणा   SPRITEA_INVALID_GTT_INT_EN		(1 << 17)
#घोषणा   PLANEA_INVALID_GTT_INT_EN		(1 << 16)
#घोषणा   DPINVGTT_EN_MASK			0xff0000
#घोषणा   DPINVGTT_EN_MASK_CHV			0xfff0000
#घोषणा   SPRITEF_INVALID_GTT_STATUS		(1 << 11)
#घोषणा   SPRITEE_INVALID_GTT_STATUS		(1 << 10)
#घोषणा   PLANEC_INVALID_GTT_STATUS		(1 << 9)
#घोषणा   CURSORC_INVALID_GTT_STATUS		(1 << 8)
#घोषणा   CURSORB_INVALID_GTT_STATUS		(1 << 7)
#घोषणा   CURSORA_INVALID_GTT_STATUS		(1 << 6)
#घोषणा   SPRITED_INVALID_GTT_STATUS		(1 << 5)
#घोषणा   SPRITEC_INVALID_GTT_STATUS		(1 << 4)
#घोषणा   PLANEB_INVALID_GTT_STATUS		(1 << 3)
#घोषणा   SPRITEB_INVALID_GTT_STATUS		(1 << 2)
#घोषणा   SPRITEA_INVALID_GTT_STATUS		(1 << 1)
#घोषणा   PLANEA_INVALID_GTT_STATUS		(1 << 0)
#घोषणा   DPINVGTT_STATUS_MASK			0xff
#घोषणा   DPINVGTT_STATUS_MASK_CHV		0xfff

#घोषणा DSPARB			_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x70030)
#घोषणा   DSPARB_CSTART_MASK	(0x7f << 7)
#घोषणा   DSPARB_CSTART_SHIFT	7
#घोषणा   DSPARB_BSTART_MASK	(0x7f)
#घोषणा   DSPARB_BSTART_SHIFT	0
#घोषणा   DSPARB_BEND_SHIFT	9 /* on 855 */
#घोषणा   DSPARB_AEND_SHIFT	0
#घोषणा   DSPARB_SPRITEA_SHIFT_VLV	0
#घोषणा   DSPARB_SPRITEA_MASK_VLV	(0xff << 0)
#घोषणा   DSPARB_SPRITEB_SHIFT_VLV	8
#घोषणा   DSPARB_SPRITEB_MASK_VLV	(0xff << 8)
#घोषणा   DSPARB_SPRITEC_SHIFT_VLV	16
#घोषणा   DSPARB_SPRITEC_MASK_VLV	(0xff << 16)
#घोषणा   DSPARB_SPRITED_SHIFT_VLV	24
#घोषणा   DSPARB_SPRITED_MASK_VLV	(0xff << 24)
#घोषणा DSPARB2				_MMIO(VLV_DISPLAY_BASE + 0x70060) /* vlv/chv */
#घोषणा   DSPARB_SPRITEA_HI_SHIFT_VLV	0
#घोषणा   DSPARB_SPRITEA_HI_MASK_VLV	(0x1 << 0)
#घोषणा   DSPARB_SPRITEB_HI_SHIFT_VLV	4
#घोषणा   DSPARB_SPRITEB_HI_MASK_VLV	(0x1 << 4)
#घोषणा   DSPARB_SPRITEC_HI_SHIFT_VLV	8
#घोषणा   DSPARB_SPRITEC_HI_MASK_VLV	(0x1 << 8)
#घोषणा   DSPARB_SPRITED_HI_SHIFT_VLV	12
#घोषणा   DSPARB_SPRITED_HI_MASK_VLV	(0x1 << 12)
#घोषणा   DSPARB_SPRITEE_HI_SHIFT_VLV	16
#घोषणा   DSPARB_SPRITEE_HI_MASK_VLV	(0x1 << 16)
#घोषणा   DSPARB_SPRITEF_HI_SHIFT_VLV	20
#घोषणा   DSPARB_SPRITEF_HI_MASK_VLV	(0x1 << 20)
#घोषणा DSPARB3				_MMIO(VLV_DISPLAY_BASE + 0x7006c) /* chv */
#घोषणा   DSPARB_SPRITEE_SHIFT_VLV	0
#घोषणा   DSPARB_SPRITEE_MASK_VLV	(0xff << 0)
#घोषणा   DSPARB_SPRITEF_SHIFT_VLV	8
#घोषणा   DSPARB_SPRITEF_MASK_VLV	(0xff << 8)

/* pnv/gen4/g4x/vlv/chv */
#घोषणा DSPFW1		_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x70034)
#घोषणा   DSPFW_SR_SHIFT		23
#घोषणा   DSPFW_SR_MASK			(0x1ff << 23)
#घोषणा   DSPFW_CURSORB_SHIFT		16
#घोषणा   DSPFW_CURSORB_MASK		(0x3f << 16)
#घोषणा   DSPFW_PLANEB_SHIFT		8
#घोषणा   DSPFW_PLANEB_MASK		(0x7f << 8)
#घोषणा   DSPFW_PLANEB_MASK_VLV		(0xff << 8) /* vlv/chv */
#घोषणा   DSPFW_PLANEA_SHIFT		0
#घोषणा   DSPFW_PLANEA_MASK		(0x7f << 0)
#घोषणा   DSPFW_PLANEA_MASK_VLV		(0xff << 0) /* vlv/chv */
#घोषणा DSPFW2		_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x70038)
#घोषणा   DSPFW_FBC_SR_EN		(1 << 31)	  /* g4x */
#घोषणा   DSPFW_FBC_SR_SHIFT		28
#घोषणा   DSPFW_FBC_SR_MASK		(0x7 << 28) /* g4x */
#घोषणा   DSPFW_FBC_HPLL_SR_SHIFT	24
#घोषणा   DSPFW_FBC_HPLL_SR_MASK	(0xf << 24) /* g4x */
#घोषणा   DSPFW_SPRITEB_SHIFT		(16)
#घोषणा   DSPFW_SPRITEB_MASK		(0x7f << 16) /* g4x */
#घोषणा   DSPFW_SPRITEB_MASK_VLV	(0xff << 16) /* vlv/chv */
#घोषणा   DSPFW_CURSORA_SHIFT		8
#घोषणा   DSPFW_CURSORA_MASK		(0x3f << 8)
#घोषणा   DSPFW_PLANEC_OLD_SHIFT	0
#घोषणा   DSPFW_PLANEC_OLD_MASK		(0x7f << 0) /* pre-gen4 sprite C */
#घोषणा   DSPFW_SPRITEA_SHIFT		0
#घोषणा   DSPFW_SPRITEA_MASK		(0x7f << 0) /* g4x */
#घोषणा   DSPFW_SPRITEA_MASK_VLV	(0xff << 0) /* vlv/chv */
#घोषणा DSPFW3		_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x7003c)
#घोषणा   DSPFW_HPLL_SR_EN		(1 << 31)
#घोषणा   PINEVIEW_SELF_REFRESH_EN	(1 << 30)
#घोषणा   DSPFW_CURSOR_SR_SHIFT		24
#घोषणा   DSPFW_CURSOR_SR_MASK		(0x3f << 24)
#घोषणा   DSPFW_HPLL_CURSOR_SHIFT	16
#घोषणा   DSPFW_HPLL_CURSOR_MASK	(0x3f << 16)
#घोषणा   DSPFW_HPLL_SR_SHIFT		0
#घोषणा   DSPFW_HPLL_SR_MASK		(0x1ff << 0)

/* vlv/chv */
#घोषणा DSPFW4		_MMIO(VLV_DISPLAY_BASE + 0x70070)
#घोषणा   DSPFW_SPRITEB_WM1_SHIFT	16
#घोषणा   DSPFW_SPRITEB_WM1_MASK	(0xff << 16)
#घोषणा   DSPFW_CURSORA_WM1_SHIFT	8
#घोषणा   DSPFW_CURSORA_WM1_MASK	(0x3f << 8)
#घोषणा   DSPFW_SPRITEA_WM1_SHIFT	0
#घोषणा   DSPFW_SPRITEA_WM1_MASK	(0xff << 0)
#घोषणा DSPFW5		_MMIO(VLV_DISPLAY_BASE + 0x70074)
#घोषणा   DSPFW_PLANEB_WM1_SHIFT	24
#घोषणा   DSPFW_PLANEB_WM1_MASK		(0xff << 24)
#घोषणा   DSPFW_PLANEA_WM1_SHIFT	16
#घोषणा   DSPFW_PLANEA_WM1_MASK		(0xff << 16)
#घोषणा   DSPFW_CURSORB_WM1_SHIFT	8
#घोषणा   DSPFW_CURSORB_WM1_MASK	(0x3f << 8)
#घोषणा   DSPFW_CURSOR_SR_WM1_SHIFT	0
#घोषणा   DSPFW_CURSOR_SR_WM1_MASK	(0x3f << 0)
#घोषणा DSPFW6		_MMIO(VLV_DISPLAY_BASE + 0x70078)
#घोषणा   DSPFW_SR_WM1_SHIFT		0
#घोषणा   DSPFW_SR_WM1_MASK		(0x1ff << 0)
#घोषणा DSPFW7		_MMIO(VLV_DISPLAY_BASE + 0x7007c)
#घोषणा DSPFW7_CHV	_MMIO(VLV_DISPLAY_BASE + 0x700b4) /* wtf #1? */
#घोषणा   DSPFW_SPRITED_WM1_SHIFT	24
#घोषणा   DSPFW_SPRITED_WM1_MASK	(0xff << 24)
#घोषणा   DSPFW_SPRITED_SHIFT		16
#घोषणा   DSPFW_SPRITED_MASK_VLV	(0xff << 16)
#घोषणा   DSPFW_SPRITEC_WM1_SHIFT	8
#घोषणा   DSPFW_SPRITEC_WM1_MASK	(0xff << 8)
#घोषणा   DSPFW_SPRITEC_SHIFT		0
#घोषणा   DSPFW_SPRITEC_MASK_VLV	(0xff << 0)
#घोषणा DSPFW8_CHV	_MMIO(VLV_DISPLAY_BASE + 0x700b8)
#घोषणा   DSPFW_SPRITEF_WM1_SHIFT	24
#घोषणा   DSPFW_SPRITEF_WM1_MASK	(0xff << 24)
#घोषणा   DSPFW_SPRITEF_SHIFT		16
#घोषणा   DSPFW_SPRITEF_MASK_VLV	(0xff << 16)
#घोषणा   DSPFW_SPRITEE_WM1_SHIFT	8
#घोषणा   DSPFW_SPRITEE_WM1_MASK	(0xff << 8)
#घोषणा   DSPFW_SPRITEE_SHIFT		0
#घोषणा   DSPFW_SPRITEE_MASK_VLV	(0xff << 0)
#घोषणा DSPFW9_CHV	_MMIO(VLV_DISPLAY_BASE + 0x7007c) /* wtf #2? */
#घोषणा   DSPFW_PLANEC_WM1_SHIFT	24
#घोषणा   DSPFW_PLANEC_WM1_MASK		(0xff << 24)
#घोषणा   DSPFW_PLANEC_SHIFT		16
#घोषणा   DSPFW_PLANEC_MASK_VLV		(0xff << 16)
#घोषणा   DSPFW_CURSORC_WM1_SHIFT	8
#घोषणा   DSPFW_CURSORC_WM1_MASK	(0x3f << 16)
#घोषणा   DSPFW_CURSORC_SHIFT		0
#घोषणा   DSPFW_CURSORC_MASK		(0x3f << 0)

/* vlv/chv high order bits */
#घोषणा DSPHOWM		_MMIO(VLV_DISPLAY_BASE + 0x70064)
#घोषणा   DSPFW_SR_HI_SHIFT		24
#घोषणा   DSPFW_SR_HI_MASK		(3 << 24) /* 2 bits क्रम chv, 1 क्रम vlv */
#घोषणा   DSPFW_SPRITEF_HI_SHIFT	23
#घोषणा   DSPFW_SPRITEF_HI_MASK		(1 << 23)
#घोषणा   DSPFW_SPRITEE_HI_SHIFT	22
#घोषणा   DSPFW_SPRITEE_HI_MASK		(1 << 22)
#घोषणा   DSPFW_PLANEC_HI_SHIFT		21
#घोषणा   DSPFW_PLANEC_HI_MASK		(1 << 21)
#घोषणा   DSPFW_SPRITED_HI_SHIFT	20
#घोषणा   DSPFW_SPRITED_HI_MASK		(1 << 20)
#घोषणा   DSPFW_SPRITEC_HI_SHIFT	16
#घोषणा   DSPFW_SPRITEC_HI_MASK		(1 << 16)
#घोषणा   DSPFW_PLANEB_HI_SHIFT		12
#घोषणा   DSPFW_PLANEB_HI_MASK		(1 << 12)
#घोषणा   DSPFW_SPRITEB_HI_SHIFT	8
#घोषणा   DSPFW_SPRITEB_HI_MASK		(1 << 8)
#घोषणा   DSPFW_SPRITEA_HI_SHIFT	4
#घोषणा   DSPFW_SPRITEA_HI_MASK		(1 << 4)
#घोषणा   DSPFW_PLANEA_HI_SHIFT		0
#घोषणा   DSPFW_PLANEA_HI_MASK		(1 << 0)
#घोषणा DSPHOWM1	_MMIO(VLV_DISPLAY_BASE + 0x70068)
#घोषणा   DSPFW_SR_WM1_HI_SHIFT		24
#घोषणा   DSPFW_SR_WM1_HI_MASK		(3 << 24) /* 2 bits क्रम chv, 1 क्रम vlv */
#घोषणा   DSPFW_SPRITEF_WM1_HI_SHIFT	23
#घोषणा   DSPFW_SPRITEF_WM1_HI_MASK	(1 << 23)
#घोषणा   DSPFW_SPRITEE_WM1_HI_SHIFT	22
#घोषणा   DSPFW_SPRITEE_WM1_HI_MASK	(1 << 22)
#घोषणा   DSPFW_PLANEC_WM1_HI_SHIFT	21
#घोषणा   DSPFW_PLANEC_WM1_HI_MASK	(1 << 21)
#घोषणा   DSPFW_SPRITED_WM1_HI_SHIFT	20
#घोषणा   DSPFW_SPRITED_WM1_HI_MASK	(1 << 20)
#घोषणा   DSPFW_SPRITEC_WM1_HI_SHIFT	16
#घोषणा   DSPFW_SPRITEC_WM1_HI_MASK	(1 << 16)
#घोषणा   DSPFW_PLANEB_WM1_HI_SHIFT	12
#घोषणा   DSPFW_PLANEB_WM1_HI_MASK	(1 << 12)
#घोषणा   DSPFW_SPRITEB_WM1_HI_SHIFT	8
#घोषणा   DSPFW_SPRITEB_WM1_HI_MASK	(1 << 8)
#घोषणा   DSPFW_SPRITEA_WM1_HI_SHIFT	4
#घोषणा   DSPFW_SPRITEA_WM1_HI_MASK	(1 << 4)
#घोषणा   DSPFW_PLANEA_WM1_HI_SHIFT	0
#घोषणा   DSPFW_PLANEA_WM1_HI_MASK	(1 << 0)

/* drain latency रेजिस्टर values*/
#घोषणा VLV_DDL(pipe)			_MMIO(VLV_DISPLAY_BASE + 0x70050 + 4 * (pipe))
#घोषणा DDL_CURSOR_SHIFT		24
#घोषणा DDL_SPRITE_SHIFT(sprite)	(8 + 8 * (sprite))
#घोषणा DDL_PLANE_SHIFT			0
#घोषणा DDL_PRECISION_HIGH		(1 << 7)
#घोषणा DDL_PRECISION_LOW		(0 << 7)
#घोषणा DRAIN_LATENCY_MASK		0x7f

#घोषणा CBR1_VLV			_MMIO(VLV_DISPLAY_BASE + 0x70400)
#घोषणा  CBR_PND_DEADLINE_DISABLE	(1 << 31)
#घोषणा  CBR_PWM_CLOCK_MUX_SELECT	(1 << 30)

#घोषणा CBR4_VLV			_MMIO(VLV_DISPLAY_BASE + 0x70450)
#घोषणा  CBR_DPLLBMD_PIPE(pipe)		(1 << (7 + (pipe) * 11)) /* pipes B and C */

/* FIFO watermark sizes etc */
#घोषणा G4X_FIFO_LINE_SIZE	64
#घोषणा I915_FIFO_LINE_SIZE	64
#घोषणा I830_FIFO_LINE_SIZE	32

#घोषणा VALLEYVIEW_FIFO_SIZE	255
#घोषणा G4X_FIFO_SIZE		127
#घोषणा I965_FIFO_SIZE		512
#घोषणा I945_FIFO_SIZE		127
#घोषणा I915_FIFO_SIZE		95
#घोषणा I855GM_FIFO_SIZE	127 /* In cachelines */
#घोषणा I830_FIFO_SIZE		95

#घोषणा VALLEYVIEW_MAX_WM	0xff
#घोषणा G4X_MAX_WM		0x3f
#घोषणा I915_MAX_WM		0x3f

#घोषणा PINEVIEW_DISPLAY_FIFO	512 /* in 64byte unit */
#घोषणा PINEVIEW_FIFO_LINE_SIZE	64
#घोषणा PINEVIEW_MAX_WM		0x1ff
#घोषणा PINEVIEW_DFT_WM		0x3f
#घोषणा PINEVIEW_DFT_HPLLOFF_WM	0
#घोषणा PINEVIEW_GUARD_WM		10
#घोषणा PINEVIEW_CURSOR_FIFO		64
#घोषणा PINEVIEW_CURSOR_MAX_WM	0x3f
#घोषणा PINEVIEW_CURSOR_DFT_WM	0
#घोषणा PINEVIEW_CURSOR_GUARD_WM	5

#घोषणा VALLEYVIEW_CURSOR_MAX_WM 64
#घोषणा I965_CURSOR_FIFO	64
#घोषणा I965_CURSOR_MAX_WM	32
#घोषणा I965_CURSOR_DFT_WM	8

/* Watermark रेजिस्टर definitions क्रम SKL */
#घोषणा _CUR_WM_A_0		0x70140
#घोषणा _CUR_WM_B_0		0x71140
#घोषणा _PLANE_WM_1_A_0		0x70240
#घोषणा _PLANE_WM_1_B_0		0x71240
#घोषणा _PLANE_WM_2_A_0		0x70340
#घोषणा _PLANE_WM_2_B_0		0x71340
#घोषणा _PLANE_WM_TRANS_1_A_0	0x70268
#घोषणा _PLANE_WM_TRANS_1_B_0	0x71268
#घोषणा _PLANE_WM_TRANS_2_A_0	0x70368
#घोषणा _PLANE_WM_TRANS_2_B_0	0x71368
#घोषणा _CUR_WM_TRANS_A_0	0x70168
#घोषणा _CUR_WM_TRANS_B_0	0x71168
#घोषणा   PLANE_WM_EN		(1 << 31)
#घोषणा   PLANE_WM_IGNORE_LINES	(1 << 30)
#घोषणा   PLANE_WM_LINES_SHIFT	14
#घोषणा   PLANE_WM_LINES_MASK	0x1f
#घोषणा   PLANE_WM_BLOCKS_MASK	0x7ff /* skl+: 10 bits, icl+ 11 bits */

#घोषणा _CUR_WM_0(pipe) _PIPE(pipe, _CUR_WM_A_0, _CUR_WM_B_0)
#घोषणा CUR_WM(pipe, level) _MMIO(_CUR_WM_0(pipe) + ((4) * (level)))
#घोषणा CUR_WM_TRANS(pipe) _MMIO_PIPE(pipe, _CUR_WM_TRANS_A_0, _CUR_WM_TRANS_B_0)

#घोषणा _PLANE_WM_1(pipe) _PIPE(pipe, _PLANE_WM_1_A_0, _PLANE_WM_1_B_0)
#घोषणा _PLANE_WM_2(pipe) _PIPE(pipe, _PLANE_WM_2_A_0, _PLANE_WM_2_B_0)
#घोषणा _PLANE_WM_BASE(pipe, plane)	\
			_PLANE(plane, _PLANE_WM_1(pipe), _PLANE_WM_2(pipe))
#घोषणा PLANE_WM(pipe, plane, level)	\
			_MMIO(_PLANE_WM_BASE(pipe, plane) + ((4) * (level)))
#घोषणा _PLANE_WM_TRANS_1(pipe)	\
			_PIPE(pipe, _PLANE_WM_TRANS_1_A_0, _PLANE_WM_TRANS_1_B_0)
#घोषणा _PLANE_WM_TRANS_2(pipe)	\
			_PIPE(pipe, _PLANE_WM_TRANS_2_A_0, _PLANE_WM_TRANS_2_B_0)
#घोषणा PLANE_WM_TRANS(pipe, plane)	\
	_MMIO(_PLANE(plane, _PLANE_WM_TRANS_1(pipe), _PLANE_WM_TRANS_2(pipe)))

/* define the Watermark रेजिस्टर on Ironlake */
#घोषणा _WM0_PIPEA_ILK		0x45100
#घोषणा _WM0_PIPEB_ILK		0x45104
#घोषणा _WM0_PIPEC_IVB		0x45200
#घोषणा WM0_PIPE_ILK(pipe)	_MMIO_PIPE3((pipe), _WM0_PIPEA_ILK, \
					    _WM0_PIPEB_ILK, _WM0_PIPEC_IVB)
#घोषणा  WM0_PIPE_PLANE_MASK	(0xffff << 16)
#घोषणा  WM0_PIPE_PLANE_SHIFT	16
#घोषणा  WM0_PIPE_SPRITE_MASK	(0xff << 8)
#घोषणा  WM0_PIPE_SPRITE_SHIFT	8
#घोषणा  WM0_PIPE_CURSOR_MASK	(0xff)
#घोषणा WM1_LP_ILK		_MMIO(0x45108)
#घोषणा  WM1_LP_SR_EN		(1 << 31)
#घोषणा  WM1_LP_LATENCY_SHIFT	24
#घोषणा  WM1_LP_LATENCY_MASK	(0x7f << 24)
#घोषणा  WM1_LP_FBC_MASK	(0xf << 20)
#घोषणा  WM1_LP_FBC_SHIFT	20
#घोषणा  WM1_LP_FBC_SHIFT_BDW	19
#घोषणा  WM1_LP_SR_MASK		(0x7ff << 8)
#घोषणा  WM1_LP_SR_SHIFT	8
#घोषणा  WM1_LP_CURSOR_MASK	(0xff)
#घोषणा WM2_LP_ILK		_MMIO(0x4510c)
#घोषणा  WM2_LP_EN		(1 << 31)
#घोषणा WM3_LP_ILK		_MMIO(0x45110)
#घोषणा  WM3_LP_EN		(1 << 31)
#घोषणा WM1S_LP_ILK		_MMIO(0x45120)
#घोषणा WM2S_LP_IVB		_MMIO(0x45124)
#घोषणा WM3S_LP_IVB		_MMIO(0x45128)
#घोषणा  WM1S_LP_EN		(1 << 31)

#घोषणा HSW_WM_LP_VAL(lat, fbc, pri, cur) \
	(WM3_LP_EN | ((lat) << WM1_LP_LATENCY_SHIFT) | \
	 ((fbc) << WM1_LP_FBC_SHIFT) | ((pri) << WM1_LP_SR_SHIFT) | (cur))

/* Memory latency समयr रेजिस्टर */
#घोषणा MLTR_ILK		_MMIO(0x11222)
#घोषणा  MLTR_WM1_SHIFT		0
#घोषणा  MLTR_WM2_SHIFT		8
/* the unit of memory self-refresh latency समय is 0.5us */
#घोषणा  ILK_SRLT_MASK		0x3f


/* the address where we get all kinds of latency value */
#घोषणा SSKPD			_MMIO(0x5d10)
#घोषणा SSKPD_WM_MASK		0x3f
#घोषणा SSKPD_WM0_SHIFT		0
#घोषणा SSKPD_WM1_SHIFT		8
#घोषणा SSKPD_WM2_SHIFT		16
#घोषणा SSKPD_WM3_SHIFT		24

/*
 * The two pipe frame counter रेजिस्टरs are not synchronized, so
 * पढ़ोing a stable value is somewhat tricky. The following code
 * should work:
 *
 *  करो अणु
 *    high1 = ((INREG(PIPEAFRAMEHIGH) & PIPE_FRAME_HIGH_MASK) >>
 *             PIPE_FRAME_HIGH_SHIFT;
 *    low1 =  ((INREG(PIPEAFRAMEPIXEL) & PIPE_FRAME_LOW_MASK) >>
 *             PIPE_FRAME_LOW_SHIFT);
 *    high2 = ((INREG(PIPEAFRAMEHIGH) & PIPE_FRAME_HIGH_MASK) >>
 *             PIPE_FRAME_HIGH_SHIFT);
 *  पूर्ण जबतक (high1 != high2);
 *  frame = (high1 << 8) | low1;
 */
#घोषणा _PIPEAFRAMEHIGH          0x70040
#घोषणा   PIPE_FRAME_HIGH_MASK    0x0000ffff
#घोषणा   PIPE_FRAME_HIGH_SHIFT   0
#घोषणा _PIPEAFRAMEPIXEL         0x70044
#घोषणा   PIPE_FRAME_LOW_MASK     0xff000000
#घोषणा   PIPE_FRAME_LOW_SHIFT    24
#घोषणा   PIPE_PIXEL_MASK         0x00ffffff
#घोषणा   PIPE_PIXEL_SHIFT        0
/* GM45+ just has to be dअगरferent */
#घोषणा _PIPEA_FRMCOUNT_G4X	0x70040
#घोषणा _PIPEA_FLIPCOUNT_G4X	0x70044
#घोषणा PIPE_FRMCOUNT_G4X(pipe) _MMIO_PIPE2(pipe, _PIPEA_FRMCOUNT_G4X)
#घोषणा PIPE_FLIPCOUNT_G4X(pipe) _MMIO_PIPE2(pipe, _PIPEA_FLIPCOUNT_G4X)

/* Cursor A & B regs */
#घोषणा _CURACNTR		0x70080
/* Old style CUR*CNTR flags (desktop 8xx) */
#घोषणा   CURSOR_ENABLE		0x80000000
#घोषणा   CURSOR_GAMMA_ENABLE	0x40000000
#घोषणा   CURSOR_STRIDE_SHIFT	28
#घोषणा   CURSOR_STRIDE(x)	((ffs(x) - 9) << CURSOR_STRIDE_SHIFT) /* 256,512,1k,2k */
#घोषणा   CURSOR_FORMAT_SHIFT	24
#घोषणा   CURSOR_FORMAT_MASK	(0x07 << CURSOR_FORMAT_SHIFT)
#घोषणा   CURSOR_FORMAT_2C	(0x00 << CURSOR_FORMAT_SHIFT)
#घोषणा   CURSOR_FORMAT_3C	(0x01 << CURSOR_FORMAT_SHIFT)
#घोषणा   CURSOR_FORMAT_4C	(0x02 << CURSOR_FORMAT_SHIFT)
#घोषणा   CURSOR_FORMAT_ARGB	(0x04 << CURSOR_FORMAT_SHIFT)
#घोषणा   CURSOR_FORMAT_XRGB	(0x05 << CURSOR_FORMAT_SHIFT)
/* New style CUR*CNTR flags */
#घोषणा   MCURSOR_MODE		0x27
#घोषणा   MCURSOR_MODE_DISABLE   0x00
#घोषणा   MCURSOR_MODE_128_32B_AX 0x02
#घोषणा   MCURSOR_MODE_256_32B_AX 0x03
#घोषणा   MCURSOR_MODE_64_32B_AX 0x07
#घोषणा   MCURSOR_MODE_128_ARGB_AX ((1 << 5) | MCURSOR_MODE_128_32B_AX)
#घोषणा   MCURSOR_MODE_256_ARGB_AX ((1 << 5) | MCURSOR_MODE_256_32B_AX)
#घोषणा   MCURSOR_MODE_64_ARGB_AX ((1 << 5) | MCURSOR_MODE_64_32B_AX)
#घोषणा   MCURSOR_PIPE_SELECT_MASK	(0x3 << 28)
#घोषणा   MCURSOR_PIPE_SELECT_SHIFT	28
#घोषणा   MCURSOR_PIPE_SELECT(pipe)	((pipe) << 28)
#घोषणा   MCURSOR_GAMMA_ENABLE  (1 << 26)
#घोषणा   MCURSOR_PIPE_CSC_ENABLE (1 << 24) /* ilk+ */
#घोषणा   MCURSOR_ROTATE_180	(1 << 15)
#घोषणा   MCURSOR_TRICKLE_FEED_DISABLE	(1 << 14)
#घोषणा _CURABASE		0x70084
#घोषणा _CURAPOS		0x70088
#घोषणा   CURSOR_POS_MASK       0x007FF
#घोषणा   CURSOR_POS_SIGN       0x8000
#घोषणा   CURSOR_X_SHIFT        0
#घोषणा   CURSOR_Y_SHIFT        16
#घोषणा CURSIZE			_MMIO(0x700a0) /* 845/865 */
#घोषणा _CUR_FBC_CTL_A		0x700a0 /* ivb+ */
#घोषणा   CUR_FBC_CTL_EN	(1 << 31)
#घोषणा _CURASURFLIVE		0x700ac /* g4x+ */
#घोषणा _CURBCNTR		0x700c0
#घोषणा _CURBBASE		0x700c4
#घोषणा _CURBPOS		0x700c8

#घोषणा _CURBCNTR_IVB		0x71080
#घोषणा _CURBBASE_IVB		0x71084
#घोषणा _CURBPOS_IVB		0x71088

#घोषणा CURCNTR(pipe) _CURSOR2(pipe, _CURACNTR)
#घोषणा CURBASE(pipe) _CURSOR2(pipe, _CURABASE)
#घोषणा CURPOS(pipe) _CURSOR2(pipe, _CURAPOS)
#घोषणा CUR_FBC_CTL(pipe) _CURSOR2(pipe, _CUR_FBC_CTL_A)
#घोषणा CURSURFLIVE(pipe) _CURSOR2(pipe, _CURASURFLIVE)

#घोषणा CURSOR_A_OFFSET 0x70080
#घोषणा CURSOR_B_OFFSET 0x700c0
#घोषणा CHV_CURSOR_C_OFFSET 0x700e0
#घोषणा IVB_CURSOR_B_OFFSET 0x71080
#घोषणा IVB_CURSOR_C_OFFSET 0x72080
#घोषणा TGL_CURSOR_D_OFFSET 0x73080

/* Display A control */
#घोषणा _DSPAADDR_VLV				0x7017C /* vlv/chv */
#घोषणा _DSPACNTR				0x70180
#घोषणा   DISPLAY_PLANE_ENABLE			(1 << 31)
#घोषणा   DISPLAY_PLANE_DISABLE			0
#घोषणा   DISPPLANE_GAMMA_ENABLE		(1 << 30)
#घोषणा   DISPPLANE_GAMMA_DISABLE		0
#घोषणा   DISPPLANE_PIXFORMAT_MASK		(0xf << 26)
#घोषणा   DISPPLANE_YUV422			(0x0 << 26)
#घोषणा   DISPPLANE_8BPP			(0x2 << 26)
#घोषणा   DISPPLANE_BGRA555			(0x3 << 26)
#घोषणा   DISPPLANE_BGRX555			(0x4 << 26)
#घोषणा   DISPPLANE_BGRX565			(0x5 << 26)
#घोषणा   DISPPLANE_BGRX888			(0x6 << 26)
#घोषणा   DISPPLANE_BGRA888			(0x7 << 26)
#घोषणा   DISPPLANE_RGBX101010			(0x8 << 26)
#घोषणा   DISPPLANE_RGBA101010			(0x9 << 26)
#घोषणा   DISPPLANE_BGRX101010			(0xa << 26)
#घोषणा   DISPPLANE_BGRA101010			(0xb << 26)
#घोषणा   DISPPLANE_RGBX161616			(0xc << 26)
#घोषणा   DISPPLANE_RGBX888			(0xe << 26)
#घोषणा   DISPPLANE_RGBA888			(0xf << 26)
#घोषणा   DISPPLANE_STEREO_ENABLE		(1 << 25)
#घोषणा   DISPPLANE_STEREO_DISABLE		0
#घोषणा   DISPPLANE_PIPE_CSC_ENABLE		(1 << 24) /* ilk+ */
#घोषणा   DISPPLANE_SEL_PIPE_SHIFT		24
#घोषणा   DISPPLANE_SEL_PIPE_MASK		(3 << DISPPLANE_SEL_PIPE_SHIFT)
#घोषणा   DISPPLANE_SEL_PIPE(pipe)		((pipe) << DISPPLANE_SEL_PIPE_SHIFT)
#घोषणा   DISPPLANE_SRC_KEY_ENABLE		(1 << 22)
#घोषणा   DISPPLANE_SRC_KEY_DISABLE		0
#घोषणा   DISPPLANE_LINE_DOUBLE			(1 << 20)
#घोषणा   DISPPLANE_NO_LINE_DOUBLE		0
#घोषणा   DISPPLANE_STEREO_POLARITY_FIRST	0
#घोषणा   DISPPLANE_STEREO_POLARITY_SECOND	(1 << 18)
#घोषणा   DISPPLANE_ALPHA_PREMULTIPLY		(1 << 16) /* CHV pipe B */
#घोषणा   DISPPLANE_ROTATE_180			(1 << 15)
#घोषणा   DISPPLANE_TRICKLE_FEED_DISABLE	(1 << 14) /* Ironlake */
#घोषणा   DISPPLANE_TILED			(1 << 10)
#घोषणा   DISPPLANE_ASYNC_FLIP			(1 << 9) /* g4x+ */
#घोषणा   DISPPLANE_MIRROR			(1 << 8) /* CHV pipe B */
#घोषणा _DSPAADDR				0x70184
#घोषणा _DSPASTRIDE				0x70188
#घोषणा _DSPAPOS				0x7018C /* reserved */
#घोषणा _DSPASIZE				0x70190
#घोषणा _DSPASURF				0x7019C /* 965+ only */
#घोषणा _DSPATILखातापूर्णF				0x701A4 /* 965+ only */
#घोषणा _DSPAOFFSET				0x701A4 /* HSW */
#घोषणा _DSPASURFLIVE				0x701AC
#घोषणा _DSPAGAMC				0x701E0

#घोषणा DSPADDR_VLV(plane)	_MMIO_PIPE2(plane, _DSPAADDR_VLV)
#घोषणा DSPCNTR(plane)		_MMIO_PIPE2(plane, _DSPACNTR)
#घोषणा DSPADDR(plane)		_MMIO_PIPE2(plane, _DSPAADDR)
#घोषणा DSPSTRIDE(plane)	_MMIO_PIPE2(plane, _DSPASTRIDE)
#घोषणा DSPPOS(plane)		_MMIO_PIPE2(plane, _DSPAPOS)
#घोषणा DSPSIZE(plane)		_MMIO_PIPE2(plane, _DSPASIZE)
#घोषणा DSPSURF(plane)		_MMIO_PIPE2(plane, _DSPASURF)
#घोषणा DSPTILखातापूर्णF(plane)	_MMIO_PIPE2(plane, _DSPATILखातापूर्णF)
#घोषणा DSPLINOFF(plane)	DSPADDR(plane)
#घोषणा DSPOFFSET(plane)	_MMIO_PIPE2(plane, _DSPAOFFSET)
#घोषणा DSPSURFLIVE(plane)	_MMIO_PIPE2(plane, _DSPASURFLIVE)
#घोषणा DSPGAMC(plane, i)	_MMIO(_PIPE2(plane, _DSPAGAMC) + (5 - (i)) * 4) /* plane C only, 6 x u0.8 */

/* CHV pipe B blender and primary plane */
#घोषणा _CHV_BLEND_A		0x60a00
#घोषणा   CHV_BLEND_LEGACY		(0 << 30)
#घोषणा   CHV_BLEND_ANDROID		(1 << 30)
#घोषणा   CHV_BLEND_MPO			(2 << 30)
#घोषणा   CHV_BLEND_MASK		(3 << 30)
#घोषणा _CHV_CANVAS_A		0x60a04
#घोषणा _PRIMPOS_A		0x60a08
#घोषणा _PRIMSIZE_A		0x60a0c
#घोषणा _PRIMCNSTALPHA_A	0x60a10
#घोषणा   PRIM_CONST_ALPHA_ENABLE	(1 << 31)

#घोषणा CHV_BLEND(pipe)		_MMIO_TRANS2(pipe, _CHV_BLEND_A)
#घोषणा CHV_CANVAS(pipe)	_MMIO_TRANS2(pipe, _CHV_CANVAS_A)
#घोषणा PRIMPOS(plane)		_MMIO_TRANS2(plane, _PRIMPOS_A)
#घोषणा PRIMSIZE(plane)		_MMIO_TRANS2(plane, _PRIMSIZE_A)
#घोषणा PRIMCNSTALPHA(plane)	_MMIO_TRANS2(plane, _PRIMCNSTALPHA_A)

/* Display/Sprite base address macros */
#घोषणा DISP_BASEADDR_MASK	(0xfffff000)
#घोषणा I915_LO_DISPBASE(val)	((val) & ~DISP_BASEADDR_MASK)
#घोषणा I915_HI_DISPBASE(val)	((val) & DISP_BASEADDR_MASK)

/*
 * VBIOS flags
 * gen2:
 * [00:06] alm,mgm
 * [10:16] all
 * [30:32] alm,mgm
 * gen3+:
 * [00:0f] all
 * [10:1f] all
 * [30:32] all
 */
#घोषणा SWF0(i)	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x70410 + (i) * 4)
#घोषणा SWF1(i)	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x71410 + (i) * 4)
#घोषणा SWF3(i)	_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x72414 + (i) * 4)
#घोषणा SWF_ILK(i)	_MMIO(0x4F000 + (i) * 4)

/* Pipe B */
#घोषणा _PIPEBDSL		(DISPLAY_MMIO_BASE(dev_priv) + 0x71000)
#घोषणा _PIPEBCONF		(DISPLAY_MMIO_BASE(dev_priv) + 0x71008)
#घोषणा _PIPEBSTAT		(DISPLAY_MMIO_BASE(dev_priv) + 0x71024)
#घोषणा _PIPEBFRAMEHIGH		0x71040
#घोषणा _PIPEBFRAMEPIXEL	0x71044
#घोषणा _PIPEB_FRMCOUNT_G4X	(DISPLAY_MMIO_BASE(dev_priv) + 0x71040)
#घोषणा _PIPEB_FLIPCOUNT_G4X	(DISPLAY_MMIO_BASE(dev_priv) + 0x71044)


/* Display B control */
#घोषणा _DSPBCNTR		(DISPLAY_MMIO_BASE(dev_priv) + 0x71180)
#घोषणा   DISPPLANE_ALPHA_TRANS_ENABLE		(1 << 15)
#घोषणा   DISPPLANE_ALPHA_TRANS_DISABLE		0
#घोषणा   DISPPLANE_SPRITE_ABOVE_DISPLAY	0
#घोषणा   DISPPLANE_SPRITE_ABOVE_OVERLAY	(1)
#घोषणा _DSPBADDR		(DISPLAY_MMIO_BASE(dev_priv) + 0x71184)
#घोषणा _DSPBSTRIDE		(DISPLAY_MMIO_BASE(dev_priv) + 0x71188)
#घोषणा _DSPBPOS		(DISPLAY_MMIO_BASE(dev_priv) + 0x7118C)
#घोषणा _DSPBSIZE		(DISPLAY_MMIO_BASE(dev_priv) + 0x71190)
#घोषणा _DSPBSURF		(DISPLAY_MMIO_BASE(dev_priv) + 0x7119C)
#घोषणा _DSPBTILखातापूर्णF		(DISPLAY_MMIO_BASE(dev_priv) + 0x711A4)
#घोषणा _DSPBOFFSET		(DISPLAY_MMIO_BASE(dev_priv) + 0x711A4)
#घोषणा _DSPBSURFLIVE		(DISPLAY_MMIO_BASE(dev_priv) + 0x711AC)

/* ICL DSI 0 and 1 */
#घोषणा _PIPEDSI0CONF		0x7b008
#घोषणा _PIPEDSI1CONF		0x7b808

/* Sprite A control */
#घोषणा _DVSACNTR		0x72180
#घोषणा   DVS_ENABLE		(1 << 31)
#घोषणा   DVS_GAMMA_ENABLE	(1 << 30)
#घोषणा   DVS_YUV_RANGE_CORRECTION_DISABLE	(1 << 27)
#घोषणा   DVS_PIXFORMAT_MASK	(3 << 25)
#घोषणा   DVS_FORMAT_YUV422	(0 << 25)
#घोषणा   DVS_FORMAT_RGBX101010	(1 << 25)
#घोषणा   DVS_FORMAT_RGBX888	(2 << 25)
#घोषणा   DVS_FORMAT_RGBX161616	(3 << 25)
#घोषणा   DVS_PIPE_CSC_ENABLE   (1 << 24)
#घोषणा   DVS_SOURCE_KEY	(1 << 22)
#घोषणा   DVS_RGB_ORDER_XBGR	(1 << 20)
#घोषणा   DVS_YUV_FORMAT_BT709	(1 << 18)
#घोषणा   DVS_YUV_BYTE_ORDER_MASK (3 << 16)
#घोषणा   DVS_YUV_ORDER_YUYV	(0 << 16)
#घोषणा   DVS_YUV_ORDER_UYVY	(1 << 16)
#घोषणा   DVS_YUV_ORDER_YVYU	(2 << 16)
#घोषणा   DVS_YUV_ORDER_VYUY	(3 << 16)
#घोषणा   DVS_ROTATE_180	(1 << 15)
#घोषणा   DVS_DEST_KEY		(1 << 2)
#घोषणा   DVS_TRICKLE_FEED_DISABLE (1 << 14)
#घोषणा   DVS_TILED		(1 << 10)
#घोषणा _DVSALINOFF		0x72184
#घोषणा _DVSASTRIDE		0x72188
#घोषणा _DVSAPOS		0x7218c
#घोषणा _DVSASIZE		0x72190
#घोषणा _DVSAKEYVAL		0x72194
#घोषणा _DVSAKEYMSK		0x72198
#घोषणा _DVSASURF		0x7219c
#घोषणा _DVSAKEYMAXVAL		0x721a0
#घोषणा _DVSATILखातापूर्णF		0x721a4
#घोषणा _DVSASURFLIVE		0x721ac
#घोषणा _DVSAGAMC_G4X		0x721e0 /* g4x */
#घोषणा _DVSASCALE		0x72204
#घोषणा   DVS_SCALE_ENABLE	(1 << 31)
#घोषणा   DVS_FILTER_MASK	(3 << 29)
#घोषणा   DVS_FILTER_MEDIUM	(0 << 29)
#घोषणा   DVS_FILTER_ENHANCING	(1 << 29)
#घोषणा   DVS_FILTER_SOFTENING	(2 << 29)
#घोषणा   DVS_VERTICAL_OFFSET_HALF (1 << 28) /* must be enabled below */
#घोषणा   DVS_VERTICAL_OFFSET_ENABLE (1 << 27)
#घोषणा _DVSAGAMC_ILK		0x72300 /* ilk/snb */
#घोषणा _DVSAGAMCMAX_ILK	0x72340 /* ilk/snb */

#घोषणा _DVSBCNTR		0x73180
#घोषणा _DVSBLINOFF		0x73184
#घोषणा _DVSBSTRIDE		0x73188
#घोषणा _DVSBPOS		0x7318c
#घोषणा _DVSBSIZE		0x73190
#घोषणा _DVSBKEYVAL		0x73194
#घोषणा _DVSBKEYMSK		0x73198
#घोषणा _DVSBSURF		0x7319c
#घोषणा _DVSBKEYMAXVAL		0x731a0
#घोषणा _DVSBTILखातापूर्णF		0x731a4
#घोषणा _DVSBSURFLIVE		0x731ac
#घोषणा _DVSBGAMC_G4X		0x731e0 /* g4x */
#घोषणा _DVSBSCALE		0x73204
#घोषणा _DVSBGAMC_ILK		0x73300 /* ilk/snb */
#घोषणा _DVSBGAMCMAX_ILK	0x73340 /* ilk/snb */

#घोषणा DVSCNTR(pipe) _MMIO_PIPE(pipe, _DVSACNTR, _DVSBCNTR)
#घोषणा DVSLINOFF(pipe) _MMIO_PIPE(pipe, _DVSALINOFF, _DVSBLINOFF)
#घोषणा DVSSTRIDE(pipe) _MMIO_PIPE(pipe, _DVSASTRIDE, _DVSBSTRIDE)
#घोषणा DVSPOS(pipe) _MMIO_PIPE(pipe, _DVSAPOS, _DVSBPOS)
#घोषणा DVSSURF(pipe) _MMIO_PIPE(pipe, _DVSASURF, _DVSBSURF)
#घोषणा DVSKEYMAX(pipe) _MMIO_PIPE(pipe, _DVSAKEYMAXVAL, _DVSBKEYMAXVAL)
#घोषणा DVSSIZE(pipe) _MMIO_PIPE(pipe, _DVSASIZE, _DVSBSIZE)
#घोषणा DVSSCALE(pipe) _MMIO_PIPE(pipe, _DVSASCALE, _DVSBSCALE)
#घोषणा DVSTILखातापूर्णF(pipe) _MMIO_PIPE(pipe, _DVSATILखातापूर्णF, _DVSBTILखातापूर्णF)
#घोषणा DVSKEYVAL(pipe) _MMIO_PIPE(pipe, _DVSAKEYVAL, _DVSBKEYVAL)
#घोषणा DVSKEYMSK(pipe) _MMIO_PIPE(pipe, _DVSAKEYMSK, _DVSBKEYMSK)
#घोषणा DVSSURFLIVE(pipe) _MMIO_PIPE(pipe, _DVSASURFLIVE, _DVSBSURFLIVE)
#घोषणा DVSGAMC_G4X(pipe, i) _MMIO(_PIPE(pipe, _DVSAGAMC_G4X, _DVSBGAMC_G4X) + (5 - (i)) * 4) /* 6 x u0.8 */
#घोषणा DVSGAMC_ILK(pipe, i) _MMIO(_PIPE(pipe, _DVSAGAMC_ILK, _DVSBGAMC_ILK) + (i) * 4) /* 16 x u0.10 */
#घोषणा DVSGAMCMAX_ILK(pipe, i) _MMIO(_PIPE(pipe, _DVSAGAMCMAX_ILK, _DVSBGAMCMAX_ILK) + (i) * 4) /* 3 x u1.10 */

#घोषणा _SPRA_CTL		0x70280
#घोषणा   SPRITE_ENABLE			(1 << 31)
#घोषणा   SPRITE_GAMMA_ENABLE		(1 << 30)
#घोषणा   SPRITE_YUV_RANGE_CORRECTION_DISABLE	(1 << 28)
#घोषणा   SPRITE_PIXFORMAT_MASK		(7 << 25)
#घोषणा   SPRITE_FORMAT_YUV422		(0 << 25)
#घोषणा   SPRITE_FORMAT_RGBX101010	(1 << 25)
#घोषणा   SPRITE_FORMAT_RGBX888		(2 << 25)
#घोषणा   SPRITE_FORMAT_RGBX161616	(3 << 25)
#घोषणा   SPRITE_FORMAT_YUV444		(4 << 25)
#घोषणा   SPRITE_FORMAT_XR_BGR101010	(5 << 25) /* Extended range */
#घोषणा   SPRITE_PIPE_CSC_ENABLE	(1 << 24)
#घोषणा   SPRITE_SOURCE_KEY		(1 << 22)
#घोषणा   SPRITE_RGB_ORDER_RGBX		(1 << 20) /* only क्रम 888 and 161616 */
#घोषणा   SPRITE_YUV_TO_RGB_CSC_DISABLE	(1 << 19)
#घोषणा   SPRITE_YUV_TO_RGB_CSC_FORMAT_BT709	(1 << 18) /* 0 is BT601 */
#घोषणा   SPRITE_YUV_BYTE_ORDER_MASK	(3 << 16)
#घोषणा   SPRITE_YUV_ORDER_YUYV		(0 << 16)
#घोषणा   SPRITE_YUV_ORDER_UYVY		(1 << 16)
#घोषणा   SPRITE_YUV_ORDER_YVYU		(2 << 16)
#घोषणा   SPRITE_YUV_ORDER_VYUY		(3 << 16)
#घोषणा   SPRITE_ROTATE_180		(1 << 15)
#घोषणा   SPRITE_TRICKLE_FEED_DISABLE	(1 << 14)
#घोषणा   SPRITE_INT_GAMMA_DISABLE	(1 << 13)
#घोषणा   SPRITE_TILED			(1 << 10)
#घोषणा   SPRITE_DEST_KEY		(1 << 2)
#घोषणा _SPRA_LINOFF		0x70284
#घोषणा _SPRA_STRIDE		0x70288
#घोषणा _SPRA_POS		0x7028c
#घोषणा _SPRA_SIZE		0x70290
#घोषणा _SPRA_KEYVAL		0x70294
#घोषणा _SPRA_KEYMSK		0x70298
#घोषणा _SPRA_SURF		0x7029c
#घोषणा _SPRA_KEYMAX		0x702a0
#घोषणा _SPRA_TILखातापूर्णF		0x702a4
#घोषणा _SPRA_OFFSET		0x702a4
#घोषणा _SPRA_SURFLIVE		0x702ac
#घोषणा _SPRA_SCALE		0x70304
#घोषणा   SPRITE_SCALE_ENABLE	(1 << 31)
#घोषणा   SPRITE_FILTER_MASK	(3 << 29)
#घोषणा   SPRITE_FILTER_MEDIUM	(0 << 29)
#घोषणा   SPRITE_FILTER_ENHANCING	(1 << 29)
#घोषणा   SPRITE_FILTER_SOFTENING	(2 << 29)
#घोषणा   SPRITE_VERTICAL_OFFSET_HALF	(1 << 28) /* must be enabled below */
#घोषणा   SPRITE_VERTICAL_OFFSET_ENABLE	(1 << 27)
#घोषणा _SPRA_GAMC		0x70400
#घोषणा _SPRA_GAMC16		0x70440
#घोषणा _SPRA_GAMC17		0x7044c

#घोषणा _SPRB_CTL		0x71280
#घोषणा _SPRB_LINOFF		0x71284
#घोषणा _SPRB_STRIDE		0x71288
#घोषणा _SPRB_POS		0x7128c
#घोषणा _SPRB_SIZE		0x71290
#घोषणा _SPRB_KEYVAL		0x71294
#घोषणा _SPRB_KEYMSK		0x71298
#घोषणा _SPRB_SURF		0x7129c
#घोषणा _SPRB_KEYMAX		0x712a0
#घोषणा _SPRB_TILखातापूर्णF		0x712a4
#घोषणा _SPRB_OFFSET		0x712a4
#घोषणा _SPRB_SURFLIVE		0x712ac
#घोषणा _SPRB_SCALE		0x71304
#घोषणा _SPRB_GAMC		0x71400
#घोषणा _SPRB_GAMC16		0x71440
#घोषणा _SPRB_GAMC17		0x7144c

#घोषणा SPRCTL(pipe) _MMIO_PIPE(pipe, _SPRA_CTL, _SPRB_CTL)
#घोषणा SPRLINOFF(pipe) _MMIO_PIPE(pipe, _SPRA_LINOFF, _SPRB_LINOFF)
#घोषणा SPRSTRIDE(pipe) _MMIO_PIPE(pipe, _SPRA_STRIDE, _SPRB_STRIDE)
#घोषणा SPRPOS(pipe) _MMIO_PIPE(pipe, _SPRA_POS, _SPRB_POS)
#घोषणा SPRSIZE(pipe) _MMIO_PIPE(pipe, _SPRA_SIZE, _SPRB_SIZE)
#घोषणा SPRKEYVAL(pipe) _MMIO_PIPE(pipe, _SPRA_KEYVAL, _SPRB_KEYVAL)
#घोषणा SPRKEYMSK(pipe) _MMIO_PIPE(pipe, _SPRA_KEYMSK, _SPRB_KEYMSK)
#घोषणा SPRSURF(pipe) _MMIO_PIPE(pipe, _SPRA_SURF, _SPRB_SURF)
#घोषणा SPRKEYMAX(pipe) _MMIO_PIPE(pipe, _SPRA_KEYMAX, _SPRB_KEYMAX)
#घोषणा SPRTILखातापूर्णF(pipe) _MMIO_PIPE(pipe, _SPRA_TILखातापूर्णF, _SPRB_TILखातापूर्णF)
#घोषणा SPROFFSET(pipe) _MMIO_PIPE(pipe, _SPRA_OFFSET, _SPRB_OFFSET)
#घोषणा SPRSCALE(pipe) _MMIO_PIPE(pipe, _SPRA_SCALE, _SPRB_SCALE)
#घोषणा SPRGAMC(pipe, i) _MMIO(_PIPE(pipe, _SPRA_GAMC, _SPRB_GAMC) + (i) * 4) /* 16 x u0.10 */
#घोषणा SPRGAMC16(pipe, i) _MMIO(_PIPE(pipe, _SPRA_GAMC16, _SPRB_GAMC16) + (i) * 4) /* 3 x u1.10 */
#घोषणा SPRGAMC17(pipe, i) _MMIO(_PIPE(pipe, _SPRA_GAMC17, _SPRB_GAMC17) + (i) * 4) /* 3 x u2.10 */
#घोषणा SPRSURFLIVE(pipe) _MMIO_PIPE(pipe, _SPRA_SURFLIVE, _SPRB_SURFLIVE)

#घोषणा _SPACNTR		(VLV_DISPLAY_BASE + 0x72180)
#घोषणा   SP_ENABLE			(1 << 31)
#घोषणा   SP_GAMMA_ENABLE		(1 << 30)
#घोषणा   SP_PIXFORMAT_MASK		(0xf << 26)
#घोषणा   SP_FORMAT_YUV422		(0x0 << 26)
#घोषणा   SP_FORMAT_8BPP		(0x2 << 26)
#घोषणा   SP_FORMAT_BGR565		(0x5 << 26)
#घोषणा   SP_FORMAT_BGRX8888		(0x6 << 26)
#घोषणा   SP_FORMAT_BGRA8888		(0x7 << 26)
#घोषणा   SP_FORMAT_RGBX1010102		(0x8 << 26)
#घोषणा   SP_FORMAT_RGBA1010102		(0x9 << 26)
#घोषणा   SP_FORMAT_BGRX1010102		(0xa << 26) /* CHV pipe B */
#घोषणा   SP_FORMAT_BGRA1010102		(0xb << 26) /* CHV pipe B */
#घोषणा   SP_FORMAT_RGBX8888		(0xe << 26)
#घोषणा   SP_FORMAT_RGBA8888		(0xf << 26)
#घोषणा   SP_ALPHA_PREMULTIPLY		(1 << 23) /* CHV pipe B */
#घोषणा   SP_SOURCE_KEY			(1 << 22)
#घोषणा   SP_YUV_FORMAT_BT709		(1 << 18)
#घोषणा   SP_YUV_BYTE_ORDER_MASK	(3 << 16)
#घोषणा   SP_YUV_ORDER_YUYV		(0 << 16)
#घोषणा   SP_YUV_ORDER_UYVY		(1 << 16)
#घोषणा   SP_YUV_ORDER_YVYU		(2 << 16)
#घोषणा   SP_YUV_ORDER_VYUY		(3 << 16)
#घोषणा   SP_ROTATE_180			(1 << 15)
#घोषणा   SP_TILED			(1 << 10)
#घोषणा   SP_MIRROR			(1 << 8) /* CHV pipe B */
#घोषणा _SPALINOFF		(VLV_DISPLAY_BASE + 0x72184)
#घोषणा _SPASTRIDE		(VLV_DISPLAY_BASE + 0x72188)
#घोषणा _SPAPOS			(VLV_DISPLAY_BASE + 0x7218c)
#घोषणा _SPASIZE		(VLV_DISPLAY_BASE + 0x72190)
#घोषणा _SPAKEYMINVAL		(VLV_DISPLAY_BASE + 0x72194)
#घोषणा _SPAKEYMSK		(VLV_DISPLAY_BASE + 0x72198)
#घोषणा _SPASURF		(VLV_DISPLAY_BASE + 0x7219c)
#घोषणा _SPAKEYMAXVAL		(VLV_DISPLAY_BASE + 0x721a0)
#घोषणा _SPATILखातापूर्णF		(VLV_DISPLAY_BASE + 0x721a4)
#घोषणा _SPACONSTALPHA		(VLV_DISPLAY_BASE + 0x721a8)
#घोषणा   SP_CONST_ALPHA_ENABLE		(1 << 31)
#घोषणा _SPACLRC0		(VLV_DISPLAY_BASE + 0x721d0)
#घोषणा   SP_CONTRAST(x)		((x) << 18) /* u3.6 */
#घोषणा   SP_BRIGHTNESS(x)		((x) & 0xff) /* s8 */
#घोषणा _SPACLRC1		(VLV_DISPLAY_BASE + 0x721d4)
#घोषणा   SP_SH_SIN(x)			(((x) & 0x7ff) << 16) /* s4.7 */
#घोषणा   SP_SH_COS(x)			(x) /* u3.7 */
#घोषणा _SPAGAMC		(VLV_DISPLAY_BASE + 0x721e0)

#घोषणा _SPBCNTR		(VLV_DISPLAY_BASE + 0x72280)
#घोषणा _SPBLINOFF		(VLV_DISPLAY_BASE + 0x72284)
#घोषणा _SPBSTRIDE		(VLV_DISPLAY_BASE + 0x72288)
#घोषणा _SPBPOS			(VLV_DISPLAY_BASE + 0x7228c)
#घोषणा _SPBSIZE		(VLV_DISPLAY_BASE + 0x72290)
#घोषणा _SPBKEYMINVAL		(VLV_DISPLAY_BASE + 0x72294)
#घोषणा _SPBKEYMSK		(VLV_DISPLAY_BASE + 0x72298)
#घोषणा _SPBSURF		(VLV_DISPLAY_BASE + 0x7229c)
#घोषणा _SPBKEYMAXVAL		(VLV_DISPLAY_BASE + 0x722a0)
#घोषणा _SPBTILखातापूर्णF		(VLV_DISPLAY_BASE + 0x722a4)
#घोषणा _SPBCONSTALPHA		(VLV_DISPLAY_BASE + 0x722a8)
#घोषणा _SPBCLRC0		(VLV_DISPLAY_BASE + 0x722d0)
#घोषणा _SPBCLRC1		(VLV_DISPLAY_BASE + 0x722d4)
#घोषणा _SPBGAMC		(VLV_DISPLAY_BASE + 0x722e0)

#घोषणा _VLV_SPR(pipe, plane_id, reg_a, reg_b) \
	_PIPE((pipe) * 2 + (plane_id) - PLANE_SPRITE0, (reg_a), (reg_b))
#घोषणा _MMIO_VLV_SPR(pipe, plane_id, reg_a, reg_b) \
	_MMIO(_VLV_SPR((pipe), (plane_id), (reg_a), (reg_b)))

#घोषणा SPCNTR(pipe, plane_id)		_MMIO_VLV_SPR((pipe), (plane_id), _SPACNTR, _SPBCNTR)
#घोषणा SPLINOFF(pipe, plane_id)	_MMIO_VLV_SPR((pipe), (plane_id), _SPALINOFF, _SPBLINOFF)
#घोषणा SPSTRIDE(pipe, plane_id)	_MMIO_VLV_SPR((pipe), (plane_id), _SPASTRIDE, _SPBSTRIDE)
#घोषणा SPPOS(pipe, plane_id)		_MMIO_VLV_SPR((pipe), (plane_id), _SPAPOS, _SPBPOS)
#घोषणा SPSIZE(pipe, plane_id)		_MMIO_VLV_SPR((pipe), (plane_id), _SPASIZE, _SPBSIZE)
#घोषणा SPKEYMINVAL(pipe, plane_id)	_MMIO_VLV_SPR((pipe), (plane_id), _SPAKEYMINVAL, _SPBKEYMINVAL)
#घोषणा SPKEYMSK(pipe, plane_id)	_MMIO_VLV_SPR((pipe), (plane_id), _SPAKEYMSK, _SPBKEYMSK)
#घोषणा SPSURF(pipe, plane_id)		_MMIO_VLV_SPR((pipe), (plane_id), _SPASURF, _SPBSURF)
#घोषणा SPKEYMAXVAL(pipe, plane_id)	_MMIO_VLV_SPR((pipe), (plane_id), _SPAKEYMAXVAL, _SPBKEYMAXVAL)
#घोषणा SPTILखातापूर्णF(pipe, plane_id)	_MMIO_VLV_SPR((pipe), (plane_id), _SPATILखातापूर्णF, _SPBTILखातापूर्णF)
#घोषणा SPCONSTALPHA(pipe, plane_id)	_MMIO_VLV_SPR((pipe), (plane_id), _SPACONSTALPHA, _SPBCONSTALPHA)
#घोषणा SPCLRC0(pipe, plane_id)		_MMIO_VLV_SPR((pipe), (plane_id), _SPACLRC0, _SPBCLRC0)
#घोषणा SPCLRC1(pipe, plane_id)		_MMIO_VLV_SPR((pipe), (plane_id), _SPACLRC1, _SPBCLRC1)
#घोषणा SPGAMC(pipe, plane_id, i)	_MMIO(_VLV_SPR((pipe), (plane_id), _SPAGAMC, _SPBGAMC) + (5 - (i)) * 4) /* 6 x u0.10 */

/*
 * CHV pipe B sprite CSC
 *
 * |cr|   |c0 c1 c2|   |cr + cr_ioff|   |cr_ooff|
 * |yg| = |c3 c4 c5| x |yg + yg_ioff| + |yg_ooff|
 * |cb|   |c6 c7 c8|   |cb + cr_ioff|   |cb_ooff|
 */
#घोषणा _MMIO_CHV_SPCSC(plane_id, reg) \
	_MMIO(VLV_DISPLAY_BASE + ((plane_id) - PLANE_SPRITE0) * 0x1000 + (reg))

#घोषणा SPCSCYGOFF(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d900)
#घोषणा SPCSCCBOFF(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d904)
#घोषणा SPCSCCROFF(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d908)
#घोषणा  SPCSC_OOFF(x)		(((x) & 0x7ff) << 16) /* s11 */
#घोषणा  SPCSC_IOFF(x)		(((x) & 0x7ff) << 0) /* s11 */

#घोषणा SPCSCC01(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d90c)
#घोषणा SPCSCC23(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d910)
#घोषणा SPCSCC45(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d914)
#घोषणा SPCSCC67(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d918)
#घोषणा SPCSCC8(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d91c)
#घोषणा  SPCSC_C1(x)		(((x) & 0x7fff) << 16) /* s3.12 */
#घोषणा  SPCSC_C0(x)		(((x) & 0x7fff) << 0) /* s3.12 */

#घोषणा SPCSCYGICLAMP(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d920)
#घोषणा SPCSCCBICLAMP(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d924)
#घोषणा SPCSCCRICLAMP(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d928)
#घोषणा  SPCSC_IMAX(x)		(((x) & 0x7ff) << 16) /* s11 */
#घोषणा  SPCSC_IMIN(x)		(((x) & 0x7ff) << 0) /* s11 */

#घोषणा SPCSCYGOCLAMP(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d92c)
#घोषणा SPCSCCBOCLAMP(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d930)
#घोषणा SPCSCCROCLAMP(plane_id)	_MMIO_CHV_SPCSC(plane_id, 0x6d934)
#घोषणा  SPCSC_OMAX(x)		((x) << 16) /* u10 */
#घोषणा  SPCSC_OMIN(x)		((x) << 0) /* u10 */

/* Skylake plane रेजिस्टरs */

#घोषणा _PLANE_CTL_1_A				0x70180
#घोषणा _PLANE_CTL_2_A				0x70280
#घोषणा _PLANE_CTL_3_A				0x70380
#घोषणा   PLANE_CTL_ENABLE			(1 << 31)
#घोषणा   PLANE_CTL_PIPE_GAMMA_ENABLE		(1 << 30)   /* Pre-GLK */
#घोषणा   PLANE_CTL_YUV_RANGE_CORRECTION_DISABLE	(1 << 28)
/*
 * ICL+ uses the same PLANE_CTL_FORMAT bits, but the field definition
 * expanded to include bit 23 as well. However, the shअगरt-24 based values
 * correctly map to the same क्रमmats in ICL, as दीर्घ as bit 23 is set to 0
 */
#घोषणा   PLANE_CTL_FORMAT_MASK			(0xf << 24)
#घोषणा   PLANE_CTL_FORMAT_YUV422		(0 << 24)
#घोषणा   PLANE_CTL_FORMAT_NV12			(1 << 24)
#घोषणा   PLANE_CTL_FORMAT_XRGB_2101010		(2 << 24)
#घोषणा   PLANE_CTL_FORMAT_P010			(3 << 24)
#घोषणा   PLANE_CTL_FORMAT_XRGB_8888		(4 << 24)
#घोषणा   PLANE_CTL_FORMAT_P012			(5 << 24)
#घोषणा   PLANE_CTL_FORMAT_XRGB_16161616F	(6 << 24)
#घोषणा   PLANE_CTL_FORMAT_P016			(7 << 24)
#घोषणा   PLANE_CTL_FORMAT_XYUV			(8 << 24)
#घोषणा   PLANE_CTL_FORMAT_INDEXED		(12 << 24)
#घोषणा   PLANE_CTL_FORMAT_RGB_565		(14 << 24)
#घोषणा   ICL_PLANE_CTL_FORMAT_MASK		(0x1f << 23)
#घोषणा   PLANE_CTL_PIPE_CSC_ENABLE		(1 << 23) /* Pre-GLK */
#घोषणा   PLANE_CTL_FORMAT_Y210                 (1 << 23)
#घोषणा   PLANE_CTL_FORMAT_Y212                 (3 << 23)
#घोषणा   PLANE_CTL_FORMAT_Y216                 (5 << 23)
#घोषणा   PLANE_CTL_FORMAT_Y410                 (7 << 23)
#घोषणा   PLANE_CTL_FORMAT_Y412                 (9 << 23)
#घोषणा   PLANE_CTL_FORMAT_Y416                 (0xb << 23)
#घोषणा   PLANE_CTL_KEY_ENABLE_MASK		(0x3 << 21)
#घोषणा   PLANE_CTL_KEY_ENABLE_SOURCE		(1 << 21)
#घोषणा   PLANE_CTL_KEY_ENABLE_DESTINATION	(2 << 21)
#घोषणा   PLANE_CTL_ORDER_BGRX			(0 << 20)
#घोषणा   PLANE_CTL_ORDER_RGBX			(1 << 20)
#घोषणा   PLANE_CTL_YUV420_Y_PLANE		(1 << 19)
#घोषणा   PLANE_CTL_YUV_TO_RGB_CSC_FORMAT_BT709	(1 << 18)
#घोषणा   PLANE_CTL_YUV422_ORDER_MASK		(0x3 << 16)
#घोषणा   PLANE_CTL_YUV422_YUYV			(0 << 16)
#घोषणा   PLANE_CTL_YUV422_UYVY			(1 << 16)
#घोषणा   PLANE_CTL_YUV422_YVYU			(2 << 16)
#घोषणा   PLANE_CTL_YUV422_VYUY			(3 << 16)
#घोषणा   PLANE_CTL_RENDER_DECOMPRESSION_ENABLE	(1 << 15)
#घोषणा   PLANE_CTL_TRICKLE_FEED_DISABLE	(1 << 14)
#घोषणा   PLANE_CTL_CLEAR_COLOR_DISABLE		(1 << 13) /* TGL+ */
#घोषणा   PLANE_CTL_PLANE_GAMMA_DISABLE		(1 << 13) /* Pre-GLK */
#घोषणा   PLANE_CTL_TILED_MASK			(0x7 << 10)
#घोषणा   PLANE_CTL_TILED_LINEAR		(0 << 10)
#घोषणा   PLANE_CTL_TILED_X			(1 << 10)
#घोषणा   PLANE_CTL_TILED_Y			(4 << 10)
#घोषणा   PLANE_CTL_TILED_YF			(5 << 10)
#घोषणा   PLANE_CTL_ASYNC_FLIP			(1 << 9)
#घोषणा   PLANE_CTL_FLIP_HORIZONTAL		(1 << 8)
#घोषणा   PLANE_CTL_MEDIA_DECOMPRESSION_ENABLE	(1 << 4) /* TGL+ */
#घोषणा   PLANE_CTL_ALPHA_MASK			(0x3 << 4) /* Pre-GLK */
#घोषणा   PLANE_CTL_ALPHA_DISABLE		(0 << 4)
#घोषणा   PLANE_CTL_ALPHA_SW_PREMULTIPLY	(2 << 4)
#घोषणा   PLANE_CTL_ALPHA_HW_PREMULTIPLY	(3 << 4)
#घोषणा   PLANE_CTL_ROTATE_MASK			0x3
#घोषणा   PLANE_CTL_ROTATE_0			0x0
#घोषणा   PLANE_CTL_ROTATE_90			0x1
#घोषणा   PLANE_CTL_ROTATE_180			0x2
#घोषणा   PLANE_CTL_ROTATE_270			0x3
#घोषणा _PLANE_STRIDE_1_A			0x70188
#घोषणा _PLANE_STRIDE_2_A			0x70288
#घोषणा _PLANE_STRIDE_3_A			0x70388
#घोषणा _PLANE_POS_1_A				0x7018c
#घोषणा _PLANE_POS_2_A				0x7028c
#घोषणा _PLANE_POS_3_A				0x7038c
#घोषणा _PLANE_SIZE_1_A				0x70190
#घोषणा _PLANE_SIZE_2_A				0x70290
#घोषणा _PLANE_SIZE_3_A				0x70390
#घोषणा _PLANE_SURF_1_A				0x7019c
#घोषणा _PLANE_SURF_2_A				0x7029c
#घोषणा _PLANE_SURF_3_A				0x7039c
#घोषणा _PLANE_OFFSET_1_A			0x701a4
#घोषणा _PLANE_OFFSET_2_A			0x702a4
#घोषणा _PLANE_OFFSET_3_A			0x703a4
#घोषणा _PLANE_KEYVAL_1_A			0x70194
#घोषणा _PLANE_KEYVAL_2_A			0x70294
#घोषणा _PLANE_KEYMSK_1_A			0x70198
#घोषणा _PLANE_KEYMSK_2_A			0x70298
#घोषणा  PLANE_KEYMSK_ALPHA_ENABLE		(1 << 31)
#घोषणा _PLANE_KEYMAX_1_A			0x701a0
#घोषणा _PLANE_KEYMAX_2_A			0x702a0
#घोषणा  PLANE_KEYMAX_ALPHA(a)			((a) << 24)
#घोषणा _PLANE_CC_VAL_1_A			0x701b4
#घोषणा _PLANE_CC_VAL_2_A			0x702b4
#घोषणा _PLANE_AUX_DIST_1_A			0x701c0
#घोषणा _PLANE_AUX_DIST_2_A			0x702c0
#घोषणा _PLANE_AUX_OFFSET_1_A			0x701c4
#घोषणा _PLANE_AUX_OFFSET_2_A			0x702c4
#घोषणा _PLANE_CUS_CTL_1_A			0x701c8
#घोषणा _PLANE_CUS_CTL_2_A			0x702c8
#घोषणा  PLANE_CUS_ENABLE			(1 << 31)
#घोषणा  PLANE_CUS_PLANE_4_RKL			(0 << 30)
#घोषणा  PLANE_CUS_PLANE_5_RKL			(1 << 30)
#घोषणा  PLANE_CUS_PLANE_6			(0 << 30)
#घोषणा  PLANE_CUS_PLANE_7			(1 << 30)
#घोषणा  PLANE_CUS_HPHASE_SIGN_NEGATIVE		(1 << 19)
#घोषणा  PLANE_CUS_HPHASE_0			(0 << 16)
#घोषणा  PLANE_CUS_HPHASE_0_25			(1 << 16)
#घोषणा  PLANE_CUS_HPHASE_0_5			(2 << 16)
#घोषणा  PLANE_CUS_VPHASE_SIGN_NEGATIVE		(1 << 15)
#घोषणा  PLANE_CUS_VPHASE_0			(0 << 12)
#घोषणा  PLANE_CUS_VPHASE_0_25			(1 << 12)
#घोषणा  PLANE_CUS_VPHASE_0_5			(2 << 12)
#घोषणा _PLANE_COLOR_CTL_1_A			0x701CC /* GLK+ */
#घोषणा _PLANE_COLOR_CTL_2_A			0x702CC /* GLK+ */
#घोषणा _PLANE_COLOR_CTL_3_A			0x703CC /* GLK+ */
#घोषणा   PLANE_COLOR_PIPE_GAMMA_ENABLE		(1 << 30) /* Pre-ICL */
#घोषणा   PLANE_COLOR_YUV_RANGE_CORRECTION_DISABLE	(1 << 28)
#घोषणा   PLANE_COLOR_INPUT_CSC_ENABLE		(1 << 20) /* ICL+ */
#घोषणा   PLANE_COLOR_PIPE_CSC_ENABLE		(1 << 23) /* Pre-ICL */
#घोषणा   PLANE_COLOR_CSC_MODE_BYPASS			(0 << 17)
#घोषणा   PLANE_COLOR_CSC_MODE_YUV601_TO_RGB601		(1 << 17)
#घोषणा   PLANE_COLOR_CSC_MODE_YUV709_TO_RGB709		(2 << 17)
#घोषणा   PLANE_COLOR_CSC_MODE_YUV2020_TO_RGB2020	(3 << 17)
#घोषणा   PLANE_COLOR_CSC_MODE_RGB709_TO_RGB2020	(4 << 17)
#घोषणा   PLANE_COLOR_PLANE_GAMMA_DISABLE	(1 << 13)
#घोषणा   PLANE_COLOR_ALPHA_MASK		(0x3 << 4)
#घोषणा   PLANE_COLOR_ALPHA_DISABLE		(0 << 4)
#घोषणा   PLANE_COLOR_ALPHA_SW_PREMULTIPLY	(2 << 4)
#घोषणा   PLANE_COLOR_ALPHA_HW_PREMULTIPLY	(3 << 4)
#घोषणा _PLANE_BUF_CFG_1_A			0x7027c
#घोषणा _PLANE_BUF_CFG_2_A			0x7037c
#घोषणा _PLANE_NV12_BUF_CFG_1_A		0x70278
#घोषणा _PLANE_NV12_BUF_CFG_2_A		0x70378

#घोषणा _PLANE_CC_VAL_1_B			0x711b4
#घोषणा _PLANE_CC_VAL_2_B			0x712b4
#घोषणा _PLANE_CC_VAL_1(pipe)	_PIPE(pipe, _PLANE_CC_VAL_1_A, _PLANE_CC_VAL_1_B)
#घोषणा _PLANE_CC_VAL_2(pipe)	_PIPE(pipe, _PLANE_CC_VAL_2_A, _PLANE_CC_VAL_2_B)
#घोषणा PLANE_CC_VAL(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_CC_VAL_1(pipe), _PLANE_CC_VAL_2(pipe))

/* Input CSC Register Definitions */
#घोषणा _PLANE_INPUT_CSC_RY_GY_1_A	0x701E0
#घोषणा _PLANE_INPUT_CSC_RY_GY_2_A	0x702E0

#घोषणा _PLANE_INPUT_CSC_RY_GY_1_B	0x711E0
#घोषणा _PLANE_INPUT_CSC_RY_GY_2_B	0x712E0

#घोषणा _PLANE_INPUT_CSC_RY_GY_1(pipe)	\
	_PIPE(pipe, _PLANE_INPUT_CSC_RY_GY_1_A, \
	     _PLANE_INPUT_CSC_RY_GY_1_B)
#घोषणा _PLANE_INPUT_CSC_RY_GY_2(pipe)	\
	_PIPE(pipe, _PLANE_INPUT_CSC_RY_GY_2_A, \
	     _PLANE_INPUT_CSC_RY_GY_2_B)

#घोषणा PLANE_INPUT_CSC_COEFF(pipe, plane, index)	\
	_MMIO_PLANE(plane, _PLANE_INPUT_CSC_RY_GY_1(pipe) +  (index) * 4, \
		    _PLANE_INPUT_CSC_RY_GY_2(pipe) + (index) * 4)

#घोषणा _PLANE_INPUT_CSC_PRखातापूर्णF_HI_1_A		0x701F8
#घोषणा _PLANE_INPUT_CSC_PRखातापूर्णF_HI_2_A		0x702F8

#घोषणा _PLANE_INPUT_CSC_PRखातापूर्णF_HI_1_B		0x711F8
#घोषणा _PLANE_INPUT_CSC_PRखातापूर्णF_HI_2_B		0x712F8

#घोषणा _PLANE_INPUT_CSC_PRखातापूर्णF_HI_1(pipe)	\
	_PIPE(pipe, _PLANE_INPUT_CSC_PRखातापूर्णF_HI_1_A, \
	     _PLANE_INPUT_CSC_PRखातापूर्णF_HI_1_B)
#घोषणा _PLANE_INPUT_CSC_PRखातापूर्णF_HI_2(pipe)	\
	_PIPE(pipe, _PLANE_INPUT_CSC_PRखातापूर्णF_HI_2_A, \
	     _PLANE_INPUT_CSC_PRखातापूर्णF_HI_2_B)
#घोषणा PLANE_INPUT_CSC_PRखातापूर्णF(pipe, plane, index)	\
	_MMIO_PLANE(plane, _PLANE_INPUT_CSC_PRखातापूर्णF_HI_1(pipe) + (index) * 4, \
		    _PLANE_INPUT_CSC_PRखातापूर्णF_HI_2(pipe) + (index) * 4)

#घोषणा _PLANE_INPUT_CSC_POSTOFF_HI_1_A		0x70204
#घोषणा _PLANE_INPUT_CSC_POSTOFF_HI_2_A		0x70304

#घोषणा _PLANE_INPUT_CSC_POSTOFF_HI_1_B		0x71204
#घोषणा _PLANE_INPUT_CSC_POSTOFF_HI_2_B		0x71304

#घोषणा _PLANE_INPUT_CSC_POSTOFF_HI_1(pipe)	\
	_PIPE(pipe, _PLANE_INPUT_CSC_POSTOFF_HI_1_A, \
	     _PLANE_INPUT_CSC_POSTOFF_HI_1_B)
#घोषणा _PLANE_INPUT_CSC_POSTOFF_HI_2(pipe)	\
	_PIPE(pipe, _PLANE_INPUT_CSC_POSTOFF_HI_2_A, \
	     _PLANE_INPUT_CSC_POSTOFF_HI_2_B)
#घोषणा PLANE_INPUT_CSC_POSTOFF(pipe, plane, index)	\
	_MMIO_PLANE(plane, _PLANE_INPUT_CSC_POSTOFF_HI_1(pipe) + (index) * 4, \
		    _PLANE_INPUT_CSC_POSTOFF_HI_2(pipe) + (index) * 4)

#घोषणा _PLANE_CTL_1_B				0x71180
#घोषणा _PLANE_CTL_2_B				0x71280
#घोषणा _PLANE_CTL_3_B				0x71380
#घोषणा _PLANE_CTL_1(pipe)	_PIPE(pipe, _PLANE_CTL_1_A, _PLANE_CTL_1_B)
#घोषणा _PLANE_CTL_2(pipe)	_PIPE(pipe, _PLANE_CTL_2_A, _PLANE_CTL_2_B)
#घोषणा _PLANE_CTL_3(pipe)	_PIPE(pipe, _PLANE_CTL_3_A, _PLANE_CTL_3_B)
#घोषणा PLANE_CTL(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_CTL_1(pipe), _PLANE_CTL_2(pipe))

#घोषणा _PLANE_STRIDE_1_B			0x71188
#घोषणा _PLANE_STRIDE_2_B			0x71288
#घोषणा _PLANE_STRIDE_3_B			0x71388
#घोषणा _PLANE_STRIDE_1(pipe)	\
	_PIPE(pipe, _PLANE_STRIDE_1_A, _PLANE_STRIDE_1_B)
#घोषणा _PLANE_STRIDE_2(pipe)	\
	_PIPE(pipe, _PLANE_STRIDE_2_A, _PLANE_STRIDE_2_B)
#घोषणा _PLANE_STRIDE_3(pipe)	\
	_PIPE(pipe, _PLANE_STRIDE_3_A, _PLANE_STRIDE_3_B)
#घोषणा PLANE_STRIDE(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_STRIDE_1(pipe), _PLANE_STRIDE_2(pipe))

#घोषणा _PLANE_POS_1_B				0x7118c
#घोषणा _PLANE_POS_2_B				0x7128c
#घोषणा _PLANE_POS_3_B				0x7138c
#घोषणा _PLANE_POS_1(pipe)	_PIPE(pipe, _PLANE_POS_1_A, _PLANE_POS_1_B)
#घोषणा _PLANE_POS_2(pipe)	_PIPE(pipe, _PLANE_POS_2_A, _PLANE_POS_2_B)
#घोषणा _PLANE_POS_3(pipe)	_PIPE(pipe, _PLANE_POS_3_A, _PLANE_POS_3_B)
#घोषणा PLANE_POS(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_POS_1(pipe), _PLANE_POS_2(pipe))

#घोषणा _PLANE_SIZE_1_B				0x71190
#घोषणा _PLANE_SIZE_2_B				0x71290
#घोषणा _PLANE_SIZE_3_B				0x71390
#घोषणा _PLANE_SIZE_1(pipe)	_PIPE(pipe, _PLANE_SIZE_1_A, _PLANE_SIZE_1_B)
#घोषणा _PLANE_SIZE_2(pipe)	_PIPE(pipe, _PLANE_SIZE_2_A, _PLANE_SIZE_2_B)
#घोषणा _PLANE_SIZE_3(pipe)	_PIPE(pipe, _PLANE_SIZE_3_A, _PLANE_SIZE_3_B)
#घोषणा PLANE_SIZE(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_SIZE_1(pipe), _PLANE_SIZE_2(pipe))

#घोषणा _PLANE_SURF_1_B				0x7119c
#घोषणा _PLANE_SURF_2_B				0x7129c
#घोषणा _PLANE_SURF_3_B				0x7139c
#घोषणा _PLANE_SURF_1(pipe)	_PIPE(pipe, _PLANE_SURF_1_A, _PLANE_SURF_1_B)
#घोषणा _PLANE_SURF_2(pipe)	_PIPE(pipe, _PLANE_SURF_2_A, _PLANE_SURF_2_B)
#घोषणा _PLANE_SURF_3(pipe)	_PIPE(pipe, _PLANE_SURF_3_A, _PLANE_SURF_3_B)
#घोषणा PLANE_SURF(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_SURF_1(pipe), _PLANE_SURF_2(pipe))

#घोषणा _PLANE_OFFSET_1_B			0x711a4
#घोषणा _PLANE_OFFSET_2_B			0x712a4
#घोषणा _PLANE_OFFSET_1(pipe) _PIPE(pipe, _PLANE_OFFSET_1_A, _PLANE_OFFSET_1_B)
#घोषणा _PLANE_OFFSET_2(pipe) _PIPE(pipe, _PLANE_OFFSET_2_A, _PLANE_OFFSET_2_B)
#घोषणा PLANE_OFFSET(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_OFFSET_1(pipe), _PLANE_OFFSET_2(pipe))

#घोषणा _PLANE_KEYVAL_1_B			0x71194
#घोषणा _PLANE_KEYVAL_2_B			0x71294
#घोषणा _PLANE_KEYVAL_1(pipe) _PIPE(pipe, _PLANE_KEYVAL_1_A, _PLANE_KEYVAL_1_B)
#घोषणा _PLANE_KEYVAL_2(pipe) _PIPE(pipe, _PLANE_KEYVAL_2_A, _PLANE_KEYVAL_2_B)
#घोषणा PLANE_KEYVAL(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_KEYVAL_1(pipe), _PLANE_KEYVAL_2(pipe))

#घोषणा _PLANE_KEYMSK_1_B			0x71198
#घोषणा _PLANE_KEYMSK_2_B			0x71298
#घोषणा _PLANE_KEYMSK_1(pipe) _PIPE(pipe, _PLANE_KEYMSK_1_A, _PLANE_KEYMSK_1_B)
#घोषणा _PLANE_KEYMSK_2(pipe) _PIPE(pipe, _PLANE_KEYMSK_2_A, _PLANE_KEYMSK_2_B)
#घोषणा PLANE_KEYMSK(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_KEYMSK_1(pipe), _PLANE_KEYMSK_2(pipe))

#घोषणा _PLANE_KEYMAX_1_B			0x711a0
#घोषणा _PLANE_KEYMAX_2_B			0x712a0
#घोषणा _PLANE_KEYMAX_1(pipe) _PIPE(pipe, _PLANE_KEYMAX_1_A, _PLANE_KEYMAX_1_B)
#घोषणा _PLANE_KEYMAX_2(pipe) _PIPE(pipe, _PLANE_KEYMAX_2_A, _PLANE_KEYMAX_2_B)
#घोषणा PLANE_KEYMAX(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_KEYMAX_1(pipe), _PLANE_KEYMAX_2(pipe))

#घोषणा _PLANE_BUF_CFG_1_B			0x7127c
#घोषणा _PLANE_BUF_CFG_2_B			0x7137c
#घोषणा  DDB_ENTRY_MASK				0x7FF /* skl+: 10 bits, icl+ 11 bits */
#घोषणा  DDB_ENTRY_END_SHIFT			16
#घोषणा _PLANE_BUF_CFG_1(pipe)	\
	_PIPE(pipe, _PLANE_BUF_CFG_1_A, _PLANE_BUF_CFG_1_B)
#घोषणा _PLANE_BUF_CFG_2(pipe)	\
	_PIPE(pipe, _PLANE_BUF_CFG_2_A, _PLANE_BUF_CFG_2_B)
#घोषणा PLANE_BUF_CFG(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_BUF_CFG_1(pipe), _PLANE_BUF_CFG_2(pipe))

#घोषणा _PLANE_NV12_BUF_CFG_1_B		0x71278
#घोषणा _PLANE_NV12_BUF_CFG_2_B		0x71378
#घोषणा _PLANE_NV12_BUF_CFG_1(pipe)	\
	_PIPE(pipe, _PLANE_NV12_BUF_CFG_1_A, _PLANE_NV12_BUF_CFG_1_B)
#घोषणा _PLANE_NV12_BUF_CFG_2(pipe)	\
	_PIPE(pipe, _PLANE_NV12_BUF_CFG_2_A, _PLANE_NV12_BUF_CFG_2_B)
#घोषणा PLANE_NV12_BUF_CFG(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_NV12_BUF_CFG_1(pipe), _PLANE_NV12_BUF_CFG_2(pipe))

#घोषणा _PLANE_AUX_DIST_1_B		0x711c0
#घोषणा _PLANE_AUX_DIST_2_B		0x712c0
#घोषणा _PLANE_AUX_DIST_1(pipe) \
			_PIPE(pipe, _PLANE_AUX_DIST_1_A, _PLANE_AUX_DIST_1_B)
#घोषणा _PLANE_AUX_DIST_2(pipe) \
			_PIPE(pipe, _PLANE_AUX_DIST_2_A, _PLANE_AUX_DIST_2_B)
#घोषणा PLANE_AUX_DIST(pipe, plane)     \
	_MMIO_PLANE(plane, _PLANE_AUX_DIST_1(pipe), _PLANE_AUX_DIST_2(pipe))

#घोषणा _PLANE_AUX_OFFSET_1_B		0x711c4
#घोषणा _PLANE_AUX_OFFSET_2_B		0x712c4
#घोषणा _PLANE_AUX_OFFSET_1(pipe)       \
		_PIPE(pipe, _PLANE_AUX_OFFSET_1_A, _PLANE_AUX_OFFSET_1_B)
#घोषणा _PLANE_AUX_OFFSET_2(pipe)       \
		_PIPE(pipe, _PLANE_AUX_OFFSET_2_A, _PLANE_AUX_OFFSET_2_B)
#घोषणा PLANE_AUX_OFFSET(pipe, plane)   \
	_MMIO_PLANE(plane, _PLANE_AUX_OFFSET_1(pipe), _PLANE_AUX_OFFSET_2(pipe))

#घोषणा _PLANE_CUS_CTL_1_B		0x711c8
#घोषणा _PLANE_CUS_CTL_2_B		0x712c8
#घोषणा _PLANE_CUS_CTL_1(pipe)       \
		_PIPE(pipe, _PLANE_CUS_CTL_1_A, _PLANE_CUS_CTL_1_B)
#घोषणा _PLANE_CUS_CTL_2(pipe)       \
		_PIPE(pipe, _PLANE_CUS_CTL_2_A, _PLANE_CUS_CTL_2_B)
#घोषणा PLANE_CUS_CTL(pipe, plane)   \
	_MMIO_PLANE(plane, _PLANE_CUS_CTL_1(pipe), _PLANE_CUS_CTL_2(pipe))

#घोषणा _PLANE_COLOR_CTL_1_B			0x711CC
#घोषणा _PLANE_COLOR_CTL_2_B			0x712CC
#घोषणा _PLANE_COLOR_CTL_3_B			0x713CC
#घोषणा _PLANE_COLOR_CTL_1(pipe)	\
	_PIPE(pipe, _PLANE_COLOR_CTL_1_A, _PLANE_COLOR_CTL_1_B)
#घोषणा _PLANE_COLOR_CTL_2(pipe)	\
	_PIPE(pipe, _PLANE_COLOR_CTL_2_A, _PLANE_COLOR_CTL_2_B)
#घोषणा PLANE_COLOR_CTL(pipe, plane)	\
	_MMIO_PLANE(plane, _PLANE_COLOR_CTL_1(pipe), _PLANE_COLOR_CTL_2(pipe))

#घोषणा _SEL_FETCH_PLANE_BASE_1_A		0x70890
#घोषणा _SEL_FETCH_PLANE_BASE_2_A		0x708B0
#घोषणा _SEL_FETCH_PLANE_BASE_3_A		0x708D0
#घोषणा _SEL_FETCH_PLANE_BASE_4_A		0x708F0
#घोषणा _SEL_FETCH_PLANE_BASE_5_A		0x70920
#घोषणा _SEL_FETCH_PLANE_BASE_6_A		0x70940
#घोषणा _SEL_FETCH_PLANE_BASE_7_A		0x70960
#घोषणा _SEL_FETCH_PLANE_BASE_CUR_A		0x70880
#घोषणा _SEL_FETCH_PLANE_BASE_1_B		0x70990

#घोषणा _SEL_FETCH_PLANE_BASE_A(plane) _PICK(plane, \
					     _SEL_FETCH_PLANE_BASE_1_A, \
					     _SEL_FETCH_PLANE_BASE_2_A, \
					     _SEL_FETCH_PLANE_BASE_3_A, \
					     _SEL_FETCH_PLANE_BASE_4_A, \
					     _SEL_FETCH_PLANE_BASE_5_A, \
					     _SEL_FETCH_PLANE_BASE_6_A, \
					     _SEL_FETCH_PLANE_BASE_7_A, \
					     _SEL_FETCH_PLANE_BASE_CUR_A)
#घोषणा _SEL_FETCH_PLANE_BASE_1(pipe) _PIPE(pipe, _SEL_FETCH_PLANE_BASE_1_A, _SEL_FETCH_PLANE_BASE_1_B)
#घोषणा _SEL_FETCH_PLANE_BASE(pipe, plane) (_SEL_FETCH_PLANE_BASE_1(pipe) - \
					    _SEL_FETCH_PLANE_BASE_1_A + \
					    _SEL_FETCH_PLANE_BASE_A(plane))

#घोषणा _SEL_FETCH_PLANE_CTL_1_A		0x70890
#घोषणा PLANE_SEL_FETCH_CTL(pipe, plane) _MMIO(_SEL_FETCH_PLANE_BASE(pipe, plane) + \
					       _SEL_FETCH_PLANE_CTL_1_A - \
					       _SEL_FETCH_PLANE_BASE_1_A)
#घोषणा PLANE_SEL_FETCH_CTL_ENABLE		REG_BIT(31)

#घोषणा _SEL_FETCH_PLANE_POS_1_A		0x70894
#घोषणा PLANE_SEL_FETCH_POS(pipe, plane) _MMIO(_SEL_FETCH_PLANE_BASE(pipe, plane) + \
					       _SEL_FETCH_PLANE_POS_1_A - \
					       _SEL_FETCH_PLANE_BASE_1_A)

#घोषणा _SEL_FETCH_PLANE_SIZE_1_A		0x70898
#घोषणा PLANE_SEL_FETCH_SIZE(pipe, plane) _MMIO(_SEL_FETCH_PLANE_BASE(pipe, plane) + \
						_SEL_FETCH_PLANE_SIZE_1_A - \
						_SEL_FETCH_PLANE_BASE_1_A)

#घोषणा _SEL_FETCH_PLANE_OFFSET_1_A		0x7089C
#घोषणा PLANE_SEL_FETCH_OFFSET(pipe, plane) _MMIO(_SEL_FETCH_PLANE_BASE(pipe, plane) + \
						  _SEL_FETCH_PLANE_OFFSET_1_A - \
						  _SEL_FETCH_PLANE_BASE_1_A)

/* SKL new cursor रेजिस्टरs */
#घोषणा _CUR_BUF_CFG_A				0x7017c
#घोषणा _CUR_BUF_CFG_B				0x7117c
#घोषणा CUR_BUF_CFG(pipe)	_MMIO_PIPE(pipe, _CUR_BUF_CFG_A, _CUR_BUF_CFG_B)

/* VBIOS regs */
#घोषणा VGACNTRL		_MMIO(0x71400)
# define VGA_DISP_DISABLE			(1 << 31)
# define VGA_2X_MODE				(1 << 30)
# define VGA_PIPE_B_SELECT			(1 << 29)

#घोषणा VLV_VGACNTRL		_MMIO(VLV_DISPLAY_BASE + 0x71400)

/* Ironlake */

#घोषणा CPU_VGACNTRL	_MMIO(0x41000)

#घोषणा DIGITAL_PORT_HOTPLUG_CNTRL	_MMIO(0x44030)
#घोषणा  DIGITAL_PORTA_HOTPLUG_ENABLE		(1 << 4)
#घोषणा  DIGITAL_PORTA_PULSE_DURATION_2ms	(0 << 2) /* pre-HSW */
#घोषणा  DIGITAL_PORTA_PULSE_DURATION_4_5ms	(1 << 2) /* pre-HSW */
#घोषणा  DIGITAL_PORTA_PULSE_DURATION_6ms	(2 << 2) /* pre-HSW */
#घोषणा  DIGITAL_PORTA_PULSE_DURATION_100ms	(3 << 2) /* pre-HSW */
#घोषणा  DIGITAL_PORTA_PULSE_DURATION_MASK	(3 << 2) /* pre-HSW */
#घोषणा  DIGITAL_PORTA_HOTPLUG_STATUS_MASK	(3 << 0)
#घोषणा  DIGITAL_PORTA_HOTPLUG_NO_DETECT	(0 << 0)
#घोषणा  DIGITAL_PORTA_HOTPLUG_SHORT_DETECT	(1 << 0)
#घोषणा  DIGITAL_PORTA_HOTPLUG_LONG_DETECT	(2 << 0)

/* refresh rate hardware control */
#घोषणा RR_HW_CTL       _MMIO(0x45300)
#घोषणा  RR_HW_LOW_POWER_FRAMES_MASK    0xff
#घोषणा  RR_HW_HIGH_POWER_FRAMES_MASK   0xff00

#घोषणा FDI_PLL_BIOS_0  _MMIO(0x46000)
#घोषणा  FDI_PLL_FB_CLOCK_MASK  0xff
#घोषणा FDI_PLL_BIOS_1  _MMIO(0x46004)
#घोषणा FDI_PLL_BIOS_2  _MMIO(0x46008)
#घोषणा DISPLAY_PORT_PLL_BIOS_0         _MMIO(0x4600c)
#घोषणा DISPLAY_PORT_PLL_BIOS_1         _MMIO(0x46010)
#घोषणा DISPLAY_PORT_PLL_BIOS_2         _MMIO(0x46014)

#घोषणा PCH_3DCGDIS0		_MMIO(0x46020)
# define MARIUNIT_CLOCK_GATE_DISABLE		(1 << 18)
# define SVSMUNIT_CLOCK_GATE_DISABLE		(1 << 1)

#घोषणा PCH_3DCGDIS1		_MMIO(0x46024)
# define VFMUNIT_CLOCK_GATE_DISABLE		(1 << 11)

#घोषणा FDI_PLL_FREQ_CTL        _MMIO(0x46030)
#घोषणा  FDI_PLL_FREQ_CHANGE_REQUEST    (1 << 24)
#घोषणा  FDI_PLL_FREQ_LOCK_LIMIT_MASK   0xfff00
#घोषणा  FDI_PLL_FREQ_DISABLE_COUNT_LIMIT_MASK  0xff


#घोषणा _PIPEA_DATA_M1		0x60030
#घोषणा  PIPE_DATA_M1_OFFSET    0
#घोषणा _PIPEA_DATA_N1		0x60034
#घोषणा  PIPE_DATA_N1_OFFSET    0

#घोषणा _PIPEA_DATA_M2		0x60038
#घोषणा  PIPE_DATA_M2_OFFSET    0
#घोषणा _PIPEA_DATA_N2		0x6003c
#घोषणा  PIPE_DATA_N2_OFFSET    0

#घोषणा _PIPEA_LINK_M1		0x60040
#घोषणा  PIPE_LINK_M1_OFFSET    0
#घोषणा _PIPEA_LINK_N1		0x60044
#घोषणा  PIPE_LINK_N1_OFFSET    0

#घोषणा _PIPEA_LINK_M2		0x60048
#घोषणा  PIPE_LINK_M2_OFFSET    0
#घोषणा _PIPEA_LINK_N2		0x6004c
#घोषणा  PIPE_LINK_N2_OFFSET    0

/* PIPEB timing regs are same start from 0x61000 */

#घोषणा _PIPEB_DATA_M1		0x61030
#घोषणा _PIPEB_DATA_N1		0x61034
#घोषणा _PIPEB_DATA_M2		0x61038
#घोषणा _PIPEB_DATA_N2		0x6103c
#घोषणा _PIPEB_LINK_M1		0x61040
#घोषणा _PIPEB_LINK_N1		0x61044
#घोषणा _PIPEB_LINK_M2		0x61048
#घोषणा _PIPEB_LINK_N2		0x6104c

#घोषणा PIPE_DATA_M1(tran) _MMIO_TRANS2(tran, _PIPEA_DATA_M1)
#घोषणा PIPE_DATA_N1(tran) _MMIO_TRANS2(tran, _PIPEA_DATA_N1)
#घोषणा PIPE_DATA_M2(tran) _MMIO_TRANS2(tran, _PIPEA_DATA_M2)
#घोषणा PIPE_DATA_N2(tran) _MMIO_TRANS2(tran, _PIPEA_DATA_N2)
#घोषणा PIPE_LINK_M1(tran) _MMIO_TRANS2(tran, _PIPEA_LINK_M1)
#घोषणा PIPE_LINK_N1(tran) _MMIO_TRANS2(tran, _PIPEA_LINK_N1)
#घोषणा PIPE_LINK_M2(tran) _MMIO_TRANS2(tran, _PIPEA_LINK_M2)
#घोषणा PIPE_LINK_N2(tran) _MMIO_TRANS2(tran, _PIPEA_LINK_N2)

/* CPU panel fitter */
/* IVB+ has 3 fitters, 0 is 7x5 capable, the other two only 3x3 */
#घोषणा _PFA_CTL_1               0x68080
#घोषणा _PFB_CTL_1               0x68880
#घोषणा  PF_ENABLE              (1 << 31)
#घोषणा  PF_PIPE_SEL_MASK_IVB	(3 << 29)
#घोषणा  PF_PIPE_SEL_IVB(pipe)	((pipe) << 29)
#घोषणा  PF_FILTER_MASK		(3 << 23)
#घोषणा  PF_FILTER_PROGRAMMED	(0 << 23)
#घोषणा  PF_FILTER_MED_3x3	(1 << 23)
#घोषणा  PF_FILTER_EDGE_ENHANCE	(2 << 23)
#घोषणा  PF_FILTER_EDGE_SOFTEN	(3 << 23)
#घोषणा _PFA_WIN_SZ		0x68074
#घोषणा _PFB_WIN_SZ		0x68874
#घोषणा _PFA_WIN_POS		0x68070
#घोषणा _PFB_WIN_POS		0x68870
#घोषणा _PFA_VSCALE		0x68084
#घोषणा _PFB_VSCALE		0x68884
#घोषणा _PFA_HSCALE		0x68090
#घोषणा _PFB_HSCALE		0x68890

#घोषणा PF_CTL(pipe)		_MMIO_PIPE(pipe, _PFA_CTL_1, _PFB_CTL_1)
#घोषणा PF_WIN_SZ(pipe)		_MMIO_PIPE(pipe, _PFA_WIN_SZ, _PFB_WIN_SZ)
#घोषणा PF_WIN_POS(pipe)	_MMIO_PIPE(pipe, _PFA_WIN_POS, _PFB_WIN_POS)
#घोषणा PF_VSCALE(pipe)		_MMIO_PIPE(pipe, _PFA_VSCALE, _PFB_VSCALE)
#घोषणा PF_HSCALE(pipe)		_MMIO_PIPE(pipe, _PFA_HSCALE, _PFB_HSCALE)

#घोषणा _PSA_CTL		0x68180
#घोषणा _PSB_CTL		0x68980
#घोषणा PS_ENABLE		(1 << 31)
#घोषणा _PSA_WIN_SZ		0x68174
#घोषणा _PSB_WIN_SZ		0x68974
#घोषणा _PSA_WIN_POS		0x68170
#घोषणा _PSB_WIN_POS		0x68970

#घोषणा PS_CTL(pipe)		_MMIO_PIPE(pipe, _PSA_CTL, _PSB_CTL)
#घोषणा PS_WIN_SZ(pipe)		_MMIO_PIPE(pipe, _PSA_WIN_SZ, _PSB_WIN_SZ)
#घोषणा PS_WIN_POS(pipe)	_MMIO_PIPE(pipe, _PSA_WIN_POS, _PSB_WIN_POS)

/*
 * Skylake scalers
 */
#घोषणा _PS_1A_CTRL      0x68180
#घोषणा _PS_2A_CTRL      0x68280
#घोषणा _PS_1B_CTRL      0x68980
#घोषणा _PS_2B_CTRL      0x68A80
#घोषणा _PS_1C_CTRL      0x69180
#घोषणा PS_SCALER_EN        (1 << 31)
#घोषणा SKL_PS_SCALER_MODE_MASK (3 << 28)
#घोषणा SKL_PS_SCALER_MODE_DYN  (0 << 28)
#घोषणा SKL_PS_SCALER_MODE_HQ  (1 << 28)
#घोषणा SKL_PS_SCALER_MODE_NV12 (2 << 28)
#घोषणा PS_SCALER_MODE_PLANAR (1 << 29)
#घोषणा PS_SCALER_MODE_NORMAL (0 << 29)
#घोषणा PS_PLANE_SEL_MASK  (7 << 25)
#घोषणा PS_PLANE_SEL(plane) (((plane) + 1) << 25)
#घोषणा PS_FILTER_MASK         (3 << 23)
#घोषणा PS_FILTER_MEDIUM       (0 << 23)
#घोषणा PS_FILTER_PROGRAMMED   (1 << 23)
#घोषणा PS_FILTER_EDGE_ENHANCE (2 << 23)
#घोषणा PS_FILTER_BILINEAR     (3 << 23)
#घोषणा PS_VERT3TAP            (1 << 21)
#घोषणा PS_VERT_INT_INVERT_FIELD1 (0 << 20)
#घोषणा PS_VERT_INT_INVERT_FIELD0 (1 << 20)
#घोषणा PS_PWRUP_PROGRESS         (1 << 17)
#घोषणा PS_V_FILTER_BYPASS        (1 << 8)
#घोषणा PS_VADAPT_EN              (1 << 7)
#घोषणा PS_VADAPT_MODE_MASK        (3 << 5)
#घोषणा PS_VADAPT_MODE_LEAST_ADAPT (0 << 5)
#घोषणा PS_VADAPT_MODE_MOD_ADAPT   (1 << 5)
#घोषणा PS_VADAPT_MODE_MOST_ADAPT  (3 << 5)
#घोषणा PS_PLANE_Y_SEL_MASK  (7 << 5)
#घोषणा PS_PLANE_Y_SEL(plane) (((plane) + 1) << 5)
#घोषणा PS_Y_VERT_FILTER_SELECT(set)   ((set) << 4)
#घोषणा PS_Y_HORZ_FILTER_SELECT(set)   ((set) << 3)
#घोषणा PS_UV_VERT_FILTER_SELECT(set)  ((set) << 2)
#घोषणा PS_UV_HORZ_FILTER_SELECT(set)  ((set) << 1)

#घोषणा _PS_PWR_GATE_1A     0x68160
#घोषणा _PS_PWR_GATE_2A     0x68260
#घोषणा _PS_PWR_GATE_1B     0x68960
#घोषणा _PS_PWR_GATE_2B     0x68A60
#घोषणा _PS_PWR_GATE_1C     0x69160
#घोषणा PS_PWR_GATE_DIS_OVERRIDE       (1 << 31)
#घोषणा PS_PWR_GATE_SETTLING_TIME_32   (0 << 3)
#घोषणा PS_PWR_GATE_SETTLING_TIME_64   (1 << 3)
#घोषणा PS_PWR_GATE_SETTLING_TIME_96   (2 << 3)
#घोषणा PS_PWR_GATE_SETTLING_TIME_128  (3 << 3)
#घोषणा PS_PWR_GATE_SLPEN_8             0
#घोषणा PS_PWR_GATE_SLPEN_16            1
#घोषणा PS_PWR_GATE_SLPEN_24            2
#घोषणा PS_PWR_GATE_SLPEN_32            3

#घोषणा _PS_WIN_POS_1A      0x68170
#घोषणा _PS_WIN_POS_2A      0x68270
#घोषणा _PS_WIN_POS_1B      0x68970
#घोषणा _PS_WIN_POS_2B      0x68A70
#घोषणा _PS_WIN_POS_1C      0x69170

#घोषणा _PS_WIN_SZ_1A       0x68174
#घोषणा _PS_WIN_SZ_2A       0x68274
#घोषणा _PS_WIN_SZ_1B       0x68974
#घोषणा _PS_WIN_SZ_2B       0x68A74
#घोषणा _PS_WIN_SZ_1C       0x69174

#घोषणा _PS_VSCALE_1A       0x68184
#घोषणा _PS_VSCALE_2A       0x68284
#घोषणा _PS_VSCALE_1B       0x68984
#घोषणा _PS_VSCALE_2B       0x68A84
#घोषणा _PS_VSCALE_1C       0x69184

#घोषणा _PS_HSCALE_1A       0x68190
#घोषणा _PS_HSCALE_2A       0x68290
#घोषणा _PS_HSCALE_1B       0x68990
#घोषणा _PS_HSCALE_2B       0x68A90
#घोषणा _PS_HSCALE_1C       0x69190

#घोषणा _PS_VPHASE_1A       0x68188
#घोषणा _PS_VPHASE_2A       0x68288
#घोषणा _PS_VPHASE_1B       0x68988
#घोषणा _PS_VPHASE_2B       0x68A88
#घोषणा _PS_VPHASE_1C       0x69188
#घोषणा  PS_Y_PHASE(x)		((x) << 16)
#घोषणा  PS_UV_RGB_PHASE(x)	((x) << 0)
#घोषणा   PS_PHASE_MASK	(0x7fff << 1) /* u2.13 */
#घोषणा   PS_PHASE_TRIP	(1 << 0)

#घोषणा _PS_HPHASE_1A       0x68194
#घोषणा _PS_HPHASE_2A       0x68294
#घोषणा _PS_HPHASE_1B       0x68994
#घोषणा _PS_HPHASE_2B       0x68A94
#घोषणा _PS_HPHASE_1C       0x69194

#घोषणा _PS_ECC_STAT_1A     0x681D0
#घोषणा _PS_ECC_STAT_2A     0x682D0
#घोषणा _PS_ECC_STAT_1B     0x689D0
#घोषणा _PS_ECC_STAT_2B     0x68AD0
#घोषणा _PS_ECC_STAT_1C     0x691D0

#घोषणा _PS_COEF_SET0_INDEX_1A	   0x68198
#घोषणा _PS_COEF_SET0_INDEX_2A	   0x68298
#घोषणा _PS_COEF_SET0_INDEX_1B	   0x68998
#घोषणा _PS_COEF_SET0_INDEX_2B	   0x68A98
#घोषणा PS_COEE_INDEX_AUTO_INC	   (1 << 10)

#घोषणा _PS_COEF_SET0_DATA_1A	   0x6819C
#घोषणा _PS_COEF_SET0_DATA_2A	   0x6829C
#घोषणा _PS_COEF_SET0_DATA_1B	   0x6899C
#घोषणा _PS_COEF_SET0_DATA_2B	   0x68A9C

#घोषणा _ID(id, a, b) _PICK_EVEN(id, a, b)
#घोषणा SKL_PS_CTRL(pipe, id) _MMIO_PIPE(pipe,        \
			_ID(id, _PS_1A_CTRL, _PS_2A_CTRL),       \
			_ID(id, _PS_1B_CTRL, _PS_2B_CTRL))
#घोषणा SKL_PS_PWR_GATE(pipe, id) _MMIO_PIPE(pipe,    \
			_ID(id, _PS_PWR_GATE_1A, _PS_PWR_GATE_2A), \
			_ID(id, _PS_PWR_GATE_1B, _PS_PWR_GATE_2B))
#घोषणा SKL_PS_WIN_POS(pipe, id) _MMIO_PIPE(pipe,     \
			_ID(id, _PS_WIN_POS_1A, _PS_WIN_POS_2A), \
			_ID(id, _PS_WIN_POS_1B, _PS_WIN_POS_2B))
#घोषणा SKL_PS_WIN_SZ(pipe, id)  _MMIO_PIPE(pipe,     \
			_ID(id, _PS_WIN_SZ_1A, _PS_WIN_SZ_2A),   \
			_ID(id, _PS_WIN_SZ_1B, _PS_WIN_SZ_2B))
#घोषणा SKL_PS_VSCALE(pipe, id)  _MMIO_PIPE(pipe,     \
			_ID(id, _PS_VSCALE_1A, _PS_VSCALE_2A),   \
			_ID(id, _PS_VSCALE_1B, _PS_VSCALE_2B))
#घोषणा SKL_PS_HSCALE(pipe, id)  _MMIO_PIPE(pipe,     \
			_ID(id, _PS_HSCALE_1A, _PS_HSCALE_2A),   \
			_ID(id, _PS_HSCALE_1B, _PS_HSCALE_2B))
#घोषणा SKL_PS_VPHASE(pipe, id)  _MMIO_PIPE(pipe,     \
			_ID(id, _PS_VPHASE_1A, _PS_VPHASE_2A),   \
			_ID(id, _PS_VPHASE_1B, _PS_VPHASE_2B))
#घोषणा SKL_PS_HPHASE(pipe, id)  _MMIO_PIPE(pipe,     \
			_ID(id, _PS_HPHASE_1A, _PS_HPHASE_2A),   \
			_ID(id, _PS_HPHASE_1B, _PS_HPHASE_2B))
#घोषणा SKL_PS_ECC_STAT(pipe, id)  _MMIO_PIPE(pipe,     \
			_ID(id, _PS_ECC_STAT_1A, _PS_ECC_STAT_2A),   \
			_ID(id, _PS_ECC_STAT_1B, _PS_ECC_STAT_2B))
#घोषणा CNL_PS_COEF_INDEX_SET(pipe, id, set)  _MMIO_PIPE(pipe,    \
			_ID(id, _PS_COEF_SET0_INDEX_1A, _PS_COEF_SET0_INDEX_2A) + (set) * 8, \
			_ID(id, _PS_COEF_SET0_INDEX_1B, _PS_COEF_SET0_INDEX_2B) + (set) * 8)

#घोषणा CNL_PS_COEF_DATA_SET(pipe, id, set)  _MMIO_PIPE(pipe,     \
			_ID(id, _PS_COEF_SET0_DATA_1A, _PS_COEF_SET0_DATA_2A) + (set) * 8, \
			_ID(id, _PS_COEF_SET0_DATA_1B, _PS_COEF_SET0_DATA_2B) + (set) * 8)
/* legacy palette */
#घोषणा _LGC_PALETTE_A           0x4a000
#घोषणा _LGC_PALETTE_B           0x4a800
#घोषणा LGC_PALETTE_RED_MASK     REG_GENMASK(23, 16)
#घोषणा LGC_PALETTE_GREEN_MASK   REG_GENMASK(15, 8)
#घोषणा LGC_PALETTE_BLUE_MASK    REG_GENMASK(7, 0)
#घोषणा LGC_PALETTE(pipe, i) _MMIO(_PIPE(pipe, _LGC_PALETTE_A, _LGC_PALETTE_B) + (i) * 4)

/* ilk/snb precision palette */
#घोषणा _PREC_PALETTE_A           0x4b000
#घोषणा _PREC_PALETTE_B           0x4c000
#घोषणा   PREC_PALETTE_RED_MASK   REG_GENMASK(29, 20)
#घोषणा   PREC_PALETTE_GREEN_MASK REG_GENMASK(19, 10)
#घोषणा   PREC_PALETTE_BLUE_MASK  REG_GENMASK(9, 0)
#घोषणा PREC_PALETTE(pipe, i) _MMIO(_PIPE(pipe, _PREC_PALETTE_A, _PREC_PALETTE_B) + (i) * 4)

#घोषणा  _PREC_PIPEAGCMAX              0x4d000
#घोषणा  _PREC_PIPEBGCMAX              0x4d010
#घोषणा PREC_PIPEGCMAX(pipe, i)        _MMIO(_PIPE(pipe, _PIPEAGCMAX, _PIPEBGCMAX) + (i) * 4)

#घोषणा _GAMMA_MODE_A		0x4a480
#घोषणा _GAMMA_MODE_B		0x4ac80
#घोषणा GAMMA_MODE(pipe) _MMIO_PIPE(pipe, _GAMMA_MODE_A, _GAMMA_MODE_B)
#घोषणा  PRE_CSC_GAMMA_ENABLE	(1 << 31)
#घोषणा  POST_CSC_GAMMA_ENABLE	(1 << 30)
#घोषणा  GAMMA_MODE_MODE_MASK	(3 << 0)
#घोषणा  GAMMA_MODE_MODE_8BIT	(0 << 0)
#घोषणा  GAMMA_MODE_MODE_10BIT	(1 << 0)
#घोषणा  GAMMA_MODE_MODE_12BIT	(2 << 0)
#घोषणा  GAMMA_MODE_MODE_SPLIT	(3 << 0) /* ivb-bdw */
#घोषणा  GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED	(3 << 0) /* icl + */

/* DMC/CSR */
#घोषणा CSR_PROGRAM(i)		_MMIO(0x80000 + (i) * 4)
#घोषणा CSR_SSP_BASE_ADDR_GEN9	0x00002FC0
#घोषणा CSR_HTP_ADDR_SKL	0x00500034
#घोषणा CSR_SSP_BASE		_MMIO(0x8F074)
#घोषणा CSR_HTP_SKL		_MMIO(0x8F004)
#घोषणा CSR_LAST_WRITE		_MMIO(0x8F034)
#घोषणा CSR_LAST_WRITE_VALUE	0xc003b400
/* MMIO address range क्रम CSR program (0x80000 - 0x82FFF) */
#घोषणा CSR_MMIO_START_RANGE	0x80000
#घोषणा CSR_MMIO_END_RANGE	0x8FFFF
#घोषणा SKL_CSR_DC3_DC5_COUNT	_MMIO(0x80030)
#घोषणा SKL_CSR_DC5_DC6_COUNT	_MMIO(0x8002C)
#घोषणा BXT_CSR_DC3_DC5_COUNT	_MMIO(0x80038)
#घोषणा TGL_DMC_DEBUG_DC5_COUNT	_MMIO(0x101084)
#घोषणा TGL_DMC_DEBUG_DC6_COUNT	_MMIO(0x101088)
#घोषणा DG1_DMC_DEBUG_DC5_COUNT	_MMIO(0x134154)

#घोषणा DMC_DEBUG3		_MMIO(0x101090)

/* Display Internal Timeout Register */
#घोषणा RM_TIMEOUT		_MMIO(0x42060)
#घोषणा  MMIO_TIMEOUT_US(us)	((us) << 0)

/* पूर्णांकerrupts */
#घोषणा DE_MASTER_IRQ_CONTROL   (1 << 31)
#घोषणा DE_SPRITEB_FLIP_DONE    (1 << 29)
#घोषणा DE_SPRITEA_FLIP_DONE    (1 << 28)
#घोषणा DE_PLANEB_FLIP_DONE     (1 << 27)
#घोषणा DE_PLANEA_FLIP_DONE     (1 << 26)
#घोषणा DE_PLANE_FLIP_DONE(plane) (1 << (26 + (plane)))
#घोषणा DE_PCU_EVENT            (1 << 25)
#घोषणा DE_GTT_FAULT            (1 << 24)
#घोषणा DE_POISON               (1 << 23)
#घोषणा DE_PERFORM_COUNTER      (1 << 22)
#घोषणा DE_PCH_EVENT            (1 << 21)
#घोषणा DE_AUX_CHANNEL_A        (1 << 20)
#घोषणा DE_DP_A_HOTPLUG         (1 << 19)
#घोषणा DE_GSE                  (1 << 18)
#घोषणा DE_PIPEB_VBLANK         (1 << 15)
#घोषणा DE_PIPEB_EVEN_FIELD     (1 << 14)
#घोषणा DE_PIPEB_ODD_FIELD      (1 << 13)
#घोषणा DE_PIPEB_LINE_COMPARE   (1 << 12)
#घोषणा DE_PIPEB_VSYNC          (1 << 11)
#घोषणा DE_PIPEB_CRC_DONE	(1 << 10)
#घोषणा DE_PIPEB_FIFO_UNDERRUN  (1 << 8)
#घोषणा DE_PIPEA_VBLANK         (1 << 7)
#घोषणा DE_PIPE_VBLANK(pipe)    (1 << (7 + 8 * (pipe)))
#घोषणा DE_PIPEA_EVEN_FIELD     (1 << 6)
#घोषणा DE_PIPEA_ODD_FIELD      (1 << 5)
#घोषणा DE_PIPEA_LINE_COMPARE   (1 << 4)
#घोषणा DE_PIPEA_VSYNC          (1 << 3)
#घोषणा DE_PIPEA_CRC_DONE	(1 << 2)
#घोषणा DE_PIPE_CRC_DONE(pipe)	(1 << (2 + 8 * (pipe)))
#घोषणा DE_PIPEA_FIFO_UNDERRUN  (1 << 0)
#घोषणा DE_PIPE_FIFO_UNDERRUN(pipe)  (1 << (8 * (pipe)))

/* More Ivybridge lolz */
#घोषणा DE_ERR_INT_IVB			(1 << 30)
#घोषणा DE_GSE_IVB			(1 << 29)
#घोषणा DE_PCH_EVENT_IVB		(1 << 28)
#घोषणा DE_DP_A_HOTPLUG_IVB		(1 << 27)
#घोषणा DE_AUX_CHANNEL_A_IVB		(1 << 26)
#घोषणा DE_EDP_PSR_INT_HSW		(1 << 19)
#घोषणा DE_SPRITEC_FLIP_DONE_IVB	(1 << 14)
#घोषणा DE_PLANEC_FLIP_DONE_IVB		(1 << 13)
#घोषणा DE_PIPEC_VBLANK_IVB		(1 << 10)
#घोषणा DE_SPRITEB_FLIP_DONE_IVB	(1 << 9)
#घोषणा DE_PLANEB_FLIP_DONE_IVB		(1 << 8)
#घोषणा DE_PIPEB_VBLANK_IVB		(1 << 5)
#घोषणा DE_SPRITEA_FLIP_DONE_IVB	(1 << 4)
#घोषणा DE_PLANEA_FLIP_DONE_IVB		(1 << 3)
#घोषणा DE_PLANE_FLIP_DONE_IVB(plane)	(1 << (3 + 5 * (plane)))
#घोषणा DE_PIPEA_VBLANK_IVB		(1 << 0)
#घोषणा DE_PIPE_VBLANK_IVB(pipe)	(1 << ((pipe) * 5))

#घोषणा VLV_MASTER_IER			_MMIO(0x4400c) /* Gunit master IER */
#घोषणा   MASTER_INTERRUPT_ENABLE	(1 << 31)

#घोषणा DEISR   _MMIO(0x44000)
#घोषणा DEIMR   _MMIO(0x44004)
#घोषणा DEIIR   _MMIO(0x44008)
#घोषणा DEIER   _MMIO(0x4400c)

#घोषणा GTISR   _MMIO(0x44010)
#घोषणा GTIMR   _MMIO(0x44014)
#घोषणा GTIIR   _MMIO(0x44018)
#घोषणा GTIER   _MMIO(0x4401c)

#घोषणा GEN8_MASTER_IRQ			_MMIO(0x44200)
#घोषणा  GEN8_MASTER_IRQ_CONTROL	(1 << 31)
#घोषणा  GEN8_PCU_IRQ			(1 << 30)
#घोषणा  GEN8_DE_PCH_IRQ		(1 << 23)
#घोषणा  GEN8_DE_MISC_IRQ		(1 << 22)
#घोषणा  GEN8_DE_PORT_IRQ		(1 << 20)
#घोषणा  GEN8_DE_PIPE_C_IRQ		(1 << 18)
#घोषणा  GEN8_DE_PIPE_B_IRQ		(1 << 17)
#घोषणा  GEN8_DE_PIPE_A_IRQ		(1 << 16)
#घोषणा  GEN8_DE_PIPE_IRQ(pipe)		(1 << (16 + (pipe)))
#घोषणा  GEN8_GT_VECS_IRQ		(1 << 6)
#घोषणा  GEN8_GT_GUC_IRQ		(1 << 5)
#घोषणा  GEN8_GT_PM_IRQ			(1 << 4)
#घोषणा  GEN8_GT_VCS1_IRQ		(1 << 3) /* NB: VCS2 in bspec! */
#घोषणा  GEN8_GT_VCS0_IRQ		(1 << 2) /* NB: VCS1 in bpsec! */
#घोषणा  GEN8_GT_BCS_IRQ		(1 << 1)
#घोषणा  GEN8_GT_RCS_IRQ		(1 << 0)

#घोषणा GEN8_GT_ISR(which) _MMIO(0x44300 + (0x10 * (which)))
#घोषणा GEN8_GT_IMR(which) _MMIO(0x44304 + (0x10 * (which)))
#घोषणा GEN8_GT_IIR(which) _MMIO(0x44308 + (0x10 * (which)))
#घोषणा GEN8_GT_IER(which) _MMIO(0x4430c + (0x10 * (which)))

#घोषणा GEN8_RCS_IRQ_SHIFT 0
#घोषणा GEN8_BCS_IRQ_SHIFT 16
#घोषणा GEN8_VCS0_IRQ_SHIFT 0  /* NB: VCS1 in bspec! */
#घोषणा GEN8_VCS1_IRQ_SHIFT 16 /* NB: VCS2 in bpsec! */
#घोषणा GEN8_VECS_IRQ_SHIFT 0
#घोषणा GEN8_WD_IRQ_SHIFT 16

#घोषणा GEN8_DE_PIPE_ISR(pipe) _MMIO(0x44400 + (0x10 * (pipe)))
#घोषणा GEN8_DE_PIPE_IMR(pipe) _MMIO(0x44404 + (0x10 * (pipe)))
#घोषणा GEN8_DE_PIPE_IIR(pipe) _MMIO(0x44408 + (0x10 * (pipe)))
#घोषणा GEN8_DE_PIPE_IER(pipe) _MMIO(0x4440c + (0x10 * (pipe)))
#घोषणा  GEN8_PIPE_FIFO_UNDERRUN	(1 << 31)
#घोषणा  GEN8_PIPE_CDCLK_CRC_ERROR	(1 << 29)
#घोषणा  GEN8_PIPE_CDCLK_CRC_DONE	(1 << 28)
#घोषणा  GEN8_PIPE_CURSOR_FAULT		(1 << 10)
#घोषणा  GEN8_PIPE_SPRITE_FAULT		(1 << 9)
#घोषणा  GEN8_PIPE_PRIMARY_FAULT	(1 << 8)
#घोषणा  GEN8_PIPE_SPRITE_FLIP_DONE	(1 << 5)
#घोषणा  GEN8_PIPE_PRIMARY_FLIP_DONE	(1 << 4)
#घोषणा  GEN8_PIPE_SCAN_LINE_EVENT	(1 << 2)
#घोषणा  GEN8_PIPE_VSYNC		(1 << 1)
#घोषणा  GEN8_PIPE_VBLANK		(1 << 0)
#घोषणा  GEN9_PIPE_CURSOR_FAULT		(1 << 11)
#घोषणा  GEN11_PIPE_PLANE7_FAULT	(1 << 22)
#घोषणा  GEN11_PIPE_PLANE6_FAULT	(1 << 21)
#घोषणा  GEN11_PIPE_PLANE5_FAULT	(1 << 20)
#घोषणा  GEN9_PIPE_PLANE4_FAULT		(1 << 10)
#घोषणा  GEN9_PIPE_PLANE3_FAULT		(1 << 9)
#घोषणा  GEN9_PIPE_PLANE2_FAULT		(1 << 8)
#घोषणा  GEN9_PIPE_PLANE1_FAULT		(1 << 7)
#घोषणा  GEN9_PIPE_PLANE4_FLIP_DONE	(1 << 6)
#घोषणा  GEN9_PIPE_PLANE3_FLIP_DONE	(1 << 5)
#घोषणा  GEN9_PIPE_PLANE2_FLIP_DONE	(1 << 4)
#घोषणा  GEN9_PIPE_PLANE1_FLIP_DONE	(1 << 3)
#घोषणा  GEN9_PIPE_PLANE_FLIP_DONE(p)	(1 << (3 + (p)))
#घोषणा GEN8_DE_PIPE_IRQ_FAULT_ERRORS \
	(GEN8_PIPE_CURSOR_FAULT | \
	 GEN8_PIPE_SPRITE_FAULT | \
	 GEN8_PIPE_PRIMARY_FAULT)
#घोषणा GEN9_DE_PIPE_IRQ_FAULT_ERRORS \
	(GEN9_PIPE_CURSOR_FAULT | \
	 GEN9_PIPE_PLANE4_FAULT | \
	 GEN9_PIPE_PLANE3_FAULT | \
	 GEN9_PIPE_PLANE2_FAULT | \
	 GEN9_PIPE_PLANE1_FAULT)
#घोषणा GEN11_DE_PIPE_IRQ_FAULT_ERRORS \
	(GEN9_DE_PIPE_IRQ_FAULT_ERRORS | \
	 GEN11_PIPE_PLANE7_FAULT | \
	 GEN11_PIPE_PLANE6_FAULT | \
	 GEN11_PIPE_PLANE5_FAULT)
#घोषणा RKL_DE_PIPE_IRQ_FAULT_ERRORS \
	(GEN9_DE_PIPE_IRQ_FAULT_ERRORS | \
	 GEN11_PIPE_PLANE5_FAULT)

#घोषणा _HPD_PIN_DDI(hpd_pin)	((hpd_pin) - HPD_PORT_A)
#घोषणा _HPD_PIN_TC(hpd_pin)	((hpd_pin) - HPD_PORT_TC1)

#घोषणा GEN8_DE_PORT_ISR _MMIO(0x44440)
#घोषणा GEN8_DE_PORT_IMR _MMIO(0x44444)
#घोषणा GEN8_DE_PORT_IIR _MMIO(0x44448)
#घोषणा GEN8_DE_PORT_IER _MMIO(0x4444c)
#घोषणा  DSI1_NON_TE			(1 << 31)
#घोषणा  DSI0_NON_TE			(1 << 30)
#घोषणा  ICL_AUX_CHANNEL_E		(1 << 29)
#घोषणा  CNL_AUX_CHANNEL_F		(1 << 28)
#घोषणा  GEN9_AUX_CHANNEL_D		(1 << 27)
#घोषणा  GEN9_AUX_CHANNEL_C		(1 << 26)
#घोषणा  GEN9_AUX_CHANNEL_B		(1 << 25)
#घोषणा  DSI1_TE			(1 << 24)
#घोषणा  DSI0_TE			(1 << 23)
#घोषणा  GEN8_DE_PORT_HOTPLUG(hpd_pin)	REG_BIT(3 + _HPD_PIN_DDI(hpd_pin))
#घोषणा  BXT_DE_PORT_HOTPLUG_MASK	(GEN8_DE_PORT_HOTPLUG(HPD_PORT_A) | \
					 GEN8_DE_PORT_HOTPLUG(HPD_PORT_B) | \
					 GEN8_DE_PORT_HOTPLUG(HPD_PORT_C))
#घोषणा  BDW_DE_PORT_HOTPLUG_MASK	GEN8_DE_PORT_HOTPLUG(HPD_PORT_A)
#घोषणा  BXT_DE_PORT_GMBUS		(1 << 1)
#घोषणा  GEN8_AUX_CHANNEL_A		(1 << 0)
#घोषणा  TGL_DE_PORT_AUX_USBC6		(1 << 13)
#घोषणा  TGL_DE_PORT_AUX_USBC5		(1 << 12)
#घोषणा  TGL_DE_PORT_AUX_USBC4		(1 << 11)
#घोषणा  TGL_DE_PORT_AUX_USBC3		(1 << 10)
#घोषणा  TGL_DE_PORT_AUX_USBC2		(1 << 9)
#घोषणा  TGL_DE_PORT_AUX_USBC1		(1 << 8)
#घोषणा  TGL_DE_PORT_AUX_DDIC		(1 << 2)
#घोषणा  TGL_DE_PORT_AUX_DDIB		(1 << 1)
#घोषणा  TGL_DE_PORT_AUX_DDIA		(1 << 0)

#घोषणा GEN8_DE_MISC_ISR _MMIO(0x44460)
#घोषणा GEN8_DE_MISC_IMR _MMIO(0x44464)
#घोषणा GEN8_DE_MISC_IIR _MMIO(0x44468)
#घोषणा GEN8_DE_MISC_IER _MMIO(0x4446c)
#घोषणा  GEN8_DE_MISC_GSE		(1 << 27)
#घोषणा  GEN8_DE_EDP_PSR		(1 << 19)

#घोषणा GEN8_PCU_ISR _MMIO(0x444e0)
#घोषणा GEN8_PCU_IMR _MMIO(0x444e4)
#घोषणा GEN8_PCU_IIR _MMIO(0x444e8)
#घोषणा GEN8_PCU_IER _MMIO(0x444ec)

#घोषणा GEN11_GU_MISC_ISR	_MMIO(0x444f0)
#घोषणा GEN11_GU_MISC_IMR	_MMIO(0x444f4)
#घोषणा GEN11_GU_MISC_IIR	_MMIO(0x444f8)
#घोषणा GEN11_GU_MISC_IER	_MMIO(0x444fc)
#घोषणा  GEN11_GU_MISC_GSE	(1 << 27)

#घोषणा GEN11_GFX_MSTR_IRQ		_MMIO(0x190010)
#घोषणा  GEN11_MASTER_IRQ		(1 << 31)
#घोषणा  GEN11_PCU_IRQ			(1 << 30)
#घोषणा  GEN11_GU_MISC_IRQ		(1 << 29)
#घोषणा  GEN11_DISPLAY_IRQ		(1 << 16)
#घोषणा  GEN11_GT_DW_IRQ(x)		(1 << (x))
#घोषणा  GEN11_GT_DW1_IRQ		(1 << 1)
#घोषणा  GEN11_GT_DW0_IRQ		(1 << 0)

#घोषणा DG1_MSTR_UNIT_INTR		_MMIO(0x190008)
#घोषणा   DG1_MSTR_IRQ			REG_BIT(31)
#घोषणा   DG1_MSTR_UNIT(u)		REG_BIT(u)

#घोषणा GEN11_DISPLAY_INT_CTL		_MMIO(0x44200)
#घोषणा  GEN11_DISPLAY_IRQ_ENABLE	(1 << 31)
#घोषणा  GEN11_AUDIO_CODEC_IRQ		(1 << 24)
#घोषणा  GEN11_DE_PCH_IRQ		(1 << 23)
#घोषणा  GEN11_DE_MISC_IRQ		(1 << 22)
#घोषणा  GEN11_DE_HPD_IRQ		(1 << 21)
#घोषणा  GEN11_DE_PORT_IRQ		(1 << 20)
#घोषणा  GEN11_DE_PIPE_C		(1 << 18)
#घोषणा  GEN11_DE_PIPE_B		(1 << 17)
#घोषणा  GEN11_DE_PIPE_A		(1 << 16)

#घोषणा GEN11_DE_HPD_ISR		_MMIO(0x44470)
#घोषणा GEN11_DE_HPD_IMR		_MMIO(0x44474)
#घोषणा GEN11_DE_HPD_IIR		_MMIO(0x44478)
#घोषणा GEN11_DE_HPD_IER		_MMIO(0x4447c)
#घोषणा  GEN11_TC_HOTPLUG(hpd_pin)		REG_BIT(16 + _HPD_PIN_TC(hpd_pin))
#घोषणा  GEN11_DE_TC_HOTPLUG_MASK		(GEN11_TC_HOTPLUG(HPD_PORT_TC6) | \
						 GEN11_TC_HOTPLUG(HPD_PORT_TC5) | \
						 GEN11_TC_HOTPLUG(HPD_PORT_TC4) | \
						 GEN11_TC_HOTPLUG(HPD_PORT_TC3) | \
						 GEN11_TC_HOTPLUG(HPD_PORT_TC2) | \
						 GEN11_TC_HOTPLUG(HPD_PORT_TC1))
#घोषणा  GEN11_TBT_HOTPLUG(hpd_pin)		REG_BIT(_HPD_PIN_TC(hpd_pin))
#घोषणा  GEN11_DE_TBT_HOTPLUG_MASK		(GEN11_TBT_HOTPLUG(HPD_PORT_TC6) | \
						 GEN11_TBT_HOTPLUG(HPD_PORT_TC5) | \
						 GEN11_TBT_HOTPLUG(HPD_PORT_TC4) | \
						 GEN11_TBT_HOTPLUG(HPD_PORT_TC3) | \
						 GEN11_TBT_HOTPLUG(HPD_PORT_TC2) | \
						 GEN11_TBT_HOTPLUG(HPD_PORT_TC1))

#घोषणा GEN11_TBT_HOTPLUG_CTL				_MMIO(0x44030)
#घोषणा GEN11_TC_HOTPLUG_CTL				_MMIO(0x44038)
#घोषणा  GEN11_HOTPLUG_CTL_ENABLE(hpd_pin)		(8 << (_HPD_PIN_TC(hpd_pin) * 4))
#घोषणा  GEN11_HOTPLUG_CTL_LONG_DETECT(hpd_pin)		(2 << (_HPD_PIN_TC(hpd_pin) * 4))
#घोषणा  GEN11_HOTPLUG_CTL_SHORT_DETECT(hpd_pin)	(1 << (_HPD_PIN_TC(hpd_pin) * 4))
#घोषणा  GEN11_HOTPLUG_CTL_NO_DETECT(hpd_pin)		(0 << (_HPD_PIN_TC(hpd_pin) * 4))

#घोषणा GEN11_GT_INTR_DW0		_MMIO(0x190018)
#घोषणा  GEN11_CSME			(31)
#घोषणा  GEN11_GUNIT			(28)
#घोषणा  GEN11_GUC			(25)
#घोषणा  GEN11_WDPERF			(20)
#घोषणा  GEN11_KCR			(19)
#घोषणा  GEN11_GTPM			(16)
#घोषणा  GEN11_BCS			(15)
#घोषणा  GEN11_RCS0			(0)

#घोषणा GEN11_GT_INTR_DW1		_MMIO(0x19001c)
#घोषणा  GEN11_VECS(x)			(31 - (x))
#घोषणा  GEN11_VCS(x)			(x)

#घोषणा GEN11_GT_INTR_DW(x)		_MMIO(0x190018 + ((x) * 4))

#घोषणा GEN11_INTR_IDENTITY_REG0	_MMIO(0x190060)
#घोषणा GEN11_INTR_IDENTITY_REG1	_MMIO(0x190064)
#घोषणा  GEN11_INTR_DATA_VALID		(1 << 31)
#घोषणा  GEN11_INTR_ENGINE_CLASS(x)	(((x) & GENMASK(18, 16)) >> 16)
#घोषणा  GEN11_INTR_ENGINE_INSTANCE(x)	(((x) & GENMASK(25, 20)) >> 20)
#घोषणा  GEN11_INTR_ENGINE_INTR(x)	((x) & 0xffff)
/* irq instances क्रम OTHER_CLASS */
#घोषणा OTHER_GUC_INSTANCE	0
#घोषणा OTHER_GTPM_INSTANCE	1

#घोषणा GEN11_INTR_IDENTITY_REG(x)	_MMIO(0x190060 + ((x) * 4))

#घोषणा GEN11_IIR_REG0_SELECTOR		_MMIO(0x190070)
#घोषणा GEN11_IIR_REG1_SELECTOR		_MMIO(0x190074)

#घोषणा GEN11_IIR_REG_SELECTOR(x)	_MMIO(0x190070 + ((x) * 4))

#घोषणा GEN11_RENDER_COPY_INTR_ENABLE	_MMIO(0x190030)
#घोषणा GEN11_VCS_VECS_INTR_ENABLE	_MMIO(0x190034)
#घोषणा GEN11_GUC_SG_INTR_ENABLE	_MMIO(0x190038)
#घोषणा GEN11_GPM_WGBOXPERF_INTR_ENABLE	_MMIO(0x19003c)
#घोषणा GEN11_CRYPTO_RSVD_INTR_ENABLE	_MMIO(0x190040)
#घोषणा GEN11_GUNIT_CSME_INTR_ENABLE	_MMIO(0x190044)

#घोषणा GEN11_RCS0_RSVD_INTR_MASK	_MMIO(0x190090)
#घोषणा GEN11_BCS_RSVD_INTR_MASK	_MMIO(0x1900a0)
#घोषणा GEN11_VCS0_VCS1_INTR_MASK	_MMIO(0x1900a8)
#घोषणा GEN11_VCS2_VCS3_INTR_MASK	_MMIO(0x1900ac)
#घोषणा GEN11_VECS0_VECS1_INTR_MASK	_MMIO(0x1900d0)
#घोषणा GEN11_GUC_SG_INTR_MASK		_MMIO(0x1900e8)
#घोषणा GEN11_GPM_WGBOXPERF_INTR_MASK	_MMIO(0x1900ec)
#घोषणा GEN11_CRYPTO_RSVD_INTR_MASK	_MMIO(0x1900f0)
#घोषणा GEN11_GUNIT_CSME_INTR_MASK	_MMIO(0x1900f4)

#घोषणा   ENGINE1_MASK			REG_GENMASK(31, 16)
#घोषणा   ENGINE0_MASK			REG_GENMASK(15, 0)

#घोषणा ILK_DISPLAY_CHICKEN2	_MMIO(0x42004)
/* Required on all Ironlake and Sandybridge according to the B-Spec. */
#घोषणा  ILK_ELPIN_409_SELECT	(1 << 25)
#घोषणा  ILK_DPARB_GATE	(1 << 22)
#घोषणा  ILK_VSDPFD_FULL	(1 << 21)
#घोषणा FUSE_STRAP			_MMIO(0x42014)
#घोषणा  ILK_INTERNAL_GRAPHICS_DISABLE	(1 << 31)
#घोषणा  ILK_INTERNAL_DISPLAY_DISABLE	(1 << 30)
#घोषणा  ILK_DISPLAY_DEBUG_DISABLE	(1 << 29)
#घोषणा  IVB_PIPE_C_DISABLE		(1 << 28)
#घोषणा  ILK_HDCP_DISABLE		(1 << 25)
#घोषणा  ILK_eDP_A_DISABLE		(1 << 24)
#घोषणा  HSW_CDCLK_LIMIT		(1 << 24)
#घोषणा  ILK_DESKTOP			(1 << 23)
#घोषणा  HSW_CPU_SSC_ENABLE		(1 << 21)

#घोषणा FUSE_STRAP3			_MMIO(0x42020)
#घोषणा  HSW_REF_CLK_SELECT		(1 << 1)

#घोषणा ILK_DSPCLK_GATE_D			_MMIO(0x42020)
#घोषणा   ILK_VRHUNIT_CLOCK_GATE_DISABLE	(1 << 28)
#घोषणा   ILK_DPFCUNIT_CLOCK_GATE_DISABLE	(1 << 9)
#घोषणा   ILK_DPFCRUNIT_CLOCK_GATE_DISABLE	(1 << 8)
#घोषणा   ILK_DPFDUNIT_CLOCK_GATE_ENABLE	(1 << 7)
#घोषणा   ILK_DPARBUNIT_CLOCK_GATE_ENABLE	(1 << 5)

#घोषणा IVB_CHICKEN3	_MMIO(0x4200c)
# define CHICKEN3_DGMG_REQ_OUT_FIX_DISABLE	(1 << 5)
# define CHICKEN3_DGMG_DONE_FIX_DISABLE		(1 << 2)

#घोषणा CHICKEN_PAR1_1			_MMIO(0x42080)
#घोषणा  KBL_ARB_FILL_SPARE_22		REG_BIT(22)
#घोषणा  DIS_RAM_BYPASS_PSR2_MAN_TRACK	(1 << 16)
#घोषणा  SKL_DE_COMPRESSED_HASH_MODE	(1 << 15)
#घोषणा  DPA_MASK_VBLANK_SRD		(1 << 15)
#घोषणा  FORCE_ARB_IDLE_PLANES		(1 << 14)
#घोषणा  SKL_EDP_PSR_FIX_RDWRAP		(1 << 3)
#घोषणा  IGNORE_PSR2_HW_TRACKING	(1 << 1)

#घोषणा CHICKEN_PAR2_1		_MMIO(0x42090)
#घोषणा  KVM_CONFIG_CHANGE_NOTIFICATION_SELECT	(1 << 14)

#घोषणा CHICKEN_MISC_2		_MMIO(0x42084)
#घोषणा  CNL_COMP_PWR_DOWN	(1 << 23)
#घोषणा  KBL_ARB_FILL_SPARE_14	REG_BIT(14)
#घोषणा  KBL_ARB_FILL_SPARE_13	REG_BIT(13)
#घोषणा  GLK_CL2_PWR_DOWN	(1 << 12)
#घोषणा  GLK_CL1_PWR_DOWN	(1 << 11)
#घोषणा  GLK_CL0_PWR_DOWN	(1 << 10)

#घोषणा CHICKEN_MISC_4		_MMIO(0x4208c)
#घोषणा   FBC_STRIDE_OVERRIDE	(1 << 13)
#घोषणा   FBC_STRIDE_MASK	0x1FFF

#घोषणा _CHICKEN_PIPESL_1_A	0x420b0
#घोषणा _CHICKEN_PIPESL_1_B	0x420b4
#घोषणा  HSW_PRI_STRETCH_MAX_MASK	REG_GENMASK(28, 27)
#घोषणा  HSW_PRI_STRETCH_MAX_X8		REG_FIELD_PREP(HSW_PRI_STRETCH_MAX_MASK, 0)
#घोषणा  HSW_PRI_STRETCH_MAX_X4		REG_FIELD_PREP(HSW_PRI_STRETCH_MAX_MASK, 1)
#घोषणा  HSW_PRI_STRETCH_MAX_X2		REG_FIELD_PREP(HSW_PRI_STRETCH_MAX_MASK, 2)
#घोषणा  HSW_PRI_STRETCH_MAX_X1		REG_FIELD_PREP(HSW_PRI_STRETCH_MAX_MASK, 3)
#घोषणा  HSW_SPR_STRETCH_MAX_MASK	REG_GENMASK(26, 25)
#घोषणा  HSW_SPR_STRETCH_MAX_X8		REG_FIELD_PREP(HSW_SPR_STRETCH_MAX_MASK, 0)
#घोषणा  HSW_SPR_STRETCH_MAX_X4		REG_FIELD_PREP(HSW_SPR_STRETCH_MAX_MASK, 1)
#घोषणा  HSW_SPR_STRETCH_MAX_X2		REG_FIELD_PREP(HSW_SPR_STRETCH_MAX_MASK, 2)
#घोषणा  HSW_SPR_STRETCH_MAX_X1		REG_FIELD_PREP(HSW_SPR_STRETCH_MAX_MASK, 3)
#घोषणा  HSW_FBCQ_DIS			(1 << 22)
#घोषणा  BDW_DPRS_MASK_VBLANK_SRD	(1 << 0)
#घोषणा CHICKEN_PIPESL_1(pipe) _MMIO_PIPE(pipe, _CHICKEN_PIPESL_1_A, _CHICKEN_PIPESL_1_B)

#घोषणा _CHICKEN_TRANS_A	0x420c0
#घोषणा _CHICKEN_TRANS_B	0x420c4
#घोषणा _CHICKEN_TRANS_C	0x420c8
#घोषणा _CHICKEN_TRANS_EDP	0x420cc
#घोषणा _CHICKEN_TRANS_D	0x420d8
#घोषणा CHICKEN_TRANS(trans)	_MMIO(_PICK((trans), \
					    [TRANSCODER_EDP] = _CHICKEN_TRANS_EDP, \
					    [TRANSCODER_A] = _CHICKEN_TRANS_A, \
					    [TRANSCODER_B] = _CHICKEN_TRANS_B, \
					    [TRANSCODER_C] = _CHICKEN_TRANS_C, \
					    [TRANSCODER_D] = _CHICKEN_TRANS_D))
#घोषणा  HSW_FRAME_START_DELAY_MASK	(3 << 27)
#घोषणा  HSW_FRAME_START_DELAY(x)	((x) << 27) /* 0-3 */
#घोषणा  VSC_DATA_SEL_SOFTWARE_CONTROL	(1 << 25) /* GLK and CNL+ */
#घोषणा  DDI_TRAINING_OVERRIDE_ENABLE	(1 << 19)
#घोषणा  DDI_TRAINING_OVERRIDE_VALUE	(1 << 18)
#घोषणा  DDIE_TRAINING_OVERRIDE_ENABLE	(1 << 17) /* CHICKEN_TRANS_A only */
#घोषणा  DDIE_TRAINING_OVERRIDE_VALUE	(1 << 16) /* CHICKEN_TRANS_A only */
#घोषणा  PSR2_ADD_VERTICAL_LINE_COUNT   (1 << 15)
#घोषणा  PSR2_VSC_ENABLE_PROG_HEADER    (1 << 12)

#घोषणा DISP_ARB_CTL	_MMIO(0x45000)
#घोषणा  DISP_FBC_MEMORY_WAKE		(1 << 31)
#घोषणा  DISP_TILE_SURFACE_SWIZZLING	(1 << 13)
#घोषणा  DISP_FBC_WM_DIS		(1 << 15)
#घोषणा DISP_ARB_CTL2	_MMIO(0x45004)
#घोषणा  DISP_DATA_PARTITION_5_6	(1 << 6)
#घोषणा  DISP_IPC_ENABLE		(1 << 3)

#घोषणा _DBUF_CTL_S1				0x45008
#घोषणा _DBUF_CTL_S2				0x44FE8
#घोषणा DBUF_CTL_S(slice)			_MMIO(_PICK_EVEN(slice, _DBUF_CTL_S1, _DBUF_CTL_S2))
#घोषणा  DBUF_POWER_REQUEST			REG_BIT(31)
#घोषणा  DBUF_POWER_STATE			REG_BIT(30)
#घोषणा  DBUF_TRACKER_STATE_SERVICE_MASK	REG_GENMASK(23, 19)
#घोषणा  DBUF_TRACKER_STATE_SERVICE(x)		REG_FIELD_PREP(DBUF_TRACKER_STATE_SERVICE_MASK, x)

#घोषणा GEN7_MSG_CTL	_MMIO(0x45010)
#घोषणा  WAIT_FOR_PCH_RESET_ACK		(1 << 1)
#घोषणा  WAIT_FOR_PCH_FLR_ACK		(1 << 0)

#घोषणा _BW_BUDDY0_CTL			0x45130
#घोषणा _BW_BUDDY1_CTL			0x45140
#घोषणा BW_BUDDY_CTL(x)			_MMIO(_PICK_EVEN(x, \
							 _BW_BUDDY0_CTL, \
							 _BW_BUDDY1_CTL))
#घोषणा   BW_BUDDY_DISABLE		REG_BIT(31)
#घोषणा   BW_BUDDY_TLB_REQ_TIMER_MASK	REG_GENMASK(21, 16)
#घोषणा   BW_BUDDY_TLB_REQ_TIMER(x)	REG_FIELD_PREP(BW_BUDDY_TLB_REQ_TIMER_MASK, x)

#घोषणा _BW_BUDDY0_PAGE_MASK		0x45134
#घोषणा _BW_BUDDY1_PAGE_MASK		0x45144
#घोषणा BW_BUDDY_PAGE_MASK(x)		_MMIO(_PICK_EVEN(x, \
							 _BW_BUDDY0_PAGE_MASK, \
							 _BW_BUDDY1_PAGE_MASK))

#घोषणा HSW_NDE_RSTWRN_OPT	_MMIO(0x46408)
#घोषणा  RESET_PCH_HANDSHAKE_ENABLE	(1 << 4)

#घोषणा GEN8_CHICKEN_DCPR_1		_MMIO(0x46430)
#घोषणा   SKL_SELECT_ALTERNATE_DC_EXIT	(1 << 30)
#घोषणा   CNL_DELAY_PMRSP		(1 << 22)
#घोषणा   MASK_WAKEMEM			(1 << 13)
#घोषणा   CNL_DDI_CLOCK_REG_ACCESS_ON	(1 << 7)

#घोषणा GEN11_CHICKEN_DCPR_2			_MMIO(0x46434)
#घोषणा   DCPR_MASK_MAXLATENCY_MEMUP_CLR	REG_BIT(27)
#घोषणा   DCPR_MASK_LPMODE			REG_BIT(26)
#घोषणा   DCPR_SEND_RESP_IMM			REG_BIT(25)
#घोषणा   DCPR_CLEAR_MEMSTAT_DIS		REG_BIT(24)

#घोषणा SKL_DFSM			_MMIO(0x51000)
#घोषणा   SKL_DFSM_DISPLAY_PM_DISABLE	(1 << 27)
#घोषणा   SKL_DFSM_DISPLAY_HDCP_DISABLE	(1 << 25)
#घोषणा   SKL_DFSM_CDCLK_LIMIT_MASK	(3 << 23)
#घोषणा   SKL_DFSM_CDCLK_LIMIT_675	(0 << 23)
#घोषणा   SKL_DFSM_CDCLK_LIMIT_540	(1 << 23)
#घोषणा   SKL_DFSM_CDCLK_LIMIT_450	(2 << 23)
#घोषणा   SKL_DFSM_CDCLK_LIMIT_337_5	(3 << 23)
#घोषणा   ICL_DFSM_DMC_DISABLE		(1 << 23)
#घोषणा   SKL_DFSM_PIPE_A_DISABLE	(1 << 30)
#घोषणा   SKL_DFSM_PIPE_B_DISABLE	(1 << 21)
#घोषणा   SKL_DFSM_PIPE_C_DISABLE	(1 << 28)
#घोषणा   TGL_DFSM_PIPE_D_DISABLE	(1 << 22)
#घोषणा   CNL_DFSM_DISPLAY_DSC_DISABLE	(1 << 7)

#घोषणा SKL_DSSM				_MMIO(0x51004)
#घोषणा CNL_DSSM_CDCLK_PLL_REFCLK_24MHz		(1 << 31)
#घोषणा ICL_DSSM_CDCLK_PLL_REFCLK_MASK		(7 << 29)
#घोषणा ICL_DSSM_CDCLK_PLL_REFCLK_24MHz		(0 << 29)
#घोषणा ICL_DSSM_CDCLK_PLL_REFCLK_19_2MHz	(1 << 29)
#घोषणा ICL_DSSM_CDCLK_PLL_REFCLK_38_4MHz	(2 << 29)

#घोषणा GEN7_FF_SLICE_CS_CHICKEN1	_MMIO(0x20e0)
#घोषणा   GEN9_FFSC_PERCTX_PREEMPT_CTRL	(1 << 14)

#घोषणा FF_SLICE_CS_CHICKEN2			_MMIO(0x20e4)
#घोषणा  GEN9_TSG_BARRIER_ACK_DISABLE		(1 << 8)
#घोषणा  GEN9_POOLED_EU_LOAD_BALANCING_FIX_DISABLE  (1 << 10)

#घोषणा GEN9_CS_DEBUG_MODE1		_MMIO(0x20ec)
#घोषणा   FF_DOP_CLOCK_GATE_DISABLE	REG_BIT(1)
#घोषणा GEN9_CTX_PREEMPT_REG		_MMIO(0x2248)
#घोषणा   GEN12_DISABLE_POSH_BUSY_FF_DOP_CG REG_BIT(11)

#घोषणा GEN8_CS_CHICKEN1		_MMIO(0x2580)
#घोषणा GEN9_PREEMPT_3D_OBJECT_LEVEL		(1 << 0)
#घोषणा GEN9_PREEMPT_GPGPU_LEVEL(hi, lo)	(((hi) << 2) | ((lo) << 1))
#घोषणा GEN9_PREEMPT_GPGPU_MID_THREAD_LEVEL	GEN9_PREEMPT_GPGPU_LEVEL(0, 0)
#घोषणा GEN9_PREEMPT_GPGPU_THREAD_GROUP_LEVEL	GEN9_PREEMPT_GPGPU_LEVEL(0, 1)
#घोषणा GEN9_PREEMPT_GPGPU_COMMAND_LEVEL	GEN9_PREEMPT_GPGPU_LEVEL(1, 0)
#घोषणा GEN9_PREEMPT_GPGPU_LEVEL_MASK		GEN9_PREEMPT_GPGPU_LEVEL(1, 1)

/* GEN7 chicken */
#घोषणा GEN7_COMMON_SLICE_CHICKEN1		_MMIO(0x7010)
  #घोषणा GEN7_CSC1_RHWO_OPT_DISABLE_IN_RCC	(1 << 10)
  #घोषणा GEN9_RHWO_OPTIMIZATION_DISABLE	(1 << 14)

#घोषणा COMMON_SLICE_CHICKEN2					_MMIO(0x7014)
  #घोषणा GEN9_PBE_COMPRESSED_HASH_SELECTION			(1 << 13)
  #घोषणा GEN9_DISABLE_GATHER_AT_SET_SHADER_COMMON_SLICE	(1 << 12)
  #घोषणा GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION		(1 << 8)
  #घोषणा GEN8_CSC2_SBE_VUE_CACHE_CONSERVATIVE			(1 << 0)

#घोषणा GEN8_L3CNTLREG	_MMIO(0x7034)
  #घोषणा GEN8_ERRDETBCTRL (1 << 9)

#घोषणा GEN11_COMMON_SLICE_CHICKEN3			_MMIO(0x7304)
  #घोषणा DG1_FLOAT_POINT_BLEND_OPT_STRICT_MODE_EN	REG_BIT(12)
  #घोषणा GEN11_BLEND_EMB_FIX_DISABLE_IN_RCC		REG_BIT(11)
  #घोषणा GEN12_DISABLE_CPS_AWARE_COLOR_PIPE		REG_BIT(9)

#घोषणा HIZ_CHICKEN					_MMIO(0x7018)
# define CHV_HZ_8X8_MODE_IN_1X				REG_BIT(15)
# define DG1_HZ_READ_SUPPRESSION_OPTIMIZATION_DISABLE   REG_BIT(14)
# define BDW_HIZ_POWER_COMPILER_CLOCK_GATING_DISABLE	REG_BIT(3)

#घोषणा GEN9_SLICE_COMMON_ECO_CHICKEN0		_MMIO(0x7308)
#घोषणा  DISABLE_PIXEL_MASK_CAMMING		(1 << 14)

#घोषणा GEN9_SLICE_COMMON_ECO_CHICKEN1		_MMIO(0x731c)
#घोषणा   GEN11_STATE_CACHE_REसूचीECT_TO_CS	(1 << 11)

#घोषणा GEN7_SARCHKMD				_MMIO(0xB000)
#घोषणा GEN7_DISABLE_DEMAND_PREFETCH		(1 << 31)
#घोषणा GEN7_DISABLE_SAMPLER_PREFETCH           (1 << 30)

#घोषणा GEN7_L3SQCREG1				_MMIO(0xB010)
#घोषणा  VLV_B0_WA_L3SQCREG1_VALUE		0x00D30000

#घोषणा GEN8_L3SQCREG1				_MMIO(0xB100)
/*
 * Note that on CHV the following has an off-by-one error wrt. to BSpec.
 * Using the क्रमmula in BSpec leads to a hang, जबतक the क्रमmula here works
 * fine and matches the क्रमmulas क्रम all other platक्रमms. A BSpec change
 * request has been filed to clarअगरy this.
 */
#घोषणा  L3_GENERAL_PRIO_CREDITS(x)		(((x) >> 1) << 19)
#घोषणा  L3_HIGH_PRIO_CREDITS(x)		(((x) >> 1) << 14)
#घोषणा  L3_PRIO_CREDITS_MASK			((0x1f << 19) | (0x1f << 14))

#घोषणा GEN7_L3CNTLREG1				_MMIO(0xB01C)
#घोषणा  GEN7_WA_FOR_GEN7_L3_CONTROL			0x3C47FF8C
#घोषणा  GEN7_L3AGDIS				(1 << 19)
#घोषणा GEN7_L3CNTLREG2				_MMIO(0xB020)
#घोषणा GEN7_L3CNTLREG3				_MMIO(0xB024)

#घोषणा GEN7_L3_CHICKEN_MODE_REGISTER		_MMIO(0xB030)
#घोषणा   GEN7_WA_L3_CHICKEN_MODE		0x20000000
#घोषणा GEN10_L3_CHICKEN_MODE_REGISTER		_MMIO(0xB114)
#घोषणा   GEN11_I2M_WRITE_DISABLE		(1 << 28)

#घोषणा GEN7_L3SQCREG4				_MMIO(0xb034)
#घोषणा  L3SQ_URB_READ_CAM_MATCH_DISABLE	(1 << 27)

#घोषणा GEN11_SCRATCH2					_MMIO(0xb140)
#घोषणा  GEN11_COHERENT_PARTIAL_WRITE_MERGE_ENABLE	(1 << 19)

#घोषणा GEN8_L3SQCREG4				_MMIO(0xb118)
#घोषणा  GEN11_LQSC_CLEAN_EVICT_DISABLE		(1 << 6)
#घोषणा  GEN8_LQSC_RO_PERF_DIS			(1 << 27)
#घोषणा  GEN8_LQSC_FLUSH_COHERENT_LINES		(1 << 21)
#घोषणा  GEN8_LQSQ_NONIA_COHERENT_ATOMICS_ENABLE REG_BIT(22)

/* GEN8 chicken */
#घोषणा HDC_CHICKEN0				_MMIO(0x7300)
#घोषणा CNL_HDC_CHICKEN0			_MMIO(0xE5F0)
#घोषणा ICL_HDC_MODE				_MMIO(0xE5F4)
#घोषणा  HDC_FORCE_CSR_NON_COHERENT_OVR_DISABLE	(1 << 15)
#घोषणा  HDC_FENCE_DEST_SLM_DISABLE		(1 << 14)
#घोषणा  HDC_DONOT_FETCH_MEM_WHEN_MASKED	(1 << 11)
#घोषणा  HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT	(1 << 5)
#घोषणा  HDC_FORCE_NON_COHERENT			(1 << 4)
#घोषणा  HDC_BARRIER_PERFORMANCE_DISABLE	(1 << 10)

#घोषणा GEN8_HDC_CHICKEN1			_MMIO(0x7304)

/* GEN9 chicken */
#घोषणा SLICE_ECO_CHICKEN0			_MMIO(0x7308)
#घोषणा   PIXEL_MASK_CAMMING_DISABLE		(1 << 14)

#घोषणा GEN9_WM_CHICKEN3			_MMIO(0x5588)
#घोषणा   GEN9_FACTOR_IN_CLR_VAL_HIZ		(1 << 9)

/* WaCatErrorRejectionIssue */
#घोषणा GEN7_SQ_CHICKEN_MBCUNIT_CONFIG		_MMIO(0x9030)
#घोषणा  GEN7_SQ_CHICKEN_MBCUNIT_SQINTMOB	(1 << 11)

#घोषणा HSW_SCRATCH1				_MMIO(0xb038)
#घोषणा  HSW_SCRATCH1_L3_DATA_ATOMICS_DISABLE	(1 << 27)

#घोषणा BDW_SCRATCH1					_MMIO(0xb11c)
#घोषणा  GEN9_LBS_SLA_RETRY_TIMER_DECREMENT_ENABLE	(1 << 2)

/*GEN11 chicken */
#घोषणा _PIPEA_CHICKEN				0x70038
#घोषणा _PIPEB_CHICKEN				0x71038
#घोषणा _PIPEC_CHICKEN				0x72038
#घोषणा PIPE_CHICKEN(pipe)			_MMIO_PIPE(pipe, _PIPEA_CHICKEN,\
							   _PIPEB_CHICKEN)
#घोषणा   PIXEL_ROUNDING_TRUNC_FB_PASSTHRU 	(1 << 15)
#घोषणा   PER_PIXEL_ALPHA_BYPASS_EN		(1 << 7)

#घोषणा FF_MODE2			_MMIO(0x6604)
#घोषणा   FF_MODE2_GS_TIMER_MASK	REG_GENMASK(31, 24)
#घोषणा   FF_MODE2_GS_TIMER_224		REG_FIELD_PREP(FF_MODE2_GS_TIMER_MASK, 224)
#घोषणा   FF_MODE2_TDS_TIMER_MASK	REG_GENMASK(23, 16)
#घोषणा   FF_MODE2_TDS_TIMER_128	REG_FIELD_PREP(FF_MODE2_TDS_TIMER_MASK, 4)

/* PCH */

#घोषणा PCH_DISPLAY_BASE	0xc0000u

/* south display engine पूर्णांकerrupt: IBX */
#घोषणा SDE_AUDIO_POWER_D	(1 << 27)
#घोषणा SDE_AUDIO_POWER_C	(1 << 26)
#घोषणा SDE_AUDIO_POWER_B	(1 << 25)
#घोषणा SDE_AUDIO_POWER_SHIFT	(25)
#घोषणा SDE_AUDIO_POWER_MASK	(7 << SDE_AUDIO_POWER_SHIFT)
#घोषणा SDE_GMBUS		(1 << 24)
#घोषणा SDE_AUDIO_HDCP_TRANSB	(1 << 23)
#घोषणा SDE_AUDIO_HDCP_TRANSA	(1 << 22)
#घोषणा SDE_AUDIO_HDCP_MASK	(3 << 22)
#घोषणा SDE_AUDIO_TRANSB	(1 << 21)
#घोषणा SDE_AUDIO_TRANSA	(1 << 20)
#घोषणा SDE_AUDIO_TRANS_MASK	(3 << 20)
#घोषणा SDE_POISON		(1 << 19)
/* 18 reserved */
#घोषणा SDE_FDI_RXB		(1 << 17)
#घोषणा SDE_FDI_RXA		(1 << 16)
#घोषणा SDE_FDI_MASK		(3 << 16)
#घोषणा SDE_AUXD		(1 << 15)
#घोषणा SDE_AUXC		(1 << 14)
#घोषणा SDE_AUXB		(1 << 13)
#घोषणा SDE_AUX_MASK		(7 << 13)
/* 12 reserved */
#घोषणा SDE_CRT_HOTPLUG         (1 << 11)
#घोषणा SDE_PORTD_HOTPLUG       (1 << 10)
#घोषणा SDE_PORTC_HOTPLUG       (1 << 9)
#घोषणा SDE_PORTB_HOTPLUG       (1 << 8)
#घोषणा SDE_SDVOB_HOTPLUG       (1 << 6)
#घोषणा SDE_HOTPLUG_MASK        (SDE_CRT_HOTPLUG | \
				 SDE_SDVOB_HOTPLUG |	\
				 SDE_PORTB_HOTPLUG |	\
				 SDE_PORTC_HOTPLUG |	\
				 SDE_PORTD_HOTPLUG)
#घोषणा SDE_TRANSB_CRC_DONE	(1 << 5)
#घोषणा SDE_TRANSB_CRC_ERR	(1 << 4)
#घोषणा SDE_TRANSB_FIFO_UNDER	(1 << 3)
#घोषणा SDE_TRANSA_CRC_DONE	(1 << 2)
#घोषणा SDE_TRANSA_CRC_ERR	(1 << 1)
#घोषणा SDE_TRANSA_FIFO_UNDER	(1 << 0)
#घोषणा SDE_TRANS_MASK		(0x3f)

/* south display engine पूर्णांकerrupt: CPT - CNP */
#घोषणा SDE_AUDIO_POWER_D_CPT	(1 << 31)
#घोषणा SDE_AUDIO_POWER_C_CPT	(1 << 30)
#घोषणा SDE_AUDIO_POWER_B_CPT	(1 << 29)
#घोषणा SDE_AUDIO_POWER_SHIFT_CPT   29
#घोषणा SDE_AUDIO_POWER_MASK_CPT    (7 << 29)
#घोषणा SDE_AUXD_CPT		(1 << 27)
#घोषणा SDE_AUXC_CPT		(1 << 26)
#घोषणा SDE_AUXB_CPT		(1 << 25)
#घोषणा SDE_AUX_MASK_CPT	(7 << 25)
#घोषणा SDE_PORTE_HOTPLUG_SPT	(1 << 25)
#घोषणा SDE_PORTA_HOTPLUG_SPT	(1 << 24)
#घोषणा SDE_PORTD_HOTPLUG_CPT	(1 << 23)
#घोषणा SDE_PORTC_HOTPLUG_CPT	(1 << 22)
#घोषणा SDE_PORTB_HOTPLUG_CPT	(1 << 21)
#घोषणा SDE_CRT_HOTPLUG_CPT	(1 << 19)
#घोषणा SDE_SDVOB_HOTPLUG_CPT	(1 << 18)
#घोषणा SDE_HOTPLUG_MASK_CPT	(SDE_CRT_HOTPLUG_CPT |		\
				 SDE_SDVOB_HOTPLUG_CPT |	\
				 SDE_PORTD_HOTPLUG_CPT |	\
				 SDE_PORTC_HOTPLUG_CPT |	\
				 SDE_PORTB_HOTPLUG_CPT)
#घोषणा SDE_HOTPLUG_MASK_SPT	(SDE_PORTE_HOTPLUG_SPT |	\
				 SDE_PORTD_HOTPLUG_CPT |	\
				 SDE_PORTC_HOTPLUG_CPT |	\
				 SDE_PORTB_HOTPLUG_CPT |	\
				 SDE_PORTA_HOTPLUG_SPT)
#घोषणा SDE_GMBUS_CPT		(1 << 17)
#घोषणा SDE_ERROR_CPT		(1 << 16)
#घोषणा SDE_AUDIO_CP_REQ_C_CPT	(1 << 10)
#घोषणा SDE_AUDIO_CP_CHG_C_CPT	(1 << 9)
#घोषणा SDE_FDI_RXC_CPT		(1 << 8)
#घोषणा SDE_AUDIO_CP_REQ_B_CPT	(1 << 6)
#घोषणा SDE_AUDIO_CP_CHG_B_CPT	(1 << 5)
#घोषणा SDE_FDI_RXB_CPT		(1 << 4)
#घोषणा SDE_AUDIO_CP_REQ_A_CPT	(1 << 2)
#घोषणा SDE_AUDIO_CP_CHG_A_CPT	(1 << 1)
#घोषणा SDE_FDI_RXA_CPT		(1 << 0)
#घोषणा SDE_AUDIO_CP_REQ_CPT	(SDE_AUDIO_CP_REQ_C_CPT | \
				 SDE_AUDIO_CP_REQ_B_CPT | \
				 SDE_AUDIO_CP_REQ_A_CPT)
#घोषणा SDE_AUDIO_CP_CHG_CPT	(SDE_AUDIO_CP_CHG_C_CPT | \
				 SDE_AUDIO_CP_CHG_B_CPT | \
				 SDE_AUDIO_CP_CHG_A_CPT)
#घोषणा SDE_FDI_MASK_CPT	(SDE_FDI_RXC_CPT | \
				 SDE_FDI_RXB_CPT | \
				 SDE_FDI_RXA_CPT)

/* south display engine पूर्णांकerrupt: ICP/TGP */
#घोषणा SDE_GMBUS_ICP			(1 << 23)
#घोषणा SDE_TC_HOTPLUG_ICP(hpd_pin)	REG_BIT(24 + _HPD_PIN_TC(hpd_pin))
#घोषणा SDE_DDI_HOTPLUG_ICP(hpd_pin)	REG_BIT(16 + _HPD_PIN_DDI(hpd_pin))
#घोषणा SDE_DDI_HOTPLUG_MASK_ICP	(SDE_DDI_HOTPLUG_ICP(HPD_PORT_D) | \
					 SDE_DDI_HOTPLUG_ICP(HPD_PORT_C) | \
					 SDE_DDI_HOTPLUG_ICP(HPD_PORT_B) | \
					 SDE_DDI_HOTPLUG_ICP(HPD_PORT_A))
#घोषणा SDE_TC_HOTPLUG_MASK_ICP		(SDE_TC_HOTPLUG_ICP(HPD_PORT_TC6) | \
					 SDE_TC_HOTPLUG_ICP(HPD_PORT_TC5) | \
					 SDE_TC_HOTPLUG_ICP(HPD_PORT_TC4) | \
					 SDE_TC_HOTPLUG_ICP(HPD_PORT_TC3) | \
					 SDE_TC_HOTPLUG_ICP(HPD_PORT_TC2) | \
					 SDE_TC_HOTPLUG_ICP(HPD_PORT_TC1))

#घोषणा SDEISR  _MMIO(0xc4000)
#घोषणा SDEIMR  _MMIO(0xc4004)
#घोषणा SDEIIR  _MMIO(0xc4008)
#घोषणा SDEIER  _MMIO(0xc400c)

#घोषणा SERR_INT			_MMIO(0xc4040)
#घोषणा  SERR_INT_POISON		(1 << 31)
#घोषणा  SERR_INT_TRANS_FIFO_UNDERRUN(pipe)	(1 << ((pipe) * 3))

/* digital port hotplug */
#घोषणा PCH_PORT_HOTPLUG		_MMIO(0xc4030)	/* SHOTPLUG_CTL */
#घोषणा  PORTA_HOTPLUG_ENABLE		(1 << 28) /* LPT:LP+ & BXT */
#घोषणा  BXT_DDIA_HPD_INVERT            (1 << 27)
#घोषणा  PORTA_HOTPLUG_STATUS_MASK	(3 << 24) /* SPT+ & BXT */
#घोषणा  PORTA_HOTPLUG_NO_DETECT	(0 << 24) /* SPT+ & BXT */
#घोषणा  PORTA_HOTPLUG_SHORT_DETECT	(1 << 24) /* SPT+ & BXT */
#घोषणा  PORTA_HOTPLUG_LONG_DETECT	(2 << 24) /* SPT+ & BXT */
#घोषणा  PORTD_HOTPLUG_ENABLE		(1 << 20)
#घोषणा  PORTD_PULSE_DURATION_2ms	(0 << 18) /* pre-LPT */
#घोषणा  PORTD_PULSE_DURATION_4_5ms	(1 << 18) /* pre-LPT */
#घोषणा  PORTD_PULSE_DURATION_6ms	(2 << 18) /* pre-LPT */
#घोषणा  PORTD_PULSE_DURATION_100ms	(3 << 18) /* pre-LPT */
#घोषणा  PORTD_PULSE_DURATION_MASK	(3 << 18) /* pre-LPT */
#घोषणा  PORTD_HOTPLUG_STATUS_MASK	(3 << 16)
#घोषणा  PORTD_HOTPLUG_NO_DETECT	(0 << 16)
#घोषणा  PORTD_HOTPLUG_SHORT_DETECT	(1 << 16)
#घोषणा  PORTD_HOTPLUG_LONG_DETECT	(2 << 16)
#घोषणा  PORTC_HOTPLUG_ENABLE		(1 << 12)
#घोषणा  BXT_DDIC_HPD_INVERT            (1 << 11)
#घोषणा  PORTC_PULSE_DURATION_2ms	(0 << 10) /* pre-LPT */
#घोषणा  PORTC_PULSE_DURATION_4_5ms	(1 << 10) /* pre-LPT */
#घोषणा  PORTC_PULSE_DURATION_6ms	(2 << 10) /* pre-LPT */
#घोषणा  PORTC_PULSE_DURATION_100ms	(3 << 10) /* pre-LPT */
#घोषणा  PORTC_PULSE_DURATION_MASK	(3 << 10) /* pre-LPT */
#घोषणा  PORTC_HOTPLUG_STATUS_MASK	(3 << 8)
#घोषणा  PORTC_HOTPLUG_NO_DETECT	(0 << 8)
#घोषणा  PORTC_HOTPLUG_SHORT_DETECT	(1 << 8)
#घोषणा  PORTC_HOTPLUG_LONG_DETECT	(2 << 8)
#घोषणा  PORTB_HOTPLUG_ENABLE		(1 << 4)
#घोषणा  BXT_DDIB_HPD_INVERT            (1 << 3)
#घोषणा  PORTB_PULSE_DURATION_2ms	(0 << 2) /* pre-LPT */
#घोषणा  PORTB_PULSE_DURATION_4_5ms	(1 << 2) /* pre-LPT */
#घोषणा  PORTB_PULSE_DURATION_6ms	(2 << 2) /* pre-LPT */
#घोषणा  PORTB_PULSE_DURATION_100ms	(3 << 2) /* pre-LPT */
#घोषणा  PORTB_PULSE_DURATION_MASK	(3 << 2) /* pre-LPT */
#घोषणा  PORTB_HOTPLUG_STATUS_MASK	(3 << 0)
#घोषणा  PORTB_HOTPLUG_NO_DETECT	(0 << 0)
#घोषणा  PORTB_HOTPLUG_SHORT_DETECT	(1 << 0)
#घोषणा  PORTB_HOTPLUG_LONG_DETECT	(2 << 0)
#घोषणा  BXT_DDI_HPD_INVERT_MASK	(BXT_DDIA_HPD_INVERT | \
					BXT_DDIB_HPD_INVERT | \
					BXT_DDIC_HPD_INVERT)

#घोषणा PCH_PORT_HOTPLUG2		_MMIO(0xc403C)	/* SHOTPLUG_CTL2 SPT+ */
#घोषणा  PORTE_HOTPLUG_ENABLE		(1 << 4)
#घोषणा  PORTE_HOTPLUG_STATUS_MASK	(3 << 0)
#घोषणा  PORTE_HOTPLUG_NO_DETECT	(0 << 0)
#घोषणा  PORTE_HOTPLUG_SHORT_DETECT	(1 << 0)
#घोषणा  PORTE_HOTPLUG_LONG_DETECT	(2 << 0)

/* This रेजिस्टर is a reuse of PCH_PORT_HOTPLUG रेजिस्टर. The
 * functionality covered in PCH_PORT_HOTPLUG is split पूर्णांकo
 * SHOTPLUG_CTL_DDI and SHOTPLUG_CTL_TC.
 */

#घोषणा SHOTPLUG_CTL_DDI				_MMIO(0xc4030)
#घोषणा   SHOTPLUG_CTL_DDI_HPD_ENABLE(hpd_pin)			(0x8 << (_HPD_PIN_DDI(hpd_pin) * 4))
#घोषणा   SHOTPLUG_CTL_DDI_HPD_STATUS_MASK(hpd_pin)		(0x3 << (_HPD_PIN_DDI(hpd_pin) * 4))
#घोषणा   SHOTPLUG_CTL_DDI_HPD_NO_DETECT(hpd_pin)		(0x0 << (_HPD_PIN_DDI(hpd_pin) * 4))
#घोषणा   SHOTPLUG_CTL_DDI_HPD_SHORT_DETECT(hpd_pin)		(0x1 << (_HPD_PIN_DDI(hpd_pin) * 4))
#घोषणा   SHOTPLUG_CTL_DDI_HPD_LONG_DETECT(hpd_pin)		(0x2 << (_HPD_PIN_DDI(hpd_pin) * 4))
#घोषणा   SHOTPLUG_CTL_DDI_HPD_SHORT_LONG_DETECT(hpd_pin)	(0x3 << (_HPD_PIN_DDI(hpd_pin) * 4))

#घोषणा SHOTPLUG_CTL_TC				_MMIO(0xc4034)
#घोषणा   ICP_TC_HPD_ENABLE(hpd_pin)		(8 << (_HPD_PIN_TC(hpd_pin) * 4))
#घोषणा   ICP_TC_HPD_LONG_DETECT(hpd_pin)	(2 << (_HPD_PIN_TC(hpd_pin) * 4))
#घोषणा   ICP_TC_HPD_SHORT_DETECT(hpd_pin)	(1 << (_HPD_PIN_TC(hpd_pin) * 4))

#घोषणा SHPD_FILTER_CNT				_MMIO(0xc4038)
#घोषणा   SHPD_FILTER_CNT_500_ADJ		0x001D9

#घोषणा _PCH_DPLL_A              0xc6014
#घोषणा _PCH_DPLL_B              0xc6018
#घोषणा PCH_DPLL(pll) _MMIO((pll) == 0 ? _PCH_DPLL_A : _PCH_DPLL_B)

#घोषणा _PCH_FPA0                0xc6040
#घोषणा  FP_CB_TUNE		(0x3 << 22)
#घोषणा _PCH_FPA1                0xc6044
#घोषणा _PCH_FPB0                0xc6048
#घोषणा _PCH_FPB1                0xc604c
#घोषणा PCH_FP0(pll) _MMIO((pll) == 0 ? _PCH_FPA0 : _PCH_FPB0)
#घोषणा PCH_FP1(pll) _MMIO((pll) == 0 ? _PCH_FPA1 : _PCH_FPB1)

#घोषणा PCH_DPLL_TEST           _MMIO(0xc606c)

#घोषणा PCH_DREF_CONTROL        _MMIO(0xC6200)
#घोषणा  DREF_CONTROL_MASK      0x7fc3
#घोषणा  DREF_CPU_SOURCE_OUTPUT_DISABLE         (0 << 13)
#घोषणा  DREF_CPU_SOURCE_OUTPUT_DOWNSPREAD      (2 << 13)
#घोषणा  DREF_CPU_SOURCE_OUTPUT_NONSPREAD       (3 << 13)
#घोषणा  DREF_CPU_SOURCE_OUTPUT_MASK		(3 << 13)
#घोषणा  DREF_SSC_SOURCE_DISABLE                (0 << 11)
#घोषणा  DREF_SSC_SOURCE_ENABLE                 (2 << 11)
#घोषणा  DREF_SSC_SOURCE_MASK			(3 << 11)
#घोषणा  DREF_NONSPREAD_SOURCE_DISABLE          (0 << 9)
#घोषणा  DREF_NONSPREAD_CK505_ENABLE		(1 << 9)
#घोषणा  DREF_NONSPREAD_SOURCE_ENABLE           (2 << 9)
#घोषणा  DREF_NONSPREAD_SOURCE_MASK		(3 << 9)
#घोषणा  DREF_SUPERSPREAD_SOURCE_DISABLE        (0 << 7)
#घोषणा  DREF_SUPERSPREAD_SOURCE_ENABLE         (2 << 7)
#घोषणा  DREF_SUPERSPREAD_SOURCE_MASK		(3 << 7)
#घोषणा  DREF_SSC4_DOWNSPREAD                   (0 << 6)
#घोषणा  DREF_SSC4_CENTERSPREAD                 (1 << 6)
#घोषणा  DREF_SSC1_DISABLE                      (0 << 1)
#घोषणा  DREF_SSC1_ENABLE                       (1 << 1)
#घोषणा  DREF_SSC4_DISABLE                      (0)
#घोषणा  DREF_SSC4_ENABLE                       (1)

#घोषणा PCH_RAWCLK_FREQ         _MMIO(0xc6204)
#घोषणा  FDL_TP1_TIMER_SHIFT    12
#घोषणा  FDL_TP1_TIMER_MASK     (3 << 12)
#घोषणा  FDL_TP2_TIMER_SHIFT    10
#घोषणा  FDL_TP2_TIMER_MASK     (3 << 10)
#घोषणा  RAWCLK_FREQ_MASK       0x3ff
#घोषणा  CNP_RAWCLK_DIV_MASK	(0x3ff << 16)
#घोषणा  CNP_RAWCLK_DIV(भाग)	((भाग) << 16)
#घोषणा  CNP_RAWCLK_FRAC_MASK	(0xf << 26)
#घोषणा  CNP_RAWCLK_DEN(den)	((den) << 26)
#घोषणा  ICP_RAWCLK_NUM(num)	((num) << 11)

#घोषणा PCH_DPLL_TMR_CFG        _MMIO(0xc6208)

#घोषणा PCH_SSC4_PARMS          _MMIO(0xc6210)
#घोषणा PCH_SSC4_AUX_PARMS      _MMIO(0xc6214)

#घोषणा PCH_DPLL_SEL		_MMIO(0xc7000)
#घोषणा	 TRANS_DPLLB_SEL(pipe)		(1 << ((pipe) * 4))
#घोषणा	 TRANS_DPLLA_SEL(pipe)		0
#घोषणा  TRANS_DPLL_ENABLE(pipe)	(1 << ((pipe) * 4 + 3))

/* transcoder */

#घोषणा _PCH_TRANS_HTOTAL_A		0xe0000
#घोषणा  TRANS_HTOTAL_SHIFT		16
#घोषणा  TRANS_HACTIVE_SHIFT		0
#घोषणा _PCH_TRANS_HBLANK_A		0xe0004
#घोषणा  TRANS_HBLANK_END_SHIFT		16
#घोषणा  TRANS_HBLANK_START_SHIFT	0
#घोषणा _PCH_TRANS_HSYNC_A		0xe0008
#घोषणा  TRANS_HSYNC_END_SHIFT		16
#घोषणा  TRANS_HSYNC_START_SHIFT	0
#घोषणा _PCH_TRANS_VTOTAL_A		0xe000c
#घोषणा  TRANS_VTOTAL_SHIFT		16
#घोषणा  TRANS_VACTIVE_SHIFT		0
#घोषणा _PCH_TRANS_VBLANK_A		0xe0010
#घोषणा  TRANS_VBLANK_END_SHIFT		16
#घोषणा  TRANS_VBLANK_START_SHIFT	0
#घोषणा _PCH_TRANS_VSYNC_A		0xe0014
#घोषणा  TRANS_VSYNC_END_SHIFT		16
#घोषणा  TRANS_VSYNC_START_SHIFT	0
#घोषणा _PCH_TRANS_VSYNCSHIFT_A		0xe0028

#घोषणा _PCH_TRANSA_DATA_M1	0xe0030
#घोषणा _PCH_TRANSA_DATA_N1	0xe0034
#घोषणा _PCH_TRANSA_DATA_M2	0xe0038
#घोषणा _PCH_TRANSA_DATA_N2	0xe003c
#घोषणा _PCH_TRANSA_LINK_M1	0xe0040
#घोषणा _PCH_TRANSA_LINK_N1	0xe0044
#घोषणा _PCH_TRANSA_LINK_M2	0xe0048
#घोषणा _PCH_TRANSA_LINK_N2	0xe004c

/* Per-transcoder DIP controls (PCH) */
#घोषणा _VIDEO_DIP_CTL_A         0xe0200
#घोषणा _VIDEO_DIP_DATA_A        0xe0208
#घोषणा _VIDEO_DIP_GCP_A         0xe0210
#घोषणा  GCP_COLOR_INDICATION		(1 << 2)
#घोषणा  GCP_DEFAULT_PHASE_ENABLE	(1 << 1)
#घोषणा  GCP_AV_MUTE			(1 << 0)

#घोषणा _VIDEO_DIP_CTL_B         0xe1200
#घोषणा _VIDEO_DIP_DATA_B        0xe1208
#घोषणा _VIDEO_DIP_GCP_B         0xe1210

#घोषणा TVIDEO_DIP_CTL(pipe) _MMIO_PIPE(pipe, _VIDEO_DIP_CTL_A, _VIDEO_DIP_CTL_B)
#घोषणा TVIDEO_DIP_DATA(pipe) _MMIO_PIPE(pipe, _VIDEO_DIP_DATA_A, _VIDEO_DIP_DATA_B)
#घोषणा TVIDEO_DIP_GCP(pipe) _MMIO_PIPE(pipe, _VIDEO_DIP_GCP_A, _VIDEO_DIP_GCP_B)

/* Per-transcoder DIP controls (VLV) */
#घोषणा _VLV_VIDEO_DIP_CTL_A		(VLV_DISPLAY_BASE + 0x60200)
#घोषणा _VLV_VIDEO_DIP_DATA_A		(VLV_DISPLAY_BASE + 0x60208)
#घोषणा _VLV_VIDEO_DIP_GDCP_PAYLOAD_A	(VLV_DISPLAY_BASE + 0x60210)

#घोषणा _VLV_VIDEO_DIP_CTL_B		(VLV_DISPLAY_BASE + 0x61170)
#घोषणा _VLV_VIDEO_DIP_DATA_B		(VLV_DISPLAY_BASE + 0x61174)
#घोषणा _VLV_VIDEO_DIP_GDCP_PAYLOAD_B	(VLV_DISPLAY_BASE + 0x61178)

#घोषणा _CHV_VIDEO_DIP_CTL_C		(VLV_DISPLAY_BASE + 0x611f0)
#घोषणा _CHV_VIDEO_DIP_DATA_C		(VLV_DISPLAY_BASE + 0x611f4)
#घोषणा _CHV_VIDEO_DIP_GDCP_PAYLOAD_C	(VLV_DISPLAY_BASE + 0x611f8)

#घोषणा VLV_TVIDEO_DIP_CTL(pipe) \
	_MMIO_PIPE3((pipe), _VLV_VIDEO_DIP_CTL_A, \
	       _VLV_VIDEO_DIP_CTL_B, _CHV_VIDEO_DIP_CTL_C)
#घोषणा VLV_TVIDEO_DIP_DATA(pipe) \
	_MMIO_PIPE3((pipe), _VLV_VIDEO_DIP_DATA_A, \
	       _VLV_VIDEO_DIP_DATA_B, _CHV_VIDEO_DIP_DATA_C)
#घोषणा VLV_TVIDEO_DIP_GCP(pipe) \
	_MMIO_PIPE3((pipe), _VLV_VIDEO_DIP_GDCP_PAYLOAD_A, \
		_VLV_VIDEO_DIP_GDCP_PAYLOAD_B, _CHV_VIDEO_DIP_GDCP_PAYLOAD_C)

/* Haswell DIP controls */

#घोषणा _HSW_VIDEO_DIP_CTL_A		0x60200
#घोषणा _HSW_VIDEO_DIP_AVI_DATA_A	0x60220
#घोषणा _HSW_VIDEO_DIP_VS_DATA_A	0x60260
#घोषणा _HSW_VIDEO_DIP_SPD_DATA_A	0x602A0
#घोषणा _HSW_VIDEO_DIP_GMP_DATA_A	0x602E0
#घोषणा _HSW_VIDEO_DIP_VSC_DATA_A	0x60320
#घोषणा _GLK_VIDEO_DIP_DRM_DATA_A	0x60440
#घोषणा _HSW_VIDEO_DIP_AVI_ECC_A	0x60240
#घोषणा _HSW_VIDEO_DIP_VS_ECC_A		0x60280
#घोषणा _HSW_VIDEO_DIP_SPD_ECC_A	0x602C0
#घोषणा _HSW_VIDEO_DIP_GMP_ECC_A	0x60300
#घोषणा _HSW_VIDEO_DIP_VSC_ECC_A	0x60344
#घोषणा _HSW_VIDEO_DIP_GCP_A		0x60210

#घोषणा _HSW_VIDEO_DIP_CTL_B		0x61200
#घोषणा _HSW_VIDEO_DIP_AVI_DATA_B	0x61220
#घोषणा _HSW_VIDEO_DIP_VS_DATA_B	0x61260
#घोषणा _HSW_VIDEO_DIP_SPD_DATA_B	0x612A0
#घोषणा _HSW_VIDEO_DIP_GMP_DATA_B	0x612E0
#घोषणा _HSW_VIDEO_DIP_VSC_DATA_B	0x61320
#घोषणा _GLK_VIDEO_DIP_DRM_DATA_B	0x61440
#घोषणा _HSW_VIDEO_DIP_BVI_ECC_B	0x61240
#घोषणा _HSW_VIDEO_DIP_VS_ECC_B		0x61280
#घोषणा _HSW_VIDEO_DIP_SPD_ECC_B	0x612C0
#घोषणा _HSW_VIDEO_DIP_GMP_ECC_B	0x61300
#घोषणा _HSW_VIDEO_DIP_VSC_ECC_B	0x61344
#घोषणा _HSW_VIDEO_DIP_GCP_B		0x61210

/* Icelake PPS_DATA and _ECC DIP Registers.
 * These are available क्रम transcoders B,C and eDP.
 * Adding the _A so as to reuse the _MMIO_TRANS2
 * definition, with which it offsets to the right location.
 */

#घोषणा _ICL_VIDEO_DIP_PPS_DATA_A	0x60350
#घोषणा _ICL_VIDEO_DIP_PPS_DATA_B	0x61350
#घोषणा _ICL_VIDEO_DIP_PPS_ECC_A	0x603D4
#घोषणा _ICL_VIDEO_DIP_PPS_ECC_B	0x613D4

#घोषणा HSW_TVIDEO_DIP_CTL(trans)		_MMIO_TRANS2(trans, _HSW_VIDEO_DIP_CTL_A)
#घोषणा HSW_TVIDEO_DIP_GCP(trans)		_MMIO_TRANS2(trans, _HSW_VIDEO_DIP_GCP_A)
#घोषणा HSW_TVIDEO_DIP_AVI_DATA(trans, i)	_MMIO_TRANS2(trans, _HSW_VIDEO_DIP_AVI_DATA_A + (i) * 4)
#घोषणा HSW_TVIDEO_DIP_VS_DATA(trans, i)	_MMIO_TRANS2(trans, _HSW_VIDEO_DIP_VS_DATA_A + (i) * 4)
#घोषणा HSW_TVIDEO_DIP_SPD_DATA(trans, i)	_MMIO_TRANS2(trans, _HSW_VIDEO_DIP_SPD_DATA_A + (i) * 4)
#घोषणा HSW_TVIDEO_DIP_GMP_DATA(trans, i)	_MMIO_TRANS2(trans, _HSW_VIDEO_DIP_GMP_DATA_A + (i) * 4)
#घोषणा HSW_TVIDEO_DIP_VSC_DATA(trans, i)	_MMIO_TRANS2(trans, _HSW_VIDEO_DIP_VSC_DATA_A + (i) * 4)
#घोषणा GLK_TVIDEO_DIP_DRM_DATA(trans, i)	_MMIO_TRANS2(trans, _GLK_VIDEO_DIP_DRM_DATA_A + (i) * 4)
#घोषणा ICL_VIDEO_DIP_PPS_DATA(trans, i)	_MMIO_TRANS2(trans, _ICL_VIDEO_DIP_PPS_DATA_A + (i) * 4)
#घोषणा ICL_VIDEO_DIP_PPS_ECC(trans, i)		_MMIO_TRANS2(trans, _ICL_VIDEO_DIP_PPS_ECC_A + (i) * 4)

#घोषणा _HSW_STEREO_3D_CTL_A		0x70020
#घोषणा   S3D_ENABLE			(1 << 31)
#घोषणा _HSW_STEREO_3D_CTL_B		0x71020

#घोषणा HSW_STEREO_3D_CTL(trans)	_MMIO_PIPE2(trans, _HSW_STEREO_3D_CTL_A)

#घोषणा _PCH_TRANS_HTOTAL_B          0xe1000
#घोषणा _PCH_TRANS_HBLANK_B          0xe1004
#घोषणा _PCH_TRANS_HSYNC_B           0xe1008
#घोषणा _PCH_TRANS_VTOTAL_B          0xe100c
#घोषणा _PCH_TRANS_VBLANK_B          0xe1010
#घोषणा _PCH_TRANS_VSYNC_B           0xe1014
#घोषणा _PCH_TRANS_VSYNCSHIFT_B 0xe1028

#घोषणा PCH_TRANS_HTOTAL(pipe)		_MMIO_PIPE(pipe, _PCH_TRANS_HTOTAL_A, _PCH_TRANS_HTOTAL_B)
#घोषणा PCH_TRANS_HBLANK(pipe)		_MMIO_PIPE(pipe, _PCH_TRANS_HBLANK_A, _PCH_TRANS_HBLANK_B)
#घोषणा PCH_TRANS_HSYNC(pipe)		_MMIO_PIPE(pipe, _PCH_TRANS_HSYNC_A, _PCH_TRANS_HSYNC_B)
#घोषणा PCH_TRANS_VTOTAL(pipe)		_MMIO_PIPE(pipe, _PCH_TRANS_VTOTAL_A, _PCH_TRANS_VTOTAL_B)
#घोषणा PCH_TRANS_VBLANK(pipe)		_MMIO_PIPE(pipe, _PCH_TRANS_VBLANK_A, _PCH_TRANS_VBLANK_B)
#घोषणा PCH_TRANS_VSYNC(pipe)		_MMIO_PIPE(pipe, _PCH_TRANS_VSYNC_A, _PCH_TRANS_VSYNC_B)
#घोषणा PCH_TRANS_VSYNCSHIFT(pipe)	_MMIO_PIPE(pipe, _PCH_TRANS_VSYNCSHIFT_A, _PCH_TRANS_VSYNCSHIFT_B)

#घोषणा _PCH_TRANSB_DATA_M1	0xe1030
#घोषणा _PCH_TRANSB_DATA_N1	0xe1034
#घोषणा _PCH_TRANSB_DATA_M2	0xe1038
#घोषणा _PCH_TRANSB_DATA_N2	0xe103c
#घोषणा _PCH_TRANSB_LINK_M1	0xe1040
#घोषणा _PCH_TRANSB_LINK_N1	0xe1044
#घोषणा _PCH_TRANSB_LINK_M2	0xe1048
#घोषणा _PCH_TRANSB_LINK_N2	0xe104c

#घोषणा PCH_TRANS_DATA_M1(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSA_DATA_M1, _PCH_TRANSB_DATA_M1)
#घोषणा PCH_TRANS_DATA_N1(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSA_DATA_N1, _PCH_TRANSB_DATA_N1)
#घोषणा PCH_TRANS_DATA_M2(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSA_DATA_M2, _PCH_TRANSB_DATA_M2)
#घोषणा PCH_TRANS_DATA_N2(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSA_DATA_N2, _PCH_TRANSB_DATA_N2)
#घोषणा PCH_TRANS_LINK_M1(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSA_LINK_M1, _PCH_TRANSB_LINK_M1)
#घोषणा PCH_TRANS_LINK_N1(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSA_LINK_N1, _PCH_TRANSB_LINK_N1)
#घोषणा PCH_TRANS_LINK_M2(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSA_LINK_M2, _PCH_TRANSB_LINK_M2)
#घोषणा PCH_TRANS_LINK_N2(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSA_LINK_N2, _PCH_TRANSB_LINK_N2)

#घोषणा _PCH_TRANSACONF              0xf0008
#घोषणा _PCH_TRANSBCONF              0xf1008
#घोषणा PCH_TRANSCONF(pipe)	_MMIO_PIPE(pipe, _PCH_TRANSACONF, _PCH_TRANSBCONF)
#घोषणा LPT_TRANSCONF		PCH_TRANSCONF(PIPE_A) /* lpt has only one transcoder */
#घोषणा  TRANS_DISABLE          (0 << 31)
#घोषणा  TRANS_ENABLE           (1 << 31)
#घोषणा  TRANS_STATE_MASK       (1 << 30)
#घोषणा  TRANS_STATE_DISABLE    (0 << 30)
#घोषणा  TRANS_STATE_ENABLE     (1 << 30)
#घोषणा  TRANS_FRAME_START_DELAY_MASK	(3 << 27) /* ibx */
#घोषणा  TRANS_FRAME_START_DELAY(x)	((x) << 27) /* ibx: 0-3 */
#घोषणा  TRANS_INTERLACE_MASK   (7 << 21)
#घोषणा  TRANS_PROGRESSIVE      (0 << 21)
#घोषणा  TRANS_INTERLACED       (3 << 21)
#घोषणा  TRANS_LEGACY_INTERLACED_ILK (2 << 21)
#घोषणा  TRANS_8BPC             (0 << 5)
#घोषणा  TRANS_10BPC            (1 << 5)
#घोषणा  TRANS_6BPC             (2 << 5)
#घोषणा  TRANS_12BPC            (3 << 5)

#घोषणा _TRANSA_CHICKEN1	 0xf0060
#घोषणा _TRANSB_CHICKEN1	 0xf1060
#घोषणा TRANS_CHICKEN1(pipe)	_MMIO_PIPE(pipe, _TRANSA_CHICKEN1, _TRANSB_CHICKEN1)
#घोषणा  TRANS_CHICKEN1_HDMIUNIT_GC_DISABLE	(1 << 10)
#घोषणा  TRANS_CHICKEN1_DP0UNIT_GC_DISABLE	(1 << 4)
#घोषणा _TRANSA_CHICKEN2	 0xf0064
#घोषणा _TRANSB_CHICKEN2	 0xf1064
#घोषणा TRANS_CHICKEN2(pipe)	_MMIO_PIPE(pipe, _TRANSA_CHICKEN2, _TRANSB_CHICKEN2)
#घोषणा  TRANS_CHICKEN2_TIMING_OVERRIDE			(1 << 31)
#घोषणा  TRANS_CHICKEN2_FDI_POLARITY_REVERSED		(1 << 29)
#घोषणा  TRANS_CHICKEN2_FRAME_START_DELAY_MASK		(3 << 27)
#घोषणा  TRANS_CHICKEN2_FRAME_START_DELAY(x)		((x) << 27) /* 0-3 */
#घोषणा  TRANS_CHICKEN2_DISABLE_DEEP_COLOR_COUNTER	(1 << 26)
#घोषणा  TRANS_CHICKEN2_DISABLE_DEEP_COLOR_MODESWITCH	(1 << 25)

#घोषणा SOUTH_CHICKEN1		_MMIO(0xc2000)
#घोषणा  FDIA_PHASE_SYNC_SHIFT_OVR	19
#घोषणा  FDIA_PHASE_SYNC_SHIFT_EN	18
#घोषणा  INVERT_DDID_HPD			(1 << 18)
#घोषणा  INVERT_DDIC_HPD			(1 << 17)
#घोषणा  INVERT_DDIB_HPD			(1 << 16)
#घोषणा  INVERT_DDIA_HPD			(1 << 15)
#घोषणा  FDI_PHASE_SYNC_OVR(pipe) (1 << (FDIA_PHASE_SYNC_SHIFT_OVR - ((pipe) * 2)))
#घोषणा  FDI_PHASE_SYNC_EN(pipe) (1 << (FDIA_PHASE_SYNC_SHIFT_EN - ((pipe) * 2)))
#घोषणा  FDI_BC_BIFURCATION_SELECT	(1 << 12)
#घोषणा  CHASSIS_CLK_REQ_DURATION_MASK	(0xf << 8)
#घोषणा  CHASSIS_CLK_REQ_DURATION(x)	((x) << 8)
#घोषणा  SBCLK_RUN_REFCLK_DIS		(1 << 7)
#घोषणा  SPT_PWM_GRANULARITY		(1 << 0)
#घोषणा SOUTH_CHICKEN2		_MMIO(0xc2004)
#घोषणा  FDI_MPHY_IOSFSB_RESET_STATUS	(1 << 13)
#घोषणा  FDI_MPHY_IOSFSB_RESET_CTL	(1 << 12)
#घोषणा  LPT_PWM_GRANULARITY		(1 << 5)
#घोषणा  DPLS_EDP_PPS_FIX_DIS		(1 << 0)

#घोषणा _FDI_RXA_CHICKEN        0xc200c
#घोषणा _FDI_RXB_CHICKEN        0xc2010
#घोषणा  FDI_RX_PHASE_SYNC_POINTER_OVR	(1 << 1)
#घोषणा  FDI_RX_PHASE_SYNC_POINTER_EN	(1 << 0)
#घोषणा FDI_RX_CHICKEN(pipe)	_MMIO_PIPE(pipe, _FDI_RXA_CHICKEN, _FDI_RXB_CHICKEN)

#घोषणा SOUTH_DSPCLK_GATE_D	_MMIO(0xc2020)
#घोषणा  PCH_GMBUSUNIT_CLOCK_GATE_DISABLE (1 << 31)
#घोषणा  PCH_DPLUNIT_CLOCK_GATE_DISABLE (1 << 30)
#घोषणा  PCH_DPLSUNIT_CLOCK_GATE_DISABLE (1 << 29)
#घोषणा  PCH_DPMGUNIT_CLOCK_GATE_DISABLE (1 << 15)
#घोषणा  PCH_CPUNIT_CLOCK_GATE_DISABLE (1 << 14)
#घोषणा  CNP_PWM_CGE_GATING_DISABLE (1 << 13)
#घोषणा  PCH_LP_PARTITION_LEVEL_DISABLE  (1 << 12)

/* CPU: FDI_TX */
#घोषणा _FDI_TXA_CTL            0x60100
#घोषणा _FDI_TXB_CTL            0x61100
#घोषणा FDI_TX_CTL(pipe)	_MMIO_PIPE(pipe, _FDI_TXA_CTL, _FDI_TXB_CTL)
#घोषणा  FDI_TX_DISABLE         (0 << 31)
#घोषणा  FDI_TX_ENABLE          (1 << 31)
#घोषणा  FDI_LINK_TRAIN_PATTERN_1       (0 << 28)
#घोषणा  FDI_LINK_TRAIN_PATTERN_2       (1 << 28)
#घोषणा  FDI_LINK_TRAIN_PATTERN_IDLE    (2 << 28)
#घोषणा  FDI_LINK_TRAIN_NONE            (3 << 28)
#घोषणा  FDI_LINK_TRAIN_VOLTAGE_0_4V    (0 << 25)
#घोषणा  FDI_LINK_TRAIN_VOLTAGE_0_6V    (1 << 25)
#घोषणा  FDI_LINK_TRAIN_VOLTAGE_0_8V    (2 << 25)
#घोषणा  FDI_LINK_TRAIN_VOLTAGE_1_2V    (3 << 25)
#घोषणा  FDI_LINK_TRAIN_PRE_EMPHASIS_NONE (0 << 22)
#घोषणा  FDI_LINK_TRAIN_PRE_EMPHASIS_1_5X (1 << 22)
#घोषणा  FDI_LINK_TRAIN_PRE_EMPHASIS_2X   (2 << 22)
#घोषणा  FDI_LINK_TRAIN_PRE_EMPHASIS_3X   (3 << 22)
/* ILK always use 400mV 0dB क्रम voltage swing and pre-emphasis level.
   SNB has dअगरferent settings. */
/* SNB A-stepping */
#घोषणा  FDI_LINK_TRAIN_400MV_0DB_SNB_A		(0x38 << 22)
#घोषणा  FDI_LINK_TRAIN_400MV_6DB_SNB_A		(0x02 << 22)
#घोषणा  FDI_LINK_TRAIN_600MV_3_5DB_SNB_A	(0x01 << 22)
#घोषणा  FDI_LINK_TRAIN_800MV_0DB_SNB_A		(0x0 << 22)
/* SNB B-stepping */
#घोषणा  FDI_LINK_TRAIN_400MV_0DB_SNB_B		(0x0 << 22)
#घोषणा  FDI_LINK_TRAIN_400MV_6DB_SNB_B		(0x3a << 22)
#घोषणा  FDI_LINK_TRAIN_600MV_3_5DB_SNB_B	(0x39 << 22)
#घोषणा  FDI_LINK_TRAIN_800MV_0DB_SNB_B		(0x38 << 22)
#घोषणा  FDI_LINK_TRAIN_VOL_EMP_MASK		(0x3f << 22)
#घोषणा  FDI_DP_PORT_WIDTH_SHIFT		19
#घोषणा  FDI_DP_PORT_WIDTH_MASK			(7 << FDI_DP_PORT_WIDTH_SHIFT)
#घोषणा  FDI_DP_PORT_WIDTH(width)           (((width) - 1) << FDI_DP_PORT_WIDTH_SHIFT)
#घोषणा  FDI_TX_ENHANCE_FRAME_ENABLE    (1 << 18)
/* Ironlake: hardwired to 1 */
#घोषणा  FDI_TX_PLL_ENABLE              (1 << 14)

/* Ivybridge has dअगरferent bits क्रम lolz */
#घोषणा  FDI_LINK_TRAIN_PATTERN_1_IVB       (0 << 8)
#घोषणा  FDI_LINK_TRAIN_PATTERN_2_IVB       (1 << 8)
#घोषणा  FDI_LINK_TRAIN_PATTERN_IDLE_IVB    (2 << 8)
#घोषणा  FDI_LINK_TRAIN_NONE_IVB            (3 << 8)

/* both Tx and Rx */
#घोषणा  FDI_COMPOSITE_SYNC		(1 << 11)
#घोषणा  FDI_LINK_TRAIN_AUTO		(1 << 10)
#घोषणा  FDI_SCRAMBLING_ENABLE          (0 << 7)
#घोषणा  FDI_SCRAMBLING_DISABLE         (1 << 7)

/* FDI_RX, FDI_X is hard-wired to Transcoder_X */
#घोषणा _FDI_RXA_CTL             0xf000c
#घोषणा _FDI_RXB_CTL             0xf100c
#घोषणा FDI_RX_CTL(pipe)	_MMIO_PIPE(pipe, _FDI_RXA_CTL, _FDI_RXB_CTL)
#घोषणा  FDI_RX_ENABLE          (1 << 31)
/* train, dp width same as FDI_TX */
#घोषणा  FDI_FS_ERRC_ENABLE		(1 << 27)
#घोषणा  FDI_FE_ERRC_ENABLE		(1 << 26)
#घोषणा  FDI_RX_POLARITY_REVERSED_LPT	(1 << 16)
#घोषणा  FDI_8BPC                       (0 << 16)
#घोषणा  FDI_10BPC                      (1 << 16)
#घोषणा  FDI_6BPC                       (2 << 16)
#घोषणा  FDI_12BPC                      (3 << 16)
#घोषणा  FDI_RX_LINK_REVERSAL_OVERRIDE  (1 << 15)
#घोषणा  FDI_DMI_LINK_REVERSE_MASK      (1 << 14)
#घोषणा  FDI_RX_PLL_ENABLE              (1 << 13)
#घोषणा  FDI_FS_ERR_CORRECT_ENABLE      (1 << 11)
#घोषणा  FDI_FE_ERR_CORRECT_ENABLE      (1 << 10)
#घोषणा  FDI_FS_ERR_REPORT_ENABLE       (1 << 9)
#घोषणा  FDI_FE_ERR_REPORT_ENABLE       (1 << 8)
#घोषणा  FDI_RX_ENHANCE_FRAME_ENABLE    (1 << 6)
#घोषणा  FDI_PCDCLK	                (1 << 4)
/* CPT */
#घोषणा  FDI_AUTO_TRAINING			(1 << 10)
#घोषणा  FDI_LINK_TRAIN_PATTERN_1_CPT		(0 << 8)
#घोषणा  FDI_LINK_TRAIN_PATTERN_2_CPT		(1 << 8)
#घोषणा  FDI_LINK_TRAIN_PATTERN_IDLE_CPT	(2 << 8)
#घोषणा  FDI_LINK_TRAIN_NORMAL_CPT		(3 << 8)
#घोषणा  FDI_LINK_TRAIN_PATTERN_MASK_CPT	(3 << 8)

#घोषणा _FDI_RXA_MISC			0xf0010
#घोषणा _FDI_RXB_MISC			0xf1010
#घोषणा  FDI_RX_PWRDN_LANE1_MASK	(3 << 26)
#घोषणा  FDI_RX_PWRDN_LANE1_VAL(x)	((x) << 26)
#घोषणा  FDI_RX_PWRDN_LANE0_MASK	(3 << 24)
#घोषणा  FDI_RX_PWRDN_LANE0_VAL(x)	((x) << 24)
#घोषणा  FDI_RX_TP1_TO_TP2_48		(2 << 20)
#घोषणा  FDI_RX_TP1_TO_TP2_64		(3 << 20)
#घोषणा  FDI_RX_FDI_DELAY_90		(0x90 << 0)
#घोषणा FDI_RX_MISC(pipe)	_MMIO_PIPE(pipe, _FDI_RXA_MISC, _FDI_RXB_MISC)

#घोषणा _FDI_RXA_TUSIZE1        0xf0030
#घोषणा _FDI_RXA_TUSIZE2        0xf0038
#घोषणा _FDI_RXB_TUSIZE1        0xf1030
#घोषणा _FDI_RXB_TUSIZE2        0xf1038
#घोषणा FDI_RX_TUSIZE1(pipe)	_MMIO_PIPE(pipe, _FDI_RXA_TUSIZE1, _FDI_RXB_TUSIZE1)
#घोषणा FDI_RX_TUSIZE2(pipe)	_MMIO_PIPE(pipe, _FDI_RXA_TUSIZE2, _FDI_RXB_TUSIZE2)

/* FDI_RX पूर्णांकerrupt रेजिस्टर क्रमmat */
#घोषणा FDI_RX_INTER_LANE_ALIGN         (1 << 10)
#घोषणा FDI_RX_SYMBOL_LOCK              (1 << 9) /* train 2 */
#घोषणा FDI_RX_BIT_LOCK                 (1 << 8) /* train 1 */
#घोषणा FDI_RX_TRAIN_PATTERN_2_FAIL     (1 << 7)
#घोषणा FDI_RX_FS_CODE_ERR              (1 << 6)
#घोषणा FDI_RX_FE_CODE_ERR              (1 << 5)
#घोषणा FDI_RX_SYMBOL_ERR_RATE_ABOVE    (1 << 4)
#घोषणा FDI_RX_HDCP_LINK_FAIL           (1 << 3)
#घोषणा FDI_RX_PIXEL_FIFO_OVERFLOW      (1 << 2)
#घोषणा FDI_RX_CROSS_CLOCK_OVERFLOW     (1 << 1)
#घोषणा FDI_RX_SYMBOL_QUEUE_OVERFLOW    (1 << 0)

#घोषणा _FDI_RXA_IIR            0xf0014
#घोषणा _FDI_RXA_IMR            0xf0018
#घोषणा _FDI_RXB_IIR            0xf1014
#घोषणा _FDI_RXB_IMR            0xf1018
#घोषणा FDI_RX_IIR(pipe)	_MMIO_PIPE(pipe, _FDI_RXA_IIR, _FDI_RXB_IIR)
#घोषणा FDI_RX_IMR(pipe)	_MMIO_PIPE(pipe, _FDI_RXA_IMR, _FDI_RXB_IMR)

#घोषणा FDI_PLL_CTL_1           _MMIO(0xfe000)
#घोषणा FDI_PLL_CTL_2           _MMIO(0xfe004)

#घोषणा PCH_LVDS	_MMIO(0xe1180)
#घोषणा  LVDS_DETECTED	(1 << 1)

#घोषणा _PCH_DP_B		0xe4100
#घोषणा PCH_DP_B		_MMIO(_PCH_DP_B)
#घोषणा _PCH_DPB_AUX_CH_CTL	0xe4110
#घोषणा _PCH_DPB_AUX_CH_DATA1	0xe4114
#घोषणा _PCH_DPB_AUX_CH_DATA2	0xe4118
#घोषणा _PCH_DPB_AUX_CH_DATA3	0xe411c
#घोषणा _PCH_DPB_AUX_CH_DATA4	0xe4120
#घोषणा _PCH_DPB_AUX_CH_DATA5	0xe4124

#घोषणा _PCH_DP_C		0xe4200
#घोषणा PCH_DP_C		_MMIO(_PCH_DP_C)
#घोषणा _PCH_DPC_AUX_CH_CTL	0xe4210
#घोषणा _PCH_DPC_AUX_CH_DATA1	0xe4214
#घोषणा _PCH_DPC_AUX_CH_DATA2	0xe4218
#घोषणा _PCH_DPC_AUX_CH_DATA3	0xe421c
#घोषणा _PCH_DPC_AUX_CH_DATA4	0xe4220
#घोषणा _PCH_DPC_AUX_CH_DATA5	0xe4224

#घोषणा _PCH_DP_D		0xe4300
#घोषणा PCH_DP_D		_MMIO(_PCH_DP_D)
#घोषणा _PCH_DPD_AUX_CH_CTL	0xe4310
#घोषणा _PCH_DPD_AUX_CH_DATA1	0xe4314
#घोषणा _PCH_DPD_AUX_CH_DATA2	0xe4318
#घोषणा _PCH_DPD_AUX_CH_DATA3	0xe431c
#घोषणा _PCH_DPD_AUX_CH_DATA4	0xe4320
#घोषणा _PCH_DPD_AUX_CH_DATA5	0xe4324

#घोषणा PCH_DP_AUX_CH_CTL(aux_ch)		_MMIO_PORT((aux_ch) - AUX_CH_B, _PCH_DPB_AUX_CH_CTL, _PCH_DPC_AUX_CH_CTL)
#घोषणा PCH_DP_AUX_CH_DATA(aux_ch, i)	_MMIO(_PORT((aux_ch) - AUX_CH_B, _PCH_DPB_AUX_CH_DATA1, _PCH_DPC_AUX_CH_DATA1) + (i) * 4) /* 5 रेजिस्टरs */

/* CPT */
#घोषणा _TRANS_DP_CTL_A		0xe0300
#घोषणा _TRANS_DP_CTL_B		0xe1300
#घोषणा _TRANS_DP_CTL_C		0xe2300
#घोषणा TRANS_DP_CTL(pipe)	_MMIO_PIPE(pipe, _TRANS_DP_CTL_A, _TRANS_DP_CTL_B)
#घोषणा  TRANS_DP_OUTPUT_ENABLE	(1 << 31)
#घोषणा  TRANS_DP_PORT_SEL_MASK		(3 << 29)
#घोषणा  TRANS_DP_PORT_SEL_NONE		(3 << 29)
#घोषणा  TRANS_DP_PORT_SEL(port)	(((port) - PORT_B) << 29)
#घोषणा  TRANS_DP_AUDIO_ONLY	(1 << 26)
#घोषणा  TRANS_DP_ENH_FRAMING	(1 << 18)
#घोषणा  TRANS_DP_8BPC		(0 << 9)
#घोषणा  TRANS_DP_10BPC		(1 << 9)
#घोषणा  TRANS_DP_6BPC		(2 << 9)
#घोषणा  TRANS_DP_12BPC		(3 << 9)
#घोषणा  TRANS_DP_BPC_MASK	(3 << 9)
#घोषणा  TRANS_DP_VSYNC_ACTIVE_HIGH	(1 << 4)
#घोषणा  TRANS_DP_VSYNC_ACTIVE_LOW	0
#घोषणा  TRANS_DP_HSYNC_ACTIVE_HIGH	(1 << 3)
#घोषणा  TRANS_DP_HSYNC_ACTIVE_LOW	0
#घोषणा  TRANS_DP_SYNC_MASK	(3 << 3)

/* SNB eDP training params */
/* SNB A-stepping */
#घोषणा  EDP_LINK_TRAIN_400MV_0DB_SNB_A		(0x38 << 22)
#घोषणा  EDP_LINK_TRAIN_400MV_6DB_SNB_A		(0x02 << 22)
#घोषणा  EDP_LINK_TRAIN_600MV_3_5DB_SNB_A	(0x01 << 22)
#घोषणा  EDP_LINK_TRAIN_800MV_0DB_SNB_A		(0x0 << 22)
/* SNB B-stepping */
#घोषणा  EDP_LINK_TRAIN_400_600MV_0DB_SNB_B	(0x0 << 22)
#घोषणा  EDP_LINK_TRAIN_400MV_3_5DB_SNB_B	(0x1 << 22)
#घोषणा  EDP_LINK_TRAIN_400_600MV_6DB_SNB_B	(0x3a << 22)
#घोषणा  EDP_LINK_TRAIN_600_800MV_3_5DB_SNB_B	(0x39 << 22)
#घोषणा  EDP_LINK_TRAIN_800_1200MV_0DB_SNB_B	(0x38 << 22)
#घोषणा  EDP_LINK_TRAIN_VOL_EMP_MASK_SNB	(0x3f << 22)

/* IVB */
#घोषणा EDP_LINK_TRAIN_400MV_0DB_IVB		(0x24 << 22)
#घोषणा EDP_LINK_TRAIN_400MV_3_5DB_IVB		(0x2a << 22)
#घोषणा EDP_LINK_TRAIN_400MV_6DB_IVB		(0x2f << 22)
#घोषणा EDP_LINK_TRAIN_600MV_0DB_IVB		(0x30 << 22)
#घोषणा EDP_LINK_TRAIN_600MV_3_5DB_IVB		(0x36 << 22)
#घोषणा EDP_LINK_TRAIN_800MV_0DB_IVB		(0x38 << 22)
#घोषणा EDP_LINK_TRAIN_800MV_3_5DB_IVB		(0x3e << 22)

/* legacy values */
#घोषणा EDP_LINK_TRAIN_500MV_0DB_IVB		(0x00 << 22)
#घोषणा EDP_LINK_TRAIN_1000MV_0DB_IVB		(0x20 << 22)
#घोषणा EDP_LINK_TRAIN_500MV_3_5DB_IVB		(0x02 << 22)
#घोषणा EDP_LINK_TRAIN_1000MV_3_5DB_IVB		(0x22 << 22)
#घोषणा EDP_LINK_TRAIN_1000MV_6DB_IVB		(0x23 << 22)

#घोषणा  EDP_LINK_TRAIN_VOL_EMP_MASK_IVB	(0x3f << 22)

#घोषणा  VLV_PMWGICZ				_MMIO(0x1300a4)

#घोषणा  RC6_LOCATION				_MMIO(0xD40)
#घोषणा	   RC6_CTX_IN_DRAM			(1 << 0)
#घोषणा  RC6_CTX_BASE				_MMIO(0xD48)
#घोषणा    RC6_CTX_BASE_MASK			0xFFFFFFF0
#घोषणा  PWRCTX_MAXCNT_RCSUNIT			_MMIO(0x2054)
#घोषणा  PWRCTX_MAXCNT_VCSUNIT0			_MMIO(0x12054)
#घोषणा  PWRCTX_MAXCNT_BCSUNIT			_MMIO(0x22054)
#घोषणा  PWRCTX_MAXCNT_VECSUNIT			_MMIO(0x1A054)
#घोषणा  PWRCTX_MAXCNT_VCSUNIT1			_MMIO(0x1C054)
#घोषणा    IDLE_TIME_MASK			0xFFFFF
#घोषणा  FORCEWAKE				_MMIO(0xA18C)
#घोषणा  FORCEWAKE_VLV				_MMIO(0x1300b0)
#घोषणा  FORCEWAKE_ACK_VLV			_MMIO(0x1300b4)
#घोषणा  FORCEWAKE_MEDIA_VLV			_MMIO(0x1300b8)
#घोषणा  FORCEWAKE_ACK_MEDIA_VLV		_MMIO(0x1300bc)
#घोषणा  FORCEWAKE_ACK_HSW			_MMIO(0x130044)
#घोषणा  FORCEWAKE_ACK				_MMIO(0x130090)
#घोषणा  VLV_GTLC_WAKE_CTRL			_MMIO(0x130090)
#घोषणा   VLV_GTLC_RENDER_CTX_EXISTS		(1 << 25)
#घोषणा   VLV_GTLC_MEDIA_CTX_EXISTS		(1 << 24)
#घोषणा   VLV_GTLC_ALLOWWAKEREQ			(1 << 0)

#घोषणा  VLV_GTLC_PW_STATUS			_MMIO(0x130094)
#घोषणा   VLV_GTLC_ALLOWWAKEACK			(1 << 0)
#घोषणा   VLV_GTLC_ALLOWWAKEERR			(1 << 1)
#घोषणा   VLV_GTLC_PW_MEDIA_STATUS_MASK		(1 << 5)
#घोषणा   VLV_GTLC_PW_RENDER_STATUS_MASK	(1 << 7)
#घोषणा  FORCEWAKE_MT				_MMIO(0xa188) /* multi-thपढ़ोed */
#घोषणा  FORCEWAKE_MEDIA_GEN9			_MMIO(0xa270)
#घोषणा  FORCEWAKE_MEDIA_VDBOX_GEN11(n)		_MMIO(0xa540 + (n) * 4)
#घोषणा  FORCEWAKE_MEDIA_VEBOX_GEN11(n)		_MMIO(0xa560 + (n) * 4)
#घोषणा  FORCEWAKE_RENDER_GEN9			_MMIO(0xa278)
#घोषणा  FORCEWAKE_GT_GEN9			_MMIO(0xa188)
#घोषणा  FORCEWAKE_ACK_MEDIA_GEN9		_MMIO(0x0D88)
#घोषणा  FORCEWAKE_ACK_MEDIA_VDBOX_GEN11(n)	_MMIO(0x0D50 + (n) * 4)
#घोषणा  FORCEWAKE_ACK_MEDIA_VEBOX_GEN11(n)	_MMIO(0x0D70 + (n) * 4)
#घोषणा  FORCEWAKE_ACK_RENDER_GEN9		_MMIO(0x0D84)
#घोषणा  FORCEWAKE_ACK_GT_GEN9			_MMIO(0x130044)
#घोषणा   FORCEWAKE_KERNEL			BIT(0)
#घोषणा   FORCEWAKE_USER			BIT(1)
#घोषणा   FORCEWAKE_KERNEL_FALLBACK		BIT(15)
#घोषणा  FORCEWAKE_MT_ACK			_MMIO(0x130040)
#घोषणा  ECOBUS					_MMIO(0xa180)
#घोषणा    FORCEWAKE_MT_ENABLE			(1 << 5)
#घोषणा  VLV_SPAREG2H				_MMIO(0xA194)
#घोषणा  GEN9_PWRGT_DOMAIN_STATUS		_MMIO(0xA2A0)
#घोषणा   GEN9_PWRGT_MEDIA_STATUS_MASK		(1 << 0)
#घोषणा   GEN9_PWRGT_RENDER_STATUS_MASK		(1 << 1)

#घोषणा  GTFIFODBG				_MMIO(0x120000)
#घोषणा    GT_FIFO_SBDEDICATE_FREE_ENTRY_CHV	(0x1f << 20)
#घोषणा    GT_FIFO_FREE_ENTRIES_CHV		(0x7f << 13)
#घोषणा    GT_FIFO_SBDROPERR			(1 << 6)
#घोषणा    GT_FIFO_BLOBDROPERR			(1 << 5)
#घोषणा    GT_FIFO_SB_READ_ABORTERR		(1 << 4)
#घोषणा    GT_FIFO_DROPERR			(1 << 3)
#घोषणा    GT_FIFO_OVFERR			(1 << 2)
#घोषणा    GT_FIFO_IAWRERR			(1 << 1)
#घोषणा    GT_FIFO_IARDERR			(1 << 0)

#घोषणा  GTFIFOCTL				_MMIO(0x120008)
#घोषणा    GT_FIFO_FREE_ENTRIES_MASK		0x7f
#घोषणा    GT_FIFO_NUM_RESERVED_ENTRIES		20
#घोषणा    GT_FIFO_CTL_BLOCK_ALL_POLICY_STALL	(1 << 12)
#घोषणा    GT_FIFO_CTL_RC6_POLICY_STALL		(1 << 11)

#घोषणा  HSW_IDICR				_MMIO(0x9008)
#घोषणा    IDIHASHMSK(x)			(((x) & 0x3f) << 16)
#घोषणा  HSW_EDRAM_CAP				_MMIO(0x120010)
#घोषणा    EDRAM_ENABLED			0x1
#घोषणा    EDRAM_NUM_BANKS(cap)			(((cap) >> 1) & 0xf)
#घोषणा    EDRAM_WAYS_IDX(cap)			(((cap) >> 5) & 0x7)
#घोषणा    EDRAM_SETS_IDX(cap)			(((cap) >> 8) & 0x3)

#घोषणा GEN6_UCGCTL1				_MMIO(0x9400)
# define GEN6_GAMUNIT_CLOCK_GATE_DISABLE		(1 << 22)
# define GEN6_EU_TCUNIT_CLOCK_GATE_DISABLE		(1 << 16)
# define GEN6_BLBUNIT_CLOCK_GATE_DISABLE		(1 << 5)
# define GEN6_CSUNIT_CLOCK_GATE_DISABLE			(1 << 7)

#घोषणा GEN6_UCGCTL2				_MMIO(0x9404)
# define GEN6_VFUNIT_CLOCK_GATE_DISABLE			(1 << 31)
# define GEN7_VDSUNIT_CLOCK_GATE_DISABLE		(1 << 30)
# define GEN7_TDLUNIT_CLOCK_GATE_DISABLE		(1 << 22)
# define GEN6_RCZUNIT_CLOCK_GATE_DISABLE		(1 << 13)
# define GEN6_RCPBUNIT_CLOCK_GATE_DISABLE		(1 << 12)
# define GEN6_RCCUNIT_CLOCK_GATE_DISABLE		(1 << 11)

#घोषणा GEN6_UCGCTL3				_MMIO(0x9408)
# define GEN6_OACSUNIT_CLOCK_GATE_DISABLE		(1 << 20)

#घोषणा GEN7_UCGCTL4				_MMIO(0x940c)
#घोषणा  GEN7_L3BANK2X_CLOCK_GATE_DISABLE	(1 << 25)
#घोषणा  GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE	(1 << 14)

#घोषणा GEN6_RCGCTL1				_MMIO(0x9410)
#घोषणा GEN6_RCGCTL2				_MMIO(0x9414)
#घोषणा GEN6_RSTCTL				_MMIO(0x9420)

#घोषणा GEN8_UCGCTL6				_MMIO(0x9430)
#घोषणा   GEN8_GAPSUNIT_CLOCK_GATE_DISABLE	(1 << 24)
#घोषणा   GEN8_SDEUNIT_CLOCK_GATE_DISABLE	(1 << 14)
#घोषणा   GEN8_HDCUNIT_CLOCK_GATE_DISABLE_HDCREQ (1 << 28)

#घोषणा GEN6_GFXPAUSE				_MMIO(0xA000)
#घोषणा GEN6_RPNSWREQ				_MMIO(0xA008)
#घोषणा   GEN6_TURBO_DISABLE			(1 << 31)
#घोषणा   GEN6_FREQUENCY(x)			((x) << 25)
#घोषणा   HSW_FREQUENCY(x)			((x) << 24)
#घोषणा   GEN9_FREQUENCY(x)			((x) << 23)
#घोषणा   GEN6_OFFSET(x)			((x) << 19)
#घोषणा   GEN6_AGGRESSIVE_TURBO			(0 << 15)
#घोषणा GEN6_RC_VIDEO_FREQ			_MMIO(0xA00C)
#घोषणा GEN6_RC_CONTROL				_MMIO(0xA090)
#घोषणा   GEN6_RC_CTL_RC6pp_ENABLE		(1 << 16)
#घोषणा   GEN6_RC_CTL_RC6p_ENABLE		(1 << 17)
#घोषणा   GEN6_RC_CTL_RC6_ENABLE		(1 << 18)
#घोषणा   GEN6_RC_CTL_RC1e_ENABLE		(1 << 20)
#घोषणा   GEN6_RC_CTL_RC7_ENABLE		(1 << 22)
#घोषणा   VLV_RC_CTL_CTX_RST_PARALLEL		(1 << 24)
#घोषणा   GEN7_RC_CTL_TO_MODE			(1 << 28)
#घोषणा   GEN6_RC_CTL_EI_MODE(x)		((x) << 27)
#घोषणा   GEN6_RC_CTL_HW_ENABLE			(1 << 31)
#घोषणा GEN6_RP_DOWN_TIMEOUT			_MMIO(0xA010)
#घोषणा GEN6_RP_INTERRUPT_LIMITS		_MMIO(0xA014)
#घोषणा GEN6_RPSTAT1				_MMIO(0xA01C)
#घोषणा   GEN6_CAGF_SHIFT			8
#घोषणा   HSW_CAGF_SHIFT			7
#घोषणा   GEN9_CAGF_SHIFT			23
#घोषणा   GEN6_CAGF_MASK			(0x7f << GEN6_CAGF_SHIFT)
#घोषणा   HSW_CAGF_MASK				(0x7f << HSW_CAGF_SHIFT)
#घोषणा   GEN9_CAGF_MASK			(0x1ff << GEN9_CAGF_SHIFT)
#घोषणा GEN6_RP_CONTROL				_MMIO(0xA024)
#घोषणा   GEN6_RP_MEDIA_TURBO			(1 << 11)
#घोषणा   GEN6_RP_MEDIA_MODE_MASK		(3 << 9)
#घोषणा   GEN6_RP_MEDIA_HW_TURBO_MODE		(3 << 9)
#घोषणा   GEN6_RP_MEDIA_HW_NORMAL_MODE		(2 << 9)
#घोषणा   GEN6_RP_MEDIA_HW_MODE			(1 << 9)
#घोषणा   GEN6_RP_MEDIA_SW_MODE			(0 << 9)
#घोषणा   GEN6_RP_MEDIA_IS_GFX			(1 << 8)
#घोषणा   GEN6_RP_ENABLE			(1 << 7)
#घोषणा   GEN6_RP_UP_IDLE_MIN			(0x1 << 3)
#घोषणा   GEN6_RP_UP_BUSY_AVG			(0x2 << 3)
#घोषणा   GEN6_RP_UP_BUSY_CONT			(0x4 << 3)
#घोषणा   GEN6_RP_DOWN_IDLE_AVG			(0x2 << 0)
#घोषणा   GEN6_RP_DOWN_IDLE_CONT		(0x1 << 0)
#घोषणा GEN6_RP_UP_THRESHOLD			_MMIO(0xA02C)
#घोषणा GEN6_RP_DOWN_THRESHOLD			_MMIO(0xA030)
#घोषणा GEN6_RP_CUR_UP_EI			_MMIO(0xA050)
#घोषणा   GEN6_RP_EI_MASK			0xffffff
#घोषणा   GEN6_CURICONT_MASK			GEN6_RP_EI_MASK
#घोषणा GEN6_RP_CUR_UP				_MMIO(0xA054)
#घोषणा   GEN6_CURBSYTAVG_MASK			GEN6_RP_EI_MASK
#घोषणा GEN6_RP_PREV_UP				_MMIO(0xA058)
#घोषणा GEN6_RP_CUR_DOWN_EI			_MMIO(0xA05C)
#घोषणा   GEN6_CURIAVG_MASK			GEN6_RP_EI_MASK
#घोषणा GEN6_RP_CUR_DOWN			_MMIO(0xA060)
#घोषणा GEN6_RP_PREV_DOWN			_MMIO(0xA064)
#घोषणा GEN6_RP_UP_EI				_MMIO(0xA068)
#घोषणा GEN6_RP_DOWN_EI				_MMIO(0xA06C)
#घोषणा GEN6_RP_IDLE_HYSTERSIS			_MMIO(0xA070)
#घोषणा GEN6_RPDEUHWTC				_MMIO(0xA080)
#घोषणा GEN6_RPDEUC				_MMIO(0xA084)
#घोषणा GEN6_RPDEUCSW				_MMIO(0xA088)
#घोषणा GEN6_RC_STATE				_MMIO(0xA094)
#घोषणा   RC_SW_TARGET_STATE_SHIFT		16
#घोषणा   RC_SW_TARGET_STATE_MASK		(7 << RC_SW_TARGET_STATE_SHIFT)
#घोषणा GEN6_RC1_WAKE_RATE_LIMIT		_MMIO(0xA098)
#घोषणा GEN6_RC6_WAKE_RATE_LIMIT		_MMIO(0xA09C)
#घोषणा GEN6_RC6pp_WAKE_RATE_LIMIT		_MMIO(0xA0A0)
#घोषणा GEN10_MEDIA_WAKE_RATE_LIMIT		_MMIO(0xA0A0)
#घोषणा GEN6_RC_EVALUATION_INTERVAL		_MMIO(0xA0A8)
#घोषणा GEN6_RC_IDLE_HYSTERSIS			_MMIO(0xA0AC)
#घोषणा GEN6_RC_SLEEP				_MMIO(0xA0B0)
#घोषणा GEN6_RCUBMABDTMR			_MMIO(0xA0B0)
#घोषणा GEN6_RC1e_THRESHOLD			_MMIO(0xA0B4)
#घोषणा GEN6_RC6_THRESHOLD			_MMIO(0xA0B8)
#घोषणा GEN6_RC6p_THRESHOLD			_MMIO(0xA0BC)
#घोषणा VLV_RCEDATA				_MMIO(0xA0BC)
#घोषणा GEN6_RC6pp_THRESHOLD			_MMIO(0xA0C0)
#घोषणा GEN6_PMINTRMSK				_MMIO(0xA168)
#घोषणा   GEN8_PMINTR_DISABLE_REसूचीECT_TO_GUC	(1 << 31)
#घोषणा   ARAT_EXPIRED_INTRMSK			(1 << 9)
#घोषणा GEN8_MISC_CTRL0				_MMIO(0xA180)
#घोषणा VLV_PWRDWNUPCTL				_MMIO(0xA294)
#घोषणा GEN9_MEDIA_PG_IDLE_HYSTERESIS		_MMIO(0xA0C4)
#घोषणा GEN9_RENDER_PG_IDLE_HYSTERESIS		_MMIO(0xA0C8)
#घोषणा GEN9_PG_ENABLE				_MMIO(0xA210)
#घोषणा   GEN9_RENDER_PG_ENABLE			REG_BIT(0)
#घोषणा   GEN9_MEDIA_PG_ENABLE			REG_BIT(1)
#घोषणा   GEN11_MEDIA_SAMPLER_PG_ENABLE		REG_BIT(2)
#घोषणा   VDN_HCP_POWERGATE_ENABLE(n)		REG_BIT(3 + 2 * (n))
#घोषणा   VDN_MFX_POWERGATE_ENABLE(n)		REG_BIT(4 + 2 * (n))
#घोषणा GEN8_PUSHBUS_CONTROL			_MMIO(0xA248)
#घोषणा GEN8_PUSHBUS_ENABLE			_MMIO(0xA250)
#घोषणा GEN8_PUSHBUS_SHIFT			_MMIO(0xA25C)

#घोषणा VLV_CHICKEN_3				_MMIO(VLV_DISPLAY_BASE + 0x7040C)
#घोषणा  PIXEL_OVERLAP_CNT_MASK			(3 << 30)
#घोषणा  PIXEL_OVERLAP_CNT_SHIFT		30

#घोषणा GEN6_PMISR				_MMIO(0x44020)
#घोषणा GEN6_PMIMR				_MMIO(0x44024) /* rps_lock */
#घोषणा GEN6_PMIIR				_MMIO(0x44028)
#घोषणा GEN6_PMIER				_MMIO(0x4402C)
#घोषणा  GEN6_PM_MBOX_EVENT			(1 << 25)
#घोषणा  GEN6_PM_THERMAL_EVENT			(1 << 24)

/*
 * For Gen11 these are in the upper word of the GPM_WGBOXPERF
 * रेजिस्टरs. Shअगरting is handled on accessing the imr and ier.
 */
#घोषणा  GEN6_PM_RP_DOWN_TIMEOUT		(1 << 6)
#घोषणा  GEN6_PM_RP_UP_THRESHOLD		(1 << 5)
#घोषणा  GEN6_PM_RP_DOWN_THRESHOLD		(1 << 4)
#घोषणा  GEN6_PM_RP_UP_EI_EXPIRED		(1 << 2)
#घोषणा  GEN6_PM_RP_DOWN_EI_EXPIRED		(1 << 1)
#घोषणा  GEN6_PM_RPS_EVENTS			(GEN6_PM_RP_UP_EI_EXPIRED   | \
						 GEN6_PM_RP_UP_THRESHOLD    | \
						 GEN6_PM_RP_DOWN_EI_EXPIRED | \
						 GEN6_PM_RP_DOWN_THRESHOLD  | \
						 GEN6_PM_RP_DOWN_TIMEOUT)

#घोषणा GEN7_GT_SCRATCH(i)			_MMIO(0x4F100 + (i) * 4)
#घोषणा GEN7_GT_SCRATCH_REG_NUM			8

#घोषणा VLV_GTLC_SURVIVABILITY_REG              _MMIO(0x130098)
#घोषणा VLV_GFX_CLK_STATUS_BIT			(1 << 3)
#घोषणा VLV_GFX_CLK_FORCE_ON_BIT		(1 << 2)

#घोषणा GEN6_GT_GFX_RC6_LOCKED			_MMIO(0x138104)
#घोषणा VLV_COUNTER_CONTROL			_MMIO(0x138104)
#घोषणा   VLV_COUNT_RANGE_HIGH			(1 << 15)
#घोषणा   VLV_MEDIA_RC0_COUNT_EN		(1 << 5)
#घोषणा   VLV_RENDER_RC0_COUNT_EN		(1 << 4)
#घोषणा   VLV_MEDIA_RC6_COUNT_EN		(1 << 1)
#घोषणा   VLV_RENDER_RC6_COUNT_EN		(1 << 0)
#घोषणा GEN6_GT_GFX_RC6				_MMIO(0x138108)
#घोषणा VLV_GT_RENDER_RC6			_MMIO(0x138108)
#घोषणा VLV_GT_MEDIA_RC6			_MMIO(0x13810C)

#घोषणा GEN6_GT_GFX_RC6p			_MMIO(0x13810C)
#घोषणा GEN6_GT_GFX_RC6pp			_MMIO(0x138110)
#घोषणा VLV_RENDER_C0_COUNT			_MMIO(0x138118)
#घोषणा VLV_MEDIA_C0_COUNT			_MMIO(0x13811C)

#घोषणा GEN6_PCODE_MAILBOX			_MMIO(0x138124)
#घोषणा   GEN6_PCODE_READY			(1 << 31)
#घोषणा   GEN6_PCODE_ERROR_MASK			0xFF
#घोषणा     GEN6_PCODE_SUCCESS			0x0
#घोषणा     GEN6_PCODE_ILLEGAL_CMD		0x1
#घोषणा     GEN6_PCODE_MIN_FREQ_TABLE_GT_RATIO_OUT_OF_RANGE 0x2
#घोषणा     GEN6_PCODE_TIMEOUT			0x3
#घोषणा     GEN6_PCODE_UNIMPLEMENTED_CMD	0xFF
#घोषणा     GEN7_PCODE_TIMEOUT			0x2
#घोषणा     GEN7_PCODE_ILLEGAL_DATA		0x3
#घोषणा     GEN11_PCODE_ILLEGAL_SUBCOMMAND	0x4
#घोषणा     GEN11_PCODE_LOCKED			0x6
#घोषणा     GEN11_PCODE_REJECTED		0x11
#घोषणा     GEN7_PCODE_MIN_FREQ_TABLE_GT_RATIO_OUT_OF_RANGE 0x10
#घोषणा   GEN6_PCODE_WRITE_RC6VIDS		0x4
#घोषणा   GEN6_PCODE_READ_RC6VIDS		0x5
#घोषणा     GEN6_ENCODE_RC6_VID(mv)		(((mv) - 245) / 5)
#घोषणा     GEN6_DECODE_RC6_VID(vids)		(((vids) * 5) + 245)
#घोषणा   BDW_PCODE_DISPLAY_FREQ_CHANGE_REQ	0x18
#घोषणा   GEN9_PCODE_READ_MEM_LATENCY		0x6
#घोषणा     GEN9_MEM_LATENCY_LEVEL_MASK		0xFF
#घोषणा     GEN9_MEM_LATENCY_LEVEL_1_5_SHIFT	8
#घोषणा     GEN9_MEM_LATENCY_LEVEL_2_6_SHIFT	16
#घोषणा     GEN9_MEM_LATENCY_LEVEL_3_7_SHIFT	24
#घोषणा   SKL_PCODE_LOAD_HDCP_KEYS		0x5
#घोषणा   SKL_PCODE_CDCLK_CONTROL		0x7
#घोषणा     SKL_CDCLK_PREPARE_FOR_CHANGE	0x3
#घोषणा     SKL_CDCLK_READY_FOR_CHANGE		0x1
#घोषणा   GEN6_PCODE_WRITE_MIN_FREQ_TABLE	0x8
#घोषणा   GEN6_PCODE_READ_MIN_FREQ_TABLE	0x9
#घोषणा   GEN6_READ_OC_PARAMS			0xc
#घोषणा   ICL_PCODE_MEM_SUBSYSYSTEM_INFO	0xd
#घोषणा     ICL_PCODE_MEM_SS_READ_GLOBAL_INFO	(0x0 << 8)
#घोषणा     ICL_PCODE_MEM_SS_READ_QGV_POINT_INFO(poपूर्णांक)	(((poपूर्णांक) << 16) | (0x1 << 8))
#घोषणा   ICL_PCODE_SAGV_DE_MEM_SS_CONFIG	0xe
#घोषणा     ICL_PCODE_POINTS_RESTRICTED		0x0
#घोषणा     ICL_PCODE_POINTS_RESTRICTED_MASK	0x1
#घोषणा   GEN6_PCODE_READ_D_COMP		0x10
#घोषणा   GEN6_PCODE_WRITE_D_COMP		0x11
#घोषणा   ICL_PCODE_EXIT_TCCOLD			0x12
#घोषणा   HSW_PCODE_DE_WRITE_FREQ_REQ		0x17
#घोषणा   DISPLAY_IPS_CONTROL			0x19
#घोषणा   TGL_PCODE_TCCOLD			0x26
#घोषणा     TGL_PCODE_EXIT_TCCOLD_DATA_L_EXIT_FAILED	REG_BIT(0)
#घोषणा     TGL_PCODE_EXIT_TCCOLD_DATA_L_BLOCK_REQ	0
#घोषणा     TGL_PCODE_EXIT_TCCOLD_DATA_L_UNBLOCK_REQ	REG_BIT(0)
            /* See also IPS_CTL */
#घोषणा     IPS_PCODE_CONTROL			(1 << 30)
#घोषणा   HSW_PCODE_DYNAMIC_DUTY_CYCLE_CONTROL	0x1A
#घोषणा   GEN9_PCODE_SAGV_CONTROL		0x21
#घोषणा     GEN9_SAGV_DISABLE			0x0
#घोषणा     GEN9_SAGV_IS_DISABLED		0x1
#घोषणा     GEN9_SAGV_ENABLE			0x3
#घोषणा   DG1_PCODE_STATUS			0x7E
#घोषणा     DG1_UNCORE_GET_INIT_STATUS		0x0
#घोषणा     DG1_UNCORE_INIT_STATUS_COMPLETE	0x1
#घोषणा GEN12_PCODE_READ_SAGV_BLOCK_TIME_US	0x23
#घोषणा GEN6_PCODE_DATA				_MMIO(0x138128)
#घोषणा   GEN6_PCODE_FREQ_IA_RATIO_SHIFT	8
#घोषणा   GEN6_PCODE_FREQ_RING_RATIO_SHIFT	16
#घोषणा GEN6_PCODE_DATA1			_MMIO(0x13812C)

#घोषणा GEN6_GT_CORE_STATUS		_MMIO(0x138060)
#घोषणा   GEN6_CORE_CPD_STATE_MASK	(7 << 4)
#घोषणा   GEN6_RCn_MASK			7
#घोषणा   GEN6_RC0			0
#घोषणा   GEN6_RC3			2
#घोषणा   GEN6_RC6			3
#घोषणा   GEN6_RC7			4

#घोषणा GEN8_GT_SLICE_INFO		_MMIO(0x138064)
#घोषणा   GEN8_LSLICESTAT_MASK		0x7

#घोषणा CHV_POWER_SS0_SIG1		_MMIO(0xa720)
#घोषणा CHV_POWER_SS1_SIG1		_MMIO(0xa728)
#घोषणा   CHV_SS_PG_ENABLE		(1 << 1)
#घोषणा   CHV_EU08_PG_ENABLE		(1 << 9)
#घोषणा   CHV_EU19_PG_ENABLE		(1 << 17)
#घोषणा   CHV_EU210_PG_ENABLE		(1 << 25)

#घोषणा CHV_POWER_SS0_SIG2		_MMIO(0xa724)
#घोषणा CHV_POWER_SS1_SIG2		_MMIO(0xa72c)
#घोषणा   CHV_EU311_PG_ENABLE		(1 << 1)

#घोषणा GEN9_SLICE_PGCTL_ACK(slice)	_MMIO(0x804c + (slice) * 0x4)
#घोषणा GEN10_SLICE_PGCTL_ACK(slice)	_MMIO(0x804c + ((slice) / 3) * 0x34 + \
					      ((slice) % 3) * 0x4)
#घोषणा   GEN9_PGCTL_SLICE_ACK		(1 << 0)
#घोषणा   GEN9_PGCTL_SS_ACK(subslice)	(1 << (2 + (subslice) * 2))
#घोषणा   GEN10_PGCTL_VALID_SS_MASK(slice) ((slice) == 0 ? 0x7F : 0x1F)

#घोषणा GEN9_SS01_EU_PGCTL_ACK(slice)	_MMIO(0x805c + (slice) * 0x8)
#घोषणा GEN10_SS01_EU_PGCTL_ACK(slice)	_MMIO(0x805c + ((slice) / 3) * 0x30 + \
					      ((slice) % 3) * 0x8)
#घोषणा GEN9_SS23_EU_PGCTL_ACK(slice)	_MMIO(0x8060 + (slice) * 0x8)
#घोषणा GEN10_SS23_EU_PGCTL_ACK(slice)	_MMIO(0x8060 + ((slice) / 3) * 0x30 + \
					      ((slice) % 3) * 0x8)
#घोषणा   GEN9_PGCTL_SSA_EU08_ACK	(1 << 0)
#घोषणा   GEN9_PGCTL_SSA_EU19_ACK	(1 << 2)
#घोषणा   GEN9_PGCTL_SSA_EU210_ACK	(1 << 4)
#घोषणा   GEN9_PGCTL_SSA_EU311_ACK	(1 << 6)
#घोषणा   GEN9_PGCTL_SSB_EU08_ACK	(1 << 8)
#घोषणा   GEN9_PGCTL_SSB_EU19_ACK	(1 << 10)
#घोषणा   GEN9_PGCTL_SSB_EU210_ACK	(1 << 12)
#घोषणा   GEN9_PGCTL_SSB_EU311_ACK	(1 << 14)

#घोषणा GEN7_MISCCPCTL				_MMIO(0x9424)
#घोषणा   GEN7_DOP_CLOCK_GATE_ENABLE		(1 << 0)
#घोषणा   GEN8_DOP_CLOCK_GATE_CFCLK_ENABLE	(1 << 2)
#घोषणा   GEN8_DOP_CLOCK_GATE_GUC_ENABLE	(1 << 4)
#घोषणा   GEN8_DOP_CLOCK_GATE_MEDIA_ENABLE     (1 << 6)

#घोषणा GEN8_GARBCNTL				_MMIO(0xB004)
#घोषणा   GEN9_GAPS_TSV_CREDIT_DISABLE		(1 << 7)
#घोषणा   GEN11_ARBITRATION_PRIO_ORDER_MASK	(0x3f << 22)
#घोषणा   GEN11_HASH_CTRL_EXCL_MASK		(0x7f << 0)
#घोषणा   GEN11_HASH_CTRL_EXCL_BIT0		(1 << 0)

#घोषणा GEN11_GLBLINVL				_MMIO(0xB404)
#घोषणा   GEN11_BANK_HASH_ADDR_EXCL_MASK	(0x7f << 5)
#घोषणा   GEN11_BANK_HASH_ADDR_EXCL_BIT0	(1 << 5)

#घोषणा GEN10_DFR_RATIO_EN_AND_CHICKEN	_MMIO(0x9550)
#घोषणा   DFR_DISABLE			(1 << 9)

#घोषणा GEN11_GACB_PERF_CTRL			_MMIO(0x4B80)
#घोषणा   GEN11_HASH_CTRL_MASK			(0x3 << 12 | 0xf << 0)
#घोषणा   GEN11_HASH_CTRL_BIT0			(1 << 0)
#घोषणा   GEN11_HASH_CTRL_BIT4			(1 << 12)

#घोषणा GEN11_LSN_UNSLCVC				_MMIO(0xB43C)
#घोषणा   GEN11_LSN_UNSLCVC_GAFS_HALF_CL2_MAXALLOC	(1 << 9)
#घोषणा   GEN11_LSN_UNSLCVC_GAFS_HALF_SF_MAXALLOC	(1 << 7)

#घोषणा GEN10_SAMPLER_MODE		_MMIO(0xE18C)
#घोषणा   ENABLE_SMALLPL			REG_BIT(15)
#घोषणा   GEN11_SAMPLER_ENABLE_HEADLESS_MSG	REG_BIT(5)

/* IVYBRIDGE DPF */
#घोषणा GEN7_L3CDERRST1(slice)		_MMIO(0xB008 + (slice) * 0x200) /* L3CD Error Status 1 */
#घोषणा   GEN7_L3CDERRST1_ROW_MASK	(0x7ff << 14)
#घोषणा   GEN7_PARITY_ERROR_VALID	(1 << 13)
#घोषणा   GEN7_L3CDERRST1_BANK_MASK	(3 << 11)
#घोषणा   GEN7_L3CDERRST1_SUBBANK_MASK	(7 << 8)
#घोषणा GEN7_PARITY_ERROR_ROW(reg) \
		(((reg) & GEN7_L3CDERRST1_ROW_MASK) >> 14)
#घोषणा GEN7_PARITY_ERROR_BANK(reg) \
		(((reg) & GEN7_L3CDERRST1_BANK_MASK) >> 11)
#घोषणा GEN7_PARITY_ERROR_SUBBANK(reg) \
		(((reg) & GEN7_L3CDERRST1_SUBBANK_MASK) >> 8)
#घोषणा   GEN7_L3CDERRST1_ENABLE	(1 << 7)

#घोषणा GEN7_L3LOG(slice, i)		_MMIO(0xB070 + (slice) * 0x200 + (i) * 4)
#घोषणा GEN7_L3LOG_SIZE			0x80

#घोषणा GEN7_HALF_SLICE_CHICKEN1	_MMIO(0xe100) /* IVB GT1 + VLV */
#घोषणा GEN7_HALF_SLICE_CHICKEN1_GT2	_MMIO(0xf100)
#घोषणा   GEN7_MAX_PS_THREAD_DEP		(8 << 12)
#घोषणा   GEN7_SINGLE_SUBSCAN_DISPATCH_ENABLE	(1 << 10)
#घोषणा   GEN7_SBE_SS_CACHE_DISPATCH_PORT_SHARING_DISABLE	(1 << 4)
#घोषणा   GEN7_PSD_SINGLE_PORT_DISPATCH_ENABLE	(1 << 3)

#घोषणा GEN9_HALF_SLICE_CHICKEN5	_MMIO(0xe188)
#घोषणा   GEN9_DG_MIRROR_FIX_ENABLE	(1 << 5)
#घोषणा   GEN9_CCS_TLB_PREFETCH_ENABLE	(1 << 3)

#घोषणा GEN8_ROW_CHICKEN		_MMIO(0xe4f0)
#घोषणा   FLOW_CONTROL_ENABLE		(1 << 15)
#घोषणा   PARTIAL_INSTRUCTION_SHOOTDOWN_DISABLE	(1 << 8)
#घोषणा   STALL_DOP_GATING_DISABLE		(1 << 5)
#घोषणा   THROTTLE_12_5				(7 << 2)
#घोषणा   DISABLE_EARLY_EOT			(1 << 1)

#घोषणा GEN7_ROW_CHICKEN2			_MMIO(0xe4f4)
#घोषणा   GEN12_DISABLE_EARLY_READ		REG_BIT(14)
#घोषणा   GEN12_PUSH_CONST_DEREF_HOLD_DIS	REG_BIT(8)

#घोषणा GEN7_ROW_CHICKEN2_GT2		_MMIO(0xf4f4)
#घोषणा   DOP_CLOCK_GATING_DISABLE	(1 << 0)
#घोषणा   PUSH_CONSTANT_DEREF_DISABLE	(1 << 8)
#घोषणा   GEN11_TDL_CLOCK_GATING_FIX_DISABLE	(1 << 1)

#घोषणा GEN9_ROW_CHICKEN4		_MMIO(0xe48c)
#घोषणा   GEN12_DISABLE_TDL_PUSH	REG_BIT(9)
#घोषणा   GEN11_DIS_PICK_2ND_EU		REG_BIT(7)

#घोषणा HSW_ROW_CHICKEN3		_MMIO(0xe49c)
#घोषणा  HSW_ROW_CHICKEN3_L3_GLOBAL_ATOMICS_DISABLE    (1 << 6)

#घोषणा HALF_SLICE_CHICKEN2		_MMIO(0xe180)
#घोषणा   GEN8_ST_PO_DISABLE		(1 << 13)

#घोषणा HALF_SLICE_CHICKEN3		_MMIO(0xe184)
#घोषणा   HSW_SAMPLE_C_PERFORMANCE	(1 << 9)
#घोषणा   GEN8_CENTROID_PIXEL_OPT_DIS	(1 << 8)
#घोषणा   GEN9_DISABLE_OCL_OOB_SUPPRESS_LOGIC	(1 << 5)
#घोषणा   CNL_FAST_ANISO_L1_BANKING_FIX	(1 << 4)
#घोषणा   GEN8_SAMPLER_POWER_BYPASS_DIS	(1 << 1)

#घोषणा GEN9_HALF_SLICE_CHICKEN7	_MMIO(0xe194)
#घोषणा   GEN9_SAMPLER_HASH_COMPRESSED_READ_ADDR	(1 << 8)
#घोषणा   GEN9_ENABLE_YV12_BUGFIX	(1 << 4)
#घोषणा   GEN9_ENABLE_GPGPU_PREEMPTION	(1 << 2)

/* Audio */
#घोषणा G4X_AUD_VID_DID			_MMIO(DISPLAY_MMIO_BASE(dev_priv) + 0x62020)
#घोषणा   INTEL_AUDIO_DEVCL		0x808629FB
#घोषणा   INTEL_AUDIO_DEVBLC		0x80862801
#घोषणा   INTEL_AUDIO_DEVCTG		0x80862802

#घोषणा G4X_AUD_CNTL_ST			_MMIO(0x620B4)
#घोषणा   G4X_ELDV_DEVCL_DEVBLC		(1 << 13)
#घोषणा   G4X_ELDV_DEVCTG		(1 << 14)
#घोषणा   G4X_ELD_ADDR_MASK		(0xf << 5)
#घोषणा   G4X_ELD_ACK			(1 << 4)
#घोषणा G4X_HDMIW_HDMIEDID		_MMIO(0x6210C)

#घोषणा _IBX_HDMIW_HDMIEDID_A		0xE2050
#घोषणा _IBX_HDMIW_HDMIEDID_B		0xE2150
#घोषणा IBX_HDMIW_HDMIEDID(pipe)	_MMIO_PIPE(pipe, _IBX_HDMIW_HDMIEDID_A, \
						  _IBX_HDMIW_HDMIEDID_B)
#घोषणा _IBX_AUD_CNTL_ST_A		0xE20B4
#घोषणा _IBX_AUD_CNTL_ST_B		0xE21B4
#घोषणा IBX_AUD_CNTL_ST(pipe)		_MMIO_PIPE(pipe, _IBX_AUD_CNTL_ST_A, \
						  _IBX_AUD_CNTL_ST_B)
#घोषणा   IBX_ELD_BUFFER_SIZE_MASK	(0x1f << 10)
#घोषणा   IBX_ELD_ADDRESS_MASK		(0x1f << 5)
#घोषणा   IBX_ELD_ACK			(1 << 4)
#घोषणा IBX_AUD_CNTL_ST2		_MMIO(0xE20C0)
#घोषणा   IBX_CP_READY(port)		((1 << 1) << (((port) - 1) * 4))
#घोषणा   IBX_ELD_VALID(port)		((1 << 0) << (((port) - 1) * 4))

#घोषणा _CPT_HDMIW_HDMIEDID_A		0xE5050
#घोषणा _CPT_HDMIW_HDMIEDID_B		0xE5150
#घोषणा CPT_HDMIW_HDMIEDID(pipe)	_MMIO_PIPE(pipe, _CPT_HDMIW_HDMIEDID_A, _CPT_HDMIW_HDMIEDID_B)
#घोषणा _CPT_AUD_CNTL_ST_A		0xE50B4
#घोषणा _CPT_AUD_CNTL_ST_B		0xE51B4
#घोषणा CPT_AUD_CNTL_ST(pipe)		_MMIO_PIPE(pipe, _CPT_AUD_CNTL_ST_A, _CPT_AUD_CNTL_ST_B)
#घोषणा CPT_AUD_CNTRL_ST2		_MMIO(0xE50C0)

#घोषणा _VLV_HDMIW_HDMIEDID_A		(VLV_DISPLAY_BASE + 0x62050)
#घोषणा _VLV_HDMIW_HDMIEDID_B		(VLV_DISPLAY_BASE + 0x62150)
#घोषणा VLV_HDMIW_HDMIEDID(pipe)	_MMIO_PIPE(pipe, _VLV_HDMIW_HDMIEDID_A, _VLV_HDMIW_HDMIEDID_B)
#घोषणा _VLV_AUD_CNTL_ST_A		(VLV_DISPLAY_BASE + 0x620B4)
#घोषणा _VLV_AUD_CNTL_ST_B		(VLV_DISPLAY_BASE + 0x621B4)
#घोषणा VLV_AUD_CNTL_ST(pipe)		_MMIO_PIPE(pipe, _VLV_AUD_CNTL_ST_A, _VLV_AUD_CNTL_ST_B)
#घोषणा VLV_AUD_CNTL_ST2		_MMIO(VLV_DISPLAY_BASE + 0x620C0)

/* These are the 4 32-bit ग_लिखो offset रेजिस्टरs क्रम each stream
 * output buffer.  It determines the offset from the
 * 3DSTATE_SO_BUFFERs that the next streamed vertex output goes to.
 */
#घोषणा GEN7_SO_WRITE_OFFSET(n)		_MMIO(0x5280 + (n) * 4)

#घोषणा _IBX_AUD_CONFIG_A		0xe2000
#घोषणा _IBX_AUD_CONFIG_B		0xe2100
#घोषणा IBX_AUD_CFG(pipe)		_MMIO_PIPE(pipe, _IBX_AUD_CONFIG_A, _IBX_AUD_CONFIG_B)
#घोषणा _CPT_AUD_CONFIG_A		0xe5000
#घोषणा _CPT_AUD_CONFIG_B		0xe5100
#घोषणा CPT_AUD_CFG(pipe)		_MMIO_PIPE(pipe, _CPT_AUD_CONFIG_A, _CPT_AUD_CONFIG_B)
#घोषणा _VLV_AUD_CONFIG_A		(VLV_DISPLAY_BASE + 0x62000)
#घोषणा _VLV_AUD_CONFIG_B		(VLV_DISPLAY_BASE + 0x62100)
#घोषणा VLV_AUD_CFG(pipe)		_MMIO_PIPE(pipe, _VLV_AUD_CONFIG_A, _VLV_AUD_CONFIG_B)

#घोषणा   AUD_CONFIG_N_VALUE_INDEX		(1 << 29)
#घोषणा   AUD_CONFIG_N_PROG_ENABLE		(1 << 28)
#घोषणा   AUD_CONFIG_UPPER_N_SHIFT		20
#घोषणा   AUD_CONFIG_UPPER_N_MASK		(0xff << 20)
#घोषणा   AUD_CONFIG_LOWER_N_SHIFT		4
#घोषणा   AUD_CONFIG_LOWER_N_MASK		(0xfff << 4)
#घोषणा   AUD_CONFIG_N_MASK			(AUD_CONFIG_UPPER_N_MASK | AUD_CONFIG_LOWER_N_MASK)
#घोषणा   AUD_CONFIG_N(n) \
	(((((n) >> 12) & 0xff) << AUD_CONFIG_UPPER_N_SHIFT) |	\
	 (((n) & 0xfff) << AUD_CONFIG_LOWER_N_SHIFT))
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_SHIFT	16
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_MASK	(0xf << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_25175	(0 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_25200	(1 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_27000	(2 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_27027	(3 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_54000	(4 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_54054	(5 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_74176	(6 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_74250	(7 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_148352	(8 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_148500	(9 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_296703	(10 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_297000	(11 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_593407	(12 << 16)
#घोषणा   AUD_CONFIG_PIXEL_CLOCK_HDMI_594000	(13 << 16)
#घोषणा   AUD_CONFIG_DISABLE_NCTS		(1 << 3)

/* HSW Audio */
#घोषणा _HSW_AUD_CONFIG_A		0x65000
#घोषणा _HSW_AUD_CONFIG_B		0x65100
#घोषणा HSW_AUD_CFG(trans)		_MMIO_TRANS(trans, _HSW_AUD_CONFIG_A, _HSW_AUD_CONFIG_B)

#घोषणा _HSW_AUD_MISC_CTRL_A		0x65010
#घोषणा _HSW_AUD_MISC_CTRL_B		0x65110
#घोषणा HSW_AUD_MISC_CTRL(trans)	_MMIO_TRANS(trans, _HSW_AUD_MISC_CTRL_A, _HSW_AUD_MISC_CTRL_B)

#घोषणा _HSW_AUD_M_CTS_ENABLE_A		0x65028
#घोषणा _HSW_AUD_M_CTS_ENABLE_B		0x65128
#घोषणा HSW_AUD_M_CTS_ENABLE(trans)	_MMIO_TRANS(trans, _HSW_AUD_M_CTS_ENABLE_A, _HSW_AUD_M_CTS_ENABLE_B)
#घोषणा   AUD_M_CTS_M_VALUE_INDEX	(1 << 21)
#घोषणा   AUD_M_CTS_M_PROG_ENABLE	(1 << 20)
#घोषणा   AUD_CONFIG_M_MASK		0xfffff

#घोषणा _HSW_AUD_DIP_ELD_CTRL_ST_A	0x650b4
#घोषणा _HSW_AUD_DIP_ELD_CTRL_ST_B	0x651b4
#घोषणा HSW_AUD_DIP_ELD_CTRL(trans)	_MMIO_TRANS(trans, _HSW_AUD_DIP_ELD_CTRL_ST_A, _HSW_AUD_DIP_ELD_CTRL_ST_B)

/* Audio Digital Converter */
#घोषणा _HSW_AUD_DIG_CNVT_1		0x65080
#घोषणा _HSW_AUD_DIG_CNVT_2		0x65180
#घोषणा AUD_DIG_CNVT(trans)		_MMIO_TRANS(trans, _HSW_AUD_DIG_CNVT_1, _HSW_AUD_DIG_CNVT_2)
#घोषणा DIP_PORT_SEL_MASK		0x3

#घोषणा _HSW_AUD_EDID_DATA_A		0x65050
#घोषणा _HSW_AUD_EDID_DATA_B		0x65150
#घोषणा HSW_AUD_EDID_DATA(trans)	_MMIO_TRANS(trans, _HSW_AUD_EDID_DATA_A, _HSW_AUD_EDID_DATA_B)

#घोषणा HSW_AUD_PIPE_CONV_CFG		_MMIO(0x6507c)
#घोषणा HSW_AUD_PIN_ELD_CP_VLD		_MMIO(0x650c0)
#घोषणा   AUDIO_INACTIVE(trans)		((1 << 3) << ((trans) * 4))
#घोषणा   AUDIO_OUTPUT_ENABLE(trans)	((1 << 2) << ((trans) * 4))
#घोषणा   AUDIO_CP_READY(trans)		((1 << 1) << ((trans) * 4))
#घोषणा   AUDIO_ELD_VALID(trans)	((1 << 0) << ((trans) * 4))

#घोषणा HSW_AUD_CHICKENBIT			_MMIO(0x65f10)
#घोषणा   SKL_AUD_CODEC_WAKE_SIGNAL		(1 << 15)

#घोषणा AUD_FREQ_CNTRL			_MMIO(0x65900)
#घोषणा AUD_PIN_BUF_CTL		_MMIO(0x48414)
#घोषणा   AUD_PIN_BUF_ENABLE		REG_BIT(31)

/* Display Audio Config Reg */
#घोषणा AUD_CONFIG_BE			_MMIO(0x65ef0)
#घोषणा HBLANK_EARLY_ENABLE_ICL(pipe)		(0x1 << (20 - (pipe)))
#घोषणा HBLANK_EARLY_ENABLE_TGL(pipe)		(0x1 << (24 + (pipe)))
#घोषणा HBLANK_START_COUNT_MASK(pipe)		(0x7 << (3 + ((pipe) * 6)))
#घोषणा HBLANK_START_COUNT(pipe, val)		(((val) & 0x7) << (3 + ((pipe)) * 6))
#घोषणा NUMBER_SAMPLES_PER_LINE_MASK(pipe)	(0x3 << ((pipe) * 6))
#घोषणा NUMBER_SAMPLES_PER_LINE(pipe, val)	(((val) & 0x3) << ((pipe) * 6))

#घोषणा HBLANK_START_COUNT_8	0
#घोषणा HBLANK_START_COUNT_16	1
#घोषणा HBLANK_START_COUNT_32	2
#घोषणा HBLANK_START_COUNT_64	3
#घोषणा HBLANK_START_COUNT_96	4
#घोषणा HBLANK_START_COUNT_128	5

/*
 * HSW - ICL घातer wells
 *
 * Platक्रमms have up to 3 घातer well control रेजिस्टर sets, each set
 * controlling up to 16 घातer wells via a request/status HW flag tuple:
 * - मुख्य (HSW_PWR_WELL_CTL[1-4])
 * - AUX  (ICL_PWR_WELL_CTL_AUX[1-4])
 * - DDI  (ICL_PWR_WELL_CTL_DDI[1-4])
 * Each control रेजिस्टर set consists of up to 4 रेजिस्टरs used by dअगरferent
 * sources that can request a घातer well to be enabled:
 * - BIOS   (HSW_PWR_WELL_CTL1/ICL_PWR_WELL_CTL_AUX1/ICL_PWR_WELL_CTL_DDI1)
 * - DRIVER (HSW_PWR_WELL_CTL2/ICL_PWR_WELL_CTL_AUX2/ICL_PWR_WELL_CTL_DDI2)
 * - KVMR   (HSW_PWR_WELL_CTL3)   (only in the मुख्य रेजिस्टर set)
 * - DEBUG  (HSW_PWR_WELL_CTL4/ICL_PWR_WELL_CTL_AUX4/ICL_PWR_WELL_CTL_DDI4)
 */
#घोषणा HSW_PWR_WELL_CTL1			_MMIO(0x45400)
#घोषणा HSW_PWR_WELL_CTL2			_MMIO(0x45404)
#घोषणा HSW_PWR_WELL_CTL3			_MMIO(0x45408)
#घोषणा HSW_PWR_WELL_CTL4			_MMIO(0x4540C)
#घोषणा   HSW_PWR_WELL_CTL_REQ(pw_idx)		(0x2 << ((pw_idx) * 2))
#घोषणा   HSW_PWR_WELL_CTL_STATE(pw_idx)	(0x1 << ((pw_idx) * 2))

/* HSW/BDW घातer well */
#घोषणा   HSW_PW_CTL_IDX_GLOBAL			15

/* SKL/BXT/GLK/CNL घातer wells */
#घोषणा   SKL_PW_CTL_IDX_PW_2			15
#घोषणा   SKL_PW_CTL_IDX_PW_1			14
#घोषणा   CNL_PW_CTL_IDX_AUX_F			12
#घोषणा   CNL_PW_CTL_IDX_AUX_D			11
#घोषणा   GLK_PW_CTL_IDX_AUX_C			10
#घोषणा   GLK_PW_CTL_IDX_AUX_B			9
#घोषणा   GLK_PW_CTL_IDX_AUX_A			8
#घोषणा   CNL_PW_CTL_IDX_DDI_F			6
#घोषणा   SKL_PW_CTL_IDX_DDI_D			4
#घोषणा   SKL_PW_CTL_IDX_DDI_C			3
#घोषणा   SKL_PW_CTL_IDX_DDI_B			2
#घोषणा   SKL_PW_CTL_IDX_DDI_A_E		1
#घोषणा   GLK_PW_CTL_IDX_DDI_A			1
#घोषणा   SKL_PW_CTL_IDX_MISC_IO		0

/* ICL/TGL - घातer wells */
#घोषणा   TGL_PW_CTL_IDX_PW_5			4
#घोषणा   ICL_PW_CTL_IDX_PW_4			3
#घोषणा   ICL_PW_CTL_IDX_PW_3			2
#घोषणा   ICL_PW_CTL_IDX_PW_2			1
#घोषणा   ICL_PW_CTL_IDX_PW_1			0

#घोषणा ICL_PWR_WELL_CTL_AUX1			_MMIO(0x45440)
#घोषणा ICL_PWR_WELL_CTL_AUX2			_MMIO(0x45444)
#घोषणा ICL_PWR_WELL_CTL_AUX4			_MMIO(0x4544C)
#घोषणा   TGL_PW_CTL_IDX_AUX_TBT6		14
#घोषणा   TGL_PW_CTL_IDX_AUX_TBT5		13
#घोषणा   TGL_PW_CTL_IDX_AUX_TBT4		12
#घोषणा   ICL_PW_CTL_IDX_AUX_TBT4		11
#घोषणा   TGL_PW_CTL_IDX_AUX_TBT3		11
#घोषणा   ICL_PW_CTL_IDX_AUX_TBT3		10
#घोषणा   TGL_PW_CTL_IDX_AUX_TBT2		10
#घोषणा   ICL_PW_CTL_IDX_AUX_TBT2		9
#घोषणा   TGL_PW_CTL_IDX_AUX_TBT1		9
#घोषणा   ICL_PW_CTL_IDX_AUX_TBT1		8
#घोषणा   TGL_PW_CTL_IDX_AUX_TC6		8
#घोषणा   TGL_PW_CTL_IDX_AUX_TC5		7
#घोषणा   TGL_PW_CTL_IDX_AUX_TC4		6
#घोषणा   ICL_PW_CTL_IDX_AUX_F			5
#घोषणा   TGL_PW_CTL_IDX_AUX_TC3		5
#घोषणा   ICL_PW_CTL_IDX_AUX_E			4
#घोषणा   TGL_PW_CTL_IDX_AUX_TC2		4
#घोषणा   ICL_PW_CTL_IDX_AUX_D			3
#घोषणा   TGL_PW_CTL_IDX_AUX_TC1		3
#घोषणा   ICL_PW_CTL_IDX_AUX_C			2
#घोषणा   ICL_PW_CTL_IDX_AUX_B			1
#घोषणा   ICL_PW_CTL_IDX_AUX_A			0

#घोषणा ICL_PWR_WELL_CTL_DDI1			_MMIO(0x45450)
#घोषणा ICL_PWR_WELL_CTL_DDI2			_MMIO(0x45454)
#घोषणा ICL_PWR_WELL_CTL_DDI4			_MMIO(0x4545C)
#घोषणा   TGL_PW_CTL_IDX_DDI_TC6		8
#घोषणा   TGL_PW_CTL_IDX_DDI_TC5		7
#घोषणा   TGL_PW_CTL_IDX_DDI_TC4		6
#घोषणा   ICL_PW_CTL_IDX_DDI_F			5
#घोषणा   TGL_PW_CTL_IDX_DDI_TC3		5
#घोषणा   ICL_PW_CTL_IDX_DDI_E			4
#घोषणा   TGL_PW_CTL_IDX_DDI_TC2		4
#घोषणा   ICL_PW_CTL_IDX_DDI_D			3
#घोषणा   TGL_PW_CTL_IDX_DDI_TC1		3
#घोषणा   ICL_PW_CTL_IDX_DDI_C			2
#घोषणा   ICL_PW_CTL_IDX_DDI_B			1
#घोषणा   ICL_PW_CTL_IDX_DDI_A			0

/* HSW - घातer well misc debug रेजिस्टरs */
#घोषणा HSW_PWR_WELL_CTL5			_MMIO(0x45410)
#घोषणा   HSW_PWR_WELL_ENABLE_SINGLE_STEP	(1 << 31)
#घोषणा   HSW_PWR_WELL_PWR_GATE_OVERRIDE	(1 << 20)
#घोषणा   HSW_PWR_WELL_FORCE_ON			(1 << 19)
#घोषणा HSW_PWR_WELL_CTL6			_MMIO(0x45414)

/* SKL Fuse Status */
क्रमागत skl_घातer_gate अणु
	SKL_PG0,
	SKL_PG1,
	SKL_PG2,
	ICL_PG3,
	ICL_PG4,
पूर्ण;

#घोषणा SKL_FUSE_STATUS				_MMIO(0x42000)
#घोषणा  SKL_FUSE_DOWNLOAD_STATUS		(1 << 31)
/*
 * PG0 is HW controlled, so करोesn't have a corresponding घातer well control knob
 * SKL_DISP_PW1_IDX..SKL_DISP_PW2_IDX -> PG1..PG2
 */
#घोषणा  SKL_PW_CTL_IDX_TO_PG(pw_idx)		\
	((pw_idx) - SKL_PW_CTL_IDX_PW_1 + SKL_PG1)
/*
 * PG0 is HW controlled, so करोesn't have a corresponding घातer well control knob
 * ICL_DISP_PW1_IDX..ICL_DISP_PW4_IDX -> PG1..PG4
 */
#घोषणा  ICL_PW_CTL_IDX_TO_PG(pw_idx)		\
	((pw_idx) - ICL_PW_CTL_IDX_PW_1 + SKL_PG1)
#घोषणा  SKL_FUSE_PG_DIST_STATUS(pg)		(1 << (27 - (pg)))

#घोषणा _CNL_AUX_REG_IDX(pw_idx)	((pw_idx) - GLK_PW_CTL_IDX_AUX_B)
#घोषणा _CNL_AUX_ANAOVRD1_B		0x162250
#घोषणा _CNL_AUX_ANAOVRD1_C		0x162210
#घोषणा _CNL_AUX_ANAOVRD1_D		0x1622D0
#घोषणा _CNL_AUX_ANAOVRD1_F		0x162A90
#घोषणा CNL_AUX_ANAOVRD1(pw_idx)	_MMIO(_PICK(_CNL_AUX_REG_IDX(pw_idx), \
						    _CNL_AUX_ANAOVRD1_B, \
						    _CNL_AUX_ANAOVRD1_C, \
						    _CNL_AUX_ANAOVRD1_D, \
						    _CNL_AUX_ANAOVRD1_F))
#घोषणा   CNL_AUX_ANAOVRD1_ENABLE	(1 << 16)
#घोषणा   CNL_AUX_ANAOVRD1_LDO_BYPASS	(1 << 23)

#घोषणा _ICL_AUX_REG_IDX(pw_idx)	((pw_idx) - ICL_PW_CTL_IDX_AUX_A)
#घोषणा _ICL_AUX_ANAOVRD1_A		0x162398
#घोषणा _ICL_AUX_ANAOVRD1_B		0x6C398
#घोषणा ICL_AUX_ANAOVRD1(pw_idx)	_MMIO(_PICK(_ICL_AUX_REG_IDX(pw_idx), \
						    _ICL_AUX_ANAOVRD1_A, \
						    _ICL_AUX_ANAOVRD1_B))
#घोषणा   ICL_AUX_ANAOVRD1_LDO_BYPASS	(1 << 7)
#घोषणा   ICL_AUX_ANAOVRD1_ENABLE	(1 << 0)

/* HDCP Key Registers */
#घोषणा HDCP_KEY_CONF			_MMIO(0x66c00)
#घोषणा  HDCP_AKSV_SEND_TRIGGER		BIT(31)
#घोषणा  HDCP_CLEAR_KEYS_TRIGGER	BIT(30)
#घोषणा  HDCP_KEY_LOAD_TRIGGER		BIT(8)
#घोषणा HDCP_KEY_STATUS			_MMIO(0x66c04)
#घोषणा  HDCP_FUSE_IN_PROGRESS		BIT(7)
#घोषणा  HDCP_FUSE_ERROR		BIT(6)
#घोषणा  HDCP_FUSE_DONE			BIT(5)
#घोषणा  HDCP_KEY_LOAD_STATUS		BIT(1)
#घोषणा  HDCP_KEY_LOAD_DONE		BIT(0)
#घोषणा HDCP_AKSV_LO			_MMIO(0x66c10)
#घोषणा HDCP_AKSV_HI			_MMIO(0x66c14)

/* HDCP Repeater Registers */
#घोषणा HDCP_REP_CTL			_MMIO(0x66d00)
#घोषणा  HDCP_TRANSA_REP_PRESENT	BIT(31)
#घोषणा  HDCP_TRANSB_REP_PRESENT	BIT(30)
#घोषणा  HDCP_TRANSC_REP_PRESENT	BIT(29)
#घोषणा  HDCP_TRANSD_REP_PRESENT	BIT(28)
#घोषणा  HDCP_DDIB_REP_PRESENT		BIT(30)
#घोषणा  HDCP_DDIA_REP_PRESENT		BIT(29)
#घोषणा  HDCP_DDIC_REP_PRESENT		BIT(28)
#घोषणा  HDCP_DDID_REP_PRESENT		BIT(27)
#घोषणा  HDCP_DDIF_REP_PRESENT		BIT(26)
#घोषणा  HDCP_DDIE_REP_PRESENT		BIT(25)
#घोषणा  HDCP_TRANSA_SHA1_M0		(1 << 20)
#घोषणा  HDCP_TRANSB_SHA1_M0		(2 << 20)
#घोषणा  HDCP_TRANSC_SHA1_M0		(3 << 20)
#घोषणा  HDCP_TRANSD_SHA1_M0		(4 << 20)
#घोषणा  HDCP_DDIB_SHA1_M0		(1 << 20)
#घोषणा  HDCP_DDIA_SHA1_M0		(2 << 20)
#घोषणा  HDCP_DDIC_SHA1_M0		(3 << 20)
#घोषणा  HDCP_DDID_SHA1_M0		(4 << 20)
#घोषणा  HDCP_DDIF_SHA1_M0		(5 << 20)
#घोषणा  HDCP_DDIE_SHA1_M0		(6 << 20) /* Bspec says 5? */
#घोषणा  HDCP_SHA1_BUSY			BIT(16)
#घोषणा  HDCP_SHA1_READY		BIT(17)
#घोषणा  HDCP_SHA1_COMPLETE		BIT(18)
#घोषणा  HDCP_SHA1_V_MATCH		BIT(19)
#घोषणा  HDCP_SHA1_TEXT_32		(1 << 1)
#घोषणा  HDCP_SHA1_COMPLETE_HASH	(2 << 1)
#घोषणा  HDCP_SHA1_TEXT_24		(4 << 1)
#घोषणा  HDCP_SHA1_TEXT_16		(5 << 1)
#घोषणा  HDCP_SHA1_TEXT_8		(6 << 1)
#घोषणा  HDCP_SHA1_TEXT_0		(7 << 1)
#घोषणा HDCP_SHA_V_PRIME_H0		_MMIO(0x66d04)
#घोषणा HDCP_SHA_V_PRIME_H1		_MMIO(0x66d08)
#घोषणा HDCP_SHA_V_PRIME_H2		_MMIO(0x66d0C)
#घोषणा HDCP_SHA_V_PRIME_H3		_MMIO(0x66d10)
#घोषणा HDCP_SHA_V_PRIME_H4		_MMIO(0x66d14)
#घोषणा HDCP_SHA_V_PRIME(h)		_MMIO((0x66d04 + (h) * 4))
#घोषणा HDCP_SHA_TEXT			_MMIO(0x66d18)

/* HDCP Auth Registers */
#घोषणा _PORTA_HDCP_AUTHENC		0x66800
#घोषणा _PORTB_HDCP_AUTHENC		0x66500
#घोषणा _PORTC_HDCP_AUTHENC		0x66600
#घोषणा _PORTD_HDCP_AUTHENC		0x66700
#घोषणा _PORTE_HDCP_AUTHENC		0x66A00
#घोषणा _PORTF_HDCP_AUTHENC		0x66900
#घोषणा _PORT_HDCP_AUTHENC(port, x)	_MMIO(_PICK(port, \
					  _PORTA_HDCP_AUTHENC, \
					  _PORTB_HDCP_AUTHENC, \
					  _PORTC_HDCP_AUTHENC, \
					  _PORTD_HDCP_AUTHENC, \
					  _PORTE_HDCP_AUTHENC, \
					  _PORTF_HDCP_AUTHENC) + (x))
#घोषणा PORT_HDCP_CONF(port)		_PORT_HDCP_AUTHENC(port, 0x0)
#घोषणा _TRANSA_HDCP_CONF		0x66400
#घोषणा _TRANSB_HDCP_CONF		0x66500
#घोषणा TRANS_HDCP_CONF(trans)		_MMIO_TRANS(trans, _TRANSA_HDCP_CONF, \
						    _TRANSB_HDCP_CONF)
#घोषणा HDCP_CONF(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP_CONF(trans) : \
					 PORT_HDCP_CONF(port))

#घोषणा  HDCP_CONF_CAPTURE_AN		BIT(0)
#घोषणा  HDCP_CONF_AUTH_AND_ENC		(BIT(1) | BIT(0))
#घोषणा PORT_HDCP_ANINIT(port)		_PORT_HDCP_AUTHENC(port, 0x4)
#घोषणा _TRANSA_HDCP_ANINIT		0x66404
#घोषणा _TRANSB_HDCP_ANINIT		0x66504
#घोषणा TRANS_HDCP_ANINIT(trans)	_MMIO_TRANS(trans, \
						    _TRANSA_HDCP_ANINIT, \
						    _TRANSB_HDCP_ANINIT)
#घोषणा HDCP_ANINIT(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP_ANINIT(trans) : \
					 PORT_HDCP_ANINIT(port))

#घोषणा PORT_HDCP_ANLO(port)		_PORT_HDCP_AUTHENC(port, 0x8)
#घोषणा _TRANSA_HDCP_ANLO		0x66408
#घोषणा _TRANSB_HDCP_ANLO		0x66508
#घोषणा TRANS_HDCP_ANLO(trans)		_MMIO_TRANS(trans, _TRANSA_HDCP_ANLO, \
						    _TRANSB_HDCP_ANLO)
#घोषणा HDCP_ANLO(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP_ANLO(trans) : \
					 PORT_HDCP_ANLO(port))

#घोषणा PORT_HDCP_ANHI(port)		_PORT_HDCP_AUTHENC(port, 0xC)
#घोषणा _TRANSA_HDCP_ANHI		0x6640C
#घोषणा _TRANSB_HDCP_ANHI		0x6650C
#घोषणा TRANS_HDCP_ANHI(trans)		_MMIO_TRANS(trans, _TRANSA_HDCP_ANHI, \
						    _TRANSB_HDCP_ANHI)
#घोषणा HDCP_ANHI(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP_ANHI(trans) : \
					 PORT_HDCP_ANHI(port))

#घोषणा PORT_HDCP_BKSVLO(port)		_PORT_HDCP_AUTHENC(port, 0x10)
#घोषणा _TRANSA_HDCP_BKSVLO		0x66410
#घोषणा _TRANSB_HDCP_BKSVLO		0x66510
#घोषणा TRANS_HDCP_BKSVLO(trans)	_MMIO_TRANS(trans, \
						    _TRANSA_HDCP_BKSVLO, \
						    _TRANSB_HDCP_BKSVLO)
#घोषणा HDCP_BKSVLO(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP_BKSVLO(trans) : \
					 PORT_HDCP_BKSVLO(port))

#घोषणा PORT_HDCP_BKSVHI(port)		_PORT_HDCP_AUTHENC(port, 0x14)
#घोषणा _TRANSA_HDCP_BKSVHI		0x66414
#घोषणा _TRANSB_HDCP_BKSVHI		0x66514
#घोषणा TRANS_HDCP_BKSVHI(trans)	_MMIO_TRANS(trans, \
						    _TRANSA_HDCP_BKSVHI, \
						    _TRANSB_HDCP_BKSVHI)
#घोषणा HDCP_BKSVHI(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP_BKSVHI(trans) : \
					 PORT_HDCP_BKSVHI(port))

#घोषणा PORT_HDCP_RPRIME(port)		_PORT_HDCP_AUTHENC(port, 0x18)
#घोषणा _TRANSA_HDCP_RPRIME		0x66418
#घोषणा _TRANSB_HDCP_RPRIME		0x66518
#घोषणा TRANS_HDCP_RPRIME(trans)	_MMIO_TRANS(trans, \
						    _TRANSA_HDCP_RPRIME, \
						    _TRANSB_HDCP_RPRIME)
#घोषणा HDCP_RPRIME(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP_RPRIME(trans) : \
					 PORT_HDCP_RPRIME(port))

#घोषणा PORT_HDCP_STATUS(port)		_PORT_HDCP_AUTHENC(port, 0x1C)
#घोषणा _TRANSA_HDCP_STATUS		0x6641C
#घोषणा _TRANSB_HDCP_STATUS		0x6651C
#घोषणा TRANS_HDCP_STATUS(trans)	_MMIO_TRANS(trans, \
						    _TRANSA_HDCP_STATUS, \
						    _TRANSB_HDCP_STATUS)
#घोषणा HDCP_STATUS(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP_STATUS(trans) : \
					 PORT_HDCP_STATUS(port))

#घोषणा  HDCP_STATUS_STREAM_A_ENC	BIT(31)
#घोषणा  HDCP_STATUS_STREAM_B_ENC	BIT(30)
#घोषणा  HDCP_STATUS_STREAM_C_ENC	BIT(29)
#घोषणा  HDCP_STATUS_STREAM_D_ENC	BIT(28)
#घोषणा  HDCP_STATUS_AUTH		BIT(21)
#घोषणा  HDCP_STATUS_ENC		BIT(20)
#घोषणा  HDCP_STATUS_RI_MATCH		BIT(19)
#घोषणा  HDCP_STATUS_R0_READY		BIT(18)
#घोषणा  HDCP_STATUS_AN_READY		BIT(17)
#घोषणा  HDCP_STATUS_CIPHER		BIT(16)
#घोषणा  HDCP_STATUS_FRAME_CNT(x)	(((x) >> 8) & 0xff)

/* HDCP2.2 Registers */
#घोषणा _PORTA_HDCP2_BASE		0x66800
#घोषणा _PORTB_HDCP2_BASE		0x66500
#घोषणा _PORTC_HDCP2_BASE		0x66600
#घोषणा _PORTD_HDCP2_BASE		0x66700
#घोषणा _PORTE_HDCP2_BASE		0x66A00
#घोषणा _PORTF_HDCP2_BASE		0x66900
#घोषणा _PORT_HDCP2_BASE(port, x)	_MMIO(_PICK((port), \
					  _PORTA_HDCP2_BASE, \
					  _PORTB_HDCP2_BASE, \
					  _PORTC_HDCP2_BASE, \
					  _PORTD_HDCP2_BASE, \
					  _PORTE_HDCP2_BASE, \
					  _PORTF_HDCP2_BASE) + (x))

#घोषणा PORT_HDCP2_AUTH(port)		_PORT_HDCP2_BASE(port, 0x98)
#घोषणा _TRANSA_HDCP2_AUTH		0x66498
#घोषणा _TRANSB_HDCP2_AUTH		0x66598
#घोषणा TRANS_HDCP2_AUTH(trans)		_MMIO_TRANS(trans, _TRANSA_HDCP2_AUTH, \
						    _TRANSB_HDCP2_AUTH)
#घोषणा   AUTH_LINK_AUTHENTICATED	BIT(31)
#घोषणा   AUTH_LINK_TYPE		BIT(30)
#घोषणा   AUTH_FORCE_CLR_INPUTCTR	BIT(19)
#घोषणा   AUTH_CLR_KEYS			BIT(18)
#घोषणा HDCP2_AUTH(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP2_AUTH(trans) : \
					 PORT_HDCP2_AUTH(port))

#घोषणा PORT_HDCP2_CTL(port)		_PORT_HDCP2_BASE(port, 0xB0)
#घोषणा _TRANSA_HDCP2_CTL		0x664B0
#घोषणा _TRANSB_HDCP2_CTL		0x665B0
#घोषणा TRANS_HDCP2_CTL(trans)		_MMIO_TRANS(trans, _TRANSA_HDCP2_CTL, \
						    _TRANSB_HDCP2_CTL)
#घोषणा   CTL_LINK_ENCRYPTION_REQ	BIT(31)
#घोषणा HDCP2_CTL(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP2_CTL(trans) : \
					 PORT_HDCP2_CTL(port))

#घोषणा PORT_HDCP2_STATUS(port)		_PORT_HDCP2_BASE(port, 0xB4)
#घोषणा _TRANSA_HDCP2_STATUS		0x664B4
#घोषणा _TRANSB_HDCP2_STATUS		0x665B4
#घोषणा TRANS_HDCP2_STATUS(trans)	_MMIO_TRANS(trans, \
						    _TRANSA_HDCP2_STATUS, \
						    _TRANSB_HDCP2_STATUS)
#घोषणा   LINK_TYPE_STATUS		BIT(22)
#घोषणा   LINK_AUTH_STATUS		BIT(21)
#घोषणा   LINK_ENCRYPTION_STATUS	BIT(20)
#घोषणा HDCP2_STATUS(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP2_STATUS(trans) : \
					 PORT_HDCP2_STATUS(port))

#घोषणा _PIPEA_HDCP2_STREAM_STATUS	0x668C0
#घोषणा _PIPEB_HDCP2_STREAM_STATUS	0x665C0
#घोषणा _PIPEC_HDCP2_STREAM_STATUS	0x666C0
#घोषणा _PIPED_HDCP2_STREAM_STATUS	0x667C0
#घोषणा PIPE_HDCP2_STREAM_STATUS(pipe)		_MMIO(_PICK((pipe), \
						      _PIPEA_HDCP2_STREAM_STATUS, \
						      _PIPEB_HDCP2_STREAM_STATUS, \
						      _PIPEC_HDCP2_STREAM_STATUS, \
						      _PIPED_HDCP2_STREAM_STATUS))

#घोषणा _TRANSA_HDCP2_STREAM_STATUS		0x664C0
#घोषणा _TRANSB_HDCP2_STREAM_STATUS		0x665C0
#घोषणा TRANS_HDCP2_STREAM_STATUS(trans)	_MMIO_TRANS(trans, \
						    _TRANSA_HDCP2_STREAM_STATUS, \
						    _TRANSB_HDCP2_STREAM_STATUS)
#घोषणा   STREAM_ENCRYPTION_STATUS	BIT(31)
#घोषणा   STREAM_TYPE_STATUS		BIT(30)
#घोषणा HDCP2_STREAM_STATUS(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP2_STREAM_STATUS(trans) : \
					 PIPE_HDCP2_STREAM_STATUS(pipe))

#घोषणा _PORTA_HDCP2_AUTH_STREAM		0x66F00
#घोषणा _PORTB_HDCP2_AUTH_STREAM		0x66F04
#घोषणा PORT_HDCP2_AUTH_STREAM(port)	_MMIO_PORT(port, \
						   _PORTA_HDCP2_AUTH_STREAM, \
						   _PORTB_HDCP2_AUTH_STREAM)
#घोषणा _TRANSA_HDCP2_AUTH_STREAM		0x66F00
#घोषणा _TRANSB_HDCP2_AUTH_STREAM		0x66F04
#घोषणा TRANS_HDCP2_AUTH_STREAM(trans)	_MMIO_TRANS(trans, \
						    _TRANSA_HDCP2_AUTH_STREAM, \
						    _TRANSB_HDCP2_AUTH_STREAM)
#घोषणा   AUTH_STREAM_TYPE		BIT(31)
#घोषणा HDCP2_AUTH_STREAM(dev_priv, trans, port) \
					(INTEL_GEN(dev_priv) >= 12 ? \
					 TRANS_HDCP2_AUTH_STREAM(trans) : \
					 PORT_HDCP2_AUTH_STREAM(port))

/* Per-pipe DDI Function Control */
#घोषणा _TRANS_DDI_FUNC_CTL_A		0x60400
#घोषणा _TRANS_DDI_FUNC_CTL_B		0x61400
#घोषणा _TRANS_DDI_FUNC_CTL_C		0x62400
#घोषणा _TRANS_DDI_FUNC_CTL_D		0x63400
#घोषणा _TRANS_DDI_FUNC_CTL_EDP		0x6F400
#घोषणा _TRANS_DDI_FUNC_CTL_DSI0	0x6b400
#घोषणा _TRANS_DDI_FUNC_CTL_DSI1	0x6bc00
#घोषणा TRANS_DDI_FUNC_CTL(tran) _MMIO_TRANS2(tran, _TRANS_DDI_FUNC_CTL_A)

#घोषणा  TRANS_DDI_FUNC_ENABLE		(1 << 31)
/* Those bits are ignored by pipe EDP since it can only connect to DDI A */
#घोषणा  TRANS_DDI_PORT_SHIFT		28
#घोषणा  TGL_TRANS_DDI_PORT_SHIFT	27
#घोषणा  TRANS_DDI_PORT_MASK		(7 << TRANS_DDI_PORT_SHIFT)
#घोषणा  TGL_TRANS_DDI_PORT_MASK	(0xf << TGL_TRANS_DDI_PORT_SHIFT)
#घोषणा  TRANS_DDI_SELECT_PORT(x)	((x) << TRANS_DDI_PORT_SHIFT)
#घोषणा  TGL_TRANS_DDI_SELECT_PORT(x)	(((x) + 1) << TGL_TRANS_DDI_PORT_SHIFT)
#घोषणा  TRANS_DDI_FUNC_CTL_VAL_TO_PORT(val)	 (((val) & TRANS_DDI_PORT_MASK) >> TRANS_DDI_PORT_SHIFT)
#घोषणा  TGL_TRANS_DDI_FUNC_CTL_VAL_TO_PORT(val) ((((val) & TGL_TRANS_DDI_PORT_MASK) >> TGL_TRANS_DDI_PORT_SHIFT) - 1)
#घोषणा  TRANS_DDI_MODE_SELECT_MASK	(7 << 24)
#घोषणा  TRANS_DDI_MODE_SELECT_HDMI	(0 << 24)
#घोषणा  TRANS_DDI_MODE_SELECT_DVI	(1 << 24)
#घोषणा  TRANS_DDI_MODE_SELECT_DP_SST	(2 << 24)
#घोषणा  TRANS_DDI_MODE_SELECT_DP_MST	(3 << 24)
#घोषणा  TRANS_DDI_MODE_SELECT_FDI	(4 << 24)
#घोषणा  TRANS_DDI_BPC_MASK		(7 << 20)
#घोषणा  TRANS_DDI_BPC_8		(0 << 20)
#घोषणा  TRANS_DDI_BPC_10		(1 << 20)
#घोषणा  TRANS_DDI_BPC_6		(2 << 20)
#घोषणा  TRANS_DDI_BPC_12		(3 << 20)
#घोषणा  TRANS_DDI_PORT_SYNC_MASTER_SELECT_MASK	REG_GENMASK(19, 18) /* bdw-cnl */
#घोषणा  TRANS_DDI_PORT_SYNC_MASTER_SELECT(x)	REG_FIELD_PREP(TRANS_DDI_PORT_SYNC_MASTER_SELECT_MASK, (x))
#घोषणा  TRANS_DDI_PVSYNC		(1 << 17)
#घोषणा  TRANS_DDI_PHSYNC		(1 << 16)
#घोषणा  TRANS_DDI_PORT_SYNC_ENABLE	REG_BIT(15) /* bdw-cnl */
#घोषणा  TRANS_DDI_EDP_INPUT_MASK	(7 << 12)
#घोषणा  TRANS_DDI_EDP_INPUT_A_ON	(0 << 12)
#घोषणा  TRANS_DDI_EDP_INPUT_A_ONOFF	(4 << 12)
#घोषणा  TRANS_DDI_EDP_INPUT_B_ONOFF	(5 << 12)
#घोषणा  TRANS_DDI_EDP_INPUT_C_ONOFF	(6 << 12)
#घोषणा  TRANS_DDI_EDP_INPUT_D_ONOFF	(7 << 12)
#घोषणा  TRANS_DDI_MST_TRANSPORT_SELECT_MASK	REG_GENMASK(11, 10)
#घोषणा  TRANS_DDI_MST_TRANSPORT_SELECT(trans)	\
	REG_FIELD_PREP(TRANS_DDI_MST_TRANSPORT_SELECT_MASK, trans)
#घोषणा  TRANS_DDI_HDCP_SIGNALLING	(1 << 9)
#घोषणा  TRANS_DDI_DP_VC_PAYLOAD_ALLOC	(1 << 8)
#घोषणा  TRANS_DDI_HDMI_SCRAMBLER_CTS_ENABLE (1 << 7)
#घोषणा  TRANS_DDI_HDMI_SCRAMBLER_RESET_FREQ (1 << 6)
#घोषणा  TRANS_DDI_HDCP_SELECT		REG_BIT(5)
#घोषणा  TRANS_DDI_BFI_ENABLE		(1 << 4)
#घोषणा  TRANS_DDI_HIGH_TMDS_CHAR_RATE	(1 << 4)
#घोषणा  TRANS_DDI_HDMI_SCRAMBLING	(1 << 0)
#घोषणा  TRANS_DDI_HDMI_SCRAMBLING_MASK (TRANS_DDI_HDMI_SCRAMBLER_CTS_ENABLE \
					| TRANS_DDI_HDMI_SCRAMBLER_RESET_FREQ \
					| TRANS_DDI_HDMI_SCRAMBLING)

#घोषणा _TRANS_DDI_FUNC_CTL2_A		0x60404
#घोषणा _TRANS_DDI_FUNC_CTL2_B		0x61404
#घोषणा _TRANS_DDI_FUNC_CTL2_C		0x62404
#घोषणा _TRANS_DDI_FUNC_CTL2_EDP	0x6f404
#घोषणा _TRANS_DDI_FUNC_CTL2_DSI0	0x6b404
#घोषणा _TRANS_DDI_FUNC_CTL2_DSI1	0x6bc04
#घोषणा TRANS_DDI_FUNC_CTL2(tran)	_MMIO_TRANS2(tran, _TRANS_DDI_FUNC_CTL2_A)
#घोषणा  PORT_SYNC_MODE_ENABLE			REG_BIT(4)
#घोषणा  PORT_SYNC_MODE_MASTER_SELECT_MASK	REG_GENMASK(2, 0)
#घोषणा  PORT_SYNC_MODE_MASTER_SELECT(x)	REG_FIELD_PREP(PORT_SYNC_MODE_MASTER_SELECT_MASK, (x))

/* DisplayPort Transport Control */
#घोषणा _DP_TP_CTL_A			0x64040
#घोषणा _DP_TP_CTL_B			0x64140
#घोषणा _TGL_DP_TP_CTL_A		0x60540
#घोषणा DP_TP_CTL(port) _MMIO_PORT(port, _DP_TP_CTL_A, _DP_TP_CTL_B)
#घोषणा TGL_DP_TP_CTL(tran) _MMIO_TRANS2((tran), _TGL_DP_TP_CTL_A)
#घोषणा  DP_TP_CTL_ENABLE			(1 << 31)
#घोषणा  DP_TP_CTL_FEC_ENABLE			(1 << 30)
#घोषणा  DP_TP_CTL_MODE_SST			(0 << 27)
#घोषणा  DP_TP_CTL_MODE_MST			(1 << 27)
#घोषणा  DP_TP_CTL_FORCE_ACT			(1 << 25)
#घोषणा  DP_TP_CTL_ENHANCED_FRAME_ENABLE	(1 << 18)
#घोषणा  DP_TP_CTL_FDI_AUTOTRAIN		(1 << 15)
#घोषणा  DP_TP_CTL_LINK_TRAIN_MASK		(7 << 8)
#घोषणा  DP_TP_CTL_LINK_TRAIN_PAT1		(0 << 8)
#घोषणा  DP_TP_CTL_LINK_TRAIN_PAT2		(1 << 8)
#घोषणा  DP_TP_CTL_LINK_TRAIN_PAT3		(4 << 8)
#घोषणा  DP_TP_CTL_LINK_TRAIN_PAT4		(5 << 8)
#घोषणा  DP_TP_CTL_LINK_TRAIN_IDLE		(2 << 8)
#घोषणा  DP_TP_CTL_LINK_TRAIN_NORMAL		(3 << 8)
#घोषणा  DP_TP_CTL_SCRAMBLE_DISABLE		(1 << 7)

/* DisplayPort Transport Status */
#घोषणा _DP_TP_STATUS_A			0x64044
#घोषणा _DP_TP_STATUS_B			0x64144
#घोषणा _TGL_DP_TP_STATUS_A		0x60544
#घोषणा DP_TP_STATUS(port) _MMIO_PORT(port, _DP_TP_STATUS_A, _DP_TP_STATUS_B)
#घोषणा TGL_DP_TP_STATUS(tran) _MMIO_TRANS2((tran), _TGL_DP_TP_STATUS_A)
#घोषणा  DP_TP_STATUS_FEC_ENABLE_LIVE		(1 << 28)
#घोषणा  DP_TP_STATUS_IDLE_DONE			(1 << 25)
#घोषणा  DP_TP_STATUS_ACT_SENT			(1 << 24)
#घोषणा  DP_TP_STATUS_MODE_STATUS_MST		(1 << 23)
#घोषणा  DP_TP_STATUS_AUTOTRAIN_DONE		(1 << 12)
#घोषणा  DP_TP_STATUS_PAYLOAD_MAPPING_VC2	(3 << 8)
#घोषणा  DP_TP_STATUS_PAYLOAD_MAPPING_VC1	(3 << 4)
#घोषणा  DP_TP_STATUS_PAYLOAD_MAPPING_VC0	(3 << 0)

/* DDI Buffer Control */
#घोषणा _DDI_BUF_CTL_A				0x64000
#घोषणा _DDI_BUF_CTL_B				0x64100
#घोषणा DDI_BUF_CTL(port) _MMIO_PORT(port, _DDI_BUF_CTL_A, _DDI_BUF_CTL_B)
#घोषणा  DDI_BUF_CTL_ENABLE			(1 << 31)
#घोषणा  DDI_BUF_TRANS_SELECT(n)	((n) << 24)
#घोषणा  DDI_BUF_EMP_MASK			(0xf << 24)
#घोषणा  DDI_BUF_PORT_REVERSAL			(1 << 16)
#घोषणा  DDI_BUF_IS_IDLE			(1 << 7)
#घोषणा  DDI_A_4_LANES				(1 << 4)
#घोषणा  DDI_PORT_WIDTH(width)			(((width) - 1) << 1)
#घोषणा  DDI_PORT_WIDTH_MASK			(7 << 1)
#घोषणा  DDI_PORT_WIDTH_SHIFT			1
#घोषणा  DDI_INIT_DISPLAY_DETECTED		(1 << 0)

/* DDI Buffer Translations */
#घोषणा _DDI_BUF_TRANS_A		0x64E00
#घोषणा _DDI_BUF_TRANS_B		0x64E60
#घोषणा DDI_BUF_TRANS_LO(port, i)	_MMIO(_PORT(port, _DDI_BUF_TRANS_A, _DDI_BUF_TRANS_B) + (i) * 8)
#घोषणा  DDI_BUF_BALANCE_LEG_ENABLE	(1 << 31)
#घोषणा DDI_BUF_TRANS_HI(port, i)	_MMIO(_PORT(port, _DDI_BUF_TRANS_A, _DDI_BUF_TRANS_B) + (i) * 8 + 4)

/* DDI DP Compliance Control */
#घोषणा _DDI_DP_COMP_CTL_A			0x605F0
#घोषणा _DDI_DP_COMP_CTL_B			0x615F0
#घोषणा DDI_DP_COMP_CTL(pipe)			_MMIO_PIPE(pipe, _DDI_DP_COMP_CTL_A, _DDI_DP_COMP_CTL_B)
#घोषणा   DDI_DP_COMP_CTL_ENABLE		(1 << 31)
#घोषणा   DDI_DP_COMP_CTL_D10_2			(0 << 28)
#घोषणा   DDI_DP_COMP_CTL_SCRAMBLED_0		(1 << 28)
#घोषणा   DDI_DP_COMP_CTL_PRBS7			(2 << 28)
#घोषणा   DDI_DP_COMP_CTL_CUSTOM80		(3 << 28)
#घोषणा   DDI_DP_COMP_CTL_HBR2			(4 << 28)
#घोषणा   DDI_DP_COMP_CTL_SCRAMBLED_1		(5 << 28)
#घोषणा   DDI_DP_COMP_CTL_HBR2_RESET		(0xFC << 0)

/* DDI DP Compliance Pattern */
#घोषणा _DDI_DP_COMP_PAT_A			0x605F4
#घोषणा _DDI_DP_COMP_PAT_B			0x615F4
#घोषणा DDI_DP_COMP_PAT(pipe, i)		_MMIO(_PIPE(pipe, _DDI_DP_COMP_PAT_A, _DDI_DP_COMP_PAT_B) + (i) * 4)

/* Sideband Interface (SBI) is programmed indirectly, via
 * SBI_ADDR, which contains the रेजिस्टर offset; and SBI_DATA,
 * which contains the payload */
#घोषणा SBI_ADDR			_MMIO(0xC6000)
#घोषणा SBI_DATA			_MMIO(0xC6004)
#घोषणा SBI_CTL_STAT			_MMIO(0xC6008)
#घोषणा  SBI_CTL_DEST_ICLK		(0x0 << 16)
#घोषणा  SBI_CTL_DEST_MPHY		(0x1 << 16)
#घोषणा  SBI_CTL_OP_IORD		(0x2 << 8)
#घोषणा  SBI_CTL_OP_IOWR		(0x3 << 8)
#घोषणा  SBI_CTL_OP_CRRD		(0x6 << 8)
#घोषणा  SBI_CTL_OP_CRWR		(0x7 << 8)
#घोषणा  SBI_RESPONSE_FAIL		(0x1 << 1)
#घोषणा  SBI_RESPONSE_SUCCESS		(0x0 << 1)
#घोषणा  SBI_BUSY			(0x1 << 0)
#घोषणा  SBI_READY			(0x0 << 0)

/* SBI offsets */
#घोषणा  SBI_SSCDIVINTPHASE			0x0200
#घोषणा  SBI_SSCDIVINTPHASE6			0x0600
#घोषणा   SBI_SSCDIVINTPHASE_DIVSEL_SHIFT	1
#घोषणा   SBI_SSCDIVINTPHASE_DIVSEL_MASK	(0x7f << 1)
#घोषणा   SBI_SSCDIVINTPHASE_DIVSEL(x)		((x) << 1)
#घोषणा   SBI_SSCDIVINTPHASE_INCVAL_SHIFT	8
#घोषणा   SBI_SSCDIVINTPHASE_INCVAL_MASK	(0x7f << 8)
#घोषणा   SBI_SSCDIVINTPHASE_INCVAL(x)		((x) << 8)
#घोषणा   SBI_SSCDIVINTPHASE_सूची(x)		((x) << 15)
#घोषणा   SBI_SSCDIVINTPHASE_PROPAGATE		(1 << 0)
#घोषणा  SBI_SSCDITHPHASE			0x0204
#घोषणा  SBI_SSCCTL				0x020c
#घोषणा  SBI_SSCCTL6				0x060C
#घोषणा   SBI_SSCCTL_PATHALT			(1 << 3)
#घोषणा   SBI_SSCCTL_DISABLE			(1 << 0)
#घोषणा  SBI_SSCAUXDIV6				0x0610
#घोषणा   SBI_SSCAUXDIV_FINALDIV2SEL_SHIFT	4
#घोषणा   SBI_SSCAUXDIV_FINALDIV2SEL_MASK	(1 << 4)
#घोषणा   SBI_SSCAUXDIV_FINALDIV2SEL(x)		((x) << 4)
#घोषणा  SBI_DBUFF0				0x2a00
#घोषणा  SBI_GEN0				0x1f00
#घोषणा   SBI_GEN0_CFG_BUFFENABLE_DISABLE	(1 << 0)

/* LPT PIXCLK_GATE */
#घोषणा PIXCLK_GATE			_MMIO(0xC6020)
#घोषणा  PIXCLK_GATE_UNGATE		(1 << 0)
#घोषणा  PIXCLK_GATE_GATE		(0 << 0)

/* SPLL */
#घोषणा SPLL_CTL			_MMIO(0x46020)
#घोषणा  SPLL_PLL_ENABLE		(1 << 31)
#घोषणा  SPLL_REF_BCLK			(0 << 28)
#घोषणा  SPLL_REF_MUXED_SSC		(1 << 28) /* CPU SSC अगर fused enabled, PCH SSC otherwise */
#घोषणा  SPLL_REF_NON_SSC_HSW		(2 << 28)
#घोषणा  SPLL_REF_PCH_SSC_BDW		(2 << 28)
#घोषणा  SPLL_REF_LCPLL			(3 << 28)
#घोषणा  SPLL_REF_MASK			(3 << 28)
#घोषणा  SPLL_FREQ_810MHz		(0 << 26)
#घोषणा  SPLL_FREQ_1350MHz		(1 << 26)
#घोषणा  SPLL_FREQ_2700MHz		(2 << 26)
#घोषणा  SPLL_FREQ_MASK			(3 << 26)

/* WRPLL */
#घोषणा _WRPLL_CTL1			0x46040
#घोषणा _WRPLL_CTL2			0x46060
#घोषणा WRPLL_CTL(pll)			_MMIO_PIPE(pll, _WRPLL_CTL1, _WRPLL_CTL2)
#घोषणा  WRPLL_PLL_ENABLE		(1 << 31)
#घोषणा  WRPLL_REF_BCLK			(0 << 28)
#घोषणा  WRPLL_REF_PCH_SSC		(1 << 28)
#घोषणा  WRPLL_REF_MUXED_SSC_BDW	(2 << 28) /* CPU SSC अगर fused enabled, PCH SSC otherwise */
#घोषणा  WRPLL_REF_SPECIAL_HSW		(2 << 28) /* muxed SSC (ULT), non-SSC (non-ULT) */
#घोषणा  WRPLL_REF_LCPLL		(3 << 28)
#घोषणा  WRPLL_REF_MASK			(3 << 28)
/* WRPLL भागider programming */
#घोषणा  WRPLL_DIVIDER_REFERENCE(x)	((x) << 0)
#घोषणा  WRPLL_DIVIDER_REF_MASK		(0xff)
#घोषणा  WRPLL_DIVIDER_POST(x)		((x) << 8)
#घोषणा  WRPLL_DIVIDER_POST_MASK	(0x3f << 8)
#घोषणा  WRPLL_DIVIDER_POST_SHIFT	8
#घोषणा  WRPLL_DIVIDER_FEEDBACK(x)	((x) << 16)
#घोषणा  WRPLL_DIVIDER_FB_SHIFT		16
#घोषणा  WRPLL_DIVIDER_FB_MASK		(0xff << 16)

/* Port घड़ी selection */
#घोषणा _PORT_CLK_SEL_A			0x46100
#घोषणा _PORT_CLK_SEL_B			0x46104
#घोषणा PORT_CLK_SEL(port) _MMIO_PORT(port, _PORT_CLK_SEL_A, _PORT_CLK_SEL_B)
#घोषणा  PORT_CLK_SEL_LCPLL_2700	(0 << 29)
#घोषणा  PORT_CLK_SEL_LCPLL_1350	(1 << 29)
#घोषणा  PORT_CLK_SEL_LCPLL_810		(2 << 29)
#घोषणा  PORT_CLK_SEL_SPLL		(3 << 29)
#घोषणा  PORT_CLK_SEL_WRPLL(pll)	(((pll) + 4) << 29)
#घोषणा  PORT_CLK_SEL_WRPLL1		(4 << 29)
#घोषणा  PORT_CLK_SEL_WRPLL2		(5 << 29)
#घोषणा  PORT_CLK_SEL_NONE		(7 << 29)
#घोषणा  PORT_CLK_SEL_MASK		(7 << 29)

/* On ICL+ this is the same as PORT_CLK_SEL, but all bits change. */
#घोषणा DDI_CLK_SEL(port)		PORT_CLK_SEL(port)
#घोषणा  DDI_CLK_SEL_NONE		(0x0 << 28)
#घोषणा  DDI_CLK_SEL_MG			(0x8 << 28)
#घोषणा  DDI_CLK_SEL_TBT_162		(0xC << 28)
#घोषणा  DDI_CLK_SEL_TBT_270		(0xD << 28)
#घोषणा  DDI_CLK_SEL_TBT_540		(0xE << 28)
#घोषणा  DDI_CLK_SEL_TBT_810		(0xF << 28)
#घोषणा  DDI_CLK_SEL_MASK		(0xF << 28)

/* Transcoder घड़ी selection */
#घोषणा _TRANS_CLK_SEL_A		0x46140
#घोषणा _TRANS_CLK_SEL_B		0x46144
#घोषणा TRANS_CLK_SEL(tran) _MMIO_TRANS(tran, _TRANS_CLK_SEL_A, _TRANS_CLK_SEL_B)
/* For each transcoder, we need to select the corresponding port घड़ी */
#घोषणा  TRANS_CLK_SEL_DISABLED		(0x0 << 29)
#घोषणा  TRANS_CLK_SEL_PORT(x)		(((x) + 1) << 29)
#घोषणा  TGL_TRANS_CLK_SEL_DISABLED	(0x0 << 28)
#घोषणा  TGL_TRANS_CLK_SEL_PORT(x)	(((x) + 1) << 28)


#घोषणा CDCLK_FREQ			_MMIO(0x46200)

#घोषणा _TRANSA_MSA_MISC		0x60410
#घोषणा _TRANSB_MSA_MISC		0x61410
#घोषणा _TRANSC_MSA_MISC		0x62410
#घोषणा _TRANS_EDP_MSA_MISC		0x6f410
#घोषणा TRANS_MSA_MISC(tran) _MMIO_TRANS2(tran, _TRANSA_MSA_MISC)
/* See DP_MSA_MISC_* क्रम the bit definitions */

/* LCPLL Control */
#घोषणा LCPLL_CTL			_MMIO(0x130040)
#घोषणा  LCPLL_PLL_DISABLE		(1 << 31)
#घोषणा  LCPLL_PLL_LOCK			(1 << 30)
#घोषणा  LCPLL_REF_NON_SSC		(0 << 28)
#घोषणा  LCPLL_REF_BCLK			(2 << 28)
#घोषणा  LCPLL_REF_PCH_SSC		(3 << 28)
#घोषणा  LCPLL_REF_MASK			(3 << 28)
#घोषणा  LCPLL_CLK_FREQ_MASK		(3 << 26)
#घोषणा  LCPLL_CLK_FREQ_450		(0 << 26)
#घोषणा  LCPLL_CLK_FREQ_54O_BDW		(1 << 26)
#घोषणा  LCPLL_CLK_FREQ_337_5_BDW	(2 << 26)
#घोषणा  LCPLL_CLK_FREQ_675_BDW		(3 << 26)
#घोषणा  LCPLL_CD_CLOCK_DISABLE		(1 << 25)
#घोषणा  LCPLL_ROOT_CD_CLOCK_DISABLE	(1 << 24)
#घोषणा  LCPLL_CD2X_CLOCK_DISABLE	(1 << 23)
#घोषणा  LCPLL_POWER_DOWN_ALLOW		(1 << 22)
#घोषणा  LCPLL_CD_SOURCE_FCLK		(1 << 21)
#घोषणा  LCPLL_CD_SOURCE_FCLK_DONE	(1 << 19)

/*
 * SKL Clocks
 */

/* CDCLK_CTL */
#घोषणा CDCLK_CTL			_MMIO(0x46000)
#घोषणा  CDCLK_FREQ_SEL_MASK		(3 << 26)
#घोषणा  CDCLK_FREQ_450_432		(0 << 26)
#घोषणा  CDCLK_FREQ_540			(1 << 26)
#घोषणा  CDCLK_FREQ_337_308		(2 << 26)
#घोषणा  CDCLK_FREQ_675_617		(3 << 26)
#घोषणा  BXT_CDCLK_CD2X_DIV_SEL_MASK	(3 << 22)
#घोषणा  BXT_CDCLK_CD2X_DIV_SEL_1	(0 << 22)
#घोषणा  BXT_CDCLK_CD2X_DIV_SEL_1_5	(1 << 22)
#घोषणा  BXT_CDCLK_CD2X_DIV_SEL_2	(2 << 22)
#घोषणा  BXT_CDCLK_CD2X_DIV_SEL_4	(3 << 22)
#घोषणा  BXT_CDCLK_CD2X_PIPE(pipe)	((pipe) << 20)
#घोषणा  CDCLK_DIVMUX_CD_OVERRIDE	(1 << 19)
#घोषणा  BXT_CDCLK_CD2X_PIPE_NONE	BXT_CDCLK_CD2X_PIPE(3)
#घोषणा  ICL_CDCLK_CD2X_PIPE(pipe)	(_PICK(pipe, 0, 2, 6) << 19)
#घोषणा  ICL_CDCLK_CD2X_PIPE_NONE	(7 << 19)
#घोषणा  TGL_CDCLK_CD2X_PIPE(pipe)	BXT_CDCLK_CD2X_PIPE(pipe)
#घोषणा  TGL_CDCLK_CD2X_PIPE_NONE	ICL_CDCLK_CD2X_PIPE_NONE
#घोषणा  BXT_CDCLK_SSA_PRECHARGE_ENABLE	(1 << 16)
#घोषणा  CDCLK_FREQ_DECIMAL_MASK	(0x7ff)

/* LCPLL_CTL */
#घोषणा LCPLL1_CTL		_MMIO(0x46010)
#घोषणा LCPLL2_CTL		_MMIO(0x46014)
#घोषणा  LCPLL_PLL_ENABLE	(1 << 31)

/* DPLL control1 */
#घोषणा DPLL_CTRL1		_MMIO(0x6C058)
#घोषणा  DPLL_CTRL1_HDMI_MODE(id)		(1 << ((id) * 6 + 5))
#घोषणा  DPLL_CTRL1_SSC(id)			(1 << ((id) * 6 + 4))
#घोषणा  DPLL_CTRL1_LINK_RATE_MASK(id)		(7 << ((id) * 6 + 1))
#घोषणा  DPLL_CTRL1_LINK_RATE_SHIFT(id)		((id) * 6 + 1)
#घोषणा  DPLL_CTRL1_LINK_RATE(linkrate, id)	((linkrate) << ((id) * 6 + 1))
#घोषणा  DPLL_CTRL1_OVERRIDE(id)		(1 << ((id) * 6))
#घोषणा  DPLL_CTRL1_LINK_RATE_2700		0
#घोषणा  DPLL_CTRL1_LINK_RATE_1350		1
#घोषणा  DPLL_CTRL1_LINK_RATE_810		2
#घोषणा  DPLL_CTRL1_LINK_RATE_1620		3
#घोषणा  DPLL_CTRL1_LINK_RATE_1080		4
#घोषणा  DPLL_CTRL1_LINK_RATE_2160		5

/* DPLL control2 */
#घोषणा DPLL_CTRL2				_MMIO(0x6C05C)
#घोषणा  DPLL_CTRL2_DDI_CLK_OFF(port)		(1 << ((port) + 15))
#घोषणा  DPLL_CTRL2_DDI_CLK_SEL_MASK(port)	(3 << ((port) * 3 + 1))
#घोषणा  DPLL_CTRL2_DDI_CLK_SEL_SHIFT(port)    ((port) * 3 + 1)
#घोषणा  DPLL_CTRL2_DDI_CLK_SEL(clk, port)	((clk) << ((port) * 3 + 1))
#घोषणा  DPLL_CTRL2_DDI_SEL_OVERRIDE(port)     (1 << ((port) * 3))

/* DPLL Status */
#घोषणा DPLL_STATUS	_MMIO(0x6C060)
#घोषणा  DPLL_LOCK(id) (1 << ((id) * 8))

/* DPLL cfg */
#घोषणा _DPLL1_CFGCR1	0x6C040
#घोषणा _DPLL2_CFGCR1	0x6C048
#घोषणा _DPLL3_CFGCR1	0x6C050
#घोषणा  DPLL_CFGCR1_FREQ_ENABLE	(1 << 31)
#घोषणा  DPLL_CFGCR1_DCO_FRACTION_MASK	(0x7fff << 9)
#घोषणा  DPLL_CFGCR1_DCO_FRACTION(x)	((x) << 9)
#घोषणा  DPLL_CFGCR1_DCO_INTEGER_MASK	(0x1ff)

#घोषणा _DPLL1_CFGCR2	0x6C044
#घोषणा _DPLL2_CFGCR2	0x6C04C
#घोषणा _DPLL3_CFGCR2	0x6C054
#घोषणा  DPLL_CFGCR2_QDIV_RATIO_MASK	(0xff << 8)
#घोषणा  DPLL_CFGCR2_QDIV_RATIO(x)	((x) << 8)
#घोषणा  DPLL_CFGCR2_QDIV_MODE(x)	((x) << 7)
#घोषणा  DPLL_CFGCR2_KDIV_MASK		(3 << 5)
#घोषणा  DPLL_CFGCR2_KDIV(x)		((x) << 5)
#घोषणा  DPLL_CFGCR2_KDIV_5 (0 << 5)
#घोषणा  DPLL_CFGCR2_KDIV_2 (1 << 5)
#घोषणा  DPLL_CFGCR2_KDIV_3 (2 << 5)
#घोषणा  DPLL_CFGCR2_KDIV_1 (3 << 5)
#घोषणा  DPLL_CFGCR2_PDIV_MASK		(7 << 2)
#घोषणा  DPLL_CFGCR2_PDIV(x)		((x) << 2)
#घोषणा  DPLL_CFGCR2_PDIV_1 (0 << 2)
#घोषणा  DPLL_CFGCR2_PDIV_2 (1 << 2)
#घोषणा  DPLL_CFGCR2_PDIV_3 (2 << 2)
#घोषणा  DPLL_CFGCR2_PDIV_7 (4 << 2)
#घोषणा  DPLL_CFGCR2_PDIV_7_INVALID	(5 << 2)
#घोषणा  DPLL_CFGCR2_CENTRAL_FREQ_MASK	(3)

#घोषणा DPLL_CFGCR1(id)	_MMIO_PIPE((id) - SKL_DPLL1, _DPLL1_CFGCR1, _DPLL2_CFGCR1)
#घोषणा DPLL_CFGCR2(id)	_MMIO_PIPE((id) - SKL_DPLL1, _DPLL1_CFGCR2, _DPLL2_CFGCR2)

/*
 * CNL Clocks
 */
#घोषणा DPCLKA_CFGCR0				_MMIO(0x6C200)
#घोषणा  DPCLKA_CFGCR0_DDI_CLK_OFF(port)	(1 << ((port) ==  PORT_F ? 23 : \
						      (port) + 10))
#घोषणा  DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(port)	((port) == PORT_F ? 21 : \
						(port) * 2)
#घोषणा  DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(port)	(3 << DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(port))
#घोषणा  DPCLKA_CFGCR0_DDI_CLK_SEL(pll, port)	((pll) << DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(port))

/* ICL Clocks */
#घोषणा ICL_DPCLKA_CFGCR0			_MMIO(0x164280)
#घोषणा  ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy)	(1 << _PICK(phy, 10, 11, 24, 4, 5))
#घोषणा  RKL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy)	REG_BIT((phy) + 10)
#घोषणा  ICL_DPCLKA_CFGCR0_TC_CLK_OFF(tc_port)	(1 << ((tc_port) < TC_PORT_4 ? \
						       (tc_port) + 12 : \
						       (tc_port) - TC_PORT_4 + 21))
#घोषणा  ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy)	((phy) * 2)
#घोषणा  ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy)	(3 << ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy))
#घोषणा  ICL_DPCLKA_CFGCR0_DDI_CLK_SEL(pll, phy)	((pll) << ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy))
#घोषणा  RKL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy)	_PICK(phy, 0, 2, 4, 27)
#घोषणा  RKL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy) \
	(3 << RKL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy))
#घोषणा  RKL_DPCLKA_CFGCR0_DDI_CLK_SEL(pll, phy) \
	((pll) << RKL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy))

/*
 * DG1 Clocks
 * First रेजिस्टरs controls the first A and B, जबतक the second रेजिस्टर
 * controls the phy C and D. The bits on these रेजिस्टरs are the
 * same, but refer to dअगरferent phys
 */
#घोषणा _DG1_DPCLKA_CFGCR0				0x164280
#घोषणा _DG1_DPCLKA1_CFGCR0				0x16C280
#घोषणा _DG1_DPCLKA_PHY_IDX(phy)			((phy) % 2)
#घोषणा _DG1_DPCLKA_PLL_IDX(pll)			((pll) % 2)
#घोषणा _DG1_PHY_DPLL_MAP(phy)				((phy) >= PHY_C ? DPLL_ID_DG1_DPLL2 : DPLL_ID_DG1_DPLL0)
#घोषणा DG1_DPCLKA_CFGCR0(phy)				_MMIO_PHY((phy) / 2, \
								  _DG1_DPCLKA_CFGCR0, \
								  _DG1_DPCLKA1_CFGCR0)
#घोषणा   DG1_DPCLKA_CFGCR0_DDI_CLK_OFF(phy)		REG_BIT(_DG1_DPCLKA_PHY_IDX(phy) + 10)
#घोषणा   DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy)	(_DG1_DPCLKA_PHY_IDX(phy) * 2)
#घोषणा   DG1_DPCLKA_CFGCR0_DDI_CLK_SEL(pll, phy)	(_DG1_DPCLKA_PLL_IDX(pll) << DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy))
#घोषणा   DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy)	(0x3 << DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy))
#घोषणा   DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_DPLL_MAP(clk_sel, phy) \
	(((clk_sel) >> DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy)) + _DG1_PHY_DPLL_MAP(phy))

/* ADLS Clocks */
#घोषणा _ADLS_DPCLKA_CFGCR0			0x164280
#घोषणा _ADLS_DPCLKA_CFGCR1			0x1642BC
#घोषणा ADLS_DPCLKA_CFGCR(phy)			_MMIO_PHY((phy) / 3, \
							  _ADLS_DPCLKA_CFGCR0, \
							  _ADLS_DPCLKA_CFGCR1)
#घोषणा  ADLS_DPCLKA_CFGCR_DDI_SHIFT(phy)		(((phy) % 3) * 2)
/* ADLS DPCLKA_CFGCR0 DDI mask */
#घोषणा  ADLS_DPCLKA_DDII_SEL_MASK			REG_GENMASK(5, 4)
#घोषणा  ADLS_DPCLKA_DDIB_SEL_MASK			REG_GENMASK(3, 2)
#घोषणा  ADLS_DPCLKA_DDIA_SEL_MASK			REG_GENMASK(1, 0)
/* ADLS DPCLKA_CFGCR1 DDI mask */
#घोषणा  ADLS_DPCLKA_DDIK_SEL_MASK			REG_GENMASK(3, 2)
#घोषणा  ADLS_DPCLKA_DDIJ_SEL_MASK			REG_GENMASK(1, 0)
#घोषणा  ADLS_DPCLKA_CFGCR_DDI_CLK_SEL_MASK(phy)	_PICK((phy), \
							ADLS_DPCLKA_DDIA_SEL_MASK, \
							ADLS_DPCLKA_DDIB_SEL_MASK, \
							ADLS_DPCLKA_DDII_SEL_MASK, \
							ADLS_DPCLKA_DDIJ_SEL_MASK, \
							ADLS_DPCLKA_DDIK_SEL_MASK)

/* CNL PLL */
#घोषणा DPLL0_ENABLE		0x46010
#घोषणा DPLL1_ENABLE		0x46014
#घोषणा _ADLS_DPLL2_ENABLE	0x46018
#घोषणा _ADLS_DPLL3_ENABLE	0x46030
#घोषणा  PLL_ENABLE		(1 << 31)
#घोषणा  PLL_LOCK		(1 << 30)
#घोषणा  PLL_POWER_ENABLE	(1 << 27)
#घोषणा  PLL_POWER_STATE	(1 << 26)
#घोषणा CNL_DPLL_ENABLE(pll)	_MMIO_PLL3(pll, DPLL0_ENABLE, DPLL1_ENABLE, \
					   _ADLS_DPLL2_ENABLE, _ADLS_DPLL3_ENABLE)

#घोषणा TBT_PLL_ENABLE		_MMIO(0x46020)

#घोषणा _MG_PLL1_ENABLE		0x46030
#घोषणा _MG_PLL2_ENABLE		0x46034
#घोषणा _MG_PLL3_ENABLE		0x46038
#घोषणा _MG_PLL4_ENABLE		0x4603C
/* Bits are the same as DPLL0_ENABLE */
#घोषणा MG_PLL_ENABLE(tc_port)	_MMIO_PORT((tc_port), _MG_PLL1_ENABLE, \
					   _MG_PLL2_ENABLE)

/* DG1 PLL */
#घोषणा DG1_DPLL_ENABLE(pll)    _MMIO_PLL3(pll, DPLL0_ENABLE, DPLL1_ENABLE, \
					   _MG_PLL1_ENABLE, _MG_PLL2_ENABLE)

#घोषणा _MG_REFCLKIN_CTL_PORT1				0x16892C
#घोषणा _MG_REFCLKIN_CTL_PORT2				0x16992C
#घोषणा _MG_REFCLKIN_CTL_PORT3				0x16A92C
#घोषणा _MG_REFCLKIN_CTL_PORT4				0x16B92C
#घोषणा   MG_REFCLKIN_CTL_OD_2_MUX(x)			((x) << 8)
#घोषणा   MG_REFCLKIN_CTL_OD_2_MUX_MASK			(0x7 << 8)
#घोषणा MG_REFCLKIN_CTL(tc_port) _MMIO_PORT((tc_port), \
					    _MG_REFCLKIN_CTL_PORT1, \
					    _MG_REFCLKIN_CTL_PORT2)

#घोषणा _MG_CLKTOP2_CORECLKCTL1_PORT1			0x1688D8
#घोषणा _MG_CLKTOP2_CORECLKCTL1_PORT2			0x1698D8
#घोषणा _MG_CLKTOP2_CORECLKCTL1_PORT3			0x16A8D8
#घोषणा _MG_CLKTOP2_CORECLKCTL1_PORT4			0x16B8D8
#घोषणा   MG_CLKTOP2_CORECLKCTL1_B_DIVRATIO(x)		((x) << 16)
#घोषणा   MG_CLKTOP2_CORECLKCTL1_B_DIVRATIO_MASK	(0xff << 16)
#घोषणा   MG_CLKTOP2_CORECLKCTL1_A_DIVRATIO(x)		((x) << 8)
#घोषणा   MG_CLKTOP2_CORECLKCTL1_A_DIVRATIO_MASK	(0xff << 8)
#घोषणा MG_CLKTOP2_CORECLKCTL1(tc_port) _MMIO_PORT((tc_port), \
						   _MG_CLKTOP2_CORECLKCTL1_PORT1, \
						   _MG_CLKTOP2_CORECLKCTL1_PORT2)

#घोषणा _MG_CLKTOP2_HSCLKCTL_PORT1			0x1688D4
#घोषणा _MG_CLKTOP2_HSCLKCTL_PORT2			0x1698D4
#घोषणा _MG_CLKTOP2_HSCLKCTL_PORT3			0x16A8D4
#घोषणा _MG_CLKTOP2_HSCLKCTL_PORT4			0x16B8D4
#घोषणा   MG_CLKTOP2_HSCLKCTL_CORE_INPUTSEL(x)		((x) << 16)
#घोषणा   MG_CLKTOP2_HSCLKCTL_CORE_INPUTSEL_MASK	(0x1 << 16)
#घोषणा   MG_CLKTOP2_HSCLKCTL_TLINEDRV_CLKSEL(x)	((x) << 14)
#घोषणा   MG_CLKTOP2_HSCLKCTL_TLINEDRV_CLKSEL_MASK	(0x3 << 14)
#घोषणा   MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_MASK		(0x3 << 12)
#घोषणा   MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_2		(0 << 12)
#घोषणा   MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_3		(1 << 12)
#घोषणा   MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_5		(2 << 12)
#घोषणा   MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_7		(3 << 12)
#घोषणा   MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO(x)		((x) << 8)
#घोषणा   MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_SHIFT		8
#घोषणा   MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_MASK		(0xf << 8)
#घोषणा MG_CLKTOP2_HSCLKCTL(tc_port) _MMIO_PORT((tc_port), \
						_MG_CLKTOP2_HSCLKCTL_PORT1, \
						_MG_CLKTOP2_HSCLKCTL_PORT2)

#घोषणा _MG_PLL_DIV0_PORT1				0x168A00
#घोषणा _MG_PLL_DIV0_PORT2				0x169A00
#घोषणा _MG_PLL_DIV0_PORT3				0x16AA00
#घोषणा _MG_PLL_DIV0_PORT4				0x16BA00
#घोषणा   MG_PLL_DIV0_FRACNEN_H				(1 << 30)
#घोषणा   MG_PLL_DIV0_FBDIV_FRAC_MASK			(0x3fffff << 8)
#घोषणा   MG_PLL_DIV0_FBDIV_FRAC_SHIFT			8
#घोषणा   MG_PLL_DIV0_FBDIV_FRAC(x)			((x) << 8)
#घोषणा   MG_PLL_DIV0_FBDIV_INT_MASK			(0xff << 0)
#घोषणा   MG_PLL_DIV0_FBDIV_INT(x)			((x) << 0)
#घोषणा MG_PLL_DIV0(tc_port) _MMIO_PORT((tc_port), _MG_PLL_DIV0_PORT1, \
					_MG_PLL_DIV0_PORT2)

#घोषणा _MG_PLL_DIV1_PORT1				0x168A04
#घोषणा _MG_PLL_DIV1_PORT2				0x169A04
#घोषणा _MG_PLL_DIV1_PORT3				0x16AA04
#घोषणा _MG_PLL_DIV1_PORT4				0x16BA04
#घोषणा   MG_PLL_DIV1_IREF_NDIVRATIO(x)			((x) << 16)
#घोषणा   MG_PLL_DIV1_DITHER_DIV_1			(0 << 12)
#घोषणा   MG_PLL_DIV1_DITHER_DIV_2			(1 << 12)
#घोषणा   MG_PLL_DIV1_DITHER_DIV_4			(2 << 12)
#घोषणा   MG_PLL_DIV1_DITHER_DIV_8			(3 << 12)
#घोषणा   MG_PLL_DIV1_NDIVRATIO(x)			((x) << 4)
#घोषणा   MG_PLL_DIV1_FBPREDIV_MASK			(0xf << 0)
#घोषणा   MG_PLL_DIV1_FBPREDIV(x)			((x) << 0)
#घोषणा MG_PLL_DIV1(tc_port) _MMIO_PORT((tc_port), _MG_PLL_DIV1_PORT1, \
					_MG_PLL_DIV1_PORT2)

#घोषणा _MG_PLL_LF_PORT1				0x168A08
#घोषणा _MG_PLL_LF_PORT2				0x169A08
#घोषणा _MG_PLL_LF_PORT3				0x16AA08
#घोषणा _MG_PLL_LF_PORT4				0x16BA08
#घोषणा   MG_PLL_LF_TDCTARGETCNT(x)			((x) << 24)
#घोषणा   MG_PLL_LF_AFCCNTSEL_256			(0 << 20)
#घोषणा   MG_PLL_LF_AFCCNTSEL_512			(1 << 20)
#घोषणा   MG_PLL_LF_GAINCTRL(x)				((x) << 16)
#घोषणा   MG_PLL_LF_INT_COEFF(x)			((x) << 8)
#घोषणा   MG_PLL_LF_PROP_COEFF(x)			((x) << 0)
#घोषणा MG_PLL_LF(tc_port) _MMIO_PORT((tc_port), _MG_PLL_LF_PORT1, \
				      _MG_PLL_LF_PORT2)

#घोषणा _MG_PLL_FRAC_LOCK_PORT1				0x168A0C
#घोषणा _MG_PLL_FRAC_LOCK_PORT2				0x169A0C
#घोषणा _MG_PLL_FRAC_LOCK_PORT3				0x16AA0C
#घोषणा _MG_PLL_FRAC_LOCK_PORT4				0x16BA0C
#घोषणा   MG_PLL_FRAC_LOCK_TRUELOCK_CRIT_32		(1 << 18)
#घोषणा   MG_PLL_FRAC_LOCK_EARLYLOCK_CRIT_32		(1 << 16)
#घोषणा   MG_PLL_FRAC_LOCK_LOCKTHRESH(x)		((x) << 11)
#घोषणा   MG_PLL_FRAC_LOCK_DCODITHEREN			(1 << 10)
#घोषणा   MG_PLL_FRAC_LOCK_FEEDFWRDCAL_EN		(1 << 8)
#घोषणा   MG_PLL_FRAC_LOCK_FEEDFWRDGAIN(x)		((x) << 0)
#घोषणा MG_PLL_FRAC_LOCK(tc_port) _MMIO_PORT((tc_port), \
					     _MG_PLL_FRAC_LOCK_PORT1, \
					     _MG_PLL_FRAC_LOCK_PORT2)

#घोषणा _MG_PLL_SSC_PORT1				0x168A10
#घोषणा _MG_PLL_SSC_PORT2				0x169A10
#घोषणा _MG_PLL_SSC_PORT3				0x16AA10
#घोषणा _MG_PLL_SSC_PORT4				0x16BA10
#घोषणा   MG_PLL_SSC_EN					(1 << 28)
#घोषणा   MG_PLL_SSC_TYPE(x)				((x) << 26)
#घोषणा   MG_PLL_SSC_STEPLENGTH(x)			((x) << 16)
#घोषणा   MG_PLL_SSC_STEPNUM(x)				((x) << 10)
#घोषणा   MG_PLL_SSC_FLLEN				(1 << 9)
#घोषणा   MG_PLL_SSC_STEPSIZE(x)			((x) << 0)
#घोषणा MG_PLL_SSC(tc_port) _MMIO_PORT((tc_port), _MG_PLL_SSC_PORT1, \
				       _MG_PLL_SSC_PORT2)

#घोषणा _MG_PLL_BIAS_PORT1				0x168A14
#घोषणा _MG_PLL_BIAS_PORT2				0x169A14
#घोषणा _MG_PLL_BIAS_PORT3				0x16AA14
#घोषणा _MG_PLL_BIAS_PORT4				0x16BA14
#घोषणा   MG_PLL_BIAS_BIAS_GB_SEL(x)			((x) << 30)
#घोषणा   MG_PLL_BIAS_BIAS_GB_SEL_MASK			(0x3 << 30)
#घोषणा   MG_PLL_BIAS_INIT_DCOAMP(x)			((x) << 24)
#घोषणा   MG_PLL_BIAS_INIT_DCOAMP_MASK			(0x3f << 24)
#घोषणा   MG_PLL_BIAS_BIAS_BONUS(x)			((x) << 16)
#घोषणा   MG_PLL_BIAS_BIAS_BONUS_MASK			(0xff << 16)
#घोषणा   MG_PLL_BIAS_BIASCAL_EN			(1 << 15)
#घोषणा   MG_PLL_BIAS_CTRIM(x)				((x) << 8)
#घोषणा   MG_PLL_BIAS_CTRIM_MASK			(0x1f << 8)
#घोषणा   MG_PLL_BIAS_VREF_RDAC(x)			((x) << 5)
#घोषणा   MG_PLL_BIAS_VREF_RDAC_MASK			(0x7 << 5)
#घोषणा   MG_PLL_BIAS_IREFTRIM(x)			((x) << 0)
#घोषणा   MG_PLL_BIAS_IREFTRIM_MASK			(0x1f << 0)
#घोषणा MG_PLL_BIAS(tc_port) _MMIO_PORT((tc_port), _MG_PLL_BIAS_PORT1, \
					_MG_PLL_BIAS_PORT2)

#घोषणा _MG_PLL_TDC_COLDST_BIAS_PORT1			0x168A18
#घोषणा _MG_PLL_TDC_COLDST_BIAS_PORT2			0x169A18
#घोषणा _MG_PLL_TDC_COLDST_BIAS_PORT3			0x16AA18
#घोषणा _MG_PLL_TDC_COLDST_BIAS_PORT4			0x16BA18
#घोषणा   MG_PLL_TDC_COLDST_IREFINT_EN			(1 << 27)
#घोषणा   MG_PLL_TDC_COLDST_REFBIAS_START_PULSE_W(x)	((x) << 17)
#घोषणा   MG_PLL_TDC_COLDST_COLDSTART			(1 << 16)
#घोषणा   MG_PLL_TDC_TDCOVCCORR_EN			(1 << 2)
#घोषणा   MG_PLL_TDC_TDCSEL(x)				((x) << 0)
#घोषणा MG_PLL_TDC_COLDST_BIAS(tc_port) _MMIO_PORT((tc_port), \
						   _MG_PLL_TDC_COLDST_BIAS_PORT1, \
						   _MG_PLL_TDC_COLDST_BIAS_PORT2)

#घोषणा _CNL_DPLL0_CFGCR0		0x6C000
#घोषणा _CNL_DPLL1_CFGCR0		0x6C080
#घोषणा  DPLL_CFGCR0_HDMI_MODE		(1 << 30)
#घोषणा  DPLL_CFGCR0_SSC_ENABLE		(1 << 29)
#घोषणा  DPLL_CFGCR0_SSC_ENABLE_ICL	(1 << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_MASK	(0xf << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_2700	(0 << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_1350	(1 << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_810	(2 << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_1620	(3 << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_1080	(4 << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_2160	(5 << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_3240	(6 << 25)
#घोषणा  DPLL_CFGCR0_LINK_RATE_4050	(7 << 25)
#घोषणा  DPLL_CFGCR0_DCO_FRACTION_MASK	(0x7fff << 10)
#घोषणा  DPLL_CFGCR0_DCO_FRACTION_SHIFT	(10)
#घोषणा  DPLL_CFGCR0_DCO_FRACTION(x)	((x) << 10)
#घोषणा  DPLL_CFGCR0_DCO_INTEGER_MASK	(0x3ff)
#घोषणा CNL_DPLL_CFGCR0(pll)		_MMIO_PLL(pll, _CNL_DPLL0_CFGCR0, _CNL_DPLL1_CFGCR0)

#घोषणा _CNL_DPLL0_CFGCR1		0x6C004
#घोषणा _CNL_DPLL1_CFGCR1		0x6C084
#घोषणा  DPLL_CFGCR1_QDIV_RATIO_MASK	(0xff << 10)
#घोषणा  DPLL_CFGCR1_QDIV_RATIO_SHIFT	(10)
#घोषणा  DPLL_CFGCR1_QDIV_RATIO(x)	((x) << 10)
#घोषणा  DPLL_CFGCR1_QDIV_MODE_SHIFT	(9)
#घोषणा  DPLL_CFGCR1_QDIV_MODE(x)	((x) << 9)
#घोषणा  DPLL_CFGCR1_KDIV_MASK		(7 << 6)
#घोषणा  DPLL_CFGCR1_KDIV_SHIFT		(6)
#घोषणा  DPLL_CFGCR1_KDIV(x)		((x) << 6)
#घोषणा  DPLL_CFGCR1_KDIV_1		(1 << 6)
#घोषणा  DPLL_CFGCR1_KDIV_2		(2 << 6)
#घोषणा  DPLL_CFGCR1_KDIV_3		(4 << 6)
#घोषणा  DPLL_CFGCR1_PDIV_MASK		(0xf << 2)
#घोषणा  DPLL_CFGCR1_PDIV_SHIFT		(2)
#घोषणा  DPLL_CFGCR1_PDIV(x)		((x) << 2)
#घोषणा  DPLL_CFGCR1_PDIV_2		(1 << 2)
#घोषणा  DPLL_CFGCR1_PDIV_3		(2 << 2)
#घोषणा  DPLL_CFGCR1_PDIV_5		(4 << 2)
#घोषणा  DPLL_CFGCR1_PDIV_7		(8 << 2)
#घोषणा  DPLL_CFGCR1_CENTRAL_FREQ	(3 << 0)
#घोषणा  DPLL_CFGCR1_CENTRAL_FREQ_8400	(3 << 0)
#घोषणा  TGL_DPLL_CFGCR1_CFSELOVRD_NORMAL_XTAL	(0 << 0)
#घोषणा CNL_DPLL_CFGCR1(pll)		_MMIO_PLL(pll, _CNL_DPLL0_CFGCR1, _CNL_DPLL1_CFGCR1)

#घोषणा _ICL_DPLL0_CFGCR0		0x164000
#घोषणा _ICL_DPLL1_CFGCR0		0x164080
#घोषणा ICL_DPLL_CFGCR0(pll)		_MMIO_PLL(pll, _ICL_DPLL0_CFGCR0, \
						  _ICL_DPLL1_CFGCR0)

#घोषणा _ICL_DPLL0_CFGCR1		0x164004
#घोषणा _ICL_DPLL1_CFGCR1		0x164084
#घोषणा ICL_DPLL_CFGCR1(pll)		_MMIO_PLL(pll, _ICL_DPLL0_CFGCR1, \
						  _ICL_DPLL1_CFGCR1)

#घोषणा _TGL_DPLL0_CFGCR0		0x164284
#घोषणा _TGL_DPLL1_CFGCR0		0x16428C
#घोषणा _TGL_TBTPLL_CFGCR0		0x16429C
#घोषणा TGL_DPLL_CFGCR0(pll)		_MMIO_PLL3(pll, _TGL_DPLL0_CFGCR0, \
						  _TGL_DPLL1_CFGCR0, \
						  _TGL_TBTPLL_CFGCR0)
#घोषणा RKL_DPLL_CFGCR0(pll)		_MMIO_PLL(pll, _TGL_DPLL0_CFGCR0, \
						  _TGL_DPLL1_CFGCR0)

#घोषणा _TGL_DPLL0_CFGCR1		0x164288
#घोषणा _TGL_DPLL1_CFGCR1		0x164290
#घोषणा _TGL_TBTPLL_CFGCR1		0x1642A0
#घोषणा TGL_DPLL_CFGCR1(pll)		_MMIO_PLL3(pll, _TGL_DPLL0_CFGCR1, \
						   _TGL_DPLL1_CFGCR1, \
						   _TGL_TBTPLL_CFGCR1)
#घोषणा RKL_DPLL_CFGCR1(pll)		_MMIO_PLL(pll, _TGL_DPLL0_CFGCR1, \
						  _TGL_DPLL1_CFGCR1)

#घोषणा _DG1_DPLL2_CFGCR0		0x16C284
#घोषणा _DG1_DPLL3_CFGCR0		0x16C28C
#घोषणा DG1_DPLL_CFGCR0(pll)		_MMIO_PLL3(pll, _TGL_DPLL0_CFGCR0, \
						   _TGL_DPLL1_CFGCR0, \
						   _DG1_DPLL2_CFGCR0, \
						   _DG1_DPLL3_CFGCR0)

#घोषणा _DG1_DPLL2_CFGCR1               0x16C288
#घोषणा _DG1_DPLL3_CFGCR1               0x16C290
#घोषणा DG1_DPLL_CFGCR1(pll)            _MMIO_PLL3(pll, _TGL_DPLL0_CFGCR1, \
						   _TGL_DPLL1_CFGCR1, \
						   _DG1_DPLL2_CFGCR1, \
						   _DG1_DPLL3_CFGCR1)

/* For ADL-S DPLL4_CFGCR0/1 are used to control DPLL2 */
#घोषणा _ADLS_DPLL3_CFGCR0		0x1642C0
#घोषणा _ADLS_DPLL4_CFGCR0		0x164294
#घोषणा ADLS_DPLL_CFGCR0(pll)		_MMIO_PLL3(pll, _TGL_DPLL0_CFGCR0, \
						   _TGL_DPLL1_CFGCR0, \
						   _ADLS_DPLL4_CFGCR0, \
						   _ADLS_DPLL3_CFGCR0)

#घोषणा _ADLS_DPLL3_CFGCR1		0x1642C4
#घोषणा _ADLS_DPLL4_CFGCR1		0x164298
#घोषणा ADLS_DPLL_CFGCR1(pll)		_MMIO_PLL3(pll, _TGL_DPLL0_CFGCR1, \
						   _TGL_DPLL1_CFGCR1, \
						   _ADLS_DPLL4_CFGCR1, \
						   _ADLS_DPLL3_CFGCR1)

#घोषणा _DKL_PHY1_BASE			0x168000
#घोषणा _DKL_PHY2_BASE			0x169000
#घोषणा _DKL_PHY3_BASE			0x16A000
#घोषणा _DKL_PHY4_BASE			0x16B000
#घोषणा _DKL_PHY5_BASE			0x16C000
#घोषणा _DKL_PHY6_BASE			0x16D000

/* DEKEL PHY MMIO Address = Phy base + (पूर्णांकernal address & ~index_mask) */
#घोषणा _DKL_PLL_DIV0			0x200
#घोषणा   DKL_PLL_DIV0_INTEG_COEFF(x)	((x) << 16)
#घोषणा   DKL_PLL_DIV0_INTEG_COEFF_MASK	(0x1F << 16)
#घोषणा   DKL_PLL_DIV0_PROP_COEFF(x)	((x) << 12)
#घोषणा   DKL_PLL_DIV0_PROP_COEFF_MASK	(0xF << 12)
#घोषणा   DKL_PLL_DIV0_FBPREDIV_SHIFT   (8)
#घोषणा   DKL_PLL_DIV0_FBPREDIV(x)	((x) << DKL_PLL_DIV0_FBPREDIV_SHIFT)
#घोषणा   DKL_PLL_DIV0_FBPREDIV_MASK	(0xF << DKL_PLL_DIV0_FBPREDIV_SHIFT)
#घोषणा   DKL_PLL_DIV0_FBDIV_INT(x)	((x) << 0)
#घोषणा   DKL_PLL_DIV0_FBDIV_INT_MASK	(0xFF << 0)
#घोषणा DKL_PLL_DIV0(tc_port)		_MMIO(_PORT(tc_port, _DKL_PHY1_BASE, \
						    _DKL_PHY2_BASE) + \
						    _DKL_PLL_DIV0)

#घोषणा _DKL_PLL_DIV1				0x204
#घोषणा   DKL_PLL_DIV1_IREF_TRIM(x)		((x) << 16)
#घोषणा   DKL_PLL_DIV1_IREF_TRIM_MASK		(0x1F << 16)
#घोषणा   DKL_PLL_DIV1_TDC_TARGET_CNT(x)	((x) << 0)
#घोषणा   DKL_PLL_DIV1_TDC_TARGET_CNT_MASK	(0xFF << 0)
#घोषणा DKL_PLL_DIV1(tc_port)		_MMIO(_PORT(tc_port, _DKL_PHY1_BASE, \
						    _DKL_PHY2_BASE) + \
						    _DKL_PLL_DIV1)

#घोषणा _DKL_PLL_SSC				0x210
#घोषणा   DKL_PLL_SSC_IREF_NDIV_RATIO(x)	((x) << 29)
#घोषणा   DKL_PLL_SSC_IREF_NDIV_RATIO_MASK	(0x7 << 29)
#घोषणा   DKL_PLL_SSC_STEP_LEN(x)		((x) << 16)
#घोषणा   DKL_PLL_SSC_STEP_LEN_MASK		(0xFF << 16)
#घोषणा   DKL_PLL_SSC_STEP_NUM(x)		((x) << 11)
#घोषणा   DKL_PLL_SSC_STEP_NUM_MASK		(0x7 << 11)
#घोषणा   DKL_PLL_SSC_EN			(1 << 9)
#घोषणा DKL_PLL_SSC(tc_port)		_MMIO(_PORT(tc_port, _DKL_PHY1_BASE, \
						    _DKL_PHY2_BASE) + \
						    _DKL_PLL_SSC)

#घोषणा _DKL_PLL_BIAS			0x214
#घोषणा   DKL_PLL_BIAS_FRAC_EN_H	(1 << 30)
#घोषणा   DKL_PLL_BIAS_FBDIV_SHIFT	(8)
#घोषणा   DKL_PLL_BIAS_FBDIV_FRAC(x)	((x) << DKL_PLL_BIAS_FBDIV_SHIFT)
#घोषणा   DKL_PLL_BIAS_FBDIV_FRAC_MASK	(0x3FFFFF << DKL_PLL_BIAS_FBDIV_SHIFT)
#घोषणा DKL_PLL_BIAS(tc_port)		_MMIO(_PORT(tc_port, _DKL_PHY1_BASE, \
						    _DKL_PHY2_BASE) + \
						    _DKL_PLL_BIAS)

#घोषणा _DKL_PLL_TDC_COLDST_BIAS		0x218
#घोषणा   DKL_PLL_TDC_SSC_STEP_SIZE(x)		((x) << 8)
#घोषणा   DKL_PLL_TDC_SSC_STEP_SIZE_MASK	(0xFF << 8)
#घोषणा   DKL_PLL_TDC_FEED_FWD_GAIN(x)		((x) << 0)
#घोषणा   DKL_PLL_TDC_FEED_FWD_GAIN_MASK	(0xFF << 0)
#घोषणा DKL_PLL_TDC_COLDST_BIAS(tc_port) _MMIO(_PORT(tc_port, \
						     _DKL_PHY1_BASE, \
						     _DKL_PHY2_BASE) + \
						     _DKL_PLL_TDC_COLDST_BIAS)

#घोषणा _DKL_REFCLKIN_CTL		0x12C
/* Bits are the same as MG_REFCLKIN_CTL */
#घोषणा DKL_REFCLKIN_CTL(tc_port)	_MMIO(_PORT(tc_port, \
						    _DKL_PHY1_BASE, \
						    _DKL_PHY2_BASE) + \
					      _DKL_REFCLKIN_CTL)

#घोषणा _DKL_CLKTOP2_HSCLKCTL		0xD4
/* Bits are the same as MG_CLKTOP2_HSCLKCTL */
#घोषणा DKL_CLKTOP2_HSCLKCTL(tc_port)	_MMIO(_PORT(tc_port, \
						    _DKL_PHY1_BASE, \
						    _DKL_PHY2_BASE) + \
					      _DKL_CLKTOP2_HSCLKCTL)

#घोषणा _DKL_CLKTOP2_CORECLKCTL1		0xD8
/* Bits are the same as MG_CLKTOP2_CORECLKCTL1 */
#घोषणा DKL_CLKTOP2_CORECLKCTL1(tc_port)	_MMIO(_PORT(tc_port, \
							    _DKL_PHY1_BASE, \
							    _DKL_PHY2_BASE) + \
						      _DKL_CLKTOP2_CORECLKCTL1)

#घोषणा _DKL_TX_DPCNTL0				0x2C0
#घोषणा  DKL_TX_PRESHOOT_COEFF(x)			((x) << 13)
#घोषणा  DKL_TX_PRESHOOT_COEFF_MASK			(0x1f << 13)
#घोषणा  DKL_TX_DE_EMPHASIS_COEFF(x)		((x) << 8)
#घोषणा  DKL_TX_DE_EMPAHSIS_COEFF_MASK		(0x1f << 8)
#घोषणा  DKL_TX_VSWING_CONTROL(x)			((x) << 0)
#घोषणा  DKL_TX_VSWING_CONTROL_MASK			(0x7 << 0)
#घोषणा DKL_TX_DPCNTL0(tc_port) _MMIO(_PORT(tc_port, \
						     _DKL_PHY1_BASE, \
						     _DKL_PHY2_BASE) + \
						     _DKL_TX_DPCNTL0)

#घोषणा _DKL_TX_DPCNTL1				0x2C4
/* Bits are the same as DKL_TX_DPCNTRL0 */
#घोषणा DKL_TX_DPCNTL1(tc_port) _MMIO(_PORT(tc_port, \
						     _DKL_PHY1_BASE, \
						     _DKL_PHY2_BASE) + \
						     _DKL_TX_DPCNTL1)

#घोषणा _DKL_TX_DPCNTL2				0x2C8
#घोषणा  DKL_TX_DP20BITMODE				(1 << 2)
#घोषणा DKL_TX_DPCNTL2(tc_port) _MMIO(_PORT(tc_port, \
						     _DKL_PHY1_BASE, \
						     _DKL_PHY2_BASE) + \
						     _DKL_TX_DPCNTL2)

#घोषणा _DKL_TX_FW_CALIB				0x2F8
#घोषणा  DKL_TX_CFG_DISABLE_WAIT_INIT			(1 << 7)
#घोषणा DKL_TX_FW_CALIB(tc_port) _MMIO(_PORT(tc_port, \
						     _DKL_PHY1_BASE, \
						     _DKL_PHY2_BASE) + \
						     _DKL_TX_FW_CALIB)

#घोषणा _DKL_TX_PMD_LANE_SUS				0xD00
#घोषणा DKL_TX_PMD_LANE_SUS(tc_port) _MMIO(_PORT(tc_port, \
							  _DKL_PHY1_BASE, \
							  _DKL_PHY2_BASE) + \
							  _DKL_TX_PMD_LANE_SUS)

#घोषणा _DKL_TX_DW17					0xDC4
#घोषणा DKL_TX_DW17(tc_port) _MMIO(_PORT(tc_port, \
						     _DKL_PHY1_BASE, \
						     _DKL_PHY2_BASE) + \
						     _DKL_TX_DW17)

#घोषणा _DKL_TX_DW18					0xDC8
#घोषणा DKL_TX_DW18(tc_port) _MMIO(_PORT(tc_port, \
						     _DKL_PHY1_BASE, \
						     _DKL_PHY2_BASE) + \
						     _DKL_TX_DW18)

#घोषणा _DKL_DP_MODE					0xA0
#घोषणा DKL_DP_MODE(tc_port) _MMIO(_PORT(tc_port, \
						     _DKL_PHY1_BASE, \
						     _DKL_PHY2_BASE) + \
						     _DKL_DP_MODE)

#घोषणा _DKL_CMN_UC_DW27			0x36C
#घोषणा  DKL_CMN_UC_DW27_UC_HEALTH		(0x1 << 15)
#घोषणा DKL_CMN_UC_DW_27(tc_port)		_MMIO(_PORT(tc_port, \
							    _DKL_PHY1_BASE, \
							    _DKL_PHY2_BASE) + \
							    _DKL_CMN_UC_DW27)

/*
 * Each Dekel PHY is addressed through a 4KB aperture. Each PHY has more than
 * 4KB of रेजिस्टर space, so a separate index is programmed in HIP_INDEX_REG0
 * or HIP_INDEX_REG1, based on the port number, to set the upper 2 address
 * bits that poपूर्णांक the 4KB winकरोw पूर्णांकo the full PHY रेजिस्टर space.
 */
#घोषणा _HIP_INDEX_REG0			0x1010A0
#घोषणा _HIP_INDEX_REG1			0x1010A4
#घोषणा HIP_INDEX_REG(tc_port)		_MMIO((tc_port) < 4 ? _HIP_INDEX_REG0 \
					      : _HIP_INDEX_REG1)
#घोषणा _HIP_INDEX_SHIFT(tc_port)	(8 * ((tc_port) % 4))
#घोषणा HIP_INDEX_VAL(tc_port, val)	((val) << _HIP_INDEX_SHIFT(tc_port))

/* BXT display engine PLL */
#घोषणा BXT_DE_PLL_CTL			_MMIO(0x6d000)
#घोषणा   BXT_DE_PLL_RATIO(x)		(x)	/* अणु60,65,100पूर्ण * 19.2MHz */
#घोषणा   BXT_DE_PLL_RATIO_MASK		0xff

#घोषणा BXT_DE_PLL_ENABLE		_MMIO(0x46070)
#घोषणा   BXT_DE_PLL_PLL_ENABLE		(1 << 31)
#घोषणा   BXT_DE_PLL_LOCK		(1 << 30)
#घोषणा   CNL_CDCLK_PLL_RATIO(x)	(x)
#घोषणा   CNL_CDCLK_PLL_RATIO_MASK	0xff

/* GEN9 DC */
#घोषणा DC_STATE_EN			_MMIO(0x45504)
#घोषणा  DC_STATE_DISABLE		0
#घोषणा  DC_STATE_EN_DC3CO		REG_BIT(30)
#घोषणा  DC_STATE_DC3CO_STATUS		REG_BIT(29)
#घोषणा  DC_STATE_EN_UPTO_DC5		(1 << 0)
#घोषणा  DC_STATE_EN_DC9		(1 << 3)
#घोषणा  DC_STATE_EN_UPTO_DC6		(2 << 0)
#घोषणा  DC_STATE_EN_UPTO_DC5_DC6_MASK   0x3

#घोषणा  DC_STATE_DEBUG                  _MMIO(0x45520)
#घोषणा  DC_STATE_DEBUG_MASK_CORES	(1 << 0)
#घोषणा  DC_STATE_DEBUG_MASK_MEMORY_UP	(1 << 1)

#घोषणा BXT_P_CR_MC_BIOS_REQ_0_0_0	_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x7114)
#घोषणा  BXT_REQ_DATA_MASK			0x3F
#घोषणा  BXT_DRAM_CHANNEL_ACTIVE_SHIFT		12
#घोषणा  BXT_DRAM_CHANNEL_ACTIVE_MASK		(0xF << 12)
#घोषणा  BXT_MEMORY_FREQ_MULTIPLIER_HZ		133333333

#घोषणा BXT_D_CR_DRP0_DUNIT8			0x1000
#घोषणा BXT_D_CR_DRP0_DUNIT9			0x1200
#घोषणा  BXT_D_CR_DRP0_DUNIT_START		8
#घोषणा  BXT_D_CR_DRP0_DUNIT_END		11
#घोषणा BXT_D_CR_DRP0_DUNIT(x)	_MMIO(MCHBAR_MIRROR_BASE_SNB + \
				      _PICK_EVEN((x) - 8, BXT_D_CR_DRP0_DUNIT8,\
						 BXT_D_CR_DRP0_DUNIT9))
#घोषणा  BXT_DRAM_RANK_MASK			0x3
#घोषणा  BXT_DRAM_RANK_SINGLE			0x1
#घोषणा  BXT_DRAM_RANK_DUAL			0x3
#घोषणा  BXT_DRAM_WIDTH_MASK			(0x3 << 4)
#घोषणा  BXT_DRAM_WIDTH_SHIFT			4
#घोषणा  BXT_DRAM_WIDTH_X8			(0x0 << 4)
#घोषणा  BXT_DRAM_WIDTH_X16			(0x1 << 4)
#घोषणा  BXT_DRAM_WIDTH_X32			(0x2 << 4)
#घोषणा  BXT_DRAM_WIDTH_X64			(0x3 << 4)
#घोषणा  BXT_DRAM_SIZE_MASK			(0x7 << 6)
#घोषणा  BXT_DRAM_SIZE_SHIFT			6
#घोषणा  BXT_DRAM_SIZE_4GBIT			(0x0 << 6)
#घोषणा  BXT_DRAM_SIZE_6GBIT			(0x1 << 6)
#घोषणा  BXT_DRAM_SIZE_8GBIT			(0x2 << 6)
#घोषणा  BXT_DRAM_SIZE_12GBIT			(0x3 << 6)
#घोषणा  BXT_DRAM_SIZE_16GBIT			(0x4 << 6)
#घोषणा  BXT_DRAM_TYPE_MASK			(0x7 << 22)
#घोषणा  BXT_DRAM_TYPE_SHIFT			22
#घोषणा  BXT_DRAM_TYPE_DDR3			(0x0 << 22)
#घोषणा  BXT_DRAM_TYPE_LPDDR3			(0x1 << 22)
#घोषणा  BXT_DRAM_TYPE_LPDDR4			(0x2 << 22)
#घोषणा  BXT_DRAM_TYPE_DDR4			(0x4 << 22)

#घोषणा SKL_MEMORY_FREQ_MULTIPLIER_HZ		266666666
#घोषणा SKL_MC_BIOS_DATA_0_0_0_MCHBAR_PCU	_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5E04)
#घोषणा  SKL_REQ_DATA_MASK			(0xF << 0)

#घोषणा SKL_MAD_INTER_CHANNEL_0_0_0_MCHBAR_MCMAIN _MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5000)
#घोषणा  SKL_DRAM_DDR_TYPE_MASK			(0x3 << 0)
#घोषणा  SKL_DRAM_DDR_TYPE_DDR4			(0 << 0)
#घोषणा  SKL_DRAM_DDR_TYPE_DDR3			(1 << 0)
#घोषणा  SKL_DRAM_DDR_TYPE_LPDDR3		(2 << 0)
#घोषणा  SKL_DRAM_DDR_TYPE_LPDDR4		(3 << 0)

#घोषणा SKL_MAD_DIMM_CH0_0_0_0_MCHBAR_MCMAIN	_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x500C)
#घोषणा SKL_MAD_DIMM_CH1_0_0_0_MCHBAR_MCMAIN	_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5010)
#घोषणा  SKL_DRAM_S_SHIFT			16
#घोषणा  SKL_DRAM_SIZE_MASK			0x3F
#घोषणा  SKL_DRAM_WIDTH_MASK			(0x3 << 8)
#घोषणा  SKL_DRAM_WIDTH_SHIFT			8
#घोषणा  SKL_DRAM_WIDTH_X8			(0x0 << 8)
#घोषणा  SKL_DRAM_WIDTH_X16			(0x1 << 8)
#घोषणा  SKL_DRAM_WIDTH_X32			(0x2 << 8)
#घोषणा  SKL_DRAM_RANK_MASK			(0x1 << 10)
#घोषणा  SKL_DRAM_RANK_SHIFT			10
#घोषणा  SKL_DRAM_RANK_1			(0x0 << 10)
#घोषणा  SKL_DRAM_RANK_2			(0x1 << 10)
#घोषणा  SKL_DRAM_RANK_MASK			(0x1 << 10)
#घोषणा  CNL_DRAM_SIZE_MASK			0x7F
#घोषणा  CNL_DRAM_WIDTH_MASK			(0x3 << 7)
#घोषणा  CNL_DRAM_WIDTH_SHIFT			7
#घोषणा  CNL_DRAM_WIDTH_X8			(0x0 << 7)
#घोषणा  CNL_DRAM_WIDTH_X16			(0x1 << 7)
#घोषणा  CNL_DRAM_WIDTH_X32			(0x2 << 7)
#घोषणा  CNL_DRAM_RANK_MASK			(0x3 << 9)
#घोषणा  CNL_DRAM_RANK_SHIFT			9
#घोषणा  CNL_DRAM_RANK_1			(0x0 << 9)
#घोषणा  CNL_DRAM_RANK_2			(0x1 << 9)
#घोषणा  CNL_DRAM_RANK_3			(0x2 << 9)
#घोषणा  CNL_DRAM_RANK_4			(0x3 << 9)

/*
 * Please see hsw_पढ़ो_dcomp() and hsw_ग_लिखो_dcomp() beक्रमe using this रेजिस्टर,
 * since on HSW we can't ग_लिखो to it using पूर्णांकel_uncore_ग_लिखो.
 */
#घोषणा D_COMP_HSW			_MMIO(MCHBAR_MIRROR_BASE_SNB + 0x5F0C)
#घोषणा D_COMP_BDW			_MMIO(0x138144)
#घोषणा  D_COMP_RCOMP_IN_PROGRESS	(1 << 9)
#घोषणा  D_COMP_COMP_FORCE		(1 << 8)
#घोषणा  D_COMP_COMP_DISABLE		(1 << 0)

/* Pipe WM_LINETIME - watermark line समय */
#घोषणा _WM_LINETIME_A		0x45270
#घोषणा _WM_LINETIME_B		0x45274
#घोषणा WM_LINETIME(pipe) _MMIO_PIPE(pipe, _WM_LINETIME_A, _WM_LINETIME_B)
#घोषणा  HSW_LINETIME_MASK	REG_GENMASK(8, 0)
#घोषणा  HSW_LINETIME(x)	REG_FIELD_PREP(HSW_LINETIME_MASK, (x))
#घोषणा  HSW_IPS_LINETIME_MASK	REG_GENMASK(24, 16)
#घोषणा  HSW_IPS_LINETIME(x)	REG_FIELD_PREP(HSW_IPS_LINETIME_MASK, (x))

/* SFUSE_STRAP */
#घोषणा SFUSE_STRAP			_MMIO(0xc2014)
#घोषणा  SFUSE_STRAP_FUSE_LOCK		(1 << 13)
#घोषणा  SFUSE_STRAP_RAW_FREQUENCY	(1 << 8)
#घोषणा  SFUSE_STRAP_DISPLAY_DISABLED	(1 << 7)
#घोषणा  SFUSE_STRAP_CRT_DISABLED	(1 << 6)
#घोषणा  SFUSE_STRAP_DDIF_DETECTED	(1 << 3)
#घोषणा  SFUSE_STRAP_DDIB_DETECTED	(1 << 2)
#घोषणा  SFUSE_STRAP_DDIC_DETECTED	(1 << 1)
#घोषणा  SFUSE_STRAP_DDID_DETECTED	(1 << 0)

#घोषणा WM_MISC				_MMIO(0x45260)
#घोषणा  WM_MISC_DATA_PARTITION_5_6	(1 << 0)

#घोषणा WM_DBG				_MMIO(0x45280)
#घोषणा  WM_DBG_DISALLOW_MULTIPLE_LP	(1 << 0)
#घोषणा  WM_DBG_DISALLOW_MAXFIFO	(1 << 1)
#घोषणा  WM_DBG_DISALLOW_SPRITE		(1 << 2)

/* pipe CSC */
#घोषणा _PIPE_A_CSC_COEFF_RY_GY	0x49010
#घोषणा _PIPE_A_CSC_COEFF_BY	0x49014
#घोषणा _PIPE_A_CSC_COEFF_RU_GU	0x49018
#घोषणा _PIPE_A_CSC_COEFF_BU	0x4901c
#घोषणा _PIPE_A_CSC_COEFF_RV_GV	0x49020
#घोषणा _PIPE_A_CSC_COEFF_BV	0x49024

#घोषणा _PIPE_A_CSC_MODE	0x49028
#घोषणा  ICL_CSC_ENABLE			(1 << 31) /* icl+ */
#घोषणा  ICL_OUTPUT_CSC_ENABLE		(1 << 30) /* icl+ */
#घोषणा  CSC_BLACK_SCREEN_OFFSET	(1 << 2) /* ilk/snb */
#घोषणा  CSC_POSITION_BEFORE_GAMMA	(1 << 1) /* pre-glk */
#घोषणा  CSC_MODE_YUV_TO_RGB		(1 << 0) /* ilk/snb */

#घोषणा _PIPE_A_CSC_PRखातापूर्णF_HI	0x49030
#घोषणा _PIPE_A_CSC_PRखातापूर्णF_ME	0x49034
#घोषणा _PIPE_A_CSC_PRखातापूर्णF_LO	0x49038
#घोषणा _PIPE_A_CSC_POSTOFF_HI	0x49040
#घोषणा _PIPE_A_CSC_POSTOFF_ME	0x49044
#घोषणा _PIPE_A_CSC_POSTOFF_LO	0x49048

#घोषणा _PIPE_B_CSC_COEFF_RY_GY	0x49110
#घोषणा _PIPE_B_CSC_COEFF_BY	0x49114
#घोषणा _PIPE_B_CSC_COEFF_RU_GU	0x49118
#घोषणा _PIPE_B_CSC_COEFF_BU	0x4911c
#घोषणा _PIPE_B_CSC_COEFF_RV_GV	0x49120
#घोषणा _PIPE_B_CSC_COEFF_BV	0x49124
#घोषणा _PIPE_B_CSC_MODE	0x49128
#घोषणा _PIPE_B_CSC_PRखातापूर्णF_HI	0x49130
#घोषणा _PIPE_B_CSC_PRखातापूर्णF_ME	0x49134
#घोषणा _PIPE_B_CSC_PRखातापूर्णF_LO	0x49138
#घोषणा _PIPE_B_CSC_POSTOFF_HI	0x49140
#घोषणा _PIPE_B_CSC_POSTOFF_ME	0x49144
#घोषणा _PIPE_B_CSC_POSTOFF_LO	0x49148

#घोषणा PIPE_CSC_COEFF_RY_GY(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_COEFF_RY_GY, _PIPE_B_CSC_COEFF_RY_GY)
#घोषणा PIPE_CSC_COEFF_BY(pipe)		_MMIO_PIPE(pipe, _PIPE_A_CSC_COEFF_BY, _PIPE_B_CSC_COEFF_BY)
#घोषणा PIPE_CSC_COEFF_RU_GU(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_COEFF_RU_GU, _PIPE_B_CSC_COEFF_RU_GU)
#घोषणा PIPE_CSC_COEFF_BU(pipe)		_MMIO_PIPE(pipe, _PIPE_A_CSC_COEFF_BU, _PIPE_B_CSC_COEFF_BU)
#घोषणा PIPE_CSC_COEFF_RV_GV(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_COEFF_RV_GV, _PIPE_B_CSC_COEFF_RV_GV)
#घोषणा PIPE_CSC_COEFF_BV(pipe)		_MMIO_PIPE(pipe, _PIPE_A_CSC_COEFF_BV, _PIPE_B_CSC_COEFF_BV)
#घोषणा PIPE_CSC_MODE(pipe)		_MMIO_PIPE(pipe, _PIPE_A_CSC_MODE, _PIPE_B_CSC_MODE)
#घोषणा PIPE_CSC_PRखातापूर्णF_HI(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_PRखातापूर्णF_HI, _PIPE_B_CSC_PRखातापूर्णF_HI)
#घोषणा PIPE_CSC_PRखातापूर्णF_ME(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_PRखातापूर्णF_ME, _PIPE_B_CSC_PRखातापूर्णF_ME)
#घोषणा PIPE_CSC_PRखातापूर्णF_LO(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_PRखातापूर्णF_LO, _PIPE_B_CSC_PRखातापूर्णF_LO)
#घोषणा PIPE_CSC_POSTOFF_HI(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_POSTOFF_HI, _PIPE_B_CSC_POSTOFF_HI)
#घोषणा PIPE_CSC_POSTOFF_ME(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_POSTOFF_ME, _PIPE_B_CSC_POSTOFF_ME)
#घोषणा PIPE_CSC_POSTOFF_LO(pipe)	_MMIO_PIPE(pipe, _PIPE_A_CSC_POSTOFF_LO, _PIPE_B_CSC_POSTOFF_LO)

/* Pipe Output CSC */
#घोषणा _PIPE_A_OUTPUT_CSC_COEFF_RY_GY	0x49050
#घोषणा _PIPE_A_OUTPUT_CSC_COEFF_BY	0x49054
#घोषणा _PIPE_A_OUTPUT_CSC_COEFF_RU_GU	0x49058
#घोषणा _PIPE_A_OUTPUT_CSC_COEFF_BU	0x4905c
#घोषणा _PIPE_A_OUTPUT_CSC_COEFF_RV_GV	0x49060
#घोषणा _PIPE_A_OUTPUT_CSC_COEFF_BV	0x49064
#घोषणा _PIPE_A_OUTPUT_CSC_PRखातापूर्णF_HI	0x49068
#घोषणा _PIPE_A_OUTPUT_CSC_PRखातापूर्णF_ME	0x4906c
#घोषणा _PIPE_A_OUTPUT_CSC_PRखातापूर्णF_LO	0x49070
#घोषणा _PIPE_A_OUTPUT_CSC_POSTOFF_HI	0x49074
#घोषणा _PIPE_A_OUTPUT_CSC_POSTOFF_ME	0x49078
#घोषणा _PIPE_A_OUTPUT_CSC_POSTOFF_LO	0x4907c

#घोषणा _PIPE_B_OUTPUT_CSC_COEFF_RY_GY	0x49150
#घोषणा _PIPE_B_OUTPUT_CSC_COEFF_BY	0x49154
#घोषणा _PIPE_B_OUTPUT_CSC_COEFF_RU_GU	0x49158
#घोषणा _PIPE_B_OUTPUT_CSC_COEFF_BU	0x4915c
#घोषणा _PIPE_B_OUTPUT_CSC_COEFF_RV_GV	0x49160
#घोषणा _PIPE_B_OUTPUT_CSC_COEFF_BV	0x49164
#घोषणा _PIPE_B_OUTPUT_CSC_PRखातापूर्णF_HI	0x49168
#घोषणा _PIPE_B_OUTPUT_CSC_PRखातापूर्णF_ME	0x4916c
#घोषणा _PIPE_B_OUTPUT_CSC_PRखातापूर्णF_LO	0x49170
#घोषणा _PIPE_B_OUTPUT_CSC_POSTOFF_HI	0x49174
#घोषणा _PIPE_B_OUTPUT_CSC_POSTOFF_ME	0x49178
#घोषणा _PIPE_B_OUTPUT_CSC_POSTOFF_LO	0x4917c

#घोषणा PIPE_CSC_OUTPUT_COEFF_RY_GY(pipe)	_MMIO_PIPE(pipe,\
							   _PIPE_A_OUTPUT_CSC_COEFF_RY_GY,\
							   _PIPE_B_OUTPUT_CSC_COEFF_RY_GY)
#घोषणा PIPE_CSC_OUTPUT_COEFF_BY(pipe)		_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_COEFF_BY, \
							   _PIPE_B_OUTPUT_CSC_COEFF_BY)
#घोषणा PIPE_CSC_OUTPUT_COEFF_RU_GU(pipe)	_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_COEFF_RU_GU, \
							   _PIPE_B_OUTPUT_CSC_COEFF_RU_GU)
#घोषणा PIPE_CSC_OUTPUT_COEFF_BU(pipe)		_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_COEFF_BU, \
							   _PIPE_B_OUTPUT_CSC_COEFF_BU)
#घोषणा PIPE_CSC_OUTPUT_COEFF_RV_GV(pipe)	_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_COEFF_RV_GV, \
							   _PIPE_B_OUTPUT_CSC_COEFF_RV_GV)
#घोषणा PIPE_CSC_OUTPUT_COEFF_BV(pipe)		_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_COEFF_BV, \
							   _PIPE_B_OUTPUT_CSC_COEFF_BV)
#घोषणा PIPE_CSC_OUTPUT_PRखातापूर्णF_HI(pipe)		_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_PRखातापूर्णF_HI, \
							   _PIPE_B_OUTPUT_CSC_PRखातापूर्णF_HI)
#घोषणा PIPE_CSC_OUTPUT_PRखातापूर्णF_ME(pipe)		_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_PRखातापूर्णF_ME, \
							   _PIPE_B_OUTPUT_CSC_PRखातापूर्णF_ME)
#घोषणा PIPE_CSC_OUTPUT_PRखातापूर्णF_LO(pipe)		_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_PRखातापूर्णF_LO, \
							   _PIPE_B_OUTPUT_CSC_PRखातापूर्णF_LO)
#घोषणा PIPE_CSC_OUTPUT_POSTOFF_HI(pipe)	_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_POSTOFF_HI, \
							   _PIPE_B_OUTPUT_CSC_POSTOFF_HI)
#घोषणा PIPE_CSC_OUTPUT_POSTOFF_ME(pipe)	_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_POSTOFF_ME, \
							   _PIPE_B_OUTPUT_CSC_POSTOFF_ME)
#घोषणा PIPE_CSC_OUTPUT_POSTOFF_LO(pipe)	_MMIO_PIPE(pipe, \
							   _PIPE_A_OUTPUT_CSC_POSTOFF_LO, \
							   _PIPE_B_OUTPUT_CSC_POSTOFF_LO)

/* pipe degamma/gamma LUTs on IVB+ */
#घोषणा _PAL_PREC_INDEX_A	0x4A400
#घोषणा _PAL_PREC_INDEX_B	0x4AC00
#घोषणा _PAL_PREC_INDEX_C	0x4B400
#घोषणा   PAL_PREC_10_12_BIT		(0 << 31)
#घोषणा   PAL_PREC_SPLIT_MODE		(1 << 31)
#घोषणा   PAL_PREC_AUTO_INCREMENT	(1 << 15)
#घोषणा   PAL_PREC_INDEX_VALUE_MASK	(0x3ff << 0)
#घोषणा   PAL_PREC_INDEX_VALUE(x)	((x) << 0)
#घोषणा _PAL_PREC_DATA_A	0x4A404
#घोषणा _PAL_PREC_DATA_B	0x4AC04
#घोषणा _PAL_PREC_DATA_C	0x4B404
#घोषणा _PAL_PREC_GC_MAX_A	0x4A410
#घोषणा _PAL_PREC_GC_MAX_B	0x4AC10
#घोषणा _PAL_PREC_GC_MAX_C	0x4B410
#घोषणा   PREC_PAL_DATA_RED_MASK	REG_GENMASK(29, 20)
#घोषणा   PREC_PAL_DATA_GREEN_MASK	REG_GENMASK(19, 10)
#घोषणा   PREC_PAL_DATA_BLUE_MASK	REG_GENMASK(9, 0)
#घोषणा _PAL_PREC_EXT_GC_MAX_A	0x4A420
#घोषणा _PAL_PREC_EXT_GC_MAX_B	0x4AC20
#घोषणा _PAL_PREC_EXT_GC_MAX_C	0x4B420
#घोषणा _PAL_PREC_EXT2_GC_MAX_A	0x4A430
#घोषणा _PAL_PREC_EXT2_GC_MAX_B	0x4AC30
#घोषणा _PAL_PREC_EXT2_GC_MAX_C	0x4B430

#घोषणा PREC_PAL_INDEX(pipe)		_MMIO_PIPE(pipe, _PAL_PREC_INDEX_A, _PAL_PREC_INDEX_B)
#घोषणा PREC_PAL_DATA(pipe)		_MMIO_PIPE(pipe, _PAL_PREC_DATA_A, _PAL_PREC_DATA_B)
#घोषणा PREC_PAL_GC_MAX(pipe, i)	_MMIO(_PIPE(pipe, _PAL_PREC_GC_MAX_A, _PAL_PREC_GC_MAX_B) + (i) * 4)
#घोषणा PREC_PAL_EXT_GC_MAX(pipe, i)	_MMIO(_PIPE(pipe, _PAL_PREC_EXT_GC_MAX_A, _PAL_PREC_EXT_GC_MAX_B) + (i) * 4)
#घोषणा PREC_PAL_EXT2_GC_MAX(pipe, i)	_MMIO(_PIPE(pipe, _PAL_PREC_EXT2_GC_MAX_A, _PAL_PREC_EXT2_GC_MAX_B) + (i) * 4)

#घोषणा _PRE_CSC_GAMC_INDEX_A	0x4A484
#घोषणा _PRE_CSC_GAMC_INDEX_B	0x4AC84
#घोषणा _PRE_CSC_GAMC_INDEX_C	0x4B484
#घोषणा   PRE_CSC_GAMC_AUTO_INCREMENT	(1 << 10)
#घोषणा _PRE_CSC_GAMC_DATA_A	0x4A488
#घोषणा _PRE_CSC_GAMC_DATA_B	0x4AC88
#घोषणा _PRE_CSC_GAMC_DATA_C	0x4B488

#घोषणा PRE_CSC_GAMC_INDEX(pipe)	_MMIO_PIPE(pipe, _PRE_CSC_GAMC_INDEX_A, _PRE_CSC_GAMC_INDEX_B)
#घोषणा PRE_CSC_GAMC_DATA(pipe)		_MMIO_PIPE(pipe, _PRE_CSC_GAMC_DATA_A, _PRE_CSC_GAMC_DATA_B)

/* ICL Multi segmented gamma */
#घोषणा _PAL_PREC_MULTI_SEG_INDEX_A	0x4A408
#घोषणा _PAL_PREC_MULTI_SEG_INDEX_B	0x4AC08
#घोषणा  PAL_PREC_MULTI_SEGMENT_AUTO_INCREMENT		REG_BIT(15)
#घोषणा  PAL_PREC_MULTI_SEGMENT_INDEX_VALUE_MASK	REG_GENMASK(4, 0)

#घोषणा _PAL_PREC_MULTI_SEG_DATA_A	0x4A40C
#घोषणा _PAL_PREC_MULTI_SEG_DATA_B	0x4AC0C
#घोषणा  PAL_PREC_MULTI_SEG_RED_LDW_MASK   REG_GENMASK(29, 24)
#घोषणा  PAL_PREC_MULTI_SEG_RED_UDW_MASK   REG_GENMASK(29, 20)
#घोषणा  PAL_PREC_MULTI_SEG_GREEN_LDW_MASK REG_GENMASK(19, 14)
#घोषणा  PAL_PREC_MULTI_SEG_GREEN_UDW_MASK REG_GENMASK(19, 10)
#घोषणा  PAL_PREC_MULTI_SEG_BLUE_LDW_MASK  REG_GENMASK(9, 4)
#घोषणा  PAL_PREC_MULTI_SEG_BLUE_UDW_MASK  REG_GENMASK(9, 0)

#घोषणा PREC_PAL_MULTI_SEG_INDEX(pipe)	_MMIO_PIPE(pipe, \
					_PAL_PREC_MULTI_SEG_INDEX_A, \
					_PAL_PREC_MULTI_SEG_INDEX_B)
#घोषणा PREC_PAL_MULTI_SEG_DATA(pipe)	_MMIO_PIPE(pipe, \
					_PAL_PREC_MULTI_SEG_DATA_A, \
					_PAL_PREC_MULTI_SEG_DATA_B)

/* pipe CSC & degamma/gamma LUTs on CHV */
#घोषणा _CGM_PIPE_A_CSC_COEFF01	(VLV_DISPLAY_BASE + 0x67900)
#घोषणा _CGM_PIPE_A_CSC_COEFF23	(VLV_DISPLAY_BASE + 0x67904)
#घोषणा _CGM_PIPE_A_CSC_COEFF45	(VLV_DISPLAY_BASE + 0x67908)
#घोषणा _CGM_PIPE_A_CSC_COEFF67	(VLV_DISPLAY_BASE + 0x6790C)
#घोषणा _CGM_PIPE_A_CSC_COEFF8	(VLV_DISPLAY_BASE + 0x67910)
#घोषणा _CGM_PIPE_A_DEGAMMA	(VLV_DISPLAY_BASE + 0x66000)
#घोषणा   CGM_PIPE_DEGAMMA_RED_MASK	REG_GENMASK(13, 0)
#घोषणा   CGM_PIPE_DEGAMMA_GREEN_MASK	REG_GENMASK(29, 16)
#घोषणा   CGM_PIPE_DEGAMMA_BLUE_MASK	REG_GENMASK(13, 0)
#घोषणा _CGM_PIPE_A_GAMMA	(VLV_DISPLAY_BASE + 0x67000)
#घोषणा   CGM_PIPE_GAMMA_RED_MASK	REG_GENMASK(9, 0)
#घोषणा   CGM_PIPE_GAMMA_GREEN_MASK	REG_GENMASK(25, 16)
#घोषणा   CGM_PIPE_GAMMA_BLUE_MASK	REG_GENMASK(9, 0)
#घोषणा _CGM_PIPE_A_MODE	(VLV_DISPLAY_BASE + 0x67A00)
#घोषणा   CGM_PIPE_MODE_GAMMA	(1 << 2)
#घोषणा   CGM_PIPE_MODE_CSC	(1 << 1)
#घोषणा   CGM_PIPE_MODE_DEGAMMA	(1 << 0)

#घोषणा _CGM_PIPE_B_CSC_COEFF01	(VLV_DISPLAY_BASE + 0x69900)
#घोषणा _CGM_PIPE_B_CSC_COEFF23	(VLV_DISPLAY_BASE + 0x69904)
#घोषणा _CGM_PIPE_B_CSC_COEFF45	(VLV_DISPLAY_BASE + 0x69908)
#घोषणा _CGM_PIPE_B_CSC_COEFF67	(VLV_DISPLAY_BASE + 0x6990C)
#घोषणा _CGM_PIPE_B_CSC_COEFF8	(VLV_DISPLAY_BASE + 0x69910)
#घोषणा _CGM_PIPE_B_DEGAMMA	(VLV_DISPLAY_BASE + 0x68000)
#घोषणा _CGM_PIPE_B_GAMMA	(VLV_DISPLAY_BASE + 0x69000)
#घोषणा _CGM_PIPE_B_MODE	(VLV_DISPLAY_BASE + 0x69A00)

#घोषणा CGM_PIPE_CSC_COEFF01(pipe)	_MMIO_PIPE(pipe, _CGM_PIPE_A_CSC_COEFF01, _CGM_PIPE_B_CSC_COEFF01)
#घोषणा CGM_PIPE_CSC_COEFF23(pipe)	_MMIO_PIPE(pipe, _CGM_PIPE_A_CSC_COEFF23, _CGM_PIPE_B_CSC_COEFF23)
#घोषणा CGM_PIPE_CSC_COEFF45(pipe)	_MMIO_PIPE(pipe, _CGM_PIPE_A_CSC_COEFF45, _CGM_PIPE_B_CSC_COEFF45)
#घोषणा CGM_PIPE_CSC_COEFF67(pipe)	_MMIO_PIPE(pipe, _CGM_PIPE_A_CSC_COEFF67, _CGM_PIPE_B_CSC_COEFF67)
#घोषणा CGM_PIPE_CSC_COEFF8(pipe)	_MMIO_PIPE(pipe, _CGM_PIPE_A_CSC_COEFF8, _CGM_PIPE_B_CSC_COEFF8)
#घोषणा CGM_PIPE_DEGAMMA(pipe, i, w)	_MMIO(_PIPE(pipe, _CGM_PIPE_A_DEGAMMA, _CGM_PIPE_B_DEGAMMA) + (i) * 8 + (w) * 4)
#घोषणा CGM_PIPE_GAMMA(pipe, i, w)	_MMIO(_PIPE(pipe, _CGM_PIPE_A_GAMMA, _CGM_PIPE_B_GAMMA) + (i) * 8 + (w) * 4)
#घोषणा CGM_PIPE_MODE(pipe)		_MMIO_PIPE(pipe, _CGM_PIPE_A_MODE, _CGM_PIPE_B_MODE)

/* MIPI DSI रेजिस्टरs */

#घोषणा _MIPI_PORT(port, a, c)	(((port) == PORT_A) ? a : c)	/* ports A and C only */
#घोषणा _MMIO_MIPI(port, a, c)	_MMIO(_MIPI_PORT(port, a, c))

/* Gen11 DSI */
#घोषणा _MMIO_DSI(tc, dsi0, dsi1)	_MMIO_TRANS((tc) - TRANSCODER_DSI_0, \
						    dsi0, dsi1)

#घोषणा MIPIO_TXESC_CLK_DIV1			_MMIO(0x160004)
#घोषणा  GLK_TX_ESC_CLK_DIV1_MASK			0x3FF
#घोषणा MIPIO_TXESC_CLK_DIV2			_MMIO(0x160008)
#घोषणा  GLK_TX_ESC_CLK_DIV2_MASK			0x3FF

#घोषणा _ICL_DSI_ESC_CLK_DIV0		0x6b090
#घोषणा _ICL_DSI_ESC_CLK_DIV1		0x6b890
#घोषणा ICL_DSI_ESC_CLK_DIV(port)	_MMIO_PORT((port),	\
							_ICL_DSI_ESC_CLK_DIV0, \
							_ICL_DSI_ESC_CLK_DIV1)
#घोषणा _ICL_DPHY_ESC_CLK_DIV0		0x162190
#घोषणा _ICL_DPHY_ESC_CLK_DIV1		0x6C190
#घोषणा ICL_DPHY_ESC_CLK_DIV(port)	_MMIO_PORT((port),	\
						_ICL_DPHY_ESC_CLK_DIV0, \
						_ICL_DPHY_ESC_CLK_DIV1)
#घोषणा  ICL_BYTE_CLK_PER_ESC_CLK_MASK		(0x1f << 16)
#घोषणा  ICL_BYTE_CLK_PER_ESC_CLK_SHIFT	16
#घोषणा  ICL_ESC_CLK_DIV_MASK			0x1ff
#घोषणा  ICL_ESC_CLK_DIV_SHIFT			0
#घोषणा DSI_MAX_ESC_CLK			20000		/* in KHz */

#घोषणा _DSI_CMD_FRMCTL_0		0x6b034
#घोषणा _DSI_CMD_FRMCTL_1		0x6b834
#घोषणा DSI_CMD_FRMCTL(port)		_MMIO_PORT(port,	\
						   _DSI_CMD_FRMCTL_0,\
						   _DSI_CMD_FRMCTL_1)
#घोषणा   DSI_FRAME_UPDATE_REQUEST		(1 << 31)
#घोषणा   DSI_PERIODIC_FRAME_UPDATE_ENABLE	(1 << 29)
#घोषणा   DSI_शून्य_PACKET_ENABLE		(1 << 28)
#घोषणा   DSI_FRAME_IN_PROGRESS			(1 << 0)

#घोषणा _DSI_INTR_MASK_REG_0		0x6b070
#घोषणा _DSI_INTR_MASK_REG_1		0x6b870
#घोषणा DSI_INTR_MASK_REG(port)		_MMIO_PORT(port,	\
						   _DSI_INTR_MASK_REG_0,\
						   _DSI_INTR_MASK_REG_1)

#घोषणा _DSI_INTR_IDENT_REG_0		0x6b074
#घोषणा _DSI_INTR_IDENT_REG_1		0x6b874
#घोषणा DSI_INTR_IDENT_REG(port)	_MMIO_PORT(port,	\
						   _DSI_INTR_IDENT_REG_0,\
						   _DSI_INTR_IDENT_REG_1)
#घोषणा   DSI_TE_EVENT				(1 << 31)
#घोषणा   DSI_RX_DATA_OR_BTA_TERMINATED		(1 << 30)
#घोषणा   DSI_TX_DATA				(1 << 29)
#घोषणा   DSI_ULPS_ENTRY_DONE			(1 << 28)
#घोषणा   DSI_NON_TE_TRIGGER_RECEIVED		(1 << 27)
#घोषणा   DSI_HOST_CHKSUM_ERROR			(1 << 26)
#घोषणा   DSI_HOST_MULTI_ECC_ERROR		(1 << 25)
#घोषणा   DSI_HOST_SINGL_ECC_ERROR		(1 << 24)
#घोषणा   DSI_HOST_CONTENTION_DETECTED		(1 << 23)
#घोषणा   DSI_HOST_FALSE_CONTROL_ERROR		(1 << 22)
#घोषणा   DSI_HOST_TIMEOUT_ERROR		(1 << 21)
#घोषणा   DSI_HOST_LOW_POWER_TX_SYNC_ERROR	(1 << 20)
#घोषणा   DSI_HOST_ESCAPE_MODE_ENTRY_ERROR	(1 << 19)
#घोषणा   DSI_FRAME_UPDATE_DONE			(1 << 16)
#घोषणा   DSI_PROTOCOL_VIOLATION_REPORTED	(1 << 15)
#घोषणा   DSI_INVALID_TX_LENGTH			(1 << 13)
#घोषणा   DSI_INVALID_VC			(1 << 12)
#घोषणा   DSI_INVALID_DATA_TYPE			(1 << 11)
#घोषणा   DSI_PERIPHERAL_CHKSUM_ERROR		(1 << 10)
#घोषणा   DSI_PERIPHERAL_MULTI_ECC_ERROR	(1 << 9)
#घोषणा   DSI_PERIPHERAL_SINGLE_ECC_ERROR	(1 << 8)
#घोषणा   DSI_PERIPHERAL_CONTENTION_DETECTED	(1 << 7)
#घोषणा   DSI_PERIPHERAL_FALSE_CTRL_ERROR	(1 << 6)
#घोषणा   DSI_PERIPHERAL_TIMEOUT_ERROR		(1 << 5)
#घोषणा   DSI_PERIPHERAL_LP_TX_SYNC_ERROR	(1 << 4)
#घोषणा   DSI_PERIPHERAL_ESC_MODE_ENTRY_CMD_ERR	(1 << 3)
#घोषणा   DSI_EOT_SYNC_ERROR			(1 << 2)
#घोषणा   DSI_SOT_SYNC_ERROR			(1 << 1)
#घोषणा   DSI_SOT_ERROR				(1 << 0)

/* Gen4+ Timestamp and Pipe Frame समय stamp रेजिस्टरs */
#घोषणा GEN4_TIMESTAMP		_MMIO(0x2358)
#घोषणा ILK_TIMESTAMP_HI	_MMIO(0x70070)
#घोषणा IVB_TIMESTAMP_CTR	_MMIO(0x44070)

#घोषणा GEN9_TIMESTAMP_OVERRIDE				_MMIO(0x44074)
#घोषणा  GEN9_TIMESTAMP_OVERRIDE_US_COUNTER_DIVIDER_SHIFT	0
#घोषणा  GEN9_TIMESTAMP_OVERRIDE_US_COUNTER_DIVIDER_MASK	0x3ff
#घोषणा  GEN9_TIMESTAMP_OVERRIDE_US_COUNTER_DENOMINATOR_SHIFT	12
#घोषणा  GEN9_TIMESTAMP_OVERRIDE_US_COUNTER_DENOMINATOR_MASK	(0xf << 12)

#घोषणा _PIPE_FRMTMSTMP_A		0x70048
#घोषणा PIPE_FRMTMSTMP(pipe)		\
			_MMIO_PIPE2(pipe, _PIPE_FRMTMSTMP_A)

/* BXT MIPI घड़ी controls */
#घोषणा BXT_MAX_VAR_OUTPUT_KHZ			39500

#घोषणा BXT_MIPI_CLOCK_CTL			_MMIO(0x46090)
#घोषणा  BXT_MIPI1_DIV_SHIFT			26
#घोषणा  BXT_MIPI2_DIV_SHIFT			10
#घोषणा  BXT_MIPI_DIV_SHIFT(port)		\
			_MIPI_PORT(port, BXT_MIPI1_DIV_SHIFT, \
					BXT_MIPI2_DIV_SHIFT)

/* TX control भागider to select actual TX घड़ी output from (8x/var) */
#घोषणा  BXT_MIPI1_TX_ESCLK_SHIFT		26
#घोषणा  BXT_MIPI2_TX_ESCLK_SHIFT		10
#घोषणा  BXT_MIPI_TX_ESCLK_SHIFT(port)		\
			_MIPI_PORT(port, BXT_MIPI1_TX_ESCLK_SHIFT, \
					BXT_MIPI2_TX_ESCLK_SHIFT)
#घोषणा  BXT_MIPI1_TX_ESCLK_FIXDIV_MASK		(0x3F << 26)
#घोषणा  BXT_MIPI2_TX_ESCLK_FIXDIV_MASK		(0x3F << 10)
#घोषणा  BXT_MIPI_TX_ESCLK_FIXDIV_MASK(port)	\
			_MIPI_PORT(port, BXT_MIPI1_TX_ESCLK_FIXDIV_MASK, \
					BXT_MIPI2_TX_ESCLK_FIXDIV_MASK)
#घोषणा  BXT_MIPI_TX_ESCLK_DIVIDER(port, val)	\
		(((val) & 0x3F) << BXT_MIPI_TX_ESCLK_SHIFT(port))
/* RX upper control भागider to select actual RX घड़ी output from 8x */
#घोषणा  BXT_MIPI1_RX_ESCLK_UPPER_SHIFT		21
#घोषणा  BXT_MIPI2_RX_ESCLK_UPPER_SHIFT		5
#घोषणा  BXT_MIPI_RX_ESCLK_UPPER_SHIFT(port)		\
			_MIPI_PORT(port, BXT_MIPI1_RX_ESCLK_UPPER_SHIFT, \
					BXT_MIPI2_RX_ESCLK_UPPER_SHIFT)
#घोषणा  BXT_MIPI1_RX_ESCLK_UPPER_FIXDIV_MASK		(3 << 21)
#घोषणा  BXT_MIPI2_RX_ESCLK_UPPER_FIXDIV_MASK		(3 << 5)
#घोषणा  BXT_MIPI_RX_ESCLK_UPPER_FIXDIV_MASK(port)	\
			_MIPI_PORT(port, BXT_MIPI1_RX_ESCLK_UPPER_FIXDIV_MASK, \
					BXT_MIPI2_RX_ESCLK_UPPER_FIXDIV_MASK)
#घोषणा  BXT_MIPI_RX_ESCLK_UPPER_DIVIDER(port, val)	\
		(((val) & 3) << BXT_MIPI_RX_ESCLK_UPPER_SHIFT(port))
/* 8/3X भागider to select the actual 8/3X घड़ी output from 8x */
#घोषणा  BXT_MIPI1_8X_BY3_SHIFT                19
#घोषणा  BXT_MIPI2_8X_BY3_SHIFT                3
#घोषणा  BXT_MIPI_8X_BY3_SHIFT(port)          \
			_MIPI_PORT(port, BXT_MIPI1_8X_BY3_SHIFT, \
					BXT_MIPI2_8X_BY3_SHIFT)
#घोषणा  BXT_MIPI1_8X_BY3_DIVIDER_MASK         (3 << 19)
#घोषणा  BXT_MIPI2_8X_BY3_DIVIDER_MASK         (3 << 3)
#घोषणा  BXT_MIPI_8X_BY3_DIVIDER_MASK(port)    \
			_MIPI_PORT(port, BXT_MIPI1_8X_BY3_DIVIDER_MASK, \
						BXT_MIPI2_8X_BY3_DIVIDER_MASK)
#घोषणा  BXT_MIPI_8X_BY3_DIVIDER(port, val)    \
			(((val) & 3) << BXT_MIPI_8X_BY3_SHIFT(port))
/* RX lower control भागider to select actual RX घड़ी output from 8x */
#घोषणा  BXT_MIPI1_RX_ESCLK_LOWER_SHIFT		16
#घोषणा  BXT_MIPI2_RX_ESCLK_LOWER_SHIFT		0
#घोषणा  BXT_MIPI_RX_ESCLK_LOWER_SHIFT(port)		\
			_MIPI_PORT(port, BXT_MIPI1_RX_ESCLK_LOWER_SHIFT, \
					BXT_MIPI2_RX_ESCLK_LOWER_SHIFT)
#घोषणा  BXT_MIPI1_RX_ESCLK_LOWER_FIXDIV_MASK		(3 << 16)
#घोषणा  BXT_MIPI2_RX_ESCLK_LOWER_FIXDIV_MASK		(3 << 0)
#घोषणा  BXT_MIPI_RX_ESCLK_LOWER_FIXDIV_MASK(port)	\
			_MIPI_PORT(port, BXT_MIPI1_RX_ESCLK_LOWER_FIXDIV_MASK, \
					BXT_MIPI2_RX_ESCLK_LOWER_FIXDIV_MASK)
#घोषणा  BXT_MIPI_RX_ESCLK_LOWER_DIVIDER(port, val)	\
		(((val) & 3) << BXT_MIPI_RX_ESCLK_LOWER_SHIFT(port))

#घोषणा RX_DIVIDER_BIT_1_2                     0x3
#घोषणा RX_DIVIDER_BIT_3_4                     0xC

/* BXT MIPI mode configure */
#घोषणा  _BXT_MIPIA_TRANS_HACTIVE			0x6B0F8
#घोषणा  _BXT_MIPIC_TRANS_HACTIVE			0x6B8F8
#घोषणा  BXT_MIPI_TRANS_HACTIVE(tc)	_MMIO_MIPI(tc, \
		_BXT_MIPIA_TRANS_HACTIVE, _BXT_MIPIC_TRANS_HACTIVE)

#घोषणा  _BXT_MIPIA_TRANS_VACTIVE			0x6B0FC
#घोषणा  _BXT_MIPIC_TRANS_VACTIVE			0x6B8FC
#घोषणा  BXT_MIPI_TRANS_VACTIVE(tc)	_MMIO_MIPI(tc, \
		_BXT_MIPIA_TRANS_VACTIVE, _BXT_MIPIC_TRANS_VACTIVE)

#घोषणा  _BXT_MIPIA_TRANS_VTOTAL			0x6B100
#घोषणा  _BXT_MIPIC_TRANS_VTOTAL			0x6B900
#घोषणा  BXT_MIPI_TRANS_VTOTAL(tc)	_MMIO_MIPI(tc, \
		_BXT_MIPIA_TRANS_VTOTAL, _BXT_MIPIC_TRANS_VTOTAL)

#घोषणा BXT_DSI_PLL_CTL			_MMIO(0x161000)
#घोषणा  BXT_DSI_PLL_PVD_RATIO_SHIFT	16
#घोषणा  BXT_DSI_PLL_PVD_RATIO_MASK	(3 << BXT_DSI_PLL_PVD_RATIO_SHIFT)
#घोषणा  BXT_DSI_PLL_PVD_RATIO_1	(1 << BXT_DSI_PLL_PVD_RATIO_SHIFT)
#घोषणा  BXT_DSIC_16X_BY1		(0 << 10)
#घोषणा  BXT_DSIC_16X_BY2		(1 << 10)
#घोषणा  BXT_DSIC_16X_BY3		(2 << 10)
#घोषणा  BXT_DSIC_16X_BY4		(3 << 10)
#घोषणा  BXT_DSIC_16X_MASK		(3 << 10)
#घोषणा  BXT_DSIA_16X_BY1		(0 << 8)
#घोषणा  BXT_DSIA_16X_BY2		(1 << 8)
#घोषणा  BXT_DSIA_16X_BY3		(2 << 8)
#घोषणा  BXT_DSIA_16X_BY4		(3 << 8)
#घोषणा  BXT_DSIA_16X_MASK		(3 << 8)
#घोषणा  BXT_DSI_FREQ_SEL_SHIFT		8
#घोषणा  BXT_DSI_FREQ_SEL_MASK		(0xF << BXT_DSI_FREQ_SEL_SHIFT)

#घोषणा BXT_DSI_PLL_RATIO_MAX		0x7D
#घोषणा BXT_DSI_PLL_RATIO_MIN		0x22
#घोषणा GLK_DSI_PLL_RATIO_MAX		0x6F
#घोषणा GLK_DSI_PLL_RATIO_MIN		0x22
#घोषणा BXT_DSI_PLL_RATIO_MASK		0xFF
#घोषणा BXT_REF_CLOCK_KHZ		19200

#घोषणा BXT_DSI_PLL_ENABLE		_MMIO(0x46080)
#घोषणा  BXT_DSI_PLL_DO_ENABLE		(1 << 31)
#घोषणा  BXT_DSI_PLL_LOCKED		(1 << 30)

#घोषणा _MIPIA_PORT_CTRL			(VLV_DISPLAY_BASE + 0x61190)
#घोषणा _MIPIC_PORT_CTRL			(VLV_DISPLAY_BASE + 0x61700)
#घोषणा MIPI_PORT_CTRL(port)	_MMIO_MIPI(port, _MIPIA_PORT_CTRL, _MIPIC_PORT_CTRL)

 /* BXT port control */
#घोषणा _BXT_MIPIA_PORT_CTRL				0x6B0C0
#घोषणा _BXT_MIPIC_PORT_CTRL				0x6B8C0
#घोषणा BXT_MIPI_PORT_CTRL(tc)	_MMIO_MIPI(tc, _BXT_MIPIA_PORT_CTRL, _BXT_MIPIC_PORT_CTRL)

/* ICL DSI MODE control */
#घोषणा _ICL_DSI_IO_MODECTL_0				0x6B094
#घोषणा _ICL_DSI_IO_MODECTL_1				0x6B894
#घोषणा ICL_DSI_IO_MODECTL(port)	_MMIO_PORT(port,	\
						    _ICL_DSI_IO_MODECTL_0, \
						    _ICL_DSI_IO_MODECTL_1)
#घोषणा  COMBO_PHY_MODE_DSI				(1 << 0)

/* Display Stream Splitter Control */
#घोषणा DSS_CTL1				_MMIO(0x67400)
#घोषणा  SPLITTER_ENABLE			(1 << 31)
#घोषणा  JOINER_ENABLE				(1 << 30)
#घोषणा  DUAL_LINK_MODE_INTERLEAVE		(1 << 24)
#घोषणा  DUAL_LINK_MODE_FRONTBACK		(0 << 24)
#घोषणा  OVERLAP_PIXELS_MASK			(0xf << 16)
#घोषणा  OVERLAP_PIXELS(pixels)			((pixels) << 16)
#घोषणा  LEFT_DL_BUF_TARGET_DEPTH_MASK		(0xfff << 0)
#घोषणा  LEFT_DL_BUF_TARGET_DEPTH(pixels)	((pixels) << 0)
#घोषणा  MAX_DL_BUFFER_TARGET_DEPTH		0x5a0

#घोषणा DSS_CTL2				_MMIO(0x67404)
#घोषणा  LEFT_BRANCH_VDSC_ENABLE		(1 << 31)
#घोषणा  RIGHT_BRANCH_VDSC_ENABLE		(1 << 15)
#घोषणा  RIGHT_DL_BUF_TARGET_DEPTH_MASK		(0xfff << 0)
#घोषणा  RIGHT_DL_BUF_TARGET_DEPTH(pixels)	((pixels) << 0)

#घोषणा _ICL_PIPE_DSS_CTL1_PB			0x78200
#घोषणा _ICL_PIPE_DSS_CTL1_PC			0x78400
#घोषणा ICL_PIPE_DSS_CTL1(pipe)			_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_PIPE_DSS_CTL1_PB, \
							   _ICL_PIPE_DSS_CTL1_PC)
#घोषणा  BIG_JOINER_ENABLE			(1 << 29)
#घोषणा  MASTER_BIG_JOINER_ENABLE		(1 << 28)
#घोषणा  VGA_CENTERING_ENABLE			(1 << 27)
#घोषणा  SPLITTER_CONFIGURATION_MASK		REG_GENMASK(26, 25)
#घोषणा  SPLITTER_CONFIGURATION_2_SEGMENT	REG_FIELD_PREP(SPLITTER_CONFIGURATION_MASK, 0)
#घोषणा  SPLITTER_CONFIGURATION_4_SEGMENT	REG_FIELD_PREP(SPLITTER_CONFIGURATION_MASK, 1)

#घोषणा _ICL_PIPE_DSS_CTL2_PB			0x78204
#घोषणा _ICL_PIPE_DSS_CTL2_PC			0x78404
#घोषणा ICL_PIPE_DSS_CTL2(pipe)			_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_PIPE_DSS_CTL2_PB, \
							   _ICL_PIPE_DSS_CTL2_PC)

#घोषणा BXT_P_DSI_REGULATOR_CFG			_MMIO(0x160020)
#घोषणा  STAP_SELECT					(1 << 0)

#घोषणा BXT_P_DSI_REGULATOR_TX_CTRL		_MMIO(0x160054)
#घोषणा  HS_IO_CTRL_SELECT				(1 << 0)

#घोषणा  DPI_ENABLE					(1 << 31) /* A + C */
#घोषणा  MIPIA_MIPI4DPHY_DELAY_COUNT_SHIFT		27
#घोषणा  MIPIA_MIPI4DPHY_DELAY_COUNT_MASK		(0xf << 27)
#घोषणा  DUAL_LINK_MODE_SHIFT				26
#घोषणा  DUAL_LINK_MODE_MASK				(1 << 26)
#घोषणा  DUAL_LINK_MODE_FRONT_BACK			(0 << 26)
#घोषणा  DUAL_LINK_MODE_PIXEL_ALTERNATIVE		(1 << 26)
#घोषणा  DITHERING_ENABLE				(1 << 25) /* A + C */
#घोषणा  FLOPPED_HSTX					(1 << 23)
#घोषणा  DE_INVERT					(1 << 19) /* XXX */
#घोषणा  MIPIA_FLISDSI_DELAY_COUNT_SHIFT		18
#घोषणा  MIPIA_FLISDSI_DELAY_COUNT_MASK			(0xf << 18)
#घोषणा  AFE_LATCHOUT					(1 << 17)
#घोषणा  LP_OUTPUT_HOLD					(1 << 16)
#घोषणा  MIPIC_FLISDSI_DELAY_COUNT_HIGH_SHIFT		15
#घोषणा  MIPIC_FLISDSI_DELAY_COUNT_HIGH_MASK		(1 << 15)
#घोषणा  MIPIC_MIPI4DPHY_DELAY_COUNT_SHIFT		11
#घोषणा  MIPIC_MIPI4DPHY_DELAY_COUNT_MASK		(0xf << 11)
#घोषणा  CSB_SHIFT					9
#घोषणा  CSB_MASK					(3 << 9)
#घोषणा  CSB_20MHZ					(0 << 9)
#घोषणा  CSB_10MHZ					(1 << 9)
#घोषणा  CSB_40MHZ					(2 << 9)
#घोषणा  BANDGAP_MASK					(1 << 8)
#घोषणा  BANDGAP_PNW_CIRCUIT				(0 << 8)
#घोषणा  BANDGAP_LNC_CIRCUIT				(1 << 8)
#घोषणा  MIPIC_FLISDSI_DELAY_COUNT_LOW_SHIFT		5
#घोषणा  MIPIC_FLISDSI_DELAY_COUNT_LOW_MASK		(7 << 5)
#घोषणा  TEARING_EFFECT_DELAY				(1 << 4) /* A + C */
#घोषणा  TEARING_EFFECT_SHIFT				2 /* A + C */
#घोषणा  TEARING_EFFECT_MASK				(3 << 2)
#घोषणा  TEARING_EFFECT_OFF				(0 << 2)
#घोषणा  TEARING_EFFECT_DSI				(1 << 2)
#घोषणा  TEARING_EFFECT_GPIO				(2 << 2)
#घोषणा  LANE_CONFIGURATION_SHIFT			0
#घोषणा  LANE_CONFIGURATION_MASK			(3 << 0)
#घोषणा  LANE_CONFIGURATION_4LANE			(0 << 0)
#घोषणा  LANE_CONFIGURATION_DUAL_LINK_A			(1 << 0)
#घोषणा  LANE_CONFIGURATION_DUAL_LINK_B			(2 << 0)

#घोषणा _MIPIA_TEARING_CTRL			(VLV_DISPLAY_BASE + 0x61194)
#घोषणा _MIPIC_TEARING_CTRL			(VLV_DISPLAY_BASE + 0x61704)
#घोषणा MIPI_TEARING_CTRL(port)			_MMIO_MIPI(port, _MIPIA_TEARING_CTRL, _MIPIC_TEARING_CTRL)
#घोषणा  TEARING_EFFECT_DELAY_SHIFT			0
#घोषणा  TEARING_EFFECT_DELAY_MASK			(0xffff << 0)

/* XXX: all bits reserved */
#घोषणा _MIPIA_AUTOPWG			(VLV_DISPLAY_BASE + 0x611a0)

/* MIPI DSI Controller and D-PHY रेजिस्टरs */

#घोषणा _MIPIA_DEVICE_READY		(dev_priv->mipi_mmio_base + 0xb000)
#घोषणा _MIPIC_DEVICE_READY		(dev_priv->mipi_mmio_base + 0xb800)
#घोषणा MIPI_DEVICE_READY(port)		_MMIO_MIPI(port, _MIPIA_DEVICE_READY, _MIPIC_DEVICE_READY)
#घोषणा  BUS_POSSESSION					(1 << 3) /* set to give bus to receiver */
#घोषणा  ULPS_STATE_MASK				(3 << 1)
#घोषणा  ULPS_STATE_ENTER				(2 << 1)
#घोषणा  ULPS_STATE_EXIT				(1 << 1)
#घोषणा  ULPS_STATE_NORMAL_OPERATION			(0 << 1)
#घोषणा  DEVICE_READY					(1 << 0)

#घोषणा _MIPIA_INTR_STAT		(dev_priv->mipi_mmio_base + 0xb004)
#घोषणा _MIPIC_INTR_STAT		(dev_priv->mipi_mmio_base + 0xb804)
#घोषणा MIPI_INTR_STAT(port)		_MMIO_MIPI(port, _MIPIA_INTR_STAT, _MIPIC_INTR_STAT)
#घोषणा _MIPIA_INTR_EN			(dev_priv->mipi_mmio_base + 0xb008)
#घोषणा _MIPIC_INTR_EN			(dev_priv->mipi_mmio_base + 0xb808)
#घोषणा MIPI_INTR_EN(port)		_MMIO_MIPI(port, _MIPIA_INTR_EN, _MIPIC_INTR_EN)
#घोषणा  TEARING_EFFECT					(1 << 31)
#घोषणा  SPL_PKT_SENT_INTERRUPT				(1 << 30)
#घोषणा  GEN_READ_DATA_AVAIL				(1 << 29)
#घोषणा  LP_GENERIC_WR_FIFO_FULL			(1 << 28)
#घोषणा  HS_GENERIC_WR_FIFO_FULL			(1 << 27)
#घोषणा  RX_PROT_VIOLATION				(1 << 26)
#घोषणा  RX_INVALID_TX_LENGTH				(1 << 25)
#घोषणा  ACK_WITH_NO_ERROR				(1 << 24)
#घोषणा  TURN_AROUND_ACK_TIMEOUT			(1 << 23)
#घोषणा  LP_RX_TIMEOUT					(1 << 22)
#घोषणा  HS_TX_TIMEOUT					(1 << 21)
#घोषणा  DPI_FIFO_UNDERRUN				(1 << 20)
#घोषणा  LOW_CONTENTION					(1 << 19)
#घोषणा  HIGH_CONTENTION				(1 << 18)
#घोषणा  TXDSI_VC_ID_INVALID				(1 << 17)
#घोषणा  TXDSI_DATA_TYPE_NOT_RECOGNISED			(1 << 16)
#घोषणा  TXCHECKSUM_ERROR				(1 << 15)
#घोषणा  TXECC_MULTIBIT_ERROR				(1 << 14)
#घोषणा  TXECC_SINGLE_BIT_ERROR				(1 << 13)
#घोषणा  TXFALSE_CONTROL_ERROR				(1 << 12)
#घोषणा  RXDSI_VC_ID_INVALID				(1 << 11)
#घोषणा  RXDSI_DATA_TYPE_NOT_REGOGNISED			(1 << 10)
#घोषणा  RXCHECKSUM_ERROR				(1 << 9)
#घोषणा  RXECC_MULTIBIT_ERROR				(1 << 8)
#घोषणा  RXECC_SINGLE_BIT_ERROR				(1 << 7)
#घोषणा  RXFALSE_CONTROL_ERROR				(1 << 6)
#घोषणा  RXHS_RECEIVE_TIMEOUT_ERROR			(1 << 5)
#घोषणा  RX_LP_TX_SYNC_ERROR				(1 << 4)
#घोषणा  RXEXCAPE_MODE_ENTRY_ERROR			(1 << 3)
#घोषणा  RXEOT_SYNC_ERROR				(1 << 2)
#घोषणा  RXSOT_SYNC_ERROR				(1 << 1)
#घोषणा  RXSOT_ERROR					(1 << 0)

#घोषणा _MIPIA_DSI_FUNC_PRG		(dev_priv->mipi_mmio_base + 0xb00c)
#घोषणा _MIPIC_DSI_FUNC_PRG		(dev_priv->mipi_mmio_base + 0xb80c)
#घोषणा MIPI_DSI_FUNC_PRG(port)		_MMIO_MIPI(port, _MIPIA_DSI_FUNC_PRG, _MIPIC_DSI_FUNC_PRG)
#घोषणा  CMD_MODE_DATA_WIDTH_MASK			(7 << 13)
#घोषणा  CMD_MODE_NOT_SUPPORTED				(0 << 13)
#घोषणा  CMD_MODE_DATA_WIDTH_16_BIT			(1 << 13)
#घोषणा  CMD_MODE_DATA_WIDTH_9_BIT			(2 << 13)
#घोषणा  CMD_MODE_DATA_WIDTH_8_BIT			(3 << 13)
#घोषणा  CMD_MODE_DATA_WIDTH_OPTION1			(4 << 13)
#घोषणा  CMD_MODE_DATA_WIDTH_OPTION2			(5 << 13)
#घोषणा  VID_MODE_FORMAT_MASK				(0xf << 7)
#घोषणा  VID_MODE_NOT_SUPPORTED				(0 << 7)
#घोषणा  VID_MODE_FORMAT_RGB565				(1 << 7)
#घोषणा  VID_MODE_FORMAT_RGB666_PACKED			(2 << 7)
#घोषणा  VID_MODE_FORMAT_RGB666				(3 << 7)
#घोषणा  VID_MODE_FORMAT_RGB888				(4 << 7)
#घोषणा  CMD_MODE_CHANNEL_NUMBER_SHIFT			5
#घोषणा  CMD_MODE_CHANNEL_NUMBER_MASK			(3 << 5)
#घोषणा  VID_MODE_CHANNEL_NUMBER_SHIFT			3
#घोषणा  VID_MODE_CHANNEL_NUMBER_MASK			(3 << 3)
#घोषणा  DATA_LANES_PRG_REG_SHIFT			0
#घोषणा  DATA_LANES_PRG_REG_MASK			(7 << 0)

#घोषणा _MIPIA_HS_TX_TIMEOUT		(dev_priv->mipi_mmio_base + 0xb010)
#घोषणा _MIPIC_HS_TX_TIMEOUT		(dev_priv->mipi_mmio_base + 0xb810)
#घोषणा MIPI_HS_TX_TIMEOUT(port)	_MMIO_MIPI(port, _MIPIA_HS_TX_TIMEOUT, _MIPIC_HS_TX_TIMEOUT)
#घोषणा  HIGH_SPEED_TX_TIMEOUT_COUNTER_MASK		0xffffff

#घोषणा _MIPIA_LP_RX_TIMEOUT		(dev_priv->mipi_mmio_base + 0xb014)
#घोषणा _MIPIC_LP_RX_TIMEOUT		(dev_priv->mipi_mmio_base + 0xb814)
#घोषणा MIPI_LP_RX_TIMEOUT(port)	_MMIO_MIPI(port, _MIPIA_LP_RX_TIMEOUT, _MIPIC_LP_RX_TIMEOUT)
#घोषणा  LOW_POWER_RX_TIMEOUT_COUNTER_MASK		0xffffff

#घोषणा _MIPIA_TURN_AROUND_TIMEOUT	(dev_priv->mipi_mmio_base + 0xb018)
#घोषणा _MIPIC_TURN_AROUND_TIMEOUT	(dev_priv->mipi_mmio_base + 0xb818)
#घोषणा MIPI_TURN_AROUND_TIMEOUT(port)	_MMIO_MIPI(port, _MIPIA_TURN_AROUND_TIMEOUT, _MIPIC_TURN_AROUND_TIMEOUT)
#घोषणा  TURN_AROUND_TIMEOUT_MASK			0x3f

#घोषणा _MIPIA_DEVICE_RESET_TIMER	(dev_priv->mipi_mmio_base + 0xb01c)
#घोषणा _MIPIC_DEVICE_RESET_TIMER	(dev_priv->mipi_mmio_base + 0xb81c)
#घोषणा MIPI_DEVICE_RESET_TIMER(port)	_MMIO_MIPI(port, _MIPIA_DEVICE_RESET_TIMER, _MIPIC_DEVICE_RESET_TIMER)
#घोषणा  DEVICE_RESET_TIMER_MASK			0xffff

#घोषणा _MIPIA_DPI_RESOLUTION		(dev_priv->mipi_mmio_base + 0xb020)
#घोषणा _MIPIC_DPI_RESOLUTION		(dev_priv->mipi_mmio_base + 0xb820)
#घोषणा MIPI_DPI_RESOLUTION(port)	_MMIO_MIPI(port, _MIPIA_DPI_RESOLUTION, _MIPIC_DPI_RESOLUTION)
#घोषणा  VERTICAL_ADDRESS_SHIFT				16
#घोषणा  VERTICAL_ADDRESS_MASK				(0xffff << 16)
#घोषणा  HORIZONTAL_ADDRESS_SHIFT			0
#घोषणा  HORIZONTAL_ADDRESS_MASK			0xffff

#घोषणा _MIPIA_DBI_FIFO_THROTTLE	(dev_priv->mipi_mmio_base + 0xb024)
#घोषणा _MIPIC_DBI_FIFO_THROTTLE	(dev_priv->mipi_mmio_base + 0xb824)
#घोषणा MIPI_DBI_FIFO_THROTTLE(port)	_MMIO_MIPI(port, _MIPIA_DBI_FIFO_THROTTLE, _MIPIC_DBI_FIFO_THROTTLE)
#घोषणा  DBI_FIFO_EMPTY_HALF				(0 << 0)
#घोषणा  DBI_FIFO_EMPTY_QUARTER				(1 << 0)
#घोषणा  DBI_FIFO_EMPTY_7_LOCATIONS			(2 << 0)

/* regs below are bits 15:0 */
#घोषणा _MIPIA_HSYNC_PADDING_COUNT	(dev_priv->mipi_mmio_base + 0xb028)
#घोषणा _MIPIC_HSYNC_PADDING_COUNT	(dev_priv->mipi_mmio_base + 0xb828)
#घोषणा MIPI_HSYNC_PADDING_COUNT(port)	_MMIO_MIPI(port, _MIPIA_HSYNC_PADDING_COUNT, _MIPIC_HSYNC_PADDING_COUNT)

#घोषणा _MIPIA_HBP_COUNT		(dev_priv->mipi_mmio_base + 0xb02c)
#घोषणा _MIPIC_HBP_COUNT		(dev_priv->mipi_mmio_base + 0xb82c)
#घोषणा MIPI_HBP_COUNT(port)		_MMIO_MIPI(port, _MIPIA_HBP_COUNT, _MIPIC_HBP_COUNT)

#घोषणा _MIPIA_HFP_COUNT		(dev_priv->mipi_mmio_base + 0xb030)
#घोषणा _MIPIC_HFP_COUNT		(dev_priv->mipi_mmio_base + 0xb830)
#घोषणा MIPI_HFP_COUNT(port)		_MMIO_MIPI(port, _MIPIA_HFP_COUNT, _MIPIC_HFP_COUNT)

#घोषणा _MIPIA_HACTIVE_AREA_COUNT	(dev_priv->mipi_mmio_base + 0xb034)
#घोषणा _MIPIC_HACTIVE_AREA_COUNT	(dev_priv->mipi_mmio_base + 0xb834)
#घोषणा MIPI_HACTIVE_AREA_COUNT(port)	_MMIO_MIPI(port, _MIPIA_HACTIVE_AREA_COUNT, _MIPIC_HACTIVE_AREA_COUNT)

#घोषणा _MIPIA_VSYNC_PADDING_COUNT	(dev_priv->mipi_mmio_base + 0xb038)
#घोषणा _MIPIC_VSYNC_PADDING_COUNT	(dev_priv->mipi_mmio_base + 0xb838)
#घोषणा MIPI_VSYNC_PADDING_COUNT(port)	_MMIO_MIPI(port, _MIPIA_VSYNC_PADDING_COUNT, _MIPIC_VSYNC_PADDING_COUNT)

#घोषणा _MIPIA_VBP_COUNT		(dev_priv->mipi_mmio_base + 0xb03c)
#घोषणा _MIPIC_VBP_COUNT		(dev_priv->mipi_mmio_base + 0xb83c)
#घोषणा MIPI_VBP_COUNT(port)		_MMIO_MIPI(port, _MIPIA_VBP_COUNT, _MIPIC_VBP_COUNT)

#घोषणा _MIPIA_VFP_COUNT		(dev_priv->mipi_mmio_base + 0xb040)
#घोषणा _MIPIC_VFP_COUNT		(dev_priv->mipi_mmio_base + 0xb840)
#घोषणा MIPI_VFP_COUNT(port)		_MMIO_MIPI(port, _MIPIA_VFP_COUNT, _MIPIC_VFP_COUNT)

#घोषणा _MIPIA_HIGH_LOW_SWITCH_COUNT	(dev_priv->mipi_mmio_base + 0xb044)
#घोषणा _MIPIC_HIGH_LOW_SWITCH_COUNT	(dev_priv->mipi_mmio_base + 0xb844)
#घोषणा MIPI_HIGH_LOW_SWITCH_COUNT(port)	_MMIO_MIPI(port,	_MIPIA_HIGH_LOW_SWITCH_COUNT, _MIPIC_HIGH_LOW_SWITCH_COUNT)

/* regs above are bits 15:0 */

#घोषणा _MIPIA_DPI_CONTROL		(dev_priv->mipi_mmio_base + 0xb048)
#घोषणा _MIPIC_DPI_CONTROL		(dev_priv->mipi_mmio_base + 0xb848)
#घोषणा MIPI_DPI_CONTROL(port)		_MMIO_MIPI(port, _MIPIA_DPI_CONTROL, _MIPIC_DPI_CONTROL)
#घोषणा  DPI_LP_MODE					(1 << 6)
#घोषणा  BACKLIGHT_OFF					(1 << 5)
#घोषणा  BACKLIGHT_ON					(1 << 4)
#घोषणा  COLOR_MODE_OFF					(1 << 3)
#घोषणा  COLOR_MODE_ON					(1 << 2)
#घोषणा  TURN_ON					(1 << 1)
#घोषणा  SHUTDOWN					(1 << 0)

#घोषणा _MIPIA_DPI_DATA			(dev_priv->mipi_mmio_base + 0xb04c)
#घोषणा _MIPIC_DPI_DATA			(dev_priv->mipi_mmio_base + 0xb84c)
#घोषणा MIPI_DPI_DATA(port)		_MMIO_MIPI(port, _MIPIA_DPI_DATA, _MIPIC_DPI_DATA)
#घोषणा  COMMAND_BYTE_SHIFT				0
#घोषणा  COMMAND_BYTE_MASK				(0x3f << 0)

#घोषणा _MIPIA_INIT_COUNT		(dev_priv->mipi_mmio_base + 0xb050)
#घोषणा _MIPIC_INIT_COUNT		(dev_priv->mipi_mmio_base + 0xb850)
#घोषणा MIPI_INIT_COUNT(port)		_MMIO_MIPI(port, _MIPIA_INIT_COUNT, _MIPIC_INIT_COUNT)
#घोषणा  MASTER_INIT_TIMER_SHIFT			0
#घोषणा  MASTER_INIT_TIMER_MASK				(0xffff << 0)

#घोषणा _MIPIA_MAX_RETURN_PKT_SIZE	(dev_priv->mipi_mmio_base + 0xb054)
#घोषणा _MIPIC_MAX_RETURN_PKT_SIZE	(dev_priv->mipi_mmio_base + 0xb854)
#घोषणा MIPI_MAX_RETURN_PKT_SIZE(port)	_MMIO_MIPI(port, \
			_MIPIA_MAX_RETURN_PKT_SIZE, _MIPIC_MAX_RETURN_PKT_SIZE)
#घोषणा  MAX_RETURN_PKT_SIZE_SHIFT			0
#घोषणा  MAX_RETURN_PKT_SIZE_MASK			(0x3ff << 0)

#घोषणा _MIPIA_VIDEO_MODE_FORMAT	(dev_priv->mipi_mmio_base + 0xb058)
#घोषणा _MIPIC_VIDEO_MODE_FORMAT	(dev_priv->mipi_mmio_base + 0xb858)
#घोषणा MIPI_VIDEO_MODE_FORMAT(port)	_MMIO_MIPI(port, _MIPIA_VIDEO_MODE_FORMAT, _MIPIC_VIDEO_MODE_FORMAT)
#घोषणा  RANDOM_DPI_DISPLAY_RESOLUTION			(1 << 4)
#घोषणा  DISABLE_VIDEO_BTA				(1 << 3)
#घोषणा  IP_TG_CONFIG					(1 << 2)
#घोषणा  VIDEO_MODE_NON_BURST_WITH_SYNC_PULSE		(1 << 0)
#घोषणा  VIDEO_MODE_NON_BURST_WITH_SYNC_EVENTS		(2 << 0)
#घोषणा  VIDEO_MODE_BURST				(3 << 0)

#घोषणा _MIPIA_EOT_DISABLE		(dev_priv->mipi_mmio_base + 0xb05c)
#घोषणा _MIPIC_EOT_DISABLE		(dev_priv->mipi_mmio_base + 0xb85c)
#घोषणा MIPI_EOT_DISABLE(port)		_MMIO_MIPI(port, _MIPIA_EOT_DISABLE, _MIPIC_EOT_DISABLE)
#घोषणा  BXT_DEFEATURE_DPI_FIFO_CTR			(1 << 9)
#घोषणा  BXT_DPHY_DEFEATURE_EN				(1 << 8)
#घोषणा  LP_RX_TIMEOUT_ERROR_RECOVERY_DISABLE		(1 << 7)
#घोषणा  HS_RX_TIMEOUT_ERROR_RECOVERY_DISABLE		(1 << 6)
#घोषणा  LOW_CONTENTION_RECOVERY_DISABLE		(1 << 5)
#घोषणा  HIGH_CONTENTION_RECOVERY_DISABLE		(1 << 4)
#घोषणा  TXDSI_TYPE_NOT_RECOGNISED_ERROR_RECOVERY_DISABLE (1 << 3)
#घोषणा  TXECC_MULTIBIT_ERROR_RECOVERY_DISABLE		(1 << 2)
#घोषणा  CLOCKSTOP					(1 << 1)
#घोषणा  EOT_DISABLE					(1 << 0)

#घोषणा _MIPIA_LP_BYTECLK		(dev_priv->mipi_mmio_base + 0xb060)
#घोषणा _MIPIC_LP_BYTECLK		(dev_priv->mipi_mmio_base + 0xb860)
#घोषणा MIPI_LP_BYTECLK(port)		_MMIO_MIPI(port, _MIPIA_LP_BYTECLK, _MIPIC_LP_BYTECLK)
#घोषणा  LP_BYTECLK_SHIFT				0
#घोषणा  LP_BYTECLK_MASK				(0xffff << 0)

#घोषणा _MIPIA_TLPX_TIME_COUNT		(dev_priv->mipi_mmio_base + 0xb0a4)
#घोषणा _MIPIC_TLPX_TIME_COUNT		(dev_priv->mipi_mmio_base + 0xb8a4)
#घोषणा MIPI_TLPX_TIME_COUNT(port)	 _MMIO_MIPI(port, _MIPIA_TLPX_TIME_COUNT, _MIPIC_TLPX_TIME_COUNT)

#घोषणा _MIPIA_CLK_LANE_TIMING		(dev_priv->mipi_mmio_base + 0xb098)
#घोषणा _MIPIC_CLK_LANE_TIMING		(dev_priv->mipi_mmio_base + 0xb898)
#घोषणा MIPI_CLK_LANE_TIMING(port)	 _MMIO_MIPI(port, _MIPIA_CLK_LANE_TIMING, _MIPIC_CLK_LANE_TIMING)

/* bits 31:0 */
#घोषणा _MIPIA_LP_GEN_DATA		(dev_priv->mipi_mmio_base + 0xb064)
#घोषणा _MIPIC_LP_GEN_DATA		(dev_priv->mipi_mmio_base + 0xb864)
#घोषणा MIPI_LP_GEN_DATA(port)		_MMIO_MIPI(port, _MIPIA_LP_GEN_DATA, _MIPIC_LP_GEN_DATA)

/* bits 31:0 */
#घोषणा _MIPIA_HS_GEN_DATA		(dev_priv->mipi_mmio_base + 0xb068)
#घोषणा _MIPIC_HS_GEN_DATA		(dev_priv->mipi_mmio_base + 0xb868)
#घोषणा MIPI_HS_GEN_DATA(port)		_MMIO_MIPI(port, _MIPIA_HS_GEN_DATA, _MIPIC_HS_GEN_DATA)

#घोषणा _MIPIA_LP_GEN_CTRL		(dev_priv->mipi_mmio_base + 0xb06c)
#घोषणा _MIPIC_LP_GEN_CTRL		(dev_priv->mipi_mmio_base + 0xb86c)
#घोषणा MIPI_LP_GEN_CTRL(port)		_MMIO_MIPI(port, _MIPIA_LP_GEN_CTRL, _MIPIC_LP_GEN_CTRL)
#घोषणा _MIPIA_HS_GEN_CTRL		(dev_priv->mipi_mmio_base + 0xb070)
#घोषणा _MIPIC_HS_GEN_CTRL		(dev_priv->mipi_mmio_base + 0xb870)
#घोषणा MIPI_HS_GEN_CTRL(port)		_MMIO_MIPI(port, _MIPIA_HS_GEN_CTRL, _MIPIC_HS_GEN_CTRL)
#घोषणा  LONG_PACKET_WORD_COUNT_SHIFT			8
#घोषणा  LONG_PACKET_WORD_COUNT_MASK			(0xffff << 8)
#घोषणा  SHORT_PACKET_PARAM_SHIFT			8
#घोषणा  SHORT_PACKET_PARAM_MASK			(0xffff << 8)
#घोषणा  VIRTUAL_CHANNEL_SHIFT				6
#घोषणा  VIRTUAL_CHANNEL_MASK				(3 << 6)
#घोषणा  DATA_TYPE_SHIFT				0
#घोषणा  DATA_TYPE_MASK					(0x3f << 0)
/* data type values, see include/video/mipi_display.h */

#घोषणा _MIPIA_GEN_FIFO_STAT		(dev_priv->mipi_mmio_base + 0xb074)
#घोषणा _MIPIC_GEN_FIFO_STAT		(dev_priv->mipi_mmio_base + 0xb874)
#घोषणा MIPI_GEN_FIFO_STAT(port)	_MMIO_MIPI(port, _MIPIA_GEN_FIFO_STAT, _MIPIC_GEN_FIFO_STAT)
#घोषणा  DPI_FIFO_EMPTY					(1 << 28)
#घोषणा  DBI_FIFO_EMPTY					(1 << 27)
#घोषणा  LP_CTRL_FIFO_EMPTY				(1 << 26)
#घोषणा  LP_CTRL_FIFO_HALF_EMPTY			(1 << 25)
#घोषणा  LP_CTRL_FIFO_FULL				(1 << 24)
#घोषणा  HS_CTRL_FIFO_EMPTY				(1 << 18)
#घोषणा  HS_CTRL_FIFO_HALF_EMPTY			(1 << 17)
#घोषणा  HS_CTRL_FIFO_FULL				(1 << 16)
#घोषणा  LP_DATA_FIFO_EMPTY				(1 << 10)
#घोषणा  LP_DATA_FIFO_HALF_EMPTY			(1 << 9)
#घोषणा  LP_DATA_FIFO_FULL				(1 << 8)
#घोषणा  HS_DATA_FIFO_EMPTY				(1 << 2)
#घोषणा  HS_DATA_FIFO_HALF_EMPTY			(1 << 1)
#घोषणा  HS_DATA_FIFO_FULL				(1 << 0)

#घोषणा _MIPIA_HS_LS_DBI_ENABLE		(dev_priv->mipi_mmio_base + 0xb078)
#घोषणा _MIPIC_HS_LS_DBI_ENABLE		(dev_priv->mipi_mmio_base + 0xb878)
#घोषणा MIPI_HS_LP_DBI_ENABLE(port)	_MMIO_MIPI(port, _MIPIA_HS_LS_DBI_ENABLE, _MIPIC_HS_LS_DBI_ENABLE)
#घोषणा  DBI_HS_LP_MODE_MASK				(1 << 0)
#घोषणा  DBI_LP_MODE					(1 << 0)
#घोषणा  DBI_HS_MODE					(0 << 0)

#घोषणा _MIPIA_DPHY_PARAM		(dev_priv->mipi_mmio_base + 0xb080)
#घोषणा _MIPIC_DPHY_PARAM		(dev_priv->mipi_mmio_base + 0xb880)
#घोषणा MIPI_DPHY_PARAM(port)		_MMIO_MIPI(port, _MIPIA_DPHY_PARAM, _MIPIC_DPHY_PARAM)
#घोषणा  EXIT_ZERO_COUNT_SHIFT				24
#घोषणा  EXIT_ZERO_COUNT_MASK				(0x3f << 24)
#घोषणा  TRAIL_COUNT_SHIFT				16
#घोषणा  TRAIL_COUNT_MASK				(0x1f << 16)
#घोषणा  CLK_ZERO_COUNT_SHIFT				8
#घोषणा  CLK_ZERO_COUNT_MASK				(0xff << 8)
#घोषणा  PREPARE_COUNT_SHIFT				0
#घोषणा  PREPARE_COUNT_MASK				(0x3f << 0)

#घोषणा _ICL_DSI_T_INIT_MASTER_0	0x6b088
#घोषणा _ICL_DSI_T_INIT_MASTER_1	0x6b888
#घोषणा ICL_DSI_T_INIT_MASTER(port)	_MMIO_PORT(port,	\
						   _ICL_DSI_T_INIT_MASTER_0,\
						   _ICL_DSI_T_INIT_MASTER_1)

#घोषणा _DPHY_CLK_TIMING_PARAM_0	0x162180
#घोषणा _DPHY_CLK_TIMING_PARAM_1	0x6c180
#घोषणा DPHY_CLK_TIMING_PARAM(port)	_MMIO_PORT(port,	\
						   _DPHY_CLK_TIMING_PARAM_0,\
						   _DPHY_CLK_TIMING_PARAM_1)
#घोषणा _DSI_CLK_TIMING_PARAM_0		0x6b080
#घोषणा _DSI_CLK_TIMING_PARAM_1		0x6b880
#घोषणा DSI_CLK_TIMING_PARAM(port)	_MMIO_PORT(port,	\
						   _DSI_CLK_TIMING_PARAM_0,\
						   _DSI_CLK_TIMING_PARAM_1)
#घोषणा  CLK_PREPARE_OVERRIDE		(1 << 31)
#घोषणा  CLK_PREPARE(x)		((x) << 28)
#घोषणा  CLK_PREPARE_MASK		(0x7 << 28)
#घोषणा  CLK_PREPARE_SHIFT		28
#घोषणा  CLK_ZERO_OVERRIDE		(1 << 27)
#घोषणा  CLK_ZERO(x)			((x) << 20)
#घोषणा  CLK_ZERO_MASK			(0xf << 20)
#घोषणा  CLK_ZERO_SHIFT		20
#घोषणा  CLK_PRE_OVERRIDE		(1 << 19)
#घोषणा  CLK_PRE(x)			((x) << 16)
#घोषणा  CLK_PRE_MASK			(0x3 << 16)
#घोषणा  CLK_PRE_SHIFT			16
#घोषणा  CLK_POST_OVERRIDE		(1 << 15)
#घोषणा  CLK_POST(x)			((x) << 8)
#घोषणा  CLK_POST_MASK			(0x7 << 8)
#घोषणा  CLK_POST_SHIFT		8
#घोषणा  CLK_TRAIL_OVERRIDE		(1 << 7)
#घोषणा  CLK_TRAIL(x)			((x) << 0)
#घोषणा  CLK_TRAIL_MASK		(0xf << 0)
#घोषणा  CLK_TRAIL_SHIFT		0

#घोषणा _DPHY_DATA_TIMING_PARAM_0	0x162184
#घोषणा _DPHY_DATA_TIMING_PARAM_1	0x6c184
#घोषणा DPHY_DATA_TIMING_PARAM(port)	_MMIO_PORT(port,	\
						   _DPHY_DATA_TIMING_PARAM_0,\
						   _DPHY_DATA_TIMING_PARAM_1)
#घोषणा _DSI_DATA_TIMING_PARAM_0	0x6B084
#घोषणा _DSI_DATA_TIMING_PARAM_1	0x6B884
#घोषणा DSI_DATA_TIMING_PARAM(port)	_MMIO_PORT(port,	\
						   _DSI_DATA_TIMING_PARAM_0,\
						   _DSI_DATA_TIMING_PARAM_1)
#घोषणा  HS_PREPARE_OVERRIDE		(1 << 31)
#घोषणा  HS_PREPARE(x)			((x) << 24)
#घोषणा  HS_PREPARE_MASK		(0x7 << 24)
#घोषणा  HS_PREPARE_SHIFT		24
#घोषणा  HS_ZERO_OVERRIDE		(1 << 23)
#घोषणा  HS_ZERO(x)			((x) << 16)
#घोषणा  HS_ZERO_MASK			(0xf << 16)
#घोषणा  HS_ZERO_SHIFT			16
#घोषणा  HS_TRAIL_OVERRIDE		(1 << 15)
#घोषणा  HS_TRAIL(x)			((x) << 8)
#घोषणा  HS_TRAIL_MASK			(0x7 << 8)
#घोषणा  HS_TRAIL_SHIFT		8
#घोषणा  HS_EXIT_OVERRIDE		(1 << 7)
#घोषणा  HS_EXIT(x)			((x) << 0)
#घोषणा  HS_EXIT_MASK			(0x7 << 0)
#घोषणा  HS_EXIT_SHIFT			0

#घोषणा _DPHY_TA_TIMING_PARAM_0		0x162188
#घोषणा _DPHY_TA_TIMING_PARAM_1		0x6c188
#घोषणा DPHY_TA_TIMING_PARAM(port)	_MMIO_PORT(port,	\
						   _DPHY_TA_TIMING_PARAM_0,\
						   _DPHY_TA_TIMING_PARAM_1)
#घोषणा _DSI_TA_TIMING_PARAM_0		0x6b098
#घोषणा _DSI_TA_TIMING_PARAM_1		0x6b898
#घोषणा DSI_TA_TIMING_PARAM(port)	_MMIO_PORT(port,	\
						   _DSI_TA_TIMING_PARAM_0,\
						   _DSI_TA_TIMING_PARAM_1)
#घोषणा  TA_SURE_OVERRIDE		(1 << 31)
#घोषणा  TA_SURE(x)			((x) << 16)
#घोषणा  TA_SURE_MASK			(0x1f << 16)
#घोषणा  TA_SURE_SHIFT			16
#घोषणा  TA_GO_OVERRIDE		(1 << 15)
#घोषणा  TA_GO(x)			((x) << 8)
#घोषणा  TA_GO_MASK			(0xf << 8)
#घोषणा  TA_GO_SHIFT			8
#घोषणा  TA_GET_OVERRIDE		(1 << 7)
#घोषणा  TA_GET(x)			((x) << 0)
#घोषणा  TA_GET_MASK			(0xf << 0)
#घोषणा  TA_GET_SHIFT			0

/* DSI transcoder configuration */
#घोषणा _DSI_TRANS_FUNC_CONF_0		0x6b030
#घोषणा _DSI_TRANS_FUNC_CONF_1		0x6b830
#घोषणा DSI_TRANS_FUNC_CONF(tc)		_MMIO_DSI(tc,	\
						  _DSI_TRANS_FUNC_CONF_0,\
						  _DSI_TRANS_FUNC_CONF_1)
#घोषणा  OP_MODE_MASK			(0x3 << 28)
#घोषणा  OP_MODE_SHIFT			28
#घोषणा  CMD_MODE_NO_GATE		(0x0 << 28)
#घोषणा  CMD_MODE_TE_GATE		(0x1 << 28)
#घोषणा  VIDEO_MODE_SYNC_EVENT		(0x2 << 28)
#घोषणा  VIDEO_MODE_SYNC_PULSE		(0x3 << 28)
#घोषणा  TE_SOURCE_GPIO			(1 << 27)
#घोषणा  LINK_READY			(1 << 20)
#घोषणा  PIX_FMT_MASK			(0x3 << 16)
#घोषणा  PIX_FMT_SHIFT			16
#घोषणा  PIX_FMT_RGB565			(0x0 << 16)
#घोषणा  PIX_FMT_RGB666_PACKED		(0x1 << 16)
#घोषणा  PIX_FMT_RGB666_LOOSE		(0x2 << 16)
#घोषणा  PIX_FMT_RGB888			(0x3 << 16)
#घोषणा  PIX_FMT_RGB101010		(0x4 << 16)
#घोषणा  PIX_FMT_RGB121212		(0x5 << 16)
#घोषणा  PIX_FMT_COMPRESSED		(0x6 << 16)
#घोषणा  BGR_TRANSMISSION		(1 << 15)
#घोषणा  PIX_VIRT_CHAN(x)		((x) << 12)
#घोषणा  PIX_VIRT_CHAN_MASK		(0x3 << 12)
#घोषणा  PIX_VIRT_CHAN_SHIFT		12
#घोषणा  PIX_BUF_THRESHOLD_MASK		(0x3 << 10)
#घोषणा  PIX_BUF_THRESHOLD_SHIFT	10
#घोषणा  PIX_BUF_THRESHOLD_1_4		(0x0 << 10)
#घोषणा  PIX_BUF_THRESHOLD_1_2		(0x1 << 10)
#घोषणा  PIX_BUF_THRESHOLD_3_4		(0x2 << 10)
#घोषणा  PIX_BUF_THRESHOLD_FULL		(0x3 << 10)
#घोषणा  CONTINUOUS_CLK_MASK		(0x3 << 8)
#घोषणा  CONTINUOUS_CLK_SHIFT		8
#घोषणा  CLK_ENTER_LP_AFTER_DATA	(0x0 << 8)
#घोषणा  CLK_HS_OR_LP			(0x2 << 8)
#घोषणा  CLK_HS_CONTINUOUS		(0x3 << 8)
#घोषणा  LINK_CALIBRATION_MASK		(0x3 << 4)
#घोषणा  LINK_CALIBRATION_SHIFT		4
#घोषणा  CALIBRATION_DISABLED		(0x0 << 4)
#घोषणा  CALIBRATION_ENABLED_INITIAL_ONLY	(0x2 << 4)
#घोषणा  CALIBRATION_ENABLED_INITIAL_PERIODIC	(0x3 << 4)
#घोषणा  BLANKING_PACKET_ENABLE		(1 << 2)
#घोषणा  S3D_ORIENTATION_LANDSCAPE	(1 << 1)
#घोषणा  EOTP_DISABLED			(1 << 0)

#घोषणा _DSI_CMD_RXCTL_0		0x6b0d4
#घोषणा _DSI_CMD_RXCTL_1		0x6b8d4
#घोषणा DSI_CMD_RXCTL(tc)		_MMIO_DSI(tc,	\
						  _DSI_CMD_RXCTL_0,\
						  _DSI_CMD_RXCTL_1)
#घोषणा  READ_UNLOADS_DW		(1 << 16)
#घोषणा  RECEIVED_UNASSIGNED_TRIGGER	(1 << 15)
#घोषणा  RECEIVED_ACKNOWLEDGE_TRIGGER	(1 << 14)
#घोषणा  RECEIVED_TEAR_EFFECT_TRIGGER	(1 << 13)
#घोषणा  RECEIVED_RESET_TRIGGER		(1 << 12)
#घोषणा  RECEIVED_PAYLOAD_WAS_LOST	(1 << 11)
#घोषणा  RECEIVED_CRC_WAS_LOST		(1 << 10)
#घोषणा  NUMBER_RX_PLOAD_DW_MASK	(0xff << 0)
#घोषणा  NUMBER_RX_PLOAD_DW_SHIFT	0

#घोषणा _DSI_CMD_TXCTL_0		0x6b0d0
#घोषणा _DSI_CMD_TXCTL_1		0x6b8d0
#घोषणा DSI_CMD_TXCTL(tc)		_MMIO_DSI(tc,	\
						  _DSI_CMD_TXCTL_0,\
						  _DSI_CMD_TXCTL_1)
#घोषणा  KEEP_LINK_IN_HS		(1 << 24)
#घोषणा  FREE_HEADER_CREDIT_MASK	(0x1f << 8)
#घोषणा  FREE_HEADER_CREDIT_SHIFT	0x8
#घोषणा  FREE_PLOAD_CREDIT_MASK		(0xff << 0)
#घोषणा  FREE_PLOAD_CREDIT_SHIFT	0
#घोषणा  MAX_HEADER_CREDIT		0x10
#घोषणा  MAX_PLOAD_CREDIT		0x40

#घोषणा _DSI_CMD_TXHDR_0		0x6b100
#घोषणा _DSI_CMD_TXHDR_1		0x6b900
#घोषणा DSI_CMD_TXHDR(tc)		_MMIO_DSI(tc,	\
						  _DSI_CMD_TXHDR_0,\
						  _DSI_CMD_TXHDR_1)
#घोषणा  PAYLOAD_PRESENT		(1 << 31)
#घोषणा  LP_DATA_TRANSFER		(1 << 30)
#घोषणा  VBLANK_FENCE			(1 << 29)
#घोषणा  PARAM_WC_MASK			(0xffff << 8)
#घोषणा  PARAM_WC_LOWER_SHIFT		8
#घोषणा  PARAM_WC_UPPER_SHIFT		16
#घोषणा  VC_MASK			(0x3 << 6)
#घोषणा  VC_SHIFT			6
#घोषणा  DT_MASK			(0x3f << 0)
#घोषणा  DT_SHIFT			0

#घोषणा _DSI_CMD_TXPYLD_0		0x6b104
#घोषणा _DSI_CMD_TXPYLD_1		0x6b904
#घोषणा DSI_CMD_TXPYLD(tc)		_MMIO_DSI(tc,	\
						  _DSI_CMD_TXPYLD_0,\
						  _DSI_CMD_TXPYLD_1)

#घोषणा _DSI_LP_MSG_0			0x6b0d8
#घोषणा _DSI_LP_MSG_1			0x6b8d8
#घोषणा DSI_LP_MSG(tc)			_MMIO_DSI(tc,	\
						  _DSI_LP_MSG_0,\
						  _DSI_LP_MSG_1)
#घोषणा  LPTX_IN_PROGRESS		(1 << 17)
#घोषणा  LINK_IN_ULPS			(1 << 16)
#घोषणा  LINK_ULPS_TYPE_LP11		(1 << 8)
#घोषणा  LINK_ENTER_ULPS		(1 << 0)

/* DSI समयout रेजिस्टरs */
#घोषणा _DSI_HSTX_TO_0			0x6b044
#घोषणा _DSI_HSTX_TO_1			0x6b844
#घोषणा DSI_HSTX_TO(tc)			_MMIO_DSI(tc,	\
						  _DSI_HSTX_TO_0,\
						  _DSI_HSTX_TO_1)
#घोषणा  HSTX_TIMEOUT_VALUE_MASK	(0xffff << 16)
#घोषणा  HSTX_TIMEOUT_VALUE_SHIFT	16
#घोषणा  HSTX_TIMEOUT_VALUE(x)		((x) << 16)
#घोषणा  HSTX_TIMED_OUT			(1 << 0)

#घोषणा _DSI_LPRX_HOST_TO_0		0x6b048
#घोषणा _DSI_LPRX_HOST_TO_1		0x6b848
#घोषणा DSI_LPRX_HOST_TO(tc)		_MMIO_DSI(tc,	\
						  _DSI_LPRX_HOST_TO_0,\
						  _DSI_LPRX_HOST_TO_1)
#घोषणा  LPRX_TIMED_OUT			(1 << 16)
#घोषणा  LPRX_TIMEOUT_VALUE_MASK	(0xffff << 0)
#घोषणा  LPRX_TIMEOUT_VALUE_SHIFT	0
#घोषणा  LPRX_TIMEOUT_VALUE(x)		((x) << 0)

#घोषणा _DSI_PWAIT_TO_0			0x6b040
#घोषणा _DSI_PWAIT_TO_1			0x6b840
#घोषणा DSI_PWAIT_TO(tc)		_MMIO_DSI(tc,	\
						  _DSI_PWAIT_TO_0,\
						  _DSI_PWAIT_TO_1)
#घोषणा  PRESET_TIMEOUT_VALUE_MASK	(0xffff << 16)
#घोषणा  PRESET_TIMEOUT_VALUE_SHIFT	16
#घोषणा  PRESET_TIMEOUT_VALUE(x)	((x) << 16)
#घोषणा  PRESPONSE_TIMEOUT_VALUE_MASK	(0xffff << 0)
#घोषणा  PRESPONSE_TIMEOUT_VALUE_SHIFT	0
#घोषणा  PRESPONSE_TIMEOUT_VALUE(x)	((x) << 0)

#घोषणा _DSI_TA_TO_0			0x6b04c
#घोषणा _DSI_TA_TO_1			0x6b84c
#घोषणा DSI_TA_TO(tc)			_MMIO_DSI(tc,	\
						  _DSI_TA_TO_0,\
						  _DSI_TA_TO_1)
#घोषणा  TA_TIMED_OUT			(1 << 16)
#घोषणा  TA_TIMEOUT_VALUE_MASK		(0xffff << 0)
#घोषणा  TA_TIMEOUT_VALUE_SHIFT		0
#घोषणा  TA_TIMEOUT_VALUE(x)		((x) << 0)

/* bits 31:0 */
#घोषणा _MIPIA_DBI_BW_CTRL		(dev_priv->mipi_mmio_base + 0xb084)
#घोषणा _MIPIC_DBI_BW_CTRL		(dev_priv->mipi_mmio_base + 0xb884)
#घोषणा MIPI_DBI_BW_CTRL(port)		_MMIO_MIPI(port, _MIPIA_DBI_BW_CTRL, _MIPIC_DBI_BW_CTRL)

#घोषणा _MIPIA_CLK_LANE_SWITCH_TIME_CNT		(dev_priv->mipi_mmio_base + 0xb088)
#घोषणा _MIPIC_CLK_LANE_SWITCH_TIME_CNT		(dev_priv->mipi_mmio_base + 0xb888)
#घोषणा MIPI_CLK_LANE_SWITCH_TIME_CNT(port)	_MMIO_MIPI(port, _MIPIA_CLK_LANE_SWITCH_TIME_CNT, _MIPIC_CLK_LANE_SWITCH_TIME_CNT)
#घोषणा  LP_HS_SSW_CNT_SHIFT				16
#घोषणा  LP_HS_SSW_CNT_MASK				(0xffff << 16)
#घोषणा  HS_LP_PWR_SW_CNT_SHIFT				0
#घोषणा  HS_LP_PWR_SW_CNT_MASK				(0xffff << 0)

#घोषणा _MIPIA_STOP_STATE_STALL		(dev_priv->mipi_mmio_base + 0xb08c)
#घोषणा _MIPIC_STOP_STATE_STALL		(dev_priv->mipi_mmio_base + 0xb88c)
#घोषणा MIPI_STOP_STATE_STALL(port)	_MMIO_MIPI(port, _MIPIA_STOP_STATE_STALL, _MIPIC_STOP_STATE_STALL)
#घोषणा  STOP_STATE_STALL_COUNTER_SHIFT			0
#घोषणा  STOP_STATE_STALL_COUNTER_MASK			(0xff << 0)

#घोषणा _MIPIA_INTR_STAT_REG_1		(dev_priv->mipi_mmio_base + 0xb090)
#घोषणा _MIPIC_INTR_STAT_REG_1		(dev_priv->mipi_mmio_base + 0xb890)
#घोषणा MIPI_INTR_STAT_REG_1(port)	_MMIO_MIPI(port, _MIPIA_INTR_STAT_REG_1, _MIPIC_INTR_STAT_REG_1)
#घोषणा _MIPIA_INTR_EN_REG_1		(dev_priv->mipi_mmio_base + 0xb094)
#घोषणा _MIPIC_INTR_EN_REG_1		(dev_priv->mipi_mmio_base + 0xb894)
#घोषणा MIPI_INTR_EN_REG_1(port)	_MMIO_MIPI(port, _MIPIA_INTR_EN_REG_1, _MIPIC_INTR_EN_REG_1)
#घोषणा  RX_CONTENTION_DETECTED				(1 << 0)

/* XXX: only pipe A ?!? */
#घोषणा MIPIA_DBI_TYPEC_CTRL		(dev_priv->mipi_mmio_base + 0xb100)
#घोषणा  DBI_TYPEC_ENABLE				(1 << 31)
#घोषणा  DBI_TYPEC_WIP					(1 << 30)
#घोषणा  DBI_TYPEC_OPTION_SHIFT				28
#घोषणा  DBI_TYPEC_OPTION_MASK				(3 << 28)
#घोषणा  DBI_TYPEC_FREQ_SHIFT				24
#घोषणा  DBI_TYPEC_FREQ_MASK				(0xf << 24)
#घोषणा  DBI_TYPEC_OVERRIDE				(1 << 8)
#घोषणा  DBI_TYPEC_OVERRIDE_COUNTER_SHIFT		0
#घोषणा  DBI_TYPEC_OVERRIDE_COUNTER_MASK		(0xff << 0)


/* MIPI adapter रेजिस्टरs */

#घोषणा _MIPIA_CTRL			(dev_priv->mipi_mmio_base + 0xb104)
#घोषणा _MIPIC_CTRL			(dev_priv->mipi_mmio_base + 0xb904)
#घोषणा MIPI_CTRL(port)			_MMIO_MIPI(port, _MIPIA_CTRL, _MIPIC_CTRL)
#घोषणा  ESCAPE_CLOCK_DIVIDER_SHIFT			5 /* A only */
#घोषणा  ESCAPE_CLOCK_DIVIDER_MASK			(3 << 5)
#घोषणा  ESCAPE_CLOCK_DIVIDER_1				(0 << 5)
#घोषणा  ESCAPE_CLOCK_DIVIDER_2				(1 << 5)
#घोषणा  ESCAPE_CLOCK_DIVIDER_4				(2 << 5)
#घोषणा  READ_REQUEST_PRIORITY_SHIFT			3
#घोषणा  READ_REQUEST_PRIORITY_MASK			(3 << 3)
#घोषणा  READ_REQUEST_PRIORITY_LOW			(0 << 3)
#घोषणा  READ_REQUEST_PRIORITY_HIGH			(3 << 3)
#घोषणा  RGB_FLIP_TO_BGR				(1 << 2)

#घोषणा  BXT_PIPE_SELECT_SHIFT				7
#घोषणा  BXT_PIPE_SELECT_MASK				(7 << 7)
#घोषणा  BXT_PIPE_SELECT(pipe)				((pipe) << 7)
#घोषणा  GLK_PHY_STATUS_PORT_READY			(1 << 31) /* RO */
#घोषणा  GLK_ULPS_NOT_ACTIVE				(1 << 30) /* RO */
#घोषणा  GLK_MIPIIO_RESET_RELEASED			(1 << 28)
#घोषणा  GLK_CLOCK_LANE_STOP_STATE			(1 << 27) /* RO */
#घोषणा  GLK_DATA_LANE_STOP_STATE			(1 << 26) /* RO */
#घोषणा  GLK_LP_WAKE					(1 << 22)
#घोषणा  GLK_LP11_LOW_PWR_MODE				(1 << 21)
#घोषणा  GLK_LP00_LOW_PWR_MODE				(1 << 20)
#घोषणा  GLK_FIREWALL_ENABLE				(1 << 16)
#घोषणा  BXT_PIXEL_OVERLAP_CNT_MASK			(0xf << 10)
#घोषणा  BXT_PIXEL_OVERLAP_CNT_SHIFT			10
#घोषणा  BXT_DSC_ENABLE					(1 << 3)
#घोषणा  BXT_RGB_FLIP					(1 << 2)
#घोषणा  GLK_MIPIIO_PORT_POWERED			(1 << 1) /* RO */
#घोषणा  GLK_MIPIIO_ENABLE				(1 << 0)

#घोषणा _MIPIA_DATA_ADDRESS		(dev_priv->mipi_mmio_base + 0xb108)
#घोषणा _MIPIC_DATA_ADDRESS		(dev_priv->mipi_mmio_base + 0xb908)
#घोषणा MIPI_DATA_ADDRESS(port)		_MMIO_MIPI(port, _MIPIA_DATA_ADDRESS, _MIPIC_DATA_ADDRESS)
#घोषणा  DATA_MEM_ADDRESS_SHIFT				5
#घोषणा  DATA_MEM_ADDRESS_MASK				(0x7ffffff << 5)
#घोषणा  DATA_VALID					(1 << 0)

#घोषणा _MIPIA_DATA_LENGTH		(dev_priv->mipi_mmio_base + 0xb10c)
#घोषणा _MIPIC_DATA_LENGTH		(dev_priv->mipi_mmio_base + 0xb90c)
#घोषणा MIPI_DATA_LENGTH(port)		_MMIO_MIPI(port, _MIPIA_DATA_LENGTH, _MIPIC_DATA_LENGTH)
#घोषणा  DATA_LENGTH_SHIFT				0
#घोषणा  DATA_LENGTH_MASK				(0xfffff << 0)

#घोषणा _MIPIA_COMMAND_ADDRESS		(dev_priv->mipi_mmio_base + 0xb110)
#घोषणा _MIPIC_COMMAND_ADDRESS		(dev_priv->mipi_mmio_base + 0xb910)
#घोषणा MIPI_COMMAND_ADDRESS(port)	_MMIO_MIPI(port, _MIPIA_COMMAND_ADDRESS, _MIPIC_COMMAND_ADDRESS)
#घोषणा  COMMAND_MEM_ADDRESS_SHIFT			5
#घोषणा  COMMAND_MEM_ADDRESS_MASK			(0x7ffffff << 5)
#घोषणा  AUTO_PWG_ENABLE				(1 << 2)
#घोषणा  MEMORY_WRITE_DATA_FROM_PIPE_RENDERING		(1 << 1)
#घोषणा  COMMAND_VALID					(1 << 0)

#घोषणा _MIPIA_COMMAND_LENGTH		(dev_priv->mipi_mmio_base + 0xb114)
#घोषणा _MIPIC_COMMAND_LENGTH		(dev_priv->mipi_mmio_base + 0xb914)
#घोषणा MIPI_COMMAND_LENGTH(port)	_MMIO_MIPI(port, _MIPIA_COMMAND_LENGTH, _MIPIC_COMMAND_LENGTH)
#घोषणा  COMMAND_LENGTH_SHIFT(n)			(8 * (n)) /* n: 0...3 */
#घोषणा  COMMAND_LENGTH_MASK(n)				(0xff << (8 * (n)))

#घोषणा _MIPIA_READ_DATA_RETURN0	(dev_priv->mipi_mmio_base + 0xb118)
#घोषणा _MIPIC_READ_DATA_RETURN0	(dev_priv->mipi_mmio_base + 0xb918)
#घोषणा MIPI_READ_DATA_RETURN(port, n) _MMIO(_MIPI(port, _MIPIA_READ_DATA_RETURN0, _MIPIC_READ_DATA_RETURN0) + 4 * (n)) /* n: 0...7 */

#घोषणा _MIPIA_READ_DATA_VALID		(dev_priv->mipi_mmio_base + 0xb138)
#घोषणा _MIPIC_READ_DATA_VALID		(dev_priv->mipi_mmio_base + 0xb938)
#घोषणा MIPI_READ_DATA_VALID(port)	_MMIO_MIPI(port, _MIPIA_READ_DATA_VALID, _MIPIC_READ_DATA_VALID)
#घोषणा  READ_DATA_VALID(n)				(1 << (n))

/* MOCS (Memory Object Control State) रेजिस्टरs */
#घोषणा GEN9_LNCFCMOCS(i)	_MMIO(0xb020 + (i) * 4)	/* L3 Cache Control */

#घोषणा __GEN9_RCS0_MOCS0	0xc800
#घोषणा GEN9_GFX_MOCS(i)	_MMIO(__GEN9_RCS0_MOCS0 + (i) * 4)
#घोषणा __GEN9_VCS0_MOCS0	0xc900
#घोषणा GEN9_MFX0_MOCS(i)	_MMIO(__GEN9_VCS0_MOCS0 + (i) * 4)
#घोषणा __GEN9_VCS1_MOCS0	0xca00
#घोषणा GEN9_MFX1_MOCS(i)	_MMIO(__GEN9_VCS1_MOCS0 + (i) * 4)
#घोषणा __GEN9_VECS0_MOCS0	0xcb00
#घोषणा GEN9_VEBOX_MOCS(i)	_MMIO(__GEN9_VECS0_MOCS0 + (i) * 4)
#घोषणा __GEN9_BCS0_MOCS0	0xcc00
#घोषणा GEN9_BLT_MOCS(i)	_MMIO(__GEN9_BCS0_MOCS0 + (i) * 4)
#घोषणा __GEN11_VCS2_MOCS0	0x10000
#घोषणा GEN11_MFX2_MOCS(i)	_MMIO(__GEN11_VCS2_MOCS0 + (i) * 4)

#घोषणा GEN9_SCRATCH_LNCF1		_MMIO(0xb008)
#घोषणा   GEN9_LNCF_NONIA_COHERENT_ATOMICS_ENABLE REG_BIT(0)

#घोषणा GEN9_SCRATCH1			_MMIO(0xb11c)
#घोषणा   EVICTION_PERF_FIX_ENABLE	REG_BIT(8)

#घोषणा GEN10_SCRATCH_LNCF2		_MMIO(0xb0a0)
#घोषणा   PMFLUSHDONE_LNICRSDROP	(1 << 20)
#घोषणा   PMFLUSH_GAPL3UNBLOCK		(1 << 21)
#घोषणा   PMFLUSHDONE_LNEBLK		(1 << 22)

#घोषणा GEN12_GLOBAL_MOCS(i)	_MMIO(0x4000 + (i) * 4) /* Global MOCS regs */

#घोषणा GEN12_GSMBASE			_MMIO(0x108100)

/* gamt regs */
#घोषणा GEN8_L3_LRA_1_GPGPU _MMIO(0x4dd4)
#घोषणा   GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_BDW  0x67F1427F /* max/min क्रम LRA1/2 */
#घोषणा   GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_CHV  0x5FF101FF /* max/min क्रम LRA1/2 */
#घोषणा   GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_SKL  0x67F1427F /*    "        " */
#घोषणा   GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_BXT  0x5FF101FF /*    "        " */

#घोषणा MMCD_MISC_CTRL		_MMIO(0x4ddc) /* skl+ */
#घोषणा  MMCD_PCLA		(1 << 31)
#घोषणा  MMCD_HOTSPOT_EN	(1 << 27)

#घोषणा _ICL_PHY_MISC_A		0x64C00
#घोषणा _ICL_PHY_MISC_B		0x64C04
#घोषणा ICL_PHY_MISC(port)	_MMIO_PORT(port, _ICL_PHY_MISC_A, \
						 _ICL_PHY_MISC_B)
#घोषणा  ICL_PHY_MISC_MUX_DDID			(1 << 28)
#घोषणा  ICL_PHY_MISC_DE_IO_COMP_PWR_DOWN	(1 << 23)

/* Icelake Display Stream Compression Registers */
#घोषणा DSCA_PICTURE_PARAMETER_SET_0		_MMIO(0x6B200)
#घोषणा DSCC_PICTURE_PARAMETER_SET_0		_MMIO(0x6BA00)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_0_PB	0x78270
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_0_PB	0x78370
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_0_PC	0x78470
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_0_PC	0x78570
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_0(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_0_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_0_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_0(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_0_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_0_PC)
#घोषणा  DSC_VBR_ENABLE			(1 << 19)
#घोषणा  DSC_422_ENABLE			(1 << 18)
#घोषणा  DSC_COLOR_SPACE_CONVERSION	(1 << 17)
#घोषणा  DSC_BLOCK_PREDICTION		(1 << 16)
#घोषणा  DSC_LINE_BUF_DEPTH_SHIFT	12
#घोषणा  DSC_BPC_SHIFT			8
#घोषणा  DSC_VER_MIN_SHIFT		4
#घोषणा  DSC_VER_MAJ			(0x1 << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_1		_MMIO(0x6B204)
#घोषणा DSCC_PICTURE_PARAMETER_SET_1		_MMIO(0x6BA04)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_1_PB	0x78274
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_1_PB	0x78374
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_1_PC	0x78474
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_1_PC	0x78574
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_1(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_1_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_1_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_1(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_1_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_1_PC)
#घोषणा  DSC_BPP(bpp)				((bpp) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_2		_MMIO(0x6B208)
#घोषणा DSCC_PICTURE_PARAMETER_SET_2		_MMIO(0x6BA08)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_2_PB	0x78278
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_2_PB	0x78378
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_2_PC	0x78478
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_2_PC	0x78578
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_2(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_2_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_2_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_2(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
					    _ICL_DSC1_PICTURE_PARAMETER_SET_2_PB, \
					    _ICL_DSC1_PICTURE_PARAMETER_SET_2_PC)
#घोषणा  DSC_PIC_WIDTH(pic_width)	((pic_width) << 16)
#घोषणा  DSC_PIC_HEIGHT(pic_height)	((pic_height) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_3		_MMIO(0x6B20C)
#घोषणा DSCC_PICTURE_PARAMETER_SET_3		_MMIO(0x6BA0C)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_3_PB	0x7827C
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_3_PB	0x7837C
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_3_PC	0x7847C
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_3_PC	0x7857C
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_3(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_3_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_3_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_3(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_3_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_3_PC)
#घोषणा  DSC_SLICE_WIDTH(slice_width)   ((slice_width) << 16)
#घोषणा  DSC_SLICE_HEIGHT(slice_height) ((slice_height) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_4		_MMIO(0x6B210)
#घोषणा DSCC_PICTURE_PARAMETER_SET_4		_MMIO(0x6BA10)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_4_PB	0x78280
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_4_PB	0x78380
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_4_PC	0x78480
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_4_PC	0x78580
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_4(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_4_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_4_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_4(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_4_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_4_PC)
#घोषणा  DSC_INITIAL_DEC_DELAY(dec_delay)       ((dec_delay) << 16)
#घोषणा  DSC_INITIAL_XMIT_DELAY(xmit_delay)     ((xmit_delay) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_5		_MMIO(0x6B214)
#घोषणा DSCC_PICTURE_PARAMETER_SET_5		_MMIO(0x6BA14)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_5_PB	0x78284
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_5_PB	0x78384
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_5_PC	0x78484
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_5_PC	0x78584
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_5(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_5_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_5_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_5(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_5_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_5_PC)
#घोषणा  DSC_SCALE_DEC_INT(scale_dec)	((scale_dec) << 16)
#घोषणा  DSC_SCALE_INC_INT(scale_inc)		((scale_inc) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_6		_MMIO(0x6B218)
#घोषणा DSCC_PICTURE_PARAMETER_SET_6		_MMIO(0x6BA18)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_6_PB	0x78288
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_6_PB	0x78388
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_6_PC	0x78488
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_6_PC	0x78588
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_6(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_6_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_6_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_6(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_6_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_6_PC)
#घोषणा  DSC_FLATNESS_MAX_QP(max_qp)		((max_qp) << 24)
#घोषणा  DSC_FLATNESS_MIN_QP(min_qp)		((min_qp) << 16)
#घोषणा  DSC_FIRST_LINE_BPG_OFFSET(offset)	((offset) << 8)
#घोषणा  DSC_INITIAL_SCALE_VALUE(value)		((value) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_7		_MMIO(0x6B21C)
#घोषणा DSCC_PICTURE_PARAMETER_SET_7		_MMIO(0x6BA1C)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_7_PB	0x7828C
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_7_PB	0x7838C
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_7_PC	0x7848C
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_7_PC	0x7858C
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_7(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							    _ICL_DSC0_PICTURE_PARAMETER_SET_7_PB, \
							    _ICL_DSC0_PICTURE_PARAMETER_SET_7_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_7(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							    _ICL_DSC1_PICTURE_PARAMETER_SET_7_PB, \
							    _ICL_DSC1_PICTURE_PARAMETER_SET_7_PC)
#घोषणा  DSC_NFL_BPG_OFFSET(bpg_offset)		((bpg_offset) << 16)
#घोषणा  DSC_SLICE_BPG_OFFSET(bpg_offset)	((bpg_offset) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_8		_MMIO(0x6B220)
#घोषणा DSCC_PICTURE_PARAMETER_SET_8		_MMIO(0x6BA20)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_8_PB	0x78290
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_8_PB	0x78390
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_8_PC	0x78490
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_8_PC	0x78590
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_8(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_8_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_8_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_8(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_8_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_8_PC)
#घोषणा  DSC_INITIAL_OFFSET(initial_offset)		((initial_offset) << 16)
#घोषणा  DSC_FINAL_OFFSET(final_offset)			((final_offset) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_9		_MMIO(0x6B224)
#घोषणा DSCC_PICTURE_PARAMETER_SET_9		_MMIO(0x6BA24)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_9_PB	0x78294
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_9_PB	0x78394
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_9_PC	0x78494
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_9_PC	0x78594
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_9(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_9_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_9_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_9(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_9_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_9_PC)
#घोषणा  DSC_RC_EDGE_FACTOR(rc_edge_fact)	((rc_edge_fact) << 16)
#घोषणा  DSC_RC_MODEL_SIZE(rc_model_size)	((rc_model_size) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_10		_MMIO(0x6B228)
#घोषणा DSCC_PICTURE_PARAMETER_SET_10		_MMIO(0x6BA28)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_10_PB	0x78298
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_10_PB	0x78398
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_10_PC	0x78498
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_10_PC	0x78598
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_10(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_10_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_10_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_10(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_10_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_10_PC)
#घोषणा  DSC_RC_TARGET_OFF_LOW(rc_tgt_off_low)		((rc_tgt_off_low) << 20)
#घोषणा  DSC_RC_TARGET_OFF_HIGH(rc_tgt_off_high)	((rc_tgt_off_high) << 16)
#घोषणा  DSC_RC_QUANT_INC_LIMIT1(lim)			((lim) << 8)
#घोषणा  DSC_RC_QUANT_INC_LIMIT0(lim)			((lim) << 0)

#घोषणा DSCA_PICTURE_PARAMETER_SET_11		_MMIO(0x6B22C)
#घोषणा DSCC_PICTURE_PARAMETER_SET_11		_MMIO(0x6BA2C)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_11_PB	0x7829C
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_11_PB	0x7839C
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_11_PC	0x7849C
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_11_PC	0x7859C
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_11(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_11_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_11_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_11(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_11_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_11_PC)

#घोषणा DSCA_PICTURE_PARAMETER_SET_12		_MMIO(0x6B260)
#घोषणा DSCC_PICTURE_PARAMETER_SET_12		_MMIO(0x6BA60)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_12_PB	0x782A0
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_12_PB	0x783A0
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_12_PC	0x784A0
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_12_PC	0x785A0
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_12(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_12_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_12_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_12(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_12_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_12_PC)

#घोषणा DSCA_PICTURE_PARAMETER_SET_13		_MMIO(0x6B264)
#घोषणा DSCC_PICTURE_PARAMETER_SET_13		_MMIO(0x6BA64)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_13_PB	0x782A4
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_13_PB	0x783A4
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_13_PC	0x784A4
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_13_PC	0x785A4
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_13(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_13_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_13_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_13(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_13_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_13_PC)

#घोषणा DSCA_PICTURE_PARAMETER_SET_14		_MMIO(0x6B268)
#घोषणा DSCC_PICTURE_PARAMETER_SET_14		_MMIO(0x6BA68)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_14_PB	0x782A8
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_14_PB	0x783A8
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_14_PC	0x784A8
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_14_PC	0x785A8
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_14(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_14_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_14_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_14(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_14_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_14_PC)

#घोषणा DSCA_PICTURE_PARAMETER_SET_15		_MMIO(0x6B26C)
#घोषणा DSCC_PICTURE_PARAMETER_SET_15		_MMIO(0x6BA6C)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_15_PB	0x782AC
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_15_PB	0x783AC
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_15_PC	0x784AC
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_15_PC	0x785AC
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_15(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_15_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_15_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_15(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_15_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_15_PC)

#घोषणा DSCA_PICTURE_PARAMETER_SET_16		_MMIO(0x6B270)
#घोषणा DSCC_PICTURE_PARAMETER_SET_16		_MMIO(0x6BA70)
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_16_PB	0x782B0
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_16_PB	0x783B0
#घोषणा _ICL_DSC0_PICTURE_PARAMETER_SET_16_PC	0x784B0
#घोषणा _ICL_DSC1_PICTURE_PARAMETER_SET_16_PC	0x785B0
#घोषणा ICL_DSC0_PICTURE_PARAMETER_SET_16(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_16_PB, \
							   _ICL_DSC0_PICTURE_PARAMETER_SET_16_PC)
#घोषणा ICL_DSC1_PICTURE_PARAMETER_SET_16(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_16_PB, \
							   _ICL_DSC1_PICTURE_PARAMETER_SET_16_PC)
#घोषणा  DSC_SLICE_ROW_PER_FRAME(slice_row_per_frame)	((slice_row_per_frame) << 20)
#घोषणा  DSC_SLICE_PER_LINE(slice_per_line)		((slice_per_line) << 16)
#घोषणा  DSC_SLICE_CHUNK_SIZE(slice_chunk_size)		((slice_chunk_size) << 0)

/* Icelake Rate Control Buffer Threshold Registers */
#घोषणा DSCA_RC_BUF_THRESH_0			_MMIO(0x6B230)
#घोषणा DSCA_RC_BUF_THRESH_0_UDW		_MMIO(0x6B230 + 4)
#घोषणा DSCC_RC_BUF_THRESH_0			_MMIO(0x6BA30)
#घोषणा DSCC_RC_BUF_THRESH_0_UDW		_MMIO(0x6BA30 + 4)
#घोषणा _ICL_DSC0_RC_BUF_THRESH_0_PB		(0x78254)
#घोषणा _ICL_DSC0_RC_BUF_THRESH_0_UDW_PB	(0x78254 + 4)
#घोषणा _ICL_DSC1_RC_BUF_THRESH_0_PB		(0x78354)
#घोषणा _ICL_DSC1_RC_BUF_THRESH_0_UDW_PB	(0x78354 + 4)
#घोषणा _ICL_DSC0_RC_BUF_THRESH_0_PC		(0x78454)
#घोषणा _ICL_DSC0_RC_BUF_THRESH_0_UDW_PC	(0x78454 + 4)
#घोषणा _ICL_DSC1_RC_BUF_THRESH_0_PC		(0x78554)
#घोषणा _ICL_DSC1_RC_BUF_THRESH_0_UDW_PC	(0x78554 + 4)
#घोषणा ICL_DSC0_RC_BUF_THRESH_0(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
						_ICL_DSC0_RC_BUF_THRESH_0_PB, \
						_ICL_DSC0_RC_BUF_THRESH_0_PC)
#घोषणा ICL_DSC0_RC_BUF_THRESH_0_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
						_ICL_DSC0_RC_BUF_THRESH_0_UDW_PB, \
						_ICL_DSC0_RC_BUF_THRESH_0_UDW_PC)
#घोषणा ICL_DSC1_RC_BUF_THRESH_0(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
						_ICL_DSC1_RC_BUF_THRESH_0_PB, \
						_ICL_DSC1_RC_BUF_THRESH_0_PC)
#घोषणा ICL_DSC1_RC_BUF_THRESH_0_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
						_ICL_DSC1_RC_BUF_THRESH_0_UDW_PB, \
						_ICL_DSC1_RC_BUF_THRESH_0_UDW_PC)

#घोषणा DSCA_RC_BUF_THRESH_1			_MMIO(0x6B238)
#घोषणा DSCA_RC_BUF_THRESH_1_UDW		_MMIO(0x6B238 + 4)
#घोषणा DSCC_RC_BUF_THRESH_1			_MMIO(0x6BA38)
#घोषणा DSCC_RC_BUF_THRESH_1_UDW		_MMIO(0x6BA38 + 4)
#घोषणा _ICL_DSC0_RC_BUF_THRESH_1_PB		(0x7825C)
#घोषणा _ICL_DSC0_RC_BUF_THRESH_1_UDW_PB	(0x7825C + 4)
#घोषणा _ICL_DSC1_RC_BUF_THRESH_1_PB		(0x7835C)
#घोषणा _ICL_DSC1_RC_BUF_THRESH_1_UDW_PB	(0x7835C + 4)
#घोषणा _ICL_DSC0_RC_BUF_THRESH_1_PC		(0x7845C)
#घोषणा _ICL_DSC0_RC_BUF_THRESH_1_UDW_PC	(0x7845C + 4)
#घोषणा _ICL_DSC1_RC_BUF_THRESH_1_PC		(0x7855C)
#घोषणा _ICL_DSC1_RC_BUF_THRESH_1_UDW_PC	(0x7855C + 4)
#घोषणा ICL_DSC0_RC_BUF_THRESH_1(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
						_ICL_DSC0_RC_BUF_THRESH_1_PB, \
						_ICL_DSC0_RC_BUF_THRESH_1_PC)
#घोषणा ICL_DSC0_RC_BUF_THRESH_1_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
						_ICL_DSC0_RC_BUF_THRESH_1_UDW_PB, \
						_ICL_DSC0_RC_BUF_THRESH_1_UDW_PC)
#घोषणा ICL_DSC1_RC_BUF_THRESH_1(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
						_ICL_DSC1_RC_BUF_THRESH_1_PB, \
						_ICL_DSC1_RC_BUF_THRESH_1_PC)
#घोषणा ICL_DSC1_RC_BUF_THRESH_1_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
						_ICL_DSC1_RC_BUF_THRESH_1_UDW_PB, \
						_ICL_DSC1_RC_BUF_THRESH_1_UDW_PC)

#घोषणा PORT_TX_DFLEXDPSP(fia)			_MMIO_FIA((fia), 0x008A0)
#घोषणा   MODULAR_FIA_MASK			(1 << 4)
#घोषणा   TC_LIVE_STATE_TBT(idx)		(1 << ((idx) * 8 + 6))
#घोषणा   TC_LIVE_STATE_TC(idx)			(1 << ((idx) * 8 + 5))
#घोषणा   DP_LANE_ASSIGNMENT_SHIFT(idx)		((idx) * 8)
#घोषणा   DP_LANE_ASSIGNMENT_MASK(idx)		(0xf << ((idx) * 8))
#घोषणा   DP_LANE_ASSIGNMENT(idx, x)		((x) << ((idx) * 8))

#घोषणा PORT_TX_DFLEXDPPMS(fia)			_MMIO_FIA((fia), 0x00890)
#घोषणा   DP_PHY_MODE_STATUS_COMPLETED(idx)	(1 << (idx))

#घोषणा PORT_TX_DFLEXDPCSSS(fia)		_MMIO_FIA((fia), 0x00894)
#घोषणा   DP_PHY_MODE_STATUS_NOT_SAFE(idx)	(1 << (idx))

#घोषणा PORT_TX_DFLEXPA1(fia)			_MMIO_FIA((fia), 0x00880)
#घोषणा   DP_PIN_ASSIGNMENT_SHIFT(idx)		((idx) * 4)
#घोषणा   DP_PIN_ASSIGNMENT_MASK(idx)		(0xf << ((idx) * 4))
#घोषणा   DP_PIN_ASSIGNMENT(idx, x)		((x) << ((idx) * 4))

/* This रेजिस्टर controls the Display State Buffer (DSB) engines. */
#घोषणा _DSBSL_INSTANCE_BASE		0x70B00
#घोषणा DSBSL_INSTANCE(pipe, id)	(_DSBSL_INSTANCE_BASE + \
					 (pipe) * 0x1000 + (id) * 0x100)
#घोषणा DSB_HEAD(pipe, id)		_MMIO(DSBSL_INSTANCE(pipe, id) + 0x0)
#घोषणा DSB_TAIL(pipe, id)		_MMIO(DSBSL_INSTANCE(pipe, id) + 0x4)
#घोषणा DSB_CTRL(pipe, id)		_MMIO(DSBSL_INSTANCE(pipe, id) + 0x8)
#घोषणा   DSB_ENABLE			(1 << 31)
#घोषणा   DSB_STATUS			(1 << 0)

#घोषणा TGL_ROOT_DEVICE_ID		0x9A00
#घोषणा TGL_ROOT_DEVICE_MASK		0xFF00
#घोषणा TGL_ROOT_DEVICE_SKU_MASK	0xF
#घोषणा TGL_ROOT_DEVICE_SKU_ULX		0x2
#घोषणा TGL_ROOT_DEVICE_SKU_ULT		0x4

#पूर्ण_अगर /* _I915_REG_H_ */
