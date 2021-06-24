<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __PSTORE_BLK_H_
#घोषणा __PSTORE_BLK_H_

#समावेश <linux/types.h>
#समावेश <linux/pstore.h>
#समावेश <linux/pstore_zone.h>

/**
 * काष्ठा pstore_device_info - back-end pstore/blk driver काष्ठाure.
 *
 * @total_size: The total size in bytes pstore/blk can use. It must be greater
 *		than 4096 and be multiple of 4096.
 * @flags:	Refer to macro starting with PSTORE_FLAGS defined in
 *		linux/pstore.h. It means what front-ends this device support.
 *		Zero means all backends क्रम compatible.
 * @पढ़ो:	The general पढ़ो operation. Both of the function parameters
 *		@size and @offset are relative value to bock device (not the
 *		whole disk).
 *		On success, the number of bytes should be वापसed, others
 *		means error.
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
काष्ठा pstore_device_info अणु
	अचिन्हित दीर्घ total_size;
	अचिन्हित पूर्णांक flags;
	pstore_zone_पढ़ो_op पढ़ो;
	pstore_zone_ग_लिखो_op ग_लिखो;
	pstore_zone_erase_op erase;
	pstore_zone_ग_लिखो_op panic_ग_लिखो;
पूर्ण;

पूर्णांक  रेजिस्टर_pstore_device(काष्ठा pstore_device_info *dev);
व्योम unरेजिस्टर_pstore_device(काष्ठा pstore_device_info *dev);

/**
 * काष्ठा pstore_blk_config - the pstore_blk backend configuration
 *
 * @device:		Name of the desired block device
 * @max_reason:		Maximum kmsg dump reason to store to block device
 * @kmsg_size:		Total size of क्रम kmsg dumps
 * @pmsg_size:		Total size of the pmsg storage area
 * @console_size:	Total size of the console storage area
 * @ftrace_size:	Total size क्रम ftrace logging data (क्रम all CPUs)
 */
काष्ठा pstore_blk_config अणु
	अक्षर device[80];
	क्रमागत kmsg_dump_reason max_reason;
	अचिन्हित दीर्घ kmsg_size;
	अचिन्हित दीर्घ pmsg_size;
	अचिन्हित दीर्घ console_size;
	अचिन्हित दीर्घ ftrace_size;
पूर्ण;

/**
 * pstore_blk_get_config - get a copy of the pstore_blk backend configuration
 *
 * @info:	The sturct pstore_blk_config to be filled in
 *
 * Failure वापसs negative error code, and success वापसs 0.
 */
पूर्णांक pstore_blk_get_config(काष्ठा pstore_blk_config *info);

#पूर्ण_अगर
