<शैली गुरु>
/******************************************************************************
 * sched.h
 *
 * Scheduler state पूर्णांकeractions
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2005, Keir Fraser <keir@xensource.com>
 */

#अगर_अघोषित __XEN_PUBLIC_SCHED_H__
#घोषणा __XEN_PUBLIC_SCHED_H__

#समावेश <xen/पूर्णांकerface/event_channel.h>

/*
 * Guest Scheduler Operations
 *
 * The SCHEDOP पूर्णांकerface provides mechanisms क्रम a guest to पूर्णांकeract
 * with the scheduler, including yield, blocking and shutting itself
 * करोwn.
 */

/*
 * The prototype क्रम this hypercall is:
 * दीर्घ HYPERVISOR_sched_op(क्रमागत sched_op cmd, व्योम *arg, ...)
 *
 * @cmd == SCHEDOP_??? (scheduler operation).
 * @arg == Operation-specअगरic extra argument(s), as described below.
 * ...  == Additional Operation-specअगरic extra arguments, described below.
 *
 * Versions of Xen prior to 3.0.2 provided only the following legacy version
 * of this hypercall, supporting only the commands yield, block and shutकरोwn:
 *  दीर्घ sched_op(पूर्णांक cmd, अचिन्हित दीर्घ arg)
 * @cmd == SCHEDOP_??? (scheduler operation).
 * @arg == 0               (SCHEDOP_yield and SCHEDOP_block)
 *      == SHUTDOWN_* code (SCHEDOP_shutकरोwn)
 *
 * This legacy version is available to new guests as:
 * दीर्घ HYPERVISOR_sched_op_compat(क्रमागत sched_op cmd, अचिन्हित दीर्घ arg)
 */

/*
 * Voluntarily yield the CPU.
 * @arg == शून्य.
 */
#घोषणा SCHEDOP_yield       0

/*
 * Block execution of this VCPU until an event is received क्रम processing.
 * If called with event upcalls masked, this operation will atomically
 * reenable event delivery and check क्रम pending events beक्रमe blocking the
 * VCPU. This aव्योमs a "wakeup waiting" race.
 * @arg == शून्य.
 */
#घोषणा SCHEDOP_block       1

/*
 * Halt execution of this करोमुख्य (all VCPUs) and notअगरy the प्रणाली controller.
 * @arg == poपूर्णांकer to sched_shutकरोwn काष्ठाure.
 *
 * If the sched_shutकरोwn_t reason is SHUTDOWN_suspend then
 * x86 PV guests must also set RDX (EDX क्रम 32-bit guests) to the MFN
 * of the guest's start info page.  RDX/EDX is the third hypercall
 * argument.
 *
 * In addition, which reason is SHUTDOWN_suspend this hypercall
 * वापसs 1 अगर suspend was cancelled or the करोमुख्य was merely
 * checkpoपूर्णांकed, and 0 अगर it is resuming in a new करोमुख्य.
 */
#घोषणा SCHEDOP_shutकरोwn    2

/*
 * Poll a set of event-channel ports. Return when one or more are pending. An
 * optional समयout may be specअगरied.
 * @arg == poपूर्णांकer to sched_poll काष्ठाure.
 */
#घोषणा SCHEDOP_poll        3

/*
 * Declare a shutकरोwn क्रम another करोमुख्य. The मुख्य use of this function is
 * in पूर्णांकerpreting shutकरोwn requests and reasons क्रम fully-भवized
 * करोमुख्यs.  A para-भवized करोमुख्य may use SCHEDOP_shutकरोwn directly.
 * @arg == poपूर्णांकer to sched_remote_shutकरोwn काष्ठाure.
 */
#घोषणा SCHEDOP_remote_shutकरोwn        4

/*
 * Latch a shutकरोwn code, so that when the करोमुख्य later shuts करोwn it
 * reports this code to the control tools.
 * @arg == sched_shutकरोwn, as क्रम SCHEDOP_shutकरोwn.
 */
#घोषणा SCHEDOP_shutकरोwn_code 5

/*
 * Setup, poke and destroy a करोमुख्य watchकरोg समयr.
 * @arg == poपूर्णांकer to sched_watchकरोg काष्ठाure.
 * With id == 0, setup a करोमुख्य watchकरोg समयr to cause करोमुख्य shutकरोwn
 *               after समयout, वापसs watchकरोg id.
 * With id != 0 and समयout == 0, destroy करोमुख्य watchकरोg समयr.
 * With id != 0 and समयout != 0, poke watchकरोg समयr and set new समयout.
 */
#घोषणा SCHEDOP_watchकरोg    6

/*
 * Override the current vcpu affinity by pinning it to one physical cpu or
 * unकरो this override restoring the previous affinity.
 * @arg == poपूर्णांकer to sched_pin_override काष्ठाure.
 *
 * A negative pcpu value will unकरो a previous pin override and restore the
 * previous cpu affinity.
 * This call is allowed क्रम the hardware करोमुख्य only and requires the cpu
 * to be part of the करोमुख्य's cpupool.
 */
#घोषणा SCHEDOP_pin_override 7

काष्ठा sched_shutकरोwn अणु
    अचिन्हित पूर्णांक reason; /* SHUTDOWN_* => shutकरोwn reason */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(sched_shutकरोwn);

काष्ठा sched_poll अणु
    GUEST_HANDLE(evtchn_port_t) ports;
    अचिन्हित पूर्णांक nr_ports;
    uपूर्णांक64_t समयout;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(sched_poll);

काष्ठा sched_remote_shutकरोwn अणु
    करोmid_t करोमुख्य_id;         /* Remote करोमुख्य ID */
    अचिन्हित पूर्णांक reason;       /* SHUTDOWN_* => shutकरोwn reason */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(sched_remote_shutकरोwn);

काष्ठा sched_watchकरोg अणु
    uपूर्णांक32_t id;                /* watchकरोg ID */
    uपूर्णांक32_t समयout;           /* समयout */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(sched_watchकरोg);

काष्ठा sched_pin_override अणु
    पूर्णांक32_t pcpu;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(sched_pin_override);

/*
 * Reason codes क्रम SCHEDOP_shutकरोwn. These may be पूर्णांकerpreted by control
 * software to determine the appropriate action. For the most part, Xen करोes
 * not care about the shutकरोwn code.
 */
#घोषणा SHUTDOWN_घातeroff   0  /* Doमुख्य निकासed normally. Clean up and समाप्त. */
#घोषणा SHUTDOWN_reboot     1  /* Clean up, समाप्त, and then restart.          */
#घोषणा SHUTDOWN_suspend    2  /* Clean up, save suspend info, समाप्त.         */
#घोषणा SHUTDOWN_crash      3  /* Tell controller we've crashed.             */
#घोषणा SHUTDOWN_watchकरोg   4  /* Restart because watchकरोg समय expired.     */

/*
 * Doमुख्य asked to perक्रमm 'soft reset' क्रम it. The expected behavior is to
 * reset पूर्णांकernal Xen state क्रम the करोमुख्य वापसing it to the poपूर्णांक where it
 * was created but leaving the करोमुख्य's memory contents and vCPU contexts
 * पूर्णांकact. This will allow the करोमुख्य to start over and set up all Xen specअगरic
 * पूर्णांकerfaces again.
 */
#घोषणा SHUTDOWN_soft_reset 5
#घोषणा SHUTDOWN_MAX        5  /* Maximum valid shutकरोwn reason.             */

#पूर्ण_अगर /* __XEN_PUBLIC_SCHED_H__ */
