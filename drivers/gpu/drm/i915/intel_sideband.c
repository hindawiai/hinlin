<शैली गुरु>
/*
 * Copyright तऊ 2013 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <यंत्र/iosf_mbi.h>

#समावेश "i915_drv.h"
#समावेश "intel_sideband.h"

/*
 * IOSF sideband, see VLV2_SidebandMsg_HAS.करोcx and
 * VLV_VLV2_PUNIT_HAS_0.8.करोcx
 */

/* Standard MMIO पढ़ो, non-posted */
#घोषणा SB_MRD_NP	0x00
/* Standard MMIO ग_लिखो, non-posted */
#घोषणा SB_MWR_NP	0x01
/* Private रेजिस्टर पढ़ो, द्विगुन-word addressing, non-posted */
#घोषणा SB_CRRDDA_NP	0x06
/* Private रेजिस्टर ग_लिखो, द्विगुन-word addressing, non-posted */
#घोषणा SB_CRWRDA_NP	0x07

अटल व्योम ping(व्योम *info)
अणु
पूर्ण

अटल व्योम __vlv_punit_get(काष्ठा drm_i915_निजी *i915)
अणु
	iosf_mbi_punit_acquire();

	/*
	 * Prevent the cpu from sleeping जबतक we use this sideband, otherwise
	 * the punit may cause a machine hang. The issue appears to be isolated
	 * with changing the घातer state of the CPU package जबतक changing
	 * the घातer state via the punit, and we have only observed it
	 * reliably on 4-core Baytail प्रणालीs suggesting the issue is in the
	 * घातer delivery mechanism and likely to be be board/function
	 * specअगरic. Hence we presume the workaround needs only be applied
	 * to the Valleyview P-unit and not all sideband communications.
	 */
	अगर (IS_VALLEYVIEW(i915)) अणु
		cpu_latency_qos_update_request(&i915->sb_qos, 0);
		on_each_cpu(ping, शून्य, 1);
	पूर्ण
पूर्ण

अटल व्योम __vlv_punit_put(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (IS_VALLEYVIEW(i915))
		cpu_latency_qos_update_request(&i915->sb_qos,
					       PM_QOS_DEFAULT_VALUE);

	iosf_mbi_punit_release();
पूर्ण

व्योम vlv_iosf_sb_get(काष्ठा drm_i915_निजी *i915, अचिन्हित दीर्घ ports)
अणु
	अगर (ports & BIT(VLV_IOSF_SB_PUNIT))
		__vlv_punit_get(i915);

	mutex_lock(&i915->sb_lock);
पूर्ण

व्योम vlv_iosf_sb_put(काष्ठा drm_i915_निजी *i915, अचिन्हित दीर्घ ports)
अणु
	mutex_unlock(&i915->sb_lock);

	अगर (ports & BIT(VLV_IOSF_SB_PUNIT))
		__vlv_punit_put(i915);
पूर्ण

अटल पूर्णांक vlv_sideband_rw(काष्ठा drm_i915_निजी *i915,
			   u32 devfn, u32 port, u32 opcode,
			   u32 addr, u32 *val)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	स्थिर bool is_पढ़ो = (opcode == SB_MRD_NP || opcode == SB_CRRDDA_NP);
	पूर्णांक err;

	lockdep_निश्चित_held(&i915->sb_lock);
	अगर (port == IOSF_PORT_PUNIT)
		iosf_mbi_निश्चित_punit_acquired();

	/* Flush the previous comms, just in हाल it failed last समय. */
	अगर (पूर्णांकel_रुको_क्रम_रेजिस्टर(uncore,
				    VLV_IOSF_DOORBELL_REQ, IOSF_SB_BUSY, 0,
				    5)) अणु
		drm_dbg(&i915->drm, "IOSF sideband idle wait (%s) timed out\n",
			is_पढ़ो ? "read" : "write");
		वापस -EAGAIN;
	पूर्ण

	preempt_disable();

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, VLV_IOSF_ADDR, addr);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, VLV_IOSF_DATA, is_पढ़ो ? 0 : *val);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, VLV_IOSF_DOORBELL_REQ,
			      (devfn << IOSF_DEVFN_SHIFT) |
			      (opcode << IOSF_OPCODE_SHIFT) |
			      (port << IOSF_PORT_SHIFT) |
			      (0xf << IOSF_BYTE_ENABLES_SHIFT) |
			      (0 << IOSF_BAR_SHIFT) |
			      IOSF_SB_BUSY);

	अगर (__पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
					 VLV_IOSF_DOORBELL_REQ, IOSF_SB_BUSY, 0,
					 10000, 0, शून्य) == 0) अणु
		अगर (is_पढ़ो)
			*val = पूर्णांकel_uncore_पढ़ो_fw(uncore, VLV_IOSF_DATA);
		err = 0;
	पूर्ण अन्यथा अणु
		drm_dbg(&i915->drm, "IOSF sideband finish wait (%s) timed out\n",
			is_पढ़ो ? "read" : "write");
		err = -ETIMEDOUT;
	पूर्ण

	preempt_enable();

	वापस err;
पूर्ण

u32 vlv_punit_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 addr)
अणु
	u32 val = 0;

	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_PUNIT,
			SB_CRRDDA_NP, addr, &val);

	वापस val;
पूर्ण

पूर्णांक vlv_punit_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 addr, u32 val)
अणु
	वापस vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_PUNIT,
			       SB_CRWRDA_NP, addr, &val);
पूर्ण

u32 vlv_bunit_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 reg)
अणु
	u32 val = 0;

	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_BUNIT,
			SB_CRRDDA_NP, reg, &val);

	वापस val;
पूर्ण

व्योम vlv_bunit_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 reg, u32 val)
अणु
	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_BUNIT,
			SB_CRWRDA_NP, reg, &val);
पूर्ण

u32 vlv_nc_पढ़ो(काष्ठा drm_i915_निजी *i915, u8 addr)
अणु
	u32 val = 0;

	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_NC,
			SB_CRRDDA_NP, addr, &val);

	वापस val;
पूर्ण

u32 vlv_iosf_sb_पढ़ो(काष्ठा drm_i915_निजी *i915, u8 port, u32 reg)
अणु
	u32 val = 0;

	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), port,
			SB_CRRDDA_NP, reg, &val);

	वापस val;
पूर्ण

व्योम vlv_iosf_sb_ग_लिखो(काष्ठा drm_i915_निजी *i915,
		       u8 port, u32 reg, u32 val)
अणु
	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), port,
			SB_CRWRDA_NP, reg, &val);
पूर्ण

u32 vlv_cck_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 reg)
अणु
	u32 val = 0;

	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_CCK,
			SB_CRRDDA_NP, reg, &val);

	वापस val;
पूर्ण

व्योम vlv_cck_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 reg, u32 val)
अणु
	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_CCK,
			SB_CRWRDA_NP, reg, &val);
पूर्ण

u32 vlv_ccu_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 reg)
अणु
	u32 val = 0;

	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_CCU,
			SB_CRRDDA_NP, reg, &val);

	वापस val;
पूर्ण

व्योम vlv_ccu_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 reg, u32 val)
अणु
	vlv_sideband_rw(i915, PCI_DEVFN(0, 0), IOSF_PORT_CCU,
			SB_CRWRDA_NP, reg, &val);
पूर्ण

अटल u32 vlv_dpio_phy_iosf_port(काष्ठा drm_i915_निजी *i915, क्रमागत dpio_phy phy)
अणु
	/*
	 * IOSF_PORT_DPIO: VLV x2 PHY (DP/HDMI B and C), CHV x1 PHY (DP/HDMI D)
	 * IOSF_PORT_DPIO_2: CHV x2 PHY (DP/HDMI B and C)
	 */
	अगर (IS_CHERRYVIEW(i915))
		वापस phy == DPIO_PHY0 ? IOSF_PORT_DPIO_2 : IOSF_PORT_DPIO;
	अन्यथा
		वापस IOSF_PORT_DPIO;
पूर्ण

u32 vlv_dpio_पढ़ो(काष्ठा drm_i915_निजी *i915, क्रमागत pipe pipe, पूर्णांक reg)
अणु
	u32 port = vlv_dpio_phy_iosf_port(i915, DPIO_PHY(pipe));
	u32 val = 0;

	vlv_sideband_rw(i915, DPIO_DEVFN, port, SB_MRD_NP, reg, &val);

	/*
	 * FIXME: There might be some रेजिस्टरs where all 1's is a valid value,
	 * so ideally we should check the रेजिस्टर offset instead...
	 */
	drm_WARN(&i915->drm, val == 0xffffffff,
		 "DPIO read pipe %c reg 0x%x == 0x%x\n",
		 pipe_name(pipe), reg, val);

	वापस val;
पूर्ण

व्योम vlv_dpio_ग_लिखो(काष्ठा drm_i915_निजी *i915,
		    क्रमागत pipe pipe, पूर्णांक reg, u32 val)
अणु
	u32 port = vlv_dpio_phy_iosf_port(i915, DPIO_PHY(pipe));

	vlv_sideband_rw(i915, DPIO_DEVFN, port, SB_MWR_NP, reg, &val);
पूर्ण

u32 vlv_flisdsi_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 reg)
अणु
	u32 val = 0;

	vlv_sideband_rw(i915, DPIO_DEVFN, IOSF_PORT_FLISDSI, SB_CRRDDA_NP,
			reg, &val);
	वापस val;
पूर्ण

व्योम vlv_flisdsi_ग_लिखो(काष्ठा drm_i915_निजी *i915, u32 reg, u32 val)
अणु
	vlv_sideband_rw(i915, DPIO_DEVFN, IOSF_PORT_FLISDSI, SB_CRWRDA_NP,
			reg, &val);
पूर्ण

/* SBI access */
अटल पूर्णांक पूर्णांकel_sbi_rw(काष्ठा drm_i915_निजी *i915, u16 reg,
			क्रमागत पूर्णांकel_sbi_destination destination,
			u32 *val, bool is_पढ़ो)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 cmd;

	lockdep_निश्चित_held(&i915->sb_lock);

	अगर (पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
				       SBI_CTL_STAT, SBI_BUSY, 0,
				       100)) अणु
		drm_err(&i915->drm,
			"timeout waiting for SBI to become ready\n");
		वापस -EBUSY;
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, SBI_ADDR, (u32)reg << 16);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, SBI_DATA, is_पढ़ो ? 0 : *val);

	अगर (destination == SBI_ICLK)
		cmd = SBI_CTL_DEST_ICLK | SBI_CTL_OP_CRRD;
	अन्यथा
		cmd = SBI_CTL_DEST_MPHY | SBI_CTL_OP_IORD;
	अगर (!is_पढ़ो)
		cmd |= BIT(8);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, SBI_CTL_STAT, cmd | SBI_BUSY);

	अगर (__पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
					 SBI_CTL_STAT, SBI_BUSY, 0,
					 100, 100, &cmd)) अणु
		drm_err(&i915->drm,
			"timeout waiting for SBI to complete read\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (cmd & SBI_RESPONSE_FAIL) अणु
		drm_err(&i915->drm, "error during SBI read of reg %x\n", reg);
		वापस -ENXIO;
	पूर्ण

	अगर (is_पढ़ो)
		*val = पूर्णांकel_uncore_पढ़ो_fw(uncore, SBI_DATA);

	वापस 0;
पूर्ण

u32 पूर्णांकel_sbi_पढ़ो(काष्ठा drm_i915_निजी *i915, u16 reg,
		   क्रमागत पूर्णांकel_sbi_destination destination)
अणु
	u32 result = 0;

	पूर्णांकel_sbi_rw(i915, reg, destination, &result, true);

	वापस result;
पूर्ण

व्योम पूर्णांकel_sbi_ग_लिखो(काष्ठा drm_i915_निजी *i915, u16 reg, u32 value,
		     क्रमागत पूर्णांकel_sbi_destination destination)
अणु
	पूर्णांकel_sbi_rw(i915, reg, destination, &value, false);
पूर्ण

अटल पूर्णांक gen6_check_mailbox_status(u32 mbox)
अणु
	चयन (mbox & GEN6_PCODE_ERROR_MASK) अणु
	हाल GEN6_PCODE_SUCCESS:
		वापस 0;
	हाल GEN6_PCODE_UNIMPLEMENTED_CMD:
		वापस -ENODEV;
	हाल GEN6_PCODE_ILLEGAL_CMD:
		वापस -ENXIO;
	हाल GEN6_PCODE_MIN_FREQ_TABLE_GT_RATIO_OUT_OF_RANGE:
	हाल GEN7_PCODE_MIN_FREQ_TABLE_GT_RATIO_OUT_OF_RANGE:
		वापस -EOVERFLOW;
	हाल GEN6_PCODE_TIMEOUT:
		वापस -ETIMEDOUT;
	शेष:
		MISSING_CASE(mbox & GEN6_PCODE_ERROR_MASK);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक gen7_check_mailbox_status(u32 mbox)
अणु
	चयन (mbox & GEN6_PCODE_ERROR_MASK) अणु
	हाल GEN6_PCODE_SUCCESS:
		वापस 0;
	हाल GEN6_PCODE_ILLEGAL_CMD:
		वापस -ENXIO;
	हाल GEN7_PCODE_TIMEOUT:
		वापस -ETIMEDOUT;
	हाल GEN7_PCODE_ILLEGAL_DATA:
		वापस -EINVAL;
	हाल GEN11_PCODE_ILLEGAL_SUBCOMMAND:
		वापस -ENXIO;
	हाल GEN11_PCODE_LOCKED:
		वापस -EBUSY;
	हाल GEN11_PCODE_REJECTED:
		वापस -EACCES;
	हाल GEN7_PCODE_MIN_FREQ_TABLE_GT_RATIO_OUT_OF_RANGE:
		वापस -EOVERFLOW;
	शेष:
		MISSING_CASE(mbox & GEN6_PCODE_ERROR_MASK);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक __sandybridge_pcode_rw(काष्ठा drm_i915_निजी *i915,
				  u32 mbox, u32 *val, u32 *val1,
				  पूर्णांक fast_समयout_us,
				  पूर्णांक slow_समयout_ms,
				  bool is_पढ़ो)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;

	lockdep_निश्चित_held(&i915->sb_lock);

	/*
	 * GEN6_PCODE_* are outside of the क्रमcewake करोमुख्य, we can use
	 * पूर्णांकel_uncore_पढ़ो/ग_लिखो_fw variants to reduce the amount of work
	 * required when पढ़ोing/writing.
	 */

	अगर (पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_PCODE_MAILBOX) & GEN6_PCODE_READY)
		वापस -EAGAIN;

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_PCODE_DATA, *val);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_PCODE_DATA1, val1 ? *val1 : 0);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore,
			      GEN6_PCODE_MAILBOX, GEN6_PCODE_READY | mbox);

	अगर (__पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
					 GEN6_PCODE_MAILBOX,
					 GEN6_PCODE_READY, 0,
					 fast_समयout_us,
					 slow_समयout_ms,
					 &mbox))
		वापस -ETIMEDOUT;

	अगर (is_पढ़ो)
		*val = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_PCODE_DATA);
	अगर (is_पढ़ो && val1)
		*val1 = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_PCODE_DATA1);

	अगर (INTEL_GEN(i915) > 6)
		वापस gen7_check_mailbox_status(mbox);
	अन्यथा
		वापस gen6_check_mailbox_status(mbox);
पूर्ण

पूर्णांक sandybridge_pcode_पढ़ो(काष्ठा drm_i915_निजी *i915, u32 mbox,
			   u32 *val, u32 *val1)
अणु
	पूर्णांक err;

	mutex_lock(&i915->sb_lock);
	err = __sandybridge_pcode_rw(i915, mbox, val, val1,
				     500, 20,
				     true);
	mutex_unlock(&i915->sb_lock);

	अगर (err) अणु
		drm_dbg(&i915->drm,
			"warning: pcode (read from mbox %x) mailbox access failed for %ps: %d\n",
			mbox, __builtin_वापस_address(0), err);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक sandybridge_pcode_ग_लिखो_समयout(काष्ठा drm_i915_निजी *i915,
				    u32 mbox, u32 val,
				    पूर्णांक fast_समयout_us,
				    पूर्णांक slow_समयout_ms)
अणु
	पूर्णांक err;

	mutex_lock(&i915->sb_lock);
	err = __sandybridge_pcode_rw(i915, mbox, &val, शून्य,
				     fast_समयout_us, slow_समयout_ms,
				     false);
	mutex_unlock(&i915->sb_lock);

	अगर (err) अणु
		drm_dbg(&i915->drm,
			"warning: pcode (write of 0x%08x to mbox %x) mailbox access failed for %ps: %d\n",
			val, mbox, __builtin_वापस_address(0), err);
	पूर्ण

	वापस err;
पूर्ण

अटल bool skl_pcode_try_request(काष्ठा drm_i915_निजी *i915, u32 mbox,
				  u32 request, u32 reply_mask, u32 reply,
				  u32 *status)
अणु
	*status = __sandybridge_pcode_rw(i915, mbox, &request, शून्य,
					 500, 0,
					 true);

	वापस *status || ((request & reply_mask) == reply);
पूर्ण

/**
 * skl_pcode_request - send PCODE request until acknowledgment
 * @i915: device निजी
 * @mbox: PCODE mailbox ID the request is targeted क्रम
 * @request: request ID
 * @reply_mask: mask used to check क्रम request acknowledgment
 * @reply: value used to check क्रम request acknowledgment
 * @समयout_base_ms: समयout क्रम polling with preemption enabled
 *
 * Keep resending the @request to @mbox until PCODE acknowledges it, PCODE
 * reports an error or an overall समयout of @समयout_base_ms+50 ms expires.
 * The request is acknowledged once the PCODE reply dword equals @reply after
 * applying @reply_mask. Polling is first attempted with preemption enabled
 * क्रम @समयout_base_ms and अगर this बार out क्रम another 50 ms with
 * preemption disabled.
 *
 * Returns 0 on success, %-ETIMEDOUT in हाल of a समयout, <0 in हाल of some
 * other error as reported by PCODE.
 */
पूर्णांक skl_pcode_request(काष्ठा drm_i915_निजी *i915, u32 mbox, u32 request,
		      u32 reply_mask, u32 reply, पूर्णांक समयout_base_ms)
अणु
	u32 status;
	पूर्णांक ret;

	mutex_lock(&i915->sb_lock);

#घोषणा COND \
	skl_pcode_try_request(i915, mbox, request, reply_mask, reply, &status)

	/*
	 * Prime the PCODE by करोing a request first. Normally it guarantees
	 * that a subsequent request, at most @समयout_base_ms later, succeeds.
	 * _रुको_क्रम() करोesn't guarantee when its passed condition is evaluated
	 * first, so send the first request explicitly.
	 */
	अगर (COND) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	ret = _रुको_क्रम(COND, समयout_base_ms * 1000, 10, 10);
	अगर (!ret)
		जाओ out;

	/*
	 * The above can समय out अगर the number of requests was low (2 in the
	 * worst हाल) _and_ PCODE was busy क्रम some reason even after a
	 * (queued) request and @समयout_base_ms delay. As a workaround retry
	 * the poll with preemption disabled to maximize the number of
	 * requests. Increase the समयout from @समयout_base_ms to 50ms to
	 * account क्रम पूर्णांकerrupts that could reduce the number of these
	 * requests, and क्रम any quirks of the PCODE firmware that delays
	 * the request completion.
	 */
	drm_dbg_kms(&i915->drm,
		    "PCODE timeout, retrying with preemption disabled\n");
	drm_WARN_ON_ONCE(&i915->drm, समयout_base_ms > 3);
	preempt_disable();
	ret = रुको_क्रम_atomic(COND, 50);
	preempt_enable();

out:
	mutex_unlock(&i915->sb_lock);
	वापस ret ? ret : status;
#अघोषित COND
पूर्ण

व्योम पूर्णांकel_pcode_init(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret;

	अगर (!IS_DGFX(i915))
		वापस;

	ret = skl_pcode_request(i915, DG1_PCODE_STATUS,
				DG1_UNCORE_GET_INIT_STATUS,
				DG1_UNCORE_INIT_STATUS_COMPLETE,
				DG1_UNCORE_INIT_STATUS_COMPLETE, 50);
	अगर (ret)
		drm_err(&i915->drm, "Pcode did not report uncore initialization completion!\n");
पूर्ण
