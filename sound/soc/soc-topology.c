<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-topology.c  --  ALSA SoC Topology
//
// Copyright (C) 2012 Texas Instruments Inc.
// Copyright (C) 2015 Intel Corporation.
//
// Authors: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//		K, Mythri P <mythri.p.k@पूर्णांकel.com>
//		Prusty, Subhransu S <subhransu.s.prusty@पूर्णांकel.com>
//		B, Jayachandran <jayachandran.b@पूर्णांकel.com>
//		Abdullah, Omair M <omair.m.abdullah@पूर्णांकel.com>
//		Jin, Yao <yao.jin@पूर्णांकel.com>
//		Lin, Mengकरोng <mengकरोng.lin@पूर्णांकel.com>
//
//  Add support to पढ़ो audio firmware topology aदीर्घside firmware text. The
//  topology data can contain kcontrols, DAPM graphs, widमाला_लो, DAIs, DAI links,
//  equalizers, firmware, coefficients etc.
//
//  This file only manages the core ALSA and ASoC components, all other bespoke
//  firmware topology data is passed to component drivers क्रम bespoke handling.

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/soc-topology.h>
#समावेश <sound/tlv.h>

#घोषणा SOC_TPLG_MAGIC_BIG_ENDIAN            0x436F5341 /* ASoC in reverse */

/*
 * We make several passes over the data (since it wont necessarily be ordered)
 * and process objects in the following order. This guarantees the component
 * drivers will be पढ़ोy with any venकरोr data beक्रमe the mixers and DAPM objects
 * are loaded (that may make use of the venकरोr data).
 */
#घोषणा SOC_TPLG_PASS_MANIFEST		0
#घोषणा SOC_TPLG_PASS_VENDOR		1
#घोषणा SOC_TPLG_PASS_MIXER		2
#घोषणा SOC_TPLG_PASS_WIDGET		3
#घोषणा SOC_TPLG_PASS_PCM_DAI		4
#घोषणा SOC_TPLG_PASS_GRAPH		5
#घोषणा SOC_TPLG_PASS_PINS		6
#घोषणा SOC_TPLG_PASS_BE_DAI		7
#घोषणा SOC_TPLG_PASS_LINK		8

#घोषणा SOC_TPLG_PASS_START	SOC_TPLG_PASS_MANIFEST
#घोषणा SOC_TPLG_PASS_END	SOC_TPLG_PASS_LINK

/* topology context */
काष्ठा soc_tplg अणु
	स्थिर काष्ठा firmware *fw;

	/* runसमय FW parsing */
	स्थिर u8 *pos;		/* पढ़ो postion */
	स्थिर u8 *hdr_pos;	/* header position */
	अचिन्हित पूर्णांक pass;	/* pass number */

	/* component caller */
	काष्ठा device *dev;
	काष्ठा snd_soc_component *comp;
	u32 index;	/* current block index */

	/* venकरोr specअगरic kcontrol operations */
	स्थिर काष्ठा snd_soc_tplg_kcontrol_ops *io_ops;
	पूर्णांक io_ops_count;

	/* venकरोr specअगरic bytes ext handlers, क्रम TLV bytes controls */
	स्थिर काष्ठा snd_soc_tplg_bytes_ext_ops *bytes_ext_ops;
	पूर्णांक bytes_ext_ops_count;

	/* optional fw loading callbacks to component drivers */
	काष्ठा snd_soc_tplg_ops *ops;
पूर्ण;

अटल पूर्णांक soc_tplg_process_headers(काष्ठा soc_tplg *tplg);
अटल व्योम soc_tplg_complete(काष्ठा soc_tplg *tplg);

/* check we करोnt overflow the data क्रम this control chunk */
अटल पूर्णांक soc_tplg_check_elem_count(काष्ठा soc_tplg *tplg, माप_प्रकार elem_size,
	अचिन्हित पूर्णांक count, माप_प्रकार bytes, स्थिर अक्षर *elem_type)
अणु
	स्थिर u8 *end = tplg->pos + elem_size * count;

	अगर (end > tplg->fw->data + tplg->fw->size) अणु
		dev_err(tplg->dev, "ASoC: %s overflow end of data\n",
			elem_type);
		वापस -EINVAL;
	पूर्ण

	/* check there is enough room in chunk क्रम control.
	   extra bytes at the end of control are क्रम venकरोr data here  */
	अगर (elem_size * count > bytes) अणु
		dev_err(tplg->dev,
			"ASoC: %s count %d of size %zu is bigger than chunk %zu\n",
			elem_type, count, elem_size, bytes);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक soc_tplg_is_eof(काष्ठा soc_tplg *tplg)
अणु
	स्थिर u8 *end = tplg->hdr_pos;

	अगर (end >= tplg->fw->data + tplg->fw->size)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ soc_tplg_get_hdr_offset(काष्ठा soc_tplg *tplg)
अणु
	वापस (अचिन्हित दीर्घ)(tplg->hdr_pos - tplg->fw->data);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ soc_tplg_get_offset(काष्ठा soc_tplg *tplg)
अणु
	वापस (अचिन्हित दीर्घ)(tplg->pos - tplg->fw->data);
पूर्ण

/* mapping of Kcontrol types and associated operations. */
अटल स्थिर काष्ठा snd_soc_tplg_kcontrol_ops io_ops[] = अणु
	अणुSND_SOC_TPLG_CTL_VOLSW, snd_soc_get_volsw,
		snd_soc_put_volsw, snd_soc_info_volswपूर्ण,
	अणुSND_SOC_TPLG_CTL_VOLSW_SX, snd_soc_get_volsw_sx,
		snd_soc_put_volsw_sx, शून्यपूर्ण,
	अणुSND_SOC_TPLG_CTL_ENUM, snd_soc_get_क्रमागत_द्विगुन,
		snd_soc_put_क्रमागत_द्विगुन, snd_soc_info_क्रमागत_द्विगुनपूर्ण,
	अणुSND_SOC_TPLG_CTL_ENUM_VALUE, snd_soc_get_क्रमागत_द्विगुन,
		snd_soc_put_क्रमागत_द्विगुन, शून्यपूर्ण,
	अणुSND_SOC_TPLG_CTL_BYTES, snd_soc_bytes_get,
		snd_soc_bytes_put, snd_soc_bytes_infoपूर्ण,
	अणुSND_SOC_TPLG_CTL_RANGE, snd_soc_get_volsw_range,
		snd_soc_put_volsw_range, snd_soc_info_volsw_rangeपूर्ण,
	अणुSND_SOC_TPLG_CTL_VOLSW_XR_SX, snd_soc_get_xr_sx,
		snd_soc_put_xr_sx, snd_soc_info_xr_sxपूर्ण,
	अणुSND_SOC_TPLG_CTL_STROBE, snd_soc_get_strobe,
		snd_soc_put_strobe, शून्यपूर्ण,
	अणुSND_SOC_TPLG_DAPM_CTL_VOLSW, snd_soc_dapm_get_volsw,
		snd_soc_dapm_put_volsw, snd_soc_info_volswपूर्ण,
	अणुSND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE, snd_soc_dapm_get_क्रमागत_द्विगुन,
		snd_soc_dapm_put_क्रमागत_द्विगुन, snd_soc_info_क्रमागत_द्विगुनपूर्ण,
	अणुSND_SOC_TPLG_DAPM_CTL_ENUM_VIRT, snd_soc_dapm_get_क्रमागत_द्विगुन,
		snd_soc_dapm_put_क्रमागत_द्विगुन, शून्यपूर्ण,
	अणुSND_SOC_TPLG_DAPM_CTL_ENUM_VALUE, snd_soc_dapm_get_क्रमागत_द्विगुन,
		snd_soc_dapm_put_क्रमागत_द्विगुन, शून्यपूर्ण,
	अणुSND_SOC_TPLG_DAPM_CTL_PIN, snd_soc_dapm_get_pin_चयन,
		snd_soc_dapm_put_pin_चयन, snd_soc_dapm_info_pin_चयनपूर्ण,
पूर्ण;

काष्ठा soc_tplg_map अणु
	पूर्णांक uid;
	पूर्णांक kid;
पूर्ण;

/* mapping of widget types from UAPI IDs to kernel IDs */
अटल स्थिर काष्ठा soc_tplg_map dapm_map[] = अणु
	अणुSND_SOC_TPLG_DAPM_INPUT, snd_soc_dapm_inputपूर्ण,
	अणुSND_SOC_TPLG_DAPM_OUTPUT, snd_soc_dapm_outputपूर्ण,
	अणुSND_SOC_TPLG_DAPM_MUX, snd_soc_dapm_muxपूर्ण,
	अणुSND_SOC_TPLG_DAPM_MIXER, snd_soc_dapm_mixerपूर्ण,
	अणुSND_SOC_TPLG_DAPM_PGA, snd_soc_dapm_pgaपूर्ण,
	अणुSND_SOC_TPLG_DAPM_OUT_DRV, snd_soc_dapm_out_drvपूर्ण,
	अणुSND_SOC_TPLG_DAPM_ADC, snd_soc_dapm_adcपूर्ण,
	अणुSND_SOC_TPLG_DAPM_DAC, snd_soc_dapm_dacपूर्ण,
	अणुSND_SOC_TPLG_DAPM_SWITCH, snd_soc_dapm_चयनपूर्ण,
	अणुSND_SOC_TPLG_DAPM_PRE, snd_soc_dapm_preपूर्ण,
	अणुSND_SOC_TPLG_DAPM_POST, snd_soc_dapm_postपूर्ण,
	अणुSND_SOC_TPLG_DAPM_AIF_IN, snd_soc_dapm_aअगर_inपूर्ण,
	अणुSND_SOC_TPLG_DAPM_AIF_OUT, snd_soc_dapm_aअगर_outपूर्ण,
	अणुSND_SOC_TPLG_DAPM_DAI_IN, snd_soc_dapm_dai_inपूर्ण,
	अणुSND_SOC_TPLG_DAPM_DAI_OUT, snd_soc_dapm_dai_outपूर्ण,
	अणुSND_SOC_TPLG_DAPM_DAI_LINK, snd_soc_dapm_dai_linkपूर्ण,
	अणुSND_SOC_TPLG_DAPM_BUFFER, snd_soc_dapm_bufferपूर्ण,
	अणुSND_SOC_TPLG_DAPM_SCHEDULER, snd_soc_dapm_schedulerपूर्ण,
	अणुSND_SOC_TPLG_DAPM_EFFECT, snd_soc_dapm_effectपूर्ण,
	अणुSND_SOC_TPLG_DAPM_SIGGEN, snd_soc_dapm_siggenपूर्ण,
	अणुSND_SOC_TPLG_DAPM_SRC, snd_soc_dapm_srcपूर्ण,
	अणुSND_SOC_TPLG_DAPM_ASRC, snd_soc_dapm_asrcपूर्ण,
	अणुSND_SOC_TPLG_DAPM_ENCODER, snd_soc_dapm_encoderपूर्ण,
	अणुSND_SOC_TPLG_DAPM_DECODER, snd_soc_dapm_decoderपूर्ण,
पूर्ण;

अटल पूर्णांक tplc_chan_get_reg(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_channel *chan, पूर्णांक map)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SND_SOC_TPLG_MAX_CHAN; i++) अणु
		अगर (le32_to_cpu(chan[i].id) == map)
			वापस le32_to_cpu(chan[i].reg);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tplc_chan_get_shअगरt(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_channel *chan, पूर्णांक map)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SND_SOC_TPLG_MAX_CHAN; i++) अणु
		अगर (le32_to_cpu(chan[i].id) == map)
			वापस le32_to_cpu(chan[i].shअगरt);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_widget_id(पूर्णांक tplg_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dapm_map); i++) अणु
		अगर (tplg_type == dapm_map[i].uid)
			वापस dapm_map[i].kid;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम soc_bind_err(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_ctl_hdr *hdr, पूर्णांक index)
अणु
	dev_err(tplg->dev,
		"ASoC: invalid control type (g,p,i) %d:%d:%d index %d at 0x%lx\n",
		hdr->ops.get, hdr->ops.put, hdr->ops.info, index,
		soc_tplg_get_offset(tplg));
पूर्ण

अटल अंतरभूत व्योम soc_control_err(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_ctl_hdr *hdr, स्थिर अक्षर *name)
अणु
	dev_err(tplg->dev,
		"ASoC: no complete mixer IO handler for %s type (g,p,i) %d:%d:%d at 0x%lx\n",
		name, hdr->ops.get, hdr->ops.put, hdr->ops.info,
		soc_tplg_get_offset(tplg));
पूर्ण

/* pass venकरोr data to component driver क्रम processing */
अटल पूर्णांक soc_tplg_venकरोr_load(काष्ठा soc_tplg *tplg,
				काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	पूर्णांक ret = 0;

	अगर (tplg->ops && tplg->ops->venकरोr_load)
		ret = tplg->ops->venकरोr_load(tplg->comp, tplg->index, hdr);
	अन्यथा अणु
		dev_err(tplg->dev, "ASoC: no vendor load callback for ID %d\n",
			hdr->venकरोr_type);
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		dev_err(tplg->dev,
			"ASoC: vendor load failed at hdr offset %ld/0x%lx for type %d:%d\n",
			soc_tplg_get_hdr_offset(tplg),
			soc_tplg_get_hdr_offset(tplg),
			hdr->type, hdr->venकरोr_type);
	वापस ret;
पूर्ण

/* optionally pass new dynamic widget to component driver. This is मुख्यly क्रम
 * बाह्यal widमाला_लो where we can assign निजी data/ops */
अटल पूर्णांक soc_tplg_widget_load(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_soc_tplg_dapm_widget *tplg_w)
अणु
	अगर (tplg->ops && tplg->ops->widget_load)
		वापस tplg->ops->widget_load(tplg->comp, tplg->index, w,
			tplg_w);

	वापस 0;
पूर्ण

/* optionally pass new dynamic widget to component driver. This is मुख्यly क्रम
 * बाह्यal widमाला_लो where we can assign निजी data/ops */
अटल पूर्णांक soc_tplg_widget_पढ़ोy(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_dapm_widget *w, काष्ठा snd_soc_tplg_dapm_widget *tplg_w)
अणु
	अगर (tplg->ops && tplg->ops->widget_पढ़ोy)
		वापस tplg->ops->widget_पढ़ोy(tplg->comp, tplg->index, w,
			tplg_w);

	वापस 0;
पूर्ण

/* pass DAI configurations to component driver क्रम extra initialization */
अटल पूर्णांक soc_tplg_dai_load(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_dai_driver *dai_drv,
	काष्ठा snd_soc_tplg_pcm *pcm, काष्ठा snd_soc_dai *dai)
अणु
	अगर (tplg->ops && tplg->ops->dai_load)
		वापस tplg->ops->dai_load(tplg->comp, tplg->index, dai_drv,
			pcm, dai);

	वापस 0;
पूर्ण

/* pass link configurations to component driver क्रम extra initialization */
अटल पूर्णांक soc_tplg_dai_link_load(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_dai_link *link, काष्ठा snd_soc_tplg_link_config *cfg)
अणु
	अगर (tplg->ops && tplg->ops->link_load)
		वापस tplg->ops->link_load(tplg->comp, tplg->index, link, cfg);

	वापस 0;
पूर्ण

/* tell the component driver that all firmware has been loaded in this request */
अटल व्योम soc_tplg_complete(काष्ठा soc_tplg *tplg)
अणु
	अगर (tplg->ops && tplg->ops->complete)
		tplg->ops->complete(tplg->comp);
पूर्ण

/* add a dynamic kcontrol */
अटल पूर्णांक soc_tplg_add_dcontrol(काष्ठा snd_card *card, काष्ठा device *dev,
	स्थिर काष्ठा snd_kcontrol_new *control_new, स्थिर अक्षर *prefix,
	व्योम *data, काष्ठा snd_kcontrol **kcontrol)
अणु
	पूर्णांक err;

	*kcontrol = snd_soc_cnew(control_new, data, control_new->name, prefix);
	अगर (*kcontrol == शून्य) अणु
		dev_err(dev, "ASoC: Failed to create new kcontrol %s\n",
		control_new->name);
		वापस -ENOMEM;
	पूर्ण

	err = snd_ctl_add(card, *kcontrol);
	अगर (err < 0) अणु
		dev_err(dev, "ASoC: Failed to add %s: %d\n",
			control_new->name, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* add a dynamic kcontrol क्रम component driver */
अटल पूर्णांक soc_tplg_add_kcontrol(काष्ठा soc_tplg *tplg,
	काष्ठा snd_kcontrol_new *k, काष्ठा snd_kcontrol **kcontrol)
अणु
	काष्ठा snd_soc_component *comp = tplg->comp;

	वापस soc_tplg_add_dcontrol(comp->card->snd_card,
				comp->dev, k, comp->name_prefix, comp, kcontrol);
पूर्ण

/* हटाओ a mixer kcontrol */
अटल व्योम हटाओ_mixer(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_करोbj *करोbj, पूर्णांक pass)
अणु
	काष्ठा snd_card *card = comp->card->snd_card;

	अगर (pass != SOC_TPLG_PASS_MIXER)
		वापस;

	अगर (करोbj->ops && करोbj->ops->control_unload)
		करोbj->ops->control_unload(comp, करोbj);

	snd_ctl_हटाओ(card, करोbj->control.kcontrol);
	list_del(&करोbj->list);
पूर्ण

/* हटाओ an क्रमागत kcontrol */
अटल व्योम हटाओ_क्रमागत(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_करोbj *करोbj, पूर्णांक pass)
अणु
	काष्ठा snd_card *card = comp->card->snd_card;

	अगर (pass != SOC_TPLG_PASS_MIXER)
		वापस;

	अगर (करोbj->ops && करोbj->ops->control_unload)
		करोbj->ops->control_unload(comp, करोbj);

	snd_ctl_हटाओ(card, करोbj->control.kcontrol);
	list_del(&करोbj->list);
पूर्ण

/* हटाओ a byte kcontrol */
अटल व्योम हटाओ_bytes(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_करोbj *करोbj, पूर्णांक pass)
अणु
	काष्ठा snd_card *card = comp->card->snd_card;

	अगर (pass != SOC_TPLG_PASS_MIXER)
		वापस;

	अगर (करोbj->ops && करोbj->ops->control_unload)
		करोbj->ops->control_unload(comp, करोbj);

	snd_ctl_हटाओ(card, करोbj->control.kcontrol);
	list_del(&करोbj->list);
पूर्ण

/* हटाओ a route */
अटल व्योम हटाओ_route(काष्ठा snd_soc_component *comp,
			 काष्ठा snd_soc_करोbj *करोbj, पूर्णांक pass)
अणु
	अगर (pass != SOC_TPLG_PASS_GRAPH)
		वापस;

	अगर (करोbj->ops && करोbj->ops->dapm_route_unload)
		करोbj->ops->dapm_route_unload(comp, करोbj);

	list_del(&करोbj->list);
पूर्ण

/* हटाओ a widget and it's kcontrols - routes must be हटाओd first */
अटल व्योम हटाओ_widget(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_करोbj *करोbj, पूर्णांक pass)
अणु
	काष्ठा snd_card *card = comp->card->snd_card;
	काष्ठा snd_soc_dapm_widget *w =
		container_of(करोbj, काष्ठा snd_soc_dapm_widget, करोbj);
	पूर्णांक i;

	अगर (pass != SOC_TPLG_PASS_WIDGET)
		वापस;

	अगर (करोbj->ops && करोbj->ops->widget_unload)
		करोbj->ops->widget_unload(comp, करोbj);

	अगर (!w->kcontrols)
		जाओ मुक्त_news;

	क्रम (i = 0; w->kcontrols && i < w->num_kcontrols; i++)
		snd_ctl_हटाओ(card, w->kcontrols[i]);

मुक्त_news:

	list_del(&करोbj->list);

	/* widget w is मुक्तd by soc-dapm.c */
पूर्ण

/* हटाओ DAI configurations */
अटल व्योम हटाओ_dai(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_करोbj *करोbj, पूर्णांक pass)
अणु
	काष्ठा snd_soc_dai_driver *dai_drv =
		container_of(करोbj, काष्ठा snd_soc_dai_driver, करोbj);
	काष्ठा snd_soc_dai *dai, *_dai;

	अगर (pass != SOC_TPLG_PASS_PCM_DAI)
		वापस;

	अगर (करोbj->ops && करोbj->ops->dai_unload)
		करोbj->ops->dai_unload(comp, करोbj);

	क्रम_each_component_dais_safe(comp, dai, _dai)
		अगर (dai->driver == dai_drv)
			snd_soc_unरेजिस्टर_dai(dai);

	list_del(&करोbj->list);
पूर्ण

/* हटाओ link configurations */
अटल व्योम हटाओ_link(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_करोbj *करोbj, पूर्णांक pass)
अणु
	काष्ठा snd_soc_dai_link *link =
		container_of(करोbj, काष्ठा snd_soc_dai_link, करोbj);

	अगर (pass != SOC_TPLG_PASS_PCM_DAI)
		वापस;

	अगर (करोbj->ops && करोbj->ops->link_unload)
		करोbj->ops->link_unload(comp, करोbj);

	list_del(&करोbj->list);
	snd_soc_हटाओ_pcm_runसमय(comp->card,
			snd_soc_get_pcm_runसमय(comp->card, link));
पूर्ण

/* unload dai link */
अटल व्योम हटाओ_backend_link(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_करोbj *करोbj, पूर्णांक pass)
अणु
	अगर (pass != SOC_TPLG_PASS_LINK)
		वापस;

	अगर (करोbj->ops && करोbj->ops->link_unload)
		करोbj->ops->link_unload(comp, करोbj);

	/*
	 * We करोn't मुक्त the link here as what हटाओ_link() करो since BE
	 * links are not allocated by topology.
	 * We however need to reset the करोbj type to its initial values
	 */
	करोbj->type = SND_SOC_DOBJ_NONE;
	list_del(&करोbj->list);
पूर्ण

/* bind a kcontrol to it's IO handlers */
अटल पूर्णांक soc_tplg_kcontrol_bind_io(काष्ठा snd_soc_tplg_ctl_hdr *hdr,
	काष्ठा snd_kcontrol_new *k,
	स्थिर काष्ठा soc_tplg *tplg)
अणु
	स्थिर काष्ठा snd_soc_tplg_kcontrol_ops *ops;
	स्थिर काष्ठा snd_soc_tplg_bytes_ext_ops *ext_ops;
	पूर्णांक num_ops, i;

	अगर (le32_to_cpu(hdr->ops.info) == SND_SOC_TPLG_CTL_BYTES
		&& k->अगरace & SNDRV_CTL_ELEM_IFACE_MIXER
		&& k->access & SNDRV_CTL_ELEM_ACCESS_TLV_READWRITE
		&& k->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) अणु
		काष्ठा soc_bytes_ext *sbe;
		काष्ठा snd_soc_tplg_bytes_control *be;

		sbe = (काष्ठा soc_bytes_ext *)k->निजी_value;
		be = container_of(hdr, काष्ठा snd_soc_tplg_bytes_control, hdr);

		/* TLV bytes controls need standard kcontrol info handler,
		 * TLV callback and extended put/get handlers.
		 */
		k->info = snd_soc_bytes_info_ext;
		k->tlv.c = snd_soc_bytes_tlv_callback;

		/*
		 * When a topology-based implementation abuses the
		 * control पूर्णांकerface and uses bytes_ext controls of
		 * more than 512 bytes, we need to disable the size
		 * checks, otherwise accesses to such controls will
		 * वापस an -EINVAL error and prevent the card from
		 * being configured.
		 */
		अगर (IS_ENABLED(CONFIG_SND_CTL_VALIDATION) && sbe->max > 512)
			k->access |= SNDRV_CTL_ELEM_ACCESS_SKIP_CHECK;

		ext_ops = tplg->bytes_ext_ops;
		num_ops = tplg->bytes_ext_ops_count;
		क्रम (i = 0; i < num_ops; i++) अणु
			अगर (!sbe->put &&
			    ext_ops[i].id == le32_to_cpu(be->ext_ops.put))
				sbe->put = ext_ops[i].put;
			अगर (!sbe->get &&
			    ext_ops[i].id == le32_to_cpu(be->ext_ops.get))
				sbe->get = ext_ops[i].get;
		पूर्ण

		अगर ((k->access & SNDRV_CTL_ELEM_ACCESS_TLV_READ) && !sbe->get)
			वापस -EINVAL;
		अगर ((k->access & SNDRV_CTL_ELEM_ACCESS_TLV_WRITE) && !sbe->put)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	/* try and map venकरोr specअगरic kcontrol handlers first */
	ops = tplg->io_ops;
	num_ops = tplg->io_ops_count;
	क्रम (i = 0; i < num_ops; i++) अणु

		अगर (k->put == शून्य && ops[i].id == le32_to_cpu(hdr->ops.put))
			k->put = ops[i].put;
		अगर (k->get == शून्य && ops[i].id == le32_to_cpu(hdr->ops.get))
			k->get = ops[i].get;
		अगर (k->info == शून्य && ops[i].id == le32_to_cpu(hdr->ops.info))
			k->info = ops[i].info;
	पूर्ण

	/* venकरोr specअगरic handlers found ? */
	अगर (k->put && k->get && k->info)
		वापस 0;

	/* none found so try standard kcontrol handlers */
	ops = io_ops;
	num_ops = ARRAY_SIZE(io_ops);
	क्रम (i = 0; i < num_ops; i++) अणु

		अगर (k->put == शून्य && ops[i].id == le32_to_cpu(hdr->ops.put))
			k->put = ops[i].put;
		अगर (k->get == शून्य && ops[i].id == le32_to_cpu(hdr->ops.get))
			k->get = ops[i].get;
		अगर (k->info == शून्य && ops[i].id == le32_to_cpu(hdr->ops.info))
			k->info = ops[i].info;
	पूर्ण

	/* standard handlers found ? */
	अगर (k->put && k->get && k->info)
		वापस 0;

	/* nothing to bind */
	वापस -EINVAL;
पूर्ण

/* bind a widमाला_लो to it's evnt handlers */
पूर्णांक snd_soc_tplg_widget_bind_event(काष्ठा snd_soc_dapm_widget *w,
		स्थिर काष्ठा snd_soc_tplg_widget_events *events,
		पूर्णांक num_events, u16 event_type)
अणु
	पूर्णांक i;

	w->event = शून्य;

	क्रम (i = 0; i < num_events; i++) अणु
		अगर (event_type == events[i].type) अणु

			/* found - so assign event */
			w->event = events[i].event_handler;
			वापस 0;
		पूर्ण
	पूर्ण

	/* not found */
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_tplg_widget_bind_event);

/* optionally pass new dynamic kcontrol to component driver. */
अटल पूर्णांक soc_tplg_init_kcontrol(काष्ठा soc_tplg *tplg,
	काष्ठा snd_kcontrol_new *k, काष्ठा snd_soc_tplg_ctl_hdr *hdr)
अणु
	अगर (tplg->ops && tplg->ops->control_load)
		वापस tplg->ops->control_load(tplg->comp, tplg->index, k,
			hdr);

	वापस 0;
पूर्ण


अटल पूर्णांक soc_tplg_create_tlv_db_scale(काष्ठा soc_tplg *tplg,
	काष्ठा snd_kcontrol_new *kc, काष्ठा snd_soc_tplg_tlv_dbscale *scale)
अणु
	अचिन्हित पूर्णांक item_len = 2 * माप(अचिन्हित पूर्णांक);
	अचिन्हित पूर्णांक *p;

	p = devm_kzalloc(tplg->dev, item_len + 2 * माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p[0] = SNDRV_CTL_TLVT_DB_SCALE;
	p[1] = item_len;
	p[2] = le32_to_cpu(scale->min);
	p[3] = (le32_to_cpu(scale->step) & TLV_DB_SCALE_MASK)
		| (le32_to_cpu(scale->mute) ? TLV_DB_SCALE_MUTE : 0);

	kc->tlv.p = (व्योम *)p;
	वापस 0;
पूर्ण

अटल पूर्णांक soc_tplg_create_tlv(काष्ठा soc_tplg *tplg,
	काष्ठा snd_kcontrol_new *kc, काष्ठा snd_soc_tplg_ctl_hdr *tc)
अणु
	काष्ठा snd_soc_tplg_ctl_tlv *tplg_tlv;
	u32 access = le32_to_cpu(tc->access);

	अगर (!(access & SNDRV_CTL_ELEM_ACCESS_TLV_READWRITE))
		वापस 0;

	अगर (!(access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK)) अणु
		tplg_tlv = &tc->tlv;
		चयन (le32_to_cpu(tplg_tlv->type)) अणु
		हाल SNDRV_CTL_TLVT_DB_SCALE:
			वापस soc_tplg_create_tlv_db_scale(tplg, kc,
					&tplg_tlv->scale);

		/* TODO: add support क्रम other TLV types */
		शेष:
			dev_dbg(tplg->dev, "Unsupported TLV type %d\n",
					tplg_tlv->type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक soc_tplg_dbytes_create(काष्ठा soc_tplg *tplg, अचिन्हित पूर्णांक count,
	माप_प्रकार size)
अणु
	काष्ठा snd_soc_tplg_bytes_control *be;
	काष्ठा soc_bytes_ext *sbe;
	काष्ठा snd_kcontrol_new kc;
	पूर्णांक i;
	पूर्णांक err = 0;

	अगर (soc_tplg_check_elem_count(tplg,
		माप(काष्ठा snd_soc_tplg_bytes_control), count,
			size, "mixer bytes")) अणु
		dev_err(tplg->dev, "ASoC: Invalid count %d for byte control\n",
			count);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		be = (काष्ठा snd_soc_tplg_bytes_control *)tplg->pos;

		/* validate kcontrol */
		अगर (strnlen(be->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			वापस -EINVAL;

		sbe = devm_kzalloc(tplg->dev, माप(*sbe), GFP_KERNEL);
		अगर (sbe == शून्य)
			वापस -ENOMEM;

		tplg->pos += (माप(काष्ठा snd_soc_tplg_bytes_control) +
			      le32_to_cpu(be->priv.size));

		dev_dbg(tplg->dev,
			"ASoC: adding bytes kcontrol %s with access 0x%x\n",
			be->hdr.name, be->hdr.access);

		स_रखो(&kc, 0, माप(kc));
		kc.name = be->hdr.name;
		kc.निजी_value = (दीर्घ)sbe;
		kc.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc.access = le32_to_cpu(be->hdr.access);

		sbe->max = le32_to_cpu(be->max);
		sbe->करोbj.type = SND_SOC_DOBJ_BYTES;
		sbe->करोbj.ops = tplg->ops;
		INIT_LIST_HEAD(&sbe->करोbj.list);

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&be->hdr, &kc, tplg);
		अगर (err) अणु
			soc_control_err(tplg, &be->hdr, be->hdr.name);
			अवरोध;
		पूर्ण

		/* pass control to driver क्रम optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc,
			(काष्ठा snd_soc_tplg_ctl_hdr *)be);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				be->hdr.name);
			अवरोध;
		पूर्ण

		/* रेजिस्टर control here */
		err = soc_tplg_add_kcontrol(tplg, &kc,
			&sbe->करोbj.control.kcontrol);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to add %s\n",
				be->hdr.name);
			अवरोध;
		पूर्ण

		list_add(&sbe->करोbj.list, &tplg->comp->करोbj_list);
	पूर्ण
	वापस err;

पूर्ण

अटल पूर्णांक soc_tplg_dmixer_create(काष्ठा soc_tplg *tplg, अचिन्हित पूर्णांक count,
	माप_प्रकार size)
अणु
	काष्ठा snd_soc_tplg_mixer_control *mc;
	काष्ठा soc_mixer_control *sm;
	काष्ठा snd_kcontrol_new kc;
	पूर्णांक i;
	पूर्णांक err = 0;

	अगर (soc_tplg_check_elem_count(tplg,
		माप(काष्ठा snd_soc_tplg_mixer_control),
		count, size, "mixers")) अणु

		dev_err(tplg->dev, "ASoC: invalid count %d for controls\n",
			count);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		mc = (काष्ठा snd_soc_tplg_mixer_control *)tplg->pos;

		/* validate kcontrol */
		अगर (strnlen(mc->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			वापस -EINVAL;

		sm = devm_kzalloc(tplg->dev, माप(*sm), GFP_KERNEL);
		अगर (sm == शून्य)
			वापस -ENOMEM;
		tplg->pos += (माप(काष्ठा snd_soc_tplg_mixer_control) +
			      le32_to_cpu(mc->priv.size));

		dev_dbg(tplg->dev,
			"ASoC: adding mixer kcontrol %s with access 0x%x\n",
			mc->hdr.name, mc->hdr.access);

		स_रखो(&kc, 0, माप(kc));
		kc.name = mc->hdr.name;
		kc.निजी_value = (दीर्घ)sm;
		kc.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc.access = le32_to_cpu(mc->hdr.access);

		/* we only support FL/FR channel mapping aपंचांग */
		sm->reg = tplc_chan_get_reg(tplg, mc->channel,
			SNDRV_CHMAP_FL);
		sm->rreg = tplc_chan_get_reg(tplg, mc->channel,
			SNDRV_CHMAP_FR);
		sm->shअगरt = tplc_chan_get_shअगरt(tplg, mc->channel,
			SNDRV_CHMAP_FL);
		sm->rshअगरt = tplc_chan_get_shअगरt(tplg, mc->channel,
			SNDRV_CHMAP_FR);

		sm->max = le32_to_cpu(mc->max);
		sm->min = le32_to_cpu(mc->min);
		sm->invert = le32_to_cpu(mc->invert);
		sm->platक्रमm_max = le32_to_cpu(mc->platक्रमm_max);
		sm->करोbj.index = tplg->index;
		sm->करोbj.ops = tplg->ops;
		sm->करोbj.type = SND_SOC_DOBJ_MIXER;
		INIT_LIST_HEAD(&sm->करोbj.list);

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&mc->hdr, &kc, tplg);
		अगर (err) अणु
			soc_control_err(tplg, &mc->hdr, mc->hdr.name);
			अवरोध;
		पूर्ण

		/* create any TLV data */
		err = soc_tplg_create_tlv(tplg, &kc, &mc->hdr);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to create TLV %s\n",
				mc->hdr.name);
			अवरोध;
		पूर्ण

		/* pass control to driver क्रम optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc,
			(काष्ठा snd_soc_tplg_ctl_hdr *) mc);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				mc->hdr.name);
			अवरोध;
		पूर्ण

		/* रेजिस्टर control here */
		err = soc_tplg_add_kcontrol(tplg, &kc,
			&sm->करोbj.control.kcontrol);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to add %s\n",
				mc->hdr.name);
			अवरोध;
		पूर्ण

		list_add(&sm->करोbj.list, &tplg->comp->करोbj_list);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक soc_tplg_dक्रमागत_create_texts(काष्ठा soc_tplg *tplg, काष्ठा soc_क्रमागत *se,
				       काष्ठा snd_soc_tplg_क्रमागत_control *ec)
अणु
	पूर्णांक i, ret;

	अगर (le32_to_cpu(ec->items) > ARRAY_SIZE(ec->texts))
		वापस -EINVAL;

	se->करोbj.control.dtexts =
		devm_kसुस्मृति(tplg->dev, le32_to_cpu(ec->items), माप(अक्षर *), GFP_KERNEL);
	अगर (se->करोbj.control.dtexts == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < le32_to_cpu(ec->items); i++) अणु

		अगर (strnlen(ec->texts[i], SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		se->करोbj.control.dtexts[i] = devm_kstrdup(tplg->dev, ec->texts[i], GFP_KERNEL);
		अगर (!se->करोbj.control.dtexts[i]) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	se->items = le32_to_cpu(ec->items);
	se->texts = (स्थिर अक्षर * स्थिर *)se->करोbj.control.dtexts;
	वापस 0;

err:
	वापस ret;
पूर्ण

अटल पूर्णांक soc_tplg_dक्रमागत_create_values(काष्ठा soc_tplg *tplg, काष्ठा soc_क्रमागत *se,
					काष्ठा snd_soc_tplg_क्रमागत_control *ec)
अणु
	पूर्णांक i;

	/*
	 * Following "if" checks अगर we have at most SND_SOC_TPLG_NUM_TEXTS
	 * values instead of using ARRAY_SIZE(ec->values) due to the fact that
	 * it is oversized क्रम its purpose. Additionally it is करोne so because
	 * it is defined in UAPI header where it can't be easily changed.
	 */
	अगर (le32_to_cpu(ec->items) > SND_SOC_TPLG_NUM_TEXTS)
		वापस -EINVAL;

	se->करोbj.control.dvalues = devm_kसुस्मृति(tplg->dev, le32_to_cpu(ec->items),
					   माप(*se->करोbj.control.dvalues),
					   GFP_KERNEL);
	अगर (!se->करोbj.control.dvalues)
		वापस -ENOMEM;

	/* convert from little-endian */
	क्रम (i = 0; i < le32_to_cpu(ec->items); i++) अणु
		se->करोbj.control.dvalues[i] = le32_to_cpu(ec->values[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक soc_tplg_dक्रमागत_create(काष्ठा soc_tplg *tplg, अचिन्हित पूर्णांक count,
	माप_प्रकार size)
अणु
	काष्ठा snd_soc_tplg_क्रमागत_control *ec;
	काष्ठा soc_क्रमागत *se;
	काष्ठा snd_kcontrol_new kc;
	पूर्णांक i;
	पूर्णांक err = 0;

	अगर (soc_tplg_check_elem_count(tplg,
		माप(काष्ठा snd_soc_tplg_क्रमागत_control),
		count, size, "enums")) अणु

		dev_err(tplg->dev, "ASoC: invalid count %d for enum controls\n",
			count);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		ec = (काष्ठा snd_soc_tplg_क्रमागत_control *)tplg->pos;

		/* validate kcontrol */
		अगर (strnlen(ec->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			वापस -EINVAL;

		se = devm_kzalloc(tplg->dev, (माप(*se)), GFP_KERNEL);
		अगर (se == शून्य)
			वापस -ENOMEM;

		tplg->pos += (माप(काष्ठा snd_soc_tplg_क्रमागत_control) +
			      le32_to_cpu(ec->priv.size));

		dev_dbg(tplg->dev, "ASoC: adding enum kcontrol %s size %d\n",
			ec->hdr.name, ec->items);

		स_रखो(&kc, 0, माप(kc));
		kc.name = ec->hdr.name;
		kc.निजी_value = (दीर्घ)se;
		kc.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc.access = le32_to_cpu(ec->hdr.access);

		se->reg = tplc_chan_get_reg(tplg, ec->channel, SNDRV_CHMAP_FL);
		se->shअगरt_l = tplc_chan_get_shअगरt(tplg, ec->channel,
			SNDRV_CHMAP_FL);
		se->shअगरt_r = tplc_chan_get_shअगरt(tplg, ec->channel,
			SNDRV_CHMAP_FL);

		se->mask = le32_to_cpu(ec->mask);
		se->करोbj.index = tplg->index;
		se->करोbj.type = SND_SOC_DOBJ_ENUM;
		se->करोbj.ops = tplg->ops;
		INIT_LIST_HEAD(&se->करोbj.list);

		चयन (le32_to_cpu(ec->hdr.ops.info)) अणु
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
		हाल SND_SOC_TPLG_CTL_ENUM_VALUE:
			err = soc_tplg_dक्रमागत_create_values(tplg, se, ec);
			अगर (err < 0) अणु
				dev_err(tplg->dev,
					"ASoC: could not create values for %s\n",
					ec->hdr.name);
				जाओ err_dक्रमागत;
			पूर्ण
			fallthrough;
		हाल SND_SOC_TPLG_CTL_ENUM:
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
			err = soc_tplg_dक्रमागत_create_texts(tplg, se, ec);
			अगर (err < 0) अणु
				dev_err(tplg->dev,
					"ASoC: could not create texts for %s\n",
					ec->hdr.name);
				जाओ err_dक्रमागत;
			पूर्ण
			अवरोध;
		शेष:
			err = -EINVAL;
			dev_err(tplg->dev,
				"ASoC: invalid enum control type %d for %s\n",
				ec->hdr.ops.info, ec->hdr.name);
			जाओ err_dक्रमागत;
		पूर्ण

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&ec->hdr, &kc, tplg);
		अगर (err) अणु
			soc_control_err(tplg, &ec->hdr, ec->hdr.name);
			जाओ err_dक्रमागत;
		पूर्ण

		/* pass control to driver क्रम optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc,
			(काष्ठा snd_soc_tplg_ctl_hdr *) ec);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				ec->hdr.name);
			जाओ err_dक्रमागत;
		पूर्ण

		/* रेजिस्टर control here */
		err = soc_tplg_add_kcontrol(tplg,
					    &kc, &se->करोbj.control.kcontrol);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: could not add kcontrol %s\n",
				ec->hdr.name);
			जाओ err_dक्रमागत;
		पूर्ण

		list_add(&se->करोbj.list, &tplg->comp->करोbj_list);
	पूर्ण
	वापस 0;

err_dक्रमागत:
	वापस err;
पूर्ण

अटल पूर्णांक soc_tplg_kcontrol_elems_load(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	काष्ठा snd_soc_tplg_ctl_hdr *control_hdr;
	पूर्णांक ret;
	पूर्णांक i;

	dev_dbg(tplg->dev, "ASoC: adding %d kcontrols at 0x%lx\n", hdr->count,
		soc_tplg_get_offset(tplg));

	क्रम (i = 0; i < le32_to_cpu(hdr->count); i++) अणु

		control_hdr = (काष्ठा snd_soc_tplg_ctl_hdr *)tplg->pos;

		अगर (le32_to_cpu(control_hdr->size) != माप(*control_hdr)) अणु
			dev_err(tplg->dev, "ASoC: invalid control size\n");
			वापस -EINVAL;
		पूर्ण

		चयन (le32_to_cpu(control_hdr->ops.info)) अणु
		हाल SND_SOC_TPLG_CTL_VOLSW:
		हाल SND_SOC_TPLG_CTL_STROBE:
		हाल SND_SOC_TPLG_CTL_VOLSW_SX:
		हाल SND_SOC_TPLG_CTL_VOLSW_XR_SX:
		हाल SND_SOC_TPLG_CTL_RANGE:
		हाल SND_SOC_TPLG_DAPM_CTL_VOLSW:
		हाल SND_SOC_TPLG_DAPM_CTL_PIN:
			ret = soc_tplg_dmixer_create(tplg, 1,
					le32_to_cpu(hdr->payload_size));
			अवरोध;
		हाल SND_SOC_TPLG_CTL_ENUM:
		हाल SND_SOC_TPLG_CTL_ENUM_VALUE:
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
			ret = soc_tplg_dक्रमागत_create(tplg, 1,
					le32_to_cpu(hdr->payload_size));
			अवरोध;
		हाल SND_SOC_TPLG_CTL_BYTES:
			ret = soc_tplg_dbytes_create(tplg, 1,
					le32_to_cpu(hdr->payload_size));
			अवरोध;
		शेष:
			soc_bind_err(tplg, control_hdr, i);
			वापस -EINVAL;
		पूर्ण
		अगर (ret < 0) अणु
			dev_err(tplg->dev, "ASoC: invalid control\n");
			वापस ret;
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

/* optionally pass new dynamic kcontrol to component driver. */
अटल पूर्णांक soc_tplg_add_route(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_dapm_route *route)
अणु
	अगर (tplg->ops && tplg->ops->dapm_route_load)
		वापस tplg->ops->dapm_route_load(tplg->comp, tplg->index,
			route);

	वापस 0;
पूर्ण

अटल पूर्णांक soc_tplg_dapm_graph_elems_load(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &tplg->comp->dapm;
	काष्ठा snd_soc_tplg_dapm_graph_elem *elem;
	काष्ठा snd_soc_dapm_route **routes;
	पूर्णांक count, i;
	पूर्णांक ret = 0;

	count = le32_to_cpu(hdr->count);

	अगर (soc_tplg_check_elem_count(tplg,
		माप(काष्ठा snd_soc_tplg_dapm_graph_elem),
		count, le32_to_cpu(hdr->payload_size), "graph")) अणु

		dev_err(tplg->dev, "ASoC: invalid count %d for DAPM routes\n",
			count);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(tplg->dev, "ASoC: adding %d DAPM routes for index %d\n", count,
		hdr->index);

	/* allocate memory क्रम poपूर्णांकer to array of dapm routes */
	routes = kसुस्मृति(count, माप(काष्ठा snd_soc_dapm_route *),
			 GFP_KERNEL);
	अगर (!routes)
		वापस -ENOMEM;

	/*
	 * allocate memory क्रम each dapm route in the array.
	 * This needs to be करोne inभागidually so that
	 * each route can be मुक्तd when it is हटाओd in हटाओ_route().
	 */
	क्रम (i = 0; i < count; i++) अणु
		routes[i] = devm_kzalloc(tplg->dev, माप(*routes[i]), GFP_KERNEL);
		अगर (!routes[i])
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		elem = (काष्ठा snd_soc_tplg_dapm_graph_elem *)tplg->pos;
		tplg->pos += माप(काष्ठा snd_soc_tplg_dapm_graph_elem);

		/* validate routes */
		अगर (strnlen(elem->source, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			    SNDRV_CTL_ELEM_ID_NAME_MAXLEN) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (strnlen(elem->sink, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			    SNDRV_CTL_ELEM_ID_NAME_MAXLEN) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (strnlen(elem->control, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			    SNDRV_CTL_ELEM_ID_NAME_MAXLEN) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		routes[i]->source = elem->source;
		routes[i]->sink = elem->sink;

		/* set to शून्य aपंचांग क्रम tplg users */
		routes[i]->connected = शून्य;
		अगर (strnlen(elem->control, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) == 0)
			routes[i]->control = शून्य;
		अन्यथा
			routes[i]->control = elem->control;

		/* add route करोbj to करोbj_list */
		routes[i]->करोbj.type = SND_SOC_DOBJ_GRAPH;
		routes[i]->करोbj.ops = tplg->ops;
		routes[i]->करोbj.index = tplg->index;
		list_add(&routes[i]->करोbj.list, &tplg->comp->करोbj_list);

		ret = soc_tplg_add_route(tplg, routes[i]);
		अगर (ret < 0) अणु
			dev_err(tplg->dev, "ASoC: topology: add_route failed: %d\n", ret);
			/*
			 * this route was added to the list, it will
			 * be मुक्तd in हटाओ_route() so increment the
			 * counter to skip it in the error handling
			 * below.
			 */
			i++;
			अवरोध;
		पूर्ण

		/* add route, but keep going अगर some fail */
		snd_soc_dapm_add_routes(dapm, routes[i], 1);
	पूर्ण

	/*
	 * मुक्त poपूर्णांकer to array of dapm routes as this is no दीर्घer needed.
	 * The memory allocated क्रम each dapm route will be मुक्तd
	 * when it is हटाओd in हटाओ_route().
	 */
	kमुक्त(routes);

	वापस ret;
पूर्ण

अटल काष्ठा snd_kcontrol_new *soc_tplg_dapm_widget_dmixer_create(
	काष्ठा soc_tplg *tplg, पूर्णांक num_kcontrols)
अणु
	काष्ठा snd_kcontrol_new *kc;
	काष्ठा soc_mixer_control *sm;
	काष्ठा snd_soc_tplg_mixer_control *mc;
	पूर्णांक i, err;

	kc = devm_kसुस्मृति(tplg->dev, num_kcontrols, माप(*kc), GFP_KERNEL);
	अगर (kc == शून्य)
		वापस शून्य;

	क्रम (i = 0; i < num_kcontrols; i++) अणु
		mc = (काष्ठा snd_soc_tplg_mixer_control *)tplg->pos;

		/* validate kcontrol */
		अगर (strnlen(mc->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			जाओ err_sm;

		sm = devm_kzalloc(tplg->dev, माप(*sm), GFP_KERNEL);
		अगर (sm == शून्य)
			जाओ err_sm;

		tplg->pos += (माप(काष्ठा snd_soc_tplg_mixer_control) +
			      le32_to_cpu(mc->priv.size));

		dev_dbg(tplg->dev, " adding DAPM widget mixer control %s at %d\n",
			mc->hdr.name, i);

		kc[i].निजी_value = (दीर्घ)sm;
		kc[i].name = devm_kstrdup(tplg->dev, mc->hdr.name, GFP_KERNEL);
		अगर (kc[i].name == शून्य)
			जाओ err_sm;
		kc[i].अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc[i].access = le32_to_cpu(mc->hdr.access);

		/* we only support FL/FR channel mapping aपंचांग */
		sm->reg = tplc_chan_get_reg(tplg, mc->channel,
			SNDRV_CHMAP_FL);
		sm->rreg = tplc_chan_get_reg(tplg, mc->channel,
			SNDRV_CHMAP_FR);
		sm->shअगरt = tplc_chan_get_shअगरt(tplg, mc->channel,
			SNDRV_CHMAP_FL);
		sm->rshअगरt = tplc_chan_get_shअगरt(tplg, mc->channel,
			SNDRV_CHMAP_FR);

		sm->max = le32_to_cpu(mc->max);
		sm->min = le32_to_cpu(mc->min);
		sm->invert = le32_to_cpu(mc->invert);
		sm->platक्रमm_max = le32_to_cpu(mc->platक्रमm_max);
		sm->करोbj.index = tplg->index;
		INIT_LIST_HEAD(&sm->करोbj.list);

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&mc->hdr, &kc[i], tplg);
		अगर (err) अणु
			soc_control_err(tplg, &mc->hdr, mc->hdr.name);
			जाओ err_sm;
		पूर्ण

		/* create any TLV data */
		err = soc_tplg_create_tlv(tplg, &kc[i], &mc->hdr);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to create TLV %s\n",
				mc->hdr.name);
			जाओ err_sm;
		पूर्ण

		/* pass control to driver क्रम optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc[i],
			(काष्ठा snd_soc_tplg_ctl_hdr *)mc);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				mc->hdr.name);
			जाओ err_sm;
		पूर्ण
	पूर्ण
	वापस kc;

err_sm:
	वापस शून्य;
पूर्ण

अटल काष्ठा snd_kcontrol_new *soc_tplg_dapm_widget_dक्रमागत_create(
	काष्ठा soc_tplg *tplg, पूर्णांक num_kcontrols)
अणु
	काष्ठा snd_kcontrol_new *kc;
	काष्ठा snd_soc_tplg_क्रमागत_control *ec;
	काष्ठा soc_क्रमागत *se;
	पूर्णांक i, err;

	kc = devm_kसुस्मृति(tplg->dev, num_kcontrols, माप(*kc), GFP_KERNEL);
	अगर (kc == शून्य)
		वापस शून्य;

	क्रम (i = 0; i < num_kcontrols; i++) अणु
		ec = (काष्ठा snd_soc_tplg_क्रमागत_control *)tplg->pos;
		/* validate kcontrol */
		अगर (strnlen(ec->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			    SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			जाओ err_se;

		se = devm_kzalloc(tplg->dev, माप(*se), GFP_KERNEL);
		अगर (se == शून्य)
			जाओ err_se;

		tplg->pos += (माप(काष्ठा snd_soc_tplg_क्रमागत_control) +
			      le32_to_cpu(ec->priv.size));

		dev_dbg(tplg->dev, " adding DAPM widget enum control %s\n",
			ec->hdr.name);

		kc[i].निजी_value = (दीर्घ)se;
		kc[i].name = devm_kstrdup(tplg->dev, ec->hdr.name, GFP_KERNEL);
		अगर (kc[i].name == शून्य)
			जाओ err_se;
		kc[i].अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc[i].access = le32_to_cpu(ec->hdr.access);

		/* we only support FL/FR channel mapping aपंचांग */
		se->reg = tplc_chan_get_reg(tplg, ec->channel, SNDRV_CHMAP_FL);
		se->shअगरt_l = tplc_chan_get_shअगरt(tplg, ec->channel,
						  SNDRV_CHMAP_FL);
		se->shअगरt_r = tplc_chan_get_shअगरt(tplg, ec->channel,
						  SNDRV_CHMAP_FR);

		se->items = le32_to_cpu(ec->items);
		se->mask = le32_to_cpu(ec->mask);
		se->करोbj.index = tplg->index;

		चयन (le32_to_cpu(ec->hdr.ops.info)) अणु
		हाल SND_SOC_TPLG_CTL_ENUM_VALUE:
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
			err = soc_tplg_dक्रमागत_create_values(tplg, se, ec);
			अगर (err < 0) अणु
				dev_err(tplg->dev, "ASoC: could not create values for %s\n",
					ec->hdr.name);
				जाओ err_se;
			पूर्ण
			fallthrough;
		हाल SND_SOC_TPLG_CTL_ENUM:
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
		हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
			err = soc_tplg_dक्रमागत_create_texts(tplg, se, ec);
			अगर (err < 0) अणु
				dev_err(tplg->dev, "ASoC: could not create texts for %s\n",
					ec->hdr.name);
				जाओ err_se;
			पूर्ण
			अवरोध;
		शेष:
			dev_err(tplg->dev, "ASoC: invalid enum control type %d for %s\n",
				ec->hdr.ops.info, ec->hdr.name);
			जाओ err_se;
		पूर्ण

		/* map io handlers */
		err = soc_tplg_kcontrol_bind_io(&ec->hdr, &kc[i], tplg);
		अगर (err) अणु
			soc_control_err(tplg, &ec->hdr, ec->hdr.name);
			जाओ err_se;
		पूर्ण

		/* pass control to driver क्रम optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc[i],
			(काष्ठा snd_soc_tplg_ctl_hdr *)ec);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				ec->hdr.name);
			जाओ err_se;
		पूर्ण
	पूर्ण

	वापस kc;

err_se:
	वापस शून्य;
पूर्ण

अटल काष्ठा snd_kcontrol_new *soc_tplg_dapm_widget_dbytes_create(
	काष्ठा soc_tplg *tplg, पूर्णांक num_kcontrols)
अणु
	काष्ठा snd_soc_tplg_bytes_control *be;
	काष्ठा soc_bytes_ext *sbe;
	काष्ठा snd_kcontrol_new *kc;
	पूर्णांक i, err;

	kc = devm_kसुस्मृति(tplg->dev, num_kcontrols, माप(*kc), GFP_KERNEL);
	अगर (!kc)
		वापस शून्य;

	क्रम (i = 0; i < num_kcontrols; i++) अणु
		be = (काष्ठा snd_soc_tplg_bytes_control *)tplg->pos;

		/* validate kcontrol */
		अगर (strnlen(be->hdr.name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
			SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
			जाओ err_sbe;

		sbe = devm_kzalloc(tplg->dev, माप(*sbe), GFP_KERNEL);
		अगर (sbe == शून्य)
			जाओ err_sbe;

		tplg->pos += (माप(काष्ठा snd_soc_tplg_bytes_control) +
			      le32_to_cpu(be->priv.size));

		dev_dbg(tplg->dev,
			"ASoC: adding bytes kcontrol %s with access 0x%x\n",
			be->hdr.name, be->hdr.access);

		kc[i].निजी_value = (दीर्घ)sbe;
		kc[i].name = devm_kstrdup(tplg->dev, be->hdr.name, GFP_KERNEL);
		अगर (kc[i].name == शून्य)
			जाओ err_sbe;
		kc[i].अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		kc[i].access = le32_to_cpu(be->hdr.access);

		sbe->max = le32_to_cpu(be->max);
		INIT_LIST_HEAD(&sbe->करोbj.list);

		/* map standard io handlers and check क्रम बाह्यal handlers */
		err = soc_tplg_kcontrol_bind_io(&be->hdr, &kc[i], tplg);
		अगर (err) अणु
			soc_control_err(tplg, &be->hdr, be->hdr.name);
			जाओ err_sbe;
		पूर्ण

		/* pass control to driver क्रम optional further init */
		err = soc_tplg_init_kcontrol(tplg, &kc[i],
			(काष्ठा snd_soc_tplg_ctl_hdr *)be);
		अगर (err < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to init %s\n",
				be->hdr.name);
			जाओ err_sbe;
		पूर्ण
	पूर्ण

	वापस kc;

err_sbe:

	वापस शून्य;
पूर्ण

अटल पूर्णांक soc_tplg_dapm_widget_create(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &tplg->comp->dapm;
	काष्ठा snd_soc_dapm_widget ढाँचा, *widget;
	काष्ठा snd_soc_tplg_ctl_hdr *control_hdr;
	काष्ठा snd_soc_card *card = tplg->comp->card;
	अचिन्हित पूर्णांक kcontrol_type;
	पूर्णांक ret = 0;

	अगर (strnlen(w->name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
		SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
		वापस -EINVAL;
	अगर (strnlen(w->sname, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) ==
		SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
		वापस -EINVAL;

	dev_dbg(tplg->dev, "ASoC: creating DAPM widget %s id %d\n",
		w->name, w->id);

	स_रखो(&ढाँचा, 0, माप(ढाँचा));

	/* map user to kernel widget ID */
	ढाँचा.id = get_widget_id(le32_to_cpu(w->id));
	अगर ((पूर्णांक)ढाँचा.id < 0)
		वापस ढाँचा.id;

	/* strings are allocated here, but used and मुक्तd by the widget */
	ढाँचा.name = kstrdup(w->name, GFP_KERNEL);
	अगर (!ढाँचा.name)
		वापस -ENOMEM;
	ढाँचा.sname = kstrdup(w->sname, GFP_KERNEL);
	अगर (!ढाँचा.sname) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	ढाँचा.reg = le32_to_cpu(w->reg);
	ढाँचा.shअगरt = le32_to_cpu(w->shअगरt);
	ढाँचा.mask = le32_to_cpu(w->mask);
	ढाँचा.subseq = le32_to_cpu(w->subseq);
	ढाँचा.on_val = w->invert ? 0 : 1;
	ढाँचा.off_val = w->invert ? 1 : 0;
	ढाँचा.ignore_suspend = le32_to_cpu(w->ignore_suspend);
	ढाँचा.event_flags = le16_to_cpu(w->event_flags);
	ढाँचा.करोbj.index = tplg->index;

	tplg->pos +=
		(माप(काष्ठा snd_soc_tplg_dapm_widget) +
		 le32_to_cpu(w->priv.size));

	अगर (w->num_kcontrols == 0) अणु
		kcontrol_type = 0;
		ढाँचा.num_kcontrols = 0;
		जाओ widget;
	पूर्ण

	control_hdr = (काष्ठा snd_soc_tplg_ctl_hdr *)tplg->pos;
	dev_dbg(tplg->dev, "ASoC: template %s has %d controls of type %x\n",
		w->name, w->num_kcontrols, control_hdr->type);

	चयन (le32_to_cpu(control_hdr->ops.info)) अणु
	हाल SND_SOC_TPLG_CTL_VOLSW:
	हाल SND_SOC_TPLG_CTL_STROBE:
	हाल SND_SOC_TPLG_CTL_VOLSW_SX:
	हाल SND_SOC_TPLG_CTL_VOLSW_XR_SX:
	हाल SND_SOC_TPLG_CTL_RANGE:
	हाल SND_SOC_TPLG_DAPM_CTL_VOLSW:
		kcontrol_type = SND_SOC_TPLG_TYPE_MIXER;  /* volume mixer */
		ढाँचा.num_kcontrols = le32_to_cpu(w->num_kcontrols);
		ढाँचा.kcontrol_news =
			soc_tplg_dapm_widget_dmixer_create(tplg,
			ढाँचा.num_kcontrols);
		अगर (!ढाँचा.kcontrol_news) अणु
			ret = -ENOMEM;
			जाओ hdr_err;
		पूर्ण
		अवरोध;
	हाल SND_SOC_TPLG_CTL_ENUM:
	हाल SND_SOC_TPLG_CTL_ENUM_VALUE:
	हाल SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
	हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
	हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
		kcontrol_type = SND_SOC_TPLG_TYPE_ENUM;	/* क्रमागतerated mixer */
		ढाँचा.num_kcontrols = le32_to_cpu(w->num_kcontrols);
		ढाँचा.kcontrol_news =
			soc_tplg_dapm_widget_dक्रमागत_create(tplg,
			ढाँचा.num_kcontrols);
		अगर (!ढाँचा.kcontrol_news) अणु
			ret = -ENOMEM;
			जाओ hdr_err;
		पूर्ण
		अवरोध;
	हाल SND_SOC_TPLG_CTL_BYTES:
		kcontrol_type = SND_SOC_TPLG_TYPE_BYTES; /* bytes control */
		ढाँचा.num_kcontrols = le32_to_cpu(w->num_kcontrols);
		ढाँचा.kcontrol_news =
			soc_tplg_dapm_widget_dbytes_create(tplg,
				ढाँचा.num_kcontrols);
		अगर (!ढाँचा.kcontrol_news) अणु
			ret = -ENOMEM;
			जाओ hdr_err;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(tplg->dev, "ASoC: invalid widget control type %d:%d:%d\n",
			control_hdr->ops.get, control_hdr->ops.put,
			le32_to_cpu(control_hdr->ops.info));
		ret = -EINVAL;
		जाओ hdr_err;
	पूर्ण

widget:
	ret = soc_tplg_widget_load(tplg, &ढाँचा, w);
	अगर (ret < 0)
		जाओ hdr_err;

	/* card dapm mutex is held by the core अगर we are loading topology
	 * data during sound card init. */
	अगर (card->instantiated)
		widget = snd_soc_dapm_new_control(dapm, &ढाँचा);
	अन्यथा
		widget = snd_soc_dapm_new_control_unlocked(dapm, &ढाँचा);
	अगर (IS_ERR(widget)) अणु
		ret = PTR_ERR(widget);
		जाओ hdr_err;
	पूर्ण

	widget->करोbj.type = SND_SOC_DOBJ_WIDGET;
	widget->करोbj.widget.kcontrol_type = kcontrol_type;
	widget->करोbj.ops = tplg->ops;
	widget->करोbj.index = tplg->index;
	list_add(&widget->करोbj.list, &tplg->comp->करोbj_list);

	ret = soc_tplg_widget_पढ़ोy(tplg, widget, w);
	अगर (ret < 0)
		जाओ पढ़ोy_err;

	kमुक्त(ढाँचा.sname);
	kमुक्त(ढाँचा.name);

	वापस 0;

पढ़ोy_err:
	हटाओ_widget(widget->dapm->component, &widget->करोbj, SOC_TPLG_PASS_WIDGET);
	snd_soc_dapm_मुक्त_widget(widget);
hdr_err:
	kमुक्त(ढाँचा.sname);
err:
	kमुक्त(ढाँचा.name);
	वापस ret;
पूर्ण

अटल पूर्णांक soc_tplg_dapm_widget_elems_load(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	काष्ठा snd_soc_tplg_dapm_widget *widget;
	पूर्णांक ret, count, i;

	count = le32_to_cpu(hdr->count);

	dev_dbg(tplg->dev, "ASoC: adding %d DAPM widgets\n", count);

	क्रम (i = 0; i < count; i++) अणु
		widget = (काष्ठा snd_soc_tplg_dapm_widget *) tplg->pos;
		अगर (le32_to_cpu(widget->size) != माप(*widget)) अणु
			dev_err(tplg->dev, "ASoC: invalid widget size\n");
			वापस -EINVAL;
		पूर्ण

		ret = soc_tplg_dapm_widget_create(tplg, widget);
		अगर (ret < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to load widget %s\n",
				widget->name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक soc_tplg_dapm_complete(काष्ठा soc_tplg *tplg)
अणु
	काष्ठा snd_soc_card *card = tplg->comp->card;
	पूर्णांक ret;

	/* Card might not have been रेजिस्टरed at this poपूर्णांक.
	 * If so, just वापस success.
	*/
	अगर (!card || !card->instantiated) अणु
		dev_warn(tplg->dev, "ASoC: Parent card not yet available,"
			" widget card binding deferred\n");
		वापस 0;
	पूर्ण

	ret = snd_soc_dapm_new_widमाला_लो(card);
	अगर (ret < 0)
		dev_err(tplg->dev, "ASoC: failed to create new widgets %d\n",
			ret);

	वापस 0;
पूर्ण

अटल पूर्णांक set_stream_info(काष्ठा soc_tplg *tplg, काष्ठा snd_soc_pcm_stream *stream,
			   काष्ठा snd_soc_tplg_stream_caps *caps)
अणु
	stream->stream_name = devm_kstrdup(tplg->dev, caps->name, GFP_KERNEL);
	अगर (!stream->stream_name)
		वापस -ENOMEM;

	stream->channels_min = le32_to_cpu(caps->channels_min);
	stream->channels_max = le32_to_cpu(caps->channels_max);
	stream->rates = le32_to_cpu(caps->rates);
	stream->rate_min = le32_to_cpu(caps->rate_min);
	stream->rate_max = le32_to_cpu(caps->rate_max);
	stream->क्रमmats = le64_to_cpu(caps->क्रमmats);
	stream->sig_bits = le32_to_cpu(caps->sig_bits);

	वापस 0;
पूर्ण

अटल व्योम set_dai_flags(काष्ठा snd_soc_dai_driver *dai_drv,
			  अचिन्हित पूर्णांक flag_mask, अचिन्हित पूर्णांक flags)
अणु
	अगर (flag_mask & SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_RATES)
		dai_drv->symmetric_rate =
			(flags & SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_RATES) ? 1 : 0;

	अगर (flag_mask & SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_CHANNELS)
		dai_drv->symmetric_channels =
			(flags & SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_CHANNELS) ?
			1 : 0;

	अगर (flag_mask & SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_SAMPLEBITS)
		dai_drv->symmetric_sample_bits =
			(flags & SND_SOC_TPLG_DAI_FLGBIT_SYMMETRIC_SAMPLEBITS) ?
			1 : 0;
पूर्ण

अटल पूर्णांक soc_tplg_dai_create(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_pcm *pcm)
अणु
	काष्ठा snd_soc_dai_driver *dai_drv;
	काष्ठा snd_soc_pcm_stream *stream;
	काष्ठा snd_soc_tplg_stream_caps *caps;
	काष्ठा snd_soc_dai *dai;
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(tplg->comp);
	पूर्णांक ret;

	dai_drv = devm_kzalloc(tplg->dev, माप(काष्ठा snd_soc_dai_driver), GFP_KERNEL);
	अगर (dai_drv == शून्य)
		वापस -ENOMEM;

	अगर (म_माप(pcm->dai_name)) अणु
		dai_drv->name = devm_kstrdup(tplg->dev, pcm->dai_name, GFP_KERNEL);
		अगर (!dai_drv->name) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण
	dai_drv->id = le32_to_cpu(pcm->dai_id);

	अगर (pcm->playback) अणु
		stream = &dai_drv->playback;
		caps = &pcm->caps[SND_SOC_TPLG_STREAM_PLAYBACK];
		ret = set_stream_info(tplg, stream, caps);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (pcm->capture) अणु
		stream = &dai_drv->capture;
		caps = &pcm->caps[SND_SOC_TPLG_STREAM_CAPTURE];
		ret = set_stream_info(tplg, stream, caps);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (pcm->compress)
		dai_drv->compress_new = snd_soc_new_compress;

	/* pass control to component driver क्रम optional further init */
	ret = soc_tplg_dai_load(tplg, dai_drv, pcm, शून्य);
	अगर (ret < 0) अणु
		dev_err(tplg->dev, "ASoC: DAI loading failed\n");
		जाओ err;
	पूर्ण

	dai_drv->करोbj.index = tplg->index;
	dai_drv->करोbj.ops = tplg->ops;
	dai_drv->करोbj.type = SND_SOC_DOBJ_PCM;
	list_add(&dai_drv->करोbj.list, &tplg->comp->करोbj_list);

	/* रेजिस्टर the DAI to the component */
	dai = snd_soc_रेजिस्टर_dai(tplg->comp, dai_drv, false);
	अगर (!dai)
		वापस -ENOMEM;

	/* Create the DAI widमाला_लो here */
	ret = snd_soc_dapm_new_dai_widमाला_लो(dapm, dai);
	अगर (ret != 0) अणु
		dev_err(dai->dev, "Failed to create DAI widgets %d\n", ret);
		snd_soc_unरेजिस्टर_dai(dai);
		वापस ret;
	पूर्ण

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल व्योम set_link_flags(काष्ठा snd_soc_dai_link *link,
		अचिन्हित पूर्णांक flag_mask, अचिन्हित पूर्णांक flags)
अणु
	अगर (flag_mask & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_RATES)
		link->symmetric_rate =
			(flags & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_RATES) ? 1 : 0;

	अगर (flag_mask & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_CHANNELS)
		link->symmetric_channels =
			(flags & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_CHANNELS) ?
			1 : 0;

	अगर (flag_mask & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_SAMPLEBITS)
		link->symmetric_sample_bits =
			(flags & SND_SOC_TPLG_LNK_FLGBIT_SYMMETRIC_SAMPLEBITS) ?
			1 : 0;

	अगर (flag_mask & SND_SOC_TPLG_LNK_FLGBIT_VOICE_WAKEUP)
		link->ignore_suspend =
			(flags & SND_SOC_TPLG_LNK_FLGBIT_VOICE_WAKEUP) ?
			1 : 0;
पूर्ण

/* create the FE DAI link */
अटल पूर्णांक soc_tplg_fe_link_create(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_pcm *pcm)
अणु
	काष्ठा snd_soc_dai_link *link;
	काष्ठा snd_soc_dai_link_component *dlc;
	पूर्णांक ret;

	/* link + cpu + codec + platक्रमm */
	link = devm_kzalloc(tplg->dev, माप(*link) + (3 * माप(*dlc)), GFP_KERNEL);
	अगर (link == शून्य)
		वापस -ENOMEM;

	dlc = (काष्ठा snd_soc_dai_link_component *)(link + 1);

	link->cpus	= &dlc[0];
	link->codecs	= &dlc[1];
	link->platक्रमms	= &dlc[2];

	link->num_cpus	 = 1;
	link->num_codecs = 1;
	link->num_platक्रमms = 1;

	link->करोbj.index = tplg->index;
	link->करोbj.ops = tplg->ops;
	link->करोbj.type = SND_SOC_DOBJ_DAI_LINK;

	अगर (म_माप(pcm->pcm_name)) अणु
		link->name = devm_kstrdup(tplg->dev, pcm->pcm_name, GFP_KERNEL);
		link->stream_name = devm_kstrdup(tplg->dev, pcm->pcm_name, GFP_KERNEL);
		अगर (!link->name || !link->stream_name) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण
	link->id = le32_to_cpu(pcm->pcm_id);

	अगर (म_माप(pcm->dai_name)) अणु
		link->cpus->dai_name = devm_kstrdup(tplg->dev, pcm->dai_name, GFP_KERNEL);
		अगर (!link->cpus->dai_name) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	link->codecs->name = "snd-soc-dummy";
	link->codecs->dai_name = "snd-soc-dummy-dai";

	link->platक्रमms->name = "snd-soc-dummy";

	/* enable DPCM */
	link->dynamic = 1;
	link->dpcm_playback = le32_to_cpu(pcm->playback);
	link->dpcm_capture = le32_to_cpu(pcm->capture);
	अगर (pcm->flag_mask)
		set_link_flags(link,
			       le32_to_cpu(pcm->flag_mask),
			       le32_to_cpu(pcm->flags));

	/* pass control to component driver क्रम optional further init */
	ret = soc_tplg_dai_link_load(tplg, link, शून्य);
	अगर (ret < 0) अणु
		dev_err(tplg->dev, "ASoC: FE link loading failed\n");
		जाओ err;
	पूर्ण

	ret = snd_soc_add_pcm_runसमय(tplg->comp->card, link);
	अगर (ret < 0) अणु
		dev_err(tplg->dev, "ASoC: adding FE link failed\n");
		जाओ err;
	पूर्ण

	list_add(&link->करोbj.list, &tplg->comp->करोbj_list);

	वापस 0;
err:
	वापस ret;
पूर्ण

/* create a FE DAI and DAI link from the PCM object */
अटल पूर्णांक soc_tplg_pcm_create(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_pcm *pcm)
अणु
	पूर्णांक ret;

	ret = soc_tplg_dai_create(tplg, pcm);
	अगर (ret < 0)
		वापस ret;

	वापस  soc_tplg_fe_link_create(tplg, pcm);
पूर्ण

/* copy stream caps from the old version 4 of source */
अटल व्योम stream_caps_new_ver(काष्ठा snd_soc_tplg_stream_caps *dest,
				काष्ठा snd_soc_tplg_stream_caps_v4 *src)
अणु
	dest->size = cpu_to_le32(माप(*dest));
	स_नकल(dest->name, src->name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	dest->क्रमmats = src->क्रमmats;
	dest->rates = src->rates;
	dest->rate_min = src->rate_min;
	dest->rate_max = src->rate_max;
	dest->channels_min = src->channels_min;
	dest->channels_max = src->channels_max;
	dest->periods_min = src->periods_min;
	dest->periods_max = src->periods_max;
	dest->period_size_min = src->period_size_min;
	dest->period_size_max = src->period_size_max;
	dest->buffer_size_min = src->buffer_size_min;
	dest->buffer_size_max = src->buffer_size_max;
पूर्ण

/**
 * pcm_new_ver - Create the new version of PCM from the old version.
 * @tplg: topology context
 * @src: older version of pcm as a source
 * @pcm: latest version of pcm created from the source
 *
 * Support from version 4. User should मुक्त the वापसed pcm manually.
 */
अटल पूर्णांक pcm_new_ver(काष्ठा soc_tplg *tplg,
		       काष्ठा snd_soc_tplg_pcm *src,
		       काष्ठा snd_soc_tplg_pcm **pcm)
अणु
	काष्ठा snd_soc_tplg_pcm *dest;
	काष्ठा snd_soc_tplg_pcm_v4 *src_v4;
	पूर्णांक i;

	*pcm = शून्य;

	अगर (le32_to_cpu(src->size) != माप(*src_v4)) अणु
		dev_err(tplg->dev, "ASoC: invalid PCM size\n");
		वापस -EINVAL;
	पूर्ण

	dev_warn(tplg->dev, "ASoC: old version of PCM\n");
	src_v4 = (काष्ठा snd_soc_tplg_pcm_v4 *)src;
	dest = kzalloc(माप(*dest), GFP_KERNEL);
	अगर (!dest)
		वापस -ENOMEM;

	dest->size = cpu_to_le32(माप(*dest)); /* size of latest abi version */
	स_नकल(dest->pcm_name, src_v4->pcm_name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	स_नकल(dest->dai_name, src_v4->dai_name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	dest->pcm_id = src_v4->pcm_id;
	dest->dai_id = src_v4->dai_id;
	dest->playback = src_v4->playback;
	dest->capture = src_v4->capture;
	dest->compress = src_v4->compress;
	dest->num_streams = src_v4->num_streams;
	क्रम (i = 0; i < le32_to_cpu(dest->num_streams); i++)
		स_नकल(&dest->stream[i], &src_v4->stream[i],
		       माप(काष्ठा snd_soc_tplg_stream));

	क्रम (i = 0; i < 2; i++)
		stream_caps_new_ver(&dest->caps[i], &src_v4->caps[i]);

	*pcm = dest;
	वापस 0;
पूर्ण

अटल पूर्णांक soc_tplg_pcm_elems_load(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	काष्ठा snd_soc_tplg_pcm *pcm, *_pcm;
	पूर्णांक count;
	पूर्णांक size;
	पूर्णांक i;
	bool abi_match;
	पूर्णांक ret;

	count = le32_to_cpu(hdr->count);

	/* check the element size and count */
	pcm = (काष्ठा snd_soc_tplg_pcm *)tplg->pos;
	size = le32_to_cpu(pcm->size);
	अगर (size > माप(काष्ठा snd_soc_tplg_pcm)
		|| size < माप(काष्ठा snd_soc_tplg_pcm_v4)) अणु
		dev_err(tplg->dev, "ASoC: invalid size %d for PCM elems\n",
			size);
		वापस -EINVAL;
	पूर्ण

	अगर (soc_tplg_check_elem_count(tplg,
				      size, count,
				      le32_to_cpu(hdr->payload_size),
				      "PCM DAI")) अणु
		dev_err(tplg->dev, "ASoC: invalid count %d for PCM DAI elems\n",
			count);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		pcm = (काष्ठा snd_soc_tplg_pcm *)tplg->pos;
		size = le32_to_cpu(pcm->size);

		/* check ABI version by size, create a new version of pcm
		 * अगर abi not match.
		 */
		अगर (size == माप(*pcm)) अणु
			abi_match = true;
			_pcm = pcm;
		पूर्ण अन्यथा अणु
			abi_match = false;
			ret = pcm_new_ver(tplg, pcm, &_pcm);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		/* create the FE DAIs and DAI links */
		ret = soc_tplg_pcm_create(tplg, _pcm);
		अगर (ret < 0) अणु
			अगर (!abi_match)
				kमुक्त(_pcm);
			वापस ret;
		पूर्ण

		/* offset by version-specअगरic काष्ठा size and
		 * real priv data size
		 */
		tplg->pos += size + le32_to_cpu(_pcm->priv.size);

		अगर (!abi_match)
			kमुक्त(_pcm); /* मुक्त the duplicated one */
	पूर्ण

	dev_dbg(tplg->dev, "ASoC: adding %d PCM DAIs\n", count);

	वापस 0;
पूर्ण

/**
 * set_link_hw_क्रमmat - Set the HW audio क्रमmat of the physical DAI link.
 * @link: &snd_soc_dai_link which should be updated
 * @cfg: physical link configs.
 *
 * Topology context contains a list of supported HW क्रमmats (configs) and
 * a शेष क्रमmat ID क्रम the physical link. This function will use this
 * शेष ID to choose the HW क्रमmat to set the link's DAI क्रमmat क्रम init.
 */
अटल व्योम set_link_hw_क्रमmat(काष्ठा snd_soc_dai_link *link,
			काष्ठा snd_soc_tplg_link_config *cfg)
अणु
	काष्ठा snd_soc_tplg_hw_config *hw_config;
	अचिन्हित अक्षर bclk_provider, fsync_provider;
	अचिन्हित अक्षर invert_bclk, invert_fsync;
	पूर्णांक i;

	क्रम (i = 0; i < le32_to_cpu(cfg->num_hw_configs); i++) अणु
		hw_config = &cfg->hw_config[i];
		अगर (hw_config->id != cfg->शेष_hw_config_id)
			जारी;

		link->dai_fmt = le32_to_cpu(hw_config->fmt) &
			SND_SOC_DAIFMT_FORMAT_MASK;

		/* घड़ी gating */
		चयन (hw_config->घड़ी_gated) अणु
		हाल SND_SOC_TPLG_DAI_CLK_GATE_GATED:
			link->dai_fmt |= SND_SOC_DAIFMT_GATED;
			अवरोध;

		हाल SND_SOC_TPLG_DAI_CLK_GATE_CONT:
			link->dai_fmt |= SND_SOC_DAIFMT_CONT;
			अवरोध;

		शेष:
			/* ignore the value */
			अवरोध;
		पूर्ण

		/* घड़ी संकेत polarity */
		invert_bclk = hw_config->invert_bclk;
		invert_fsync = hw_config->invert_fsync;
		अगर (!invert_bclk && !invert_fsync)
			link->dai_fmt |= SND_SOC_DAIFMT_NB_NF;
		अन्यथा अगर (!invert_bclk && invert_fsync)
			link->dai_fmt |= SND_SOC_DAIFMT_NB_IF;
		अन्यथा अगर (invert_bclk && !invert_fsync)
			link->dai_fmt |= SND_SOC_DAIFMT_IB_NF;
		अन्यथा
			link->dai_fmt |= SND_SOC_DAIFMT_IB_IF;

		/* घड़ी masters */
		bclk_provider = (hw_config->bclk_provider ==
			       SND_SOC_TPLG_BCLK_CP);
		fsync_provider = (hw_config->fsync_provider ==
				SND_SOC_TPLG_FSYNC_CP);
		अगर (bclk_provider && fsync_provider)
			link->dai_fmt |= SND_SOC_DAIFMT_CBP_CFP;
		अन्यथा अगर (!bclk_provider && fsync_provider)
			link->dai_fmt |= SND_SOC_DAIFMT_CBC_CFP;
		अन्यथा अगर (bclk_provider && !fsync_provider)
			link->dai_fmt |= SND_SOC_DAIFMT_CBP_CFC;
		अन्यथा
			link->dai_fmt |= SND_SOC_DAIFMT_CBC_CFC;
	पूर्ण
पूर्ण

/**
 * link_new_ver - Create a new physical link config from the old
 * version of source.
 * @tplg: topology context
 * @src: old version of phyical link config as a source
 * @link: latest version of physical link config created from the source
 *
 * Support from version 4. User need मुक्त the वापसed link config manually.
 */
अटल पूर्णांक link_new_ver(काष्ठा soc_tplg *tplg,
			काष्ठा snd_soc_tplg_link_config *src,
			काष्ठा snd_soc_tplg_link_config **link)
अणु
	काष्ठा snd_soc_tplg_link_config *dest;
	काष्ठा snd_soc_tplg_link_config_v4 *src_v4;
	पूर्णांक i;

	*link = शून्य;

	अगर (le32_to_cpu(src->size) !=
	    माप(काष्ठा snd_soc_tplg_link_config_v4)) अणु
		dev_err(tplg->dev, "ASoC: invalid physical link config size\n");
		वापस -EINVAL;
	पूर्ण

	dev_warn(tplg->dev, "ASoC: old version of physical link config\n");

	src_v4 = (काष्ठा snd_soc_tplg_link_config_v4 *)src;
	dest = kzalloc(माप(*dest), GFP_KERNEL);
	अगर (!dest)
		वापस -ENOMEM;

	dest->size = cpu_to_le32(माप(*dest));
	dest->id = src_v4->id;
	dest->num_streams = src_v4->num_streams;
	क्रम (i = 0; i < le32_to_cpu(dest->num_streams); i++)
		स_नकल(&dest->stream[i], &src_v4->stream[i],
		       माप(काष्ठा snd_soc_tplg_stream));

	*link = dest;
	वापस 0;
पूर्ण

/**
 * snd_soc_find_dai_link - Find a DAI link
 *
 * @card: soc card
 * @id: DAI link ID to match
 * @name: DAI link name to match, optional
 * @stream_name: DAI link stream name to match, optional
 *
 * This function will search all existing DAI links of the soc card to
 * find the link of the same ID. Since DAI links may not have their
 * unique ID, so name and stream name should also match अगर being
 * specअगरied.
 *
 * Return: poपूर्णांकer of DAI link, or शून्य अगर not found.
 */
अटल काष्ठा snd_soc_dai_link *snd_soc_find_dai_link(काष्ठा snd_soc_card *card,
						      पूर्णांक id, स्थिर अक्षर *name,
						      स्थिर अक्षर *stream_name)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai_link *link;

	क्रम_each_card_rtds(card, rtd) अणु
		link = rtd->dai_link;

		अगर (link->id != id)
			जारी;

		अगर (name && (!link->name || म_भेद(name, link->name)))
			जारी;

		अगर (stream_name && (!link->stream_name
				    || म_भेद(stream_name, link->stream_name)))
			जारी;

		वापस link;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Find and configure an existing physical DAI link */
अटल पूर्णांक soc_tplg_link_config(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_link_config *cfg)
अणु
	काष्ठा snd_soc_dai_link *link;
	स्थिर अक्षर *name, *stream_name;
	माप_प्रकार len;
	पूर्णांक ret;

	len = strnlen(cfg->name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	अगर (len == SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
		वापस -EINVAL;
	अन्यथा अगर (len)
		name = cfg->name;
	अन्यथा
		name = शून्य;

	len = strnlen(cfg->stream_name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	अगर (len == SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
		वापस -EINVAL;
	अन्यथा अगर (len)
		stream_name = cfg->stream_name;
	अन्यथा
		stream_name = शून्य;

	link = snd_soc_find_dai_link(tplg->comp->card, le32_to_cpu(cfg->id),
				     name, stream_name);
	अगर (!link) अणु
		dev_err(tplg->dev, "ASoC: physical link %s (id %d) not exist\n",
			name, cfg->id);
		वापस -EINVAL;
	पूर्ण

	/* hw क्रमmat */
	अगर (cfg->num_hw_configs)
		set_link_hw_क्रमmat(link, cfg);

	/* flags */
	अगर (cfg->flag_mask)
		set_link_flags(link,
			       le32_to_cpu(cfg->flag_mask),
			       le32_to_cpu(cfg->flags));

	/* pass control to component driver क्रम optional further init */
	ret = soc_tplg_dai_link_load(tplg, link, cfg);
	अगर (ret < 0) अणु
		dev_err(tplg->dev, "ASoC: physical link loading failed\n");
		वापस ret;
	पूर्ण

	/* क्रम unloading it in snd_soc_tplg_component_हटाओ */
	link->करोbj.index = tplg->index;
	link->करोbj.ops = tplg->ops;
	link->करोbj.type = SND_SOC_DOBJ_BACKEND_LINK;
	list_add(&link->करोbj.list, &tplg->comp->करोbj_list);

	वापस 0;
पूर्ण


/* Load physical link config elements from the topology context */
अटल पूर्णांक soc_tplg_link_elems_load(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	काष्ठा snd_soc_tplg_link_config *link, *_link;
	पूर्णांक count;
	पूर्णांक size;
	पूर्णांक i, ret;
	bool abi_match;

	count = le32_to_cpu(hdr->count);

	/* check the element size and count */
	link = (काष्ठा snd_soc_tplg_link_config *)tplg->pos;
	size = le32_to_cpu(link->size);
	अगर (size > माप(काष्ठा snd_soc_tplg_link_config)
		|| size < माप(काष्ठा snd_soc_tplg_link_config_v4)) अणु
		dev_err(tplg->dev, "ASoC: invalid size %d for physical link elems\n",
			size);
		वापस -EINVAL;
	पूर्ण

	अगर (soc_tplg_check_elem_count(tplg,
				      size, count,
				      le32_to_cpu(hdr->payload_size),
				      "physical link config")) अणु
		dev_err(tplg->dev, "ASoC: invalid count %d for physical link elems\n",
			count);
		वापस -EINVAL;
	पूर्ण

	/* config physical DAI links */
	क्रम (i = 0; i < count; i++) अणु
		link = (काष्ठा snd_soc_tplg_link_config *)tplg->pos;
		size = le32_to_cpu(link->size);
		अगर (size == माप(*link)) अणु
			abi_match = true;
			_link = link;
		पूर्ण अन्यथा अणु
			abi_match = false;
			ret = link_new_ver(tplg, link, &_link);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ret = soc_tplg_link_config(tplg, _link);
		अगर (ret < 0) अणु
			अगर (!abi_match)
				kमुक्त(_link);
			वापस ret;
		पूर्ण

		/* offset by version-specअगरic काष्ठा size and
		 * real priv data size
		 */
		tplg->pos += size + le32_to_cpu(_link->priv.size);

		अगर (!abi_match)
			kमुक्त(_link); /* मुक्त the duplicated one */
	पूर्ण

	वापस 0;
पूर्ण

/**
 * soc_tplg_dai_config - Find and configure an existing physical DAI.
 * @tplg: topology context
 * @d: physical DAI configs.
 *
 * The physical dai should alपढ़ोy be रेजिस्टरed by the platक्रमm driver.
 * The platक्रमm driver should specअगरy the DAI name and ID क्रम matching.
 */
अटल पूर्णांक soc_tplg_dai_config(काष्ठा soc_tplg *tplg,
			       काष्ठा snd_soc_tplg_dai *d)
अणु
	काष्ठा snd_soc_dai_link_component dai_component;
	काष्ठा snd_soc_dai *dai;
	काष्ठा snd_soc_dai_driver *dai_drv;
	काष्ठा snd_soc_pcm_stream *stream;
	काष्ठा snd_soc_tplg_stream_caps *caps;
	पूर्णांक ret;

	स_रखो(&dai_component, 0, माप(dai_component));

	dai_component.dai_name = d->dai_name;
	dai = snd_soc_find_dai(&dai_component);
	अगर (!dai) अणु
		dev_err(tplg->dev, "ASoC: physical DAI %s not registered\n",
			d->dai_name);
		वापस -EINVAL;
	पूर्ण

	अगर (le32_to_cpu(d->dai_id) != dai->id) अणु
		dev_err(tplg->dev, "ASoC: physical DAI %s id mismatch\n",
			d->dai_name);
		वापस -EINVAL;
	पूर्ण

	dai_drv = dai->driver;
	अगर (!dai_drv)
		वापस -EINVAL;

	अगर (d->playback) अणु
		stream = &dai_drv->playback;
		caps = &d->caps[SND_SOC_TPLG_STREAM_PLAYBACK];
		ret = set_stream_info(tplg, stream, caps);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (d->capture) अणु
		stream = &dai_drv->capture;
		caps = &d->caps[SND_SOC_TPLG_STREAM_CAPTURE];
		ret = set_stream_info(tplg, stream, caps);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (d->flag_mask)
		set_dai_flags(dai_drv,
			      le32_to_cpu(d->flag_mask),
			      le32_to_cpu(d->flags));

	/* pass control to component driver क्रम optional further init */
	ret = soc_tplg_dai_load(tplg, dai_drv, शून्य, dai);
	अगर (ret < 0) अणु
		dev_err(tplg->dev, "ASoC: DAI loading failed\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	वापस ret;
पूर्ण

/* load physical DAI elements */
अटल पूर्णांक soc_tplg_dai_elems_load(काष्ठा soc_tplg *tplg,
				   काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	काष्ठा snd_soc_tplg_dai *dai;
	पूर्णांक count;
	पूर्णांक i, ret;

	count = le32_to_cpu(hdr->count);

	/* config the existing BE DAIs */
	क्रम (i = 0; i < count; i++) अणु
		dai = (काष्ठा snd_soc_tplg_dai *)tplg->pos;
		अगर (le32_to_cpu(dai->size) != माप(*dai)) अणु
			dev_err(tplg->dev, "ASoC: invalid physical DAI size\n");
			वापस -EINVAL;
		पूर्ण

		ret = soc_tplg_dai_config(tplg, dai);
		अगर (ret < 0) अणु
			dev_err(tplg->dev, "ASoC: failed to configure DAI\n");
			वापस ret;
		पूर्ण

		tplg->pos += (माप(*dai) + le32_to_cpu(dai->priv.size));
	पूर्ण

	dev_dbg(tplg->dev, "ASoC: Configure %d BE DAIs\n", count);
	वापस 0;
पूर्ण

/**
 * manअगरest_new_ver - Create a new version of manअगरest from the old version
 * of source.
 * @tplg: topology context
 * @src: old version of manअगरest as a source
 * @manअगरest: latest version of manअगरest created from the source
 *
 * Support from version 4. Users need मुक्त the वापसed manअगरest manually.
 */
अटल पूर्णांक manअगरest_new_ver(काष्ठा soc_tplg *tplg,
			    काष्ठा snd_soc_tplg_manअगरest *src,
			    काष्ठा snd_soc_tplg_manअगरest **manअगरest)
अणु
	काष्ठा snd_soc_tplg_manअगरest *dest;
	काष्ठा snd_soc_tplg_manअगरest_v4 *src_v4;
	पूर्णांक size;

	*manअगरest = शून्य;

	size = le32_to_cpu(src->size);
	अगर (size != माप(*src_v4)) अणु
		dev_warn(tplg->dev, "ASoC: invalid manifest size %d\n",
			 size);
		अगर (size)
			वापस -EINVAL;
		src->size = cpu_to_le32(माप(*src_v4));
	पूर्ण

	dev_warn(tplg->dev, "ASoC: old version of manifest\n");

	src_v4 = (काष्ठा snd_soc_tplg_manअगरest_v4 *)src;
	dest = kzalloc(माप(*dest) + le32_to_cpu(src_v4->priv.size),
		       GFP_KERNEL);
	अगर (!dest)
		वापस -ENOMEM;

	dest->size = cpu_to_le32(माप(*dest)); /* size of latest abi version */
	dest->control_elems = src_v4->control_elems;
	dest->widget_elems = src_v4->widget_elems;
	dest->graph_elems = src_v4->graph_elems;
	dest->pcm_elems = src_v4->pcm_elems;
	dest->dai_link_elems = src_v4->dai_link_elems;
	dest->priv.size = src_v4->priv.size;
	अगर (dest->priv.size)
		स_नकल(dest->priv.data, src_v4->priv.data,
		       le32_to_cpu(src_v4->priv.size));

	*manअगरest = dest;
	वापस 0;
पूर्ण

अटल पूर्णांक soc_tplg_manअगरest_load(काष्ठा soc_tplg *tplg,
				  काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	काष्ठा snd_soc_tplg_manअगरest *manअगरest, *_manअगरest;
	bool abi_match;
	पूर्णांक ret = 0;

	manअगरest = (काष्ठा snd_soc_tplg_manअगरest *)tplg->pos;

	/* check ABI version by size, create a new manअगरest अगर abi not match */
	अगर (le32_to_cpu(manअगरest->size) == माप(*manअगरest)) अणु
		abi_match = true;
		_manअगरest = manअगरest;
	पूर्ण अन्यथा अणु
		abi_match = false;
		ret = manअगरest_new_ver(tplg, manअगरest, &_manअगरest);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* pass control to component driver क्रम optional further init */
	अगर (tplg->ops && tplg->ops->manअगरest)
		ret = tplg->ops->manअगरest(tplg->comp, tplg->index, _manअगरest);

	अगर (!abi_match)	/* मुक्त the duplicated one */
		kमुक्त(_manअगरest);

	वापस ret;
पूर्ण

/* validate header magic, size and type */
अटल पूर्णांक soc_valid_header(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	अगर (soc_tplg_get_hdr_offset(tplg) >= tplg->fw->size)
		वापस 0;

	अगर (le32_to_cpu(hdr->size) != माप(*hdr)) अणु
		dev_err(tplg->dev,
			"ASoC: invalid header size for type %d at offset 0x%lx size 0x%zx.\n",
			le32_to_cpu(hdr->type), soc_tplg_get_hdr_offset(tplg),
			tplg->fw->size);
		वापस -EINVAL;
	पूर्ण

	/* big endian firmware objects not supported aपंचांग */
	अगर (le32_to_cpu(hdr->magic) == SOC_TPLG_MAGIC_BIG_ENDIAN) अणु
		dev_err(tplg->dev,
			"ASoC: pass %d big endian not supported header got %x at offset 0x%lx size 0x%zx.\n",
			tplg->pass, hdr->magic,
			soc_tplg_get_hdr_offset(tplg), tplg->fw->size);
		वापस -EINVAL;
	पूर्ण

	अगर (le32_to_cpu(hdr->magic) != SND_SOC_TPLG_MAGIC) अणु
		dev_err(tplg->dev,
			"ASoC: pass %d does not have a valid header got %x at offset 0x%lx size 0x%zx.\n",
			tplg->pass, hdr->magic,
			soc_tplg_get_hdr_offset(tplg), tplg->fw->size);
		वापस -EINVAL;
	पूर्ण

	/* Support ABI from version 4 */
	अगर (le32_to_cpu(hdr->abi) > SND_SOC_TPLG_ABI_VERSION ||
	    le32_to_cpu(hdr->abi) < SND_SOC_TPLG_ABI_VERSION_MIN) अणु
		dev_err(tplg->dev,
			"ASoC: pass %d invalid ABI version got 0x%x need 0x%x at offset 0x%lx size 0x%zx.\n",
			tplg->pass, hdr->abi,
			SND_SOC_TPLG_ABI_VERSION, soc_tplg_get_hdr_offset(tplg),
			tplg->fw->size);
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->payload_size == 0) अणु
		dev_err(tplg->dev, "ASoC: header has 0 size at offset 0x%lx.\n",
			soc_tplg_get_hdr_offset(tplg));
		वापस -EINVAL;
	पूर्ण

	वापस 1;
पूर्ण

/* check header type and call appropriate handler */
अटल पूर्णांक soc_tplg_load_header(काष्ठा soc_tplg *tplg,
	काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	पूर्णांक (*elem_load)(काष्ठा soc_tplg *tplg,
			 काष्ठा snd_soc_tplg_hdr *hdr);
	अचिन्हित पूर्णांक hdr_pass;

	tplg->pos = tplg->hdr_pos + माप(काष्ठा snd_soc_tplg_hdr);

	tplg->index = le32_to_cpu(hdr->index);

	चयन (le32_to_cpu(hdr->type)) अणु
	हाल SND_SOC_TPLG_TYPE_MIXER:
	हाल SND_SOC_TPLG_TYPE_ENUM:
	हाल SND_SOC_TPLG_TYPE_BYTES:
		hdr_pass = SOC_TPLG_PASS_MIXER;
		elem_load = soc_tplg_kcontrol_elems_load;
		अवरोध;
	हाल SND_SOC_TPLG_TYPE_DAPM_GRAPH:
		hdr_pass = SOC_TPLG_PASS_GRAPH;
		elem_load = soc_tplg_dapm_graph_elems_load;
		अवरोध;
	हाल SND_SOC_TPLG_TYPE_DAPM_WIDGET:
		hdr_pass = SOC_TPLG_PASS_WIDGET;
		elem_load = soc_tplg_dapm_widget_elems_load;
		अवरोध;
	हाल SND_SOC_TPLG_TYPE_PCM:
		hdr_pass = SOC_TPLG_PASS_PCM_DAI;
		elem_load = soc_tplg_pcm_elems_load;
		अवरोध;
	हाल SND_SOC_TPLG_TYPE_DAI:
		hdr_pass = SOC_TPLG_PASS_BE_DAI;
		elem_load = soc_tplg_dai_elems_load;
		अवरोध;
	हाल SND_SOC_TPLG_TYPE_DAI_LINK:
	हाल SND_SOC_TPLG_TYPE_BACKEND_LINK:
		/* physical link configurations */
		hdr_pass = SOC_TPLG_PASS_LINK;
		elem_load = soc_tplg_link_elems_load;
		अवरोध;
	हाल SND_SOC_TPLG_TYPE_MANIFEST:
		hdr_pass = SOC_TPLG_PASS_MANIFEST;
		elem_load = soc_tplg_manअगरest_load;
		अवरोध;
	शेष:
		/* bespoke venकरोr data object */
		hdr_pass = SOC_TPLG_PASS_VENDOR;
		elem_load = soc_tplg_venकरोr_load;
		अवरोध;
	पूर्ण

	अगर (tplg->pass == hdr_pass) अणु
		dev_dbg(tplg->dev,
			"ASoC: Got 0x%x bytes of type %d version %d vendor %d at pass %d\n",
			hdr->payload_size, hdr->type, hdr->version,
			hdr->venकरोr_type, tplg->pass);
		वापस elem_load(tplg, hdr);
	पूर्ण

	वापस 0;
पूर्ण

/* process the topology file headers */
अटल पूर्णांक soc_tplg_process_headers(काष्ठा soc_tplg *tplg)
अणु
	काष्ठा snd_soc_tplg_hdr *hdr;
	पूर्णांक ret;

	tplg->pass = SOC_TPLG_PASS_START;

	/* process the header types from start to end */
	जबतक (tplg->pass <= SOC_TPLG_PASS_END) अणु

		tplg->hdr_pos = tplg->fw->data;
		hdr = (काष्ठा snd_soc_tplg_hdr *)tplg->hdr_pos;

		जबतक (!soc_tplg_is_eof(tplg)) अणु

			/* make sure header is valid beक्रमe loading */
			ret = soc_valid_header(tplg, hdr);
			अगर (ret < 0) अणु
				dev_err(tplg->dev,
					"ASoC: topology: invalid header: %d\n", ret);
				वापस ret;
			पूर्ण अन्यथा अगर (ret == 0) अणु
				अवरोध;
			पूर्ण

			/* load the header object */
			ret = soc_tplg_load_header(tplg, hdr);
			अगर (ret < 0) अणु
				dev_err(tplg->dev,
					"ASoC: topology: could not load header: %d\n", ret);
				वापस ret;
			पूर्ण

			/* जाओ next header */
			tplg->hdr_pos += le32_to_cpu(hdr->payload_size) +
				माप(काष्ठा snd_soc_tplg_hdr);
			hdr = (काष्ठा snd_soc_tplg_hdr *)tplg->hdr_pos;
		पूर्ण

		/* next data type pass */
		tplg->pass++;
	पूर्ण

	/* संकेत DAPM we are complete */
	ret = soc_tplg_dapm_complete(tplg);
	अगर (ret < 0)
		dev_err(tplg->dev,
			"ASoC: failed to initialise DAPM from Firmware\n");

	वापस ret;
पूर्ण

अटल पूर्णांक soc_tplg_load(काष्ठा soc_tplg *tplg)
अणु
	पूर्णांक ret;

	ret = soc_tplg_process_headers(tplg);
	अगर (ret == 0)
		soc_tplg_complete(tplg);

	वापस ret;
पूर्ण

/* load audio component topology from "firmware" file */
पूर्णांक snd_soc_tplg_component_load(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_tplg_ops *ops, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा soc_tplg tplg;
	पूर्णांक ret;

	/*
	 * check अगर we have sane parameters:
	 * comp - needs to exist to keep and reference data जबतक parsing
	 * comp->dev - used क्रम resource management and prपूर्णांकs
	 * comp->card - used क्रम setting card related parameters
	 * fw - we need it, as it is the very thing we parse
	 */
	अगर (!comp || !comp->dev || !comp->card || !fw)
		वापस -EINVAL;

	/* setup parsing context */
	स_रखो(&tplg, 0, माप(tplg));
	tplg.fw = fw;
	tplg.dev = comp->dev;
	tplg.comp = comp;
	अगर (ops) अणु
		tplg.ops = ops;
		tplg.io_ops = ops->io_ops;
		tplg.io_ops_count = ops->io_ops_count;
		tplg.bytes_ext_ops = ops->bytes_ext_ops;
		tplg.bytes_ext_ops_count = ops->bytes_ext_ops_count;
	पूर्ण

	ret = soc_tplg_load(&tplg);
	/* मुक्त the created components अगर fail to load topology */
	अगर (ret)
		snd_soc_tplg_component_हटाओ(comp);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_tplg_component_load);

/* हटाओ dynamic controls from the component driver */
पूर्णांक snd_soc_tplg_component_हटाओ(काष्ठा snd_soc_component *comp)
अणु
	काष्ठा snd_soc_करोbj *करोbj, *next_करोbj;
	पूर्णांक pass = SOC_TPLG_PASS_END;

	/* process the header types from end to start */
	जबतक (pass >= SOC_TPLG_PASS_START) अणु

		/* हटाओ mixer controls */
		list_क्रम_each_entry_safe(करोbj, next_करोbj, &comp->करोbj_list,
			list) अणु

			चयन (करोbj->type) अणु
			हाल SND_SOC_DOBJ_MIXER:
				हटाओ_mixer(comp, करोbj, pass);
				अवरोध;
			हाल SND_SOC_DOBJ_ENUM:
				हटाओ_क्रमागत(comp, करोbj, pass);
				अवरोध;
			हाल SND_SOC_DOBJ_BYTES:
				हटाओ_bytes(comp, करोbj, pass);
				अवरोध;
			हाल SND_SOC_DOBJ_GRAPH:
				हटाओ_route(comp, करोbj, pass);
				अवरोध;
			हाल SND_SOC_DOBJ_WIDGET:
				हटाओ_widget(comp, करोbj, pass);
				अवरोध;
			हाल SND_SOC_DOBJ_PCM:
				हटाओ_dai(comp, करोbj, pass);
				अवरोध;
			हाल SND_SOC_DOBJ_DAI_LINK:
				हटाओ_link(comp, करोbj, pass);
				अवरोध;
			हाल SND_SOC_DOBJ_BACKEND_LINK:
				/*
				 * call link_unload ops अगर extra
				 * deinitialization is needed.
				 */
				हटाओ_backend_link(comp, करोbj, pass);
				अवरोध;
			शेष:
				dev_err(comp->dev, "ASoC: invalid component type %d for removal\n",
					करोbj->type);
				अवरोध;
			पूर्ण
		पूर्ण
		pass--;
	पूर्ण

	/* let caller know अगर FW can be मुक्तd when no objects are left */
	वापस !list_empty(&comp->करोbj_list);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_tplg_component_हटाओ);
