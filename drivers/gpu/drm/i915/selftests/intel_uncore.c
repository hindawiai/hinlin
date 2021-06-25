<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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

#समावेश "../i915_selftest.h"

अटल पूर्णांक पूर्णांकel_fw_table_check(स्थिर काष्ठा पूर्णांकel_क्रमcewake_range *ranges,
				अचिन्हित पूर्णांक num_ranges,
				bool is_watertight)
अणु
	अचिन्हित पूर्णांक i;
	s32 prev;

	क्रम (i = 0, prev = -1; i < num_ranges; i++, ranges++) अणु
		/* Check that the table is watertight */
		अगर (is_watertight && (prev + 1) != (s32)ranges->start) अणु
			pr_err("%s: entry[%d]:(%x, %x) is not watertight to previous (%x)\n",
			       __func__, i, ranges->start, ranges->end, prev);
			वापस -EINVAL;
		पूर्ण

		/* Check that the table never goes backwards */
		अगर (prev >= (s32)ranges->start) अणु
			pr_err("%s: entry[%d]:(%x, %x) is less than the previous (%x)\n",
			       __func__, i, ranges->start, ranges->end, prev);
			वापस -EINVAL;
		पूर्ण

		/* Check that the entry is valid */
		अगर (ranges->start >= ranges->end) अणु
			pr_err("%s: entry[%d]:(%x, %x) has negative length\n",
			       __func__, i, ranges->start, ranges->end);
			वापस -EINVAL;
		पूर्ण

		prev = ranges->end;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_shaकरोw_table_check(व्योम)
अणु
	काष्ठा अणु
		स्थिर i915_reg_t *regs;
		अचिन्हित पूर्णांक size;
	पूर्ण reg_lists[] = अणु
		अणु gen8_shaकरोwed_regs, ARRAY_SIZE(gen8_shaकरोwed_regs) पूर्ण,
		अणु gen11_shaकरोwed_regs, ARRAY_SIZE(gen11_shaकरोwed_regs) पूर्ण,
		अणु gen12_shaकरोwed_regs, ARRAY_SIZE(gen12_shaकरोwed_regs) पूर्ण,
	पूर्ण;
	स्थिर i915_reg_t *reg;
	अचिन्हित पूर्णांक i, j;
	s32 prev;

	क्रम (j = 0; j < ARRAY_SIZE(reg_lists); ++j) अणु
		reg = reg_lists[j].regs;
		क्रम (i = 0, prev = -1; i < reg_lists[j].size; i++, reg++) अणु
			u32 offset = i915_mmio_reg_offset(*reg);

			अगर (prev >= (s32)offset) अणु
				pr_err("%s: entry[%d]:(%x) is before previous (%x)\n",
				       __func__, i, offset, prev);
				वापस -EINVAL;
			पूर्ण

			prev = offset;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_uncore_mock_selftests(व्योम)
अणु
	काष्ठा अणु
		स्थिर काष्ठा पूर्णांकel_क्रमcewake_range *ranges;
		अचिन्हित पूर्णांक num_ranges;
		bool is_watertight;
	पूर्ण fw[] = अणु
		अणु __vlv_fw_ranges, ARRAY_SIZE(__vlv_fw_ranges), false पूर्ण,
		अणु __chv_fw_ranges, ARRAY_SIZE(__chv_fw_ranges), false पूर्ण,
		अणु __gen9_fw_ranges, ARRAY_SIZE(__gen9_fw_ranges), true पूर्ण,
		अणु __gen11_fw_ranges, ARRAY_SIZE(__gen11_fw_ranges), true पूर्ण,
		अणु __gen12_fw_ranges, ARRAY_SIZE(__gen12_fw_ranges), true पूर्ण,
	पूर्ण;
	पूर्णांक err, i;

	क्रम (i = 0; i < ARRAY_SIZE(fw); i++) अणु
		err = पूर्णांकel_fw_table_check(fw[i].ranges,
					   fw[i].num_ranges,
					   fw[i].is_watertight);
		अगर (err)
			वापस err;
	पूर्ण

	err = पूर्णांकel_shaकरोw_table_check();
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक live_क्रमcewake_ops(व्योम *arg)
अणु
	अटल स्थिर काष्ठा reg अणु
		स्थिर अक्षर *name;
		अचिन्हित दीर्घ platक्रमms;
		अचिन्हित पूर्णांक offset;
	पूर्ण रेजिस्टरs[] = अणु
		अणु
			"RING_START",
			INTEL_GEN_MASK(6, 7),
			0x38,
		पूर्ण,
		अणु
			"RING_MI_MODE",
			INTEL_GEN_MASK(8, BITS_PER_LONG),
			0x9c,
		पूर्ण
	पूर्ण;
	स्थिर काष्ठा reg *r;
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_uncore_क्रमcewake_करोमुख्य *करोमुख्य;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांकel_wakeref_t wakeref;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err = 0;

	GEM_BUG_ON(gt->awake);

	/* vlv/chv with their pcu behave dअगरferently wrt पढ़ोs */
	अगर (IS_VALLEYVIEW(gt->i915) || IS_CHERRYVIEW(gt->i915)) अणु
		pr_debug("PCU fakes forcewake badly; skipping\n");
		वापस 0;
	पूर्ण

	/*
	 * Not quite as reliable across the gen as one would hope.
	 *
	 * Either our theory of operation is incorrect, or there reमुख्य
	 * बाह्यal parties पूर्णांकerfering with the घातerwells.
	 *
	 * https://bugs.मुक्तdesktop.org/show_bug.cgi?id=110210
	 */
	अगर (!IS_ENABLED(CONFIG_DRM_I915_SELFTEST_BROKEN))
		वापस 0;

	/* We have to pick carefully to get the exact behaviour we need */
	क्रम (r = रेजिस्टरs; r->name; r++)
		अगर (r->platक्रमms & INTEL_INFO(gt->i915)->gen_mask)
			अवरोध;
	अगर (!r->name) अणु
		pr_debug("Forcewaked register not known for %s; skipping\n",
			 पूर्णांकel_platक्रमm_name(INTEL_INFO(gt->i915)->platक्रमm));
		वापस 0;
	पूर्ण

	wakeref = पूर्णांकel_runसमय_pm_get(uncore->rpm);

	क्रम_each_fw_करोमुख्य(करोमुख्य, uncore, पंचांगp) अणु
		smp_store_mb(करोमुख्य->active, false);
		अगर (!hrसमयr_cancel(&करोमुख्य->समयr))
			जारी;

		पूर्णांकel_uncore_fw_release_समयr(&करोमुख्य->समयr);
	पूर्ण

	क्रम_each_engine(engine, gt, id) अणु
		i915_reg_t mmio = _MMIO(engine->mmio_base + r->offset);
		u32 __iomem *reg = uncore->regs + engine->mmio_base + r->offset;
		क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs;
		u32 val;

		अगर (!engine->शेष_state)
			जारी;

		fw_करोमुख्यs = पूर्णांकel_uncore_क्रमcewake_क्रम_reg(uncore, mmio,
							    FW_REG_READ);
		अगर (!fw_करोमुख्यs)
			जारी;

		क्रम_each_fw_करोमुख्य_masked(करोमुख्य, fw_करोमुख्यs, uncore, पंचांगp) अणु
			अगर (!करोमुख्य->wake_count)
				जारी;

			pr_err("fw_domain %s still active, aborting test!\n",
			       पूर्णांकel_uncore_क्रमcewake_करोमुख्य_to_str(करोमुख्य->id));
			err = -EINVAL;
			जाओ out_rpm;
		पूर्ण

		पूर्णांकel_uncore_क्रमcewake_get(uncore, fw_करोमुख्यs);
		val = पढ़ोl(reg);
		पूर्णांकel_uncore_क्रमcewake_put(uncore, fw_करोमुख्यs);

		/* Flush the क्रमcewake release (delayed onto a समयr) */
		क्रम_each_fw_करोमुख्य_masked(करोमुख्य, fw_करोमुख्यs, uncore, पंचांगp) अणु
			smp_store_mb(करोमुख्य->active, false);
			अगर (hrसमयr_cancel(&करोमुख्य->समयr))
				पूर्णांकel_uncore_fw_release_समयr(&करोमुख्य->समयr);

			preempt_disable();
			err = रुको_ack_clear(करोमुख्य, FORCEWAKE_KERNEL);
			preempt_enable();
			अगर (err) अणु
				pr_err("Failed to clear fw_domain %s\n",
				       पूर्णांकel_uncore_क्रमcewake_करोमुख्य_to_str(करोमुख्य->id));
				जाओ out_rpm;
			पूर्ण
		पूर्ण

		अगर (!val) अणु
			pr_err("%s:%s was zero while fw was held!\n",
			       engine->name, r->name);
			err = -EINVAL;
			जाओ out_rpm;
		पूर्ण

		/* We then expect the पढ़ो to वापस 0 outside of the fw */
		अगर (रुको_क्रम(पढ़ोl(reg) == 0, 100)) अणु
			pr_err("%s:%s=%0x, fw_domains 0x%x still up after 100ms!\n",
			       engine->name, r->name, पढ़ोl(reg), fw_करोमुख्यs);
			err = -ETIMEDOUT;
			जाओ out_rpm;
		पूर्ण
	पूर्ण

out_rpm:
	पूर्णांकel_runसमय_pm_put(uncore->rpm, wakeref);
	वापस err;
पूर्ण

अटल पूर्णांक live_क्रमcewake_करोमुख्यs(व्योम *arg)
अणु
#घोषणा FW_RANGE 0x40000
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	अचिन्हित दीर्घ *valid;
	u32 offset;
	पूर्णांक err;

	अगर (!HAS_FPGA_DBG_UNCLAIMED(gt->i915) &&
	    !IS_VALLEYVIEW(gt->i915) &&
	    !IS_CHERRYVIEW(gt->i915))
		वापस 0;

	/*
	 * This test may lockup the machine or cause GPU hangs afterwards.
	 */
	अगर (!IS_ENABLED(CONFIG_DRM_I915_SELFTEST_BROKEN))
		वापस 0;

	valid = biपंचांगap_zalloc(FW_RANGE, GFP_KERNEL);
	अगर (!valid)
		वापस -ENOMEM;

	पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);

	check_क्रम_unclaimed_mmio(uncore);
	क्रम (offset = 0; offset < FW_RANGE; offset += 4) अणु
		i915_reg_t reg = अणु offset पूर्ण;

		पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, reg);
		अगर (!check_क्रम_unclaimed_mmio(uncore))
			set_bit(offset, valid);
	पूर्ण

	पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);

	err = 0;
	क्रम_each_set_bit(offset, valid, FW_RANGE) अणु
		i915_reg_t reg = अणु offset पूर्ण;

		iosf_mbi_punit_acquire();
		पूर्णांकel_uncore_क्रमcewake_reset(uncore);
		iosf_mbi_punit_release();

		check_क्रम_unclaimed_mmio(uncore);

		पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, reg);
		अगर (check_क्रम_unclaimed_mmio(uncore)) अणु
			pr_err("Unclaimed mmio read to register 0x%04x\n",
			       offset);
			err = -EINVAL;
		पूर्ण
	पूर्ण

	biपंचांगap_मुक्त(valid);
	वापस err;
पूर्ण

अटल पूर्णांक live_fw_table(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;

	/* Confirm the table we load is still valid */
	वापस पूर्णांकel_fw_table_check(gt->uncore->fw_करोमुख्यs_table,
				    gt->uncore->fw_करोमुख्यs_table_entries,
				    INTEL_GEN(gt->i915) >= 9);
पूर्ण

पूर्णांक पूर्णांकel_uncore_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_fw_table),
		SUBTEST(live_क्रमcewake_ops),
		SUBTEST(live_क्रमcewake_करोमुख्यs),
	पूर्ण;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
