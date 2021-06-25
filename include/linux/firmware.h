<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FIRMWARE_H
#घोषणा _LINUX_FIRMWARE_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/gfp.h>

#घोषणा FW_ACTION_NOHOTPLUG 0
#घोषणा FW_ACTION_HOTPLUG 1

काष्ठा firmware अणु
	माप_प्रकार size;
	स्थिर u8 *data;

	/* firmware loader निजी fields */
	व्योम *priv;
पूर्ण;

काष्ठा module;
काष्ठा device;

काष्ठा builtin_fw अणु
	अक्षर *name;
	व्योम *data;
	अचिन्हित दीर्घ size;
पूर्ण;

/* We have to play tricks here much like stringअगरy() to get the
   __COUNTER__ macro to be expanded as we want it */
#घोषणा __fw_concat1(x, y) x##y
#घोषणा __fw_concat(x, y) __fw_concat1(x, y)

#घोषणा DECLARE_BUILTIN_FIRMWARE(name, blob)				     \
	DECLARE_BUILTIN_FIRMWARE_SIZE(name, &(blob), माप(blob))

#घोषणा DECLARE_BUILTIN_FIRMWARE_SIZE(name, blob, size)			     \
	अटल स्थिर काष्ठा builtin_fw __fw_concat(__builtin_fw,__COUNTER__) \
	__used __section(".builtin_fw") = अणु name, blob, size पूर्ण

#अगर defined(CONFIG_FW_LOADER) || (defined(CONFIG_FW_LOADER_MODULE) && defined(MODULE))
पूर्णांक request_firmware(स्थिर काष्ठा firmware **fw, स्थिर अक्षर *name,
		     काष्ठा device *device);
पूर्णांक firmware_request_nowarn(स्थिर काष्ठा firmware **fw, स्थिर अक्षर *name,
			    काष्ठा device *device);
पूर्णांक firmware_request_platक्रमm(स्थिर काष्ठा firmware **fw, स्थिर अक्षर *name,
			      काष्ठा device *device);
पूर्णांक request_firmware_noरुको(
	काष्ठा module *module, bool uevent,
	स्थिर अक्षर *name, काष्ठा device *device, gfp_t gfp, व्योम *context,
	व्योम (*cont)(स्थिर काष्ठा firmware *fw, व्योम *context));
पूर्णांक request_firmware_direct(स्थिर काष्ठा firmware **fw, स्थिर अक्षर *name,
			    काष्ठा device *device);
पूर्णांक request_firmware_पूर्णांकo_buf(स्थिर काष्ठा firmware **firmware_p,
	स्थिर अक्षर *name, काष्ठा device *device, व्योम *buf, माप_प्रकार size);
पूर्णांक request_partial_firmware_पूर्णांकo_buf(स्थिर काष्ठा firmware **firmware_p,
				      स्थिर अक्षर *name, काष्ठा device *device,
				      व्योम *buf, माप_प्रकार size, माप_प्रकार offset);

व्योम release_firmware(स्थिर काष्ठा firmware *fw);
#अन्यथा
अटल अंतरभूत पूर्णांक request_firmware(स्थिर काष्ठा firmware **fw,
				   स्थिर अक्षर *name,
				   काष्ठा device *device)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक firmware_request_nowarn(स्थिर काष्ठा firmware **fw,
					  स्थिर अक्षर *name,
					  काष्ठा device *device)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक firmware_request_platक्रमm(स्थिर काष्ठा firmware **fw,
					    स्थिर अक्षर *name,
					    काष्ठा device *device)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक request_firmware_noरुको(
	काष्ठा module *module, bool uevent,
	स्थिर अक्षर *name, काष्ठा device *device, gfp_t gfp, व्योम *context,
	व्योम (*cont)(स्थिर काष्ठा firmware *fw, व्योम *context))
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम release_firmware(स्थिर काष्ठा firmware *fw)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक request_firmware_direct(स्थिर काष्ठा firmware **fw,
					  स्थिर अक्षर *name,
					  काष्ठा device *device)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक request_firmware_पूर्णांकo_buf(स्थिर काष्ठा firmware **firmware_p,
	स्थिर अक्षर *name, काष्ठा device *device, व्योम *buf, माप_प्रकार size)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक request_partial_firmware_पूर्णांकo_buf
					(स्थिर काष्ठा firmware **firmware_p,
					 स्थिर अक्षर *name,
					 काष्ठा device *device,
					 व्योम *buf, माप_प्रकार size, माप_प्रकार offset)
अणु
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर

पूर्णांक firmware_request_cache(काष्ठा device *device, स्थिर अक्षर *name);

#पूर्ण_अगर
