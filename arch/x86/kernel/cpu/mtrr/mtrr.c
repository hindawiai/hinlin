<शैली गुरु>
/*  Generic MTRR (Memory Type Range Register) driver.

    Copyright (C) 1997-2000  Riअक्षरd Gooch
    Copyright (c) 2002	     Patrick Mochel

    This library is मुक्त software; you can redistribute it and/or
    modअगरy it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License क्रम more details.

    You should have received a copy of the GNU Library General Public
    License aदीर्घ with this library; अगर not, ग_लिखो to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    Riअक्षरd Gooch may be reached by email at  rgooch@atnf.csiro.au
    The postal address is:
      Riअक्षरd Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Australia.

    Source: "Pentium Pro Family Developer's Manual, Volume 3:
    Operating System Writer's Guide" (Intel करोcument number 242692),
    section 11.11.7

    This was cleaned and made पढ़ोable by Patrick Mochel <mochel@osdl.org>
    on 6-7 March 2002.
    Source: Intel Architecture Software Developers Manual, Volume 3:
    System Programming Guide; Section 9.11. (1997 edition - PPro).
*/

#समावेश <linux/types.h> /* FIXME: kvm_para.h needs this */

#समावेश <linux/stop_machine.h>
#समावेश <linux/kvm_para.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/sort.h>
#समावेश <linux/cpu.h>
#समावेश <linux/pci.h>
#समावेश <linux/smp.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/rcupdate.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/memtype.h>

#समावेश "mtrr.h"

/* arch_phys_wc_add वापसs an MTRR रेजिस्टर index plus this offset. */
#घोषणा MTRR_TO_PHYS_WC_OFFSET 1000

u32 num_var_ranges;
अटल bool __mtrr_enabled;

अटल bool mtrr_enabled(व्योम)
अणु
	वापस __mtrr_enabled;
पूर्ण

अचिन्हित पूर्णांक mtrr_usage_table[MTRR_MAX_VAR_RANGES];
अटल DEFINE_MUTEX(mtrr_mutex);

u64 size_or_mask, size_and_mask;
अटल bool mtrr_aps_delayed_init;

अटल स्थिर काष्ठा mtrr_ops *mtrr_ops[X86_VENDOR_NUM] __ro_after_init;

स्थिर काष्ठा mtrr_ops *mtrr_अगर;

अटल व्योम set_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base,
		     अचिन्हित दीर्घ size, mtrr_type type);

व्योम __init set_mtrr_ops(स्थिर काष्ठा mtrr_ops *ops)
अणु
	अगर (ops->venकरोr && ops->venकरोr < X86_VENDOR_NUM)
		mtrr_ops[ops->venकरोr] = ops;
पूर्ण

/*  Returns non-zero अगर we have the ग_लिखो-combining memory type  */
अटल पूर्णांक have_wrcomb(व्योम)
अणु
	काष्ठा pci_dev *dev;

	dev = pci_get_class(PCI_CLASS_BRIDGE_HOST << 8, शून्य);
	अगर (dev != शून्य) अणु
		/*
		 * ServerWorks LE chipsets < rev 6 have problems with
		 * ग_लिखो-combining. Don't allow it and leave room क्रम other
		 * chipsets to be tagged
		 */
		अगर (dev->venकरोr == PCI_VENDOR_ID_SERVERWORKS &&
		    dev->device == PCI_DEVICE_ID_SERVERWORKS_LE &&
		    dev->revision <= 5) अणु
			pr_info("Serverworks LE rev < 6 detected. Write-combining disabled.\n");
			pci_dev_put(dev);
			वापस 0;
		पूर्ण
		/*
		 * Intel 450NX errata # 23. Non ascending cacheline evictions to
		 * ग_लिखो combining memory may resulting in data corruption
		 */
		अगर (dev->venकरोr == PCI_VENDOR_ID_INTEL &&
		    dev->device == PCI_DEVICE_ID_INTEL_82451NX) अणु
			pr_info("Intel 450NX MMC detected. Write-combining disabled.\n");
			pci_dev_put(dev);
			वापस 0;
		पूर्ण
		pci_dev_put(dev);
	पूर्ण
	वापस mtrr_अगर->have_wrcomb ? mtrr_अगर->have_wrcomb() : 0;
पूर्ण

/*  This function वापसs the number of variable MTRRs  */
अटल व्योम __init set_num_var_ranges(व्योम)
अणु
	अचिन्हित दीर्घ config = 0, dummy;

	अगर (use_पूर्णांकel())
		rdmsr(MSR_MTRRcap, config, dummy);
	अन्यथा अगर (is_cpu(AMD) || is_cpu(HYGON))
		config = 2;
	अन्यथा अगर (is_cpu(CYRIX) || is_cpu(CENTAUR))
		config = 8;

	num_var_ranges = config & 0xff;
पूर्ण

अटल व्योम __init init_table(व्योम)
अणु
	पूर्णांक i, max;

	max = num_var_ranges;
	क्रम (i = 0; i < max; i++)
		mtrr_usage_table[i] = 1;
पूर्ण

काष्ठा set_mtrr_data अणु
	अचिन्हित दीर्घ	smp_base;
	अचिन्हित दीर्घ	smp_size;
	अचिन्हित पूर्णांक	smp_reg;
	mtrr_type	smp_type;
पूर्ण;

/**
 * mtrr_rendezvous_handler - Work करोne in the synchronization handler. Executed
 * by all the CPUs.
 * @info: poपूर्णांकer to mtrr configuration data
 *
 * Returns nothing.
 */
अटल पूर्णांक mtrr_rendezvous_handler(व्योम *info)
अणु
	काष्ठा set_mtrr_data *data = info;

	/*
	 * We use this same function to initialize the mtrrs during boot,
	 * resume, runसमय cpu online and on an explicit request to set a
	 * specअगरic MTRR.
	 *
	 * During boot or suspend, the state of the boot cpu's mtrrs has been
	 * saved, and we want to replicate that across all the cpus that come
	 * online (either at the end of boot or resume or during a runसमय cpu
	 * online). If we're करोing that, @reg is set to something special and on
	 * all the cpu's we करो mtrr_अगर->set_all() (On the logical cpu that
	 * started the boot/resume sequence, this might be a duplicate
	 * set_all()).
	 */
	अगर (data->smp_reg != ~0U) अणु
		mtrr_अगर->set(data->smp_reg, data->smp_base,
			     data->smp_size, data->smp_type);
	पूर्ण अन्यथा अगर (mtrr_aps_delayed_init || !cpu_online(smp_processor_id())) अणु
		mtrr_अगर->set_all();
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक types_compatible(mtrr_type type1, mtrr_type type2)
अणु
	वापस type1 == MTRR_TYPE_UNCACHABLE ||
	       type2 == MTRR_TYPE_UNCACHABLE ||
	       (type1 == MTRR_TYPE_WRTHROUGH && type2 == MTRR_TYPE_WRBACK) ||
	       (type1 == MTRR_TYPE_WRBACK && type2 == MTRR_TYPE_WRTHROUGH);
पूर्ण

/**
 * set_mtrr - update mtrrs on all processors
 * @reg:	mtrr in question
 * @base:	mtrr base
 * @size:	mtrr size
 * @type:	mtrr type
 *
 * This is kinda tricky, but क्रमtunately, Intel spelled it out क्रम us cleanly:
 *
 * 1. Queue work to करो the following on all processors:
 * 2. Disable Interrupts
 * 3. Wait क्रम all procs to करो so
 * 4. Enter no-fill cache mode
 * 5. Flush caches
 * 6. Clear PGE bit
 * 7. Flush all TLBs
 * 8. Disable all range रेजिस्टरs
 * 9. Update the MTRRs
 * 10. Enable all range रेजिस्टरs
 * 11. Flush all TLBs and caches again
 * 12. Enter normal cache mode and reenable caching
 * 13. Set PGE
 * 14. Wait क्रम buddies to catch up
 * 15. Enable पूर्णांकerrupts.
 *
 * What करोes that mean क्रम us? Well, stop_machine() will ensure that
 * the rendezvous handler is started on each CPU. And in lockstep they
 * करो the state transition of disabling पूर्णांकerrupts, updating MTRR's
 * (the CPU venकरोrs may each करो it dअगरferently, so we call mtrr_अगर->set()
 * callback and let them take care of it.) and enabling पूर्णांकerrupts.
 *
 * Note that the mechanism is the same क्रम UP प्रणालीs, too; all the SMP stuff
 * becomes nops.
 */
अटल व्योम
set_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, mtrr_type type)
अणु
	काष्ठा set_mtrr_data data = अणु .smp_reg = reg,
				      .smp_base = base,
				      .smp_size = size,
				      .smp_type = type
				    पूर्ण;

	stop_machine(mtrr_rendezvous_handler, &data, cpu_online_mask);
पूर्ण

अटल व्योम set_mtrr_cpuslocked(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base,
				अचिन्हित दीर्घ size, mtrr_type type)
अणु
	काष्ठा set_mtrr_data data = अणु .smp_reg = reg,
				      .smp_base = base,
				      .smp_size = size,
				      .smp_type = type
				    पूर्ण;

	stop_machine_cpuslocked(mtrr_rendezvous_handler, &data, cpu_online_mask);
पूर्ण

अटल व्योम set_mtrr_from_inactive_cpu(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base,
				      अचिन्हित दीर्घ size, mtrr_type type)
अणु
	काष्ठा set_mtrr_data data = अणु .smp_reg = reg,
				      .smp_base = base,
				      .smp_size = size,
				      .smp_type = type
				    पूर्ण;

	stop_machine_from_inactive_cpu(mtrr_rendezvous_handler, &data,
				       cpu_callout_mask);
पूर्ण

/**
 * mtrr_add_page - Add a memory type region
 * @base: Physical base address of region in pages (in units of 4 kB!)
 * @size: Physical size of region in pages (4 kB)
 * @type: Type of MTRR desired
 * @increment: If this is true करो usage counting on the region
 *
 * Memory type region रेजिस्टरs control the caching on newer Intel and
 * non Intel processors. This function allows drivers to request an
 * MTRR is added. The details and hardware specअगरics of each processor's
 * implementation are hidden from the caller, but nevertheless the
 * caller should expect to need to provide a घातer of two size on an
 * equivalent घातer of two boundary.
 *
 * If the region cannot be added either because all regions are in use
 * or the CPU cannot support it a negative value is वापसed. On success
 * the रेजिस्टर number क्रम this entry is वापसed, but should be treated
 * as a cookie only.
 *
 * On a multiprocessor machine the changes are made to all processors.
 * This is required on x86 by the Intel processors.
 *
 * The available types are
 *
 * %MTRR_TYPE_UNCACHABLE - No caching
 *
 * %MTRR_TYPE_WRBACK - Write data back in bursts whenever
 *
 * %MTRR_TYPE_WRCOMB - Write data back soon but allow bursts
 *
 * %MTRR_TYPE_WRTHROUGH - Cache पढ़ोs but not ग_लिखोs
 *
 * BUGS: Needs a quiet flag क्रम the हालs where drivers करो not mind
 * failures and करो not wish प्रणाली log messages to be sent.
 */
पूर्णांक mtrr_add_page(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
		  अचिन्हित पूर्णांक type, bool increment)
अणु
	अचिन्हित दीर्घ lbase, lsize;
	पूर्णांक i, replace, error;
	mtrr_type ltype;

	अगर (!mtrr_enabled())
		वापस -ENXIO;

	error = mtrr_अगर->validate_add_page(base, size, type);
	अगर (error)
		वापस error;

	अगर (type >= MTRR_NUM_TYPES) अणु
		pr_warn("type: %u invalid\n", type);
		वापस -EINVAL;
	पूर्ण

	/* If the type is WC, check that this processor supports it */
	अगर ((type == MTRR_TYPE_WRCOMB) && !have_wrcomb()) अणु
		pr_warn("your processor doesn't support write-combining\n");
		वापस -ENOSYS;
	पूर्ण

	अगर (!size) अणु
		pr_warn("zero sized request\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((base | (base + size - 1)) >>
	    (boot_cpu_data.x86_phys_bits - PAGE_SHIFT)) अणु
		pr_warn("base or size exceeds the MTRR width\n");
		वापस -EINVAL;
	पूर्ण

	error = -EINVAL;
	replace = -1;

	/* No CPU hotplug when we change MTRR entries */
	get_online_cpus();

	/* Search क्रम existing MTRR  */
	mutex_lock(&mtrr_mutex);
	क्रम (i = 0; i < num_var_ranges; ++i) अणु
		mtrr_अगर->get(i, &lbase, &lsize, &ltype);
		अगर (!lsize || base > lbase + lsize - 1 ||
		    base + size - 1 < lbase)
			जारी;
		/*
		 * At this poपूर्णांक we know there is some kind of
		 * overlap/enclosure
		 */
		अगर (base < lbase || base + size - 1 > lbase + lsize - 1) अणु
			अगर (base <= lbase &&
			    base + size - 1 >= lbase + lsize - 1) अणु
				/*  New region enबंदs an existing region  */
				अगर (type == ltype) अणु
					replace = replace == -1 ? i : -2;
					जारी;
				पूर्ण अन्यथा अगर (types_compatible(type, ltype))
					जारी;
			पूर्ण
			pr_warn("0x%lx000,0x%lx000 overlaps existing 0x%lx000,0x%lx000\n", base, size, lbase,
				lsize);
			जाओ out;
		पूर्ण
		/* New region is enबंदd by an existing region */
		अगर (ltype != type) अणु
			अगर (types_compatible(type, ltype))
				जारी;
			pr_warn("type mismatch for %lx000,%lx000 old: %s new: %s\n",
				base, size, mtrr_attrib_to_str(ltype),
				mtrr_attrib_to_str(type));
			जाओ out;
		पूर्ण
		अगर (increment)
			++mtrr_usage_table[i];
		error = i;
		जाओ out;
	पूर्ण
	/* Search क्रम an empty MTRR */
	i = mtrr_अगर->get_मुक्त_region(base, size, replace);
	अगर (i >= 0) अणु
		set_mtrr_cpuslocked(i, base, size, type);
		अगर (likely(replace < 0)) अणु
			mtrr_usage_table[i] = 1;
		पूर्ण अन्यथा अणु
			mtrr_usage_table[i] = mtrr_usage_table[replace];
			अगर (increment)
				mtrr_usage_table[i]++;
			अगर (unlikely(replace != i)) अणु
				set_mtrr_cpuslocked(replace, 0, 0, 0);
				mtrr_usage_table[replace] = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("no more MTRRs available\n");
	पूर्ण
	error = i;
 out:
	mutex_unlock(&mtrr_mutex);
	put_online_cpus();
	वापस error;
पूर्ण

अटल पूर्णांक mtrr_check(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	अगर ((base & (PAGE_SIZE - 1)) || (size & (PAGE_SIZE - 1))) अणु
		pr_warn("size and base must be multiples of 4 kiB\n");
		pr_debug("size: 0x%lx  base: 0x%lx\n", size, base);
		dump_stack();
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mtrr_add - Add a memory type region
 * @base: Physical base address of region
 * @size: Physical size of region
 * @type: Type of MTRR desired
 * @increment: If this is true करो usage counting on the region
 *
 * Memory type region रेजिस्टरs control the caching on newer Intel and
 * non Intel processors. This function allows drivers to request an
 * MTRR is added. The details and hardware specअगरics of each processor's
 * implementation are hidden from the caller, but nevertheless the
 * caller should expect to need to provide a घातer of two size on an
 * equivalent घातer of two boundary.
 *
 * If the region cannot be added either because all regions are in use
 * or the CPU cannot support it a negative value is वापसed. On success
 * the रेजिस्टर number क्रम this entry is वापसed, but should be treated
 * as a cookie only.
 *
 * On a multiprocessor machine the changes are made to all processors.
 * This is required on x86 by the Intel processors.
 *
 * The available types are
 *
 * %MTRR_TYPE_UNCACHABLE - No caching
 *
 * %MTRR_TYPE_WRBACK - Write data back in bursts whenever
 *
 * %MTRR_TYPE_WRCOMB - Write data back soon but allow bursts
 *
 * %MTRR_TYPE_WRTHROUGH - Cache पढ़ोs but not ग_लिखोs
 *
 * BUGS: Needs a quiet flag क्रम the हालs where drivers करो not mind
 * failures and करो not wish प्रणाली log messages to be sent.
 */
पूर्णांक mtrr_add(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, अचिन्हित पूर्णांक type,
	     bool increment)
अणु
	अगर (!mtrr_enabled())
		वापस -ENODEV;
	अगर (mtrr_check(base, size))
		वापस -EINVAL;
	वापस mtrr_add_page(base >> PAGE_SHIFT, size >> PAGE_SHIFT, type,
			     increment);
पूर्ण

/**
 * mtrr_del_page - delete a memory type region
 * @reg: Register वापसed by mtrr_add
 * @base: Physical base address
 * @size: Size of region
 *
 * If रेजिस्टर is supplied then base and size are ignored. This is
 * how drivers should call it.
 *
 * Releases an MTRR region. If the usage count drops to zero the
 * रेजिस्टर is मुक्तd and the region वापसs to शेष state.
 * On success the रेजिस्टर is वापसed, on failure a negative error
 * code.
 */
पूर्णांक mtrr_del_page(पूर्णांक reg, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	पूर्णांक i, max;
	mtrr_type ltype;
	अचिन्हित दीर्घ lbase, lsize;
	पूर्णांक error = -EINVAL;

	अगर (!mtrr_enabled())
		वापस -ENODEV;

	max = num_var_ranges;
	/* No CPU hotplug when we change MTRR entries */
	get_online_cpus();
	mutex_lock(&mtrr_mutex);
	अगर (reg < 0) अणु
		/*  Search क्रम existing MTRR  */
		क्रम (i = 0; i < max; ++i) अणु
			mtrr_अगर->get(i, &lbase, &lsize, &ltype);
			अगर (lbase == base && lsize == size) अणु
				reg = i;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (reg < 0) अणु
			pr_debug("no MTRR for %lx000,%lx000 found\n",
				 base, size);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (reg >= max) अणु
		pr_warn("register: %d too big\n", reg);
		जाओ out;
	पूर्ण
	mtrr_अगर->get(reg, &lbase, &lsize, &ltype);
	अगर (lsize < 1) अणु
		pr_warn("MTRR %d not used\n", reg);
		जाओ out;
	पूर्ण
	अगर (mtrr_usage_table[reg] < 1) अणु
		pr_warn("reg: %d has count=0\n", reg);
		जाओ out;
	पूर्ण
	अगर (--mtrr_usage_table[reg] < 1)
		set_mtrr_cpuslocked(reg, 0, 0, 0);
	error = reg;
 out:
	mutex_unlock(&mtrr_mutex);
	put_online_cpus();
	वापस error;
पूर्ण

/**
 * mtrr_del - delete a memory type region
 * @reg: Register वापसed by mtrr_add
 * @base: Physical base address
 * @size: Size of region
 *
 * If रेजिस्टर is supplied then base and size are ignored. This is
 * how drivers should call it.
 *
 * Releases an MTRR region. If the usage count drops to zero the
 * रेजिस्टर is मुक्तd and the region वापसs to शेष state.
 * On success the रेजिस्टर is वापसed, on failure a negative error
 * code.
 */
पूर्णांक mtrr_del(पूर्णांक reg, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	अगर (!mtrr_enabled())
		वापस -ENODEV;
	अगर (mtrr_check(base, size))
		वापस -EINVAL;
	वापस mtrr_del_page(reg, base >> PAGE_SHIFT, size >> PAGE_SHIFT);
पूर्ण

/**
 * arch_phys_wc_add - add a WC MTRR and handle errors अगर PAT is unavailable
 * @base: Physical base address
 * @size: Size of region
 *
 * If PAT is available, this करोes nothing.  If PAT is unavailable, it
 * attempts to add a WC MTRR covering size bytes starting at base and
 * logs an error अगर this fails.
 *
 * The called should provide a घातer of two size on an equivalent
 * घातer of two boundary.
 *
 * Drivers must store the वापस value to pass to mtrr_del_wc_अगर_needed,
 * but drivers should not try to पूर्णांकerpret that वापस value.
 */
पूर्णांक arch_phys_wc_add(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	पूर्णांक ret;

	अगर (pat_enabled() || !mtrr_enabled())
		वापस 0;  /* Success!  (We करोn't need to करो anything.) */

	ret = mtrr_add(base, size, MTRR_TYPE_WRCOMB, true);
	अगर (ret < 0) अणु
		pr_warn("Failed to add WC MTRR for [%p-%p]; performance may suffer.",
			(व्योम *)base, (व्योम *)(base + size - 1));
		वापस ret;
	पूर्ण
	वापस ret + MTRR_TO_PHYS_WC_OFFSET;
पूर्ण
EXPORT_SYMBOL(arch_phys_wc_add);

/*
 * arch_phys_wc_del - unकरोes arch_phys_wc_add
 * @handle: Return value from arch_phys_wc_add
 *
 * This cleans up after mtrr_add_wc_अगर_needed.
 *
 * The API guarantees that mtrr_del_wc_अगर_needed(error code) and
 * mtrr_del_wc_अगर_needed(0) करो nothing.
 */
व्योम arch_phys_wc_del(पूर्णांक handle)
अणु
	अगर (handle >= 1) अणु
		WARN_ON(handle < MTRR_TO_PHYS_WC_OFFSET);
		mtrr_del(handle - MTRR_TO_PHYS_WC_OFFSET, 0, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(arch_phys_wc_del);

/*
 * arch_phys_wc_index - translates arch_phys_wc_add's वापस value
 * @handle: Return value from arch_phys_wc_add
 *
 * This will turn the वापस value from arch_phys_wc_add पूर्णांकo an mtrr
 * index suitable क्रम debugging.
 *
 * Note: There is no legitimate use क्रम this function, except possibly
 * in prपूर्णांकk line.  Alas there is an illegitimate use in some ancient
 * drm ioctls.
 */
पूर्णांक arch_phys_wc_index(पूर्णांक handle)
अणु
	अगर (handle < MTRR_TO_PHYS_WC_OFFSET)
		वापस -1;
	अन्यथा
		वापस handle - MTRR_TO_PHYS_WC_OFFSET;
पूर्ण
EXPORT_SYMBOL_GPL(arch_phys_wc_index);

/*
 * HACK ALERT!
 * These should be called implicitly, but we can't yet until all the initcall
 * stuff is करोne...
 */
अटल व्योम __init init_अगरs(व्योम)
अणु
#अगर_अघोषित CONFIG_X86_64
	amd_init_mtrr();
	cyrix_init_mtrr();
	centaur_init_mtrr();
#पूर्ण_अगर
पूर्ण

/* The suspend/resume methods are only क्रम CPU without MTRR. CPU using generic
 * MTRR driver करोesn't require this
 */
काष्ठा mtrr_value अणु
	mtrr_type	ltype;
	अचिन्हित दीर्घ	lbase;
	अचिन्हित दीर्घ	lsize;
पूर्ण;

अटल काष्ठा mtrr_value mtrr_value[MTRR_MAX_VAR_RANGES];

अटल पूर्णांक mtrr_save(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_var_ranges; i++) अणु
		mtrr_अगर->get(i, &mtrr_value[i].lbase,
				&mtrr_value[i].lsize,
				&mtrr_value[i].ltype);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mtrr_restore(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_var_ranges; i++) अणु
		अगर (mtrr_value[i].lsize) अणु
			set_mtrr(i, mtrr_value[i].lbase,
				    mtrr_value[i].lsize,
				    mtrr_value[i].ltype);
		पूर्ण
	पूर्ण
पूर्ण



अटल काष्ठा syscore_ops mtrr_syscore_ops = अणु
	.suspend	= mtrr_save,
	.resume		= mtrr_restore,
पूर्ण;

पूर्णांक __initdata changed_by_mtrr_cleanup;

#घोषणा SIZE_OR_MASK_BITS(n)  (~((1ULL << ((n) - PAGE_SHIFT)) - 1))
/**
 * mtrr_bp_init - initialize mtrrs on the boot CPU
 *
 * This needs to be called early; beक्रमe any of the other CPUs are
 * initialized (i.e. beक्रमe smp_init()).
 *
 */
व्योम __init mtrr_bp_init(व्योम)
अणु
	u32 phys_addr;

	init_अगरs();

	phys_addr = 32;

	अगर (boot_cpu_has(X86_FEATURE_MTRR)) अणु
		mtrr_अगर = &generic_mtrr_ops;
		size_or_mask = SIZE_OR_MASK_BITS(36);
		size_and_mask = 0x00f00000;
		phys_addr = 36;

		/*
		 * This is an AMD specअगरic MSR, but we assume(hope?) that
		 * Intel will implement it too when they extend the address
		 * bus of the Xeon.
		 */
		अगर (cpuid_eax(0x80000000) >= 0x80000008) अणु
			phys_addr = cpuid_eax(0x80000008) & 0xff;
			/* CPUID workaround क्रम Intel 0F33/0F34 CPU */
			अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL &&
			    boot_cpu_data.x86 == 0xF &&
			    boot_cpu_data.x86_model == 0x3 &&
			    (boot_cpu_data.x86_stepping == 0x3 ||
			     boot_cpu_data.x86_stepping == 0x4))
				phys_addr = 36;

			size_or_mask = SIZE_OR_MASK_BITS(phys_addr);
			size_and_mask = ~size_or_mask & 0xfffff00000ULL;
		पूर्ण अन्यथा अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_CENTAUR &&
			   boot_cpu_data.x86 == 6) अणु
			/*
			 * VIA C* family have Intel style MTRRs,
			 * but करोn't support PAE
			 */
			size_or_mask = SIZE_OR_MASK_BITS(32);
			size_and_mask = 0;
			phys_addr = 32;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (boot_cpu_data.x86_venकरोr) अणु
		हाल X86_VENDOR_AMD:
			अगर (cpu_feature_enabled(X86_FEATURE_K6_MTRR)) अणु
				/* Pre-Athlon (K6) AMD CPU MTRRs */
				mtrr_अगर = mtrr_ops[X86_VENDOR_AMD];
				size_or_mask = SIZE_OR_MASK_BITS(32);
				size_and_mask = 0;
			पूर्ण
			अवरोध;
		हाल X86_VENDOR_CENTAUR:
			अगर (cpu_feature_enabled(X86_FEATURE_CENTAUR_MCR)) अणु
				mtrr_अगर = mtrr_ops[X86_VENDOR_CENTAUR];
				size_or_mask = SIZE_OR_MASK_BITS(32);
				size_and_mask = 0;
			पूर्ण
			अवरोध;
		हाल X86_VENDOR_CYRIX:
			अगर (cpu_feature_enabled(X86_FEATURE_CYRIX_ARR)) अणु
				mtrr_अगर = mtrr_ops[X86_VENDOR_CYRIX];
				size_or_mask = SIZE_OR_MASK_BITS(32);
				size_and_mask = 0;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mtrr_अगर) अणु
		__mtrr_enabled = true;
		set_num_var_ranges();
		init_table();
		अगर (use_पूर्णांकel()) अणु
			/* BIOS may override */
			__mtrr_enabled = get_mtrr_state();

			अगर (mtrr_enabled())
				mtrr_bp_pat_init();

			अगर (mtrr_cleanup(phys_addr)) अणु
				changed_by_mtrr_cleanup = 1;
				mtrr_अगर->set_all();
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!mtrr_enabled()) अणु
		pr_info("Disabled\n");

		/*
		 * PAT initialization relies on MTRR's rendezvous handler.
		 * Skip PAT init until the handler can initialize both
		 * features independently.
		 */
		pat_disable("MTRRs disabled, skipping PAT initialization too.");
	पूर्ण
पूर्ण

व्योम mtrr_ap_init(व्योम)
अणु
	अगर (!mtrr_enabled())
		वापस;

	अगर (!use_पूर्णांकel() || mtrr_aps_delayed_init)
		वापस;

	/*
	 * Ideally we should hold mtrr_mutex here to aव्योम mtrr entries
	 * changed, but this routine will be called in cpu boot समय,
	 * holding the lock अवरोधs it.
	 *
	 * This routine is called in two हालs:
	 *
	 *   1. very early समय of software resume, when there असलolutely
	 *      isn't mtrr entry changes;
	 *
	 *   2. cpu hotadd समय. We let mtrr_add/del_page hold cpuhotplug
	 *      lock to prevent mtrr entry changes
	 */
	set_mtrr_from_inactive_cpu(~0U, 0, 0, 0);
पूर्ण

/**
 * mtrr_save_state - Save current fixed-range MTRR state of the first
 *	cpu in cpu_online_mask.
 */
व्योम mtrr_save_state(व्योम)
अणु
	पूर्णांक first_cpu;

	अगर (!mtrr_enabled())
		वापस;

	first_cpu = cpumask_first(cpu_online_mask);
	smp_call_function_single(first_cpu, mtrr_save_fixed_ranges, शून्य, 1);
पूर्ण

व्योम set_mtrr_aps_delayed_init(व्योम)
अणु
	अगर (!mtrr_enabled())
		वापस;
	अगर (!use_पूर्णांकel())
		वापस;

	mtrr_aps_delayed_init = true;
पूर्ण

/*
 * Delayed MTRR initialization क्रम all AP's
 */
व्योम mtrr_aps_init(व्योम)
अणु
	अगर (!use_पूर्णांकel() || !mtrr_enabled())
		वापस;

	/*
	 * Check अगर someone has requested the delay of AP MTRR initialization,
	 * by करोing set_mtrr_aps_delayed_init(), prior to this poपूर्णांक. If not,
	 * then we are करोne.
	 */
	अगर (!mtrr_aps_delayed_init)
		वापस;

	set_mtrr(~0U, 0, 0, 0);
	mtrr_aps_delayed_init = false;
पूर्ण

व्योम mtrr_bp_restore(व्योम)
अणु
	अगर (!use_पूर्णांकel() || !mtrr_enabled())
		वापस;

	mtrr_अगर->set_all();
पूर्ण

अटल पूर्णांक __init mtrr_init_finialize(व्योम)
अणु
	अगर (!mtrr_enabled())
		वापस 0;

	अगर (use_पूर्णांकel()) अणु
		अगर (!changed_by_mtrr_cleanup)
			mtrr_state_warn();
		वापस 0;
	पूर्ण

	/*
	 * The CPU has no MTRR and seems to not support SMP. They have
	 * specअगरic drivers, we use a tricky method to support
	 * suspend/resume क्रम them.
	 *
	 * TBD: is there any प्रणाली with such CPU which supports
	 * suspend/resume? If no, we should हटाओ the code.
	 */
	रेजिस्टर_syscore_ops(&mtrr_syscore_ops);

	वापस 0;
पूर्ण
subsys_initcall(mtrr_init_finialize);
