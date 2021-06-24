<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (c) 2004-2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

/*
 * Cross Partition Communication (XPC) partition support.
 *
 *	This is the part of XPC that detects the presence/असलence of
 *	other partitions. It provides a heartbeat and monitors the
 *	heartbeats of other partitions.
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/slab.h>
#समावेश "xpc.h"
#समावेश <यंत्र/uv/uv_hub.h>

/* XPC is निकासing flag */
पूर्णांक xpc_निकासing;

/* this partition's reserved page poपूर्णांकers */
काष्ठा xpc_rsvd_page *xpc_rsvd_page;
अटल अचिन्हित दीर्घ *xpc_part_nasids;
अचिन्हित दीर्घ *xpc_mach_nasids;

अटल पूर्णांक xpc_nasid_mask_nbytes;	/* #of bytes in nasid mask */
पूर्णांक xpc_nasid_mask_nदीर्घs;	/* #of दीर्घs in nasid mask */

काष्ठा xpc_partition *xpc_partitions;

/*
 * Guarantee that the kदो_स्मृति'd memory is cacheline aligned.
 */
व्योम *
xpc_kदो_स्मृति_cacheline_aligned(माप_प्रकार size, gfp_t flags, व्योम **base)
अणु
	/* see अगर kदो_स्मृति will give us cachline aligned memory by शेष */
	*base = kदो_स्मृति(size, flags);
	अगर (*base == शून्य)
		वापस शून्य;

	अगर ((u64)*base == L1_CACHE_ALIGN((u64)*base))
		वापस *base;

	kमुक्त(*base);

	/* nope, we'll have to करो it ourselves */
	*base = kदो_स्मृति(size + L1_CACHE_BYTES, flags);
	अगर (*base == शून्य)
		वापस शून्य;

	वापस (व्योम *)L1_CACHE_ALIGN((u64)*base);
पूर्ण

/*
 * Given a nasid, get the physical address of the  partition's reserved page
 * क्रम that nasid. This function वापसs 0 on any error.
 */
अटल अचिन्हित दीर्घ
xpc_get_rsvd_page_pa(पूर्णांक nasid)
अणु
	क्रमागत xp_retval ret;
	u64 cookie = 0;
	अचिन्हित दीर्घ rp_pa = nasid;	/* seed with nasid */
	माप_प्रकार len = 0;
	माप_प्रकार buf_len = 0;
	व्योम *buf = शून्य;
	व्योम *buf_base = शून्य;
	क्रमागत xp_retval (*get_partition_rsvd_page_pa)
		(व्योम *, u64 *, अचिन्हित दीर्घ *, माप_प्रकार *) =
		xpc_arch_ops.get_partition_rsvd_page_pa;

	जबतक (1) अणु

		/* !!! rp_pa will need to be _gpa on UV.
		 * ??? So करो we save it पूर्णांकo the architecture specअगरic parts
		 * ??? of the xpc_partition काष्ठाure? Do we नाम this
		 * ??? function or have two versions? Rename rp_pa क्रम UV to
		 * ??? rp_gpa?
		 */
		ret = get_partition_rsvd_page_pa(buf, &cookie, &rp_pa, &len);

		dev_dbg(xpc_part, "SAL returned with ret=%d, cookie=0x%016lx, "
			"address=0x%016lx, len=0x%016lx\n", ret,
			(अचिन्हित दीर्घ)cookie, rp_pa, len);

		अगर (ret != xpNeedMoreInfo)
			अवरोध;

		अगर (len > buf_len) अणु
			kमुक्त(buf_base);
			buf_len = L1_CACHE_ALIGN(len);
			buf = xpc_kदो_स्मृति_cacheline_aligned(buf_len, GFP_KERNEL,
							    &buf_base);
			अगर (buf_base == शून्य) अणु
				dev_err(xpc_part, "unable to kmalloc "
					"len=0x%016lx\n", buf_len);
				ret = xpNoMemory;
				अवरोध;
			पूर्ण
		पूर्ण

		ret = xp_remote_स_नकल(xp_pa(buf), rp_pa, len);
		अगर (ret != xpSuccess) अणु
			dev_dbg(xpc_part, "xp_remote_memcpy failed %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(buf_base);

	अगर (ret != xpSuccess)
		rp_pa = 0;

	dev_dbg(xpc_part, "reserved page at phys address 0x%016lx\n", rp_pa);
	वापस rp_pa;
पूर्ण

/*
 * Fill the partition reserved page with the inक्रमmation needed by
 * other partitions to discover we are alive and establish initial
 * communications.
 */
पूर्णांक
xpc_setup_rsvd_page(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा xpc_rsvd_page *rp;
	अचिन्हित दीर्घ rp_pa;
	अचिन्हित दीर्घ new_ts_jअगरfies;

	/* get the local reserved page's address */

	preempt_disable();
	rp_pa = xpc_get_rsvd_page_pa(xp_cpu_to_nasid(smp_processor_id()));
	preempt_enable();
	अगर (rp_pa == 0) अणु
		dev_err(xpc_part, "SAL failed to locate the reserved page\n");
		वापस -ESRCH;
	पूर्ण
	rp = (काष्ठा xpc_rsvd_page *)__va(xp_socket_pa(rp_pa));

	अगर (rp->SAL_version < 3) अणु
		/* SAL_versions < 3 had a SAL_partid defined as a u8 */
		rp->SAL_partid &= 0xff;
	पूर्ण
	BUG_ON(rp->SAL_partid != xp_partition_id);

	अगर (rp->SAL_partid < 0 || rp->SAL_partid >= xp_max_npartitions) अणु
		dev_err(xpc_part, "the reserved page's partid of %d is outside "
			"supported range (< 0 || >= %d)\n", rp->SAL_partid,
			xp_max_npartitions);
		वापस -EINVAL;
	पूर्ण

	rp->version = XPC_RP_VERSION;
	rp->max_npartitions = xp_max_npartitions;

	/* establish the actual sizes of the nasid masks */
	अगर (rp->SAL_version == 1) अणु
		/* SAL_version 1 didn't set the nasids_size field */
		rp->SAL_nasids_size = 128;
	पूर्ण
	xpc_nasid_mask_nbytes = rp->SAL_nasids_size;
	xpc_nasid_mask_nदीर्घs = BITS_TO_LONGS(rp->SAL_nasids_size *
					      BITS_PER_BYTE);

	/* setup the poपूर्णांकers to the various items in the reserved page */
	xpc_part_nasids = XPC_RP_PART_NASIDS(rp);
	xpc_mach_nasids = XPC_RP_MACH_NASIDS(rp);

	ret = xpc_arch_ops.setup_rsvd_page(rp);
	अगर (ret != 0)
		वापस ret;

	/*
	 * Set बारtamp of when reserved page was setup by XPC.
	 * This signअगरies to the remote partition that our reserved
	 * page is initialized.
	 */
	new_ts_jअगरfies = jअगरfies;
	अगर (new_ts_jअगरfies == 0 || new_ts_jअगरfies == rp->ts_jअगरfies)
		new_ts_jअगरfies++;
	rp->ts_jअगरfies = new_ts_jअगरfies;

	xpc_rsvd_page = rp;
	वापस 0;
पूर्ण

व्योम
xpc_tearकरोwn_rsvd_page(व्योम)
अणु
	/* a zero बारtamp indicates our rsvd page is not initialized */
	xpc_rsvd_page->ts_jअगरfies = 0;
पूर्ण

/*
 * Get a copy of a portion of the remote partition's rsvd page.
 *
 * remote_rp poपूर्णांकs to a buffer that is cacheline aligned क्रम BTE copies and
 * is large enough to contain a copy of their reserved page header and
 * part_nasids mask.
 */
क्रमागत xp_retval
xpc_get_remote_rp(पूर्णांक nasid, अचिन्हित दीर्घ *discovered_nasids,
		  काष्ठा xpc_rsvd_page *remote_rp, अचिन्हित दीर्घ *remote_rp_pa)
अणु
	पूर्णांक l;
	क्रमागत xp_retval ret;

	/* get the reserved page's physical address */

	*remote_rp_pa = xpc_get_rsvd_page_pa(nasid);
	अगर (*remote_rp_pa == 0)
		वापस xpNoRsvdPageAddr;

	/* pull over the reserved page header and part_nasids mask */
	ret = xp_remote_स_नकल(xp_pa(remote_rp), *remote_rp_pa,
			       XPC_RP_HEADER_SIZE + xpc_nasid_mask_nbytes);
	अगर (ret != xpSuccess)
		वापस ret;

	अगर (discovered_nasids != शून्य) अणु
		अचिन्हित दीर्घ *remote_part_nasids =
		    XPC_RP_PART_NASIDS(remote_rp);

		क्रम (l = 0; l < xpc_nasid_mask_nदीर्घs; l++)
			discovered_nasids[l] |= remote_part_nasids[l];
	पूर्ण

	/* zero बारtamp indicates the reserved page has not been setup */
	अगर (remote_rp->ts_jअगरfies == 0)
		वापस xpRsvdPageNotSet;

	अगर (XPC_VERSION_MAJOR(remote_rp->version) !=
	    XPC_VERSION_MAJOR(XPC_RP_VERSION)) अणु
		वापस xpBadVersion;
	पूर्ण

	/* check that both remote and local partids are valid क्रम each side */
	अगर (remote_rp->SAL_partid < 0 ||
	    remote_rp->SAL_partid >= xp_max_npartitions ||
	    remote_rp->max_npartitions <= xp_partition_id) अणु
		वापस xpInvalidPartid;
	पूर्ण

	अगर (remote_rp->SAL_partid == xp_partition_id)
		वापस xpLocalPartid;

	वापस xpSuccess;
पूर्ण

/*
 * See अगर the other side has responded to a partition deactivate request
 * from us. Though we requested the remote partition to deactivate with regard
 * to us, we really only need to रुको क्रम the other side to disengage from us.
 */
अटल पूर्णांक __xpc_partition_disengaged(काष्ठा xpc_partition *part,
				      bool from_समयr)
अणु
	लघु partid = XPC_PARTID(part);
	पूर्णांक disengaged;

	disengaged = !xpc_arch_ops.partition_engaged(partid);
	अगर (part->disengage_समयout) अणु
		अगर (!disengaged) अणु
			अगर (समय_is_after_jअगरfies(part->disengage_समयout)) अणु
				/* समयlimit hasn't been reached yet */
				वापस 0;
			पूर्ण

			/*
			 * Other side hasn't responded to our deactivate
			 * request in a समयly fashion, so assume it's dead.
			 */

			dev_info(xpc_part, "deactivate request to remote "
				 "partition %d timed out\n", partid);
			xpc_disengage_समयकरोut = 1;
			xpc_arch_ops.assume_partition_disengaged(partid);
			disengaged = 1;
		पूर्ण
		part->disengage_समयout = 0;

		/* Cancel the समयr function अगर not called from it */
		अगर (!from_समयr)
			del_समयr_sync(&part->disengage_समयr);

		DBUG_ON(part->act_state != XPC_P_AS_DEACTIVATING &&
			part->act_state != XPC_P_AS_INACTIVE);
		अगर (part->act_state != XPC_P_AS_INACTIVE)
			xpc_wakeup_channel_mgr(part);

		xpc_arch_ops.cancel_partition_deactivation_request(part);
	पूर्ण
	वापस disengaged;
पूर्ण

पूर्णांक xpc_partition_disengaged(काष्ठा xpc_partition *part)
अणु
	वापस __xpc_partition_disengaged(part, false);
पूर्ण

पूर्णांक xpc_partition_disengaged_from_समयr(काष्ठा xpc_partition *part)
अणु
	वापस __xpc_partition_disengaged(part, true);
पूर्ण

/*
 * Mark specअगरied partition as active.
 */
क्रमागत xp_retval
xpc_mark_partition_active(काष्ठा xpc_partition *part)
अणु
	अचिन्हित दीर्घ irq_flags;
	क्रमागत xp_retval ret;

	dev_dbg(xpc_part, "setting partition %d to ACTIVE\n", XPC_PARTID(part));

	spin_lock_irqsave(&part->act_lock, irq_flags);
	अगर (part->act_state == XPC_P_AS_ACTIVATING) अणु
		part->act_state = XPC_P_AS_ACTIVE;
		ret = xpSuccess;
	पूर्ण अन्यथा अणु
		DBUG_ON(part->reason == xpSuccess);
		ret = part->reason;
	पूर्ण
	spin_unlock_irqrestore(&part->act_lock, irq_flags);

	वापस ret;
पूर्ण

/*
 * Start the process of deactivating the specअगरied partition.
 */
व्योम
xpc_deactivate_partition(स्थिर पूर्णांक line, काष्ठा xpc_partition *part,
			 क्रमागत xp_retval reason)
अणु
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&part->act_lock, irq_flags);

	अगर (part->act_state == XPC_P_AS_INACTIVE) अणु
		XPC_SET_REASON(part, reason, line);
		spin_unlock_irqrestore(&part->act_lock, irq_flags);
		अगर (reason == xpReactivating) अणु
			/* we पूर्णांकerrupt ourselves to reactivate partition */
			xpc_arch_ops.request_partition_reactivation(part);
		पूर्ण
		वापस;
	पूर्ण
	अगर (part->act_state == XPC_P_AS_DEACTIVATING) अणु
		अगर ((part->reason == xpUnloading && reason != xpUnloading) ||
		    reason == xpReactivating) अणु
			XPC_SET_REASON(part, reason, line);
		पूर्ण
		spin_unlock_irqrestore(&part->act_lock, irq_flags);
		वापस;
	पूर्ण

	part->act_state = XPC_P_AS_DEACTIVATING;
	XPC_SET_REASON(part, reason, line);

	spin_unlock_irqrestore(&part->act_lock, irq_flags);

	/* ask remote partition to deactivate with regard to us */
	xpc_arch_ops.request_partition_deactivation(part);

	/* set a समयlimit on the disengage phase of the deactivation request */
	part->disengage_समयout = jअगरfies + (xpc_disengage_समयlimit * HZ);
	part->disengage_समयr.expires = part->disengage_समयout;
	add_समयr(&part->disengage_समयr);

	dev_dbg(xpc_part, "bringing partition %d down, reason = %d\n",
		XPC_PARTID(part), reason);

	xpc_partition_going_करोwn(part, reason);
पूर्ण

/*
 * Mark specअगरied partition as inactive.
 */
व्योम
xpc_mark_partition_inactive(काष्ठा xpc_partition *part)
अणु
	अचिन्हित दीर्घ irq_flags;

	dev_dbg(xpc_part, "setting partition %d to INACTIVE\n",
		XPC_PARTID(part));

	spin_lock_irqsave(&part->act_lock, irq_flags);
	part->act_state = XPC_P_AS_INACTIVE;
	spin_unlock_irqrestore(&part->act_lock, irq_flags);
	part->remote_rp_pa = 0;
पूर्ण

/*
 * SAL has provided a partition and machine mask.  The partition mask
 * contains a bit क्रम each even nasid in our partition.  The machine
 * mask contains a bit क्रम each even nasid in the entire machine.
 *
 * Using those two bit arrays, we can determine which nasids are
 * known in the machine.  Each should also have a reserved page
 * initialized अगर they are available क्रम partitioning.
 */
व्योम
xpc_discovery(व्योम)
अणु
	व्योम *remote_rp_base;
	काष्ठा xpc_rsvd_page *remote_rp;
	अचिन्हित दीर्घ remote_rp_pa;
	पूर्णांक region;
	पूर्णांक region_size;
	पूर्णांक max_regions;
	पूर्णांक nasid;
	अचिन्हित दीर्घ *discovered_nasids;
	क्रमागत xp_retval ret;

	remote_rp = xpc_kदो_स्मृति_cacheline_aligned(XPC_RP_HEADER_SIZE +
						  xpc_nasid_mask_nbytes,
						  GFP_KERNEL, &remote_rp_base);
	अगर (remote_rp == शून्य)
		वापस;

	discovered_nasids = kसुस्मृति(xpc_nasid_mask_nदीर्घs, माप(दीर्घ),
				    GFP_KERNEL);
	अगर (discovered_nasids == शून्य) अणु
		kमुक्त(remote_rp_base);
		वापस;
	पूर्ण

	/*
	 * The term 'region' in this context refers to the minimum number of
	 * nodes that can comprise an access protection grouping. The access
	 * protection is in regards to memory, IOI and IPI.
	 */
	region_size = xp_region_size;

	अगर (is_uv_प्रणाली())
		max_regions = 256;
	अन्यथा अणु
		max_regions = 64;

		चयन (region_size) अणु
		हाल 128:
			max_regions *= 2;
			fallthrough;
		हाल 64:
			max_regions *= 2;
			fallthrough;
		हाल 32:
			max_regions *= 2;
			region_size = 16;
		पूर्ण
	पूर्ण

	क्रम (region = 0; region < max_regions; region++) अणु

		अगर (xpc_निकासing)
			अवरोध;

		dev_dbg(xpc_part, "searching region %d\n", region);

		क्रम (nasid = (region * region_size * 2);
		     nasid < ((region + 1) * region_size * 2); nasid += 2) अणु

			अगर (xpc_निकासing)
				अवरोध;

			dev_dbg(xpc_part, "checking nasid %d\n", nasid);

			अगर (test_bit(nasid / 2, xpc_part_nasids)) अणु
				dev_dbg(xpc_part, "PROM indicates Nasid %d is "
					"part of the local partition; skipping "
					"region\n", nasid);
				अवरोध;
			पूर्ण

			अगर (!(test_bit(nasid / 2, xpc_mach_nasids))) अणु
				dev_dbg(xpc_part, "PROM indicates Nasid %d was "
					"not on Numa-Link network at reset\n",
					nasid);
				जारी;
			पूर्ण

			अगर (test_bit(nasid / 2, discovered_nasids)) अणु
				dev_dbg(xpc_part, "Nasid %d is part of a "
					"partition which was previously "
					"discovered\n", nasid);
				जारी;
			पूर्ण

			/* pull over the rsvd page header & part_nasids mask */

			ret = xpc_get_remote_rp(nasid, discovered_nasids,
						remote_rp, &remote_rp_pa);
			अगर (ret != xpSuccess) अणु
				dev_dbg(xpc_part, "unable to get reserved page "
					"from nasid %d, reason=%d\n", nasid,
					ret);

				अगर (ret == xpLocalPartid)
					अवरोध;

				जारी;
			पूर्ण

			xpc_arch_ops.request_partition_activation(remote_rp,
							 remote_rp_pa, nasid);
		पूर्ण
	पूर्ण

	kमुक्त(discovered_nasids);
	kमुक्त(remote_rp_base);
पूर्ण

/*
 * Given a partid, get the nasids owned by that partition from the
 * remote partition's reserved page.
 */
क्रमागत xp_retval
xpc_initiate_partid_to_nasids(लघु partid, व्योम *nasid_mask)
अणु
	काष्ठा xpc_partition *part;
	अचिन्हित दीर्घ part_nasid_pa;

	part = &xpc_partitions[partid];
	अगर (part->remote_rp_pa == 0)
		वापस xpPartitionDown;

	स_रखो(nasid_mask, 0, xpc_nasid_mask_nbytes);

	part_nasid_pa = (अचिन्हित दीर्घ)XPC_RP_PART_NASIDS(part->remote_rp_pa);

	वापस xp_remote_स_नकल(xp_pa(nasid_mask), part_nasid_pa,
				xpc_nasid_mask_nbytes);
पूर्ण
