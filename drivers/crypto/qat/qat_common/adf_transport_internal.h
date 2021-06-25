<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_TRANSPORT_INTRN_H
#घोषणा ADF_TRANSPORT_INTRN_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock_types.h>
#समावेश "adf_transport.h"

काष्ठा adf_etr_ring_debug_entry अणु
	अक्षर ring_name[ADF_CFG_MAX_KEY_LEN_IN_BYTES];
	काष्ठा dentry *debug;
पूर्ण;

काष्ठा adf_etr_ring_data अणु
	व्योम *base_addr;
	atomic_t *inflights;
	adf_callback_fn callback;
	काष्ठा adf_etr_bank_data *bank;
	dma_addr_t dma_addr;
	काष्ठा adf_etr_ring_debug_entry *ring_debug;
	spinlock_t lock;	/* protects ring data काष्ठा */
	u16 head;
	u16 tail;
	u8 ring_number;
	u8 ring_size;
	u8 msg_size;
पूर्ण;

काष्ठा adf_etr_bank_data अणु
	काष्ठा adf_etr_ring_data *rings;
	काष्ठा tasklet_काष्ठा resp_handler;
	व्योम __iomem *csr_addr;
	u32 irq_coalesc_समयr;
	u32 bank_number;
	u16 ring_mask;
	u16 irq_mask;
	spinlock_t lock;	/* protects bank data काष्ठा */
	काष्ठा adf_accel_dev *accel_dev;
	काष्ठा dentry *bank_debug_dir;
	काष्ठा dentry *bank_debug_cfg;
पूर्ण;

काष्ठा adf_etr_data अणु
	काष्ठा adf_etr_bank_data *banks;
	काष्ठा dentry *debug;
पूर्ण;

व्योम adf_response_handler(uपूर्णांकptr_t bank_addr);
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>
पूर्णांक adf_bank_debugfs_add(काष्ठा adf_etr_bank_data *bank);
व्योम adf_bank_debugfs_rm(काष्ठा adf_etr_bank_data *bank);
पूर्णांक adf_ring_debugfs_add(काष्ठा adf_etr_ring_data *ring, स्थिर अक्षर *name);
व्योम adf_ring_debugfs_rm(काष्ठा adf_etr_ring_data *ring);
#अन्यथा
अटल अंतरभूत पूर्णांक adf_bank_debugfs_add(काष्ठा adf_etr_bank_data *bank)
अणु
	वापस 0;
पूर्ण

#घोषणा adf_bank_debugfs_rm(bank) करो अणुपूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक adf_ring_debugfs_add(काष्ठा adf_etr_ring_data *ring,
				       स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

#घोषणा adf_ring_debugfs_rm(ring) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#पूर्ण_अगर
