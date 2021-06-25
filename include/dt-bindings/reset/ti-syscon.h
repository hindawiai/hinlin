<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * TI Syscon Reset definitions
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 */

#अगर_अघोषित __DT_BINDINGS_RESET_TI_SYSCON_H__
#घोषणा __DT_BINDINGS_RESET_TI_SYSCON_H__

/*
 * The reset करोes not support the feature and corresponding
 * values are not valid
 */
#घोषणा ASSERT_NONE	(1 << 0)
#घोषणा DEASSERT_NONE	(1 << 1)
#घोषणा STATUS_NONE	(1 << 2)

/* When set this function is activated by setting(vs clearing) this bit */
#घोषणा ASSERT_SET	(1 << 3)
#घोषणा DEASSERT_SET	(1 << 4)
#घोषणा STATUS_SET	(1 << 5)

/* The following are the inverse of the above and are added क्रम consistency */
#घोषणा ASSERT_CLEAR	(0 << 3)
#घोषणा DEASSERT_CLEAR	(0 << 4)
#घोषणा STATUS_CLEAR	(0 << 5)

#पूर्ण_अगर
