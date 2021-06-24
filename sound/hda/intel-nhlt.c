<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2015-2019 Intel Corporation

#समावेश <linux/acpi.h>
#समावेश <sound/पूर्णांकel-nhlt.h>

काष्ठा nhlt_acpi_table *पूर्णांकel_nhlt_init(काष्ठा device *dev)
अणु
	काष्ठा nhlt_acpi_table *nhlt;
	acpi_status status;

	status = acpi_get_table(ACPI_SIG_NHLT, 0,
				(काष्ठा acpi_table_header **)&nhlt);
	अगर (ACPI_FAILURE(status)) अणु
		dev_warn(dev, "NHLT table not found\n");
		वापस शून्य;
	पूर्ण

	वापस nhlt;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_nhlt_init);

व्योम पूर्णांकel_nhlt_मुक्त(काष्ठा nhlt_acpi_table *nhlt)
अणु
	acpi_put_table((काष्ठा acpi_table_header *)nhlt);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_nhlt_मुक्त);

पूर्णांक पूर्णांकel_nhlt_get_dmic_geo(काष्ठा device *dev, काष्ठा nhlt_acpi_table *nhlt)
अणु
	काष्ठा nhlt_endpoपूर्णांक *epnt;
	काष्ठा nhlt_dmic_array_config *cfg;
	काष्ठा nhlt_venकरोr_dmic_array_config *cfg_venकरोr;
	काष्ठा nhlt_fmt *fmt_configs;
	अचिन्हित पूर्णांक dmic_geo = 0;
	u16 max_ch = 0;
	u8 i, j;

	अगर (!nhlt)
		वापस 0;

	अगर (nhlt->header.length <= माप(काष्ठा acpi_table_header)) अणु
		dev_warn(dev, "Invalid DMIC description table\n");
		वापस 0;
	पूर्ण

	क्रम (j = 0, epnt = nhlt->desc; j < nhlt->endpoपूर्णांक_count; j++,
	     epnt = (काष्ठा nhlt_endpoपूर्णांक *)((u8 *)epnt + epnt->length)) अणु

		अगर (epnt->linktype != NHLT_LINK_DMIC)
			जारी;

		cfg = (काष्ठा nhlt_dmic_array_config  *)(epnt->config.caps);
		fmt_configs = (काष्ठा nhlt_fmt *)(epnt->config.caps + epnt->config.size);

		/* find max number of channels based on क्रमmat_configuration */
		अगर (fmt_configs->fmt_count) अणु
			dev_dbg(dev, "%s: found %d format definitions\n",
				__func__, fmt_configs->fmt_count);

			क्रम (i = 0; i < fmt_configs->fmt_count; i++) अणु
				काष्ठा wav_fmt_ext *fmt_ext;

				fmt_ext = &fmt_configs->fmt_config[i].fmt_ext;

				अगर (fmt_ext->fmt.channels > max_ch)
					max_ch = fmt_ext->fmt.channels;
			पूर्ण
			dev_dbg(dev, "%s: max channels found %d\n", __func__, max_ch);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "%s: No format information found\n", __func__);
		पूर्ण

		अगर (cfg->device_config.config_type != NHLT_CONFIG_TYPE_MIC_ARRAY) अणु
			dmic_geo = max_ch;
		पूर्ण अन्यथा अणु
			चयन (cfg->array_type) अणु
			हाल NHLT_MIC_ARRAY_2CH_SMALL:
			हाल NHLT_MIC_ARRAY_2CH_BIG:
				dmic_geo = MIC_ARRAY_2CH;
				अवरोध;

			हाल NHLT_MIC_ARRAY_4CH_1ST_GEOM:
			हाल NHLT_MIC_ARRAY_4CH_L_SHAPED:
			हाल NHLT_MIC_ARRAY_4CH_2ND_GEOM:
				dmic_geo = MIC_ARRAY_4CH;
				अवरोध;
			हाल NHLT_MIC_ARRAY_VENDOR_DEFINED:
				cfg_venकरोr = (काष्ठा nhlt_venकरोr_dmic_array_config *)cfg;
				dmic_geo = cfg_venकरोr->nb_mics;
				अवरोध;
			शेष:
				dev_warn(dev, "%s: undefined DMIC array_type 0x%0x\n",
					 __func__, cfg->array_type);
			पूर्ण

			अगर (dmic_geo > 0) अणु
				dev_dbg(dev, "%s: Array with %d dmics\n", __func__, dmic_geo);
			पूर्ण
			अगर (max_ch > dmic_geo) अणु
				dev_dbg(dev, "%s: max channels %d exceed dmic number %d\n",
					__func__, max_ch, dmic_geo);
			पूर्ण
		पूर्ण
	पूर्ण

	dev_dbg(dev, "%s: dmic number %d max_ch %d\n",
		__func__, dmic_geo, max_ch);

	वापस dmic_geo;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_nhlt_get_dmic_geo);
