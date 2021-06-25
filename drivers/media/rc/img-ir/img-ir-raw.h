<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ImgTec IR Raw Decoder found in PowerDown Controller.
 *
 * Copyright 2010-2014 Imagination Technologies Ltd.
 */

#अगर_अघोषित _IMG_IR_RAW_H_
#घोषणा _IMG_IR_RAW_H_

काष्ठा img_ir_priv;

#अगर_घोषित CONFIG_IR_IMG_RAW

/**
 * काष्ठा img_ir_priv_raw - Private driver data क्रम raw decoder.
 * @rdev:		Raw remote control device
 * @समयr:		Timer to echo samples to keep soft decoders happy.
 * @last_status:	Last raw status bits.
 */
काष्ठा img_ir_priv_raw अणु
	काष्ठा rc_dev		*rdev;
	काष्ठा समयr_list	समयr;
	u32			last_status;
पूर्ण;

अटल अंतरभूत bool img_ir_raw_enabled(काष्ठा img_ir_priv_raw *raw)
अणु
	वापस raw->rdev;
पूर्ण;

व्योम img_ir_isr_raw(काष्ठा img_ir_priv *priv, u32 irq_status);
व्योम img_ir_setup_raw(काष्ठा img_ir_priv *priv);
पूर्णांक img_ir_probe_raw(काष्ठा img_ir_priv *priv);
व्योम img_ir_हटाओ_raw(काष्ठा img_ir_priv *priv);

#अन्यथा

काष्ठा img_ir_priv_raw अणु
पूर्ण;
अटल अंतरभूत bool img_ir_raw_enabled(काष्ठा img_ir_priv_raw *raw)
अणु
	वापस false;
पूर्ण;
अटल अंतरभूत व्योम img_ir_isr_raw(काष्ठा img_ir_priv *priv, u32 irq_status)
अणु
पूर्ण
अटल अंतरभूत व्योम img_ir_setup_raw(काष्ठा img_ir_priv *priv)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक img_ir_probe_raw(काष्ठा img_ir_priv *priv)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम img_ir_हटाओ_raw(काष्ठा img_ir_priv *priv)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_IR_IMG_RAW */

#पूर्ण_अगर /* _IMG_IR_RAW_H_ */
