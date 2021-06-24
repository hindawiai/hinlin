<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IIO_BUFFER_GENERIC_IMPL_H_
#घोषणा _IIO_BUFFER_GENERIC_IMPL_H_
#समावेश <linux/sysfs.h>
#समावेश <linux/kref.h>

#अगर_घोषित CONFIG_IIO_BUFFER

#समावेश <uapi/linux/iio/buffer.h>

काष्ठा iio_dev;
काष्ठा iio_buffer;

/**
 * INDIO_BUFFER_FLAG_FIXED_WATERMARK - Watermark level of the buffer can not be
 *   configured. It has a fixed value which will be buffer specअगरic.
 */
#घोषणा INDIO_BUFFER_FLAG_FIXED_WATERMARK BIT(0)

/**
 * काष्ठा iio_buffer_access_funcs - access functions क्रम buffers.
 * @store_to:		actually store stuff to the buffer
 * @पढ़ो:		try to get a specअगरied number of bytes (must exist)
 * @data_available:	indicates how much data is available क्रम पढ़ोing from
 *			the buffer.
 * @request_update:	अगर a parameter change has been marked, update underlying
 *			storage.
 * @set_bytes_per_datum:set number of bytes per datum
 * @set_length:		set number of datums in buffer
 * @enable:             called अगर the buffer is attached to a device and the
 *                      device starts sampling. Calls are balanced with
 *                      @disable.
 * @disable:            called अगर the buffer is attached to a device and the
 *                      device stops sampling. Calles are balanced with @enable.
 * @release:		called when the last reference to the buffer is dropped,
 *			should मुक्त all resources allocated by the buffer.
 * @modes:		Supported operating modes by this buffer type
 * @flags:		A biपंचांगask combination of INDIO_BUFFER_FLAG_*
 *
 * The purpose of this काष्ठाure is to make the buffer element
 * modular as event क्रम a given driver, dअगरferent useहालs may require
 * dअगरferent buffer designs (space efficiency vs speed क्रम example).
 *
 * It is worth noting that a given buffer implementation may only support a
 * small proportion of these functions.  The core code 'should' cope fine with
 * any of them not existing.
 **/
काष्ठा iio_buffer_access_funcs अणु
	पूर्णांक (*store_to)(काष्ठा iio_buffer *buffer, स्थिर व्योम *data);
	पूर्णांक (*पढ़ो)(काष्ठा iio_buffer *buffer, माप_प्रकार n, अक्षर __user *buf);
	माप_प्रकार (*data_available)(काष्ठा iio_buffer *buffer);

	पूर्णांक (*request_update)(काष्ठा iio_buffer *buffer);

	पूर्णांक (*set_bytes_per_datum)(काष्ठा iio_buffer *buffer, माप_प्रकार bpd);
	पूर्णांक (*set_length)(काष्ठा iio_buffer *buffer, अचिन्हित पूर्णांक length);

	पूर्णांक (*enable)(काष्ठा iio_buffer *buffer, काष्ठा iio_dev *indio_dev);
	पूर्णांक (*disable)(काष्ठा iio_buffer *buffer, काष्ठा iio_dev *indio_dev);

	व्योम (*release)(काष्ठा iio_buffer *buffer);

	अचिन्हित पूर्णांक modes;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/**
 * काष्ठा iio_buffer - general buffer काष्ठाure
 *
 * Note that the पूर्णांकernals of this काष्ठाure should only be of पूर्णांकerest to
 * those writing new buffer implementations.
 */
काष्ठा iio_buffer अणु
	/** @length: Number of datums in buffer. */
	अचिन्हित पूर्णांक length;

	/** @flags: File ops flags including busy flag. */
	अचिन्हित दीर्घ flags;

	/**  @bytes_per_datum: Size of inभागidual datum including बारtamp. */
	माप_प्रकार bytes_per_datum;

	/**
	 * @access: Buffer access functions associated with the
	 * implementation.
	 */
	स्थिर काष्ठा iio_buffer_access_funcs *access;

	/** @scan_mask: Biपंचांगask used in masking scan mode elements. */
	दीर्घ *scan_mask;

	/** @demux_list: List of operations required to demux the scan. */
	काष्ठा list_head demux_list;

	/** @pollq: Wait queue to allow क्रम polling on the buffer. */
	रुको_queue_head_t pollq;

	/** @watermark: Number of datums to रुको क्रम poll/पढ़ो. */
	अचिन्हित पूर्णांक watermark;

	/* निजी: */
	/* @scan_बारtamp: Does the scan mode include a बारtamp. */
	bool scan_बारtamp;

	/* @buffer_attr_list: List of buffer attributes. */
	काष्ठा list_head buffer_attr_list;

	/*
	 * @buffer_group: Attributes of the new buffer group.
	 * Includes scan elements attributes.
	 */
	काष्ठा attribute_group buffer_group;

	/* @attrs: Standard attributes of the buffer. */
	स्थिर काष्ठा attribute **attrs;

	/* @demux_bounce: Buffer क्रम करोing gather from incoming scan. */
	व्योम *demux_bounce;

	/* @attached_entry: Entry in the devices list of buffers attached by the driver. */
	काष्ठा list_head attached_entry;

	/* @buffer_list: Entry in the devices list of current buffers. */
	काष्ठा list_head buffer_list;

	/* @ref: Reference count of the buffer. */
	काष्ठा kref ref;
पूर्ण;

/**
 * iio_update_buffers() - add or हटाओ buffer from active list
 * @indio_dev:		device to add buffer to
 * @insert_buffer:	buffer to insert
 * @हटाओ_buffer:	buffer_to_हटाओ
 *
 * Note this will tear करोwn the all buffering and build it up again
 */
पूर्णांक iio_update_buffers(काष्ठा iio_dev *indio_dev,
		       काष्ठा iio_buffer *insert_buffer,
		       काष्ठा iio_buffer *हटाओ_buffer);

/**
 * iio_buffer_init() - Initialize the buffer काष्ठाure
 * @buffer:		buffer to be initialized
 **/
व्योम iio_buffer_init(काष्ठा iio_buffer *buffer);

काष्ठा iio_buffer *iio_buffer_get(काष्ठा iio_buffer *buffer);
व्योम iio_buffer_put(काष्ठा iio_buffer *buffer);

#अन्यथा /* CONFIG_IIO_BUFFER */

अटल अंतरभूत व्योम iio_buffer_get(काष्ठा iio_buffer *buffer) अणुपूर्ण
अटल अंतरभूत व्योम iio_buffer_put(काष्ठा iio_buffer *buffer) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_IIO_BUFFER */
#पूर्ण_अगर /* _IIO_BUFFER_GENERIC_IMPL_H_ */
