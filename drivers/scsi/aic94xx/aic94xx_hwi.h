<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aic94xx SAS/SATA driver hardware पूर्णांकerface header file.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#अगर_अघोषित _AIC94XX_HWI_H_
#घोषणा _AIC94XX_HWI_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>

#समावेश <scsi/libsas.h>

#समावेश "aic94xx.h"
#समावेश "aic94xx_sas.h"

/* Define ASD_MAX_PHYS to the maximum phys ever. Currently 8. */
#घोषणा ASD_MAX_PHYS       8
#घोषणा ASD_PCBA_SN_SIZE   12

काष्ठा asd_ha_addrspace अणु
	व्योम __iomem  *addr;
	अचिन्हित दीर्घ  start;       /* pci resource start */
	अचिन्हित दीर्घ  len;         /* pci resource len */
	अचिन्हित दीर्घ  flags;       /* pci resource flags */

	/* addresses पूर्णांकernal to the host adapter */
	u32 swa_base; /* mmspace 1 (MBAR1) uses this only */
	u32 swb_base;
	u32 swc_base;
पूर्ण;

काष्ठा bios_काष्ठा अणु
	पूर्णांक    present;
	u8     maj;
	u8     min;
	u32    bld;
पूर्ण;

काष्ठा unit_element_काष्ठा अणु
	u16    num;
	u16    size;
	व्योम   *area;
पूर्ण;

काष्ठा flash_काष्ठा अणु
	u32    bar;
	पूर्णांक    present;
	पूर्णांक    wide;
	u8     manuf;
	u8     dev_id;
	u8     sec_prot;
	u8     method;

	u32    dir_offs;
पूर्ण;

काष्ठा asd_phy_desc अणु
	/* From CTRL-A settings, then set to what is appropriate */
	u8     sas_addr[SAS_ADDR_SIZE];
	u8     max_sas_lrate;
	u8     min_sas_lrate;
	u8     max_sata_lrate;
	u8     min_sata_lrate;
	u8     flags;
#घोषणा ASD_CRC_DIS  1
#घोषणा ASD_SATA_SPINUP_HOLD 2

	u8     phy_control_0; /* mode 5 reg 0x160 */
	u8     phy_control_1; /* mode 5 reg 0x161 */
	u8     phy_control_2; /* mode 5 reg 0x162 */
	u8     phy_control_3; /* mode 5 reg 0x163 */
पूर्ण;

काष्ठा asd_dma_tok अणु
	व्योम *vaddr;
	dma_addr_t dma_handle;
	माप_प्रकार size;
पूर्ण;

काष्ठा hw_profile अणु
	काष्ठा bios_काष्ठा bios;
	काष्ठा unit_element_काष्ठा ue;
	काष्ठा flash_काष्ठा flash;

	u8     sas_addr[SAS_ADDR_SIZE];
	अक्षर   pcba_sn[ASD_PCBA_SN_SIZE+1];

	u8     enabled_phys;	  /* mask of enabled phys */
	काष्ठा asd_phy_desc phy_desc[ASD_MAX_PHYS];
	u32    max_scbs;	  /* असलolute sequencer scb queue size */
	काष्ठा asd_dma_tok *scb_ext;
	u32    max_ddbs;
	काष्ठा asd_dma_tok *ddb_ext;

	spinlock_t ddb_lock;
	व्योम  *ddb_biपंचांगap;

	पूर्णांक    num_phys;	  /* ENABLEABLE */
	पूर्णांक    max_phys;	  /* REPORTED + ENABLEABLE */

	अचिन्हित addr_range;	  /* max # of addrs; max # of possible ports */
	अचिन्हित port_name_base;
	अचिन्हित dev_name_base;
	अचिन्हित sata_name_base;
पूर्ण;

काष्ठा asd_ascb अणु
	काष्ठा list_head list;
	काष्ठा asd_ha_काष्ठा *ha;

	काष्ठा scb *scb;	  /* equals dma_scb->vaddr */
	काष्ठा asd_dma_tok dma_scb;
	काष्ठा asd_dma_tok *sg_arr;

	व्योम (*tasklet_complete)(काष्ठा asd_ascb *, काष्ठा करोne_list_काष्ठा *);
	u8     uldd_समयr:1;

	/* पूर्णांकernally generated command */
	काष्ठा समयr_list समयr;
	काष्ठा completion *completion;
	u8        tag_valid:1;
	__be16    tag;		  /* error recovery only */

	/* If this is an Empty SCB, index of first edb in seq->edb_arr. */
	पूर्णांक    edb_index;

	/* Used by the समयr समयout function. */
	पूर्णांक    tc_index;

	व्योम   *uldd_task;
पूर्ण;

#घोषणा ASD_DL_SIZE_BITS   0x8
#घोषणा ASD_DL_SIZE        (1<<(2+ASD_DL_SIZE_BITS))
#घोषणा ASD_DEF_DL_TOGGLE  0x01

काष्ठा asd_seq_data अणु
	spinlock_t pend_q_lock;
	u16    scbpro;
	पूर्णांक    pending;
	काष्ठा list_head pend_q;
	पूर्णांक    can_queue;	  /* per adapter */
	काष्ठा asd_dma_tok next_scb; /* next scb to be delivered to CSEQ */

	spinlock_t tc_index_lock;
	व्योम **tc_index_array;
	व्योम *tc_index_biपंचांगap;
	पूर्णांक   tc_index_biपंचांगap_bits;

	काष्ठा tasklet_काष्ठा dl_tasklet;
	काष्ठा करोne_list_काष्ठा *dl; /* array of करोne list entries, equals */
	काष्ठा asd_dma_tok *actual_dl; /* actual_dl->vaddr */
	पूर्णांक    dl_toggle;
	पूर्णांक    dl_next;

	पूर्णांक    num_edbs;
	काष्ठा asd_dma_tok **edb_arr;
	पूर्णांक    num_escbs;
	काष्ठा asd_ascb **escb_arr; /* array of poपूर्णांकers to escbs */
पूर्ण;

/* This is an पूर्णांकernal port काष्ठाure. These are used to get accurate
 * phy_mask क्रम updating DDB 0.
 */
काष्ठा asd_port अणु
	u8  sas_addr[SAS_ADDR_SIZE];
	u8  attached_sas_addr[SAS_ADDR_SIZE];
	u32 phy_mask;
	पूर्णांक num_phys;
पूर्ण;

/* This is the Host Adapter काष्ठाure.  It describes the hardware
 * SAS adapter.
 */
काष्ठा asd_ha_काष्ठा अणु
	काष्ठा pci_dev   *pcidev;
	स्थिर अक्षर       *name;

	काष्ठा sas_ha_काष्ठा sas_ha;

	u8                revision_id;

	पूर्णांक               iospace;
	spinlock_t        iolock;
	काष्ठा asd_ha_addrspace io_handle[2];

	काष्ठा hw_profile hw_prof;

	काष्ठा asd_phy    phys[ASD_MAX_PHYS];
	spinlock_t        asd_ports_lock;
	काष्ठा asd_port   asd_ports[ASD_MAX_PHYS];
	काष्ठा asd_sas_port   ports[ASD_MAX_PHYS];

	काष्ठा dma_pool  *scb_pool;

	काष्ठा asd_seq_data  seq; /* sequencer related */
	u32    bios_status;
	स्थिर काष्ठा firmware *bios_image;
पूर्ण;

/* ---------- Common macros ---------- */

#घोषणा ASD_BUSADDR_LO(__dma_handle) ((u32)(__dma_handle))
#घोषणा ASD_BUSADDR_HI(__dma_handle) (((माप(dma_addr_t))==8)     \
                                    ? ((u32)((__dma_handle) >> 32)) \
                                    : ((u32)0))

#घोषणा dev_to_asd_ha(__dev)  pci_get_drvdata(to_pci_dev(__dev))
#घोषणा SCB_SITE_VALID(__site_no) (((__site_no) & 0xF0FF) != 0x00FF   \
				 && ((__site_no) & 0xF0FF) > 0x001F)
/* For each bit set in __lseq_mask, set __lseq to equal the bit
 * position of the set bit and execute the statement following.
 * __mc is the temporary mask, used as a mask "counter".
 */
#घोषणा क्रम_each_sequencer(__lseq_mask, __mc, __lseq)                        \
	क्रम ((__mc)=(__lseq_mask),(__lseq)=0;(__mc)!=0;(__lseq++),(__mc)>>=1)\
		अगर (((__mc) & 1))
#घोषणा क्रम_each_phy(__lseq_mask, __mc, __lseq)                              \
	क्रम ((__mc)=(__lseq_mask),(__lseq)=0;(__mc)!=0;(__lseq++),(__mc)>>=1)\
		अगर (((__mc) & 1))

#घोषणा PHY_ENABLED(_HA, _I) ((_HA)->hw_prof.enabled_phys & (1<<(_I)))

/* ---------- DMA allocs ---------- */

अटल अंतरभूत काष्ठा asd_dma_tok *asd_dmatok_alloc(gfp_t flags)
अणु
	वापस kmem_cache_alloc(asd_dma_token_cache, flags);
पूर्ण

अटल अंतरभूत व्योम asd_dmatok_मुक्त(काष्ठा asd_dma_tok *token)
अणु
	kmem_cache_मुक्त(asd_dma_token_cache, token);
पूर्ण

अटल अंतरभूत काष्ठा asd_dma_tok *asd_alloc_coherent(काष्ठा asd_ha_काष्ठा *
						     asd_ha, माप_प्रकार size,
						     gfp_t flags)
अणु
	काष्ठा asd_dma_tok *token = asd_dmatok_alloc(flags);
	अगर (token) अणु
		token->size = size;
		token->vaddr = dma_alloc_coherent(&asd_ha->pcidev->dev,
						  token->size,
						  &token->dma_handle,
						  flags);
		अगर (!token->vaddr) अणु
			asd_dmatok_मुक्त(token);
			token = शून्य;
		पूर्ण
	पूर्ण
	वापस token;
पूर्ण

अटल अंतरभूत व्योम asd_मुक्त_coherent(काष्ठा asd_ha_काष्ठा *asd_ha,
				     काष्ठा asd_dma_tok *token)
अणु
	अगर (token) अणु
		dma_मुक्त_coherent(&asd_ha->pcidev->dev, token->size,
				  token->vaddr, token->dma_handle);
		asd_dmatok_मुक्त(token);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम asd_init_ascb(काष्ठा asd_ha_काष्ठा *asd_ha,
				 काष्ठा asd_ascb *ascb)
अणु
	INIT_LIST_HEAD(&ascb->list);
	ascb->scb = ascb->dma_scb.vaddr;
	ascb->ha = asd_ha;
	समयr_setup(&ascb->समयr, शून्य, 0);
	ascb->tc_index = -1;
पूर्ण

/* Must be called with the tc_index_lock held!
 */
अटल अंतरभूत व्योम asd_tc_index_release(काष्ठा asd_seq_data *seq, पूर्णांक index)
अणु
	seq->tc_index_array[index] = शून्य;
	clear_bit(index, seq->tc_index_biपंचांगap);
पूर्ण

/* Must be called with the tc_index_lock held!
 */
अटल अंतरभूत पूर्णांक asd_tc_index_get(काष्ठा asd_seq_data *seq, व्योम *ptr)
अणु
	पूर्णांक index;

	index = find_first_zero_bit(seq->tc_index_biपंचांगap,
				    seq->tc_index_biपंचांगap_bits);
	अगर (index == seq->tc_index_biपंचांगap_bits)
		वापस -1;

	seq->tc_index_array[index] = ptr;
	set_bit(index, seq->tc_index_biपंचांगap);

	वापस index;
पूर्ण

/* Must be called with the tc_index_lock held!
 */
अटल अंतरभूत व्योम *asd_tc_index_find(काष्ठा asd_seq_data *seq, पूर्णांक index)
अणु
	वापस seq->tc_index_array[index];
पूर्ण

/**
 * asd_ascb_मुक्त -- मुक्त a single aSCB after is has completed
 * @ascb: poपूर्णांकer to the aSCB of पूर्णांकerest
 *
 * This मुक्तs an aSCB after it has been executed/completed by
 * the sequencer.
 */
अटल अंतरभूत व्योम asd_ascb_मुक्त(काष्ठा asd_ascb *ascb)
अणु
	अगर (ascb) अणु
		काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
		अचिन्हित दीर्घ flags;

		BUG_ON(!list_empty(&ascb->list));
		spin_lock_irqsave(&ascb->ha->seq.tc_index_lock, flags);
		asd_tc_index_release(&ascb->ha->seq, ascb->tc_index);
		spin_unlock_irqrestore(&ascb->ha->seq.tc_index_lock, flags);
		dma_pool_मुक्त(asd_ha->scb_pool, ascb->dma_scb.vaddr,
			      ascb->dma_scb.dma_handle);
		kmem_cache_मुक्त(asd_ascb_cache, ascb);
	पूर्ण
पूर्ण

/**
 * asd_ascb_list_मुक्त -- मुक्त a list of ascbs
 * @ascb_list: a list of ascbs
 *
 * This function will मुक्त a list of ascbs allocated by asd_ascb_alloc_list.
 * It is used when say the scb queueing function वापसed QUEUE_FULL,
 * and we करो not need the ascbs any more.
 */
अटल अंतरभूत व्योम asd_ascb_मुक्त_list(काष्ठा asd_ascb *ascb_list)
अणु
	LIST_HEAD(list);
	काष्ठा list_head *n, *pos;

	__list_add(&list, ascb_list->list.prev, &ascb_list->list);
	list_क्रम_each_safe(pos, n, &list) अणु
		list_del_init(pos);
		asd_ascb_मुक्त(list_entry(pos, काष्ठा asd_ascb, list));
	पूर्ण
पूर्ण

/* ---------- Function declarations ---------- */

पूर्णांक  asd_init_hw(काष्ठा asd_ha_काष्ठा *asd_ha);
irqवापस_t asd_hw_isr(पूर्णांक irq, व्योम *dev_id);


काष्ठा asd_ascb *asd_ascb_alloc_list(काष्ठा asd_ha_काष्ठा
				     *asd_ha, पूर्णांक *num,
				     gfp_t gfp_mask);

पूर्णांक  asd_post_ascb_list(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_ascb *ascb,
			पूर्णांक num);
पूर्णांक  asd_post_escb_list(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_ascb *ascb,
			पूर्णांक num);

पूर्णांक  asd_init_post_escbs(काष्ठा asd_ha_काष्ठा *asd_ha);
व्योम asd_build_control_phy(काष्ठा asd_ascb *ascb, पूर्णांक phy_id, u8 subfunc);
व्योम asd_control_led(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक phy_id, पूर्णांक op);
व्योम asd_turn_led(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक phy_id, पूर्णांक op);
पूर्णांक  asd_enable_phys(काष्ठा asd_ha_काष्ठा *asd_ha, स्थिर u8 phy_mask);

व्योम asd_ascb_समयकरोut(काष्ठा समयr_list *t);
पूर्णांक  asd_chip_hardrst(काष्ठा asd_ha_काष्ठा *asd_ha);

#पूर्ण_अगर
