<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dell_rbu.c
 * Bios Update driver क्रम Dell प्रणालीs
 * Author: Dell Inc
 *         Abhay Salunke <abhay_salunke@dell.com>
 *
 * Copyright (C) 2005 Dell Inc.
 *
 * Remote BIOS Update (rbu) driver is used क्रम updating DELL BIOS by
 * creating entries in the /sys file प्रणालीs on Linux 2.6 and higher
 * kernels. The driver supports two mechanism to update the BIOS namely
 * contiguous and packetized. Both these methods still require having some
 * application to set the CMOS bit indicating the BIOS to update itself
 * after a reboot.
 *
 * Contiguous method:
 * This driver ग_लिखोs the incoming data in a monolithic image by allocating
 * contiguous physical pages large enough to accommodate the incoming BIOS
 * image size.
 *
 * Packetized method:
 * The driver ग_लिखोs the incoming packet image by allocating a new packet
 * on every समय the packet data is written. This driver requires an
 * application to अवरोध the BIOS image in to fixed sized packet chunks.
 *
 * See Documentation/admin-guide/dell_rbu.rst क्रम more info.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/firmware.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/set_memory.h>

MODULE_AUTHOR("Abhay Salunke <abhay_salunke@dell.com>");
MODULE_DESCRIPTION("Driver for updating BIOS image on DELL systems");
MODULE_LICENSE("GPL");
MODULE_VERSION("3.2");

#घोषणा BIOS_SCAN_LIMIT 0xffffffff
#घोषणा MAX_IMAGE_LENGTH 16
अटल काष्ठा _rbu_data अणु
	व्योम *image_update_buffer;
	अचिन्हित दीर्घ image_update_buffer_size;
	अचिन्हित दीर्घ bios_image_size;
	पूर्णांक image_update_ordernum;
	spinlock_t lock;
	अचिन्हित दीर्घ packet_पढ़ो_count;
	अचिन्हित दीर्घ num_packets;
	अचिन्हित दीर्घ packetsize;
	अचिन्हित दीर्घ imagesize;
	पूर्णांक entry_created;
पूर्ण rbu_data;

अटल अक्षर image_type[MAX_IMAGE_LENGTH + 1] = "mono";
module_param_string(image_type, image_type, माप (image_type), 0);
MODULE_PARM_DESC(image_type, "BIOS image type. choose- mono or packet or init");

अटल अचिन्हित दीर्घ allocation_न्यूनमान = 0x100000;
module_param(allocation_न्यूनमान, uदीर्घ, 0644);
MODULE_PARM_DESC(allocation_न्यूनमान, "Minimum address for allocations when using Packet mode");

काष्ठा packet_data अणु
	काष्ठा list_head list;
	माप_प्रकार length;
	व्योम *data;
	पूर्णांक ordernum;
पूर्ण;

अटल काष्ठा packet_data packet_data_head;

अटल काष्ठा platक्रमm_device *rbu_device;
अटल पूर्णांक context;

अटल व्योम init_packet_head(व्योम)
अणु
	INIT_LIST_HEAD(&packet_data_head.list);
	rbu_data.packet_पढ़ो_count = 0;
	rbu_data.num_packets = 0;
	rbu_data.packetsize = 0;
	rbu_data.imagesize = 0;
पूर्ण

अटल पूर्णांक create_packet(व्योम *data, माप_प्रकार length)
अणु
	काष्ठा packet_data *newpacket;
	पूर्णांक ordernum = 0;
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक packet_array_size = 0;
	व्योम **invalid_addr_packet_array = शून्य;
	व्योम *packet_data_temp_buf = शून्य;
	अचिन्हित पूर्णांक idx = 0;

	pr_debug("entry\n");

	अगर (!rbu_data.packetsize) अणु
		pr_debug("packetsize not specified\n");
		retval = -EINVAL;
		जाओ out_noalloc;
	पूर्ण

	spin_unlock(&rbu_data.lock);

	newpacket = kzalloc(माप (काष्ठा packet_data), GFP_KERNEL);

	अगर (!newpacket) अणु
		pr_warn("failed to allocate new packet\n");
		retval = -ENOMEM;
		spin_lock(&rbu_data.lock);
		जाओ out_noalloc;
	पूर्ण

	ordernum = get_order(length);

	/*
	 * BIOS errata mean we cannot allocate packets below 1MB or they will
	 * be overwritten by BIOS.
	 *
	 * array to temporarily hold packets
	 * that are below the allocation न्यूनमान
	 *
	 * NOTE: very simplistic because we only need the न्यूनमान to be at 1MB
	 *       due to BIOS errata. This shouldn't be used क्रम higher न्यूनमानs
	 *       or you will run out of mem trying to allocate the array.
	 */
	packet_array_size = max_t(अचिन्हित पूर्णांक, allocation_न्यूनमान / rbu_data.packetsize, 1);
	invalid_addr_packet_array = kसुस्मृति(packet_array_size, माप(व्योम *),
						GFP_KERNEL);

	अगर (!invalid_addr_packet_array) अणु
		pr_warn("failed to allocate invalid_addr_packet_array\n");
		retval = -ENOMEM;
		spin_lock(&rbu_data.lock);
		जाओ out_alloc_packet;
	पूर्ण

	जबतक (!packet_data_temp_buf) अणु
		packet_data_temp_buf = (अचिन्हित अक्षर *)
			__get_मुक्त_pages(GFP_KERNEL, ordernum);
		अगर (!packet_data_temp_buf) अणु
			pr_warn("failed to allocate new packet\n");
			retval = -ENOMEM;
			spin_lock(&rbu_data.lock);
			जाओ out_alloc_packet_array;
		पूर्ण

		अगर ((अचिन्हित दीर्घ)virt_to_phys(packet_data_temp_buf)
				< allocation_न्यूनमान) अणु
			pr_debug("packet 0x%lx below floor at 0x%lx\n",
					(अचिन्हित दीर्घ)virt_to_phys(
						packet_data_temp_buf),
					allocation_न्यूनमान);
			invalid_addr_packet_array[idx++] = packet_data_temp_buf;
			packet_data_temp_buf = शून्य;
		पूर्ण
	पूर्ण
	/*
	 * set to uncachable or it may never get written back beक्रमe reboot
	 */
	set_memory_uc((अचिन्हित दीर्घ)packet_data_temp_buf, 1 << ordernum);

	spin_lock(&rbu_data.lock);

	newpacket->data = packet_data_temp_buf;

	pr_debug("newpacket at physical addr %lx\n",
		(अचिन्हित दीर्घ)virt_to_phys(newpacket->data));

	/* packets may not have fixed size */
	newpacket->length = length;
	newpacket->ordernum = ordernum;
	++rbu_data.num_packets;

	/* initialize the newly created packet headers */
	INIT_LIST_HEAD(&newpacket->list);
	list_add_tail(&newpacket->list, &packet_data_head.list);

	स_नकल(newpacket->data, data, length);

	pr_debug("exit\n");

out_alloc_packet_array:
	/* always मुक्त packet array */
	जबतक (idx--) अणु
		pr_debug("freeing unused packet below floor 0x%lx\n",
			(अचिन्हित दीर्घ)virt_to_phys(invalid_addr_packet_array[idx]));
		मुक्त_pages((अचिन्हित दीर्घ)invalid_addr_packet_array[idx], ordernum);
	पूर्ण
	kमुक्त(invalid_addr_packet_array);

out_alloc_packet:
	/* अगर error, मुक्त data */
	अगर (retval)
		kमुक्त(newpacket);

out_noalloc:
	वापस retval;
पूर्ण

अटल पूर्णांक packetize_data(स्थिर u8 *data, माप_प्रकार length)
अणु
	पूर्णांक rc = 0;
	पूर्णांक करोne = 0;
	पूर्णांक packet_length;
	u8 *temp;
	u8 *end = (u8 *) data + length;
	pr_debug("data length %zd\n", length);
	अगर (!rbu_data.packetsize) अणु
		pr_warn("packetsize not specified\n");
		वापस -EIO;
	पूर्ण

	temp = (u8 *) data;

	/* packetize the hunk */
	जबतक (!करोne) अणु
		अगर ((temp + rbu_data.packetsize) < end)
			packet_length = rbu_data.packetsize;
		अन्यथा अणु
			/* this is the last packet */
			packet_length = end - temp;
			करोne = 1;
		पूर्ण

		अगर ((rc = create_packet(temp, packet_length)))
			वापस rc;

		pr_debug("%p:%td\n", temp, (end - temp));
		temp += packet_length;
	पूर्ण

	rbu_data.imagesize = length;

	वापस rc;
पूर्ण

अटल पूर्णांक करो_packet_पढ़ो(अक्षर *data, काष्ठा packet_data *newpacket,
	पूर्णांक length, पूर्णांक bytes_पढ़ो, पूर्णांक *list_पढ़ो_count)
अणु
	व्योम *ptemp_buf;
	पूर्णांक bytes_copied = 0;
	पूर्णांक j = 0;

	*list_पढ़ो_count += newpacket->length;

	अगर (*list_पढ़ो_count > bytes_पढ़ो) अणु
		/* poपूर्णांक to the start of unपढ़ो data */
		j = newpacket->length - (*list_पढ़ो_count - bytes_पढ़ो);
		/* poपूर्णांक to the offset in the packet buffer */
		ptemp_buf = (u8 *) newpacket->data + j;
		/*
		 * check अगर there is enough room in
		 * * the incoming buffer
		 */
		अगर (length > (*list_पढ़ो_count - bytes_पढ़ो))
			/*
			 * copy what ever is there in this
			 * packet and move on
			 */
			bytes_copied = (*list_पढ़ो_count - bytes_पढ़ो);
		अन्यथा
			/* copy the reमुख्यing */
			bytes_copied = length;
		स_नकल(data, ptemp_buf, bytes_copied);
	पूर्ण
	वापस bytes_copied;
पूर्ण

अटल पूर्णांक packet_पढ़ो_list(अक्षर *data, माप_प्रकार * pपढ़ो_length)
अणु
	काष्ठा packet_data *newpacket;
	पूर्णांक temp_count = 0;
	पूर्णांक bytes_copied = 0;
	पूर्णांक bytes_पढ़ो = 0;
	पूर्णांक reमुख्यing_bytes = 0;
	अक्षर *pdest = data;

	/* check अगर we have any packets */
	अगर (0 == rbu_data.num_packets)
		वापस -ENOMEM;

	reमुख्यing_bytes = *pपढ़ो_length;
	bytes_पढ़ो = rbu_data.packet_पढ़ो_count;

	list_क्रम_each_entry(newpacket, (&packet_data_head.list)->next, list) अणु
		bytes_copied = करो_packet_पढ़ो(pdest, newpacket,
			reमुख्यing_bytes, bytes_पढ़ो, &temp_count);
		reमुख्यing_bytes -= bytes_copied;
		bytes_पढ़ो += bytes_copied;
		pdest += bytes_copied;
		/*
		 * check अगर we reached end of buffer beक्रमe reaching the
		 * last packet
		 */
		अगर (reमुख्यing_bytes == 0)
			अवरोध;
	पूर्ण
	/*finally set the bytes पढ़ो */
	*pपढ़ो_length = bytes_पढ़ो - rbu_data.packet_पढ़ो_count;
	rbu_data.packet_पढ़ो_count = bytes_पढ़ो;
	वापस 0;
पूर्ण

अटल व्योम packet_empty_list(व्योम)
अणु
	काष्ठा packet_data *newpacket, *पंचांगp;

	list_क्रम_each_entry_safe(newpacket, पंचांगp, (&packet_data_head.list)->next, list) अणु
		list_del(&newpacket->list);

		/*
		 * zero out the RBU packet memory beक्रमe मुक्तing
		 * to make sure there are no stale RBU packets left in memory
		 */
		स_रखो(newpacket->data, 0, rbu_data.packetsize);
		set_memory_wb((अचिन्हित दीर्घ)newpacket->data,
			1 << newpacket->ordernum);
		मुक्त_pages((अचिन्हित दीर्घ) newpacket->data,
			newpacket->ordernum);
		kमुक्त(newpacket);
	पूर्ण
	rbu_data.packet_पढ़ो_count = 0;
	rbu_data.num_packets = 0;
	rbu_data.imagesize = 0;
पूर्ण

/*
 * img_update_मुक्त: Frees the buffer allocated क्रम storing BIOS image
 * Always called with lock held and वापसed with lock held
 */
अटल व्योम img_update_मुक्त(व्योम)
अणु
	अगर (!rbu_data.image_update_buffer)
		वापस;
	/*
	 * zero out this buffer beक्रमe मुक्तing it to get rid of any stale
	 * BIOS image copied in memory.
	 */
	स_रखो(rbu_data.image_update_buffer, 0,
		rbu_data.image_update_buffer_size);
	मुक्त_pages((अचिन्हित दीर्घ) rbu_data.image_update_buffer,
		rbu_data.image_update_ordernum);

	/*
	 * Re-initialize the rbu_data variables after a मुक्त
	 */
	rbu_data.image_update_ordernum = -1;
	rbu_data.image_update_buffer = शून्य;
	rbu_data.image_update_buffer_size = 0;
	rbu_data.bios_image_size = 0;
पूर्ण

/*
 * img_update_पुनः_स्मृति: This function allocates the contiguous pages to
 * accommodate the requested size of data. The memory address and size
 * values are stored globally and on every call to this function the new
 * size is checked to see अगर more data is required than the existing size.
 * If true the previous memory is मुक्तd and new allocation is करोne to
 * accommodate the new size. If the incoming size is less then than the
 * alपढ़ोy allocated size, then that memory is reused. This function is
 * called with lock held and वापसs with lock held.
 */
अटल पूर्णांक img_update_पुनः_स्मृति(अचिन्हित दीर्घ size)
अणु
	अचिन्हित अक्षर *image_update_buffer = शून्य;
	अचिन्हित दीर्घ img_buf_phys_addr;
	पूर्णांक ordernum;

	/*
	 * check अगर the buffer of sufficient size has been
	 * alपढ़ोy allocated
	 */
	अगर (rbu_data.image_update_buffer_size >= size) अणु
		/*
		 * check क्रम corruption
		 */
		अगर ((size != 0) && (rbu_data.image_update_buffer == शून्य)) अणु
			pr_err("corruption check failed\n");
			वापस -EINVAL;
		पूर्ण
		/*
		 * we have a valid pre-allocated buffer with
		 * sufficient size
		 */
		वापस 0;
	पूर्ण

	/*
	 * मुक्त any previously allocated buffer
	 */
	img_update_मुक्त();

	spin_unlock(&rbu_data.lock);

	ordernum = get_order(size);
	image_update_buffer =
		(अचिन्हित अक्षर *)__get_मुक्त_pages(GFP_DMA32, ordernum);
	spin_lock(&rbu_data.lock);
	अगर (!image_update_buffer) अणु
		pr_debug("Not enough memory for image update: size = %ld\n", size);
		वापस -ENOMEM;
	पूर्ण

	img_buf_phys_addr = (अचिन्हित दीर्घ)virt_to_phys(image_update_buffer);
	अगर (WARN_ON_ONCE(img_buf_phys_addr > BIOS_SCAN_LIMIT))
		वापस -EINVAL; /* can't happen per definition */

	rbu_data.image_update_buffer = image_update_buffer;
	rbu_data.image_update_buffer_size = size;
	rbu_data.bios_image_size = rbu_data.image_update_buffer_size;
	rbu_data.image_update_ordernum = ordernum;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार पढ़ो_packet_data(अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	पूर्णांक retval;
	माप_प्रकार bytes_left;
	माप_प्रकार data_length;
	अक्षर *ptempBuf = buffer;

	/* check to see अगर we have something to वापस */
	अगर (rbu_data.num_packets == 0) अणु
		pr_debug("no packets written\n");
		retval = -ENOMEM;
		जाओ पढ़ो_rbu_data_निकास;
	पूर्ण

	अगर (pos > rbu_data.imagesize) अणु
		retval = 0;
		pr_warn("data underrun\n");
		जाओ पढ़ो_rbu_data_निकास;
	पूर्ण

	bytes_left = rbu_data.imagesize - pos;
	data_length = min(bytes_left, count);

	अगर ((retval = packet_पढ़ो_list(ptempBuf, &data_length)) < 0)
		जाओ पढ़ो_rbu_data_निकास;

	अगर ((pos + count) > rbu_data.imagesize) अणु
		rbu_data.packet_पढ़ो_count = 0;
		/* this was the last copy */
		retval = bytes_left;
	पूर्ण अन्यथा
		retval = count;

      पढ़ो_rbu_data_निकास:
	वापस retval;
पूर्ण

अटल sमाप_प्रकार पढ़ो_rbu_mono_data(अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	/* check to see अगर we have something to वापस */
	अगर ((rbu_data.image_update_buffer == शून्य) ||
		(rbu_data.bios_image_size == 0)) अणु
		pr_debug("image_update_buffer %p, bios_image_size %lu\n",
			rbu_data.image_update_buffer,
			rbu_data.bios_image_size);
		वापस -ENOMEM;
	पूर्ण

	वापस memory_पढ़ो_from_buffer(buffer, count, &pos,
			rbu_data.image_update_buffer, rbu_data.bios_image_size);
पूर्ण

अटल sमाप_प्रकार data_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *bin_attr,
			 अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	sमाप_प्रकार ret_count = 0;

	spin_lock(&rbu_data.lock);

	अगर (!म_भेद(image_type, "mono"))
		ret_count = पढ़ो_rbu_mono_data(buffer, pos, count);
	अन्यथा अगर (!म_भेद(image_type, "packet"))
		ret_count = पढ़ो_packet_data(buffer, pos, count);
	अन्यथा
		pr_debug("invalid image type specified\n");

	spin_unlock(&rbu_data.lock);
	वापस ret_count;
पूर्ण
अटल BIN_ATTR_RO(data, 0);

अटल व्योम callbackfn_rbu(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	rbu_data.entry_created = 0;

	अगर (!fw)
		वापस;

	अगर (!fw->size)
		जाओ out;

	spin_lock(&rbu_data.lock);
	अगर (!म_भेद(image_type, "mono")) अणु
		अगर (!img_update_पुनः_स्मृति(fw->size))
			स_नकल(rbu_data.image_update_buffer,
				fw->data, fw->size);
	पूर्ण अन्यथा अगर (!म_भेद(image_type, "packet")) अणु
		/*
		 * we need to मुक्त previous packets अगर a
		 * new hunk of packets needs to be करोwnloaded
		 */
		packet_empty_list();
		अगर (packetize_data(fw->data, fw->size))
			/* Inहाल something goes wrong when we are
			 * in middle of packetizing the data, we
			 * need to मुक्त up whatever packets might
			 * have been created beक्रमe we quit.
			 */
			packet_empty_list();
	पूर्ण अन्यथा
		pr_debug("invalid image type specified\n");
	spin_unlock(&rbu_data.lock);
 out:
	release_firmware(fw);
पूर्ण

अटल sमाप_प्रकार image_type_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr,
			       अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	पूर्णांक size = 0;
	अगर (!pos)
		size = scnम_लिखो(buffer, count, "%s\n", image_type);
	वापस size;
पूर्ण

अटल sमाप_प्रकार image_type_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	पूर्णांक rc = count;
	पूर्णांक req_firm_rc = 0;
	पूर्णांक i;
	spin_lock(&rbu_data.lock);
	/*
	 * Find the first newline or space
	 */
	क्रम (i = 0; i < count; ++i)
		अगर (buffer[i] == '\n' || buffer[i] == ' ') अणु
			buffer[i] = '\0';
			अवरोध;
		पूर्ण
	अगर (i == count)
		buffer[count] = '\0';

	अगर (म_माला(buffer, "mono"))
		म_नकल(image_type, "mono");
	अन्यथा अगर (म_माला(buffer, "packet"))
		म_नकल(image_type, "packet");
	अन्यथा अगर (म_माला(buffer, "init")) अणु
		/*
		 * If due to the user error the driver माला_लो in a bad
		 * state where even though it is loaded , the
		 * /sys/class/firmware/dell_rbu entries are missing.
		 * to cover this situation the user can recreate entries
		 * by writing init to image_type.
		 */
		अगर (!rbu_data.entry_created) अणु
			spin_unlock(&rbu_data.lock);
			req_firm_rc = request_firmware_noरुको(THIS_MODULE,
				FW_ACTION_NOHOTPLUG, "dell_rbu",
				&rbu_device->dev, GFP_KERNEL, &context,
				callbackfn_rbu);
			अगर (req_firm_rc) अणु
				pr_err("request_firmware_nowait failed %d\n", rc);
				rc = -EIO;
			पूर्ण अन्यथा
				rbu_data.entry_created = 1;

			spin_lock(&rbu_data.lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("image_type is invalid\n");
		spin_unlock(&rbu_data.lock);
		वापस -EINVAL;
	पूर्ण

	/* we must मुक्त all previous allocations */
	packet_empty_list();
	img_update_मुक्त();
	spin_unlock(&rbu_data.lock);

	वापस rc;
पूर्ण
अटल BIN_ATTR_RW(image_type, 0);

अटल sमाप_प्रकार packet_size_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	पूर्णांक size = 0;
	अगर (!pos) अणु
		spin_lock(&rbu_data.lock);
		size = scnम_लिखो(buffer, count, "%lu\n", rbu_data.packetsize);
		spin_unlock(&rbu_data.lock);
	पूर्ण
	वापस size;
पूर्ण

अटल sमाप_प्रकार packet_size_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *bin_attr,
				 अक्षर *buffer, loff_t pos, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ temp;
	spin_lock(&rbu_data.lock);
	packet_empty_list();
	माला_पूछो(buffer, "%lu", &temp);
	अगर (temp < 0xffffffff)
		rbu_data.packetsize = temp;

	spin_unlock(&rbu_data.lock);
	वापस count;
पूर्ण
अटल BIN_ATTR_RW(packet_size, 0);

अटल काष्ठा bin_attribute *rbu_bin_attrs[] = अणु
	&bin_attr_data,
	&bin_attr_image_type,
	&bin_attr_packet_size,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rbu_group = अणु
	.bin_attrs = rbu_bin_attrs,
पूर्ण;

अटल पूर्णांक __init dcdrbu_init(व्योम)
अणु
	पूर्णांक rc;
	spin_lock_init(&rbu_data.lock);

	init_packet_head();
	rbu_device = platक्रमm_device_रेजिस्टर_simple("dell_rbu", -1, शून्य, 0);
	अगर (IS_ERR(rbu_device)) अणु
		pr_err("platform_device_register_simple failed\n");
		वापस PTR_ERR(rbu_device);
	पूर्ण

	rc = sysfs_create_group(&rbu_device->dev.kobj, &rbu_group);
	अगर (rc)
		जाओ out_devreg;

	rbu_data.entry_created = 0;
	वापस 0;

out_devreg:
	platक्रमm_device_unरेजिस्टर(rbu_device);
	वापस rc;
पूर्ण

अटल __निकास व्योम dcdrbu_निकास(व्योम)
अणु
	spin_lock(&rbu_data.lock);
	packet_empty_list();
	img_update_मुक्त();
	spin_unlock(&rbu_data.lock);
	sysfs_हटाओ_group(&rbu_device->dev.kobj, &rbu_group);
	platक्रमm_device_unरेजिस्टर(rbu_device);
पूर्ण

module_निकास(dcdrbu_निकास);
module_init(dcdrbu_init);
