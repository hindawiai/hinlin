<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2010 Loongson Inc. & Lemote Inc. &
 *                    Institute of Computing Technology
 * Author:  Xiang Gao, gaoxiang@ict.ac.cn
 *          Huacai Chen, chenhc@lemote.com
 *          Xiaofu Meng, Shuangshuang Zhang
 */
#अगर_अघोषित _ASM_MACH_LOONGSON64_MMZONE_H
#घोषणा _ASM_MACH_LOONGSON64_MMZONE_H

#घोषणा NODE_ADDRSPACE_SHIFT 44

#घोषणा pa_to_nid(addr)  (((addr) & 0xf00000000000) >> NODE_ADDRSPACE_SHIFT)
#घोषणा nid_to_addrbase(nid) ((अचिन्हित दीर्घ)(nid) << NODE_ADDRSPACE_SHIFT)

बाह्य काष्ठा pglist_data *__node_data[];

#घोषणा NODE_DATA(n)		(__node_data[n])

बाह्य व्योम setup_zero_pages(व्योम);
बाह्य व्योम __init prom_init_numa_memory(व्योम);

#पूर्ण_अगर /* _ASM_MACH_MMZONE_H */
