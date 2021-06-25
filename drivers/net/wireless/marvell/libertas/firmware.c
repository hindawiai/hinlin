<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Firmware loading and handling functions.
 */

#समावेश <linux/sched.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश "dev.h"
#समावेश "decl.h"

अटल व्योम load_next_firmware_from_table(काष्ठा lbs_निजी *निजी);

अटल व्योम lbs_fw_loaded(काष्ठा lbs_निजी *priv, पूर्णांक ret,
	स्थिर काष्ठा firmware *helper, स्थिर काष्ठा firmware *मुख्यfw)
अणु
	अचिन्हित दीर्घ flags;

	lbs_deb_fw("firmware load complete, code %d\n", ret);

	/* User must मुक्त helper/मुख्यfw */
	priv->fw_callback(priv, ret, helper, मुख्यfw);

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->fw_callback = शून्य;
	wake_up(&priv->fw_रुकोq);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण

अटल व्योम करो_load_firmware(काष्ठा lbs_निजी *priv, स्थिर अक्षर *name,
	व्योम (*cb)(स्थिर काष्ठा firmware *fw, व्योम *context))
अणु
	पूर्णांक ret;

	lbs_deb_fw("Requesting %s\n", name);
	ret = request_firmware_noरुको(THIS_MODULE, true, name,
			priv->fw_device, GFP_KERNEL, priv, cb);
	अगर (ret) अणु
		lbs_deb_fw("request_firmware_nowait error %d\n", ret);
		lbs_fw_loaded(priv, ret, शून्य, शून्य);
	पूर्ण
पूर्ण

अटल व्योम मुख्य_firmware_cb(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	काष्ठा lbs_निजी *priv = context;

	अगर (!firmware) अणु
		/* Failed to find firmware: try next table entry */
		load_next_firmware_from_table(priv);
		वापस;
	पूर्ण

	/* Firmware found! */
	lbs_fw_loaded(priv, 0, priv->helper_fw, firmware);
	अगर (priv->helper_fw) अणु
		release_firmware (priv->helper_fw);
		priv->helper_fw = शून्य;
	पूर्ण
	release_firmware (firmware);
पूर्ण

अटल व्योम helper_firmware_cb(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	काष्ठा lbs_निजी *priv = context;

	अगर (!firmware) अणु
		/* Failed to find firmware: try next table entry */
		load_next_firmware_from_table(priv);
		वापस;
	पूर्ण

	/* Firmware found! */
	अगर (priv->fw_iter->fwname) अणु
		priv->helper_fw = firmware;
		करो_load_firmware(priv, priv->fw_iter->fwname, मुख्य_firmware_cb);
	पूर्ण अन्यथा अणु
		/* No मुख्य firmware needed क्रम this helper --> success! */
		lbs_fw_loaded(priv, 0, firmware, शून्य);
	पूर्ण
पूर्ण

अटल व्योम load_next_firmware_from_table(काष्ठा lbs_निजी *priv)
अणु
	स्थिर काष्ठा lbs_fw_table *iter;

	अगर (!priv->fw_iter)
		iter = priv->fw_table;
	अन्यथा
		iter = ++priv->fw_iter;

	अगर (priv->helper_fw) अणु
		release_firmware(priv->helper_fw);
		priv->helper_fw = शून्य;
	पूर्ण

next:
	अगर (!iter->helper) अणु
		/* End of table hit. */
		lbs_fw_loaded(priv, -ENOENT, शून्य, शून्य);
		वापस;
	पूर्ण

	अगर (iter->model != priv->fw_model) अणु
		iter++;
		जाओ next;
	पूर्ण

	priv->fw_iter = iter;
	करो_load_firmware(priv, iter->helper, helper_firmware_cb);
पूर्ण

व्योम lbs_रुको_क्रम_firmware_load(काष्ठा lbs_निजी *priv)
अणु
	रुको_event(priv->fw_रुकोq, priv->fw_callback == शून्य);
पूर्ण

/**
 *  lbs_get_firmware_async - Retrieves firmware asynchronously. Can load
 *  either a helper firmware and a मुख्य firmware (2-stage), or just the helper.
 *
 *  @priv:      Poपूर्णांकer to lbs_निजी instance
 *  @device:   	A poपूर्णांकer to &device काष्ठाure
 *  @card_model: Bus-specअगरic card model ID used to filter firmware table
 *		elements
 *  @fw_table:	Table of firmware file names and device model numbers
 *		terminated by an entry with a शून्य helper name
 *  @callback:	User callback to invoke when firmware load succeeds or fails.
 */
पूर्णांक lbs_get_firmware_async(काष्ठा lbs_निजी *priv, काष्ठा device *device,
			    u32 card_model, स्थिर काष्ठा lbs_fw_table *fw_table,
			    lbs_fw_cb callback)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->driver_lock, flags);
	अगर (priv->fw_callback) अणु
		lbs_deb_fw("firmware load already in progress\n");
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		वापस -EBUSY;
	पूर्ण

	priv->fw_device = device;
	priv->fw_callback = callback;
	priv->fw_table = fw_table;
	priv->fw_iter = शून्य;
	priv->fw_model = card_model;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbs_deb_fw("Starting async firmware load\n");
	load_next_firmware_from_table(priv);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lbs_get_firmware_async);

/**
 *  lbs_get_firmware - Retrieves two-stage firmware
 *
 *  @dev:     	A poपूर्णांकer to &device काष्ठाure
 *  @card_model: Bus-specअगरic card model ID used to filter firmware table
 *		elements
 *  @fw_table:	Table of firmware file names and device model numbers
 *		terminated by an entry with a शून्य helper name
 *  @helper:	On success, the helper firmware; caller must मुक्त
 *  @मुख्यfw:	On success, the मुख्य firmware; caller must मुक्त
 *
 * Deprecated: use lbs_get_firmware_async() instead.
 *
 *  वापसs:		0 on success, non-zero on failure
 */
पूर्णांक lbs_get_firmware(काष्ठा device *dev, u32 card_model,
			स्थिर काष्ठा lbs_fw_table *fw_table,
			स्थिर काष्ठा firmware **helper,
			स्थिर काष्ठा firmware **मुख्यfw)
अणु
	स्थिर काष्ठा lbs_fw_table *iter;
	पूर्णांक ret;

	BUG_ON(helper == शून्य);
	BUG_ON(मुख्यfw == शून्य);

	/* Search क्रम firmware to use from the table. */
	iter = fw_table;
	जबतक (iter && iter->helper) अणु
		अगर (iter->model != card_model)
			जाओ next;

		अगर (*helper == शून्य) अणु
			ret = request_firmware(helper, iter->helper, dev);
			अगर (ret)
				जाओ next;

			/* If the device has one-stage firmware (ie cf8305) and
			 * we've got it then we don't need to bother with the
			 * मुख्य firmware.
			 */
			अगर (iter->fwname == शून्य)
				वापस 0;
		पूर्ण

		अगर (*मुख्यfw == शून्य) अणु
			ret = request_firmware(मुख्यfw, iter->fwname, dev);
			अगर (ret) अणु
				/* Clear the helper to ensure we करोn't have
				 * mismatched firmware pairs.
				 */
				release_firmware(*helper);
				*helper = शून्य;
			पूर्ण
		पूर्ण

		अगर (*helper && *मुख्यfw)
			वापस 0;

  next:
		iter++;
	पूर्ण

	/* Failed */
	release_firmware(*helper);
	*helper = शून्य;
	release_firmware(*मुख्यfw);
	*मुख्यfw = शून्य;

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(lbs_get_firmware);
