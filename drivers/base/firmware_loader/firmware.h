<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __FIRMWARE_LOADER_H
#घोषणा __FIRMWARE_LOADER_H

#समावेश <linux/bitops.h>
#समावेश <linux/firmware.h>
#समावेश <linux/types.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/completion.h>

#समावेश <generated/utsrelease.h>

/**
 * क्रमागत fw_opt - options to control firmware loading behaviour
 *
 * @FW_OPT_UEVENT: Enables the fallback mechanism to send a kobject uevent
 *	when the firmware is not found. Userspace is in अक्षरge to load the
 *	firmware using the sysfs loading facility.
 * @FW_OPT_NOWAIT: Used to describe the firmware request is asynchronous.
 * @FW_OPT_USERHELPER: Enable the fallback mechanism, in हाल the direct
 *	fileप्रणाली lookup fails at finding the firmware.  For details refer to
 *	firmware_fallback_sysfs().
 * @FW_OPT_NO_WARN: Quiet, aव्योम prपूर्णांकing warning messages.
 * @FW_OPT_NOCACHE: Disables firmware caching. Firmware caching is used to
 *	cache the firmware upon suspend, so that upon resume races against the
 *	firmware file lookup on storage is aव्योमed. Used क्रम calls where the
 *	file may be too big, or where the driver takes अक्षरge of its own
 *	firmware caching mechanism.
 * @FW_OPT_NOFALLBACK_SYSFS: Disable the sysfs fallback mechanism. Takes
 *	precedence over &FW_OPT_UEVENT and &FW_OPT_USERHELPER.
 * @FW_OPT_FALLBACK_PLATFORM: Enable fallback to device fw copy embedded in
 *	the platक्रमm's मुख्य firmware. If both this fallback and the sysfs
 *      fallback are enabled, then this fallback will be tried first.
 * @FW_OPT_PARTIAL: Allow partial पढ़ो of firmware instead of needing to पढ़ो
 *	entire file.
 */
क्रमागत fw_opt अणु
	FW_OPT_UEVENT			= BIT(0),
	FW_OPT_NOWAIT			= BIT(1),
	FW_OPT_USERHELPER		= BIT(2),
	FW_OPT_NO_WARN			= BIT(3),
	FW_OPT_NOCACHE			= BIT(4),
	FW_OPT_NOFALLBACK_SYSFS		= BIT(5),
	FW_OPT_FALLBACK_PLATFORM	= BIT(6),
	FW_OPT_PARTIAL			= BIT(7),
पूर्ण;

क्रमागत fw_status अणु
	FW_STATUS_UNKNOWN,
	FW_STATUS_LOADING,
	FW_STATUS_DONE,
	FW_STATUS_ABORTED,
पूर्ण;

/*
 * Concurrent request_firmware() क्रम the same firmware need to be
 * serialized.  काष्ठा fw_state is simple state machine which hold the
 * state of the firmware loading.
 */
काष्ठा fw_state अणु
	काष्ठा completion completion;
	क्रमागत fw_status status;
पूर्ण;

काष्ठा fw_priv अणु
	काष्ठा kref ref;
	काष्ठा list_head list;
	काष्ठा firmware_cache *fwc;
	काष्ठा fw_state fw_st;
	व्योम *data;
	माप_प्रकार size;
	माप_प्रकार allocated_size;
	माप_प्रकार offset;
	u32 opt_flags;
#अगर_घोषित CONFIG_FW_LOADER_PAGED_BUF
	bool is_paged_buf;
	काष्ठा page **pages;
	पूर्णांक nr_pages;
	पूर्णांक page_array_size;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FW_LOADER_USER_HELPER
	bool need_uevent;
	काष्ठा list_head pending_list;
#पूर्ण_अगर
	स्थिर अक्षर *fw_name;
पूर्ण;

बाह्य काष्ठा mutex fw_lock;

अटल अंतरभूत bool __fw_state_check(काष्ठा fw_priv *fw_priv,
				    क्रमागत fw_status status)
अणु
	काष्ठा fw_state *fw_st = &fw_priv->fw_st;

	वापस fw_st->status == status;
पूर्ण

अटल अंतरभूत पूर्णांक __fw_state_रुको_common(काष्ठा fw_priv *fw_priv, दीर्घ समयout)
अणु
	काष्ठा fw_state *fw_st = &fw_priv->fw_st;
	दीर्घ ret;

	ret = रुको_क्रम_completion_समाप्तable_समयout(&fw_st->completion, समयout);
	अगर (ret != 0 && fw_st->status == FW_STATUS_ABORTED)
		वापस -ENOENT;
	अगर (!ret)
		वापस -ETIMEDOUT;

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल अंतरभूत व्योम __fw_state_set(काष्ठा fw_priv *fw_priv,
				  क्रमागत fw_status status)
अणु
	काष्ठा fw_state *fw_st = &fw_priv->fw_st;

	WRITE_ONCE(fw_st->status, status);

	अगर (status == FW_STATUS_DONE || status == FW_STATUS_ABORTED)
		complete_all(&fw_st->completion);
पूर्ण

अटल अंतरभूत व्योम fw_state_पातed(काष्ठा fw_priv *fw_priv)
अणु
	__fw_state_set(fw_priv, FW_STATUS_ABORTED);
पूर्ण

अटल अंतरभूत bool fw_state_is_पातed(काष्ठा fw_priv *fw_priv)
अणु
	वापस __fw_state_check(fw_priv, FW_STATUS_ABORTED);
पूर्ण

अटल अंतरभूत व्योम fw_state_start(काष्ठा fw_priv *fw_priv)
अणु
	__fw_state_set(fw_priv, FW_STATUS_LOADING);
पूर्ण

अटल अंतरभूत व्योम fw_state_करोne(काष्ठा fw_priv *fw_priv)
अणु
	__fw_state_set(fw_priv, FW_STATUS_DONE);
पूर्ण

पूर्णांक assign_fw(काष्ठा firmware *fw, काष्ठा device *device);

#अगर_घोषित CONFIG_FW_LOADER_PAGED_BUF
व्योम fw_मुक्त_paged_buf(काष्ठा fw_priv *fw_priv);
पूर्णांक fw_grow_paged_buf(काष्ठा fw_priv *fw_priv, पूर्णांक pages_needed);
पूर्णांक fw_map_paged_buf(काष्ठा fw_priv *fw_priv);
bool fw_is_paged_buf(काष्ठा fw_priv *fw_priv);
#अन्यथा
अटल अंतरभूत व्योम fw_मुक्त_paged_buf(काष्ठा fw_priv *fw_priv) अणुपूर्ण
अटल अंतरभूत पूर्णांक fw_grow_paged_buf(काष्ठा fw_priv *fw_priv, पूर्णांक pages_needed) अणु वापस -ENXIO; पूर्ण
अटल अंतरभूत पूर्णांक fw_map_paged_buf(काष्ठा fw_priv *fw_priv) अणु वापस -ENXIO; पूर्ण
अटल अंतरभूत bool fw_is_paged_buf(काष्ठा fw_priv *fw_priv) अणु वापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __FIRMWARE_LOADER_H */
