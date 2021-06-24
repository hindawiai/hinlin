<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  skl-nhlt.c - Intel SKL Platक्रमm NHLT parsing
 *
 *  Copyright (C) 2015 Intel Corp
 *  Author: Sanjiv Kumar <sanjiv.kumar@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <linux/pci.h>
#समावेश <sound/पूर्णांकel-nhlt.h>
#समावेश "skl.h"
#समावेश "skl-i2s.h"

अटल काष्ठा nhlt_specअगरic_cfg *skl_get_specअगरic_cfg(
		काष्ठा device *dev, काष्ठा nhlt_fmt *fmt,
		u8 no_ch, u32 rate, u16 bps, u8 linktype)
अणु
	काष्ठा nhlt_specअगरic_cfg *sp_config;
	काष्ठा wav_fmt *wfmt;
	काष्ठा nhlt_fmt_cfg *fmt_config = fmt->fmt_config;
	पूर्णांक i;

	dev_dbg(dev, "Format count =%d\n", fmt->fmt_count);

	क्रम (i = 0; i < fmt->fmt_count; i++) अणु
		wfmt = &fmt_config->fmt_ext.fmt;
		dev_dbg(dev, "ch=%d fmt=%d s_rate=%d\n", wfmt->channels,
			 wfmt->bits_per_sample, wfmt->samples_per_sec);
		अगर (wfmt->channels == no_ch && wfmt->bits_per_sample == bps) अणु
			/*
			 * अगर link type is dmic ignore rate check as the blob is
			 * generic क्रम all rates
			 */
			sp_config = &fmt_config->config;
			अगर (linktype == NHLT_LINK_DMIC)
				वापस sp_config;

			अगर (wfmt->samples_per_sec == rate)
				वापस sp_config;
		पूर्ण

		fmt_config = (काष्ठा nhlt_fmt_cfg *)(fmt_config->config.caps +
						fmt_config->config.size);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम dump_config(काष्ठा device *dev, u32 instance_id, u8 linktype,
		u8 s_fmt, u8 num_channels, u32 s_rate, u8 dirn, u16 bps)
अणु
	dev_dbg(dev, "Input configuration\n");
	dev_dbg(dev, "ch=%d fmt=%d s_rate=%d\n", num_channels, s_fmt, s_rate);
	dev_dbg(dev, "vbus_id=%d link_type=%d\n", instance_id, linktype);
	dev_dbg(dev, "bits_per_sample=%d\n", bps);
पूर्ण

अटल bool skl_check_ep_match(काष्ठा device *dev, काष्ठा nhlt_endpoपूर्णांक *epnt,
		u32 instance_id, u8 link_type, u8 dirn, u8 dev_type)
अणु
	dev_dbg(dev, "vbus_id=%d link_type=%d dir=%d dev_type = %d\n",
			epnt->भव_bus_id, epnt->linktype,
			epnt->direction, epnt->device_type);

	अगर ((epnt->भव_bus_id == instance_id) &&
			(epnt->linktype == link_type) &&
			(epnt->direction == dirn)) अणु
		/* करो not check dev_type क्रम DMIC link type */
		अगर (epnt->linktype == NHLT_LINK_DMIC)
			वापस true;

		अगर (epnt->device_type == dev_type)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

काष्ठा nhlt_specअगरic_cfg
*skl_get_ep_blob(काष्ठा skl_dev *skl, u32 instance, u8 link_type,
			u8 s_fmt, u8 num_ch, u32 s_rate,
			u8 dirn, u8 dev_type)
अणु
	काष्ठा nhlt_fmt *fmt;
	काष्ठा nhlt_endpoपूर्णांक *epnt;
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	काष्ठा device *dev = bus->dev;
	काष्ठा nhlt_specअगरic_cfg *sp_config;
	काष्ठा nhlt_acpi_table *nhlt = skl->nhlt;
	u16 bps = (s_fmt == 16) ? 16 : 32;
	u8 j;

	dump_config(dev, instance, link_type, s_fmt, num_ch, s_rate, dirn, bps);

	epnt = (काष्ठा nhlt_endpoपूर्णांक *)nhlt->desc;

	dev_dbg(dev, "endpoint count =%d\n", nhlt->endpoपूर्णांक_count);

	क्रम (j = 0; j < nhlt->endpoपूर्णांक_count; j++) अणु
		अगर (skl_check_ep_match(dev, epnt, instance, link_type,
						dirn, dev_type)) अणु
			fmt = (काष्ठा nhlt_fmt *)(epnt->config.caps +
						 epnt->config.size);
			sp_config = skl_get_specअगरic_cfg(dev, fmt, num_ch,
							s_rate, bps, link_type);
			अगर (sp_config)
				वापस sp_config;
		पूर्ण

		epnt = (काष्ठा nhlt_endpoपूर्णांक *)((u8 *)epnt + epnt->length);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम skl_nhlt_trim_space(अक्षर *trim)
अणु
	अक्षर *s = trim;
	पूर्णांक cnt;
	पूर्णांक i;

	cnt = 0;
	क्रम (i = 0; s[i]; i++) अणु
		अगर (!है_खाली(s[i]))
			s[cnt++] = s[i];
	पूर्ण

	s[cnt] = '\0';
पूर्ण

पूर्णांक skl_nhlt_update_topology_bin(काष्ठा skl_dev *skl)
अणु
	काष्ठा nhlt_acpi_table *nhlt = (काष्ठा nhlt_acpi_table *)skl->nhlt;
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	काष्ठा device *dev = bus->dev;

	dev_dbg(dev, "oem_id %.6s, oem_table_id %.8s oem_revision %d\n",
		nhlt->header.oem_id, nhlt->header.oem_table_id,
		nhlt->header.oem_revision);

	snम_लिखो(skl->tplg_name, माप(skl->tplg_name), "%x-%.6s-%.8s-%d%s",
		skl->pci_id, nhlt->header.oem_id, nhlt->header.oem_table_id,
		nhlt->header.oem_revision, "-tplg.bin");

	skl_nhlt_trim_space(skl->tplg_name);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार skl_nhlt_platक्रमm_id_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा hdac_bus *bus = pci_get_drvdata(pci);
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा nhlt_acpi_table *nhlt = (काष्ठा nhlt_acpi_table *)skl->nhlt;
	अक्षर platक्रमm_id[32];

	प्र_लिखो(platक्रमm_id, "%x-%.6s-%.8s-%d", skl->pci_id,
			nhlt->header.oem_id, nhlt->header.oem_table_id,
			nhlt->header.oem_revision);

	skl_nhlt_trim_space(platक्रमm_id);
	वापस प्र_लिखो(buf, "%s\n", platक्रमm_id);
पूर्ण

अटल DEVICE_ATTR(platक्रमm_id, 0444, skl_nhlt_platक्रमm_id_show, शून्य);

पूर्णांक skl_nhlt_create_sysfs(काष्ठा skl_dev *skl)
अणु
	काष्ठा device *dev = &skl->pci->dev;

	अगर (sysfs_create_file(&dev->kobj, &dev_attr_platक्रमm_id.attr))
		dev_warn(dev, "Error creating sysfs entry\n");

	वापस 0;
पूर्ण

व्योम skl_nhlt_हटाओ_sysfs(काष्ठा skl_dev *skl)
अणु
	काष्ठा device *dev = &skl->pci->dev;

	अगर (skl->nhlt)
		sysfs_हटाओ_file(&dev->kobj, &dev_attr_platक्रमm_id.attr);
पूर्ण

/*
 * Queries NHLT क्रम all the fmt configuration क्रम a particular endpoपूर्णांक and
 * stores all possible rates supported in a rate table क्रम the corresponding
 * sclk/sclkfs.
 */
अटल व्योम skl_get_ssp_clks(काष्ठा skl_dev *skl, काष्ठा skl_ssp_clk *ssp_clks,
				काष्ठा nhlt_fmt *fmt, u8 id)
अणु
	काष्ठा skl_i2s_config_blob_ext *i2s_config_ext;
	काष्ठा skl_i2s_config_blob_legacy *i2s_config;
	काष्ठा skl_clk_parent_src *parent;
	काष्ठा skl_ssp_clk *sclk, *sclkfs;
	काष्ठा nhlt_fmt_cfg *fmt_cfg;
	काष्ठा wav_fmt_ext *wav_fmt;
	अचिन्हित दीर्घ rate;
	bool present = false;
	पूर्णांक rate_index = 0;
	u16 channels, bps;
	u8 clk_src;
	पूर्णांक i, j;
	u32 fs;

	sclk = &ssp_clks[SKL_SCLK_OFS];
	sclkfs = &ssp_clks[SKL_SCLKFS_OFS];

	अगर (fmt->fmt_count == 0)
		वापस;

	क्रम (i = 0; i < fmt->fmt_count; i++) अणु
		fmt_cfg = &fmt->fmt_config[i];
		wav_fmt = &fmt_cfg->fmt_ext;

		channels = wav_fmt->fmt.channels;
		bps = wav_fmt->fmt.bits_per_sample;
		fs = wav_fmt->fmt.samples_per_sec;

		/*
		 * In हाल of TDM configuration on a ssp, there can
		 * be more than one blob in which channel masks are
		 * dअगरferent क्रम each useहाल क्रम a specअगरic rate and bps.
		 * But the sclk rate will be generated क्रम the total
		 * number of channels used क्रम that endpoपूर्णांक.
		 *
		 * So क्रम the given fs and bps, choose blob which has
		 * the superset of all channels क्रम that endpoपूर्णांक and
		 * derive the rate.
		 */
		क्रम (j = i; j < fmt->fmt_count; j++) अणु
			fmt_cfg = &fmt->fmt_config[j];
			wav_fmt = &fmt_cfg->fmt_ext;
			अगर ((fs == wav_fmt->fmt.samples_per_sec) &&
			   (bps == wav_fmt->fmt.bits_per_sample))
				channels = max_t(u16, channels,
						wav_fmt->fmt.channels);
		पूर्ण

		rate = channels * bps * fs;

		/* check अगर the rate is added alपढ़ोy to the given SSP's sclk */
		क्रम (j = 0; (j < SKL_MAX_CLK_RATES) &&
			    (sclk[id].rate_cfg[j].rate != 0); j++) अणु
			अगर (sclk[id].rate_cfg[j].rate == rate) अणु
				present = true;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Fill rate and parent क्रम sclk/sclkfs */
		अगर (!present) अणु
			i2s_config_ext = (काष्ठा skl_i2s_config_blob_ext *)
						fmt->fmt_config[0].config.caps;

			/* MCLK Divider Source Select */
			अगर (is_legacy_blob(i2s_config_ext->hdr.sig)) अणु
				i2s_config = ext_to_legacy_blob(i2s_config_ext);
				clk_src = get_clk_src(i2s_config->mclk,
						SKL_MNDSS_DIV_CLK_SRC_MASK);
			पूर्ण अन्यथा अणु
				clk_src = get_clk_src(i2s_config_ext->mclk,
						SKL_MNDSS_DIV_CLK_SRC_MASK);
			पूर्ण

			parent = skl_get_parent_clk(clk_src);

			/*
			 * Do not copy the config data अगर there is no parent
			 * घड़ी available क्रम this घड़ी source select
			 */
			अगर (!parent)
				जारी;

			sclk[id].rate_cfg[rate_index].rate = rate;
			sclk[id].rate_cfg[rate_index].config = fmt_cfg;
			sclkfs[id].rate_cfg[rate_index].rate = rate;
			sclkfs[id].rate_cfg[rate_index].config = fmt_cfg;
			sclk[id].parent_name = parent->name;
			sclkfs[id].parent_name = parent->name;

			rate_index++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम skl_get_mclk(काष्ठा skl_dev *skl, काष्ठा skl_ssp_clk *mclk,
				काष्ठा nhlt_fmt *fmt, u8 id)
अणु
	काष्ठा skl_i2s_config_blob_ext *i2s_config_ext;
	काष्ठा skl_i2s_config_blob_legacy *i2s_config;
	काष्ठा nhlt_specअगरic_cfg *fmt_cfg;
	काष्ठा skl_clk_parent_src *parent;
	u32 clkभाग, भाग_ratio;
	u8 clk_src;

	fmt_cfg = &fmt->fmt_config[0].config;
	i2s_config_ext = (काष्ठा skl_i2s_config_blob_ext *)fmt_cfg->caps;

	/* MCLK Divider Source Select and भागider */
	अगर (is_legacy_blob(i2s_config_ext->hdr.sig)) अणु
		i2s_config = ext_to_legacy_blob(i2s_config_ext);
		clk_src = get_clk_src(i2s_config->mclk,
				SKL_MCLK_DIV_CLK_SRC_MASK);
		clkभाग = i2s_config->mclk.mभागr &
				SKL_MCLK_DIV_RATIO_MASK;
	पूर्ण अन्यथा अणु
		clk_src = get_clk_src(i2s_config_ext->mclk,
				SKL_MCLK_DIV_CLK_SRC_MASK);
		clkभाग = i2s_config_ext->mclk.mभागr[0] &
				SKL_MCLK_DIV_RATIO_MASK;
	पूर्ण

	/* bypass भागider */
	भाग_ratio = 1;

	अगर (clkभाग != SKL_MCLK_DIV_RATIO_MASK)
		/* Divider is 2 + clkभाग */
		भाग_ratio = clkभाग + 2;

	/* Calculate MCLK rate from source using भाग value */
	parent = skl_get_parent_clk(clk_src);
	अगर (!parent)
		वापस;

	mclk[id].rate_cfg[0].rate = parent->rate/भाग_ratio;
	mclk[id].rate_cfg[0].config = &fmt->fmt_config[0];
	mclk[id].parent_name = parent->name;
पूर्ण

व्योम skl_get_clks(काष्ठा skl_dev *skl, काष्ठा skl_ssp_clk *ssp_clks)
अणु
	काष्ठा nhlt_acpi_table *nhlt = (काष्ठा nhlt_acpi_table *)skl->nhlt;
	काष्ठा nhlt_endpoपूर्णांक *epnt;
	काष्ठा nhlt_fmt *fmt;
	पूर्णांक i;
	u8 id;

	epnt = (काष्ठा nhlt_endpoपूर्णांक *)nhlt->desc;
	क्रम (i = 0; i < nhlt->endpoपूर्णांक_count; i++) अणु
		अगर (epnt->linktype == NHLT_LINK_SSP) अणु
			id = epnt->भव_bus_id;

			fmt = (काष्ठा nhlt_fmt *)(epnt->config.caps
					+ epnt->config.size);

			skl_get_ssp_clks(skl, ssp_clks, fmt, id);
			skl_get_mclk(skl, ssp_clks, fmt, id);
		पूर्ण
		epnt = (काष्ठा nhlt_endpoपूर्णांक *)((u8 *)epnt + epnt->length);
	पूर्ण
पूर्ण
