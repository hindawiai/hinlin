<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_idle.c - native hardware idle loop क्रम modern Intel processors
 *
 * Copyright (c) 2013 - 2020, Intel Corporation.
 * Len Brown <len.brown@पूर्णांकel.com>
 * Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

/*
 * पूर्णांकel_idle is a cpuidle driver that loads on all Intel CPUs with MWAIT
 * in lieu of the legacy ACPI processor_idle driver.  The पूर्णांकent is to
 * make Linux more efficient on these processors, as पूर्णांकel_idle knows
 * more than ACPI, as well as make Linux more immune to ACPI BIOS bugs.
 */

/*
 * Design Assumptions
 *
 * All CPUs have same idle states as boot CPU
 *
 * Chipset BM_STS (bus master status) bit is a NOP
 *	क्रम preventing entry पूर्णांकo deep C-states
 *
 * CPU will flush caches as needed when entering a C-state via MWAIT
 *	(in contrast to entering ACPI C3, in which हाल the WBINVD
 *	inकाष्ठाion needs to be executed to flush the caches)
 */

/*
 * Known limitations
 *
 * ACPI has a .suspend hack to turn off deep c-statees during suspend
 * to aव्योम complications with the lapic समयr workaround.
 * Have not seen issues with suspend, but may need same workaround here.
 *
 */

/* un-comment DEBUG to enable pr_debug() statements */
/* #घोषणा DEBUG */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/tick.h>
#समावेश <trace/events/घातer.h>
#समावेश <linux/sched.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/moduleparam.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/mरुको.h>
#समावेश <यंत्र/msr.h>

#घोषणा INTEL_IDLE_VERSION "0.5.1"

अटल काष्ठा cpuidle_driver पूर्णांकel_idle_driver = अणु
	.name = "intel_idle",
	.owner = THIS_MODULE,
पूर्ण;
/* पूर्णांकel_idle.max_cstate=0 disables driver */
अटल पूर्णांक max_cstate = CPUIDLE_STATE_MAX - 1;
अटल अचिन्हित पूर्णांक disabled_states_mask;

अटल काष्ठा cpuidle_device __percpu *पूर्णांकel_idle_cpuidle_devices;

अटल अचिन्हित दीर्घ स्वतः_demotion_disable_flags;
अटल bool disable_promotion_to_c1e;

काष्ठा idle_cpu अणु
	काष्ठा cpuidle_state *state_table;

	/*
	 * Hardware C-state स्वतः-demotion may not always be optimal.
	 * Indicate which enable bits to clear here.
	 */
	अचिन्हित दीर्घ स्वतः_demotion_disable_flags;
	bool byt_स्वतः_demotion_disable_flag;
	bool disable_promotion_to_c1e;
	bool use_acpi;
पूर्ण;

अटल स्थिर काष्ठा idle_cpu *icpu __initdata;
अटल काष्ठा cpuidle_state *cpuidle_state_table __initdata;

अटल अचिन्हित पूर्णांक mरुको_substates __initdata;

/*
 * Enable this state by शेष even अगर the ACPI _CST करोes not list it.
 */
#घोषणा CPUIDLE_FLAG_ALWAYS_ENABLE	BIT(15)

/*
 * MWAIT takes an 8-bit "hint" in EAX "suggesting"
 * the C-state (top nibble) and sub-state (bottom nibble)
 * 0x00 means "MWAIT(C1)", 0x10 means "MWAIT(C2)" etc.
 *
 * We store the hपूर्णांक at the top of our "flags" क्रम each state.
 */
#घोषणा flg2MWAIT(flags) (((flags) >> 24) & 0xFF)
#घोषणा MWAIT2flg(eax) ((eax & 0xFF) << 24)

/**
 * पूर्णांकel_idle - Ask the processor to enter the given idle state.
 * @dev: cpuidle device of the target CPU.
 * @drv: cpuidle driver (assumed to poपूर्णांक to पूर्णांकel_idle_driver).
 * @index: Target idle state index.
 *
 * Use the MWAIT inकाष्ठाion to notअगरy the processor that the CPU represented by
 * @dev is idle and it can try to enter the idle state corresponding to @index.
 *
 * If the local APIC समयr is not known to be reliable in the target idle state,
 * enable one-shot tick broadcasting क्रम the target CPU beक्रमe executing MWAIT.
 *
 * Optionally call leave_mm() क्रम the target CPU upfront to aव्योम wakeups due to
 * flushing user TLBs.
 *
 * Must be called under local_irq_disable().
 */
अटल __cpuidle पूर्णांक पूर्णांकel_idle(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	काष्ठा cpuidle_state *state = &drv->states[index];
	अचिन्हित दीर्घ eax = flg2MWAIT(state->flags);
	अचिन्हित दीर्घ ecx = 1; /* अवरोध on पूर्णांकerrupt flag */

	mरुको_idle_with_hपूर्णांकs(eax, ecx);

	वापस index;
पूर्ण

/**
 * पूर्णांकel_idle_s2idle - Ask the processor to enter the given idle state.
 * @dev: cpuidle device of the target CPU.
 * @drv: cpuidle driver (assumed to poपूर्णांक to पूर्णांकel_idle_driver).
 * @index: Target idle state index.
 *
 * Use the MWAIT inकाष्ठाion to notअगरy the processor that the CPU represented by
 * @dev is idle and it can try to enter the idle state corresponding to @index.
 *
 * Invoked as a suspend-to-idle callback routine with frozen user space, frozen
 * scheduler tick and suspended scheduler घड़ी on the target CPU.
 */
अटल __cpuidle पूर्णांक पूर्णांकel_idle_s2idle(काष्ठा cpuidle_device *dev,
				       काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	अचिन्हित दीर्घ eax = flg2MWAIT(drv->states[index].flags);
	अचिन्हित दीर्घ ecx = 1; /* अवरोध on पूर्णांकerrupt flag */

	mरुको_idle_with_hपूर्णांकs(eax, ecx);

	वापस 0;
पूर्ण

/*
 * States are indexed by the cstate number,
 * which is also the index पूर्णांकo the MWAIT hपूर्णांक array.
 * Thus C0 is a dummy.
 */
अटल काष्ठा cpuidle_state nehalem_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 3,
		.target_residency = 6,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 20,
		.target_residency = 80,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 200,
		.target_residency = 800,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state snb_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 80,
		.target_residency = 211,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 104,
		.target_residency = 345,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7",
		.desc = "MWAIT 0x30",
		.flags = MWAIT2flg(0x30) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 109,
		.target_residency = 345,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state byt_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 1,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6N",
		.desc = "MWAIT 0x58",
		.flags = MWAIT2flg(0x58) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 300,
		.target_residency = 275,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6S",
		.desc = "MWAIT 0x52",
		.flags = MWAIT2flg(0x52) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 500,
		.target_residency = 560,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7",
		.desc = "MWAIT 0x60",
		.flags = MWAIT2flg(0x60) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 1200,
		.target_residency = 4000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7S",
		.desc = "MWAIT 0x64",
		.flags = MWAIT2flg(0x64) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 10000,
		.target_residency = 20000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state cht_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 1,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6N",
		.desc = "MWAIT 0x58",
		.flags = MWAIT2flg(0x58) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 80,
		.target_residency = 275,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6S",
		.desc = "MWAIT 0x52",
		.flags = MWAIT2flg(0x52) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 200,
		.target_residency = 560,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7",
		.desc = "MWAIT 0x60",
		.flags = MWAIT2flg(0x60) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 1200,
		.target_residency = 4000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7S",
		.desc = "MWAIT 0x64",
		.flags = MWAIT2flg(0x64) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 10000,
		.target_residency = 20000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state ivb_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 1,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 59,
		.target_residency = 156,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 80,
		.target_residency = 300,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7",
		.desc = "MWAIT 0x30",
		.flags = MWAIT2flg(0x30) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 87,
		.target_residency = 300,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state ivt_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 1,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 80,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 59,
		.target_residency = 156,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 82,
		.target_residency = 300,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state ivt_cstates_4s[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 1,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 250,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 59,
		.target_residency = 300,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 84,
		.target_residency = 400,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state ivt_cstates_8s[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 1,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 500,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 59,
		.target_residency = 600,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 88,
		.target_residency = 700,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state hsw_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 33,
		.target_residency = 100,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 133,
		.target_residency = 400,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7s",
		.desc = "MWAIT 0x32",
		.flags = MWAIT2flg(0x32) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 166,
		.target_residency = 500,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C8",
		.desc = "MWAIT 0x40",
		.flags = MWAIT2flg(0x40) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 300,
		.target_residency = 900,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C9",
		.desc = "MWAIT 0x50",
		.flags = MWAIT2flg(0x50) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 600,
		.target_residency = 1800,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C10",
		.desc = "MWAIT 0x60",
		.flags = MWAIT2flg(0x60) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 2600,
		.target_residency = 7700,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;
अटल काष्ठा cpuidle_state bdw_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 40,
		.target_residency = 100,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 133,
		.target_residency = 400,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7s",
		.desc = "MWAIT 0x32",
		.flags = MWAIT2flg(0x32) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 166,
		.target_residency = 500,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C8",
		.desc = "MWAIT 0x40",
		.flags = MWAIT2flg(0x40) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 300,
		.target_residency = 900,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C9",
		.desc = "MWAIT 0x50",
		.flags = MWAIT2flg(0x50) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 600,
		.target_residency = 1800,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C10",
		.desc = "MWAIT 0x60",
		.flags = MWAIT2flg(0x60) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 2600,
		.target_residency = 7700,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state skl_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C3",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 70,
		.target_residency = 100,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 85,
		.target_residency = 200,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7s",
		.desc = "MWAIT 0x33",
		.flags = MWAIT2flg(0x33) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 124,
		.target_residency = 800,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C8",
		.desc = "MWAIT 0x40",
		.flags = MWAIT2flg(0x40) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 200,
		.target_residency = 800,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C9",
		.desc = "MWAIT 0x50",
		.flags = MWAIT2flg(0x50) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 480,
		.target_residency = 5000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C10",
		.desc = "MWAIT 0x60",
		.flags = MWAIT2flg(0x60) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 890,
		.target_residency = 5000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state skx_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 133,
		.target_residency = 600,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state icx_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 1,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 4,
		.target_residency = 4,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 170,
		.target_residency = 600,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state atom_cstates[] __initdata = अणु
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C2",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10),
		.निकास_latency = 20,
		.target_residency = 80,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C4",
		.desc = "MWAIT 0x30",
		.flags = MWAIT2flg(0x30) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 100,
		.target_residency = 400,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x52",
		.flags = MWAIT2flg(0x52) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 140,
		.target_residency = 560,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;
अटल काष्ठा cpuidle_state tangier_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 4,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C4",
		.desc = "MWAIT 0x30",
		.flags = MWAIT2flg(0x30) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 100,
		.target_residency = 400,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x52",
		.flags = MWAIT2flg(0x52) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 140,
		.target_residency = 560,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7",
		.desc = "MWAIT 0x60",
		.flags = MWAIT2flg(0x60) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 1200,
		.target_residency = 4000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C9",
		.desc = "MWAIT 0x64",
		.flags = MWAIT2flg(0x64) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 10000,
		.target_residency = 20000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;
अटल काष्ठा cpuidle_state avn_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x51",
		.flags = MWAIT2flg(0x51) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 15,
		.target_residency = 45,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;
अटल काष्ठा cpuidle_state knl_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 1,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x10",
		.flags = MWAIT2flg(0x10) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 120,
		.target_residency = 500,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state bxt_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 133,
		.target_residency = 133,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C7s",
		.desc = "MWAIT 0x31",
		.flags = MWAIT2flg(0x31) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 155,
		.target_residency = 155,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C8",
		.desc = "MWAIT 0x40",
		.flags = MWAIT2flg(0x40) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 1000,
		.target_residency = 1000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C9",
		.desc = "MWAIT 0x50",
		.flags = MWAIT2flg(0x50) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 2000,
		.target_residency = 2000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C10",
		.desc = "MWAIT 0x60",
		.flags = MWAIT2flg(0x60) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 10000,
		.target_residency = 10000,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल काष्ठा cpuidle_state dnv_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 10,
		.target_residency = 20,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 50,
		.target_residency = 500,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

/*
 * Note, depending on HW and FW revision, SnowRidge SoC may or may not support
 * C6, and this is indicated in the CPUID mरुको leaf.
 */
अटल काष्ठा cpuidle_state snr_cstates[] __initdata = अणु
	अणु
		.name = "C1",
		.desc = "MWAIT 0x00",
		.flags = MWAIT2flg(0x00),
		.निकास_latency = 2,
		.target_residency = 2,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C1E",
		.desc = "MWAIT 0x01",
		.flags = MWAIT2flg(0x01) | CPUIDLE_FLAG_ALWAYS_ENABLE,
		.निकास_latency = 15,
		.target_residency = 25,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.name = "C6",
		.desc = "MWAIT 0x20",
		.flags = MWAIT2flg(0x20) | CPUIDLE_FLAG_TLB_FLUSHED,
		.निकास_latency = 130,
		.target_residency = 500,
		.enter = &पूर्णांकel_idle,
		.enter_s2idle = पूर्णांकel_idle_s2idle, पूर्ण,
	अणु
		.enter = शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_nehalem __initस्थिर = अणु
	.state_table = nehalem_cstates,
	.स्वतः_demotion_disable_flags = NHM_C1_AUTO_DEMOTE | NHM_C3_AUTO_DEMOTE,
	.disable_promotion_to_c1e = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_nhx __initस्थिर = अणु
	.state_table = nehalem_cstates,
	.स्वतः_demotion_disable_flags = NHM_C1_AUTO_DEMOTE | NHM_C3_AUTO_DEMOTE,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_atom __initस्थिर = अणु
	.state_table = atom_cstates,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_tangier __initस्थिर = अणु
	.state_table = tangier_cstates,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_lincroft __initस्थिर = अणु
	.state_table = atom_cstates,
	.स्वतः_demotion_disable_flags = ATM_LNC_C6_AUTO_DEMOTE,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_snb __initस्थिर = अणु
	.state_table = snb_cstates,
	.disable_promotion_to_c1e = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_snx __initस्थिर = अणु
	.state_table = snb_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_byt __initस्थिर = अणु
	.state_table = byt_cstates,
	.disable_promotion_to_c1e = true,
	.byt_स्वतः_demotion_disable_flag = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_cht __initस्थिर = अणु
	.state_table = cht_cstates,
	.disable_promotion_to_c1e = true,
	.byt_स्वतः_demotion_disable_flag = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_ivb __initस्थिर = अणु
	.state_table = ivb_cstates,
	.disable_promotion_to_c1e = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_ivt __initस्थिर = अणु
	.state_table = ivt_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_hsw __initस्थिर = अणु
	.state_table = hsw_cstates,
	.disable_promotion_to_c1e = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_hsx __initस्थिर = अणु
	.state_table = hsw_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_bdw __initस्थिर = अणु
	.state_table = bdw_cstates,
	.disable_promotion_to_c1e = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_bdx __initस्थिर = अणु
	.state_table = bdw_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_skl __initस्थिर = अणु
	.state_table = skl_cstates,
	.disable_promotion_to_c1e = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_skx __initस्थिर = अणु
	.state_table = skx_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_icx __initस्थिर = अणु
	.state_table = icx_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_avn __initस्थिर = अणु
	.state_table = avn_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_knl __initस्थिर = अणु
	.state_table = knl_cstates,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_bxt __initस्थिर = अणु
	.state_table = bxt_cstates,
	.disable_promotion_to_c1e = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_dnv __initस्थिर = अणु
	.state_table = dnv_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा idle_cpu idle_cpu_snr __initस्थिर = अणु
	.state_table = snr_cstates,
	.disable_promotion_to_c1e = true,
	.use_acpi = true,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_idle_ids[] __initस्थिर = अणु
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM_EP,		&idle_cpu_nhx),
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM,		&idle_cpu_nehalem),
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM_G,		&idle_cpu_nehalem),
	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE,		&idle_cpu_nehalem),
	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE_EP,		&idle_cpu_nhx),
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM_EX,		&idle_cpu_nhx),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_BONNELL,	&idle_cpu_atom),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_BONNELL_MID,	&idle_cpu_lincroft),
	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE_EX,		&idle_cpu_nhx),
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE,		&idle_cpu_snb),
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE_X,	&idle_cpu_snx),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SALTWELL,	&idle_cpu_atom),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT,	&idle_cpu_byt),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT_MID,	&idle_cpu_tangier),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT,	&idle_cpu_cht),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE,		&idle_cpu_ivb),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE_X,		&idle_cpu_ivt),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL,		&idle_cpu_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_X,		&idle_cpu_hsx),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_L,		&idle_cpu_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_G,		&idle_cpu_hsw),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT_D,	&idle_cpu_avn),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL,		&idle_cpu_bdw),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_G,		&idle_cpu_bdw),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X,		&idle_cpu_bdx),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_D,		&idle_cpu_bdx),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_L,		&idle_cpu_skl),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE,		&idle_cpu_skl),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE_L,		&idle_cpu_skl),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE,		&idle_cpu_skl),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_X,		&idle_cpu_skx),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_X,		&idle_cpu_icx),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_D,		&idle_cpu_icx),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNL,	&idle_cpu_knl),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNM,	&idle_cpu_knl),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT,	&idle_cpu_bxt),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_PLUS,	&idle_cpu_bxt),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_D,	&idle_cpu_dnv),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_D,	&idle_cpu_snr),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_mरुको_ids[] __initस्थिर = अणु
	X86_MATCH_VENDOR_FAM_FEATURE(INTEL, 6, X86_FEATURE_MWAIT, शून्य),
	अणुपूर्ण
पूर्ण;

अटल bool __init पूर्णांकel_idle_max_cstate_reached(पूर्णांक cstate)
अणु
	अगर (cstate + 1 > max_cstate) अणु
		pr_info("max_cstate %d reached\n", max_cstate);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool __init पूर्णांकel_idle_state_needs_समयr_stop(काष्ठा cpuidle_state *state)
अणु
	अचिन्हित दीर्घ eax = flg2MWAIT(state->flags);

	अगर (boot_cpu_has(X86_FEATURE_ARAT))
		वापस false;

	/*
	 * Switch over to one-shot tick broadcast अगर the target C-state
	 * is deeper than C1.
	 */
	वापस !!((eax >> MWAIT_SUBSTATE_SIZE) & MWAIT_CSTATE_MASK);
पूर्ण

#अगर_घोषित CONFIG_ACPI_PROCESSOR_CSTATE
#समावेश <acpi/processor.h>

अटल bool no_acpi __पढ़ो_mostly;
module_param(no_acpi, bool, 0444);
MODULE_PARM_DESC(no_acpi, "Do not use ACPI _CST for building the idle states list");

अटल bool क्रमce_use_acpi __पढ़ो_mostly; /* No effect अगर no_acpi is set. */
module_param_named(use_acpi, क्रमce_use_acpi, bool, 0444);
MODULE_PARM_DESC(use_acpi, "Use ACPI _CST for building the idle states list");

अटल काष्ठा acpi_processor_घातer acpi_state_table __initdata;

/**
 * पूर्णांकel_idle_cst_usable - Check अगर the _CST inक्रमmation can be used.
 *
 * Check अगर all of the C-states listed by _CST in the max_cstate range are
 * ACPI_CSTATE_FFH, which means that they should be entered via MWAIT.
 */
अटल bool __init पूर्णांकel_idle_cst_usable(व्योम)
अणु
	पूर्णांक cstate, limit;

	limit = min_t(पूर्णांक, min_t(पूर्णांक, CPUIDLE_STATE_MAX, max_cstate + 1),
		      acpi_state_table.count);

	क्रम (cstate = 1; cstate < limit; cstate++) अणु
		काष्ठा acpi_processor_cx *cx = &acpi_state_table.states[cstate];

		अगर (cx->entry_method != ACPI_CSTATE_FFH)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool __init पूर्णांकel_idle_acpi_cst_extract(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	अगर (no_acpi) अणु
		pr_debug("Not allowed to use ACPI _CST\n");
		वापस false;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा acpi_processor *pr = per_cpu(processors, cpu);

		अगर (!pr)
			जारी;

		अगर (acpi_processor_evaluate_cst(pr->handle, cpu, &acpi_state_table))
			जारी;

		acpi_state_table.count++;

		अगर (!पूर्णांकel_idle_cst_usable())
			जारी;

		अगर (!acpi_processor_claim_cst_control())
			अवरोध;

		वापस true;
	पूर्ण

	acpi_state_table.count = 0;
	pr_debug("ACPI _CST not found or not usable\n");
	वापस false;
पूर्ण

अटल व्योम __init पूर्णांकel_idle_init_cstates_acpi(काष्ठा cpuidle_driver *drv)
अणु
	पूर्णांक cstate, limit = min_t(पूर्णांक, CPUIDLE_STATE_MAX, acpi_state_table.count);

	/*
	 * If limit > 0, पूर्णांकel_idle_cst_usable() has वापसed 'true', so all of
	 * the पूर्णांकeresting states are ACPI_CSTATE_FFH.
	 */
	क्रम (cstate = 1; cstate < limit; cstate++) अणु
		काष्ठा acpi_processor_cx *cx;
		काष्ठा cpuidle_state *state;

		अगर (पूर्णांकel_idle_max_cstate_reached(cstate - 1))
			अवरोध;

		cx = &acpi_state_table.states[cstate];

		state = &drv->states[drv->state_count++];

		snम_लिखो(state->name, CPUIDLE_NAME_LEN, "C%d_ACPI", cstate);
		strlcpy(state->desc, cx->desc, CPUIDLE_DESC_LEN);
		state->निकास_latency = cx->latency;
		/*
		 * For C1-type C-states use the same number क्रम both the निकास
		 * latency and target residency, because that is the हाल क्रम
		 * C1 in the majority of the अटल C-states tables above.
		 * For the other types of C-states, however, set the target
		 * residency to 3 बार the निकास latency which should lead to
		 * a reasonable balance between energy-efficiency and
		 * perक्रमmance in the majority of पूर्णांकeresting हालs.
		 */
		state->target_residency = cx->latency;
		अगर (cx->type > ACPI_STATE_C1)
			state->target_residency *= 3;

		state->flags = MWAIT2flg(cx->address);
		अगर (cx->type > ACPI_STATE_C2)
			state->flags |= CPUIDLE_FLAG_TLB_FLUSHED;

		अगर (disabled_states_mask & BIT(cstate))
			state->flags |= CPUIDLE_FLAG_OFF;

		अगर (पूर्णांकel_idle_state_needs_समयr_stop(state))
			state->flags |= CPUIDLE_FLAG_TIMER_STOP;

		state->enter = पूर्णांकel_idle;
		state->enter_s2idle = पूर्णांकel_idle_s2idle;
	पूर्ण
पूर्ण

अटल bool __init पूर्णांकel_idle_off_by_शेष(u32 mरुको_hपूर्णांक)
अणु
	पूर्णांक cstate, limit;

	/*
	 * If there are no _CST C-states, करो not disable any C-states by
	 * शेष.
	 */
	अगर (!acpi_state_table.count)
		वापस false;

	limit = min_t(पूर्णांक, CPUIDLE_STATE_MAX, acpi_state_table.count);
	/*
	 * If limit > 0, पूर्णांकel_idle_cst_usable() has वापसed 'true', so all of
	 * the पूर्णांकeresting states are ACPI_CSTATE_FFH.
	 */
	क्रम (cstate = 1; cstate < limit; cstate++) अणु
		अगर (acpi_state_table.states[cstate].address == mरुको_hपूर्णांक)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण
#अन्यथा /* !CONFIG_ACPI_PROCESSOR_CSTATE */
#घोषणा क्रमce_use_acpi	(false)

अटल अंतरभूत bool पूर्णांकel_idle_acpi_cst_extract(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम पूर्णांकel_idle_init_cstates_acpi(काष्ठा cpuidle_driver *drv) अणु पूर्ण
अटल अंतरभूत bool पूर्णांकel_idle_off_by_शेष(u32 mरुको_hपूर्णांक) अणु वापस false; पूर्ण
#पूर्ण_अगर /* !CONFIG_ACPI_PROCESSOR_CSTATE */

/**
 * ivt_idle_state_table_update - Tune the idle states table क्रम Ivy Town.
 *
 * Tune IVT multi-socket tarमाला_लो.
 * Assumption: num_sockets == (max_package_num + 1).
 */
अटल व्योम __init ivt_idle_state_table_update(व्योम)
अणु
	/* IVT uses a dअगरferent table क्रम 1-2, 3-4, and > 4 sockets */
	पूर्णांक cpu, package_num, num_sockets = 1;

	क्रम_each_online_cpu(cpu) अणु
		package_num = topology_physical_package_id(cpu);
		अगर (package_num + 1 > num_sockets) अणु
			num_sockets = package_num + 1;

			अगर (num_sockets > 4) अणु
				cpuidle_state_table = ivt_cstates_8s;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (num_sockets > 2)
		cpuidle_state_table = ivt_cstates_4s;

	/* अन्यथा, 1 and 2 socket प्रणालीs use शेष ivt_cstates */
पूर्ण

/**
 * irtl_2_usec - IRTL to microseconds conversion.
 * @irtl: IRTL MSR value.
 *
 * Translate the IRTL (Interrupt Response Time Limit) MSR value to microseconds.
 */
अटल अचिन्हित दीर्घ दीर्घ __init irtl_2_usec(अचिन्हित दीर्घ दीर्घ irtl)
अणु
	अटल स्थिर अचिन्हित पूर्णांक irtl_ns_units[] __initस्थिर = अणु
		1, 32, 1024, 32768, 1048576, 33554432, 0, 0
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ ns;

	अगर (!irtl)
		वापस 0;

	ns = irtl_ns_units[(irtl >> 10) & 0x7];

	वापस भाग_u64((irtl & 0x3FF) * ns, NSEC_PER_USEC);
पूर्ण

/**
 * bxt_idle_state_table_update - Fix up the Broxton idle states table.
 *
 * On BXT, trust the IRTL (Interrupt Response Time Limit) MSR to show the
 * definitive maximum latency and use the same value क्रम target_residency.
 */
अटल व्योम __init bxt_idle_state_table_update(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक usec;

	rdmsrl(MSR_PKGC6_IRTL, msr);
	usec = irtl_2_usec(msr);
	अगर (usec) अणु
		bxt_cstates[2].निकास_latency = usec;
		bxt_cstates[2].target_residency = usec;
	पूर्ण

	rdmsrl(MSR_PKGC7_IRTL, msr);
	usec = irtl_2_usec(msr);
	अगर (usec) अणु
		bxt_cstates[3].निकास_latency = usec;
		bxt_cstates[3].target_residency = usec;
	पूर्ण

	rdmsrl(MSR_PKGC8_IRTL, msr);
	usec = irtl_2_usec(msr);
	अगर (usec) अणु
		bxt_cstates[4].निकास_latency = usec;
		bxt_cstates[4].target_residency = usec;
	पूर्ण

	rdmsrl(MSR_PKGC9_IRTL, msr);
	usec = irtl_2_usec(msr);
	अगर (usec) अणु
		bxt_cstates[5].निकास_latency = usec;
		bxt_cstates[5].target_residency = usec;
	पूर्ण

	rdmsrl(MSR_PKGC10_IRTL, msr);
	usec = irtl_2_usec(msr);
	अगर (usec) अणु
		bxt_cstates[6].निकास_latency = usec;
		bxt_cstates[6].target_residency = usec;
	पूर्ण

पूर्ण

/**
 * sklh_idle_state_table_update - Fix up the Sky Lake idle states table.
 *
 * On SKL-H (model 0x5e) skip C8 and C9 अगर C10 is enabled and SGX disabled.
 */
अटल व्योम __init sklh_idle_state_table_update(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;


	/* अगर PC10 disabled via cmdline पूर्णांकel_idle.max_cstate=7 or shallower */
	अगर (max_cstate <= 7)
		वापस;

	/* अगर PC10 not present in CPUID.MWAIT.EDX */
	अगर ((mरुको_substates & (0xF << 28)) == 0)
		वापस;

	rdmsrl(MSR_PKG_CST_CONFIG_CONTROL, msr);

	/* PC10 is not enabled in PKG C-state limit */
	अगर ((msr & 0xF) != 8)
		वापस;

	ecx = 0;
	cpuid(7, &eax, &ebx, &ecx, &edx);

	/* अगर SGX is present */
	अगर (ebx & (1 << 2)) अणु

		rdmsrl(MSR_IA32_FEAT_CTL, msr);

		/* अगर SGX is enabled */
		अगर (msr & (1 << 18))
			वापस;
	पूर्ण

	skl_cstates[5].flags |= CPUIDLE_FLAG_UNUSABLE;	/* C8-SKL */
	skl_cstates[6].flags |= CPUIDLE_FLAG_UNUSABLE;	/* C9-SKL */
पूर्ण

अटल bool __init पूर्णांकel_idle_verअगरy_cstate(अचिन्हित पूर्णांक mरुको_hपूर्णांक)
अणु
	अचिन्हित पूर्णांक mरुको_cstate = MWAIT_HINT2CSTATE(mरुको_hपूर्णांक) + 1;
	अचिन्हित पूर्णांक num_substates = (mरुको_substates >> mरुको_cstate * 4) &
					MWAIT_SUBSTATE_MASK;

	/* Ignore the C-state अगर there are NO sub-states in CPUID क्रम it. */
	अगर (num_substates == 0)
		वापस false;

	अगर (mरुको_cstate > 2 && !boot_cpu_has(X86_FEATURE_NONSTOP_TSC))
		mark_tsc_unstable("TSC halts in idle states deeper than C2");

	वापस true;
पूर्ण

अटल व्योम __init पूर्णांकel_idle_init_cstates_icpu(काष्ठा cpuidle_driver *drv)
अणु
	पूर्णांक cstate;

	चयन (boot_cpu_data.x86_model) अणु
	हाल INTEL_FAM6_IVYBRIDGE_X:
		ivt_idle_state_table_update();
		अवरोध;
	हाल INTEL_FAM6_ATOM_GOLDMONT:
	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
		bxt_idle_state_table_update();
		अवरोध;
	हाल INTEL_FAM6_SKYLAKE:
		sklh_idle_state_table_update();
		अवरोध;
	पूर्ण

	क्रम (cstate = 0; cstate < CPUIDLE_STATE_MAX; ++cstate) अणु
		अचिन्हित पूर्णांक mरुको_hपूर्णांक;

		अगर (पूर्णांकel_idle_max_cstate_reached(cstate))
			अवरोध;

		अगर (!cpuidle_state_table[cstate].enter &&
		    !cpuidle_state_table[cstate].enter_s2idle)
			अवरोध;

		/* If marked as unusable, skip this state. */
		अगर (cpuidle_state_table[cstate].flags & CPUIDLE_FLAG_UNUSABLE) अणु
			pr_debug("state %s is disabled\n",
				 cpuidle_state_table[cstate].name);
			जारी;
		पूर्ण

		mरुको_hपूर्णांक = flg2MWAIT(cpuidle_state_table[cstate].flags);
		अगर (!पूर्णांकel_idle_verअगरy_cstate(mरुको_hपूर्णांक))
			जारी;

		/* Structure copy. */
		drv->states[drv->state_count] = cpuidle_state_table[cstate];

		अगर ((disabled_states_mask & BIT(drv->state_count)) ||
		    ((icpu->use_acpi || क्रमce_use_acpi) &&
		     पूर्णांकel_idle_off_by_शेष(mरुको_hपूर्णांक) &&
		     !(cpuidle_state_table[cstate].flags & CPUIDLE_FLAG_ALWAYS_ENABLE)))
			drv->states[drv->state_count].flags |= CPUIDLE_FLAG_OFF;

		अगर (पूर्णांकel_idle_state_needs_समयr_stop(&drv->states[drv->state_count]))
			drv->states[drv->state_count].flags |= CPUIDLE_FLAG_TIMER_STOP;

		drv->state_count++;
	पूर्ण

	अगर (icpu->byt_स्वतः_demotion_disable_flag) अणु
		wrmsrl(MSR_CC6_DEMOTION_POLICY_CONFIG, 0);
		wrmsrl(MSR_MC6_DEMOTION_POLICY_CONFIG, 0);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_idle_cpuidle_driver_init - Create the list of available idle states.
 * @drv: cpuidle driver काष्ठाure to initialize.
 */
अटल व्योम __init पूर्णांकel_idle_cpuidle_driver_init(काष्ठा cpuidle_driver *drv)
अणु
	cpuidle_poll_state_init(drv);

	अगर (disabled_states_mask & BIT(0))
		drv->states[0].flags |= CPUIDLE_FLAG_OFF;

	drv->state_count = 1;

	अगर (icpu)
		पूर्णांकel_idle_init_cstates_icpu(drv);
	अन्यथा
		पूर्णांकel_idle_init_cstates_acpi(drv);
पूर्ण

अटल व्योम स्वतः_demotion_disable(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr_bits;

	rdmsrl(MSR_PKG_CST_CONFIG_CONTROL, msr_bits);
	msr_bits &= ~स्वतः_demotion_disable_flags;
	wrmsrl(MSR_PKG_CST_CONFIG_CONTROL, msr_bits);
पूर्ण

अटल व्योम c1e_promotion_disable(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr_bits;

	rdmsrl(MSR_IA32_POWER_CTL, msr_bits);
	msr_bits &= ~0x2;
	wrmsrl(MSR_IA32_POWER_CTL, msr_bits);
पूर्ण

/**
 * पूर्णांकel_idle_cpu_init - Register the target CPU with the cpuidle core.
 * @cpu: CPU to initialize.
 *
 * Register a cpuidle device object क्रम @cpu and update its MSRs in accordance
 * with the processor model flags.
 */
अटल पूर्णांक पूर्णांकel_idle_cpu_init(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuidle_device *dev;

	dev = per_cpu_ptr(पूर्णांकel_idle_cpuidle_devices, cpu);
	dev->cpu = cpu;

	अगर (cpuidle_रेजिस्टर_device(dev)) अणु
		pr_debug("cpuidle_register_device %d failed!\n", cpu);
		वापस -EIO;
	पूर्ण

	अगर (स्वतः_demotion_disable_flags)
		स्वतः_demotion_disable();

	अगर (disable_promotion_to_c1e)
		c1e_promotion_disable();

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_idle_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuidle_device *dev;

	अगर (!boot_cpu_has(X86_FEATURE_ARAT))
		tick_broadcast_enable();

	/*
	 * Some प्रणालीs can hotplug a cpu at runसमय after
	 * the kernel has booted, we have to initialize the
	 * driver in this हाल
	 */
	dev = per_cpu_ptr(पूर्णांकel_idle_cpuidle_devices, cpu);
	अगर (!dev->रेजिस्टरed)
		वापस पूर्णांकel_idle_cpu_init(cpu);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_idle_cpuidle_devices_uninit - Unरेजिस्टर all cpuidle devices.
 */
अटल व्योम __init पूर्णांकel_idle_cpuidle_devices_uninit(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_online_cpu(i)
		cpuidle_unरेजिस्टर_device(per_cpu_ptr(पूर्णांकel_idle_cpuidle_devices, i));
पूर्ण

अटल पूर्णांक __init पूर्णांकel_idle_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	अचिन्हित पूर्णांक eax, ebx, ecx;
	पूर्णांक retval;

	/* Do not load पूर्णांकel_idle at all क्रम now अगर idle= is passed */
	अगर (boot_option_idle_override != IDLE_NO_OVERRIDE)
		वापस -ENODEV;

	अगर (max_cstate == 0) अणु
		pr_debug("disabled\n");
		वापस -EPERM;
	पूर्ण

	id = x86_match_cpu(पूर्णांकel_idle_ids);
	अगर (id) अणु
		अगर (!boot_cpu_has(X86_FEATURE_MWAIT)) अणु
			pr_debug("Please enable MWAIT in BIOS SETUP\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		id = x86_match_cpu(पूर्णांकel_mरुको_ids);
		अगर (!id)
			वापस -ENODEV;
	पूर्ण

	अगर (boot_cpu_data.cpuid_level < CPUID_MWAIT_LEAF)
		वापस -ENODEV;

	cpuid(CPUID_MWAIT_LEAF, &eax, &ebx, &ecx, &mरुको_substates);

	अगर (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPORTED) ||
	    !(ecx & CPUID5_ECX_INTERRUPT_BREAK) ||
	    !mरुको_substates)
			वापस -ENODEV;

	pr_debug("MWAIT substates: 0x%x\n", mरुको_substates);

	icpu = (स्थिर काष्ठा idle_cpu *)id->driver_data;
	अगर (icpu) अणु
		cpuidle_state_table = icpu->state_table;
		स्वतः_demotion_disable_flags = icpu->स्वतः_demotion_disable_flags;
		disable_promotion_to_c1e = icpu->disable_promotion_to_c1e;
		अगर (icpu->use_acpi || क्रमce_use_acpi)
			पूर्णांकel_idle_acpi_cst_extract();
	पूर्ण अन्यथा अगर (!पूर्णांकel_idle_acpi_cst_extract()) अणु
		वापस -ENODEV;
	पूर्ण

	pr_debug("v" INTEL_IDLE_VERSION " model 0x%X\n",
		 boot_cpu_data.x86_model);

	पूर्णांकel_idle_cpuidle_devices = alloc_percpu(काष्ठा cpuidle_device);
	अगर (!पूर्णांकel_idle_cpuidle_devices)
		वापस -ENOMEM;

	पूर्णांकel_idle_cpuidle_driver_init(&पूर्णांकel_idle_driver);

	retval = cpuidle_रेजिस्टर_driver(&पूर्णांकel_idle_driver);
	अगर (retval) अणु
		काष्ठा cpuidle_driver *drv = cpuidle_get_driver();
		prपूर्णांकk(KERN_DEBUG pr_fmt("intel_idle yielding to %s\n"),
		       drv ? drv->name : "none");
		जाओ init_driver_fail;
	पूर्ण

	retval = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "idle/intel:online",
				   पूर्णांकel_idle_cpu_online, शून्य);
	अगर (retval < 0)
		जाओ hp_setup_fail;

	pr_debug("Local APIC timer is reliable in %s\n",
		 boot_cpu_has(X86_FEATURE_ARAT) ? "all C-states" : "C1");

	वापस 0;

hp_setup_fail:
	पूर्णांकel_idle_cpuidle_devices_uninit();
	cpuidle_unरेजिस्टर_driver(&पूर्णांकel_idle_driver);
init_driver_fail:
	मुक्त_percpu(पूर्णांकel_idle_cpuidle_devices);
	वापस retval;

पूर्ण
device_initcall(पूर्णांकel_idle_init);

/*
 * We are not really modular, but we used to support that.  Meaning we also
 * support "intel_idle.max_cstate=..." at boot and also a पढ़ो-only export of
 * it at /sys/module/पूर्णांकel_idle/parameters/max_cstate -- so using module_param
 * is the easiest way (currently) to जारी करोing that.
 */
module_param(max_cstate, पूर्णांक, 0444);
/*
 * The positions of the bits that are set in this number are the indices of the
 * idle states to be disabled by शेष (as reflected by the names of the
 * corresponding idle state directories in sysfs, "state0", "state1" ...
 * "state<i>" ..., where <i> is the index of the given state).
 */
module_param_named(states_off, disabled_states_mask, uपूर्णांक, 0444);
MODULE_PARM_DESC(states_off, "Mask of disabled idle states");
