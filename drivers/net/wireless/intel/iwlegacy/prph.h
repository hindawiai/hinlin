<शैली गुरु>
/******************************************************************************
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2005 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA 02110,
 * USA
 *
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 * BSD LICENSE
 *
 * Copyright(c) 2005 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#अगर_अघोषित	__il_prph_h__
#घोषणा __il_prph_h__

/*
 * Registers in this file are पूर्णांकernal, not PCI bus memory mapped.
 * Driver accesses these via HBUS_TARG_PRPH_* रेजिस्टरs.
 */
#घोषणा PRPH_BASE	(0x00000)
#घोषणा PRPH_END	(0xFFFFF)

/* APMG (घातer management) स्थिरants */
#घोषणा APMG_BASE			(PRPH_BASE + 0x3000)
#घोषणा APMG_CLK_CTRL_REG		(APMG_BASE + 0x0000)
#घोषणा APMG_CLK_EN_REG			(APMG_BASE + 0x0004)
#घोषणा APMG_CLK_DIS_REG		(APMG_BASE + 0x0008)
#घोषणा APMG_PS_CTRL_REG		(APMG_BASE + 0x000c)
#घोषणा APMG_PCIDEV_STT_REG		(APMG_BASE + 0x0010)
#घोषणा APMG_RFKILL_REG			(APMG_BASE + 0x0014)
#घोषणा APMG_RTC_INT_STT_REG		(APMG_BASE + 0x001c)
#घोषणा APMG_RTC_INT_MSK_REG		(APMG_BASE + 0x0020)
#घोषणा APMG_DIGITAL_SVR_REG		(APMG_BASE + 0x0058)
#घोषणा APMG_ANALOG_SVR_REG		(APMG_BASE + 0x006C)

#घोषणा APMS_CLK_VAL_MRB_FUNC_MODE	(0x00000001)
#घोषणा APMG_CLK_VAL_DMA_CLK_RQT	(0x00000200)
#घोषणा APMG_CLK_VAL_BSM_CLK_RQT	(0x00000800)

#घोषणा APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS	(0x00400000)
#घोषणा APMG_PS_CTRL_VAL_RESET_REQ		(0x04000000)
#घोषणा APMG_PS_CTRL_MSK_PWR_SRC		(0x03000000)
#घोषणा APMG_PS_CTRL_VAL_PWR_SRC_VMAIN		(0x00000000)
#घोषणा APMG_PS_CTRL_VAL_PWR_SRC_MAX		(0x01000000)	/* 3945 only */
#घोषणा APMG_PS_CTRL_VAL_PWR_SRC_VAUX		(0x02000000)
#घोषणा APMG_SVR_VOLTAGE_CONFIG_BIT_MSK	(0x000001E0)	/* bit 8:5 */
#घोषणा APMG_SVR_DIGITAL_VOLTAGE_1_32		(0x00000060)

#घोषणा APMG_PCIDEV_STT_VAL_L1_ACT_DIS		(0x00000800)

/**
 * BSM (Bootstrap State Machine)
 *
 * The Bootstrap State Machine (BSM) stores a लघु bootstrap uCode program
 * in special SRAM that करोes not घातer करोwn when the embedded control
 * processor is sleeping (e.g. क्रम periodic घातer-saving shutकरोwns of radio).
 *
 * When घातering back up after sleeps (or during initial uCode load), the BSM
 * पूर्णांकernally loads the लघु bootstrap program from the special SRAM पूर्णांकo the
 * embedded processor's inकाष्ठाion SRAM, and starts the processor so it runs
 * the bootstrap program.
 *
 * This bootstrap program loads (via PCI busmaster DMA) inकाष्ठाions and data
 * images क्रम a uCode program from host DRAM locations.  The host driver
 * indicates DRAM locations and sizes क्रम inकाष्ठाion and data images via the
 * four BSM_DRAM_* रेजिस्टरs.  Once the bootstrap program loads the new program,
 * the new program starts स्वतःmatically.
 *
 * The uCode used क्रम खोलो-source drivers includes two programs:
 *
 * 1)  Initialization -- perक्रमms hardware calibration and sets up some
 *     पूर्णांकernal data, then notअगरies host via "initialize alive" notअगरication
 *     (काष्ठा il_init_alive_resp) that it has completed all of its work.
 *     After संकेत from host, it then loads and starts the runसमय program.
 *     The initialization program must be used when initially setting up the
 *     NIC after loading the driver.
 *
 * 2)  Runसमय/Protocol -- perक्रमms all normal runसमय operations.  This
 *     notअगरies host via "alive" notअगरication (काष्ठा il_alive_resp) that it
 *     is पढ़ोy to be used.
 *
 * When initializing the NIC, the host driver करोes the following procedure:
 *
 * 1)  Load bootstrap program (inकाष्ठाions only, no data image क्रम bootstrap)
 *     पूर्णांकo bootstrap memory.  Use dword ग_लिखोs starting at BSM_SRAM_LOWER_BOUND
 *
 * 2)  Poपूर्णांक (via BSM_DRAM_*) to the "initialize" uCode data and inकाष्ठाion
 *     images in host DRAM.
 *
 * 3)  Set up BSM to copy from BSM SRAM पूर्णांकo uCode inकाष्ठाion SRAM when asked:
 *     BSM_WR_MEM_SRC_REG = 0
 *     BSM_WR_MEM_DST_REG = RTC_INST_LOWER_BOUND
 *     BSM_WR_MEM_DWCOUNT_REG = # dwords in bootstrap inकाष्ठाion image
 *
 * 4)  Load bootstrap पूर्णांकo inकाष्ठाion SRAM:
 *     BSM_WR_CTRL_REG = BSM_WR_CTRL_REG_BIT_START
 *
 * 5)  Wait क्रम load completion:
 *     Poll BSM_WR_CTRL_REG क्रम BSM_WR_CTRL_REG_BIT_START = 0
 *
 * 6)  Enable future boot loads whenever NIC's घातer management triggers it:
 *     BSM_WR_CTRL_REG = BSM_WR_CTRL_REG_BIT_START_EN
 *
 * 7)  Start the NIC by removing all reset bits:
 *     CSR_RESET = 0
 *
 *     The bootstrap uCode (alपढ़ोy in inकाष्ठाion SRAM) loads initialization
 *     uCode.  Initialization uCode perक्रमms data initialization, sends
 *     "initialize alive" notअगरication to host, and रुकोs क्रम a संकेत from
 *     host to load runसमय code.
 *
 * 4)  Poपूर्णांक (via BSM_DRAM_*) to the "runtime" uCode data and inकाष्ठाion
 *     images in host DRAM.  The last रेजिस्टर loaded must be the inकाष्ठाion
 *     byte count रेजिस्टर ("1" in MSbit tells initialization uCode to load
 *     the runसमय uCode):
 *     BSM_DRAM_INST_BYTECOUNT_REG = byte count | BSM_DRAM_INST_LOAD
 *
 * 5)  Wait क्रम "alive" notअगरication, then issue normal runसमय commands.
 *
 * Data caching during घातer-करोwns:
 *
 * Just beक्रमe the embedded controller घातers करोwn (e.g क्रम स्वतःmatic
 * घातer-saving modes, or क्रम RFKILL), uCode stores (via PCI busmaster DMA)
 * a current snapshot of the embedded processor's data SRAM पूर्णांकo host DRAM.
 * This caches the data जबतक the embedded processor's memory is घातered करोwn.
 * Location and size are controlled by BSM_DRAM_DATA_* रेजिस्टरs.
 *
 * NOTE:  Inकाष्ठाion SRAM करोes not need to be saved, since that करोesn't
 *        change during operation; the original image (from uCode distribution
 *        file) can be used क्रम reload.
 *
 * When घातering back up, the BSM loads the bootstrap program.  Bootstrap looks
 * at the BSM_DRAM_* रेजिस्टरs, which now poपूर्णांक to the runसमय inकाष्ठाion
 * image and the cached (modअगरied) runसमय data (*not* the initialization
 * uCode).  Bootstrap reloads these runसमय images पूर्णांकo SRAM, and restarts the
 * uCode from where it left off beक्रमe the घातer-करोwn.
 *
 * NOTE:  Initialization uCode करोes *not* run as part of the save/restore
 *        procedure.
 *
 * This save/restore method is mostly क्रम स्वतःnomous घातer management during
 * normal operation (result of C_POWER_TBL).  Platक्रमm suspend/resume and
 * RFKILL should use complete restarts (with total re-initialization) of uCode,
 * allowing total shutकरोwn (including BSM memory).
 *
 * Note that, during normal operation, the host DRAM that held the initial
 * startup data क्रम the runसमय code is now being used as a backup data cache
 * क्रम modअगरied data!  If you need to completely re-initialize the NIC, make
 * sure that you use the runसमय data image from the uCode distribution file,
 * not the modअगरied/saved runसमय data.  You may want to store a separate
 * "clean" runसमय data image in DRAM to aव्योम disk पढ़ोs of distribution file.
 */

/* BSM bit fields */
#घोषणा BSM_WR_CTRL_REG_BIT_START     (0x80000000)	/* start boot load now */
#घोषणा BSM_WR_CTRL_REG_BIT_START_EN  (0x40000000)	/* enable boot after pwrup */
#घोषणा BSM_DRAM_INST_LOAD            (0x80000000)	/* start program load now */

/* BSM addresses */
#घोषणा BSM_BASE                     (PRPH_BASE + 0x3400)
#घोषणा BSM_END                      (PRPH_BASE + 0x3800)

#घोषणा BSM_WR_CTRL_REG              (BSM_BASE + 0x000)	/* ctl and status */
#घोषणा BSM_WR_MEM_SRC_REG           (BSM_BASE + 0x004)	/* source in BSM mem */
#घोषणा BSM_WR_MEM_DST_REG           (BSM_BASE + 0x008)	/* dest in SRAM mem */
#घोषणा BSM_WR_DWCOUNT_REG           (BSM_BASE + 0x00C)	/* bytes */
#घोषणा BSM_WR_STATUS_REG            (BSM_BASE + 0x010)	/* bit 0:  1 == करोne */

/*
 * Poपूर्णांकers and size regs क्रम bootstrap load and data SRAM save/restore.
 * NOTE:  3945 poपूर्णांकers use bits 31:0 of DRAM address.
 *        4965 poपूर्णांकers use bits 35:4 of DRAM address.
 */
#घोषणा BSM_DRAM_INST_PTR_REG        (BSM_BASE + 0x090)
#घोषणा BSM_DRAM_INST_BYTECOUNT_REG  (BSM_BASE + 0x094)
#घोषणा BSM_DRAM_DATA_PTR_REG        (BSM_BASE + 0x098)
#घोषणा BSM_DRAM_DATA_BYTECOUNT_REG  (BSM_BASE + 0x09C)

/*
 * BSM special memory, stays घातered on during घातer-save sleeps.
 * Read/ग_लिखो, address range from LOWER_BOUND to (LOWER_BOUND + SIZE -1)
 */
#घोषणा BSM_SRAM_LOWER_BOUND         (PRPH_BASE + 0x3800)
#घोषणा BSM_SRAM_SIZE			(1024)	/* bytes */

/* 3945 Tx scheduler रेजिस्टरs */
#घोषणा ALM_SCD_BASE                        (PRPH_BASE + 0x2E00)
#घोषणा ALM_SCD_MODE_REG                    (ALM_SCD_BASE + 0x000)
#घोषणा ALM_SCD_ARASTAT_REG                 (ALM_SCD_BASE + 0x004)
#घोषणा ALM_SCD_TXFACT_REG                  (ALM_SCD_BASE + 0x010)
#घोषणा ALM_SCD_TXF4MF_REG                  (ALM_SCD_BASE + 0x014)
#घोषणा ALM_SCD_TXF5MF_REG                  (ALM_SCD_BASE + 0x020)
#घोषणा ALM_SCD_SBYP_MODE_1_REG             (ALM_SCD_BASE + 0x02C)
#घोषणा ALM_SCD_SBYP_MODE_2_REG             (ALM_SCD_BASE + 0x030)

/**
 * Tx Scheduler
 *
 * The Tx Scheduler selects the next frame to be transmitted, choosing TFDs
 * (Transmit Frame Descriptors) from up to 16 circular Tx queues resident in
 * host DRAM.  It steers each frame's Tx command (which contains the frame
 * data) पूर्णांकo one of up to 7 prioritized Tx DMA FIFO channels within the
 * device.  A queue maps to only one (selectable by driver) Tx DMA channel,
 * but one DMA channel may take input from several queues.
 *
 * Tx DMA FIFOs have dedicated purposes.  For 4965, they are used as follows
 * (cf. शेष_queue_to_tx_fअगरo in 4965.c):
 *
 * 0 -- EDCA BK (background) frames, lowest priority
 * 1 -- EDCA BE (best efक्रमt) frames, normal priority
 * 2 -- EDCA VI (video) frames, higher priority
 * 3 -- EDCA VO (voice) and management frames, highest priority
 * 4 -- Commands (e.g. RXON, etc.)
 * 5 -- unused (HCCA)
 * 6 -- unused (HCCA)
 * 7 -- not used by driver (device-पूर्णांकernal only)
 *
 *
 * Driver should normally map queues 0-6 to Tx DMA/FIFO channels 0-6.
 * In addition, driver can map the reमुख्यing queues to Tx DMA/FIFO
 * channels 0-3 to support 11n aggregation via EDCA DMA channels.
 *
 * The driver sets up each queue to work in one of two modes:
 *
 * 1)  Scheduler-Ack, in which the scheduler स्वतःmatically supports a
 *     block-ack (BA) win of up to 64 TFDs.  In this mode, each queue
 *     contains TFDs क्रम a unique combination of Recipient Address (RA)
 *     and Traffic Identअगरier (TID), that is, traffic of a given
 *     Quality-Of-Service (QOS) priority, destined क्रम a single station.
 *
 *     In scheduler-ack mode, the scheduler keeps track of the Tx status of
 *     each frame within the BA win, including whether it's been transmitted,
 *     and whether it's been acknowledged by the receiving station.  The device
 *     स्वतःmatically processes block-acks received from the receiving STA,
 *     and reschedules un-acked frames to be retransmitted (successful
 *     Tx completion may end up being out-of-order).
 *
 *     The driver must मुख्यtain the queue's Byte Count table in host DRAM
 *     (काष्ठा il4965_sched_queue_byte_cnt_tbl) क्रम this mode.
 *     This mode करोes not support fragmentation.
 *
 * 2)  FIFO (a.k.a. non-Scheduler-ACK), in which each TFD is processed in order.
 *     The device may स्वतःmatically retry Tx, but will retry only one frame
 *     at a समय, until receiving ACK from receiving station, or reaching
 *     retry limit and giving up.
 *
 *     The command queue (#4/#9) must use this mode!
 *     This mode करोes not require use of the Byte Count table in host DRAM.
 *
 * Driver controls scheduler operation via 3 means:
 * 1)  Scheduler रेजिस्टरs
 * 2)  Shared scheduler data base in पूर्णांकernal 4956 SRAM
 * 3)  Shared data in host DRAM
 *
 * Initialization:
 *
 * When loading, driver should allocate memory क्रम:
 * 1)  16 TFD circular buffers, each with space क्रम (typically) 256 TFDs.
 * 2)  16 Byte Count circular buffers in 16 KBytes contiguous memory
 *     (1024 bytes क्रम each queue).
 *
 * After receiving "Alive" response from uCode, driver must initialize
 * the scheduler (especially क्रम queue #4/#9, the command queue, otherwise
 * the driver can't issue commands!):
 */

/**
 * Max Tx win size is the max number of contiguous TFDs that the scheduler
 * can keep track of at one समय when creating block-ack chains of frames.
 * Note that "64" matches the number of ack bits in a block-ack packet.
 * Driver should use SCD_WIN_SIZE and SCD_FRAME_LIMIT values to initialize
 * IL49_SCD_CONTEXT_QUEUE_OFFSET(x) values.
 */
#घोषणा SCD_WIN_SIZE				64
#घोषणा SCD_FRAME_LIMIT				64

/* SCD रेजिस्टरs are पूर्णांकernal, must be accessed via HBUS_TARG_PRPH regs */
#घोषणा IL49_SCD_START_OFFSET		0xa02c00

/*
 * 4965 tells driver SRAM address क्रम पूर्णांकernal scheduler काष्ठाs via this reg.
 * Value is valid only after "Alive" response from uCode.
 */
#घोषणा IL49_SCD_SRAM_BASE_ADDR           (IL49_SCD_START_OFFSET + 0x0)

/*
 * Driver may need to update queue-empty bits after changing queue's
 * ग_लिखो and पढ़ो poपूर्णांकers (idxes) during (re-)initialization (i.e. when
 * scheduler is not tracking what's happening).
 * Bit fields:
 * 31-16:  Write mask -- 1: update empty bit, 0: करोn't change empty bit
 * 15-00:  Empty state, one क्रम each queue -- 1: empty, 0: non-empty
 * NOTE:  This रेजिस्टर is not used by Linux driver.
 */
#घोषणा IL49_SCD_EMPTY_BITS               (IL49_SCD_START_OFFSET + 0x4)

/*
 * Physical base address of array of byte count (BC) circular buffers (CBs).
 * Each Tx queue has a BC CB in host DRAM to support Scheduler-ACK mode.
 * This रेजिस्टर poपूर्णांकs to BC CB क्रम queue 0, must be on 1024-byte boundary.
 * Others are spaced by 1024 bytes.
 * Each BC CB is 2 bytes * (256 + 64) = 740 bytes, followed by 384 bytes pad.
 * (Index पूर्णांकo a queue's BC CB) = (idx into queue's TFD CB) = (SSN & 0xff).
 * Bit fields:
 * 25-00:  Byte Count CB physical address [35:10], must be 1024-byte aligned.
 */
#घोषणा IL49_SCD_DRAM_BASE_ADDR           (IL49_SCD_START_OFFSET + 0x10)

/*
 * Enables any/all Tx DMA/FIFO channels.
 * Scheduler generates requests क्रम only the active channels.
 * Set this to 0xff to enable all 8 channels (normal usage).
 * Bit fields:
 *  7- 0:  Enable (1), disable (0), one bit क्रम each channel 0-7
 */
#घोषणा IL49_SCD_TXFACT                   (IL49_SCD_START_OFFSET + 0x1c)
/*
 * Queue (x) Write Poपूर्णांकers (idxes, really!), one क्रम each Tx queue.
 * Initialized and updated by driver as new TFDs are added to queue.
 * NOTE:  If using Block Ack, idx must correspond to frame's
 *        Start Sequence Number; idx = (SSN & 0xff)
 * NOTE:  Alternative to HBUS_TARG_WRPTR, which is what Linux driver uses?
 */
#घोषणा IL49_SCD_QUEUE_WRPTR(x)  (IL49_SCD_START_OFFSET + 0x24 + (x) * 4)

/*
 * Queue (x) Read Poपूर्णांकers (idxes, really!), one क्रम each Tx queue.
 * For FIFO mode, idx indicates next frame to transmit.
 * For Scheduler-ACK mode, idx indicates first frame in Tx win.
 * Initialized by driver, updated by scheduler.
 */
#घोषणा IL49_SCD_QUEUE_RDPTR(x)  (IL49_SCD_START_OFFSET + 0x64 + (x) * 4)

/*
 * Select which queues work in chain mode (1) vs. not (0).
 * Use chain mode to build chains of aggregated frames.
 * Bit fields:
 * 31-16:  Reserved
 * 15-00:  Mode, one bit क्रम each queue -- 1: Chain mode, 0: one-at-a-समय
 * NOTE:  If driver sets up queue क्रम chain mode, it should be also set up
 *        Scheduler-ACK mode as well, via SCD_QUEUE_STATUS_BITS(x).
 */
#घोषणा IL49_SCD_QUEUECHAIN_SEL  (IL49_SCD_START_OFFSET + 0xd0)

/*
 * Select which queues पूर्णांकerrupt driver when scheduler increments
 * a queue's पढ़ो poपूर्णांकer (idx).
 * Bit fields:
 * 31-16:  Reserved
 * 15-00:  Interrupt enable, one bit क्रम each queue -- 1: enabled, 0: disabled
 * NOTE:  This functionality is apparently a no-op; driver relies on पूर्णांकerrupts
 *        from Rx queue to पढ़ो Tx command responses and update Tx queues.
 */
#घोषणा IL49_SCD_INTERRUPT_MASK  (IL49_SCD_START_OFFSET + 0xe4)

/*
 * Queue search status रेजिस्टरs.  One क्रम each queue.
 * Sets up queue mode and assigns queue to Tx DMA channel.
 * Bit fields:
 * 19-10: Write mask/enable bits क्रम bits 0-9
 *     9: Driver should init to "0"
 *     8: Scheduler-ACK mode (1), non-Scheduler-ACK (i.e. FIFO) mode (0).
 *        Driver should init to "1" क्रम aggregation mode, or "0" otherwise.
 *   7-6: Driver should init to "0"
 *     5: Winकरोw Size Left; indicates whether scheduler can request
 *        another TFD, based on win size, etc.  Driver should init
 *        this bit to "1" क्रम aggregation mode, or "0" क्रम non-agg.
 *   4-1: Tx FIFO to use (range 0-7).
 *     0: Queue is active (1), not active (0).
 * Other bits should be written as "0"
 *
 * NOTE:  If enabling Scheduler-ACK mode, chain mode should also be enabled
 *        via SCD_QUEUECHAIN_SEL.
 */
#घोषणा IL49_SCD_QUEUE_STATUS_BITS(x)\
	(IL49_SCD_START_OFFSET + 0x104 + (x) * 4)

/* Bit field positions */
#घोषणा IL49_SCD_QUEUE_STTS_REG_POS_ACTIVE	(0)
#घोषणा IL49_SCD_QUEUE_STTS_REG_POS_TXF	(1)
#घोषणा IL49_SCD_QUEUE_STTS_REG_POS_WSL	(5)
#घोषणा IL49_SCD_QUEUE_STTS_REG_POS_SCD_ACK	(8)

/* Write masks */
#घोषणा IL49_SCD_QUEUE_STTS_REG_POS_SCD_ACT_EN	(10)
#घोषणा IL49_SCD_QUEUE_STTS_REG_MSK		(0x0007FC00)

/**
 * 4965 पूर्णांकernal SRAM काष्ठाures क्रम scheduler, shared with driver ...
 *
 * Driver should clear and initialize the following areas after receiving
 * "Alive" response from 4965 uCode, i.e. after initial
 * uCode load, or after a uCode load करोne क्रम error recovery:
 *
 * SCD_CONTEXT_DATA_OFFSET (size 128 bytes)
 * SCD_TX_STTS_BITMAP_OFFSET (size 256 bytes)
 * SCD_TRANSLATE_TBL_OFFSET (size 32 bytes)
 *
 * Driver accesses SRAM via HBUS_TARG_MEM_* रेजिस्टरs.
 * Driver पढ़ोs base address of this scheduler area from SCD_SRAM_BASE_ADDR.
 * All OFFSET values must be added to this base address.
 */

/*
 * Queue context.  One 8-byte entry क्रम each of 16 queues.
 *
 * Driver should clear this entire area (size 0x80) to 0 after receiving
 * "Alive" notअगरication from uCode.  Additionally, driver should init
 * each queue's entry as follows:
 *
 * LS Dword bit fields:
 *  0-06:  Max Tx win size क्रम Scheduler-ACK.  Driver should init to 64.
 *
 * MS Dword bit fields:
 * 16-22:  Frame limit.  Driver should init to 10 (0xa).
 *
 * Driver should init all other bits to 0.
 *
 * Init must be करोne after driver receives "Alive" response from 4965 uCode,
 * and when setting up queue क्रम aggregation.
 */
#घोषणा IL49_SCD_CONTEXT_DATA_OFFSET			0x380
#घोषणा IL49_SCD_CONTEXT_QUEUE_OFFSET(x) \
			(IL49_SCD_CONTEXT_DATA_OFFSET + ((x) * 8))

#घोषणा IL49_SCD_QUEUE_CTX_REG1_WIN_SIZE_POS		(0)
#घोषणा IL49_SCD_QUEUE_CTX_REG1_WIN_SIZE_MSK		(0x0000007F)
#घोषणा IL49_SCD_QUEUE_CTX_REG2_FRAME_LIMIT_POS	(16)
#घोषणा IL49_SCD_QUEUE_CTX_REG2_FRAME_LIMIT_MSK	(0x007F0000)

/*
 * Tx Status Biपंचांगap
 *
 * Driver should clear this entire area (size 0x100) to 0 after receiving
 * "Alive" notअगरication from uCode.  Area is used only by device itself;
 * no other support (besides clearing) is required from driver.
 */
#घोषणा IL49_SCD_TX_STTS_BITMAP_OFFSET		0x400

/*
 * RAxTID to queue translation mapping.
 *
 * When queue is in Scheduler-ACK mode, frames placed in a that queue must be
 * क्रम only one combination of receiver address (RA) and traffic ID (TID), i.e.
 * one QOS priority level destined क्रम one station (क्रम this wireless link,
 * not final destination).  The SCD_TRANSLATE_TBL area provides 16 16-bit
 * mappings, one क्रम each of the 16 queues.  If queue is not in Scheduler-ACK
 * mode, the device ignores the mapping value.
 *
 * Bit fields, क्रम each 16-bit map:
 * 15-9:  Reserved, set to 0
 *  8-4:  Index पूर्णांकo device's station table क्रम recipient station
 *  3-0:  Traffic ID (tid), range 0-15
 *
 * Driver should clear this entire area (size 32 bytes) to 0 after receiving
 * "Alive" notअगरication from uCode.  To update a 16-bit map value, driver
 * must पढ़ो a dword-aligned value from device SRAM, replace the 16-bit map
 * value of पूर्णांकerest, and ग_लिखो the dword value back पूर्णांकo device SRAM.
 */
#घोषणा IL49_SCD_TRANSLATE_TBL_OFFSET		0x500

/* Find translation table dword to पढ़ो/ग_लिखो क्रम given queue */
#घोषणा IL49_SCD_TRANSLATE_TBL_OFFSET_QUEUE(x) \
	((IL49_SCD_TRANSLATE_TBL_OFFSET + ((x) * 2)) & 0xfffffffc)

#घोषणा IL_SCD_TXFIFO_POS_TID			(0)
#घोषणा IL_SCD_TXFIFO_POS_RA			(4)
#घोषणा IL_SCD_QUEUE_RA_TID_MAP_RATID_MSK	(0x01FF)

/*********************** END TX SCHEDULER *************************************/

#पूर्ण_अगर /* __il_prph_h__ */
