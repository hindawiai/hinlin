<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * console.h
 *
 * Console I/O पूर्णांकerface क्रम Xen guest OSes.
 *
 * Copyright (c) 2005, Keir Fraser
 */

#अगर_अघोषित __XEN_PUBLIC_IO_CONSOLE_H__
#घोषणा __XEN_PUBLIC_IO_CONSOLE_H__

प्रकार uपूर्णांक32_t XENCONS_RING_IDX;

#घोषणा MASK_XENCONS_IDX(idx, ring) ((idx) & (माप(ring)-1))

काष्ठा xencons_पूर्णांकerface अणु
    अक्षर in[1024];
    अक्षर out[2048];
    XENCONS_RING_IDX in_cons, in_prod;
    XENCONS_RING_IDX out_cons, out_prod;
पूर्ण;

#पूर्ण_अगर /* __XEN_PUBLIC_IO_CONSOLE_H__ */
