<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _INDUSTRIAL_IO_OPAQUE_H_
#घोषणा _INDUSTRIAL_IO_OPAQUE_H_

/**
 * काष्ठा iio_dev_opaque - industrial I/O device opaque inक्रमmation
 * @indio_dev:			खुला industrial I/O device inक्रमmation
 * @event_पूर्णांकerface:		event chrdevs associated with पूर्णांकerrupt lines
 * @attached_buffers:		array of buffers अटलally attached by the driver
 * @attached_buffers_cnt:	number of buffers in the array of अटलally attached buffers
 * @buffer_ioctl_handler:	ioctl() handler क्रम this IIO device's buffer पूर्णांकerface
 * @buffer_list:		list of all buffers currently attached
 * @channel_attr_list:		keep track of स्वतःmatically created channel
 *				attributes
 * @chan_attr_group:		group क्रम all attrs in base directory
 * @ioctl_handlers:		ioctl handlers रेजिस्टरed with the core handler
 * @groups:			attribute groups
 * @groupcounter:		index of next attribute group
 * @legacy_scan_el_group:	attribute group क्रम legacy scan elements attribute group
 * @legacy_buffer_group:	attribute group क्रम legacy buffer attributes group
 * @debugfs_dentry:		device specअगरic debugfs dentry
 * @cached_reg_addr:		cached रेजिस्टर address क्रम debugfs पढ़ोs
 * @पढ़ो_buf:			पढ़ो buffer to be used क्रम the initial reg पढ़ो
 * @पढ़ो_buf_len:		data length in @पढ़ो_buf
 */
काष्ठा iio_dev_opaque अणु
	काष्ठा iio_dev			indio_dev;
	काष्ठा iio_event_पूर्णांकerface	*event_पूर्णांकerface;
	काष्ठा iio_buffer		**attached_buffers;
	अचिन्हित पूर्णांक			attached_buffers_cnt;
	काष्ठा iio_ioctl_handler	*buffer_ioctl_handler;
	काष्ठा list_head		buffer_list;
	काष्ठा list_head		channel_attr_list;
	काष्ठा attribute_group		chan_attr_group;
	काष्ठा list_head		ioctl_handlers;
	स्थिर काष्ठा attribute_group	**groups;
	पूर्णांक				groupcounter;
	काष्ठा attribute_group		legacy_scan_el_group;
	काष्ठा attribute_group		legacy_buffer_group;
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry			*debugfs_dentry;
	अचिन्हित			cached_reg_addr;
	अक्षर				पढ़ो_buf[20];
	अचिन्हित पूर्णांक			पढ़ो_buf_len;
#पूर्ण_अगर
पूर्ण;

#घोषणा to_iio_dev_opaque(indio_dev)		\
	container_of(indio_dev, काष्ठा iio_dev_opaque, indio_dev)

#पूर्ण_अगर
