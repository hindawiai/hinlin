<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * HD-audio core stuff
 */

#अगर_अघोषित __SOUND_HDAUDIO_H
#घोषणा __SOUND_HDAUDIO_H

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/समयcounter.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/meदो_स्मृति.h>
#समावेश <sound/hda_verbs.h>
#समावेश <drm/i915_component.h>

/* codec node id */
प्रकार u16 hda_nid_t;

काष्ठा hdac_bus;
काष्ठा hdac_stream;
काष्ठा hdac_device;
काष्ठा hdac_driver;
काष्ठा hdac_widget_tree;
काष्ठा hda_device_id;

/*
 * exported bus type
 */
बाह्य काष्ठा bus_type snd_hda_bus_type;

/*
 * generic arrays
 */
काष्ठा snd_array अणु
	अचिन्हित पूर्णांक used;
	अचिन्हित पूर्णांक alloced;
	अचिन्हित पूर्णांक elem_size;
	अचिन्हित पूर्णांक alloc_align;
	व्योम *list;
पूर्ण;

/*
 * HD-audio codec base device
 */
काष्ठा hdac_device अणु
	काष्ठा device dev;
	पूर्णांक type;
	काष्ठा hdac_bus *bus;
	अचिन्हित पूर्णांक addr;		/* codec address */
	काष्ठा list_head list;		/* list poपूर्णांक क्रम bus codec_list */

	hda_nid_t afg;			/* AFG node id */
	hda_nid_t mfg;			/* MFG node id */

	/* ids */
	अचिन्हित पूर्णांक venकरोr_id;
	अचिन्हित पूर्णांक subप्रणाली_id;
	अचिन्हित पूर्णांक revision_id;
	अचिन्हित पूर्णांक afg_function_id;
	अचिन्हित पूर्णांक mfg_function_id;
	अचिन्हित पूर्णांक afg_unsol:1;
	अचिन्हित पूर्णांक mfg_unsol:1;

	अचिन्हित पूर्णांक घातer_caps;	/* FG घातer caps */

	स्थिर अक्षर *venकरोr_name;	/* codec venकरोr name */
	स्थिर अक्षर *chip_name;		/* codec chip name */

	/* verb exec op override */
	पूर्णांक (*exec_verb)(काष्ठा hdac_device *dev, अचिन्हित पूर्णांक cmd,
			 अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक *res);

	/* widमाला_लो */
	अचिन्हित पूर्णांक num_nodes;
	hda_nid_t start_nid, end_nid;

	/* misc flags */
	atomic_t in_pm;		/* suspend/resume being perक्रमmed */

	/* sysfs */
	काष्ठा mutex widget_lock;
	काष्ठा hdac_widget_tree *widमाला_लो;

	/* regmap */
	काष्ठा regmap *regmap;
	काष्ठा mutex regmap_lock;
	काष्ठा snd_array venकरोr_verbs;
	bool lazy_cache:1;	/* करोn't wake up क्रम ग_लिखोs */
	bool caps_overwriting:1; /* caps overग_लिखो being in process */
	bool cache_coef:1;	/* cache COEF पढ़ो/ग_लिखो too */
पूर्ण;

/* device/driver type used क्रम matching */
क्रमागत अणु
	HDA_DEV_CORE,
	HDA_DEV_LEGACY,
	HDA_DEV_ASOC,
पूर्ण;

क्रमागत अणु
	SND_SKL_PCI_BIND_AUTO,	/* स्वतःmatic selection based on pci class */
	SND_SKL_PCI_BIND_LEGACY,/* bind only with legacy driver */
	SND_SKL_PCI_BIND_ASOC	/* bind only with ASoC driver */
पूर्ण;

/* direction */
क्रमागत अणु
	HDA_INPUT, HDA_OUTPUT
पूर्ण;

#घोषणा dev_to_hdac_dev(_dev)	container_of(_dev, काष्ठा hdac_device, dev)

पूर्णांक snd_hdac_device_init(काष्ठा hdac_device *dev, काष्ठा hdac_bus *bus,
			 स्थिर अक्षर *name, अचिन्हित पूर्णांक addr);
व्योम snd_hdac_device_निकास(काष्ठा hdac_device *dev);
पूर्णांक snd_hdac_device_रेजिस्टर(काष्ठा hdac_device *codec);
व्योम snd_hdac_device_unरेजिस्टर(काष्ठा hdac_device *codec);
पूर्णांक snd_hdac_device_set_chip_name(काष्ठा hdac_device *codec, स्थिर अक्षर *name);
पूर्णांक snd_hdac_codec_modalias(काष्ठा hdac_device *hdac, अक्षर *buf, माप_प्रकार size);

पूर्णांक snd_hdac_refresh_widमाला_लो(काष्ठा hdac_device *codec);

पूर्णांक snd_hdac_पढ़ो(काष्ठा hdac_device *codec, hda_nid_t nid,
		  अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm, अचिन्हित पूर्णांक *res);
पूर्णांक _snd_hdac_पढ़ो_parm(काष्ठा hdac_device *codec, hda_nid_t nid, पूर्णांक parm,
			अचिन्हित पूर्णांक *res);
पूर्णांक snd_hdac_पढ़ो_parm_uncached(काष्ठा hdac_device *codec, hda_nid_t nid,
				पूर्णांक parm);
पूर्णांक snd_hdac_override_parm(काष्ठा hdac_device *codec, hda_nid_t nid,
			   अचिन्हित पूर्णांक parm, अचिन्हित पूर्णांक val);
पूर्णांक snd_hdac_get_connections(काष्ठा hdac_device *codec, hda_nid_t nid,
			     hda_nid_t *conn_list, पूर्णांक max_conns);
पूर्णांक snd_hdac_get_sub_nodes(काष्ठा hdac_device *codec, hda_nid_t nid,
			   hda_nid_t *start_id);
अचिन्हित पूर्णांक snd_hdac_calc_stream_क्रमmat(अचिन्हित पूर्णांक rate,
					 अचिन्हित पूर्णांक channels,
					 snd_pcm_क्रमmat_t क्रमmat,
					 अचिन्हित पूर्णांक maxbps,
					 अचिन्हित लघु spdअगर_ctls);
पूर्णांक snd_hdac_query_supported_pcm(काष्ठा hdac_device *codec, hda_nid_t nid,
				u32 *ratesp, u64 *क्रमmatsp, अचिन्हित पूर्णांक *bpsp);
bool snd_hdac_is_supported_क्रमmat(काष्ठा hdac_device *codec, hda_nid_t nid,
				  अचिन्हित पूर्णांक क्रमmat);

पूर्णांक snd_hdac_codec_पढ़ो(काष्ठा hdac_device *hdac, hda_nid_t nid,
			पूर्णांक flags, अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm);
पूर्णांक snd_hdac_codec_ग_लिखो(काष्ठा hdac_device *hdac, hda_nid_t nid,
			पूर्णांक flags, अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm);
bool snd_hdac_check_घातer_state(काष्ठा hdac_device *hdac,
		hda_nid_t nid, अचिन्हित पूर्णांक target_state);
अचिन्हित पूर्णांक snd_hdac_sync_घातer_state(काष्ठा hdac_device *hdac,
		      hda_nid_t nid, अचिन्हित पूर्णांक target_state);
/**
 * snd_hdac_पढ़ो_parm - पढ़ो a codec parameter
 * @codec: the codec object
 * @nid: NID to पढ़ो a parameter
 * @parm: parameter to पढ़ो
 *
 * Returns -1 क्रम error.  If you need to distinguish the error more
 * strictly, use _snd_hdac_पढ़ो_parm() directly.
 */
अटल अंतरभूत पूर्णांक snd_hdac_पढ़ो_parm(काष्ठा hdac_device *codec, hda_nid_t nid,
				     पूर्णांक parm)
अणु
	अचिन्हित पूर्णांक val;

	वापस _snd_hdac_पढ़ो_parm(codec, nid, parm, &val) < 0 ? -1 : val;
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक snd_hdac_घातer_up(काष्ठा hdac_device *codec);
पूर्णांक snd_hdac_घातer_करोwn(काष्ठा hdac_device *codec);
पूर्णांक snd_hdac_घातer_up_pm(काष्ठा hdac_device *codec);
पूर्णांक snd_hdac_घातer_करोwn_pm(काष्ठा hdac_device *codec);
पूर्णांक snd_hdac_keep_घातer_up(काष्ठा hdac_device *codec);

/* call this at entering पूर्णांकo suspend/resume callbacks in codec driver */
अटल अंतरभूत व्योम snd_hdac_enter_pm(काष्ठा hdac_device *codec)
अणु
	atomic_inc(&codec->in_pm);
पूर्ण

/* call this at leaving from suspend/resume callbacks in codec driver */
अटल अंतरभूत व्योम snd_hdac_leave_pm(काष्ठा hdac_device *codec)
अणु
	atomic_dec(&codec->in_pm);
पूर्ण

अटल अंतरभूत bool snd_hdac_is_in_pm(काष्ठा hdac_device *codec)
अणु
	वापस atomic_पढ़ो(&codec->in_pm);
पूर्ण

अटल अंतरभूत bool snd_hdac_is_घातer_on(काष्ठा hdac_device *codec)
अणु
	वापस !pm_runसमय_suspended(&codec->dev);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_hdac_घातer_up(काष्ठा hdac_device *codec) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_घातer_करोwn(काष्ठा hdac_device *codec) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_घातer_up_pm(काष्ठा hdac_device *codec) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_घातer_करोwn_pm(काष्ठा hdac_device *codec) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_keep_घातer_up(काष्ठा hdac_device *codec) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम snd_hdac_enter_pm(काष्ठा hdac_device *codec) अणुपूर्ण
अटल अंतरभूत व्योम snd_hdac_leave_pm(काष्ठा hdac_device *codec) अणुपूर्ण
अटल अंतरभूत bool snd_hdac_is_in_pm(काष्ठा hdac_device *codec) अणु वापस false; पूर्ण
अटल अंतरभूत bool snd_hdac_is_घातer_on(काष्ठा hdac_device *codec) अणु वापस true; पूर्ण
#पूर्ण_अगर

/*
 * HD-audio codec base driver
 */
काष्ठा hdac_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक type;
	स्थिर काष्ठा hda_device_id *id_table;
	पूर्णांक (*match)(काष्ठा hdac_device *dev, काष्ठा hdac_driver *drv);
	व्योम (*unsol_event)(काष्ठा hdac_device *dev, अचिन्हित पूर्णांक event);

	/* fields used by ext bus APIs */
	पूर्णांक (*probe)(काष्ठा hdac_device *dev);
	पूर्णांक (*हटाओ)(काष्ठा hdac_device *dev);
	व्योम (*shutकरोwn)(काष्ठा hdac_device *dev);
पूर्ण;

#घोषणा drv_to_hdac_driver(_drv) container_of(_drv, काष्ठा hdac_driver, driver)

स्थिर काष्ठा hda_device_id *
hdac_get_device_id(काष्ठा hdac_device *hdev, काष्ठा hdac_driver *drv);

/*
 * Bus verb चालकs
 */
काष्ठा hdac_bus_ops अणु
	/* send a single command */
	पूर्णांक (*command)(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक cmd);
	/* get a response from the last command */
	पूर्णांक (*get_response)(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
			    अचिन्हित पूर्णांक *res);
	/* notअगरy of codec link घातer-up/करोwn */
	व्योम (*link_घातer)(काष्ठा hdac_device *hdev, bool enable);
पूर्ण;

/*
 * ops used क्रम ASoC HDA codec drivers
 */
काष्ठा hdac_ext_bus_ops अणु
	पूर्णांक (*hdev_attach)(काष्ठा hdac_device *hdev);
	पूर्णांक (*hdev_detach)(काष्ठा hdac_device *hdev);
पूर्ण;

#घोषणा HDA_UNSOL_QUEUE_SIZE	64
#घोषणा HDA_MAX_CODECS		8	/* limit by controller side */

/*
 * CORB/RIRB
 *
 * Each CORB entry is 4byte, RIRB is 8byte
 */
काष्ठा hdac_rb अणु
	__le32 *buf;		/* भव address of CORB/RIRB buffer */
	dma_addr_t addr;	/* physical address of CORB/RIRB buffer */
	अचिन्हित लघु rp, wp;	/* RIRB पढ़ो/ग_लिखो poपूर्णांकers */
	पूर्णांक cmds[HDA_MAX_CODECS];	/* number of pending requests */
	u32 res[HDA_MAX_CODECS];	/* last पढ़ो value */
पूर्ण;

/*
 * HD-audio bus base driver
 *
 * @ppcap: pp capabilities poपूर्णांकer
 * @spbcap: SPIB capabilities poपूर्णांकer
 * @mlcap: MultiLink capabilities poपूर्णांकer
 * @gtscap: gts capabilities poपूर्णांकer
 * @drsmcap: dma resume capabilities poपूर्णांकer
 * @num_streams: streams supported
 * @idx: HDA link index
 * @hlink_list: link list of HDA links
 * @lock: lock क्रम link and display घातer mgmt
 * @cmd_dma_state: state of cmd DMAs: CORB and RIRB
 */
काष्ठा hdac_bus अणु
	काष्ठा device *dev;
	स्थिर काष्ठा hdac_bus_ops *ops;
	स्थिर काष्ठा hdac_ext_bus_ops *ext_ops;

	/* h/w resources */
	अचिन्हित दीर्घ addr;
	व्योम __iomem *remap_addr;
	पूर्णांक irq;

	व्योम __iomem *ppcap;
	व्योम __iomem *spbcap;
	व्योम __iomem *mlcap;
	व्योम __iomem *gtscap;
	व्योम __iomem *drsmcap;

	/* codec linked list */
	काष्ठा list_head codec_list;
	अचिन्हित पूर्णांक num_codecs;

	/* link caddr -> codec */
	काष्ठा hdac_device *caddr_tbl[HDA_MAX_CODEC_ADDRESS + 1];

	/* unsolicited event queue */
	u32 unsol_queue[HDA_UNSOL_QUEUE_SIZE * 2]; /* ring buffer */
	अचिन्हित पूर्णांक unsol_rp, unsol_wp;
	काष्ठा work_काष्ठा unsol_work;

	/* bit flags of detected codecs */
	अचिन्हित दीर्घ codec_mask;

	/* bit flags of घातered codecs */
	अचिन्हित दीर्घ codec_घातered;

	/* CORB/RIRB */
	काष्ठा hdac_rb corb;
	काष्ठा hdac_rb rirb;
	अचिन्हित पूर्णांक last_cmd[HDA_MAX_CODECS];	/* last sent command */
	रुको_queue_head_t rirb_wq;

	/* CORB/RIRB and position buffers */
	काष्ठा snd_dma_buffer rb;
	काष्ठा snd_dma_buffer posbuf;
	पूर्णांक dma_type;			/* SNDRV_DMA_TYPE_XXX क्रम CORB/RIRB */

	/* hdac_stream linked list */
	काष्ठा list_head stream_list;

	/* operation state */
	bool chip_init:1;		/* h/w initialized */

	/* behavior flags */
	bool aligned_mmio:1;		/* aligned MMIO access */
	bool sync_ग_लिखो:1;		/* sync after verb ग_लिखो */
	bool use_posbuf:1;		/* use position buffer */
	bool snoop:1;			/* enable snooping */
	bool align_bdle_4k:1;		/* BDLE align 4K boundary */
	bool reverse_assign:1;		/* assign devices in reverse order */
	bool corbrp_self_clear:1;	/* CORBRP clears itself after reset */
	bool polling_mode:1;
	bool needs_damn_दीर्घ_delay:1;

	पूर्णांक poll_count;

	पूर्णांक bdl_pos_adj;		/* BDL position adjusपंचांगent */

	/* delay समय in us क्रम dma stop */
	अचिन्हित पूर्णांक dma_stop_delay;

	/* locks */
	spinlock_t reg_lock;
	काष्ठा mutex cmd_mutex;
	काष्ठा mutex lock;

	/* DRM component पूर्णांकerface */
	काष्ठा drm_audio_component *audio_component;
	दीर्घ display_घातer_status;
	अचिन्हित दीर्घ display_घातer_active;

	/* parameters required क्रम enhanced capabilities */
	पूर्णांक num_streams;
	पूर्णांक idx;

	/* link management */
	काष्ठा list_head hlink_list;
	bool cmd_dma_state;

	/* factor used to derive STRIPE control value */
	अचिन्हित पूर्णांक sकरो_limit;
पूर्ण;

पूर्णांक snd_hdac_bus_init(काष्ठा hdac_bus *bus, काष्ठा device *dev,
		      स्थिर काष्ठा hdac_bus_ops *ops);
व्योम snd_hdac_bus_निकास(काष्ठा hdac_bus *bus);
पूर्णांक snd_hdac_bus_exec_verb_unlocked(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
				    अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक *res);

व्योम snd_hdac_codec_link_up(काष्ठा hdac_device *codec);
व्योम snd_hdac_codec_link_करोwn(काष्ठा hdac_device *codec);

पूर्णांक snd_hdac_bus_send_cmd(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक val);
पूर्णांक snd_hdac_bus_get_response(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
			      अचिन्हित पूर्णांक *res);
पूर्णांक snd_hdac_bus_parse_capabilities(काष्ठा hdac_bus *bus);

bool snd_hdac_bus_init_chip(काष्ठा hdac_bus *bus, bool full_reset);
व्योम snd_hdac_bus_stop_chip(काष्ठा hdac_bus *bus);
व्योम snd_hdac_bus_init_cmd_io(काष्ठा hdac_bus *bus);
व्योम snd_hdac_bus_stop_cmd_io(काष्ठा hdac_bus *bus);
व्योम snd_hdac_bus_enter_link_reset(काष्ठा hdac_bus *bus);
व्योम snd_hdac_bus_निकास_link_reset(काष्ठा hdac_bus *bus);
पूर्णांक snd_hdac_bus_reset_link(काष्ठा hdac_bus *bus, bool full_reset);
व्योम snd_hdac_bus_link_घातer(काष्ठा hdac_device *hdev, bool enable);

व्योम snd_hdac_bus_update_rirb(काष्ठा hdac_bus *bus);
पूर्णांक snd_hdac_bus_handle_stream_irq(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक status,
				    व्योम (*ack)(काष्ठा hdac_bus *,
						काष्ठा hdac_stream *));

पूर्णांक snd_hdac_bus_alloc_stream_pages(काष्ठा hdac_bus *bus);
व्योम snd_hdac_bus_मुक्त_stream_pages(काष्ठा hdac_bus *bus);

#अगर_घोषित CONFIG_SND_HDA_ALIGNED_MMIO
अचिन्हित पूर्णांक snd_hdac_aligned_पढ़ो(व्योम __iomem *addr, अचिन्हित पूर्णांक mask);
व्योम snd_hdac_aligned_ग_लिखो(अचिन्हित पूर्णांक val, व्योम __iomem *addr,
			    अचिन्हित पूर्णांक mask);
#घोषणा snd_hdac_aligned_mmio(bus)	(bus)->aligned_mmio
#अन्यथा
#घोषणा snd_hdac_aligned_mmio(bus)	false
#घोषणा snd_hdac_aligned_पढ़ो(addr, mask)	0
#घोषणा snd_hdac_aligned_ग_लिखो(val, addr, mask) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल अंतरभूत व्योम snd_hdac_reg_ग_लिखोb(काष्ठा hdac_bus *bus, व्योम __iomem *addr,
				       u8 val)
अणु
	अगर (snd_hdac_aligned_mmio(bus))
		snd_hdac_aligned_ग_लिखो(val, addr, 0xff);
	अन्यथा
		ग_लिखोb(val, addr);
पूर्ण

अटल अंतरभूत व्योम snd_hdac_reg_ग_लिखोw(काष्ठा hdac_bus *bus, व्योम __iomem *addr,
				       u16 val)
अणु
	अगर (snd_hdac_aligned_mmio(bus))
		snd_hdac_aligned_ग_लिखो(val, addr, 0xffff);
	अन्यथा
		ग_लिखोw(val, addr);
पूर्ण

अटल अंतरभूत u8 snd_hdac_reg_पढ़ोb(काष्ठा hdac_bus *bus, व्योम __iomem *addr)
अणु
	वापस snd_hdac_aligned_mmio(bus) ?
		snd_hdac_aligned_पढ़ो(addr, 0xff) : पढ़ोb(addr);
पूर्ण

अटल अंतरभूत u16 snd_hdac_reg_पढ़ोw(काष्ठा hdac_bus *bus, व्योम __iomem *addr)
अणु
	वापस snd_hdac_aligned_mmio(bus) ?
		snd_hdac_aligned_पढ़ो(addr, 0xffff) : पढ़ोw(addr);
पूर्ण

#घोषणा snd_hdac_reg_ग_लिखोl(bus, addr, val)	ग_लिखोl(val, addr)
#घोषणा snd_hdac_reg_पढ़ोl(bus, addr)	पढ़ोl(addr)

/*
 * macros क्रम easy use
 */
#घोषणा _snd_hdac_chip_ग_लिखोb(chip, reg, value) \
	snd_hdac_reg_ग_लिखोb(chip, (chip)->remap_addr + (reg), value)
#घोषणा _snd_hdac_chip_पढ़ोb(chip, reg) \
	snd_hdac_reg_पढ़ोb(chip, (chip)->remap_addr + (reg))
#घोषणा _snd_hdac_chip_ग_लिखोw(chip, reg, value) \
	snd_hdac_reg_ग_लिखोw(chip, (chip)->remap_addr + (reg), value)
#घोषणा _snd_hdac_chip_पढ़ोw(chip, reg) \
	snd_hdac_reg_पढ़ोw(chip, (chip)->remap_addr + (reg))
#घोषणा _snd_hdac_chip_ग_लिखोl(chip, reg, value) \
	snd_hdac_reg_ग_लिखोl(chip, (chip)->remap_addr + (reg), value)
#घोषणा _snd_hdac_chip_पढ़ोl(chip, reg) \
	snd_hdac_reg_पढ़ोl(chip, (chip)->remap_addr + (reg))

/* पढ़ो/ग_लिखो a रेजिस्टर, pass without AZX_REG_ prefix */
#घोषणा snd_hdac_chip_ग_लिखोl(chip, reg, value) \
	_snd_hdac_chip_ग_लिखोl(chip, AZX_REG_ ## reg, value)
#घोषणा snd_hdac_chip_ग_लिखोw(chip, reg, value) \
	_snd_hdac_chip_ग_लिखोw(chip, AZX_REG_ ## reg, value)
#घोषणा snd_hdac_chip_ग_लिखोb(chip, reg, value) \
	_snd_hdac_chip_ग_लिखोb(chip, AZX_REG_ ## reg, value)
#घोषणा snd_hdac_chip_पढ़ोl(chip, reg) \
	_snd_hdac_chip_पढ़ोl(chip, AZX_REG_ ## reg)
#घोषणा snd_hdac_chip_पढ़ोw(chip, reg) \
	_snd_hdac_chip_पढ़ोw(chip, AZX_REG_ ## reg)
#घोषणा snd_hdac_chip_पढ़ोb(chip, reg) \
	_snd_hdac_chip_पढ़ोb(chip, AZX_REG_ ## reg)

/* update a रेजिस्टर, pass without AZX_REG_ prefix */
#घोषणा snd_hdac_chip_updatel(chip, reg, mask, val) \
	snd_hdac_chip_ग_लिखोl(chip, reg, \
			     (snd_hdac_chip_पढ़ोl(chip, reg) & ~(mask)) | (val))
#घोषणा snd_hdac_chip_updatew(chip, reg, mask, val) \
	snd_hdac_chip_ग_लिखोw(chip, reg, \
			     (snd_hdac_chip_पढ़ोw(chip, reg) & ~(mask)) | (val))
#घोषणा snd_hdac_chip_updateb(chip, reg, mask, val) \
	snd_hdac_chip_ग_लिखोb(chip, reg, \
			     (snd_hdac_chip_पढ़ोb(chip, reg) & ~(mask)) | (val))

/*
 * HD-audio stream
 */
काष्ठा hdac_stream अणु
	काष्ठा hdac_bus *bus;
	काष्ठा snd_dma_buffer bdl; /* BDL buffer */
	__le32 *posbuf;		/* position buffer poपूर्णांकer */
	पूर्णांक direction;		/* playback / capture (SNDRV_PCM_STREAM_*) */

	अचिन्हित पूर्णांक bufsize;	/* size of the play buffer in bytes */
	अचिन्हित पूर्णांक period_bytes; /* size of the period in bytes */
	अचिन्हित पूर्णांक frags;	/* number क्रम period in the play buffer */
	अचिन्हित पूर्णांक fअगरo_size;	/* FIFO size */

	व्योम __iomem *sd_addr;	/* stream descriptor poपूर्णांकer */

	u32 sd_पूर्णांक_sta_mask;	/* stream पूर्णांक status mask */

	/* pcm support */
	काष्ठा snd_pcm_substream *substream;	/* asचिन्हित substream,
						 * set in PCM खोलो
						 */
	काष्ठा snd_compr_stream *cstream;
	अचिन्हित पूर्णांक क्रमmat_val;	/* क्रमmat value to be set in the
					 * controller and the codec
					 */
	अचिन्हित अक्षर stream_tag;	/* asचिन्हित stream */
	अचिन्हित अक्षर index;		/* stream index */
	पूर्णांक asचिन्हित_key;		/* last device# key asचिन्हित to */

	bool खोलोed:1;
	bool running:1;
	bool prepared:1;
	bool no_period_wakeup:1;
	bool locked:1;
	bool stripe:1;			/* apply stripe control */

	u64 curr_pos;
	/* बारtamp */
	अचिन्हित दीर्घ start_wallclk;	/* start + minimum wallclk */
	अचिन्हित दीर्घ period_wallclk;	/* wallclk क्रम period */
	काष्ठा समयcounter  tc;
	काष्ठा cyclecounter cc;
	पूर्णांक delay_negative_threshold;

	काष्ठा list_head list;
#अगर_घोषित CONFIG_SND_HDA_DSP_LOADER
	/* DSP access mutex */
	काष्ठा mutex dsp_mutex;
#पूर्ण_अगर
पूर्ण;

व्योम snd_hdac_stream_init(काष्ठा hdac_bus *bus, काष्ठा hdac_stream *azx_dev,
			  पूर्णांक idx, पूर्णांक direction, पूर्णांक tag);
काष्ठा hdac_stream *snd_hdac_stream_assign(काष्ठा hdac_bus *bus,
					   काष्ठा snd_pcm_substream *substream);
व्योम snd_hdac_stream_release(काष्ठा hdac_stream *azx_dev);
काष्ठा hdac_stream *snd_hdac_get_stream(काष्ठा hdac_bus *bus,
					पूर्णांक dir, पूर्णांक stream_tag);

पूर्णांक snd_hdac_stream_setup(काष्ठा hdac_stream *azx_dev);
व्योम snd_hdac_stream_cleanup(काष्ठा hdac_stream *azx_dev);
पूर्णांक snd_hdac_stream_setup_periods(काष्ठा hdac_stream *azx_dev);
पूर्णांक snd_hdac_stream_set_params(काष्ठा hdac_stream *azx_dev,
				अचिन्हित पूर्णांक क्रमmat_val);
व्योम snd_hdac_stream_start(काष्ठा hdac_stream *azx_dev, bool fresh_start);
व्योम snd_hdac_stream_clear(काष्ठा hdac_stream *azx_dev);
व्योम snd_hdac_stream_stop(काष्ठा hdac_stream *azx_dev);
व्योम snd_hdac_stream_reset(काष्ठा hdac_stream *azx_dev);
व्योम snd_hdac_stream_sync_trigger(काष्ठा hdac_stream *azx_dev, bool set,
				  अचिन्हित पूर्णांक streams, अचिन्हित पूर्णांक reg);
व्योम snd_hdac_stream_sync(काष्ठा hdac_stream *azx_dev, bool start,
			  अचिन्हित पूर्णांक streams);
व्योम snd_hdac_stream_समयcounter_init(काष्ठा hdac_stream *azx_dev,
				      अचिन्हित पूर्णांक streams);
पूर्णांक snd_hdac_get_stream_stripe_ctl(काष्ठा hdac_bus *bus,
				काष्ठा snd_pcm_substream *substream);

/*
 * macros क्रम easy use
 */
/* पढ़ो/ग_लिखो a रेजिस्टर, pass without AZX_REG_ prefix */
#घोषणा snd_hdac_stream_ग_लिखोl(dev, reg, value) \
	snd_hdac_reg_ग_लिखोl((dev)->bus, (dev)->sd_addr + AZX_REG_ ## reg, value)
#घोषणा snd_hdac_stream_ग_लिखोw(dev, reg, value) \
	snd_hdac_reg_ग_लिखोw((dev)->bus, (dev)->sd_addr + AZX_REG_ ## reg, value)
#घोषणा snd_hdac_stream_ग_लिखोb(dev, reg, value) \
	snd_hdac_reg_ग_लिखोb((dev)->bus, (dev)->sd_addr + AZX_REG_ ## reg, value)
#घोषणा snd_hdac_stream_पढ़ोl(dev, reg) \
	snd_hdac_reg_पढ़ोl((dev)->bus, (dev)->sd_addr + AZX_REG_ ## reg)
#घोषणा snd_hdac_stream_पढ़ोw(dev, reg) \
	snd_hdac_reg_पढ़ोw((dev)->bus, (dev)->sd_addr + AZX_REG_ ## reg)
#घोषणा snd_hdac_stream_पढ़ोb(dev, reg) \
	snd_hdac_reg_पढ़ोb((dev)->bus, (dev)->sd_addr + AZX_REG_ ## reg)

/* update a रेजिस्टर, pass without AZX_REG_ prefix */
#घोषणा snd_hdac_stream_updatel(dev, reg, mask, val) \
	snd_hdac_stream_ग_लिखोl(dev, reg, \
			       (snd_hdac_stream_पढ़ोl(dev, reg) & \
				~(mask)) | (val))
#घोषणा snd_hdac_stream_updatew(dev, reg, mask, val) \
	snd_hdac_stream_ग_लिखोw(dev, reg, \
			       (snd_hdac_stream_पढ़ोw(dev, reg) & \
				~(mask)) | (val))
#घोषणा snd_hdac_stream_updateb(dev, reg, mask, val) \
	snd_hdac_stream_ग_लिखोb(dev, reg, \
			       (snd_hdac_stream_पढ़ोb(dev, reg) & \
				~(mask)) | (val))

#अगर_घोषित CONFIG_SND_HDA_DSP_LOADER
/* DSP lock helpers */
#घोषणा snd_hdac_dsp_lock_init(dev)	mutex_init(&(dev)->dsp_mutex)
#घोषणा snd_hdac_dsp_lock(dev)		mutex_lock(&(dev)->dsp_mutex)
#घोषणा snd_hdac_dsp_unlock(dev)	mutex_unlock(&(dev)->dsp_mutex)
#घोषणा snd_hdac_stream_is_locked(dev)	((dev)->locked)
/* DSP loader helpers */
पूर्णांक snd_hdac_dsp_prepare(काष्ठा hdac_stream *azx_dev, अचिन्हित पूर्णांक क्रमmat,
			 अचिन्हित पूर्णांक byte_size, काष्ठा snd_dma_buffer *bufp);
व्योम snd_hdac_dsp_trigger(काष्ठा hdac_stream *azx_dev, bool start);
व्योम snd_hdac_dsp_cleanup(काष्ठा hdac_stream *azx_dev,
			  काष्ठा snd_dma_buffer *dmab);
#अन्यथा /* CONFIG_SND_HDA_DSP_LOADER */
#घोषणा snd_hdac_dsp_lock_init(dev)	करो अणुपूर्ण जबतक (0)
#घोषणा snd_hdac_dsp_lock(dev)		करो अणुपूर्ण जबतक (0)
#घोषणा snd_hdac_dsp_unlock(dev)	करो अणुपूर्ण जबतक (0)
#घोषणा snd_hdac_stream_is_locked(dev)	0

अटल अंतरभूत पूर्णांक
snd_hdac_dsp_prepare(काष्ठा hdac_stream *azx_dev, अचिन्हित पूर्णांक क्रमmat,
		     अचिन्हित पूर्णांक byte_size, काष्ठा snd_dma_buffer *bufp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_hdac_dsp_trigger(काष्ठा hdac_stream *azx_dev, bool start)
अणु
पूर्ण

अटल अंतरभूत व्योम snd_hdac_dsp_cleanup(काष्ठा hdac_stream *azx_dev,
					काष्ठा snd_dma_buffer *dmab)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_HDA_DSP_LOADER */


/*
 * generic array helpers
 */
व्योम *snd_array_new(काष्ठा snd_array *array);
व्योम snd_array_मुक्त(काष्ठा snd_array *array);
अटल अंतरभूत व्योम snd_array_init(काष्ठा snd_array *array, अचिन्हित पूर्णांक size,
				  अचिन्हित पूर्णांक align)
अणु
	array->elem_size = size;
	array->alloc_align = align;
पूर्ण

अटल अंतरभूत व्योम *snd_array_elem(काष्ठा snd_array *array, अचिन्हित पूर्णांक idx)
अणु
	वापस array->list + idx * array->elem_size;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_array_index(काष्ठा snd_array *array, व्योम *ptr)
अणु
	वापस (अचिन्हित दीर्घ)(ptr - array->list) / array->elem_size;
पूर्ण

/* a helper macro to iterate क्रम each snd_array element */
#घोषणा snd_array_क्रम_each(array, idx, ptr) \
	क्रम ((idx) = 0, (ptr) = (array)->list; (idx) < (array)->used; \
	     (ptr) = snd_array_elem(array, ++(idx)))

#पूर्ण_अगर /* __SOUND_HDAUDIO_H */
