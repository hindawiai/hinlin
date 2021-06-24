<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 hvcall exports क्रम modules.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#घोषणा LV1_CALL(name, in, out, num)                          \
  बाह्य s64 _lv1_##name(LV1_##in##_IN_##out##_OUT_ARG_DECL); \
  EXPORT_SYMBOL(_lv1_##name);

#समावेश <यंत्र/lv1call.h>
