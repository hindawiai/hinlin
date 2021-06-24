<शैली गुरु>
/*
 * PMC-Sierra 8001/8081/8088/8089 SAS/SATA based host adapters driver
 *
 * Copyright (c) 2008-2009 USI Co., Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */

#अगर_अघोषित _PM8001_DEFS_H_
#घोषणा _PM8001_DEFS_H_

क्रमागत chip_flavors अणु
	chip_8001,
	chip_8008,
	chip_8009,
	chip_8018,
	chip_8019,
	chip_8074,
	chip_8076,
	chip_8077,
	chip_8006,
	chip_8070,
	chip_8072
पूर्ण;

क्रमागत phy_speed अणु
	PHY_SPEED_15 = 0x01,
	PHY_SPEED_30 = 0x02,
	PHY_SPEED_60 = 0x04,
	PHY_SPEED_120 = 0x08,
पूर्ण;

क्रमागत data_direction अणु
	DATA_सूची_NONE = 0x0,	/* NO TRANSFER */
	DATA_सूची_IN = 0x01,	/* INBOUND */
	DATA_सूची_OUT = 0x02,	/* OUTBOUND */
	DATA_सूची_BYRECIPIENT = 0x04, /* UNSPECIFIED */
पूर्ण;

क्रमागत port_type अणु
	PORT_TYPE_SAS = (1L << 1),
	PORT_TYPE_SATA = (1L << 0),
पूर्ण;

/* driver compile-समय configuration */
#घोषणा	PM8001_MAX_CCB		 1024	/* max ccbs supported */
#घोषणा PM8001_MPI_QUEUE         1024   /* maximum mpi queue entries */
#घोषणा	PM8001_MAX_INB_NUM	 64
#घोषणा	PM8001_MAX_OUTB_NUM	 64
#घोषणा	PM8001_CAN_QUEUE	 508	/* SCSI Queue depth */

/* Inbound/Outbound queue size */
#घोषणा IOMB_SIZE_SPC		64
#घोषणा IOMB_SIZE_SPCV		128

/* unchangeable hardware details */
#घोषणा	PM8001_MAX_PHYS		 16	/* max. possible phys */
#घोषणा	PM8001_MAX_PORTS	 16	/* max. possible ports */
#घोषणा	PM8001_MAX_DEVICES	 2048	/* max supported device */
#घोषणा	PM8001_MAX_MSIX_VEC	 64	/* max msi-x पूर्णांक क्रम spcv/ve */
#घोषणा	PM8001_RESERVE_SLOT	 8

#घोषणा	CONFIG_SCSI_PM8001_MAX_DMA_SG	528
#घोषणा PM8001_MAX_DMA_SG	CONFIG_SCSI_PM8001_MAX_DMA_SG

क्रमागत memory_region_num अणु
	AAP1 = 0x0, /* application acceleration processor */
	IOP,	    /* IO processor */
	NVMD,	    /* NVM device */
	FW_FLASH,    /* memory क्रम fw flash update */
	FORENSIC_MEM,  /* memory क्रम fw क्रमensic data */
	USI_MAX_MEMCNT_BASE
पूर्ण;
#घोषणा	PM8001_EVENT_LOG_SIZE	 (128 * 1024)

/**
 * maximum DMA memory regions(number of IBQ + number of IBQ CI
 * + number of  OBQ + number of OBQ PI)
 */
#घोषणा USI_MAX_MEMCNT	(USI_MAX_MEMCNT_BASE + ((2 * PM8001_MAX_INB_NUM) \
			+ (2 * PM8001_MAX_OUTB_NUM)))
/*error code*/
क्रमागत mpi_err अणु
	MPI_IO_STATUS_SUCCESS = 0x0,
	MPI_IO_STATUS_BUSY = 0x01,
	MPI_IO_STATUS_FAIL = 0x02,
पूर्ण;

/**
 * Phy Control स्थिरants
 */
क्रमागत phy_control_type अणु
	PHY_LINK_RESET = 0x01,
	PHY_HARD_RESET = 0x02,
	PHY_NOTIFY_ENABLE_SPINUP = 0x10,
पूर्ण;

क्रमागत pm8001_hba_info_flags अणु
	PM8001F_INIT_TIME	= (1U << 0),
	PM8001F_RUN_TIME	= (1U << 1),
पूर्ण;

/**
 * Phy Status
 */
#घोषणा PHY_LINK_DISABLE	0x00
#घोषणा PHY_LINK_DOWN		0x01
#घोषणा PHY_STATE_LINK_UP_SPCV	0x2
#घोषणा PHY_STATE_LINK_UP_SPC	0x1

#पूर्ण_अगर
