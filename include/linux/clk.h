<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/linux/clk.h
 *
 *  Copyright (C) 2004 ARM Limited.
 *  Written by Deep Blue Solutions Limited.
 *  Copyright (C) 2011-2012 Linaro Ltd <mturquette@linaro.org>
 */
#अगर_अघोषित __LINUX_CLK_H
#घोषणा __LINUX_CLK_H

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>

काष्ठा device;
काष्ठा clk;
काष्ठा device_node;
काष्ठा of_phandle_args;

/**
 * DOC: clk notअगरier callback types
 *
 * PRE_RATE_CHANGE - called immediately beक्रमe the clk rate is changed,
 *     to indicate that the rate change will proceed.  Drivers must
 *     immediately terminate any operations that will be affected by the
 *     rate change.  Callbacks may either वापस NOTIFY_DONE, NOTIFY_OK,
 *     NOTIFY_STOP or NOTIFY_BAD.
 *
 * ABORT_RATE_CHANGE: called अगर the rate change failed क्रम some reason
 *     after PRE_RATE_CHANGE.  In this हाल, all रेजिस्टरed notअगरiers on
 *     the clk will be called with ABORT_RATE_CHANGE. Callbacks must
 *     always वापस NOTIFY_DONE or NOTIFY_OK.
 *
 * POST_RATE_CHANGE - called after the clk rate change has successfully
 *     completed.  Callbacks must always वापस NOTIFY_DONE or NOTIFY_OK.
 *
 */
#घोषणा PRE_RATE_CHANGE			BIT(0)
#घोषणा POST_RATE_CHANGE		BIT(1)
#घोषणा ABORT_RATE_CHANGE		BIT(2)

/**
 * काष्ठा clk_notअगरier - associate a clk with a notअगरier
 * @clk: काष्ठा clk * to associate the notअगरier with
 * @notअगरier_head: a blocking_notअगरier_head क्रम this clk
 * @node: linked list poपूर्णांकers
 *
 * A list of काष्ठा clk_notअगरier is मुख्यtained by the notअगरier code.
 * An entry is created whenever code रेजिस्टरs the first notअगरier on a
 * particular @clk.  Future notअगरiers on that @clk are added to the
 * @notअगरier_head.
 */
काष्ठा clk_notअगरier अणु
	काष्ठा clk			*clk;
	काष्ठा srcu_notअगरier_head	notअगरier_head;
	काष्ठा list_head		node;
पूर्ण;

/**
 * काष्ठा clk_notअगरier_data - rate data to pass to the notअगरier callback
 * @clk: काष्ठा clk * being changed
 * @old_rate: previous rate of this clk
 * @new_rate: new rate of this clk
 *
 * For a pre-notअगरier, old_rate is the clk's rate beक्रमe this rate
 * change, and new_rate is what the rate will be in the future.  For a
 * post-notअगरier, old_rate and new_rate are both set to the clk's
 * current rate (this was करोne to optimize the implementation).
 */
काष्ठा clk_notअगरier_data अणु
	काष्ठा clk		*clk;
	अचिन्हित दीर्घ		old_rate;
	अचिन्हित दीर्घ		new_rate;
पूर्ण;

/**
 * काष्ठा clk_bulk_data - Data used क्रम bulk clk operations.
 *
 * @id: घड़ी consumer ID
 * @clk: काष्ठा clk * to store the associated घड़ी
 *
 * The CLK APIs provide a series of clk_bulk_() API calls as
 * a convenience to consumers which require multiple clks.  This
 * काष्ठाure is used to manage data क्रम these calls.
 */
काष्ठा clk_bulk_data अणु
	स्थिर अक्षर		*id;
	काष्ठा clk		*clk;
पूर्ण;

#अगर_घोषित CONFIG_COMMON_CLK

/**
 * clk_notअगरier_रेजिस्टर - रेजिस्टर a घड़ी rate-change notअगरier callback
 * @clk: घड़ी whose rate we are पूर्णांकerested in
 * @nb: notअगरier block with callback function poपूर्णांकer
 *
 * ProTip: debugging across notअगरier chains can be frustrating. Make sure that
 * your notअगरier callback function prपूर्णांकs a nice big warning in हाल of
 * failure.
 */
पूर्णांक clk_notअगरier_रेजिस्टर(काष्ठा clk *clk, काष्ठा notअगरier_block *nb);

/**
 * clk_notअगरier_unरेजिस्टर - unरेजिस्टर a घड़ी rate-change notअगरier callback
 * @clk: घड़ी whose rate we are no दीर्घer पूर्णांकerested in
 * @nb: notअगरier block which will be unरेजिस्टरed
 */
पूर्णांक clk_notअगरier_unरेजिस्टर(काष्ठा clk *clk, काष्ठा notअगरier_block *nb);

/**
 * devm_clk_notअगरier_रेजिस्टर - रेजिस्टर a managed rate-change notअगरier callback
 * @dev: device क्रम घड़ी "consumer"
 * @clk: घड़ी whose rate we are पूर्णांकerested in
 * @nb: notअगरier block with callback function poपूर्णांकer
 *
 * Returns 0 on success, -EERROR otherwise
 */
पूर्णांक devm_clk_notअगरier_रेजिस्टर(काष्ठा device *dev, काष्ठा clk *clk,
			       काष्ठा notअगरier_block *nb);

/**
 * clk_get_accuracy - obtain the घड़ी accuracy in ppb (parts per billion)
 *		      क्रम a घड़ी source.
 * @clk: घड़ी source
 *
 * This माला_लो the घड़ी source accuracy expressed in ppb.
 * A perfect घड़ी वापसs 0.
 */
दीर्घ clk_get_accuracy(काष्ठा clk *clk);

/**
 * clk_set_phase - adjust the phase shअगरt of a घड़ी संकेत
 * @clk: घड़ी संकेत source
 * @degrees: number of degrees the संकेत is shअगरted
 *
 * Shअगरts the phase of a घड़ी संकेत by the specअगरied degrees. Returns 0 on
 * success, -EERROR otherwise.
 */
पूर्णांक clk_set_phase(काष्ठा clk *clk, पूर्णांक degrees);

/**
 * clk_get_phase - वापस the phase shअगरt of a घड़ी संकेत
 * @clk: घड़ी संकेत source
 *
 * Returns the phase shअगरt of a घड़ी node in degrees, otherwise वापसs
 * -EERROR.
 */
पूर्णांक clk_get_phase(काष्ठा clk *clk);

/**
 * clk_set_duty_cycle - adjust the duty cycle ratio of a घड़ी संकेत
 * @clk: घड़ी संकेत source
 * @num: numerator of the duty cycle ratio to be applied
 * @den: denominator of the duty cycle ratio to be applied
 *
 * Adjust the duty cycle of a घड़ी संकेत by the specअगरied ratio. Returns 0 on
 * success, -EERROR otherwise.
 */
पूर्णांक clk_set_duty_cycle(काष्ठा clk *clk, अचिन्हित पूर्णांक num, अचिन्हित पूर्णांक den);

/**
 * clk_get_scaled_duty_cycle - वापस the duty cycle ratio of a घड़ी संकेत
 * @clk: घड़ी संकेत source
 * @scale: scaling factor to be applied to represent the ratio as an पूर्णांकeger
 *
 * Returns the duty cycle ratio multiplied by the scale provided, otherwise
 * वापसs -EERROR.
 */
पूर्णांक clk_get_scaled_duty_cycle(काष्ठा clk *clk, अचिन्हित पूर्णांक scale);

/**
 * clk_is_match - check अगर two clk's poपूर्णांक to the same hardware घड़ी
 * @p: clk compared against q
 * @q: clk compared against p
 *
 * Returns true अगर the two काष्ठा clk poपूर्णांकers both poपूर्णांक to the same hardware
 * घड़ी node. Put dअगरferently, वापसs true अगर @p and @q
 * share the same &काष्ठा clk_core object.
 *
 * Returns false otherwise. Note that two शून्य clks are treated as matching.
 */
bool clk_is_match(स्थिर काष्ठा clk *p, स्थिर काष्ठा clk *q);

#अन्यथा

अटल अंतरभूत पूर्णांक clk_notअगरier_रेजिस्टर(काष्ठा clk *clk,
					काष्ठा notअगरier_block *nb)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक clk_notअगरier_unरेजिस्टर(काष्ठा clk *clk,
					  काष्ठा notअगरier_block *nb)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक devm_clk_notअगरier_रेजिस्टर(काष्ठा device *dev,
					     काष्ठा clk *clk,
					     काष्ठा notअगरier_block *nb)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत दीर्घ clk_get_accuracy(काष्ठा clk *clk)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत दीर्घ clk_set_phase(काष्ठा clk *clk, पूर्णांक phase)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत दीर्घ clk_get_phase(काष्ठा clk *clk)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक clk_set_duty_cycle(काष्ठा clk *clk, अचिन्हित पूर्णांक num,
				     अचिन्हित पूर्णांक den)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक clk_get_scaled_duty_cycle(काष्ठा clk *clk,
						     अचिन्हित पूर्णांक scale)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool clk_is_match(स्थिर काष्ठा clk *p, स्थिर काष्ठा clk *q)
अणु
	वापस p == q;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_CLK_PREPARE
/**
 * clk_prepare - prepare a घड़ी source
 * @clk: घड़ी source
 *
 * This prepares the घड़ी source क्रम use.
 *
 * Must not be called from within atomic context.
 */
पूर्णांक clk_prepare(काष्ठा clk *clk);
पूर्णांक __must_check clk_bulk_prepare(पूर्णांक num_clks,
				  स्थिर काष्ठा clk_bulk_data *clks);

/**
 * clk_is_enabled_when_prepared - indicate अगर preparing a घड़ी also enables it.
 * @clk: घड़ी source
 *
 * Returns true अगर clk_prepare() implicitly enables the घड़ी, effectively
 * making clk_enable()/clk_disable() no-ops, false otherwise.
 *
 * This is of पूर्णांकerest मुख्यly to the घातer management code where actually
 * disabling the घड़ी also requires unpreparing it to have any material
 * effect.
 *
 * Regardless of the value वापसed here, the caller must always invoke
 * clk_enable() or clk_prepare_enable()  and counterparts क्रम usage counts
 * to be right.
 */
bool clk_is_enabled_when_prepared(काष्ठा clk *clk);
#अन्यथा
अटल अंतरभूत पूर्णांक clk_prepare(काष्ठा clk *clk)
अणु
	might_sleep();
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
clk_bulk_prepare(पूर्णांक num_clks, स्थिर काष्ठा clk_bulk_data *clks)
अणु
	might_sleep();
	वापस 0;
पूर्ण

अटल अंतरभूत bool clk_is_enabled_when_prepared(काष्ठा clk *clk)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/**
 * clk_unprepare - unकरो preparation of a घड़ी source
 * @clk: घड़ी source
 *
 * This unकरोes a previously prepared घड़ी.  The caller must balance
 * the number of prepare and unprepare calls.
 *
 * Must not be called from within atomic context.
 */
#अगर_घोषित CONFIG_HAVE_CLK_PREPARE
व्योम clk_unprepare(काष्ठा clk *clk);
व्योम clk_bulk_unprepare(पूर्णांक num_clks, स्थिर काष्ठा clk_bulk_data *clks);
#अन्यथा
अटल अंतरभूत व्योम clk_unprepare(काष्ठा clk *clk)
अणु
	might_sleep();
पूर्ण
अटल अंतरभूत व्योम clk_bulk_unprepare(पूर्णांक num_clks,
				      स्थिर काष्ठा clk_bulk_data *clks)
अणु
	might_sleep();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_CLK
/**
 * clk_get - lookup and obtain a reference to a घड़ी producer.
 * @dev: device क्रम घड़ी "consumer"
 * @id: घड़ी consumer ID
 *
 * Returns a काष्ठा clk corresponding to the घड़ी producer, or
 * valid IS_ERR() condition containing त्रुटि_सं.  The implementation
 * uses @dev and @id to determine the घड़ी consumer, and thereby
 * the घड़ी producer.  (IOW, @id may be identical strings, but
 * clk_get may वापस dअगरferent घड़ी producers depending on @dev.)
 *
 * Drivers must assume that the घड़ी source is not enabled.
 *
 * clk_get should not be called from within पूर्णांकerrupt context.
 */
काष्ठा clk *clk_get(काष्ठा device *dev, स्थिर अक्षर *id);

/**
 * clk_bulk_get - lookup and obtain a number of references to घड़ी producer.
 * @dev: device क्रम घड़ी "consumer"
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table of consumer
 *
 * This helper function allows drivers to get several clk consumers in one
 * operation. If any of the clk cannot be acquired then any clks
 * that were obtained will be मुक्तd beक्रमe वापसing to the caller.
 *
 * Returns 0 अगर all घड़ीs specअगरied in clk_bulk_data table are obtained
 * successfully, or valid IS_ERR() condition containing त्रुटि_सं.
 * The implementation uses @dev and @clk_bulk_data.id to determine the
 * घड़ी consumer, and thereby the घड़ी producer.
 * The घड़ी वापसed is stored in each @clk_bulk_data.clk field.
 *
 * Drivers must assume that the घड़ी source is not enabled.
 *
 * clk_bulk_get should not be called from within पूर्णांकerrupt context.
 */
पूर्णांक __must_check clk_bulk_get(काष्ठा device *dev, पूर्णांक num_clks,
			      काष्ठा clk_bulk_data *clks);
/**
 * clk_bulk_get_all - lookup and obtain all available references to घड़ी
 *		      producer.
 * @dev: device क्रम घड़ी "consumer"
 * @clks: poपूर्णांकer to the clk_bulk_data table of consumer
 *
 * This helper function allows drivers to get all clk consumers in one
 * operation. If any of the clk cannot be acquired then any clks
 * that were obtained will be मुक्तd beक्रमe वापसing to the caller.
 *
 * Returns a positive value क्रम the number of घड़ीs obtained जबतक the
 * घड़ी references are stored in the clk_bulk_data table in @clks field.
 * Returns 0 अगर there're none and a negative value अगर something failed.
 *
 * Drivers must assume that the घड़ी source is not enabled.
 *
 * clk_bulk_get should not be called from within पूर्णांकerrupt context.
 */
पूर्णांक __must_check clk_bulk_get_all(काष्ठा device *dev,
				  काष्ठा clk_bulk_data **clks);

/**
 * clk_bulk_get_optional - lookup and obtain a number of references to घड़ी producer
 * @dev: device क्रम घड़ी "consumer"
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table of consumer
 *
 * Behaves the same as clk_bulk_get() except where there is no घड़ी producer.
 * In this हाल, instead of वापसing -ENOENT, the function वापसs 0 and
 * शून्य क्रम a clk क्रम which a घड़ी producer could not be determined.
 */
पूर्णांक __must_check clk_bulk_get_optional(काष्ठा device *dev, पूर्णांक num_clks,
				       काष्ठा clk_bulk_data *clks);
/**
 * devm_clk_bulk_get - managed get multiple clk consumers
 * @dev: device क्रम घड़ी "consumer"
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table of consumer
 *
 * Return 0 on success, an त्रुटि_सं on failure.
 *
 * This helper function allows drivers to get several clk
 * consumers in one operation with management, the clks will
 * स्वतःmatically be मुक्तd when the device is unbound.
 */
पूर्णांक __must_check devm_clk_bulk_get(काष्ठा device *dev, पूर्णांक num_clks,
				   काष्ठा clk_bulk_data *clks);
/**
 * devm_clk_bulk_get_optional - managed get multiple optional consumer घड़ीs
 * @dev: device क्रम घड़ी "consumer"
 * @num_clks: the number of clk_bulk_data
 * @clks: poपूर्णांकer to the clk_bulk_data table of consumer
 *
 * Behaves the same as devm_clk_bulk_get() except where there is no घड़ी
 * producer.  In this हाल, instead of वापसing -ENOENT, the function वापसs
 * शून्य क्रम given clk. It is assumed all घड़ीs in clk_bulk_data are optional.
 *
 * Returns 0 अगर all घड़ीs specअगरied in clk_bulk_data table are obtained
 * successfully or क्रम any clk there was no clk provider available, otherwise
 * वापसs valid IS_ERR() condition containing त्रुटि_सं.
 * The implementation uses @dev and @clk_bulk_data.id to determine the
 * घड़ी consumer, and thereby the घड़ी producer.
 * The घड़ी वापसed is stored in each @clk_bulk_data.clk field.
 *
 * Drivers must assume that the घड़ी source is not enabled.
 *
 * clk_bulk_get should not be called from within पूर्णांकerrupt context.
 */
पूर्णांक __must_check devm_clk_bulk_get_optional(काष्ठा device *dev, पूर्णांक num_clks,
					    काष्ठा clk_bulk_data *clks);
/**
 * devm_clk_bulk_get_all - managed get multiple clk consumers
 * @dev: device क्रम घड़ी "consumer"
 * @clks: poपूर्णांकer to the clk_bulk_data table of consumer
 *
 * Returns a positive value क्रम the number of घड़ीs obtained जबतक the
 * घड़ी references are stored in the clk_bulk_data table in @clks field.
 * Returns 0 अगर there're none and a negative value अगर something failed.
 *
 * This helper function allows drivers to get several clk
 * consumers in one operation with management, the clks will
 * स्वतःmatically be मुक्तd when the device is unbound.
 */

पूर्णांक __must_check devm_clk_bulk_get_all(काष्ठा device *dev,
				       काष्ठा clk_bulk_data **clks);

/**
 * devm_clk_get - lookup and obtain a managed reference to a घड़ी producer.
 * @dev: device क्रम घड़ी "consumer"
 * @id: घड़ी consumer ID
 *
 * Returns a काष्ठा clk corresponding to the घड़ी producer, or
 * valid IS_ERR() condition containing त्रुटि_सं.  The implementation
 * uses @dev and @id to determine the घड़ी consumer, and thereby
 * the घड़ी producer.  (IOW, @id may be identical strings, but
 * clk_get may वापस dअगरferent घड़ी producers depending on @dev.)
 *
 * Drivers must assume that the घड़ी source is not enabled.
 *
 * devm_clk_get should not be called from within पूर्णांकerrupt context.
 *
 * The घड़ी will स्वतःmatically be मुक्तd when the device is unbound
 * from the bus.
 */
काष्ठा clk *devm_clk_get(काष्ठा device *dev, स्थिर अक्षर *id);

/**
 * devm_clk_get_optional - lookup and obtain a managed reference to an optional
 *			   घड़ी producer.
 * @dev: device क्रम घड़ी "consumer"
 * @id: घड़ी consumer ID
 *
 * Behaves the same as devm_clk_get() except where there is no घड़ी producer.
 * In this हाल, instead of वापसing -ENOENT, the function वापसs शून्य.
 */
काष्ठा clk *devm_clk_get_optional(काष्ठा device *dev, स्थिर अक्षर *id);

/**
 * devm_get_clk_from_child - lookup and obtain a managed reference to a
 *			     घड़ी producer from child node.
 * @dev: device क्रम घड़ी "consumer"
 * @np: poपूर्णांकer to घड़ी consumer node
 * @con_id: घड़ी consumer ID
 *
 * This function parses the घड़ीs, and uses them to look up the
 * काष्ठा clk from the रेजिस्टरed list of घड़ी providers by using
 * @np and @con_id
 *
 * The घड़ी will स्वतःmatically be मुक्तd when the device is unbound
 * from the bus.
 */
काष्ठा clk *devm_get_clk_from_child(काष्ठा device *dev,
				    काष्ठा device_node *np, स्थिर अक्षर *con_id);
/**
 * clk_rate_exclusive_get - get exclusivity over the rate control of a
 *                          producer
 * @clk: घड़ी source
 *
 * This function allows drivers to get exclusive control over the rate of a
 * provider. It prevents any other consumer to execute, even indirectly,
 * opereation which could alter the rate of the provider or cause glitches
 *
 * If exlusivity is claimed more than once on घड़ी, even by the same driver,
 * the rate effectively माला_लो locked as exclusivity can't be preempted.
 *
 * Must not be called from within atomic context.
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_rate_exclusive_get(काष्ठा clk *clk);

/**
 * clk_rate_exclusive_put - release exclusivity over the rate control of a
 *                          producer
 * @clk: घड़ी source
 *
 * This function allows drivers to release the exclusivity it previously got
 * from clk_rate_exclusive_get()
 *
 * The caller must balance the number of clk_rate_exclusive_get() and
 * clk_rate_exclusive_put() calls.
 *
 * Must not be called from within atomic context.
 */
व्योम clk_rate_exclusive_put(काष्ठा clk *clk);

/**
 * clk_enable - inक्रमm the प्रणाली when the घड़ी source should be running.
 * @clk: घड़ी source
 *
 * If the घड़ी can not be enabled/disabled, this should वापस success.
 *
 * May be called from atomic contexts.
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_enable(काष्ठा clk *clk);

/**
 * clk_bulk_enable - inक्रमm the प्रणाली when the set of clks should be running.
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table of consumer
 *
 * May be called from atomic contexts.
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक __must_check clk_bulk_enable(पूर्णांक num_clks,
				 स्थिर काष्ठा clk_bulk_data *clks);

/**
 * clk_disable - inक्रमm the प्रणाली when the घड़ी source is no दीर्घer required.
 * @clk: घड़ी source
 *
 * Inक्रमm the प्रणाली that a घड़ी source is no दीर्घer required by
 * a driver and may be shut करोwn.
 *
 * May be called from atomic contexts.
 *
 * Implementation detail: अगर the घड़ी source is shared between
 * multiple drivers, clk_enable() calls must be balanced by the
 * same number of clk_disable() calls क्रम the घड़ी source to be
 * disabled.
 */
व्योम clk_disable(काष्ठा clk *clk);

/**
 * clk_bulk_disable - inक्रमm the प्रणाली when the set of clks is no
 *		      दीर्घer required.
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table of consumer
 *
 * Inक्रमm the प्रणाली that a set of clks is no दीर्घer required by
 * a driver and may be shut करोwn.
 *
 * May be called from atomic contexts.
 *
 * Implementation detail: अगर the set of clks is shared between
 * multiple drivers, clk_bulk_enable() calls must be balanced by the
 * same number of clk_bulk_disable() calls क्रम the घड़ी source to be
 * disabled.
 */
व्योम clk_bulk_disable(पूर्णांक num_clks, स्थिर काष्ठा clk_bulk_data *clks);

/**
 * clk_get_rate - obtain the current घड़ी rate (in Hz) क्रम a घड़ी source.
 *		  This is only valid once the घड़ी source has been enabled.
 * @clk: घड़ी source
 */
अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk);

/**
 * clk_put	- "free" the घड़ी source
 * @clk: घड़ी source
 *
 * Note: drivers must ensure that all clk_enable calls made on this
 * घड़ी source are balanced by clk_disable calls prior to calling
 * this function.
 *
 * clk_put should not be called from within पूर्णांकerrupt context.
 */
व्योम clk_put(काष्ठा clk *clk);

/**
 * clk_bulk_put	- "free" the घड़ी source
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table of consumer
 *
 * Note: drivers must ensure that all clk_bulk_enable calls made on this
 * घड़ी source are balanced by clk_bulk_disable calls prior to calling
 * this function.
 *
 * clk_bulk_put should not be called from within पूर्णांकerrupt context.
 */
व्योम clk_bulk_put(पूर्णांक num_clks, काष्ठा clk_bulk_data *clks);

/**
 * clk_bulk_put_all - "free" all the घड़ी source
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table of consumer
 *
 * Note: drivers must ensure that all clk_bulk_enable calls made on this
 * घड़ी source are balanced by clk_bulk_disable calls prior to calling
 * this function.
 *
 * clk_bulk_put_all should not be called from within पूर्णांकerrupt context.
 */
व्योम clk_bulk_put_all(पूर्णांक num_clks, काष्ठा clk_bulk_data *clks);

/**
 * devm_clk_put	- "free" a managed घड़ी source
 * @dev: device used to acquire the घड़ी
 * @clk: घड़ी source acquired with devm_clk_get()
 *
 * Note: drivers must ensure that all clk_enable calls made on this
 * घड़ी source are balanced by clk_disable calls prior to calling
 * this function.
 *
 * clk_put should not be called from within पूर्णांकerrupt context.
 */
व्योम devm_clk_put(काष्ठा device *dev, काष्ठा clk *clk);

/*
 * The reमुख्यing APIs are optional क्रम machine class support.
 */


/**
 * clk_round_rate - adjust a rate to the exact rate a घड़ी can provide
 * @clk: घड़ी source
 * @rate: desired घड़ी rate in Hz
 *
 * This answers the question "अगर I were to pass @rate to clk_set_rate(),
 * what घड़ी rate would I end up with?" without changing the hardware
 * in any way.  In other words:
 *
 *   rate = clk_round_rate(clk, r);
 *
 * and:
 *
 *   clk_set_rate(clk, r);
 *   rate = clk_get_rate(clk);
 *
 * are equivalent except the क्रमmer करोes not modअगरy the घड़ी hardware
 * in any way.
 *
 * Returns rounded घड़ी rate in Hz, or negative त्रुटि_सं.
 */
दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);

/**
 * clk_set_rate - set the घड़ी rate क्रम a घड़ी source
 * @clk: घड़ी source
 * @rate: desired घड़ी rate in Hz
 *
 * Updating the rate starts at the top-most affected घड़ी and then
 * walks the tree करोwn to the bottom-most घड़ी that needs updating.
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);

/**
 * clk_set_rate_exclusive- set the घड़ी rate and claim exclusivity over
 *                         घड़ी source
 * @clk: घड़ी source
 * @rate: desired घड़ी rate in Hz
 *
 * This helper function allows drivers to atomically set the rate of a producer
 * and claim exclusivity over the rate control of the producer.
 *
 * It is essentially a combination of clk_set_rate() and
 * clk_rate_exclusite_get(). Caller must balance this call with a call to
 * clk_rate_exclusive_put()
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_rate_exclusive(काष्ठा clk *clk, अचिन्हित दीर्घ rate);

/**
 * clk_has_parent - check अगर a घड़ी is a possible parent क्रम another
 * @clk: घड़ी source
 * @parent: parent घड़ी source
 *
 * This function can be used in drivers that need to check that a घड़ी can be
 * the parent of another without actually changing the parent.
 *
 * Returns true अगर @parent is a possible parent क्रम @clk, false otherwise.
 */
bool clk_has_parent(काष्ठा clk *clk, काष्ठा clk *parent);

/**
 * clk_set_rate_range - set a rate range क्रम a घड़ी source
 * @clk: घड़ी source
 * @min: desired minimum घड़ी rate in Hz, inclusive
 * @max: desired maximum घड़ी rate in Hz, inclusive
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_rate_range(काष्ठा clk *clk, अचिन्हित दीर्घ min, अचिन्हित दीर्घ max);

/**
 * clk_set_min_rate - set a minimum घड़ी rate क्रम a घड़ी source
 * @clk: घड़ी source
 * @rate: desired minimum घड़ी rate in Hz, inclusive
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_min_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);

/**
 * clk_set_max_rate - set a maximum घड़ी rate क्रम a घड़ी source
 * @clk: घड़ी source
 * @rate: desired maximum घड़ी rate in Hz, inclusive
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_max_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);

/**
 * clk_set_parent - set the parent घड़ी source क्रम this घड़ी
 * @clk: घड़ी source
 * @parent: parent घड़ी source
 *
 * Returns success (0) or negative त्रुटि_सं.
 */
पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent);

/**
 * clk_get_parent - get the parent घड़ी source क्रम this घड़ी
 * @clk: घड़ी source
 *
 * Returns काष्ठा clk corresponding to parent घड़ी source, or
 * valid IS_ERR() condition containing त्रुटि_सं.
 */
काष्ठा clk *clk_get_parent(काष्ठा clk *clk);

/**
 * clk_get_sys - get a घड़ी based upon the device name
 * @dev_id: device name
 * @con_id: connection ID
 *
 * Returns a काष्ठा clk corresponding to the घड़ी producer, or
 * valid IS_ERR() condition containing त्रुटि_सं.  The implementation
 * uses @dev_id and @con_id to determine the घड़ी consumer, and
 * thereby the घड़ी producer. In contrast to clk_get() this function
 * takes the device name instead of the device itself क्रम identअगरication.
 *
 * Drivers must assume that the घड़ी source is not enabled.
 *
 * clk_get_sys should not be called from within पूर्णांकerrupt context.
 */
काष्ठा clk *clk_get_sys(स्थिर अक्षर *dev_id, स्थिर अक्षर *con_id);

/**
 * clk_save_context - save घड़ी context क्रम घातeroff
 *
 * Saves the context of the घड़ी रेजिस्टर क्रम घातerstates in which the
 * contents of the रेजिस्टरs will be lost. Occurs deep within the suspend
 * code so locking is not necessary.
 */
पूर्णांक clk_save_context(व्योम);

/**
 * clk_restore_context - restore घड़ी context after घातeroff
 *
 * This occurs with all घड़ीs enabled. Occurs deep within the resume code
 * so locking is not necessary.
 */
व्योम clk_restore_context(व्योम);

#अन्यथा /* !CONFIG_HAVE_CLK */

अटल अंतरभूत काष्ठा clk *clk_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check clk_bulk_get(काष्ठा device *dev, पूर्णांक num_clks,
					    काष्ठा clk_bulk_data *clks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check clk_bulk_get_optional(काष्ठा device *dev,
				पूर्णांक num_clks, काष्ठा clk_bulk_data *clks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check clk_bulk_get_all(काष्ठा device *dev,
					 काष्ठा clk_bulk_data **clks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा clk *devm_clk_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा clk *devm_clk_get_optional(काष्ठा device *dev,
						स्थिर अक्षर *id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check devm_clk_bulk_get(काष्ठा device *dev, पूर्णांक num_clks,
						 काष्ठा clk_bulk_data *clks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check devm_clk_bulk_get_optional(काष्ठा device *dev,
				पूर्णांक num_clks, काष्ठा clk_bulk_data *clks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check devm_clk_bulk_get_all(काष्ठा device *dev,
						     काष्ठा clk_bulk_data **clks)
अणु

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा clk *devm_get_clk_from_child(काष्ठा device *dev,
				काष्ठा device_node *np, स्थिर अक्षर *con_id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम clk_put(काष्ठा clk *clk) अणुपूर्ण

अटल अंतरभूत व्योम clk_bulk_put(पूर्णांक num_clks, काष्ठा clk_bulk_data *clks) अणुपूर्ण

अटल अंतरभूत व्योम clk_bulk_put_all(पूर्णांक num_clks, काष्ठा clk_bulk_data *clks) अणुपूर्ण

अटल अंतरभूत व्योम devm_clk_put(काष्ठा device *dev, काष्ठा clk *clk) अणुपूर्ण


अटल अंतरभूत पूर्णांक clk_rate_exclusive_get(काष्ठा clk *clk)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम clk_rate_exclusive_put(काष्ठा clk *clk) अणुपूर्ण

अटल अंतरभूत पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check clk_bulk_enable(पूर्णांक num_clks,
					       स्थिर काष्ठा clk_bulk_data *clks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम clk_disable(काष्ठा clk *clk) अणुपूर्ण


अटल अंतरभूत व्योम clk_bulk_disable(पूर्णांक num_clks,
				    स्थिर काष्ठा clk_bulk_data *clks) अणुपूर्ण

अटल अंतरभूत अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक clk_set_rate_exclusive(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool clk_has_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक clk_set_rate_range(काष्ठा clk *clk, अचिन्हित दीर्घ min,
				     अचिन्हित दीर्घ max)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक clk_set_min_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक clk_set_max_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा clk *clk_get_parent(काष्ठा clk *clk)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा clk *clk_get_sys(स्थिर अक्षर *dev_id, स्थिर अक्षर *con_id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक clk_save_context(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम clk_restore_context(व्योम) अणुपूर्ण

#पूर्ण_अगर

/* clk_prepare_enable helps हालs using clk_enable in non-atomic context. */
अटल अंतरभूत पूर्णांक clk_prepare_enable(काष्ठा clk *clk)
अणु
	पूर्णांक ret;

	ret = clk_prepare(clk);
	अगर (ret)
		वापस ret;
	ret = clk_enable(clk);
	अगर (ret)
		clk_unprepare(clk);

	वापस ret;
पूर्ण

/* clk_disable_unprepare helps हालs using clk_disable in non-atomic context. */
अटल अंतरभूत व्योम clk_disable_unprepare(काष्ठा clk *clk)
अणु
	clk_disable(clk);
	clk_unprepare(clk);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
clk_bulk_prepare_enable(पूर्णांक num_clks, स्थिर काष्ठा clk_bulk_data *clks)
अणु
	पूर्णांक ret;

	ret = clk_bulk_prepare(num_clks, clks);
	अगर (ret)
		वापस ret;
	ret = clk_bulk_enable(num_clks, clks);
	अगर (ret)
		clk_bulk_unprepare(num_clks, clks);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम clk_bulk_disable_unprepare(पूर्णांक num_clks,
					      स्थिर काष्ठा clk_bulk_data *clks)
अणु
	clk_bulk_disable(num_clks, clks);
	clk_bulk_unprepare(num_clks, clks);
पूर्ण

/**
 * clk_get_optional - lookup and obtain a reference to an optional घड़ी
 *		      producer.
 * @dev: device क्रम घड़ी "consumer"
 * @id: घड़ी consumer ID
 *
 * Behaves the same as clk_get() except where there is no घड़ी producer. In
 * this हाल, instead of वापसing -ENOENT, the function वापसs शून्य.
 */
अटल अंतरभूत काष्ठा clk *clk_get_optional(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा clk *clk = clk_get(dev, id);

	अगर (clk == ERR_PTR(-ENOENT))
		वापस शून्य;

	वापस clk;
पूर्ण

#अगर defined(CONFIG_OF) && defined(CONFIG_COMMON_CLK)
काष्ठा clk *of_clk_get(काष्ठा device_node *np, पूर्णांक index);
काष्ठा clk *of_clk_get_by_name(काष्ठा device_node *np, स्थिर अक्षर *name);
काष्ठा clk *of_clk_get_from_provider(काष्ठा of_phandle_args *clkspec);
#अन्यथा
अटल अंतरभूत काष्ठा clk *of_clk_get(काष्ठा device_node *np, पूर्णांक index)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत काष्ठा clk *of_clk_get_by_name(काष्ठा device_node *np,
					     स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत काष्ठा clk *of_clk_get_from_provider(काष्ठा of_phandle_args *clkspec)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
