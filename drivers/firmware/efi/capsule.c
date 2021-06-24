<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * EFI capsule support.
 *
 * Copyright 2013 Intel Corporation; author Matt Fleming
 */

#घोषणा pr_fmt(fmt) "efi: " fmt

#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/efi.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/पन.स>

प्रकार काष्ठा अणु
	u64 length;
	u64 data;
पूर्ण efi_capsule_block_desc_t;

अटल bool capsule_pending;
अटल bool stop_capsules;
अटल पूर्णांक efi_reset_type = -1;

/*
 * capsule_mutex serialises access to both capsule_pending and
 * efi_reset_type and stop_capsules.
 */
अटल DEFINE_MUTEX(capsule_mutex);

/**
 * efi_capsule_pending - has a capsule been passed to the firmware?
 * @reset_type: store the type of EFI reset अगर capsule is pending
 *
 * To ensure that the रेजिस्टरed capsule is processed correctly by the
 * firmware we need to perक्रमm a specअगरic type of reset. If a capsule is
 * pending वापस the reset type in @reset_type.
 *
 * This function will race with callers of efi_capsule_update(), क्रम
 * example, calling this function जबतक somebody अन्यथा is in
 * efi_capsule_update() but hasn't reached efi_capsue_update_locked()
 * will miss the updates to capsule_pending and efi_reset_type after
 * efi_capsule_update_locked() completes.
 *
 * A non-racy use is from platक्रमm reboot code because we use
 * प्रणाली_state to ensure no capsules can be sent to the firmware once
 * we're at SYSTEM_RESTART. See efi_capsule_update_locked().
 */
bool efi_capsule_pending(पूर्णांक *reset_type)
अणु
	अगर (!capsule_pending)
		वापस false;

	अगर (reset_type)
		*reset_type = efi_reset_type;

	वापस true;
पूर्ण

/*
 * Whitelist of EFI capsule flags that we support.
 *
 * We करो not handle EFI_CAPSULE_INITIATE_RESET because that would
 * require us to prepare the kernel क्रम reboot. Refuse to load any
 * capsules with that flag and any other flags that we करो not know how
 * to handle.
 */
#घोषणा EFI_CAPSULE_SUPPORTED_FLAG_MASK			\
	(EFI_CAPSULE_PERSIST_ACROSS_RESET | EFI_CAPSULE_POPULATE_SYSTEM_TABLE)

/**
 * efi_capsule_supported - करोes the firmware support the capsule?
 * @guid: venकरोr guid of capsule
 * @flags: capsule flags
 * @size: size of capsule data
 * @reset: the reset type required क्रम this capsule
 *
 * Check whether a capsule with @flags is supported by the firmware
 * and that @size करोesn't exceed the maximum size क्रम a capsule.
 *
 * No attempt is made to check @reset against the reset type required
 * by any pending capsules because of the races involved.
 */
पूर्णांक efi_capsule_supported(efi_guid_t guid, u32 flags, माप_प्रकार size, पूर्णांक *reset)
अणु
	efi_capsule_header_t capsule;
	efi_capsule_header_t *cap_list[] = अणु &capsule पूर्ण;
	efi_status_t status;
	u64 max_size;

	अगर (flags & ~EFI_CAPSULE_SUPPORTED_FLAG_MASK)
		वापस -EINVAL;

	capsule.headersize = capsule.imagesize = माप(capsule);
	स_नकल(&capsule.guid, &guid, माप(efi_guid_t));
	capsule.flags = flags;

	status = efi.query_capsule_caps(cap_list, 1, &max_size, reset);
	अगर (status != EFI_SUCCESS)
		वापस efi_status_to_err(status);

	अगर (size > max_size)
		वापस -ENOSPC;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(efi_capsule_supported);

/*
 * Every scatter gather list (block descriptor) page must end with a
 * continuation poपूर्णांकer. The last continuation poपूर्णांकer of the last
 * page must be zero to mark the end of the chain.
 */
#घोषणा SGLIST_PER_PAGE	((PAGE_SIZE / माप(efi_capsule_block_desc_t)) - 1)

/*
 * How many scatter gather list (block descriptor) pages करो we need
 * to map @count pages?
 */
अटल अंतरभूत अचिन्हित पूर्णांक sg_pages_num(अचिन्हित पूर्णांक count)
अणु
	वापस DIV_ROUND_UP(count, SGLIST_PER_PAGE);
पूर्ण

/**
 * efi_capsule_update_locked - pass a single capsule to the firmware
 * @capsule: capsule to send to the firmware
 * @sg_pages: array of scatter gather (block descriptor) pages
 * @reset: the reset type required क्रम @capsule
 *
 * Since this function must be called under capsule_mutex check
 * whether efi_reset_type will conflict with @reset, and atomically
 * set it and capsule_pending अगर a capsule was successfully sent to
 * the firmware.
 *
 * We also check to see अगर the प्रणाली is about to restart, and अगर so,
 * पात. This aव्योमs races between efi_capsule_update() and
 * efi_capsule_pending().
 */
अटल पूर्णांक
efi_capsule_update_locked(efi_capsule_header_t *capsule,
			  काष्ठा page **sg_pages, पूर्णांक reset)
अणु
	efi_physical_addr_t sglist_phys;
	efi_status_t status;

	lockdep_निश्चित_held(&capsule_mutex);

	/*
	 * If someone has alपढ़ोy रेजिस्टरed a capsule that requires a
	 * dअगरferent reset type, we're out of luck and must पात.
	 */
	अगर (efi_reset_type >= 0 && efi_reset_type != reset) अणु
		pr_err("Conflicting capsule reset type %d (%d).\n",
		       reset, efi_reset_type);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If the प्रणाली is getting पढ़ोy to restart it may have
	 * called efi_capsule_pending() to make decisions (such as
	 * whether to क्रमce an EFI reboot), and we're racing against
	 * that call. Abort in that हाल.
	 */
	अगर (unlikely(stop_capsules)) अणु
		pr_warn("Capsule update raced with reboot, aborting.\n");
		वापस -EINVAL;
	पूर्ण

	sglist_phys = page_to_phys(sg_pages[0]);

	status = efi.update_capsule(&capsule, 1, sglist_phys);
	अगर (status == EFI_SUCCESS) अणु
		capsule_pending = true;
		efi_reset_type = reset;
	पूर्ण

	वापस efi_status_to_err(status);
पूर्ण

/**
 * efi_capsule_update - send a capsule to the firmware
 * @capsule: capsule to send to firmware
 * @pages: an array of capsule data pages
 *
 * Build a scatter gather list with EFI capsule block descriptors to
 * map the capsule described by @capsule with its data in @pages and
 * send it to the firmware via the UpdateCapsule() runसमय service.
 *
 * @capsule must be a भव mapping of the complete capsule update in the
 * kernel address space, as the capsule can be consumed immediately.
 * A capsule_header_t that describes the entire contents of the capsule
 * must be at the start of the first data page.
 *
 * Even though this function will validate that the firmware supports
 * the capsule guid, users will likely want to check that
 * efi_capsule_supported() वापसs true beक्रमe calling this function
 * because it makes it easier to prपूर्णांक helpful error messages.
 *
 * If the capsule is successfully submitted to the firmware, any
 * subsequent calls to efi_capsule_pending() will वापस true. @pages
 * must not be released or modअगरied अगर this function वापसs
 * successfully.
 *
 * Callers must be prepared क्रम this function to fail, which can
 * happen अगर we raced with प्रणाली reboot or अगर there is alपढ़ोy a
 * pending capsule that has a reset type that conflicts with the one
 * required by @capsule. Do NOT use efi_capsule_pending() to detect
 * this conflict since that would be racy. Instead, submit the capsule
 * to efi_capsule_update() and check the वापस value.
 *
 * Return 0 on success, a converted EFI status code on failure.
 */
पूर्णांक efi_capsule_update(efi_capsule_header_t *capsule, phys_addr_t *pages)
अणु
	u32 imagesize = capsule->imagesize;
	efi_guid_t guid = capsule->guid;
	अचिन्हित पूर्णांक count, sg_count;
	u32 flags = capsule->flags;
	काष्ठा page **sg_pages;
	पूर्णांक rv, reset_type;
	पूर्णांक i, j;

	rv = efi_capsule_supported(guid, flags, imagesize, &reset_type);
	अगर (rv)
		वापस rv;

	count = DIV_ROUND_UP(imagesize, PAGE_SIZE);
	sg_count = sg_pages_num(count);

	sg_pages = kसुस्मृति(sg_count, माप(*sg_pages), GFP_KERNEL);
	अगर (!sg_pages)
		वापस -ENOMEM;

	क्रम (i = 0; i < sg_count; i++) अणु
		sg_pages[i] = alloc_page(GFP_KERNEL);
		अगर (!sg_pages[i]) अणु
			rv = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < sg_count; i++) अणु
		efi_capsule_block_desc_t *sglist;

		sglist = kmap_atomic(sg_pages[i]);

		क्रम (j = 0; j < SGLIST_PER_PAGE && count > 0; j++) अणु
			u64 sz = min_t(u64, imagesize,
				       PAGE_SIZE - (u64)*pages % PAGE_SIZE);

			sglist[j].length = sz;
			sglist[j].data = *pages++;

			imagesize -= sz;
			count--;
		पूर्ण

		/* Continuation poपूर्णांकer */
		sglist[j].length = 0;

		अगर (i + 1 == sg_count)
			sglist[j].data = 0;
		अन्यथा
			sglist[j].data = page_to_phys(sg_pages[i + 1]);

#अगर defined(CONFIG_ARM) || defined(CONFIG_ARM64)
		/*
		 * At runसमय, the firmware has no way to find out where the
		 * sglist elements are mapped, अगर they are mapped in the first
		 * place. Thereक्रमe, on architectures that can only perक्रमm
		 * cache मुख्यtenance by भव address, the firmware is unable
		 * to perक्रमm this मुख्यtenance, and so it is up to the OS to करो
		 * it instead.
		 */
		efi_capsule_flush_cache_range(sglist, PAGE_SIZE);
#पूर्ण_अगर
		kunmap_atomic(sglist);
	पूर्ण

	mutex_lock(&capsule_mutex);
	rv = efi_capsule_update_locked(capsule, sg_pages, reset_type);
	mutex_unlock(&capsule_mutex);

out:
	क्रम (i = 0; rv && i < sg_count; i++) अणु
		अगर (sg_pages[i])
			__मुक्त_page(sg_pages[i]);
	पूर्ण

	kमुक्त(sg_pages);
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(efi_capsule_update);

अटल पूर्णांक capsule_reboot_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *cmd)
अणु
	mutex_lock(&capsule_mutex);
	stop_capsules = true;
	mutex_unlock(&capsule_mutex);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block capsule_reboot_nb = अणु
	.notअगरier_call = capsule_reboot_notअगरy,
पूर्ण;

अटल पूर्णांक __init capsule_reboot_रेजिस्टर(व्योम)
अणु
	वापस रेजिस्टर_reboot_notअगरier(&capsule_reboot_nb);
पूर्ण
core_initcall(capsule_reboot_रेजिस्टर);
