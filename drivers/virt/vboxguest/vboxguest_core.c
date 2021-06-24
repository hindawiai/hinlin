<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR CDDL-1.0) */
/*
 * vboxguest core guest-device handling code, VBoxGuest.cpp in upstream svn.
 *
 * Copyright (C) 2007-2016 Oracle Corporation
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/vbox_err.h>
#समावेश <linux/vbox_utils.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "vboxguest_core.h"
#समावेश "vboxguest_version.h"

/* Get the poपूर्णांकer to the first HGCM parameter. */
#घोषणा VBG_IOCTL_HGCM_CALL_PARMS(a) \
	((काष्ठा vmmdev_hgcm_function_parameter *)( \
		(u8 *)(a) + माप(काष्ठा vbg_ioctl_hgcm_call)))
/* Get the poपूर्णांकer to the first HGCM parameter in a 32-bit request. */
#घोषणा VBG_IOCTL_HGCM_CALL_PARMS32(a) \
	((काष्ठा vmmdev_hgcm_function_parameter32 *)( \
		(u8 *)(a) + माप(काष्ठा vbg_ioctl_hgcm_call)))

#घोषणा GUEST_MAPPINGS_TRIES	5

#घोषणा VBG_KERNEL_REQUEST \
	(VMMDEV_REQUESTOR_KERNEL | VMMDEV_REQUESTOR_USR_DRV | \
	 VMMDEV_REQUESTOR_CON_DONT_KNOW | VMMDEV_REQUESTOR_TRUST_NOT_GIVEN)

/**
 * Reserves memory in which the VMM can relocate any guest mappings
 * that are भग्नing around.
 *
 * This operation is a little bit tricky since the VMM might not accept
 * just any address because of address clashes between the three contexts
 * it operates in, so we try several बार.
 *
 * Failure to reserve the guest mappings is ignored.
 *
 * @gdev:		The Guest extension device.
 */
अटल व्योम vbg_guest_mappings_init(काष्ठा vbg_dev *gdev)
अणु
	काष्ठा vmmdev_hypervisorinfo *req;
	व्योम *guest_mappings[GUEST_MAPPINGS_TRIES];
	काष्ठा page **pages = शून्य;
	u32 size, hypervisor_size;
	पूर्णांक i, rc;

	/* Query the required space. */
	req = vbg_req_alloc(माप(*req), VMMDEVREQ_GET_HYPERVISOR_INFO,
			    VBG_KERNEL_REQUEST);
	अगर (!req)
		वापस;

	req->hypervisor_start = 0;
	req->hypervisor_size = 0;
	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0)
		जाओ out;

	/*
	 * The VMM will report back अगर there is nothing it wants to map, like
	 * क्रम instance in VT-x and AMD-V mode.
	 */
	अगर (req->hypervisor_size == 0)
		जाओ out;

	hypervisor_size = req->hypervisor_size;
	/* Add 4M so that we can align the vmap to 4MiB as the host requires. */
	size = PAGE_ALIGN(req->hypervisor_size) + SZ_4M;

	pages = kदो_स्मृति_array(size >> PAGE_SHIFT, माप(*pages), GFP_KERNEL);
	अगर (!pages)
		जाओ out;

	gdev->guest_mappings_dummy_page = alloc_page(GFP_HIGHUSER);
	अगर (!gdev->guest_mappings_dummy_page)
		जाओ out;

	क्रम (i = 0; i < (size >> PAGE_SHIFT); i++)
		pages[i] = gdev->guest_mappings_dummy_page;

	/*
	 * Try several बार, the VMM might not accept some addresses because
	 * of address clashes between the three contexts.
	 */
	क्रम (i = 0; i < GUEST_MAPPINGS_TRIES; i++) अणु
		guest_mappings[i] = vmap(pages, (size >> PAGE_SHIFT),
					 VM_MAP, PAGE_KERNEL_RO);
		अगर (!guest_mappings[i])
			अवरोध;

		req->header.request_type = VMMDEVREQ_SET_HYPERVISOR_INFO;
		req->header.rc = VERR_INTERNAL_ERROR;
		req->hypervisor_size = hypervisor_size;
		req->hypervisor_start =
			(अचिन्हित दीर्घ)PTR_ALIGN(guest_mappings[i], SZ_4M);

		rc = vbg_req_perक्रमm(gdev, req);
		अगर (rc >= 0) अणु
			gdev->guest_mappings = guest_mappings[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/* Free vmap's from failed attempts. */
	जबतक (--i >= 0)
		vunmap(guest_mappings[i]);

	/* On failure मुक्त the dummy-page backing the vmap */
	अगर (!gdev->guest_mappings) अणु
		__मुक्त_page(gdev->guest_mappings_dummy_page);
		gdev->guest_mappings_dummy_page = शून्य;
	पूर्ण

out:
	vbg_req_मुक्त(req, माप(*req));
	kमुक्त(pages);
पूर्ण

/**
 * Unकरो what vbg_guest_mappings_init did.
 *
 * @gdev:		The Guest extension device.
 */
अटल व्योम vbg_guest_mappings_निकास(काष्ठा vbg_dev *gdev)
अणु
	काष्ठा vmmdev_hypervisorinfo *req;
	पूर्णांक rc;

	अगर (!gdev->guest_mappings)
		वापस;

	/*
	 * Tell the host that we're going to मुक्त the memory we reserved क्रम
	 * it, the मुक्त it up. (Leak the memory अगर anything goes wrong here.)
	 */
	req = vbg_req_alloc(माप(*req), VMMDEVREQ_SET_HYPERVISOR_INFO,
			    VBG_KERNEL_REQUEST);
	अगर (!req)
		वापस;

	req->hypervisor_start = 0;
	req->hypervisor_size = 0;

	rc = vbg_req_perक्रमm(gdev, req);

	vbg_req_मुक्त(req, माप(*req));

	अगर (rc < 0) अणु
		vbg_err("%s error: %d\n", __func__, rc);
		वापस;
	पूर्ण

	vunmap(gdev->guest_mappings);
	gdev->guest_mappings = शून्य;

	__मुक्त_page(gdev->guest_mappings_dummy_page);
	gdev->guest_mappings_dummy_page = शून्य;
पूर्ण

/**
 * Report the guest inक्रमmation to the host.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 */
अटल पूर्णांक vbg_report_guest_info(काष्ठा vbg_dev *gdev)
अणु
	/*
	 * Allocate and fill in the two guest info reports.
	 */
	काष्ठा vmmdev_guest_info *req1 = शून्य;
	काष्ठा vmmdev_guest_info2 *req2 = शून्य;
	पूर्णांक rc, ret = -ENOMEM;

	req1 = vbg_req_alloc(माप(*req1), VMMDEVREQ_REPORT_GUEST_INFO,
			     VBG_KERNEL_REQUEST);
	req2 = vbg_req_alloc(माप(*req2), VMMDEVREQ_REPORT_GUEST_INFO2,
			     VBG_KERNEL_REQUEST);
	अगर (!req1 || !req2)
		जाओ out_मुक्त;

	req1->पूर्णांकerface_version = VMMDEV_VERSION;
	req1->os_type = VMMDEV_OSTYPE_LINUX26;
#अगर __BITS_PER_LONG == 64
	req1->os_type |= VMMDEV_OSTYPE_X64;
#पूर्ण_अगर

	req2->additions_major = VBG_VERSION_MAJOR;
	req2->additions_minor = VBG_VERSION_MINOR;
	req2->additions_build = VBG_VERSION_BUILD;
	req2->additions_revision = VBG_SVN_REV;
	req2->additions_features =
		VMMDEV_GUEST_INFO2_ADDITIONS_FEATURES_REQUESTOR_INFO;
	strlcpy(req2->name, VBG_VERSION_STRING,
		माप(req2->name));

	/*
	 * There are two protocols here:
	 *      1. INFO2 + INFO1. Supported by >=3.2.51.
	 *      2. INFO1 and optionally INFO2. The old protocol.
	 *
	 * We try protocol 2 first.  It will fail with VERR_NOT_SUPPORTED
	 * अगर not supported by the VMMDev (message ordering requirement).
	 */
	rc = vbg_req_perक्रमm(gdev, req2);
	अगर (rc >= 0) अणु
		rc = vbg_req_perक्रमm(gdev, req1);
	पूर्ण अन्यथा अगर (rc == VERR_NOT_SUPPORTED || rc == VERR_NOT_IMPLEMENTED) अणु
		rc = vbg_req_perक्रमm(gdev, req1);
		अगर (rc >= 0) अणु
			rc = vbg_req_perक्रमm(gdev, req2);
			अगर (rc == VERR_NOT_IMPLEMENTED)
				rc = VINF_SUCCESS;
		पूर्ण
	पूर्ण
	ret = vbg_status_code_to_त्रुटि_सं(rc);

out_मुक्त:
	vbg_req_मुक्त(req2, माप(*req2));
	vbg_req_मुक्त(req1, माप(*req1));
	वापस ret;
पूर्ण

/**
 * Report the guest driver status to the host.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 * @active:		Flag whether the driver is now active or not.
 */
अटल पूर्णांक vbg_report_driver_status(काष्ठा vbg_dev *gdev, bool active)
अणु
	काष्ठा vmmdev_guest_status *req;
	पूर्णांक rc;

	req = vbg_req_alloc(माप(*req), VMMDEVREQ_REPORT_GUEST_STATUS,
			    VBG_KERNEL_REQUEST);
	अगर (!req)
		वापस -ENOMEM;

	req->facility = VBOXGUEST_FACILITY_TYPE_VBOXGUEST_DRIVER;
	अगर (active)
		req->status = VBOXGUEST_FACILITY_STATUS_ACTIVE;
	अन्यथा
		req->status = VBOXGUEST_FACILITY_STATUS_INACTIVE;
	req->flags = 0;

	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc == VERR_NOT_IMPLEMENTED)	/* Compatibility with older hosts. */
		rc = VINF_SUCCESS;

	vbg_req_मुक्त(req, माप(*req));

	वापस vbg_status_code_to_त्रुटि_सं(rc);
पूर्ण

/**
 * Inflate the balloon by one chunk. The caller owns the balloon mutex.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 * @chunk_idx:		Index of the chunk.
 */
अटल पूर्णांक vbg_balloon_inflate(काष्ठा vbg_dev *gdev, u32 chunk_idx)
अणु
	काष्ठा vmmdev_memballoon_change *req = gdev->mem_balloon.change_req;
	काष्ठा page **pages;
	पूर्णांक i, rc, ret;

	pages = kदो_स्मृति_array(VMMDEV_MEMORY_BALLOON_CHUNK_PAGES,
			      माप(*pages),
			      GFP_KERNEL | __GFP_NOWARN);
	अगर (!pages)
		वापस -ENOMEM;

	req->header.size = माप(*req);
	req->inflate = true;
	req->pages = VMMDEV_MEMORY_BALLOON_CHUNK_PAGES;

	क्रम (i = 0; i < VMMDEV_MEMORY_BALLOON_CHUNK_PAGES; i++) अणु
		pages[i] = alloc_page(GFP_KERNEL | __GFP_NOWARN);
		अगर (!pages[i]) अणु
			ret = -ENOMEM;
			जाओ out_error;
		पूर्ण

		req->phys_page[i] = page_to_phys(pages[i]);
	पूर्ण

	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0) अणु
		vbg_err("%s error, rc: %d\n", __func__, rc);
		ret = vbg_status_code_to_त्रुटि_सं(rc);
		जाओ out_error;
	पूर्ण

	gdev->mem_balloon.pages[chunk_idx] = pages;

	वापस 0;

out_error:
	जबतक (--i >= 0)
		__मुक्त_page(pages[i]);
	kमुक्त(pages);

	वापस ret;
पूर्ण

/**
 * Deflate the balloon by one chunk. The caller owns the balloon mutex.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 * @chunk_idx:		Index of the chunk.
 */
अटल पूर्णांक vbg_balloon_deflate(काष्ठा vbg_dev *gdev, u32 chunk_idx)
अणु
	काष्ठा vmmdev_memballoon_change *req = gdev->mem_balloon.change_req;
	काष्ठा page **pages = gdev->mem_balloon.pages[chunk_idx];
	पूर्णांक i, rc;

	req->header.size = माप(*req);
	req->inflate = false;
	req->pages = VMMDEV_MEMORY_BALLOON_CHUNK_PAGES;

	क्रम (i = 0; i < VMMDEV_MEMORY_BALLOON_CHUNK_PAGES; i++)
		req->phys_page[i] = page_to_phys(pages[i]);

	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0) अणु
		vbg_err("%s error, rc: %d\n", __func__, rc);
		वापस vbg_status_code_to_त्रुटि_सं(rc);
	पूर्ण

	क्रम (i = 0; i < VMMDEV_MEMORY_BALLOON_CHUNK_PAGES; i++)
		__मुक्त_page(pages[i]);
	kमुक्त(pages);
	gdev->mem_balloon.pages[chunk_idx] = शून्य;

	वापस 0;
पूर्ण

/**
 * Respond to VMMDEV_EVENT_BALLOON_CHANGE_REQUEST events, query the size
 * the host wants the balloon to be and adjust accordingly.
 */
अटल व्योम vbg_balloon_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vbg_dev *gdev =
		container_of(work, काष्ठा vbg_dev, mem_balloon.work);
	काष्ठा vmmdev_memballoon_info *req = gdev->mem_balloon.get_req;
	u32 i, chunks;
	पूर्णांक rc, ret;

	/*
	 * Setting this bit means that we request the value from the host and
	 * change the guest memory balloon according to the वापसed value.
	 */
	req->event_ack = VMMDEV_EVENT_BALLOON_CHANGE_REQUEST;
	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0) अणु
		vbg_err("%s error, rc: %d)\n", __func__, rc);
		वापस;
	पूर्ण

	/*
	 * The host always वापसs the same maximum amount of chunks, so
	 * we करो this once.
	 */
	अगर (!gdev->mem_balloon.max_chunks) अणु
		gdev->mem_balloon.pages =
			devm_kसुस्मृति(gdev->dev, req->phys_mem_chunks,
				     माप(काष्ठा page **), GFP_KERNEL);
		अगर (!gdev->mem_balloon.pages)
			वापस;

		gdev->mem_balloon.max_chunks = req->phys_mem_chunks;
	पूर्ण

	chunks = req->balloon_chunks;
	अगर (chunks > gdev->mem_balloon.max_chunks) अणु
		vbg_err("%s: illegal balloon size %u (max=%u)\n",
			__func__, chunks, gdev->mem_balloon.max_chunks);
		वापस;
	पूर्ण

	अगर (chunks > gdev->mem_balloon.chunks) अणु
		/* inflate */
		क्रम (i = gdev->mem_balloon.chunks; i < chunks; i++) अणु
			ret = vbg_balloon_inflate(gdev, i);
			अगर (ret < 0)
				वापस;

			gdev->mem_balloon.chunks++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* deflate */
		क्रम (i = gdev->mem_balloon.chunks; i-- > chunks;) अणु
			ret = vbg_balloon_deflate(gdev, i);
			अगर (ret < 0)
				वापस;

			gdev->mem_balloon.chunks--;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * Callback क्रम heartbeat समयr.
 */
अटल व्योम vbg_heartbeat_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा vbg_dev *gdev = from_समयr(gdev, t, heartbeat_समयr);

	vbg_req_perक्रमm(gdev, gdev->guest_heartbeat_req);
	mod_समयr(&gdev->heartbeat_समयr,
		  msecs_to_jअगरfies(gdev->heartbeat_पूर्णांकerval_ms));
पूर्ण

/**
 * Configure the host to check guest's heartbeat
 * and get heartbeat पूर्णांकerval from the host.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 * @enabled:		Set true to enable guest heartbeat checks on host.
 */
अटल पूर्णांक vbg_heartbeat_host_config(काष्ठा vbg_dev *gdev, bool enabled)
अणु
	काष्ठा vmmdev_heartbeat *req;
	पूर्णांक rc;

	req = vbg_req_alloc(माप(*req), VMMDEVREQ_HEARTBEAT_CONFIGURE,
			    VBG_KERNEL_REQUEST);
	अगर (!req)
		वापस -ENOMEM;

	req->enabled = enabled;
	req->पूर्णांकerval_ns = 0;
	rc = vbg_req_perक्रमm(gdev, req);
	करो_भाग(req->पूर्णांकerval_ns, 1000000); /* ns -> ms */
	gdev->heartbeat_पूर्णांकerval_ms = req->पूर्णांकerval_ns;
	vbg_req_मुक्त(req, माप(*req));

	वापस vbg_status_code_to_त्रुटि_सं(rc);
पूर्ण

/**
 * Initializes the heartbeat समयr. This feature may be disabled by the host.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 */
अटल पूर्णांक vbg_heartbeat_init(काष्ठा vbg_dev *gdev)
अणु
	पूर्णांक ret;

	/* Make sure that heartbeat checking is disabled अगर we fail. */
	ret = vbg_heartbeat_host_config(gdev, false);
	अगर (ret < 0)
		वापस ret;

	ret = vbg_heartbeat_host_config(gdev, true);
	अगर (ret < 0)
		वापस ret;

	gdev->guest_heartbeat_req = vbg_req_alloc(
					माप(*gdev->guest_heartbeat_req),
					VMMDEVREQ_GUEST_HEARTBEAT,
					VBG_KERNEL_REQUEST);
	अगर (!gdev->guest_heartbeat_req)
		वापस -ENOMEM;

	vbg_info("%s: Setting up heartbeat to trigger every %d milliseconds\n",
		 __func__, gdev->heartbeat_पूर्णांकerval_ms);
	mod_समयr(&gdev->heartbeat_समयr, 0);

	वापस 0;
पूर्ण

/**
 * Cleanup hearbeat code, stop HB समयr and disable host heartbeat checking.
 * @gdev:		The Guest extension device.
 */
अटल व्योम vbg_heartbeat_निकास(काष्ठा vbg_dev *gdev)
अणु
	del_समयr_sync(&gdev->heartbeat_समयr);
	vbg_heartbeat_host_config(gdev, false);
	vbg_req_मुक्त(gdev->guest_heartbeat_req,
		     माप(*gdev->guest_heartbeat_req));
पूर्ण

/**
 * Applies a change to the bit usage tracker.
 * Return: true अगर the mask changed, false अगर not.
 * @tracker:		The bit usage tracker.
 * @changed:		The bits to change.
 * @previous:		The previous value of the bits.
 */
अटल bool vbg_track_bit_usage(काष्ठा vbg_bit_usage_tracker *tracker,
				u32 changed, u32 previous)
अणु
	bool global_change = false;

	जबतक (changed) अणु
		u32 bit = ffs(changed) - 1;
		u32 biपंचांगask = BIT(bit);

		अगर (biपंचांगask & previous) अणु
			tracker->per_bit_usage[bit] -= 1;
			अगर (tracker->per_bit_usage[bit] == 0) अणु
				global_change = true;
				tracker->mask &= ~biपंचांगask;
			पूर्ण
		पूर्ण अन्यथा अणु
			tracker->per_bit_usage[bit] += 1;
			अगर (tracker->per_bit_usage[bit] == 1) अणु
				global_change = true;
				tracker->mask |= biपंचांगask;
			पूर्ण
		पूर्ण

		changed &= ~biपंचांगask;
	पूर्ण

	वापस global_change;
पूर्ण

/**
 * Init and termination worker क्रम resetting the (host) event filter on the host
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		   The Guest extension device.
 * @fixed_events:	   Fixed events (init समय).
 */
अटल पूर्णांक vbg_reset_host_event_filter(काष्ठा vbg_dev *gdev,
				       u32 fixed_events)
अणु
	काष्ठा vmmdev_mask *req;
	पूर्णांक rc;

	req = vbg_req_alloc(माप(*req), VMMDEVREQ_CTL_GUEST_FILTER_MASK,
			    VBG_KERNEL_REQUEST);
	अगर (!req)
		वापस -ENOMEM;

	req->not_mask = U32_MAX & ~fixed_events;
	req->or_mask = fixed_events;
	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0)
		vbg_err("%s error, rc: %d\n", __func__, rc);

	vbg_req_मुक्त(req, माप(*req));
	वापस vbg_status_code_to_त्रुटि_सं(rc);
पूर्ण

/**
 * Changes the event filter mask क्रम the given session.
 *
 * This is called in response to VBG_IOCTL_CHANGE_FILTER_MASK as well as to
 * करो session cleanup. Takes the session mutex.
 *
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:			The Guest extension device.
 * @session:			The session.
 * @or_mask:			The events to add.
 * @not_mask:			The events to हटाओ.
 * @session_termination:	Set अगर we're called by the session cleanup code.
 *				This tweaks the error handling so we perक्रमm
 *				proper session cleanup even अगर the host
 *				misbehaves.
 */
अटल पूर्णांक vbg_set_session_event_filter(काष्ठा vbg_dev *gdev,
					काष्ठा vbg_session *session,
					u32 or_mask, u32 not_mask,
					bool session_termination)
अणु
	काष्ठा vmmdev_mask *req;
	u32 changed, previous;
	पूर्णांक rc, ret = 0;

	/*
	 * Allocate a request buffer beक्रमe taking the spinlock, when
	 * the session is being terminated the requestor is the kernel,
	 * as we're cleaning up.
	 */
	req = vbg_req_alloc(माप(*req), VMMDEVREQ_CTL_GUEST_FILTER_MASK,
			    session_termination ? VBG_KERNEL_REQUEST :
						  session->requestor);
	अगर (!req) अणु
		अगर (!session_termination)
			वापस -ENOMEM;
		/* Ignore allocation failure, we must करो session cleanup. */
	पूर्ण

	mutex_lock(&gdev->session_mutex);

	/* Apply the changes to the session mask. */
	previous = session->event_filter;
	session->event_filter |= or_mask;
	session->event_filter &= ~not_mask;

	/* If anything actually changed, update the global usage counters. */
	changed = previous ^ session->event_filter;
	अगर (!changed)
		जाओ out;

	vbg_track_bit_usage(&gdev->event_filter_tracker, changed, previous);
	or_mask = gdev->fixed_events | gdev->event_filter_tracker.mask;

	अगर (gdev->event_filter_host == or_mask || !req)
		जाओ out;

	gdev->event_filter_host = or_mask;
	req->or_mask = or_mask;
	req->not_mask = ~or_mask;
	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0) अणु
		ret = vbg_status_code_to_त्रुटि_सं(rc);

		/* Failed, roll back (unless it's session termination समय). */
		gdev->event_filter_host = U32_MAX;
		अगर (session_termination)
			जाओ out;

		vbg_track_bit_usage(&gdev->event_filter_tracker, changed,
				    session->event_filter);
		session->event_filter = previous;
	पूर्ण

out:
	mutex_unlock(&gdev->session_mutex);
	vbg_req_मुक्त(req, माप(*req));

	वापस ret;
पूर्ण

/**
 * Init and termination worker क्रम set guest capabilities to zero on the host.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 */
अटल पूर्णांक vbg_reset_host_capabilities(काष्ठा vbg_dev *gdev)
अणु
	काष्ठा vmmdev_mask *req;
	पूर्णांक rc;

	req = vbg_req_alloc(माप(*req), VMMDEVREQ_SET_GUEST_CAPABILITIES,
			    VBG_KERNEL_REQUEST);
	अगर (!req)
		वापस -ENOMEM;

	req->not_mask = U32_MAX;
	req->or_mask = 0;
	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0)
		vbg_err("%s error, rc: %d\n", __func__, rc);

	vbg_req_मुक्त(req, माप(*req));
	वापस vbg_status_code_to_त्रुटि_सं(rc);
पूर्ण

/**
 * Set guest capabilities on the host.
 * Must be called with gdev->session_mutex hold.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:			The Guest extension device.
 * @session:			The session.
 * @session_termination:	Set अगर we're called by the session cleanup code.
 */
अटल पूर्णांक vbg_set_host_capabilities(काष्ठा vbg_dev *gdev,
				     काष्ठा vbg_session *session,
				     bool session_termination)
अणु
	काष्ठा vmmdev_mask *req;
	u32 caps;
	पूर्णांक rc;

	WARN_ON(!mutex_is_locked(&gdev->session_mutex));

	caps = gdev->acquired_guest_caps | gdev->set_guest_caps_tracker.mask;

	अगर (gdev->guest_caps_host == caps)
		वापस 0;

	/* On termination the requestor is the kernel, as we're cleaning up. */
	req = vbg_req_alloc(माप(*req), VMMDEVREQ_SET_GUEST_CAPABILITIES,
			    session_termination ? VBG_KERNEL_REQUEST :
						  session->requestor);
	अगर (!req) अणु
		gdev->guest_caps_host = U32_MAX;
		वापस -ENOMEM;
	पूर्ण

	req->or_mask = caps;
	req->not_mask = ~caps;
	rc = vbg_req_perक्रमm(gdev, req);
	vbg_req_मुक्त(req, माप(*req));

	gdev->guest_caps_host = (rc >= 0) ? caps : U32_MAX;

	वापस vbg_status_code_to_त्रुटि_सं(rc);
पूर्ण

/**
 * Acquire (get exclusive access) guest capabilities क्रम a session.
 * Takes the session mutex.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:			The Guest extension device.
 * @session:			The session.
 * @flags:			Flags (VBGL_IOC_AGC_FLAGS_XXX).
 * @or_mask:			The capabilities to add.
 * @not_mask:			The capabilities to हटाओ.
 * @session_termination:	Set अगर we're called by the session cleanup code.
 *				This tweaks the error handling so we perक्रमm
 *				proper session cleanup even अगर the host
 *				misbehaves.
 */
अटल पूर्णांक vbg_acquire_session_capabilities(काष्ठा vbg_dev *gdev,
					    काष्ठा vbg_session *session,
					    u32 or_mask, u32 not_mask,
					    u32 flags, bool session_termination)
अणु
	अचिन्हित दीर्घ irqflags;
	bool wakeup = false;
	पूर्णांक ret = 0;

	mutex_lock(&gdev->session_mutex);

	अगर (gdev->set_guest_caps_tracker.mask & or_mask) अणु
		vbg_err("%s error: cannot acquire caps which are currently set\n",
			__func__);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Mark any caps in the or_mask as now being in acquire-mode. Note
	 * once caps are in acquire_mode they always stay in this mode.
	 * This impacts event handling, so we take the event-lock.
	 */
	spin_lock_irqsave(&gdev->event_spinlock, irqflags);
	gdev->acquire_mode_guest_caps |= or_mask;
	spin_unlock_irqrestore(&gdev->event_spinlock, irqflags);

	/* If we only have to चयन the caps to acquire mode, we're करोne. */
	अगर (flags & VBGL_IOC_AGC_FLAGS_CONFIG_ACQUIRE_MODE)
		जाओ out;

	not_mask &= ~or_mask; /* or_mask takes priority over not_mask */
	not_mask &= session->acquired_guest_caps;
	or_mask &= ~session->acquired_guest_caps;

	अगर (or_mask == 0 && not_mask == 0)
		जाओ out;

	अगर (gdev->acquired_guest_caps & or_mask) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	gdev->acquired_guest_caps |= or_mask;
	gdev->acquired_guest_caps &= ~not_mask;
	/* session->acquired_guest_caps impacts event handling, take the lock */
	spin_lock_irqsave(&gdev->event_spinlock, irqflags);
	session->acquired_guest_caps |= or_mask;
	session->acquired_guest_caps &= ~not_mask;
	spin_unlock_irqrestore(&gdev->event_spinlock, irqflags);

	ret = vbg_set_host_capabilities(gdev, session, session_termination);
	/* Roll back on failure, unless it's session termination समय. */
	अगर (ret < 0 && !session_termination) अणु
		gdev->acquired_guest_caps &= ~or_mask;
		gdev->acquired_guest_caps |= not_mask;
		spin_lock_irqsave(&gdev->event_spinlock, irqflags);
		session->acquired_guest_caps &= ~or_mask;
		session->acquired_guest_caps |= not_mask;
		spin_unlock_irqrestore(&gdev->event_spinlock, irqflags);
	पूर्ण

	/*
	 * If we added a capability, check अगर that means some other thपढ़ो in
	 * our session should be unblocked because there are events pending
	 * (the result of vbg_get_allowed_event_mask_क्रम_session() may change).
	 *
	 * HACK ALERT! When the seamless support capability is added we generate
	 *	a seamless change event so that the ring-3 client can sync with
	 *	the seamless state.
	 */
	अगर (ret == 0 && or_mask != 0) अणु
		spin_lock_irqsave(&gdev->event_spinlock, irqflags);

		अगर (or_mask & VMMDEV_GUEST_SUPPORTS_SEAMLESS)
			gdev->pending_events |=
				VMMDEV_EVENT_SEAMLESS_MODE_CHANGE_REQUEST;

		अगर (gdev->pending_events)
			wakeup = true;

		spin_unlock_irqrestore(&gdev->event_spinlock, irqflags);

		अगर (wakeup)
			wake_up(&gdev->event_wq);
	पूर्ण

out:
	mutex_unlock(&gdev->session_mutex);

	वापस ret;
पूर्ण

/**
 * Sets the guest capabilities क्रम a session. Takes the session mutex.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:			The Guest extension device.
 * @session:			The session.
 * @or_mask:			The capabilities to add.
 * @not_mask:			The capabilities to हटाओ.
 * @session_termination:	Set अगर we're called by the session cleanup code.
 *				This tweaks the error handling so we perक्रमm
 *				proper session cleanup even अगर the host
 *				misbehaves.
 */
अटल पूर्णांक vbg_set_session_capabilities(काष्ठा vbg_dev *gdev,
					काष्ठा vbg_session *session,
					u32 or_mask, u32 not_mask,
					bool session_termination)
अणु
	u32 changed, previous;
	पूर्णांक ret = 0;

	mutex_lock(&gdev->session_mutex);

	अगर (gdev->acquire_mode_guest_caps & or_mask) अणु
		vbg_err("%s error: cannot set caps which are in acquire_mode\n",
			__func__);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Apply the changes to the session mask. */
	previous = session->set_guest_caps;
	session->set_guest_caps |= or_mask;
	session->set_guest_caps &= ~not_mask;

	/* If anything actually changed, update the global usage counters. */
	changed = previous ^ session->set_guest_caps;
	अगर (!changed)
		जाओ out;

	vbg_track_bit_usage(&gdev->set_guest_caps_tracker, changed, previous);

	ret = vbg_set_host_capabilities(gdev, session, session_termination);
	/* Roll back on failure, unless it's session termination समय. */
	अगर (ret < 0 && !session_termination) अणु
		vbg_track_bit_usage(&gdev->set_guest_caps_tracker, changed,
				    session->set_guest_caps);
		session->set_guest_caps = previous;
	पूर्ण

out:
	mutex_unlock(&gdev->session_mutex);

	वापस ret;
पूर्ण

/**
 * vbg_query_host_version get the host feature mask and version inक्रमmation.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 */
अटल पूर्णांक vbg_query_host_version(काष्ठा vbg_dev *gdev)
अणु
	काष्ठा vmmdev_host_version *req;
	पूर्णांक rc, ret;

	req = vbg_req_alloc(माप(*req), VMMDEVREQ_GET_HOST_VERSION,
			    VBG_KERNEL_REQUEST);
	अगर (!req)
		वापस -ENOMEM;

	rc = vbg_req_perक्रमm(gdev, req);
	ret = vbg_status_code_to_त्रुटि_सं(rc);
	अगर (ret) अणु
		vbg_err("%s error: %d\n", __func__, rc);
		जाओ out;
	पूर्ण

	snम_लिखो(gdev->host_version, माप(gdev->host_version), "%u.%u.%ur%u",
		 req->major, req->minor, req->build, req->revision);
	gdev->host_features = req->features;

	vbg_info("vboxguest: host-version: %s %#x\n", gdev->host_version,
		 gdev->host_features);

	अगर (!(req->features & VMMDEV_HVF_HGCM_PHYS_PAGE_LIST)) अणु
		vbg_err("vboxguest: Error host too old (does not support page-lists)\n");
		ret = -ENODEV;
	पूर्ण

out:
	vbg_req_मुक्त(req, माप(*req));
	वापस ret;
पूर्ण

/**
 * Initializes the VBoxGuest device extension when the
 * device driver is loaded.
 *
 * The native code locates the VMMDev on the PCI bus and retrieve
 * the MMIO and I/O port ranges, this function will take care of
 * mapping the MMIO memory (अगर present). Upon successful वापस
 * the native code should set up the पूर्णांकerrupt handler.
 *
 * Return: 0 or negative त्रुटि_सं value.
 *
 * @gdev:		The Guest extension device.
 * @fixed_events:	Events that will be enabled upon init and no client
 *			will ever be allowed to mask.
 */
पूर्णांक vbg_core_init(काष्ठा vbg_dev *gdev, u32 fixed_events)
अणु
	पूर्णांक ret = -ENOMEM;

	gdev->fixed_events = fixed_events | VMMDEV_EVENT_HGCM;
	gdev->event_filter_host = U32_MAX;	/* क्रमces a report */
	gdev->guest_caps_host = U32_MAX;	/* क्रमces a report */

	init_रुकोqueue_head(&gdev->event_wq);
	init_रुकोqueue_head(&gdev->hgcm_wq);
	spin_lock_init(&gdev->event_spinlock);
	mutex_init(&gdev->session_mutex);
	mutex_init(&gdev->cancel_req_mutex);
	समयr_setup(&gdev->heartbeat_समयr, vbg_heartbeat_समयr, 0);
	INIT_WORK(&gdev->mem_balloon.work, vbg_balloon_work);

	gdev->mem_balloon.get_req =
		vbg_req_alloc(माप(*gdev->mem_balloon.get_req),
			      VMMDEVREQ_GET_MEMBALLOON_CHANGE_REQ,
			      VBG_KERNEL_REQUEST);
	gdev->mem_balloon.change_req =
		vbg_req_alloc(माप(*gdev->mem_balloon.change_req),
			      VMMDEVREQ_CHANGE_MEMBALLOON,
			      VBG_KERNEL_REQUEST);
	gdev->cancel_req =
		vbg_req_alloc(माप(*(gdev->cancel_req)),
			      VMMDEVREQ_HGCM_CANCEL2,
			      VBG_KERNEL_REQUEST);
	gdev->ack_events_req =
		vbg_req_alloc(माप(*gdev->ack_events_req),
			      VMMDEVREQ_ACKNOWLEDGE_EVENTS,
			      VBG_KERNEL_REQUEST);
	gdev->mouse_status_req =
		vbg_req_alloc(माप(*gdev->mouse_status_req),
			      VMMDEVREQ_GET_MOUSE_STATUS,
			      VBG_KERNEL_REQUEST);

	अगर (!gdev->mem_balloon.get_req || !gdev->mem_balloon.change_req ||
	    !gdev->cancel_req || !gdev->ack_events_req ||
	    !gdev->mouse_status_req)
		जाओ err_मुक्त_reqs;

	ret = vbg_query_host_version(gdev);
	अगर (ret)
		जाओ err_मुक्त_reqs;

	ret = vbg_report_guest_info(gdev);
	अगर (ret) अणु
		vbg_err("vboxguest: vbg_report_guest_info error: %d\n", ret);
		जाओ err_मुक्त_reqs;
	पूर्ण

	ret = vbg_reset_host_event_filter(gdev, gdev->fixed_events);
	अगर (ret) अणु
		vbg_err("vboxguest: Error setting fixed event filter: %d\n",
			ret);
		जाओ err_मुक्त_reqs;
	पूर्ण

	ret = vbg_reset_host_capabilities(gdev);
	अगर (ret) अणु
		vbg_err("vboxguest: Error clearing guest capabilities: %d\n",
			ret);
		जाओ err_मुक्त_reqs;
	पूर्ण

	ret = vbg_core_set_mouse_status(gdev, 0);
	अगर (ret) अणु
		vbg_err("vboxguest: Error clearing mouse status: %d\n", ret);
		जाओ err_मुक्त_reqs;
	पूर्ण

	/* These may fail without requiring the driver init to fail. */
	vbg_guest_mappings_init(gdev);
	vbg_heartbeat_init(gdev);

	/* All Done! */
	ret = vbg_report_driver_status(gdev, true);
	अगर (ret < 0)
		vbg_err("vboxguest: Error reporting driver status: %d\n", ret);

	वापस 0;

err_मुक्त_reqs:
	vbg_req_मुक्त(gdev->mouse_status_req,
		     माप(*gdev->mouse_status_req));
	vbg_req_मुक्त(gdev->ack_events_req,
		     माप(*gdev->ack_events_req));
	vbg_req_मुक्त(gdev->cancel_req,
		     माप(*gdev->cancel_req));
	vbg_req_मुक्त(gdev->mem_balloon.change_req,
		     माप(*gdev->mem_balloon.change_req));
	vbg_req_मुक्त(gdev->mem_balloon.get_req,
		     माप(*gdev->mem_balloon.get_req));
	वापस ret;
पूर्ण

/**
 * Call this on निकास to clean-up vboxguest-core managed resources.
 *
 * The native code should call this beक्रमe the driver is loaded,
 * but करोn't call this on shutकरोwn.
 * @gdev:		The Guest extension device.
 */
व्योम vbg_core_निकास(काष्ठा vbg_dev *gdev)
अणु
	vbg_heartbeat_निकास(gdev);
	vbg_guest_mappings_निकास(gdev);

	/* Clear the host flags (mouse status etc). */
	vbg_reset_host_event_filter(gdev, 0);
	vbg_reset_host_capabilities(gdev);
	vbg_core_set_mouse_status(gdev, 0);

	vbg_req_मुक्त(gdev->mouse_status_req,
		     माप(*gdev->mouse_status_req));
	vbg_req_मुक्त(gdev->ack_events_req,
		     माप(*gdev->ack_events_req));
	vbg_req_मुक्त(gdev->cancel_req,
		     माप(*gdev->cancel_req));
	vbg_req_मुक्त(gdev->mem_balloon.change_req,
		     माप(*gdev->mem_balloon.change_req));
	vbg_req_मुक्त(gdev->mem_balloon.get_req,
		     माप(*gdev->mem_balloon.get_req));
पूर्ण

/**
 * Creates a VBoxGuest user session.
 *
 * vboxguest_linux.c calls this when userspace खोलोs the अक्षर-device.
 * Return: A poपूर्णांकer to the new session or an ERR_PTR on error.
 * @gdev:		The Guest extension device.
 * @requestor:		VMMDEV_REQUESTOR_* flags
 */
काष्ठा vbg_session *vbg_core_खोलो_session(काष्ठा vbg_dev *gdev, u32 requestor)
अणु
	काष्ठा vbg_session *session;

	session = kzalloc(माप(*session), GFP_KERNEL);
	अगर (!session)
		वापस ERR_PTR(-ENOMEM);

	session->gdev = gdev;
	session->requestor = requestor;

	वापस session;
पूर्ण

/**
 * Closes a VBoxGuest session.
 * @session:		The session to बंद (and मुक्त).
 */
व्योम vbg_core_बंद_session(काष्ठा vbg_session *session)
अणु
	काष्ठा vbg_dev *gdev = session->gdev;
	पूर्णांक i, rc;

	vbg_acquire_session_capabilities(gdev, session, 0, U32_MAX, 0, true);
	vbg_set_session_capabilities(gdev, session, 0, U32_MAX, true);
	vbg_set_session_event_filter(gdev, session, 0, U32_MAX, true);

	क्रम (i = 0; i < ARRAY_SIZE(session->hgcm_client_ids); i++) अणु
		अगर (!session->hgcm_client_ids[i])
			जारी;

		/* requestor is kernel here, as we're cleaning up. */
		vbg_hgcm_disconnect(gdev, VBG_KERNEL_REQUEST,
				    session->hgcm_client_ids[i], &rc);
	पूर्ण

	kमुक्त(session);
पूर्ण

अटल पूर्णांक vbg_ioctl_chk(काष्ठा vbg_ioctl_hdr *hdr, माप_प्रकार in_size,
			 माप_प्रकार out_size)
अणु
	अगर (hdr->size_in  != (माप(*hdr) + in_size) ||
	    hdr->size_out != (माप(*hdr) + out_size))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vbg_ioctl_driver_version_info(
	काष्ठा vbg_ioctl_driver_version_info *info)
अणु
	स्थिर u16 vbg_maj_version = VBG_IOC_VERSION >> 16;
	u16 min_maj_version, req_maj_version;

	अगर (vbg_ioctl_chk(&info->hdr, माप(info->u.in), माप(info->u.out)))
		वापस -EINVAL;

	req_maj_version = info->u.in.req_version >> 16;
	min_maj_version = info->u.in.min_version >> 16;

	अगर (info->u.in.min_version > info->u.in.req_version ||
	    min_maj_version != req_maj_version)
		वापस -EINVAL;

	अगर (info->u.in.min_version <= VBG_IOC_VERSION &&
	    min_maj_version == vbg_maj_version) अणु
		info->u.out.session_version = VBG_IOC_VERSION;
	पूर्ण अन्यथा अणु
		info->u.out.session_version = U32_MAX;
		info->hdr.rc = VERR_VERSION_MISMATCH;
	पूर्ण

	info->u.out.driver_version  = VBG_IOC_VERSION;
	info->u.out.driver_revision = 0;
	info->u.out.reserved1      = 0;
	info->u.out.reserved2      = 0;

	वापस 0;
पूर्ण

/* Must be called with the event_lock held */
अटल u32 vbg_get_allowed_event_mask_क्रम_session(काष्ठा vbg_dev *gdev,
						  काष्ठा vbg_session *session)
अणु
	u32 acquire_mode_caps = gdev->acquire_mode_guest_caps;
	u32 session_acquired_caps = session->acquired_guest_caps;
	u32 allowed_events = VMMDEV_EVENT_VALID_EVENT_MASK;

	अगर ((acquire_mode_caps & VMMDEV_GUEST_SUPPORTS_GRAPHICS) &&
	    !(session_acquired_caps & VMMDEV_GUEST_SUPPORTS_GRAPHICS))
		allowed_events &= ~VMMDEV_EVENT_DISPLAY_CHANGE_REQUEST;

	अगर ((acquire_mode_caps & VMMDEV_GUEST_SUPPORTS_SEAMLESS) &&
	    !(session_acquired_caps & VMMDEV_GUEST_SUPPORTS_SEAMLESS))
		allowed_events &= ~VMMDEV_EVENT_SEAMLESS_MODE_CHANGE_REQUEST;

	वापस allowed_events;
पूर्ण

अटल bool vbg_रुको_event_cond(काष्ठा vbg_dev *gdev,
				काष्ठा vbg_session *session,
				u32 event_mask)
अणु
	अचिन्हित दीर्घ flags;
	bool wakeup;
	u32 events;

	spin_lock_irqsave(&gdev->event_spinlock, flags);

	events = gdev->pending_events & event_mask;
	events &= vbg_get_allowed_event_mask_क्रम_session(gdev, session);
	wakeup = events || session->cancel_रुकोers;

	spin_unlock_irqrestore(&gdev->event_spinlock, flags);

	वापस wakeup;
पूर्ण

/* Must be called with the event_lock held */
अटल u32 vbg_consume_events_locked(काष्ठा vbg_dev *gdev,
				     काष्ठा vbg_session *session,
				     u32 event_mask)
अणु
	u32 events = gdev->pending_events & event_mask;

	events &= vbg_get_allowed_event_mask_क्रम_session(gdev, session);
	gdev->pending_events &= ~events;
	वापस events;
पूर्ण

अटल पूर्णांक vbg_ioctl_रुको_क्रम_events(काष्ठा vbg_dev *gdev,
				     काष्ठा vbg_session *session,
				     काष्ठा vbg_ioctl_रुको_क्रम_events *रुको)
अणु
	u32 समयout_ms = रुको->u.in.समयout_ms;
	u32 event_mask = रुको->u.in.events;
	अचिन्हित दीर्घ flags;
	दीर्घ समयout;
	पूर्णांक ret = 0;

	अगर (vbg_ioctl_chk(&रुको->hdr, माप(रुको->u.in), माप(रुको->u.out)))
		वापस -EINVAL;

	अगर (समयout_ms == U32_MAX)
		समयout = MAX_SCHEDULE_TIMEOUT;
	अन्यथा
		समयout = msecs_to_jअगरfies(समयout_ms);

	रुको->u.out.events = 0;
	करो अणु
		समयout = रुको_event_पूर्णांकerruptible_समयout(
				gdev->event_wq,
				vbg_रुको_event_cond(gdev, session, event_mask),
				समयout);

		spin_lock_irqsave(&gdev->event_spinlock, flags);

		अगर (समयout < 0 || session->cancel_रुकोers) अणु
			ret = -EINTR;
		पूर्ण अन्यथा अगर (समयout == 0) अणु
			ret = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			रुको->u.out.events =
			   vbg_consume_events_locked(gdev, session, event_mask);
		पूर्ण

		spin_unlock_irqrestore(&gdev->event_spinlock, flags);

		/*
		 * Someone अन्यथा may have consumed the event(s) first, in
		 * which हाल we go back to रुकोing.
		 */
	पूर्ण जबतक (ret == 0 && रुको->u.out.events == 0);

	वापस ret;
पूर्ण

अटल पूर्णांक vbg_ioctl_पूर्णांकerrupt_all_रुको_events(काष्ठा vbg_dev *gdev,
					       काष्ठा vbg_session *session,
					       काष्ठा vbg_ioctl_hdr *hdr)
अणु
	अचिन्हित दीर्घ flags;

	अगर (hdr->size_in != माप(*hdr) || hdr->size_out != माप(*hdr))
		वापस -EINVAL;

	spin_lock_irqsave(&gdev->event_spinlock, flags);
	session->cancel_रुकोers = true;
	spin_unlock_irqrestore(&gdev->event_spinlock, flags);

	wake_up(&gdev->event_wq);

	वापस 0;
पूर्ण

/**
 * Checks अगर the VMM request is allowed in the context of the given session.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 * @session:		The calling session.
 * @req:		The request.
 */
अटल पूर्णांक vbg_req_allowed(काष्ठा vbg_dev *gdev, काष्ठा vbg_session *session,
			   स्थिर काष्ठा vmmdev_request_header *req)
अणु
	स्थिर काष्ठा vmmdev_guest_status *guest_status;
	bool trusted_apps_only;

	चयन (req->request_type) अणु
	/* Trusted users apps only. */
	हाल VMMDEVREQ_QUERY_CREDENTIALS:
	हाल VMMDEVREQ_REPORT_CREDENTIALS_JUDGEMENT:
	हाल VMMDEVREQ_REGISTER_SHARED_MODULE:
	हाल VMMDEVREQ_UNREGISTER_SHARED_MODULE:
	हाल VMMDEVREQ_WRITE_COREDUMP:
	हाल VMMDEVREQ_GET_CPU_HOTPLUG_REQ:
	हाल VMMDEVREQ_SET_CPU_HOTPLUG_STATUS:
	हाल VMMDEVREQ_CHECK_SHARED_MODULES:
	हाल VMMDEVREQ_GET_PAGE_SHARING_STATUS:
	हाल VMMDEVREQ_DEBUG_IS_PAGE_SHARED:
	हाल VMMDEVREQ_REPORT_GUEST_STATS:
	हाल VMMDEVREQ_REPORT_GUEST_USER_STATE:
	हाल VMMDEVREQ_GET_STATISTICS_CHANGE_REQ:
		trusted_apps_only = true;
		अवरोध;

	/* Anyone. */
	हाल VMMDEVREQ_GET_MOUSE_STATUS:
	हाल VMMDEVREQ_SET_MOUSE_STATUS:
	हाल VMMDEVREQ_SET_POINTER_SHAPE:
	हाल VMMDEVREQ_GET_HOST_VERSION:
	हाल VMMDEVREQ_IDLE:
	हाल VMMDEVREQ_GET_HOST_TIME:
	हाल VMMDEVREQ_SET_POWER_STATUS:
	हाल VMMDEVREQ_ACKNOWLEDGE_EVENTS:
	हाल VMMDEVREQ_CTL_GUEST_FILTER_MASK:
	हाल VMMDEVREQ_REPORT_GUEST_STATUS:
	हाल VMMDEVREQ_GET_DISPLAY_CHANGE_REQ:
	हाल VMMDEVREQ_VIDEMODE_SUPPORTED:
	हाल VMMDEVREQ_GET_HEIGHT_REDUCTION:
	हाल VMMDEVREQ_GET_DISPLAY_CHANGE_REQ2:
	हाल VMMDEVREQ_VIDEMODE_SUPPORTED2:
	हाल VMMDEVREQ_VIDEO_ACCEL_ENABLE:
	हाल VMMDEVREQ_VIDEO_ACCEL_FLUSH:
	हाल VMMDEVREQ_VIDEO_SET_VISIBLE_REGION:
	हाल VMMDEVREQ_VIDEO_UPDATE_MONITOR_POSITIONS:
	हाल VMMDEVREQ_GET_DISPLAY_CHANGE_REQEX:
	हाल VMMDEVREQ_GET_DISPLAY_CHANGE_REQ_MULTI:
	हाल VMMDEVREQ_GET_SEAMLESS_CHANGE_REQ:
	हाल VMMDEVREQ_GET_VRDPCHANGE_REQ:
	हाल VMMDEVREQ_LOG_STRING:
	हाल VMMDEVREQ_GET_SESSION_ID:
		trusted_apps_only = false;
		अवरोध;

	/* Depends on the request parameters... */
	हाल VMMDEVREQ_REPORT_GUEST_CAPABILITIES:
		guest_status = (स्थिर काष्ठा vmmdev_guest_status *)req;
		चयन (guest_status->facility) अणु
		हाल VBOXGUEST_FACILITY_TYPE_ALL:
		हाल VBOXGUEST_FACILITY_TYPE_VBOXGUEST_DRIVER:
			vbg_err("Denying userspace vmm report guest cap. call facility %#08x\n",
				guest_status->facility);
			वापस -EPERM;
		हाल VBOXGUEST_FACILITY_TYPE_VBOX_SERVICE:
			trusted_apps_only = true;
			अवरोध;
		हाल VBOXGUEST_FACILITY_TYPE_VBOX_TRAY_CLIENT:
		हाल VBOXGUEST_FACILITY_TYPE_SEAMLESS:
		हाल VBOXGUEST_FACILITY_TYPE_GRAPHICS:
		शेष:
			trusted_apps_only = false;
			अवरोध;
		पूर्ण
		अवरोध;

	/* Anything अन्यथा is not allowed. */
	शेष:
		vbg_err("Denying userspace vmm call type %#08x\n",
			req->request_type);
		वापस -EPERM;
	पूर्ण

	अगर (trusted_apps_only &&
	    (session->requestor & VMMDEV_REQUESTOR_USER_DEVICE)) अणु
		vbg_err("Denying userspace vmm call type %#08x through vboxuser device node\n",
			req->request_type);
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vbg_ioctl_vmmrequest(काष्ठा vbg_dev *gdev,
				काष्ठा vbg_session *session, व्योम *data)
अणु
	काष्ठा vbg_ioctl_hdr *hdr = data;
	पूर्णांक ret;

	अगर (hdr->size_in != hdr->size_out)
		वापस -EINVAL;

	अगर (hdr->size_in > VMMDEV_MAX_VMMDEVREQ_SIZE)
		वापस -E2BIG;

	अगर (hdr->type == VBG_IOCTL_HDR_TYPE_DEFAULT)
		वापस -EINVAL;

	ret = vbg_req_allowed(gdev, session, data);
	अगर (ret < 0)
		वापस ret;

	vbg_req_perक्रमm(gdev, data);
	WARN_ON(hdr->rc == VINF_HGCM_ASYNC_EXECUTE);

	वापस 0;
पूर्ण

अटल पूर्णांक vbg_ioctl_hgcm_connect(काष्ठा vbg_dev *gdev,
				  काष्ठा vbg_session *session,
				  काष्ठा vbg_ioctl_hgcm_connect *conn)
अणु
	u32 client_id;
	पूर्णांक i, ret;

	अगर (vbg_ioctl_chk(&conn->hdr, माप(conn->u.in), माप(conn->u.out)))
		वापस -EINVAL;

	/* Find a मुक्त place in the sessions clients array and claim it */
	mutex_lock(&gdev->session_mutex);
	क्रम (i = 0; i < ARRAY_SIZE(session->hgcm_client_ids); i++) अणु
		अगर (!session->hgcm_client_ids[i]) अणु
			session->hgcm_client_ids[i] = U32_MAX;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&gdev->session_mutex);

	अगर (i >= ARRAY_SIZE(session->hgcm_client_ids))
		वापस -EMखाता;

	ret = vbg_hgcm_connect(gdev, session->requestor, &conn->u.in.loc,
			       &client_id, &conn->hdr.rc);

	mutex_lock(&gdev->session_mutex);
	अगर (ret == 0 && conn->hdr.rc >= 0) अणु
		conn->u.out.client_id = client_id;
		session->hgcm_client_ids[i] = client_id;
	पूर्ण अन्यथा अणु
		conn->u.out.client_id = 0;
		session->hgcm_client_ids[i] = 0;
	पूर्ण
	mutex_unlock(&gdev->session_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक vbg_ioctl_hgcm_disconnect(काष्ठा vbg_dev *gdev,
				     काष्ठा vbg_session *session,
				     काष्ठा vbg_ioctl_hgcm_disconnect *disconn)
अणु
	u32 client_id;
	पूर्णांक i, ret;

	अगर (vbg_ioctl_chk(&disconn->hdr, माप(disconn->u.in), 0))
		वापस -EINVAL;

	client_id = disconn->u.in.client_id;
	अगर (client_id == 0 || client_id == U32_MAX)
		वापस -EINVAL;

	mutex_lock(&gdev->session_mutex);
	क्रम (i = 0; i < ARRAY_SIZE(session->hgcm_client_ids); i++) अणु
		अगर (session->hgcm_client_ids[i] == client_id) अणु
			session->hgcm_client_ids[i] = U32_MAX;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&gdev->session_mutex);

	अगर (i >= ARRAY_SIZE(session->hgcm_client_ids))
		वापस -EINVAL;

	ret = vbg_hgcm_disconnect(gdev, session->requestor, client_id,
				  &disconn->hdr.rc);

	mutex_lock(&gdev->session_mutex);
	अगर (ret == 0 && disconn->hdr.rc >= 0)
		session->hgcm_client_ids[i] = 0;
	अन्यथा
		session->hgcm_client_ids[i] = client_id;
	mutex_unlock(&gdev->session_mutex);

	वापस ret;
पूर्ण

अटल bool vbg_param_valid(क्रमागत vmmdev_hgcm_function_parameter_type type)
अणु
	चयन (type) अणु
	हाल VMMDEV_HGCM_PARM_TYPE_32BIT:
	हाल VMMDEV_HGCM_PARM_TYPE_64BIT:
	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR:
	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक vbg_ioctl_hgcm_call(काष्ठा vbg_dev *gdev,
			       काष्ठा vbg_session *session, bool f32bit,
			       काष्ठा vbg_ioctl_hgcm_call *call)
अणु
	माप_प्रकार actual_size;
	u32 client_id;
	पूर्णांक i, ret;

	अगर (call->hdr.size_in < माप(*call))
		वापस -EINVAL;

	अगर (call->hdr.size_in != call->hdr.size_out)
		वापस -EINVAL;

	अगर (call->parm_count > VMMDEV_HGCM_MAX_PARMS)
		वापस -E2BIG;

	client_id = call->client_id;
	अगर (client_id == 0 || client_id == U32_MAX)
		वापस -EINVAL;

	actual_size = माप(*call);
	अगर (f32bit)
		actual_size += call->parm_count *
			       माप(काष्ठा vmmdev_hgcm_function_parameter32);
	अन्यथा
		actual_size += call->parm_count *
			       माप(काष्ठा vmmdev_hgcm_function_parameter);
	अगर (call->hdr.size_in < actual_size) अणु
		vbg_debug("VBG_IOCTL_HGCM_CALL: hdr.size_in %d required size is %zd\n",
			  call->hdr.size_in, actual_size);
		वापस -EINVAL;
	पूर्ण
	call->hdr.size_out = actual_size;

	/* Validate parameter types */
	अगर (f32bit) अणु
		काष्ठा vmmdev_hgcm_function_parameter32 *parm =
			VBG_IOCTL_HGCM_CALL_PARMS32(call);

		क्रम (i = 0; i < call->parm_count; i++)
			अगर (!vbg_param_valid(parm[i].type))
				वापस -EINVAL;
	पूर्ण अन्यथा अणु
		काष्ठा vmmdev_hgcm_function_parameter *parm =
			VBG_IOCTL_HGCM_CALL_PARMS(call);

		क्रम (i = 0; i < call->parm_count; i++)
			अगर (!vbg_param_valid(parm[i].type))
				वापस -EINVAL;
	पूर्ण

	/*
	 * Validate the client id.
	 */
	mutex_lock(&gdev->session_mutex);
	क्रम (i = 0; i < ARRAY_SIZE(session->hgcm_client_ids); i++)
		अगर (session->hgcm_client_ids[i] == client_id)
			अवरोध;
	mutex_unlock(&gdev->session_mutex);
	अगर (i >= ARRAY_SIZE(session->hgcm_client_ids)) अणु
		vbg_debug("VBG_IOCTL_HGCM_CALL: INVALID handle. u32Client=%#08x\n",
			  client_id);
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_COMPAT) && f32bit)
		ret = vbg_hgcm_call32(gdev, session->requestor, client_id,
				      call->function, call->समयout_ms,
				      VBG_IOCTL_HGCM_CALL_PARMS32(call),
				      call->parm_count, &call->hdr.rc);
	अन्यथा
		ret = vbg_hgcm_call(gdev, session->requestor, client_id,
				    call->function, call->समयout_ms,
				    VBG_IOCTL_HGCM_CALL_PARMS(call),
				    call->parm_count, &call->hdr.rc);

	अगर (ret == -E2BIG) अणु
		/* E2BIG needs to be reported through the hdr.rc field. */
		call->hdr.rc = VERR_OUT_OF_RANGE;
		ret = 0;
	पूर्ण

	अगर (ret && ret != -EINTR && ret != -ETIMEDOUT)
		vbg_err("VBG_IOCTL_HGCM_CALL error: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक vbg_ioctl_log(काष्ठा vbg_ioctl_log *log)
अणु
	अगर (log->hdr.size_out != माप(log->hdr))
		वापस -EINVAL;

	vbg_info("%.*s", (पूर्णांक)(log->hdr.size_in - माप(log->hdr)),
		 log->u.in.msg);

	वापस 0;
पूर्ण

अटल पूर्णांक vbg_ioctl_change_filter_mask(काष्ठा vbg_dev *gdev,
					काष्ठा vbg_session *session,
					काष्ठा vbg_ioctl_change_filter *filter)
अणु
	u32 or_mask, not_mask;

	अगर (vbg_ioctl_chk(&filter->hdr, माप(filter->u.in), 0))
		वापस -EINVAL;

	or_mask = filter->u.in.or_mask;
	not_mask = filter->u.in.not_mask;

	अगर ((or_mask | not_mask) & ~VMMDEV_EVENT_VALID_EVENT_MASK)
		वापस -EINVAL;

	वापस vbg_set_session_event_filter(gdev, session, or_mask, not_mask,
					    false);
पूर्ण

अटल पूर्णांक vbg_ioctl_acquire_guest_capabilities(काष्ठा vbg_dev *gdev,
	     काष्ठा vbg_session *session,
	     काष्ठा vbg_ioctl_acquire_guest_caps *caps)
अणु
	u32 flags, or_mask, not_mask;

	अगर (vbg_ioctl_chk(&caps->hdr, माप(caps->u.in), 0))
		वापस -EINVAL;

	flags = caps->u.in.flags;
	or_mask = caps->u.in.or_mask;
	not_mask = caps->u.in.not_mask;

	अगर (flags & ~VBGL_IOC_AGC_FLAGS_VALID_MASK)
		वापस -EINVAL;

	अगर ((or_mask | not_mask) & ~VMMDEV_GUEST_CAPABILITIES_MASK)
		वापस -EINVAL;

	वापस vbg_acquire_session_capabilities(gdev, session, or_mask,
						not_mask, flags, false);
पूर्ण

अटल पूर्णांक vbg_ioctl_change_guest_capabilities(काष्ठा vbg_dev *gdev,
	     काष्ठा vbg_session *session, काष्ठा vbg_ioctl_set_guest_caps *caps)
अणु
	u32 or_mask, not_mask;
	पूर्णांक ret;

	अगर (vbg_ioctl_chk(&caps->hdr, माप(caps->u.in), माप(caps->u.out)))
		वापस -EINVAL;

	or_mask = caps->u.in.or_mask;
	not_mask = caps->u.in.not_mask;

	अगर ((or_mask | not_mask) & ~VMMDEV_GUEST_CAPABILITIES_MASK)
		वापस -EINVAL;

	ret = vbg_set_session_capabilities(gdev, session, or_mask, not_mask,
					   false);
	अगर (ret)
		वापस ret;

	caps->u.out.session_caps = session->set_guest_caps;
	caps->u.out.global_caps = gdev->guest_caps_host;

	वापस 0;
पूर्ण

अटल पूर्णांक vbg_ioctl_check_balloon(काष्ठा vbg_dev *gdev,
				   काष्ठा vbg_ioctl_check_balloon *balloon_info)
अणु
	अगर (vbg_ioctl_chk(&balloon_info->hdr, 0, माप(balloon_info->u.out)))
		वापस -EINVAL;

	balloon_info->u.out.balloon_chunks = gdev->mem_balloon.chunks;
	/*
	 * Under Linux we handle VMMDEV_EVENT_BALLOON_CHANGE_REQUEST
	 * events entirely in the kernel, see vbg_core_isr().
	 */
	balloon_info->u.out.handle_in_r3 = false;

	वापस 0;
पूर्ण

अटल पूर्णांक vbg_ioctl_ग_लिखो_core_dump(काष्ठा vbg_dev *gdev,
				     काष्ठा vbg_session *session,
				     काष्ठा vbg_ioctl_ग_लिखो_coredump *dump)
अणु
	काष्ठा vmmdev_ग_लिखो_core_dump *req;

	अगर (vbg_ioctl_chk(&dump->hdr, माप(dump->u.in), 0))
		वापस -EINVAL;

	req = vbg_req_alloc(माप(*req), VMMDEVREQ_WRITE_COREDUMP,
			    session->requestor);
	अगर (!req)
		वापस -ENOMEM;

	req->flags = dump->u.in.flags;
	dump->hdr.rc = vbg_req_perक्रमm(gdev, req);

	vbg_req_मुक्त(req, माप(*req));
	वापस 0;
पूर्ण

/**
 * Common IOCtl क्रम user to kernel communication.
 * Return: 0 or negative त्रुटि_सं value.
 * @session:	The client session.
 * @req:	The requested function.
 * @data:	The i/o data buffer, minimum size माप(काष्ठा vbg_ioctl_hdr).
 */
पूर्णांक vbg_core_ioctl(काष्ठा vbg_session *session, अचिन्हित पूर्णांक req, व्योम *data)
अणु
	अचिन्हित पूर्णांक req_no_size = req & ~IOCSIZE_MASK;
	काष्ठा vbg_dev *gdev = session->gdev;
	काष्ठा vbg_ioctl_hdr *hdr = data;
	bool f32bit = false;

	hdr->rc = VINF_SUCCESS;
	अगर (!hdr->size_out)
		hdr->size_out = hdr->size_in;

	/*
	 * hdr->version and hdr->size_in / hdr->size_out minimum size are
	 * alपढ़ोy checked by vbg_misc_device_ioctl().
	 */

	/* For VMMDEV_REQUEST hdr->type != VBG_IOCTL_HDR_TYPE_DEFAULT */
	अगर (req_no_size == VBG_IOCTL_VMMDEV_REQUEST(0) ||
	    req == VBG_IOCTL_VMMDEV_REQUEST_BIG ||
	    req == VBG_IOCTL_VMMDEV_REQUEST_BIG_ALT)
		वापस vbg_ioctl_vmmrequest(gdev, session, data);

	अगर (hdr->type != VBG_IOCTL_HDR_TYPE_DEFAULT)
		वापस -EINVAL;

	/* Fixed size requests. */
	चयन (req) अणु
	हाल VBG_IOCTL_DRIVER_VERSION_INFO:
		वापस vbg_ioctl_driver_version_info(data);
	हाल VBG_IOCTL_HGCM_CONNECT:
		वापस vbg_ioctl_hgcm_connect(gdev, session, data);
	हाल VBG_IOCTL_HGCM_DISCONNECT:
		वापस vbg_ioctl_hgcm_disconnect(gdev, session, data);
	हाल VBG_IOCTL_WAIT_FOR_EVENTS:
		वापस vbg_ioctl_रुको_क्रम_events(gdev, session, data);
	हाल VBG_IOCTL_INTERRUPT_ALL_WAIT_FOR_EVENTS:
		वापस vbg_ioctl_पूर्णांकerrupt_all_रुको_events(gdev, session, data);
	हाल VBG_IOCTL_CHANGE_FILTER_MASK:
		वापस vbg_ioctl_change_filter_mask(gdev, session, data);
	हाल VBG_IOCTL_ACQUIRE_GUEST_CAPABILITIES:
		वापस vbg_ioctl_acquire_guest_capabilities(gdev, session, data);
	हाल VBG_IOCTL_CHANGE_GUEST_CAPABILITIES:
		वापस vbg_ioctl_change_guest_capabilities(gdev, session, data);
	हाल VBG_IOCTL_CHECK_BALLOON:
		वापस vbg_ioctl_check_balloon(gdev, data);
	हाल VBG_IOCTL_WRITE_CORE_DUMP:
		वापस vbg_ioctl_ग_लिखो_core_dump(gdev, session, data);
	पूर्ण

	/* Variable sized requests. */
	चयन (req_no_size) अणु
#अगर_घोषित CONFIG_COMPAT
	हाल VBG_IOCTL_HGCM_CALL_32(0):
		f32bit = true;
		fallthrough;
#पूर्ण_अगर
	हाल VBG_IOCTL_HGCM_CALL(0):
		वापस vbg_ioctl_hgcm_call(gdev, session, f32bit, data);
	हाल VBG_IOCTL_LOG(0):
	हाल VBG_IOCTL_LOG_ALT(0):
		वापस vbg_ioctl_log(data);
	पूर्ण

	vbg_err_ratelimited("Userspace made an unknown ioctl req %#08x\n", req);
	वापस -ENOTTY;
पूर्ण

/**
 * Report guest supported mouse-features to the host.
 *
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:		The Guest extension device.
 * @features:		The set of features to report to the host.
 */
पूर्णांक vbg_core_set_mouse_status(काष्ठा vbg_dev *gdev, u32 features)
अणु
	काष्ठा vmmdev_mouse_status *req;
	पूर्णांक rc;

	req = vbg_req_alloc(माप(*req), VMMDEVREQ_SET_MOUSE_STATUS,
			    VBG_KERNEL_REQUEST);
	अगर (!req)
		वापस -ENOMEM;

	req->mouse_features = features;
	req->poपूर्णांकer_pos_x = 0;
	req->poपूर्णांकer_pos_y = 0;

	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0)
		vbg_err("%s error, rc: %d\n", __func__, rc);

	vbg_req_मुक्त(req, माप(*req));
	वापस vbg_status_code_to_त्रुटि_सं(rc);
पूर्ण

/** Core पूर्णांकerrupt service routine. */
irqवापस_t vbg_core_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vbg_dev *gdev = dev_id;
	काष्ठा vmmdev_events *req = gdev->ack_events_req;
	bool mouse_position_changed = false;
	अचिन्हित दीर्घ flags;
	u32 events = 0;
	पूर्णांक rc;

	अगर (!gdev->mmio->V.V1_04.have_events)
		वापस IRQ_NONE;

	/* Get and acknowlegde events. */
	req->header.rc = VERR_INTERNAL_ERROR;
	req->events = 0;
	rc = vbg_req_perक्रमm(gdev, req);
	अगर (rc < 0) अणु
		vbg_err("Error performing events req, rc: %d\n", rc);
		वापस IRQ_NONE;
	पूर्ण

	events = req->events;

	अगर (events & VMMDEV_EVENT_MOUSE_POSITION_CHANGED) अणु
		mouse_position_changed = true;
		events &= ~VMMDEV_EVENT_MOUSE_POSITION_CHANGED;
	पूर्ण

	अगर (events & VMMDEV_EVENT_HGCM) अणु
		wake_up(&gdev->hgcm_wq);
		events &= ~VMMDEV_EVENT_HGCM;
	पूर्ण

	अगर (events & VMMDEV_EVENT_BALLOON_CHANGE_REQUEST) अणु
		schedule_work(&gdev->mem_balloon.work);
		events &= ~VMMDEV_EVENT_BALLOON_CHANGE_REQUEST;
	पूर्ण

	अगर (events) अणु
		spin_lock_irqsave(&gdev->event_spinlock, flags);
		gdev->pending_events |= events;
		spin_unlock_irqrestore(&gdev->event_spinlock, flags);

		wake_up(&gdev->event_wq);
	पूर्ण

	अगर (mouse_position_changed)
		vbg_linux_mouse_event(gdev);

	वापस IRQ_HANDLED;
पूर्ण
