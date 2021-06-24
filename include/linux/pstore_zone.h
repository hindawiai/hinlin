<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __PSTORE_ZONE_H_
#घोषणा __PSTORE_ZONE_H_

#समावेश <linux/types.h>

प्रकार sमाप_प्रकार (*pstore_zone_पढ़ो_op)(अक्षर *, माप_प्रकार, loff_t);
प्रकार sमाप_प्रकार (*pstore_zone_ग_लिखो_op)(स्थिर अक्षर *, माप_प्रकार, loff_t);
प्रकार sमाप_प्रकार (*pstore_zone_erase_op)(माप_प्रकार, loff_t);
/**
 * काष्ठा pstore_zone_info - pstore/zone back-end driver काष्ठाure
 *
 * @owner:	Module which is responsible क्रम this back-end driver.
 * @name:	Name of the back-end driver.
 * @total_size: The total size in bytes pstore/zone can use. It must be greater
 *		than 4096 and be multiple of 4096.
 * @kmsg_size:	The size of oops/panic zone. Zero means disabled, otherwise,
 *		it must be multiple of SECTOR_SIZE(512 Bytes).
 * @max_reason: Maximum kmsg dump reason to store.
 * @pmsg_size:	The size of pmsg zone which is the same as @kmsg_size.
 * @console_size:The size of console zone which is the same as @kmsg_size.
 * @ftrace_size:The size of ftrace zone which is the same as @kmsg_size.
 * @पढ़ो:	The general पढ़ो operation. Both of the function parameters
 *		@size and @offset are relative value to storage.
 *		On success, the number of bytes should be वापसed, others
 *		mean error.
 * @ग_लिखो:	The same as @पढ़ो, but the following error number:
 *		-EBUSY means try to ग_लिखो again later.
 *		-ENOMSG means to try next zone.
 * @erase:	The general erase operation क्रम device with special removing
 *		job. Both of the function parameters @size and @offset are
 *		relative value to storage.
 *		Return 0 on success and others on failure.
 * @panic_ग_लिखो:The ग_लिखो operation only used क्रम panic हाल. It's optional
 *		अगर you करो not care panic log. The parameters are relative
 *		value to storage.
 *		On success, the number of bytes should be वापसed, others
 *		excluding -ENOMSG mean error. -ENOMSG means to try next zone.
 */
काष्ठा pstore_zone_info अणु
	काष्ठा module *owner;
	स्थिर अक्षर *name;

	अचिन्हित दीर्घ total_size;
	अचिन्हित दीर्घ kmsg_size;
	पूर्णांक max_reason;
	अचिन्हित दीर्घ pmsg_size;
	अचिन्हित दीर्घ console_size;
	अचिन्हित दीर्घ ftrace_size;
	pstore_zone_पढ़ो_op पढ़ो;
	pstore_zone_ग_लिखो_op ग_लिखो;
	pstore_zone_erase_op erase;
	pstore_zone_ग_लिखो_op panic_ग_लिखो;
पूर्ण;

बाह्य पूर्णांक रेजिस्टर_pstore_zone(काष्ठा pstore_zone_info *info);
बाह्य व्योम unरेजिस्टर_pstore_zone(काष्ठा pstore_zone_info *info);

#पूर्ण_अगर
