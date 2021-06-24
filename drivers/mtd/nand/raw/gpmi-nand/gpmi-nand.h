<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Freescale GPMI न_अंकD Flash Driver
 *
 * Copyright (C) 2010-2011 Freescale Semiconductor, Inc.
 * Copyright (C) 2008 Embedded Alley Solutions, Inc.
 */
#अगर_अघोषित __DRIVERS_MTD_न_अंकD_GPMI_न_अंकD_H
#घोषणा __DRIVERS_MTD_न_अंकD_GPMI_न_अंकD_H

#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>

#घोषणा GPMI_CLK_MAX 5 /* MX6Q needs five घड़ीs */
काष्ठा resources अणु
	व्योम __iomem  *gpmi_regs;
	व्योम __iomem  *bch_regs;
	अचिन्हित पूर्णांक  dma_low_channel;
	अचिन्हित पूर्णांक  dma_high_channel;
	काष्ठा clk    *घड़ी[GPMI_CLK_MAX];
पूर्ण;

/**
 * काष्ठा bch_geometry - BCH geometry description.
 * @gf_len:                   The length of Galois Field. (e.g., 13 or 14)
 * @ecc_strength:             A number that describes the strength of the ECC
 *                            algorithm.
 * @page_size:                The size, in bytes, of a physical page, including
 *                            both data and OOB.
 * @metadata_size:            The size, in bytes, of the metadata.
 * @ecc_chunk_size:           The size, in bytes, of a single ECC chunk. Note
 *                            the first chunk in the page includes both data and
 *                            metadata, so it's a bit larger than this value.
 * @ecc_chunk_count:          The number of ECC chunks in the page,
 * @payload_size:             The size, in bytes, of the payload buffer.
 * @auxiliary_size:           The size, in bytes, of the auxiliary buffer.
 * @auxiliary_status_offset:  The offset पूर्णांकo the auxiliary buffer at which
 *                            the ECC status appears.
 * @block_mark_byte_offset:   The byte offset in the ECC-based page view at
 *                            which the underlying physical block mark appears.
 * @block_mark_bit_offset:    The bit offset पूर्णांकo the ECC-based page view at
 *                            which the underlying physical block mark appears.
 */
काष्ठा bch_geometry अणु
	अचिन्हित पूर्णांक  gf_len;
	अचिन्हित पूर्णांक  ecc_strength;
	अचिन्हित पूर्णांक  page_size;
	अचिन्हित पूर्णांक  metadata_size;
	अचिन्हित पूर्णांक  ecc_chunk_size;
	अचिन्हित पूर्णांक  ecc_chunk_count;
	अचिन्हित पूर्णांक  payload_size;
	अचिन्हित पूर्णांक  auxiliary_size;
	अचिन्हित पूर्णांक  auxiliary_status_offset;
	अचिन्हित पूर्णांक  block_mark_byte_offset;
	अचिन्हित पूर्णांक  block_mark_bit_offset;
पूर्ण;

/**
 * काष्ठा boot_rom_geometry - Boot ROM geometry description.
 * @stride_size_in_pages:        The size of a boot block stride, in pages.
 * @search_area_stride_exponent: The logarithm to base 2 of the size of a
 *                               search area in boot block strides.
 */
काष्ठा boot_rom_geometry अणु
	अचिन्हित पूर्णांक  stride_size_in_pages;
	अचिन्हित पूर्णांक  search_area_stride_exponent;
पूर्ण;

क्रमागत gpmi_type अणु
	IS_MX23,
	IS_MX28,
	IS_MX6Q,
	IS_MX6SX,
	IS_MX7D,
पूर्ण;

काष्ठा gpmi_devdata अणु
	क्रमागत gpmi_type type;
	पूर्णांक bch_max_ecc_strength;
	पूर्णांक max_chain_delay; /* See the async EDO mode */
	स्थिर अक्षर * स्थिर *clks;
	स्थिर पूर्णांक clks_count;
पूर्ण;

/**
 * काष्ठा gpmi_nfc_hardware_timing - GPMI hardware timing parameters.
 * @must_apply_timings:        Whether controller timings have alपढ़ोy been
 *                             applied or not (useful only जबतक there is
 *                             support क्रम only one chip select)
 * @clk_rate:                  The घड़ी rate that must be used to derive the
 *                             following parameters
 * @timing0:                   HW_GPMI_TIMING0 रेजिस्टर
 * @timing1:                   HW_GPMI_TIMING1 रेजिस्टर
 * @ctrl1n:                    HW_GPMI_CTRL1n रेजिस्टर
 */
काष्ठा gpmi_nfc_hardware_timing अणु
	bool must_apply_timings;
	अचिन्हित दीर्घ पूर्णांक clk_rate;
	u32 timing0;
	u32 timing1;
	u32 ctrl1n;
पूर्ण;

#घोषणा GPMI_MAX_TRANSFERS	8

काष्ठा gpmi_transfer अणु
	u8 cmdbuf[8];
	काष्ठा scatterlist sgl;
	क्रमागत dma_data_direction direction;
पूर्ण;

काष्ठा gpmi_nand_data अणु
	/* Devdata */
	स्थिर काष्ठा gpmi_devdata *devdata;

	/* System Interface */
	काष्ठा device		*dev;
	काष्ठा platक्रमm_device	*pdev;

	/* Resources */
	काष्ठा resources	resources;

	/* Flash Hardware */
	काष्ठा gpmi_nfc_hardware_timing hw;

	/* BCH */
	काष्ठा bch_geometry	bch_geometry;
	काष्ठा completion	bch_करोne;

	/* न_अंकD Boot issue */
	bool			swap_block_mark;
	काष्ठा boot_rom_geometry rom_geometry;

	/* MTD / न_अंकD */
	काष्ठा nand_controller	base;
	काष्ठा nand_chip	nand;

	काष्ठा gpmi_transfer	transfers[GPMI_MAX_TRANSFERS];
	पूर्णांक			ntransfers;

	bool			bch;
	uपूर्णांक32_t		bch_flashlayout0;
	uपूर्णांक32_t		bch_flashlayout1;

	अक्षर			*data_buffer_dma;

	व्योम			*auxiliary_virt;
	dma_addr_t		auxiliary_phys;

	व्योम			*raw_buffer;

	/* DMA channels */
#घोषणा DMA_CHANS		8
	काष्ठा dma_chan		*dma_chans[DMA_CHANS];
	काष्ठा completion	dma_करोne;
पूर्ण;

/* BCH : Status Block Completion Codes */
#घोषणा STATUS_GOOD		0x00
#घोषणा STATUS_ERASED		0xff
#घोषणा STATUS_UNCORRECTABLE	0xfe

/* Use the devdata to distinguish dअगरferent Archs. */
#घोषणा GPMI_IS_MX23(x)		((x)->devdata->type == IS_MX23)
#घोषणा GPMI_IS_MX28(x)		((x)->devdata->type == IS_MX28)
#घोषणा GPMI_IS_MX6Q(x)		((x)->devdata->type == IS_MX6Q)
#घोषणा GPMI_IS_MX6SX(x)	((x)->devdata->type == IS_MX6SX)
#घोषणा GPMI_IS_MX7D(x)		((x)->devdata->type == IS_MX7D)

#घोषणा GPMI_IS_MX6(x)		(GPMI_IS_MX6Q(x) || GPMI_IS_MX6SX(x) || \
				 GPMI_IS_MX7D(x))
#घोषणा GPMI_IS_MXS(x)		(GPMI_IS_MX23(x) || GPMI_IS_MX28(x))
#पूर्ण_अगर
