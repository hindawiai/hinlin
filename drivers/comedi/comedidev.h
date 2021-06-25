<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * comedidev.h
 * header file क्रम kernel-only काष्ठाures, variables, and स्थिरants
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _COMEDIDEV_H
#घोषणा _COMEDIDEV_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/kref.h>

#समावेश "comedi.h"

#घोषणा COMEDI_VERSION(a, b, c) (((a) << 16) + ((b) << 8) + (c))
#घोषणा COMEDI_VERSION_CODE COMEDI_VERSION(COMEDI_MAJORVERSION, \
	COMEDI_MINORVERSION, COMEDI_MICROVERSION)
#घोषणा COMEDI_RELEASE VERSION

#घोषणा COMEDI_NUM_BOARD_MINORS 0x30

/**
 * काष्ठा comedi_subdevice - Working data क्रम a COMEDI subdevice
 * @device: COMEDI device to which this subdevice beदीर्घs.  (Initialized by
 *	comedi_alloc_subdevices().)
 * @index: Index of this subdevice within device's array of subdevices.
 *	(Initialized by comedi_alloc_subdevices().)
 * @type: Type of subdevice from &क्रमागत comedi_subdevice_type.  (Initialized by
 *	the low-level driver.)
 * @n_chan: Number of channels the subdevice supports.  (Initialized by the
 *	low-level driver.)
 * @subdev_flags: Various "SDF" flags indicating aspects of the subdevice to
 *	the COMEDI core and user application.  (Initialized by the low-level
 *	driver.)
 * @len_chanlist: Maximum length of a channel list अगर the subdevice supports
 *	asynchronous acquisition commands.  (Optionally initialized by the
 *	low-level driver, or changed from 0 to 1 during post-configuration.)
 * @निजी: Private data poपूर्णांकer which is either set by the low-level driver
 *	itself, or by a call to comedi_alloc_spriv() which allocates storage.
 *	In the latter हाल, the storage is स्वतःmatically मुक्तd after the
 *	low-level driver's "detach" handler is called क्रम the device.
 *	(Initialized by the low-level driver.)
 * @async: Poपूर्णांकer to &काष्ठा comedi_async id the subdevice supports
 *	asynchronous acquisition commands.  (Allocated and initialized during
 *	post-configuration अगर needed.)
 * @lock: Poपूर्णांकer to a file object that perक्रमmed a %COMEDI_LOCK ioctl on the
 *	subdevice.  (Initially शून्य.)
 * @busy: Poपूर्णांकer to a file object that is perक्रमming an asynchronous
 *	acquisition command on the subdevice.  (Initially शून्य.)
 * @runflags: Internal flags क्रम use by COMEDI core, mostly indicating whether
 *	an asynchronous acquisition command is running.
 * @spin_lock: Generic spin-lock क्रम use by the COMEDI core and the low-level
 *	driver.  (Initialized by comedi_alloc_subdevices().)
 * @io_bits: Bit-mask indicating the channel directions क्रम a DIO subdevice
 *	with no more than 32 channels.  A '1' at a bit position indicates the
 *	corresponding channel is configured as an output.  (Initialized by the
 *	low-level driver क्रम a DIO subdevice.  Forced to all-outमाला_दो during
 *	post-configuration क्रम a digital output subdevice.)
 * @maxdata: If non-zero, this is the maximum raw data value of each channel.
 *	If zero, the maximum data value is channel-specअगरic.  (Initialized by
 *	the low-level driver.)
 * @maxdata_list: If the maximum data value is channel-specअगरic, this poपूर्णांकs
 *	to an array of maximum data values indexed by channel index.
 *	(Initialized by the low-level driver.)
 * @range_table: If non-शून्य, this poपूर्णांकs to a COMEDI range table क्रम the
 *	subdevice.  If शून्य, the range table is channel-specअगरic.  (Initialized
 *	by the low-level driver, will be set to an "invalid" range table during
 *	post-configuration अगर @range_table and @range_table_list are both
 *	शून्य.)
 * @range_table_list: If the COMEDI range table is channel-specअगरic, this
 *	poपूर्णांकs to an array of poपूर्णांकers to COMEDI range tables indexed by
 *	channel number.  (Initialized by the low-level driver.)
 * @chanlist: Not used.
 * @insn_पढ़ो: Optional poपूर्णांकer to a handler क्रम the %INSN_READ inकाष्ठाion.
 *	(Initialized by the low-level driver, or set to a शेष handler
 *	during post-configuration.)
 * @insn_ग_लिखो: Optional poपूर्णांकer to a handler क्रम the %INSN_WRITE inकाष्ठाion.
 *	(Initialized by the low-level driver, or set to a शेष handler
 *	during post-configuration.)
 * @insn_bits: Optional poपूर्णांकer to a handler क्रम the %INSN_BITS inकाष्ठाion
 *	क्रम a digital input, digital output or digital input/output subdevice.
 *	(Initialized by the low-level driver, or set to a शेष handler
 *	during post-configuration.)
 * @insn_config: Optional poपूर्णांकer to a handler क्रम the %INSN_CONFIG
 *	inकाष्ठाion.  (Initialized by the low-level driver, or set to a शेष
 *	handler during post-configuration.)
 * @करो_cmd: If the subdevice supports asynchronous acquisition commands, this
 *	poपूर्णांकs to a handler to set it up in hardware.  (Initialized by the
 *	low-level driver.)
 * @करो_cmdtest: If the subdevice supports asynchronous acquisition commands,
 *	this poपूर्णांकs to a handler used to check and possibly tweak a prospective
 *	acquisition command without setting it up in hardware.  (Initialized by
 *	the low-level driver.)
 * @poll: If the subdevice supports asynchronous acquisition commands, this
 *	is an optional poपूर्णांकer to a handler क्रम the %COMEDI_POLL ioctl which
 *	inकाष्ठाs the low-level driver to synchronize buffers.  (Initialized by
 *	the low-level driver अगर needed.)
 * @cancel: If the subdevice supports asynchronous acquisition commands, this
 *	poपूर्णांकs to a handler used to terminate a running command.  (Initialized
 *	by the low-level driver.)
 * @buf_change: If the subdevice supports asynchronous acquisition commands,
 *	this is an optional poपूर्णांकer to a handler that is called when the data
 *	buffer क्रम handling asynchronous commands is allocated or पुनः_स्मृतिated.
 *	(Initialized by the low-level driver अगर needed.)
 * @munge: If the subdevice supports asynchronous acquisition commands and
 *	uses DMA to transfer data from the hardware to the acquisition buffer,
 *	this poपूर्णांकs to a function used to "munge" the data values from the
 *	hardware पूर्णांकo the क्रमmat expected by COMEDI.  (Initialized by the
 *	low-level driver अगर needed.)
 * @async_dma_dir: If the subdevice supports asynchronous acquisition commands
 *	and uses DMA to transfer data from the hardware to the acquisition
 *	buffer, this sets the DMA direction क्रम the buffer. (initialized to
 *	%DMA_NONE by comedi_alloc_subdevices() and changed by the low-level
 *	driver अगर necessary.)
 * @state: Handy bit-mask indicating the output states क्रम a DIO or digital
 *	output subdevice with no more than 32 channels. (Initialized by the
 *	low-level driver.)
 * @class_dev: If the subdevice supports asynchronous acquisition commands,
 *	this poपूर्णांकs to a sysfs comediX_subdY device where X is the minor device
 *	number of the COMEDI device and Y is the subdevice number.  The minor
 *	device number क्रम the sysfs device is allocated dynamically in the
 *	range 48 to 255.  This is used to allow the COMEDI device to be खोलोed
 *	with a dअगरferent शेष पढ़ो or ग_लिखो subdevice.  (Allocated during
 *	post-configuration अगर needed.)
 * @minor: If @class_dev is set, this is its dynamically allocated minor
 *	device number.  (Set during post-configuration अगर necessary.)
 * @पढ़ोback: Optional poपूर्णांकer to memory allocated by
 *	comedi_alloc_subdev_पढ़ोback() used to hold the values written to
 *	analog output channels so they can be पढ़ो back.  The storage is
 *	स्वतःmatically मुक्तd after the low-level driver's "detach" handler is
 *	called क्रम the device.  (Initialized by the low-level driver.)
 *
 * This is the मुख्य control काष्ठाure क्रम a COMEDI subdevice.  If the subdevice
 * supports asynchronous acquisition commands, additional inक्रमmation is stored
 * in the &काष्ठा comedi_async poपूर्णांकed to by @async.
 *
 * Most of the subdevice is initialized by the low-level driver's "attach" or
 * "auto_attach" handlers but parts of it are initialized by
 * comedi_alloc_subdevices(), and other parts are initialized during
 * post-configuration on वापस from that handler.
 *
 * A low-level driver that sets @insn_bits क्रम a digital input, digital output,
 * or DIO subdevice may leave @insn_पढ़ो and @insn_ग_लिखो uninitialized, in
 * which हाल they will be set to a शेष handler during post-configuration
 * that uses @insn_bits to emulate the %INSN_READ and %INSN_WRITE inकाष्ठाions.
 */
काष्ठा comedi_subdevice अणु
	काष्ठा comedi_device *device;
	पूर्णांक index;
	पूर्णांक type;
	पूर्णांक n_chan;
	पूर्णांक subdev_flags;
	पूर्णांक len_chanlist;	/* maximum length of channel/gain list */

	व्योम *निजी;

	काष्ठा comedi_async *async;

	व्योम *lock;
	व्योम *busy;
	अचिन्हित पूर्णांक runflags;
	spinlock_t spin_lock;	/* generic spin-lock क्रम COMEDI and drivers */

	अचिन्हित पूर्णांक io_bits;

	अचिन्हित पूर्णांक maxdata;	/* अगर maxdata==0, use list */
	स्थिर अचिन्हित पूर्णांक *maxdata_list;	/* list is channel specअगरic */

	स्थिर काष्ठा comedi_lrange *range_table;
	स्थिर काष्ठा comedi_lrange *स्थिर *range_table_list;

	अचिन्हित पूर्णांक *chanlist;	/* driver-owned chanlist (not used) */

	पूर्णांक (*insn_पढ़ो)(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);
	पूर्णांक (*insn_ग_लिखो)(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);
	पूर्णांक (*insn_bits)(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);
	पूर्णांक (*insn_config)(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित पूर्णांक *data);

	पूर्णांक (*करो_cmd)(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s);
	पूर्णांक (*करो_cmdtest)(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_cmd *cmd);
	पूर्णांक (*poll)(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s);
	पूर्णांक (*cancel)(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s);

	/* called when the buffer changes */
	पूर्णांक (*buf_change)(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s);

	व्योम (*munge)(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		      व्योम *data, अचिन्हित पूर्णांक num_bytes,
		      अचिन्हित पूर्णांक start_chan_index);
	क्रमागत dma_data_direction async_dma_dir;

	अचिन्हित पूर्णांक state;

	काष्ठा device *class_dev;
	पूर्णांक minor;

	अचिन्हित पूर्णांक *पढ़ोback;
पूर्ण;

/**
 * काष्ठा comedi_buf_page - Describe a page of a COMEDI buffer
 * @virt_addr: Kernel address of page.
 * @dma_addr: DMA address of page अगर in DMA coherent memory.
 */
काष्ठा comedi_buf_page अणु
	व्योम *virt_addr;
	dma_addr_t dma_addr;
पूर्ण;

/**
 * काष्ठा comedi_buf_map - Describe pages in a COMEDI buffer
 * @dma_hw_dev: Low-level hardware &काष्ठा device poपूर्णांकer copied from the
 *	COMEDI device's hw_dev member.
 * @page_list: Poपूर्णांकer to array of &काष्ठा comedi_buf_page, one क्रम each
 *	page in the buffer.
 * @n_pages: Number of pages in the buffer.
 * @dma_dir: DMA direction used to allocate pages of DMA coherent memory,
 *	or %DMA_NONE अगर pages allocated from regular memory.
 * @refcount: &काष्ठा kref reference counter used to मुक्त the buffer.
 *
 * A COMEDI data buffer is allocated as inभागidual pages, either in
 * conventional memory or DMA coherent memory, depending on the attached,
 * low-level hardware device.  (The buffer pages also get mapped पूर्णांकo the
 * kernel's contiguous virtual address space pointed to by the 'prealloc_buf'
 * member of &काष्ठा comedi_async.)
 *
 * The buffer is normally मुक्तd when the COMEDI device is detached from the
 * low-level driver (which may happen due to device removal), but अगर it happens
 * to be mmapped at the समय, the pages cannot be मुक्तd until the buffer has
 * been munmapped.  That is what the reference counter is क्रम.  (The भव
 * address space poपूर्णांकed by 'prealloc_buf' is मुक्तd when the COMEDI device is
 * detached.)
 */
काष्ठा comedi_buf_map अणु
	काष्ठा device *dma_hw_dev;
	काष्ठा comedi_buf_page *page_list;
	अचिन्हित पूर्णांक n_pages;
	क्रमागत dma_data_direction dma_dir;
	काष्ठा kref refcount;
पूर्ण;

/**
 * काष्ठा comedi_async - Control data क्रम asynchronous COMEDI commands
 * @pपुनः_स्मृति_buf: Kernel भव address of allocated acquisition buffer.
 * @pपुनः_स्मृति_bufsz: Buffer size (in bytes).
 * @buf_map: Map of buffer pages.
 * @max_bufsize: Maximum allowed buffer size (in bytes).
 * @buf_ग_लिखो_count: "Write completed" count (in bytes, modulo 2**32).
 * @buf_ग_लिखो_alloc_count: "Allocated for writing" count (in bytes,
 *	modulo 2**32).
 * @buf_पढ़ो_count: "Read completed" count (in bytes, modulo 2**32).
 * @buf_पढ़ो_alloc_count: "Allocated for reading" count (in bytes,
 *	modulo 2**32).
 * @buf_ग_लिखो_ptr: Buffer position क्रम ग_लिखोr.
 * @buf_पढ़ो_ptr: Buffer position क्रम पढ़ोer.
 * @cur_chan: Current position in chanlist क्रम scan (क्रम those drivers that
 *	use it).
 * @scans_करोne: The number of scans completed.
 * @scan_progress: Amount received or sent क्रम current scan (in bytes).
 * @munge_chan: Current position in chanlist क्रम "munging".
 * @munge_count: "Munge" count (in bytes, modulo 2**32).
 * @munge_ptr: Buffer position क्रम "munging".
 * @events: Bit-vector of events that have occurred.
 * @cmd: Details of comedi command in progress.
 * @रुको_head: Task रुको queue क्रम file पढ़ोer or ग_लिखोr.
 * @cb_mask: Bit-vector of events that should wake रुकोing tasks.
 * @पूर्णांकtrig: Software trigger function क्रम command, or शून्य.
 *
 * Note about the ..._count and ..._ptr members:
 *
 * Think of the _Count values being पूर्णांकegers of unlimited size, indexing
 * पूर्णांकo a buffer of infinite length (though only an advancing portion
 * of the buffer of fixed length pपुनः_स्मृति_bufsz is accessible at any
 * समय).  Then:
 *
 *   Buf_Read_Count <= Buf_Read_Alloc_Count <= Munge_Count <=
 *   Buf_Write_Count <= Buf_Write_Alloc_Count <=
 *   (Buf_Read_Count + pपुनः_स्मृति_bufsz)
 *
 * (Those aren't the actual members, apart from pपुनः_स्मृति_bufsz.) When the
 * buffer is reset, those _Count values start at 0 and only increase in value,
 * मुख्यtaining the above inequalities until the next समय the buffer is
 * reset.  The buffer is भागided पूर्णांकo the following regions by the inequalities:
 *
 *   [0, Buf_Read_Count):
 *     old region no दीर्घer accessible
 *
 *   [Buf_Read_Count, Buf_Read_Alloc_Count):
 *     filled and munged region allocated क्रम पढ़ोing but not yet पढ़ो
 *
 *   [Buf_Read_Alloc_Count, Munge_Count):
 *     filled and munged region not yet allocated क्रम पढ़ोing
 *
 *   [Munge_Count, Buf_Write_Count):
 *     filled region not yet munged
 *
 *   [Buf_Write_Count, Buf_Write_Alloc_Count):
 *     unfilled region allocated क्रम writing but not yet written
 *
 *   [Buf_Write_Alloc_Count, Buf_Read_Count + pपुनः_स्मृति_bufsz):
 *     unfilled region not yet allocated क्रम writing
 *
 *   [Buf_Read_Count + pपुनः_स्मृति_bufsz, infinity):
 *     unfilled region not yet accessible
 *
 * Data needs to be written पूर्णांकo the buffer beक्रमe it can be पढ़ो out,
 * and may need to be converted (or "munged") between the two
 * operations.  Extra unfilled buffer space may need to allocated क्रम
 * writing (advancing Buf_Write_Alloc_Count) beक्रमe new data is written.
 * After writing new data, the newly filled space needs to be released
 * (advancing Buf_Write_Count).  This also results in the new data being
 * "munged" (advancing Munge_Count).  Beक्रमe data is पढ़ो out of the
 * buffer, extra space may need to be allocated क्रम पढ़ोing (advancing
 * Buf_Read_Alloc_Count).  After the data has been पढ़ो out, the space
 * needs to be released (advancing Buf_Read_Count).
 *
 * The actual members, buf_पढ़ो_count, buf_पढ़ो_alloc_count,
 * munge_count, buf_ग_लिखो_count, and buf_ग_लिखो_alloc_count take the
 * value of the corresponding capitalized _Count values modulo 2^32
 * (अच_पूर्णांक_उच्च+1).  Subtracting a "higher" _count value from a "lower"
 * _count value gives the same answer as subtracting a "higher" _Count
 * value from a lower _Count value because pपुनः_स्मृति_bufsz < अच_पूर्णांक_उच्च+1.
 * The modulo operation is करोne implicitly.
 *
 * The buf_पढ़ो_ptr, munge_ptr, and buf_ग_लिखो_ptr members take the value
 * of the corresponding capitalized _Count values modulo pपुनः_स्मृति_bufsz.
 * These correspond to byte indices in the physical buffer.  The modulo
 * operation is करोne by subtracting pपुनः_स्मृति_bufsz when the value
 * exceeds pपुनः_स्मृति_bufsz (assuming pपुनः_स्मृति_bufsz plus the increment is
 * less than or equal to अच_पूर्णांक_उच्च).
 */
काष्ठा comedi_async अणु
	व्योम *pपुनः_स्मृति_buf;
	अचिन्हित पूर्णांक pपुनः_स्मृति_bufsz;
	काष्ठा comedi_buf_map *buf_map;
	अचिन्हित पूर्णांक max_bufsize;
	अचिन्हित पूर्णांक buf_ग_लिखो_count;
	अचिन्हित पूर्णांक buf_ग_लिखो_alloc_count;
	अचिन्हित पूर्णांक buf_पढ़ो_count;
	अचिन्हित पूर्णांक buf_पढ़ो_alloc_count;
	अचिन्हित पूर्णांक buf_ग_लिखो_ptr;
	अचिन्हित पूर्णांक buf_पढ़ो_ptr;
	अचिन्हित पूर्णांक cur_chan;
	अचिन्हित पूर्णांक scans_करोne;
	अचिन्हित पूर्णांक scan_progress;
	अचिन्हित पूर्णांक munge_chan;
	अचिन्हित पूर्णांक munge_count;
	अचिन्हित पूर्णांक munge_ptr;
	अचिन्हित पूर्णांक events;
	काष्ठा comedi_cmd cmd;
	रुको_queue_head_t रुको_head;
	अचिन्हित पूर्णांक cb_mask;
	पूर्णांक (*पूर्णांकtrig)(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		       अचिन्हित पूर्णांक x);
पूर्ण;

/**
 * क्रमागत comedi_cb - &काष्ठा comedi_async callback "events"
 * @COMEDI_CB_EOS:		end-of-scan
 * @COMEDI_CB_EOA:		end-of-acquisition/output
 * @COMEDI_CB_BLOCK:		data has arrived, wakes up पढ़ो() / ग_लिखो()
 * @COMEDI_CB_EOBUF:		DEPRECATED: end of buffer
 * @COMEDI_CB_ERROR:		card error during acquisition
 * @COMEDI_CB_OVERFLOW:		buffer overflow/underflow
 * @COMEDI_CB_ERROR_MASK:	events that indicate an error has occurred
 * @COMEDI_CB_CANCEL_MASK:	events that will cancel an async command
 */
क्रमागत comedi_cb अणु
	COMEDI_CB_EOS		= BIT(0),
	COMEDI_CB_EOA		= BIT(1),
	COMEDI_CB_BLOCK		= BIT(2),
	COMEDI_CB_EOBUF		= BIT(3),
	COMEDI_CB_ERROR		= BIT(4),
	COMEDI_CB_OVERFLOW	= BIT(5),
	/* masks */
	COMEDI_CB_ERROR_MASK	= (COMEDI_CB_ERROR | COMEDI_CB_OVERFLOW),
	COMEDI_CB_CANCEL_MASK	= (COMEDI_CB_EOA | COMEDI_CB_ERROR_MASK)
पूर्ण;

/**
 * काष्ठा comedi_driver - COMEDI driver registration
 * @driver_name: Name of driver.
 * @module: Owning module.
 * @attach: The optional "attach" handler क्रम manually configured COMEDI
 *	devices.
 * @detach: The "detach" handler क्रम deconfiguring COMEDI devices.
 * @स्वतः_attach: The optional "auto_attach" handler क्रम स्वतःmatically
 *	configured COMEDI devices.
 * @num_names: Optional number of "board names" supported.
 * @board_name: Optional poपूर्णांकer to a poपूर्णांकer to a board name.  The poपूर्णांकer
 *	to a board name is embedded in an element of a driver-defined array
 *	of अटल, पढ़ो-only board type inक्रमmation.
 * @offset: Optional size of each element of the driver-defined array of
 *	अटल, पढ़ो-only board type inक्रमmation, i.e. the offset between each
 *	poपूर्णांकer to a board name.
 *
 * This is used with comedi_driver_रेजिस्टर() and comedi_driver_unरेजिस्टर() to
 * रेजिस्टर and unरेजिस्टर a low-level COMEDI driver with the COMEDI core.
 *
 * If @num_names is non-zero, @board_name should be non-शून्य, and @offset
 * should be at least माप(*board_name).  These are used by the handler क्रम
 * the %COMEDI_DEVCONFIG ioctl to match a hardware device and its driver by
 * board name.  If @num_names is zero, the %COMEDI_DEVCONFIG ioctl matches a
 * hardware device and its driver by driver name.  This is only useful अगर the
 * @attach handler is set.  If @num_names is non-zero, the driver's @attach
 * handler will be called with the COMEDI device काष्ठाure's board_ptr member
 * poपूर्णांकing to the matched poपूर्णांकer to a board name within the driver's निजी
 * array of अटल, पढ़ो-only board type inक्रमmation.
 *
 * The @detach handler has two roles.  If a COMEDI device was successfully
 * configured by the @attach or @स्वतः_attach handler, it is called when the
 * device is being deconfigured (by the %COMEDI_DEVCONFIG ioctl, or due to
 * unloading of the driver, or due to device removal).  It is also called when
 * the @attach or @स्वतः_attach handler वापसs an error.  Thereक्रमe, the
 * @attach or @स्वतः_attach handlers can defer clean-up on error until the
 * @detach handler is called.  If the @attach or @स्वतः_attach handlers मुक्त
 * any resources themselves, they must prevent the @detach handler from
 * मुक्तing the same resources.  The @detach handler must not assume that all
 * resources requested by the @attach or @स्वतः_attach handler were
 * successfully allocated.
 */
काष्ठा comedi_driver अणु
	/* निजी: */
	काष्ठा comedi_driver *next;	/* Next in list of COMEDI drivers. */
	/* खुला: */
	स्थिर अक्षर *driver_name;
	काष्ठा module *module;
	पूर्णांक (*attach)(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it);
	व्योम (*detach)(काष्ठा comedi_device *dev);
	पूर्णांक (*स्वतः_attach)(काष्ठा comedi_device *dev, अचिन्हित दीर्घ context);
	अचिन्हित पूर्णांक num_names;
	स्थिर अक्षर *स्थिर *board_name;
	पूर्णांक offset;
पूर्ण;

/**
 * काष्ठा comedi_device - Working data क्रम a COMEDI device
 * @use_count: Number of खोलो file objects.
 * @driver: Low-level COMEDI driver attached to this COMEDI device.
 * @pacer: Optional poपूर्णांकer to a dynamically allocated acquisition pacer
 *	control.  It is मुक्तd स्वतःmatically after the COMEDI device is
 *	detached from the low-level driver.
 * @निजी: Optional poपूर्णांकer to निजी data allocated by the low-level
 *	driver.  It is मुक्तd स्वतःmatically after the COMEDI device is
 *	detached from the low-level driver.
 * @class_dev: Sysfs comediX device.
 * @minor: Minor device number of COMEDI अक्षर device (0-47).
 * @detach_count: Counter incremented every समय the COMEDI device is detached.
 *	Used क्रम checking a previous attachment is still valid.
 * @hw_dev: Optional poपूर्णांकer to the low-level hardware &काष्ठा device.  It is
 *	required क्रम स्वतःmatically configured COMEDI devices and optional क्रम
 *	COMEDI devices configured by the %COMEDI_DEVCONFIG ioctl, although
 *	the bus-specअगरic COMEDI functions only work अगर it is set correctly.
 *	It is also passed to dma_alloc_coherent() क्रम COMEDI subdevices that
 *	have their 'async_dma_dir' member set to something other than
 *	%DMA_NONE.
 * @board_name: Poपूर्णांकer to a COMEDI board name or a COMEDI driver name.  When
 *	the low-level driver's "attach" handler is called by the handler क्रम
 *	the %COMEDI_DEVCONFIG ioctl, it either poपूर्णांकs to a matched board name
 *	string अगर the 'num_names' member of the &काष्ठा comedi_driver is
 *	non-zero, otherwise it poपूर्णांकs to the low-level driver name string.
 *	When the low-lever driver's "auto_attach" handler is called क्रम an
 *	स्वतःmatically configured COMEDI device, it poपूर्णांकs to the low-level
 *	driver name string.  The low-level driver is मुक्त to change it in its
 *	"attach" or "auto_attach" handler अगर it wishes.
 * @board_ptr: Optional poपूर्णांकer to निजी, पढ़ो-only board type inक्रमmation in
 *	the low-level driver.  If the 'num_names' member of the &काष्ठा
 *	comedi_driver is non-zero, the handler क्रम the %COMEDI_DEVCONFIG ioctl
 *	will poपूर्णांक it to a poपूर्णांकer to a matched board name string within the
 *	driver's निजी array of अटल, पढ़ो-only board type inक्रमmation when
 *	calling the driver's "attach" handler.  The low-level driver is मुक्त to
 *	change it.
 * @attached: Flag indicating that the COMEDI device is attached to a low-level
 *	driver.
 * @ioenabled: Flag used to indicate that a PCI device has been enabled and
 *	its regions requested.
 * @spinlock: Generic spin-lock क्रम use by the low-level driver.
 * @mutex: Generic mutex क्रम use by the COMEDI core module.
 * @attach_lock: &काष्ठा rw_semaphore used to guard against the COMEDI device
 *	being detached जबतक an operation is in progress.  The करोwn_ग_लिखो()
 *	operation is only allowed जबतक @mutex is held and is used when
 *	changing @attached and @detach_count and calling the low-level driver's
 *	"detach" handler.  The करोwn_पढ़ो() operation is generally used without
 *	holding @mutex.
 * @refcount: &काष्ठा kref reference counter क्रम मुक्तing COMEDI device.
 * @n_subdevices: Number of COMEDI subdevices allocated by the low-level
 *	driver क्रम this device.
 * @subdevices: Dynamically allocated array of COMEDI subdevices.
 * @mmio: Optional poपूर्णांकer to a remapped MMIO region set by the low-level
 *	driver.
 * @iobase: Optional base of an I/O port region requested by the low-level
 *	driver.
 * @iolen: Length of I/O port region requested at @iobase.
 * @irq: Optional IRQ number requested by the low-level driver.
 * @पढ़ो_subdev: Optional poपूर्णांकer to a शेष COMEDI subdevice operated on by
 *	the पढ़ो() file operation.  Set by the low-level driver.
 * @ग_लिखो_subdev: Optional poपूर्णांकer to a शेष COMEDI subdevice operated on by
 *	the ग_लिखो() file operation.  Set by the low-level driver.
 * @async_queue: Storage क्रम fasync_helper().
 * @खोलो: Optional poपूर्णांकer to a function set by the low-level driver to be
 *	called when @use_count changes from 0 to 1.
 * @बंद: Optional poपूर्णांकer to a function set by the low-level driver to be
 *	called when @use_count changed from 1 to 0.
 * @insn_device_config: Optional poपूर्णांकer to a handler क्रम all sub-inकाष्ठाions
 *	except %INSN_DEVICE_CONFIG_GET_ROUTES of the %INSN_DEVICE_CONFIG
 *	inकाष्ठाion.  If this is not initialized by the low-level driver, a
 *	शेष handler will be set during post-configuration.
 * @get_valid_routes: Optional poपूर्णांकer to a handler क्रम the
 *	%INSN_DEVICE_CONFIG_GET_ROUTES sub-inकाष्ठाion of the
 *	%INSN_DEVICE_CONFIG inकाष्ठाion set.  If this is not initialized by the
 *	low-level driver, a शेष handler that copies zero routes back to the
 *	user will be used.
 *
 * This is the मुख्य control data काष्ठाure क्रम a COMEDI device (as far as the
 * COMEDI core is concerned).  There are two groups of COMEDI devices -
 * "legacy" devices that are configured by the handler क्रम the
 * %COMEDI_DEVCONFIG ioctl, and स्वतःmatically configured devices resulting
 * from a call to comedi_स्वतः_config() as a result of a bus driver probe in
 * a low-level COMEDI driver.  The "legacy" COMEDI devices are allocated
 * during module initialization अगर the "comedi_num_legacy_minors" module
 * parameter is non-zero and use minor device numbers from 0 to
 * comedi_num_legacy_minors minus one.  The स्वतःmatically configured COMEDI
 * devices are allocated on demand and use minor device numbers from
 * comedi_num_legacy_minors to 47.
 */
काष्ठा comedi_device अणु
	पूर्णांक use_count;
	काष्ठा comedi_driver *driver;
	काष्ठा comedi_8254 *pacer;
	व्योम *निजी;

	काष्ठा device *class_dev;
	पूर्णांक minor;
	अचिन्हित पूर्णांक detach_count;
	काष्ठा device *hw_dev;

	स्थिर अक्षर *board_name;
	स्थिर व्योम *board_ptr;
	अचिन्हित पूर्णांक attached:1;
	अचिन्हित पूर्णांक ioenabled:1;
	spinlock_t spinlock;	/* generic spin-lock क्रम low-level driver */
	काष्ठा mutex mutex;	/* generic mutex क्रम COMEDI core */
	काष्ठा rw_semaphore attach_lock;
	काष्ठा kref refcount;

	पूर्णांक n_subdevices;
	काष्ठा comedi_subdevice *subdevices;

	/* dumb */
	व्योम __iomem *mmio;
	अचिन्हित दीर्घ iobase;
	अचिन्हित दीर्घ iolen;
	अचिन्हित पूर्णांक irq;

	काष्ठा comedi_subdevice *पढ़ो_subdev;
	काष्ठा comedi_subdevice *ग_लिखो_subdev;

	काष्ठा fasync_काष्ठा *async_queue;

	पूर्णांक (*खोलो)(काष्ठा comedi_device *dev);
	व्योम (*बंद)(काष्ठा comedi_device *dev);
	पूर्णांक (*insn_device_config)(काष्ठा comedi_device *dev,
				  काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);
	अचिन्हित पूर्णांक (*get_valid_routes)(काष्ठा comedi_device *dev,
					 अचिन्हित पूर्णांक n_pairs,
					 अचिन्हित पूर्णांक *pair_data);
पूर्ण;

/*
 * function prototypes
 */

व्योम comedi_event(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s);

काष्ठा comedi_device *comedi_dev_get_from_minor(अचिन्हित पूर्णांक minor);
पूर्णांक comedi_dev_put(काष्ठा comedi_device *dev);

bool comedi_is_subdevice_running(काष्ठा comedi_subdevice *s);

व्योम *comedi_alloc_spriv(काष्ठा comedi_subdevice *s, माप_प्रकार size);
व्योम comedi_set_spriv_स्वतः_मुक्त(काष्ठा comedi_subdevice *s);

पूर्णांक comedi_check_chanlist(काष्ठा comedi_subdevice *s,
			  पूर्णांक n,
			  अचिन्हित पूर्णांक *chanlist);

/* range stuff */

#घोषणा RANGE(a, b)		अणु(a) * 1e6, (b) * 1e6, 0पूर्ण
#घोषणा RANGE_ext(a, b)		अणु(a) * 1e6, (b) * 1e6, RF_EXTERNALपूर्ण
#घोषणा RANGE_mA(a, b)		अणु(a) * 1e6, (b) * 1e6, UNIT_mAपूर्ण
#घोषणा RANGE_unitless(a, b)	अणु(a) * 1e6, (b) * 1e6, 0पूर्ण
#घोषणा BIP_RANGE(a)		अणु-(a) * 1e6, (a) * 1e6, 0पूर्ण
#घोषणा UNI_RANGE(a)		अणु0, (a) * 1e6, 0पूर्ण

बाह्य स्थिर काष्ठा comedi_lrange range_bipolar10;
बाह्य स्थिर काष्ठा comedi_lrange range_bipolar5;
बाह्य स्थिर काष्ठा comedi_lrange range_bipolar2_5;
बाह्य स्थिर काष्ठा comedi_lrange range_unipolar10;
बाह्य स्थिर काष्ठा comedi_lrange range_unipolar5;
बाह्य स्थिर काष्ठा comedi_lrange range_unipolar2_5;
बाह्य स्थिर काष्ठा comedi_lrange range_0_20mA;
बाह्य स्थिर काष्ठा comedi_lrange range_4_20mA;
बाह्य स्थिर काष्ठा comedi_lrange range_0_32mA;
बाह्य स्थिर काष्ठा comedi_lrange range_unknown;

#घोषणा range_digital		range_unipolar5

/**
 * काष्ठा comedi_lrange - Describes a COMEDI range table
 * @length: Number of entries in the range table.
 * @range: Array of &काष्ठा comedi_krange, one क्रम each range.
 *
 * Each element of @range[] describes the minimum and maximum physical range
 * and the type of units.  Typically, the type of unit is %UNIT_volt
 * (i.e. volts) and the minimum and maximum are in millionths of a volt.
 * There may also be a flag that indicates the minimum and maximum are merely
 * scale factors क्रम an unknown, बाह्यal reference.
 */
काष्ठा comedi_lrange अणु
	पूर्णांक length;
	काष्ठा comedi_krange range[];
पूर्ण;

/**
 * comedi_range_is_bipolar() - Test अगर subdevice range is bipolar
 * @s: COMEDI subdevice.
 * @range: Index of range within a range table.
 *
 * Tests whether a range is bipolar by checking whether its minimum value
 * is negative.
 *
 * Assumes @range is valid.  Does not work क्रम subdevices using a
 * channel-specअगरic range table list.
 *
 * Return:
 *	%true अगर the range is bipolar.
 *	%false अगर the range is unipolar.
 */
अटल अंतरभूत bool comedi_range_is_bipolar(काष्ठा comedi_subdevice *s,
					   अचिन्हित पूर्णांक range)
अणु
	वापस s->range_table->range[range].min < 0;
पूर्ण

/**
 * comedi_range_is_unipolar() - Test अगर subdevice range is unipolar
 * @s: COMEDI subdevice.
 * @range: Index of range within a range table.
 *
 * Tests whether a range is unipolar by checking whether its minimum value
 * is at least 0.
 *
 * Assumes @range is valid.  Does not work क्रम subdevices using a
 * channel-specअगरic range table list.
 *
 * Return:
 *	%true अगर the range is unipolar.
 *	%false अगर the range is bipolar.
 */
अटल अंतरभूत bool comedi_range_is_unipolar(काष्ठा comedi_subdevice *s,
					    अचिन्हित पूर्णांक range)
अणु
	वापस s->range_table->range[range].min >= 0;
पूर्ण

/**
 * comedi_range_is_बाह्यal() - Test अगर subdevice range is बाह्यal
 * @s: COMEDI subdevice.
 * @range: Index of range within a range table.
 *
 * Tests whether a range is बाह्यally reference by checking whether its
 * %RF_EXTERNAL flag is set.
 *
 * Assumes @range is valid.  Does not work क्रम subdevices using a
 * channel-specअगरic range table list.
 *
 * Return:
 *	%true अगर the range is बाह्यal.
 *	%false अगर the range is पूर्णांकernal.
 */
अटल अंतरभूत bool comedi_range_is_बाह्यal(काष्ठा comedi_subdevice *s,
					    अचिन्हित पूर्णांक range)
अणु
	वापस !!(s->range_table->range[range].flags & RF_EXTERNAL);
पूर्ण

/**
 * comedi_chan_range_is_bipolar() - Test अगर channel-specअगरic range is bipolar
 * @s: COMEDI subdevice.
 * @chan: The channel number.
 * @range: Index of range within a range table.
 *
 * Tests whether a range is bipolar by checking whether its minimum value
 * is negative.
 *
 * Assumes @chan and @range are valid.  Only works क्रम subdevices with a
 * channel-specअगरic range table list.
 *
 * Return:
 *	%true अगर the range is bipolar.
 *	%false अगर the range is unipolar.
 */
अटल अंतरभूत bool comedi_chan_range_is_bipolar(काष्ठा comedi_subdevice *s,
						अचिन्हित पूर्णांक chan,
						अचिन्हित पूर्णांक range)
अणु
	वापस s->range_table_list[chan]->range[range].min < 0;
पूर्ण

/**
 * comedi_chan_range_is_unipolar() - Test अगर channel-specअगरic range is unipolar
 * @s: COMEDI subdevice.
 * @chan: The channel number.
 * @range: Index of range within a range table.
 *
 * Tests whether a range is unipolar by checking whether its minimum value
 * is at least 0.
 *
 * Assumes @chan and @range are valid.  Only works क्रम subdevices with a
 * channel-specअगरic range table list.
 *
 * Return:
 *	%true अगर the range is unipolar.
 *	%false अगर the range is bipolar.
 */
अटल अंतरभूत bool comedi_chan_range_is_unipolar(काष्ठा comedi_subdevice *s,
						 अचिन्हित पूर्णांक chan,
						 अचिन्हित पूर्णांक range)
अणु
	वापस s->range_table_list[chan]->range[range].min >= 0;
पूर्ण

/**
 * comedi_chan_range_is_बाह्यal() - Test अगर channel-specअगरic range is बाह्यal
 * @s: COMEDI subdevice.
 * @chan: The channel number.
 * @range: Index of range within a range table.
 *
 * Tests whether a range is बाह्यally reference by checking whether its
 * %RF_EXTERNAL flag is set.
 *
 * Assumes @chan and @range are valid.  Only works क्रम subdevices with a
 * channel-specअगरic range table list.
 *
 * Return:
 *	%true अगर the range is bipolar.
 *	%false अगर the range is unipolar.
 */
अटल अंतरभूत bool comedi_chan_range_is_बाह्यal(काष्ठा comedi_subdevice *s,
						 अचिन्हित पूर्णांक chan,
						 अचिन्हित पूर्णांक range)
अणु
	वापस !!(s->range_table_list[chan]->range[range].flags & RF_EXTERNAL);
पूर्ण

/**
 * comedi_offset_munge() - Convert between offset binary and 2's complement
 * @s: COMEDI subdevice.
 * @val: Value to be converted.
 *
 * Toggles the highest bit of a sample value to toggle between offset binary
 * and 2's complement.  Assumes that @s->maxdata is a घातer of 2 minus 1.
 *
 * Return: The converted value.
 */
अटल अंतरभूत अचिन्हित पूर्णांक comedi_offset_munge(काष्ठा comedi_subdevice *s,
					       अचिन्हित पूर्णांक val)
अणु
	वापस val ^ s->maxdata ^ (s->maxdata >> 1);
पूर्ण

/**
 * comedi_bytes_per_sample() - Determine subdevice sample size
 * @s: COMEDI subdevice.
 *
 * The sample size will be 4 (माप पूर्णांक) or 2 (माप लघु) depending on
 * whether the %SDF_LSAMPL subdevice flag is set or not.
 *
 * Return: The subdevice sample size.
 */
अटल अंतरभूत अचिन्हित पूर्णांक comedi_bytes_per_sample(काष्ठा comedi_subdevice *s)
अणु
	वापस s->subdev_flags & SDF_LSAMPL ? माप(पूर्णांक) : माप(लघु);
पूर्ण

/**
 * comedi_sample_shअगरt() - Determine log2 of subdevice sample size
 * @s: COMEDI subdevice.
 *
 * The sample size will be 4 (माप पूर्णांक) or 2 (माप लघु) depending on
 * whether the %SDF_LSAMPL subdevice flag is set or not.  The log2 of the
 * sample size will be 2 or 1 and can be used as the right opeअक्रम of a
 * bit-shअगरt चालक to multiply or भागide something by the sample size.
 *
 * Return: log2 of the subdevice sample size.
 */
अटल अंतरभूत अचिन्हित पूर्णांक comedi_sample_shअगरt(काष्ठा comedi_subdevice *s)
अणु
	वापस s->subdev_flags & SDF_LSAMPL ? 2 : 1;
पूर्ण

/**
 * comedi_bytes_to_samples() - Convert a number of bytes to a number of samples
 * @s: COMEDI subdevice.
 * @nbytes: Number of bytes
 *
 * Return: The number of bytes भागided by the subdevice sample size.
 */
अटल अंतरभूत अचिन्हित पूर्णांक comedi_bytes_to_samples(काष्ठा comedi_subdevice *s,
						   अचिन्हित पूर्णांक nbytes)
अणु
	वापस nbytes >> comedi_sample_shअगरt(s);
पूर्ण

/**
 * comedi_samples_to_bytes() - Convert a number of samples to a number of bytes
 * @s: COMEDI subdevice.
 * @nsamples: Number of samples.
 *
 * Return: The number of samples multiplied by the subdevice sample size.
 * (Does not check क्रम arithmetic overflow.)
 */
अटल अंतरभूत अचिन्हित पूर्णांक comedi_samples_to_bytes(काष्ठा comedi_subdevice *s,
						   अचिन्हित पूर्णांक nsamples)
अणु
	वापस nsamples << comedi_sample_shअगरt(s);
पूर्ण

/**
 * comedi_check_trigger_src() - Trivially validate a comedi_cmd trigger source
 * @src: Poपूर्णांकer to the trigger source to validate.
 * @flags: Biपंचांगask of valid %TRIG_* क्रम the trigger.
 *
 * This is used in "step 1" of the करो_cmdtest functions of comedi drivers
 * to validate the comedi_cmd triggers. The mask of the @src against the
 * @flags allows the userspace comedilib to pass all the comedi_cmd
 * triggers as %TRIG_ANY and get back a biपंचांगask of the valid trigger sources.
 *
 * Return:
 *	0 अगर trigger sources in *@src are all supported.
 *	-EINVAL अगर any trigger source in *@src is unsupported.
 */
अटल अंतरभूत पूर्णांक comedi_check_trigger_src(अचिन्हित पूर्णांक *src,
					   अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक orig_src = *src;

	*src = orig_src & flags;
	अगर (*src == TRIG_INVALID || *src != orig_src)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 * comedi_check_trigger_is_unique() - Make sure a trigger source is unique
 * @src: The trigger source to check.
 *
 * Return:
 *	0 अगर no more than one trigger source is set.
 *	-EINVAL अगर more than one trigger source is set.
 */
अटल अंतरभूत पूर्णांक comedi_check_trigger_is_unique(अचिन्हित पूर्णांक src)
अणु
	/* this test is true अगर more than one _src bit is set */
	अगर ((src & (src - 1)) != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 * comedi_check_trigger_arg_is() - Trivially validate a trigger argument
 * @arg: Poपूर्णांकer to the trigger arg to validate.
 * @val: The value the argument should be.
 *
 * Forces *@arg to be @val.
 *
 * Return:
 *	0 अगर *@arg was alपढ़ोy @val.
 *	-EINVAL अगर *@arg dअगरfered from @val.
 */
अटल अंतरभूत पूर्णांक comedi_check_trigger_arg_is(अचिन्हित पूर्णांक *arg,
					      अचिन्हित पूर्णांक val)
अणु
	अगर (*arg != val) अणु
		*arg = val;
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * comedi_check_trigger_arg_min() - Trivially validate a trigger argument min
 * @arg: Poपूर्णांकer to the trigger arg to validate.
 * @val: The minimum value the argument should be.
 *
 * Forces *@arg to be at least @val, setting it to @val अगर necessary.
 *
 * Return:
 *	0 अगर *@arg was alपढ़ोy at least @val.
 *	-EINVAL अगर *@arg was less than @val.
 */
अटल अंतरभूत पूर्णांक comedi_check_trigger_arg_min(अचिन्हित पूर्णांक *arg,
					       अचिन्हित पूर्णांक val)
अणु
	अगर (*arg < val) अणु
		*arg = val;
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * comedi_check_trigger_arg_max() - Trivially validate a trigger argument max
 * @arg: Poपूर्णांकer to the trigger arg to validate.
 * @val: The maximum value the argument should be.
 *
 * Forces *@arg to be no more than @val, setting it to @val अगर necessary.
 *
 * Return:
 *	0 अगर*@arg was alपढ़ोy no more than @val.
 *	-EINVAL अगर *@arg was greater than @val.
 */
अटल अंतरभूत पूर्णांक comedi_check_trigger_arg_max(अचिन्हित पूर्णांक *arg,
					       अचिन्हित पूर्णांक val)
अणु
	अगर (*arg > val) अणु
		*arg = val;
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Must set dev->hw_dev अगर you wish to dma directly पूर्णांकo comedi's buffer.
 * Also useful क्रम retrieving a previously configured hardware device of
 * known bus type.  Set स्वतःmatically क्रम स्वतः-configured devices.
 * Automatically set to शून्य when detaching hardware device.
 */
पूर्णांक comedi_set_hw_dev(काष्ठा comedi_device *dev, काष्ठा device *hw_dev);

/**
 * comedi_buf_n_bytes_पढ़ोy - Determine amount of unपढ़ो data in buffer
 * @s: COMEDI subdevice.
 *
 * Determines the number of bytes of unपढ़ो data in the asynchronous
 * acquisition data buffer क्रम a subdevice.  The data in question might not
 * have been fully "munged" yet.
 *
 * Returns: The amount of unपढ़ो data in bytes.
 */
अटल अंतरभूत अचिन्हित पूर्णांक comedi_buf_n_bytes_पढ़ोy(काष्ठा comedi_subdevice *s)
अणु
	वापस s->async->buf_ग_लिखो_count - s->async->buf_पढ़ो_count;
पूर्ण

अचिन्हित पूर्णांक comedi_buf_ग_लिखो_alloc(काष्ठा comedi_subdevice *s, अचिन्हित पूर्णांक n);
अचिन्हित पूर्णांक comedi_buf_ग_लिखो_मुक्त(काष्ठा comedi_subdevice *s, अचिन्हित पूर्णांक n);

अचिन्हित पूर्णांक comedi_buf_पढ़ो_n_available(काष्ठा comedi_subdevice *s);
अचिन्हित पूर्णांक comedi_buf_पढ़ो_alloc(काष्ठा comedi_subdevice *s, अचिन्हित पूर्णांक n);
अचिन्हित पूर्णांक comedi_buf_पढ़ो_मुक्त(काष्ठा comedi_subdevice *s, अचिन्हित पूर्णांक n);

अचिन्हित पूर्णांक comedi_buf_ग_लिखो_samples(काष्ठा comedi_subdevice *s,
				      स्थिर व्योम *data, अचिन्हित पूर्णांक nsamples);
अचिन्हित पूर्णांक comedi_buf_पढ़ो_samples(काष्ठा comedi_subdevice *s,
				     व्योम *data, अचिन्हित पूर्णांक nsamples);

/* drivers.c - general comedi driver functions */

#घोषणा COMEDI_TIMEOUT_MS	1000

पूर्णांक comedi_समयout(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		   काष्ठा comedi_insn *insn,
		   पूर्णांक (*cb)(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn, अचिन्हित दीर्घ context),
		   अचिन्हित दीर्घ context);

अचिन्हित पूर्णांक comedi_handle_events(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s);

पूर्णांक comedi_dio_insn_config(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data,
			   अचिन्हित पूर्णांक mask);
अचिन्हित पूर्णांक comedi_dio_update_state(काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक *data);
अचिन्हित पूर्णांक comedi_bytes_per_scan_cmd(काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_cmd *cmd);
अचिन्हित पूर्णांक comedi_bytes_per_scan(काष्ठा comedi_subdevice *s);
अचिन्हित पूर्णांक comedi_nscans_left(काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक nscans);
अचिन्हित पूर्णांक comedi_nsamples_left(काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक nsamples);
व्योम comedi_inc_scan_progress(काष्ठा comedi_subdevice *s,
			      अचिन्हित पूर्णांक num_bytes);

व्योम *comedi_alloc_devpriv(काष्ठा comedi_device *dev, माप_प्रकार size);
पूर्णांक comedi_alloc_subdevices(काष्ठा comedi_device *dev, पूर्णांक num_subdevices);
पूर्णांक comedi_alloc_subdev_पढ़ोback(काष्ठा comedi_subdevice *s);

पूर्णांक comedi_पढ़ोback_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);

पूर्णांक comedi_load_firmware(काष्ठा comedi_device *dev, काष्ठा device *hw_dev,
			 स्थिर अक्षर *name,
			 पूर्णांक (*cb)(काष्ठा comedi_device *dev,
				   स्थिर u8 *data, माप_प्रकार size,
				   अचिन्हित दीर्घ context),
			 अचिन्हित दीर्घ context);

पूर्णांक __comedi_request_region(काष्ठा comedi_device *dev,
			    अचिन्हित दीर्घ start, अचिन्हित दीर्घ len);
पूर्णांक comedi_request_region(काष्ठा comedi_device *dev,
			  अचिन्हित दीर्घ start, अचिन्हित दीर्घ len);
व्योम comedi_legacy_detach(काष्ठा comedi_device *dev);

पूर्णांक comedi_स्वतः_config(काष्ठा device *hardware_device,
		       काष्ठा comedi_driver *driver, अचिन्हित दीर्घ context);
व्योम comedi_स्वतः_unconfig(काष्ठा device *hardware_device);

पूर्णांक comedi_driver_रेजिस्टर(काष्ठा comedi_driver *driver);
व्योम comedi_driver_unरेजिस्टर(काष्ठा comedi_driver *driver);

/**
 * module_comedi_driver() - Helper macro क्रम रेजिस्टरing a comedi driver
 * @__comedi_driver: comedi_driver काष्ठा
 *
 * Helper macro क्रम comedi drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only use
 * this macro once, and calling it replaces module_init() and module_निकास().
 */
#घोषणा module_comedi_driver(__comedi_driver) \
	module_driver(__comedi_driver, comedi_driver_रेजिस्टर, \
			comedi_driver_unरेजिस्टर)

#पूर्ण_अगर /* _COMEDIDEV_H */
