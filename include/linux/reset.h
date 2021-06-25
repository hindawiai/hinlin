<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RESET_H_
#घोषणा _LINUX_RESET_H_

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

काष्ठा device;
काष्ठा device_node;
काष्ठा reset_control;

/**
 * काष्ठा reset_control_bulk_data - Data used क्रम bulk reset control operations.
 *
 * @id: reset control consumer ID
 * @rstc: काष्ठा reset_control * to store the associated reset control
 *
 * The reset APIs provide a series of reset_control_bulk_*() API calls as
 * a convenience to consumers which require multiple reset controls.
 * This काष्ठाure is used to manage data क्रम these calls.
 */
काष्ठा reset_control_bulk_data अणु
	स्थिर अक्षर			*id;
	काष्ठा reset_control		*rstc;
पूर्ण;

#अगर_घोषित CONFIG_RESET_CONTROLLER

पूर्णांक reset_control_reset(काष्ठा reset_control *rstc);
पूर्णांक reset_control_rearm(काष्ठा reset_control *rstc);
पूर्णांक reset_control_निश्चित(काष्ठा reset_control *rstc);
पूर्णांक reset_control_deनिश्चित(काष्ठा reset_control *rstc);
पूर्णांक reset_control_status(काष्ठा reset_control *rstc);
पूर्णांक reset_control_acquire(काष्ठा reset_control *rstc);
व्योम reset_control_release(काष्ठा reset_control *rstc);

पूर्णांक reset_control_bulk_reset(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs);
पूर्णांक reset_control_bulk_निश्चित(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs);
पूर्णांक reset_control_bulk_deनिश्चित(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs);
पूर्णांक reset_control_bulk_acquire(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs);
व्योम reset_control_bulk_release(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs);

काष्ठा reset_control *__of_reset_control_get(काष्ठा device_node *node,
				     स्थिर अक्षर *id, पूर्णांक index, bool shared,
				     bool optional, bool acquired);
काष्ठा reset_control *__reset_control_get(काष्ठा device *dev, स्थिर अक्षर *id,
					  पूर्णांक index, bool shared,
					  bool optional, bool acquired);
व्योम reset_control_put(काष्ठा reset_control *rstc);
पूर्णांक __reset_control_bulk_get(काष्ठा device *dev, पूर्णांक num_rstcs,
			     काष्ठा reset_control_bulk_data *rstcs,
			     bool shared, bool optional, bool acquired);
व्योम reset_control_bulk_put(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs);

पूर्णांक __device_reset(काष्ठा device *dev, bool optional);
काष्ठा reset_control *__devm_reset_control_get(काष्ठा device *dev,
				     स्थिर अक्षर *id, पूर्णांक index, bool shared,
				     bool optional, bool acquired);
पूर्णांक __devm_reset_control_bulk_get(काष्ठा device *dev, पूर्णांक num_rstcs,
				  काष्ठा reset_control_bulk_data *rstcs,
				  bool shared, bool optional, bool acquired);

काष्ठा reset_control *devm_reset_control_array_get(काष्ठा device *dev,
						   bool shared, bool optional);
काष्ठा reset_control *of_reset_control_array_get(काष्ठा device_node *np,
						 bool shared, bool optional,
						 bool acquired);

पूर्णांक reset_control_get_count(काष्ठा device *dev);

#अन्यथा

अटल अंतरभूत पूर्णांक reset_control_reset(काष्ठा reset_control *rstc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reset_control_rearm(काष्ठा reset_control *rstc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reset_control_निश्चित(काष्ठा reset_control *rstc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reset_control_deनिश्चित(काष्ठा reset_control *rstc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reset_control_status(काष्ठा reset_control *rstc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक reset_control_acquire(काष्ठा reset_control *rstc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम reset_control_release(काष्ठा reset_control *rstc)
अणु
पूर्ण

अटल अंतरभूत व्योम reset_control_put(काष्ठा reset_control *rstc)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक __device_reset(काष्ठा device *dev, bool optional)
अणु
	वापस optional ? 0 : -ENOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा reset_control *__of_reset_control_get(
					काष्ठा device_node *node,
					स्थिर अक्षर *id, पूर्णांक index, bool shared,
					bool optional, bool acquired)
अणु
	वापस optional ? शून्य : ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *__reset_control_get(
					काष्ठा device *dev, स्थिर अक्षर *id,
					पूर्णांक index, bool shared, bool optional,
					bool acquired)
अणु
	वापस optional ? शून्य : ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक
reset_control_bulk_reset(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
reset_control_bulk_निश्चित(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
reset_control_bulk_deनिश्चित(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
reset_control_bulk_acquire(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
reset_control_bulk_release(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
__reset_control_bulk_get(काष्ठा device *dev, पूर्णांक num_rstcs,
			 काष्ठा reset_control_bulk_data *rstcs,
			 bool shared, bool optional, bool acquired)
अणु
	वापस optional ? 0 : -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम
reset_control_bulk_put(पूर्णांक num_rstcs, काष्ठा reset_control_bulk_data *rstcs)
अणु
पूर्ण

अटल अंतरभूत काष्ठा reset_control *__devm_reset_control_get(
					काष्ठा device *dev, स्थिर अक्षर *id,
					पूर्णांक index, bool shared, bool optional,
					bool acquired)
अणु
	वापस optional ? शून्य : ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक
__devm_reset_control_bulk_get(काष्ठा device *dev, पूर्णांक num_rstcs,
			      काष्ठा reset_control_bulk_data *rstcs,
			      bool shared, bool optional, bool acquired)
अणु
	वापस optional ? 0 : -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
devm_reset_control_array_get(काष्ठा device *dev, bool shared, bool optional)
अणु
	वापस optional ? शून्य : ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
of_reset_control_array_get(काष्ठा device_node *np, bool shared, bool optional,
			   bool acquired)
अणु
	वापस optional ? शून्य : ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक reset_control_get_count(काष्ठा device *dev)
अणु
	वापस -ENOENT;
पूर्ण

#पूर्ण_अगर /* CONFIG_RESET_CONTROLLER */

अटल अंतरभूत पूर्णांक __must_check device_reset(काष्ठा device *dev)
अणु
	वापस __device_reset(dev, false);
पूर्ण

अटल अंतरभूत पूर्णांक device_reset_optional(काष्ठा device *dev)
अणु
	वापस __device_reset(dev, true);
पूर्ण

/**
 * reset_control_get_exclusive - Lookup and obtain an exclusive reference
 *                               to a reset controller.
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Returns a काष्ठा reset_control or IS_ERR() condition containing त्रुटि_सं.
 * If this function is called more than once क्रम the same reset_control it will
 * वापस -EBUSY.
 *
 * See reset_control_get_shared() क्रम details on shared references to
 * reset-controls.
 *
 * Use of id names is optional.
 */
अटल अंतरभूत काष्ठा reset_control *
__must_check reset_control_get_exclusive(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस __reset_control_get(dev, id, 0, false, false, true);
पूर्ण

/**
 * reset_control_bulk_get_exclusive - Lookup and obtain exclusive references to
 *                                    multiple reset controllers.
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Fills the rstcs array with poपूर्णांकers to exclusive reset controls and
 * वापसs 0, or an IS_ERR() condition containing त्रुटि_सं.
 */
अटल अंतरभूत पूर्णांक __must_check
reset_control_bulk_get_exclusive(काष्ठा device *dev, पूर्णांक num_rstcs,
				 काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __reset_control_bulk_get(dev, num_rstcs, rstcs, false, false, true);
पूर्ण

/**
 * reset_control_get_exclusive_released - Lookup and obtain a temoprarily
 *                                        exclusive reference to a reset
 *                                        controller.
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Returns a काष्ठा reset_control or IS_ERR() condition containing त्रुटि_सं.
 * reset-controls वापसed by this function must be acquired via
 * reset_control_acquire() beक्रमe they can be used and should be released
 * via reset_control_release() afterwards.
 *
 * Use of id names is optional.
 */
अटल अंतरभूत काष्ठा reset_control *
__must_check reset_control_get_exclusive_released(काष्ठा device *dev,
						  स्थिर अक्षर *id)
अणु
	वापस __reset_control_get(dev, id, 0, false, false, false);
पूर्ण

/**
 * reset_control_bulk_get_exclusive_released - Lookup and obtain temporarily
 *                                    exclusive references to multiple reset
 *                                    controllers.
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Fills the rstcs array with poपूर्णांकers to exclusive reset controls and
 * वापसs 0, or an IS_ERR() condition containing त्रुटि_सं.
 * reset-controls वापसed by this function must be acquired via
 * reset_control_bulk_acquire() beक्रमe they can be used and should be released
 * via reset_control_bulk_release() afterwards.
 */
अटल अंतरभूत पूर्णांक __must_check
reset_control_bulk_get_exclusive_released(काष्ठा device *dev, पूर्णांक num_rstcs,
					  काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __reset_control_bulk_get(dev, num_rstcs, rstcs, false, false, false);
पूर्ण

/**
 * reset_control_bulk_get_optional_exclusive_released - Lookup and obtain optional
 *                                    temporarily exclusive references to multiple
 *                                    reset controllers.
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Optional variant of reset_control_bulk_get_exclusive_released(). If the
 * requested reset is not specअगरied in the device tree, this function वापसs 0
 * instead of an error and missing rtsc is set to शून्य.
 *
 * See reset_control_bulk_get_exclusive_released() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
reset_control_bulk_get_optional_exclusive_released(काष्ठा device *dev, पूर्णांक num_rstcs,
						   काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __reset_control_bulk_get(dev, num_rstcs, rstcs, false, true, false);
पूर्ण

/**
 * reset_control_get_shared - Lookup and obtain a shared reference to a
 *                            reset controller.
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Returns a काष्ठा reset_control or IS_ERR() condition containing त्रुटि_सं.
 * This function is पूर्णांकended क्रम use with reset-controls which are shared
 * between hardware blocks.
 *
 * When a reset-control is shared, the behavior of reset_control_निश्चित /
 * deनिश्चित is changed, the reset-core will keep track of a deनिश्चित_count
 * and only (re-)निश्चित the reset after reset_control_निश्चित has been called
 * as many बार as reset_control_deनिश्चित was called. Also see the remark
 * about shared reset-controls in the reset_control_निश्चित करोcs.
 *
 * Calling reset_control_निश्चित without first calling reset_control_deनिश्चित
 * is not allowed on a shared reset control. Calling reset_control_reset is
 * also not allowed on a shared reset control.
 *
 * Use of id names is optional.
 */
अटल अंतरभूत काष्ठा reset_control *reset_control_get_shared(
					काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस __reset_control_get(dev, id, 0, true, false, false);
पूर्ण

/**
 * reset_control_bulk_get_shared - Lookup and obtain shared references to
 *                                 multiple reset controllers.
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Fills the rstcs array with poपूर्णांकers to shared reset controls and
 * वापसs 0, or an IS_ERR() condition containing त्रुटि_सं.
 */
अटल अंतरभूत पूर्णांक __must_check
reset_control_bulk_get_shared(काष्ठा device *dev, पूर्णांक num_rstcs,
			      काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __reset_control_bulk_get(dev, num_rstcs, rstcs, true, false, false);
पूर्ण

/**
 * reset_control_get_optional_exclusive - optional reset_control_get_exclusive()
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Optional variant of reset_control_get_exclusive(). If the requested reset
 * is not specअगरied in the device tree, this function वापसs शून्य instead of
 * an error.
 *
 * See reset_control_get_exclusive() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *reset_control_get_optional_exclusive(
					काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस __reset_control_get(dev, id, 0, false, true, true);
पूर्ण

/**
 * reset_control_bulk_get_optional_exclusive - optional
 *                                             reset_control_bulk_get_exclusive()
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Optional variant of reset_control_bulk_get_exclusive(). If any of the
 * requested resets are not specअगरied in the device tree, this function sets
 * them to शून्य instead of वापसing an error.
 *
 * See reset_control_bulk_get_exclusive() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
reset_control_bulk_get_optional_exclusive(काष्ठा device *dev, पूर्णांक num_rstcs,
					  काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __reset_control_bulk_get(dev, num_rstcs, rstcs, false, true, true);
पूर्ण

/**
 * reset_control_get_optional_shared - optional reset_control_get_shared()
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Optional variant of reset_control_get_shared(). If the requested reset
 * is not specअगरied in the device tree, this function वापसs शून्य instead of
 * an error.
 *
 * See reset_control_get_shared() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *reset_control_get_optional_shared(
					काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस __reset_control_get(dev, id, 0, true, true, false);
पूर्ण

/**
 * reset_control_bulk_get_optional_shared - optional
 *                                             reset_control_bulk_get_shared()
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Optional variant of reset_control_bulk_get_shared(). If the requested resets
 * are not specअगरied in the device tree, this function sets them to शून्य
 * instead of वापसing an error.
 *
 * See reset_control_bulk_get_shared() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
reset_control_bulk_get_optional_shared(काष्ठा device *dev, पूर्णांक num_rstcs,
				       काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __reset_control_bulk_get(dev, num_rstcs, rstcs, true, true, false);
पूर्ण

/**
 * of_reset_control_get_exclusive - Lookup and obtain an exclusive reference
 *                                  to a reset controller.
 * @node: device to be reset by the controller
 * @id: reset line name
 *
 * Returns a काष्ठा reset_control or IS_ERR() condition containing त्रुटि_सं.
 *
 * Use of id names is optional.
 */
अटल अंतरभूत काष्ठा reset_control *of_reset_control_get_exclusive(
				काष्ठा device_node *node, स्थिर अक्षर *id)
अणु
	वापस __of_reset_control_get(node, id, 0, false, false, true);
पूर्ण

/**
 * of_reset_control_get_shared - Lookup and obtain a shared reference
 *                               to a reset controller.
 * @node: device to be reset by the controller
 * @id: reset line name
 *
 * When a reset-control is shared, the behavior of reset_control_निश्चित /
 * deनिश्चित is changed, the reset-core will keep track of a deनिश्चित_count
 * and only (re-)निश्चित the reset after reset_control_निश्चित has been called
 * as many बार as reset_control_deनिश्चित was called. Also see the remark
 * about shared reset-controls in the reset_control_निश्चित करोcs.
 *
 * Calling reset_control_निश्चित without first calling reset_control_deनिश्चित
 * is not allowed on a shared reset control. Calling reset_control_reset is
 * also not allowed on a shared reset control.
 * Returns a काष्ठा reset_control or IS_ERR() condition containing त्रुटि_सं.
 *
 * Use of id names is optional.
 */
अटल अंतरभूत काष्ठा reset_control *of_reset_control_get_shared(
				काष्ठा device_node *node, स्थिर अक्षर *id)
अणु
	वापस __of_reset_control_get(node, id, 0, true, false, false);
पूर्ण

/**
 * of_reset_control_get_exclusive_by_index - Lookup and obtain an exclusive
 *                                           reference to a reset controller
 *                                           by index.
 * @node: device to be reset by the controller
 * @index: index of the reset controller
 *
 * This is to be used to perक्रमm a list of resets क्रम a device or घातer करोमुख्य
 * in whatever order. Returns a काष्ठा reset_control or IS_ERR() condition
 * containing त्रुटि_सं.
 */
अटल अंतरभूत काष्ठा reset_control *of_reset_control_get_exclusive_by_index(
					काष्ठा device_node *node, पूर्णांक index)
अणु
	वापस __of_reset_control_get(node, शून्य, index, false, false, true);
पूर्ण

/**
 * of_reset_control_get_shared_by_index - Lookup and obtain a shared
 *                                        reference to a reset controller
 *                                        by index.
 * @node: device to be reset by the controller
 * @index: index of the reset controller
 *
 * When a reset-control is shared, the behavior of reset_control_निश्चित /
 * deनिश्चित is changed, the reset-core will keep track of a deनिश्चित_count
 * and only (re-)निश्चित the reset after reset_control_निश्चित has been called
 * as many बार as reset_control_deनिश्चित was called. Also see the remark
 * about shared reset-controls in the reset_control_निश्चित करोcs.
 *
 * Calling reset_control_निश्चित without first calling reset_control_deनिश्चित
 * is not allowed on a shared reset control. Calling reset_control_reset is
 * also not allowed on a shared reset control.
 * Returns a काष्ठा reset_control or IS_ERR() condition containing त्रुटि_सं.
 *
 * This is to be used to perक्रमm a list of resets क्रम a device or घातer करोमुख्य
 * in whatever order. Returns a काष्ठा reset_control or IS_ERR() condition
 * containing त्रुटि_सं.
 */
अटल अंतरभूत काष्ठा reset_control *of_reset_control_get_shared_by_index(
					काष्ठा device_node *node, पूर्णांक index)
अणु
	वापस __of_reset_control_get(node, शून्य, index, true, false, false);
पूर्ण

/**
 * devm_reset_control_get_exclusive - resource managed
 *                                    reset_control_get_exclusive()
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Managed reset_control_get_exclusive(). For reset controllers वापसed
 * from this function, reset_control_put() is called स्वतःmatically on driver
 * detach.
 *
 * See reset_control_get_exclusive() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *
__must_check devm_reset_control_get_exclusive(काष्ठा device *dev,
					      स्थिर अक्षर *id)
अणु
	वापस __devm_reset_control_get(dev, id, 0, false, false, true);
पूर्ण

/**
 * devm_reset_control_bulk_get_exclusive - resource managed
 *                                         reset_control_bulk_get_exclusive()
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Managed reset_control_bulk_get_exclusive(). For reset controllers वापसed
 * from this function, reset_control_put() is called स्वतःmatically on driver
 * detach.
 *
 * See reset_control_bulk_get_exclusive() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
devm_reset_control_bulk_get_exclusive(काष्ठा device *dev, पूर्णांक num_rstcs,
				      काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __devm_reset_control_bulk_get(dev, num_rstcs, rstcs, false, false, true);
पूर्ण

/**
 * devm_reset_control_get_exclusive_released - resource managed
 *                                             reset_control_get_exclusive_released()
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Managed reset_control_get_exclusive_released(). For reset controllers
 * वापसed from this function, reset_control_put() is called स्वतःmatically on
 * driver detach.
 *
 * See reset_control_get_exclusive_released() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *
__must_check devm_reset_control_get_exclusive_released(काष्ठा device *dev,
						       स्थिर अक्षर *id)
अणु
	वापस __devm_reset_control_get(dev, id, 0, false, false, false);
पूर्ण

/**
 * devm_reset_control_bulk_get_exclusive_released - resource managed
 *                                                  reset_control_bulk_get_exclusive_released()
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Managed reset_control_bulk_get_exclusive_released(). For reset controllers
 * वापसed from this function, reset_control_put() is called स्वतःmatically on
 * driver detach.
 *
 * See reset_control_bulk_get_exclusive_released() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
devm_reset_control_bulk_get_exclusive_released(काष्ठा device *dev, पूर्णांक num_rstcs,
					       काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __devm_reset_control_bulk_get(dev, num_rstcs, rstcs, false, false, false);
पूर्ण

/**
 * devm_reset_control_get_optional_exclusive_released - resource managed
 *                                                      reset_control_get_optional_exclusive_released()
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Managed-and-optional variant of reset_control_get_exclusive_released(). For
 * reset controllers वापसed from this function, reset_control_put() is called
 * स्वतःmatically on driver detach.
 *
 * See reset_control_get_exclusive_released() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *
__must_check devm_reset_control_get_optional_exclusive_released(काष्ठा device *dev,
								स्थिर अक्षर *id)
अणु
	वापस __devm_reset_control_get(dev, id, 0, false, true, false);
पूर्ण

/**
 * devm_reset_control_bulk_get_optional_exclusive_released - resource managed
 *                                                           reset_control_bulk_optional_get_exclusive_released()
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Managed reset_control_bulk_optional_get_exclusive_released(). For reset
 * controllers वापसed from this function, reset_control_put() is called
 * स्वतःmatically on driver detach.
 *
 * See reset_control_bulk_optional_get_exclusive_released() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
devm_reset_control_bulk_get_optional_exclusive_released(काष्ठा device *dev, पूर्णांक num_rstcs,
							काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __devm_reset_control_bulk_get(dev, num_rstcs, rstcs, false, true, false);
पूर्ण

/**
 * devm_reset_control_get_shared - resource managed reset_control_get_shared()
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Managed reset_control_get_shared(). For reset controllers वापसed from
 * this function, reset_control_put() is called स्वतःmatically on driver detach.
 * See reset_control_get_shared() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *devm_reset_control_get_shared(
					काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस __devm_reset_control_get(dev, id, 0, true, false, false);
पूर्ण

/**
 * devm_reset_control_bulk_get_shared - resource managed
 *                                      reset_control_bulk_get_shared()
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Managed reset_control_bulk_get_shared(). For reset controllers वापसed
 * from this function, reset_control_put() is called स्वतःmatically on driver
 * detach.
 *
 * See reset_control_bulk_get_shared() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
devm_reset_control_bulk_get_shared(काष्ठा device *dev, पूर्णांक num_rstcs,
				   काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __devm_reset_control_bulk_get(dev, num_rstcs, rstcs, true, false, false);
पूर्ण

/**
 * devm_reset_control_get_optional_exclusive - resource managed
 *                                             reset_control_get_optional_exclusive()
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Managed reset_control_get_optional_exclusive(). For reset controllers
 * वापसed from this function, reset_control_put() is called स्वतःmatically on
 * driver detach.
 *
 * See reset_control_get_optional_exclusive() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *devm_reset_control_get_optional_exclusive(
					काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस __devm_reset_control_get(dev, id, 0, false, true, true);
पूर्ण

/**
 * devm_reset_control_bulk_get_optional_exclusive - resource managed
 *                                                  reset_control_bulk_get_optional_exclusive()
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Managed reset_control_bulk_get_optional_exclusive(). For reset controllers
 * वापसed from this function, reset_control_put() is called स्वतःmatically on
 * driver detach.
 *
 * See reset_control_bulk_get_optional_exclusive() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
devm_reset_control_bulk_get_optional_exclusive(काष्ठा device *dev, पूर्णांक num_rstcs,
					       काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __devm_reset_control_bulk_get(dev, num_rstcs, rstcs, true, false, true);
पूर्ण

/**
 * devm_reset_control_get_optional_shared - resource managed
 *                                          reset_control_get_optional_shared()
 * @dev: device to be reset by the controller
 * @id: reset line name
 *
 * Managed reset_control_get_optional_shared(). For reset controllers वापसed
 * from this function, reset_control_put() is called स्वतःmatically on driver
 * detach.
 *
 * See reset_control_get_optional_shared() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *devm_reset_control_get_optional_shared(
					काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस __devm_reset_control_get(dev, id, 0, true, true, false);
पूर्ण

/**
 * devm_reset_control_bulk_get_optional_shared - resource managed
 *                                               reset_control_bulk_get_optional_shared()
 * @dev: device to be reset by the controller
 * @num_rstcs: number of entries in rstcs array
 * @rstcs: array of काष्ठा reset_control_bulk_data with reset line names set
 *
 * Managed reset_control_bulk_get_optional_shared(). For reset controllers
 * वापसed from this function, reset_control_put() is called स्वतःmatically on
 * driver detach.
 *
 * See reset_control_bulk_get_optional_shared() क्रम more inक्रमmation.
 */
अटल अंतरभूत पूर्णांक __must_check
devm_reset_control_bulk_get_optional_shared(काष्ठा device *dev, पूर्णांक num_rstcs,
					    काष्ठा reset_control_bulk_data *rstcs)
अणु
	वापस __devm_reset_control_bulk_get(dev, num_rstcs, rstcs, true, true, false);
पूर्ण

/**
 * devm_reset_control_get_exclusive_by_index - resource managed
 *                                             reset_control_get_exclusive()
 * @dev: device to be reset by the controller
 * @index: index of the reset controller
 *
 * Managed reset_control_get_exclusive(). For reset controllers वापसed from
 * this function, reset_control_put() is called स्वतःmatically on driver
 * detach.
 *
 * See reset_control_get_exclusive() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *
devm_reset_control_get_exclusive_by_index(काष्ठा device *dev, पूर्णांक index)
अणु
	वापस __devm_reset_control_get(dev, शून्य, index, false, false, true);
पूर्ण

/**
 * devm_reset_control_get_shared_by_index - resource managed
 *                                          reset_control_get_shared
 * @dev: device to be reset by the controller
 * @index: index of the reset controller
 *
 * Managed reset_control_get_shared(). For reset controllers वापसed from
 * this function, reset_control_put() is called स्वतःmatically on driver detach.
 * See reset_control_get_shared() क्रम more inक्रमmation.
 */
अटल अंतरभूत काष्ठा reset_control *
devm_reset_control_get_shared_by_index(काष्ठा device *dev, पूर्णांक index)
अणु
	वापस __devm_reset_control_get(dev, शून्य, index, true, false, false);
पूर्ण

/*
 * TEMPORARY calls to use during transition:
 *
 *   of_reset_control_get() => of_reset_control_get_exclusive()
 *
 * These अंतरभूत function calls will be हटाओd once all consumers
 * have been moved over to the new explicit API.
 */
अटल अंतरभूत काष्ठा reset_control *of_reset_control_get(
				काष्ठा device_node *node, स्थिर अक्षर *id)
अणु
	वापस of_reset_control_get_exclusive(node, id);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *of_reset_control_get_by_index(
				काष्ठा device_node *node, पूर्णांक index)
अणु
	वापस of_reset_control_get_exclusive_by_index(node, index);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *devm_reset_control_get(
				काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस devm_reset_control_get_exclusive(dev, id);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *devm_reset_control_get_optional(
				काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	वापस devm_reset_control_get_optional_exclusive(dev, id);

पूर्ण

अटल अंतरभूत काष्ठा reset_control *devm_reset_control_get_by_index(
				काष्ठा device *dev, पूर्णांक index)
अणु
	वापस devm_reset_control_get_exclusive_by_index(dev, index);
पूर्ण

/*
 * APIs to manage a list of reset controllers
 */
अटल अंतरभूत काष्ठा reset_control *
devm_reset_control_array_get_exclusive(काष्ठा device *dev)
अणु
	वापस devm_reset_control_array_get(dev, false, false);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
devm_reset_control_array_get_shared(काष्ठा device *dev)
अणु
	वापस devm_reset_control_array_get(dev, true, false);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
devm_reset_control_array_get_optional_exclusive(काष्ठा device *dev)
अणु
	वापस devm_reset_control_array_get(dev, false, true);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
devm_reset_control_array_get_optional_shared(काष्ठा device *dev)
अणु
	वापस devm_reset_control_array_get(dev, true, true);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
of_reset_control_array_get_exclusive(काष्ठा device_node *node)
अणु
	वापस of_reset_control_array_get(node, false, false, true);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
of_reset_control_array_get_exclusive_released(काष्ठा device_node *node)
अणु
	वापस of_reset_control_array_get(node, false, false, false);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
of_reset_control_array_get_shared(काष्ठा device_node *node)
अणु
	वापस of_reset_control_array_get(node, true, false, true);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
of_reset_control_array_get_optional_exclusive(काष्ठा device_node *node)
अणु
	वापस of_reset_control_array_get(node, false, true, true);
पूर्ण

अटल अंतरभूत काष्ठा reset_control *
of_reset_control_array_get_optional_shared(काष्ठा device_node *node)
अणु
	वापस of_reset_control_array_get(node, true, true, true);
पूर्ण
#पूर्ण_अगर
