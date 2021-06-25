<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013, Michael (Ellerman|Neuling), IBM Corporation.
 */

#घोषणा pr_fmt(fmt)	"powernv: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/smp.h>
#समावेश <linux/stop_machine.h>

#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/smp.h>

#समावेश "subcore.h"
#समावेश "powernv.h"


/*
 * Split/unsplit procedure:
 *
 * A core can be in one of three states, unsplit, 2-way split, and 4-way split.
 *
 * The mapping to subcores_per_core is simple:
 *
 *  State       | subcores_per_core
 *  ------------|------------------
 *  Unsplit     |        1
 *  2-way split |        2
 *  4-way split |        4
 *
 * The core is split aदीर्घ thपढ़ो boundaries, the mapping between subcores and
 * thपढ़ोs is as follows:
 *
 *  Unsplit:
 *          ----------------------------
 *  Subcore |            0             |
 *          ----------------------------
 *  Thपढ़ो  |  0  1  2  3  4  5  6  7  |
 *          ----------------------------
 *
 *  2-way split:
 *          -------------------------------------
 *  Subcore |        0        |        1        |
 *          -------------------------------------
 *  Thपढ़ो  |  0   1   2   3  |  4   5   6   7  |
 *          -------------------------------------
 *
 *  4-way split:
 *          -----------------------------------------
 *  Subcore |    0    |    1    |    2    |    3    |
 *          -----------------------------------------
 *  Thपढ़ो  |  0   1  |  2   3  |  4   5  |  6   7  |
 *          -----------------------------------------
 *
 *
 * Transitions
 * -----------
 *
 * It is not possible to transition between either of the split states, the
 * core must first be unsplit. The legal transitions are:
 *
 *  -----------          ---------------
 *  |         |  <---->  | 2-way split |
 *  |         |          ---------------
 *  | Unsplit |
 *  |         |          ---------------
 *  |         |  <---->  | 4-way split |
 *  -----------          ---------------
 *
 * Unsplitting
 * -----------
 *
 * Unsplitting is the simpler procedure. It requires thपढ़ो 0 to request the
 * unsplit जबतक all other thपढ़ोs NAP.
 *
 * Thपढ़ो 0 clears HID0_POWER8_DYNLPARDIS (Dynamic LPAR Disable). This tells
 * the hardware that अगर all thपढ़ोs except 0 are napping, the hardware should
 * unsplit the core.
 *
 * Non-zero thपढ़ोs are sent to a NAP loop, they करोn't निकास the loop until they
 * see the core unsplit.
 *
 * Core 0 spins रुकोing क्रम the hardware to see all the other thपढ़ोs napping
 * and perक्रमm the unsplit.
 *
 * Once thपढ़ो 0 sees the unsplit, it IPIs the secondary thपढ़ोs to wake them
 * out of NAP. They will then see the core unsplit and निकास the NAP loop.
 *
 * Splitting
 * ---------
 *
 * The basic splitting procedure is fairly straight क्रमward. However it is
 * complicated by the fact that after the split occurs, the newly created
 * subcores are not in a fully initialised state.
 *
 * Most notably the subcores करो not have the correct value क्रम SDR1, which
 * means they must not be running in भव mode when the split occurs. The
 * subcores have separate समयbases SPRs but these are pre-synchronised by
 * opal.
 *
 * To begin with secondary thपढ़ोs are sent to an assembly routine. There they
 * चयन to real mode, so they are immune to the uninitialised SDR1 value.
 * Once in real mode they indicate that they are in real mode, and spin रुकोing
 * to see the core split.
 *
 * Thपढ़ो 0 रुकोs to see that all secondaries are in real mode, and then begins
 * the splitting procedure. It firstly sets HID0_POWER8_DYNLPARDIS, which
 * prevents the hardware from unsplitting. Then it sets the appropriate HID bit
 * to request the split, and spins रुकोing to see that the split has happened.
 *
 * Concurrently the secondaries will notice the split. When they करो they set up
 * their SPRs, notably SDR1, and then they can वापस to भव mode and निकास
 * the procedure.
 */

/* Initialised at boot by subcore_init() */
अटल पूर्णांक subcores_per_core;

/*
 * Used to communicate to offline cpus that we want them to pop out of the
 * offline loop and करो a split or unsplit.
 *
 * 0 - no split happening
 * 1 - unsplit in progress
 * 2 - split to 2 in progress
 * 4 - split to 4 in progress
 */
अटल पूर्णांक new_split_mode;

अटल cpumask_var_t cpu_offline_mask;

काष्ठा split_state अणु
	u8 step;
	u8 master;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा split_state, split_state);

अटल व्योम रुको_क्रम_sync_step(पूर्णांक step)
अणु
	पूर्णांक i, cpu = smp_processor_id();

	क्रम (i = cpu + 1; i < cpu + thपढ़ोs_per_core; i++)
		जबतक(per_cpu(split_state, i).step < step)
			barrier();

	/* Order the रुको loop vs any subsequent loads/stores. */
	mb();
पूर्ण

अटल व्योम update_hid_in_slw(u64 hid0)
अणु
	u64 idle_states = pnv_get_supported_cpuidle_states();

	अगर (idle_states & OPAL_PM_WINKLE_ENABLED) अणु
		/* OPAL call to patch slw with the new HID0 value */
		u64 cpu_pir = hard_smp_processor_id();

		opal_slw_set_reg(cpu_pir, SPRN_HID0, hid0);
	पूर्ण
पूर्ण

अटल व्योम unsplit_core(व्योम)
अणु
	u64 hid0, mask;
	पूर्णांक i, cpu;

	mask = HID0_POWER8_2LPARMODE | HID0_POWER8_4LPARMODE;

	cpu = smp_processor_id();
	अगर (cpu_thपढ़ो_in_core(cpu) != 0) अणु
		जबतक (mfspr(SPRN_HID0) & mask)
			घातer7_idle_type(PNV_THREAD_NAP);

		per_cpu(split_state, cpu).step = SYNC_STEP_UNSPLIT;
		वापस;
	पूर्ण

	hid0 = mfspr(SPRN_HID0);
	hid0 &= ~HID0_POWER8_DYNLPARDIS;
	update_घातer8_hid0(hid0);
	update_hid_in_slw(hid0);

	जबतक (mfspr(SPRN_HID0) & mask)
		cpu_relax();

	/* Wake secondaries out of NAP */
	क्रम (i = cpu + 1; i < cpu + thपढ़ोs_per_core; i++)
		smp_send_reschedule(i);

	रुको_क्रम_sync_step(SYNC_STEP_UNSPLIT);
पूर्ण

अटल व्योम split_core(पूर्णांक new_mode)
अणु
	काष्ठा अणु  u64 value; u64 mask; पूर्ण split_parms[2] = अणु
		अणु HID0_POWER8_1TO2LPAR, HID0_POWER8_2LPARMODE पूर्ण,
		अणु HID0_POWER8_1TO4LPAR, HID0_POWER8_4LPARMODE पूर्ण
	पूर्ण;
	पूर्णांक i, cpu;
	u64 hid0;

	/* Convert new_mode (2 or 4) पूर्णांकo an index पूर्णांकo our parms array */
	i = (new_mode >> 1) - 1;
	BUG_ON(i < 0 || i > 1);

	cpu = smp_processor_id();
	अगर (cpu_thपढ़ो_in_core(cpu) != 0) अणु
		split_core_secondary_loop(&per_cpu(split_state, cpu).step);
		वापस;
	पूर्ण

	रुको_क्रम_sync_step(SYNC_STEP_REAL_MODE);

	/* Write new mode */
	hid0  = mfspr(SPRN_HID0);
	hid0 |= HID0_POWER8_DYNLPARDIS | split_parms[i].value;
	update_घातer8_hid0(hid0);
	update_hid_in_slw(hid0);

	/* Wait क्रम it to happen */
	जबतक (!(mfspr(SPRN_HID0) & split_parms[i].mask))
		cpu_relax();
पूर्ण

अटल व्योम cpu_करो_split(पूर्णांक new_mode)
अणु
	/*
	 * At boot subcores_per_core will be 0, so we will always unsplit at
	 * boot. In the usual हाल where the core is alपढ़ोy unsplit it's a
	 * nop, and this just ensures the kernel's notion of the mode is
	 * consistent with the hardware.
	 */
	अगर (subcores_per_core != 1)
		unsplit_core();

	अगर (new_mode != 1)
		split_core(new_mode);

	mb();
	per_cpu(split_state, smp_processor_id()).step = SYNC_STEP_FINISHED;
पूर्ण

bool cpu_core_split_required(व्योम)
अणु
	smp_rmb();

	अगर (!new_split_mode)
		वापस false;

	cpu_करो_split(new_split_mode);

	वापस true;
पूर्ण

व्योम update_subcore_sibling_mask(व्योम)
अणु
	पूर्णांक cpu;
	/*
	 * sibling mask क्रम the first cpu. Left shअगरt this by required bits
	 * to get sibling mask क्रम the rest of the cpus.
	 */
	पूर्णांक sibling_mask_first_cpu =  (1 << thपढ़ोs_per_subcore) - 1;

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक tid = cpu_thपढ़ो_in_core(cpu);
		पूर्णांक offset = (tid / thपढ़ोs_per_subcore) * thपढ़ोs_per_subcore;
		पूर्णांक mask = sibling_mask_first_cpu << offset;

		paca_ptrs[cpu]->subcore_sibling_mask = mask;

	पूर्ण
पूर्ण

अटल पूर्णांक cpu_update_split_mode(व्योम *data)
अणु
	पूर्णांक cpu, new_mode = *(पूर्णांक *)data;

	अगर (this_cpu_ptr(&split_state)->master) अणु
		new_split_mode = new_mode;
		smp_wmb();

		cpumask_andnot(cpu_offline_mask, cpu_present_mask,
			       cpu_online_mask);

		/* This should work even though the cpu is offline */
		क्रम_each_cpu(cpu, cpu_offline_mask)
			smp_send_reschedule(cpu);
	पूर्ण

	cpu_करो_split(new_mode);

	अगर (this_cpu_ptr(&split_state)->master) अणु
		/* Wait क्रम all cpus to finish beक्रमe we touch subcores_per_core */
		क्रम_each_present_cpu(cpu) अणु
			अगर (cpu >= setup_max_cpus)
				अवरोध;

			जबतक(per_cpu(split_state, cpu).step < SYNC_STEP_FINISHED)
				barrier();
		पूर्ण

		new_split_mode = 0;

		/* Make the new mode खुला */
		subcores_per_core = new_mode;
		thपढ़ोs_per_subcore = thपढ़ोs_per_core / subcores_per_core;
		update_subcore_sibling_mask();

		/* Make sure the new mode is written beक्रमe we निकास */
		mb();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_subcores_per_core(पूर्णांक new_mode)
अणु
	काष्ठा split_state *state;
	पूर्णांक cpu;

	अगर (kvm_hv_mode_active()) अणु
		pr_err("Unable to change split core mode while KVM active.\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * We are only called at boot, or from the sysfs ग_लिखो. If that ever
	 * changes we'll need a lock here.
	 */
	BUG_ON(new_mode < 1 || new_mode > 4 || new_mode == 3);

	क्रम_each_present_cpu(cpu) अणु
		state = &per_cpu(split_state, cpu);
		state->step = SYNC_STEP_INITIAL;
		state->master = 0;
	पूर्ण

	cpus_पढ़ो_lock();

	/* This cpu will update the globals beक्रमe निकासing stop machine */
	this_cpu_ptr(&split_state)->master = 1;

	/* Ensure state is consistent beक्रमe we call the other cpus */
	mb();

	stop_machine_cpuslocked(cpu_update_split_mode, &new_mode,
				cpu_online_mask);

	cpus_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल sमाप_प्रकार __used store_subcores_per_core(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	/* We are serialised by the attribute lock */

	rc = माला_पूछो(buf, "%lx", &val);
	अगर (rc != 1)
		वापस -EINVAL;

	चयन (val) अणु
	हाल 1:
	हाल 2:
	हाल 4:
		अगर (subcores_per_core == val)
			/* Nothing to करो */
			जाओ out;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rc = set_subcores_per_core(val);
	अगर (rc)
		वापस rc;

out:
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_subcores_per_core(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%x\n", subcores_per_core);
पूर्ण

अटल DEVICE_ATTR(subcores_per_core, 0644,
		show_subcores_per_core, store_subcores_per_core);

अटल पूर्णांक subcore_init(व्योम)
अणु
	अचिन्हित pvr_ver;

	pvr_ver = PVR_VER(mfspr(SPRN_PVR));

	अगर (pvr_ver != PVR_POWER8 &&
	    pvr_ver != PVR_POWER8E &&
	    pvr_ver != PVR_POWER8NVL)
		वापस 0;

	/*
	 * We need all thपढ़ोs in a core to be present to split/unsplit so
         * जारी only अगर max_cpus are aligned to thपढ़ोs_per_core.
	 */
	अगर (setup_max_cpus % thपढ़ोs_per_core)
		वापस 0;

	BUG_ON(!alloc_cpumask_var(&cpu_offline_mask, GFP_KERNEL));

	set_subcores_per_core(1);

	वापस device_create_file(cpu_subsys.dev_root,
				  &dev_attr_subcores_per_core);
पूर्ण
machine_device_initcall(घातernv, subcore_init);
