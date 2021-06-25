<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Smart Sound Technology (SST) DSP Core Driver
 *
 * Copyright (C) 2013, Intel Corporation. All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/delay.h>

#समावेश "sst-dsp.h"
#समावेश "sst-dsp-priv.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/पूर्णांकel-sst.h>

/* Internal generic low-level SST IO functions - can be overidden */
व्योम sst_shim32_ग_लिखो(व्योम __iomem *addr, u32 offset, u32 value)
अणु
	ग_लिखोl(value, addr + offset);
पूर्ण
EXPORT_SYMBOL_GPL(sst_shim32_ग_लिखो);

u32 sst_shim32_पढ़ो(व्योम __iomem *addr, u32 offset)
अणु
	वापस पढ़ोl(addr + offset);
पूर्ण
EXPORT_SYMBOL_GPL(sst_shim32_पढ़ो);

व्योम sst_shim32_ग_लिखो64(व्योम __iomem *addr, u32 offset, u64 value)
अणु
	ग_लिखोq(value, addr + offset);
पूर्ण
EXPORT_SYMBOL_GPL(sst_shim32_ग_लिखो64);

u64 sst_shim32_पढ़ो64(व्योम __iomem *addr, u32 offset)
अणु
	वापस पढ़ोq(addr + offset);
पूर्ण
EXPORT_SYMBOL_GPL(sst_shim32_पढ़ो64);

/* Public API */
व्योम sst_dsp_shim_ग_लिखो(काष्ठा sst_dsp *sst, u32 offset, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sst->spinlock, flags);
	sst->ops->ग_लिखो(sst->addr.shim, offset, value);
	spin_unlock_irqrestore(&sst->spinlock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_shim_ग_लिखो);

u32 sst_dsp_shim_पढ़ो(काष्ठा sst_dsp *sst, u32 offset)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&sst->spinlock, flags);
	val = sst->ops->पढ़ो(sst->addr.shim, offset);
	spin_unlock_irqrestore(&sst->spinlock, flags);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_shim_पढ़ो);

व्योम sst_dsp_shim_ग_लिखो_unlocked(काष्ठा sst_dsp *sst, u32 offset, u32 value)
अणु
	sst->ops->ग_लिखो(sst->addr.shim, offset, value);
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_shim_ग_लिखो_unlocked);

u32 sst_dsp_shim_पढ़ो_unlocked(काष्ठा sst_dsp *sst, u32 offset)
अणु
	वापस sst->ops->पढ़ो(sst->addr.shim, offset);
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_shim_पढ़ो_unlocked);

पूर्णांक sst_dsp_shim_update_bits_unlocked(काष्ठा sst_dsp *sst, u32 offset,
				u32 mask, u32 value)
अणु
	bool change;
	अचिन्हित पूर्णांक old, new;
	u32 ret;

	ret = sst_dsp_shim_पढ़ो_unlocked(sst, offset);

	old = ret;
	new = (old & (~mask)) | (value & mask);

	change = (old != new);
	अगर (change)
		sst_dsp_shim_ग_लिखो_unlocked(sst, offset, new);

	वापस change;
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_shim_update_bits_unlocked);

/* This is क्रम रेजिस्टरs bits with attribute RWC */
व्योम sst_dsp_shim_update_bits_क्रमced_unlocked(काष्ठा sst_dsp *sst, u32 offset,
				u32 mask, u32 value)
अणु
	अचिन्हित पूर्णांक old, new;
	u32 ret;

	ret = sst_dsp_shim_पढ़ो_unlocked(sst, offset);

	old = ret;
	new = (old & (~mask)) | (value & mask);

	sst_dsp_shim_ग_लिखो_unlocked(sst, offset, new);
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_shim_update_bits_क्रमced_unlocked);

पूर्णांक sst_dsp_shim_update_bits(काष्ठा sst_dsp *sst, u32 offset,
				u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	bool change;

	spin_lock_irqsave(&sst->spinlock, flags);
	change = sst_dsp_shim_update_bits_unlocked(sst, offset, mask, value);
	spin_unlock_irqrestore(&sst->spinlock, flags);
	वापस change;
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_shim_update_bits);

/* This is क्रम रेजिस्टरs bits with attribute RWC */
व्योम sst_dsp_shim_update_bits_क्रमced(काष्ठा sst_dsp *sst, u32 offset,
				u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sst->spinlock, flags);
	sst_dsp_shim_update_bits_क्रमced_unlocked(sst, offset, mask, value);
	spin_unlock_irqrestore(&sst->spinlock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_shim_update_bits_क्रमced);

पूर्णांक sst_dsp_रेजिस्टर_poll(काष्ठा sst_dsp *ctx, u32 offset, u32 mask,
			 u32 target, u32 समय, अक्षर *operation)
अणु
	u32 reg;
	अचिन्हित दीर्घ समयout;
	पूर्णांक k = 0, s = 500;

	/*
	 * split the loop पूर्णांकo sleeps of varying resolution. more accurately,
	 * the range of wakeups are:
	 * Phase 1(first 5ms): min sleep 0.5ms; max sleep 1ms.
	 * Phase 2:( 5ms to 10ms) : min sleep 0.5ms; max sleep 10ms
	 * (usleep_range (500, 1000) and usleep_range(5000, 10000) are
	 * both possible in this phase depending on whether k > 10 or not).
	 * Phase 3: (beyond 10 ms) min sleep 5ms; max sleep 10ms.
	 */

	समयout = jअगरfies + msecs_to_jअगरfies(समय);
	जबतक ((((reg = sst_dsp_shim_पढ़ो_unlocked(ctx, offset)) & mask) != target)
		&& समय_beक्रमe(jअगरfies, समयout)) अणु
		k++;
		अगर (k > 10)
			s = 5000;

		usleep_range(s, 2*s);
	पूर्ण

	अगर ((reg & mask) == target) अणु
		dev_dbg(ctx->dev, "FW Poll Status: reg=%#x %s successful\n",
					reg, operation);

		वापस 0;
	पूर्ण

	dev_dbg(ctx->dev, "FW Poll Status: reg=%#x %s timedout\n",
					reg, operation);
	वापस -ETIME;
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_रेजिस्टर_poll);

पूर्णांक sst_dsp_mailbox_init(काष्ठा sst_dsp *sst, u32 inbox_offset, माप_प्रकार inbox_size,
	u32 outbox_offset, माप_प्रकार outbox_size)
अणु
	sst->mailbox.in_base = sst->addr.lpe + inbox_offset;
	sst->mailbox.out_base = sst->addr.lpe + outbox_offset;
	sst->mailbox.in_size = inbox_size;
	sst->mailbox.out_size = outbox_size;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_mailbox_init);

व्योम sst_dsp_outbox_ग_लिखो(काष्ठा sst_dsp *sst, व्योम *message, माप_प्रकार bytes)
अणु
	u32 i;

	trace_sst_ipc_outbox_ग_लिखो(bytes);

	स_नकल_toio(sst->mailbox.out_base, message, bytes);

	क्रम (i = 0; i < bytes; i += 4)
		trace_sst_ipc_outbox_wdata(i, *(u32 *)(message + i));
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_outbox_ग_लिखो);

व्योम sst_dsp_outbox_पढ़ो(काष्ठा sst_dsp *sst, व्योम *message, माप_प्रकार bytes)
अणु
	u32 i;

	trace_sst_ipc_outbox_पढ़ो(bytes);

	स_नकल_fromio(message, sst->mailbox.out_base, bytes);

	क्रम (i = 0; i < bytes; i += 4)
		trace_sst_ipc_outbox_rdata(i, *(u32 *)(message + i));
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_outbox_पढ़ो);

व्योम sst_dsp_inbox_ग_लिखो(काष्ठा sst_dsp *sst, व्योम *message, माप_प्रकार bytes)
अणु
	u32 i;

	trace_sst_ipc_inbox_ग_लिखो(bytes);

	स_नकल_toio(sst->mailbox.in_base, message, bytes);

	क्रम (i = 0; i < bytes; i += 4)
		trace_sst_ipc_inbox_wdata(i, *(u32 *)(message + i));
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_inbox_ग_लिखो);

व्योम sst_dsp_inbox_पढ़ो(काष्ठा sst_dsp *sst, व्योम *message, माप_प्रकार bytes)
अणु
	u32 i;

	trace_sst_ipc_inbox_पढ़ो(bytes);

	स_नकल_fromio(message, sst->mailbox.in_base, bytes);

	क्रम (i = 0; i < bytes; i += 4)
		trace_sst_ipc_inbox_rdata(i, *(u32 *)(message + i));
पूर्ण
EXPORT_SYMBOL_GPL(sst_dsp_inbox_पढ़ो);

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood");
MODULE_DESCRIPTION("Intel SST Core");
MODULE_LICENSE("GPL v2");
