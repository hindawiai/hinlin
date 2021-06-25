<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __FIRMWARE_FALLBACK_H
#घोषणा __FIRMWARE_FALLBACK_H

#समावेश <linux/firmware.h>
#समावेश <linux/device.h>

#समावेश "firmware.h"

/**
 * काष्ठा firmware_fallback_config - firmware fallback configuration settings
 *
 * Helps describe and fine tune the fallback mechanism.
 *
 * @क्रमce_sysfs_fallback: क्रमce the sysfs fallback mechanism to be used
 * 	as अगर one had enabled CONFIG_FW_LOADER_USER_HELPER_FALLBACK=y.
 * 	Useful to help debug a CONFIG_FW_LOADER_USER_HELPER_FALLBACK=y
 * 	functionality on a kernel where that config entry has been disabled.
 * @ignore_sysfs_fallback: क्रमce to disable the sysfs fallback mechanism.
 * 	This emulates the behaviour as अगर we had set the kernel
 * 	config CONFIG_FW_LOADER_USER_HELPER=n.
 * @old_समयout: क्रम पूर्णांकernal use
 * @loading_समयout: the समयout to रुको क्रम the fallback mechanism beक्रमe
 * 	giving up, in seconds.
 */
काष्ठा firmware_fallback_config अणु
	अचिन्हित पूर्णांक क्रमce_sysfs_fallback;
	अचिन्हित पूर्णांक ignore_sysfs_fallback;
	पूर्णांक old_समयout;
	पूर्णांक loading_समयout;
पूर्ण;

#अगर_घोषित CONFIG_FW_LOADER_USER_HELPER
पूर्णांक firmware_fallback_sysfs(काष्ठा firmware *fw, स्थिर अक्षर *name,
			    काष्ठा device *device,
			    u32 opt_flags,
			    पूर्णांक ret);
व्योम समाप्त_pending_fw_fallback_reqs(bool only_समाप्त_custom);

व्योम fw_fallback_set_cache_समयout(व्योम);
व्योम fw_fallback_set_शेष_समयout(व्योम);

पूर्णांक रेजिस्टर_sysfs_loader(व्योम);
व्योम unरेजिस्टर_sysfs_loader(व्योम);
#अन्यथा /* CONFIG_FW_LOADER_USER_HELPER */
अटल अंतरभूत पूर्णांक firmware_fallback_sysfs(काष्ठा firmware *fw, स्थिर अक्षर *name,
					  काष्ठा device *device,
					  u32 opt_flags,
					  पूर्णांक ret)
अणु
	/* Keep carrying over the same error */
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम समाप्त_pending_fw_fallback_reqs(bool only_समाप्त_custom) अणु पूर्ण
अटल अंतरभूत व्योम fw_fallback_set_cache_समयout(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम fw_fallback_set_शेष_समयout(व्योम) अणु पूर्ण

अटल अंतरभूत पूर्णांक रेजिस्टर_sysfs_loader(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_sysfs_loader(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FW_LOADER_USER_HELPER */

#अगर_घोषित CONFIG_EFI_EMBEDDED_FIRMWARE
पूर्णांक firmware_fallback_platक्रमm(काष्ठा fw_priv *fw_priv);
#अन्यथा
अटल अंतरभूत पूर्णांक firmware_fallback_platक्रमm(काष्ठा fw_priv *fw_priv)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __FIRMWARE_FALLBACK_H */
