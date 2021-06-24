<शैली गुरु>
/*
 * Copyright (C) 2013 Broadcom Corporation
 * Copyright 2013 Linaro Limited
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _CLK_KONA_H
#घोषणा _CLK_KONA_H

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/clk-provider.h>

#घोषणा	BILLION		1000000000

/* The common घड़ी framework uses u8 to represent a parent index */
#घोषणा PARENT_COUNT_MAX	((u32)U8_MAX)

#घोषणा BAD_CLK_INDEX		U8_MAX	/* Can't ever be valid */
#घोषणा BAD_CLK_NAME		((स्थिर अक्षर *)-1)

#घोषणा BAD_SCALED_DIV_VALUE	U64_MAX

/*
 * Utility macros क्रम object flag management.  If possible, flags
 * should be defined such that 0 is the desired शेष value.
 */
#घोषणा FLAG(type, flag)		BCM_CLK_ ## type ## _FLAGS_ ## flag
#घोषणा FLAG_SET(obj, type, flag)	((obj)->flags |= FLAG(type, flag))
#घोषणा FLAG_CLEAR(obj, type, flag)	((obj)->flags &= ~(FLAG(type, flag)))
#घोषणा FLAG_FLIP(obj, type, flag)	((obj)->flags ^= FLAG(type, flag))
#घोषणा FLAG_TEST(obj, type, flag)	(!!((obj)->flags & FLAG(type, flag)))

/* CCU field state tests */

#घोषणा ccu_policy_exists(ccu_policy)	((ccu_policy)->enable.offset != 0)

/* Clock field state tests */

#घोषणा policy_exists(policy)		((policy)->offset != 0)

#घोषणा gate_exists(gate)		FLAG_TEST(gate, GATE, EXISTS)
#घोषणा gate_is_enabled(gate)		FLAG_TEST(gate, GATE, ENABLED)
#घोषणा gate_is_hw_controllable(gate)	FLAG_TEST(gate, GATE, HW)
#घोषणा gate_is_sw_controllable(gate)	FLAG_TEST(gate, GATE, SW)
#घोषणा gate_is_sw_managed(gate)	FLAG_TEST(gate, GATE, SW_MANAGED)
#घोषणा gate_is_no_disable(gate)	FLAG_TEST(gate, GATE, NO_DISABLE)

#घोषणा gate_flip_enabled(gate)		FLAG_FLIP(gate, GATE, ENABLED)

#घोषणा hyst_exists(hyst)		((hyst)->offset != 0)

#घोषणा भागider_exists(भाग)		FLAG_TEST(भाग, DIV, EXISTS)
#घोषणा भागider_is_fixed(भाग)		FLAG_TEST(भाग, DIV, FIXED)
#घोषणा भागider_has_fraction(भाग)	(!भागider_is_fixed(भाग) && \
						(भाग)->u.s.frac_width > 0)

#घोषणा selector_exists(sel)		((sel)->width != 0)
#घोषणा trigger_exists(trig)		FLAG_TEST(trig, TRIG, EXISTS)

#घोषणा policy_lvm_en_exists(enable)	((enable)->offset != 0)
#घोषणा policy_ctl_exists(control)	((control)->offset != 0)

/* Clock type, used to tell common block what it's part of */
क्रमागत bcm_clk_type अणु
	bcm_clk_none,		/* undefined घड़ी type */
	bcm_clk_bus,
	bcm_clk_core,
	bcm_clk_peri
पूर्ण;

/*
 * CCU policy control क्रम घड़ीs.  Clocks can be enabled or disabled
 * based on the CCU policy in effect.  One bit in each policy mask
 * रेजिस्टर (one per CCU policy) represents whether the घड़ी is
 * enabled when that policy is effect or not.  The CCU policy engine
 * must be stopped to update these bits, and must be restarted again
 * afterward.
 */
काष्ठा bcm_clk_policy अणु
	u32 offset;		/* first policy mask रेजिस्टर offset */
	u32 bit;		/* bit used in all mask रेजिस्टरs */
पूर्ण;

/* Policy initialization macro */

#घोषणा POLICY(_offset, _bit)						\
	अणु								\
		.offset = (_offset),					\
		.bit = (_bit),						\
	पूर्ण

/*
 * Gating control and status is managed by a 32-bit gate रेजिस्टर.
 *
 * There are several types of gating available:
 * - (no gate)
 *     A घड़ी with no gate is assumed to be always enabled.
 * - hardware-only gating (स्वतः-gating)
 *     Enabling or disabling घड़ीs with this type of gate is
 *     managed स्वतःmatically by the hardware.  Such घड़ीs can be
 *     considered by the software to be enabled.  The current status
 *     of स्वतः-gated घड़ीs can be पढ़ो from the gate status bit.
 * - software-only gating
 *     Auto-gating is not available क्रम this type of घड़ी.
 *     Instead, software manages whether it's enabled by setting or
 *     clearing the enable bit.  The current gate status of a gate
 *     under software control can be पढ़ो from the gate status bit.
 *     To ensure a change to the gating status is complete, the
 *     status bit can be polled to verअगरy that the gate has entered
 *     the desired state.
 * - selectable hardware or software gating
 *     Gating क्रम this type of घड़ी can be configured to be either
 *     under software or hardware control.  Which type is in use is
 *     determined by the hw_sw_sel bit of the gate रेजिस्टर.
 */
काष्ठा bcm_clk_gate अणु
	u32 offset;		/* gate रेजिस्टर offset */
	u32 status_bit;		/* 0: gate is disabled; 0: gatge is enabled */
	u32 en_bit;		/* 0: disable; 1: enable */
	u32 hw_sw_sel_bit;	/* 0: hardware gating; 1: software gating */
	u32 flags;		/* BCM_CLK_GATE_FLAGS_* below */
पूर्ण;

/*
 * Gate flags:
 *   HW         means this gate can be स्वतः-gated
 *   SW         means the state of this gate can be software controlled
 *   NO_DISABLE means this gate is (only) enabled अगर under software control
 *   SW_MANAGED means the status of this gate is under software control
 *   ENABLED    means this software-managed gate is *supposed* to be enabled
 */
#घोषणा BCM_CLK_GATE_FLAGS_EXISTS	((u32)1 << 0)	/* Gate is valid */
#घोषणा BCM_CLK_GATE_FLAGS_HW		((u32)1 << 1)	/* Can स्वतः-gate */
#घोषणा BCM_CLK_GATE_FLAGS_SW		((u32)1 << 2)	/* Software control */
#घोषणा BCM_CLK_GATE_FLAGS_NO_DISABLE	((u32)1 << 3)	/* HW or enabled */
#घोषणा BCM_CLK_GATE_FLAGS_SW_MANAGED	((u32)1 << 4)	/* SW now in control */
#घोषणा BCM_CLK_GATE_FLAGS_ENABLED	((u32)1 << 5)	/* If SW_MANAGED */

/*
 * Gate initialization macros.
 *
 * Any gate initially under software control will be enabled.
 */

/* A hardware/software gate initially under software control */
#घोषणा HW_SW_GATE(_offset, _status_bit, _en_bit, _hw_sw_sel_bit)	\
	अणु								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.en_bit = (_en_bit),					\
		.hw_sw_sel_bit = (_hw_sw_sel_bit),			\
		.flags = FLAG(GATE, HW)|FLAG(GATE, SW)|			\
			FLAG(GATE, SW_MANAGED)|FLAG(GATE, ENABLED)|	\
			FLAG(GATE, EXISTS),				\
	पूर्ण

/* A hardware/software gate initially under hardware control */
#घोषणा HW_SW_GATE_AUTO(_offset, _status_bit, _en_bit, _hw_sw_sel_bit)	\
	अणु								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.en_bit = (_en_bit),					\
		.hw_sw_sel_bit = (_hw_sw_sel_bit),			\
		.flags = FLAG(GATE, HW)|FLAG(GATE, SW)|			\
			FLAG(GATE, EXISTS),				\
	पूर्ण

/* A hardware-or-enabled gate (enabled अगर not under hardware control) */
#घोषणा HW_ENABLE_GATE(_offset, _status_bit, _en_bit, _hw_sw_sel_bit)	\
	अणु								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.en_bit = (_en_bit),					\
		.hw_sw_sel_bit = (_hw_sw_sel_bit),			\
		.flags = FLAG(GATE, HW)|FLAG(GATE, SW)|			\
			FLAG(GATE, NO_DISABLE)|FLAG(GATE, EXISTS),	\
	पूर्ण

/* A software-only gate */
#घोषणा SW_ONLY_GATE(_offset, _status_bit, _en_bit)			\
	अणु								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.en_bit = (_en_bit),					\
		.flags = FLAG(GATE, SW)|FLAG(GATE, SW_MANAGED)|		\
			FLAG(GATE, ENABLED)|FLAG(GATE, EXISTS),		\
	पूर्ण

/* A hardware-only gate */
#घोषणा HW_ONLY_GATE(_offset, _status_bit)				\
	अणु								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.flags = FLAG(GATE, HW)|FLAG(GATE, EXISTS),		\
	पूर्ण

/* Gate hysteresis क्रम घड़ीs */
काष्ठा bcm_clk_hyst अणु
	u32 offset;		/* hyst रेजिस्टर offset (normally CLKGATE) */
	u32 en_bit;		/* bit used to enable hysteresis */
	u32 val_bit;		/* अगर enabled: 0 = low delay; 1 = high delay */
पूर्ण;

/* Hysteresis initialization macro */

#घोषणा HYST(_offset, _en_bit, _val_bit)				\
	अणु								\
		.offset = (_offset),					\
		.en_bit = (_en_bit),					\
		.val_bit = (_val_bit),					\
	पूर्ण

/*
 * Each घड़ी can have zero, one, or two भागiders which change the
 * output rate of the घड़ी.  Each भागider can be either fixed or
 * variable.  If there are two भागiders, they are the "pre-divider"
 * and the "regular" or "downstream" भागider.  If there is only one,
 * there is no pre-भागider.
 *
 * A fixed भागider is any non-zero (positive) value, and it
 * indicates how the input rate is affected by the भागider.
 *
 * The value of a variable भागider is मुख्यtained in a sub-field of a
 * 32-bit भागider रेजिस्टर.  The position of the field in the
 * रेजिस्टर is defined by its offset and width.  The value recorded
 * in this field is always 1 less than the value it represents.
 *
 * In addition, a variable भागider can indicate that some subset
 * of its bits represent a "fractional" part of the भागider.  Such
 * bits comprise the low-order portion of the भागider field, and can
 * be viewed as representing the portion of the भागider that lies to
 * the right of the decimal poपूर्णांक.  Most variable भागiders have zero
 * fractional bits.  Variable भागiders with non-zero fraction width
 * still record a value 1 less than the value they represent; the
 * added 1 करोes *not* affect the low-order bit in this हाल, it
 * affects the bits above the fractional part only.  (Often in this
 * code a भागider field value is distinguished from the value it
 * represents by referring to the latter as a "divisor".)
 *
 * In order to aव्योम dealing with fractions, भागider arithmetic is
 * perक्रमmed using "scaled" values.  A scaled value is one that's
 * been left-shअगरted by the fractional width of a भागider.  Dividing
 * a scaled value by a scaled भागisor produces the desired quotient
 * without loss of precision and without any other special handling
 * क्रम fractions.
 *
 * The recorded value of a variable भागider can be modअगरied.  To
 * modअगरy either भागider (or both), a घड़ी must be enabled (i.e.,
 * using its gate).  In addition, a trigger रेजिस्टर (described
 * below) must be used to commit the change, and polled to verअगरy
 * the change is complete.
 */
काष्ठा bcm_clk_भाग अणु
	जोड़ अणु
		काष्ठा अणु	/* variable भागider */
			u32 offset;	/* भागider रेजिस्टर offset */
			u32 shअगरt;	/* field shअगरt */
			u32 width;	/* field width */
			u32 frac_width;	/* field fraction width */

			u64 scaled_भाग;	/* scaled भागider value */
		पूर्ण s;
		u32 fixed;	/* non-zero fixed भागider value */
	पूर्ण u;
	u32 flags;		/* BCM_CLK_DIV_FLAGS_* below */
पूर्ण;

/*
 * Divider flags:
 *   EXISTS means this भागider exists
 *   FIXED means it is a fixed-rate भागider
 */
#घोषणा BCM_CLK_DIV_FLAGS_EXISTS	((u32)1 << 0)	/* Divider is valid */
#घोषणा BCM_CLK_DIV_FLAGS_FIXED		((u32)1 << 1)	/* Fixed-value */

/* Divider initialization macros */

/* A fixed (non-zero) भागider */
#घोषणा FIXED_DIVIDER(_value)						\
	अणु								\
		.u.fixed = (_value),					\
		.flags = FLAG(DIV, EXISTS)|FLAG(DIV, FIXED),		\
	पूर्ण

/* A भागider with an पूर्णांकegral भागisor */
#घोषणा DIVIDER(_offset, _shअगरt, _width)				\
	अणु								\
		.u.s.offset = (_offset),				\
		.u.s.shअगरt = (_shअगरt),					\
		.u.s.width = (_width),					\
		.u.s.scaled_भाग = BAD_SCALED_DIV_VALUE,			\
		.flags = FLAG(DIV, EXISTS),				\
	पूर्ण

/* A भागider whose भागisor has an पूर्णांकeger and fractional part */
#घोषणा FRAC_DIVIDER(_offset, _shअगरt, _width, _frac_width)		\
	अणु								\
		.u.s.offset = (_offset),				\
		.u.s.shअगरt = (_shअगरt),					\
		.u.s.width = (_width),					\
		.u.s.frac_width = (_frac_width),			\
		.u.s.scaled_भाग = BAD_SCALED_DIV_VALUE,			\
		.flags = FLAG(DIV, EXISTS),				\
	पूर्ण

/*
 * Clocks may have multiple "parent" घड़ीs.  If there is more than
 * one, a selector must be specअगरied to define which of the parent
 * घड़ीs is currently in use.  The selected घड़ी is indicated in a
 * sub-field of a 32-bit selector रेजिस्टर.  The range of
 * representable selector values typically exceeds the number of
 * available parent घड़ीs.  Occasionally the reset value of a
 * selector field is explicitly set to a (specअगरic) value that करोes
 * not correspond to a defined input घड़ी.
 *
 * We रेजिस्टर all known parent घड़ीs with the common घड़ी code
 * using a packed array (i.e., no empty slots) of (parent) घड़ी
 * names, and refer to them later using indexes पूर्णांकo that array.
 * We मुख्यtain an array of selector values indexed by common घड़ी
 * index values in order to map between these common घड़ी indexes
 * and the selector values used by the hardware.
 *
 * Like भागiders, a selector can be modअगरied, but to करो so a घड़ी
 * must be enabled, and a trigger must be used to commit the change.
 */
काष्ठा bcm_clk_sel अणु
	u32 offset;		/* selector रेजिस्टर offset */
	u32 shअगरt;		/* field shअगरt */
	u32 width;		/* field width */

	u32 parent_count;	/* number of entries in parent_sel[] */
	u32 *parent_sel;	/* array of parent selector values */
	u8 clk_index;		/* current selected index in parent_sel[] */
पूर्ण;

/* Selector initialization macro */
#घोषणा SELECTOR(_offset, _shअगरt, _width)				\
	अणु								\
		.offset = (_offset),					\
		.shअगरt = (_shअगरt),					\
		.width = (_width),					\
		.clk_index = BAD_CLK_INDEX,				\
	पूर्ण

/*
 * Making changes to a variable भागider or a selector क्रम a घड़ी
 * requires the use of a trigger.  A trigger is defined by a single
 * bit within a रेजिस्टर.  To संकेत a change, a 1 is written पूर्णांकo
 * that bit.  To determine when the change has been completed, that
 * trigger bit is polled; the पढ़ो value will be 1 जबतक the change
 * is in progress, and 0 when it is complete.
 *
 * Occasionally a घड़ी will have more than one trigger.  In this
 * हाल, the "pre-trigger" will be used when changing a घड़ी's
 * selector and/or its pre-भागider.
 */
काष्ठा bcm_clk_trig अणु
	u32 offset;		/* trigger रेजिस्टर offset */
	u32 bit;		/* trigger bit */
	u32 flags;		/* BCM_CLK_TRIG_FLAGS_* below */
पूर्ण;

/*
 * Trigger flags:
 *   EXISTS means this trigger exists
 */
#घोषणा BCM_CLK_TRIG_FLAGS_EXISTS	((u32)1 << 0)	/* Trigger is valid */

/* Trigger initialization macro */
#घोषणा TRIGGER(_offset, _bit)						\
	अणु								\
		.offset = (_offset),					\
		.bit = (_bit),						\
		.flags = FLAG(TRIG, EXISTS),				\
	पूर्ण

काष्ठा peri_clk_data अणु
	काष्ठा bcm_clk_policy policy;
	काष्ठा bcm_clk_gate gate;
	काष्ठा bcm_clk_hyst hyst;
	काष्ठा bcm_clk_trig pre_trig;
	काष्ठा bcm_clk_भाग pre_भाग;
	काष्ठा bcm_clk_trig trig;
	काष्ठा bcm_clk_भाग भाग;
	काष्ठा bcm_clk_sel sel;
	स्थिर अक्षर *घड़ीs[];	/* must be last; use CLOCKS() to declare */
पूर्ण;
#घोषणा CLOCKS(...)	अणु __VA_ARGS__, शून्य, पूर्ण
#घोषणा NO_CLOCKS	अणु शून्य, पूर्ण	/* Must use of no parent घड़ीs */

काष्ठा kona_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा clk_init_data init_data;	/* includes name of this घड़ी */
	काष्ठा ccu_data *ccu;	/* ccu this घड़ी is associated with */
	क्रमागत bcm_clk_type type;
	जोड़ अणु
		व्योम *data;
		काष्ठा peri_clk_data *peri;
	पूर्ण u;
पूर्ण;
#घोषणा to_kona_clk(_hw) \
	container_of(_hw, काष्ठा kona_clk, hw)

/* Initialization macro क्रम an entry in a CCU's kona_clks[] array. */
#घोषणा KONA_CLK(_ccu_name, _clk_name, _type)				\
	अणु								\
		.init_data	= अणु					\
			.name = #_clk_name,				\
			.ops = &kona_ ## _type ## _clk_ops,		\
		पूर्ण,							\
		.ccu		= &_ccu_name ## _ccu_data,		\
		.type		= bcm_clk_ ## _type,			\
		.u.data		= &_clk_name ## _data,			\
	पूर्ण
#घोषणा LAST_KONA_CLK	अणु .type = bcm_clk_none पूर्ण

/*
 * CCU policy control.  To enable software update of the policy
 * tables the CCU policy engine must be stopped by setting the
 * software update enable bit (LVM_EN).  After an update the engine
 * is restarted using the GO bit and either the GO_ATL or GO_AC bit.
 */
काष्ठा bcm_lvm_en अणु
	u32 offset;		/* LVM_EN रेजिस्टर offset */
	u32 bit;		/* POLICY_CONFIG_EN bit in रेजिस्टर */
पूर्ण;

/* Policy enable initialization macro */
#घोषणा CCU_LVM_EN(_offset, _bit)					\
	अणु								\
		.offset = (_offset),					\
		.bit = (_bit),						\
	पूर्ण

काष्ठा bcm_policy_ctl अणु
	u32 offset;		/* POLICY_CTL रेजिस्टर offset */
	u32 go_bit;
	u32 atl_bit;		/* GO, GO_ATL, and GO_AC bits */
	u32 ac_bit;
पूर्ण;

/* Policy control initialization macro */
#घोषणा CCU_POLICY_CTL(_offset, _go_bit, _ac_bit, _atl_bit)		\
	अणु								\
		.offset = (_offset),					\
		.go_bit = (_go_bit),					\
		.ac_bit = (_ac_bit),					\
		.atl_bit = (_atl_bit),					\
	पूर्ण

काष्ठा ccu_policy अणु
	काष्ठा bcm_lvm_en enable;
	काष्ठा bcm_policy_ctl control;
पूर्ण;

/*
 * Each CCU defines a mapped area of memory containing रेजिस्टरs
 * used to manage घड़ीs implemented by the CCU.  Access to memory
 * within the CCU's space is serialized by a spinlock.  Beक्रमe any
 * (other) address can be written, a special access "password" value
 * must be written to its WR_ACCESS रेजिस्टर (located at the base
 * address of the range).  We keep track of the name of each CCU as
 * it is set up, and मुख्यtain them in a list.
 */
काष्ठा ccu_data अणु
	व्योम __iomem *base;	/* base of mapped address space */
	spinlock_t lock;	/* serialization lock */
	bool ग_लिखो_enabled;	/* ग_लिखो access is currently enabled */
	काष्ठा ccu_policy policy;
	काष्ठा device_node *node;
	माप_प्रकार clk_num;
	स्थिर अक्षर *name;
	u32 range;		/* byte range of address space */
	काष्ठा kona_clk kona_clks[];	/* must be last */
पूर्ण;

/* Initialization क्रम common fields in a Kona ccu_data काष्ठाure */
#घोषणा KONA_CCU_COMMON(_prefix, _name, _ccuname)			    \
	.name		= #_name "_ccu",				    \
	.lock		= __SPIN_LOCK_UNLOCKED(_name ## _ccu_data.lock),    \
	.clk_num	= _prefix ## _ ## _ccuname ## _CCU_CLOCK_COUNT

/* Exported globals */

बाह्य काष्ठा clk_ops kona_peri_clk_ops;

/* Externally visible functions */

बाह्य u64 scaled_भाग_max(काष्ठा bcm_clk_भाग *भाग);
बाह्य u64 scaled_भाग_build(काष्ठा bcm_clk_भाग *भाग, u32 भाग_value,
				u32 billionths);

बाह्य व्योम __init kona_dt_ccu_setup(काष्ठा ccu_data *ccu,
				काष्ठा device_node *node);
बाह्य bool __init kona_ccu_init(काष्ठा ccu_data *ccu);

#पूर्ण_अगर /* _CLK_KONA_H */
