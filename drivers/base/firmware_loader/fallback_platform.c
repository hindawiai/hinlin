<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/efi_embedded_fw.h>
#समावेश <linux/property.h>
#समावेश <linux/security.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "fallback.h"
#समावेश "firmware.h"

पूर्णांक firmware_fallback_platक्रमm(काष्ठा fw_priv *fw_priv)
अणु
	स्थिर u8 *data;
	माप_प्रकार size;
	पूर्णांक rc;

	अगर (!(fw_priv->opt_flags & FW_OPT_FALLBACK_PLATFORM))
		वापस -ENOENT;

	rc = security_kernel_load_data(LOADING_FIRMWARE, true);
	अगर (rc)
		वापस rc;

	rc = efi_get_embedded_fw(fw_priv->fw_name, &data, &size);
	अगर (rc)
		वापस rc; /* rc == -ENOENT when the fw was not found */

	अगर (fw_priv->data && size > fw_priv->allocated_size)
		वापस -ENOMEM;

	rc = security_kernel_post_load_data((u8 *)data, size, LOADING_FIRMWARE,
						"platform");
	अगर (rc)
		वापस rc;

	अगर (!fw_priv->data)
		fw_priv->data = vदो_स्मृति(size);
	अगर (!fw_priv->data)
		वापस -ENOMEM;

	स_नकल(fw_priv->data, data, size);
	fw_priv->size = size;
	fw_state_करोne(fw_priv);
	वापस 0;
पूर्ण
