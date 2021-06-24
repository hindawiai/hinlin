<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/bug.h>
#समावेश <linux/पन.स>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/soc/qcom/mdt_loader.h>

#समावेश "ipa.h"
#समावेश "ipa_clock.h"
#समावेश "ipa_data.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_resource.h"
#समावेश "ipa_cmd.h"
#समावेश "ipa_reg.h"
#समावेश "ipa_mem.h"
#समावेश "ipa_table.h"
#समावेश "ipa_modem.h"
#समावेश "ipa_uc.h"
#समावेश "ipa_interrupt.h"
#समावेश "gsi_trans.h"

/**
 * DOC: The IP Accelerator
 *
 * This driver supports the Qualcomm IP Accelerator (IPA), which is a
 * networking component found in many Qualcomm SoCs.  The IPA is connected
 * to the application processor (AP), but is also connected (and partially
 * controlled by) other "execution environments" (EEs), such as a modem.
 *
 * The IPA is the conduit between the AP and the modem that carries network
 * traffic.  This driver presents a network पूर्णांकerface representing the
 * connection of the modem to बाह्यal (e.g. LTE) networks.
 *
 * The IPA provides protocol checksum calculation, offloading this work
 * from the AP.  The IPA offers additional functionality, including routing,
 * filtering, and NAT support, but that more advanced functionality is not
 * currently supported.  Despite that, some resources--including routing
 * tables and filter tables--are defined in this driver because they must
 * be initialized even when the advanced hardware features are not used.
 *
 * There are two distinct layers that implement the IPA hardware, and this
 * is reflected in the organization of the driver.  The generic software
 * पूर्णांकerface (GSI) is an पूर्णांकegral component of the IPA, providing a
 * well-defined communication layer between the AP subप्रणाली and the IPA
 * core.  The GSI implements a set of "channels" used क्रम communication
 * between the AP and the IPA.
 *
 * The IPA layer uses GSI channels to implement its "endpoints".  And जबतक
 * a GSI channel carries data between the AP and the IPA, a pair of IPA
 * endpoपूर्णांकs is used to carry traffic between two EEs.  Specअगरically, the मुख्य
 * modem network पूर्णांकerface is implemented by two pairs of endpoपूर्णांकs:  a TX
 * endpoपूर्णांक on the AP coupled with an RX endpoपूर्णांक on the modem; and another
 * RX endpoपूर्णांक on the AP receiving data from a TX endpoपूर्णांक on the modem.
 */

/* The name of the GSI firmware file relative to /lib/firmware */
#घोषणा IPA_FW_PATH_DEFAULT	"ipa_fws.mdt"
#घोषणा IPA_PAS_ID		15

/* Shअगरt of 19.2 MHz बारtamp to achieve lower resolution बारtamps */
#घोषणा DPL_TIMESTAMP_SHIFT	14	/* ~1.172 kHz, ~853 usec per tick */
#घोषणा TAG_TIMESTAMP_SHIFT	14
#घोषणा NAT_TIMESTAMP_SHIFT	24	/* ~1.144 Hz, ~874 msec per tick */

/* Divider क्रम 19.2 MHz crystal oscillator घड़ी to get common समयr घड़ी */
#घोषणा IPA_XO_CLOCK_DIVIDER	192	/* 1 is subtracted where used */

/**
 * ipa_suspend_handler() - Handle the suspend IPA पूर्णांकerrupt
 * @ipa:	IPA poपूर्णांकer
 * @irq_id:	IPA पूर्णांकerrupt type (unused)
 *
 * If an RX endpoपूर्णांक is in suspend state, and the IPA has a packet
 * destined क्रम that endpoपूर्णांक, the IPA generates a SUSPEND पूर्णांकerrupt
 * to inक्रमm the AP that it should resume the endpoपूर्णांक.  If we get
 * one of these पूर्णांकerrupts we just resume everything.
 */
अटल व्योम ipa_suspend_handler(काष्ठा ipa *ipa, क्रमागत ipa_irq_id irq_id)
अणु
	/* Just report the event, and let प्रणाली resume handle the rest.
	 * More than one endpoपूर्णांक could संकेत this; अगर so, ignore
	 * all but the first.
	 */
	अगर (!test_and_set_bit(IPA_FLAG_RESUMED, ipa->flags))
		pm_wakeup_dev_event(&ipa->pdev->dev, 0, true);

	/* Acknowledge/clear the suspend पूर्णांकerrupt on all endpoपूर्णांकs */
	ipa_पूर्णांकerrupt_suspend_clear_all(ipa->पूर्णांकerrupt);
पूर्ण

/**
 * ipa_setup() - Set up IPA hardware
 * @ipa:	IPA poपूर्णांकer
 *
 * Perक्रमm initialization that requires issuing immediate commands on
 * the command TX endpoपूर्णांक.  If the modem is करोing GSI firmware load
 * and initialization, this function will be called when an SMP2P
 * पूर्णांकerrupt has been संकेतed by the modem.  Otherwise it will be
 * called from ipa_probe() after GSI firmware has been successfully
 * loaded, authenticated, and started by Trust Zone.
 */
पूर्णांक ipa_setup(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_endpoपूर्णांक *exception_endpoपूर्णांक;
	काष्ठा ipa_endpoपूर्णांक *command_endpoपूर्णांक;
	काष्ठा device *dev = &ipa->pdev->dev;
	पूर्णांक ret;

	ret = gsi_setup(&ipa->gsi);
	अगर (ret)
		वापस ret;

	ipa->पूर्णांकerrupt = ipa_पूर्णांकerrupt_setup(ipa);
	अगर (IS_ERR(ipa->पूर्णांकerrupt)) अणु
		ret = PTR_ERR(ipa->पूर्णांकerrupt);
		जाओ err_gsi_tearकरोwn;
	पूर्ण
	ipa_पूर्णांकerrupt_add(ipa->पूर्णांकerrupt, IPA_IRQ_TX_SUSPEND,
			  ipa_suspend_handler);

	ipa_uc_setup(ipa);

	ret = device_init_wakeup(dev, true);
	अगर (ret)
		जाओ err_uc_tearकरोwn;

	ipa_endpoपूर्णांक_setup(ipa);

	/* We need to use the AP command TX endpoपूर्णांक to perक्रमm other
	 * initialization, so we enable first.
	 */
	command_endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX];
	ret = ipa_endpoपूर्णांक_enable_one(command_endpoपूर्णांक);
	अगर (ret)
		जाओ err_endpoपूर्णांक_tearकरोwn;

	ret = ipa_mem_setup(ipa);	/* No matching tearकरोwn required */
	अगर (ret)
		जाओ err_command_disable;

	ret = ipa_table_setup(ipa);	/* No matching tearकरोwn required */
	अगर (ret)
		जाओ err_command_disable;

	/* Enable the exception handling endpoपूर्णांक, and tell the hardware
	 * to use it by शेष.
	 */
	exception_endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_LAN_RX];
	ret = ipa_endpoपूर्णांक_enable_one(exception_endpoपूर्णांक);
	अगर (ret)
		जाओ err_command_disable;

	ipa_endpoपूर्णांक_शेष_route_set(ipa, exception_endpoपूर्णांक->endpoपूर्णांक_id);

	/* We're all set.  Now prepare क्रम communication with the modem */
	ret = ipa_modem_setup(ipa);
	अगर (ret)
		जाओ err_शेष_route_clear;

	ipa->setup_complete = true;

	dev_info(dev, "IPA driver setup completed successfully\n");

	वापस 0;

err_शेष_route_clear:
	ipa_endpoपूर्णांक_शेष_route_clear(ipa);
	ipa_endpoपूर्णांक_disable_one(exception_endpoपूर्णांक);
err_command_disable:
	ipa_endpoपूर्णांक_disable_one(command_endpoपूर्णांक);
err_endpoपूर्णांक_tearकरोwn:
	ipa_endpoपूर्णांक_tearकरोwn(ipa);
	(व्योम)device_init_wakeup(dev, false);
err_uc_tearकरोwn:
	ipa_uc_tearकरोwn(ipa);
	ipa_पूर्णांकerrupt_हटाओ(ipa->पूर्णांकerrupt, IPA_IRQ_TX_SUSPEND);
	ipa_पूर्णांकerrupt_tearकरोwn(ipa->पूर्णांकerrupt);
err_gsi_tearकरोwn:
	gsi_tearकरोwn(&ipa->gsi);

	वापस ret;
पूर्ण

/**
 * ipa_tearकरोwn() - Inverse of ipa_setup()
 * @ipa:	IPA poपूर्णांकer
 */
अटल व्योम ipa_tearकरोwn(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_endpoपूर्णांक *exception_endpoपूर्णांक;
	काष्ठा ipa_endpoपूर्णांक *command_endpoपूर्णांक;

	ipa_modem_tearकरोwn(ipa);
	ipa_endpoपूर्णांक_शेष_route_clear(ipa);
	exception_endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_LAN_RX];
	ipa_endpoपूर्णांक_disable_one(exception_endpoपूर्णांक);
	command_endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX];
	ipa_endpoपूर्णांक_disable_one(command_endpoपूर्णांक);
	ipa_endpoपूर्णांक_tearकरोwn(ipa);
	(व्योम)device_init_wakeup(&ipa->pdev->dev, false);
	ipa_uc_tearकरोwn(ipa);
	ipa_पूर्णांकerrupt_हटाओ(ipa->पूर्णांकerrupt, IPA_IRQ_TX_SUSPEND);
	ipa_पूर्णांकerrupt_tearकरोwn(ipa->पूर्णांकerrupt);
	gsi_tearकरोwn(&ipa->gsi);
पूर्ण

/* Configure bus access behavior क्रम IPA components */
अटल व्योम ipa_hardware_config_comp(काष्ठा ipa *ipa)
अणु
	u32 val;

	/* Nothing to configure prior to IPA v4.0 */
	अगर (ipa->version < IPA_VERSION_4_0)
		वापस;

	val = ioपढ़ो32(ipa->reg_virt + IPA_REG_COMP_CFG_OFFSET);

	अगर (ipa->version == IPA_VERSION_4_0) अणु
		val &= ~IPA_QMB_SELECT_CONS_EN_FMASK;
		val &= ~IPA_QMB_SELECT_PROD_EN_FMASK;
		val &= ~IPA_QMB_SELECT_GLOBAL_EN_FMASK;
	पूर्ण अन्यथा अगर (ipa->version < IPA_VERSION_4_5) अणु
		val |= GSI_MULTI_AXI_MASTERS_DIS_FMASK;
	पूर्ण अन्यथा अणु
		/* For IPA v4.5 IPA_FULL_FLUSH_WAIT_RSC_CLOSE_EN is 0 */
	पूर्ण

	val |= GSI_MULTI_INORDER_RD_DIS_FMASK;
	val |= GSI_MULTI_INORDER_WR_DIS_FMASK;

	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_COMP_CFG_OFFSET);
पूर्ण

/* Configure DDR and (possibly) PCIe max पढ़ो/ग_लिखो QSB values */
अटल व्योम
ipa_hardware_config_qsb(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_data *data)
अणु
	स्थिर काष्ठा ipa_qsb_data *data0;
	स्थिर काष्ठा ipa_qsb_data *data1;
	u32 val;

	/* निश्चित(data->qsb_count > 0); */
	/* निश्चित(data->qsb_count < 3); */

	/* QMB 0 represents DDR; QMB 1 (अगर present) represents PCIe */
	data0 = &data->qsb_data[IPA_QSB_MASTER_DDR];
	अगर (data->qsb_count > 1)
		data1 = &data->qsb_data[IPA_QSB_MASTER_PCIE];

	/* Max outstanding ग_लिखो accesses क्रम QSB masters */
	val = u32_encode_bits(data0->max_ग_लिखोs, GEN_QMB_0_MAX_WRITES_FMASK);
	अगर (data->qsb_count > 1)
		val |= u32_encode_bits(data1->max_ग_लिखोs,
				       GEN_QMB_1_MAX_WRITES_FMASK);
	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_QSB_MAX_WRITES_OFFSET);

	/* Max outstanding पढ़ो accesses क्रम QSB masters */
	val = u32_encode_bits(data0->max_पढ़ोs, GEN_QMB_0_MAX_READS_FMASK);
	अगर (ipa->version >= IPA_VERSION_4_0)
		val |= u32_encode_bits(data0->max_पढ़ोs_beats,
				       GEN_QMB_0_MAX_READS_BEATS_FMASK);
	अगर (data->qsb_count > 1) अणु
		val |= u32_encode_bits(data1->max_पढ़ोs,
				       GEN_QMB_1_MAX_READS_FMASK);
		अगर (ipa->version >= IPA_VERSION_4_0)
			val |= u32_encode_bits(data1->max_पढ़ोs_beats,
					       GEN_QMB_1_MAX_READS_BEATS_FMASK);
	पूर्ण
	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_QSB_MAX_READS_OFFSET);
पूर्ण

/* The पूर्णांकernal inactivity समयr घड़ी is used क्रम the aggregation समयr */
#घोषणा TIMER_FREQUENCY	32000		/* 32 KHz inactivity समयr घड़ी */

/* Compute the value to use in the COUNTER_CFG रेजिस्टर AGGR_GRANULARITY
 * field to represent the given number of microseconds.  The value is one
 * less than the number of समयr ticks in the requested period.  0 is not
 * a valid granularity value.
 */
अटल u32 ipa_aggr_granularity_val(u32 usec)
अणु
	/* निश्चित(usec != 0); */

	वापस DIV_ROUND_CLOSEST(usec * TIMER_FREQUENCY, USEC_PER_SEC) - 1;
पूर्ण

/* IPA uses unअगरied Qसमय starting at IPA v4.5, implementing various
 * बारtamps and समयrs independent of the IPA core घड़ी rate.  The
 * Qसमयr is based on a 56-bit बारtamp incremented at each tick of
 * a 19.2 MHz SoC crystal oscillator (XO घड़ी).
 *
 * For IPA बारtamps (tag, NAT, data path logging) a lower resolution
 * बारtamp is achieved by shअगरting the Qसमयr बारtamp value right
 * some number of bits to produce the low-order bits of the coarser
 * granularity बारtamp.
 *
 * For समयrs, a common समयr घड़ी is derived from the XO घड़ी using
 * a भागider (we use 192, to produce a 100kHz समयr घड़ी).  From
 * this common घड़ी, three "pulse generators" are used to produce
 * समयr ticks at a configurable frequency.  IPA समयrs (such as
 * those used क्रम aggregation or head-of-line block handling) now
 * define their period based on one of these pulse generators.
 */
अटल व्योम ipa_qसमय_config(काष्ठा ipa *ipa)
अणु
	u32 val;

	/* Timer घड़ी भागider must be disabled when we change the rate */
	ioग_लिखो32(0, ipa->reg_virt + IPA_REG_TIMERS_XO_CLK_DIV_CFG_OFFSET);

	/* Set DPL समय stamp resolution to use Qसमय (instead of 1 msec) */
	val = u32_encode_bits(DPL_TIMESTAMP_SHIFT, DPL_TIMESTAMP_LSB_FMASK);
	val |= u32_encode_bits(1, DPL_TIMESTAMP_SEL_FMASK);
	/* Configure tag and NAT Qसमय बारtamp resolution as well */
	val |= u32_encode_bits(TAG_TIMESTAMP_SHIFT, TAG_TIMESTAMP_LSB_FMASK);
	val |= u32_encode_bits(NAT_TIMESTAMP_SHIFT, NAT_TIMESTAMP_LSB_FMASK);
	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_QTIME_TIMESTAMP_CFG_OFFSET);

	/* Set granularity of pulse generators used क्रम other समयrs */
	val = u32_encode_bits(IPA_GRAN_100_US, GRAN_0_FMASK);
	val |= u32_encode_bits(IPA_GRAN_1_MS, GRAN_1_FMASK);
	val |= u32_encode_bits(IPA_GRAN_1_MS, GRAN_2_FMASK);
	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_TIMERS_PULSE_GRAN_CFG_OFFSET);

	/* Actual भागider is 1 more than value supplied here */
	val = u32_encode_bits(IPA_XO_CLOCK_DIVIDER - 1, DIV_VALUE_FMASK);
	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_TIMERS_XO_CLK_DIV_CFG_OFFSET);

	/* Divider value is set; re-enable the common समयr घड़ी भागider */
	val |= u32_encode_bits(1, DIV_ENABLE_FMASK);
	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_TIMERS_XO_CLK_DIV_CFG_OFFSET);
पूर्ण

अटल व्योम ipa_idle_indication_cfg(काष्ठा ipa *ipa,
				    u32 enter_idle_debounce_thresh,
				    bool स्थिर_non_idle_enable)
अणु
	u32 offset;
	u32 val;

	val = u32_encode_bits(enter_idle_debounce_thresh,
			      ENTER_IDLE_DEBOUNCE_THRESH_FMASK);
	अगर (स्थिर_non_idle_enable)
		val |= CONST_NON_IDLE_ENABLE_FMASK;

	offset = ipa_reg_idle_indication_cfg_offset(ipa->version);
	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

/**
 * ipa_hardware_dcd_config() - Enable dynamic घड़ी भागision on IPA
 * @ipa:	IPA poपूर्णांकer
 *
 * Configures when the IPA संकेतs it is idle to the global घड़ी
 * controller, which can respond by scalling करोwn the घड़ी to
 * save घातer.
 */
अटल व्योम ipa_hardware_dcd_config(काष्ठा ipa *ipa)
अणु
	/* Recommended values क्रम IPA 3.5 and later according to IPA HPG */
	ipa_idle_indication_cfg(ipa, 256, false);
पूर्ण

अटल व्योम ipa_hardware_dcd_deconfig(काष्ठा ipa *ipa)
अणु
	/* Power-on reset values */
	ipa_idle_indication_cfg(ipa, 0, true);
पूर्ण

/**
 * ipa_hardware_config() - Primitive hardware initialization
 * @ipa:	IPA poपूर्णांकer
 * @data:	IPA configuration data
 */
अटल व्योम ipa_hardware_config(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_data *data)
अणु
	क्रमागत ipa_version version = ipa->version;
	u32 granularity;
	u32 val;

	/* IPA v4.5+ has no backward compatibility रेजिस्टर */
	अगर (version < IPA_VERSION_4_5) अणु
		val = data->backward_compat;
		ioग_लिखो32(val, ipa->reg_virt + IPA_REG_BCR_OFFSET);
	पूर्ण

	/* Implement some hardware workarounds */
	अगर (version >= IPA_VERSION_4_0 && version < IPA_VERSION_4_5) अणु
		/* Enable खोलो global घड़ीs (not needed क्रम IPA v4.5) */
		val = GLOBAL_FMASK;
		val |= GLOBAL_2X_CLK_FMASK;
		ioग_लिखो32(val, ipa->reg_virt + IPA_REG_CLKON_CFG_OFFSET);

		/* Disable PA mask to allow HOLB drop */
		val = ioपढ़ो32(ipa->reg_virt + IPA_REG_TX_CFG_OFFSET);
		val &= ~PA_MASK_EN_FMASK;
		ioग_लिखो32(val, ipa->reg_virt + IPA_REG_TX_CFG_OFFSET);
	पूर्ण

	ipa_hardware_config_comp(ipa);

	/* Configure प्रणाली bus limits */
	ipa_hardware_config_qsb(ipa, data);

	अगर (version < IPA_VERSION_4_5) अणु
		/* Configure aggregation समयr granularity */
		granularity = ipa_aggr_granularity_val(IPA_AGGR_GRANULARITY);
		val = u32_encode_bits(granularity, AGGR_GRANULARITY_FMASK);
		ioग_लिखो32(val, ipa->reg_virt + IPA_REG_COUNTER_CFG_OFFSET);
	पूर्ण अन्यथा अणु
		ipa_qसमय_config(ipa);
	पूर्ण

	/* IPA v4.2 करोes not support hashed tables, so disable them */
	अगर (version == IPA_VERSION_4_2) अणु
		u32 offset = ipa_reg_filt_rout_hash_en_offset(version);

		ioग_लिखो32(0, ipa->reg_virt + offset);
	पूर्ण

	/* Enable dynamic घड़ी भागision */
	ipa_hardware_dcd_config(ipa);
पूर्ण

/**
 * ipa_hardware_deconfig() - Inverse of ipa_hardware_config()
 * @ipa:	IPA poपूर्णांकer
 *
 * This restores the घातer-on reset values (even अगर they aren't dअगरferent)
 */
अटल व्योम ipa_hardware_deconfig(काष्ठा ipa *ipa)
अणु
	/* Mostly we just leave things as we set them. */
	ipa_hardware_dcd_deconfig(ipa);
पूर्ण

/**
 * ipa_config() - Configure IPA hardware
 * @ipa:	IPA poपूर्णांकer
 * @data:	IPA configuration data
 *
 * Perक्रमm initialization requiring IPA घड़ी to be enabled.
 */
अटल पूर्णांक ipa_config(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_data *data)
अणु
	पूर्णांक ret;

	/* Get a घड़ी reference to allow initialization.  This reference
	 * is held after initialization completes, and won't get dropped
	 * unless/until a प्रणाली suspend request arrives.
	 */
	ipa_घड़ी_get(ipa);

	ipa_hardware_config(ipa, data);

	ret = ipa_endpoपूर्णांक_config(ipa);
	अगर (ret)
		जाओ err_hardware_deconfig;

	ret = ipa_mem_config(ipa);
	अगर (ret)
		जाओ err_endpoपूर्णांक_deconfig;

	ipa_table_config(ipa);		/* No deconfig required */

	/* Assign resource limitation to each group; no deconfig required */
	ret = ipa_resource_config(ipa, data->resource_data);
	अगर (ret)
		जाओ err_mem_deconfig;

	ret = ipa_modem_config(ipa);
	अगर (ret)
		जाओ err_mem_deconfig;

	वापस 0;

err_mem_deconfig:
	ipa_mem_deconfig(ipa);
err_endpoपूर्णांक_deconfig:
	ipa_endpoपूर्णांक_deconfig(ipa);
err_hardware_deconfig:
	ipa_hardware_deconfig(ipa);
	ipa_घड़ी_put(ipa);

	वापस ret;
पूर्ण

/**
 * ipa_deconfig() - Inverse of ipa_config()
 * @ipa:	IPA poपूर्णांकer
 */
अटल व्योम ipa_deconfig(काष्ठा ipa *ipa)
अणु
	ipa_modem_deconfig(ipa);
	ipa_mem_deconfig(ipa);
	ipa_endpoपूर्णांक_deconfig(ipa);
	ipa_hardware_deconfig(ipa);
	ipa_घड़ी_put(ipa);
पूर्ण

अटल पूर्णांक ipa_firmware_load(काष्ठा device *dev)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा device_node *node;
	काष्ठा resource res;
	phys_addr_t phys;
	स्थिर अक्षर *path;
	sमाप_प्रकार size;
	व्योम *virt;
	पूर्णांक ret;

	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	अगर (!node) अणु
		dev_err(dev, "DT error getting \"memory-region\" property\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret) अणु
		dev_err(dev, "error %d getting \"memory-region\" resource\n",
			ret);
		वापस ret;
	पूर्ण

	/* Use name from DTB अगर specअगरied; use शेष क्रम *any* error */
	ret = of_property_पढ़ो_string(dev->of_node, "firmware-name", &path);
	अगर (ret) अणु
		dev_dbg(dev, "error %d getting \"firmware-name\" resource\n",
			ret);
		path = IPA_FW_PATH_DEFAULT;
	पूर्ण

	ret = request_firmware(&fw, path, dev);
	अगर (ret) अणु
		dev_err(dev, "error %d requesting \"%s\"\n", ret, path);
		वापस ret;
	पूर्ण

	phys = res.start;
	size = (माप_प्रकार)resource_size(&res);
	virt = memremap(phys, size, MEMREMAP_WC);
	अगर (!virt) अणु
		dev_err(dev, "unable to remap firmware memory\n");
		ret = -ENOMEM;
		जाओ out_release_firmware;
	पूर्ण

	ret = qcom_mdt_load(dev, fw, path, IPA_PAS_ID, virt, phys, size, शून्य);
	अगर (ret)
		dev_err(dev, "error %d loading \"%s\"\n", ret, path);
	अन्यथा अगर ((ret = qcom_scm_pas_auth_and_reset(IPA_PAS_ID)))
		dev_err(dev, "error %d authenticating \"%s\"\n", ret, path);

	memunmap(virt);
out_release_firmware:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id ipa_match[] = अणु
	अणु
		.compatible	= "qcom,sdm845-ipa",
		.data		= &ipa_data_v3_5_1,
	पूर्ण,
	अणु
		.compatible	= "qcom,sc7180-ipa",
		.data		= &ipa_data_v4_2,
	पूर्ण,
	अणु
		.compatible	= "qcom,sdx55-ipa",
		.data		= &ipa_data_v4_5,
	पूर्ण,
	अणु
		.compatible	= "qcom,sm8350-ipa",
		.data		= &ipa_data_v4_9,
	पूर्ण,
	अणु
		.compatible	= "qcom,sc7280-ipa",
		.data		= &ipa_data_v4_11,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ipa_match);

/* Check things that can be validated at build समय.  This just
 * groups these things BUILD_BUG_ON() calls करोn't clutter the rest
 * of the code.
 * */
अटल व्योम ipa_validate_build(व्योम)
अणु
#अगर_घोषित IPA_VALIDATE
	/* At one समय we assumed a 64-bit build, allowing some करो_भाग()
	 * calls to be replaced by simple भागision or modulo operations.
	 * We currently only perक्रमm भागide and modulo operations on u32,
	 * u16, or माप_प्रकार objects, and of those only माप_प्रकार has any chance
	 * of being a 64-bit value.  (It should be guaranteed 32 bits wide
	 * on a 32-bit build, but there is no harm in verअगरying that.)
	 */
	BUILD_BUG_ON(!IS_ENABLED(CONFIG_64BIT) && माप(माप_प्रकार) != 4);

	/* Code assumes the EE ID क्रम the AP is 0 (zeroed काष्ठाure field) */
	BUILD_BUG_ON(GSI_EE_AP != 0);

	/* There's no poपूर्णांक अगर we have no channels or event rings */
	BUILD_BUG_ON(!GSI_CHANNEL_COUNT_MAX);
	BUILD_BUG_ON(!GSI_EVT_RING_COUNT_MAX);

	/* GSI hardware design limits */
	BUILD_BUG_ON(GSI_CHANNEL_COUNT_MAX > 32);
	BUILD_BUG_ON(GSI_EVT_RING_COUNT_MAX > 31);

	/* The number of TREs in a transaction is limited by the channel's
	 * TLV FIFO size.  A transaction काष्ठाure uses 8-bit fields
	 * to represents the number of TREs it has allocated and used.
	 */
	BUILD_BUG_ON(GSI_TLV_MAX > U8_MAX);

	/* This is used as a भागisor */
	BUILD_BUG_ON(!IPA_AGGR_GRANULARITY);

	/* Aggregation granularity value can't be 0, and must fit */
	BUILD_BUG_ON(!ipa_aggr_granularity_val(IPA_AGGR_GRANULARITY));
	BUILD_BUG_ON(ipa_aggr_granularity_val(IPA_AGGR_GRANULARITY) >
			field_max(AGGR_GRANULARITY_FMASK));
#पूर्ण_अगर /* IPA_VALIDATE */
पूर्ण

/**
 * ipa_probe() - IPA platक्रमm driver probe function
 * @pdev:	Platक्रमm device poपूर्णांकer
 *
 * Return:	0 अगर successful, or a negative error code (possibly
 *		EPROBE_DEFER)
 *
 * This is the मुख्य entry poपूर्णांक क्रम the IPA driver.  Initialization proceeds
 * in several stages:
 *   - The "init" stage involves activities that can be initialized without
 *     access to the IPA hardware.
 *   - The "config" stage requires the IPA घड़ी to be active so IPA रेजिस्टरs
 *     can be accessed, but करोes not require the use of IPA immediate commands.
 *   - The "setup" stage uses IPA immediate commands, and so requires the GSI
 *     layer to be initialized.
 *
 * A Boolean Device Tree "modem-init" property determines whether GSI
 * initialization will be perक्रमmed by the AP (Trust Zone) or the modem.
 * If the AP करोes GSI initialization, the setup phase is entered after
 * this has completed successfully.  Otherwise the modem initializes
 * the GSI layer and संकेतs it has finished by sending an SMP2P पूर्णांकerrupt
 * to the AP; this triggers the start अगर IPA setup.
 */
अटल पूर्णांक ipa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा ipa_data *data;
	काष्ठा ipa_घड़ी *घड़ी;
	bool modem_init;
	काष्ठा ipa *ipa;
	पूर्णांक ret;

	ipa_validate_build();

	/* Get configuration data early; needed क्रम घड़ी initialization */
	data = of_device_get_match_data(dev);
	अगर (!data) अणु
		/* This is really IPA_VALIDATE (should never happen) */
		dev_err(dev, "matched hardware not supported\n");
		वापस -ENODEV;
	पूर्ण

	/* If we need Trust Zone, make sure it's available */
	modem_init = of_property_पढ़ो_bool(dev->of_node, "modem-init");
	अगर (!modem_init)
		अगर (!qcom_scm_is_available())
			वापस -EPROBE_DEFER;

	/* The घड़ी and पूर्णांकerconnects might not be पढ़ोy when we're
	 * probed, so might वापस -EPROBE_DEFER.
	 */
	घड़ी = ipa_घड़ी_init(dev, data->घड़ी_data);
	अगर (IS_ERR(घड़ी))
		वापस PTR_ERR(घड़ी);

	/* No more EPROBE_DEFER.  Allocate and initialize the IPA काष्ठाure */
	ipa = kzalloc(माप(*ipa), GFP_KERNEL);
	अगर (!ipa) अणु
		ret = -ENOMEM;
		जाओ err_घड़ी_निकास;
	पूर्ण

	ipa->pdev = pdev;
	dev_set_drvdata(dev, ipa);
	ipa->घड़ी = घड़ी;
	ipa->version = data->version;
	init_completion(&ipa->completion);

	ret = ipa_reg_init(ipa);
	अगर (ret)
		जाओ err_kमुक्त_ipa;

	ret = ipa_mem_init(ipa, data->mem_data);
	अगर (ret)
		जाओ err_reg_निकास;

	ret = gsi_init(&ipa->gsi, pdev, ipa->version, data->endpoपूर्णांक_count,
		       data->endpoपूर्णांक_data);
	अगर (ret)
		जाओ err_mem_निकास;

	/* Result is a non-zero mask of endpoपूर्णांकs that support filtering */
	ipa->filter_map = ipa_endpoपूर्णांक_init(ipa, data->endpoपूर्णांक_count,
					    data->endpoपूर्णांक_data);
	अगर (!ipa->filter_map) अणु
		ret = -EINVAL;
		जाओ err_gsi_निकास;
	पूर्ण

	ret = ipa_table_init(ipa);
	अगर (ret)
		जाओ err_endpoपूर्णांक_निकास;

	ret = ipa_modem_init(ipa, modem_init);
	अगर (ret)
		जाओ err_table_निकास;

	ret = ipa_config(ipa, data);
	अगर (ret)
		जाओ err_modem_निकास;

	dev_info(dev, "IPA driver initialized");

	/* If the modem is करोing early initialization, it will trigger a
	 * call to ipa_setup() call when it has finished.  In that हाल
	 * we're करोne here.
	 */
	अगर (modem_init)
		वापस 0;

	/* Otherwise we need to load the firmware and have Trust Zone validate
	 * and install it.  If that succeeds we can proceed with setup.
	 */
	ret = ipa_firmware_load(dev);
	अगर (ret)
		जाओ err_deconfig;

	ret = ipa_setup(ipa);
	अगर (ret)
		जाओ err_deconfig;

	वापस 0;

err_deconfig:
	ipa_deconfig(ipa);
err_modem_निकास:
	ipa_modem_निकास(ipa);
err_table_निकास:
	ipa_table_निकास(ipa);
err_endpoपूर्णांक_निकास:
	ipa_endpoपूर्णांक_निकास(ipa);
err_gsi_निकास:
	gsi_निकास(&ipa->gsi);
err_mem_निकास:
	ipa_mem_निकास(ipa);
err_reg_निकास:
	ipa_reg_निकास(ipa);
err_kमुक्त_ipa:
	kमुक्त(ipa);
err_घड़ी_निकास:
	ipa_घड़ी_निकास(घड़ी);

	वापस ret;
पूर्ण

अटल पूर्णांक ipa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipa *ipa = dev_get_drvdata(&pdev->dev);
	काष्ठा ipa_घड़ी *घड़ी = ipa->घड़ी;
	पूर्णांक ret;

	अगर (ipa->setup_complete) अणु
		ret = ipa_modem_stop(ipa);
		/* If starting or stopping is in progress, try once more */
		अगर (ret == -EBUSY) अणु
			usleep_range(USEC_PER_MSEC, 2 * USEC_PER_MSEC);
			ret = ipa_modem_stop(ipa);
		पूर्ण
		अगर (ret)
			वापस ret;

		ipa_tearकरोwn(ipa);
	पूर्ण

	ipa_deconfig(ipa);
	ipa_modem_निकास(ipa);
	ipa_table_निकास(ipa);
	ipa_endpoपूर्णांक_निकास(ipa);
	gsi_निकास(&ipa->gsi);
	ipa_mem_निकास(ipa);
	ipa_reg_निकास(ipa);
	kमुक्त(ipa);
	ipa_घड़ी_निकास(घड़ी);

	वापस 0;
पूर्ण

अटल व्योम ipa_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = ipa_हटाओ(pdev);
	अगर (ret)
		dev_err(&pdev->dev, "shutdown: remove returned %d\n", ret);
पूर्ण

/**
 * ipa_suspend() - Power management प्रणाली suspend callback
 * @dev:	IPA device काष्ठाure
 *
 * Return:	Always वापसs zero
 *
 * Called by the PM framework when a प्रणाली suspend operation is invoked.
 * Suspends endpoपूर्णांकs and releases the घड़ी reference held to keep
 * the IPA घड़ी running until this poपूर्णांक.
 */
अटल पूर्णांक ipa_suspend(काष्ठा device *dev)
अणु
	काष्ठा ipa *ipa = dev_get_drvdata(dev);

	/* When a suspended RX endpoपूर्णांक has a packet पढ़ोy to receive, we
	 * get an IPA SUSPEND पूर्णांकerrupt.  We trigger a प्रणाली resume in
	 * that हाल, but only on the first such पूर्णांकerrupt since suspend.
	 */
	__clear_bit(IPA_FLAG_RESUMED, ipa->flags);

	ipa_endpoपूर्णांक_suspend(ipa);

	ipa_घड़ी_put(ipa);

	वापस 0;
पूर्ण

/**
 * ipa_resume() - Power management प्रणाली resume callback
 * @dev:	IPA device काष्ठाure
 *
 * Return:	Always वापसs 0
 *
 * Called by the PM framework when a प्रणाली resume operation is invoked.
 * Takes an IPA घड़ी reference to keep the घड़ी running until suspend,
 * and resumes endpoपूर्णांकs.
 */
अटल पूर्णांक ipa_resume(काष्ठा device *dev)
अणु
	काष्ठा ipa *ipa = dev_get_drvdata(dev);

	/* This घड़ी reference will keep the IPA out of suspend
	 * until we get a घातer management suspend request.
	 */
	ipa_घड़ी_get(ipa);

	ipa_endpoपूर्णांक_resume(ipa);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ipa_pm_ops = अणु
	.suspend	= ipa_suspend,
	.resume		= ipa_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver ipa_driver = अणु
	.probe		= ipa_probe,
	.हटाओ		= ipa_हटाओ,
	.shutकरोwn	= ipa_shutकरोwn,
	.driver	= अणु
		.name		= "ipa",
		.pm		= &ipa_pm_ops,
		.of_match_table	= ipa_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ipa_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm IP Accelerator device driver");
