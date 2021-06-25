<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common code क्रम Intel Running Average Power Limit (RAPL) support.
 * Copyright (c) 2019, Intel Corporation.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/cpu.h>
#समावेश <linux/घातercap.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पूर्णांकel_rapl.h>
#समावेश <linux/processor.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/iosf_mbi.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

/* biपंचांगasks क्रम RAPL MSRs, used by primitive access functions */
#घोषणा ENERGY_STATUS_MASK      0xffffffff

#घोषणा POWER_LIMIT1_MASK       0x7FFF
#घोषणा POWER_LIMIT1_ENABLE     BIT(15)
#घोषणा POWER_LIMIT1_CLAMP      BIT(16)

#घोषणा POWER_LIMIT2_MASK       (0x7FFFULL<<32)
#घोषणा POWER_LIMIT2_ENABLE     BIT_ULL(47)
#घोषणा POWER_LIMIT2_CLAMP      BIT_ULL(48)
#घोषणा POWER_HIGH_LOCK         BIT_ULL(63)
#घोषणा POWER_LOW_LOCK          BIT(31)

#घोषणा POWER_LIMIT4_MASK		0x1FFF

#घोषणा TIME_WINDOW1_MASK       (0x7FULL<<17)
#घोषणा TIME_WINDOW2_MASK       (0x7FULL<<49)

#घोषणा POWER_UNIT_OFFSET	0
#घोषणा POWER_UNIT_MASK		0x0F

#घोषणा ENERGY_UNIT_OFFSET	0x08
#घोषणा ENERGY_UNIT_MASK	0x1F00

#घोषणा TIME_UNIT_OFFSET	0x10
#घोषणा TIME_UNIT_MASK		0xF0000

#घोषणा POWER_INFO_MAX_MASK     (0x7fffULL<<32)
#घोषणा POWER_INFO_MIN_MASK     (0x7fffULL<<16)
#घोषणा POWER_INFO_MAX_TIME_WIN_MASK     (0x3fULL<<48)
#घोषणा POWER_INFO_THERMAL_SPEC_MASK     0x7fff

#घोषणा PERF_STATUS_THROTTLE_TIME_MASK 0xffffffff
#घोषणा PP_POLICY_MASK         0x1F

/* Non HW स्थिरants */
#घोषणा RAPL_PRIMITIVE_DERIVED       BIT(1)	/* not from raw data */
#घोषणा RAPL_PRIMITIVE_DUMMY         BIT(2)

#घोषणा TIME_WINDOW_MAX_MSEC 40000
#घोषणा TIME_WINDOW_MIN_MSEC 250
#घोषणा ENERGY_UNIT_SCALE    1000	/* scale from driver unit to घातercap unit */
क्रमागत unit_type अणु
	ARBITRARY_UNIT,		/* no translation */
	POWER_UNIT,
	ENERGY_UNIT,
	TIME_UNIT,
पूर्ण;

/* per करोमुख्य data, some are optional */
#घोषणा NR_RAW_PRIMITIVES (NR_RAPL_PRIMITIVES - 2)

#घोषणा	DOMAIN_STATE_INACTIVE           BIT(0)
#घोषणा	DOMAIN_STATE_POWER_LIMIT_SET    BIT(1)
#घोषणा DOMAIN_STATE_BIOS_LOCKED        BIT(2)

अटल स्थिर अक्षर pl1_name[] = "long_term";
अटल स्थिर अक्षर pl2_name[] = "short_term";
अटल स्थिर अक्षर pl4_name[] = "peak_power";

#घोषणा घातer_zone_to_rapl_करोमुख्य(_zone) \
	container_of(_zone, काष्ठा rapl_करोमुख्य, घातer_zone)

काष्ठा rapl_शेषs अणु
	u8 न्यूनमान_freq_reg_addr;
	पूर्णांक (*check_unit)(काष्ठा rapl_package *rp, पूर्णांक cpu);
	व्योम (*set_न्यूनमान_freq)(काष्ठा rapl_करोमुख्य *rd, bool mode);
	u64 (*compute_समय_winकरोw)(काष्ठा rapl_package *rp, u64 val,
				    bool to_raw);
	अचिन्हित पूर्णांक dram_करोमुख्य_energy_unit;
	अचिन्हित पूर्णांक psys_करोमुख्य_energy_unit;
पूर्ण;
अटल काष्ठा rapl_शेषs *rapl_शेषs;

/* Sideband MBI रेजिस्टरs */
#घोषणा IOSF_CPU_POWER_BUDGET_CTL_BYT (0x2)
#घोषणा IOSF_CPU_POWER_BUDGET_CTL_TNG (0xdf)

#घोषणा PACKAGE_PLN_INT_SAVED   BIT(0)
#घोषणा MAX_PRIM_NAME (32)

/* per करोमुख्य data. used to describe inभागidual knobs such that access function
 * can be consolidated पूर्णांकo one instead of many अंतरभूत functions.
 */
काष्ठा rapl_primitive_info अणु
	स्थिर अक्षर *name;
	u64 mask;
	पूर्णांक shअगरt;
	क्रमागत rapl_करोमुख्य_reg_id id;
	क्रमागत unit_type unit;
	u32 flag;
पूर्ण;

#घोषणा PRIMITIVE_INFO_INIT(p, m, s, i, u, f) अणु	\
		.name = #p,			\
		.mask = m,			\
		.shअगरt = s,			\
		.id = i,			\
		.unit = u,			\
		.flag = f			\
	पूर्ण

अटल व्योम rapl_init_करोमुख्यs(काष्ठा rapl_package *rp);
अटल पूर्णांक rapl_पढ़ो_data_raw(काष्ठा rapl_करोमुख्य *rd,
			      क्रमागत rapl_primitives prim,
			      bool xlate, u64 *data);
अटल पूर्णांक rapl_ग_लिखो_data_raw(काष्ठा rapl_करोमुख्य *rd,
			       क्रमागत rapl_primitives prim,
			       अचिन्हित दीर्घ दीर्घ value);
अटल u64 rapl_unit_xlate(काष्ठा rapl_करोमुख्य *rd,
			   क्रमागत unit_type type, u64 value, पूर्णांक to_raw);
अटल व्योम package_घातer_limit_irq_save(काष्ठा rapl_package *rp);

अटल LIST_HEAD(rapl_packages);	/* guarded by CPU hotplug lock */

अटल स्थिर अक्षर *स्थिर rapl_करोमुख्य_names[] = अणु
	"package",
	"core",
	"uncore",
	"dram",
	"psys",
पूर्ण;

अटल पूर्णांक get_energy_counter(काष्ठा घातercap_zone *घातer_zone,
			      u64 *energy_raw)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	u64 energy_now;

	/* prevent CPU hotplug, make sure the RAPL करोमुख्य करोes not go
	 * away जबतक पढ़ोing the counter.
	 */
	get_online_cpus();
	rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);

	अगर (!rapl_पढ़ो_data_raw(rd, ENERGY_COUNTER, true, &energy_now)) अणु
		*energy_raw = energy_now;
		put_online_cpus();

		वापस 0;
	पूर्ण
	put_online_cpus();

	वापस -EIO;
पूर्ण

अटल पूर्णांक get_max_energy_counter(काष्ठा घातercap_zone *pcd_dev, u64 *energy)
अणु
	काष्ठा rapl_करोमुख्य *rd = घातer_zone_to_rapl_करोमुख्य(pcd_dev);

	*energy = rapl_unit_xlate(rd, ENERGY_UNIT, ENERGY_STATUS_MASK, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक release_zone(काष्ठा घातercap_zone *घातer_zone)
अणु
	काष्ठा rapl_करोमुख्य *rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);
	काष्ठा rapl_package *rp = rd->rp;

	/* package zone is the last zone of a package, we can मुक्त
	 * memory here since all children has been unरेजिस्टरed.
	 */
	अगर (rd->id == RAPL_DOMAIN_PACKAGE) अणु
		kमुक्त(rd);
		rp->करोमुख्यs = शून्य;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक find_nr_घातer_limit(काष्ठा rapl_करोमुख्य *rd)
अणु
	पूर्णांक i, nr_pl = 0;

	क्रम (i = 0; i < NR_POWER_LIMITS; i++) अणु
		अगर (rd->rpl[i].name)
			nr_pl++;
	पूर्ण

	वापस nr_pl;
पूर्ण

अटल पूर्णांक set_करोमुख्य_enable(काष्ठा घातercap_zone *घातer_zone, bool mode)
अणु
	काष्ठा rapl_करोमुख्य *rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);

	अगर (rd->state & DOMAIN_STATE_BIOS_LOCKED)
		वापस -EACCES;

	get_online_cpus();
	rapl_ग_लिखो_data_raw(rd, PL1_ENABLE, mode);
	अगर (rapl_शेषs->set_न्यूनमान_freq)
		rapl_शेषs->set_न्यूनमान_freq(rd, mode);
	put_online_cpus();

	वापस 0;
पूर्ण

अटल पूर्णांक get_करोमुख्य_enable(काष्ठा घातercap_zone *घातer_zone, bool *mode)
अणु
	काष्ठा rapl_करोमुख्य *rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);
	u64 val;

	अगर (rd->state & DOMAIN_STATE_BIOS_LOCKED) अणु
		*mode = false;
		वापस 0;
	पूर्ण
	get_online_cpus();
	अगर (rapl_पढ़ो_data_raw(rd, PL1_ENABLE, true, &val)) अणु
		put_online_cpus();
		वापस -EIO;
	पूर्ण
	*mode = val;
	put_online_cpus();

	वापस 0;
पूर्ण

/* per RAPL करोमुख्य ops, in the order of rapl_करोमुख्य_type */
अटल स्थिर काष्ठा घातercap_zone_ops zone_ops[] = अणु
	/* RAPL_DOMAIN_PACKAGE */
	अणु
	 .get_energy_uj = get_energy_counter,
	 .get_max_energy_range_uj = get_max_energy_counter,
	 .release = release_zone,
	 .set_enable = set_करोमुख्य_enable,
	 .get_enable = get_करोमुख्य_enable,
	 पूर्ण,
	/* RAPL_DOMAIN_PP0 */
	अणु
	 .get_energy_uj = get_energy_counter,
	 .get_max_energy_range_uj = get_max_energy_counter,
	 .release = release_zone,
	 .set_enable = set_करोमुख्य_enable,
	 .get_enable = get_करोमुख्य_enable,
	 पूर्ण,
	/* RAPL_DOMAIN_PP1 */
	अणु
	 .get_energy_uj = get_energy_counter,
	 .get_max_energy_range_uj = get_max_energy_counter,
	 .release = release_zone,
	 .set_enable = set_करोमुख्य_enable,
	 .get_enable = get_करोमुख्य_enable,
	 पूर्ण,
	/* RAPL_DOMAIN_DRAM */
	अणु
	 .get_energy_uj = get_energy_counter,
	 .get_max_energy_range_uj = get_max_energy_counter,
	 .release = release_zone,
	 .set_enable = set_करोमुख्य_enable,
	 .get_enable = get_करोमुख्य_enable,
	 पूर्ण,
	/* RAPL_DOMAIN_PLATFORM */
	अणु
	 .get_energy_uj = get_energy_counter,
	 .get_max_energy_range_uj = get_max_energy_counter,
	 .release = release_zone,
	 .set_enable = set_करोमुख्य_enable,
	 .get_enable = get_करोमुख्य_enable,
	 पूर्ण,
पूर्ण;

/*
 * Constraपूर्णांक index used by घातercap can be dअगरferent than घातer limit (PL)
 * index in that some  PLs maybe missing due to non-existent MSRs. So we
 * need to convert here by finding the valid PLs only (name populated).
 */
अटल पूर्णांक contraपूर्णांक_to_pl(काष्ठा rapl_करोमुख्य *rd, पूर्णांक cid)
अणु
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < NR_POWER_LIMITS; i++) अणु
		अगर ((rd->rpl[i].name) && j++ == cid) अणु
			pr_debug("%s: index %d\n", __func__, i);
			वापस i;
		पूर्ण
	पूर्ण
	pr_err("Cannot find matching power limit for constraint %d\n", cid);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक set_घातer_limit(काष्ठा घातercap_zone *घातer_zone, पूर्णांक cid,
			   u64 घातer_limit)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	काष्ठा rapl_package *rp;
	पूर्णांक ret = 0;
	पूर्णांक id;

	get_online_cpus();
	rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);
	id = contraपूर्णांक_to_pl(rd, cid);
	अगर (id < 0) अणु
		ret = id;
		जाओ set_निकास;
	पूर्ण

	rp = rd->rp;

	अगर (rd->state & DOMAIN_STATE_BIOS_LOCKED) अणु
		dev_warn(&घातer_zone->dev,
			 "%s locked by BIOS, monitoring only\n", rd->name);
		ret = -EACCES;
		जाओ set_निकास;
	पूर्ण

	चयन (rd->rpl[id].prim_id) अणु
	हाल PL1_ENABLE:
		rapl_ग_लिखो_data_raw(rd, POWER_LIMIT1, घातer_limit);
		अवरोध;
	हाल PL2_ENABLE:
		rapl_ग_लिखो_data_raw(rd, POWER_LIMIT2, घातer_limit);
		अवरोध;
	हाल PL4_ENABLE:
		rapl_ग_लिखो_data_raw(rd, POWER_LIMIT4, घातer_limit);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (!ret)
		package_घातer_limit_irq_save(rp);
set_निकास:
	put_online_cpus();
	वापस ret;
पूर्ण

अटल पूर्णांक get_current_घातer_limit(काष्ठा घातercap_zone *घातer_zone, पूर्णांक cid,
				   u64 *data)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	u64 val;
	पूर्णांक prim;
	पूर्णांक ret = 0;
	पूर्णांक id;

	get_online_cpus();
	rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);
	id = contraपूर्णांक_to_pl(rd, cid);
	अगर (id < 0) अणु
		ret = id;
		जाओ get_निकास;
	पूर्ण

	चयन (rd->rpl[id].prim_id) अणु
	हाल PL1_ENABLE:
		prim = POWER_LIMIT1;
		अवरोध;
	हाल PL2_ENABLE:
		prim = POWER_LIMIT2;
		अवरोध;
	हाल PL4_ENABLE:
		prim = POWER_LIMIT4;
		अवरोध;
	शेष:
		put_online_cpus();
		वापस -EINVAL;
	पूर्ण
	अगर (rapl_पढ़ो_data_raw(rd, prim, true, &val))
		ret = -EIO;
	अन्यथा
		*data = val;

get_निकास:
	put_online_cpus();

	वापस ret;
पूर्ण

अटल पूर्णांक set_समय_winकरोw(काष्ठा घातercap_zone *घातer_zone, पूर्णांक cid,
			   u64 winकरोw)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	पूर्णांक ret = 0;
	पूर्णांक id;

	get_online_cpus();
	rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);
	id = contraपूर्णांक_to_pl(rd, cid);
	अगर (id < 0) अणु
		ret = id;
		जाओ set_समय_निकास;
	पूर्ण

	चयन (rd->rpl[id].prim_id) अणु
	हाल PL1_ENABLE:
		rapl_ग_लिखो_data_raw(rd, TIME_WINDOW1, winकरोw);
		अवरोध;
	हाल PL2_ENABLE:
		rapl_ग_लिखो_data_raw(rd, TIME_WINDOW2, winकरोw);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

set_समय_निकास:
	put_online_cpus();
	वापस ret;
पूर्ण

अटल पूर्णांक get_समय_winकरोw(काष्ठा घातercap_zone *घातer_zone, पूर्णांक cid,
			   u64 *data)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	u64 val;
	पूर्णांक ret = 0;
	पूर्णांक id;

	get_online_cpus();
	rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);
	id = contraपूर्णांक_to_pl(rd, cid);
	अगर (id < 0) अणु
		ret = id;
		जाओ get_समय_निकास;
	पूर्ण

	चयन (rd->rpl[id].prim_id) अणु
	हाल PL1_ENABLE:
		ret = rapl_पढ़ो_data_raw(rd, TIME_WINDOW1, true, &val);
		अवरोध;
	हाल PL2_ENABLE:
		ret = rapl_पढ़ो_data_raw(rd, TIME_WINDOW2, true, &val);
		अवरोध;
	हाल PL4_ENABLE:
		/*
		 * Time winकरोw parameter is not applicable क्रम PL4 entry
		 * so assigining '0' as शेष value.
		 */
		val = 0;
		अवरोध;
	शेष:
		put_online_cpus();
		वापस -EINVAL;
	पूर्ण
	अगर (!ret)
		*data = val;

get_समय_निकास:
	put_online_cpus();

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *get_स्थिरraपूर्णांक_name(काष्ठा घातercap_zone *घातer_zone,
				       पूर्णांक cid)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	पूर्णांक id;

	rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);
	id = contraपूर्णांक_to_pl(rd, cid);
	अगर (id >= 0)
		वापस rd->rpl[id].name;

	वापस शून्य;
पूर्ण

अटल पूर्णांक get_max_घातer(काष्ठा घातercap_zone *घातer_zone, पूर्णांक id, u64 *data)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	u64 val;
	पूर्णांक prim;
	पूर्णांक ret = 0;

	get_online_cpus();
	rd = घातer_zone_to_rapl_करोमुख्य(घातer_zone);
	चयन (rd->rpl[id].prim_id) अणु
	हाल PL1_ENABLE:
		prim = THERMAL_SPEC_POWER;
		अवरोध;
	हाल PL2_ENABLE:
		prim = MAX_POWER;
		अवरोध;
	हाल PL4_ENABLE:
		prim = MAX_POWER;
		अवरोध;
	शेष:
		put_online_cpus();
		वापस -EINVAL;
	पूर्ण
	अगर (rapl_पढ़ो_data_raw(rd, prim, true, &val))
		ret = -EIO;
	अन्यथा
		*data = val;

	/* As a generalization rule, PL4 would be around two बार PL2. */
	अगर (rd->rpl[id].prim_id == PL4_ENABLE)
		*data = *data * 2;

	put_online_cpus();

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा घातercap_zone_स्थिरraपूर्णांक_ops स्थिरraपूर्णांक_ops = अणु
	.set_घातer_limit_uw = set_घातer_limit,
	.get_घातer_limit_uw = get_current_घातer_limit,
	.set_समय_winकरोw_us = set_समय_winकरोw,
	.get_समय_winकरोw_us = get_समय_winकरोw,
	.get_max_घातer_uw = get_max_घातer,
	.get_name = get_स्थिरraपूर्णांक_name,
पूर्ण;

/* called after करोमुख्य detection and package level data are set */
अटल व्योम rapl_init_करोमुख्यs(काष्ठा rapl_package *rp)
अणु
	क्रमागत rapl_करोमुख्य_type i;
	क्रमागत rapl_करोमुख्य_reg_id j;
	काष्ठा rapl_करोमुख्य *rd = rp->करोमुख्यs;

	क्रम (i = 0; i < RAPL_DOMAIN_MAX; i++) अणु
		अचिन्हित पूर्णांक mask = rp->करोमुख्य_map & (1 << i);

		अगर (!mask)
			जारी;

		rd->rp = rp;

		अगर (i == RAPL_DOMAIN_PLATFORM && rp->id > 0) अणु
			snम_लिखो(rd->name, RAPL_DOMAIN_NAME_LENGTH, "psys-%d",
				topology_physical_package_id(rp->lead_cpu));
		पूर्ण अन्यथा
			snम_लिखो(rd->name, RAPL_DOMAIN_NAME_LENGTH, "%s",
				rapl_करोमुख्य_names[i]);

		rd->id = i;
		rd->rpl[0].prim_id = PL1_ENABLE;
		rd->rpl[0].name = pl1_name;

		/*
		 * The PL2 घातer करोमुख्य is applicable क्रम limits two
		 * and limits three
		 */
		अगर (rp->priv->limits[i] >= 2) अणु
			rd->rpl[1].prim_id = PL2_ENABLE;
			rd->rpl[1].name = pl2_name;
		पूर्ण

		/* Enable PL4 करोमुख्य अगर the total घातer limits are three */
		अगर (rp->priv->limits[i] == 3) अणु
			rd->rpl[2].prim_id = PL4_ENABLE;
			rd->rpl[2].name = pl4_name;
		पूर्ण

		क्रम (j = 0; j < RAPL_DOMAIN_REG_MAX; j++)
			rd->regs[j] = rp->priv->regs[i][j];

		चयन (i) अणु
		हाल RAPL_DOMAIN_DRAM:
			rd->करोमुख्य_energy_unit =
			    rapl_शेषs->dram_करोमुख्य_energy_unit;
			अगर (rd->करोमुख्य_energy_unit)
				pr_info("DRAM domain energy unit %dpj\n",
					rd->करोमुख्य_energy_unit);
			अवरोध;
		हाल RAPL_DOMAIN_PLATFORM:
			rd->करोमुख्य_energy_unit =
			    rapl_शेषs->psys_करोमुख्य_energy_unit;
			अगर (rd->करोमुख्य_energy_unit)
				pr_info("Platform domain energy unit %dpj\n",
					rd->करोमुख्य_energy_unit);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		rd++;
	पूर्ण
पूर्ण

अटल u64 rapl_unit_xlate(काष्ठा rapl_करोमुख्य *rd, क्रमागत unit_type type,
			   u64 value, पूर्णांक to_raw)
अणु
	u64 units = 1;
	काष्ठा rapl_package *rp = rd->rp;
	u64 scale = 1;

	चयन (type) अणु
	हाल POWER_UNIT:
		units = rp->घातer_unit;
		अवरोध;
	हाल ENERGY_UNIT:
		scale = ENERGY_UNIT_SCALE;
		/* per करोमुख्य unit takes precedence */
		अगर (rd->करोमुख्य_energy_unit)
			units = rd->करोमुख्य_energy_unit;
		अन्यथा
			units = rp->energy_unit;
		अवरोध;
	हाल TIME_UNIT:
		वापस rapl_शेषs->compute_समय_winकरोw(rp, value, to_raw);
	हाल ARBITRARY_UNIT:
	शेष:
		वापस value;
	पूर्ण

	अगर (to_raw)
		वापस भाग64_u64(value, units) * scale;

	value *= units;

	वापस भाग64_u64(value, scale);
पूर्ण

/* in the order of क्रमागत rapl_primitives */
अटल काष्ठा rapl_primitive_info rpi[] = अणु
	/* name, mask, shअगरt, msr index, unit भागisor */
	PRIMITIVE_INFO_INIT(ENERGY_COUNTER, ENERGY_STATUS_MASK, 0,
			    RAPL_DOMAIN_REG_STATUS, ENERGY_UNIT, 0),
	PRIMITIVE_INFO_INIT(POWER_LIMIT1, POWER_LIMIT1_MASK, 0,
			    RAPL_DOMAIN_REG_LIMIT, POWER_UNIT, 0),
	PRIMITIVE_INFO_INIT(POWER_LIMIT2, POWER_LIMIT2_MASK, 32,
			    RAPL_DOMAIN_REG_LIMIT, POWER_UNIT, 0),
	PRIMITIVE_INFO_INIT(POWER_LIMIT4, POWER_LIMIT4_MASK, 0,
				RAPL_DOMAIN_REG_PL4, POWER_UNIT, 0),
	PRIMITIVE_INFO_INIT(FW_LOCK, POWER_LOW_LOCK, 31,
			    RAPL_DOMAIN_REG_LIMIT, ARBITRARY_UNIT, 0),
	PRIMITIVE_INFO_INIT(PL1_ENABLE, POWER_LIMIT1_ENABLE, 15,
			    RAPL_DOMAIN_REG_LIMIT, ARBITRARY_UNIT, 0),
	PRIMITIVE_INFO_INIT(PL1_CLAMP, POWER_LIMIT1_CLAMP, 16,
			    RAPL_DOMAIN_REG_LIMIT, ARBITRARY_UNIT, 0),
	PRIMITIVE_INFO_INIT(PL2_ENABLE, POWER_LIMIT2_ENABLE, 47,
			    RAPL_DOMAIN_REG_LIMIT, ARBITRARY_UNIT, 0),
	PRIMITIVE_INFO_INIT(PL2_CLAMP, POWER_LIMIT2_CLAMP, 48,
			    RAPL_DOMAIN_REG_LIMIT, ARBITRARY_UNIT, 0),
	PRIMITIVE_INFO_INIT(PL4_ENABLE, POWER_LIMIT4_MASK, 0,
				RAPL_DOMAIN_REG_PL4, ARBITRARY_UNIT, 0),
	PRIMITIVE_INFO_INIT(TIME_WINDOW1, TIME_WINDOW1_MASK, 17,
			    RAPL_DOMAIN_REG_LIMIT, TIME_UNIT, 0),
	PRIMITIVE_INFO_INIT(TIME_WINDOW2, TIME_WINDOW2_MASK, 49,
			    RAPL_DOMAIN_REG_LIMIT, TIME_UNIT, 0),
	PRIMITIVE_INFO_INIT(THERMAL_SPEC_POWER, POWER_INFO_THERMAL_SPEC_MASK,
			    0, RAPL_DOMAIN_REG_INFO, POWER_UNIT, 0),
	PRIMITIVE_INFO_INIT(MAX_POWER, POWER_INFO_MAX_MASK, 32,
			    RAPL_DOMAIN_REG_INFO, POWER_UNIT, 0),
	PRIMITIVE_INFO_INIT(MIN_POWER, POWER_INFO_MIN_MASK, 16,
			    RAPL_DOMAIN_REG_INFO, POWER_UNIT, 0),
	PRIMITIVE_INFO_INIT(MAX_TIME_WINDOW, POWER_INFO_MAX_TIME_WIN_MASK, 48,
			    RAPL_DOMAIN_REG_INFO, TIME_UNIT, 0),
	PRIMITIVE_INFO_INIT(THROTTLED_TIME, PERF_STATUS_THROTTLE_TIME_MASK, 0,
			    RAPL_DOMAIN_REG_PERF, TIME_UNIT, 0),
	PRIMITIVE_INFO_INIT(PRIORITY_LEVEL, PP_POLICY_MASK, 0,
			    RAPL_DOMAIN_REG_POLICY, ARBITRARY_UNIT, 0),
	/* non-hardware */
	PRIMITIVE_INFO_INIT(AVERAGE_POWER, 0, 0, 0, POWER_UNIT,
			    RAPL_PRIMITIVE_DERIVED),
	अणुशून्य, 0, 0, 0पूर्ण,
पूर्ण;

/* Read primitive data based on its related काष्ठा rapl_primitive_info.
 * अगर xlate flag is set, वापस translated data based on data units, i.e.
 * समय, energy, and घातer.
 * RAPL MSRs are non-architectual and are laid out not consistently across
 * करोमुख्यs. Here we use primitive info to allow writing consolidated access
 * functions.
 * For a given primitive, it is processed by MSR mask and shअगरt. Unit conversion
 * is pre-asचिन्हित based on RAPL unit MSRs पढ़ो at init समय.
 * 63-------------------------- 31--------------------------- 0
 * |                           xxxxx (mask)                   |
 * |                                |<- shअगरt ----------------|
 * 63-------------------------- 31--------------------------- 0
 */
अटल पूर्णांक rapl_पढ़ो_data_raw(काष्ठा rapl_करोमुख्य *rd,
			      क्रमागत rapl_primitives prim, bool xlate, u64 *data)
अणु
	u64 value;
	काष्ठा rapl_primitive_info *rp = &rpi[prim];
	काष्ठा reg_action ra;
	पूर्णांक cpu;

	अगर (!rp->name || rp->flag & RAPL_PRIMITIVE_DUMMY)
		वापस -EINVAL;

	ra.reg = rd->regs[rp->id];
	अगर (!ra.reg)
		वापस -EINVAL;

	cpu = rd->rp->lead_cpu;

	/* करोमुख्य with 2 limits has dअगरferent bit */
	अगर (prim == FW_LOCK && rd->rp->priv->limits[rd->id] == 2) अणु
		rp->mask = POWER_HIGH_LOCK;
		rp->shअगरt = 63;
	पूर्ण
	/* non-hardware data are collected by the polling thपढ़ो */
	अगर (rp->flag & RAPL_PRIMITIVE_DERIVED) अणु
		*data = rd->rdd.primitives[prim];
		वापस 0;
	पूर्ण

	ra.mask = rp->mask;

	अगर (rd->rp->priv->पढ़ो_raw(cpu, &ra)) अणु
		pr_debug("failed to read reg 0x%llx on cpu %d\n", ra.reg, cpu);
		वापस -EIO;
	पूर्ण

	value = ra.value >> rp->shअगरt;

	अगर (xlate)
		*data = rapl_unit_xlate(rd, rp->unit, value, 0);
	अन्यथा
		*data = value;

	वापस 0;
पूर्ण

/* Similar use of primitive info in the पढ़ो counterpart */
अटल पूर्णांक rapl_ग_लिखो_data_raw(काष्ठा rapl_करोमुख्य *rd,
			       क्रमागत rapl_primitives prim,
			       अचिन्हित दीर्घ दीर्घ value)
अणु
	काष्ठा rapl_primitive_info *rp = &rpi[prim];
	पूर्णांक cpu;
	u64 bits;
	काष्ठा reg_action ra;
	पूर्णांक ret;

	cpu = rd->rp->lead_cpu;
	bits = rapl_unit_xlate(rd, rp->unit, value, 1);
	bits <<= rp->shअगरt;
	bits &= rp->mask;

	स_रखो(&ra, 0, माप(ra));

	ra.reg = rd->regs[rp->id];
	ra.mask = rp->mask;
	ra.value = bits;

	ret = rd->rp->priv->ग_लिखो_raw(cpu, &ra);

	वापस ret;
पूर्ण

/*
 * Raw RAPL data stored in MSRs are in certain scales. We need to
 * convert them पूर्णांकo standard units based on the units reported in
 * the RAPL unit MSRs. This is specअगरic to CPUs as the method to
 * calculate units dअगरfer on dअगरferent CPUs.
 * We convert the units to below क्रमmat based on CPUs.
 * i.e.
 * energy unit: picoJoules  : Represented in picoJoules by शेष
 * घातer unit : microWatts  : Represented in milliWatts by शेष
 * समय unit  : microseconds: Represented in seconds by शेष
 */
अटल पूर्णांक rapl_check_unit_core(काष्ठा rapl_package *rp, पूर्णांक cpu)
अणु
	काष्ठा reg_action ra;
	u32 value;

	ra.reg = rp->priv->reg_unit;
	ra.mask = ~0;
	अगर (rp->priv->पढ़ो_raw(cpu, &ra)) अणु
		pr_err("Failed to read power unit REG 0x%llx on CPU %d, exit.\n",
		       rp->priv->reg_unit, cpu);
		वापस -ENODEV;
	पूर्ण

	value = (ra.value & ENERGY_UNIT_MASK) >> ENERGY_UNIT_OFFSET;
	rp->energy_unit = ENERGY_UNIT_SCALE * 1000000 / (1 << value);

	value = (ra.value & POWER_UNIT_MASK) >> POWER_UNIT_OFFSET;
	rp->घातer_unit = 1000000 / (1 << value);

	value = (ra.value & TIME_UNIT_MASK) >> TIME_UNIT_OFFSET;
	rp->समय_unit = 1000000 / (1 << value);

	pr_debug("Core CPU %s energy=%dpJ, time=%dus, power=%duW\n",
		 rp->name, rp->energy_unit, rp->समय_unit, rp->घातer_unit);

	वापस 0;
पूर्ण

अटल पूर्णांक rapl_check_unit_atom(काष्ठा rapl_package *rp, पूर्णांक cpu)
अणु
	काष्ठा reg_action ra;
	u32 value;

	ra.reg = rp->priv->reg_unit;
	ra.mask = ~0;
	अगर (rp->priv->पढ़ो_raw(cpu, &ra)) अणु
		pr_err("Failed to read power unit REG 0x%llx on CPU %d, exit.\n",
		       rp->priv->reg_unit, cpu);
		वापस -ENODEV;
	पूर्ण

	value = (ra.value & ENERGY_UNIT_MASK) >> ENERGY_UNIT_OFFSET;
	rp->energy_unit = ENERGY_UNIT_SCALE * 1 << value;

	value = (ra.value & POWER_UNIT_MASK) >> POWER_UNIT_OFFSET;
	rp->घातer_unit = (1 << value) * 1000;

	value = (ra.value & TIME_UNIT_MASK) >> TIME_UNIT_OFFSET;
	rp->समय_unit = 1000000 / (1 << value);

	pr_debug("Atom %s energy=%dpJ, time=%dus, power=%duW\n",
		 rp->name, rp->energy_unit, rp->समय_unit, rp->घातer_unit);

	वापस 0;
पूर्ण

अटल व्योम घातer_limit_irq_save_cpu(व्योम *info)
अणु
	u32 l, h = 0;
	काष्ठा rapl_package *rp = (काष्ठा rapl_package *)info;

	/* save the state of PLN irq mask bit beक्रमe disabling it */
	rdmsr_safe(MSR_IA32_PACKAGE_THERM_INTERRUPT, &l, &h);
	अगर (!(rp->घातer_limit_irq & PACKAGE_PLN_INT_SAVED)) अणु
		rp->घातer_limit_irq = l & PACKAGE_THERM_INT_PLN_ENABLE;
		rp->घातer_limit_irq |= PACKAGE_PLN_INT_SAVED;
	पूर्ण
	l &= ~PACKAGE_THERM_INT_PLN_ENABLE;
	wrmsr_safe(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
पूर्ण

/* REVISIT:
 * When package घातer limit is set artअगरicially low by RAPL, LVT
 * thermal पूर्णांकerrupt क्रम package घातer limit should be ignored
 * since we are not really exceeding the real limit. The पूर्णांकention
 * is to aव्योम excessive पूर्णांकerrupts जबतक we are trying to save घातer.
 * A useful feature might be routing the package_घातer_limit पूर्णांकerrupt
 * to userspace via eventfd. once we have a useहाल, this is simple
 * to करो by adding an atomic notअगरier.
 */

अटल व्योम package_घातer_limit_irq_save(काष्ठा rapl_package *rp)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_PTS) || !boot_cpu_has(X86_FEATURE_PLN))
		वापस;

	smp_call_function_single(rp->lead_cpu, घातer_limit_irq_save_cpu, rp, 1);
पूर्ण

/*
 * Restore per package घातer limit पूर्णांकerrupt enable state. Called from cpu
 * hotplug code on package removal.
 */
अटल व्योम package_घातer_limit_irq_restore(काष्ठा rapl_package *rp)
अणु
	u32 l, h;

	अगर (!boot_cpu_has(X86_FEATURE_PTS) || !boot_cpu_has(X86_FEATURE_PLN))
		वापस;

	/* irq enable state not saved, nothing to restore */
	अगर (!(rp->घातer_limit_irq & PACKAGE_PLN_INT_SAVED))
		वापस;

	rdmsr_safe(MSR_IA32_PACKAGE_THERM_INTERRUPT, &l, &h);

	अगर (rp->घातer_limit_irq & PACKAGE_THERM_INT_PLN_ENABLE)
		l |= PACKAGE_THERM_INT_PLN_ENABLE;
	अन्यथा
		l &= ~PACKAGE_THERM_INT_PLN_ENABLE;

	wrmsr_safe(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
पूर्ण

अटल व्योम set_न्यूनमान_freq_शेष(काष्ठा rapl_करोमुख्य *rd, bool mode)
अणु
	पूर्णांक nr_घातerlimit = find_nr_घातer_limit(rd);

	/* always enable clamp such that p-state can go below OS requested
	 * range. घातer capping priority over guranteed frequency.
	 */
	rapl_ग_लिखो_data_raw(rd, PL1_CLAMP, mode);

	/* some करोमुख्यs have pl2 */
	अगर (nr_घातerlimit > 1) अणु
		rapl_ग_लिखो_data_raw(rd, PL2_ENABLE, mode);
		rapl_ग_लिखो_data_raw(rd, PL2_CLAMP, mode);
	पूर्ण
पूर्ण

अटल व्योम set_न्यूनमान_freq_atom(काष्ठा rapl_करोमुख्य *rd, bool enable)
अणु
	अटल u32 घातer_ctrl_orig_val;
	u32 mdata;

	अगर (!rapl_शेषs->न्यूनमान_freq_reg_addr) अणु
		pr_err("Invalid floor frequency config register\n");
		वापस;
	पूर्ण

	अगर (!घातer_ctrl_orig_val)
		iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_CR_READ,
			      rapl_शेषs->न्यूनमान_freq_reg_addr,
			      &घातer_ctrl_orig_val);
	mdata = घातer_ctrl_orig_val;
	अगर (enable) अणु
		mdata &= ~(0x7f << 8);
		mdata |= 1 << 8;
	पूर्ण
	iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_CR_WRITE,
		       rapl_शेषs->न्यूनमान_freq_reg_addr, mdata);
पूर्ण

अटल u64 rapl_compute_समय_winकरोw_core(काष्ठा rapl_package *rp, u64 value,
					 bool to_raw)
अणु
	u64 f, y;		/* fraction and exp. used क्रम समय unit */

	/*
	 * Special processing based on 2^Y*(1+F/4), refer
	 * to Intel Software Developer's manual Vol.3B: CH 14.9.3.
	 */
	अगर (!to_raw) अणु
		f = (value & 0x60) >> 5;
		y = value & 0x1f;
		value = (1 << y) * (4 + f) * rp->समय_unit / 4;
	पूर्ण अन्यथा अणु
		करो_भाग(value, rp->समय_unit);
		y = ilog2(value);
		f = भाग64_u64(4 * (value - (1 << y)), 1 << y);
		value = (y & 0x1f) | ((f & 0x3) << 5);
	पूर्ण
	वापस value;
पूर्ण

अटल u64 rapl_compute_समय_winकरोw_atom(काष्ठा rapl_package *rp, u64 value,
					 bool to_raw)
अणु
	/*
	 * Atom समय unit encoding is straight क्रमward val * समय_unit,
	 * where समय_unit is शेष to 1 sec. Never 0.
	 */
	अगर (!to_raw)
		वापस (value) ? value *= rp->समय_unit : rp->समय_unit;

	value = भाग64_u64(value, rp->समय_unit);

	वापस value;
पूर्ण

अटल स्थिर काष्ठा rapl_शेषs rapl_शेषs_core = अणु
	.न्यूनमान_freq_reg_addr = 0,
	.check_unit = rapl_check_unit_core,
	.set_न्यूनमान_freq = set_न्यूनमान_freq_शेष,
	.compute_समय_winकरोw = rapl_compute_समय_winकरोw_core,
पूर्ण;

अटल स्थिर काष्ठा rapl_शेषs rapl_शेषs_hsw_server = अणु
	.check_unit = rapl_check_unit_core,
	.set_न्यूनमान_freq = set_न्यूनमान_freq_शेष,
	.compute_समय_winकरोw = rapl_compute_समय_winकरोw_core,
	.dram_करोमुख्य_energy_unit = 15300,
पूर्ण;

अटल स्थिर काष्ठा rapl_शेषs rapl_शेषs_spr_server = अणु
	.check_unit = rapl_check_unit_core,
	.set_न्यूनमान_freq = set_न्यूनमान_freq_शेष,
	.compute_समय_winकरोw = rapl_compute_समय_winकरोw_core,
	.dram_करोमुख्य_energy_unit = 15300,
	.psys_करोमुख्य_energy_unit = 1000000000,
पूर्ण;

अटल स्थिर काष्ठा rapl_शेषs rapl_शेषs_byt = अणु
	.न्यूनमान_freq_reg_addr = IOSF_CPU_POWER_BUDGET_CTL_BYT,
	.check_unit = rapl_check_unit_atom,
	.set_न्यूनमान_freq = set_न्यूनमान_freq_atom,
	.compute_समय_winकरोw = rapl_compute_समय_winकरोw_atom,
पूर्ण;

अटल स्थिर काष्ठा rapl_शेषs rapl_शेषs_tng = अणु
	.न्यूनमान_freq_reg_addr = IOSF_CPU_POWER_BUDGET_CTL_TNG,
	.check_unit = rapl_check_unit_atom,
	.set_न्यूनमान_freq = set_न्यूनमान_freq_atom,
	.compute_समय_winकरोw = rapl_compute_समय_winकरोw_atom,
पूर्ण;

अटल स्थिर काष्ठा rapl_शेषs rapl_शेषs_ann = अणु
	.न्यूनमान_freq_reg_addr = 0,
	.check_unit = rapl_check_unit_atom,
	.set_न्यूनमान_freq = शून्य,
	.compute_समय_winकरोw = rapl_compute_समय_winकरोw_atom,
पूर्ण;

अटल स्थिर काष्ठा rapl_शेषs rapl_शेषs_cht = अणु
	.न्यूनमान_freq_reg_addr = 0,
	.check_unit = rapl_check_unit_atom,
	.set_न्यूनमान_freq = शून्य,
	.compute_समय_winकरोw = rapl_compute_समय_winकरोw_atom,
पूर्ण;

अटल स्थिर काष्ठा rapl_शेषs rapl_शेषs_amd = अणु
	.check_unit = rapl_check_unit_core,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id rapl_ids[] __initस्थिर = अणु
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE_X,	&rapl_शेषs_core),

	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE_X,		&rapl_शेषs_core),

	X86_MATCH_INTEL_FAM6_MODEL(HASWELL,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_L,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_G,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_X,		&rapl_शेषs_hsw_server),

	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_G,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_D,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X,		&rapl_शेषs_hsw_server),

	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_L,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_X,		&rapl_शेषs_hsw_server),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE_L,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(CANNONLAKE_L,	&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_L,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_NNPI,	&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_X,		&rapl_शेषs_hsw_server),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_D,		&rapl_शेषs_hsw_server),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE_L,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE_L,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ROCKETLAKE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE_L,		&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(SAPPHIRERAPIDS_X,	&rapl_शेषs_spr_server),
	X86_MATCH_INTEL_FAM6_MODEL(LAKEFIELD,		&rapl_शेषs_core),

	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT,	&rapl_शेषs_byt),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT,	&rapl_शेषs_cht),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT_MID,	&rapl_शेषs_tng),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT_MID,	&rapl_शेषs_ann),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT,	&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_PLUS,	&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_D,	&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT,	&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_D,	&rapl_शेषs_core),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_L,	&rapl_शेषs_core),

	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNL,	&rapl_शेषs_hsw_server),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNM,	&rapl_शेषs_hsw_server),

	X86_MATCH_VENDOR_FAM(AMD, 0x17, &rapl_शेषs_amd),
	X86_MATCH_VENDOR_FAM(AMD, 0x19, &rapl_शेषs_amd),
	X86_MATCH_VENDOR_FAM(HYGON, 0x18, &rapl_शेषs_amd),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, rapl_ids);

/* Read once क्रम all raw primitive data क्रम करोमुख्यs */
अटल व्योम rapl_update_करोमुख्य_data(काष्ठा rapl_package *rp)
अणु
	पूर्णांक dmn, prim;
	u64 val;

	क्रम (dmn = 0; dmn < rp->nr_करोमुख्यs; dmn++) अणु
		pr_debug("update %s domain %s data\n", rp->name,
			 rp->करोमुख्यs[dmn].name);
		/* exclude non-raw primitives */
		क्रम (prim = 0; prim < NR_RAW_PRIMITIVES; prim++) अणु
			अगर (!rapl_पढ़ो_data_raw(&rp->करोमुख्यs[dmn], prim,
						rpi[prim].unit, &val))
				rp->करोमुख्यs[dmn].rdd.primitives[prim] = val;
		पूर्ण
	पूर्ण

पूर्ण

अटल पूर्णांक rapl_package_रेजिस्टर_घातercap(काष्ठा rapl_package *rp)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	काष्ठा घातercap_zone *घातer_zone = शून्य;
	पूर्णांक nr_pl, ret;

	/* Update the करोमुख्य data of the new package */
	rapl_update_करोमुख्य_data(rp);

	/* first we रेजिस्टर package करोमुख्य as the parent zone */
	क्रम (rd = rp->करोमुख्यs; rd < rp->करोमुख्यs + rp->nr_करोमुख्यs; rd++) अणु
		अगर (rd->id == RAPL_DOMAIN_PACKAGE) अणु
			nr_pl = find_nr_घातer_limit(rd);
			pr_debug("register package domain %s\n", rp->name);
			घातer_zone = घातercap_रेजिस्टर_zone(&rd->घातer_zone,
					    rp->priv->control_type, rp->name,
					    शून्य, &zone_ops[rd->id], nr_pl,
					    &स्थिरraपूर्णांक_ops);
			अगर (IS_ERR(घातer_zone)) अणु
				pr_debug("failed to register power zone %s\n",
					 rp->name);
				वापस PTR_ERR(घातer_zone);
			पूर्ण
			/* track parent zone in per package/socket data */
			rp->घातer_zone = घातer_zone;
			/* करोne, only one package करोमुख्य per socket */
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!घातer_zone) अणु
		pr_err("no package domain found, unknown topology!\n");
		वापस -ENODEV;
	पूर्ण
	/* now रेजिस्टर करोमुख्यs as children of the socket/package */
	क्रम (rd = rp->करोमुख्यs; rd < rp->करोमुख्यs + rp->nr_करोमुख्यs; rd++) अणु
		काष्ठा घातercap_zone *parent = rp->घातer_zone;

		अगर (rd->id == RAPL_DOMAIN_PACKAGE)
			जारी;
		अगर (rd->id == RAPL_DOMAIN_PLATFORM)
			parent = शून्य;
		/* number of घातer limits per करोमुख्य varies */
		nr_pl = find_nr_घातer_limit(rd);
		घातer_zone = घातercap_रेजिस्टर_zone(&rd->घातer_zone,
						    rp->priv->control_type,
						    rd->name, parent,
						    &zone_ops[rd->id], nr_pl,
						    &स्थिरraपूर्णांक_ops);

		अगर (IS_ERR(घातer_zone)) अणु
			pr_debug("failed to register power_zone, %s:%s\n",
				 rp->name, rd->name);
			ret = PTR_ERR(घातer_zone);
			जाओ err_cleanup;
		पूर्ण
	पूर्ण
	वापस 0;

err_cleanup:
	/*
	 * Clean up previously initialized करोमुख्यs within the package अगर we
	 * failed after the first करोमुख्य setup.
	 */
	जबतक (--rd >= rp->करोमुख्यs) अणु
		pr_debug("unregister %s domain %s\n", rp->name, rd->name);
		घातercap_unरेजिस्टर_zone(rp->priv->control_type,
					 &rd->घातer_zone);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rapl_check_करोमुख्य(पूर्णांक cpu, पूर्णांक करोमुख्य, काष्ठा rapl_package *rp)
अणु
	काष्ठा reg_action ra;

	चयन (करोमुख्य) अणु
	हाल RAPL_DOMAIN_PACKAGE:
	हाल RAPL_DOMAIN_PP0:
	हाल RAPL_DOMAIN_PP1:
	हाल RAPL_DOMAIN_DRAM:
	हाल RAPL_DOMAIN_PLATFORM:
		ra.reg = rp->priv->regs[करोमुख्य][RAPL_DOMAIN_REG_STATUS];
		अवरोध;
	शेष:
		pr_err("invalid domain id %d\n", करोमुख्य);
		वापस -EINVAL;
	पूर्ण
	/* make sure करोमुख्य counters are available and contains non-zero
	 * values, otherwise skip it.
	 */

	ra.mask = ENERGY_STATUS_MASK;
	अगर (rp->priv->पढ़ो_raw(cpu, &ra) || !ra.value)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * Check अगर घातer limits are available. Two हालs when they are not available:
 * 1. Locked by BIOS, in this हाल we still provide पढ़ो-only access so that
 *    users can see what limit is set by the BIOS.
 * 2. Some CPUs make some करोमुख्यs monitoring only which means PLx MSRs may not
 *    exist at all. In this हाल, we करो not show the स्थिरraपूर्णांकs in घातercap.
 *
 * Called after करोमुख्यs are detected and initialized.
 */
अटल व्योम rapl_detect_घातerlimit(काष्ठा rapl_करोमुख्य *rd)
अणु
	u64 val64;
	पूर्णांक i;

	/* check अगर the करोमुख्य is locked by BIOS, ignore अगर MSR करोesn't exist */
	अगर (!rapl_पढ़ो_data_raw(rd, FW_LOCK, false, &val64)) अणु
		अगर (val64) अणु
			pr_info("RAPL %s domain %s locked by BIOS\n",
				rd->rp->name, rd->name);
			rd->state |= DOMAIN_STATE_BIOS_LOCKED;
		पूर्ण
	पूर्ण
	/* check अगर घातer limit MSR exists, otherwise करोमुख्य is monitoring only */
	क्रम (i = 0; i < NR_POWER_LIMITS; i++) अणु
		पूर्णांक prim = rd->rpl[i].prim_id;

		अगर (rapl_पढ़ो_data_raw(rd, prim, false, &val64))
			rd->rpl[i].name = शून्य;
	पूर्ण
पूर्ण

/* Detect active and valid करोमुख्यs क्रम the given CPU, caller must
 * ensure the CPU beदीर्घs to the targeted package and CPU hotlug is disabled.
 */
अटल पूर्णांक rapl_detect_करोमुख्यs(काष्ठा rapl_package *rp, पूर्णांक cpu)
अणु
	काष्ठा rapl_करोमुख्य *rd;
	पूर्णांक i;

	क्रम (i = 0; i < RAPL_DOMAIN_MAX; i++) अणु
		/* use physical package id to पढ़ो counters */
		अगर (!rapl_check_करोमुख्य(cpu, i, rp)) अणु
			rp->करोमुख्य_map |= 1 << i;
			pr_info("Found RAPL domain %s\n", rapl_करोमुख्य_names[i]);
		पूर्ण
	पूर्ण
	rp->nr_करोमुख्यs = biपंचांगap_weight(&rp->करोमुख्य_map, RAPL_DOMAIN_MAX);
	अगर (!rp->nr_करोमुख्यs) अणु
		pr_debug("no valid rapl domains found in %s\n", rp->name);
		वापस -ENODEV;
	पूर्ण
	pr_debug("found %d domains on %s\n", rp->nr_करोमुख्यs, rp->name);

	rp->करोमुख्यs = kसुस्मृति(rp->nr_करोमुख्यs + 1, माप(काष्ठा rapl_करोमुख्य),
			      GFP_KERNEL);
	अगर (!rp->करोमुख्यs)
		वापस -ENOMEM;

	rapl_init_करोमुख्यs(rp);

	क्रम (rd = rp->करोमुख्यs; rd < rp->करोमुख्यs + rp->nr_करोमुख्यs; rd++)
		rapl_detect_घातerlimit(rd);

	वापस 0;
पूर्ण

/* called from CPU hotplug notअगरier, hotplug lock held */
व्योम rapl_हटाओ_package(काष्ठा rapl_package *rp)
अणु
	काष्ठा rapl_करोमुख्य *rd, *rd_package = शून्य;

	package_घातer_limit_irq_restore(rp);

	क्रम (rd = rp->करोमुख्यs; rd < rp->करोमुख्यs + rp->nr_करोमुख्यs; rd++) अणु
		rapl_ग_लिखो_data_raw(rd, PL1_ENABLE, 0);
		rapl_ग_लिखो_data_raw(rd, PL1_CLAMP, 0);
		अगर (find_nr_घातer_limit(rd) > 1) अणु
			rapl_ग_लिखो_data_raw(rd, PL2_ENABLE, 0);
			rapl_ग_लिखो_data_raw(rd, PL2_CLAMP, 0);
			rapl_ग_लिखो_data_raw(rd, PL4_ENABLE, 0);
		पूर्ण
		अगर (rd->id == RAPL_DOMAIN_PACKAGE) अणु
			rd_package = rd;
			जारी;
		पूर्ण
		pr_debug("remove package, undo power limit on %s: %s\n",
			 rp->name, rd->name);
		घातercap_unरेजिस्टर_zone(rp->priv->control_type,
					 &rd->घातer_zone);
	पूर्ण
	/* करो parent zone last */
	घातercap_unरेजिस्टर_zone(rp->priv->control_type,
				 &rd_package->घातer_zone);
	list_del(&rp->plist);
	kमुक्त(rp);
पूर्ण
EXPORT_SYMBOL_GPL(rapl_हटाओ_package);

/* caller to ensure CPU hotplug lock is held */
काष्ठा rapl_package *rapl_find_package_करोमुख्य(पूर्णांक cpu, काष्ठा rapl_अगर_priv *priv)
अणु
	पूर्णांक id = topology_logical_die_id(cpu);
	काष्ठा rapl_package *rp;

	list_क्रम_each_entry(rp, &rapl_packages, plist) अणु
		अगर (rp->id == id
		    && rp->priv->control_type == priv->control_type)
			वापस rp;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rapl_find_package_करोमुख्य);

/* called from CPU hotplug notअगरier, hotplug lock held */
काष्ठा rapl_package *rapl_add_package(पूर्णांक cpu, काष्ठा rapl_अगर_priv *priv)
अणु
	पूर्णांक id = topology_logical_die_id(cpu);
	काष्ठा rapl_package *rp;
	पूर्णांक ret;

	अगर (!rapl_शेषs)
		वापस ERR_PTR(-ENODEV);

	rp = kzalloc(माप(काष्ठा rapl_package), GFP_KERNEL);
	अगर (!rp)
		वापस ERR_PTR(-ENOMEM);

	/* add the new package to the list */
	rp->id = id;
	rp->lead_cpu = cpu;
	rp->priv = priv;

	अगर (topology_max_die_per_package() > 1)
		snम_लिखो(rp->name, PACKAGE_DOMAIN_NAME_LENGTH,
			 "package-%d-die-%d",
			 topology_physical_package_id(cpu), topology_die_id(cpu));
	अन्यथा
		snम_लिखो(rp->name, PACKAGE_DOMAIN_NAME_LENGTH, "package-%d",
			 topology_physical_package_id(cpu));

	/* check अगर the package contains valid करोमुख्यs */
	अगर (rapl_detect_करोमुख्यs(rp, cpu) || rapl_शेषs->check_unit(rp, cpu)) अणु
		ret = -ENODEV;
		जाओ err_मुक्त_package;
	पूर्ण
	ret = rapl_package_रेजिस्टर_घातercap(rp);
	अगर (!ret) अणु
		INIT_LIST_HEAD(&rp->plist);
		list_add(&rp->plist, &rapl_packages);
		वापस rp;
	पूर्ण

err_मुक्त_package:
	kमुक्त(rp->करोमुख्यs);
	kमुक्त(rp);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(rapl_add_package);

अटल व्योम घातer_limit_state_save(व्योम)
अणु
	काष्ठा rapl_package *rp;
	काष्ठा rapl_करोमुख्य *rd;
	पूर्णांक nr_pl, ret, i;

	get_online_cpus();
	list_क्रम_each_entry(rp, &rapl_packages, plist) अणु
		अगर (!rp->घातer_zone)
			जारी;
		rd = घातer_zone_to_rapl_करोमुख्य(rp->घातer_zone);
		nr_pl = find_nr_घातer_limit(rd);
		क्रम (i = 0; i < nr_pl; i++) अणु
			चयन (rd->rpl[i].prim_id) अणु
			हाल PL1_ENABLE:
				ret = rapl_पढ़ो_data_raw(rd,
						 POWER_LIMIT1, true,
						 &rd->rpl[i].last_घातer_limit);
				अगर (ret)
					rd->rpl[i].last_घातer_limit = 0;
				अवरोध;
			हाल PL2_ENABLE:
				ret = rapl_पढ़ो_data_raw(rd,
						 POWER_LIMIT2, true,
						 &rd->rpl[i].last_घातer_limit);
				अगर (ret)
					rd->rpl[i].last_घातer_limit = 0;
				अवरोध;
			हाल PL4_ENABLE:
				ret = rapl_पढ़ो_data_raw(rd,
						 POWER_LIMIT4, true,
						 &rd->rpl[i].last_घातer_limit);
				अगर (ret)
					rd->rpl[i].last_घातer_limit = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	put_online_cpus();
पूर्ण

अटल व्योम घातer_limit_state_restore(व्योम)
अणु
	काष्ठा rapl_package *rp;
	काष्ठा rapl_करोमुख्य *rd;
	पूर्णांक nr_pl, i;

	get_online_cpus();
	list_क्रम_each_entry(rp, &rapl_packages, plist) अणु
		अगर (!rp->घातer_zone)
			जारी;
		rd = घातer_zone_to_rapl_करोमुख्य(rp->घातer_zone);
		nr_pl = find_nr_घातer_limit(rd);
		क्रम (i = 0; i < nr_pl; i++) अणु
			चयन (rd->rpl[i].prim_id) अणु
			हाल PL1_ENABLE:
				अगर (rd->rpl[i].last_घातer_limit)
					rapl_ग_लिखो_data_raw(rd, POWER_LIMIT1,
					    rd->rpl[i].last_घातer_limit);
				अवरोध;
			हाल PL2_ENABLE:
				अगर (rd->rpl[i].last_घातer_limit)
					rapl_ग_लिखो_data_raw(rd, POWER_LIMIT2,
					    rd->rpl[i].last_घातer_limit);
				अवरोध;
			हाल PL4_ENABLE:
				अगर (rd->rpl[i].last_घातer_limit)
					rapl_ग_लिखो_data_raw(rd, POWER_LIMIT4,
					    rd->rpl[i].last_घातer_limit);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	put_online_cpus();
पूर्ण

अटल पूर्णांक rapl_pm_callback(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ mode, व्योम *_unused)
अणु
	चयन (mode) अणु
	हाल PM_SUSPEND_PREPARE:
		घातer_limit_state_save();
		अवरोध;
	हाल PM_POST_SUSPEND:
		घातer_limit_state_restore();
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block rapl_pm_notअगरier = अणु
	.notअगरier_call = rapl_pm_callback,
पूर्ण;

अटल काष्ठा platक्रमm_device *rapl_msr_platdev;

अटल पूर्णांक __init rapl_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	पूर्णांक ret;

	id = x86_match_cpu(rapl_ids);
	अगर (!id) अणु
		pr_err("driver does not support CPU family %d model %d\n",
		       boot_cpu_data.x86, boot_cpu_data.x86_model);

		वापस -ENODEV;
	पूर्ण

	rapl_शेषs = (काष्ठा rapl_शेषs *)id->driver_data;

	ret = रेजिस्टर_pm_notअगरier(&rapl_pm_notअगरier);
	अगर (ret)
		वापस ret;

	rapl_msr_platdev = platक्रमm_device_alloc("intel_rapl_msr", 0);
	अगर (!rapl_msr_platdev) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	ret = platक्रमm_device_add(rapl_msr_platdev);
	अगर (ret)
		platक्रमm_device_put(rapl_msr_platdev);

end:
	अगर (ret)
		unरेजिस्टर_pm_notअगरier(&rapl_pm_notअगरier);

	वापस ret;
पूर्ण

अटल व्योम __निकास rapl_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(rapl_msr_platdev);
	unरेजिस्टर_pm_notअगरier(&rapl_pm_notअगरier);
पूर्ण

fs_initcall(rapl_init);
module_निकास(rapl_निकास);

MODULE_DESCRIPTION("Intel Runtime Average Power Limit (RAPL) common code");
MODULE_AUTHOR("Jacob Pan <jacob.jun.pan@intel.com>");
MODULE_LICENSE("GPL v2");
