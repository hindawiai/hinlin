<शैली गुरु>
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#समावेश <linux/delay.h>
#समावेश "hfi.h"
#समावेश "common.h"
#समावेश "eprom.h"

/*
 * The EPROM is logically भागided पूर्णांकo three partitions:
 *	partition 0: the first 128K, visible from PCI ROM BAR
 *	partition 1: 4K config file (sector size)
 *	partition 2: the rest
 */
#घोषणा P0_SIZE (128 * 1024)
#घोषणा P1_SIZE   (4 * 1024)
#घोषणा P1_START P0_SIZE
#घोषणा P2_START (P0_SIZE + P1_SIZE)

/* controller page size, in bytes */
#घोषणा EP_PAGE_SIZE 256
#घोषणा EP_PAGE_MASK (EP_PAGE_SIZE - 1)
#घोषणा EP_PAGE_DWORDS (EP_PAGE_SIZE / माप(u32))

/* controller commands */
#घोषणा CMD_SHIFT 24
#घोषणा CMD_NOP			    (0)
#घोषणा CMD_READ_DATA(addr)	    ((0x03 << CMD_SHIFT) | addr)
#घोषणा CMD_RELEASE_POWERDOWN_NOID  ((0xab << CMD_SHIFT))

/* controller पूर्णांकerface speeds */
#घोषणा EP_SPEED_FULL 0x2	/* full speed */

/*
 * How दीर्घ to रुको क्रम the EPROM to become available, in ms.
 * The spec 32 Mb EPROM takes around 40s to erase then ग_लिखो.
 * Double it क्रम safety.
 */
#घोषणा EPROM_TIMEOUT 80000 /* ms */

/*
 * Read a 256 byte (64 dword) EPROM page.
 * All callers have verअगरied the offset is at a page boundary.
 */
अटल व्योम पढ़ो_page(काष्ठा hfi1_devdata *dd, u32 offset, u32 *result)
अणु
	पूर्णांक i;

	ग_लिखो_csr(dd, ASIC_EEP_ADDR_CMD, CMD_READ_DATA(offset));
	क्रम (i = 0; i < EP_PAGE_DWORDS; i++)
		result[i] = (u32)पढ़ो_csr(dd, ASIC_EEP_DATA);
	ग_लिखो_csr(dd, ASIC_EEP_ADDR_CMD, CMD_NOP); /* बंद खोलो page */
पूर्ण

/*
 * Read length bytes starting at offset from the start of the EPROM.
 */
अटल पूर्णांक पढ़ो_length(काष्ठा hfi1_devdata *dd, u32 start, u32 len, व्योम *dest)
अणु
	u32 buffer[EP_PAGE_DWORDS];
	u32 end;
	u32 start_offset;
	u32 पढ़ो_start;
	u32 bytes;

	अगर (len == 0)
		वापस 0;

	end = start + len;

	/*
	 * Make sure the पढ़ो range is not outside of the controller पढ़ो
	 * command address range.  Note that '>' is correct below - the end
	 * of the range is OK अगर it stops at the limit, but no higher.
	 */
	अगर (end > (1 << CMD_SHIFT))
		वापस -EINVAL;

	/* पढ़ो the first partial page */
	start_offset = start & EP_PAGE_MASK;
	अगर (start_offset) अणु
		/* partial starting page */

		/* align and पढ़ो the page that contains the start */
		पढ़ो_start = start & ~EP_PAGE_MASK;
		पढ़ो_page(dd, पढ़ो_start, buffer);

		/* the rest of the page is available data */
		bytes = EP_PAGE_SIZE - start_offset;

		अगर (len <= bytes) अणु
			/* end is within this page */
			स_नकल(dest, (u8 *)buffer + start_offset, len);
			वापस 0;
		पूर्ण

		स_नकल(dest, (u8 *)buffer + start_offset, bytes);

		start += bytes;
		len -= bytes;
		dest += bytes;
	पूर्ण
	/* start is now page aligned */

	/* पढ़ो whole pages */
	जबतक (len >= EP_PAGE_SIZE) अणु
		पढ़ो_page(dd, start, buffer);
		स_नकल(dest, buffer, EP_PAGE_SIZE);

		start += EP_PAGE_SIZE;
		len -= EP_PAGE_SIZE;
		dest += EP_PAGE_SIZE;
	पूर्ण

	/* पढ़ो the last partial page */
	अगर (len) अणु
		पढ़ो_page(dd, start, buffer);
		स_नकल(dest, buffer, len);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Initialize the EPROM handler.
 */
पूर्णांक eprom_init(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret = 0;

	/* only the discrete chip has an EPROM */
	अगर (dd->pcidev->device != PCI_DEVICE_ID_INTEL0)
		वापस 0;

	/*
	 * It is OK अगर both HFIs reset the EPROM as दीर्घ as they करोn't
	 * करो it at the same समय.
	 */
	ret = acquire_chip_resource(dd, CR_EPROM, EPROM_TIMEOUT);
	अगर (ret) अणु
		dd_dev_err(dd,
			   "%s: unable to acquire EPROM resource, no EPROM support\n",
			   __func__);
		जाओ करोne_asic;
	पूर्ण

	/* reset EPROM to be sure it is in a good state */

	/* set reset */
	ग_लिखो_csr(dd, ASIC_EEP_CTL_STAT, ASIC_EEP_CTL_STAT_EP_RESET_SMASK);
	/* clear reset, set speed */
	ग_लिखो_csr(dd, ASIC_EEP_CTL_STAT,
		  EP_SPEED_FULL << ASIC_EEP_CTL_STAT_RATE_SPI_SHIFT);

	/* wake the device with command "release powerdown NoID" */
	ग_लिखो_csr(dd, ASIC_EEP_ADDR_CMD, CMD_RELEASE_POWERDOWN_NOID);

	dd->eprom_available = true;
	release_chip_resource(dd, CR_EPROM);
करोne_asic:
	वापस ret;
पूर्ण

/* magic अक्षरacter sequence that begins an image */
#घोषणा IMAGE_START_MAGIC "APO="

/* magic अक्षरacter sequence that might trail an image */
#घोषणा IMAGE_TRAIL_MAGIC "egamiAPO"

/* EPROM file types */
#घोषणा HFI1_EFT_PLATFORM_CONFIG 2

/* segment size - 128 KiB */
#घोषणा SEG_SIZE (128 * 1024)

काष्ठा hfi1_eprom_footer अणु
	u32 oprom_size;		/* size of the oprom, in bytes */
	u16 num_table_entries;
	u16 version;		/* version of this footer */
	u32 magic;		/* must be last */
पूर्ण;

काष्ठा hfi1_eprom_table_entry अणु
	u32 type;		/* file type */
	u32 offset;		/* file offset from start of EPROM */
	u32 size;		/* file size, in bytes */
पूर्ण;

/*
 * Calculate the max number of table entries that will fit within a directory
 * buffer of size 'dir_size'.
 */
#घोषणा MAX_TABLE_ENTRIES(dir_size) \
	(((dir_size) - माप(काष्ठा hfi1_eprom_footer)) / \
		माप(काष्ठा hfi1_eprom_table_entry))

#घोषणा सूचीECTORY_SIZE(n) (माप(काष्ठा hfi1_eprom_footer) + \
	(माप(काष्ठा hfi1_eprom_table_entry) * (n)))

#घोषणा MAGIC4(a, b, c, d) ((d) << 24 | (c) << 16 | (b) << 8 | (a))
#घोषणा FOOTER_MAGIC MAGIC4('e', 'p', 'r', 'm')
#घोषणा FOOTER_VERSION 1

/*
 * Read all of partition 1.  The actual file is at the front.  Adjust
 * the वापसed size अगर a trailing image magic is found.
 */
अटल पूर्णांक पढ़ो_partition_platक्रमm_config(काष्ठा hfi1_devdata *dd, व्योम **data,
					  u32 *size)
अणु
	व्योम *buffer;
	व्योम *p;
	u32 length;
	पूर्णांक ret;

	buffer = kदो_स्मृति(P1_SIZE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	ret = पढ़ो_length(dd, P1_START, P1_SIZE, buffer);
	अगर (ret) अणु
		kमुक्त(buffer);
		वापस ret;
	पूर्ण

	/* config partition is valid only अगर it starts with IMAGE_START_MAGIC */
	अगर (स_भेद(buffer, IMAGE_START_MAGIC, म_माप(IMAGE_START_MAGIC))) अणु
		kमुक्त(buffer);
		वापस -ENOENT;
	पूर्ण

	/* scan क्रम image magic that may trail the actual data */
	p = strnstr(buffer, IMAGE_TRAIL_MAGIC, P1_SIZE);
	अगर (p)
		length = p - buffer;
	अन्यथा
		length = P1_SIZE;

	*data = buffer;
	*size = length;
	वापस 0;
पूर्ण

/*
 * The segment magic has been checked.  There is a footer and table of
 * contents present.
 *
 * directory is a u32 aligned buffer of size EP_PAGE_SIZE.
 */
अटल पूर्णांक पढ़ो_segment_platक्रमm_config(काष्ठा hfi1_devdata *dd,
					व्योम *directory, व्योम **data, u32 *size)
अणु
	काष्ठा hfi1_eprom_footer *footer;
	काष्ठा hfi1_eprom_table_entry *table;
	काष्ठा hfi1_eprom_table_entry *entry;
	व्योम *buffer = शून्य;
	व्योम *table_buffer = शून्य;
	पूर्णांक ret, i;
	u32 directory_size;
	u32 seg_base, seg_offset;
	u32 bytes_available, ncopied, to_copy;

	/* the footer is at the end of the directory */
	footer = (काष्ठा hfi1_eprom_footer *)
			(directory + EP_PAGE_SIZE - माप(*footer));

	/* make sure the काष्ठाure version is supported */
	अगर (footer->version != FOOTER_VERSION)
		वापस -EINVAL;

	/* oprom size cannot be larger than a segment */
	अगर (footer->oprom_size >= SEG_SIZE)
		वापस -EINVAL;

	/* the file table must fit in a segment with the oprom */
	अगर (footer->num_table_entries >
			MAX_TABLE_ENTRIES(SEG_SIZE - footer->oprom_size))
		वापस -EINVAL;

	/* find the file table start, which precedes the footer */
	directory_size = सूचीECTORY_SIZE(footer->num_table_entries);
	अगर (directory_size <= EP_PAGE_SIZE) अणु
		/* the file table fits पूर्णांकo the directory buffer handed in */
		table = (काष्ठा hfi1_eprom_table_entry *)
				(directory + EP_PAGE_SIZE - directory_size);
	पूर्ण अन्यथा अणु
		/* need to allocate and पढ़ो more */
		table_buffer = kदो_स्मृति(directory_size, GFP_KERNEL);
		अगर (!table_buffer)
			वापस -ENOMEM;
		ret = पढ़ो_length(dd, SEG_SIZE - directory_size,
				  directory_size, table_buffer);
		अगर (ret)
			जाओ करोne;
		table = table_buffer;
	पूर्ण

	/* look क्रम the platक्रमm configuration file in the table */
	क्रम (entry = शून्य, i = 0; i < footer->num_table_entries; i++) अणु
		अगर (table[i].type == HFI1_EFT_PLATFORM_CONFIG) अणु
			entry = &table[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!entry) अणु
		ret = -ENOENT;
		जाओ करोne;
	पूर्ण

	/*
	 * Sanity check on the configuration file size - it should never
	 * be larger than 4 KiB.
	 */
	अगर (entry->size > (4 * 1024)) अणु
		dd_dev_err(dd, "Bad configuration file size 0x%x\n",
			   entry->size);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* check क्रम bogus offset and size that wrap when added together */
	अगर (entry->offset + entry->size < entry->offset) अणु
		dd_dev_err(dd,
			   "Bad configuration file start + size 0x%x+0x%x\n",
			   entry->offset, entry->size);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* allocate the buffer to वापस */
	buffer = kदो_स्मृति(entry->size, GFP_KERNEL);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/*
	 * Extract the file by looping over segments until it is fully पढ़ो.
	 */
	seg_offset = entry->offset % SEG_SIZE;
	seg_base = entry->offset - seg_offset;
	ncopied = 0;
	जबतक (ncopied < entry->size) अणु
		/* calculate data bytes available in this segment */

		/* start with the bytes from the current offset to the end */
		bytes_available = SEG_SIZE - seg_offset;
		/* subtract off footer and table from segment 0 */
		अगर (seg_base == 0) अणु
			/*
			 * Sanity check: should not have a starting poपूर्णांक
			 * at or within the directory.
			 */
			अगर (bytes_available <= directory_size) अणु
				dd_dev_err(dd,
					   "Bad configuration file - offset 0x%x within footer+table\n",
					   entry->offset);
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			bytes_available -= directory_size;
		पूर्ण

		/* calculate bytes wanted */
		to_copy = entry->size - ncopied;

		/* max out at the available bytes in this segment */
		अगर (to_copy > bytes_available)
			to_copy = bytes_available;

		/*
		 * Read from the EPROM.
		 *
		 * The sanity check क्रम entry->offset is करोne in पढ़ो_length().
		 * The EPROM offset is validated against what the hardware
		 * addressing supports.  In addition, अगर the offset is larger
		 * than the actual EPROM, it silently wraps.  It will work
		 * fine, though the पढ़ोer may not get what they expected
		 * from the EPROM.
		 */
		ret = पढ़ो_length(dd, seg_base + seg_offset, to_copy,
				  buffer + ncopied);
		अगर (ret)
			जाओ करोne;

		ncopied += to_copy;

		/* set up क्रम next segment */
		seg_offset = footer->oprom_size;
		seg_base += SEG_SIZE;
	पूर्ण

	/* success */
	ret = 0;
	*data = buffer;
	*size = entry->size;

करोne:
	kमुक्त(table_buffer);
	अगर (ret)
		kमुक्त(buffer);
	वापस ret;
पूर्ण

/*
 * Read the platक्रमm configuration file from the EPROM.
 *
 * On success, an allocated buffer containing the data and its size are
 * वापसed.  It is up to the caller to मुक्त this buffer.
 *
 * Return value:
 *   0	      - success
 *   -ENXIO   - no EPROM is available
 *   -EBUSY   - not able to acquire access to the EPROM
 *   -ENOENT  - no recognizable file written
 *   -ENOMEM  - buffer could not be allocated
 *   -EINVAL  - invalid EPROM contentents found
 */
पूर्णांक eprom_पढ़ो_platक्रमm_config(काष्ठा hfi1_devdata *dd, व्योम **data, u32 *size)
अणु
	u32 directory[EP_PAGE_DWORDS]; /* aligned buffer */
	पूर्णांक ret;

	अगर (!dd->eprom_available)
		वापस -ENXIO;

	ret = acquire_chip_resource(dd, CR_EPROM, EPROM_TIMEOUT);
	अगर (ret)
		वापस -EBUSY;

	/* पढ़ो the last page of the segment क्रम the EPROM क्रमmat magic */
	ret = पढ़ो_length(dd, SEG_SIZE - EP_PAGE_SIZE, EP_PAGE_SIZE, directory);
	अगर (ret)
		जाओ करोne;

	/* last dword of the segment contains a magic value */
	अगर (directory[EP_PAGE_DWORDS - 1] == FOOTER_MAGIC) अणु
		/* segment क्रमmat */
		ret = पढ़ो_segment_platक्रमm_config(dd, directory, data, size);
	पूर्ण अन्यथा अणु
		/* partition क्रमmat */
		ret = पढ़ो_partition_platक्रमm_config(dd, data, size);
	पूर्ण

करोne:
	release_chip_resource(dd, CR_EPROM);
	वापस ret;
पूर्ण
