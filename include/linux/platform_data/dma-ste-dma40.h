<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2007-2010
 * Author: Per Forlin <per.क्रमlin@stericsson.com> क्रम ST-Ericsson
 * Author: Jonas Aaberg <jonas.aberg@stericsson.com> क्रम ST-Ericsson
 */


#अगर_अघोषित STE_DMA40_H
#घोषणा STE_DMA40_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>

/*
 * Maxium size क्रम a single dma descriptor
 * Size is limited to 16 bits.
 * Size is in the units of addr-widths (1,2,4,8 bytes)
 * Larger transfers will be split up to multiple linked desc
 */
#घोषणा STEDMA40_MAX_SEG_SIZE 0xFFFF

/* dev types क्रम स_नकल */
#घोषणा STEDMA40_DEV_DST_MEMORY (-1)
#घोषणा	STEDMA40_DEV_SRC_MEMORY (-1)

क्रमागत stedma40_mode अणु
	STEDMA40_MODE_LOGICAL = 0,
	STEDMA40_MODE_PHYSICAL,
	STEDMA40_MODE_OPERATION,
पूर्ण;

क्रमागत stedma40_mode_opt अणु
	STEDMA40_PCHAN_BASIC_MODE = 0,
	STEDMA40_LCHAN_SRC_LOG_DST_LOG = 0,
	STEDMA40_PCHAN_MODULO_MODE,
	STEDMA40_PCHAN_DOUBLE_DST_MODE,
	STEDMA40_LCHAN_SRC_PHY_DST_LOG,
	STEDMA40_LCHAN_SRC_LOG_DST_PHY,
पूर्ण;

#घोषणा STEDMA40_ESIZE_8_BIT  0x0
#घोषणा STEDMA40_ESIZE_16_BIT 0x1
#घोषणा STEDMA40_ESIZE_32_BIT 0x2
#घोषणा STEDMA40_ESIZE_64_BIT 0x3

/* The value 4 indicates that PEN-reg shall be set to 0 */
#घोषणा STEDMA40_PSIZE_PHY_1  0x4
#घोषणा STEDMA40_PSIZE_PHY_2  0x0
#घोषणा STEDMA40_PSIZE_PHY_4  0x1
#घोषणा STEDMA40_PSIZE_PHY_8  0x2
#घोषणा STEDMA40_PSIZE_PHY_16 0x3

/*
 * The number of elements dअगरfer in logical and
 * physical mode
 */
#घोषणा STEDMA40_PSIZE_LOG_1  STEDMA40_PSIZE_PHY_2
#घोषणा STEDMA40_PSIZE_LOG_4  STEDMA40_PSIZE_PHY_4
#घोषणा STEDMA40_PSIZE_LOG_8  STEDMA40_PSIZE_PHY_8
#घोषणा STEDMA40_PSIZE_LOG_16 STEDMA40_PSIZE_PHY_16

/* Maximum number of possible physical channels */
#घोषणा STEDMA40_MAX_PHYS 32

क्रमागत stedma40_flow_ctrl अणु
	STEDMA40_NO_FLOW_CTRL,
	STEDMA40_FLOW_CTRL,
पूर्ण;

/**
 * काष्ठा stedma40_half_channel_info - dst/src channel configuration
 *
 * @big_endian: true अगर the src/dst should be पढ़ो as big endian
 * @data_width: Data width of the src/dst hardware
 * @p_size: Burst size
 * @flow_ctrl: Flow control on/off.
 */
काष्ठा stedma40_half_channel_info अणु
	bool big_endian;
	क्रमागत dma_slave_buswidth data_width;
	पूर्णांक psize;
	क्रमागत stedma40_flow_ctrl flow_ctrl;
पूर्ण;

/**
 * काष्ठा stedma40_chan_cfg - Structure to be filled by client drivers.
 *
 * @dir: MEM 2 MEM, PERIPH 2 MEM , MEM 2 PERIPH, PERIPH 2 PERIPH
 * @high_priority: true अगर high-priority
 * @realसमय: true अगर realसमय mode is to be enabled.  Only available on DMA40
 * version 3+, i.e DB8500v2+
 * @mode: channel mode: physical, logical, or operation
 * @mode_opt: options क्रम the chosen channel mode
 * @dev_type: src/dst device type (driver uses dir to figure out which)
 * @src_info: Parameters क्रम dst half channel
 * @dst_info: Parameters क्रम dst half channel
 * @use_fixed_channel: अगर true, use physical channel specअगरied by phy_channel
 * @phy_channel: physical channel to use, only अगर use_fixed_channel is true
 *
 * This काष्ठाure has to be filled by the client drivers.
 * It is recommended to करो all dma configurations क्रम clients in the machine.
 *
 */
काष्ठा stedma40_chan_cfg अणु
	क्रमागत dma_transfer_direction		 dir;
	bool					 high_priority;
	bool					 realसमय;
	क्रमागत stedma40_mode			 mode;
	क्रमागत stedma40_mode_opt			 mode_opt;
	पूर्णांक					 dev_type;
	काष्ठा stedma40_half_channel_info	 src_info;
	काष्ठा stedma40_half_channel_info	 dst_info;

	bool					 use_fixed_channel;
	पूर्णांक					 phy_channel;
पूर्ण;

/**
 * काष्ठा stedma40_platक्रमm_data - Configuration काष्ठा क्रम the dma device.
 *
 * @dev_tx: mapping between destination event line and io address
 * @dev_rx: mapping between source event line and io address
 * @disabled_channels: A vector, ending with -1, that marks physical channels
 * that are क्रम dअगरferent reasons not available क्रम the driver.
 * @soft_lli_chans: A vector, that marks physical channels will use LLI by SW
 * which aव्योमs HW bug that exists in some versions of the controller.
 * SoftLLI पूर्णांकroduces relink overhead that could impact perक्रमmace क्रम
 * certain use हालs.
 * @num_of_soft_lli_chans: The number of channels that needs to be configured
 * to use SoftLLI.
 * @use_esram_lcla: flag क्रम mapping the lcla पूर्णांकo esram region
 * @num_of_स_नकल_chans: The number of channels reserved क्रम स_नकल.
 * @num_of_phy_chans: The number of physical channels implemented in HW.
 * 0 means पढ़ोing the number of channels from DMA HW but this is only valid
 * क्रम 'multiple of 4' channels, like 8.
 */
काष्ठा stedma40_platक्रमm_data अणु
	पूर्णांक				 disabled_channels[STEDMA40_MAX_PHYS];
	पूर्णांक				*soft_lli_chans;
	पूर्णांक				 num_of_soft_lli_chans;
	bool				 use_esram_lcla;
	पूर्णांक				 num_of_स_नकल_chans;
	पूर्णांक				 num_of_phy_chans;
पूर्ण;

#अगर_घोषित CONFIG_STE_DMA40

/**
 * stedma40_filter() - Provides stedma40_chan_cfg to the
 * ste_dma40 dma driver via the dmaengine framework.
 * करोes some checking of what's provided.
 *
 * Never directly called by client. It used by dmaengine.
 * @chan: dmaengine handle.
 * @data: Must be of type: काष्ठा stedma40_chan_cfg and is
 * the configuration of the framework.
 *
 *
 */

bool stedma40_filter(काष्ठा dma_chan *chan, व्योम *data);

/**
 * stedma40_slave_mem() - Transfers a raw data buffer to or from a slave
 * (=device)
 *
 * @chan: dmaengine handle
 * @addr: source or destination physicall address.
 * @size: bytes to transfer
 * @direction: direction of transfer
 * @flags: is actually क्रमागत dma_ctrl_flags. See dmaengine.h
 */

अटल अंतरभूत काष्ठा
dma_async_tx_descriptor *stedma40_slave_mem(काष्ठा dma_chan *chan,
					    dma_addr_t addr,
					    अचिन्हित पूर्णांक size,
					    क्रमागत dma_transfer_direction direction,
					    अचिन्हित दीर्घ flags)
अणु
	काष्ठा scatterlist sg;
	sg_init_table(&sg, 1);
	sg.dma_address = addr;
	sg.length = size;

	वापस dmaengine_prep_slave_sg(chan, &sg, 1, direction, flags);
पूर्ण

#अन्यथा
अटल अंतरभूत bool stedma40_filter(काष्ठा dma_chan *chan, व्योम *data)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा
dma_async_tx_descriptor *stedma40_slave_mem(काष्ठा dma_chan *chan,
					    dma_addr_t addr,
					    अचिन्हित पूर्णांक size,
					    क्रमागत dma_transfer_direction direction,
					    अचिन्हित दीर्घ flags)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
