<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2+ common Clock Management (CM) IP block functions
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 *
 * XXX This code should eventually be moved to a CM driver.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "cm2xxx.h"
#समावेश "cm3xxx.h"
#समावेश "cm33xx.h"
#समावेश "cm44xx.h"
#समावेश "clock.h"

/*
 * cm_ll_data: function poपूर्णांकers to SoC-specअगरic implementations of
 * common CM functions
 */
अटल काष्ठा cm_ll_data null_cm_ll_data;
अटल स्थिर काष्ठा cm_ll_data *cm_ll_data = &null_cm_ll_data;

/* cm_base: base भव address of the CM IP block */
काष्ठा omap_करोमुख्य_base cm_base;

/* cm2_base: base भव address of the CM2 IP block (OMAP44xx only) */
काष्ठा omap_करोमुख्य_base cm2_base;

#घोषणा CM_NO_CLOCKS		0x1
#घोषणा CM_SINGLE_INSTANCE	0x2

/**
 * omap2_set_globals_cm - set the CM/CM2 base addresses (क्रम early use)
 * @cm: CM base भव address
 * @cm2: CM2 base भव address (अगर present on the booted SoC)
 *
 * XXX Will be replaced when the PRM/CM drivers are completed.
 */
व्योम __init omap2_set_globals_cm(व्योम __iomem *cm, व्योम __iomem *cm2)
अणु
	cm_base.va = cm;
	cm2_base.va = cm2;
पूर्ण

/**
 * cm_split_idlest_reg - split CM_IDLEST reg addr पूर्णांकo its components
 * @idlest_reg: CM_IDLEST* भव address
 * @prcm_inst: poपूर्णांकer to an s16 to वापस the PRCM instance offset
 * @idlest_reg_id: poपूर्णांकer to a u8 to वापस the CM_IDLESTx रेजिस्टर ID
 *
 * Given an असलolute CM_IDLEST रेजिस्टर address @idlest_reg, passes
 * the PRCM instance offset and IDLEST रेजिस्टर ID back to the caller
 * via the @prcm_inst and @idlest_reg_id.  Returns -EINVAL upon error,
 * or 0 upon success.  XXX This function is only needed until असलolute
 * रेजिस्टर addresses are हटाओd from the OMAP काष्ठा clk records.
 */
पूर्णांक cm_split_idlest_reg(काष्ठा clk_omap_reg *idlest_reg, s16 *prcm_inst,
			u8 *idlest_reg_id)
अणु
	पूर्णांक ret;
	अगर (!cm_ll_data->split_idlest_reg) अणु
		WARN_ONCE(1, "cm: %s: no low-level function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	ret = cm_ll_data->split_idlest_reg(idlest_reg, prcm_inst,
					   idlest_reg_id);
	*prcm_inst -= cm_base.offset;
	वापस ret;
पूर्ण

/**
 * omap_cm_रुको_module_पढ़ोy - रुको क्रम a module to leave idle or standby
 * @part: PRCM partition
 * @prcm_mod: PRCM module offset
 * @idlest_reg: CM_IDLESTx रेजिस्टर
 * @idlest_shअगरt: shअगरt of the bit in the CM_IDLEST* रेजिस्टर to check
 *
 * Wait क्रम the PRCM to indicate that the module identअगरied by
 * (@prcm_mod, @idlest_id, @idlest_shअगरt) is घड़ीed.  Return 0 upon
 * success, -EBUSY अगर the module करोesn't enable in समय, or -EINVAL अगर
 * no per-SoC रुको_module_पढ़ोy() function poपूर्णांकer has been रेजिस्टरed
 * or अगर the idlest रेजिस्टर is unknown on the SoC.
 */
पूर्णांक omap_cm_रुको_module_पढ़ोy(u8 part, s16 prcm_mod, u16 idlest_reg,
			      u8 idlest_shअगरt)
अणु
	अगर (!cm_ll_data->रुको_module_पढ़ोy) अणु
		WARN_ONCE(1, "cm: %s: no low-level function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	वापस cm_ll_data->रुको_module_पढ़ोy(part, prcm_mod, idlest_reg,
					     idlest_shअगरt);
पूर्ण

/**
 * omap_cm_रुको_module_idle - रुको क्रम a module to enter idle or standby
 * @part: PRCM partition
 * @prcm_mod: PRCM module offset
 * @idlest_reg: CM_IDLESTx रेजिस्टर
 * @idlest_shअगरt: shअगरt of the bit in the CM_IDLEST* रेजिस्टर to check
 *
 * Wait क्रम the PRCM to indicate that the module identअगरied by
 * (@prcm_mod, @idlest_id, @idlest_shअगरt) is no दीर्घer घड़ीed.  Return
 * 0 upon success, -EBUSY अगर the module करोesn't enable in समय, or
 * -EINVAL अगर no per-SoC रुको_module_idle() function poपूर्णांकer has been
 * रेजिस्टरed or अगर the idlest रेजिस्टर is unknown on the SoC.
 */
पूर्णांक omap_cm_रुको_module_idle(u8 part, s16 prcm_mod, u16 idlest_reg,
			     u8 idlest_shअगरt)
अणु
	अगर (!cm_ll_data->रुको_module_idle) अणु
		WARN_ONCE(1, "cm: %s: no low-level function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	वापस cm_ll_data->रुको_module_idle(part, prcm_mod, idlest_reg,
					    idlest_shअगरt);
पूर्ण

/**
 * omap_cm_module_enable - enable a module
 * @mode: target mode क्रम the module
 * @part: PRCM partition
 * @inst: PRCM instance
 * @clkctrl_offs: CM_CLKCTRL रेजिस्टर offset क्रम the module
 *
 * Enables घड़ीs क्रम a module identअगरied by (@part, @inst, @clkctrl_offs)
 * making its IO space accessible. Return 0 upon success, -EINVAL अगर no
 * per-SoC module_enable() function poपूर्णांकer has been रेजिस्टरed.
 */
पूर्णांक omap_cm_module_enable(u8 mode, u8 part, u16 inst, u16 clkctrl_offs)
अणु
	अगर (!cm_ll_data->module_enable) अणु
		WARN_ONCE(1, "cm: %s: no low-level function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	cm_ll_data->module_enable(mode, part, inst, clkctrl_offs);
	वापस 0;
पूर्ण

/**
 * omap_cm_module_disable - disable a module
 * @part: PRCM partition
 * @inst: PRCM instance
 * @clkctrl_offs: CM_CLKCTRL रेजिस्टर offset क्रम the module
 *
 * Disables घड़ीs क्रम a module identअगरied by (@part, @inst, @clkctrl_offs)
 * makings its IO space inaccessible. Return 0 upon success, -EINVAL अगर
 * no per-SoC module_disable() function poपूर्णांकer has been रेजिस्टरed.
 */
पूर्णांक omap_cm_module_disable(u8 part, u16 inst, u16 clkctrl_offs)
अणु
	अगर (!cm_ll_data->module_disable) अणु
		WARN_ONCE(1, "cm: %s: no low-level function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	cm_ll_data->module_disable(part, inst, clkctrl_offs);
	वापस 0;
पूर्ण

u32 omap_cm_xlate_clkctrl(u8 part, u16 inst, u16 clkctrl_offs)
अणु
	अगर (!cm_ll_data->xlate_clkctrl) अणु
		WARN_ONCE(1, "cm: %s: no low-level function defined\n",
			  __func__);
		वापस 0;
	पूर्ण
	वापस cm_ll_data->xlate_clkctrl(part, inst, clkctrl_offs);
पूर्ण

/**
 * cm_रेजिस्टर - रेजिस्टर per-SoC low-level data with the CM
 * @cld: low-level per-SoC OMAP CM data & function poपूर्णांकers to रेजिस्टर
 *
 * Register per-SoC low-level OMAP CM data and function poपूर्णांकers with
 * the OMAP CM common पूर्णांकerface.  The caller must keep the data
 * poपूर्णांकed to by @cld valid until it calls cm_unरेजिस्टर() and
 * it वापसs successfully.  Returns 0 upon success, -EINVAL अगर @cld
 * is शून्य, or -EEXIST अगर cm_रेजिस्टर() has alपढ़ोy been called
 * without an पूर्णांकervening cm_unरेजिस्टर().
 */
पूर्णांक cm_रेजिस्टर(स्थिर काष्ठा cm_ll_data *cld)
अणु
	अगर (!cld)
		वापस -EINVAL;

	अगर (cm_ll_data != &null_cm_ll_data)
		वापस -EEXIST;

	cm_ll_data = cld;

	वापस 0;
पूर्ण

/**
 * cm_unरेजिस्टर - unरेजिस्टर per-SoC low-level data & function poपूर्णांकers
 * @cld: low-level per-SoC OMAP CM data & function poपूर्णांकers to unरेजिस्टर
 *
 * Unरेजिस्टर per-SoC low-level OMAP CM data and function poपूर्णांकers
 * that were previously रेजिस्टरed with cm_रेजिस्टर().  The
 * caller may not destroy any of the data poपूर्णांकed to by @cld until
 * this function वापसs successfully.  Returns 0 upon success, or
 * -EINVAL अगर @cld is शून्य or अगर @cld करोes not match the काष्ठा
 * cm_ll_data * previously रेजिस्टरed by cm_रेजिस्टर().
 */
पूर्णांक cm_unरेजिस्टर(स्थिर काष्ठा cm_ll_data *cld)
अणु
	अगर (!cld || cm_ll_data != cld)
		वापस -EINVAL;

	cm_ll_data = &null_cm_ll_data;

	वापस 0;
पूर्ण

#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DRA7XX)
अटल काष्ठा omap_prcm_init_data cm_data __initdata = अणु
	.index = TI_CLKM_CM,
	.init = omap4_cm_init,
पूर्ण;

अटल काष्ठा omap_prcm_init_data cm2_data __initdata = अणु
	.index = TI_CLKM_CM2,
	.init = omap4_cm_init,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP2
अटल काष्ठा omap_prcm_init_data omap2_prcm_data __initdata = अणु
	.index = TI_CLKM_CM,
	.init = omap2xxx_cm_init,
	.flags = CM_NO_CLOCKS | CM_SINGLE_INSTANCE,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
अटल काष्ठा omap_prcm_init_data omap3_cm_data __initdata = अणु
	.index = TI_CLKM_CM,
	.init = omap3xxx_cm_init,
	.flags = CM_SINGLE_INSTANCE,

	/*
	 * IVA2 offset is a negative value, must offset the cm_base address
	 * by this to get it to positive side on the iomap
	 */
	.offset = -OMAP3430_IVA2_MOD,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_TI81XX)
अटल काष्ठा omap_prcm_init_data am3_prcm_data __initdata = अणु
	.index = TI_CLKM_CM,
	.flags = CM_NO_CLOCKS | CM_SINGLE_INSTANCE,
	.init = am33xx_cm_init,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_AM43XX
अटल काष्ठा omap_prcm_init_data am4_prcm_data __initdata = अणु
	.index = TI_CLKM_CM,
	.flags = CM_NO_CLOCKS | CM_SINGLE_INSTANCE,
	.init = omap4_cm_init,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id omap_cm_dt_match_table[] __initस्थिर = अणु
#अगर_घोषित CONFIG_ARCH_OMAP2
	अणु .compatible = "ti,omap2-prcm", .data = &omap2_prcm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP3
	अणु .compatible = "ti,omap3-cm", .data = &omap3_cm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP4
	अणु .compatible = "ti,omap4-cm1", .data = &cm_data पूर्ण,
	अणु .compatible = "ti,omap4-cm2", .data = &cm2_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_OMAP5
	अणु .compatible = "ti,omap5-cm-core-aon", .data = &cm_data पूर्ण,
	अणु .compatible = "ti,omap5-cm-core", .data = &cm2_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_DRA7XX
	अणु .compatible = "ti,dra7-cm-core-aon", .data = &cm_data पूर्ण,
	अणु .compatible = "ti,dra7-cm-core", .data = &cm2_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_AM33XX
	अणु .compatible = "ti,am3-prcm", .data = &am3_prcm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_AM43XX
	अणु .compatible = "ti,am4-prcm", .data = &am4_prcm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_TI81XX
	अणु .compatible = "ti,dm814-prcm", .data = &am3_prcm_data पूर्ण,
	अणु .compatible = "ti,dm816-prcm", .data = &am3_prcm_data पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

/**
 * omap2_cm_base_init - initialize iomappings क्रम the CM drivers
 *
 * Detects and initializes the iomappings क्रम the CM driver, based
 * on the DT data. Returns 0 in success, negative error value
 * otherwise.
 */
पूर्णांक __init omap2_cm_base_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा omap_prcm_init_data *data;
	काष्ठा resource res;
	पूर्णांक ret;
	काष्ठा omap_करोमुख्य_base *mem = शून्य;

	क्रम_each_matching_node_and_match(np, omap_cm_dt_match_table, &match) अणु
		data = (काष्ठा omap_prcm_init_data *)match->data;

		ret = of_address_to_resource(np, 0, &res);
		अगर (ret)
			वापस ret;

		अगर (data->index == TI_CLKM_CM)
			mem = &cm_base;

		अगर (data->index == TI_CLKM_CM2)
			mem = &cm2_base;

		data->mem = ioremap(res.start, resource_size(&res));

		अगर (mem) अणु
			mem->pa = res.start + data->offset;
			mem->va = data->mem + data->offset;
			mem->offset = data->offset;
		पूर्ण

		data->np = np;

		अगर (data->init && (data->flags & CM_SINGLE_INSTANCE ||
				   (cm_base.va && cm2_base.va)))
			data->init(data);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap_cm_init - low level init क्रम the CM drivers
 *
 * Initializes the low level घड़ी infraकाष्ठाure क्रम CM drivers.
 * Returns 0 in success, negative error value in failure.
 */
पूर्णांक __init omap_cm_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा omap_prcm_init_data *data;
	पूर्णांक ret;

	क्रम_each_matching_node_and_match(np, omap_cm_dt_match_table, &match) अणु
		data = match->data;

		अगर (data->flags & CM_NO_CLOCKS)
			जारी;

		ret = omap2_clk_provider_init(np, data->index, शून्य, data->mem);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
