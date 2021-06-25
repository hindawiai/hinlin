<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  hdac_hdmi.c - ASoc HDA-HDMI codec driver क्रम Intel platक्रमms
 *
 *  Copyright (C) 2014-2015 Intel Corp
 *  Author: Samreen Nilofer <samreen.nilofer@पूर्णांकel.com>
 *	    Subhransu S. Prusty <subhransu.s.prusty@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/hdmi.h>
#समावेश <drm/drm_edid.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_i915.h>
#समावेश <sound/pcm_drm_eld.h>
#समावेश <sound/hda_chmap.h>
#समावेश "../../hda/local.h"
#समावेश "hdac_hdmi.h"

#घोषणा NAME_SIZE	32

#घोषणा AMP_OUT_MUTE		0xb080
#घोषणा AMP_OUT_UNMUTE		0xb000
#घोषणा PIN_OUT			(AC_PINCTL_OUT_EN)

#घोषणा HDA_MAX_CONNECTIONS     32

#घोषणा HDA_MAX_CVTS		3
#घोषणा HDA_MAX_PORTS		3

#घोषणा ELD_MAX_SIZE    256
#घोषणा ELD_FIXED_BYTES	20

#घोषणा ELD_VER_CEA_861D 2
#घोषणा ELD_VER_PARTIAL 31
#घोषणा ELD_MAX_MNL     16

काष्ठा hdac_hdmi_cvt_params अणु
	अचिन्हित पूर्णांक channels_min;
	अचिन्हित पूर्णांक channels_max;
	u32 rates;
	u64 क्रमmats;
	अचिन्हित पूर्णांक maxbps;
पूर्ण;

काष्ठा hdac_hdmi_cvt अणु
	काष्ठा list_head head;
	hda_nid_t nid;
	स्थिर अक्षर *name;
	काष्ठा hdac_hdmi_cvt_params params;
पूर्ण;

/* Currently only spk_alloc, more to be added */
काष्ठा hdac_hdmi_parsed_eld अणु
	u8 spk_alloc;
पूर्ण;

काष्ठा hdac_hdmi_eld अणु
	bool	monitor_present;
	bool	eld_valid;
	पूर्णांक	eld_size;
	अक्षर    eld_buffer[ELD_MAX_SIZE];
	काष्ठा	hdac_hdmi_parsed_eld info;
पूर्ण;

काष्ठा hdac_hdmi_pin अणु
	काष्ठा list_head head;
	hda_nid_t nid;
	bool mst_capable;
	काष्ठा hdac_hdmi_port *ports;
	पूर्णांक num_ports;
	काष्ठा hdac_device *hdev;
पूर्ण;

काष्ठा hdac_hdmi_port अणु
	काष्ठा list_head head;
	पूर्णांक id;
	काष्ठा hdac_hdmi_pin *pin;
	पूर्णांक num_mux_nids;
	hda_nid_t mux_nids[HDA_MAX_CONNECTIONS];
	काष्ठा hdac_hdmi_eld eld;
	स्थिर अक्षर *jack_pin;
	bool is_connect;
	काष्ठा snd_soc_dapm_context *dapm;
	स्थिर अक्षर *output_pin;
	काष्ठा work_काष्ठा dapm_work;
पूर्ण;

काष्ठा hdac_hdmi_pcm अणु
	काष्ठा list_head head;
	पूर्णांक pcm_id;
	काष्ठा list_head port_list;
	काष्ठा hdac_hdmi_cvt *cvt;
	काष्ठा snd_soc_jack *jack;
	पूर्णांक stream_tag;
	पूर्णांक channels;
	पूर्णांक क्रमmat;
	bool chmap_set;
	अचिन्हित अक्षर chmap[8]; /* ALSA API channel-map */
	काष्ठा mutex lock;
	पूर्णांक jack_event;
	काष्ठा snd_kcontrol *eld_ctl;
पूर्ण;

काष्ठा hdac_hdmi_dai_port_map अणु
	पूर्णांक dai_id;
	काष्ठा hdac_hdmi_port *port;
	काष्ठा hdac_hdmi_cvt *cvt;
पूर्ण;

काष्ठा hdac_hdmi_drv_data अणु
	अचिन्हित पूर्णांक venकरोr_nid;
पूर्ण;

काष्ठा hdac_hdmi_priv अणु
	काष्ठा hdac_device *hdev;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_card *card;
	काष्ठा hdac_hdmi_dai_port_map dai_map[HDA_MAX_CVTS];
	काष्ठा list_head pin_list;
	काष्ठा list_head cvt_list;
	काष्ठा list_head pcm_list;
	पूर्णांक num_pin;
	पूर्णांक num_cvt;
	पूर्णांक num_ports;
	काष्ठा mutex pin_mutex;
	काष्ठा hdac_chmap chmap;
	काष्ठा hdac_hdmi_drv_data *drv_data;
	काष्ठा snd_soc_dai_driver *dai_drv;
पूर्ण;

#घोषणा hdev_to_hdmi_priv(_hdev) dev_get_drvdata(&(_hdev)->dev)

अटल काष्ठा hdac_hdmi_pcm *
hdac_hdmi_get_pcm_from_cvt(काष्ठा hdac_hdmi_priv *hdmi,
			   काष्ठा hdac_hdmi_cvt *cvt)
अणु
	काष्ठा hdac_hdmi_pcm *pcm;

	list_क्रम_each_entry(pcm, &hdmi->pcm_list, head) अणु
		अगर (pcm->cvt == cvt)
			वापस pcm;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम hdac_hdmi_jack_report(काष्ठा hdac_hdmi_pcm *pcm,
		काष्ठा hdac_hdmi_port *port, bool is_connect)
अणु
	काष्ठा hdac_device *hdev = port->pin->hdev;

	port->is_connect = is_connect;
	अगर (is_connect) अणु
		/*
		 * Report Jack connect event when a device is connected
		 * क्रम the first समय where same PCM is attached to multiple
		 * ports.
		 */
		अगर (pcm->jack_event == 0) अणु
			dev_dbg(&hdev->dev,
					"jack report for pcm=%d\n",
					pcm->pcm_id);
			snd_soc_jack_report(pcm->jack, SND_JACK_AVOUT,
						SND_JACK_AVOUT);
		पूर्ण
		pcm->jack_event++;
	पूर्ण अन्यथा अणु
		/*
		 * Report Jack disconnect event when a device is disconnected
		 * is the only last connected device when same PCM is attached
		 * to multiple ports.
		 */
		अगर (pcm->jack_event == 1)
			snd_soc_jack_report(pcm->jack, 0, SND_JACK_AVOUT);
		अगर (pcm->jack_event > 0)
			pcm->jack_event--;
	पूर्ण
पूर्ण

अटल व्योम hdac_hdmi_port_dapm_update(काष्ठा hdac_hdmi_port *port)
अणु
	अगर (port->is_connect)
		snd_soc_dapm_enable_pin(port->dapm, port->jack_pin);
	अन्यथा
		snd_soc_dapm_disable_pin(port->dapm, port->jack_pin);
	snd_soc_dapm_sync(port->dapm);
पूर्ण

अटल व्योम hdac_hdmi_jack_dapm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdac_hdmi_port *port;

	port = container_of(work, काष्ठा hdac_hdmi_port, dapm_work);
	hdac_hdmi_port_dapm_update(port);
पूर्ण

अटल व्योम hdac_hdmi_jack_report_sync(काष्ठा hdac_hdmi_pcm *pcm,
		काष्ठा hdac_hdmi_port *port, bool is_connect)
अणु
	hdac_hdmi_jack_report(pcm, port, is_connect);
	hdac_hdmi_port_dapm_update(port);
पूर्ण

/* MST supported verbs */
/*
 * Get the no devices that can be connected to a port on the Pin widget.
 */
अटल पूर्णांक hdac_hdmi_get_port_len(काष्ठा hdac_device *hdev, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक caps;
	अचिन्हित पूर्णांक type, param;

	caps = get_wcaps(hdev, nid);
	type = get_wcaps_type(caps);

	अगर (!(caps & AC_WCAP_DIGITAL) || (type != AC_WID_PIN))
		वापस 0;

	param = snd_hdac_पढ़ो_parm_uncached(hdev, nid, AC_PAR_DEVLIST_LEN);
	अगर (param == -1)
		वापस param;

	वापस param & AC_DEV_LIST_LEN_MASK;
पूर्ण

/*
 * Get the port entry select on the pin. Return the port entry
 * id selected on the pin. Return 0 means the first port entry
 * is selected or MST is not supported.
 */
अटल पूर्णांक hdac_hdmi_port_select_get(काष्ठा hdac_device *hdev,
					काष्ठा hdac_hdmi_port *port)
अणु
	वापस snd_hdac_codec_पढ़ो(hdev, port->pin->nid,
				0, AC_VERB_GET_DEVICE_SEL, 0);
पूर्ण

/*
 * Sets the selected port entry क्रम the configuring Pin widget verb.
 * वापसs error अगर port set is not equal to port get otherwise success
 */
अटल पूर्णांक hdac_hdmi_port_select_set(काष्ठा hdac_device *hdev,
					काष्ठा hdac_hdmi_port *port)
अणु
	पूर्णांक num_ports;

	अगर (!port->pin->mst_capable)
		वापस 0;

	/* AC_PAR_DEVLIST_LEN is 0 based. */
	num_ports = hdac_hdmi_get_port_len(hdev, port->pin->nid);
	अगर (num_ports < 0)
		वापस -EIO;
	/*
	 * Device List Length is a 0 based पूर्णांकeger value indicating the
	 * number of sink device that a MST Pin Widget can support.
	 */
	अगर (num_ports + 1  < port->id)
		वापस 0;

	snd_hdac_codec_ग_लिखो(hdev, port->pin->nid, 0,
			AC_VERB_SET_DEVICE_SEL, port->id);

	अगर (port->id != hdac_hdmi_port_select_get(hdev, port))
		वापस -EIO;

	dev_dbg(&hdev->dev, "Selected the port=%d\n", port->id);

	वापस 0;
पूर्ण

अटल काष्ठा hdac_hdmi_pcm *get_hdmi_pcm_from_id(काष्ठा hdac_hdmi_priv *hdmi,
						पूर्णांक pcm_idx)
अणु
	काष्ठा hdac_hdmi_pcm *pcm;

	list_क्रम_each_entry(pcm, &hdmi->pcm_list, head) अणु
		अगर (pcm->pcm_id == pcm_idx)
			वापस pcm;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक sad_क्रमmat(स्थिर u8 *sad)
अणु
	वापस ((sad[0] >> 0x3) & 0x1f);
पूर्ण

अटल अचिन्हित पूर्णांक sad_sample_bits_lpcm(स्थिर u8 *sad)
अणु
	वापस (sad[2] & 7);
पूर्ण

अटल पूर्णांक hdac_hdmi_eld_limit_क्रमmats(काष्ठा snd_pcm_runसमय *runसमय,
						व्योम *eld)
अणु
	u64 क्रमmats = SNDRV_PCM_FMTBIT_S16;
	पूर्णांक i;
	स्थिर u8 *sad, *eld_buf = eld;

	sad = drm_eld_sad(eld_buf);
	अगर (!sad)
		जाओ क्रमmat_स्थिरraपूर्णांक;

	क्रम (i = drm_eld_sad_count(eld_buf); i > 0; i--, sad += 3) अणु
		अगर (sad_क्रमmat(sad) == 1) अणु /* AUDIO_CODING_TYPE_LPCM */

			/*
			 * the controller support 20 and 24 bits in 32 bit
			 * container so we set S32
			 */
			अगर (sad_sample_bits_lpcm(sad) & 0x6)
				क्रमmats |= SNDRV_PCM_FMTBIT_S32;
		पूर्ण
	पूर्ण

क्रमmat_स्थिरraपूर्णांक:
	वापस snd_pcm_hw_स्थिरraपूर्णांक_mask64(runसमय, SNDRV_PCM_HW_PARAM_FORMAT,
				क्रमmats);

पूर्ण

अटल व्योम
hdac_hdmi_set_dip_index(काष्ठा hdac_device *hdev, hda_nid_t pin_nid,
				पूर्णांक packet_index, पूर्णांक byte_index)
अणु
	पूर्णांक val;

	val = (packet_index << 5) | (byte_index & 0x1f);
	snd_hdac_codec_ग_लिखो(hdev, pin_nid, 0, AC_VERB_SET_HDMI_DIP_INDEX, val);
पूर्ण

काष्ठा dp_audio_infoframe अणु
	u8 type; /* 0x84 */
	u8 len;  /* 0x1b */
	u8 ver;  /* 0x11 << 2 */

	u8 CC02_CT47;	/* match with HDMI infoframe from this on */
	u8 SS01_SF24;
	u8 CXT04;
	u8 CA;
	u8 LFEPBL01_LSV36_DM_INH7;
पूर्ण;

अटल पूर्णांक hdac_hdmi_setup_audio_infoframe(काष्ठा hdac_device *hdev,
		   काष्ठा hdac_hdmi_pcm *pcm, काष्ठा hdac_hdmi_port *port)
अणु
	uपूर्णांक8_t buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AUDIO_INFOFRAME_SIZE];
	काष्ठा hdmi_audio_infoframe frame;
	काष्ठा hdac_hdmi_pin *pin = port->pin;
	काष्ठा dp_audio_infoframe dp_ai;
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_cvt *cvt = pcm->cvt;
	u8 *dip;
	पूर्णांक ret;
	पूर्णांक i;
	स्थिर u8 *eld_buf;
	u8 conn_type;
	पूर्णांक channels, ca;

	ca = snd_hdac_channel_allocation(hdev, port->eld.info.spk_alloc,
			pcm->channels, pcm->chmap_set, true, pcm->chmap);

	channels = snd_hdac_get_active_channels(ca);
	hdmi->chmap.ops.set_channel_count(hdev, cvt->nid, channels);

	snd_hdac_setup_channel_mapping(&hdmi->chmap, pin->nid, false, ca,
				pcm->channels, pcm->chmap, pcm->chmap_set);

	eld_buf = port->eld.eld_buffer;
	conn_type = drm_eld_get_conn_type(eld_buf);

	चयन (conn_type) अणु
	हाल DRM_ELD_CONN_TYPE_HDMI:
		hdmi_audio_infoframe_init(&frame);

		frame.channels = channels;
		frame.channel_allocation = ca;

		ret = hdmi_audio_infoframe_pack(&frame, buffer, माप(buffer));
		अगर (ret < 0)
			वापस ret;

		अवरोध;

	हाल DRM_ELD_CONN_TYPE_DP:
		स_रखो(&dp_ai, 0, माप(dp_ai));
		dp_ai.type	= 0x84;
		dp_ai.len	= 0x1b;
		dp_ai.ver	= 0x11 << 2;
		dp_ai.CC02_CT47	= channels - 1;
		dp_ai.CA	= ca;

		dip = (u8 *)&dp_ai;
		अवरोध;

	शेष:
		dev_err(&hdev->dev, "Invalid connection type: %d\n", conn_type);
		वापस -EIO;
	पूर्ण

	/* stop infoframe transmission */
	hdac_hdmi_set_dip_index(hdev, pin->nid, 0x0, 0x0);
	snd_hdac_codec_ग_लिखो(hdev, pin->nid, 0,
			AC_VERB_SET_HDMI_DIP_XMIT, AC_DIPXMIT_DISABLE);


	/*  Fill infoframe. Index स्वतः-incremented */
	hdac_hdmi_set_dip_index(hdev, pin->nid, 0x0, 0x0);
	अगर (conn_type == DRM_ELD_CONN_TYPE_HDMI) अणु
		क्रम (i = 0; i < माप(buffer); i++)
			snd_hdac_codec_ग_लिखो(hdev, pin->nid, 0,
				AC_VERB_SET_HDMI_DIP_DATA, buffer[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < माप(dp_ai); i++)
			snd_hdac_codec_ग_लिखो(hdev, pin->nid, 0,
				AC_VERB_SET_HDMI_DIP_DATA, dip[i]);
	पूर्ण

	/* Start infoframe */
	hdac_hdmi_set_dip_index(hdev, pin->nid, 0x0, 0x0);
	snd_hdac_codec_ग_लिखो(hdev, pin->nid, 0,
			AC_VERB_SET_HDMI_DIP_XMIT, AC_DIPXMIT_BEST);

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_set_tdm_slot(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
		पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_dai_get_drvdata(dai);
	काष्ठा hdac_device *hdev = hdmi->hdev;
	काष्ठा hdac_hdmi_dai_port_map *dai_map;
	काष्ठा hdac_hdmi_pcm *pcm;

	dev_dbg(&hdev->dev, "%s: strm_tag: %d\n", __func__, tx_mask);

	dai_map = &hdmi->dai_map[dai->id];

	pcm = hdac_hdmi_get_pcm_from_cvt(hdmi, dai_map->cvt);

	अगर (pcm)
		pcm->stream_tag = (tx_mask << 4);

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_set_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *hparams, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_dai_get_drvdata(dai);
	काष्ठा hdac_hdmi_dai_port_map *dai_map;
	काष्ठा hdac_hdmi_pcm *pcm;
	पूर्णांक क्रमmat;

	dai_map = &hdmi->dai_map[dai->id];

	क्रमmat = snd_hdac_calc_stream_क्रमmat(params_rate(hparams),
			params_channels(hparams), params_क्रमmat(hparams),
			dai->driver->playback.sig_bits, 0);

	pcm = hdac_hdmi_get_pcm_from_cvt(hdmi, dai_map->cvt);
	अगर (!pcm)
		वापस -EIO;

	pcm->क्रमmat = क्रमmat;
	pcm->channels = params_channels(hparams);

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_query_port_connlist(काष्ठा hdac_device *hdev,
					काष्ठा hdac_hdmi_pin *pin,
					काष्ठा hdac_hdmi_port *port)
अणु
	अगर (!(get_wcaps(hdev, pin->nid) & AC_WCAP_CONN_LIST)) अणु
		dev_warn(&hdev->dev,
			"HDMI: pin %d wcaps %#x does not support connection list\n",
			pin->nid, get_wcaps(hdev, pin->nid));
		वापस -EINVAL;
	पूर्ण

	अगर (hdac_hdmi_port_select_set(hdev, port) < 0)
		वापस -EIO;

	port->num_mux_nids = snd_hdac_get_connections(hdev, pin->nid,
			port->mux_nids, HDA_MAX_CONNECTIONS);
	अगर (port->num_mux_nids == 0)
		dev_warn(&hdev->dev,
			"No connections found for pin:port %d:%d\n",
						pin->nid, port->id);

	dev_dbg(&hdev->dev, "num_mux_nids %d for pin:port %d:%d\n",
			port->num_mux_nids, pin->nid, port->id);

	वापस port->num_mux_nids;
पूर्ण

/*
 * Query pcm list and वापस port to which stream is routed.
 *
 * Also query connection list of the pin, to validate the cvt to port map.
 *
 * Same stream rendering to multiple ports simultaneously can be करोne
 * possibly, but not supported क्रम now in driver. So वापस the first port
 * connected.
 */
अटल काष्ठा hdac_hdmi_port *hdac_hdmi_get_port_from_cvt(
			काष्ठा hdac_device *hdev,
			काष्ठा hdac_hdmi_priv *hdmi,
			काष्ठा hdac_hdmi_cvt *cvt)
अणु
	काष्ठा hdac_hdmi_pcm *pcm;
	काष्ठा hdac_hdmi_port *port;
	पूर्णांक ret, i;

	list_क्रम_each_entry(pcm, &hdmi->pcm_list, head) अणु
		अगर (pcm->cvt == cvt) अणु
			अगर (list_empty(&pcm->port_list))
				जारी;

			list_क्रम_each_entry(port, &pcm->port_list, head) अणु
				mutex_lock(&pcm->lock);
				ret = hdac_hdmi_query_port_connlist(hdev,
							port->pin, port);
				mutex_unlock(&pcm->lock);
				अगर (ret < 0)
					जारी;

				क्रम (i = 0; i < port->num_mux_nids; i++) अणु
					अगर (port->mux_nids[i] == cvt->nid &&
						port->eld.monitor_present &&
						port->eld.eld_valid)
						वापस port;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Go through all converters and ensure connection is set to
 * the correct pin as set via kcontrols.
 */
अटल व्योम hdac_hdmi_verअगरy_connect_sel_all_pins(काष्ठा hdac_device *hdev)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_port *port;
	काष्ठा hdac_hdmi_cvt *cvt;
	पूर्णांक cvt_idx = 0;

	list_क्रम_each_entry(cvt, &hdmi->cvt_list, head) अणु
		port = hdac_hdmi_get_port_from_cvt(hdev, hdmi, cvt);
		अगर (port && port->pin) अणु
			snd_hdac_codec_ग_लिखो(hdev, port->pin->nid, 0,
					     AC_VERB_SET_CONNECT_SEL, cvt_idx);
			dev_dbg(&hdev->dev, "%s: %s set connect %d -> %d\n",
				__func__, cvt->name, port->pin->nid, cvt_idx);
		पूर्ण
		++cvt_idx;
	पूर्ण
पूर्ण

/*
 * This tries to get a valid pin and set the HW स्थिरraपूर्णांकs based on the
 * ELD. Even अगर a valid pin is not found वापस success so that device खोलो
 * करोesn't fail.
 */
अटल पूर्णांक hdac_hdmi_pcm_खोलो(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_dai_get_drvdata(dai);
	काष्ठा hdac_device *hdev = hdmi->hdev;
	काष्ठा hdac_hdmi_dai_port_map *dai_map;
	काष्ठा hdac_hdmi_cvt *cvt;
	काष्ठा hdac_hdmi_port *port;
	पूर्णांक ret;

	dai_map = &hdmi->dai_map[dai->id];

	cvt = dai_map->cvt;
	port = hdac_hdmi_get_port_from_cvt(hdev, hdmi, cvt);

	/*
	 * To make PA and other userland happy.
	 * userland scans devices so वापसing error करोes not help.
	 */
	अगर (!port)
		वापस 0;
	अगर ((!port->eld.monitor_present) ||
			(!port->eld.eld_valid)) अणु

		dev_warn(&hdev->dev,
			"Failed: present?:%d ELD valid?:%d pin:port: %d:%d\n",
			port->eld.monitor_present, port->eld.eld_valid,
			port->pin->nid, port->id);

		वापस 0;
	पूर्ण

	dai_map->port = port;

	ret = hdac_hdmi_eld_limit_क्रमmats(substream->runसमय,
				port->eld.eld_buffer);
	अगर (ret < 0)
		वापस ret;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_eld(substream->runसमय,
				port->eld.eld_buffer);
पूर्ण

अटल व्योम hdac_hdmi_pcm_बंद(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_dai_get_drvdata(dai);
	काष्ठा hdac_hdmi_dai_port_map *dai_map;
	काष्ठा hdac_hdmi_pcm *pcm;

	dai_map = &hdmi->dai_map[dai->id];

	pcm = hdac_hdmi_get_pcm_from_cvt(hdmi, dai_map->cvt);

	अगर (pcm) अणु
		mutex_lock(&pcm->lock);
		pcm->chmap_set = false;
		स_रखो(pcm->chmap, 0, माप(pcm->chmap));
		pcm->channels = 0;
		mutex_unlock(&pcm->lock);
	पूर्ण

	अगर (dai_map->port)
		dai_map->port = शून्य;
पूर्ण

अटल पूर्णांक
hdac_hdmi_query_cvt_params(काष्ठा hdac_device *hdev, काष्ठा hdac_hdmi_cvt *cvt)
अणु
	अचिन्हित पूर्णांक chans;
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	पूर्णांक err;

	chans = get_wcaps(hdev, cvt->nid);
	chans = get_wcaps_channels(chans);

	cvt->params.channels_min = 2;

	cvt->params.channels_max = chans;
	अगर (chans > hdmi->chmap.channels_max)
		hdmi->chmap.channels_max = chans;

	err = snd_hdac_query_supported_pcm(hdev, cvt->nid,
			&cvt->params.rates,
			&cvt->params.क्रमmats,
			&cvt->params.maxbps);
	अगर (err < 0)
		dev_err(&hdev->dev,
			"Failed to query pcm params for nid %d: %d\n",
			cvt->nid, err);

	वापस err;
पूर्ण

अटल पूर्णांक hdac_hdmi_fill_widget_info(काष्ठा device *dev,
		काष्ठा snd_soc_dapm_widget *w, क्रमागत snd_soc_dapm_type id,
		व्योम *priv, स्थिर अक्षर *wname, स्थिर अक्षर *stream,
		काष्ठा snd_kcontrol_new *wc, पूर्णांक numkc,
		पूर्णांक (*event)(काष्ठा snd_soc_dapm_widget *,
		काष्ठा snd_kcontrol *, पूर्णांक), अचिन्हित लघु event_flags)
अणु
	w->id = id;
	w->name = devm_kstrdup(dev, wname, GFP_KERNEL);
	अगर (!w->name)
		वापस -ENOMEM;

	w->sname = stream;
	w->reg = SND_SOC_NOPM;
	w->shअगरt = 0;
	w->kcontrol_news = wc;
	w->num_kcontrols = numkc;
	w->priv = priv;
	w->event = event;
	w->event_flags = event_flags;

	वापस 0;
पूर्ण

अटल व्योम hdac_hdmi_fill_route(काष्ठा snd_soc_dapm_route *route,
		स्थिर अक्षर *sink, स्थिर अक्षर *control, स्थिर अक्षर *src,
		पूर्णांक (*handler)(काष्ठा snd_soc_dapm_widget *src,
			काष्ठा snd_soc_dapm_widget *sink))
अणु
	route->sink = sink;
	route->source = src;
	route->control = control;
	route->connected = handler;
पूर्ण

अटल काष्ठा hdac_hdmi_pcm *hdac_hdmi_get_pcm(काष्ठा hdac_device *hdev,
					काष्ठा hdac_hdmi_port *port)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pcm *pcm;
	काष्ठा hdac_hdmi_port *p;

	list_क्रम_each_entry(pcm, &hdmi->pcm_list, head) अणु
		अगर (list_empty(&pcm->port_list))
			जारी;

		list_क्रम_each_entry(p, &pcm->port_list, head) अणु
			अगर (p->id == port->id && port->pin == p->pin)
				वापस pcm;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम hdac_hdmi_set_घातer_state(काष्ठा hdac_device *hdev,
			     hda_nid_t nid, अचिन्हित पूर्णांक pwr_state)
अणु
	पूर्णांक count;
	अचिन्हित पूर्णांक state;

	अगर (get_wcaps(hdev, nid) & AC_WCAP_POWER) अणु
		अगर (!snd_hdac_check_घातer_state(hdev, nid, pwr_state)) अणु
			क्रम (count = 0; count < 10; count++) अणु
				snd_hdac_codec_पढ़ो(hdev, nid, 0,
						AC_VERB_SET_POWER_STATE,
						pwr_state);
				state = snd_hdac_sync_घातer_state(hdev,
						nid, pwr_state);
				अगर (!(state & AC_PWRST_ERROR))
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hdac_hdmi_set_amp(काष्ठा hdac_device *hdev,
				   hda_nid_t nid, पूर्णांक val)
अणु
	अगर (get_wcaps(hdev, nid) & AC_WCAP_OUT_AMP)
		snd_hdac_codec_ग_लिखो(hdev, nid, 0,
					AC_VERB_SET_AMP_GAIN_MUTE, val);
पूर्ण


अटल पूर्णांक hdac_hdmi_pin_output_widget_event(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा hdac_hdmi_port *port = w->priv;
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(w->dapm->dev);
	काष्ठा hdac_hdmi_pcm *pcm;

	dev_dbg(&hdev->dev, "%s: widget: %s event: %x\n",
			__func__, w->name, event);

	pcm = hdac_hdmi_get_pcm(hdev, port);
	अगर (!pcm)
		वापस -EIO;

	/* set the device अगर pin is mst_capable */
	अगर (hdac_hdmi_port_select_set(hdev, port) < 0)
		वापस -EIO;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		hdac_hdmi_set_घातer_state(hdev, port->pin->nid, AC_PWRST_D0);

		/* Enable out path क्रम this pin widget */
		snd_hdac_codec_ग_लिखो(hdev, port->pin->nid, 0,
				AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT);

		hdac_hdmi_set_amp(hdev, port->pin->nid, AMP_OUT_UNMUTE);

		वापस hdac_hdmi_setup_audio_infoframe(hdev, pcm, port);

	हाल SND_SOC_DAPM_POST_PMD:
		hdac_hdmi_set_amp(hdev, port->pin->nid, AMP_OUT_MUTE);

		/* Disable out path क्रम this pin widget */
		snd_hdac_codec_ग_लिखो(hdev, port->pin->nid, 0,
				AC_VERB_SET_PIN_WIDGET_CONTROL, 0);

		hdac_hdmi_set_घातer_state(hdev, port->pin->nid, AC_PWRST_D3);
		अवरोध;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_cvt_output_widget_event(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा hdac_hdmi_cvt *cvt = w->priv;
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(w->dapm->dev);
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pcm *pcm;

	dev_dbg(&hdev->dev, "%s: widget: %s event: %x\n",
			__func__, w->name, event);

	pcm = hdac_hdmi_get_pcm_from_cvt(hdmi, cvt);
	अगर (!pcm)
		वापस -EIO;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		hdac_hdmi_set_घातer_state(hdev, cvt->nid, AC_PWRST_D0);

		/* Enable transmission */
		snd_hdac_codec_ग_लिखो(hdev, cvt->nid, 0,
			AC_VERB_SET_DIGI_CONVERT_1, 1);

		/* Category Code (CC) to zero */
		snd_hdac_codec_ग_लिखो(hdev, cvt->nid, 0,
			AC_VERB_SET_DIGI_CONVERT_2, 0);

		snd_hdac_codec_ग_लिखो(hdev, cvt->nid, 0,
				AC_VERB_SET_CHANNEL_STREAMID, pcm->stream_tag);
		snd_hdac_codec_ग_लिखो(hdev, cvt->nid, 0,
				AC_VERB_SET_STREAM_FORMAT, pcm->क्रमmat);

		/*
		 * The connection indices are shared by all converters and
		 * may पूर्णांकerfere with each other. Ensure correct
		 * routing क्रम all converters at stream start.
		 */
		hdac_hdmi_verअगरy_connect_sel_all_pins(hdev);

		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_hdac_codec_ग_लिखो(hdev, cvt->nid, 0,
				AC_VERB_SET_CHANNEL_STREAMID, 0);
		snd_hdac_codec_ग_लिखो(hdev, cvt->nid, 0,
				AC_VERB_SET_STREAM_FORMAT, 0);

		hdac_hdmi_set_घातer_state(hdev, cvt->nid, AC_PWRST_D3);
		अवरोध;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_pin_mux_widget_event(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *kc, पूर्णांक event)
अणु
	काष्ठा hdac_hdmi_port *port = w->priv;
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(w->dapm->dev);
	पूर्णांक mux_idx;

	dev_dbg(&hdev->dev, "%s: widget: %s event: %x\n",
			__func__, w->name, event);

	अगर (!kc)
		kc  = w->kcontrols[0];

	mux_idx = dapm_kcontrol_get_value(kc);

	/* set the device अगर pin is mst_capable */
	अगर (hdac_hdmi_port_select_set(hdev, port) < 0)
		वापस -EIO;

	अगर (mux_idx > 0) अणु
		snd_hdac_codec_ग_लिखो(hdev, port->pin->nid, 0,
			AC_VERB_SET_CONNECT_SEL, (mux_idx - 1));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Based on user selection, map the PINs with the PCMs.
 */
अटल पूर्णांक hdac_hdmi_set_pin_port_mux(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret;
	काष्ठा hdac_hdmi_port *p, *p_next;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा hdac_hdmi_port *port = w->priv;
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(dapm->dev);
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pcm *pcm;
	स्थिर अक्षर *cvt_name =  e->texts[ucontrol->value.क्रमागतerated.item[0]];

	ret = snd_soc_dapm_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
	अगर (ret < 0)
		वापस ret;

	अगर (port == शून्य)
		वापस -EINVAL;

	mutex_lock(&hdmi->pin_mutex);
	list_क्रम_each_entry(pcm, &hdmi->pcm_list, head) अणु
		अगर (list_empty(&pcm->port_list))
			जारी;

		list_क्रम_each_entry_safe(p, p_next, &pcm->port_list, head) अणु
			अगर (p == port && p->id == port->id &&
					p->pin == port->pin) अणु
				hdac_hdmi_jack_report_sync(pcm, port, false);
				list_del(&p->head);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Jack status is not reported during device probe as the
	 * PCMs are not रेजिस्टरed by then. So report it here.
	 */
	list_क्रम_each_entry(pcm, &hdmi->pcm_list, head) अणु
		अगर (!म_भेद(cvt_name, pcm->cvt->name)) अणु
			list_add_tail(&port->head, &pcm->port_list);
			अगर (port->eld.monitor_present && port->eld.eld_valid) अणु
				hdac_hdmi_jack_report_sync(pcm, port, true);
				mutex_unlock(&hdmi->pin_mutex);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&hdmi->pin_mutex);

	वापस ret;
पूर्ण

/*
 * Ideally the Mux inमाला_दो should be based on the num_muxs क्रमागतerated, but
 * the display driver seem to be programming the connection list क्रम the pin
 * widget runसमय.
 *
 * So programming all the possible inमाला_दो क्रम the mux, the user has to take
 * care of selecting the right one and leaving all other inमाला_दो selected to
 * "NONE"
 */
अटल पूर्णांक hdac_hdmi_create_pin_port_muxs(काष्ठा hdac_device *hdev,
				काष्ठा hdac_hdmi_port *port,
				काष्ठा snd_soc_dapm_widget *widget,
				स्थिर अक्षर *widget_name)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pin *pin = port->pin;
	काष्ठा snd_kcontrol_new *kc;
	काष्ठा hdac_hdmi_cvt *cvt;
	काष्ठा soc_क्रमागत *se;
	अक्षर kc_name[NAME_SIZE];
	अक्षर mux_items[NAME_SIZE];
	/* To hold inमाला_दो to the Pin mux */
	अक्षर *items[HDA_MAX_CONNECTIONS];
	पूर्णांक i = 0;
	पूर्णांक num_items = hdmi->num_cvt + 1;

	kc = devm_kzalloc(&hdev->dev, माप(*kc), GFP_KERNEL);
	अगर (!kc)
		वापस -ENOMEM;

	se = devm_kzalloc(&hdev->dev, माप(*se), GFP_KERNEL);
	अगर (!se)
		वापस -ENOMEM;

	snम_लिखो(kc_name, NAME_SIZE, "Pin %d port %d Input",
						pin->nid, port->id);
	kc->name = devm_kstrdup(&hdev->dev, kc_name, GFP_KERNEL);
	अगर (!kc->name)
		वापस -ENOMEM;

	kc->निजी_value = (दीर्घ)se;
	kc->अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	kc->access = 0;
	kc->info = snd_soc_info_क्रमागत_द्विगुन;
	kc->put = hdac_hdmi_set_pin_port_mux;
	kc->get = snd_soc_dapm_get_क्रमागत_द्विगुन;

	se->reg = SND_SOC_NOPM;

	/* क्रमागत texts: ["NONE", "cvt #", "cvt #", ...] */
	se->items = num_items;
	se->mask = roundup_घात_of_two(se->items) - 1;

	प्र_लिखो(mux_items, "NONE");
	items[i] = devm_kstrdup(&hdev->dev, mux_items, GFP_KERNEL);
	अगर (!items[i])
		वापस -ENOMEM;

	list_क्रम_each_entry(cvt, &hdmi->cvt_list, head) अणु
		i++;
		प्र_लिखो(mux_items, "cvt %d", cvt->nid);
		items[i] = devm_kstrdup(&hdev->dev, mux_items, GFP_KERNEL);
		अगर (!items[i])
			वापस -ENOMEM;
	पूर्ण

	se->texts = devm_kmemdup(&hdev->dev, items,
			(num_items  * माप(अक्षर *)), GFP_KERNEL);
	अगर (!se->texts)
		वापस -ENOMEM;

	वापस hdac_hdmi_fill_widget_info(&hdev->dev, widget,
			snd_soc_dapm_mux, port, widget_name, शून्य, kc, 1,
			hdac_hdmi_pin_mux_widget_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_REG);
पूर्ण

/* Add cvt <- input <- mux route map */
अटल व्योम hdac_hdmi_add_pinmux_cvt_route(काष्ठा hdac_device *hdev,
			काष्ठा snd_soc_dapm_widget *widमाला_लो,
			काष्ठा snd_soc_dapm_route *route, पूर्णांक rindex)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	स्थिर काष्ठा snd_kcontrol_new *kc;
	काष्ठा soc_क्रमागत *se;
	पूर्णांक mux_index = hdmi->num_cvt + hdmi->num_ports;
	पूर्णांक i, j;

	क्रम (i = 0; i < hdmi->num_ports; i++) अणु
		kc = widमाला_लो[mux_index].kcontrol_news;
		se = (काष्ठा soc_क्रमागत *)kc->निजी_value;
		क्रम (j = 0; j < hdmi->num_cvt; j++) अणु
			hdac_hdmi_fill_route(&route[rindex],
					widमाला_लो[mux_index].name,
					se->texts[j + 1],
					widमाला_लो[j].name, शून्य);

			rindex++;
		पूर्ण

		mux_index++;
	पूर्ण
पूर्ण

/*
 * Widमाला_लो are added in the below sequence
 *	Converter widमाला_लो क्रम num converters क्रमागतerated
 *	Pin-port widमाला_लो क्रम num ports क्रम Pins क्रमागतerated
 *	Pin-port mux widमाला_लो to represent connenction list of pin widget
 *
 * For each port, one Mux and One output widget is added
 * Total widमाला_लो elements = num_cvt + (num_ports * 2);
 *
 * Routes are added as below:
 *	pin-port mux -> pin (based on num_ports)
 *	cvt -> "Input sel control" -> pin-port_mux
 *
 * Total route elements:
 *	num_ports + (pin_muxes * num_cvt)
 */
अटल पूर्णांक create_fill_widget_route_map(काष्ठा snd_soc_dapm_context *dapm)
अणु
	काष्ठा snd_soc_dapm_widget *widमाला_लो;
	काष्ठा snd_soc_dapm_route *route;
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(dapm->dev);
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा snd_soc_dai_driver *dai_drv = hdmi->dai_drv;
	अक्षर widget_name[NAME_SIZE];
	काष्ठा hdac_hdmi_cvt *cvt;
	काष्ठा hdac_hdmi_pin *pin;
	पूर्णांक ret, i = 0, num_routes = 0, j;

	अगर (list_empty(&hdmi->cvt_list) || list_empty(&hdmi->pin_list))
		वापस -EINVAL;

	widमाला_लो = devm_kzalloc(dapm->dev, (माप(*widमाला_लो) *
				((2 * hdmi->num_ports) + hdmi->num_cvt)),
				GFP_KERNEL);

	अगर (!widमाला_लो)
		वापस -ENOMEM;

	/* DAPM widमाला_लो to represent each converter widget */
	list_क्रम_each_entry(cvt, &hdmi->cvt_list, head) अणु
		प्र_लिखो(widget_name, "Converter %d", cvt->nid);
		ret = hdac_hdmi_fill_widget_info(dapm->dev, &widमाला_लो[i],
			snd_soc_dapm_aअगर_in, cvt,
			widget_name, dai_drv[i].playback.stream_name, शून्य, 0,
			hdac_hdmi_cvt_output_widget_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD);
		अगर (ret < 0)
			वापस ret;
		i++;
	पूर्ण

	list_क्रम_each_entry(pin, &hdmi->pin_list, head) अणु
		क्रम (j = 0; j < pin->num_ports; j++) अणु
			प्र_लिखो(widget_name, "hif%d-%d Output",
				pin->nid, pin->ports[j].id);
			ret = hdac_hdmi_fill_widget_info(dapm->dev, &widमाला_लो[i],
					snd_soc_dapm_output, &pin->ports[j],
					widget_name, शून्य, शून्य, 0,
					hdac_hdmi_pin_output_widget_event,
					SND_SOC_DAPM_PRE_PMU |
					SND_SOC_DAPM_POST_PMD);
			अगर (ret < 0)
				वापस ret;
			pin->ports[j].output_pin = widमाला_लो[i].name;
			i++;
		पूर्ण
	पूर्ण

	/* DAPM widमाला_लो to represent the connection list to pin widget */
	list_क्रम_each_entry(pin, &hdmi->pin_list, head) अणु
		क्रम (j = 0; j < pin->num_ports; j++) अणु
			प्र_लिखो(widget_name, "Pin%d-Port%d Mux",
				pin->nid, pin->ports[j].id);
			ret = hdac_hdmi_create_pin_port_muxs(hdev,
						&pin->ports[j], &widमाला_लो[i],
						widget_name);
			अगर (ret < 0)
				वापस ret;
			i++;

			/* For cvt to pin_mux mapping */
			num_routes += hdmi->num_cvt;

			/* For pin_mux to pin mapping */
			num_routes++;
		पूर्ण
	पूर्ण

	route = devm_kzalloc(dapm->dev, (माप(*route) * num_routes),
							GFP_KERNEL);
	अगर (!route)
		वापस -ENOMEM;

	i = 0;
	/* Add pin <- शून्य <- mux route map */
	list_क्रम_each_entry(pin, &hdmi->pin_list, head) अणु
		क्रम (j = 0; j < pin->num_ports; j++) अणु
			पूर्णांक sink_index = i + hdmi->num_cvt;
			पूर्णांक src_index = sink_index + pin->num_ports *
						hdmi->num_pin;

			hdac_hdmi_fill_route(&route[i],
				widमाला_लो[sink_index].name, शून्य,
				widमाला_लो[src_index].name, शून्य);
			i++;
		पूर्ण
	पूर्ण

	hdac_hdmi_add_pinmux_cvt_route(hdev, widमाला_लो, route, i);

	snd_soc_dapm_new_controls(dapm, widमाला_लो,
		((2 * hdmi->num_ports) + hdmi->num_cvt));

	snd_soc_dapm_add_routes(dapm, route, num_routes);
	snd_soc_dapm_new_widमाला_लो(dapm->card);

	वापस 0;

पूर्ण

अटल पूर्णांक hdac_hdmi_init_dai_map(काष्ठा hdac_device *hdev)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_dai_port_map *dai_map;
	काष्ठा hdac_hdmi_cvt *cvt;
	पूर्णांक dai_id = 0;

	अगर (list_empty(&hdmi->cvt_list))
		वापस -EINVAL;

	list_क्रम_each_entry(cvt, &hdmi->cvt_list, head) अणु
		dai_map = &hdmi->dai_map[dai_id];
		dai_map->dai_id = dai_id;
		dai_map->cvt = cvt;

		dai_id++;

		अगर (dai_id == HDA_MAX_CVTS) अणु
			dev_warn(&hdev->dev,
				"Max dais supported: %d\n", dai_id);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_add_cvt(काष्ठा hdac_device *hdev, hda_nid_t nid)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_cvt *cvt;
	अक्षर name[NAME_SIZE];

	cvt = devm_kzalloc(&hdev->dev, माप(*cvt), GFP_KERNEL);
	अगर (!cvt)
		वापस -ENOMEM;

	cvt->nid = nid;
	प्र_लिखो(name, "cvt %d", cvt->nid);
	cvt->name = devm_kstrdup(&hdev->dev, name, GFP_KERNEL);
	अगर (!cvt->name)
		वापस -ENOMEM;

	list_add_tail(&cvt->head, &hdmi->cvt_list);
	hdmi->num_cvt++;

	वापस hdac_hdmi_query_cvt_params(hdev, cvt);
पूर्ण

अटल पूर्णांक hdac_hdmi_parse_eld(काष्ठा hdac_device *hdev,
			काष्ठा hdac_hdmi_port *port)
अणु
	अचिन्हित पूर्णांक ver, mnl;

	ver = (port->eld.eld_buffer[DRM_ELD_VER] & DRM_ELD_VER_MASK)
						>> DRM_ELD_VER_SHIFT;

	अगर (ver != ELD_VER_CEA_861D && ver != ELD_VER_PARTIAL) अणु
		dev_err(&hdev->dev, "HDMI: Unknown ELD version %d\n", ver);
		वापस -EINVAL;
	पूर्ण

	mnl = (port->eld.eld_buffer[DRM_ELD_CEA_EDID_VER_MNL] &
		DRM_ELD_MNL_MASK) >> DRM_ELD_MNL_SHIFT;

	अगर (mnl > ELD_MAX_MNL) अणु
		dev_err(&hdev->dev, "HDMI: MNL Invalid %d\n", mnl);
		वापस -EINVAL;
	पूर्ण

	port->eld.info.spk_alloc = port->eld.eld_buffer[DRM_ELD_SPEAKER];

	वापस 0;
पूर्ण

अटल व्योम hdac_hdmi_present_sense(काष्ठा hdac_hdmi_pin *pin,
				    काष्ठा hdac_hdmi_port *port)
अणु
	काष्ठा hdac_device *hdev = pin->hdev;
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pcm *pcm;
	पूर्णांक size = 0;
	पूर्णांक port_id = -1;
	bool eld_valid, eld_changed;

	अगर (!hdmi)
		वापस;

	/*
	 * In हाल of non MST pin, get_eld info API expectes port
	 * to be -1.
	 */
	mutex_lock(&hdmi->pin_mutex);
	port->eld.monitor_present = false;

	अगर (pin->mst_capable)
		port_id = port->id;

	size = snd_hdac_acomp_get_eld(hdev, pin->nid, port_id,
				&port->eld.monitor_present,
				port->eld.eld_buffer,
				ELD_MAX_SIZE);

	अगर (size > 0) अणु
		size = min(size, ELD_MAX_SIZE);
		अगर (hdac_hdmi_parse_eld(hdev, port) < 0)
			size = -EINVAL;
	पूर्ण

	eld_valid = port->eld.eld_valid;

	अगर (size > 0) अणु
		port->eld.eld_valid = true;
		port->eld.eld_size = size;
	पूर्ण अन्यथा अणु
		port->eld.eld_valid = false;
		port->eld.eld_size = 0;
	पूर्ण

	eld_changed = (eld_valid != port->eld.eld_valid);

	pcm = hdac_hdmi_get_pcm(hdev, port);

	अगर (!port->eld.monitor_present || !port->eld.eld_valid) अणु

		dev_err(&hdev->dev, "%s: disconnect for pin:port %d:%d\n",
						__func__, pin->nid, port->id);

		/*
		 * PCMs are not रेजिस्टरed during device probe, so करोn't
		 * report jack here. It will be करोne in usermode mux
		 * control select.
		 */
		अगर (pcm) अणु
			hdac_hdmi_jack_report(pcm, port, false);
			schedule_work(&port->dapm_work);
		पूर्ण

		mutex_unlock(&hdmi->pin_mutex);
		वापस;
	पूर्ण

	अगर (port->eld.monitor_present && port->eld.eld_valid) अणु
		अगर (pcm) अणु
			hdac_hdmi_jack_report(pcm, port, true);
			schedule_work(&port->dapm_work);
		पूर्ण

		prपूर्णांक_hex_dump_debug("ELD: ", DUMP_PREFIX_OFFSET, 16, 1,
			  port->eld.eld_buffer, port->eld.eld_size, false);

	पूर्ण
	mutex_unlock(&hdmi->pin_mutex);

	अगर (eld_changed && pcm)
		snd_ctl_notअगरy(hdmi->card,
			       SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO,
			       &pcm->eld_ctl->id);
पूर्ण

अटल पूर्णांक hdac_hdmi_add_ports(काष्ठा hdac_device *hdev,
			       काष्ठा hdac_hdmi_pin *pin)
अणु
	काष्ठा hdac_hdmi_port *ports;
	पूर्णांक max_ports = HDA_MAX_PORTS;
	पूर्णांक i;

	/*
	 * FIXME: max_port may vary क्रम each platक्रमm, so pass this as
	 * as driver data or query from i915 पूर्णांकerface when this API is
	 * implemented.
	 */

	ports = devm_kसुस्मृति(&hdev->dev, max_ports, माप(*ports), GFP_KERNEL);
	अगर (!ports)
		वापस -ENOMEM;

	क्रम (i = 0; i < max_ports; i++) अणु
		ports[i].id = i;
		ports[i].pin = pin;
		INIT_WORK(&ports[i].dapm_work, hdac_hdmi_jack_dapm_work);
	पूर्ण
	pin->ports = ports;
	pin->num_ports = max_ports;
	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_add_pin(काष्ठा hdac_device *hdev, hda_nid_t nid)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pin *pin;
	पूर्णांक ret;

	pin = devm_kzalloc(&hdev->dev, माप(*pin), GFP_KERNEL);
	अगर (!pin)
		वापस -ENOMEM;

	pin->nid = nid;
	pin->mst_capable = false;
	pin->hdev = hdev;
	ret = hdac_hdmi_add_ports(hdev, pin);
	अगर (ret < 0)
		वापस ret;

	list_add_tail(&pin->head, &hdmi->pin_list);
	hdmi->num_pin++;
	hdmi->num_ports += pin->num_ports;

	वापस 0;
पूर्ण

#घोषणा INTEL_VENDOR_NID 0x08
#घोषणा INTEL_GLK_VENDOR_NID 0x0b
#घोषणा INTEL_GET_VENDOR_VERB 0xf81
#घोषणा INTEL_SET_VENDOR_VERB 0x781
#घोषणा INTEL_EN_DP12			0x02 /* enable DP 1.2 features */
#घोषणा INTEL_EN_ALL_PIN_CVTS	0x01 /* enable 2nd & 3rd pins and convertors */

अटल व्योम hdac_hdmi_skl_enable_all_pins(काष्ठा hdac_device *hdev)
अणु
	अचिन्हित पूर्णांक venकरोr_param;
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	अचिन्हित पूर्णांक venकरोr_nid = hdmi->drv_data->venकरोr_nid;

	venकरोr_param = snd_hdac_codec_पढ़ो(hdev, venकरोr_nid, 0,
				INTEL_GET_VENDOR_VERB, 0);
	अगर (venकरोr_param == -1 || venकरोr_param & INTEL_EN_ALL_PIN_CVTS)
		वापस;

	venकरोr_param |= INTEL_EN_ALL_PIN_CVTS;
	venकरोr_param = snd_hdac_codec_पढ़ो(hdev, venकरोr_nid, 0,
				INTEL_SET_VENDOR_VERB, venकरोr_param);
	अगर (venकरोr_param == -1)
		वापस;
पूर्ण

अटल व्योम hdac_hdmi_skl_enable_dp12(काष्ठा hdac_device *hdev)
अणु
	अचिन्हित पूर्णांक venकरोr_param;
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	अचिन्हित पूर्णांक venकरोr_nid = hdmi->drv_data->venकरोr_nid;

	venकरोr_param = snd_hdac_codec_पढ़ो(hdev, venकरोr_nid, 0,
				INTEL_GET_VENDOR_VERB, 0);
	अगर (venकरोr_param == -1 || venकरोr_param & INTEL_EN_DP12)
		वापस;

	/* enable DP1.2 mode */
	venकरोr_param |= INTEL_EN_DP12;
	venकरोr_param = snd_hdac_codec_पढ़ो(hdev, venकरोr_nid, 0,
				INTEL_SET_VENDOR_VERB, venकरोr_param);
	अगर (venकरोr_param == -1)
		वापस;

पूर्ण

अटल पूर्णांक hdac_hdmi_eld_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	काष्ठा hdac_hdmi_pcm *pcm;
	काष्ठा hdac_hdmi_port *port;
	काष्ठा hdac_hdmi_eld *eld;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = 0;

	pcm = get_hdmi_pcm_from_id(hdmi, kcontrol->id.device);
	अगर (!pcm) अणु
		dev_dbg(component->dev, "%s: no pcm, device %d\n", __func__,
			kcontrol->id.device);
		वापस 0;
	पूर्ण

	अगर (list_empty(&pcm->port_list)) अणु
		dev_dbg(component->dev, "%s: empty port list, device %d\n",
			__func__, kcontrol->id.device);
		वापस 0;
	पूर्ण

	mutex_lock(&hdmi->pin_mutex);

	list_क्रम_each_entry(port, &pcm->port_list, head) अणु
		eld = &port->eld;

		अगर (eld->eld_valid) अणु
			uinfo->count = eld->eld_size;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&hdmi->pin_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_eld_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	काष्ठा hdac_hdmi_pcm *pcm;
	काष्ठा hdac_hdmi_port *port;
	काष्ठा hdac_hdmi_eld *eld;

	स_रखो(ucontrol->value.bytes.data, 0, माप(ucontrol->value.bytes.data));

	pcm = get_hdmi_pcm_from_id(hdmi, kcontrol->id.device);
	अगर (!pcm) अणु
		dev_dbg(component->dev, "%s: no pcm, device %d\n", __func__,
			kcontrol->id.device);
		वापस 0;
	पूर्ण

	अगर (list_empty(&pcm->port_list)) अणु
		dev_dbg(component->dev, "%s: empty port list, device %d\n",
			__func__, kcontrol->id.device);
		वापस 0;
	पूर्ण

	mutex_lock(&hdmi->pin_mutex);

	list_क्रम_each_entry(port, &pcm->port_list, head) अणु
		eld = &port->eld;

		अगर (!eld->eld_valid)
			जारी;

		अगर (eld->eld_size > ARRAY_SIZE(ucontrol->value.bytes.data) ||
		    eld->eld_size > ELD_MAX_SIZE) अणु
			mutex_unlock(&hdmi->pin_mutex);

			dev_err(component->dev, "%s: buffer too small, device %d eld_size %d\n",
				__func__, kcontrol->id.device, eld->eld_size);
			snd_BUG();
			वापस -EINVAL;
		पूर्ण

		स_नकल(ucontrol->value.bytes.data, eld->eld_buffer,
		       eld->eld_size);
		अवरोध;
	पूर्ण

	mutex_unlock(&hdmi->pin_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_create_eld_ctl(काष्ठा snd_soc_component *component, काष्ठा hdac_hdmi_pcm *pcm)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_new hdmi_eld_ctl = अणु
		.access	= SNDRV_CTL_ELEM_ACCESS_READ |
			  SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.अगरace	= SNDRV_CTL_ELEM_IFACE_PCM,
		.name	= "ELD",
		.info	= hdac_hdmi_eld_ctl_info,
		.get	= hdac_hdmi_eld_ctl_get,
		.device	= pcm->pcm_id,
	पूर्ण;

	/* add ELD ctl with the device number corresponding to the PCM stream */
	kctl = snd_ctl_new1(&hdmi_eld_ctl, component);
	अगर (!kctl)
		वापस -ENOMEM;

	pcm->eld_ctl = kctl;

	वापस snd_ctl_add(component->card->snd_card, kctl);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops hdmi_dai_ops = अणु
	.startup = hdac_hdmi_pcm_खोलो,
	.shutकरोwn = hdac_hdmi_pcm_बंद,
	.hw_params = hdac_hdmi_set_hw_params,
	.set_tdm_slot = hdac_hdmi_set_tdm_slot,
पूर्ण;

/*
 * Each converter can support a stream independently. So a dai is created
 * based on the number of converter queried.
 */
अटल पूर्णांक hdac_hdmi_create_dais(काष्ठा hdac_device *hdev,
		काष्ठा snd_soc_dai_driver **dais,
		काष्ठा hdac_hdmi_priv *hdmi, पूर्णांक num_dais)
अणु
	काष्ठा snd_soc_dai_driver *hdmi_dais;
	काष्ठा hdac_hdmi_cvt *cvt;
	अक्षर name[NAME_SIZE], dai_name[NAME_SIZE];
	पूर्णांक i = 0;
	u32 rates, bps;
	अचिन्हित पूर्णांक rate_max = 384000, rate_min = 8000;
	u64 क्रमmats;
	पूर्णांक ret;

	hdmi_dais = devm_kzalloc(&hdev->dev,
			(माप(*hdmi_dais) * num_dais),
			GFP_KERNEL);
	अगर (!hdmi_dais)
		वापस -ENOMEM;

	list_क्रम_each_entry(cvt, &hdmi->cvt_list, head) अणु
		ret = snd_hdac_query_supported_pcm(hdev, cvt->nid,
					&rates,	&क्रमmats, &bps);
		अगर (ret)
			वापस ret;

		/* Filter out 44.1, 88.2 and 176.4Khz */
		rates &= ~(SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_88200 |
			   SNDRV_PCM_RATE_176400);
		अगर (!rates)
			वापस -EINVAL;

		प्र_लिखो(dai_name, "intel-hdmi-hifi%d", i+1);
		hdmi_dais[i].name = devm_kstrdup(&hdev->dev,
					dai_name, GFP_KERNEL);

		अगर (!hdmi_dais[i].name)
			वापस -ENOMEM;

		snम_लिखो(name, माप(name), "hifi%d", i+1);
		hdmi_dais[i].playback.stream_name =
				devm_kstrdup(&hdev->dev, name, GFP_KERNEL);
		अगर (!hdmi_dais[i].playback.stream_name)
			वापस -ENOMEM;

		/*
		 * Set caps based on capability queried from the converter.
		 * It will be स्थिरrained runसमय based on ELD queried.
		 */
		hdmi_dais[i].playback.क्रमmats = क्रमmats;
		hdmi_dais[i].playback.rates = rates;
		hdmi_dais[i].playback.rate_max = rate_max;
		hdmi_dais[i].playback.rate_min = rate_min;
		hdmi_dais[i].playback.channels_min = 2;
		hdmi_dais[i].playback.channels_max = 2;
		hdmi_dais[i].playback.sig_bits = bps;
		hdmi_dais[i].ops = &hdmi_dai_ops;
		i++;
	पूर्ण

	*dais = hdmi_dais;
	hdmi->dai_drv = hdmi_dais;

	वापस 0;
पूर्ण

/*
 * Parse all nodes and store the cvt/pin nids in array
 * Add one समय initialization क्रम pin and cvt widमाला_लो
 */
अटल पूर्णांक hdac_hdmi_parse_and_map_nid(काष्ठा hdac_device *hdev,
		काष्ठा snd_soc_dai_driver **dais, पूर्णांक *num_dais)
अणु
	hda_nid_t nid;
	पूर्णांक i, num_nodes;
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	पूर्णांक ret;

	hdac_hdmi_skl_enable_all_pins(hdev);
	hdac_hdmi_skl_enable_dp12(hdev);

	num_nodes = snd_hdac_get_sub_nodes(hdev, hdev->afg, &nid);
	अगर (!nid || num_nodes <= 0) अणु
		dev_warn(&hdev->dev, "HDMI: failed to get afg sub nodes\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_nodes; i++, nid++) अणु
		अचिन्हित पूर्णांक caps;
		अचिन्हित पूर्णांक type;

		caps = get_wcaps(hdev, nid);
		type = get_wcaps_type(caps);

		अगर (!(caps & AC_WCAP_DIGITAL))
			जारी;

		चयन (type) अणु

		हाल AC_WID_AUD_OUT:
			ret = hdac_hdmi_add_cvt(hdev, nid);
			अगर (ret < 0)
				वापस ret;
			अवरोध;

		हाल AC_WID_PIN:
			ret = hdac_hdmi_add_pin(hdev, nid);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!hdmi->num_pin || !hdmi->num_cvt) अणु
		ret = -EIO;
		dev_err(&hdev->dev, "Bad pin/cvt setup in %s\n", __func__);
		वापस ret;
	पूर्ण

	ret = hdac_hdmi_create_dais(hdev, dais, hdmi, hdmi->num_cvt);
	अगर (ret) अणु
		dev_err(&hdev->dev, "Failed to create dais with err: %d\n",
			ret);
		वापस ret;
	पूर्ण

	*num_dais = hdmi->num_cvt;
	ret = hdac_hdmi_init_dai_map(hdev);
	अगर (ret < 0)
		dev_err(&hdev->dev, "Failed to init DAI map with err: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hdac_hdmi_pin2port(व्योम *aptr, पूर्णांक pin)
अणु
	वापस pin - 4; /* map NID 0x05 -> port #1 */
पूर्ण

अटल व्योम hdac_hdmi_eld_notअगरy_cb(व्योम *aptr, पूर्णांक port, पूर्णांक pipe)
अणु
	काष्ठा hdac_device *hdev = aptr;
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pin *pin;
	काष्ठा hdac_hdmi_port *hport = शून्य;
	काष्ठा snd_soc_component *component = hdmi->component;
	पूर्णांक i;

	/* Don't know how this mapping is derived */
	hda_nid_t pin_nid = port + 0x04;

	dev_dbg(&hdev->dev, "%s: for pin:%d port=%d\n", __func__,
							pin_nid, pipe);

	/*
	 * skip notअगरication during प्रणाली suspend (but not in runसमय PM);
	 * the state will be updated at resume. Also since the ELD and
	 * connection states are updated in anyway at the end of the resume,
	 * we can skip it when received during PM process.
	 */
	अगर (snd_घातer_get_state(component->card->snd_card) !=
			SNDRV_CTL_POWER_D0)
		वापस;

	अगर (atomic_पढ़ो(&hdev->in_pm))
		वापस;

	list_क्रम_each_entry(pin, &hdmi->pin_list, head) अणु
		अगर (pin->nid != pin_nid)
			जारी;

		/* In हाल of non MST pin, pipe is -1 */
		अगर (pipe == -1) अणु
			pin->mst_capable = false;
			/* अगर not MST, शेष is port[0] */
			hport = &pin->ports[0];
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < pin->num_ports; i++) अणु
				pin->mst_capable = true;
				अगर (pin->ports[i].id == pipe) अणु
					hport = &pin->ports[i];
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (hport)
			hdac_hdmi_present_sense(pin, hport);
	पूर्ण

पूर्ण

अटल काष्ठा drm_audio_component_audio_ops aops = अणु
	.pin2port	= hdac_hdmi_pin2port,
	.pin_eld_notअगरy	= hdac_hdmi_eld_notअगरy_cb,
पूर्ण;

अटल काष्ठा snd_pcm *hdac_hdmi_get_pcm_from_id(काष्ठा snd_soc_card *card,
						पूर्णांक device)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;

	क्रम_each_card_rtds(card, rtd) अणु
		अगर (rtd->pcm && (rtd->pcm->device == device))
			वापस rtd->pcm;
	पूर्ण

	वापस शून्य;
पूर्ण

/* create jack pin kcontrols */
अटल पूर्णांक create_fill_jack_kcontrols(काष्ठा snd_soc_card *card,
				    काष्ठा hdac_device *hdev)
अणु
	काष्ठा hdac_hdmi_pin *pin;
	काष्ठा snd_kcontrol_new *kc;
	अक्षर kc_name[NAME_SIZE], xname[NAME_SIZE];
	अक्षर *name;
	पूर्णांक i = 0, j;
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा snd_soc_component *component = hdmi->component;

	kc = devm_kसुस्मृति(component->dev, hdmi->num_ports,
				माप(*kc), GFP_KERNEL);

	अगर (!kc)
		वापस -ENOMEM;

	list_क्रम_each_entry(pin, &hdmi->pin_list, head) अणु
		क्रम (j = 0; j < pin->num_ports; j++) अणु
			snम_लिखो(xname, माप(xname), "hif%d-%d Jack",
						pin->nid, pin->ports[j].id);
			name = devm_kstrdup(component->dev, xname, GFP_KERNEL);
			अगर (!name)
				वापस -ENOMEM;
			snम_लिखो(kc_name, माप(kc_name), "%s Switch", xname);
			kc[i].name = devm_kstrdup(component->dev, kc_name,
							GFP_KERNEL);
			अगर (!kc[i].name)
				वापस -ENOMEM;

			kc[i].निजी_value = (अचिन्हित दीर्घ)name;
			kc[i].अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
			kc[i].access = 0;
			kc[i].info = snd_soc_dapm_info_pin_चयन;
			kc[i].put = snd_soc_dapm_put_pin_चयन;
			kc[i].get = snd_soc_dapm_get_pin_चयन;
			i++;
		पूर्ण
	पूर्ण

	वापस snd_soc_add_card_controls(card, kc, i);
पूर्ण

पूर्णांक hdac_hdmi_jack_port_init(काष्ठा snd_soc_component *component,
			काष्ठा snd_soc_dapm_context *dapm)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	काष्ठा hdac_device *hdev = hdmi->hdev;
	काष्ठा hdac_hdmi_pin *pin;
	काष्ठा snd_soc_dapm_widget *widमाला_लो;
	काष्ठा snd_soc_dapm_route *route;
	अक्षर w_name[NAME_SIZE];
	पूर्णांक i = 0, j, ret;

	widमाला_लो = devm_kसुस्मृति(dapm->dev, hdmi->num_ports,
				माप(*widमाला_लो), GFP_KERNEL);

	अगर (!widमाला_लो)
		वापस -ENOMEM;

	route = devm_kसुस्मृति(dapm->dev, hdmi->num_ports,
				माप(*route), GFP_KERNEL);
	अगर (!route)
		वापस -ENOMEM;

	/* create Jack DAPM widget */
	list_क्रम_each_entry(pin, &hdmi->pin_list, head) अणु
		क्रम (j = 0; j < pin->num_ports; j++) अणु
			snम_लिखो(w_name, माप(w_name), "hif%d-%d Jack",
						pin->nid, pin->ports[j].id);

			ret = hdac_hdmi_fill_widget_info(dapm->dev, &widमाला_लो[i],
					snd_soc_dapm_spk, शून्य,
					w_name, शून्य, शून्य, 0, शून्य, 0);
			अगर (ret < 0)
				वापस ret;

			pin->ports[j].jack_pin = widमाला_लो[i].name;
			pin->ports[j].dapm = dapm;

			/* add to route from Jack widget to output */
			hdac_hdmi_fill_route(&route[i], pin->ports[j].jack_pin,
					शून्य, pin->ports[j].output_pin, शून्य);

			i++;
		पूर्ण
	पूर्ण

	/* Add Route from Jack widget to the output widget */
	ret = snd_soc_dapm_new_controls(dapm, widमाला_लो, hdmi->num_ports);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dapm_add_routes(dapm, route, hdmi->num_ports);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dapm_new_widमाला_लो(dapm->card);
	अगर (ret < 0)
		वापस ret;

	/* Add Jack Pin चयन Kcontrol */
	ret = create_fill_jack_kcontrols(dapm->card, hdev);

	अगर (ret < 0)
		वापस ret;

	/* शेष set the Jack Pin चयन to OFF */
	list_क्रम_each_entry(pin, &hdmi->pin_list, head) अणु
		क्रम (j = 0; j < pin->num_ports; j++)
			snd_soc_dapm_disable_pin(pin->ports[j].dapm,
						pin->ports[j].jack_pin);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hdac_hdmi_jack_port_init);

पूर्णांक hdac_hdmi_jack_init(काष्ठा snd_soc_dai *dai, पूर्णांक device,
				काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	काष्ठा hdac_device *hdev = hdmi->hdev;
	काष्ठा hdac_hdmi_pcm *pcm;
	काष्ठा snd_pcm *snd_pcm;
	पूर्णांक err;

	/*
	 * this is a new PCM device, create new pcm and
	 * add to the pcm list
	 */
	pcm = devm_kzalloc(&hdev->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;
	pcm->pcm_id = device;
	pcm->cvt = hdmi->dai_map[dai->id].cvt;
	pcm->jack_event = 0;
	pcm->jack = jack;
	mutex_init(&pcm->lock);
	INIT_LIST_HEAD(&pcm->port_list);
	snd_pcm = hdac_hdmi_get_pcm_from_id(dai->component->card, device);
	अगर (snd_pcm) अणु
		err = snd_hdac_add_chmap_ctls(snd_pcm, device, &hdmi->chmap);
		अगर (err < 0) अणु
			dev_err(&hdev->dev,
				"chmap control add failed with err: %d for pcm: %d\n",
				err, device);
			वापस err;
		पूर्ण
	पूर्ण

	/* add control क्रम ELD Bytes */
	err = hdac_hdmi_create_eld_ctl(component, pcm);
	अगर (err < 0) अणु
		dev_err(&hdev->dev,
			"eld control add failed with err: %d for pcm: %d\n",
			err, device);
		वापस err;
	पूर्ण

	list_add_tail(&pcm->head, &hdmi->pcm_list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hdac_hdmi_jack_init);

अटल व्योम hdac_hdmi_present_sense_all_pins(काष्ठा hdac_device *hdev,
			काष्ठा hdac_hdmi_priv *hdmi, bool detect_pin_caps)
अणु
	पूर्णांक i;
	काष्ठा hdac_hdmi_pin *pin;

	list_क्रम_each_entry(pin, &hdmi->pin_list, head) अणु
		अगर (detect_pin_caps) अणु

			अगर (hdac_hdmi_get_port_len(hdev, pin->nid)  == 0)
				pin->mst_capable = false;
			अन्यथा
				pin->mst_capable = true;
		पूर्ण

		क्रम (i = 0; i < pin->num_ports; i++) अणु
			अगर (!pin->mst_capable && i > 0)
				जारी;

			hdac_hdmi_present_sense(pin, &pin->ports[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hdmi_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	काष्ठा hdac_device *hdev = hdmi->hdev;
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा hdac_ext_link *hlink;
	पूर्णांक ret;

	hdmi->component = component;

	/*
	 * hold the ref जबतक we probe, also no need to drop the ref on
	 * निकास, we call pm_runसमय_suspend() so that will करो क्रम us
	 */
	hlink = snd_hdac_ext_bus_get_link(hdev->bus, dev_name(&hdev->dev));
	अगर (!hlink) अणु
		dev_err(&hdev->dev, "hdac link not found\n");
		वापस -EIO;
	पूर्ण

	snd_hdac_ext_bus_link_get(hdev->bus, hlink);

	ret = create_fill_widget_route_map(dapm);
	अगर (ret < 0)
		वापस ret;

	aops.audio_ptr = hdev;
	ret = snd_hdac_acomp_रेजिस्टर_notअगरier(hdev->bus, &aops);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "notifier register failed: err: %d\n", ret);
		वापस ret;
	पूर्ण

	hdac_hdmi_present_sense_all_pins(hdev, hdmi, true);
	/* Imp: Store the card poपूर्णांकer in hda_codec */
	hdmi->card = dapm->card->snd_card;

	/*
	 * Setup a device_link between card device and HDMI codec device.
	 * The card device is the consumer and the HDMI codec device is
	 * the supplier. With this setting, we can make sure that the audio
	 * करोमुख्य in display घातer will be always turned on beक्रमe operating
	 * on the HDMI audio codec रेजिस्टरs.
	 * Let's use the flag DL_FLAG_AUTOREMOVE_CONSUMER. This can make
	 * sure the device link is मुक्तd when the machine driver is हटाओd.
	 */
	device_link_add(component->card->dev, &hdev->dev, DL_FLAG_RPM_ACTIVE |
			DL_FLAG_AUTOREMOVE_CONSUMER);
	/*
	 * hdac_device core alपढ़ोy sets the state to active and calls
	 * get_noresume. So enable runसमय and set the device to suspend.
	 */
	pm_runसमय_enable(&hdev->dev);
	pm_runसमय_put(&hdev->dev);
	pm_runसमय_suspend(&hdev->dev);

	वापस 0;
पूर्ण

अटल व्योम hdmi_codec_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	काष्ठा hdac_device *hdev = hdmi->hdev;
	पूर्णांक ret;

	ret = snd_hdac_acomp_रेजिस्टर_notअगरier(hdev->bus, शून्य);
	अगर (ret < 0)
		dev_err(&hdev->dev, "notifier unregister failed: err: %d\n",
				ret);

	pm_runसमय_disable(&hdev->dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hdmi_codec_resume(काष्ठा device *dev)
अणु
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(dev);
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret < 0)
		वापस ret;
	/*
	 * As the ELD notअगरy callback request is not entertained जबतक the
	 * device is in suspend state. Need to manually check detection of
	 * all pins here. pin capablity change is not support, so use the
	 * alपढ़ोy set pin caps.
	 *
	 * NOTE: this is safe to call even अगर the codec करोesn't actually resume.
	 * The pin check involves only with DRM audio component hooks, so it
	 * works even अगर the HD-audio side is still dreaming peacefully.
	 */
	hdac_hdmi_present_sense_all_pins(hdev, hdmi, false);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा hdmi_codec_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver hdmi_hda_codec = अणु
	.probe			= hdmi_codec_probe,
	.हटाओ			= hdmi_codec_हटाओ,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल व्योम hdac_hdmi_get_chmap(काष्ठा hdac_device *hdev, पूर्णांक pcm_idx,
					अचिन्हित अक्षर *chmap)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pcm *pcm = get_hdmi_pcm_from_id(hdmi, pcm_idx);

	स_नकल(chmap, pcm->chmap, ARRAY_SIZE(pcm->chmap));
पूर्ण

अटल व्योम hdac_hdmi_set_chmap(काष्ठा hdac_device *hdev, पूर्णांक pcm_idx,
				अचिन्हित अक्षर *chmap, पूर्णांक prepared)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pcm *pcm = get_hdmi_pcm_from_id(hdmi, pcm_idx);
	काष्ठा hdac_hdmi_port *port;

	अगर (!pcm)
		वापस;

	अगर (list_empty(&pcm->port_list))
		वापस;

	mutex_lock(&pcm->lock);
	pcm->chmap_set = true;
	स_नकल(pcm->chmap, chmap, ARRAY_SIZE(pcm->chmap));
	list_क्रम_each_entry(port, &pcm->port_list, head)
		अगर (prepared)
			hdac_hdmi_setup_audio_infoframe(hdev, pcm, port);
	mutex_unlock(&pcm->lock);
पूर्ण

अटल bool is_hdac_hdmi_pcm_attached(काष्ठा hdac_device *hdev, पूर्णांक pcm_idx)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pcm *pcm = get_hdmi_pcm_from_id(hdmi, pcm_idx);

	अगर (!pcm)
		वापस false;

	अगर (list_empty(&pcm->port_list))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hdac_hdmi_get_spk_alloc(काष्ठा hdac_device *hdev, पूर्णांक pcm_idx)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pcm *pcm = get_hdmi_pcm_from_id(hdmi, pcm_idx);
	काष्ठा hdac_hdmi_port *port;

	अगर (!pcm)
		वापस 0;

	अगर (list_empty(&pcm->port_list))
		वापस 0;

	port = list_first_entry(&pcm->port_list, काष्ठा hdac_hdmi_port, head);

	अगर (!port || !port->eld.eld_valid)
		वापस 0;

	वापस port->eld.info.spk_alloc;
पूर्ण

अटल काष्ठा hdac_hdmi_drv_data पूर्णांकel_glk_drv_data  = अणु
	.venकरोr_nid = INTEL_GLK_VENDOR_NID,
पूर्ण;

अटल काष्ठा hdac_hdmi_drv_data पूर्णांकel_drv_data  = अणु
	.venकरोr_nid = INTEL_VENDOR_NID,
पूर्ण;

अटल पूर्णांक hdac_hdmi_dev_probe(काष्ठा hdac_device *hdev)
अणु
	काष्ठा hdac_hdmi_priv *hdmi_priv;
	काष्ठा snd_soc_dai_driver *hdmi_dais = शून्य;
	काष्ठा hdac_ext_link *hlink;
	पूर्णांक num_dais = 0;
	पूर्णांक ret;
	काष्ठा hdac_driver *hdrv = drv_to_hdac_driver(hdev->dev.driver);
	स्थिर काष्ठा hda_device_id *hdac_id = hdac_get_device_id(hdev, hdrv);

	/* hold the ref जबतक we probe */
	hlink = snd_hdac_ext_bus_get_link(hdev->bus, dev_name(&hdev->dev));
	अगर (!hlink) अणु
		dev_err(&hdev->dev, "hdac link not found\n");
		वापस -EIO;
	पूर्ण

	snd_hdac_ext_bus_link_get(hdev->bus, hlink);

	hdmi_priv = devm_kzalloc(&hdev->dev, माप(*hdmi_priv), GFP_KERNEL);
	अगर (hdmi_priv == शून्य)
		वापस -ENOMEM;

	snd_hdac_रेजिस्टर_chmap_ops(hdev, &hdmi_priv->chmap);
	hdmi_priv->chmap.ops.get_chmap = hdac_hdmi_get_chmap;
	hdmi_priv->chmap.ops.set_chmap = hdac_hdmi_set_chmap;
	hdmi_priv->chmap.ops.is_pcm_attached = is_hdac_hdmi_pcm_attached;
	hdmi_priv->chmap.ops.get_spk_alloc = hdac_hdmi_get_spk_alloc;
	hdmi_priv->hdev = hdev;

	अगर (!hdac_id)
		वापस -ENODEV;

	अगर (hdac_id->driver_data)
		hdmi_priv->drv_data =
			(काष्ठा hdac_hdmi_drv_data *)hdac_id->driver_data;
	अन्यथा
		hdmi_priv->drv_data = &पूर्णांकel_drv_data;

	dev_set_drvdata(&hdev->dev, hdmi_priv);

	INIT_LIST_HEAD(&hdmi_priv->pin_list);
	INIT_LIST_HEAD(&hdmi_priv->cvt_list);
	INIT_LIST_HEAD(&hdmi_priv->pcm_list);
	mutex_init(&hdmi_priv->pin_mutex);

	/*
	 * Turned off in the runसमय_suspend during the first explicit
	 * pm_runसमय_suspend call.
	 */
	snd_hdac_display_घातer(hdev->bus, hdev->addr, true);

	ret = hdac_hdmi_parse_and_map_nid(hdev, &hdmi_dais, &num_dais);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev,
			"Failed in parse and map nid with err: %d\n", ret);
		वापस ret;
	पूर्ण
	snd_hdac_refresh_widमाला_लो(hdev);

	/* ASoC specअगरic initialization */
	ret = devm_snd_soc_रेजिस्टर_component(&hdev->dev, &hdmi_hda_codec,
					hdmi_dais, num_dais);

	snd_hdac_ext_bus_link_put(hdev->bus, hlink);

	वापस ret;
पूर्ण

अटल व्योम clear_dapm_works(काष्ठा hdac_device *hdev)
अणु
	काष्ठा hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	काष्ठा hdac_hdmi_pin *pin;
	पूर्णांक i;

	list_क्रम_each_entry(pin, &hdmi->pin_list, head)
		क्रम (i = 0; i < pin->num_ports; i++)
			cancel_work_sync(&pin->ports[i].dapm_work);
पूर्ण

अटल पूर्णांक hdac_hdmi_dev_हटाओ(काष्ठा hdac_device *hdev)
अणु
	clear_dapm_works(hdev);
	snd_hdac_display_घातer(hdev->bus, hdev->addr, false);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक hdac_hdmi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(dev);
	काष्ठा hdac_bus *bus = hdev->bus;
	काष्ठा hdac_ext_link *hlink;

	dev_dbg(dev, "Enter: %s\n", __func__);

	/* controller may not have been initialized क्रम the first समय */
	अगर (!bus)
		वापस 0;

	/*
	 * Power करोwn afg.
	 * codec_पढ़ो is preferred over codec_ग_लिखो to set the घातer state.
	 * This way verb is send to set the घातer state and response
	 * is received. So setting घातer state is ensured without using loop
	 * to पढ़ो the state.
	 */
	snd_hdac_codec_पढ़ो(hdev, hdev->afg, 0,	AC_VERB_SET_POWER_STATE,
							AC_PWRST_D3);

	hlink = snd_hdac_ext_bus_get_link(bus, dev_name(dev));
	अगर (!hlink) अणु
		dev_err(dev, "hdac link not found\n");
		वापस -EIO;
	पूर्ण

	snd_hdac_codec_link_करोwn(hdev);
	snd_hdac_ext_bus_link_put(bus, hlink);

	snd_hdac_display_घातer(bus, hdev->addr, false);

	वापस 0;
पूर्ण

अटल पूर्णांक hdac_hdmi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(dev);
	काष्ठा hdac_bus *bus = hdev->bus;
	काष्ठा hdac_ext_link *hlink;

	dev_dbg(dev, "Enter: %s\n", __func__);

	/* controller may not have been initialized क्रम the first समय */
	अगर (!bus)
		वापस 0;

	hlink = snd_hdac_ext_bus_get_link(bus, dev_name(dev));
	अगर (!hlink) अणु
		dev_err(dev, "hdac link not found\n");
		वापस -EIO;
	पूर्ण

	snd_hdac_ext_bus_link_get(bus, hlink);
	snd_hdac_codec_link_up(hdev);

	snd_hdac_display_घातer(bus, hdev->addr, true);

	hdac_hdmi_skl_enable_all_pins(hdev);
	hdac_hdmi_skl_enable_dp12(hdev);

	/* Power up afg */
	snd_hdac_codec_पढ़ो(hdev, hdev->afg, 0,	AC_VERB_SET_POWER_STATE,
							AC_PWRST_D0);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा hdac_hdmi_runसमय_suspend शून्य
#घोषणा hdac_hdmi_runसमय_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops hdac_hdmi_pm = अणु
	SET_RUNTIME_PM_OPS(hdac_hdmi_runसमय_suspend, hdac_hdmi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, hdmi_codec_resume)
पूर्ण;

अटल स्थिर काष्ठा hda_device_id hdmi_list[] = अणु
	HDA_CODEC_EXT_ENTRY(0x80862809, 0x100000, "Skylake HDMI", 0),
	HDA_CODEC_EXT_ENTRY(0x8086280a, 0x100000, "Broxton HDMI", 0),
	HDA_CODEC_EXT_ENTRY(0x8086280b, 0x100000, "Kabylake HDMI", 0),
	HDA_CODEC_EXT_ENTRY(0x8086280c, 0x100000, "Cannonlake HDMI",
						   &पूर्णांकel_glk_drv_data),
	HDA_CODEC_EXT_ENTRY(0x8086280d, 0x100000, "Geminilake HDMI",
						   &पूर्णांकel_glk_drv_data),
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hdaudio, hdmi_list);

अटल काष्ठा hdac_driver hdmi_driver = अणु
	.driver = अणु
		.name   = "HDMI HDA Codec",
		.pm = &hdac_hdmi_pm,
	पूर्ण,
	.id_table       = hdmi_list,
	.probe          = hdac_hdmi_dev_probe,
	.हटाओ         = hdac_hdmi_dev_हटाओ,
पूर्ण;

अटल पूर्णांक __init hdmi_init(व्योम)
अणु
	वापस snd_hda_ext_driver_रेजिस्टर(&hdmi_driver);
पूर्ण

अटल व्योम __निकास hdmi_निकास(व्योम)
अणु
	snd_hda_ext_driver_unरेजिस्टर(&hdmi_driver);
पूर्ण

module_init(hdmi_init);
module_निकास(hdmi_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HDMI HD codec");
MODULE_AUTHOR("Samreen Nilofer<samreen.nilofer@intel.com>");
MODULE_AUTHOR("Subhransu S. Prusty<subhransu.s.prusty@intel.com>");
