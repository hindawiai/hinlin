<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Raw Decoder found in PowerDown Controller.
 *
 * Copyright 2010-2014 Imagination Technologies Ltd.
 *
 * This ties पूर्णांकo the input subप्रणाली using the RC-core in raw mode. Raw IR
 * संकेत edges are reported and decoded by generic software decoders.
 */

#समावेश <linux/spinlock.h>
#समावेश <media/rc-core.h>
#समावेश "img-ir.h"

#घोषणा ECHO_TIMEOUT_MS 150	/* ms between echos */

/* must be called with priv->lock held */
अटल व्योम img_ir_refresh_raw(काष्ठा img_ir_priv *priv, u32 irq_status)
अणु
	काष्ठा img_ir_priv_raw *raw = &priv->raw;
	काष्ठा rc_dev *rc_dev = priv->raw.rdev;
	पूर्णांक multiple;
	u32 ir_status;

	/* find whether both rise and fall was detected */
	multiple = ((irq_status & IMG_IR_IRQ_EDGE) == IMG_IR_IRQ_EDGE);
	/*
	 * If so, we need to see अगर the level has actually changed.
	 * If it's just noise that we didn't have समय to process,
	 * there's no poपूर्णांक reporting it.
	 */
	ir_status = img_ir_पढ़ो(priv, IMG_IR_STATUS) & IMG_IR_IRRXD;
	अगर (multiple && ir_status == raw->last_status)
		वापस;
	raw->last_status = ir_status;

	/* report the edge to the IR raw decoders */
	अगर (ir_status) /* low */
		ir_raw_event_store_edge(rc_dev, false);
	अन्यथा /* high */
		ir_raw_event_store_edge(rc_dev, true);
	ir_raw_event_handle(rc_dev);
पूर्ण

/* called with priv->lock held */
व्योम img_ir_isr_raw(काष्ठा img_ir_priv *priv, u32 irq_status)
अणु
	काष्ठा img_ir_priv_raw *raw = &priv->raw;

	/* check not removing */
	अगर (!raw->rdev)
		वापस;

	img_ir_refresh_raw(priv, irq_status);

	/* start / push back the echo समयr */
	mod_समयr(&raw->समयr, jअगरfies + msecs_to_jअगरfies(ECHO_TIMEOUT_MS));
पूर्ण

/*
 * Echo समयr callback function.
 * The raw decoders expect to get a final sample even अगर there are no edges, in
 * order to be assured of the final space. If there are no edges क्रम a certain
 * समय we use this समयr to emit a final sample to satisfy them.
 */
अटल व्योम img_ir_echo_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा img_ir_priv *priv = from_समयr(priv, t, raw.समयr);

	spin_lock_irq(&priv->lock);

	/* check not removing */
	अगर (priv->raw.rdev)
		/*
		 * It's safe to pass irq_status=0 since it's only used to check
		 * क्रम द्विगुन edges.
		 */
		img_ir_refresh_raw(priv, 0);

	spin_unlock_irq(&priv->lock);
पूर्ण

व्योम img_ir_setup_raw(काष्ठा img_ir_priv *priv)
अणु
	u32 irq_en;

	अगर (!priv->raw.rdev)
		वापस;

	/* clear and enable edge पूर्णांकerrupts */
	spin_lock_irq(&priv->lock);
	irq_en = img_ir_पढ़ो(priv, IMG_IR_IRQ_ENABLE);
	irq_en |= IMG_IR_IRQ_EDGE;
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_CLEAR, IMG_IR_IRQ_EDGE);
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE, irq_en);
	spin_unlock_irq(&priv->lock);
पूर्ण

पूर्णांक img_ir_probe_raw(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_raw *raw = &priv->raw;
	काष्ठा rc_dev *rdev;
	पूर्णांक error;

	/* Set up the echo समयr */
	समयr_setup(&raw->समयr, img_ir_echo_समयr, 0);

	/* Allocate raw decoder */
	raw->rdev = rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rdev) अणु
		dev_err(priv->dev, "cannot allocate raw input device\n");
		वापस -ENOMEM;
	पूर्ण
	rdev->priv = priv;
	rdev->map_name = RC_MAP_EMPTY;
	rdev->device_name = "IMG Infrared Decoder Raw";

	/* Register raw decoder */
	error = rc_रेजिस्टर_device(rdev);
	अगर (error) अणु
		dev_err(priv->dev, "failed to register raw IR input device\n");
		rc_मुक्त_device(rdev);
		raw->rdev = शून्य;
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

व्योम img_ir_हटाओ_raw(काष्ठा img_ir_priv *priv)
अणु
	काष्ठा img_ir_priv_raw *raw = &priv->raw;
	काष्ठा rc_dev *rdev = raw->rdev;
	u32 irq_en;

	अगर (!rdev)
		वापस;

	/* चयन off and disable raw (edge) पूर्णांकerrupts */
	spin_lock_irq(&priv->lock);
	raw->rdev = शून्य;
	irq_en = img_ir_पढ़ो(priv, IMG_IR_IRQ_ENABLE);
	irq_en &= ~IMG_IR_IRQ_EDGE;
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE, irq_en);
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_CLEAR, IMG_IR_IRQ_EDGE);
	spin_unlock_irq(&priv->lock);

	rc_unरेजिस्टर_device(rdev);

	del_समयr_sync(&raw->समयr);
पूर्ण
