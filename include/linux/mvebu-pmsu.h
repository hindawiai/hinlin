<शैली गुरु>
/*
 * Copyright (C) 2012 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __MVEBU_PMSU_H__
#घोषणा __MVEBU_PMSU_H__

#अगर_घोषित CONFIG_MACH_MVEBU_V7
पूर्णांक mvebu_pmsu_dfs_request(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत पूर्णांक mvebu_pmsu_dfs_request(पूर्णांक cpu) अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MVEBU_PMSU_H__ */
