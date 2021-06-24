<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PS3 Logical Perक्रमmance Monitor.
 *
 *  Copyright (C) 2007 Sony Computer Entertainment Inc.
 *  Copyright 2007 Sony Corp.
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ps3.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/cell-pmu.h>


/* BOOKMARK tag macros */
#घोषणा PS3_PM_BOOKMARK_START                    0x8000000000000000ULL
#घोषणा PS3_PM_BOOKMARK_STOP                     0x4000000000000000ULL
#घोषणा PS3_PM_BOOKMARK_TAG_KERNEL               0x1000000000000000ULL
#घोषणा PS3_PM_BOOKMARK_TAG_USER                 0x3000000000000000ULL
#घोषणा PS3_PM_BOOKMARK_TAG_MASK_HI              0xF000000000000000ULL
#घोषणा PS3_PM_BOOKMARK_TAG_MASK_LO              0x0F00000000000000ULL

/* CBE PM CONTROL रेजिस्टर macros */
#घोषणा PS3_PM_CONTROL_PPU_TH0_BOOKMARK          0x00001000
#घोषणा PS3_PM_CONTROL_PPU_TH1_BOOKMARK          0x00000800
#घोषणा PS3_PM_CONTROL_PPU_COUNT_MODE_MASK       0x000C0000
#घोषणा PS3_PM_CONTROL_PPU_COUNT_MODE_PROBLEM    0x00080000
#घोषणा PS3_WRITE_PM_MASK                        0xFFFFFFFFFFFFFFFFULL

/* CBE PM START STOP रेजिस्टर macros */
#घोषणा PS3_PM_START_STOP_PPU_TH0_BOOKMARK_START 0x02000000
#घोषणा PS3_PM_START_STOP_PPU_TH1_BOOKMARK_START 0x01000000
#घोषणा PS3_PM_START_STOP_PPU_TH0_BOOKMARK_STOP  0x00020000
#घोषणा PS3_PM_START_STOP_PPU_TH1_BOOKMARK_STOP  0x00010000
#घोषणा PS3_PM_START_STOP_START_MASK             0xFF000000
#घोषणा PS3_PM_START_STOP_STOP_MASK              0x00FF0000

/* CBE PM COUNTER रेजिस्टर macres */
#घोषणा PS3_PM_COUNTER_MASK_HI                   0xFFFFFFFF00000000ULL
#घोषणा PS3_PM_COUNTER_MASK_LO                   0x00000000FFFFFFFFULL

/* BASE SIGNAL GROUP NUMBER macros */
#घोषणा PM_ISLAND2_BASE_SIGNAL_GROUP_NUMBER  0
#घोषणा PM_ISLAND2_SIGNAL_GROUP_NUMBER1      6
#घोषणा PM_ISLAND2_SIGNAL_GROUP_NUMBER2      7
#घोषणा PM_ISLAND3_BASE_SIGNAL_GROUP_NUMBER  7
#घोषणा PM_ISLAND4_BASE_SIGNAL_GROUP_NUMBER  15
#घोषणा PM_SPU_TRIGGER_SIGNAL_GROUP_NUMBER   17
#घोषणा PM_SPU_EVENT_SIGNAL_GROUP_NUMBER     18
#घोषणा PM_ISLAND5_BASE_SIGNAL_GROUP_NUMBER  18
#घोषणा PM_ISLAND6_BASE_SIGNAL_GROUP_NUMBER  24
#घोषणा PM_ISLAND7_BASE_SIGNAL_GROUP_NUMBER  49
#घोषणा PM_ISLAND8_BASE_SIGNAL_GROUP_NUMBER  52
#घोषणा PM_SIG_GROUP_SPU                     41
#घोषणा PM_SIG_GROUP_SPU_TRIGGER             42
#घोषणा PM_SIG_GROUP_SPU_EVENT               43
#घोषणा PM_SIG_GROUP_MFC_MAX                 60

/**
 * काष्ठा ps3_lpm_shaकरोw_regs - Perक्रमmance monitor shaकरोw रेजिस्टरs.
 *
 * @pm_control: Shaकरोw of the processor's pm_control रेजिस्टर.
 * @pm_start_stop: Shaकरोw of the processor's pm_start_stop रेजिस्टर.
 * @group_control: Shaकरोw of the processor's group_control रेजिस्टर.
 * @debug_bus_control: Shaकरोw of the processor's debug_bus_control रेजिस्टर.
 *
 * The logical perक्रमmance monitor provides a ग_लिखो-only पूर्णांकerface to
 * these processor रेजिस्टरs.  These shaकरोw variables cache the processor
 * रेजिस्टर values क्रम पढ़ोing.
 *
 * The initial value of the shaकरोw रेजिस्टरs at lpm creation is
 * PS3_LPM_SHADOW_REG_INIT.
 */

काष्ठा ps3_lpm_shaकरोw_regs अणु
	u64 pm_control;
	u64 pm_start_stop;
	u64 group_control;
	u64 debug_bus_control;
पूर्ण;

#घोषणा PS3_LPM_SHADOW_REG_INIT 0xFFFFFFFF00000000ULL

/**
 * काष्ठा ps3_lpm_priv - Private lpm device data.
 *
 * @खोलो: An atomic variable indicating the lpm driver has been खोलोed.
 * @rights: The lpm rigths granted by the प्रणाली policy module.  A logical
 *  OR of क्रमागत ps3_lpm_rights.
 * @node_id: The node id of a BE processor whose perक्रमmance monitor this
 *  lpar has the right to use.
 * @pu_id: The lv1 id of the logical PU.
 * @lpm_id: The lv1 id of this lpm instance.
 * @outlet_id: The outlet created by lv1 क्रम this lpm instance.
 * @tb_count: The number of bytes of data held in the lv1 trace buffer.
 * @tb_cache: Kernel buffer to receive the data from the lv1 trace buffer.
 *  Must be 128 byte aligned.
 * @tb_cache_size: Size of the kernel @tb_cache buffer.  Must be 128 byte
 *  aligned.
 * @tb_cache_पूर्णांकernal: An unaligned buffer allocated by this driver to be
 *  used क्रम the trace buffer cache when ps3_lpm_खोलो() is called with a
 *  शून्य tb_cache argument.  Otherwise unused.
 * @shaकरोw: Processor रेजिस्टर shaकरोw of type काष्ठा ps3_lpm_shaकरोw_regs.
 * @sbd: The काष्ठा ps3_प्रणाली_bus_device attached to this driver.
 *
 * The trace buffer is a buffer allocated and used पूर्णांकernally to the lv1
 * hypervisor to collect trace data.  The trace buffer cache is a guest
 * buffer that accepts the trace data from the trace buffer.
 */

काष्ठा ps3_lpm_priv अणु
	atomic_t खोलो;
	u64 rights;
	u64 node_id;
	u64 pu_id;
	u64 lpm_id;
	u64 outlet_id;
	u64 tb_count;
	व्योम *tb_cache;
	u64 tb_cache_size;
	व्योम *tb_cache_पूर्णांकernal;
	काष्ठा ps3_lpm_shaकरोw_regs shaकरोw;
	काष्ठा ps3_प्रणाली_bus_device *sbd;
पूर्ण;

क्रमागत अणु
	PS3_LPM_DEFAULT_TB_CACHE_SIZE = 0x4000,
पूर्ण;

/**
 * lpm_priv - Static instance of the lpm data.
 *
 * Since the exported routines करोn't support the notion of a device
 * instance we need to hold the instance in this अटल variable
 * and then only allow at most one instance at a समय to be created.
 */

अटल काष्ठा ps3_lpm_priv *lpm_priv;

अटल काष्ठा device *sbd_core(व्योम)
अणु
	BUG_ON(!lpm_priv || !lpm_priv->sbd);
	वापस &lpm_priv->sbd->core;
पूर्ण

/**
 * use_start_stop_bookmark - Enable the PPU bookmark trace.
 *
 * And it enables PPU bookmark triggers ONLY अगर the other triggers are not set.
 * The start/stop bookmarks are inserted at ps3_enable_pm() and ps3_disable_pm()
 * to start/stop LPM.
 *
 * Used to get good quality of the perक्रमmance counter.
 */

क्रमागत अणुuse_start_stop_bookmark = 1,पूर्ण;

व्योम ps3_set_bookmark(u64 bookmark)
अणु
	/*
	 * As per the PPE book IV, to aव्योम bookmark loss there must
	 * not be a traced branch within 10 cycles of setting the
	 * SPRN_BKMK रेजिस्टर.  The actual text is unclear अगर 'within'
	 * includes cycles beक्रमe the call.
	 */

	यंत्र अस्थिर("nop;nop;nop;nop;nop;nop;nop;nop;nop;");
	mtspr(SPRN_BKMK, bookmark);
	यंत्र अस्थिर("nop;nop;nop;nop;nop;nop;nop;nop;nop;");
पूर्ण
EXPORT_SYMBOL_GPL(ps3_set_bookmark);

व्योम ps3_set_pm_bookmark(u64 tag, u64 incident, u64 th_id)
अणु
	u64 bookmark;

	bookmark = (get_tb() & 0x00000000FFFFFFFFULL) |
		PS3_PM_BOOKMARK_TAG_KERNEL;
	bookmark = ((tag << 56) & PS3_PM_BOOKMARK_TAG_MASK_LO) |
		(incident << 48) | (th_id << 32) | bookmark;
	ps3_set_bookmark(bookmark);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_set_pm_bookmark);

/**
 * ps3_पढ़ो_phys_ctr - Read physical counter रेजिस्टरs.
 *
 * Each physical counter can act as one 32 bit counter or as two 16 bit
 * counters.
 */

u32 ps3_पढ़ो_phys_ctr(u32 cpu, u32 phys_ctr)
अणु
	पूर्णांक result;
	u64 counter0415;
	u64 counter2637;

	अगर (phys_ctr >= NR_PHYS_CTRS) अणु
		dev_dbg(sbd_core(), "%s:%u: phys_ctr too big: %u\n", __func__,
			__LINE__, phys_ctr);
		वापस 0;
	पूर्ण

	result = lv1_set_lpm_counter(lpm_priv->lpm_id, 0, 0, 0, 0, &counter0415,
				     &counter2637);
	अगर (result) अणु
		dev_err(sbd_core(), "%s:%u: lv1_set_lpm_counter failed: "
			"phys_ctr %u, %s\n", __func__, __LINE__, phys_ctr,
			ps3_result(result));
		वापस 0;
	पूर्ण

	चयन (phys_ctr) अणु
	हाल 0:
		वापस counter0415 >> 32;
	हाल 1:
		वापस counter0415 & PS3_PM_COUNTER_MASK_LO;
	हाल 2:
		वापस counter2637 >> 32;
	हाल 3:
		वापस counter2637 & PS3_PM_COUNTER_MASK_LO;
	शेष:
		BUG();
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_पढ़ो_phys_ctr);

/**
 * ps3_ग_लिखो_phys_ctr - Write physical counter रेजिस्टरs.
 *
 * Each physical counter can act as one 32 bit counter or as two 16 bit
 * counters.
 */

व्योम ps3_ग_लिखो_phys_ctr(u32 cpu, u32 phys_ctr, u32 val)
अणु
	u64 counter0415;
	u64 counter0415_mask;
	u64 counter2637;
	u64 counter2637_mask;
	पूर्णांक result;

	अगर (phys_ctr >= NR_PHYS_CTRS) अणु
		dev_dbg(sbd_core(), "%s:%u: phys_ctr too big: %u\n", __func__,
			__LINE__, phys_ctr);
		वापस;
	पूर्ण

	चयन (phys_ctr) अणु
	हाल 0:
		counter0415 = (u64)val << 32;
		counter0415_mask = PS3_PM_COUNTER_MASK_HI;
		counter2637 = 0x0;
		counter2637_mask = 0x0;
		अवरोध;
	हाल 1:
		counter0415 = (u64)val;
		counter0415_mask = PS3_PM_COUNTER_MASK_LO;
		counter2637 = 0x0;
		counter2637_mask = 0x0;
		अवरोध;
	हाल 2:
		counter0415 = 0x0;
		counter0415_mask = 0x0;
		counter2637 = (u64)val << 32;
		counter2637_mask = PS3_PM_COUNTER_MASK_HI;
		अवरोध;
	हाल 3:
		counter0415 = 0x0;
		counter0415_mask = 0x0;
		counter2637 = (u64)val;
		counter2637_mask = PS3_PM_COUNTER_MASK_LO;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	result = lv1_set_lpm_counter(lpm_priv->lpm_id,
				     counter0415, counter0415_mask,
				     counter2637, counter2637_mask,
				     &counter0415, &counter2637);
	अगर (result)
		dev_err(sbd_core(), "%s:%u: lv1_set_lpm_counter failed: "
			"phys_ctr %u, val %u, %s\n", __func__, __LINE__,
			phys_ctr, val, ps3_result(result));
पूर्ण
EXPORT_SYMBOL_GPL(ps3_ग_लिखो_phys_ctr);

/**
 * ps3_पढ़ो_ctr - Read counter.
 *
 * Read 16 or 32 bits depending on the current size of the counter.
 * Counters 4, 5, 6 & 7 are always 16 bit.
 */

u32 ps3_पढ़ो_ctr(u32 cpu, u32 ctr)
अणु
	u32 val;
	u32 phys_ctr = ctr & (NR_PHYS_CTRS - 1);

	val = ps3_पढ़ो_phys_ctr(cpu, phys_ctr);

	अगर (ps3_get_ctr_size(cpu, phys_ctr) == 16)
		val = (ctr < NR_PHYS_CTRS) ? (val >> 16) : (val & 0xffff);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_पढ़ो_ctr);

/**
 * ps3_ग_लिखो_ctr - Write counter.
 *
 * Write 16 or 32 bits depending on the current size of the counter.
 * Counters 4, 5, 6 & 7 are always 16 bit.
 */

व्योम ps3_ग_लिखो_ctr(u32 cpu, u32 ctr, u32 val)
अणु
	u32 phys_ctr;
	u32 phys_val;

	phys_ctr = ctr & (NR_PHYS_CTRS - 1);

	अगर (ps3_get_ctr_size(cpu, phys_ctr) == 16) अणु
		phys_val = ps3_पढ़ो_phys_ctr(cpu, phys_ctr);

		अगर (ctr < NR_PHYS_CTRS)
			val = (val << 16) | (phys_val & 0xffff);
		अन्यथा
			val = (val & 0xffff) | (phys_val & 0xffff0000);
	पूर्ण

	ps3_ग_लिखो_phys_ctr(cpu, phys_ctr, val);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_ग_लिखो_ctr);

/**
 * ps3_पढ़ो_pm07_control - Read counter control रेजिस्टरs.
 *
 * Each logical counter has a corresponding control रेजिस्टर.
 */

u32 ps3_पढ़ो_pm07_control(u32 cpu, u32 ctr)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_पढ़ो_pm07_control);

/**
 * ps3_ग_लिखो_pm07_control - Write counter control रेजिस्टरs.
 *
 * Each logical counter has a corresponding control रेजिस्टर.
 */

व्योम ps3_ग_लिखो_pm07_control(u32 cpu, u32 ctr, u32 val)
अणु
	पूर्णांक result;
	अटल स्थिर u64 mask = 0xFFFFFFFFFFFFFFFFULL;
	u64 old_value;

	अगर (ctr >= NR_CTRS) अणु
		dev_dbg(sbd_core(), "%s:%u: ctr too big: %u\n", __func__,
			__LINE__, ctr);
		वापस;
	पूर्ण

	result = lv1_set_lpm_counter_control(lpm_priv->lpm_id, ctr, val, mask,
					     &old_value);
	अगर (result)
		dev_err(sbd_core(), "%s:%u: lv1_set_lpm_counter_control "
			"failed: ctr %u, %s\n", __func__, __LINE__, ctr,
			ps3_result(result));
पूर्ण
EXPORT_SYMBOL_GPL(ps3_ग_लिखो_pm07_control);

/**
 * ps3_पढ़ो_pm - Read Other LPM control रेजिस्टरs.
 */

u32 ps3_पढ़ो_pm(u32 cpu, क्रमागत pm_reg_name reg)
अणु
	पूर्णांक result = 0;
	u64 val = 0;

	चयन (reg) अणु
	हाल pm_control:
		वापस lpm_priv->shaकरोw.pm_control;
	हाल trace_address:
		वापस CBE_PM_TRACE_BUF_EMPTY;
	हाल pm_start_stop:
		वापस lpm_priv->shaकरोw.pm_start_stop;
	हाल pm_पूर्णांकerval:
		result = lv1_set_lpm_पूर्णांकerval(lpm_priv->lpm_id, 0, 0, &val);
		अगर (result) अणु
			val = 0;
			dev_dbg(sbd_core(), "%s:%u: lv1 set_interval failed: "
				"reg %u, %s\n", __func__, __LINE__, reg,
				ps3_result(result));
		पूर्ण
		वापस (u32)val;
	हाल group_control:
		वापस lpm_priv->shaकरोw.group_control;
	हाल debug_bus_control:
		वापस lpm_priv->shaकरोw.debug_bus_control;
	हाल pm_status:
		result = lv1_get_lpm_पूर्णांकerrupt_status(lpm_priv->lpm_id,
						      &val);
		अगर (result) अणु
			val = 0;
			dev_dbg(sbd_core(), "%s:%u: lv1 get_lpm_status failed: "
				"reg %u, %s\n", __func__, __LINE__, reg,
				ps3_result(result));
		पूर्ण
		वापस (u32)val;
	हाल ext_tr_समयr:
		वापस 0;
	शेष:
		dev_dbg(sbd_core(), "%s:%u: unknown reg: %d\n", __func__,
			__LINE__, reg);
		BUG();
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_पढ़ो_pm);

/**
 * ps3_ग_लिखो_pm - Write Other LPM control रेजिस्टरs.
 */

व्योम ps3_ग_लिखो_pm(u32 cpu, क्रमागत pm_reg_name reg, u32 val)
अणु
	पूर्णांक result = 0;
	u64 dummy;

	चयन (reg) अणु
	हाल group_control:
		अगर (val != lpm_priv->shaकरोw.group_control)
			result = lv1_set_lpm_group_control(lpm_priv->lpm_id,
							   val,
							   PS3_WRITE_PM_MASK,
							   &dummy);
		lpm_priv->shaकरोw.group_control = val;
		अवरोध;
	हाल debug_bus_control:
		अगर (val != lpm_priv->shaकरोw.debug_bus_control)
			result = lv1_set_lpm_debug_bus_control(lpm_priv->lpm_id,
							      val,
							      PS3_WRITE_PM_MASK,
							      &dummy);
		lpm_priv->shaकरोw.debug_bus_control = val;
		अवरोध;
	हाल pm_control:
		अगर (use_start_stop_bookmark)
			val |= (PS3_PM_CONTROL_PPU_TH0_BOOKMARK |
				PS3_PM_CONTROL_PPU_TH1_BOOKMARK);
		अगर (val != lpm_priv->shaकरोw.pm_control)
			result = lv1_set_lpm_general_control(lpm_priv->lpm_id,
							     val,
							     PS3_WRITE_PM_MASK,
							     0, 0, &dummy,
							     &dummy);
		lpm_priv->shaकरोw.pm_control = val;
		अवरोध;
	हाल pm_पूर्णांकerval:
		result = lv1_set_lpm_पूर्णांकerval(lpm_priv->lpm_id, val,
					      PS3_WRITE_PM_MASK, &dummy);
		अवरोध;
	हाल pm_start_stop:
		अगर (val != lpm_priv->shaकरोw.pm_start_stop)
			result = lv1_set_lpm_trigger_control(lpm_priv->lpm_id,
							     val,
							     PS3_WRITE_PM_MASK,
							     &dummy);
		lpm_priv->shaकरोw.pm_start_stop = val;
		अवरोध;
	हाल trace_address:
	हाल ext_tr_समयr:
	हाल pm_status:
		अवरोध;
	शेष:
		dev_dbg(sbd_core(), "%s:%u: unknown reg: %d\n", __func__,
			__LINE__, reg);
		BUG();
		अवरोध;
	पूर्ण

	अगर (result)
		dev_err(sbd_core(), "%s:%u: lv1 set_control failed: "
			"reg %u, %s\n", __func__, __LINE__, reg,
			ps3_result(result));
पूर्ण
EXPORT_SYMBOL_GPL(ps3_ग_लिखो_pm);

/**
 * ps3_get_ctr_size - Get the size of a physical counter.
 *
 * Returns either 16 or 32.
 */

u32 ps3_get_ctr_size(u32 cpu, u32 phys_ctr)
अणु
	u32 pm_ctrl;

	अगर (phys_ctr >= NR_PHYS_CTRS) अणु
		dev_dbg(sbd_core(), "%s:%u: phys_ctr too big: %u\n", __func__,
			__LINE__, phys_ctr);
		वापस 0;
	पूर्ण

	pm_ctrl = ps3_पढ़ो_pm(cpu, pm_control);
	वापस (pm_ctrl & CBE_PM_16BIT_CTR(phys_ctr)) ? 16 : 32;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_get_ctr_size);

/**
 * ps3_set_ctr_size - Set the size of a physical counter to 16 or 32 bits.
 */

व्योम ps3_set_ctr_size(u32 cpu, u32 phys_ctr, u32 ctr_size)
अणु
	u32 pm_ctrl;

	अगर (phys_ctr >= NR_PHYS_CTRS) अणु
		dev_dbg(sbd_core(), "%s:%u: phys_ctr too big: %u\n", __func__,
			__LINE__, phys_ctr);
		वापस;
	पूर्ण

	pm_ctrl = ps3_पढ़ो_pm(cpu, pm_control);

	चयन (ctr_size) अणु
	हाल 16:
		pm_ctrl |= CBE_PM_16BIT_CTR(phys_ctr);
		ps3_ग_लिखो_pm(cpu, pm_control, pm_ctrl);
		अवरोध;

	हाल 32:
		pm_ctrl &= ~CBE_PM_16BIT_CTR(phys_ctr);
		ps3_ग_लिखो_pm(cpu, pm_control, pm_ctrl);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ps3_set_ctr_size);

अटल u64 pm_translate_संकेत_group_number_on_island2(u64 subgroup)
अणु

	अगर (subgroup == 2)
		subgroup = 3;

	अगर (subgroup <= 6)
		वापस PM_ISLAND2_BASE_SIGNAL_GROUP_NUMBER + subgroup;
	अन्यथा अगर (subgroup == 7)
		वापस PM_ISLAND2_SIGNAL_GROUP_NUMBER1;
	अन्यथा
		वापस PM_ISLAND2_SIGNAL_GROUP_NUMBER2;
पूर्ण

अटल u64 pm_translate_संकेत_group_number_on_island3(u64 subgroup)
अणु

	चयन (subgroup) अणु
	हाल 2:
	हाल 3:
	हाल 4:
		subgroup += 2;
		अवरोध;
	हाल 5:
		subgroup = 8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस PM_ISLAND3_BASE_SIGNAL_GROUP_NUMBER + subgroup;
पूर्ण

अटल u64 pm_translate_संकेत_group_number_on_island4(u64 subgroup)
अणु
	वापस PM_ISLAND4_BASE_SIGNAL_GROUP_NUMBER + subgroup;
पूर्ण

अटल u64 pm_translate_संकेत_group_number_on_island5(u64 subgroup)
अणु

	चयन (subgroup) अणु
	हाल 3:
		subgroup = 4;
		अवरोध;
	हाल 4:
		subgroup = 6;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस PM_ISLAND5_BASE_SIGNAL_GROUP_NUMBER + subgroup;
पूर्ण

अटल u64 pm_translate_संकेत_group_number_on_island6(u64 subgroup,
						       u64 subsubgroup)
अणु
	चयन (subgroup) अणु
	हाल 3:
	हाल 4:
	हाल 5:
		subgroup += 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (subsubgroup) अणु
	हाल 4:
	हाल 5:
	हाल 6:
		subsubgroup += 2;
		अवरोध;
	हाल 7:
	हाल 8:
	हाल 9:
	हाल 10:
		subsubgroup += 4;
		अवरोध;
	हाल 11:
	हाल 12:
	हाल 13:
		subsubgroup += 5;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (subgroup <= 5)
		वापस (PM_ISLAND6_BASE_SIGNAL_GROUP_NUMBER + subgroup);
	अन्यथा
		वापस (PM_ISLAND6_BASE_SIGNAL_GROUP_NUMBER + subgroup
			+ subsubgroup - 1);
पूर्ण

अटल u64 pm_translate_संकेत_group_number_on_island7(u64 subgroup)
अणु
	वापस PM_ISLAND7_BASE_SIGNAL_GROUP_NUMBER + subgroup;
पूर्ण

अटल u64 pm_translate_संकेत_group_number_on_island8(u64 subgroup)
अणु
	वापस PM_ISLAND8_BASE_SIGNAL_GROUP_NUMBER + subgroup;
पूर्ण

अटल u64 pm_संकेत_group_to_ps3_lv1_संकेत_group(u64 group)
अणु
	u64 island;
	u64 subgroup;
	u64 subsubgroup;

	subgroup = 0;
	subsubgroup = 0;
	island = 0;
	अगर (group < 1000) अणु
		अगर (group < 100) अणु
			अगर (20 <= group && group < 30) अणु
				island = 2;
				subgroup = group - 20;
			पूर्ण अन्यथा अगर (30 <= group && group < 40) अणु
				island = 3;
				subgroup = group - 30;
			पूर्ण अन्यथा अगर (40 <= group && group < 50) अणु
				island = 4;
				subgroup = group - 40;
			पूर्ण अन्यथा अगर (50 <= group && group < 60) अणु
				island = 5;
				subgroup = group - 50;
			पूर्ण अन्यथा अगर (60 <= group && group < 70) अणु
				island = 6;
				subgroup = group - 60;
			पूर्ण अन्यथा अगर (70 <= group && group < 80) अणु
				island = 7;
				subgroup = group - 70;
			पूर्ण अन्यथा अगर (80 <= group && group < 90) अणु
				island = 8;
				subgroup = group - 80;
			पूर्ण
		पूर्ण अन्यथा अगर (200 <= group && group < 300) अणु
			island = 2;
			subgroup = group - 200;
		पूर्ण अन्यथा अगर (600 <= group && group < 700) अणु
			island = 6;
			subgroup = 5;
			subsubgroup = group - 650;
		पूर्ण
	पूर्ण अन्यथा अगर (6000 <= group && group < 7000) अणु
		island = 6;
		subgroup = 5;
		subsubgroup = group - 6500;
	पूर्ण

	चयन (island) अणु
	हाल 2:
		वापस pm_translate_संकेत_group_number_on_island2(subgroup);
	हाल 3:
		वापस pm_translate_संकेत_group_number_on_island3(subgroup);
	हाल 4:
		वापस pm_translate_संकेत_group_number_on_island4(subgroup);
	हाल 5:
		वापस pm_translate_संकेत_group_number_on_island5(subgroup);
	हाल 6:
		वापस pm_translate_संकेत_group_number_on_island6(subgroup,
								   subsubgroup);
	हाल 7:
		वापस pm_translate_संकेत_group_number_on_island7(subgroup);
	हाल 8:
		वापस pm_translate_संकेत_group_number_on_island8(subgroup);
	शेष:
		dev_dbg(sbd_core(), "%s:%u: island not found: %llu\n", __func__,
			__LINE__, group);
		BUG();
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल u64 pm_bus_word_to_ps3_lv1_bus_word(u8 word)
अणु

	चयन (word) अणु
	हाल 1:
		वापस 0xF000;
	हाल 2:
		वापस 0x0F00;
	हाल 4:
		वापस 0x00F0;
	हाल 8:
	शेष:
		वापस 0x000F;
	पूर्ण
पूर्ण

अटल पूर्णांक __ps3_set_संकेत(u64 lv1_संकेत_group, u64 bus_select,
			    u64 संकेत_select, u64 attr1, u64 attr2, u64 attr3)
अणु
	पूर्णांक ret;

	ret = lv1_set_lpm_संकेत(lpm_priv->lpm_id, lv1_संकेत_group, bus_select,
				 संकेत_select, attr1, attr2, attr3);
	अगर (ret)
		dev_err(sbd_core(),
			"%s:%u: error:%d 0x%llx 0x%llx 0x%llx 0x%llx 0x%llx 0x%llx\n",
			__func__, __LINE__, ret, lv1_संकेत_group, bus_select,
			संकेत_select, attr1, attr2, attr3);

	वापस ret;
पूर्ण

पूर्णांक ps3_set_संकेत(u64 संकेत_group, u8 संकेत_bit, u16 sub_unit,
		   u8 bus_word)
अणु
	पूर्णांक ret;
	u64 lv1_संकेत_group;
	u64 bus_select;
	u64 संकेत_select;
	u64 attr1, attr2, attr3;

	अगर (संकेत_group == 0)
		वापस __ps3_set_संकेत(0, 0, 0, 0, 0, 0);

	lv1_संकेत_group =
		pm_संकेत_group_to_ps3_lv1_संकेत_group(संकेत_group);
	bus_select = pm_bus_word_to_ps3_lv1_bus_word(bus_word);

	चयन (संकेत_group) अणु
	हाल PM_SIG_GROUP_SPU_TRIGGER:
		संकेत_select = 1;
		संकेत_select = संकेत_select << (63 - संकेत_bit);
		अवरोध;
	हाल PM_SIG_GROUP_SPU_EVENT:
		संकेत_select = 1;
		संकेत_select = (संकेत_select << (63 - संकेत_bit)) | 0x3;
		अवरोध;
	शेष:
		संकेत_select = 0;
		अवरोध;
	पूर्ण

	/*
	 * 0: physical object.
	 * 1: logical object.
	 * This parameter is only used क्रम the PPE and SPE संकेतs.
	 */
	attr1 = 1;

	/*
	 * This parameter is used to specअगरy the target physical/logical
	 * PPE/SPE object.
	 */
	अगर (PM_SIG_GROUP_SPU <= संकेत_group &&
		संकेत_group < PM_SIG_GROUP_MFC_MAX)
		attr2 = sub_unit;
	अन्यथा
		attr2 = lpm_priv->pu_id;

	/*
	 * This parameter is only used क्रम setting the SPE संकेत.
	 */
	attr3 = 0;

	ret = __ps3_set_संकेत(lv1_संकेत_group, bus_select, संकेत_select,
			       attr1, attr2, attr3);
	अगर (ret)
		dev_err(sbd_core(), "%s:%u: __ps3_set_signal failed: %d\n",
			__func__, __LINE__, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_set_संकेत);

u32 ps3_get_hw_thपढ़ो_id(पूर्णांक cpu)
अणु
	वापस get_hard_smp_processor_id(cpu);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_get_hw_thपढ़ो_id);

/**
 * ps3_enable_pm - Enable the entire perक्रमmance monitoring unit.
 *
 * When we enable the LPM, all pending ग_लिखोs to counters get committed.
 */

व्योम ps3_enable_pm(u32 cpu)
अणु
	पूर्णांक result;
	u64 पंचांगp;
	पूर्णांक insert_bookmark = 0;

	lpm_priv->tb_count = 0;

	अगर (use_start_stop_bookmark) अणु
		अगर (!(lpm_priv->shaकरोw.pm_start_stop &
			(PS3_PM_START_STOP_START_MASK
			| PS3_PM_START_STOP_STOP_MASK))) अणु
			result = lv1_set_lpm_trigger_control(lpm_priv->lpm_id,
				(PS3_PM_START_STOP_PPU_TH0_BOOKMARK_START |
				PS3_PM_START_STOP_PPU_TH1_BOOKMARK_START |
				PS3_PM_START_STOP_PPU_TH0_BOOKMARK_STOP |
				PS3_PM_START_STOP_PPU_TH1_BOOKMARK_STOP),
				0xFFFFFFFFFFFFFFFFULL, &पंचांगp);

			अगर (result)
				dev_err(sbd_core(), "%s:%u: "
					"lv1_set_lpm_trigger_control failed: "
					"%s\n", __func__, __LINE__,
					ps3_result(result));

			insert_bookmark = !result;
		पूर्ण
	पूर्ण

	result = lv1_start_lpm(lpm_priv->lpm_id);

	अगर (result)
		dev_err(sbd_core(), "%s:%u: lv1_start_lpm failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	अगर (use_start_stop_bookmark && !result && insert_bookmark)
		ps3_set_bookmark(get_tb() | PS3_PM_BOOKMARK_START);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_enable_pm);

/**
 * ps3_disable_pm - Disable the entire perक्रमmance monitoring unit.
 */

व्योम ps3_disable_pm(u32 cpu)
अणु
	पूर्णांक result;
	u64 पंचांगp;

	ps3_set_bookmark(get_tb() | PS3_PM_BOOKMARK_STOP);

	result = lv1_stop_lpm(lpm_priv->lpm_id, &पंचांगp);

	अगर (result) अणु
		अगर (result != LV1_WRONG_STATE)
			dev_err(sbd_core(), "%s:%u: lv1_stop_lpm failed: %s\n",
				__func__, __LINE__, ps3_result(result));
		वापस;
	पूर्ण

	lpm_priv->tb_count = पंचांगp;

	dev_dbg(sbd_core(), "%s:%u: tb_count %llu (%llxh)\n", __func__, __LINE__,
		lpm_priv->tb_count, lpm_priv->tb_count);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_disable_pm);

/**
 * ps3_lpm_copy_tb - Copy data from the trace buffer to a kernel buffer.
 * @offset: Offset in bytes from the start of the trace buffer.
 * @buf: Copy destination.
 * @count: Maximum count of bytes to copy.
 * @bytes_copied: Poपूर्णांकer to a variable that will receive the number of
 *  bytes copied to @buf.
 *
 * On error @buf will contain any successfully copied trace buffer data
 * and bytes_copied will be set to the number of bytes successfully copied.
 */

पूर्णांक ps3_lpm_copy_tb(अचिन्हित दीर्घ offset, व्योम *buf, अचिन्हित दीर्घ count,
		    अचिन्हित दीर्घ *bytes_copied)
अणु
	पूर्णांक result;

	*bytes_copied = 0;

	अगर (!lpm_priv->tb_cache)
		वापस -EPERM;

	अगर (offset >= lpm_priv->tb_count)
		वापस 0;

	count = min_t(u64, count, lpm_priv->tb_count - offset);

	जबतक (*bytes_copied < count) अणु
		स्थिर अचिन्हित दीर्घ request = count - *bytes_copied;
		u64 पंचांगp;

		result = lv1_copy_lpm_trace_buffer(lpm_priv->lpm_id, offset,
						   request, &पंचांगp);
		अगर (result) अणु
			dev_dbg(sbd_core(), "%s:%u: 0x%lx bytes at 0x%lx\n",
				__func__, __LINE__, request, offset);

			dev_err(sbd_core(), "%s:%u: lv1_copy_lpm_trace_buffer "
				"failed: %s\n", __func__, __LINE__,
				ps3_result(result));
			वापस result == LV1_WRONG_STATE ? -EBUSY : -EINVAL;
		पूर्ण

		स_नकल(buf, lpm_priv->tb_cache, पंचांगp);
		buf += पंचांगp;
		*bytes_copied += पंचांगp;
		offset += पंचांगp;
	पूर्ण
	dev_dbg(sbd_core(), "%s:%u: copied %lxh bytes\n", __func__, __LINE__,
		*bytes_copied);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_lpm_copy_tb);

/**
 * ps3_lpm_copy_tb_to_user - Copy data from the trace buffer to a user buffer.
 * @offset: Offset in bytes from the start of the trace buffer.
 * @buf: A __user copy destination.
 * @count: Maximum count of bytes to copy.
 * @bytes_copied: Poपूर्णांकer to a variable that will receive the number of
 *  bytes copied to @buf.
 *
 * On error @buf will contain any successfully copied trace buffer data
 * and bytes_copied will be set to the number of bytes successfully copied.
 */

पूर्णांक ps3_lpm_copy_tb_to_user(अचिन्हित दीर्घ offset, व्योम __user *buf,
			    अचिन्हित दीर्घ count, अचिन्हित दीर्घ *bytes_copied)
अणु
	पूर्णांक result;

	*bytes_copied = 0;

	अगर (!lpm_priv->tb_cache)
		वापस -EPERM;

	अगर (offset >= lpm_priv->tb_count)
		वापस 0;

	count = min_t(u64, count, lpm_priv->tb_count - offset);

	जबतक (*bytes_copied < count) अणु
		स्थिर अचिन्हित दीर्घ request = count - *bytes_copied;
		u64 पंचांगp;

		result = lv1_copy_lpm_trace_buffer(lpm_priv->lpm_id, offset,
						   request, &पंचांगp);
		अगर (result) अणु
			dev_dbg(sbd_core(), "%s:%u: 0x%lx bytes at 0x%lx\n",
				__func__, __LINE__, request, offset);
			dev_err(sbd_core(), "%s:%u: lv1_copy_lpm_trace_buffer "
				"failed: %s\n", __func__, __LINE__,
				ps3_result(result));
			वापस result == LV1_WRONG_STATE ? -EBUSY : -EINVAL;
		पूर्ण

		result = copy_to_user(buf, lpm_priv->tb_cache, पंचांगp);

		अगर (result) अणु
			dev_dbg(sbd_core(), "%s:%u: 0x%llx bytes at 0x%p\n",
				__func__, __LINE__, पंचांगp, buf);
			dev_err(sbd_core(), "%s:%u: copy_to_user failed: %d\n",
				__func__, __LINE__, result);
			वापस -EFAULT;
		पूर्ण

		buf += पंचांगp;
		*bytes_copied += पंचांगp;
		offset += पंचांगp;
	पूर्ण
	dev_dbg(sbd_core(), "%s:%u: copied %lxh bytes\n", __func__, __LINE__,
		*bytes_copied);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_lpm_copy_tb_to_user);

/**
 * ps3_get_and_clear_pm_पूर्णांकerrupts -
 *
 * Clearing पूर्णांकerrupts क्रम the entire perक्रमmance monitoring unit.
 * Reading pm_status clears the पूर्णांकerrupt bits.
 */

u32 ps3_get_and_clear_pm_पूर्णांकerrupts(u32 cpu)
अणु
	वापस ps3_पढ़ो_pm(cpu, pm_status);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_get_and_clear_pm_पूर्णांकerrupts);

/**
 * ps3_enable_pm_पूर्णांकerrupts -
 *
 * Enabling पूर्णांकerrupts क्रम the entire perक्रमmance monitoring unit.
 * Enables the पूर्णांकerrupt bits in the pm_status रेजिस्टर.
 */

व्योम ps3_enable_pm_पूर्णांकerrupts(u32 cpu, u32 thपढ़ो, u32 mask)
अणु
	अगर (mask)
		ps3_ग_लिखो_pm(cpu, pm_status, mask);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_enable_pm_पूर्णांकerrupts);

/**
 * ps3_enable_pm_पूर्णांकerrupts -
 *
 * Disabling पूर्णांकerrupts क्रम the entire perक्रमmance monitoring unit.
 */

व्योम ps3_disable_pm_पूर्णांकerrupts(u32 cpu)
अणु
	ps3_get_and_clear_pm_पूर्णांकerrupts(cpu);
	ps3_ग_लिखो_pm(cpu, pm_status, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_disable_pm_पूर्णांकerrupts);

/**
 * ps3_lpm_खोलो - Open the logical perक्रमmance monitor device.
 * @tb_type: Specअगरies the type of trace buffer lv1 should use क्रम this lpm
 *  instance, specअगरied by one of क्रमागत ps3_lpm_tb_type.
 * @tb_cache: Optional user supplied buffer to use as the trace buffer cache.
 *  If शून्य, the driver will allocate and manage an पूर्णांकernal buffer.
 *  Unused when when @tb_type is PS3_LPM_TB_TYPE_NONE.
 * @tb_cache_size: The size in bytes of the user supplied @tb_cache buffer.
 *  Unused when @tb_cache is शून्य or @tb_type is PS3_LPM_TB_TYPE_NONE.
 */

पूर्णांक ps3_lpm_खोलो(क्रमागत ps3_lpm_tb_type tb_type, व्योम *tb_cache,
	u64 tb_cache_size)
अणु
	पूर्णांक result;
	u64 tb_size;

	BUG_ON(!lpm_priv);
	BUG_ON(tb_type != PS3_LPM_TB_TYPE_NONE
		&& tb_type != PS3_LPM_TB_TYPE_INTERNAL);

	अगर (tb_type == PS3_LPM_TB_TYPE_NONE && tb_cache)
		dev_dbg(sbd_core(), "%s:%u: bad in vals\n", __func__, __LINE__);

	अगर (!atomic_add_unless(&lpm_priv->खोलो, 1, 1)) अणु
		dev_dbg(sbd_core(), "%s:%u: busy\n", __func__, __LINE__);
		वापस -EBUSY;
	पूर्ण

	/* Note tb_cache needs 128 byte alignment. */

	अगर (tb_type == PS3_LPM_TB_TYPE_NONE) अणु
		lpm_priv->tb_cache_size = 0;
		lpm_priv->tb_cache_पूर्णांकernal = शून्य;
		lpm_priv->tb_cache = शून्य;
	पूर्ण अन्यथा अगर (tb_cache) अणु
		अगर (tb_cache != (व्योम *)ALIGN((अचिन्हित दीर्घ)tb_cache, 128)
			|| tb_cache_size != ALIGN(tb_cache_size, 128)) अणु
			dev_err(sbd_core(), "%s:%u: unaligned tb_cache\n",
				__func__, __LINE__);
			result = -EINVAL;
			जाओ fail_align;
		पूर्ण
		lpm_priv->tb_cache_size = tb_cache_size;
		lpm_priv->tb_cache_पूर्णांकernal = शून्य;
		lpm_priv->tb_cache = tb_cache;
	पूर्ण अन्यथा अणु
		lpm_priv->tb_cache_size = PS3_LPM_DEFAULT_TB_CACHE_SIZE;
		lpm_priv->tb_cache_पूर्णांकernal = kzalloc(
			lpm_priv->tb_cache_size + 127, GFP_KERNEL);
		अगर (!lpm_priv->tb_cache_पूर्णांकernal) अणु
			result = -ENOMEM;
			जाओ fail_दो_स्मृति;
		पूर्ण
		lpm_priv->tb_cache = (व्योम *)ALIGN(
			(अचिन्हित दीर्घ)lpm_priv->tb_cache_पूर्णांकernal, 128);
	पूर्ण

	result = lv1_स्थिरruct_lpm(lpm_priv->node_id, tb_type, 0, 0,
				ps3_mm_phys_to_lpar(__pa(lpm_priv->tb_cache)),
				lpm_priv->tb_cache_size, &lpm_priv->lpm_id,
				&lpm_priv->outlet_id, &tb_size);

	अगर (result) अणु
		dev_err(sbd_core(), "%s:%u: lv1_construct_lpm failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		result = -EINVAL;
		जाओ fail_स्थिरruct;
	पूर्ण

	lpm_priv->shaकरोw.pm_control = PS3_LPM_SHADOW_REG_INIT;
	lpm_priv->shaकरोw.pm_start_stop = PS3_LPM_SHADOW_REG_INIT;
	lpm_priv->shaकरोw.group_control = PS3_LPM_SHADOW_REG_INIT;
	lpm_priv->shaकरोw.debug_bus_control = PS3_LPM_SHADOW_REG_INIT;

	dev_dbg(sbd_core(), "%s:%u: lpm_id 0x%llx, outlet_id 0x%llx, "
		"tb_size 0x%llx\n", __func__, __LINE__, lpm_priv->lpm_id,
		lpm_priv->outlet_id, tb_size);

	वापस 0;

fail_स्थिरruct:
	kमुक्त(lpm_priv->tb_cache_पूर्णांकernal);
	lpm_priv->tb_cache_पूर्णांकernal = शून्य;
fail_दो_स्मृति:
fail_align:
	atomic_dec(&lpm_priv->खोलो);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_lpm_खोलो);

/**
 * ps3_lpm_बंद - Close the lpm device.
 *
 */

पूर्णांक ps3_lpm_बंद(व्योम)
अणु
	dev_dbg(sbd_core(), "%s:%u\n", __func__, __LINE__);

	lv1_deकाष्ठा_lpm(lpm_priv->lpm_id);
	lpm_priv->lpm_id = 0;

	kमुक्त(lpm_priv->tb_cache_पूर्णांकernal);
	lpm_priv->tb_cache_पूर्णांकernal = शून्य;

	atomic_dec(&lpm_priv->खोलो);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_lpm_बंद);

अटल पूर्णांक ps3_lpm_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	dev_dbg(&dev->core, " -> %s:%u\n", __func__, __LINE__);

	अगर (lpm_priv) अणु
		dev_info(&dev->core, "%s:%u: called twice\n",
			__func__, __LINE__);
		वापस -EBUSY;
	पूर्ण

	lpm_priv = kzalloc(माप(*lpm_priv), GFP_KERNEL);

	अगर (!lpm_priv)
		वापस -ENOMEM;

	lpm_priv->sbd = dev;
	lpm_priv->node_id = dev->lpm.node_id;
	lpm_priv->pu_id = dev->lpm.pu_id;
	lpm_priv->rights = dev->lpm.rights;

	dev_info(&dev->core, " <- %s:%u:\n", __func__, __LINE__);

	वापस 0;
पूर्ण

अटल व्योम ps3_lpm_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	dev_dbg(&dev->core, " -> %s:%u:\n", __func__, __LINE__);

	ps3_lpm_बंद();

	kमुक्त(lpm_priv);
	lpm_priv = शून्य;

	dev_info(&dev->core, " <- %s:%u:\n", __func__, __LINE__);
पूर्ण

अटल काष्ठा ps3_प्रणाली_bus_driver ps3_lpm_driver = अणु
	.match_id = PS3_MATCH_ID_LPM,
	.core.name	= "ps3-lpm",
	.core.owner	= THIS_MODULE,
	.probe		= ps3_lpm_probe,
	.हटाओ		= ps3_lpm_हटाओ,
	.shutकरोwn	= ps3_lpm_हटाओ,
पूर्ण;

अटल पूर्णांक __init ps3_lpm_init(व्योम)
अणु
	pr_debug("%s:%d:\n", __func__, __LINE__);
	वापस ps3_प्रणाली_bus_driver_रेजिस्टर(&ps3_lpm_driver);
पूर्ण

अटल व्योम __निकास ps3_lpm_निकास(व्योम)
अणु
	pr_debug("%s:%d:\n", __func__, __LINE__);
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&ps3_lpm_driver);
पूर्ण

module_init(ps3_lpm_init);
module_निकास(ps3_lpm_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PS3 Logical Performance Monitor Driver");
MODULE_AUTHOR("Sony Corporation");
MODULE_ALIAS(PS3_MODULE_ALIAS_LPM);
