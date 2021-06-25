<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SOUND_HDAUDIO_EXT_H
#घोषणा __SOUND_HDAUDIO_EXT_H

#समावेश <sound/hdaudपन.स>

पूर्णांक snd_hdac_ext_bus_init(काष्ठा hdac_bus *bus, काष्ठा device *dev,
		      स्थिर काष्ठा hdac_bus_ops *ops,
		      स्थिर काष्ठा hdac_ext_bus_ops *ext_ops);

व्योम snd_hdac_ext_bus_निकास(काष्ठा hdac_bus *bus);
पूर्णांक snd_hdac_ext_bus_device_init(काष्ठा hdac_bus *bus, पूर्णांक addr,
				काष्ठा hdac_device *hdev, पूर्णांक type);
व्योम snd_hdac_ext_bus_device_निकास(काष्ठा hdac_device *hdev);
व्योम snd_hdac_ext_bus_device_हटाओ(काष्ठा hdac_bus *bus);

#घोषणा HDA_CODEC_REV_EXT_ENTRY(_vid, _rev, _name, drv_data) \
	अणु .venकरोr_id = (_vid), .rev_id = (_rev), .name = (_name), \
	  .api_version = HDA_DEV_ASOC, \
	  .driver_data = (अचिन्हित दीर्घ)(drv_data) पूर्ण
#घोषणा HDA_CODEC_EXT_ENTRY(_vid, _revid, _name, _drv_data) \
	HDA_CODEC_REV_EXT_ENTRY(_vid, _revid, _name, _drv_data)

व्योम snd_hdac_ext_bus_ppcap_enable(काष्ठा hdac_bus *chip, bool enable);
व्योम snd_hdac_ext_bus_ppcap_पूर्णांक_enable(काष्ठा hdac_bus *chip, bool enable);

व्योम snd_hdac_ext_stream_spbcap_enable(काष्ठा hdac_bus *chip,
				 bool enable, पूर्णांक index);

पूर्णांक snd_hdac_ext_bus_get_ml_capabilities(काष्ठा hdac_bus *bus);
काष्ठा hdac_ext_link *snd_hdac_ext_bus_get_link(काष्ठा hdac_bus *bus,
						स्थिर अक्षर *codec_name);

क्रमागत hdac_ext_stream_type अणु
	HDAC_EXT_STREAM_TYPE_COUPLED = 0,
	HDAC_EXT_STREAM_TYPE_HOST,
	HDAC_EXT_STREAM_TYPE_LINK
पूर्ण;

/**
 * hdac_ext_stream: HDAC extended stream क्रम extended HDA caps
 *
 * @hstream: hdac_stream
 * @pphc_addr: processing pipe host stream poपूर्णांकer
 * @pplc_addr: processing pipe link stream poपूर्णांकer
 * @spib_addr: software position in buffers stream poपूर्णांकer
 * @fअगरo_addr: software position Max fअगरos stream poपूर्णांकer
 * @dpibr_addr: DMA position in buffer resume poपूर्णांकer
 * @dpib: DMA position in buffer
 * @lpib: Linear position in buffer
 * @decoupled: stream host and link is decoupled
 * @link_locked: link is locked
 * @link_prepared: link is prepared
 * link_substream: link substream
 */
काष्ठा hdac_ext_stream अणु
	काष्ठा hdac_stream hstream;

	व्योम __iomem *pphc_addr;
	व्योम __iomem *pplc_addr;

	व्योम __iomem *spib_addr;
	व्योम __iomem *fअगरo_addr;

	व्योम __iomem *dpibr_addr;

	u32 dpib;
	u32 lpib;
	bool decoupled:1;
	bool link_locked:1;
	bool link_prepared;

	काष्ठा snd_pcm_substream *link_substream;
पूर्ण;

#घोषणा hdac_stream(s)		(&(s)->hstream)
#घोषणा stream_to_hdac_ext_stream(s) \
	container_of(s, काष्ठा hdac_ext_stream, hstream)

व्योम snd_hdac_ext_stream_init(काष्ठा hdac_bus *bus,
				काष्ठा hdac_ext_stream *stream, पूर्णांक idx,
				पूर्णांक direction, पूर्णांक tag);
पूर्णांक snd_hdac_ext_stream_init_all(काष्ठा hdac_bus *bus, पूर्णांक start_idx,
		पूर्णांक num_stream, पूर्णांक dir);
व्योम snd_hdac_stream_मुक्त_all(काष्ठा hdac_bus *bus);
व्योम snd_hdac_link_मुक्त_all(काष्ठा hdac_bus *bus);
काष्ठा hdac_ext_stream *snd_hdac_ext_stream_assign(काष्ठा hdac_bus *bus,
					   काष्ठा snd_pcm_substream *substream,
					   पूर्णांक type);
व्योम snd_hdac_ext_stream_release(काष्ठा hdac_ext_stream *azx_dev, पूर्णांक type);
व्योम snd_hdac_ext_stream_decouple(काष्ठा hdac_bus *bus,
				काष्ठा hdac_ext_stream *azx_dev, bool decouple);
व्योम snd_hdac_ext_stop_streams(काष्ठा hdac_bus *bus);

पूर्णांक snd_hdac_ext_stream_set_spib(काष्ठा hdac_bus *bus,
				 काष्ठा hdac_ext_stream *stream, u32 value);
पूर्णांक snd_hdac_ext_stream_get_spbmaxfअगरo(काष्ठा hdac_bus *bus,
				 काष्ठा hdac_ext_stream *stream);
व्योम snd_hdac_ext_stream_drsm_enable(काष्ठा hdac_bus *bus,
				bool enable, पूर्णांक index);
पूर्णांक snd_hdac_ext_stream_set_dpibr(काष्ठा hdac_bus *bus,
				काष्ठा hdac_ext_stream *stream, u32 value);
पूर्णांक snd_hdac_ext_stream_set_lpib(काष्ठा hdac_ext_stream *stream, u32 value);

व्योम snd_hdac_ext_link_stream_start(काष्ठा hdac_ext_stream *hstream);
व्योम snd_hdac_ext_link_stream_clear(काष्ठा hdac_ext_stream *hstream);
व्योम snd_hdac_ext_link_stream_reset(काष्ठा hdac_ext_stream *hstream);
पूर्णांक snd_hdac_ext_link_stream_setup(काष्ठा hdac_ext_stream *stream, पूर्णांक fmt);

काष्ठा hdac_ext_link अणु
	काष्ठा hdac_bus *bus;
	पूर्णांक index;
	व्योम __iomem *ml_addr; /* link output stream reg poपूर्णांकer */
	u32 lcaps;   /* link capablities */
	u16 lsdiid;  /* link sdi identअगरier */

	पूर्णांक ref_count;

	काष्ठा list_head list;
पूर्ण;

पूर्णांक snd_hdac_ext_bus_link_घातer_up(काष्ठा hdac_ext_link *link);
पूर्णांक snd_hdac_ext_bus_link_घातer_करोwn(काष्ठा hdac_ext_link *link);
पूर्णांक snd_hdac_ext_bus_link_घातer_up_all(काष्ठा hdac_bus *bus);
पूर्णांक snd_hdac_ext_bus_link_घातer_करोwn_all(काष्ठा hdac_bus *bus);
व्योम snd_hdac_ext_link_set_stream_id(काष्ठा hdac_ext_link *link,
				 पूर्णांक stream);
व्योम snd_hdac_ext_link_clear_stream_id(काष्ठा hdac_ext_link *link,
				 पूर्णांक stream);

पूर्णांक snd_hdac_ext_bus_link_get(काष्ठा hdac_bus *bus, काष्ठा hdac_ext_link *link);
पूर्णांक snd_hdac_ext_bus_link_put(काष्ठा hdac_bus *bus, काष्ठा hdac_ext_link *link);

व्योम snd_hdac_ext_bus_link_घातer(काष्ठा hdac_device *codec, bool enable);

/* update रेजिस्टर macro */
#घोषणा snd_hdac_updatel(addr, reg, mask, val)		\
	ग_लिखोl(((पढ़ोl(addr + reg) & ~(mask)) | (val)), \
		addr + reg)

#घोषणा snd_hdac_updatew(addr, reg, mask, val)		\
	ग_लिखोw(((पढ़ोw(addr + reg) & ~(mask)) | (val)), \
		addr + reg)


काष्ठा hdac_ext_device;

/* ops common to all codec drivers */
काष्ठा hdac_ext_codec_ops अणु
	पूर्णांक (*build_controls)(काष्ठा hdac_ext_device *dev);
	पूर्णांक (*init)(काष्ठा hdac_ext_device *dev);
	व्योम (*मुक्त)(काष्ठा hdac_ext_device *dev);
पूर्ण;

काष्ठा hda_dai_map अणु
	अक्षर *dai_name;
	hda_nid_t nid;
	u32	maxbps;
पूर्ण;

काष्ठा hdac_ext_dma_params अणु
	u32 क्रमmat;
	u8 stream_tag;
पूर्ण;

पूर्णांक snd_hda_ext_driver_रेजिस्टर(काष्ठा hdac_driver *drv);
व्योम snd_hda_ext_driver_unरेजिस्टर(काष्ठा hdac_driver *drv);

#पूर्ण_अगर /* __SOUND_HDAUDIO_EXT_H */
