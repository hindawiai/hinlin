<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2013 Imagination Technologies Ltd.
 */
#अगर_अघोषित _ASM_VPE_H
#घोषणा _ASM_VPE_H

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>

#घोषणा VPE_MODULE_NAME "vpe"
#घोषणा VPE_MODULE_MINOR 1

/* grab the likely amount of memory we will need. */
#अगर_घोषित CONFIG_MIPS_VPE_LOADER_TOM
#घोषणा P_SIZE (2 * 1024 * 1024)
#अन्यथा
/* add an overhead to the max kदो_स्मृति size क्रम non-striped symbols/etc */
#घोषणा P_SIZE (256 * 1024)
#पूर्ण_अगर

#घोषणा MAX_VPES 16

अटल अंतरभूत पूर्णांक aprp_cpu_index(व्योम)
अणु
#अगर_घोषित CONFIG_MIPS_CMP
	वापस setup_max_cpus;
#अन्यथा
	बाह्य पूर्णांक tclimit;
	वापस tclimit;
#पूर्ण_अगर
पूर्ण

क्रमागत vpe_state अणु
	VPE_STATE_UNUSED = 0,
	VPE_STATE_INUSE,
	VPE_STATE_RUNNING
पूर्ण;

क्रमागत tc_state अणु
	TC_STATE_UNUSED = 0,
	TC_STATE_INUSE,
	TC_STATE_RUNNING,
	TC_STATE_DYNAMIC
पूर्ण;

काष्ठा vpe अणु
	क्रमागत vpe_state state;

	/* (device) minor associated with this vpe */
	पूर्णांक minor;

	/* elfloader stuff */
	व्योम *load_addr;
	अचिन्हित दीर्घ len;
	अक्षर *pbuffer;
	अचिन्हित दीर्घ plen;

	अचिन्हित दीर्घ __start;

	/* tc's associated with this vpe */
	काष्ठा list_head tc;

	/* The list of vpe's */
	काष्ठा list_head list;

	/* shared symbol address */
	व्योम *shared_ptr;

	/* the list of who wants to know when something major happens */
	काष्ठा list_head notअगरy;

	अचिन्हित पूर्णांक ntcs;
पूर्ण;

काष्ठा tc अणु
	क्रमागत tc_state state;
	पूर्णांक index;

	काष्ठा vpe *pvpe;	/* parent VPE */
	काष्ठा list_head tc;	/* The list of TC's with this VPE */
	काष्ठा list_head list;	/* The global list of tc's */
पूर्ण;

काष्ठा vpe_notअगरications अणु
	व्योम (*start)(पूर्णांक vpe);
	व्योम (*stop)(पूर्णांक vpe);

	काष्ठा list_head list;
पूर्ण;

काष्ठा vpe_control अणु
	spinlock_t vpe_list_lock;
	काष्ठा list_head vpe_list;      /* Virtual processing elements */
	spinlock_t tc_list_lock;
	काष्ठा list_head tc_list;       /* Thपढ़ो contexts */
पूर्ण;

बाह्य अचिन्हित दीर्घ physical_memsize;
बाह्य काष्ठा vpe_control vpecontrol;
बाह्य स्थिर काष्ठा file_operations vpe_fops;

पूर्णांक vpe_notअगरy(पूर्णांक index, काष्ठा vpe_notअगरications *notअगरy);

व्योम *vpe_get_shared(पूर्णांक index);

काष्ठा vpe *get_vpe(पूर्णांक minor);
काष्ठा tc *get_tc(पूर्णांक index);
काष्ठा vpe *alloc_vpe(पूर्णांक minor);
काष्ठा tc *alloc_tc(पूर्णांक index);
व्योम release_vpe(काष्ठा vpe *v);

व्योम *alloc_progmem(अचिन्हित दीर्घ len);
व्योम release_progmem(व्योम *ptr);

पूर्णांक vpe_run(काष्ठा vpe *v);
व्योम cleanup_tc(काष्ठा tc *tc);

पूर्णांक __init vpe_module_init(व्योम);
व्योम __निकास vpe_module_निकास(व्योम);
#पूर्ण_अगर /* _ASM_VPE_H */
