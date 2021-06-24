<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel Smart Sound Technology (SST) Core
 *
 * Copyright (C) 2013, Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __SOUND_SOC_SST_DSP_H
#घोषणा __SOUND_SOC_SST_DSP_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा sst_dsp;

/*
 * SST Device.
 *
 * This काष्ठाure is populated by the SST core driver.
 */
काष्ठा sst_dsp_device अणु
	/* Mandatory fields */
	काष्ठा sst_ops *ops;
	irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *context);
	व्योम *thपढ़ो_context;
पूर्ण;

/* SHIM Read / Write */
व्योम sst_dsp_shim_ग_लिखो(काष्ठा sst_dsp *sst, u32 offset, u32 value);
u32 sst_dsp_shim_पढ़ो(काष्ठा sst_dsp *sst, u32 offset);
पूर्णांक sst_dsp_shim_update_bits(काष्ठा sst_dsp *sst, u32 offset,
				u32 mask, u32 value);
व्योम sst_dsp_shim_update_bits_क्रमced(काष्ठा sst_dsp *sst, u32 offset,
				u32 mask, u32 value);

/* SHIM Read / Write Unlocked क्रम callers alपढ़ोy holding sst lock */
व्योम sst_dsp_shim_ग_लिखो_unlocked(काष्ठा sst_dsp *sst, u32 offset, u32 value);
u32 sst_dsp_shim_पढ़ो_unlocked(काष्ठा sst_dsp *sst, u32 offset);
पूर्णांक sst_dsp_shim_update_bits_unlocked(काष्ठा sst_dsp *sst, u32 offset,
				u32 mask, u32 value);
व्योम sst_dsp_shim_update_bits_क्रमced_unlocked(काष्ठा sst_dsp *sst, u32 offset,
				u32 mask, u32 value);

/* Internal generic low-level SST IO functions - can be overidden */
व्योम sst_shim32_ग_लिखो(व्योम __iomem *addr, u32 offset, u32 value);
u32 sst_shim32_पढ़ो(व्योम __iomem *addr, u32 offset);
व्योम sst_shim32_ग_लिखो64(व्योम __iomem *addr, u32 offset, u64 value);
u64 sst_shim32_पढ़ो64(व्योम __iomem *addr, u32 offset);

/* Mailbox management */
पूर्णांक sst_dsp_mailbox_init(काष्ठा sst_dsp *sst, u32 inbox_offset,
	माप_प्रकार inbox_size, u32 outbox_offset, माप_प्रकार outbox_size);
व्योम sst_dsp_inbox_ग_लिखो(काष्ठा sst_dsp *sst, व्योम *message, माप_प्रकार bytes);
व्योम sst_dsp_inbox_पढ़ो(काष्ठा sst_dsp *sst, व्योम *message, माप_प्रकार bytes);
व्योम sst_dsp_outbox_ग_लिखो(काष्ठा sst_dsp *sst, व्योम *message, माप_प्रकार bytes);
व्योम sst_dsp_outbox_पढ़ो(काष्ठा sst_dsp *sst, व्योम *message, माप_प्रकार bytes);
पूर्णांक sst_dsp_रेजिस्टर_poll(काष्ठा sst_dsp  *ctx, u32 offset, u32 mask,
		 u32 target, u32 समय, अक्षर *operation);

#पूर्ण_अगर
