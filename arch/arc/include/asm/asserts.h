<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Synopsys, Inc. (www.synopsys.com)
 *
 * Author: Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>
 */
#अगर_अघोषित __ASM_ARC_ASSERTS_H
#घोषणा __ASM_ARC_ASSERTS_H

/* Helpers to sanitize config options. */

व्योम chk_opt_strict(अक्षर *opt_name, bool hw_exists, bool opt_ena);
व्योम chk_opt_weak(अक्षर *opt_name, bool hw_exists, bool opt_ena);

/*
 * Check required config option:
 *  - panic in हाल of OPT enabled but corresponding HW असलent.
 *  - warn in हाल of OPT disabled but corresponding HW exists.
*/
#घोषणा CHK_OPT_STRICT(opt_name, hw_exists)				\
(अणु									\
	chk_opt_strict(#opt_name, hw_exists, IS_ENABLED(opt_name));	\
पूर्ण)

/*
 * Check optional config option:
 *  - panic in हाल of OPT enabled but corresponding HW असलent.
*/
#घोषणा CHK_OPT_WEAK(opt_name, hw_exists)				\
(अणु									\
	chk_opt_weak(#opt_name, hw_exists, IS_ENABLED(opt_name));	\
पूर्ण)

#पूर्ण_अगर /* __ASM_ARC_ASSERTS_H */
