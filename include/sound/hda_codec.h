<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 *
 * Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SOUND_HDA_CODEC_H
#घोषणा __SOUND_HDA_CODEC_H

#समावेश <linux/kref.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_verbs.h>
#समावेश <sound/hda_regmap.h>

#घोषणा IS_BXT(pci) ((pci)->venकरोr == 0x8086 && (pci)->device == 0x5a98)
#घोषणा IS_CFL(pci) ((pci)->venकरोr == 0x8086 && (pci)->device == 0xa348)

/*
 * Structures
 */

काष्ठा hda_bus;
काष्ठा hda_beep;
काष्ठा hda_codec;
काष्ठा hda_pcm;
काष्ठा hda_pcm_stream;

/*
 * codec bus
 *
 * each controller needs to creata a hda_bus to assign the accessor.
 * A hda_bus contains several codecs in the list codec_list.
 */
काष्ठा hda_bus अणु
	काष्ठा hdac_bus core;

	काष्ठा snd_card *card;

	काष्ठा pci_dev *pci;
	स्थिर अक्षर *modelname;

	काष्ठा mutex prepare_mutex;

	/* asचिन्हित PCMs */
	DECLARE_BITMAP(pcm_dev_bits, SNDRV_PCM_DEVICES);

	/* misc op flags */
	अचिन्हित पूर्णांक allow_bus_reset:1;	/* allow bus reset at fatal error */
	/* status क्रम codec/controller */
	अचिन्हित पूर्णांक shutकरोwn :1;	/* being unloaded */
	अचिन्हित पूर्णांक response_reset:1;	/* controller was reset */
	अचिन्हित पूर्णांक in_reset:1;	/* during reset operation */
	अचिन्हित पूर्णांक no_response_fallback:1; /* करोn't fallback at RIRB error */
	अचिन्हित पूर्णांक bus_probing :1;	/* during probing process */
	अचिन्हित पूर्णांक keep_घातer:1;	/* keep घातer up क्रम notअगरication */

	पूर्णांक primary_dig_out_type;	/* primary digital out PCM type */
	अचिन्हित पूर्णांक mixer_asचिन्हित;	/* codec addr क्रम mixer name */
पूर्ण;

/* from hdac_bus to hda_bus */
#घोषणा to_hda_bus(bus)		container_of(bus, काष्ठा hda_bus, core)

/*
 * codec preset
 *
 * Known codecs have the patch to build and set up the controls/PCMs
 * better than the generic parser.
 */
प्रकार पूर्णांक (*hda_codec_patch_t)(काष्ठा hda_codec *);
	
#घोषणा HDA_CODEC_ID_SKIP_PROBE		0x00000001
#घोषणा HDA_CODEC_ID_GENERIC_HDMI	0x00000101
#घोषणा HDA_CODEC_ID_GENERIC		0x00000201

#घोषणा HDA_CODEC_REV_ENTRY(_vid, _rev, _name, _patch) \
	अणु .venकरोr_id = (_vid), .rev_id = (_rev), .name = (_name), \
	  .api_version = HDA_DEV_LEGACY, \
	  .driver_data = (अचिन्हित दीर्घ)(_patch) पूर्ण
#घोषणा HDA_CODEC_ENTRY(_vid, _name, _patch) \
	HDA_CODEC_REV_ENTRY(_vid, 0, _name, _patch)

काष्ठा hda_codec_driver अणु
	काष्ठा hdac_driver core;
	स्थिर काष्ठा hda_device_id *id;
पूर्ण;

पूर्णांक __hda_codec_driver_रेजिस्टर(काष्ठा hda_codec_driver *drv, स्थिर अक्षर *name,
			       काष्ठा module *owner);
#घोषणा hda_codec_driver_रेजिस्टर(drv) \
	__hda_codec_driver_रेजिस्टर(drv, KBUILD_MODNAME, THIS_MODULE)
व्योम hda_codec_driver_unरेजिस्टर(काष्ठा hda_codec_driver *drv);
#घोषणा module_hda_codec_driver(drv) \
	module_driver(drv, hda_codec_driver_रेजिस्टर, \
		      hda_codec_driver_unरेजिस्टर)

/* ops set by the preset patch */
काष्ठा hda_codec_ops अणु
	पूर्णांक (*build_controls)(काष्ठा hda_codec *codec);
	पूर्णांक (*build_pcms)(काष्ठा hda_codec *codec);
	पूर्णांक (*init)(काष्ठा hda_codec *codec);
	व्योम (*मुक्त)(काष्ठा hda_codec *codec);
	व्योम (*unsol_event)(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक res);
	व्योम (*set_घातer_state)(काष्ठा hda_codec *codec, hda_nid_t fg,
				अचिन्हित पूर्णांक घातer_state);
#अगर_घोषित CONFIG_PM
	पूर्णांक (*suspend)(काष्ठा hda_codec *codec);
	पूर्णांक (*resume)(काष्ठा hda_codec *codec);
	पूर्णांक (*check_घातer_status)(काष्ठा hda_codec *codec, hda_nid_t nid);
#पूर्ण_अगर
	व्योम (*reboot_notअगरy)(काष्ठा hda_codec *codec);
	व्योम (*stream_pm)(काष्ठा hda_codec *codec, hda_nid_t nid, bool on);
पूर्ण;

/* PCM callbacks */
काष्ठा hda_pcm_ops अणु
	पूर्णांक (*खोलो)(काष्ठा hda_pcm_stream *info, काष्ठा hda_codec *codec,
		    काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*बंद)(काष्ठा hda_pcm_stream *info, काष्ठा hda_codec *codec,
		     काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*prepare)(काष्ठा hda_pcm_stream *info, काष्ठा hda_codec *codec,
		       अचिन्हित पूर्णांक stream_tag, अचिन्हित पूर्णांक क्रमmat,
		       काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*cleanup)(काष्ठा hda_pcm_stream *info, काष्ठा hda_codec *codec,
		       काष्ठा snd_pcm_substream *substream);
	अचिन्हित पूर्णांक (*get_delay)(काष्ठा hda_pcm_stream *info,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream);
पूर्ण;

/* PCM inक्रमmation क्रम each substream */
काष्ठा hda_pcm_stream अणु
	अचिन्हित पूर्णांक substreams;	/* number of substreams, 0 = not exist*/
	अचिन्हित पूर्णांक channels_min;	/* min. number of channels */
	अचिन्हित पूर्णांक channels_max;	/* max. number of channels */
	hda_nid_t nid;	/* शेष NID to query rates/क्रमmats/bps, or set up */
	u32 rates;	/* supported rates */
	u64 क्रमmats;	/* supported क्रमmats (SNDRV_PCM_FMTBIT_) */
	अचिन्हित पूर्णांक maxbps;	/* supported max. bit per sample */
	स्थिर काष्ठा snd_pcm_chmap_elem *chmap; /* chmap to override */
	काष्ठा hda_pcm_ops ops;
पूर्ण;

/* PCM types */
क्रमागत अणु
	HDA_PCM_TYPE_AUDIO,
	HDA_PCM_TYPE_SPDIF,
	HDA_PCM_TYPE_HDMI,
	HDA_PCM_TYPE_MODEM,
	HDA_PCM_NTYPES
पूर्ण;

#घोषणा SNDRV_PCM_INVALID_DEVICE	(-1)
/* क्रम PCM creation */
काष्ठा hda_pcm अणु
	अक्षर *name;
	काष्ठा hda_pcm_stream stream[2];
	अचिन्हित पूर्णांक pcm_type;	/* HDA_PCM_TYPE_XXX */
	पूर्णांक device;		/* device number to assign */
	काष्ठा snd_pcm *pcm;	/* asचिन्हित PCM instance */
	bool own_chmap;		/* codec driver provides own channel maps */
	/* निजी: */
	काष्ठा hda_codec *codec;
	काष्ठा kref kref;
	काष्ठा list_head list;
पूर्ण;

/* codec inक्रमmation */
काष्ठा hda_codec अणु
	काष्ठा hdac_device core;
	काष्ठा hda_bus *bus;
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक addr;	/* codec addr*/
	u32 probe_id; /* overridden id क्रम probing */

	/* detected preset */
	स्थिर काष्ठा hda_device_id *preset;
	स्थिर अक्षर *modelname;	/* model name क्रम preset */

	/* set by patch */
	काष्ठा hda_codec_ops patch_ops;

	/* PCM to create, set by patch_ops.build_pcms callback */
	काष्ठा list_head pcm_list_head;

	/* codec specअगरic info */
	व्योम *spec;

	/* beep device */
	काष्ठा hda_beep *beep;
	अचिन्हित पूर्णांक beep_mode;

	/* widget capabilities cache */
	u32 *wcaps;

	काष्ठा snd_array mixers;	/* list of asचिन्हित mixer elements */
	काष्ठा snd_array nids;		/* list of mapped mixer elements */

	काष्ठा list_head conn_list;	/* linked-list of connection-list */

	काष्ठा mutex spdअगर_mutex;
	काष्ठा mutex control_mutex;
	काष्ठा snd_array spdअगर_out;
	अचिन्हित पूर्णांक spdअगर_in_enable;	/* SPDIF input enable? */
	स्थिर hda_nid_t *follower_dig_outs; /* optional digital out follower widमाला_लो */
	काष्ठा snd_array init_pins;	/* initial (BIOS) pin configurations */
	काष्ठा snd_array driver_pins;	/* pin configs set by codec parser */
	काष्ठा snd_array cvt_setups;	/* audio convert setups */

	काष्ठा mutex user_mutex;
#अगर_घोषित CONFIG_SND_HDA_RECONFIG
	काष्ठा snd_array init_verbs;	/* additional init verbs */
	काष्ठा snd_array hपूर्णांकs;		/* additional hपूर्णांकs */
	काष्ठा snd_array user_pins;	/* शेष pin configs to override */
#पूर्ण_अगर

#अगर_घोषित CONFIG_SND_HDA_HWDEP
	काष्ठा snd_hwdep *hwdep;	/* asचिन्हित hwdep device */
#पूर्ण_अगर

	/* misc flags */
	अचिन्हित पूर्णांक in_मुक्तing:1; /* being released */
	अचिन्हित पूर्णांक रेजिस्टरed:1; /* codec was रेजिस्टरed */
	अचिन्हित पूर्णांक display_घातer_control:1; /* needs display घातer */
	अचिन्हित पूर्णांक spdअगर_status_reset :1; /* needs to toggle SPDIF क्रम each
					     * status change
					     * (e.g. Realtek codecs)
					     */
	अचिन्हित पूर्णांक pin_amp_workaround:1; /* pin out-amp takes index
					    * (e.g. Conexant codecs)
					    */
	अचिन्हित पूर्णांक single_adc_amp:1; /* adc in-amp takes no index
					* (e.g. CX20549 codec)
					*/
	अचिन्हित पूर्णांक no_sticky_stream:1; /* no sticky-PCM stream assignment */
	अचिन्हित पूर्णांक pins_shutup:1;	/* pins are shut up */
	अचिन्हित पूर्णांक no_trigger_sense:1; /* करोn't trigger at pin-sensing */
	अचिन्हित पूर्णांक no_jack_detect:1;	/* Machine has no jack-detection */
	अचिन्हित पूर्णांक inv_eapd:1; /* broken h/w: inverted EAPD control */
	अचिन्हित पूर्णांक inv_jack_detect:1;	/* broken h/w: inverted detection bit */
	अचिन्हित पूर्णांक pcm_क्रमmat_first:1; /* PCM क्रमmat must be set first */
	अचिन्हित पूर्णांक cached_ग_लिखो:1;	/* ग_लिखो only to caches */
	अचिन्हित पूर्णांक dp_mst:1; /* support DP1.2 Multi-stream transport */
	अचिन्हित पूर्णांक dump_coef:1; /* dump processing coefs in codec proc file */
	अचिन्हित पूर्णांक घातer_save_node:1; /* advanced PM क्रम each widget */
	अचिन्हित पूर्णांक स्वतः_runसमय_pm:1; /* enable स्वतःmatic codec runसमय pm */
	अचिन्हित पूर्णांक क्रमce_pin_prefix:1; /* Add location prefix */
	अचिन्हित पूर्णांक link_करोwn_at_suspend:1; /* link करोwn at runसमय suspend */
	अचिन्हित पूर्णांक relaxed_resume:1;	/* करोn't resume क्रमcibly क्रम jack */
	अचिन्हित पूर्णांक क्रमced_resume:1; /* क्रमced resume क्रम jack */
	अचिन्हित पूर्णांक mst_no_extra_pcms:1; /* no backup PCMs क्रम DP-MST */

#अगर_घोषित CONFIG_PM
	अचिन्हित दीर्घ घातer_on_acct;
	अचिन्हित दीर्घ घातer_off_acct;
	अचिन्हित दीर्घ घातer_jअगरfies;
#पूर्ण_अगर

	/* filter the requested घातer state per nid */
	अचिन्हित पूर्णांक (*घातer_filter)(काष्ठा hda_codec *codec, hda_nid_t nid,
				     अचिन्हित पूर्णांक घातer_state);

	/* codec-specअगरic additional proc output */
	व्योम (*proc_widget_hook)(काष्ठा snd_info_buffer *buffer,
				 काष्ठा hda_codec *codec, hda_nid_t nid);

	/* jack detection */
	काष्ठा snd_array jacktbl;
	अचिन्हित दीर्घ jackpoll_पूर्णांकerval; /* In jअगरfies. Zero means no poll, rely on unsol events */
	काष्ठा delayed_work jackpoll_work;

	पूर्णांक depop_delay; /* depop delay in ms, -1 क्रम शेष delay समय */

	/* fix-up list */
	पूर्णांक fixup_id;
	स्थिर काष्ठा hda_fixup *fixup_list;
	स्थिर अक्षर *fixup_name;

	/* additional init verbs */
	काष्ठा snd_array verbs;
पूर्ण;

#घोषणा dev_to_hda_codec(_dev)	container_of(_dev, काष्ठा hda_codec, core.dev)
#घोषणा hda_codec_dev(_dev)	(&(_dev)->core.dev)

#घोषणा hdac_to_hda_priv(_hdac) \
			container_of(_hdac, काष्ठा hdac_hda_priv, codec.core)
#घोषणा hdac_to_hda_codec(_hdac) container_of(_hdac, काष्ठा hda_codec, core)

#घोषणा list_क्रम_each_codec(c, bus) \
	list_क्रम_each_entry(c, &(bus)->core.codec_list, core.list)
#घोषणा list_क्रम_each_codec_safe(c, n, bus)				\
	list_क्रम_each_entry_safe(c, n, &(bus)->core.codec_list, core.list)

/* snd_hda_codec_पढ़ो/ग_लिखो optional flags */
#घोषणा HDA_RW_NO_RESPONSE_FALLBACK	(1 << 0)

/*
 * स्थिरructors
 */
पूर्णांक snd_hda_codec_new(काष्ठा hda_bus *bus, काष्ठा snd_card *card,
		      अचिन्हित पूर्णांक codec_addr, काष्ठा hda_codec **codecp);
पूर्णांक snd_hda_codec_device_new(काष्ठा hda_bus *bus, काष्ठा snd_card *card,
		      अचिन्हित पूर्णांक codec_addr, काष्ठा hda_codec *codec);
पूर्णांक snd_hda_codec_configure(काष्ठा hda_codec *codec);
पूर्णांक snd_hda_codec_update_widमाला_लो(काष्ठा hda_codec *codec);

/*
 * low level functions
 */
अटल अंतरभूत अचिन्हित पूर्णांक
snd_hda_codec_पढ़ो(काष्ठा hda_codec *codec, hda_nid_t nid,
				पूर्णांक flags,
				अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm)
अणु
	वापस snd_hdac_codec_पढ़ो(&codec->core, nid, flags, verb, parm);
पूर्ण

अटल अंतरभूत पूर्णांक
snd_hda_codec_ग_लिखो(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक flags,
			अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm)
अणु
	वापस snd_hdac_codec_ग_लिखो(&codec->core, nid, flags, verb, parm);
पूर्ण

#घोषणा snd_hda_param_पढ़ो(codec, nid, param) \
	snd_hdac_पढ़ो_parm(&(codec)->core, nid, param)
#घोषणा snd_hda_get_sub_nodes(codec, nid, start_nid) \
	snd_hdac_get_sub_nodes(&(codec)->core, nid, start_nid)
पूर्णांक snd_hda_get_connections(काष्ठा hda_codec *codec, hda_nid_t nid,
			    hda_nid_t *conn_list, पूर्णांक max_conns);
अटल अंतरभूत पूर्णांक
snd_hda_get_num_conns(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	वापस snd_hda_get_connections(codec, nid, शून्य, 0);
पूर्ण

#घोषणा snd_hda_get_raw_connections(codec, nid, list, max_conns) \
	snd_hdac_get_connections(&(codec)->core, nid, list, max_conns)
#घोषणा snd_hda_get_num_raw_conns(codec, nid) \
	snd_hdac_get_connections(&(codec)->core, nid, शून्य, 0)

पूर्णांक snd_hda_get_conn_list(काष्ठा hda_codec *codec, hda_nid_t nid,
			  स्थिर hda_nid_t **listp);
पूर्णांक snd_hda_override_conn_list(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक nums,
			  स्थिर hda_nid_t *list);
पूर्णांक snd_hda_get_conn_index(काष्ठा hda_codec *codec, hda_nid_t mux,
			   hda_nid_t nid, पूर्णांक recursive);
अचिन्हित पूर्णांक snd_hda_get_num_devices(काष्ठा hda_codec *codec, hda_nid_t nid);
पूर्णांक snd_hda_get_devices(काष्ठा hda_codec *codec, hda_nid_t nid,
			u8 *dev_list, पूर्णांक max_devices);
पूर्णांक snd_hda_get_dev_select(काष्ठा hda_codec *codec, hda_nid_t nid);
पूर्णांक snd_hda_set_dev_select(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id);

काष्ठा hda_verb अणु
	hda_nid_t nid;
	u32 verb;
	u32 param;
पूर्ण;

व्योम snd_hda_sequence_ग_लिखो(काष्ठा hda_codec *codec,
			    स्थिर काष्ठा hda_verb *seq);

/* cached ग_लिखो */
अटल अंतरभूत पूर्णांक
snd_hda_codec_ग_लिखो_cache(काष्ठा hda_codec *codec, hda_nid_t nid,
			  पूर्णांक flags, अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm)
अणु
	वापस snd_hdac_regmap_ग_लिखो(&codec->core, nid, verb, parm);
पूर्ण

/* the काष्ठा क्रम codec->pin_configs */
काष्ठा hda_pincfg अणु
	hda_nid_t nid;
	अचिन्हित अक्षर ctrl;	/* original pin control value */
	अचिन्हित अक्षर target;	/* target pin control value */
	अचिन्हित पूर्णांक cfg;	/* शेष configuration */
पूर्ण;

अचिन्हित पूर्णांक snd_hda_codec_get_pincfg(काष्ठा hda_codec *codec, hda_nid_t nid);
पूर्णांक snd_hda_codec_set_pincfg(काष्ठा hda_codec *codec, hda_nid_t nid,
			     अचिन्हित पूर्णांक cfg);
पूर्णांक snd_hda_add_pincfg(काष्ठा hda_codec *codec, काष्ठा snd_array *list,
		       hda_nid_t nid, अचिन्हित पूर्णांक cfg); /* क्रम hwdep */
व्योम snd_hda_shutup_pins(काष्ठा hda_codec *codec);

/* SPDIF controls */
काष्ठा hda_spdअगर_out अणु
	hda_nid_t nid;		/* Converter nid values relate to */
	अचिन्हित पूर्णांक status;	/* IEC958 status bits */
	अचिन्हित लघु ctls;	/* SPDIF control bits */
पूर्ण;
काष्ठा hda_spdअगर_out *snd_hda_spdअगर_out_of_nid(काष्ठा hda_codec *codec,
					       hda_nid_t nid);
व्योम snd_hda_spdअगर_ctls_unassign(काष्ठा hda_codec *codec, पूर्णांक idx);
व्योम snd_hda_spdअगर_ctls_assign(काष्ठा hda_codec *codec, पूर्णांक idx, hda_nid_t nid);

/*
 * Mixer
 */
पूर्णांक snd_hda_codec_build_controls(काष्ठा hda_codec *codec);

/*
 * PCM
 */
पूर्णांक snd_hda_codec_parse_pcms(काष्ठा hda_codec *codec);
पूर्णांक snd_hda_codec_build_pcms(काष्ठा hda_codec *codec);

__म_लिखो(2, 3)
काष्ठा hda_pcm *snd_hda_codec_pcm_new(काष्ठा hda_codec *codec,
				      स्थिर अक्षर *fmt, ...);

व्योम snd_hda_codec_cleanup_क्रम_unbind(काष्ठा hda_codec *codec);

अटल अंतरभूत व्योम snd_hda_codec_pcm_get(काष्ठा hda_pcm *pcm)
अणु
	kref_get(&pcm->kref);
पूर्ण
व्योम snd_hda_codec_pcm_put(काष्ठा hda_pcm *pcm);

पूर्णांक snd_hda_codec_prepare(काष्ठा hda_codec *codec,
			  काष्ठा hda_pcm_stream *hinfo,
			  अचिन्हित पूर्णांक stream,
			  अचिन्हित पूर्णांक क्रमmat,
			  काष्ठा snd_pcm_substream *substream);
व्योम snd_hda_codec_cleanup(काष्ठा hda_codec *codec,
			   काष्ठा hda_pcm_stream *hinfo,
			   काष्ठा snd_pcm_substream *substream);

व्योम snd_hda_codec_setup_stream(काष्ठा hda_codec *codec, hda_nid_t nid,
				u32 stream_tag,
				पूर्णांक channel_id, पूर्णांक क्रमmat);
व्योम __snd_hda_codec_cleanup_stream(काष्ठा hda_codec *codec, hda_nid_t nid,
				    पूर्णांक करो_now);
#घोषणा snd_hda_codec_cleanup_stream(codec, nid) \
	__snd_hda_codec_cleanup_stream(codec, nid, 0)

#घोषणा snd_hda_query_supported_pcm(codec, nid, ratesp, fmtsp, bpsp) \
	snd_hdac_query_supported_pcm(&(codec)->core, nid, ratesp, fmtsp, bpsp)
#घोषणा snd_hda_is_supported_क्रमmat(codec, nid, fmt) \
	snd_hdac_is_supported_क्रमmat(&(codec)->core, nid, fmt)

बाह्य स्थिर काष्ठा snd_pcm_chmap_elem snd_pcm_2_1_chmaps[];

पूर्णांक snd_hda_attach_pcm_stream(काष्ठा hda_bus *_bus, काष्ठा hda_codec *codec,
			      काष्ठा hda_pcm *cpcm);

/*
 * Misc
 */
व्योम snd_hda_get_codec_name(काष्ठा hda_codec *codec, अक्षर *name, पूर्णांक namelen);
व्योम snd_hda_codec_set_घातer_to_all(काष्ठा hda_codec *codec, hda_nid_t fg,
				    अचिन्हित पूर्णांक घातer_state);

पूर्णांक snd_hda_lock_devices(काष्ठा hda_bus *bus);
व्योम snd_hda_unlock_devices(काष्ठा hda_bus *bus);
व्योम snd_hda_bus_reset(काष्ठा hda_bus *bus);
व्योम snd_hda_bus_reset_codecs(काष्ठा hda_bus *bus);

पूर्णांक snd_hda_codec_set_name(काष्ठा hda_codec *codec, स्थिर अक्षर *name);

/*
 * घातer management
 */
बाह्य स्थिर काष्ठा dev_pm_ops hda_codec_driver_pm;

अटल अंतरभूत
पूर्णांक hda_call_check_घातer_status(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
#अगर_घोषित CONFIG_PM
	अगर (codec->patch_ops.check_घातer_status)
		वापस codec->patch_ops.check_घातer_status(codec, nid);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * घातer saving
 */
#घोषणा snd_hda_घातer_up(codec)		snd_hdac_घातer_up(&(codec)->core)
#घोषणा snd_hda_घातer_up_pm(codec)	snd_hdac_घातer_up_pm(&(codec)->core)
#घोषणा snd_hda_घातer_करोwn(codec)	snd_hdac_घातer_करोwn(&(codec)->core)
#घोषणा snd_hda_घातer_करोwn_pm(codec)	snd_hdac_घातer_करोwn_pm(&(codec)->core)
#अगर_घोषित CONFIG_PM
व्योम snd_hda_set_घातer_save(काष्ठा hda_bus *bus, पूर्णांक delay);
व्योम snd_hda_update_घातer_acct(काष्ठा hda_codec *codec);
#अन्यथा
अटल अंतरभूत व्योम snd_hda_set_घातer_save(काष्ठा hda_bus *bus, पूर्णांक delay) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool hda_codec_need_resume(काष्ठा hda_codec *codec)
अणु
	वापस !codec->relaxed_resume && codec->jacktbl.used;
पूर्ण

#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER
/*
 * patch firmware
 */
पूर्णांक snd_hda_load_patch(काष्ठा hda_bus *bus, माप_प्रकार size, स्थिर व्योम *buf);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SND_HDA_DSP_LOADER
पूर्णांक snd_hda_codec_load_dsp_prepare(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक क्रमmat,
				   अचिन्हित पूर्णांक size,
				   काष्ठा snd_dma_buffer *bufp);
व्योम snd_hda_codec_load_dsp_trigger(काष्ठा hda_codec *codec, bool start);
व्योम snd_hda_codec_load_dsp_cleanup(काष्ठा hda_codec *codec,
				    काष्ठा snd_dma_buffer *dmab);
#अन्यथा
अटल अंतरभूत पूर्णांक
snd_hda_codec_load_dsp_prepare(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक क्रमmat,
				अचिन्हित पूर्णांक size,
				काष्ठा snd_dma_buffer *bufp)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम
snd_hda_codec_load_dsp_trigger(काष्ठा hda_codec *codec, bool start) अणुपूर्ण
अटल अंतरभूत व्योम
snd_hda_codec_load_dsp_cleanup(काष्ठा hda_codec *codec,
				काष्ठा snd_dma_buffer *dmab) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_HDA_CODEC_H */
