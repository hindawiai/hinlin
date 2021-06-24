<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */
#अगर_अघोषित __ASMARC_SETUP_H
#घोषणा __ASMARC_SETUP_H


#समावेश <linux/types.h>
#समावेश <uapi/यंत्र/setup.h>

#घोषणा COMMAND_LINE_SIZE 256

/*
 * Data काष्ठाure to map a ID to string
 * Used a lot क्रम bootup reporting of hardware भागersity
 */
काष्ठा id_to_str अणु
	पूर्णांक id;
	स्थिर अक्षर *str;
पूर्ण;

बाह्य पूर्णांक root_mountflags, end_mem;

व्योम setup_processor(व्योम);
व्योम __init setup_arch_memory(व्योम);
दीर्घ __init arc_get_mem_sz(व्योम);

/* Helpers used in arc_*_mumbojumbo routines */
#घोषणा IS_AVAIL1(v, s)		((v) ? s : "")
#घोषणा IS_DISABLED_RUN(v)	((v) ? "" : "(disabled) ")
#घोषणा IS_USED_RUN(v)		((v) ? "" : "(not used) ")
#घोषणा IS_USED_CFG(cfg)	IS_USED_RUN(IS_ENABLED(cfg))
#घोषणा IS_AVAIL2(v, s, cfg)	IS_AVAIL1(v, s), IS_AVAIL1(v, IS_USED_CFG(cfg))
#घोषणा IS_AVAIL3(v, v2, s)	IS_AVAIL1(v, s), IS_AVAIL1(v, IS_DISABLED_RUN(v2))

#पूर्ण_अगर /* __ASMARC_SETUP_H */
