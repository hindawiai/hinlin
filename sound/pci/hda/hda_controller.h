<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Common functionality क्रम the alsa driver code base क्रम HD Audio.
 */

#अगर_अघोषित __SOUND_HDA_CONTROLLER_H
#घोषणा __SOUND_HDA_CONTROLLER_H

#समावेश <linux/समयcounter.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/hda_codec.h>
#समावेश <sound/hda_रेजिस्टर.h>

#घोषणा AZX_MAX_CODECS		HDA_MAX_CODECS
#घोषणा AZX_DEFAULT_CODECS	4

/* driver quirks (capabilities) */
/* bits 0-7 are used क्रम indicating driver type */
#घोषणा AZX_DCAPS_NO_TCSEL	(1 << 8)	/* No Intel TCSEL bit */
#घोषणा AZX_DCAPS_NO_MSI	(1 << 9)	/* No MSI support */
#घोषणा AZX_DCAPS_SNOOP_MASK	(3 << 10)	/* snoop type mask */
#घोषणा AZX_DCAPS_SNOOP_OFF	(1 << 12)	/* snoop शेष off */
#अगर_घोषित CONFIG_SND_HDA_I915
#घोषणा AZX_DCAPS_I915_COMPONENT (1 << 13)	/* bind with i915 gfx */
#अन्यथा
#घोषणा AZX_DCAPS_I915_COMPONENT 0		/* NOP */
#पूर्ण_अगर
/* 14 unused */
#घोषणा AZX_DCAPS_CTX_WORKAROUND (1 << 15)	/* X-Fi workaround */
#घोषणा AZX_DCAPS_POSFIX_LPIB	(1 << 16)	/* Use LPIB as शेष */
#घोषणा AZX_DCAPS_AMD_WORKAROUND (1 << 17)	/* AMD-specअगरic workaround */
#घोषणा AZX_DCAPS_NO_64BIT	(1 << 18)	/* No 64bit address */
/* 19 unused */
#घोषणा AZX_DCAPS_OLD_SSYNC	(1 << 20)	/* Old SSYNC reg क्रम ICH */
#घोषणा AZX_DCAPS_NO_ALIGN_बफ_मानE (1 << 21)	/* no buffer size alignment */
/* 22 unused */
#घोषणा AZX_DCAPS_4K_BDLE_BOUNDARY (1 << 23)	/* BDLE in 4k boundary */
/* 24 unused */
#घोषणा AZX_DCAPS_COUNT_LPIB_DELAY  (1 << 25)	/* Take LPIB as delay */
#घोषणा AZX_DCAPS_PM_RUNTIME	(1 << 26)	/* runसमय PM support */
/* 27 unused */
#घोषणा AZX_DCAPS_CORBRP_SELF_CLEAR (1 << 28)	/* CORBRP clears itself after reset */
#घोषणा AZX_DCAPS_NO_MSI64      (1 << 29)	/* Stick to 32-bit MSIs */
#घोषणा AZX_DCAPS_SEPARATE_STREAM_TAG	(1 << 30) /* capture and playback use separate stream tag */

क्रमागत अणु
	AZX_SNOOP_TYPE_NONE,
	AZX_SNOOP_TYPE_SCH,
	AZX_SNOOP_TYPE_ATI,
	AZX_SNOOP_TYPE_NVIDIA,
पूर्ण;

काष्ठा azx_dev अणु
	काष्ठा hdac_stream core;

	अचिन्हित पूर्णांक irq_pending:1;
	/*
	 * For VIA:
	 *  A flag to ensure DMA position is 0
	 *  when link position is not greater than FIFO size
	 */
	अचिन्हित पूर्णांक insufficient:1;
पूर्ण;

#घोषणा azx_stream(dev)		(&(dev)->core)
#घोषणा stream_to_azx_dev(s)	container_of(s, काष्ठा azx_dev, core)

काष्ठा azx;

/* Functions to पढ़ो/ग_लिखो to hda रेजिस्टरs. */
काष्ठा hda_controller_ops अणु
	/* Disable msi अगर supported, PCI only */
	पूर्णांक (*disable_msi_reset_irq)(काष्ठा azx *);
	व्योम (*pcm_mmap_prepare)(काष्ठा snd_pcm_substream *substream,
				 काष्ठा vm_area_काष्ठा *area);
	/* Check अगर current position is acceptable */
	पूर्णांक (*position_check)(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev);
	/* enable/disable the link घातer */
	पूर्णांक (*link_घातer)(काष्ठा azx *chip, bool enable);
पूर्ण;

काष्ठा azx_pcm अणु
	काष्ठा azx *chip;
	काष्ठा snd_pcm *pcm;
	काष्ठा hda_codec *codec;
	काष्ठा hda_pcm *info;
	काष्ठा list_head list;
पूर्ण;

प्रकार अचिन्हित पूर्णांक (*azx_get_pos_callback_t)(काष्ठा azx *, काष्ठा azx_dev *);
प्रकार पूर्णांक (*azx_get_delay_callback_t)(काष्ठा azx *, काष्ठा azx_dev *, अचिन्हित पूर्णांक pos);

काष्ठा azx अणु
	काष्ठा hda_bus bus;

	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;
	पूर्णांक dev_index;

	/* chip type specअगरic */
	पूर्णांक driver_type;
	अचिन्हित पूर्णांक driver_caps;
	पूर्णांक playback_streams;
	पूर्णांक playback_index_offset;
	पूर्णांक capture_streams;
	पूर्णांक capture_index_offset;
	पूर्णांक num_streams;
	पूर्णांक jackpoll_पूर्णांकerval; /* jack poll पूर्णांकerval in jअगरfies */

	/* Register पूर्णांकeraction. */
	स्थिर काष्ठा hda_controller_ops *ops;

	/* position adjusपंचांगent callbacks */
	azx_get_pos_callback_t get_position[2];
	azx_get_delay_callback_t get_delay[2];

	/* locks */
	काष्ठा mutex खोलो_mutex; /* Prevents concurrent खोलो/बंद operations */

	/* PCM */
	काष्ठा list_head pcm_list; /* azx_pcm list */

	/* HD codec */
	पूर्णांक  codec_probe_mask; /* copied from probe_mask option */
	अचिन्हित पूर्णांक beep_mode;

#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER
	स्थिर काष्ठा firmware *fw;
#पूर्ण_अगर

	/* flags */
	पूर्णांक bdl_pos_adj;
	अचिन्हित पूर्णांक running:1;
	अचिन्हित पूर्णांक fallback_to_single_cmd:1;
	अचिन्हित पूर्णांक single_cmd:1;
	अचिन्हित पूर्णांक msi:1;
	अचिन्हित पूर्णांक probing:1; /* codec probing phase */
	अचिन्हित पूर्णांक snoop:1;
	अचिन्हित पूर्णांक uc_buffer:1; /* non-cached pages क्रम stream buffers */
	अचिन्हित पूर्णांक align_buffer_size:1;
	अचिन्हित पूर्णांक region_requested:1;
	अचिन्हित पूर्णांक disabled:1; /* disabled by vga_चयनeroo */
	अचिन्हित पूर्णांक pm_prepared:1;

	/* GTS present */
	अचिन्हित पूर्णांक gts_present:1;

#अगर_घोषित CONFIG_SND_HDA_DSP_LOADER
	काष्ठा azx_dev saved_azx_dev;
#पूर्ण_अगर
पूर्ण;

#घोषणा azx_bus(chip)	(&(chip)->bus.core)
#घोषणा bus_to_azx(_bus)	container_of(_bus, काष्ठा azx, bus.core)

अटल अंतरभूत bool azx_snoop(काष्ठा azx *chip)
अणु
	वापस !IS_ENABLED(CONFIG_X86) || chip->snoop;
पूर्ण

/*
 * macros क्रम easy use
 */

#घोषणा azx_ग_लिखोl(chip, reg, value) \
	snd_hdac_chip_ग_लिखोl(azx_bus(chip), reg, value)
#घोषणा azx_पढ़ोl(chip, reg) \
	snd_hdac_chip_पढ़ोl(azx_bus(chip), reg)
#घोषणा azx_ग_लिखोw(chip, reg, value) \
	snd_hdac_chip_ग_लिखोw(azx_bus(chip), reg, value)
#घोषणा azx_पढ़ोw(chip, reg) \
	snd_hdac_chip_पढ़ोw(azx_bus(chip), reg)
#घोषणा azx_ग_लिखोb(chip, reg, value) \
	snd_hdac_chip_ग_लिखोb(azx_bus(chip), reg, value)
#घोषणा azx_पढ़ोb(chip, reg) \
	snd_hdac_chip_पढ़ोb(azx_bus(chip), reg)

#घोषणा azx_has_pm_runसमय(chip) \
	((chip)->driver_caps & AZX_DCAPS_PM_RUNTIME)

/* PCM setup */
अटल अंतरभूत काष्ठा azx_dev *get_azx_dev(काष्ठा snd_pcm_substream *substream)
अणु
	वापस substream->runसमय->निजी_data;
पूर्ण
अचिन्हित पूर्णांक azx_get_position(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev);
अचिन्हित पूर्णांक azx_get_pos_lpib(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev);
अचिन्हित पूर्णांक azx_get_pos_posbuf(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev);

/* Stream control. */
व्योम azx_stop_all_streams(काष्ठा azx *chip);

/* Allocation functions. */
#घोषणा azx_alloc_stream_pages(chip) \
	snd_hdac_bus_alloc_stream_pages(azx_bus(chip))
#घोषणा azx_मुक्त_stream_pages(chip) \
	snd_hdac_bus_मुक्त_stream_pages(azx_bus(chip))

/* Low level azx पूर्णांकerface */
व्योम azx_init_chip(काष्ठा azx *chip, bool full_reset);
व्योम azx_stop_chip(काष्ठा azx *chip);
#घोषणा azx_enter_link_reset(chip) \
	snd_hdac_bus_enter_link_reset(azx_bus(chip))
irqवापस_t azx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/* Codec पूर्णांकerface */
पूर्णांक azx_bus_init(काष्ठा azx *chip, स्थिर अक्षर *model);
पूर्णांक azx_probe_codecs(काष्ठा azx *chip, अचिन्हित पूर्णांक max_slots);
पूर्णांक azx_codec_configure(काष्ठा azx *chip);
पूर्णांक azx_init_streams(काष्ठा azx *chip);
व्योम azx_मुक्त_streams(काष्ठा azx *chip);

#पूर्ण_अगर /* __SOUND_HDA_CONTROLLER_H */
