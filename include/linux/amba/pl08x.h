<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/amba/pl08x.h - ARM PrimeCell DMA Controller driver
 *
 * Copyright (C) 2005 ARM Ltd
 * Copyright (C) 2010 ST-Ericsson SA
 *
 * pl08x inक्रमmation required by platक्रमm code
 *
 * Please credit ARM.com
 * Documentation: ARM DDI 0196D
 */

#अगर_अघोषित AMBA_PL08X_H
#घोषणा AMBA_PL08X_H

/* We need sizes of काष्ठाs from this header */
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा pl08x_driver_data;
काष्ठा pl08x_phy_chan;
काष्ठा pl08x_txd;

/* Biपंचांगasks क्रम selecting AHB ports क्रम DMA transfers */
क्रमागत अणु
	PL08X_AHB1 = (1 << 0),
	PL08X_AHB2 = (1 << 1)
पूर्ण;

/**
 * काष्ठा pl08x_channel_data - data काष्ठाure to pass info between
 * platक्रमm and PL08x driver regarding channel configuration
 * @bus_id: name of this device channel, not just a device name since
 * devices may have more than one channel e.g. "foo_tx"
 * @min_संकेत: the minimum DMA संकेत number to be muxed in क्रम this
 * channel (क्रम platक्रमms supporting muxed संकेतs). If you have
 * अटल assignments, make sure this is set to the asचिन्हित संकेत
 * number, PL08x have 16 possible संकेतs in number 0 thru 15 so
 * when these are not enough they often get muxed (in hardware)
 * disabling simultaneous use of the same channel क्रम two devices.
 * @max_संकेत: the maximum DMA संकेत number to be muxed in क्रम
 * the channel. Set to the same as min_संकेत क्रम
 * devices with अटल assignments
 * @muxval: a number usually used to poke पूर्णांकo some mux regiser to
 * mux in the संकेत to this channel
 * @addr: source/target address in physical memory क्रम this DMA channel,
 * can be the address of a FIFO रेजिस्टर क्रम burst requests क्रम example.
 * This can be left undefined अगर the PrimeCell API is used क्रम configuring
 * this.
 * @single: the device connected to this channel will request single DMA
 * transfers, not bursts. (Bursts are शेष.)
 * @periph_buses: the device connected to this channel is accessible via
 * these buses (use PL08X_AHB1 | PL08X_AHB2).
 */
काष्ठा pl08x_channel_data अणु
	स्थिर अक्षर *bus_id;
	पूर्णांक min_संकेत;
	पूर्णांक max_संकेत;
	u32 muxval;
	dma_addr_t addr;
	bool single;
	u8 periph_buses;
पूर्ण;

क्रमागत pl08x_burst_size अणु
	PL08X_BURST_SZ_1,
	PL08X_BURST_SZ_4,
	PL08X_BURST_SZ_8,
	PL08X_BURST_SZ_16,
	PL08X_BURST_SZ_32,
	PL08X_BURST_SZ_64,
	PL08X_BURST_SZ_128,
	PL08X_BURST_SZ_256,
पूर्ण;

क्रमागत pl08x_bus_width अणु
	PL08X_BUS_WIDTH_8_BITS,
	PL08X_BUS_WIDTH_16_BITS,
	PL08X_BUS_WIDTH_32_BITS,
पूर्ण;

/**
 * काष्ठा pl08x_platक्रमm_data - the platक्रमm configuration क्रम the PL08x
 * PrimeCells.
 * @slave_channels: the channels defined क्रम the dअगरferent devices on the
 * platक्रमm, all inclusive, including multiplexed channels. The available
 * physical channels will be multiplexed around these संकेतs as they are
 * requested, just क्रमागतerate all possible channels.
 * @num_slave_channels: number of elements in the slave channel array
 * @स_नकल_burst_size: the appropriate burst size क्रम स_नकल operations
 * @स_नकल_bus_width: memory bus width
 * @स_नकल_prot_buff: whether स_नकल DMA is bufferable
 * @स_नकल_prot_cache: whether स_नकल DMA is cacheable
 * @get_xfer_संकेत: request a physical संकेत to be used क्रम a DMA transfer
 * immediately: अगर there is some multiplexing or similar blocking the use
 * of the channel the transfer can be denied by वापसing less than zero,
 * अन्यथा it वापसs the allocated संकेत number
 * @put_xfer_संकेत: indicate to the platक्रमm that this physical संकेत is not
 * running any DMA transfer and multiplexing can be recycled
 * @lli_buses: buses which LLIs can be fetched from: PL08X_AHB1 | PL08X_AHB2
 * @mem_buses: buses which memory can be accessed from: PL08X_AHB1 | PL08X_AHB2
 * @slave_map: DMA slave matching table
 * @slave_map_len: number of elements in @slave_map
 */
काष्ठा pl08x_platक्रमm_data अणु
	काष्ठा pl08x_channel_data *slave_channels;
	अचिन्हित पूर्णांक num_slave_channels;
	क्रमागत pl08x_burst_size स_नकल_burst_size;
	क्रमागत pl08x_bus_width स_नकल_bus_width;
	bool स_नकल_prot_buff;
	bool स_नकल_prot_cache;
	पूर्णांक (*get_xfer_संकेत)(स्थिर काष्ठा pl08x_channel_data *);
	व्योम (*put_xfer_संकेत)(स्थिर काष्ठा pl08x_channel_data *, पूर्णांक);
	u8 lli_buses;
	u8 mem_buses;
	स्थिर काष्ठा dma_slave_map *slave_map;
	पूर्णांक slave_map_len;
पूर्ण;

#अगर_घोषित CONFIG_AMBA_PL08X
bool pl08x_filter_id(काष्ठा dma_chan *chan, व्योम *chan_id);
#अन्यथा
अटल अंतरभूत bool pl08x_filter_id(काष्ठा dma_chan *chan, व्योम *chan_id)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* AMBA_PL08X_H */
