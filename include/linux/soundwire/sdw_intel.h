<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/* Copyright(c) 2015-17 Intel Corporation. */

#अगर_अघोषित __SDW_INTEL_H
#घोषणा __SDW_INTEL_H

#समावेश <linux/irqवापस.h>
#समावेश <linux/soundwire/sdw.h>

/**
 * काष्ठा sdw_पूर्णांकel_stream_params_data: configuration passed during
 * the @params_stream callback, e.g. क्रम पूर्णांकeraction with DSP
 * firmware.
 */
काष्ठा sdw_पूर्णांकel_stream_params_data अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_soc_dai *dai;
	काष्ठा snd_pcm_hw_params *hw_params;
	पूर्णांक link_id;
	पूर्णांक alh_stream_id;
पूर्ण;

/**
 * काष्ठा sdw_पूर्णांकel_stream_मुक्त_data: configuration passed during
 * the @मुक्त_stream callback, e.g. क्रम पूर्णांकeraction with DSP
 * firmware.
 */
काष्ठा sdw_पूर्णांकel_stream_मुक्त_data अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक link_id;
पूर्ण;

/**
 * काष्ठा sdw_पूर्णांकel_ops: Intel audio driver callback ops
 *
 */
काष्ठा sdw_पूर्णांकel_ops अणु
	पूर्णांक (*params_stream)(काष्ठा device *dev,
			     काष्ठा sdw_पूर्णांकel_stream_params_data *params_data);
	पूर्णांक (*मुक्त_stream)(काष्ठा device *dev,
			   काष्ठा sdw_पूर्णांकel_stream_मुक्त_data *मुक्त_data);
पूर्ण;

/**
 * काष्ठा sdw_पूर्णांकel_acpi_info - Soundwire Intel inक्रमmation found in ACPI tables
 * @handle: ACPI controller handle
 * @count: link count found with "sdw-master-count" property
 * @link_mask: bit-wise mask listing links enabled by BIOS menu
 *
 * this काष्ठाure could be expanded to e.g. provide all the _ADR
 * inक्रमmation in हाल the link_mask is not sufficient to identअगरy
 * platक्रमm capabilities.
 */
काष्ठा sdw_पूर्णांकel_acpi_info अणु
	acpi_handle handle;
	पूर्णांक count;
	u32 link_mask;
पूर्ण;

काष्ठा sdw_पूर्णांकel_link_res;

/* Intel घड़ी-stop/pm_runसमय quirk definitions */

/*
 * Force the घड़ी to reमुख्य on during pm_runसमय suspend. This might
 * be needed अगर Slave devices करो not have an alternate घड़ी source or
 * अगर the latency requirements are very strict.
 */
#घोषणा SDW_INTEL_CLK_STOP_NOT_ALLOWED		BIT(0)

/*
 * Stop the bus during pm_runसमय suspend. If set, a complete bus
 * reset and re-क्रमागतeration will be perक्रमmed when the bus
 * restarts. This mode shall not be used अगर Slave devices can generate
 * in-band wakes.
 */
#घोषणा SDW_INTEL_CLK_STOP_TEARDOWN		BIT(1)

/*
 * Stop the bus during pm_suspend अगर Slaves are not wake capable
 * (e.g. speaker amplअगरiers). The घड़ी-stop mode is typically
 * slightly higher घातer than when the IP is completely घातered-off.
 */
#घोषणा SDW_INTEL_CLK_STOP_WAKE_CAPABLE_ONLY	BIT(2)

/*
 * Require a bus reset (and complete re-क्रमागतeration) when निकासing
 * घड़ी stop modes. This may be needed अगर the controller घातer was
 * turned off and all context lost. This quirk shall not be used अगर a
 * Slave device needs to reमुख्य क्रमागतerated and keep its context,
 * e.g. to provide the reasons क्रम the wake, report acoustic events or
 * pass a history buffer.
 */
#घोषणा SDW_INTEL_CLK_STOP_BUS_RESET		BIT(3)

काष्ठा sdw_पूर्णांकel_slave_id अणु
	पूर्णांक link_id;
	काष्ठा sdw_slave_id id;
पूर्ण;

/**
 * काष्ठा sdw_पूर्णांकel_ctx - context allocated by the controller
 * driver probe
 * @count: link count
 * @mmio_base: mmio base of SoundWire रेजिस्टरs, only used to check
 * hardware capabilities after all घातer dependencies are settled.
 * @link_mask: bit-wise mask listing SoundWire links reported by the
 * Controller
 * @num_slaves: total number of devices exposed across all enabled links
 * @handle: ACPI parent handle
 * @links: inक्रमmation क्रम each link (controller-specअगरic and kept
 * opaque here)
 * @ids: array of slave_id, representing Slaves exposed across all enabled
 * links
 * @link_list: list to handle पूर्णांकerrupts across all links
 * @shim_lock: mutex to handle concurrent rmw access to shared SHIM रेजिस्टरs.
 * @shim_mask: flags to track initialization of SHIM shared रेजिस्टरs
 */
काष्ठा sdw_पूर्णांकel_ctx अणु
	पूर्णांक count;
	व्योम __iomem *mmio_base;
	u32 link_mask;
	पूर्णांक num_slaves;
	acpi_handle handle;
	काष्ठा sdw_पूर्णांकel_link_res *links;
	काष्ठा sdw_पूर्णांकel_slave_id *ids;
	काष्ठा list_head link_list;
	काष्ठा mutex shim_lock; /* lock क्रम access to shared SHIM रेजिस्टरs */
	u32 shim_mask;
पूर्ण;

/**
 * काष्ठा sdw_पूर्णांकel_res - Soundwire Intel global resource काष्ठाure,
 * typically populated by the DSP driver
 *
 * @count: link count
 * @mmio_base: mmio base of SoundWire रेजिस्टरs
 * @irq: पूर्णांकerrupt number
 * @handle: ACPI parent handle
 * @parent: parent device
 * @ops: callback ops
 * @dev: device implementing hwparams and मुक्त callbacks
 * @link_mask: bit-wise mask listing links selected by the DSP driver
 * This mask may be a subset of the one reported by the controller since
 * machine-specअगरic quirks are handled in the DSP driver.
 * @घड़ी_stop_quirks: mask array of possible behaviors requested by the
 * DSP driver. The quirks are common क्रम all links क्रम now.
 */
काष्ठा sdw_पूर्णांकel_res अणु
	पूर्णांक count;
	व्योम __iomem *mmio_base;
	पूर्णांक irq;
	acpi_handle handle;
	काष्ठा device *parent;
	स्थिर काष्ठा sdw_पूर्णांकel_ops *ops;
	काष्ठा device *dev;
	u32 link_mask;
	u32 घड़ी_stop_quirks;
पूर्ण;

/*
 * On Intel platक्रमms, the SoundWire IP has dependencies on घातer
 * rails shared with the DSP, and the initialization steps are split
 * in three. First an ACPI scan to check what the firmware describes
 * in DSDT tables, then an allocation step (with no hardware
 * configuration but with all the relevant devices created) and last
 * the actual hardware configuration. The final stage is a global
 * पूर्णांकerrupt enable which is controlled by the DSP driver. Splitting
 * these phases helps simplअगरy the boot flow and make early decisions
 * on e.g. which machine driver to select (I2S mode, HDaudio or
 * SoundWire).
 */
पूर्णांक sdw_पूर्णांकel_acpi_scan(acpi_handle *parent_handle,
			काष्ठा sdw_पूर्णांकel_acpi_info *info);

व्योम sdw_पूर्णांकel_process_wakeen_event(काष्ठा sdw_पूर्णांकel_ctx *ctx);

काष्ठा sdw_पूर्णांकel_ctx *
sdw_पूर्णांकel_probe(काष्ठा sdw_पूर्णांकel_res *res);

पूर्णांक sdw_पूर्णांकel_startup(काष्ठा sdw_पूर्णांकel_ctx *ctx);

व्योम sdw_पूर्णांकel_निकास(काष्ठा sdw_पूर्णांकel_ctx *ctx);

व्योम sdw_पूर्णांकel_enable_irq(व्योम __iomem *mmio_base, bool enable);

irqवापस_t sdw_पूर्णांकel_thपढ़ो(पूर्णांक irq, व्योम *dev_id);

#घोषणा SDW_INTEL_QUIRK_MASK_BUS_DISABLE      BIT(1)

#पूर्ण_अगर
