<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    I2C functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_I2C_H
#घोषणा IVTV_I2C_H

व्योम ivtv_i2c_new_ir_legacy(काष्ठा ivtv *itv);
पूर्णांक ivtv_i2c_रेजिस्टर(काष्ठा ivtv *itv, अचिन्हित idx);
काष्ठा v4l2_subdev *ivtv_find_hw(काष्ठा ivtv *itv, u32 hw);

/* init + रेजिस्टर i2c adapter */
पूर्णांक init_ivtv_i2c(काष्ठा ivtv *itv);
व्योम निकास_ivtv_i2c(काष्ठा ivtv *itv);

#पूर्ण_अगर
