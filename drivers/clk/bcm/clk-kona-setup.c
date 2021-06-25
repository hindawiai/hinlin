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

#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>

#समावेश "clk-kona.h"

/* These are used when a selector or trigger is found to be unneeded */
#घोषणा selector_clear_exists(sel)	((sel)->width = 0)
#घोषणा trigger_clear_exists(trig)	FLAG_CLEAR(trig, TRIG, EXISTS)

/* Validity checking */

अटल bool ccu_data_offsets_valid(काष्ठा ccu_data *ccu)
अणु
	काष्ठा ccu_policy *ccu_policy = &ccu->policy;
	u32 limit;

	limit = ccu->range - माप(u32);
	limit = round_करोwn(limit, माप(u32));
	अगर (ccu_policy_exists(ccu_policy)) अणु
		अगर (ccu_policy->enable.offset > limit) अणु
			pr_err("%s: bad policy enable offset for %s "
					"(%u > %u)\n", __func__,
				ccu->name, ccu_policy->enable.offset, limit);
			वापस false;
		पूर्ण
		अगर (ccu_policy->control.offset > limit) अणु
			pr_err("%s: bad policy control offset for %s "
					"(%u > %u)\n", __func__,
				ccu->name, ccu_policy->control.offset, limit);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool clk_requires_trigger(काष्ठा kona_clk *bcm_clk)
अणु
	काष्ठा peri_clk_data *peri = bcm_clk->u.peri;
	काष्ठा bcm_clk_sel *sel;
	काष्ठा bcm_clk_भाग *भाग;

	अगर (bcm_clk->type != bcm_clk_peri)
		वापस false;

	sel = &peri->sel;
	अगर (sel->parent_count && selector_exists(sel))
		वापस true;

	भाग = &peri->भाग;
	अगर (!भागider_exists(भाग))
		वापस false;

	/* Fixed भागiders करोn't need triggers */
	अगर (!भागider_is_fixed(भाग))
		वापस true;

	भाग = &peri->pre_भाग;

	वापस भागider_exists(भाग) && !भागider_is_fixed(भाग);
पूर्ण

अटल bool peri_clk_data_offsets_valid(काष्ठा kona_clk *bcm_clk)
अणु
	काष्ठा peri_clk_data *peri;
	काष्ठा bcm_clk_policy *policy;
	काष्ठा bcm_clk_gate *gate;
	काष्ठा bcm_clk_hyst *hyst;
	काष्ठा bcm_clk_भाग *भाग;
	काष्ठा bcm_clk_sel *sel;
	काष्ठा bcm_clk_trig *trig;
	स्थिर अक्षर *name;
	u32 range;
	u32 limit;

	BUG_ON(bcm_clk->type != bcm_clk_peri);
	peri = bcm_clk->u.peri;
	name = bcm_clk->init_data.name;
	range = bcm_clk->ccu->range;

	limit = range - माप(u32);
	limit = round_करोwn(limit, माप(u32));

	policy = &peri->policy;
	अगर (policy_exists(policy)) अणु
		अगर (policy->offset > limit) अणु
			pr_err("%s: bad policy offset for %s (%u > %u)\n",
				__func__, name, policy->offset, limit);
			वापस false;
		पूर्ण
	पूर्ण

	gate = &peri->gate;
	hyst = &peri->hyst;
	अगर (gate_exists(gate)) अणु
		अगर (gate->offset > limit) अणु
			pr_err("%s: bad gate offset for %s (%u > %u)\n",
				__func__, name, gate->offset, limit);
			वापस false;
		पूर्ण

		अगर (hyst_exists(hyst)) अणु
			अगर (hyst->offset > limit) अणु
				pr_err("%s: bad hysteresis offset for %s "
					"(%u > %u)\n", __func__,
					name, hyst->offset, limit);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (hyst_exists(hyst)) अणु
		pr_err("%s: hysteresis but no gate for %s\n", __func__, name);
		वापस false;
	पूर्ण

	भाग = &peri->भाग;
	अगर (भागider_exists(भाग)) अणु
		अगर (भाग->u.s.offset > limit) अणु
			pr_err("%s: bad divider offset for %s (%u > %u)\n",
				__func__, name, भाग->u.s.offset, limit);
			वापस false;
		पूर्ण
	पूर्ण

	भाग = &peri->pre_भाग;
	अगर (भागider_exists(भाग)) अणु
		अगर (भाग->u.s.offset > limit) अणु
			pr_err("%s: bad pre-divider offset for %s "
					"(%u > %u)\n",
				__func__, name, भाग->u.s.offset, limit);
			वापस false;
		पूर्ण
	पूर्ण

	sel = &peri->sel;
	अगर (selector_exists(sel)) अणु
		अगर (sel->offset > limit) अणु
			pr_err("%s: bad selector offset for %s (%u > %u)\n",
				__func__, name, sel->offset, limit);
			वापस false;
		पूर्ण
	पूर्ण

	trig = &peri->trig;
	अगर (trigger_exists(trig)) अणु
		अगर (trig->offset > limit) अणु
			pr_err("%s: bad trigger offset for %s (%u > %u)\n",
				__func__, name, trig->offset, limit);
			वापस false;
		पूर्ण
	पूर्ण

	trig = &peri->pre_trig;
	अगर (trigger_exists(trig)) अणु
		अगर (trig->offset > limit) अणु
			pr_err("%s: bad pre-trigger offset for %s (%u > %u)\n",
				__func__, name, trig->offset, limit);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/* A bit position must be less than the number of bits in a 32-bit रेजिस्टर. */
अटल bool bit_posn_valid(u32 bit_posn, स्थिर अक्षर *field_name,
			स्थिर अक्षर *घड़ी_name)
अणु
	u32 limit = BITS_PER_BYTE * माप(u32) - 1;

	अगर (bit_posn > limit) अणु
		pr_err("%s: bad %s bit for %s (%u > %u)\n", __func__,
			field_name, घड़ी_name, bit_posn, limit);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * A bitfield must be at least 1 bit wide.  Both the low-order and
 * high-order bits must lie within a 32-bit रेजिस्टर.  We require
 * fields to be less than 32 bits wide, मुख्यly because we use
 * shअगरting to produce field masks, and shअगरting a full word width
 * is not well-defined by the C standard.
 */
अटल bool bitfield_valid(u32 shअगरt, u32 width, स्थिर अक्षर *field_name,
			स्थिर अक्षर *घड़ी_name)
अणु
	u32 limit = BITS_PER_BYTE * माप(u32);

	अगर (!width) अणु
		pr_err("%s: bad %s field width 0 for %s\n", __func__,
			field_name, घड़ी_name);
		वापस false;
	पूर्ण
	अगर (shअगरt + width > limit) अणु
		pr_err("%s: bad %s for %s (%u + %u > %u)\n", __func__,
			field_name, घड़ी_name, shअगरt, width, limit);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool
ccu_policy_valid(काष्ठा ccu_policy *ccu_policy, स्थिर अक्षर *ccu_name)
अणु
	काष्ठा bcm_lvm_en *enable = &ccu_policy->enable;
	काष्ठा bcm_policy_ctl *control;

	अगर (!bit_posn_valid(enable->bit, "policy enable", ccu_name))
		वापस false;

	control = &ccu_policy->control;
	अगर (!bit_posn_valid(control->go_bit, "policy control GO", ccu_name))
		वापस false;

	अगर (!bit_posn_valid(control->atl_bit, "policy control ATL", ccu_name))
		वापस false;

	अगर (!bit_posn_valid(control->ac_bit, "policy control AC", ccu_name))
		वापस false;

	वापस true;
पूर्ण

अटल bool policy_valid(काष्ठा bcm_clk_policy *policy, स्थिर अक्षर *घड़ी_name)
अणु
	अगर (!bit_posn_valid(policy->bit, "policy", घड़ी_name))
		वापस false;

	वापस true;
पूर्ण

/*
 * All gates, अगर defined, have a status bit, and क्रम hardware-only
 * gates, that's it.  Gates that can be software controlled also
 * have an enable bit.  And a gate that can be hardware or software
 * controlled will have a hardware/software select bit.
 */
अटल bool gate_valid(काष्ठा bcm_clk_gate *gate, स्थिर अक्षर *field_name,
			स्थिर अक्षर *घड़ी_name)
अणु
	अगर (!bit_posn_valid(gate->status_bit, "gate status", घड़ी_name))
		वापस false;

	अगर (gate_is_sw_controllable(gate)) अणु
		अगर (!bit_posn_valid(gate->en_bit, "gate enable", घड़ी_name))
			वापस false;

		अगर (gate_is_hw_controllable(gate)) अणु
			अगर (!bit_posn_valid(gate->hw_sw_sel_bit,
						"gate hw/sw select",
						घड़ी_name))
				वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG_ON(!gate_is_hw_controllable(gate));
	पूर्ण

	वापस true;
पूर्ण

अटल bool hyst_valid(काष्ठा bcm_clk_hyst *hyst, स्थिर अक्षर *घड़ी_name)
अणु
	अगर (!bit_posn_valid(hyst->en_bit, "hysteresis enable", घड़ी_name))
		वापस false;

	अगर (!bit_posn_valid(hyst->val_bit, "hysteresis value", घड़ी_name))
		वापस false;

	वापस true;
पूर्ण

/*
 * A selector bitfield must be valid.  Its parent_sel array must
 * also be reasonable क्रम the field.
 */
अटल bool sel_valid(काष्ठा bcm_clk_sel *sel, स्थिर अक्षर *field_name,
			स्थिर अक्षर *घड़ी_name)
अणु
	अगर (!bitfield_valid(sel->shअगरt, sel->width, field_name, घड़ी_name))
		वापस false;

	अगर (sel->parent_count) अणु
		u32 max_sel;
		u32 limit;

		/*
		 * Make sure the selector field can hold all the
		 * selector values we expect to be able to use.  A
		 * घड़ी only needs to have a selector defined अगर it
		 * has more than one parent.  And in that हाल the
		 * highest selector value will be in the last entry
		 * in the array.
		 */
		max_sel = sel->parent_sel[sel->parent_count - 1];
		limit = (1 << sel->width) - 1;
		अगर (max_sel > limit) अणु
			pr_err("%s: bad selector for %s "
					"(%u needs > %u bits)\n",
				__func__, घड़ी_name, max_sel,
				sel->width);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("%s: ignoring selector for %s (no parents)\n",
			__func__, घड़ी_name);
		selector_clear_exists(sel);
		kमुक्त(sel->parent_sel);
		sel->parent_sel = शून्य;
	पूर्ण

	वापस true;
पूर्ण

/*
 * A fixed भागider just needs to be non-zero.  A variable भागider
 * has to have a valid भागider bitfield, and अगर it has a fraction,
 * the width of the fraction must not be no more than the width of
 * the भागider as a whole.
 */
अटल bool भाग_valid(काष्ठा bcm_clk_भाग *भाग, स्थिर अक्षर *field_name,
			स्थिर अक्षर *घड़ी_name)
अणु
	अगर (भागider_is_fixed(भाग)) अणु
		/* Any fixed भागider value but 0 is OK */
		अगर (भाग->u.fixed == 0) अणु
			pr_err("%s: bad %s fixed value 0 for %s\n", __func__,
				field_name, घड़ी_name);
			वापस false;
		पूर्ण
		वापस true;
	पूर्ण
	अगर (!bitfield_valid(भाग->u.s.shअगरt, भाग->u.s.width,
				field_name, घड़ी_name))
		वापस false;

	अगर (भागider_has_fraction(भाग))
		अगर (भाग->u.s.frac_width > भाग->u.s.width) अणु
			pr_warn("%s: bad %s fraction width for %s (%u > %u)\n",
				__func__, field_name, घड़ी_name,
				भाग->u.s.frac_width, भाग->u.s.width);
			वापस false;
		पूर्ण

	वापस true;
पूर्ण

/*
 * If a घड़ी has two भागiders, the combined number of fractional
 * bits must be representable in a 32-bit अचिन्हित value.  This
 * is because we scale up a भागidend using both भागiders beक्रमe
 * भागiding to improve accuracy, and we need to aव्योम overflow.
 */
अटल bool kona_भागiders_valid(काष्ठा kona_clk *bcm_clk)
अणु
	काष्ठा peri_clk_data *peri = bcm_clk->u.peri;
	काष्ठा bcm_clk_भाग *भाग;
	काष्ठा bcm_clk_भाग *pre_भाग;
	u32 limit;

	BUG_ON(bcm_clk->type != bcm_clk_peri);

	अगर (!भागider_exists(&peri->भाग) || !भागider_exists(&peri->pre_भाग))
		वापस true;

	भाग = &peri->भाग;
	pre_भाग = &peri->pre_भाग;
	अगर (भागider_is_fixed(भाग) || भागider_is_fixed(pre_भाग))
		वापस true;

	limit = BITS_PER_BYTE * माप(u32);

	वापस भाग->u.s.frac_width + pre_भाग->u.s.frac_width <= limit;
पूर्ण


/* A trigger just needs to represent a valid bit position */
अटल bool trig_valid(काष्ठा bcm_clk_trig *trig, स्थिर अक्षर *field_name,
			स्थिर अक्षर *घड़ी_name)
अणु
	वापस bit_posn_valid(trig->bit, field_name, घड़ी_name);
पूर्ण

/* Determine whether the set of peripheral घड़ी रेजिस्टरs are valid. */
अटल bool
peri_clk_data_valid(काष्ठा kona_clk *bcm_clk)
अणु
	काष्ठा peri_clk_data *peri;
	काष्ठा bcm_clk_policy *policy;
	काष्ठा bcm_clk_gate *gate;
	काष्ठा bcm_clk_hyst *hyst;
	काष्ठा bcm_clk_sel *sel;
	काष्ठा bcm_clk_भाग *भाग;
	काष्ठा bcm_clk_भाग *pre_भाग;
	काष्ठा bcm_clk_trig *trig;
	स्थिर अक्षर *name;

	BUG_ON(bcm_clk->type != bcm_clk_peri);

	/*
	 * First validate रेजिस्टर offsets.  This is the only place
	 * where we need something from the ccu, so we करो these
	 * together.
	 */
	अगर (!peri_clk_data_offsets_valid(bcm_clk))
		वापस false;

	peri = bcm_clk->u.peri;
	name = bcm_clk->init_data.name;

	policy = &peri->policy;
	अगर (policy_exists(policy) && !policy_valid(policy, name))
		वापस false;

	gate = &peri->gate;
	अगर (gate_exists(gate) && !gate_valid(gate, "gate", name))
		वापस false;

	hyst = &peri->hyst;
	अगर (hyst_exists(hyst) && !hyst_valid(hyst, name))
		वापस false;

	sel = &peri->sel;
	अगर (selector_exists(sel)) अणु
		अगर (!sel_valid(sel, "selector", name))
			वापस false;

	पूर्ण अन्यथा अगर (sel->parent_count > 1) अणु
		pr_err("%s: multiple parents but no selector for %s\n",
			__func__, name);

		वापस false;
	पूर्ण

	भाग = &peri->भाग;
	pre_भाग = &peri->pre_भाग;
	अगर (भागider_exists(भाग)) अणु
		अगर (!भाग_valid(भाग, "divider", name))
			वापस false;

		अगर (भागider_exists(pre_भाग))
			अगर (!भाग_valid(pre_भाग, "pre-divider", name))
				वापस false;
	पूर्ण अन्यथा अगर (भागider_exists(pre_भाग)) अणु
		pr_err("%s: pre-divider but no divider for %s\n", __func__,
			name);
		वापस false;
	पूर्ण

	trig = &peri->trig;
	अगर (trigger_exists(trig)) अणु
		अगर (!trig_valid(trig, "trigger", name))
			वापस false;

		अगर (trigger_exists(&peri->pre_trig)) अणु
			अगर (!trig_valid(trig, "pre-trigger", name)) अणु
				वापस false;
			पूर्ण
		पूर्ण
		अगर (!clk_requires_trigger(bcm_clk)) अणु
			pr_warn("%s: ignoring trigger for %s (not needed)\n",
				__func__, name);
			trigger_clear_exists(trig);
		पूर्ण
	पूर्ण अन्यथा अगर (trigger_exists(&peri->pre_trig)) अणु
		pr_err("%s: pre-trigger but no trigger for %s\n", __func__,
			name);
		वापस false;
	पूर्ण अन्यथा अगर (clk_requires_trigger(bcm_clk)) अणु
		pr_err("%s: required trigger missing for %s\n", __func__,
			name);
		वापस false;
	पूर्ण

	वापस kona_भागiders_valid(bcm_clk);
पूर्ण

अटल bool kona_clk_valid(काष्ठा kona_clk *bcm_clk)
अणु
	चयन (bcm_clk->type) अणु
	हाल bcm_clk_peri:
		अगर (!peri_clk_data_valid(bcm_clk))
			वापस false;
		अवरोध;
	शेष:
		pr_err("%s: unrecognized clock type (%d)\n", __func__,
			(पूर्णांक)bcm_clk->type);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Scan an array of parent घड़ी names to determine whether there
 * are any entries containing BAD_CLK_NAME.  Such entries are
 * placeholders क्रम non-supported घड़ीs.  Keep track of the
 * position of each घड़ी name in the original array.
 *
 * Allocates an array of poपूर्णांकers to to hold the names of all
 * non-null entries in the original array, and वापसs a poपूर्णांकer to
 * that array in *names.  This will be used क्रम रेजिस्टरing the
 * घड़ी with the common घड़ी code.  On successful वापस,
 * *count indicates how many entries are in that names array.
 *
 * If there is more than one entry in the resulting names array,
 * another array is allocated to record the parent selector value
 * क्रम each (defined) parent घड़ी.  This is the value that
 * represents this parent घड़ी in the घड़ी's source selector
 * रेजिस्टर.  The position of the घड़ी in the original parent array
 * defines that selector value.  The number of entries in this array
 * is the same as the number of entries in the parent names array.
 *
 * The array of selector values is वापसed.  If the घड़ी has no
 * parents, no selector is required and a null poपूर्णांकer is वापसed.
 *
 * Returns a null poपूर्णांकer अगर the घड़ी names array supplied was
 * null.  (This is not an error.)
 *
 * Returns a poपूर्णांकer-coded error अगर an error occurs.
 */
अटल u32 *parent_process(स्थिर अक्षर *घड़ीs[],
			u32 *count, स्थिर अक्षर ***names)
अणु
	अटल स्थिर अक्षर **parent_names;
	अटल u32 *parent_sel;
	स्थिर अक्षर **घड़ी;
	u32 parent_count;
	u32 bad_count = 0;
	u32 orig_count;
	u32 i;
	u32 j;

	*count = 0;	/* In हाल of early वापस */
	*names = शून्य;
	अगर (!घड़ीs)
		वापस शून्य;

	/*
	 * Count the number of names in the null-terminated array,
	 * and find out how many of those are actually घड़ी names.
	 */
	क्रम (घड़ी = घड़ीs; *घड़ी; घड़ी++)
		अगर (*घड़ी == BAD_CLK_NAME)
			bad_count++;
	orig_count = (u32)(घड़ी - घड़ीs);
	parent_count = orig_count - bad_count;

	/* If all घड़ीs are unsupported, we treat it as no घड़ी */
	अगर (!parent_count)
		वापस शून्य;

	/* Aव्योम exceeding our parent घड़ी limit */
	अगर (parent_count > PARENT_COUNT_MAX) अणु
		pr_err("%s: too many parents (%u > %u)\n", __func__,
			parent_count, PARENT_COUNT_MAX);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * There is one parent name क्रम each defined parent घड़ी.
	 * We also मुख्यtain an array containing the selector value
	 * क्रम each defined घड़ी.  If there's only one घड़ी, the
	 * selector is not required, but we allocate space क्रम the
	 * array anyway to keep things simple.
	 */
	parent_names = kदो_स्मृति_array(parent_count, माप(*parent_names),
			       GFP_KERNEL);
	अगर (!parent_names)
		वापस ERR_PTR(-ENOMEM);

	/* There is at least one parent, so allocate a selector array */
	parent_sel = kदो_स्मृति_array(parent_count, माप(*parent_sel),
				   GFP_KERNEL);
	अगर (!parent_sel) अणु
		kमुक्त(parent_names);

		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Now fill in the parent names and selector arrays */
	क्रम (i = 0, j = 0; i < orig_count; i++) अणु
		अगर (घड़ीs[i] != BAD_CLK_NAME) अणु
			parent_names[j] = घड़ीs[i];
			parent_sel[j] = i;
			j++;
		पूर्ण
	पूर्ण
	*names = parent_names;
	*count = parent_count;

	वापस parent_sel;
पूर्ण

अटल पूर्णांक
clk_sel_setup(स्थिर अक्षर **घड़ीs, काष्ठा bcm_clk_sel *sel,
		काष्ठा clk_init_data *init_data)
अणु
	स्थिर अक्षर **parent_names = शून्य;
	u32 parent_count = 0;
	u32 *parent_sel;

	/*
	 * If a peripheral घड़ी has multiple parents, the value
	 * used by the hardware to select that parent is represented
	 * by the parent घड़ी's position in the "clocks" list.  Some
	 * values करोn't have defined or supported घड़ीs; these will
	 * have BAD_CLK_NAME entries in the parents[] array.  The
	 * list is terminated by a शून्य entry.
	 *
	 * We need to supply (only) the names of defined parent
	 * घड़ीs when रेजिस्टरing a घड़ी though, so we use an
	 * array of parent selector values to map between the
	 * indexes the common घड़ी code uses and the selector
	 * values we need.
	 */
	parent_sel = parent_process(घड़ीs, &parent_count, &parent_names);
	अगर (IS_ERR(parent_sel)) अणु
		पूर्णांक ret = PTR_ERR(parent_sel);

		pr_err("%s: error processing parent clocks for %s (%d)\n",
			__func__, init_data->name, ret);

		वापस ret;
	पूर्ण

	init_data->parent_names = parent_names;
	init_data->num_parents = parent_count;

	sel->parent_count = parent_count;
	sel->parent_sel = parent_sel;

	वापस 0;
पूर्ण

अटल व्योम clk_sel_tearकरोwn(काष्ठा bcm_clk_sel *sel,
		काष्ठा clk_init_data *init_data)
अणु
	kमुक्त(sel->parent_sel);
	sel->parent_sel = शून्य;
	sel->parent_count = 0;

	init_data->num_parents = 0;
	kमुक्त(init_data->parent_names);
	init_data->parent_names = शून्य;
पूर्ण

अटल व्योम peri_clk_tearकरोwn(काष्ठा peri_clk_data *data,
				काष्ठा clk_init_data *init_data)
अणु
	clk_sel_tearकरोwn(&data->sel, init_data);
पूर्ण

/*
 * Caller is responsible क्रम मुक्तing the parent_names[] and
 * parent_sel[] arrays in the peripheral घड़ी's "data" काष्ठाure
 * that can be asचिन्हित अगर the घड़ी has one or more parent घड़ीs
 * associated with it.
 */
अटल पूर्णांक
peri_clk_setup(काष्ठा peri_clk_data *data, काष्ठा clk_init_data *init_data)
अणु
	init_data->flags = CLK_IGNORE_UNUSED;

	वापस clk_sel_setup(data->घड़ीs, &data->sel, init_data);
पूर्ण

अटल व्योम bcm_clk_tearकरोwn(काष्ठा kona_clk *bcm_clk)
अणु
	चयन (bcm_clk->type) अणु
	हाल bcm_clk_peri:
		peri_clk_tearकरोwn(bcm_clk->u.data, &bcm_clk->init_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	bcm_clk->u.data = शून्य;
	bcm_clk->type = bcm_clk_none;
पूर्ण

अटल व्योम kona_clk_tearकरोwn(काष्ठा clk_hw *hw)
अणु
	काष्ठा kona_clk *bcm_clk;

	अगर (!hw)
		वापस;

	clk_hw_unरेजिस्टर(hw);

	bcm_clk = to_kona_clk(hw);
	bcm_clk_tearकरोwn(bcm_clk);
पूर्ण

अटल पूर्णांक kona_clk_setup(काष्ठा kona_clk *bcm_clk)
अणु
	पूर्णांक ret;
	काष्ठा clk_init_data *init_data = &bcm_clk->init_data;

	चयन (bcm_clk->type) अणु
	हाल bcm_clk_peri:
		ret = peri_clk_setup(bcm_clk->u.data, init_data);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		pr_err("%s: clock type %d invalid for %s\n", __func__,
			(पूर्णांक)bcm_clk->type, init_data->name);
		वापस -EINVAL;
	पूर्ण

	/* Make sure everything makes sense beक्रमe we set it up */
	अगर (!kona_clk_valid(bcm_clk)) अणु
		pr_err("%s: clock data invalid for %s\n", __func__,
			init_data->name);
		ret = -EINVAL;
		जाओ out_tearकरोwn;
	पूर्ण

	bcm_clk->hw.init = init_data;
	ret = clk_hw_रेजिस्टर(शून्य, &bcm_clk->hw);
	अगर (ret) अणु
		pr_err("%s: error registering clock %s (%d)\n", __func__,
			init_data->name, ret);
		जाओ out_tearकरोwn;
	पूर्ण

	वापस 0;
out_tearकरोwn:
	bcm_clk_tearकरोwn(bcm_clk);

	वापस ret;
पूर्ण

अटल व्योम ccu_clks_tearकरोwn(काष्ठा ccu_data *ccu)
अणु
	u32 i;

	क्रम (i = 0; i < ccu->clk_num; i++)
		kona_clk_tearकरोwn(&ccu->kona_clks[i].hw);
पूर्ण

अटल व्योम kona_ccu_tearकरोwn(काष्ठा ccu_data *ccu)
अणु
	अगर (!ccu->base)
		वापस;

	of_clk_del_provider(ccu->node);	/* safe अगर never added */
	ccu_clks_tearकरोwn(ccu);
	of_node_put(ccu->node);
	ccu->node = शून्य;
	iounmap(ccu->base);
	ccu->base = शून्य;
पूर्ण

अटल bool ccu_data_valid(काष्ठा ccu_data *ccu)
अणु
	काष्ठा ccu_policy *ccu_policy;

	अगर (!ccu_data_offsets_valid(ccu))
		वापस false;

	ccu_policy = &ccu->policy;
	अगर (ccu_policy_exists(ccu_policy))
		अगर (!ccu_policy_valid(ccu_policy, ccu->name))
			वापस false;

	वापस true;
पूर्ण

अटल काष्ठा clk_hw *
of_clk_kona_onecell_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा ccu_data *ccu = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= ccu->clk_num) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &ccu->kona_clks[idx].hw;
पूर्ण

/*
 * Set up a CCU.  Call the provided ccu_clks_setup callback to
 * initialize the array of घड़ीs provided by the CCU.
 */
व्योम __init kona_dt_ccu_setup(काष्ठा ccu_data *ccu,
			काष्ठा device_node *node)
अणु
	काष्ठा resource res = अणु 0 पूर्ण;
	resource_माप_प्रकार range;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret) अणु
		pr_err("%s: no valid CCU registers found for %pOFn\n", __func__,
			node);
		जाओ out_err;
	पूर्ण

	range = resource_size(&res);
	अगर (range > (resource_माप_प्रकार)U32_MAX) अणु
		pr_err("%s: address range too large for %pOFn\n", __func__,
			node);
		जाओ out_err;
	पूर्ण

	ccu->range = (u32)range;

	अगर (!ccu_data_valid(ccu)) अणु
		pr_err("%s: ccu data not valid for %pOFn\n", __func__, node);
		जाओ out_err;
	पूर्ण

	ccu->base = ioremap(res.start, ccu->range);
	अगर (!ccu->base) अणु
		pr_err("%s: unable to map CCU registers for %pOFn\n", __func__,
			node);
		जाओ out_err;
	पूर्ण
	ccu->node = of_node_get(node);

	/*
	 * Set up each defined kona घड़ी and save the result in
	 * the घड़ी framework घड़ी array (in ccu->data).  Then
	 * रेजिस्टर as a provider क्रम these घड़ीs.
	 */
	क्रम (i = 0; i < ccu->clk_num; i++) अणु
		अगर (!ccu->kona_clks[i].ccu)
			जारी;
		kona_clk_setup(&ccu->kona_clks[i]);
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_kona_onecell_get, ccu);
	अगर (ret) अणु
		pr_err("%s: error adding ccu %pOFn as provider (%d)\n", __func__,
				node, ret);
		जाओ out_err;
	पूर्ण

	अगर (!kona_ccu_init(ccu))
		pr_err("Broadcom %pOFn initialization had errors\n", node);

	वापस;
out_err:
	kona_ccu_tearकरोwn(ccu);
	pr_err("Broadcom %pOFn setup aborted\n", node);
पूर्ण
