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

#समावेश "clk-kona.h"

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>

/*
 * "Policies" affect the frequencies of bus घड़ीs provided by a
 * CCU.  (I believe these polices are named "Deep Sleep", "Economy",
 * "Normal", and "Turbo".)  A lower policy number has lower घातer
 * consumption, and policy 2 is the शेष.
 */
#घोषणा CCU_POLICY_COUNT	4

#घोषणा CCU_ACCESS_PASSWORD      0xA5A500
#घोषणा CLK_GATE_DELAY_LOOP      2000

/* Bitfield operations */

/* Produces a mask of set bits covering a range of a 32-bit value */
अटल अंतरभूत u32 bitfield_mask(u32 shअगरt, u32 width)
अणु
	वापस ((1 << width) - 1) << shअगरt;
पूर्ण

/* Extract the value of a bitfield found within a given रेजिस्टर value */
अटल अंतरभूत u32 bitfield_extract(u32 reg_val, u32 shअगरt, u32 width)
अणु
	वापस (reg_val & bitfield_mask(shअगरt, width)) >> shअगरt;
पूर्ण

/* Replace the value of a bitfield found within a given रेजिस्टर value */
अटल अंतरभूत u32 bitfield_replace(u32 reg_val, u32 shअगरt, u32 width, u32 val)
अणु
	u32 mask = bitfield_mask(shअगरt, width);

	वापस (reg_val & ~mask) | (val << shअगरt);
पूर्ण

/* Divider and scaling helpers */

/* Convert a भागider पूर्णांकo the scaled भागisor value it represents. */
अटल अंतरभूत u64 scaled_भाग_value(काष्ठा bcm_clk_भाग *भाग, u32 reg_भाग)
अणु
	वापस (u64)reg_भाग + ((u64)1 << भाग->u.s.frac_width);
पूर्ण

/*
 * Build a scaled भागider value as बंद as possible to the
 * given whole part (भाग_value) and fractional part (expressed
 * in billionths).
 */
u64 scaled_भाग_build(काष्ठा bcm_clk_भाग *भाग, u32 भाग_value, u32 billionths)
अणु
	u64 combined;

	BUG_ON(!भाग_value);
	BUG_ON(billionths >= BILLION);

	combined = (u64)भाग_value * BILLION + billionths;
	combined <<= भाग->u.s.frac_width;

	वापस DIV_ROUND_CLOSEST_ULL(combined, BILLION);
पूर्ण

/* The scaled minimum भागisor representable by a भागider */
अटल अंतरभूत u64
scaled_भाग_min(काष्ठा bcm_clk_भाग *भाग)
अणु
	अगर (भागider_is_fixed(भाग))
		वापस (u64)भाग->u.fixed;

	वापस scaled_भाग_value(भाग, 0);
पूर्ण

/* The scaled maximum भागisor representable by a भागider */
u64 scaled_भाग_max(काष्ठा bcm_clk_भाग *भाग)
अणु
	u32 reg_भाग;

	अगर (भागider_is_fixed(भाग))
		वापस (u64)भाग->u.fixed;

	reg_भाग = ((u32)1 << भाग->u.s.width) - 1;

	वापस scaled_भाग_value(भाग, reg_भाग);
पूर्ण

/*
 * Convert a scaled भागisor पूर्णांकo its भागider representation as
 * stored in a भागider रेजिस्टर field.
 */
अटल अंतरभूत u32
भागider(काष्ठा bcm_clk_भाग *भाग, u64 scaled_भाग)
अणु
	BUG_ON(scaled_भाग < scaled_भाग_min(भाग));
	BUG_ON(scaled_भाग > scaled_भाग_max(भाग));

	वापस (u32)(scaled_भाग - ((u64)1 << भाग->u.s.frac_width));
पूर्ण

/* Return a rate scaled क्रम use when भागiding by a scaled भागisor. */
अटल अंतरभूत u64
scale_rate(काष्ठा bcm_clk_भाग *भाग, u32 rate)
अणु
	अगर (भागider_is_fixed(भाग))
		वापस (u64)rate;

	वापस (u64)rate << भाग->u.s.frac_width;
पूर्ण

/* CCU access */

/* Read a 32-bit रेजिस्टर value from a CCU's address space. */
अटल अंतरभूत u32 __ccu_पढ़ो(काष्ठा ccu_data *ccu, u32 reg_offset)
अणु
	वापस पढ़ोl(ccu->base + reg_offset);
पूर्ण

/* Write a 32-bit रेजिस्टर value पूर्णांकo a CCU's address space. */
अटल अंतरभूत व्योम
__ccu_ग_लिखो(काष्ठा ccu_data *ccu, u32 reg_offset, u32 reg_val)
अणु
	ग_लिखोl(reg_val, ccu->base + reg_offset);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ccu_lock(काष्ठा ccu_data *ccu)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ccu->lock, flags);

	वापस flags;
पूर्ण
अटल अंतरभूत व्योम ccu_unlock(काष्ठा ccu_data *ccu, अचिन्हित दीर्घ flags)
अणु
	spin_unlock_irqrestore(&ccu->lock, flags);
पूर्ण

/*
 * Enable/disable ग_लिखो access to CCU रक्षित रेजिस्टरs.  The
 * WR_ACCESS रेजिस्टर क्रम all CCUs is at offset 0.
 */
अटल अंतरभूत व्योम __ccu_ग_लिखो_enable(काष्ठा ccu_data *ccu)
अणु
	अगर (ccu->ग_लिखो_enabled) अणु
		pr_err("%s: access already enabled for %s\n", __func__,
			ccu->name);
		वापस;
	पूर्ण
	ccu->ग_लिखो_enabled = true;
	__ccu_ग_लिखो(ccu, 0, CCU_ACCESS_PASSWORD | 1);
पूर्ण

अटल अंतरभूत व्योम __ccu_ग_लिखो_disable(काष्ठा ccu_data *ccu)
अणु
	अगर (!ccu->ग_लिखो_enabled) अणु
		pr_err("%s: access wasn't enabled for %s\n", __func__,
			ccu->name);
		वापस;
	पूर्ण

	__ccu_ग_लिखो(ccu, 0, CCU_ACCESS_PASSWORD);
	ccu->ग_लिखो_enabled = false;
पूर्ण

/*
 * Poll a रेजिस्टर in a CCU's address space, वापसing when the
 * specअगरied bit in that रेजिस्टर's value is set (or clear).  Delay
 * a microsecond after each पढ़ो of the रेजिस्टर.  Returns true अगर
 * successful, or false अगर we gave up trying.
 *
 * Caller must ensure the CCU lock is held.
 */
अटल अंतरभूत bool
__ccu_रुको_bit(काष्ठा ccu_data *ccu, u32 reg_offset, u32 bit, bool want)
अणु
	अचिन्हित पूर्णांक tries;
	u32 bit_mask = 1 << bit;

	क्रम (tries = 0; tries < CLK_GATE_DELAY_LOOP; tries++) अणु
		u32 val;
		bool bit_val;

		val = __ccu_पढ़ो(ccu, reg_offset);
		bit_val = (val & bit_mask) != 0;
		अगर (bit_val == want)
			वापस true;
		udelay(1);
	पूर्ण
	pr_warn("%s: %s/0x%04x bit %u was never %s\n", __func__,
		ccu->name, reg_offset, bit, want ? "set" : "clear");

	वापस false;
पूर्ण

/* Policy operations */

अटल bool __ccu_policy_engine_start(काष्ठा ccu_data *ccu, bool sync)
अणु
	काष्ठा bcm_policy_ctl *control = &ccu->policy.control;
	u32 offset;
	u32 go_bit;
	u32 mask;
	bool ret;

	/* If we करोn't need to control policy for this CCU, we're करोne. */
	अगर (!policy_ctl_exists(control))
		वापस true;

	offset = control->offset;
	go_bit = control->go_bit;

	/* Ensure we're not busy beक्रमe we start */
	ret = __ccu_रुको_bit(ccu, offset, go_bit, false);
	अगर (!ret) अणु
		pr_err("%s: ccu %s policy engine wouldn't go idle\n",
			__func__, ccu->name);
		वापस false;
	पूर्ण

	/*
	 * If it's a synchronous request, we'll रुको क्रम the voltage
	 * and frequency of the active load to stabilize beक्रमe
	 * वापसing.  To करो this we select the active load by
	 * setting the ATL bit.
	 *
	 * An asynchronous request instead ramps the voltage in the
	 * background, and when that process stabilizes, the target
	 * load is copied to the active load and the CCU frequency
	 * is चयनed.  We करो this by selecting the target load
	 * (ATL bit clear) and setting the request स्वतः-copy (AC bit
	 * set).
	 *
	 * Note, we करो NOT पढ़ो-modअगरy-ग_लिखो this रेजिस्टर.
	 */
	mask = (u32)1 << go_bit;
	अगर (sync)
		mask |= 1 << control->atl_bit;
	अन्यथा
		mask |= 1 << control->ac_bit;
	__ccu_ग_लिखो(ccu, offset, mask);

	/* Wait क्रम indication that operation is complete. */
	ret = __ccu_रुको_bit(ccu, offset, go_bit, false);
	अगर (!ret)
		pr_err("%s: ccu %s policy engine never started\n",
			__func__, ccu->name);

	वापस ret;
पूर्ण

अटल bool __ccu_policy_engine_stop(काष्ठा ccu_data *ccu)
अणु
	काष्ठा bcm_lvm_en *enable = &ccu->policy.enable;
	u32 offset;
	u32 enable_bit;
	bool ret;

	/* If we करोn't need to control policy for this CCU, we're करोne. */
	अगर (!policy_lvm_en_exists(enable))
		वापस true;

	/* Ensure we're not busy beक्रमe we start */
	offset = enable->offset;
	enable_bit = enable->bit;
	ret = __ccu_रुको_bit(ccu, offset, enable_bit, false);
	अगर (!ret) अणु
		pr_err("%s: ccu %s policy engine already stopped\n",
			__func__, ccu->name);
		वापस false;
	पूर्ण

	/* Now set the bit to stop the engine (NO पढ़ो-modअगरy-ग_लिखो) */
	__ccu_ग_लिखो(ccu, offset, (u32)1 << enable_bit);

	/* Wait क्रम indication that it has stopped. */
	ret = __ccu_रुको_bit(ccu, offset, enable_bit, false);
	अगर (!ret)
		pr_err("%s: ccu %s policy engine never stopped\n",
			__func__, ccu->name);

	वापस ret;
पूर्ण

/*
 * A CCU has four operating conditions ("policies"), and some घड़ीs
 * can be disabled or enabled based on which policy is currently in
 * effect.  Such घड़ीs have a bit in a "policy mask" रेजिस्टर क्रम
 * each policy indicating whether the घड़ी is enabled क्रम that
 * policy or not.  The bit position क्रम a घड़ी is the same क्रम all
 * four रेजिस्टरs, and the 32-bit रेजिस्टरs are at consecutive
 * addresses.
 */
अटल bool policy_init(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_policy *policy)
अणु
	u32 offset;
	u32 mask;
	पूर्णांक i;
	bool ret;

	अगर (!policy_exists(policy))
		वापस true;

	/*
	 * We need to stop the CCU policy engine to allow update
	 * of our policy bits.
	 */
	अगर (!__ccu_policy_engine_stop(ccu)) अणु
		pr_err("%s: unable to stop CCU %s policy engine\n",
			__func__, ccu->name);
		वापस false;
	पूर्ण

	/*
	 * For now, अगर a घड़ी defines its policy bit we just mark
	 * it "enabled" क्रम all four policies.
	 */
	offset = policy->offset;
	mask = (u32)1 << policy->bit;
	क्रम (i = 0; i < CCU_POLICY_COUNT; i++) अणु
		u32 reg_val;

		reg_val = __ccu_पढ़ो(ccu, offset);
		reg_val |= mask;
		__ccu_ग_लिखो(ccu, offset, reg_val);
		offset += माप(u32);
	पूर्ण

	/* We're करोne updating; fire up the policy engine again. */
	ret = __ccu_policy_engine_start(ccu, true);
	अगर (!ret)
		pr_err("%s: unable to restart CCU %s policy engine\n",
			__func__, ccu->name);

	वापस ret;
पूर्ण

/* Gate operations */

/* Determine whether a घड़ी is gated.  CCU lock must be held.  */
अटल bool
__is_clk_gate_enabled(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate)
अणु
	u32 bit_mask;
	u32 reg_val;

	/* If there is no gate we can assume it's enabled. */
	अगर (!gate_exists(gate))
		वापस true;

	bit_mask = 1 << gate->status_bit;
	reg_val = __ccu_पढ़ो(ccu, gate->offset);

	वापस (reg_val & bit_mask) != 0;
पूर्ण

/* Determine whether a घड़ी is gated. */
अटल bool
is_clk_gate_enabled(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate)
अणु
	दीर्घ flags;
	bool ret;

	/* Aव्योम taking the lock अगर we can */
	अगर (!gate_exists(gate))
		वापस true;

	flags = ccu_lock(ccu);
	ret = __is_clk_gate_enabled(ccu, gate);
	ccu_unlock(ccu, flags);

	वापस ret;
पूर्ण

/*
 * Commit our desired gate state to the hardware.
 * Returns true अगर successful, false otherwise.
 */
अटल bool
__gate_commit(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate)
अणु
	u32 reg_val;
	u32 mask;
	bool enabled = false;

	BUG_ON(!gate_exists(gate));
	अगर (!gate_is_sw_controllable(gate))
		वापस true;		/* Nothing we can change */

	reg_val = __ccu_पढ़ो(ccu, gate->offset);

	/* For a hardware/software gate, set which is in control */
	अगर (gate_is_hw_controllable(gate)) अणु
		mask = (u32)1 << gate->hw_sw_sel_bit;
		अगर (gate_is_sw_managed(gate))
			reg_val |= mask;
		अन्यथा
			reg_val &= ~mask;
	पूर्ण

	/*
	 * If software is in control, enable or disable the gate.
	 * If hardware is, clear the enabled bit क्रम good measure.
	 * If a software controlled gate can't be disabled, we're
	 * required to ग_लिखो a 0 पूर्णांकo the enable bit (but the gate
	 * will be enabled).
	 */
	mask = (u32)1 << gate->en_bit;
	अगर (gate_is_sw_managed(gate) && (enabled = gate_is_enabled(gate)) &&
			!gate_is_no_disable(gate))
		reg_val |= mask;
	अन्यथा
		reg_val &= ~mask;

	__ccu_ग_लिखो(ccu, gate->offset, reg_val);

	/* For a hardware controlled gate, we're करोne */
	अगर (!gate_is_sw_managed(gate))
		वापस true;

	/* Otherwise रुको क्रम the gate to be in desired state */
	वापस __ccu_रुको_bit(ccu, gate->offset, gate->status_bit, enabled);
पूर्ण

/*
 * Initialize a gate.  Our desired state (hardware/software select,
 * and अगर software, its enable state) is committed to hardware
 * without the usual checks to see अगर it's alपढ़ोy set up that way.
 * Returns true अगर successful, false otherwise.
 */
अटल bool gate_init(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate)
अणु
	अगर (!gate_exists(gate))
		वापस true;
	वापस __gate_commit(ccu, gate);
पूर्ण

/*
 * Set a gate to enabled or disabled state.  Does nothing अगर the
 * gate is not currently under software control, or अगर it is alपढ़ोy
 * in the requested state.  Returns true अगर successful, false
 * otherwise.  CCU lock must be held.
 */
अटल bool
__clk_gate(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate, bool enable)
अणु
	bool ret;

	अगर (!gate_exists(gate) || !gate_is_sw_managed(gate))
		वापस true;	/* Nothing to करो */

	अगर (!enable && gate_is_no_disable(gate)) अणु
		pr_warn("%s: invalid gate disable request (ignoring)\n",
			__func__);
		वापस true;
	पूर्ण

	अगर (enable == gate_is_enabled(gate))
		वापस true;	/* No change */

	gate_flip_enabled(gate);
	ret = __gate_commit(ccu, gate);
	अगर (!ret)
		gate_flip_enabled(gate);	/* Revert the change */

	वापस ret;
पूर्ण

/* Enable or disable a gate.  Returns 0 अगर successful, -EIO otherwise */
अटल पूर्णांक clk_gate(काष्ठा ccu_data *ccu, स्थिर अक्षर *name,
			काष्ठा bcm_clk_gate *gate, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	bool success;

	/*
	 * Aव्योम taking the lock अगर we can.  We quietly ignore
	 * requests to change state that करोn't make sense.
	 */
	अगर (!gate_exists(gate) || !gate_is_sw_managed(gate))
		वापस 0;
	अगर (!enable && gate_is_no_disable(gate))
		वापस 0;

	flags = ccu_lock(ccu);
	__ccu_ग_लिखो_enable(ccu);

	success = __clk_gate(ccu, gate, enable);

	__ccu_ग_लिखो_disable(ccu);
	ccu_unlock(ccu, flags);

	अगर (success)
		वापस 0;

	pr_err("%s: failed to %s gate for %s\n", __func__,
		enable ? "enable" : "disable", name);

	वापस -EIO;
पूर्ण

/* Hysteresis operations */

/*
 * If a घड़ी gate requires a turn-off delay it will have
 * "hysteresis" रेजिस्टर bits defined.  The first, अगर set, enables
 * the delay; and अगर enabled, the second bit determines whether the
 * delay is "low" or "high" (1 means high).  For now, अगर it's
 * defined क्रम a घड़ी, we set it.
 */
अटल bool hyst_init(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_hyst *hyst)
अणु
	u32 offset;
	u32 reg_val;
	u32 mask;

	अगर (!hyst_exists(hyst))
		वापस true;

	offset = hyst->offset;
	mask = (u32)1 << hyst->en_bit;
	mask |= (u32)1 << hyst->val_bit;

	reg_val = __ccu_पढ़ो(ccu, offset);
	reg_val |= mask;
	__ccu_ग_लिखो(ccu, offset, reg_val);

	वापस true;
पूर्ण

/* Trigger operations */

/*
 * Caller must ensure CCU lock is held and access is enabled.
 * Returns true अगर successful, false otherwise.
 */
अटल bool __clk_trigger(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_trig *trig)
अणु
	/* Trigger the घड़ी and रुको क्रम it to finish */
	__ccu_ग_लिखो(ccu, trig->offset, 1 << trig->bit);

	वापस __ccu_रुको_bit(ccu, trig->offset, trig->bit, false);
पूर्ण

/* Divider operations */

/* Read a भागider value and वापस the scaled भागisor it represents. */
अटल u64 भागider_पढ़ो_scaled(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_भाग *भाग)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg_val;
	u32 reg_भाग;

	अगर (भागider_is_fixed(भाग))
		वापस (u64)भाग->u.fixed;

	flags = ccu_lock(ccu);
	reg_val = __ccu_पढ़ो(ccu, भाग->u.s.offset);
	ccu_unlock(ccu, flags);

	/* Extract the full भागider field from the रेजिस्टर value */
	reg_भाग = bitfield_extract(reg_val, भाग->u.s.shअगरt, भाग->u.s.width);

	/* Return the scaled भागisor value it represents */
	वापस scaled_भाग_value(भाग, reg_भाग);
पूर्ण

/*
 * Convert a भागider's scaled भागisor value पूर्णांकo its recorded क्रमm
 * and commit it पूर्णांकo the hardware भागider रेजिस्टर.
 *
 * Returns 0 on success.  Returns -EINVAL क्रम invalid arguments.
 * Returns -ENXIO अगर gating failed, and -EIO अगर a trigger failed.
 */
अटल पूर्णांक __भाग_commit(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate,
			काष्ठा bcm_clk_भाग *भाग, काष्ठा bcm_clk_trig *trig)
अणु
	bool enabled;
	u32 reg_भाग;
	u32 reg_val;
	पूर्णांक ret = 0;

	BUG_ON(भागider_is_fixed(भाग));

	/*
	 * If we're just initializing the भागider, and no initial
	 * state was defined in the device tree, we just find out
	 * what its current value is rather than updating it.
	 */
	अगर (भाग->u.s.scaled_भाग == BAD_SCALED_DIV_VALUE) अणु
		reg_val = __ccu_पढ़ो(ccu, भाग->u.s.offset);
		reg_भाग = bitfield_extract(reg_val, भाग->u.s.shअगरt,
						भाग->u.s.width);
		भाग->u.s.scaled_भाग = scaled_भाग_value(भाग, reg_भाग);

		वापस 0;
	पूर्ण

	/* Convert the scaled भागisor to the value we need to record */
	reg_भाग = भागider(भाग, भाग->u.s.scaled_भाग);

	/* Clock needs to be enabled beक्रमe changing the rate */
	enabled = __is_clk_gate_enabled(ccu, gate);
	अगर (!enabled && !__clk_gate(ccu, gate, true)) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	/* Replace the भागider value and record the result */
	reg_val = __ccu_पढ़ो(ccu, भाग->u.s.offset);
	reg_val = bitfield_replace(reg_val, भाग->u.s.shअगरt, भाग->u.s.width,
					reg_भाग);
	__ccu_ग_लिखो(ccu, भाग->u.s.offset, reg_val);

	/* If the trigger fails we still want to disable the gate */
	अगर (!__clk_trigger(ccu, trig))
		ret = -EIO;

	/* Disable the घड़ी again अगर it was disabled to begin with */
	अगर (!enabled && !__clk_gate(ccu, gate, false))
		ret = ret ? ret : -ENXIO;	/* वापस first error */
out:
	वापस ret;
पूर्ण

/*
 * Initialize a भागider by committing our desired state to hardware
 * without the usual checks to see अगर it's alपढ़ोy set up that way.
 * Returns true अगर successful, false otherwise.
 */
अटल bool भाग_init(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate,
			काष्ठा bcm_clk_भाग *भाग, काष्ठा bcm_clk_trig *trig)
अणु
	अगर (!भागider_exists(भाग) || भागider_is_fixed(भाग))
		वापस true;
	वापस !__भाग_commit(ccu, gate, भाग, trig);
पूर्ण

अटल पूर्णांक भागider_ग_लिखो(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate,
			काष्ठा bcm_clk_भाग *भाग, काष्ठा bcm_clk_trig *trig,
			u64 scaled_भाग)
अणु
	अचिन्हित दीर्घ flags;
	u64 previous;
	पूर्णांक ret;

	BUG_ON(भागider_is_fixed(भाग));

	previous = भाग->u.s.scaled_भाग;
	अगर (previous == scaled_भाग)
		वापस 0;	/* No change */

	भाग->u.s.scaled_भाग = scaled_भाग;

	flags = ccu_lock(ccu);
	__ccu_ग_लिखो_enable(ccu);

	ret = __भाग_commit(ccu, gate, भाग, trig);

	__ccu_ग_लिखो_disable(ccu);
	ccu_unlock(ccu, flags);

	अगर (ret)
		भाग->u.s.scaled_भाग = previous;		/* Revert the change */

	वापस ret;

पूर्ण

/* Common घड़ी rate helpers */

/*
 * Implement the common घड़ी framework recalc_rate method, taking
 * पूर्णांकo account a भागider and an optional pre-भागider.  The
 * pre-भागider रेजिस्टर poपूर्णांकer may be शून्य.
 */
अटल अचिन्हित दीर्घ clk_recalc_rate(काष्ठा ccu_data *ccu,
			काष्ठा bcm_clk_भाग *भाग, काष्ठा bcm_clk_भाग *pre_भाग,
			अचिन्हित दीर्घ parent_rate)
अणु
	u64 scaled_parent_rate;
	u64 scaled_भाग;
	u64 result;

	अगर (!भागider_exists(भाग))
		वापस parent_rate;

	अगर (parent_rate > (अचिन्हित दीर्घ)दीर्घ_उच्च)
		वापस 0;	/* actually this would be a caller bug */

	/*
	 * If there is a pre-भागider, भागide the scaled parent rate
	 * by the pre-भागider value first.  In this हाल--to improve
	 * accuracy--scale the parent rate by *both* the pre-भागider
	 * value and the भागider beक्रमe actually computing the
	 * result of the pre-भागider.
	 *
	 * If there's only one भागider, just scale the parent rate.
	 */
	अगर (pre_भाग && भागider_exists(pre_भाग)) अणु
		u64 scaled_rate;

		scaled_rate = scale_rate(pre_भाग, parent_rate);
		scaled_rate = scale_rate(भाग, scaled_rate);
		scaled_भाग = भागider_पढ़ो_scaled(ccu, pre_भाग);
		scaled_parent_rate = DIV_ROUND_CLOSEST_ULL(scaled_rate,
							scaled_भाग);
	पूर्ण अन्यथा  अणु
		scaled_parent_rate = scale_rate(भाग, parent_rate);
	पूर्ण

	/*
	 * Get the scaled भागisor value, and भागide the scaled
	 * parent rate by that to determine this घड़ी's resulting
	 * rate.
	 */
	scaled_भाग = भागider_पढ़ो_scaled(ccu, भाग);
	result = DIV_ROUND_CLOSEST_ULL(scaled_parent_rate, scaled_भाग);

	वापस (अचिन्हित दीर्घ)result;
पूर्ण

/*
 * Compute the output rate produced when a given parent rate is fed
 * पूर्णांकo two भागiders.  The pre-भागider can be शून्य, and even अगर it's
 * non-null it may be nonexistent.  It's also OK क्रम the भागider to
 * be nonexistent, and in that हाल the pre-भागider is also ignored.
 *
 * If scaled_भाग is non-null, it is used to वापस the scaled भागisor
 * value used by the (करोwnstream) भागider to produce that rate.
 */
अटल दीर्घ round_rate(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_भाग *भाग,
				काष्ठा bcm_clk_भाग *pre_भाग,
				अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
				u64 *scaled_भाग)
अणु
	u64 scaled_parent_rate;
	u64 min_scaled_भाग;
	u64 max_scaled_भाग;
	u64 best_scaled_भाग;
	u64 result;

	BUG_ON(!भागider_exists(भाग));
	BUG_ON(!rate);
	BUG_ON(parent_rate > (u64)दीर्घ_उच्च);

	/*
	 * If there is a pre-भागider, भागide the scaled parent rate
	 * by the pre-भागider value first.  In this हाल--to improve
	 * accuracy--scale the parent rate by *both* the pre-भागider
	 * value and the भागider beक्रमe actually computing the
	 * result of the pre-भागider.
	 *
	 * If there's only one भागider, just scale the parent rate.
	 *
	 * For simplicity we treat the pre-भागider as fixed (क्रम now).
	 */
	अगर (भागider_exists(pre_भाग)) अणु
		u64 scaled_rate;
		u64 scaled_pre_भाग;

		scaled_rate = scale_rate(pre_भाग, parent_rate);
		scaled_rate = scale_rate(भाग, scaled_rate);
		scaled_pre_भाग = भागider_पढ़ो_scaled(ccu, pre_भाग);
		scaled_parent_rate = DIV_ROUND_CLOSEST_ULL(scaled_rate,
							scaled_pre_भाग);
	पूर्ण अन्यथा अणु
		scaled_parent_rate = scale_rate(भाग, parent_rate);
	पूर्ण

	/*
	 * Compute the best possible भागider and ensure it is in
	 * range.  A fixed भागider can't be changed, so just report
	 * the best we can करो.
	 */
	अगर (!भागider_is_fixed(भाग)) अणु
		best_scaled_भाग = DIV_ROUND_CLOSEST_ULL(scaled_parent_rate,
							rate);
		min_scaled_भाग = scaled_भाग_min(भाग);
		max_scaled_भाग = scaled_भाग_max(भाग);
		अगर (best_scaled_भाग > max_scaled_भाग)
			best_scaled_भाग = max_scaled_भाग;
		अन्यथा अगर (best_scaled_भाग < min_scaled_भाग)
			best_scaled_भाग = min_scaled_भाग;
	पूर्ण अन्यथा अणु
		best_scaled_भाग = भागider_पढ़ो_scaled(ccu, भाग);
	पूर्ण

	/* OK, figure out the resulting rate */
	result = DIV_ROUND_CLOSEST_ULL(scaled_parent_rate, best_scaled_भाग);

	अगर (scaled_भाग)
		*scaled_भाग = best_scaled_भाग;

	वापस (दीर्घ)result;
पूर्ण

/* Common घड़ी parent helpers */

/*
 * For a given parent selector (रेजिस्टर field) value, find the
 * index पूर्णांकo a selector's parent_sel array that contains it.
 * Returns the index, or BAD_CLK_INDEX अगर it's not found.
 */
अटल u8 parent_index(काष्ठा bcm_clk_sel *sel, u8 parent_sel)
अणु
	u8 i;

	BUG_ON(sel->parent_count > (u32)U8_MAX);
	क्रम (i = 0; i < sel->parent_count; i++)
		अगर (sel->parent_sel[i] == parent_sel)
			वापस i;
	वापस BAD_CLK_INDEX;
पूर्ण

/*
 * Fetch the current value of the selector, and translate that पूर्णांकo
 * its corresponding index in the parent array we रेजिस्टरed with
 * the घड़ी framework.
 *
 * Returns parent array index that corresponds with the value found,
 * or BAD_CLK_INDEX अगर the found value is out of range.
 */
अटल u8 selector_पढ़ो_index(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_sel *sel)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg_val;
	u32 parent_sel;
	u8 index;

	/* If there's no selector, there's only one parent */
	अगर (!selector_exists(sel))
		वापस 0;

	/* Get the value in the selector रेजिस्टर */
	flags = ccu_lock(ccu);
	reg_val = __ccu_पढ़ो(ccu, sel->offset);
	ccu_unlock(ccu, flags);

	parent_sel = bitfield_extract(reg_val, sel->shअगरt, sel->width);

	/* Look up that selector's parent array index and वापस it */
	index = parent_index(sel, parent_sel);
	अगर (index == BAD_CLK_INDEX)
		pr_err("%s: out-of-range parent selector %u (%s 0x%04x)\n",
			__func__, parent_sel, ccu->name, sel->offset);

	वापस index;
पूर्ण

/*
 * Commit our desired selector value to the hardware.
 *
 * Returns 0 on success.  Returns -EINVAL क्रम invalid arguments.
 * Returns -ENXIO अगर gating failed, and -EIO अगर a trigger failed.
 */
अटल पूर्णांक
__sel_commit(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate,
			काष्ठा bcm_clk_sel *sel, काष्ठा bcm_clk_trig *trig)
अणु
	u32 parent_sel;
	u32 reg_val;
	bool enabled;
	पूर्णांक ret = 0;

	BUG_ON(!selector_exists(sel));

	/*
	 * If we're just initializing the selector, and no initial
	 * state was defined in the device tree, we just find out
	 * what its current value is rather than updating it.
	 */
	अगर (sel->clk_index == BAD_CLK_INDEX) अणु
		u8 index;

		reg_val = __ccu_पढ़ो(ccu, sel->offset);
		parent_sel = bitfield_extract(reg_val, sel->shअगरt, sel->width);
		index = parent_index(sel, parent_sel);
		अगर (index == BAD_CLK_INDEX)
			वापस -EINVAL;
		sel->clk_index = index;

		वापस 0;
	पूर्ण

	BUG_ON((u32)sel->clk_index >= sel->parent_count);
	parent_sel = sel->parent_sel[sel->clk_index];

	/* Clock needs to be enabled beक्रमe changing the parent */
	enabled = __is_clk_gate_enabled(ccu, gate);
	अगर (!enabled && !__clk_gate(ccu, gate, true))
		वापस -ENXIO;

	/* Replace the selector value and record the result */
	reg_val = __ccu_पढ़ो(ccu, sel->offset);
	reg_val = bitfield_replace(reg_val, sel->shअगरt, sel->width, parent_sel);
	__ccu_ग_लिखो(ccu, sel->offset, reg_val);

	/* If the trigger fails we still want to disable the gate */
	अगर (!__clk_trigger(ccu, trig))
		ret = -EIO;

	/* Disable the घड़ी again अगर it was disabled to begin with */
	अगर (!enabled && !__clk_gate(ccu, gate, false))
		ret = ret ? ret : -ENXIO;	/* वापस first error */

	वापस ret;
पूर्ण

/*
 * Initialize a selector by committing our desired state to hardware
 * without the usual checks to see अगर it's alपढ़ोy set up that way.
 * Returns true अगर successful, false otherwise.
 */
अटल bool sel_init(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate,
			काष्ठा bcm_clk_sel *sel, काष्ठा bcm_clk_trig *trig)
अणु
	अगर (!selector_exists(sel))
		वापस true;
	वापस !__sel_commit(ccu, gate, sel, trig);
पूर्ण

/*
 * Write a new value पूर्णांकo a selector रेजिस्टर to चयन to a
 * dअगरferent parent घड़ी.  Returns 0 on success, or an error code
 * (from __sel_commit()) otherwise.
 */
अटल पूर्णांक selector_ग_लिखो(काष्ठा ccu_data *ccu, काष्ठा bcm_clk_gate *gate,
			काष्ठा bcm_clk_sel *sel, काष्ठा bcm_clk_trig *trig,
			u8 index)
अणु
	अचिन्हित दीर्घ flags;
	u8 previous;
	पूर्णांक ret;

	previous = sel->clk_index;
	अगर (previous == index)
		वापस 0;	/* No change */

	sel->clk_index = index;

	flags = ccu_lock(ccu);
	__ccu_ग_लिखो_enable(ccu);

	ret = __sel_commit(ccu, gate, sel, trig);

	__ccu_ग_लिखो_disable(ccu);
	ccu_unlock(ccu, flags);

	अगर (ret)
		sel->clk_index = previous;	/* Revert the change */

	वापस ret;
पूर्ण

/* Clock operations */

अटल पूर्णांक kona_peri_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा bcm_clk_gate *gate = &bcm_clk->u.peri->gate;

	वापस clk_gate(bcm_clk->ccu, bcm_clk->init_data.name, gate, true);
पूर्ण

अटल व्योम kona_peri_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा bcm_clk_gate *gate = &bcm_clk->u.peri->gate;

	(व्योम)clk_gate(bcm_clk->ccu, bcm_clk->init_data.name, gate, false);
पूर्ण

अटल पूर्णांक kona_peri_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा bcm_clk_gate *gate = &bcm_clk->u.peri->gate;

	वापस is_clk_gate_enabled(bcm_clk->ccu, gate) ? 1 : 0;
पूर्ण

अटल अचिन्हित दीर्घ kona_peri_clk_recalc_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा peri_clk_data *data = bcm_clk->u.peri;

	वापस clk_recalc_rate(bcm_clk->ccu, &data->भाग, &data->pre_भाग,
				parent_rate);
पूर्ण

अटल दीर्घ kona_peri_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा bcm_clk_भाग *भाग = &bcm_clk->u.peri->भाग;

	अगर (!भागider_exists(भाग))
		वापस clk_hw_get_rate(hw);

	/* Quietly aव्योम a zero rate */
	वापस round_rate(bcm_clk->ccu, भाग, &bcm_clk->u.peri->pre_भाग,
				rate ? rate : 1, *parent_rate, शून्य);
पूर्ण

अटल पूर्णांक kona_peri_clk_determine_rate(काष्ठा clk_hw *hw,
					काष्ठा clk_rate_request *req)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा clk_hw *current_parent;
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित दीर्घ best_delta;
	अचिन्हित दीर्घ best_rate;
	u32 parent_count;
	दीर्घ rate;
	u32 which;

	/*
	 * If there is no other parent to choose, use the current one.
	 * Note:  We करोn't honor (or use) CLK_SET_RATE_NO_REPARENT.
	 */
	WARN_ON_ONCE(bcm_clk->init_data.flags & CLK_SET_RATE_NO_REPARENT);
	parent_count = (u32)bcm_clk->init_data.num_parents;
	अगर (parent_count < 2) अणु
		rate = kona_peri_clk_round_rate(hw, req->rate,
						&req->best_parent_rate);
		अगर (rate < 0)
			वापस rate;

		req->rate = rate;
		वापस 0;
	पूर्ण

	/* Unless we can करो better, stick with current parent */
	current_parent = clk_hw_get_parent(hw);
	parent_rate = clk_hw_get_rate(current_parent);
	best_rate = kona_peri_clk_round_rate(hw, req->rate, &parent_rate);
	best_delta = असल(best_rate - req->rate);

	/* Check whether any other parent घड़ी can produce a better result */
	क्रम (which = 0; which < parent_count; which++) अणु
		काष्ठा clk_hw *parent = clk_hw_get_parent_by_index(hw, which);
		अचिन्हित दीर्घ delta;
		अचिन्हित दीर्घ other_rate;

		BUG_ON(!parent);
		अगर (parent == current_parent)
			जारी;

		/* We करोn't support CLK_SET_RATE_PARENT */
		parent_rate = clk_hw_get_rate(parent);
		other_rate = kona_peri_clk_round_rate(hw, req->rate,
						      &parent_rate);
		delta = असल(other_rate - req->rate);
		अगर (delta < best_delta) अणु
			best_delta = delta;
			best_rate = other_rate;
			req->best_parent_hw = parent;
			req->best_parent_rate = parent_rate;
		पूर्ण
	पूर्ण

	req->rate = best_rate;
	वापस 0;
पूर्ण

अटल पूर्णांक kona_peri_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा peri_clk_data *data = bcm_clk->u.peri;
	काष्ठा bcm_clk_sel *sel = &data->sel;
	काष्ठा bcm_clk_trig *trig;
	पूर्णांक ret;

	BUG_ON(index >= sel->parent_count);

	/* If there's only one parent we don't require a selector */
	अगर (!selector_exists(sel))
		वापस 0;

	/*
	 * The regular trigger is used by शेष, but अगर there's a
	 * pre-trigger we want to use that instead.
	 */
	trig = trigger_exists(&data->pre_trig) ? &data->pre_trig
					       : &data->trig;

	ret = selector_ग_लिखो(bcm_clk->ccu, &data->gate, sel, trig, index);
	अगर (ret == -ENXIO) अणु
		pr_err("%s: gating failure for %s\n", __func__,
			bcm_clk->init_data.name);
		ret = -EIO;	/* Don't prolअगरerate weird errors */
	पूर्ण अन्यथा अगर (ret == -EIO) अणु
		pr_err("%s: %strigger failed for %s\n", __func__,
			trig == &data->pre_trig ? "pre-" : "",
			bcm_clk->init_data.name);
	पूर्ण

	वापस ret;
पूर्ण

अटल u8 kona_peri_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा peri_clk_data *data = bcm_clk->u.peri;
	u8 index;

	index = selector_पढ़ो_index(bcm_clk->ccu, &data->sel);

	/* Not all callers would handle an out-of-range value gracefully */
	वापस index == BAD_CLK_INDEX ? 0 : index;
पूर्ण

अटल पूर्णांक kona_peri_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा kona_clk *bcm_clk = to_kona_clk(hw);
	काष्ठा peri_clk_data *data = bcm_clk->u.peri;
	काष्ठा bcm_clk_भाग *भाग = &data->भाग;
	u64 scaled_भाग = 0;
	पूर्णांक ret;

	अगर (parent_rate > (अचिन्हित दीर्घ)दीर्घ_उच्च)
		वापस -EINVAL;

	अगर (rate == clk_hw_get_rate(hw))
		वापस 0;

	अगर (!भागider_exists(भाग))
		वापस rate == parent_rate ? 0 : -EINVAL;

	/*
	 * A fixed भागider can't be changed.  (Nor can a fixed
	 * pre-भागider be, but क्रम now we never actually try to
	 * change that.)  Tolerate a request क्रम a no-op change.
	 */
	अगर (भागider_is_fixed(&data->भाग))
		वापस rate == parent_rate ? 0 : -EINVAL;

	/*
	 * Get the scaled भागisor value needed to achieve a घड़ी
	 * rate as बंद as possible to what was requested, given
	 * the parent घड़ी rate supplied.
	 */
	(व्योम)round_rate(bcm_clk->ccu, भाग, &data->pre_भाग,
				rate ? rate : 1, parent_rate, &scaled_भाग);

	/*
	 * We aren't updating any pre-भागider at this poपूर्णांक, so
	 * we'll use the regular trigger.
	 */
	ret = भागider_ग_लिखो(bcm_clk->ccu, &data->gate, &data->भाग,
				&data->trig, scaled_भाग);
	अगर (ret == -ENXIO) अणु
		pr_err("%s: gating failure for %s\n", __func__,
			bcm_clk->init_data.name);
		ret = -EIO;	/* Don't prolअगरerate weird errors */
	पूर्ण अन्यथा अगर (ret == -EIO) अणु
		pr_err("%s: trigger failed for %s\n", __func__,
			bcm_clk->init_data.name);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा clk_ops kona_peri_clk_ops = अणु
	.enable = kona_peri_clk_enable,
	.disable = kona_peri_clk_disable,
	.is_enabled = kona_peri_clk_is_enabled,
	.recalc_rate = kona_peri_clk_recalc_rate,
	.determine_rate = kona_peri_clk_determine_rate,
	.set_parent = kona_peri_clk_set_parent,
	.get_parent = kona_peri_clk_get_parent,
	.set_rate = kona_peri_clk_set_rate,
पूर्ण;

/* Put a peripheral घड़ी पूर्णांकo its initial state */
अटल bool __peri_clk_init(काष्ठा kona_clk *bcm_clk)
अणु
	काष्ठा ccu_data *ccu = bcm_clk->ccu;
	काष्ठा peri_clk_data *peri = bcm_clk->u.peri;
	स्थिर अक्षर *name = bcm_clk->init_data.name;
	काष्ठा bcm_clk_trig *trig;

	BUG_ON(bcm_clk->type != bcm_clk_peri);

	अगर (!policy_init(ccu, &peri->policy)) अणु
		pr_err("%s: error initializing policy for %s\n",
			__func__, name);
		वापस false;
	पूर्ण
	अगर (!gate_init(ccu, &peri->gate)) अणु
		pr_err("%s: error initializing gate for %s\n", __func__, name);
		वापस false;
	पूर्ण
	अगर (!hyst_init(ccu, &peri->hyst)) अणु
		pr_err("%s: error initializing hyst for %s\n", __func__, name);
		वापस false;
	पूर्ण
	अगर (!भाग_init(ccu, &peri->gate, &peri->भाग, &peri->trig)) अणु
		pr_err("%s: error initializing divider for %s\n", __func__,
			name);
		वापस false;
	पूर्ण

	/*
	 * For the pre-भागider and selector, the pre-trigger is used
	 * अगर it's present, otherwise we just use the regular trigger.
	 */
	trig = trigger_exists(&peri->pre_trig) ? &peri->pre_trig
					       : &peri->trig;

	अगर (!भाग_init(ccu, &peri->gate, &peri->pre_भाग, trig)) अणु
		pr_err("%s: error initializing pre-divider for %s\n", __func__,
			name);
		वापस false;
	पूर्ण

	अगर (!sel_init(ccu, &peri->gate, &peri->sel, trig)) अणु
		pr_err("%s: error initializing selector for %s\n", __func__,
			name);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool __kona_clk_init(काष्ठा kona_clk *bcm_clk)
अणु
	चयन (bcm_clk->type) अणु
	हाल bcm_clk_peri:
		वापस __peri_clk_init(bcm_clk);
	शेष:
		BUG();
	पूर्ण
	वापस false;
पूर्ण

/* Set a CCU and all its घड़ीs पूर्णांकo their desired initial state */
bool __init kona_ccu_init(काष्ठा ccu_data *ccu)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक which;
	काष्ठा kona_clk *kona_clks = ccu->kona_clks;
	bool success = true;

	flags = ccu_lock(ccu);
	__ccu_ग_लिखो_enable(ccu);

	क्रम (which = 0; which < ccu->clk_num; which++) अणु
		काष्ठा kona_clk *bcm_clk = &kona_clks[which];

		अगर (!bcm_clk->ccu)
			जारी;

		success &= __kona_clk_init(bcm_clk);
	पूर्ण

	__ccu_ग_लिखो_disable(ccu);
	ccu_unlock(ccu, flags);
	वापस success;
पूर्ण
