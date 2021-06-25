<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 *
 * Description: CoreSight Program Flow Trace driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/coresight.h>
#समावेश <linux/coresight-pmu.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/clk.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/sections.h>

#समावेश "coresight-etm.h"
#समावेश "coresight-etm-perf.h"

/*
 * Not really modular but using module_param is the easiest way to
 * reमुख्य consistent with existing use हालs क्रम now.
 */
अटल पूर्णांक boot_enable;
module_param_named(boot_enable, boot_enable, पूर्णांक, S_IRUGO);

अटल काष्ठा eपंचांग_drvdata *eपंचांगdrvdata[NR_CPUS];

अटल क्रमागत cpuhp_state hp_online;

/*
 * Memory mapped ग_लिखोs to clear os lock are not supported on some processors
 * and OS lock must be unlocked beक्रमe any memory mapped access on such
 * processors, otherwise memory mapped पढ़ोs/ग_लिखोs will be invalid.
 */
अटल व्योम eपंचांग_os_unlock(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	/* Writing any value to ETMOSLAR unlocks the trace रेजिस्टरs */
	eपंचांग_ग_लिखोl(drvdata, 0x0, ETMOSLAR);
	drvdata->os_unlock = true;
	isb();
पूर्ण

अटल व्योम eपंचांग_set_pwrdwn(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	u32 eपंचांगcr;

	/* Ensure pending cp14 accesses complete beक्रमe setting pwrdwn */
	mb();
	isb();
	eपंचांगcr = eपंचांग_पढ़ोl(drvdata, ETMCR);
	eपंचांगcr |= ETMCR_PWD_DWN;
	eपंचांग_ग_लिखोl(drvdata, eपंचांगcr, ETMCR);
पूर्ण

अटल व्योम eपंचांग_clr_pwrdwn(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	u32 eपंचांगcr;

	eपंचांगcr = eपंचांग_पढ़ोl(drvdata, ETMCR);
	eपंचांगcr &= ~ETMCR_PWD_DWN;
	eपंचांग_ग_लिखोl(drvdata, eपंचांगcr, ETMCR);
	/* Ensure pwrup completes beक्रमe subsequent cp14 accesses */
	mb();
	isb();
पूर्ण

अटल व्योम eपंचांग_set_pwrup(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	u32 eपंचांगpdcr;

	eपंचांगpdcr = पढ़ोl_relaxed(drvdata->base + ETMPDCR);
	eपंचांगpdcr |= ETMPDCR_PWD_UP;
	ग_लिखोl_relaxed(eपंचांगpdcr, drvdata->base + ETMPDCR);
	/* Ensure pwrup completes beक्रमe subsequent cp14 accesses */
	mb();
	isb();
पूर्ण

अटल व्योम eपंचांग_clr_pwrup(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	u32 eपंचांगpdcr;

	/* Ensure pending cp14 accesses complete beक्रमe clearing pwrup */
	mb();
	isb();
	eपंचांगpdcr = पढ़ोl_relaxed(drvdata->base + ETMPDCR);
	eपंचांगpdcr &= ~ETMPDCR_PWD_UP;
	ग_लिखोl_relaxed(eपंचांगpdcr, drvdata->base + ETMPDCR);
पूर्ण

/**
 * coresight_समयout_eपंचांग - loop until a bit has changed to a specअगरic state.
 * @drvdata: eपंचांग's निजी data काष्ठाure.
 * @offset: address of a रेजिस्टर, starting from @addr.
 * @position: the position of the bit of पूर्णांकerest.
 * @value: the value the bit should have.
 *
 * Basically the same as @coresight_समयout except क्रम the रेजिस्टर access
 * method where we have to account क्रम CP14 configurations.

 * Return: 0 as soon as the bit has taken the desired state or -EAGAIN अगर
 * TIMEOUT_US has elapsed, which ever happens first.
 */

अटल पूर्णांक coresight_समयout_eपंचांग(काष्ठा eपंचांग_drvdata *drvdata, u32 offset,
				  पूर्णांक position, पूर्णांक value)
अणु
	पूर्णांक i;
	u32 val;

	क्रम (i = TIMEOUT_US; i > 0; i--) अणु
		val = eपंचांग_पढ़ोl(drvdata, offset);
		/* Waiting on the bit to go from 0 to 1 */
		अगर (value) अणु
			अगर (val & BIT(position))
				वापस 0;
		/* Waiting on the bit to go from 1 to 0 */
		पूर्ण अन्यथा अणु
			अगर (!(val & BIT(position)))
				वापस 0;
		पूर्ण

		/*
		 * Delay is arbitrary - the specअगरication करोesn't say how दीर्घ
		 * we are expected to रुको.  Extra check required to make sure
		 * we करोn't रुको needlessly on the last iteration.
		 */
		अगर (i - 1)
			udelay(1);
	पूर्ण

	वापस -EAGAIN;
पूर्ण


अटल व्योम eपंचांग_set_prog(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	u32 eपंचांगcr;

	eपंचांगcr = eपंचांग_पढ़ोl(drvdata, ETMCR);
	eपंचांगcr |= ETMCR_ETM_PRG;
	eपंचांग_ग_लिखोl(drvdata, eपंचांगcr, ETMCR);
	/*
	 * Recommended by spec क्रम cp14 accesses to ensure eपंचांगcr ग_लिखो is
	 * complete beक्रमe polling eपंचांगsr
	 */
	isb();
	अगर (coresight_समयout_eपंचांग(drvdata, ETMSR, ETMSR_PROG_BIT, 1)) अणु
		dev_err(&drvdata->csdev->dev,
			"%s: timeout observed when probing at offset %#x\n",
			__func__, ETMSR);
	पूर्ण
पूर्ण

अटल व्योम eपंचांग_clr_prog(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	u32 eपंचांगcr;

	eपंचांगcr = eपंचांग_पढ़ोl(drvdata, ETMCR);
	eपंचांगcr &= ~ETMCR_ETM_PRG;
	eपंचांग_ग_लिखोl(drvdata, eपंचांगcr, ETMCR);
	/*
	 * Recommended by spec क्रम cp14 accesses to ensure eपंचांगcr ग_लिखो is
	 * complete beक्रमe polling eपंचांगsr
	 */
	isb();
	अगर (coresight_समयout_eपंचांग(drvdata, ETMSR, ETMSR_PROG_BIT, 0)) अणु
		dev_err(&drvdata->csdev->dev,
			"%s: timeout observed when probing at offset %#x\n",
			__func__, ETMSR);
	पूर्ण
पूर्ण

व्योम eपंचांग_set_शेष(काष्ठा eपंचांग_config *config)
अणु
	पूर्णांक i;

	अगर (WARN_ON_ONCE(!config))
		वापस;

	/*
	 * Taken verbatim from the TRM:
	 *
	 * To trace all memory:
	 *  set bit [24] in रेजिस्टर 0x009, the ETMTECR1, to 1
	 *  set all other bits in रेजिस्टर 0x009, the ETMTECR1, to 0
	 *  set all bits in रेजिस्टर 0x007, the ETMTECR2, to 0
	 *  set रेजिस्टर 0x008, the ETMTEEVR, to 0x6F (TRUE).
	 */
	config->enable_ctrl1 = BIT(24);
	config->enable_ctrl2 = 0x0;
	config->enable_event = ETM_HARD_WIRE_RES_A;

	config->trigger_event = ETM_DEFAULT_EVENT_VAL;
	config->enable_event = ETM_HARD_WIRE_RES_A;

	config->seq_12_event = ETM_DEFAULT_EVENT_VAL;
	config->seq_21_event = ETM_DEFAULT_EVENT_VAL;
	config->seq_23_event = ETM_DEFAULT_EVENT_VAL;
	config->seq_31_event = ETM_DEFAULT_EVENT_VAL;
	config->seq_32_event = ETM_DEFAULT_EVENT_VAL;
	config->seq_13_event = ETM_DEFAULT_EVENT_VAL;
	config->बारtamp_event = ETM_DEFAULT_EVENT_VAL;

	क्रम (i = 0; i < ETM_MAX_CNTR; i++) अणु
		config->cntr_rld_val[i] = 0x0;
		config->cntr_event[i] = ETM_DEFAULT_EVENT_VAL;
		config->cntr_rld_event[i] = ETM_DEFAULT_EVENT_VAL;
		config->cntr_val[i] = 0x0;
	पूर्ण

	config->seq_curr_state = 0x0;
	config->ctxid_idx = 0x0;
	क्रम (i = 0; i < ETM_MAX_CTXID_CMP; i++)
		config->ctxid_pid[i] = 0x0;

	config->ctxid_mask = 0x0;
	/* Setting शेष to 1024 as per TRM recommendation */
	config->sync_freq = 0x400;
पूर्ण

व्योम eपंचांग_config_trace_mode(काष्ठा eपंचांग_config *config)
अणु
	u32 flags, mode;

	mode = config->mode;

	mode &= (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER);

	/* excluding kernel AND user space करोesn't make sense */
	अगर (mode == (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER))
		वापस;

	/* nothing to करो अगर neither flags are set */
	अगर (!(mode & ETM_MODE_EXCL_KERN) && !(mode & ETM_MODE_EXCL_USER))
		वापस;

	flags = (1 << 0 |	/* inकाष्ठाion execute */
		 3 << 3 |	/* ARM inकाष्ठाion */
		 0 << 5 |	/* No data value comparison */
		 0 << 7 |	/* No exact mach */
		 0 << 8);	/* Ignore context ID */

	/* No need to worry about single address comparators. */
	config->enable_ctrl2 = 0x0;

	/* Bit 0 is address range comparator 1 */
	config->enable_ctrl1 = ETMTECR1_ADDR_COMP_1;

	/*
	 * On ETMv3.5:
	 * ETMACTRn[13,11] == Non-secure state comparison control
	 * ETMACTRn[12,10] == Secure state comparison control
	 *
	 * b00 == Match in all modes in this state
	 * b01 == Do not match in any more in this state
	 * b10 == Match in all modes excepts user mode in this state
	 * b11 == Match only in user mode in this state
	 */

	/* Tracing in secure mode is not supported at this समय */
	flags |= (0 << 12 | 1 << 10);

	अगर (mode & ETM_MODE_EXCL_USER) अणु
		/* exclude user, match all modes except user mode */
		flags |= (1 << 13 | 0 << 11);
	पूर्ण अन्यथा अणु
		/* exclude kernel, match only in user mode */
		flags |= (1 << 13 | 1 << 11);
	पूर्ण

	/*
	 * The ETMEEVR रेजिस्टर is alपढ़ोy set to "hard wire A".  As such
	 * all there is to करो is setup an address comparator that spans
	 * the entire address range and configure the state and mode bits.
	 */
	config->addr_val[0] = (u32) 0x0;
	config->addr_val[1] = (u32) ~0x0;
	config->addr_acctype[0] = flags;
	config->addr_acctype[1] = flags;
	config->addr_type[0] = ETM_ADDR_TYPE_RANGE;
	config->addr_type[1] = ETM_ADDR_TYPE_RANGE;
पूर्ण

#घोषणा ETM3X_SUPPORTED_OPTIONS (ETMCR_CYC_ACC | \
				 ETMCR_TIMESTAMP_EN | \
				 ETMCR_RETURN_STACK)

अटल पूर्णांक eपंचांग_parse_event_config(काष्ठा eपंचांग_drvdata *drvdata,
				  काष्ठा perf_event *event)
अणु
	काष्ठा eपंचांग_config *config = &drvdata->config;
	काष्ठा perf_event_attr *attr = &event->attr;

	अगर (!attr)
		वापस -EINVAL;

	/* Clear configuration from previous run */
	स_रखो(config, 0, माप(काष्ठा eपंचांग_config));

	अगर (attr->exclude_kernel)
		config->mode = ETM_MODE_EXCL_KERN;

	अगर (attr->exclude_user)
		config->mode = ETM_MODE_EXCL_USER;

	/* Always start from the शेष config */
	eपंचांग_set_शेष(config);

	/*
	 * By शेष the tracers are configured to trace the whole address
	 * range.  Narrow the field only अगर requested by user space.
	 */
	अगर (config->mode)
		eपंचांग_config_trace_mode(config);

	/*
	 * At this समय only cycle accurate, वापस stack  and बारtamp
	 * options are available.
	 */
	अगर (attr->config & ~ETM3X_SUPPORTED_OPTIONS)
		वापस -EINVAL;

	config->ctrl = attr->config;

	/*
	 * Possible to have cores with PTM (supports ret stack) and ETM
	 * (never has ret stack) on the same SoC. So अगर we have a request
	 * क्रम वापस stack that can't be honoured on this core then
	 * clear the bit - trace will still जारी normally
	 */
	अगर ((config->ctrl & ETMCR_RETURN_STACK) &&
	    !(drvdata->eपंचांगccer & ETMCCER_RETSTACK))
		config->ctrl &= ~ETMCR_RETURN_STACK;

	वापस 0;
पूर्ण

अटल पूर्णांक eपंचांग_enable_hw(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	पूर्णांक i, rc;
	u32 eपंचांगcr;
	काष्ठा eपंचांग_config *config = &drvdata->config;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	CS_UNLOCK(drvdata->base);

	rc = coresight_claim_device_unlocked(csdev);
	अगर (rc)
		जाओ करोne;

	/* Turn engine on */
	eपंचांग_clr_pwrdwn(drvdata);
	/* Apply घातer to trace रेजिस्टरs */
	eपंचांग_set_pwrup(drvdata);
	/* Make sure all रेजिस्टरs are accessible */
	eपंचांग_os_unlock(drvdata);

	eपंचांग_set_prog(drvdata);

	eपंचांगcr = eपंचांग_पढ़ोl(drvdata, ETMCR);
	/* Clear setting from a previous run अगर need be */
	eपंचांगcr &= ~ETM3X_SUPPORTED_OPTIONS;
	eपंचांगcr |= drvdata->port_size;
	eपंचांगcr |= ETMCR_ETM_EN;
	eपंचांग_ग_लिखोl(drvdata, config->ctrl | eपंचांगcr, ETMCR);
	eपंचांग_ग_लिखोl(drvdata, config->trigger_event, ETMTRIGGER);
	eपंचांग_ग_लिखोl(drvdata, config->startstop_ctrl, ETMTSSCR);
	eपंचांग_ग_लिखोl(drvdata, config->enable_event, ETMTEEVR);
	eपंचांग_ग_लिखोl(drvdata, config->enable_ctrl1, ETMTECR1);
	eपंचांग_ग_लिखोl(drvdata, config->fअगरofull_level, ETMFFLR);
	क्रम (i = 0; i < drvdata->nr_addr_cmp; i++) अणु
		eपंचांग_ग_लिखोl(drvdata, config->addr_val[i], ETMACVRn(i));
		eपंचांग_ग_लिखोl(drvdata, config->addr_acctype[i], ETMACTRn(i));
	पूर्ण
	क्रम (i = 0; i < drvdata->nr_cntr; i++) अणु
		eपंचांग_ग_लिखोl(drvdata, config->cntr_rld_val[i], ETMCNTRLDVRn(i));
		eपंचांग_ग_लिखोl(drvdata, config->cntr_event[i], ETMCNTENRn(i));
		eपंचांग_ग_लिखोl(drvdata, config->cntr_rld_event[i],
			   ETMCNTRLDEVRn(i));
		eपंचांग_ग_लिखोl(drvdata, config->cntr_val[i], ETMCNTVRn(i));
	पूर्ण
	eपंचांग_ग_लिखोl(drvdata, config->seq_12_event, ETMSQ12EVR);
	eपंचांग_ग_लिखोl(drvdata, config->seq_21_event, ETMSQ21EVR);
	eपंचांग_ग_लिखोl(drvdata, config->seq_23_event, ETMSQ23EVR);
	eपंचांग_ग_लिखोl(drvdata, config->seq_31_event, ETMSQ31EVR);
	eपंचांग_ग_लिखोl(drvdata, config->seq_32_event, ETMSQ32EVR);
	eपंचांग_ग_लिखोl(drvdata, config->seq_13_event, ETMSQ13EVR);
	eपंचांग_ग_लिखोl(drvdata, config->seq_curr_state, ETMSQR);
	क्रम (i = 0; i < drvdata->nr_ext_out; i++)
		eपंचांग_ग_लिखोl(drvdata, ETM_DEFAULT_EVENT_VAL, ETMEXTOUTEVRn(i));
	क्रम (i = 0; i < drvdata->nr_ctxid_cmp; i++)
		eपंचांग_ग_लिखोl(drvdata, config->ctxid_pid[i], ETMCIDCVRn(i));
	eपंचांग_ग_लिखोl(drvdata, config->ctxid_mask, ETMCIDCMR);
	eपंचांग_ग_लिखोl(drvdata, config->sync_freq, ETMSYNCFR);
	/* No बाह्यal input selected */
	eपंचांग_ग_लिखोl(drvdata, 0x0, ETMEXTINSELR);
	eपंचांग_ग_लिखोl(drvdata, config->बारtamp_event, ETMTSEVR);
	/* No auxiliary control selected */
	eपंचांग_ग_लिखोl(drvdata, 0x0, ETMAUXCR);
	eपंचांग_ग_लिखोl(drvdata, drvdata->traceid, ETMTRACEIDR);
	/* No VMID comparator value selected */
	eपंचांग_ग_लिखोl(drvdata, 0x0, ETMVMIDCVR);

	eपंचांग_clr_prog(drvdata);

करोne:
	CS_LOCK(drvdata->base);

	dev_dbg(&drvdata->csdev->dev, "cpu: %d enable smp call done: %d\n",
		drvdata->cpu, rc);
	वापस rc;
पूर्ण

काष्ठा eपंचांग_enable_arg अणु
	काष्ठा eपंचांग_drvdata *drvdata;
	पूर्णांक rc;
पूर्ण;

अटल व्योम eपंचांग_enable_hw_smp_call(व्योम *info)
अणु
	काष्ठा eपंचांग_enable_arg *arg = info;

	अगर (WARN_ON(!arg))
		वापस;
	arg->rc = eपंचांग_enable_hw(arg->drvdata);
पूर्ण

अटल पूर्णांक eपंचांग_cpu_id(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	वापस drvdata->cpu;
पूर्ण

पूर्णांक eपंचांग_get_trace_id(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक trace_id = -1;
	काष्ठा device *eपंचांग_dev;

	अगर (!drvdata)
		जाओ out;

	eपंचांग_dev = drvdata->csdev->dev.parent;
	अगर (!local_पढ़ो(&drvdata->mode))
		वापस drvdata->traceid;

	pm_runसमय_get_sync(eपंचांग_dev);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	CS_UNLOCK(drvdata->base);
	trace_id = (eपंचांग_पढ़ोl(drvdata, ETMTRACEIDR) & ETM_TRACEID_MASK);
	CS_LOCK(drvdata->base);

	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	pm_runसमय_put(eपंचांग_dev);

out:
	वापस trace_id;

पूर्ण

अटल पूर्णांक eपंचांग_trace_id(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	वापस eपंचांग_get_trace_id(drvdata);
पूर्ण

अटल पूर्णांक eपंचांग_enable_perf(काष्ठा coresight_device *csdev,
			   काष्ठा perf_event *event)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	अगर (WARN_ON_ONCE(drvdata->cpu != smp_processor_id()))
		वापस -EINVAL;

	/* Configure the tracer based on the session's specअगरics */
	eपंचांग_parse_event_config(drvdata, event);
	/* And enable it */
	वापस eपंचांग_enable_hw(drvdata);
पूर्ण

अटल पूर्णांक eपंचांग_enable_sysfs(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा eपंचांग_enable_arg arg = अणु पूर्ण;
	पूर्णांक ret;

	spin_lock(&drvdata->spinlock);

	/*
	 * Configure the ETM only अगर the CPU is online.  If it isn't online
	 * hw configuration will take place on the local CPU during bring up.
	 */
	अगर (cpu_online(drvdata->cpu)) अणु
		arg.drvdata = drvdata;
		ret = smp_call_function_single(drvdata->cpu,
					       eपंचांग_enable_hw_smp_call, &arg, 1);
		अगर (!ret)
			ret = arg.rc;
		अगर (!ret)
			drvdata->sticky_enable = true;
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण

	spin_unlock(&drvdata->spinlock);

	अगर (!ret)
		dev_dbg(&csdev->dev, "ETM tracing enabled\n");
	वापस ret;
पूर्ण

अटल पूर्णांक eपंचांग_enable(काष्ठा coresight_device *csdev,
		      काष्ठा perf_event *event, u32 mode)
अणु
	पूर्णांक ret;
	u32 val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	val = local_cmpxchg(&drvdata->mode, CS_MODE_DISABLED, mode);

	/* Someone is alपढ़ोy using the tracer */
	अगर (val)
		वापस -EBUSY;

	चयन (mode) अणु
	हाल CS_MODE_SYSFS:
		ret = eपंचांग_enable_sysfs(csdev);
		अवरोध;
	हाल CS_MODE_PERF:
		ret = eपंचांग_enable_perf(csdev, event);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	/* The tracer didn't start */
	अगर (ret)
		local_set(&drvdata->mode, CS_MODE_DISABLED);

	वापस ret;
पूर्ण

अटल व्योम eपंचांग_disable_hw(व्योम *info)
अणु
	पूर्णांक i;
	काष्ठा eपंचांग_drvdata *drvdata = info;
	काष्ठा eपंचांग_config *config = &drvdata->config;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	CS_UNLOCK(drvdata->base);
	eपंचांग_set_prog(drvdata);

	/* Read back sequencer and counters क्रम post trace analysis */
	config->seq_curr_state = (eपंचांग_पढ़ोl(drvdata, ETMSQR) & ETM_SQR_MASK);

	क्रम (i = 0; i < drvdata->nr_cntr; i++)
		config->cntr_val[i] = eपंचांग_पढ़ोl(drvdata, ETMCNTVRn(i));

	eपंचांग_set_pwrdwn(drvdata);
	coresight_disclaim_device_unlocked(csdev);

	CS_LOCK(drvdata->base);

	dev_dbg(&drvdata->csdev->dev,
		"cpu: %d disable smp call done\n", drvdata->cpu);
पूर्ण

अटल व्योम eपंचांग_disable_perf(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	अगर (WARN_ON_ONCE(drvdata->cpu != smp_processor_id()))
		वापस;

	CS_UNLOCK(drvdata->base);

	/* Setting the prog bit disables tracing immediately */
	eपंचांग_set_prog(drvdata);

	/*
	 * There is no way to know when the tracer will be used again so
	 * घातer करोwn the tracer.
	 */
	eपंचांग_set_pwrdwn(drvdata);
	coresight_disclaim_device_unlocked(csdev);

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम eपंचांग_disable_sysfs(काष्ठा coresight_device *csdev)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	/*
	 * Taking hotplug lock here protects from घड़ीs getting disabled
	 * with tracing being left on (crash scenario) अगर user disable occurs
	 * after cpu online mask indicates the cpu is offline but beक्रमe the
	 * DYING hotplug callback is serviced by the ETM driver.
	 */
	cpus_पढ़ो_lock();
	spin_lock(&drvdata->spinlock);

	/*
	 * Executing eपंचांग_disable_hw on the cpu whose ETM is being disabled
	 * ensures that रेजिस्टर ग_लिखोs occur when cpu is घातered.
	 */
	smp_call_function_single(drvdata->cpu, eपंचांग_disable_hw, drvdata, 1);

	spin_unlock(&drvdata->spinlock);
	cpus_पढ़ो_unlock();

	dev_dbg(&csdev->dev, "ETM tracing disabled\n");
पूर्ण

अटल व्योम eपंचांग_disable(काष्ठा coresight_device *csdev,
			काष्ठा perf_event *event)
अणु
	u32 mode;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	/*
	 * For as दीर्घ as the tracer isn't disabled another entity can't
	 * change its status.  As such we can पढ़ो the status here without
	 * fearing it will change under us.
	 */
	mode = local_पढ़ो(&drvdata->mode);

	चयन (mode) अणु
	हाल CS_MODE_DISABLED:
		अवरोध;
	हाल CS_MODE_SYSFS:
		eपंचांग_disable_sysfs(csdev);
		अवरोध;
	हाल CS_MODE_PERF:
		eपंचांग_disable_perf(csdev);
		अवरोध;
	शेष:
		WARN_ON_ONCE(mode);
		वापस;
	पूर्ण

	अगर (mode)
		local_set(&drvdata->mode, CS_MODE_DISABLED);
पूर्ण

अटल स्थिर काष्ठा coresight_ops_source eपंचांग_source_ops = अणु
	.cpu_id		= eपंचांग_cpu_id,
	.trace_id	= eपंचांग_trace_id,
	.enable		= eपंचांग_enable,
	.disable	= eपंचांग_disable,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops eपंचांग_cs_ops = अणु
	.source_ops	= &eपंचांग_source_ops,
पूर्ण;

अटल पूर्णांक eपंचांग_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!eपंचांगdrvdata[cpu])
		वापस 0;

	अगर (eपंचांगdrvdata[cpu]->boot_enable && !eपंचांगdrvdata[cpu]->sticky_enable)
		coresight_enable(eपंचांगdrvdata[cpu]->csdev);
	वापस 0;
पूर्ण

अटल पूर्णांक eपंचांग_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!eपंचांगdrvdata[cpu])
		वापस 0;

	spin_lock(&eपंचांगdrvdata[cpu]->spinlock);
	अगर (!eपंचांगdrvdata[cpu]->os_unlock) अणु
		eपंचांग_os_unlock(eपंचांगdrvdata[cpu]);
		eपंचांगdrvdata[cpu]->os_unlock = true;
	पूर्ण

	अगर (local_पढ़ो(&eपंचांगdrvdata[cpu]->mode))
		eपंचांग_enable_hw(eपंचांगdrvdata[cpu]);
	spin_unlock(&eपंचांगdrvdata[cpu]->spinlock);
	वापस 0;
पूर्ण

अटल पूर्णांक eपंचांग_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!eपंचांगdrvdata[cpu])
		वापस 0;

	spin_lock(&eपंचांगdrvdata[cpu]->spinlock);
	अगर (local_पढ़ो(&eपंचांगdrvdata[cpu]->mode))
		eपंचांग_disable_hw(eपंचांगdrvdata[cpu]);
	spin_unlock(&eपंचांगdrvdata[cpu]->spinlock);
	वापस 0;
पूर्ण

अटल bool eपंचांग_arch_supported(u8 arch)
अणु
	चयन (arch) अणु
	हाल ETM_ARCH_V3_3:
		अवरोध;
	हाल ETM_ARCH_V3_5:
		अवरोध;
	हाल PFT_ARCH_V1_0:
		अवरोध;
	हाल PFT_ARCH_V1_1:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम eपंचांग_init_arch_data(व्योम *info)
अणु
	u32 eपंचांगidr;
	u32 eपंचांगccr;
	काष्ठा eपंचांग_drvdata *drvdata = info;

	/* Make sure all रेजिस्टरs are accessible */
	eपंचांग_os_unlock(drvdata);

	CS_UNLOCK(drvdata->base);

	/* First dummy पढ़ो */
	(व्योम)eपंचांग_पढ़ोl(drvdata, ETMPDSR);
	/* Provide घातer to ETM: ETMPDCR[3] == 1 */
	eपंचांग_set_pwrup(drvdata);
	/*
	 * Clear घातer करोwn bit since when this bit is set ग_लिखोs to
	 * certain रेजिस्टरs might be ignored.
	 */
	eपंचांग_clr_pwrdwn(drvdata);
	/*
	 * Set prog bit. It will be set from reset but this is included to
	 * ensure it is set
	 */
	eपंचांग_set_prog(drvdata);

	/* Find all capabilities */
	eपंचांगidr = eपंचांग_पढ़ोl(drvdata, ETMIDR);
	drvdata->arch = BMVAL(eपंचांगidr, 4, 11);
	drvdata->port_size = eपंचांग_पढ़ोl(drvdata, ETMCR) & PORT_SIZE_MASK;

	drvdata->eपंचांगccer = eपंचांग_पढ़ोl(drvdata, ETMCCER);
	eपंचांगccr = eपंचांग_पढ़ोl(drvdata, ETMCCR);
	drvdata->eपंचांगccr = eपंचांगccr;
	drvdata->nr_addr_cmp = BMVAL(eपंचांगccr, 0, 3) * 2;
	drvdata->nr_cntr = BMVAL(eपंचांगccr, 13, 15);
	drvdata->nr_ext_inp = BMVAL(eपंचांगccr, 17, 19);
	drvdata->nr_ext_out = BMVAL(eपंचांगccr, 20, 22);
	drvdata->nr_ctxid_cmp = BMVAL(eपंचांगccr, 24, 25);

	eपंचांग_set_pwrdwn(drvdata);
	eपंचांग_clr_pwrup(drvdata);
	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम eपंचांग_init_trace_id(काष्ठा eपंचांग_drvdata *drvdata)
अणु
	drvdata->traceid = coresight_get_trace_id(drvdata->cpu);
पूर्ण

अटल पूर्णांक __init eपंचांग_hp_setup(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_nocalls_cpuslocked(CPUHP_AP_ARM_CORESIGHT_STARTING,
						   "arm/coresight:starting",
						   eपंचांग_starting_cpu, eपंचांग_dying_cpu);

	अगर (ret)
		वापस ret;

	ret = cpuhp_setup_state_nocalls_cpuslocked(CPUHP_AP_ONLINE_DYN,
						   "arm/coresight:online",
						   eपंचांग_online_cpu, शून्य);

	/* HP dyn state ID वापसed in ret on success */
	अगर (ret > 0) अणु
		hp_online = ret;
		वापस 0;
	पूर्ण

	/* failed dyn state - हटाओ others */
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_ARM_CORESIGHT_STARTING);

	वापस ret;
पूर्ण

अटल व्योम eपंचांग_hp_clear(व्योम)
अणु
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_ARM_CORESIGHT_STARTING);
	अगर (hp_online) अणु
		cpuhp_हटाओ_state_nocalls(hp_online);
		hp_online = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक eपंचांग_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret;
	व्योम __iomem *base;
	काष्ठा device *dev = &adev->dev;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा eपंचांग_drvdata *drvdata;
	काष्ठा resource *res = &adev->res;
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->use_cp14 = fwnode_property_पढ़ो_bool(dev->fwnode, "arm,cp14");
	dev_set_drvdata(dev, drvdata);

	/* Validity क्रम the resource is alपढ़ोy checked by the AMBA core */
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	drvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	spin_lock_init(&drvdata->spinlock);

	drvdata->atclk = devm_clk_get(&adev->dev, "atclk"); /* optional */
	अगर (!IS_ERR(drvdata->atclk)) अणु
		ret = clk_prepare_enable(drvdata->atclk);
		अगर (ret)
			वापस ret;
	पूर्ण

	drvdata->cpu = coresight_get_cpu(dev);
	अगर (drvdata->cpu < 0)
		वापस drvdata->cpu;

	desc.name  = devm_kaप्र_लिखो(dev, GFP_KERNEL, "etm%d", drvdata->cpu);
	अगर (!desc.name)
		वापस -ENOMEM;

	अगर (smp_call_function_single(drvdata->cpu,
				     eपंचांग_init_arch_data,  drvdata, 1))
		dev_err(dev, "ETM arch init failed\n");

	अगर (eपंचांग_arch_supported(drvdata->arch) == false)
		वापस -EINVAL;

	eपंचांग_init_trace_id(drvdata);
	eपंचांग_set_शेष(&drvdata->config);

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	adev->dev.platक्रमm_data = pdata;

	desc.type = CORESIGHT_DEV_TYPE_SOURCE;
	desc.subtype.source_subtype = CORESIGHT_DEV_SUBTYPE_SOURCE_PROC;
	desc.ops = &eपंचांग_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	desc.groups = coresight_eपंचांग_groups;
	drvdata->csdev = coresight_रेजिस्टर(&desc);
	अगर (IS_ERR(drvdata->csdev))
		वापस PTR_ERR(drvdata->csdev);

	ret = eपंचांग_perf_symlink(drvdata->csdev, true);
	अगर (ret) अणु
		coresight_unरेजिस्टर(drvdata->csdev);
		वापस ret;
	पूर्ण

	eपंचांगdrvdata[drvdata->cpu] = drvdata;

	pm_runसमय_put(&adev->dev);
	dev_info(&drvdata->csdev->dev,
		 "%s initialized\n", (अक्षर *)coresight_get_uci_data(id));
	अगर (boot_enable) अणु
		coresight_enable(drvdata->csdev);
		drvdata->boot_enable = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम clear_eपंचांगdrvdata(व्योम *info)
अणु
	पूर्णांक cpu = *(पूर्णांक *)info;

	eपंचांगdrvdata[cpu] = शून्य;
पूर्ण

अटल व्योम eपंचांग_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(&adev->dev);

	eपंचांग_perf_symlink(drvdata->csdev, false);

	/*
	 * Taking hotplug lock here to aव्योम racing between eपंचांग_हटाओ and
	 * CPU hotplug call backs.
	 */
	cpus_पढ़ो_lock();
	/*
	 * The पढ़ोers क्रम eपंचांगdrvdata[] are CPU hotplug call backs
	 * and PM notअगरication call backs. Change eपंचांगdrvdata[i] on
	 * CPU i ensures these call backs has consistent view
	 * inside one call back function.
	 */
	अगर (smp_call_function_single(drvdata->cpu, clear_eपंचांगdrvdata, &drvdata->cpu, 1))
		eपंचांगdrvdata[drvdata->cpu] = शून्य;

	cpus_पढ़ो_unlock();

	coresight_unरेजिस्टर(drvdata->csdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक eपंचांग_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);

	वापस 0;
पूर्ण

अटल पूर्णांक eपंचांग_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_prepare_enable(drvdata->atclk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops eपंचांग_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(eपंचांग_runसमय_suspend, eपंचांग_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा amba_id eपंचांग_ids[] = अणु
	/* ETM 3.3 */
	CS_AMBA_ID_DATA(0x000bb921, "ETM 3.3"),
	/* ETM 3.5 - Cortex-A5 */
	CS_AMBA_ID_DATA(0x000bb955, "ETM 3.5"),
	/* ETM 3.5 */
	CS_AMBA_ID_DATA(0x000bb956, "ETM 3.5"),
	/* PTM 1.0 */
	CS_AMBA_ID_DATA(0x000bb950, "PTM 1.0"),
	/* PTM 1.1 */
	CS_AMBA_ID_DATA(0x000bb95f, "PTM 1.1"),
	/* PTM 1.1 Qualcomm */
	CS_AMBA_ID_DATA(0x000b006f, "PTM 1.1"),
	अणु 0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, eपंचांग_ids);

अटल काष्ठा amba_driver eपंचांग_driver = अणु
	.drv = अणु
		.name	= "coresight-etm3x",
		.owner	= THIS_MODULE,
		.pm	= &eपंचांग_dev_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= eपंचांग_probe,
	.हटाओ         = eपंचांग_हटाओ,
	.id_table	= eपंचांग_ids,
पूर्ण;

अटल पूर्णांक __init eपंचांग_init(व्योम)
अणु
	पूर्णांक ret;

	ret = eपंचांग_hp_setup();

	/* eपंचांग_hp_setup() करोes its own cleanup - निकास on error */
	अगर (ret)
		वापस ret;

	ret = amba_driver_रेजिस्टर(&eपंचांग_driver);
	अगर (ret) अणु
		pr_err("Error registering etm3x driver\n");
		eपंचांग_hp_clear();
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास eपंचांग_निकास(व्योम)
अणु
	amba_driver_unरेजिस्टर(&eपंचांग_driver);
	eपंचांग_hp_clear();
पूर्ण

module_init(eपंचांग_init);
module_निकास(eपंचांग_निकास);

MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_AUTHOR("Mathieu Poirier <mathieu.poirier@linaro.org>");
MODULE_DESCRIPTION("Arm CoreSight Program Flow Trace driver");
MODULE_LICENSE("GPL v2");
