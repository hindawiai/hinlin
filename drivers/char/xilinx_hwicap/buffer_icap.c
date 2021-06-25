<शैली गुरु>
/*****************************************************************************
 *
 *     Author: Xilinx, Inc.
 *
 *     This program is मुक्त software; you can redistribute it and/or modअगरy it
 *     under the terms of the GNU General Public License as published by the
 *     Free Software Foundation; either version 2 of the License, or (at your
 *     option) any later version.
 *
 *     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
 *     AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
 *     SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
 *     OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
 *     APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
 *     THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
 *     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
 *     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
 *     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
 *     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
 *     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
 *     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE.
 *
 *     (c) Copyright 2003-2008 Xilinx Inc.
 *     All rights reserved.
 *
 *     You should have received a copy of the GNU General Public License aदीर्घ
 *     with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *     675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *****************************************************************************/

#समावेश "buffer_icap.h"

/* Indicates how many bytes will fit in a buffer. (1 BRAM) */
#घोषणा XHI_MAX_BUFFER_BYTES        2048
#घोषणा XHI_MAX_BUFFER_INTS         (XHI_MAX_BUFFER_BYTES >> 2)

/* File access and error स्थिरants */
#घोषणा XHI_DEVICE_READ_ERROR       -1
#घोषणा XHI_DEVICE_WRITE_ERROR      -2
#घोषणा XHI_BUFFER_OVERFLOW_ERROR   -3

#घोषणा XHI_DEVICE_READ             0x1
#घोषणा XHI_DEVICE_WRITE            0x0

/* Constants क्रम checking transfer status */
#घोषणा XHI_CYCLE_DONE              0
#घोषणा XHI_CYCLE_EXECUTING         1

/* buffer_icap रेजिस्टर offsets */

/* Size of transfer, पढ़ो & ग_लिखो */
#घोषणा XHI_SIZE_REG_OFFSET        0x800L
/* offset पूर्णांकo bram, पढ़ो & ग_लिखो */
#घोषणा XHI_BRAM_OFFSET_REG_OFFSET 0x804L
/* Read not Configure, direction of transfer.  Write only */
#घोषणा XHI_RNC_REG_OFFSET         0x808L
/* Indicates transfer complete. Read only */
#घोषणा XHI_STATUS_REG_OFFSET      0x80CL

/* Constants क्रम setting the RNC रेजिस्टर */
#घोषणा XHI_CONFIGURE              0x0UL
#घोषणा XHI_READBACK               0x1UL

/* Constants क्रम the Done रेजिस्टर */
#घोषणा XHI_NOT_FINISHED           0x0UL
#घोषणा XHI_FINISHED               0x1UL

#घोषणा XHI_BUFFER_START 0

/**
 * buffer_icap_get_status - Get the contents of the status रेजिस्टर.
 * @drvdata: a poपूर्णांकer to the drvdata.
 *
 * The status रेजिस्टर contains the ICAP status and the करोne bit.
 *
 * D8 - cfgerr
 * D7 - dalign
 * D6 - rip
 * D5 - in_पात_l
 * D4 - Always 1
 * D3 - Always 1
 * D2 - Always 1
 * D1 - Always 1
 * D0 - Done bit
 **/
u32 buffer_icap_get_status(काष्ठा hwicap_drvdata *drvdata)
अणु
	वापस in_be32(drvdata->base_address + XHI_STATUS_REG_OFFSET);
पूर्ण

/**
 * buffer_icap_get_bram - Reads data from the storage buffer bram.
 * @base_address: contains the base address of the component.
 * @offset: The word offset from which the data should be पढ़ो.
 *
 * A bram is used as a configuration memory cache.  One frame of data can
 * be stored in this "storage buffer".
 **/
अटल अंतरभूत u32 buffer_icap_get_bram(व्योम __iomem *base_address,
		u32 offset)
अणु
	वापस in_be32(base_address + (offset << 2));
पूर्ण

/**
 * buffer_icap_busy - Return true अगर the icap device is busy
 * @base_address: is the base address of the device
 *
 * The queries the low order bit of the status रेजिस्टर, which
 * indicates whether the current configuration or पढ़ोback operation
 * has completed.
 **/
अटल अंतरभूत bool buffer_icap_busy(व्योम __iomem *base_address)
अणु
	u32 status = in_be32(base_address + XHI_STATUS_REG_OFFSET);
	वापस (status & 1) == XHI_NOT_FINISHED;
पूर्ण

/**
 * buffer_icap_set_size - Set the size रेजिस्टर.
 * @base_address: is the base address of the device
 * @data: The size in bytes.
 *
 * The size रेजिस्टर holds the number of 8 bit bytes to transfer between
 * bram and the icap (or icap to bram).
 **/
अटल अंतरभूत व्योम buffer_icap_set_size(व्योम __iomem *base_address,
		u32 data)
अणु
	out_be32(base_address + XHI_SIZE_REG_OFFSET, data);
पूर्ण

/**
 * buffer_icap_set_offset - Set the bram offset रेजिस्टर.
 * @base_address: contains the base address of the device.
 * @data: is the value to be written to the data रेजिस्टर.
 *
 * The bram offset रेजिस्टर holds the starting bram address to transfer
 * data from during configuration or ग_लिखो data to during पढ़ोback.
 **/
अटल अंतरभूत व्योम buffer_icap_set_offset(व्योम __iomem *base_address,
		u32 data)
अणु
	out_be32(base_address + XHI_BRAM_OFFSET_REG_OFFSET, data);
पूर्ण

/**
 * buffer_icap_set_rnc - Set the RNC (Readback not Configure) रेजिस्टर.
 * @base_address: contains the base address of the device.
 * @data: is the value to be written to the data रेजिस्टर.
 *
 * The RNC रेजिस्टर determines the direction of the data transfer.  It
 * controls whether a configuration or पढ़ोback take place.  Writing to
 * this रेजिस्टर initiates the transfer.  A value of 1 initiates a
 * पढ़ोback जबतक writing a value of 0 initiates a configuration.
 **/
अटल अंतरभूत व्योम buffer_icap_set_rnc(व्योम __iomem *base_address,
		u32 data)
अणु
	out_be32(base_address + XHI_RNC_REG_OFFSET, data);
पूर्ण

/**
 * buffer_icap_set_bram - Write data to the storage buffer bram.
 * @base_address: contains the base address of the component.
 * @offset: The word offset at which the data should be written.
 * @data: The value to be written to the bram offset.
 *
 * A bram is used as a configuration memory cache.  One frame of data can
 * be stored in this "storage buffer".
 **/
अटल अंतरभूत व्योम buffer_icap_set_bram(व्योम __iomem *base_address,
		u32 offset, u32 data)
अणु
	out_be32(base_address + (offset << 2), data);
पूर्ण

/**
 * buffer_icap_device_पढ़ो - Transfer bytes from ICAP to the storage buffer.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @offset: The storage buffer start address.
 * @count: The number of words (32 bit) to पढ़ो from the
 *           device (ICAP).
 **/
अटल पूर्णांक buffer_icap_device_पढ़ो(काष्ठा hwicap_drvdata *drvdata,
		u32 offset, u32 count)
अणु

	s32 retries = 0;
	व्योम __iomem *base_address = drvdata->base_address;

	अगर (buffer_icap_busy(base_address))
		वापस -EBUSY;

	अगर ((offset + count) > XHI_MAX_BUFFER_INTS)
		वापस -EINVAL;

	/* setSize count*4 to get bytes. */
	buffer_icap_set_size(base_address, (count << 2));
	buffer_icap_set_offset(base_address, offset);
	buffer_icap_set_rnc(base_address, XHI_READBACK);

	जबतक (buffer_icap_busy(base_address)) अणु
		retries++;
		अगर (retries > XHI_MAX_RETRIES)
			वापस -EBUSY;
	पूर्ण
	वापस 0;

पूर्ण;

/**
 * buffer_icap_device_ग_लिखो - Transfer bytes from ICAP to the storage buffer.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @offset: The storage buffer start address.
 * @count: The number of words (32 bit) to पढ़ो from the
 *           device (ICAP).
 **/
अटल पूर्णांक buffer_icap_device_ग_लिखो(काष्ठा hwicap_drvdata *drvdata,
		u32 offset, u32 count)
अणु

	s32 retries = 0;
	व्योम __iomem *base_address = drvdata->base_address;

	अगर (buffer_icap_busy(base_address))
		वापस -EBUSY;

	अगर ((offset + count) > XHI_MAX_BUFFER_INTS)
		वापस -EINVAL;

	/* setSize count*4 to get bytes. */
	buffer_icap_set_size(base_address, count << 2);
	buffer_icap_set_offset(base_address, offset);
	buffer_icap_set_rnc(base_address, XHI_CONFIGURE);

	जबतक (buffer_icap_busy(base_address)) अणु
		retries++;
		अगर (retries > XHI_MAX_RETRIES)
			वापस -EBUSY;
	पूर्ण
	वापस 0;

पूर्ण;

/**
 * buffer_icap_reset - Reset the logic of the icap device.
 * @drvdata: a poपूर्णांकer to the drvdata.
 *
 * Writing to the status रेजिस्टर resets the ICAP logic in an पूर्णांकernal
 * version of the core.  For the version of the core published in EDK,
 * this is a noop.
 **/
व्योम buffer_icap_reset(काष्ठा hwicap_drvdata *drvdata)
अणु
    out_be32(drvdata->base_address + XHI_STATUS_REG_OFFSET, 0xFEFE);
पूर्ण

/**
 * buffer_icap_set_configuration - Load a partial bitstream from प्रणाली memory.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @data: Kernel address of the partial bitstream.
 * @size: the size of the partial bitstream in 32 bit words.
 **/
पूर्णांक buffer_icap_set_configuration(काष्ठा hwicap_drvdata *drvdata, u32 *data,
			     u32 size)
अणु
	पूर्णांक status;
	s32 buffer_count = 0;
	bool dirty = false;
	u32 i;
	व्योम __iomem *base_address = drvdata->base_address;

	/* Loop through all the data */
	क्रम (i = 0, buffer_count = 0; i < size; i++) अणु

		/* Copy data to bram */
		buffer_icap_set_bram(base_address, buffer_count, data[i]);
		dirty = true;

		अगर (buffer_count < XHI_MAX_BUFFER_INTS - 1) अणु
			buffer_count++;
			जारी;
		पूर्ण

		/* Write data to ICAP */
		status = buffer_icap_device_ग_लिखो(
				drvdata,
				XHI_BUFFER_START,
				XHI_MAX_BUFFER_INTS);
		अगर (status != 0) अणु
			/* पात. */
			buffer_icap_reset(drvdata);
			वापस status;
		पूर्ण

		buffer_count = 0;
		dirty = false;
	पूर्ण

	/* Write unwritten data to ICAP */
	अगर (dirty) अणु
		/* Write data to ICAP */
		status = buffer_icap_device_ग_लिखो(drvdata, XHI_BUFFER_START,
					     buffer_count);
		अगर (status != 0) अणु
			/* पात. */
			buffer_icap_reset(drvdata);
		पूर्ण
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण;

/**
 * buffer_icap_get_configuration - Read configuration data from the device.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @data: Address of the data representing the partial bitstream
 * @size: the size of the partial bitstream in 32 bit words.
 **/
पूर्णांक buffer_icap_get_configuration(काष्ठा hwicap_drvdata *drvdata, u32 *data,
			     u32 size)
अणु
	पूर्णांक status;
	s32 buffer_count = 0;
	u32 i;
	व्योम __iomem *base_address = drvdata->base_address;

	/* Loop through all the data */
	क्रम (i = 0, buffer_count = XHI_MAX_BUFFER_INTS; i < size; i++) अणु
		अगर (buffer_count == XHI_MAX_BUFFER_INTS) अणु
			u32 words_reमुख्यing = size - i;
			u32 words_to_पढ़ो =
				words_reमुख्यing <
				XHI_MAX_BUFFER_INTS ? words_reमुख्यing :
				XHI_MAX_BUFFER_INTS;

			/* Read data from ICAP */
			status = buffer_icap_device_पढ़ो(
					drvdata,
					XHI_BUFFER_START,
					words_to_पढ़ो);
			अगर (status != 0) अणु
				/* पात. */
				buffer_icap_reset(drvdata);
				वापस status;
			पूर्ण

			buffer_count = 0;
		पूर्ण

		/* Copy data from bram */
		data[i] = buffer_icap_get_bram(base_address, buffer_count);
		buffer_count++;
	पूर्ण

	वापस 0;
पूर्ण;
