<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित _DRM_MANAGED_H_
#घोषणा _DRM_MANAGED_H_

#समावेश <linux/gfp.h>
#समावेश <linux/overflow.h>
#समावेश <linux/types.h>

काष्ठा drm_device;

प्रकार व्योम (*drmres_release_t)(काष्ठा drm_device *dev, व्योम *res);

/**
 * drmm_add_action - add a managed release action to a &drm_device
 * @dev: DRM device
 * @action: function which should be called when @dev is released
 * @data: opaque poपूर्णांकer, passed to @action
 *
 * This function adds the @release action with optional parameter @data to the
 * list of cleanup actions क्रम @dev. The cleanup actions will be run in reverse
 * order in the final drm_dev_put() call क्रम @dev.
 */
#घोषणा drmm_add_action(dev, action, data) \
	__drmm_add_action(dev, action, data, #action)

पूर्णांक __must_check __drmm_add_action(काष्ठा drm_device *dev,
				   drmres_release_t action,
				   व्योम *data, स्थिर अक्षर *name);

/**
 * drmm_add_action_or_reset - add a managed release action to a &drm_device
 * @dev: DRM device
 * @action: function which should be called when @dev is released
 * @data: opaque poपूर्णांकer, passed to @action
 *
 * Similar to drmm_add_action(), with the only dअगरference that upon failure
 * @action is directly called क्रम any cleanup work necessary on failures.
 */
#घोषणा drmm_add_action_or_reset(dev, action, data) \
	__drmm_add_action_or_reset(dev, action, data, #action)

पूर्णांक __must_check __drmm_add_action_or_reset(काष्ठा drm_device *dev,
					    drmres_release_t action,
					    व्योम *data, स्थिर अक्षर *name);

व्योम *drmm_kदो_स्मृति(काष्ठा drm_device *dev, माप_प्रकार size, gfp_t gfp) __दो_स्मृति;

/**
 * drmm_kzalloc - &drm_device managed kzalloc()
 * @dev: DRM device
 * @size: size of the memory allocation
 * @gfp: GFP allocation flags
 *
 * This is a &drm_device managed version of kzalloc(). The allocated memory is
 * स्वतःmatically मुक्तd on the final drm_dev_put(). Memory can also be मुक्तd
 * beक्रमe the final drm_dev_put() by calling drmm_kमुक्त().
 */
अटल अंतरभूत व्योम *drmm_kzalloc(काष्ठा drm_device *dev, माप_प्रकार size, gfp_t gfp)
अणु
	वापस drmm_kदो_स्मृति(dev, size, gfp | __GFP_ZERO);
पूर्ण

/**
 * drmm_kदो_स्मृति_array - &drm_device managed kदो_स्मृति_array()
 * @dev: DRM device
 * @n: number of array elements to allocate
 * @size: size of array member
 * @flags: GFP allocation flags
 *
 * This is a &drm_device managed version of kदो_स्मृति_array(). The allocated
 * memory is स्वतःmatically मुक्तd on the final drm_dev_put() and works exactly
 * like a memory allocation obtained by drmm_kदो_स्मृति().
 */
अटल अंतरभूत व्योम *drmm_kदो_स्मृति_array(काष्ठा drm_device *dev,
				       माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(n, size, &bytes)))
		वापस शून्य;

	वापस drmm_kदो_स्मृति(dev, bytes, flags);
पूर्ण

/**
 * drmm_kसुस्मृति - &drm_device managed kसुस्मृति()
 * @dev: DRM device
 * @n: number of array elements to allocate
 * @size: size of array member
 * @flags: GFP allocation flags
 *
 * This is a &drm_device managed version of kसुस्मृति(). The allocated memory is
 * स्वतःmatically मुक्तd on the final drm_dev_put() and works exactly like a
 * memory allocation obtained by drmm_kदो_स्मृति().
 */
अटल अंतरभूत व्योम *drmm_kसुस्मृति(काष्ठा drm_device *dev,
				 माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	वापस drmm_kदो_स्मृति_array(dev, n, size, flags | __GFP_ZERO);
पूर्ण

अक्षर *drmm_kstrdup(काष्ठा drm_device *dev, स्थिर अक्षर *s, gfp_t gfp);

व्योम drmm_kमुक्त(काष्ठा drm_device *dev, व्योम *data);

#पूर्ण_अगर
