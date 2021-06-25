<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#समावेश <linux/i2c.h>
#समावेश <linux/firmware.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश "../include/linux/libmsrlisthelper.h"
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

/* Tagged binary data container काष्ठाure definitions. */
काष्ठा tbd_header अणु
	u32 tag;          /*!< Tag identअगरier, also checks endianness */
	u32 size;         /*!< Container size including this header */
	u32 version;      /*!< Version, क्रमmat 0xYYMMDDVV */
	u32 revision;     /*!< Revision, क्रमmat 0xYYMMDDVV */
	u32 config_bits;  /*!< Configuration flag bits set */
	u32 checksum;     /*!< Global checksum, header included */
पूर्ण __packed;

काष्ठा tbd_record_header अणु
	u32 size;        /*!< Size of record including header */
	u8 क्रमmat_id;    /*!< tbd_क्रमmat_t क्रमागतeration values used */
	u8 packing_key;  /*!< Packing method; 0 = no packing */
	u16 class_id;    /*!< tbd_class_t क्रमागतeration values used */
पूर्ण __packed;

काष्ठा tbd_data_record_header अणु
	u16 next_offset;
	u16 flags;
	u16 data_offset;
	u16 data_size;
पूर्ण __packed;

#घोषणा TBD_CLASS_DRV_ID 2

अटल पूर्णांक set_msr_configuration(काष्ठा i2c_client *client, uपूर्णांक8_t *bufptr,
				 अचिन्हित पूर्णांक size)
अणु
	/* The configuration data contains any number of sequences where
	 * the first byte (that is, uपूर्णांक8_t) that marks the number of bytes
	 * in the sequence to follow, is indeed followed by the indicated
	 * number of bytes of actual data to be written to sensor.
	 * By convention, the first two bytes of actual data should be
	 * understood as an address in the sensor address space (hibyte
	 * followed by lobyte) where the reमुख्यing data in the sequence
	 * will be written. */

	u8 *ptr = bufptr;

	जबतक (ptr < bufptr + size) अणु
		काष्ठा i2c_msg msg = अणु
			.addr = client->addr,
			.flags = 0,
		पूर्ण;
		पूर्णांक ret;

		/* How many bytes */
		msg.len = *ptr++;
		/* Where the bytes are located */
		msg.buf = ptr;
		ptr += msg.len;

		अगर (ptr > bufptr + size)
			/* Accessing data beyond bounds is not tolerated */
			वापस -EINVAL;

		ret = i2c_transfer(client->adapter, &msg, 1);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "i2c write error: %d", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_and_apply(काष्ठा i2c_client *client, uपूर्णांक8_t *buffer,
			   अचिन्हित पूर्णांक size)
अणु
	u8 *endptr8 = buffer + size;
	काष्ठा tbd_data_record_header *header =
	    (काष्ठा tbd_data_record_header *)buffer;

	/* There may be any number of datasets present */
	अचिन्हित पूर्णांक dataset = 0;

	करो अणु
		/* In below, four variables are पढ़ो from buffer */
		अगर ((uपूर्णांक8_t *)header + माप(*header) > endptr8)
			वापस -EINVAL;

		/* All data should be located within given buffer */
		अगर ((uपूर्णांक8_t *)header + header->data_offset +
		    header->data_size > endptr8)
			वापस -EINVAL;

		/* We have a new valid dataset */
		dataset++;
		/* See whether there is MSR data */
		/* If yes, update the reg info */
		अगर (header->data_size && (header->flags & 1)) अणु
			पूर्णांक ret;

			dev_info(&client->dev,
				 "New MSR data for sensor driver (dataset %02d) size:%d\n",
				 dataset, header->data_size);
			ret = set_msr_configuration(client,
						    buffer + header->data_offset,
						    header->data_size);
			अगर (ret)
				वापस ret;
		पूर्ण
		header = (काष्ठा tbd_data_record_header *)(buffer +
			 header->next_offset);
	पूर्ण जबतक (header->next_offset);

	वापस 0;
पूर्ण

पूर्णांक apply_msr_data(काष्ठा i2c_client *client, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा tbd_header *header;
	काष्ठा tbd_record_header *record;

	अगर (!fw) अणु
		dev_warn(&client->dev, "Drv data is not loaded.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (माप(*header) > fw->size)
		वापस -EINVAL;

	header = (काष्ठा tbd_header *)fw->data;
	/* Check that we have drvb block. */
	अगर (स_भेद(&header->tag, "DRVB", 4))
		वापस -EINVAL;

	/* Check the size */
	अगर (header->size != fw->size)
		वापस -EINVAL;

	अगर (माप(*header) + माप(*record) > fw->size)
		वापस -EINVAL;

	record = (काष्ठा tbd_record_header *)(header + 1);
	/* Check that class id mathes tbd's drv id. */
	अगर (record->class_id != TBD_CLASS_DRV_ID)
		वापस -EINVAL;

	/* Size 0 shall not be treated as an error */
	अगर (!record->size)
		वापस 0;

	वापस parse_and_apply(client, (uपूर्णांक8_t *)(record + 1), record->size);
पूर्ण
EXPORT_SYMBOL_GPL(apply_msr_data);

पूर्णांक load_msr_list(काष्ठा i2c_client *client, अक्षर *name,
		  स्थिर काष्ठा firmware **fw)
अणु
	पूर्णांक ret = request_firmware(fw, name, &client->dev);

	अगर (ret) अणु
		dev_err(&client->dev,
			"Error %d while requesting firmware %s\n",
			ret, name);
		वापस ret;
	पूर्ण
	dev_info(&client->dev, "Received %lu bytes drv data\n",
		 (अचिन्हित दीर्घ)(*fw)->size);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(load_msr_list);

व्योम release_msr_list(काष्ठा i2c_client *client, स्थिर काष्ठा firmware *fw)
अणु
	release_firmware(fw);
पूर्ण
EXPORT_SYMBOL_GPL(release_msr_list);

अटल पूर्णांक init_msrlisthelper(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम निकास_msrlisthelper(व्योम)
अणु
पूर्ण

module_init(init_msrlisthelper);
module_निकास(निकास_msrlisthelper);

MODULE_AUTHOR("Jukka Kaartinen <jukka.o.kaartinen@intel.com>");
MODULE_LICENSE("GPL");
