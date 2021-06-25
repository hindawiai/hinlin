<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mtu3_debug.h - debug header
 *
 * Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#अगर_अघोषित __MTU3_DEBUG_H__
#घोषणा __MTU3_DEBUG_H__

#समावेश <linux/debugfs.h>

काष्ठा ssusb_mtk;

#घोषणा MTU3_DEBUGFS_NAME_LEN 32

काष्ठा mtu3_regset अणु
	अक्षर name[MTU3_DEBUGFS_NAME_LEN];
	काष्ठा debugfs_regset32 regset;
पूर्ण;

काष्ठा mtu3_file_map अणु
	स्थिर अक्षर *name;
	पूर्णांक (*show)(काष्ठा seq_file *s, व्योम *unused);
पूर्ण;

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
व्योम ssusb_dev_debugfs_init(काष्ठा ssusb_mtk *ssusb);
व्योम ssusb_dr_debugfs_init(काष्ठा ssusb_mtk *ssusb);
व्योम ssusb_debugfs_create_root(काष्ठा ssusb_mtk *ssusb);
व्योम ssusb_debugfs_हटाओ_root(काष्ठा ssusb_mtk *ssusb);

#अन्यथा
अटल अंतरभूत व्योम ssusb_dev_debugfs_init(काष्ठा ssusb_mtk *ssusb) अणुपूर्ण
अटल अंतरभूत व्योम ssusb_dr_debugfs_init(काष्ठा ssusb_mtk *ssusb) अणुपूर्ण
अटल अंतरभूत व्योम ssusb_debugfs_create_root(काष्ठा ssusb_mtk *ssusb) अणुपूर्ण
अटल अंतरभूत व्योम ssusb_debugfs_हटाओ_root(काष्ठा ssusb_mtk *ssusb) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#अगर IS_ENABLED(CONFIG_TRACING)
व्योम mtu3_dbg_trace(काष्ठा device *dev, स्थिर अक्षर *fmt, ...);

#अन्यथा
अटल अंतरभूत व्योम mtu3_dbg_trace(काष्ठा device *dev, स्थिर अक्षर *fmt, ...) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_TRACING */

#पूर्ण_अगर /* __MTU3_DEBUG_H__ */
