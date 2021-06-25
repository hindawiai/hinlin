<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (c) 2010-2011 Jeremy Kerr <jeremy.kerr@canonical.com>
 *  Copyright (C) 2011-2012 Linaro Ltd <mturquette@linaro.org>
 */
#अगर_अघोषित __LINUX_CLK_PROVIDER_H
#घोषणा __LINUX_CLK_PROVIDER_H

#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>

/*
 * flags used across common काष्ठा clk.  these flags should only affect the
 * top-level framework.  custom flags क्रम dealing with hardware specअगरics
 * beदीर्घ in काष्ठा clk_foo
 *
 * Please update clk_flags[] in drivers/clk/clk.c when making changes here!
 */
#घोषणा CLK_SET_RATE_GATE	BIT(0) /* must be gated across rate change */
#घोषणा CLK_SET_PARENT_GATE	BIT(1) /* must be gated across re-parent */
#घोषणा CLK_SET_RATE_PARENT	BIT(2) /* propagate rate change up one level */
#घोषणा CLK_IGNORE_UNUSED	BIT(3) /* करो not gate even अगर unused */
				/* unused */
				/* unused */
#घोषणा CLK_GET_RATE_NOCACHE	BIT(6) /* करो not use the cached clk rate */
#घोषणा CLK_SET_RATE_NO_REPARENT BIT(7) /* करोn't re-parent on rate change */
#घोषणा CLK_GET_ACCURACY_NOCACHE BIT(8) /* करो not use the cached clk accuracy */
#घोषणा CLK_RECALC_NEW_RATES	BIT(9) /* recalc rates after notअगरications */
#घोषणा CLK_SET_RATE_UNGATE	BIT(10) /* घड़ी needs to run to set rate */
#घोषणा CLK_IS_CRITICAL		BIT(11) /* करो not gate, ever */
/* parents need enable during gate/ungate, set rate and re-parent */
#घोषणा CLK_OPS_PARENT_ENABLE	BIT(12)
/* duty cycle call may be क्रमwarded to the parent घड़ी */
#घोषणा CLK_DUTY_CYCLE_PARENT	BIT(13)

काष्ठा clk;
काष्ठा clk_hw;
काष्ठा clk_core;
काष्ठा dentry;

/**
 * काष्ठा clk_rate_request - Structure encoding the clk स्थिरraपूर्णांकs that
 * a घड़ी user might require.
 *
 * @rate:		Requested घड़ी rate. This field will be adjusted by
 *			घड़ी drivers according to hardware capabilities.
 * @min_rate:		Minimum rate imposed by clk users.
 * @max_rate:		Maximum rate imposed by clk users.
 * @best_parent_rate:	The best parent rate a parent can provide to fulfill the
 *			requested स्थिरraपूर्णांकs.
 * @best_parent_hw:	The most appropriate parent घड़ी that fulfills the
 *			requested स्थिरraपूर्णांकs.
 *
 */
काष्ठा clk_rate_request अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ min_rate;
	अचिन्हित दीर्घ max_rate;
	अचिन्हित दीर्घ best_parent_rate;
	काष्ठा clk_hw *best_parent_hw;
पूर्ण;

/**
 * काष्ठा clk_duty - Struture encoding the duty cycle ratio of a घड़ी
 *
 * @num:	Numerator of the duty cycle ratio
 * @den:	Denominator of the duty cycle ratio
 */
काष्ठा clk_duty अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक den;
पूर्ण;

/**
 * काष्ठा clk_ops -  Callback operations क्रम hardware घड़ीs; these are to
 * be provided by the घड़ी implementation, and will be called by drivers
 * through the clk_* api.
 *
 * @prepare:	Prepare the घड़ी क्रम enabling. This must not वापस until
 *		the घड़ी is fully prepared, and it's safe to call clk_enable.
 *		This callback is पूर्णांकended to allow घड़ी implementations to
 *		करो any initialisation that may sleep. Called with
 *		prepare_lock held.
 *
 * @unprepare:	Release the घड़ी from its prepared state. This will typically
 *		unकरो any work करोne in the @prepare callback. Called with
 *		prepare_lock held.
 *
 * @is_prepared: Queries the hardware to determine अगर the घड़ी is prepared.
 *		This function is allowed to sleep. Optional, अगर this op is not
 *		set then the prepare count will be used.
 *
 * @unprepare_unused: Unprepare the घड़ी atomically.  Only called from
 *		clk_disable_unused क्रम prepare घड़ीs with special needs.
 *		Called with prepare mutex held. This function may sleep.
 *
 * @enable:	Enable the घड़ी atomically. This must not वापस until the
 *		घड़ी is generating a valid घड़ी संकेत, usable by consumer
 *		devices. Called with enable_lock held. This function must not
 *		sleep.
 *
 * @disable:	Disable the घड़ी atomically. Called with enable_lock held.
 *		This function must not sleep.
 *
 * @is_enabled:	Queries the hardware to determine अगर the घड़ी is enabled.
 *		This function must not sleep. Optional, अगर this op is not
 *		set then the enable count will be used.
 *
 * @disable_unused: Disable the घड़ी atomically.  Only called from
 *		clk_disable_unused क्रम gate घड़ीs with special needs.
 *		Called with enable_lock held.  This function must not
 *		sleep.
 *
 * @save_context: Save the context of the घड़ी in prepration क्रम घातeroff.
 *
 * @restore_context: Restore the context of the घड़ी after a restoration
 *		of घातer.
 *
 * @recalc_rate	Recalculate the rate of this घड़ी, by querying hardware. The
 *		parent rate is an input parameter.  It is up to the caller to
 *		ensure that the prepare_mutex is held across this call.
 *		Returns the calculated rate.  Optional, but recommended - अगर
 *		this op is not set then घड़ी rate will be initialized to 0.
 *
 * @round_rate:	Given a target rate as input, वापसs the बंदst rate actually
 *		supported by the घड़ी. The parent rate is an input/output
 *		parameter.
 *
 * @determine_rate: Given a target rate as input, वापसs the बंदst rate
 *		actually supported by the घड़ी, and optionally the parent घड़ी
 *		that should be used to provide the घड़ी rate.
 *
 * @set_parent:	Change the input source of this घड़ी; क्रम घड़ीs with multiple
 *		possible parents specअगरy a new parent by passing in the index
 *		as a u8 corresponding to the parent in either the .parent_names
 *		or .parents arrays.  This function in affect translates an
 *		array index पूर्णांकo the value programmed पूर्णांकo the hardware.
 *		Returns 0 on success, -EERROR otherwise.
 *
 * @get_parent:	Queries the hardware to determine the parent of a घड़ी.  The
 *		वापस value is a u8 which specअगरies the index corresponding to
 *		the parent घड़ी.  This index can be applied to either the
 *		.parent_names or .parents arrays.  In लघु, this function
 *		translates the parent value पढ़ो from hardware पूर्णांकo an array
 *		index.  Currently only called when the घड़ी is initialized by
 *		__clk_init.  This callback is mandatory क्रम घड़ीs with
 *		multiple parents.  It is optional (and unnecessary) क्रम घड़ीs
 *		with 0 or 1 parents.
 *
 * @set_rate:	Change the rate of this घड़ी. The requested rate is specअगरied
 *		by the second argument, which should typically be the वापस
 *		of .round_rate call.  The third argument gives the parent rate
 *		which is likely helpful क्रम most .set_rate implementation.
 *		Returns 0 on success, -EERROR otherwise.
 *
 * @set_rate_and_parent: Change the rate and the parent of this घड़ी. The
 *		requested rate is specअगरied by the second argument, which
 *		should typically be the वापस of .round_rate call.  The
 *		third argument gives the parent rate which is likely helpful
 *		क्रम most .set_rate_and_parent implementation. The fourth
 *		argument gives the parent index. This callback is optional (and
 *		unnecessary) क्रम घड़ीs with 0 or 1 parents as well as
 *		क्रम घड़ीs that can tolerate चयनing the rate and the parent
 *		separately via calls to .set_parent and .set_rate.
 *		Returns 0 on success, -EERROR otherwise.
 *
 * @recalc_accuracy: Recalculate the accuracy of this घड़ी. The घड़ी accuracy
 *		is expressed in ppb (parts per billion). The parent accuracy is
 *		an input parameter.
 *		Returns the calculated accuracy.  Optional - अगर	this op is not
 *		set then घड़ी accuracy will be initialized to parent accuracy
 *		or 0 (perfect घड़ी) अगर घड़ी has no parent.
 *
 * @get_phase:	Queries the hardware to get the current phase of a घड़ी.
 *		Returned values are 0-359 degrees on success, negative
 *		error codes on failure.
 *
 * @set_phase:	Shअगरt the phase this घड़ी संकेत in degrees specअगरied
 *		by the second argument. Valid values क्रम degrees are
 *		0-359. Return 0 on success, otherwise -EERROR.
 *
 * @get_duty_cycle: Queries the hardware to get the current duty cycle ratio
 *              of a घड़ी. Returned values denominator cannot be 0 and must be
 *              superior or equal to the numerator.
 *
 * @set_duty_cycle: Apply the duty cycle ratio to this घड़ी संकेत specअगरied by
 *              the numerator (2nd argurment) and denominator (3rd  argument).
 *              Argument must be a valid ratio (denominator > 0
 *              and >= numerator) Return 0 on success, otherwise -EERROR.
 *
 * @init:	Perक्रमm platक्रमm-specअगरic initialization magic.
 *		This is not used by any of the basic घड़ी types.
 *		This callback exist क्रम HW which needs to perक्रमm some
 *		initialisation magic क्रम CCF to get an accurate view of the
 *		घड़ी. It may also be used dynamic resource allocation is
 *		required. It shall not used to deal with घड़ी parameters,
 *		such as rate or parents.
 *		Returns 0 on success, -EERROR otherwise.
 *
 * @terminate:  Free any resource allocated by init.
 *
 * @debug_init:	Set up type-specअगरic debugfs entries क्रम this घड़ी.  This
 *		is called once, after the debugfs directory entry क्रम this
 *		घड़ी has been created.  The dentry poपूर्णांकer representing that
 *		directory is provided as an argument.  Called with
 *		prepare_lock held.  Returns 0 on success, -EERROR otherwise.
 *
 *
 * The clk_enable/clk_disable and clk_prepare/clk_unprepare pairs allow
 * implementations to split any work between atomic (enable) and sleepable
 * (prepare) contexts.  If enabling a घड़ी requires code that might sleep,
 * this must be करोne in clk_prepare.  Clock enable code that will never be
 * called in a sleepable context may be implemented in clk_enable.
 *
 * Typically, drivers will call clk_prepare when a घड़ी may be needed later
 * (eg. when a device is खोलोed), and clk_enable when the घड़ी is actually
 * required (eg. from an पूर्णांकerrupt). Note that clk_prepare MUST have been
 * called beक्रमe clk_enable.
 */
काष्ठा clk_ops अणु
	पूर्णांक		(*prepare)(काष्ठा clk_hw *hw);
	व्योम		(*unprepare)(काष्ठा clk_hw *hw);
	पूर्णांक		(*is_prepared)(काष्ठा clk_hw *hw);
	व्योम		(*unprepare_unused)(काष्ठा clk_hw *hw);
	पूर्णांक		(*enable)(काष्ठा clk_hw *hw);
	व्योम		(*disable)(काष्ठा clk_hw *hw);
	पूर्णांक		(*is_enabled)(काष्ठा clk_hw *hw);
	व्योम		(*disable_unused)(काष्ठा clk_hw *hw);
	पूर्णांक		(*save_context)(काष्ठा clk_hw *hw);
	व्योम		(*restore_context)(काष्ठा clk_hw *hw);
	अचिन्हित दीर्घ	(*recalc_rate)(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate);
	दीर्घ		(*round_rate)(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *parent_rate);
	पूर्णांक		(*determine_rate)(काष्ठा clk_hw *hw,
					  काष्ठा clk_rate_request *req);
	पूर्णांक		(*set_parent)(काष्ठा clk_hw *hw, u8 index);
	u8		(*get_parent)(काष्ठा clk_hw *hw);
	पूर्णांक		(*set_rate)(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate);
	पूर्णांक		(*set_rate_and_parent)(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate, u8 index);
	अचिन्हित दीर्घ	(*recalc_accuracy)(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_accuracy);
	पूर्णांक		(*get_phase)(काष्ठा clk_hw *hw);
	पूर्णांक		(*set_phase)(काष्ठा clk_hw *hw, पूर्णांक degrees);
	पूर्णांक		(*get_duty_cycle)(काष्ठा clk_hw *hw,
					  काष्ठा clk_duty *duty);
	पूर्णांक		(*set_duty_cycle)(काष्ठा clk_hw *hw,
					  काष्ठा clk_duty *duty);
	पूर्णांक		(*init)(काष्ठा clk_hw *hw);
	व्योम		(*terminate)(काष्ठा clk_hw *hw);
	व्योम		(*debug_init)(काष्ठा clk_hw *hw, काष्ठा dentry *dentry);
पूर्ण;

/**
 * काष्ठा clk_parent_data - clk parent inक्रमmation
 * @hw: parent clk_hw poपूर्णांकer (used क्रम clk providers with पूर्णांकernal clks)
 * @fw_name: parent name local to provider रेजिस्टरing clk
 * @name: globally unique parent name (used as a fallback)
 * @index: parent index local to provider रेजिस्टरing clk (अगर @fw_name असलent)
 */
काष्ठा clk_parent_data अणु
	स्थिर काष्ठा clk_hw	*hw;
	स्थिर अक्षर		*fw_name;
	स्थिर अक्षर		*name;
	पूर्णांक			index;
पूर्ण;

/**
 * काष्ठा clk_init_data - holds init data that's common to all घड़ीs and is
 * shared between the घड़ी provider and the common घड़ी framework.
 *
 * @name: घड़ी name
 * @ops: operations this घड़ी supports
 * @parent_names: array of string names क्रम all possible parents
 * @parent_data: array of parent data क्रम all possible parents (when some
 *               parents are बाह्यal to the clk controller)
 * @parent_hws: array of poपूर्णांकers to all possible parents (when all parents
 *              are पूर्णांकernal to the clk controller)
 * @num_parents: number of possible parents
 * @flags: framework-level hपूर्णांकs and quirks
 */
काष्ठा clk_init_data अणु
	स्थिर अक्षर		*name;
	स्थिर काष्ठा clk_ops	*ops;
	/* Only one of the following three should be asचिन्हित */
	स्थिर अक्षर		* स्थिर *parent_names;
	स्थिर काष्ठा clk_parent_data	*parent_data;
	स्थिर काष्ठा clk_hw		**parent_hws;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
पूर्ण;

/**
 * काष्ठा clk_hw - handle क्रम traversing from a काष्ठा clk to its corresponding
 * hardware-specअगरic काष्ठाure.  काष्ठा clk_hw should be declared within काष्ठा
 * clk_foo and then referenced by the काष्ठा clk instance that uses काष्ठा
 * clk_foo's clk_ops
 *
 * @core: poपूर्णांकer to the काष्ठा clk_core instance that poपूर्णांकs back to this
 * काष्ठा clk_hw instance
 *
 * @clk: poपूर्णांकer to the per-user काष्ठा clk instance that can be used to call
 * पूर्णांकo the clk API
 *
 * @init: poपूर्णांकer to काष्ठा clk_init_data that contains the init data shared
 * with the common घड़ी framework. This poपूर्णांकer will be set to शून्य once
 * a clk_रेजिस्टर() variant is called on this clk_hw poपूर्णांकer.
 */
काष्ठा clk_hw अणु
	काष्ठा clk_core *core;
	काष्ठा clk *clk;
	स्थिर काष्ठा clk_init_data *init;
पूर्ण;

/*
 * DOC: Basic घड़ी implementations common to many platक्रमms
 *
 * Each basic घड़ी hardware type is comprised of a काष्ठाure describing the
 * घड़ी hardware, implementations of the relevant callbacks in काष्ठा clk_ops,
 * unique flags क्रम that hardware type, a registration function and an
 * alternative macro क्रम अटल initialization
 */

/**
 * काष्ठा clk_fixed_rate - fixed-rate घड़ी
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @fixed_rate:	स्थिरant frequency of घड़ी
 * @fixed_accuracy: स्थिरant accuracy of घड़ी in ppb (parts per billion)
 * @flags:	hardware specअगरic flags
 *
 * Flags:
 * * CLK_FIXED_RATE_PARENT_ACCURACY - Use the accuracy of the parent clk
 *                                    instead of what's set in @fixed_accuracy.
 */
काष्ठा clk_fixed_rate अणु
	काष्ठा		clk_hw hw;
	अचिन्हित दीर्घ	fixed_rate;
	अचिन्हित दीर्घ	fixed_accuracy;
	अचिन्हित दीर्घ	flags;
पूर्ण;

#घोषणा CLK_FIXED_RATE_PARENT_ACCURACY		BIT(0)

बाह्य स्थिर काष्ठा clk_ops clk_fixed_rate_ops;
काष्ठा clk_hw *__clk_hw_रेजिस्टर_fixed_rate(काष्ठा device *dev,
		काष्ठा device_node *np, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, स्थिर काष्ठा clk_hw *parent_hw,
		स्थिर काष्ठा clk_parent_data *parent_data, अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ fixed_rate, अचिन्हित दीर्घ fixed_accuracy,
		अचिन्हित दीर्घ clk_fixed_flags);
काष्ठा clk *clk_रेजिस्टर_fixed_rate(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ fixed_rate);
/**
 * clk_hw_रेजिस्टर_fixed_rate - रेजिस्टर fixed-rate घड़ी with the घड़ी
 * framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @fixed_rate: non-adjustable घड़ी rate
 */
#घोषणा clk_hw_रेजिस्टर_fixed_rate(dev, name, parent_name, flags, fixed_rate)  \
	__clk_hw_रेजिस्टर_fixed_rate((dev), शून्य, (name), (parent_name), शून्य, \
				     शून्य, (flags), (fixed_rate), 0, 0)
/**
 * clk_hw_रेजिस्टर_fixed_rate_parent_hw - रेजिस्टर fixed-rate घड़ी with
 * the घड़ी framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_hw: poपूर्णांकer to parent clk
 * @flags: framework-specअगरic flags
 * @fixed_rate: non-adjustable घड़ी rate
 */
#घोषणा clk_hw_रेजिस्टर_fixed_rate_parent_hw(dev, name, parent_hw, flags,     \
					     fixed_rate)		      \
	__clk_hw_रेजिस्टर_fixed_rate((dev), शून्य, (name), शून्य, (parent_hw),  \
				     शून्य, (flags), (fixed_rate), 0, 0)
/**
 * clk_hw_रेजिस्टर_fixed_rate_parent_data - रेजिस्टर fixed-rate घड़ी with
 * the घड़ी framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_data: parent clk data
 * @flags: framework-specअगरic flags
 * @fixed_rate: non-adjustable घड़ी rate
 */
#घोषणा clk_hw_रेजिस्टर_fixed_rate_parent_data(dev, name, parent_hw, flags,   \
					     fixed_rate)		      \
	__clk_hw_रेजिस्टर_fixed_rate((dev), शून्य, (name), शून्य, शून्य,	      \
				     (parent_data), (flags), (fixed_rate), 0, \
				     0)
/**
 * clk_hw_रेजिस्टर_fixed_rate_with_accuracy - रेजिस्टर fixed-rate घड़ी with
 * the घड़ी framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @fixed_rate: non-adjustable घड़ी rate
 * @fixed_accuracy: non-adjustable घड़ी accuracy
 */
#घोषणा clk_hw_रेजिस्टर_fixed_rate_with_accuracy(dev, name, parent_name,      \
						 flags, fixed_rate,	      \
						 fixed_accuracy)	      \
	__clk_hw_रेजिस्टर_fixed_rate((dev), शून्य, (name), (parent_name),      \
				     शून्य, शून्य, (flags), (fixed_rate),       \
				     (fixed_accuracy), 0)
/**
 * clk_hw_रेजिस्टर_fixed_rate_with_accuracy_parent_hw - रेजिस्टर fixed-rate
 * घड़ी with the घड़ी framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_hw: poपूर्णांकer to parent clk
 * @flags: framework-specअगरic flags
 * @fixed_rate: non-adjustable घड़ी rate
 * @fixed_accuracy: non-adjustable घड़ी accuracy
 */
#घोषणा clk_hw_रेजिस्टर_fixed_rate_with_accuracy_parent_hw(dev, name,	      \
		parent_hw, flags, fixed_rate, fixed_accuracy)		      \
	__clk_hw_रेजिस्टर_fixed_rate((dev), शून्य, (name), शून्य, (parent_hw)   \
				     शून्य, शून्य, (flags), (fixed_rate),	      \
				     (fixed_accuracy), 0)
/**
 * clk_hw_रेजिस्टर_fixed_rate_with_accuracy_parent_data - रेजिस्टर fixed-rate
 * घड़ी with the घड़ी framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @fixed_rate: non-adjustable घड़ी rate
 * @fixed_accuracy: non-adjustable घड़ी accuracy
 */
#घोषणा clk_hw_रेजिस्टर_fixed_rate_with_accuracy_parent_data(dev, name,	      \
		parent_data, flags, fixed_rate, fixed_accuracy)		      \
	__clk_hw_रेजिस्टर_fixed_rate((dev), शून्य, (name), शून्य, शून्य,	      \
				     (parent_data), शून्य, (flags),	      \
				     (fixed_rate), (fixed_accuracy), 0)

व्योम clk_unरेजिस्टर_fixed_rate(काष्ठा clk *clk);
व्योम clk_hw_unरेजिस्टर_fixed_rate(काष्ठा clk_hw *hw);

व्योम of_fixed_clk_setup(काष्ठा device_node *np);

/**
 * काष्ठा clk_gate - gating घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर controlling gate
 * @bit_idx:	single bit controlling gate
 * @flags:	hardware-specअगरic flags
 * @lock:	रेजिस्टर lock
 *
 * Clock which can gate its output.  Implements .enable & .disable
 *
 * Flags:
 * CLK_GATE_SET_TO_DISABLE - by शेष this घड़ी sets the bit at bit_idx to
 *	enable the घड़ी.  Setting this flag करोes the opposite: setting the bit
 *	disable the घड़ी and clearing it enables the घड़ी
 * CLK_GATE_HIWORD_MASK - The gate settings are only in lower 16-bit
 *	of this रेजिस्टर, and mask of gate bits are in higher 16-bit of this
 *	रेजिस्टर.  While setting the gate bits, higher 16-bit should also be
 *	updated to indicate changing gate bits.
 * CLK_GATE_BIG_ENDIAN - by शेष little endian रेजिस्टर accesses are used क्रम
 *	the gate रेजिस्टर.  Setting this flag makes the रेजिस्टर accesses big
 *	endian.
 */
काष्ठा clk_gate अणु
	काष्ठा clk_hw hw;
	व्योम __iomem	*reg;
	u8		bit_idx;
	u8		flags;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_clk_gate(_hw) container_of(_hw, काष्ठा clk_gate, hw)

#घोषणा CLK_GATE_SET_TO_DISABLE		BIT(0)
#घोषणा CLK_GATE_HIWORD_MASK		BIT(1)
#घोषणा CLK_GATE_BIG_ENDIAN		BIT(2)

बाह्य स्थिर काष्ठा clk_ops clk_gate_ops;
काष्ठा clk_hw *__clk_hw_रेजिस्टर_gate(काष्ठा device *dev,
		काष्ठा device_node *np, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, स्थिर काष्ठा clk_hw *parent_hw,
		स्थिर काष्ठा clk_parent_data *parent_data,
		अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 bit_idx,
		u8 clk_gate_flags, spinlock_t *lock);
काष्ठा clk *clk_रेजिस्टर_gate(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 bit_idx,
		u8 clk_gate_flags, spinlock_t *lock);
/**
 * clk_hw_रेजिस्टर_gate - रेजिस्टर a gate घड़ी with the घड़ी framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of this घड़ी's parent
 * @flags: framework-specअगरic flags क्रम this घड़ी
 * @reg: रेजिस्टर address to control gating of this घड़ी
 * @bit_idx: which bit in the रेजिस्टर controls gating of this घड़ी
 * @clk_gate_flags: gate-specअगरic flags क्रम this घड़ी
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_gate(dev, name, parent_name, flags, reg, bit_idx,     \
			     clk_gate_flags, lock)			      \
	__clk_hw_रेजिस्टर_gate((dev), शून्य, (name), (parent_name), शून्य,      \
			       शून्य, (flags), (reg), (bit_idx),		      \
			       (clk_gate_flags), (lock))
/**
 * clk_hw_रेजिस्टर_gate_parent_hw - रेजिस्टर a gate घड़ी with the घड़ी
 * framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_hw: poपूर्णांकer to parent clk
 * @flags: framework-specअगरic flags क्रम this घड़ी
 * @reg: रेजिस्टर address to control gating of this घड़ी
 * @bit_idx: which bit in the रेजिस्टर controls gating of this घड़ी
 * @clk_gate_flags: gate-specअगरic flags क्रम this घड़ी
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_gate_parent_hw(dev, name, parent_hw, flags, reg,      \
				       bit_idx, clk_gate_flags, lock)	      \
	__clk_hw_रेजिस्टर_gate((dev), शून्य, (name), शून्य, (parent_hw),        \
			       शून्य, (flags), (reg), (bit_idx),		      \
			       (clk_gate_flags), (lock))
/**
 * clk_hw_रेजिस्टर_gate_parent_data - रेजिस्टर a gate घड़ी with the घड़ी
 * framework
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_data: parent clk data
 * @flags: framework-specअगरic flags क्रम this घड़ी
 * @reg: रेजिस्टर address to control gating of this घड़ी
 * @bit_idx: which bit in the रेजिस्टर controls gating of this घड़ी
 * @clk_gate_flags: gate-specअगरic flags क्रम this घड़ी
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_gate_parent_data(dev, name, parent_data, flags, reg,  \
				       bit_idx, clk_gate_flags, lock)	      \
	__clk_hw_रेजिस्टर_gate((dev), शून्य, (name), शून्य, शून्य, (parent_data), \
			       (flags), (reg), (bit_idx),		      \
			       (clk_gate_flags), (lock))
व्योम clk_unरेजिस्टर_gate(काष्ठा clk *clk);
व्योम clk_hw_unरेजिस्टर_gate(काष्ठा clk_hw *hw);
पूर्णांक clk_gate_is_enabled(काष्ठा clk_hw *hw);

काष्ठा clk_भाग_प्रकारable अणु
	अचिन्हित पूर्णांक	val;
	अचिन्हित पूर्णांक	भाग;
पूर्ण;

/**
 * काष्ठा clk_भागider - adjustable भागider घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर containing the भागider
 * @shअगरt:	shअगरt to the भागider bit field
 * @width:	width of the भागider bit field
 * @table:	array of value/भागider pairs, last entry should have भाग = 0
 * @lock:	रेजिस्टर lock
 *
 * Clock with an adjustable भागider affecting its output frequency.  Implements
 * .recalc_rate, .set_rate and .round_rate
 *
 * Flags:
 * CLK_DIVIDER_ONE_BASED - by शेष the भागisor is the value पढ़ो from the
 *	रेजिस्टर plus one.  If CLK_DIVIDER_ONE_BASED is set then the भागider is
 *	the raw value पढ़ो from the रेजिस्टर, with the value of zero considered
 *	invalid, unless CLK_DIVIDER_ALLOW_ZERO is set.
 * CLK_DIVIDER_POWER_OF_TWO - घड़ी भागisor is 2 उठाओd to the value पढ़ो from
 *	the hardware रेजिस्टर
 * CLK_DIVIDER_ALLOW_ZERO - Allow zero भागisors.  For भागiders which have
 *	CLK_DIVIDER_ONE_BASED set, it is possible to end up with a zero भागisor.
 *	Some hardware implementations gracefully handle this हाल and allow a
 *	zero भागisor by not modअगरying their input घड़ी
 *	(भागide by one / bypass).
 * CLK_DIVIDER_HIWORD_MASK - The भागider settings are only in lower 16-bit
 *	of this रेजिस्टर, and mask of भागider bits are in higher 16-bit of this
 *	रेजिस्टर.  While setting the भागider bits, higher 16-bit should also be
 *	updated to indicate changing भागider bits.
 * CLK_DIVIDER_ROUND_CLOSEST - Makes the best calculated भागider to be rounded
 *	to the बंदst पूर्णांकeger instead of the up one.
 * CLK_DIVIDER_READ_ONLY - The भागider settings are preconfigured and should
 *	not be changed by the घड़ी framework.
 * CLK_DIVIDER_MAX_AT_ZERO - For भागiders which are like CLK_DIVIDER_ONE_BASED
 *	except when the value पढ़ो from the रेजिस्टर is zero, the भागisor is
 *	2^width of the field.
 * CLK_DIVIDER_BIG_ENDIAN - By शेष little endian रेजिस्टर accesses are used
 *	क्रम the भागider रेजिस्टर.  Setting this flag makes the रेजिस्टर accesses
 *	big endian.
 */
काष्ठा clk_भागider अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		shअगरt;
	u8		width;
	u8		flags;
	स्थिर काष्ठा clk_भाग_प्रकारable	*table;
	spinlock_t	*lock;
पूर्ण;

#घोषणा clk_भाग_mask(width)	((1 << (width)) - 1)
#घोषणा to_clk_भागider(_hw) container_of(_hw, काष्ठा clk_भागider, hw)

#घोषणा CLK_DIVIDER_ONE_BASED		BIT(0)
#घोषणा CLK_DIVIDER_POWER_OF_TWO	BIT(1)
#घोषणा CLK_DIVIDER_ALLOW_ZERO		BIT(2)
#घोषणा CLK_DIVIDER_HIWORD_MASK		BIT(3)
#घोषणा CLK_DIVIDER_ROUND_CLOSEST	BIT(4)
#घोषणा CLK_DIVIDER_READ_ONLY		BIT(5)
#घोषणा CLK_DIVIDER_MAX_AT_ZERO		BIT(6)
#घोषणा CLK_DIVIDER_BIG_ENDIAN		BIT(7)

बाह्य स्थिर काष्ठा clk_ops clk_भागider_ops;
बाह्य स्थिर काष्ठा clk_ops clk_भागider_ro_ops;

अचिन्हित दीर्घ भागider_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate,
		अचिन्हित पूर्णांक val, स्थिर काष्ठा clk_भाग_प्रकारable *table,
		अचिन्हित दीर्घ flags, अचिन्हित दीर्घ width);
दीर्घ भागider_round_rate_parent(काष्ठा clk_hw *hw, काष्ठा clk_hw *parent,
			       अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *prate,
			       स्थिर काष्ठा clk_भाग_प्रकारable *table,
			       u8 width, अचिन्हित दीर्घ flags);
दीर्घ भागider_ro_round_rate_parent(काष्ठा clk_hw *hw, काष्ठा clk_hw *parent,
				  अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *prate,
				  स्थिर काष्ठा clk_भाग_प्रकारable *table, u8 width,
				  अचिन्हित दीर्घ flags, अचिन्हित पूर्णांक val);
पूर्णांक भागider_get_val(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
		स्थिर काष्ठा clk_भाग_प्रकारable *table, u8 width,
		अचिन्हित दीर्घ flags);

काष्ठा clk_hw *__clk_hw_रेजिस्टर_भागider(काष्ठा device *dev,
		काष्ठा device_node *np, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, स्थिर काष्ठा clk_hw *parent_hw,
		स्थिर काष्ठा clk_parent_data *parent_data, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 shअगरt, u8 width, u8 clk_भागider_flags,
		स्थिर काष्ठा clk_भाग_प्रकारable *table, spinlock_t *lock);
काष्ठा clk_hw *__devm_clk_hw_रेजिस्टर_भागider(काष्ठा device *dev,
		काष्ठा device_node *np, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, स्थिर काष्ठा clk_hw *parent_hw,
		स्थिर काष्ठा clk_parent_data *parent_data, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 shअगरt, u8 width, u8 clk_भागider_flags,
		स्थिर काष्ठा clk_भाग_प्रकारable *table, spinlock_t *lock);
काष्ठा clk *clk_रेजिस्टर_भागider_table(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 shअगरt, u8 width,
		u8 clk_भागider_flags, स्थिर काष्ठा clk_भाग_प्रकारable *table,
		spinlock_t *lock);
/**
 * clk_रेजिस्टर_भागider - रेजिस्टर a भागider घड़ी with the घड़ी framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_रेजिस्टर_भागider(dev, name, parent_name, flags, reg, shअगरt, width, \
			     clk_भागider_flags, lock)			       \
	clk_रेजिस्टर_भागider_table((dev), (name), (parent_name), (flags),      \
				   (reg), (shअगरt), (width),		       \
				   (clk_भागider_flags), शून्य, (lock))
/**
 * clk_hw_रेजिस्टर_भागider - रेजिस्टर a भागider घड़ी with the घड़ी framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_भागider(dev, name, parent_name, flags, reg, shअगरt,    \
				width, clk_भागider_flags, lock)		      \
	__clk_hw_रेजिस्टर_भागider((dev), शून्य, (name), (parent_name), शून्य,   \
				  शून्य, (flags), (reg), (shअगरt), (width),     \
				  (clk_भागider_flags), शून्य, (lock))
/**
 * clk_hw_रेजिस्टर_भागider_parent_hw - रेजिस्टर a भागider घड़ी with the घड़ी
 * framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_hw: poपूर्णांकer to parent clk
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_भागider_parent_hw(dev, name, parent_hw, flags, reg,   \
					  shअगरt, width, clk_भागider_flags,    \
					  lock)				      \
	__clk_hw_रेजिस्टर_भागider((dev), शून्य, (name), शून्य, (parent_hw),     \
				  शून्य, (flags), (reg), (shअगरt), (width),     \
				  (clk_भागider_flags), शून्य, (lock))
/**
 * clk_hw_रेजिस्टर_भागider_parent_data - रेजिस्टर a भागider घड़ी with the घड़ी
 * framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_data: parent clk data
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_भागider_parent_data(dev, name, parent_data, flags,    \
					    reg, shअगरt, width,		      \
					    clk_भागider_flags, lock)	      \
	__clk_hw_रेजिस्टर_भागider((dev), शून्य, (name), शून्य, शून्य,	      \
				  (parent_data), (flags), (reg), (shअगरt),     \
				  (width), (clk_भागider_flags), शून्य, (lock))
/**
 * clk_hw_रेजिस्टर_भागider_table - रेजिस्टर a table based भागider घड़ी with
 * the घड़ी framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @table: array of भागider/value pairs ending with a भाग set to 0
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_भागider_table(dev, name, parent_name, flags, reg,     \
				      shअगरt, width, clk_भागider_flags, table, \
				      lock)				      \
	__clk_hw_रेजिस्टर_भागider((dev), शून्य, (name), (parent_name), शून्य,   \
				  शून्य, (flags), (reg), (shअगरt), (width),     \
				  (clk_भागider_flags), (table), (lock))
/**
 * clk_hw_रेजिस्टर_भागider_table_parent_hw - रेजिस्टर a table based भागider
 * घड़ी with the घड़ी framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_hw: poपूर्णांकer to parent clk
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @table: array of भागider/value pairs ending with a भाग set to 0
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_भागider_table_parent_hw(dev, name, parent_hw, flags,  \
						reg, shअगरt, width,	      \
						clk_भागider_flags, table,     \
						lock)			      \
	__clk_hw_रेजिस्टर_भागider((dev), शून्य, (name), शून्य, (parent_hw),     \
				  शून्य, (flags), (reg), (shअगरt), (width),     \
				  (clk_भागider_flags), (table), (lock))
/**
 * clk_hw_रेजिस्टर_भागider_table_parent_data - रेजिस्टर a table based भागider
 * घड़ी with the घड़ी framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_data: parent clk data
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @table: array of भागider/value pairs ending with a भाग set to 0
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा clk_hw_रेजिस्टर_भागider_table_parent_data(dev, name, parent_data,     \
						  flags, reg, shअगरt, width,   \
						  clk_भागider_flags, table,   \
						  lock)			      \
	__clk_hw_रेजिस्टर_भागider((dev), शून्य, (name), शून्य, शून्य,	      \
				  (parent_data), (flags), (reg), (shअगरt),     \
				  (width), (clk_भागider_flags), (table),      \
				  (lock))
/**
 * devm_clk_hw_रेजिस्टर_भागider - रेजिस्टर a भागider घड़ी with the घड़ी framework
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा devm_clk_hw_रेजिस्टर_भागider(dev, name, parent_name, flags, reg, shअगरt,    \
				width, clk_भागider_flags, lock)		      \
	__devm_clk_hw_रेजिस्टर_भागider((dev), शून्य, (name), (parent_name), शून्य,   \
				  शून्य, (flags), (reg), (shअगरt), (width),     \
				  (clk_भागider_flags), शून्य, (lock))
/**
 * devm_clk_hw_रेजिस्टर_भागider_table - रेजिस्टर a table based भागider घड़ी
 * with the घड़ी framework (devres variant)
 * @dev: device रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @flags: framework-specअगरic flags
 * @reg: रेजिस्टर address to adjust भागider
 * @shअगरt: number of bits to shअगरt the bitfield
 * @width: width of the bitfield
 * @clk_भागider_flags: भागider-specअगरic flags क्रम this घड़ी
 * @table: array of भागider/value pairs ending with a भाग set to 0
 * @lock: shared रेजिस्टर lock क्रम this घड़ी
 */
#घोषणा devm_clk_hw_रेजिस्टर_भागider_table(dev, name, parent_name, flags,     \
					   reg, shअगरt, width,		      \
					   clk_भागider_flags, table, lock)    \
	__devm_clk_hw_रेजिस्टर_भागider((dev), शून्य, (name), (parent_name),    \
				       शून्य, शून्य, (flags), (reg), (shअगरt),   \
				       (width), (clk_भागider_flags), (table), \
				       (lock))

व्योम clk_unरेजिस्टर_भागider(काष्ठा clk *clk);
व्योम clk_hw_unरेजिस्टर_भागider(काष्ठा clk_hw *hw);

/**
 * काष्ठा clk_mux - multiplexer घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर controlling multiplexer
 * @table:	array of रेजिस्टर values corresponding to the parent index
 * @shअगरt:	shअगरt to multiplexer bit field
 * @mask:	mask of mutliplexer bit field
 * @flags:	hardware-specअगरic flags
 * @lock:	रेजिस्टर lock
 *
 * Clock with multiple selectable parents.  Implements .get_parent, .set_parent
 * and .recalc_rate
 *
 * Flags:
 * CLK_MUX_INDEX_ONE - रेजिस्टर index starts at 1, not 0
 * CLK_MUX_INDEX_BIT - रेजिस्टर index is a single bit (घातer of two)
 * CLK_MUX_HIWORD_MASK - The mux settings are only in lower 16-bit of this
 *	रेजिस्टर, and mask of mux bits are in higher 16-bit of this रेजिस्टर.
 *	While setting the mux bits, higher 16-bit should also be updated to
 *	indicate changing mux bits.
 * CLK_MUX_READ_ONLY - The mux रेजिस्टरs can't be written, only पढ़ो in the
 * 	.get_parent clk_op.
 * CLK_MUX_ROUND_CLOSEST - Use the parent rate that is बंदst to the desired
 *	frequency.
 * CLK_MUX_BIG_ENDIAN - By शेष little endian रेजिस्टर accesses are used क्रम
 *	the mux रेजिस्टर.  Setting this flag makes the रेजिस्टर accesses big
 *	endian.
 */
काष्ठा clk_mux अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u32		*table;
	u32		mask;
	u8		shअगरt;
	u8		flags;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_clk_mux(_hw) container_of(_hw, काष्ठा clk_mux, hw)

#घोषणा CLK_MUX_INDEX_ONE		BIT(0)
#घोषणा CLK_MUX_INDEX_BIT		BIT(1)
#घोषणा CLK_MUX_HIWORD_MASK		BIT(2)
#घोषणा CLK_MUX_READ_ONLY		BIT(3) /* mux can't be changed */
#घोषणा CLK_MUX_ROUND_CLOSEST		BIT(4)
#घोषणा CLK_MUX_BIG_ENDIAN		BIT(5)

बाह्य स्थिर काष्ठा clk_ops clk_mux_ops;
बाह्य स्थिर काष्ठा clk_ops clk_mux_ro_ops;

काष्ठा clk_hw *__clk_hw_रेजिस्टर_mux(काष्ठा device *dev, काष्ठा device_node *np,
		स्थिर अक्षर *name, u8 num_parents,
		स्थिर अक्षर * स्थिर *parent_names,
		स्थिर काष्ठा clk_hw **parent_hws,
		स्थिर काष्ठा clk_parent_data *parent_data,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 shअगरt, u32 mask,
		u8 clk_mux_flags, u32 *table, spinlock_t *lock);
काष्ठा clk_hw *__devm_clk_hw_रेजिस्टर_mux(काष्ठा device *dev, काष्ठा device_node *np,
		स्थिर अक्षर *name, u8 num_parents,
		स्थिर अक्षर * स्थिर *parent_names,
		स्थिर काष्ठा clk_hw **parent_hws,
		स्थिर काष्ठा clk_parent_data *parent_data,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 shअगरt, u32 mask,
		u8 clk_mux_flags, u32 *table, spinlock_t *lock);
काष्ठा clk *clk_रेजिस्टर_mux_table(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, u8 num_parents,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 shअगरt, u32 mask,
		u8 clk_mux_flags, u32 *table, spinlock_t *lock);

#घोषणा clk_रेजिस्टर_mux(dev, name, parent_names, num_parents, flags, reg,    \
			 shअगरt, width, clk_mux_flags, lock)		      \
	clk_रेजिस्टर_mux_table((dev), (name), (parent_names), (num_parents),  \
			       (flags), (reg), (shअगरt), BIT((width)) - 1,     \
			       (clk_mux_flags), शून्य, (lock))
#घोषणा clk_hw_रेजिस्टर_mux_table(dev, name, parent_names, num_parents,	      \
				  flags, reg, shअगरt, mask, clk_mux_flags,     \
				  table, lock)				      \
	__clk_hw_रेजिस्टर_mux((dev), शून्य, (name), (num_parents),	      \
			      (parent_names), शून्य, शून्य, (flags), (reg),     \
			      (shअगरt), (mask), (clk_mux_flags), (table),      \
			      (lock))
#घोषणा clk_hw_रेजिस्टर_mux(dev, name, parent_names, num_parents, flags, reg, \
			    shअगरt, width, clk_mux_flags, lock)		      \
	__clk_hw_रेजिस्टर_mux((dev), शून्य, (name), (num_parents),	      \
			      (parent_names), शून्य, शून्य, (flags), (reg),     \
			      (shअगरt), BIT((width)) - 1, (clk_mux_flags),     \
			      शून्य, (lock))
#घोषणा clk_hw_रेजिस्टर_mux_hws(dev, name, parent_hws, num_parents, flags,    \
				reg, shअगरt, width, clk_mux_flags, lock)	      \
	__clk_hw_रेजिस्टर_mux((dev), शून्य, (name), (num_parents), शून्य,	      \
			      (parent_hws), शून्य, (flags), (reg), (shअगरt),    \
			      BIT((width)) - 1, (clk_mux_flags), शून्य, (lock))
#घोषणा clk_hw_रेजिस्टर_mux_parent_data(dev, name, parent_data, num_parents,  \
					flags, reg, shअगरt, width,	      \
					clk_mux_flags, lock)		      \
	__clk_hw_रेजिस्टर_mux((dev), शून्य, (name), (num_parents), शून्य, शून्य, \
			      (parent_data), (flags), (reg), (shअगरt),	      \
			      BIT((width)) - 1, (clk_mux_flags), शून्य, (lock))
#घोषणा devm_clk_hw_रेजिस्टर_mux(dev, name, parent_names, num_parents, flags, reg, \
			    shअगरt, width, clk_mux_flags, lock)		      \
	__devm_clk_hw_रेजिस्टर_mux((dev), शून्य, (name), (num_parents),	      \
			      (parent_names), शून्य, शून्य, (flags), (reg),     \
			      (shअगरt), BIT((width)) - 1, (clk_mux_flags),     \
			      शून्य, (lock))

पूर्णांक clk_mux_val_to_index(काष्ठा clk_hw *hw, u32 *table, अचिन्हित पूर्णांक flags,
			 अचिन्हित पूर्णांक val);
अचिन्हित पूर्णांक clk_mux_index_to_val(u32 *table, अचिन्हित पूर्णांक flags, u8 index);

व्योम clk_unरेजिस्टर_mux(काष्ठा clk *clk);
व्योम clk_hw_unरेजिस्टर_mux(काष्ठा clk_hw *hw);

व्योम of_fixed_factor_clk_setup(काष्ठा device_node *node);

/**
 * काष्ठा clk_fixed_factor - fixed multiplier and भागider घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @mult:	multiplier
 * @भाग:	भागider
 *
 * Clock with a fixed multiplier and भागider. The output frequency is the
 * parent घड़ी rate भागided by भाग and multiplied by mult.
 * Implements .recalc_rate, .set_rate and .round_rate
 */

काष्ठा clk_fixed_factor अणु
	काष्ठा clk_hw	hw;
	अचिन्हित पूर्णांक	mult;
	अचिन्हित पूर्णांक	भाग;
पूर्ण;

#घोषणा to_clk_fixed_factor(_hw) container_of(_hw, काष्ठा clk_fixed_factor, hw)

बाह्य स्थिर काष्ठा clk_ops clk_fixed_factor_ops;
काष्ठा clk *clk_रेजिस्टर_fixed_factor(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग);
व्योम clk_unरेजिस्टर_fixed_factor(काष्ठा clk *clk);
काष्ठा clk_hw *clk_hw_रेजिस्टर_fixed_factor(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग);
व्योम clk_hw_unरेजिस्टर_fixed_factor(काष्ठा clk_hw *hw);
काष्ठा clk_hw *devm_clk_hw_रेजिस्टर_fixed_factor(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग);
/**
 * काष्ठा clk_fractional_भागider - adjustable fractional भागider घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर containing the भागider
 * @mshअगरt:	shअगरt to the numerator bit field
 * @mwidth:	width of the numerator bit field
 * @nshअगरt:	shअगरt to the denominator bit field
 * @nwidth:	width of the denominator bit field
 * @lock:	रेजिस्टर lock
 *
 * Clock with adjustable fractional भागider affecting its output frequency.
 *
 * Flags:
 * CLK_FRAC_DIVIDER_ZERO_BASED - by शेष the numerator and denominator
 *	is the value पढ़ो from the रेजिस्टर. If CLK_FRAC_DIVIDER_ZERO_BASED
 *	is set then the numerator and denominator are both the value पढ़ो
 *	plus one.
 * CLK_FRAC_DIVIDER_BIG_ENDIAN - By शेष little endian रेजिस्टर accesses are
 *	used क्रम the भागider रेजिस्टर.  Setting this flag makes the रेजिस्टर
 *	accesses big endian.
 */
काष्ठा clk_fractional_भागider अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		mshअगरt;
	u8		mwidth;
	u32		mmask;
	u8		nshअगरt;
	u8		nwidth;
	u32		nmask;
	u8		flags;
	व्योम		(*approximation)(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *parent_rate,
				अचिन्हित दीर्घ *m, अचिन्हित दीर्घ *n);
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_clk_fd(_hw) container_of(_hw, काष्ठा clk_fractional_भागider, hw)

#घोषणा CLK_FRAC_DIVIDER_ZERO_BASED		BIT(0)
#घोषणा CLK_FRAC_DIVIDER_BIG_ENDIAN		BIT(1)

बाह्य स्थिर काष्ठा clk_ops clk_fractional_भागider_ops;
काष्ठा clk *clk_रेजिस्टर_fractional_भागider(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 mshअगरt, u8 mwidth, u8 nshअगरt, u8 nwidth,
		u8 clk_भागider_flags, spinlock_t *lock);
काष्ठा clk_hw *clk_hw_रेजिस्टर_fractional_भागider(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 mshअगरt, u8 mwidth, u8 nshअगरt, u8 nwidth,
		u8 clk_भागider_flags, spinlock_t *lock);
व्योम clk_hw_unरेजिस्टर_fractional_भागider(काष्ठा clk_hw *hw);

/**
 * काष्ठा clk_multiplier - adjustable multiplier घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर containing the multiplier
 * @shअगरt:	shअगरt to the multiplier bit field
 * @width:	width of the multiplier bit field
 * @lock:	रेजिस्टर lock
 *
 * Clock with an adjustable multiplier affecting its output frequency.
 * Implements .recalc_rate, .set_rate and .round_rate
 *
 * Flags:
 * CLK_MULTIPLIER_ZERO_BYPASS - By शेष, the multiplier is the value पढ़ो
 *	from the रेजिस्टर, with 0 being a valid value effectively
 *	zeroing the output घड़ी rate. If CLK_MULTIPLIER_ZERO_BYPASS is
 *	set, then a null multiplier will be considered as a bypass,
 *	leaving the parent rate unmodअगरied.
 * CLK_MULTIPLIER_ROUND_CLOSEST - Makes the best calculated भागider to be
 *	rounded to the बंदst पूर्णांकeger instead of the करोwn one.
 * CLK_MULTIPLIER_BIG_ENDIAN - By शेष little endian रेजिस्टर accesses are
 *	used क्रम the multiplier रेजिस्टर.  Setting this flag makes the रेजिस्टर
 *	accesses big endian.
 */
काष्ठा clk_multiplier अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		shअगरt;
	u8		width;
	u8		flags;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_clk_multiplier(_hw) container_of(_hw, काष्ठा clk_multiplier, hw)

#घोषणा CLK_MULTIPLIER_ZERO_BYPASS		BIT(0)
#घोषणा CLK_MULTIPLIER_ROUND_CLOSEST	BIT(1)
#घोषणा CLK_MULTIPLIER_BIG_ENDIAN		BIT(2)

बाह्य स्थिर काष्ठा clk_ops clk_multiplier_ops;

/***
 * काष्ठा clk_composite - aggregate घड़ी of mux, भागider and gate घड़ीs
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @mux_hw:	handle between composite and hardware-specअगरic mux घड़ी
 * @rate_hw:	handle between composite and hardware-specअगरic rate घड़ी
 * @gate_hw:	handle between composite and hardware-specअगरic gate घड़ी
 * @mux_ops:	घड़ी ops क्रम mux
 * @rate_ops:	घड़ी ops क्रम rate
 * @gate_ops:	घड़ी ops क्रम gate
 */
काष्ठा clk_composite अणु
	काष्ठा clk_hw	hw;
	काष्ठा clk_ops	ops;

	काष्ठा clk_hw	*mux_hw;
	काष्ठा clk_hw	*rate_hw;
	काष्ठा clk_hw	*gate_hw;

	स्थिर काष्ठा clk_ops	*mux_ops;
	स्थिर काष्ठा clk_ops	*rate_ops;
	स्थिर काष्ठा clk_ops	*gate_ops;
पूर्ण;

#घोषणा to_clk_composite(_hw) container_of(_hw, काष्ठा clk_composite, hw)

काष्ठा clk *clk_रेजिस्टर_composite(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
		काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
		काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
		काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
		अचिन्हित दीर्घ flags);
काष्ठा clk *clk_रेजिस्टर_composite_pdata(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर काष्ठा clk_parent_data *parent_data, पूर्णांक num_parents,
		काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
		काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
		काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
		अचिन्हित दीर्घ flags);
व्योम clk_unरेजिस्टर_composite(काष्ठा clk *clk);
काष्ठा clk_hw *clk_hw_रेजिस्टर_composite(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
		काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
		काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
		काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
		अचिन्हित दीर्घ flags);
काष्ठा clk_hw *clk_hw_रेजिस्टर_composite_pdata(काष्ठा device *dev,
		स्थिर अक्षर *name,
		स्थिर काष्ठा clk_parent_data *parent_data, पूर्णांक num_parents,
		काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
		काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
		काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
		अचिन्हित दीर्घ flags);
काष्ठा clk_hw *devm_clk_hw_रेजिस्टर_composite_pdata(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर काष्ठा clk_parent_data *parent_data,
		पूर्णांक num_parents,
		काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
		काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
		काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
		अचिन्हित दीर्घ flags);
व्योम clk_hw_unरेजिस्टर_composite(काष्ठा clk_hw *hw);

काष्ठा clk *clk_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw);
काष्ठा clk *devm_clk_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw);

पूर्णांक __must_check clk_hw_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw);
पूर्णांक __must_check devm_clk_hw_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw);
पूर्णांक __must_check of_clk_hw_रेजिस्टर(काष्ठा device_node *node, काष्ठा clk_hw *hw);

व्योम clk_unरेजिस्टर(काष्ठा clk *clk);
व्योम devm_clk_unरेजिस्टर(काष्ठा device *dev, काष्ठा clk *clk);

व्योम clk_hw_unरेजिस्टर(काष्ठा clk_hw *hw);
व्योम devm_clk_hw_unरेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw);

/* helper functions */
स्थिर अक्षर *__clk_get_name(स्थिर काष्ठा clk *clk);
स्थिर अक्षर *clk_hw_get_name(स्थिर काष्ठा clk_hw *hw);
#अगर_घोषित CONFIG_COMMON_CLK
काष्ठा clk_hw *__clk_get_hw(काष्ठा clk *clk);
#अन्यथा
अटल अंतरभूत काष्ठा clk_hw *__clk_get_hw(काष्ठा clk *clk)
अणु
	वापस (काष्ठा clk_hw *)clk;
पूर्ण
#पूर्ण_अगर

काष्ठा clk *clk_hw_get_clk(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id);
काष्ठा clk *devm_clk_hw_get_clk(काष्ठा device *dev, काष्ठा clk_hw *hw,
				स्थिर अक्षर *con_id);

अचिन्हित पूर्णांक clk_hw_get_num_parents(स्थिर काष्ठा clk_hw *hw);
काष्ठा clk_hw *clk_hw_get_parent(स्थिर काष्ठा clk_hw *hw);
काष्ठा clk_hw *clk_hw_get_parent_by_index(स्थिर काष्ठा clk_hw *hw,
					  अचिन्हित पूर्णांक index);
पूर्णांक clk_hw_get_parent_index(काष्ठा clk_hw *hw);
पूर्णांक clk_hw_set_parent(काष्ठा clk_hw *hw, काष्ठा clk_hw *new_parent);
अचिन्हित पूर्णांक __clk_get_enable_count(काष्ठा clk *clk);
अचिन्हित दीर्घ clk_hw_get_rate(स्थिर काष्ठा clk_hw *hw);
अचिन्हित दीर्घ clk_hw_get_flags(स्थिर काष्ठा clk_hw *hw);
#घोषणा clk_hw_can_set_rate_parent(hw) \
	(clk_hw_get_flags((hw)) & CLK_SET_RATE_PARENT)

bool clk_hw_is_prepared(स्थिर काष्ठा clk_hw *hw);
bool clk_hw_rate_is_रक्षित(स्थिर काष्ठा clk_hw *hw);
bool clk_hw_is_enabled(स्थिर काष्ठा clk_hw *hw);
bool __clk_is_enabled(काष्ठा clk *clk);
काष्ठा clk *__clk_lookup(स्थिर अक्षर *name);
पूर्णांक __clk_mux_determine_rate(काष्ठा clk_hw *hw,
			     काष्ठा clk_rate_request *req);
पूर्णांक __clk_determine_rate(काष्ठा clk_hw *core, काष्ठा clk_rate_request *req);
पूर्णांक __clk_mux_determine_rate_बंदst(काष्ठा clk_hw *hw,
				     काष्ठा clk_rate_request *req);
पूर्णांक clk_mux_determine_rate_flags(काष्ठा clk_hw *hw,
				 काष्ठा clk_rate_request *req,
				 अचिन्हित दीर्घ flags);
व्योम clk_hw_reparent(काष्ठा clk_hw *hw, काष्ठा clk_hw *new_parent);
व्योम clk_hw_set_rate_range(काष्ठा clk_hw *hw, अचिन्हित दीर्घ min_rate,
			   अचिन्हित दीर्घ max_rate);

अटल अंतरभूत व्योम __clk_hw_set_clk(काष्ठा clk_hw *dst, काष्ठा clk_hw *src)
अणु
	dst->clk = src->clk;
	dst->core = src->core;
पूर्ण

अटल अंतरभूत दीर्घ भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *prate,
				      स्थिर काष्ठा clk_भाग_प्रकारable *table,
				      u8 width, अचिन्हित दीर्घ flags)
अणु
	वापस भागider_round_rate_parent(hw, clk_hw_get_parent(hw),
					 rate, prate, table, width, flags);
पूर्ण

अटल अंतरभूत दीर्घ भागider_ro_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ *prate,
					 स्थिर काष्ठा clk_भाग_प्रकारable *table,
					 u8 width, अचिन्हित दीर्घ flags,
					 अचिन्हित पूर्णांक val)
अणु
	वापस भागider_ro_round_rate_parent(hw, clk_hw_get_parent(hw),
					    rate, prate, table, width, flags,
					    val);
पूर्ण

/*
 * FIXME घड़ी api without lock protection
 */
अचिन्हित दीर्घ clk_hw_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate);

काष्ठा clk_onecell_data अणु
	काष्ठा clk **clks;
	अचिन्हित पूर्णांक clk_num;
पूर्ण;

काष्ठा clk_hw_onecell_data अणु
	अचिन्हित पूर्णांक num;
	काष्ठा clk_hw *hws[];
पूर्ण;

#घोषणा CLK_OF_DECLARE(name, compat, fn) OF_DECLARE_1(clk, name, compat, fn)

/*
 * Use this macro when you have a driver that requires two initialization
 * routines, one at of_clk_init(), and one at platक्रमm device probe
 */
#घोषणा CLK_OF_DECLARE_DRIVER(name, compat, fn) \
	अटल व्योम __init name##_of_clk_init_driver(काष्ठा device_node *np) \
	अणु								\
		of_node_clear_flag(np, OF_POPULATED);			\
		fn(np);							\
	पूर्ण								\
	OF_DECLARE_1(clk, name, compat, name##_of_clk_init_driver)

#घोषणा CLK_HW_INIT(_name, _parent, _ops, _flags)		\
	(&(काष्ठा clk_init_data) अणु				\
		.flags		= _flags,			\
		.name		= _name,			\
		.parent_names	= (स्थिर अक्षर *[]) अणु _parent पूर्ण,	\
		.num_parents	= 1,				\
		.ops		= _ops,				\
	पूर्ण)

#घोषणा CLK_HW_INIT_HW(_name, _parent, _ops, _flags)			\
	(&(काष्ठा clk_init_data) अणु					\
		.flags		= _flags,				\
		.name		= _name,				\
		.parent_hws	= (स्थिर काष्ठा clk_hw*[]) अणु _parent पूर्ण,	\
		.num_parents	= 1,					\
		.ops		= _ops,					\
	पूर्ण)

/*
 * This macro is पूर्णांकended क्रम drivers to be able to share the otherwise
 * inभागidual काष्ठा clk_hw[] compound literals created by the compiler
 * when using CLK_HW_INIT_HW. It करोes NOT support multiple parents.
 */
#घोषणा CLK_HW_INIT_HWS(_name, _parent, _ops, _flags)			\
	(&(काष्ठा clk_init_data) अणु					\
		.flags		= _flags,				\
		.name		= _name,				\
		.parent_hws	= _parent,				\
		.num_parents	= 1,					\
		.ops		= _ops,					\
	पूर्ण)

#घोषणा CLK_HW_INIT_FW_NAME(_name, _parent, _ops, _flags)		\
	(&(काष्ठा clk_init_data) अणु					\
		.flags		= _flags,				\
		.name		= _name,				\
		.parent_data	= (स्थिर काष्ठा clk_parent_data[]) अणु	\
					अणु .fw_name = _parent पूर्ण,		\
				  पूर्ण,					\
		.num_parents	= 1,					\
		.ops		= _ops,					\
	पूर्ण)

#घोषणा CLK_HW_INIT_PARENTS(_name, _parents, _ops, _flags)	\
	(&(काष्ठा clk_init_data) अणु				\
		.flags		= _flags,			\
		.name		= _name,			\
		.parent_names	= _parents,			\
		.num_parents	= ARRAY_SIZE(_parents),		\
		.ops		= _ops,				\
	पूर्ण)

#घोषणा CLK_HW_INIT_PARENTS_HW(_name, _parents, _ops, _flags)	\
	(&(काष्ठा clk_init_data) अणु				\
		.flags		= _flags,			\
		.name		= _name,			\
		.parent_hws	= _parents,			\
		.num_parents	= ARRAY_SIZE(_parents),		\
		.ops		= _ops,				\
	पूर्ण)

#घोषणा CLK_HW_INIT_PARENTS_DATA(_name, _parents, _ops, _flags)	\
	(&(काष्ठा clk_init_data) अणु				\
		.flags		= _flags,			\
		.name		= _name,			\
		.parent_data	= _parents,			\
		.num_parents	= ARRAY_SIZE(_parents),		\
		.ops		= _ops,				\
	पूर्ण)

#घोषणा CLK_HW_INIT_NO_PARENT(_name, _ops, _flags)	\
	(&(काष्ठा clk_init_data) अणु			\
		.flags          = _flags,		\
		.name           = _name,		\
		.parent_names   = शून्य,			\
		.num_parents    = 0,			\
		.ops            = _ops,			\
	पूर्ण)

#घोषणा CLK_FIXED_FACTOR(_काष्ठा, _name, _parent,			\
			_भाग, _mult, _flags)				\
	काष्ठा clk_fixed_factor _काष्ठा = अणु				\
		.भाग		= _भाग,					\
		.mult		= _mult,				\
		.hw.init	= CLK_HW_INIT(_name,			\
					      _parent,			\
					      &clk_fixed_factor_ops,	\
					      _flags),			\
	पूर्ण

#घोषणा CLK_FIXED_FACTOR_HW(_काष्ठा, _name, _parent,			\
			    _भाग, _mult, _flags)			\
	काष्ठा clk_fixed_factor _काष्ठा = अणु				\
		.भाग		= _भाग,					\
		.mult		= _mult,				\
		.hw.init	= CLK_HW_INIT_HW(_name,			\
						 _parent,		\
						 &clk_fixed_factor_ops,	\
						 _flags),		\
	पूर्ण

/*
 * This macro allows the driver to reuse the _parent array क्रम multiple
 * fixed factor clk declarations.
 */
#घोषणा CLK_FIXED_FACTOR_HWS(_काष्ठा, _name, _parent,			\
			     _भाग, _mult, _flags)			\
	काष्ठा clk_fixed_factor _काष्ठा = अणु				\
		.भाग		= _भाग,					\
		.mult		= _mult,				\
		.hw.init	= CLK_HW_INIT_HWS(_name,		\
						  _parent,		\
						  &clk_fixed_factor_ops, \
						  _flags),	\
	पूर्ण

#घोषणा CLK_FIXED_FACTOR_FW_NAME(_काष्ठा, _name, _parent,		\
				 _भाग, _mult, _flags)			\
	काष्ठा clk_fixed_factor _काष्ठा = अणु				\
		.भाग		= _भाग,					\
		.mult		= _mult,				\
		.hw.init	= CLK_HW_INIT_FW_NAME(_name,		\
						      _parent,		\
						      &clk_fixed_factor_ops, \
						      _flags),		\
	पूर्ण

#अगर_घोषित CONFIG_OF
पूर्णांक of_clk_add_provider(काष्ठा device_node *np,
			काष्ठा clk *(*clk_src_get)(काष्ठा of_phandle_args *args,
						   व्योम *data),
			व्योम *data);
पूर्णांक of_clk_add_hw_provider(काष्ठा device_node *np,
			   काष्ठा clk_hw *(*get)(काष्ठा of_phandle_args *clkspec,
						 व्योम *data),
			   व्योम *data);
पूर्णांक devm_of_clk_add_hw_provider(काष्ठा device *dev,
			   काष्ठा clk_hw *(*get)(काष्ठा of_phandle_args *clkspec,
						 व्योम *data),
			   व्योम *data);
व्योम of_clk_del_provider(काष्ठा device_node *np);
व्योम devm_of_clk_del_provider(काष्ठा device *dev);
काष्ठा clk *of_clk_src_simple_get(काष्ठा of_phandle_args *clkspec,
				  व्योम *data);
काष्ठा clk_hw *of_clk_hw_simple_get(काष्ठा of_phandle_args *clkspec,
				    व्योम *data);
काष्ठा clk *of_clk_src_onecell_get(काष्ठा of_phandle_args *clkspec, व्योम *data);
काष्ठा clk_hw *of_clk_hw_onecell_get(काष्ठा of_phandle_args *clkspec,
				     व्योम *data);
पूर्णांक of_clk_parent_fill(काष्ठा device_node *np, स्थिर अक्षर **parents,
		       अचिन्हित पूर्णांक size);
पूर्णांक of_clk_detect_critical(काष्ठा device_node *np, पूर्णांक index,
			    अचिन्हित दीर्घ *flags);

#अन्यथा /* !CONFIG_OF */

अटल अंतरभूत पूर्णांक of_clk_add_provider(काष्ठा device_node *np,
			काष्ठा clk *(*clk_src_get)(काष्ठा of_phandle_args *args,
						   व्योम *data),
			व्योम *data)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक of_clk_add_hw_provider(काष्ठा device_node *np,
			काष्ठा clk_hw *(*get)(काष्ठा of_phandle_args *clkspec,
					      व्योम *data),
			व्योम *data)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक devm_of_clk_add_hw_provider(काष्ठा device *dev,
			   काष्ठा clk_hw *(*get)(काष्ठा of_phandle_args *clkspec,
						 व्योम *data),
			   व्योम *data)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम of_clk_del_provider(काष्ठा device_node *np) अणुपूर्ण
अटल अंतरभूत व्योम devm_of_clk_del_provider(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत काष्ठा clk *of_clk_src_simple_get(
	काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत काष्ठा clk_hw *
of_clk_hw_simple_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत काष्ठा clk *of_clk_src_onecell_get(
	काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत काष्ठा clk_hw *
of_clk_hw_onecell_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत पूर्णांक of_clk_parent_fill(काष्ठा device_node *np,
				     स्थिर अक्षर **parents, अचिन्हित पूर्णांक size)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक of_clk_detect_critical(काष्ठा device_node *np, पूर्णांक index,
					  अचिन्हित दीर्घ *flags)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

व्योम clk_gate_restore_context(काष्ठा clk_hw *hw);

#पूर्ण_अगर /* CLK_PROVIDER_H */
