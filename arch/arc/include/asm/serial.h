<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_SERIAL_H
#घोषणा _ASM_ARC_SERIAL_H

/*
 * early 8250 (now earlycon) requires BASE_BAUD to be defined in this header.
 * However to still determine it dynamically (क्रम multi-platक्रमm images)
 * we करो this in a helper by parsing the FDT early
 */

बाह्य अचिन्हित पूर्णांक __init arc_early_base_baud(व्योम);

#घोषणा BASE_BAUD	arc_early_base_baud()

#पूर्ण_अगर /* _ASM_ARC_SERIAL_H */
