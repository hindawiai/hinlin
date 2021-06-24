<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 IBM Corp.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>

#समावेश "cxl.h"
#समावेश "hcalls.h"
#समावेश "trace.h"

#घोषणा CXL_ERROR_DETECTED_EVENT	1
#घोषणा CXL_SLOT_RESET_EVENT		2
#घोषणा CXL_RESUME_EVENT		3

अटल व्योम pci_error_handlers(काष्ठा cxl_afu *afu,
				पूर्णांक bus_error_event,
				pci_channel_state_t state)
अणु
	काष्ठा pci_dev *afu_dev;

	अगर (afu->phb == शून्य)
		वापस;

	list_क्रम_each_entry(afu_dev, &afu->phb->bus->devices, bus_list) अणु
		अगर (!afu_dev->driver)
			जारी;

		चयन (bus_error_event) अणु
		हाल CXL_ERROR_DETECTED_EVENT:
			afu_dev->error_state = state;

			अगर (afu_dev->driver->err_handler &&
			    afu_dev->driver->err_handler->error_detected)
				afu_dev->driver->err_handler->error_detected(afu_dev, state);
		अवरोध;
		हाल CXL_SLOT_RESET_EVENT:
			afu_dev->error_state = state;

			अगर (afu_dev->driver->err_handler &&
			    afu_dev->driver->err_handler->slot_reset)
				afu_dev->driver->err_handler->slot_reset(afu_dev);
		अवरोध;
		हाल CXL_RESUME_EVENT:
			अगर (afu_dev->driver->err_handler &&
			    afu_dev->driver->err_handler->resume)
				afu_dev->driver->err_handler->resume(afu_dev);
		अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t guest_handle_psl_slice_error(काष्ठा cxl_context *ctx, u64 dsisr,
					u64 errstat)
अणु
	pr_devel("in %s\n", __func__);
	dev_crit(&ctx->afu->dev, "PSL ERROR STATUS: 0x%.16llx\n", errstat);

	वापस cxl_ops->ack_irq(ctx, 0, errstat);
पूर्ण

अटल sमाप_प्रकार guest_collect_vpd(काष्ठा cxl *adapter, काष्ठा cxl_afu *afu,
			व्योम *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक entries, mod;
	अचिन्हित दीर्घ **vpd_buf = शून्य;
	काष्ठा sg_list *le;
	पूर्णांक rc = 0, i, tocopy;
	u64 out = 0;

	अगर (buf == शून्य)
		वापस -EINVAL;

	/* number of entries in the list */
	entries = len / SG_BUFFER_SIZE;
	mod = len % SG_BUFFER_SIZE;
	अगर (mod)
		entries++;

	अगर (entries > SG_MAX_ENTRIES) अणु
		entries = SG_MAX_ENTRIES;
		len = SG_MAX_ENTRIES * SG_BUFFER_SIZE;
		mod = 0;
	पूर्ण

	vpd_buf = kसुस्मृति(entries, माप(अचिन्हित दीर्घ *), GFP_KERNEL);
	अगर (!vpd_buf)
		वापस -ENOMEM;

	le = (काष्ठा sg_list *)get_zeroed_page(GFP_KERNEL);
	अगर (!le) अणु
		rc = -ENOMEM;
		जाओ err1;
	पूर्ण

	क्रम (i = 0; i < entries; i++) अणु
		vpd_buf[i] = (अचिन्हित दीर्घ *)get_zeroed_page(GFP_KERNEL);
		अगर (!vpd_buf[i]) अणु
			rc = -ENOMEM;
			जाओ err2;
		पूर्ण
		le[i].phys_addr = cpu_to_be64(virt_to_phys(vpd_buf[i]));
		le[i].len = cpu_to_be64(SG_BUFFER_SIZE);
		अगर ((i == (entries - 1)) && mod)
			le[i].len = cpu_to_be64(mod);
	पूर्ण

	अगर (adapter)
		rc = cxl_h_collect_vpd_adapter(adapter->guest->handle,
					virt_to_phys(le), entries, &out);
	अन्यथा
		rc = cxl_h_collect_vpd(afu->guest->handle, 0,
				virt_to_phys(le), entries, &out);
	pr_devel("length of available (entries: %i), vpd: %#llx\n",
		entries, out);

	अगर (!rc) अणु
		/*
		 * hcall वापसs in 'out' the size of available VPDs.
		 * It fills the buffer with as much data as possible.
		 */
		अगर (out < len)
			len = out;
		rc = len;
		अगर (out) अणु
			क्रम (i = 0; i < entries; i++) अणु
				अगर (len < SG_BUFFER_SIZE)
					tocopy = len;
				अन्यथा
					tocopy = SG_BUFFER_SIZE;
				स_नकल(buf, vpd_buf[i], tocopy);
				buf += tocopy;
				len -= tocopy;
			पूर्ण
		पूर्ण
	पूर्ण
err2:
	क्रम (i = 0; i < entries; i++) अणु
		अगर (vpd_buf[i])
			मुक्त_page((अचिन्हित दीर्घ) vpd_buf[i]);
	पूर्ण
	मुक्त_page((अचिन्हित दीर्घ) le);
err1:
	kमुक्त(vpd_buf);
	वापस rc;
पूर्ण

अटल पूर्णांक guest_get_irq_info(काष्ठा cxl_context *ctx, काष्ठा cxl_irq_info *info)
अणु
	वापस cxl_h_collect_पूर्णांक_info(ctx->afu->guest->handle, ctx->process_token, info);
पूर्ण

अटल irqवापस_t guest_psl_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cxl_context *ctx = data;
	काष्ठा cxl_irq_info irq_info;
	पूर्णांक rc;

	pr_devel("%d: received PSL interrupt %i\n", ctx->pe, irq);
	rc = guest_get_irq_info(ctx, &irq_info);
	अगर (rc) अणु
		WARN(1, "Unable to get IRQ info: %i\n", rc);
		वापस IRQ_HANDLED;
	पूर्ण

	rc = cxl_irq_psl8(irq, ctx, &irq_info);
	वापस rc;
पूर्ण

अटल पूर्णांक afu_पढ़ो_error_state(काष्ठा cxl_afu *afu, पूर्णांक *state_out)
अणु
	u64 state;
	पूर्णांक rc = 0;

	अगर (!afu)
		वापस -EIO;

	rc = cxl_h_पढ़ो_error_state(afu->guest->handle, &state);
	अगर (!rc) अणु
		WARN_ON(state != H_STATE_NORMAL &&
			state != H_STATE_DISABLE &&
			state != H_STATE_TEMP_UNAVAILABLE &&
			state != H_STATE_PERM_UNAVAILABLE);
		*state_out = state & 0xffffffff;
	पूर्ण
	वापस rc;
पूर्ण

अटल irqवापस_t guest_slice_irq_err(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cxl_afu *afu = data;
	पूर्णांक rc;
	u64 serr, afu_error, dsisr;

	rc = cxl_h_get_fn_error_पूर्णांकerrupt(afu->guest->handle, &serr);
	अगर (rc) अणु
		dev_crit(&afu->dev, "Couldn't read PSL_SERR_An: %d\n", rc);
		वापस IRQ_HANDLED;
	पूर्ण
	afu_error = cxl_p2n_पढ़ो(afu, CXL_AFU_ERR_An);
	dsisr = cxl_p2n_पढ़ो(afu, CXL_PSL_DSISR_An);
	cxl_afu_decode_psl_serr(afu, serr);
	dev_crit(&afu->dev, "AFU_ERR_An: 0x%.16llx\n", afu_error);
	dev_crit(&afu->dev, "PSL_DSISR_An: 0x%.16llx\n", dsisr);

	rc = cxl_h_ack_fn_error_पूर्णांकerrupt(afu->guest->handle, serr);
	अगर (rc)
		dev_crit(&afu->dev, "Couldn't ack slice error interrupt: %d\n",
			rc);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक irq_alloc_range(काष्ठा cxl *adapter, पूर्णांक len, पूर्णांक *irq)
अणु
	पूर्णांक i, n;
	काष्ठा irq_avail *cur;

	क्रम (i = 0; i < adapter->guest->irq_nranges; i++) अणु
		cur = &adapter->guest->irq_avail[i];
		n = biपंचांगap_find_next_zero_area(cur->biपंचांगap, cur->range,
					0, len, 0);
		अगर (n < cur->range) अणु
			biपंचांगap_set(cur->biपंचांगap, n, len);
			*irq = cur->offset + n;
			pr_devel("guest: allocate IRQs %#x->%#x\n",
				*irq, *irq + len - 1);

			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक irq_मुक्त_range(काष्ठा cxl *adapter, पूर्णांक irq, पूर्णांक len)
अणु
	पूर्णांक i, n;
	काष्ठा irq_avail *cur;

	अगर (len == 0)
		वापस -ENOENT;

	क्रम (i = 0; i < adapter->guest->irq_nranges; i++) अणु
		cur = &adapter->guest->irq_avail[i];
		अगर (irq >= cur->offset &&
			(irq + len) <= (cur->offset + cur->range)) अणु
			n = irq - cur->offset;
			biपंचांगap_clear(cur->biपंचांगap, n, len);
			pr_devel("guest: release IRQs %#x->%#x\n",
				irq, irq + len - 1);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक guest_reset(काष्ठा cxl *adapter)
अणु
	काष्ठा cxl_afu *afu = शून्य;
	पूर्णांक i, rc;

	pr_devel("Adapter reset request\n");
	spin_lock(&adapter->afu_list_lock);
	क्रम (i = 0; i < adapter->slices; i++) अणु
		अगर ((afu = adapter->afu[i])) अणु
			pci_error_handlers(afu, CXL_ERROR_DETECTED_EVENT,
					pci_channel_io_frozen);
			cxl_context_detach_all(afu);
		पूर्ण
	पूर्ण

	rc = cxl_h_reset_adapter(adapter->guest->handle);
	क्रम (i = 0; i < adapter->slices; i++) अणु
		अगर (!rc && (afu = adapter->afu[i])) अणु
			pci_error_handlers(afu, CXL_SLOT_RESET_EVENT,
					pci_channel_io_normal);
			pci_error_handlers(afu, CXL_RESUME_EVENT, 0);
		पूर्ण
	पूर्ण
	spin_unlock(&adapter->afu_list_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक guest_alloc_one_irq(काष्ठा cxl *adapter)
अणु
	पूर्णांक irq;

	spin_lock(&adapter->guest->irq_alloc_lock);
	अगर (irq_alloc_range(adapter, 1, &irq))
		irq = -ENOSPC;
	spin_unlock(&adapter->guest->irq_alloc_lock);
	वापस irq;
पूर्ण

अटल व्योम guest_release_one_irq(काष्ठा cxl *adapter, पूर्णांक irq)
अणु
	spin_lock(&adapter->guest->irq_alloc_lock);
	irq_मुक्त_range(adapter, irq, 1);
	spin_unlock(&adapter->guest->irq_alloc_lock);
पूर्ण

अटल पूर्णांक guest_alloc_irq_ranges(काष्ठा cxl_irq_ranges *irqs,
				काष्ठा cxl *adapter, अचिन्हित पूर्णांक num)
अणु
	पूर्णांक i, try, irq;

	स_रखो(irqs, 0, माप(काष्ठा cxl_irq_ranges));

	spin_lock(&adapter->guest->irq_alloc_lock);
	क्रम (i = 0; i < CXL_IRQ_RANGES && num; i++) अणु
		try = num;
		जबतक (try) अणु
			अगर (irq_alloc_range(adapter, try, &irq) == 0)
				अवरोध;
			try /= 2;
		पूर्ण
		अगर (!try)
			जाओ error;
		irqs->offset[i] = irq;
		irqs->range[i] = try;
		num -= try;
	पूर्ण
	अगर (num)
		जाओ error;
	spin_unlock(&adapter->guest->irq_alloc_lock);
	वापस 0;

error:
	क्रम (i = 0; i < CXL_IRQ_RANGES; i++)
		irq_मुक्त_range(adapter, irqs->offset[i], irqs->range[i]);
	spin_unlock(&adapter->guest->irq_alloc_lock);
	वापस -ENOSPC;
पूर्ण

अटल व्योम guest_release_irq_ranges(काष्ठा cxl_irq_ranges *irqs,
				काष्ठा cxl *adapter)
अणु
	पूर्णांक i;

	spin_lock(&adapter->guest->irq_alloc_lock);
	क्रम (i = 0; i < CXL_IRQ_RANGES; i++)
		irq_मुक्त_range(adapter, irqs->offset[i], irqs->range[i]);
	spin_unlock(&adapter->guest->irq_alloc_lock);
पूर्ण

अटल पूर्णांक guest_रेजिस्टर_serr_irq(काष्ठा cxl_afu *afu)
अणु
	afu->err_irq_name = kaप्र_लिखो(GFP_KERNEL, "cxl-%s-err",
				      dev_name(&afu->dev));
	अगर (!afu->err_irq_name)
		वापस -ENOMEM;

	अगर (!(afu->serr_virq = cxl_map_irq(afu->adapter, afu->serr_hwirq,
				 guest_slice_irq_err, afu, afu->err_irq_name))) अणु
		kमुक्त(afu->err_irq_name);
		afu->err_irq_name = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम guest_release_serr_irq(काष्ठा cxl_afu *afu)
अणु
	cxl_unmap_irq(afu->serr_virq, afu);
	cxl_ops->release_one_irq(afu->adapter, afu->serr_hwirq);
	kमुक्त(afu->err_irq_name);
पूर्ण

अटल पूर्णांक guest_ack_irq(काष्ठा cxl_context *ctx, u64 tfc, u64 psl_reset_mask)
अणु
	वापस cxl_h_control_faults(ctx->afu->guest->handle, ctx->process_token,
				tfc >> 32, (psl_reset_mask != 0));
पूर्ण

अटल व्योम disable_afu_irqs(काष्ठा cxl_context *ctx)
अणु
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक virq;
	पूर्णांक r, i;

	pr_devel("Disabling AFU(%d) interrupts\n", ctx->afu->slice);
	क्रम (r = 0; r < CXL_IRQ_RANGES; r++) अणु
		hwirq = ctx->irqs.offset[r];
		क्रम (i = 0; i < ctx->irqs.range[r]; hwirq++, i++) अणु
			virq = irq_find_mapping(शून्य, hwirq);
			disable_irq(virq);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम enable_afu_irqs(काष्ठा cxl_context *ctx)
अणु
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक virq;
	पूर्णांक r, i;

	pr_devel("Enabling AFU(%d) interrupts\n", ctx->afu->slice);
	क्रम (r = 0; r < CXL_IRQ_RANGES; r++) अणु
		hwirq = ctx->irqs.offset[r];
		क्रम (i = 0; i < ctx->irqs.range[r]; hwirq++, i++) अणु
			virq = irq_find_mapping(शून्य, hwirq);
			enable_irq(virq);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक _guest_afu_cr_पढ़ोXX(पूर्णांक sz, काष्ठा cxl_afu *afu, पूर्णांक cr_idx,
			u64 offset, u64 *val)
अणु
	अचिन्हित दीर्घ cr;
	अक्षर c;
	पूर्णांक rc = 0;

	अगर (afu->crs_len < sz)
		वापस -ENOENT;

	अगर (unlikely(offset >= afu->crs_len))
		वापस -दुस्फल;

	cr = get_zeroed_page(GFP_KERNEL);
	अगर (!cr)
		वापस -ENOMEM;

	rc = cxl_h_get_config(afu->guest->handle, cr_idx, offset,
			virt_to_phys((व्योम *)cr), sz);
	अगर (rc)
		जाओ err;

	चयन (sz) अणु
	हाल 1:
		c = *((अक्षर *) cr);
		*val = c;
		अवरोध;
	हाल 2:
		*val = in_le16((u16 *)cr);
		अवरोध;
	हाल 4:
		*val = in_le32((अचिन्हित *)cr);
		अवरोध;
	हाल 8:
		*val = in_le64((u64 *)cr);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
err:
	मुक्त_page(cr);
	वापस rc;
पूर्ण

अटल पूर्णांक guest_afu_cr_पढ़ो32(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset,
			u32 *out)
अणु
	पूर्णांक rc;
	u64 val;

	rc = _guest_afu_cr_पढ़ोXX(4, afu, cr_idx, offset, &val);
	अगर (!rc)
		*out = (u32) val;
	वापस rc;
पूर्ण

अटल पूर्णांक guest_afu_cr_पढ़ो16(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset,
			u16 *out)
अणु
	पूर्णांक rc;
	u64 val;

	rc = _guest_afu_cr_पढ़ोXX(2, afu, cr_idx, offset, &val);
	अगर (!rc)
		*out = (u16) val;
	वापस rc;
पूर्ण

अटल पूर्णांक guest_afu_cr_पढ़ो8(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset,
			u8 *out)
अणु
	पूर्णांक rc;
	u64 val;

	rc = _guest_afu_cr_पढ़ोXX(1, afu, cr_idx, offset, &val);
	अगर (!rc)
		*out = (u8) val;
	वापस rc;
पूर्ण

अटल पूर्णांक guest_afu_cr_पढ़ो64(काष्ठा cxl_afu *afu, पूर्णांक cr_idx, u64 offset,
			u64 *out)
अणु
	वापस _guest_afu_cr_पढ़ोXX(8, afu, cr_idx, offset, out);
पूर्ण

अटल पूर्णांक guest_afu_cr_ग_लिखो32(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u32 in)
अणु
	/* config record is not writable from guest */
	वापस -EPERM;
पूर्ण

अटल पूर्णांक guest_afu_cr_ग_लिखो16(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u16 in)
अणु
	/* config record is not writable from guest */
	वापस -EPERM;
पूर्ण

अटल पूर्णांक guest_afu_cr_ग_लिखो8(काष्ठा cxl_afu *afu, पूर्णांक cr, u64 off, u8 in)
अणु
	/* config record is not writable from guest */
	वापस -EPERM;
पूर्ण

अटल पूर्णांक attach_afu_directed(काष्ठा cxl_context *ctx, u64 wed, u64 amr)
अणु
	काष्ठा cxl_process_element_hcall *elem;
	काष्ठा cxl *adapter = ctx->afu->adapter;
	स्थिर काष्ठा cred *cred;
	u32 pid, idx;
	पूर्णांक rc, r, i;
	u64 mmio_addr, mmio_size;
	__be64 flags = 0;

	/* Must be 8 byte aligned and cannot cross a 4096 byte boundary */
	अगर (!(elem = (काष्ठा cxl_process_element_hcall *)
			get_zeroed_page(GFP_KERNEL)))
		वापस -ENOMEM;

	elem->version = cpu_to_be64(CXL_PROCESS_ELEMENT_VERSION);
	अगर (ctx->kernel) अणु
		pid = 0;
		flags |= CXL_PE_TRANSLATION_ENABLED;
		flags |= CXL_PE_PRIVILEGED_PROCESS;
		अगर (mfmsr() & MSR_SF)
			flags |= CXL_PE_64_BIT;
	पूर्ण अन्यथा अणु
		pid = current->pid;
		flags |= CXL_PE_PROBLEM_STATE;
		flags |= CXL_PE_TRANSLATION_ENABLED;
		अगर (!test_tsk_thपढ़ो_flag(current, TIF_32BIT))
			flags |= CXL_PE_64_BIT;
		cred = get_current_cred();
		अगर (uid_eq(cred->euid, GLOBAL_ROOT_UID))
			flags |= CXL_PE_PRIVILEGED_PROCESS;
		put_cred(cred);
	पूर्ण
	elem->flags         = cpu_to_be64(flags);
	elem->common.tid    = cpu_to_be32(0); /* Unused */
	elem->common.pid    = cpu_to_be32(pid);
	elem->common.csrp   = cpu_to_be64(0); /* disable */
	elem->common.u.psl8.aurp0  = cpu_to_be64(0); /* disable */
	elem->common.u.psl8.aurp1  = cpu_to_be64(0); /* disable */

	cxl_prefault(ctx, wed);

	elem->common.u.psl8.sstp0  = cpu_to_be64(ctx->sstp0);
	elem->common.u.psl8.sstp1  = cpu_to_be64(ctx->sstp1);

	/*
	 * Ensure we have at least one पूर्णांकerrupt allocated to take faults क्रम
	 * kernel contexts that may not have allocated any AFU IRQs at all:
	 */
	अगर (ctx->irqs.range[0] == 0) अणु
		rc = afu_रेजिस्टर_irqs(ctx, 0);
		अगर (rc)
			जाओ out_मुक्त;
	पूर्ण

	क्रम (r = 0; r < CXL_IRQ_RANGES; r++) अणु
		क्रम (i = 0; i < ctx->irqs.range[r]; i++) अणु
			अगर (r == 0 && i == 0) अणु
				elem->pslVirtualIsn = cpu_to_be32(ctx->irqs.offset[0]);
			पूर्ण अन्यथा अणु
				idx = ctx->irqs.offset[r] + i - adapter->guest->irq_base_offset;
				elem->applicationVirtualIsnBiपंचांगap[idx / 8] |= 0x80 >> (idx % 8);
			पूर्ण
		पूर्ण
	पूर्ण
	elem->common.amr = cpu_to_be64(amr);
	elem->common.wed = cpu_to_be64(wed);

	disable_afu_irqs(ctx);

	rc = cxl_h_attach_process(ctx->afu->guest->handle, elem,
				&ctx->process_token, &mmio_addr, &mmio_size);
	अगर (rc == H_SUCCESS) अणु
		अगर (ctx->master || !ctx->afu->pp_psa) अणु
			ctx->psn_phys = ctx->afu->psn_phys;
			ctx->psn_size = ctx->afu->adapter->ps_size;
		पूर्ण अन्यथा अणु
			ctx->psn_phys = mmio_addr;
			ctx->psn_size = mmio_size;
		पूर्ण
		अगर (ctx->afu->pp_psa && mmio_size &&
			ctx->afu->pp_size == 0) अणु
			/*
			 * There's no property in the device tree to पढ़ो the
			 * pp_size. We only find out at the 1st attach.
			 * Compared to bare-metal, it is too late and we
			 * should really lock here. However, on घातerVM,
			 * pp_size is really only used to display in /sys.
			 * Being discussed with pHyp क्रम their next release.
			 */
			ctx->afu->pp_size = mmio_size;
		पूर्ण
		/* from PAPR: process element is bytes 4-7 of process token */
		ctx->बाह्यal_pe = ctx->process_token & 0xFFFFFFFF;
		pr_devel("CXL pe=%i is known as %i for pHyp, mmio_size=%#llx",
			ctx->pe, ctx->बाह्यal_pe, ctx->psn_size);
		ctx->pe_inserted = true;
		enable_afu_irqs(ctx);
	पूर्ण

out_मुक्त:
	मुक्त_page((u64)elem);
	वापस rc;
पूर्ण

अटल पूर्णांक guest_attach_process(काष्ठा cxl_context *ctx, bool kernel, u64 wed, u64 amr)
अणु
	pr_devel("in %s\n", __func__);

	ctx->kernel = kernel;
	अगर (ctx->afu->current_mode == CXL_MODE_सूचीECTED)
		वापस attach_afu_directed(ctx, wed, amr);

	/* dedicated mode not supported on FW840 */

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक detach_afu_directed(काष्ठा cxl_context *ctx)
अणु
	अगर (!ctx->pe_inserted)
		वापस 0;
	अगर (cxl_h_detach_process(ctx->afu->guest->handle, ctx->process_token))
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक guest_detach_process(काष्ठा cxl_context *ctx)
अणु
	pr_devel("in %s\n", __func__);
	trace_cxl_detach(ctx);

	अगर (!cxl_ops->link_ok(ctx->afu->adapter, ctx->afu))
		वापस -EIO;

	अगर (ctx->afu->current_mode == CXL_MODE_सूचीECTED)
		वापस detach_afu_directed(ctx);

	वापस -EINVAL;
पूर्ण

अटल व्योम guest_release_afu(काष्ठा device *dev)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(dev);

	pr_devel("%s\n", __func__);

	idr_destroy(&afu->contexts_idr);

	kमुक्त(afu->guest);
	kमुक्त(afu);
पूर्ण

sमाप_प्रकार cxl_guest_पढ़ो_afu_vpd(काष्ठा cxl_afu *afu, व्योम *buf, माप_प्रकार len)
अणु
	वापस guest_collect_vpd(शून्य, afu, buf, len);
पूर्ण

#घोषणा ERR_BUFF_MAX_COPY_SIZE PAGE_SIZE
अटल sमाप_प्रकार guest_afu_पढ़ो_err_buffer(काष्ठा cxl_afu *afu, अक्षर *buf,
					loff_t off, माप_प्रकार count)
अणु
	व्योम *tbuf = शून्य;
	पूर्णांक rc = 0;

	tbuf = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!tbuf)
		वापस -ENOMEM;

	rc = cxl_h_get_afu_err(afu->guest->handle,
			       off & 0x7,
			       virt_to_phys(tbuf),
			       count);
	अगर (rc)
		जाओ err;

	अगर (count > ERR_BUFF_MAX_COPY_SIZE)
		count = ERR_BUFF_MAX_COPY_SIZE - (off & 0x7);
	स_नकल(buf, tbuf, count);
err:
	मुक्त_page((u64)tbuf);

	वापस rc;
पूर्ण

अटल पूर्णांक guest_afu_check_and_enable(काष्ठा cxl_afu *afu)
अणु
	वापस 0;
पूर्ण

अटल bool guest_support_attributes(स्थिर अक्षर *attr_name,
				     क्रमागत cxl_attrs type)
अणु
	चयन (type) अणु
	हाल CXL_ADAPTER_ATTRS:
		अगर ((म_भेद(attr_name, "base_image") == 0) ||
			(म_भेद(attr_name, "load_image_on_perst") == 0) ||
			(म_भेद(attr_name, "perst_reloads_same_image") == 0) ||
			(म_भेद(attr_name, "image_loaded") == 0))
			वापस false;
		अवरोध;
	हाल CXL_AFU_MASTER_ATTRS:
		अगर ((म_भेद(attr_name, "pp_mmio_off") == 0))
			वापस false;
		अवरोध;
	हाल CXL_AFU_ATTRS:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक activate_afu_directed(काष्ठा cxl_afu *afu)
अणु
	पूर्णांक rc;

	dev_info(&afu->dev, "Activating AFU(%d) directed mode\n", afu->slice);

	afu->current_mode = CXL_MODE_सूचीECTED;

	afu->num_procs = afu->max_procs_भवised;

	अगर ((rc = cxl_अक्षरdev_m_afu_add(afu)))
		वापस rc;

	अगर ((rc = cxl_sysfs_afu_m_add(afu)))
		जाओ err;

	अगर ((rc = cxl_अक्षरdev_s_afu_add(afu)))
		जाओ err1;

	वापस 0;
err1:
	cxl_sysfs_afu_m_हटाओ(afu);
err:
	cxl_अक्षरdev_afu_हटाओ(afu);
	वापस rc;
पूर्ण

अटल पूर्णांक guest_afu_activate_mode(काष्ठा cxl_afu *afu, पूर्णांक mode)
अणु
	अगर (!mode)
		वापस 0;
	अगर (!(mode & afu->modes_supported))
		वापस -EINVAL;

	अगर (mode == CXL_MODE_सूचीECTED)
		वापस activate_afu_directed(afu);

	अगर (mode == CXL_MODE_DEDICATED)
		dev_err(&afu->dev, "Dedicated mode not supported\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक deactivate_afu_directed(काष्ठा cxl_afu *afu)
अणु
	dev_info(&afu->dev, "Deactivating AFU(%d) directed mode\n", afu->slice);

	afu->current_mode = 0;
	afu->num_procs = 0;

	cxl_sysfs_afu_m_हटाओ(afu);
	cxl_अक्षरdev_afu_हटाओ(afu);

	cxl_ops->afu_reset(afu);

	वापस 0;
पूर्ण

अटल पूर्णांक guest_afu_deactivate_mode(काष्ठा cxl_afu *afu, पूर्णांक mode)
अणु
	अगर (!mode)
		वापस 0;
	अगर (!(mode & afu->modes_supported))
		वापस -EINVAL;

	अगर (mode == CXL_MODE_सूचीECTED)
		वापस deactivate_afu_directed(afu);
	वापस 0;
पूर्ण

अटल पूर्णांक guest_afu_reset(काष्ठा cxl_afu *afu)
अणु
	pr_devel("AFU(%d) reset request\n", afu->slice);
	वापस cxl_h_reset_afu(afu->guest->handle);
पूर्ण

अटल पूर्णांक guest_map_slice_regs(काष्ठा cxl_afu *afu)
अणु
	अगर (!(afu->p2n_mmio = ioremap(afu->guest->p2n_phys, afu->guest->p2n_size))) अणु
		dev_err(&afu->dev, "Error mapping AFU(%d) MMIO regions\n",
			afu->slice);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम guest_unmap_slice_regs(काष्ठा cxl_afu *afu)
अणु
	अगर (afu->p2n_mmio)
		iounmap(afu->p2n_mmio);
पूर्ण

अटल पूर्णांक afu_update_state(काष्ठा cxl_afu *afu)
अणु
	पूर्णांक rc, cur_state;

	rc = afu_पढ़ो_error_state(afu, &cur_state);
	अगर (rc)
		वापस rc;

	अगर (afu->guest->previous_state == cur_state)
		वापस 0;

	pr_devel("AFU(%d) update state to %#x\n", afu->slice, cur_state);

	चयन (cur_state) अणु
	हाल H_STATE_NORMAL:
		afu->guest->previous_state = cur_state;
		अवरोध;

	हाल H_STATE_DISABLE:
		pci_error_handlers(afu, CXL_ERROR_DETECTED_EVENT,
				pci_channel_io_frozen);

		cxl_context_detach_all(afu);
		अगर ((rc = cxl_ops->afu_reset(afu)))
			pr_devel("reset hcall failed %d\n", rc);

		rc = afu_पढ़ो_error_state(afu, &cur_state);
		अगर (!rc && cur_state == H_STATE_NORMAL) अणु
			pci_error_handlers(afu, CXL_SLOT_RESET_EVENT,
					pci_channel_io_normal);
			pci_error_handlers(afu, CXL_RESUME_EVENT, 0);
		पूर्ण
		afu->guest->previous_state = 0;
		अवरोध;

	हाल H_STATE_TEMP_UNAVAILABLE:
		afu->guest->previous_state = cur_state;
		अवरोध;

	हाल H_STATE_PERM_UNAVAILABLE:
		dev_err(&afu->dev, "AFU is in permanent error state\n");
		pci_error_handlers(afu, CXL_ERROR_DETECTED_EVENT,
				pci_channel_io_perm_failure);
		afu->guest->previous_state = cur_state;
		अवरोध;

	शेष:
		pr_err("Unexpected AFU(%d) error state: %#x\n",
		       afu->slice, cur_state);
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम afu_handle_errstate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cxl_afu_guest *afu_guest =
		container_of(to_delayed_work(work), काष्ठा cxl_afu_guest, work_err);

	अगर (!afu_update_state(afu_guest->parent) &&
	    afu_guest->previous_state == H_STATE_PERM_UNAVAILABLE)
		वापस;

	अगर (afu_guest->handle_err)
		schedule_delayed_work(&afu_guest->work_err,
				      msecs_to_jअगरfies(3000));
पूर्ण

अटल bool guest_link_ok(काष्ठा cxl *cxl, काष्ठा cxl_afu *afu)
अणु
	पूर्णांक state;

	अगर (afu && (!afu_पढ़ो_error_state(afu, &state))) अणु
		अगर (state == H_STATE_NORMAL)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक afu_properties_look_ok(काष्ठा cxl_afu *afu)
अणु
	अगर (afu->pp_irqs < 0) अणु
		dev_err(&afu->dev, "Unexpected per-process minimum interrupt value\n");
		वापस -EINVAL;
	पूर्ण

	अगर (afu->max_procs_भवised < 1) अणु
		dev_err(&afu->dev, "Unexpected max number of processes virtualised value\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxl_guest_init_afu(काष्ठा cxl *adapter, पूर्णांक slice, काष्ठा device_node *afu_np)
अणु
	काष्ठा cxl_afu *afu;
	bool मुक्त = true;
	पूर्णांक rc;

	pr_devel("in %s - AFU(%d)\n", __func__, slice);
	अगर (!(afu = cxl_alloc_afu(adapter, slice)))
		वापस -ENOMEM;

	अगर (!(afu->guest = kzalloc(माप(काष्ठा cxl_afu_guest), GFP_KERNEL))) अणु
		kमुक्त(afu);
		वापस -ENOMEM;
	पूर्ण

	अगर ((rc = dev_set_name(&afu->dev, "afu%i.%i",
					  adapter->adapter_num,
					  slice)))
		जाओ err1;

	adapter->slices++;

	अगर ((rc = cxl_of_पढ़ो_afu_handle(afu, afu_np)))
		जाओ err1;

	अगर ((rc = cxl_ops->afu_reset(afu)))
		जाओ err1;

	अगर ((rc = cxl_of_पढ़ो_afu_properties(afu, afu_np)))
		जाओ err1;

	अगर ((rc = afu_properties_look_ok(afu)))
		जाओ err1;

	अगर ((rc = guest_map_slice_regs(afu)))
		जाओ err1;

	अगर ((rc = guest_रेजिस्टर_serr_irq(afu)))
		जाओ err2;

	/*
	 * After we call this function we must not मुक्त the afu directly, even
	 * अगर it वापसs an error!
	 */
	अगर ((rc = cxl_रेजिस्टर_afu(afu)))
		जाओ err_put1;

	अगर ((rc = cxl_sysfs_afu_add(afu)))
		जाओ err_put1;

	/*
	 * pHyp करोesn't expose the programming models supported by the
	 * AFU. pHyp currently only supports directed mode. If it adds
	 * dedicated mode later, this version of cxl has no way to
	 * detect it. So we'll initialize the driver, but the first
	 * attach will fail.
	 * Being discussed with pHyp to करो better (likely new property)
	 */
	अगर (afu->max_procs_भवised == 1)
		afu->modes_supported = CXL_MODE_DEDICATED;
	अन्यथा
		afu->modes_supported = CXL_MODE_सूचीECTED;

	अगर ((rc = cxl_afu_select_best_mode(afu)))
		जाओ err_put2;

	adapter->afu[afu->slice] = afu;

	afu->enabled = true;

	/*
	 * wake up the cpu periodically to check the state
	 * of the AFU using "afu" stored in the guest काष्ठाure.
	 */
	afu->guest->parent = afu;
	afu->guest->handle_err = true;
	INIT_DELAYED_WORK(&afu->guest->work_err, afu_handle_errstate);
	schedule_delayed_work(&afu->guest->work_err, msecs_to_jअगरfies(1000));

	अगर ((rc = cxl_pci_vphb_add(afu)))
		dev_info(&afu->dev, "Can't register vPHB\n");

	वापस 0;

err_put2:
	cxl_sysfs_afu_हटाओ(afu);
err_put1:
	device_unरेजिस्टर(&afu->dev);
	मुक्त = false;
	guest_release_serr_irq(afu);
err2:
	guest_unmap_slice_regs(afu);
err1:
	अगर (मुक्त) अणु
		kमुक्त(afu->guest);
		kमुक्त(afu);
	पूर्ण
	वापस rc;
पूर्ण

व्योम cxl_guest_हटाओ_afu(काष्ठा cxl_afu *afu)
अणु
	अगर (!afu)
		वापस;

	/* flush and stop pending job */
	afu->guest->handle_err = false;
	flush_delayed_work(&afu->guest->work_err);

	cxl_pci_vphb_हटाओ(afu);
	cxl_sysfs_afu_हटाओ(afu);

	spin_lock(&afu->adapter->afu_list_lock);
	afu->adapter->afu[afu->slice] = शून्य;
	spin_unlock(&afu->adapter->afu_list_lock);

	cxl_context_detach_all(afu);
	cxl_ops->afu_deactivate_mode(afu, afu->current_mode);
	guest_release_serr_irq(afu);
	guest_unmap_slice_regs(afu);

	device_unरेजिस्टर(&afu->dev);
पूर्ण

अटल व्योम मुक्त_adapter(काष्ठा cxl *adapter)
अणु
	काष्ठा irq_avail *cur;
	पूर्णांक i;

	अगर (adapter->guest) अणु
		अगर (adapter->guest->irq_avail) अणु
			क्रम (i = 0; i < adapter->guest->irq_nranges; i++) अणु
				cur = &adapter->guest->irq_avail[i];
				kमुक्त(cur->biपंचांगap);
			पूर्ण
			kमुक्त(adapter->guest->irq_avail);
		पूर्ण
		kमुक्त(adapter->guest->status);
		kमुक्त(adapter->guest);
	पूर्ण
	cxl_हटाओ_adapter_nr(adapter);
	kमुक्त(adapter);
पूर्ण

अटल पूर्णांक properties_look_ok(काष्ठा cxl *adapter)
अणु
	/* The असलence of this property means that the operational
	 * status is unknown or okay
	 */
	अगर (म_माप(adapter->guest->status) &&
	    म_भेद(adapter->guest->status, "okay")) अणु
		pr_err("ABORTING:Bad operational status of the device\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

sमाप_प्रकार cxl_guest_पढ़ो_adapter_vpd(काष्ठा cxl *adapter, व्योम *buf, माप_प्रकार len)
अणु
	वापस guest_collect_vpd(adapter, शून्य, buf, len);
पूर्ण

व्योम cxl_guest_हटाओ_adapter(काष्ठा cxl *adapter)
अणु
	pr_devel("in %s\n", __func__);

	cxl_sysfs_adapter_हटाओ(adapter);

	cxl_guest_हटाओ_अक्षरdev(adapter);
	device_unरेजिस्टर(&adapter->dev);
पूर्ण

अटल व्योम release_adapter(काष्ठा device *dev)
अणु
	मुक्त_adapter(to_cxl_adapter(dev));
पूर्ण

काष्ठा cxl *cxl_guest_init_adapter(काष्ठा device_node *np, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cxl *adapter;
	bool मुक्त = true;
	पूर्णांक rc;

	अगर (!(adapter = cxl_alloc_adapter()))
		वापस ERR_PTR(-ENOMEM);

	अगर (!(adapter->guest = kzalloc(माप(काष्ठा cxl_guest), GFP_KERNEL))) अणु
		मुक्त_adapter(adapter);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	adapter->slices = 0;
	adapter->guest->pdev = pdev;
	adapter->dev.parent = &pdev->dev;
	adapter->dev.release = release_adapter;
	dev_set_drvdata(&pdev->dev, adapter);

	/*
	 * Hypervisor controls PSL समयbase initialization (p1 रेजिस्टर).
	 * On FW840, PSL is initialized.
	 */
	adapter->psl_समयbase_synced = true;

	अगर ((rc = cxl_of_पढ़ो_adapter_handle(adapter, np)))
		जाओ err1;

	अगर ((rc = cxl_of_पढ़ो_adapter_properties(adapter, np)))
		जाओ err1;

	अगर ((rc = properties_look_ok(adapter)))
		जाओ err1;

	अगर ((rc = cxl_guest_add_अक्षरdev(adapter)))
		जाओ err1;

	/*
	 * After we call this function we must not मुक्त the adapter directly,
	 * even अगर it वापसs an error!
	 */
	अगर ((rc = cxl_रेजिस्टर_adapter(adapter)))
		जाओ err_put1;

	अगर ((rc = cxl_sysfs_adapter_add(adapter)))
		जाओ err_put1;

	/* release the context lock as the adapter is configured */
	cxl_adapter_context_unlock(adapter);

	वापस adapter;

err_put1:
	device_unरेजिस्टर(&adapter->dev);
	मुक्त = false;
	cxl_guest_हटाओ_अक्षरdev(adapter);
err1:
	अगर (मुक्त)
		मुक्त_adapter(adapter);
	वापस ERR_PTR(rc);
पूर्ण

व्योम cxl_guest_reload_module(काष्ठा cxl *adapter)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = adapter->guest->pdev;
	cxl_guest_हटाओ_adapter(adapter);

	cxl_of_probe(pdev);
पूर्ण

स्थिर काष्ठा cxl_backend_ops cxl_guest_ops = अणु
	.module = THIS_MODULE,
	.adapter_reset = guest_reset,
	.alloc_one_irq = guest_alloc_one_irq,
	.release_one_irq = guest_release_one_irq,
	.alloc_irq_ranges = guest_alloc_irq_ranges,
	.release_irq_ranges = guest_release_irq_ranges,
	.setup_irq = शून्य,
	.handle_psl_slice_error = guest_handle_psl_slice_error,
	.psl_पूर्णांकerrupt = guest_psl_irq,
	.ack_irq = guest_ack_irq,
	.attach_process = guest_attach_process,
	.detach_process = guest_detach_process,
	.update_ivtes = शून्य,
	.support_attributes = guest_support_attributes,
	.link_ok = guest_link_ok,
	.release_afu = guest_release_afu,
	.afu_पढ़ो_err_buffer = guest_afu_पढ़ो_err_buffer,
	.afu_check_and_enable = guest_afu_check_and_enable,
	.afu_activate_mode = guest_afu_activate_mode,
	.afu_deactivate_mode = guest_afu_deactivate_mode,
	.afu_reset = guest_afu_reset,
	.afu_cr_पढ़ो8 = guest_afu_cr_पढ़ो8,
	.afu_cr_पढ़ो16 = guest_afu_cr_पढ़ो16,
	.afu_cr_पढ़ो32 = guest_afu_cr_पढ़ो32,
	.afu_cr_पढ़ो64 = guest_afu_cr_पढ़ो64,
	.afu_cr_ग_लिखो8 = guest_afu_cr_ग_लिखो8,
	.afu_cr_ग_लिखो16 = guest_afu_cr_ग_लिखो16,
	.afu_cr_ग_लिखो32 = guest_afu_cr_ग_लिखो32,
	.पढ़ो_adapter_vpd = cxl_guest_पढ़ो_adapter_vpd,
पूर्ण;
