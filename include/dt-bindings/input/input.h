<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम most input bindings.
 *
 * Most input bindings include key code, matrix key code क्रमmat.
 * In most हालs, key code and matrix key code क्रमmat uses
 * the standard values/macro defined in this header.
 */

#अगर_अघोषित _DT_BINDINGS_INPUT_INPUT_H
#घोषणा _DT_BINDINGS_INPUT_INPUT_H

#समावेश "linux-event-codes.h"

#घोषणा MATRIX_KEY(row, col, code)	\
	((((row) & 0xFF) << 24) | (((col) & 0xFF) << 16) | ((code) & 0xFFFF))

#पूर्ण_अगर /* _DT_BINDINGS_INPUT_INPUT_H */
