<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/pnv-ocxl.h>
#समावेश <यंत्र/xive.h>
#समावेश "ocxl_internal.h"
#समावेश "trace.h"

काष्ठा afu_irq अणु
	पूर्णांक id;
	पूर्णांक hw_irq;
	अचिन्हित पूर्णांक virq;
	अक्षर *name;
	irqवापस_t (*handler)(व्योम *निजी);
	व्योम (*मुक्त_निजी)(व्योम *निजी);
	व्योम *निजी;
पूर्ण;

पूर्णांक ocxl_irq_offset_to_id(काष्ठा ocxl_context *ctx, u64 offset)
अणु
	वापस (offset - ctx->afu->irq_base_offset) >> PAGE_SHIFT;
पूर्ण

u64 ocxl_irq_id_to_offset(काष्ठा ocxl_context *ctx, पूर्णांक irq_id)
अणु
	वापस ctx->afu->irq_base_offset + (irq_id << PAGE_SHIFT);
पूर्ण

पूर्णांक ocxl_irq_set_handler(काष्ठा ocxl_context *ctx, पूर्णांक irq_id,
		irqवापस_t (*handler)(व्योम *निजी),
		व्योम (*मुक्त_निजी)(व्योम *निजी),
		व्योम *निजी)
अणु
	काष्ठा afu_irq *irq;
	पूर्णांक rc;

	mutex_lock(&ctx->irq_lock);
	irq = idr_find(&ctx->irq_idr, irq_id);
	अगर (!irq) अणु
		rc = -EINVAL;
		जाओ unlock;
	पूर्ण

	irq->handler = handler;
	irq->निजी = निजी;
	irq->मुक्त_निजी = मुक्त_निजी;

	rc = 0;
	// Fall through to unlock

unlock:
	mutex_unlock(&ctx->irq_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_irq_set_handler);

अटल irqवापस_t afu_irq_handler(पूर्णांक virq, व्योम *data)
अणु
	काष्ठा afu_irq *irq = (काष्ठा afu_irq *) data;

	trace_ocxl_afu_irq_receive(virq);

	अगर (irq->handler)
		वापस irq->handler(irq->निजी);

	वापस IRQ_HANDLED; // Just drop it on the ground
पूर्ण

अटल पूर्णांक setup_afu_irq(काष्ठा ocxl_context *ctx, काष्ठा afu_irq *irq)
अणु
	पूर्णांक rc;

	irq->virq = irq_create_mapping(शून्य, irq->hw_irq);
	अगर (!irq->virq) अणु
		pr_err("irq_create_mapping failed\n");
		वापस -ENOMEM;
	पूर्ण
	pr_debug("hw_irq %d mapped to virq %u\n", irq->hw_irq, irq->virq);

	irq->name = kaप्र_लिखो(GFP_KERNEL, "ocxl-afu-%u", irq->virq);
	अगर (!irq->name) अणु
		irq_dispose_mapping(irq->virq);
		वापस -ENOMEM;
	पूर्ण

	rc = request_irq(irq->virq, afu_irq_handler, 0, irq->name, irq);
	अगर (rc) अणु
		kमुक्त(irq->name);
		irq->name = शून्य;
		irq_dispose_mapping(irq->virq);
		pr_err("request_irq failed: %d\n", rc);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम release_afu_irq(काष्ठा afu_irq *irq)
अणु
	मुक्त_irq(irq->virq, irq);
	irq_dispose_mapping(irq->virq);
	kमुक्त(irq->name);
पूर्ण

पूर्णांक ocxl_afu_irq_alloc(काष्ठा ocxl_context *ctx, पूर्णांक *irq_id)
अणु
	काष्ठा afu_irq *irq;
	पूर्णांक rc;

	irq = kzalloc(माप(काष्ठा afu_irq), GFP_KERNEL);
	अगर (!irq)
		वापस -ENOMEM;

	/*
	 * We limit the number of afu irqs per context and per link to
	 * aव्योम a single process or user depleting the pool of IPIs
	 */

	mutex_lock(&ctx->irq_lock);

	irq->id = idr_alloc(&ctx->irq_idr, irq, 0, MAX_IRQ_PER_CONTEXT,
			GFP_KERNEL);
	अगर (irq->id < 0) अणु
		rc = -ENOSPC;
		जाओ err_unlock;
	पूर्ण

	rc = ocxl_link_irq_alloc(ctx->afu->fn->link, &irq->hw_irq);
	अगर (rc)
		जाओ err_idr;

	rc = setup_afu_irq(ctx, irq);
	अगर (rc)
		जाओ err_alloc;

	trace_ocxl_afu_irq_alloc(ctx->pasid, irq->id, irq->virq, irq->hw_irq);
	mutex_unlock(&ctx->irq_lock);

	*irq_id = irq->id;

	वापस 0;

err_alloc:
	ocxl_link_मुक्त_irq(ctx->afu->fn->link, irq->hw_irq);
err_idr:
	idr_हटाओ(&ctx->irq_idr, irq->id);
err_unlock:
	mutex_unlock(&ctx->irq_lock);
	kमुक्त(irq);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_afu_irq_alloc);

अटल व्योम afu_irq_मुक्त(काष्ठा afu_irq *irq, काष्ठा ocxl_context *ctx)
अणु
	trace_ocxl_afu_irq_मुक्त(ctx->pasid, irq->id);
	अगर (ctx->mapping)
		unmap_mapping_range(ctx->mapping,
				ocxl_irq_id_to_offset(ctx, irq->id),
				1 << PAGE_SHIFT, 1);
	release_afu_irq(irq);
	अगर (irq->मुक्त_निजी)
		irq->मुक्त_निजी(irq->निजी);
	ocxl_link_मुक्त_irq(ctx->afu->fn->link, irq->hw_irq);
	kमुक्त(irq);
पूर्ण

पूर्णांक ocxl_afu_irq_मुक्त(काष्ठा ocxl_context *ctx, पूर्णांक irq_id)
अणु
	काष्ठा afu_irq *irq;

	mutex_lock(&ctx->irq_lock);

	irq = idr_find(&ctx->irq_idr, irq_id);
	अगर (!irq) अणु
		mutex_unlock(&ctx->irq_lock);
		वापस -EINVAL;
	पूर्ण
	idr_हटाओ(&ctx->irq_idr, irq->id);
	afu_irq_मुक्त(irq, ctx);
	mutex_unlock(&ctx->irq_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_afu_irq_मुक्त);

व्योम ocxl_afu_irq_मुक्त_all(काष्ठा ocxl_context *ctx)
अणु
	काष्ठा afu_irq *irq;
	पूर्णांक id;

	mutex_lock(&ctx->irq_lock);
	idr_क्रम_each_entry(&ctx->irq_idr, irq, id)
		afu_irq_मुक्त(irq, ctx);
	mutex_unlock(&ctx->irq_lock);
पूर्ण

u64 ocxl_afu_irq_get_addr(काष्ठा ocxl_context *ctx, पूर्णांक irq_id)
अणु
	काष्ठा xive_irq_data *xd;
	काष्ठा afu_irq *irq;
	u64 addr = 0;

	mutex_lock(&ctx->irq_lock);
	irq = idr_find(&ctx->irq_idr, irq_id);
	अगर (irq) अणु
		xd = irq_get_handler_data(irq->virq);
		addr = xd ? xd->trig_page : 0;
	पूर्ण
	mutex_unlock(&ctx->irq_lock);
	वापस addr;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_afu_irq_get_addr);
