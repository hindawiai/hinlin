<शैली गुरु>
/*
 * drivers/dma/fsl_raid.h
 *
 * Freescale RAID Engine device driver
 *
 * Author:
 *	Harninder Rai <harninder.rai@मुक्तscale.com>
 *	Naveen Burmi <naveenburmi@मुक्तscale.com>
 *
 * Reग_लिखो:
 *	Xuelin Shi <xuelin.shi@मुक्तscale.com>

 * Copyright (c) 2010-2012 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#घोषणा FSL_RE_MAX_CHANS		4
#घोषणा FSL_RE_DPAA_MODE		BIT(30)
#घोषणा FSL_RE_NON_DPAA_MODE		BIT(31)
#घोषणा FSL_RE_GFM_POLY			0x1d000000
#घोषणा FSL_RE_ADD_JOB(x)		((x) << 16)
#घोषणा FSL_RE_RMVD_JOB(x)		((x) << 16)
#घोषणा FSL_RE_CFG1_CBSI		0x08000000
#घोषणा FSL_RE_CFG1_CBS0		0x00080000
#घोषणा FSL_RE_SLOT_FULL_SHIFT		8
#घोषणा FSL_RE_SLOT_FULL(x)		((x) >> FSL_RE_SLOT_FULL_SHIFT)
#घोषणा FSL_RE_SLOT_AVAIL_SHIFT		8
#घोषणा FSL_RE_SLOT_AVAIL(x)		((x) >> FSL_RE_SLOT_AVAIL_SHIFT)
#घोषणा FSL_RE_PQ_OPCODE		0x1B
#घोषणा FSL_RE_XOR_OPCODE		0x1A
#घोषणा FSL_RE_MOVE_OPCODE		0x8
#घोषणा FSL_RE_FRAME_ALIGN		16
#घोषणा FSL_RE_BLOCK_SIZE		0x3 /* 4096 bytes */
#घोषणा FSL_RE_CACHEABLE_IO		0x0
#घोषणा FSL_RE_BUFFER_OUTPUT		0x0
#घोषणा FSL_RE_INTR_ON_ERROR		0x1
#घोषणा FSL_RE_DATA_DEP			0x1
#घोषणा FSL_RE_ENABLE_DPI		0x0
#घोषणा FSL_RE_RING_SIZE		0x400
#घोषणा FSL_RE_RING_SIZE_MASK		(FSL_RE_RING_SIZE - 1)
#घोषणा FSL_RE_RING_SIZE_SHIFT		8
#घोषणा FSL_RE_ADDR_BIT_SHIFT		4
#घोषणा FSL_RE_ADDR_BIT_MASK		(BIT(FSL_RE_ADDR_BIT_SHIFT) - 1)
#घोषणा FSL_RE_ERROR			0x40000000
#घोषणा FSL_RE_INTR			0x80000000
#घोषणा FSL_RE_CLR_INTR			0x80000000
#घोषणा FSL_RE_PAUSE			0x80000000
#घोषणा FSL_RE_ENABLE			0x80000000
#घोषणा FSL_RE_REG_LIODN_MASK		0x00000FFF

#घोषणा FSL_RE_CDB_OPCODE_MASK		0xF8000000
#घोषणा FSL_RE_CDB_OPCODE_SHIFT		27
#घोषणा FSL_RE_CDB_EXCLEN_MASK		0x03000000
#घोषणा FSL_RE_CDB_EXCLEN_SHIFT		24
#घोषणा FSL_RE_CDB_EXCLQ1_MASK		0x00F00000
#घोषणा FSL_RE_CDB_EXCLQ1_SHIFT		20
#घोषणा FSL_RE_CDB_EXCLQ2_MASK		0x000F0000
#घोषणा FSL_RE_CDB_EXCLQ2_SHIFT		16
#घोषणा FSL_RE_CDB_BLKSIZE_MASK		0x0000C000
#घोषणा FSL_RE_CDB_BLKSIZE_SHIFT	14
#घोषणा FSL_RE_CDB_CACHE_MASK		0x00003000
#घोषणा FSL_RE_CDB_CACHE_SHIFT		12
#घोषणा FSL_RE_CDB_BUFFER_MASK		0x00000800
#घोषणा FSL_RE_CDB_BUFFER_SHIFT		11
#घोषणा FSL_RE_CDB_ERROR_MASK		0x00000400
#घोषणा FSL_RE_CDB_ERROR_SHIFT		10
#घोषणा FSL_RE_CDB_NRCS_MASK		0x0000003C
#घोषणा FSL_RE_CDB_NRCS_SHIFT		6
#घोषणा FSL_RE_CDB_DEPEND_MASK		0x00000008
#घोषणा FSL_RE_CDB_DEPEND_SHIFT		3
#घोषणा FSL_RE_CDB_DPI_MASK		0x00000004
#घोषणा FSL_RE_CDB_DPI_SHIFT		2

/*
 * the largest cf block is 19*माप(काष्ठा cmpnd_frame), which is 304 bytes.
 * here 19 = 1(cdb)+2(dest)+16(src), align to 64bytes, that is 320 bytes.
 * the largest cdb block: काष्ठा pq_cdb which is 180 bytes, adding to cf block
 * 320+180=500, align to 64bytes, that is 512 bytes.
 */
#घोषणा FSL_RE_CF_DESC_SIZE		320
#घोषणा FSL_RE_CF_CDB_SIZE		512
#घोषणा FSL_RE_CF_CDB_ALIGN		64

काष्ठा fsl_re_ctrl अणु
	/* General Configuration Registers */
	__be32 global_config;	/* Global Configuration Register */
	u8     rsvd1[4];
	__be32 galois_field_config; /* Galois Field Configuration Register */
	u8     rsvd2[4];
	__be32 jq_wrr_config;   /* WRR Configuration रेजिस्टर */
	u8     rsvd3[4];
	__be32 crc_config;	/* CRC Configuration रेजिस्टर */
	u8     rsvd4[228];
	__be32 प्रणाली_reset;	/* System Reset Register */
	u8     rsvd5[252];
	__be32 global_status;	/* Global Status Register */
	u8     rsvd6[832];
	__be32 re_liodn_base;	/* LIODN Base Register */
	u8     rsvd7[1712];
	__be32 re_version_id;	/* Version ID रेजिस्टर of RE */
	__be32 re_version_id_2; /* Version ID 2 रेजिस्टर of RE */
	u8     rsvd8[512];
	__be32 host_config;	/* Host I/F Configuration Register */
पूर्ण;

काष्ठा fsl_re_chan_cfg अणु
	/* Registers क्रम JR पूर्णांकerface */
	__be32 jr_config_0;	/* Job Queue Configuration 0 Register */
	__be32 jr_config_1;	/* Job Queue Configuration 1 Register */
	__be32 jr_पूर्णांकerrupt_status; /* Job Queue Interrupt Status Register */
	u8     rsvd1[4];
	__be32 jr_command;	/* Job Queue Command Register */
	u8     rsvd2[4];
	__be32 jr_status;	/* Job Queue Status Register */
	u8     rsvd3[228];

	/* Input Ring */
	__be32 inbring_base_h;	/* Inbound Ring Base Address Register - High */
	__be32 inbring_base_l;	/* Inbound Ring Base Address Register - Low */
	__be32 inbring_size;	/* Inbound Ring Size Register */
	u8     rsvd4[4];
	__be32 inbring_slot_avail; /* Inbound Ring Slot Available Register */
	u8     rsvd5[4];
	__be32 inbring_add_job;	/* Inbound Ring Add Job Register */
	u8     rsvd6[4];
	__be32 inbring_cnsmr_indx; /* Inbound Ring Consumer Index Register */
	u8     rsvd7[220];

	/* Output Ring */
	__be32 oubring_base_h;	/* Outbound Ring Base Address Register - High */
	__be32 oubring_base_l;	/* Outbound Ring Base Address Register - Low */
	__be32 oubring_size;	/* Outbound Ring Size Register */
	u8     rsvd8[4];
	__be32 oubring_job_rmvd; /* Outbound Ring Job Removed Register */
	u8     rsvd9[4];
	__be32 oubring_slot_full; /* Outbound Ring Slot Full Register */
	u8     rsvd10[4];
	__be32 oubring_prdcr_indx; /* Outbound Ring Producer Index */
पूर्ण;

/*
 * Command Descriptor Block (CDB) क्रम unicast move command.
 * In RAID Engine terms, स_नकल is करोne through move command
 */
काष्ठा fsl_re_move_cdb अणु
	__be32 cdb32;
पूर्ण;

/* Data protection/पूर्णांकegrity related fields */
#घोषणा FSL_RE_DPI_APPS_MASK		0xC0000000
#घोषणा FSL_RE_DPI_APPS_SHIFT		30
#घोषणा FSL_RE_DPI_REF_MASK		0x30000000
#घोषणा FSL_RE_DPI_REF_SHIFT		28
#घोषणा FSL_RE_DPI_GUARD_MASK		0x0C000000
#घोषणा FSL_RE_DPI_GUARD_SHIFT		26
#घोषणा FSL_RE_DPI_ATTR_MASK		0x03000000
#घोषणा FSL_RE_DPI_ATTR_SHIFT		24
#घोषणा FSL_RE_DPI_META_MASK		0x0000FFFF

काष्ठा fsl_re_dpi अणु
	__be32 dpi32;
	__be32 ref;
पूर्ण;

/*
 * CDB क्रम GenQ command. In RAID Engine terminology, XOR is
 * करोne through this command
 */
काष्ठा fsl_re_xor_cdb अणु
	__be32 cdb32;
	u8 gfm[16];
	काष्ठा fsl_re_dpi dpi_dest_spec;
	काष्ठा fsl_re_dpi dpi_src_spec[16];
पूर्ण;

/* CDB क्रम no-op command */
काष्ठा fsl_re_noop_cdb अणु
	__be32 cdb32;
पूर्ण;

/*
 * CDB क्रम GenQQ command. In RAID Engine terminology, P/Q is
 * करोne through this command
 */
काष्ठा fsl_re_pq_cdb अणु
	__be32 cdb32;
	u8 gfm_q1[16];
	u8 gfm_q2[16];
	काष्ठा fsl_re_dpi dpi_dest_spec[2];
	काष्ठा fsl_re_dpi dpi_src_spec[16];
पूर्ण;

/* Compound frame */
#घोषणा FSL_RE_CF_ADDR_HIGH_MASK	0x000000FF
#घोषणा FSL_RE_CF_EXT_MASK		0x80000000
#घोषणा FSL_RE_CF_EXT_SHIFT		31
#घोषणा FSL_RE_CF_FINAL_MASK		0x40000000
#घोषणा FSL_RE_CF_FINAL_SHIFT		30
#घोषणा FSL_RE_CF_LENGTH_MASK		0x000FFFFF
#घोषणा FSL_RE_CF_BPID_MASK		0x00FF0000
#घोषणा FSL_RE_CF_BPID_SHIFT		16
#घोषणा FSL_RE_CF_OFFSET_MASK		0x00001FFF

काष्ठा fsl_re_cmpnd_frame अणु
	__be32 addr_high;
	__be32 addr_low;
	__be32 efrl32;
	__be32 rbro32;
पूर्ण;

/* Frame descriptor */
#घोषणा FSL_RE_HWDESC_LIODN_MASK	0x3F000000
#घोषणा FSL_RE_HWDESC_LIODN_SHIFT	24
#घोषणा FSL_RE_HWDESC_BPID_MASK		0x00FF0000
#घोषणा FSL_RE_HWDESC_BPID_SHIFT	16
#घोषणा FSL_RE_HWDESC_ELIODN_MASK	0x0000F000
#घोषणा FSL_RE_HWDESC_ELIODN_SHIFT	12
#घोषणा FSL_RE_HWDESC_FMT_SHIFT		29
#घोषणा FSL_RE_HWDESC_FMT_MASK		(0x3 << FSL_RE_HWDESC_FMT_SHIFT)

काष्ठा fsl_re_hw_desc अणु
	__be32 lbea32;
	__be32 addr_low;
	__be32 fmt32;
	__be32 status;
पूर्ण;

/* Raid Engine device निजी data */
काष्ठा fsl_re_drv_निजी अणु
	u8 total_chans;
	काष्ठा dma_device dma_dev;
	काष्ठा fsl_re_ctrl *re_regs;
	काष्ठा fsl_re_chan *re_jrs[FSL_RE_MAX_CHANS];
	काष्ठा dma_pool *cf_desc_pool;
	काष्ठा dma_pool *hw_desc_pool;
पूर्ण;

/* Per job ring data काष्ठाure */
काष्ठा fsl_re_chan अणु
	अक्षर name[16];
	spinlock_t desc_lock; /* queue lock */
	काष्ठा list_head ack_q;  /* रुको to acked queue */
	काष्ठा list_head active_q; /* alपढ़ोy issued on hw, not completed */
	काष्ठा list_head submit_q;
	काष्ठा list_head मुक्त_q; /* alloc available queue */
	काष्ठा device *dev;
	काष्ठा fsl_re_drv_निजी *re_dev;
	काष्ठा dma_chan chan;
	काष्ठा fsl_re_chan_cfg *jrregs;
	पूर्णांक irq;
	काष्ठा tasklet_काष्ठा irqtask;
	u32 alloc_count;

	/* hw descriptor ring क्रम inbound queue*/
	dma_addr_t inb_phys_addr;
	काष्ठा fsl_re_hw_desc *inb_ring_virt_addr;
	u32 inb_count;

	/* hw descriptor ring क्रम outbound queue */
	dma_addr_t oub_phys_addr;
	काष्ठा fsl_re_hw_desc *oub_ring_virt_addr;
	u32 oub_count;
पूर्ण;

/* Async transaction descriptor */
काष्ठा fsl_re_desc अणु
	काष्ठा dma_async_tx_descriptor async_tx;
	काष्ठा list_head node;
	काष्ठा fsl_re_hw_desc hwdesc;
	काष्ठा fsl_re_chan *re_chan;

	/* hwdesc will poपूर्णांक to cf_addr */
	व्योम *cf_addr;
	dma_addr_t cf_paddr;

	व्योम *cdb_addr;
	dma_addr_t cdb_paddr;
	पूर्णांक status;
पूर्ण;
