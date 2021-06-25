<शैली गुरु>
/*
 * Adaptec AIC7xxx device driver क्रम Linux.
 *
 * Copyright (c) 1994 John Aycock
 *   The University of Calgary Deparपंचांगent of Computer Science.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, ग_लिखो to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * Copyright (c) 2000-2003 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic7xxx_osm.h#151 $
 *
 */
#अगर_अघोषित _AIC7XXX_LINUX_H_
#घोषणा _AIC7XXX_LINUX_H_

#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

/* Core SCSI definitions */
#घोषणा AIC_LIB_PREFIX ahc

#समावेश "cam.h"
#समावेश "queue.h"
#समावेश "scsi_message.h"
#समावेश "aiclib.h"

/*********************************** Debugging ********************************/
#अगर_घोषित CONFIG_AIC7XXX_DEBUG_ENABLE
#अगर_घोषित CONFIG_AIC7XXX_DEBUG_MASK
#घोषणा AHC_DEBUG 1
#घोषणा AHC_DEBUG_OPTS CONFIG_AIC7XXX_DEBUG_MASK
#अन्यथा
/*
 * Compile in debugging code, but करो not enable any म_लिखोs.
 */
#घोषणा AHC_DEBUG 1
#पूर्ण_अगर
/* No debugging code. */
#पूर्ण_अगर

/************************* Forward Declarations *******************************/
काष्ठा ahc_softc;
प्रकार काष्ठा pci_dev *ahc_dev_softc_t;
प्रकार काष्ठा scsi_cmnd      *ahc_io_ctx_t;

/******************************* Byte Order ***********************************/
#घोषणा ahc_htobe16(x)	cpu_to_be16(x)
#घोषणा ahc_htobe32(x)	cpu_to_be32(x)
#घोषणा ahc_htobe64(x)	cpu_to_be64(x)
#घोषणा ahc_htole16(x)	cpu_to_le16(x)
#घोषणा ahc_htole32(x)	cpu_to_le32(x)
#घोषणा ahc_htole64(x)	cpu_to_le64(x)

#घोषणा ahc_be16toh(x)	be16_to_cpu(x)
#घोषणा ahc_be32toh(x)	be32_to_cpu(x)
#घोषणा ahc_be64toh(x)	be64_to_cpu(x)
#घोषणा ahc_le16toh(x)	le16_to_cpu(x)
#घोषणा ahc_le32toh(x)	le32_to_cpu(x)
#घोषणा ahc_le64toh(x)	le64_to_cpu(x)

/************************* Configuration Data *********************************/
बाह्य u_पूर्णांक aic7xxx_no_probe;
बाह्य u_पूर्णांक aic7xxx_allow_memio;
बाह्य काष्ठा scsi_host_ढाँचा aic7xxx_driver_ढाँचा;

/***************************** Bus Space/DMA **********************************/

प्रकार uपूर्णांक32_t bus_माप_प्रकार;

प्रकार क्रमागत अणु
	BUS_SPACE_MEMIO,
	BUS_SPACE_PIO
पूर्ण bus_space_tag_t;

प्रकार जोड़ अणु
	u_दीर्घ		  ioport;
	अस्थिर uपूर्णांक8_t __iomem *maddr;
पूर्ण bus_space_handle_t;

प्रकार काष्ठा bus_dma_segment
अणु
	dma_addr_t	ds_addr;
	bus_माप_प्रकार	ds_len;
पूर्ण bus_dma_segment_t;

काष्ठा ahc_linux_dma_tag
अणु
	bus_माप_प्रकार	alignment;
	bus_माप_प्रकार	boundary;
	bus_माप_प्रकार	maxsize;
पूर्ण;
प्रकार काष्ठा ahc_linux_dma_tag* bus_dma_tag_t;

प्रकार dma_addr_t bus_dmamap_t;

प्रकार पूर्णांक bus_dma_filter_t(व्योम*, dma_addr_t);
प्रकार व्योम bus_dmamap_callback_t(व्योम *, bus_dma_segment_t *, पूर्णांक, पूर्णांक);

#घोषणा BUS_DMA_WAITOK		0x0
#घोषणा BUS_DMA_NOWAIT		0x1
#घोषणा BUS_DMA_ALLOCNOW	0x2
#घोषणा BUS_DMA_LOAD_SEGS	0x4	/*
					 * Argument is an S/G list not
					 * a single buffer.
					 */

#घोषणा BUS_SPACE_MAXADDR	0xFFFFFFFF
#घोषणा BUS_SPACE_MAXADDR_32BIT	0xFFFFFFFF
#घोषणा BUS_SPACE_MAXSIZE_32BIT	0xFFFFFFFF

पूर्णांक	ahc_dma_tag_create(काष्ठा ahc_softc *, bus_dma_tag_t /*parent*/,
			   bus_माप_प्रकार /*alignment*/, bus_माप_प्रकार /*boundary*/,
			   dma_addr_t /*lowaddr*/, dma_addr_t /*highaddr*/,
			   bus_dma_filter_t*/*filter*/, व्योम */*filterarg*/,
			   bus_माप_प्रकार /*maxsize*/, पूर्णांक /*nsegments*/,
			   bus_माप_प्रकार /*maxsegsz*/, पूर्णांक /*flags*/,
			   bus_dma_tag_t */*dma_tagp*/);

व्योम	ahc_dma_tag_destroy(काष्ठा ahc_softc *, bus_dma_tag_t /*tag*/);

पूर्णांक	ahc_dmamem_alloc(काष्ठा ahc_softc *, bus_dma_tag_t /*dmat*/,
			 व्योम** /*vaddr*/, पूर्णांक /*flags*/,
			 bus_dmamap_t* /*mapp*/);

व्योम	ahc_dmamem_मुक्त(काष्ठा ahc_softc *, bus_dma_tag_t /*dmat*/,
			व्योम* /*vaddr*/, bus_dmamap_t /*map*/);

व्योम	ahc_dmamap_destroy(काष्ठा ahc_softc *, bus_dma_tag_t /*tag*/,
			   bus_dmamap_t /*map*/);

पूर्णांक	ahc_dmamap_load(काष्ठा ahc_softc *ahc, bus_dma_tag_t /*dmat*/,
			bus_dmamap_t /*map*/, व्योम * /*buf*/,
			bus_माप_प्रकार /*buflen*/, bus_dmamap_callback_t *,
			व्योम */*callback_arg*/, पूर्णांक /*flags*/);

पूर्णांक	ahc_dmamap_unload(काष्ठा ahc_softc *, bus_dma_tag_t, bus_dmamap_t);

/*
 * Operations perक्रमmed by ahc_dmamap_sync().
 */
#घोषणा BUS_DMASYNC_PREREAD	0x01	/* pre-पढ़ो synchronization */
#घोषणा BUS_DMASYNC_POSTREAD	0x02	/* post-पढ़ो synchronization */
#घोषणा BUS_DMASYNC_PREWRITE	0x04	/* pre-ग_लिखो synchronization */
#घोषणा BUS_DMASYNC_POSTWRITE	0x08	/* post-ग_लिखो synchronization */

/*
 * XXX
 * ahc_dmamap_sync is only used on buffers allocated with
 * the pci_alloc_consistent() API.  Although I'm not sure how
 * this works on architectures with a ग_लिखो buffer, Linux करोes
 * not have an API to sync "coherent" memory.  Perhaps we need
 * to करो an mb()?
 */
#घोषणा ahc_dmamap_sync(ahc, dma_tag, dmamap, offset, len, op)

/********************************** Includes **********************************/
#अगर_घोषित CONFIG_AIC7XXX_REG_PRETTY_PRINT
#घोषणा AIC_DEBUG_REGISTERS 1
#अन्यथा
#घोषणा AIC_DEBUG_REGISTERS 0
#पूर्ण_अगर
#समावेश "aic7xxx.h"

/***************************** Timer Facilities *******************************/
अटल अंतरभूत व्योम
ahc_scb_समयr_reset(काष्ठा scb *scb, u_पूर्णांक usec)
अणु
पूर्ण

/***************************** SMP support ************************************/
#समावेश <linux/spinlock.h>

#घोषणा AIC7XXX_DRIVER_VERSION "7.0"

/*************************** Device Data Structures ***************************/
/*
 * A per probed device काष्ठाure used to deal with some error recovery
 * scenarios that the Linux mid-layer code just करोesn't know how to
 * handle.  The काष्ठाure allocated क्रम a device only becomes persistent
 * after a successfully completed inquiry command to the target when
 * that inquiry data indicates a lun is present.
 */
प्रकार क्रमागत अणु
	AHC_DEV_FREEZE_TIL_EMPTY = 0x02, /* Freeze queue until active == 0 */
	AHC_DEV_Q_BASIC		 = 0x10, /* Allow basic device queuing */
	AHC_DEV_Q_TAGGED	 = 0x20, /* Allow full SCSI2 command queueing */
	AHC_DEV_PERIODIC_OTAG	 = 0x40, /* Send OTAG to prevent starvation */
पूर्ण ahc_linux_dev_flags;

काष्ठा ahc_linux_device अणु
	/*
	 * The number of transactions currently
	 * queued to the device.
	 */
	पूर्णांक			active;

	/*
	 * The currently allowed number of
	 * transactions that can be queued to
	 * the device.  Must be चिन्हित क्रम
	 * conversion from tagged to untagged
	 * mode where the device may have more
	 * than one outstanding active transaction.
	 */
	पूर्णांक			खोलोings;

	/*
	 * A positive count indicates that this
	 * device's queue is halted.
	 */
	u_पूर्णांक			qfrozen;

	/*
	 * Cumulative command counter.
	 */
	u_दीर्घ			commands_issued;

	/*
	 * The number of tagged transactions when
	 * running at our current खोलोing level
	 * that have been successfully received by
	 * this device since the last QUEUE FULL.
	 */
	u_पूर्णांक			tag_success_count;
#घोषणा AHC_TAG_SUCCESS_INTERVAL 50

	ahc_linux_dev_flags	flags;

	/*
	 * The high limit क्रम the tags variable.
	 */
	u_पूर्णांक			maxtags;

	/*
	 * The computed number of tags outstanding
	 * at the समय of the last QUEUE FULL event.
	 */
	u_पूर्णांक			tags_on_last_queuefull;

	/*
	 * How many बार we have seen a queue full
	 * with the same number of tags.  This is used
	 * to stop our adaptive queue depth algorithm
	 * on devices with a fixed number of tags.
	 */
	u_पूर्णांक			last_queuefull_same_count;
#घोषणा AHC_LOCK_TAGS_COUNT 50

	/*
	 * How many transactions have been queued
	 * without the device going idle.  We use
	 * this statistic to determine when to issue
	 * an ordered tag to prevent transaction
	 * starvation.  This statistic is only updated
	 * अगर the AHC_DEV_PERIODIC_OTAG flag is set
	 * on this device.
	 */
	u_पूर्णांक			commands_since_idle_or_otag;
#घोषणा AHC_OTAG_THRESH	500
पूर्ण;

/********************* Definitions Required by the Core ***********************/
/*
 * Number of SG segments we require.  So दीर्घ as the S/G segments क्रम
 * a particular transaction are allocated in a physically contiguous
 * manner and are allocated below 4GB, the number of S/G segments is
 * unrestricted.
 */
#घोषणा	AHC_NSEG 128

/*
 * Per-SCB OSM storage.
 */
काष्ठा scb_platक्रमm_data अणु
	काष्ठा ahc_linux_device	*dev;
	dma_addr_t		 buf_busaddr;
	uपूर्णांक32_t		 xfer_len;
	uपूर्णांक32_t		 sense_resid;	/* Auto-Sense residual */
पूर्ण;

/*
 * Define a काष्ठाure used क्रम each host adapter.  All members are
 * aligned on a boundary >= the size of the member to honor the
 * alignment restrictions of the various platक्रमms supported by
 * this driver.
 */
काष्ठा ahc_platक्रमm_data अणु
	/*
	 * Fields accessed from पूर्णांकerrupt context.
	 */
	काष्ठा scsi_target *starget[AHC_NUM_TARGETS];

	spinlock_t		 spin_lock;
	u_पूर्णांक			 qfrozen;
	काष्ठा completion	*eh_करोne;
	काष्ठा Scsi_Host	*host;		/* poपूर्णांकer to scsi host */
#घोषणा AHC_LINUX_NOIRQ	((uपूर्णांक32_t)~0)
	uपूर्णांक32_t		 irq;		/* IRQ क्रम this adapter */
	uपूर्णांक32_t		 bios_address;
	resource_माप_प्रकार		 mem_busaddr;	/* Mem Base Addr */
पूर्ण;

व्योम ahc_delay(दीर्घ);


/***************************** Low Level I/O **********************************/
uपूर्णांक8_t ahc_inb(काष्ठा ahc_softc * ahc, दीर्घ port);
व्योम ahc_outb(काष्ठा ahc_softc * ahc, दीर्घ port, uपूर्णांक8_t val);
व्योम ahc_outsb(काष्ठा ahc_softc * ahc, दीर्घ port,
	       uपूर्णांक8_t *, पूर्णांक count);
व्योम ahc_insb(काष्ठा ahc_softc * ahc, दीर्घ port,
	       uपूर्णांक8_t *, पूर्णांक count);

/**************************** Initialization **********************************/
पूर्णांक		ahc_linux_रेजिस्टर_host(काष्ठा ahc_softc *,
					काष्ठा scsi_host_ढाँचा *);

/******************************** Locking *************************************/
/* Lock protecting पूर्णांकernal data काष्ठाures */

अटल अंतरभूत व्योम
ahc_lockinit(काष्ठा ahc_softc *ahc)
अणु
	spin_lock_init(&ahc->platक्रमm_data->spin_lock);
पूर्ण

अटल अंतरभूत व्योम
ahc_lock(काष्ठा ahc_softc *ahc, अचिन्हित दीर्घ *flags)
अणु
	spin_lock_irqsave(&ahc->platक्रमm_data->spin_lock, *flags);
पूर्ण

अटल अंतरभूत व्योम
ahc_unlock(काष्ठा ahc_softc *ahc, अचिन्हित दीर्घ *flags)
अणु
	spin_unlock_irqrestore(&ahc->platक्रमm_data->spin_lock, *flags);
पूर्ण

/******************************* PCI Definitions ******************************/
/*
 * PCIM_xxx: mask to locate subfield in रेजिस्टर
 * PCIR_xxx: config रेजिस्टर offset
 * PCIC_xxx: device class
 * PCIS_xxx: device subclass
 * PCIP_xxx: device programming पूर्णांकerface
 * PCIV_xxx: PCI venकरोr ID (only required to fixup ancient devices)
 * PCID_xxx: device ID
 */
#घोषणा PCIR_DEVVENDOR		0x00
#घोषणा PCIR_VENDOR		0x00
#घोषणा PCIR_DEVICE		0x02
#घोषणा PCIR_COMMAND		0x04
#घोषणा PCIM_CMD_PORTEN		0x0001
#घोषणा PCIM_CMD_MEMEN		0x0002
#घोषणा PCIM_CMD_BUSMASTEREN	0x0004
#घोषणा PCIM_CMD_MWRICEN	0x0010
#घोषणा PCIM_CMD_PERRESPEN	0x0040
#घोषणा	PCIM_CMD_SERRESPEN	0x0100
#घोषणा PCIR_STATUS		0x06
#घोषणा PCIR_REVID		0x08
#घोषणा PCIR_PROGIF		0x09
#घोषणा PCIR_SUBCLASS		0x0a
#घोषणा PCIR_CLASS		0x0b
#घोषणा PCIR_CACHELNSZ		0x0c
#घोषणा PCIR_LATTIMER		0x0d
#घोषणा PCIR_HEADERTYPE		0x0e
#घोषणा PCIM_MFDEV		0x80
#घोषणा PCIR_BIST		0x0f
#घोषणा PCIR_CAP_PTR		0x34

/* config रेजिस्टरs क्रम header type 0 devices */
#घोषणा PCIR_MAPS	0x10
#घोषणा PCIR_SUBVEND_0	0x2c
#घोषणा PCIR_SUBDEV_0	0x2e

प्रकार क्रमागत
अणु
	AHC_POWER_STATE_D0,
	AHC_POWER_STATE_D1,
	AHC_POWER_STATE_D2,
	AHC_POWER_STATE_D3
पूर्ण ahc_घातer_state;

/**************************** VL/EISA Routines ********************************/
#अगर_घोषित CONFIG_EISA
पूर्णांक			 ahc_linux_eisa_init(व्योम);
व्योम			 ahc_linux_eisa_निकास(व्योम);
पूर्णांक			 aic7770_map_रेजिस्टरs(काष्ठा ahc_softc *ahc,
					       u_पूर्णांक port);
पूर्णांक			 aic7770_map_पूर्णांक(काष्ठा ahc_softc *ahc, u_पूर्णांक irq);
#अन्यथा
अटल अंतरभूत पूर्णांक	ahc_linux_eisa_init(व्योम) अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम	ahc_linux_eisa_निकास(व्योम) अणु
पूर्ण
#पूर्ण_अगर

/******************************* PCI Routines *********************************/
#अगर_घोषित CONFIG_PCI
पूर्णांक			 ahc_linux_pci_init(व्योम);
व्योम			 ahc_linux_pci_निकास(व्योम);
पूर्णांक			 ahc_pci_map_रेजिस्टरs(काष्ठा ahc_softc *ahc);
पूर्णांक			 ahc_pci_map_पूर्णांक(काष्ठा ahc_softc *ahc);

uपूर्णांक32_t		 ahc_pci_पढ़ो_config(ahc_dev_softc_t pci,
					     पूर्णांक reg, पूर्णांक width);

व्योम			 ahc_pci_ग_लिखो_config(ahc_dev_softc_t pci,
					      पूर्णांक reg, uपूर्णांक32_t value,
					      पूर्णांक width);

अटल अंतरभूत पूर्णांक ahc_get_pci_function(ahc_dev_softc_t);
अटल अंतरभूत पूर्णांक
ahc_get_pci_function(ahc_dev_softc_t pci)
अणु
	वापस (PCI_FUNC(pci->devfn));
पूर्ण

अटल अंतरभूत पूर्णांक ahc_get_pci_slot(ahc_dev_softc_t);
अटल अंतरभूत पूर्णांक
ahc_get_pci_slot(ahc_dev_softc_t pci)
अणु
	वापस (PCI_SLOT(pci->devfn));
पूर्ण

अटल अंतरभूत पूर्णांक ahc_get_pci_bus(ahc_dev_softc_t);
अटल अंतरभूत पूर्णांक
ahc_get_pci_bus(ahc_dev_softc_t pci)
अणु
	वापस (pci->bus->number);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ahc_linux_pci_init(व्योम) अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ahc_linux_pci_निकास(व्योम) अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ahc_flush_device_ग_लिखोs(काष्ठा ahc_softc *);
अटल अंतरभूत व्योम
ahc_flush_device_ग_लिखोs(काष्ठा ahc_softc *ahc)
अणु
	/* XXX Is this sufficient क्रम all architectures??? */
	ahc_inb(ahc, INTSTAT);
पूर्ण

/**************************** Proc FS Support *********************************/
पूर्णांक	ahc_proc_ग_लिखो_seeprom(काष्ठा Scsi_Host *, अक्षर *, पूर्णांक);
पूर्णांक	ahc_linux_show_info(काष्ठा seq_file *, काष्ठा Scsi_Host *);

/*************************** Doमुख्य Validation ********************************/
/*********************** Transaction Access Wrappers *************************/

अटल अंतरभूत
व्योम ahc_cmd_set_transaction_status(काष्ठा scsi_cmnd *cmd, uपूर्णांक32_t status)
अणु
	cmd->result &= ~(CAM_STATUS_MASK << 16);
	cmd->result |= status << 16;
पूर्ण

अटल अंतरभूत
व्योम ahc_set_transaction_status(काष्ठा scb *scb, uपूर्णांक32_t status)
अणु
	ahc_cmd_set_transaction_status(scb->io_ctx,status);
पूर्ण

अटल अंतरभूत
व्योम ahc_cmd_set_scsi_status(काष्ठा scsi_cmnd *cmd, uपूर्णांक32_t status)
अणु
	cmd->result &= ~0xFFFF;
	cmd->result |= status;
पूर्ण

अटल अंतरभूत
व्योम ahc_set_scsi_status(काष्ठा scb *scb, uपूर्णांक32_t status)
अणु
	ahc_cmd_set_scsi_status(scb->io_ctx, status);
पूर्ण

अटल अंतरभूत
uपूर्णांक32_t ahc_cmd_get_transaction_status(काष्ठा scsi_cmnd *cmd)
अणु
	वापस ((cmd->result >> 16) & CAM_STATUS_MASK);
पूर्ण

अटल अंतरभूत
uपूर्णांक32_t ahc_get_transaction_status(काष्ठा scb *scb)
अणु
	वापस (ahc_cmd_get_transaction_status(scb->io_ctx));
पूर्ण

अटल अंतरभूत
uपूर्णांक32_t ahc_cmd_get_scsi_status(काष्ठा scsi_cmnd *cmd)
अणु
	वापस (cmd->result & 0xFFFF);
पूर्ण

अटल अंतरभूत
uपूर्णांक32_t ahc_get_scsi_status(काष्ठा scb *scb)
अणु
	वापस (ahc_cmd_get_scsi_status(scb->io_ctx));
पूर्ण

अटल अंतरभूत
व्योम ahc_set_transaction_tag(काष्ठा scb *scb, पूर्णांक enabled, u_पूर्णांक type)
अणु
	/*
	 * Nothing to करो क्रम linux as the incoming transaction
	 * has no concept of tag/non tagged, etc.
	 */
पूर्ण

अटल अंतरभूत
u_दीर्घ ahc_get_transfer_length(काष्ठा scb *scb)
अणु
	वापस (scb->platक्रमm_data->xfer_len);
पूर्ण

अटल अंतरभूत
पूर्णांक ahc_get_transfer_dir(काष्ठा scb *scb)
अणु
	वापस (scb->io_ctx->sc_data_direction);
पूर्ण

अटल अंतरभूत
व्योम ahc_set_residual(काष्ठा scb *scb, u_दीर्घ resid)
अणु
	scsi_set_resid(scb->io_ctx, resid);
पूर्ण

अटल अंतरभूत
व्योम ahc_set_sense_residual(काष्ठा scb *scb, u_दीर्घ resid)
अणु
	scb->platक्रमm_data->sense_resid = resid;
पूर्ण

अटल अंतरभूत
u_दीर्घ ahc_get_residual(काष्ठा scb *scb)
अणु
	वापस scsi_get_resid(scb->io_ctx);
पूर्ण

अटल अंतरभूत
u_दीर्घ ahc_get_sense_residual(काष्ठा scb *scb)
अणु
	वापस (scb->platक्रमm_data->sense_resid);
पूर्ण

अटल अंतरभूत
पूर्णांक ahc_perक्रमm_स्वतःsense(काष्ठा scb *scb)
अणु
	/*
	 * We always perक्रमm स्वतःsense in Linux.
	 * On other platक्रमms this is set on a
	 * per-transaction basis.
	 */
	वापस (1);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
ahc_get_sense_bufsize(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	वापस (माप(काष्ठा scsi_sense_data));
पूर्ण

अटल अंतरभूत व्योम
ahc_notअगरy_xfer_settings_change(काष्ठा ahc_softc *ahc,
				काष्ठा ahc_devinfo *devinfo)
अणु
	/* Nothing to करो here क्रम linux */
पूर्ण

अटल अंतरभूत व्योम
ahc_platक्रमm_scb_मुक्त(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
पूर्ण

पूर्णांक	ahc_platक्रमm_alloc(काष्ठा ahc_softc *ahc, व्योम *platक्रमm_arg);
व्योम	ahc_platक्रमm_मुक्त(काष्ठा ahc_softc *ahc);
व्योम	ahc_platक्रमm_मुक्तze_devq(काष्ठा ahc_softc *ahc, काष्ठा scb *scb);

अटल अंतरभूत व्योम
ahc_मुक्तze_scb(काष्ठा scb *scb)
अणु
	अगर ((scb->io_ctx->result & (CAM_DEV_QFRZN << 16)) == 0) अणु
		scb->io_ctx->result |= CAM_DEV_QFRZN << 16;
		scb->platक्रमm_data->dev->qfrozen++;
	पूर्ण
पूर्ण

व्योम	ahc_platक्रमm_set_tags(काष्ठा ahc_softc *ahc, काष्ठा scsi_device *sdev,
			      काष्ठा ahc_devinfo *devinfo, ahc_queue_alg);
पूर्णांक	ahc_platक्रमm_पात_scbs(काष्ठा ahc_softc *ahc, पूर्णांक target,
				अक्षर channel, पूर्णांक lun, u_पूर्णांक tag,
				role_t role, uपूर्णांक32_t status);
irqवापस_t
	ahc_linux_isr(पूर्णांक irq, व्योम *dev_id);
व्योम	ahc_platक्रमm_flushwork(काष्ठा ahc_softc *ahc);
व्योम	ahc_करोne(काष्ठा ahc_softc*, काष्ठा scb*);
व्योम	ahc_send_async(काष्ठा ahc_softc *, अक्षर channel,
		       u_पूर्णांक target, u_पूर्णांक lun, ac_code);
व्योम	ahc_prपूर्णांक_path(काष्ठा ahc_softc *, काष्ठा scb *);

#अगर_घोषित CONFIG_PCI
#घोषणा AHC_PCI_CONFIG 1
#अन्यथा
#घोषणा AHC_PCI_CONFIG 0
#पूर्ण_अगर
#घोषणा bootverbose aic7xxx_verbose
बाह्य u_पूर्णांक aic7xxx_verbose;
#पूर्ण_अगर /* _AIC7XXX_LINUX_H_ */
