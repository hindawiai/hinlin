<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * EFI capsule loader driver.
 *
 * Copyright 2015 Intel Corporation
 */

#घोषणा pr_fmt(fmt) "efi: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/efi.h>
#समावेश <linux/vदो_स्मृति.h>

#घोषणा NO_FURTHER_WRITE_ACTION -1

/**
 * efi_मुक्त_all_buff_pages - मुक्त all previous allocated buffer pages
 * @cap_info: poपूर्णांकer to current instance of capsule_info काष्ठाure
 *
 *	In addition to मुक्तing buffer pages, it flags NO_FURTHER_WRITE_ACTION
 *	to cease processing data in subsequent ग_लिखो(2) calls until बंद(2)
 *	is called.
 **/
अटल व्योम efi_मुक्त_all_buff_pages(काष्ठा capsule_info *cap_info)
अणु
	जबतक (cap_info->index > 0)
		__मुक्त_page(cap_info->pages[--cap_info->index]);

	cap_info->index = NO_FURTHER_WRITE_ACTION;
पूर्ण

पूर्णांक __efi_capsule_setup_info(काष्ठा capsule_info *cap_info)
अणु
	माप_प्रकार pages_needed;
	पूर्णांक ret;
	व्योम *temp_page;

	pages_needed = ALIGN(cap_info->total_size, PAGE_SIZE) / PAGE_SIZE;

	अगर (pages_needed == 0) अणु
		pr_err("invalid capsule size\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर the capsule binary supported */
	ret = efi_capsule_supported(cap_info->header.guid,
				    cap_info->header.flags,
				    cap_info->header.imagesize,
				    &cap_info->reset_type);
	अगर (ret) अणु
		pr_err("capsule not supported\n");
		वापस ret;
	पूर्ण

	temp_page = kपुनः_स्मृति(cap_info->pages,
			     pages_needed * माप(व्योम *),
			     GFP_KERNEL | __GFP_ZERO);
	अगर (!temp_page)
		वापस -ENOMEM;

	cap_info->pages = temp_page;

	temp_page = kपुनः_स्मृति(cap_info->phys,
			     pages_needed * माप(phys_addr_t *),
			     GFP_KERNEL | __GFP_ZERO);
	अगर (!temp_page)
		वापस -ENOMEM;

	cap_info->phys = temp_page;

	वापस 0;
पूर्ण

/**
 * efi_capsule_setup_info - obtain the efi capsule header in the binary and
 *			    setup capsule_info काष्ठाure
 * @cap_info: poपूर्णांकer to current instance of capsule_info काष्ठाure
 * @kbuff: a mapped first page buffer poपूर्णांकer
 * @hdr_bytes: the total received number of bytes क्रम efi header
 *
 * Platक्रमms with non-standard capsule update mechanisms can override
 * this __weak function so they can perक्रमm any required capsule
 * image munging. See quark_quirk_function() क्रम an example.
 **/
पूर्णांक __weak efi_capsule_setup_info(काष्ठा capsule_info *cap_info, व्योम *kbuff,
				  माप_प्रकार hdr_bytes)
अणु
	/* Only process data block that is larger than efi header size */
	अगर (hdr_bytes < माप(efi_capsule_header_t))
		वापस 0;

	स_नकल(&cap_info->header, kbuff, माप(cap_info->header));
	cap_info->total_size = cap_info->header.imagesize;

	वापस __efi_capsule_setup_info(cap_info);
पूर्ण

/**
 * efi_capsule_submit_update - invoke the efi_capsule_update API once binary
 *			       upload करोne
 * @cap_info: poपूर्णांकer to current instance of capsule_info काष्ठाure
 **/
अटल sमाप_प्रकार efi_capsule_submit_update(काष्ठा capsule_info *cap_info)
अणु
	bool करो_vunmap = false;
	पूर्णांक ret;

	/*
	 * cap_info->capsule may have been asचिन्हित alपढ़ोy by a quirk
	 * handler, so only overग_लिखो it अगर it is शून्य
	 */
	अगर (!cap_info->capsule) अणु
		cap_info->capsule = vmap(cap_info->pages, cap_info->index,
					 VM_MAP, PAGE_KERNEL);
		अगर (!cap_info->capsule)
			वापस -ENOMEM;
		करो_vunmap = true;
	पूर्ण

	ret = efi_capsule_update(cap_info->capsule, cap_info->phys);
	अगर (करो_vunmap)
		vunmap(cap_info->capsule);
	अगर (ret) अणु
		pr_err("capsule update failed\n");
		वापस ret;
	पूर्ण

	/* Indicate capsule binary uploading is करोne */
	cap_info->index = NO_FURTHER_WRITE_ACTION;

	अगर (cap_info->header.flags & EFI_CAPSULE_PERSIST_ACROSS_RESET) अणु
		pr_info("Successfully uploaded capsule file with reboot type '%s'\n",
			!cap_info->reset_type ? "RESET_COLD" :
			cap_info->reset_type == 1 ? "RESET_WARM" :
			"RESET_SHUTDOWN");
	पूर्ण अन्यथा अणु
		pr_info("Successfully processed capsule file\n");
	पूर्ण

	वापस 0;
पूर्ण

/**
 * efi_capsule_ग_लिखो - store the capsule binary and pass it to
 *		       efi_capsule_update() API
 * @file: file poपूर्णांकer
 * @buff: buffer poपूर्णांकer
 * @count: number of bytes in @buff
 * @offp: not used
 *
 *	Expectation:
 *	- A user space tool should start at the beginning of capsule binary and
 *	  pass data in sequentially.
 *	- Users should बंद and re-खोलो this file note in order to upload more
 *	  capsules.
 *	- After an error वापसed, user should बंद the file and restart the
 *	  operation क्रम the next try otherwise -EIO will be वापसed until the
 *	  file is बंदd.
 *	- An EFI capsule header must be located at the beginning of capsule
 *	  binary file and passed in as first block data of ग_लिखो operation.
 **/
अटल sमाप_प्रकार efi_capsule_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buff,
				 माप_प्रकार count, loff_t *offp)
अणु
	पूर्णांक ret;
	काष्ठा capsule_info *cap_info = file->निजी_data;
	काष्ठा page *page;
	व्योम *kbuff = शून्य;
	माप_प्रकार ग_लिखो_byte;

	अगर (count == 0)
		वापस 0;

	/* Return error जबतक NO_FURTHER_WRITE_ACTION is flagged */
	अगर (cap_info->index < 0)
		वापस -EIO;

	/* Only alloc a new page when previous page is full */
	अगर (!cap_info->page_bytes_reमुख्य) अणु
		page = alloc_page(GFP_KERNEL);
		अगर (!page) अणु
			ret = -ENOMEM;
			जाओ failed;
		पूर्ण

		cap_info->pages[cap_info->index] = page;
		cap_info->phys[cap_info->index] = page_to_phys(page);
		cap_info->page_bytes_reमुख्य = PAGE_SIZE;
		cap_info->index++;
	पूर्ण अन्यथा अणु
		page = cap_info->pages[cap_info->index - 1];
	पूर्ण

	kbuff = kmap(page);
	kbuff += PAGE_SIZE - cap_info->page_bytes_reमुख्य;

	/* Copy capsule binary data from user space to kernel space buffer */
	ग_लिखो_byte = min_t(माप_प्रकार, count, cap_info->page_bytes_reमुख्य);
	अगर (copy_from_user(kbuff, buff, ग_लिखो_byte)) अणु
		ret = -EFAULT;
		जाओ fail_unmap;
	पूर्ण
	cap_info->page_bytes_reमुख्य -= ग_लिखो_byte;

	/* Setup capsule binary info काष्ठाure */
	अगर (cap_info->header.headersize == 0) अणु
		ret = efi_capsule_setup_info(cap_info, kbuff - cap_info->count,
					     cap_info->count + ग_लिखो_byte);
		अगर (ret)
			जाओ fail_unmap;
	पूर्ण

	cap_info->count += ग_लिखो_byte;
	kunmap(page);

	/* Submit the full binary to efi_capsule_update() API */
	अगर (cap_info->header.headersize > 0 &&
	    cap_info->count >= cap_info->total_size) अणु
		अगर (cap_info->count > cap_info->total_size) अणु
			pr_err("capsule upload size exceeded header defined size\n");
			ret = -EINVAL;
			जाओ failed;
		पूर्ण

		ret = efi_capsule_submit_update(cap_info);
		अगर (ret)
			जाओ failed;
	पूर्ण

	वापस ग_लिखो_byte;

fail_unmap:
	kunmap(page);
failed:
	efi_मुक्त_all_buff_pages(cap_info);
	वापस ret;
पूर्ण

/**
 * efi_capsule_flush - called by file बंद or file flush
 * @file: file poपूर्णांकer
 * @id: not used
 *
 *	If a capsule is being partially uploaded then calling this function
 *	will be treated as upload termination and will मुक्त those completed
 *	buffer pages and -ECANCELED will be वापसed.
 **/
अटल पूर्णांक efi_capsule_flush(काष्ठा file *file, fl_owner_t id)
अणु
	पूर्णांक ret = 0;
	काष्ठा capsule_info *cap_info = file->निजी_data;

	अगर (cap_info->index > 0) अणु
		pr_err("capsule upload not complete\n");
		efi_मुक्त_all_buff_pages(cap_info);
		ret = -ECANCELED;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * efi_capsule_release - called by file बंद
 * @inode: not used
 * @file: file poपूर्णांकer
 *
 *	We will not मुक्त successfully submitted pages since efi update
 *	requires data to be मुख्यtained across प्रणाली reboot.
 **/
अटल पूर्णांक efi_capsule_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा capsule_info *cap_info = file->निजी_data;

	kमुक्त(cap_info->pages);
	kमुक्त(cap_info->phys);
	kमुक्त(file->निजी_data);
	file->निजी_data = शून्य;
	वापस 0;
पूर्ण

/**
 * efi_capsule_खोलो - called by file खोलो
 * @inode: not used
 * @file: file poपूर्णांकer
 *
 *	Will allocate each capsule_info memory क्रम each file खोलो call.
 *	This provided the capability to support multiple file खोलो feature
 *	where user is not needed to रुको क्रम others to finish in order to
 *	upload their capsule binary.
 **/
अटल पूर्णांक efi_capsule_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा capsule_info *cap_info;

	cap_info = kzalloc(माप(*cap_info), GFP_KERNEL);
	अगर (!cap_info)
		वापस -ENOMEM;

	cap_info->pages = kzalloc(माप(व्योम *), GFP_KERNEL);
	अगर (!cap_info->pages) अणु
		kमुक्त(cap_info);
		वापस -ENOMEM;
	पूर्ण

	cap_info->phys = kzalloc(माप(व्योम *), GFP_KERNEL);
	अगर (!cap_info->phys) अणु
		kमुक्त(cap_info->pages);
		kमुक्त(cap_info);
		वापस -ENOMEM;
	पूर्ण

	file->निजी_data = cap_info;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations efi_capsule_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = efi_capsule_खोलो,
	.ग_लिखो = efi_capsule_ग_लिखो,
	.flush = efi_capsule_flush,
	.release = efi_capsule_release,
	.llseek = no_llseek,
पूर्ण;

अटल काष्ठा miscdevice efi_capsule_misc = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "efi_capsule_loader",
	.fops = &efi_capsule_fops,
पूर्ण;

अटल पूर्णांक __init efi_capsule_loader_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!efi_enabled(EFI_RUNTIME_SERVICES))
		वापस -ENODEV;

	ret = misc_रेजिस्टर(&efi_capsule_misc);
	अगर (ret)
		pr_err("Unable to register capsule loader device\n");

	वापस ret;
पूर्ण
module_init(efi_capsule_loader_init);

अटल व्योम __निकास efi_capsule_loader_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&efi_capsule_misc);
पूर्ण
module_निकास(efi_capsule_loader_निकास);

MODULE_DESCRIPTION("EFI capsule firmware binary loader");
MODULE_LICENSE("GPL v2");
