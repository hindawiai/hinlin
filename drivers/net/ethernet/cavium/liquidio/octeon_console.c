<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*
 * @file octeon_console.c
 */
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/crc32.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "liquidio_image.h"
#समावेश "octeon_mem_ops.h"

अटल व्योम octeon_remote_lock(व्योम);
अटल व्योम octeon_remote_unlock(व्योम);
अटल u64 cvmx_booपंचांगem_phy_named_block_find(काष्ठा octeon_device *oct,
					     स्थिर अक्षर *name,
					     u32 flags);
अटल पूर्णांक octeon_console_पढ़ो(काष्ठा octeon_device *oct, u32 console_num,
			       अक्षर *buffer, u32 buf_size);

#घोषणा BOOTLOADER_PCI_READ_BUFFER_DATA_ADDR    0x0006c008
#घोषणा BOOTLOADER_PCI_READ_BUFFER_LEN_ADDR     0x0006c004
#घोषणा BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR   0x0006c000
#घोषणा BOOTLOADER_PCI_READ_DESC_ADDR           0x0006c100
#घोषणा BOOTLOADER_PCI_WRITE_BUFFER_STR_LEN     248

#घोषणा OCTEON_PCI_IO_BUF_OWNER_OCTEON    0x00000001
#घोषणा OCTEON_PCI_IO_BUF_OWNER_HOST      0x00000002

/** Can change without अवरोधing ABI */
#घोषणा CVMX_BOOTMEM_NUM_NAMED_BLOCKS 64

/** minimum alignment of booपंचांगem alloced blocks */
#घोषणा CVMX_BOOTMEM_ALIGNMENT_SIZE     (16ull)

/** CVMX booपंचांगem descriptor major version */
#घोषणा CVMX_BOOTMEM_DESC_MAJ_VER   3
/* CVMX booपंचांगem descriptor minor version */
#घोषणा CVMX_BOOTMEM_DESC_MIN_VER   0

/* Current versions */
#घोषणा OCTEON_PCI_CONSOLE_MAJOR_VERSION    1
#घोषणा OCTEON_PCI_CONSOLE_MINOR_VERSION    0
#घोषणा OCTEON_PCI_CONSOLE_BLOCK_NAME   "__pci_console"
#घोषणा OCTEON_CONSOLE_POLL_INTERVAL_MS  100    /* 10 बार per second */

/* First three members of cvmx_booपंचांगem_desc are left in original
 * positions क्रम backwards compatibility.
 * Assumes big endian target
 */
काष्ठा cvmx_booपंचांगem_desc अणु
	/** spinlock to control access to list */
	u32 lock;

	/** flags क्रम indicating various conditions */
	u32 flags;

	u64 head_addr;

	/** incremented changed when incompatible changes made */
	u32 major_version;

	/** incremented changed when compatible changes made,
	 *  reset to zero when major incremented
	 */
	u32 minor_version;

	u64 app_data_addr;
	u64 app_data_size;

	/** number of elements in named blocks array */
	u32 nb_num_blocks;

	/** length of name array in booपंचांगem blocks */
	u32 named_block_name_len;

	/** address of named memory block descriptors */
	u64 named_block_array_addr;
पूर्ण;

/* Structure that defines a single console.
 *
 * Note: when पढ़ो_index == ग_लिखो_index, the buffer is empty.
 * The actual usable size of each console is console_buf_size -1;
 */
काष्ठा octeon_pci_console अणु
	u64 input_base_addr;
	u32 input_पढ़ो_index;
	u32 input_ग_लिखो_index;
	u64 output_base_addr;
	u32 output_पढ़ो_index;
	u32 output_ग_लिखो_index;
	u32 lock;
	u32 buf_size;
पूर्ण;

/* This is the मुख्य container काष्ठाure that contains all the inक्रमmation
 * about all PCI consoles.  The address of this काष्ठाure is passed to various
 * routines that operation on PCI consoles.
 */
काष्ठा octeon_pci_console_desc अणु
	u32 major_version;
	u32 minor_version;
	u32 lock;
	u32 flags;
	u32 num_consoles;
	u32 pad;
	/* must be 64 bit aligned here... */
	/* Array of addresses of octeon_pci_console काष्ठाures */
	u64 console_addr_array[];
	/* Implicit storage क्रम console_addr_array */
पूर्ण;

/*
 * This function is the implementation of the get macros defined
 * क्रम inभागidual काष्ठाure members. The argument are generated
 * by the macros inorder to पढ़ो only the needed memory.
 *
 * @param oct    Poपूर्णांकer to current octeon device
 * @param base   64bit physical address of the complete काष्ठाure
 * @param offset Offset from the beginning of the काष्ठाure to the member being
 *               accessed.
 * @param size   Size of the काष्ठाure member.
 *
 * @वापस Value of the काष्ठाure member promoted पूर्णांकo a u64.
 */
अटल अंतरभूत u64 __cvmx_booपंचांगem_desc_get(काष्ठा octeon_device *oct,
					  u64 base,
					  u32 offset,
					  u32 size)
अणु
	base = (1ull << 63) | (base + offset);
	चयन (size) अणु
	हाल 4:
		वापस octeon_पढ़ो_device_mem32(oct, base);
	हाल 8:
		वापस octeon_पढ़ो_device_mem64(oct, base);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * This function retrieves the string name of a named block. It is
 * more complicated than a simple स_नकल() since the named block
 * descriptor may not be directly accessible.
 *
 * @param addr   Physical address of the named block descriptor
 * @param str    String to receive the named block string name
 * @param len    Length of the string buffer, which must match the length
 *               stored in the booपंचांगem descriptor.
 */
अटल व्योम CVMX_BOOTMEM_NAMED_GET_NAME(काष्ठा octeon_device *oct,
					u64 addr,
					अक्षर *str,
					u32 len)
अणु
	addr += दुरत्व(काष्ठा cvmx_booपंचांगem_named_block_desc, name);
	octeon_pci_पढ़ो_core_mem(oct, addr, (u8 *)str, len);
	str[len] = 0;
पूर्ण

/* See header file क्रम descriptions of functions */

/*
 * Check the version inक्रमmation on the booपंचांगem descriptor
 *
 * @param exact_match
 *               Exact major version to check against. A zero means
 *               check that the version supports named blocks.
 *
 * @वापस Zero अगर the version is correct. Negative अगर the version is
 *         incorrect. Failures also cause a message to be displayed.
 */
अटल पूर्णांक __cvmx_booपंचांगem_check_version(काष्ठा octeon_device *oct,
					u32 exact_match)
अणु
	u32 major_version;
	u32 minor_version;

	अगर (!oct->booपंचांगem_desc_addr)
		oct->booपंचांगem_desc_addr =
			octeon_पढ़ो_device_mem64(oct,
						 BOOTLOADER_PCI_READ_DESC_ADDR);
	major_version = (u32)__cvmx_booपंचांगem_desc_get(
			oct, oct->booपंचांगem_desc_addr,
			दुरत्व(काष्ठा cvmx_booपंचांगem_desc, major_version),
			माप_field(काष्ठा cvmx_booपंचांगem_desc, major_version));
	minor_version = (u32)__cvmx_booपंचांगem_desc_get(
			oct, oct->booपंचांगem_desc_addr,
			दुरत्व(काष्ठा cvmx_booपंचांगem_desc, minor_version),
			माप_field(काष्ठा cvmx_booपंचांगem_desc, minor_version));

	dev_dbg(&oct->pci_dev->dev, "%s: major_version=%d\n", __func__,
		major_version);
	अगर ((major_version > 3) ||
	    (exact_match && major_version != exact_match)) अणु
		dev_err(&oct->pci_dev->dev, "bootmem ver mismatch %d.%d addr:0x%llx\n",
			major_version, minor_version,
			(दीर्घ दीर्घ)oct->booपंचांगem_desc_addr);
		वापस -1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा cvmx_booपंचांगem_named_block_desc
*__cvmx_booपंचांगem_find_named_block_flags(काष्ठा octeon_device *oct,
					स्थिर अक्षर *name, u32 flags)
अणु
	काष्ठा cvmx_booपंचांगem_named_block_desc *desc =
		&oct->booपंचांगem_named_block_desc;
	u64 named_addr = cvmx_booपंचांगem_phy_named_block_find(oct, name, flags);

	अगर (named_addr) अणु
		desc->base_addr = __cvmx_booपंचांगem_desc_get(
				oct, named_addr,
				दुरत्व(काष्ठा cvmx_booपंचांगem_named_block_desc,
					 base_addr),
				माप_field(
					काष्ठा cvmx_booपंचांगem_named_block_desc,
					base_addr));
		desc->size = __cvmx_booपंचांगem_desc_get(oct, named_addr,
				दुरत्व(काष्ठा cvmx_booपंचांगem_named_block_desc,
					 size),
				माप_field(
					काष्ठा cvmx_booपंचांगem_named_block_desc,
					size));

		म_नकलन(desc->name, name, माप(desc->name));
		desc->name[माप(desc->name) - 1] = 0;
		वापस &oct->booपंचांगem_named_block_desc;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण
पूर्ण

अटल u64 cvmx_booपंचांगem_phy_named_block_find(काष्ठा octeon_device *oct,
					     स्थिर अक्षर *name,
					     u32 flags)
अणु
	u64 result = 0;

	अगर (!__cvmx_booपंचांगem_check_version(oct, 3)) अणु
		u32 i;

		u64 named_block_array_addr = __cvmx_booपंचांगem_desc_get(
					oct, oct->booपंचांगem_desc_addr,
					दुरत्व(काष्ठा cvmx_booपंचांगem_desc,
						 named_block_array_addr),
					माप_field(काष्ठा cvmx_booपंचांगem_desc,
						     named_block_array_addr));
		u32 num_blocks = (u32)__cvmx_booपंचांगem_desc_get(
					oct, oct->booपंचांगem_desc_addr,
					दुरत्व(काष्ठा cvmx_booपंचांगem_desc,
						 nb_num_blocks),
					माप_field(काष्ठा cvmx_booपंचांगem_desc,
						     nb_num_blocks));

		u32 name_length = (u32)__cvmx_booपंचांगem_desc_get(
					oct, oct->booपंचांगem_desc_addr,
					दुरत्व(काष्ठा cvmx_booपंचांगem_desc,
						 named_block_name_len),
					माप_field(काष्ठा cvmx_booपंचांगem_desc,
						     named_block_name_len));

		u64 named_addr = named_block_array_addr;

		क्रम (i = 0; i < num_blocks; i++) अणु
			u64 named_size = __cvmx_booपंचांगem_desc_get(
					oct, named_addr,
					 दुरत्व(
					काष्ठा cvmx_booपंचांगem_named_block_desc,
					size),
					 माप_field(
					काष्ठा cvmx_booपंचांगem_named_block_desc,
					size));

			अगर (name && named_size) अणु
				अक्षर *name_पंचांगp =
					kदो_स्मृति(name_length + 1, GFP_KERNEL);
				अगर (!name_पंचांगp)
					अवरोध;

				CVMX_BOOTMEM_NAMED_GET_NAME(oct, named_addr,
							    name_पंचांगp,
							    name_length);
				अगर (!म_भेदन(name, name_पंचांगp, name_length)) अणु
					result = named_addr;
					kमुक्त(name_पंचांगp);
					अवरोध;
				पूर्ण
				kमुक्त(name_पंचांगp);
			पूर्ण अन्यथा अगर (!name && !named_size) अणु
				result = named_addr;
				अवरोध;
			पूर्ण

			named_addr +=
				माप(काष्ठा cvmx_booपंचांगem_named_block_desc);
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

/*
 * Find a named block on the remote Octeon
 *
 * @param name      Name of block to find
 * @param base_addr Address the block is at (OUTPUT)
 * @param size      The size of the block (OUTPUT)
 *
 * @वापस Zero on success, One on failure.
 */
अटल पूर्णांक octeon_named_block_find(काष्ठा octeon_device *oct, स्थिर अक्षर *name,
				   u64 *base_addr, u64 *size)
अणु
	स्थिर काष्ठा cvmx_booपंचांगem_named_block_desc *named_block;

	octeon_remote_lock();
	named_block = __cvmx_booपंचांगem_find_named_block_flags(oct, name, 0);
	octeon_remote_unlock();
	अगर (named_block) अणु
		*base_addr = named_block->base_addr;
		*size = named_block->size;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम octeon_remote_lock(व्योम)
अणु
	/* fill this in अगर any sharing is needed */
पूर्ण

अटल व्योम octeon_remote_unlock(व्योम)
अणु
	/* fill this in अगर any sharing is needed */
पूर्ण

पूर्णांक octeon_console_send_cmd(काष्ठा octeon_device *oct, अक्षर *cmd_str,
			    u32 रुको_hundredths)
अणु
	u32 len = (u32)म_माप(cmd_str);

	dev_dbg(&oct->pci_dev->dev, "sending \"%s\" to bootloader\n", cmd_str);

	अगर (len > BOOTLOADER_PCI_WRITE_BUFFER_STR_LEN - 1) अणु
		dev_err(&oct->pci_dev->dev, "Command string too long, max length is: %d\n",
			BOOTLOADER_PCI_WRITE_BUFFER_STR_LEN - 1);
		वापस -1;
	पूर्ण

	अगर (octeon_रुको_क्रम_bootloader(oct, रुको_hundredths) != 0) अणु
		dev_err(&oct->pci_dev->dev, "Bootloader not ready for command.\n");
		वापस -1;
	पूर्ण

	/* Write command to bootloader */
	octeon_remote_lock();
	octeon_pci_ग_लिखो_core_mem(oct, BOOTLOADER_PCI_READ_BUFFER_DATA_ADDR,
				  (u8 *)cmd_str, len);
	octeon_ग_लिखो_device_mem32(oct, BOOTLOADER_PCI_READ_BUFFER_LEN_ADDR,
				  len);
	octeon_ग_लिखो_device_mem32(oct, BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR,
				  OCTEON_PCI_IO_BUF_OWNER_OCTEON);

	/* Bootloader should accept command very quickly
	 * अगर it really was पढ़ोy
	 */
	अगर (octeon_रुको_क्रम_bootloader(oct, 200) != 0) अणु
		octeon_remote_unlock();
		dev_err(&oct->pci_dev->dev, "Bootloader did not accept command.\n");
		वापस -1;
	पूर्ण
	octeon_remote_unlock();
	वापस 0;
पूर्ण

पूर्णांक octeon_रुको_क्रम_bootloader(काष्ठा octeon_device *oct,
			       u32 रुको_समय_hundredths)
अणु
	dev_dbg(&oct->pci_dev->dev, "waiting %d0 ms for bootloader\n",
		रुको_समय_hundredths);

	अगर (octeon_mem_access_ok(oct))
		वापस -1;

	जबतक (रुको_समय_hundredths > 0 &&
	       octeon_पढ़ो_device_mem32(oct,
					BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR)
	       != OCTEON_PCI_IO_BUF_OWNER_HOST) अणु
		अगर (--रुको_समय_hundredths <= 0)
			वापस -1;
		schedule_समयout_unपूर्णांकerruptible(HZ / 100);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम octeon_console_handle_result(काष्ठा octeon_device *oct,
					 माप_प्रकार console_num)
अणु
	काष्ठा octeon_console *console;

	console = &oct->console[console_num];

	console->रुकोing = 0;
पूर्ण

अटल अक्षर console_buffer[OCTEON_CONSOLE_MAX_READ_BYTES];

अटल व्योम output_console_line(काष्ठा octeon_device *oct,
				काष्ठा octeon_console *console,
				माप_प्रकार console_num,
				अक्षर *console_buffer,
				s32 bytes_पढ़ो)
अणु
	अक्षर *line;
	s32 i;
	माप_प्रकार len;

	line = console_buffer;
	क्रम (i = 0; i < bytes_पढ़ो; i++) अणु
		/* Output a line at a समय, prefixed */
		अगर (console_buffer[i] == '\n') अणु
			console_buffer[i] = '\0';
			/* We need to output 'line', prefaced by 'leftover'.
			 * However, it is possible we're being called to
			 * output 'leftover' by itself (in the हाल of nothing
			 * having been पढ़ो from the console).
			 *
			 * To aव्योम duplication, check क्रम this condition.
			 */
			अगर (console->leftover[0] &&
			    (line != console->leftover)) अणु
				अगर (console->prपूर्णांक)
					(*console->prपूर्णांक)(oct, (u32)console_num,
							  console->leftover,
							  line);
				console->leftover[0] = '\0';
			पूर्ण अन्यथा अणु
				अगर (console->prपूर्णांक)
					(*console->prपूर्णांक)(oct, (u32)console_num,
							  line, शून्य);
			पूर्ण
			line = &console_buffer[i + 1];
		पूर्ण
	पूर्ण

	/* Save off any leftovers */
	अगर (line != &console_buffer[bytes_पढ़ो]) अणु
		console_buffer[bytes_पढ़ो] = '\0';
		len = म_माप(console->leftover);
		म_नकलन(&console->leftover[len], line,
			माप(console->leftover) - len);
	पूर्ण
पूर्ण

अटल व्योम check_console(काष्ठा work_काष्ठा *work)
अणु
	s32 bytes_पढ़ो, tries, total_पढ़ो;
	माप_प्रकार len;
	काष्ठा octeon_console *console;
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)wk->ctxptr;
	u32 console_num = (u32)wk->ctxul;
	u32 delay;

	console = &oct->console[console_num];
	tries = 0;
	total_पढ़ो = 0;

	करो अणु
		/* Take console output regardless of whether it will
		 * be logged
		 */
		bytes_पढ़ो =
			octeon_console_पढ़ो(oct, console_num, console_buffer,
					    माप(console_buffer) - 1);
		अगर (bytes_पढ़ो > 0) अणु
			total_पढ़ो += bytes_पढ़ो;
			अगर (console->रुकोing)
				octeon_console_handle_result(oct, console_num);
			अगर (console->prपूर्णांक) अणु
				output_console_line(oct, console, console_num,
						    console_buffer, bytes_पढ़ो);
			पूर्ण
		पूर्ण अन्यथा अगर (bytes_पढ़ो < 0) अणु
			dev_err(&oct->pci_dev->dev, "Error reading console %u, ret=%d\n",
				console_num, bytes_पढ़ो);
		पूर्ण

		tries++;
	पूर्ण जबतक ((bytes_पढ़ो > 0) && (tries < 16));

	/* If nothing is पढ़ो after polling the console,
	 * output any leftovers अगर any
	 */
	अगर (console->prपूर्णांक && (total_पढ़ो == 0) &&
	    (console->leftover[0])) अणु
		/* append '\n' as terminator for 'output_console_line' */
		len = म_माप(console->leftover);
		console->leftover[len] = '\n';
		output_console_line(oct, console, console_num,
				    console->leftover, (s32)(len + 1));
		console->leftover[0] = '\0';
	पूर्ण

	delay = OCTEON_CONSOLE_POLL_INTERVAL_MS;

	schedule_delayed_work(&wk->work, msecs_to_jअगरfies(delay));
पूर्ण

पूर्णांक octeon_init_consoles(काष्ठा octeon_device *oct)
अणु
	पूर्णांक ret = 0;
	u64 addr, size;

	ret = octeon_mem_access_ok(oct);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "Memory access not okay'\n");
		वापस ret;
	पूर्ण

	ret = octeon_named_block_find(oct, OCTEON_PCI_CONSOLE_BLOCK_NAME, &addr,
				      &size);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "Could not find console '%s'\n",
			OCTEON_PCI_CONSOLE_BLOCK_NAME);
		वापस ret;
	पूर्ण

	/* Dedicate one of Octeon's BAR1 index रेजिस्टरs to create a अटल
	 * mapping to a region of Octeon DRAM that contains the PCI console
	 * named block.
	 */
	oct->console_nb_info.bar1_index = BAR1_INDEX_STATIC_MAP;
	oct->fn_list.bar1_idx_setup(oct, addr, oct->console_nb_info.bar1_index,
				    true);
	oct->console_nb_info.dram_region_base = addr
		& ~(OCTEON_BAR1_ENTRY_SIZE - 1ULL);

	/* num_consoles > 0, is an indication that the consoles
	 * are accessible
	 */
	oct->num_consoles = octeon_पढ़ो_device_mem32(oct,
		addr + दुरत्व(काष्ठा octeon_pci_console_desc,
			num_consoles));
	oct->console_desc_addr = addr;

	dev_dbg(&oct->pci_dev->dev, "Initialized consoles. %d available\n",
		oct->num_consoles);

	वापस ret;
पूर्ण

अटल व्योम octeon_get_uboot_version(काष्ठा octeon_device *oct)
अणु
	s32 bytes_पढ़ो, tries, total_पढ़ो;
	काष्ठा octeon_console *console;
	u32 console_num = 0;
	अक्षर *uboot_ver;
	अक्षर *buf;
	अक्षर *p;

#घोषणा OCTEON_UBOOT_VER_BUF_SIZE 512
	buf = kदो_स्मृति(OCTEON_UBOOT_VER_BUF_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस;

	अगर (octeon_console_send_cmd(oct, "setenv stdout pci\n", 50)) अणु
		kमुक्त(buf);
		वापस;
	पूर्ण

	अगर (octeon_console_send_cmd(oct, "version\n", 1)) अणु
		kमुक्त(buf);
		वापस;
	पूर्ण

	console = &oct->console[console_num];
	tries = 0;
	total_पढ़ो = 0;

	करो अणु
		/* Take console output regardless of whether it will
		 * be logged
		 */
		bytes_पढ़ो =
			octeon_console_पढ़ो(oct,
					    console_num, buf + total_पढ़ो,
					    OCTEON_UBOOT_VER_BUF_SIZE - 1 -
					    total_पढ़ो);
		अगर (bytes_पढ़ो > 0) अणु
			buf[bytes_पढ़ो] = '\0';

			total_पढ़ो += bytes_पढ़ो;
			अगर (console->रुकोing)
				octeon_console_handle_result(oct, console_num);
		पूर्ण अन्यथा अगर (bytes_पढ़ो < 0) अणु
			dev_err(&oct->pci_dev->dev, "Error reading console %u, ret=%d\n",
				console_num, bytes_पढ़ो);
		पूर्ण

		tries++;
	पूर्ण जबतक ((bytes_पढ़ो > 0) && (tries < 16));

	/* If nothing is पढ़ो after polling the console,
	 * output any leftovers अगर any
	 */
	अगर ((total_पढ़ो == 0) && (console->leftover[0])) अणु
		dev_dbg(&oct->pci_dev->dev, "%u: %s\n",
			console_num, console->leftover);
		console->leftover[0] = '\0';
	पूर्ण

	buf[OCTEON_UBOOT_VER_BUF_SIZE - 1] = '\0';

	uboot_ver = म_माला(buf, "U-Boot");
	अगर (uboot_ver) अणु
		p = म_माला(uboot_ver, "mips");
		अगर (p) अणु
			p--;
			*p = '\0';
			dev_info(&oct->pci_dev->dev, "%s\n", uboot_ver);
		पूर्ण
	पूर्ण

	kमुक्त(buf);
	octeon_console_send_cmd(oct, "setenv stdout serial\n", 50);
पूर्ण

पूर्णांक octeon_add_console(काष्ठा octeon_device *oct, u32 console_num,
		       अक्षर *dbg_enb)
अणु
	पूर्णांक ret = 0;
	u32 delay;
	u64 coपढ़ोdr;
	काष्ठा delayed_work *work;
	काष्ठा octeon_console *console;

	अगर (console_num >= oct->num_consoles) अणु
		dev_err(&oct->pci_dev->dev,
			"trying to read from console number %d when only 0 to %d exist\n",
			console_num, oct->num_consoles);
	पूर्ण अन्यथा अणु
		console = &oct->console[console_num];

		console->रुकोing = 0;

		coपढ़ोdr = oct->console_desc_addr + console_num * 8 +
			दुरत्व(काष्ठा octeon_pci_console_desc,
				 console_addr_array);
		console->addr = octeon_पढ़ो_device_mem64(oct, coपढ़ोdr);
		coपढ़ोdr = console->addr + दुरत्व(काष्ठा octeon_pci_console,
						    buf_size);
		console->buffer_size = octeon_पढ़ो_device_mem32(oct, coपढ़ोdr);
		coपढ़ोdr = console->addr + दुरत्व(काष्ठा octeon_pci_console,
						    input_base_addr);
		console->input_base_addr =
			octeon_पढ़ो_device_mem64(oct, coपढ़ोdr);
		coपढ़ोdr = console->addr + दुरत्व(काष्ठा octeon_pci_console,
						    output_base_addr);
		console->output_base_addr =
			octeon_पढ़ो_device_mem64(oct, coपढ़ोdr);
		console->leftover[0] = '\0';

		work = &oct->console_poll_work[console_num].work;

		octeon_get_uboot_version(oct);

		INIT_DELAYED_WORK(work, check_console);
		oct->console_poll_work[console_num].ctxptr = (व्योम *)oct;
		oct->console_poll_work[console_num].ctxul = console_num;
		delay = OCTEON_CONSOLE_POLL_INTERVAL_MS;
		schedule_delayed_work(work, msecs_to_jअगरfies(delay));

		/* an empty string means use शेष debug console enablement */
		अगर (dbg_enb && !dbg_enb[0])
			dbg_enb = "setenv pci_console_active 1";
		अगर (dbg_enb)
			ret = octeon_console_send_cmd(oct, dbg_enb, 2000);

		console->active = 1;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Removes all consoles
 *
 * @param oct         octeon device
 */
व्योम octeon_हटाओ_consoles(काष्ठा octeon_device *oct)
अणु
	u32 i;
	काष्ठा octeon_console *console;

	क्रम (i = 0; i < oct->num_consoles; i++) अणु
		console = &oct->console[i];

		अगर (!console->active)
			जारी;

		cancel_delayed_work_sync(&oct->console_poll_work[i].
						work);
		console->addr = 0;
		console->buffer_size = 0;
		console->input_base_addr = 0;
		console->output_base_addr = 0;
	पूर्ण

	oct->num_consoles = 0;
पूर्ण

अटल अंतरभूत पूर्णांक octeon_console_मुक्त_bytes(u32 buffer_size,
					    u32 wr_idx,
					    u32 rd_idx)
अणु
	अगर (rd_idx >= buffer_size || wr_idx >= buffer_size)
		वापस -1;

	वापस ((buffer_size - 1) - (wr_idx - rd_idx)) % buffer_size;
पूर्ण

अटल अंतरभूत पूर्णांक octeon_console_avail_bytes(u32 buffer_size,
					     u32 wr_idx,
					     u32 rd_idx)
अणु
	अगर (rd_idx >= buffer_size || wr_idx >= buffer_size)
		वापस -1;

	वापस buffer_size - 1 -
	       octeon_console_मुक्त_bytes(buffer_size, wr_idx, rd_idx);
पूर्ण

अटल पूर्णांक octeon_console_पढ़ो(काष्ठा octeon_device *oct, u32 console_num,
			       अक्षर *buffer, u32 buf_size)
अणु
	पूर्णांक bytes_to_पढ़ो;
	u32 rd_idx, wr_idx;
	काष्ठा octeon_console *console;

	अगर (console_num >= oct->num_consoles) अणु
		dev_err(&oct->pci_dev->dev, "Attempted to read from disabled console %d\n",
			console_num);
		वापस 0;
	पूर्ण

	console = &oct->console[console_num];

	/* Check to see अगर any data is available.
	 * Maybe optimize this with 64-bit पढ़ो.
	 */
	rd_idx = octeon_पढ़ो_device_mem32(oct, console->addr +
		दुरत्व(काष्ठा octeon_pci_console, output_पढ़ो_index));
	wr_idx = octeon_पढ़ो_device_mem32(oct, console->addr +
		दुरत्व(काष्ठा octeon_pci_console, output_ग_लिखो_index));

	bytes_to_पढ़ो = octeon_console_avail_bytes(console->buffer_size,
						   wr_idx, rd_idx);
	अगर (bytes_to_पढ़ो <= 0)
		वापस bytes_to_पढ़ो;

	bytes_to_पढ़ो = min_t(s32, bytes_to_पढ़ो, buf_size);

	/* Check to see अगर what we want to पढ़ो is not contiguous, and limit
	 * ourselves to the contiguous block
	 */
	अगर (rd_idx + bytes_to_पढ़ो >= console->buffer_size)
		bytes_to_पढ़ो = console->buffer_size - rd_idx;

	octeon_pci_पढ़ो_core_mem(oct, console->output_base_addr + rd_idx,
				 (u8 *)buffer, bytes_to_पढ़ो);
	octeon_ग_लिखो_device_mem32(oct, console->addr +
				  दुरत्व(काष्ठा octeon_pci_console,
					   output_पढ़ो_index),
				  (rd_idx + bytes_to_पढ़ो) %
				  console->buffer_size);

	वापस bytes_to_पढ़ो;
पूर्ण

#घोषणा FBUF_SIZE	(4 * 1024 * 1024)
#घोषणा MAX_BOOTTIME_SIZE    80

पूर्णांक octeon_करोwnload_firmware(काष्ठा octeon_device *oct, स्थिर u8 *data,
			     माप_प्रकार size)
अणु
	काष्ठा octeon_firmware_file_header *h;
	अक्षर bootसमय[MAX_BOOTTIME_SIZE];
	काष्ठा बारpec64 ts;
	u32 crc32_result;
	u64 load_addr;
	u32 image_len;
	पूर्णांक ret = 0;
	u32 i, rem;

	अगर (size < माप(काष्ठा octeon_firmware_file_header)) अणु
		dev_err(&oct->pci_dev->dev, "Firmware file too small (%d < %d).\n",
			(u32)size,
			(u32)माप(काष्ठा octeon_firmware_file_header));
		वापस -EINVAL;
	पूर्ण

	h = (काष्ठा octeon_firmware_file_header *)data;

	अगर (be32_to_cpu(h->magic) != LIO_NIC_MAGIC) अणु
		dev_err(&oct->pci_dev->dev, "Unrecognized firmware file.\n");
		वापस -EINVAL;
	पूर्ण

	crc32_result = crc32((अचिन्हित पूर्णांक)~0, data,
			     माप(काष्ठा octeon_firmware_file_header) -
			     माप(u32)) ^ ~0U;
	अगर (crc32_result != be32_to_cpu(h->crc32)) अणु
		dev_err(&oct->pci_dev->dev, "Firmware CRC mismatch (0x%08x != 0x%08x).\n",
			crc32_result, be32_to_cpu(h->crc32));
		वापस -EINVAL;
	पूर्ण

	अगर (स_भेद(LIQUIDIO_BASE_VERSION, h->version,
		   म_माप(LIQUIDIO_BASE_VERSION))) अणु
		dev_err(&oct->pci_dev->dev, "Unmatched firmware version. Expected %s.x, got %s.\n",
			LIQUIDIO_BASE_VERSION,
			h->version);
		वापस -EINVAL;
	पूर्ण

	अगर (be32_to_cpu(h->num_images) > LIO_MAX_IMAGES) अणु
		dev_err(&oct->pci_dev->dev, "Too many images in firmware file (%d).\n",
			be32_to_cpu(h->num_images));
		वापस -EINVAL;
	पूर्ण

	dev_info(&oct->pci_dev->dev, "Firmware version: %s\n", h->version);
	snम_लिखो(oct->fw_info.liquidio_firmware_version, 32, "LIQUIDIO: %s",
		 h->version);

	data += माप(काष्ठा octeon_firmware_file_header);

	dev_info(&oct->pci_dev->dev, "%s: Loading %d images\n", __func__,
		 be32_to_cpu(h->num_images));
	/* load all images */
	क्रम (i = 0; i < be32_to_cpu(h->num_images); i++) अणु
		load_addr = be64_to_cpu(h->desc[i].addr);
		image_len = be32_to_cpu(h->desc[i].len);

		dev_info(&oct->pci_dev->dev, "Loading firmware %d at %llx\n",
			 image_len, load_addr);

		/* Write in 4MB chunks*/
		rem = image_len;

		जबतक (rem) अणु
			अगर (rem < FBUF_SIZE)
				size = rem;
			अन्यथा
				size = FBUF_SIZE;

			/* करोwnload the image */
			octeon_pci_ग_लिखो_core_mem(oct, load_addr, data, (u32)size);

			data += size;
			rem -= (u32)size;
			load_addr += size;
		पूर्ण
	पूर्ण

	/* Pass date and समय inक्रमmation to NIC at the समय of loading
	 * firmware and periodically update the host समय to NIC firmware.
	 * This is to make NIC firmware use the same समय reference as Host,
	 * so that it is easy to correlate logs from firmware and host क्रम
	 * debugging.
	 *
	 * Octeon always uses UTC समय. so समयzone inक्रमmation is not sent.
	 */
	kसमय_get_real_ts64(&ts);
	ret = snम_लिखो(bootसमय, MAX_BOOTTIME_SIZE,
		       " time_sec=%lld time_nsec=%ld",
		       (s64)ts.tv_sec, ts.tv_nsec);
	अगर ((माप(h->bootcmd) - strnlen(h->bootcmd, माप(h->bootcmd))) <
		ret) अणु
		dev_err(&oct->pci_dev->dev, "Boot command buffer too small\n");
		वापस -EINVAL;
	पूर्ण
	म_जोड़न(h->bootcmd, bootसमय,
		माप(h->bootcmd) - strnlen(h->bootcmd, माप(h->bootcmd)));

	dev_info(&oct->pci_dev->dev, "Writing boot command: %s\n",
		 h->bootcmd);

	/* Invoke the bootcmd */
	ret = octeon_console_send_cmd(oct, h->bootcmd, 50);
	अगर (ret)
		dev_info(&oct->pci_dev->dev, "Boot command send failed\n");

	वापस ret;
पूर्ण
