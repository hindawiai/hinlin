<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/* Copyright(c) 2015-17 Intel Corporation. */
#समावेश <sound/soc.h>

#अगर_अघोषित __SDW_CADENCE_H
#घोषणा __SDW_CADENCE_H

#घोषणा SDW_CADENCE_GSYNC_KHZ		4 /* 4 kHz */
#घोषणा SDW_CADENCE_GSYNC_HZ		(SDW_CADENCE_GSYNC_KHZ * 1000)

/**
 * काष्ठा sdw_cdns_pdi: PDI (Physical Data Interface) instance
 *
 * @num: pdi number
 * @पूर्णांकel_alh_id: link identअगरier
 * @l_ch_num: low channel क्रम PDI
 * @h_ch_num: high channel क्रम PDI
 * @ch_count: total channel count क्रम PDI
 * @dir: data direction
 * @type: stream type, PDM or PCM
 */
काष्ठा sdw_cdns_pdi अणु
	पूर्णांक num;
	पूर्णांक पूर्णांकel_alh_id;
	पूर्णांक l_ch_num;
	पूर्णांक h_ch_num;
	पूर्णांक ch_count;
	क्रमागत sdw_data_direction dir;
	क्रमागत sdw_stream_type type;
पूर्ण;

/**
 * काष्ठा sdw_cdns_streams: Cadence stream data काष्ठाure
 *
 * @num_bd: number of bidirectional streams
 * @num_in: number of input streams
 * @num_out: number of output streams
 * @num_ch_bd: number of bidirectional stream channels
 * @num_ch_bd: number of input stream channels
 * @num_ch_bd: number of output stream channels
 * @num_pdi: total number of PDIs
 * @bd: bidirectional streams
 * @in: input streams
 * @out: output streams
 */
काष्ठा sdw_cdns_streams अणु
	अचिन्हित पूर्णांक num_bd;
	अचिन्हित पूर्णांक num_in;
	अचिन्हित पूर्णांक num_out;
	अचिन्हित पूर्णांक num_ch_bd;
	अचिन्हित पूर्णांक num_ch_in;
	अचिन्हित पूर्णांक num_ch_out;
	अचिन्हित पूर्णांक num_pdi;
	काष्ठा sdw_cdns_pdi *bd;
	काष्ठा sdw_cdns_pdi *in;
	काष्ठा sdw_cdns_pdi *out;
पूर्ण;

/**
 * काष्ठा sdw_cdns_stream_config: stream configuration
 *
 * @pcm_bd: number of bidirectional PCM streams supported
 * @pcm_in: number of input PCM streams supported
 * @pcm_out: number of output PCM streams supported
 * @pdm_bd: number of bidirectional PDM streams supported
 * @pdm_in: number of input PDM streams supported
 * @pdm_out: number of output PDM streams supported
 */
काष्ठा sdw_cdns_stream_config अणु
	अचिन्हित पूर्णांक pcm_bd;
	अचिन्हित पूर्णांक pcm_in;
	अचिन्हित पूर्णांक pcm_out;
	अचिन्हित पूर्णांक pdm_bd;
	अचिन्हित पूर्णांक pdm_in;
	अचिन्हित पूर्णांक pdm_out;
पूर्ण;

/**
 * काष्ठा sdw_cdns_dma_data: Cadence DMA data
 *
 * @name: SoundWire stream name
 * @stream: stream runसमय
 * @pdi: PDI used क्रम this dai
 * @bus: Bus handle
 * @stream_type: Stream type
 * @link_id: Master link id
 * @hw_params: hw_params to be applied in .prepare step
 * @suspended: status set when suspended, to be used in .prepare
 */
काष्ठा sdw_cdns_dma_data अणु
	अक्षर *name;
	काष्ठा sdw_stream_runसमय *stream;
	काष्ठा sdw_cdns_pdi *pdi;
	काष्ठा sdw_bus *bus;
	क्रमागत sdw_stream_type stream_type;
	पूर्णांक link_id;
	काष्ठा snd_pcm_hw_params *hw_params;
	bool suspended;
पूर्ण;

/**
 * काष्ठा sdw_cdns - Cadence driver context
 * @dev: Linux device
 * @bus: Bus handle
 * @instance: instance number
 * @response_buf: SoundWire response buffer
 * @tx_complete: Tx completion
 * @defer: Defer poपूर्णांकer
 * @ports: Data ports
 * @num_ports: Total number of data ports
 * @pcm: PCM streams
 * @pdm: PDM streams
 * @रेजिस्टरs: Cadence रेजिस्टरs
 * @link_up: Link status
 * @msg_count: Messages sent on bus
 */
काष्ठा sdw_cdns अणु
	काष्ठा device *dev;
	काष्ठा sdw_bus bus;
	अचिन्हित पूर्णांक instance;

	u32 response_buf[0x80];
	काष्ठा completion tx_complete;
	काष्ठा sdw_defer *defer;

	काष्ठा sdw_cdns_port *ports;
	पूर्णांक num_ports;

	काष्ठा sdw_cdns_streams pcm;
	काष्ठा sdw_cdns_streams pdm;

	व्योम __iomem *रेजिस्टरs;

	bool link_up;
	अचिन्हित पूर्णांक msg_count;
	bool पूर्णांकerrupt_enabled;

	काष्ठा work_काष्ठा work;

	काष्ठा list_head list;
पूर्ण;

#घोषणा bus_to_cdns(_bus) container_of(_bus, काष्ठा sdw_cdns, bus)

/* Exported symbols */

पूर्णांक sdw_cdns_probe(काष्ठा sdw_cdns *cdns);
बाह्य काष्ठा sdw_master_ops sdw_cdns_master_ops;

irqवापस_t sdw_cdns_irq(पूर्णांक irq, व्योम *dev_id);
irqवापस_t sdw_cdns_thपढ़ो(पूर्णांक irq, व्योम *dev_id);

पूर्णांक sdw_cdns_init(काष्ठा sdw_cdns *cdns);
पूर्णांक sdw_cdns_pdi_init(काष्ठा sdw_cdns *cdns,
		      काष्ठा sdw_cdns_stream_config config);
पूर्णांक sdw_cdns_निकास_reset(काष्ठा sdw_cdns *cdns);
पूर्णांक sdw_cdns_enable_पूर्णांकerrupt(काष्ठा sdw_cdns *cdns, bool state);

bool sdw_cdns_is_घड़ी_stop(काष्ठा sdw_cdns *cdns);
पूर्णांक sdw_cdns_घड़ी_stop(काष्ठा sdw_cdns *cdns, bool block_wake);
पूर्णांक sdw_cdns_घड़ी_restart(काष्ठा sdw_cdns *cdns, bool bus_reset);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम sdw_cdns_debugfs_init(काष्ठा sdw_cdns *cdns, काष्ठा dentry *root);
#पूर्ण_अगर

काष्ठा sdw_cdns_pdi *sdw_cdns_alloc_pdi(काष्ठा sdw_cdns *cdns,
					काष्ठा sdw_cdns_streams *stream,
					u32 ch, u32 dir, पूर्णांक dai_id);
व्योम sdw_cdns_config_stream(काष्ठा sdw_cdns *cdns,
			    u32 ch, u32 dir, काष्ठा sdw_cdns_pdi *pdi);

क्रमागत sdw_command_response
cdns_reset_page_addr(काष्ठा sdw_bus *bus, अचिन्हित पूर्णांक dev_num);

क्रमागत sdw_command_response
cdns_xfer_msg(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg);

क्रमागत sdw_command_response
cdns_xfer_msg_defer(काष्ठा sdw_bus *bus,
		    काष्ठा sdw_msg *msg, काष्ठा sdw_defer *defer);

क्रमागत sdw_command_response
cdns_reset_page_addr(काष्ठा sdw_bus *bus, अचिन्हित पूर्णांक dev_num);

पूर्णांक cdns_bus_conf(काष्ठा sdw_bus *bus, काष्ठा sdw_bus_params *params);

पूर्णांक cdns_set_sdw_stream(काष्ठा snd_soc_dai *dai,
			व्योम *stream, bool pcm, पूर्णांक direction);
#पूर्ण_अगर /* __SDW_CADENCE_H */
