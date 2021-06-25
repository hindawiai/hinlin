<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ti-sysc.c - Texas Instruments sysc पूर्णांकerconnect target driver
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/iopoll.h>

#समावेश <linux/platक्रमm_data/ti-sysc.h>

#समावेश <dt-bindings/bus/ti-sysc.h>

#घोषणा DIS_ISP		BIT(2)
#घोषणा DIS_IVA		BIT(1)
#घोषणा DIS_SGX		BIT(0)

#घोषणा SOC_FLAG(match, flag)	अणु .machine = match, .data = (व्योम *)(flag), पूर्ण

#घोषणा MAX_MODULE_SOFTRESET_WAIT		10000

क्रमागत sysc_soc अणु
	SOC_UNKNOWN,
	SOC_2420,
	SOC_2430,
	SOC_3430,
	SOC_3630,
	SOC_4430,
	SOC_4460,
	SOC_4470,
	SOC_5430,
	SOC_AM3,
	SOC_AM4,
	SOC_DRA7,
पूर्ण;

काष्ठा sysc_address अणु
	अचिन्हित दीर्घ base;
	काष्ठा list_head node;
पूर्ण;

काष्ठा sysc_soc_info अणु
	अचिन्हित दीर्घ general_purpose:1;
	क्रमागत sysc_soc soc;
	काष्ठा mutex list_lock;			/* disabled modules list lock */
	काष्ठा list_head disabled_modules;
पूर्ण;

क्रमागत sysc_घड़ीs अणु
	SYSC_FCK,
	SYSC_ICK,
	SYSC_OPTFCK0,
	SYSC_OPTFCK1,
	SYSC_OPTFCK2,
	SYSC_OPTFCK3,
	SYSC_OPTFCK4,
	SYSC_OPTFCK5,
	SYSC_OPTFCK6,
	SYSC_OPTFCK7,
	SYSC_MAX_CLOCKS,
पूर्ण;

अटल काष्ठा sysc_soc_info *sysc_soc;
अटल स्थिर अक्षर * स्थिर reg_names[] = अणु "rev", "sysc", "syss", पूर्ण;
अटल स्थिर अक्षर * स्थिर घड़ी_names[SYSC_MAX_CLOCKS] = अणु
	"fck", "ick", "opt0", "opt1", "opt2", "opt3", "opt4",
	"opt5", "opt6", "opt7",
पूर्ण;

#घोषणा SYSC_IDLEMODE_MASK		3
#घोषणा SYSC_CLOCKACTIVITY_MASK		3

/**
 * काष्ठा sysc - TI sysc पूर्णांकerconnect target module रेजिस्टरs and capabilities
 * @dev: काष्ठा device poपूर्णांकer
 * @module_pa: physical address of the पूर्णांकerconnect target module
 * @module_size: size of the पूर्णांकerconnect target module
 * @module_va: भव address of the पूर्णांकerconnect target module
 * @offsets: रेजिस्टर offsets from module base
 * @mdata: ti-sysc to hwmod translation data क्रम a module
 * @घड़ीs: घड़ीs used by the पूर्णांकerconnect target module
 * @घड़ी_roles: घड़ी role names क्रम the found घड़ीs
 * @nr_घड़ीs: number of घड़ीs used by the पूर्णांकerconnect target module
 * @rsts: resets used by the पूर्णांकerconnect target module
 * @legacy_mode: configured क्रम legacy mode अगर set
 * @cap: पूर्णांकerconnect target module capabilities
 * @cfg: पूर्णांकerconnect target module configuration
 * @cookie: data used by legacy platक्रमm callbacks
 * @name: name अगर available
 * @revision: पूर्णांकerconnect target module revision
 * @enabled: sysc runसमय enabled status
 * @needs_resume: runसमय resume needed on resume from suspend
 * @child_needs_resume: runसमय resume needed क्रम child on resume from suspend
 * @disable_on_idle: status flag used क्रम disabling modules with resets
 * @idle_work: work काष्ठाure used to perक्रमm delayed idle on a module
 * @pre_reset_quirk: module specअगरic pre-reset quirk
 * @post_reset_quirk: module specअगरic post-reset quirk
 * @reset_करोne_quirk: module specअगरic reset करोne quirk
 * @module_enable_quirk: module specअगरic enable quirk
 * @module_disable_quirk: module specअगरic disable quirk
 * @module_unlock_quirk: module specअगरic sysconfig unlock quirk
 * @module_lock_quirk: module specअगरic sysconfig lock quirk
 */
काष्ठा sysc अणु
	काष्ठा device *dev;
	u64 module_pa;
	u32 module_size;
	व्योम __iomem *module_va;
	पूर्णांक offsets[SYSC_MAX_REGS];
	काष्ठा ti_sysc_module_data *mdata;
	काष्ठा clk **घड़ीs;
	स्थिर अक्षर **घड़ी_roles;
	पूर्णांक nr_घड़ीs;
	काष्ठा reset_control *rsts;
	स्थिर अक्षर *legacy_mode;
	स्थिर काष्ठा sysc_capabilities *cap;
	काष्ठा sysc_config cfg;
	काष्ठा ti_sysc_cookie cookie;
	स्थिर अक्षर *name;
	u32 revision;
	अचिन्हित पूर्णांक enabled:1;
	अचिन्हित पूर्णांक needs_resume:1;
	अचिन्हित पूर्णांक child_needs_resume:1;
	काष्ठा delayed_work idle_work;
	व्योम (*pre_reset_quirk)(काष्ठा sysc *sysc);
	व्योम (*post_reset_quirk)(काष्ठा sysc *sysc);
	व्योम (*reset_करोne_quirk)(काष्ठा sysc *sysc);
	व्योम (*module_enable_quirk)(काष्ठा sysc *sysc);
	व्योम (*module_disable_quirk)(काष्ठा sysc *sysc);
	व्योम (*module_unlock_quirk)(काष्ठा sysc *sysc);
	व्योम (*module_lock_quirk)(काष्ठा sysc *sysc);
पूर्ण;

अटल व्योम sysc_parse_dts_quirks(काष्ठा sysc *ddata, काष्ठा device_node *np,
				  bool is_child);

अटल व्योम sysc_ग_लिखो(काष्ठा sysc *ddata, पूर्णांक offset, u32 value)
अणु
	अगर (ddata->cfg.quirks & SYSC_QUIRK_16BIT) अणु
		ग_लिखोw_relaxed(value & 0xffff, ddata->module_va + offset);

		/* Only i2c revision has LO and HI रेजिस्टर with stride of 4 */
		अगर (ddata->offsets[SYSC_REVISION] >= 0 &&
		    offset == ddata->offsets[SYSC_REVISION]) अणु
			u16 hi = value >> 16;

			ग_लिखोw_relaxed(hi, ddata->module_va + offset + 4);
		पूर्ण

		वापस;
	पूर्ण

	ग_लिखोl_relaxed(value, ddata->module_va + offset);
पूर्ण

अटल u32 sysc_पढ़ो(काष्ठा sysc *ddata, पूर्णांक offset)
अणु
	अगर (ddata->cfg.quirks & SYSC_QUIRK_16BIT) अणु
		u32 val;

		val = पढ़ोw_relaxed(ddata->module_va + offset);

		/* Only i2c revision has LO and HI रेजिस्टर with stride of 4 */
		अगर (ddata->offsets[SYSC_REVISION] >= 0 &&
		    offset == ddata->offsets[SYSC_REVISION]) अणु
			u16 पंचांगp = पढ़ोw_relaxed(ddata->module_va + offset + 4);

			val |= पंचांगp << 16;
		पूर्ण

		वापस val;
	पूर्ण

	वापस पढ़ोl_relaxed(ddata->module_va + offset);
पूर्ण

अटल bool sysc_opt_clks_needed(काष्ठा sysc *ddata)
अणु
	वापस !!(ddata->cfg.quirks & SYSC_QUIRK_OPT_CLKS_NEEDED);
पूर्ण

अटल u32 sysc_पढ़ो_revision(काष्ठा sysc *ddata)
अणु
	पूर्णांक offset = ddata->offsets[SYSC_REVISION];

	अगर (offset < 0)
		वापस 0;

	वापस sysc_पढ़ो(ddata, offset);
पूर्ण

अटल u32 sysc_पढ़ो_sysconfig(काष्ठा sysc *ddata)
अणु
	पूर्णांक offset = ddata->offsets[SYSC_SYSCONFIG];

	अगर (offset < 0)
		वापस 0;

	वापस sysc_पढ़ो(ddata, offset);
पूर्ण

अटल u32 sysc_पढ़ो_sysstatus(काष्ठा sysc *ddata)
अणु
	पूर्णांक offset = ddata->offsets[SYSC_SYSSTATUS];

	अगर (offset < 0)
		वापस 0;

	वापस sysc_पढ़ो(ddata, offset);
पूर्ण

/* Poll on reset status */
अटल पूर्णांक sysc_रुको_softreset(काष्ठा sysc *ddata)
अणु
	u32 sysc_mask, syss_करोne, rstval;
	पूर्णांक syss_offset, error = 0;

	अगर (ddata->cap->regbits->srst_shअगरt < 0)
		वापस 0;

	syss_offset = ddata->offsets[SYSC_SYSSTATUS];
	sysc_mask = BIT(ddata->cap->regbits->srst_shअगरt);

	अगर (ddata->cfg.quirks & SYSS_QUIRK_RESETDONE_INVERTED)
		syss_करोne = 0;
	अन्यथा
		syss_करोne = ddata->cfg.syss_mask;

	अगर (syss_offset >= 0) अणु
		error = पढ़ोx_poll_समयout_atomic(sysc_पढ़ो_sysstatus, ddata,
				rstval, (rstval & ddata->cfg.syss_mask) ==
				syss_करोne, 100, MAX_MODULE_SOFTRESET_WAIT);

	पूर्ण अन्यथा अगर (ddata->cfg.quirks & SYSC_QUIRK_RESET_STATUS) अणु
		error = पढ़ोx_poll_समयout_atomic(sysc_पढ़ो_sysconfig, ddata,
				rstval, !(rstval & sysc_mask),
				100, MAX_MODULE_SOFTRESET_WAIT);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक sysc_add_named_घड़ी_from_child(काष्ठा sysc *ddata,
					   स्थिर अक्षर *name,
					   स्थिर अक्षर *optfck_name)
अणु
	काष्ठा device_node *np = ddata->dev->of_node;
	काष्ठा device_node *child;
	काष्ठा clk_lookup *cl;
	काष्ठा clk *घड़ी;
	स्थिर अक्षर *n;

	अगर (name)
		n = name;
	अन्यथा
		n = optfck_name;

	/* Does the घड़ी alias alपढ़ोy exist? */
	घड़ी = of_clk_get_by_name(np, n);
	अगर (!IS_ERR(घड़ी)) अणु
		clk_put(घड़ी);

		वापस 0;
	पूर्ण

	child = of_get_next_available_child(np, शून्य);
	अगर (!child)
		वापस -ENODEV;

	घड़ी = devm_get_clk_from_child(ddata->dev, child, name);
	अगर (IS_ERR(घड़ी))
		वापस PTR_ERR(घड़ी);

	/*
	 * Use clkdev_add() instead of clkdev_alloc() to aव्योम the MAX_DEV_ID
	 * limit क्रम clk_get(). If cl ever needs to be मुक्तd, it should be करोne
	 * with clkdev_drop().
	 */
	cl = kzalloc(माप(*cl), GFP_KERNEL);
	अगर (!cl)
		वापस -ENOMEM;

	cl->con_id = n;
	cl->dev_id = dev_name(ddata->dev);
	cl->clk = घड़ी;
	clkdev_add(cl);

	clk_put(घड़ी);

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_init_ext_opt_घड़ी(काष्ठा sysc *ddata, स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *optfck_name;
	पूर्णांक error, index;

	अगर (ddata->nr_घड़ीs < SYSC_OPTFCK0)
		index = SYSC_OPTFCK0;
	अन्यथा
		index = ddata->nr_घड़ीs;

	अगर (name)
		optfck_name = name;
	अन्यथा
		optfck_name = घड़ी_names[index];

	error = sysc_add_named_घड़ी_from_child(ddata, name, optfck_name);
	अगर (error)
		वापस error;

	ddata->घड़ी_roles[index] = optfck_name;
	ddata->nr_घड़ीs++;

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_get_one_घड़ी(काष्ठा sysc *ddata, स्थिर अक्षर *name)
अणु
	पूर्णांक error, i, index = -ENODEV;

	अगर (!म_भेदन(घड़ी_names[SYSC_FCK], name, 3))
		index = SYSC_FCK;
	अन्यथा अगर (!म_भेदन(घड़ी_names[SYSC_ICK], name, 3))
		index = SYSC_ICK;

	अगर (index < 0) अणु
		क्रम (i = SYSC_OPTFCK0; i < SYSC_MAX_CLOCKS; i++) अणु
			अगर (!ddata->घड़ीs[i]) अणु
				index = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (index < 0) अणु
		dev_err(ddata->dev, "clock %s not added\n", name);
		वापस index;
	पूर्ण

	ddata->घड़ीs[index] = devm_clk_get(ddata->dev, name);
	अगर (IS_ERR(ddata->घड़ीs[index])) अणु
		dev_err(ddata->dev, "clock get error for %s: %li\n",
			name, PTR_ERR(ddata->घड़ीs[index]));

		वापस PTR_ERR(ddata->घड़ीs[index]);
	पूर्ण

	error = clk_prepare(ddata->घड़ीs[index]);
	अगर (error) अणु
		dev_err(ddata->dev, "clock prepare error for %s: %i\n",
			name, error);

		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_get_घड़ीs(काष्ठा sysc *ddata)
अणु
	काष्ठा device_node *np = ddata->dev->of_node;
	काष्ठा property *prop;
	स्थिर अक्षर *name;
	पूर्णांक nr_fck = 0, nr_ick = 0, i, error = 0;

	ddata->घड़ी_roles = devm_kसुस्मृति(ddata->dev,
					  SYSC_MAX_CLOCKS,
					  माप(*ddata->घड़ी_roles),
					  GFP_KERNEL);
	अगर (!ddata->घड़ी_roles)
		वापस -ENOMEM;

	of_property_क्रम_each_string(np, "clock-names", prop, name) अणु
		अगर (!म_भेदन(घड़ी_names[SYSC_FCK], name, 3))
			nr_fck++;
		अगर (!म_भेदन(घड़ी_names[SYSC_ICK], name, 3))
			nr_ick++;
		ddata->घड़ी_roles[ddata->nr_घड़ीs] = name;
		ddata->nr_घड़ीs++;
	पूर्ण

	अगर (ddata->nr_घड़ीs < 1)
		वापस 0;

	अगर ((ddata->cfg.quirks & SYSC_QUIRK_EXT_OPT_CLOCK)) अणु
		error = sysc_init_ext_opt_घड़ी(ddata, शून्य);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (ddata->nr_घड़ीs > SYSC_MAX_CLOCKS) अणु
		dev_err(ddata->dev, "too many clocks for %pOF\n", np);

		वापस -EINVAL;
	पूर्ण

	अगर (nr_fck > 1 || nr_ick > 1) अणु
		dev_err(ddata->dev, "max one fck and ick for %pOF\n", np);

		वापस -EINVAL;
	पूर्ण

	/* Always add a slot क्रम मुख्य घड़ीs fck and ick even अगर unused */
	अगर (!nr_fck)
		ddata->nr_घड़ीs++;
	अगर (!nr_ick)
		ddata->nr_घड़ीs++;

	ddata->घड़ीs = devm_kसुस्मृति(ddata->dev,
				     ddata->nr_घड़ीs, माप(*ddata->घड़ीs),
				     GFP_KERNEL);
	अगर (!ddata->घड़ीs)
		वापस -ENOMEM;

	क्रम (i = 0; i < SYSC_MAX_CLOCKS; i++) अणु
		स्थिर अक्षर *name = ddata->घड़ी_roles[i];

		अगर (!name)
			जारी;

		error = sysc_get_one_घड़ी(ddata, name);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_enable_मुख्य_घड़ीs(काष्ठा sysc *ddata)
अणु
	काष्ठा clk *घड़ी;
	पूर्णांक i, error;

	अगर (!ddata->घड़ीs)
		वापस 0;

	क्रम (i = 0; i < SYSC_OPTFCK0; i++) अणु
		घड़ी = ddata->घड़ीs[i];

		/* Main घड़ीs may not have ick */
		अगर (IS_ERR_OR_शून्य(घड़ी))
			जारी;

		error = clk_enable(घड़ी);
		अगर (error)
			जाओ err_disable;
	पूर्ण

	वापस 0;

err_disable:
	क्रम (i--; i >= 0; i--) अणु
		घड़ी = ddata->घड़ीs[i];

		/* Main घड़ीs may not have ick */
		अगर (IS_ERR_OR_शून्य(घड़ी))
			जारी;

		clk_disable(घड़ी);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम sysc_disable_मुख्य_घड़ीs(काष्ठा sysc *ddata)
अणु
	काष्ठा clk *घड़ी;
	पूर्णांक i;

	अगर (!ddata->घड़ीs)
		वापस;

	क्रम (i = 0; i < SYSC_OPTFCK0; i++) अणु
		घड़ी = ddata->घड़ीs[i];
		अगर (IS_ERR_OR_शून्य(घड़ी))
			जारी;

		clk_disable(घड़ी);
	पूर्ण
पूर्ण

अटल पूर्णांक sysc_enable_opt_घड़ीs(काष्ठा sysc *ddata)
अणु
	काष्ठा clk *घड़ी;
	पूर्णांक i, error;

	अगर (!ddata->घड़ीs || ddata->nr_घड़ीs < SYSC_OPTFCK0 + 1)
		वापस 0;

	क्रम (i = SYSC_OPTFCK0; i < SYSC_MAX_CLOCKS; i++) अणु
		घड़ी = ddata->घड़ीs[i];

		/* Assume no holes क्रम opt घड़ीs */
		अगर (IS_ERR_OR_शून्य(घड़ी))
			वापस 0;

		error = clk_enable(घड़ी);
		अगर (error)
			जाओ err_disable;
	पूर्ण

	वापस 0;

err_disable:
	क्रम (i--; i >= 0; i--) अणु
		घड़ी = ddata->घड़ीs[i];
		अगर (IS_ERR_OR_शून्य(घड़ी))
			जारी;

		clk_disable(घड़ी);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम sysc_disable_opt_घड़ीs(काष्ठा sysc *ddata)
अणु
	काष्ठा clk *घड़ी;
	पूर्णांक i;

	अगर (!ddata->घड़ीs || ddata->nr_घड़ीs < SYSC_OPTFCK0 + 1)
		वापस;

	क्रम (i = SYSC_OPTFCK0; i < SYSC_MAX_CLOCKS; i++) अणु
		घड़ी = ddata->घड़ीs[i];

		/* Assume no holes क्रम opt घड़ीs */
		अगर (IS_ERR_OR_शून्य(घड़ी))
			वापस;

		clk_disable(घड़ी);
	पूर्ण
पूर्ण

अटल व्योम sysc_clkdm_deny_idle(काष्ठा sysc *ddata)
अणु
	काष्ठा ti_sysc_platक्रमm_data *pdata;

	अगर (ddata->legacy_mode || (ddata->cfg.quirks & SYSC_QUIRK_CLKDM_NOAUTO))
		वापस;

	pdata = dev_get_platdata(ddata->dev);
	अगर (pdata && pdata->clkdm_deny_idle)
		pdata->clkdm_deny_idle(ddata->dev, &ddata->cookie);
पूर्ण

अटल व्योम sysc_clkdm_allow_idle(काष्ठा sysc *ddata)
अणु
	काष्ठा ti_sysc_platक्रमm_data *pdata;

	अगर (ddata->legacy_mode || (ddata->cfg.quirks & SYSC_QUIRK_CLKDM_NOAUTO))
		वापस;

	pdata = dev_get_platdata(ddata->dev);
	अगर (pdata && pdata->clkdm_allow_idle)
		pdata->clkdm_allow_idle(ddata->dev, &ddata->cookie);
पूर्ण

/**
 * sysc_init_resets - init rstctrl reset line अगर configured
 * @ddata: device driver data
 *
 * See sysc_rstctrl_reset_deनिश्चित().
 */
अटल पूर्णांक sysc_init_resets(काष्ठा sysc *ddata)
अणु
	ddata->rsts =
		devm_reset_control_get_optional_shared(ddata->dev, "rstctrl");

	वापस PTR_ERR_OR_ZERO(ddata->rsts);
पूर्ण

/**
 * sysc_parse_and_check_child_range - parses module IO region from ranges
 * @ddata: device driver data
 *
 * In general we only need rev, syss, and sysc रेजिस्टरs and not the whole
 * module range. But we करो want the offsets क्रम these रेजिस्टरs from the
 * module base. This allows us to check them against the legacy hwmod
 * platक्रमm data. Let's also check the ranges are configured properly.
 */
अटल पूर्णांक sysc_parse_and_check_child_range(काष्ठा sysc *ddata)
अणु
	काष्ठा device_node *np = ddata->dev->of_node;
	स्थिर __be32 *ranges;
	u32 nr_addr, nr_size;
	पूर्णांक len, error;

	ranges = of_get_property(np, "ranges", &len);
	अगर (!ranges) अणु
		dev_err(ddata->dev, "missing ranges for %pOF\n", np);

		वापस -ENOENT;
	पूर्ण

	len /= माप(*ranges);

	अगर (len < 3) अणु
		dev_err(ddata->dev, "incomplete ranges for %pOF\n", np);

		वापस -EINVAL;
	पूर्ण

	error = of_property_पढ़ो_u32(np, "#address-cells", &nr_addr);
	अगर (error)
		वापस -ENOENT;

	error = of_property_पढ़ो_u32(np, "#size-cells", &nr_size);
	अगर (error)
		वापस -ENOENT;

	अगर (nr_addr != 1 || nr_size != 1) अणु
		dev_err(ddata->dev, "invalid ranges for %pOF\n", np);

		वापस -EINVAL;
	पूर्ण

	ranges++;
	ddata->module_pa = of_translate_address(np, ranges++);
	ddata->module_size = be32_to_cpup(ranges);

	वापस 0;
पूर्ण

/* Interconnect instances to probe beक्रमe l4_per instances */
अटल काष्ठा resource early_bus_ranges[] = अणु
	/* am3/4 l4_wkup */
	अणु .start = 0x44c00000, .end = 0x44c00000 + 0x300000, पूर्ण,
	/* omap4/5 and dra7 l4_cfg */
	अणु .start = 0x4a000000, .end = 0x4a000000 + 0x300000, पूर्ण,
	/* omap4 l4_wkup */
	अणु .start = 0x4a300000, .end = 0x4a300000 + 0x30000,  पूर्ण,
	/* omap5 and dra7 l4_wkup without dra7 dcan segment */
	अणु .start = 0x4ae00000, .end = 0x4ae00000 + 0x30000,  पूर्ण,
पूर्ण;

अटल atomic_t sysc_defer = ATOMIC_INIT(10);

/**
 * sysc_defer_non_critical - defer non_critical पूर्णांकerconnect probing
 * @ddata: device driver data
 *
 * We want to probe l4_cfg and l4_wkup पूर्णांकerconnect instances beक्रमe any
 * l4_per instances as l4_per instances depend on resources on l4_cfg and
 * l4_wkup पूर्णांकerconnects.
 */
अटल पूर्णांक sysc_defer_non_critical(काष्ठा sysc *ddata)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	अगर (!atomic_पढ़ो(&sysc_defer))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(early_bus_ranges); i++) अणु
		res = &early_bus_ranges[i];
		अगर (ddata->module_pa >= res->start &&
		    ddata->module_pa <= res->end) अणु
			atomic_set(&sysc_defer, 0);

			वापस 0;
		पूर्ण
	पूर्ण

	atomic_dec_अगर_positive(&sysc_defer);

	वापस -EPROBE_DEFER;
पूर्ण

अटल काष्ठा device_node *मानक_निकास_path;

अटल व्योम sysc_init_मानक_निकास_path(काष्ठा sysc *ddata)
अणु
	काष्ठा device_node *np = शून्य;
	स्थिर अक्षर *uart;

	अगर (IS_ERR(मानक_निकास_path))
		वापस;

	अगर (मानक_निकास_path)
		वापस;

	np = of_find_node_by_path("/chosen");
	अगर (!np)
		जाओ err;

	uart = of_get_property(np, "stdout-path", शून्य);
	अगर (!uart)
		जाओ err;

	np = of_find_node_by_path(uart);
	अगर (!np)
		जाओ err;

	मानक_निकास_path = np;

	वापस;

err:
	मानक_निकास_path = ERR_PTR(-ENODEV);
पूर्ण

अटल व्योम sysc_check_quirk_मानक_निकास(काष्ठा sysc *ddata,
				    काष्ठा device_node *np)
अणु
	sysc_init_मानक_निकास_path(ddata);
	अगर (np != मानक_निकास_path)
		वापस;

	ddata->cfg.quirks |= SYSC_QUIRK_NO_IDLE_ON_INIT |
				SYSC_QUIRK_NO_RESET_ON_INIT;
पूर्ण

/**
 * sysc_check_one_child - check child configuration
 * @ddata: device driver data
 * @np: child device node
 *
 * Let's aव्योम messy situations where we have new पूर्णांकerconnect target
 * node but children have "ti,hwmods". These beदीर्घ to the पूर्णांकerconnect
 * target node and are managed by this driver.
 */
अटल व्योम sysc_check_one_child(काष्ठा sysc *ddata,
				 काष्ठा device_node *np)
अणु
	स्थिर अक्षर *name;

	name = of_get_property(np, "ti,hwmods", शून्य);
	अगर (name && !of_device_is_compatible(np, "ti,sysc"))
		dev_warn(ddata->dev, "really a child ti,hwmods property?");

	sysc_check_quirk_मानक_निकास(ddata, np);
	sysc_parse_dts_quirks(ddata, np, true);
पूर्ण

अटल व्योम sysc_check_children(काष्ठा sysc *ddata)
अणु
	काष्ठा device_node *child;

	क्रम_each_child_of_node(ddata->dev->of_node, child)
		sysc_check_one_child(ddata, child);
पूर्ण

/*
 * So far only I2C uses 16-bit पढ़ो access with घड़ीactivity with revision
 * in two रेजिस्टरs with stride of 4. We can detect this based on the rev
 * रेजिस्टर size to configure things far enough to be able to properly पढ़ो
 * the revision रेजिस्टर.
 */
अटल व्योम sysc_check_quirk_16bit(काष्ठा sysc *ddata, काष्ठा resource *res)
अणु
	अगर (resource_size(res) == 8)
		ddata->cfg.quirks |= SYSC_QUIRK_16BIT | SYSC_QUIRK_USE_CLOCKACT;
पूर्ण

/**
 * sysc_parse_one - parses the पूर्णांकerconnect target module रेजिस्टरs
 * @ddata: device driver data
 * @reg: रेजिस्टर to parse
 */
अटल पूर्णांक sysc_parse_one(काष्ठा sysc *ddata, क्रमागत sysc_रेजिस्टरs reg)
अणु
	काष्ठा resource *res;
	स्थिर अक्षर *name;

	चयन (reg) अणु
	हाल SYSC_REVISION:
	हाल SYSC_SYSCONFIG:
	हाल SYSC_SYSSTATUS:
		name = reg_names[reg];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource_byname(to_platक्रमm_device(ddata->dev),
					   IORESOURCE_MEM, name);
	अगर (!res) अणु
		ddata->offsets[reg] = -ENODEV;

		वापस 0;
	पूर्ण

	ddata->offsets[reg] = res->start - ddata->module_pa;
	अगर (reg == SYSC_REVISION)
		sysc_check_quirk_16bit(ddata, res);

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_parse_रेजिस्टरs(काष्ठा sysc *ddata)
अणु
	पूर्णांक i, error;

	क्रम (i = 0; i < SYSC_MAX_REGS; i++) अणु
		error = sysc_parse_one(ddata, i);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sysc_check_रेजिस्टरs - check क्रम misconfigured रेजिस्टर overlaps
 * @ddata: device driver data
 */
अटल पूर्णांक sysc_check_रेजिस्टरs(काष्ठा sysc *ddata)
अणु
	पूर्णांक i, j, nr_regs = 0, nr_matches = 0;

	क्रम (i = 0; i < SYSC_MAX_REGS; i++) अणु
		अगर (ddata->offsets[i] < 0)
			जारी;

		अगर (ddata->offsets[i] > (ddata->module_size - 4)) अणु
			dev_err(ddata->dev, "register outside module range");

				वापस -EINVAL;
		पूर्ण

		क्रम (j = 0; j < SYSC_MAX_REGS; j++) अणु
			अगर (ddata->offsets[j] < 0)
				जारी;

			अगर (ddata->offsets[i] == ddata->offsets[j])
				nr_matches++;
		पूर्ण
		nr_regs++;
	पूर्ण

	अगर (nr_matches > nr_regs) अणु
		dev_err(ddata->dev, "overlapping registers: (%i/%i)",
			nr_regs, nr_matches);

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * syc_ioremap - ioremap रेजिस्टर space क्रम the पूर्णांकerconnect target module
 * @ddata: device driver data
 *
 * Note that the पूर्णांकerconnect target module रेजिस्टरs can be anywhere
 * within the पूर्णांकerconnect target module range. For example, SGX has
 * them at offset 0x1fc00 in the 32MB module address space. And cpsw
 * has them at offset 0x1200 in the CPSW_WR child. Usually the
 * the पूर्णांकerconnect target module रेजिस्टरs are at the beginning of
 * the module range though.
 */
अटल पूर्णांक sysc_ioremap(काष्ठा sysc *ddata)
अणु
	पूर्णांक size;

	अगर (ddata->offsets[SYSC_REVISION] < 0 &&
	    ddata->offsets[SYSC_SYSCONFIG] < 0 &&
	    ddata->offsets[SYSC_SYSSTATUS] < 0) अणु
		size = ddata->module_size;
	पूर्ण अन्यथा अणु
		size = max3(ddata->offsets[SYSC_REVISION],
			    ddata->offsets[SYSC_SYSCONFIG],
			    ddata->offsets[SYSC_SYSSTATUS]);

		अगर (size < SZ_1K)
			size = SZ_1K;

		अगर ((size + माप(u32)) > ddata->module_size)
			size = ddata->module_size;
	पूर्ण

	ddata->module_va = devm_ioremap(ddata->dev,
					ddata->module_pa,
					size + माप(u32));
	अगर (!ddata->module_va)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * sysc_map_and_check_रेजिस्टरs - ioremap and check device रेजिस्टरs
 * @ddata: device driver data
 */
अटल पूर्णांक sysc_map_and_check_रेजिस्टरs(काष्ठा sysc *ddata)
अणु
	काष्ठा device_node *np = ddata->dev->of_node;
	पूर्णांक error;

	error = sysc_parse_and_check_child_range(ddata);
	अगर (error)
		वापस error;

	error = sysc_defer_non_critical(ddata);
	अगर (error)
		वापस error;

	sysc_check_children(ddata);

	अगर (!of_get_property(np, "reg", शून्य))
		वापस 0;

	error = sysc_parse_रेजिस्टरs(ddata);
	अगर (error)
		वापस error;

	error = sysc_ioremap(ddata);
	अगर (error)
		वापस error;

	error = sysc_check_रेजिस्टरs(ddata);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

/**
 * sysc_show_rev - पढ़ो and show पूर्णांकerconnect target module revision
 * @bufp: buffer to prपूर्णांक the inक्रमmation to
 * @ddata: device driver data
 */
अटल पूर्णांक sysc_show_rev(अक्षर *bufp, काष्ठा sysc *ddata)
अणु
	पूर्णांक len;

	अगर (ddata->offsets[SYSC_REVISION] < 0)
		वापस प्र_लिखो(bufp, ":NA");

	len = प्र_लिखो(bufp, ":%08x", ddata->revision);

	वापस len;
पूर्ण

अटल पूर्णांक sysc_show_reg(काष्ठा sysc *ddata,
			 अक्षर *bufp, क्रमागत sysc_रेजिस्टरs reg)
अणु
	अगर (ddata->offsets[reg] < 0)
		वापस प्र_लिखो(bufp, ":NA");

	वापस प्र_लिखो(bufp, ":%x", ddata->offsets[reg]);
पूर्ण

अटल पूर्णांक sysc_show_name(अक्षर *bufp, काष्ठा sysc *ddata)
अणु
	अगर (!ddata->name)
		वापस 0;

	वापस प्र_लिखो(bufp, ":%s", ddata->name);
पूर्ण

/**
 * sysc_show_रेजिस्टरs - show inक्रमmation about पूर्णांकerconnect target module
 * @ddata: device driver data
 */
अटल व्योम sysc_show_रेजिस्टरs(काष्ठा sysc *ddata)
अणु
	अक्षर buf[128];
	अक्षर *bufp = buf;
	पूर्णांक i;

	क्रम (i = 0; i < SYSC_MAX_REGS; i++)
		bufp += sysc_show_reg(ddata, bufp, i);

	bufp += sysc_show_rev(bufp, ddata);
	bufp += sysc_show_name(bufp, ddata);

	dev_dbg(ddata->dev, "%llx:%x%s\n",
		ddata->module_pa, ddata->module_size,
		buf);
पूर्ण

/**
 * sysc_ग_लिखो_sysconfig - handle sysconfig quirks क्रम रेजिस्टर ग_लिखो
 * @ddata: device driver data
 * @value: रेजिस्टर value
 */
अटल व्योम sysc_ग_लिखो_sysconfig(काष्ठा sysc *ddata, u32 value)
अणु
	अगर (ddata->module_unlock_quirk)
		ddata->module_unlock_quirk(ddata);

	sysc_ग_लिखो(ddata, ddata->offsets[SYSC_SYSCONFIG], value);

	अगर (ddata->module_lock_quirk)
		ddata->module_lock_quirk(ddata);
पूर्ण

#घोषणा SYSC_IDLE_MASK	(SYSC_NR_IDLEMODES - 1)
#घोषणा SYSC_CLOCACT_ICK	2

/* Caller needs to manage sysc_clkdm_deny_idle() and sysc_clkdm_allow_idle() */
अटल पूर्णांक sysc_enable_module(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	स्थिर काष्ठा sysc_regbits *regbits;
	u32 reg, idlemodes, best_mode;
	पूर्णांक error;

	ddata = dev_get_drvdata(dev);

	/*
	 * Some modules like DSS reset स्वतःmatically on idle. Enable optional
	 * reset घड़ीs and रुको क्रम OCP softreset to complete.
	 */
	अगर (ddata->cfg.quirks & SYSC_QUIRK_OPT_CLKS_IN_RESET) अणु
		error = sysc_enable_opt_घड़ीs(ddata);
		अगर (error) अणु
			dev_err(ddata->dev,
				"Optional clocks failed for enable: %i\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण
	/*
	 * Some modules like i2c and hdq1w have unusable reset status unless
	 * the module reset quirk is enabled. Skip status check on enable.
	 */
	अगर (!(ddata->cfg.quirks & SYSC_MODULE_QUIRK_ENA_RESETDONE)) अणु
		error = sysc_रुको_softreset(ddata);
		अगर (error)
			dev_warn(ddata->dev, "OCP softreset timed out\n");
	पूर्ण
	अगर (ddata->cfg.quirks & SYSC_QUIRK_OPT_CLKS_IN_RESET)
		sysc_disable_opt_घड़ीs(ddata);

	/*
	 * Some subप्रणाली निजी पूर्णांकerconnects, like DSS top level module,
	 * need only the स्वतःmatic OCP softreset handling with no sysconfig
	 * रेजिस्टर bits to configure.
	 */
	अगर (ddata->offsets[SYSC_SYSCONFIG] == -ENODEV)
		वापस 0;

	regbits = ddata->cap->regbits;
	reg = sysc_पढ़ो(ddata, ddata->offsets[SYSC_SYSCONFIG]);

	/*
	 * Set CLOCKACTIVITY, we only use it क्रम ick. And we only configure it
	 * based on the SYSC_QUIRK_USE_CLOCKACT flag, not based on the hardware
	 * capabilities. See the old HWMOD_SET_DEFAULT_CLOCKACT flag.
	 */
	अगर (regbits->clkact_shअगरt >= 0 &&
	    (ddata->cfg.quirks & SYSC_QUIRK_USE_CLOCKACT))
		reg |= SYSC_CLOCACT_ICK << regbits->clkact_shअगरt;

	/* Set SIDLE mode */
	idlemodes = ddata->cfg.sidlemodes;
	अगर (!idlemodes || regbits->sidle_shअगरt < 0)
		जाओ set_midle;

	अगर (ddata->cfg.quirks & (SYSC_QUIRK_SWSUP_SIDLE |
				 SYSC_QUIRK_SWSUP_SIDLE_ACT)) अणु
		best_mode = SYSC_IDLE_NO;
	पूर्ण अन्यथा अणु
		best_mode = fls(ddata->cfg.sidlemodes) - 1;
		अगर (best_mode > SYSC_IDLE_MASK) अणु
			dev_err(dev, "%s: invalid sidlemode\n", __func__);
			वापस -EINVAL;
		पूर्ण

		/* Set WAKEUP */
		अगर (regbits->enwkup_shअगरt >= 0 &&
		    ddata->cfg.sysc_val & BIT(regbits->enwkup_shअगरt))
			reg |= BIT(regbits->enwkup_shअगरt);
	पूर्ण

	reg &= ~(SYSC_IDLE_MASK << regbits->sidle_shअगरt);
	reg |= best_mode << regbits->sidle_shअगरt;
	sysc_ग_लिखो_sysconfig(ddata, reg);

set_midle:
	/* Set MIDLE mode */
	idlemodes = ddata->cfg.midlemodes;
	अगर (!idlemodes || regbits->midle_shअगरt < 0)
		जाओ set_स्वतःidle;

	best_mode = fls(ddata->cfg.midlemodes) - 1;
	अगर (best_mode > SYSC_IDLE_MASK) अणु
		dev_err(dev, "%s: invalid midlemode\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (ddata->cfg.quirks & SYSC_QUIRK_SWSUP_MSTANDBY)
		best_mode = SYSC_IDLE_NO;

	reg &= ~(SYSC_IDLE_MASK << regbits->midle_shअगरt);
	reg |= best_mode << regbits->midle_shअगरt;
	sysc_ग_लिखो_sysconfig(ddata, reg);

set_स्वतःidle:
	/* Autoidle bit must enabled separately अगर available */
	अगर (regbits->स्वतःidle_shअगरt >= 0 &&
	    ddata->cfg.sysc_val & BIT(regbits->स्वतःidle_shअगरt)) अणु
		reg |= 1 << regbits->स्वतःidle_shअगरt;
		sysc_ग_लिखो_sysconfig(ddata, reg);
	पूर्ण

	/* Flush posted ग_लिखो */
	sysc_पढ़ो(ddata, ddata->offsets[SYSC_SYSCONFIG]);

	अगर (ddata->module_enable_quirk)
		ddata->module_enable_quirk(ddata);

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_best_idle_mode(u32 idlemodes, u32 *best_mode)
अणु
	अगर (idlemodes & BIT(SYSC_IDLE_SMART_WKUP))
		*best_mode = SYSC_IDLE_SMART_WKUP;
	अन्यथा अगर (idlemodes & BIT(SYSC_IDLE_SMART))
		*best_mode = SYSC_IDLE_SMART;
	अन्यथा अगर (idlemodes & BIT(SYSC_IDLE_FORCE))
		*best_mode = SYSC_IDLE_FORCE;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Caller needs to manage sysc_clkdm_deny_idle() and sysc_clkdm_allow_idle() */
अटल पूर्णांक sysc_disable_module(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	स्थिर काष्ठा sysc_regbits *regbits;
	u32 reg, idlemodes, best_mode;
	पूर्णांक ret;

	ddata = dev_get_drvdata(dev);
	अगर (ddata->offsets[SYSC_SYSCONFIG] == -ENODEV)
		वापस 0;

	अगर (ddata->module_disable_quirk)
		ddata->module_disable_quirk(ddata);

	regbits = ddata->cap->regbits;
	reg = sysc_पढ़ो(ddata, ddata->offsets[SYSC_SYSCONFIG]);

	/* Set MIDLE mode */
	idlemodes = ddata->cfg.midlemodes;
	अगर (!idlemodes || regbits->midle_shअगरt < 0)
		जाओ set_sidle;

	ret = sysc_best_idle_mode(idlemodes, &best_mode);
	अगर (ret) अणु
		dev_err(dev, "%s: invalid midlemode\n", __func__);
		वापस ret;
	पूर्ण

	अगर (ddata->cfg.quirks & (SYSC_QUIRK_SWSUP_MSTANDBY) ||
	    ddata->cfg.quirks & (SYSC_QUIRK_FORCE_MSTANDBY))
		best_mode = SYSC_IDLE_FORCE;

	reg &= ~(SYSC_IDLE_MASK << regbits->midle_shअगरt);
	reg |= best_mode << regbits->midle_shअगरt;
	sysc_ग_लिखो_sysconfig(ddata, reg);

set_sidle:
	/* Set SIDLE mode */
	idlemodes = ddata->cfg.sidlemodes;
	अगर (!idlemodes || regbits->sidle_shअगरt < 0)
		वापस 0;

	अगर (ddata->cfg.quirks & SYSC_QUIRK_SWSUP_SIDLE) अणु
		best_mode = SYSC_IDLE_FORCE;
	पूर्ण अन्यथा अणु
		ret = sysc_best_idle_mode(idlemodes, &best_mode);
		अगर (ret) अणु
			dev_err(dev, "%s: invalid sidlemode\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	reg &= ~(SYSC_IDLE_MASK << regbits->sidle_shअगरt);
	reg |= best_mode << regbits->sidle_shअगरt;
	अगर (regbits->स्वतःidle_shअगरt >= 0 &&
	    ddata->cfg.sysc_val & BIT(regbits->स्वतःidle_shअगरt))
		reg |= 1 << regbits->स्वतःidle_shअगरt;
	sysc_ग_लिखो_sysconfig(ddata, reg);

	/* Flush posted ग_लिखो */
	sysc_पढ़ो(ddata, ddata->offsets[SYSC_SYSCONFIG]);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sysc_runसमय_suspend_legacy(काष्ठा device *dev,
						      काष्ठा sysc *ddata)
अणु
	काष्ठा ti_sysc_platक्रमm_data *pdata;
	पूर्णांक error;

	pdata = dev_get_platdata(ddata->dev);
	अगर (!pdata)
		वापस 0;

	अगर (!pdata->idle_module)
		वापस -ENODEV;

	error = pdata->idle_module(dev, &ddata->cookie);
	अगर (error)
		dev_err(dev, "%s: could not idle: %i\n",
			__func__, error);

	reset_control_निश्चित(ddata->rsts);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sysc_runसमय_resume_legacy(काष्ठा device *dev,
						     काष्ठा sysc *ddata)
अणु
	काष्ठा ti_sysc_platक्रमm_data *pdata;
	पूर्णांक error;

	pdata = dev_get_platdata(ddata->dev);
	अगर (!pdata)
		वापस 0;

	अगर (!pdata->enable_module)
		वापस -ENODEV;

	error = pdata->enable_module(dev, &ddata->cookie);
	अगर (error)
		dev_err(dev, "%s: could not enable: %i\n",
			__func__, error);

	reset_control_deनिश्चित(ddata->rsts);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sysc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	पूर्णांक error = 0;

	ddata = dev_get_drvdata(dev);

	अगर (!ddata->enabled)
		वापस 0;

	sysc_clkdm_deny_idle(ddata);

	अगर (ddata->legacy_mode) अणु
		error = sysc_runसमय_suspend_legacy(dev, ddata);
		अगर (error)
			जाओ err_allow_idle;
	पूर्ण अन्यथा अणु
		error = sysc_disable_module(dev);
		अगर (error)
			जाओ err_allow_idle;
	पूर्ण

	sysc_disable_मुख्य_घड़ीs(ddata);

	अगर (sysc_opt_clks_needed(ddata))
		sysc_disable_opt_घड़ीs(ddata);

	ddata->enabled = false;

err_allow_idle:
	sysc_clkdm_allow_idle(ddata);

	reset_control_निश्चित(ddata->rsts);

	वापस error;
पूर्ण

अटल पूर्णांक __maybe_unused sysc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	पूर्णांक error = 0;

	ddata = dev_get_drvdata(dev);

	अगर (ddata->enabled)
		वापस 0;


	sysc_clkdm_deny_idle(ddata);

	अगर (sysc_opt_clks_needed(ddata)) अणु
		error = sysc_enable_opt_घड़ीs(ddata);
		अगर (error)
			जाओ err_allow_idle;
	पूर्ण

	error = sysc_enable_मुख्य_घड़ीs(ddata);
	अगर (error)
		जाओ err_opt_घड़ीs;

	reset_control_deनिश्चित(ddata->rsts);

	अगर (ddata->legacy_mode) अणु
		error = sysc_runसमय_resume_legacy(dev, ddata);
		अगर (error)
			जाओ err_मुख्य_घड़ीs;
	पूर्ण अन्यथा अणु
		error = sysc_enable_module(dev);
		अगर (error)
			जाओ err_मुख्य_घड़ीs;
	पूर्ण

	ddata->enabled = true;

	sysc_clkdm_allow_idle(ddata);

	वापस 0;

err_मुख्य_घड़ीs:
	sysc_disable_मुख्य_घड़ीs(ddata);
err_opt_घड़ीs:
	अगर (sysc_opt_clks_needed(ddata))
		sysc_disable_opt_घड़ीs(ddata);
err_allow_idle:
	sysc_clkdm_allow_idle(ddata);

	वापस error;
पूर्ण

अटल पूर्णांक sysc_reinit_module(काष्ठा sysc *ddata, bool leave_enabled)
अणु
	काष्ठा device *dev = ddata->dev;
	पूर्णांक error;

	/* Disable target module अगर it is enabled */
	अगर (ddata->enabled) अणु
		error = sysc_runसमय_suspend(dev);
		अगर (error)
			dev_warn(dev, "reinit suspend failed: %i\n", error);
	पूर्ण

	/* Enable target module */
	error = sysc_runसमय_resume(dev);
	अगर (error)
		dev_warn(dev, "reinit resume failed: %i\n", error);

	अगर (leave_enabled)
		वापस error;

	/* Disable target module अगर no leave_enabled was set */
	error = sysc_runसमय_suspend(dev);
	अगर (error)
		dev_warn(dev, "reinit suspend failed: %i\n", error);

	वापस error;
पूर्ण

अटल पूर्णांक __maybe_unused sysc_noirq_suspend(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;

	ddata = dev_get_drvdata(dev);

	अगर (ddata->cfg.quirks &
	    (SYSC_QUIRK_LEGACY_IDLE | SYSC_QUIRK_NO_IDLE))
		वापस 0;

	अगर (!ddata->enabled)
		वापस 0;

	ddata->needs_resume = 1;

	वापस sysc_runसमय_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sysc_noirq_resume(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	पूर्णांक error = 0;

	ddata = dev_get_drvdata(dev);

	अगर (ddata->cfg.quirks &
	    (SYSC_QUIRK_LEGACY_IDLE | SYSC_QUIRK_NO_IDLE))
		वापस 0;

	अगर (ddata->cfg.quirks & SYSC_QUIRK_REINIT_ON_RESUME) अणु
		error = sysc_reinit_module(ddata, ddata->needs_resume);
		अगर (error)
			dev_warn(dev, "noirq_resume failed: %i\n", error);
	पूर्ण अन्यथा अगर (ddata->needs_resume) अणु
		error = sysc_runसमय_resume(dev);
		अगर (error)
			dev_warn(dev, "noirq_resume failed: %i\n", error);
	पूर्ण

	ddata->needs_resume = 0;

	वापस error;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sysc_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(sysc_noirq_suspend, sysc_noirq_resume)
	SET_RUNTIME_PM_OPS(sysc_runसमय_suspend,
			   sysc_runसमय_resume,
			   शून्य)
पूर्ण;

/* Module revision रेजिस्टर based quirks */
काष्ठा sysc_revision_quirk अणु
	स्थिर अक्षर *name;
	u32 base;
	पूर्णांक rev_offset;
	पूर्णांक sysc_offset;
	पूर्णांक syss_offset;
	u32 revision;
	u32 revision_mask;
	u32 quirks;
पूर्ण;

#घोषणा SYSC_QUIRK(optname, optbase, optrev, optsysc, optsyss,		\
		   optrev_val, optrevmask, optquirkmask)		\
	अणु								\
		.name = (optname),					\
		.base = (optbase),					\
		.rev_offset = (optrev),					\
		.sysc_offset = (optsysc),				\
		.syss_offset = (optsyss),				\
		.revision = (optrev_val),				\
		.revision_mask = (optrevmask),				\
		.quirks = (optquirkmask),				\
	पूर्ण

अटल स्थिर काष्ठा sysc_revision_quirk sysc_revision_quirks[] = अणु
	/* These drivers need to be fixed to not use pm_runसमय_irq_safe() */
	SYSC_QUIRK("gpio", 0, 0, 0x10, 0x114, 0x50600801, 0xffff00ff,
		   SYSC_QUIRK_LEGACY_IDLE | SYSC_QUIRK_OPT_CLKS_IN_RESET),
	SYSC_QUIRK("sham", 0, 0x100, 0x110, 0x114, 0x40000c03, 0xffffffff,
		   SYSC_QUIRK_LEGACY_IDLE),
	SYSC_QUIRK("smartreflex", 0, -ENODEV, 0x24, -ENODEV, 0x00000000, 0xffffffff,
		   SYSC_QUIRK_LEGACY_IDLE),
	SYSC_QUIRK("smartreflex", 0, -ENODEV, 0x38, -ENODEV, 0x00000000, 0xffffffff,
		   SYSC_QUIRK_LEGACY_IDLE),
	SYSC_QUIRK("uart", 0, 0x50, 0x54, 0x58, 0x00000046, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_LEGACY_IDLE),
	SYSC_QUIRK("uart", 0, 0x50, 0x54, 0x58, 0x00000052, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_LEGACY_IDLE),
	/* Uarts on omap4 and later */
	SYSC_QUIRK("uart", 0, 0x50, 0x54, 0x58, 0x50411e03, 0xffff00ff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_LEGACY_IDLE),
	SYSC_QUIRK("uart", 0, 0x50, 0x54, 0x58, 0x47422e03, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_LEGACY_IDLE),

	/* Quirks that need to be set based on the module address */
	SYSC_QUIRK("mcpdm", 0x40132000, 0, 0x10, -ENODEV, 0x50000800, 0xffffffff,
		   SYSC_QUIRK_EXT_OPT_CLOCK | SYSC_QUIRK_NO_RESET_ON_INIT |
		   SYSC_QUIRK_SWSUP_SIDLE),

	/* Quirks that need to be set based on detected module */
	SYSC_QUIRK("aess", 0, 0, 0x10, -ENODEV, 0x40000000, 0xffffffff,
		   SYSC_MODULE_QUIRK_AESS),
	SYSC_QUIRK("dcan", 0x48480000, 0x20, -ENODEV, -ENODEV, 0xa3170504, 0xffffffff,
		   SYSC_QUIRK_CLKDM_NOAUTO),
	SYSC_QUIRK("dss", 0x4832a000, 0, 0x10, 0x14, 0x00000020, 0xffffffff,
		   SYSC_QUIRK_OPT_CLKS_IN_RESET | SYSC_MODULE_QUIRK_DSS_RESET),
	SYSC_QUIRK("dss", 0x58000000, 0, -ENODEV, 0x14, 0x00000040, 0xffffffff,
		   SYSC_QUIRK_OPT_CLKS_IN_RESET | SYSC_MODULE_QUIRK_DSS_RESET),
	SYSC_QUIRK("dss", 0x58000000, 0, -ENODEV, 0x14, 0x00000061, 0xffffffff,
		   SYSC_QUIRK_OPT_CLKS_IN_RESET | SYSC_MODULE_QUIRK_DSS_RESET),
	SYSC_QUIRK("dwc3", 0x48880000, 0, 0x10, -ENODEV, 0x500a0200, 0xffffffff,
		   SYSC_QUIRK_CLKDM_NOAUTO),
	SYSC_QUIRK("dwc3", 0x488c0000, 0, 0x10, -ENODEV, 0x500a0200, 0xffffffff,
		   SYSC_QUIRK_CLKDM_NOAUTO),
	SYSC_QUIRK("gpmc", 0, 0, 0x10, 0x14, 0x00000060, 0xffffffff,
		   SYSC_QUIRK_GPMC_DEBUG),
	SYSC_QUIRK("hdmi", 0, 0, 0x10, -ENODEV, 0x50030200, 0xffffffff,
		   SYSC_QUIRK_OPT_CLKS_NEEDED),
	SYSC_QUIRK("hdq1w", 0, 0, 0x14, 0x18, 0x00000006, 0xffffffff,
		   SYSC_MODULE_QUIRK_HDQ1W | SYSC_MODULE_QUIRK_ENA_RESETDONE),
	SYSC_QUIRK("hdq1w", 0, 0, 0x14, 0x18, 0x0000000a, 0xffffffff,
		   SYSC_MODULE_QUIRK_HDQ1W | SYSC_MODULE_QUIRK_ENA_RESETDONE),
	SYSC_QUIRK("i2c", 0, 0, 0x20, 0x10, 0x00000036, 0x000000ff,
		   SYSC_MODULE_QUIRK_I2C | SYSC_MODULE_QUIRK_ENA_RESETDONE),
	SYSC_QUIRK("i2c", 0, 0, 0x20, 0x10, 0x0000003c, 0x000000ff,
		   SYSC_MODULE_QUIRK_I2C | SYSC_MODULE_QUIRK_ENA_RESETDONE),
	SYSC_QUIRK("i2c", 0, 0, 0x20, 0x10, 0x00000040, 0x000000ff,
		   SYSC_MODULE_QUIRK_I2C | SYSC_MODULE_QUIRK_ENA_RESETDONE),
	SYSC_QUIRK("i2c", 0, 0, 0x10, 0x90, 0x5040000a, 0xfffff0f0,
		   SYSC_MODULE_QUIRK_I2C | SYSC_MODULE_QUIRK_ENA_RESETDONE),
	SYSC_QUIRK("gpu", 0x50000000, 0x14, -ENODEV, -ENODEV, 0x00010201, 0xffffffff, 0),
	SYSC_QUIRK("gpu", 0x50000000, 0xfe00, 0xfe10, -ENODEV, 0x40000000 , 0xffffffff,
		   SYSC_MODULE_QUIRK_SGX),
	SYSC_QUIRK("lcdc", 0, 0, 0x54, -ENODEV, 0x4f201000, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_SWSUP_MSTANDBY),
	SYSC_QUIRK("rtc", 0, 0x74, 0x78, -ENODEV, 0x4eb01908, 0xffff00f0,
		   SYSC_MODULE_QUIRK_RTC_UNLOCK),
	SYSC_QUIRK("tptc", 0, 0, 0x10, -ENODEV, 0x40006c00, 0xffffefff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_SWSUP_MSTANDBY),
	SYSC_QUIRK("tptc", 0, 0, -ENODEV, -ENODEV, 0x40007c00, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_SWSUP_MSTANDBY),
	SYSC_QUIRK("sata", 0, 0xfc, 0x1100, -ENODEV, 0x5e412000, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_SWSUP_MSTANDBY),
	SYSC_QUIRK("usb_host_hs", 0, 0, 0x10, 0x14, 0x50700100, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_SWSUP_MSTANDBY),
	SYSC_QUIRK("usb_host_hs", 0, 0, 0x10, -ENODEV, 0x50700101, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_SWSUP_MSTANDBY),
	SYSC_QUIRK("usb_otg_hs", 0, 0x400, 0x404, 0x408, 0x00000050,
		   0xffffffff, SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_SWSUP_MSTANDBY),
	SYSC_QUIRK("usb_otg_hs", 0, 0, 0x10, -ENODEV, 0x4ea2080d, 0xffffffff,
		   SYSC_QUIRK_SWSUP_SIDLE | SYSC_QUIRK_SWSUP_MSTANDBY |
		   SYSC_QUIRK_REINIT_ON_RESUME),
	SYSC_QUIRK("wdt", 0, 0, 0x10, 0x14, 0x502a0500, 0xfffff0f0,
		   SYSC_MODULE_QUIRK_WDT),
	/* PRUSS on am3, am4 and am5 */
	SYSC_QUIRK("pruss", 0, 0x26000, 0x26004, -ENODEV, 0x47000000, 0xff000000,
		   SYSC_MODULE_QUIRK_PRUSS),
	/* Watchकरोg on am3 and am4 */
	SYSC_QUIRK("wdt", 0x44e35000, 0, 0x10, 0x14, 0x502a0500, 0xfffff0f0,
		   SYSC_MODULE_QUIRK_WDT | SYSC_QUIRK_SWSUP_SIDLE),

#अगर_घोषित DEBUG
	SYSC_QUIRK("adc", 0, 0, 0x10, -ENODEV, 0x47300001, 0xffffffff, 0),
	SYSC_QUIRK("atl", 0, 0, -ENODEV, -ENODEV, 0x0a070100, 0xffffffff, 0),
	SYSC_QUIRK("cm", 0, 0, -ENODEV, -ENODEV, 0x40000301, 0xffffffff, 0),
	SYSC_QUIRK("control", 0, 0, 0x10, -ENODEV, 0x40000900, 0xffffffff, 0),
	SYSC_QUIRK("cpgmac", 0, 0x1200, 0x1208, 0x1204, 0x4edb1902,
		   0xffff00f0, 0),
	SYSC_QUIRK("dcan", 0, 0x20, -ENODEV, -ENODEV, 0xa3170504, 0xffffffff, 0),
	SYSC_QUIRK("dcan", 0, 0x20, -ENODEV, -ENODEV, 0x4edb1902, 0xffffffff, 0),
	SYSC_QUIRK("dispc", 0x4832a400, 0, 0x10, 0x14, 0x00000030, 0xffffffff, 0),
	SYSC_QUIRK("dispc", 0x58001000, 0, 0x10, 0x14, 0x00000040, 0xffffffff, 0),
	SYSC_QUIRK("dispc", 0x58001000, 0, 0x10, 0x14, 0x00000051, 0xffffffff, 0),
	SYSC_QUIRK("dmic", 0, 0, 0x10, -ENODEV, 0x50010000, 0xffffffff, 0),
	SYSC_QUIRK("dsi", 0x58004000, 0, 0x10, 0x14, 0x00000030, 0xffffffff, 0),
	SYSC_QUIRK("dsi", 0x58005000, 0, 0x10, 0x14, 0x00000030, 0xffffffff, 0),
	SYSC_QUIRK("dsi", 0x58005000, 0, 0x10, 0x14, 0x00000040, 0xffffffff, 0),
	SYSC_QUIRK("dsi", 0x58009000, 0, 0x10, 0x14, 0x00000040, 0xffffffff, 0),
	SYSC_QUIRK("dwc3", 0, 0, 0x10, -ENODEV, 0x500a0200, 0xffffffff, 0),
	SYSC_QUIRK("d2d", 0x4a0b6000, 0, 0x10, 0x14, 0x00000010, 0xffffffff, 0),
	SYSC_QUIRK("d2d", 0x4a0cd000, 0, 0x10, 0x14, 0x00000010, 0xffffffff, 0),
	SYSC_QUIRK("elm", 0x48080000, 0, 0x10, 0x14, 0x00000020, 0xffffffff, 0),
	SYSC_QUIRK("emif", 0, 0, -ENODEV, -ENODEV, 0x40441403, 0xffff0fff, 0),
	SYSC_QUIRK("emif", 0, 0, -ENODEV, -ENODEV, 0x50440500, 0xffffffff, 0),
	SYSC_QUIRK("epwmss", 0, 0, 0x4, -ENODEV, 0x47400001, 0xffffffff, 0),
	SYSC_QUIRK("gpu", 0, 0x1fc00, 0x1fc10, -ENODEV, 0, 0, 0),
	SYSC_QUIRK("gpu", 0, 0xfe00, 0xfe10, -ENODEV, 0x40000000 , 0xffffffff, 0),
	SYSC_QUIRK("hdmi", 0, 0, 0x10, -ENODEV, 0x50031d00, 0xffffffff, 0),
	SYSC_QUIRK("hsi", 0, 0, 0x10, 0x14, 0x50043101, 0xffffffff, 0),
	SYSC_QUIRK("iss", 0, 0, 0x10, -ENODEV, 0x40000101, 0xffffffff, 0),
	SYSC_QUIRK("keypad", 0x4a31c000, 0, 0x10, 0x14, 0x00000020, 0xffffffff, 0),
	SYSC_QUIRK("mcasp", 0, 0, 0x4, -ENODEV, 0x44306302, 0xffffffff, 0),
	SYSC_QUIRK("mcasp", 0, 0, 0x4, -ENODEV, 0x44307b02, 0xffffffff, 0),
	SYSC_QUIRK("mcbsp", 0, -ENODEV, 0x8c, -ENODEV, 0, 0, 0),
	SYSC_QUIRK("mcspi", 0, 0, 0x10, -ENODEV, 0x40300a0b, 0xffff00ff, 0),
	SYSC_QUIRK("mcspi", 0, 0, 0x110, 0x114, 0x40300a0b, 0xffffffff, 0),
	SYSC_QUIRK("mailbox", 0, 0, 0x10, -ENODEV, 0x00000400, 0xffffffff, 0),
	SYSC_QUIRK("m3", 0, 0, -ENODEV, -ENODEV, 0x5f580105, 0x0fff0f00, 0),
	SYSC_QUIRK("ocp2scp", 0, 0, 0x10, 0x14, 0x50060005, 0xfffffff0, 0),
	SYSC_QUIRK("ocp2scp", 0, 0, -ENODEV, -ENODEV, 0x50060007, 0xffffffff, 0),
	SYSC_QUIRK("padconf", 0, 0, 0x10, -ENODEV, 0x4fff0800, 0xffffffff, 0),
	SYSC_QUIRK("padconf", 0, 0, -ENODEV, -ENODEV, 0x40001100, 0xffffffff, 0),
	SYSC_QUIRK("pcie", 0x51000000, -ENODEV, -ENODEV, -ENODEV, 0, 0, 0),
	SYSC_QUIRK("pcie", 0x51800000, -ENODEV, -ENODEV, -ENODEV, 0, 0, 0),
	SYSC_QUIRK("prcm", 0, 0, -ENODEV, -ENODEV, 0x40000100, 0xffffffff, 0),
	SYSC_QUIRK("prcm", 0, 0, -ENODEV, -ENODEV, 0x00004102, 0xffffffff, 0),
	SYSC_QUIRK("prcm", 0, 0, -ENODEV, -ENODEV, 0x40000400, 0xffffffff, 0),
	SYSC_QUIRK("rfbi", 0x4832a800, 0, 0x10, 0x14, 0x00000010, 0xffffffff, 0),
	SYSC_QUIRK("rfbi", 0x58002000, 0, 0x10, 0x14, 0x00000010, 0xffffffff, 0),
	SYSC_QUIRK("scm", 0, 0, 0x10, -ENODEV, 0x40000900, 0xffffffff, 0),
	SYSC_QUIRK("scm", 0, 0, -ENODEV, -ENODEV, 0x4e8b0100, 0xffffffff, 0),
	SYSC_QUIRK("scm", 0, 0, -ENODEV, -ENODEV, 0x4f000100, 0xffffffff, 0),
	SYSC_QUIRK("scm", 0, 0, -ENODEV, -ENODEV, 0x40000900, 0xffffffff, 0),
	SYSC_QUIRK("scrm", 0, 0, -ENODEV, -ENODEV, 0x00000010, 0xffffffff, 0),
	SYSC_QUIRK("sdio", 0, 0, 0x10, -ENODEV, 0x40202301, 0xffff0ff0, 0),
	SYSC_QUIRK("sdio", 0, 0x2fc, 0x110, 0x114, 0x31010000, 0xffffffff, 0),
	SYSC_QUIRK("sdma", 0, 0, 0x2c, 0x28, 0x00010900, 0xffffffff, 0),
	SYSC_QUIRK("slimbus", 0, 0, 0x10, -ENODEV, 0x40000902, 0xffffffff, 0),
	SYSC_QUIRK("slimbus", 0, 0, 0x10, -ENODEV, 0x40002903, 0xffffffff, 0),
	SYSC_QUIRK("spinlock", 0, 0, 0x10, -ENODEV, 0x50020000, 0xffffffff, 0),
	SYSC_QUIRK("rng", 0, 0x1fe0, 0x1fe4, -ENODEV, 0x00000020, 0xffffffff, 0),
	SYSC_QUIRK("timer", 0, 0, 0x10, 0x14, 0x00000013, 0xffffffff, 0),
	SYSC_QUIRK("timer", 0, 0, 0x10, 0x14, 0x00000015, 0xffffffff, 0),
	/* Some समयrs on omap4 and later */
	SYSC_QUIRK("timer", 0, 0, 0x10, -ENODEV, 0x50002100, 0xffffffff, 0),
	SYSC_QUIRK("timer", 0, 0, 0x10, -ENODEV, 0x4fff1301, 0xffff00ff, 0),
	SYSC_QUIRK("timer32k", 0, 0, 0x4, -ENODEV, 0x00000040, 0xffffffff, 0),
	SYSC_QUIRK("timer32k", 0, 0, 0x4, -ENODEV, 0x00000011, 0xffffffff, 0),
	SYSC_QUIRK("timer32k", 0, 0, 0x4, -ENODEV, 0x00000060, 0xffffffff, 0),
	SYSC_QUIRK("tpcc", 0, 0, -ENODEV, -ENODEV, 0x40014c00, 0xffffffff, 0),
	SYSC_QUIRK("usbhstll", 0, 0, 0x10, 0x14, 0x00000004, 0xffffffff, 0),
	SYSC_QUIRK("usbhstll", 0, 0, 0x10, 0x14, 0x00000008, 0xffffffff, 0),
	SYSC_QUIRK("venc", 0x58003000, 0, -ENODEV, -ENODEV, 0x00000002, 0xffffffff, 0),
	SYSC_QUIRK("vfpe", 0, 0, 0x104, -ENODEV, 0x4d001200, 0xffffffff, 0),
#पूर्ण_अगर
पूर्ण;

/*
 * Early quirks based on module base and रेजिस्टर offsets only that are
 * needed beक्रमe the module revision can be पढ़ो
 */
अटल व्योम sysc_init_early_quirks(काष्ठा sysc *ddata)
अणु
	स्थिर काष्ठा sysc_revision_quirk *q;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sysc_revision_quirks); i++) अणु
		q = &sysc_revision_quirks[i];

		अगर (!q->base)
			जारी;

		अगर (q->base != ddata->module_pa)
			जारी;

		अगर (q->rev_offset != ddata->offsets[SYSC_REVISION])
			जारी;

		अगर (q->sysc_offset != ddata->offsets[SYSC_SYSCONFIG])
			जारी;

		अगर (q->syss_offset != ddata->offsets[SYSC_SYSSTATUS])
			जारी;

		ddata->name = q->name;
		ddata->cfg.quirks |= q->quirks;
	पूर्ण
पूर्ण

/* Quirks that also consider the revision रेजिस्टर value */
अटल व्योम sysc_init_revision_quirks(काष्ठा sysc *ddata)
अणु
	स्थिर काष्ठा sysc_revision_quirk *q;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sysc_revision_quirks); i++) अणु
		q = &sysc_revision_quirks[i];

		अगर (q->base && q->base != ddata->module_pa)
			जारी;

		अगर (q->rev_offset != ddata->offsets[SYSC_REVISION])
			जारी;

		अगर (q->sysc_offset != ddata->offsets[SYSC_SYSCONFIG])
			जारी;

		अगर (q->syss_offset != ddata->offsets[SYSC_SYSSTATUS])
			जारी;

		अगर (q->revision == ddata->revision ||
		    (q->revision & q->revision_mask) ==
		    (ddata->revision & q->revision_mask)) अणु
			ddata->name = q->name;
			ddata->cfg.quirks |= q->quirks;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * DSS needs dispc outमाला_दो disabled to reset modules. Returns mask of
 * enabled DSS पूर्णांकerrupts. Eventually we may be able to करो this on
 * dispc init rather than top-level DSS init.
 */
अटल u32 sysc_quirk_dispc(काष्ठा sysc *ddata, पूर्णांक dispc_offset,
			    bool disable)
अणु
	bool lcd_en, digit_en, lcd2_en = false, lcd3_en = false;
	स्थिर पूर्णांक lcd_en_mask = BIT(0), digit_en_mask = BIT(1);
	पूर्णांक manager_count;
	bool frameकरोnetv_irq = true;
	u32 val, irq_mask = 0;

	चयन (sysc_soc->soc) अणु
	हाल SOC_2420 ... SOC_3630:
		manager_count = 2;
		frameकरोnetv_irq = false;
		अवरोध;
	हाल SOC_4430 ... SOC_4470:
		manager_count = 3;
		अवरोध;
	हाल SOC_5430:
	हाल SOC_DRA7:
		manager_count = 4;
		अवरोध;
	हाल SOC_AM4:
		manager_count = 1;
		frameकरोnetv_irq = false;
		अवरोध;
	हाल SOC_UNKNOWN:
	शेष:
		वापस 0;
	पूर्ण

	/* Remap the whole module range to be able to reset dispc outमाला_दो */
	devm_iounmap(ddata->dev, ddata->module_va);
	ddata->module_va = devm_ioremap(ddata->dev,
					ddata->module_pa,
					ddata->module_size);
	अगर (!ddata->module_va)
		वापस -EIO;

	/* DISP_CONTROL */
	val = sysc_पढ़ो(ddata, dispc_offset + 0x40);
	lcd_en = val & lcd_en_mask;
	digit_en = val & digit_en_mask;
	अगर (lcd_en)
		irq_mask |= BIT(0);			/* FRAMEDONE */
	अगर (digit_en) अणु
		अगर (frameकरोnetv_irq)
			irq_mask |= BIT(24);		/* FRAMEDONETV */
		अन्यथा
			irq_mask |= BIT(2) | BIT(3);	/* EVSYNC bits */
	पूर्ण
	अगर (disable & (lcd_en | digit_en))
		sysc_ग_लिखो(ddata, dispc_offset + 0x40,
			   val & ~(lcd_en_mask | digit_en_mask));

	अगर (manager_count <= 2)
		वापस irq_mask;

	/* DISPC_CONTROL2 */
	val = sysc_पढ़ो(ddata, dispc_offset + 0x238);
	lcd2_en = val & lcd_en_mask;
	अगर (lcd2_en)
		irq_mask |= BIT(22);			/* FRAMEDONE2 */
	अगर (disable && lcd2_en)
		sysc_ग_लिखो(ddata, dispc_offset + 0x238,
			   val & ~lcd_en_mask);

	अगर (manager_count <= 3)
		वापस irq_mask;

	/* DISPC_CONTROL3 */
	val = sysc_पढ़ो(ddata, dispc_offset + 0x848);
	lcd3_en = val & lcd_en_mask;
	अगर (lcd3_en)
		irq_mask |= BIT(30);			/* FRAMEDONE3 */
	अगर (disable && lcd3_en)
		sysc_ग_लिखो(ddata, dispc_offset + 0x848,
			   val & ~lcd_en_mask);

	वापस irq_mask;
पूर्ण

/* DSS needs child outमाला_दो disabled and SDI रेजिस्टरs cleared क्रम reset */
अटल व्योम sysc_pre_reset_quirk_dss(काष्ठा sysc *ddata)
अणु
	स्थिर पूर्णांक dispc_offset = 0x1000;
	पूर्णांक error;
	u32 irq_mask, val;

	/* Get enabled outमाला_दो */
	irq_mask = sysc_quirk_dispc(ddata, dispc_offset, false);
	अगर (!irq_mask)
		वापस;

	/* Clear IRQSTATUS */
	sysc_ग_लिखो(ddata, dispc_offset + 0x18, irq_mask);

	/* Disable outमाला_दो */
	val = sysc_quirk_dispc(ddata, dispc_offset, true);

	/* Poll IRQSTATUS */
	error = पढ़ोl_poll_समयout(ddata->module_va + dispc_offset + 0x18,
				   val, val != irq_mask, 100, 50);
	अगर (error)
		dev_warn(ddata->dev, "%s: timed out %08x !+ %08x\n",
			 __func__, val, irq_mask);

	अगर (sysc_soc->soc == SOC_3430) अणु
		/* Clear DSS_SDI_CONTROL */
		sysc_ग_लिखो(ddata, 0x44, 0);

		/* Clear DSS_PLL_CONTROL */
		sysc_ग_लिखो(ddata, 0x48, 0);
	पूर्ण

	/* Clear DSS_CONTROL to चयन DSS घड़ी sources to PRCM अगर not */
	sysc_ग_लिखो(ddata, 0x40, 0);
पूर्ण

/* 1-wire needs module's पूर्णांकernal घड़ीs enabled क्रम reset */
अटल व्योम sysc_pre_reset_quirk_hdq1w(काष्ठा sysc *ddata)
अणु
	पूर्णांक offset = 0x0c;	/* HDQ_CTRL_STATUS */
	u16 val;

	val = sysc_पढ़ो(ddata, offset);
	val |= BIT(5);
	sysc_ग_लिखो(ddata, offset, val);
पूर्ण

/* AESS (Audio Engine SubSystem) needs स्वतःgating set after enable */
अटल व्योम sysc_module_enable_quirk_aess(काष्ठा sysc *ddata)
अणु
	पूर्णांक offset = 0x7c;	/* AESS_AUTO_GATING_ENABLE */

	sysc_ग_लिखो(ddata, offset, 1);
पूर्ण

/* I2C needs to be disabled क्रम reset */
अटल व्योम sysc_clk_quirk_i2c(काष्ठा sysc *ddata, bool enable)
अणु
	पूर्णांक offset;
	u16 val;

	/* I2C_CON, omap2/3 is dअगरferent from omap4 and later */
	अगर ((ddata->revision & 0xffffff00) == 0x001f0000)
		offset = 0x24;
	अन्यथा
		offset = 0xa4;

	/* I2C_EN */
	val = sysc_पढ़ो(ddata, offset);
	अगर (enable)
		val |= BIT(15);
	अन्यथा
		val &= ~BIT(15);
	sysc_ग_लिखो(ddata, offset, val);
पूर्ण

अटल व्योम sysc_pre_reset_quirk_i2c(काष्ठा sysc *ddata)
अणु
	sysc_clk_quirk_i2c(ddata, false);
पूर्ण

अटल व्योम sysc_post_reset_quirk_i2c(काष्ठा sysc *ddata)
अणु
	sysc_clk_quirk_i2c(ddata, true);
पूर्ण

/* RTC on am3 and 4 needs to be unlocked and locked क्रम sysconfig */
अटल व्योम sysc_quirk_rtc(काष्ठा sysc *ddata, bool lock)
अणु
	u32 val, kick0_val = 0, kick1_val = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	अगर (!lock) अणु
		kick0_val = 0x83e70b13;
		kick1_val = 0x95a4f1e0;
	पूर्ण

	local_irq_save(flags);
	/* RTC_STATUS BUSY bit may stay active क्रम 1/32768 seconds (~30 usec) */
	error = पढ़ोl_poll_समयout_atomic(ddata->module_va + 0x44, val,
					  !(val & BIT(0)), 100, 50);
	अगर (error)
		dev_warn(ddata->dev, "rtc busy timeout\n");
	/* Now we have ~15 microseconds to पढ़ो/ग_लिखो various रेजिस्टरs */
	sysc_ग_लिखो(ddata, 0x6c, kick0_val);
	sysc_ग_लिखो(ddata, 0x70, kick1_val);
	local_irq_restore(flags);
पूर्ण

अटल व्योम sysc_module_unlock_quirk_rtc(काष्ठा sysc *ddata)
अणु
	sysc_quirk_rtc(ddata, false);
पूर्ण

अटल व्योम sysc_module_lock_quirk_rtc(काष्ठा sysc *ddata)
अणु
	sysc_quirk_rtc(ddata, true);
पूर्ण

/* 36xx SGX needs a quirk क्रम to bypass OCP IPG पूर्णांकerrupt logic */
अटल व्योम sysc_module_enable_quirk_sgx(काष्ठा sysc *ddata)
अणु
	पूर्णांक offset = 0xff08;	/* OCP_DEBUG_CONFIG */
	u32 val = BIT(31);	/* THALIA_INT_BYPASS */

	sysc_ग_लिखो(ddata, offset, val);
पूर्ण

/* Watchकरोg समयr needs a disable sequence after reset */
अटल व्योम sysc_reset_करोne_quirk_wdt(काष्ठा sysc *ddata)
अणु
	पूर्णांक wps, spr, error;
	u32 val;

	wps = 0x34;
	spr = 0x48;

	sysc_ग_लिखो(ddata, spr, 0xaaaa);
	error = पढ़ोl_poll_समयout(ddata->module_va + wps, val,
				   !(val & 0x10), 100,
				   MAX_MODULE_SOFTRESET_WAIT);
	अगर (error)
		dev_warn(ddata->dev, "wdt disable step1 failed\n");

	sysc_ग_लिखो(ddata, spr, 0x5555);
	error = पढ़ोl_poll_समयout(ddata->module_va + wps, val,
				   !(val & 0x10), 100,
				   MAX_MODULE_SOFTRESET_WAIT);
	अगर (error)
		dev_warn(ddata->dev, "wdt disable step2 failed\n");
पूर्ण

/* PRUSS needs to set MSTANDBY_INIT inorder to idle properly */
अटल व्योम sysc_module_disable_quirk_pruss(काष्ठा sysc *ddata)
अणु
	u32 reg;

	reg = sysc_पढ़ो(ddata, ddata->offsets[SYSC_SYSCONFIG]);
	reg |= SYSC_PRUSS_STANDBY_INIT;
	sysc_ग_लिखो(ddata, ddata->offsets[SYSC_SYSCONFIG], reg);
पूर्ण

अटल व्योम sysc_init_module_quirks(काष्ठा sysc *ddata)
अणु
	अगर (ddata->legacy_mode || !ddata->name)
		वापस;

	अगर (ddata->cfg.quirks & SYSC_MODULE_QUIRK_HDQ1W) अणु
		ddata->pre_reset_quirk = sysc_pre_reset_quirk_hdq1w;

		वापस;
	पूर्ण

#अगर_घोषित CONFIG_OMAP_GPMC_DEBUG
	अगर (ddata->cfg.quirks & SYSC_QUIRK_GPMC_DEBUG) अणु
		ddata->cfg.quirks |= SYSC_QUIRK_NO_RESET_ON_INIT;

		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (ddata->cfg.quirks & SYSC_MODULE_QUIRK_I2C) अणु
		ddata->pre_reset_quirk = sysc_pre_reset_quirk_i2c;
		ddata->post_reset_quirk = sysc_post_reset_quirk_i2c;

		वापस;
	पूर्ण

	अगर (ddata->cfg.quirks & SYSC_MODULE_QUIRK_AESS)
		ddata->module_enable_quirk = sysc_module_enable_quirk_aess;

	अगर (ddata->cfg.quirks & SYSC_MODULE_QUIRK_DSS_RESET)
		ddata->pre_reset_quirk = sysc_pre_reset_quirk_dss;

	अगर (ddata->cfg.quirks & SYSC_MODULE_QUIRK_RTC_UNLOCK) अणु
		ddata->module_unlock_quirk = sysc_module_unlock_quirk_rtc;
		ddata->module_lock_quirk = sysc_module_lock_quirk_rtc;

		वापस;
	पूर्ण

	अगर (ddata->cfg.quirks & SYSC_MODULE_QUIRK_SGX)
		ddata->module_enable_quirk = sysc_module_enable_quirk_sgx;

	अगर (ddata->cfg.quirks & SYSC_MODULE_QUIRK_WDT) अणु
		ddata->reset_करोne_quirk = sysc_reset_करोne_quirk_wdt;
		ddata->module_disable_quirk = sysc_reset_करोne_quirk_wdt;
	पूर्ण

	अगर (ddata->cfg.quirks & SYSC_MODULE_QUIRK_PRUSS)
		ddata->module_disable_quirk = sysc_module_disable_quirk_pruss;
पूर्ण

अटल पूर्णांक sysc_घड़ीकरोमुख्य_init(काष्ठा sysc *ddata)
अणु
	काष्ठा ti_sysc_platक्रमm_data *pdata = dev_get_platdata(ddata->dev);
	काष्ठा clk *fck = शून्य, *ick = शून्य;
	पूर्णांक error;

	अगर (!pdata || !pdata->init_घड़ीकरोमुख्य)
		वापस 0;

	चयन (ddata->nr_घड़ीs) अणु
	हाल 2:
		ick = ddata->घड़ीs[SYSC_ICK];
		fallthrough;
	हाल 1:
		fck = ddata->घड़ीs[SYSC_FCK];
		अवरोध;
	हाल 0:
		वापस 0;
	पूर्ण

	error = pdata->init_घड़ीकरोमुख्य(ddata->dev, fck, ick, &ddata->cookie);
	अगर (!error || error == -ENODEV)
		वापस 0;

	वापस error;
पूर्ण

/*
 * Note that pdata->init_module() typically करोes a reset first. After
 * pdata->init_module() is करोne, PM runसमय can be used क्रम the पूर्णांकerconnect
 * target module.
 */
अटल पूर्णांक sysc_legacy_init(काष्ठा sysc *ddata)
अणु
	काष्ठा ti_sysc_platक्रमm_data *pdata = dev_get_platdata(ddata->dev);
	पूर्णांक error;

	अगर (!pdata || !pdata->init_module)
		वापस 0;

	error = pdata->init_module(ddata->dev, ddata->mdata, &ddata->cookie);
	अगर (error == -EEXIST)
		error = 0;

	वापस error;
पूर्ण

/*
 * Note that the caller must ensure the पूर्णांकerconnect target module is enabled
 * beक्रमe calling reset. Otherwise reset will not complete.
 */
अटल पूर्णांक sysc_reset(काष्ठा sysc *ddata)
अणु
	पूर्णांक sysc_offset, sysc_val, error;
	u32 sysc_mask;

	sysc_offset = ddata->offsets[SYSC_SYSCONFIG];

	अगर (ddata->legacy_mode ||
	    ddata->cap->regbits->srst_shअगरt < 0 ||
	    ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT)
		वापस 0;

	sysc_mask = BIT(ddata->cap->regbits->srst_shअगरt);

	अगर (ddata->pre_reset_quirk)
		ddata->pre_reset_quirk(ddata);

	अगर (sysc_offset >= 0) अणु
		sysc_val = sysc_पढ़ो_sysconfig(ddata);
		sysc_val |= sysc_mask;
		sysc_ग_लिखो(ddata, sysc_offset, sysc_val);
	पूर्ण

	अगर (ddata->cfg.srst_udelay)
		usleep_range(ddata->cfg.srst_udelay,
			     ddata->cfg.srst_udelay * 2);

	अगर (ddata->post_reset_quirk)
		ddata->post_reset_quirk(ddata);

	error = sysc_रुको_softreset(ddata);
	अगर (error)
		dev_warn(ddata->dev, "OCP softreset timed out\n");

	अगर (ddata->reset_करोne_quirk)
		ddata->reset_करोne_quirk(ddata);

	वापस error;
पूर्ण

/*
 * At this poपूर्णांक the module is configured enough to पढ़ो the revision but
 * module may not be completely configured yet to use PM runसमय. Enable
 * all घड़ीs directly during init to configure the quirks needed क्रम PM
 * runसमय based on the revision रेजिस्टर.
 */
अटल पूर्णांक sysc_init_module(काष्ठा sysc *ddata)
अणु
	bool rstctrl_deनिश्चितed = false;
	पूर्णांक error = 0;

	error = sysc_घड़ीकरोमुख्य_init(ddata);
	अगर (error)
		वापस error;

	sysc_clkdm_deny_idle(ddata);

	/*
	 * Always enable घड़ीs. The bootloader may or may not have enabled
	 * the related घड़ीs.
	 */
	error = sysc_enable_opt_घड़ीs(ddata);
	अगर (error)
		वापस error;

	error = sysc_enable_मुख्य_घड़ीs(ddata);
	अगर (error)
		जाओ err_opt_घड़ीs;

	अगर (!(ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT)) अणु
		error = reset_control_deनिश्चित(ddata->rsts);
		अगर (error)
			जाओ err_मुख्य_घड़ीs;
		rstctrl_deनिश्चितed = true;
	पूर्ण

	ddata->revision = sysc_पढ़ो_revision(ddata);
	sysc_init_revision_quirks(ddata);
	sysc_init_module_quirks(ddata);

	अगर (ddata->legacy_mode) अणु
		error = sysc_legacy_init(ddata);
		अगर (error)
			जाओ err_मुख्य_घड़ीs;
	पूर्ण

	अगर (!ddata->legacy_mode) अणु
		error = sysc_enable_module(ddata->dev);
		अगर (error)
			जाओ err_मुख्य_घड़ीs;
	पूर्ण

	error = sysc_reset(ddata);
	अगर (error)
		dev_err(ddata->dev, "Reset failed with %d\n", error);

	अगर (error && !ddata->legacy_mode)
		sysc_disable_module(ddata->dev);

err_मुख्य_घड़ीs:
	अगर (error)
		sysc_disable_मुख्य_घड़ीs(ddata);
err_opt_घड़ीs:
	/* No re-enable of घड़ीकरोमुख्य स्वतःidle to prevent module स्वतःidle */
	अगर (error) अणु
		sysc_disable_opt_घड़ीs(ddata);
		sysc_clkdm_allow_idle(ddata);
	पूर्ण

	अगर (error && rstctrl_deनिश्चितed &&
	    !(ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT))
		reset_control_निश्चित(ddata->rsts);

	वापस error;
पूर्ण

अटल पूर्णांक sysc_init_sysc_mask(काष्ठा sysc *ddata)
अणु
	काष्ठा device_node *np = ddata->dev->of_node;
	पूर्णांक error;
	u32 val;

	error = of_property_पढ़ो_u32(np, "ti,sysc-mask", &val);
	अगर (error)
		वापस 0;

	ddata->cfg.sysc_val = val & ddata->cap->sysc_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_init_idlemode(काष्ठा sysc *ddata, u8 *idlemodes,
			      स्थिर अक्षर *name)
अणु
	काष्ठा device_node *np = ddata->dev->of_node;
	काष्ठा property *prop;
	स्थिर __be32 *p;
	u32 val;

	of_property_क्रम_each_u32(np, name, prop, p, val) अणु
		अगर (val >= SYSC_NR_IDLEMODES) अणु
			dev_err(ddata->dev, "invalid idlemode: %i\n", val);
			वापस -EINVAL;
		पूर्ण
		*idlemodes |=  (1 << val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_init_idlemodes(काष्ठा sysc *ddata)
अणु
	पूर्णांक error;

	error = sysc_init_idlemode(ddata, &ddata->cfg.midlemodes,
				   "ti,sysc-midle");
	अगर (error)
		वापस error;

	error = sysc_init_idlemode(ddata, &ddata->cfg.sidlemodes,
				   "ti,sysc-sidle");
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

/*
 * Only some devices on omap4 and later have SYSCONFIG reset करोne
 * bit. We can detect this अगर there is no SYSSTATUS at all, or the
 * SYSTATUS bit 0 is not used. Note that some SYSSTATUS रेजिस्टरs
 * have multiple bits क्रम the child devices like OHCI and EHCI.
 * Depends on SYSC being parsed first.
 */
अटल पूर्णांक sysc_init_syss_mask(काष्ठा sysc *ddata)
अणु
	काष्ठा device_node *np = ddata->dev->of_node;
	पूर्णांक error;
	u32 val;

	error = of_property_पढ़ो_u32(np, "ti,syss-mask", &val);
	अगर (error) अणु
		अगर ((ddata->cap->type == TI_SYSC_OMAP4 ||
		     ddata->cap->type == TI_SYSC_OMAP4_TIMER) &&
		    (ddata->cfg.sysc_val & SYSC_OMAP4_SOFTRESET))
			ddata->cfg.quirks |= SYSC_QUIRK_RESET_STATUS;

		वापस 0;
	पूर्ण

	अगर (!(val & 1) && (ddata->cfg.sysc_val & SYSC_OMAP4_SOFTRESET))
		ddata->cfg.quirks |= SYSC_QUIRK_RESET_STATUS;

	ddata->cfg.syss_mask = val;

	वापस 0;
पूर्ण

/*
 * Many child device drivers need to have fck and opt घड़ीs available
 * to get the घड़ी rate क्रम device पूर्णांकernal configuration etc.
 */
अटल पूर्णांक sysc_child_add_named_घड़ी(काष्ठा sysc *ddata,
				      काष्ठा device *child,
				      स्थिर अक्षर *name)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_lookup *l;
	पूर्णांक error = 0;

	अगर (!name)
		वापस 0;

	clk = clk_get(child, name);
	अगर (!IS_ERR(clk)) अणु
		error = -EEXIST;
		जाओ put_clk;
	पूर्ण

	clk = clk_get(ddata->dev, name);
	अगर (IS_ERR(clk))
		वापस -ENODEV;

	l = clkdev_create(clk, name, dev_name(child));
	अगर (!l)
		error = -ENOMEM;
put_clk:
	clk_put(clk);

	वापस error;
पूर्ण

अटल पूर्णांक sysc_child_add_घड़ीs(काष्ठा sysc *ddata,
				 काष्ठा device *child)
अणु
	पूर्णांक i, error;

	क्रम (i = 0; i < ddata->nr_घड़ीs; i++) अणु
		error = sysc_child_add_named_घड़ी(ddata,
						   child,
						   ddata->घड़ी_roles[i]);
		अगर (error && error != -EEXIST) अणु
			dev_err(ddata->dev, "could not add child clock %s: %i\n",
				ddata->घड़ी_roles[i], error);

			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा device_type sysc_device_type = अणु
पूर्ण;

अटल काष्ठा sysc *sysc_child_to_parent(काष्ठा device *dev)
अणु
	काष्ठा device *parent = dev->parent;

	अगर (!parent || parent->type != &sysc_device_type)
		वापस शून्य;

	वापस dev_get_drvdata(parent);
पूर्ण

अटल पूर्णांक __maybe_unused sysc_child_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	पूर्णांक error;

	ddata = sysc_child_to_parent(dev);

	error = pm_generic_runसमय_suspend(dev);
	अगर (error)
		वापस error;

	अगर (!ddata->enabled)
		वापस 0;

	वापस sysc_runसमय_suspend(ddata->dev);
पूर्ण

अटल पूर्णांक __maybe_unused sysc_child_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	पूर्णांक error;

	ddata = sysc_child_to_parent(dev);

	अगर (!ddata->enabled) अणु
		error = sysc_runसमय_resume(ddata->dev);
		अगर (error < 0)
			dev_err(ddata->dev,
				"%s error: %i\n", __func__, error);
	पूर्ण

	वापस pm_generic_runसमय_resume(dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sysc_child_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	पूर्णांक error;

	ddata = sysc_child_to_parent(dev);

	dev_dbg(ddata->dev, "%s %s\n", __func__,
		ddata->name ? ddata->name : "");

	error = pm_generic_suspend_noirq(dev);
	अगर (error) अणु
		dev_err(dev, "%s error at %i: %i\n",
			__func__, __LINE__, error);

		वापस error;
	पूर्ण

	अगर (!pm_runसमय_status_suspended(dev)) अणु
		error = pm_generic_runसमय_suspend(dev);
		अगर (error) अणु
			dev_dbg(dev, "%s busy at %i: %i\n",
				__func__, __LINE__, error);

			वापस 0;
		पूर्ण

		error = sysc_runसमय_suspend(ddata->dev);
		अगर (error) अणु
			dev_err(dev, "%s error at %i: %i\n",
				__func__, __LINE__, error);

			वापस error;
		पूर्ण

		ddata->child_needs_resume = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_child_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा sysc *ddata;
	पूर्णांक error;

	ddata = sysc_child_to_parent(dev);

	dev_dbg(ddata->dev, "%s %s\n", __func__,
		ddata->name ? ddata->name : "");

	अगर (ddata->child_needs_resume) अणु
		ddata->child_needs_resume = false;

		error = sysc_runसमय_resume(ddata->dev);
		अगर (error)
			dev_err(ddata->dev,
				"%s runtime resume error: %i\n",
				__func__, error);

		error = pm_generic_runसमय_resume(dev);
		अगर (error)
			dev_err(ddata->dev,
				"%s generic runtime resume: %i\n",
				__func__, error);
	पूर्ण

	वापस pm_generic_resume_noirq(dev);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा dev_pm_करोमुख्य sysc_child_pm_करोमुख्य = अणु
	.ops = अणु
		SET_RUNTIME_PM_OPS(sysc_child_runसमय_suspend,
				   sysc_child_runसमय_resume,
				   शून्य)
		USE_PLATFORM_PM_SLEEP_OPS
		SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(sysc_child_suspend_noirq,
					      sysc_child_resume_noirq)
	पूर्ण
पूर्ण;

/**
 * sysc_legacy_idle_quirk - handle children in omap_device compatible way
 * @ddata: device driver data
 * @child: child device driver
 *
 * Allow idle क्रम child devices as करोne with _od_runसमय_suspend().
 * Otherwise many child devices will not idle because of the permanent
 * parent usecount set in pm_runसमय_irq_safe().
 *
 * Note that the दीर्घ term solution is to just modअगरy the child device
 * drivers to not set pm_runसमय_irq_safe() and then this can be just
 * dropped.
 */
अटल व्योम sysc_legacy_idle_quirk(काष्ठा sysc *ddata, काष्ठा device *child)
अणु
	अगर (ddata->cfg.quirks & SYSC_QUIRK_LEGACY_IDLE)
		dev_pm_करोमुख्य_set(child, &sysc_child_pm_करोमुख्य);
पूर्ण

अटल पूर्णांक sysc_notअगरier_call(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ event, व्योम *device)
अणु
	काष्ठा device *dev = device;
	काष्ठा sysc *ddata;
	पूर्णांक error;

	ddata = sysc_child_to_parent(dev);
	अगर (!ddata)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		error = sysc_child_add_घड़ीs(ddata, dev);
		अगर (error)
			वापस error;
		sysc_legacy_idle_quirk(ddata, dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block sysc_nb = अणु
	.notअगरier_call = sysc_notअगरier_call,
पूर्ण;

/* Device tree configured quirks */
काष्ठा sysc_dts_quirk अणु
	स्थिर अक्षर *name;
	u32 mask;
पूर्ण;

अटल स्थिर काष्ठा sysc_dts_quirk sysc_dts_quirks[] = अणु
	अणु .name = "ti,no-idle-on-init",
	  .mask = SYSC_QUIRK_NO_IDLE_ON_INIT, पूर्ण,
	अणु .name = "ti,no-reset-on-init",
	  .mask = SYSC_QUIRK_NO_RESET_ON_INIT, पूर्ण,
	अणु .name = "ti,no-idle",
	  .mask = SYSC_QUIRK_NO_IDLE, पूर्ण,
पूर्ण;

अटल व्योम sysc_parse_dts_quirks(काष्ठा sysc *ddata, काष्ठा device_node *np,
				  bool is_child)
अणु
	स्थिर काष्ठा property *prop;
	पूर्णांक i, len;

	क्रम (i = 0; i < ARRAY_SIZE(sysc_dts_quirks); i++) अणु
		स्थिर अक्षर *name = sysc_dts_quirks[i].name;

		prop = of_get_property(np, name, &len);
		अगर (!prop)
			जारी;

		ddata->cfg.quirks |= sysc_dts_quirks[i].mask;
		अगर (is_child) अणु
			dev_warn(ddata->dev,
				 "dts flag should be at module level for %s\n",
				 name);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sysc_init_dts_quirks(काष्ठा sysc *ddata)
अणु
	काष्ठा device_node *np = ddata->dev->of_node;
	पूर्णांक error;
	u32 val;

	ddata->legacy_mode = of_get_property(np, "ti,hwmods", शून्य);

	sysc_parse_dts_quirks(ddata, np, false);
	error = of_property_पढ़ो_u32(np, "ti,sysc-delay-us", &val);
	अगर (!error) अणु
		अगर (val > 255) अणु
			dev_warn(ddata->dev, "bad ti,sysc-delay-us: %i\n",
				 val);
		पूर्ण

		ddata->cfg.srst_udelay = (u8)val;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sysc_unprepare(काष्ठा sysc *ddata)
अणु
	पूर्णांक i;

	अगर (!ddata->घड़ीs)
		वापस;

	क्रम (i = 0; i < SYSC_MAX_CLOCKS; i++) अणु
		अगर (!IS_ERR_OR_शून्य(ddata->घड़ीs[i]))
			clk_unprepare(ddata->घड़ीs[i]);
	पूर्ण
पूर्ण

/*
 * Common sysc रेजिस्टर bits found on omap2, also known as type1
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap2 = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = 12,
	.sidle_shअगरt = 3,
	.clkact_shअगरt = 8,
	.emuमुक्त_shअगरt = 5,
	.enwkup_shअगरt = 2,
	.srst_shअगरt = 1,
	.स्वतःidle_shअगरt = 0,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap2 = अणु
	.type = TI_SYSC_OMAP2,
	.sysc_mask = SYSC_OMAP2_CLOCKACTIVITY | SYSC_OMAP2_EMUFREE |
		     SYSC_OMAP2_ENAWAKEUP | SYSC_OMAP2_SOFTRESET |
		     SYSC_OMAP2_AUTOIDLE,
	.regbits = &sysc_regbits_omap2,
पूर्ण;

/* All omap2 and 3 समयrs, and समयrs 1, 2 & 10 on omap 4 and 5 */
अटल स्थिर काष्ठा sysc_capabilities sysc_omap2_समयr = अणु
	.type = TI_SYSC_OMAP2_TIMER,
	.sysc_mask = SYSC_OMAP2_CLOCKACTIVITY | SYSC_OMAP2_EMUFREE |
		     SYSC_OMAP2_ENAWAKEUP | SYSC_OMAP2_SOFTRESET |
		     SYSC_OMAP2_AUTOIDLE,
	.regbits = &sysc_regbits_omap2,
	.mod_quirks = SYSC_QUIRK_USE_CLOCKACT,
पूर्ण;

/*
 * SHAM2 (SHA1/MD5) sysc found on omap3, a variant of sysc_regbits_omap2
 * with dअगरferent sidle position
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap3_sham = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = -ENODEV,
	.sidle_shअगरt = 4,
	.clkact_shअगरt = -ENODEV,
	.enwkup_shअगरt = -ENODEV,
	.srst_shअगरt = 1,
	.स्वतःidle_shअगरt = 0,
	.emuमुक्त_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap3_sham = अणु
	.type = TI_SYSC_OMAP3_SHAM,
	.sysc_mask = SYSC_OMAP2_SOFTRESET | SYSC_OMAP2_AUTOIDLE,
	.regbits = &sysc_regbits_omap3_sham,
पूर्ण;

/*
 * AES रेजिस्टर bits found on omap3 and later, a variant of
 * sysc_regbits_omap2 with dअगरferent sidle position
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap3_aes = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = -ENODEV,
	.sidle_shअगरt = 6,
	.clkact_shअगरt = -ENODEV,
	.enwkup_shअगरt = -ENODEV,
	.srst_shअगरt = 1,
	.स्वतःidle_shअगरt = 0,
	.emuमुक्त_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap3_aes = अणु
	.type = TI_SYSC_OMAP3_AES,
	.sysc_mask = SYSC_OMAP2_SOFTRESET | SYSC_OMAP2_AUTOIDLE,
	.regbits = &sysc_regbits_omap3_aes,
पूर्ण;

/*
 * Common sysc रेजिस्टर bits found on omap4, also known as type2
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap4 = अणु
	.dmadisable_shअगरt = 16,
	.midle_shअगरt = 4,
	.sidle_shअगरt = 2,
	.clkact_shअगरt = -ENODEV,
	.enwkup_shअगरt = -ENODEV,
	.emuमुक्त_shअगरt = 1,
	.srst_shअगरt = 0,
	.स्वतःidle_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap4 = अणु
	.type = TI_SYSC_OMAP4,
	.sysc_mask = SYSC_OMAP4_DMADISABLE | SYSC_OMAP4_FREEEMU |
		     SYSC_OMAP4_SOFTRESET,
	.regbits = &sysc_regbits_omap4,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap4_समयr = अणु
	.type = TI_SYSC_OMAP4_TIMER,
	.sysc_mask = SYSC_OMAP4_DMADISABLE | SYSC_OMAP4_FREEEMU |
		     SYSC_OMAP4_SOFTRESET,
	.regbits = &sysc_regbits_omap4,
पूर्ण;

/*
 * Common sysc रेजिस्टर bits found on omap4, also known as type3
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap4_simple = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = 2,
	.sidle_shअगरt = 0,
	.clkact_shअगरt = -ENODEV,
	.enwkup_shअगरt = -ENODEV,
	.srst_shअगरt = -ENODEV,
	.emuमुक्त_shअगरt = -ENODEV,
	.स्वतःidle_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap4_simple = अणु
	.type = TI_SYSC_OMAP4_SIMPLE,
	.regbits = &sysc_regbits_omap4_simple,
पूर्ण;

/*
 * SmartReflex sysc found on omap34xx
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap34xx_sr = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = -ENODEV,
	.sidle_shअगरt = -ENODEV,
	.clkact_shअगरt = 20,
	.enwkup_shअगरt = -ENODEV,
	.srst_shअगरt = -ENODEV,
	.emuमुक्त_shअगरt = -ENODEV,
	.स्वतःidle_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_34xx_sr = अणु
	.type = TI_SYSC_OMAP34XX_SR,
	.sysc_mask = SYSC_OMAP2_CLOCKACTIVITY,
	.regbits = &sysc_regbits_omap34xx_sr,
	.mod_quirks = SYSC_QUIRK_USE_CLOCKACT | SYSC_QUIRK_UNCACHED |
		      SYSC_QUIRK_LEGACY_IDLE,
पूर्ण;

/*
 * SmartReflex sysc found on omap36xx and later
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap36xx_sr = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = -ENODEV,
	.sidle_shअगरt = 24,
	.clkact_shअगरt = -ENODEV,
	.enwkup_shअगरt = 26,
	.srst_shअगरt = -ENODEV,
	.emuमुक्त_shअगरt = -ENODEV,
	.स्वतःidle_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_36xx_sr = अणु
	.type = TI_SYSC_OMAP36XX_SR,
	.sysc_mask = SYSC_OMAP3_SR_ENAWAKEUP,
	.regbits = &sysc_regbits_omap36xx_sr,
	.mod_quirks = SYSC_QUIRK_UNCACHED | SYSC_QUIRK_LEGACY_IDLE,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap4_sr = अणु
	.type = TI_SYSC_OMAP4_SR,
	.regbits = &sysc_regbits_omap36xx_sr,
	.mod_quirks = SYSC_QUIRK_LEGACY_IDLE,
पूर्ण;

/*
 * McASP रेजिस्टर bits found on omap4 and later
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap4_mcasp = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = -ENODEV,
	.sidle_shअगरt = 0,
	.clkact_shअगरt = -ENODEV,
	.enwkup_shअगरt = -ENODEV,
	.srst_shअगरt = -ENODEV,
	.emuमुक्त_shअगरt = -ENODEV,
	.स्वतःidle_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap4_mcasp = अणु
	.type = TI_SYSC_OMAP4_MCASP,
	.regbits = &sysc_regbits_omap4_mcasp,
	.mod_quirks = SYSC_QUIRK_OPT_CLKS_NEEDED,
पूर्ण;

/*
 * McASP found on dra7 and later
 */
अटल स्थिर काष्ठा sysc_capabilities sysc_dra7_mcasp = अणु
	.type = TI_SYSC_OMAP4_SIMPLE,
	.regbits = &sysc_regbits_omap4_simple,
	.mod_quirks = SYSC_QUIRK_OPT_CLKS_NEEDED,
पूर्ण;

/*
 * FS USB host found on omap4 and later
 */
अटल स्थिर काष्ठा sysc_regbits sysc_regbits_omap4_usb_host_fs = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = -ENODEV,
	.sidle_shअगरt = 24,
	.clkact_shअगरt = -ENODEV,
	.enwkup_shअगरt = 26,
	.srst_shअगरt = -ENODEV,
	.emuमुक्त_shअगरt = -ENODEV,
	.स्वतःidle_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_omap4_usb_host_fs = अणु
	.type = TI_SYSC_OMAP4_USB_HOST_FS,
	.sysc_mask = SYSC_OMAP2_ENAWAKEUP,
	.regbits = &sysc_regbits_omap4_usb_host_fs,
पूर्ण;

अटल स्थिर काष्ठा sysc_regbits sysc_regbits_dra7_mcan = अणु
	.dmadisable_shअगरt = -ENODEV,
	.midle_shअगरt = -ENODEV,
	.sidle_shअगरt = -ENODEV,
	.clkact_shअगरt = -ENODEV,
	.enwkup_shअगरt = 4,
	.srst_shअगरt = 0,
	.emuमुक्त_shअगरt = -ENODEV,
	.स्वतःidle_shअगरt = -ENODEV,
पूर्ण;

अटल स्थिर काष्ठा sysc_capabilities sysc_dra7_mcan = अणु
	.type = TI_SYSC_DRA7_MCAN,
	.sysc_mask = SYSC_DRA7_MCAN_ENAWAKEUP | SYSC_OMAP4_SOFTRESET,
	.regbits = &sysc_regbits_dra7_mcan,
	.mod_quirks = SYSS_QUIRK_RESETDONE_INVERTED,
पूर्ण;

/*
 * PRUSS found on some AM33xx, AM437x and AM57xx SoCs
 */
अटल स्थिर काष्ठा sysc_capabilities sysc_pruss = अणु
	.type = TI_SYSC_PRUSS,
	.sysc_mask = SYSC_PRUSS_STANDBY_INIT | SYSC_PRUSS_SUB_MWAIT,
	.regbits = &sysc_regbits_omap4_simple,
	.mod_quirks = SYSC_MODULE_QUIRK_PRUSS,
पूर्ण;

अटल पूर्णांक sysc_init_pdata(काष्ठा sysc *ddata)
अणु
	काष्ठा ti_sysc_platक्रमm_data *pdata = dev_get_platdata(ddata->dev);
	काष्ठा ti_sysc_module_data *mdata;

	अगर (!pdata)
		वापस 0;

	mdata = devm_kzalloc(ddata->dev, माप(*mdata), GFP_KERNEL);
	अगर (!mdata)
		वापस -ENOMEM;

	अगर (ddata->legacy_mode) अणु
		mdata->name = ddata->legacy_mode;
		mdata->module_pa = ddata->module_pa;
		mdata->module_size = ddata->module_size;
		mdata->offsets = ddata->offsets;
		mdata->nr_offsets = SYSC_MAX_REGS;
		mdata->cap = ddata->cap;
		mdata->cfg = &ddata->cfg;
	पूर्ण

	ddata->mdata = mdata;

	वापस 0;
पूर्ण

अटल पूर्णांक sysc_init_match(काष्ठा sysc *ddata)
अणु
	स्थिर काष्ठा sysc_capabilities *cap;

	cap = of_device_get_match_data(ddata->dev);
	अगर (!cap)
		वापस -EINVAL;

	ddata->cap = cap;
	अगर (ddata->cap)
		ddata->cfg.quirks |= ddata->cap->mod_quirks;

	वापस 0;
पूर्ण

अटल व्योम ti_sysc_idle(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sysc *ddata;

	ddata = container_of(work, काष्ठा sysc, idle_work.work);

	/*
	 * One समय decrement of घड़ी usage counts अगर left on from init.
	 * Note that we disable opt घड़ीs unconditionally in this हाल
	 * as they are enabled unconditionally during init without
	 * considering sysc_opt_clks_needed() at that poपूर्णांक.
	 */
	अगर (ddata->cfg.quirks & (SYSC_QUIRK_NO_IDLE |
				 SYSC_QUIRK_NO_IDLE_ON_INIT)) अणु
		sysc_disable_मुख्य_घड़ीs(ddata);
		sysc_disable_opt_घड़ीs(ddata);
		sysc_clkdm_allow_idle(ddata);
	पूर्ण

	/* Keep permanent PM runसमय usage count क्रम SYSC_QUIRK_NO_IDLE */
	अगर (ddata->cfg.quirks & SYSC_QUIRK_NO_IDLE)
		वापस;

	/*
	 * Decrement PM runसमय usage count क्रम SYSC_QUIRK_NO_IDLE_ON_INIT
	 * and SYSC_QUIRK_NO_RESET_ON_INIT
	 */
	अगर (pm_runसमय_active(ddata->dev))
		pm_runसमय_put_sync(ddata->dev);
पूर्ण

/*
 * SoC model and features detection. Only needed क्रम SoCs that need
 * special handling क्रम quirks, no need to list others.
 */
अटल स्थिर काष्ठा soc_device_attribute sysc_soc_match[] = अणु
	SOC_FLAG("OMAP242*", SOC_2420),
	SOC_FLAG("OMAP243*", SOC_2430),
	SOC_FLAG("OMAP3[45]*", SOC_3430),
	SOC_FLAG("OMAP3[67]*", SOC_3630),
	SOC_FLAG("OMAP443*", SOC_4430),
	SOC_FLAG("OMAP446*", SOC_4460),
	SOC_FLAG("OMAP447*", SOC_4470),
	SOC_FLAG("OMAP54*", SOC_5430),
	SOC_FLAG("AM433", SOC_AM3),
	SOC_FLAG("AM43*", SOC_AM4),
	SOC_FLAG("DRA7*", SOC_DRA7),

	अणु /* sentinel */ पूर्ण,
पूर्ण;

/*
 * List of SoCs variants with disabled features. By शेष we assume all
 * devices in the device tree are available so no need to list those SoCs.
 */
अटल स्थिर काष्ठा soc_device_attribute sysc_soc_feat_match[] = अणु
	/* OMAP3430/3530 and AM3517 variants with some accelerators disabled */
	SOC_FLAG("AM3505", DIS_SGX),
	SOC_FLAG("OMAP3525", DIS_SGX),
	SOC_FLAG("OMAP3515", DIS_IVA | DIS_SGX),
	SOC_FLAG("OMAP3503", DIS_ISP | DIS_IVA | DIS_SGX),

	/* OMAP3630/DM3730 variants with some accelerators disabled */
	SOC_FLAG("AM3703", DIS_IVA | DIS_SGX),
	SOC_FLAG("DM3725", DIS_SGX),
	SOC_FLAG("OMAP3611", DIS_ISP | DIS_IVA | DIS_SGX),
	SOC_FLAG("OMAP3615/AM3715", DIS_IVA),
	SOC_FLAG("OMAP3621", DIS_ISP),

	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक sysc_add_disabled(अचिन्हित दीर्घ base)
अणु
	काष्ठा sysc_address *disabled_module;

	disabled_module = kzalloc(माप(*disabled_module), GFP_KERNEL);
	अगर (!disabled_module)
		वापस -ENOMEM;

	disabled_module->base = base;

	mutex_lock(&sysc_soc->list_lock);
	list_add(&disabled_module->node, &sysc_soc->disabled_modules);
	mutex_unlock(&sysc_soc->list_lock);

	वापस 0;
पूर्ण

/*
 * One समय init to detect the booted SoC and disable unavailable features.
 * Note that we initialize अटल data shared across all ti-sysc instances
 * so ddata is only used क्रम SoC type. This can be called from module_init
 * once we no दीर्घer need to rely on platक्रमm data.
 */
अटल पूर्णांक sysc_init_soc(काष्ठा sysc *ddata)
अणु
	स्थिर काष्ठा soc_device_attribute *match;
	काष्ठा ti_sysc_platक्रमm_data *pdata;
	अचिन्हित दीर्घ features = 0;
	काष्ठा device_node *np;

	अगर (sysc_soc)
		वापस 0;

	sysc_soc = kzalloc(माप(*sysc_soc), GFP_KERNEL);
	अगर (!sysc_soc)
		वापस -ENOMEM;

	mutex_init(&sysc_soc->list_lock);
	INIT_LIST_HEAD(&sysc_soc->disabled_modules);
	sysc_soc->general_purpose = true;

	pdata = dev_get_platdata(ddata->dev);
	अगर (pdata && pdata->soc_type_gp)
		sysc_soc->general_purpose = pdata->soc_type_gp();

	match = soc_device_match(sysc_soc_match);
	अगर (match && match->data)
		sysc_soc->soc = (पूर्णांक)match->data;

	/*
	 * Check and warn about possible old incomplete dtb. We now want to see
	 * simple-pm-bus instead of simple-bus in the dtb क्रम genpd using SoCs.
	 */
	चयन (sysc_soc->soc) अणु
	हाल SOC_AM3:
	हाल SOC_AM4:
	हाल SOC_4430 ... SOC_4470:
	हाल SOC_5430:
	हाल SOC_DRA7:
		np = of_find_node_by_path("/ocp");
		WARN_ONCE(np && of_device_is_compatible(np, "simple-bus"),
			  "ti-sysc: Incomplete old dtb, please update\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Ignore devices that are not available on HS and EMU SoCs */
	अगर (!sysc_soc->general_purpose) अणु
		चयन (sysc_soc->soc) अणु
		हाल SOC_3430 ... SOC_3630:
			sysc_add_disabled(0x48304000);	/* समयr12 */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	match = soc_device_match(sysc_soc_feat_match);
	अगर (!match)
		वापस 0;

	अगर (match->data)
		features = (अचिन्हित दीर्घ)match->data;

	/*
	 * Add disabled devices to the list based on the module base.
	 * Note that this must be करोne beक्रमe we attempt to access the
	 * device and have module revision checks working.
	 */
	अगर (features & DIS_ISP)
		sysc_add_disabled(0x480bd400);
	अगर (features & DIS_IVA)
		sysc_add_disabled(0x5d000000);
	अगर (features & DIS_SGX)
		sysc_add_disabled(0x50000000);

	वापस 0;
पूर्ण

अटल व्योम sysc_cleanup_soc(व्योम)
अणु
	काष्ठा sysc_address *disabled_module;
	काष्ठा list_head *pos, *पंचांगp;

	अगर (!sysc_soc)
		वापस;

	mutex_lock(&sysc_soc->list_lock);
	list_क्रम_each_safe(pos, पंचांगp, &sysc_soc->disabled_modules) अणु
		disabled_module = list_entry(pos, काष्ठा sysc_address, node);
		list_del(pos);
		kमुक्त(disabled_module);
	पूर्ण
	mutex_unlock(&sysc_soc->list_lock);
पूर्ण

अटल पूर्णांक sysc_check_disabled_devices(काष्ठा sysc *ddata)
अणु
	काष्ठा sysc_address *disabled_module;
	काष्ठा list_head *pos;
	पूर्णांक error = 0;

	mutex_lock(&sysc_soc->list_lock);
	list_क्रम_each(pos, &sysc_soc->disabled_modules) अणु
		disabled_module = list_entry(pos, काष्ठा sysc_address, node);
		अगर (ddata->module_pa == disabled_module->base) अणु
			dev_dbg(ddata->dev, "module disabled for this SoC\n");
			error = -ENODEV;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&sysc_soc->list_lock);

	वापस error;
पूर्ण

/*
 * Ignore समयrs tagged with no-reset and no-idle. These are likely in use,
 * क्रम example by drivers/घड़ीsource/समयr-ti-dm-sysसमयr.c. If more checks
 * are needed, we could also look at the समयr रेजिस्टर configuration.
 */
अटल पूर्णांक sysc_check_active_समयr(काष्ठा sysc *ddata)
अणु
	अगर (ddata->cap->type != TI_SYSC_OMAP2_TIMER &&
	    ddata->cap->type != TI_SYSC_OMAP4_TIMER)
		वापस 0;

	अगर ((ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT) &&
	    (ddata->cfg.quirks & SYSC_QUIRK_NO_IDLE))
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sysc_match_table[] = अणु
	अणु .compatible = "simple-bus", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक sysc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_sysc_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा sysc *ddata;
	पूर्णांक error;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->offsets[SYSC_REVISION] = -ENODEV;
	ddata->offsets[SYSC_SYSCONFIG] = -ENODEV;
	ddata->offsets[SYSC_SYSSTATUS] = -ENODEV;
	ddata->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ddata);

	error = sysc_init_soc(ddata);
	अगर (error)
		वापस error;

	error = sysc_init_match(ddata);
	अगर (error)
		वापस error;

	error = sysc_init_dts_quirks(ddata);
	अगर (error)
		वापस error;

	error = sysc_map_and_check_रेजिस्टरs(ddata);
	अगर (error)
		वापस error;

	error = sysc_init_sysc_mask(ddata);
	अगर (error)
		वापस error;

	error = sysc_init_idlemodes(ddata);
	अगर (error)
		वापस error;

	error = sysc_init_syss_mask(ddata);
	अगर (error)
		वापस error;

	error = sysc_init_pdata(ddata);
	अगर (error)
		वापस error;

	sysc_init_early_quirks(ddata);

	error = sysc_check_disabled_devices(ddata);
	अगर (error)
		वापस error;

	error = sysc_check_active_समयr(ddata);
	अगर (error)
		वापस error;

	error = sysc_get_घड़ीs(ddata);
	अगर (error)
		वापस error;

	error = sysc_init_resets(ddata);
	अगर (error)
		जाओ unprepare;

	error = sysc_init_module(ddata);
	अगर (error)
		जाओ unprepare;

	pm_runसमय_enable(ddata->dev);
	error = pm_runसमय_get_sync(ddata->dev);
	अगर (error < 0) अणु
		pm_runसमय_put_noidle(ddata->dev);
		pm_runसमय_disable(ddata->dev);
		जाओ unprepare;
	पूर्ण

	/* Balance use counts as PM runसमय should have enabled these all */
	अगर (!(ddata->cfg.quirks &
	      (SYSC_QUIRK_NO_IDLE | SYSC_QUIRK_NO_IDLE_ON_INIT))) अणु
		sysc_disable_मुख्य_घड़ीs(ddata);
		sysc_disable_opt_घड़ीs(ddata);
		sysc_clkdm_allow_idle(ddata);
	पूर्ण

	अगर (!(ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT))
		reset_control_निश्चित(ddata->rsts);

	sysc_show_रेजिस्टरs(ddata);

	ddata->dev->type = &sysc_device_type;
	error = of_platक्रमm_populate(ddata->dev->of_node, sysc_match_table,
				     pdata ? pdata->auxdata : शून्य,
				     ddata->dev);
	अगर (error)
		जाओ err;

	INIT_DELAYED_WORK(&ddata->idle_work, ti_sysc_idle);

	/* At least earlycon won't survive without deferred idle */
	अगर (ddata->cfg.quirks & (SYSC_QUIRK_NO_IDLE |
				 SYSC_QUIRK_NO_IDLE_ON_INIT |
				 SYSC_QUIRK_NO_RESET_ON_INIT)) अणु
		schedule_delayed_work(&ddata->idle_work, 3000);
	पूर्ण अन्यथा अणु
		pm_runसमय_put(&pdev->dev);
	पूर्ण

	वापस 0;

err:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
unprepare:
	sysc_unprepare(ddata);

	वापस error;
पूर्ण

अटल पूर्णांक sysc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sysc *ddata = platक्रमm_get_drvdata(pdev);
	पूर्णांक error;

	cancel_delayed_work_sync(&ddata->idle_work);

	error = pm_runसमय_get_sync(ddata->dev);
	अगर (error < 0) अणु
		pm_runसमय_put_noidle(ddata->dev);
		pm_runसमय_disable(ddata->dev);
		जाओ unprepare;
	पूर्ण

	of_platक्रमm_depopulate(&pdev->dev);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	अगर (!reset_control_status(ddata->rsts))
		reset_control_निश्चित(ddata->rsts);

unprepare:
	sysc_unprepare(ddata);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sysc_match[] = अणु
	अणु .compatible = "ti,sysc-omap2", .data = &sysc_omap2, पूर्ण,
	अणु .compatible = "ti,sysc-omap2-timer", .data = &sysc_omap2_समयr, पूर्ण,
	अणु .compatible = "ti,sysc-omap4", .data = &sysc_omap4, पूर्ण,
	अणु .compatible = "ti,sysc-omap4-timer", .data = &sysc_omap4_समयr, पूर्ण,
	अणु .compatible = "ti,sysc-omap4-simple", .data = &sysc_omap4_simple, पूर्ण,
	अणु .compatible = "ti,sysc-omap3430-sr", .data = &sysc_34xx_sr, पूर्ण,
	अणु .compatible = "ti,sysc-omap3630-sr", .data = &sysc_36xx_sr, पूर्ण,
	अणु .compatible = "ti,sysc-omap4-sr", .data = &sysc_omap4_sr, पूर्ण,
	अणु .compatible = "ti,sysc-omap3-sham", .data = &sysc_omap3_sham, पूर्ण,
	अणु .compatible = "ti,sysc-omap-aes", .data = &sysc_omap3_aes, पूर्ण,
	अणु .compatible = "ti,sysc-mcasp", .data = &sysc_omap4_mcasp, पूर्ण,
	अणु .compatible = "ti,sysc-dra7-mcasp", .data = &sysc_dra7_mcasp, पूर्ण,
	अणु .compatible = "ti,sysc-usb-host-fs",
	  .data = &sysc_omap4_usb_host_fs, पूर्ण,
	अणु .compatible = "ti,sysc-dra7-mcan", .data = &sysc_dra7_mcan, पूर्ण,
	अणु .compatible = "ti,sysc-pruss", .data = &sysc_pruss, पूर्ण,
	अणु  पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sysc_match);

अटल काष्ठा platक्रमm_driver sysc_driver = अणु
	.probe		= sysc_probe,
	.हटाओ		= sysc_हटाओ,
	.driver         = अणु
		.name   = "ti-sysc",
		.of_match_table	= sysc_match,
		.pm = &sysc_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sysc_init(व्योम)
अणु
	bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &sysc_nb);

	वापस platक्रमm_driver_रेजिस्टर(&sysc_driver);
पूर्ण
module_init(sysc_init);

अटल व्योम __निकास sysc_निकास(व्योम)
अणु
	bus_unरेजिस्टर_notअगरier(&platक्रमm_bus_type, &sysc_nb);
	platक्रमm_driver_unरेजिस्टर(&sysc_driver);
	sysc_cleanup_soc();
पूर्ण
module_निकास(sysc_निकास);

MODULE_DESCRIPTION("TI sysc interconnect target driver");
MODULE_LICENSE("GPL v2");
