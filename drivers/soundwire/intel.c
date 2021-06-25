<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2015-17 Intel Corporation.

/*
 * Soundwire Intel Master Driver
 */

#समावेश <linux/acpi.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_पूर्णांकel.h>
#समावेश "cadence_master.h"
#समावेश "bus.h"
#समावेश "intel.h"

#घोषणा INTEL_MASTER_SUSPEND_DELAY_MS	3000

/*
 * debug/config flags क्रम the Intel SoundWire Master.
 *
 * Since we may have multiple masters active, we can have up to 8
 * flags reused in each byte, with master0 using the ls-byte, etc.
 */

#घोषणा SDW_INTEL_MASTER_DISABLE_PM_RUNTIME		BIT(0)
#घोषणा SDW_INTEL_MASTER_DISABLE_CLOCK_STOP		BIT(1)
#घोषणा SDW_INTEL_MASTER_DISABLE_PM_RUNTIME_IDLE	BIT(2)
#घोषणा SDW_INTEL_MASTER_DISABLE_MULTI_LINK		BIT(3)

अटल पूर्णांक md_flags;
module_param_named(sdw_md_flags, md_flags, पूर्णांक, 0444);
MODULE_PARM_DESC(sdw_md_flags, "SoundWire Intel Master device flags (0x0 all off)");

/* Intel SHIM Registers Definition */
#घोषणा SDW_SHIM_LCAP			0x0
#घोषणा SDW_SHIM_LCTL			0x4
#घोषणा SDW_SHIM_IPPTR			0x8
#घोषणा SDW_SHIM_SYNC			0xC

#घोषणा SDW_SHIM_CTLSCAP(x)		(0x010 + 0x60 * (x))
#घोषणा SDW_SHIM_CTLS0CM(x)		(0x012 + 0x60 * (x))
#घोषणा SDW_SHIM_CTLS1CM(x)		(0x014 + 0x60 * (x))
#घोषणा SDW_SHIM_CTLS2CM(x)		(0x016 + 0x60 * (x))
#घोषणा SDW_SHIM_CTLS3CM(x)		(0x018 + 0x60 * (x))
#घोषणा SDW_SHIM_PCMSCAP(x)		(0x020 + 0x60 * (x))

#घोषणा SDW_SHIM_PCMSYCHM(x, y)		(0x022 + (0x60 * (x)) + (0x2 * (y)))
#घोषणा SDW_SHIM_PCMSYCHC(x, y)		(0x042 + (0x60 * (x)) + (0x2 * (y)))
#घोषणा SDW_SHIM_PDMSCAP(x)		(0x062 + 0x60 * (x))
#घोषणा SDW_SHIM_IOCTL(x)		(0x06C + 0x60 * (x))
#घोषणा SDW_SHIM_CTMCTL(x)		(0x06E + 0x60 * (x))

#घोषणा SDW_SHIM_WAKEEN			0x190
#घोषणा SDW_SHIM_WAKESTS		0x192

#घोषणा SDW_SHIM_LCTL_SPA		BIT(0)
#घोषणा SDW_SHIM_LCTL_SPA_MASK		GENMASK(3, 0)
#घोषणा SDW_SHIM_LCTL_CPA		BIT(8)
#घोषणा SDW_SHIM_LCTL_CPA_MASK		GENMASK(11, 8)

#घोषणा SDW_SHIM_SYNC_SYNCPRD_VAL_24	(24000 / SDW_CADENCE_GSYNC_KHZ - 1)
#घोषणा SDW_SHIM_SYNC_SYNCPRD_VAL_38_4	(38400 / SDW_CADENCE_GSYNC_KHZ - 1)
#घोषणा SDW_SHIM_SYNC_SYNCPRD		GENMASK(14, 0)
#घोषणा SDW_SHIM_SYNC_SYNCCPU		BIT(15)
#घोषणा SDW_SHIM_SYNC_CMDSYNC_MASK	GENMASK(19, 16)
#घोषणा SDW_SHIM_SYNC_CMDSYNC		BIT(16)
#घोषणा SDW_SHIM_SYNC_SYNCGO		BIT(24)

#घोषणा SDW_SHIM_PCMSCAP_ISS		GENMASK(3, 0)
#घोषणा SDW_SHIM_PCMSCAP_OSS		GENMASK(7, 4)
#घोषणा SDW_SHIM_PCMSCAP_BSS		GENMASK(12, 8)

#घोषणा SDW_SHIM_PCMSYCM_LCHN		GENMASK(3, 0)
#घोषणा SDW_SHIM_PCMSYCM_HCHN		GENMASK(7, 4)
#घोषणा SDW_SHIM_PCMSYCM_STREAM		GENMASK(13, 8)
#घोषणा SDW_SHIM_PCMSYCM_सूची		BIT(15)

#घोषणा SDW_SHIM_PDMSCAP_ISS		GENMASK(3, 0)
#घोषणा SDW_SHIM_PDMSCAP_OSS		GENMASK(7, 4)
#घोषणा SDW_SHIM_PDMSCAP_BSS		GENMASK(12, 8)
#घोषणा SDW_SHIM_PDMSCAP_CPSS		GENMASK(15, 13)

#घोषणा SDW_SHIM_IOCTL_MIF		BIT(0)
#घोषणा SDW_SHIM_IOCTL_CO		BIT(1)
#घोषणा SDW_SHIM_IOCTL_COE		BIT(2)
#घोषणा SDW_SHIM_IOCTL_DO		BIT(3)
#घोषणा SDW_SHIM_IOCTL_DOE		BIT(4)
#घोषणा SDW_SHIM_IOCTL_BKE		BIT(5)
#घोषणा SDW_SHIM_IOCTL_WPDD		BIT(6)
#घोषणा SDW_SHIM_IOCTL_CIBD		BIT(8)
#घोषणा SDW_SHIM_IOCTL_DIBD		BIT(9)

#घोषणा SDW_SHIM_CTMCTL_DACTQE		BIT(0)
#घोषणा SDW_SHIM_CTMCTL_DODS		BIT(1)
#घोषणा SDW_SHIM_CTMCTL_DOAIS		GENMASK(4, 3)

#घोषणा SDW_SHIM_WAKEEN_ENABLE		BIT(0)
#घोषणा SDW_SHIM_WAKESTS_STATUS		BIT(0)

/* Intel ALH Register definitions */
#घोषणा SDW_ALH_STRMZCFG(x)		(0x000 + (0x4 * (x)))
#घोषणा SDW_ALH_NUM_STREAMS		64

#घोषणा SDW_ALH_STRMZCFG_DMAT_VAL	0x3
#घोषणा SDW_ALH_STRMZCFG_DMAT		GENMASK(7, 0)
#घोषणा SDW_ALH_STRMZCFG_CHN		GENMASK(19, 16)

क्रमागत पूर्णांकel_pdi_type अणु
	INTEL_PDI_IN = 0,
	INTEL_PDI_OUT = 1,
	INTEL_PDI_BD = 2,
पूर्ण;

#घोषणा cdns_to_पूर्णांकel(_cdns) container_of(_cdns, काष्ठा sdw_पूर्णांकel, cdns)

/*
 * Read, ग_लिखो helpers क्रम HW रेजिस्टरs
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_पढ़ोl(व्योम __iomem *base, पूर्णांक offset)
अणु
	वापस पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_ग_लिखोl(व्योम __iomem *base, पूर्णांक offset, पूर्णांक value)
अणु
	ग_लिखोl(value, base + offset);
पूर्ण

अटल अंतरभूत u16 पूर्णांकel_पढ़ोw(व्योम __iomem *base, पूर्णांक offset)
अणु
	वापस पढ़ोw(base + offset);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_ग_लिखोw(व्योम __iomem *base, पूर्णांक offset, u16 value)
अणु
	ग_लिखोw(value, base + offset);
पूर्ण

अटल पूर्णांक पूर्णांकel_रुको_bit(व्योम __iomem *base, पूर्णांक offset, u32 mask, u32 target)
अणु
	पूर्णांक समयout = 10;
	u32 reg_पढ़ो;

	करो अणु
		reg_पढ़ो = पढ़ोl(base + offset);
		अगर ((reg_पढ़ो & mask) == target)
			वापस 0;

		समयout--;
		usleep_range(50, 100);
	पूर्ण जबतक (समयout != 0);

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक पूर्णांकel_clear_bit(व्योम __iomem *base, पूर्णांक offset, u32 value, u32 mask)
अणु
	ग_लिखोl(value, base + offset);
	वापस पूर्णांकel_रुको_bit(base, offset, mask, 0);
पूर्ण

अटल पूर्णांक पूर्णांकel_set_bit(व्योम __iomem *base, पूर्णांक offset, u32 value, u32 mask)
अणु
	ग_लिखोl(value, base + offset);
	वापस पूर्णांकel_रुको_bit(base, offset, mask, mask);
पूर्ण

/*
 * debugfs
 */
#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा RD_BUF (2 * PAGE_SIZE)

अटल sमाप_प्रकार पूर्णांकel_प्र_लिखो(व्योम __iomem *mem, bool l,
			     अक्षर *buf, माप_प्रकार pos, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक value;

	अगर (l)
		value = पूर्णांकel_पढ़ोl(mem, reg);
	अन्यथा
		value = पूर्णांकel_पढ़ोw(mem, reg);

	वापस scnम_लिखो(buf + pos, RD_BUF - pos, "%4x\t%4x\n", reg, value);
पूर्ण

अटल पूर्णांक पूर्णांकel_reg_show(काष्ठा seq_file *s_file, व्योम *data)
अणु
	काष्ठा sdw_पूर्णांकel *sdw = s_file->निजी;
	व्योम __iomem *s = sdw->link_res->shim;
	व्योम __iomem *a = sdw->link_res->alh;
	अक्षर *buf;
	sमाप_प्रकार ret;
	पूर्णांक i, j;
	अचिन्हित पूर्णांक links, reg;

	buf = kzalloc(RD_BUF, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	links = पूर्णांकel_पढ़ोl(s, SDW_SHIM_LCAP) & GENMASK(2, 0);

	ret = scnम_लिखो(buf, RD_BUF, "Register  Value\n");
	ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\nShim\n");

	क्रम (i = 0; i < links; i++) अणु
		reg = SDW_SHIM_LCAP + i * 4;
		ret += पूर्णांकel_प्र_लिखो(s, true, buf, ret, reg);
	पूर्ण

	क्रम (i = 0; i < links; i++) अणु
		ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\nLink%d\n", i);
		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_CTLSCAP(i));
		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_CTLS0CM(i));
		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_CTLS1CM(i));
		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_CTLS2CM(i));
		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_CTLS3CM(i));
		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_PCMSCAP(i));

		ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\n PCMSyCH registers\n");

		/*
		 * the value 10 is the number of PDIs. We will need a
		 * cleanup to हटाओ hard-coded Intel configurations
		 * from cadence_master.c
		 */
		क्रम (j = 0; j < 10; j++) अणु
			ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret,
					SDW_SHIM_PCMSYCHM(i, j));
			ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret,
					SDW_SHIM_PCMSYCHC(i, j));
		पूर्ण
		ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\n PDMSCAP, IOCTL, CTMCTL\n");

		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_PDMSCAP(i));
		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_IOCTL(i));
		ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_CTMCTL(i));
	पूर्ण

	ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\nWake registers\n");
	ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_WAKEEN);
	ret += पूर्णांकel_प्र_लिखो(s, false, buf, ret, SDW_SHIM_WAKESTS);

	ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\nALH STRMzCFG\n");
	क्रम (i = 0; i < SDW_ALH_NUM_STREAMS; i++)
		ret += पूर्णांकel_प्र_लिखो(a, true, buf, ret, SDW_ALH_STRMZCFG(i));

	seq_म_लिखो(s_file, "%s", buf);
	kमुक्त(buf);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(पूर्णांकel_reg);

अटल पूर्णांक पूर्णांकel_set_m_datamode(व्योम *data, u64 value)
अणु
	काष्ठा sdw_पूर्णांकel *sdw = data;
	काष्ठा sdw_bus *bus = &sdw->cdns.bus;

	अगर (value > SDW_PORT_DATA_MODE_STATIC_1)
		वापस -EINVAL;

	/* Userspace changed the hardware state behind the kernel's back */
	add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);

	bus->params.m_data_mode = value;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(पूर्णांकel_set_m_datamode_fops, शून्य,
			 पूर्णांकel_set_m_datamode, "%llu\n");

अटल पूर्णांक पूर्णांकel_set_s_datamode(व्योम *data, u64 value)
अणु
	काष्ठा sdw_पूर्णांकel *sdw = data;
	काष्ठा sdw_bus *bus = &sdw->cdns.bus;

	अगर (value > SDW_PORT_DATA_MODE_STATIC_1)
		वापस -EINVAL;

	/* Userspace changed the hardware state behind the kernel's back */
	add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);

	bus->params.s_data_mode = value;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(पूर्णांकel_set_s_datamode_fops, शून्य,
			 पूर्णांकel_set_s_datamode, "%llu\n");

अटल व्योम पूर्णांकel_debugfs_init(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	काष्ठा dentry *root = sdw->cdns.bus.debugfs;

	अगर (!root)
		वापस;

	sdw->debugfs = debugfs_create_dir("intel-sdw", root);

	debugfs_create_file("intel-registers", 0400, sdw->debugfs, sdw,
			    &पूर्णांकel_reg_fops);

	debugfs_create_file("intel-m-datamode", 0200, sdw->debugfs, sdw,
			    &पूर्णांकel_set_m_datamode_fops);

	debugfs_create_file("intel-s-datamode", 0200, sdw->debugfs, sdw,
			    &पूर्णांकel_set_s_datamode_fops);

	sdw_cdns_debugfs_init(&sdw->cdns, sdw->debugfs);
पूर्ण

अटल व्योम पूर्णांकel_debugfs_निकास(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	debugfs_हटाओ_recursive(sdw->debugfs);
पूर्ण
#अन्यथा
अटल व्योम पूर्णांकel_debugfs_init(काष्ठा sdw_पूर्णांकel *sdw) अणुपूर्ण
अटल व्योम पूर्णांकel_debugfs_निकास(काष्ठा sdw_पूर्णांकel *sdw) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/*
 * shim ops
 */

अटल पूर्णांक पूर्णांकel_link_घातer_up(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	अचिन्हित पूर्णांक link_id = sdw->instance;
	व्योम __iomem *shim = sdw->link_res->shim;
	u32 *shim_mask = sdw->link_res->shim_mask;
	काष्ठा sdw_bus *bus = &sdw->cdns.bus;
	काष्ठा sdw_master_prop *prop = &bus->prop;
	u32 spa_mask, cpa_mask;
	u32 link_control;
	पूर्णांक ret = 0;
	u32 syncprd;
	u32 sync_reg;

	mutex_lock(sdw->link_res->shim_lock);

	/*
	 * The hardware relies on an पूर्णांकernal counter, typically 4kHz,
	 * to generate the SoundWire SSP - which defines a 'safe'
	 * synchronization poपूर्णांक between commands and audio transport
	 * and allows क्रम multi link synchronization. The SYNCPRD value
	 * is only dependent on the oscillator घड़ी provided to
	 * the IP, so adjust based on _DSD properties reported in DSDT
	 * tables. The values reported are based on either 24MHz
	 * (CNL/CML) or 38.4 MHz (ICL/TGL+).
	 */
	अगर (prop->mclk_freq % 6000000)
		syncprd = SDW_SHIM_SYNC_SYNCPRD_VAL_38_4;
	अन्यथा
		syncprd = SDW_SHIM_SYNC_SYNCPRD_VAL_24;

	अगर (!*shim_mask) अणु
		dev_dbg(sdw->cdns.dev, "%s: powering up all links\n", __func__);

		/* we first need to program the SyncPRD/CPU रेजिस्टरs */
		dev_dbg(sdw->cdns.dev,
			"%s: first link up, programming SYNCPRD\n", __func__);

		/* set SyncPRD period */
		sync_reg = पूर्णांकel_पढ़ोl(shim, SDW_SHIM_SYNC);
		u32p_replace_bits(&sync_reg, syncprd, SDW_SHIM_SYNC_SYNCPRD);

		/* Set SyncCPU bit */
		sync_reg |= SDW_SHIM_SYNC_SYNCCPU;
		पूर्णांकel_ग_लिखोl(shim, SDW_SHIM_SYNC, sync_reg);

		/* Link घातer up sequence */
		link_control = पूर्णांकel_पढ़ोl(shim, SDW_SHIM_LCTL);

		/* only घातer-up enabled links */
		spa_mask = FIELD_PREP(SDW_SHIM_LCTL_SPA_MASK, sdw->link_res->link_mask);
		cpa_mask = FIELD_PREP(SDW_SHIM_LCTL_CPA_MASK, sdw->link_res->link_mask);

		link_control |=  spa_mask;

		ret = पूर्णांकel_set_bit(shim, SDW_SHIM_LCTL, link_control, cpa_mask);
		अगर (ret < 0) अणु
			dev_err(sdw->cdns.dev, "Failed to power up link: %d\n", ret);
			जाओ out;
		पूर्ण

		/* SyncCPU will change once link is active */
		ret = पूर्णांकel_रुको_bit(shim, SDW_SHIM_SYNC,
				     SDW_SHIM_SYNC_SYNCCPU, 0);
		अगर (ret < 0) अणु
			dev_err(sdw->cdns.dev,
				"Failed to set SHIM_SYNC: %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	*shim_mask |= BIT(link_id);

	sdw->cdns.link_up = true;
out:
	mutex_unlock(sdw->link_res->shim_lock);

	वापस ret;
पूर्ण

/* this needs to be called with shim_lock */
अटल व्योम पूर्णांकel_shim_glue_to_master_ip(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	व्योम __iomem *shim = sdw->link_res->shim;
	अचिन्हित पूर्णांक link_id = sdw->instance;
	u16 ioctl;

	/* Switch to MIP from Glue logic */
	ioctl = पूर्णांकel_पढ़ोw(shim,  SDW_SHIM_IOCTL(link_id));

	ioctl &= ~(SDW_SHIM_IOCTL_DOE);
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	ioctl &= ~(SDW_SHIM_IOCTL_DO);
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	ioctl |= (SDW_SHIM_IOCTL_MIF);
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	ioctl &= ~(SDW_SHIM_IOCTL_BKE);
	ioctl &= ~(SDW_SHIM_IOCTL_COE);
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	/* at this poपूर्णांक Master IP has full control of the I/Os */
पूर्ण

/* this needs to be called with shim_lock */
अटल व्योम पूर्णांकel_shim_master_ip_to_glue(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	अचिन्हित पूर्णांक link_id = sdw->instance;
	व्योम __iomem *shim = sdw->link_res->shim;
	u16 ioctl;

	/* Glue logic */
	ioctl = पूर्णांकel_पढ़ोw(shim, SDW_SHIM_IOCTL(link_id));
	ioctl |= SDW_SHIM_IOCTL_BKE;
	ioctl |= SDW_SHIM_IOCTL_COE;
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	ioctl &= ~(SDW_SHIM_IOCTL_MIF);
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	/* at this poपूर्णांक Integration Glue has full control of the I/Os */
पूर्ण

अटल पूर्णांक पूर्णांकel_shim_init(काष्ठा sdw_पूर्णांकel *sdw, bool घड़ी_stop)
अणु
	व्योम __iomem *shim = sdw->link_res->shim;
	अचिन्हित पूर्णांक link_id = sdw->instance;
	पूर्णांक ret = 0;
	u16 ioctl = 0, act = 0;

	mutex_lock(sdw->link_res->shim_lock);

	/* Initialize Shim */
	ioctl |= SDW_SHIM_IOCTL_BKE;
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	ioctl |= SDW_SHIM_IOCTL_WPDD;
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	ioctl |= SDW_SHIM_IOCTL_DO;
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	ioctl |= SDW_SHIM_IOCTL_DOE;
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_IOCTL(link_id), ioctl);
	usleep_range(10, 15);

	पूर्णांकel_shim_glue_to_master_ip(sdw);

	u16p_replace_bits(&act, 0x1, SDW_SHIM_CTMCTL_DOAIS);
	act |= SDW_SHIM_CTMCTL_DACTQE;
	act |= SDW_SHIM_CTMCTL_DODS;
	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_CTMCTL(link_id), act);
	usleep_range(10, 15);

	mutex_unlock(sdw->link_res->shim_lock);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_shim_wake(काष्ठा sdw_पूर्णांकel *sdw, bool wake_enable)
अणु
	व्योम __iomem *shim = sdw->link_res->shim;
	अचिन्हित पूर्णांक link_id = sdw->instance;
	u16 wake_en, wake_sts;

	mutex_lock(sdw->link_res->shim_lock);
	wake_en = पूर्णांकel_पढ़ोw(shim, SDW_SHIM_WAKEEN);

	अगर (wake_enable) अणु
		/* Enable the wakeup */
		wake_en |= (SDW_SHIM_WAKEEN_ENABLE << link_id);
		पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_WAKEEN, wake_en);
	पूर्ण अन्यथा अणु
		/* Disable the wake up पूर्णांकerrupt */
		wake_en &= ~(SDW_SHIM_WAKEEN_ENABLE << link_id);
		पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_WAKEEN, wake_en);

		/* Clear wake status */
		wake_sts = पूर्णांकel_पढ़ोw(shim, SDW_SHIM_WAKESTS);
		wake_sts |= (SDW_SHIM_WAKEEN_ENABLE << link_id);
		पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_WAKESTS_STATUS, wake_sts);
	पूर्ण
	mutex_unlock(sdw->link_res->shim_lock);
पूर्ण

अटल पूर्णांक पूर्णांकel_link_घातer_करोwn(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	u32 link_control, spa_mask, cpa_mask;
	अचिन्हित पूर्णांक link_id = sdw->instance;
	व्योम __iomem *shim = sdw->link_res->shim;
	u32 *shim_mask = sdw->link_res->shim_mask;
	पूर्णांक ret = 0;

	mutex_lock(sdw->link_res->shim_lock);

	पूर्णांकel_shim_master_ip_to_glue(sdw);

	अगर (!(*shim_mask & BIT(link_id)))
		dev_err(sdw->cdns.dev,
			"%s: Unbalanced power-up/down calls\n", __func__);

	*shim_mask &= ~BIT(link_id);

	अगर (!*shim_mask) अणु

		dev_dbg(sdw->cdns.dev, "%s: powering down all links\n", __func__);

		/* Link घातer करोwn sequence */
		link_control = पूर्णांकel_पढ़ोl(shim, SDW_SHIM_LCTL);

		/* only घातer-करोwn enabled links */
		spa_mask = FIELD_PREP(SDW_SHIM_LCTL_SPA_MASK, ~sdw->link_res->link_mask);
		cpa_mask = FIELD_PREP(SDW_SHIM_LCTL_CPA_MASK, sdw->link_res->link_mask);

		link_control &=  spa_mask;

		ret = पूर्णांकel_clear_bit(shim, SDW_SHIM_LCTL, link_control, cpa_mask);
	पूर्ण

	mutex_unlock(sdw->link_res->shim_lock);

	अगर (ret < 0) अणु
		dev_err(sdw->cdns.dev, "%s: could not power down link\n", __func__);

		वापस ret;
	पूर्ण

	sdw->cdns.link_up = false;
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_shim_sync_arm(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	व्योम __iomem *shim = sdw->link_res->shim;
	u32 sync_reg;

	mutex_lock(sdw->link_res->shim_lock);

	/* update SYNC रेजिस्टर */
	sync_reg = पूर्णांकel_पढ़ोl(shim, SDW_SHIM_SYNC);
	sync_reg |= (SDW_SHIM_SYNC_CMDSYNC << sdw->instance);
	पूर्णांकel_ग_लिखोl(shim, SDW_SHIM_SYNC, sync_reg);

	mutex_unlock(sdw->link_res->shim_lock);
पूर्ण

अटल पूर्णांक पूर्णांकel_shim_sync_go_unlocked(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	व्योम __iomem *shim = sdw->link_res->shim;
	u32 sync_reg;
	पूर्णांक ret;

	/* Read SYNC रेजिस्टर */
	sync_reg = पूर्णांकel_पढ़ोl(shim, SDW_SHIM_SYNC);

	/*
	 * Set SyncGO bit to synchronously trigger a bank चयन क्रम
	 * all the masters. A ग_लिखो to SYNCGO bit clears CMDSYNC bit क्रम all
	 * the Masters.
	 */
	sync_reg |= SDW_SHIM_SYNC_SYNCGO;

	ret = पूर्णांकel_clear_bit(shim, SDW_SHIM_SYNC, sync_reg,
			      SDW_SHIM_SYNC_SYNCGO);

	अगर (ret < 0)
		dev_err(sdw->cdns.dev, "SyncGO clear failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_shim_sync_go(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	पूर्णांक ret;

	mutex_lock(sdw->link_res->shim_lock);

	ret = पूर्णांकel_shim_sync_go_unlocked(sdw);

	mutex_unlock(sdw->link_res->shim_lock);

	वापस ret;
पूर्ण

/*
 * PDI routines
 */
अटल व्योम पूर्णांकel_pdi_init(काष्ठा sdw_पूर्णांकel *sdw,
			   काष्ठा sdw_cdns_stream_config *config)
अणु
	व्योम __iomem *shim = sdw->link_res->shim;
	अचिन्हित पूर्णांक link_id = sdw->instance;
	पूर्णांक pcm_cap, pdm_cap;

	/* PCM Stream Capability */
	pcm_cap = पूर्णांकel_पढ़ोw(shim, SDW_SHIM_PCMSCAP(link_id));

	config->pcm_bd = FIELD_GET(SDW_SHIM_PCMSCAP_BSS, pcm_cap);
	config->pcm_in = FIELD_GET(SDW_SHIM_PCMSCAP_ISS, pcm_cap);
	config->pcm_out = FIELD_GET(SDW_SHIM_PCMSCAP_OSS, pcm_cap);

	dev_dbg(sdw->cdns.dev, "PCM cap bd:%d in:%d out:%d\n",
		config->pcm_bd, config->pcm_in, config->pcm_out);

	/* PDM Stream Capability */
	pdm_cap = पूर्णांकel_पढ़ोw(shim, SDW_SHIM_PDMSCAP(link_id));

	config->pdm_bd = FIELD_GET(SDW_SHIM_PDMSCAP_BSS, pdm_cap);
	config->pdm_in = FIELD_GET(SDW_SHIM_PDMSCAP_ISS, pdm_cap);
	config->pdm_out = FIELD_GET(SDW_SHIM_PDMSCAP_OSS, pdm_cap);

	dev_dbg(sdw->cdns.dev, "PDM cap bd:%d in:%d out:%d\n",
		config->pdm_bd, config->pdm_in, config->pdm_out);
पूर्ण

अटल पूर्णांक
पूर्णांकel_pdi_get_ch_cap(काष्ठा sdw_पूर्णांकel *sdw, अचिन्हित पूर्णांक pdi_num, bool pcm)
अणु
	व्योम __iomem *shim = sdw->link_res->shim;
	अचिन्हित पूर्णांक link_id = sdw->instance;
	पूर्णांक count;

	अगर (pcm) अणु
		count = पूर्णांकel_पढ़ोw(shim, SDW_SHIM_PCMSYCHC(link_id, pdi_num));

		/*
		 * WORKAROUND: on all existing Intel controllers, pdi
		 * number 2 reports channel count as 1 even though it
		 * supports 8 channels. Perक्रमming hardcoding क्रम pdi
		 * number 2.
		 */
		अगर (pdi_num == 2)
			count = 7;

	पूर्ण अन्यथा अणु
		count = पूर्णांकel_पढ़ोw(shim, SDW_SHIM_PDMSCAP(link_id));
		count = FIELD_GET(SDW_SHIM_PDMSCAP_CPSS, count);
	पूर्ण

	/* zero based values क्रम channel count in रेजिस्टर */
	count++;

	वापस count;
पूर्ण

अटल पूर्णांक पूर्णांकel_pdi_get_ch_update(काष्ठा sdw_पूर्णांकel *sdw,
				   काष्ठा sdw_cdns_pdi *pdi,
				   अचिन्हित पूर्णांक num_pdi,
				   अचिन्हित पूर्णांक *num_ch, bool pcm)
अणु
	पूर्णांक i, ch_count = 0;

	क्रम (i = 0; i < num_pdi; i++) अणु
		pdi->ch_count = पूर्णांकel_pdi_get_ch_cap(sdw, pdi->num, pcm);
		ch_count += pdi->ch_count;
		pdi++;
	पूर्ण

	*num_ch = ch_count;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pdi_stream_ch_update(काष्ठा sdw_पूर्णांकel *sdw,
				      काष्ठा sdw_cdns_streams *stream, bool pcm)
अणु
	पूर्णांकel_pdi_get_ch_update(sdw, stream->bd, stream->num_bd,
				&stream->num_ch_bd, pcm);

	पूर्णांकel_pdi_get_ch_update(sdw, stream->in, stream->num_in,
				&stream->num_ch_in, pcm);

	पूर्णांकel_pdi_get_ch_update(sdw, stream->out, stream->num_out,
				&stream->num_ch_out, pcm);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pdi_ch_update(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	/* First update PCM streams followed by PDM streams */
	पूर्णांकel_pdi_stream_ch_update(sdw, &sdw->cdns.pcm, true);
	पूर्णांकel_pdi_stream_ch_update(sdw, &sdw->cdns.pdm, false);

	वापस 0;
पूर्ण

अटल व्योम
पूर्णांकel_pdi_shim_configure(काष्ठा sdw_पूर्णांकel *sdw, काष्ठा sdw_cdns_pdi *pdi)
अणु
	व्योम __iomem *shim = sdw->link_res->shim;
	अचिन्हित पूर्णांक link_id = sdw->instance;
	पूर्णांक pdi_conf = 0;

	/* the Bulk and PCM streams are not contiguous */
	pdi->पूर्णांकel_alh_id = (link_id * 16) + pdi->num + 3;
	अगर (pdi->num >= 2)
		pdi->पूर्णांकel_alh_id += 2;

	/*
	 * Program stream parameters to stream SHIM रेजिस्टर
	 * This is applicable क्रम PCM stream only.
	 */
	अगर (pdi->type != SDW_STREAM_PCM)
		वापस;

	अगर (pdi->dir == SDW_DATA_सूची_RX)
		pdi_conf |= SDW_SHIM_PCMSYCM_सूची;
	अन्यथा
		pdi_conf &= ~(SDW_SHIM_PCMSYCM_सूची);

	u32p_replace_bits(&pdi_conf, pdi->पूर्णांकel_alh_id, SDW_SHIM_PCMSYCM_STREAM);
	u32p_replace_bits(&pdi_conf, pdi->l_ch_num, SDW_SHIM_PCMSYCM_LCHN);
	u32p_replace_bits(&pdi_conf, pdi->h_ch_num, SDW_SHIM_PCMSYCM_HCHN);

	पूर्णांकel_ग_लिखोw(shim, SDW_SHIM_PCMSYCHM(link_id, pdi->num), pdi_conf);
पूर्ण

अटल व्योम
पूर्णांकel_pdi_alh_configure(काष्ठा sdw_पूर्णांकel *sdw, काष्ठा sdw_cdns_pdi *pdi)
अणु
	व्योम __iomem *alh = sdw->link_res->alh;
	अचिन्हित पूर्णांक link_id = sdw->instance;
	अचिन्हित पूर्णांक conf;

	/* the Bulk and PCM streams are not contiguous */
	pdi->पूर्णांकel_alh_id = (link_id * 16) + pdi->num + 3;
	अगर (pdi->num >= 2)
		pdi->पूर्णांकel_alh_id += 2;

	/* Program Stream config ALH रेजिस्टर */
	conf = पूर्णांकel_पढ़ोl(alh, SDW_ALH_STRMZCFG(pdi->पूर्णांकel_alh_id));

	u32p_replace_bits(&conf, SDW_ALH_STRMZCFG_DMAT_VAL, SDW_ALH_STRMZCFG_DMAT);
	u32p_replace_bits(&conf, pdi->ch_count - 1, SDW_ALH_STRMZCFG_CHN);

	पूर्णांकel_ग_लिखोl(alh, SDW_ALH_STRMZCFG(pdi->पूर्णांकel_alh_id), conf);
पूर्ण

अटल पूर्णांक पूर्णांकel_params_stream(काष्ठा sdw_पूर्णांकel *sdw,
			       काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai,
			       काष्ठा snd_pcm_hw_params *hw_params,
			       पूर्णांक link_id, पूर्णांक alh_stream_id)
अणु
	काष्ठा sdw_पूर्णांकel_link_res *res = sdw->link_res;
	काष्ठा sdw_पूर्णांकel_stream_params_data params_data;

	params_data.substream = substream;
	params_data.dai = dai;
	params_data.hw_params = hw_params;
	params_data.link_id = link_id;
	params_data.alh_stream_id = alh_stream_id;

	अगर (res->ops && res->ops->params_stream && res->dev)
		वापस res->ops->params_stream(res->dev,
					       &params_data);
	वापस -EIO;
पूर्ण

अटल पूर्णांक पूर्णांकel_मुक्त_stream(काष्ठा sdw_पूर्णांकel *sdw,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai,
			     पूर्णांक link_id)
अणु
	काष्ठा sdw_पूर्णांकel_link_res *res = sdw->link_res;
	काष्ठा sdw_पूर्णांकel_stream_मुक्त_data मुक्त_data;

	मुक्त_data.substream = substream;
	मुक्त_data.dai = dai;
	मुक्त_data.link_id = link_id;

	अगर (res->ops && res->ops->मुक्त_stream && res->dev)
		वापस res->ops->मुक्त_stream(res->dev,
					     &मुक्त_data);

	वापस 0;
पूर्ण

/*
 * bank चयन routines
 */

अटल पूर्णांक पूर्णांकel_pre_bank_चयन(काष्ठा sdw_bus *bus)
अणु
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);

	/* Write to रेजिस्टर only क्रम multi-link */
	अगर (!bus->multi_link)
		वापस 0;

	पूर्णांकel_shim_sync_arm(sdw);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_post_bank_चयन(काष्ठा sdw_bus *bus)
अणु
	काष्ठा sdw_cdns *cdns = bus_to_cdns(bus);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	व्योम __iomem *shim = sdw->link_res->shim;
	पूर्णांक sync_reg, ret;

	/* Write to रेजिस्टर only क्रम multi-link */
	अगर (!bus->multi_link)
		वापस 0;

	mutex_lock(sdw->link_res->shim_lock);

	/* Read SYNC रेजिस्टर */
	sync_reg = पूर्णांकel_पढ़ोl(shim, SDW_SHIM_SYNC);

	/*
	 * post_bank_चयन() ops is called from the bus in loop क्रम
	 * all the Masters in the steam with the expectation that
	 * we trigger the bankचयन क्रम the only first Master in the list
	 * and करो nothing क्रम the other Masters
	 *
	 * So, set the SYNCGO bit only अगर CMDSYNC bit is set क्रम any Master.
	 */
	अगर (!(sync_reg & SDW_SHIM_SYNC_CMDSYNC_MASK)) अणु
		ret = 0;
		जाओ unlock;
	पूर्ण

	ret = पूर्णांकel_shim_sync_go_unlocked(sdw);
unlock:
	mutex_unlock(sdw->link_res->shim_lock);

	अगर (ret < 0)
		dev_err(sdw->cdns.dev, "Post bank switch failed: %d\n", ret);

	वापस ret;
पूर्ण

/*
 * DAI routines
 */

अटल पूर्णांक पूर्णांकel_startup(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_cdns *cdns = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(cdns->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		dev_err_ratelimited(cdns->dev,
				    "pm_runtime_get_sync failed in %s, ret %d\n",
				    __func__, ret);
		pm_runसमय_put_noidle(cdns->dev);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_cdns *cdns = snd_soc_dai_get_drvdata(dai);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_cdns_dma_data *dma;
	काष्ठा sdw_cdns_pdi *pdi;
	काष्ठा sdw_stream_config sconfig;
	काष्ठा sdw_port_config *pconfig;
	पूर्णांक ch, dir;
	पूर्णांक ret;
	bool pcm = true;

	dma = snd_soc_dai_get_dma_data(dai, substream);
	अगर (!dma)
		वापस -EIO;

	ch = params_channels(params);
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		dir = SDW_DATA_सूची_RX;
	अन्यथा
		dir = SDW_DATA_सूची_TX;

	अगर (dma->stream_type == SDW_STREAM_PDM)
		pcm = false;

	अगर (pcm)
		pdi = sdw_cdns_alloc_pdi(cdns, &cdns->pcm, ch, dir, dai->id);
	अन्यथा
		pdi = sdw_cdns_alloc_pdi(cdns, &cdns->pdm, ch, dir, dai->id);

	अगर (!pdi) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* करो run-समय configurations क्रम SHIM, ALH and PDI/PORT */
	पूर्णांकel_pdi_shim_configure(sdw, pdi);
	पूर्णांकel_pdi_alh_configure(sdw, pdi);
	sdw_cdns_config_stream(cdns, ch, dir, pdi);

	/* store pdi and hw_params, may be needed in prepare step */
	dma->suspended = false;
	dma->pdi = pdi;
	dma->hw_params = params;

	/* Inक्रमm DSP about PDI stream number */
	ret = पूर्णांकel_params_stream(sdw, substream, dai, params,
				  sdw->instance,
				  pdi->पूर्णांकel_alh_id);
	अगर (ret)
		जाओ error;

	sconfig.direction = dir;
	sconfig.ch_count = ch;
	sconfig.frame_rate = params_rate(params);
	sconfig.type = dma->stream_type;

	अगर (dma->stream_type == SDW_STREAM_PDM) अणु
		sconfig.frame_rate *= 50;
		sconfig.bps = 1;
	पूर्ण अन्यथा अणु
		sconfig.bps = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	पूर्ण

	/* Port configuration */
	pconfig = kzalloc(माप(*pconfig), GFP_KERNEL);
	अगर (!pconfig) अणु
		ret =  -ENOMEM;
		जाओ error;
	पूर्ण

	pconfig->num = pdi->num;
	pconfig->ch_mask = (1 << ch) - 1;

	ret = sdw_stream_add_master(&cdns->bus, &sconfig,
				    pconfig, 1, dma->stream);
	अगर (ret)
		dev_err(cdns->dev, "add master to stream failed:%d\n", ret);

	kमुक्त(pconfig);
error:
	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_prepare(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_cdns *cdns = snd_soc_dai_get_drvdata(dai);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_cdns_dma_data *dma;
	पूर्णांक ch, dir;
	पूर्णांक ret = 0;

	dma = snd_soc_dai_get_dma_data(dai, substream);
	अगर (!dma) अणु
		dev_err(dai->dev, "failed to get dma data in %s\n",
			__func__);
		वापस -EIO;
	पूर्ण

	अगर (dma->suspended) अणु
		dma->suspended = false;

		/*
		 * .prepare() is called after प्रणाली resume, where we
		 * need to reinitialize the SHIM/ALH/Cadence IP.
		 * .prepare() is also called to deal with underflows,
		 * but in those हालs we cannot touch ALH/SHIM
		 * रेजिस्टरs
		 */

		/* configure stream */
		ch = params_channels(dma->hw_params);
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			dir = SDW_DATA_सूची_RX;
		अन्यथा
			dir = SDW_DATA_सूची_TX;

		पूर्णांकel_pdi_shim_configure(sdw, dma->pdi);
		पूर्णांकel_pdi_alh_configure(sdw, dma->pdi);
		sdw_cdns_config_stream(cdns, ch, dir, dma->pdi);

		/* Inक्रमm DSP about PDI stream number */
		ret = पूर्णांकel_params_stream(sdw, substream, dai,
					  dma->hw_params,
					  sdw->instance,
					  dma->pdi->पूर्णांकel_alh_id);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
पूर्णांकel_hw_मुक्त(काष्ठा snd_pcm_substream *substream, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_cdns *cdns = snd_soc_dai_get_drvdata(dai);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_cdns_dma_data *dma;
	पूर्णांक ret;

	dma = snd_soc_dai_get_dma_data(dai, substream);
	अगर (!dma)
		वापस -EIO;

	/*
	 * The sdw stream state will transition to RELEASED when stream->
	 * master_list is empty. So the stream state will transition to
	 * DEPREPARED क्रम the first cpu-dai and to RELEASED क्रम the last
	 * cpu-dai.
	 */
	ret = sdw_stream_हटाओ_master(&cdns->bus, dma->stream);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "remove master from stream %s failed: %d\n",
			dma->stream->name, ret);
		वापस ret;
	पूर्ण

	ret = पूर्णांकel_मुक्त_stream(sdw, substream, dai, sdw->instance);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "intel_free_stream: failed %d\n", ret);
		वापस ret;
	पूर्ण

	dma->hw_params = शून्य;
	dma->pdi = शून्य;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_cdns *cdns = snd_soc_dai_get_drvdata(dai);

	pm_runसमय_mark_last_busy(cdns->dev);
	pm_runसमय_put_स्वतःsuspend(cdns->dev);
पूर्ण

अटल पूर्णांक पूर्णांकel_component_dais_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sdw_cdns_dma_data *dma;
	काष्ठा snd_soc_dai *dai;

	क्रम_each_component_dais(component, dai) अणु
		/*
		 * we करोn't have a .suspend dai_ops, and we don't have access
		 * to the substream, so let's mark both capture and playback
		 * DMA contexts as suspended
		 */
		dma = dai->playback_dma_data;
		अगर (dma)
			dma->suspended = true;

		dma = dai->capture_dma_data;
		अगर (dma)
			dma->suspended = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pcm_set_sdw_stream(काष्ठा snd_soc_dai *dai,
				    व्योम *stream, पूर्णांक direction)
अणु
	वापस cdns_set_sdw_stream(dai, stream, true, direction);
पूर्ण

अटल पूर्णांक पूर्णांकel_pdm_set_sdw_stream(काष्ठा snd_soc_dai *dai,
				    व्योम *stream, पूर्णांक direction)
अणु
	वापस cdns_set_sdw_stream(dai, stream, false, direction);
पूर्ण

अटल व्योम *पूर्णांकel_get_sdw_stream(काष्ठा snd_soc_dai *dai,
				  पूर्णांक direction)
अणु
	काष्ठा sdw_cdns_dma_data *dma;

	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
		dma = dai->playback_dma_data;
	अन्यथा
		dma = dai->capture_dma_data;

	अगर (!dma)
		वापस ERR_PTR(-EINVAL);

	वापस dma->stream;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops पूर्णांकel_pcm_dai_ops = अणु
	.startup = पूर्णांकel_startup,
	.hw_params = पूर्णांकel_hw_params,
	.prepare = पूर्णांकel_prepare,
	.hw_मुक्त = पूर्णांकel_hw_मुक्त,
	.shutकरोwn = पूर्णांकel_shutकरोwn,
	.set_sdw_stream = पूर्णांकel_pcm_set_sdw_stream,
	.get_sdw_stream = पूर्णांकel_get_sdw_stream,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops पूर्णांकel_pdm_dai_ops = अणु
	.startup = पूर्णांकel_startup,
	.hw_params = पूर्णांकel_hw_params,
	.prepare = पूर्णांकel_prepare,
	.hw_मुक्त = पूर्णांकel_hw_मुक्त,
	.shutकरोwn = पूर्णांकel_shutकरोwn,
	.set_sdw_stream = पूर्णांकel_pdm_set_sdw_stream,
	.get_sdw_stream = पूर्णांकel_get_sdw_stream,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver dai_component = अणु
	.name           = "soundwire",
	.suspend	= पूर्णांकel_component_dais_suspend
पूर्ण;

अटल पूर्णांक पूर्णांकel_create_dai(काष्ठा sdw_cdns *cdns,
			    काष्ठा snd_soc_dai_driver *dais,
			    क्रमागत पूर्णांकel_pdi_type type,
			    u32 num, u32 off, u32 max_ch, bool pcm)
अणु
	पूर्णांक i;

	अगर (num == 0)
		वापस 0;

	 /* TODO: Read supported rates/क्रमmats from hardware */
	क्रम (i = off; i < (off + num); i++) अणु
		dais[i].name = devm_kaप्र_लिखो(cdns->dev, GFP_KERNEL,
					      "SDW%d Pin%d",
					      cdns->instance, i);
		अगर (!dais[i].name)
			वापस -ENOMEM;

		अगर (type == INTEL_PDI_BD || type == INTEL_PDI_OUT) अणु
			dais[i].playback.channels_min = 1;
			dais[i].playback.channels_max = max_ch;
			dais[i].playback.rates = SNDRV_PCM_RATE_48000;
			dais[i].playback.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
		पूर्ण

		अगर (type == INTEL_PDI_BD || type == INTEL_PDI_IN) अणु
			dais[i].capture.channels_min = 1;
			dais[i].capture.channels_max = max_ch;
			dais[i].capture.rates = SNDRV_PCM_RATE_48000;
			dais[i].capture.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
		पूर्ण

		अगर (pcm)
			dais[i].ops = &पूर्णांकel_pcm_dai_ops;
		अन्यथा
			dais[i].ops = &पूर्णांकel_pdm_dai_ops;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_रेजिस्टर_dai(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	काष्ठा sdw_cdns *cdns = &sdw->cdns;
	काष्ठा sdw_cdns_streams *stream;
	काष्ठा snd_soc_dai_driver *dais;
	पूर्णांक num_dai, ret, off = 0;

	/* DAIs are created based on total number of PDIs supported */
	num_dai = cdns->pcm.num_pdi + cdns->pdm.num_pdi;

	dais = devm_kसुस्मृति(cdns->dev, num_dai, माप(*dais), GFP_KERNEL);
	अगर (!dais)
		वापस -ENOMEM;

	/* Create PCM DAIs */
	stream = &cdns->pcm;

	ret = पूर्णांकel_create_dai(cdns, dais, INTEL_PDI_IN, cdns->pcm.num_in,
			       off, stream->num_ch_in, true);
	अगर (ret)
		वापस ret;

	off += cdns->pcm.num_in;
	ret = पूर्णांकel_create_dai(cdns, dais, INTEL_PDI_OUT, cdns->pcm.num_out,
			       off, stream->num_ch_out, true);
	अगर (ret)
		वापस ret;

	off += cdns->pcm.num_out;
	ret = पूर्णांकel_create_dai(cdns, dais, INTEL_PDI_BD, cdns->pcm.num_bd,
			       off, stream->num_ch_bd, true);
	अगर (ret)
		वापस ret;

	/* Create PDM DAIs */
	stream = &cdns->pdm;
	off += cdns->pcm.num_bd;
	ret = पूर्णांकel_create_dai(cdns, dais, INTEL_PDI_IN, cdns->pdm.num_in,
			       off, stream->num_ch_in, false);
	अगर (ret)
		वापस ret;

	off += cdns->pdm.num_in;
	ret = पूर्णांकel_create_dai(cdns, dais, INTEL_PDI_OUT, cdns->pdm.num_out,
			       off, stream->num_ch_out, false);
	अगर (ret)
		वापस ret;

	off += cdns->pdm.num_out;
	ret = पूर्णांकel_create_dai(cdns, dais, INTEL_PDI_BD, cdns->pdm.num_bd,
			       off, stream->num_ch_bd, false);
	अगर (ret)
		वापस ret;

	वापस snd_soc_रेजिस्टर_component(cdns->dev, &dai_component,
					  dais, num_dai);
पूर्ण

अटल पूर्णांक sdw_master_पढ़ो_पूर्णांकel_prop(काष्ठा sdw_bus *bus)
अणु
	काष्ठा sdw_master_prop *prop = &bus->prop;
	काष्ठा fwnode_handle *link;
	अक्षर name[32];
	u32 quirk_mask;

	/* Find master handle */
	snम_लिखो(name, माप(name),
		 "mipi-sdw-link-%d-subproperties", bus->link_id);

	link = device_get_named_child_node(bus->dev, name);
	अगर (!link) अणु
		dev_err(bus->dev, "Master node %s not found\n", name);
		वापस -EIO;
	पूर्ण

	fwnode_property_पढ़ो_u32(link,
				 "intel-sdw-ip-clock",
				 &prop->mclk_freq);

	/* the values reported by BIOS are the 2x घड़ी, not the bus घड़ी */
	prop->mclk_freq /= 2;

	fwnode_property_पढ़ो_u32(link,
				 "intel-quirk-mask",
				 &quirk_mask);

	अगर (quirk_mask & SDW_INTEL_QUIRK_MASK_BUS_DISABLE)
		prop->hw_disabled = true;

	prop->quirks = SDW_MASTER_QUIRKS_CLEAR_INITIAL_CLASH |
		SDW_MASTER_QUIRKS_CLEAR_INITIAL_PARITY;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_prop_पढ़ो(काष्ठा sdw_bus *bus)
अणु
	/* Initialize with शेष handler to पढ़ो all DisCo properties */
	sdw_master_पढ़ो_prop(bus);

	/* पढ़ो Intel-specअगरic properties */
	sdw_master_पढ़ो_पूर्णांकel_prop(bus);

	वापस 0;
पूर्ण

अटल काष्ठा sdw_master_ops sdw_पूर्णांकel_ops = अणु
	.पढ़ो_prop = sdw_master_पढ़ो_prop,
	.override_adr = sdw_dmi_override_adr,
	.xfer_msg = cdns_xfer_msg,
	.xfer_msg_defer = cdns_xfer_msg_defer,
	.reset_page_addr = cdns_reset_page_addr,
	.set_bus_conf = cdns_bus_conf,
	.pre_bank_चयन = पूर्णांकel_pre_bank_चयन,
	.post_bank_चयन = पूर्णांकel_post_bank_चयन,
पूर्ण;

अटल पूर्णांक पूर्णांकel_init(काष्ठा sdw_पूर्णांकel *sdw)
अणु
	bool घड़ी_stop;

	/* Initialize shim and controller */
	पूर्णांकel_link_घातer_up(sdw);

	घड़ी_stop = sdw_cdns_is_घड़ी_stop(&sdw->cdns);

	पूर्णांकel_shim_init(sdw, घड़ी_stop);

	वापस 0;
पूर्ण

/*
 * probe and init
 */
अटल पूर्णांक पूर्णांकel_master_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdw_पूर्णांकel *sdw;
	काष्ठा sdw_cdns *cdns;
	काष्ठा sdw_bus *bus;
	पूर्णांक ret;

	sdw = devm_kzalloc(dev, माप(*sdw), GFP_KERNEL);
	अगर (!sdw)
		वापस -ENOMEM;

	cdns = &sdw->cdns;
	bus = &cdns->bus;

	sdw->instance = pdev->id;
	sdw->link_res = dev_get_platdata(dev);
	cdns->dev = dev;
	cdns->रेजिस्टरs = sdw->link_res->रेजिस्टरs;
	cdns->instance = sdw->instance;
	cdns->msg_count = 0;

	bus->link_id = pdev->id;

	sdw_cdns_probe(cdns);

	/* Set property पढ़ो ops */
	sdw_पूर्णांकel_ops.पढ़ो_prop = पूर्णांकel_prop_पढ़ो;
	bus->ops = &sdw_पूर्णांकel_ops;

	/* set driver data, accessed by snd_soc_dai_get_drvdata() */
	dev_set_drvdata(dev, cdns);

	/* use generic bandwidth allocation algorithm */
	sdw->cdns.bus.compute_params = sdw_compute_params;

	ret = sdw_bus_master_add(bus, dev, dev->fwnode);
	अगर (ret) अणु
		dev_err(dev, "sdw_bus_master_add fail: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (bus->prop.hw_disabled)
		dev_info(dev,
			 "SoundWire master %d is disabled, will be ignored\n",
			 bus->link_id);
	/*
	 * Ignore BIOS err_threshold, it's a really bad idea when dealing
	 * with multiple hardware synchronized links
	 */
	bus->prop.err_threshold = 0;

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_master_startup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdw_cdns_stream_config config;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdw_cdns *cdns = dev_get_drvdata(dev);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_bus *bus = &cdns->bus;
	पूर्णांक link_flags;
	bool multi_link;
	u32 घड़ी_stop_quirks;
	पूर्णांक ret;

	अगर (bus->prop.hw_disabled) अणु
		dev_info(dev,
			 "SoundWire master %d is disabled, ignoring\n",
			 sdw->instance);
		वापस 0;
	पूर्ण

	link_flags = md_flags >> (bus->link_id * 8);
	multi_link = !(link_flags & SDW_INTEL_MASTER_DISABLE_MULTI_LINK);
	अगर (!multi_link) अणु
		dev_dbg(dev, "Multi-link is disabled\n");
		bus->multi_link = false;
	पूर्ण अन्यथा अणु
		/*
		 * hardware-based synchronization is required regardless
		 * of the number of segments used by a stream: SSP-based
		 * synchronization is gated by gsync when the multi-master
		 * mode is set.
		 */
		bus->multi_link = true;
		bus->hw_sync_min_links = 1;
	पूर्ण

	/* Initialize shim, controller */
	ret = पूर्णांकel_init(sdw);
	अगर (ret)
		जाओ err_init;

	/* Read the PDI config and initialize cadence PDI */
	पूर्णांकel_pdi_init(sdw, &config);
	ret = sdw_cdns_pdi_init(cdns, config);
	अगर (ret)
		जाओ err_init;

	पूर्णांकel_pdi_ch_update(sdw);

	ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, true);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot enable interrupts\n");
		जाओ err_init;
	पूर्ण

	/*
	 * follow recommended programming flows to aव्योम समयouts when
	 * gsync is enabled
	 */
	अगर (multi_link)
		पूर्णांकel_shim_sync_arm(sdw);

	ret = sdw_cdns_init(cdns);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to initialize Cadence IP\n");
		जाओ err_पूर्णांकerrupt;
	पूर्ण

	ret = sdw_cdns_निकास_reset(cdns);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to exit bus reset sequence\n");
		जाओ err_पूर्णांकerrupt;
	पूर्ण

	अगर (multi_link) अणु
		ret = पूर्णांकel_shim_sync_go(sdw);
		अगर (ret < 0) अणु
			dev_err(dev, "sync go failed: %d\n", ret);
			जाओ err_पूर्णांकerrupt;
		पूर्ण
	पूर्ण

	/* Register DAIs */
	ret = पूर्णांकel_रेजिस्टर_dai(sdw);
	अगर (ret) अणु
		dev_err(dev, "DAI registration failed: %d\n", ret);
		snd_soc_unरेजिस्टर_component(dev);
		जाओ err_पूर्णांकerrupt;
	पूर्ण

	पूर्णांकel_debugfs_init(sdw);

	/* Enable runसमय PM */
	अगर (!(link_flags & SDW_INTEL_MASTER_DISABLE_PM_RUNTIME)) अणु
		pm_runसमय_set_स्वतःsuspend_delay(dev,
						 INTEL_MASTER_SUSPEND_DELAY_MS);
		pm_runसमय_use_स्वतःsuspend(dev);
		pm_runसमय_mark_last_busy(dev);

		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	घड़ी_stop_quirks = sdw->link_res->घड़ी_stop_quirks;
	अगर (घड़ी_stop_quirks & SDW_INTEL_CLK_STOP_NOT_ALLOWED) अणु
		/*
		 * To keep the घड़ी running we need to prevent
		 * pm_runसमय suspend from happening by increasing the
		 * reference count.
		 * This quirk is specअगरied by the parent PCI device in
		 * हाल of specअगरic latency requirements. It will have
		 * no effect अगर pm_runसमय is disabled by the user via
		 * a module parameter क्रम testing purposes.
		 */
		pm_runसमय_get_noresume(dev);
	पूर्ण

	/*
	 * The runसमय PM status of Slave devices is "Unsupported"
	 * until they report as ATTACHED. If they करोn't, e.g. because
	 * there are no Slave devices populated or अगर the घातer-on is
	 * delayed or dependent on a घातer चयन, the Master will
	 * reमुख्य active and prevent its parent from suspending.
	 *
	 * Conditionally क्रमce the pm_runसमय core to re-evaluate the
	 * Master status in the असलence of any Slave activity. A quirk
	 * is provided to e.g. deal with Slaves that may be घातered on
	 * with a delay. A more complete solution would require the
	 * definition of Master properties.
	 */
	अगर (!(link_flags & SDW_INTEL_MASTER_DISABLE_PM_RUNTIME_IDLE))
		pm_runसमय_idle(dev);

	वापस 0;

err_पूर्णांकerrupt:
	sdw_cdns_enable_पूर्णांकerrupt(cdns, false);
err_init:
	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_master_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdw_cdns *cdns = dev_get_drvdata(dev);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_bus *bus = &cdns->bus;

	/*
	 * Since pm_runसमय is alपढ़ोy disabled, we करोn't decrease
	 * the refcount when the घड़ी_stop_quirk is
	 * SDW_INTEL_CLK_STOP_NOT_ALLOWED
	 */
	अगर (!bus->prop.hw_disabled) अणु
		पूर्णांकel_debugfs_निकास(sdw);
		sdw_cdns_enable_पूर्णांकerrupt(cdns, false);
		snd_soc_unरेजिस्टर_component(dev);
	पूर्ण
	sdw_bus_master_delete(bus);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_master_process_wakeen_event(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdw_पूर्णांकel *sdw;
	काष्ठा sdw_bus *bus;
	व्योम __iomem *shim;
	u16 wake_sts;

	sdw = platक्रमm_get_drvdata(pdev);
	bus = &sdw->cdns.bus;

	अगर (bus->prop.hw_disabled) अणु
		dev_dbg(dev, "SoundWire master %d is disabled, ignoring\n", bus->link_id);
		वापस 0;
	पूर्ण

	shim = sdw->link_res->shim;
	wake_sts = पूर्णांकel_पढ़ोw(shim, SDW_SHIM_WAKESTS);

	अगर (!(wake_sts & BIT(sdw->instance)))
		वापस 0;

	/* disable WAKEEN पूर्णांकerrupt ASAP to prevent पूर्णांकerrupt flood */
	पूर्णांकel_shim_wake(sdw, false);

	/*
	 * resume the Master, which will generate a bus reset and result in
	 * Slaves re-attaching and be re-क्रमागतerated. The SoundWire physical
	 * device which generated the wake will trigger an पूर्णांकerrupt, which
	 * will in turn cause the corresponding Linux Slave device to be
	 * resumed and the Slave codec driver to check the status.
	 */
	pm_request_resume(dev);

	वापस 0;
पूर्ण

/*
 * PM calls
 */

अटल पूर्णांक __maybe_unused पूर्णांकel_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdw_cdns *cdns = dev_get_drvdata(dev);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_bus *bus = &cdns->bus;
	u32 घड़ी_stop_quirks;
	पूर्णांक ret;

	अगर (bus->prop.hw_disabled) अणु
		dev_dbg(dev, "SoundWire master %d is disabled, ignoring\n",
			bus->link_id);
		वापस 0;
	पूर्ण

	अगर (pm_runसमय_suspended(dev)) अणु
		dev_dbg(dev, "%s: pm_runtime status: suspended\n", __func__);

		घड़ी_stop_quirks = sdw->link_res->घड़ी_stop_quirks;

		अगर ((घड़ी_stop_quirks & SDW_INTEL_CLK_STOP_BUS_RESET ||
		     !घड़ी_stop_quirks) &&
		    !pm_runसमय_suspended(dev->parent)) अणु

			/*
			 * अगर we've enabled घड़ी stop, and the parent
			 * is still active, disable shim wake. The
			 * SHIM रेजिस्टरs are not accessible अगर the
			 * parent is alपढ़ोy pm_runसमय suspended so
			 * it's too late to change that configuration
			 */

			पूर्णांकel_shim_wake(sdw, false);
		पूर्ण

		वापस 0;
	पूर्ण

	ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, false);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot disable interrupts on suspend\n");
		वापस ret;
	पूर्ण

	ret = पूर्णांकel_link_घातer_करोwn(sdw);
	अगर (ret) अणु
		dev_err(dev, "Link power down failed: %d\n", ret);
		वापस ret;
	पूर्ण

	पूर्णांकel_shim_wake(sdw, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_suspend_runसमय(काष्ठा device *dev)
अणु
	काष्ठा sdw_cdns *cdns = dev_get_drvdata(dev);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_bus *bus = &cdns->bus;
	u32 घड़ी_stop_quirks;
	पूर्णांक ret;

	अगर (bus->prop.hw_disabled) अणु
		dev_dbg(dev, "SoundWire master %d is disabled, ignoring\n",
			bus->link_id);
		वापस 0;
	पूर्ण

	घड़ी_stop_quirks = sdw->link_res->घड़ी_stop_quirks;

	अगर (घड़ी_stop_quirks & SDW_INTEL_CLK_STOP_TEARDOWN) अणु

		ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, false);
		अगर (ret < 0) अणु
			dev_err(dev, "cannot disable interrupts on suspend\n");
			वापस ret;
		पूर्ण

		ret = पूर्णांकel_link_घातer_करोwn(sdw);
		अगर (ret) अणु
			dev_err(dev, "Link power down failed: %d\n", ret);
			वापस ret;
		पूर्ण

		पूर्णांकel_shim_wake(sdw, false);

	पूर्ण अन्यथा अगर (घड़ी_stop_quirks & SDW_INTEL_CLK_STOP_BUS_RESET ||
		   !घड़ी_stop_quirks) अणु
		bool wake_enable = true;

		ret = sdw_cdns_घड़ी_stop(cdns, true);
		अगर (ret < 0) अणु
			dev_err(dev, "cannot enable clock stop on suspend\n");
			wake_enable = false;
		पूर्ण

		ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, false);
		अगर (ret < 0) अणु
			dev_err(dev, "cannot disable interrupts on suspend\n");
			वापस ret;
		पूर्ण

		ret = पूर्णांकel_link_घातer_करोwn(sdw);
		अगर (ret) अणु
			dev_err(dev, "Link power down failed: %d\n", ret);
			वापस ret;
		पूर्ण

		पूर्णांकel_shim_wake(sdw, wake_enable);
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s clock_stop_quirks %x unsupported\n",
			__func__, घड़ी_stop_quirks);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_cdns *cdns = dev_get_drvdata(dev);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_bus *bus = &cdns->bus;
	पूर्णांक link_flags;
	bool multi_link;
	पूर्णांक ret;

	अगर (bus->prop.hw_disabled) अणु
		dev_dbg(dev, "SoundWire master %d is disabled, ignoring\n",
			bus->link_id);
		वापस 0;
	पूर्ण

	link_flags = md_flags >> (bus->link_id * 8);
	multi_link = !(link_flags & SDW_INTEL_MASTER_DISABLE_MULTI_LINK);

	अगर (pm_runसमय_suspended(dev)) अणु
		dev_dbg(dev, "%s: pm_runtime status was suspended, forcing active\n", __func__);

		/* follow required sequence from runसमय_pm.rst */
		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_mark_last_busy(dev);
		pm_runसमय_enable(dev);

		link_flags = md_flags >> (bus->link_id * 8);

		अगर (!(link_flags & SDW_INTEL_MASTER_DISABLE_PM_RUNTIME_IDLE))
			pm_runसमय_idle(dev);
	पूर्ण

	ret = पूर्णांकel_init(sdw);
	अगर (ret) अणु
		dev_err(dev, "%s failed: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	/*
	 * make sure all Slaves are tagged as UNATTACHED and provide
	 * reason क्रम reinitialization
	 */
	sdw_clear_slave_status(bus, SDW_UNATTACH_REQUEST_MASTER_RESET);

	ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, true);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot enable interrupts during resume\n");
		वापस ret;
	पूर्ण

	/*
	 * follow recommended programming flows to aव्योम समयouts when
	 * gsync is enabled
	 */
	अगर (multi_link)
		पूर्णांकel_shim_sync_arm(sdw);

	ret = sdw_cdns_init(&sdw->cdns);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to initialize Cadence IP during resume\n");
		वापस ret;
	पूर्ण

	ret = sdw_cdns_निकास_reset(cdns);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to exit bus reset sequence during resume\n");
		वापस ret;
	पूर्ण

	अगर (multi_link) अणु
		ret = पूर्णांकel_shim_sync_go(sdw);
		अगर (ret < 0) अणु
			dev_err(dev, "sync go failed during resume\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * after प्रणाली resume, the pm_runसमय suspend() may kick in
	 * during the क्रमागतeration, beक्रमe any children device क्रमce the
	 * master device to reमुख्य active.  Using pm_runसमय_get()
	 * routines is not really possible, since it'd prevent the
	 * master from suspending.
	 * A reasonable compromise is to update the pm_runसमय
	 * counters and delay the pm_runसमय suspend by several
	 * seconds, by when all क्रमागतeration should be complete.
	 */
	pm_runसमय_mark_last_busy(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_resume_runसमय(काष्ठा device *dev)
अणु
	काष्ठा sdw_cdns *cdns = dev_get_drvdata(dev);
	काष्ठा sdw_पूर्णांकel *sdw = cdns_to_पूर्णांकel(cdns);
	काष्ठा sdw_bus *bus = &cdns->bus;
	u32 घड़ी_stop_quirks;
	bool घड़ी_stop0;
	पूर्णांक link_flags;
	bool multi_link;
	पूर्णांक status;
	पूर्णांक ret;

	अगर (bus->prop.hw_disabled) अणु
		dev_dbg(dev, "SoundWire master %d is disabled, ignoring\n",
			bus->link_id);
		वापस 0;
	पूर्ण

	link_flags = md_flags >> (bus->link_id * 8);
	multi_link = !(link_flags & SDW_INTEL_MASTER_DISABLE_MULTI_LINK);

	घड़ी_stop_quirks = sdw->link_res->घड़ी_stop_quirks;

	अगर (घड़ी_stop_quirks & SDW_INTEL_CLK_STOP_TEARDOWN) अणु
		ret = पूर्णांकel_init(sdw);
		अगर (ret) अणु
			dev_err(dev, "%s failed: %d\n", __func__, ret);
			वापस ret;
		पूर्ण

		/*
		 * make sure all Slaves are tagged as UNATTACHED and provide
		 * reason क्रम reinitialization
		 */
		sdw_clear_slave_status(bus, SDW_UNATTACH_REQUEST_MASTER_RESET);

		ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, true);
		अगर (ret < 0) अणु
			dev_err(dev, "cannot enable interrupts during resume\n");
			वापस ret;
		पूर्ण

		/*
		 * follow recommended programming flows to aव्योम
		 * समयouts when gsync is enabled
		 */
		अगर (multi_link)
			पूर्णांकel_shim_sync_arm(sdw);

		ret = sdw_cdns_init(&sdw->cdns);
		अगर (ret < 0) अणु
			dev_err(dev, "unable to initialize Cadence IP during resume\n");
			वापस ret;
		पूर्ण

		ret = sdw_cdns_निकास_reset(cdns);
		अगर (ret < 0) अणु
			dev_err(dev, "unable to exit bus reset sequence during resume\n");
			वापस ret;
		पूर्ण

		अगर (multi_link) अणु
			ret = पूर्णांकel_shim_sync_go(sdw);
			अगर (ret < 0) अणु
				dev_err(dev, "sync go failed during resume\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (घड़ी_stop_quirks & SDW_INTEL_CLK_STOP_BUS_RESET) अणु
		ret = पूर्णांकel_init(sdw);
		अगर (ret) अणु
			dev_err(dev, "%s failed: %d\n", __func__, ret);
			वापस ret;
		पूर्ण

		/*
		 * An exception condition occurs क्रम the CLK_STOP_BUS_RESET
		 * हाल अगर one or more masters reमुख्य active. In this condition,
		 * all the masters are घातered on क्रम they are in the same घातer
		 * करोमुख्य. Master can preserve its context क्रम घड़ी stop0, so
		 * there is no need to clear slave status and reset bus.
		 */
		घड़ी_stop0 = sdw_cdns_is_घड़ी_stop(&sdw->cdns);

		अगर (!घड़ी_stop0) अणु

			/*
			 * make sure all Slaves are tagged as UNATTACHED and
			 * provide reason क्रम reinitialization
			 */

			status = SDW_UNATTACH_REQUEST_MASTER_RESET;
			sdw_clear_slave_status(bus, status);

			ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, true);
			अगर (ret < 0) अणु
				dev_err(dev, "cannot enable interrupts during resume\n");
				वापस ret;
			पूर्ण

			/*
			 * follow recommended programming flows to aव्योम
			 * समयouts when gsync is enabled
			 */
			अगर (multi_link)
				पूर्णांकel_shim_sync_arm(sdw);

			/*
			 * Re-initialize the IP since it was घातered-off
			 */
			sdw_cdns_init(&sdw->cdns);

		पूर्ण अन्यथा अणु
			ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, true);
			अगर (ret < 0) अणु
				dev_err(dev, "cannot enable interrupts during resume\n");
				वापस ret;
			पूर्ण
		पूर्ण

		ret = sdw_cdns_घड़ी_restart(cdns, !घड़ी_stop0);
		अगर (ret < 0) अणु
			dev_err(dev, "unable to restart clock during resume\n");
			वापस ret;
		पूर्ण

		अगर (!घड़ी_stop0) अणु
			ret = sdw_cdns_निकास_reset(cdns);
			अगर (ret < 0) अणु
				dev_err(dev, "unable to exit bus reset sequence during resume\n");
				वापस ret;
			पूर्ण

			अगर (multi_link) अणु
				ret = पूर्णांकel_shim_sync_go(sdw);
				अगर (ret < 0) अणु
					dev_err(sdw->cdns.dev, "sync go failed during resume\n");
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (!घड़ी_stop_quirks) अणु

		घड़ी_stop0 = sdw_cdns_is_घड़ी_stop(&sdw->cdns);
		अगर (!घड़ी_stop0)
			dev_err(dev, "%s invalid configuration, clock was not stopped", __func__);

		ret = पूर्णांकel_init(sdw);
		अगर (ret) अणु
			dev_err(dev, "%s failed: %d\n", __func__, ret);
			वापस ret;
		पूर्ण

		ret = sdw_cdns_enable_पूर्णांकerrupt(cdns, true);
		अगर (ret < 0) अणु
			dev_err(dev, "cannot enable interrupts during resume\n");
			वापस ret;
		पूर्ण

		ret = sdw_cdns_घड़ी_restart(cdns, false);
		अगर (ret < 0) अणु
			dev_err(dev, "unable to resume master during resume\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s clock_stop_quirks %x unsupported\n",
			__func__, घड़ी_stop_quirks);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops पूर्णांकel_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(पूर्णांकel_suspend, पूर्णांकel_resume)
	SET_RUNTIME_PM_OPS(पूर्णांकel_suspend_runसमय, पूर्णांकel_resume_runसमय, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sdw_पूर्णांकel_drv = अणु
	.probe = पूर्णांकel_master_probe,
	.हटाओ = पूर्णांकel_master_हटाओ,
	.driver = अणु
		.name = "intel-sdw",
		.pm = &पूर्णांकel_pm,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(sdw_पूर्णांकel_drv);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:intel-sdw");
MODULE_DESCRIPTION("Intel Soundwire Master Driver");
