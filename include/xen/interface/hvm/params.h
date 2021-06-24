<शैली गुरु>
/*
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
 */

#अगर_अघोषित __XEN_PUBLIC_HVM_PARAMS_H__
#घोषणा __XEN_PUBLIC_HVM_PARAMS_H__

#समावेश <xen/पूर्णांकerface/hvm/hvm_op.h>

/*
 * Parameter space क्रम HVMOP_अणुset,getपूर्ण_param.
 */

#घोषणा HVM_PARAM_CALLBACK_IRQ 0
/*
 * How should CPU0 event-channel notअगरications be delivered?
 *
 * If val == 0 then CPU0 event-channel notअगरications are not delivered.
 * If val != 0, val[63:56] encodes the type, as follows:
 */

#घोषणा HVM_PARAM_CALLBACK_TYPE_GSI      0
/*
 * val[55:0] is a delivery GSI.  GSI 0 cannot be used, as it aliases val == 0,
 * and disables all notअगरications.
 */

#घोषणा HVM_PARAM_CALLBACK_TYPE_PCI_INTX 1
/*
 * val[55:0] is a delivery PCI INTx line:
 * Doमुख्य = val[47:32], Bus = val[31:16] DevFn = val[15:8], IntX = val[1:0]
 */

#अगर defined(__i386__) || defined(__x86_64__)
#घोषणा HVM_PARAM_CALLBACK_TYPE_VECTOR   2
/*
 * val[7:0] is a vector number.  Check क्रम XENFEAT_hvm_callback_vector to know
 * अगर this delivery method is available.
 */
#या_अगर defined(__arm__) || defined(__aarch64__)
#घोषणा HVM_PARAM_CALLBACK_TYPE_PPI      2
/*
 * val[55:16] needs to be zero.
 * val[15:8] is पूर्णांकerrupt flag of the PPI used by event-channel:
 *  bit 8: the PPI is edge(1) or level(0) triggered
 *  bit 9: the PPI is active low(1) or high(0)
 * val[7:0] is a PPI number used by event-channel.
 * This is only used by ARM/ARM64 and masking/eoi the पूर्णांकerrupt associated to
 * the notअगरication is handled by the पूर्णांकerrupt controller.
 */
#पूर्ण_अगर

#घोषणा HVM_PARAM_STORE_PFN    1
#घोषणा HVM_PARAM_STORE_EVTCHN 2

#घोषणा HVM_PARAM_PAE_ENABLED  4

#घोषणा HVM_PARAM_IOREQ_PFN    5

#घोषणा HVM_PARAM_BUFIOREQ_PFN 6

/*
 * Set mode क्रम भव समयrs (currently x86 only):
 *  delay_क्रम_missed_ticks (शेष):
 *   Do not advance a vcpu's समय beyond the correct delivery समय क्रम
 *   पूर्णांकerrupts that have been missed due to preemption. Deliver missed
 *   पूर्णांकerrupts when the vcpu is rescheduled and advance the vcpu's भव
 *   समय stepwise क्रम each one.
 *  no_delay_क्रम_missed_ticks:
 *   As above, missed पूर्णांकerrupts are delivered, but guest समय always tracks
 *   wallघड़ी (i.e., real) समय जबतक करोing so.
 *  no_missed_ticks_pending:
 *   No missed पूर्णांकerrupts are held pending. Instead, to ensure ticks are
 *   delivered at some non-zero rate, अगर we detect missed ticks then the
 *   पूर्णांकernal tick alarm is not disabled अगर the VCPU is preempted during the
 *   next tick period.
 *  one_missed_tick_pending:
 *   Missed पूर्णांकerrupts are collapsed together and delivered as one 'late tick'.
 *   Guest समय always tracks wallघड़ी (i.e., real) समय.
 */
#घोषणा HVM_PARAM_TIMER_MODE   10
#घोषणा HVMPTM_delay_क्रम_missed_ticks    0
#घोषणा HVMPTM_no_delay_क्रम_missed_ticks 1
#घोषणा HVMPTM_no_missed_ticks_pending   2
#घोषणा HVMPTM_one_missed_tick_pending   3

/* Boolean: Enable भव HPET (high-precision event समयr)? (x86-only) */
#घोषणा HVM_PARAM_HPET_ENABLED 11

/* Identity-map page directory used by Intel EPT when CR0.PG=0. */
#घोषणा HVM_PARAM_IDENT_PT     12

/* Device Model करोमुख्य, शेषs to 0. */
#घोषणा HVM_PARAM_DM_DOMAIN    13

/* ACPI S state: currently support S0 and S3 on x86. */
#घोषणा HVM_PARAM_ACPI_S_STATE 14

/* TSS used on Intel when CR0.PE=0. */
#घोषणा HVM_PARAM_VM86_TSS     15

/* Boolean: Enable aligning all periodic vpts to reduce पूर्णांकerrupts */
#घोषणा HVM_PARAM_VPT_ALIGN    16

/* Console debug shared memory ring and event channel */
#घोषणा HVM_PARAM_CONSOLE_PFN    17
#घोषणा HVM_PARAM_CONSOLE_EVTCHN 18

#घोषणा HVM_NR_PARAMS          19

#पूर्ण_अगर /* __XEN_PUBLIC_HVM_PARAMS_H__ */
